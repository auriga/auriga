/*
 * Copyright (C) 2002-2007  Auriga
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
#include <time.h>
#include <math.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "mmo.h"
#include "utils.h"

#include "guild.h"
#include "skill.h"
#include "map.h"
#include "path.h"
#include "clif.h"
#include "pc.h"
#include "bonus.h"
#include "pet.h"
#include "mob.h"
#include "battle.h"
#include "party.h"
#include "itemdb.h"
#include "script.h"
#include "intif.h"
#include "status.h"
#include "date.h"
#include "unit.h"
#include "homun.h"
#include "msg.h"
#include "ranking.h"
#include "npc.h"
#include "merc.h"
#include "buyingstore.h"
#include "elem.h"

#define SKILLUNITTIMER_INVERVAL	100

/* スキル番号＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable[MAX_SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 0- */
	-1,-1,-1,-1,-1,-1,SC_PROVOKE,SC_MAGNUM,SC_ENDURE,-1,
	/* 10- */
	SC_SIGHT,-1,SC_SAFETYWALL,-1,-1,SC_FREEZE,SC_STONE,-1,-1,-1,
	/* 20- */
	-1,-1,-1,-1,SC_RUWACH,SC_PNEUMA,-1,-1,-1,SC_INCREASEAGI,
	/* 30- */
	SC_DECREASEAGI,-1,SC_SIGNUMCRUCIS,SC_ANGELUS,SC_BLESSING,-1,-1,-1,-1,-1,
	/* 40- */
	-1,-1,-1,-1,-1,SC_CONCENTRATE,SC_DOUBLE,-1,-1,-1,
	/* 50- */
	-1,SC_HIDING,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 60- */
	SC_TWOHANDQUICKEN,SC_AUTOCOUNTER,-1,-1,-1,-1,SC_IMPOSITIO,SC_SUFFRAGIUM,SC_ASPERSIO,SC_BENEDICTIO,
	/* 70- */
	-1,SC_SLOWPOISON,-1,SC_KYRIE,SC_MAGNIFICAT,SC_GLORIA,SC_SILENCE,-1,SC_AETERNA,-1,
	/* 80- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 90- */
	-1,-1,SC_QUAGMIRE,-1,-1,-1,-1,-1,-1,-1,
	/* 100- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 110- */
	-1,SC_ADRENALINE,SC_WEAPONPERFECTION,SC_OVERTHRUST,SC_MAXIMIZEPOWER,-1,-1,SC_ANKLE,-1,-1,
	/* 120- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 130- */
	-1,-1,-1,-1,-1,SC_CLOAKING,SC_STUN,-1,SC_ENCPOISON,SC_POISONREACT,
	/* 140- */
	SC_POISON,SC_SPLASHER,-1,SC_TRICKDEAD,-1,-1,SC_AUTOBERSERK,-1,-1,-1,
	/* 150- */
	-1,-1,-1,-1,-1,SC_LOUD,-1,SC_ENERGYCOAT,-1,-1,
	/* 160- */
	-1,-1,SC_ELEMENTWATER,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,SC_ELEMENTPOISON,SC_ELEMENTHOLY,SC_ELEMENTDARK,SC_ELEMENTELEKINESIS,
	/* 170- */
	-1,-1,-1,SC_SELFDESTRUCTION,-1,-1,-1,-1,-1,-1,
	/* 180- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 190- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 200- */
	-1,SC_KEEPING,-1,-1,SC_BARRIER,SC_NPC_DEFENDER,-1,SC_HALLUCINATION,SC_REBIRTH,-1,
	/* 210- */
	-1,-1,-1,-1,-1,SC_STRIPWEAPON,SC_STRIPSHIELD,SC_STRIPARMOR,SC_STRIPHELM,-1,
	/* 220- */
	SC_GRAFFITI,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 230- */
	-1,-1,-1,-1,SC_CP_WEAPON,SC_CP_SHIELD,SC_CP_ARMOR,SC_CP_HELM,-1,-1,
	/* 240- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,SC_AUTOGUARD,
	/* 250- */
	-1,-1,SC_REFLECTSHIELD,-1,-1,SC_DEVOTION,SC_PROVIDENCE,SC_DEFENDER,SC_SPEARQUICKEN,-1,
	/* 260- */
	-1,-1,-1,-1,-1,-1,-1,-1,SC_STEELBODY,SC_BLADESTOP_WAIT,
	/* 270- */
	SC_EXPLOSIONSPIRITS,SC_EXTREMITYFIST,-1,-1,-1,-1,SC_MAGICROD,-1,-1,-1,
	/* 280- */
	SC_FLAMELAUNCHER,SC_FROSTWEAPON,SC_LIGHTNINGLOADER,SC_SEISMICWEAPON,-1,SC_VOLCANO,SC_DELUGE,SC_VIOLENTGALE,-1,-1,
	/* 290- */
	-1,-1,-1,-1,SC_REVERSEORCISH,-1,-1,-1,-1,-1,
	/* 300- */
	-1,-1,-1,-1,-1,-1,SC_LULLABY,SC_RICHMANKIM,SC_ETERNALCHAOS,SC_DRUMBATTLE,
	/* 310- */
	SC_NIBELUNGEN,SC_ROKISWEIL,SC_INTOABYSS,SC_SIEGFRIED,-1,-1,-1,SC_DISSONANCE,-1,SC_WHISTLE,
	/* 320- */
	SC_ASSNCROS,SC_POEMBRAGI,SC_APPLEIDUN,-1,-1,SC_UGLYDANCE,-1,SC_HUMMING,SC_DONTFORGETME,SC_FORTUNE,
	/* 330- */
	SC_SERVICE4U,SC_SELFDESTRUCTION,-1,-1,-1,SC_WE_FEMALE,-1,-1,-1,-1,
	/* 340- */
	-1,-1,SC_STOP,-1,-1,-1,-1,-1,SC_ELEMENTUNDEAD,SC_EXPLOSIONSPIRITS,
	/* 350- */
	SC_SPEEDUP1,-1,-1,SC_INVISIBLE,-1,SC_AURABLADE,SC_PARRYING,SC_CONCENTRATION,SC_TENSIONRELAX,SC_BERSERK,
	/* 360- */
	-1,SC_ASSUMPTIO,SC_BASILICA,-1,-1,-1,SC_MAGICPOWER,-1,SC_SACRIFICE,SC_GOSPEL,
	/* 370- */
	-1,SC_TIGERFIST,-1,-1,-1,-1,-1,-1,SC_EDP,-1,
	/* 380- */
	SC_TRUESIGHT,-1,-1,SC_WINDWALK,SC_MELTDOWN,-1,-1,SC_CARTBOOST,-1,SC_CHASEWALK,
	/* 390- */
	SC_REJECTSWORD,-1,-1,-1,-1,-1,SC_MARIONETTE,-1,SC_HEADCRUSH,SC_JOINTBEAT,
	/* 400- */
	-1,-1,SC_MINDBREAKER,SC_MEMORIZE,SC_FOGWALL,SC_SPIDERWEB,-1,-1,SC_BABY,-1,
	/* 410- */
	-1,SC_RUN,SC_READYSTORM,-1,SC_READYDOWN,-1,SC_READYTURN,-1,SC_READYCOUNTER,-1,
	/* 420- */
	SC_DODGE,-1,-1,-1,-1,SC_SEVENWIND,-1,-1,SC_WARM,SC_WARM,
	/* 430- */
	SC_WARM,SC_SUN_COMFORT,SC_MOON_COMFORT,SC_STAR_COMFORT,-1,-1,-1,-1,-1,-1,
	/* 440- */
	-1,-1,-1,-1,SC_FUSION,SC_ALCHEMIST,-1,SC_MONK,SC_STAR,SC_SAGE,
	/* 450- */
	SC_CRUSADER,SC_SUPERNOVICE,SC_KNIGHT,SC_WIZARD,SC_PRIEST,SC_BARDDANCER,SC_ROGUE,SC_ASSASIN,SC_BLACKSMITH,SC_ADRENALINE2,
	/* 460- */
	SC_HUNTER,SC_SOULLINKER,SC_KAIZEL,SC_KAAHI,SC_KAUPE,SC_KAITE,-1,-1,-1,SC_SMA,
	/* 470- */
	SC_SWOO,SC_SKE,SC_SKA,SC_PROVOKE,SC_MODECHANGE,SC_PRESERVE,-1,-1,-1,-1,
	/* 480- */
	-1,-1,SC_DOUBLECASTING,-1,SC_GRAVITATION_USER,-1,SC_OVERTHRUSTMAX,SC_LONGINGFREEDOM,SC_HERMODE,-1,
	/* 490- */
	-1,-1,-1,-1,SC_HIGH,SC_ONEHAND,-1,-1,-1,-1,
	/* 500- */
	-1,SC_FLING,-1,-1,SC_MADNESSCANCEL,SC_ADJUSTMENT,SC_INCREASING,-1,-1,-1,
	/* 510- */
	-1,-1,-1,SC_DISARM,-1,-1,-1,SC_GATLINGFEVER,-1,SC_FULLBUSTER,
	/* 520- */
	-1,-1,-1,-1,-1,-1,-1,SC_TATAMIGAESHI,SC_HIDING,-1,
	/* 530- */
	-1,SC_UTSUSEMI,SC_BUNSINJYUTSU,-1,-1,-1,-1,-1,SC_SUITON,-1,
	/* 540- */
	-1,-1,-1,SC_NEN,-1,-1,-1,-1,-1,-1,
	/* 550- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 600- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 650- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 660- */
	-1,-1,-1,SC_SILENCE,SC_FREEZE,SC_BLEED,SC_STONE,SC_CONFUSION,SC_SLEEP,SC_SIGHT,
	/* 670- */
	-1,SC_MAGICMIRROR,SC_SLOWCAST,SC_CRITICALWOUND,-1,SC_STONESKIN,SC_ANTIMAGIC,SC_CURSE,SC_STUN,-1,
	/* 680- */
	-1,-1,-1,SC_HELLPOWER,SC_HELLPOWER,SC_INVINCIBLE,SC_INVINCIBLEOFF,-1,-1,SC_BLESSING,
	/* 690- */
	SC_INCREASEAGI,SC_ASSUMPTIO,-1,-1,-1,-1,SC_ELEMENTUNDEAD,-1,-1,-1,
	/* 700- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 710- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 720- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 730- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 740- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

/* (スキル番号 - SECOND_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable2[MAX_SECONDSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 1001- */
	-1,SC_SHRINK,-1,-1,SC_CLOSECONFINE,SC_SIGHTBLASTER,-1,SC_ELEMENTWATER,-1,-1,
	/* 1011- */
	SC_WINKCHARM,-1,-1,-1,-1,-1,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,
};

/* (スキル番号 - THIRD_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable3[MAX_THIRDSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 2001- */
	SC_ENCHANTBLADE,-1,SC_DEATHBOUND,-1,SC_FEAR,-1,-1,SC_HELLINFERNO,SC_FEAR,-1,
	/* 2011- */
	SC_BERKANA,-1,SC_NAUTHIZ,SC_TURISUSS,SC_HAGALAZ,SC_ISHA,-1,SC_EISIR,SC_URUZ,-1,
	/* 2021- */
	SC_VENOMIMPRESS,-1,-1,-1,-1,-1,SC_POISONINGWEAPON,SC_WEAPONBLOCKING,-1,-1,
	/* 2031- */
	-1,-1,SC_CLOAKINGEXCEED,-1,SC_HALLUCINATIONWALK,SC_ROLLINGCUTTER,-1,-1,-1,-1,
	/* 2041- */
	SC_BLESSING,SC_INCREASEAGI,-1,SC_EPICLESIS,SC_KYRIE,SC_ORATIO,SC_LAUDAAGNUS,SC_LAUDARAMUS,-1,SC_RENOVATIO,
	/* 2051- */
	-1,-1,SC_EXPIATIO,SC_DUPLELIGHT,-1,-1,SC_SILENCE,-1,-1,-1,
	/* 2061- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2071- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2081- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2091- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2101- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2201- */
	SC_WHITEIMPRISON,-1,SC_FROSTMISTY,SC_FREEZE,SC_MARSHOFABYSS,SC_RECOGNIZEDSPELL,SC_STONE,-1,SC_STASIS,-1,
	/* 2211- */
	SC_STUN,SC_HELLINFERNO,SC_HELLINFERNO,-1,-1,-1,-1,SC_HELLINFERNO,SC_FROSTMISTY,SC_STUN,
	/* 2221- */
	SC_BLEED,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2231- */
	-1,-1,-1,SC_FEARBREEZE,-1,-1,-1,SC_ELECTRICSHOCKER,-1,-1,
	/* 2241- */
	-1,SC_WUGDASH,-1,SC_WUGBITE,-1,-1,SC_CAMOUFLAGE,-1,SC_ELEMENTFIRE,SC_ELEMENTWATER,
	/* 2251- */
	SC_ELEMENTGROUND,SC_ELEMENTWIND,SC_HELLINFERNO,SC_FROSTMISTY,-1,-1,-1,-1,SC_HELLINFERNO,SC_FROSTMISTY,
	/* 2261- */
	-1,SC_ACCELERATION,SC_HOVERING,-1,-1,-1,-1,SC_SHAPESHIFT,-1,SC_INFRAREDSCAN,
	/* 2271- */
	SC_ANALYZE,SC_MAGNETICFIELD,SC_NEUTRALBARRIER_USER,SC_STEALTHFIELD_USER,-1,-1,-1,-1,-1,-1,
	/* 2281- */
	-1,-1,-1,-1,SC__REPRODUCE,SC__AUTOSHADOWSPELL,SC__SHADOWFORM,-1,SC__BODYPAINT,SC__INVISIBILITY,
	/* 2291- */
	SC__DEADLYINFECT,SC__ENERVATION,SC__GROOMY,SC__IGNORANCE,SC__LAZINESS,SC__UNLUCKY,SC__WEAKNESS,SC__STRIPACCESSARY,SC__MANHOLE,-1,
	/* 2301- */
	-1,-1,SC_BERSERK,-1,-1,-1,-1,-1,-1,-1,
	/* 2311- */
	SC_REFLECTDAMAGE,-1,SC_FORCEOFVANGUARD,-1,-1,SC_EXEEDBREAK,-1,SC_PRESTIGE,SC_BANDING,SC_SITDOWN_FORCE,
	/* 2321- */
	-1,SC_BENEDICTIO,SC_EARTHDRIVE,-1,SC_INSPIRATION,-1,-1,-1,SC_FALLENEMPIRE,-1,
	/* 2331- */
	-1,-1,SC_CRESCENTELBOW,SC_CURSEDCIRCLE,SC_LIGHTNINGWALK,-1,SC_SITDOWN_FORCE,SC_RAISINGDRAGON,-1,-1,
	/* 2341- */
	-1,-1,-1,-1,-1,SC_GENTLETOUCH_ENERGYGAIN,SC_GENTLETOUCH_CHANGE,SC_GENTLETOUCH_REVITALIZE,-1,SC_SWING,
	/* 2351- */
	SC_SYMPHONY_LOVE,SC_MOONLIT_SERENADE,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2361- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2371- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2381- */
	SC_RUSH_WINDMILL,SC_ECHOSONG,SC_HARMONIZE,-1,-1,-1,-1,-1,-1,-1,
	/* 2391- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2401- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2411- */
	-1,-1,-1,-1,-1,-1,-1,-1,SC_NETHERWORLD,SC_SIREN,
	/* 2421- */
	-1,SC_DEEP_SLEEP,SC_SIRCLEOFNATURE,-1,SC_GLOOMYDAY,-1,SC_SONG_OF_MANA,SC_DANCE_WITH_WUG,-1,SC_SATURDAY_NIGHT_FEVER,
	/* 2431- */
	SC_LERADS_DEW,SC_MELODYOFSINK,SC_BEYOND_OF_WARCRY,SC_UNLIMITED_HUMMING_VOICE,-1,-1,-1,-1,-1,-1,
	/* 2441- */
	-1,-1,SC_PROPERTYWALK,SC_PROPERTYWALK,SC_SPELLFIST,SC_BLEED,SC_DIAMONDDUST,-1,-1,-1,
	/* 2451- */
	SC_STRIKING,SC_WARMER,SC_VACUUM_EXTREME,-1,SC_DEEP_SLEEP,-1,SC_SUMMON_ELEM,SC_SUMMON_ELEM,SC_SUMMON_ELEM,SC_SUMMON_ELEM,
	/* 2461- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2471- */
	-1,-1,-1,-1,-1,-1,-1,SC_GN_CARTBOOST,SC_THORNS_TRAP,SC_BLOOD_SUCKER,
	/* 2481- */
	SC_SPORE_EXPLOSION,-1,-1,-1,SC_HELLINFERNO,-1,-1,-1,-1,-1,
	/* 2491- */
	-1,SC_MANDRAGORA,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2501- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2511- */
	-1,-1,-1,-1,SC_SACRAMENT,-1,SC_FEAR,-1,-1,
};

/* (スキル番号 - QUEST_SKILLID)＝＞ステータス異常番号変換テーブル */
int QuestSkillStatusChangeTable[MAX_QUESTSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 2533- */
	-1,-1,-1,-1,SC_ODINS_POWER,-1,-1,SC_DISSONANCE,SC_UGLYDANCE
};

/* (スキル番号 - KO_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTableKO[MAX_KOSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 3001- */
	SC_HIDING,-1,-1,SC_KO_JYUMONJIKIRI,-1,-1,-1,-1,-1,-1,
	/* 3011- */
	SC_MEIKYOUSISUI,-1,SC_KYOUGAKU,SC_CURSE,-1,-1,-1,-1,-1,SC_KO_ZENKAI,
	/* 3021- */
	SC_CONFUSION,SC_IZAYOI,SC_KG_KAGEHUMI,SC_KYOMU,SC_KAGEMUSYA,SC_ZANGETSU,SC_GENSOU,-1,SC_AKAITSUKI,-1,
	/* 3031- */
	-1,-1,-1,-1,-1,
};

/* (スキル番号 - 3EX_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTableEX3[MAX_EX3SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 5001- */
	SC_DARKCROW,SC_UNLIMIT,-1,SC_FROSTMISTY,-1,SC_STUN,SC_FRIGG_SONG,-1,-1,SC__ESCAPE,
	/* 5011- */
	SC_OFFERTORIUM,SC_TELEKINESIS_INTENSE,-1,-1,SC_HELLINFERNO,
};

/* (スキル番号 - SUM_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTableSUM[MAX_SUMSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 5018- */
	-1,-1,SC_SUHIDE,SC_BLEED,SC_SU_STOOP,-1,-1,-1,SC_BLEED,SC_CATNIPPOWDER,
	/* 5028- */
	-1,SC_SV_ROOTTWIST,-1,-1,SC_BITESCAR,-1,-1,SC_ARCLOUSEDASH,-1,-1,
	/* 5038- */
	-1,SC_TUNAPARTY,SC_SHRIMP,SC_FRESHSHRIMP,-1,-1,-1,-1,-1,SC_HISS,
	/* 5048- */
	SC_NYANGGRASS,SC_GROOMING,SC_GROOMING,SC_PROTECTIONOFSHRIMP,-1,SC_CHATTERING,-1,SC_CHATTERING,-1,
};

/* (スキル番号 - HOM_SKILLID)＝＞ステータス異常番号変換テーブル */
int HomSkillStatusChangeTable[MAX_HOMSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 8000- */
	-1,SC_AVOID,-1,SC_CHANGE,-1,SC_DEFENCE,-1,SC_BLOODLUST,-1,SC_FLEET,
	/* 8010- */
	SC_SPEED,-1,-1,-1,-1,-1,
};

/* (スキル番号 - MERC_SKILLID)＝＞ステータス異常番号変換テーブル */
int MercSkillStatusChangeTable[MAX_MERCSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 8201- */
	-1,SC_MAGNUM,-1,SC_PARRYING,SC_REFLECTSHIELD,SC_BERSERK,SC_DOUBLE,-1,-1,-1,
	/* 8211- */
	-1,-1,-1,-1,-1,-1,-1,-1,SC_DEFENDER,SC_AUTOGUARD,
	/* 8221- */
	SC_DEVOTION,SC_MAGNIFICAT,SC_WEAPONQUICKEN,SC_SIGHT,-1,-1,-1,-1,-1,-1,
	/* 8231- */
	-1,SC_PROVOKE,SC_AUTOBERSERK,SC_DECREASEAGI,-1,SC_SILENCE,-1,SC_KYRIE,SC_BLESSING,SC_INCREASEAGI,
	/* 8241- */
	SC_INVINCIBLEOFF,
};

/* (スキル番号 - ELEM_SKILLID)＝＞ステータス異常番号変換テーブル */
int ElemSkillStatusChangeTable[MAX_ELEMSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 8401- */
	SC_CIRCLE_OF_FIRE,SC_FIRE_CLOAK,-1,SC_WATER_SCREEN,SC_WATER_DROP,SC_WATER_BARRIER,SC_WIND_STEP,SC_WIND_CURTAIN,SC_ZEPHYR,SC_SOLID_SKIN,
	/* 8411- */
	SC_STONE_SHIELD,SC_POWER_OF_GAIA,SC_PYROTECHNIC,SC_HEATER,SC_TROPIC,SC_AQUAPLAY,SC_COOLER,SC_CHILLY_AIR,SC_GUST,SC_BLAST,
	/* 8421- */
	SC_WILD_STORM,SC_PETROLOGY,SC_CURSED_SOIL,SC_UPHEAVAL,-1,-1,-1,-1,-1,-1,
	/* 8431- */
	-1,-1,SC_TIDAL_WEAPON,-1,-1,-1,-1,-1,-1,SC_ROCK_CRUSHER,
	/* 8441- */
	SC_ROCK_CRUSHER_ATK,-1,
};

/* (スキル番号 - GUILD_SKILLID)＝＞ステータス異常番号変換テーブル */
int GuildSkillStatusChangeTable[MAX_GUILDSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 10000- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 10010- */
	SC_BATTLEORDER,SC_REGENERATION,-1,-1,-1,-1,
};

/* スキルデータベース */
struct skill_db skill_db[MAX_SKILL_DB];

/* アイテム作成データベース */
struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

/* 矢作成スキルデータベース */
struct skill_arrow_db skill_arrow_db[MAX_SKILL_ARROW_DB];

/* アブラカダブラ発動スキルデータベース */
struct skill_abra_db skill_abra_db[MAX_SKILL_ABRA_DB];

/* ランダム発動スキルデータ */
struct skill_rand_db skill_rand_db[MAX_SKILL_RAND_DB];

/* チェンジマテリアル合成データベース */
struct skill_material_db skill_material_db[MAX_SKILL_PRODUCE_DB];

/* プロトタイプ */
static struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y);
static struct skill_unit_group *skill_initunitgroup(struct block_list *src,int count,int skillid,int skilllv,int unit_id,unsigned int tick);

static int skill_item_consume(struct block_list *bl, struct skill_condition *cnd, int type, int *itemid, int *amount);
static int skill_get_spellslot( int skillid );

static void skill_brandishspear_dir(struct square *tc,int dir,int are);
static void skill_brandishspear_first(struct square *tc,int dir,int x,int y);
static int skill_frostjoke_scream(struct block_list *bl,va_list ap);
static int skill_abra_dataset(struct map_session_data *sd, int skilllv);
static int skill_clear_element_field(struct block_list *bl);
static int skill_landprotector(struct block_list *bl, va_list ap );
static int skill_tarot_card_of_fate(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int wheel);
static int skill_trap_splash(struct block_list *bl, va_list ap );
static int skill_count_target(struct block_list *bl, va_list ap );
static int skill_unit_onplace(struct skill_unit *src,struct block_list *bl,unsigned int tick);
static int skill_unit_effect(struct block_list *bl,va_list ap);
static int skill_greed( struct block_list *bl,va_list ap );
static int skill_balkyoung( struct block_list *bl,va_list ap );
static int skill_castle_mob_changetarget(struct block_list *bl,va_list ap);
static int skill_delunit_by_ganbantein(struct block_list *bl, va_list ap );
static int skill_count_unitgroup(struct unit_data *ud,int skillid);
static int skill_am_twilight(struct map_session_data* sd, int skillid);
static int skill_check_condition_use_sub(struct block_list *bl,va_list ap);
static int skill_chainlightning(struct block_list *bl,va_list ap);
static int skill_detonator(struct block_list *bl,va_list ap);
static int skill_maelstrom(struct block_list *bl,va_list ap);
static int skill_trample(struct block_list *bl,va_list ap);
static int skill_dominion_impulse(struct block_list *bl,va_list ap);
static int skill_fire_expansion(struct block_list *bl,va_list ap);

/* スキルユニットの配置情報を返す */
static struct skill_unit_layout skill_unit_layout[MAX_SKILL_UNIT_LAYOUT];
static int firewall_unit_pos;
static int icewall_unit_pos;
static int earthstrain_unit_pos;

static struct skill_unit_layout *skill_get_unit_layout(int skillid,int skilllv,struct block_list *src,int x,int y)
{
	int pos = skill_get_unit_layout_type(skillid,skilllv);
	int dir;

	if(pos != -1)
		return &skill_unit_layout[pos];

	if(src->x == x && src->y == y)
		dir = 6;
	else
		dir = path_calc_dir(src,x,y);

	if(skillid == MG_FIREWALL)
		return &skill_unit_layout[firewall_unit_pos+dir];
	else if(skillid == WZ_ICEWALL)
		return &skill_unit_layout[icewall_unit_pos+dir];
	else if(skillid == WL_EARTHSTRAIN)
		return &skill_unit_layout[earthstrain_unit_pos+dir];

	printf("unknown unit layout for skill %d, %d\n",skillid,skilllv);
	return &skill_unit_layout[0];
}

int GetSkillStatusChangeTable(int id)
{
	if(id >= 0 && id < MAX_SKILL)
		return SkillStatusChangeTable[id];

	if(id >= SECOND_SKILLID && id < MAX_SECOND_SKILLID)
		return SkillStatusChangeTable2[id - SECOND_SKILLID];

	if(id >= THIRD_SKILLID && id < MAX_THIRD_SKILLID)
		return SkillStatusChangeTable3[id - THIRD_SKILLID];

	if(id >= QUEST_SKILLID && id < MAX_QUEST_SKILLID)
		return QuestSkillStatusChangeTable[id - QUEST_SKILLID];

	if(id >= KO_SKILLID && id < MAX_KO_SKILLID)
		return SkillStatusChangeTableKO[id - KO_SKILLID];

	if(id >= EX3_SKILLID && id < MAX_EX3_SKILLID)
		return SkillStatusChangeTableEX3[id - EX3_SKILLID];

	if(id >= SUM_SKILLID && id < MAX_SUM_SKILLID)
		return SkillStatusChangeTableSUM[id - SUM_SKILLID];

	if(id >= HOM_SKILLID && id < MAX_HOM_SKILLID)
		return HomSkillStatusChangeTable[id - HOM_SKILLID];

	if(id >= MERC_SKILLID && id < MAX_MERC_SKILLID)
		return MercSkillStatusChangeTable[id - MERC_SKILLID];

	if(id >= ELEM_SKILLID && id < MAX_ELEM_SKILLID)
		return ElemSkillStatusChangeTable[id - ELEM_SKILLID];

	if(id >= GUILD_SKILLID && id < MAX_GUILD_SKILLID)
		return GuildSkillStatusChangeTable[id - GUILD_SKILLID];

	return -1;
}
int skill_get_hit(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].hit;
}
int skill_get_inf(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].inf;
}
int skill_get_pl(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].pl;
}
int skill_get_nk(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].nk;
}
int skill_get_max(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].max;
}
int skill_get_range(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].range[lv-1];
}
int skill_get_hp(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].hp[lv-1];
}
int skill_get_sp(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].sp[lv-1];
}
int skill_get_zeny(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].zeny[lv-1];
}
int skill_get_num(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].num[lv-1];
}
int skill_get_cast(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].cast[lv-1];
}
int skill_get_fixedcast(int id ,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].fixedcast[lv-1];
}
int skill_get_delay(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].delay[lv-1];
}
int skill_get_cooldown(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].cooldown[lv-1];
}
int skill_get_time(int id ,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].upkeep_time[lv-1];
}
int skill_get_time2(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].upkeep_time2[lv-1];
}
int skill_get_castdef(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].cast_def_rate;
}
unsigned int skill_get_weapontype(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].weapon;
}
int skill_get_inf2(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].inf2;
}
int skill_get_maxcount(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].maxcount[lv-1];
}
int skill_get_skill_type(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].skill_type;
}
int skill_get_blewcount(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].blewcount[lv-1];
}
int skill_get_unit_id(int id,int flag)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].unit_id[flag];
}
int skill_get_unit_layout_type(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].unit_layout_type[lv-1];
}
int skill_get_unit_interval(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].unit_interval;
}
int skill_get_unit_range(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].unit_range[lv-1];
}
int skill_get_unit_target(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].unit_target;
}
int skill_get_unit_flag(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].unit_flag[lv-1];
}
int skill_get_arrow_cost(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].arrow_cost[lv-1];
}
int skill_get_arrow_type(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].arrow_type;
}
int skill_get_cloneable(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].cloneable;
}
int skill_get_misfire(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].misfire;
}
int skill_get_zone(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].zone;
}
int skill_get_damage_rate(int id,int type)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].damage_rate[type];
}
int skill_get_range_type(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].range_type;
}
int skill_get_amotion_delay(int id)
{
	id = skill_get_skilldb_id(id);
	return skill_db[id].amotion_delay;
}

/* 補正済み射程を返す */
int skill_get_fixed_range(struct block_list *bl,int id,int lv)
{
	int range;

	nullpo_retr(0, bl);

	range = skill_get_range(id,lv);
	if(range < 0)
		range = status_get_range(bl) - (range + 1);

	// スキル毎の射程増加処理
	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			int skill;
			switch(id) {
				case HT_LANDMINE:			/* ランドマイン */
				case HT_FREEZINGTRAP:		/* フリージングトラップ */
				case HT_BLASTMINE:			/* ブラストマイン */
				case HT_CLAYMORETRAP:		/* クレイモアトラップ */
				case RA_CLUSTERBOMB:		/* クラスターボム */
				case RA_FIRINGTRAP:			/* ファイアリングトラップ */
				case RA_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
					if((skill = pc_checkskill(sd,RA_RESEARCHTRAP)) > 0)	// トラップ研究 
						range += (skill + 1) / 2;
					break;
				case WL_WHITEIMPRISON:		/* ホワイトインプリズン */
				case WL_SOULEXPANSION:		/* ソウルエクスパンション */
				case WL_MARSHOFABYSS:		/* マーシュオブアビス */
				case WL_SIENNAEXECRATE:		/* シエナエクセクレイト */
				case WL_DRAINLIFE:			/* ドレインライフ */
				case WL_CRIMSONROCK:		/* クリムゾンロック */
				case WL_HELLINFERNO:		/* ヘルインフェルノ */
				case WL_COMET:				/* コメット */
				case WL_CHAINLIGHTNING:		/* チェーンライトニング */
				case WL_EARTHSTRAIN:		/* アースストレイン */
				case WL_TETRAVORTEX:		/* テトラボルテックス */
				case WL_RELEASE:			/* リリース */
					if((skill = pc_checkskill(sd,WL_RADIUS)) > 0)		// ラディウス
						range += skill;
					break;
				default:
					break;
			}
		}
	}
	return range;
}

/*==========================================
 * ランダム発動スキル検索
 *------------------------------------------
 */
int skill_searchrandomid(int type)
{
	int c;

	// typeは1以上なのでデクリメントする
	type--;
	if(type < 0 || type >= MAX_SKILL_RAND_DB)
		return 0;

	c = skill_rand_db[type].entry;
	if(c > 0 && skill_rand_db[type].data[c-1].qty > 0) {
		int i, num = atn_rand() % skill_rand_db[type].data[c-1].qty;
		for(i=0; i < c && num >= skill_rand_db[type].data[i].qty; i++);

		return skill_rand_db[type].data[i].nameid;
	}
	return 0;
}

/*==========================================
 * スキル追加効果
 *------------------------------------------
 */
int skill_additional_effect( struct block_list* src, struct block_list *bl,int skillid,int skilllv,int attack_type,unsigned int tick)
{
	/* MOB追加効果スキル用 */
	static const int sc[] = {
		SC_POISON, SC_BLIND, SC_SILENCE, SC_STUN,
		SC_STONE, SC_CURSE, SC_SLEEP
	};
	static const int sc2[] = {
		MG_STONECURSE,WZ_STORMGUST,NPC_STUNATTACK,
		NPC_SLEEPATTACK,TF_POISON,NPC_CURSEATTACK,
		NPC_SILENCEATTACK,0,NPC_BLINDATTACK,LK_HEADCRUSH
	};

	struct map_session_data *sd = NULL, *dstsd = NULL;
	struct mob_data         *md = NULL, *dstmd = NULL;
	struct skill_unit       *unit = NULL;
	struct status_change    *tsc = NULL;
	int skill;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if(skilllv < 0) return 0;

	// PC,MOB,PET,MERC,ELEM以外は追加効果の対象外
	if(!(bl->type & (BL_PC | BL_MOB | BL_PET | BL_MERC | BL_ELEM)))
		return 0;

	// グラウンドドリフトのときはsrcを設置者に置換
	if(src->type == BL_SKILL) {
		unit = (struct skill_unit *)src;
		if(unit && unit->group) {
			src = map_id2bl(unit->group->src_id);
			if(src == NULL)
				return 0;
		}
	}

	sd    = BL_DOWNCAST( BL_PC,  src );
	dstsd = BL_DOWNCAST( BL_PC,  bl );
	dstmd = BL_DOWNCAST( BL_MOB, bl );

	tsc = status_get_sc(bl);

	switch(skillid) {
	case 0:
		if(sd) {
			/* 自動鷹 */
			if( pc_isfalcon(sd) &&
			    (skill = pc_checkskill(sd,HT_BLITZBEAT)) > 0 &&
			    (sd->status.weapon == WT_BOW || battle_config.allow_any_weapon_autoblitz) &&
			    atn_rand()%10000 < sd->paramc[5]*30+100 )
			{
				int lv = (sd->status.job_level+9)/10;
				skill_castend_damage_id(src,bl,HT_BLITZBEAT,(skill < lv)? skill: lv,tick,0xf00000);
			}
			/* 自動ウォーグストライク */
			if( pc_iswolf(sd) &&
			    (skill = pc_checkskill(sd,RA_WUGSTRIKE)) > 0 &&
			    atn_rand()%10000 < sd->paramc[5]*30 )
			{
				skill_castend_damage_id(src,bl,RA_WUGSTRIKE,skill,tick,0xf00000);
			}
			/* スナッチャー */
			if(sd->status.weapon != WT_BOW && (skill = pc_checkskill(sd,RG_SNATCHER)) > 0) {
				int skill2;
				if((skill*15 + 55) + (skill2 = pc_checkskill(sd,TF_STEAL))*10 > atn_rand()%1000) {
					if(dstmd && pc_steal_item(sd,dstmd))
						clif_skill_nodamage(src,bl,TF_STEAL,skill2,1);
					else if(battle_config.display_snatcher_skill_fail)
						clif_skill_fail(sd,skillid,0,0,0);
				}
			}
			/* テコン蹴り構え */
			if(sd->sc.data[SC_TKCOMBO].timer == -1) {
				int id = 0, lv = 0;
				if(sd->sc.data[SC_READYSTORM].timer != -1 && (lv = pc_checkskill(sd,TK_STORMKICK)) > 0 && atn_rand()%100 < 15) {
					// フェオリチャギ
					id = TK_STORMKICK;
				}
				else if(sd->sc.data[SC_READYDOWN].timer != -1 && (lv = pc_checkskill(sd,TK_DOWNKICK)) > 0 && atn_rand()%100 < 15) {
					// ネリョチャギ
					id = TK_DOWNKICK;
				}
				else if(sd->sc.data[SC_READYTURN].timer != -1 && (lv = pc_checkskill(sd,TK_TURNKICK)) > 0 && atn_rand()%100 < 15) {
					// トルリョチャギ
					id = TK_TURNKICK;
				}
				else if(sd->sc.data[SC_READYCOUNTER].timer != -1 && (lv = pc_checkskill(sd,TK_COUNTER)) > 0) {
					// アプチャオルリギ
					int counter_rate = 20;
					if(sd->sc.data[SC_COUNTER_RATE_UP].timer != -1 && (skill = pc_checkskill(sd,SG_FRIEND)) > 0) {
						counter_rate += counter_rate * (50 + 50 * skill);
						status_change_end(&sd->bl,SC_COUNTER_RATE_UP,-1);
					}
					if(atn_rand()%100 < counter_rate)
						id = TK_COUNTER;
				}
				if(id > 0 && lv > 0) {
					int delay = status_get_adelay(src) + 2000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
					// TKコンボ入力時間の最低保障追加
					if(delay < battle_config.tkcombo_delay_lower_limits) {
						delay = battle_config.tkcombo_delay_lower_limits;
					}
					if(delay > 0) {
						status_change_start(&sd->bl,SC_TKCOMBO,id,lv,0,0,delay,0);
						sd->ud.attackabletime = tick + delay;
					}
					clif_skill_nodamage(&sd->bl,&sd->bl,id-1,pc_checkskill(sd,id-1),1);
				}
			}
			/* エンチャントデットリーポイズン(猛毒効果) */
			if(sd->sc.data[SC_EDP].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DPOISON,sd->sc.data[SC_EDP].val2,sd->status.base_level)) {
					int lv = sd->sc.data[SC_EDP].val1;
					status_change_pretimer(bl,SC_DPOISON,lv,0,0,0,skill_get_time2(ASC_EDP,lv),0,tick+status_get_amotion(src));
				}
			}
			/* メルトダウン */
			if(sd->sc.data[SC_MELTDOWN].timer != -1) {
				if(atn_rand() % 100 < sd->sc.data[SC_MELTDOWN].val1) {
					// 武器破壊
					if(dstsd) {
						pc_break_equip(dstsd, LOC_RARM);
					} else {
						status_change_start(bl,SC_STRIPWEAPON,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
				if(atn_rand() % 1000 < sd->sc.data[SC_MELTDOWN].val1*7) {
					// 鎧破壊
					if(dstsd) {
						pc_break_equip(dstsd, LOC_BODY);
					} else {
						status_change_start(bl,SC_STRIPARMOR,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
			}
			/* ポイズニングウェポン */
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				int lv   = sd->sc.data[SC_POISONINGWEAPON].val1;
				int type = sd->sc.data[SC_POISONINGWEAPON].val2;
				if(atn_rand() % 10000 < status_change_rate(bl,type,sd->sc.data[SC_POISONINGWEAPON].val3,status_get_lv(src)))
					status_change_start(bl,type,lv,0,0,0,skill_get_time2(GC_POISONINGWEAPON,lv),0);
			}
		}
		break;
	case SM_BASH:			/* バッシュ（急所攻撃） */
		if( sd && pc_checkskill(sd,SM_FATALBLOW) > 0 ) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*(skilllv-5)+(sd->status.base_level/3),sd->status.base_level))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0,tick+status_get_amotion(src));
		}
		else if (md && mob_db[md->class_].mode_opt[MDOPT_FATALBLOW] > 0) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*(skilllv-5)+(status_get_lv(src)/3),mob_db[md->class_].lv))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case TF_POISON:			/* インベナム */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,400*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,0,0,0);
		break;

	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,200*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case AS_VENOMKNIFE:		/* ベナムナイフ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,TF_POISON,0,0,0);
		break;

	case AS_SONICBLOW:		/* ソニックブロー */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,200*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_FREEZINGTRAP:		/* フリージングトラップ */
	case MA_FREEZINGTRAP:
		if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_FLASHER:		/* フラッシャー */
		if( !(status_get_mode(bl)&MD_BOSS) && status_get_race(bl) != RCT_PLANT ) { // ボスと植物無効
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case WZ_METEOR:			/* メテオストーム */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case WZ_VERMILION:		/* ロードオブヴァーミリオン */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,400*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case WZ_FROSTNOVA:		/* フロストノヴァ */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv*500+3300,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case WZ_STORMGUST:		/* ストームガスト */
#ifdef PRE_RENEWAL
#ifdef DYNAMIC_SC_DATA
		status_calloc_sc_data(tsc);
#endif
		if(tsc) {	// ボス属性とその他でval3の用途が違うため演算位置を調整
			if(status_get_mode(bl)&MD_BOSS) {
				// ボス属性
				if(tsc->data[SC_FREEZE].val3 >= 3)
					tsc->data[SC_FREEZE].val3 = 0;
				tsc->data[SC_FREEZE].val3++;	// 重複ダメージのタイミングに使用(skill_unit_onplace_timer()内にて使用)
			} else {
				// 非ボス属性
				if(++tsc->data[SC_FREEZE].val3 >= 3) {	// 通常通り凍結タイミングに使用 
					tsc->data[SC_FREEZE].val3 = 0;
					if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,20000,status_get_lv(src)))
						status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
				}
			}
		}
#else
		if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,7500-500*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
#endif
		break;

	case HT_LANDMINE:		/* ランドマイン */
	case MA_LANDMINE:
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_SHOCKWAVE:		/* ショックウェーブトラップ */
		if(dstsd) {
			dstsd->status.sp -= dstsd->status.sp*(5+15*skilllv)/100;
			if(dstsd->status.sp <= 0)
				dstsd->status.sp = 0;
			clif_updatestatus(dstsd,SP_SP);
		}
		break;
	case HT_SANDMAN:		/* サンドマン */
	case MA_SANDMAN:
		if(!(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,1000*skilllv+4000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case TF_SPRINKLESAND:		/* 砂まき */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case TF_THROWSTONE:		/* 石投げ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,300,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case CR_HOLYCROSS:		/* ホーリークロス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case CR_GRANDCROSS:		/* グランドクロス */
	case NPC_GRANDDARKNESS:		/* グランドダークネス */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {	// 強制付与だが完全耐性には無効
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;

	case CR_SHIELDCHARGE:		/* シールドチャージ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1500+skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case RG_RAID:			/* サプライズアタック */
		{
#ifdef PRE_RENEWAL
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000+300*skilllv,status_get_lv(src)))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,3000,0,tick+status_get_amotion(src));
#else
			struct status_change *sc = status_get_sc(src);
			if(sc && sc->data[SC_RAID].timer != -1 && sc->data[SC_RAID].val2 > 0) {
				sc->data[SC_RAID].val2--;
				if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000+300*skilllv,status_get_lv(src)))
					status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,3000,0,tick+status_get_amotion(src));
			}
#endif
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,1000+300*skilllv,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case BA_FROSTJOKE:		/* 寒いジョーク */
		if(status_get_hp(bl) > 0) {	// 対象が死んでいない
			int rate = 0;
			if(battle_check_target(src,bl,BCT_ENEMY) > 0)
				rate = 1500 + 500 * skilllv;
			else if(battle_check_target(src,bl,BCT_PARTY) > 0)	// PTメンバにも低確率でかかる
				rate = (skilllv > 5) ? 1000 : (375 + 125 * skilllv) / 10 * 10;

			if(rate > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case DC_SCREAM:		/* スクリーム */
		if(status_get_hp(bl) > 0) {	// 対象が死んでいない
			int rate = 0;
			if(battle_check_target(src,bl,BCT_ENEMY) > 0)
				rate = 2500 + 500 * skilllv;
			else if(battle_check_target(src,bl,BCT_PARTY) > 0)	// PTメンバにも低確率でかかる
				rate = (skilllv > 5) ? 1250 : (625 + 125 * skilllv) / 10 * 10;

			if(rate > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_STUN,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case DC_UGLYDANCE:	/* 自分勝手なダンス */
		if(dstsd) {
			int sp = 5+skilllv*(5+pc_checkskill(dstsd,DC_DANCINGLESSON));
			pc_heal(dstsd,0,-sp);
		}
		break;

	case BD_LULLABY:	/* 子守唄 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,2550,status_get_lv(src)))
			status_change_pretimer(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case AM_ACIDTERROR:		/* アシッドテラー */
		if(bl->type == BL_PC && atn_rand()%100 < skill_get_time(skillid,skilllv)) {
			pc_break_equip((struct map_session_data *)bl, LOC_BODY);
			clif_emotion(bl,23);
		}
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	/* MOBの追加効果付きスキル */

	case NPC_PETRIFYATTACK:
	case NPC_POISON:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
	case NPC_BLINDATTACK:
		if(atn_rand() % 10000 < status_change_rate(bl,sc[skillid-NPC_POISON],skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,sc[skillid-NPC_POISON],skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_MENTALBREAKER:
		if(dstsd) {
			int sp = dstsd->status.max_sp*(10+skilllv*5)/100;
			if(sp < 1) sp = 1;
			pc_heal(dstsd,0,-sp);
		}
		break;
	case NPC_WEAPONBRAKER:
		if(dstsd && atn_rand()%100 < skilllv*10)
			pc_break_equip(dstsd, LOC_RARM);
		break;
	case NPC_ARMORBRAKE:
		if(dstsd && atn_rand()%100 < skilllv*10)
			pc_break_equip(dstsd, LOC_BODY);
		break;
	case NPC_HELMBRAKE:
		if(dstsd && atn_rand()%100 < skilllv*10)
			pc_break_equip(dstsd, LOC_HEAD2);
		break;
	case NPC_SHIELDBRAKE:
		if(dstsd && atn_rand()%100 < skilllv*10)
			pc_break_equip(dstsd, LOC_LARM);
		break;

	case LK_HEADCRUSH:		/* ヘッドクラッシュ */
		{
			int race = status_get_race(bl);
			if( !battle_check_undead(race,status_get_elem_type(bl)) && race != RCT_DEMON ) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,5000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;
	case LK_JOINTBEAT:		/* ジョイントビート */
		if( atn_rand()%100 < skilllv*5+5-status_get_str(bl)*27/100 )
			status_change_pretimer(bl,SC_JOINTBEAT,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case PF_SPIDERWEB:		/* スパイダーウェブ */
		{
			int sec = skill_get_time2(skillid,skilllv);
			if( map[src->m].flag.pvp || map[src->m].flag.gvg ) // 対人フィールドでは拘束時間半減
				sec = sec/2;
			unit_stop_walking(bl,1);
			status_change_start(bl,SC_SPIDERWEB,skilllv,0,0,0,sec,0);
		}
		break;
	case ASC_METEORASSAULT:		/* メテオアサルト */
		{
			int type = 0;
			switch(atn_rand()%3) {
				case 0: type = SC_STUN;  break;
				case 1: type = SC_BLIND; break;
				case 2: type = SC_BLEED; break;
			}
			if(atn_rand() % 10000 < status_change_rate(bl,type,500+skilllv*500,status_get_lv(src)))
				status_change_pretimer(bl,type,skilllv,0,0,0,skill_get_time2(sc2[type-SC_STONE],7),0,tick+status_get_amotion(src));
		}
		break;
	case MO_EXTREMITYFIST:		/* 阿修羅覇凰拳 */
		// 阿修羅を使うと5分間自然回復しないようになる
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0 );
		break;
	case HW_NAPALMVULCAN:			/* ナパームバルカン */
		// skilllv*5%の確率で状態異常判定を行い、その後100%の確率で呪い判定を行う
		if(atn_rand() % 10000 < skilllv*500) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
		}
		break;
	case PA_PRESSURE:		/* プレッシャー */
		if(dstsd) {
			// 対象に15% + skilllv*5%のSP攻撃(必中)
			int sp = dstsd->status.sp*(15+5*skilllv)/100;
			pc_heal(dstsd,0,-sp);
		}
		break;
	case WS_CARTTERMINATION:
		// skilllv*5%の確率でスタン
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,skill_get_time2(NPC_STUNATTACK,7),0,tick+status_get_amotion(src));
		break;
	case CR_ACIDDEMONSTRATION:	/* アシッドデモンストレーション */
		if(atn_rand()%100 <= skilllv) {
			if(dstsd)
				pc_break_equip(dstsd, LOC_RARM);
			else
				status_change_start(bl,SC_STRIPWEAPON,1,0,0,0,skill_get_time(RG_STRIPWEAPON,1),0);
		}
		if(atn_rand()%100 <= skilllv) {
			if(dstsd)
				pc_break_equip(dstsd, LOC_BODY);
			else
				status_change_start(bl,SC_STRIPARMOR,1,0,0,0,skill_get_time(RG_STRIPARMOR,1),0);
		}
		break;
	case TK_DOWNKICK:		/* ネリョチャギ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,33330,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,5000,0,tick+status_get_amotion(src));
		break;
	case TK_TURNKICK:		/* トルリョチャギ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,20000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case CH_TIGERFIST:		/* 伏虎拳 */
		if( atn_rand()%100 < 10 + skilllv*10 ) {
			int sec = skill_get_time2(skillid,skilllv) - status_get_agi(bl)*50;
			// 最低拘束時間補償（とりあえずアンクルの1/2）
			if(sec < 1500 + 15*skilllv)
				sec = 1500 + 15*skilllv;
			status_change_start(bl,SC_TIGERFIST,skilllv,0,0,0,sec,0);
			unit_stop_walking(bl,1);
		}
		break;
	case SL_STUN:			/* エストン */
		if(status_get_size(bl) == 1 && atn_rand() % 10000 < status_change_rate(bl,SC_STUN,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,2000,0,tick+status_get_amotion(src));
		break;
	case GS_FLING:			/* フライング */
		if(sd) {
			int i, y = 0;
			for(i=0; i<MAX_INVENTORY; i++) {
				if(sd->status.inventory[i].nameid == 7517) {
					y = (sd->status.inventory[i].amount > 4)? 4: sd->status.inventory[i].amount;
					pc_delitem(sd,i,y,0,1);
					break;
				}
			}
			status_change_start(bl,SC_FLING,skilllv+y,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case GS_BULLSEYE:		/* ブルズアイ */
		if(atn_rand()%10000 < 10) {
			if(dstsd) {
				dstsd->status.hp = 1;
				clif_updatestatus(dstsd,SP_HP);
			}
			if(dstmd && !(status_get_mode(bl)&MD_BOSS))
				dstmd->hp = 1;
		}
		break;
	case GS_DISARM:			/* ディスアーム */
		if(atn_rand()%100 < 10 + skilllv*10) {
			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_RARM)) {
						pc_unequipitem(dstsd,i,0);
						break;
					}
				}
			}
			if(dstmd && !(status_get_mode(bl)&MD_BOSS)) {
				status_change_start(bl,SC_DISARM,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			}
		}
		break;
	case GS_PIERCINGSHOT:		/* ピアーシングショット */
		{
			int race = status_get_race(bl);
			if( !(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) ) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,300*skilllv,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;
	case GS_FULLBUSTER:		/* フルバスター */
		{
			//status_change_start(src,SC_FULLBUSTER,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			if(atn_rand() % 10000 < status_change_rate(src,SC_BLIND,200*skilllv,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLIND,7,0,0,0,skill_get_time2(NPC_BLINDATTACK,7),0,tick+status_get_amotion(src));
		}
		break;
	case GS_GROUNDDRIFT:		/* グラウンドドリフト */
		if(unit && unit->group)
		{
			int type = 0;
			int timeid = 0;
			switch(unit->group->unit_id) {
				case UNT_GROUNDDRIFT_WIND:
					type = SC_STUN;
					timeid = NPC_STUNATTACK;
					break;
				case UNT_GROUNDDRIFT_DARK:
					type = SC_BLIND;
					timeid = NPC_BLINDATTACK;
					break;
				case UNT_GROUNDDRIFT_POISON:
					type = SC_POISON;
					timeid = NPC_POISON;
					break;
				case UNT_GROUNDDRIFT_WATER:
					type = SC_FREEZE;
					timeid = WZ_STORMGUST;
					break;
				case UNT_GROUNDDRIFT_FIRE:
					skill_blown(&unit->bl,bl,3|SAB_NODAMAGE);
					break;
			}

			// 確率は50%
			if(type > 0 && atn_rand() % 10000 < status_change_rate(bl,type,5000,status_get_lv(src)))
				status_change_pretimer(bl,type,7,0,0,0,skill_get_time2(timeid,7),0,tick+status_get_amotion(src));
		}
		break;
	case NJ_KASUMIKIRI:		/* 霞斬り */
		status_change_start(src,SC_HIDING,skilllv,0,1,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NJ_HYOUSYOURAKU:		/* 氷柱落し */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,1000+skilllv*1000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NPC_ICEBREATH:		/* アイスブレス */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,7000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NPC_ACIDBREATH:		/* アシッドブレス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,7000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_BLEEDING:		/* 出血攻撃 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,(skilllv < 5)? skilllv*2000:10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_HELLJUDGEMENT:		/* ヘルジャッジメント */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_EVILLAND:		/* イビルランド */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_CRITICALWOUND:		/* 致命傷攻撃 */
		status_change_start(bl,SC_CRITICALWOUND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case MER_CRASH:			/* クラッシュ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*600,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RK_WINDCUTTER:		/* ウィンドカッター */
		if(atn_rand() % 10000 < 300 + skilllv * 200)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RK_DRAGONBREATH:	/* ファイアードラゴンブレス */
		if(atn_rand() % 10000 < 500 + skilllv * 100)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RK_DRAGONBREATH_WATER:	// ウォータードラゴンブレス
		if(atn_rand() % 10000 < 500 + skilllv * 100)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case AB_ADORAMUS:		/* アドラムス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		status_change_start(bl,SC_DECREASEAGI,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WL_JACKFROST:		/* ジャックフロスト */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_CRIMSONROCK:	/* クリムゾンロック */
		if(atn_rand() % 10000 < 4000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WL_COMET:			/* コメット */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WL_EARTHSTRAIN:	/* アースストレイン */
		{
			int rate = 100 * skilllv * skilllv + 700 * skilllv + 600;
			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if( dstsd->status.inventory[i].equip & LOC_RARM &&
						(!tsc || (tsc->data[SC_CP_WEAPON].timer == -1 && tsc->data[SC_STRIPWEAPON].timer == -1)) ) {
						if(atn_rand() % 10000 < rate) {
							pc_unequipitem(dstsd,i,0);
							status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
						}
					}
					if( dstsd->status.inventory[i].equip & LOC_HEAD2 &&
						(!tsc || (tsc->data[SC_CP_HELM].timer == -1 && tsc->data[SC_STRIPHELM].timer == -1)) ) {
						if(atn_rand() % 10000 < rate) {
							pc_unequipitem(dstsd,i,0);
							status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
						}
					}
				}
			} else {
				if(atn_rand() % 10000 < rate) {
					status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				}
				if(atn_rand() % 10000 < rate) {
					status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				}
			}
		}
		break;
	case RA_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		if(!tsc || tsc->data[SC_ELECTRICSHOCKER].timer == -1) {
			int sec = skill_get_time2(skillid,skilllv) - status_get_agi(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			// 最低拘束時間補償
			if(sec < 3000 + 30 * skilllv)
				sec = 3000 + 30 * skilllv;
			unit_stop_walking(bl,1);
			status_change_start(bl,SC_ELECTRICSHOCKER,skilllv,0,0,0,sec,0);
		}
		break;
	case RA_WUGBITE:	/* ウォーグバイト */
		{
			int sec = skill_get_time(skillid,skilllv);
			if(sd)
				sec += pc_checkskill(sd,RA_TOOTHOFWUG) * 1000;
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0,tick+status_get_amotion(src));
		}
		break;
	case RA_MAGENTATRAP:	/* マゼンタトラップ */
	case RA_COBALTTRAP:		/* コバルトトラップ */
	case RA_MAIZETRAP:		/* メイズトラップ */
	case RA_VERDURETRAP:	/* ヴェルデュールトラップ */
		if(dstmd) {
			// ボス属性だった場合と暫定で40%の確率で使用失敗
			if((battle_config.boss_no_element_change && dstmd && dstmd->mode&MD_BOSS) || atn_rand() % 100 < 40)
				break;
			// 敵は属性レベルを維持する
			switch(skillid) {
				case RA_MAGENTATRAP:	// 火
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_FIRE;
					break;
				case RA_COBALTTRAP:		// 水
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WATER;
					break;
				case RA_MAIZETRAP:		// 地
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_EARTH;
					break;
				case RA_VERDURETRAP:	// 風
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WIND;
					break;
			}
		}
		else if(!dstsd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case RA_FIRINGTRAP:		/* ファイアリングトラップ */
	case RA_ICEBOUNDTRAP:	/* アイスバウンドトラップ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*1000+4000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_PILEBUNKER:		/* パイルバンカー */
		if(atn_rand() % 10000 < 500 + skilllv * 1500)
			status_change_release(bl,0x100); 	// 防御魔法解除
		break;
	case NC_FLAMELAUNCHER:	/* フレイムスローワー */
		if(atn_rand() % 10000 < 5000 + skilllv * 1000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_COLDSLOWER:		/* コールドスローワー */
		if((!tsc || tsc->data[SC_FREEZE].timer == -1) &&
			(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,2000 + skilllv * 1000,status_get_lv(src)))) {
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		} else if(atn_rand() % 10000 < skilllv * 1000) {
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NC_POWERSWING:	/* パワースイング */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_MAGMA_ERUPTION_DOTDAMAGE:	/* マグマイラプション(追撃) */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case LG_SHIELDPRESS:	/* シールドプレス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,3000+skilllv*800,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case LG_PINPOINTATTACK:	/* ピンポイントアタック */
		switch(skilllv) {
		case 1:
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,5000,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			break;
		case 2:
			if(dstsd && atn_rand() % 10000 < 5000)
				pc_break_equip(dstsd, LOC_HEAD2);
			break;
		case 3:
			if(dstsd && atn_rand() % 10000 < 5000)
				pc_break_equip(dstsd, LOC_LARM);
			break;
		case 4:
			if(dstsd && atn_rand() % 10000 < 5000)
				pc_break_equip(dstsd, LOC_BODY);
			break;
		case 5:
			if(dstsd && atn_rand() % 10000 < 5000)
				pc_break_equip(dstsd, LOC_RARM);
			break;
		}
		break;
	case LG_MOONSLASHER:	/* ムーンスラッシャー */
		if(atn_rand() % 10000 < 2000 + skilllv * 1600)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case LG_RAYOFGENESIS:	/* レイオブジェネシス */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,5000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;
	case LG_EARTHDRIVE:		/* アースドライブ */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_DRAGONCOMBO:	/* 双龍脚 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,100+skilllv*100,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_FALLENEMPIRE:	/* 大纏崩捶 */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_WINDMILL:		/* 旋風腿 */
		if(dstsd)
			status_change_start(bl,SC_SITDOWN_FORCE,skilllv,0,0,0,1000,0);
		else if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_GENTLETOUCH_QUIET:	/* 点穴 -默- */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SILENCE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_HOWLINGOFLION:	/* 獅子吼 */
		if(atn_rand() % 10000 < 500 + skilllv * 500)
			status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		if(tsc) {
			if(tsc->data[SC_SWING].timer != -1)
				status_change_end(bl,SC_SWING,-1);
			if(tsc->data[SC_SYMPHONY_LOVE].timer != -1)
				status_change_end(bl,SC_SYMPHONY_LOVE,-1);
			if(tsc->data[SC_MOONLIT_SERENADE].timer != -1)
				status_change_end(bl,SC_MOONLIT_SERENADE,-1);
			if(tsc->data[SC_RUSH_WINDMILL].timer != -1)
				status_change_end(bl,SC_RUSH_WINDMILL,-1);
			if(tsc->data[SC_ECHOSONG].timer != -1)
				status_change_end(bl,SC_ECHOSONG,-1);
			if(tsc->data[SC_HARMONIZE].timer != -1)
				status_change_end(bl,SC_HARMONIZE,-1);
			if(tsc->data[SC_SIREN].timer != -1)
				status_change_end(bl,SC_SIREN,-1);
			if(tsc->data[SC_SIRCLEOFNATURE].timer != -1)
				status_change_end(bl,SC_SIRCLEOFNATURE,-1);
			if(tsc->data[SC_GLOOMYDAY].timer != -1)
				status_change_end(bl,SC_GLOOMYDAY,-1);
			if(tsc->data[SC_SONG_OF_MANA].timer != -1)
				status_change_end(bl,SC_SONG_OF_MANA,-1);
			if(tsc->data[SC_DANCE_WITH_WUG].timer != -1)
				status_change_end(bl,SC_DANCE_WITH_WUG,-1);
			if(tsc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1)
				status_change_end(bl,SC_SATURDAY_NIGHT_FEVER,-1);
			if(tsc->data[SC_LERADS_DEW].timer != -1)
				status_change_end(bl,SC_LERADS_DEW,-1);
			if(tsc->data[SC_MELODYOFSINK].timer != -1)
				status_change_end(bl,SC_MELODYOFSINK,-1);
			if(tsc->data[SC_BEYOND_OF_WARCRY].timer != -1)
				status_change_end(bl,SC_BEYOND_OF_WARCRY,-1);
			if(tsc->data[SC_UNLIMITED_HUMMING_VOICE].timer != -1)
				status_change_end(bl,SC_UNLIMITED_HUMMING_VOICE,-1);
		}
		break;

	case WM_SOUND_OF_DESTRUCTION:	/* サウンドオブディストラクション */
		if(tsc && atn_rand() % 10000 < 4000 + skilllv * 1000 - (status_get_lv(bl) / 5 + status_get_dex(bl) / 5 + status_get_int(bl) / 5) * 100) {
			if(tsc->data[SC_SWING].timer != -1)
				status_change_end(bl,SC_SWING,-1);
			if(tsc->data[SC_SYMPHONY_LOVE].timer != -1)
				status_change_end(bl,SC_SYMPHONY_LOVE,-1);
			if(tsc->data[SC_MOONLIT_SERENADE].timer != -1)
				status_change_end(bl,SC_MOONLIT_SERENADE,-1);
			if(tsc->data[SC_RUSH_WINDMILL].timer != -1)
				status_change_end(bl,SC_RUSH_WINDMILL,-1);
			if(tsc->data[SC_ECHOSONG].timer != -1)
				status_change_end(bl,SC_ECHOSONG,-1);
			if(tsc->data[SC_HARMONIZE].timer != -1)
				status_change_end(bl,SC_HARMONIZE,-1);
			if(tsc->data[SC_SIREN].timer != -1)
				status_change_end(bl,SC_SIREN,-1);
			if(tsc->data[SC_SIRCLEOFNATURE].timer != -1)
				status_change_end(bl,SC_SIRCLEOFNATURE,-1);
			if(tsc->data[SC_GLOOMYDAY].timer != -1)
				status_change_end(bl,SC_GLOOMYDAY,-1);
			if(tsc->data[SC_SONG_OF_MANA].timer != -1)
				status_change_end(bl,SC_SONG_OF_MANA,-1);
			if(tsc->data[SC_DANCE_WITH_WUG].timer != -1)
				status_change_end(bl,SC_DANCE_WITH_WUG,-1);
			if(tsc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1)
				status_change_end(bl,SC_SATURDAY_NIGHT_FEVER,-1);
			if(tsc->data[SC_LERADS_DEW].timer != -1)
				status_change_end(bl,SC_LERADS_DEW,-1);
			if(tsc->data[SC_MELODYOFSINK].timer != -1)
				status_change_end(bl,SC_MELODYOFSINK,-1);
			if(tsc->data[SC_BEYOND_OF_WARCRY].timer != -1)
				status_change_end(bl,SC_BEYOND_OF_WARCRY,-1);
			if(tsc->data[SC_UNLIMITED_HUMMING_VOICE].timer != -1)
				status_change_end(bl,SC_UNLIMITED_HUMMING_VOICE,-1);
		}
		break;
	case SO_EARTHGRAVE:		/* アースグレイヴ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_DIAMONDDUST:	/* ダイヤモンドダスト */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500 + skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_CLOUD_KILL:		/* クラウドキル */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_HELLS_PLANT_ATK:	/* ヘルズプラント(攻撃) */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,500 + skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,2000 + skilllv * 1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_DEMONIC_FIRE:	/* デモニックファイアー */
		if(atn_rand() % 10000 < 400 + skilllv * 400)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_SLINGITEM_RANGEMELEEATK:	/* スリングアイテム(遠距離攻撃) */
		switch(skilllv) {
		case 1:		// ココナッツ爆弾
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,5000,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,5000,status_get_lv(src)))
				status_change_pretimer(bl,SC_STUN,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			break;
		case 2:		// メロン爆弾
			status_change_start(bl,SC_MELON_BOMB,15,0,0,0,skill_get_time(skillid,skilllv),0);
			break;
		case 4:		// バナナ爆弾
			status_change_start(bl,SC_BANANA_BOMB,15,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		}
		break;
	case KO_JYUMONJIKIRI:	/* 十文字斬り */
		if(!tsc || tsc->data[GetSkillStatusChangeTable(skillid)].timer == -1)
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case KO_MAKIBISHI:		/* 撒菱 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SU_SCRATCH:	/* ひっかく */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,500 + skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SU_SV_STEMSPEAR:	/* マタタビランス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SU_SCAROFTAROU:	/* タロウの傷 */
		if(atn_rand() % 10000 < 60 + status_get_jlv(src)/3 + status_get_dex(src)/10) {	// 暫定確率
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case NPC_UGLYDANCE:
		if(dstsd) {
			int sp = 5+skilllv*5;
			pc_heal(dstsd,0,-sp);
		}
		break;
	}

	// 追加状態異常
	switch(skillid) {
	case HT_FREEZINGTRAP:	// カード効果無視のスキル
	case AS_VENOMKNIFE:
	case CR_GRANDCROSS:
	case NPC_GRANDDARKNESS:
	case AM_DEMONSTRATION:
	case AM_ACIDTERROR:
	case ASC_METEORASSAULT:
	case ASC_BREAKER:
	case AS_SPLASHER:
	case WS_CARTTERMINATION:
	case CR_ACIDDEMONSTRATION:
	case GS_BULLSEYE:
	case NJ_ZENYNAGE:
	case ITM_TOMAHAWK:
	case KO_MUCHANAGE:
		return 0;
	default:
		if(sd && attack_type&BF_WEAPON && skillid > 0) {	// 物理攻撃スキル
			/* エンチャントデットリーポイズン(猛毒効果) */
			if(sd->sc.data[SC_EDP].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DPOISON,sd->sc.data[SC_EDP].val2,sd->status.base_level)) {
					int lv = sd->sc.data[SC_EDP].val1;
					status_change_pretimer(bl,SC_DPOISON,lv,0,0,0,skill_get_time2(ASC_EDP,lv),0,tick+status_get_amotion(src));
				}
			}
			/* メルトダウン */
			if(sd->sc.data[SC_MELTDOWN].timer != -1) {
				if(atn_rand() % 100 < sd->sc.data[SC_MELTDOWN].val1) {
					// 武器破壊
					if(dstsd) {
						pc_break_equip(dstsd, LOC_RARM);
					} else {
						status_change_start(bl,SC_STRIPWEAPON,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
				if(atn_rand() % 1000 < sd->sc.data[SC_MELTDOWN].val1*7) {
					// 鎧破壊
					if(dstsd) {
						pc_break_equip(dstsd, LOC_BODY);
					} else {
						status_change_start(bl,SC_STRIPARMOR,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
			}
			/* ポイズニングウェポン */
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				int lv   = sd->sc.data[SC_POISONINGWEAPON].val1;
				int type = sd->sc.data[SC_POISONINGWEAPON].val2;
				if(atn_rand() % 10000 < status_change_rate(bl,type,sd->sc.data[SC_POISONINGWEAPON].val3,status_get_lv(src)))
					status_change_start(bl,type,lv,0,0,0,skill_get_time2(GC_POISONINGWEAPON,lv),0);
			}
		}
	}

	// スキルの追加状態異常
	if(sd && sd->skill_addeff.count > 0 && skillid > 0) {
		int i;
		for(i = 0; i < sd->skill_addeff.count; i++) {
			if(sd->skill_addeff.id[i] == skillid) {
				int j, rate;
				for(j = 0; j < MAX_EFF_TYPE; j++) {
					rate = sd->skill_addeff.addeff[i][j];
					status_change_addeff_start(src,bl,j,rate,1,tick);
				}
			}
		}
	}

	if(attack_type&BF_WEAPON)
	{
		// 物理通常攻撃なら混乱終了
		if(tsc && tsc->data[SC_CONFUSION].timer != -1 && skillid == 0)
			status_change_end(bl,SC_CONFUSION,-1);

		// カードによる追加効果
		if(sd) {
			int i, rate;

			for(i = 0; i < MAX_EFF_TYPE; i++) {
				if(!dstmd || dstmd->class_ != MOBID_EMPERIUM) {
					if(sd->addeff_range_flag[i] > 2) {
						sd->addeff_range_flag[i] -= 2;	// レンジフラグがあれば元に戻す
						continue;
					}

					rate = sd->addeff[i];
					if(sd->state.arrow_atk)
						rate += sd->arrow_addeff[i];

					status_change_addeff_start(src,bl,i,rate,2,tick);
				}

				rate = sd->addeff2[i];
				if(sd->state.arrow_atk)
					rate += sd->arrow_addeff2[i];

				status_change_addeff_start(src,src,i,rate,3,tick);
			}
		}

		// 村正による呪い
		if(sd && sd->curse_by_muramasa > 0)
		{
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_CURSE,sd->curse_by_muramasa,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
		}

		// 殴ってアイテム消滅
		if(sd && sd->loss_equip_flag&0x0010)
		{
			int i;
			for(i = 0; i < EQUIP_INDEX_MAX; i++)
			{
				if(atn_rand()%10000 < sd->loss_equip_rate_when_attack[i])
				{
					pc_lossequipitem(sd,i,0);
				}
			}
		}

		// 殴ってアイテムブレイク
		if(sd && sd->loss_equip_flag&0x0100)
		{
			int i;
			for(i = 0; i < EQUIP_INDEX_MAX; i++)
			{
				if(atn_rand()%10000 < sd->break_myequip_rate_when_attack[i])
				{
					pc_break_equip2(sd,i);
				}
			}
		}

		// 殴ってmob変化
		if(sd && dstmd && mob_db[dstmd->class_].race != RCT_HUMAN && !map[dstmd->bl.m].flag.nobranch &&
		   !(mob_db[dstmd->class_].mode&MD_BOSS) && dstmd->class_ != MOBID_EMPERIUM && dstmd->state.special_mob_ai != 1)
		{
			if(atn_rand()%10000 < sd->mob_class_change_rate)
			{
				//clif_skill_nodamage(src,bl,SA_CLASSCHANGE,1,1);
				mob_class_change_randam(dstmd,sd->status.base_level);
			}
		}

	// 魔法による追加状態異常
	} else if(attack_type&BF_MAGIC) {
		if(sd) {
			int i, rate;
			for(i = 0; i < MAX_EFF_TYPE; i++) {
				rate = sd->magic_addeff[i];
				status_change_addeff_start(src,bl,i,rate,4,tick);
			}
		}
	}

	return 0;
}

/*=========================================================================
 * スキル攻撃吹き飛ばし処理
 *  count -> 0x00XYZZZZ
 *	X: 吹き飛ばし方向指定(逆向き)
 *	   ただし0（真北指定、真南に飛ばす）なら8として代入
 *	Y: フラグ
 *		SAB_NOMALBLOW   : srcとtargetの位置関係で吹飛ばし方向を決定
 *		SAB_REVERSEBLOW : targetの向きと逆方向に吹飛ぶ
 *		SAB_NODAMAGE    : ダメージを発生させずに吹飛ばす
 *		SAB_NOPATHSTOP  : 吹き飛び経路に壁があったらそこで止まる
 *　	SAB_NOTKNOCK    : ノックバックではないスキル用の特殊フラグ
 *	Z: 吹き飛ばしセル数
 *-------------------------------------------------------------------------
 */
int skill_blown( struct block_list *src, struct block_list *target,int count)
{
	int dx=0,dy=0,nx,ny;
	int dir,ret;
	struct status_change *sc = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	// シーズなら吹き飛ばし失敗
	if(map[target->m].flag.gvg)
		return 0;

	// 吹き飛ばしセル数が0
	if((count&0xffff) == 0)
		return 0;

	sc = status_get_sc(target);

	if(sc) {
		if(sc->data[SC_ANKLE].timer != -1)	// アンクル中は無条件で吹き飛ばされない
			return 0;
		if(sc->data[SC_SU_STOOP].timer != -1)	// うずくまる解除
			status_change_end(target, SC_SU_STOOP, -1);
	}

	if(target->type == BL_PC) {
		if(!(count&SAB_NOTKNOCK) && ((struct map_session_data *)target)->special_state.no_knockback)
			return 0;
		// バジリカ中は吹き飛ばされない
		if(sc && sc->data[SC_BASILICA].timer!=-1 && sc->data[SC_BASILICA].val2==target->id)
			return 0;
	} else if(target->type == BL_MOB) {
		struct mob_data *md=(struct mob_data *)target;
		if(battle_config.boss_no_knockbacking==1 && mob_db[md->class_].mode&MD_BOSS)
			return 0;
		if(battle_config.boss_no_knockbacking==2 && mob_db[md->class_].mexp > 0)
			return 0;
	} else if(target->type & (BL_PET | BL_SKILL)) {
		;	// 何もしない
	} else {
		return 0;
	}

	if(count&0xf00000) {
		dir = (count>>20)&0xf;
		if(dir == 8)	// 0に置換する
			dir = 0;
	}
	else if(count&SAB_REVERSEBLOW || (target->x == src->x && target->y == src->y)) {
		dir = status_get_dir(target);
	}
	else {
		dir = path_calc_dir(target,src->x,src->y);
	}
	if(dir >= 0 && dir < 8) {
		dx = -dirx[dir];
		dy = -diry[dir];
	}

	ret = path_blownpos(target->m,target->x,target->y,dx,dy,count&0xffff,(count&SAB_NOPATHSTOP)? 1: 0);
	nx  = ret>>16;
	ny  = ret&0xffff;

	if(count&SAB_NODAMAGE)
		unit_stop_walking(target,0);	// ダメージディレイ無し
	else
		unit_stop_walking(target,2);	// ダメージディレイ有り

	if(target->type == BL_SKILL) {
		struct skill_unit *su = (struct skill_unit *)target;
		skill_unit_move_unit_group(su->group,target->m,nx-target->x,ny-target->y);
	} else {
		unit_movepos(target,nx,ny,(count&SAB_NODAMAGE)? 0: 1);
	}

	return 1;
}

/*=========================================================================
 * スキル攻撃吹き飛ばし処理(カード追加効果用)
 *-------------------------------------------------------------------------
 */
int skill_add_blown( struct block_list *src, struct block_list *target,int skillid,int flag)
{
	nullpo_retr(0, src);
	nullpo_retr(0, target);

	if(src->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)src;
		int i;
		for(i = 0; i<sd->skill_blow.count; i++)
		{
			if(sd->skill_blow.id[i] == skillid)
			{
				 skill_blown(src,target,sd->skill_blow.grid[i]|flag);
				 return 1;
			}
		}
	}
	return 0;
}

/*==========================================
 * スキル範囲攻撃用(map_foreachinareaから呼ばれる)
 * flagについて：16進図を確認
 * MSB <- 0ffTffff -> LSB
 *  ffff = 自由に使用可能
 *     T = ターゲット選択用(BCT_*)
 *     0 = 予約。0に固定
 *------------------------------------------
 */
static int skill_area_temp[8];	/* 一時変数。必要なら使う。 */
typedef int (*SkillFunc)(struct block_list *,struct block_list *,int,int,unsigned int,int);

static int skill_area_sub( struct block_list *bl,va_list ap )
{
	struct block_list *src;
	int skill_id,skill_lv,flag;
	unsigned int tick;
	SkillFunc func;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	if(!(bl->type & (BL_CHAR | BL_SKILL)))
		return 0;

	src      = va_arg(ap,struct block_list *); // ここではsrcの値を参照していないのでNULLチェックはしない
	skill_id = va_arg(ap,int);
	skill_lv = va_arg(ap,int);
	tick     = va_arg(ap,unsigned int);
	flag     = va_arg(ap,int);
	func     = va_arg(ap,SkillFunc);

	if(battle_check_target(src,bl,flag) > 0)
		return func(src,bl,skill_id,skill_lv,tick,flag);

	return 0;
}

static int skill_area_trap_sub( struct block_list *bl,va_list ap )
{
	struct block_list *src;
	struct skill_unit *unit;
	int skill_id, skill_lv, flag;
	unsigned int tick;
	SkillFunc func;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = (struct skill_unit *)bl);

	if(!unit->alive || !unit->group)
		return 0;

	src      = va_arg(ap,struct block_list *);
	skill_id = va_arg(ap,int);
	skill_lv = va_arg(ap,int);
	tick     = va_arg(ap,unsigned int);
	flag     = va_arg(ap,int);
	func     = va_arg(ap,SkillFunc);

	// battle_check_targetで該当しない罠が攻撃対象
	switch (unit->group->unit_id) {
		case UNT_FIREPILLAR_WAITING:	/* ファイアーピラー(発動前) */
		case UNT_SKIDTRAP:	/* スキッドトラップ */
		case UNT_LANDMINE:	/* ランドマイン */
		case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
		case UNT_SANDMAN:	/* サンドマン */
		case UNT_FLASHER:	/* フラッシャー */
		case UNT_FREEZINGTRAP:	/* フリージングトラップ */
		case UNT_TALKIEBOX:	/* トーキーボックス */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN)
				break;
			return 0;
		case UNT_ANKLESNARE:	/* アンクルスネア */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN || unit->group->val2 > 0)
				break;
			return 0;
		case UNT_MAGENTATRAP:	/* マゼンタトラップ */
		case UNT_COBALTTRAP:	/* コバルトトラップ */
		case UNT_MAIZETRAP:		/* メイズトラップ */
		case UNT_VERDURETRAP:	/* ヴェルデュールトラップ */
		case UNT_FIRINGTRAP:	/* ファイアリングトラップ */
		case UNT_ICEBOUNDTRAP:	/* アイスバウンドトラップ */
		case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		case UNT_CLUSTERBOMB:	/* クラスターボム */
			if(skill_id == RA_SENSITIVEKEEN)
				break;
			return 0;
		default:
			return 0;
	}

	return func(src,bl,skill_id,skill_lv,tick,flag);
}

/*==========================================
 * スキルユニットの重ね置きチェック
 *------------------------------------------
 */
static int skill_check_unit_range_sub( struct block_list *bl,va_list ap )
{
	struct skill_unit *unit;
	int skillid,ug_id;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = (struct skill_unit *)bl);

	if (!unit->alive || !unit->group)
		return 0;

	skillid = va_arg(ap,int);
	ug_id = unit->group->skill_id;

	switch (skillid)
	{
		case MG_SAFETYWALL:
		case AL_PNEUMA:
			if(ug_id == MG_SAFETYWALL || ug_id == AL_PNEUMA) {
				return 1;
			}
			break;
		case AL_WARP:
		case HT_SKIDTRAP:
		case HT_LANDMINE:
		case HT_ANKLESNARE:
		case HT_SHOCKWAVE:
		case HT_SANDMAN:
		case HT_FLASHER:
		case HT_FREEZINGTRAP:
		case HT_BLASTMINE:
		case HT_CLAYMORETRAP:
		case HT_TALKIEBOX:
		case MA_SKIDTRAP:
		case MA_LANDMINE:
		case MA_SANDMAN:
		case MA_FREEZINGTRAP:
			if( (ug_id >= HT_SKIDTRAP && ug_id <= HT_CLAYMORETRAP) ||
			    (ug_id >= MA_SKIDTRAP && ug_id <= MA_FREEZINGTRAP) ||
			    ug_id == HT_TALKIEBOX )
			{
				return 1;
			}
			break;
		case HP_BASILICA:
			if( (ug_id >= HT_SKIDTRAP && ug_id <= HT_CLAYMORETRAP) ||
			    (ug_id >= MA_SKIDTRAP && ug_id <= MA_FREEZINGTRAP) ||
			    ug_id == HT_TALKIEBOX ||
			    ug_id == PR_SANCTUARY )
			{
				return 1;
			}
			break;
		default:	// 同じスキルユニットでなければ許可
			if(ug_id == skillid) {
				return 1;
			}
			break;
	}

	return 0;
}

static int skill_check_unit_range(int m,int x,int y,int skillid,int skilllv)
{
	int range = skill_get_unit_range(skillid,skilllv);
	int layout_type = skill_get_unit_layout_type(skillid,skilllv);

	if(layout_type == -1 || layout_type > MAX_SQUARE_LAYOUT) {
		printf("skill_check_unit_range: unsupported layout type %d for skill %d\n",layout_type,skillid);
		return 0;
	}

	// とりあえず正方形のユニットレイアウトのみ対応
	range += layout_type;
	return map_foreachinarea(skill_check_unit_range_sub,m,
			x-range,y-range,x+range,y+range,BL_SKILL,skillid);
}

/*==========================================
 * スキルユニットの足元置きチェック
 *------------------------------------------
 */
static int skill_check_unit_range2_sub( struct block_list *bl,va_list ap )
{
	int skillid;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	if(!(bl->type & BL_CHAR))
		return 0;

	if(unit_isdead(bl))
		return 0;

	skillid = va_arg(ap,int);
	if(skillid == HP_BASILICA && skill_area_temp[1] == bl->id)
		return 0;

	return 1;
}

static int skill_check_unit_range2(int m,int x,int y,int skillid, int skilllv)
{
	int range = skill_get_unit_range(skillid,skilllv);
	int layout_type = skill_get_unit_layout_type(skillid,skilllv);

	if(layout_type == -1 || layout_type > MAX_SQUARE_LAYOUT) {
		printf("skill_check_unit_range2: unsupported layout type %d for skill %d\n",layout_type,skillid);
		return 0;
	}

	// とりあえず正方形のユニットレイアウトのみ対応
	range += layout_type;
	return map_foreachinarea(skill_check_unit_range2_sub,m,
			x-range,y-range,x+range,y+range,BL_CHAR,skillid);
}

/*==========================================
 * スキル発動の遅延
 *------------------------------------------
 */
struct castend_delay {
	struct block_list *src;
	int target;
	int id;
	int lv;
	int flag;
};

static int skill_castend_delay_sub(int tid, unsigned int tick, int id, void *data)
{
	struct castend_delay *dat = (struct castend_delay *)data;
	struct block_list *target = map_id2bl(dat->target);

	if (target && dat && map_id2bl(id) == dat->src && target->prev != NULL)
		skill_castend_damage_id(dat->src, target, dat->id, dat->lv, tick, dat->flag);
	aFree(dat);
	return 0;
}

int skill_castend_delay(struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct castend_delay *dat;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	dat = (struct castend_delay *)aCalloc(1, sizeof(struct castend_delay));
	dat->src    = src;
	dat->target = bl->id;
	dat->id     = skillid;
	dat->lv     = skilllv;
	dat->flag   = flag;
	add_timer2(tick, skill_castend_delay_sub, src->id, dat);

	return 0;
}

/*=========================================================================
 * 範囲スキル使用処理小分けここから
 */
/* 対象の数をカウントする。（skill_area_temp[0]を初期化しておくこと） */
static int skill_area_sub_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(skill_area_temp[0] < 0xffff)
		skill_area_temp[0]++;
	return 1;
}

/*==========================================
 * 水場の数を数える
 *------------------------------------------
 */
static int skill_count_water(struct block_list *src,int range)
{
	int i,x,y,cnt = 0,size = range*2+1;
	struct skill_unit *unit;

	for (i=0;i<size*size;i++) {
		x = src->x+(i%size-range);
		y = src->y+(i/size-range);
		if(map_find_skill_unit_oncell(src,x,y,SA_LANDPROTECTOR,NULL))
			continue;
		if(map_getcell(src->m,x,y,CELL_CHKWATER)) {
			cnt++;
			continue;
		}
		unit = map_find_skill_unit_oncell(src,x,y,SA_DELUGE,NULL);
		if(unit) {
			cnt++;
			skill_delunit(unit);
		} else {
			unit = map_find_skill_unit_oncell(src,x,y,NJ_SUITON,NULL);
			if(unit) {
				cnt++;
				skill_delunit(unit);
			}
		}
	}
	return cnt;
}
/*=========================================================================
 * パーティ内のミンストレル、ワンダラーの数をカウントする。（skill_area_temp[0]を初期化しておくこと）
 *------------------------------------------
 */
static int skill_partner_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(src->type != BL_PC || target->type != BL_PC)
		return 0;

	if(skill_area_temp[0] < 0xffff && (((struct map_session_data *)target)->s_class.job == PC_JOB_MI || ((struct map_session_data *)target)->s_class.job == PC_JOB_WA) &&
		    ((struct map_session_data *)src)->status.party_id > 0 &&
		    ((struct map_session_data *)target)->status.party_id > 0 &&
		    ((struct map_session_data *)src)->status.party_id == ((struct map_session_data *)target)->status.party_id &&
		    !unit_isdead(target) )
		skill_area_temp[0]++;
	return 1;
}

/*==========================================
 *
 *------------------------------------------
 */
static int skill_timerskill_timer(int tid, unsigned int tick, int id, void *data)
{
	struct block_list *src = map_id2bl(id);
	struct unit_data *ud;
	struct skill_timerskill *skl;
	int range;

	nullpo_retr(0, src);
	nullpo_retr(0, ud = unit_bl2ud(src));
	nullpo_retr(0, skl = (struct skill_timerskill*)data);

	linkdb_erase( &ud->skilltimerskill, skl);
	skl->timer = -1;

	do {
		if(src->prev == NULL)
			break;
		if(skl->target_id) {
			struct block_list *target = NULL;

			if(unit_isdead(src))
				break;
			target = map_id2bl(skl->target_id);

			// インティミデイトとエクスパルシオンはtargetが存在しなくても良いのでここの判定は除外
			if(skl->skill_id != RG_INTIMIDATE && skl->skill_id != NPC_EXPULSION && skl->skill_id != SC_FATALMENACE) {
				if(target == NULL || src->m != target->m)
					break;
				if(target->prev == NULL || unit_isdead(target))
					break;
			}

			switch(skl->skill_id) {
			case RG_INTIMIDATE:
				if(src->type == BL_PC && !map[src->m].flag.noteleport)
					pc_randomwarp((struct map_session_data *)src,3);
				else if(src->type == BL_MOB && !map[src->m].flag.monster_noteleport)
					mob_warp((struct mob_data *)src,-1,-1,-1,3);
				else
					break;
				if(target && target->prev != NULL && src->m == target->m) {
					struct cell_xy free_cell[3*3];
					int count, x, y;
					count = map_searchfreecell(free_cell, src->m, src->x-1, src->y-1, src->x+1, src->y+1);
					if(count > 0) {
						int n = atn_rand() % count;
						x = free_cell[n].x;
						y = free_cell[n].y;
					} else {
						x = src->x;
						y = src->y;
					}
					if(target->type == BL_PC && !unit_isdead(target))
						pc_setpos((struct map_session_data *)target,map[src->m].name,x,y,3);
					else if(target->type == BL_MOB)
						mob_warp((struct mob_data *)target,-1,x,y,3);
				}
				break;
			case NPC_EXPULSION:
				if(target && target->prev != NULL && src->m == target->m) {
					if(target->type == BL_PC && !map[target->m].flag.noteleport && !unit_isdead(target))
						pc_randomwarp((struct map_session_data *)target,3);
					else if(target->type == BL_MOB && !map[target->m].flag.monster_noteleport)
						mob_warp((struct mob_data *)target,-1,-1,-1,3);
				}
				break;
			case BA_FROSTJOKE:			/* 寒いジョーク */
			case DC_SCREAM:				/* スクリーム */
				range=AREA_SIZE;		// 視界全体
				map_foreachinarea(skill_frostjoke_scream,src->m,src->x-range,src->y-range,
					src->x+range,src->y+range,BL_CHAR,src,skl->skill_id,skl->skill_lv,tick);
				break;
			case WZ_WATERBALL:
				if (skl->type>1) {
					skl->timer = 0;	// skill_addtimerskillで使用されないように
					skill_addtimerskill(src,tick+150,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type-1,skl->flag);
					skl->timer = -1;
				}
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case RK_HUNDREDSPEAR:		/* ハンドレッドスピアのスピアブーメラン追撃 */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,KN_SPEARBOOMERANG);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,KN_SPEARBOOMERANG,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,KN_SPEARBOOMERANG,1,tick,skl->flag);
				}
				break;
			case GC_DARKILLUSION:		/* ダークイリュージョンのクロスインパクト追撃 */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,GC_CROSSIMPACT);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,GC_CROSSIMPACT,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,GC_CROSSIMPACT,1,tick,skl->flag);
				}
				break;
			case NC_POWERSWING:		/* パワースイングのアックスブーメラン追撃 */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,NC_AXEBOOMERANG);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,1,tick,skl->flag);
				}
				break;
			case AB_DUPLELIGHT_MELEE:		/* デュプレライト(物理) */
			case WM_REVERBERATION_MELEE:	/* 振動残響(物理) */
				battle_skill_attack(BF_WEAPON,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case AB_DUPLELIGHT_MAGIC:		/* デュプレライト(魔法) */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_CHAINLIGHTNING_ATK:		/* チェーンライトニング(連鎖) */
				{
					struct block_list *tbl = NULL;
					int c = 0;

					battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,(0x0f<<20)|skl->flag);
					map_foreachinarea(skill_chainlightning,
						target->m,target->x-3,target->y-3,target->x+3,target->y+3,BL_CHAR,
						src,target->id,&tbl,&c);
					if(tbl && skl->type < skl->skill_lv + 4) {
						skill_addtimerskill(src,tick+700,tbl->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					} else if(skl->type < 4) {
						skill_addtimerskill(src,tick+700,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					}
				}
				break;
			case NPC_EARTHQUAKE:			/* アースクエイク */
			case WL_HELLINFERNO:			/* ヘルインフェルノ */
			case WL_SUMMON_ATK_FIRE:		/* サモンファイアボール(攻撃) */
			case WL_SUMMON_ATK_WIND:		/* サモンボールライトニング(攻撃) */
			case WL_SUMMON_ATK_WATER:		/* サモンウォーターボール(攻撃) */
			case WL_SUMMON_ATK_GROUND:		/* サモンストーン(攻撃) */
			case WM_REVERBERATION_MAGIC:	/* 振動残響(魔法) */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_TETRAVORTEX_FIRE:		/* テトラボルテックス(火) */
			case WL_TETRAVORTEX_WATER:		/* テトラボルテックス(水) */
			case WL_TETRAVORTEX_WIND:		/* テトラボルテックス(風) */
			case WL_TETRAVORTEX_GROUND:		/* テトラボルテックス(地) */
				clif_skill_nodamage(src,target,skl->skill_id,skl->skill_lv,1);
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case RA_SENSITIVEKEEN:		/* 鋭敏な嗅覚のウォグバイト追撃 */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,RA_WUGBITE);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,RA_WUGBITE,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,RA_WUGBITE,1,tick,skl->flag);
				}
				break;
			case SR_DRAGONCOMBO:
			case SR_FALLENEMPIRE:
			case SR_TIGERCANNON:
			case SR_SKYNETBLOW:
				if(src->type == BL_PC) {
					if(unit_distance(src,target) >= 3)
						break;
					skill_castend_damage_id(src,target,skl->skill_id,pc_checkskill((struct map_session_data *)src,skl->skill_id),tick,skl->flag);
				}
				break;
			case SC_FATALMENACE:		/* フェイタルメナス */
				if(skl->flag) {		// 使用者の処理
					if(src->type == BL_PC && !map[src->m].flag.noteleport)
						pc_setpos((struct map_session_data *)src,map[src->m].name,skl->x,skl->y,3);
					else if(src->type == BL_MOB && !map[src->m].flag.monster_noteleport)
						mob_warp((struct mob_data *)src,-1,skl->x,skl->y,3);
				}
				if(target && !unit_isdead(target)) {
					struct cell_xy free_cell[3*3];
					int count, x, y;
					count = map_searchfreecell(free_cell, src->m, skl->x-1, skl->y-1, skl->x+1, skl->y+1);
					if(count > 0) {
						int n = atn_rand() % count;
						x = free_cell[n].x;
						y = free_cell[n].y;
					} else {
						x = src->x;
						y = src->y;
					}
					if(target->type == BL_PC && !map[target->m].flag.noteleport)
						pc_setpos((struct map_session_data *)target,map[src->m].name,x,y,3);
					else if(target->type == BL_MOB && !map[src->m].flag.monster_noteleport)
						mob_warp((struct mob_data *)target,-1,x,y,3);
				}
				break;
			case NPC_PULSESTRIKE2:		/* パルスストライクIIの連撃 */
				skill_castend_damage_id(src,target,skl->skill_id,skl->skill_lv,tick,0);
				break;
			case NPC_DANCINGBLADE_ATK:		/* ダンシングブレイド(連鎖) */
				{
					struct block_list *tbl = NULL;
					int c = 0;

					battle_skill_attack(BF_WEAPON,src,src,target,skl->skill_id,skl->skill_lv,tick,(0x0f<<20)|skl->flag);
					map_foreachinarea(skill_chainlightning,
						target->m,target->x-5,target->y-5,target->x+5,target->y+5,BL_CHAR,
						src,target->id,&tbl,&c);
					if(tbl && skl->type < 5) {
						skill_addtimerskill(src,tick+650,tbl->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					} else if(skl->type < 5) {
						skill_addtimerskill(src,tick+650,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					}
				}
				break;
			default:
				battle_skill_attack(skl->type,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			}
		} else {
			if(src->m != skl->m)
				break;

			switch(skl->skill_id) {
			case BS_HAMMERFALL:
				range=(skl->skill_lv>5)?AREA_SIZE:2;
				skill_area_temp[1] = skl->src_id;
				skill_area_temp[2] = skl->x;
				skill_area_temp[3] = skl->y;
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|2,
					skill_castend_nodamage_id);
				break;
			case WZ_METEOR:
			case SU_CN_METEOR:				/* イヌハッカメテオ */
				if(skl->type >= 0) {
					int x = skl->type>>16, y = skl->type&0xffff;
					if(map_getcell(src->m,x,y,CELL_CHKPASS))
						skill_unitsetting(src,skl->skill_id,skl->skill_lv,x,y,0);
					if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS))
						clif_skill_poseffect(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,tick);
				} else {
					if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS))
						skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			case GS_DESPERADO:
			case WL_EARTHSTRAIN:	/* アースストレイン */
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS))
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				break;
			case NC_MAGMA_ERUPTION:	/* マグマイラプション */
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-3,skl->y-3,skl->x+3,skl->y+3,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				break;
			case LG_OVERBRAND_BRANDISH:		/* オーバーブランド(薙ぎ) */
				{
					int dir = path_calc_dir(src,skl->x,skl->y);
					map_foreachinshootpath(
						skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],3,5,(BL_CHAR|BL_SKILL),
						src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY,skill_castend_damage_id
					);
				}
				break;
			case GN_CRAZYWEED:		/* クレイジーウィード */
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS)) {
					map_foreachinarea(skill_delunit_by_ganbantein,
						src->m,skl->x-2,skl->y-2,skl->x+2,skl->y+2,BL_SKILL);
					skill_unitsetting(src,GN_CRAZYWEED_ATK,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			}
		}
	} while(0);

	aFree( skl );
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int skill_addtimerskill(struct block_list *src,unsigned int tick,int target,int x,int y,int skill_id,int skill_lv,int type,int flag)
{
	struct unit_data *ud;
	struct skill_timerskill *skl;

	nullpo_retr(1, src);
	nullpo_retr(1, ud = unit_bl2ud( src ) );

	skl            = (struct skill_timerskill *)aCalloc( 1, sizeof(struct skill_timerskill) );
	skl->timer     = add_timer(tick, skill_timerskill_timer, src->id, skl);
	skl->src_id    = src->id;
	skl->target_id = target;
	skl->skill_id  = skill_id;
	skl->skill_lv  = skill_lv;
	skl->m         = src->m;
	skl->x         = x;
	skl->y         = y;
	skl->type      = type;
	skl->flag      = flag;

	linkdb_insert( &ud->skilltimerskill, skl, skl);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int skill_cleartimerskill(struct block_list *src)
{
	struct unit_data *ud;
	struct linkdb_node *node1, *node2;

	nullpo_retr(0, src);
	nullpo_retr(0, ud = unit_bl2ud( src ) );

	node1 = ud->skilltimerskill;
	while( node1 ) {
		struct skill_timerskill *skl = (struct skill_timerskill *)node1->data;
		if( skl->timer != -1 ) {
			delete_timer(skl->timer, skill_timerskill_timer);
		}
		node2 = node1->next;
		aFree( skl );
		node1 = node2;
	}
	linkdb_final( &ud->skilltimerskill );

	return 0;
}

/* 範囲スキル使用処理小分けここまで
 * -------------------------------------------------------------------------
 */

/*==========================================
 * スキル使用（詠唱完了、ID指定）
 *------------------------------------------
 */
int skill_castend_id(int tid, unsigned int tick, int id, void *data)
{
	struct block_list *target, *src = map_id2bl(id);
	struct map_session_data *src_sd   = NULL;
	struct mob_data         *src_md   = NULL;
	struct homun_data       *src_hd   = NULL;
	struct merc_data        *src_mcd  = NULL;
	struct elem_data        *src_eld  = NULL;
	struct unit_data        *src_ud   = NULL;
	struct status_change    *tsc      = NULL;
	struct status_change    *sc       = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, src_ud = unit_bl2ud(src));

	if( src->prev == NULL ) // prevが無いのはありなの？
		return 0;

	src_sd  = BL_DOWNCAST( BL_PC,   src );
	src_md  = BL_DOWNCAST( BL_MOB,  src );
	src_hd  = BL_DOWNCAST( BL_HOM,  src );
	src_mcd = BL_DOWNCAST( BL_MERC, src );
	src_eld = BL_DOWNCAST( BL_ELEM, src );

	if(src_ud->skillid != SA_CASTCANCEL && !(src_ud->skillid == SO_SPELLFIST && (src_sd && (src_sd->skill_used.id == MG_FIREBOLT || src_sd->skill_used.id == MG_COLDBOLT || src_sd->skill_used.id == MG_LIGHTNINGBOLT)))) {
		if( src_ud->skilltimer != tid )	// タイマIDの確認
			return 0;
		if( src_sd && src_ud->skilltimer != -1 &&
			(pc_checkskill(src_sd,SA_FREECAST) > 0 ||
			src_ud->skillid == LG_EXEEDBREAK))
		{
			src_sd->speed = src_sd->prev_speed;
			clif_updatestatus(src_sd,SP_SPEED);
		}
		src_ud->skilltimer = -1;
	}

	target = map_id2bl(src_ud->skilltarget);
	if(target)
		tsc = status_get_sc(target);
	sc = status_get_sc(src);

	// スキル条件確認
	do {
		int inf2;

		if(!target || target->prev == NULL)
			break;
		if(src->m != target->m || unit_isdead(src))
			break;

		// ウォールオブフォグ 不発判定
		if(tsc && (tsc->data[SC_FOGWALL].timer != -1 || tsc->data[SC_FOGWALLPENALTY].timer != -1) && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 75)
			break;

		if(src_ud->skillid == PR_LEXAETERNA) {
			if(tsc && (tsc->data[SC_FREEZE].timer != -1 || (tsc->data[SC_STONE].timer != -1 && tsc->data[SC_STONE].val2 == 0))) {
				break;
			}
		} else if(src_ud->skillid == RG_BACKSTAP) {
			int dir   = path_calc_dir(src,target->x,target->y);
			int t_dir = status_get_dir(target);
			int dist  = unit_distance(src,target);
			if(target->type != BL_SKILL && (dist == 0 || path_check_dir(dir,t_dir)))
				break;
		}

		// 沈黙や状態異常など
		if(src_md) {
			if(src_md->sc.data[SC_ROKISWEIL].timer != -1)
				break;
			if(!(mob_db[src_md->class_].mode & MD_BOSS) && src_md->sc.data[SC_HERMODE].timer != -1)
				break;
			if((src_md->sc.opt1 > OPT1_NORMAL && src_md->sc.opt1 != OPT1_BURNNING) || src_md->sc.data[SC_SILENCE].timer != -1 || src_md->sc.data[SC_STEELBODY].timer != -1)
				break;
			if(src_md->sc.data[SC_AUTOCOUNTER].timer != -1 && src_md->ud.skillid != KN_AUTOCOUNTER)
				break;
			if(src_md->sc.data[SC_BLADESTOP].timer != -1)
				break;
			if(src_md->sc.data[SC_BERSERK].timer != -1)
				break;
			if(src_md->sc.data[SC_DEATHBOUND].timer != -1 && src_md->ud.skillid != RK_DEATHBOUND)
				break;
			if(src_md->sc.data[SC_STASIS].timer != -1 && skill_get_skill_type(src_md->ud.skillid) == BF_MAGIC)
				break;
			if(src_md->sc.data[SC__SHADOWFORM].timer != -1)
				break;
			if(src_md->sc.data[SC__MANHOLE].timer != -1)
				break;
			if(src_md->sc.data[SC__INVISIBILITY].timer != -1 && src_md->ud.skillid != SC_INVISIBILITY)
				break;
			if(src_md->sc.data[SC__IGNORANCE].timer != -1)
				break;
			if(src_md->sc.data[SC_CURSEDCIRCLE].timer != -1)
				break;

			if(src_md->ud.skillid != NPC_EMOTION)
				src_md->last_thinktime = tick + status_get_adelay(src);
			if(src_md->skillidx >= 0)
				src_md->skilldelay[src_md->skillidx] = tick;
		}

		inf2 = skill_get_inf2(src_ud->skillid);
		if(inf2 & INF2_ATTACK || skill_get_inf(src_ud->skillid) & INF_ATTACK) {
			int fail_flag = 1;
			switch(src_ud->skillid) {	// 敵以外をターゲットにしても良いスキル
				case AS_GRIMTOOTH:
				case KN_BRANDISHSPEAR:
				case SN_SHARPSHOOTING:
				case GS_SPREADATTACK:
				case NJ_HUUMA:
				case NJ_BAKUENRYU:
				case NJ_KAMAITACHI:
				case MA_SHARPSHOOTING:
				case ML_BRANDISH:
				case PR_LEXDIVINA:
				case MER_LEXDIVINA:
				case MO_EXTREMITYFIST:
				case SA_DISPELL:
				case TK_JUMPKICK:
				case SR_TIGERCANNON:
				case SR_GATEOFHELL:
					fail_flag = 0;
					break;
				case SA_SPELLBREAKER:
					if(map[src->m].flag.town)	// 街中のみPCに有効
						fail_flag = 0;
					break;
			}
			if(fail_flag) {
				if(battle_check_target(src,target,BCT_ENEMY) <= 0)	// 彼我敵対関係チェック
					break;
			}
		}
		if(inf2 & (INF2_PARTY_ONLY | INF2_GUILD_ONLY) && src->id != target->id) {
			int fail_flag = 1;
			if(inf2 & INF2_PARTY_ONLY && battle_check_target(src,target,BCT_PARTY) > 0)
				fail_flag = 0;
			else if(src_sd && inf2 & INF2_GUILD_ONLY && src_sd->status.guild_id > 0 && src_sd->status.guild_id == status_get_guild_id(target))
				fail_flag = 0;
			if(fail_flag) {
				break;
			}
		}

		if(skill_get_nk(src_ud->skillid)&4) {
			// 射線チェック
			if(!path_search_long(NULL,src->m,src->x,src->y,target->x,target->y)) {
				if(src_sd && battle_config.skill_out_range_consume)
					skill_check_condition(&src_sd->bl,1);	// アイテム消費
				break;
			}
		}

		// PC,HOM,MERC,ELEMは使用条件チェック
		if(src_sd || src_hd || src_mcd || src_eld) {
			if(!skill_check_condition(src,1))
				break;
		}
		if(src_sd) {
			src_sd->skill_item.id      = -1;
			src_sd->skill_item.lv      = -1;
			src_sd->skill_item.flag    = 0;
		}

		if(battle_config.pc_skill_log)
			printf("PC %d skill castend skill=%d\n",src->id,src_ud->skillid);
		unit_stop_walking(src,0);

		if(src_sd) {
			int cooldown = skill_cooldownfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);
			int delay    = skill_delayfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);

			if(cooldown > 0) {
				int nameid = skill_get_skilldb_id(src_ud->skillid);
				if(nameid > 0) {
					src_sd->skillcooldown[nameid] = tick + cooldown;
					clif_skill_cooldown(src_sd, src_ud->skillid, cooldown);
				}
			}
#if PACKETVER > 20081126
			if(delay > 0)
				clif_status_change(&src_sd->bl, SI_ACTIONDELAY, 1, delay, 0, 0, 0);
#endif
		}

		// エモ、チャット
		if(src_md && src_md->skillidx != -1)
		{
			short emotion = mob_db[src_md->class_].skill[src_md->skillidx].emotion;
			short msg_id = mob_db[src_md->class_].skill[src_md->skillidx].msg_id;
			if(emotion >= 0)
				clif_emotion(&src_md->bl,emotion);
			if(msg_id > 0)
				mob_talk(src_md,msg_id);
		}

		switch( skill_get_nk(src_ud->skillid)&3 )
		{
		case 0:	/* 攻撃系 */
		case 2:	/* 吹き飛ばし系 */
			skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
			break;
		case 1:	/* 支援系 */
			if((src_ud->skillid == AL_HEAL ||
				     src_ud->skillid == PR_SANCTUARY ||
				     src_ud->skillid == AB_HIGHNESSHEAL) &&
				     tsc && tsc->data[SC_AKAITSUKI].timer != -1)
			{
				skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
			}
			else if( (src_ud->skillid == AL_HEAL ||
			     src_ud->skillid == PR_SANCTUARY ||
			     src_ud->skillid == ALL_RESURRECTION ||
			     src_ud->skillid == PR_ASPERSIO ||
			     src_ud->skillid == AB_HIGHNESSHEAL) &&
			    battle_check_undead(status_get_race(target),status_get_elem_type(target)) &&
			    !(src_md && target->type == BL_MOB) )	// MOB→MOBならアンデッドでも回復
			{
				if( target->type != BL_PC ||
				    (src_md && src_md->skillidx >= 0 && !mob_db[src_md->class_].skill[src_md->skillidx].val[0]) ) {
					skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
				} else if( map[src->m].flag.pvp || map[src->m].flag.gvg ) {
					if((src_ud->skillid == AL_HEAL || src_ud->skillid == AB_HIGHNESSHEAL) && battle_check_target(src,target,BCT_PARTY))
						break;
					skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
				} else {
					break;
				}
			}
			else
			{
				skill_castend_nodamage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
			}
			break;
		}

		// スキル使用で発動するオートスペル,アクティブアイテム
		if(src_sd) {
			bonus_autospellskill_start(src,target,src_ud->skillid,tick,0);
			bonus_activeitemskill_start(src_sd,src_ud->skillid,tick);
		}

		if(src_md)
			src_md->skillidx = -1;

		if(sc && sc->data[SC_CAMOUFLAGE].timer != -1 && src_ud->skillid != RA_CAMOUFLAGE) {
			status_change_end(src,SC_CAMOUFLAGE,-1);
		}
		return 0;
	} while(0);

	// スキル使用失敗
	src_ud->canact_tick  = tick;
	src_ud->canmove_tick = tick;
	if(src_sd) {
		src_sd->skill_item.id      = -1;
		src_sd->skill_item.lv      = -1;
		src_sd->skill_item.flag    = 0;
	} else if(src_md) {
		src_md->skillidx = -1;
	}

	return 0;
}

/*==========================================
 * スキル使用（詠唱完了、ID指定攻撃系）
 *------------------------------------------
 */
int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	int is_enemy = 1;

	nullpo_retr(1, src);
	nullpo_retr(1, bl);

	if(bl->prev == NULL)
		return 1;
	if(unit_isdead(bl))
		return 1;

	sd  = BL_DOWNCAST( BL_PC,   src );
	md  = BL_DOWNCAST( BL_MOB,  src );
	hd  = BL_DOWNCAST( BL_HOM,  src );
	eld = BL_DOWNCAST( BL_ELEM, src );

	switch(skillid) {
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
			if(src != bl)
				bl = src;
			break;
		case AS_GRIMTOOTH:
		case SN_SHARPSHOOTING:
		case GS_SPREADATTACK:
		case NJ_HUUMA:
		case NJ_BAKUENRYU:
		case NJ_KAMAITACHI:
		case MA_SHARPSHOOTING:
		case MO_EXTREMITYFIST:
		case TK_JUMPKICK:
		case SR_TIGERCANNON:
		case SR_GATEOFHELL:
			// skill_castend_idで許可したスキルはここで敵チェック
			if(skill_get_inf2(skillid) & INF2_ATTACK || skill_get_inf(skillid) & INF_ATTACK) {
				if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
					is_enemy = 0;
			}
			break;
	}

	map_freeblock_lock();

	switch(skillid)
	{
	/* 武器攻撃系スキル */
	case SM_BASH:			/* バッシュ */
	case MC_MAMMONITE:		/* メマーナイト */
	case KN_PIERCE:			/* ピアース */
	case KN_SPEARBOOMERANG:	/* スピアブーメラン */
	case TF_POISON:			/* インベナム */
	case TF_SPRINKLESAND:	/* 砂まき */
	case AC_CHARGEARROW:	/* チャージアロー */
	case ASC_METEORASSAULT:	/* メテオアサルト */
	case RG_INTIMIDATE:		/* インティミデイト */
	case AM_ACIDTERROR:		/* アシッドテラー */
	case BA_MUSICALSTRIKE:	/* ミュージカルストライク */
	case DC_THROWARROW:		/* 矢撃ち */
	case BA_DISSONANCE:		/* 不協和音 */
	case CR_HOLYCROSS:		/* ホーリークロス */
	case CR_SHIELDCHARGE:
	case CR_SHIELDBOOMERANG:
	case NPC_PIERCINGATT:
	case NPC_MENTALBREAKER:
	case NPC_RANGEATTACK:
	case NPC_CRITICALSLASH:
	case NPC_COMBOATTACK:
	case NPC_POISON:
	case NPC_BLINDATTACK:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	case NPC_PETRIFYATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
	case NPC_RANDOMATTACK:
	case NPC_WATERATTACK:
	case NPC_GROUNDATTACK:
	case NPC_FIREATTACK:
	case NPC_WINDATTACK:
	case NPC_POISONATTACK:
	case NPC_HOLYATTACK:
	case NPC_DARKNESSATTACK:
	case NPC_TELEKINESISATTACK:
	case NPC_UNDEADATTACK:
	case NPC_WEAPONBRAKER:
	case NPC_ARMORBRAKE:
	case NPC_HELMBRAKE:
	case NPC_SHIELDBRAKE:
	case NPC_DARKCROSS:
	case LK_SPIRALPIERCE:		/* スパイラルピアース */
	case LK_HEADCRUSH:			/* ヘッドクラッシュ */
	case LK_JOINTBEAT:			/* ジョイントビート */
	case ASC_BREAKER:			/* ソウルブレイカー */
	case HW_MAGICCRASHER:		/* マジッククラッシャー */
	case PA_SHIELDCHAIN:		/* シールドチェイン */
	case WS_CARTTERMINATION:	/* カートターミネーション */
	case CR_ACIDDEMONSTRATION:	/* アシッドデモンストレーション */
	case ITM_TOMAHAWK:			/* トマホーク投げ */
	case AS_VENOMKNIFE:			/* ベナムナイフ */
	case HT_PHANTASMIC:			/* ファンタズミックアロー */
	case CH_TIGERFIST:		/* 伏虎拳 */
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
	case TK_DOWNKICK:	/* ネリョチャギ */
	case TK_COUNTER:	/* アプチャオルリギ */
	case GS_FLING:			/* フライング */
	case GS_TRIPLEACTION:	/* トリプルアクション */
	case GS_MAGICALBULLET:	/* マジカルバレット */
	case GS_TRACKING:		/* トラッキング */
	case GS_RAPIDSHOWER:	/* ラピッドシャワー */
	case GS_DUST:			/* ダスト */
	case GS_PIERCINGSHOT:	/* ピアーシングショット */
	case GS_FULLBUSTER:		/* フルバスター */
	case NJ_SYURIKEN:		/* 手裏剣投げ */
	case NJ_KUNAI:			/* 苦無投げ */
	case NJ_ZENYNAGE:		/* 銭投げ */
	case NJ_KASUMIKIRI:		/* 霞斬り */
	case HFLI_MOON:
	case HFLI_SBR44:
	case NPC_BLEEDING:		/* 出血攻撃 */
	case NPC_CRITICALWOUND:		/* 致命傷攻撃 */
	case NPC_EXPULSION:		/* エクスパルシオン */
	case MS_BASH:
	case MA_CHARGEARROW:
	case ML_PIERCE:
	case ML_SPIRALPIERCE:
	case MER_CRASH:			/* クラッシュ */
	case RK_SONICWAVE:			/* ソニックウェーブ */
	case RK_DRAGONBREATH:	/* ファイアードラゴンブレス */
	case RK_DRAGONBREATH_WATER:	/* ウォータードラゴンブレス */
	case AB_DUPLELIGHT_MELEE:	/* デュプレライト(物理) */
	case RA_WUGBITE:		/* ウォーグバイト */
	case NC_BOOSTKNUCKLE:	/* ブーストナックル */
	case NC_PILEBUNKER:		/* パイルバンカー */
	case NC_VULCANARM:		/* バルカンアーム */
	case NC_COLDSLOWER:		/* コールドスローワー */
	case NC_ARMSCANNON:		/* アームズキャノン */
	case NC_AXEBOOMERANG:	/* アックスブーメラン */
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
	case LG_BANISHINGPOINT:	/* バニシングポイント */
	case LG_SHIELDPRESS:	/* シールドプレス */
	case LG_OVERBRAND:		/* オーバーブランド */
	case LG_HESPERUSLIT:	/* ヘスペルスリット */
	case SR_DRAGONCOMBO:	/* 双龍脚 */
	case SR_FALLENEMPIRE:	/* 大纏崩捶 */
	case SR_GENTLETOUCH_QUIET:	/* 点穴 -默- */
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
	case WM_GREAT_ECHO:		/* グレートエコー */
	case GN_DEMONIC_FIRE:	/* デモニックファイアー */
	case GN_FIRE_EXPANSION_ACID:	/* ファイアーエクスパンション(塩酸) */
	case GN_SLINGITEM_RANGEMELEEATK:	/* スリングアイテム(遠距離攻撃) */
	case KO_SETSUDAN:		/* 霊魂絶断 */
	case KO_BAKURETSU:		/* 爆裂苦無 */
	case EL_WIND_SLASH:		/* ウィンドスラッシュ */
	case EL_STONE_HAMMER:	/* ストーンハンマー */
	case NPC_DISSONANCE:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NPC_GUIDEDATTACK:	/* ガイデッドアタック */
		status_change_start(src,SC_INCHIT,status_get_dex(src)/2,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case KN_BRANDISHSPEAR:		/* ブランディッシュスピア */
	case ML_BRANDISH:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_area_temp[1]++;
		break;
	case AC_DOUBLE:			/* ダブルストレイフィング */
	case MA_DOUBLE:
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case GS_DISARM:			/* ディスアーム */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AS_SONICBLOW:		/* ソニックブロー */
	case CG_ARROWVULCAN:		/* アローバルカン */
	case GC_CROSSIMPACT:	/* クロスインパクト */
		{
			struct unit_data *ud = unit_bl2ud(src);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if(ud) {
				// スキルモーションディレイは最大で3秒くらい？
				int delay = status_get_adelay(src);
				ud->canmove_tick = tick + ( (delay>2000)? 3000: 6000*1000/(4000-delay) );
			}
		}
		break;
	case HT_POWER:			/* ピーストストレイフィング*/
		status_change_end(src,SC_DOUBLE,-1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case MO_INVESTIGATE:	/* 発勁 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case RG_RAID:			/* サプライズアタック */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
#ifndef PRE_RENEWAL
		status_change_start(bl,SC_RAID,7,0,0,0,skill_get_time(skillid,skilllv),0 );
#endif
		break;
	case RG_BACKSTAP:		/* バックスタブ */
		{
			int dir   = path_calc_dir(src,bl->x,bl->y);
			int t_dir = status_get_dir(bl);
			int dist  = unit_distance(src,bl);
			if((dist > 0 && !path_check_dir(dir,t_dir)) || bl->type == BL_SKILL) {
				sc = status_get_sc(src);
				if(sc && sc->data[SC_HIDING].timer != -1)
					status_change_end(src, SC_HIDING, -1);	// ハイディング解除
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)>0) { // 攻撃を受けた目標は振り向く
					unit_setdir(bl, path_calc_dir(bl,src->x,src->y));
				}
			} else if(sd) {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(md && !mob_is_pcview(md->class_)) {
			// 見た目がPCでない場合は何故か姿が消えてしまうので抑制する
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		if(battle_config.finger_offensive_type && sd) {
			int i;
			for(i=1; i<sd->spiritball.old; i++)
				skill_addtimerskill(src,tick+i*200,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
			sd->ud.canmove_tick = tick + (sd->spiritball.old-1)*200;
		}
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case MO_CHAINCOMBO:		/* 連打掌 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case TK_STORMKICK:	/* フェオリチャギ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			skill_area_temp[1]=src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-2,src->y-2,src->x+2,src->y+2,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;

	case TK_TURNKICK:	/* トルリョチャギ */
		if(flag&1){
			/* 個別処理 */
			if(bl->id != skill_area_temp[1]) {
				struct block_list pos;
				memset(&pos,0,sizeof(pos));
				pos.m = bl->m;
				pos.x = skill_area_temp[2];
				pos.y = skill_area_temp[3];
				skill_blown(&pos,bl,skill_area_temp[4] | SAB_NODAMAGE);
				skill_additional_effect(src,bl,skillid,skilllv,BF_WEAPON,tick);
			}
		} else {
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* まずターゲットに攻撃を加える */
			if(!battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			/* その後ターゲット以外の範囲内のMOB全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,skill_area_temp[2]-1,skill_area_temp[3]-1,skill_area_temp[2]+1,skill_area_temp[3]+1,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case KN_CHARGEATK:	/* チャージアタック */
	case TK_JUMPKICK:	/* ティオアプチャギ */
	case NJ_ISSEN:		/* 一閃 */
		{
			int dist = unit_distance(src,bl);
			if(sd && (skillid != KN_CHARGEATK || battle_config.gvg_chargeattack_move || !map[sd->bl.m].flag.gvg)) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,0,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				if(skillid == TK_JUMPKICK)
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
				else
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			if(skillid == TK_JUMPKICK) {
				sc = status_get_sc(src);
				if(sc && sc->data[SC_RUN].timer != -1)
					status_change_end(src,SC_RUN,-1);
			}
		}
		break;
	case MO_COMBOFINISH:	/* 猛龍拳 */
		sc = status_get_sc(src);
		/* モンクの魂状態の場合は範囲攻撃 */
		if(sc && sc->data[SC_MONK].timer != -1) {
			if(flag&1) {
				if(bl->id != skill_area_temp[1])
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = bl->x;
				skill_area_temp[3] = bl->y;
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				map_foreachinarea(skill_area_sub,
					src->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case CH_PALMSTRIKE:		/* 猛虎硬爬山 */
		clif_damage(src,bl,tick,status_get_amotion(src),0,-1,1,4,0,0);	// 攻撃モーションのみ入れる
		skill_addtimerskill(src,tick+1000,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		break;
	case MO_EXTREMITYFIST:	/* 阿修羅覇鳳拳 */
		{
			int dx = 0;
			int dy = 0;
			short dir = 0;

			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
			if(!is_enemy && sd && sd->status.sp > 0) {
				sd->status.sp = 0;
				clif_updatestatus(sd, SP_SP);
			}
			if(sd) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + 100 + sd->speed * ((dx > dy)? dx: dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
			}
			status_change_end(src,SC_COMBO,-1);
			status_change_end(src, SC_EXPLOSIONSPIRITS, -1);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_BLADESTOP].timer != -1) {
				status_change_end(src,SC_BLADESTOP,-1);
			}
			dir = path_calc_dir(src,bl->x,bl->y);
			if(dir > 0 && dir < 4) dx = -3;
			else if(dir > 4) dx = 3;
			if(dir > 2 && dir < 6) dy = -3;
			else if(dir == 7 || dir < 2) dy = 3;
			if(dx == 0 && dy == 0) dx = 1;
			if(!unit_movepos(src,src->x + dx,src->y + dy,1)) {
				if(dx > 0) dx = -1;
				else if(dx < 0) dx = 1;
				if(dy > 0) dy = -1;
				else if(dy < 0) dy = 1;

				unit_movepos(src,src->x + dx,src->y + dy,1);
			}
		}
		break;
	case GS_BULLSEYE:		/* ブルズアイ */
		{
			int race = status_get_race(bl);
			if(race == RCT_BRUTE || race == RCT_HUMAN) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case NJ_KIRIKAGE:		/* 影斬り */
		{
			int dist = unit_distance(src,bl);
			if(sd && pc_checkskill(sd,NJ_SHADOWJUMP) * 2 + 5 >= dist) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,0,0,0);
						break;
					}
				}
				if(!map[src->m].flag.gvg) {
					sd->ud.to_x = sd->bl.x + dx;
					sd->ud.to_y = sd->bl.y + dy;
					clif_walkok(sd);
					clif_move(&sd->bl);
					if(dx < 0) dx = -dx;
					if(dy < 0) dy = -dy;
					sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
					if(sd->ud.canact_tick < sd->ud.canmove_tick)
						sd->ud.canact_tick = sd->ud.canmove_tick;
					unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
				}
				else {
					if(status_get_range(src) < dist) {
						status_change_end(src, SC_HIDING, -1);	// ハイディング解除
						break;
					}
				}
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			status_change_end(src, SC_HIDING, -1);	// ハイディング解除
		}
		break;
	/* 武器系範囲攻撃スキル */
	case AC_SHOWER:			/* アローシャワー */
	case MA_SHOWER:
		{
			// 指定セルを攻撃中心にするためにsrcの代わりを用意する
			struct block_list pos;
			memset(&pos,0,sizeof(struct block_list));
			pos.m = bl->m;
			pos.x = skill_area_temp[2];
			pos.y = skill_area_temp[3];
			if( battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500) ) {
				int count = skill_get_blewcount(skillid,skilllv)|SAB_NOPATHSTOP;
				if(bl->x == pos.x && bl->y == pos.y)
					count |= 6<<20;		// 指定座標と同一なら西へノックバック
				skill_blown(&pos,bl,count);
			}
		}
		break;
	case SM_MAGNUM:			/* マグナムブレイク */
	case MS_MAGNUM:
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				int x = skill_area_temp[2], y = skill_area_temp[3];
				int type;
				if(path_distance(bl->x,bl->y,x,y) > 1)
					type = 1;	// 外周
				else
					type = 0;	// 内周
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500|type);
			}
		} else {
			int ar = (md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)? 4: 2;

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,ELE_FIRE,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_SPLASHATTACK:	/* スプラッシュアタック */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = 3;
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x500|skill_area_temp[0]);
		} else {
			int ar = 2;
			skill_area_temp[0] = 0;
			//分散範囲は3x3 攻撃範囲は5x5
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_GRIMTOOTH:		/* グリムトゥース */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = 1;
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case MC_CARTREVOLUTION:	/* カートレボリューション */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
			{
				if(bl->x == skill_area_temp[2] && bl->y == skill_area_temp[3]) {
					skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// ターゲットと同一座標なら西へノックバック
				} else {
					struct block_list pos;
					memset(&pos,0,sizeof(pos));
					pos.m = bl->m;
					pos.x = skill_area_temp[2];
					pos.y = skill_area_temp[3];
					skill_blown(&pos,bl,skill_area_temp[4]);		// ターゲットとの位置関係で飛ばす方向を決める
				}
			}
		} else {
			int x = bl->x, y = bl->y;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* まずターゲットに攻撃を加える */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// 西に強制ノックバック

			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,x-1,y-1,x+1,y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KN_BOWLINGBASH:	/* ボウリングバッシュ */
	case MS_BOWLINGBASH:
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id!=skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int i,c,dir;	/* 他人から聞いた動きなので間違ってる可能性大＆効率が悪いっす＞＜ */
			/* まずターゲットに攻撃を加える */
			if(!battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			c   = skill_get_blewcount(skillid,skilllv);
			dir = (status_get_dir(src)+4) & 0x07;
			if(dir == 0)
				dir = 8;
			if(map[bl->m].flag.gvg) c = 0;
			for(i=0; i<c; i++) {
				skill_blown(src,bl,(dir<<20)|SAB_NODAMAGE|1);
				skill_area_temp[0] = 0;
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY ,
					skill_area_sub_count);
				if(skill_area_temp[0] > 1)
					break;
			}
			unit_stop_walking(bl,2);	// 最後にダメージディレイを入れる
			skill_area_temp[1] = bl->id;
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case MO_BALKYOUNG:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		map_foreachinarea(skill_balkyoung,bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),src,bl);
		break;
	case KN_SPEARSTAB:		/* スピアスタブ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
				skill_blown(src,bl,skill_area_temp[2]);
		} else {
			int x = bl->x, y = bl->y;
			int i, dir = path_calc_dir(bl,src->x,src->y);
			if(dir == 0)
				dir = 8;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv)|(dir<<20);
			if(map[bl->m].flag.gvg)
				skill_area_temp[2] = 0;
			/* まずターゲットに攻撃を加える */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				skill_blown(src,bl,skill_area_temp[2]);
			for(i=0; i<4; i++) {
				map_foreachinarea(skill_area_sub,bl->m,x,y,x,y,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				x += dirx[dir];
				y += diry[dir];
			}
		}
		break;
	case SN_SHARPSHOOTING:			/* シャープシューティング */
	case MA_SHARPSHOOTING:
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],12,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case GS_SPREADATTACK:	/* スプレッドアタック */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = (skilllv-1)/3+1;
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			map_foreachinarea(skill_area_sub,
				src->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NJ_HUUMA:		/* 風魔手裏剣投げ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		} else {
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_EARTHQUAKE:		/* アースクエイク */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				skill_addtimerskill(src,tick+200,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+400,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+600,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
			}
		} else {
			int ar = 5+(skilllv-1)%5*2;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_PC|BL_MOB),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_PC|BL_MOB),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_FIREBREATH:		/* ファイアブレス */
	case NPC_ICEBREATH:		/* アイスブレス */
	case NPC_THUNDERBREATH:		/* サンダーブレス */
	case NPC_ACIDBREATH:		/* アシッドブレス */
	case NPC_DARKNESSBREATH:	/* ダークネスブレス */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,4,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case NPC_PULSESTRIKE:		/* パルスストライク */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-7,src->y-7,src->x+7,src->y+7,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_HELLJUDGEMENT:		/* ヘルジャッジメント */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		} else {
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-14,src->y-14,src->x+14,src->y+14,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_VAMPIRE_GIFT:		/* ヴァンパイアリックタッチ */
		if(flag&1) {
			/* 個別にダメージを与える */
			int heal = battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			if(heal) {
				clif_skill_nodamage(src,src,AL_HEAL,heal,1);
				battle_heal(NULL,src,heal,0,0);
			}
		} else {
			int ar = (skilllv > 5)? 13: 3 + (skilllv * 2);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_PULSESTRIKE2:		/* パルスストライクII */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			clif_skill_poseffect(src,skillid,-1,src->x,src->y,tick);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-5,src->y-5,src->x+5,src->y+5,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_DANCINGBLADE:		/* ダンシングブレイド */
		clif_skill_poseffect(src,skillid,-1,bl->x,bl->y,tick);
		skill_addtimerskill(src,tick+150,bl->id,0,0,NPC_DANCINGBLADE_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case NPC_DARKPIERCING:		/* ダークピアーシング */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,2,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		}
		break;

	/* 魔法系スキル */
	case MG_SOULSTRIKE:			/* ソウルストライク */
	case NPC_DARKSTRIKE:		/* ダークストライク */
	case MG_COLDBOLT:			/* コールドボルト */
	case MG_FIREBOLT:			/* ファイアーボルト */
	case MG_LIGHTNINGBOLT:		/* ライトニングボルト*/
	case WZ_EARTHSPIKE:			/* アーススパイク */
	case AL_HEAL:				/* ヒール */
	case AL_HOLYLIGHT:			/* ホーリーライト */
	case WZ_JUPITEL:			/* ユピテルサンダー */
	case NPC_DARKTHUNDER:		/* ダークサンダー */
	case NPC_MAGICALATTACK:		/* 魔法打撃攻撃 */
	case PR_ASPERSIO:			/* アスペルシオ */
	case NJ_KOUENKA:			/* 紅炎華 */
	case NJ_HYOUSENSOU:			/* 氷閃槍 */
	case NJ_HUUJIN:				/* 風刃 */
	case AB_HIGHNESSHEAL:		/* ハイネスヒール */
	case AB_ADORAMUS:			/* アドラムス */
	case AB_DUPLELIGHT_MAGIC:	/* デュプレライト(魔法) */
	case LG_RAYOFGENESIS:		/* レイオブジェネシス */
	case WM_METALICSOUND:		/* メタリックサウンド */
	case EL_FIRE_ARROW:			/* ファイアーアロー */
	case EL_ICE_NEEDLE:			/* アイスニードル */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case ALL_RESURRECTION:		/* リザレクション */
	case PR_TURNUNDEAD:			/* ターンアンデッド */
		if(battle_check_undead(status_get_race(bl),status_get_elem_type(bl))) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			map_freeblock_unlock();
			return 1;
		}
		break;
	case HVAN_CAPRICE:		/* カプリス */
		{
			static const int caprice[4] = { MG_COLDBOLT,MG_FIREBOLT,MG_LIGHTNINGBOLT,WZ_EARTHSPIKE};
			battle_skill_attack(BF_MAGIC,src,src,bl,caprice[atn_rand()%4],skilllv,tick,flag);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;
	case CG_TAROTCARD:		/* 運命のタロットカード */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_TRICKDEAD].timer != -1) {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		skill_tarot_card_of_fate(src,bl,skillid,skilllv,tick,0);
		break;
	case MG_FROSTDIVER:		/* フロストダイバー */
		{
			int damage;

			sc = status_get_sc(bl);
			if(sc && sc->data[SC_FREEZE].timer != -1) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			damage = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(status_get_hp(bl) > 0 && damage > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv*300+3500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case WZ_WATERBALL:			/* ウォーターボール */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(skilllv > 1) {
			int cnt, range;
			range = (skilllv > 5)? 2: skilllv / 2;
			if(sd && !map[sd->bl.m].flag.rain)
				cnt = skill_count_water(src,range) - 1;
			else
				cnt = skill_get_num(skillid,skilllv) - 1;
			if(cnt > 0)
				skill_addtimerskill(src,tick+150,bl->id,0,0,skillid,skilllv,cnt,flag);
		}
		break;

	case PR_BENEDICTIO:			/* 聖体降福 */
		{
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(bl->type == BL_MOB || !map[bl->m].flag.normal)
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;

	case SL_SMA:				/* エスマ */
	case SL_STUN:				/* エストン */
	case SL_STIN:				/* エスティン */
		if(sd && bl->type != BL_MOB && !battle_config.allow_es_magic_all)
			clif_skill_fail(sd,skillid,0,0,0);
		else
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	/* 魔法系範囲攻撃スキル */
	case MG_NAPALMBEAT:			/* ナパームビート */
	case MG_FIREBALL:			/* ファイアーボール */
	case WZ_SIGHTRASHER:		/* サイトラッシャー */
	case HW_NAPALMVULCAN:		/* ナパームバルカン */
	case AB_JUDEX:				/* ジュデックス */
	case WL_SOULEXPANSION:		/* ソウルエクスパンション */
	case SO_POISON_BUSTER:		/* ポイズンバスター */
	case SO_VARETYR_SPEAR:		/* ヴェラチュールスピア */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				int count;
				if(skillid == MG_FIREBALL) {
					/* ファイアーボールなら中心からの距離を計算 */
					count = path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]);
				} else {
					count = skill_area_temp[0];
				}
				if(skillid != HW_NAPALMVULCAN && skillid != AB_JUDEX && skillid != WL_SOULEXPANSION && skillid != WL_CRIMSONROCK)
					count |= 0x0500;
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,count);
			}
		} else {
			int ar = 0, srcflg = 0;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			switch (skillid) {
				case MG_NAPALMBEAT:
				case HW_NAPALMVULCAN:
					ar = 1;
					/* ナパームビート・ナパームバルカンは分散ダメージなので敵の数を数える */
					map_foreachinarea(skill_area_sub,
							bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick,flag|BCT_ENEMY,
							skill_area_sub_count);
					break;
				case MG_FIREBALL:
					ar = 2;
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case WZ_SIGHTRASHER:
					ar = 7;
					srcflg = 1;
					bl = src;
					status_change_end(src,SC_SIGHT,-1);
					break;
				case AB_JUDEX:				/* ジュデックス */
					ar = 1;
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case WL_SOULEXPANSION:		/* ソウルエクスパンション */
					ar = (skilllv + 1) / 2;
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case SO_POISON_BUSTER:	/* ポイズンバスター */
					ar = (skilllv / 5) + 1;
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case SO_VARETYR_SPEAR:	/* ヴェラチュールスピア */
					ar = (skilllv + 1) / 2;
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
			}
			if(srcflg) {
				/* スキルエフェクト表示 */
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			} else {
				/* ターゲットに攻撃を加える(スキルエフェクト表示) */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
			}
			/* ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(skillid == WZ_SIGHTRASHER)
				map_foreachinarea(skill_area_trap_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
		}
		break;
	case WZ_FROSTNOVA:			/* フロストノヴァ */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_HYOUSYOURAKU:		/* 氷柱落し */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_RAIGEKISAI:			/* 雷撃砕 */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_KAMAITACHI:			/* 朔風 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],skill_get_fixed_range(src,skillid,skilllv),1,
				(BL_CHAR|BL_SKILL),src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;

	/* その他 */
	case TF_THROWSTONE:			/* 石投げ */
	case PA_PRESSURE:			/* プレッシャー */
	case SN_FALCONASSAULT:			/* ファルコンアサルト */
	case GN_HELLS_PLANT_ATK:	/* ヘルズプラント */
	case NPC_DARKBREATH:
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case HT_BLITZBEAT:			/* ブリッツビート */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
		} else {
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if(flag&0xf00000) {
				map_foreachinarea(skill_area_sub,bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY,skill_area_sub_count);
			}
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case CR_GRANDCROSS:			/* グランドクロス */
	case NPC_GRANDDARKNESS:			/* グランドダークネス */
		{
			struct unit_data *ud = unit_bl2ud(src);
			if(status_check_no_magic_damage(src))
				break;
			status_change_start(src,SC_STRIPSHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			/* スキルユニット配置 */
			skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
			if(ud)
				ud->canmove_tick = tick + 900;
		}
		break;
	case PF_SOULBURN:		/* ソウルバーン */
		if(bl->type == BL_PC) {
			struct block_list *dstbl;
			int sp, rate;
			if(status_check_no_magic_damage(bl))
				break;
			if(sd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk)
				break;
			rate = (skilllv >= 5)? 70: 10 * skilllv + 30;
			if(atn_rand() % 100 >= rate) {
				dstbl = src;	// 自分に対してダメージ
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
			} else {
				dstbl = bl;
			}
			clif_skill_nodamage(src,dstbl,skillid,skilllv,1);
			sp = status_get_sp(dstbl);
			// SPを0にする
			if(dstbl->type == BL_PC)
				unit_heal(dstbl,0,-sp);
			if(skilllv >= 5) {
				// SP*2のダメージを与える(MDEFで計算)
				int damage = sp * 2 * (100 - status_get_mdef(dstbl)) / 100 - status_get_mdef2(dstbl);
				if(damage < 1)
					damage = 1;
				battle_damage(src,dstbl,damage,skillid,skilllv,0);
			}
			if(sd)
				sd->skillstatictimer[PF_SOULBURN] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case NPC_SELFDESTRUCTION2:	/* 自爆2 */
		if(flag&1) {
			if(bl->type == BL_PC && !map[src->m].flag.pvp && !map[src->m].flag.gvg)
				break;
		}
		// fall through
	case NPC_SELFDESTRUCTION:	/* 自爆 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(md) {
				md->hp = skill_area_temp[2];
				if(bl->id != skill_area_temp[1]) {
					battle_skill_attack(BF_MISC,src,src,bl,NPC_SELFDESTRUCTION,skilllv,tick,flag);
				}
				md->hp = 1;
			}
		} else {
			sc = status_get_sc(src);
			if(sc && sc->data[SC_SELFDESTRUCTION].timer != -1)
				status_change_end(src,SC_SELFDESTRUCTION,-1);

			if(md && md->hp > 0) {
				if(skillid == NPC_SELFDESTRUCTION2 && md->hp >= status_get_max_hp(&md->bl)) {
					// 自爆2でHP全回復状態なら発動しない
					break;
				}
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = md->hp;
				clif_skill_nodamage(src,src,NPC_SELFDESTRUCTION,-1,1);
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-5,bl->y-5,bl->x+5,bl->y+5,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ALL|1,
					skill_castend_damage_id);
				mob_damage(NULL,md,md->hp,1);
			}
		}
		break;
	case HVAN_EXPLOSION:	/* バイオエクスプロージョン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = 5;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			if(map[src->m].flag.normal) {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			} else {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
			if(hd) {
				hd->intimate = 1;
				if(battle_config.homun_skill_intimate_type)
					hd->status.intimate = 1;
				clif_send_homdata(hd->msd,1,hd->intimate/100);
			}
			battle_damage(NULL,src,status_get_hp(src),skillid,skilllv,flag);
		}
		break;
	case NJ_TATAMIGAESHI:	/* 畳返し */
		status_change_start(src,SC_TATAMIGAESHI,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_KAENSIN:	/* 火炎陣 */
		bl = src;
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_BAKUENRYU:	/* 龍炎陣 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case GS_DESPERADO:	/* デスペラード */
		{
			int tmpx, tmpy, i, num;
			bl = src;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
					break;
			}
			num = skill_get_num(skillid,skilllv);
			for(i=0; i<num; i++) {
				tmpx = src->x + (atn_rand()%5 - 2);
				tmpy = src->y + (atn_rand()%5 - 2);
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,0);
			}
		}
		break;

	/* HP吸収/HP吸収魔法 */
	case NPC_BLOODDRAIN:
	case NPC_ENERGYDRAIN:
		{
			int heal = battle_skill_attack((skillid == NPC_BLOODDRAIN)? BF_WEAPON: BF_MAGIC,
					src,src,bl,skillid,skilllv,tick,flag);
			if(heal > 0) {
				struct block_list tbl;
				memset(&tbl, 0, sizeof(tbl));
				tbl.m = src->m;
				tbl.x = src->x;
				tbl.y = src->y;
				clif_skill_nodamage(&tbl,src,AL_HEAL,heal,1);
				battle_heal(NULL,src,heal,0,0);
			}
		}
		break;
	case RK_HUNDREDSPEAR:	/* ハンドレッドスピア */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < (10 + 3*skilllv)) {
			skill_blown(src,bl,6|SAB_NOPATHSTOP);
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case RK_IGNITIONBREAK:	/* イグニッションブレイク */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-5,src->y-5,src->x+5,src->y+5,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_WINDCUTTER:		/* ウィンドカッター */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			}
		}
		break;
	case RK_CRUSHSTRIKE:	/* クラッシュストライク */
		if(sd && battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag))
			pc_break_equip(sd, LOC_RARM);
		break;
	case RK_STORMBLAST:		/* ストームブラスト */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
					skill_blown(src,bl,7 - path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]));
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-3,src->y-3,src->x+3,src->y+3,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_PHANTOMTHRUST:	/* ファントムスラスト */
		if(battle_check_target(src,bl,BCT_ENEMY) > 0 || battle_check_target(src,bl,BCT_PARTY) > 0) {
			if(!map[bl->m].flag.gvg && !(status_get_mode(bl)&MD_BOSS)) {
				int posx = 0, posy = 0;

				if(bl->x > src->x) {
					posx = 1;
				} else if(bl->x < src->x) {
					posx = -1;
				}

				if(bl->y >= src->y) {
					posy = 1;
				} else if(bl->y < src->y) {
					posy = -1;
				}
				unit_movepos(bl, src->x+posx, src->y+posy, 0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if (battle_check_target(src,bl,BCT_ENEMY) > 0 ){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;
	case GC_DARKILLUSION:	/* ダークイリュージョン */
	case RA_WUGSTRIKE:		/* ウォーグストライク */
	case LG_PINPOINTATTACK:	/* ピンポイントアタック */
	case KO_JYUMONJIKIRI:	/* 十文字斬り */
		{
			int dist = unit_distance(src,bl);
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1 && (skillid != RA_WUGSTRIKE || pc_iswolfmount(sd))) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,0,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
			if(skillid == GC_DARKILLUSION) {
				if(atn_rand()%100 < (30 - 5*skilllv))
					skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
			}
		}
		break;
	case GC_COUNTERSLASH:	/* カウンタースラッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-1,src->y-1,src->x+1,src->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_end(src,SC_WEAPONBLOCKING2,-1);
		}
		break;
	case GC_VENOMPRESSURE:	/* ベナムプレッシャー */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			sc = status_get_sc(src);
			if(sc && sc->data[SC_POISONINGWEAPON].timer != -1) {
				if(atn_rand() % 10000 < status_change_rate(bl,sc->data[SC_POISONINGWEAPON].val2,7000+skilllv*500,status_get_lv(src)))
					status_change_start(bl,sc->data[SC_POISONINGWEAPON].val2,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				else if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				status_change_end(src,SC_POISONINGWEAPON,-1);
			}
		}
		break;
	case GC_PHANTOMMENACE:	/* ファントムメナス */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				sc = status_get_sc(bl);
				if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING)) {
					if(sc->option & (OPTION_HIDE | OPTION_CLOAKING)) {
						status_change_end(bl, SC_HIDING, -1);
						status_change_end(bl, SC_CLOAKING, -1);
						status_change_end(bl, SC_CLOAKINGEXCEED, -1);
					}
					if(sc->option & OPTION_SPECIALHIDING) {
						status_change_end(bl, SC_INVISIBLE, -1);
					}
					if(sc->data[SC__SHADOWFORM].timer != -1) {
						status_change_end(bl, SC__SHADOWFORM, -1);
					}
					else
						battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				}
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-3,src->y-3,src->x+3,src->y+3,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_ROLLINGCUTTER:	/* ローリングカッター */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_ROLLINGCUTTER].timer == -1) {
					status_change_start(src,SC_ROLLINGCUTTER,1,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_ROLLINGCUTTER].val1 < 10) {
					int rolling = ++sc->data[SC_ROLLINGCUTTER].val1;
					status_change_start(src,SC_ROLLINGCUTTER,rolling,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-1,src->y-1,src->x+1,src->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_CROSSRIPPERSLASHER:	/* クロスリッパースラッシャー */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_end(src,SC_ROLLINGCUTTER,-1);
		break;
	case GC_DARKCROW:	/* ダーククロー */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WL_FROSTMISTY:		/* フロストミスティ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				if(path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y)) {
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				}
				if(atn_rand() % 10000 < 2500 + skilllv * 500)
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-11,src->y-11,src->x+11,src->y+11,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_JACKFROST:		/* ジャックフロスト */
		if(flag&1) {
			if(!path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y))
				break;
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skilllv + 6;
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_DRAINLIFE:		/* ドレインライフ */
		{
			int heal = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(heal > 0 && atn_rand() % 100 < 70 + skilllv * 5) {
				heal = heal * (skilllv * 8 * status_get_lv(src) / 100) / 100;
				if(sd) {
					if(sd->status.hp + heal > sd->status.max_hp)
						heal = sd->status.max_hp - sd->status.hp;
					if(heal <= 0)
						break;
					clif_heal(sd->fd,SP_HP,heal);
				}
				unit_heal(src,heal,0);
			}
		}
		break;
	case WL_CRIMSONROCK:		/* クリムゾンロック */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-3,bl->y-3,bl->x+3,bl->y+3,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_HELLINFERNO:		/* ヘルインフェルノ */
		if(battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand() % 10000 < 5500 + skilllv * 500) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		skill_addtimerskill(src,tick + 300,bl->id,0,0,WL_HELLINFERNO,skilllv,0,(0x0f<<20)|0x500|flag|1);
		break;
	case WL_COMET:				/* コメット */
		if(!path_search_long(NULL,bl->m,bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]))
			break;
		if(bl->id != skill_area_temp[1]) {
			int dist = path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]);
			int type;
			if(dist > 5)
				type = 3;	// 遠距離
			else if(dist > 3)
				type = 2;	// 中距離
			else if(dist > 1)
				type = 1;	// 近距離
			else
				type = 0;	// 中心
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,type);
		}
		break;
	case WL_CHAINLIGHTNING:		/* チェーンライトニング */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_addtimerskill(src,tick + 700,bl->id,0,0,WL_CHAINLIGHTNING_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case RA_ARROWSTORM:		/* アローストーム */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_AIMEDBOLT:      /* エイムドボルト */
		if(sd) {
			int cost = 1;
			sc = status_get_sc(bl);
			if(sc && (sc->data[SC_ANKLE].timer != -1 || sc->data[SC_ELECTRICSHOCKER].timer != -1 || sc->data[SC_WUGBITE].timer != -1))
				cost = status_get_size(bl) + 2;
			if(cost > 0 && !battle_delarrow(sd,cost,skillid))   // 矢の消費
				break;
		}
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case RA_WUGDASH:		/* ウォーグダッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_SENSITIVEKEEN:	/* 鋭敏な嗅覚 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				sc = status_get_sc(bl);
				if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING)) {
					if(sc->option & (OPTION_HIDE | OPTION_CLOAKING)) {
						status_change_end(bl, SC_HIDING, -1);
						status_change_end(bl, SC_CLOAKING, -1);
						status_change_end(bl, SC_CLOAKINGEXCEED, -1);
						status_change_end(bl, SC__INVISIBILITY, -1);
					}
					if(sc->option & OPTION_SPECIALHIDING) {
						status_change_end(bl, SC_INVISIBLE, -1);
					}
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
					if(atn_rand()%100 < (8*skilllv)) {
						skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
					}
				}
			}
		} else if(flag&2) {
			if(bl->type == BL_SKILL) {
				struct skill_unit *su = (struct skill_unit *)bl;
				if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
					break;
				if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2)		// 補足中のアンクルスネアは除外
					break;
				if(itemdb_exists(su->group->val3)) {
					struct item item_tmp;
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid = su->group->val3;
					item_tmp.identify = 1;
					map_addflooritem(&item_tmp,1,bl->m,bl->x,bl->y,0,0,0,0);
				}
				skill_delunit(su);
			}
		} else {
			int ar = skilllv + 2;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ALL|2,
				skill_castend_damage_id);
		}
		break;
	case NC_FLAMELAUNCHER:	/* フレイムスローワー */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			int posx = -dirx[dir] * 2, posy = -diry[dir] * 2;
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,bl->x+posx,bl->y+posy,dirx[dir],diry[dir],5,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case NC_SELFDESTRUCTION:	/* セルフディストラクション */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skilllv + 1;

			if(sd) {
				if(!pc_isgear(sd)) {
					clif_skill_fail(sd,skillid,0,0,0);
					break;
				}
			}

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				/* 魔導ギアを解除 */
				pc_setoption(sd, (sd->sc.option & ~OPTION_MADOGEAR));
				sd->status.sp = 0;
				clif_updatestatus(sd,SP_SP);
			}
		}
		break;
	case NC_AXETORNADO:	/* アックストルネード */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = (skilllv > 2) ? 3: 2;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_POWERSWING:		/* パワースイング */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < 5) {
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case NC_DISJOINT:		/* FAW解除 */
		if(bl->type == BL_MOB) {
			struct mob_data* md = (struct mob_data*)bl;
			if(md->class_ >= 2042 && md->class_ <= 2046 && md->master_id != 0) {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, skilllv, 0);
				mob_damage(src, md, md->hp, 2);
			} else if(sd) {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case SC_FATALMENACE:	/* フェイタルメナス */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				/* 個別にダメージを与える */
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
					skill_addtimerskill(src,tick + 800,bl->id,skill_area_temp[2],skill_area_temp[3],skillid,skilllv,0,0);
				}
			}
		} else {
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			/* まずターゲットに攻撃を加える */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0)) {
				/* ランダムにセルを探索 */
				map_random_freecell(src->m, &skill_area_temp[2], &skill_area_temp[3]);
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				skill_addtimerskill(src,tick + 800,bl->id,skill_area_temp[2],skill_area_temp[3],skillid,skilllv,0,1);
			}
		}
		break;
	case SC_TRIANGLESHOT:	/* トライアングルショット */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand()%10000 < 100 + 100 * skilllv) {
				skill_blown(src,bl,5|SAB_REVERSEBLOW|SAB_NOPATHSTOP);
			}
		}
		break;
	case SC_FEINTBOMB:		/* フェイントボム */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		break;
	case LG_CANNONSPEAR:	/* キャノンスピア */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],10,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case LG_RAGEBURST:		/* レイジバーストアタック */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_FORCEOFVANGUARD].timer != -1 && sc->data[SC_FORCEOFVANGUARD].val4 > 0) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			sc->data[SC_FORCEOFVANGUARD].val4 = 0;
			if(sd)
				clif_mshield(sd,0);
		}
		break;
	case LG_SHIELDSPELL:	/* シールドスペル */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		else if(flag&2) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case LG_OVERBRAND_BRANDISH:		/* オーバーブランド(薙ぎ) */
		{
			int dist = unit_distance(src,bl);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv) + dist) {
				battle_skill_attack(BF_WEAPON,src,src,bl,LG_OVERBRAND_PLUSATK,skilllv,tick,0x0500);
			}
		}
		break;
	case LG_MOONSLASHER:	/* ムーンスラッシャー */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = 3;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case LG_EARTHDRIVE:		/* アースドライブ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = (skilllv + 1) / 2;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_delunit_by_ganbantein,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL);
			if(sd && atn_rand() % 10000 < 500)
				pc_break_equip(sd, LOC_LARM);
		}
		break;
	case SR_SKYNETBLOW:	/* 天羅地網 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = 2;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_EARTHSHAKER:	/* 地雷震 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				sc = status_get_sc(bl);
				if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING)) {
					if(sc->option & (OPTION_HIDE | OPTION_CLOAKING)) {
						status_change_end(bl, SC_HIDING, -1);
						status_change_end(bl, SC_CLOAKING, -1);
						status_change_end(bl, SC_CLOAKINGEXCEED, -1);
						status_change_end(bl, SC__INVISIBILITY, -1);
					}
					if(sc->option & OPTION_SPECIALHIDING) {
						status_change_end(bl, SC_INVISIBLE, -1);
					}
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|1);
				}
				else {
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag&~1);
				}
			}
		} else {
			int ar = skilllv;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_TIGERCANNON:	/* 號砲 */
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
		break;
	case SR_KNUCKLEARROW:	/* 修羅身弾 */
		{
			int dist = unit_distance(src,bl);
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,0,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv)) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500|1);
			}
		}
		break;
	case SR_WINDMILL:	/* 旋風腿 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-2,src->y-2,src->x+2,src->y+2,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_RAMPAGEBLASTER:		/* 爆気散弾 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = 3;
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_HOWLINGOFLION:	/* 獅子吼 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = 2 + skilllv;
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WM_SOUND_OF_DESTRUCTION:	/* サウンドオブディストラクション */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = (skilllv + 1) / 2 + 1;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_CART_TORNADO:	/* カートトルネード */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = 2;
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_CARTCANNON:		/* カートキャノン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = (skilllv + 1) / 2;
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_BLOOD_SUCKER:	/* ブラッドサッカー */
		if(unit_distance(src,bl) < 12){
			int heal = battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x500);
			heal = heal * (5 + skilllv * 5) / 100;
			if(status_get_hp(src) + heal > status_get_max_hp(src))
				heal = status_get_max_hp(src) - status_get_hp(src);
			if(heal > 0) {
				battle_heal(NULL,src,heal,0,0);
				if(sd)
					clif_heal(sd->fd,SP_HP,heal);
			}
		}
		break;
	case GN_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500|1);
		} else {
			int ar = skilllv;
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_ILLUSIONDOPING:	/* イリュージョンドーピング */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
			}
			if( atn_rand() % 10000 < 9000-1000*skilllv )
				status_change_start(bl,SC_ILLUSIONDOPING,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,9000-1000*skilllv,status_get_lv(src)) )
				status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		} else {
			int ar = (skilllv+1)/2;
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20));
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_HAPPOKUNAI:		/* 八方苦無 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = (skilllv < 5)? 4 : 5;
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_MUCHANAGE:	/* 無茶投げ */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		break;
	case KO_MAKIBISHI:			/* 撒菱 */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case KO_KAIHOU:				/* 術式 -解放- */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case SU_BITE:	// かみつく
	case SU_SCAROFTAROU:	// タロウの傷
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SU_SCRATCH:	// ひっかく
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_PICKYPECK:	// ピッキ突き
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(status_get_hp(bl) / status_get_max_hp(bl) * 100 <= 20 + skilllv * 10) {	// 敵のHPが一定以下なら
			battle_skill_attack(BF_WEAPON,src,src,bl,SU_PICKYPECK_DOUBLE_ATK,skilllv,tick,flag);
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// キャロットビート
	case SU_LUNATICCARROTBEAT2:	// キャロットビート(スタン)
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,SU_LUNATICCARROTBEAT,skilllv,tick,flag) > 0) {
				if(skillid == SU_LUNATICCARROTBEAT2 && atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,5000,status_get_lv(src)))
					status_change_pretimer(&sd->bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = 2 + (skilllv+1) / 2;
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_SVG_SPIRIT:	// サベージの魂
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			int dist = unit_distance(src,bl);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],dist,0,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case SU_SV_STEMSPEAR:	/* マタタビランス */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case EL_FIRE_BOMB:		/* ファイアーボム */
	case EL_FIRE_WAVE:		/* ファイアーウェーブ */
	case EL_WATER_SCREW:	/* ウォータースクリュー */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TIDAL_WEAPON:	/* タイダルウェポン */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else if(eld && eld->msd) {
			clif_skill_nodamage(src,&eld->msd->bl,skillid,skilllv,1);
			//clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_HURRICANE:		/* ハリケーンレイジ */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TYPOON_MIS:		/* タイフーンミサイル */
	case EL_ROCK_CRUSHER:	/* ロックランチャー */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,flag);
		}
		break;
	case EL_STONE_RAIN:		/* ストーンレイン */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case 0:
		if(sd) {
			if(flag&3) {
				if(bl->id != skill_area_temp[1])
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			} else {
				int ar = sd->splash_range;
				skill_area_temp[1] = bl->id;
				map_foreachinarea(skill_area_sub,
					bl->m, bl->x - ar, bl->y - ar, bl->x + ar, bl->y + ar, (BL_CHAR|BL_SKILL),
					src, skillid, skilllv, tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	default:
		map_freeblock_unlock();
		return 1;
	}
	map_freeblock_unlock();

	return 0;
}

/*==========================================
 * スキル使用（詠唱完了、ID指定支援系）
 *------------------------------------------
 */
int skill_castend_nodamage_id( struct block_list *src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd  = NULL, *dstsd  = NULL;
	struct mob_data         *md  = NULL, *dstmd  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	int is_enemy = 1;

	nullpo_retr(1, src);
	nullpo_retr(1, bl);

	if(bl->prev == NULL)
		return 1;
	if(unit_isdead(bl) && skillid != ALL_RESURRECTION && skillid != PR_REDEMPTIO && skillid != WM_DEADHILLHERE)
		return 1;
	if(status_get_class(bl) == MOBID_EMPERIUM)
		return 1;

	sd  = BL_DOWNCAST( BL_PC,   src );
	md  = BL_DOWNCAST( BL_MOB,  src );
	hd  = BL_DOWNCAST( BL_HOM,  src );
	mcd = BL_DOWNCAST( BL_MERC, src );
	eld = BL_DOWNCAST( BL_ELEM, src );

	dstsd  = BL_DOWNCAST( BL_PC,   bl );
	dstmd  = BL_DOWNCAST( BL_MOB,  bl );

	if(sd && unit_isdead(&sd->bl))
		return 1;
	if(!md && dstmd && dstmd->mode&MD_SKILLIMMUNITY)
		return 1;

	switch(skillid) {
		case KN_BRANDISHSPEAR:
		case ML_BRANDISH:
			// skill_castend_idで許可したスキルはここで敵チェック
			if(skill_get_inf2(skillid) & INF2_ATTACK || skill_get_inf(skillid) & INF_ATTACK) {
				if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
					is_enemy = 0;
			}
			break;
	}

	map_freeblock_lock();

	switch(skillid)
	{
	case AL_HEAL:				/* ヒール */
	case AB_HIGHNESSHEAL:		/* ハイネスヒール */
		{
			int heal;
			int heal_get_jobexp;
			int lv;
			lv = (skillid == AB_HIGHNESSHEAL)? 10: skilllv;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, lv));
			sc = status_get_sc(bl);
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999ヒール
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// 黄金蟲カード（ヒール量０）
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0; 	// バーサーク中はヒール０
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// 魔道ギア搭乗中はヒール０
			if(sd && dstsd && sd->status.partner_id == dstsd->status.char_id && (sd->s_class.job == PC_CLASS_SNV || sd->s_class.job == PC_CLASS_ESNV) && sd->sex == SEX_FEMALE)
				heal *= 2;	// スパノビの嫁が旦那にヒールすると2倍になる
			if(skillid == AB_HIGHNESSHEAL)
				heal = heal * (170 + 30 * skilllv) / 100;
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// カイト
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// 自分自身に対しては回復量0
					heal = 0;
				} else {		// ヒール反射
					bl = src;
					dstsd = sd;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			heal_get_jobexp = battle_heal(NULL,bl,heal,0,0);

			// JOB経験値獲得
			if(sd && dstsd && heal > 0 && src != bl && battle_config.heal_exp > 0) {
				heal_get_jobexp = heal_get_jobexp * battle_config.heal_exp / 100;
				if(heal_get_jobexp <= 0)
					heal_get_jobexp = 1;
				pc_gainexp(sd,NULL,0,heal_get_jobexp,0);
			}
		}
		break;

	case HLIF_HEAL:		/* 治癒の手助け */
		{
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));
			sc = status_get_sc(bl);
			if(hd) {
				int skill = homun_checkskill(hd,HLIF_BRAIN);
				if(skill > 0)
					heal += heal * skill / 50;
			}
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999ヒール
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// 黄金蟲カード（ヒール量０）
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0;	// バーサーク中はヒール０
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// 魔道ギア搭乗中はヒール０
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// カイト
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// 自分自身に対しては回復量0
					heal = 0;
				} else {		// ヒール反射
					bl = src;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case ALL_RESURRECTION:		/* リザレクション */
		if(!dstsd)
			break;
		if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVPで復活不可能状態
			break;
		if(!unit_isdead(&dstsd->bl))			// 死亡判定
			break;
		if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// ヘルパワー状態は蘇生不可
			break;

		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		dstsd->status.hp = dstsd->status.max_hp * ((skilllv >= 4)? 80: skilllv*20-10)/100;
		if(dstsd->status.hp <= 0)
			dstsd->status.hp = 1;
		if(dstsd->special_state.restart_full_recover) {	// オシリスカード
			dstsd->status.hp = dstsd->status.max_hp;
			dstsd->status.sp = dstsd->status.max_sp;
			clif_updatestatus(dstsd,SP_SP);
		}
		clif_updatestatus(dstsd,SP_HP);
		pc_setstand(dstsd);
		if(battle_config.pc_invincible_time > 0)
			pc_setinvincibletimer(dstsd,battle_config.pc_invincible_time);
		clif_resurrection(&dstsd->bl,1);

		if(src != bl && sd && battle_config.resurrection_exp > 0)
		{
			atn_bignumber exp = 0, jexp = 0;
			int lv  = dstsd->status.base_level - sd->status.base_level;
			int jlv = dstsd->status.job_level  - sd->status.job_level;
			if(lv > 0) {
				exp = (atn_bignumber)dstsd->status.base_exp * lv * battle_config.resurrection_exp / 1000000;
				if(exp < 1)
					exp = 1;
			}
			if(jlv > 0) {
				jexp = (atn_bignumber)dstsd->status.job_exp * jlv * battle_config.resurrection_exp / 1000000;
				if(jexp < 1)
					jexp = 1;
			}
			if(exp > 0 || jexp > 0)
				pc_gainexp(sd,NULL,exp,jexp,0);
		}
		break;

	case AL_DECAGI:			/* 速度減少 */
	case MER_DECAGI:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if( atn_rand()%100 < (50+skilllv*3+(status_get_lv(src)+status_get_int(src)/5)-status_get_mdef(bl)) ) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,0,skill_get_time(skillid,skilllv),0);
			else
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		status_change_release(bl,0x80); // 速度減少による状態異常解除
		break;

	case AL_CRUCIS:
		if(flag&1) {
			int race = status_get_race(bl);
			int ele = status_get_elem_type(bl);
			if(race == RCT_DEMON || battle_check_undead(race,ele)) {
				int rate = 23 + skilllv*4 + status_get_lv(src) - status_get_lv(bl);
				if(atn_rand()%100 < rate)
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,0,0);
			}
		} else {
			const int range = AREA_SIZE;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-range,src->y-range,src->x+range,src->y+range,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;

	case PR_LEXDIVINA:		/* レックスディビーナ */
	case MER_LEXDIVINA:
		sc = status_get_sc(bl);
		if(sc) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if(sc->data[SC_SILENCE].timer != -1) {
				// 沈黙中なら敵味方問わず沈黙解除
				status_change_end(bl,SC_SILENCE,-1);
			} else if(battle_check_target(src,bl,BCT_ENEMY) > 0) {
				if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SA_ABRACADABRA:
		if( sd && !map[src->m].flag.noabra ) {
			int abra_skillid = 0, maxlv;
			int abra_skilllv = pc_checkskill(sd,SA_ABRACADABRA);
			while(abra_skillid == 0) {
				abra_skillid=skill_abra_dataset(sd,skilllv);
			}
			maxlv = skill_get_max(abra_skillid);
			if(abra_skilllv > maxlv)
				abra_skilllv = maxlv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sd->skill_item.id      = abra_skillid;
			sd->skill_item.lv      = abra_skilllv;
			sd->skill_item.flag    = 1;		// 使用条件判定する
			clif_item_skill(sd, abra_skillid, abra_skilllv, msg_txt(179)); // アブラカダブラ
		}
		break;
	case SA_COMA:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd ) {
			if( dstsd->special_state.no_magic_damage )
				break;
			dstsd->status.hp = 1;
			dstsd->status.sp = 1;
			clif_updatestatus(dstsd,SP_HP);
			clif_updatestatus(dstsd,SP_SP);
		}
		else if(dstmd) {
			dstmd->hp = 1;
		}
		break;
	case SA_FULLRECOVERY:
	case NPC_ALLHEAL:		/* ライフストリーム */
		{
			int heal;
			if(skillid == NPC_ALLHEAL)
				heal = status_get_max_hp(bl) - status_get_hp(bl);
			else
				heal = status_get_max_hp(bl);
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			if( dstsd ) {
				if( dstsd->special_state.no_magic_damage )
					break;
				pc_heal(dstsd,heal,dstsd->status.max_sp);
			}
			else if(dstmd) {
				dstmd->hp = status_get_max_hp(bl);
			}
		}
		break;
	case SA_SUMMONMONSTER:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			mob_once_spawn(sd,sd->bl.m,sd->bl.x,sd->bl.y,"--ja--",-1,1,"");
		break;
	case SA_LEVELUP:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && pc_nextbaseexp(sd))
			pc_gainexp(sd,NULL,(atn_bignumber)pc_nextbaseexp(sd)*10/100,0,0);
		break;

	case SA_INSTANTDEATH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			pc_damage(NULL,sd,sd->status.max_hp);
		break;

	case SA_QUESTION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_emotion(bl,1);
		break;
	case SA_GRAVITY:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case SA_CLASSCHANGE:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstmd) {
			// クラスチェンジ用ボスモンスターID
			static const int changeclass[] = {
				1038,1039,1046,1059,1086,1087,1112,1115,1147,1150,
				1157,1159,1190,1251,1252,1272,1312,1373,1389,1418,
				1492,1511
			};
			mob_class_change(dstmd,changeclass,sizeof(changeclass)/sizeof(changeclass[0]));
		}
		break;
	case SA_MONOCELL:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstmd) {
			// チェンジポリン用モンスターID
			static const int poringclass[] = { MOBID_PORING, MOBID_PORING };
			mob_class_change(dstmd,poringclass,sizeof(poringclass)/sizeof(poringclass[0]));
		}
		break;
	case SA_DEATH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd)
			pc_damage(NULL,dstsd,dstsd->status.max_hp);
		else if(dstmd)
			mob_damage(NULL,dstmd,dstmd->hp,1);
		break;
	case SA_REVERSEORCISH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd)
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SA_FORTUNE:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			pc_getzeny(sd,status_get_lv(bl)*100);
		break;
	case SA_TAMINGMONSTER:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && dstmd) {
			if(pet_search_data(dstmd->class_, PET_CLASS) != NULL)
				pet_catch_process1(sd,dstmd->class_);
		}
		break;
	case PF_SPIDERWEB:		/* スパイダーウェブ */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case AL_INCAGI:			/* 速度増加 */
	case MER_INCAGI:
	case AL_BLESSING:		/* ブレッシング */
	case MER_BLESSING:
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_HIGH].timer != -1)
			status_change_end(bl,SC_HIGH,-1);
		if(dstsd && dstsd->sc.data[SC_ELEMENTUNDEAD].timer != -1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			break;
		}
	case PR_SLOWPOISON:
	case PR_IMPOSITIO:		/* イムポシティオマヌス */
	case PR_LEXAETERNA:		/* レックスエーテルナ */
	case PR_SUFFRAGIUM:		/* サフラギウム */
	case CR_PROVIDENCE:		/* プロヴィデンス */
	case SA_FLAMELAUNCHER:		/* フレイムランチャー */
	case SA_FROSTWEAPON:		/* フロストウェポン */
	case SA_LIGHTNINGLOADER:	/* ライトニングローダー */
	case SA_SEISMICWEAPON:		/* サイズミックウェポン */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_BENEDICTIO:		/* 聖体降福 */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON )
				break;
			if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SA_ELEMENTWATER:	/* ウォーターエレメンタルチェンジ */
	case SA_ELEMENTGROUND:	/* アースエレメンタルチェンジ */
	case SA_ELEMENTFIRE:	/* ファイアーエレメンタルチェンジ */
	case SA_ELEMENTWIND:	/* ウィンドエレメンタルチェンジ */
		if(dstmd) {
			// ボス属性だった場合と暫定で40%の確率で使用失敗
			if((battle_config.boss_no_element_change && dstmd && dstmd->mode&MD_BOSS) || atn_rand() % 100 < 40) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			// 敵は属性レベルを維持する
			switch(skillid) {
				case SA_ELEMENTWATER:	// 水
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WATER;
					break;
				case SA_ELEMENTGROUND:	// 土
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_EARTH;
					break;
				case SA_ELEMENTFIRE:	// 火
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_FIRE;
					break;
				case SA_ELEMENTWIND:	// 風
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WIND;
					break;
			}
			// ディスペル対策を一応やる？
			//status_change_start(bl,GetSkillStatusChangeTable(skillid),dstmd->def_ele/20,0,0,0,skill_get_time(skillid,skilllv),0 );
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		else if(!dstsd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NPC_CHANGEUNDEAD:		/* 不死属性付与 */
		if( dstsd && dstsd->special_state.no_magic_damage ) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else {
			if(status_get_elem_type(bl) == ELE_DARK || status_get_race(bl) == RCT_DEMON)
				break;
			status_change_start(bl,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;

	case BA_PANGVOICE:	/* パンボイス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_CONFUSION].timer != -1)
			status_change_end(bl,SC_CONFUSION,-1);
		else if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,7000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,0,0,0);
		break;
	case DC_WINKCHARM:	/* 魅惑のウィンク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd) {
			if(atn_rand() % 10000 < status_change_rate(&dstsd->bl,SC_CONFUSION,1000,status_get_lv(src))) {
				status_change_pretimer(&dstsd->bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
				break;
			}
		} else if(dstmd) {
			int race = status_get_race(&dstmd->bl);
			if( !(dstmd->mode&MD_BOSS) && (race == RCT_DEMON || race == RCT_HUMAN || race == RCT_ANGEL) ) {
				if(atn_rand() % 100 < 40 + status_get_lv(src) - status_get_lv(bl)) {
					status_change_start(&dstmd->bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,10000,0);
					break;
				}
			}
		}
		if(sd)
			clif_skill_fail(sd,skillid,0,0,0);
		break;
	case TK_RUN:		/* タイリギ */
		if(sd) {
			if(sd->sc.data[SC_RUN].timer != -1) {
				// 5セル以内でLv7以上で素手ならスパート開始
				if(sd->sc.data[SC_RUN].val4 >= 2) {
					int lv = sd->sc.data[SC_RUN].val1;
			   		if(lv >= 7 && sd->sc.data[SC_RUN].val4 <= 6 && sd->weapontype1 == WT_FIST && sd->weapontype2 == WT_FIST)
						status_change_start(bl,SC_SPURT,lv,0,0,0,skill_get_time2(TK_RUN,lv),0);
					status_change_end(bl,SC_RUN,-1);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
				}
			} else {
				status_change_start(bl,SC_RUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TK_HIGHJUMP:	/* ノピティギ */
		{
			int dir = status_get_dir(src);
			int x,y;
			if(dir & 1) {	// 斜め移動の場合
				x = src->x + dirx[dir] * (skilllv+skilllv/3);
				y = src->y + diry[dir] * (skilllv+skilllv/3);
			} else {
				x = src->x + dirx[dir] * skilllv*2;
				y = src->y + diry[dir] * skilllv*2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 着地地点とその一歩先が移動可能セルでPC,MOB,NPCいずれも居ないなら
			if( !map[src->m].flag.pvp && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
			    map_getcell(src->m,x,y,CELL_CHKPASS) && map_getcell(src->m,x+dirx[dir],y+diry[dir],CELL_CHKPASS) &&
			    !map_count_oncell(src->m,x,y,BL_PC|BL_MOB|BL_NPC)
			) {
				unit_movepos(src,x,y,0x11);
			}
		}
		break;
	case TK_MISSION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && pc_checkskill(sd,TK_MISSION)>0)
		{
			if(sd->status.class_ == PC_CLASS_TK) {
				int count = ranking_get_point(sd,RK_TAEKWON)%100;
				if(sd->tk_mission_target == 0 || (count == 0 && atn_rand()%100 == 0))
				{
					int i = 0;
					while(i++ < 1000) {
						sd->tk_mission_target = mobdb_searchrandomid(1,sd->status.base_level);
						if(mob_db[sd->tk_mission_target].max_hp <= 0)
							continue;
						if(mob_db[sd->tk_mission_target].mode&MD_BOSS)	// ボス属性除外
							continue;
						break;
					}
					if(i >= 1000)
						sd->tk_mission_target = 0;
					pc_setglobalreg(sd,"PC_MISSION_TARGET",sd->tk_mission_target);
				}
				clif_mission_mob(sd,sd->tk_mission_target,count);
			} else {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case SG_SUN_WARM:		/* 太陽の温もり */
	case SG_MOON_WARM:		/* 月の温もり */
	case SG_STAR_WARM:		/* 星の温もり */
		{
			struct skill_unit_group *sg;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_WARM].timer != -1) {
				status_change_end(src,SC_WARM,-1);
			}
			sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,bl->id,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TK_SEVENWIND:		/* 暖かい風 */
		{
#ifdef PRE_RENEWAL
			int type = (skilllv < 7)? GetSkillStatusChangeTable(skillid): SC_ASPERSIO;
#else
			int type = GetSkillStatusChangeTable(skillid);
#endif
			status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SL_SWOO:			/* エスウ */
		if(sd && !dstmd && !battle_config.allow_es_magic_all) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,10000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_SWOO].timer != -1) {
			status_change_end(bl,SC_SWOO,-1);
			status_change_pretimer(src,SC_STUN,7,0,0,0,10000,0,tick+status_get_amotion(src));
		} else {
			status_change_start(bl,SC_SWOO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case SL_SKA:			/* エスカ */
	case SL_SKE:			/* エスク */
		if( sd && !dstmd && !battle_config.allow_es_magic_all ) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,1000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(skillid == SL_SKE)
			status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		break;
	case SL_KAAHI:			/* カアヒ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_KAAHI].timer != -1) {
			status_change_end(src,SC_KAAHI,-1);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_ASPERSIO:		/* アスペルシオ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_KYRIE:			/* キリエエレイソン */
	case MER_KYRIE:
		clif_skill_nodamage(bl,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SM_AUTOBERSERK:
	case KN_AUTOCOUNTER:		/* オートカウンター */
	case KN_TWOHANDQUICKEN:		/* ツーハンドクイッケン */
	case CR_SPEARQUICKEN:		/* スピアクイッケン */
	case CR_REFLECTSHIELD:
	case AS_ENCHANTPOISON:		/* エンチャントポイズン */
	case AS_POISONREACT:		/* ポイズンリアクト */
	case MC_LOUD:			/* ラウドボイス */
	case MG_ENERGYCOAT:		/* エナジーコート */
	case AL_RUWACH:			/* ルアフ */
	case MO_EXPLOSIONSPIRITS:	/* 爆裂波動 */
	case MO_STEELBODY:		/* 金剛 */
	case WE_BABY:
	case LK_AURABLADE:		/* オーラブレイド */
	case WS_CARTBOOST:		/* カートブースト */
	case SN_SIGHT:			/* トゥルーサイト */
	case WS_MELTDOWN:		/* メルトダウン */
	case ST_REJECTSWORD:		/* リジェクトソード */
	case HW_MAGICPOWER:		/* 魔法力増幅 */
	case PF_MEMORIZE:		/* メモライズ */
	case PF_DOUBLECASTING:		/* ダブルキャスティング */
	case PA_SACRIFICE:		/* サクリファイス */
	case ST_PRESERVE:		/* プリザーブ */
	case WS_OVERTHRUSTMAX:		/* オーバートラストマックス */
	case WZ_SIGHTBLASTER:		/* サイトブラスター */
	case KN_ONEHAND:		/* ワンハンドクイッケン */
	case TK_READYSTORM:
	case TK_READYDOWN:
	case TK_READYTURN:
	case TK_READYCOUNTER:
	case TK_DODGE:
	case SG_SUN_COMFORT:
	case SG_MOON_COMFORT:
	case SG_STAR_COMFORT:
	case SL_KAIZEL:			/* カイゼル */
	case SL_KAITE:			/* カイト */
	case SL_KAUPE:			/* カウプ */
	case GS_INCREASING:		/* インクリージングアキュアラシー */
	case NJ_UTSUSEMI:		/* 空蝉の術 */
	case NJ_NEN:			/* 念 */
	case NPC_POWERUP:		/* ラッシュアタック */
	case NPC_AGIUP:			/* 速度強化 */
	case NPC_DEFENDER:
	case NPC_MAGICMIRROR:		/* マジックミラー */
	case NPC_HELLPOWER:			/* ヘルパワー */
	case RK_DEATHBOUND:			/* デスバウンド */
	case RK_MILLENNIUMSHIELD:	/* ミレニアムシールド */
	case RK_GIANTGROWTH:		/* ジャイアントグロース */
	case RK_VITALITYACTIVATION:	/* バイタリティアクティベーション */
	case RK_ABUNDANCE:			/* アバンダンス */
	case GC_VENOMIMPRESS:		/* ベナムインプレス */
	case GC_WEAPONBLOCKING:		/* ウェポンブロッキング */
	case GC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
	case AB_RENOVATIO:			/* レノヴァティオ */
	case AB_EXPIATIO:			/* エクスピアティオ */
	case AB_DUPLELIGHT:			/* デュプレライト */
	case AB_SECRAMENT:			/* サクラメント */
	case AB_OFFERTORIUM:		/* オフェルトリウム */
	case WL_MARSHOFABYSS:		/* マーシュオブアビス */
	case WL_RECOGNIZEDSPELL:	/* リゴグナイズドスペル */
	case WL_TELEKINESIS_INTENSE:	/* テレキネシスインテンス */
	case RA_FEARBREEZE:			/* フィアーブリーズ */
	case RA_UNLIMIT:			/* アンリミット */
	case NC_ACCELERATION:		/* アクセラレーション */
	case NC_HOVERING:			/* ホバーリング */
	case NC_SHAPESHIFT:			/* シェイプシフト */
	case SC_REPRODUCE:			/* リプロデュース */
	case SC_DEADLYINFECT:		/* デッドリーインフェクト */
	case LG_REFLECTDAMAGE:		/* リフレクトダメージ */
	case LG_FORCEOFVANGUARD:	/* フォースオブバンガード */
	case LG_EXEEDBREAK:			/* イクシードブレイク */
	case LG_PRESTIGE:			/* プレスティージ */
	case SR_CRESCENTELBOW:		/* 破碎柱 */
	case SR_LIGHTNINGWALK:		/* 閃電歩 */
	case SR_GENTLETOUCH_ENERGYGAIN:	/* 点穴 -球- */
	case WM_GLOOMYDAY:			/* メランコリー */
	case GN_CARTBOOST:			/* カートブースト */
	case ALL_ODINS_POWER:		/* オーディンの力 */
	case KO_MEIKYOUSISUI:		/* 明鏡止水 */
	case MS_REFLECTSHIELD:
	case MER_QUICKEN:			/* ウェポンクイッケン */
	case MER_AUTOBERSERK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_STONESKIN:		/* ストーンスキン */
	case NPC_ANTIMAGIC:		/* アンチマジック */
		//clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_PARRYING:		/* パリイング */
	case MG_SIGHT:			/* サイト */
	case MS_PARRYING:
	case MER_SIGHT:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case HP_ASSUMPTIO:		/* アスムプティオ */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		break;
	case CASH_ASSUMPTIO:	/* パーティーアスムプティオ */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LK_CONCENTRATION:	/* コンセントレイション */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick;
		status_change_start(bl,SC_ENDURE,1,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_BERSERK:		/* バーサーク */
	case MS_BERSERK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd) {
			sd->status.hp = sd->status.max_hp;
			clif_updatestatus(sd,SP_HP);
		} else if(hd) {
			hd->status.hp = hd->max_hp;
			clif_send_homstatus(hd->msd,0);
		} else if(mcd) {
			mcd->status.hp = mcd->max_hp;
			clif_mercupdatestatus(mcd->msd,SP_HP);
		}
		break;
	case SM_ENDURE:			/* インデュア */
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick + 10000;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_TENSIONRELAX:	/* テンションリラックス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd){
			pc_setsit(sd);
			clif_sitting(&sd->bl, 1);
		}
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case MC_CHANGECART:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case AC_CONCENTRATION:	/* 集中力向上 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		map_foreachinarea(status_change_timer_sub,
			src->m,src->x-1,src->y-1,src->x+1,src->y+1,BL_CHAR,
			src,GetSkillStatusChangeTable(skillid),skilllv,tick);
		break;
	case SM_PROVOKE:		/* プロボック */
	case SM_SELFPROVOKE:	/* セルフプロボック */
	case MER_PROVOKE:
		// MVPmobと不死には効かない・成功判定
		if( status_get_mode(bl)&MD_BOSS || battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) || atn_rand()%100 > 70 + skilllv * 3 + status_get_lv(src) - status_get_lv(bl) ) {
			if(skillid != SM_SELFPROVOKE) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				map_freeblock_unlock();
				return 1;
			}
		}
		clif_skill_nodamage(src,bl,(skillid == SM_SELFPROVOKE)? SM_PROVOKE : skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );

		// 凍結・石化・睡眠を解除
		status_change_attacked_end(bl);

		if(dstmd) {
			int range = skill_get_fixed_range(src,skillid,skilllv);
			mob_target(dstmd,src,range);
			battle_join_struggle(dstmd, src);
			if(dstmd->state.angry)
				dstmd->state.angry = 0;
		}
		if(sd)	// 使用者がプレイヤーのとき詠唱妨害
			unit_skillcastcancel(bl,2);
		break;

	case CG_MARIONETTE:		/* マリオネットコントロール */
		if(sd && dstsd)
		{
			status_change_start(src,SC_MARIONETTE,1,bl->id,0,0,60000,0);
			status_change_start(bl,SC_MARIONETTE2,1,src->id,0,0,60000,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		}
		break;
	case CR_DEVOTION:		/* ディボーション */
		if(sd && dstsd) {
			int i, n;
			int lv   = abs(sd->status.base_level - dstsd->status.base_level);
			int type = GetSkillStatusChangeTable(skillid);

			if( sd->bl.id == dstsd->bl.id ||			// 相手は自分はダメ
			    lv > battle_config.devotion_level_difference ||	// レベル差
			    sd->status.party_id <= 0 ||				// 自分がPT未所属だとダメ
			    dstsd->status.party_id <= 0 ||			// 相手がPT未所属だとダメ
			    sd->status.party_id != dstsd->status.party_id ||	// 同じパーティじゃないとダメ
			    dstsd->s_class.job == PC_JOB_CR ||		// 相手がクルセイダーだとダメ
			    dstsd->s_class.job == PC_JOB_LG ||		// 相手がロイヤルガードだとダメ
			    (type >= 0 && dstsd->sc.data[type].timer != -1 && dstsd->sc.data[type].val1 != sd->bl.id) )	// 違うクルセからディボーション済みならダメ
			{
				clif_skill_fail(sd,skillid,0,0,0);
				map_freeblock_unlock();
				return 1;
			}

			for(i = 0, n = -1; i < skilllv && i < 5; i++) {
				if(sd->dev.val1[i] == dstsd->bl.id) {	// 既にディボーション済みの相手
					n = i;
					break;
				}
				if(!sd->dev.val1[i])	// 空きがあったら確保する
					n = i;
			}
			if(n < 0) {	// 何故か空きがなかった
				map_freeblock_unlock();
				return 1;
			}
			sd->dev.val1[n] = dstsd->bl.id;
			sd->dev.val2[n] = dstsd->bl.id;
			clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,skilllv,1);
			clif_devotion(sd);
			status_change_start(&dstsd->bl,type,sd->bl.id,1,0,0,skill_get_time(skillid,skilllv),0 );
		}
		else if(sd) {
			if(dstmd) {
				int range = skill_get_fixed_range(&sd->bl,skillid,skilllv);
				clif_skill_nodamage(&sd->bl,&dstmd->bl,skillid,skilllv,1);
				mob_target(dstmd, &sd->bl, range);
				battle_join_struggle(dstmd, &sd->bl);
			} else {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case MO_CALLSPIRITS:	/* 気功 */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case CH_SOULCOLLECT:	/* 練気功 */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),MAX_SPIRITBALL);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case MO_BLADESTOP:	/* 白刃取り */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;
	case MO_ABSORBSPIRITS:	/* 気奪 */
		{
			int val = 0;
			if(dstsd && dstsd->spiritball.num > 0) {
				if( sd && sd != dstsd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk )
					break;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				val = dstsd->spiritball.num * 7;
				pc_delspiritball(dstsd,dstsd->spiritball.num,0);
			} else if(dstmd && !(dstmd->mode&MD_BOSS)) { // 対象がモンスターでBOSS属性でない場合
				// 20%の確率で対象のLv*2のSPを回復する。成功したときはターゲッティングする。
				if(atn_rand()%100 < 20) {
					val = 2 * mob_db[dstmd->class_].lv;
					mob_target(dstmd,src,0);
					battle_join_struggle(dstmd, src);
					unit_skillcastcancel(bl,2);	// 詠唱妨害

					// 凍結・石化・睡眠を解除
					status_change_attacked_end(bl);
				}
			}
			if(sd) {
				if(val > 0x7FFF)
					val = 0x7FFF;
				if(sd->status.sp + val > sd->status.max_sp)
					val = sd->status.max_sp - sd->status.sp;
				if(val > 0) {
					sd->status.sp += val;
					clif_heal(sd->fd,SP_SP,val);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
				} else {
					clif_skill_fail(sd,skillid,0,0,0);
				}
			}
		}
		break;

	case AC_MAKINGARROW:		/* 矢作成 */
		if(sd) {
			clif_arrow_create_list(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_PHARMACY:			/* ポーション作成 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_PHARMACY,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_TWILIGHT1:
	case AM_TWILIGHT2:
	case AM_TWILIGHT3:
		if(sd) {
			skill_am_twilight(sd,skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_CALLHOMUN:	/* コールホムンクルス */
		if(sd && !sd->hd) {
			homun_callhom(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_REST:				/* 安息 */
		if(sd && homun_isalive(sd)) {
			homun_return_embryo(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_RESURRECTHOMUN:				/* リザレクションホムンクルス */
		if(sd && !sd->hd && sd->hom.hp <= 0) {
			homun_revive(sd,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ASC_CDP:				/* デッドリーポイズン作成 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_CDP,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATECOIN:			/* クリエイトコイン */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_COIN,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATENUGGET:			/* 塊製造 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_NUGGET,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SA_CREATECON:
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_CONVERTER,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case BS_HAMMERFALL:		/* ハンマーフォール */
		if( dstsd && dstsd->special_state.no_weapon_damage )
			break;
		if( atn_rand() % 10000 < status_change_rate(bl,SC_STUN,(skilllv > 5)? 10000: 2000+skilllv*1000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RG_RAID:			/* サプライズアタック */
		{
			int ar = 1;
#ifndef PRE_RENEWAL
			ar += 2;
#endif
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,SC_RAID,0,10,0,0,skill_get_time(skillid,skilllv),0 );
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_end(src, SC_HIDING, -1);	// ハイディング解除
		}
		break;
	case ASC_METEORASSAULT:	/* メテオアサルト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		map_foreachinarea(skill_area_sub,
			bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
			src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
			skill_castend_damage_id);
		break;
	case KN_BRANDISHSPEAR:	/* ブランディッシュスピア */
	case ML_BRANDISH:
		{
			int c, n = 4;
			int dir = path_calc_dir(src,bl->x,bl->y);
			struct square tc;

			skill_brandishspear_first(&tc,dir,bl->x,bl->y);
			skill_brandishspear_dir(&tc,dir,4);

			skill_area_temp[1] = 0;

			/* 範囲4 */
			if(skilllv > 9) {
				for(c=1; c<4; c++) {
					map_foreachinarea(skill_area_sub,
						bl->m,tc.val1[c],tc.val2[c],tc.val1[c],tc.val2[c],(BL_CHAR|BL_SKILL),
						src,skillid,skilllv,tick, flag|BCT_ENEMY|n,
						skill_castend_damage_id);
				}
			}
			/* 範囲3,2 */
			if(skilllv > 6) {
				skill_brandishspear_dir(&tc,dir,-1);
				n--;
			} else {
				skill_brandishspear_dir(&tc,dir,-2);
				n-=2;
			}
			if(skilllv > 3) {
				for(c=0; c<5; c++) {
					map_foreachinarea(skill_area_sub,
						bl->m,tc.val1[c],tc.val2[c],tc.val1[c],tc.val2[c],(BL_CHAR|BL_SKILL),
						src,skillid,skilllv,tick, flag|BCT_ENEMY|n,
						skill_castend_damage_id);
					if(skilllv > 6 && n == 3 && c == 4) {
						skill_brandishspear_dir(&tc,dir,-1);
						n--;
						c = -1;
					}
				}
			}
			/* 範囲1 */
			for(c=0; c<10; c++) {
				if(c == 0 || c == 5)
					skill_brandishspear_dir(&tc,dir,-1);
				map_foreachinarea(skill_area_sub,
					bl->m,tc.val1[c%5],tc.val2[c%5],tc.val1[c%5],tc.val2[c%5],(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}

			if(skill_area_temp[1] == 0) {
				skill_castend_damage_id(src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case GS_GLITTERING:		/* フリップザコイン */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(atn_rand()%100 < 20 + skilllv * 10) {
				pc_addcoin(sd,skill_get_time(skillid,skilllv),10);
			} else {
				pc_delcoin(sd,1,0);
			}
		}
		break;

	/* パーティスキル */
	case AL_ANGELUS:		/* エンジェラス */
	case PR_MAGNIFICAT:		/* マグニフィカート */
	case PR_GLORIA:			/* グロリア */
	case SN_WINDWALK:		/* ウインドウォーク */
	case CASH_BLESSING:		/* パーティーブレッシング */
	case CASH_INCAGI:		/* パーティー速度増加 */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case BS_ADRENALINE:		/* アドレナリンラッシュ */
	case BS_ADRENALINE2:		/* フルアドレナリンラッシュ */
	case BS_WEAPONPERFECT:		/* ウェポンパーフェクション */
	case BS_OVERTHRUST:		/* オーバートラスト */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((src == bl)? 1: 0),0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MER_MAGNIFICAT:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		clif_skill_nodamage(bl,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);

		if(mcd && mcd->msd) {
			// 傭兵なら雇い主にも
			if( mcd->msd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(&mcd->msd->bl,&mcd->msd->bl,skillid,skilllv,1);
			status_change_start(&mcd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	/*（付加と解除が必要） */
	case BS_MAXIMIZE:		/* マキシマイズパワー */
	case NV_TRICKDEAD:		/* 死んだふり */
	case CR_DEFENDER:		/* ディフェンダー */
	case CR_AUTOGUARD:		/* オートガード */
	case CR_SHRINK:			/* シュリンク */
	case GS_GATLINGFEVER:			/* ガトリングフィーバー */
	case ML_DEFENDER:
	case ML_AUTOGUARD:
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				if(skillid == BS_MAXIMIZE)
					status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
				else
					status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case TF_HIDING:			/* ハイディング */
	case KO_YAMIKUMO:		/* 闇雲 */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			if(sc && sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(bl,SC_CLOSECONFINE,-1);
		}
		break;

	case ST_CHASEWALK:		/* チェイスウォーク */
	case AS_CLOAKING:		/* クローキング */
	case GC_CLOAKINGEXCEED:	/* クローキングエクシード */
	case SC_INVISIBILITY:	/* インビジビリティ */
	case NPC_INVISIBLE:		/* インビジブル */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
			}
			if(skillid == AS_CLOAKING && skilllv < 3)
				skill_check_cloaking(bl);
		}
		break;

	/* 対地スキル */
	case HP_BASILICA:			/* バジリカ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BASILICA].timer != -1) {
			skill_basilica_cancel(src);
			status_change_end(bl,SC_BASILICA,-1);
			break;
		}
		status_change_start(bl,SC_BASILICA,skilllv,bl->id,0,0,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case BD_LULLABY:			/* 子守唄 */
	case BD_RICHMANKIM:			/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:		/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:		/* ニーベルングの指輪 */
	case BD_ROKISWEIL:			/* ロキの叫び */
	case BD_INTOABYSS:			/* 深淵の中に */
	case BD_SIEGFRIED:			/* 不死身のジークフリード */
	case BA_DISSONANCE:			/* 不協和音 */
	case BA_POEMBRAGI:			/* ブラギの詩 */
	case BA_WHISTLE:			/* 口笛 */
	case BA_ASSASSINCROSS:		/* 夕陽のアサシンクロス */
	case BA_APPLEIDUN:			/* イドゥンの林檎 */
	case DC_UGLYDANCE:			/* 自分勝手なダンス */
	case DC_HUMMING:			/* ハミング */
	case DC_DONTFORGETME:		/* 私を忘れないで… */
	case DC_FORTUNEKISS:		/* 幸運のキス */
	case DC_SERVICEFORYOU:		/* サービスフォーユー */
	case CG_MOONLIT:			/* 月明りの下で */
	case CG_HERMODE:			/* ヘルモードの杖 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case CG_LONGINGFREEDOM:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,SC_LONGINGFREEDOM,skilllv,0,0,0,1000,0);
		break;

	case PA_GOSPEL:				/* ゴスペル */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_GOSPEL].timer != -1) {
			status_change_end(bl,SC_GOSPEL,-1);
		} else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			status_change_release(src,0x04);	// ゴスペル術者のステータス異常解除
			if(sg) {
				clif_skill_poseffect(src,skillid,skilllv,src->x,src->y,tick);
				status_change_start(bl,SC_GOSPEL,skilllv,bl->id,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case BD_ADAPTATION:			/* アドリブ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_DANCING].timer != -1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_stop_dancing(src,0);
		}
		break;

	case BA_FROSTJOKE:			/* 寒いジョーク */
	case DC_SCREAM:				/* スクリーム */
		if( sd || (md && mob_is_pcview(md->class_)) ) {
			// 見た目がPCでない場合は何故か姿が消えてしまうので除外する
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		skill_addtimerskill(src,tick+3000,bl->id,0,0,skillid,skilllv,0,flag);
		if(md) {		// Mobは喋れないから、スキル名を叫ばせてみる
			char output[100];
			if(skillid == BA_FROSTJOKE)
				snprintf(output, sizeof(output), msg_txt(181), md->name); // %s : 寒いジョーク !!
			else
				snprintf(output, sizeof(output), msg_txt(182), md->name); // %s : スクリーム !!
			clif_GlobalMessage(&md->bl, output, AREA_CHAT_WOC);
		}
		break;

	case TF_STEAL:			/* スティール */
		if(sd) {
			if(dstmd && pc_steal_item(sd,dstmd))
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			else
				clif_skill_fail(sd,skillid,0x0a,0,0);
		}
		break;

	case RG_STEALCOIN:		/* スティールコイン */
		if(sd) {
			if(dstmd && pc_steal_coin(sd,dstmd)) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			} else {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;

	case MG_STONECURSE:			/* ストーンカース */
		if(status_get_mode(bl)&MD_BOSS) {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd && dstsd->special_state.no_magic_damage)
			break;
		if(dstmd)
			mob_target(dstmd,src,skill_get_fixed_range(src,skillid,skilllv));

		sc = status_get_sc(bl);
		if(sc && sc->data[SC_STONE].timer != -1) {
			status_change_end(bl,SC_STONE,-1);
		} else if(!battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) && atn_rand() % 10000 < status_change_rate(bl,SC_STONE,skilllv*400+2000,status_get_lv(src))) {
			status_change_start(bl,SC_STONE,skilllv,0,0,5000,skill_get_time2(skillid,skilllv),0);

			// 成功なのでLv6以上はジェム消費処理
			if(skilllv >= 6) {
				int i, val;
				struct map_session_data *msd = map_bl2msd(src);

				if(msd == NULL)
					break;

				for(i=0; i<10; i++) {
					if(skill_db[skillid].itemid[i] < 715 || skill_db[skillid].itemid[i] > 717)
						continue;

					val = skill_db[skillid].amount[i];
					if(msd->special_state.no_gemstone || msd->sc.data[SC_WIZARD].timer != -1 || msd->sc.data[SC_INTOABYSS].timer != -1)
						val--;

					if(val > 0) {
						int idx = pc_search_inventory(msd,skill_db[skillid].itemid[i]);
						if(idx < 0)
							continue;
						pc_delitem(msd,idx,val,0,1);
					}
				}
			}
		} else {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
		}
		break;

	case NV_FIRSTAID:			/* 応急手当 */
		{
			int heal = skill_fix_heal(src, bl, skillid, 5);
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case AL_CURE:				/* キュアー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		break;

	case TF_DETOXIFY:			/* 解毒 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_DPOISON, -1);
		break;

	case PR_STRECOVERY:			/* リカバリー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_STUN, -1);
		if( battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) ) {	// アンデッドなら暗闇効果
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
				status_change_pretimer(bl, SC_BLIND,1,0,0,0,30000,0,tick+status_get_amotion(src));
		}
		if(dstmd) {
			mob_unlocktarget(dstmd,tick);
			dstmd->attacked_id = 0;
			dstmd->attacked_players = 0;
		}
		break;

	case WZ_ESTIMATION:			/* モンスター情報 */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_estimation(sd,bl);
		}
		break;
	case MER_ESTIMATION:
		if(mcd && mcd->msd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_estimation(mcd->msd,bl);
		}
		break;

	case MC_IDENTIFY:			/* アイテム鑑定 */
		if(sd)
			clif_item_identify_list(sd);
		break;

	case WS_WEAPONREFINE:		/* 武器精錬 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			clif_weapon_refine_list(sd);
		break;

	case BS_REPAIRWEAPON:			/* 武器修理 */
		if(sd && dstsd)
			clif_item_repair_list(sd,dstsd);
		break;

	case MC_VENDING:			/* 露店開設 */
		if(sd && pc_iscarton(sd)) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,83,0,0);
				return 1;
			}
			clif_openvendingreq(sd,2+sd->ud.skilllv);
		}
		break;

	case AL_TELEPORT:			/* テレポート */
		{
			int alive = 1;
			if(!md || !(md->mode&MD_BOSS) || !battle_config.boss_teleport_on_landprotector) {
				// PCおよび一般MOBはランドプロテクター上ではテレポート不可
				map_foreachinarea(skill_landprotector,src->m,src->x,src->y,src->x,src->y,BL_SKILL,skillid,&alive);
			}
			if(alive) {
				if(sd) {
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					if(sd->ud.skilllv == 1) {
						clif_skill_warppoint(sd,sd->ud.skillid,"Random","","","");
					} else {
						clif_skill_warppoint(sd,sd->ud.skillid,"Random",sd->status.save_point.map,"","");
					}
				} else if(md && md->sc.data[SC_ANKLE].timer == -1) {
					mob_warp(md,-1,-1,-1,3);
				}
			}
		}
		break;

	case AL_HOLYWATER:			/* アクアベネディクタ */
		if(sd) {
			int eflag;
			struct item item_tmp;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 523;
			item_tmp.identify = 1;
			if(battle_config.holywater_name_input) {
				item_tmp.card[0] = 0xfe;
				item_tmp.card[1] = 0;
				*((int *)(&item_tmp.card[2]))=sd->status.char_id;	// キャラID
			}
			eflag = pc_additem(sd,&item_tmp,1);
			if(eflag) {
				clif_additem(sd,0,0,eflag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		break;
	case TF_PICKSTONE:
		if(sd) {
			int eflag;
			struct item item_tmp;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 7049;
			item_tmp.identify = 1;
			clif_takeitem(&sd->bl,0);
			eflag = pc_additem(sd,&item_tmp,1);
			if(eflag) {
				clif_additem(sd,0,0,eflag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		break;

	case RG_STRIPWEAPON:		/* ストリップウェポン */
	case RG_STRIPSHIELD:		/* ストリップシールド */
	case RG_STRIPARMOR:			/* ストリップアーマー */
	case RG_STRIPHELM:			/* ストリップヘルム */
		{
			int cp_scid, scid, equip;
			int strip_fix, strip_time;

			scid = GetSkillStatusChangeTable(skillid);
			if(scid < 0)
				break;
			switch (skillid) {
				case RG_STRIPWEAPON:
					equip   = LOC_RARM;
					cp_scid = SC_CP_WEAPON;
					break;
				case RG_STRIPSHIELD:
					equip   = LOC_LARM;
					cp_scid = SC_CP_SHIELD;
					break;
				case RG_STRIPARMOR:
					equip   = LOC_BODY;
					cp_scid = SC_CP_ARMOR;
					break;
				case RG_STRIPHELM:
					equip   = LOC_HEAD2;
					cp_scid = SC_CP_HELM;
					break;
				default:
					map_freeblock_unlock();
					return 1;
			}
			sc = status_get_sc(bl);
			if(sc && (sc->data[scid].timer != -1 || sc->data[cp_scid].timer != -1)) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			strip_fix = 2 * (status_get_dex(src) - status_get_dex(bl));

			if(atn_rand()%1000 > 50 + skilllv*50 + strip_fix)
				break;

			if(dstsd) {
				int i;
				if(equip == LOC_LARM) {
					// ストリップシールドは弓以外の両手武器には失敗
					if( dstsd->equip_index[EQUIP_INDEX_LARM] >= 0 &&
					    itemdb_isweapon(dstsd->inventory_data[dstsd->equip_index[EQUIP_INDEX_LARM]]->nameid) &&
					    dstsd->status.weapon != WT_BOW )
						break;
				}
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & equip)) {
						pc_unequipitem(dstsd,i,0);
						break;
					}
				}
				if(i >= MAX_INVENTORY && !md) {	// MOB -> PC は装備をしていなくても発動
					if(sd)
						clif_skill_fail(sd,skillid,0,0,0);
					break;
				}
			}
			if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));
			status_change_start(bl,scid,skilllv,0,0,0,strip_time,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ST_FULLSTRIP:		/* フルストリップ */
		{
			int strip_fix, rate, strip_time;
			int fail = 1;
			int skill_fix = 50 + 20 * skilllv;

			strip_fix = status_get_dex(src) - status_get_dex(bl);
			rate = skill_fix + 2 * strip_fix;

			if(rate < skill_fix)
				rate = skill_fix;
			if(atn_rand()%1000 >= rate)
				break;
			if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));

			sc = status_get_sc(bl);
			if(dstsd) {
				int i;

				status_calc_pc_stop_begin(&dstsd->bl);
				for(i=0; i<=MAX_INVENTORY; i++) {
					if( dstsd->status.inventory[i].equip & LOC_RARM &&
					    (!sc || (sc->data[SC_CP_WEAPON].timer == -1 && sc->data[SC_STRIPWEAPON].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
					if( dstsd->status.inventory[i].equip & LOC_LARM ) {
						// ストリップシールドは弓以外の両手武器には失敗
						if( dstsd->equip_index[EQUIP_INDEX_LARM] >= 0 &&
						    itemdb_isweapon(dstsd->inventory_data[dstsd->equip_index[EQUIP_INDEX_LARM]]->nameid) &&
						    dstsd->status.weapon != WT_BOW ) {
							;
						}
						else if( !sc || (sc->data[SC_CP_SHIELD].timer == -1 && sc->data[SC_STRIPSHIELD].timer == -1) ) {
							pc_unequipitem(dstsd,i,0);
							status_change_start(bl,SC_STRIPSHIELD,skilllv,0,0,0,strip_time,0);
							fail = 0;
						}
					}
					if( dstsd->status.inventory[i].equip & LOC_BODY &&
					    (!sc || (sc->data[SC_CP_ARMOR].timer == -1 && sc->data[SC_STRIPARMOR].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPARMOR,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
					if( dstsd->status.inventory[i].equip & LOC_HEAD2 &&
					    (!sc || (sc->data[SC_CP_HELM].timer == -1 && sc->data[SC_STRIPHELM].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
				}
				status_calc_pc_stop_end(&dstsd->bl);
			} else {
				if(!sc || (sc->data[SC_CP_WEAPON].timer == -1 && sc->data[SC_STRIPWEAPON].timer == -1)) {
					status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_SHIELD].timer == -1 && sc->data[SC_STRIPSHIELD].timer == -1)) {
					status_change_start(bl,SC_STRIPSHIELD,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_ARMOR].timer == -1 && sc->data[SC_STRIPARMOR].timer == -1)) {
					status_change_start(bl,SC_STRIPARMOR,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_HELM].timer == -1 && sc->data[SC_STRIPHELM].timer == -1)) {
					status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(fail && sd)
				clif_fullstrip_fail(sd);
		}
		break;
	case AM_POTIONPITCHER:		/* ポーションピッチャー */
		{
			struct block_list tbl;
			int hp = 0, sp = 0;
			if(sd) {
				int x = (skilllv > 10)? 9: skilllv - 1;
				int i = pc_search_inventory(sd,skill_db[skillid].itemid[x]);

				if(i < 0 || skill_db[skillid].itemid[x] <= 0) {
					clif_skill_fail(sd,skillid,0,0,0);
					map_freeblock_unlock();
					return 1;
				}
				if(sd->inventory_data[i] == NULL || sd->status.inventory[i].amount < skill_db[skillid].amount[x]) {
					clif_skill_fail(sd,skillid,0,0,0);
					map_freeblock_unlock();
					return 1;
				}
				sd->state.potionpitcher_flag = 1;
				memset(&sd->potion,0,sizeof(sd->potion));
				sd->ud.skilltarget = bl->id;
				if(sd->inventory_data[i]->use_script) {
					run_script(sd->inventory_data[i]->use_script,0,sd->bl.id,0);
				}
				pc_delitem(sd,i,skill_db[skillid].amount[x],0,1);
				sd->state.potionpitcher_flag = 0;
				if(sd->potion.hp_per > 0 || sd->potion.sp_per > 0) {
					hp = (int)((atn_bignumber)status_get_max_hp(bl) * sd->potion.hp_per / 100);
					hp = hp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
					if(dstsd) {
						sp = dstsd->status.max_sp * sd->potion.sp_per / 100;
						sp = sp * (100 + pc_checkskill(sd,AM_POTIONPITCHER) + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
					}
				} else {
					if(sd->potion.hp > 0) {
						hp = sd->potion.hp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
						hp = hp * (100 + (status_get_vit(bl)<<1)) / 100;
						if(dstsd)
							hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10) / 100;
					}
					if(sd->potion.sp > 0) {
						sp = sd->potion.sp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
						sp = sp * (100 + (status_get_int(bl)<<1)) / 100;
						if(dstsd)
							sp = sp * (100 + pc_checkskill(dstsd,MG_SRECOVERY)*10) / 100;
					}
				}
				if(sd->sc.data[SC_ALCHEMIST].timer != -1) {
					hp = hp * (100 + sd->status.base_level) / 100;
					sp = sp * (100 + sd->status.base_level) / 100;
				}
			} else {
				hp = (1 + atn_rand()%400) * (100 + skilllv*10) / 100;
				hp = hp * (100 + (status_get_vit(bl)<<1)) / 100;
				if(dstsd)
					hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10) / 100;
			}
			hp = skill_fix_heal(src, bl, skillid, hp);

			memset(&tbl, 0, sizeof(tbl));
			tbl.m = src->m;
			tbl.x = src->x;
			tbl.y = src->y;
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_BERSERK].timer != -1)
				hp = sp = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(hp > 0 || (hp <= 0 && sp <= 0))
				clif_skill_nodamage(&tbl,bl,AL_HEAL,hp,1);
			if(sp > 0)
				clif_skill_nodamage(&tbl,bl,MG_SRECOVERY,sp,1);
			battle_heal(src,bl,hp,sp,0);
		}
		break;

	case CR_SLIMPITCHER:	/* スリムポーションピッチャー */
		if(sd && flag&1) {
			struct block_list tbl;
			int hp = sd->potion.hp * (100 + pc_checkskill(sd,CR_SLIMPITCHER)*10 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
			hp = hp * (100 + (status_get_vit(bl)<<1))/100;
			if(dstsd) {
				hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10)/100;
			}
			hp = skill_fix_heal(&sd->bl, bl, skillid, hp);
			memset(&tbl, 0, sizeof(tbl));
			tbl.m = src->m;
			tbl.x = src->x;
			tbl.y = src->y;
			clif_skill_nodamage(&tbl,bl,AL_HEAL,hp,1);
			battle_heal(NULL,bl,hp,0,0);
		}
		break;

	case AM_BERSERKPITCHER:		/* バーサークピッチャー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,SC_SPEEDPOTION2,1,0,0,0,900000,0);
		break;
	case AM_CP_WEAPON:
	case AM_CP_SHIELD:
	case AM_CP_ARMOR:
	case AM_CP_HELM:
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1)
				status_change_end(bl, type, -1);
			status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case CR_FULLPROTECTION:			/* フルケミカルチャージ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc) {
			if(sc->data[SC_STRIPWEAPON].timer != -1)
				status_change_end(bl, SC_STRIPWEAPON, -1);
			if(sc->data[SC_STRIPSHIELD].timer != -1)
				status_change_end(bl, SC_STRIPSHIELD, -1);
			if(sc->data[SC_STRIPARMOR].timer != -1)
				status_change_end(bl, SC_STRIPARMOR, -1);
			if(sc->data[SC_STRIPHELM].timer != -1)
				status_change_end(bl, SC_STRIPHELM, -1);
		}
		status_change_start(bl,SC_CP_WEAPON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_SHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_ARMOR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_HELM,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	case SA_DISPELL:			/* ディスペル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		// ソウルリンカーは無効
		if(dstsd && dstsd->status.class_ == PC_CLASS_SL)
			break;
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_ROGUE].timer != -1)	// ローグの魂中は無効
			break;
		if(atn_rand()%100 >= skilllv*10+50)
			break;
		status_change_release(bl,0x02);	// ディスペルによるステータス異常解除
		break;

	case TF_BACKSLIDING:		/* バックステップ */
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// 方向を保存しておいて、吹き飛ばし後に戻す
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);
			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
			if(sc && sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(bl,SC_CLOSECONFINE,-1);
		}
		break;

	case SA_CASTCANCEL:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_skillcastcancel(src,1);
		if(sd) {
			int sp = skill_get_sp(sd->skill_used.id,sd->skill_used.lv) * (110 - 20 * skilllv) / 100;
			if(sp > 0)
				pc_heal(sd,0,-sp);
		}
		break;
	case SA_SPELLBREAKER:	/* スペルブレイカー */
		if(sd && status_get_mode(bl)&MD_BOSS && atn_rand()%100 < 90) {
			clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_MAGICROD].timer != -1) {
			int sp;
			if(dstsd) {
				sp = skill_get_sp(skillid,skilllv) * sc->data[SC_MAGICROD].val2 / 100; 
				if(sp > 0x7fff) sp = 0x7fff;
				else if(sp < 1) sp = 1;
				if(dstsd->status.sp + sp > dstsd->status.max_sp) {
					sp = dstsd->status.max_sp - dstsd->status.sp;
					dstsd->status.sp = dstsd->status.max_sp;
				} else {
					dstsd->status.sp += sp;
				}
				clif_heal(dstsd->fd,SP_SP,sp);
			}
			clif_skill_nodamage(bl,bl,SA_MAGICROD,sc->data[SC_MAGICROD].val1,1);
			if(sd) {
				sp = sd->status.max_sp/5;
				if(sp < 1) sp = 1;
				pc_heal(sd,0,-sp);
			}
		} else {
			struct unit_data *ud = unit_bl2ud(bl);
			if(ud && ud->skilltimer != -1 && ud->skillid > 0 && skill_get_skill_type(ud->skillid) == BF_MAGIC) {
				int sp = skill_get_sp(ud->skillid,ud->skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				unit_skillcastcancel(bl,0);
				if(dstsd)
					pc_heal(dstsd,0,-sp);
				if(sd) {
					sp = sp * 25 * (skilllv - 1) / 100;
					if(skilllv > 1 && sp < 1) sp = 1;
					if(sp > 0x7fff) sp = 0x7fff;
					else if(sp < 1) sp = 1;
					if(sd->status.sp + sp > sd->status.max_sp) {
						sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					} else {
						sd->status.sp += sp;
					}
					clif_heal(sd->fd,SP_SP,sp);
				}
			} else if(sd) {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case SA_MAGICROD:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SA_AUTOSPELL:			/* オートスペル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			clif_autospell(sd,skilllv);
		} else {
			int maxlv = 1, spellid = 0;
			if(skilllv >= 10) {
				spellid = MG_FROSTDIVER;
				maxlv = skilllv - 9;
			}
			else if(skilllv >= 8) {
				spellid = MG_FIREBALL;
				maxlv = skilllv - 7;
			}
			else if(skilllv >= 5) {
				spellid = MG_SOULSTRIKE;
				maxlv = skilllv - 4;
			}
			else if(skilllv >= 2) {
				int r = atn_rand()%3;
				if(r == 0)
					spellid = MG_COLDBOLT;
				else if(r == 1)
					spellid = MG_FIREBOLT;
				else
					spellid = MG_LIGHTNINGBOLT;
				maxlv = skilllv - 1;
			}
			else if(skilllv > 0) {
				spellid = MG_NAPALMBEAT;
				maxlv = 3;
			}
			if(spellid > 0)
				status_change_start(src,SC_AUTOSPELL,skilllv,spellid,maxlv,0,skill_get_time(SA_AUTOSPELL,skilllv),0);
		}
		break;
	case PF_MINDBREAKER:
		if(atn_rand()%100 < 55 + skilllv * 5) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);

			// 凍結・石化・睡眠を解除
			status_change_attacked_end(bl);

			if(dstmd) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			}
			unit_skillcastcancel(bl,2);	// 詠唱妨害
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case PF_SOULCHANGE:		/* ソウルチェンジ */
		if(sd && dstsd) {
			int sp;
			// PVP,GVG以外ではPTメンバーにのみ使用可
			if(!map[src->m].flag.pvp && !map[src->m].flag.gvg && battle_check_target(src,bl,BCT_PARTY) <= 0)
				break;
			// 対象がバーサーク中でない場合のみ使用可
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sp = sd->status.sp - dstsd->status.sp;
#ifndef PRE_RENEWAL
			sp = sp / 2;
#endif
			pc_heal(sd,0,-sp);
			pc_heal(dstsd,0,sp);
		}
		break;
	case NPC_ATTRICHANGE:	/* ランダム属性変化 */
		if(md) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			md->def_ele = atn_rand()%ELE_MAX;
			if(md->def_ele == ELE_UNDEAD)		// 不死は除く
				md->def_ele = ELE_NEUTRAL;
			md->def_ele += (1 + atn_rand()%4) * 20;	// 属性レベルはランダム
		} else if(sd) {
			static int armor_element[9]={
				SC_ELEMENTWATER,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,SC_ELEMENTPOISON,
				SC_ELEMENTHOLY,SC_ELEMENTDARK,SC_ELEMENTELEKINESIS,SC_ELEMENTUNDEAD
			};
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,armor_element[atn_rand()%9],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case NPC_CHANGEWATER:
	case NPC_CHANGEGROUND:
	case NPC_CHANGEFIRE:
	case NPC_CHANGEWIND:
	case NPC_CHANGEPOISON:
	case NPC_CHANGEHOLY:
	case NPC_CHANGETELEKINESIS:
	case NPC_CHANGEDARKNESS:
	case NPC_CHANGEUNDEAD2:
		if(md) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			md->def_ele = skill_get_pl(skillid);
			md->def_ele += (1 + atn_rand()%4) * 20;	// 属性レベルはランダム
		} else if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_PROVOCATION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(md && md->skillidx != -1)
			clif_pet_performance(src,mob_db[md->class_].skill[md->skillidx].val[0]);
		break;

	case NPC_SMOKING:			/* 喫煙 */
		clif_damage(src,src,tick,status_get_amotion(src),status_get_dmotion(src),3,1,0,0,0);
		break;

	case NPC_HALLUCINATION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	case NPC_KEEPING:
	case NPC_BARRIER:
		{
			struct unit_data *ud = unit_bl2ud(src);
			int skill_time = skill_get_time(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_time,0);
			if(ud)
				ud->canmove_tick = tick + skill_time;
		}
		break;

	case NPC_DARKBLESSING:
		{
			int sc_def = 100 - status_get_mdef(bl);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd && dstsd->special_state.no_magic_damage)
				break;
			if(status_get_elem_type(bl) == ELE_DARK || status_get_race(bl) == RCT_DEMON)
				break;
			if(atn_rand()%100 < sc_def * (50 + skilllv * 5) / 100) {
				if(dstsd) {
					int hp = status_get_hp(bl) - 1;
					pc_heal(dstsd,-hp,0);
				}
				else if(dstmd) {
					dstmd->hp = 1;
				}
			}
		}
		break;

	case NPC_LICK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_weapon_damage )
			break;
		if(dstsd)
			pc_heal(dstsd,0,-100);
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case NPC_SUICIDE:			/* 自決 */
		if(md) {
			md->state.noexp  = 1;
			md->state.nodrop = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			mob_damage(NULL,md,md->hp,3);
		}
		break;

	case NPC_SUMMONSLAVE:		/* 手下召喚 */
	case NPC_SUMMONMONSTER:		/* MOB召喚 */
	case NPC_DEATHSUMMON:		/* デスサモン */
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mob_db[md->class_].skill[md->skillidx];
			mob_summonslave(md,ms->val,sizeof(ms->val)/sizeof(ms->val[0]),skilllv,(skillid == NPC_SUMMONSLAVE)? 1: 0);
		}
		break;
	case NPC_CALLSLAVE:		/* 取り巻き呼び戻し */
		if(md) {
			int mobcount;
			md->recallcount       = 0;	// 初期化
			md->state.recall_flag = 0;
			mobcount = mob_countslave(md);
			if(mobcount > 0) {
				md->state.recall_flag = 1;	// mob.cの[取り巻きモンスターの処理]で利用
				md->recallmob_count   = mobcount;
			}
		}
		break;
	case NPC_REBIRTH:
		if(md && !md->state.rebirth) {
			// 1度もリバースを使ってない場合のみ発動
			status_change_start(src,SC_REBIRTH,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_RUN:		/* 後退 */
		if(md) {
			int dx = dirx[md->dir] * skilllv;
			int dy = diry[md->dir] * skilllv;
			mob_unlocktarget(md,tick);
			unit_walktoxy(&md->bl,md->bl.x-dx,md->bl.y-dy);	// 自分の向いている方向と逆向きに移動
		}
		break;

	case NPC_TRANSFORMATION:
	case NPC_METAMORPHOSIS:
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mob_db[md->class_].skill[md->skillidx];
			int size = sizeof(ms->val)/sizeof(ms->val[0]);
			if(skilllv > 1)
				mob_summonslave(md,ms->val,size,skilllv-1,0);
			mob_class_change(md,ms->val,size);
		}
		break;

	case NPC_EMOTION:			/* エモーション */
	case NPC_EMOTION_ON:			/* モードチェンジ */
		if(md && md->skillidx != -1) {
			clif_emotion(&md->bl,mob_db[md->class_].skill[md->skillidx].val[0]);
			if(mob_db[md->class_].skill[md->skillidx].val[1]) {	// モードチェンジ
				md->mode = mob_db[md->class_].skill[md->skillidx].val[1];
				unit_stop_walking(&md->bl,1);
				unit_stopattack(&md->bl);
				mob_unlocktarget(md, tick);
			}
			status_change_end(src,SC_MODECHANGE,-1);
			if(skillid == NPC_EMOTION_ON)
				status_change_start(src,SC_MODECHANGE,skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case WE_MALE:				/* 君だけは護るよ */
		if(sd && dstsd) {
			int hp_rate = (skilllv <= 0)? 0: skill_db[skillid].hp_rate[skilllv-1];
			int gain_hp;
			if(battle_config.new_marrige_skill)
				gain_hp = dstsd->status.max_hp;
			else
				gain_hp = sd->status.max_hp;
			gain_hp = gain_hp * abs(hp_rate) / 100;
			gain_hp = skill_fix_heal(&sd->bl, &dstsd->bl, skillid, gain_hp);
			clif_skill_nodamage(src,bl,skillid,gain_hp,1);
			battle_heal(NULL,bl,gain_hp,0,0);
		}
		break;
	case WE_FEMALE:				/* あなたに尽くします */
		if(sd && dstsd) {
			int sp_rate = (skilllv <= 0)? 0: skill_db[skillid].sp_rate[skilllv-1];
			int gain_sp;
			// バーサーク中の対象には無効
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			if(battle_config.new_marrige_skill)
				gain_sp = dstsd->status.max_sp;
			else
				gain_sp = sd->status.max_sp;
			gain_sp = gain_sp * abs(sp_rate) / 100;
			clif_skill_nodamage(src,bl,skillid,gain_sp,1);
			battle_heal(NULL,bl,0,gain_sp,0);

			// スパノビの嫁が旦那に使用すると10%の確率でステータス付与
			if((sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) && sd->sex == SEX_FEMALE && atn_rand()%100 < 10) {
				int sec = skill_get_time2(skillid,skilllv);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,0,sec,0);
				status_change_start(&dstsd->bl,GetSkillStatusChangeTable(skillid),skilllv,2,0,0,sec,0);
			}
		}
		break;

	case WE_CALLPARTNER:			/* あなたに逢いたい */
	case WE_CALLPARENT:			/* ママ、パパ、来て */
	case WE_CALLBABY:			/* 坊や、いらっしゃい */
		if(sd) {
			int i, d, x, y;
			if(map[sd->bl.m].flag.nomemo) {
				clif_skill_teleportmessage(sd,1);
				map_freeblock_unlock();
				return 0;
			}
			if(skillid == WE_CALLPARTNER)
				clif_callpartner(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			if(battle_config.pc_land_skill_limit) {
				int maxcount = skill_get_maxcount(sd->ud.skillid,sd->ud.skilllv);
				if(maxcount > 0) {
					if(skill_count_unitgroup(&sd->ud, sd->ud.skillid) >= maxcount) {
						clif_skill_fail(sd,sd->ud.skillid,0,0,0);
						sd->ud.canact_tick  = tick;
						sd->ud.canmove_tick = tick;
						map_freeblock_unlock();
						return 0;
					}
				}
			}
			// 目の前に呼び出す
			for(i = 0; i < 8; i++) {
				if(i&1)
					d = (sd->dir - ((i+1)>>1)) & 7;
				else
					d = (sd->dir + ((i+1)>>1)) & 7;

				x = sd->bl.x + dirx[d];
				y = sd->bl.y + diry[d];
				if(map_getcell(sd->bl.m,x,y,CELL_CHKPASS))
					break;
			}
			if(i >= 8) {
				x = sd->bl.x;
				y = sd->bl.y;
			}
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case PF_HPCONVERSION:			/* 生命力変換 */
		if(sd) {
			if(sd->status.hp <= sd->status.max_hp / 10) {
				clif_skill_fail(sd,skillid,0,0,0);
			} else {
				int conv_hp = 0, conv_sp = 0;
				clif_skill_nodamage(src, bl, skillid, skilllv, 1);
				conv_hp = sd->status.max_hp / 10; // 基本はMAXHPの10%
				conv_sp = conv_hp * 10 * skilllv / 100;
				if(sd->status.sp + conv_sp > sd->status.max_sp)
					conv_sp = sd->status.max_sp - sd->status.sp;
				pc_heal(sd, -conv_hp, conv_sp);
				clif_heal(sd->fd, SP_SP, conv_sp);
				clif_updatestatus(sd, SP_SP);
			}
		}
		break;
	case HT_REMOVETRAP:				/* リムーブトラップ */
	case MA_REMOVETRAP:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(bl->type == BL_SKILL) {
			struct skill_unit *su = (struct skill_unit *)bl;
			if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
				break;
			if(su->group->src_id != src->id && !map[bl->m].flag.pvp && !map[bl->m].flag.gvg)
				break;
			if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2) {
				struct block_list *target = map_id2bl(su->group->val2);
				if(target && target->type == BL_PC)
					status_change_end(target,SC_ANKLE,-1);
			} else if(sd && itemdb_exists(su->group->val3)) {
				// 罠を取り返す
				struct item item_tmp;
				int eflag;
				if(battle_config.skill_removetrap_type == 1) {
					int i;
					for(i=0; i<10; i++) {
						if(skill_db[su->group->skill_id].itemid[i] <= 0)
							continue;
						memset(&item_tmp,0,sizeof(item_tmp));
						// 設置用トラップの代わりに改良型設置用トラップを消費していた場合
						if(skill_db[su->group->skill_id].itemid[i] == 1065 && su->group->val3 == 7940) {
							item_tmp.nameid = 7940;
							item_tmp.amount = 1;
						} else {
							item_tmp.nameid = skill_db[su->group->skill_id].itemid[i];
							item_tmp.amount = skill_db[su->group->skill_id].amount[i];
						}
						item_tmp.identify = 1;
						if((eflag = pc_additem(sd,&item_tmp,item_tmp.amount))) {
							clif_additem(sd,0,0,eflag);
							map_addflooritem(&item_tmp,item_tmp.amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
						}
					}
				} else {
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid   = su->group->val3;
					item_tmp.identify = 1;
					if((eflag = pc_additem(sd,&item_tmp,1))) {
						clif_additem(sd,0,0,eflag);
						map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
					}
				}

			}
			skill_delunit(su);
		}
		break;
	case HT_SPRINGTRAP:				/* スプリングトラップ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(bl->type == BL_SKILL) {
			struct skill_unit *su = (struct skill_unit *)bl;
			if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
				break;
			if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2 > 0)		// 補足中は破壊不可
				break;
			su->group->unit_id = UNT_USED_TRAPS;
			clif_changelook(bl,LOOK_BASE,su->group->unit_id);
			su->group->limit = su->limit = DIFF_TICK(tick+1500,su->group->tick);
		}
		break;
	case BD_ENCORE:					/* アンコール */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			unit_skilluse_id(&sd->bl,src->id,sd->skill_dance.id,sd->skill_dance.lv);
		break;
	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(
#ifdef PRE_RENEWAL
			(atn_bignumber)status_get_max_hp(bl)*3/4 < status_get_hp(bl) ||
#endif
			status_get_mode(bl)&MD_BOSS) {
			// HPが3/4以上残っているか相手がボス属性なら失敗
			clif_skill_fail(sd,skillid,0,0,0);
			map_freeblock_unlock();
			return 1;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case ASC_EDP:			/* エンチャントデッドリーポイズン */
		{
			int time = skill_get_time(skillid,skilllv);
			if(sd)
				time += pc_checkskill(sd,GC_RESEARCHNEWPOISON) * 3000;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,time,0);
#ifndef PRE_RENEWAL
			// pre時の計算式が不明のためRE限定
			status_change_start(bl,SC_MAGNUM,skilllv,ELE_POISON,0,0,time,0);
#endif
		}
		break;
	case RG_CLOSECONFINE:		/* クローズコンファイン */
		{
			int dir;
			if(status_get_mode(bl)&MD_BOSS) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,1,src->id,bl->id,skill_get_time(skillid,skilllv),0);

			dir = path_calc_dir(src,bl->x,bl->y);
			//unit_setdir(src,dir);
			unit_movepos(bl,src->x+dirx[dir],src->y+diry[dir],0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),1,2,bl->id,src->id,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_STOP:			/* ホールドウェブ */
		status_change_start(src,GetSkillStatusChangeTable(skillid),1,1,src->id,bl->id,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),1,2,bl->id,src->id,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_REDEMPTIO:		/* レデムプティオ */
		if(sd == NULL)
			break;
		if(flag&1) {
			if(unit_isdead(bl)) {
				skill_area_temp[0]++;
				skill_castend_nodamage_id(src,bl,ALL_RESURRECTION,3,tick,1);
			}
		} else {
			skill_area_temp[0] = 0;
			party_foreachsamemap(skill_area_sub,
				sd,AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);

			if(!battle_config.redemptio_penalty_type)
				break;
			if(battle_config.redemptio_penalty_type&1 && skill_area_temp[0] == 0)
				break;
			if(battle_config.redemptio_penalty_type&2 && skill_area_temp[0] >= 5)
				break;

			// HP1, SP0
			pc_heal(sd, -sd->status.hp + 1, -sd->status.sp);

			// 経験値ペナルティ
			if(skill_area_temp[0] < 5) {
				int per = (5 - skill_area_temp[0]) * 20;
				pc_exp_penalty(sd, NULL, per, 3);
			}
		}
		break;

	case MO_KITRANSLATION:		/* 気功転移 */
		if(dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),1);
		}
		break;
	case BS_GREED:			/* グリード */
		if (sd && (battle_config.greed_use_town || !map[src->m].flag.town) && !map[src->m].flag.pvp && !map[src->m].flag.gvg) {	// 街・PvP・GvGでは使用不可
			struct party *p = NULL;
			if(sd->status.party_id > 0)
				p = party_search(sd->status.party_id);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_greed,sd->bl.m,sd->bl.x-2,sd->bl.y-2,sd->bl.x+2,sd->bl.y+2,BL_ITEM,sd,p);
		}
		break;

	case GD_BATTLEORDER:		/* 臨戦態勢 */
	case GD_REGENERATION:		/* 激励 */
	case GD_RESTORE:		/* 治療 */
		if(sd) {
			int mi, range;
			struct guild *g = guild_search(sd->status.guild_id);

			if(g == NULL)
				break;
			range = skill_get_range(skillid,skilllv);
			for(mi = 0; mi < g->max_member; mi++)
			{
				struct map_session_data *member = g->member[mi].sd;
				if(member == NULL)
					continue;
				if(sd->bl.m != member->bl.m)
					continue;
				if(path_distance(sd->bl.x,sd->bl.y,member->bl.x,member->bl.y) <= range) {
					clif_skill_nodamage(src,&member->bl,skillid,skilllv,1);
					if(skillid == GD_RESTORE) {
						// バーサーク中のメンバーには使用不可
						if(member->sc.data[SC_BERSERK].timer != -1)
							continue;
						pc_heal(member, member->status.max_hp * 90 / 100, member->status.max_sp * 90 / 100);
					} else {
						status_change_start(&member->bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
					}
				}
			}
			if(skillid == GD_BATTLEORDER)
				status_change_start(&sd->bl,SC_BATTLEORDER_DELAY,0,0,0,0,300000,0);
			else if(skillid == GD_REGENERATION)
				status_change_start(&sd->bl,SC_REGENERATION_DELAY,0,0,0,0,300000,0);
			else
				status_change_start(&sd->bl,SC_RESTORE_DELAY,0,0,0,0,300000,0);
		}
		break;
	case GD_EMERGENCYCALL:		/* 緊急招集 */
		if(sd) {
			int mi, px, py, count = 0;
			struct guild *g = guild_search(sd->status.guild_id);
			struct cell_xy free_cell[7*7];

			if(g == NULL)
				break;
			clif_skill_nodamage(src,src,skillid,skilllv,1);

			if(battle_config.emergencycall_point_type != 0)
				count = map_searchfreecell(free_cell,sd->bl.m,sd->bl.x-3,sd->bl.y-3,sd->bl.x+3,sd->bl.y+3);

			for(mi = 0; mi < g->max_member; mi++)
			{
				struct map_session_data *member = g->member[mi].sd;
				if(member == NULL)
					continue;
				if(member->bl.id == sd->bl.id)	// 自分自身は除外
					continue;
				if(battle_config.emergencycall_call_limit && sd->bl.m != member->bl.m)	// 同マップのみ
					continue;
				if(member->state.refuse_emergencycall)
					continue;

				if(count <= 0) {
					// 足元
					px = sd->bl.x;
					py = sd->bl.y;
				} else {
					int idx = atn_rand()%count;
					px = free_cell[idx].x;
					py = free_cell[idx].y;
					if(battle_config.emergencycall_point_type == 2 &&
					   path_search(NULL,sd->bl.m,sd->bl.x,sd->bl.y,px,py,0))
					{
						// 崖越えEMC禁止
						mi--;
						count--;
						free_cell[idx] = free_cell[count];
						continue;
					}
				}
				pc_setpos(member,map[sd->bl.m].name,px,py,3);
			}
			status_change_start(&sd->bl,SC_EMERGENCYCALL_DELAY,0,0,0,0,300000,0);
		}
		break;

	case SG_FEEL:
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(!sd->status.feel_map[skilllv-1][0])
				clif_feel_display(sd,skilllv);
			else
				clif_feel_info(sd,skilllv);
		}
		break;
	case SG_HATE:
		if(sd && skilllv > 0 && skilllv <= 3) {
			// 既に登録済み
			if(sd->hate_mob[skilllv-1] != -1) {
				clif_hate_info(sd,skilllv,sd->hate_mob[skilllv-1]);
				break;
			}
			if(dstsd) {	// 登録相手がPC
				sd->hate_mob[skilllv-1] = dstsd->status.class_;
				if(battle_config.save_hate_mob)
					pc_setglobalreg(sd,"PC_HATE_MOB_STAR",sd->hate_mob[skilllv-1]+1);
				clif_skill_nodamage(src,src,skillid,skilllv,1);
				clif_hate_mob(sd,skilllv,sd->hate_mob[skilllv-1]);
			} else if(dstmd) {	// 登録相手がMOB
				switch(skilllv) {
				case 1:
					if(status_get_size(bl) == 0) {
						sd->hate_mob[0] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_SUN", sd->hate_mob[0]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[0]);
					} else {
						clif_skill_fail(sd,skillid,0,0,0);
					}
					break;
				case 2:
					if(status_get_size(bl) == 1 && status_get_max_hp(bl) >= 6000) {
						sd->hate_mob[1] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_MOON", sd->hate_mob[1]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[1]);
					} else {
						clif_skill_fail(sd,skillid,0,0,0);
					}
					break;
				case 3:
					if(status_get_size(bl) == 2 && status_get_max_hp(bl) >= 20000) {
						sd->hate_mob[2] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_STAR", sd->hate_mob[2]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[2]);
					} else {
						clif_skill_fail(sd,skillid,0,0,0);
					}
					break;
				default:
					clif_skill_fail(sd,skillid,0,0,0);
					break;
				}
			}
		}
		break;
	case SG_FUSION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl,SC_STAR,-1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SL_ALCHEMIST:		/* アルケミストの魂 */
	case SL_MONK:			/* モンクの魂 */
	case SL_STAR:			/* ケンセイの魂 */
	case SL_SAGE:			/* セージの魂 */
	case SL_CRUSADER:		/* クルセイダーの魂 */
	case SL_KNIGHT:			/* ナイトの魂 */
	case SL_WIZARD:			/* ウィザードの魂 */
	case SL_PRIEST:			/* プリーストの魂 */
	case SL_SUPERNOVICE:		/* スーパーノービスの魂 */
	case SL_BARDDANCER:		/* バードとダンサーの魂 */
	case SL_ROGUE:			/* ローグの魂 */
	case SL_ASSASIN:		/* アサシンの魂 */
	case SL_BLACKSMITH:		/* ブラックスミスの魂 */
	case SL_HUNTER:			/* ハンターの魂 */
	case SL_SOULLINKER:		/* ソウルリンカーの魂 */
	case SL_DEATHKNIGHT:		/* デスナイトの魂 */
	case SL_COLLECTOR:		/* ダークコレクターの魂 */
	case SL_NINJA:			/* 忍者の魂 */
	case SL_GUNNER:			/* ガンスリンガーの魂 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SL_HIGH:			/* 転生一次職業の魂 */
		if(status_get_lv(bl) < 11 || status_get_lv(bl) > 70) {   // 対象のベースレベルが11以下、または70以上だと使用不可
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_MADNESSCANCEL:		/* マッドネスキャンセラー */
		sc = status_get_sc(bl);
		if(!sc || sc->data[SC_ADJUSTMENT].timer == -1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case GS_ADJUSTMENT:			/* アジャストメント */
		sc = status_get_sc(bl);
		if(!sc || sc->data[SC_MADNESSCANCEL].timer == -1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case GS_CRACKER:			/* クラッカー */
		{
			int cost = skill_get_arrow_cost(skillid,skilllv);
			int rate;
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			rate = 5000 - (unit_distance(src,bl) / 3) * 1000;
			if(rate < 2000)
				rate = 2000;

			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,rate,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case NJ_BUNSINJYUTSU:		/* 影分身 */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_NEN].timer != -1)
			status_change_end(bl,SC_NEN,-1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case ALL_BUYING_STORE:			/* 買取露店開設 */
		if(sd) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,83,0,0);
				return 1;
			}
			buyingstore_openstorewindow(sd, MAX_BUYINGSTORE_COUNT);
		}
		break;
	case ALL_WEWISH:			/* ホーリーナイト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case RETURN_TO_ELDICASTES:		/* エルディカスティスへの帰還 */
	case ALL_GUARDIAN_RECALL:		/* モーラへの帰還 */
	case ECLAGE_RECALL:		/* エクラージュへの帰還 */
		if(sd) {
			int x, y;
			const char *mapname;

			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportalで禁止
					break;
			}
			if(skillid == RETURN_TO_ELDICASTES) {
				x = 198;
				y = 187;
				mapname = "dicastes01.gat";
			} else if(skillid == ALL_GUARDIAN_RECALL) {
				x = 44;
				y = 151;
				mapname = "mora.gat";
			} else {
				x = 47;
				y = 31;
				mapname = "ecl_in01.gat";
			}

			if(pc_setpos(sd,mapname,x,y,0)) {
				// マップが存在しなかった
				clif_skill_fail(sd,skillid,0,0,0);
				map_freeblock_unlock();
				return 0;
			}
		}
		break;
	case HAMI_CASTLE:		/* キャスリング */
		if(hd && hd->msd && atn_rand()%100 < 20*skilllv)
		{
			int x, y;
			struct map_session_data *msd = hd->msd;
			if( path_search(NULL,hd->bl.m,hd->bl.x,hd->bl.y,msd->bl.x,msd->bl.y,0) != 0 ) {
				// キャスリングを用いた壁越え禁止
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			clif_skill_nodamage(&hd->bl,&msd->bl,skillid,skilllv,1);

			x = hd->bl.x;
			y = hd->bl.y;

			unit_movepos(&hd->bl,msd->bl.x,msd->bl.y,0);
			unit_movepos(&msd->bl,x,y,0);

			map_foreachinarea(skill_castle_mob_changetarget,hd->bl.m,
				hd->bl.x-AREA_SIZE,hd->bl.y-AREA_SIZE,
				hd->bl.x+AREA_SIZE,hd->bl.y+AREA_SIZE,
				BL_MOB,&msd->bl,&hd->bl);
		}
		break;
	case HVAN_CHAOTIC:		/* カオティックベネディクション */
		if(hd) {
			struct block_list* heal_target = NULL;
			int n = (skilllv < 5)? skilllv - 1: 4;
			int rnd = atn_rand()%100;
			static const int per[5][2] = {
				{20,50},{50,60},{25,75},{60,64},{34,67}
			};

			if(rnd < per[n][0]) {
				// ホム
				heal_target = &hd->bl;
			} else if(rnd < per[n][1]) {
				// 主人
				if(!unit_isdead(&hd->msd->bl))	// 生存
					heal_target = &hd->msd->bl;
				else
					heal_target = &hd->bl;
			} else {
				// MOB
				heal_target = map_id2bl(hd->target_id);
				if(heal_target == NULL)
					heal_target = &hd->bl;
			}
			if(heal_target) {
				int val  = (skilllv > 0)? skill_calc_heal(src, 1+atn_rand()%skilllv) : 0;
				int heal = skill_fix_heal(&hd->bl, heal_target, skillid, val);
				// エフェクト出ないのでヒール
				clif_skill_nodamage(src,heal_target,AL_HEAL,heal,1);
				clif_skill_nodamage(src,heal_target,skillid,heal,1);
				battle_heal(NULL,heal_target,heal,0,0);
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
			}
		}
		break;
	case HLIF_AVOID:		/* 緊急回避 */
	case HAMI_DEFENCE:		/* ディフェンス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			// 主人にも
			if(hd->msd && !unit_isdead(&hd->msd->bl)) {
				clif_skill_nodamage(src,&hd->msd->bl,skillid,skilllv,1);
				status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HAMI_BLOODLUST:		/* ブラッドラスト */
	case HFLI_FLEET:		/* フリートムーブ */
	case HFLI_SPEED:		/* オーバードスピード */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HLIF_CHANGE:		/* メンタルチェンジ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		unit_heal(src,status_get_max_hp(src),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case NPC_DRAGONFEAR:		/* ドラゴンフィアー */
	case NPC_WIDESILENCE:		/* 範囲沈黙攻撃 */
	case NPC_WIDEFREEZE:		/* 範囲凍結攻撃 */
	case NPC_WIDEBLEEDING:		/* 範囲出血攻撃 */
	case NPC_WIDESTONE:		/* 範囲石化攻撃 */
	case NPC_WIDECONFUSE:		/* 範囲混乱攻撃 */
	case NPC_WIDESLEEP:		/* 範囲睡眠攻撃 */
	case NPC_WIDECURSE:		/* 範囲呪い攻撃 */
	case NPC_WIDESTUN:		/* 範囲スタン攻撃 */
	case NPC_WIDEHELLDIGNITY:	/* ヘルディグニティ */
		if(flag&1) {
			if(skillid == NPC_DRAGONFEAR) {
				const int sc_type[4] = { SC_STUN, SC_CONFUSION, SC_SILENCE, SC_BLEED };
				int n = atn_rand() % 4;
				// upkeep_time2は配列の添え字に従う
				if(atn_rand() % 10000 < status_change_rate(bl,sc_type[n],10000,status_get_lv(src)))
					status_change_pretimer(bl,sc_type[n],skilllv,0,0,0,skill_get_time2(skillid,n+1),0,tick+status_get_amotion(src));
			} else {
				if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skilllv * 3 - 1;
			//clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESIGHT:		/* ワイドサイト */
		clif_skill_nodamage(src,bl,MG_SIGHT,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_SLOWCAST:		/* スロウキャスト */
		if(flag&1) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		} else {
			int ar = skilllv * 3 - 1;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESOULDRAIN:	/* マナバーン */
		if(flag&1) {
			if(dstsd) {
				int sp = dstsd->status.max_sp * (((skilllv - 1) % 5 + 1) * 20) / 100;
				if(sp < 1) sp = 1;
				pc_heal(dstsd,0,-sp);
			}
		} else {
			int ar = (skilllv > 5)? 13: (skilllv * 2) + 3;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_TALK:			/* トーク */
		if(md && md->skillidx != -1) {
			mob_talk(md,mob_db[md->class_].skill[md->skillidx].val[0]);
		}
		break;
	case NPC_INVINCIBLE:		/* インビンシブル */
		status_change_end(bl, SC_INVINCIBLEOFF, -1);
	case NPC_INVINCIBLEOFF:		/* インビンシブルオフ */
	case MER_INVINCIBLEOFF2:	/* マインドブラスター */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_PULSESTRIKE2:		/* パルスストライクII */
		{
			int i;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i = 0; i < 3; i++) {
				skill_addtimerskill(src,tick + 1000 * i,bl->id,0,0,skillid,skilllv,0,0x0500);
			}
		}
		break;
	case MER_REGAIN:		/* リゲイン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_SLEEP, -1);
		break;
	case MER_TENDER:		/* テンダー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		break;
	case MER_BENEDICTION:		/* ベネディクション */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		break;
	case MER_RECUPERATE:		/* リキュポレイト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_POISON, -1);
		break;
	case MER_MENTALCURE:		/* メンタルキュア */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		break;
	case MER_COMPRESS:		/* コンプレス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_BLEED, -1);
		break;
	case MER_SCAPEGOAT:		/* 身代わり */
		if(mcd && mcd->msd) {
			int hp = status_get_hp(&mcd->bl);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_heal(mcd->msd,hp,0);
			battle_damage(NULL,&mcd->bl,hp,skillid,skilllv,flag);
		}
		break;
	case RK_ENCHANTBLADE:		/* エンチャントブレイド */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,status_get_int(src),0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_DRAGONHOWLING:	/* ドラゴンハウリング */
		if(flag&1) {
			if(atn_rand() % 100 < 50 + skilllv * 6)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 2 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case RK_STONEHARDSKIN:		/* ストーンハードスキン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),((sd)? sd->status.job_level: 0),0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_REFRESH:			/* リフレッシュ */
		{
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 25 / 100);
			battle_heal(NULL,bl,heal,0,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x08);		// 暫定でゴスペル全状態異常無効と同効果
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_FIGHTINGSPIRIT:		/* ファイティングスピリット */
		if(flag&1) {
			if(src != bl && skill_area_temp[0])
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7/4,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			skill_area_temp[0] = 0;
			if(sd && sd->status.party_id > 0) {
				skill_area_temp[0] = party_check_same_map_member_count(sd);
				/* パーティ全体への処理 */
				party_foreachsamemap(skill_area_sub,
					sd,PT_AREA_SIZE,
					src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_LUXANIMA:		/* ラクスアニマ */
		{
			const int runes[6] = { SC_BERKANA, SC_NAUTHIZ, SC_TURISUSS, SC_HAGALAZ, SC_ISHA, SC_URUZ };

			if(sd == NULL || sd->status.party_id == 0 || flag&1) {
				if(src->id == bl->id)
					break;

				status_change_start(bl, runes[skill_area_temp[5]], skilllv, 0, 0, 0, skill_get_time(skillid, skilllv),0);
			} else if(sd) {
				int recent = 0, result = -1;
				int i;

				for(i = 0; i < 6; i++) {
					if(sd->sc.data[runes[i]].timer != -1 && ((sd->sc.data[runes[i]].timer * (runes[i] == SC_NAUTHIZ? 3 : 1)) > recent || recent == 0)) {
						recent = sd->sc.data[runes[i]].timer;
						result = i;
					}
				}

				if(result != -1) {
					skill_area_temp[5] = result;
					status_change_end(src, runes[result], -1);
					party_foreachsamemap(skill_area_sub,sd,2,src,skillid,skilllv,tick, flag|BCT_PARTY|1,skill_castend_nodamage_id);
					clif_skill_nodamage(src, src, skillid, skilllv, 1);
				}
			}
		}
		break;
	case GC_WEAPONCRUSH:	/* ウェポンクラッシュ */
		{
			int crush_fix;

			sc = status_get_sc(bl);
			if(sc && (sc->data[SC_STRIPWEAPON].timer != -1 || sc->data[SC_CP_WEAPON].timer != -1)) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				status_change_end(src,SC_WEAPONBLOCKING2,-1);
				break;
			}

			crush_fix = status_get_dex(src) - status_get_dex(bl);
			if(crush_fix < 0)
				crush_fix = 0;
			if(atn_rand()%100 < 5 + 2 * skilllv + crush_fix / 5) {
				if(dstsd) {
					int i;
					for(i=0; i<MAX_INVENTORY; i++) {
						if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip&LOC_RARM)) {
							pc_unequipitem(dstsd,i,0);
							break;
						}
					}
					if(i >= MAX_INVENTORY) {
						if(sd)
							clif_skill_fail(sd,skillid,0,0,0);
						status_change_end(src,SC_WEAPONBLOCKING2,-1);
						break;
					}
				}
				status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,skill_get_time(skillid,skilllv) + crush_fix / 2,0);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			}
			status_change_end(src,SC_WEAPONBLOCKING2,-1);
		}
		break;
	case GC_CREATENEWPOISON:	/* 新毒製造 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_NEWPOISON,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GC_ANTIDOTE:			/* アンチドート */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_calc_pc_stop_begin(bl);

		status_change_end(bl, SC_TOXIN, -1);
		status_change_end(bl, SC_PARALIZE, -1);
		status_change_end(bl, SC_VENOMBLEED, -1);
		status_change_end(bl, SC_MAGICMUSHROOM, -1);
		status_change_end(bl, SC_DEATHHURT, -1);
		status_change_end(bl, SC_PYREXIA, -1);
		status_change_end(bl, SC_OBLIVIONCURSE, -1);
		status_change_end(bl, SC_LEECHEND, -1);

		status_calc_pc_stop_end(bl);
		break;
	case GC_POISONINGWEAPON:	/* ポイズニングウェポン */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_poison_list(sd,skilllv);
		}
		break;
	case AB_ANCILLA:			/* アンシラ */
		if(sd) {
			struct item item_tmp;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 12333;
			item_tmp.identify = 1;
			pc_additem(sd,&item_tmp,1);
		}
		break;
	case AB_CLEMENTIA:		/* クレメンティア */
	case AB_CANTO:			/* カントキャンディダス */
	case AB_CHEAL:			/* コルセオヒール */
		if(sd == NULL)
			break;
		if(flag&1 || sd->status.party_id == 0) {
			int lv = 0;

			switch(skillid) {
				case AB_CLEMENTIA: lv = pc_checkskill(sd,AL_BLESSING); break;
				case AB_CANTO:     lv = pc_checkskill(sd,AL_INCAGI);   break;
				case AB_CHEAL:     lv = pc_checkskill(sd,AL_HEAL);     break;
			}
			lv = (lv < 1)? 1: lv;

			if(skillid == AB_CHEAL) {
				int heal;

				heal = skill_fix_heal(&sd->bl, bl, skillid, skill_calc_heal(&sd->bl, lv));
				if(sd->status.party_id == 0)
					skill_area_temp[0] = 1;
				heal += heal * skill_area_temp[0] * 25 / 1000;

				if(dstsd) {
					if(dstsd->sc.data[SC_BERSERK].timer != -1)
						heal = 0; 	// バーサーク中はヒール０

					if(pc_isgear(dstsd))
						heal = 0; 	// 魔道ギア搭乗中はヒール０
				}

				clif_skill_nodamage(&sd->bl,bl,skillid,heal,1);
				battle_heal(&sd->bl,bl,heal,0,0);
			} else {
				clif_skill_nodamage(&sd->bl,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),lv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = (skilllv == 1)? 3: (skilllv == 2)? 7: 15;
			skill_area_temp[0] = 0;
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_area_sub_count);
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_PRAEFATIO:		/* プラエファティオ */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if( sd == NULL || sd->status.party_id == 0 )
				skill_area_temp[0] = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,skillid,skill_get_time(skillid,skilllv),0);	// キリエエレイソンと区別するためにval4にskillidを格納
		} else {
			skill_area_temp[0] = 0;
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,18,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_area_sub_count);
			party_foreachsamemap(skill_area_sub,
				sd,18,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_ORATIO:	/* オラティオ */
		if(flag&1) {
			if(atn_rand() % 100 < 40 + skilllv * 5)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-AREA_SIZE,bl->y-AREA_SIZE,
				bl->x+AREA_SIZE,bl->y+AREA_SIZE,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_LAUDAAGNUS:		/* ラウダアグヌス */
	case AB_LAUDARAMUS:		/* ラウダラムス */
		if(sd == NULL)
			break;
		if(flag&1 || sd->status.party_id == 0) {
			/* 個別の処理 */
			if(dstsd && dstsd->special_state.no_magic_damage)
				break;
			sc = status_get_sc(bl);
			if(skillid == AB_LAUDAAGNUS && sc && (sc->data[SC_FREEZE].timer != -1 || sc->data[SC_STONE].timer != -1 || sc->data[SC_BLIND].timer != -1 ||
				sc->data[SC_HELLINFERNO].timer != -1 || sc->data[SC_FROSTMISTY].timer != -1 || sc->data[SC_DIAMONDDUST].timer != -1) && atn_rand() % 100 < skilllv * 25)
			{
				status_change_end(bl, SC_FREEZE, -1);
				status_change_end(bl, SC_STONE, -1);
				status_change_end(bl, SC_BLIND, -1);
				status_change_end(bl, SC_HELLINFERNO, -1);
				status_change_end(bl, SC_FROSTMISTY, -1);
				status_change_end(bl, SC_DIAMONDDUST, -1);
			} else if(skillid == AB_LAUDARAMUS && sc && (sc->data[SC_SILENCE].timer != -1 || sc->data[SC_SLEEP].timer != -1 || sc->data[SC_STUN].timer != -1 ||
				sc->data[SC_DEEP_SLEEP].timer != -1 || sc->data[SC_MANDRAGORA].timer != -1) && atn_rand() % 100 < skilllv * 25)
			{
				status_change_end(bl, SC_SILENCE, -1);
				status_change_end(bl, SC_SLEEP, -1);
				status_change_end(bl, SC_STUN, -1);
				status_change_end(bl, SC_DEEP_SLEEP, -1);
				status_change_end(bl, SC_MANDRAGORA, -1);
			} else {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			clif_skill_nodamage(&sd->bl,bl,skillid,skilllv,1);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,18,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_CLEARANCE:		/* クリアランス */
		if(atn_rand() % 100 < 60 + skilllv * 8) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x200);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case AB_SILENTIUM:	/* シレンティウム */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 3 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_WHITEIMPRISON:	/* ホワイトインプリズン */
		sc = status_get_sc(bl);
		if((sc && sc->data[SC_WHITEIMPRISON].timer != -1) || status_get_mode(bl)&MD_BOSS || (src != bl && battle_check_target(src,bl,BCT_ENEMY) <= 0) || atn_rand() % 100 >= 50 + skilllv * 3) {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,(src == bl)? 5000: skill_get_time(skillid,skilllv),0);
		break;
	case WL_SIENNAEXECRATE:	/* シエナエクセクレイト */
		if(flag&1) {
			if(!battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) && atn_rand() % 10000 < status_change_rate(bl,SC_STONE,skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STONE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = (skilllv / 2) + 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_STASIS:		/* ステイシス */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 8 + skilllv;
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_TETRAVORTEX:		/* テトラボルテックス */
		{
			int summon_id[4] = { WL_TETRAVORTEX_FIRE, WL_TETRAVORTEX_WATER, WL_TETRAVORTEX_WIND, WL_TETRAVORTEX_GROUND };
			int i;
			sc = status_get_sc(src);
			if(sc) {
				int c = 0;
				for(i = 0; i < 5; i++) {
					if(sc->data[SC_SUMMONBALL1 + i].timer != -1) {
						if(c < 4) {
							switch(sc->data[SC_SUMMONBALL1 + i].val2) {
								case 1:		// サモンボールライトニング
									summon_id[c] = WL_TETRAVORTEX_WIND;
									break;
								case 2:		// サモンウォーターボール
									summon_id[c] = WL_TETRAVORTEX_WATER;
									break;
								case 3:		// サモンストーン
									summon_id[c] = WL_TETRAVORTEX_GROUND;
									break;
								default:	// サモンファイアーボール
									summon_id[c] = WL_TETRAVORTEX_FIRE;
									break;
							}
							c++;
						}
						status_change_end(src,SC_SUMMONBALL1 + i,-1);
					}
				}
			}
			for(i = 0; i < 4; i++) {
				skill_addtimerskill(src,tick + 250 * i,bl->id,0,0,summon_id[i],skilllv,0,0x0500);
			}
			status_change_pretimer(bl,GetSkillStatusChangeTable(summon_id[atn_rand()%4]),skilllv,0,0,0,skill_get_time(summon_id[atn_rand()%4],skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_SUMMONFB:		/* サモンファイアボール */
	case WL_SUMMONBL:		/* サモンボールライトニング */
	case WL_SUMMONWB:		/* サモンウォーターボール */
	case WL_SUMMONSTONE:	/* サモンストーン */
		sc = status_get_sc(bl);
		if(sc) {
			int i;
			for(i = 0; i < 5; i++) {
				if(sc->data[SC_SUMMONBALL1 + i].timer == -1) {
					int type = (skillid == WL_SUMMONSTONE)? 3: skillid - WL_SUMMONFB;
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					status_change_start(bl,SC_SUMMONBALL1 + i,skilllv,type,0,0,skill_get_time(skillid,skilllv),0);
					break;
				}
			}
			if(i >= 5 && sd)
				clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case WL_RELEASE:	/* リリース */
		sc = status_get_sc(src);
		if(sc) {
			/* 保持スペルがある場合 */
			if(sd && pc_checkskill(sd,sd->freeze_sp_skill[0]) > 0 && sc->data[SC_SPELLBOOK].timer != -1) {
				int freeze_skillid = sd->freeze_sp_skill[0];
				int freeze_skilliv = pc_checkskill(sd,freeze_skillid);

				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				if(skill_get_inf(freeze_skillid)&INF_GROUND) {	// 場所指定のスキル
					skill_castend_pos2(src,bl->x,bl->y,freeze_skillid,freeze_skilliv,tick,0);
				} else if(skill_get_nk(freeze_skillid)&1){
					skill_castend_nodamage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				} else {
					skill_castend_damage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				}
				memmove(&sd->freeze_sp_skill[0],&sd->freeze_sp_skill[1],sizeof(sd->freeze_sp_skill[0])*(MAX_FREEZE_SPELL-1));
				memset(&sd->freeze_sp_skill[MAX_FREEZE_SPELL-1], 0, sizeof(sd->freeze_sp_skill[0]));
				sd->freeze_sp_slot -= skill_get_spellslot(freeze_skillid);

				// 保存スキルを全て使用
				if(sd->freeze_sp_skill[0] == 0) {
					status_change_end(src,SC_SPELLBOOK,-1);
				}
			} else {
				int i, j = 0;
				for(i = 0; i < 5; i++) {
					if(sc->data[SC_SUMMONBALL1 + i].timer != -1) {
						if(j == 0) {	// エフェクトは1発目のみ
							clif_skill_nodamage(src,bl,skillid,skilllv,1);
						}
						skill_addtimerskill(src,tick + 400 * j,bl->id,0,0,WL_SUMMON_ATK_FIRE + sc->data[SC_SUMMONBALL1 + i].val2,sc->data[SC_SUMMONBALL1 + i].val1,0,(0x0f<<20)|flag);
						status_change_end(src,SC_SUMMONBALL1 + i,-1);
						j++;
						if(skilllv < 2) {		// SkillLv2は全てのサモンボールを消費
							break;
						}
					}
				}
				if(j <= 0 && sd) {	// サモンボールが無かった
					clif_skill_fail(sd,skillid,0x14,0,0);
				}
			}
		}
		break;
	case WL_READING_SB:	/* リーディングスペルブック */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_reading_sb_list(sd);
		}
		break;
	case RA_WUGMASTERY:	/* ウォーグマスタリー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_iswolf(sd)) {
				pc_setoption(sd,OPTION_NOTHING);
			} else {
				pc_setoption(sd,OPTION_WUG);
			}
		}
		break;
	case RA_WUGRIDER:	/* ウォーグライダー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			unit_stop_walking(src,1);
			if(pc_iswolfmount(sd)) {
				pc_setoption(sd,OPTION_WUG);
			} else {
				pc_setoption(sd,OPTION_WUGRIDER);
			}
		}
		break;
	case RA_WUGDASH:	/* ウォーグダッシュ */
		if(sd) {
			if(sd->sc.data[SC_WUGDASH].timer != -1) {
				status_change_end(bl,SC_WUGDASH,-1);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			} else {
				int dir = status_get_dir(bl);
				if(map_getcell(sd->bl.m,sd->bl.x+dirx[dir],sd->bl.y+diry[dir],CELL_CHKPASS) && map_count_oncell(sd->bl.m,sd->bl.x+dirx[dir],sd->bl.y+diry[dir],BL_PC|BL_MOB|BL_NPC) == 0)
					status_change_start(bl,SC_WUGDASH,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case RA_CAMOUFLAGE:	/* カモフラージュ */
		if(sd && skilllv < 3) {		// 周りに壁があるかのチェック
			int i;
			for(i=0; i<8;i++){
				if(map_getcell(bl->m,bl->x+dirx[i],bl->y+diry[i],CELL_CHKNOPASS))
					break;
			}
			if(i >= 8) {
				clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NC_F_SIDESLIDE:	/* フロントサイドスライド */
	case NC_B_SIDESLIDE:	/* リアサイドスライド */
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			int dir, pc_dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			dir = status_get_dir(src);

			if(skillid == NC_F_SIDESLIDE) {
				dir = (dir+4) & 0x07;
				if(dir == 0)
					dir = 8;
			}

			// 方向を保存しておいて、吹き飛ばし後に戻す
			if(sd) {
				pc_dir = sd->dir;
				head_dir = sd->head_dir;
			}

			unit_stop_walking(src,1);
			skill_blown(src,bl,count|(dir<<20)|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			clif_blown(src,src->x,src->y);
			clif_skill_nodamage(src,src,skillid,skilllv,1);

			if(sd)
				pc_setdir(sd, pc_dir, head_dir);
		}
		break;
	case NC_EMERGENCYCOOL:	/* エマージェンシークール */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_OVERHEAT].timer != -1) {
			status_change_end(src,SC_OVERHEAT,-1);
		}
		if(sd) {
			sd->overheat = 0;	// 加熱度を初期化
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NC_INFRAREDSCAN:	/* インフラレッドスキャン */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING)) {
				if(sc->option & (OPTION_HIDE | OPTION_CLOAKING)) {
					status_change_end(bl, SC_HIDING, -1);
					status_change_end(bl, SC_CLOAKING, -1);
					status_change_end(bl, SC_CLOAKINGEXCEED, -1);
					status_change_end(bl, SC__INVISIBILITY, -1);
				}
				if(sc->option & OPTION_SPECIALHIDING) {
					status_change_end(bl, SC_INVISIBLE, -1);
				}
			}
			if(atn_rand() % 10000 < 5000) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-7,bl->y-7,bl->x+7,bl->y+7,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_ANALYZE:		/* アナライズ */
		if(atn_rand() % 10000 < 1400 * skilllv) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case NC_MAGNETICFIELD:	/* マグネティックフィールド */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				int sec = skill_get_time(skillid,skilllv) - status_get_agi(bl)*100;
				if(status_get_mode(bl)&MD_BOSS)
					sec /= 5;
				// 最低拘束時間補償
				if(sec < 3000)
					sec = 3000;
				unit_stop_walking(bl,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0);
			}
		} else {
			int ar = skilllv;
			sc = status_get_sc(src);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			// ホバーリング状態じゃなければ自信にも状態異常
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				int sec = skill_get_time(skillid,skilllv) - status_get_agi(src)*100;
				if(status_get_mode(src)&MD_BOSS)
					sec /= 5;
				// 最低拘束時間補償
				if(sec < 3000)
					sec = 3000;
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0);
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_NEUTRALBARRIER:		/* ニュートラルバリアー */
	case NC_STEALTHFIELD:		/* ステルスフィールド */
		{
			struct skill_unit_group *sg;
			int type = GetSkillStatusChangeTable(skillid);
			if(type < 0)
				break;
			sc = status_get_sc(src);
			if(sc && sc->data[type].timer != -1) {
				status_change_end(src,type,-1);
			}
			sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,type,skilllv,0,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case NC_REPAIR:			/* リペア */
		if(dstsd && pc_isgear(dstsd)) {
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * (3 + 3 * skilllv) / 100);
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case SC_AUTOSHADOWSPELL:	/* オートシャドウスペル */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_autoshadowspell(sd,skilllv);
		}
		break;
	case SC_SHADOWFORM:			/* シャドウフォーム */
		if(sd) {
			if(dstsd && dstsd->shadowform_id == 0) {
				if(sd->bl.id == dstsd->bl.id ||
				   ((!map[src->m].flag.pvp && !map[src->m].flag.gvg) &&
				    (sd->status.party_id <= 0 || dstsd->status.party_id <= 0 ||
				    sd->status.party_id != dstsd->status.party_id)))
				{
					clif_skill_fail(sd,skillid,0,0,0);
					break;
				}
				clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,skilllv,1);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,dstsd->bl.id,0,0,skill_get_time(skillid,skilllv),0 );
				dstsd->shadowform_id = sd->bl.id;
			} else {
				clif_skill_fail(sd,skillid,0,0,0);
			}
		}
		break;
	case SC_BODYPAINT:	/* ボディペインティング */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				sc = status_get_sc(bl);
				if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING)) {
					if(sc->option & (OPTION_HIDE | OPTION_CLOAKING)) {
						status_change_end(bl, SC_HIDING, -1);
						status_change_end(bl, SC_CLOAKING, -1);
						status_change_end(bl, SC_CLOAKINGEXCEED, -1);
						status_change_end(bl, SC__INVISIBILITY, -1);
					}
					if(sc->option & OPTION_SPECIALHIDING) {
						status_change_end(bl, SC_INVISIBLE, -1);
					}
				}
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300+200*skilllv,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
				if(atn_rand() % 10000 < 500 * skilllv)
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-2,src->y-2,src->x+2,src->y+2,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SC_ENERVATION:		/* マスカレード ： エナーベーション */
	case SC_GROOMY:			/* マスカレード ： グルーミー */
	case SC_IGNORANCE:		/* マスカレード ： イグノアランス */
	case SC_LAZINESS:		/* マスカレード ： レイジーネス */
	case SC_UNLUCKY:		/* マスカレード ： アンラッキー */
	case SC_WEAKNESS:		/* マスカレード ： ウィークネス */
		{
			int mask_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			mask_fix = (status_get_dex(src) + status_get_lv(src)) - (status_get_agi(bl) - status_get_lv(bl));
			if(mask_fix < 0)
				mask_fix = 0;

			if(atn_rand()%100 >= 5 + 2 * skilllv + mask_fix / 5) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			// スキルごとの個別処理
			switch(skillid) {
			case SC_ENERVATION:	/* マスカレード ： エナーベーション */
				if(dstsd)
					pc_delspiritball(dstsd,dstsd->spiritball.num,0);	// 気弾を削除
				break;
			case SC_GROOMY:		/* マスカレード ： グルーミー */
				if(dstsd) {
					pc_setoption(dstsd,(dstsd->sc.option & ~(OPTION_CARTMASK | OPTION_FALCON |
						OPTION_PECO | OPTION_DRAGONMASK | OPTION_WUG | OPTION_WUGRIDER)));	// カートなどの付属品を削除
					if(dstsd->pd) pet_return_egg(dstsd);
					if(dstsd->hd) homun_return_embryo(dstsd);
					status_change_end(bl,SC_ALL_RIDING,-1);
					status_change_end(bl,SC_ON_PUSH_CART,-1);
				}
				break;
			case SC_IGNORANCE:		/* マスカレード ： イグノアランス */
				{
					int sp;

					if(dstsd) {
						sp = 100 * skilllv;
						if(dstsd->status.sp < sp)
							sp = dstsd->status.sp;
						dstsd->status.sp -= sp;
						clif_updatestatus(dstsd,SP_SP);
					}
					else
					{
						sp = status_get_lv(bl);
					}

					if(sd) {
						sd->status.sp += sp;
						if(sd->status.sp > sd->status.max_sp)
							sd->status.sp = sd->status.max_sp;
						clif_updatestatus(sd,SP_SP);
					}
				}
				break;
			case SC_WEAKNESS:		/* マスカレード ： ウィークネス */
				if(dstsd) {
					int i;

					for(i=0; i<=MAX_INVENTORY; i++) {
						if(dstsd->status.inventory[i].equip & LOC_RLARM) {
							pc_unequipitem(dstsd,i,0);	// 武器と盾を解除
						}
					}
				}
				break;
			default:
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SC_STRIPACCESSARY:		/* ストリップアクセサリー */
		{
			int strip_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			strip_fix = status_get_dex(src) - status_get_dex(bl);
			if(strip_fix < 0)
				strip_fix = 0;
			if(atn_rand()%100 >= 12 + 2 * skilllv + ((strip_fix)? strip_fix / 5: 0)) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_RLACCESSORY)) {
						pc_unequipitem(dstsd,i,0);
					}
				}
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SC_FEINTBOMB:		/* フェイントボム */
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// バックステップ
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
		}
		break;
	case SC_ESCAPE:			/* エスケープ */
		if(sd) {
			int i, nameid, amount, idx = 0;
			for(i = 0; i < 10; i++) {
				nameid = skill_db[skill_get_skilldb_id(skillid)].itemid[i];
				amount = skill_db[skill_get_skilldb_id(skillid)].amount[i];
				if(nameid <= 0 || amount <= 0)
					continue;
				idx = pc_search_inventory(sd,nameid);

				// 設置用トラップが足りなかった場合
				if((idx < 0 || sd->status.inventory[idx].amount < amount) && nameid == 1065)
				{
					// 改良型設置用トラップを検索
					nameid = 7940;
					amount = 1;
					idx = pc_search_inventory(sd,nameid);
				}

				if(idx < 0 || sd->status.inventory[idx].amount < amount) {
					break;
				}
				pc_delitem(sd,idx,amount,0,1);
			}
		}
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// バックステップ
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
		}
		break;
	case LG_TRAMPLE:		/* トランプル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		map_foreachinarea(skill_trample,bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,BL_SKILL,src,skilllv);
		break;
	case LG_SHIELDSPELL:		/* シールドスペル */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src))) {
				int time = 20000;
				if(sd) {
					int idx = sd->equip_index[EQUIP_INDEX_LARM];
					if(idx >= 0 && sd->inventory_data[idx] && itemdb_isarmor(sd->inventory_data[idx]->nameid)) {
						time = time * sd->inventory_data[idx]->mdef;
					}
				}
				status_change_pretimer(bl,SC_SILENCE,1,0,0,0,time,0,tick+status_get_amotion(src));
			}
		}
		else if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(idx >= 0 && sd->inventory_data[idx] && itemdb_isarmor(sd->inventory_data[idx]->nameid)) {
				int rate,val;
				switch(skilllv) {
				case 1:
#ifdef PRE_RENEWAL
					val = sd->inventory_data[idx]->def * 10;
#else
					val = sd->inventory_data[idx]->def;
#endif
					if(atn_rand()%100 >= val) {
						clif_skill_fail(sd,skillid,0,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// 範囲物理攻撃
						int ar = (val>80? 3: (val>40? 2: 1));
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_damage_id);
					}
					else if(rate < 75) {	// 物理攻撃反射
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,1,val/10,0,val*2000,0);
					}
					else {					// 攻撃力増加
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,2,val,0,val*3000,0);
					}
					break;
				case 2:
					val = sd->inventory_data[idx]->mdef;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,0,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 30) {			// 範囲魔法攻撃
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|2,
							skill_castend_damage_id);
					}
					else if(rate < 60) {	// 沈黙攻撃
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_nodamage_id);
					}
					else {					// マグニフィカート
						status_change_start(bl,SC_SHIELDSPELL_MDEF,skilllv,0,0,0,val*30000,0);
					}
					break;
				case 3:
					val = sd->status.inventory[idx].refine;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,0,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// HP回復
						int heal = sd->status.max_hp * (1 + sd->status.base_level / 10 + val) / 100;
						clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
						pc_heal(sd,heal,0);
					}
					else if(rate < 75) {	// 鎧破壊
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,1,val*10,0,val*30000,0);
					}
					else {					// DEF増加
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,2,val*10*sd->status.base_level/100,0,val*20000,0);
					}
					break;
				}
			}
		}
		break;
	case LG_BANDING:			/* バンディング */
		sc = status_get_sc(src);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			status_change_end(src,GetSkillStatusChangeTable(skillid),-1);
		}
		else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,sg->bl.id,0,0);
			}
		}
		break;
	case LG_PIETY:		/* パイエティ */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LG_INSPIRATION:		/* インスピレーション */
		if(sd) {
			int loss_exp = pc_nextbaseexp(sd) / 1000;
			if(loss_exp > 0) {
				sd->status.base_exp -= loss_exp;
				if(sd->status.base_exp < 0)
					sd->status.base_exp = 0;
				clif_updatestatus(sd,SP_BASEEXP);
			}
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_release(src,0x04);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SR_CURSEDCIRCLE:		/* 呪縛陣 */
		if(flag&1) {
			if(!(status_get_mode(bl)&MD_BOSS)) {
				if(sd) {
					if(sd->spiritball.num > 0) {
						pc_delspiritball(sd,1,0);
						status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					}
				} else {
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		} else {
			int ar = (skilllv + 1) / 2;
			status_change_start(bl,SC_CURSEDCIRCLE_USER,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_RAISINGDRAGON:		/* 潜龍昇天 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_EXPLOSIONSPIRITS,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd)
			pc_addspiritball(sd,skill_get_time2(skillid,skilllv),MAX_SPIRITBALL);
		break;
	case SR_ASSIMILATEPOWER:	/* 吸気功 */
		if(flag&1) {
			int val = 0;
			if(dstsd && dstsd->spiritball.num > 0) {
				val += dstsd->spiritball.num;
				pc_delspiritball(dstsd,dstsd->spiritball.num,0);
			}
			if(sd) {
				int sp = sd->status.max_sp * val / 100;
				if(sd->status.sp + sp > sd->status.max_sp)
					sp = sd->status.max_sp - sd->status.sp;
				if(sp > 0) {
					sd->status.sp += sp;
					clif_updatestatus(sd,SP_SP);
				}
			}
		} else {
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				src->m,src->x-2,src->y-2,src->x+2,src->y+2,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_POWERVELOCITY:		/* 全気注入 */
		if(sd && dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),sd->spiritball.num);
			pc_delspiritball(sd,sd->spiritball.num,0);
		}
		break;
	case SR_GENTLETOUCH_CURE:	/* 点穴 -快- */
		{
			int heal = (int)(skilllv * 120 + (atn_bignumber)status_get_max_hp(bl) * (2 + skilllv) / 100);
			battle_heal(NULL,bl,heal,0,0);
			if(atn_rand()%100 < skilllv * 5 + status_get_dex(src) / 2) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_calc_pc_stop_begin(bl);

				status_change_end(bl, SC_STONE, -1);
				status_change_end(bl, SC_FREEZE, -1);
				status_change_end(bl, SC_STUN, -1);
				status_change_end(bl, SC_POISON, -1);
				status_change_end(bl, SC_SILENCE, -1);
				status_change_end(bl, SC_BLIND, -1);
				status_change_end(bl, SC_HALLUCINATION, -1);
				status_change_end(bl, SC_HELLINFERNO, -1);
				status_change_end(bl, SC_FROSTMISTY, -1);
				status_change_end(bl, SC_TOXIN, -1);
				status_change_end(bl, SC_PARALIZE, -1);
				status_change_end(bl, SC_VENOMBLEED, -1);
				status_change_end(bl, SC_MAGICMUSHROOM, -1);
				status_change_end(bl, SC_DEATHHURT, -1);
				status_change_end(bl, SC_PYREXIA, -1);
				status_change_end(bl, SC_OBLIVIONCURSE, -1);
				status_change_end(bl, SC_LEECHEND, -1);

				status_calc_pc_stop_end(bl);
			}
		}
		break;
	case SR_GENTLETOUCH_CHANGE:		/* 点穴 -反- */
		{
			int val1 = (status_get_str(src) / 2 + status_get_dex(src) / 4) * skilllv / 5;
			int val2 = (200 / (status_get_int(src)>1? status_get_int(src): 1) ) * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val1,val2>0? val2: 0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_GENTLETOUCH_REVITALIZE:	/* 点穴 -活- */
		{
			int val = status_get_vit(src) / 2 * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_FLASHCOMBO:		/* 閃光連撃 */
		{
			int combo_id[4] = { SR_DRAGONCOMBO,SR_FALLENEMPIRE,SR_TIGERCANNON,SR_SKYNETBLOW };
			int combo_lv[4] = { 10,5,10,5 };
			int delay[4] = { 0,250,500,2000 };
			int i;
			if(sd)
				sd->ud.attackabletime = sd->item_delay_tick = sd->ud.canact_tick = tick + 2000;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i = 0; i < 4; i++) {
				skill_addtimerskill(src,tick + delay[i],bl->id,0,0,
					combo_id[i],(sd ? pc_checkskill(sd,combo_id[i]) : combo_lv[i]),BF_WEAPON,flag);
			}
		}
		break;
	case WA_SWING_DANCE:		/* スイングダンス */
	case WA_SYMPHONY_OF_LOVE:	/* 恋人たちの為のシンフォニー */
	case WA_MOONLIT_SERENADE:	/* 月明かりのセレナーデ */
	case MI_RUSH_WINDMILL:		/* 風車に向かって突撃 */
	case MI_ECHOSONG:			/* エコーの歌 */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? sd->status.job_level: 0),((sd)? pc_checkskill(sd,WM_LESSON): 0),0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 6 + skilllv;
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MI_HARMONIZE:			/* ハーモナイズ */
		{
			int param = 5 + skilllv * 5;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
			if(src != bl)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case WM_VOICEOFSIREN:	/* セイレーンの声 */
		if(flag&1) {
			if(atn_rand() % 10000 < 2000 + 1000 * skilllv) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = 1 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_DEADHILLHERE:		/* 生死の境で */
		if(dstsd) {
			if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVPで復活不可能状態
				break;
			if(!unit_isdead(&dstsd->bl))			// 死亡判定
				break;
			if(atn_rand() % 10000 >= 9000 + 200 * skilllv)
				break;
			if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// ヘルパワー状態は蘇生不可
				break;
			if(dstsd->special_state.no_magic_damage)
				break;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd->special_state.restart_full_recover) {	// オシリスカード
				dstsd->status.hp = dstsd->status.max_hp;
				dstsd->status.sp = dstsd->status.max_sp;
			}
			else {
				if(dstsd->status.sp > 0) {
					dstsd->status.hp = dstsd->status.sp;
					dstsd->status.sp -= dstsd->status.sp * (50 - skilllv * 10) / 100;
				}
				else
					dstsd->status.hp = 1;
			}

			clif_updatestatus(dstsd,SP_HP);
			clif_updatestatus(dstsd,SP_SP);
			pc_setstand(dstsd);
			if(battle_config.pc_invincible_time > 0)
				pc_setinvincibletimer(dstsd,battle_config.pc_invincible_time);
			clif_resurrection(&dstsd->bl,1);
		}
		break;
	case WM_LULLABY_DEEPSLEEP:	/* 安らぎの子守唄 */
		if(flag&1) {
			if(bl->id != skill_area_temp[0]) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DEEP_SLEEP,400 * skilllv,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = 4 + skilllv;
			skill_area_temp[0] = src->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_SIRCLEOFNATURE:		/* 循環する自然の音 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 2 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_RANDOMIZESPELL:		/* 不確定要素の言語 */
		if(sd) {
			int rand_skillid = skill_searchrandomid(2);
			int rand_skilllv = skill_get_max(rand_skillid);

			if(rand_skilllv > skilllv + 5)
				rand_skilllv = skilllv + 5;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sd->skill_item.id      = rand_skillid;
			sd->skill_item.lv      = rand_skilllv;
			sd->skill_item.flag    = 1;		// 使用条件判定する
			clif_item_skill(sd, rand_skillid, rand_skilllv, "");
		}
		break;
	case WM_SONG_OF_MANA:		/* マナの歌 */
	case WM_DANCE_WITH_WUG:		/* ダンスウィズウォーグ */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 4 + skilllv;
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
		if(flag&1) {
			if(skill_area_temp[0] >= 7) {
				int dmg = 9999;
				if(status_get_max_hp(src) < dmg)
					dmg = status_get_max_hp(src);
				clif_damage(bl,bl,tick,0,0,dmg,0,9,0,0);
				battle_damage(bl,bl,dmg,0,0,0);
			}
			if(!unit_isdead(bl))
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 2 + skilllv;
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
					src,skillid,skilllv,tick,flag|BCT_ALL|1,
					skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_LERADS_DEW:			/* レーラズの霧 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 4 + (skilllv+1)/2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_BEYOND_OF_WARCRY:	/* ビヨンドオブウォークライ */
	case WM_MELODYOFSINK:		/* メロディーオブシンク */
		if(flag&1) {
			int rate = 1500 + 500 * skilllv;
			if(skill_area_temp[0] >= 3 && skill_area_temp[0] <= 7)
				rate += 5 * (skill_area_temp[0]-2);
			if(atn_rand() % 10000 < 1500 + 500 * skilllv) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = 4 + (skilllv+1)/2;
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-5,bl->y-5,bl->x+5,bl->y+5,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_FRIGG_SONG:		/* フリッグの歌 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 2 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 通常マップは全プレイヤー、対人MAPではPARTYのみ
			if(!map[src->m].flag.pvp && !map[src->m].flag.gvg && !map[src->m].flag.pk) {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_NOENEMY|1,
					skill_castend_nodamage_id);
			}
			else {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
		}
		break;
	case SO_FIREWALK:		/* ファイアーウォーク */
	case SO_ELECTRICWALK:	/* エレクトリックウォーク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SO_SPELLFIST:		/* スペルフィスト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_skillcastcancel(src,1);
		if(sd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,sd->skill_used.id,sd->skill_used.lv,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_STRIKING:		/* ストライキング */
		{
			int val = 8 + skilllv * 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd) {
				int idx = dstsd->equip_index[EQUIP_INDEX_RARM];
				if(idx >= 0 && dstsd->inventory_data[idx])
					val = val * dstsd->inventory_data[idx]->wlv;
			}
			if(sd) {
				val += pc_checkskill(sd,SA_FLAMELAUNCHER) * 5;
				val += pc_checkskill(sd,SA_FROSTWEAPON) * 5;
				val += pc_checkskill(sd,SA_LIGHTNINGLOADER) * 5;
				val += pc_checkskill(sd,SA_SEISMICWEAPON) * 5;
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,val,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = (skilllv + 1) / 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SO_EL_CONTROL:		/* エレメンタルコントロール */
		if(sd && sd->eld) {
			int mode;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skilllv == 4) {
				elem_delete_data(sd);
				break;
			}
			switch(skilllv) {
				case 1:  mode = ELMODE_PASSIVE;   break;
				case 2:  mode = ELMODE_DEFENSIVE; break;
				case 3:  mode = ELMODE_OFFENSIVE; break;
				default: mode = ELMODE_WAIT;      break;
			}
			elem_change_mode(sd->eld, mode);
		}
		break;
	case SO_SUMMON_AGNI:	/* サモンアグニ */
	case SO_SUMMON_AQUA:	/* サモンアクア */
	case SO_SUMMON_VENTUS:	/* サモンベントス */
	case SO_SUMMON_TERA:	/* サモンテラ */
		if(sd) {
			int elem_id = 0;
			int type = GetSkillStatusChangeTable(skillid);
			if(type < 0)
				break;

			switch(skillid) {
				case SO_SUMMON_AGNI:   elem_id = 2114 + skilllv - 1; break;
				case SO_SUMMON_AQUA:   elem_id = 2117 + skilllv - 1; break;
				case SO_SUMMON_VENTUS: elem_id = 2120 + skilllv - 1; break;
				case SO_SUMMON_TERA:   elem_id = 2123 + skilllv - 1; break;
			}

			// 精霊召喚中の場合は一旦解除する
			if(sd->sc.data[type].timer != -1)
				status_change_end(src,type,-1);

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_create_data(sd,elem_id,skill_get_time(skillid,skilllv)/1000);
			status_change_start(src,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_EL_ACTION:	/* エレメンタルアクション */
		if(sd && sd->eld) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_skilluse(sd->eld, bl, ELMODE_OFFENSIVE);
		}
		break;
	case SO_EL_ANALYSIS:	/* エレメンタルアナライシス */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,skilllv);
		}
		break;
	case SO_EL_CURE:	/* エレメンタルキュアー */
		if(sd && sd->eld) {
			int hp = sd->status.max_hp * 10 / 100;
			int sp = sd->status.max_sp * 10 / 100;
			if(sd->status.hp >= hp && sd->status.sp >= sp) {
				int hp2 = sd->eld->max_hp * 10 / 100;
				int sp2 = sd->eld->max_sp * 10 / 100;

				sd->status.hp -= hp;
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_HP);
				clif_updatestatus(sd,SP_SP);

				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				elem_heal(sd->eld,hp2,sp2);
			}
		}
		break;
	case SO_ELEMENTAL_SHIELD:	/* エレメンタルシールド */
		if(flag&1 || sd == NULL) {
			if(unit_isdead(bl))			// 死亡判定
				break;
			skill_unitsetting(src,MG_SAFETYWALL,skilllv + 5,bl->x,bl->y,0);
			skill_unitsetting(src,AL_PNEUMA,1,bl->x,bl->y,0);
		} else if(sd) {
			if(!sd->eld)
				break;
			elem_delete_data(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->status.party_id)
				party_foreachsamemap(skill_area_sub,sd,5,src,skillid,skilllv,tick,flag|BCT_PARTY|1,skill_castend_nodamage_id);
			else {
				skill_unitsetting(src,MG_SAFETYWALL,skilllv + 5,src->x,src->y,0);
				skill_unitsetting(src,AL_PNEUMA,1,src->x,src->y,0);
			}
		}
		break;
	case GN_BLOOD_SUCKER:		/* ブラッドサッカー */
	case GN_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case LG_KINGS_GRACE:	/* キングスグレイス */
	case GN_WALLOFTHORN:	/* ソーンウォール */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case GN_MANDRAGORA:		/* ハウリングオブマンドラゴラ */
		if(flag&1) {
			if(atn_rand() % 10000 < 2500 + 1000 * skilllv) {
				if(dstsd) {
					int sp = dstsd->status.max_sp * (25 + skilllv * 5) / 100;
					if(dstsd->status.sp < sp)
						sp = dstsd->status.sp;
					dstsd->status.sp -= sp;
					clif_updatestatus(dstsd,SP_SP);
				}
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-7,bl->y-7,bl->x+7,bl->y+7,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_SLINGITEM:		/* スリングアイテム */
		if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if(idx >= 0 && sd->inventory_data[idx]) {
				int nameid = sd->inventory_data[idx]->nameid;
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(nameid <= 0)
					break;
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))
					break;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);

				// 投擲物によって効果決定
				switch(nameid) {
				case 13260:		// リンゴ爆弾
				case 13261:		// ココナッツ爆弾
				case 13262:		// メロン爆弾
				case 13264:		// バナナ爆弾
				case 13265:		// 黒い塊
				case 13266:		// 硬くて黒い塊
				case 13267:		// とても硬い塊
					if(battle_check_target(src,bl,BCT_ENEMY) > 0)
						battle_skill_attack(BF_WEAPON,src,src,bl,GN_SLINGITEM_RANGEMELEEATK,nameid - 13260,tick,flag|(0x0f<<20));
					break;
				case 13263:		// パイナップル爆弾
					if(battle_check_target(src,bl,BCT_ENEMY) > 0)
						map_foreachinarea(skill_area_sub,
							bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
							src,GN_SLINGITEM_RANGEMELEEATK,3,tick,flag|BCT_ENEMY|(0x0f<<20),
							skill_castend_damage_id);
					break;
				default:
					if(dstsd) {
						struct item_data *item = itemdb_search(nameid);
						if(item->use_script)
							run_script(item->use_script,0,dstsd->bl.id,0);
					}
					break;
				}
			}
		}
		break;
	case GN_CHANGEMATERIAL:	/* チェンジマテリアル */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,0);
		}
		break;
	case GN_MIX_COOKING:	/* ミックスクッキング */
		if(sd) {
			clif_making_list(sd,PRD_MIX_COOKING,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_MAKEBOMB:		/* 爆弾製造 */
		if(sd) {
			clif_making_list(sd,PRD_MAKEBOMB,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_S_PHARMACY:		/* スペシャルファーマシー */
		if(sd) {
			clif_making_list(sd,PRD_S_PHARMACY,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case KO_ZANZOU:		/* 幻術 -影武者- */
		if(sd) {
			int id = 0;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, sd->bl.x, sd->bl.y, sd->status.name, 2308, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->hp           = 3000 + skilllv * 3000 + sd->status.max_sp;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// バックステップ
				int dir = 0, head_dir = 0;
				int count = skill_get_blewcount(skillid,skilllv);

				if(sd) {
					dir = sd->dir;
					head_dir = sd->head_dir;
				}
				unit_stop_walking(src,1);
				skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
				if(sd)
					pc_setdir(sd, dir, head_dir);
			}
		}
		break;
	case KO_KYOUGAKU:		/* 幻術 -驚愕- */
		{
			int rate;
			// プレイヤー以外または味方には使用不可
			if(bl->type != BL_PC || battle_check_target(src,bl,BCT_PARTY) > 0) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			rate = 4500 + 500 * skilllv - status_get_int(bl) / 10;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int param = (skilllv > 0)? skilllv*2 + atn_rand()%(skilllv*3) : 0;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
		}
		break;
	case KO_JYUSATSU:		/* 幻術 -呪殺- */
		{
			int rate;
			// プレイヤー以外には使用不可
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			rate = 4500 + 1000 * skilllv - status_get_int(bl) / 2;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int damage = (int)((atn_bignumber)status_get_max_hp(bl) * skilllv * 5 / 100);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_damage(src,bl,damage,0,0,0);
				if(status_get_lv(src) >= status_get_lv(bl)) {
					if(atn_rand() % 10000 < 10 * skilllv) {
						// コーマ
						if(dstsd) {
							dstsd->status.hp = 1;
							clif_updatestatus(dstsd,SP_HP);
						}
					}
				}
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
		}
		break;
	case KO_KAHU_ENTEN:	/* 火符：炎天 */
	case KO_HYOUHU_HUBUKI:	/* 氷符：吹雪 */
	case KO_KAZEHU_SEIRAN:	/* 風符：青嵐 */
	case KO_DOHU_KOUKAI:	/* 土符：剛塊 */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 他属性を召喚している場合は削除
			if(sd->elementball.num) {
				if(sd->elementball.ele != skill_get_pl(skillid)) {
					pc_delelementball(sd,sd->elementball.num,0);
				}
			}
			pc_addelementball(sd,skill_get_time(skillid,skilllv),MAX_ELEMENTBALL,skill_get_pl(skillid));
		}
		break;
	case KO_GENWAKU:		/* 幻術 -幻惑- */
		{
			int rate = 4500 + 500 * skilllv - status_get_int(bl) / 10;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int x = src->x;
				int y = src->y;
				struct block_list *t_bl = src;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				unit_movepos(src,bl->x,bl->y,0);
				if(!(status_get_mode(bl)&MD_BOSS))	// ボス属性以外
					unit_movepos(bl,x,y,0);
				if(atn_rand() % 10000 < 7500) {
					t_bl = bl;
				}
				status_change_pretimer(t_bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
		}
		break;
	case KO_IZAYOI:		/* 十六夜 */
	case KG_KYOMU:		/* 幻術 -虚無の影- */
	case KG_KAGEMUSYA:	/* 幻術 -分身- */
	case OB_ZANGETSU:	/* 幻術 -残月- */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case KG_KAGEHUMI:	/* 幻術 -影踏み- */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc) {
				if(sc->data[SC_HIDING].timer != -1 || sc->data[SC_CLOAKING].timer != -1 || sc->data[SC_CLOAKINGEXCEED].timer != -1 ||
				   sc->data[SC__SHADOWFORM].timer != -1 || sc->data[SC_CAMOUFLAGE].timer != -1 || sc->data[SC_MARIONETTE].timer != -1 ||
				   sc->data[SC_MARIONETTE2].timer != -1 || sc->data[SC_HARMONIZE].timer != -1)
				{
					status_change_end(bl, SC_HIDING, -1);
					status_change_end(bl, SC_CLOAKING, -1);
					status_change_end(bl, SC_CLOAKINGEXCEED, -1);
					status_change_end(bl, SC__SHADOWFORM, -1);
					status_change_end(bl, SC_CAMOUFLAGE, -1);
					status_change_end(bl, SC_MARIONETTE, -1);
					status_change_end(bl, SC_MARIONETTE2, -1);
					status_change_end(bl, SC_HARMONIZE, -1);
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		} else {
			int ar = 1 + skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case OB_OBOROGENSOU:	/* 幻術 -朧幻想- */
		{
			int hp = 0, hp_val, hp_max, hp_per = 0, hp_lv;
			int sp = 0, sp_val, sp_max, sp_per = 0, sp_lv;

			// プレイヤー以外には無効
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置

			// HPの割合算出
			hp_val = status_get_hp(bl);
			hp_max = status_get_max_hp(bl);

			if(hp_max != 0) {
				hp_per = 100 * hp_val / hp_max;
			}
			if(hp_per > 75)      hp_lv = 5;
			else if(hp_per > 50) hp_lv = 4;
			else if(hp_per > 30) hp_lv = 3;
			else if(hp_per > 15) hp_lv = 2;
			else                 hp_lv = 1;

			if(hp_val % 2 == 0)
				hp = hp_max * ((6 - hp_lv) * 4 + skilllv) / 100;
			else
				hp -= hp_max * (hp_lv * 4 + skilllv) / 100;

			// SPの割合算出
			sp_val = status_get_sp(bl);
			sp_max = status_get_max_sp(bl);

			if(sp_max != 0) {
				sp_per = 100 * sp_val / sp_max;
			}
			if(sp_per > 75)      sp_lv = 5;
			else if(sp_per > 50) sp_lv = 4;
			else if(sp_per > 30) sp_lv = 3;
			else if(sp_per > 15) sp_lv = 2;
			else                 sp_lv = 1;

			if(sp_val % 2 == 0)
				sp = sp_max * ((6 - sp_lv) * 3 + skilllv) / 100;
			else
				sp -= sp_max * (sp_lv * 3 + skilllv) / 100;

			unit_heal(bl,hp,sp);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case OB_AKAITSUKI:	/* 幻術 -紅月- */
		// 対人MAP以外ではプレイヤーに使用不可またはBOSS、味方には使用不可
		if((!map[src->m].flag.pvp && !map[src->m].flag.gvg && !map[src->m].flag.pk && bl->type == BL_PC) || status_get_mode(bl)&MD_BOSS || battle_check_target(src,bl,BCT_PARTY) > 0) {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_HIDE:	/* かくれる */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			break;
		}
	case SU_STOOP:	/* うずくまる */
	case SU_CHATTERING:	/* チャタリング */
	case SU_ARCLOUSEDASH:	/* アクラウスダッシュ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_TUNAPARTY:	/* マグロシールド */
		{
			int rate;
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			rate = (int)(skilllv * 10 * (atn_bignumber)status_get_max_hp(bl) / 100);
			if(sd && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// 海の魂
				rate *= 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,rate,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_CN_POWDERING:	/* イヌハッカシャワー */
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case SU_SV_ROOTTWIST:	/* マタタビの根っこ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_HISS:	/* 警戒 */
		if(flag&1 || sd == NULL) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			int ar = 9 + (skilllv/2) * 3;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_POWEROFFLOCK:	/* 群れの力 */
		if(flag&1) {
			int rate = 10 + 5 * skilllv + status_get_dex(src) / 10 + status_get_luk(src) / 10;	// 暫定確率
			if(atn_rand() % 10000 < rate)
				status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-7,bl->y-7,
				bl->x+7,bl->y+7,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_GROOMING:	/* グルーミング */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_BLEED, -1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_FEAR, -1);
		status_change_end(bl, SC_MANDRAGORA, -1);
		status_change_end(bl, SC_DIAMONDDUST, -1);
		status_change_end(bl, SC_FROSTMISTY, -1);
		status_change_end(bl, SC_DEEP_SLEEP, -1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_PURRING:	/* のどを鳴らす */
		if(flag&1) {
			int lv = pc_checkskill(sd,SU_GROOMING);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_end(bl, SC_STUN, -1);
			status_change_end(bl, SC_FREEZE, -1);
			status_change_end(bl, SC_STONE, -1);
			status_change_end(bl, SC_SLEEP, -1);
			status_change_end(bl, SC_SILENCE, -1);
			status_change_end(bl, SC_BLEED, -1);
			status_change_end(bl, SC_POISON, -1);
			status_change_end(bl, SC_FEAR, -1);
			status_change_end(bl, SC_MANDRAGORA, -1);
			status_change_end(bl, SC_DIAMONDDUST, -1);
			status_change_end(bl, SC_FROSTMISTY, -1);
			status_change_end(bl, SC_DEEP_SLEEP, -1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),lv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 9 + (skilllv/2) * 3;
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_MEOWMEOW:	/* ミャウミャウ */
		if(flag&1) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 9 + (skilllv/2) * 3;
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_FRESHSHRIMP:	/* 新鮮なエビ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv)),skill_get_time(skillid,skilllv),0);
		break;
	case SU_BUNCHOFSHRIMP:	/* エビ三昧 */
		if(flag&1) {
			int heal;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));

			if(sc) {
				if(sc->data[SC_CRITICALWOUND].timer != -1)
					heal = heal * (100 - sc->data[SC_CRITICALWOUND].val1 * 10) / 100;
				if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
					heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
				if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
					heal = 0;
			}
			//if(bl->type == BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
			//	heal = 0;	/* 黄金蟲カード（ヒール量０） */

			battle_heal(NULL,bl,heal,0,0);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = 9 + (skilllv/2) * 3;
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_TUNABELLY:	/* 大トロ */
		int heal = (int)(5 + skilllv * 5 + (skilllv>=5? 20: (skilllv==4? 10: 0)) * (atn_bignumber)status_get_max_hp(bl) / 100);

		if(sc) {
			if(sc->data[SC_CRITICALWOUND].timer != -1)
				heal = heal * (100 - sc->data[SC_CRITICALWOUND].val1 * 10) / 100;
			if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
				heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
			if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
				heal = 0;
		}
		//if(bl->type == BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
		//	heal = 0;	/* 黄金蟲カード（ヒール量０） */

		battle_heal(NULL,bl,heal,0,0);
		break;
	case SU_SHRIMPARTY:	/* エビパーティー */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// キャロットビート
		if(sd) {
			int nameid, amount, idx = 0;

			nameid = 515;	// ニンジン
			amount = 1;

			idx = pc_search_inventory(sd,nameid);

			if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {	// ニンジン持ってたら消費
				pc_delitem(sd,idx,amount,0,1);
				skill_castend_damage_id(src,bl,SU_LUNATICCARROTBEAT2,skilllv,tick,0);
				break;
			}
		}
		skill_castend_damage_id(src,bl,SU_LUNATICCARROTBEAT,skilllv,tick,0);
		break;
	case ECL_SNOWFLIP:
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_BLEED, -1);
		status_change_end(bl, SC_HELLINFERNO, -1);
		status_change_end(bl, SC_DEEP_SLEEP, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_PEONYMAMY:
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_FROSTMISTY, -1);
		status_change_end(bl, SC_DIAMONDDUST, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_SADAGUI:
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		status_change_end(bl, SC_FEAR, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_SEQUOIADUST:
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_DECREASEAGI, -1);
		status_change_end(bl, SC_REVERSEORCISH, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case EL_CIRCLE_OF_FIRE:	/* サークルオブファイア */
	case EL_FIRE_CLOAK:		/* ファイアークローク */
	case EL_WATER_SCREEN:	/* ウォータースクリーン */
	case EL_WATER_DROP:		/* ウォータードロップ */
	case EL_WIND_STEP:		/* ウィンドステップ */
	case EL_WIND_CURTAIN:	/* ウィンドカーテン */
	case EL_SOLID_SKIN:		/* ソリッドスキン */
	case EL_STONE_SHIELD:	/* ストーンシールド */
	case EL_PYROTECHNIC:	/* パイロテクニック */
	case EL_HEATER:			/* ヒーター */
	case EL_TROPIC:			/* トロピック */
	case EL_AQUAPLAY:		/* アクアプレイ */
	case EL_COOLER:			/* クーラー */
	case EL_CHILLY_AIR:		/* クールエアー */
	case EL_GUST:			/* ガスト */
	case EL_BLAST:			/* ブラスト */
	case EL_WILD_STORM:		/* ワイルドストーム */
	case EL_PETROLOGY:		/* ペトロジー */
	case EL_CURSED_SOIL:	/* カースドソイル */
	case EL_UPHEAVAL:		/* アップヘイバル */
		if(eld && eld->msd) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_FIRE_MANTLE:		/* ファイアーマントル */
	case EL_WATER_BARRIER:		/* ウォーターバリアー */
	case EL_ZEPHYR:				/* ゼファー */
	case EL_POWER_OF_GAIA:		/* パワーオブガイア */
		if(eld && eld->msd) {
			clif_skill_poseffect(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,tick);
			skill_unitsetting(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,0);
		}
		break;
	case NPC_DISSONANCE:
	case NPC_UGLYDANCE:
		sc = status_get_sc(src);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sc && sc->data[SC_DANCING].timer != -1) {
			status_change_end(src,SC_DANCING,-1);
		}
		else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				status_change_start(src,SC_DANCING,skillid,sg->bl.id,0,0,skill_get_time(skillid,skilllv)+1000,0);
			}
		}
		break;
	default:
		printf("skill_castend_nodamage_id: Unknown skill used:%d\n",skillid);
		map_freeblock_unlock();
		return 1;
	}
	map_freeblock_unlock();

	return 0;
}

/*==========================================
 * スキル使用（詠唱完了、場所指定）
 *------------------------------------------
 */
int skill_castend_pos(int tid, unsigned int tick, int id, void *data)
{
	struct block_list *src = map_id2bl(id);
	struct map_session_data *src_sd  = NULL;
	struct mob_data         *src_md  = NULL;
	struct homun_data       *src_hd  = NULL;
	struct merc_data        *src_mcd = NULL;
	struct elem_data        *src_eld = NULL;
	struct unit_data        *src_ud  = NULL;
	struct status_change    *sc      = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, src_ud = unit_bl2ud(src));

	if( src->prev == NULL )
		return 0;

	src_sd  = BL_DOWNCAST( BL_PC ,  src );
	src_md  = BL_DOWNCAST( BL_MOB,  src );
	src_hd  = BL_DOWNCAST( BL_HOM,  src );
	src_mcd = BL_DOWNCAST( BL_MERC, src );
	src_eld = BL_DOWNCAST( BL_ELEM, src );

	sc = status_get_sc(src);

	if( src_ud->skilltimer != tid )	// タイマIDの確認
		return 0;
	if(src_sd && src_ud->skilltimer != -1 && pc_checkskill(src_sd,SA_FREECAST) > 0) {
		src_sd->speed = src_sd->prev_speed;
		clif_updatestatus(src_sd,SP_SPEED);
	}
	src_ud->skilltimer = -1;

	do {
		int range;

		if(unit_isdead(src))
			break;

		if(src_md) {
			if(src_md->sc.data[SC_ROKISWEIL].timer != -1)
				break;
			if(!(mob_db[src_md->class_].mode & MD_BOSS) && src_md->sc.data[SC_HERMODE].timer != -1)
				break;
			if((src_md->sc.opt1 > OPT1_NORMAL  && src_md->sc.opt1 != OPT1_BURNNING) || src_md->sc.data[SC_SILENCE].timer != -1 || src_md->sc.data[SC_STEELBODY].timer != -1)
				break;
			if(src_md->sc.data[SC_AUTOCOUNTER].timer != -1 && src_md->ud.skillid != KN_AUTOCOUNTER)
				break;
			if(src_md->sc.data[SC_BLADESTOP].timer != -1)
				break;
			if(src_md->sc.data[SC_BERSERK].timer != -1)
				break;
			if(src_md->sc.data[SC_DEATHBOUND].timer != -1 && src_md->ud.skillid != RK_DEATHBOUND)
				break;
			if(src_md->sc.data[SC_STASIS].timer != -1 && skill_get_skill_type(src_md->ud.skillid) == BF_MAGIC)
				break;
			if(src_md->sc.data[SC__SHADOWFORM].timer != -1)
				break;
			if(src_md->sc.data[SC__MANHOLE].timer != -1)
				break;
			if(src_md->sc.data[SC__INVISIBILITY].timer != -1 && src_md->ud.skillid != SC_INVISIBILITY)
				break;
			if(src_md->sc.data[SC__IGNORANCE].timer != -1)
				break;
		}

		if( (src_sd && !battle_config.pc_skill_reiteration) ||
		    (src_md && !battle_config.monster_skill_reiteration) )
		{
			if( skill_get_unit_flag(src_ud->skillid,src_ud->skilllv)&UF_NOREITERATION &&
			    skill_check_unit_range(src->m,src_ud->skillx,src_ud->skilly,src_ud->skillid,src_ud->skilllv) )
				break;
		}
		if( (src_sd && battle_config.pc_skill_nofootset) ||
		    (src_md && battle_config.monster_skill_nofootset) )
		{
			if( skill_get_unit_flag(src_ud->skillid,src_ud->skilllv)&UF_NOFOOTSET &&
			    skill_check_unit_range2(src->m,src_ud->skillx,src_ud->skilly,src_ud->skillid,src_ud->skilllv) )
				break;
		}
		if( (src_sd && battle_config.pc_land_skill_limit) ||
		    (src_md && battle_config.monster_land_skill_limit) )
		{
			int maxcount = skill_get_maxcount(src_ud->skillid,src_ud->skilllv);
			if(maxcount > 0 && skill_count_unitgroup(src_ud,src_ud->skillid) >= maxcount)
				break;
		}

		range = skill_get_fixed_range(src,src_ud->skillid,src_ud->skilllv);
		if(src_sd)
			range += battle_config.pc_skill_add_range;
		else if(src_md)
			range += battle_config.mob_skill_add_range;

		if(!src_sd || battle_config.check_skillpos_range) {	// 発動元がPCで射程チェック無しならこの処理は無視してクライアントの情報を信頼する
			if(range < path_distance(src->x,src->y,src_ud->skillx,src_ud->skilly)) {
				if(src_sd && battle_config.skill_out_range_consume)
					skill_check_condition(&src_sd->bl,1);	// アイテム消費
				break;
			}
		}

		// PC,HOM,MERC,ELEMは使用条件チェック
		if(src_sd || src_hd || src_mcd || src_eld) {
			if(!skill_check_condition(src,1))
				break;
		}
		if(src_sd) {
			src_sd->skill_item.id      = -1;
			src_sd->skill_item.lv      = -1;
			src_sd->skill_item.flag    = 0;
		}

		if(src_sd && battle_config.pc_skill_log)
			printf("PC %d skill castend skill=%d\n",src->id,src_ud->skillid);
		if(src_md && battle_config.mob_skill_log)
			printf("MOB skill castend skill=%d, class = %d\n",src_ud->skillid,src_md->class_);

		unit_stop_walking(src,0);

		if(src_sd) {
			int cooldown = skill_cooldownfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);
			int delay    = skill_delayfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);

			if(cooldown > 0) {
				int nameid = skill_get_skilldb_id(src_ud->skillid);
				if(nameid > 0) {
					src_sd->skillcooldown[nameid] = tick + cooldown;
					clif_skill_cooldown(src_sd, src_ud->skillid, cooldown);
				}
			}
#if PACKETVER > 20081126
			if(delay > 0)
				clif_status_change(&src_sd->bl, SI_ACTIONDELAY, 1, delay, 0, 0, 0);
#endif
		}

		// エモ、チャット
		if(src_md && src_md->skillidx != -1)
		{
			short emotion = mob_db[src_md->class_].skill[src_md->skillidx].emotion;
			short msg_id = mob_db[src_md->class_].skill[src_md->skillidx].msg_id;
			if(emotion >= 0)
				clif_emotion(&src_md->bl,emotion);
			if(msg_id > 0)
				mob_talk(src_md,msg_id);
		}
		skill_castend_pos2(src,src_ud->skillx,src_ud->skilly,src_ud->skillid,src_ud->skilllv,tick,0);

		// スキル使用で発動するオートスペル,アクティブアイテム
		if(src_sd) {
			bonus_autospellskill_start(src,src,src_ud->skillid,tick,0);
			bonus_activeitemskill_start(src_sd,src_ud->skillid,tick);
		}

		if(src_md)
			src_md->skillidx = -1;

		if(sc && sc->data[SC_CAMOUFLAGE].timer != -1 && src_ud->skillid != RA_CAMOUFLAGE) {
			status_change_end(src,SC_CAMOUFLAGE,-1);
		}
		return 0;
	} while(0);

	// スキル使用失敗
	src_ud->canact_tick  = tick;
	src_ud->canmove_tick = tick;
	if(src_sd) {
		clif_skill_fail(src_sd,src_ud->skillid,0,0,0);
		src_sd->skill_item.id     = -1;
		src_sd->skill_item.lv     = -1;
		src_sd->skill_item.flag   = 0;
	} else if(src_md) {
		src_md->skillidx = -1;
	}

	return 0;
}

/*==========================================
 * スキル使用（詠唱完了、場所指定の実際の処理）
 *------------------------------------------
 */
int skill_castend_pos2( struct block_list *src, int x,int y,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, src);

	sd = BL_DOWNCAST( BL_PC, src );

	switch(skillid) {
	case WZ_METEOR:
	case WZ_ICEWALL:
	case MO_BODYRELOCATION:
	case AM_CANNIBALIZE:
	case AM_SPHEREMINE:
	case CR_CULTIVATION:
	case RA_CLUSTERBOMB:
	case RA_FIRINGTRAP:
	case RA_ICEBOUNDTRAP:
	case SC_ESCAPE:
	case SU_CN_METEOR:
		break;
	default:
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
	}

	switch(skillid)
	{
	case AC_SHOWER:				/* アローシャワー */
	case MA_SHOWER:
		{
#ifndef PRE_RENEWAL
			int ar = (skilllv>5? 2: 1);
#else
			int ar = 1;
#endif
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case PR_BENEDICTIO:			/* 聖体降福 */
		skill_area_temp[1] = src->id;
		map_foreachinarea(skill_area_sub,
			src->m,x-1,y-1,x+1,y+1,BL_PC,
			src,skillid,skilllv,tick, flag|BCT_ALL|1,
			skill_castend_nodamage_id);
		map_foreachinarea(skill_area_sub,
			src->m,x-1,y-1,x+1,y+1,BL_CHAR,
			src,skillid,skilllv,tick, flag|BCT_ALL|1,
			skill_castend_damage_id);
		break;

	case BS_HAMMERFALL:			/* ハンマーフォール */
		skill_addtimerskill(src,tick+skill_get_time(skillid,skilllv),0,x,y,skillid,skilllv,BF_WEAPON,flag|BCT_ENEMY|2);
		break;

	case HT_DETECTING:				/* ディテクティング */
		map_foreachinarea(status_change_timer_sub,src->m,x-3,y-3,x+3,y+3,BL_CHAR,src,SC_SIGHT,skilllv,tick);
		break;

	case WZ_ICEWALL:			/* アイスウォール */
		if(map[src->m].flag.noicewall) {
			if(sd)
				clif_skill_fail(sd,skillid,0,0,0);
		} else {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case MG_SAFETYWALL:			/* セイフティウォール */
	case MG_FIREWALL:			/* ファイアーウォール */
	case MG_THUNDERSTORM:		/* サンダーストーム */
	case AL_PNEUMA:				/* ニューマ */
	case WZ_FIREPILLAR:			/* ファイアピラー */
	case WZ_VERMILION:			/* ロードオブヴァーミリオン */
	case WZ_FROSTNOVA:          /* フロストノヴァ */ 
	case WZ_HEAVENDRIVE:		/* ヘヴンズドライブ */
	case WZ_QUAGMIRE:			/* クァグマイア */
	case PR_SANCTUARY:			/* サンクチュアリ */
	case PR_MAGNUS:				/* マグヌスエクソシズム */
	case CR_GRANDCROSS:			/* グランドクロス */
	case NPC_GRANDDARKNESS:			/* グランドダークネス */
	case AS_VENOMDUST:			/* ベナムダスト */
	case AM_DEMONSTRATION:		/* デモンストレーション */
	case PF_SPIDERWEB:			/* スパイダーウェブ */
	case PF_FOGWALL:			/* ウォールオブフォグ */
	case NJ_TATAMIGAESHI:		/* 畳返し */
	case NJ_BAKUENRYU:			/* 龍炎陣 */
	case NJ_HYOUSYOURAKU:		/* 氷柱落し */
	case NPC_EVILLAND:			/* イービルランド */
	case NPC_VENOMFOG:			/* ベナムフォグ */
	case NPC_FLAMECROSS:		/* フレイムクロス */
	case NPC_HELLBURNING:		/* ヘルバーニング */
	case GC_POISONSMOKE:		/* ポイズンスモーク */
	case SC_MANHOLE:			/* マンホール */
	case SC_DIMENSIONDOOR:		/* ディメンションドア */
	case SC_CHAOSPANIC:			/* カオスパニック */
	case SC_MAELSTROM:			/* メイルストーム */
	case SC_BLOODYLUST:			/* ブラッディラスト */
	case WM_REVERBERATION:		/* 振動残響 */
	case WM_POEMOFNETHERWORLD:	/* 地獄の歌 */
	case SO_EARTHGRAVE:			/* アースグレイブ */
	case SO_DIAMONDDUST:		/* ダイヤモンドダスト */
	case SO_PSYCHIC_WAVE:		/* サイキックウェーブ */
	case SO_CLOUD_KILL:			/* クラウドキル */
	case SO_WARMER:				/* ウォーマー */
	case SO_VACUUM_EXTREME:		/* バキュームエクストリーム */
	case SO_FIRE_INSIGNIA:		/* ファイアーインシグニア */
	case SO_WATER_INSIGNIA:		/* ウォーターインシグニア */
	case SO_WIND_INSIGNIA:		/* ウィンドインシグニア */
	case SO_EARTH_INSIGNIA:		/* アースインシグニア */
	case GN_THORNS_TRAP:		/* ソーントラップ */
	case GN_DEMONIC_FIRE:		/* デモニックファイアー */
	case GN_HELLS_PLANT:		/* ヘルズプラント */
	case KO_HUUMARANKA:			/* 風魔手裏剣乱華 */
	case SU_NYANGGRASS:			/* ニャングラス */
	case MA_SKIDTRAP:
	case MA_LANDMINE:
	case MA_SANDMAN:
	case MA_FREEZINGTRAP:
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case HT_SKIDTRAP:			/* スキッドトラップ */
	case HT_LANDMINE:			/* ランドマイン */
	case HT_ANKLESNARE:			/* アンクルスネア */
	case HT_SHOCKWAVE:			/* ショックウェーブトラップ */
	case HT_SANDMAN:			/* サンドマン */
	case HT_FLASHER:			/* フラッシャー */
	case HT_FREEZINGTRAP:		/* フリージングトラップ */
	case HT_BLASTMINE:			/* ブラストマイン */
	case HT_CLAYMORETRAP:		/* クレイモアトラップ */
	case HT_TALKIEBOX:			/* トーキーボックス */
		if(sd) {
			int i, nameid, amount, idx, trapid = 0;
			for(i = 0; i < 10; i++) {
				nameid = skill_db[skill_get_skilldb_id(skillid)].itemid[i];
				amount = skill_db[skill_get_skilldb_id(skillid)].amount[i];
				if(nameid <= 0 || amount <= 0)
					continue;
				idx = pc_search_inventory(sd,nameid);

				// トラップ研究を習得中で設置用トラップが足りなかった場合
				if((idx < 0 || sd->status.inventory[idx].amount < amount) &&
					pc_checkskill(sd,RA_RESEARCHTRAP) && nameid == 1065)
				{
					// 改良型設置用トラップを検索
					nameid = 7940;
					amount = 1;
					idx = pc_search_inventory(sd,nameid);
				}

				if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {
					pc_delitem(sd,idx,amount,0,1);
					// 消費したのがトラップ系アイテムの場合
					if(nameid == 1065 || nameid == 7940)
						trapid = nameid;
				}
			}
			skill_unitsetting(src,skillid,skilllv,x,y,trapid);
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case HW_GRAVITATION:		/* グラビテーションフィールド */
		{
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,x,y,0);
			if(sg) {
				struct unit_data *ud = unit_bl2ud(src);
				if(ud && DIFF_TICK(ud->canact_tick, tick) < 5000) {
					// 発動後5秒間はリログ禁止
					ud->canact_tick = tick + 5000;
				}
				status_change_start(src,SC_GRAVITATION_USER,skilllv,0,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case RG_GRAFFITI:			/* グラフィティ */
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,x,y,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_GROUNDDRIFT:			/* グラウンドドリフト */
		if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if(idx >= 0 && sd->inventory_data[idx]) {
				int nameid = sd->inventory_data[idx]->nameid;
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(nameid <= 0)
					break;
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
					break;
				skill_unitsetting(src,skillid,skilllv,x,y,nameid);
			}
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case SA_VOLCANO:		/* ボルケーノ */
	case SA_DELUGE:			/* デリュージ */
	case SA_VIOLENTGALE:		/* バイオレントゲイル */
	case SA_LANDPROTECTOR:		/* ランドプロテクター */
	case NJ_SUITON:			/* 水遁 */
	case NJ_KAENSIN:		/* 火炎陣 */
		skill_clear_element_field(src);	// 既に自分が発動している属性場をクリア
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case WZ_METEOR:			/* メテオストーム */
	case SU_CN_METEOR:	/* イヌハッカメテオ */
		{
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int interval = (skilllv > 10)? 2500: 1000;
			int loop = skilllv / 2 + 2;
			for(i=0; i < loop; i++) {
				if(skilllv > 10) {
					tmpx = x + (atn_rand()%29 - 14);
					tmpy = y + (atn_rand()%29 - 14);
				} else {
					tmpx = x + (atn_rand()%7 - 3);
					tmpy = y + (atn_rand()%7 - 3);
				}
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skillid,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skillid,skilllv,-1,0);
		}
		break;

	case WZ_STORMGUST:          /* ストームガスト */ 
		{
			int i, j;

			// ユニットを南西→北東まで81個作る
			for(i = 0; i < 9; i++) {
				for(j = 0; j < 9; j++) {
					skill_unitsetting(src,skillid,skilllv,x-4+i,y-4+j,0);
				}
			}
		}
		break;

	case AL_WARP:				/* ワープポータル */
		if(sd) {
			const char *p[3];
			int i = 0;
			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportalで禁止
					break;
			} else {
				if(map[sd->bl.m].flag.noteleport)	// noteleportで禁止
					break;
			}
			for(i=0; i<3; i++) {
				if(sd->ud.skilllv > i+1 && i < MAX_PORTAL_MEMO)
					p[i] = sd->status.memo_point[i].map;
				else
					p[i] = "";
			}
			clif_skill_warppoint(sd,sd->ud.skillid,sd->status.save_point.map, p[0], p[1], p[2]);
		}
		break;
	case HW_GANBANTEIN:			/* ガンバンテイン */
		if(atn_rand()%100 < 80) {
			map_foreachinarea(skill_delunit_by_ganbantein,src->m,x-1,y-1,x+1,y+1,BL_SKILL);
		} else if(sd) {
			clif_skill_fail(sd,skillid,0,0,0);
		}
		break;
	case MO_BODYRELOCATION:			/* 残影 */
		{
			struct status_change *sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				if(sd) {
					sd->skillstatictimer[MO_EXTREMITYFIST] = tick + 2000;
				}
#if PACKETVER < 20111025
				clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
				unit_movepos(src,x,y,1);
#else
				unit_movepos(src,x,y,2);
#endif
			}
		}
		break;
	case AM_CANNIBALIZE:	/* バイオプラント */
		if(sd) {
			int n, id = 0;
			const int summons[5] = { 1589, 1579, 1575, 1555, 1590 };
			struct mob_data *tmpmd = NULL;

			n  = (skilllv > 5)? 4: skilllv - 1;
			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, summons[n], 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id = sd->bl.id;
				tmpmd->guild_id  = status_get_guild_id(src);
				tmpmd->hp        = 1500 + skilllv * 200 + sd->status.base_level * 10;

				// 非移動でアクティブで反撃する[0x0:非移動 0x1:移動 0x4:ACT 0x8:非ACT 0x40:反撃無 0x80:反撃有]
				tmpmd->mode = MD_AGGRESSIVE + MD_CANATTACK;

				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.special_mob_ai = 1;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_CULTIVATION:	/* 植物栽培 */
		if(sd) {
			int id, n = (skilllv >= 2)? 1: 0;
			const int summons[2][6] = {
				{ 1084, 1085, 1084, 1085, 1084, 1085 },
				{ 1078, 1079, 1080, 1081, 1082, 1083 }
			};
			int i = skilllv - 1;
			int j = pc_search_inventory(sd,skill_db[skillid].itemid[i]);
			struct mob_data *tmpmd = NULL;

			if(j < 0 || skill_db[skillid].itemid[i] <= 0 || sd->inventory_data[j] == NULL ||
				sd->status.inventory[j].amount < skill_db[skillid].amount[i] ||
				map_count_oncell(src->m,x,y,BL_MOB) || atn_rand()%100 < 50)
			{
				clif_skill_fail(sd,skillid,0,0,0);
				break;
			}

			id = mob_once_spawn(sd, sd->bl.m, x, y, "--ja--", summons[n][atn_rand()%6], 1, "");

			if((tmpmd = map_id2md(id)) != NULL)
				tmpmd->deletetimer = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case AM_SPHEREMINE:	/* スフィアーマイン */
		if(sd) {
			int id = 0;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, 1142, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->hp           = 2000 + skilllv * 400;
				tmpmd->def_ele      = 40 + ELE_WATER;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.spheremine_no_drop;
				tmpmd->state.noexp  = battle_config.spheremine_no_exp;
				tmpmd->state.nomvp  = battle_config.spheremine_no_mvp;
				tmpmd->state.special_mob_ai = 2;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_SLIMPITCHER:
		if(sd) {
			int i = (skilllv > 10)? 9: skilllv - 1;
			int j, itemid;

			if(battle_config.slimpitcher_nocost && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg) {
				const int potion[10] = { 501, 501, 501, 501, 501, 503, 503, 503, 503, 504 };
				itemid = potion[i];
			} else {
				itemid = skill_db[skillid].itemid[i];
			}
			j = pc_search_inventory(sd,itemid);
			if(j < 0 || itemid <= 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[skillid].amount[i]) {
				clif_skill_fail(sd,skillid,0,0,0);
				return 1;
			}
			sd->state.potionpitcher_flag = 1;
			sd->potion.hp = 0;
			if(sd->inventory_data[j]->use_script) {
				run_script(sd->inventory_data[j]->use_script,0,sd->bl.id,0);
			}
			pc_delitem(sd,j,skill_db[skillid].amount[i],0,1);
			sd->state.potionpitcher_flag = 0;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			if(sd->potion.hp > 0) {
				map_foreachinarea(skill_area_sub,
					src->m,x-3,y-3,x+3,y+3,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
		}
		break;
	case NJ_HUUMA:		/* 風魔手裏剣投げ */
		skill_area_temp[0] = 0;
		skill_area_temp[1] = src->id;
		map_foreachinarea(skill_area_sub,
			src->m,x-1,y-1,x+1,y+1,(BL_CHAR|BL_SKILL),
			src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
			skill_castend_damage_id);
		break;
	case NJ_RAIGEKISAI:	/* 雷撃砕 */
#ifndef PRE_RENEWAL
		clif_skill_nodamage(src,src,skillid,skilllv,1);
#endif
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NJ_SHADOWJUMP:	/* 影跳び */
		if(sd && map[sd->bl.m].flag.gvg) {
			clif_skill_fail(sd,skillid,0,0,0);
		} else {
			struct status_change *sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// 崖打ち可能セルは無視して移動
				if(map_getcellp(&map[src->m],x,y,CELL_CHKPASS)) {
					unit_movepos(src,x,y,0x21);
					status_change_end(src, SC_HIDING, -1);
				}
			}
		}
		break;
	case RK_WINDCUTTER:	/* ウィンドカッター */
		{
			int dir = path_calc_dir(src,x,y);
			skill_area_temp[1] = src->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],6,2,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case RK_DRAGONBREATH:		/* ファイアードラゴンブレス */
	case RK_DRAGONBREATH_WATER:	/* ウォータードラゴンブレス */
		{
			int ar = (skilllv - 1) / 3 + 1;

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AB_EPICLESIS:			/* エピクレシス */
		{
			int ar = skill_get_unit_range(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_PC,
				src,ALL_RESURRECTION,3,tick,flag|BCT_NOENEMY|1,
				skill_castend_nodamage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case WL_COMET:				/* コメット */
		{
			int ar = 7;
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_EARTHSTRAIN:		/* アースストレイン */
		{
			int dir = (src->x == x && src->y == y)? 6: path_calc_dir(src,x,y);
			int tmpx, tmpy;
			int addx = 0, addy = 0;
			int i, loop = skilllv + 4;

			// 縦を優先
			addy = diry[dir];
			addx = (addy == 0)? dirx[dir]: 0;

			// 初期位置を指定
			tmpx = src->x + addx;
			tmpy = src->y + addy;

			clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
			for(i = 1; i < loop; i++) {
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,flag);
				tmpx += addx;
				tmpy += addy;
			}
		}
		break;
	case RA_DETONATOR:				/* デトネイター */
		clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		map_foreachinarea(skill_detonator,src->m,x-3,y-3,x+3,y+3,BL_SKILL,src);
		break;
	case RA_ELECTRICSHOCKER:	/* エレクトリックショッカー */
	case RA_CLUSTERBOMB:		/* クラスターボム */
	case RA_MAGENTATRAP:		/* マゼンタトラップ */
	case RA_COBALTTRAP:			/* コバルトトラップ */
	case RA_MAIZETRAP:			/* メイズトラップ */
	case RA_VERDURETRAP:		/* ヴェルデュールトラップ */
	case RA_FIRINGTRAP:			/* ファイアリングトラップ */
	case RA_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		if(sd)
			skill_unitsetting(src,skillid,skilllv,x,y,7940);
		else
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NC_COLDSLOWER:	/* コールドスローワー */
		{
			int ar = 1 + skilllv;
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_ARMSCANNON:		/* アームズキャノン */
		{
			int ar = 4 - skilllv;
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_SILVERSNIPER:	/* FAW シルバースナイパー */
		if(sd) {
			int id;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, 2042, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.special_mob_ai = 1;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case NC_MAGICDECOY:		/* FAW マジックデコイ */
		if(sd) {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			clif_magicdecoy_list(sd,skilllv,x,y);
		}
		break;
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
		skill_addtimerskill(src,tick+1000,0,x,y,skillid,skilllv,0,flag);
		break;
	case LG_OVERBRAND:		/* オーバーブランド */
		{
			int dir = path_calc_dir(src,x,y);
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],6,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,skill_castend_damage_id
			);
			skill_addtimerskill(src,tick+200,0,x,y,LG_OVERBRAND_BRANDISH,skilllv,0,flag);
		}
		break;
	case LG_RAYOFGENESIS:	/* レイオブジェネシス */
		skill_area_temp[1] = src->id;
		skill_area_temp[2] = x;
		skill_area_temp[3] = y;
		map_foreachinarea(skill_area_sub,
			src->m,x-5,y-5,x+5,y+5,(BL_CHAR|BL_SKILL),
			src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
			skill_castend_damage_id);
		break;
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
		{
			int ar = (skilllv + 1) / 2;
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WM_DOMINION_IMPULSE:		/* ドミニオンインパルス */
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		map_foreachinarea(skill_dominion_impulse,src->m,x-5,y-5,x+5,y+5,BL_SKILL);
		break;
	case WM_SEVERE_RAINSTORM:	/* シビアレインストーム */
		if(sd) {
			int cost = skill_get_arrow_cost(skillid,skilllv);
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
				break;
		}
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case WM_LULLABY_DEEPSLEEP:		/* 安らぎの子守唄 */
		{
			int ar = 4 + skilllv;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_GREAT_ECHO:			/* グレートエコー */
		{
			int ar = (skilllv + 4) / 2;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		{
			int ar = (skilllv + 1) / 2;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_CRAZYWEED:		/* クレイジーウィード */
		{
			int tmpx, tmpy, i, num;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			num = skill_get_num(skillid,skilllv);
			for(i=0; i<num; i++) {
				tmpx = x + (atn_rand()%9 - 4);
				tmpy = y + (atn_rand()%9 - 4);
				skill_addtimerskill(src,tick+i*200,0,tmpx,tmpy,skillid,skilllv,0,0);
			}
		}
		break;
	case GN_FIRE_EXPANSION:		/* ファイアーエクスパンション */
		if(sd) {
			int i = (skilllv > skill_get_max(skillid))? skill_get_max(skillid) - 1: skilllv - 1;
			int id, j;

			if(i >= 10) {
				i = 9;
			}
			id = skill_get_skilldb_id(skillid);
			j  = pc_search_inventory(sd,skill_db[id].itemid[i]);

			if(j < 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[id].amount[i]) {
				clif_skill_fail(sd,skillid,0,0,0);
				break;
			}
			pc_delitem(sd,j,skill_db[id].amount[i],0,1);
		}
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		map_foreachinarea(skill_fire_expansion,src->m,x-2,y-2,x+2,y+2,BL_SKILL,src,skilllv,tick);
		break;
	case KO_BAKURETSU:		/* 爆裂苦無 */
		{
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-1,y-1,x+1,y+1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_MUCHANAGE:		/* 無茶投げ */
		{
			int ar = (skilllv<10)? 1: 2;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
		}
		break;
	case KO_MAKIBISHI:			/* 撒菱 */
		{
			int i;
			for(i = 0; i < skilllv+2; i++) {
				x = src->x - 1 + atn_rand()%3;
				y = src->y - 1 + atn_rand()%3;
				skill_unitsetting(src,skillid,skilllv,x,y,0);
			}
		}
		break;
	case KO_ZENKAI:		/* 術式全開 */
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case SU_LOPE:		/* ニャンジャンプ */
		if( !map[src->m].flag.turbo && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
		    map_getcell(src->m,x,y,CELL_CHKPASS) && !map_count_oncell(src->m,x,y,BL_PC|BL_MOB|BL_NPC)
		) {
			unit_movepos(src,x,y,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,0,0,0);
		break;

	}
	return 0;
}

/*==========================================
 * スキル使用（詠唱完了、map指定）
 *------------------------------------------
 */
void skill_castend_map( struct map_session_data *sd,int skill_num, const char *mapname)
{
	nullpo_retv(sd);

	if( sd->bl.prev == NULL || unit_isdead(&sd->bl) )
		return;

	// 不正パケット
	if(skill_num != sd->ud.skillid)
		return;

	if( (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->sc.option&OPTION_HIDE )
		return;

	// スキルが使えない状態異常中
	if( sd->sc.data[SC_SILENCE].timer != -1 ||
	    sd->sc.data[SC_ROKISWEIL].timer != -1 ||
	    sd->sc.data[SC_HERMODE].timer != -1 ||
	    sd->sc.data[SC_AUTOCOUNTER].timer != -1 ||
	    sd->sc.data[SC_DEATHBOUND].timer != -1 ||
	    sd->sc.data[SC_STEELBODY].timer != -1 ||
	    sd->sc.data[SC_BERSERK].timer != -1 ||
	    (skill_num != CG_LONGINGFREEDOM && sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_LONGINGFREEDOM].timer == -1) ||
	    sd->sc.data[SC_KINGS_GRACE].timer != -1 ||
	    sd->sc.data[SC_OBLIVIONCURSE].timer != -1 ||
	    sd->sc.data[SC__IGNORANCE].timer != -1)
		return;

	unit_stopattack(&sd->bl);

	if(battle_config.pc_skill_log)
		printf("PC %d skill castend skill =%d map=%s\n",sd->bl.id,skill_num,mapname);
	unit_stop_walking(&sd->bl,0);

	if(strcmp(mapname,"cancel") == 0)
		return;

	switch(skill_num) {
	case AL_TELEPORT:		/* テレポート */
		{
			int alive = 1;
			map_foreachinarea(skill_landprotector,sd->bl.m,sd->bl.x,sd->bl.y,sd->bl.x,sd->bl.y,BL_SKILL,AL_TELEPORT,&alive);
			if(alive) {
				if(strcmp(mapname,"Random") == 0)
					pc_randomwarp(sd,3);
				else
					pc_setpos(sd,sd->status.save_point.map,sd->status.save_point.x,sd->status.save_point.y,3);
			}
		}
		break;
	case AL_WARP:			/* ワープポータル */
		{
			const struct point *p[MAX_PORTAL_MEMO+1];
			struct skill_unit_group *group;
			int i, x = 0, y = 0;

			p[0] = &sd->status.save_point;
			for(i=0; i<MAX_PORTAL_MEMO; i++) {
				p[i+1] = &sd->status.memo_point[i];
			}
			if(battle_config.pc_land_skill_limit) {
				int maxcount = skill_get_maxcount(sd->ud.skillid,sd->ud.skilllv);
				if(maxcount > 0 && skill_count_unitgroup(&sd->ud,sd->ud.skillid) >= maxcount) {
					clif_skill_fail(sd,sd->ud.skillid,0,0,0);
					sd->ud.canact_tick = sd->ud.canmove_tick = gettick();
					break;
				}
			}
			for(i=0; i<sd->ud.skilllv; i++) {
				if(strcmp(mapname,p[i]->map) == 0) {
					x = p[i]->x;
					y = p[i]->y;
					break;
				}
			}
			if(x == 0 || y == 0)	// 不正パケット？
				break;

			if(!battle_config.pc_skill_reiteration) {
				if( skill_get_unit_flag(sd->ud.skillid,sd->ud.skilllv)&UF_NOREITERATION &&
				    skill_check_unit_range(sd->bl.m,sd->ud.skillx,sd->ud.skilly,sd->ud.skillid,sd->ud.skilllv) )
					break;
			}
			if(battle_config.pc_skill_nofootset) {
				if( skill_get_unit_flag(sd->ud.skillid,sd->ud.skilllv)&UF_NOFOOTSET &&
				    skill_check_unit_range2(sd->bl.m,sd->ud.skillx,sd->ud.skilly,sd->ud.skillid,sd->ud.skilllv) )
					break;
			}

			if(!skill_check_condition(&sd->bl,3))
				break;
			if((group = skill_unitsetting(&sd->bl,sd->ud.skillid,sd->ud.skilllv,sd->ud.skillx,sd->ud.skilly,0)) == NULL)
				break;
			group->valstr = (char *)aCalloc(16, sizeof(char)); // max map_name is 15 char + NULL
			memcpy(group->valstr, mapname, 15);
			group->val2 = (x<<16)|y;
		}
		break;
	}

	return;
}

/*==========================================
 * スキルユニット設定処理
 *------------------------------------------
 */
struct skill_unit_group *skill_unitsetting( struct block_list *src, int skillid,int skilllv,int x,int y,int flag)
{
	struct skill_unit_group *group;
	int i,limit,val1=0,val2=0,val3=0,on_flag=0,mael_flag=1;
	int target,interval,range,unit_flag,unit_id;
	struct skill_unit_layout *layout;
	struct map_session_data *sd = NULL;
	unsigned int tick = gettick();

	nullpo_retr(0, src);

	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;

	limit     = skill_get_time(skillid,skilllv);
	range     = skill_get_unit_range(skillid,skilllv);
	interval  = skill_get_unit_interval(skillid);
	target    = skill_get_unit_target(skillid);
	unit_flag = skill_get_unit_flag(skillid,skilllv);
	layout    = skill_get_unit_layout(skillid,skilllv,src,x,y);
	unit_id   = skill_get_unit_id(skillid,0);

	if(unit_flag&UF_DEFNOTENEMY && battle_config.defnotenemy)
		target = BCT_NOENEMY;

	switch (skillid) {
	case MG_SAFETYWALL:			/* セイフティウォール */
#ifndef PRE_RENEWAL
		val1 = 13000+300*skilllv;
		if(sd) val1 += sd->status.max_sp;
#endif
		val2 = skilllv+1;
		break;
	case WZ_METEOR:
		/* メテオストーム(オーバーレベル) */
		if(src->type == BL_MOB && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
			range = 10;
		break;
	case WZ_VERMILION:
		/* ロードオブヴァーミリオン(オーバーレベル) */
		if(src->type == BL_MOB && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
			range = 20;
		break;
	case MG_FIREWALL:			/* ファイアーウォール */
	case NPC_FLAMECROSS:		/* フレイムクロス */
		val2 = 4+skilllv;
		break;
	case AL_WARP:				/* ワープポータル */
		val1 = skilllv+6;
		if(flag)
			unit_id = skill_get_unit_id(skillid,1);
		else
			limit=2000;
		break;
	case PR_SANCTUARY:			/* サンクチュアリ */
		val1 = skilllv*2+6;
		val2 = skill_fix_heal(src, NULL, skillid, ((skilllv > 6)? 777: skilllv * 100));
		interval = interval + 500;
		break;
	case WZ_FIREPILLAR:			/* ファイアーピラー */
		if(flag) {
			unit_id = skill_get_unit_id(skillid,1);
			limit = 150;
		}
		break;
	case HT_SKIDTRAP:			/* スキッドトラップ */
	case MA_SKIDTRAP:
		val1 = src->x;
		val2 = src->y;
		val3 = flag;		// 罠アイテムID
		if(map[src->m].flag.gvg)
			limit <<= 2;
		break;
	case HT_LANDMINE:		/* ランドマイン */
	case HT_ANKLESNARE:		/* アンクルスネア */
	case HT_SHOCKWAVE:		/* ショックウェーブトラップ */
	case HT_SANDMAN:		/* サンドマン */
	case HT_FLASHER:		/* フラッシャー */
	case HT_FREEZINGTRAP:	/* フリージングトラップ */
	case HT_BLASTMINE:		/* ブラストマイン */
	case HT_CLAYMORETRAP:	/* クレイモアトラップ */
	case HT_TALKIEBOX:		/* トーキーボックス */
	case MA_LANDMINE:
	case MA_SANDMAN:
	case MA_FREEZINGTRAP:
		val3 = flag;		// 罠アイテムID
		if(map[src->m].flag.gvg)
			limit <<= 2;
		break;
	case BA_WHISTLE:			/* 口笛 */
#ifdef PRE_RENEWAL
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON)>>1;
		val2 = status_get_agi(src)/10;
#else
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON)>>1;
		val2 = status_get_agi(src)/15;
#endif
		break;
	case DC_HUMMING:			/* ハミング */
#ifdef PRE_RENEWAL
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON)>>1;
		val2 = status_get_dex(src)/10;
#else
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON);
		val2 = status_get_dex(src)/15;
#endif
		break;
	case DC_DONTFORGETME:		/* 私を忘れないで… */
		val1 = status_get_dex(src)/10 + 3*skilllv + 5;
		val2 = status_get_agi(src)/10 + 3*skilllv + 5;
		if(sd){
			val1 += pc_checkskill(sd,DC_DANCINGLESSON);
			val2 += pc_checkskill(sd,DC_DANCINGLESSON);
		}
		break;
	case BA_POEMBRAGI:			/* ブラギの詩 */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = (status_get_dex(src)/10) << 16;
		val2 |= status_get_int(src)/5;
		break;
	case BA_APPLEIDUN:			/* イドゥンの林檎 */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = status_get_vit(src);
		val3 = 0;
		break;
	case DC_SERVICEFORYOU:		/* サービスフォーユー */
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON)>>1;
		val2 = status_get_int(src)/10;
		break;
	case BA_ASSASSINCROSS:		/* 夕陽のアサシンクロス */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = (val1/2 + status_get_agi(src)/20) + skilllv;
		break;
	case DC_FORTUNEKISS:		/* 幸運のキス */
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON)>>1;
		val2 = status_get_luk(src)/10;
		break;
	case HP_BASILICA:
		val1 = src->id;
		break;
	case SA_VOLCANO:		/* ボルケーノ */
	case SA_DELUGE:			/* デリュージ */
	case SA_VIOLENTGALE:	/* バイオレントゲイル */
		if(sd) {
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
			{
				// レベルの低いものを使った場合持続時間減少？
				// 属性場の残り時間算出
				limit = sd->sc.data[SC_ELEMENTFIELD].val2 - DIFF_TICK(tick, (unsigned int)sd->sc.data[SC_ELEMENTFIELD].val3);
			} else {
				status_change_start(src,SC_ELEMENTFIELD,1,skill_get_time(skillid,skilllv),tick,0,0,0);
			}
		}
		break;
	case GS_GROUNDDRIFT:	/* グラウンドドリフト */
		{
			const unsigned char drift_id[] = {
				UNT_GROUNDDRIFT_FIRE,
				UNT_GROUNDDRIFT_WIND,
				UNT_GROUNDDRIFT_POISON,
				UNT_GROUNDDRIFT_DARK,
				UNT_GROUNDDRIFT_WATER
			};

			if(flag >= 13203 && flag <= 13207)	// スフィアのアイテムID
				unit_id = drift_id[flag - 13203];
			else
				unit_id = drift_id[atn_rand()%5];
		}
		break;
	case NPC_EVILLAND:		/* イービルランド */
		val1 = (skilllv > 6)? 666: skilllv*100;
		interval += 500;
		break;
	case GC_POISONSMOKE:	/* ポイズンスモーク */
		if(sd) {
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1) {
				val1 = sd->sc.data[SC_POISONINGWEAPON].val2;
				//status_change_end(&sd->bl,SC_POISONINGWEAPON,-1);
			}
		}
		break;
	case RA_ELECTRICSHOCKER:	/* エレクトリックショッカー */
	case RA_CLUSTERBOMB:		/* クラスターボム */
	case RA_MAGENTATRAP:		/* マゼンタトラップ */
	case RA_COBALTTRAP:			/* コバルトトラップ */
	case RA_MAIZETRAP:			/* メイズトラップ */
	case RA_VERDURETRAP:		/* ヴェルデュールトラップ */
	case RA_FIRINGTRAP:			/* ファイアリングトラップ */
	case RA_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		val3 = flag;		// 罠アイテムID
		break;
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
		limit = interval * 10;
		break;
	case LG_BANDING:	/* バンディング */
		limit = 600000;		// 時間切れ無し
		break;
	case KO_ZENKAI:		/* 術式全開 */
		if(sd) {
			// 召喚中の球体の属性に応じてunit_idを変化させる
			switch(sd->elementball.ele) {
				case ELE_WATER:
					unit_id = UNT_ZENKAI_WATER;
					val1    = ELE_WATER;	// val1は属性値
					break;
				case ELE_EARTH:
					unit_id = UNT_ZENKAI_GROUND;
					val1    = ELE_EARTH;	// val1は属性値
					break;
				case ELE_FIRE:
					unit_id = UNT_ZENKAI_FIRE;
					val1    = ELE_FIRE;	// val1は属性値
					break;
				case ELE_WIND:
					unit_id = UNT_ZENKAI_WIND;
					val1    = ELE_WIND;	// val1は属性値
					break;
			}
			// 召喚中の球体の数に応じてlimitが延びる
			limit *= sd->elementball.num;
		} else {
			val1 = ELE_FIRE;	// val1は属性値
		}
		break;
	case EL_FIRE_MANTLE:		/* ファイアーマントル */
		val2 = skilllv;
		break;
	}

	nullpo_retr( NULL, group = skill_initunitgroup(src,layout->count,skillid,skilllv,unit_id,tick) );
	group->limit       = limit;
	group->val1        = val1;
	group->val2        = val2;
	group->val3        = val3;
	group->target_flag = target;
	group->interval    = interval;

	if(skillid == HT_TALKIEBOX || skillid == RG_GRAFFITI) {
		group->valstr = (char *)aCalloc(80,sizeof(char));
		if(sd)
			memcpy(group->valstr,sd->message,80);
	}

	if(unit_flag&UF_DANCE) {
		if(sd) {
			sd->skill_dance.id = skillid;
			sd->skill_dance.lv = skilllv;
		}
		status_change_start(src,SC_DANCING,skillid,group->bl.id,0,0,skill_get_time(skillid,skilllv)+1000,0);
		// 合奏スキルは相方をダンス状態にする
		if(sd && unit_flag&UF_ENSEMBLE) {
			int c = 0;
			map_foreachinarea(skill_check_condition_use_sub,sd->bl.m,
				sd->bl.x-1,sd->bl.y-1,sd->bl.x+1,sd->bl.y+1,BL_PC,sd,&c);
		}
	}

	for(i=0; i<layout->count; i++) {
		int ux = x + layout->dx[i];
		int uy = y + layout->dy[i];
		int alive = 1;

		val1  = skilllv;
		val2  = 0;
		limit = group->limit;

		switch (skillid) {
			case MG_FIREWALL:		/* ファイアーウォール */
				val2 = group->val2;
				// ゲイル上なら時間倍
				if(map_find_skill_unit_oncell(src,ux,uy,SA_VIOLENTGALE,NULL)!=NULL)
				{
					limit = limit*150/100;
					on_flag = 1;
				}
				break;
			case WZ_ICEWALL:		/* アイスウォール */
				val1 = (skilllv<=1)? 500: 200+200*skilllv;
				break;
			case PF_FOGWALL:
				// デリュージ上なら時間倍
				if(map_find_skill_unit_oncell(src,ux,uy,SA_DELUGE,NULL)!=NULL)
				{
					limit = limit*2;
					on_flag = 1;
				}
				break;
			case WZ_FIREPILLAR:		/* ファイアーピラー */
			case HT_LANDMINE:		/* ランドマイン */
			case HT_ANKLESNARE:		/* アンクルスネア */
			case HT_SHOCKWAVE:		/* ショックウェーブトラップ */
			case HT_SANDMAN:		/* サンドマン */
			case HT_FLASHER:		/* フラッシャー */
			case HT_FREEZINGTRAP:		/* フリージングトラップ */
			case HT_SKIDTRAP:		/* スキッドトラップ */
			case MA_SKIDTRAP:
			case MA_LANDMINE:
			case MA_SANDMAN:
			case MA_FREEZINGTRAP:
				val1 = 3500;	// 罠の耐久HP
				break;
			case HT_TALKIEBOX:		/* トーキーボックス */
				val1 = 70000;	// 罠の耐久HP
				break;
			case NJ_KAENSIN:		/* 火炎陣 */
				val1 = 4+(skilllv+1)/2;
				break;
			case WM_REVERBERATION:	/* 振動残響 */
				val1 = 1+skilllv;
				break;
			case GN_WALLOFTHORN:	/* ソーンウォール */
				val1 = 2000+2000*skilllv;
				break;
		}

		// ランドプロテクターがないかチェック
		switch(skillid) {
			case HT_SKIDTRAP:		/* スキッドトラップ */
			case HT_LANDMINE:		/* ランドマイン */
			case HT_ANKLESNARE:		/* アンクルスネア */
			case HT_SHOCKWAVE:		/* ショックウェーブトラップ */
			case HT_SANDMAN:		/* サンドマン */
			case HT_FLASHER:		/* フラッシャー */
			case HT_FREEZINGTRAP:	/* フリージングトラップ */
			case HT_BLASTMINE:		/* ブラストマイン */
			case HT_CLAYMORETRAP:	/* クレイモアトラップ */
			case BD_LULLABY:		/* 子守歌 */
			case BA_DISSONANCE:		/* 不協和音 */
			case BA_WHISTLE:		/* 口笛 */
			case BA_ASSASSINCROSS:	/* 夕陽のアサシンクロス */
			case BA_POEMBRAGI:		/* ブラギの詩*/
			case BA_APPLEIDUN:		/* イドゥンの林檎 */
			case DC_UGLYDANCE:		/* 自分勝手なダンス */
			case DC_HUMMING:		/* ハミング */
			case DC_DONTFORGETME:	/* 私を忘れないで… */
			case DC_FORTUNEKISS:	/* 幸運のキス */
			case DC_SERVICEFORYOU:	/* サービスフォーユー */
			case CG_HERMODE:		/* ヘルモードの杖 */
			case NPC_EVILLAND:		/* イービルランド */
			case MA_SKIDTRAP:		/* スキッドトラップ */
			case MA_LANDMINE:		/* ランドマイン */
			case MA_SANDMAN:		/* サンドマン */
			case MA_FREEZINGTRAP:	/* フリージングトラップ */
			case NPC_DISSONANCE:
			case NPC_UGLYDANCE:
				break;
			default:
				map_foreachinarea(skill_landprotector,src->m,ux,uy,ux,uy,BL_SKILL,skillid,&alive);
				if(alive)
					map_foreachinarea(skill_maelstrom,src->m,ux-2,uy-2,ux+2,uy+2,BL_SKILL,skilllv,&alive,&mael_flag);
				break;
		}

		if(unit_flag&UF_PATHCHECK && alive) { // 射線チェック
			if(!path_search_long(NULL,src->m,src->x,src->y,ux,uy))
				alive = 0;
		}

		if(skillid == WZ_ICEWALL && alive) {
			val2 = map_getcell(src->m,ux,uy,CELL_GETTYPE);
			if(val2 == 5 || val2 == 1) {
				alive = 0;
			} else {
				map_setcell(src->m,ux,uy,5);
				clif_changemapcell(src->m,ux,uy,5,0);
			}
		}

		if(alive) {
			struct skill_unit *unit;
			nullpo_retr(NULL, unit = skill_initunit(group,i,ux,uy));
			unit->val1  = val1;
			unit->val2  = val2;
			unit->limit = limit;
			unit->range = range;
		}
	}

	if(on_flag) {
		switch(skillid) {
		case MG_FIREWALL:
			group->limit = group->limit*150/100;
			break;
		case PF_FOGWALL:
			group->limit *= 2;
			break;
		}
	}

	map_freeblock_lock();

	// 全てのユニットの設置が終わってからスキル効果を発動させる
	for(i=0; i<layout->count; i++) {
		struct skill_unit *unit = &group->unit[i];

		if(unit->alive && unit->range == 0) {
			map_foreachinarea(skill_unit_effect,unit->bl.m,
				unit->bl.x,unit->bl.y,unit->bl.x,unit->bl.y,
				(BL_PC|BL_MOB|BL_MERC|BL_ELEM),&unit->bl,tick,1);
		}
	}

	// スキルユニットグループが既に消滅している可能性があるので再取得
	group = map_id2sg(group->bl.id);

	map_freeblock_unlock();

	if(group && group->alive_count <= 0) {
		// ユニットが発生しなかった
		skill_delunitgroup(group);
		group = NULL;
	}

	return group;
}

/*==========================================
 * スキルユニットの発動イベント(位置発動)
 *------------------------------------------
 */
static int skill_unit_onplace(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg;
	struct skill_unit *unit2;
	struct status_change *sc;
	int type;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if( bl->prev == NULL || !src->alive || unit_isdead(bl) )
		return 0;

	if( bl->type == BL_PC && ((struct map_session_data*)bl)->invincible_timer != -1 )
		return 0; // 無敵タイマー中

	nullpo_retr(0, sg = src->group);

	if(battle_check_target(&src->bl,bl,sg->target_flag) <= 0)
		return 0;

	sc = status_get_sc(bl);

	// 対象がホバーリング状態の場合は一部無効
	if(sc && sc->data[SC_HOVERING].timer != -1) {
		switch(sg->unit_id) {
		case UNT_QUAGMIRE:
		case UNT_BLASTMINE:
		case UNT_SKIDTRAP:
		case UNT_ANKLESNARE:
		case UNT_VENOMDUST:
		case UNT_LANDMINE:
		case UNT_SHOCKWAVE:
		case UNT_SANDMAN:
		case UNT_FLASHER:
		case UNT_FREEZINGTRAP:
		case UNT_CLAYMORETRAP:
		case UNT_TALKIEBOX:
		case UNT_GRAVITATION:
		case UNT_SUITON:
		case UNT_MAKIBISHI:
			return 0;
		}
	}

	type = GetSkillStatusChangeTable(sg->skill_id);
	if(type < 0)
		return 0;

	switch (sg->unit_id) {
//	case UNT_PNEUMA:	/* ニューマ */
	case UNT_SAFETYWALL:	/* セイフティウォール */
		if(!sc || sc->data[type].timer==-1)
			status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,sg->limit,0);
		break;
	case UNT_QUAGMIRE:	/* クァグマイア */
		if (bl->type==BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
			break;
		if (sc && sc->data[type].timer!=-1)
			break;
		status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_VOLCANO:	/* ボルケーノ */
	case UNT_DELUGE:	/* デリュージ */
	case UNT_VIOLENTGALE:	/* バイオレントゲイル */
		if (sc && sc->data[type].timer!=-1) {
			unit2 = map_id2su(sc->data[type].val2);
			if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_SUITON:	/* 水遁 */
		if (sc && sc->data[type].timer!=-1) {
			unit2 = map_id2su(sc->data[type].val2);
			if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		if(status_get_class(bl) == PC_CLASS_NJ || battle_check_target(&src->bl,bl,BCT_ENEMY)<=0) {
			status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		} else {
			int penalty = - ((sg->skill_lv + 1) / 3 * 26 + 4) / 10;
			status_change_start(bl,type,sg->skill_lv,src->bl.id,penalty,1,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_LULLABY:		/* 子守唄 */
	case UNT_RICHMANKIM:		/* ニヨルドの宴 */
	case UNT_ETERNALCHAOS:		/* 永遠の混沌 */
	case UNT_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case UNT_RINGNIBELUNGEN:	/* ニーベルングの指輪 */
	case UNT_ROKISWEIL:		/* ロキの叫び */
	case UNT_INTOABYSS:		/* 深淵の中に */
	case UNT_SIEGFRIED:		/* 不死身のジークフリード */
	case UNT_DISSONANCE:		/* 不協和音 */
	case UNT_UGLYDANCE:		/* 自分勝手なダンス */
		// ダンス効果を自分にかける？
		if (sg->src_id==bl->id && battle_config.allow_me_concert_effect==0)
			break;

		if (sg->unit_id == UNT_ROKISWEIL) {
			// ロキを自分に適用しない
			if(sg->src_id==bl->id && battle_config.allow_me_concert_effect==1 && battle_config.allow_me_rokisweil==1)
				break;
			// ロキはボス無効
			if(status_get_mode(bl)&MD_BOSS)
				break;
		}
		// 永遠の混沌はボス無効
		else if (sg->unit_id == UNT_ETERNALCHAOS) {
			if(status_get_mode(bl)&MD_BOSS)
				break;
		}
		if (sc && sc->data[type].timer!=-1) {
			unit2 = map_id2su(sc->data[type].val4);
			if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_WHISTLE:		/* 口笛 */
	case UNT_ASSASSINCROSS:		/* 夕陽のアサシンクロス */
	case UNT_POEMBRAGI:		/* ブラギの詩 */
	case UNT_APPLEIDUN:		/* イドゥンの林檎 */
	case UNT_HUMMING:		/* ハミング */
	case UNT_DONTFORGETME:		/* 私を忘れないで… */
	case UNT_FORTUNEKISS:		/* 幸運のキス */
	case UNT_SERVICEFORYOU:		/* サービスフォーユー */
		// ダンス効果を自分にかける？
		if(sg->src_id==bl->id && (!sc || sc->data[SC_BARDDANCER].timer==-1)
							&& battle_config.allow_me_dance_effect==0)
			break;
		if(sc && sc->data[type].timer!=-1) {
			unit2 = map_id2su(sc->data[type].val4);
			if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_CALLFAMILY:				/* あなたに逢いたい or ママ、パパ、来て or 坊や、いらっしゃい */
		break;
	case UNT_FOGWALL:				/* ウォールオブフォグ */
		if(status_check_no_magic_damage(bl))
			break;
		// 霧の中
		if(map[bl->m].flag.normal) {	// 通常マップ
			if(bl->type==BL_PC || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		} else if(status_get_party_id(&src->bl)>0) {	// それ以外でPT時
			if(battle_check_target(bl,&src->bl,BCT_ENEMY)<=0 || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		} else {	// それ以外でソロ時
			if(bl->id==sg->src_id || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		}
		break;
	case UNT_MOONLIT:		/* 月明りの下で */
		break;
	case UNT_GRAVITATION:		/* グラビテーションフィールド */
		if (battle_check_target(&src->bl,bl,BCT_ENEMY)>0)	// 敵対象
		{
			status_change_start(bl,SC_GRAVITATION,sg->skill_lv,0,0,0,9000,0);
		}
		break;
	case UNT_HERMODE:		/* ヘルモードの杖 */
		{
			int same_flag = 0;

			// 自分は除外
			if(sg->src_id==bl->id)
				break;

			// ギルドとパーティーが同じなら支援スキル解除対象
			if( status_get_guild_id(&src->bl)==status_get_guild_id(bl) ||
			    status_get_party_id(&src->bl)==status_get_guild_id(bl) )
			{
				same_flag = 1;
				// ソウルリンカー以外は支援スキル解除
				if(status_get_class(bl) != PC_CLASS_SL)
					status_change_release(bl,0x20);
			}

			if(sc && sc->data[type].timer!=-1 && same_flag==0) {
				unit2 = map_id2su(sc->data[type].val4);
				if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
					break;
			}
			status_change_start(bl,type,same_flag,sg->val1,sg->val2,
					src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_NEUTRALBARRIER:	/* ニュートラルバリアー */
		if(sc && sc->data[type].timer != -1) {
			unit2 = map_id2su(sc->data[type].val4);
			if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
				break;
		}
		status_change_start(bl,SC_NEUTRALBARRIER,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_STEALTHFIELD:	/* ステルスフィールド */
		// 使用者には効果なし
		if(sg->src_id == bl->id)
			break;
		if(sc && sc->data[type].timer != -1) {
			unit2 = map_id2su(sc->data[type].val4);
			if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
				break;
		}
		status_change_start(bl,SC_STEALTHFIELD,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_KINGS_GRACE:	/* キングスグレイス */
		if(sc && sc->data[type].timer != -1) {
			unit2 = map_id2su(sc->data[type].val4);
			if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
				break;
		}
		status_change_start(bl,SC_KINGS_GRACE,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_BLOODYLUST:	/* ブラッディラスト */
		if(status_get_party_id(&src->bl)>0 && battle_check_target(&src->bl,bl,BCT_ENEMY)<=0) {
			if(sc && sc->data[type].timer != -1) {
				unit2 = map_id2su(sc->data[type].val4);
				if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
					break;
			}
			status_change_start(bl,SC_BERSERK,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
	case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
	case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
	case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
		if( sc && sc->data[type].timer != -1 ) {
			unit2 = map_id2su(sc->data[type].val2);
			if( unit2 && unit2->group && ( unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0 ) )
				break;
		}
		status_change_start(bl,type,sg->skill_lv,src->bl.id,sg->val1,15,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		// 敵ならユニットに応じて状態異常を付与する
		if( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 ) {
			switch(sg->unit_id) {
				case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
					switch(atn_rand()%3) {
					case 0:	// 凍結
						if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_FREEZE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 氷結
						status_change_pretimer(bl,SC_FROSTMISTY,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 冷凍
						status_change_pretimer(bl,SC_DIAMONDDUST,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
					switch(atn_rand()%2) {
					case 0:	// 石化
						if(atn_rand() % 10000 < status_change_rate(bl,SC_STONE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_STONE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 毒
						if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
					// 発火
					status_change_pretimer(bl,SC_HELLINFERNO,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
					break;
				case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
					switch(atn_rand()%3) {
					case 0:	// 沈黙
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SILENCE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 睡眠
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 深い睡眠
						status_change_pretimer(bl,SC_DEEP_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
			}
		}
		break;
	case UNT_NYANGGRASS:	/* ニャングラス */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(!sc || sc->data[SC_NYANGGRASS].timer==-1)
				status_change_start(bl,SC_NYANGGRASS,sg->skill_lv,src->bl.id,0,0,sg->limit,0);
		}
		break;
/*	default:
		if(battle_config.error_log)
			printf("skill_unit_onplace: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}

	return 0;
}

/*==========================================
 * スキルユニットの発動イベント(タイマー発動)
 *------------------------------------------
 */
static int skill_unit_onplace_timer(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg;
	struct block_list *ss;
	struct status_change *sc;
	struct unit_data *ud;
	struct linkdb_node **node;
	int tickset_id, diff = 0;
	unsigned int tickset_tick;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	nullpo_retr(0, sg = src->group);

	if(!src->alive)
		return 0;

	if(unit_isdead(bl))
		return 0;

	nullpo_retr(0, ss = map_id2bl(sg->src_id));
	nullpo_retr(0, ud = unit_bl2ud(bl));

	sc = status_get_sc(bl);

	if(status_get_mode(bl)&MD_SKILLIMMUNITY)
		return 0;

	// 対象がホバーリング状態の場合は一部無効
	if(sc && sc->data[SC_HOVERING].timer != -1) {
		switch(sg->unit_id) {
		case UNT_QUAGMIRE:
		case UNT_BLASTMINE:
		case UNT_SKIDTRAP:
		case UNT_ANKLESNARE:
		case UNT_VENOMDUST:
		case UNT_LANDMINE:
		case UNT_SHOCKWAVE:
		case UNT_SANDMAN:
		case UNT_FLASHER:
		case UNT_FREEZINGTRAP:
		case UNT_CLAYMORETRAP:
		case UNT_TALKIEBOX:
		case UNT_GRAVITATION:
		case UNT_SUITON:
		case UNT_MAKIBISHI:
			return 0;
		}
	}

	// 前に影響を受けてからintervalの間は影響を受けない
	if(skill_get_unit_flag(sg->skill_id,sg->skill_lv)&UF_NOOVERLAP) {
		tickset_id = sg->skill_id;
		node       = &ud->skilltickset;
	} else {
		tickset_id = bl->id;
		node       = &sg->tickset;
	}
	tickset_tick = PTR2UINT(linkdb_search( node, INT2PTR(tickset_id) ));
	if(tickset_tick == 0)
		tickset_tick = tick;

	diff = DIFF_TICK(tick, tickset_tick);
	if(sg->skill_id == PR_SANCTUARY) {
		diff += 500; // 新規に回復したユニットだけカウントするための仕掛け
	}

	if(diff < 0) {
		if(sg->skill_id == WZ_STORMGUST && status_get_mode(bl)&MD_BOSS) {
			// ボス属性にはストームガストの3HIT毎に2HITのダメージが重なる
			if(!sc || sc->data[SC_FREEZE].val3 != 3)
				return 0;
		} else {
			return 0;
		}
	}

	tickset_tick = tick + sg->interval;

	// GXは重なっていたら3HITしない
	if(sg->skill_id == CR_GRANDCROSS && !battle_config.gx_allhit) {
		int count = map_count_oncell(bl->m,bl->x,bl->y,BL_PC|BL_MOB);
		if(count > 0)
			tickset_tick += sg->interval * (count-1);
	}
	linkdb_replace( node, INT2PTR(tickset_id), UINT2PTR(tickset_tick) );

	switch (sg->unit_id) {
	case UNT_PNEUMA:	/* ニューマ */
		if(!sc || sc->data[SC_PNEUMA].timer==-1)
			status_change_start(bl,SC_PNEUMA,sg->skill_lv,src->bl.id,0,0,sg->limit,0);
		break;
	case UNT_WARP_ACTIVE:	/* ワープポータル(発動後) */
		if (bl->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)bl;
			if(sd) {
				if ((sd->state.warp_waiting || strcmp(map[bl->m].name,sg->valstr) == 0) &&
				    src->bl.m == bl->m &&
				    src->bl.x == bl->x &&
				    src->bl.y == bl->y &&
				    src->bl.x == sd->ud.to_x &&
				    src->bl.y == sd->ud.to_y)
				{
					sd->state.warp_waiting = 0;
					if (battle_config.chat_warpportal || !sd->chatID){
						char mapname[24];
						int  x = sg->val2>>16;
						int  y = sg->val2&0xffff;
						strncpy(mapname,sg->valstr,24);
						if( sg->src_id == bl->id ||
						    (strcmp(map[src->bl.m].name,sg->valstr) == 0 && src->bl.x == (sg->val2>>16) && src->bl.y == (sg->val2&0xffff)) ||
						    (--sg->val1) <= 0 )
						{
							skill_delunitgroup(sg);
						}
						pc_setpos(sd,mapname,x,y,3);
					}
				} else {
				 	sd->state.warp_waiting = 1;
				}
			}
		} else if(bl->type == BL_MOB && battle_config.mob_warpportal) {
			int m = map_mapname2mapid(sg->valstr);
			mob_warp((struct mob_data *)bl,m,sg->val2>>16,sg->val2&0xffff,3);
		}
		break;
	case UNT_SANCTUARY:	/* サンクチュアリ */
		{
			int race = status_get_race(bl);

#ifndef PRE_RENEWAL
			if(bl->type == BL_MOB && ((struct mob_data *)bl)->class_ == MOBID_EMPERIUM)
				break;
#endif
			if (battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON || (sc && sc->data[SC_AKAITSUKI].timer != -1)) {
				if (bl->type == BL_PC) {
					if(!map[bl->m].flag.pvp && !map[bl->m].flag.gvg)
						break;
				}
				if (battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0))
					sg->val1 = sg->val1-2;	// チャットキャンセルに対応
			} else {
				int heal;
				if (status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				heal = sg->val2;
				if(sc) {
					if(sc->data[SC_CRITICALWOUND].timer != -1)
						heal = heal * (100 - sc->data[SC_CRITICALWOUND].val1 * 10) / 100;
					if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
						heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
					if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
						heal = 0;
				}
				if(bl->type == BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
					heal = 0;	/* 黄金蟲カード（ヒール量０） */

				clif_skill_nodamage(&src->bl,bl,AL_HEAL,heal,1);
				battle_heal(NULL,bl,heal,0,0);
				if (diff >= 500)
					sg->val1--;	// 新規に入ったユニットだけカウント
			}
			if (sg->val1 <= 0)
				skill_delunitgroup(sg);
		}
		break;
	case UNT_MAGNUS:	/* マグヌスエクソシズム */
		{
			int race = status_get_race(bl);
			if (!battle_check_undead(race,status_get_elem_type(bl)) && race != RCT_DEMON)
				return 0;
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			src->val2++;
		}
		break;
	case UNT_FIREWALL:		/* ファイアーウォール */
	case UNT_FLAMECROSS:	/* フレイムクロス */
		do {
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_ATTACK_SKILLS:	/* 攻撃系スキル全般 */
		switch(sg->skill_id) {
		case GS_DESPERADO:	/* デスペラード */
		case GN_CRAZYWEED_ATK:	/* クレイジーウィード */
		case KO_HUUMARANKA:		/* 風魔手裏剣乱華 */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
			break;
		case SG_SUN_WARM:	/* 温もり */
		case SG_MOON_WARM:	/* 温もり */
		case SG_STAR_WARM:	/* 温もり */
			{
				const int x = bl->x, y = bl->y;
				int hit   = 0;
				int count = skill_get_blewcount(sg->skill_id,sg->skill_lv);

				do {
					if(bl->type != BL_PC) {
						if(battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0))
							skill_blown(&src->bl,bl,count|SAB_REVERSEBLOW|SAB_NOPATHSTOP);
					} else {
						struct map_session_data *sd = (struct map_session_data *)bl;
						if(sd) {
							sd->status.sp -= 15;
								if(sd->status.sp < 0)
									sd->status.sp = 0;
								clif_updatestatus(sd,SP_SP);
							}
						}
				} while(sg->alive_count > 0 && !unit_isdead(bl) && x == bl->x && y == bl->y &&
					sg->interval > 0 && ++hit < SKILLUNITTIMER_INVERVAL / sg->interval);
			}
			break;
		default:
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_EARTHSTRAIN:	/* アースストレイン */
	case UNT_PSYCHIC_WAVE:	/* サイキックウェーブ */
	case UNT_CLOUD_KILL:	/* クラウドキル */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_FIREPILLAR_WAITING:	/* ファイアーピラー(発動前) */
		skill_unitsetting(ss,sg->skill_id,sg->skill_lv,src->bl.x,src->bl.y,1);
		skill_delunit(src);
		break;
	case UNT_FIREPILLAR_ACTIVE:	/* ファイアーピラー(発動後) */
		{
			int i = src->range;
			int splash_count = 0;
#ifdef PRE_RENEWAL
			if(sg->skill_lv>5)
				i += 2;
#else
			i += 1;
#endif
			splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
		}
		break;
	case UNT_SKIDTRAP:	/* スキッドトラップ */
		{
			// 罠設置時のキャラの座標とターゲットの位置関係で飛ぶ方向を決める
			int xs = sg->val1, ys = sg->val2, dir;
			int count = skill_get_blewcount(sg->skill_id,sg->skill_lv);
			if( (bl->x == src->bl.x && bl->y == src->bl.y) || (bl->x == xs && bl->y == ys) ) {
				dir = 6;	// 罠の直上か設置時の位置に居るなら真西に飛ぶ
			} else {
				dir = path_calc_dir(bl,xs,ys);
				if(dir == 0)
					dir = 8;
			}
			skill_blown(&src->bl,bl,count|(dir<<20)|SAB_NODAMAGE|SAB_NOPATHSTOP);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_LANDMINE:	/* ランドマイン */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick)+1500;
		break;

	case UNT_BLASTMINE:	/* ブラストマイン */
	case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
	case UNT_SANDMAN:	/* サンドマン */
	case UNT_FLASHER:	/* フラッシャー */
	case UNT_FREEZINGTRAP:	/* フリージングトラップ */
	case UNT_CLAYMORETRAP:	/* クレイモアトラップ */
	case UNT_MAGENTATRAP:		/* マゼンタトラップ */
	case UNT_COBALTTRAP:		/* コバルトトラップ */
	case UNT_MAIZETRAP:			/* メイズトラップ */
	case UNT_VERDURETRAP:		/* ヴェルデュールトラップ */
	case UNT_CLUSTERBOMB:		/* クラスターボム */
	case UNT_FIRINGTRAP:		/* ファイアリングトラップ */
	case UNT_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		{
			int splash_count = 0;
			int i = src->range;
			int sec;

			// サンドマンとクレイモアは効果範囲を1セル広げる
			if(sg->unit_id == UNT_SANDMAN || sg->unit_id == UNT_CLAYMORETRAP || sg->unit_id == UNT_MAGENTATRAP || sg->unit_id == UNT_COBALTTRAP ||
				sg->unit_id == UNT_MAIZETRAP || sg->unit_id == UNT_VERDURETRAP || sg->unit_id == UNT_FIRINGTRAP || sg->unit_id == UNT_ICEBOUNDTRAP)
			{
				i++;
			}
			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: ((sg->unit_id == UNT_CLUSTERBOMB)? 1000: 1500);
			splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + sec;
		}
		break;

	case UNT_ANKLESNARE:	/* アンクルスネア */
		{
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if (sg->val2 == 0 && (!sc || sc->data[type].timer == -1)) {
				int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
				if(status_get_mode(bl)&MD_BOSS)
					sec /= 5;
				// 最低拘束時間補償（式はeAのものをとりあえず採用）
				if(sec < 3000 + 30 * sg->skill_lv)
					sec = 3000 + 30 * sg->skill_lv;
				status_change_start(bl,type,sg->skill_lv,sg->bl.id,0,0,sec,0);
				// 本来ならボス属性なら吸い寄せられないが、skill_delunitgroup() 等の処理と上手く折り合いが付かないので保留
				if(!map[src->bl.m].flag.pvp && !map[src->bl.m].flag.gvg) {
					unit_movepos(bl, src->bl.x, src->bl.y, 0);
					clif_01ac(&src->bl);
				}
				sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
				sg->val2     = bl->id;
				sg->interval = -1;
				src->range   = 0;
			}
		}
		break;
	case UNT_VENOMDUST:	/* ベナムダスト */
		{
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if(type < 0)
				break;
			if (sc && sc->data[type].timer != -1)
				break;
			if(atn_rand() % 10000 < status_change_rate(bl,type,10000,status_get_lv(ss)))
				status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_DEMONSTRATION:	/* デモンストレーション */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(bl->type == BL_PC && atn_rand()%100 < sg->skill_lv)
			pc_break_equip((struct map_session_data *)bl, LOC_RARM);
		break;
	case UNT_TALKIEBOX:				/* トーキーボックス */
		if(sg->src_id == bl->id) // 自分が踏んでも発動しない
			break;
		if(sg->val2 == 0) {
			clif_talkiebox(&src->bl,sg->valstr);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 5000;
			sg->val2  = -1; // 踏んだ
		}
		break;
	case UNT_GOSPEL:	/* ゴスペル */
		{
			struct map_session_data *sd = NULL;
			if(bl->type == BL_PC)
				sd = (struct map_session_data *)bl;
			if (sd && sg->src_id == bl->id) {
				int hp = (sg->skill_lv <= 5) ? 30 : 45;
				int sp = (sg->skill_lv <= 5) ? 20 : 35;
				if(sd->status.hp <= hp || sd->status.sp <= sp) {
					status_change_end(bl,SC_GOSPEL,-1);
					break;
				}
				pc_heal(sd,-hp,-sp);
				break;
			}
			if (sd && sd->special_state.no_magic_damage)
				break;
			if (atn_rand()%100 >= 50 + sg->skill_lv * 5)
				break;
			if (battle_check_target(&src->bl,bl,BCT_PARTY) > 0) {	// 味方(PT)対象
				int type = 0;
				switch(atn_rand()%13) {
				case 0:		// HPを回復(1000～9999？)
					battle_heal(NULL,bl,1000+atn_rand()%9000,0,0);
					break;
				case 1:		// MHPを100%増加(持続時間60秒)
					status_change_start(bl,SC_INCMHP2,100,0,0,0,60000,0);
					type = 0x17;
					break;
				case 2:		// MSPを100%増加(持続時間60秒)
					status_change_start(bl,SC_INCMSP2,100,0,0,0,60000,0);
					type = 0x18;
					break;
				case 3:		// 全てのステータス+20(持続時間60秒)
					status_change_start(bl,SC_INCALLSTATUS,20,0,0,0,60000,0);
					type = 0x19;
					break;
				case 4:		// ブレッシングLv10効果付与
					status_change_start(bl,SC_BLESSING,10,0,0,0,skill_get_time(AL_BLESSING,10),0);
					break;
				case 5:		// 速度増加Lv10効果付与
					status_change_start(bl,SC_INCREASEAGI,10,0,0,0,skill_get_time(AL_INCAGI,10),0);
					break;
				case 6:		// 武器に聖属性効果付与
					status_change_start(bl,SC_ASPERSIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1c;
					break;
				case 7:		// 鎧に聖属性効果付与
					status_change_start(bl,SC_BENEDICTIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1d;
					break;
				case 8:		// ATKが100%増加
					status_change_start(bl,SC_INCATK2,100,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1f;
					break;
				case 9:		// HIT, FLEEが+50(持続時間60秒)
					status_change_start(bl,SC_INCHIT,50,0,0,0,60000,0);
					status_change_start(bl,SC_INCFLEE,50,0,0,0,60000,0);
					type = 0x20;
					break;
				case 10:	// 全ての状態異常を解除
					status_change_release(bl,0x08);
					type = 0x15;
					break;
				case 11:	// 全状態異常の耐性(持続時間60秒)
					status_change_start(bl,SC_STATUS_UNCHANGE,0,0,0,0,60000,0);
					type = 0x16;
					break;
				case 12:	// 防御力増加(持続時間10秒)
					status_change_start(bl,SC_INCDAMAGE,-50,0,0,0,10000,0);
					type = 0x1e;
					break;
				}
				if(type > 0 && sd)
					clif_gospel_message(sd,type);
			}
			else if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS)) {	// 敵対象でボス以外
				switch(atn_rand()%8) {
				case 0:		// ランダムダメージ(1000～9999？)
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
					break;
				case 1:		// 呪い効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_CURSE,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 2:		// 暗黒効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_BLIND,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 3:		// 毒効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 4:		// プロボックLv10効果付与
					status_change_start(bl,SC_PROVOKE,10,0,0,0,skill_get_time(SM_PROVOKE,10),0);
					break;
				case 5:		// ATKが0に減少(持続時間20秒)
					status_change_start(bl,SC_INCATK2,-100,0,0,0,20000,0);
					break;
				case 6:		// FLEEが0に減少(持続時間20秒)
					status_change_start(bl,SC_INCFLEE2,-100,0,0,0,20000,0);
					break;
				case 7:		// HITが0に減少(持続時間50秒)
					status_change_start(bl,SC_INCHIT2,-100,0,0,0,50000,0);
					break;
				}
			}
		}
		break;
	case UNT_BASILICA:	/* バジリカ */
		if (sg->src_id == bl->id)
			break;
		if ( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS) )
			skill_blown(&src->bl,bl,SAB_NODAMAGE|1);
		if (battle_check_target(&src->bl,bl,BCT_NOENEMY)>0) {
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if(type < 0)
				break;
			status_change_start(bl,type,sg->skill_lv,sg->val1,sg->val2,src->bl.id,sg->interval+100,0);
		}
		break;
	case UNT_SPIDERWEB:	/* スパイダーウェブ */
		if((!sc || sc->data[SC_SPIDERWEB].timer == -1) && sg->val2 == 0) {
			skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
			unit_movepos(bl, src->bl.x, src->bl.y, 0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + skill_get_time2(sg->skill_id,sg->skill_lv);
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_MOONLIT: 	/* 月明りの下で */
		if(!(bl->type & (BL_MOB | BL_PC)))
			break;
		if (sg->src_id == bl->id)
			break;
		// 相方
		if(sc && sc->data[SC_DANCING].timer != -1 && sg->src_id == sc->data[SC_DANCING].val4)
			break;
		if(!(status_get_mode(bl)&MD_BOSS))
		{
			int d = unit_distance(&src->bl,bl);
			int range = skill_get_unit_range(sg->skill_id,sg->skill_lv);
			int count = (d < range)? range-d+2: 1;
			skill_blown(&src->bl,bl,count|SAB_NODAMAGE);
		}
		break;
	case UNT_GRAVITATION:
		if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)		// 敵対象
		{
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		//	unit_fixdamage(&src->bl,bl,0, 0, 0,sg->skill_lv*200+200,1, 4, 0, 0);
		}
		break;
	case UNT_TATAMIGAESHI:	/* 畳返し */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
		break;
	case UNT_KAEN:	/* 火炎陣 */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(--src->val1 <= 0)
			skill_delunit(src);
		break;
	case UNT_GROUNDDRIFT_WIND:	/* グラウンドドリフト */
	case UNT_GROUNDDRIFT_DARK:
	case UNT_GROUNDDRIFT_POISON:
	case UNT_GROUNDDRIFT_WATER:
	case UNT_GROUNDDRIFT_FIRE:
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick) + 1500;
		break;
	case UNT_EVILLAND:	/* イービルランド */
		{
			int race = status_get_race(bl);

			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				int heal = sg->val1;
				if(status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,heal,1);
				battle_heal(NULL,bl,heal,0,0);
			} else if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
				battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			}
		}
		break;
	case UNT_POISONSMOKE:	/* ポイズンスモーク */
		if(atn_rand() % 10000 < status_change_rate(bl,sg->val1,2000,status_get_lv(&src->bl)))
			status_change_start(bl,sg->val1,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_EPICLESIS:	/* エピクレシス */
		{
			int race = status_get_race(bl);

			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(bl->type == BL_PC) {
					if(!map[bl->m].flag.pvp && !map[bl->m].flag.gvg)
						break;
				}
				battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			} else if(battle_check_target(&src->bl,bl,BCT_NOENEMY)) {
				if(sc && sc->data[SC_EPICLESIS].timer == -1)
					status_change_start(bl,SC_EPICLESIS,sg->skill_lv,0,0,0,sg->limit,0);
				if(bl->type == BL_PC) {
					struct map_session_data *sd = (struct map_session_data *)bl;

					if(sd->status.hp < sd->status.max_hp) {
						int hp = sd->status.max_hp * (((sg->skill_lv - 1) / 2) + 3) / 100;
						if(sd->status.hp + hp > sd->status.max_hp) {
							hp = sd->status.max_hp - sd->status.hp;
						}
						if(hp > 0) {
							sd->status.hp += hp;
							clif_heal(sd->fd,SP_HP,hp);
						}
					}

					if(sd->status.sp < sd->status.max_sp) {
						int sp = sd->status.max_sp * (((sg->skill_lv - 1) / 2) + 2) / 100;
						if(sd->status.sp + sp > sd->status.max_sp) {
							sp = sd->status.max_sp - sd->status.sp;
						}
						if(sp > 0) {
							sd->status.sp += sp;
							clif_heal(sd->fd,SP_SP,sp);
						}
					}
				}
			}
		}
		break;
	case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		map_foreachinarea(skill_trap_splash,src->bl.m,
					src->bl.x-2,src->bl.y-2,
					src->bl.x+2,src->bl.y+2,
					(BL_CHAR|BL_SKILL),src,tick,1);
		sg->unit_id = UNT_USED_TRAPS;
		//clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
		sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		break;
	case UNT_MAGMA_ERUPTION:	/* マグマイラプション */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,NC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		break;
	case UNT_MANHOLE:	/* マンホール */
		if(sg->val2 == 0) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			unit_movepos(bl, src->bl.x, src->bl.y, 0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_DIMENSIONDOOR:	/* ディメンションドア */
		if(bl->type == BL_PC)
			pc_randomwarp((struct map_session_data *)bl,3);
		else if(bl->type == BL_MOB)
			mob_warp((struct mob_data *)bl,-1,-1,-1,3);
		break;
	case UNT_CHAOSPANIC:	/* カオスパニック */
		if(sc && sc->data[SC_CONFUSION].timer == -1)
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
		break;
	case UNT_SEVERE_RAINSTORM:	/* シビアレインストーム */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,WM_SEVERE_RAINSTORM_MELEE,sg->skill_lv,tick,0);
		break;
	case UNT_REVERBERATION:		/* 振動残響 */
		{
			int splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-2,src->bl.y-2,
						src->bl.x+2,src->bl.y+2,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-2,src->bl.y-2,
						src->bl.x+2,src->bl.y+2,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_POEMOFNETHERWORLD:	/* 地獄の歌 */
		if(sg->val2 == 0 && !(status_get_mode(bl)&MD_BOSS)) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_FIREWALK:		/* ファイアーウォーク */
	case UNT_ELECTRICWALK:	/* エレクトリックウォーク */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		skill_delunit(src);
		break;
	case UNT_WARMER:	/* ウォーマー */
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		if(bl->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)bl;

			if(sd->status.hp < sd->status.max_hp) {
				int hp = sd->status.max_hp * sg->skill_lv / 100;
				if(sd->status.hp + hp > sd->status.max_hp) {
					hp = sd->status.max_hp - sd->status.hp;
				}
				if(hp > 0) {
					if(sc && sc->data[SC_AKAITSUKI].timer != -1) {
						unit_fixdamage(ss,bl,tick,0,status_get_dmotion(bl),hp,0,0,0,0);
					} else {
						sd->status.hp += hp;
						clif_heal(sd->fd,SP_HP,hp);
					}
				}
			}
		}
		status_change_end(bl,SC_DIAMONDDUST,-1);// 冷凍
		status_change_end(bl,SC_FREEZE,-1);		// 凍結
		status_change_end(bl,SC_FROSTMISTY,-1);	// 氷結
		break;
	case UNT_VACUUM_EXTREME:	/* バキュームエクストリーム */
		{
			int sec = skill_get_time(sg->skill_id,sg->skill_lv) - status_get_str(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			// 最低拘束時間補償
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			if(!(status_get_mode(bl)&MD_BOSS) && !map[bl->m].flag.gvg && bl->x != src->bl.x && bl->y != src->bl.y)
				unit_movepos(bl, src->bl.x, src->bl.y, 0);
			//sg->limit=DIFF_TICK(tick,sg->tick)+sec;
		}
		break;
	case UNT_THORNS_TRAP:		/* ソーントラップ */
		if(sg->val2 == 0 && (!sc || sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1)) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv);
			if(status_get_mode(bl)&MD_CANMOVE)
				unit_movepos(bl, src->bl.x, src->bl.y, 0);
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
		}
		else if(sc && sc->data[SC_THORNS_TRAP].timer != -1 && bl->id == sg->val2) {
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_WALLOFTHORN:	/* ソーンウォール */
		if(!(status_get_mode(bl)&MD_BOSS))
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_DEMONIC_FIRE:	/* デモニックファイアー */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2);
		break;
	case UNT_FIRE_EXPANSION_SMOKE_POWDER:	/* ファイアーエクスパンション(煙幕) */
		if(sc && sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv),0);
		break;
	case UNT_FIRE_EXPANSION_TEAR_GAS:		/* ファイアーエクスパンション(催涙ガス) */
		if(sc && sc->data[SC_FIRE_EXPANSION_TEAR_GAS].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv),0);
		break;
	case UNT_HELLS_PLANT:	/* ヘルズプラント */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,GN_HELLS_PLANT_ATK,sg->skill_lv,tick,0);
		skill_delunit(src);
		break;
	case UNT_FIRE_MANTLE:	/* ファイアーマントル */
		do {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_MAKIBISHI:	/* 撒菱 */
		unit_fixdamage(ss,bl,tick,0,status_get_dmotion(bl),20*sg->skill_lv,0,0,0,0);
		skill_delunit(src);
		break;
	case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
	case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
	case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
	case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
		// 敵ならユニットに応じて状態異常を付与する
		if( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 ) {
			switch(sg->unit_id) {
				case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
					switch(atn_rand()%3) {
					case 0:	// 凍結
						if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_FREEZE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 氷結
						status_change_pretimer(bl,SC_FROSTMISTY,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 冷凍
						status_change_pretimer(bl,SC_DIAMONDDUST,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
					switch(atn_rand()%2) {
					case 0:	// 石化
						if(atn_rand() % 10000 < status_change_rate(bl,SC_STONE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_STONE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 毒
						if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
					// 発火
					status_change_pretimer(bl,SC_HELLINFERNO,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
					break;
				case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
					switch(atn_rand()%3) {
					case 0:	// 沈黙
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SILENCE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 睡眠
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 深い睡眠
						status_change_pretimer(bl,SC_DEEP_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
			}
		}
		break;
	case UNT_CATNIPPOWDER:	/* イヌハッカシャワー */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		break;
	case UNT_VENOMFOG:	/* ベナムフォグ */
		{
			int hp = 2000;

			if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
				if(status_get_elem_type(bl) == ELE_POISON)
					break;
				hp = battle_attr_fix(hp, ELE_NEUTRAL, status_get_element(bl));
				clif_damage(&src->bl,bl,tick,0,0,hp,0,9,0,0);
				battle_damage(NULL,bl,hp,0,0,0);
			} else if(battle_check_target(&src->bl,bl,BCT_NOENEMY) > 0) {
				if(status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,hp,1);
				battle_heal(NULL,bl,hp,0,0);
			}
		}
		break;
	}

	if(bl->type == BL_MOB && ss != bl)	/* スキル使用条件のMOBスキル */
	{
		struct mob_data *md = (struct mob_data *)bl;
		int target = md->target_id;
		if(battle_config.mob_changetarget_byskill == 1 || target == 0)
		{
			if(ss->type & (BL_PC | BL_HOM | BL_MERC | BL_ELEM))
				md->target_id = ss->id;
		}
		mobskill_use(md,tick,MSC_SKILLUSED|(sg->skill_id<<16));
		md->target_id = target;
	}
	return 0;
}

/*==========================================
 * スキルユニットから離脱
 *------------------------------------------
 */
static int skill_unit_onout(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg;
	struct status_change *sc;
	int type;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	nullpo_retr(0, sg=src->group);

	if (bl->prev==NULL || !src->alive || unit_isdead(bl))
		return 0;

	if( bl->type == BL_PC && ((struct map_session_data*)bl)->invincible_timer != -1 )
		return 0; // 無敵タイマー中

	switch(sg->unit_id){
	case UNT_SAFETYWALL:	/* セイフティウォール */
	case UNT_PNEUMA:	/* ニューマ */
	case UNT_QUAGMIRE:	/* クァグマイア */
	case UNT_VOLCANO:	/* ボルケーノ */
	case UNT_DELUGE:	/* デリュージ */
	case UNT_VIOLENTGALE:	/* バイオレントゲイル */
	case UNT_NYANGGRASS:	/* ニャングラス */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (type==SC_QUAGMIRE && bl->type==BL_MOB)
			break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val2==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_SUITON:	/* 水遁 */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val2==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_ANKLESNARE:	/* アンクルスネア */
		{
			struct block_list *target=map_id2bl(sg->val2);
			type = GetSkillStatusChangeTable(sg->skill_id);
			if( type == -1 ) break;
			if( target && target==bl ){
				status_change_end(bl,type,-1);
				sg->limit=DIFF_TICK(tick,sg->tick)+1000;
			}
		}
		break;
	case UNT_LULLABY:	/* 子守唄 */
	case UNT_RICHMANKIM:	/* ニヨルドの宴 */
	case UNT_ETERNALCHAOS:	/* 永遠の混沌 */
	case UNT_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case UNT_RINGNIBELUNGEN:	/* ニーベルングの指輪 */
	case UNT_ROKISWEIL:	/* ロキの叫び */
	case UNT_INTOABYSS:	/* 深淵の中に */
	case UNT_SIEGFRIED:	/* 不死身のジークフリード */
	case UNT_DISSONANCE:	/* 不協和音 */
	case UNT_WHISTLE:	/* 口笛 */
	case UNT_ASSASSINCROSS:	/* 夕陽のアサシンクロス */
	case UNT_POEMBRAGI:	/* ブラギの詩 */
	case UNT_APPLEIDUN:	/* イドゥンの林檎 */
	case UNT_UGLYDANCE:	/* 自分勝手なダンス */
	case UNT_HUMMING:	/* ハミング */
	case UNT_FORTUNEKISS:	/* 幸運のキス */
	case UNT_SERVICEFORYOU:	/* サービスフォーユー */
	case UNT_DONTFORGETME:	/* 私を忘れないで… */
	case UNT_BASILICA:	/* バジリカ */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val4==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_FOGWALL:	/* ウォールオブフォグ */
		sc = status_get_sc(bl);
		if(sc){
			if(sc->data[SC_FOGWALL].timer!=-1 && !(status_get_mode(bl)&MD_BOSS))	// ボス属性MOBは効果時間中持続
				status_change_end(bl,SC_FOGWALL,-1);
			// PCなら効果消える
			if(bl->type==BL_PC && sc->data[SC_FOGWALLPENALTY].timer!=-1)
				status_change_end(bl,SC_FOGWALLPENALTY,-1);
		}
		break;
	case UNT_MOONLIT: 	/* 月明りの下で */
		break;
	case UNT_SPIDERWEB:	/* スパイダーウェブ */
		{
			struct block_list *target = map_id2bl(sg->val2);
			if (target && target==bl)
				status_change_end(bl,SC_SPIDERWEB,-1);
			sg->limit = DIFF_TICK(tick,sg->tick)+1000;
			break;
		}

	case UNT_GRAVITATION:	/* グラビテーションフィールド */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_GRAVITATION].timer!=-1)
			status_change_end(bl,SC_GRAVITATION,-1);
		break;
	case UNT_HERMODE:	/* ヘルモードの杖 */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_HERMODE].timer!=-1)
			status_change_end(bl,SC_HERMODE,-1);
		break;
	case UNT_EPICLESIS:		/* エピクレシス */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_EPICLESIS].timer != -1)
			status_change_end(bl,SC_EPICLESIS,-1);
		break;
	case UNT_NEUTRALBARRIER:	/* ニュートラルバリアー */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_NEUTRALBARRIER].timer != -1)
			status_change_end(bl,SC_NEUTRALBARRIER,-1);
		break;
	case UNT_STEALTHFIELD:		/* ステルスフィールド */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_STEALTHFIELD].timer != -1)
			status_change_end(bl,SC_STEALTHFIELD,-1);
		break;
	case UNT_KINGS_GRACE:	/* キングスグレイス */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_KINGS_GRACE].timer != -1)
			status_change_end(bl,SC_KINGS_GRACE,-1);
		break;
	case UNT_BLOODYLUST:	/* ブラッディラスト */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_BERSERK].timer != -1)
			status_change_end(bl,SC_BERSERK,-1);
		break;
	case UNT_WARMER:		/* ウォーマー */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_WARMER].timer != -1)
			status_change_end(bl,SC_WARMER,-1);
		break;
	case UNT_THORNS_TRAP:	/* ソーントラップ */
		{
			struct block_list *target = map_id2bl(sg->val2);
			if (target && target == bl)
				status_change_end(bl,SC_THORNS_TRAP,-1);
			sg->limit = DIFF_TICK(tick,sg->tick)+1000;
		}
		break;
	case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
	case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
	case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
	case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer != -1 && sc->data[type].val2 == src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
/*	default:
		if(battle_config.error_log)
			printf("skill_unit_onout: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}
	return 0;
}

/*==========================================
 * スキルユニット効果発動/離脱処理(foreachinarea)
 *------------------------------------------
 */
static int skill_unit_effect(struct block_list *bl,va_list ap)
{
	struct skill_unit *unit;
	struct skill_unit_group *group;
	int flag;
	unsigned int tick;
	static int called = 0;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = va_arg(ap,struct skill_unit*));
	nullpo_retr(0, group = unit->group);

	tick = va_arg(ap,unsigned int);
	flag = va_arg(ap,unsigned int);

	if(!(bl->type & (BL_PC | BL_MOB | BL_MERC | BL_ELEM)))
		return 0;

	if(!unit->alive)
		return 0;

	if(flag) {
		skill_unit_onplace(unit,bl,tick);
	} else {
		skill_unit_onout(unit,bl,tick);
		unit = map_find_skill_unit_oncell(bl,bl->x,bl->y,group->skill_id,unit);
		if(unit && called == 0) {
			called = 1;
			skill_unit_onplace(unit,bl,tick);
			called = 0;
		}
	}

	return 0;
}

/*==========================================
 * スキルユニットの限界イベント
 *------------------------------------------
 */
static int skill_unit_onlimit(struct skill_unit *src,unsigned int tick)
{
	struct skill_unit_group *sg;

	nullpo_retr(0, src);
	nullpo_retr(0, sg=src->group);

	switch(sg->unit_id){
	case UNT_ICEWALL:	/* アイスウォール */
		map_setcell(src->bl.m,src->bl.x,src->bl.y,src->val2);
		clif_changemapcell(src->bl.m,src->bl.x,src->bl.y,src->val2,1);
		break;
	case UNT_CALLFAMILY:
		{
			struct map_session_data *sd = map_id2sd(sg->src_id);
			if(sd == NULL)
				break;
			if(sg->skill_id == WE_CALLPARTNER) {		/* あなたに逢いたい */
				if(sd->status.partner_id)
					intif_charmovereq2(sd,map_charid2nick(sd->status.partner_id),map[src->bl.m].name,src->bl.x,src->bl.y,0);
			}
			else if(sg->skill_id == WE_CALLPARENT) {	/* ママ、パパ、来て */
				if(sd->status.parent_id[0] && sd->status.parent_id[1]) {
					intif_charmovereq2(sd,map_charid2nick(sd->status.parent_id[0]),map[src->bl.m].name,src->bl.x,src->bl.y,2);
					intif_charmovereq2(sd,map_charid2nick(sd->status.parent_id[1]),map[src->bl.m].name,src->bl.x,src->bl.y,2);
				}
			}
			else if(sg->skill_id == WE_CALLBABY) {		/* 坊や、いらっしゃい */
				if(sd->status.baby_id)
					intif_charmovereq2(sd,map_charid2nick(sd->status.baby_id),map[src->bl.m].name,src->bl.x,src->bl.y,2);
			}
		}
		break;
	}
	return 0;
}

/*==========================================
 * スキルユニットのダメージイベント
 *------------------------------------------
 */
int skill_unit_ondamaged(struct skill_unit *src,struct block_list *bl,int damage,unsigned int tick)
{
	struct skill_unit_group *sg;

	nullpo_retr(0, src);
	nullpo_retr(0, sg = src->group);

	switch(sg->unit_id) {
	case UNT_FIREPILLAR_WAITING:	/* ファイアーピラー(発動前) */
	case UNT_ICEWALL:		/* アイスウォール */
	case UNT_SKIDTRAP:		/* スキッドトラップ */
	case UNT_LANDMINE:		/* ランドマイン */
	case UNT_SHOCKWAVE:		/* ショックウェーブトラップ */
	case UNT_SANDMAN:		/* サンドマン */
	case UNT_FLASHER:		/* フラッシャー */
	case UNT_FREEZINGTRAP:		/* フリージングトラップ */
	case UNT_TALKIEBOX:		/* トーキーボックス */
	case UNT_ANKLESNARE:		/* アンクルスネア */
	case UNT_WALLOFTHORN:	/* ソーンウォール */
		src->val1 -= damage;
		break;
	case UNT_BLASTMINE:		/* ブラストマイン */
		if(bl == NULL) {
			damage = 0;
			break;
		}
		skill_blown(bl,&src->bl,2);	// 吹き飛ばしてみる
		break;
	case UNT_REVERBERATION:	/* 振動残響 */
		src->val1 -= 1;
		break;
	default:
		damage = 0;
		break;
	}
	return damage;
}

/*---------------------------------------------------------------------------- */

/*==========================================
 * 範囲内キャラ存在確認判定処理(foreachinarea)
 *------------------------------------------
 */
static int skill_check_condition_char_sub(struct block_list *bl,va_list ap)
{
	int *c;
	struct map_session_data *sd, *ssd;
	struct skill_condition *cnd;
	int sp;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd  = (struct map_session_data *)bl);
	nullpo_retr(0, ssd = va_arg(ap,struct map_session_data *));
	nullpo_retr(0, c   = va_arg(ap,int *));
	nullpo_retr(0, cnd = va_arg(ap, struct skill_condition *));

	// チェックしない設定ならcにありえない大きな数字を返して終了
	// 本当はforeachの前にやりたいけど設定適用箇所をまとめるためにここへ
	if(!battle_config.player_skill_partner_check) {
		(*c) = 0x7fffffff;
		return 0;
	}

	if(sd == ssd)
		return 0;

	sp = skill_get_sp(cnd->id,cnd->lv);

	switch(cnd->id){
	case PR_BENEDICTIO:		/* 聖体降福 */
		if( (*c) < 2 &&
		    (sd->s_class.job == PC_JOB_AL || sd->s_class.job == PC_JOB_PR || sd->s_class.job == PC_JOB_MO ||
		     sd->s_class.job == PC_JOB_AB || sd->s_class.job == PC_JOB_SR) &&
		    (sd->bl.y == ssd->bl.y && (sd->bl.x == ssd->bl.x-1 || sd->bl.x == ssd->bl.x+1)) &&
		    sd->status.sp >= sp/2 )
			(*c)++;
		break;
	case BD_LULLABY:		/* 子守歌 */
	case BD_RICHMANKIM:		/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:		/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:		/* ニーベルングの指輪 */
	case BD_ROKISWEIL:		/* ロキの叫び */
	case BD_INTOABYSS:		/* 深淵の中に */
	case BD_SIEGFRIED:		/* 不死身のジークフリード */
	case BD_RAGNAROK:		/* 神々の黄昏 */
	case CG_MOONLIT:		/* 月明りの下で */
		if( (*c) < 1 ) {
			int weapon = sd->status.weapon;
			if(weapon >= WT_MAX)
					weapon -= WT_DOUBLE_DD + WT_MAX;

		    if( (((ssd->s_class.job == PC_JOB_BA || ssd->s_class.job == PC_JOB_MI) && (sd->s_class.job == PC_JOB_DC || sd->s_class.job == PC_JOB_WA)) ||
			    ((ssd->s_class.job == PC_JOB_DC || ssd->s_class.job == PC_JOB_WA) && (sd->s_class.job == PC_JOB_BA || sd->s_class.job == PC_JOB_MI))) &&
			    sd->status.party_id > 0 &&
			    ssd->status.party_id > 0 &&
			    sd->status.party_id == ssd->status.party_id &&
			    !unit_isdead(&sd->bl) &&
			    !pc_issit(sd) &&
			    sd->sc.data[SC_DANCING].timer == -1 &&
			    (skill_get_weapontype(cnd->id) & (1<<weapon)) &&
			    sd->status.sp >= sp &&
			    sd->sc.data[SC_STONE].timer == -1 &&
			    sd->sc.data[SC_FREEZE].timer == -1 &&
			    sd->sc.data[SC_SILENCE].timer == -1 &&
			    sd->sc.data[SC_SLEEP].timer == -1 &&
			    sd->sc.data[SC_STUN].timer == -1 )
				(*c) = pc_checkskill(sd,cnd->id);
		}
		break;
	case WM_GREAT_ECHO:					/* グレートエコー */
	case WM_SONG_OF_MANA:				/* マナの歌 */
	case WM_DANCE_WITH_WUG:				/* ダンスウィズウォーグ */
	case WM_SOUND_OF_DESTRUCTION:		/* サウンドオブディストラクション */
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
	case WM_LERADS_DEW:					/* レーラズの霧 */
	case WM_MELODYOFSINK:				/* メロディーオブシンク */
	case WM_BEYOND_OF_WARCRY:			/* ビヨンドオブウォークライ */
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		if( (*c) < 1 &&
		    (sd->s_class.job == PC_JOB_MI || sd->s_class.job == PC_JOB_WA) &&
		    sd->status.party_id > 0 &&
		    ssd->status.party_id > 0 &&
		    sd->status.party_id == ssd->status.party_id &&
		    !unit_isdead(&sd->bl) &&
		    !pc_issit(sd) &&
		    sd->sc.data[SC_STONE].timer == -1 &&
		    sd->sc.data[SC_FREEZE].timer == -1 &&
		    sd->sc.data[SC_SILENCE].timer == -1 &&
		    sd->sc.data[SC_SLEEP].timer == -1 &&
		    sd->sc.data[SC_STUN].timer == -1 )
			(*c)++;
		break;
	}
	return 0;
}

/*==========================================
 * 範囲内キャラ存在確認判定後スキル使用処理(foreachinarea)
 *------------------------------------------
 */
static int skill_check_condition_use_sub(struct block_list *bl,va_list ap)
{
	int *c;
	struct map_session_data *sd, *ssd;
	int skillid, skilllv, sp;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd  = (struct map_session_data *)bl);
	nullpo_retr(0, ssd = va_arg(ap,struct map_session_data *));
	nullpo_retr(0, c   = va_arg(ap,int *));

	// チェックしない設定ならcにありえない大きな数字を返して終了
	// 本当はforeachの前にやりたいけど設定適用箇所をまとめるためにここへ
	if(!battle_config.player_skill_partner_check) {
		(*c) = 0x7fffffff;
		return 0;
	}

	if(sd == ssd)
		return 0;

	skillid = ssd->ud.skillid;
	skilllv = ssd->ud.skilllv;

	sp = skill_get_sp(skillid,skilllv);

	switch(skillid){
	case PR_BENEDICTIO:		/* 聖体降福 */
		if( (*c) < 2 &&
		    (sd->s_class.job == PC_JOB_AL || sd->s_class.job == PC_JOB_PR || sd->s_class.job == PC_JOB_MO ||
		     sd->s_class.job == PC_JOB_AB || sd->s_class.job == PC_JOB_SR) &&
		    (sd->bl.y == ssd->bl.y && (sd->bl.x == ssd->bl.x-1 || sd->bl.x == ssd->bl.x+1)) &&
		    sd->status.sp >= sp/2 )
		{
			sd->status.sp -= sp/2;
			clif_updatestatus(sd,SP_SP);
			(*c)++;
		}
		break;
	case BD_LULLABY:		/* 子守歌 */
	case BD_RICHMANKIM:		/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:		/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:		/* ニーベルングの指輪 */
	case BD_ROKISWEIL:		/* ロキの叫び */
	case BD_INTOABYSS:		/* 深淵の中に */
	case BD_SIEGFRIED:		/* 不死身のジークフリード */
	case BD_RAGNAROK:		/* 神々の黄昏 */
	case CG_MOONLIT:		/* 月明りの下で */
		if( (*c) < 1 ) {
			int weapon = sd->status.weapon;
			if(weapon >= WT_MAX)
				weapon -= WT_DOUBLE_DD + WT_MAX;

		    if( (((ssd->s_class.job == PC_JOB_BA || ssd->s_class.job == PC_JOB_MI) && (sd->s_class.job == PC_JOB_DC || sd->s_class.job == PC_JOB_WA)) ||
			    ((ssd->s_class.job == PC_JOB_DC || ssd->s_class.job == PC_JOB_WA) && (sd->s_class.job == PC_JOB_BA || sd->s_class.job == PC_JOB_MI))) &&
			    pc_checkskill(sd,skillid) > 0 &&
			    sd->status.party_id > 0 &&
			    ssd->status.party_id > 0 &&
			    sd->status.party_id == ssd->status.party_id &&
			    !unit_isdead(&sd->bl) &&
			    !pc_issit(sd) &&
			    sd->sc.data[SC_DANCING].timer == -1 &&
			    (skill_get_weapontype(skillid) & (1<<weapon)) &&
			    sd->status.sp >= sp &&
			    sd->sc.data[SC_STONE].timer == -1 &&
			    sd->sc.data[SC_FREEZE].timer == -1 &&
			    sd->sc.data[SC_SILENCE].timer == -1 &&
			    sd->sc.data[SC_SLEEP].timer == -1 &&
			    sd->sc.data[SC_STUN].timer == -1 )
			{
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				ssd->sc.data[SC_DANCING].val4 = bl->id;
				clif_skill_nodamage(bl,&ssd->bl,skillid,skilllv,1);
				status_change_start(bl,SC_DANCING,skillid,ssd->sc.data[SC_DANCING].val2,0,ssd->bl.id,skill_get_time(skillid,skilllv)+1000,0);
				sd->skill_dance.id = sd->ud.skillid = skillid;
				sd->skill_dance.lv = sd->ud.skilllv = skilllv;
				ssd->dance.x = sd->bl.x;
				ssd->dance.y = sd->bl.y;
				(*c)++;
			}
		}
		break;
	case WM_GREAT_ECHO:					/* グレートエコー */
	case WM_SONG_OF_MANA:				/* マナの歌 */
	case WM_DANCE_WITH_WUG:				/* ダンスウィズウォーグ */
	case WM_SOUND_OF_DESTRUCTION:		/* サウンドオブディストラクション */
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
	case WM_LERADS_DEW:					/* レーラズの霧 */
	case WM_MELODYOFSINK:				/* メロディーオブシンク */
	case WM_BEYOND_OF_WARCRY:			/* ビヨンドオブウォークライ */
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		if( (*c) < 1 &&
		    (sd->s_class.job == PC_JOB_MI || sd->s_class.job == PC_JOB_WA) &&
		    sd->status.party_id > 0 &&
		    ssd->status.party_id > 0 &&
		    sd->status.party_id == ssd->status.party_id &&
		    !unit_isdead(&sd->bl) &&
		    !pc_issit(sd) &&
		    sd->sc.data[SC_STONE].timer == -1 &&
		    sd->sc.data[SC_FREEZE].timer == -1 &&
		    sd->sc.data[SC_SILENCE].timer == -1 &&
		    sd->sc.data[SC_SLEEP].timer == -1 &&
		    sd->sc.data[SC_STUN].timer == -1 )
		{
			if(sd->status.sp < sp)
				sd->status.sp = 0;
			else
				sd->status.sp -= sp;
			clif_updatestatus(sd,SP_SP);
			(*c)++;
		}
		break;
	}
	return 0;
}

/*==========================================
 * 範囲内バイオプラント、スフィアマイン用Mob存在確認判定処理(foreachinarea)
 *------------------------------------------
 */
static int skill_check_condition_mob_master_sub(struct block_list *bl,va_list ap)
{
	int src_id, mob_class;
	struct mob_data *md;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, md = (struct mob_data*)bl);

	src_id    = va_arg(ap,int);
	mob_class = va_arg(ap,int);

	if(md->class_ == mob_class && md->master_id == src_id)
		return 1;

	return 0;
}

/*==========================================
 * スキル使用条件（偽で使用失敗）
 *------------------------------------------
 */
static int skill_check_condition2_pc(struct map_session_data *sd, struct skill_condition *cnd, int type);
static int skill_check_condition2_mob(struct mob_data *md, struct skill_condition *cnd, int type);
static int skill_check_condition2_pet(struct pet_data *pd, struct skill_condition *cnd, int type);
static int skill_check_condition2_hom(struct homun_data *hd, struct skill_condition *cnd, int type);
static int skill_check_condition2_merc(struct merc_data *mcd, struct skill_condition *cnd, int type);
static int skill_check_condition2_elem(struct elem_data *eld, struct skill_condition *cnd, int type);

int skill_check_condition(struct block_list *bl, int type)
{
	struct unit_data *ud = unit_bl2ud( bl );
	struct skill_condition cnd;
	int r;

	nullpo_retr( 0, ud );

	cnd.id     = ud->skillid;
	cnd.lv     = ud->skilllv;
	cnd.x      = ud->skillx;
	cnd.y      = ud->skilly;
	cnd.target = ud->skilltarget;

	r = skill_check_condition2( bl, &cnd, type );
	// skill_check_condition 内部で書き換えた値を戻す
	if( r ) {
		ud->skillid     = cnd.id;
		ud->skilllv     = cnd.lv;
		ud->skillx      = cnd.x;
		ud->skilly      = cnd.y;
		ud->skilltarget = cnd.target;
	}
	return r;
}

int skill_check_condition2(struct block_list *bl, struct skill_condition *cnd, int type)
{
	struct map_session_data *sd;
	struct map_session_data *target_sd;
	struct status_change    *sc;
	struct block_list *target;

	nullpo_retr(0, bl);
	nullpo_retr(0, cnd);

	target = map_id2bl( cnd->target );
	if( target && !(target->type & BL_CHAR) ) {
		// スキル対象はPC,MOB,HOM,MERCのみ
		target = NULL;
	}

	sd        = BL_DOWNCAST( BL_PC, bl );
	target_sd = BL_DOWNCAST( BL_PC, target );

	sc = status_get_sc(bl);

	// PC, MOB, PET, HOM, MERC, ELEM 共通の失敗はここに記述

	// 状態異常関連
	if(sc && sc->count > 0)
	{
		if( sc->data[SC_SILENCE].timer!=-1 ||
		    sc->data[SC_ROKISWEIL].timer!=-1 ||
		    (sc->data[SC_AUTOCOUNTER].timer != -1 && cnd->id != KN_AUTOCOUNTER) ||
		    (sc->data[SC_DEATHBOUND].timer != -1 && cnd->id != RK_DEATHBOUND) ||
		    sc->data[SC_STEELBODY].timer != -1 ||
		    sc->data[SC_BERSERK].timer != -1 ||
		    (sc->data[SC_MARIONETTE].timer !=-1 && cnd->id != CG_MARIONETTE) ||
		    sc->data[SC_OBLIVIONCURSE].timer != -1 ||
			sc->data[SC_WHITEIMPRISON].timer != -1 ||
		    (sc->data[SC_STASIS].timer != -1 && skill_get_skill_type(cnd->id) == BF_MAGIC) ||
		    sc->data[SC_KINGS_GRACE].timer != -1 ||
			sc->data[SC__SHADOWFORM].timer != -1 ||
			sc->data[SC__MANHOLE].timer != -1 ||
			(sc->data[SC__INVISIBILITY].timer != -1 && cnd->id != SC_INVISIBILITY) ||
			sc->data[SC__IGNORANCE].timer != -1 ||
			sc->data[SC_CURSEDCIRCLE].timer != -1 ||
			sc->data[SC_DIAMONDDUST].timer != -1)
			return 0;

		if(sc->data[SC_BLADESTOP].timer != -1) {
			int lv = sc->data[SC_BLADESTOP].val1;
			if(sc->data[SC_BLADESTOP].val2 == 1) return 0;	// 白羽された側なのでダメ
			if(lv==1) return 0;
			if(lv==2 && cnd->id!=MO_FINGEROFFENSIVE) return 0;
			if(lv==3 && cnd->id!=MO_FINGEROFFENSIVE && cnd->id!=MO_INVESTIGATE) return 0;
			if(lv==4 && cnd->id!=MO_FINGEROFFENSIVE && cnd->id!=MO_INVESTIGATE && cnd->id!=MO_CHAINCOMBO) return 0;
			if(lv==5 && cnd->id!=MO_FINGEROFFENSIVE && cnd->id!=MO_INVESTIGATE && cnd->id!=MO_CHAINCOMBO && cnd->id!=MO_EXTREMITYFIST) return 0;
		}

		if(target) {
			if(sc->data[SC_WINKCHARM].timer != -1 && sc->data[SC_WINKCHARM].val2 == target->id)
				return 0;
			if(sc->data[SC_SIREN].timer != -1 && sc->data[SC_SIREN].val2 == target->id)
				return 0;
		}

		/* 演奏/ダンス中 */
		if(sc->data[SC_DANCING].timer != -1 && sc->data[SC_LONGINGFREEDOM].timer == -1)
		{
			if(sd && pc_checkskill(sd,WM_LESSON) >= 5 && cnd->id >= WA_SWING_DANCE && cnd->id <= WM_UNLIMITED_HUMMING_VOICE) {
				;
			}
			else {
				if(!battle_config.player_skill_partner_check &&
				   !(battle_config.sole_concert_type & 2) &&	// 単独合奏中に矢撃ち/MSができない設定
				   cnd->id != BD_ADAPTATION && cnd->id != CG_LONGINGFREEDOM)
				{
					switch (sc->data[SC_DANCING].val1)
					{
					case BD_LULLABY:			// 子守歌
					case BD_RICHMANKIM:			// ニヨルドの宴
					case BD_ETERNALCHAOS:		// 永遠の混沌
					case BD_DRUMBATTLEFIELD:	// 戦太鼓の響き
					case BD_RINGNIBELUNGEN:		// ニーベルングの指輪
					case BD_ROKISWEIL:			// ロキの叫び
					case BD_INTOABYSS:			// 深淵の中に
					case BD_SIEGFRIED:			// 不死身のジークフリード
					case BD_RAGNAROK:			// 神々の黄昏
					case CG_MOONLIT:			// 月明りの下で
						return 0;
					}
				}
				if(cnd->id != BD_ADAPTATION && cnd->id != BA_MUSICALSTRIKE && cnd->id != DC_THROWARROW && cnd->id != CG_LONGINGFREEDOM)
					return 0;
			}
		}
	}

	// 魂スキルかどうかの判定
	if( cnd->id == SL_ALCHEMIST ||
	    (cnd->id >= SL_MONK && cnd->id <= SL_SOULLINKER && cnd->id != BS_ADRENALINE2) ||
	    cnd->id == SL_HIGH ||
	    (cnd->id >= SL_DEATHKNIGHT && cnd->id <= SL_GUNNER) )
	{
		int job, fail = 0;

		// 検証に時間がかかるので塊系で２プレイヤーがいない場合は一律弾く
		if(!sd || !target_sd)
			return 0;

		job = target_sd->s_class.job;

		switch(cnd->id)
		{
			case SL_ALCHEMIST:   if(job != PC_JOB_AM && job != PC_JOB_GN) fail = 1; break; // アルケミストの魂
			case SL_MONK:        if(job != PC_JOB_MO && job != PC_JOB_SR) fail = 1; break; // モンクの魂
			case SL_STAR:        if(job != PC_JOB_SG) fail = 1; break; // ケンセイの魂
			case SL_SAGE:        if(job != PC_JOB_SA && job != PC_JOB_SO) fail = 1; break; // セージの魂
			case SL_CRUSADER:    if(job != PC_JOB_CR && job != PC_JOB_LG) fail = 1; break; // クルセイダーの魂
			case SL_SUPERNOVICE: if(job != PC_JOB_SNV && job != PC_JOB_ESNV) fail = 1; break; // スーパーノービスの魂
			case SL_KNIGHT:      if(job != PC_JOB_KN && job != PC_JOB_RK) fail = 1; break; // ナイトの魂
			case SL_WIZARD:      if(job != PC_JOB_WZ && job != PC_JOB_WL) fail = 1; break; // ウィザードの魂
			case SL_PRIEST:      if(job != PC_JOB_PR && job != PC_JOB_AB) fail = 1; break; // プリーストの魂
			case SL_BARDDANCER:  if(job != PC_JOB_BA && job != PC_JOB_DC && job != PC_JOB_MI && job != PC_JOB_WA) fail = 1; break; // バードとダンサーの魂
			case SL_ROGUE:       if(job != PC_JOB_RG && job != PC_JOB_SC) fail = 1; break; // ローグの魂
			case SL_ASSASIN:     if(job != PC_JOB_AS && job != PC_JOB_GC) fail = 1; break; // アサシンの魂
			case SL_BLACKSMITH:  if(job != PC_JOB_BS && job != PC_JOB_NC) fail = 1; break; // ブラックスミスの魂
			case SL_HUNTER:      if(job != PC_JOB_HT && job != PC_JOB_RA) fail = 1; break; // ハンターの魂
			case SL_SOULLINKER:  if(job != PC_JOB_SL) fail = 1; break; // ソウルリンカーの魂
			case SL_HIGH:        if(job < PC_JOB_SM || job > PC_JOB_TF || target_sd->s_class.upper != PC_UPPER_HIGH) fail = 1; break; // 一次上位職業の魂
			default: fail = 1;
		}
		if(battle_config.job_soul_check && fail) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		// 最終判定
		if(!battle_config.soulskill_can_be_used_for_myself && sd == target_sd)
		{
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,0))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,3000,0,gettick()+status_get_amotion(&sd->bl));
			return 0;
		}
	}

	// スキルごとの特殊判定
	switch( cnd->id ) {
	case PR_TURNUNDEAD:			/* ターンアンデッド */
		if(!target)
			return 0;
		if(!battle_check_undead(status_get_race(target),status_get_elem_type(target)))
			return 0;
		break;
	case AM_POTIONPITCHER:		/* ポーションピッチャー */
		if(target) {
			if(bl == target)	// 対象が自分ならOK
				break;
			if(target->type == BL_HOM) {
				struct homun_data *thd = (struct homun_data *)target;
				if(thd && thd->msd) {
					int pid;
					if(sd && sd == thd->msd)	// 自分のホムはOK
						break;
					pid = status_get_party_id(bl);
					if(pid > 0 && pid == status_get_party_id(&thd->msd->bl))	// PTMのホムはOK
						break;
				}
			} else {
				int pid, gid;
				pid = status_get_party_id(bl);
				if(pid > 0 && pid == status_get_party_id(target))	// 同じPTはOK
					break;
				gid = status_get_guild_id(bl);
				if(gid > 0 && gid == status_get_guild_id(target))	// 同じギルドはOK
					break;
				if(guild_check_alliance(gid,status_get_guild_id(target),0))	// 同盟ギルドはOK
					break;
			}
		}
		if(sd)
			clif_skill_fail(sd,cnd->id,0,0,0);
		return 0;

	case MO_KITRANSLATION:	/* 気功転移 */
		if( !target_sd ||
		    bl == target ||
		    target_sd->status.party_id <= 0 ||
		    status_get_party_id(bl) != target_sd->status.party_id ||
		    target_sd->status.class_ == PC_CLASS_GS )
		{
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case ALL_RESURRECTION:	/* リザレクション */
		if(!target)
			return 0;
		if(!unit_isdead(target) && !battle_check_undead(status_get_race(target),status_get_elem_type(target)))
			return 0;
		break;
	case HP_BASILICA:		/* バジリカ */
		if(!type) {	// 詠唱開始時のみチェック
			if(sc && sc->data[SC_BASILICA].timer != -1)
				break;
			skill_area_temp[1] = bl->id;
			if(skill_check_unit_range(bl->m,bl->x,bl->y,cnd->id,cnd->lv)) {
				if(sd)
					clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
			if(skill_check_unit_range2(bl->m,bl->x,bl->y,cnd->id,cnd->lv)) {
				if(sd)
					clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case HT_POWER:		/* ビーストストレイピング */
		if(sc && sc->data[SC_HUNTER].timer != -1 && sc->data[SC_DOUBLE].timer != -1) {
			int race = status_get_race(target);
			if(race == RCT_BRUTE || race == RCT_INSECT)
				break;
		}
		if(sd)
			clif_skill_fail(sd,cnd->id,0,0,0);
		return 0;

	case AM_TWILIGHT1:
		if(!sc || sc->data[SC_ALCHEMIST].timer == -1) {
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case AM_TWILIGHT2:
		if(!sd)
			return 0;
		if(battle_config.twilight_party_check) {
			int f = 0;
			if(sd->status.party_id > 0 && sc && sc->data[SC_ALCHEMIST].timer != -1)
			{
				struct party *pt = party_search(sd->status.party_id);
				if(pt) {
					int i;
					for(i=0; i<MAX_PARTY; i++) {
						if(pt->member[i].sd) {
							switch(pt->member[i].sd->status.class_) {
								case PC_CLASS_SNV:
								case PC_CLASS_SNV_B:
								case PC_CLASS_ESNV:
								case PC_CLASS_ESNV_B:
									f = 1;
									break;
							}
							if(f)
								break;
						}
					}
				}
			}
			if(f == 0) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case AM_TWILIGHT3:
		if(!sd)
			return 0;
		if(battle_config.twilight_party_check) {
			int f = 0;
			if(sd->status.party_id > 0 && sc && sc->data[SC_ALCHEMIST].timer != -1)
			{
				struct party *pt = party_search(sd->status.party_id);
				if(pt) {
					int i;
					for(i=0; i<MAX_PARTY; i++) {
						if(pt->member[i].sd && pt->member[i].sd->status.class_ == PC_CLASS_TK) {
							f = 1;
							break;
						}
					}
				}
			}
			if(f == 0) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case AM_BERSERKPITCHER:
		if(target_sd && target_sd->status.base_level < 85) {
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case NPC_SUMMONSLAVE:
	case NPC_SUMMONMONSTER:
	case NPC_DEATHSUMMON:		/* デスサモン */
		if(bl->type != BL_MOB)
			return 0;
		break;
	case WE_BABY:
		if(!sd)
			return 0;
		if( !target_sd ||
		    (sd->status.parent_id[0] != target_sd->status.char_id && sd->status.parent_id[1] != target_sd->status.char_id) )
		{
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case CR_PROVIDENCE:	// プロヴィデンス
		if(!target_sd)
			return 0;
		if(target_sd->s_class.job == PC_JOB_CR || target_sd->s_class.job == PC_JOB_LG) {
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case HP_ASSUMPTIO:	// アスムプティオ
	case CASH_ASSUMPTIO:	// パーティーアスムプティオ
		if(map[bl->m].flag.gvg && !battle_config.allow_assumptop_in_gvg) {
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case CG_MARIONETTE:	// マリオネット
		if(!sd || !target_sd)
			return 0;

		// 既に自分が接続していた相手なら止める
		if(sc && sc->data[SC_MARIONETTE].timer != -1 && sc->data[SC_MARIONETTE].val2 == target_sd->bl.id) {
			status_change_end(bl,SC_MARIONETTE,-1);
			return 0;
		}

		// 自分・同じクラス・マリオネット状態なら失敗
		if( sd == target_sd || sd->s_class.job == target_sd->s_class.job ||
		    sd->sc.data[SC_MARIONETTE].timer != -1 || sd->sc.data[SC_MARIONETTE2].timer != -1 ||
		    target_sd->sc.data[SC_MARIONETTE].timer != -1 || target_sd->sc.data[SC_MARIONETTE2].timer != -1)
		{
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SR_POWERVELOCITY:	/* 全気注入 */
		if( !target_sd ||
		    bl == target ||
		    target_sd->status.class_ == PC_CLASS_GS )
		{
			if(sd)
				clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case WM_DEADHILLHERE:	/* 生死の境で */
		if(!target)
			return 0;
		if(!unit_isdead(target))
			return 0;
		break;
	}

	if(bl->type == BL_PC)
		return skill_check_condition2_pc((struct map_session_data*)bl, cnd, type);
	if(bl->type == BL_MOB)
		return skill_check_condition2_mob((struct mob_data*)bl, cnd, type);
	if(bl->type == BL_PET)
		return skill_check_condition2_pet((struct pet_data*)bl, cnd, type);
	if(bl->type == BL_HOM)
		return skill_check_condition2_hom((struct homun_data*)bl, cnd, type);
	if(bl->type == BL_MERC)
		return skill_check_condition2_merc((struct merc_data*)bl, cnd, type);
	if(bl->type == BL_ELEM)
		return skill_check_condition2_elem((struct elem_data*)bl, cnd, type);

	return 0;
}

// PC用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_pc(struct map_session_data *sd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,hp_rate,sp_rate,zeny,weapon,state,spiritball,coin,skilldb_id,arrow;
	int itemid[10],amount[10];
	int item_nocost = 0;
	struct block_list *bl = NULL, *target = NULL;
	struct unit_data  *ud = NULL;

	nullpo_retr(0, sd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, bl = &sd->bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	target = map_id2bl( cnd->target );

	// チェイス、ハイド、クローキング時のスキル
	if(sd->sc.option&OPTION_HIDE) {
		switch(cnd->id) {
		case TF_HIDING:
		case AS_GRIMTOOTH:
		case RG_BACKSTAP:
		case RG_RAID:
		case NJ_KIRIKAGE:
		case NJ_SHADOWJUMP:
		case KO_YAMIKUMO:
			break;
		default:
			return 0;
		}
	}

	if(pc_ischasewalk(sd) && cnd->id != ST_CHASEWALK)	// チェイスウォーク
	 	return 0;

	// ソウルリンカーで使えないスキル
	if(sd->status.class_ == PC_CLASS_SL) {
		switch(cnd->id) {
			case TK_READYSTORM:
			case TK_READYDOWN:
			case TK_READYTURN:
			case TK_READYCOUNTER:
			case TK_JUMPKICK:
				if( battle_config.soul_linker_battle_mode == 0 ||
				    (battle_config.soul_linker_battle_mode == 1 && sd->sc.data[SC_SOULLINKER].timer == -1) ) {
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
				break;
			case SL_KAIZEL:		/* カイゼル */
			case SL_KAAHI:		/* カアヒ */
			case SL_KAITE:		/* カイト */
			case SL_KAUPE:		/* カウプ */
				if(target == NULL || target->type != BL_PC) {
					// 対象が人以外失敗
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
				if(battle_config.soul_linker_battle_mode_ka == 0) {
					struct map_session_data *target_sd = (struct map_session_data *)target;
					if( target_sd->status.char_id == sd->status.char_id ||
					    target_sd->status.char_id == sd->status.partner_id ||
					    target_sd->status.char_id == sd->status.baby_id ||
					    sd->sc.data[SC_SOULLINKER].timer != -1 ) {
						;	// 何もしない
					} else {
						clif_skill_fail(sd,cnd->id,0,0,0);
						return 0;
					}
				}
				break;
		}
	}

	// ウォーグライダー中
	if(pc_iswolfmount(sd)) {
		switch(cnd->id) {
			case HT_SKIDTRAP:
			case HT_LANDMINE:
			case HT_ANKLESNARE:
			case HT_SHOCKWAVE:
			case HT_SANDMAN:
			case HT_FLASHER:
			case HT_FREEZINGTRAP:
			case HT_BLASTMINE:
			case HT_CLAYMORETRAP:
			case HT_TALKIEBOX:
			case RA_DETONATOR:
			case RA_CLUSTERBOMB:
			case RA_WUGRIDER:
			case RA_WUGDASH:
			case RA_WUGSTRIKE:
			case RA_FIRINGTRAP:
			case RA_ICEBOUNDTRAP:
				break;
			default:
				clif_skill_fail(sd,cnd->id,0x17,0,0);
				return 0;
		}
	}

	// GMハイド中で、コンフィグでハイド中攻撃不可 GMレベルが指定より大きい場合
	if(sd->sc.option&OPTION_SPECIALHIDING && battle_config.hide_attack == 0 && pc_isGM(sd) < battle_config.gm_hide_attack_lv)
		return 0;	// 隠れてスキル使うなんて卑怯なGMデスネ

	if(battle_config.gm_skilluncond > 0 && pc_isGM(sd) >= battle_config.gm_skilluncond)
		return 1;
	// 点穴-快-は睡眠状態では使えない
	if( cnd->id  == SR_GENTLETOUCH_CURE ) {
		if( sd->sc.opt1 == OPT1_SLEEP ) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
	} else {
		if(sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
	}
	if(pc_is90overweight(sd)) {
		clif_skill_fail(sd,cnd->id,9,0,0);
		return 0;
	}

	if(cnd->id == sd->skill_menu.id)
		return 0;

	// 駆け足時にスキルを使った場合終了
	// 再度の駆け足か飛び蹴りは除外
	if(sd->sc.data[SC_RUN].timer != -1 && cnd->id != TK_RUN && cnd->id != TK_JUMPKICK)
		status_change_end(bl,SC_RUN,-1);

	// ウォーグダッシュ中のスキル使用
	if(sd->sc.data[SC_WUGDASH].timer != -1 && cnd->id != RA_WUGDASH)
		status_change_end(bl,SC_WUGDASH,-1);

	/* アイテムの場合の判定 */
	if(sd->skill_item.id == cnd->id) {
		if(type == 0)			// 初回の呼び出し（unit.cより）なら無条件で許可
			return 1;
		sd->skill_item.id   = -1;
		sd->skill_item.lv   = -1;
		if( !sd->skill_item.flag )	// フラグないなら許可
			return 1;
	}

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	weapon     = skill_db[skilldb_id].weapon;
	state      = skill_db[skilldb_id].state;
	spiritball = (cnd->lv <= 0)? 0: skill_db[skilldb_id].spiritball[cnd->lv-1];
	coin       = (cnd->lv <= 0)? 0: skill_db[skilldb_id].coin[cnd->lv-1];
	arrow      = skill_get_arrow_cost(cnd->id,cnd->lv);

	for(i=0; i<10; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}

	if(hp_rate > 0)
		hp += sd->status.hp * hp_rate / 100;
	else
		hp += sd->status.max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += sd->status.sp * sp_rate / 100;
	else
		sp += sd->status.max_sp * abs(sp_rate) / 100;

	if(sd->skill_used.id == BD_ENCORE && cnd->id == sd->skill_dance.id)	// アンコール時はSP消費が半分
		sp /= 2;
	if(sd->sc.data[SC_RECOGNIZEDSPELL].timer!=-1)		// リゴグナイズドスペル時は消費SP25%増加
		sp = sp * 125 / 100;
	if(sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].timer != -1) {	// エンドレスハミングボイス時は消費SP～15%増加
		int cost = 15;
		cost -= sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].val4 * 3;
		if(cost > 0)
			sp = sp * (100 + cost) / 100;
	}
	if(sd->skill_addspcost.count > 0) {		// カードによるSP使用量増加
		int i;
		for(i=0; i<sd->skill_addspcost.count; i++) {
			if(cnd->id == sd->skill_addspcost.id[i])
				sp += sd->skill_addspcost.rate[i];
		}
	}

#ifndef PRE_RENEWAL
	if(spiritball > 0)
		sd->spiritball.old = 0;
#endif

	switch( cnd->id ) {
	case SL_SMA:	/* エスマ */
		if(!(type&1) && sd->sc.data[SC_SMA].timer==-1){	// エスマ詠唱可能状態
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case CG_LONGINGFREEDOM:
		// 合奏以外使えない
		if(sd->sc.data[SC_DANCING].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		} else {
			int dance_id = sd->sc.data[SC_DANCING].val1;
			if( (dance_id >= BA_WHISTLE && dance_id <= BA_APPLEIDUN) ||
			    (dance_id >= DC_HUMMING && dance_id <= DC_SERVICEFORYOU) ||
			    dance_id == CG_MOONLIT || dance_id == CG_HERMODE )
			{
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case CG_MOONLIT:			/* 月明りの下で */
		{
			int x1,x2,y1,y2,i,j;
			int range = skill_get_unit_range(cnd->id,cnd->lv)+1;
			x1 = bl->x - range;
			x2 = bl->x + range;
			y1 = bl->y - range;
			y2 = bl->y + range;
			// 終始点がマップ外
			if(x1<0 || x2>=map[bl->m].xs-1 || y1<0 || y2>=map[bl->m].ys-1)
				return 0;

			for(i=x1;i<=x2;i++)
			{
				for(j=y1;j<=y2;j++)
				{
					if(map_getcell(bl->m,i,j,CELL_CHKNOPASS))
						return 0;
				}
			}
		}
		// fall through
	case BD_LULLABY:				/* 子守歌 */
	case BD_RICHMANKIM:				/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:			/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:		/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:			/* ニーベルングの指輪 */
	case BD_ROKISWEIL:				/* ロキの叫び */
	case BD_INTOABYSS:				/* 深淵の中に */
	case BD_SIEGFRIED:				/* 不死身のジークフリード */
	case BD_RAGNAROK:				/* 神々の黄昏 */
		{
			int range=1;
			int c=0;
			map_foreachinarea(skill_check_condition_char_sub,bl->m,
				bl->x-range,bl->y-range,
				bl->x+range,bl->y+range,BL_PC,sd,&c,cnd);
			// ダンス開始位置(合奏用)
			sd->dance.x = bl->x;
			sd->dance.y = bl->y;
			if(c<1){
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}else if(c==0x7fffffff){ // 相方不要設定だった
				;
			}else{
				cnd->lv = (c + cnd->lv)/2;
			}
		}
		break;
	case SA_ELEMENTWATER:	// 水
	case SA_ELEMENTGROUND:	// 土
	case SA_ELEMENTFIRE:	// 火
	case SA_ELEMENTWIND:	// 風
		{
			// PC -> PCだけ禁止する
			if( target && target->type == BL_PC )
			{
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case RA_WUGDASH:	// ウォーグダッシュ
		if(!pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	}

	// 特殊な消費処理
	switch(cnd->id)
	{
		case MC_MAMMONITE:	/* メマーナイト */
			if(pc_checkskill(sd,BS_UNFAIRLYTRICK)>0)
				zeny = zeny*90/100;
			break;
		case AL_HOLYLIGHT:	/* ホーリーライト */
			// プリーストの魂時はSP消費量増加
			if(sd->sc.data[SC_PRIEST].timer!=-1)
				sp = sp * 5;
			break;
#ifndef PRE_RENEWAL
		case AS_SONICBLOW:	/* ソニックブロー */
			if(sd->sc.data[SC_ASSASIN].timer != -1)
				sp = sp * 2;
			break;
#endif
		case SL_SMA:		/* エスマ */
		case SL_STUN:		/* エスタン */
		case SL_STIN:		/* エスティン */
			{
				int kaina_lv = pc_checkskill(sd,SL_KAINA);

				if(kaina_lv==0)
					break;
				if(sd->status.base_level>=90)
					sp -= sp*7*kaina_lv/100;
				else if(sd->status.base_level>=80)
					sp -= sp*5*kaina_lv/100;
				else if(sd->status.base_level>=70)
					sp -= sp*3*kaina_lv/100;
			}
			break;
		case MO_CHAINCOMBO:
		case MO_COMBOFINISH:
		case CH_TIGERFIST:
		case CH_CHAINCRUSH:
			// モンクの魂　連携スキルのSP消費減少
			if(sd->sc.data[SC_MONK].timer!=-1)
				sp -= sp*sd->sc.data[SC_MONK].val1/10;
			break;
		case NJ_ZENYNAGE:
			if(!(type&1)) {
				if(zeny>=2) {
					zeny /= 2;
					sd->zenynage_damage = zeny + atn_rand()%zeny;
					zeny = sd->zenynage_damage;
				} else if(cnd->lv > 0) {
					// お金消費無しのデフォルトダメージ
					sd->zenynage_damage = 500*cnd->lv + atn_rand()%(500*cnd->lv);
				}
			} else {
				zeny = sd->zenynage_damage;
			}
			break;
		case MG_NAPALMBEAT:
		case MG_SOULSTRIKE:
		case HW_NAPALMVULCAN:
		case WL_SOULEXPANSION:
		case WL_WHITEIMPRISON:
			// テレキネシスインテンス
			if(sd->sc.data[SC_TELEKINESIS_INTENSE].timer != -1)
				sp -= sp*sd->sc.data[SC_TELEKINESIS_INTENSE].val3/100;
			break;
		case KO_MUCHANAGE:
			if(!(type&1) && cnd->lv > 0) {
				sd->zenynage_damage = 5000*cnd->lv + atn_rand()%(5000*cnd->lv);
			}
			break;
	}
#ifndef PRE_RENEWAL
	// バードとダンサーの魂
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
		sp += sp * 50 / 100;	/* 消費SP増加 */
	// ウィザードの魂
	if(sd->sc.data[SC_WIZARD].timer != -1) {
		for(i=0; i<10; i++) {
			if(itemid[i] <= 0)
				continue;
			if(itemid[i] == 717)
				sp += sp * 50 / 100;	/* 消費SP増加 */
		}
	}
#endif

	if(sd->dsprate!=100)
		sp=sp*sd->dsprate/100;	/* 消費SP修正 */

	// マスカレード ： レイジーネス
	if(sd->sc.data[SC__LAZINESS].timer != -1)
		sp += sd->sc.data[SC__LAZINESS].val1 * 10;	/* 消費SP増加 */

	// マスカレード ： アンラッキー
	if(sd->sc.data[SC__UNLUCKY].timer != -1)
		zeny += 1000;			/* 消費zeny増加 */

	switch(cnd->id) {
	case SA_CASTCANCEL:
	case SO_SPELLFIST:
		if(ud->skilltimer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case BS_MAXIMIZE:		/* マキシマイズパワー */
	case NV_TRICKDEAD:		/* 死んだふり */
	case TF_HIDING:			/* ハイディング */
	case AS_CLOAKING:		/* クローキング */
	case CR_AUTOGUARD:		/* オートガード */
	case PA_GOSPEL:			/* ゴスペル */
	case ST_CHASEWALK:		/* チェイスウォーク */
	case NPC_INVISIBLE:		/* インビジブル */
	case TK_RUN:			/* タイリギ */
	case GS_GATLINGFEVER:		/* ガトリングフィーバー */
	case CR_SHRINK:			/* シュリンク */
	//case RA_CAMOUFLAGE:		/* カモフラージュ */
	case ML_AUTOGUARD:
	case KO_YAMIKUMO:		/* 闇雲 */
		{
			int sc_type = GetSkillStatusChangeTable(cnd->id);
			if(sc_type > 0 && sd->sc.data[sc_type].timer != -1)
				sp = 0;	// 解除する場合はSP消費しない
		}
		break;
	case AL_TELEPORT:
		{
			int alive;
			if(map[bl->m].flag.noteleport) {
				alive = 0;
			} else {
				alive = 1;
				map_foreachinarea(skill_landprotector,bl->m,bl->x,bl->y,bl->x,bl->y,BL_SKILL,AL_TELEPORT,&alive);
			}
			if(!alive) {
				clif_skill_teleportmessage(sd,0);
				return 0;
			}
		}
		break;
	case AL_WARP:
		if(map[bl->m].flag.noportal) {
			clif_skill_teleportmessage(sd,0);
			return 0;
		}
		break;
	case MO_CALLSPIRITS:		/* 気功 */
		{
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? cnd->lv: skill_get_max(cnd->id);
			if(sd->sc.data[SC_RAISINGDRAGON].timer != -1)
				max += sd->sc.data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num >= max) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case MO_BODYRELOCATION:		/* 残影 */
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
			spiritball = 0;
		break;
	case CH_SOULCOLLECT:		/* 練気功 */
		if(battle_config.soulcollect_max_fail) {
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? pc_checkskill(sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sd->sc.data[SC_RAISINGDRAGON].timer != -1)
				max += sd->sc.data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num >= max) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		if (sd->spiritball.num > 0 && sd->spiritball.num < spiritball) {
			spiritball = sd->spiritball.num;
			sd->spiritball.old = sd->spiritball.num;
		} else {
			sd->spiritball.old = cnd->lv;
		}
		break;
	case MO_CHAINCOMBO:		/* 連打掌 */
		if(sd->sc.data[SC_BLADESTOP].timer==-1){
			if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_TRIPLEATTACK)
				return 0;
		}
		break;
	case MO_COMBOFINISH:		/* 猛龍拳 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_CHAINCOMBO)
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_TIGERFIST:		/* 伏虎拳 */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_CHAINCRUSH))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_TIGERFIST))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case MO_EXTREMITYFIST:		/* 阿修羅覇鳳拳 */
		if((sd->sc.data[SC_COMBO].timer != -1 && (sd->sc.data[SC_COMBO].val1 == MO_COMBOFINISH || sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)) || sd->sc.data[SC_BLADESTOP].timer!=-1)
		{
			if(sd->sc.data[SC_COMBO].timer != -1 && sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)
				spiritball = 1;
			else
				spiritball--;	// =4でも良いが
			if(spiritball<0)
				spiritball=0;
		}
		break;
	case TK_STORMKICK:		/* フェオリチャギ */
	case TK_DOWNKICK:		/* ネリョチャギ */
	case TK_TURNKICK:		/* トルリョチャギ */
	case TK_COUNTER:		/* アプチャオルリギ */
		if(sd->sc.data[SC_TKCOMBO].timer == -1 ||
		   (sd->sc.data[SC_TKCOMBO].val4 != TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 != cnd->id) ||
		   (sd->sc.data[SC_TKCOMBO].val4 == TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 == cnd->id)	// ランカーは直前のスキルと同一ならコンボ終了
		) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			status_change_end(&sd->bl,SC_TKCOMBO,-1);
			return 0;
		}
		break;
	case BD_ADAPTATION:		/* アドリブ */
		{
			struct skill_unit_group *group=NULL;
			if(
				sd->sc.data[SC_DANCING].timer==-1 ||
				((group=map_id2sg(sd->sc.data[SC_DANCING].val2)) &&
				(skill_get_time(sd->sc.data[SC_DANCING].val1,group->skill_lv) -
				sd->sc.data[SC_DANCING].val3*1000) <= skill_get_time2(cnd->id,cnd->lv))
			){
				// ダンス中で使用後5秒以上のみ？
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case PR_BENEDICTIO:		/* 聖体降福 */
		{
			int range=1;
			int c=0;
			if(!(type&1)){
				map_foreachinarea(skill_check_condition_char_sub,bl->m,
					bl->x-range,bl->y-range,
					bl->x+range,bl->y+range,BL_PC,sd,&c,cnd);
				if(c<2){
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
			}else{
				map_foreachinarea(skill_check_condition_use_sub,bl->m,
					bl->x-range,bl->y-range,
					bl->x+range,bl->y+range,BL_PC,sd,&c);
			}
		}
		break;
	case WE_CALLPARTNER:		/* あなたに逢いたい */
		if(!sd->status.partner_id){
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case WE_CALLPARENT:		/* ママ、パパ、来て */
		if(!sd->status.parent_id[0] && !sd->status.parent_id[1]){
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case WE_CALLBABY:		/* 坊や、いらっしゃい */
		if(!sd->status.baby_id){
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case AM_CANNIBALIZE:		/* バイオプラント */
	case AM_SPHEREMINE:		/* スフィアーマイン */
		if(type&1){
			const int summons[5] = { 1589, 1579, 1575, 1555, 1590 };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount>0) {
				int c,n=0;
				do{
					c = map_foreachinarea(
						skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
						map[bl->m].ys, BL_MOB, bl->id,
						(cnd->id==AM_CANNIBALIZE)? summons[n]: 1142
					);
					// 今回召喚するmobとは別の種類のmobを召喚していないかもチェック
					if((cnd->id==AM_CANNIBALIZE && ((c > 0 && n != cnd->lv-1) || (n == cnd->lv-1 && c >= maxcount)))
						|| (cnd->id==AM_SPHEREMINE && c >= maxcount)){
						clif_skill_fail(sd,cnd->id,0,0,0);
						return 0;
					}
				}while(cnd->id != AM_SPHEREMINE && ++n < 5);
			}
		}
		break;
	case AM_CALLHOMUN:			/* コールホムンクルス */
		// 作成済みで安息時
		if(sd->hom.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id && !sd->hom.incubate)
			break;
		if(sd->hd) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(sd->hom.homun_id > 0) {	// 作成済みホムが居る時にエンブリオ持ってたら失敗
			for(i=0; i<MAX_INVENTORY; i++) {
				if(sd->status.inventory[i].nameid == 7142) {
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
			}
		}
		break;
	case AM_REST:			/* 安息 */
		if(!homun_isalive(sd) || status_get_hp(&sd->hd->bl) < sd->hd->max_hp * 80 / 100) {
			// ホムのHPがMHPの80%以上であること
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case AM_RESURRECTHOMUN:			/* リザレクションホムンクルス */
		if(sd->hd || sd->hom.hp > 0) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case WZ_FIREPILLAR:
		if(cnd->lv <= 5)	// no gems required at level 1-5
			item_nocost = 1;
		// fall through
	case PF_SPIDERWEB:		/* スパイダーウェブ */
	case MG_FIREWALL:		/* ファイアーウォール */
	case GN_THORNS_TRAP:	/* ソーントラップ */
	case GN_WALLOFTHORN:	/* ソーンウォール */
		/* 数制限 */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case PF_HPCONVERSION:		/* 生命力変換 */
		if(sd->status.sp >= sd->status.max_sp)
			return 0;
		break;
	case PA_PRESSURE:		/* プレッシャー */
		if(status_get_class(target) == MOBID_EMPERIUM) {	// エンペは使用不可
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case CR_DEVOTION:		/* ディボーション */
		if(target && target->type == BL_PC) {
			for(i = 0; i < cnd->lv && i < 5; i++) {
				if(sd->dev.val1[i] <= 0)
					break;
			}
			if(i >= cnd->lv || i >= 5) {
				// 定員オーバー
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;

	case BD_LULLABY:			/* 子守唄 */
	case BD_RICHMANKIM:			/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:		/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:		/* ニーベルングの指輪 */
	case BD_ROKISWEIL:			/* ロキの叫び */
	case BD_INTOABYSS:			/* 深淵の中に */
	case BD_SIEGFRIED:			/* 不死身のジークフリード */
	case BA_DISSONANCE:			/* 不協和音 */
	case BA_POEMBRAGI:			/* ブラギの詩 */
	case BA_WHISTLE:			/* 口笛 */
	case BA_ASSASSINCROSS:		/* 夕陽のアサシンクロス */
	case BA_APPLEIDUN:			/* イドゥンの林檎 */
	case DC_UGLYDANCE:			/* 自分勝手なダンス */
	case DC_HUMMING:			/* ハミング */
	case DC_DONTFORGETME:		/* 私を忘れないで… */
	case DC_FORTUNEKISS:		/* 幸運のキス */
	case DC_SERVICEFORYOU:		/* サービスフォーユー */
	case CG_MOONLIT:			/* 月明りの下で */
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		break;
	case CG_HERMODE:			/* ヘルモードの杖 */
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		if(battle_config.hermode_gvg_only && map[bl->m].flag.gvg==0){	// シーズ以外使えない
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		// WPチェック？
		if(battle_config.hermode_wp_check && !skill_hermode_wp_check(bl))
		{
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SG_SUN_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[0]){
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case SG_SUN_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[0] && (battle_config.allow_skill_without_day || is_day_of_sun()))
				break;
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SG_MOON_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[1]){
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case SG_MOON_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[1] && (battle_config.allow_skill_without_day || is_day_of_moon()))
				break;
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SG_STAR_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[2]){
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case SG_STAR_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[2] && (battle_config.allow_skill_without_day || is_day_of_star()))
				break;
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SG_HATE:
		if(status_get_class(target) == MOBID_EMPERIUM) {	// エンペは登録不可
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SG_FUSION:
		if(sd->sc.data[SC_FUSION].timer != -1) {	// 解除するときはsp消費なし
			sp = 0;
		}
		if(sd->sc.data[SC_STAR].timer == -1) {	// ケンセイの魂状態
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case PR_REDEMPTIO:
		if(battle_config.redemptio_penalty_type) {
			int exp = pc_nextbaseexp(sd);
			if(exp <= 0) {
				// オーラの場合は現在のレベルに必要な経験値を参照する
				sd->status.base_level--;
				exp = pc_nextbaseexp(sd);
				sd->status.base_level++;
				if(exp <= 0) {
					// それでもexpが未設定なら許可
					break;
				}
			}
			if(sd->status.base_exp < exp / 100 * battle_config.death_penalty_base / 100) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case GS_GLITTERING:		/* フリップザコイン */
		if(sd->coin.num >= 10) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case HT_POWER:			/* ビーストストレイフィング */
		if(sd->sc.data[SC_DOUBLE].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case GC_WEAPONBLOCKING:	/* ウェポンブロッキング */
		if(sd->sc.data[SC_WEAPONBLOCKING].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_COUNTERSLASH:		/* カウンタースラッシュ */
	case GC_WEAPONCRUSH:		/* ウェポンクラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCKING2].timer == -1) {
			clif_skill_fail(sd,cnd->id,0x1f,0,0);
			return 0;
		}
		break;
	case GC_VENOMPRESSURE:		/* ベナムプレッシャー */
	case GC_POISONSMOKE:		/* ポイズンスモーク */
		if(sd->sc.data[SC_POISONINGWEAPON].timer == -1) {
			clif_skill_fail(sd,cnd->id,0x20,0,0);
			return 0;
		}
		break;
	case GC_CLOAKINGEXCEED:	/* クローキングエクシード */
		if(sd->sc.data[SC_CLOAKINGEXCEED].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
		if(sd->sc.data[SC_HALLUCINATIONWALK].timer != -1 || sd->sc.data[SC_HALLUCINATIONWALK2].timer != -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case GC_CROSSRIPPERSLASHER:		/* クロスリッパースラッシャー */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,0x10,0,0);
			return 0;
		}
		break;
	case AB_ANCILLA:			/* アンシラ */
		{
			int idx = pc_search_inventory(sd,12333);
			if(idx >= 0 && sd->status.inventory[idx].amount >= 3 ) {	/* 作成前に所持限界数を超えている */
				clif_skill_fail(sd,cnd->id,0x0c,0,0);
				return 0;
			}
		}
		break;
	case WL_TETRAVORTEX:		/* テトラボルテックス */
		{
			int c = 0, i;
			for(i = 0; i < 5; i++) {
				if(sd->sc.data[SC_SUMMONBALL1 + i].timer != -1) {
					c++;
				}
			}
			if(c < 4) {
				clif_skill_fail(sd,cnd->id,0x14,0,0);
				return 0;
			}
		}
		break;
	case WL_SUMMONFB:		/* サモンファイアボール */
	case WL_SUMMONBL:		/* サモンボールライトニング */
	case WL_SUMMONWB:		/* サモンウォーターボール */
	case WL_SUMMONSTONE:	/* サモンストーン */
		{
			int i;
			for(i = 0; i < 5; i++) {
				if(sd->sc.data[SC_SUMMONBALL1 + i].timer == -1)
					break;
			}
			if(i >= 5) {	// 召喚数がいっぱい
				clif_skill_fail(sd,cnd->id,0x13,0,0);
				return 0;
			}
		}
		break;
	case NC_PILEBUNKER:			/* パイルバンカー */
	case NC_HOVERING:			/* ホバーリング */
		{
			int i, itemid;
			for(i = 0; i < 10; i++) {
				itemid = skill_db[skill_get_skilldb_id(cnd->id)].itemid[i];
				// 装備品を装備しているか判定
				if(itemdb_isequip3(itemid) && !pc_equippeditem(sd,itemid)) {
					clif_skill_fail(sd,cnd->id,0x48,0,itemid);
					return 0;
				}
			}
		}
		break;
	case NC_SILVERSNIPER:		/* FAW シルバースナイパー */
		if(type&1){
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, 2042
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
			}
		}
		break;
	case NC_MAGICDECOY:      /* FAW マジックデコイ */
		if(type&1){
			const int mob_id[4] = {
				2043, 2044, 2046, 2045
			};
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = 0;
				for(i = 0; i < 4; i++) {
					c += map_foreachinarea(
						skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
						map[bl->m].ys, BL_MOB, bl->id, mob_id[i]
					);
				}
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
			}
		}
		break;
	case SC_REPRODUCE:	/* リプロデュース */
		if(sd->sc.data[SC__REPRODUCE].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case SC_INVISIBILITY:	/* インビジビリティ */
		if(sd->sc.data[SC__INVISIBILITY].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case SC_DIMENSIONDOOR:	/* ディメンションドア */
		if(map[bl->m].flag.noteleport) {
			clif_skill_teleportmessage(sd,2);
			return 0;
		}
		break;
	case LG_FORCEOFVANGUARD:	/* フォースオブバンガード */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case LG_RAGEBURST:	/* レイジバーストアタック */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer == -1 || sd->sc.data[SC_FORCEOFVANGUARD].val4 < 1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case LG_PRESTIGE:	/* プレスティージ */
	case LG_BANDING:	/* バンディング */
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case LG_RAYOFGENESIS:	/* レイオブジェネシス */
		if(sd->sc.data[SC_INSPIRATION].timer == -1 && (sd->sc.data[SC_BANDING].timer == -1 || sd->sc.data[SC_BANDING].val2 < 2)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case LG_HESPERUSLIT:	/* ヘスペルスリット */
		if(sd->sc.data[SC_INSPIRATION].timer == -1 && (sd->sc.data[SC_BANDING].timer == -1 || sd->sc.data[SC_BANDING].val2 < 3)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case LG_INSPIRATION:	/* インスピレーション */
		if(sd->sc.data[SC_PRESTIGE].timer != -1 || sd->sc.data[SC_BANDING].timer != -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SR_FALLENEMPIRE:		/* 大纏崩捶 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SR_DRAGONCOMBO)
			return 0;
		break;
	case SR_TIGERCANNON:		/* 號砲 */
		if(sd->status.hp < sd->status.max_hp * (10 + cnd->lv * 2) / 100) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(sd->status.sp < sd->status.max_sp * (5 + cnd->lv) / 100) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SR_RAMPAGEBLASTER:		/* 爆気散弾 */
		if(sd->spiritball.num) {
			spiritball = sd->spiritball.num;
			sd->spiritball.old = sd->spiritball.num;
		} else {
			clif_skill_fail(sd,cnd->id,0x4a,0,0);
			return 0;
		}
		break;
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		if(sd->status.sp < sd->status.max_sp * 30 / 100) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case WM_GREAT_ECHO:					/* グレートエコー */
	case WM_SONG_OF_MANA:				/* マナの歌 */
	case WM_DANCE_WITH_WUG:				/* ダンスウィズウォーグ */
	case WM_SOUND_OF_DESTRUCTION:		/* サウンドオブディストラクション */
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
	case WM_LERADS_DEW:					/* レーラズの霧 */
	case WM_MELODYOFSINK:				/* メロディーオブシンク */
	case WM_BEYOND_OF_WARCRY:			/* ビヨンドオブウォークライ */
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		{
			int c=0;
			if(cnd->id == WM_SATURDAY_NIGHT_FEVER && !map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
			if(!(type&1)){
				map_foreachinarea(skill_check_condition_char_sub,bl->m,
					bl->x-15,bl->y-15,
					bl->x+15,bl->y+15,BL_PC,sd,&c,cnd);
				if(c<1){
					clif_skill_fail(sd,cnd->id,0,0,0);
					return 0;
				}
			}else{
				map_foreachinarea(skill_check_condition_use_sub,bl->m,
					bl->x-15,bl->y-15,
					bl->x+15,bl->y+15,BL_PC,sd,&c);
			}
		}
		break;
	case SO_POISON_BUSTER:	/* ポイズンバスター */
		if(target) {
			struct status_change *sc = status_get_sc(target);

			if(sc && sc->data[SC_POISON].timer == -1) {
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		if(!map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SO_SUMMON_AGNI:	/* サモンアグニ */
	case SO_SUMMON_AQUA:	/* サモンアクア */
	case SO_SUMMON_VENTUS:	/* サモンベントス */
	case SO_SUMMON_TERA:	/* サモンテラ */
		{
			int skill = pc_checkskill(sd,SO_EL_SYMPATHY);
			if(skill > 0) {
				sp -= sp * (5 + skill * 5) / 100;
			}
		}
		break;
	case SO_EL_CONTROL:	/* エレメンタルコントロール */
	case SO_EL_ACTION:	/* エレメンタルアクション */
	case SO_ELEMENTAL_SHIELD:	/* エレメンタルシールド */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SO_EL_CURE:	/* エレメンタルキュアー */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(sd->status.sp < sd->status.max_sp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,0x01,0,0);
			return 0;
		}
		if(sd->status.hp < sd->status.max_hp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,0x02,0,0);
			return 0;
		}
		break;
	case KO_KAHU_ENTEN:	/* 火符‐炎天 */
	case KO_HYOUHU_HUBUKI:	/* 氷符‐吹雪 */
	case KO_KAZEHU_SEIRAN:	/* 風符‐青嵐 */
	case KO_DOHU_KOUKAI:	/* 土符‐剛塊 */
		if(sd->elementball.num >= MAX_ELEMENTBALL) {
			if(sd->elementball.ele == skill_get_pl(cnd->id)) {
				clif_skill_fail(sd,cnd->id,0x13,0,0);
				return 0;
			}
		}
		break;
	case KO_KAIHOU:	/* 術式解放 */
	case KO_ZENKAI:	/* 術式全開 */
		if(sd->elementball.num < 1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case GD_BATTLEORDER:		/* 臨戦態勢 */
	case GD_REGENERATION:		/* 激励 */
	case GD_RESTORE:		/* 治療 */
	case GD_EMERGENCYCALL:		/* 緊急招集 */
		if(!battle_config.guild_skill_available) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(battle_config.allow_guild_skill_in_gvg_only && !map[bl->m].flag.gvg) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(battle_config.guild_skill_in_pvp_limit && map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(sd->sc.data[SC_BATTLEORDER_DELAY + cnd->id - GD_BATTLEORDER].timer != -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		if(cnd->id == GD_EMERGENCYCALL && battle_config.no_emergency_call) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	}

	if(!(type&2)) {
		int w;

		if(!sd->skill_item.flag) {		// アイテムスキル由来ならSPチェックは不要
			if(sp > 0 && sd->status.sp < sp) {		/* SPチェック */
				clif_skill_fail(sd,cnd->id,1,0,0);
				return 0;
			}
		}
		if(hp > 0 && sd->status.hp < hp) {			/* HPチェック */
			clif_skill_fail(sd,cnd->id,2,0,0);
			return 0;
		}
		if(zeny > 0 && sd->status.zeny < zeny) {
			sd->zenynage_damage = 0;
			clif_skill_fail(sd,cnd->id,5,0,0);
			return 0;
		}

		w = sd->status.weapon;
		if(w >= WT_MAX)
			w -= WT_DOUBLE_DD + WT_MAX;

		if(!(weapon & (1<<w))) {
			clif_skill_fail(sd,cnd->id,6,0,0);
			return 0;
		}
		if(spiritball > 0 && sd->spiritball.num < spiritball) {
			clif_skill_fail(sd,cnd->id,74,spiritball,0);		// 気球不足
			return 0;
		}
		if(coin > 0 && sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,0,0,0);		// コイン不足
			return 0;
		}
		if(arrow > 0) {						// 矢不足
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if( idx == -1 ||
			    !(sd->inventory_data[idx]->arrow_type & skill_get_arrow_type(cnd->id)) ||
			    sd->status.inventory[idx].amount < arrow )
			{
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
	}

	switch(state) {
	case SST_HIDING:
		if(!(sd->sc.option&OPTION_HIDE)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_CLOAKING:
		if(!pc_iscloaking(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_CHASEWALKING:
		if(!pc_ischasewalk(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_HIDDEN:
		if(!pc_ishiding(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_RIDING:
		if(!pc_isriding(sd) && !pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_FALCON:
		if(!pc_isfalcon(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_CART:
		if(!pc_iscarton(sd)) {
			clif_skill_fail(sd,cnd->id,0x39,0,0);
			return 0;
		}
		break;
	case SST_SHIELD:
		if(sd->status.shield <= 0) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_SIGHT:
		if(sd->sc.data[SC_SIGHT].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(sd->sc.data[SC_CARTBOOST].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_NEN:
		if(sd->sc.data[SC_NEN].timer == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_RECOV_WEIGHT_RATE:
		if(battle_config.natural_heal_weight_rate <= 100 && sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_WATER:
		if(!map[bl->m].flag.rain) {
			// 水場判定
			if(( !map_getcell(bl->m,bl->x,bl->y,CELL_CHKWATER) &&
			    sd->sc.data[SC_DELUGE].timer == -1 &&
			    sd->sc.data[SC_SUITON].timer == -1 ) ||
			    map_find_skill_unit_oncell(bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL))
			{
				clif_skill_fail(sd,cnd->id,0,0,0);
				return 0;
			}
		}
		break;
	case SST_DRAGON:
		if(!pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_WOLF:
		if(!pc_iswolf(sd) && !pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,0,0,0);
			return 0;
		}
		break;
	case SST_GEAR:
		if(!pc_isgear(sd)) {
			clif_skill_fail(sd,cnd->id,33,0,0);
			return 0;
		}
		break;
	}

	// 属性場用 出ている間はコスト無し
	switch(cnd->id)
	{
		case SA_VOLCANO:		/* ボルケーノ */
		case SA_DELUGE:			/* デリュージ */
		case SA_VIOLENTGALE:	/* バイオレントゲイル */
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
				item_nocost = 1;
			break;
	}

	// GVG PVP以外のマップでの特殊処理
	if(map[bl->m].flag.pvp==0 && map[bl->m].flag.gvg==0)
	{
		switch(cnd->id)
		{
			case AM_DEMONSTRATION:
				if(battle_config.demonstration_nocost)
					item_nocost = 1;
				break;
			case AM_ACIDTERROR:
				if(battle_config.acidterror_nocost)
					item_nocost = 1;
				break;
			case AM_CANNIBALIZE:
				if(battle_config.cannibalize_nocost)
					item_nocost = 1;
				break;
			case AM_SPHEREMINE:
				if(battle_config.spheremine_nocost)
					item_nocost = 1;
				break;
			case AM_CP_WEAPON:
			case AM_CP_SHIELD:
			case AM_CP_ARMOR:
			case AM_CP_HELM:
			case CR_FULLPROTECTION:
				if(battle_config.chemical_nocost)
					item_nocost = 1;
				break;
			case CR_ACIDDEMONSTRATION:
				if(battle_config.aciddemonstration_nocost)
					item_nocost = 1;
				break;
			case CR_SLIMPITCHER:
				if(battle_config.slimpitcher_nocost)
				{
					for(i=0;i<5;i++) {
						// 赤ポーション
						itemid[i] = 501;
						amount[i] = 1;
					}
					for(;i<9;i++) {
						// 黄ポーション
						itemid[i] = 503;
						amount[i] = 1;
					}
					// 白ポーション
					itemid[i] = 504;
					amount[i] = 1;
				}
			default:
				break;
		}
	}

	if(!item_nocost) {
		if(skill_item_consume(&sd->bl, cnd, type, itemid, amount) == 0)
			return 0;
	}

	if(type == 1) {
		if(!sd->skill_item.flag) {	// アイテムスキル由来ならSP消費しない
			if(sp > 0) {				// SP消費
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
			}
		}
		if(hp > 0) {					// HP消費
			sd->status.hp -= hp;
			clif_updatestatus(sd,SP_HP);
		}
		if(zeny > 0)					// Zeny消費
			pc_payzeny(sd,zeny);
		if(spiritball > 0)				// 気球消費
			pc_delspiritball(sd,spiritball,0);
		if(coin > 0)					// コイン消費
			pc_delcoin(sd,coin,0);
	}
	return 1;
}

// MOB用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_mob(struct mob_data *md, struct skill_condition *cnd, int type)
{
	nullpo_retr(0, md);
	nullpo_retr(0, cnd);

	if(md->sc.option&OPTION_CLOAKING && (cnd->id == TF_HIDING || cnd->id == KO_YAMIKUMO))
		return 0;

	if(md->sc.opt1 > OPT1_NORMAL && md->sc.opt1 != OPT1_BURNNING)
		return 0;

	switch(cnd->id)
	{
		case NPC_SUMMONMONSTER:
			if(md->master_id > 0 && md->state.special_mob_ai) {
				// 召還主がPCなら使用不可
				return 0;
			}
			break;
		case NPC_SUMMONSLAVE:
			if(md->master_id <= 0)
				break;
			if(md->state.special_mob_ai) {
				// 召還主がPCなら使用不可
				return 0;
			}
			if(battle_config.summonslave_generation > 0) {
				// 召還世代を計算する
				int count = battle_config.summonslave_generation;
				int id    = md->master_id;
				do {
					struct mob_data *mmd = map_id2md(id);
					if(mmd == NULL || mmd->bl.prev == NULL || unit_isdead(&mmd->bl) || mmd->m != md->m)
						break;
					id = mmd->master_id;
				} while(--count > 0);

				if(count <= 0)
					return 0;
			}
			break;
		case NPC_DEATHSUMMON:		/* デスサモン */
			if(md->master_id > 0 && md->state.special_mob_ai) {
				// 召還主がPCなら使用不可
				return 0;
			}
			if(md->state.skillstate != MSS_DEAD) {
				// 生きていたら使用不可
				return 0;
			}
			break;
	}

	return 1;
}

// PET用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_pet(struct pet_data *pd, struct skill_condition *cnd, int type)
{
	nullpo_retr(0, pd);
	nullpo_retr(0, cnd);

	// ペットが使えないほうがよいスキル
	switch(cnd->id)
	{
		case CG_MOONLIT:	/* 月明りの下で */
			// ペットに使われると通行の邪魔
			return 0;
	}
	return 1;
}

// HOM用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_hom(struct homun_data *hd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,hp_rate,sp_rate,zeny,state,skilldb_id;
	struct map_session_data* msd;
	struct block_list *bl;
	int itemid[10],amount[10];

	nullpo_retr(0, hd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, msd = hd->msd);
	nullpo_retr(0, bl = &hd->bl);

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<10; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}

	if(hp_rate > 0)
		hp += hd->status.hp * hp_rate / 100;
	else
		hp += hd->status.max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += hd->status.sp * sp_rate / 100;
	else
		sp += hd->status.max_sp * abs(sp_rate) / 100;

	switch(cnd->id) {
		case HLIF_HEAL:
		case HLIF_AVOID:
			if(hd->sc.data[SC_CHANGE].timer != -1)
				return 0;
			break;
	}

	if(!(type&2)) {
		if(hp > 0 && hd->status.hp < hp)	/* HPチェック */
			return 0;
		if(sp > 0 && hd->status.sp < sp)	/* SPチェック */
			return 0;
		if(zeny > 0 && msd->status.zeny < zeny)
			return 0;

		switch(cnd->id)
		{
			case HFLI_SBR44:	/* S.B.R.44 */
				if(hd->intimate < 200)
					return 0;
				break;
			case HVAN_EXPLOSION:	/* バイオエクスプロージョン */
				if(hd->intimate < battle_config.hvan_explosion_intimate)
					return 0;
				break;
		}
	}

	switch(state) {
	case SST_SIGHT:
		if(hd->sc.data[SC_SIGHT].timer == -1) {
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(hd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(hd->sc.data[SC_CARTBOOST].timer == -1) {
			return 0;
		}
		break;
	case SST_NEN:
		if(hd->sc.data[SC_NEN].timer == -1) {
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			return 0;
		}
		break;
	case SST_WATER:
		if(!map[bl->m].flag.rain) {
			// 水場判定
			if( !map_getcell(bl->m,bl->x,bl->y,CELL_CHKWATER) &&
				map_find_skill_unit_oncell(bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL) &&
			    hd->sc.data[SC_DELUGE].timer == -1 &&
			    hd->sc.data[SC_SUITON].timer == -1 )
				return 0;
		}
		break;
	}

	if(skill_item_consume(&hd->bl, cnd, type, itemid, amount) == 0)
		return 0;

	if(type == 1) {
		if(sp > 0) {				// SP消費
			hd->status.sp -= sp;
			clif_send_homstatus(msd,0);
		}
		if(hp > 0) {				// HP消費
			hd->status.hp -= hp;
			clif_send_homstatus(msd,0);
		}
		if(zeny > 0)				// Zeny消費
			pc_payzeny(msd,zeny);
	}
	return 1;
}

// MERC用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_merc(struct merc_data *mcd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,hp_rate,sp_rate,zeny,state,skilldb_id;
	struct map_session_data* msd;
	struct block_list *bl;
	int itemid[10],amount[10];

	nullpo_retr(0, mcd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, msd = mcd->msd);
	nullpo_retr(0, bl = &mcd->bl);

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<10; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}

	if(hp_rate > 0)
		hp += mcd->status.hp * hp_rate / 100;
	else
		hp += mcd->max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += mcd->status.sp * sp_rate / 100;
	else
		sp += mcd->max_sp * abs(sp_rate) / 100;

	if(!(type&2)) {
		if(hp > 0 && mcd->status.hp < hp)	/* HPチェック */
			return 0;
		if(sp > 0 && mcd->status.sp < sp)	/* SPチェック */
			return 0;
		if(zeny > 0 && msd->status.zeny < zeny)
			return 0;
	}

	switch(state) {
	case SST_SIGHT:
		if(mcd->sc.data[SC_SIGHT].timer == -1) {
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(mcd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(mcd->sc.data[SC_CARTBOOST].timer == -1) {
			return 0;
		}
		break;
	case SST_NEN:
		if(mcd->sc.data[SC_NEN].timer == -1) {
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			return 0;
		}
		break;
	case SST_WATER:
		if(!map[bl->m].flag.rain) {
			// 水場判定
			if( !map_getcell(bl->m,bl->x,bl->y,CELL_CHKWATER) &&
				map_find_skill_unit_oncell(bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL) &&
			    mcd->sc.data[SC_DELUGE].timer == -1 &&
			    mcd->sc.data[SC_SUITON].timer == -1 )
				return 0;
		}
		break;
	}

	if(skill_item_consume(&mcd->bl, cnd, type, itemid, amount) == 0)
		return 0;

	if(type == 1) {
		if(sp > 0) {				// SP消費
			mcd->status.sp -= sp;
			clif_mercupdatestatus(msd,SP_SP);
		}
		if(hp > 0) {				// HP消費
			mcd->status.hp -= hp;
			clif_mercupdatestatus(msd,SP_HP);
		}
		if(zeny > 0)				// Zeny消費
			pc_payzeny(msd,zeny);
	}
	return 1;
}

// ELEM用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_elem(struct elem_data *eld, struct skill_condition *cnd, int type)
{
	int i,hp,sp,hp_rate,sp_rate,zeny,state,skilldb_id;
	struct map_session_data* msd;
	struct block_list *bl;
	int itemid[10],amount[10];

	nullpo_retr(0, eld);
	nullpo_retr(0, cnd);
	nullpo_retr(0, msd = eld->msd);
	nullpo_retr(0, bl = &eld->bl);

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<10; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}

	if(hp_rate > 0)
		hp += eld->status.hp * hp_rate / 100;
	else
		hp += eld->max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += eld->status.sp * sp_rate / 100;
	else
		sp += eld->max_sp * abs(sp_rate) / 100;

	if(!(type&2)) {
		if(hp > 0 && eld->status.hp < hp)	/* HPチェック */
			return 0;
		if(sp > 0 && eld->status.sp < sp)	/* SPチェック */
			return 0;
		if(zeny > 0 && msd->status.zeny < zeny)
			return 0;
	}

	switch(state) {
	case SST_SIGHT:
		if(eld->sc.data[SC_SIGHT].timer == -1) {
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(eld->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(eld->sc.data[SC_CARTBOOST].timer == -1) {
			return 0;
		}
		break;
	case SST_NEN:
		if(eld->sc.data[SC_NEN].timer == -1) {
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			return 0;
		}
		break;
	case SST_WATER:
		if(!map[bl->m].flag.rain) {
			// 水場判定
			if( !map_getcell(bl->m,bl->x,bl->y,CELL_CHKWATER) &&
				map_find_skill_unit_oncell(bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL) &&
			    eld->sc.data[SC_DELUGE].timer == -1 &&
			    eld->sc.data[SC_SUITON].timer == -1 )
				return 0;
		}
		break;
	}

	if(skill_item_consume(&eld->bl, cnd, type, itemid, amount) == 0)
		return 0;

	if(type == 1) {
		if(sp > 0) {				// SP消費
			eld->status.sp -= sp;
			clif_elemupdatestatus(msd,SP_SP);
		}
		if(hp > 0) {				// HP消費
			eld->status.hp -= hp;
			clif_elemupdatestatus(msd,SP_HP);
		}
		if(zeny > 0)				// Zeny消費
			pc_payzeny(msd,zeny);
	}
	return 1;
}

/*==========================================
 * スキルによるアイテム消費
 *------------------------------------------
 */
static int skill_item_consume(struct block_list *bl, struct skill_condition *cnd, int type, int *itemid, int *amount)
{
	struct map_session_data *sd = NULL;
	struct status_change *sc;
	int i, idx[10];

	nullpo_retr(0, bl);
	nullpo_retr(0, cnd);

	sd = map_bl2msd(bl);
	if(sd == NULL)
		return 0;

	sc = status_get_sc(bl);

	for(i=0; i<10; i++) {
		int x = (cnd->lv > 10)? 9: cnd->lv - 1;

		idx[i] = -1;
		if(itemid[i] <= 0)
			continue;

		if(cnd->id != HW_GANBANTEIN && cnd->id != RG_GRAFFITI) {
			if(itemid[i] >= 715 && itemid[i] <= 717) {
				if(sd->special_state.no_gemstone || (sc && (sc->data[SC_WIZARD].timer != -1 || sc->data[SC_INTOABYSS].timer != -1))) {
					if(cnd->id == SA_ABRACADABRA && --amount[i] <= 0)
						continue;
					else if(cnd->id != SA_ABRACADABRA)
						continue;
				}
			}
		}
		if((cnd->id == AM_POTIONPITCHER || cnd->id == CR_SLIMPITCHER || cnd->id == CR_CULTIVATION || cnd->id == GN_FIRE_EXPANSION || cnd->id == KO_MAKIBISHI ||
			cnd->id == SO_SUMMON_AGNI || cnd->id == SO_SUMMON_AQUA || cnd->id == SO_SUMMON_VENTUS || cnd->id == SO_SUMMON_TERA ||
			cnd->id == SO_FIRE_INSIGNIA || cnd->id == SO_WATER_INSIGNIA || cnd->id == SO_WIND_INSIGNIA || cnd->id == SO_EARTH_INSIGNIA)
			&& i != x)
			continue;

		idx[i] = pc_search_inventory(sd,itemid[i]);
		if(idx[i] < 0 || sd->status.inventory[idx[i]].amount < amount[i]) {
			// トラップ研究を習得中で設置用トラップが足りなかった場合
			if(pc_checkskill(sd,RA_RESEARCHTRAP) && itemid[i] ==1065) {
				// 改良型設置用トラップに置き換えて再検索
				itemid[i] = 7940;
				amount[i] = 1;
				i--;
				continue;
			}
			if(itemdb_isequip3(itemid[i]))
				clif_skill_fail(sd,cnd->id,0x48,amount[i],itemid[i]);
			else if(itemid[i] == 716)
				clif_skill_fail(sd,cnd->id,0x07,amount[i],0);
			else if(itemid[i] == 717)
				clif_skill_fail(sd,cnd->id,0x08,amount[i],0);
			else if(itemid[i] == 523)
				clif_skill_fail(sd,cnd->id,0x0d,amount[i],0);
			else if(itemid[i] == 12333)
				clif_skill_fail(sd,cnd->id,0x0e,amount[i],0);
			else if(itemid[i] == 6121 || itemid[i] == 6122)
				clif_skill_fail(sd,cnd->id,0x18,amount[i],0);
			else
				clif_skill_fail(sd,cnd->id,0x47,amount[i],itemid[i]);
			return 0;
		}

		// ストーンカースLv6以上はジェム消費なしにしておく
		if(cnd->id == MG_STONECURSE && cnd->lv >= 6 && itemid[i] >= 715 && itemid[i] <= 717) {
			idx[i] = -1;
		}
		// ハンターのトラップスキルはユニット設置時にアイテム消費
		if(cnd->id >= HT_SKIDTRAP && (cnd->id <= HT_CLAYMORETRAP || cnd->id == HT_TALKIEBOX)) {
			idx[i] = -1;
		}

		if(sc) {
			// トロピック時、50%の確率で消費しない
			if(sc->data[SC_TROPIC].timer != -1 && (cnd->id == SA_FLAMELAUNCHER || cnd->id == SA_VOLCANO) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// クールエアー時、50%の確率で消費しない
			if(sc->data[SC_CHILLY_AIR].timer != -1 && (cnd->id == SA_FROSTWEAPON || cnd->id == SA_DELUGE) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// ワイルドストーム時、50%の確率で消費しない
			if(sc->data[SC_WILD_STORM].timer != -1 && (cnd->id == SA_LIGHTNINGLOADER || cnd->id == SA_VIOLENTGALE) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// アップヘイバル時、50%の確率で消費しない
			if(sc->data[SC_UPHEAVAL].timer != -1 && cnd->id == SA_SEISMICWEAPON && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
		}
	}

	if(type&1 && (cnd->id != AL_WARP || type&2)) {
		if(cnd->id != AM_POTIONPITCHER && cnd->id != CR_SLIMPITCHER && cnd->id != GN_FIRE_EXPANSION) {
			for(i=0; i<10; i++) {
				if(idx[i] >= 0)
					pc_delitem(sd,idx[i],amount[i],0,1);	// アイテム消費
			}
		}
	}

	return 1;
}

/*==========================================
 * 詠唱時間計算
 *------------------------------------------
 */
int skill_castfix(struct block_list *bl, int skillid, int casttime, int fixedtime)
{
	struct status_change *sc;
	struct map_session_data *sd = NULL;
	int i;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

	sc = status_get_sc(bl);

	if(sc) {
		// 魔法力増幅の効果終了
		if(sc->data[SC_MAGICPOWER].timer != -1) {
			if(sc->data[SC_MAGICPOWER].val2 > 0) {
				/* 最初に通った時にはアイコン消去だけ */
				sc->data[SC_MAGICPOWER].val2--;
				clif_status_change(bl, SI_MAGICPOWER, 0, 0, 0, 0, 0);
			} else {
				status_change_end(bl, SC_MAGICPOWER, -1);
			}
		}
		// デスバウンド待機中
		if(sc->data[SC_DEATHBOUND].timer != -1)
			fixedtime += 1000;
	}

	// カードによる詠唱時間増減効果
	if(casttime > 0 && sd && sd->skill_addcast.count > 0) {
		for(i=0; i<sd->skill_addcast.count; i++) {
			if(skillid == sd->skill_addcast.id[i])
				casttime += sd->skill_addcast.time[i];
		}
	}

	if(casttime > 0) {
		int reduce_time = 0;	// 削減時間

		/* サフラギウム */
		if(sc && sc->data[SC_SUFFRAGIUM].timer != -1) {
			reduce_time += sc->data[SC_SUFFRAGIUM].val1 * 15;
			status_change_end(bl, SC_SUFFRAGIUM, -1);
		}

		// ステータスの影響を計算する
		if(bl->type != BL_MOB) {
			int dex = status_get_dex(bl);
			int max = (int)battle_config.no_cast_dex;
#ifndef PRE_RENEWAL
			if(battle_config.no_cast_int > 0) {
				dex += status_get_int(bl) / 2;
				max += (int)battle_config.no_cast_int;
			}
#endif
			if(max > dex) {
#ifdef PRE_RENEWAL
				casttime = casttime * (max - dex) / max;
#else
				casttime = (int)(casttime * (1 - sqrt(dex/(float)max)));
#endif
				if(sd) {
					casttime = casttime * battle_config.cast_rate / 100;
					reduce_time += 100 - sd->castrate;
				}
			} else {
				casttime = 0;
			}
		}

		if(sc) {
			int type = -1;

			/* ブラギの詩 */
			if(sc->data[SC_POEMBRAGI].timer != -1)
				type = SC_POEMBRAGI;
			else if(sc->data[SC_POEMBRAGI_].timer != -1)
				type = SC_POEMBRAGI_;

			if(type >= 0) {
				reduce_time += (sc->data[type].val1*3 + sc->data[type].val2 + (sc->data[type].val3>>16));
			}

#ifndef PRE_RENEWAL
			/* ウィザードの魂 */
			if(sc->data[SC_WIZARD].timer != -1) {
				int itemid;
				for(i=0; i<10; i++) {
					itemid = skill_db[skill_get_skilldb_id(skillid)].itemid[i];
					if(itemid <= 0)
						continue;
					if(itemid == 717)
						reduce_time -= 50;
				}
			}
#endif

			/* スロウキャスト */
			if(sc->data[SC_SLOWCAST].timer != -1)
				reduce_time -= sc->data[SC_SLOWCAST].val1 * 20;

			/* マスカレード ： レイジーネス */
			if(sc->data[SC__LAZINESS].timer != -1)
				reduce_time -= sc->data[SC__LAZINESS].val1 * 10;

			/* 十六夜 */
			if(sc->data[SC_IZAYOI].timer != -1)
				reduce_time += 50;

			/* テレキネシスインテンス */
			if(sc->data[SC_TELEKINESIS_INTENSE].timer != -1 && skill_get_pl(skillid) == ELE_GHOST)
				reduce_time += 10;
		}

		// カードによる詠唱時間増減効果
		if(sd && sd->skill_addcastrate.count > 0) {
			for(i=0; i<sd->skill_addcastrate.count; i++) {
				if(skillid == sd->skill_addcastrate.id[i])
					casttime = casttime * (100 + sd->skill_addcastrate.rate[i])/100;
			}
		}

		casttime = casttime * (100 - reduce_time) / 100;
	}

	if(casttime < 0)
		casttime = 0;

	if(fixedtime > 0) {
		int reduce_time2 = 0;	// 固定詠唱削減時間

		/* ラディウス */
		if(sd && pc_checkskill(sd,WL_RADIUS)) {
			reduce_time2 += (5 + pc_checkskill(sd,WL_RADIUS) * 5);
		}

		if(sc) {
			/* サクラメント */
			if(sc->data[SC_SACRAMENT].timer != -1) {
				if(reduce_time2 < sc->data[SC_SACRAMENT].val2)
					reduce_time2 = sc->data[SC_SACRAMENT].val2;
			}

			/* ダンスウィズウォーグ */
			if(sc->data[SC_DANCE_WITH_WUG].timer != -1) {
				int val = 20 + sc->data[SC_DANCE_WITH_WUG].val4 * 10;
				if(reduce_time2 < val)
					reduce_time2 = val;
			}
		}

		if(sd) {
			reduce_time2 = ((reduce_time2 < sd->fixcastrate)? sd->fixcastrate: reduce_time2) + sd->fixcastrate_;

			// カードによる固定詠唱時間増減効果
			if(sd->skill_fixcastrate.count > 0) {
				for(i=0; i<sd->skill_fixcastrate.count; i++) {
					if(skillid == sd->skill_fixcastrate.id[i])
						fixedtime = fixedtime * (100 + sd->skill_fixcastrate.rate[i]) / 100;
				}
			}
		}

		if(sc) {
			/* スロウキャスト */
			if(sc->data[SC_SLOWCAST].timer != -1)
				reduce_time2 -= sc->data[SC_SLOWCAST].val1 * 20;

			/* フロストミスティ */
			if(sc->data[SC_FROSTMISTY].timer != -1)
				reduce_time2 -= 15;
		}

		fixedtime = fixedtime * (100 - reduce_time2) / 100;
	}

	// ニャンジャンプ習得時は緊急招集の詠唱時間2倍
	if(sd && skillid == GD_EMERGENCYCALL && pc_checkskill(sd,SU_LOPE) > 0) {
		casttime  <<= 1;
		fixedtime <<= 1;
	}
	if(sc) {
		/* ハウリングオブマンドラゴラ */
		if(sc->data[SC_MANDRAGORA].timer != -1) {
			fixedtime += sc->data[SC_MANDRAGORA].val3;		// 強制固定詠唱増加
		}
		/* 十六夜 */
		if(sc->data[SC_IZAYOI].timer != -1)
			fixedtime = 0;
	}
	if(fixedtime < 0)
		fixedtime = 0;

	return casttime + fixedtime;
}

/*==========================================
 * ディレイ計算
 *------------------------------------------
 */
int skill_delayfix(struct block_list *bl, int skillid, int skilllv)
{
	struct status_change *sc;
	int delay = skill_get_delay(skillid, skilllv);
	int reduce_time = 0;	// 削減時間

	nullpo_retr(0, bl);

	if(skillid == SA_MAGICROD)
		return 0;
	if(bl->type == BL_MOB) // MOBはスキルディレイ0
		return 0;

	sc = status_get_sc(bl);

	if(delay <= 0 && skill_get_cast(skillid, skilllv) <= 0) {
		delay = status_get_adelay(bl) / 2;
	} else {
		switch(skillid) {
			case AC_SHOWER:
			case AS_SONICBLOW:
			case SA_ABRACADABRA:
			case CG_ARROWVULCAN:
			case GS_GLITTERING:
			case GS_DUST:
			case GS_GROUNDDRIFT:
				break;
			default:
				if(bl->type == BL_PC) {
					struct map_session_data *sd = (struct map_session_data *)bl;
					if(battle_config.delay_dependon_dex) {	// dexの影響を計算する
						if(battle_config.no_delay_dex > status_get_dex(bl)) {
							delay = delay * (battle_config.no_delay_dex - status_get_dex(bl)) / battle_config.no_delay_dex;
						} else {
							delay = 0;
						}
					}
					delay = delay * battle_config.delay_rate / 100;
					if(sd && sd->skill_delay_rate)
						reduce_time -= sd->skill_delay_rate;
				}

				/* ブラギの詩 */
				if(sc) {
					if(sc->data[SC_POEMBRAGI].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI].val1 * rate + sc->data[SC_POEMBRAGI].val2 * 2
							+ (sc->data[SC_POEMBRAGI].val3 & 0xffff));
					} else if(sc->data[SC_POEMBRAGI_].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI_].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI_].val1 * rate + sc->data[SC_POEMBRAGI_].val2 * 2
							+ (sc->data[SC_POEMBRAGI_].val3 & 0xffff));
					}
				}
				break;
		}
	}

	if(sc) {
		switch(skillid) {
			case AS_SONICBLOW:
				if(sc->data[SC_ASSASIN].timer != -1 && !map[bl->m].flag.gvg) {
					reduce_time += 50;
				}
				break;
			case CR_SHIELDBOOMERANG:
				if(sc->data[SC_CRUSADER].timer != -1) {
					reduce_time += 50;
				}
				break;
		}
	}

	delay = delay * (100 - reduce_time)/100;

	if(skill_get_amotion_delay(skillid) && delay < status_get_amotion(bl))
		return status_get_amotion(bl);
	else
		return (delay > 0) ? delay : 0;
}

/*==========================================
 * クールダウン計算
 *------------------------------------------
 */
int skill_cooldownfix(struct block_list *bl, int skillid, int skilllv)
{
	struct map_session_data *sd = NULL;
	int cooldown = skill_get_cooldown(skillid, skilllv);

	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

	if(sd) {
		if(skillid == SU_TUNABELLY && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// 大トロ
			cooldown -= 3000;

		if(sd->skill_cooldown.count > 0) {
			int i;
			for(i=0; i<sd->skill_cooldown.count; i++) {
				if(skillid == sd->skill_cooldown.id[i])
					cooldown += sd->skill_cooldown.time[i];
			}
		}
	}

	return (cooldown > 0) ? cooldown : 0;
}

/*=========================================
 * ブランディッシュスピア 初期範囲決定
 *----------------------------------------
 */
static void skill_brandishspear_first(struct square *tc,int dir,int x,int y)
{
	nullpo_retv(tc);

	switch(dir) {
	case 0:
		tc->val1[0]=x-2;
		tc->val1[1]=x-1;
		tc->val1[2]=x;
		tc->val1[3]=x+1;
		tc->val1[4]=x+2;
		tc->val2[0]=
		tc->val2[1]=
		tc->val2[2]=
		tc->val2[3]=
		tc->val2[4]=y-1;
		break;
	case 1:
		tc->val1[0]=x-1;
		tc->val1[1]=x;
		tc->val1[2]=x+1;
		tc->val1[3]=x+2;
		tc->val1[4]=x+3;
		tc->val2[0]=y-4;
		tc->val2[1]=y-3;
		tc->val2[2]=y-1;
		tc->val2[3]=y;
		tc->val2[4]=y+1;
		break;
	case 2:
		tc->val1[0]=
		tc->val1[1]=
		tc->val1[2]=
		tc->val1[3]=
		tc->val1[4]=x+1;
		tc->val2[0]=y+2;
		tc->val2[1]=y+1;
		tc->val2[2]=y;
		tc->val2[3]=y-1;
		tc->val2[4]=y-2;
		break;
	case 3:
		tc->val1[0]=x+3;
		tc->val1[1]=x+2;
		tc->val1[2]=x+1;
		tc->val1[3]=x;
		tc->val1[4]=x-1;
		tc->val2[0]=y-1;
		tc->val2[1]=y;
		tc->val2[2]=y+1;
		tc->val2[3]=y+2;
		tc->val2[4]=y+3;
		break;
	case 4:
		tc->val1[0]=x-2;
		tc->val1[1]=x-1;
		tc->val1[2]=x;
		tc->val1[3]=x+1;
		tc->val1[4]=x+2;
		tc->val2[0]=
		tc->val2[1]=
		tc->val2[2]=
		tc->val2[3]=
		tc->val2[4]=y+1;
		break;
	case 5:
		tc->val1[0]=x+1;
		tc->val1[1]=x;
		tc->val1[2]=x-1;
		tc->val1[3]=x-2;
		tc->val1[4]=x-3;
		tc->val2[0]=y+3;
		tc->val2[1]=y+2;
		tc->val2[2]=y+1;
		tc->val2[3]=y;
		tc->val2[4]=y-1;
		break;
	case 6:
		tc->val1[0]=
		tc->val1[1]=
		tc->val1[2]=
		tc->val1[3]=
		tc->val1[4]=x-1;
		tc->val2[0]=y+2;
		tc->val2[1]=y+1;
		tc->val2[2]=y;
		tc->val2[3]=y-1;
		tc->val2[4]=y-2;
		break;
	case 7:
		tc->val1[0]=x-3;
		tc->val1[1]=x-2;
		tc->val1[2]=x-1;
		tc->val1[3]=x;
		tc->val1[4]=x+1;
		tc->val2[1]=y;
		tc->val2[0]=y+1;
		tc->val2[2]=y-1;
		tc->val2[3]=y-2;
		tc->val2[4]=y-3;
		break;
	}
}

/*=========================================
 * ブランディッシュスピア 方向判定 範囲拡張
 *-----------------------------------------
 */
static void skill_brandishspear_dir(struct square *tc,int dir,int are)
{
	int c;

	nullpo_retv(tc);

	for(c=0;c<5;c++) {
		switch(dir) {
		case 0:
			tc->val2[c]+=are;
			break;
		case 1:
			tc->val1[c]-=are; tc->val2[c]+=are;
			break;
		case 2:
			tc->val1[c]-=are;
			break;
		case 3:
			tc->val1[c]-=are; tc->val2[c]-=are;
			break;
		case 4:
			tc->val2[c]-=are;
			break;
		case 5:
			tc->val1[c]+=are; tc->val2[c]-=are;
			break;
		case 6:
			tc->val1[c]+=are;
			break;
		case 7:
			tc->val1[c]+=are; tc->val2[c]+=are;
			break;
		}
	}
}

/*----------------------------------------------------------------------------
 * 個別スキルの関数
 */

/*==========================================
 * ディボーション有効の総確認
 *------------------------------------------
 */
void skill_devotion(struct map_session_data *msd)
{
	int n;

	nullpo_retv(msd);

	for(n=0; n<5; n++) {
		if(msd->dev.val1[n]) {
			struct map_session_data *sd = map_id2sd(msd->dev.val1[n]);
			// 相手が見つからない or 相手をディボしてるのが自分じゃない or 距離が離れてる
			if( sd == NULL || msd->bl.id != sd->sc.data[SC_DEVOTION].val1 || skill_devotion3(msd,msd->dev.val1[n]) ) {
				msd->dev.val1[n] = 0;
				msd->dev.val2[n] = 0;
				if(sd && sd->sc.data[SC_DEVOTION].timer != -1 && sd->sc.data[SC_DEVOTION].val1)
					status_change_end(&sd->bl, SC_DEVOTION, -1);
				clif_devotion(msd);
			}
		}
	}
}

/*==========================================
 * 被ディボーションが歩いた時の距離チェック
 *------------------------------------------
 */
void skill_devotion2(struct block_list *bl,int crusader)
{
	struct map_session_data *sd;

	nullpo_retv(bl);

	if((sd = map_id2sd(crusader)) != NULL)
		skill_devotion3(sd,bl->id);
}

/*==========================================
 * クルセが歩いた時の距離チェック
 *------------------------------------------
 */
int skill_devotion3(struct map_session_data *msd,int target_id)
{
	struct map_session_data *sd;

	nullpo_retr(1, msd);

	if((sd = map_id2sd(target_id)) == NULL)
		return 1;

	if(unit_distance(&msd->bl, &sd->bl) > pc_checkskill(msd,CR_DEVOTION) + 6) {	// 許容範囲を超えてた
		int n;
		for(n=0; n<5; n++) {
			if(msd->dev.val1[n] == sd->bl.id) {
				if(msd->dev.val2[n]) {
					msd->dev.val2[n] = 0;	// 離れた時は、糸を切るだけ
					clif_devotion(msd);
				}
				break;
			}
		}
		return 1;
	}
	return 0;
}

/*==========================================
 * マリオネット主が歩いた時の距離チェック
 *------------------------------------------
 */
int skill_marionette(struct map_session_data *sd,int target_id)
{
	struct map_session_data *tsd;

	nullpo_retr(1, sd);

	if((tsd = map_id2sd(target_id)) == NULL) {
		if(sd->sc.data[SC_MARIONETTE].timer != -1)
			status_change_end(&sd->bl,SC_MARIONETTE,-1);
		return 1;
	}

	if(unit_distance(&sd->bl, &tsd->bl) > 7) {	// 許容範囲を超えてた
		status_change_end(&sd->bl,SC_MARIONETTE,-1);
		return 1;
	}

	return 0;
}

/*==========================================
 * 被マリオネットが歩いた時の距離チェック
 *------------------------------------------
 */
void skill_marionette2(struct map_session_data *dstsd,int src_id)
{
	struct map_session_data *sd;

	nullpo_retv(dstsd);

	if( (sd = map_id2sd(src_id)) != NULL )
		skill_marionette(sd,dstsd->bl.id);
	else
		status_change_end(&dstsd->bl,SC_MARIONETTE2,-1);
}

/*==========================================
 * シャドウフォーム主が歩いた時の距離チェック
 *------------------------------------------
 */
int skill_shadowform(struct map_session_data *sd,int target_id)
{
	struct map_session_data *tsd;

	nullpo_retr(1, sd);

	if((tsd = map_id2sd(target_id)) == NULL) {
		if(sd->sc.data[SC__SHADOWFORM].timer != -1)
			status_change_end(&sd->bl,SC__SHADOWFORM,-1);
		return 1;
	}

	if(unit_distance(&sd->bl, &tsd->bl) > 14) {	// 許容範囲を超えてた
		status_change_end(&sd->bl,SC__SHADOWFORM,-1);
		return 1;
	}

	return 0;
}

/*==========================================
 * 被シャドウフォームが歩いた時の距離チェック
 *------------------------------------------
 */
void skill_shadowform2(struct map_session_data *dstsd)
{
	struct map_session_data *sd;

	nullpo_retv(dstsd);

	if( (sd = map_id2sd(dstsd->shadowform_id)) != NULL )
		skill_shadowform(sd,dstsd->bl.id);
	else
		dstsd->shadowform_id = 0;

	return;
}

/*==========================================
 * オートスペル
 *------------------------------------------
 */
void skill_autospell(struct map_session_data *sd, int skillid)
{
	int skilllv, lv;
	int maxlv = 1;

	nullpo_retv(sd);

	skilllv = pc_checkskill(sd,SA_AUTOSPELL);

	switch(skillid) {
		case MG_NAPALMBEAT:
			maxlv = 3;
			break;
		case MG_COLDBOLT:
		case MG_FIREBOLT:
		case MG_LIGHTNINGBOLT:
			if(skilllv == 2)
				maxlv = 1;
			else if(skilllv == 3)
				maxlv = 2;
			else if(skilllv >= 4)
				maxlv = 3;
			break;
		case MG_SOULSTRIKE:
			if(skilllv == 5)
				maxlv = 1;
			else if(skilllv == 6)
				maxlv = 2;
			else if(skilllv >= 7)
				maxlv = 3;
			break;
		case MG_FIREBALL:
			if(skilllv == 8)
				maxlv = 1;
			else if(skilllv >= 9)
				maxlv = 2;
			break;
		case MG_FROSTDIVER:
			maxlv = 1;
			break;
		default:
			return;
	}

	if(maxlv > (lv = pc_checkskill(sd,skillid)))
		maxlv = lv;

	// if player doesn't have the skill (hacker?)
	if(lv == 0)
		return;

	status_change_start(&sd->bl,SC_AUTOSPELL,skilllv,skillid,maxlv,0,	// val1:スキルID val2:使用最大Lv
		skill_get_time(SA_AUTOSPELL,skilllv),0);// にしてみたけどbscriptが書き易い・・・？

	return;
}

/*==========================================
 * ギャングスターパラダイスおよびテコン休息
 * 判定処理判定処理
 *------------------------------------------
 */
static int skill_sit_count(struct block_list *bl,va_list ap)
{
	int flag;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	flag = va_arg(ap,int);

	if(!pc_issit(sd))
		return 0;

	if(flag&1 && pc_checkskill(sd,RG_GANGSTER) > 0)
		return 1;
	else if(flag&2 && sd->s_class.job >= PC_JOB_TK && sd->s_class.job <= PC_JOB_SL)
		return 1;

	return 0;
}

static int skill_sit_in(struct block_list *bl,va_list ap)
{
	int flag;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	flag = va_arg(ap,int);

	if(!pc_issit(sd))
		return 0;

	if(flag&1 && pc_checkskill(sd,RG_GANGSTER) > 0)
		sd->state.gangsterparadise = 1;
	else if(flag&2 && sd->s_class.job >= PC_JOB_TK && sd->s_class.job <= PC_JOB_SL)
		sd->state.taekwonrest = 1;

	return 0;
}

static int skill_sit_out(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	int flag;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	flag = va_arg(ap,int);

	if((flag&1 && sd->state.gangsterparadise) || (flag&2 && sd->state.taekwonrest)) {
		int c = map_foreachinarea(skill_sit_count,bl->m,
			bl->x-1,bl->y-1,
			bl->x+1,bl->y+1,BL_PC,flag);
		if(c < 2) {
			if(flag&1)
				sd->state.gangsterparadise = 0;
			if(flag&2)
				sd->state.taekwonrest = 0;
		}
	}
	return 0;
}

int skill_sit(struct map_session_data *sd, int type)
{
	int flag = 0;

	nullpo_retr(0, sd);

	if(pc_checkskill(sd,RG_GANGSTER) > 0)
		flag |= 1;
	if(pc_checkskill(sd,TK_HPTIME) > 0 || pc_checkskill(sd,TK_SPTIME) > 0)
		flag |= 2;

	if(!flag)
		return 0;

	if(type) {
		// 座った時の処理
		int c = map_foreachinarea(skill_sit_count,sd->bl.m,
			sd->bl.x-1,sd->bl.y-1,
			sd->bl.x+1,sd->bl.y+1,BL_PC,flag);
		if(c > 1) {
			// 成功したら効果付与
			map_foreachinarea(skill_sit_in,sd->bl.m,
				sd->bl.x-1,sd->bl.y-1,
				sd->bl.x+1,sd->bl.y+1,BL_PC,flag);
		}
	} else {
		// 立ち上がったときの処理
		map_foreachinarea(skill_sit_out,sd->bl.m,
			sd->bl.x-1,sd->bl.y-1,
			sd->bl.x+1,sd->bl.y+1,BL_PC,flag);
		if(flag&1)
			sd->state.gangsterparadise = 0;
		if(flag&2)
			sd->state.taekwonrest = 0;
	}

	return 0;
}

/*==========================================
 * 寒いジョーク・スクリーム判定処理(foreachinarea)
 *------------------------------------------
 */
static int skill_frostjoke_scream(struct block_list *bl,va_list ap)
{
	struct block_list *src;
	int skillnum,skilllv;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, src=va_arg(ap,struct block_list*));

	skillnum = va_arg(ap,int);
	skilllv  = va_arg(ap,int);
	tick     = va_arg(ap,unsigned int);

	if(src == bl)	// 自分には効かない
		return 0;

	skill_additional_effect(src,bl,skillnum,skilllv,BF_MISC,tick);

	return 0;
}

/*==========================================
 * 転生スキルか？
 *------------------------------------------
 */
static int skill_upperskill(int skillid)
{
	if(LK_AURABLADE <= skillid && skillid <= ASC_CDP)
		return 1;
	if(ST_PRESERVE <= skillid && skillid <= CR_CULTIVATION)
		return 1;
	return 0;
}

/*==========================================
 * 敵のスキルか？
 *------------------------------------------
 */
static int skill_mobskill(int skillid)
{
	if(NPC_PIERCINGATT <= skillid && skillid <= NPC_SUMMONMONSTER)
		return 1;

	if(NPC_DARKCROSS <= skillid && skillid <= NPC_RUN)
		return 1;

	if(NPC_EARTHQUAKE <= skillid && skillid <= NPC_ALLHEAL)
		return 1;

	if(NPC_WIDEHEALTHFEAR <= skillid && skillid <= NPC_WIDECRITICALWOUND)
		return 1;

	if(skillid == NPC_SELFDESTRUCTION2)
		return 1;

	return 0;
}

/*==========================================
 * アブラカダブラの使用スキル決定(決定スキルがダメなら0を返す)
 *------------------------------------------
 */
static int skill_abra_dataset(struct map_session_data *sd, int skilllv)
{
	int skill = atn_rand()%MAX_SKILL_ABRA_DB;

	nullpo_retr(0, sd);

	// セージの転生スキル使用を許可しない
	if( battle_config.extended_abracadabra == 0 &&
	    sd->s_class.upper == PC_UPPER_NORMAL &&
	    skill_upperskill(skill_abra_db[skill].nameid) )
		return 0;

	// dbに基づくレベル・確率判定
	if(skill_abra_db[skill].req_lv > skilllv || atn_rand()%10000 >= skill_abra_db[skill].per)
		return 0;
	// NPC・結婚・養子・アイテムスキルはダメ
	if( skill_mobskill( skill_abra_db[skill].nameid ) ||
	   (skill_abra_db[skill].nameid >= WE_BABY && skill_abra_db[skill].nameid <= WE_CALLBABY))
		return 0;

	// 演奏スキルはダメ
	if (skill_get_unit_flag(skill_abra_db[skill].nameid, skilllv)&UF_DANCE)
		return 0;

	return skill_abra_db[skill].nameid;
}

/*==========================================
 * バジリカのセルを設定する
 *------------------------------------------
 */
static void skill_basilica_cell(struct skill_unit *unit,int skilllv,int flag)
{
	int i,x,y;
	int range, size;

	nullpo_retv(unit);

	range = skill_get_unit_range(HP_BASILICA, skilllv);
	size  = range*2+1;

	for (i=0;i<size*size;i++) {
		x = unit->bl.x+(i%size-range);
		y = unit->bl.y+(i/size-range);
		map_setcell(unit->bl.m,x,y,flag);
	}
}

/*==========================================
 * バジリカの発動を止める
 *------------------------------------------
 */
void skill_basilica_cancel(struct block_list *bl)
{
	struct unit_data *ud = NULL;
	struct linkdb_node *node, *node2;
	struct skill_unit_group   *group;

	nullpo_retv(bl);
	nullpo_retv(ud = unit_bl2ud(bl));

	node = ud->skillunit;
	while( node ) {
		node2 = node->next;
		group = (struct skill_unit_group *)node->data;
		if(group && group->skill_id == HP_BASILICA)
			skill_delunitgroup(group);
		node = node2;
	}
}

/*==========================================
 *
 *------------------------------------------
 */
static int skill_clear_element_field(struct block_list *bl)
{
	struct unit_data *ud = NULL;
	struct linkdb_node *node, *node2;
	struct skill_unit_group   *group;

	nullpo_retr(0, bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	node = ud->skillunit;
	while( node ) {
		node2 = node->next;
		group = (struct skill_unit_group *)node->data;
		if(group) {
			switch(group->skill_id) {
				case SA_DELUGE:
				case SA_VOLCANO:
				case SA_VIOLENTGALE:
				case SA_LANDPROTECTOR:
				case NJ_SUITON:
				case NJ_KAENSIN:
				case KO_ZENKAI:
					skill_delunitgroup(group);
					break;
			}
		}
		node = node2;
	}
	return 0;
}

/*==========================================
 * ランドプロテクターチェック(foreachinarea)
 *------------------------------------------
 */
static int skill_landprotector(struct block_list *bl, va_list ap )
{
	int skillid;
	int *alive;
	struct skill_unit *unit;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, unit->group);

	skillid = va_arg(ap,int);
	alive   = va_arg(ap,int *);

	if(skillid == SA_LANDPROTECTOR) {
		if(alive && unit->group->skill_id == SA_LANDPROTECTOR)
			(*alive)=0;
		if(alive && unit->group->skill_id == WZ_ICEWALL)	// アイスウォールがあるセルにはランドプロテクターが出ない
			(*alive)=0;
		switch(unit->group->skill_id) {
		case WZ_ICEWALL:	// アイスウォール
		case HT_SKIDTRAP:	// スキッドトラップ
		case HT_LANDMINE:	// ランドマイン
		case HT_ANKLESNARE:	// アンクルスネア
		case HT_SHOCKWAVE:	// ショックウェーブトラップ
		case HT_SANDMAN:	// サンドマン
		case HT_FLASHER:	// フラッシャー
		case HT_FREEZINGTRAP:	// フリージングトラップ
		case HT_BLASTMINE:	// ブラストマイン
		case HT_CLAYMORETRAP:	// クレイモアトラップ
		case MA_SKIDTRAP:	// スキッドトラップ
		case MA_LANDMINE:	// ランドマイン
		case MA_SANDMAN:	// サンドマン
		case MA_FREEZINGTRAP:	// フリージングトラップ
		case BA_DISSONANCE:	// 不協和音
		case BA_WHISTLE:	// 口笛
		case BA_ASSASSINCROSS:	// 夕陽のアサシンクロス
		case BA_POEMBRAGI:	// ブラギの詩
		case BA_APPLEIDUN:	// イドゥンの林檎
		case DC_UGLYDANCE:	// 自分勝手なダンス
		case DC_HUMMING:	// ハミング
		case DC_DONTFORGETME:	// 私を忘れないで…
		case DC_FORTUNEKISS:	// 幸運のキス
		case DC_SERVICEFORYOU:	// サービスフォーユー
		case CG_HERMODE:	// ヘルモードの杖
		case NPC_EVILLAND:	// イービルランド
		case NPC_DISSONANCE:
		case NPC_UGLYDANCE:
			break;
		default:
			skill_delunit(unit);
		}			
	} else if(skillid == PF_FOGWALL) {
		if(alive && (unit->group->skill_id == SA_LANDPROTECTOR ||
			unit->group->skill_id == SA_VIOLENTGALE || unit->group->skill_id == SA_VOLCANO))
			(*alive)=0;
	} else {
		if(alive && unit->group->skill_id == SA_LANDPROTECTOR)
			(*alive)=0;
		if(alive && unit->group->skill_id == WZ_ICEWALL) {	// アイスウォールがあるセルはオブジェクトスキルが出ない
			if(skillid != AL_TELEPORT)
				(*alive)=0;
		}
	}
	return 0;
}

/*==========================================
 * イドゥンの林檎の回復処理(foreachinarea)
 *------------------------------------------
 */
static int skill_idun_heal(struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	struct block_list *src;
	int heal;
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = va_arg(ap,struct skill_unit *));
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, sg = unit->group);

	if(bl->id == sg->src_id)
		return 0;

	if(!(bl->type & (BL_PC | BL_MOB)))
		return 0;

	sc = status_get_sc(bl);

	heal = 30+sg->skill_lv*5+((sg->val1)>>16)*5+((sg->val2)&0xfff)/2;
	heal = skill_fix_heal(src, bl, sg->skill_id, heal);

	if(sc && sc->data[SC_AKAITSUKI].timer != -1) {
		unit_fixdamage(src,bl,gettick(),0,status_get_dmotion(bl),heal,0,0,0,0);
	} else {
		clif_skill_nodamage(&unit->bl,bl,AL_HEAL,heal,1);
		battle_heal(NULL,bl,heal,0,0);
	}

	return 0;
}

/*==========================================
 * 運命のタロットカード
 *------------------------------------------
 */
static int skill_tarot_card_of_fate(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int wheel)
{
	struct map_session_data* tsd=NULL;
	struct mob_data* tmd=NULL;
	int card_num,rate;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	if(!(target->type & (BL_PC | BL_MOB)))
		return 0;
	if(status_get_class(target) == MOBID_EMPERIUM)
		return 0;

	// 運命の輪だと100%成功
	if(wheel == 0 && atn_rand()%100 >= skilllv*8)
		return 0;

	tsd = BL_DOWNCAST( BL_PC,  target );
	tmd = BL_DOWNCAST( BL_MOB, target );

	rate = atn_rand()%10000;

	if(rate < 1000)      card_num =  0;	// 10%
	else if(rate < 2000) card_num =  1;	// 10%
	else if(rate < 3000) card_num =  2;	// 10%
	else if(rate < 3700) card_num =  3;	//  7%
	else if(rate < 4700) card_num =  4;	// 10%
	else if(rate < 6200) card_num =  5;	// 15%
	else if(rate < 6300) card_num =  6;	//  1%
	else if(rate < 6900) card_num =  7;	//  6%
	else if(rate < 7400) card_num =  8;	//  5%
	else if(rate < 8200) card_num =  9;	//  8%
	else if(rate < 8300) card_num = 10;	//  1%
	else if(rate < 8500) card_num = 11;	//  2%
	else if(rate < 9000) card_num = 12;	//  5%
	else                 card_num = 13;	// 10%

	if(wheel == 0)	// 運命の輪だとエフェクトなし？
	{
		switch(battle_config.tarotcard_display_position)
		{
			case 1:
				clif_misceffect2(src,523+card_num);
				break;
			case 2:
				clif_misceffect2(target,523+card_num);
				break;
			case 3:
				clif_misceffect2(src,523+card_num);
				clif_misceffect2(target,523+card_num);
				break;
			default:
				break;
		}
	}

	switch(card_num)
	{
		case 0:
			/* 愚者(The Fool) - SPが0になる */
			if(tsd) {
				tsd->status.sp = 0;
				clif_updatestatus(tsd,SP_SP);
			}
			break;
		case 1:
			/* 魔法師(The Magician) - 30秒間Matkが半分に落ちる */
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
				status_change_start(target,SC_THE_MAGICIAN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		case 2:
			/* 女教皇(The High Priestess) - すべての補助魔法が消える */
			status_change_release(target,0x40);
			break;
		case 3:
			/* 戦車(The Chariot) - 防御力無視の1000ダメージ 防具がランダムに一つ破壊される */
			if(tsd){
				switch(atn_rand()%4) {
					case 0: pc_break_equip(tsd,LOC_RARM); break;
					case 1: pc_break_equip(tsd,LOC_BODY);  break;
					case 2: pc_break_equip(tsd,LOC_LARM); break;
					case 3: pc_break_equip(tsd,LOC_HEAD2);   break;
				}
			}
			unit_fixdamage(src,target,0, 0, 0,1000,1, 4, 0, 0);
			break;
		case 4:
			/* 力(Strength) - 30秒間ATKが半分に落ちる */
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
				status_change_start(target,SC_STRENGTH,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		case 5:
			/* 恋人(The Lovers) - どこかにテレポートさせる- HPが2000回復される */
			unit_heal(target, 2000, 0);
			// テレポート不可の場合は回復のみ
			if(tsd) {
				if(!map[tsd->bl.m].flag.noteleport)
					pc_randomwarp(tsd,0);
			} else if(tmd) {
				if(!map[tmd->bl.m].flag.monster_noteleport)
					mob_warp(tmd,tmd->bl.m,-1,-1,0);
			}
			break;
		case 6:
			/* 運命の輪(Wheel of Fortune) - ランダムに他のタロットカード二枚の効果を同時に与える */
			if(wheel > 0 && wheel < 50) {	// もう1度実行（50回で打ち切り）
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,wheel+1);
			} else {			// ２つ実行
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,1);
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,1);
			}
			break;
		case 7:
			/* 吊られた男(The Hanged Man) - 睡眠、凍結、石化の中から一つが無条件かかる */
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
			{
				switch(atn_rand()%3)
				{
					case 0:	// 睡眠
						if(atn_rand() % 10000 < status_change_rate(target,SC_SLEEP,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_SLEEP,7,0,0,0,skill_get_time2(NPC_SLEEPATTACK,7),0,tick+status_get_amotion(src));
						break;
					case 1:	// 凍結
						if(atn_rand() % 10000 < status_change_rate(target,SC_FREEZE,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_FREEZE,7,0,0,0,skill_get_time2(MG_FROSTDIVER,7),0,tick+status_get_amotion(src));
						break;
					case 2:	// 石化
						if(atn_rand() % 10000 < status_change_rate(target,SC_STONE,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_STONE,7,0,0,0,skill_get_time2(MG_STONECURSE,7),0,tick+status_get_amotion(src));
						break;
				}
			}
			break;
		case 8:
			/* 死神(Death) - 呪い + コーマ + 毒にかかる */
			if(atn_rand() % 10000 < status_change_rate(target,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(target,SC_POISON,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_POISON,7,0,0,0,skill_get_time2(TF_POISON,7),0,tick+status_get_amotion(src));
			// コーマ
			if(tsd) {
				tsd->status.hp = 1;
				clif_updatestatus(tsd,SP_HP);
			} else if(tmd && !(status_get_mode(&tmd->bl)&MD_BOSS)) {	// ボス属性以外
				tmd->hp = 1;
			}
			break;
		case 9:
			/* 節制(Temperance) - 30秒間混乱にかかる */
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
				if(atn_rand() % 10000 < status_change_rate(target,SC_CONFUSION,10000,status_get_lv(src)))
					status_change_pretimer(target,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
			break;
		case 10:
			/* 悪魔(The Devil) - 防御力無視6666ダメージ + 30秒間ATK半分、MATK半分、呪い */
			if(atn_rand() % 10000 < status_change_rate(target,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
				status_change_start(target,SC_THE_DEVIL,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			unit_fixdamage(src,target,0, 0, 0,6666,1, 4, 0, 0);
			break;
		case 11:
			/* 塔(The Tower) - 防御力無視4444固定ダメージ */
			unit_fixdamage(src,target,0, 0, 0,4444,1, 4, 0, 0);
			break;
		case 12:
			/* 星(The Star) - 星が回る すなわち、5秒間スタンにかかる */
			if(atn_rand() % 10000 < status_change_rate(target,SC_STUN,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_STUN,7,0,0,0,5000,0,tick+status_get_amotion(src));
			break;
		case 13:
			/* 太陽(The Sun) - 30秒間ATK、MATK、回避、命中、防御力が全て20%ずつ下落する */
			if(!(status_get_mode(target)&MD_BOSS))	// ボス属性以外
				status_change_start(target,SC_THE_SUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
	}
	return 1;
}

/*==========================================
 * 指定範囲内でsrcに対して有効なターゲットのblの数を数える(foreachinarea)
 *------------------------------------------
 */
static int skill_count_target(struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	if((unit = va_arg(ap,struct skill_unit *)) == NULL)
		return 0;
	if(battle_check_target(&unit->bl,bl,BCT_ENEMY) <= 0)
		return 0;

	return 1;
}

/*==========================================
 * トラップ範囲処理(foreachinarea)
 *------------------------------------------
 */
static int skill_trap_splash(struct block_list *bl, va_list ap )
{
	unsigned int tick;
	int splash_count;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	struct block_list *ss;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = va_arg(ap,struct skill_unit *));
	nullpo_retr(0, sg = unit->group);
	nullpo_retr(0, ss = map_id2bl(sg->src_id));

	tick = va_arg(ap,unsigned int);
	splash_count = va_arg(ap,int);

	if(battle_check_target(&unit->bl,bl,BCT_ENEMY) > 0){
		switch(sg->unit_id){
			case UNT_FIREPILLAR_ACTIVE:	/* ファイアーピラー(発動後) */
				if(battle_config.firepillar_splash_on) {
					int i;
					for(i = 0; i < splash_count; i++)
						battle_skill_attack(BF_MAGIC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				} else {
					battle_skill_attack(BF_MAGIC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				}
				break;
			case UNT_SANDMAN:	/* サンドマン */
			case UNT_FLASHER:	/* フラッシャー */
			case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
			case UNT_MAGENTATRAP:		/* マゼンタトラップ */
			case UNT_COBALTTRAP:		/* コバルトトラップ */
			case UNT_MAIZETRAP:			/* メイズトラップ */
			case UNT_VERDURETRAP:		/* ヴェルデュールトラップ */
				skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
				break;
			case UNT_BLASTMINE:	/* ブラストマイン */
			case UNT_CLAYMORETRAP:	/* クレイモアトラップ */
				if(battle_config.trap_splash_on) {
					int i;
					for(i = 0; i < splash_count; i++) {
						battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
					}
				} else {
					battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				}
				break;
			case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
				break;
			case UNT_FREEZINGTRAP:	/* フリージングトラップ */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				battle_skill_attack(BF_WEAPON,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				break;
			case UNT_FIRINGTRAP:	/* ファイアリングトラップ */
			case UNT_ICEBOUNDTRAP:	/* アイスバウンドトラップ */
			case UNT_CLUSTERBOMB:	/* クラスターボム */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				break;
			case UNT_REVERBERATION:	/* 振動残響 */
				skill_addtimerskill(ss,tick + 200,bl->id,0,0,WM_REVERBERATION_MELEE,sg->skill_lv,0,(0x0f<<20)|0x0500|splash_count);
				skill_addtimerskill(ss,tick + 400,bl->id,0,0,WM_REVERBERATION_MAGIC,sg->skill_lv,0,(0x0f<<20)|0x0500|splash_count);
				break;
			default:
				break;
		}
	}

	return 0;
}

/*----------------------------------------------------------------------------
 * ステータス異常
 *----------------------------------------------------------------------------
 */

/* クローキング検査（周りに移動不可能地帯があるか） */
int skill_check_cloaking(struct block_list *bl)
{
	int i;
	struct status_change *sc;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && battle_config.pc_cloak_check_type&1)
		return 0;
	if(bl->type == BL_MOB && battle_config.monster_cloak_check_type&1)
		return 0;

	for(i=0;i<8;i++){
		if(map_getcell(bl->m,bl->x+dirx[i],bl->y+diry[i],CELL_CHKNOPASS))
			return 0;
	}
	status_change_end(bl, SC_CLOAKING, -1);
	sc = status_get_sc(bl);
	if(sc)
		sc->option &= ~OPTION_CLOAKING;	/* 念のための処理 */

	return 1;
}

/*
 *----------------------------------------------------------------------------
 * スキルユニット
 *----------------------------------------------------------------------------
 */

/*==========================================
 * 演奏/ダンスをやめる
 * flag 1で合奏中なら相方にユニットを任せる
 *------------------------------------------
 */
void skill_stop_dancing(struct block_list *src, int flag)
{
	struct map_session_data *sd = NULL;
	struct status_change *sc;
	struct skill_unit_group *group;

	nullpo_retv(src);

	sc = status_get_sc(src);
	if(sc == NULL)
		return;
	if(sc->data[SC_DANCING].timer == -1)
		return;

	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;

	group = map_id2sg(sc->data[SC_DANCING].val2); // ダンスのスキルユニットIDはval2に入ってる

	if(sd && group && sc->data[SC_DANCING].val4) { // 合奏中断
		struct map_session_data* dsd = map_id2sd(sc->data[SC_DANCING].val4); // 相方のsd取得
		if(flag) { // ログアウトなど片方が落ちても演奏が継続される
			if(dsd && src->id == group->src_id) { // グループを持ってるPCが落ちる
				group->src_id = dsd->bl.id; // 相方にグループを任せる
				linkdb_insert( &dsd->ud.skillunit, INT2PTR(group->bl.id), group );
				linkdb_erase( &sd->ud.skillunit, INT2PTR(group->bl.id) );
				if(flag&1) // ログアウト
					dsd->sc.data[SC_DANCING].val4 = 0; // 相方の相方を0にして合奏終了→通常のダンス状態
				if(flag&2) // ハエ飛びなど
					return; // 合奏もダンス状態も終了させない＆スキルユニットは置いてけぼり
			} else if(dsd && dsd->bl.id == group->src_id) { // 相方がグループを持っているPCが落ちる(自分はグループを持っていない)
				if(flag&1) // ログアウト
					dsd->sc.data[SC_DANCING].val4 = 0; // 相方の相方を0にして合奏終了→通常のダンス状態
				if(flag&2) // ハエ飛びなど
					return; // 合奏もダンス状態も終了させない＆スキルユニットは置いてけぼり
			}
			status_change_end(src, SC_DANCING, -1);	// 自分のステータスを終了させる
			// そしてグループは消さない＆消さないのでステータス計算もいらない？
			return;
		} else {
			if(dsd && src->id == group->src_id) { // グループを持ってるPCが止める
				status_change_end(&dsd->bl, SC_DANCING, -1);// 相手のステータスを終了させる
			}
			else if(dsd && dsd->bl.id == group->src_id) { // 相方がグループを持っているPCが止める(自分はグループを持っていない)
				status_change_end(src, SC_DANCING, -1);// 自分のステータスを終了させる
			}
		}
	}
	if(flag&2 && sd && group) { // ハエで飛んだときとかはユニットも飛ぶ
		skill_unit_move_unit_group(group, sd->bl.m, (sd->ud.to_x - sd->bl.x), (sd->ud.to_y - sd->bl.y));
		return;
	}
	if(group)
		skill_delunitgroup(group);
	if(sd)
		status_calc_pc(sd,0);
}

/*==========================================
 * ヘルモードの杖チェック
 *------------------------------------------
 */
static int skill_hermode_wp_check_sub(struct block_list *bl, va_list ap )
{
	int *flag;
	struct npc_data *nd;

	nullpo_retr(0, bl);
	nullpo_retr(0, nd = (struct npc_data *)bl);

	flag = va_arg(ap,int*);
	if(*flag)
		return 1;

	if(nd->subtype == WARP || (nd->subtype == SCRIPT && nd->class_ == WARP_CLASS))
		*flag = 1;

	return *flag;
}

int skill_hermode_wp_check(struct block_list *bl)
{
	int wp_flag = 0;
	int range   = battle_config.hermode_wp_check_range;

	nullpo_retr(0, bl);

	map_foreachinarea(skill_hermode_wp_check_sub,bl->m,bl->x-range,bl->y-range,bl->x+range,bl->y+range,BL_NPC,&wp_flag);
	return wp_flag;
}

/*==========================================
 * ガンバンテインによるユニット削除
 *------------------------------------------
 */
static int skill_delunit_by_ganbantein(struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;

	nullpo_retr(0, bl);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, unit->group);

	switch(unit->group->skill_id)
	{
		case MG_SAFETYWALL:
		case MG_FIREWALL:
		case MG_THUNDERSTORM:
		case AL_PNEUMA:
		case AL_WARP:
		case PR_SANCTUARY:
		case PR_MAGNUS:
		case WZ_FIREPILLAR:
		case WZ_METEOR:
		case WZ_VERMILION:
		case WZ_ICEWALL:
		case WZ_FROSTNOVA:
		case WZ_STORMGUST:
		case WZ_HEAVENDRIVE:
		case WZ_QUAGMIRE:
		case HT_SKIDTRAP:
		case HT_LANDMINE:
		case HT_ANKLESNARE:
		case HT_SHOCKWAVE:
		case HT_SANDMAN:
		case HT_FLASHER:
		case HT_FREEZINGTRAP:
		case HT_BLASTMINE:
		case HT_CLAYMORETRAP:
		case HT_TALKIEBOX:
		case AS_VENOMDUST:
		case RG_GRAFFITI:
		case AM_DEMONSTRATION:
		case CR_GRANDCROSS:
		case SA_VOLCANO:
		case SA_DELUGE:
		case SA_VIOLENTGALE:
		case SA_LANDPROTECTOR:
		case BA_DISSONANCE:
		case BA_WHISTLE:
		case BA_ASSASSINCROSS:
		case BA_POEMBRAGI:
		case BA_APPLEIDUN:
		case DC_UGLYDANCE:
		case DC_HUMMING:
		case DC_DONTFORGETME:
		case DC_FORTUNEKISS:
		case DC_SERVICEFORYOU:
		case WE_CALLPARTNER:
		case NPC_GRANDDARKNESS:
		case HP_BASILICA:
		case PA_GOSPEL:
		case PF_FOGWALL:
		case PF_SPIDERWEB:
		case WE_CALLPARENT:
		case WE_CALLBABY:
		case SG_SUN_WARM:
		case SG_MOON_WARM:
		case SG_STAR_WARM:
		case HW_GRAVITATION:
		case GS_DESPERADO:
		case GS_GROUNDDRIFT:
		case NJ_TATAMIGAESHI:
		case NJ_KAENSIN:
		case NJ_BAKUENRYU:
		case NJ_SUITON:
		case NJ_HYOUSYOURAKU:
		case NJ_RAIGEKISAI:
		case NPC_EVILLAND:
		case GC_POISONSMOKE:
		case AB_EPICLESIS:
		case WL_EARTHSTRAIN:
		case RA_ELECTRICSHOCKER:
		case RA_CLUSTERBOMB:
		case RA_MAGENTATRAP:
		case RA_COBALTTRAP:
		case RA_MAIZETRAP:
		case RA_VERDURETRAP:
		case RA_FIRINGTRAP:
		case RA_ICEBOUNDTRAP:
		case NC_NEUTRALBARRIER:
		case NC_STEALTHFIELD:
		case MA_SKIDTRAP:
		case MA_LANDMINE:
		case MA_SANDMAN:
		case MA_FREEZINGTRAP:
		case KO_HUUMARANKA:
		case KO_MAKIBISHI:
		case KO_ZENKAI:
		case SU_CN_METEOR:
		case NPC_DISSONANCE:
		case NPC_UGLYDANCE:
			skill_delunit(unit);
			break;
	}
	return 0;
}

/*==========================================
 * スキルユニット初期化
 *------------------------------------------
 */
static struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y)
{
	struct skill_unit *unit;

	nullpo_retr(NULL, group);
	nullpo_retr(NULL, unit = &group->unit[idx]);

	if(!unit->alive)
		group->alive_count++;

	unit->bl.id   = map_addobject(&unit->bl);
	unit->bl.type = BL_SKILL;
	unit->bl.m    = group->bl.m;
	unit->bl.x    = x;
	unit->bl.y    = y;
	unit->group   = group;
	unit->val1    = 0;
	unit->val2    = 0;
	unit->alive   = 1;

	map_addblock(&unit->bl);
	clif_skill_setunit(unit);

	if(group->skill_id == HP_BASILICA)
		skill_basilica_cell(unit,group->skill_lv,CELL_SETBASILICA);

	return unit;
}

/*==========================================
 * スキルユニット削除
 *------------------------------------------
 */
int skill_delunit(struct skill_unit *unit)
{
	struct skill_unit_group *group;
	unsigned int tick = gettick();

	nullpo_retr(0, unit);
	nullpo_retr(0, group = unit->group);

	if(!unit->alive)
		return 0;

	/* onlimitイベント呼び出し */
	skill_unit_onlimit(unit,tick);

	/* onoutイベント呼び出し */
	if(!unit->range) {
		map_foreachinarea(skill_unit_effect,unit->bl.m,
			unit->bl.x,unit->bl.y,unit->bl.x,unit->bl.y,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),
			&unit->bl,tick,0);
	}

	if(group->skill_id == HP_BASILICA)
		skill_basilica_cell(unit,group->skill_lv,CELL_CLRBASILICA);

	clif_skill_delunit(unit);

	unit->group = NULL;
	unit->alive = 0;
	map_delobjectnofree(unit->bl.id);
	if(group->alive_count > 0 && (--group->alive_count) <= 0)
		skill_delunitgroup(group);

	return 0;
}

/*==========================================
 * スキルユニットグループ初期化
 *------------------------------------------
 */
static struct skill_unit_group *skill_initunitgroup(struct block_list *src,int count,int skillid,int skilllv,int unit_id,unsigned int tick)
{
	struct unit_data *ud;
	struct skill_unit_group *group;

	nullpo_retr(NULL, src);
	nullpo_retr(NULL, ud = unit_bl2ud(src));

	group             = (struct skill_unit_group *)aCalloc(1,sizeof(struct skill_unit_group));
	group->bl.id      = map_addobject(&group->bl);
	group->bl.type    = BL_GRP;
	group->bl.m       = src->m;
	group->src_id     = src->id;
	group->party_id   = status_get_party_id(src);
	group->guild_id   = status_get_guild_id(src);
	group->unit       = (struct skill_unit *)aCalloc(count,sizeof(struct skill_unit));
	group->unit_count = count;
	group->val1       = 0;
	group->val2       = 0;
	group->skill_id   = skillid;
	group->skill_lv   = skilllv;
	group->unit_id    = unit_id;
	group->limit      = 10000;
	group->interval   = 1000;
	group->tick       = tick;
	group->valstr     = NULL;
	linkdb_insert( &ud->skillunit, INT2PTR(group->bl.id), group );

	return group;
}

/*==========================================
 * スキルユニットグループ削除
 *------------------------------------------
 */
int skill_delunitgroup(struct skill_unit_group *group)
{
	struct block_list *src;
	struct unit_data  *ud = NULL;

	nullpo_retr(0, group);

	if(group->unit_count <= 0)
		return 0;

	src = map_id2bl(group->src_id);
	if(src)
		ud = unit_bl2ud(src);

	// ダンススキルはダンス状態を解除する
	if(skill_get_unit_flag(group->skill_id,group->skill_lv)&UF_DANCE) {
		if(src)
			status_change_end(src,SC_DANCING,-1);
	}

	// 状態異常にユニットグループが保存されている場合はクリアする
	switch(group->unit_id) {
	case UNT_GOSPEL:
	case UNT_GRAFFITI:
	case UNT_GRAVITATION:
		if(src) {
			struct status_change *sc = status_get_sc(src);
			int type = GetSkillStatusChangeTable(group->skill_id);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				sc->data[type].val4 = 0;
				status_change_end(src,type,-1);
			}
		}
		break;
	}

	// 状態異常にユニットグループが保存されている場合はクリアする
	switch(group->skill_id) {
	case SG_SUN_WARM:	// 太陽の温もり
	case SG_MOON_WARM:	// 月の温もり
	case SG_STAR_WARM:	// 星の温もり
		if(src) {
			struct status_change *sc = status_get_sc(src);
			int type = GetSkillStatusChangeTable(group->skill_id);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				sc->data[type].val4 = 0;
				status_change_end(src,type,-1);
			}
		}
		break;
	}

	if(ud) {
		if( linkdb_erase( &ud->skillunit, INT2PTR(group->bl.id) ) == NULL ) {
			// 見つからなかった
			return 0;
		}
	}

	group->alive_count = 0;
	if(group->unit != NULL) {
		int i;
		for(i=0; i<group->unit_count; i++) {
			if(group->unit[i].alive)
				skill_delunit(&group->unit[i]);
		}
	}
	if(group->valstr != NULL) {
		aFree(group->valstr);
		group->valstr = NULL;
	}

	linkdb_final( &group->tickset );
	map_freeblock(group->unit);	/* free()の替わり */
	map_delobject(group->bl.id);

	return 0;
}

/*==========================================
 * スキルユニットグループ全削除
 *------------------------------------------
 */
int skill_clear_unitgroup(struct block_list *src)
{
	struct skill_unit_group *group;
	struct unit_data *ud;
	struct linkdb_node *node, *node2;

	nullpo_retr(0, src);
	nullpo_retr(0, ud = unit_bl2ud(src));

	node = ud->skillunit;
	while( node ) {
		node2 = node->next;
		group = (struct skill_unit_group *)node->data;
		if(group->src_id == src->id)
			skill_delunitgroup(group);
		node = node2;
	}
	linkdb_final( &ud->skillunit );

	return 0;
}

/*==========================================
 * スキルユニットタイマー発動処理用(foreachinarea)
 *------------------------------------------
 */
static int skill_unit_timer_sub_onplace(struct block_list *bl, va_list ap)
{
	struct skill_unit *unit;
	struct skill_unit_group *group;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	unit = va_arg(ap,struct skill_unit *);
	tick = va_arg(ap,unsigned int);

	if(!unit || !unit->alive)
		return 0;
	if(!(bl->type & (BL_PC | BL_MOB | BL_MERC | BL_ELEM)))
		return 0;

	nullpo_retr(0, group = unit->group);

	if(battle_check_target(&unit->bl,bl,group->target_flag) <= 0)
		return 0;

	// 壁抜け防止の射線チェック
	if(!path_search_long(NULL,bl->m,bl->x,bl->y,unit->bl.x,unit->bl.y))
		return 0;

	skill_unit_onplace_timer(unit,bl,tick);

	return 0;
}

/*==========================================
 * スキルユニットタイマー処理用(foreachobject)
 *------------------------------------------
 */
static int skill_unit_timer_sub( struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;
	struct skill_unit_group *group;
	int range;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, group = unit->group);

	tick = va_arg(ap,unsigned int);

	if(!unit->alive)
		return 0;

	range = unit->range;

	/* onplace_timerイベント呼び出し */
	if(range >= 0 && group->interval != -1)
	{
		map_foreachinarea(skill_unit_timer_sub_onplace, bl->m,
			bl->x-range,bl->y-range,bl->x+range,bl->y+range,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),unit,tick);
		if(!unit->alive)
			return 0;
		// マグヌスは発動したユニットは削除する
		if(group->skill_id == PR_MAGNUS && unit->val2) {
			skill_delunit(unit);
			return 0;
		}
	}

	// イドゥンの林檎による回復
	if(group->unit_id == UNT_APPLEIDUN &&
#ifdef PRE_RENEWAL
		DIFF_TICK(tick,group->tick) >= 6000 * group->val3
#else
		DIFF_TICK(tick,group->tick) >= 5000 * group->val3
#endif
	) {
		struct block_list *src = map_id2bl(group->src_id);
		if(src == NULL)
			return 0;
		if(src->type == BL_PC || src->type == BL_MOB) {
			range = skill_get_unit_layout_type(group->skill_id,group->skill_lv);
			map_foreachinarea(skill_idun_heal,src->m,
				src->x-range,src->y-range,src->x+range,src->y+range,src->type,unit,src);
		}
		group->val3++;
	}

	if(DIFF_TICK(tick,group->tick) >= group->limit || DIFF_TICK(tick,group->tick) >= unit->limit) {
		/* 時間切れ削除 */
		switch(group->unit_id) {
			case UNT_WARP_WAITING:	/* ワープポータル(発動前) */
				group->unit_id = UNT_WARP_ACTIVE;
				clif_changelook(bl,LOOK_BASE,group->unit_id);
				group->limit = unit->limit = skill_get_time(group->skill_id,group->skill_lv);
				return 0;
			case UNT_BLASTMINE:		/* ブラストマイン */
				group->unit_id = UNT_USED_TRAPS;
				clif_changelook(bl,LOOK_BASE,group->unit_id);
				group->limit = unit->limit = DIFF_TICK(tick+1500,group->tick);
				return 0;

			case UNT_ANKLESNARE:	/* アンクルスネア */
				if(group->val2 > 0) {
					break;
				}
				// fall through
			case UNT_SKIDTRAP:	/* スキッドトラップ */
			case UNT_LANDMINE:	/* ランドマイン */
			case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
			case UNT_SANDMAN:	/* サンドマン */
			case UNT_FLASHER:	/* フラッシャー */
			case UNT_FREEZINGTRAP:	/* フリージングトラップ */
			case UNT_TALKIEBOX:	/* トーキーボックス */
				if(unit->val1 <= 0) {
					break;
				}
				// fall through
			case UNT_CLAYMORETRAP:		/* クレイモアトラップ */
			case UNT_MAGENTATRAP:		/* マゼンタトラップ */
			case UNT_COBALTTRAP:		/* コバルトトラップ */
			case UNT_MAIZETRAP:			/* メイズトラップ */
			case UNT_VERDURETRAP:		/* ヴェルデュールトラップ */
			case UNT_FIRINGTRAP:		/* ファイアリングトラップ */
			case UNT_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
			case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
			case UNT_CLUSTERBOMB:		/* クラスターボム */
				if(itemdb_exists(unit->group->val3)) {
					struct block_list *src = map_id2bl(group->src_id);
					if(src && src->type == BL_PC) {
						struct item item_tmp;
						memset(&item_tmp,0,sizeof(item_tmp));
						item_tmp.nameid   = unit->group->val3;
						item_tmp.identify = 1;
						map_addflooritem(&item_tmp,1,bl->m,bl->x,bl->y,0,0,0,0);	// 罠返還
					}
				}
				break;
			case UNT_FEINTBOMB:		/* フェイントボム */
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-3,bl->y-3,bl->x+3,bl->y+3,(BL_CHAR|BL_SKILL),
					map_id2bl(group->src_id),group->skill_id,group->skill_lv,group->tick,BCT_ENEMY|1,
					skill_castend_damage_id);
				break;
			case UNT_BANDING:	/* バンディング */
				group->limit = DIFF_TICK(tick,group->tick)+600000;
				return 0;
			case UNT_REVERBERATION:	/* 振動残響 */
				{
					int splash_count = map_foreachinarea(skill_count_target,bl->m,
						bl->x-2,bl->y-2,bl->x+2,bl->y+2,
						(BL_CHAR|BL_SKILL),bl);
					map_foreachinarea(skill_trap_splash,
						bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,
						(BL_CHAR|BL_SKILL),bl,tick,splash_count);
					group->unit_id = UNT_USED_TRAPS;
					clif_changelook(bl,LOOK_BASE,group->unit_id);
					group->limit = unit->limit = DIFF_TICK(tick,group->tick)+1500;
				}
				return 0;
			default:
				break;
		}
		skill_delunit(unit);
	} else {
		/* 耐久切れチェック */
		switch(group->unit_id) {
			case UNT_ICEWALL:	/* アイスウォール */
				unit->val1 -= 5;
				if(unit->val1 <= 0 && unit->limit + group->tick > tick + 700)
					unit->limit = DIFF_TICK(tick+700,group->tick);
				break;
			case UNT_FIREPILLAR_WAITING:	/* ファイアーピラー(発動前) */
			case UNT_SKIDTRAP:	/* スキッドトラップ */
			case UNT_ANKLESNARE:	/* アンクルスネア */
			case UNT_LANDMINE:	/* ランドマイン */
			case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
			case UNT_SANDMAN:	/* サンドマン */
			case UNT_FLASHER:	/* フラッシャー */
			case UNT_FREEZINGTRAP:	/* フリージングトラップ */
			case UNT_TALKIEBOX:	/* トーキーボックス */
				if(unit->val1 <= 0) {
					if(group->unit_id == UNT_ANKLESNARE && group->val2 > 0) {	// 捕獲中のアンクルなら即座に削除
						skill_delunit(unit);
					} else {
						group->unit_id = UNT_USED_TRAPS;
						group->limit = DIFF_TICK(tick,group->tick)+1500;
					}
				}
				break;
			case UNT_REVERBERATION:	/* 振動残響 */
			case UNT_WALLOFTHORN:	/* ソーンウォール */
				if(unit->val1 <= 0)
					skill_delunit(unit);
				break;
		}
	}

	return 0;
}

/*==========================================
 * スキルユニットタイマー処理
 *------------------------------------------
 */
static int skill_unit_timer( int tid,unsigned int tick,int id,void *data)
{
	map_foreachobject( skill_unit_timer_sub, BL_SKILL, tick );

	return 0;
}

/*==========================================
 * ユニット移動処理用(foreachinarea)
 *------------------------------------------
 */
static int skill_unit_move_sub(struct block_list *bl, va_list ap)
{
	struct skill_unit *unit;
	struct skill_unit_group *group;
	struct block_list *target;
	unsigned int tick;
	int flag;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, target = va_arg(ap,struct block_list*));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, group = unit->group);

	tick = va_arg(ap,unsigned int);
	flag = va_arg(ap,int);

	if(!unit->alive || group->interval != -1)
		return 0;

	if(flag)
		skill_unit_onplace(unit,target,tick);
	else
		skill_unit_onout(unit,target,tick);

	return 0;
}

/*==========================================
 * ユニット移動時処理
 *   flag 0:移動前処理(ユニット位置のスキルユニットを離脱)
 *        1:移動後処理(ユニット位置のスキルユニットを発動)
 *------------------------------------------
 */
int skill_unit_move(struct block_list *bl,unsigned int tick,int flag)
{
	nullpo_retr(0, bl);

	if(bl->prev == NULL)
		return 0;

	if(!(bl->type & (BL_PC | BL_MOB | BL_MERC | BL_ELEM)))
		return 0;

	map_foreachinarea(skill_unit_move_sub,bl->m,bl->x,bl->y,bl->x,bl->y,BL_SKILL,bl,tick,flag);

	return 0;
}

/*==========================================
 * スキルユニット自体の移動時処理
 * 引数はグループと移動量
 *------------------------------------------
 */
int skill_unit_move_unit_group(struct skill_unit_group *group,int m,int dx,int dy)
{
	int i,j,moveblock;
	unsigned int tick = gettick();
	unsigned char m_flag[MAX_SKILL_UNIT_COUNT];	// group->unit_countはMAX_SKILL_UNIT_COUNTを越えることはない
	struct skill_unit *unit1, *unit2;

	nullpo_retr(0, group);

	if(group->unit_count <= 0)
		return 0;
	if(group->unit == NULL)
		return 0;

	// 移動可能なスキルはダンス系と罠とファイアーピラーと温もりのみ
	if( !(skill_get_unit_flag(group->skill_id,group->skill_lv)&UF_DANCE) &&
	     !skill_unit_istrap(group->unit_id) &&
	     group->unit_id != UNT_FIREPILLAR_WAITING &&
	     group->skill_id != SG_SUN_WARM &&
	     group->skill_id != SG_MOON_WARM &&
	     group->skill_id != SG_STAR_WARM &&
	     group->unit_id != UNT_NEUTRALBARRIER &&
	     group->unit_id != UNT_STEALTHFIELD	&&
	     group->unit_id != UNT_KINGS_GRACE )
		return 0;
	if( group->unit_id == UNT_ANKLESNARE && (battle_config.anklesnare_no_knockbacking || group->val2 > 0) )	// 補足中のアンクルは移動不可
		return 0;

	// 移動フラグ
	memset(m_flag, 0, sizeof(m_flag));

	// 先にフラグを全部決める
	//   m_flag
	//     0: 単純移動
	//     1: ユニットを移動する(現位置からユニットがなくなる)
	//     2: 残留＆新位置が移動先となる(移動先にユニットが存在しない)
	//     3: 残留
	for(i=0; i<group->unit_count; i++) {
		unit1= &group->unit[i];
		if(!unit1->alive || unit1->bl.m != m)
			continue;
		for(j=0; j<group->unit_count; j++) {
			unit2 = &group->unit[j];
			if(!unit2->alive)
				continue;
			if(unit1->bl.x + dx == unit2->bl.x && unit1->bl.y + dy == unit2->bl.y) {
				// 移動先にユニットがかぶっている
				m_flag[i] |= 0x1;
			}
			if(unit1->bl.x - dx == unit2->bl.x && unit1->bl.y - dy == unit2->bl.y) {
				// ユニットがこの場所にやってくる
				m_flag[i] |= 0x2;
			}
		}
	}
	// フラグに基づいてユニット移動
	// フラグが1のunitを探し、フラグが2のunitの移動先に移す
	j = 0;
	for(i=0; i<group->unit_count; i++) {
		unit1 = &group->unit[i];
		if(!unit1->alive)
			continue;
		if(!(m_flag[i]&0x2)) {
			// ユニットがなくなる場所でスキルユニット影響を消す
			map_foreachinarea(skill_unit_effect,unit1->bl.m,
				unit1->bl.x,unit1->bl.y,unit1->bl.x,unit1->bl.y,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),
				&unit1->bl,tick,0);
		}
		if(m_flag[i] == 0) {
			// 単純移動
			moveblock = map_block_is_differ(&unit1->bl, m, unit1->bl.x+dx, unit1->bl.y+dy);
			if(moveblock)
				map_delblock(&unit1->bl);
			unit1->bl.m = m;
			unit1->bl.x += dx;
			unit1->bl.y += dy;
			if(moveblock)
				map_addblock(&unit1->bl);
			clif_skill_setunit(unit1);
		} else if(m_flag[i] == 1) {
			// フラグが2のものを探してそのユニットの移動先に移動
			for( ; j<group->unit_count; j++) {
				if(m_flag[j] == 2) {
					// 継承移動
					unit2 = &group->unit[j];
					if(!unit2->alive)
						continue;
					moveblock = map_block_is_differ(&unit1->bl, m, unit2->bl.x+dx, unit2->bl.y+dy);
					if(moveblock)
						map_delblock(&unit1->bl);
					unit1->bl.m = m;
					unit1->bl.x = unit2->bl.x+dx;
					unit1->bl.y = unit2->bl.y+dy;
					if(moveblock)
						map_addblock(&unit1->bl);
					clif_skill_setunit(unit1);
					j++;
					break;
				}
			}
		}
		if(!(m_flag[i]&0x2)) {
			// 移動後の場所でスキルユニットを発動
			map_foreachinarea(skill_unit_effect,unit1->bl.m,
				unit1->bl.x,unit1->bl.y,unit1->bl.x,unit1->bl.y,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),
				&unit1->bl,tick,1);
		}
	}
	return 0;
}

/*==========================================
 * 設置済みスキルユニットの数を返す
 *------------------------------------------
 */
static int skill_count_unitgroup(struct unit_data *ud,int skillid)
{
	int c = 0;
	struct skill_unit_group *group;
	struct linkdb_node *node;

	nullpo_retr(0, ud);

	node = ud->skillunit;
	while( node ) {
		group = (struct skill_unit_group *)node->data;
		if( group->alive_count > 0 && group->skill_id == skillid ) {
			c++;
		}
		node = node->next;
	}
	return c;
}

/*----------------------------------------------------------------------------
 * アイテム合成
 *----------------------------------------------------------------------------
 */

/*==========================================
 * アイテム合成可能判定
 *------------------------------------------
 */
int skill_can_produce_mix( struct map_session_data *sd, int idx, int trigger)
{
	int i,j,req_skill;

	nullpo_retr(0, sd);

	if(idx < 0 || idx >= MAX_SKILL_PRODUCE_DB)
		return 0;

	if(skill_produce_db[idx].nameid <= 0)
		return 0;

	if(trigger >= 0) {
		if(skill_produce_db[idx].itemlv != trigger)
			return 0;
	}

	// req_skillが0以下のときはreq_skilllvの判定をしない
	if((req_skill = skill_produce_db[idx].req_skill) > 0 && pc_checkskill(sd,req_skill) < skill_produce_db[idx].req_skilllv)
		return 0;

	for(i=0; i<MAX_PRODUCE_RESOURCE; i++) {
		int amount, count = 0;
		int id = skill_produce_db[idx].mat_id[i];

		if(id <= 0)	// これ以上は材料要らない
			break;
		amount = skill_produce_db[idx].mat_amount[i];
		if((sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB) && sd->skill_menu.lv > 1)
			amount = amount * 10;
		if(amount <= 0)
			amount = 1;	// 消耗されないが作る時必要なアイテム

		for(j=0; j<MAX_INVENTORY; j++) {
			if(sd->status.inventory[j].nameid == id) {
				count += sd->status.inventory[j].amount;
				if(count >= amount)
					break;	// 足りたので検索終了
			}
		}
		if(count < amount)	// アイテムが足りない
			return 0;
	}
	return 1;
}

/*==========================================
 * アイテム合成の成功確率計算
 *------------------------------------------
 */
static int skill_calc_produce_rate(struct map_session_data *sd, int idx, int sc, int ele)
{
	int make_per, skill_lv;
	int int_ = sd->paramc[3];
	int dex  = sd->paramc[4];
	int luk  = sd->paramc[5];

	nullpo_retr(0, sd);

	if(idx < 0 || idx >= MAX_SKILL_PRODUCE_DB)
		return 0;

	make_per = skill_produce_db[idx].per;
	skill_lv = pc_checkskill(sd,skill_produce_db[idx].req_skill);

	/* 基本確率を算出してmake_perに加算 */

	switch (skill_produce_db[idx].itemlv)
	{
	case PRD_WEAPON_L1:	// 武器製造
	case PRD_WEAPON_L2:
	case PRD_WEAPON_L3:
		make_per += sd->status.job_level*20 + dex*10 + luk*10 + skill_lv*500 + pc_checkskill(sd,BS_WEAPONRESEARCH)*100;

		if(pc_search_inventory(sd,989) >= 0)		// エンペリウムの金敷
			make_per += 1000;
		else if(pc_search_inventory(sd,988) >= 0)	// 黄金の金敷
			make_per += 500;
		else if(pc_search_inventory(sd,987) >= 0)	// オリデオコンの金敷
			make_per += 300;
		//else if(pc_search_inventory(sd,986) >= 0)	// 金敷
		//	make_per += 0:

		if(ele)
			make_per -= 2000;	// 属性石の確率低下
		if(sc > 0)
			make_per -= sc * 1500;	// 星の確率低下

		if(skill_produce_db[idx].itemlv == PRD_WEAPON_L3)
			make_per += pc_checkskill(sd,BS_ORIDEOCON)*100;	// オリデオコン研究は暫定

		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;

	case PRD_ORE:		// 鉱石
		make_per += sd->status.job_level*20 + dex*10 + luk*10 + skill_lv*500;
		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;

	case PRD_PHARMACY:	// ファーマシー
		if(skill_produce_db[idx].nameid == 7142 && pc_checkskill(sd,AM_BIOETHICS) <= 0) {	// 生命倫理未修得時は成功率0
			make_per = 0;
		} else {
			make_per += pc_checkskill(sd,AM_LEARNINGPOTION)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
			if(battle_config.pp_rate != 100)
				make_per = make_per * battle_config.pp_rate/100;
		}
		break;

	case PRD_CDP:		// デッドリーポイズン
		make_per += dex*40 + luk*20;
		if(battle_config.cdp_rate != 100)
			make_per = make_per * battle_config.cdp_rate/100;
		break;

	case PRD_CONVERTER:	// コンバーター
		switch(skill_produce_db[idx].nameid)
		{
			case 12114: skill_lv = pc_checkskill(sd,SA_FLAMELAUNCHER);	break;
			case 12115: skill_lv = pc_checkskill(sd,SA_FROSTWEAPON);	break;
			case 12116: skill_lv = pc_checkskill(sd,SA_LIGHTNINGLOADER);	break;
			case 12117: skill_lv = pc_checkskill(sd,SA_SEISMICWEAPON);	break;
			default: skill_lv = 5; break;
		}
		make_per += skill_lv*1000 + sd->status.job_level*20 + int_*10 + dex*10;
		if(battle_config.scroll_produce_rate != 100)
			make_per = make_per * battle_config.scroll_produce_rate/100;
		break;

	case PRD_COOKING:	// 料理
		make_per += sd->skill_menu.lv + sd->status.job_level*20 + dex*20 + luk*10;
		if(battle_config.cooking_rate != 100)
			make_per = make_per * battle_config.cooking_rate/100;
		break;

	/* 以下未実装製造 */
	case PRD_SCROLL:	// スクロール
		make_per += sd->skill_menu.lv + sd->status.job_level*10 + int_*10 + dex*10;
		if(battle_config.scroll_produce_rate != 100)
			make_per = make_per * battle_config.scroll_produce_rate/100;
		break;

	case PRD_SYN_POTION:	// ポーション合成
		make_per += sd->skill_menu.lv + sd->status.job_level*10 + int_*10 + dex*10 - skill_lv*200;
		if(battle_config.making_rate != 100)
			make_per = make_per * battle_config.making_rate/100;
		break;

	case PRD_COIN:		// コイン
	case PRD_NUGGET:	// 塊
	case PRD_ORIDEOCON:	// オリデオコン研究
		make_per += sd->status.base_level*30 + dex*20 + luk*10 + skill_lv*500;
		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;
	case PRD_RUNE:		// ルーンストーン製造
		make_per += skill_lv*200 + sd->status.job_level*20 + (dex + luk)*5;
		break;
	case PRD_NEWPOISON:	// 新毒製造
		make_per += pc_checkskill(sd,GC_RESEARCHNEWPOISON)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
		break;
	case PRD_MIX_COOKING:	// ミックスクッキング
		make_per += 3000 + sd->status.job_level*20 + dex*20 + luk*10;
		break;
	case PRD_MAKEBOMB:	// 爆弾製造
		make_per += 5000 + sd->status.job_level*20 + dex*20 + luk*10;
		break;
	case PRD_S_PHARMACY:	// スペシャルファーマシー
		make_per += pc_checkskill(sd,AM_LEARNINGPOTION)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
		if(battle_config.pp_rate != 100)
			make_per = make_per * battle_config.pp_rate/100;
		break;
	}

	if(make_per < 1)
		make_per = 1;

	// 養子の成功率70%
	if(pc_isbaby(sd))
		make_per = make_per * 70/100;

	return make_per;
}

/*==========================================
 * ファーマシーによるランキングポイント計算
 *------------------------------------------
 */
static int skill_am_ranking_point(struct map_session_data *sd, int nameid, int success)
{
	int point = 0;

	nullpo_retr(0, sd);

	// 成功時
	if(success) {
		// 全てのファーマシー対象設定か、スリム系の場合に処理
		if(battle_config.pharmacy_get_point_type || nameid == 545 || nameid == 546 || nameid == 547) {
			// 連続成功数増加
			sd->am_pharmacy_success++;
			if(sd->am_pharmacy_success > 10) {
				sd->am_pharmacy_success = 10;
			}
			// +10成功したら合計ポイント+64?
			// 現在 規定成功数ごとにポイントを貰えるように設定
			if(battle_config.alchemist_point_type) {
				if(sd->am_pharmacy_success == 10) {
					point = 50;
					sd->am_pharmacy_success = 0;
				}
			} else {
				switch(sd->am_pharmacy_success) {
					case 3:
						point = 1;
						break;
					case 5:
						point = 3;
						break;
					case 7:
						point= 10;
						break;
					case 10:
						point = 50;
						sd->am_pharmacy_success = 0;
						break;
				}
			}
		}
	} else {	// 失敗時
		sd->am_pharmacy_success = 0;
		if(battle_config.alchemist_point_type) {
			if(sd->am_pharmacy_success >= 7)
				point = 10;
			else if(sd->am_pharmacy_success >= 5)
				point = 3;
			else if(sd->am_pharmacy_success >= 3)
				point = 1;
		}
	}
	return point;
}

/*==========================================
 * アイテム合成
 *------------------------------------------
 */
void skill_produce_mix(struct map_session_data *sd, int nameid, int slot1, int slot2, int slot3)
{
	int slot[3];
	int i, sc, ele, type;
	int idx= -1, cnt=0;

	nullpo_retv(sd);

	if(nameid <= 0)		// cancel
		return;

	for(i=0; i<MAX_SKILL_PRODUCE_DB; i++) {
		if(skill_produce_db[i].nameid == nameid) {
			idx = i;
			break;
		}
	}
	if(idx < 0)
		return;

	if(!skill_can_produce_mix(sd,idx,-1)) {	/* 条件不足 */
		if(sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB)
			clif_skill_message(sd, sd->skill_menu.id, 808);	// 材料が足りません。
		return;
	}

	slot[0] = slot1;
	slot[1] = slot2;
	slot[2] = slot3;

	/* 埋め込み処理 */
	for(i=0, sc=0, ele=0; i<3; i++) {
		int j;
		if(slot[i] <= 0)
			continue;
		j = pc_search_inventory(sd,slot[i]);
		if(j < 0)	/* 不正パケット(アイテム存在)チェック */
			continue;
		if(slot[i] == 1000) {	/* 星のかけら */
			pc_delitem(sd,j,1,1,1);
			sc++;
			cnt++;
		}
		if(slot[i] >= 994 && slot[i] <= 997 && ele == 0) {	/* 属性石 */
			static const int ele_table[4] = { ELE_FIRE, ELE_WATER, ELE_WIND, ELE_EARTH };
			pc_delitem(sd,j,1,1,1);
			ele = ele_table[slot[i]-994];
			cnt++;
		}
	}

	type = skill_produce_db[idx].itemlv;

	if(type == PRD_RUNE) {
		i = pc_search_inventory(sd,nameid);
		if(i >= 0 && sd->status.inventory[i].amount >= 20 ) {	/* 作成前に所持限界数を超えている */
			clif_msgstringtable(sd, 0x61b);	// 最大所持量より多いルーンストーンを作成することはできません。
			return;
		}
	}

	/* 材料消費 */
	for(i=0; i<MAX_PRODUCE_RESOURCE; i++) {
		int amount;
		int id = skill_produce_db[idx].mat_id[i];

		if(id <= 0)	// これ以上は材料要らない
			break;
		amount = skill_produce_db[idx].mat_amount[i];	/* 必要な個数 */
		if((sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB) && sd->skill_menu.lv > 1)
			amount = amount * 10;
		do {	/* ２つ以上のインデックスにまたがっているかもしれない */
			int j, c = 0;

			j = pc_search_inventory(sd,id);
			if(j >= 0) {
				c = sd->status.inventory[j].amount;
				if(c > amount)
					c = amount;	/* 足りている */
				pc_delitem(sd,j,c,0,1);
			} else {
				if(battle_config.error_log)
					printf("skill_produce_mix: material item error\n");
				return;
			}
			amount -= c;	/* まだ足りない個数を計算 */
		} while(amount > 0);	/* 材料を消費するまで繰り返す */
	}

	if(atn_rand()%10000 < skill_calc_produce_rate(sd, idx, sc, ele) || type == PRD_S_PHARMACY) {	// 確率判定
		/* 成功 */
		struct item tmp_item;
		int amount = 1;
		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid   = nameid;
		tmp_item.amount   = 1;
		tmp_item.identify = 1;

		if(type == PRD_WEAPON_L1 || type == PRD_WEAPON_L2 || type == PRD_WEAPON_L3)
		{
			tmp_item.card[0] = 0x00ff;					// 製造武器フラグ
			tmp_item.card[1] = ((sc * 5) << 8) + ele;			// 属性石と星
			*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// キャラID
		}
		else {
			int flag = 0;
			if(type == PRD_PHARMACY || type == PRD_SYN_POTION)
				flag = battle_config.produce_potion_name_input;
			else if(type == PRD_CONVERTER || type == PRD_SCROLL)
				flag = battle_config.scroll_item_name_input;
			else
				flag = battle_config.produce_item_name_input;

			if(flag) {
				tmp_item.card[0] = 0x00fe;
				tmp_item.card[1] = 0;
				*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// キャラID
			}
		}

		switch (type) {
			case PRD_PHARMACY:
			{
				int point = skill_am_ranking_point(sd, nameid, 1);
				if(point > 0) {
					ranking_gain_point(sd,RK_ALCHEMIST,point);
					ranking_setglobalreg(sd,RK_ALCHEMIST);
					ranking_update(sd,RK_ALCHEMIST);
				}
				clif_produceeffect(sd,2,nameid);	/* 製薬エフェクト */
				clif_misceffect(&sd->bl,5);		/* 他人にも成功を通知 */
				break;
			}
			case PRD_CDP:
			case PRD_CONVERTER:
			case PRD_SYN_POTION:
				clif_produceeffect(sd,2,nameid);	/* 暫定で製薬エフェクト */
				clif_misceffect(&sd->bl,5);
				break;
			case PRD_WEAPON_L1:
			case PRD_WEAPON_L2:
			case PRD_WEAPON_L3:
				if(tmp_item.card[0] == 0x00ff && cnt == 3 && itemdb_wlv(nameid) == 3) {
					ranking_gain_point(sd,RK_BLACKSMITH,10);
					ranking_setglobalreg(sd,RK_BLACKSMITH);
					ranking_update(sd,RK_BLACKSMITH);
				}
				clif_produceeffect(sd,0,nameid);	/* 武器製造エフェクト */
				clif_misceffect(&sd->bl,3);
				break;
			case PRD_ORE:
			case PRD_COIN:
			case PRD_NUGGET:
			case PRD_ORIDEOCON:
				clif_produceeffect(sd,0,nameid);	/* 武器製造エフェクト */
				clif_misceffect(&sd->bl,3);
				break;
			case PRD_COOKING:
				clif_misceffect2(&sd->bl,608);
				break;
			case PRD_SCROLL:
				clif_misceffect2(&sd->bl,610);
				break;
			case PRD_RUNE:
				{
					int lv = pc_checkskill(sd,RK_RUNEMASTERY);
					if(lv >= 10)
						amount += atn_rand()%3;
					else if(lv >= 5)
						amount += atn_rand()%2;
					i = pc_search_inventory(sd,nameid);
					if(i >= 0 && sd->status.inventory[i].amount + amount >= 20 ) {
						amount = 20 - sd->status.inventory[i].amount;
					}
					clif_produceeffect(sd,2,nameid);
					clif_misceffect(&sd->bl,5);
				}
				break;
			case PRD_NEWPOISON:
				amount += 5 + atn_rand()%4;
				clif_produceeffect(sd,2,nameid);
				clif_misceffect(&sd->bl,5);
				break;
			case PRD_S_PHARMACY:
				if(sd->skill_menu.lv >= 10)
					amount = 4 + atn_rand()%3;
				else if(sd->skill_menu.lv >= 9)
					amount = 3 + atn_rand()%3;
				else if(sd->skill_menu.lv >= 6)
					amount = 3;
				else if(sd->skill_menu.lv == 1)
					amount = 1;
				else
					amount = 2;
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// 成功しました。
				break;
			case PRD_MIX_COOKING:
				if(sd->skill_menu.lv > 1)
					amount = 1 + atn_rand()%15;
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// 成功しました。
				break;
			case PRD_MAKEBOMB:
				if(sd->skill_menu.lv > 1)
					amount = 5 + atn_rand()%11;
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// 成功しました。
				break;
		}
		pc_additem(sd,&tmp_item,amount);	// 重量オーバーなら消滅
	} else {
		/* 失敗 */
		switch (type) {
			case PRD_PHARMACY:
				{
					int point = skill_am_ranking_point(sd, nameid, 0);
					if(point > 0) {
						ranking_gain_point(sd,RK_ALCHEMIST,point);
						ranking_setglobalreg(sd,RK_ALCHEMIST);
						ranking_update(sd,RK_ALCHEMIST);
					}
					clif_produceeffect(sd,3,nameid);	/* 製薬失敗エフェクト */
					clif_misceffect(&sd->bl,6);		/* 他人にも失敗を通知 */
				}
				break;
			case PRD_CDP:
				clif_produceeffect(sd,3,nameid);	/* 暫定で製薬エフェクト */
				clif_misceffect(&sd->bl,6);		/* 他人にも失敗を通知 */
				pc_heal(sd, -(sd->status.max_hp>>2), 0);
				break;
			case PRD_CONVERTER:
			case PRD_SYN_POTION:
			case PRD_RUNE:
			case PRD_NEWPOISON:
				clif_produceeffect(sd,3,nameid);	/* 暫定で製薬エフェクト */
				clif_misceffect(&sd->bl,6);		/* 他人にも失敗を通知 */
				break;
			case PRD_WEAPON_L1:
			case PRD_WEAPON_L2:
			case PRD_WEAPON_L3:
			case PRD_ORE:
			case PRD_COIN:
			case PRD_NUGGET:
			case PRD_ORIDEOCON:
				clif_produceeffect(sd,1,nameid);	/* 武器製造失敗エフェクト */
				clif_misceffect(&sd->bl,2);		/* 他人にも失敗を通知 */
				break;
			case PRD_COOKING:
				clif_misceffect2(&sd->bl,609);
				break;
			case PRD_SCROLL:
				clif_misceffect2(&sd->bl,611);
				break;
			case PRD_S_PHARMACY:
				clif_skill_message(sd, sd->skill_menu.id, 1575);	// 失敗しました。
				break;
			case PRD_MIX_COOKING:
				{
					static const int failitem[] = { 12435, 13265, 13266, 13267, 13268 };
					struct item tmp_item;
					int amount = 1;
					memset(&tmp_item, 0, sizeof(tmp_item));
					tmp_item.nameid   = failitem[atn_rand()%(sizeof(failitem)/sizeof(failitem[0]))];
					tmp_item.amount   = 1;
					tmp_item.identify = 1;
					if(sd->skill_menu.lv > 1) {
						amount += atn_rand()%15;
						clif_skill_message(sd, sd->skill_menu.id, 1576);	// 失敗し、全ての材料がなくなりました。
					} else {
						clif_skill_message(sd, sd->skill_menu.id, 1575);	// 失敗しました。
					}
					pc_additem(sd,&tmp_item,amount);
				}
				break;
			case PRD_MAKEBOMB:
				if(sd->skill_menu.lv > 1)
					clif_skill_message(sd, sd->skill_menu.id, 1576);	// 失敗し、全ての材料がなくなりました。
				else
					clif_skill_message(sd, sd->skill_menu.id, 1575);	// 失敗しました。
				break;
		}
	}
	return;
}

/*==========================================
 * トワイライトファーマシー
 *------------------------------------------
 */
static int skill_am_twilight_sub(struct map_session_data* sd,int nameid,int count)
{
	int i, make_per = 0, amount = 0, point = 0;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_SKILL_PRODUCE_DB; i++) {
		if(skill_produce_db[i].nameid == nameid)
			break;
	}
	if(i >= MAX_SKILL_PRODUCE_DB)
		return 0;	// 存在しない製造アイテム

	make_per = skill_calc_produce_rate(sd, i, 0, 0);

	for(i=0; i<count; i++) {
		int n = (atn_rand()%10000 < make_per)? 1: 0;
		amount += n;
		point += skill_am_ranking_point(sd, nameid, n);
	}

	if(amount > 0) {
		struct item tmp_item;
		clif_produceeffect(sd,2,nameid);	/* 製薬エフェクト */
		clif_misceffect(&sd->bl,5);		/* 他人にも成功を通知 */

		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid   = nameid;
		tmp_item.amount   = amount;
		tmp_item.identify = 1;

		if(battle_config.produce_potion_name_input)
		{
			tmp_item.card[0] = 0x00fe;
			tmp_item.card[1] = 0;
			*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// キャラID
		}
		pc_additem(sd, &tmp_item, amount);	// 重量オーバーなら消滅
	} else {
		// 失敗
		clif_produceeffect(sd,3,nameid);	/* 製薬失敗エフェクト */
		clif_misceffect(&sd->bl,6);		/* 他人にも失敗を通知 */
	}

	if(point > 0) {
		ranking_gain_point(sd,RK_ALCHEMIST,point);
		ranking_setglobalreg(sd,RK_ALCHEMIST);
		ranking_update(sd,RK_ALCHEMIST);
	}
	return 1;
}

static int skill_am_twilight(struct map_session_data *sd, int skillid)
{
	nullpo_retr(0, sd);

	switch(skillid) {
		case AM_TWILIGHT1:
			skill_am_twilight_sub(sd,504,200);
			break;
		case AM_TWILIGHT2:
			skill_am_twilight_sub(sd,547,200);
			break;
		case AM_TWILIGHT3:
			skill_am_twilight_sub(sd,970,100);
			skill_am_twilight_sub(sd,7135,50);
			skill_am_twilight_sub(sd,7136,50);
			break;
	}

	return 1;
}

void skill_arrow_create(struct map_session_data *sd, int nameid)
{
	int i, j, flag, idx;
	struct item tmp_item;

	nullpo_retv(sd);

	if(nameid <= 0)
		return;

	for(idx = 0; idx < MAX_SKILL_ARROW_DB; idx++) {
		if (nameid == skill_arrow_db[idx].nameid)
			break;
	}
	if (idx == MAX_SKILL_ARROW_DB)
		return;

	if ((j = pc_search_inventory(sd, nameid)) < 0 || sd->status.inventory[j].equip)
		return;

	pc_delitem(sd,j,1,0,1);
	for(i=0;i<5;i++) {
		memset(&tmp_item,0,sizeof(tmp_item));
		tmp_item.nameid = skill_arrow_db[idx].cre_id[i];
		if (tmp_item.nameid <= 0)
			continue;
		tmp_item.amount = skill_arrow_db[idx].cre_amount[i];
		if (tmp_item.amount <= 0)
			continue;
		tmp_item.identify = 1;
		if(battle_config.making_arrow_name_input) {
			tmp_item.card[0]=0x00fe;
			tmp_item.card[1]=0;
			*((int *)(&tmp_item.card[2]))=sd->status.char_id;	/* キャラID */
		}
		if((flag = pc_additem(sd,&tmp_item,tmp_item.amount))) {
			clif_additem(sd,0,0,flag);
			map_addflooritem(&tmp_item,tmp_item.amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
		}
	}

	return;
}

/*==========================================
 * 武器修理
 *------------------------------------------
 */
void skill_repair_weapon(struct map_session_data *sd, int idx)
{
	const int material[5] = { 999, 1002, 998, 999, 756 };	// 鋼鉄・鉄鉱石・鉄・鋼鉄・オリデオコン原石
	int itemid, n;
	int skillid = BS_REPAIRWEAPON;
	struct map_session_data *dstsd;
	struct item_data *data;

	nullpo_retv(sd);

	if(idx == 0xffff || idx < 0 || idx >= MAX_INVENTORY)	// cencel or invalid range
		return;

	dstsd = map_id2sd(sd->skill_menu.val);
	if(!dstsd || dstsd->status.inventory[idx].nameid <= 0 || dstsd->status.inventory[idx].attribute == 0) {
		clif_skill_fail(sd,skillid,0,0,0);
		return;
	}

	if(sd != dstsd) {	// 対象が自分でないなら射程チェック
		int range = skill_get_fixed_range(&sd->bl,skillid,1);
		if(!battle_check_range(&sd->bl, &dstsd->bl, range+1)) {
			clif_item_repaireffect(sd, 1, dstsd->status.inventory[idx].nameid);
			return;
		}
	}

	data = dstsd->inventory_data[idx];

	if(data && itemdb_isweapon(data->nameid)) {	// 武器
		if(data->wlv >= 1 && data->wlv <= 4)
			itemid = material[data->wlv];
		else
			itemid = material[4];		// 武器Lvが5以上ならLv4と同じ材料にしておく
	} else {			// 防具
		itemid = material[0];
	}

	if((n = pc_search_inventory(sd, itemid)) < 0) {
		clif_item_repaireffect(sd, 1, dstsd->status.inventory[idx].nameid);
	} else {
		clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,1,1);
		pc_delitem(sd,n,1,0,1);
		dstsd->status.inventory[idx].attribute = 0;
		clif_delitem(dstsd, 1, idx, 1);
		clif_additem(dstsd, idx, 1, 0);
		clif_item_repaireffect(sd, 0, dstsd->status.inventory[idx].nameid);
	}

	return;
}

/*==========================================
 * ポイズニングウェポン
 *------------------------------------------
 */
void skill_poisoning_weapon(struct map_session_data *sd, int nameid)
{
	static const int poison[] = {
		12717, 12718, 12719, 12720, 12721, 12722, 12723, 12724
	};
	static const int type[] = {
		SC_PARALIZE, SC_LEECHEND, SC_OBLIVIONCURSE, SC_DEATHHURT, SC_TOXIN, SC_PYREXIA, SC_MAGICMUSHROOM, SC_VENOMBLEED
	};

	nullpo_retv(sd);

	if(nameid > 0) {
		int i;
		for(i = 0; i < sizeof(poison)/sizeof(poison[0]); i++) {
			if(poison[i] == nameid) {
				int j = pc_search_inventory(sd, nameid);
				if (j >= 0) {
					pc_delitem(sd,j,1,0,1);
					if(sd->sc.data[SC_POISONINGWEAPON].timer != -1)
						status_change_end(&sd->bl,SC_POISONINGWEAPON,-1);
					status_change_start(&sd->bl,SC_POISONINGWEAPON,sd->skill_menu.lv,type[i],0,0,skill_get_time(GC_POISONINGWEAPON,sd->skill_menu.lv),0);
				}
				break;
			}
		}
	}

	return;
}

/*==========================================
 * リーディングスペルブック
 *------------------------------------------
 */
void skill_reading_sb(struct map_session_data *sd, int nameid)
{
	static const int book[] = {
		6189, 6190, 6191, 6192, 6193, 6194,
		6195, 6196,	6197, 6198,	6199, 6200,
		6201, 6202, 6203, 6204, 6205
	};
	static const int spell[] = {
		MG_FIREBOLT, MG_COLDBOLT, MG_LIGHTNINGBOLT, WZ_STORMGUST, WZ_VERMILION, WZ_METEOR,
		WL_COMET, WL_TETRAVORTEX, MG_THUNDERSTORM, WZ_JUPITEL, WZ_WATERBALL, WZ_HEAVENDRIVE,
		WZ_EARTHSPIKE, WL_EARTHSTRAIN, WL_CHAINLIGHTNING, WL_CRIMSONROCK, WL_DRAINLIFE
	};

	nullpo_retv(sd);

	if(nameid > 0) {
		int i;
		for(i = 0; i < sizeof(book)/sizeof(book[0]); i++) {
			if(book[i] == nameid) {
				if(pc_search_inventory(sd, nameid) >= 0) {
					int j, slot;

					/* スキルの習得チェック */
					if(pc_checkskill(sd,spell[i]) <= 0) {
						clif_skill_fail(sd,WL_READING_SB,0x34,0,0);
						break;
					}

					slot = skill_get_spellslot(spell[i]);

					/* スロットの上限チェック */
					if(sd->freeze_sp_slot + slot > 4 + pc_checkskill(sd,WL_FREEZE_SP) * 4 + sd->status.base_level/10 + sd->status.int_/10) {
						clif_skill_fail(sd,WL_READING_SB,0x35,0,0);
						break;
					}

					/* 保持スペルの空きチェック */
					for(j = 0; j < MAX_FREEZE_SPELL; j++) {
						if(sd->freeze_sp_skill[j] == 0) {
							sd->freeze_sp_slot += slot;
							sd->freeze_sp_skill[j] = spell[i];
							status_change_start(&sd->bl,SC_SPELLBOOK,0,0,0,0,10000,0);
							break;
						}
					}
				}
				break;
			}
		}
	}

	return;
}

/*==========================================
 * FAW マジックデコイ
 *------------------------------------------
 */
void skill_magicdecoy(struct map_session_data *sd, int nameid)
{
	static const int element[] = {
		990, 991, 992, 993,
	};
	static const int mob_id[] = {
		2043, 2044, 2046, 2045,
	};

	nullpo_retv(sd);

	if(nameid > 0) {
		int i;
		for(i = 0; i < sizeof(element)/sizeof(element[0]); i++) {
			if(element[i] == nameid) {
				int j = pc_search_inventory(sd, nameid);
				if (j >= 0) {
					int x = sd->skill_menu.val>>16;		// X座標は上位バイト
					int y = sd->skill_menu.val&0xffff;	// Y座標は下位バイト
					int id;
					struct mob_data *md = NULL;

					pc_delitem(sd,j,1,0,1);
					id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, mob_id[i], 1, "");

					if((md = map_id2md(id)) != NULL) {
						md->master_id = sd->bl.id;
						md->guild_id  = status_get_guild_id(&sd->bl);
						md->deletetimer  = add_timer(gettick()+skill_get_time(NC_MAGICDECOY,sd->skill_menu.lv),mob_timer_delete,id,NULL);
						md->state.nodrop = battle_config.cannibalize_no_drop;
						md->state.noexp  = battle_config.cannibalize_no_exp;
						md->state.nomvp  = battle_config.cannibalize_no_mvp;
						md->state.special_mob_ai = 1;
					}
					break;
				}
			}
		}
	}

	return;
}

/*==========================================
 * オートシャドウスペル
 *------------------------------------------
 */
void skill_autoshadowspell(struct map_session_data *sd, int skillid)
{
	int skilllv;

	nullpo_retv(sd);

	if(skillid >= THIRD_SKILLID)	// 不正対策
		return;

	if((skilllv = pc_checkskill(sd,skillid)) > 0) {
		/* シャドウオートスペルの使用時レベルでオートスペルのレベルが決定 */
		int shadowlv = (sd->skill_menu.lv + 1) / 2;

		skilllv = (skilllv > shadowlv)? shadowlv: skilllv;
		status_change_start(&sd->bl,SC__AUTOSHADOWSPELL,sd->skill_menu.lv,skillid,skilllv,0,skill_get_time(SC_AUTOSHADOWSPELL,sd->skill_menu.lv),0);
	}

	return;
}

/*==========================================
 * チェンジマテリアル
 *------------------------------------------
 */
void skill_changematerial(struct map_session_data *sd, int num, unsigned short *item_list)
{
	int i, j, k;
	int nameid, amount, flag;
	struct item tmp_item;

	nullpo_retv(sd);
	nullpo_retv(item_list);

	if(num <= 0)
		return;

	for(i = 0; i < MAX_SKILL_PRODUCE_DB; i++) {
		struct skill_material_db *mdb = &skill_material_db[i];
		int c = 0;
		int m = 0;

		if(mdb->nameid == 0)
			break;

		for(j = 0; j < MAX_PRODUCE_RESOURCE; j++) {
			if(mdb->mat_id[j] == 0)
				break;

			for(k = 0; k < num; k++) {
				int idx = item_list[k * 2] - 2;
				if(idx < 0 || idx >= MAX_INVENTORY) {
					// anti hacker
					continue;
				}
				nameid = sd->status.inventory[idx].nameid;
				amount = item_list[k * 2 + 1];
				if(amount <= 0)
					continue;

				if(nameid == mdb->mat_id[j] && amount % mdb->mat_amount[j] == 0) {
					if(m != 0) {
						if(amount / mdb->mat_amount[j] != m)
							break;
					} else {
						m = amount / mdb->mat_amount[j];
					}
					c++;
				}
			}
		}

		if(j == num && c == num) {
			for(k = 0; k < num; k++) {
				int idx = item_list[k * 2] - 2;
				if(idx < 0 || idx >= MAX_INVENTORY) {
					// anti hacker
					continue;
				}
				pc_delitem(sd, idx, item_list[k * 2 + 1], 0, 1);	// アイテム消費
			}
			memset(&tmp_item, 0, sizeof(tmp_item));
			tmp_item.nameid = mdb->nameid;
			tmp_item.amount = mdb->amount[0] * m;
			if(mdb->amount[1] > mdb->amount[0]) {
				tmp_item.amount += atn_rand() % (mdb->amount[1] * m - mdb->amount[0] * m + 1);
			}
			tmp_item.identify = 1;
			if((flag = pc_additem(sd, &tmp_item, tmp_item.amount))) {
				clif_additem(sd, 0, 0, flag);
				map_addflooritem(&tmp_item, tmp_item.amount, sd->bl.m, sd->bl.x, sd->bl.y, 0, 0, 0, 0);
			}
			clif_skill_message(sd, GN_CHANGEMATERIAL, 1574);	// 成功しました。
			return;
		}
	}

	clif_skill_message(sd, GN_CHANGEMATERIAL, 1575);	// 失敗しました。

	return;
}

/*==========================================
 * エレメンタルアナライシス
 *------------------------------------------
 */
void skill_el_analysis(struct map_session_data *sd, int num, int skilllv, unsigned short *item_list)
{
	int i, nameid, amount, result, addnum, flag;
	struct item tmp_item;

	nullpo_retv(sd);
	nullpo_retv(item_list);

	if(num <= 0) {
		clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
		return;
	}

	for(i = 0; i < num; i++) {
		int idx = item_list[i * 2] - 2;
		if(idx < 0 || idx >= MAX_INVENTORY) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
			return;
		}
		nameid = sd->status.inventory[idx].nameid;
		amount = item_list[i * 2 + 1];
		if(amount <= 0) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
			return;
		}

		switch(nameid) {
			case 994: result = 990; break;	// フレイムハート > レッドブラッド
			case 995: result = 991; break;	// ミスティックフローズン > クリスタルブルー
			case 996: result = 992; break;	// ラフウィンド > ウィンドオブヴェルデュール
			case 997: result = 993; break;	// グレイトネイチャ > イエローライブ
			case 990: result = 994; break;	// レッドブラッド > フレイムハート
			case 991: result = 995; break;	// クリスタルブルー > ミスティックフローズン
			case 992: result = 996; break;	// ウィンドオブヴェルデュール > ラフウィンド
			case 993: result = 997; break;	// イエローライブ > グレイトネイチャ
			default:
				clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
				return;
		}

		switch(skilllv) {
			case 1:		// エレメンタルアナライシス Lv1
				addnum = amount * (atn_rand()%5 + 5);
				break;
			case 2:		// エレメンタルアナライシス Lv2
				addnum = amount / 10;
				break;
			default:
				clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
				return;
		}

		if(addnum <= 0) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// 失敗しました。
			return;
		}

		pc_delitem(sd, idx, amount, 0, 1);	// アイテム消費

		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid = result;
		tmp_item.amount = addnum;
		tmp_item.identify = 1;
		if((flag = pc_additem(sd, &tmp_item, tmp_item.amount))) {
			clif_additem(sd, 0, 0, flag);
			map_addflooritem(&tmp_item, tmp_item.amount, sd->bl.m, sd->bl.x, sd->bl.y, 0, 0, 0, 0);
		}
	}

	clif_skill_message(sd, SO_EL_ANALYSIS, 1574);	// 成功しました。

	return;
}

/*==========================================
 * フリージングスペルで使用するスキルのスロット数を取得
 *------------------------------------------
 */
static int skill_get_spellslot(int skillid)
{
	int slot = 0;

	switch(skillid) {
		case MG_FIREBOLT:		// ファイアーボルト
		case MG_COLDBOLT:		// コールドボルト
		case MG_LIGHTNINGBOLT:	// ライトニングボルト
			slot = 7;
			break;
		case WZ_EARTHSPIKE:		// アーススパイク
		case WL_DRAINLIFE:		// ドレインライフ
			slot = 8;
			break;
		case MG_THUNDERSTORM:	// サンダーストーム
		case WZ_JUPITEL:		// ユピテルサンダー
		case WZ_WATERBALL:		// ウォーターボール
		case WZ_HEAVENDRIVE:	// ヘヴンズドライブ
			slot = 9;
			break;
		case WZ_STORMGUST:		// ストームガスト
		case WZ_VERMILION:		// ロードオブヴァーミリオン
		case WZ_METEOR:			// メテオストーム
			slot = 10;
			break;
		case WL_EARTHSTRAIN:	// アースストレイン
		case WL_CHAINLIGHTNING:	// チェーンライトニング
		case WL_CRIMSONROCK:	// クリムゾンロック
			slot = 12;
			break;
		case WL_COMET:			// コメット
		case WL_TETRAVORTEX:	// テトラボルテックス
			slot = 22;
			break;
	}

	return slot;
}

/*==========================================
 * 武器精錬
 *------------------------------------------
 */
void skill_weapon_refine(struct map_session_data *sd, int idx)
{
	const int refine_item[5] = { 0, 1010, 1011, 984, 984 };
	int skilllv,wlv,n;

	nullpo_retv(sd);

	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	skilllv = pc_checkskill(sd,WS_WEAPONREFINE);

	wlv = itemdb_wlv(sd->status.inventory[idx].nameid);

	// 不正チェック
	if( wlv <= 0 ||
	    sd->status.inventory[idx].nameid <= 0 ||
	    sd->status.inventory[idx].identify != 1 ||
	    !sd->inventory_data[idx]->refine )
		return;
	if(sd->status.inventory[idx].refine >= skilllv){
		clif_weapon_refine_res(sd,2,sd->status.inventory[idx].nameid);
		return;
	}

	if(wlv > 4)	// 武器Lv5以上はLv4と同じとみなす
		wlv = 4;

	// アイテムチェック
	n = pc_search_inventory(sd,refine_item[wlv]);
	if(n < 0) {
		clif_weapon_refine_res(sd,3,refine_item[wlv]);
		return;
	}

	if(atn_rand()%1000 < status_percentrefinery_weaponrefine(sd,&sd->status.inventory[idx])) {
		// 成功
		clif_weapon_refine_res(sd,0,sd->status.inventory[idx].nameid);
		skill_success_weaponrefine(sd,idx);
	} else {
		// 失敗
		clif_weapon_refine_res(sd,1,sd->status.inventory[idx].nameid);
		skill_fail_weaponrefine(sd,idx);
	}

	// アイテム消費
	pc_delitem(sd,n,1,0,1);

	return;
}

/*==========================================
 * 武器精錬成功
 *------------------------------------------
 */
int skill_success_weaponrefine(struct map_session_data *sd,int idx)
{
	nullpo_retr(0, sd);

	if(idx < 0)
		return 0;

	sd->status.inventory[idx].refine++;
	if(sd->status.inventory[idx].refine > MAX_REFINE)
		sd->status.inventory[idx].refine = MAX_REFINE;

	clif_refine(sd->fd,0,idx,sd->status.inventory[idx].refine);
	clif_misceffect(&sd->bl,3);

	// ブラックスミス 名声値
	if(sd->status.inventory[idx].refine==MAX_REFINE && (*((int *)(&sd->status.inventory[idx].card[2]))) == sd->status.char_id)
	{
		switch(itemdb_wlv(sd->status.inventory[idx].nameid))
		{
			case 1:
				ranking_gain_point(sd,RK_BLACKSMITH,1);
				ranking_setglobalreg(sd,RK_BLACKSMITH);
				ranking_update(sd,RK_BLACKSMITH);
				break;
			case 2:
				ranking_gain_point(sd,RK_BLACKSMITH,25);
				ranking_setglobalreg(sd,RK_BLACKSMITH);
				ranking_update(sd,RK_BLACKSMITH);
				break;
			case 3:
				ranking_gain_point(sd,RK_BLACKSMITH,1000);
				ranking_setglobalreg(sd,RK_BLACKSMITH);
				ranking_update(sd,RK_BLACKSMITH);
				break;
			default:
				break;
		};
	}

	return 0;
}

/*==========================================
 * 武器精錬失敗
 *------------------------------------------
 */
int skill_fail_weaponrefine(struct map_session_data *sd,int idx)
{
	nullpo_retr(0, sd);

	if(idx < 0)
		return 0;

	sd->status.inventory[idx].refine = 0;
	pc_delitem(sd,idx,1,0,2);
	// 精錬失敗エフェクトのパケット
	clif_refine(sd->fd,1,idx,sd->status.inventory[idx].refine);
	// 他の人にも失敗を通知
	clif_misceffect(&sd->bl,2);

	return 0;
}

/*==========================================
 * 貪欲
 *------------------------------------------
 */
static int skill_greed( struct block_list *bl,va_list ap )
{
	struct map_session_data *sd;
	struct flooritem_data *fitem;
	struct party *p;

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = va_arg(ap,struct map_session_data *));
	nullpo_retr(0, fitem = (struct flooritem_data *)bl);

	p = va_arg(ap,struct party *);

	pc_takeitem_sub(p, sd, fitem);
	return 0;
}

/*==========================================
 * 寸勁
 *------------------------------------------
 */
static int skill_balkyoung( struct block_list *bl,va_list ap )
{
	struct block_list *src;
	struct block_list *tbl;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, tbl = va_arg(ap,struct block_list *));

	if(!(bl->type & (BL_CHAR | BL_SKILL)))
		return 0;

	// 本人には適用しない?
	if(bl->id == tbl->id)
		return 0;
	if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
		return 0;

	skill_blown(src,bl,4);	// 吹き飛ばしてみる
	if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,7000,status_get_lv(src)))
		status_change_pretimer(bl,SC_STUN,1,0,0,0,5000,0,gettick()+status_get_amotion(src));

	return 0;
}

/*==========================================
 * チェーンライトニング連鎖対象
 *------------------------------------------
 */
static int skill_chainlightning( struct block_list *bl,va_list ap )
{
	struct block_list *src;
	struct block_list **tbl;
	int tid;
	int *c;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	tid = va_arg(ap,int);
	tbl = va_arg(ap,struct block_list **);
	c   = va_arg(ap,int *);

	// 同じ相手の場合は無視
	if(bl->id == tid)
		return 0;

	if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
		return 0;

	if(atn_rand()%1000 < 1000/(++(*c)))
		*tbl = bl;

	return 1;
}

/*==========================================
 * デトネイター
 *------------------------------------------
 */
static int skill_detonator( struct block_list *bl, va_list ap )
{
	int ar, sec;
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	// 自分が設置したトラップのみ
	if(sg->src_id != src->id)
		return 0;

	switch(sg->unit_id)
	{
		case UNT_BLASTMINE:
		case UNT_SANDMAN:
		case UNT_FLASHER:
		case UNT_CLAYMORETRAP:
		case UNT_CLUSTERBOMB:
		case UNT_FIRINGTRAP:
		case UNT_ICEBOUNDTRAP:
			ar = unit->range;

			// サンドマンとクレイモアは効果範囲を1セル広げる
			if(sg->unit_id == UNT_SANDMAN || sg->unit_id == UNT_CLAYMORETRAP || sg->unit_id == UNT_FIRINGTRAP || sg->unit_id == UNT_ICEBOUNDTRAP){
				ar += 1;
			}

			// クラスターボムは効果範囲を3セル広げる
			if(sg->unit_id == UNT_CLUSTERBOMB) {
				ar += 3;
			}

			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: ((sg->unit_id == UNT_CLUSTERBOMB)? 1000: 1500);

			// 罠を発動させる
			map_foreachinarea(skill_trap_splash,unit->bl.m,
						unit->bl.x-ar,unit->bl.y-ar,
						unit->bl.x+ar,unit->bl.y+ar,
						(BL_CHAR|BL_SKILL),unit,sg->tick,1);

			// 起動した罠の後処理
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(gettick(),sg->tick) + sec;
			break;

		case UNT_TALKIEBOX:
			if(sg->val2 == 0) {
				clif_talkiebox(bl,sg->valstr);
				sg->unit_id = UNT_USED_TRAPS;
				clif_changelook(bl,LOOK_BASE,sg->unit_id);
				sg->limit = DIFF_TICK(gettick(),sg->tick) + 5000;
				sg->val2  = -1; // 踏んだ
			}
			break;
	}
	return 0;
}

/*==========================================
 * メイルストーム
 *------------------------------------------
 */
static int skill_maelstrom( struct block_list *bl, va_list ap )
{
	int skilllv;
	int *alive, *flag;
	struct skill_unit *unit;
	struct block_list *src;
	struct map_session_data *src_sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, unit = (struct skill_unit *)bl);

	skilllv = va_arg(ap,int);
	alive   = va_arg(ap,int *);
	flag    = va_arg(ap,int *);
	src     = map_id2bl(unit->group->src_id);

	/* 範囲内にメイルストームが存在するか？ */
	if(src && unit->group->skill_id == SC_MAELSTROM) {
		int ar = skill_get_unit_range(unit->group->skill_id, unit->group->skill_lv);
		/* 範囲内に使用者が存在するか */
		if((src->m == bl->m) && (src->x >= bl->x-ar) && (src->x <= bl->x+ar) && (src->y >= bl->y-ar) && (src->y <= bl->y+ar)) {
			(*alive)=0;

			/* 使用者がPCの場合 */
			if((*flag) && src->type == BL_PC && (src_sd = (struct map_session_data *)src)) {
				int sp = unit->group->skill_lv * skilllv + (src_sd->status.job_level / 5);
				if(src_sd->status.sp + sp > src_sd->status.max_sp)
					sp = src_sd->status.max_sp - src_sd->status.sp;
				if(sp) {
					clif_heal(src_sd->fd,SP_SP,sp);
					pc_heal(src_sd,0,sp);
				}
				(*flag)=0;
			}
		}
	}

	return 0;
}

/*==========================================
 * トランプル
 *------------------------------------------
 */
static int skill_trample( struct block_list *bl, va_list ap )
{
	int ar, skilllv, sec;
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	skilllv = va_arg(ap,int);

	if(atn_rand()%100 >= 25 + skilllv * 25)
		return 0;

	if(!(skill_get_inf2(sg->skill_id)&INF2_TRAP))
		return 0;

	switch(sg->unit_id)
	{
		case UNT_BLASTMINE:
		case UNT_SANDMAN:
		case UNT_FLASHER:
		case UNT_CLAYMORETRAP:
		case UNT_CLUSTERBOMB:
		case UNT_FIRINGTRAP:
		case UNT_ICEBOUNDTRAP:
			ar = unit->range;

			// サンドマンとクレイモアは効果範囲を1セル広げる
			if(sg->unit_id == UNT_SANDMAN || sg->unit_id == UNT_CLAYMORETRAP || sg->unit_id == UNT_FIRINGTRAP || sg->unit_id == UNT_ICEBOUNDTRAP){
				ar += 1;
			}

			// クラスターボムは効果範囲を3セル広げる
			if(sg->unit_id == UNT_CLUSTERBOMB) {
				ar += 3;
			}

			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: ((sg->unit_id == UNT_CLUSTERBOMB)? 1000: 1500);

			// 罠を発動させる
			map_foreachinarea(skill_trap_splash,unit->bl.m,
						unit->bl.x-ar,unit->bl.y-ar,
						unit->bl.x+ar,unit->bl.y+ar,
						(BL_CHAR|BL_SKILL),unit,sg->tick,1);

			// 起動した罠の後処理
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(gettick(),sg->tick) + sec;
			break;

		case UNT_TALKIEBOX:
			if(sg->val2 == 0) {
				clif_talkiebox(bl,sg->valstr);
				sg->unit_id = UNT_USED_TRAPS;
				clif_changelook(bl,LOOK_BASE,sg->unit_id);
				sg->limit = DIFF_TICK(gettick(),sg->tick) + 5000;
				sg->val2  = -1; // 踏んだ
			}
			break;
		default:
			skill_delunit(unit);
			break;
	}
	return 0;
}

/*==========================================
 * ドミニオンインパルス
 *------------------------------------------
 */
static int skill_dominion_impulse( struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;
	struct skill_unit_group *sg;

	nullpo_retr(0, bl);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	if(sg->unit_id == UNT_REVERBERATION) {
		unsigned int tick = gettick();
		int splash_count = map_foreachinarea(skill_count_target,bl->m,
			bl->x-2,bl->y-2,bl->x+2,bl->y+2,
			(BL_CHAR|BL_SKILL),bl);
		map_foreachinarea(skill_trap_splash,
			bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,
			(BL_CHAR|BL_SKILL),bl,tick,splash_count);
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(bl,LOOK_BASE,sg->unit_id);
		sg->limit = unit->limit = DIFF_TICK(tick,sg->tick)+1500;
	}

	return 0;
}

/*==========================================
 * ファイアーエクスパンション
 *------------------------------------------
 */
static int skill_fire_expansion( struct block_list *bl, va_list ap )
{
	int skilllv;
	unsigned int tick;
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;

	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, bl);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	skilllv = va_arg(ap,int);
	tick = va_arg(ap,unsigned int);

	if(sg->src_id != src->id)
		return 0;

	if(sg->unit_id == UNT_DEMONIC_FIRE && sg->val2 == 0) {
		switch(skilllv) {
		case 1:		// 油
			sg->val2 = 1;
			sg->limit = unit->limit += 10000;
			break;
		case 2:		// 爆発
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
				src,sg->skill_id,sg->skill_lv,tick,(0x0f<<20)|BCT_ENEMY|2,
				skill_castend_damage_id);
			skill_delunitgroup(sg);
			break;
		case 3:		// 煙幕
			sg->unit_id = UNT_FIRE_EXPANSION_SMOKE_POWDER;
			sg->target_flag = skill_get_unit_target(GN_FIRE_EXPANSION_SMOKE_POWDER);
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			break;
		case 4:		// 催涙ガス
			sg->unit_id = UNT_FIRE_EXPANSION_TEAR_GAS;
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			break;
		case 5:		// 塩酸
			{
				int acidlv = 1;
				if(src->type == BL_PC) {
					struct map_session_data *sd = (struct map_session_data *)src;
					acidlv = pc_checkskill(sd,CR_ACIDDEMONSTRATION);
					acidlv = (acidlv < 1)? 1: acidlv;
				}
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
					src,GN_FIRE_EXPANSION_ACID,acidlv,tick,(0x0f<<20)|BCT_ENEMY|0x0800,
					skill_castend_damage_id);
			}
			skill_delunitgroup(sg);
			break;
		}
	}

	return 0;
}

/*==========================================
 * キャスリングのターゲット変更
 *------------------------------------------
 */
static int skill_castle_mob_changetarget(struct block_list *bl,va_list ap)
{
	struct mob_data* md;
	struct block_list *from_bl;
	struct block_list *to_bl;

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data*)bl);
	nullpo_retr(0, from_bl = va_arg(ap,struct block_list *));
	nullpo_retr(0, to_bl = va_arg(ap,struct block_list *));

	if(md->target_id == from_bl->id)
		md->target_id = to_bl->id;
	return 0;
}

/*==========================================
 * クローンスキル
 *------------------------------------------
 */
int skill_clone(struct map_session_data* sd,int skillid,int skilllv)
{
	nullpo_retr(0, sd);

	if(skillid <= 0 || skilllv <= 0)
		return 0;
	// 高レベルを取得している
	if(pc_checkskill(sd,skillid) >= skilllv)
		return 0;

	// 取得可能スキルか？
	if(skill_get_cloneable(skillid)&(1<<sd->s_class.upper))
	{
		int cloneskilllv;
		// サンクチュアリを受けた場合、同Lvのヒールをクローン
		if(skillid == PR_SANCTUARY)
		{
			skillid = AL_HEAL;
			if(pc_checkskill(sd,skillid) >= skilllv)
				return 0;
		}
		cloneskilllv = pc_checkskill(sd,RG_PLAGIARISM);
		sd->skill_clone.id = skillid;
		sd->skill_clone.lv = (skilllv > cloneskilllv)? cloneskilllv: skilllv;
		clif_skillinfoblock(sd);
		return 1;
	}
	return 0;
}

/*==========================================
 * リプロデュース
 *------------------------------------------
 */
int skill_reproduce(struct map_session_data* sd,int skillid,int skilllv)
{
	nullpo_retr(0, sd);

	if(skillid <= 0 || skilllv <= 0)
		return 0;

	// サブスキルの場合はメインに置き換え
	switch(skillid) {
		case AB_DUPLELIGHT_MELEE:	// デュプレライト(物理)
		case AB_DUPLELIGHT_MAGIC:	// デュプレライト(魔法)
			skillid = AB_DUPLELIGHT;
			break;
		case WL_CHAINLIGHTNING_ATK:	// チェーンライトニング(連鎖)
			skillid = WL_CHAINLIGHTNING;
			break;
		case WL_TETRAVORTEX_FIRE:	// テトラボルテックス(火)
		case WL_TETRAVORTEX_WATER:	// テトラボルテックス(水)
		case WL_TETRAVORTEX_WIND:	// テトラボルテックス(風)
		case WL_TETRAVORTEX_GROUND:	// テトラボルテックス(地)
			skillid = WL_TETRAVORTEX;
			break;
		case WL_SUMMON_ATK_FIRE:	// サモンファイアボール(攻撃)
			skillid = WL_SUMMONFB;
			break;
		case WL_SUMMON_ATK_WIND:	// サモンボールライトニング(攻撃)
			skillid = WL_SUMMONBL;
			break;
		case WL_SUMMON_ATK_WATER:	// サモンウォーターボール(攻撃)
			skillid = WL_SUMMONWB;
			break;
		case WL_SUMMON_ATK_GROUND:	// サモンストーン(攻撃)
			skillid = WL_SUMMONSTONE;
			break;
		case LG_OVERBRAND_BRANDISH:	// オーバーブランド(薙ぎ)
		case LG_OVERBRAND_PLUSATK:	// オーバーブランド(追撃)
			skillid = LG_OVERBRAND;
			break;
		case WM_REVERBERATION_MELEE:	// 振動残響(物理)
		case WM_REVERBERATION_MAGIC:	// 振動残響(魔法)
			skillid = WM_REVERBERATION;
			break;
		case WM_SEVERE_RAINSTORM_MELEE:	// シビアレインストーム(攻撃)
			skillid = WM_SEVERE_RAINSTORM;
			break;
		case GN_CRAZYWEED_ATK:	// クレイジーウィード(攻撃)
			skillid = GN_CRAZYWEED;
			break;
		case GN_FIRE_EXPANSION_SMOKE_POWDER:	// ファイアーエクスパンション(煙幕)
		case GN_FIRE_EXPANSION_TEAR_GAS:		// ファイアーエクスパンション(催涙ガス)
		case GN_FIRE_EXPANSION_ACID:			// ファイアーエクスパンション(塩酸)
			skillid = GN_FIRE_EXPANSION;
			break;
		case GN_HELLS_PLANT_ATK:	// ヘルズプラント(攻撃)
			skillid = GN_HELLS_PLANT;
			break;
		case GN_SLINGITEM_RANGEMELEEATK:	// スリングアイテム(遠距離攻撃)
			skillid = GN_SLINGITEM;
			break;
		case NC_MAGMA_ERUPTION_DOTDAMAGE:	// マグマイラプション
			skillid = NC_MAGMA_ERUPTION;
			break;
	}

	// 高レベルを取得している
	if(pc_checkskill(sd,skillid) >= skilllv)
		return 0;

	if(sd->sc.data[SC__REPRODUCE].timer != -1) {
		// 取得可能スキルか？
		if((skill_get_cloneable(skillid)&(1<<(sd->s_class.upper))) || (skill_get_cloneable(skillid)&0x08))
		{
			int reproducelv = sd->sc.data[SC__REPRODUCE].val1;
			sd->skill_reproduce.id = skillid;
			// スキルレベルはリプロデュースのレベルで習得
			sd->skill_reproduce.lv = (reproducelv > skill_get_max(skillid))? skill_get_max(skillid): reproducelv;
			clif_skillinfoblock(sd);
			return 1;
		}
	}
	return 0;
}

/*==========================================
 * 回復量補正
 *------------------------------------------
 */
int skill_fix_heal(struct block_list *src, struct block_list *bl, int skill_id, int heal)
{
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change *sc = NULL, *tsc = NULL;
	int i, skill = 0, rate = 0;

	nullpo_retr(0, src);

	sc = status_get_sc(src);
	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;
	if(bl){
		tsc = status_get_sc(bl);
		if(bl->type == BL_PC)
			tsd = (struct map_session_data *)bl;
	}

	if(tsc && tsc->data[SC_CRITICALWOUND].timer != -1)
		heal = heal * (100 - tsc->data[SC_CRITICALWOUND].val1 * 10) / 100;
	if(tsc && tsc->data[SC_DEATHHURT].timer != -1)
		heal = heal * (100 - tsc->data[SC_DEATHHURT].val2) / 100;

	if(sc && sc->data[SC_OFFERTORIUM].timer != -1)
		rate += sc->data[SC_OFFERTORIUM].val1 * 30;

	if(sd) {
		if(sd->skill_healup.count > 0 && heal > 0 && skill_id > 0) {
			for(i = 0; i < sd->skill_healup.count; i++) {
				if(skill_id == sd->skill_healup.id[i]) {
					rate += sd->skill_healup.rate[i];
					break;
				}
			}
		}

		// メディタティオ
		skill += pc_checkskill(sd,HP_MEDITATIO) * 2;
		// 海の力
		skill += pc_checkskill(sd,SU_POWEROFSEA)>0? 50: 0;
		// 海の魂(新鮮なエビ)
		if(skill_id == SU_FRESHSHRIMP && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)
			skill += 30;
	}

#ifndef PRE_RENEWAL
	if(skill > 0)
		rate += skill;
#endif

	if(rate > 0)
		heal += heal * rate / 100;

#ifndef PRE_RENEWAL
	// Matkの加算
	if(skill_id == AL_HEAL || skill_id == AB_CHEAL || skill_id == AB_HIGHNESSHEAL)
		heal += battle_calc_base_magic_damage(src);
#endif

	if(tsd && tsd->skill_subhealup.count > 0 && heal > 0 && skill_id > 0) {
		for(i = 0; i < tsd->skill_subhealup.count; i++) {
			if(skill_id == tsd->skill_subhealup.id[i]) {
				heal += heal * tsd->skill_subhealup.rate[i] / 100;
				break;
			}
		}
	}

#ifdef PRE_RENEWAL
	if(skill > 0)	// メディタティオ
		heal += heal * skill / 100;
#endif

	return heal;
}

/*----------------------------------------------------------------------------
 * 初期化系
 */

/*==========================================
 * 文字列処理
 *   ',' で区切ってvalに戻す
 *------------------------------------------
 */
static int skill_split_str(char *str,char **val,int num)
{
	int i;

	for (i=0; i<num && str; i++){
		val[i] = str;
		str = strchr(str,',');
		if (str)
			*str++=0;
	}
	return i;
}

/*==========================================
 * 文字列処理
 *   ':' で区切ってatoiしてvalに戻す
 *------------------------------------------
 */
static int skill_split_atoi(char *str,int *val,int num)
{
	int i, max = 0;

	for (i=0; i<num; i++) {
		if (str) {
			val[i] = max = atoi(str);
			str = strchr(str,':');
			if (str)
				*str++=0;
		} else {
			val[i] = max;
		}
	}
	return i;
}

/*==========================================
 * 文字列処理
 *   ':' で区切ってstrtolしてvalに戻す
 *------------------------------------------
 */
static int skill_split_strtol(char *str,int *val,int num,int base)
{
	int i, max = 0;

	for (i=0; i<num; i++) {
		if (str) {
			val[i] = max = strtol(str, NULL, base);
			str = strchr(str,':');
			if (str)
				*str++=0;
		} else {
			val[i] = max;
		}
	}
	return i;
}

/*==========================================
 * スキルユニットの配置情報作成
 *------------------------------------------
 */
static void skill_init_unit_layout(void)
{
	int i,j,pos = 0;

	memset(skill_unit_layout,0,sizeof(skill_unit_layout));
	// 矩形のユニット配置を作成する
	for (i=0; i<=MAX_SQUARE_LAYOUT; i++) {
		int size = i*2+1;
		skill_unit_layout[i].count = size*size;
		for (j=0; j<size*size; j++) {
			skill_unit_layout[i].dx[j] = (j%size-i);
			skill_unit_layout[i].dy[j] = (j/size-i);
		}
	}
	pos = i;
	// 矩形以外のユニット配置を作成する
	for (i=0;i<MAX_SKILL_DB;i++) {
		if (!skill_db[i].unit_id[0] || skill_db[i].unit_layout_type[0] != -1)
			continue;
		switch (skill_db[i].id) {
			case MG_FIREWALL:
			case WZ_ICEWALL:
			case WL_EARTHSTRAIN:
				// ファイアーウォール、アイスウォールは方向で変わるので別処理
				break;
			case PR_SANCTUARY:
			{
				const int dx[] = {
					-1, 0, 1,-2,-1, 0, 1, 2,-2,-1,
					 0, 1, 2,-2,-1, 0, 1, 2,-1, 0, 1};
				const int dy[]={
					-2,-2,-2,-1,-1,-1,-1,-1, 0, 0,
					 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2};
				skill_unit_layout[pos].count = 21;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PR_MAGNUS:
			{
				const int dx[] = {
					-1, 0, 1,-1, 0, 1,-3,-2,-1, 0,
					 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,
					-3,-2,-1, 0, 1, 2, 3,-1, 0, 1,-1, 0, 1};
				const int dy[] = {
					-3,-3,-3,-2,-2,-2,-1,-1,-1,-1,
					-1,-1,-1, 0, 0, 0, 0, 0, 0, 0,
					 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3};
				skill_unit_layout[pos].count = 33;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case WZ_FROSTNOVA:
			{
#ifdef PRE_RENEWAL
				const int dx[] = {
					-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,
					-2,-1, 1, 2,-2,-1, 0, 1, 2,-2,
					-1, 0, 1, 2};
				const int dy[]={
					-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,
					 0, 0, 0, 0, 1, 1, 1, 1, 1, 2,
					 2, 2, 2, 2};
				skill_unit_layout[pos].count = 24;
#else
				const int dx[] = {
					-3,-2,-1, 0, 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,
					-3,-2,-1, 0, 1, 2, 3,-3,-2,-1, 1, 2, 3,-3,
					-2,-1, 0, 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,-3,
					-2,-1, 0, 1, 2, 3};
				const int dy[]={
					-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,
					-1,-1,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 1,
					 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3,
					 3, 3, 3, 3, 3, 3};
				skill_unit_layout[pos].count = 48;
#endif
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case AS_VENOMDUST:
			{
				const int dx[] = {-1, 0, 0, 0, 1};
				const int dy[] = { 0,-1, 0, 1, 0};
				skill_unit_layout[pos].count = 5;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case CR_GRANDCROSS:
			case NPC_GRANDDARKNESS:
			{
				const int dx[] = {
					 0, 0,-1, 0, 1,-2,-1, 0, 1, 2,
					-4,-3,-2,-1, 0, 1, 2, 3, 4,-2,
					-1, 0, 1, 2,-1, 0, 1, 0, 0};
				const int dy[] = {
					-4,-3,-2,-2,-2,-1,-1,-1,-1,-1,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					 1, 1, 1, 1, 2, 2, 2, 3, 4};
				skill_unit_layout[pos].count = 29;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PF_FOGWALL:
			{
				const int dx[] = {
					-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
				const int dy[] = {
					-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
				skill_unit_layout[pos].count = 15;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PA_GOSPEL:
			{
				const int dx[] = {
					-1, 0, 1,-1, 0, 1,-3,-2,-1, 0,
					 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,
					-3,-2,-1, 0, 1, 2, 3,-1, 0, 1,
					-1, 0, 1};
				const int dy[] = {
					-3,-3,-3,-2,-2,-2,-1,-1,-1,-1,
					-1,-1,-1, 0, 0, 0, 0, 0, 0, 0,
					 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
					 3, 3, 3};
				skill_unit_layout[pos].count = 33;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case NJ_TATAMIGAESHI:
			{
				// Lv1（3x3でトータル4セル）
				const int dx1[] = {-1, 1, 0, 0};
				const int dy1[] = { 0, 0,-1, 1};
				// Lv2,3（5x5でトータル8セル）
				const int dx2[] = {-2,-1, 1, 2, 0, 0, 0, 0};
				const int dy2[] = { 0, 0, 0, 0,-2,-1, 1, 2};
				// Lv4,5（7x7でトータル12セル）
				const int dx3[] = {-3,-2,-1, 1, 2, 3, 0, 0, 0, 0, 0, 0};
				const int dy3[] = { 0, 0, 0, 0, 0, 0,-3,-2,-1, 1, 2, 3};
				// Lv1のセット
				j = 0;
				skill_unit_layout[pos].count = 4;
				memcpy(skill_unit_layout[pos].dx,dx1,sizeof(dx1));
				memcpy(skill_unit_layout[pos].dy,dy1,sizeof(dy1));
				skill_db[i].unit_layout_type[j] = pos;
				// Lv2,3のセット
				j++;
				pos++;
				skill_unit_layout[pos].count = 8;
				memcpy(skill_unit_layout[pos].dx,dx2,sizeof(dx2));
				memcpy(skill_unit_layout[pos].dy,dy2,sizeof(dy2));
				skill_db[i].unit_layout_type[j] = pos;
				skill_db[i].unit_layout_type[++j] = pos;
				// Lv4,5のセット
				j++;
				pos++;
				skill_unit_layout[pos].count = 12;
				memcpy(skill_unit_layout[pos].dx,dx3,sizeof(dx3));
				memcpy(skill_unit_layout[pos].dy,dy3,sizeof(dy3));
				skill_db[i].unit_layout_type[j] = pos;
				skill_db[i].unit_layout_type[++j] = pos;
				// Lv6以上は同じtypeで埋める
				for (;j<MAX_SKILL_LEVEL;j++)
					skill_db[i].unit_layout_type[j] = pos;
				pos++;
				continue;	// 既にLv毎にposを設定したので以下の処理は飛ばす
			}
			case NPC_FLAMECROSS:		/* フレイムクロス */
			{
				const int dx[] = {-2,-1, 1, 2, 0, 0, 0, 0};
				const int dy[] = { 0, 0, 0, 0,-2,-1, 1, 2};
				skill_unit_layout[pos].count = 8;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case GN_WALLOFTHORN:		/* ソーンウォール */
			{
				const int dx[] = {
					-2,-1, 0, 1, 2,-2, 2,-2,
					 2,-2, 2,-2,-1, 0, 1, 2,
				};
				const int dy[] = {
					-2,-2,-2,-2,-2,-1,-1, 0,
					 0, 1, 1, 2, 2, 2, 2, 2
				};
				skill_unit_layout[pos].count = 16;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case EL_FIRE_MANTLE:		/* ファイアーマントル */
			{
				const int dx[] = {-1, 0, 1, 1, 1, 0,-1,-1};
				const int dy[] = {-1,-1,-1, 0, 1, 1, 1, 0};
				skill_unit_layout[pos].count = 8;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			default:
				printf("unknown unit layout at skill %d\n",i);
				break;
		}
		if (!skill_unit_layout[pos].count)
			continue;
		for (j=0;j<MAX_SKILL_LEVEL;j++)
			skill_db[i].unit_layout_type[j] = pos;
		pos++;
	}
	// ファイヤーウォール
	firewall_unit_pos = pos;
	for (i=0;i<8;i++) {
		if (i&1) {	/* 斜め配置 */
			skill_unit_layout[pos].count = 5;
			if (i&0x2) {
				int dx[] = {-1,-1, 0, 0, 1};
				int dy[] = { 1, 0, 0,-1,-1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {
				int dx[] = { 1, 1 ,0, 0,-1};
				int dy[] = { 1, 0, 0,-1,-1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		} else {	/* 縦横配置 */
			skill_unit_layout[pos].count = 3;
			if (i%4==0) {	/* 上下 */
				int dx[] = {-1, 0, 1};
				int dy[] = { 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			/* 左右 */
				int dx[] = { 0, 0, 0};
				int dy[] = {-1, 0, 1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
	// アイスウォール
	icewall_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 5;
		if (i&1) {	/* 斜め配置 */
			if (i&0x2) {
				int dx[] = {-2,-1, 0, 1, 2};
				int dy[] = { 2, 1, 0,-1,-2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {
				int dx[] = { 2, 1 ,0,-1,-2};
				int dy[] = { 2, 1, 0,-1,-2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		} else {	/* 縦横配置 */
			if (i%4==0) {	/* 上下 */
				int dx[] = {-2,-1, 0, 1, 2};
				int dy[] = { 0, 0, 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			/* 左右 */
				int dx[] = { 0, 0, 0, 0, 0};
				int dy[] = {-2,-1, 0, 1, 2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
	// アースストレイン
	earthstrain_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 15;
		if (i==2 || i==6) {		/* 	左右 */
			int dx[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			int dy[] = {-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		} else {			/* 上下 */
			int dx[] = {-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7};
			int dy[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		}
		pos++;
	}
}

/*==========================================
 * スキル関係ファイル読み込み
 * skill_db.txt スキルデータ
 * skill_cast_db.txt スキルの詠唱時間とディレイデータ
 * produce_db.txt アイテム作成スキル用データ
 * create_arrow_db.txt 矢作成スキル用データ
 * abra_db.txt アブラカダブラ発動スキルデータ
 *------------------------------------------
 */
static int skill_readdb(void)
{
	int i,j,k,m;
	FILE *fp;
	char line[1024],*p;
#ifdef PRE_RENEWAL
	const char *filename[] = {
		"db/skill_db.txt",         "db/pre/skill_db_pre.txt",         "db/addon/skill_db_add.txt",
		"db/skill_require_db.txt", "db/pre/skill_require_db_pre.txt", "db/addon/skill_require_db_add.txt",
		"db/skill_cast_db.txt",    "db/pre/skill_cast_db_pre.txt",    "db/addon/skill_cast_db_add.txt",
		"db/skill_unit_db.txt",    "db/pre/skill_unit_db_pre.txt",    "db/addon/skill_unit_db_add.txt",
		"db/produce_db.txt",       "db/pre/produce_db_pre.txt",       "db/addon/produce_db_add.txt"
	};
	const int max = 3;
#else
	const char *filename[] = {
		"db/skill_db.txt",         "db/addon/skill_db_add.txt",
		"db/skill_require_db.txt", "db/addon/skill_require_db_add.txt",
		"db/skill_cast_db.txt",    "db/addon/skill_cast_db_add.txt",
		"db/skill_unit_db.txt",    "db/addon/skill_unit_db_add.txt",
		"db/produce_db.txt",       "db/addon/produce_db_add.txt"
	};
	const int max = 2;
#endif
	const char *filename2;

	memset(skill_db,0,sizeof(skill_db));

	/* スキルデータベース */
	for(m = 0; m < max; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > 0)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,14);
			if(split[13]==NULL || j<14)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_db[i].id = atoi(split[0]);
			skill_split_atoi(split[1],skill_db[i].range,MAX_SKILL_LEVEL);
			skill_db[i].hit = atoi(split[2]);
			skill_db[i].inf = atoi(split[3]);
			skill_db[i].pl  = atoi(split[4]);
			skill_db[i].nk  = atoi(split[5]);

			skill_db[i].max = atoi(split[6]);
			if(skill_db[i].max > MAX_SKILL_LEVEL)
				skill_db[i].max = MAX_SKILL_LEVEL;

			skill_split_atoi(split[7],skill_db[i].num,MAX_SKILL_LEVEL);

			if(strcmpi(split[8],"yes") == 0)
				skill_db[i].castcancel = 1;
			else
				skill_db[i].castcancel = 0;
			skill_db[i].cast_def_rate = atoi(split[9]);
			skill_db[i].inf2          = (int)strtol(split[10], NULL, 0);
			skill_split_atoi(split[11],skill_db[i].maxcount,MAX_SKILL_LEVEL);
			if(strcmpi(split[12],"weapon") == 0)
				skill_db[i].skill_type = BF_WEAPON;
			else if(strcmpi(split[12],"magic") == 0)
				skill_db[i].skill_type = BF_MAGIC;
			else if(strcmpi(split[12],"misc") == 0)
				skill_db[i].skill_type = BF_MISC;
			else
				skill_db[i].skill_type = 0;
			skill_split_atoi(split[13],skill_db[i].blewcount,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキルデータベース2 */
	filename2 = "db/skill_db2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k = 0;
	while(fgets(line,1020,fp)){
		char *split[50];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		j = skill_split_str(line,split,9);
		if(split[8]==NULL || j<9)
			continue;

		i = skill_get_skilldb_id(atoi(split[0]));
		if(i == 0)
			continue;

		skill_db[i].cloneable = atoi(split[1]);
		skill_db[i].misfire   = atoi(split[2]);
		skill_db[i].zone      = atoi(split[3]);
		skill_split_atoi(split[4],skill_db[i].damage_rate,sizeof(skill_db[i].damage_rate)/sizeof(int));
		skill_db[i].range_type = atoi(split[5]);
		skill_db[i].amotion_delay = atoi(split[6]);
		k++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* スキル要求データベース */
	for(m= max; m < max * 2; m++) {
		int n;
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,29);
			if(split[28]==NULL || j<29)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].hp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[2],skill_db[i].sp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[3],skill_db[i].hp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].sp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].zeny,MAX_SKILL_LEVEL);

			skill_db[i].weapon = 0;
			p = split[6];
			for(j=0;j<32;j++){
				n = atoi(p);
				if(n == WT_DOUBLE_MAX) {
					skill_db[i].weapon = 0xffffffff;
					break;
				} else {
					if(n >= WT_MAX) {
						n -= WT_DOUBLE_DD + WT_MAX;
					}
					skill_db[i].weapon |= 1<<n;
				}
				p=strchr(p,':');
				if(!p)
					break;
				p++;
			}

			if( strcmpi(split[7],"hiding") == 0 )                   skill_db[i].state = SST_HIDING;
			else if( strcmpi(split[7],"cloaking") == 0 )            skill_db[i].state = SST_CLOAKING;
			else if( strcmpi(split[7],"chasewalking") == 0 )        skill_db[i].state = SST_CHASEWALKING;
			else if( strcmpi(split[7],"hidden") == 0 )              skill_db[i].state = SST_HIDDEN;
			else if( strcmpi(split[7],"riding") == 0 )              skill_db[i].state = SST_RIDING;
			else if( strcmpi(split[7],"falcon") == 0 )              skill_db[i].state = SST_FALCON;
			else if( strcmpi(split[7],"cart") == 0 )                skill_db[i].state = SST_CART;
			else if( strcmpi(split[7],"shield") == 0 )              skill_db[i].state = SST_SHIELD;
			else if( strcmpi(split[7],"sight") == 0 )               skill_db[i].state = SST_SIGHT;
			else if( strcmpi(split[7],"explosionspirits") == 0 )    skill_db[i].state = SST_EXPLOSIONSPIRITS;
			else if( strcmpi(split[7],"cartboost") == 0 )           skill_db[i].state = SST_CARTBOOST;
			else if( strcmpi(split[7],"nen") == 0 )                 skill_db[i].state = SST_NEN;
			else if( strcmpi(split[7],"recover_weight_rate") == 0 ) skill_db[i].state = SST_RECOV_WEIGHT_RATE;
			else if( strcmpi(split[7],"move_enable") == 0 )         skill_db[i].state = SST_MOVE_ENABLE;
			else if( strcmpi(split[7],"water") == 0 )               skill_db[i].state = SST_WATER;
			else if( strcmpi(split[7],"dragon") == 0 )              skill_db[i].state = SST_DRAGON;
			else if( strcmpi(split[7],"wolf") == 0 )                skill_db[i].state = SST_WOLF;
			else if( strcmpi(split[7],"gear") == 0 )                skill_db[i].state = SST_GEAR;
			else                                                    skill_db[i].state = SST_NONE;

			skill_split_atoi(split[8],skill_db[i].spiritball,MAX_SKILL_LEVEL);
			skill_db[i].itemid[0] = atoi(split[9]);
			skill_db[i].amount[0] = atoi(split[10]);
			skill_db[i].itemid[1] = atoi(split[11]);
			skill_db[i].amount[1] = atoi(split[12]);
			skill_db[i].itemid[2] = atoi(split[13]);
			skill_db[i].amount[2] = atoi(split[14]);
			skill_db[i].itemid[3] = atoi(split[15]);
			skill_db[i].amount[3] = atoi(split[16]);
			skill_db[i].itemid[4] = atoi(split[17]);
			skill_db[i].amount[4] = atoi(split[18]);
			skill_db[i].itemid[5] = atoi(split[19]);
			skill_db[i].amount[5] = atoi(split[20]);
			skill_db[i].itemid[6] = atoi(split[21]);
			skill_db[i].amount[6] = atoi(split[22]);
			skill_db[i].itemid[7] = atoi(split[23]);
			skill_db[i].amount[7] = atoi(split[24]);
			skill_db[i].itemid[8] = atoi(split[25]);
			skill_db[i].amount[8] = atoi(split[26]);
			skill_db[i].itemid[9] = atoi(split[27]);
			skill_db[i].amount[9] = atoi(split[28]);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキル要求データベース2 */
	filename2 = "db/skill_require_db2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k = 0;
	while(fgets(line,1020,fp)){
		char *split[50];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		j = skill_split_str(line,split,6);
		if(split[5]==NULL || j<6)
			continue;

		i = skill_get_skilldb_id(atoi(split[0]));
		if(i == 0)
			continue;

		skill_split_atoi(split[1],skill_db[i].coin,MAX_SKILL_LEVEL);
		skill_db[i].arrow_type = atoi(split[2]);
		skill_split_atoi(split[3],skill_db[i].arrow_cost,MAX_SKILL_LEVEL);
		k++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* キャスティングデータベース */
	for(m = max * 2; m < max * 3; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 2)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,7);
			if(split[6]==NULL || j<7)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].cast,MAX_SKILL_LEVEL);
			skill_split_atoi(split[2],skill_db[i].fixedcast,MAX_SKILL_LEVEL);
			skill_split_atoi(split[3],skill_db[i].delay,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].cooldown,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].upkeep_time,MAX_SKILL_LEVEL);
			skill_split_atoi(split[6],skill_db[i].upkeep_time2,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキルユニットデータベース */
	for(m = max * 3; m < max * 4; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 3)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while (fgets(line,1020,fp)) {
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if (line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,8);
			if (split[7]==NULL || j<8)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_db[i].unit_id[0] = strtol(split[1],NULL,16);
			skill_db[i].unit_id[1] = strtol(split[2],NULL,16);
			skill_split_atoi(split[3],skill_db[i].unit_layout_type,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].unit_range,MAX_SKILL_LEVEL);
			skill_db[i].unit_interval = atoi(split[5]);
			skill_db[i].unit_target   = strtol(split[6],NULL,16);
			skill_split_strtol(split[7],skill_db[i].unit_flag,MAX_SKILL_LEVEL,16);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}
	skill_init_unit_layout();

	/* 製造系スキルデータベース */
	memset(skill_produce_db, 0, sizeof(skill_produce_db));

	for(m = max * 4; m < max * 5; m++) {
		int count = 0;
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 4)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		while(fgets(line,1020,fp)){
			char *split[6 + MAX_PRODUCE_RESOURCE * 2];
			int x,y;
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			memset(split,0,sizeof(split));
			for(j=0,p=line;j<6 + MAX_PRODUCE_RESOURCE * 2 && p;j++){
				split[j]=p;
				p=strchr(p,',');
				if(p) *p++=0;
			}
			if(split[0]==NULL)
				continue;
			i=atoi(split[0]);
			if(i<=0)
				continue;

			for(k=0; k<MAX_SKILL_PRODUCE_DB; k++) {
				if(skill_produce_db[k].nameid <= 0 || skill_produce_db[k].nameid == i)
					break;
			}
			if(k >= MAX_SKILL_PRODUCE_DB)
				break;

			skill_produce_db[k].nameid      = i;
			skill_produce_db[k].itemlv      = atoi(split[1]);
			skill_produce_db[k].req_skill   = atoi(split[2]);
			skill_produce_db[k].req_skilllv = atoi(split[3]);
			skill_produce_db[k].per         = atoi(split[4]);

			for(x=5,y=0; split[x] && split[x+1] && y<MAX_PRODUCE_RESOURCE; x+=2,y++){
				skill_produce_db[k].mat_id[y]     = atoi(split[x]);
				skill_produce_db[k].mat_amount[y] = atoi(split[x+1]);
			}
			count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], count);
	}

	/* 矢作成データベース */
	memset(skill_arrow_db, 0, sizeof(skill_arrow_db));
	filename2 = "db/create_arrow_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[16];
		int x,y;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;

		skill_arrow_db[k].nameid=i;

		for(x=1,y=0;split[x] && split[x+1] && y<5;x+=2,y++){
			skill_arrow_db[k].cre_id[y]     = atoi(split[x]);
			skill_arrow_db[k].cre_amount[y] = atoi(split[x+1]);
		}
		k++;
		if(k >= MAX_SKILL_ARROW_DB)
			break;
	}
	fclose(fp);
	printf("read %sdone (count=%d)\n", filename2, k);

	/* アブラカタブラデータベース */
	memset(skill_abra_db, 0, sizeof(skill_abra_db));
	filename2 = "db/abra_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[16];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;
		i=atoi(split[3]);
		if(i<=0)
			continue;

		skill_abra_db[k].nameid = atoi(split[0]);
		skill_abra_db[k].req_lv = atoi(split[2]);
		skill_abra_db[k].per    = atoi(split[3]);

		k++;
		if(k >= MAX_SKILL_ABRA_DB)
			break;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* ランダム発動スキルデータベース */
	memset(skill_rand_db, 0, sizeof(skill_rand_db));
	filename2 = "db/skill_random.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		int randomid,skillid,range,c;
		char *split[16];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;

		randomid = atoi(split[0]) - 1;
		if(randomid < 0 || randomid >= MAX_SKILL_RAND_DB)
			continue;

		skillid = atoi(split[1]);
		if(skill_get_skilldb_id(skillid) == 0)
			continue;

		range = atoi(split[2]);
		if(range < 1 || range >= MAX_SKILL_RAND_RATE)
			continue;

		c = skill_rand_db[randomid].entry;
		if(c >= MAX_SKILL_RAND_ENTRY)
			break;
		if(c > 0)
			range += skill_rand_db[randomid].data[c-1].qty;

		skill_rand_db[randomid].data[c].nameid = skillid;
		skill_rand_db[randomid].data[c].qty = range;
		skill_rand_db[randomid].entry++;

		k++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* チェンジマテリアルデータベース */
	memset(skill_material_db,0,sizeof(skill_material_db));
	filename2 = "db/changematerial_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[3 + MAX_PRODUCE_RESOURCE * 2];
		int x,y;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		memset(split,0,sizeof(split));
		for(j = 0, p = line; j < 3 + MAX_PRODUCE_RESOURCE * 2 && p; j++){
			split[j] = p;
			p = strchr(p,',');
			if(p) *p++ = 0;
		}
		if(split[0] == NULL)
			continue;
		i = atoi(split[0]);
		if(i <= 0)
			continue;

		skill_material_db[k].nameid = i;
		skill_split_atoi(split[1],skill_material_db[k].amount,2);
		for(x = 2, y = 0; split[x] && split[x + 1] && y < MAX_PRODUCE_RESOURCE; x += 2, y++){
			skill_material_db[k].mat_id[y]     = atoi(split[x]);
			skill_material_db[k].mat_amount[y] = atoi(split[x + 1]);
		}

		k++;
		if(k >= MAX_SKILL_PRODUCE_DB)
			break;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	return 0;
}

void skill_reload(void)
{
	skill_readdb();
}

/*==========================================
 * スキル関係初期化処理
 *------------------------------------------
 */
int do_init_skill(void)
{
	unsigned int tick = gettick();

	skill_readdb();

	add_timer_func_list(skill_unit_timer);
	add_timer_func_list(skill_castend_id);
	add_timer_func_list(skill_castend_pos);
	add_timer_func_list(skill_timerskill_timer);
	add_timer_func_list(skill_castend_delay_sub);

	add_timer_interval(tick+SKILLUNITTIMER_INVERVAL,skill_unit_timer,0,NULL,SKILLUNITTIMER_INVERVAL);

	return 0;
}
