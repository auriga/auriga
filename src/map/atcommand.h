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

#ifndef _ATCOMMAND_H_
#define _ATCOMMAND_H_

typedef enum {
	AtCommand_None = -1,
	AtCommand_Broadcast = 0,
	AtCommand_LocalBroadcast,
	AtCommand_MapMove,
	AtCommand_ResetState,
	AtCommand_ResetSkill,
	AtCommand_RuraP,
	AtCommand_Rura,
	AtCommand_Where,
	AtCommand_JumpTo,
	AtCommand_Jump,
	AtCommand_Who,
	AtCommand_Save,
	AtCommand_Load,
	AtCommand_Speed,
	AtCommand_Storage,
	AtCommand_GuildStorage,
	AtCommand_Option,
	AtCommand_Hide,
	AtCommand_JobChange,
	AtCommand_Die,
	AtCommand_Kill,
	AtCommand_Alive,
	AtCommand_Kami,
	AtCommand_KamiB,
	AtCommand_KamiC,
	AtCommand_Heal,
	AtCommand_Item,
	AtCommand_Item2,
	AtCommand_Item3,
	AtCommand_ItemReset,
	AtCommand_BaseLevelUp,
	AtCommand_JobLevelUp,
	AtCommand_Help,
	AtCommand_GM,
	AtCommand_PvPOff,
	AtCommand_PvPOn,
	AtCommand_GvGOff,
	AtCommand_GvGOn,
	AtCommand_Model,
	AtCommand_Go,
	AtCommand_Monster,
	AtCommand_MonsterMap,
	AtCommand_KillMonster,
	AtCommand_KillMonster2,
	AtCommand_Refine,
	AtCommand_Produce,
	AtCommand_Repair,
	AtCommand_Memo,
	AtCommand_GAT,
	AtCommand_Packet,
	AtCommand_StatusPoint,
	AtCommand_SkillPoint,
	AtCommand_Zeny,
	AtCommand_Strength,
	AtCommand_Agility,
	AtCommand_Vitality,
	AtCommand_Intelligence,
	AtCommand_Dexterity,
	AtCommand_Luck,
	AtCommand_GuildLevelUp,
	AtCommand_GuildSkillPoint,
	AtCommand_MakePet,
	AtCommand_Hatch,
	AtCommand_PetFriendly,
	AtCommand_PetHungry,
	AtCommand_PetRename,
	AtCommand_CharPetRename,
	AtCommand_Recall,
	AtCommand_Recallall,
	AtCommand_RecallGuild,
	AtCommand_RecallParty,
	AtCommand_CharacterJob,
	AtCommand_Revive,
	AtCommand_CharacterStats,
	AtCommand_CharacterOption,
	AtCommand_CharacterSave,
	AtCommand_CharacterLoad,
	AtCommand_Night,
	AtCommand_Day,
	AtCommand_Doom,
	AtCommand_DoomMap,
	AtCommand_Raise,
	AtCommand_RaiseMap,
	AtCommand_CharacterBaseLevel,
	AtCommand_CharacterJobLevel,
	AtCommand_Kick,
	AtCommand_KickAll,
	AtCommand_AllSkill,
	AtCommand_QuestSkill,
	AtCommand_CharQuestSkill,
	AtCommand_LostSkill,
	AtCommand_CharLostSkill,
	AtCommand_SpiritBall,
	AtCommand_Party,
	AtCommand_PartyOption,
	AtCommand_Guild,
	AtCommand_AgitStart,
	AtCommand_AgitEnd,
	AtCommand_OnlyMes,
	AtCommand_MesWeb,
	AtCommand_MapExit,
	AtCommand_IDSearch,
	AtCommand_ItemIdentify,
	AtCommand_Shuffle,
	AtCommand_Maintenance,
	AtCommand_Misceffect,
	AtCommand_Summon,
	AtCommand_WhoP,
	AtCommand_CharSkReset,
	AtCommand_CharStReset,
	AtCommand_CharReset,
	AtCommand_CharSKPoint,
	AtCommand_CharSTPoint,
	AtCommand_CharZeny,
	AtCommand_CharItemreset,
	AtCommand_MapInfo,
	AtCommand_MobSearch,
	AtCommand_CleanMap,
	AtCommand_Clock,
	AtCommand_GiveItem,
	AtCommand_Weather,
	AtCommand_NpcTalk,
	AtCommand_PetTalk,
	AtCommand_HomTalk,
	AtCommand_Users,
	AtCommand_ReloadAtcommand,
	AtCommand_ReloadBattleConf,
	AtCommand_ReloadGMAccount,
	AtCommand_ReloadHomunDB,
	AtCommand_ReloadItemDB,
	AtCommand_ReloadMercDB,
	AtCommand_ReloadElemDB,
	AtCommand_ReloadMobDB,
	AtCommand_ReloadPcDB,
	AtCommand_ReloadSkillDB,
	AtCommand_ReloadStatusDB,
	AtCommand_ReloadMotd,
	AtCommand_ItemMonster,
	AtCommand_Mapflag,
	AtCommand_MannerPoint,
	AtCommand_ConnectLimit,
	AtCommand_Econ,
	AtCommand_Ecoff,
	AtCommand_Icon,
	AtCommand_Ranking,
	AtCommand_Blacksmith,
	AtCommand_Alchemist,
	AtCommand_TaeKwon,
	AtCommand_ResetFeel,
	AtCommand_ResetHate,
	AtCommand_emotion,
	AtCommand_statall,
	AtCommand_RankingPoint,
	AtCommand_ViewClass,
	AtCommand_MailBox,
	AtCommand_ReadVars,
	AtCommand_WriteVars,
	AtCommand_CloneSkill,
	AtCommand_CloneSkill2,
	AtCommand_Reproduce,
	AtCommand_Reproduce2,
	AtCommand_MobInfo,
	AtCommand_HomLevel,
	AtCommand_HomViewClass,
	AtCommand_HomEvolution,
	AtCommand_HomRecalc,
	AtCommand_MakeHomun,
	AtCommand_HomFriendly,
	AtCommand_AutoLoot,
	AtCommand_ChangeMapType,
	AtCommand_HotkeySet,
	AtCommand_CallMerc,
	AtCommand_Alliance,
	AtCommand_Unknown,
	AtCommand_MAX,
} AtCommandType;

struct map_session_data;

typedef struct AtCommandInfo {
	AtCommandType type;
	const char* command;
	int level;
	int (*proc)(const int, struct map_session_data*, AtCommandType command, const char* message);
	struct AtCommandInfo *next;
} AtCommandInfo;

AtCommandType is_atcommand_sub(const int fd, struct map_session_data *sd, const char *str, int gmlvl);
AtCommandType is_atcommand(const int fd, struct map_session_data* sd, const char* message);

char GM_Symbol(void);
int get_atcommand_level(const AtCommandType type);

int atcommand_config_read(const char *cfgName);

void do_final_atcommand(void);
void atcommand_reload(void);
int do_init_atcommand(void);

#endif
