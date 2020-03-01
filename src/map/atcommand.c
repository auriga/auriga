/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "socket.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "db.h"

#include "map.h"
#include "msg.h"
#include "chrif.h"
#include "intif.h"
#include "clif.h"
#include "itemdb.h"
#include "pc.h"
#include "skill.h"
#include "mob.h"
#include "pet.h"
#include "homun.h"
#include "battle.h"
#include "party.h"
#include "guild.h"
#include "atcommand.h"
#include "script.h"
#include "npc.h"
#include "status.h"
#include "storage.h"
#include "ranking.h"
#include "homun.h"
#include "unit.h"
#include "merc.h"
#include "elem.h"

static char command_symbol = '@'; /* first char of the commands */

#define COMMAND_HASH_SIZE 127
static AtCommandInfo *command_hash_table[COMMAND_HASH_SIZE];

static AtCommandInfo *synonym_table; /* table for GM command synonyms */
static int synonym_count = 0; /* number of synonyms */

#define MAX_ATCOMMAND_GO 50
struct atcommand_go_db {
	int nameid;
	char code[8];
	char mapname[24];
	short x,y;
};
static struct atcommand_go_db atcommand_go_db[MAX_ATCOMMAND_GO];

#define ATCOMMAND_FUNC(x) int atcommand_ ## x (const int fd, struct map_session_data* sd, AtCommandType command, const char* message)

ATCOMMAND_FUNC(rurap);
ATCOMMAND_FUNC(rura);
ATCOMMAND_FUNC(where);
ATCOMMAND_FUNC(jumpto);
ATCOMMAND_FUNC(jump);
ATCOMMAND_FUNC(who);
ATCOMMAND_FUNC(save);
ATCOMMAND_FUNC(load);
ATCOMMAND_FUNC(speed);
ATCOMMAND_FUNC(storage);
ATCOMMAND_FUNC(guildstorage);
ATCOMMAND_FUNC(option);
ATCOMMAND_FUNC(hide);
ATCOMMAND_FUNC(jobchange);
ATCOMMAND_FUNC(die);
ATCOMMAND_FUNC(kill);
ATCOMMAND_FUNC(alive);
ATCOMMAND_FUNC(kami);
ATCOMMAND_FUNC(heal);
ATCOMMAND_FUNC(item);
ATCOMMAND_FUNC(item2);
ATCOMMAND_FUNC(item3);
ATCOMMAND_FUNC(itemreset);
ATCOMMAND_FUNC(baselevelup);
ATCOMMAND_FUNC(joblevelup);
ATCOMMAND_FUNC(help);
ATCOMMAND_FUNC(gm);
ATCOMMAND_FUNC(pvpoff);
ATCOMMAND_FUNC(pvpon);
ATCOMMAND_FUNC(gvgoff);
ATCOMMAND_FUNC(gvgon);
ATCOMMAND_FUNC(model);
ATCOMMAND_FUNC(go);
ATCOMMAND_FUNC(monster);
ATCOMMAND_FUNC(killmonster);
ATCOMMAND_FUNC(refine);
ATCOMMAND_FUNC(produce);
ATCOMMAND_FUNC(repair);
ATCOMMAND_FUNC(memo);
ATCOMMAND_FUNC(gat);
ATCOMMAND_FUNC(packet);
ATCOMMAND_FUNC(statuspoint);
ATCOMMAND_FUNC(skillpoint);
ATCOMMAND_FUNC(zeny);
ATCOMMAND_FUNC(param);
ATCOMMAND_FUNC(guildlevelup);
ATCOMMAND_FUNC(guildskillpoint);
ATCOMMAND_FUNC(makepet);
ATCOMMAND_FUNC(hatch);
ATCOMMAND_FUNC(petfriendly);
ATCOMMAND_FUNC(pethungry);
ATCOMMAND_FUNC(petrename);
ATCOMMAND_FUNC(charpetrename);
ATCOMMAND_FUNC(recall);
ATCOMMAND_FUNC(recallall);
ATCOMMAND_FUNC(recallguild);
ATCOMMAND_FUNC(recallparty);
ATCOMMAND_FUNC(character_job);
ATCOMMAND_FUNC(revive);
ATCOMMAND_FUNC(character_stats);
ATCOMMAND_FUNC(character_option);
ATCOMMAND_FUNC(character_save);
ATCOMMAND_FUNC(night);
ATCOMMAND_FUNC(day);
ATCOMMAND_FUNC(doom);
ATCOMMAND_FUNC(raise);
ATCOMMAND_FUNC(character_baselevel);
ATCOMMAND_FUNC(character_joblevel);
ATCOMMAND_FUNC(kick);
ATCOMMAND_FUNC(kickall);
ATCOMMAND_FUNC(allskill);
ATCOMMAND_FUNC(questskill);
ATCOMMAND_FUNC(charquestskill);
ATCOMMAND_FUNC(lostskill);
ATCOMMAND_FUNC(charlostskill);
ATCOMMAND_FUNC(spiritball);
ATCOMMAND_FUNC(party);
ATCOMMAND_FUNC(partyoption);
ATCOMMAND_FUNC(guild);
ATCOMMAND_FUNC(agitstart);
ATCOMMAND_FUNC(agitend);
ATCOMMAND_FUNC(onlymes);
ATCOMMAND_FUNC(mesweb);
ATCOMMAND_FUNC(mapexit);
ATCOMMAND_FUNC(idsearch);
ATCOMMAND_FUNC(itemidentify);
ATCOMMAND_FUNC(shuffle);
ATCOMMAND_FUNC(maintenance);
ATCOMMAND_FUNC(misceffect);
ATCOMMAND_FUNC(summon);
ATCOMMAND_FUNC(whop);
ATCOMMAND_FUNC(charskreset);
ATCOMMAND_FUNC(charstreset);
ATCOMMAND_FUNC(charreset);
ATCOMMAND_FUNC(charstpoint);
ATCOMMAND_FUNC(charskpoint);
ATCOMMAND_FUNC(charzeny);
ATCOMMAND_FUNC(charitemreset);
ATCOMMAND_FUNC(mapinfo);
ATCOMMAND_FUNC(mobsearch);
ATCOMMAND_FUNC(cleanmap);
ATCOMMAND_FUNC(clock);
ATCOMMAND_FUNC(giveitem);
ATCOMMAND_FUNC(weather);
ATCOMMAND_FUNC(npctalk);
ATCOMMAND_FUNC(pettalk);
ATCOMMAND_FUNC(homtalk);
ATCOMMAND_FUNC(users);
ATCOMMAND_FUNC(reloadatcommand);
ATCOMMAND_FUNC(reloadbattleconf);
ATCOMMAND_FUNC(reloadgmaccount);
ATCOMMAND_FUNC(reloadhomundb);
ATCOMMAND_FUNC(reloaditemdb);
ATCOMMAND_FUNC(reloadmercdb);
ATCOMMAND_FUNC(reloadelemdb);
ATCOMMAND_FUNC(reloadmobdb);
ATCOMMAND_FUNC(reloadpcdb);
ATCOMMAND_FUNC(reloadskilldb);
ATCOMMAND_FUNC(reloadstatusdb);
ATCOMMAND_FUNC(reloadmotd);
ATCOMMAND_FUNC(itemmonster);
ATCOMMAND_FUNC(mapflag);
ATCOMMAND_FUNC(mannerpoint);
ATCOMMAND_FUNC(connectlimit);
ATCOMMAND_FUNC(econ);
ATCOMMAND_FUNC(ecoff);
ATCOMMAND_FUNC(icon);
ATCOMMAND_FUNC(ranking);
ATCOMMAND_FUNC(blacksmith);
ATCOMMAND_FUNC(alchemist);
ATCOMMAND_FUNC(taekwon);
ATCOMMAND_FUNC(resetfeel);
ATCOMMAND_FUNC(resethate);
ATCOMMAND_FUNC(resetstate);
ATCOMMAND_FUNC(resetskill);
ATCOMMAND_FUNC(emotion);
ATCOMMAND_FUNC(statall);
ATCOMMAND_FUNC(rankingpoint);
ATCOMMAND_FUNC(viewclass);
ATCOMMAND_FUNC(mailbox);
ATCOMMAND_FUNC(readvars);
ATCOMMAND_FUNC(writevars);
ATCOMMAND_FUNC(cloneskill);
ATCOMMAND_FUNC(cloneskill2);
ATCOMMAND_FUNC(reproduce);
ATCOMMAND_FUNC(reproduce2);
ATCOMMAND_FUNC(mobinfo);
ATCOMMAND_FUNC(homlevel);
ATCOMMAND_FUNC(homviewclass);
ATCOMMAND_FUNC(homevolution);
ATCOMMAND_FUNC(homrecalc);
ATCOMMAND_FUNC(makehomun);
ATCOMMAND_FUNC(homfriendly);
ATCOMMAND_FUNC(autoloot);
ATCOMMAND_FUNC(changemaptype);
ATCOMMAND_FUNC(hotkeyset);
ATCOMMAND_FUNC(callmerc);
ATCOMMAND_FUNC(alliance);

/*==========================================
 * AtCommandInfo atcommand_info[]構造体の定義
 *------------------------------------------
 */
static AtCommandInfo atcommand_info[] = {
	{ AtCommand_RuraP,              "@rura+",            0, atcommand_rurap,               NULL },
	{ AtCommand_Rura,               "@rura",             0, atcommand_rura,                NULL },
	{ AtCommand_Where,              "@where",            0, atcommand_where,               NULL },
	{ AtCommand_JumpTo,             "@jumpto",           0, atcommand_jumpto,              NULL },
	{ AtCommand_Jump,               "@jump",             0, atcommand_jump,                NULL },
	{ AtCommand_Who,                "@who",              0, atcommand_who,                 NULL },
	{ AtCommand_Save,               "@save",             0, atcommand_save,                NULL },
	{ AtCommand_Load,               "@load",             0, atcommand_load,                NULL },
	{ AtCommand_Speed,              "@speed",            0, atcommand_speed,               NULL },
	{ AtCommand_Storage,            "@storage",          0, atcommand_storage,             NULL },
	{ AtCommand_GuildStorage,       "@gstorage",         0, atcommand_guildstorage,        NULL },
	{ AtCommand_Option,             "@option",           0, atcommand_option,              NULL },
	{ AtCommand_Hide,               "@hide",             0, atcommand_hide,                NULL },
	{ AtCommand_JobChange,          "@jobchange",        0, atcommand_jobchange,           NULL },
	{ AtCommand_Die,                "@die",              0, atcommand_die,                 NULL },
	{ AtCommand_Kill,               "@kill",             0, atcommand_kill,                NULL },
	{ AtCommand_Alive,              "@alive",            0, atcommand_alive,               NULL },
	{ AtCommand_Kami,               "@kami",             0, atcommand_kami,                NULL },
	{ AtCommand_KamiB,              "@kamib",            0, atcommand_kami,                NULL },
	{ AtCommand_KamiC,              "@kamic",            0, atcommand_kami,                NULL },
	{ AtCommand_Heal,               "@heal",             0, atcommand_heal,                NULL },
	{ AtCommand_Item,               "@item",             0, atcommand_item,                NULL },
	{ AtCommand_Item2,              "@item2",            0, atcommand_item2,               NULL },
	{ AtCommand_Item3,              "@item3",            0, atcommand_item3,               NULL },
	{ AtCommand_ItemReset,          "@itemreset",        0, atcommand_itemreset,           NULL },
	{ AtCommand_BaseLevelUp,        "@lvup",             0, atcommand_baselevelup,         NULL },
	{ AtCommand_JobLevelUp,         "@joblvup",          0, atcommand_joblevelup,          NULL },
	{ AtCommand_Help,               "@help",             0, atcommand_help,                NULL },
	{ AtCommand_GM,                 "@gm",               0, atcommand_gm,                  NULL },
	{ AtCommand_PvPOff,             "@pvpoff",           0, atcommand_pvpoff,              NULL },
	{ AtCommand_PvPOn,              "@pvpon",            0, atcommand_pvpon,               NULL },
	{ AtCommand_GvGOff,             "@gvgoff",           0, atcommand_gvgoff,              NULL },
	{ AtCommand_GvGOn,              "@gvgon",            0, atcommand_gvgon,               NULL },
	{ AtCommand_Model,              "@model",            0, atcommand_model,               NULL },
	{ AtCommand_Go,                 "@go",               0, atcommand_go,                  NULL },
	{ AtCommand_Monster,            "@monster",          0, atcommand_monster,             NULL },
	{ AtCommand_MonsterMap,         "@monstermap",       0, atcommand_monster,             NULL },
	{ AtCommand_KillMonster,        "@killmonster",      0, atcommand_killmonster,         NULL },
	{ AtCommand_KillMonster2,       "@killmonster2",     0, atcommand_killmonster,         NULL },
	{ AtCommand_Refine,             "@refine",           0, atcommand_refine,              NULL },
	{ AtCommand_Produce,            "@produce",          0, atcommand_produce,             NULL },
	{ AtCommand_Repair,             "@repair",           0, atcommand_repair,              NULL },
	{ AtCommand_Memo,               "@memo",             0, atcommand_memo,                NULL },
	{ AtCommand_GAT,                "@gat",              0, atcommand_gat,                 NULL },
	{ AtCommand_Packet,             "@packet",           0, atcommand_packet,              NULL },
	{ AtCommand_StatusPoint,        "@stpoint",          0, atcommand_statuspoint,         NULL },
	{ AtCommand_SkillPoint,         "@skpoint",          0, atcommand_skillpoint,          NULL },
	{ AtCommand_Zeny,               "@zeny",             0, atcommand_zeny,                NULL },
	{ AtCommand_Strength,           "@str",              0, atcommand_param,               NULL },
	{ AtCommand_Agility,            "@agi",              0, atcommand_param,               NULL },
	{ AtCommand_Vitality,           "@vit",              0, atcommand_param,               NULL },
	{ AtCommand_Intelligence,       "@int",              0, atcommand_param,               NULL },
	{ AtCommand_Dexterity,          "@dex",              0, atcommand_param,               NULL },
	{ AtCommand_Luck,               "@luk",              0, atcommand_param,               NULL },
	{ AtCommand_GuildLevelUp,       "@guildlvup",        0, atcommand_guildlevelup,        NULL },
	{ AtCommand_GuildSkillPoint,    "@guildskpoint",     0, atcommand_guildskillpoint,     NULL },
	{ AtCommand_MakePet,            "@makepet",          0, atcommand_makepet,             NULL },
	{ AtCommand_Hatch,              "@hatch",            0, atcommand_hatch,               NULL },
	{ AtCommand_PetFriendly,        "@petfriendly",      0, atcommand_petfriendly,         NULL },
	{ AtCommand_PetHungry,          "@pethungry",        0, atcommand_pethungry,           NULL },
	{ AtCommand_PetRename,          "@petrename",        0, atcommand_petrename,           NULL },
	{ AtCommand_CharPetRename,      "@charpetrename",    0, atcommand_charpetrename,       NULL },
	{ AtCommand_Recall,             "@recall",           0, atcommand_recall,              NULL },
	{ AtCommand_Recallall,          "@recallall",        0, atcommand_recallall,           NULL },
	{ AtCommand_RecallGuild,        "@recallguild",      0, atcommand_recallguild,         NULL },
	{ AtCommand_RecallParty,        "@recallparty",      0, atcommand_recallparty,         NULL },
	{ AtCommand_CharacterJob,       "@charjob",          0, atcommand_character_job,       NULL },
	{ AtCommand_Revive,             "@revive",           0, atcommand_revive,              NULL },
	{ AtCommand_CharacterStats,     "@charstats",        0, atcommand_character_stats,     NULL },
	{ AtCommand_CharacterOption,    "@charoption",       0, atcommand_character_option,    NULL },
	{ AtCommand_CharacterSave,      "@charsave",         0, atcommand_character_save,      NULL },
	{ AtCommand_Night,              "@night",            0, atcommand_night,               NULL },
	{ AtCommand_Day,                "@day",              0, atcommand_day,                 NULL },
	{ AtCommand_Doom,               "@doom",             0, atcommand_doom,                NULL },
	{ AtCommand_DoomMap,            "@doommap",          0, atcommand_doom,                NULL },
	{ AtCommand_Raise,              "@raise",            0, atcommand_raise,               NULL },
	{ AtCommand_RaiseMap,           "@raisemap",         0, atcommand_raise,               NULL },
	{ AtCommand_CharacterBaseLevel, "@charbaselvl",      0, atcommand_character_baselevel, NULL },
	{ AtCommand_CharacterJobLevel,  "@charjlvl",         0, atcommand_character_joblevel,  NULL },
	{ AtCommand_Kick,               "@kick",             0, atcommand_kick,                NULL },
	{ AtCommand_KickAll,            "@kickall",          0, atcommand_kickall,             NULL },
	{ AtCommand_AllSkill,           "@allskill",         0, atcommand_allskill,            NULL },
	{ AtCommand_QuestSkill,         "@questskill",       0, atcommand_questskill,          NULL },
	{ AtCommand_CharQuestSkill,     "@charquestskill",   0, atcommand_charquestskill,      NULL },
	{ AtCommand_LostSkill,          "@lostskill",        0, atcommand_lostskill,           NULL },
	{ AtCommand_CharLostSkill,      "@charlostskill",    0, atcommand_charlostskill,       NULL },
	{ AtCommand_SpiritBall,         "@spiritball",       0, atcommand_spiritball,          NULL },
	{ AtCommand_Party,              "@party",            0, atcommand_party,               NULL },
	{ AtCommand_PartyOption,        "@partyoption",      0, atcommand_partyoption,         NULL },
	{ AtCommand_Guild,              "@guild",            0, atcommand_guild,               NULL },
	{ AtCommand_AgitStart,          "@agitstart",        0, atcommand_agitstart,           NULL },
	{ AtCommand_AgitEnd,            "@agitend",          0, atcommand_agitend,             NULL },
	{ AtCommand_OnlyMes,            "@mes",              0, atcommand_onlymes,             NULL },
	{ AtCommand_MesWeb,             "@mesweb",           0, atcommand_mesweb,              NULL },
	{ AtCommand_MapExit,            "@mapexit",          0, atcommand_mapexit,             NULL },
	{ AtCommand_IDSearch,           "@idsearch",         0, atcommand_idsearch,            NULL },
	{ AtCommand_ItemIdentify,       "@itemidentify",     0, atcommand_itemidentify,        NULL },
	{ AtCommand_Shuffle,            "@shuffle",          0, atcommand_shuffle,             NULL },
	{ AtCommand_Maintenance,        "@maintenance",      0, atcommand_maintenance,         NULL },
	{ AtCommand_Misceffect,         "@misceffect",       0, atcommand_misceffect,          NULL },
	{ AtCommand_Summon,             "@summon",           0, atcommand_summon,              NULL },
	{ AtCommand_WhoP,               "@who+",             0, atcommand_whop,                NULL },
	{ AtCommand_CharReset,          "@charreset",        0, atcommand_charreset,           NULL },
	{ AtCommand_CharSkReset,        "@charskreset",      0, atcommand_charskreset,         NULL },
	{ AtCommand_CharStReset,        "@charstreset",      0, atcommand_charstreset,         NULL },
	{ AtCommand_CharSKPoint,        "@charskpoint",      0, atcommand_charskpoint,         NULL },
	{ AtCommand_CharSTPoint,        "@charstpoint",      0, atcommand_charstpoint,         NULL },
	{ AtCommand_CharZeny,           "@charzeny",         0, atcommand_charzeny,            NULL },
	{ AtCommand_CharItemreset,      "@charitemreset",    0, atcommand_charitemreset,       NULL },
	{ AtCommand_MapInfo,            "@mapinfo",          0, atcommand_mapinfo,             NULL },
	{ AtCommand_MobSearch,          "@mobsearch",        0, atcommand_mobsearch,           NULL },
	{ AtCommand_CleanMap,           "@cleanmap",         0, atcommand_cleanmap,            NULL },
	{ AtCommand_Clock,              "@clock",            0, atcommand_clock,               NULL },
	{ AtCommand_GiveItem,           "@giveitem",         0, atcommand_giveitem,            NULL },
	{ AtCommand_Weather,            "@weather",          0, atcommand_weather,             NULL },
	{ AtCommand_NpcTalk,            "@npctalk",          0, atcommand_npctalk,             NULL },
	{ AtCommand_PetTalk,            "@pettalk",          0, atcommand_pettalk,             NULL },
	{ AtCommand_HomTalk,            "@homtalk" ,         0, atcommand_homtalk,             NULL },
	{ AtCommand_Users,              "@users",            0, atcommand_users,               NULL },
	{ AtCommand_ReloadAtcommand,    "@reloadatcommand",  0, atcommand_reloadatcommand,     NULL },
	{ AtCommand_ReloadBattleConf,   "@reloadbattleconf", 0, atcommand_reloadbattleconf,    NULL },
	{ AtCommand_ReloadGMAccount,    "@reloadgmaccount",  0, atcommand_reloadgmaccount,     NULL },
	{ AtCommand_ReloadHomunDB,      "@reloadhomundb",    0, atcommand_reloadhomundb,       NULL },
	{ AtCommand_ReloadItemDB,       "@reloaditemdb",     0, atcommand_reloaditemdb,        NULL },
	{ AtCommand_ReloadMercDB,       "@reloadmercdb",     0, atcommand_reloadmercdb,        NULL },
	{ AtCommand_ReloadElemDB,       "@reloadelemdb",     0, atcommand_reloadelemdb,        NULL },
	{ AtCommand_ReloadMobDB,        "@reloadmobdb",      0, atcommand_reloadmobdb,         NULL },
	{ AtCommand_ReloadPcDB,         "@reloadpcdb",       0, atcommand_reloadpcdb,          NULL },
	{ AtCommand_ReloadSkillDB,      "@reloadskilldb",    0, atcommand_reloadskilldb,       NULL },
	{ AtCommand_ReloadStatusDB,     "@reloadstatusdb",   0, atcommand_reloadstatusdb,      NULL },
	{ AtCommand_ReloadMotd,         "@reloadmotd",       0, atcommand_reloadmotd,          NULL },
	{ AtCommand_ItemMonster,        "@im",               0, atcommand_itemmonster,         NULL },
	{ AtCommand_Mapflag,            "@mapflag",          0, atcommand_mapflag,             NULL },
	{ AtCommand_MannerPoint,        "@mannerpoint",      0, atcommand_mannerpoint,         NULL },
	{ AtCommand_ConnectLimit,       "@connectlimit",     0, atcommand_connectlimit,        NULL },
	{ AtCommand_Econ,               "@econ",             0, atcommand_econ,                NULL },
	{ AtCommand_Ecoff,              "@ecoff",            0, atcommand_ecoff,               NULL },
	{ AtCommand_Icon,               "@icon",             0, atcommand_icon,                NULL },
	{ AtCommand_Ranking,            "@ranking",          0, atcommand_ranking,             NULL },
	{ AtCommand_Blacksmith,         "@blacksmith",       0, atcommand_blacksmith,          NULL },
	{ AtCommand_Alchemist,          "@alchemist",        0, atcommand_alchemist,           NULL },
	{ AtCommand_TaeKwon,            "@taekwon",          0, atcommand_taekwon,             NULL },
	{ AtCommand_ResetFeel,          "@resetfeel",        0, atcommand_resetfeel,           NULL },
	{ AtCommand_ResetHate,          "@resethate",        0, atcommand_resethate,           NULL },
	{ AtCommand_ResetState,         "@resetstate",       0, atcommand_resetstate,          NULL },
	{ AtCommand_ResetSkill,         "@resetskill",       0, atcommand_resetskill,          NULL },
	{ AtCommand_emotion,            "@emotion",          0, atcommand_emotion,             NULL },
	{ AtCommand_statall,            "@statall",          0, atcommand_statall,             NULL },
	{ AtCommand_RankingPoint,       "@rankingpoint",     0, atcommand_rankingpoint,        NULL },
	{ AtCommand_ViewClass,          "@viewclass",        0, atcommand_viewclass,           NULL },
	{ AtCommand_MailBox,            "@mailbox",          0, atcommand_mailbox,             NULL },
	{ AtCommand_ReadVars,           "@readvars",         0, atcommand_readvars,            NULL },
	{ AtCommand_WriteVars,          "@writevars",        0, atcommand_writevars,           NULL },
	{ AtCommand_CloneSkill,         "@cloneskill",       0, atcommand_cloneskill,          NULL },
	{ AtCommand_CloneSkill2,        "@cloneskill2",      0, atcommand_cloneskill2,         NULL },
	{ AtCommand_Reproduce,          "@reproduce",        0, atcommand_reproduce,           NULL },
	{ AtCommand_Reproduce2,         "@reproduce2",       0, atcommand_reproduce2,          NULL },
	{ AtCommand_MobInfo,            "@mobinfo",          0, atcommand_mobinfo,             NULL },
	{ AtCommand_HomLevel,           "@homlv",            0, atcommand_homlevel,            NULL },
	{ AtCommand_HomViewClass,       "@homviewclass",     0, atcommand_homviewclass,        NULL },
	{ AtCommand_HomEvolution,       "@evolution",        0, atcommand_homevolution,        NULL },
	{ AtCommand_HomRecalc,          "@homrecalc",        0, atcommand_homrecalc,           NULL },
	{ AtCommand_MakeHomun,          "@makehomun",        0, atcommand_makehomun,           NULL },
	{ AtCommand_HomFriendly,        "@homfriendly",      0, atcommand_homfriendly,         NULL },
	{ AtCommand_AutoLoot,           "@autoloot",         0, atcommand_autoloot,            NULL },
	{ AtCommand_ChangeMapType,      "@changemaptype",    0, atcommand_changemaptype,       NULL },
	{ AtCommand_HotkeySet,          "@hotkeyset",        0, atcommand_hotkeyset,           NULL },
	{ AtCommand_CallMerc,           "@callmerc",         0, atcommand_callmerc,            NULL },
	{ AtCommand_Alliance,           "@alliance",         0, atcommand_alliance,            NULL },
		// add here
	{ AtCommand_MapMove,            "@mapmove",          0, NULL,                          NULL },
	{ AtCommand_Broadcast,          "@broadcast",        0, NULL,                          NULL },
	{ AtCommand_LocalBroadcast,     "@local_broadcast",  0, NULL,                          NULL },
	{ AtCommand_Unknown,            NULL,              100, NULL,                          NULL },
};

/*===============================================
 * This function return the GM command symbol
 *-----------------------------------------------
 */
char GM_Symbol(void)
{
	return command_symbol;
}

/*==========================================
 * ハッシュ計算
 *------------------------------------------
 */
static unsigned int command2hash(const unsigned char *p)
{
	unsigned int h = 0;

	// SDBM Algorithm
	while (*p) {
		h = (h<<6)+(h<<16)-h;
		h += (unsigned char)tolower(*p++);
	}
	return h % COMMAND_HASH_SIZE;
}

/*==========================================
 *
 *------------------------------------------
 */
static AtCommandInfo* get_atcommandinfo_byname(const char* name)
{
	AtCommandInfo *p = command_hash_table[command2hash(name)];

	while (p) {
		if (strcmpi(p->command + 1, name) == 0) {
			return p;
		}
		p = p->next;
	}

	return NULL;
}

/*==========================================
 * @コマンドの必要レベルを取得
 *------------------------------------------
 */
int get_atcommand_level(const AtCommandType type)
{
	int i;

	for (i = 0; atcommand_info[i].type != AtCommand_None; i++) {
		if (atcommand_info[i].type == type)
			return atcommand_info[i].level;
	}
	return 100;
}

/*==========================================
 * @コマンドに存在するかどうか確認する
 *------------------------------------------
 */
AtCommandType is_atcommand_sub(const int fd, struct map_session_data *sd, const char *str, int gmlvl)
{
	AtCommandInfo *info;
	char command[100];
	const char *p = str;

	nullpo_retr(AtCommand_None, sd);

	if (!p || !*p) {
		printf("at command message is empty\n");
		return AtCommand_None;
	}
	if (p[0] != command_symbol || p[1] == command_symbol)
		return AtCommand_None;

	while (*p && !isspace((unsigned char)*p)) {
		p++;
	}
	if (p - str >= sizeof command) // too long
		return AtCommand_None;

	if (gmlvl <= 0)
		gmlvl = pc_isGM(sd);

	memset(command, '\0', sizeof command);
	memcpy(command, str, p - str);

	info = get_atcommandinfo_byname(command + 1);
	if (info == NULL || info->proc == NULL || gmlvl < info->level) {
		if (pc_isGM(sd)) {
			msg_output(fd, msg_txt(132), command);
			return AtCommand_Unknown;
		}
		return AtCommand_None;
	}

	if (map[sd->bl.m].flag.nocommand && map[sd->bl.m].flag.nocommand > gmlvl) {
		msg_output(fd, msg_txt(180), command);
	} else {
		// コマンド実行
		if (isspace((unsigned char)*p)) {
			p++;
		}
		if (info->proc(fd, sd, info->type, p) != 0) {
			if (pc_isGM(sd)) {
				// 異常終了
				msg_output(fd, msg_txt(133), command);
			} else {
				return AtCommand_None;
			}
		}
	}

	return info->type;
}

/*==========================================
 *
 *------------------------------------------
 */
AtCommandType is_atcommand(const int fd, struct map_session_data* sd, const char* message)
{
	const char* str;
	int s_flag;

	nullpo_retr(AtCommand_None, sd);

	if (!message || !*message)
		return AtCommand_None;

	str = message + strlen(sd->status.name);
	s_flag = 0;
	while (*str && (isspace((unsigned char)*str) || (s_flag == 0 && *str == ':'))) {
		if (*str == ':')
			s_flag = 1;
		str++;
	}
	if (!*str)
		return AtCommand_None;

	return is_atcommand_sub(fd, sd, str, 0);
}


/*==========================================
 *
 *------------------------------------------
 */
static void atcommand_synonym_free(void)
{
	int i;

	for (i = 0; i < synonym_count; i++) {
		char *cmd = (char *)synonym_table[i].command;	// freeするためにconst外す
		aFree(cmd);
	}
	if (synonym_table != NULL) {
		aFree(synonym_table);
		synonym_table = NULL;
	}
	synonym_count = 0;

	return;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
void do_final_atcommand(void)
{
	atcommand_synonym_free();

	return;
}

/*==========================================
 * ハッシュテーブルへ追加
 *------------------------------------------
 */
static void atcommand_add_hashtable(AtCommandInfo *info)
{
	unsigned int h;
	AtCommandInfo *p;

	nullpo_retv(info);

	h = command2hash(info->command + 1);
	p = command_hash_table[h];

	if (p == NULL) {
		command_hash_table[h] = info;
	} else {
		while (p->next) {
			p = p->next;
		}
		p->next = info;
	}

	return;
}

/*==========================================
 * ハッシュテーブル作成
 *------------------------------------------
 */
static int atcommand_create_hashtable(void)
{
	int i;

	for (i = 0; i < COMMAND_HASH_SIZE; i++) {
		command_hash_table[i] = NULL;
	}
	for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++) {
		atcommand_add_hashtable(&atcommand_info[i]);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_config_read(const char *cfgName)
{
	static int counter = 0;
	int i;
	AtCommandInfo* p;
	FILE* fp;
	char line[1024], w1[1024], w2[1024];

	if (counter == 0) {
		atcommand_synonym_free();

		for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++) {
			atcommand_info[i].level = 0;
			atcommand_info[i].next  = NULL;
		}
		atcommand_info[i].level = 100; // AtCommand_Unknown
		atcommand_create_hashtable();
		command_symbol = '@';
	}

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("atcommand_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}
	counter++;

	while (fgets(line, sizeof(line)-1, fp)) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if (sscanf(line, "%1023[^=]= %1023[^\r\n]", w1, w2) == 2) { // synonym
			char *c = NULL;

			/* searching if synonym is not a gm command */
			if ((p = get_atcommandinfo_byname(w1)) != NULL) {
				printf("Error in %s file: GM synonym '%s' is not a synonym, but a GM command.\n", cfgName, w1);
				continue;
			}
			if(battle_config.atc_gmonly > 0) {
				c = strchr(w2, ':');
				if (c)
					*c = 0;
			}

			/* searching if gm command exists */
			if ((p = get_atcommandinfo_byname(w2)) != NULL) {
				// GM command found, create synonym
				char *cmd;
				int level;

				if(c && c[1] == ' ') {
					// set synonym GM level
					level = atoi(c + 2);
					if (level < 0)
						level = 0;
					else if (level > 100)
						level = 100;
				} else {
					level = p->level;
				}

				if (synonym_count == 0) {
					synonym_table = (AtCommandInfo *)aMalloc(sizeof(AtCommandInfo));
				} else {
					synonym_table = (AtCommandInfo *)aRealloc(synonym_table, (synonym_count + 1) * sizeof(AtCommandInfo));
				}
				synonym_table[synonym_count].type  = p->type;
				synonym_table[synonym_count].level = level;
				synonym_table[synonym_count].proc  = p->proc;
				synonym_table[synonym_count].next  = NULL;

				cmd = (char *)aMalloc(strlen(w1) + 2);	// symbol + \0 = 2
				cmd[0] = '@';
				memcpy(cmd + 1, w1, strlen(w1) + 1);

				synonym_table[synonym_count].command = cmd;
				synonym_count++;
			} else {
				printf("Error in %s file: GM command '%s' of synonym '%s' doesn't exist.\n", cfgName, w2, w1);
			}
		} else if (sscanf(line, "%1024[^:]:%1023s", w1, w2) == 2) {
			if (strcmpi(w1, "import") == 0) {
				atcommand_config_read(w2);
			} else if (strcmpi(w1, "command_symbol") == 0) {
				if (!iscntrl(w2[0]) && // w2[0] > 31 &&
				    w2[0] != '/' && // symbol of standard ragnarok GM commands
				    w2[0] != '%' && // symbol of party chat speaking
				    w2[0] != '$') // symbol of guild chat speaking
					command_symbol = w2[0];
			} else if (battle_config.atc_gmonly > 0) {
				if ((p = get_atcommandinfo_byname(w1)) != NULL) {
					p->level = atoi(w2);
					if (p->level < 0)
						p->level = 0;
					else if (p->level > 100)
						p->level = 100;
				} else {
					printf("file [%s]: Unknown GM command: %c%s.\n", cfgName, command_symbol, w1);
				}
			}
		}
	}
	fclose(fp);

	counter--;
	if (counter == 0) {
		// synonym tableはreallocでメモリが移動するのでハッシュテーブルへの追加は最後に行う
		for (i = 0; i < synonym_count; i++) {
			atcommand_add_hashtable(&synonym_table[i]);
		}
		printf("Symbol: '%c' for GM commands.\n", command_symbol);
	}

	return 0;
}

// @ command 処理関数群

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_rurap(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char map_name[100];
	char character[100];
	int x, y;
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99s %d %d %99[^\n]", map_name, &x, &y, character) < 4)
		return -1;

	pl_sd = map_nick2sd(character);
	if (pl_sd == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return 0;
	}

	if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
		int m;

		if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13)
			strcat(map_name, ".gat");
		m = map_mapname2mapid(map_name);
		if (x < 0 || y < 0 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys))) {
			clif_displaymessage(fd, msg_txt(2));
		} else {
			if (pc_setpos(pl_sd, map_name, x, y, 3) == 0) {
				clif_displaymessage(pl_sd->fd, msg_txt(0));
			} else {
				clif_displaymessage(fd, msg_txt(1));
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_rura(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char map_name[100];
	int x = 0, y = 0, m;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %d %d", map_name, &x, &y) < 1)
		return -1;

	if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13)
		strcat(map_name, ".gat");

	m = map_mapname2mapid(map_name);
	if (x < 0 || y < 0 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys)))
		clif_displaymessage(fd, msg_txt(2));
	else
		clif_displaymessage(fd, (pc_setpos(sd, map_name, x, y, 3) == 0) ? msg_txt(0) : msg_txt(1));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_where(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (message && *message) {
		char character[100];
		memset(character, '\0', sizeof character);
		if (sscanf(message, "%99[^\n]", character) < 1)
			return -1;
		if (strlen(character) > 23)
			return -1;
		intif_where(sd->status.account_id, character);
	} else {
		msg_output(fd, "%s %s %d %d", sd->status.name, sd->mapname, sd->bl.x, sd->bl.y);
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_jumpto(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;
	if (strlen(character) > 23 || strncmp(sd->status.name, character, 24) == 0)
		return -1;

	intif_jumpto(sd->status.account_id,character);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_jump(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int x = 0, y = 0;

	nullpo_retr(-1, sd);

	if (message && *message) {
		if (sscanf(message, "%d %d", &x, &y) < 2)
			return -1;
	}

	if (x >= 0 && x < map[sd->bl.m].xs && y >= 0 && y < map[sd->bl.m].ys) {
		pc_setpos(sd, sd->mapname, x, y, 3);
		msg_output(fd, msg_txt(5), x, y);
	} else {
		clif_displaymessage(fd, msg_txt(2));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_who(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	map_who(fd);

	return 0;
}

/*==========================================
 * 居場所付き検索を行う
 *------------------------------------------
 */
int atcommand_whop(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
			if (!(battle_config.hide_GM_session && pc_isGM(pl_sd))) {
				msg_output(fd, "%s [%d/%d] %s %d %d",
					pl_sd->status.name, pl_sd->status.base_level, pl_sd->status.job_level,
					pl_sd->mapname, pl_sd->bl.x, pl_sd->bl.y);
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_save(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_setsavepoint(sd, sd->mapname, sd->bl.x, sd->bl.y);
	if (sd->status.pet_id > 0 && sd->pd)
		intif_save_petdata(sd->status.account_id, &sd->pet);
	chrif_save(sd,0);
	storage_storage_save(sd);
	clif_displaymessage(fd, msg_txt(6));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_load(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_setpos(sd, sd->status.save_point.map, sd->status.save_point.x, sd->status.save_point.y, 0);
	clif_displaymessage(fd, msg_txt(7));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_speed(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int speed;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	speed = atoi(message);
	if (speed > MIN_WALK_SPEED && speed < MAX_WALK_SPEED) {
		sd->speed = speed;
		clif_updatestatus(sd, SP_SPEED);
		clif_displaymessage(fd, msg_txt(8));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_storage(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	if (storage_storageopen(sd) == 1)
		clif_displaymessage(fd, msg_txt(130));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_guildstorage(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.guild_id > 0 && sd->state.gstorage_lockreq == 0) {
		sd->state.gstorage_lockreq = 2;
		intif_trylock_guild_storage(sd,0);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_option(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	unsigned short opt1 = OPT1_NORMAL;
	char opt2[100] = "", opt3[100] = "", option[100] = "";

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%hu %99s %99s %99s", &opt1, opt2, option, opt3) < 1)
		return -1;

	sd->sc.opt1 = opt1;
	sd->sc.opt2 = (unsigned short)strtoul(opt2, NULL, 0);
	sd->sc.opt3 = strtoul(opt3, NULL, 0);

	clif_changeoption2(&sd->bl);
	pc_setoption(sd, strtoul(option, NULL, 0));

	clif_displaymessage(fd, msg_txt(9));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_hide(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (pc_isinvisible(sd)) {
		sd->sc.option &= ~OPTION_SPECIALHIDING;
		clif_displaymessage(fd, msg_txt(10));
		if (battle_config.gm_perfect_hide)	// 完全なインビジブルモードなら出現させる
			clif_spawnpc(sd);
	} else {
		sd->sc.option |= OPTION_SPECIALHIDING;
		clif_displaymessage(fd, msg_txt(11));
		if (battle_config.gm_perfect_hide)	// 完全なインビジブルモードなら消滅させる
			clif_clearchar(&sd->bl,0);
	}
	clif_changeoption(&sd->bl);

	return 0;
}

/*==========================================
 * 転職する upperを指定すると転生や養子にもなれる
 *------------------------------------------
 */
int atcommand_jobchange(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int job, upper = -1;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &job, &upper) < 1)
		return -1;

	if (job >= 0 && job < PC_JOB_MAX) {
		if (pc_jobchange(sd, job, upper) == 0)
			clif_displaymessage(fd, msg_txt(12));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_die(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_damage(NULL, sd, sd->status.hp + 1);
	clif_displaymessage(fd, msg_txt(13));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_kill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
			clif_displaymessage(fd, msg_txt(14));
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_alive(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!unit_isdead(&sd->bl))
		return -1;

	sd->status.hp = sd->status.max_hp;
	sd->status.sp = sd->status.max_sp;
	pc_setstand(sd);
	if (battle_config.pc_invincible_time > 0)
		pc_setinvincibletimer(sd, battle_config.pc_invincible_time);
	clif_updatestatus(sd, SP_HP);
	clif_updatestatus(sd, SP_SP);
	clif_resurrection(&sd->bl, 1);
	clif_displaymessage(fd, msg_txt(16));

	return 0;
}

/*==========================================
 * @kami,@kamib,@kamic
 *------------------------------------------
 */
int atcommand_kami(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char output[200];

	if (!message || !*message)
		return -1;

	if (command == AtCommand_KamiC) {
		unsigned int color;
		if (sscanf(message, "%x %199[^\n]", &color, output) < 2)
			return -1;
		intif_announce(output, strlen(output) + 1, color&0x00ffffff, 400, 12, 0, 0);
	} else {
		if (sscanf(message, "%199[^\n]", output) < 1)
			return -1;
		intif_GMmessage(output, strlen(output) + 1, (command == AtCommand_KamiB) ? 0x10 : 0);
	}

	return 0;
}

/*==========================================
 * 叫ぶ
 *------------------------------------------
 */
int atcommand_onlymes(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char temp[200], buf[512];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%199[^#\n]", temp) < 1)
		return -1;

	snprintf(buf, sizeof(buf), "%s %s : %s", msg_txt(156), sd->status.name, temp);	// [mes]
	clif_onlymessage(buf, strlen(buf) + 1);

	return 0;
}

/*==========================================
 * Webチャット
 *------------------------------------------
 */
int atcommand_mesweb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char temp[200];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%199[^#\n]", temp) < 1)
		return -1;

	clif_webchat_message(msg_txt(156), sd->status.name, temp); // [mes]

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_heal(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int hp = 0, sp = 0;

	nullpo_retr(-1, sd);

	if (message && *message)
		sscanf(message, "%d %d", &hp, &sp);

	if (hp == 0) {
		hp = sd->status.max_hp - sd->status.hp;
	} else if (hp > 0) {
		if (hp > sd->status.max_hp - sd->status.hp)
			hp = sd->status.max_hp - sd->status.hp;
	} else if (hp < 0) {
		if (hp < -sd->status.hp + 1)
			hp = -sd->status.hp + 1;
	}
	if (sp == 0) {
		sp = sd->status.max_sp - sd->status.sp;
	} else if (sp > 0) {
		if (sp > sd->status.max_sp - sd->status.sp)
			sp = sd->status.max_sp - sd->status.sp;
	} else if (sp < 0) {
		if (sp < -sd->status.sp)
			sp = -sd->status.sp;
	}

	if (hp > 0)
		clif_heal(fd, SP_HP, (hp > 0x7fff) ? 0x7fff : hp);
	if (sp > 0)
		clif_heal(fd, SP_SP, (sp > 0x7fff) ? 0x7fff : sp);
	pc_heal(sd, hp, sp);
	clif_displaymessage(fd, msg_txt(17));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_item(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char item_name[100];
	int number = 0, item_id = 0;
	struct item_data *item_data;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d", item_name, &number) < 1)
		return -1;

	if (number <= 0)
		number = 1;

	item_id = atoi(item_name);
	if (item_id < 0)
		item_id = itemdb_searchrandomid(-item_id);

	if (item_id > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(item_name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}

	if (item_id > 0) {
		int i, flag;
		int loop = 1, get_count = number;
		struct item item_tmp;

		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			loop = number;
			get_count = 1;
		}
		for (i = 0; i < loop; i++) {
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid = item_id;
			item_tmp.identify = 1;
			if ((flag = pc_additem(sd, &item_tmp, get_count)))
				clif_additem(sd, 0, 0, flag);
		}
		clif_displaymessage(fd, msg_txt(18));
	} else {
		clif_displaymessage(fd, msg_txt(19));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_item2(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct item_data *item_data;
	char item_name[100];
	int item_id = 0, number = 0;
	int identify = 0, refine = 0, attr = 0;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	unsigned int limit = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %d %d %d %d %d %d %d %u",
		item_name, &number, &identify, &refine, &attr, &c1, &c2, &c3, &c4, &limit) < 10)
		return -1;

	if (number <= 0)
		number = 1;
	if (battle_config.itemidentify)
		identify = 1;
	if ((item_id = atoi(item_name)) > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(item_name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}

	if (item_id > 0) {
		int i, flag;
		int loop = 1, get_count = number;
		struct item item_tmp;

		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			loop = number;
			get_count = 1;
			if (item_data->flag.pet_egg) {
				identify = 1;
				refine = 0;
			}
			if (item_data->flag.pet_acce)
				refine = 0;
			if (refine > MAX_REFINE)
				refine = MAX_REFINE;
		} else {
			identify = 1;
			refine = 0;
			attr = 0;
		}
		for (i = 0; i < loop; i++) {
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid    = item_id;
			item_tmp.identify  = identify;
			item_tmp.refine    = refine;
			item_tmp.attribute = attr;
			item_tmp.card[0]   = c1;
			item_tmp.card[1]   = c2;
			item_tmp.card[2]   = c3;
			item_tmp.card[3]   = c4;
			item_tmp.limit     = (limit > 0)? (unsigned int)time(NULL) + limit: 0;
			if ((flag = pc_additem(sd, &item_tmp, get_count)))
				clif_additem(sd, 0, 0, flag);
		}
		clif_displaymessage(fd, msg_txt(18));
	} else {
		clif_displaymessage(fd, msg_txt(19));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_item3(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	struct item_data *item_data;
	char item_name[100];
	char character[100];
	int item_id = 0, number = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %99[^\n]", item_name, &number, character) < 3)
		return -1;

	if (number <= 0)
		number = 1;
	if ((pl_sd = map_nick2sd(character)) == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return 0;
	}

	if ((item_id = atoi(item_name)) > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(item_name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}

	if (item_id > 0) {
		int i, flag;
		int loop = 1, get_count = number, equip_item = 0;
		struct item item_tmp;

		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			loop = number;
			get_count = 1;
			equip_item = 1;
		}
		for (i = 0; i < loop; i++) {
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid    = item_id;
			item_tmp.identify  = 1;
			item_tmp.refine    = 0;
			item_tmp.attribute = 0;
			item_tmp.card[0]   = (equip_item) ? 0x00ff : 0x00fe;
			item_tmp.card[1]   = 0;
			*((int *)(&item_tmp.card[2])) = pl_sd->status.char_id;
			if ((flag = pc_additem(sd, &item_tmp, get_count)))
				clif_additem(sd, 0, 0, flag);
		}
		clif_displaymessage(fd, msg_txt(18));
	} else {
		clif_displaymessage(fd, msg_txt(19));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_itemreset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].amount && sd->status.inventory[i].equip == 0) {
			if (sd->status.inventory[i].card[0] == (short)0xff00)
				intif_delete_petdata(*((int *)(&sd->status.inventory[i].card[1])));
			pc_delitem(sd, i, sd->status.inventory[i].amount, 0, 0);
		}
	}
	clif_displaymessage(fd, msg_txt(20));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charitemreset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		int i;
		for (i = 0; i < MAX_INVENTORY; i++) {
			if (pl_sd->status.inventory[i].amount && pl_sd->status.inventory[i].equip == 0) {
				if (pl_sd->status.inventory[i].card[0] == (short)0xff00)
	 				intif_delete_petdata(*((int *)(&pl_sd->status.inventory[i].card[1])));
				pc_delitem(pl_sd, i, pl_sd->status.inventory[i].amount, 0, 0);
			}
		}
		clif_displaymessage(fd, msg_txt(20));
		clif_displaymessage(pl_sd->fd, msg_txt(20));
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_baselevelup(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int level;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	level = atoi(message);
	if (level > MAX_LEVEL)
		level = MAX_LEVEL;
	else if (level < -MAX_LEVEL)
		level = -MAX_LEVEL;

	if (level > 0) {
		int i;
		if (sd->status.base_level + level > MAX_LEVEL)
			level = MAX_LEVEL - (int)sd->status.base_level;
		if (level <= 0)
			return -1;
		for (i = 1; i <= level; i++) {
			if(sd->status.base_level + i >= 151 && battle_config.get_status_point_over_lv100)
				sd->status.status_point += (sd->status.base_level + i + 45 ) / 7;
			else if(sd->status.base_level + i >= 100 && battle_config.get_status_point_over_lv100)
				sd->status.status_point += (sd->status.base_level + i + 129 ) / 10;
			else
				sd->status.status_point += (sd->status.base_level + i + 14) / 5;
		}
		sd->status.base_level += level;
		clif_updatestatus(sd, SP_BASELEVEL);
		clif_updatestatus(sd, SP_NEXTBASEEXP);
		clif_updatestatus(sd, SP_STATUSPOINT);
		status_calc_pc(sd, 0);
		pc_heal(sd, sd->status.max_hp, sd->status.max_sp);
		clif_misceffect(&sd->bl, 0);
		clif_displaymessage(fd, msg_txt(21));
	} else if (level < 0) {
		if ((int)sd->status.base_level + level <= 0)
			level = 1 - (int)sd->status.base_level;
		if (level >= 0)
			return -1;
		sd->status.base_level += level;
		clif_updatestatus(sd, SP_BASELEVEL);
		clif_updatestatus(sd, SP_NEXTBASEEXP);
		status_calc_pc(sd, 0);
		clif_displaymessage(fd, msg_txt(22));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_joblevelup(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int up_level, level;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	up_level = max_job_table[sd->s_class.upper][sd->s_class.job];

	level = atoi(message);
	if (level > up_level)
		level = up_level;
	else if (level < -up_level)
		level = -up_level;

	if (sd->status.job_level == up_level && level > 0) {
		clif_displaymessage(fd, msg_txt(23));
	} else if (level >= 1) {
		if (sd->status.job_level + level > up_level)
			level = up_level - sd->status.job_level;
		sd->status.job_level += level;
		clif_updatestatus(sd, SP_JOBLEVEL);
		clif_updatestatus(sd, SP_NEXTJOBEXP);
		sd->status.skill_point += level;
		clif_updatestatus(sd, SP_SKILLPOINT);
		status_calc_pc(sd, 0);
		clif_misceffect(&sd->bl, 1);
		clif_displaymessage(fd, msg_txt(24));
	} else if (level < 0 && sd->status.job_level + level > 0) {
		sd->status.job_level += level;
		clif_updatestatus(sd, SP_JOBLEVEL);
		clif_updatestatus(sd, SP_NEXTJOBEXP);
		status_calc_pc(sd, 0);
		clif_displaymessage(fd, msg_txt(25));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_help(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	FILE* fp;
	char buf[1024];
	int i, start = 0, end = 0, lines = 0;

	if (message && *message) {
		sscanf(message, "%d %d", &start, &end);
		if (start < 0 || end < 0 || (start > 0 && end > 0 && start > end)) {
			clif_displaymessage(fd, msg_txt(27));
			return 0;
		}
	}

	fp = fopen(help_txt, "r");
	if (fp == NULL) {
		clif_displaymessage(fd, msg_txt(27));
		return 0;
	}
	clif_displaymessage(fd, msg_txt(26));

	while (fgets(buf, 1020, fp) != NULL) {
		lines++;
		if ((start > 0 && lines < start) || (end > 0 && lines > end))
			continue;
		if (buf[0] == '/' && buf[1] == '/')
			continue;
		for (i = 0; buf[i] != '\0'; i++) {
			if (buf[i] == '\r' || buf[i] == '\n') {
				buf[i] = '\0';
				break;
			}
		}
		if (buf[0] == '\0')	// 空文字は表示されないのでパケット送信しない
			continue;

		// symbolの置換
		if (command_symbol != '@') {
			char *p = buf;
			while ((p = strchr(p, '@')) != NULL) {
				for (i = 0; i < synonym_count; i++) {
					if (strncasecmp(p+1, synonym_table[i].command+1, strlen(synonym_table[i].command+1)) == 0) {
						*p = command_symbol;
						break;
					}
				}
				if (i == synonym_count) {
					for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++) {
						if (strncasecmp(p+1, atcommand_info[i].command+1, strlen(atcommand_info[i].command+1)) == 0) {
							*p = command_symbol;
							break;
						}
					}
				}
				p++;
			}
		}
		clif_displaymessage(fd, buf);
	}
	fclose(fp);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_gm(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char password[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", password) < 1)
		return -1;

	if (sd->status.party_id) {
		clif_displaymessage(fd, msg_txt(28));
	} else if (sd->status.guild_id) {
		clif_displaymessage(fd, msg_txt(29));
	} else {
		if (sd->status.pet_id > 0 && sd->pd)
			intif_save_petdata(sd->status.account_id, &sd->pet);
		chrif_save(sd,0);
		storage_storage_save(sd);
		clif_displaymessage(fd, msg_txt(30));
		chrif_changegm(sd->status.account_id, password, strlen(password) + 1);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_pvpoff(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (map[sd->bl.m].flag.pvp) {
		struct map_session_data *pl_sd;
		int i;

		map[sd->bl.m].flag.pvp = 0;
		clif_send0199(sd->bl.m, 0);
		for (i = 0; i < fd_max; i++) {	// 人数分ループ
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
				if (sd->bl.m == pl_sd->bl.m) {
					clif_pvpset(pl_sd, 0, 0, 2);
					if (pl_sd->pvp_timer != -1) {
						delete_timer(pl_sd->pvp_timer, pc_calc_pvprank_timer);
						pl_sd->pvp_timer = -1;
					}
				}
			}
		}
		map_field_setting();
		clif_displaymessage(fd, msg_txt(31));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_pvpon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	unsigned int tick = gettick();

	nullpo_retr(-1, sd);

	if (!map[sd->bl.m].flag.pvp) {
		struct map_session_data *pl_sd;
		int i;

		map[sd->bl.m].flag.pvp = 1;
		clif_send0199(sd->bl.m, 1);
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
				if (sd->bl.m == pl_sd->bl.m && pl_sd->pvp_timer == -1) {
					pl_sd->pvp_timer = add_timer(tick + 200,pc_calc_pvprank_timer, pl_sd->bl.id, NULL);
					pl_sd->pvp_rank = 0;
					pl_sd->pvp_lastusers = 0;
					pl_sd->pvp_point = 5;
				}
			}
		}
		map_field_setting();
		clif_displaymessage(fd, msg_txt(32));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_gvgoff(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (map[sd->bl.m].flag.gvg) {
		map[sd->bl.m].flag.gvg = 0;
		clif_send0199(sd->bl.m, 0);
		clif_displaymessage(fd, msg_txt(33));
		map_field_setting();
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_gvgon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!map[sd->bl.m].flag.gvg) {
		map[sd->bl.m].flag.gvg = 1;
		clif_send0199(sd->bl.m, 3);
		clif_displaymessage(fd, msg_txt(34));
		map_field_setting();
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_model(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int hair_style = 0, hair_color = 0, cloth_color = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d %d", &hair_style, &hair_color, &cloth_color) < 1)
		return -1;

	if (hair_style  >= -1 && hair_style  < MAX_HAIR_STYLE &&
	    hair_color  >= -1 && hair_color  < MAX_HAIR_COLOR &&
	    cloth_color >= -1 && cloth_color < MAX_CLOTH_COLOR)
	{
		if (MAX_CLOTH_COLOR <= 5 && cloth_color > 0) {
			if ( (sd->sex == SEX_MALE && (sd->status.class_ == PC_CLASS_AS ||  sd->status.class_ == PC_CLASS_RG)) ||
			     (sd->status.class_ >= PC_CLASS_TK && sd->status.class_ <= PC_CLASS_SL) )
			{
				// 服の色未実装職の判定
				clif_displaymessage(fd, msg_txt(35));
				return 0;
			}
		}
		// -1指定の箇所は変更しない
		if (hair_style >= 0)
			pc_changelook(sd, LOOK_HAIR, hair_style);
		if (hair_color >= 0)
			pc_changelook(sd, LOOK_HAIR_COLOR, hair_color);
		if (cloth_color >= 0)
			pc_changelook(sd, LOOK_CLOTHES_COLOR, cloth_color);
		clif_displaymessage(fd, msg_txt(36));
	} else {
		clif_displaymessage(fd, msg_txt(37));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_go(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char map_code[100];
	int i, idx = -1;

	nullpo_retr(-1, sd);

	if(!message || !*message)
		return -1;
	if(sscanf(message, "%99s", map_code) < 1)
		return -1;

	if(isdigit(*map_code)) {
		int go_id = atoi(map_code);
		// DBのIDから検索
		for(i=0; i<MAX_ATCOMMAND_GO; i++) {
			if(atcommand_go_db[i].nameid == go_id) {
				idx = i;
				break;
			}
		}
	}
	else {
		// DBの略称名(code)から検索
		for(i=0; i<MAX_ATCOMMAND_GO; i++) {
			if(strcmpi(atcommand_go_db[i].code,map_code) == 0) {
				idx = i;
				break;
			}
		}
	}

	if(idx >= 0) {
		if(pc_setpos(sd, atcommand_go_db[idx].mapname, atcommand_go_db[idx].x, atcommand_go_db[idx].y, 3))
			clif_displaymessage(fd, msg_txt(38));
	} else {
		clif_displaymessage(fd, msg_txt(38));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_monster(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char name[100], monster[100];
	int mob_id = 0, number = 0, x = 0, y = 0;
	int i, count = 0, on_map = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	name[0] = '\0';

	if (sscanf(message, "%99s %d %d %d", monster, &number, &x, &y) < 1 &&
	    sscanf(message, "\"%99[^\"]\" %99s %d %d %d", name, monster, &number, &x, &y) < 2 &&
	    sscanf(message, "%99s \"%99[^\"]\" %d %d %d", monster, name, &number, &x, &y) < 2 &&
	    sscanf(message, "%99s %99s %d %d %d", name, monster, &number, &x, &y) < 2)
		return -1;

	if ((mob_id = atoi(monster)) == 0)
		mob_id = mobdb_searchname(monster);
	if (number <= 0)
		number = 1;
	if (!name[0])
		strcpy(name, "--ja--");
	// check for command @monster/@monstermap
	if (command == AtCommand_MonsterMap)
		on_map = 1;

	if (battle_config.etc_log) {
		printf("%cmonster %s name=%s id=%d count=%d ", command_symbol, monster, name, mob_id, number);
		if (on_map)
			printf("(on entire map)\n");
		else
			printf("(%d,%d)\n", x, y);
	}

	for (i = 0; i < number; i++) {
		int mx, my, j = 0;
		do {
			if (on_map) {
				mx = atn_rand() % (map[sd->bl.m].xs - 2) + 1;
				my = atn_rand() % (map[sd->bl.m].ys - 2) + 1;
			} else {
				if (x <= 0)
					mx = sd->bl.x + (atn_rand() % 10 - 5);
				else
					mx = x;
				if (y <= 0)
					my = sd->bl.y + (atn_rand() % 10 - 5);
				else
					my = y;
			}
		} while (map_getcell(sd->bl.m, mx, my, CELL_CHKNOPASS) && (++j) < 50);

		if (j >= 50) {
			mx = sd->bl.x;
			my = sd->bl.y;
		}
		if (mob_once_spawn(sd, sd->bl.m, mx, my, name, mob_id, 1, ""))
			count++;
	}
	if (count != 0)
		clif_displaymessage(fd, msg_txt(39));
	else
		clif_displaymessage(fd, msg_txt(40));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int atcommand_killmonster_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	int drop = va_arg(ap, int);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	if (drop)
		mob_damage(NULL, md, md->hp, 2);
	else
		unit_remove_map(&md->bl, 1, 0);

	return 0;
}

int atcommand_killmonster(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int map_id = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message) {
		map_id = sd->bl.m;
	} else {
		char map_name[100];
		sscanf(message, "%99s", map_name);
		if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) {
			strcat(map_name, ".gat");
		}
		if ((map_id = map_mapname2mapid(map_name)) < 0)
			map_id = sd->bl.m;
	}
	map_foreachinarea(atcommand_killmonster_sub, map_id, 0, 0,
		map[map_id].xs, map[map_id].ys, BL_MOB, (command == AtCommand_KillMonster));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_refine(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i, position, refine, current_position, current_refine;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &position, &refine) < 2)
		return -1;

	if (refine < -MAX_REFINE)
		refine = -MAX_REFINE;
	else if (refine > MAX_REFINE)
		refine = MAX_REFINE;
	else if (refine == 0)
		refine = 1;

	for (i = 0; i < MAX_INVENTORY; i++) {
		struct item *data = &sd->status.inventory[i];

		if (data->nameid == 0)
			continue;
		if (!data->equip)
			continue;
		if (position && !(data->equip & position))
			continue;
		current_refine = data->refine;
		data->refine += refine;
		if (data->refine > MAX_REFINE)
			data->refine = MAX_REFINE;
		else if (data->refine < 0)
			data->refine = 0;
		if (current_refine == data->refine)
			continue;
		current_position = data->equip;
		pc_unequipitem(sd, i, 0);
		clif_refine(fd, 0, i, data->refine);
		clif_delitem(sd, 3, i, 1);
		clif_additem(sd, i, 1, 0);
		pc_equipitem(sd, i, current_position);
		clif_misceffect(&sd->bl, 3);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_produce(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct item_data *item_data = NULL;
	char item_name[100];
	int item_id = 0, attribute = 0, star = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %d", item_name, &attribute, &star) < 1)
		return -1;

	if ((item_id = atoi(item_name)) == 0) {
		item_data = itemdb_searchname(item_name);
		if (item_data)
			item_id = item_data->nameid;
	} else {
		item_data = itemdb_exists(item_id);
	}

	if (item_data && (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid))) {
		struct item tmp_item;
		int flag;

		if (attribute < 0 || attribute > 4)
			attribute = 0;
		if (star < 0 || star > 3)
			star = 0;
		memset(&tmp_item, 0, sizeof tmp_item);
		tmp_item.nameid = item_id;
		tmp_item.amount = 1;
		tmp_item.identify = 1;
		tmp_item.card[0] = 0x00ff;
		tmp_item.card[1] = ((star * 5) << 8) + attribute;
		*((int *)(&tmp_item.card[2])) = sd->status.char_id;
		clif_produceeffect(sd, 0, item_id); // 製造エフェクトパケット
		clif_misceffect(&sd->bl, 3); // 他人にも成功を通知
		if ((flag = pc_additem(sd, &tmp_item, 1)))
			clif_additem(sd, 0, 0, flag);
	} else {
		clif_displaymessage(fd, msg_txt(192));
	}

	return 0;
}

/*==========================================
 * 壊れた武具を全て修理する
 *------------------------------------------
 */
int atcommand_repair(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i, count = 0;

	nullpo_retr(-1, sd);

	for (i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].nameid && sd->status.inventory[i].attribute) {
			sd->status.inventory[i].attribute = 0;
			clif_item_repaireffect(sd, 0, i);
			count++;
		}
	}
	if (count > 0) {
		clif_misceffect2(&sd->bl,101);
		clif_itemlist(sd);
		clif_equiplist(sd);
		clif_displaymessage(fd, msg_txt(157)); // 修理しました
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_memo(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int position;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	position = atoi(message);
	if (position < 0)
		position = 0;
	else if (position >= MAX_PORTAL_MEMO)
		position = MAX_PORTAL_MEMO - 1;
	pc_memo(sd, position);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_gat(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int y = 0;

	nullpo_retr(-1, sd);

	for (y = 2; y >= -2; y--) {
		msg_output(fd, "%s (x= %d, y= %d) %02X %02X %02X %02X %02X",
			map[sd->bl.m].name, sd->bl.x - 2, sd->bl.y + y,
			map_getcell(sd->bl.m, sd->bl.x - 2, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x - 1, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x,     sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x + 1, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x + 2, sd->bl.y + y, CELL_GETTYPE));
	}

	return 0;
}

/*==========================================
 * 指定パケットを折り返し送りつける（デバッグ）
 *------------------------------------------
 */
int atcommand_packet(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	clif_send_packet(sd,message);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_statuspoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int point;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (point > 0 || sd->status.status_point + point >= 0) {
		sd->status.status_point += point;
		clif_updatestatus(sd, SP_STATUSPOINT);
	} else {
		clif_displaymessage(fd, msg_txt(41));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_skillpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int point;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (point > 0 || sd->status.skill_point + point >= 0) {
		sd->status.skill_point += point;
		clif_updatestatus(sd, SP_SKILLPOINT);
	} else {
		clif_displaymessage(fd, msg_txt(41));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_zeny(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int zeny;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	zeny = atoi(message);
	if (zeny > 0 && zeny > MAX_ZENY - sd->status.zeny)
		zeny = MAX_ZENY - sd->status.zeny;
	else if (zeny < 0 && sd->status.zeny + zeny < 0)
		zeny = sd->status.zeny * (-1);

	if (zeny == 0) {
		clif_displaymessage(fd, msg_txt(41));
	} else {
		sd->status.zeny += zeny;
		clif_updatestatus(sd, SP_ZENY);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_param(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int max, value, new_value;
	short *status = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	value = atoi(message);
	switch (command) {
		case AtCommand_Strength:
			status = &sd->status.str;
			break;
		case AtCommand_Agility:
			status = &sd->status.agi;
			break;
		case AtCommand_Vitality:
			status = &sd->status.vit;
			break;
		case AtCommand_Intelligence:
			status = &sd->status.int_;
			break;
		case AtCommand_Dexterity:
			status = &sd->status.dex;
			break;
		case AtCommand_Luck:
			status = &sd->status.luk;
			break;
		default:
			break;
	}
	if (status == NULL)
		return -1;

	if(pc_is3rdclass(sd) && pc_isbaby(sd))
		max = battle_config.third_baby_status_max;
	else if(pc_is3rdclass(sd))
		max = battle_config.third_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV && pc_isbaby(sd))
		max = battle_config.esnv_baby_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV)
		max = battle_config.esnv_status_max;
	else if(sd->status.class_ == PC_CLASS_KG || sd->status.class_ == PC_CLASS_OB)
		max = battle_config.ko_status_max;
	else if(sd->status.class_ == PC_CLASS_RL)
		max = battle_config.rl_status_max;
	else if(sd->status.class_ == PC_CLASS_SUM)
		max = battle_config.sum_status_max;
	else if(pc_isbaby(sd))
		max = battle_config.baby_status_max;
	else
		max = battle_config.max_parameter;

	new_value = *status + value;
	if (new_value < 1)
		value = 1 - *status;
	if (new_value > max)
		value = max - *status;
	*status += value;

	clif_updatestatus(sd, SP_STR + command - AtCommand_Strength);
	clif_updatestatus(sd, SP_USTR + command - AtCommand_Strength);
	status_calc_pc(sd, 0);
	clif_displaymessage(fd, msg_txt(42));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_guildlevelup(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int level = 0;
	struct guild *g = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	level = atoi(message);
	if (sd->status.guild_id <= 0 ||
	    (g = guild_search(sd->status.guild_id)) == NULL) {
		clif_displaymessage(fd, msg_txt(43));
		return 0;
	}
	if (strcmp(sd->status.name, g->master) != 0) {
		clif_displaymessage(fd, msg_txt(44));
		return 0;
	}

	if (g->guild_lv + level >= 1 && g->guild_lv + level <= MAX_GUILDLEVEL) {
		intif_guild_change_basicinfo(g->guild_id, GBI_GUILDLV, &level, 2);
	} else {
		clif_displaymessage(fd, msg_txt(41));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_guildskillpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int point = 0;
	struct guild *g = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (sd->status.guild_id <= 0 ||
	    (g = guild_search(sd->status.guild_id)) == NULL) {
		clif_displaymessage(fd, msg_txt(43));
		return 0;
	}
	if (strcmp(sd->status.name, g->master) != 0) {
		clif_displaymessage(fd, msg_txt(44));
		return 0;
	}

	if (point > 0 || g->skill_point + point >= 0) {
		intif_guild_change_basicinfo(g->guild_id, GBI_SKILLPOINT, &point, sizeof(point));
	} else {
		clif_displaymessage(fd, msg_txt(41));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_makepet(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct pet_db *db;
	int id = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((id = atoi(message)) == 0)
		 id = mobdb_searchname(message);
	db = pet_search_data(id, PET_CLASS);
	if (!db)
		db = pet_search_data(id, PET_EGG);
	if (db) {
		sd->catch_target_class = db->class_;
		intif_create_pet(
			sd->status.account_id, sd->status.char_id, db->class_, mobdb_search(db->class_)->lv,
		    db->EggID, 0, db->intimate, 100, 0, 1, db->jname
		);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_hatch(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.pet_id > 0)
		return -1;

	clif_sendegg(sd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_petfriendly(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int friendly;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	friendly = atoi(message);
	if (sd->status.pet_id > 0 && sd->pd) {
		int t = sd->pet.intimate;
		sd->pet.intimate = friendly;
		if (sd->pet.intimate < 0)
			sd->pet.intimate = 0;
		else if (sd->pet.intimate > 1000)
			sd->pet.intimate = 1000;
		clif_send_petstatus(sd);
		if (battle_config.pet_status_support) {
			if ((sd->pet.intimate > 0 && t <= 0) ||
			    (sd->pet.intimate <= 0 && t > 0)) {
				if (sd->bl.prev != NULL)
					status_calc_pc(sd, 0);
				else
					status_calc_pc(sd, 2);
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_pethungry(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int hungry;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sd->status.pet_id <= 0 || sd->pd == NULL)
		return -1;

	hungry = atoi(message);
	sd->pet.hungry = hungry;
	if (sd->pet.hungry < 0)
		sd->pet.hungry = 0;
	else if (sd->pet.hungry > 100)
		sd->pet.hungry = 100;
	clif_send_petstatus(sd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_petrename(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.pet_id <= 0 || sd->pd == NULL)
		return -1;

	sd->pet.rename_flag = 0;
	intif_save_petdata(sd->status.account_id, &sd->pet);
	clif_send_petstatus(sd);
	clif_displaymessage(fd, msg_txt(123));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charpetrename(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pl_sd->status.pet_id <= 0 || pl_sd->pd == NULL)
			return -1;
		if (pl_sd->pet.rename_flag == 0)
			return -1;
		pl_sd->pet.rename_flag = 0;
		intif_save_petdata(pl_sd->status.account_id, &pl_sd->pet);
		clif_send_petstatus(pl_sd);
		clif_displaymessage(fd, msg_txt(123));
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_recall(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;
	if (strlen(character) > 23 || strncmp(sd->status.name, character, 24) == 0)
		return -1;

	intif_charmovereq(sd,character,1);

	return 0;
}

/*==========================================
 * recallを接続者全員にかける
 *------------------------------------------
 */
int atcommand_recallall(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] &&
		    (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth &&
		    sd->status.account_id != pl_sd->status.account_id &&
		    pc_isGM(sd) >= pc_isGM(pl_sd))
		{
			pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
			//intif_charmovereq(sd,pl_sd->status.name,1);
		}
	}
	clif_displaymessage(fd, msg_txt(105));

	return 0;
}

/*==========================================
 * Recall online characters of a guild to your location
 *------------------------------------------
 */
int atcommand_recallguild(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char guild_name[100];
	struct map_session_data *pl_sd;
	struct guild *g;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", guild_name) < 1)
		return -1;

	if ((g = guild_searchname(guild_name)) != NULL || (g = guild_search(atoi(message))) != NULL) {
		int i;
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth &&
			    sd->status.account_id != pl_sd->status.account_id &&
			    pl_sd->status.guild_id == g->guild_id)
				pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
		}
		msg_output(fd, msg_txt(106), g->name);
	} else {
		clif_displaymessage(fd, msg_txt(107));
	}

	return 0;
}

/*==========================================
 * Recall online characters of a party to your location
 *------------------------------------------
 */
int atcommand_recallparty(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char party_name[100];
	struct map_session_data *pl_sd;
	struct party *p;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", party_name) < 1)
		return -1;

	if ((p = party_searchname(party_name)) != NULL || (p = party_search(atoi(message))) != NULL) {
		int i;
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth &&
			    sd->status.account_id != pl_sd->status.account_id &&
			    pl_sd->status.party_id == p->party_id)
				pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
		}
		msg_output(fd, msg_txt(108), p->name);
	} else {
		clif_displaymessage(fd, msg_txt(109));
	}

	return 0;
}

/*==========================================
 * 対象キャラクターを転職させる upper指定で転生や養子も可能
 *------------------------------------------
 */
int atcommand_character_job(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data* pl_sd;
	int job, upper;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%d %d %99[^\n]", &job, &upper, character) < 3) {	// upper指定してあるか
		upper = -1;
		if (sscanf(message, "%d %99[^\n]", &job, character) < 2)	// upper指定してない上に何か足りない
			return -1;
	}

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			if ((job >= 0 && job < PC_JOB_MAX)) {
				pc_jobchange(pl_sd, job, upper);
				clif_displaymessage(fd, msg_txt(48));
			} else {
				clif_displaymessage(fd, msg_txt(49));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_revive(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		pl_sd->status.hp = pl_sd->status.max_hp;
		pc_setstand(pl_sd);
		if (battle_config.pc_invincible_time > 0)
			pc_setinvincibletimer(sd, battle_config.pc_invincible_time);
		clif_updatestatus(pl_sd, SP_HP);
		clif_updatestatus(pl_sd, SP_SP);
		clif_resurrection(&pl_sd->bl, 1);
		clif_displaymessage(fd, msg_txt(51));
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_character_stats(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd = NULL;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		msg_output(fd, msg_txt(53),  pl_sd->status.name);
		msg_output(fd, msg_txt(158), pl_sd->status.base_level);
		msg_output(fd, msg_txt(159), pl_sd->status.job_level);
		msg_output(fd, msg_txt(160), pl_sd->status.hp);
		msg_output(fd, msg_txt(161), pl_sd->status.max_hp);
		msg_output(fd, msg_txt(162), pl_sd->status.sp);
		msg_output(fd, msg_txt(163), pl_sd->status.max_sp);
		msg_output(fd, msg_txt(164), pl_sd->status.str);
		msg_output(fd, msg_txt(165), pl_sd->status.agi);
		msg_output(fd, msg_txt(166), pl_sd->status.vit);
		msg_output(fd, msg_txt(167), pl_sd->status.int_);
		msg_output(fd, msg_txt(168), pl_sd->status.dex);
		msg_output(fd, msg_txt(169), pl_sd->status.luk);
		msg_output(fd, msg_txt(170), pl_sd->status.zeny);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_character_option(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	unsigned short opt1, opt2;
	unsigned int opt3, option;
	struct map_session_data* pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%hu %hu %u %u %99[^\n]", &opt1, &opt2, &option, &opt3, character) < 5)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pl_sd->sc.opt1 = opt1;
			pl_sd->sc.opt2 = opt2;
			pl_sd->sc.opt3 = opt3;
			clif_changeoption2(&pl_sd->bl);
			pc_setoption(pl_sd, option);
			clif_displaymessage(fd, msg_txt(55));
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_character_save(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char map_name[100];
	char character[100];
	struct map_session_data* pl_sd;
	int x, y;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %d %d %99[^\n]", map_name, &x, &y, character) < 4)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			int m;

			if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) {
				strcat(map_name, ".gat");
			}
			m = map_mapname2mapid(map_name);
			if (x < 0 || y < 0 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys))) {
				clif_displaymessage(fd, msg_txt(2));
			} else {
				pc_setsavepoint(pl_sd, map_name, x, y);
				clif_displaymessage(fd, msg_txt(57));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_night(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
			//clif_status_load_id(pl_sd,SI_MIRACLE,1);
			clif_displaymessage(pl_sd->fd, msg_txt(59));
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_day(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
			//clif_status_load_id(pl_sd,SI_MIRACLE,0);
			clif_displaymessage(pl_sd->fd, msg_txt(60));
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_doom(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth && pc_isGM(sd) >= pc_isGM(pl_sd))
		{
			if (command == AtCommand_DoomMap && sd->bl.m != pl_sd->bl.m)
				continue;

			pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
			clif_displaymessage(pl_sd->fd, msg_txt(61));
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_raise(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth && unit_isdead(&pl_sd->bl))
		{
			if (command == AtCommand_RaiseMap && sd->bl.m != pl_sd->bl.m)
				continue;

			pl_sd->status.hp = pl_sd->status.max_hp;
			pl_sd->status.sp = pl_sd->status.max_sp;
			pc_setstand(pl_sd);
			clif_updatestatus(pl_sd, SP_HP);
			clif_updatestatus(pl_sd, SP_SP);
			clif_resurrection(&pl_sd->bl, 1);
			clif_displaymessage(pl_sd->fd, msg_txt(63));
		}
	}
	clif_displaymessage(fd, msg_txt(64));

	return 0;
}

/*==========================================
 * atcommand_character_baselevel @charbaselvlで対象キャラのレベルを上げる
 *------------------------------------------
*/
int atcommand_character_baselevel(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	char character[100];
	int level = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &level, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			if (level > 0) {
				int i;
				if (pl_sd->status.base_level + level > MAX_LEVEL)
					level = MAX_LEVEL - (int)pl_sd->status.base_level;
				if (level <= 0)
					return -1;
				for (i = 1; i <= level; i++)
					pl_sd->status.status_point += (pl_sd->status.base_level + i + 14) / 5;
				pl_sd->status.base_level += level;
				clif_updatestatus(pl_sd, SP_BASELEVEL);
				clif_updatestatus(pl_sd, SP_NEXTBASEEXP);
				clif_updatestatus(pl_sd, SP_STATUSPOINT);
				status_calc_pc(pl_sd, 0);
				pc_heal(pl_sd, pl_sd->status.max_hp, pl_sd->status.max_sp);
				clif_misceffect(&pl_sd->bl, 0);
				clif_displaymessage(fd, msg_txt(65));
			} else if (level < 0) {
				if ((int)pl_sd->status.base_level + level <= 0)
					level = 1 - (int)pl_sd->status.base_level;
				if (level >= 0)
					return -1;
				pl_sd->status.base_level += level;
				clif_updatestatus(pl_sd, SP_BASELEVEL);
				clif_updatestatus(pl_sd, SP_NEXTBASEEXP);
				status_calc_pc(pl_sd, 0);
				clif_displaymessage(fd, msg_txt(66));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * atcommand_character_joblevel @charjoblvlで対象キャラのJobレベルを上げる
 *------------------------------------------
 */
int atcommand_character_joblevel(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	char character[100];
	int level = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &level, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			int max_level = max_job_table[pl_sd->s_class.upper][pl_sd->s_class.job];
			if (pl_sd->status.job_level == max_level && level > 0) {
				clif_displaymessage(fd, msg_txt(23));
			} else if (level >= 1) {
				if (pl_sd->status.job_level + level > max_level)
					level = max_level - pl_sd->status.job_level;
				pl_sd->status.job_level += level;
				clif_updatestatus(pl_sd, SP_JOBLEVEL);
				clif_updatestatus(pl_sd, SP_NEXTJOBEXP);
				pl_sd->status.skill_point += level;
				clif_updatestatus(pl_sd, SP_SKILLPOINT);
				status_calc_pc(pl_sd, 0);
				clif_misceffect(&pl_sd->bl, 1);
				clif_displaymessage(fd, msg_txt(68));
			} else if (level < 0 && sd->status.job_level + level > 0) {
				pl_sd->status.job_level += level;
				clif_updatestatus(pl_sd, SP_JOBLEVEL);
				clif_updatestatus(pl_sd, SP_NEXTJOBEXP);
				status_calc_pc(pl_sd, 0);
				clif_displaymessage(fd, msg_txt(69));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_kick(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return 0;
	}

	if (pc_isGM(sd) >= pc_isGM(pl_sd))
		clif_GM_kick(sd, pl_sd, 1);
	else
		clif_GM_kickack(sd, 0);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_kickall(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
			if (sd->status.account_id != pl_sd->status.account_id)
				clif_GM_kick(sd, pl_sd, 0);
		}
	}
	clif_GM_kick(sd, sd, 0);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_allskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int flag = 0;

	nullpo_retr(-1, sd);

	if (message && *message)
		flag = atoi(message);

	pc_allskillup(sd,flag);
	clif_displaymessage(fd, msg_txt(76));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_questskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int skill_id;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	skill_id = atoi(message);
	if (skill_get_inf2(skill_id) & INF2_QUEST) {
		pc_skill(sd, skill_id, 1, 0);
		clif_displaymessage(fd, msg_txt(70));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charquestskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;
	int skill_id;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &skill_id, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (skill_get_inf2(skill_id) & INF2_QUEST && pc_checkskill2(pl_sd, skill_id) == 0) {
			pc_skill(pl_sd, skill_id, 1, 0);
			msg_output(fd, msg_txt(110), pl_sd->status.name);
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_lostskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int skill_id = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	skill_id = atoi(message);
	if (skill_get_inf2(skill_id) & INF2_QUEST && pc_checkskill2(sd, skill_id) > 0) {
		sd->status.skill[skill_id].lv   = 0;
		sd->status.skill[skill_id].flag = 0;
		clif_skillinfoblock(sd);
		clif_displaymessage(fd, msg_txt(71));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charlostskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;
	int skill_id;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &skill_id, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (skill_get_inf2(skill_id) & INF2_QUEST && pc_checkskill2(pl_sd, skill_id) > 0) {
			pl_sd->status.skill[skill_id].lv   = 0;
			pl_sd->status.skill[skill_id].flag = 0;
			clif_skillinfoblock(pl_sd);
			msg_output(fd, msg_txt(111), pl_sd->status.name);
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_spiritball(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int number;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	number = atoi(message);
	if (number >= 0 && number <= 0x7FFF) {
		if (sd->spiritball.num > 0)
			pc_delspiritball(sd, sd->spiritball.num, 1);
		sd->spiritball.num = number;
		clif_spiritball(sd);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_party(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char party_name[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", party_name) < 1)
		return -1;

	party_create(sd, party_name, 0, 0);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_partyoption(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int exp_flag, item_flag, item2_flag;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%d %d %d", &exp_flag, &item_flag, &item2_flag) < 3)
		return -1;

	party_changeoption(sd, exp_flag&1, (item_flag ? 1 : 0) | (item2_flag ? 2 : 0));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_guild(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char guild_name[100];
	int prev;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", guild_name) < 1)
		return -1;

	prev = battle_config.guild_emperium_check;
	battle_config.guild_emperium_check = 0;
	guild_create(sd, guild_name);
	battle_config.guild_emperium_check = prev;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_agitstart(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	if (agit_flag) {
		clif_displaymessage(fd, msg_txt(73));
	} else {
		agit_flag = 1;
		guild_agit_start();
		clif_displaymessage(fd, msg_txt(72));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_agitend(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	if (!agit_flag) {
		clif_displaymessage(fd, msg_txt(75));
	} else {
		agit_flag = 0;
		guild_agit_end();
		clif_displaymessage(fd, msg_txt(74));
	}

	return 0;
}

/*==========================================
 * マップサーバーを終了させる
 *------------------------------------------
 */
int atcommand_mapexit(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	exit(1);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int atcommand_idsearch_sub(void *key, void *data, va_list ap)
{
	struct item_data *item = (struct item_data *)data;
	char *str  = va_arg(ap,char *);
	int fd     = va_arg(ap,int);

	if (strstr(item->jname, str)) {
		char slot[16] = "";
		if (item->slot > 0) {
			sprintf(slot, " [%d]", item->slot);
		}
		msg_output(fd, msg_txt(78), item->jname, slot, item->nameid);	// "%s%s : %d"
		return 1;
	}
	return 0;
}

int atcommand_idsearch(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char item_name[100];
	int match;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", item_name) < 1)
		return -1;

	msg_output(fd, msg_txt(77), item_name);

	match = itemdb_idsearch(fd, item_name, atcommand_idsearch_sub);
	msg_output(fd, msg_txt(79), match);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_itemidentify(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].amount && sd->status.inventory[i].identify == 0)
			pc_item_identify(sd, i);
	}
	clif_displaymessage(fd, msg_txt(80));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int atcommand_shuffle_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	mob_warp(md, md->bl.m, -1, -1, 3);

	return 0;
}

int atcommand_shuffle(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int mode;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	mode = atoi(message)+1;

	if (mode&1) {	// PCのシャッフル
		struct map_session_data *pl_sd;
		int i;
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
			    pl_sd->state.auth && sd->bl.m == pl_sd->bl.m && pc_isGM(sd) >= pc_isGM(pl_sd))
				pc_setpos(pl_sd, map[pl_sd->bl.m].name, 0, 0, 3);
		}
	}
	if (mode&2) {	// MOBのシャッフル
		map_foreachinarea(atcommand_shuffle_sub, sd->bl.m, 0, 0, map[sd->bl.m].xs, map[sd->bl.m].ys, BL_MOB);
	}
	clif_displaymessage(fd, msg_txt(81));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_maintenance(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	if (!message || !*message)
		return -1;

	chrif_maintenance(atoi(message));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_misceffect(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int effno = 0, id = 0;
	struct block_list *bl = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &effno, &id) < 1)
		return -1;

	if (id > 0)
		bl = map_id2bl(id);
	if (bl == NULL || bl->prev == NULL)
		bl = &sd->bl;

	clif_misceffect2(bl,effno);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_summon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mob_name[100];
	int mob_id = 0;
	int x, y, id;
	struct mob_data *md;
	unsigned int tick = gettick();

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s", mob_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if (mob_id == 0)
		return -1;

	x = sd->bl.x + (atn_rand() % 10 - 5);
	y = sd->bl.y + (atn_rand() % 10 - 5);

	id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, mob_id, 1, "");
	if ((md = map_id2md(id)) != NULL) {
		md->state.special_mob_ai = 1;
		md->master_id   = sd->bl.id;
		md->mode        = mobdb_search(md->class_)->mode | MD_AGGRESSIVE;
		md->deletetimer = add_timer(tick+60000,mob_timer_delete,id,NULL);
		clif_misceffect2(&md->bl,344);
	}
	clif_skill_poseffect(&sd->bl,AM_CALLHOMUN,1,x,y,tick);

	return 0;
}

/*==========================================
 * Character Skill Reset
 *------------------------------------------
 */
int atcommand_charskreset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) < pc_isGM(pl_sd))
			return -1;
		pc_resetskill(pl_sd, -1);
		msg_output(fd, msg_txt(99), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * Character Stat Reset
 *------------------------------------------
 */
int atcommand_charstreset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) < pc_isGM(pl_sd))
			return -1;
		pc_resetstate(pl_sd);
		msg_output(fd, msg_txt(100), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * Character Reset
 *------------------------------------------
 */
int atcommand_charreset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) < pc_isGM(pl_sd))
			return -1;
		pc_resetstate(pl_sd);
		pc_resetskill(pl_sd, -1);
		msg_output(fd, msg_txt(101), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * Character Status Point (rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charstpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	int point = 0;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &point, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		int new_status_point = (int)pl_sd->status.status_point + point;

		if (point > 0 && (point > 0x7FFF || new_status_point > 0x7FFF)) // fix positiv overflow
			new_status_point = 0x7FFF;
		else if (point < 0 && (point < -0x7FFF || new_status_point < 0)) // fix negativ overflow
			new_status_point = 0;
		if (new_status_point == (int)pl_sd->status.status_point)
			return -1;
		pl_sd->status.status_point = new_status_point;
		clif_updatestatus(pl_sd, SP_STATUSPOINT);
		msg_output(fd, msg_txt(102), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * Character Skill Point (Rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charskpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	int point = 0;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &point, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		int new_skill_point = (int)pl_sd->status.skill_point + point;

		if (point > 0 && (point > 0x7FFF || new_skill_point > 0x7FFF)) // fix positiv overflow
			new_skill_point = 0x7FFF;
		else if (point < 0 && (point < -0x7FFF || new_skill_point < 0)) // fix negativ overflow
			new_skill_point = 0;
		if (new_skill_point == (int)pl_sd->status.skill_point)
			return -1;
		pl_sd->status.skill_point = new_skill_point;
		clif_updatestatus(pl_sd, SP_SKILLPOINT);
		msg_output(fd, msg_txt(103), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * Character Zeny Point (Rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charzeny(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	int zeny = 0;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &zeny, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		int new_zeny = pl_sd->status.zeny + zeny;

		if (zeny > 0 && (zeny > MAX_ZENY || new_zeny > MAX_ZENY)) // fix positiv overflow
			new_zeny = MAX_ZENY;
		else if (zeny < 0 && (zeny < -MAX_ZENY || new_zeny < 0)) // fix negativ overflow
			new_zeny = 0;
		if (new_zeny == pl_sd->status.zeny)
			return -1;
		pl_sd->status.zeny = new_zeny;
		clif_updatestatus(pl_sd, SP_ZENY);
		msg_output(fd, msg_txt(104), character);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * @mapinfo <map name> [0-3] by MC_Cameri
 * => Shows information about the map [map name]
 * 0 = 追加情報なし
 * 1 = MAP内に居るPCの情報
 * 2 = MAP内に居るNPCの情報（接触型のみ）
 * 3 = MAP内にあるチャットの情報
 *------------------------------------------
 */
int atcommand_mapinfo(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	struct chat_data *cd = NULL;
	char map_name[100] = "";
	int m_id, i, chat_num, list = 0;

	nullpo_retr(-1, sd);

	if (message && *message) {
		sscanf(message, "%d %99s", &list, map_name);
		if (list < 0 || list > 3)
			return -1;
	}

	if (map_name[0] == '\0')
		strcpy(map_name, sd->mapname);
	if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) // 16 - 4 (.gat)
		strcat(map_name, ".gat");

	if ((m_id = map_mapname2mapid(map_name)) < 0)
		return -1;

	clif_displaymessage(fd, "------ Map Info ------");
	msg_output(fd, "Map Name: %s", map_name);
	msg_output(fd, "Players In Map: %d", map[m_id].users);
	msg_output(fd, "NPCs In Map: %d", map[m_id].npc_num);

	for (i=chat_num=0; i<fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth && (cd = map_id2cd(pl_sd->chatID)) != NULL)
			chat_num++;
	}

	msg_output(fd, "Chats In Map: %d", chat_num);
	clif_displaymessage(fd, "------ Map Flags ------");

	msg_output(fd, "Player vs Player: %s | No Guild: %s | No Party: %s",
		(map[m_id].flag.pvp) ? "True" : "False",
		(map[m_id].flag.pvp_noguild) ? "True" : "False",
		(map[m_id].flag.pvp_noparty) ? "True" : "False");
	msg_output(fd, "Guild vs Guild: %s | No Party: %s",
		(map[m_id].flag.gvg) ? "True" : "False",
		(map[m_id].flag.gvg_noparty) ? "True" : "False");

	msg_output(fd, "Town: %s", (map[m_id].flag.town) ? "True" : "False");
	msg_output(fd, "No Dead Branch: %s", (map[m_id].flag.nobranch) ? "True" : "False");
	msg_output(fd, "No Memo: %s", (map[m_id].flag.nomemo) ? "True" : "False");
	msg_output(fd, "No Penalty: %s", (map[m_id].flag.nopenalty) ? "True" : "False");
	msg_output(fd, "No Return: %s", (map[m_id].flag.noreturn) ? "True" : "False");
	msg_output(fd, "No Save: %s", (map[m_id].flag.nosave) ? "True" : "False");
	msg_output(fd, "No Teleport: %s", (map[m_id].flag.noteleport) ? "True" : "False");
	msg_output(fd, "No Portal: %s", (map[m_id].flag.noportal) ? "True" : "False");
	msg_output(fd, "No Monster Teleport: %s", (map[m_id].flag.monster_noteleport) ? "True" : "False");
	msg_output(fd, "No Zeny Penalty: %s", (map[m_id].flag.nozenypenalty) ? "True" : "False");
	msg_output(fd, "No IceWall: %s", (map[m_id].flag.noicewall) ? "True" : "False");
	msg_output(fd, "PK: %s", (map[m_id].flag.pk) ? "True" : "False");

	switch (list) {
		case 0:
			// Do nothing. It's list 0, no additional display.
			break;
		case 1:
			clif_displaymessage(fd, "----- Players in Map -----");
			for (i = 0; i < fd_max; i++) {
				if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
				    pl_sd->state.auth && strcmp(pl_sd->mapname, map_name) == 0)
				{
					msg_output(fd, "Player '%s' (session #%d) | Location: %d,%d",
						pl_sd->status.name, i, pl_sd->bl.x, pl_sd->bl.y);
				}
			}
			break;
		case 2:
			clif_displaymessage(fd, "----- NPCs in Map -----");
			for (i = 0; i < map[m_id].npc_num; i++) {	// map[].npcには接触型のNPCしか保存されていない（手抜き）
				const char *direction;
				struct npc_data *nd = map[m_id].npc[i];

				switch (nd->dir) {
					case 0:  direction = "North";      break;
					case 1:  direction = "North West"; break;
					case 2:  direction = "West";       break;
					case 3:  direction = "South West"; break;
					case 4:  direction = "South";      break;
					case 5:  direction = "South East"; break;
					case 6:  direction = "East";       break;
					case 7:  direction = "North East"; break;
					case 9:  direction = "North";      break;
					default: direction = "Unknown";    break;
				}
				msg_output(fd, "NPC %d: %s | Direction: %s | Sprite: %d | Location: %d %d",
				        i+1, nd->name, direction, nd->class_, nd->bl.x, nd->bl.y);
			}
			break;
		case 3:
			clif_displaymessage(fd, "----- Chats in Map -----");
			for (i = 0; i < fd_max; i++) {
				if (session[i] &&
				    (pl_sd = (struct map_session_data *)session[i]->session_data) &&
				    pl_sd->state.auth &&
				    (cd = map_id2cd(pl_sd->chatID)) &&
				    strcmp(pl_sd->mapname, map_name) == 0 &&
				    cd->usersd[0] == pl_sd)
				{
					msg_output(fd, "Chat %d: %s | Player: %s | Location: %d %d",
							i, cd->title, pl_sd->status.name, cd->bl.x, cd->bl.y);
					msg_output(fd, "   Users: %d/%d | Password: %8s | Public: %s",
							cd->users, cd->limit, cd->pass, (cd->pub) ? "Yes" : "No");
				}
			}
			break;
	}

	return 0;
}

/*==========================================
 * Mob search
 *------------------------------------------
 */
static int atcommand_mobsearch_sub(struct block_list *bl,va_list ap)
{
	int mob_id, fd;
	int *number;
	struct mob_data *md;

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	mob_id = va_arg(ap,int);
	fd     = va_arg(ap,const int);
	number = va_arg(ap,int *);

	switch (mob_id) {
		case -1:
			break;
		case -2:
			if ( !(status_get_mode(&md->bl)&MD_BOSS) )
				return 0;
			break;
		case -3:
			if ( !(status_get_mode(&md->bl)&MD_BOSS) || mobdb_search(md->class_)->mexp <= 0 )
				return 0;
			break;
		default:
			if ( md->class_ != mob_id )
				return 0;
			break;
	}
	msg_output(fd, msg_txt(94), ++(*number), md->bl.x, md->bl.y, md->name);

	return 0;
}

int atcommand_mobsearch(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mob_name[100], map_name[100] = "";
	const char *p;
	int mob_id, map_id = 0, number = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %99s", mob_name, map_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if (mob_id != -1 && mob_id != -2 && mob_id != -3 && !mobdb_exists(mob_id)) {
		msg_output(fd, msg_txt(93), mob_name);
		return 0;
	}

	if (mob_id == -1)
		p = msg_txt(153); // all
	else if (mob_id == -2 || mob_id == -3)
		p = msg_txt(154); // boss
	else if (mob_id > 0 && mob_id == atoi(mob_name) && mobdb_search(mob_id)->jname[0])
		p = mobdb_search(mob_id)->jname; // --ja--
	else
		p = mob_name;

	if ((map_id = map_mapname2mapid(map_name)) < 0)
		map_id = sd->bl.m;

	msg_output(fd, msg_txt(92), p, map[map_id].name);

	map_foreachinarea(atcommand_mobsearch_sub, map_id, 0, 0, map[map_id].xs, map[map_id].ys, BL_MOB, mob_id, fd, &number);

	return 0;
}

/*==========================================
 * ドロップアイテムの掃除
 *------------------------------------------
 */
static int atcommand_cleanmap_sub(struct block_list *bl,va_list ap)
{
	struct flooritem_data *fitem = NULL;

	nullpo_retr(0, bl);
	nullpo_retr(0, fitem = (struct flooritem_data *)bl);

	delete_timer(fitem->cleartimer,map_clearflooritem_timer);
	if (fitem->item_data.card[0] == (short)0xff00)
		intif_delete_petdata(*((int *)(&fitem->item_data.card[1])));
	clif_clearflooritem(fitem,-1);
	map_delobject(fitem->bl.id);

	return 0;
}

int atcommand_cleanmap(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	map_foreachinarea(atcommand_cleanmap_sub, sd->bl.m, sd->bl.x-AREA_SIZE*2,sd->bl. y-AREA_SIZE*2,
		sd->bl.x+AREA_SIZE*2, sd->bl.y+AREA_SIZE*2, BL_ITEM);
	clif_displaymessage(fd, msg_txt(95));

	return 0;
}

/*==========================================
 * Clock
 *------------------------------------------
 */
int atcommand_clock(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct tm *tm;
	time_t t;

	t = time(NULL);
	tm = localtime(&t);

	msg_output(fd, msg_txt(96), tm->tm_hour, tm->tm_min, tm->tm_sec);

	return 0;
}

/*==========================================
 * Give Item
 * @giveitem (item_id or item_name) amount charname
 *------------------------------------------
 */
static void atcommand_giveitem_sub(struct map_session_data *sd,struct item_data *item_data,int number)
{
	int i, flag;
	int loop = 1, get_count = number;
	struct item item_tmp;

	nullpo_retv(sd);
	nullpo_retv(item_data);

	if (itemdb_isequip2(item_data)) {
		loop = number;
		get_count = 1;
	}
	for (i = 0; i < loop; i++) {
		memset(&item_tmp, 0, sizeof(item_tmp));
		item_tmp.nameid = item_data->nameid;
		item_tmp.identify = 1;
		if ((flag = pc_additem(sd, &item_tmp, get_count)))
			clif_additem(sd, 0, 0, flag);
	}

	return;
}

int atcommand_giveitem(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	struct item_data *item_data = NULL;
	char item_name[100], character[100];
	int number, item_id;

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %99[^\n]", item_name, &number, character) < 3)
		return -1;

	if (number <= 0)
		number = 1;

	item_id = atoi(item_name);
	if (item_id < 0)
		item_id = itemdb_searchrandomid(-item_id);

	if (item_id > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(item_name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}
	if (item_id <= 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) { // 該当名のキャラが存在する
		atcommand_giveitem_sub(pl_sd,item_data,number);
		msg_output(pl_sd->fd, msg_txt(97), item_data->jname, number);
		msg_output(fd, msg_txt(98), pl_sd->status.name, item_data->jname, number);
	} else if (strcmp(character,"ALL") == 0) {	// 名前がALLなら、接続者全員へ
		int i;
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
				atcommand_giveitem_sub(pl_sd,item_data,number);
				msg_output(pl_sd->fd, msg_txt(97), item_data->jname, number);
			}
		}
		msg_output(fd, msg_txt(98), msg_txt(135), item_data->jname, number);
	} else {
		return -1;
	}

	return 0;
}

/*==========================================
 * Weather control
 * 発動後に効果を戻す(消す)方法が分からない・・・
 *------------------------------------------
 */
int atcommand_weather(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int type, m = -1, effno = -1;
	char weather[100], map_name[100] = "";

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %99s", weather, map_name) < 1)
		return -1;

	if (map_name[0]) {
		if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13)
			strcat(map_name, ".gat");
		m = map_mapname2mapid(map_name);
	}
	if (m < 0)
		m = sd->bl.m;

	type = atoi(weather);
	if (type == 0 && strcmp(weather, "0") != 0) {
		if (!strcmp(weather,"day"))
			type = 0;
		else if (!strcmp(weather,"rain"))
			type = 1;
		else if (!strcmp(weather,"snow"))
			type = 2;
		else if (!strcmp(weather,"sakura"))
			type = 3;
		else if (!strcmp(weather,"fog"))
			type = 4;
		else if (!strcmp(weather,"leaves"))
			type = 5;
		else if (!strcmp(weather,"fireworks"))
			type = 6;
		else if (!strcmp(weather,"cloud1"))
			type = 7;
		else if (!strcmp(weather,"cloud2"))
			type = 8;
		else if (!strcmp(weather,"cloud3"))
			type = 9;
		else
			return -1;
	}

	switch(type) {
		case 0:
			if (map[m].flag.rain) {
				effno = 410;
			}
			map[m].flag.rain      = 0;
			map[m].flag.snow      = 0;
			map[m].flag.sakura    = 0;
			map[m].flag.fog       = 0;
			map[m].flag.leaves    = 0;
			map[m].flag.fireworks = 0;
			map[m].flag.cloud1    = 0;
			map[m].flag.cloud2    = 0;
			map[m].flag.cloud3    = 0;
			clif_displaymessage(fd, msg_txt(112));
			break;
		case 1:
			if (!map[m].flag.rain) {
				effno = 161;
				map[m].flag.rain = 1;
				clif_displaymessage(fd, msg_txt(84));
			} else {
				map[m].flag.rain = 0;
			}
			break;
		case 2:
			if (!map[m].flag.snow) {
				effno = 162;
				map[m].flag.snow = 1;
				clif_displaymessage(fd, msg_txt(85));
			} else {
				map[m].flag.snow = 0;
			}
			break;
		case 3:
			if (!map[m].flag.sakura) {
				effno = 163;
				map[m].flag.sakura = 1;
				clif_displaymessage(fd, msg_txt(86));
			} else {
				map[m].flag.sakura = 0;
			}
			break;
		case 4:
			if (!map[m].flag.fog) {
				effno = 515;
				map[m].flag.fog = 1;
				clif_displaymessage(fd, msg_txt(87));
			} else {
				map[m].flag.fog = 0;
			}
			break;
		case 5:
			if (!map[m].flag.leaves) {
				effno = 333;
				map[m].flag.leaves = 1;
				clif_displaymessage(fd, msg_txt(88));
			} else {
				map[m].flag.leaves = 0;
			}
			break;
		case 6:
			if (!map[m].flag.fireworks) {
				effno = 301;
				map[m].flag.fireworks = 1;
				clif_displaymessage(fd, msg_txt(119));
			} else {
				map[m].flag.fireworks = 0;
			}
			break;
		case 7:
			if (!map[m].flag.cloud1) {
				effno = 230;
				map[m].flag.cloud1 = 1;
				clif_displaymessage(fd, msg_txt(120));
			} else {
				map[m].flag.cloud1 = 0;
			}
			break;
		case 8:
			if (!map[m].flag.cloud2) {
				effno = 233;
				map[m].flag.cloud2 = 1;
				clif_displaymessage(fd, msg_txt(121));
			} else {
				map[m].flag.cloud2 = 0;
			}
			break;
		case 9:
			if (!map[m].flag.cloud3) {
				effno = 516;
				map[m].flag.cloud3 = 1;
				clif_displaymessage(fd, msg_txt(122));
			} else {
				map[m].flag.cloud3 = 0;
			}
			break;
	}

	if (effno >= 0) {
		struct map_session_data *psd;
		int i;

		// 指定マップ内に既に居るキャラは即時に天候変化
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (psd = (struct map_session_data *)session[i]->session_data) != NULL && psd->state.auth) {
				if (psd->bl.m == m)
					clif_misceffect3(psd->fd, psd->bl.id, effno);
			}
		}
	}

	return 0;
}

/*==========================================
 * NPCに話させる
 *------------------------------------------
 */
int atcommand_npctalk(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char name[100], mes[100];

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %99[^\n]", name, mes) < 2)
		return -1;

	npc_globalmessage(name,mes);

	return 0;
}

/*==========================================
 * PETに話させる
 *------------------------------------------
 */
int atcommand_pettalk(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mes[100], output[128];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", mes) < 1)
		return -1;
	if (sd->pd == NULL || sd->status.pet_id <= 0)
		return -1;

	sprintf(output, "%s : %s", sd->pet.name, mes);
	clif_GlobalMessage(&sd->pd->bl, output, AREA_CHAT_WOC);

	return 0;
}

/*==========================================
 * HOMに話させる
 *------------------------------------------
 */
int atcommand_homtalk(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char mes[100], output[128];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99[^\n]", mes) < 1)
		return -1;
	if (sd->hd == NULL || sd->status.homun_id <= 0 || unit_isdead(&sd->hd->bl))
		return -1;

	sprintf(output, "%s : %s", sd->hd->status.name, mes);
	clif_GlobalMessage(&sd->hd->bl, output, AREA_CHAT_WOC);

	return 0;
}

/*==========================================
 * サーバー内の人数マップを表示させる
 *------------------------------------------
 */
int atcommand_users(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i, count = 0;
	int *users;

	users = (int *)aCalloc(map_num, sizeof(int));

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth && !pl_sd->state.waitingdisconnect)
		{
			if (!(battle_config.hide_GM_session && pc_isGM(pl_sd))) {
				users[pl_sd->bl.m]++;
				count++;
			}
		}
	}

	if (count > 0) {
		for (i = 0; i < map_num; i++) {
			if (users[i] > 0) {
				msg_output(fd, "%s : %d (%02.02lf%%)", map[i].name, users[i], (double)users[i] * 100. / count);
			}
		}
	}
	msg_output(fd, msg_txt(171), count); // all : %d
	aFree(users);

	return 0;
}

/*==========================================
 * @reloadatcommand
 *   atcommand_auriga.conf のリロード
 *------------------------------------------
 */
int atcommand_reloadatcommand(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	atcommand_config_read(atcommand_conf_filename);
	clif_displaymessage(fd, msg_txt(113));

	return 0;
}

/*==========================================
 * @reloadbattleconf
 *   battle_auriga.conf のリロード
 *------------------------------------------
 */
int atcommand_reloadbattleconf(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	battle_config_read(battle_conf_filename);
	clif_displaymessage(fd, msg_txt(114));

	return 0;
}

/*==========================================
 * @reloadgmaccount
 *   gm_account_filename のリロード
 *------------------------------------------
 */
int atcommand_reloadgmaccount(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	pc_read_gm_account();
	clif_displaymessage(fd, msg_txt(115));

	return 0;
}

/*==========================================
 * @reloadhomundb
 *   ホムンクルス関連DBのリロード
 *------------------------------------------
 */
int atcommand_reloadhomundb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	homun_reload();
	clif_displaymessage(fd, msg_txt(145));

	return 0;
}

/*==========================================
 * itemDBのリロード
 *------------------------------------------
 */
int atcommand_reloaditemdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	itemdb_reload();
	read_petdb();
	clif_displaymessage(fd, msg_txt(89));

	return 0;
}

/*==========================================
 * @reloadmercdb
 *   傭兵関連DBのリロード
 *------------------------------------------
 */
int atcommand_reloadmercdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	merc_reload();
	clif_displaymessage(fd, msg_txt(193));

	return 0;
}

/*==========================================
 * @reloadelemdb
 *   精霊関連DBのリロード
 *------------------------------------------
 */
int atcommand_reloadelemdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	elem_reload();
	clif_displaymessage(fd, msg_txt(210));

	return 0;
}

/*==========================================
 * MOBDBのリロード
 *------------------------------------------
 */
int atcommand_reloadmobdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	mob_reload();
	read_petdb();
	clif_displaymessage(fd, msg_txt(90));

	return 0;
}

/*==========================================
 * @reloadpcdb
 *   exp.txt skill_tree.txt attr_fix.txt
 *   のリロード
 *------------------------------------------
 */
int atcommand_reloadpcdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	pc_readdb();
	clif_displaymessage(fd, msg_txt(117));

	return 0;
}

/*==========================================
 * スキルDBのリロード
 *------------------------------------------
 */
int atcommand_reloadskilldb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	skill_reload();
	clif_displaymessage(fd, msg_txt(91));

	return 0;
}

/*==========================================
 * @reloadstatusdb
 *   job_db1.txt job_db2.txt job_db2-2.txt
 *   refine_db.txt size_fix.txt scdata_db.txt
 *   のリロード
 *------------------------------------------
 */
int atcommand_reloadstatusdb(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	status_readdb();
	clif_displaymessage(fd, msg_txt(116));

	return 0;
}

/*==========================================
 * Message of the Dayのリロード
 *------------------------------------------
 */
int atcommand_reloadmotd(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	msg_read_motd();
	clif_displaymessage(fd, msg_txt(186));

	return 0;
}

/*==========================================
 * @im
 *   アイテムやモンスターの簡易召還
 *------------------------------------------
 */
int atcommand_itemmonster(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char name[100];
	int item_id = 0;
	struct item_data *item_data;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s", name) < 1)
		return -1;

	if ((item_id = atoi(name)) > 0) {
		if (battle_config.item_check) {
			item_data = itemdb_exists(item_id);
			if (item_data == NULL || !itemdb_available(item_id))
				item_id = 0;
		} else {
			item_data = itemdb_search(item_id);
		}
	} else {
		item_data = itemdb_searchname(name);
		if (item_data && (!battle_config.item_check || itemdb_available(item_data->nameid)))
			item_id = item_data->nameid;
	}

	if (item_id > 0) {
		int get_count, flag;
		struct item item_tmp;

		memset(&item_tmp, 0, sizeof(item_tmp));
		item_tmp.nameid = item_id;
		if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
		    item_data->flag.pet_egg || item_data->flag.pet_acce) {
			get_count = 1;
			item_tmp.identify = 0;
		} else {
			get_count = 30;
			item_tmp.identify = 1;
		}
		if (battle_config.itemidentify)
			item_tmp.identify = 1;
		if ((flag = pc_additem(sd, &item_tmp, get_count))) {
			clif_additem(sd, 0, 0, flag);
		}
		return 0;
	} else {
		int mob_id, x = 0, y = 0;

		if ((mob_id = atoi(name)) == 0)
			mob_id = mobdb_searchname(name);
		if (mob_id == 0) {
			clif_displaymessage(fd, msg_txt(40));
			return 0;
		}
		x = sd->bl.x + (atn_rand() % 10 - 5);
		y = sd->bl.y + (atn_rand() % 10 - 5);
		if (mob_once_spawn(sd, sd->bl.m, x, y, "--ja--", mob_id, 1, "") == 0)
			clif_displaymessage(fd, msg_txt(118));
	}

	return 0;
}

/*==========================================
 * Mapflag
 *------------------------------------------
 */
int atcommand_mapflag(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char w3[100], w4[100] = "";

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s %99s", w3, w4) < 1)
		return -1;

	if (npc_set_mapflag(sd->bl.m, w3, w4) < 0) {
		clif_displaymessage(fd,msg_txt(124));
		return 0;
	}
	map_field_setting();
	msg_output(fd, msg_txt(125), w3);

	return 0;
}

/*==========================================
 * マナーポイント
 *------------------------------------------
 */
int atcommand_mannerpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int manner;
	char character[100];

	if (battle_config.nomanner_mode)
		return 0;

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%d %99[^\n]", &manner, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	clif_manner_message(sd, 0);
	clif_manner_message(pl_sd, 5);

	if(pl_sd->status.manner < manner) {
		pl_sd->status.manner -= manner;
		status_change_start(&pl_sd->bl,SC_NOCHAT,0,0,0,0,0,0);
	} else {
		pl_sd->status.manner = 0;
		status_change_end(&pl_sd->bl,SC_NOCHAT,-1);
	}

	clif_GM_silence(sd, pl_sd, ((manner > 0)? 1: 0));

	return 0;
}

/*==========================================
 * キャラ鯖の制限人数の変更
 *------------------------------------------
 */
int atcommand_connectlimit(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int limit = 0;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &limit) < 1)
		return -1;
	if (limit < 0)
		return -1;

	intif_char_connect_limit(limit);

	if (limit) {
		msg_output(fd, msg_txt(126), limit);
	} else {
		clif_displaymessage(fd, msg_txt(127));
	}

	return 0;
}

/*==========================================
 * 緊急招集の受諾
 *------------------------------------------
 */
int atcommand_econ(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct guild *g = NULL;

	nullpo_retr(-1, sd);

	if (sd->status.guild_id <= 0)
		return -1;

	g = guild_search(sd->status.guild_id);
	if (g == NULL || sd == g->member[0].sd)
		return -1;

	sd->state.refuse_emergencycall = 0;
	msg_output(fd, msg_txt(128), g->master);

	return 0;
}

/*==========================================
 * 緊急招集の拒否
 *------------------------------------------
 */
int atcommand_ecoff(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct guild *g = NULL;

	nullpo_retr(-1, sd);

	if (sd->status.guild_id <= 0)
		return -1;

	g = guild_search(sd->status.guild_id);
	if (g == NULL || sd == g->member[0].sd)
		return -1;

	sd->state.refuse_emergencycall = 1;
	msg_output(fd, msg_txt(129), g->master);

	return 0;
}

/*==========================================
 * アイコン表示 デバック用
 *------------------------------------------
 */
int atcommand_icon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int type = 0, on = 1, val1 = 0, val2 = 0, val3 = 0;
	unsigned int tick = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d %u %d %d %d", &type, &on, &tick, &val1, &val2, &val3) < 1)
		return -1;

	clif_status_change(&sd->bl, type, on, tick, val1, val2, val3);

	return 0;
}

/*==========================================
 * BSランキング
 *------------------------------------------
 */
int atcommand_blacksmith(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	ranking_display(sd,RK_BLACKSMITH,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * アルケミランキング
 *------------------------------------------
 */
int atcommand_alchemist(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	ranking_display(sd,RK_ALCHEMIST,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * テコンランキング
 *------------------------------------------
 */
int atcommand_taekwon(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	ranking_display(sd,RK_TAEKWON,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * ランキング
 *------------------------------------------
 */
int atcommand_ranking(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &i) < 1)
		return -1;
	if (i < 0 || i >= MAX_RANKER)
		return -1;

	ranking_display(sd,i,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * ランキングポイント付与
 *------------------------------------------
 */
int atcommand_rankingpoint(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int type,point;
	struct map_session_data *pl_sd;
	char char_name[100] = "";

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d %99[^\n]", &type, &point, char_name) < 2)
		return -1;
	if (type < 0 || type >= MAX_RANKER)
		return -1;

	if (char_name[0])
		pl_sd = map_nick2sd(char_name);
	else
		pl_sd = sd;

	if (pl_sd != NULL) {
		ranking_gain_point(pl_sd,type,point);
		ranking_setglobalreg(pl_sd,type);
		ranking_update(pl_sd,type);
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}

/*==========================================
 * 感情をリセット
 *------------------------------------------
 */
int atcommand_resetfeel(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &i) < 1)
		return -1;

	if (i >= 0 && i < 3) {
		sd->feel_index[i] = -1;
		memset(&sd->status.feel_map[i], 0, sizeof(sd->status.feel_map[0]));
		chrif_save(sd,0);
	}

	return 0;
}

/*==========================================
 * 憎悪をリセット
 *------------------------------------------
 */
int atcommand_resethate(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	const char *reg[] = { "PC_HATE_MOB_SUN", "PC_HATE_MOB_MOON", "PC_HATE_MOB_STAR" };
	int i;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &i) < 1)
		return -1;

	if (i >= 0 && i < sizeof(reg)/sizeof(reg[0])) {
		sd->hate_mob[i] = -1;
		pc_setglobalreg(sd,reg[i],0);
	}

	return 0;
}

/*==========================================
 * resetstate
 *------------------------------------------
 */
int atcommand_resetstate(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_resetstate(sd);

	return 0;
}

/*==========================================
 * resetskill
 *------------------------------------------
 */
int atcommand_resetskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_resetskill(sd, -1);

	return 0;
}

/*==========================================
 * エモーション表示＠デバッグ用
 *------------------------------------------
 */
int atcommand_emotion(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	clif_emotion(&sd->bl, atoi(message));

	return 0;
}

/*==========================================
 * ステータスMAX
 *------------------------------------------
 */
int atcommand_statall(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int idx;
	short* status[6];
	int max;

	nullpo_retr(-1, sd);

	status[0] = &sd->status.str;
	status[1] = &sd->status.agi;
	status[2] = &sd->status.vit;
	status[3] = &sd->status.int_;
	status[4] = &sd->status.dex;
	status[5] = &sd->status.luk;

	if(pc_is3rdclass(sd) && pc_isbaby(sd))
		max = battle_config.third_baby_status_max;
	else if(pc_is3rdclass(sd))
		max = battle_config.third_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV && pc_isbaby(sd))
		max = battle_config.esnv_baby_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV)
		max = battle_config.esnv_status_max;
	else if(sd->status.class_ == PC_CLASS_KG || sd->status.class_ == PC_CLASS_OB)
		max = battle_config.ko_status_max;
	else if(sd->status.class_ == PC_CLASS_RL)
		max = battle_config.rl_status_max;
	else if(sd->status.class_ == PC_CLASS_SUM)
		max = battle_config.sum_status_max;
	else if(pc_isbaby(sd))
		max = battle_config.baby_status_max;
	else
		max = battle_config.max_parameter;

	if (!message || !*message) {
		for (idx = 0; idx < 6; idx++)
			*status[idx] = (short)max;
	} else {
		int value, new_value;
		value = atoi(message);
		for (idx = 0; idx < 6; idx++) {
			new_value = *status[idx] + value;
			if (new_value < 1)
				new_value = 1;
			else if (new_value > max)
				new_value = max;
			*status[idx] = (short)new_value;
		}
	}

	clif_updatestatus(sd, SP_STR);
	clif_updatestatus(sd, SP_AGI);
	clif_updatestatus(sd, SP_VIT);
	clif_updatestatus(sd, SP_INT);
	clif_updatestatus(sd, SP_DEX);
	clif_updatestatus(sd, SP_LUK);
	clif_updatestatus(sd, SP_USTR);
	clif_updatestatus(sd, SP_UAGI);
	clif_updatestatus(sd, SP_UVIT);
	clif_updatestatus(sd, SP_UINT);
	clif_updatestatus(sd, SP_UDEX);
	clif_updatestatus(sd, SP_ULUK);
	status_calc_pc(sd, 0);
	clif_displaymessage(fd, msg_txt(42));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_viewclass(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int view_class;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &view_class) < 1)
		return -1;

	sd->view_class = view_class;
	clif_changelook(&sd->bl,LOOK_BASE,view_class);

	return 0;
}

/*==========================================
 * メールBOX開かせる
 *------------------------------------------
 */
int atcommand_mailbox(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	clif_openmailbox(fd);

	return 0;
}

/*==========================================
 * スクリプト変数の操作
 *------------------------------------------
 */
static int atcommand_vars_sub(struct map_session_data *sd,const char *src_var,const char *name,const char *str)
{
	struct map_session_data *pl_sd = NULL;
	struct linkdb_node **ref = NULL;
	char dst_var[100];
	char *p, *output = NULL;
	char prefix, postfix;
	int elem = 0;
	const int read_only = (str)? 0: 1;

	strncpy(dst_var, src_var, 99);
	dst_var[99] = 0;

	if ((p = strchr(dst_var, '[')) != NULL)	// []の部分は削る
		*p = 0;

	// 登録されていて参照可能な変数かどうか調べる
	if (!script_check_variable(dst_var, (p != NULL), read_only)) {
		return 15;
	}

	prefix  = *dst_var;
	postfix = dst_var[strlen(dst_var)-1];

	if (prefix != '$' && prefix != '\'') {
		if (name && name[0])
			pl_sd = map_nick2sd(name);
		else
			pl_sd = sd;

		if (pl_sd == NULL)
			return 54;
	}
	if (prefix == '\'') {
		struct npc_data *nd = NULL;
		if (dst_var[1] == '@') {
			return 56;
		}
		nd = npc_name2id(name);
		if (nd == NULL || nd->subtype != SCRIPT || !nd->u.scr.script) {
			return 58;
		}
		ref = &nd->u.scr.script->script_vars;
	}

	// []があるときはgetelementofarrayと同様の処理をする
	if (p) {
		size_t len;
		int flag = 0;
		if (postfix == '$') {	// postfixは削る
			dst_var[strlen(dst_var)-1] = 0;
		}
		len = strlen(dst_var);

		while (1) {
			char *np = NULL;
			elem = strtobxl(++p, &np, 0);
			if ( elem < 0 || elem >= 128 || !np || np[0] != ']' || (np[1] != '[' && np[1] != '\0') )
				return 15;
			p = np + 1;
			if (*p == '\0')
				break;
			if (elem == 0 && !flag)
				continue;

			len += sprintf(dst_var + len, "[%d]", elem);
			flag = 1;
		}
		if (postfix == '$')
			strcat(dst_var, "$");
	}

	if (read_only) {
		void *ret = script_read_vars(pl_sd, dst_var, elem, ref);
		if (postfix == '$') {
			output = (char *)aMalloc(strlen(src_var) + strlen((char*)ret) + 4);
			sprintf(output, "%s : %s", src_var, (char*)ret);
		} else {
			output = (char *)aMalloc(strlen(src_var) + 16 + 4);
			sprintf(output, "%s : %d", src_var, PTR2INT(ret));
		}
	} else {
		const char *format = msg_txt(67);
		script_write_vars(pl_sd, dst_var, elem, (postfix == '$')? (void*)str: INT2PTR(strtobxl(str,NULL,0)), ref);
		output = (char *)aMalloc(strlen(format) + strlen(src_var) + strlen(str) + 1);
		sprintf(output, format, src_var, str);
	}
	clif_displaymessage(sd->fd, output);
	aFree(output);

	return -1;	// succeeded
}

/*==========================================
 * スクリプト変数を読み取る
 *------------------------------------------
 */
int atcommand_readvars(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int err;
	char vars[100], name[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(name, 0, sizeof(name));
	if (sscanf(message, "%99s %99[^\n]", vars, name) < 1)
		return -1;

	err = atcommand_vars_sub(sd, vars, name, NULL);
	if (err >= 0)	// エラー時
		msg_output(fd, msg_txt(err), vars);

	return 0;
}

/*==========================================
 * スクリプト変数に書き込む
 *------------------------------------------
 */
int atcommand_writevars(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int err, next = 0;
	char vars[100], name[100], str[100];
	char c = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %c%n", vars, &c, &next) < 2)
		return -1;

	memset(name, 0, sizeof(name));

	// "で囲んである場合は簡易parseする
	if (c == '\"') {
		int i = 0;
		const char *p = message + next;

		while (*p && *p != '\"' && i < 99) {
			if ((unsigned char)p[-1] <= 0x7e && *p == '\\') {
				p++;
			}
			str[i++] = *p++;
		}
		if (*p != '\"') {
			return -1;
		}
		str[i] = 0;
		sscanf(p, "\" %99[^\n]", name);
	} else {
		if (sscanf(message + next - 1, "%99s %99[^\n]", str, name) < 1)
			return -1;
	}

	err = atcommand_vars_sub(sd, vars, name, str);
	if (err >= 0)	// エラー時
		msg_output(fd, msg_txt(err), vars);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_cloneskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (skillid < 0)
		return 0;

	if (ret == 1)
		skilllv = skill_get_max(skillid);

	if (pc_checkskill(sd,RG_PLAGIARISM) && sd->sc.data[SC_PRESERVE].timer == -1)
		skill_clone(sd, skillid, skilllv);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_cloneskill2(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int cloneskilllv, skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (skillid < 0)
		return 0;

	if (ret == 1)
		skilllv = skill_get_max(skillid);
	if (skilllv < 0)
		skilllv = 0;

	cloneskilllv      = pc_checkskill(sd,RG_PLAGIARISM);
	sd->skill_clone.id = skillid;
	sd->skill_clone.lv = (skilllv > cloneskilllv) ? cloneskilllv : skilllv;
	clif_skillinfoblock(sd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_reproduce(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (skillid < 0)
		return 0;

	if (ret == 1)
		skilllv = skill_get_max(skillid);

	if (pc_checkskill(sd,SC_REPRODUCE) && sd->sc.data[SC__REPRODUCE].timer != -1)
		skill_reproduce(sd, skillid, skilllv);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_reproduce2(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int reproducelv, skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (skillid < 0)
		return 0;

	if (ret == 1)
		skilllv = skill_get_max(skillid);
	if (skilllv < 0)
		skilllv = 0;

	reproducelv      = pc_checkskill(sd,SC_REPRODUCE);
	sd->skill_reproduce.id = skillid;
	sd->skill_reproduce.lv = (skilllv > reproducelv) ? reproducelv : skilllv;
	clif_skillinfoblock(sd);

	return 0;
}

/*==========================================
 * Show Monster DB Info   v 1.0
 * originally by [Lupus] eAthena
 *------------------------------------------
 */
int atcommand_mobinfo(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	const char *msize[] = { "小型", "中型", "大型" };
	const char *mrace[] = { "無", "不死", "動物", "植物", "昆虫", "魚", "悪魔", "人間", "天使", "竜", "Boss", "Non-Boss" };
	const char *melement[] = { "無", "無", "水", "地", "火", "風", "毒", "聖", "闇", "念", "不死" };
	char output[200];
	struct item_data *item_data;
	struct mobdb_data *m;
	int i, j, mob_id;
	size_t len;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((mob_id = atoi(message)) == 0)
		mob_id = mobdb_searchname(message);

	if (!mobdb_exists(mob_id)) {
		clif_displaymessage(fd, msg_txt(40));
		return 0;
	}

	m = mobdb_search(mob_id);

	// stats
	msg_output(fd, "%s Monster: %s/%s (%d)", ((m->mexp)? "MVP": ""),
		m->name, m->jname, mob_id);
	msg_output(fd, " Level:%d  HP:%d  SP:%d  Base EXP:%d  Job EXP:%d",
		m->lv, m->max_hp, m->max_sp, m->base_exp, m->job_exp);
	msg_output(fd, " DEF:%d  MDEF:%d  STR:%d  AGI:%d  VIT:%d  INT:%d  DEX:%d  LUK:%d",
		m->def, m->mdef, m->str, m->agi, m->vit, m->int_, m->dex, m->luk);

	if (m->element < 20) {
		// Element - None, Level 0
		i = 0;
		j = 0;
	} else {
		i = m->element % 20 + 1;
		j = m->element / 20;
		if (i >= sizeof(melement)/sizeof(melement[0]))
			i = 0;
	}
	msg_output(fd, " ATK:%d-%d  Range:%d-%d-%d  Size: %s  Race: %s  Element: %s (Lv:%d)",
		m->atk1, m->atk2, m->range, m->range2 , m->range3,
		((m->size >= sizeof(msize)/sizeof(msize[0]))? "-": msize[m->size]), ((m->race >= sizeof(mrace)/sizeof(mrace[0]))? "-": mrace[m->race]), melement[i], j);

	// drops
	clif_displaymessage(fd, " Drops:");
	strcpy(output, " ");
	len = strlen(output);
	for (i = 0, j = 0; i < ITEM_DROP_COUNT; i++) {
		int rate;
		if (m->dropitem[i].nameid <= 0 || (item_data = itemdb_exists(m->dropitem[i].nameid)) == NULL)
			continue;
		rate = mob_droprate_fix(&sd->bl, m->dropitem[i].nameid, m->dropitem[i].p);
		if (rate > 0) {
			len += sprintf(output + len, " - %s  %02.02lf%%", item_data->jname, (double)rate / 100.);
			if (++j % 3 == 0) {
				clif_displaymessage(fd, output);
				strcpy(output, " ");
				len = 1;
			}
		}
	}
	if (j == 0)
		clif_displaymessage(fd, "This monster has no drops.");
	else if (j % 3 != 0)
		clif_displaymessage(fd, output);

	// mvp
	if (m->mexp) {
		msg_output(fd, " MVP Bonus EXP:%d  %02.02lf%%", m->mexp, (double)m->mexpper / 100.);
		strcpy(output, " MVP Items:");
		len = strlen(output);
		for (i = 0, j = 0; i < 3; i++) {
			if (m->mvpitem[i].nameid <= 0 || (item_data = itemdb_exists(m->mvpitem[i].nameid)) == NULL)
				continue;
			if (m->mvpitem[i].p > 0) {
				if (j++ == 0) {
					strcat(output, " -");
					len += 2;
				}
				len += sprintf(output + len, " %s  %02.02lf%%", item_data->jname, (double)m->mvpitem[i].p / 100.);
			}
		}
		if (j == 0)
			clif_displaymessage(fd, "This monster has no MVP prizes.");
		else
			clif_displaymessage(fd, output);
	}

	return 0;
}

/*==========================================
 * ホムのレベル調節
 *------------------------------------------
 */
int atcommand_homlevel(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int level;
	struct homun_data *hd = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if ((hd = sd->hd) == NULL)
		return -1;

	level = atoi(message);
	if (level > MAX_LEVEL)
		return -1;

	if (level >= 1) {
		int i, flag = 0;
		for (i = 1; i <= level; i++) {
			if (homun_nextbaseexp(hd) <= 0)
				break;
			flag = 1;
			hd->status.base_level++;
			//hd->status.status_point += 15 + (hd->status.base_level+14)/3;	// 微調整してもうまくいかず・・・
			if (hd->status.base_level%3 == 0)	// 3レベル毎にSkillPoint加算
				hd->status.skill_point++;

			homun_upstatus(&hd->status);	// ステアップ計算
		}
		if (flag) {
			homun_calc_status(hd);			// ステータス計算
			homun_heal(hd,hd->max_hp,hd->max_sp);
			clif_misceffect2(&hd->bl,568);
			if (hd->msd) {
				clif_send_homstatus(hd->msd,0);
				clif_homskillinfoblock(hd->msd);
			}
		}
		clif_displaymessage(fd, msg_txt(50));
	} else if (level < 0) {
		clif_displaymessage(fd, msg_txt(52));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_homviewclass(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int view_class;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &view_class) < 1)
		return -1;

	if (sd->hd)
		sd->hd->view_class = view_class;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_homevolution(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int evo_class = 0;

	nullpo_retr(-1, sd);

	if (sd->hd == NULL)
		return 0;

	if (message && *message) {
		if (sscanf(message, "%d", &evo_class) < 1)
			evo_class = 0;
	}
	homun_change_class(sd, evo_class);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_homrecalc(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->hd == NULL)
		return 0;

	homun_recalc_status(sd->hd);
	homun_heal(sd->hd,sd->hd->status.max_hp,sd->hd->status.max_sp);
	if (sd->hd->msd) {
		clif_send_homstatus(sd->hd->msd,0);
		clif_homskillinfoblock(sd->hd->msd);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_makehomun(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int homunid;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d", &homunid) < 1)
		return -1;
	if (homunid < HOM_ID || homunid >= HOM_ID + MAX_HOMUN_DB)
		return -1;

	if (sd->status.homun_id == 0 && sd->state.homun_creating == 0) {
		homun_create_hom(sd,homunid);
	} else {
		clif_displaymessage(fd, msg_txt(144));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_homfriendly(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int friendly;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	friendly = atoi(message);
	if (sd->status.homun_id > 0 && sd->hd) {
		if (friendly < 0 || friendly > 100000)
			return -1;
		sd->hd->status.intimate = friendly;
		sd->hd->intimate = sd->hd->status.intimate;
		clif_send_homdata(sd,1,sd->hd->intimate/100);
	}

	return 0;
}

/*==========================================
 * アイテムの自動取得機能を切り替える
 *------------------------------------------
 */
int atcommand_autoloot(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->state.autoloot) {
		sd->state.autoloot = 0;
		clif_displaymessage(fd, msg_txt(146));
	} else {
		sd->state.autoloot = 1;
		clif_displaymessage(fd, msg_txt(147));
	}

	return 0;
}

/*==========================================
 * セルタイプを変更する
 *------------------------------------------
 */
int atcommand_changemaptype(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int x, y, type;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%d %d %d", &x, &y, &type) < 3)
		return -1;

	map_setcell(sd->bl.m, x, y, type);
	clif_changemapcell(sd->bl.m, x, y, type, 1);
	clif_displaymessage(fd, msg_txt(183));

	return 0;
}

/*==========================================
 * ホットキーセットの切り替え
 *------------------------------------------
 */
int atcommand_hotkeyset(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int num, hotkeys;
#if PACKETVER >= 20090617
	hotkeys = 38;
#elif PACKETVER >= 20090603
	hotkeys = 36;
#else
	hotkeys = 27;
#endif

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	num = atoi(message);

	if (num >= 0 && num <= (MAX_HOTKEYS - 1) / hotkeys) {
		sd->hotkey_set = num;
		clif_send_hotkey(sd);
		msg_output(fd, msg_txt(184), sd->hotkey_set);
	} else {
		msg_output(fd, msg_txt(185), (MAX_HOTKEYS - 1) / hotkeys);
	}

	return 0;
}

/*==========================================
 * 傭兵召喚
 *------------------------------------------
 */
int atcommand_callmerc(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int class_, retr;
	unsigned int limit;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if ((retr = sscanf(message, "%d %u", &class_, &limit)) < 1)
		return -1;
	if (retr == 1)
		limit = 1800;

	merc_callmerc(sd, class_, limit);

	return 0;
}

/*==========================================
 * @コマンド設定ファイル読み込み
 * atcommand_go_db.txt @go設定ファイル
 *------------------------------------------
 */
static int atcommand_readdb(void)
{
	int i = 0, j;
	FILE *fp;
	char line[1024], *p;
	const char *filename = "db/atcommand_go_db.txt";

	memset(&atcommand_go_db, 0, sizeof(atcommand_go_db));

	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("atcommand_readdb: open [%s] failed !\n", filename);
		return 1;
	}

	while(fgets(line,1020,fp)){
		char *split[5];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<5 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 5)
			continue;
		if(i < 0 || i >= MAX_ATCOMMAND_GO)
			continue;

		atcommand_go_db[i].nameid = atoi(split[0]);
		strncpy(atcommand_go_db[i].code,split[1],8);
		strncpy(atcommand_go_db[i].mapname,split[2],24);
		atcommand_go_db[i].x  = (short)atoi(split[3]);
		atcommand_go_db[i].y  = (short)atoi(split[4]);

		// mapnameに拡張子".gat"指定が無い場合
		if(strstr(atcommand_go_db[i].mapname, ".gat") == NULL && strlen(atcommand_go_db[i].mapname) < 19)
			strcat(atcommand_go_db[i].mapname, ".gat");

		// force \0 terminal
		atcommand_go_db[i].code[7] = '\0';
		atcommand_go_db[i].mapname[23] = '\0';

		if(++i >= MAX_ATCOMMAND_GO)
			break;
	}

	fclose(fp);
	printf("read %s done (count=%d)\n", filename, i);

	return 0;
}

/*==========================================
 * 同盟チャットの切り替え
 *------------------------------------------
 */
int atcommand_alliance(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!battle_config.alliance_message)
		return 0;

	if (sd->state.alliance_message) {
		sd->state.alliance_message = 0;
		clif_displaymessage(fd, msg_txt(211));
	} else {
		sd->state.alliance_message = 1;
		clif_displaymessage(fd, msg_txt(212));
	}

	return 0;
}

/*==========================================
 * リロード
 *------------------------------------------
 */
void atcommand_reload(void)
{
	atcommand_readdb();
}

/*==========================================
 * クエスト初期化処理
 *------------------------------------------
 */
int do_init_atcommand(void)
{
	atcommand_readdb();

	return 0;
}
