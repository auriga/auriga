//atcommand.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "socket.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"

#include "map.h"
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
#include "ranking.h"
#include "homun.h"
//#include "trade.h"
//#include "core.h"
#include "db.h"
#include "unit.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

//JOB TABLE
extern int max_job_table[3][32];

static char command_symbol = '@'; /* first char of the commands */

#define MSG_NUMBER 200
static char *msg_table[MSG_NUMBER]; /* Server messages */

static struct synonym_table { /* table for GM command synonyms */
	char* synonym;
	char* command;
} *synonym_table = NULL;
static int synonym_count = 0; /* number of synonyms */

#define ATCOMMAND_FUNC(x) int atcommand_ ## x (const int fd, struct map_session_data* sd, const char* command, const char* message)
//ATCOMMAND_FUNC(broadcast);
//ATCOMMAND_FUNC(localbroadcast);
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
ATCOMMAND_FUNC(killmonster2);
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
ATCOMMAND_FUNC(doommap);
ATCOMMAND_FUNC(raise);
ATCOMMAND_FUNC(raisemap);
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
ATCOMMAND_FUNC(guild);
ATCOMMAND_FUNC(agitstart);
ATCOMMAND_FUNC(agitend);
ATCOMMAND_FUNC(onlymes);
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
ATCOMMAND_FUNC(users);
ATCOMMAND_FUNC(reloadatcommand);
ATCOMMAND_FUNC(reloadbattleconf);
ATCOMMAND_FUNC(reloadgmaccount);
ATCOMMAND_FUNC(reloadhomundb);
ATCOMMAND_FUNC(reloaditemdb);
ATCOMMAND_FUNC(reloadmobdb);
ATCOMMAND_FUNC(reloadpcdb);
ATCOMMAND_FUNC(reloadskilldb);
ATCOMMAND_FUNC(reloadstatusdb);
ATCOMMAND_FUNC(itemmonster);
ATCOMMAND_FUNC(mapflag);
ATCOMMAND_FUNC(mannerpoint);
ATCOMMAND_FUNC(connectlimit);
ATCOMMAND_FUNC(help1);
ATCOMMAND_FUNC(help2);
ATCOMMAND_FUNC(help3);
ATCOMMAND_FUNC(help4);
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
ATCOMMAND_FUNC(mobinfo);
ATCOMMAND_FUNC(homlevel);
ATCOMMAND_FUNC(homviewclass);
ATCOMMAND_FUNC(homevolution);
ATCOMMAND_FUNC(homrecalc);
ATCOMMAND_FUNC(makehomun);
ATCOMMAND_FUNC(homfriendly);
ATCOMMAND_FUNC(autoloot);

/*==========================================
 *AtCommandInfo atcommand_info[]構造体の定義
 *------------------------------------------
 */
static AtCommandInfo atcommand_info[] = {
	{ AtCommand_RuraP,              "@rura+",            0, atcommand_rurap },
	{ AtCommand_Rura,               "@rura",             0, atcommand_rura },
	{ AtCommand_Where,              "@where",            0, atcommand_where },
	{ AtCommand_JumpTo,             "@jumpto",           0, atcommand_jumpto },
	{ AtCommand_Jump,               "@jump",             0, atcommand_jump },
	{ AtCommand_Who,                "@who",              0, atcommand_who },
	{ AtCommand_Save,               "@save",             0, atcommand_save },
	{ AtCommand_Load,               "@load",             0, atcommand_load },
	{ AtCommand_Speed,              "@speed",            0, atcommand_speed },
	{ AtCommand_Storage,            "@storage",          0, atcommand_storage },
	{ AtCommand_GuildStorage,       "@gstorage",         0, atcommand_guildstorage },
	{ AtCommand_Option,             "@option",           0, atcommand_option },
	{ AtCommand_Hide,               "@hide",             0, atcommand_hide },
	{ AtCommand_JobChange,          "@jobchange",        0, atcommand_jobchange },
	{ AtCommand_Die,                "@die",              0, atcommand_die },
	{ AtCommand_Kill,               "@kill",             0, atcommand_kill },
	{ AtCommand_Alive,              "@alive",            0, atcommand_alive },
	{ AtCommand_Kami,               "@kami",             0, atcommand_kami },
	{ AtCommand_KamiB,              "@kamib",            0, atcommand_kami },
	{ AtCommand_KamiC,              "@kamic",            0, atcommand_kami },
	{ AtCommand_Heal,               "@heal",             0, atcommand_heal },
	{ AtCommand_Item,               "@item",             0, atcommand_item },
	{ AtCommand_Item2,              "@item2",            0, atcommand_item2 },
	{ AtCommand_Item3,              "@item3",            0, atcommand_item3 },
	{ AtCommand_ItemReset,          "@itemreset",        0, atcommand_itemreset },
	{ AtCommand_BaseLevelUp,        "@lvup",             0, atcommand_baselevelup },
	{ AtCommand_JobLevelUp,         "@joblvup",          0, atcommand_joblevelup },
	{ AtCommand_Help,               "@help",             0, atcommand_help },
	{ AtCommand_Help1,              "@help1",            0, atcommand_help1 },
	{ AtCommand_Help2,              "@help2",            0, atcommand_help2 },
	{ AtCommand_Help3,              "@help3",            0, atcommand_help3 },
	{ AtCommand_Help4,              "@help4",            0, atcommand_help4 },
	{ AtCommand_GM,                 "@gm",               0, atcommand_gm },
	{ AtCommand_PvPOff,             "@pvpoff",           0, atcommand_pvpoff },
	{ AtCommand_PvPOn,              "@pvpon",            0, atcommand_pvpon },
	{ AtCommand_GvGOff,             "@gvgoff",           0, atcommand_gvgoff },
	{ AtCommand_GvGOn,              "@gvgon",            0, atcommand_gvgon },
	{ AtCommand_Model,              "@model",            0, atcommand_model },
	{ AtCommand_Go,                 "@go",               0, atcommand_go },
	{ AtCommand_Monster,            "@monster",          0, atcommand_monster },
	{ AtCommand_MonsterMap,         "@monstermap",       0, atcommand_monster },
	{ AtCommand_KillMonster,        "@killmonster",      0, atcommand_killmonster },
	{ AtCommand_KillMonster2,       "@killmonster2",     0, atcommand_killmonster2 },
	{ AtCommand_Refine,             "@refine",           0, atcommand_refine },
	{ AtCommand_Produce,            "@produce",          0, atcommand_produce },
	{ AtCommand_Repair,             "@repair",           0, atcommand_repair },
	{ AtCommand_Memo,               "@memo",             0, atcommand_memo },
	{ AtCommand_GAT,                "@gat",              0, atcommand_gat },
	{ AtCommand_Packet,             "@packet",           0, atcommand_packet },
	{ AtCommand_StatusPoint,        "@stpoint",          0, atcommand_statuspoint },
	{ AtCommand_SkillPoint,         "@skpoint",          0, atcommand_skillpoint },
	{ AtCommand_Zeny,               "@zeny",             0, atcommand_zeny },
	{ AtCommand_Strength,           "@str",              0, atcommand_param },
	{ AtCommand_Agility,            "@agi",              0, atcommand_param },
	{ AtCommand_Vitality,           "@vit",              0, atcommand_param },
	{ AtCommand_Intelligence,       "@int",              0, atcommand_param },
	{ AtCommand_Dexterity,          "@dex",              0, atcommand_param },
	{ AtCommand_Luck,               "@luk",              0, atcommand_param },
	{ AtCommand_GuildLevelUp,       "@guildlvup",        0, atcommand_guildlevelup },
	{ AtCommand_MakePet,            "@makepet",          0, atcommand_makepet },
	{ AtCommand_Hatch,              "@hatch",            0, atcommand_hatch },
	{ AtCommand_PetFriendly,        "@petfriendly",      0, atcommand_petfriendly },
	{ AtCommand_PetHungry,          "@pethungry",        0, atcommand_pethungry },
	{ AtCommand_PetRename,          "@petrename",        0, atcommand_petrename },
	{ AtCommand_CharPetRename,      "@charpetrename",    0, atcommand_charpetrename },
	{ AtCommand_Recall,             "@recall",           0, atcommand_recall },
	{ AtCommand_Recallall,          "@recallall",        0, atcommand_recallall },
	{ AtCommand_RecallGuild,        "@recallguild",      0, atcommand_recallguild },
	{ AtCommand_RecallParty,        "@recallparty",      0, atcommand_recallparty },
	{ AtCommand_CharacterJob,       "@charjob",          0, atcommand_character_job },
	{ AtCommand_Revive,             "@revive",           0, atcommand_revive },
	{ AtCommand_CharacterStats,     "@charstats",        0, atcommand_character_stats },
	{ AtCommand_CharacterOption,    "@charoption",       0, atcommand_character_option },
	{ AtCommand_CharacterSave,      "@charsave",         0, atcommand_character_save },
	{ AtCommand_Night,              "@night",            0, atcommand_night },
	{ AtCommand_Day,                "@day",              0, atcommand_day },
	{ AtCommand_Doom,               "@doom",             0, atcommand_doom },
	{ AtCommand_DoomMap,            "@doommap",          0, atcommand_doommap },
	{ AtCommand_Raise,              "@raise",            0, atcommand_raise },
	{ AtCommand_RaiseMap,           "@raisemap",         0, atcommand_raisemap },
	{ AtCommand_CharacterBaseLevel, "@charbaselvl",      0, atcommand_character_baselevel },
	{ AtCommand_CharacterJobLevel,  "@charjlvl",         0, atcommand_character_joblevel },
	{ AtCommand_Kick,               "@kick",             0, atcommand_kick },
	{ AtCommand_KickAll,            "@kickall",          0, atcommand_kickall },
	{ AtCommand_AllSkill,           "@allskill",         0, atcommand_allskill },
	{ AtCommand_QuestSkill,         "@questskill",       0, atcommand_questskill },
	{ AtCommand_CharQuestSkill,     "@charquestskill",   0, atcommand_charquestskill },
	{ AtCommand_LostSkill,          "@lostskill",        0, atcommand_lostskill },
	{ AtCommand_CharLostSkill,      "@charlostskill",    0, atcommand_charlostskill },
	{ AtCommand_SpiritBall,         "@spiritball",       0, atcommand_spiritball },
	{ AtCommand_Party,              "@party",            0, atcommand_party },
	{ AtCommand_Guild,              "@guild",            0, atcommand_guild },
	{ AtCommand_AgitStart,          "@agitstart",        0, atcommand_agitstart },
	{ AtCommand_AgitEnd,            "@agitend",          0, atcommand_agitend },
	{ AtCommand_OnlyMes,            "@mes",              0, atcommand_onlymes },
	{ AtCommand_MesWeb,             "@mesweb",           0, atcommand_onlymes },
	{ AtCommand_MapExit,            "@mapexit",          0, atcommand_mapexit },
	{ AtCommand_IDSearch,           "@idsearch",         0, atcommand_idsearch },
	{ AtCommand_ItemIdentify,       "@itemidentify",     0, atcommand_itemidentify },
	{ AtCommand_Shuffle,            "@shuffle",          0, atcommand_shuffle },
	{ AtCommand_Maintenance,        "@maintenance",      0, atcommand_maintenance },
	{ AtCommand_Misceffect,         "@misceffect",       0, atcommand_misceffect },
	{ AtCommand_Summon,             "@summon",           0, atcommand_summon },
	{ AtCommand_WhoP,               "@who+",             0, atcommand_whop },
	{ AtCommand_CharReset,          "@charreset",        0, atcommand_charreset },
	{ AtCommand_CharSkReset,        "@charskreset",      0, atcommand_charskreset },
	{ AtCommand_CharStReset,        "@charstreset",      0, atcommand_charstreset },
	{ AtCommand_CharSKPoint,        "@charskpoint",      0, atcommand_charskpoint },
	{ AtCommand_CharSTPoint,        "@charstpoint",      0, atcommand_charstpoint },
	{ AtCommand_CharZeny,           "@charzeny",         0, atcommand_charzeny },
	{ AtCommand_CharItemreset,      "@charitemreset",    0, atcommand_charitemreset },
	{ AtCommand_MapInfo,            "@mapinfo",          0, atcommand_mapinfo },
	{ AtCommand_MobSearch,          "@mobsearch",        0, atcommand_mobsearch },
	{ AtCommand_CleanMap,           "@cleanmap",         0, atcommand_cleanmap },
	{ AtCommand_Clock,              "@clock",            0, atcommand_clock },
	{ AtCommand_GiveItem,           "@giveitem",         0, atcommand_giveitem },
	{ AtCommand_Weather,            "@weather",          0, atcommand_weather },
	{ AtCommand_NpcTalk,            "@npctalk",          0, atcommand_npctalk },
	{ AtCommand_PetTalk,            "@pettalk",          0, atcommand_pettalk },
	{ AtCommand_Users,              "@users",            0, atcommand_users },
	{ AtCommand_ReloadAtcommand,    "@reloadatcommand",  0, atcommand_reloadatcommand },
	{ AtCommand_ReloadBattleConf,   "@reloadbattleconf", 0, atcommand_reloadbattleconf },
	{ AtCommand_ReloadGMAccount,    "@reloadgmaccount",  0, atcommand_reloadgmaccount },
	{ AtCommand_ReloadHomunDB,      "@reloadhomundb",    0, atcommand_reloadhomundb },
	{ AtCommand_ReloadItemDB,       "@reloaditemdb",     0, atcommand_reloaditemdb },
	{ AtCommand_ReloadMobDB,        "@reloadmobdb",      0, atcommand_reloadmobdb },
	{ AtCommand_ReloadPcDB,         "@reloadpcdb",       0, atcommand_reloadpcdb },
	{ AtCommand_ReloadSkillDB,      "@reloadskilldb",    0, atcommand_reloadskilldb },
	{ AtCommand_ReloadStatusDB,     "@reloadstatusdb",   0, atcommand_reloadstatusdb },
	{ AtCommand_ItemMonster,        "@im",               0, atcommand_itemmonster },
	{ AtCommand_Mapflag,            "@mapflag",          0, atcommand_mapflag },
	{ AtCommand_MannerPoint,        "@mannerpoint",      0, atcommand_mannerpoint },
	{ AtCommand_ConnectLimit,       "@connectlimit",     0, atcommand_connectlimit },
	{ AtCommand_Econ,               "@econ",             0, atcommand_econ  },
	{ AtCommand_Ecoff,              "@ecoff",            0, atcommand_ecoff },
	{ AtCommand_Icon,               "@icon",             0, atcommand_icon  },
	{ AtCommand_Ranking,            "@ranking",          0, atcommand_ranking	},
	{ AtCommand_Blacksmith,         "@blacksmith",       0, atcommand_blacksmith	},
	{ AtCommand_Alchemist,          "@alchemist",        0, atcommand_alchemist	},
	{ AtCommand_TaeKwon,            "@taekwon",          0, atcommand_taekwon	},
	{ AtCommand_ResetFeel,          "@resetfeel",        0, atcommand_resetfeel	},
	{ AtCommand_ResetHate,          "@resethate",        0, atcommand_resethate	},
	{ AtCommand_ResetState,         "@resetstate",       0, atcommand_resetstate },
	{ AtCommand_ResetSkill,         "@resetskill",       0, atcommand_resetskill },
	{ AtCommand_emotion,            "@emotion",          0, atcommand_emotion },
	{ AtCommand_statall,            "@statall",          0, atcommand_statall },
	{ AtCommand_RankingPoint,       "@rankingpoint",     0, atcommand_rankingpoint	},
	{ AtCommand_ViewClass,          "@viewclass",        0, atcommand_viewclass	},
	{ AtCommand_MailBox,            "@mailbox",          0, atcommand_mailbox	},
	{ AtCommand_ReadVars,           "@readvars",         0, atcommand_readvars	},
	{ AtCommand_WriteVars,          "@writevars",        0, atcommand_writevars	},
	{ AtCommand_CloneSkill,         "@cloneskill",       0, atcommand_cloneskill	},
	{ AtCommand_CloneSkill2,        "@cloneskill2",      0, atcommand_cloneskill2	},
	{ AtCommand_MobInfo,            "@mobinfo",          0, atcommand_mobinfo	},
	{ AtCommand_HomLevel,           "@homlv",            0, atcommand_homlevel	},
	{ AtCommand_HomViewClass,       "@homviewclass",     0, atcommand_homviewclass	},
	{ AtCommand_HomEvolution,       "@evolution",        0, atcommand_homevolution	},
	{ AtCommand_HomRecalc,          "@homrecalc",        0, atcommand_homrecalc	},
	{ AtCommand_MakeHomun,          "@makehomun",        0, atcommand_makehomun	},
	{ AtCommand_HomFriendly,        "@homfriendly",      0, atcommand_homfriendly },
	{ AtCommand_AutoLoot,           "@autoloot",         0, atcommand_autoloot	},
		// add here
	{ AtCommand_MapMove,            "@mapmove",          0, NULL },
	{ AtCommand_Broadcast,          "@broadcast",        0, NULL },
	{ AtCommand_LocalBroadcast,     "@local_broadcast",  0, NULL },
	{ AtCommand_Unknown,            NULL,              100, NULL }
};

/*===============================================
 * This function return the GM command symbol
 *-----------------------------------------------
 */
char GM_Symbol(void) {
	return command_symbol;
}

/*==========================================
 *get_atcommand_level @コマンドの必要レベルを取得
 *------------------------------------------
 */
int get_atcommand_level(const AtCommandType type)
{
	int i;

	for (i = 0; atcommand_info[i].type != AtCommand_None; i++)
		if (atcommand_info[i].type == type)
			return atcommand_info[i].level;

	return 100;
}

/*==========================================
 *
 *------------------------------------------
 */
AtCommandType
atcommand(
	const int level, const char* message, struct AtCommandInfo* info)
{
	const char* p = message;
	char command[100];
	int i;

	if (!info)
		return AtCommand_None;
	if (!p || !*p) {
		fprintf(stderr, "at command message is empty\n");
		return AtCommand_None;
	}
	if (*p != command_symbol)
		return AtCommand_None;

	if (/*p[0] == command_symbol &&*/ p[1] == command_symbol)
		return AtCommand_None;

	memset(info, 0, sizeof(AtCommandInfo));
	sscanf(p, "%99s", command);
	command[sizeof(command) - 1] = '\0';

	// check for synonym here
	for (i = 0; i < synonym_count; i++) {
		if (strcmpi(command + 1, synonym_table[i].synonym) == 0) {
			memset(command + 1, 0, sizeof(command) - 1); // don't change command_symbol (+1)
			strcpy(command + 1, synonym_table[i].command);
			break;
		}
	}

	i = 0;
	while (atcommand_info[i].type != AtCommand_Unknown) {
		if (strcmpi(command + 1, atcommand_info[i].command + 1) == 0)
			break;
		i++;
	}
	if (atcommand_info[i].type == AtCommand_Unknown ||
	    atcommand_info[i].proc == NULL ||
	    level < atcommand_info[i].level)
		return AtCommand_Unknown;
	memcpy(info, &atcommand_info[i], sizeof atcommand_info[i]);

	return info->type;
}

/*==========================================
 *is_atcommand @コマンドに存在するかどうか確認する
 *------------------------------------------
 */
AtCommandType
is_atcommand(const int fd, struct map_session_data* sd, const char* message, int gmlvl)
{
	const char* str;
	int s_flag;
	char command[100];
	const char* p;
	AtCommandInfo info;
	AtCommandType type;

	nullpo_retr(0, sd);

	if (!message || !*message)
		return AtCommand_None;

	str = message + strlen(sd->status.name);
	s_flag = 0;
	while (*str && (isspace(*str) || (s_flag == 0 && *str == ':'))) {
		if (*str == ':')
			s_flag = 1;
		str++;
	}
	if (!*str)
		return AtCommand_None;

	p = str;
	while (*p && !isspace(*p))
		p++;
	if (p - str >= sizeof command) // too long
		return AtCommand_None;
	memset(command, '\0', sizeof command);
	strncpy(command, str, p - str);
	if (isspace(*p))
		p++;

	type = atcommand((gmlvl > 0) ? gmlvl : pc_isGM(sd), command, &info);
	if (type != AtCommand_None) {
		char output[200];
		if (type == AtCommand_Unknown) {
			if (pc_isGM(sd)) {
				snprintf(output, sizeof output, msg_txt(132), command);
				clif_displaymessage(fd, output);
			}else{
				return AtCommand_None;
			}
		} else if (pc_isGM(sd)) {
			if (info.proc(fd, sd, command, p) != 0) {
				// 異常終了
				snprintf(output, sizeof output, msg_txt(133), command);
				clif_displaymessage(fd, output);
			}
		} else {
			if (info.proc(fd, sd, command, p) != 0)
				return AtCommand_None;
		}
		return info.type;
	}

	return AtCommand_None;
}

//struct Atcommand_Config atcommand_config;

/*==========================================
 * Return the message string of the specified number
 *------------------------------------------
 */
char * msg_txt(int msg_number) {
	if (msg_number < 0 || msg_number >= MSG_NUMBER) {
		if (battle_config.error_log)
			printf("Message text error: Invalid message number: %d.\n", msg_number);
	} else if (msg_table[msg_number] != NULL && msg_table[msg_number][0] != '\0')
		return msg_table[msg_number];

	return "<no message>";
}

/*==========================================
 *
 *------------------------------------------
 */
/* Read Message Data */
int msg_config_read(const char *cfgName)
{
	static int msg_config_read_done = 0; /* for multiple configuration reading */
	int msg_number;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	// init table
	if (msg_config_read_done == 0) {
		memset(&msg_table[0], 0, sizeof(msg_table[0]) * MSG_NUMBER);
		msg_config_read_done = 1;
	}

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("File not found: %s.\n", cfgName);
		return 1;
	}

	line[sizeof(line)-1] = '\0';
	while(fgets(line, sizeof(line)-1, fp)) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;
		if (sscanf(line,"%d: %[^\r\n]",&msg_number,w2) != 2) {
			if (sscanf(line,"%s: %[^\r\n]",w1,w2) != 2)
				continue;
			if (strcmpi(w1,"import") == 0) {
				msg_config_read(w2);
			}
			continue;
		}
		if (msg_number >= 0 && msg_number < MSG_NUMBER) {
			if (msg_table[msg_number]) {
				aFree(msg_table[msg_number]);
			}
			msg_table[msg_number] = (char *)aCalloc(strlen(w2) + 1, sizeof(char)); // + NULL
			strcpy(msg_table[msg_number], w2);
			//printf("msg text -> %d:%s\n", msg_number, msg_table[msg_number]);
		} else if (battle_config.error_log)
			printf("file [%s]: Invalid message number: %d.\n", cfgName, msg_number);
	}
	fclose(fp);

	return 0;
}

/*==========================================
 * Free Message Data
 *------------------------------------------
 */
void do_final_msg_config(void) {
	int msg_number;

	for (msg_number = 0; msg_number < MSG_NUMBER; msg_number++) {
		if (msg_table[msg_number]) {
			aFree(msg_table[msg_number]);
		}
	}

	return;
}

/*
static AtCommandInfo* getAtCommandInfoByType(const AtCommandType type)
{
	int i;

	for (i = 0; atcommand_info[i].type != AtCommand_None; i++)
		if (atcommand_info[i].type == type)
			return &atcommand_info[i];

	return NULL;
}
*/

/*==========================================
 *
 *------------------------------------------
 */
static AtCommandInfo*
get_atcommandinfo_byname(const char* name)
{
	int i;

	for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++)
		if (strcmpi(atcommand_info[i].command + 1, name) == 0)
			return &atcommand_info[i];

	return NULL;
}

/*==========================================
 *
 *------------------------------------------
 */
static void atcommand_synonym_free(void) {
	int i;

	for (i = 0; i < synonym_count; i++) {
		aFree(synonym_table[i].synonym);
		//synonym_table[i].synonym = NULL;
		aFree(synonym_table[i].command);
		//synonym_table[i].command = NULL;
	}
	if (synonym_table != NULL) {
		aFree(synonym_table);
		synonym_table = NULL;
	}
	synonym_count = 0;

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_config_read(const char *cfgName) {
	static int counter = 0;
	int i;
	AtCommandInfo* p;
	FILE* fp;
	char line[1024], w1[1024], w2[1024];

	if (counter == 0) {
		i = 0;
		while (atcommand_info[i].type != AtCommand_Unknown) {
			atcommand_info[i].level = 0;
			i++;
		}
		atcommand_info[i].level = 100; // AtCommand_Unknown
		atcommand_synonym_free();
		command_symbol = '@';
	}
	counter++;

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("file not found: %s\n", cfgName);
		counter--;
		return 1;
	}

	while (fgets(line, sizeof(line)-1, fp)) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if (sscanf(line, "%[^:]:%s", w1, w2) == 2) {
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
				} else
					printf("file [%s]: Unknown GM command: %c%s.\n", cfgName, command_symbol, w1);
			}

		} else if (sscanf(line, "%[^=]=%s", w1, w2) == 2) { // synonym
			/* searching if synonym is not a gm command */
			for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++)
				if (strcmpi(atcommand_info[i].command + 1, w1) == 0) {
					printf("Error in %s file: GM synonym '%s' is not a synonym, but a GM command.\n", cfgName, w1);
					break;
				}
			// if synonym is ok
			if (atcommand_info[i].type == AtCommand_Unknown) {
				/* searching if gm command exists */
				for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++)
					if (strcmpi(atcommand_info[i].command + 1, w2) == 0) {
						// GM command found, create synonym
						//printf("new synonym: %s->%s\n", w1, w2);
						if (synonym_count == 0) {
							synonym_table = (struct synonym_table*)aMalloc(sizeof(struct synonym_table));
						} else {
							synonym_table = (struct synonym_table*)aRealloc((void*)synonym_table, (synonym_count + 1) * sizeof(struct synonym_table));
						}
						synonym_table[synonym_count].synonym = (char*)aCalloc(strlen(w1) + 1, sizeof(char));
						strcpy(synonym_table[synonym_count].synonym, w1);
						synonym_table[synonym_count].command = (char*)aCalloc(strlen(w2) + 1, sizeof(char));
						strcpy(synonym_table[synonym_count].command, w2);
						synonym_count++;
						break;
					}
				if (atcommand_info[i].type == AtCommand_Unknown)
					printf("Error in %s file: GM command '%s' of synonym '%s' doesn't exist.\n", cfgName, w2, w1);
			}
		}
	}
	fclose(fp);

	counter--;
	if (counter == 0)
		printf("Symbol: '%c' for GM commands.\n", command_symbol);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void do_final_atcommand(void) {
	do_final_msg_config();
	atcommand_synonym_free();

	return;
}

// @ command 処理関数群

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_rurap(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char map_name[100];
	char character[100];
	int x, y, m;
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
		return -1;
	}

	if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
		if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13)
			strcat(map_name, ".gat");
		m = map_mapname2mapid(map_name);
		if (x < 0 || x >= 400 || y < 0 || y >= 400 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys))) {
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
int
atcommand_rura(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
	if (x < 0 || x >= 400 || y < 0 || y >= 400 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys)))
		clif_displaymessage(fd, msg_txt(2));
	else
		clif_displaymessage(fd, (pc_setpos(sd, map_name, x, y, 3) == 0) ? msg_txt(0) : msg_txt(1));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_where(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;
	if (strlen(character) > 24 || strncmp(sd->status.name, character, 24) == 0)
		return -1;

	intif_where(sd->status.account_id, character);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_jumpto(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;
	if (strlen(character) > 24 || strncmp(sd->status.name, character, 24) == 0)
		return -1;

	intif_jumpto(sd->status.account_id,character);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_jump(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int x, y;

	nullpo_retr(-1, sd);

	if (sscanf(message, "%d %d", &x, &y) < 2)
		return -1;

	if (x >= 0 && x < map[sd->bl.m].xs && y >= 0 && y < map[sd->bl.m].ys) {
		char output[200];
		pc_setpos(sd, sd->mapname, x, y, 3);
		snprintf(output, sizeof output, msg_txt(5), x, y);
		clif_displaymessage(fd, output);
	} else {
		clif_displaymessage(fd, msg_txt(2));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_who(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	map_who(fd);

	return 0;
}

/*==========================================
 * 居場所付き検索を行う
 *------------------------------------------
 */
int
atcommand_whop(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char output[200];
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) &&
		    pl_sd->state.auth) {
			if (!(battle_config.hide_GM_session && pc_isGM(pl_sd))) {
				snprintf(output, sizeof output, "%s [%d/%d] %s %d %d", 
					pl_sd->status.name, pl_sd->status.base_level, pl_sd->status.job_level, pl_sd->mapname, pl_sd->bl.x, pl_sd->bl.y);
				clif_displaymessage(fd, output);
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_save(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_setsavepoint(sd, sd->mapname, sd->bl.x, sd->bl.y);
	if (sd->status.pet_id > 0 && sd->pd)
		intif_save_petdata(sd->status.account_id, &sd->pet);
	pc_makesavestatus(sd);
	chrif_save(sd);
	storage_storage_save(sd);
	clif_displaymessage(fd, msg_txt(6));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_load(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	pc_setpos(sd, sd->status.save_point.map,
		sd->status.save_point.x, sd->status.save_point.y, 0);
	clif_displaymessage(fd, msg_txt(7));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_speed(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int speed;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	speed = atoi(message);
	if (speed > MIN_WALK_SPEED && speed < MAX_WALK_SPEED) {
		sd->speed = speed;
		//sd->walktimer = x;
		//この文を追加 by れあ
		clif_updatestatus(sd, SP_SPEED);
		clif_displaymessage(fd, msg_txt(8));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_storage(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	if (storage_storageopen(sd) == 1)
		clif_displaymessage(fd, msg_txt(130));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_guildstorage(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.guild_id > 0) {
		if (storage_guild_storageopen(sd) == 1)
			clif_displaymessage(fd, msg_txt(130));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_option(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int param1, param2 = 0, param3 = 0, param4 = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%d %d %d %d", &param1, &param2, &param3, &param4) < 1)
		return -1;

	sd->opt1 = param1;
	sd->opt2 = param2;
	sd->opt3 = param4;
	if (!(sd->status.option & CART_MASK) && param3 & CART_MASK) {
		clif_cart_itemlist(sd);
		clif_cart_equiplist(sd);
		clif_updatestatus(sd, SP_CARTINFO);
	}
	sd->status.option = param3;
	clif_changeoption(&sd->bl);
	clif_send_clothcolor(&sd->bl);
	clif_displaymessage(fd, msg_txt(9));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_hide(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.option & 0x40) {
		sd->status.option &= ~0x40;
		clif_displaymessage(fd, msg_txt(10));
	} else {
		sd->status.option |= 0x40;
		clif_displaymessage(fd, msg_txt(11));
	}
	clif_changeoption(&sd->bl);
	clif_send_clothcolor(&sd->bl);

	return 0;
}

/*==========================================
 * 転職する upperを指定すると転生や養子にもなれる
 *------------------------------------------
 */
int
atcommand_jobchange(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int job, upper = -1;
	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &job, &upper) < 1)
		return -1;

	if ((job >= 0 && job < MAX_VALID_PC_CLASS)) {
		if (job >= 24)
			upper = 0;
		if (pc_jobchange(sd, job, upper) == 0)
			clif_displaymessage(fd, msg_txt(12));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_die(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int
atcommand_kill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	sscanf(message, "%99[^\n]", character);
	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
			clif_displaymessage(fd, msg_txt(14));
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_alive(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
 * kami,kamib,kamic
 *------------------------------------------
 */
int
atcommand_kami(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char output[200];
	unsigned long color;

	if (!message || !*message)
		return -1;

	memset(output, '\0', sizeof output);
	if (*(command + 5) != 'c') {
		sscanf(message, "%199[^\n]", output);
		intif_GMmessage(output, strlen(output) + 1, (*(command + 5) == 'b') ? 0x10 : 0);
	} else {
		if (sscanf(message, "%lx %199[^\n]", &color, output) < 2)
			return -1;
		color = color & 0x00FFFFFF;
		intif_announce(output, strlen(output) + 1, color, 0);
	}

	return 0;
}

/*==========================================
 *叫ぶ
 *------------------------------------------
 */
int atcommand_onlymes(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char temp0[200];

	nullpo_retr(-1, sd);

	sscanf(message, "%199[^#\n]", temp0);
	clif_webchat_message(msg_txt(156), sd->status.name, temp0); // [mes]

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_heal(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int hp = 0, sp = 0;

	nullpo_retr(-1, sd);

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
int
atcommand_item(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char item_name[100];
	int number = 0, item_id = 0, flag = 0;
	struct item item_tmp;
	struct item_data *item_data;

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d", item_name, &number) < 1)
		return -1;
	if (number <= 0)
		number = 1;

	if ((item_id = atoi(item_name)) > 0) {
		if (battle_config.item_check) {
			item_id = (((item_data = itemdb_exists(item_id)) &&
			           itemdb_available(item_id)) ? item_id : 0);
		} else {
			item_data = itemdb_search(item_id);
		}
	} else if ((item_data = itemdb_searchname(item_name)) != NULL) {
		item_id = (!battle_config.item_check || itemdb_available(item_data->nameid)) ? item_data->nameid : 0;
	}

	if (item_id > 0) {
		int loop = 1, get_count = number,i;
		if (item_data->type == 4 || item_data->type == 5 ||
		    item_data->type == 7 || item_data->type == 8) {
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
int
atcommand_item2(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct item item_tmp;
	struct item_data *item_data;
	char item_name[100];
	int item_id = 0, number = 0;
	int identify = 0, refine = 0, attr = 0;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	int flag = 0;

	if (sscanf(message, "%99s %d %d %d %d %d %d %d %d", item_name, &number,
	    &identify, &refine, &attr, &c1, &c2, &c3, &c4) >= 9) {
		if (number <= 0)
			number = 1;
		if (battle_config.itemidentify)
			identify = 1;
		if ((item_id = atoi(item_name)) > 0) {
			if (battle_config.item_check) {
				item_id = (((item_data = itemdb_exists(item_id)) && itemdb_available(item_id)) ? item_id : 0);
			} else {
				item_data = itemdb_search(item_id);
			}
		} else if ((item_data = itemdb_searchname(item_name)) != NULL) {
			item_id = (!battle_config.item_check || itemdb_available(item_data->nameid)) ? item_data->nameid : 0;
		}

		if (item_id > 0) {
			int loop = 1, get_count = number, i = 0;

			if (item_data->type == 4 || item_data->type == 5 ||
			    item_data->type == 7 || item_data->type == 8) {
				loop = number;
				get_count = 1;
				if (item_data->type == 7) {
					identify = 1;
					refine = 0;
				}
				if (item_data->type == 8)
					refine = 0;
				if (refine > 10)
					refine = 10;
			} else {
				identify = 1;
				refine = 0;
				attr = 0;
			}
			for (i = 0; i < loop; i++) {
				memset(&item_tmp, 0, sizeof(item_tmp));
				item_tmp.nameid = item_id;
				item_tmp.identify = identify;
				item_tmp.refine = refine;
				item_tmp.attribute = attr;
				item_tmp.card[0] = c1;
				item_tmp.card[1] = c2;
				item_tmp.card[2] = c3;
				item_tmp.card[3] = c4;
				if ((flag = pc_additem(sd, &item_tmp, get_count)))
					clif_additem(sd, 0, 0, flag);
			}
			clif_displaymessage(fd, msg_txt(18));
		} else {
			clif_displaymessage(fd, msg_txt(19));
			return -1;
		}
	} else {
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_item3(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	struct item item_tmp;
	struct item_data *item_data;
	char item_name[100];
	char character[64];
	int item_id = 0, number = 0;
	int flag = 0,equip_item = 0;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99s %d %99[^\n]", item_name, &number, character) == 3) {
		if (number <= 0)
			number = 1;
		if ((pl_sd = map_nick2sd(character)) == NULL) {
			clif_displaymessage(fd, msg_txt(3));
			return -1;
		}

		if ((item_id = atoi(item_name)) > 0) {
			if (battle_config.item_check) {
				item_id = (((item_data = itemdb_exists(item_id)) && itemdb_available(item_id)) ? item_id : 0);
			} else {
				item_data = itemdb_search(item_id);
			}
		} else if ((item_data = itemdb_searchname(item_name)) != NULL) {
			item_id = (!battle_config.item_check || itemdb_available(item_data->nameid)) ? item_data->nameid : 0;
		}

		if (item_id > 0) {
			int loop = 1, get_count = number, i = 0;

			if (item_data->type == 4 || item_data->type == 5 ||
			    item_data->type == 7 || item_data->type == 8) {
				loop = number;
				get_count = 1;
				equip_item = 1;
			}
			for (i = 0; i < loop; i++) {
				memset(&item_tmp, 0, sizeof(item_tmp));
				item_tmp.nameid = item_id;
				item_tmp.identify = 1;
				item_tmp.refine = 0;
				item_tmp.attribute = 0;
				item_tmp.card[0] = (equip_item) ? 0x00ff : 0x00fe;
				item_tmp.card[1] = 0;
				*((unsigned long *)(&item_tmp.card[2])) = pl_sd->char_id;
				if ((flag = pc_additem(sd, &item_tmp, get_count)))
					clif_additem(sd, 0, 0, flag);
			}
			clif_displaymessage(fd, msg_txt(18));
		} else {
			clif_displaymessage(fd, msg_txt(19));
			return 1;
		}
	} else
		return 1;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_itemreset(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].amount &&
		    sd->status.inventory[i].equip == 0)
			pc_delitem(sd, i, sd->status.inventory[i].amount, 0);
	}
	clif_displaymessage(fd, msg_txt(20));

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_charitemreset(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i = 0;
	char character[100];
	struct map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	memset(character, '\0', sizeof character);
	if (!message || !*message || sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		for (i = 0; i < MAX_INVENTORY; i++) {
			if (pl_sd->status.inventory[i].amount &&
			    pl_sd->status.inventory[i].equip == 0)
				pc_delitem(pl_sd, i, pl_sd->status.inventory[i].amount, 0);
		}
		clif_displaymessage(fd, msg_txt(20));
		clif_displaymessage(pl_sd->fd, msg_txt(20));
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_baselevelup(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int level, i;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	level = atoi(message);
	if (level > (int)MAX_LEVEL)
		level = (int)MAX_LEVEL;
	else if (level < (int)(-MAX_LEVEL))
		level = (int)(-MAX_LEVEL);

	if (level > 0) {
		if ((int)sd->status.base_level + level > (int)MAX_LEVEL)
			level = (int)MAX_LEVEL - (int)sd->status.base_level;
		if (level <= 0)
			return -1;
		for (i = 1; i <= level; i++)
			sd->status.status_point += (sd->status.base_level + i + 14) / 5;
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
int
atcommand_joblevelup(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int up_level, level;
	//転生や養子の場合の元の職業を算出する
	struct pc_base_job s_class;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	s_class = pc_calc_base_job(sd->status.class);
	up_level = max_job_table[s_class.upper][s_class.job];

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
static void atcommand_help_sub(const int fd, const char *message, char *filename)
{
	FILE* fp;
	char * p;
	char buf[BUFSIZ];
	char buf2[BUFSIZ];
	int display = 1;
	int i;

	fp = fopen(filename, "r");
	if (fp != NULL) {
		clif_displaymessage(fd, msg_txt(26));
		memset(buf, 0, sizeof(buf));
		while (fgets(buf, sizeof buf - 20, fp) != NULL) {
			for (i = 0; buf[i] != '\0'; i++) {
				if (buf[i] == '\r' || buf[i] == '\n') {
					buf[i] = '\0';
					break;
				}
			}
			if (message && *message && buf[0] == '@') {
				if (strstr(buf, message)) {
					display = 1;
				} else {
					display = 0;
					continue;
				}
			}
			if (display) {
				p = buf;
				while ((p = strchr(p, '@')) != NULL) {
					for (i = 0; i < synonym_count; i++) {
						memcpy(buf2, p + 1, strlen(synonym_table[i].synonym));
						buf2[strlen(synonym_table[i].synonym)] = 0;
						if (strcmpi(buf2, synonym_table[i].synonym) == 0) { // strncmpi will be better, but doesn't work under win32 (bcc32 don't recognize strncasecmp)
							*p = command_symbol;
							break;
						}
					}
					if (i == synonym_count) {
						for (i = 0; atcommand_info[i].type != AtCommand_Unknown; i++) {
							memcpy(buf2, p + 1, strlen(atcommand_info[i].command + 1));
							buf2[strlen(atcommand_info[i].command + 1)] = 0;
							if (strcmpi(buf2, atcommand_info[i].command + 1) == 0) { // strncmpi will be better, but doesn't work under win32 (bcc32 don't recognize strncasecmp)
								*p = command_symbol;
								break;
							}
						}
					}
					p++;
				}
				clif_displaymessage(fd, buf);
			}
		}
		fclose(fp);
	} else
		clif_displaymessage(fd, msg_txt(27));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_help(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	atcommand_help_sub(fd, message, help_txt);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */

int
atcommand_help1(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[] = "conf/help1.txt";

	atcommand_help_sub(fd, message, name);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */

int
atcommand_help2(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[] = "conf/help2.txt";

	atcommand_help_sub(fd, message, name);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */

int
atcommand_help3(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[] = "conf/help3.txt";

	atcommand_help_sub(fd, message, name);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */

int
atcommand_help4(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[] = "conf/help4.txt";

	atcommand_help_sub(fd, message, name);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_gm(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char password[100];

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(password, '\0', sizeof password);
	sscanf(message, "%99[^\n]", password);
	if (sd->status.party_id)
		clif_displaymessage(fd, msg_txt(28));
	else if (sd->status.guild_id)
		clif_displaymessage(fd, msg_txt(29));
	else {
		if (sd->status.pet_id > 0 && sd->pd)
			intif_save_petdata(sd->status.account_id, &sd->pet);
		pc_makesavestatus(sd);
		chrif_save(sd);
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
int
atcommand_pvpoff(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	if (map[sd->bl.m].flag.pvp) {
		map[sd->bl.m].flag.pvp = 0;
		clif_send0199(sd->bl.m, 0);
		for (i = 0; i < fd_max; i++) {	//人数分ループ
			if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
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
int
atcommand_pvpon(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	if (!map[sd->bl.m].flag.pvp) {
		map[sd->bl.m].flag.pvp = 1;
		clif_send0199(sd->bl.m, 1);
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
				if (sd->bl.m == pl_sd->bl.m && pl_sd->pvp_timer == -1) {
					pl_sd->pvp_timer = add_timer(gettick() + 200,pc_calc_pvprank_timer, pl_sd->bl.id, 0);
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
int
atcommand_gvgoff(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int
atcommand_gvgon(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int
atcommand_model(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int hair_style, hair_color = 0, cloth_color = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d %d", &hair_style, &hair_color, &cloth_color) < 1)
		return -1;

	if (hair_style  >= 0 && hair_style  < MAX_HAIR_STYLE &&
	    hair_color  >= 0 && hair_color  < MAX_HAIR_COLOR &&
	    cloth_color >= 0 && cloth_color < MAX_CLOTH_COLOR) {
		//服の色変更
		if (MAX_CLOTH_COLOR <= 5 && cloth_color != 0 && sd->sex == 1 &&
			(sd->status.class == 12 ||  sd->status.class == 17)
		) {
			//服の色未実装職の判定
			clif_displaymessage(fd, msg_txt(35));
		} else {
			pc_changelook(sd, LOOK_HAIR, hair_style);
			pc_changelook(sd, LOOK_HAIR_COLOR, hair_color);
			pc_changelook(sd, LOOK_CLOTHES_COLOR, cloth_color);
			clif_displaymessage(fd, msg_txt(36));
		}
	} else {
		clif_displaymessage(fd, msg_txt(37));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_go(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int town = 0;
	struct { char map_name[16]; int x,y; } data[] = {
		{	"prontera.gat",   156, 191	},	//	0=プロンテラ
		{	"morocc.gat",     156,  93	},	//	1=モロク
		{	"geffen.gat",     119,  59	},	//	2=ゲフェン
		{	"payon.gat",      174, 104	},	//	3=フェイヨン
		{	"alberta.gat",    192, 147	},	//	4=アルベルタ
		{	"izlude.gat",     128, 114	},	//	5=イズルード
		{	"aldebaran.gat",  140, 131	},	//	6=アルデバラン
		{	"xmas.gat",       147, 134	},	//	7=ルティエ
		{	"comodo.gat",     209, 143	},	//	8=コモド
		{	"yuno.gat",       157,  51	},	//	9=ジュノー
		{	"amatsu.gat",     198,  84	},	//	10=アマツ
		{	"gonryun.gat",    160, 120	},	//	11=コンロン
		{	"umbala.gat",      89, 157	},	//	12=ウンバラ
		{	"niflheim.gat",   202, 177	},	//	13=ニブルヘルム
		{	"louyang.gat",    217,  40	},	//	14=龍之城
		{	"jawaii.gat",     241, 116	},	//	15=ジャワイ
		{	"ayothaya.gat",   217, 187	},	//	16=アユタヤ
		{	"einbroch.gat",   149,  38	},	//	17=アインブロック(南口)
		{	"einbroch.gat",   158, 317	},	//	18=アインブロック(北口)
		{	"einbech.gat",    103, 197	},	//	19=アインベフ
		{	"lighthalzen.gat",214, 322	},	//	20=リヒタルゼン
		{	"hugel.gat",       95,  63	},	//	21=フィゲル
		{	"rachel.gat",     131, 115	},	//	22=ラヘル
	};

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	town = atoi(message);
	if (town >= 0 &&
	    town <= battle_config.atcommand_go_significant_values &&
	    town < (int)(sizeof(data) / sizeof(data[0]))) {
		pc_setpos(sd, data[town].map_name, data[town].x, data[town].y, 3);
	} else {
		clif_displaymessage(fd, msg_txt(38));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_monster(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[100];
	char monster[100];
	int mob_id = 0;
	int number = 0;
	int x = 0;
	int y = 0;
	int count = 0;
	int i = 0;
	int on_map = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "\"%[^\"]\" %s %d %d %d", name, monster, &number, &x, &y) < 2 &&
	    sscanf(message, "%s \"%[^\"]\" %d %d %d", monster, name, &number, &x, &y) < 2 &&
	    sscanf(message, "%99s %99s %d %d %d", name, monster, &number, &x, &y) < 2)
		return -1;

	if ((mob_id = atoi(monster)) == 0)
		mob_id = mobdb_searchname(monster);
	if (number <= 0)
		number = 1;
	// check for command @monster/@monstermap
	if (strstr(command, "map") != NULL)
		on_map = 1;

	if (battle_config.etc_log) {
		if (on_map)
			printf("%s monster=%s name=%s id=%d count=%d (on entire map)\n",
				command, monster, name, mob_id, number);
		else
			printf("%s monster=%s name=%s id=%d count=%d (%d,%d)\n",
				command, monster, name, mob_id, number, x, y);
	}

	for (i = 0; i < number; i++) {
		int mx = 0, my = 0;
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
		count += (mob_once_spawn(sd, "this", mx, my, name, mob_id, 1, "") != 0) ? 1 : 0;
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
static int atkillmonster_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md = NULL;
	int flag = va_arg(ap, int);

	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (md = (struct mob_data *)bl)) {
		if (flag)
			mob_damage(NULL, md, md->hp, 2);
		else
			unit_remove_map(&md->bl, 1);
	}
	return 0;
}

void
atcommand_killmonster_sub(
	const int fd, struct map_session_data* sd, const char* message,
	const int drop)
{
	int map_id = 0;

	nullpo_retv(sd);

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
	map_foreachinarea(atkillmonster_sub, map_id, 0, 0,
		map[map_id].xs, map[map_id].ys, BL_MOB, drop);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_killmonster(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	atcommand_killmonster_sub(fd, sd, message, 1);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_killmonster2(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	atcommand_killmonster_sub(fd, sd, message, 0);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_refine(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;
	int position, refine, current_position, current_refine;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &position, &refine) < 2)
		return -1;

	if (refine < -10)
		refine = -10;
	else if (refine > 10)
		refine = 10;
	else if (refine == 0)
		refine = 1;

	for(i = 0; i < MAX_INVENTORY; i++) {
		struct item *data = &sd->status.inventory[i];

		if (data->nameid == 0)
			continue;
		if (!data->equip)
			continue;
		if (position && !(data->equip & position))
			continue;
		current_refine = data->refine;
		data->refine += refine;
		if (data->refine > 10)
			data->refine = 10;
		else if (data->refine < 0)
			data->refine = 0;
		if (current_refine == data->refine)
			continue;
		current_position = data->equip;
		pc_unequipitem(sd, i, 0);
		clif_refine(fd, sd, 0, i, data->refine);
		clif_delitem(sd, i, 1);
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
int
atcommand_produce(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char item_name[100];
	int item_id = 0, attribute = 0, star = 0;
	int flag = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s %d %d", item_name, &attribute, &star) > 0) {
		if ((item_id = atoi(item_name)) == 0) {
			struct item_data *item_data = itemdb_searchname(item_name);
			if (item_data)
				item_id = item_data->nameid;
		}
		if (itemdb_exists(item_id) &&
		    (item_id <=  500 || item_id >  1099) &&
		    (item_id <  4001 || item_id >  4148) &&
		    (item_id <  7001 || item_id > 10019) &&
			itemdb_isequip(item_id)) {
			struct item tmp_item;
			if (attribute < MIN_ATTRIBUTE || attribute > MAX_ATTRIBUTE)
				attribute = ATTRIBUTE_NORMAL;
			if (star < MIN_STAR || star > MAX_STAR)
				star = 0;
			memset(&tmp_item, 0, sizeof tmp_item);
			tmp_item.nameid = item_id;
			tmp_item.amount = 1;
			tmp_item.identify = 1;
			tmp_item.card[0] = 0x00ff;
			tmp_item.card[1] = ((star * 5) << 8) + attribute;
			*((unsigned long *)(&tmp_item.card[2])) = sd->char_id;
			clif_produceeffect(sd, 0, item_id); // 製造エフェクトパケット
			clif_misceffect(&sd->bl, 3); // 他人にも成功を通知
			if ((flag = pc_additem(sd, &tmp_item, 1)))
				clif_additem(sd, 0, 0, flag);
		} else {
			if (battle_config.error_log)
				printf("%cproduce NOT WEAPON [%d]\n", command_symbol, item_id);
			return -1;
		}
	}

	return 0;
}

/*==========================================
 * 壊れた武具を全て修理する
 *------------------------------------------
 */
int atcommand_repair(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int count, i;

	nullpo_retr(-1, sd);

	count = 0;
	for(i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].nameid && sd->status.inventory[i].attribute) {
			sd->status.inventory[i].attribute = 0;
			clif_item_repaireffect(sd, 0, sd->status.inventory[i].nameid);
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
int
atcommand_memo(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int position = 0;

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
int
atcommand_gat(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char output[64];
	int y = 0;

	nullpo_retr(-1, sd);

	for (y = 2; y >= -2; y--) {
		snprintf(output, sizeof output,
			"%s (x= %d, y= %d) %02X %02X %02X %02X %02X",
			map[sd->bl.m].name, sd->bl.x - 2, sd->bl.y + y,
			map_getcell(sd->bl.m, sd->bl.x - 2, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x - 1, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x,     sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x + 1, sd->bl.y + y, CELL_GETTYPE),
			map_getcell(sd->bl.m, sd->bl.x + 2, sd->bl.y + y, CELL_GETTYPE));
		clif_displaymessage(fd, output);
	}

	return 0;
}

/*==========================================
 * 指定パケットを折り返し送りつける（デバッグ）
 *------------------------------------------
 */
int
atcommand_packet(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int
atcommand_statuspoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int point = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (point > 0 || sd->status.status_point + point >= 0) {
		sd->status.status_point += point;
		clif_updatestatus(sd, SP_STATUSPOINT);
	} else {
		clif_displaymessage(fd, msg_txt(41));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_skillpoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int point = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	point = atoi(message);
	if (point > 0 || sd->status.skill_point + point >= 0) {
		sd->status.skill_point += point;
		clif_updatestatus(sd, SP_SKILLPOINT);
	} else {
		clif_displaymessage(fd, msg_txt(41));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_zeny(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int zeny = 0;

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
		return -1;
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
int
atcommand_param(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i = 0, value = 0, index = -1, new_value = 0;
	int max_parameter[6];

	const char* param[] = {
		"@str", "@agi", "@vit", "@int", "@dex", "@luk", NULL
	};
	short* status[6];
	status[0] = &sd->status.str;
	status[1] = &sd->status.agi;
	status[2] = &sd->status.vit;
	status[3] = &sd->status.int_;
	status[4] = &sd->status.dex;
	status[5] = &sd->status.luk;

	max_parameter[0] = battle_config.max_parameter_str;
	max_parameter[1] = battle_config.max_parameter_agi;
	max_parameter[2] = battle_config.max_parameter_vit;
	max_parameter[3] = battle_config.max_parameter_int;
	max_parameter[4] = battle_config.max_parameter_dex;
	max_parameter[5] = battle_config.max_parameter_luk;

	if (!message || !*message)
		return -1;
	value = atoi(message);

	for (i = 0; param[i] != NULL; i++) {
		if (strcmpi(command + 1, param[i] + 1) == 0) {
			index = i;
			break;
		}
	}
	if (index < 0)
		return -1;

	new_value = (int)(*status[index]) + value;
	if (new_value < 1)
		value = 1 - *status[index];
	if (new_value > max_parameter[index])
		value = max_parameter[index] - *status[index];
	*status[index] += value;

	clif_updatestatus(sd, SP_STR + index);
	clif_updatestatus(sd, SP_USTR + index);
	status_calc_pc(sd, 0);
	clif_displaymessage(fd, msg_txt(42));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_guildlevelup(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int level = 0;
	struct guild *guild_info = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	level = atoi(message);
	if (sd->status.guild_id <= 0 ||
	    (guild_info = guild_search(sd->status.guild_id)) == NULL) {
		clif_displaymessage(fd, msg_txt(43));
		return 0;
	}
	if (strcmp(sd->status.name, guild_info->master) != 0) {
		clif_displaymessage(fd, msg_txt(44));
		return 0;
	}

	if (guild_info->guild_lv + level >= 1 &&
		guild_info->guild_lv + level <= MAX_GUILDLEVEL)
		intif_guild_change_basicinfo(guild_info->guild_id, GBI_GUILDLV, &level, 2);
	else {
		clif_displaymessage(fd, msg_txt(41));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_makepet(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int id = 0, pet_id = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if ((id = atoi(message)) == 0)
		 id = mobdb_searchname(message);
	pet_id = search_petDB_index(id, PET_CLASS);
	if (pet_id < 0)
		pet_id = search_petDB_index(id, PET_EGG);
	if (pet_id >= 0) {
		sd->catch_target_class = pet_db[pet_id].class;
		intif_create_pet(sd->status.account_id, sd->status.char_id,
		                 pet_db[pet_id].class, mob_db[pet_db[pet_id].class].lv,
		                 pet_db[pet_id].EggID, 0, pet_db[pet_id].intimate,
		                 100, 0, 1, pet_db[pet_id].jname);
	} else {
		return -1;
	}

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int atcommand_hatch(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	if (sd->status.pet_id <= 0)
		clif_sendegg(sd);
	else
		return -1;

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_petfriendly(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int friendly = 0;

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
int
atcommand_pethungry(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int hungry = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	hungry = atoi(message);
	if (sd->status.pet_id > 0 && sd->pd) {
		sd->pet.hungry = hungry;
		if (sd->pet.hungry < 0)
			sd->pet.hungry = 0;
		else if (sd->pet.hungry > 100)
			sd->pet.hungry = 100;
		clif_send_petstatus(sd);
	} else
		return -1;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_petrename(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	if (sd->status.pet_id > 0 && sd->pd) {
		sd->pet.rename_flag = 0;
		intif_save_petdata(sd->status.account_id, &sd->pet);
		clif_send_petstatus(sd);
		clif_displaymessage(fd, msg_txt(123));
	} else
		return -1;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charpetrename(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pl_sd->status.pet_id > 0 && pl_sd->pd) {
			if (pl_sd->pet.rename_flag != 0) {
				pl_sd->pet.rename_flag = 0;
				intif_save_petdata(pl_sd->status.account_id, &pl_sd->pet);
				clif_send_petstatus(pl_sd);
				clif_displaymessage(fd, msg_txt(123));
			} else {
				return -1;
			}
		} else {
			return -1;
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_recall(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
//	struct map_session_data *pl_sd = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;
	if (strlen(character) > 24 || strncmp(sd->status.name, character, 24) == 0)
		return -1;

	intif_charmovereq(sd,character,1);

	return 0;
}

/*==========================================
 * recallを接続者全員にかける
 *------------------------------------------
 */
int atcommand_recallall(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;
	char output[200];

	memset(output, '\0', sizeof(output));

	for (i = 0; i < fd_max; i++)
		if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth &&
		    sd->status.account_id != pl_sd->status.account_id &&
		    pc_isGM(sd) >= pc_isGM(pl_sd))
				pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
//				intif_charmovereq(sd,pl_sd->status.name,1);

	clif_displaymessage(fd, msg_txt(105));

	return 0;
}
/*==========================================
 * Recall online characters of a guild to your location
 *------------------------------------------
 */
int atcommand_recallguild(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;
	char guild_name[100];
	char output[200];
	struct guild *g;

	memset(guild_name, '\0', sizeof(guild_name));
	memset(output, '\0', sizeof(output));

	if (!message || !*message || sscanf(message, "%99[^\n]", guild_name) < 1)
		return -1;

	if ((g = guild_searchname(guild_name)) != NULL ||
	    (g = guild_search(atoi(message))) != NULL) {
		for (i = 0; i < fd_max; i++)
			if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth &&
			    sd->status.account_id != pl_sd->status.account_id &&
			    pl_sd->status.guild_id == g->guild_id)
				pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
		sprintf(output, msg_txt(106), g->name);
		clif_displaymessage(fd, output);
	} else {
		clif_displaymessage(fd, msg_txt(107));
		return -1;
	}

	return 0;
}

/*==========================================
 * Recall online characters of a party to your location
 *------------------------------------------
 */
int atcommand_recallparty(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;
	struct map_session_data *pl_sd;
	char party_name[100];
	char output[200];
	struct party *p;

	memset(party_name, '\0', sizeof(party_name));
	memset(output, '\0', sizeof(output));

	if (!message || !*message || sscanf(message, "%99[^\n]", party_name) < 1)
		return -1;

	if ((p = party_searchname(party_name)) != NULL ||
	    (p = party_search(atoi(message))) != NULL) {
		for (i = 0; i < fd_max; i++)
			if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth &&
			    sd->status.account_id != pl_sd->status.account_id &&
			    pl_sd->status.party_id == p->party_id)
				pc_setpos(pl_sd, sd->mapname, sd->bl.x, sd->bl.y, 2);
		sprintf(output, msg_txt(108), p->name);
		clif_displaymessage(fd, output);
	} else {
		clif_displaymessage(fd, msg_txt(109));
		return -1;
	}

	return 0;
}
/*==========================================
 * 対象キャラクターを転職させる upper指定で転生や養子も可能
 *------------------------------------------
 */
int
atcommand_character_job(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	struct map_session_data* pl_sd;
	int job, upper;

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%d %d %99[^\n]", &job, &upper, character) < 3){ //upper指定してある
		upper = -1;
		if (sscanf(message, "%d %99[^\n]", &job, character) < 2) //upper指定してない上に何か足りない
			return -1;
	}

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			if ((job >= 0 && job < MAX_VALID_PC_CLASS)) {
				if (job >= 24)
					upper = 0;
				pc_jobchange(pl_sd, job, upper);
				clif_displaymessage(fd, msg_txt(48));
			} else {
				clif_displaymessage(fd, msg_txt(49));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_revive(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	sscanf(message, "%99[^\n]", character);
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
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_character_stats(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	sscanf(message, "%99[^\n]", character);
	if ((pl_sd = map_nick2sd(character)) != NULL) {
		char output[200];
		int i = 0;
		struct {
			const char* format;
			int value;
		} output_table[14];

		output_table[ 0].format = msg_txt(158); output_table[ 0].value = pl_sd->status.base_level; // Base Level: %d
		output_table[ 1].format = msg_txt(159); output_table[ 1].value = pl_sd->status.job_level; // Job Level: %d
		output_table[ 2].format = msg_txt(160); output_table[ 2].value = pl_sd->status.hp; // Hp: %d
		output_table[ 3].format = msg_txt(161); output_table[ 3].value = pl_sd->status.max_hp; // MaxHp: %d
		output_table[ 4].format = msg_txt(162); output_table[ 4].value = pl_sd->status.sp; // Sp: %d
		output_table[ 5].format = msg_txt(163); output_table[ 5].value = pl_sd->status.max_sp; // MaxSp: %d
		output_table[ 6].format = msg_txt(164); output_table[ 6].value = pl_sd->status.str; // Str: %d
		output_table[ 7].format = msg_txt(165); output_table[ 7].value = pl_sd->status.agi; // Agi: %d
		output_table[ 8].format = msg_txt(166); output_table[ 8].value = pl_sd->status.vit; // Vit: %d
		output_table[ 9].format = msg_txt(167); output_table[ 9].value = pl_sd->status.int_; // Int: %d
		output_table[10].format = msg_txt(168); output_table[10].value = pl_sd->status.dex; // Dex: %d
		output_table[11].format = msg_txt(169); output_table[11].value = pl_sd->status.luk; // Luk: %d
		output_table[12].format = msg_txt(170); output_table[12].value = pl_sd->status.zeny; // Zeny: %d
		output_table[13].format = NULL;         output_table[13].value = 0;

		snprintf(output, sizeof output, msg_txt(53), pl_sd->status.name);
		clif_displaymessage(fd, output);
		for (i = 0; output_table[i].format != NULL; i++) {
			snprintf(output, sizeof output, output_table[i].format, output_table[i].value);
			clif_displaymessage(fd, output);
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_character_option(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	int opt1, opt2, opt3;
	struct map_session_data* pl_sd;

	if (!message || !*message)
		return -1;
	memset(character, '\0', sizeof character);
	if (sscanf(message, "%d %d %d %99[^\n]", &opt1, &opt2, &opt3, character) < 4 || opt1 < 0 || opt2 < 0 || opt3 < 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pl_sd->opt1 = opt1;
			pl_sd->opt2 = opt2;
			pl_sd->status.option = opt3;
			clif_changeoption(&pl_sd->bl);
			clif_send_clothcolor(&pl_sd->bl);
			clif_displaymessage(fd, msg_txt(55));
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_character_save(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char map_name[100];
	char character[100];
	struct map_session_data* pl_sd;
	int x, y, m;

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99s %d %d %99[^\n]", map_name, &x, &y, character) < 4)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) {
				strcat(map_name, ".gat");
			}
			m = map_mapname2mapid(map_name);
			if (x < 0 || x >= 400 || y < 0 || y >= 400 || (m >= 0 && (x >= map[m].xs || y >= map[m].ys))) {
				clif_displaymessage(fd, msg_txt(2));
				return -1;
			} else {
				pc_setsavepoint(pl_sd, map_name, x, y);
				clif_displaymessage(fd, msg_txt(57));
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_night(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for(i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
			pl_sd->opt2 |= 0x10;
			clif_changeoption(&pl_sd->bl);
			clif_send_clothcolor(&pl_sd->bl);
			clif_displaymessage(pl_sd->fd, msg_txt(59));
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_day(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for(i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
			pl_sd->opt2 &= ~0x10;
			clif_changeoption(&pl_sd->bl);
			clif_send_clothcolor(&pl_sd->bl);
			clif_displaymessage(pl_sd->fd, msg_txt(60));
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_doom(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	for(i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
			pl_sd = session[i]->session_data;
			if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
				pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
				clif_displaymessage(pl_sd->fd, msg_txt(61));
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_doommap(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) &&
		    pl_sd->state.auth && sd->bl.m == pl_sd->bl.m &&
		    pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
			clif_displaymessage(pl_sd->fd, msg_txt(61));
		}
	}
	clif_displaymessage(fd, msg_txt(62));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void
atcommand_raise_sub(struct map_session_data* sd)
{
	if (sd && sd->state.auth && unit_isdead(&sd->bl)) {
		sd->status.hp = sd->status.max_hp;
		sd->status.sp = sd->status.max_sp;
		pc_setstand(sd);
		clif_updatestatus(sd, SP_HP);
		clif_updatestatus(sd, SP_SP);
		clif_resurrection(&sd->bl, 1);
		clif_displaymessage(sd->fd, msg_txt(63));
	}
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_raise(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;

	for (i = 0; i < fd_max; i++) {
		if (session[i])
			atcommand_raise_sub(session[i]->session_data);
	}
	clif_displaymessage(fd, msg_txt(64));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_raisemap(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) &&
		    pl_sd->state.auth && unit_isdead(&pl_sd->bl) && sd->bl.m == pl_sd->bl.m)
			atcommand_raise_sub(pl_sd);
	}
	clif_displaymessage(fd, msg_txt(64));

	return 0;
}

/*==========================================
 * atcommand_character_baselevel @charbaselvlで対象キャラのレベルを上げる
 *------------------------------------------
*/
int
atcommand_character_baselevel(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	char character[100];
	int level = 0, i = 0;

	if (!message || !*message) //messageが空ならエラーを返して終了
		return -1; //エラーを返して終了

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%d %99[^\n]", &level, character) < 2) //messageにLevelとキャラ名が無ければ
		return -1; //エラーを返して終了

	if ((pl_sd = map_nick2sd(character)) != NULL) { //該当名のキャラが存在する
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) { //対象キャラのGMレベルが自分より小さい
			if (level > 0) { //上げるレベルが１より大きい
				if ((int)pl_sd->status.base_level + level > (int)MAX_LEVEL)
					level = (int)MAX_LEVEL - (int)pl_sd->status.base_level;
				if (level <= 0)
					return -1;
				for (i = 1; i <= level; i++) //入力されたレベル回ステータスポイントを追加する
					pl_sd->status.status_point += (pl_sd->status.base_level + i + 14) / 5 ;
				pl_sd->status.base_level += level; //対象キャラのベースレベルを上げる
				clif_updatestatus(pl_sd, SP_BASELEVEL); //クライアントに上げたベースレベルを送る
				clif_updatestatus(pl_sd, SP_NEXTBASEEXP); //クライアントに次のベースレベルアップまでの必要経験値を送る
				clif_updatestatus(pl_sd, SP_STATUSPOINT); //クライアントにステータスポイントを送る
				status_calc_pc(pl_sd, 0); //ステータスを計算しなおす
				pc_heal(pl_sd, pl_sd->status.max_hp, pl_sd->status.max_sp); //HPとSPを完全回復させる
				clif_misceffect(&pl_sd->bl, 0); //ベースレベルアップエフェクトの送信
				clif_displaymessage(fd, msg_txt(65)); //レベルを上げたメッセージを表示する
			} else if (level < 0) {
				if ((int)pl_sd->status.base_level + level <= 0)
					level = 1 - (int)pl_sd->status.base_level;
				if (level >= 0)
					return -1;
				pl_sd->status.base_level += level; //対象キャラのレベルを下げる
				clif_updatestatus(pl_sd, SP_BASELEVEL); //クライアントに下げたベースレベルを送る
				clif_updatestatus(pl_sd, SP_NEXTBASEEXP); //クライアントに次のベースレベルアップまでの必要経験値を送る
				status_calc_pc(pl_sd, 0); //ステータスを計算しなおす
				clif_displaymessage(fd, msg_txt(66)); //レベルを下げたメッセージを表示する
			}
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0; //正常終了
}

/*==========================================
 * atcommand_character_joblevel @charjoblvlで対象キャラのJobレベルを上げる
 *------------------------------------------
 */
int
atcommand_character_joblevel(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	char character[100];
	int max_level = 50, level = 0;
	//転生や養子の場合の元の職業を算出する
	struct pc_base_job pl_s_class;

	if (!message || !*message)
		return -1;
	memset(character, '\0', sizeof character);
	if (sscanf(message, "%d %99[^\n]", &level, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		pl_s_class = pc_calc_base_job(pl_sd->status.class);
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			max_level = max_job_table[pl_s_class.upper][pl_s_class.job];
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
		return -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_kick(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];

	if (!message || !*message)
		return -1;
	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) == NULL) {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
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
int
atcommand_kickall(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] &&
			(pl_sd = session[i]->session_data) && pl_sd->state.auth) {
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
int
atcommand_allskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	pc_allskillup(sd);
	clif_displaymessage(fd, msg_txt(76));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_questskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int skill_id;

	if (!message || !*message)
		return -1;

	skill_id = atoi(message);
	if (skill_get_inf2(skill_id) & 0x01) {
		pc_skill(sd, skill_id, 1, 0);
		clif_displaymessage(fd, msg_txt(70));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charquestskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	char output[100];
	struct map_session_data *pl_sd;
	int skill_id = 0;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%d %99[^\n]", &skill_id, character) < 2 || skill_id < 0)
		return -1;

	if (skill_id >= 0 && skill_id < MAX_SKILL_DB) {
		if(skill_get_inf2(skill_id) & 0x01
		   && (pl_sd = map_nick2sd(character)) != NULL
		   && pc_checkskill2(pl_sd, skill_id) == 0){
				pc_skill(pl_sd, skill_id, 1, 0);
				sprintf(output, msg_txt(110), pl_sd->status.name);
				clif_displaymessage(fd, output);
		} else {
			clif_displaymessage(fd, msg_txt(3));
			return -1;
		}
	} else
		return -1;

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_lostskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int skill_id = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	skill_id = atoi(message);
	if (skill_id > 0 && skill_id < MAX_SKILL &&
		pc_checkskill2(sd, skill_id) == 0)
		return -1;
	sd->status.skill[skill_id].lv = 0;
	sd->status.skill[skill_id].flag = 0;
	clif_skillinfoblock(sd);
	clif_displaymessage(fd, msg_txt(71));

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int atcommand_charlostskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	char output[100];
	struct map_session_data *pl_sd;
	int skill_id = 0;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%d %99[^\n]", &skill_id, character) < 2 || skill_id < 0)
		return -1;

	if (skill_id >= 0 && skill_id < MAX_SKILL) {
		if (skill_get_inf2(skill_id) & 0x01
			&& (pl_sd = map_nick2sd(character)) != NULL
			&& pc_checkskill2(pl_sd, skill_id) > 0) {
				pl_sd->status.skill[skill_id].lv = 0;
				pl_sd->status.skill[skill_id].flag = 0;
				clif_skillinfoblock(pl_sd);
				sprintf(output, msg_txt(111), pl_sd->status.name);
				clif_displaymessage(fd, output);
		} else {
			clif_displaymessage(fd, msg_txt(3));
			return -1;
		}
	} else
		return -1;

	return 0;
}
/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_spiritball(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int number;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	number = atoi(message);
	if (number >= 0 && number <= 0x7FFF) {
		if (sd->spiritball > 0)
			pc_delspiritball(sd, sd->spiritball, 1);
		sd->spiritball = number;
		clif_spiritball(sd);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_party(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char party[100];
	if (!message || !*message)
		return -1;

	memset(party, '\0', sizeof(party));
	if (sscanf(message, "%99[^\n]", party))
		party_create(sd, party);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_guild(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char guild[100];
	int prev;

	if (!message || !*message)
		return -1;

	memset(guild, '\0', sizeof(guild));
	if (sscanf(message, "%99[^\n]", guild) == 0)
		return -1;

	prev = battle_config.guild_emperium_check;
	battle_config.guild_emperium_check = 0;
	guild_create(sd, guild);
	battle_config.guild_emperium_check = prev;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_agitstart(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	if (agit_flag == 1) {
		clif_displaymessage(fd, msg_txt(73));
		return 1;
	}
	agit_flag = 1;
	guild_agit_start();
	clif_displaymessage(fd, msg_txt(72));

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_agitend(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	if (agit_flag == 0) {
		clif_displaymessage(fd, msg_txt(75));
		return 1;
	}
	agit_flag = 0;
	guild_agit_end();
	clif_displaymessage(fd, msg_txt(74));

	return 0;
}

/*==========================================
 * @mapexitでマップサーバーを終了させる
 *------------------------------------------
 */
int
atcommand_mapexit(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth) {
			if (sd->status.account_id != pl_sd->status.account_id)
				clif_GM_kick(sd, pl_sd, 0);
		}
	}
	clif_GM_kick(sd, sd, 0);

	exit(1);

	return 0;
}

int
atcommand_idsearch(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char item_name[100];
	char output[100];
	unsigned int i, len, match;
	struct item_data *item;

	if (sscanf(message, "%99s", item_name) < 0)
		return -1;

	len = strlen(item_name);
	snprintf(output, sizeof output, msg_txt(77), item_name);
	clif_displaymessage(fd,output);
	match = 0;
	for(i = 0; i < 20000; i++) {
		if ((item = itemdb_exists(i)) != NULL && strstr(item->jname, item_name) != NULL) {
			match++;
			snprintf(output, sizeof output, msg_txt(78), item->jname, item->nameid);
			clif_displaymessage(fd, output);
		}
	}
	snprintf(output, sizeof output, msg_txt(79), match);
	clif_displaymessage(fd,output);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_itemidentify(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i = 0;

	nullpo_retr(-1, sd);

	for (i = 0; i < MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].amount && sd->status.inventory[i].identify == 0)
			pc_item_identify(sd, i);
	}
	clif_displaymessage(fd, msg_txt(80));

	return 0;
}

static int atshuffle_sub(struct block_list *bl,va_list ap)
{
	nullpo_retr(0, bl);

	mob_warp((struct mob_data *)bl,bl->m,-1,-1,3);

	return 0;
}

int
atcommand_shuffle(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int mode;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	mode = atoi(message)+1;

	if(mode&1) {	// PCのシャッフル
		struct map_session_data *pl_sd;
		int i;
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = session[i]->session_data) &&
			    pl_sd->state.auth && sd->bl.m == pl_sd->bl.m && pc_isGM(sd) >= pc_isGM(pl_sd))
				pc_setpos(pl_sd, map[pl_sd->bl.m].name, 0, 0, 3);
		}
	}
	if(mode&2) {	//MOBのシャッフル
		map_foreachinarea(atshuffle_sub, sd->bl.m, 0, 0, map[sd->bl.m].xs, map[sd->bl.m].ys, BL_MOB);
	}
	clif_displaymessage(fd, msg_txt(81));

	return 0;
}

int
atcommand_maintenance(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	chrif_maintenance(atoi(message)); // maintenance

	return 0;
}

int
atcommand_misceffect(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int effno = 0,bl_num=0;
	struct block_list *bl=NULL;

	nullpo_retr(-1, sd);

	if (sscanf(message, "%d %d", &effno , &bl_num) < 0)
		return -1;

	if(bl_num>0)
		bl = map_id2bl(bl_num);
	if(bl == NULL || bl->prev == NULL)
		bl = &sd->bl;

	clif_misceffect2(bl,effno);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_summon(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char mob_name[100];
	int mob_id = 0;
	int x = 0;
	int y = 0;
	int id = 0;
	struct mob_data *md;
	unsigned int tick=gettick();

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%99s", mob_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if(mob_id == 0)
		return -1;

	x = sd->bl.x + (atn_rand() % 10 - 5);
	y = sd->bl.y + (atn_rand() % 10 - 5);

	id = mob_once_spawn(sd,"this", x, y, sd->status.name, mob_id, 1, "");
	if( (md=map_id2md(id)) ){
		md->master_id=sd->bl.id;
		md->state.special_mob_ai=1;
		md->mode=mob_db[md->class].mode|0x04;
		md->deletetimer=add_timer(tick+60000,mob_timer_delete,id,0);
		clif_misceffect2(&md->bl,344);
	}
	clif_skill_poseffect(&sd->bl,AM_CALLHOMUN,1,x,y,tick);

	return 0;
}

/*==========================================
 * Character Skill Reset
 *------------------------------------------
 */
int atcommand_charskreset(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	char output[200];
	struct map_session_data *pl_sd;

	memset(character, '\0', sizeof(character));
	memset(output, '\0', sizeof(output));

	if (!message || !*message || sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_resetskill(pl_sd);
			sprintf(output, msg_txt(99), character);
			clif_displaymessage(fd, output);
		} else
			return -1;
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 * Character Stat Reset
 *------------------------------------------
 */
int atcommand_charstreset(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	char output[200];
	struct map_session_data *pl_sd;

	memset(character, '\0', sizeof(character));
	memset(output, '\0', sizeof(output));

	if (!message || !*message || sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_resetstate(pl_sd);
			sprintf(output, msg_txt(100), character);
			clif_displaymessage(fd, output);
		} else
			return -1;
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 * Character Reset
 *------------------------------------------
 */
int atcommand_charreset(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char character[100];
	char output[200];
	struct map_session_data *pl_sd;

	memset(character, '\0', sizeof(character));
	memset(output, '\0', sizeof(output));

	if (!message || !*message || sscanf(message, "%99[^\n]", character) < 1)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (pc_isGM(sd) >= pc_isGM(pl_sd)) {
			pc_resetstate(pl_sd);
			pc_resetskill(pl_sd);
			sprintf(output, msg_txt(101), character);
			clif_displaymessage(fd, output);
		} else
			return -1;
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}
/*==========================================
 * Character Status Point (rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charstpoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	char output[100];
	int new_status_point;
	int point = 0;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%d %99[^\n]", &point, character) < 2 || point == 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		new_status_point = (int)pl_sd->status.status_point + point;
		if (point > 0 && (point > 0x7FFF || new_status_point > 0x7FFF)) // fix positiv overflow
			new_status_point = 0x7FFF;
		else if (point < 0 && (point < -0x7FFF || new_status_point < 0)) // fix negativ overflow
			new_status_point = 0;
		if (new_status_point != (int)pl_sd->status.status_point) {
			pl_sd->status.status_point = new_status_point;
			clif_updatestatus(pl_sd, SP_STATUSPOINT);
			sprintf(output, msg_txt(102), character);
			clif_displaymessage(fd, output);
		} else {
			return -1;
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 * Character Skill Point (Rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charskpoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	char output[100];
	int new_skill_point;
	int point = 0;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%d %99[^\n]", &point, character) < 2 || point == 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		new_skill_point = (int)pl_sd->status.skill_point + point;
		if (point > 0 && (point > 0x7FFF || new_skill_point > 0x7FFF)) // fix positiv overflow
			new_skill_point = 0x7FFF;
		else if (point < 0 && (point < -0x7FFF || new_skill_point < 0)) // fix negativ overflow
			new_skill_point = 0;
		if (new_skill_point != (int)pl_sd->status.skill_point) {
			pl_sd->status.skill_point = new_skill_point;
			clif_updatestatus(pl_sd, SP_SKILLPOINT);
			sprintf(output, msg_txt(103), character);
			clif_displaymessage(fd, output);
		} else {
			return -1;
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}
/*==========================================
 * Character Zeny Point (Rewritten by [Yor])
 *------------------------------------------
 */
int atcommand_charzeny(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	char character[100];
	char output[100];
	int zeny = 0, new_zeny;

	memset(character, '\0', sizeof(character));

	if (!message || !*message || sscanf(message, "%d %99[^\n]", &zeny, character) < 2 || zeny == 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		new_zeny = pl_sd->status.zeny + zeny;
		if (zeny > 0 && (zeny > MAX_ZENY || new_zeny > MAX_ZENY)) // fix positiv overflow
			new_zeny = MAX_ZENY;
		else if (zeny < 0 && (zeny < -MAX_ZENY || new_zeny < 0)) // fix negativ overflow
			new_zeny = 0;
		if (new_zeny != pl_sd->status.zeny) {
			pl_sd->status.zeny = new_zeny;
			clif_updatestatus(pl_sd, SP_ZENY);
			sprintf(output, msg_txt(104), character);
			clif_displaymessage(fd, output);
		} else {
			return -1;
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
		return -1;
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
int atcommand_mapinfo(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	struct npc_data *nd = NULL;
	struct chat_data *cd = NULL;
	char output[200], map_name[100];
	char direction[12];
	int m_id, i, chat_num, list = 0;

	memset(output, '\0', sizeof(output));
	memset(map_name, '\0', sizeof(map_name));
	memset(direction, '\0', sizeof(direction));

	sscanf(message, "%d %99s", &list, map_name);

	if (list < 0 || list > 3)
		return -1;

	if (map_name[0] == '\0')
		strcpy(map_name, sd->mapname);
	if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13) // 16 - 4 (.gat)
		strcat(map_name, ".gat");

	if ((m_id = map_mapname2mapid(map_name)) < 0)
		return -1;

	clif_displaymessage(fd, "------ Map Info ------");
	sprintf(output, "Map Name: %s", map_name);
	clif_displaymessage(fd, output);
	sprintf(output, "Players In Map: %d", map[m_id].users);
	clif_displaymessage(fd, output);
	sprintf(output, "NPCs In Map: %d", map[m_id].npc_num);
	clif_displaymessage(fd, output);

	for (i=chat_num=0; i<fd_max; i++)
		if (session[i] && (pl_sd = session[i]->session_data)
			 && pl_sd->state.auth && (cd = map_id2cd(pl_sd->chatID)))
				chat_num++;

	sprintf(output, "Chats In Map: %d", chat_num);
	clif_displaymessage(fd, output);
	clif_displaymessage(fd, "------ Map Flags ------");
	sprintf(output, "Player vs Player: %s | No Guild: %s | No Party: %s",
		(map[m_id].flag.pvp) ? "True" : "False",
		(map[m_id].flag.pvp_noguild) ? "True" : "False",
		(map[m_id].flag.pvp_noparty) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "Guild vs Guild: %s | No Party: %s",
		(map[m_id].flag.gvg) ? "True" : "False",
		(map[m_id].flag.gvg_noparty) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Dead Branch: %s",
		(map[m_id].flag.nobranch) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Memo: %s",
		(map[m_id].flag.nomemo) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Penalty: %s",
		(map[m_id].flag.nopenalty) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Return: %s",
		(map[m_id].flag.noreturn) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Save: %s",
		(map[m_id].flag.nosave) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Teleport: %s",
		(map[m_id].flag.noteleport) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Portal: %s",
		(map[m_id].flag.noportal) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Monster Teleport: %s",
		(map[m_id].flag.monster_noteleport) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No Zeny Penalty: %s",
		(map[m_id].flag.nozenypenalty) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "No IceWall: %s",
		(map[m_id].flag.noicewall) ? "True" : "False");
	clif_displaymessage(fd, output);
	sprintf(output, "PK: %s",
		(map[m_id].flag.pk) ? "True" : "False");
	clif_displaymessage(fd, output);
	switch (list) {
		case 0:
			// Do nothing. It's list 0, no additional display.
			break;
		case 1:
			clif_displaymessage(fd, "----- Players in Map -----");
			for (i = 0; i < fd_max; i++) {
				if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth && strcmp(pl_sd->mapname, map_name) == 0) {
					sprintf(output, "Player '%s' (session #%d) | Location: %d,%d",
						pl_sd->status.name, i, pl_sd->bl.x, pl_sd->bl.y);
					clif_displaymessage(fd, output);
				}
			}
			break;
		case 2:
			clif_displaymessage(fd, "----- NPCs in Map -----");
			for (i = 0; i < map[m_id].npc_num;) {	// map[].npcには接触型のNPCしか保存されていない（手抜き）
				nd = map[m_id].npc[i];
				switch(nd->dir) {
				case 0:
					strcpy(direction, "North");
					break;
				case 1:
					strcpy(direction, "North West");
					break;
				case 2:
					strcpy(direction, "West");
					break;
				case 3:
					strcpy(direction, "South West");
					break;
				case 4:
					strcpy(direction, "South");
					break;
				case 5:
					strcpy(direction, "South East");
					break;
				case 6:
					strcpy(direction, "East");
					break;
				case 7:
					strcpy(direction, "North East");
					break;
				case 9:
					strcpy(direction, "North");
					break;
				default:
					strcpy(direction, "Unknown");
					break;
				}
				sprintf(output, "NPC %d: %s | Direction: %s | Sprite: %d | Location: %d %d",
				        ++i, nd->name, direction, nd->class, nd->bl.x, nd->bl.y);
				clif_displaymessage(fd, output);
			}
			break;
		case 3:
			clif_displaymessage(fd, "----- Chats in Map -----");
			for (i = 0; i < fd_max; i++) {
				if (session[i] && (pl_sd = session[i]->session_data) && pl_sd->state.auth &&
					(cd = map_id2cd(pl_sd->chatID)) &&
					strcmp(pl_sd->mapname, map_name) == 0 &&
					cd->usersd[0] == pl_sd) {
					sprintf(output, "Chat %d: %s | Player: %s | Location: %d %d",
							i, cd->title, pl_sd->status.name, cd->bl.x, cd->bl.y);
					clif_displaymessage(fd, output);
					sprintf(output, "   Users: %d/%d | Password: %s | Public: %s",
							cd->users, cd->limit, cd->pass, (cd->pub) ? "Yes" : "No");
					clif_displaymessage(fd, output);
				}
			}
			break;
		default: // normally impossible to arrive here
			sprintf(output, "Please, enter at least a valid list number (usage: %cmapinfo <0-3> [map]).", command_symbol);
			clif_displaymessage(fd, output);
			return -1;
			break;
	}

	return 0;
}

/*==========================================
 * Mob search
 *------------------------------------------
 */
static int atmobsearch_sub(struct block_list *bl,va_list ap)
{
	int mob_id,fd;
	static int number=0;
	struct mob_data *md=NULL;
	char output[128];

	nullpo_retr(0, bl);

	if (!ap) {
		number = 0;
		return 0;
	}
	mob_id = va_arg(ap,int);
	fd = va_arg(ap,const int);

	if(bl->type == BL_MOB)
		md = (struct mob_data *)bl;

	if (!md || !fd)
		return 0;

	switch (mob_id) {
		case -1:
			break;
		case -2:
			if( !(status_get_mode(&md->bl)&0x20) )
				return 0;
			break;
		case -3:
			if( !(status_get_mode(&md->bl)&0x20) || mob_db[md->class].mexp <= 0 )
				return 0;
			break;
		default:
			if( md->class != mob_id )
				return 0;
			break;
	}
	snprintf(output, sizeof output, msg_txt(94), ++number, bl->x, bl->y, md->name);
	clif_displaymessage(fd, output);

	return 0;
}

/*==========================================
 * MOB Search
 *------------------------------------------
 */
int
atcommand_mobsearch(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char mob_name[100], map_name[100]="";
	char output[100];
	int mob_id, map_id = 0;

	nullpo_retr(-1, sd);

	if (sscanf(message, "%s %99s", mob_name, map_name) < 1)
		return -1;

	if ((mob_id = atoi(mob_name)) == 0)
		mob_id = mobdb_searchname(mob_name);
	if (mob_id != -1 && mob_id != -2 && mob_id != -3 && !mobdb_checkid(mob_id)) {
		snprintf(output, sizeof output, msg_txt(93), mob_name);
		clif_displaymessage(fd, output);
		return 0;
	}

	if (mob_id == -1)
		strncpy(mob_name, msg_txt(153), sizeof(mob_name) -1); // all
	else if (mob_id == -2 || mob_id == -3)
		strncpy(mob_name, msg_txt(154), sizeof(mob_name) -1); // boss
	else if (mob_id > 0 && (mob_id == atoi(mob_name)) && mob_db[mob_id].jname)
		strcpy(mob_name, mob_db[mob_id].jname);	// --ja--
//		strcpy(mob_name, mob_db[mob_id].name);	// --en--
	if ((map_id = map_mapname2mapid(map_name)) == -1)
		map_id = sd->bl.m;

	snprintf(output, sizeof output, msg_txt(92), mob_name, map[map_id].name);
	clif_displaymessage(fd, output);

	map_foreachinarea(atmobsearch_sub, map_id, 0, 0, map[map_id].xs, map[map_id].ys, BL_MOB, mob_id, fd);
	atmobsearch_sub(&sd->bl, 0);		// 番号リセット

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

	if(bl->type == BL_ITEM)
		fitem = (struct flooritem_data *)bl;
	if(fitem == NULL) {
		if (battle_config.error_log)
			printf("map_clearflooritem_timer : error\n");
		return 1;
	}
	delete_timer(fitem->cleartimer,map_clearflooritem_timer);
	if(fitem->item_data.card[0] == (short)0xff00)
		intif_delete_petdata(*((long *)(&fitem->item_data.card[1])));
	clif_clearflooritem(fitem,0);
	map_delobject(fitem->bl.id);

	return 0;
}

int
atcommand_cleanmap(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i = 0;

	map_foreachinarea(atcommand_cleanmap_sub,sd->bl.m,
	                  sd->bl.x-AREA_SIZE*2,sd->bl.y-AREA_SIZE*2,
	                  sd->bl.x+AREA_SIZE*2,sd->bl.y+AREA_SIZE*2,
	                  BL_ITEM,sd,&i);
	clif_displaymessage(fd, msg_txt(95));

	return 0;
}

/*==========================================
 * Clock
 *------------------------------------------
 */
int
atcommand_clock(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char output[48];
	struct tm *tm;
	time_t t;

	t = time(NULL);
	tm = localtime(&t);

	sprintf(output, msg_txt(96), tm->tm_hour,tm->tm_min,tm->tm_sec);

	clif_displaymessage(fd, output);

	return 0;
}

/*==========================================
 * Give Item
 * @giveitem (item_id or item_name) amount charname
 *------------------------------------------
 */
static void atcommand_giveitem_sub(
	struct map_session_data *sd,struct item_data *item_data,int number)
{
	int flag = 0;
	int loop = 1, get_count = number,i;
	struct item item_tmp;

	if(sd && item_data){
		if (item_data->type == 4 || item_data->type == 5 ||
		    item_data->type == 7 || item_data->type == 8) {
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
	}

	return;
}

int
atcommand_giveitem(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd = NULL;
	struct item_data *item_data;
	char item_name[100];
	char character[100];
	char output[100];
	int number,i,item_id;

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%99s %d %99[^\n]", item_name, &number, character) < 3)
		return -1;

	if (number <= 0)
		number = 1;

	if ((item_id = atoi(item_name)) > 0) {
		if (battle_config.item_check) {
			item_id =
				(((item_data = itemdb_exists(item_id)) &&
				 itemdb_available(item_id)) ? item_id : 0);
		} else {
			item_data = itemdb_search(item_id);
		}
		strncpy(item_name,item_data->jname,31);
	} else if ((item_data = itemdb_searchname(item_name)) != NULL) {
		item_id = (!battle_config.item_check ||
			itemdb_available(item_data->nameid)) ? item_data->nameid : 0;
	}
	if(item_id == 0)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) { //該当名のキャラが存在する
		atcommand_giveitem_sub(pl_sd,item_data,number);
		snprintf(output, sizeof output, msg_txt(97), item_name,number);
		clif_displaymessage(pl_sd->fd, output);
		snprintf(output, sizeof output, msg_txt(98), pl_sd->status.name,item_name,number);
		clif_displaymessage(fd, output);
	} else if(strcmp(character,"ALL")==0){			// 名前がALLなら、接続者全員へ
		for (i = 0; i < fd_max; i++) {
			if (session[i] && (pl_sd = session[i]->session_data)){
				atcommand_giveitem_sub(pl_sd,item_data,number);
				snprintf(output, sizeof output, msg_txt(97),item_name,number);
				clif_displaymessage(pl_sd->fd, output);
			}
		}
		snprintf(output, sizeof output, msg_txt(98), msg_txt(135), item_name, number);
		clif_displaymessage(fd, output);
	} else
		return -1;

	return 0;
}
/*==========================================
 * Weather control
 * 発動後に効果を戻す(消す)方法が分からない・・・
 *------------------------------------------
 */
int
atcommand_weather(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *psd=NULL;
	int i,type,map_id,effno=0;
	char weather[100],map_name[100],output[100];

	if (sscanf(message, "%99s %99s", weather , map_name) < 1)
		return -1;

	if (map_name[0] == '\0')
		strcpy(map_name, sd->mapname);
	else if (strstr(map_name, ".gat") == NULL && strlen(map_name) < 13)
		strcat(map_name, ".gat");

	if ((map_id = map_mapname2mapid(map_name)) < 0)
		map_id = sd->bl.m;

	if(!atoi(weather)){
		if(!strcmp(weather,"day"))
			type=0;
		else if(!strcmp(weather,"0"))
			type=0;
		else if(!strcmp(weather,"rain"))
			type=1;
		else if(!strcmp(weather,"snow"))
			type=2;
		else if(!strcmp(weather,"sakura"))
			type=3;
		else if(!strcmp(weather,"fog"))
			type=4;
		else if(!strcmp(weather,"leaves"))
			type=5;
		else if(!strcmp(weather,"fireworks"))
			type=6;
		else if(!strcmp(weather,"cloud1"))
			type=7;
		else if(!strcmp(weather,"cloud2"))
			type=8;
		else if(!strcmp(weather,"cloud3"))
			type=9;
		else
			return -1;
	} else
		type=atoi(weather);

	if(type<0 || type>9)
		return -1;

	switch(type){
		case 0:
			if(map[map_id].flag.rain==1)
				effno=410;
			map[map_id].flag.rain=0;
			map[map_id].flag.snow=0;
			map[map_id].flag.sakura=0;
			map[map_id].flag.fog=0;
			map[map_id].flag.leaves=0;
			map[map_id].flag.fireworks=0;
			map[map_id].flag.cloud1=0;
			map[map_id].flag.cloud2=0;
			map[map_id].flag.cloud3=0;
			snprintf(output, sizeof output, msg_txt(112));
			clif_displaymessage(fd, output);
			break;
		case 1:
			if(!map[map_id].flag.rain){
				effno=161;
				map[map_id].flag.rain=1;
				snprintf(output, sizeof output, msg_txt(84));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.rain=0;
			}
			break;
		case 2:
			if(!map[map_id].flag.snow){
				effno=162;
				map[map_id].flag.snow=1;
				snprintf(output, sizeof output, msg_txt(85));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.snow=0;
			}
			break;
		case 3:
			if(!map[map_id].flag.sakura){
				effno=163;
				map[map_id].flag.sakura=1;
				snprintf(output, sizeof output, msg_txt(86));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.sakura=0;
			}
			break;
		case 4:
			if(!map[map_id].flag.fog){
				effno=515;
				map[map_id].flag.fog=1;
				snprintf(output, sizeof output, msg_txt(87));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.fog=0;
			}
			break;
		case 5:
			if(!map[map_id].flag.leaves){
				effno=333;
				map[map_id].flag.leaves=1;
				snprintf(output, sizeof output, msg_txt(88));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.leaves=0;
			}
			break;
		case 6:
			if(!map[map_id].flag.fireworks){
//				effno=297;
//				effno=299;
				effno=301;
				map[map_id].flag.fireworks=1;
				snprintf(output, sizeof output, msg_txt(119));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.fireworks=0;
			}
			break;
		case 7:
			if(!map[map_id].flag.cloud1){
				effno=230;
				map[map_id].flag.cloud1=1;
				snprintf(output, sizeof output, msg_txt(120));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.cloud1=0;
			}
			break;
		case 8:
			if(!map[map_id].flag.cloud2){
				effno=233;
				map[map_id].flag.cloud2=1;
				snprintf(output, sizeof output, msg_txt(121));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.cloud2=0;
			}
			break;
		case 9:
			if(!map[map_id].flag.cloud3){
				effno=516;
				map[map_id].flag.cloud3=1;
				snprintf(output, sizeof output, msg_txt(122));
				clif_displaymessage(fd, output);
			}else{
				map[map_id].flag.cloud3=0;
			}
			break;
		default:
			break;
	}
	// 指定マップ内に既に居るキャラは即時に天候変化
	for(i=0; effno && i < fd_max; i++) {
		if (session[i] && (psd = session[i]->session_data) != NULL && psd->state.auth){
			if(strcmp(map_name,"all.gat") && !strcmp(map_name,psd->mapname))
				clif_misceffect3(&psd->bl,effno);
		}
	}

	return 0;
}

/*==========================================
 * NPCに話させる
 *------------------------------------------
 */
int
atcommand_npctalk(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char name[100],mes[100];

	memset(mes, '\0', sizeof mes);
	if (sscanf(message, "%s %99[^\n]", name, mes) < 2)
		return -1;

	npc_globalmessage(name,mes);

	return 0;
}

/*==========================================
 * PETに話させる
 *------------------------------------------
 */
int
atcommand_pettalk(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char mes[100],temp[100];
	struct pet_data *pd;

	nullpo_retr(-1, sd);

	if (!sd->status.pet_id || !(pd = sd->pd))// || !sd->pet.rename_flag)
		return -1;

	memset(mes, '\0', sizeof mes);
	if (sscanf(message, "%99[^\n]", mes) < 1)
		return -1;

	snprintf(temp, sizeof temp ,"%s : %s",sd->pet.name,mes);
	clif_GlobalMessage(&pd->bl,temp);

	return 0;
}

/*==========================================
 * @users
 * サーバー内の人数マップを表示させる
 * 手抜きのため汚くなっているのは仕様です。
 *------------------------------------------
 */

static struct dbt *users_db;
static int users_all;

static int atcommand_users_sub1(struct map_session_data* sd,va_list va) {
	int users = (int)strdb_search(users_db,sd->mapname) + 1;

	users_all++;
	strdb_insert(users_db,sd->mapname,(void *)users);

	return 0;
}

static int atcommand_users_sub2(void* key,void* val,va_list va) {
	char buf[256];
	struct map_session_data* sd = va_arg(va,struct map_session_data*);

	sprintf(buf,"%s : %d (%d%%)",(char *)key,(int)val,(int)val * 100 / users_all);
	clif_displaymessage(sd->fd,buf);

	return 0;
}

int
atcommand_users(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char buf[256];

	users_all = 0;
	users_db = strdb_init(24);
	clif_foreachclient(atcommand_users_sub1);
	strdb_foreach(users_db,atcommand_users_sub2,sd);
	sprintf(buf, msg_txt(171), users_all); // all : %d
	clif_displaymessage(fd,buf);
	strdb_final(users_db,NULL);

	return 0;
}

/*==========================================
 * @reloadatcommand
 *   atcommand_athena.conf のリロード
 *------------------------------------------
 */
int
atcommand_reloadatcommand(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	atcommand_config_read(ATCOMMAND_CONF_FILENAME);
	clif_displaymessage(fd, msg_txt(113));

	return 0;
}

/*==========================================
 * @reloadbattleconf
 *   battle_athena.conf のリロード
 *------------------------------------------
 */
int
atcommand_reloadbattleconf(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	battle_config_read(BATTLE_CONF_FILENAME);
	clif_displaymessage(fd, msg_txt(114));

	return 0;
}

/*==========================================
 * @reloadgmaccount
 *   gm_account_filename のリロード
 *------------------------------------------
 */
int
atcommand_reloadgmaccount(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int atcommand_reloadhomundb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	homun_reload();
	clif_displaymessage(fd, msg_txt(145));

	return 0;
}

/*==========================================
 *itemDBのリロード
 *------------------------------------------
 */
int atcommand_reloaditemdb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	itemdb_reload();
	clif_displaymessage(fd, msg_txt(89));

	return 0;
}

/*==========================================
 *MOBDBのリロード
 *------------------------------------------
 */
int atcommand_reloadmobdb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
int
atcommand_reloadpcdb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	pc_readdb();
	clif_displaymessage(fd, msg_txt(117));

	return 0;
}

/*==========================================
 *スキルDBのリロード
 *------------------------------------------
 */
int atcommand_reloadskilldb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	skill_reload();
	clif_displaymessage(fd, msg_txt(91));

	return 0;
}

/*==========================================
 * @reloadstatusdb
 *   job_db1.txt job_db2.txt job_db2-2.txt
 *   refine_db.txt size_fix.txt
 *   のリロード
 *------------------------------------------
 */
int
atcommand_reloadstatusdb(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	status_readdb();
	clif_displaymessage(fd, msg_txt(116));

	return 0;
}

/*==========================================
 * @im
 *   アイテムやモンスターの簡易召還
 *------------------------------------------
 */
int atcommand_itemmonster(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message )
{
	char name[ 100 ];
	int item_id = 0;
	int flag = 0;
	struct item item_tmp;
	struct item_data *item_data;

	nullpo_retr( -1, sd);

	if (!message || !*message)
		return -1;

	if (sscanf(message, "%99s", name) < 1)
		return -1;

	if ((item_id = atoi(name)) > 0) {
		if (battle_config.item_check) {
			item_id = (((item_data = itemdb_exists(item_id)) && itemdb_available(item_id)) ? item_id : 0);
		} else {
			item_data = itemdb_search(item_id);
		}
	} else if ((item_data = itemdb_searchname(name)) != NULL) {
		item_id = (!battle_config.item_check || itemdb_available(item_data->nameid)) ? item_data->nameid : 0;
	}

	if (item_id > 0) {
		int get_count;
		memset(&item_tmp, 0, sizeof(item_tmp));
		item_tmp.nameid = item_id;
		if(item_data->type == 4 || item_data->type == 5 ||
		   item_data->type == 7 || item_data->type == 8 ){
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
		int mob_id, x=0, y=0;
		if ((mob_id = atoi(name)) == 0)
			mob_id = mobdb_searchname(name);
		if (mob_id == 0) {
			clif_displaymessage(fd, msg_txt(40));
			return 0;
		}

		x = sd->bl.x + ( atn_rand() % 10 - 5 );
		y = sd->bl.y + ( atn_rand() % 10 - 5 );
		if( mob_once_spawn(sd, "this", x, y, "--ja--", mob_id, 1, "") == 0 ){
			clif_displaymessage( fd, msg_txt(118) );
		}
	}

	return 0;
}

/*==========================================
 * Mapflag
 *------------------------------------------
 */
int atcommand_mapflag(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char w3[100],w4[100];
	int m=sd->bl.m;
	char drop_arg1[16],drop_arg2[16];
	int drop_id=0,drop_type=0,drop_per=0;
	char output[100];

	if (sscanf(message, "%99s %99s", w3, w4) < 1)
		return -1;

	if ( strcmpi(w3,"nosave")==0) {
		char savemap[16];
		int savex, savey;
		if (strcmp(w4,"SavePoint")==0) {
			memcpy(map[m].save.map,"SavePoint",16);
			map[m].save.x=-1;
			map[m].save.y=-1;
			map[m].flag.nosave=1;
		} else if (sscanf(w4,"%[^,],%d,%d",savemap,&savex,&savey)==3) {
			if (map_mapname2mapid(savemap) >= 0) {
				memcpy(map[m].save.map,savemap,16);
				map[m].save.x=savex;
				map[m].save.y=savey;
				map[m].flag.nosave=1;
			}
		} else {
			map[m].flag.nosave=0;
		}
	} else if (strcmpi(w3,"nomemo")==0) {
		map[m].flag.nomemo ^= 1;
	} else if (strcmpi(w3,"noteleport")==0) {
		map[m].flag.noteleport ^= 1;
	} else if (strcmpi(w3,"noportal")==0) {
		map[m].flag.noportal ^= 1;
	} else if (strcmpi(w3,"noreturn")==0) {
		map[m].flag.noreturn ^= 1;
	} else if (strcmpi(w3,"monster_noteleport")==0) {
		map[m].flag.monster_noteleport ^= 1;
	} else if (strcmpi(w3,"nobranch")==0) {
		map[m].flag.nobranch ^= 1;
	} else if (strcmpi(w3,"nopenalty")==0) {
		map[m].flag.nopenalty ^= 1;
	} else if (strcmpi(w3,"pvp")==0) {
		map[m].flag.pvp ^= 1;
	} else if (strcmpi(w3,"pvp_noparty")==0) {
		map[m].flag.pvp_noparty ^= 1;
	} else if (strcmpi(w3,"pvp_noguild")==0) {
		map[m].flag.pvp_noguild ^= 1;
	} else if (strcmpi(w3,"pvp_nightmaredrop")==0) {
		if (sscanf(w4,"%[^,],%[^,],%d",drop_arg1,drop_arg2,&drop_per)==3) {
			int i;
			if(strcmp(drop_arg1,"random")==0)
				drop_id = -1;
			else if(itemdb_exists( (drop_id=atoi(drop_arg1)) )==NULL)
				drop_id = 0;
			if(strcmp(drop_arg2,"inventory")==0)
				drop_type = 1;
			else if(strcmp(drop_arg2,"equip")==0)
				drop_type = 2;
			else if(strcmp(drop_arg2,"all")==0)
				drop_type = 3;
			else {
				drop_id = 0;
				map[m].flag.pvp_nightmaredrop=0;
			}

			if(drop_id != 0){
				for (i=0;i<MAX_DROP_PER_MAP;i++){
					if(map[m].drop_list[i].drop_id==0){
						map[m].drop_list[i].drop_id = drop_id;
						map[m].drop_list[i].drop_type = drop_type;
						map[m].drop_list[i].drop_per = drop_per;
						break;
					}
				}
				map[m].flag.pvp_nightmaredrop=1;
			}
		}
	} else if (strcmpi(w3,"pvp_nocalcrank")==0) {
		map[m].flag.pvp_nocalcrank ^= 1;
	} else if (strcmpi(w3,"gvg")==0) {
		map[m].flag.gvg ^= 1;
	} else if (strcmpi(w3,"gvg_noparty")==0) {
		map[m].flag.gvg_noparty ^= 1;
	} else if (strcmpi(w3,"nozenypenalty")==0) {
		map[m].flag.nozenypenalty ^= 1;
	} else if (strcmpi(w3,"notrade")==0) {
		map[m].flag.notrade ^= 1;
	} else if (strcmpi(w3,"noskill")==0) {
		map[m].flag.noskill ^= 1;
	} else if (strcmpi(w3,"noabra")==0) {
		map[m].flag.noabra ^= 1;
	} else if (strcmpi(w3,"nodrop")==0) {
		map[m].flag.nodrop ^= 1;
	} else if (strcmpi(w3,"snow")==0) {
		map[m].flag.snow ^= 1;
	} else if (strcmpi(w3,"fog")==0) {
		map[m].flag.fog ^= 1;
	} else if (strcmpi(w3,"sakura")==0) {
		map[m].flag.sakura ^= 1;
	} else if (strcmpi(w3,"leaves")==0) {
		map[m].flag.leaves ^= 1;
	} else if (strcmpi(w3,"rain")==0) {
		map[m].flag.rain ^= 1;
	} else if (strcmpi(w3,"base_exp_rate")==0) {
		int temp=atoi(w4);
		if(temp>=0)
			map[m].base_exp_rate=temp;
	} else if (strcmpi(w3,"job_exp_rate")==0) {
		int temp=atoi(w4);
		if(temp>=0)
			map[m].job_exp_rate=temp;
	} else if (strcmpi(w3,"pk")==0) {
		map[m].flag.pk ^= 1;
	} else if (strcmpi(w3,"pk_noparty")==0) {
		map[m].flag.pk_noparty ^= 1;
	} else if (strcmpi(w3,"pk_noguild")==0) {
		map[m].flag.pk_noguild ^= 1;
	} else if (strcmpi(w3,"pk_nightmaredrop")==0) {
		if (sscanf(w4,"%[^,],%[^,],%d",drop_arg1,drop_arg2,&drop_per)==3) {
			int i;
			if(strcmp(drop_arg1,"random")==0)
				drop_id = -1;
			else if(itemdb_exists( (drop_id=atoi(drop_arg1)) )==NULL)
				drop_id = 0;
			if(strcmp(drop_arg2,"inventory")==0)
				drop_type = 1;
			else if(strcmp(drop_arg2,"equip")==0)
				drop_type = 2;
			else if(strcmp(drop_arg2,"all")==0)
				drop_type = 3;
			else {
				drop_id = 0;
				map[m].flag.pk_nightmaredrop=0;
			}

			if(drop_id != 0){
				for (i=0;i<MAX_DROP_PER_MAP;i++){
					if(map[m].drop_list[i].drop_id==0){
						map[m].drop_list[i].drop_id = drop_id;
						map[m].drop_list[i].drop_type = drop_type;
						map[m].drop_list[i].drop_per = drop_per;
						break;
					}
				}
				map[m].flag.pk_nightmaredrop=1;
			}
		}
	} else if (strcmpi(w3,"pk_nocalcrank")==0) {
		map[m].flag.pk_nocalcrank ^= 1;
	} else if (strcmpi(w3,"noicewall")==0) {
		map[m].flag.noicewall ^= 1;
	} else if (strcmpi(w3,"turbo")==0) {
		map[m].flag.turbo ^= 1;
	} else if (strcmpi(w3,"norevive")==0) {
		map[m].flag.norevive ^= 1;
	} else{
		clif_displaymessage(fd,msg_txt(124));
		return -1;
	}
	map_field_setting();
	sprintf(output,msg_txt(125),w3);
	clif_displaymessage(fd,output);

	return 0;
}

/*==========================================
 * マナーポイント
 *------------------------------------------
 */
int
atcommand_mannerpoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct map_session_data *pl_sd;
	int manner;
	char character[100];

	if (!message || !*message)
		return -1;

	memset(character, '\0', sizeof character);
	if (sscanf(message, "%d %99[^\n]", &manner, character) < 2)
		return -1;

	if(battle_config.nomanner_mode)
		return 0;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		pl_sd->status.manner -= manner;
		status_change_start(&pl_sd->bl,SC_NOCHAT,0,0,0,0,0,0);
		clif_displaymessage(fd, msg_txt(155));
	}else{
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 * キャラ鯖の制限人数の変更
 *------------------------------------------
 */
int
atcommand_connectlimit(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int limit=0;
	char temp[100];

	if (sscanf(message, "%d", &limit) < 1)
		return -1;
	if(limit < 0)
		return -1;

	intif_char_connect_limit(limit);

	if(limit)
		sprintf(temp,msg_txt(126),limit);
	else
		sprintf(temp,msg_txt(127));
	clif_displaymessage(fd, temp);

	return 0;
}

/*==========================================
 * 緊急招集の受諾
 *------------------------------------------
 */
int
atcommand_econ(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct guild *g = NULL;
	char temp[100];
	nullpo_retr(-1, sd);

	if(sd->status.guild_id == 0)
		return -1;

	g = guild_search(sd->status.guild_id);

	if(g && sd != g->member[0].sd){
		sd->state.refuse_emergencycall = 0;
		sprintf(temp,msg_txt(128),g->master);
		clif_displaymessage(fd, temp);
	} else
		return -1;

	return 0;
}

/*==========================================
 * 緊急招集の拒否
 *------------------------------------------
 */
int
atcommand_ecoff(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	struct guild *g = NULL;
	char temp[100];
	nullpo_retr(-1, sd);

	if(sd->status.guild_id == 0)
		return -1;

	g = guild_search(sd->status.guild_id);

	if(g && sd != g->member[0].sd){
		sd->state.refuse_emergencycall = 1;
		sprintf(temp,msg_txt(129),g->master);
		clif_displaymessage(fd, temp);
	} else
		return -1;

	return 0;
}

/*==========================================
 * アイコン表示 デバック用
 *------------------------------------------
 */
int
atcommand_icon(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int	a1=0,a2=1;
	nullpo_retr( -1, sd );

	if (sscanf(message, "%d %d", &a1, &a2) < 2)
		return -1;

	clif_status_change(&sd->bl,a1,a2);	/* アイコン表示 */

	return 0;
}

/*==========================================
 * BSランキング
 *------------------------------------------
 */
int
atcommand_blacksmith(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr( -1, sd );

	ranking_display(sd,RK_BLACKSMITH,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * アルケミランキング
 *------------------------------------------
 */
int
atcommand_alchemist(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr( -1, sd );

	ranking_display(sd,RK_ALCHEMIST,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * テコンランキング
 *------------------------------------------
 */
int
atcommand_taekwon(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr( -1, sd );

	ranking_display(sd,RK_TAEKWON,0,MAX_RANKER-1);

	return 0;
}

int
atcommand_ranking(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;

	nullpo_retr( -1, sd );

	if (sscanf(message, "%d", &i) < 1)
		return -1;
	if(i<0 || i>=MAX_RANKER)
		return -1;

	ranking_display(sd,i,0,MAX_RANKER-1);

	return 0;
}

/*==========================================
 * ランキングポイント付与
 * type:0 blacksmith 1:alchemist 2:taekwon
 *------------------------------------------
 */
int
atcommand_rankingpoint(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int type,point;
	struct map_session_data *pl_sd;
	char char_name[100];

	nullpo_retr( -1, sd );

	memset(char_name, '\0', sizeof char_name);
	if (sscanf(message, "%d %d %99[^\n]", &type, &point, char_name) < 2)
		return -1;
	if(type<0 || type>3)
		return -1;

	if(strlen(char_name)>0)
		pl_sd = map_nick2sd(char_name);
	else
		pl_sd = sd;

	if(pl_sd != NULL){
		ranking_gain_point(pl_sd,type,point);
		ranking_setglobalreg(pl_sd,type);
		ranking_update(pl_sd,type);
	}else{
		clif_displaymessage(fd, msg_txt(3));
		return -1;
	}

	return 0;
}

/*==========================================
 * 感情をリセット
 *------------------------------------------
 */
int
atcommand_resetfeel(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;

	nullpo_retr( -1, sd );

	if (sscanf(message, "%d", &i) < 1)
		return -1;

	if(i>=0 && i<3){
		sd->feel_index[i] = -1;
		memset(&sd->status.feel_map[i], 0, sizeof(sd->status.feel_map[0]));
	}
	chrif_save(sd);

	return 0;
}

/*==========================================
 * 憎悪をリセット
 *------------------------------------------
 */
int
atcommand_resethate(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int i;

	nullpo_retr( -1, sd );

	if (sscanf(message, "%d", &i) < 1)
		return -1;

	if(i>=0 && i<3)
		sd->hate_mob[i] = -1;

	return 0;
}
/*==========================================
 * resetstate/resetskill
 *------------------------------------------
 */
int
atcommand_resetstate(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);
	pc_resetstate(sd);

	return 0;
}

int
atcommand_resetskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);
	pc_resetskill(sd);

	return 0;
}

/*==========================================
 * エモーション表示＠デバッグ用
 *------------------------------------------
 */
int
atcommand_emotion(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int emotion;
	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	emotion = atoi(message);
	clif_emotion(&sd->bl,emotion);

	return 0;
}

/*==========================================
 * ステータスMAX
 *------------------------------------------
 */
int
atcommand_statall(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{

	int idx;
	short value, new_value;
	short max_parameter[6];
	short* status[6];

	status[0] = &sd->status.str;
	status[1] = &sd->status.agi;
	status[2] = &sd->status.vit;
	status[3] = &sd->status.int_;
	status[4] = &sd->status.dex;
	status[5] = &sd->status.luk;

	max_parameter[0] = (short)battle_config.max_parameter_str;
	max_parameter[1] = (short)battle_config.max_parameter_agi;
	max_parameter[2] = (short)battle_config.max_parameter_vit;
	max_parameter[3] = (short)battle_config.max_parameter_int;
	max_parameter[4] = (short)battle_config.max_parameter_dex;
	max_parameter[5] = (short)battle_config.max_parameter_luk;

	if (!message || !*message) {
		for(idx = 0; idx < 6; idx++)
			*status[idx] = max_parameter[idx];
	} else {
		value = (short)atoi(message);
		for(idx = 0; idx < 6; idx++) {
			new_value = *status[idx] + value;
			if (new_value < 1)
				new_value = 1;
			else if (new_value > max_parameter[idx])
				new_value = max_parameter[idx];
			*status[idx] = new_value;
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
int
atcommand_viewclass(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int view_class;

	nullpo_retr(-1, sd);

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
int
atcommand_mailbox(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);
	clif_openmailbox(sd->fd);

	return 0;
}

/*==========================================
 * スクリプト変数を読み取る
 *------------------------------------------
 */
int atcommand_readvars(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char vars[100],name[100];
	char *output;

	nullpo_retr(-1, sd);

	if(!message || !*message)
		return -1;

	memset(name, '\0', sizeof(name));
	if(sscanf(message, "%99s %99[^\n]", vars, name) < 1)
		return -1;
	if(strlen(vars) < 1)
		return -1;

	output = script_operate_vars(sd, name, vars, NULL, 1);
	clif_displaymessage(fd,output);
	aFree(output);

	return 0;
}

/*==========================================
 * スクリプト変数に書き込む
 *------------------------------------------
 */
int atcommand_writevars(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	char vars[100],name[100],str[100];
	char *output;

	nullpo_retr(-1, sd);

	if(!message || !*message)
		return -1;

	memset(name, '\0', sizeof(name));

	// "で囲んである場合は簡易parseする
	if(strchr(message,'\"')) {
		int i=0;
		char buf[204];	// '\"'+str+'\"'+' '+name+'\0' = 204
		char *p;

		memset(buf, '\0', sizeof(buf));
		if(sscanf(message, "%99s %203[^\n]", vars, buf) < 2 || *buf != '\"')
			return -1;
		p = buf+1;
		while(*p && *p != '\"' && i<99) {
			if((unsigned char)p[-1] <= 0x7e && *p == '\\') {
				p++;
			}
			str[i++] = *p++;
		}
		str[i] = '\0';
		if(*p && *(++p) == ' ' && *(++p))
			memcpy(name, p, 99);
	} else {
		if(sscanf(message, "%99s %99s %99[^\n]", vars, str, name) < 2)
			return -1;
	}

	if(strlen(vars) < 1)
		return -1;

	output = script_operate_vars(sd, name, vars, str, 0);
	clif_displaymessage(fd,output);
	aFree(output);

	return 0;
}

/*==========================================
 * 
 *------------------------------------------
 */
int atcommand_cloneskill(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if(!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (ret == 1)
		skilllv = skill_get_max(skillid);

	skill_clone(sd, skillid, skilllv);

	return 0;
}

/*==========================================
 * 
 *------------------------------------------
 */
int atcommand_cloneskill2(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int cloneskilllv, skillid, skilllv = 0, ret;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	if ((ret = sscanf(message, "%d %d", &skillid, &skilllv)) < 1)
		return -1;

	if (ret == 1)
		skilllv = skill_get_max(skillid);

	cloneskilllv = pc_checkskill(sd,RG_PLAGIARISM);
	sd->cloneskill_id = skillid;
	sd->cloneskill_lv = (skilllv > cloneskilllv) ? cloneskilllv : skilllv;
	clif_skillinfoblock(sd);

	return 0;
}

/*==========================================
 * Show Monster DB Info   v 1.0
 * originally by [Lupus] eAthena
 *------------------------------------------
 */
int atcommand_mobinfo(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	unsigned char msize[3][7] = {"小型", "中型", "大型"};
	unsigned char mrace[12][11] = {"無", "不死", "動物", "植物", "昆虫", "魚", "悪魔", "人間", "天使", "竜", "Boss", "Non-Boss"};
	unsigned char melement[11][8] = {"無", "無", "水", "地", "火", "風", "毒", "聖", "闇", "念", "不死"};
	char output[200];
	char output2[200];
	struct item_data *item_data;
	struct mob_db *mob;
	int mob_id;
	int i, j;

	memset(output, '\0', sizeof(output));
	memset(output2, '\0', sizeof(output2));

	if (!message || !*message)
		return -1;

	if ((mob_id = atoi(message)) == 0)
		mob_id = mobdb_searchname(message);

	if (!mobdb_checkid(mob_id)) {
		clif_displaymessage(fd, msg_txt(40));
		return 0;
	}

	if((mob=&mob_db[mob_id])==NULL)
		return -1;

	// stats
	if (mob->mexp)
		sprintf(output, "MVP Monster: '%s'/'%s' (%d)", mob->name, mob->jname, mob_id);
	else
		sprintf(output, "Monster: '%s'/'%s' (%d)", mob->name, mob->jname, mob_id);
	clif_displaymessage(fd, output);
	sprintf(output, " Level:%d  HP:%d  SP:%d  Base EXP:%d  Job EXP:%d", mob->lv, mob->max_hp, mob->max_sp, (int)mob->base_exp, (int)mob->job_exp);
	clif_displaymessage(fd, output);
	sprintf(output, " DEF:%d  MDEF:%d  STR:%d  AGI:%d  VIT:%d  INT:%d  DEX:%d  LUK:%d", mob->def, mob->mdef, mob->str, mob->agi, mob->vit, mob->int_, mob->dex, mob->luk);
	clif_displaymessage(fd, output);
	if (mob->element < 20) {
		//Element - None, Level 0
		i = 0;
		j = 0;
	} else {
		i = mob->element % 20 + 1;
		j = mob->element / 20;
	}
	sprintf(output, " ATK:%d~%d  Range:%d~%d~%d  Size:%s  Race: %s  Element: %s (Lv:%d)", mob->atk1, mob->atk2, mob->range, mob->range2 , mob->range3, msize[mob->size], mrace[mob->race], melement[i], j);
	clif_displaymessage(fd, output);
	// drops
	clif_displaymessage(fd, " Drops:");
	strcpy(output, " ");
	j = 0;
	for (i = 0; i < ITEM_DROP_COUNT; i++) {
		if (mob->dropitem[i].nameid <= 0 || (item_data = itemdb_search(mob->dropitem[i].nameid)) == NULL)
			continue;
		if ( mob_droprate_fix( mob->dropitem[i].nameid, mob->dropitem[i].p ) > 0) {
			sprintf(output2, " - %s  %02.02f%%", item_data->jname
				, (float)mob_droprate_fix( mob->dropitem[i].nameid, mob->dropitem[i].p ) / 100);
			strcat(output, output2);
			if (++j % 3 == 0) {
				clif_displaymessage(fd, output);
				strcpy(output, " ");
			}
		}
	}
	if (j == 0)
		clif_displaymessage(fd, "This monster has no drops.");
	else if (j % 3 != 0)
		clif_displaymessage(fd, output);
	// mvp
	if (mob->mexp) {
		sprintf(output, " MVP Bonus EXP:%d  %02.02f%%", (int)mob->mexp, (float)mob->mexpper / 100);
		clif_displaymessage(fd, output);
		strcpy(output, " MVP Items:");
		j = 0;
		for (i = 0; i < 3; i++) {
			if (mob->mvpitem[i].nameid <= 0 || (item_data = itemdb_search(mob->mvpitem[i].nameid)) == NULL)
				continue;
			if (mob->mvpitem[i].p > 0) {
				j++;
				if (j == 1)
					sprintf(output2, " %s  %02.02f%%", item_data->jname, (float)mob->mvpitem[i].p / 100);
				else
					sprintf(output2, " - %s  %02.02f%%", item_data->jname, (float)mob->mvpitem[i].p / 100);
				strcat(output, output2);
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
int
atcommand_homlevel(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int level = 0, i = 0;
	struct homun_data *hd = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if ( (hd = sd->hd) == NULL )
		return -1;

	level = atoi(message);
	if (level > 1000 || level < -1000)
		return -1;
	if (level >= 1) {
		int hp = 0, sp = 0;
		for (i = 1; i <= level; i++){
			if(homun_nextbaseexp(hd) <= 0)
				break;
			hd->status.base_level++;
		//	hd->status.status_point += 15 + (hd->status.base_level+14)/3;	// 微調整してもうまくいかず・・・
			if(hd->status.base_level%3==0)	// 3レベル毎にSkillPoint加算
				hd->status.skill_point++;

			// 実測値の、最大値〜最小値でランダム上昇
			hp = homun_db[hd->status.class-HOM_ID].hp_kmax-homun_db[hd->status.class-HOM_ID].hp_kmin;
			hd->status.max_hp += homun_db[hd->status.class-HOM_ID].hp_kmin + atn_rand()%hp;
			sp = homun_db[hd->status.class-HOM_ID].sp_kmax-homun_db[hd->status.class-HOM_ID].sp_kmin;
			hd->status.max_sp += homun_db[hd->status.class-HOM_ID].sp_kmin + atn_rand()%sp;

		//	homun_upstatus(&hd->status);	// オートステ振り(statuspoint方式)
			homun_upstatus2(&hd->status);	// ステアップ計算
		}
		homun_calc_status(hd);			// ステータス計算
		homun_heal(hd,hd->max_hp,hd->max_sp);
		clif_misceffect2(&hd->bl,568);
		if(hd->msd){
			clif_send_homstatus(hd->msd,0);
			clif_homskillinfoblock(hd->msd);
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
int
atcommand_homviewclass(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int view_class;

	nullpo_retr(-1, sd);

	if (sscanf(message, "%d", &view_class) < 1)
		return -1;

	if(sd->hd)
		sd->hd->view_class = view_class;

	return 0;
}
/*==========================================
 * 
 *------------------------------------------
 */
int
atcommand_homevolution(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int evo_class=0;

	nullpo_retr(-1, sd);

	if( sd->hd ) {
		if(sscanf(message, "%d", &evo_class) < 1)
			evo_class = 0;
		homun_change_class( sd, evo_class );
	}
	return 0;
}

/*==========================================
 * 
 *------------------------------------------
 */
int
atcommand_homrecalc(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	nullpo_retr(-1, sd);

	if(sd->hd)
	{
		homun_recalc_status(sd->hd);
		homun_heal(sd->hd,sd->hd->status.max_hp,sd->hd->status.max_sp);
		if(sd->hd->msd){
			clif_send_homstatus(sd->hd->msd,0);
			clif_homskillinfoblock(sd->hd->msd);
		}
	}

	return 0;
}

/*==========================================
 * 
 *------------------------------------------
 */
int
atcommand_makehomun(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int homunid;

	nullpo_retr(-1, sd);

	if(sscanf(message, "%d", &homunid)<1)
		return -1;
	if( HOM_ID <= homunid && homunid < HOM_ID + MAX_HOMUN_DB );
	else
		return -1;

	if(sd->status.homun_id==0) {
		homun_create_hom(sd,homunid);
	} else {
		clif_displaymessage(fd,msg_txt(144));
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int
atcommand_homfriendly(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
{
	int friendly = 0;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;

	friendly = atoi(message);
	if (sd->status.homun_id > 0 && sd->hd) {
		if (friendly >= 0 && friendly <= 100000) {
			sd->hd->status.intimate = friendly;
			sd->hd->intimate = sd->hd->status.intimate;
			clif_send_homdata(sd,0x100,sd->hd->intimate/100);
		} else {
			return -1;
		}
	}

	return 0;
}

/*==========================================
 * アイテムの自動取得機能を切り替える
 *   from eAthena by Upa-Kun
 *------------------------------------------
 */
int
atcommand_autoloot(
	const int fd, struct map_session_data* sd,
	const char* command, const char* message)
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
