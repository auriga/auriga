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
#include "skill_internal.h"
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

#define SKILLUNITTIMER_INVERVAL	50

static struct dbt *skillname_db = NULL;

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
	-1,SC_FLING,-1,-1,SC_MADNESSCANCEL,SC_ADJUSTMENT,SC_INCREASING,SC_MAGICALBULLET,-1,-1,
	/* 510- */
	-1,-1,-1,-1,-1,-1,-1,SC_GATLINGFEVER,-1,-1,
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
	-1,-1,-1,-1,-1,-1,-1,-1,SC_HELLINFERNO,-1,
	/* 710- */
	-1,-1,-1,-1,-1,-1,SC_MAXPAIN,-1,-1,-1,
	/* 720- */
	SC_FREEZE,SC_SPIDERWEB,-1,-1,SC_BURNT,-1,-1,SC_AETERNA,-1,-1,
	/* 730- */
	SC_CURSEDCIRCLE,-1,-1,-1,-1,SC_MANDRAGORA,-1,-1,-1,-1,
	/* 740- */
	-1,-1,-1,-1,SC_PROPERTYWALK,SC_PROPERTYWALK,-1,-1,-1,-1,
	/* 750- */
	-1,SC_ALL_STAT_DOWN,SC_GRADUAL_GRAVITY,SC_DAMAGE_HEAL,-1,-1,-1,-1,-1,-1,
	/* 760- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 770- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 780- */
	-1,-1,-1,SC_KILLING_AURA,-1,
};

/* (スキル番号 - SECOND_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable2[MAX_SECONDSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 1001- */
	-1,SC_SHRINK,-1,-1,SC_CLOSECONFINE,SC_SIGHTBLASTER,-1,SC_ELEMENTWATER,-1,-1,
	/* 1011- */
	SC_WINKCHARM,-1,-1,-1,-1,-1,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,
};

/* (スキル番号 - THIRD1_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable3_1[MAX_THIRD1SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 2001- */
	SC_ENCHANTBLADE,-1,SC_DEATHBOUND,-1,SC_FEAR,-1,-1,SC_HELLINFERNO,SC_FEAR,-1,
	/* 2011- */
	SC_MILLENNIUMSHIELD,SC_CRUSHSTRIKE,SC_REFRESH,SC_GIANTGROWTH,SC_STONEHARDSKIN,SC_VITALITYACTIVATION,-1,SC_FIGHTINGSPIRIT,SC_ABUNDANCE,-1,
	/* 2021- */
	SC_VENOMIMPRESS,-1,-1,-1,-1,-1,SC_POISONINGWEAPON,SC_WEAPONBLOCKING,SC_WEAPONBLOCK_ON,-1,
	/* 2031- */
	-1,-1,SC_CLOAKINGEXCEED,-1,SC_HALLUCINATIONWALK,SC_ROLLINGCUTTER,-1,-1,-1,SC_ADORAMUS,
	/* 2041- */
	SC_BLESSING,SC_INCREASEAGI,-1,SC_EPICLESIS,SC_KYRIE,SC_ORATIO,SC_LAUDAAGNUS,SC_LAUDARAMUS,-1,SC_RENOVATIO,
	/* 2051- */
	-1,-1,SC_EXPIATIO,SC_DUPLELIGHT,-1,-1,SC_SILENCE,
};

/* (スキル番号 - THIRD2_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable3_2[MAX_THIRD2SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 2201- */
	SC_WHITEIMPRISON,-1,SC_FROSTMISTY,SC_FREEZE,SC_MARSHOFABYSS,SC_RECOGNIZEDSPELL,SC_STONE,-1,SC_STASIS,-1,
	/* 2211- */
	SC_STUN,SC_HELLINFERNO,SC_HELLINFERNO,-1,-1,-1,-1,SC_HELLINFERNO,SC_FROSTMISTY,SC_BLEED,
	/* 2221- */
	SC_STUN,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2231- */
	-1,-1,-1,SC_FEARBREEZE,-1,-1,-1,SC_ELECTRICSHOCKER,-1,-1,
	/* 2241- */
	-1,SC_WUGDASH,-1,SC_WUGBITE,-1,-1,SC_CAMOUFLAGE,-1,-1,-1,
	/* 2251- */
	-1,-1,SC_HELLINFERNO,SC_FROSTMISTY,-1,-1,-1,-1,SC_HELLINFERNO,-1,
	/* 2261- */
	-1,SC_ACCELERATION,SC_HOVERING,-1,-1,-1,-1,SC_SHAPESHIFT,-1,SC_INFRAREDSCAN,
	/* 2271- */
	SC_ANALYZE,SC_MAGNETICFIELD,SC_NEUTRALBARRIER_MASTER,SC_STEALTHFIELD_MASTER,-1,-1,-1,-1,-1,-1,
	/* 2281- */
	-1,-1,-1,-1,SC__REPRODUCE,SC__AUTOSHADOWSPELL,SC__SHADOWFORM,-1,SC__BODYPAINT,SC__INVISIBILITY,
	/* 2291- */
	SC__DEADLYINFECT,SC__ENERVATION,SC__GROOMY,SC__IGNORANCE,SC__LAZINESS,SC__UNLUCKY,SC__WEAKNESS,SC__STRIPACCESSARY,SC__MANHOLE,-1,
	/* 2301- */
	-1,-1,SC_BERSERK,SC__FEINTBOMB,-1,-1,-1,-1,-1,-1,
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
	SC_STRIKING,SC_WARMER,SC_VACUUM_EXTREME,SC_STUN,SC_DEEP_SLEEP,-1,SC_SUMMON_ELEM,SC_SUMMON_ELEM,SC_SUMMON_ELEM,SC_SUMMON_ELEM,
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
	-1,-1,-1,-1,SC_SACRAMENT,-1,SC_FEAR,-1,-1,-1,
	/* 2521- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2531- */
	-1,-1,-1,-1,-1,-1,SC_ODINS_POWER,-1,-1,SC_DISSONANCE,
	/* 2541- */
	SC_UGLYDANCE,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 2551- */
	-1,-1,-1,-1,SC_B_TRAP,-1,-1,SC_E_CHAIN,-1,SC_C_MARKER,
	/* 2561- */
	-1,SC_H_MINE,SC_P_ALTER,SC_FALLEN_ANGEL,-1,-1,-1,SC_HEAT_BARREL,SC_ANTI_M_BLAST,-1,
	/* 2571- */
	-1,-1,-1,SC_LIGHTOFMOON,SC_LUNARSTANCE,-1,SC_LIGHTOFSTAR,SC_STARSTANCE,SC_NEWMOON,SC_FLASHKICK,
	/* 2581- */
	-1,SC_NOVAEXPLOSING,SC_UNIVERSESTANCE,SC_FALLINGSTAR,SC_GRAVITYCONTROL,SC_DIMENSION,SC_CREATINGSTAR,-1,-1,SC_LIGHTOFSUN,
	/* 2591- */
	SC_SUNSTANCE,-1,-1,-1,-1,SC_SOULGOLEM,SC_SOULSHADOW,SC_SOULFALCON,SC_SOULFAIRY,-1,
	/* 2601- */
	SC_SOULCURSE,SC_SWHOO,SC_SHA,-1,SC_SOULUNITY,SC_SOULDIVISION,SC_SOULREAPER,-1,SC_SOULCOLLECT,-1,
	/* 2611- */
	-1,-1,
};

/* (スキル番号 - THIRD3_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable3_3[MAX_THIRD3SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 3001- */
	SC_HIDING,-1,-1,SC_KO_JYUMONJIKIRI,-1,-1,-1,-1,-1,-1,
	/* 3011- */
	SC_MEIKYOUSISUI,-1,SC_KYOUGAKU,SC_CURSE,-1,-1,-1,-1,-1,SC_KO_ZENKAI,
	/* 3021- */
	SC_CONFUSION,SC_IZAYOI,SC_KG_KAGEHUMI,SC_KYOMU,SC_KAGEMUSYA,SC_ZANGETSU,SC_GENSOU,-1,SC_AKAITSUKI,-1,
	/* 3031- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 3041- */
	-1,-1,-1,-1,-1,
};

/* (スキル番号 - THIRD4_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable3_4[MAX_THIRD4SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 5001- */
	SC_DARKCROW,SC_UNLIMIT,-1,SC_FROSTMISTY,-1,SC_STUN,SC_FRIGG_SONG,-1,-1,SC__ESCAPE,
	/* 5011- */
	SC_OFFERTORIUM,SC_TELEKINESIS_INTENSE,-1,-1,SC_HELLINFERNO,-1,-1,-1,-1,SC_SUHIDE,
	/* 5021- */
	SC_BLEED,SC_SU_STOOP,-1,-1,-1,SC_BLEED,SC_CATNIPPOWDER,-1,SC_SV_ROOTTWIST,-1,
	/* 5031- */
	-1,SC_BITESCAR,-1,-1,SC_ARCLOUSEDASH,-1,-1,-1,SC_TUNAPARTY,SC_SHRIMP,
	/* 5041- */
	SC_FRESHSHRIMP,-1,-1,-1,-1,-1,SC_HISS,SC_NYANGGRASS,SC_GROOMING,SC_GROOMING,
	/* 5051- */
	SC_PROTECTIONOFSHRIMP,-1,SC_CHATTERING,-1,SC_CHATTERING,-1,-1,-1,-1,-1,
	/* 5061- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 5071- */
	SC_FULL_THROTTLE,-1,-1,-1,-1,SC_HELPANGEL,-1,-1,
};

/* (スキル番号 - FOURTH1_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable4_1[MAX_FOURTH1SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 5201- */
	SC_SERVANTWEAPON,-1,SC_SERVANT_SIGN,SC_HANDICAPSTATE_DEEPBLIND,-1,SC_CHARGINGPIERCE,-1,-1,-1,SC_DRAGONIC_AURA,
	/* 5211- */
	-1,SC_VIGOR,-1,SC_DEADLY_DEFEASANCE,SC_CLIMAX_DES_HU,-1,-1,SC_CLIMAX_EARTH,-1,-1,
	/* 5221- */
	-1,SC_CLIMAX_BLOOM,-1,-1,SC_CLIMAX_CRYIMP,-1,-1,-1,-1,-1,
	/* 5231- */
	-1,SC_CLIMAX,-1,-1,-1,-1,-1,SC_POWERFUL_FAITH,SC_FIRM_FAITH,-1,
	/* 5241- */
	SC_HOLY_OIL,SC_SINCERE_FAITH,SC_MASSIVE_F_BLASTER,-1,SC_FIRST_BRAND,SC_FIRST_FAITH_POWER,SC_SECOND_JUDGE,SC_SECOND_BRAND,SC_SECOND_BRAND,SC_SECOND_BRAND,
	/* 5251- */
	-1,-1,-1,SC_THIRD_EXOR_FLAME,SC_GUARD_STANCE,SC_GUARDIAN_S,SC_REBOUND_S,-1,-1,SC_ATTACK_STANCE,
	/* 5261- */
	SC_ULTIMATE_S,SC_HOLY_S,SC_SPEAR_SCAR,-1,SC_SHIELD_POWER,-1,-1,-1,SC_MEDIALE,-1,
	/* 5271- */
	SC_A_VITA,SC_A_TELUM,SC_HANDICAPSTATE_DEEPSILENCE,-1,SC_PRE_ACIES,-1,-1,SC_COMPETENTIA,-1,-1,
	/* 5281- */
	SC_RELIGIO,SC_BENEDICTUM,-1,-1,SC_SHADOW_EXCEED,SC_DANCING_KNIFE,-1,-1,SC_E_SLASH_COUNT,SC_POTENT_VENOM,
	/* 5291- */
	-1,SC_WEAPONBLOCK_ON,SC_SHADOW_WEAPON,SC_DARKCROW,SC_AXE_STOMP,SC_RUSH_QUAKE2,-1,SC_A_MACHINE,SC_D_MACHINE,-1,
	/* 5301- */
	-1,SC_ABR_BATTLE_WARIOR,SC_ABR_DUAL_CANNON,SC_ABR_MOTHER_NET,SC_ABR_INFINITY,-1,-1,-1,-1,-1,
	/* 5311- */
	-1,-1,SC_SHADOW_STRIP,SC_ABYSS_DAGGER,SC_HANDICAPSTATE_MISFORTUNE,-1,SC_ABYSSFORCEWEAPON,SC_ABYSS_SLAYER,-1,-1,
	/* 5321- */
	-1,-1,-1,SC_WINDSIGN,-1,-1,-1,SC_CALAMITYGALE,-1,-1,
	/* 5331- */
	SC_HANDICAPSTATE_DEEPBLIND,SC_HANDICAPSTATE_CRYSTALLIZATION,SC_HANDICAPSTATE_LIGHTNINGSTRIKE,SC_CRESCIVEBOLT,SC_HANDICAPSTATE_CONFLAGRATION,-1,-1,-1,SC_PROTECTSHADOWEQUIP,-1,
	/* 5341- */
	-1,-1,-1,SC_BO_WOODENWARRIOR,SC_BO_WOODEN_FAIRY,SC_BO_CREEPER,SC_RESEARCHREPORT,SC_BO_HELLTREE,-1,-1,
	/* 5351- */
	SC_MYSTIC_SYMPHONY,SC_KVASIR_SONATA,SC_ROSEBLOSSOM,-1,-1,-1,SC_SOUNDBLEND,SC_GEF_NOCTURN,-1,SC_AIN_RHAPSODY,
	/* 5361- */
	SC_MUSICAL_INTERLUDE,SC_JAWAII_SERENADE,-1,SC_PRON_MARCH,-1,SC_SPELL_ENCHANTING,-1,-1,SC_HANDICAPSTATE_FROSTBITE,SC_HANDICAPSTATE_LIGHTNINGSTRIKE,
	/* 5371- */
	SC_HANDICAPSTATE_DEADLYPOISON,SC_HANDICAPSTATE_CONFLAGRATION,SC_HANDICAPSTATE_CRYSTALLIZATION,-1,SC_SUMMON_ELEMENTAL_ARDOR,SC_SUMMON_ELEMENTAL_DILUVIO,SC_SUMMON_ELEMENTAL_PROCELLA,SC_SUMMON_ELEMENTAL_TERREMOTUS,SC_SUMMON_ELEMENTAL_SERPENS,-1,
	/* 5381- */
	SC_ELEMENTAL_VEIL,-1,-1,-1,-1,-1,SC_BO_HELL_DUSTY,-1,-1,-1,
	/* 5391- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 5401- */
	-1,-1,SC_INTENSIVE_AIM,SC_GRENADE_FRAGMENT_1,-1,-1,-1,-1,-1,-1,
	/* 5411- */
	-1,-1,SC_AUTO_FIRING_LAUNCHEREFST,SC_HIDDEN_CARD,-1,-1,-1,SC_TALISMAN_OF_PROTECTION,SC_TALISMAN_OF_WARRIOR,SC_TALISMAN_OF_MAGICIAN,
	/* 5421- */
	-1,-1,SC_TALISMAN_OF_FIVE_ELEMENTS,-1,-1,SC_T_FIRST_GOD,SC_T_SECOND_GOD,SC_T_THIRD_GOD,SC_T_FOURTH_GOD,-1,
	/* 5431- */
	SC_T_FIVETH_GOD,SC_HEAVEN_AND_EARTH,-1,-1,-1,SC_HOGOGONG,-1,-1,-1,SC_MARINE_FESTIVAL,
	/* 5441- */
	SC_SANDY_FESTIVAL,SC_KI_SUL_RAMPAGE,-1,SC_COLORS_OF_HYUN_ROK_1,-1,-1,SC_TEMPORARY_COMMUNION,SC_BLESSING_OF_M_CREATURES,-1,-1,
	/* 5451- */
	-1,SC_STUN,SC_SHIELDCHAINRUSH,SC_PC_STOP,SC_STUN,-1,SC_MISTYFROST,-1,SC_GROUNDGRAVITY,SC_CURSE,
	/* 5461- */
	SC_BREAKINGLIMIT,SC_RULEBREAK,-1,-1,SC_RISING_SUN,-1,-1,SC_RISING_MOON,-1,-1,
	/* 5471- */
	-1,SC_STAR_BURST,-1,-1,SC_SKY_ENCHANT,SC_SHADOW_CLOCK,SC_SHADOW_CLOCK,-1,-1,SC_NIGHTMARE,
	/* 5481- */
	-1,-1,SC_NIGHTMARE,-1,SC_NIGHTMARE,SC_SHADOW_CLOCK,-1,-1,-1,-1,
	/* 5491- */
	-1,SC_NIGHTMARE,-1,-1,-1,-1,-1,
};

/* (スキル番号 - FOURTH2_SKILLID)＝＞ステータス異常番号変換テーブル */
int SkillStatusChangeTable4_2[MAX_FOURTH2SKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 6001- */
	-1,-1,-1,-1,-1,-1,
};

/* (スキル番号 - HOM_SKILLID)＝＞ステータス異常番号変換テーブル */
int HomSkillStatusChangeTable[MAX_HOMSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 8001- */
	-1,SC_AVOID,-1,SC_CHANGE,-1,SC_DEFENCE,-1,SC_BLOODLUST,-1,SC_FLEET,
	/* 8011- */
	SC_SPEED,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 8021- */
	SC_PAIN_KILLER,SC_LIGHT_OF_REGENE,SC_OVERED_BOOST,-1,-1,SC_SILENCE,-1,-1,-1,-1,
	/* 8031- */
	-1,SC_GOLDENE_FERSE,SC_SAFETYWALL,-1,SC_ANGRIFFS_MODUS,SC_TINDER_BREAKER,SC_CBC,SC_EQC,SC_MAGMA_FLOW,SC_GRANITIC_ARMOR,
	/* 8041- */
	SC_HELLINFERNO,SC_PYROCLASTIC,SC_VOLCANIC_ASH,-1,-1,-1,-1,-1,-1,-1,
	/* 8051- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,
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
	SC_ROCK_CRUSHER_ATK,-1,SC_FLAMETECHNIC,SC_FLAMEARMOR,-1,SC_COLD_FORCE,SC_CRYSTAL_ARMOR,-1,SC_GRACE_BREEZE,SC_EYES_OF_STORM,
	/* 8451- */
	-1,SC_EARTH_CARE,SC_STRONG_PROTECTION,-1,SC_DEEP_POISONING,SC_POISON_SHIELD,-1,
};

/* (スキル番号 - ABR_SKILLID)＝＞ステータス異常番号変換テーブル */
int AbrSkillStatusChangeTable[MAX_ABRSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 8601- */
	-1,-1,-1,-1,-1,
};

/* (スキル番号 - GUILD_SKILLID)＝＞ステータス異常番号変換テーブル */
int GuildSkillStatusChangeTable[MAX_GUILDSKILL] = {	/* status.hのenumのSC_***とあわせること */
	/* 10000- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 10010- */
	SC_BATTLEORDER,SC_REGENERATION,-1,-1,-1,-1,-1,-1,-1,-1,
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

static int skill_frostjoke_scream(struct block_list *bl,va_list ap);
static int skill_trap_splash(struct block_list *bl, va_list ap );
static int skill_count_target(struct block_list *bl, va_list ap );
static int skill_unit_onplace(struct skill_unit *src,struct block_list *bl,unsigned int tick);
static int skill_unit_effect(struct block_list *bl,va_list ap);
static int skill_check_condition_use_sub(struct block_list *bl,va_list ap);
static int skill_chainlightning(struct block_list *bl,va_list ap);
static int skill_maelstrom(struct block_list *bl,va_list ap);

/* スキルユニットの配置情報を返す */
static struct skill_unit_layout skill_unit_layout[MAX_SKILL_UNIT_LAYOUT];
static int firewall_unit_pos;
static int icewall_unit_pos;
static int earthstrain_unit_pos;
static int firerain_unit_pos;

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
	else if(skillid == RL_FIRE_RAIN)
		return &skill_unit_layout[firerain_unit_pos+dir];

	printf("unknown unit layout for skill %d, %d\n",skillid,skilllv);
	return &skill_unit_layout[0];
}

int GetSkillStatusChangeTable(int id)
{
	if(id >= 0 && id < MAX_SKILLID)
		return SkillStatusChangeTable[id];

	if(id >= SECOND_SKILLID && id < MAX_SECOND_SKILLID)
		return SkillStatusChangeTable2[id - SECOND_SKILLID];

	if(id >= THIRD1_SKILLID && id < MAX_THIRD1_SKILLID)
		return SkillStatusChangeTable3_1[id - THIRD1_SKILLID];

	if(id >= THIRD2_SKILLID && id < MAX_THIRD2_SKILLID)
		return SkillStatusChangeTable3_2[id - THIRD2_SKILLID];

	if(id >= THIRD3_SKILLID && id < MAX_THIRD3_SKILLID)
		return SkillStatusChangeTable3_3[id - THIRD3_SKILLID];

	if(id >= THIRD4_SKILLID && id < MAX_THIRD4_SKILLID)
		return SkillStatusChangeTable3_4[id - THIRD4_SKILLID];

	if(id >= FOURTH1_SKILLID && id < MAX_FOURTH1_SKILLID)
		return SkillStatusChangeTable4_1[id - FOURTH1_SKILLID];

	if(id >= FOURTH2_SKILLID && id < MAX_FOURTH2_SKILLID)
		return SkillStatusChangeTable4_2[id - FOURTH2_SKILLID];

	if(id >= HOM_SKILLID && id < MAX_HOM_SKILLID)
		return HomSkillStatusChangeTable[id - HOM_SKILLID];

	if(id >= MERC_SKILLID && id < MAX_MERC_SKILLID)
		return MercSkillStatusChangeTable[id - MERC_SKILLID];

	if(id >= ELEM_SKILLID && id < MAX_ELEM_SKILLID)
		return ElemSkillStatusChangeTable[id - ELEM_SKILLID];

	if(id >= ABR_SKILLID && id < MAX_ABR_SKILLID)
		return AbrSkillStatusChangeTable[id - ABR_SKILLID];

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
int skill_get_ap(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].ap[lv-1];
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
int skill_get_area(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].area[lv-1];
}
int skill_get_healap(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].heal_ap[lv-1];
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
int skill_get_unit_interval(int id,int lv)
{
	if(lv<=0) return 0;

	id = skill_get_skilldb_id(id);
	if(lv > MAX_SKILL_LEVEL) lv = MAX_SKILL_LEVEL;
	return skill_db[id].unit_interval[lv-1];
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
int skill_get_name2id(const char *name)
{
	struct skill_db *skill;

	skill = (struct skill_db *)strdb_search(skillname_db,name);
	return (skill)? skill->id: 0;
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
				case RA_ARROWSTORM:			/* アローストーム */
				case RA_AIMEDBOLT:			/* エイムドボルト */
				case WH_HAWKRUSH:			/* ホークラッシュ */
				case WH_HAWKBOOMERANG:		/* ホークブーメラン */
				case WH_GALESTORM:			/* ゲイルストーム */
				case WH_CRESCIVE_BOLT:		/* クレッシブボルト */
				case TR_RHYTHMSHOOTING:		/* リズムシューティング */
					if((skill = pc_checkskill(sd,AC_VULTURE)) > 0)	// ワシの目
						range += skill;
					break;
				case GS_TRACKING:			/* トラッキング */
				case GS_PIERCINGSHOT:		/* ピアーシングショット */
				case GS_RAPIDSHOWER:		/* ラピッドシャワー */
				case GS_FULLBUSTER:			/* フルバスター */
				case GS_SPREADATTACK:		/* スプレッドアタック */
				case GS_GROUNDDRIFT:		/* グラウンドドリフト */
					if((skill = pc_checkskill(sd,GS_SNAKEEYE)) > 0)	// スネークアイ
						range += skill;
					break;
				case NJ_KIRIKAGE:			/* 影斬り */
					if((skill = pc_checkskill(sd,NJ_SHADOWJUMP)) > 0)	// 影跳び
						range = skill_get_range(NJ_SHADOWJUMP,skill);	// 影跳びの習得レベルで射程が変動
					break;
				case HT_LANDMINE:			/* ランドマイン */
				case HT_FREEZINGTRAP:		/* フリージングトラップ */
				case HT_BLASTMINE:			/* ブラストマイン */
				case HT_CLAYMORETRAP:		/* クレイモアトラップ */
				case RA_CLUSTERBOMB:		/* クラスターボム */
				case RA_FIRINGTRAP:			/* ファイアリングトラップ */
				case RA_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
				case WH_DEEPBLINDTRAP:		/* ディープブラインドトラップ */
				case WH_SOLIDTRAP:			/* ソリッドトラップ */
				case WH_SWIFTTRAP:			/* スイフトトラップ */
				case WH_FLAMETRAP:			/* フレイムトラップ */
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
	struct homun_data       *hd = NULL;
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
	hd    = BL_DOWNCAST( BL_HOM, src );
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
				if(pc_is3rdclass(sd) || pc_is4thclass(sd)) {
					// 3次職・4次職は習得レベルで発動
					skill_castend_damage_id(src,bl,HT_BLITZBEAT,skill,tick,0xf00000);
				} else {
					int lv = (sd->status.job_level+9)/10;
					skill_castend_damage_id(src,bl,HT_BLITZBEAT,(skill < lv)? skill: lv,tick,0xf00000);
				}
			}
			/* 自動ウォーグストライク */
			if( pc_iswolf(sd) && (skill = pc_checkskill(sd,RA_WUGSTRIKE)) > 0) {
				int rate = sd->paramc[5]*30;
				if(pc_isfalcon(sd))
					rate = rate / 3;
				if(atn_rand()%10000 < rate)
					skill_castend_damage_id(src,bl,RA_WUGSTRIKE,skill,tick,0xf00000);
			}
			/* 自動ホークラッシュ */
			if( pc_isfalcon(sd) && (skill = pc_checkskill(sd,WH_HAWKRUSH)) > 0) {
				int rate = sd->paramc[10]*30;
				rate += rate * (pc_checkskill(sd,WH_NATUREFRIENDLY) * 20) / 100;
				if(atn_rand()%10000 < rate)
					skill_castend_damage_id(src,bl,WH_HAWKRUSH,skill,tick,0xf00000);
			}
			/* スナッチャー */
			if(sd->status.weapon != WT_BOW && (skill = pc_checkskill(sd,RG_SNATCHER)) > 0) {
				int skill2;
				if((skill*15 + 55) + (skill2 = pc_checkskill(sd,TF_STEAL))*10 > atn_rand()%1000) {
					if(dstmd && pc_steal_item(sd,dstmd))
						clif_skill_nodamage(src,bl,TF_STEAL,skill2,1);
					else if(battle_config.display_snatcher_skill_fail)
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
		else if (md && mobdb_search(md->class_)->mode_opt[MDOPT_FATALBLOW] > 0) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*(skilllv-5)+(status_get_lv(src)/3),mobdb_search(md->class_)->lv))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case TF_POISON:			/* インベナム */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,400*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;

	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,200*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case AS_VENOMKNIFE:		/* ベナムナイフ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,TF_POISON,SKILLFAIL_FAILED,0,0);
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
			struct status_change *s_sc = status_get_sc(src);
			if(s_sc && s_sc->data[SC_RAID].timer != -1 && s_sc->data[SC_RAID].val2 > 0) {
				s_sc->data[SC_RAID].val2--;
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
			pc_heal(dstsd,0,-sp,0,0);
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
			pc_heal(dstsd,0,-sp,0,0);
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
			pc_heal(dstsd,0,-sp,0,0);
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
			int coin = 5;
			if(sd->coin.num < 5)
				coin = sd->coin.num;
			pc_delcoin(sd,coin,0);
			status_change_start(bl,SC_FLING,skilllv,coin,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case GS_BULLSEYE:		/* ブルズアイ */
		{
			int race = status_get_race(bl);
			if(!(status_get_mode(bl)&MD_BOSS) && (race == RCT_BRUTE || race == RCT_DEMIHUMAN || race == RCT_PLAYER_HUMAN || race == RCT_PLAYER_DORAM) && atn_rand()%10000 < 10)
				skill_castend_nodamage_id(src,bl,SA_COMA,skilllv,tick,0);
		}
		break;
	case GS_DISARM:			/* ディスアーム */
		{
			int rate = status_get_dex(src) / ((7-skilllv)*4) + status_get_luk(src) / ((6-skilllv)*4);
			rate = rate + status_get_lv(src) - (status_get_agi(bl) * rate/100) - status_get_luk(bl) - status_get_lv(bl);
			if(rate > 0 && atn_rand()%100 < rate) {
				if(dstsd) {
					int i;
					for(i=0; i<MAX_INVENTORY; i++) {
						if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_RARM)) {
							pc_unequipitem(dstsd,i,0);
							status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
							break;
						}
					}
				}
				else if(dstmd && !(status_get_mode(bl)&MD_BOSS)) {
					status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				}
			}
		}
		break;
	case GS_PIERCINGSHOT:		/* ピアーシングショット */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GS_FULLBUSTER:		/* フルバスター */
		{
			if(atn_rand() % 10000 < status_change_rate(src,SC_BLIND,200*skilllv,status_get_lv(src)))
				status_change_pretimer(src,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
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
	case NPC_HELLJUDGEMENT2:		/* デモニックヘルジャッジメント */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_EVILLAND:		/* イビルランド */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_CRITICALWOUND:		/* 致命傷攻撃 */
		status_change_start(bl,SC_CRITICALWOUND,skilllv,skilllv*10,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_WIDECRITICALWOUND:		/* ワイドクリティカルウーンズ */
		status_change_start(bl,SC_CRITICALWOUND,skilllv,skilllv>=6? (skilllv-5)*20: skilllv*20,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_VENOMIMPRESS:		/* Mベナムインプレス */
		status_change_start(bl,SC_VENOMIMPRESS,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_MAGMA_ERUPTION:	/* Mマグマイラプション */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,9000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_MAGMA_ERUPTION_DOTDAMAGE:	/* Mマグマイラプション(追撃) */
		status_change_start(bl,SC_HELLINFERNO,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_RAYOFGENESIS:	/* Mレイオブジェネシス */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,(skilllv<8? 500: 1000),status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_DRAGONBREATH:	/* Mドラゴンブレス */
		if(atn_rand() % 10000 < 5000) {
			if(skilllv < 6)
				status_change_pretimer(bl,SC_HELLINFERNO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			else
				status_change_pretimer(bl,SC_FROSTMISTY,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case MH_NEEDLE_OF_PARALYZE:	/* ニードルオブパラライズ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_PARALYZE,2500+skilllv*1500,status_get_lv(src)))
			status_change_start(bl,SC_PARALYZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case MH_POISON_MIST:	/* ポイズンミスト */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_STAHL_HORN:	/* シュタールホーン */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_SILVERVEIN_RUSH:	/* シルバーベインラッシュ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_MIDNIGHT_FRENZY:	/* ミッドナイトフレンジ */
		if(atn_rand() % 10000 < 1000+skilllv*200+(hd? hd->spiritball * 100: 0))
			status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_TINDER_BREAKER:	/*ティンダーブレイカー */
		{
			struct status_change *s_sc = status_get_sc(src);
			int duration = status_get_str(src) / 7 - status_get_str(bl) / 10;
			if(duration < skilllv)
				duration = skilllv;

			if(s_sc && s_sc->data[SC_TINDER_BREAKER].timer != -1) {
				struct block_list *target = map_id2bl(s_sc->data[SC_TINDER_BREAKER].val2);
				if(target) {
					status_change_end(target,SC_TINDER_BREAKER,-1);
				}
			}
			status_change_start(src,SC_TINDER_BREAKER,skilllv,bl->id,0,0,duration*1000,0);
			status_change_start(bl,SC_TINDER_BREAKER,skilllv,src->id,0,0,duration*1000,0);
		}
		break;
	case MH_EQC:	/* E.Q.C */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_LAVA_SLIDE:		/* ラーヴァスライド */
		if(atn_rand() % 10000 < skilllv * 1000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
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
		if(atn_rand() % 10000 < 1500) {
			int sec = skill_get_time(skillid,skilllv) - (status_get_lv(bl) * 20) - (status_get_agi(bl) * 20) - (status_get_luk(bl) * 10);
			if(sec > 0)
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0,tick+status_get_amotion(src));
		}
		break;
	case RK_DRAGONBREATH_WATER:	// ウォータードラゴンブレス
		if(atn_rand() % 10000 < 1500) {
			int sec = skill_get_time(skillid,skilllv) - (status_get_vit(bl) * 50) - (status_get_dex(bl) * 50);
			if(sec > 0)
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0,tick+status_get_amotion(src));
		}
		break;
	case AB_ADORAMUS:		/* アドラムス */
		if(atn_rand() % 10000 < skilllv * 400) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_JACKFROST:		/* ジャックフロスト */
	case NPC_JACKFROST:		/* Mジャックフロスト */
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
	case NPC_COMET:			/* Mコメット */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
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
			int sec = skill_get_time2(skillid,skilllv) - (status_get_agi(bl) + status_get_vit(bl)) * 70;
			if(sec > 0) {
				unit_stop_walking(bl,1);
				status_change_start(bl,SC_ELECTRICSHOCKER,skilllv,0,0,0,sec,0);
			}
		}
		break;
	case RA_WUGBITE:	/* ウォーグバイト */
		{
			int rate = 50 + skilllv * 10 - status_get_agi(bl) / 4;
			if(sd)
				skill = pc_checkskill(sd,RA_TOOTHOFWUG);
			else
				skill = 0;

			rate += skill * 2;
			if(rate < 50)
				rate = 50;

			if(atn_rand() % 100 < rate){
				unit_stop_walking(bl,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv)+skill*500,0);
			}
		}
		break;
	case RA_MAGENTATRAP:	/* マゼンタトラップ */
	case RA_COBALTTRAP:		/* コバルトトラップ */
	case RA_MAIZETRAP:		/* メイズトラップ */
	case RA_VERDURETRAP:	/* ヴェルデュールトラップ */
		if(dstmd) {
			// ボス属性には無効
			if((battle_config.boss_no_element_change && dstmd->mode&MD_BOSS))
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
			(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv * 1000,status_get_lv(src)))) {
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		} else if(atn_rand() % 10000 < 2000 + skilllv * 1000) {
			status_change_pretimer(bl,SC_FROSTMISTY,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
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
	case NPC_CLOUD_KILL:		/* Mクラウドキル */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_VARETYR_SPEAR:		/* ヴェラチュールスピアー */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
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
	case RL_MASS_SPIRAL:		/* マススパイラル */
		if(!(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,3000+1000*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RL_BANISHING_BUSTER:	/* バニシングバスター */
		if(atn_rand()%100 < skilllv*10+50)
			status_change_release(bl,0x02);	// ディスペル効果
		break;
	case RL_AM_BLAST:		/* アンチマテリアルブラスト */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RL_S_STORM:		/* シャッターストーム */
		if(dstsd && atn_rand()%10000 <= 500 * skilllv) {
			pc_break_equip2(dstsd, EQUIP_INDEX_HEAD2);
		}
		break;
	case SJ_FULLMOONKICK:	/* 満月脚 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SJ_STAREMPEROR:		/* 星帝降臨 */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SILENCE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SP_SPA:			/* エスパ */
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SHA:			/* エスハ */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SP_SOULEXPLOSION:	/* 魂の崩壊 */
		status_change_end(bl,SC_ALCHEMIST,-1);
		status_change_end(bl,SC_MONK,-1);
		status_change_end(bl,SC_STAR,-1);
		status_change_end(bl,SC_SAGE,-1);
		status_change_end(bl,SC_CRUSADER,-1);
		status_change_end(bl,SC_SUPERNOVICE,-1);
		status_change_end(bl,SC_KNIGHT,-1);
		status_change_end(bl,SC_WIZARD,-1);
		status_change_end(bl,SC_PRIEST,-1);
		status_change_end(bl,SC_BARDDANCER,-1);
		status_change_end(bl,SC_ROGUE,-1);
		status_change_end(bl,SC_ASSASIN,-1);
		status_change_end(bl,SC_BLACKSMITH,-1);
		status_change_end(bl,SC_HUNTER,-1);
		status_change_end(bl,SC_SOULLINKER,-1);
		status_change_end(bl,SC_HIGH,-1);
		status_change_end(bl,SC_DEATHKINGHT,-1);
		status_change_end(bl,SC_COLLECTOR,-1);
		status_change_end(bl,SC_NINJA,-1);
		status_change_end(bl,SC_GUNNER,-1);
		status_change_end(bl,SC_SOULGOLEM,-1);
		status_change_end(bl,SC_SOULSHADOW,-1);
		status_change_end(bl,SC_SOULFALCON,-1);
		status_change_end(bl,SC_SOULFAIRY,-1);
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
	case SU_CN_METEOR2:	/* イヌハッカメテオ(呪い) */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case NPC_UGLYDANCE:
		if(dstsd) {
			int sp = 5+skilllv*5;
			pc_heal(dstsd,0,-sp,0,0);
		}
		break;
	case DK_SERVANT_W_PHANTOM:	/* サーヴァントウェポン：ファントム */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case AG_DEADLY_PROJECTION:	/* デッドリープロジェクション */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case IQ_FIRST_BRAND:		/* 第一撃：烙印 */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case IQ_SECOND_FLAME:		/* 第二撃：滅魔の火 */
	case IQ_SECOND_FAITH:		/* 第二撃：信念 */
	case IQ_SECOND_JUDGEMENT:	/* 第二撃：審判 */
		if(tsc && tsc->data[SC_FIRST_BRAND].timer != -1)
			status_change_end(bl,SC_FIRST_BRAND,-1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case IQ_THIRD_PUNISH:		/* 第三撃：断罪 */
	case IQ_THIRD_FLAME_BOMB:	/* 第三撃：滅火撃 */
	case IQ_THIRD_CONSECRATION:	/* 第三撃：浄化 */
		if(tsc && tsc->data[SC_SECOND_BRAND].timer != -1)
			status_change_end(bl,SC_SECOND_BRAND,-1);
		break;
	case CD_ARBITRIUM:	/* アルビトリウム */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*200,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case ABC_UNLUCKY_RUSH:	/* アンラッキーラッシュ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WH_DEEPBLINDTRAP:	/* ディープブラインドトラップ */
	case WH_SOLIDTRAP:		/* ソリッドトラップ */
	case WH_SWIFTTRAP:		/* スイフトトラップ */
	case WH_FLAMETRAP:		/* フレイムトラップ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case BO_ACIDIFIED_ZONE_WATER:		/* アシディファイドゾーン(水) */
	case BO_ACIDIFIED_ZONE_GROUND:		/* アシディファイドゾーン(地) */
	case BO_ACIDIFIED_ZONE_WIND:		/* アシディファイドゾーン(風) */
	case BO_ACIDIFIED_ZONE_FIRE:		/* アシディファイドゾーン(火) */
		if(atn_rand()%100 < skilllv)
			skill_unitsetting(src,BO_ACIDIFIED_ZONE_WATER_INSTALL_ON_GROUND+skillid-BO_ACIDIFIED_ZONE_WATER,skilllv,bl->x,bl->y,0);
		break;
	case TR_ROSEBLOSSOM:	/* ロゼブロッサム */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case EM_DIAMOND_STORM:		/* ダイヤモンドストーム */
	case EM_TERRA_DRIVE:		/* テラドライブ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),750+skilllv*1250,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case EM_LIGHTNING_LAND:		/* ライトニングランド */
	case EM_VENOM_SWAMP:		/* ベナムスワンプ */
	case EM_CONFLAGRATION:		/* コンフラグレーション */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SH_HOWLING_OF_CHUL_HO:	/* タイガーハウリング */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case HN_MEGA_SONIC_BLOW:	/* メガソニックブロー */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),3000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_SHIELD_CHAIN_RUSH:	/* シールドチェーンラッシュ */
	case HN_SPIRAL_PIERCE_MAX:	/* スパイラルピアースマックス */
		if(!(status_get_mode(bl)&MD_BOSS))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_METEOR_STORM_BUSTER:	/* メテオストームバスター */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),3000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_NAPALM_VULCAN_STRIKE:	/* ナパームバルカンストライク */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SKE_ALL_IN_THE_SKY:	/* 天羅万象 */
		unit_heal(bl,0,0,-(status_get_ap(bl)),1);
		break;
	case SS_KAGEGARI:			/* 影狩り */
	case SS_FUUMASHOUAKU:		/* 風魔手裏剣 -掌握- */
	case SS_KUNAIWAIKYOKU:		/* 苦無 -歪曲- */
	case SS_ANTENPOU:			/* 暗転砲 */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
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
		if(sd && dstmd && mobdb_search(dstmd->class_)->race != RCT_DEMIHUMAN && !map[dstmd->bl.m].flag.nobranch &&
		   !(mobdb_search(dstmd->class_)->mode&MD_BOSS) && dstmd->class_ != MOBID_EMPERIUM && dstmd->state.special_mob_ai == MOB_AI_NONE)
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
		if(battle_config.boss_no_knockbacking==1 && mobdb_search(md->class_)->mode&MD_BOSS)
			return 0;
		if(battle_config.boss_no_knockbacking==2 && mobdb_search(md->class_)->mexp > 0)
			return 0;
		if(md->mode&MD_KNOCKBACKIMMUNITY)
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
int skill_area_temp[8];	/* 一時変数。必要なら使う。 */

int skill_area_sub( struct block_list *bl,va_list ap )
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

int skill_area_trap_sub( struct block_list *bl,va_list ap )
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
		case UNT_MAGENTATRAP:	/* マゼンタトラップ */
		case UNT_COBALTTRAP:	/* コバルトトラップ */
		case UNT_MAIZETRAP:		/* メイズトラップ */
		case UNT_VERDURETRAP:	/* ヴェルデュールトラップ */
		case UNT_FIRINGTRAP:	/* ファイアリングトラップ */
		case UNT_ICEBOUNDTRAP:	/* アイスバウンドトラップ */
		case UNT_CLUSTERBOMB:	/* クラスターボム */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN)
				break;
			return 0;
		case UNT_ANKLESNARE:	/* アンクルスネア */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN || unit->group->val2 > 0)
				break;
			return 0;
		case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
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
		case MH_STEINWAND:
			if(ug_id == MG_SAFETYWALL || ug_id == AL_PNEUMA || ug_id == MH_STEINWAND) {
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
		case RA_ELECTRICSHOCKER:	// エレクトリックショッカー
		case RA_CLUSTERBOMB:		// クラスターボム
		case RA_MAGENTATRAP:		// マゼンタトラップ
		case RA_COBALTTRAP:			// コバルトトラップ
		case RA_MAIZETRAP:			// メイズトラップ
		case RA_VERDURETRAP:		// ヴェルデュールトラップ
		case RA_FIRINGTRAP:			// ファイアリングトラップ
		case RA_ICEBOUNDTRAP:		// アイスバウンドトラップ
			if( (ug_id >= HT_SKIDTRAP && ug_id <= HT_CLAYMORETRAP) ||
			    (ug_id >= MA_SKIDTRAP && ug_id <= MA_FREEZINGTRAP) ||
			    ug_id == HT_TALKIEBOX ||
				(ug_id >= RA_ELECTRICSHOCKER && ug_id <= RA_CLUSTERBOMB) ||
				(ug_id >= RA_MAGENTATRAP && ug_id <= RA_ICEBOUNDTRAP) )
			{
				return 1;
			}
			break;
		case HP_BASILICA:
			if( (ug_id >= HT_SKIDTRAP && ug_id <= HT_CLAYMORETRAP) ||
			    (ug_id >= MA_SKIDTRAP && ug_id <= MA_FREEZINGTRAP) ||
			    ug_id == HT_TALKIEBOX ||
				(ug_id >= RA_ELECTRICSHOCKER && ug_id <= RA_CLUSTERBOMB) ||
				(ug_id >= RA_MAGENTATRAP && ug_id <= RA_ICEBOUNDTRAP) ||
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
int skill_area_sub_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(skill_area_temp[0] < 0xffff)
		skill_area_temp[0]++;
	return 1;
}

/*==========================================
 * 水場の数を数える
 *------------------------------------------
 */
int skill_count_water(struct block_list *src,int range)
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
int skill_partner_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(src->type != BL_PC || target->type != BL_PC)
		return 0;

	if(skill_area_temp[0] < 0xffff && (pc_get_base_job(((struct map_session_data *)target)->s_class.job,3) == PC_JOB_MI || pc_get_base_job(((struct map_session_data *)target)->s_class.job,3) == PC_JOB_WA) &&
		    ((struct map_session_data *)src)->status.party_id > 0 &&
		    ((struct map_session_data *)target)->status.party_id > 0 &&
		    ((struct map_session_data *)src)->status.party_id == ((struct map_session_data *)target)->status.party_id &&
		    !unit_isdead(target) )
		skill_area_temp[0]++;
	return 1;
}
/*=========================================================================
 * パーティ内のトルバドゥール、トルヴェールの数をカウントする。（skill_area_temp[0]を初期化しておくこと）
 *-------------------------------------------------------------------------
 */
int skill_4thpartner_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(src->type != BL_PC || target->type != BL_PC)
		return 0;

	if(skill_area_temp[0] < 0xffff && (pc_get_base_job(((struct map_session_data *)target)->s_class.job,4) == PC_JOB_TRB || pc_get_base_job(((struct map_session_data *)target)->s_class.job,4) == PC_JOB_TRV) &&
		    ((struct map_session_data *)src)->status.party_id > 0 &&
		    ((struct map_session_data *)target)->status.party_id > 0 &&
		    ((struct map_session_data *)src)->status.party_id == ((struct map_session_data *)target)->status.party_id &&
		    !unit_isdead(target) )
		skill_area_temp[0]++;
	return 1;
}
/*==========================================
* 範囲内に自身が配置した指定スキルユニットがあるかチェック(map_foreachinarea)
 *------------------------------------------
 */
static int skill_check_unit_id(struct block_list *bl,va_list ap)
{
	int src_id, skill_id;
	struct skill_unit *su;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, su = (struct skill_unit*)bl);

	src_id   = va_arg(ap,int);
	skill_id = va_arg(ap,int);

	if(su->group) {
		if(su->group->src_id == src_id && su->group->skill_id == skill_id)
			return 1;
	}

	return 0;
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
			if(skl->skill_id != RG_INTIMIDATE && skl->skill_id != NPC_EXPULSION) {
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
				range = skill_get_area(skl->skill_id,skl->skill_lv);
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
					if(lv > 0 && (((struct map_session_data *)src)->weapontype1 == WT_1HAXE || ((struct map_session_data *)src)->weapontype1 == WT_2HAXE))
						battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,1,tick,skl->flag);
				}
				break;
			case AB_DUPLELIGHT_MELEE:		/* グレイアムライト */
			case SR_CRESCENTELBOW:			/* 破碎柱 */
			case WM_REVERBERATION_MELEE:	/* 振動残響(物理) */
			case NPC_REVERBERATION_ATK:		/* M振動残響(攻撃) */
				battle_skill_attack(BF_WEAPON,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case AB_DUPLELIGHT_MAGIC:		/* ミリアムライト */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_CHAINLIGHTNING_ATK:		/* チェーンライトニング(連鎖) */
				{
					struct block_list *tbl = NULL;
					int c = 0;

					range = skill_get_area(skl->skill_id,skl->skill_lv);
					battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,(0x0f<<20)|skl->flag|skl->type);
					map_foreachinarea(skill_chainlightning,
						target->m,target->x-range,target->y-range,target->x+range,target->y+range,BL_CHAR,
						src,target->id,&tbl,&c);
					if(tbl && skl->type < skl->skill_lv + 4) {
						skill_addtimerskill(src,tick+650,tbl->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					} else if(skl->type < 4) {
						skill_addtimerskill(src,tick+650,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
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
			case SS_ANKOKURYUUAKUMU:		/* 幻術 -暗黒龍- */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_TETRAVORTEX_FIRE:		/* テトラボルテックス(火) */
			case WL_TETRAVORTEX_WATER:		/* テトラボルテックス(水) */
			case WL_TETRAVORTEX_WIND:		/* テトラボルテックス(風) */
			case WL_TETRAVORTEX_GROUND:		/* テトラボルテックス(地) */
				clif_skill_nodamage(src,target,skl->skill_id,skl->skill_lv,1);
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				if(range > 0) {
					map_foreachinarea(skill_area_sub,target->m,
						target->x-range,target->y-range,target->x+range,target->y+range,BL_CHAR,
						src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
						skill_castend_damage_id);
				}
				else{
					battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				}
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
			case NPC_PULSESTRIKE2:		/* パルスストライクIIの連撃 */
				skill_castend_damage_id(src,target,skl->skill_id,skl->skill_lv,tick,0);
				break;
			case NPC_DANCINGBLADE_ATK:		/* ダンシングブレイド(連鎖) */
				{
					struct block_list *tbl = NULL;
					int c = 0;

					range = skill_get_area(skl->skill_id,skl->skill_lv);
					battle_skill_attack(BF_WEAPON,src,src,target,skl->skill_id,skl->skill_lv,tick,(0x0f<<20)|skl->flag);
					map_foreachinarea(skill_chainlightning,
						target->m,target->x-range,target->y-range,target->x+range,target->y+range,BL_CHAR,
						src,target->id,&tbl,&c);
					if(tbl && skl->type < 5) {
						skill_addtimerskill(src,tick+650,tbl->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					} else if(skl->type < 5) {
						skill_addtimerskill(src,tick+650,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type+1,skl->flag);
					}
				}
				break;
			case SJ_FALLINGSTAR_ATK2:	/* 流星落下(追撃) */
				clif_skill_nodamage(src,target,skl->skill_id,skl->skill_lv,1);
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,target->m,
					target->x-range,target->y-range,target->x+range,target->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				break;
			case AG_DESTRUCTIVE_HURRICANE:		/* ディストラクティブハリケーン */
			case AG_CRYSTAL_IMPACT_ATK:	/* クリスタルインパクト(追撃) */
			case AG_CRIMSON_ARROW_ATK:	/* クリムゾンアロー(攻撃) */
			case CD_ARBITRIUM_ATK:		/* アルビトリウム(追撃) */
				skill_castend_damage_id(src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
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
				range=(skl->skill_lv>5)?AREA_SIZE: skill_get_area(skl->skill_id,skl->skill_lv);
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
			case SU_CN_METEOR2:				/* イヌハッカメテオ(呪い) */
			case HN_METEOR_STORM_BUSTER:	/* メテオストームバスター */
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
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS))
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,skl->flag);
				break;
			case WL_EARTHSTRAIN:    /* アースストレイン */
				{
					struct skill_unit_group *sg = NULL;
					sg = map_id2sg(skl->type);
					if(sg) {
						int x = skl->flag>>16, y = skl->flag&0xffff;
						if(map_getcell(src->m,x,y,CELL_CHKNOPASS)) {
							skill_delunitgroup(sg);
						} else {
							skill_unit_move_unit_group(sg,src->m,skl->x,skl->y);
						}
					}
				}
				break;
			case NC_MAGMA_ERUPTION:	/* マグマイラプション */
			case NPC_MAGMA_ERUPTION:	/* Mマグマイラプション */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
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
					range = skill_get_area(skl->skill_id,skl->skill_lv);
					map_foreachinarea(skill_delunit_by_ganbantein,
						src->m,skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_SKILL);
					skill_unitsetting(src,GN_CRAZYWEED_ATK,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			case RL_FIRE_RAIN:	/* ファイアーレイン */
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS)) {
					if(atn_rand()%100 < 20 * skl->skill_lv) {
						range = skill_get_area(skl->skill_id,skl->skill_lv);
						map_foreachinarea(skill_delunit_by_ganbantein,src->m,skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_SKILL);
					}
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			case NPC_WIDESUCK:		/* ワイドブラッド */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_nodamage_id);
				break;
			case NW_HASTY_FIRE_IN_THE_HOLE:	/* ヘイスティファイアインザホール */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				skill_area_temp[1] = skl->src_id;
				skill_area_temp[2] = skl->x;
				skill_area_temp[3] = skl->y;
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_damage_id);
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

		// 火山灰 不発判定
		if(sc && sc->data[SC_VOLCANIC_ASH].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 50)
			break;

		// 不幸 不発判定
		if(sc && sc->data[SC_HANDICAPSTATE_MISFORTUNE].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 25)
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
			if(!(mobdb_search(src_md->class_)->mode & MD_BOSS) && src_md->sc.data[SC_HERMODE].timer != -1)
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
		// 移動しながら使用可能なスキル
		if( src_ud->skillid != RA_WUGRIDER )	// ウォーグライダー
			unit_stop_walking(src,0);

		if(src_sd) {
			int cooldown = skill_cooldownfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);
			int delay    = skill_delayfix(&src_sd->bl, src_ud->skillid, src_ud->skilllv);
			int heal_ap  = skill_get_healap(src_ud->skillid, src_ud->skilllv);

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
			if((src_ud->skillid == TR_ROSEBLOSSOM || src_ud->skillid == TR_RHYTHMSHOOTING || src_ud->skillid == TR_METALIC_FURY || src_ud->skillid == TR_SOUNDBLEND) && pc_checkskill(src_sd,TR_STAGE_MANNER) >= 5)
				heal_ap += 1;
			if(src_sd->skill_used.id == TR_RETROSPECTION)	// 回想
				heal_ap *= 2;
			if(src_ud->skillid == SH_HOGOGONG_STRIKE && (pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO) || src_sd->sc.data[SC_TEMPORARY_COMMUNION].timer != -1))
				heal_ap += 1;
			if(src_ud->skillid == SH_HYUN_ROK_CANNON && (pc_checkskill(src_sd,SH_COMMUNE_WITH_HYUN_ROK) || src_sd->sc.data[SC_TEMPORARY_COMMUNION].timer != -1))
				heal_ap += 1;

			if(heal_ap > 0)
				pc_heal(src_sd,0,0,heal_ap,0);
		}

		// エモ、チャット
		if(src_md && src_md->skillidx != -1)
		{
			int i;
			struct mob_skill *ms = mobdb_search(src_md->class_)->skill;
			short emotion = ms[src_md->skillidx].emotion;
			short msg_id = ms[src_md->skillidx].msg_id;
			if(emotion >= 0)
				clif_emotion(&src_md->bl,emotion);
			if(msg_id > 0)
				mob_talk(src_md,msg_id);
			for(i=0; i<mobdb_search(src_md->class_)->maxskill; i++) {
				if(ms[i].skill_id == src_ud->skillid)
					src_md->skilldelay[i] = tick + ms[src_md->skillidx].delay;
			}
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
			     src_ud->skillid == AB_RENOVATIO ||
			     src_ud->skillid == AB_HIGHNESSHEAL) &&
			    battle_check_undead(status_get_race(target),status_get_elem_type(target)) &&
			    !(src_md && target->type == BL_MOB) )	// MOB→MOBならアンデッドでも回復
			{
				if( target->type != BL_PC ||
				    (src_md && src_md->skillidx >= 0 && !mobdb_search(src_md->class_)->skill[src_md->skillidx].val[0]) ) {
					skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
				} else if( map[src->m].flag.pvp || map[src->m].flag.gvg ) {
					if((src_ud->skillid == AL_HEAL || src_ud->skillid == AB_RENOVATIO || src_ud->skillid == AB_HIGHNESSHEAL) && battle_check_target(src,target,BCT_PARTY))
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
		if(src_sd && src_ud && src_sd->state.autoskill_flag) {
			int casttime = skill_castfix(src, src_ud->skillid, skill_get_cast(src_ud->skillid,src_ud->skilllv), skill_get_fixedcast(src_ud->skillid,src_ud->skilllv));
			int delay = skill_delayfix(src, src_ud->skillid, src_ud->skilllv);
			src_ud->canact_tick  = tick + casttime + delay;
			src_ud->canmove_tick = tick;
			src_ud->skilltarget  = target->id;
			src_ud->skillx       = 0;
			src_ud->skilly       = 0;
			src_ud->skillid      = src_ud->skillid;
			src_ud->skilllv      = src_ud->skilllv;
			src_ud->skilltimer = add_timer(src_ud->canact_tick, skill_castend_id, src->id, NULL);
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
		src_sd->state.autoskill_flag = false;
	} else if(src_md) {
		src_md->skillidx = -1;
	}

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

		// 火山灰 不発判定
		if(sc && sc->data[SC_VOLCANIC_ASH].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 50)
			break;
		// 不幸 不発判定
		if(sc && sc->data[SC_HANDICAPSTATE_MISFORTUNE].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 25)
			break;

		if(src_md) {
			if(src_md->sc.data[SC_ROKISWEIL].timer != -1)
				break;
			if(!(mobdb_search(src_md->class_)->mode & MD_BOSS) && src_md->sc.data[SC_HERMODE].timer != -1)
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
			if(src_md->sc.data[SC_HANDICAPSTATE_DEEPSILENCE].timer != -1)
				break;
			if(src_md->sc.data[SC_HANDICAPSTATE_FROSTBITE].timer != -1)
				break;
			if(src_md->sc.data[SC_HANDICAPSTATE_SWOONING].timer != -1)
				break;
			if(src_md->sc.data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1)
				break;
			if(src_md->sc.data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1)
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
			int heal_ap  = skill_get_healap(src_ud->skillid, src_ud->skilllv);

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
			if((src_ud->skillid == WH_DEEPBLINDTRAP || src_ud->skillid == WH_SOLIDTRAP || src_ud->skillid == WH_SWIFTTRAP || src_ud->skillid == WH_FLAMETRAP) && pc_checkskill(src_sd,WH_ADVANCED_TRAP) >= 3)
				heal_ap += 1;

			if(heal_ap > 0)
				pc_heal(src_sd,0,0,heal_ap,0);
		}

		// エモ、チャット
		if(src_md && src_md->skillidx != -1)
		{
			int i;
			struct mob_skill *ms = mobdb_search(src_md->class_)->skill;
			short emotion = ms[src_md->skillidx].emotion;
			short msg_id = ms[src_md->skillidx].msg_id;
			if(emotion >= 0)
				clif_emotion(&src_md->bl,emotion);
			if(msg_id > 0)
				mob_talk(src_md,msg_id);
			for(i=0; i<mobdb_search(src_md->class_)->maxskill; i++) {
				if(ms[i].skill_id == src_ud->skillid)
					src_md->skilldelay[i] = tick + ms[src_md->skillidx].delay;
			}
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
		clif_skill_fail(src_sd,src_ud->skillid,SKILLFAIL_FAILED,0,0);
		src_sd->skill_item.id     = -1;
		src_sd->skill_item.lv     = -1;
		src_sd->skill_item.flag   = 0;
	} else if(src_md) {
		src_md->skillidx = -1;
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
	    sd->sc.data[SC__IGNORANCE].timer != -1 ||
	    sd->sc.data[SC_HANDICAPSTATE_DEEPSILENCE].timer != -1 ||
		sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 ||
		sd->sc.data[SC_HANDICAPSTATE_SWOONING].timer != -1 ||
		sd->sc.data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 ||
		sd->sc.data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1 )
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
					clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_MORESKILL,0,0);
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
	interval  = skill_get_unit_interval(skillid,skilllv);
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
	case GS_DESPERADO:	/* デスペラード */
		val2 = flag;
		break;
	case GS_GROUNDDRIFT:	/* グラウンドドリフト */
		// flag = 弾の属性でUnitを決定
		switch(flag) {
		case ELE_WATER:
			unit_id = UNT_GROUNDDRIFT_WATER;
			val2 = ELE_WATER;
			break;
		case ELE_FIRE:
			unit_id = UNT_GROUNDDRIFT_FIRE;
			val2 = ELE_FIRE;
			break;
		case ELE_WIND:
			unit_id = UNT_GROUNDDRIFT_WIND;
			val2 = ELE_WIND;
			break;
		case ELE_POISON:
			unit_id = UNT_GROUNDDRIFT_POISON;
			val2 = ELE_POISON;
			break;
		case ELE_DARK:
			unit_id = UNT_GROUNDDRIFT_DARK;
			val2 = ELE_DARK;
			break;
		default:
			unit_id = UNT_GROUNDDRIFT_NEUTRAL;
			val2 = ELE_NEUTRAL;
			break;
		}
		break;
	case NPC_EVILLAND:		/* イービルランド */
		val1 = (skilllv > 6)? 666: skilllv*100;
		interval += 500;
		break;
	case NPC_VENOMFOG:			// ベナムフォグ
		if(src->type == BL_MOB)
			val1 = mobdb_search(((struct mob_data *)src)->class_)->atk1;
		else
			val1 = status_get_atk(src);
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
	case NPC_MAGMA_ERUPTION:	/* Mマグマイラプション */
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
	case AG_VIOLENT_QUAKE:		/* バイオレントクエイク */
		if(flag == 5) {		// クライマックスLv5：発動範囲が狭まる
			range -= 1;
		}
		val1 = flag;
		break;
	case AG_VIOLENT_QUAKE_ATK:	/* バイオレントクエイク(攻撃) */
		if(flag == 2) {		// クライマックスLv2：ダメージ範囲が拡大
			range *= 2;
		}
		val1 = flag;
		break;
	case AG_ALL_BLOOM:			/* オールブルーム */
		if(flag == 1) {		// クライマックスLv1：発動間隔が半分
			interval /= 2;
			limit /= 2;
		}
		val1 = flag;
		break;
	case AG_ALL_BLOOM_ATK:		/* オールブルーム(攻撃) */
		val1 = flag;
		break;
	case WH_DEEPBLINDTRAP:	/* ディープブラインドトラップ */
	case WH_SOLIDTRAP:		/* ソリッドトラップ */
	case WH_SWIFTTRAP:		/* スイフトトラップ */
	case WH_FLAMETRAP:		/* フレイムトラップ */
		if(sd && pc_checkskill(sd,WH_ADVANCED_TRAP) > 0) {
			limit += 500 + pc_checkskill(sd,WH_ADVANCED_TRAP) * 500;
		}
		break;
	case MH_STEINWAND:			/* シュタインワンド */
		val1 = 300*skilllv;
		if(sd && sd->hd) val1 += 65 * (sd->hom.int_ + sd->hom.base_level) + sd->hom.max_sp;
		val2 = skilllv+4;
		break;
	case MH_LAVA_SLIDE:			/* ラーヴァスライド */
		val2 = 5;
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
			case SO_FIREWALK:			/* ファイアーウォーク */
			case SO_ELECTRICWALK:		/* エレクトリックウォーク */
				val1 = 1 + atn_rand()%3;	// 回数
				break;
			case WM_REVERBERATION:	/* 振動残響 */
			case NPC_REVERBERATION:	/* M振動残響 */
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
			case RL_B_TRAP:			/* バインドトラップ */
			case NPC_EVILLAND:		/* イービルランド */
			case NPC_VENOMFOG:		/* ベナムフォグ */
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
		case UNT_B_TRAP:
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
		case UNT_B_TRAP:
			return 0;
		}
	}

	// 時間切れ間際は発動させないようにするか判定
	if(battle_config.skill_unit_interval_limit && ((sg->limit > 0 && DIFF_TICK(tick,sg->tick) >= sg->limit) || (src->limit > 0 && DIFF_TICK(tick,sg->tick) >= src->limit))) {
		return 0;
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
		status_change_start(bl,SC_PNEUMA,sg->skill_lv,src->bl.id,0,0,sg->interval+100,0);
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
						heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
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
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2|0x0500);
			break;
		case GN_CRAZYWEED_ATK:	/* クレイジーウィード */
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
		case WL_COMET:				/* コメット */
		case NPC_COMET:				/* Mコメット */
			{
				struct skill_unit *su = (struct skill_unit *)(sg->unit);
				if(su) {
					int dist = path_distance(bl->x,bl->y,su->bl.x,su->bl.y);
					clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,(dist > 7)? 3: (dist > 5)? 2: (dist > 3)? 1: 0);
				}
			}
			break;
		case AG_VIOLENT_QUAKE_ATK:		/* バイオレントクエイク(攻撃) */
		case AG_ALL_BLOOM_ATK:			/* オールブルーム(攻撃) */
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val1);
			break;
		case SKE_STAR_BURST:			/* 天命落星 */
		case SS_KUNAIKAITEN:			/* 苦無 -回転- */
		case SS_KUNAIKUSSETSU:			/* 苦無 -屈折- */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			break;
		default:
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_EARTHSTRAIN:	/* アースストレイン */
	case UNT_PSYCHIC_WAVE:	/* サイキックウェーブ */
	case UNT_CLOUD_KILL:	/* クラウドキル */
	case UNT_POISON_MIST:	/* ポイズンミスト */
	case UNT_RAIN_OF_CRYSTAL:	/* レインオブクリスタル */
	case UNT_MYSTERY_ILLUSION:	/* ミステリーイリュージョン */
	case UNT_STRANTUM_TREMOR:	/* ストラタムトレマー */
	case UNT_TORNADO_STORM:		/* トルネードストーム */
	case UNT_FLORAL_FLARE_ROAD:	/* フローラルフレアロード */
	case UNT_CROSS_RAIN:	/* クロスレイン */
	case UNT_PNEUMATICUS_PROCELLA:	/* ニューマティックプロセラ */
	case UNT_LIGHTNING_LAND:	/* ライトニングランド */
	case UNT_VENOM_SWAMP:		/* ベナムスワンプ */
	case UNT_CONFLAGRATION:		/* コンフラグレーション */
	case UNT_HYUN_ROKS_BREEZE:	/* ディアーブリーズ */
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
	case UNT_FIRINGTRAP:		/* ファイアリングトラップ */
	case UNT_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		{
			int splash_count = 0;
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			int sec;

			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: 1500;
			splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
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
				pc_heal(sd,-hp,-sp,0,0);
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
	case UNT_GROUNDDRIFT_NEUTRAL:
#ifdef PRE_RENEWAL
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
#else
		int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
		map_foreachinarea(skill_trap_splash,src->bl.m,
					src->bl.x-ar,src->bl.y-ar,
					src->bl.x+ar,src->bl.y+ar,
					(BL_CHAR|BL_SKILL),src,tick,1);
#endif
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
		if(atn_rand() % 10000 < status_change_rate(bl,sg->val1,5000,status_get_lv(&src->bl)))
			status_change_start(bl,sg->val1,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_EPICLESIS:	/* エピクレシス */
		if(battle_check_target(&src->bl,bl,BCT_NOENEMY)) {
			status_change_start(bl,SC_EPICLESIS,sg->skill_lv,0,0,0,sg->interval+100,0);
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
		skill_detect(bl);		// ディティクト効果
		break;
	case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		{
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			unit_movepos(bl, src->bl.x, src->bl.y, 0);		// 踏んだ対象者のみ移動
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			//clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_CLUSTERBOMB:		/* クラスターボム */
		// 効果範囲(設置禁止領域)ではなく罠上に重なったら発動
		if(src->bl.m == bl->m && src->bl.x == bl->x && src->bl.y == bl->y){
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 1000;
		}
		break;
	case UNT_MAGMA_ERUPTION:	/* マグマイラプション */
		if(sg->skill_id == NC_MAGMA_ERUPTION)
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		else
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NPC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
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
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			int splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
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
		if(--src->val1 <= 0)
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
	case UNT_B_TRAP:		/* バインドトラップ */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_FIRE_RAIN:		/* ファイアーレイン */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		break;
	case UNT_CATNIPPOWDER:	/* イヌハッカシャワー */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		break;
	case UNT_NYANGGRASS:	/* ニャングラス */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_NYANGGRASS].timer == -1)
				status_change_start(bl,SC_NYANGGRASS,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_VENOMFOG:	/* ベナムフォグ */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,NPC_VENOMFOG,sg->skill_lv,tick,0);
		} else if(bl->type == BL_MOB) {
			if(status_get_hp(bl) < status_get_max_hp(bl)) {
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,sg->val1*sg->skill_lv,1);
				battle_heal(NULL,bl,sg->val1*sg->skill_lv,0,0);
			}
		}
		break;
	case UNT_CANE_OF_EVIL_EYE:		/* ケーンオブイビルアイ */
		// 初回ダメージが出ない？
		if(sg->val2 == 1 && battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,NPC_CANE_OF_EVIL_EYE,sg->skill_lv,tick,0x500);
		sg->val2 = 1;
 		break;
	case UNT_LAVA_SLIDE:			/* ラーヴァスライド */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,MH_LAVA_SLIDE,sg->skill_lv,tick,0);
		if(--sg->val2 <= 0)
			skill_delunitgroup(sg);
		break;
	case UNT_VOLCANIC_ASH:		/* ボルカニックアッシュ */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_VOLCANIC_ASH].timer == -1)
				status_change_start(bl,SC_VOLCANIC_ASH,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_CREATINGSTAR:	/* 創星の書 */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		status_change_start(bl,SC_CREATINGSTAR,sg->skill_lv,0,0,0,sg->interval+100,0);
		break;
	case UNT_VIOLENT_QUAKE:	/* バイオレントクエイク */
	case UNT_ALL_BLOOM:		/* オールブルーム */
		if(sg->val1 == 4) {		// クライマックスLv4：発動範囲内の敵を状態異常
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_ASTRAL_STRIKE:		/* アストラルストライク */
		if(DIFF_TICK(tick,sg->tick) >= 500) {	// 設置直後は攻撃なし
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_ABYSS_SQUARE:		/* アビススクエア */
		{
			int ismaster = 0;
			struct skill_unit *su = (struct skill_unit *)(sg->unit);
			if(su) {
				if(path_distance(su->bl.x,su->bl.y,ss->x,ss->y) <= src->range) {
					ismaster = 1;
				}
			}
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,ismaster);
		}
		break;
	case UNT_DEEPBLIND_TRAP:	/* ディープブラインドトラップ */
	case UNT_SOLID_TRAP:		/* ソリッドトラップ */
	case UNT_SWIFT_TRAP:		/* スイフトトラップ */
	case UNT_FLAME_TRAP:		/* フレイムトラップ */
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer != -1)
			break;
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_ACIDIFIED_ZONE_WATER:		/* アシディファイドゾーン(水) */
	case UNT_ACIDIFIED_ZONE_GROUND:		/* アシディファイドゾーン(地) */
	case UNT_ACIDIFIED_ZONE_WIND:		/* アシディファイドゾーン(風) */
	case UNT_ACIDIFIED_ZONE_FIRE:		/* アシディファイドゾーン(火) */
	case UNT_FUUMASHOUAKU:				/* 風魔手裏剣 -掌握- */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_TOTEM_OF_TUTELARY:			/* 城隍堂 */
		if(sg->val1%2 == 0 || sg->val1%3 == 0){
			struct map_session_data *sd = (struct map_session_data *)ss;
			int hp = 0;
			int sp = 0;
			if(sg->val1%2 == 0) {
				hp = skill_fix_heal(ss, bl, AL_HEAL, skill_calc_heal(ss, sg->skill_lv));
				hp += (1000 + sg->skill_lv * 4000 + status_get_crt(ss) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * sg->skill_lv * 50: 0)) * status_get_lv(ss) / 100;
			}
			if(sg->val1%3 == 0) {
				sp = (sg->skill_lv * 50 + status_get_crt(ss) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * sg->skill_lv * 5: 0)) * status_get_lv(ss) / 100;
			}
			unit_heal(bl,hp,sp,0,1);
		}
		break;
	case UNT_JACK_FROST_NOVA:		/* ジャックフロストノヴァ */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,1);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_GROUND_GRAVITATION:	/* グラウンドグラビテーション */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,2);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
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
	case UNT_NYANGGRASS:	/* ニャングラス */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_NYANGGRASS].timer != -1 && sc->data[SC_NYANGGRASS].val2 == src->bl.id)
			status_change_end(bl,SC_NYANGGRASS,-1);
		break;
	case UNT_CREATINGSTAR:	/* 創星の書 */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_CREATINGSTAR].timer != -1 && sc->data[SC_CREATINGSTAR].val2 == src->bl.id){
			sc->data[SC_CREATINGSTAR].val4 = 0;
			status_change_end(bl,SC_CREATINGSTAR,-1);
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
			sc->data[SC_DIAMONDDUST].timer != -1 ||
			sc->data[SC_NOVAEXPLOSING].timer != -1 ||
			sc->data[SC_GRAVITYCONTROL].timer != -1 ||
			sc->data[SC_HANDICAPSTATE_DEEPSILENCE].timer != -1 ||
			sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 ||
			sc->data[SC_HANDICAPSTATE_SWOONING].timer != -1 ||
			sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 ||
			sc->data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1 ||
			sc->data[SC_KI_SUL_RAMPAGE].timer != -1)
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
				switch(cnd->id) {
				case BD_ADAPTATION:
				case BA_MUSICALSTRIKE:
				case DC_THROWARROW:
				case CG_LONGINGFREEDOM:
				case TR_RETROSPECTION:		// 回想
				case TR_MYSTIC_SYMPHONY:	// ミスティックシンフォニー
				case TR_KVASIR_SONATA:		// ソナタオブクヴァシル
				case TR_ROSEBLOSSOM:		// ロゼブロッサム
				case TR_RHYTHMSHOOTING:		// リズムシューティング
				case TR_METALIC_FURY:		// メタリックフューリー
				case TR_SOUNDBLEND:			// サウンドブレンド
				case TR_GEF_NOCTURN:		// ゲフェニアノクターン
				case TR_ROKI_CAPRICCIO:		// ロキの気まぐれ
				case TR_AIN_RHAPSODY:		// 鉱員のラプソディ
				case TR_MUSICAL_INTERLUDE:	// ミュージカルインタールード
				case TR_JAWAII_SERENADE:	// 夕焼けのセレナーデ
				case TR_NIPELHEIM_REQUIEM:	// 死者たちへのレクイエム
				case TR_PRON_MARCH:			// プロンテラマーチ
					break;
				default:
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
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
			case SL_ALCHEMIST:   if(pc_get_base_job(job,2) != PC_JOB_AM) fail = 1; break; // アルケミストの魂
			case SL_MONK:        if(pc_get_base_job(job,2) != PC_JOB_MO) fail = 1; break; // モンクの魂
			case SL_STAR:        if(pc_get_base_job(job,2) != PC_JOB_SG) fail = 1; break; // ケンセイの魂
			case SL_SAGE:        if(pc_get_base_job(job,2) != PC_JOB_SA) fail = 1; break; // セージの魂
			case SL_CRUSADER:    if(pc_get_base_job(job,2) != PC_JOB_CR) fail = 1; break; // クルセイダーの魂
			case SL_SUPERNOVICE: if(pc_get_base_job(job,1) != PC_JOB_SNV) fail = 1; break; // スーパーノービスの魂
			case SL_KNIGHT:      if(pc_get_base_job(job,2) != PC_JOB_KN) fail = 1; break; // ナイトの魂
			case SL_WIZARD:      if(pc_get_base_job(job,2) != PC_JOB_WZ) fail = 1; break; // ウィザードの魂
			case SL_PRIEST:      if(pc_get_base_job(job,2) != PC_JOB_PR) fail = 1; break; // プリーストの魂
			case SL_BARDDANCER:  if(pc_get_base_job(job,2) != PC_JOB_BA && pc_get_base_job(job,2) != PC_JOB_DC) fail = 1; break; // バードとダンサーの魂
			case SL_ROGUE:       if(pc_get_base_job(job,2) != PC_JOB_RG) fail = 1; break; // ローグの魂
			case SL_ASSASIN:     if(pc_get_base_job(job,2) != PC_JOB_AS) fail = 1; break; // アサシンの魂
			case SL_BLACKSMITH:  if(pc_get_base_job(job,2) != PC_JOB_BS) fail = 1; break; // ブラックスミスの魂
			case SL_HUNTER:      if(pc_get_base_job(job,2) != PC_JOB_HT) fail = 1; break; // ハンターの魂
			case SL_SOULLINKER:  if(pc_get_base_job(job,2) != PC_JOB_SL) fail = 1; break; // ソウルリンカーの魂
			case SL_HIGH:        if(job < PC_JOB_SM || job > PC_JOB_TF || target_sd->s_class.upper != PC_UPPER_HIGH) fail = 1; break; // 転生一次職業の魂
			default: fail = 1;
		}
		if(battle_config.job_soul_check && fail) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
		return 0;

	case MO_KITRANSLATION:	/* 気功転移 */
		if( !target_sd ||
		    bl == target ||
		    target_sd->status.party_id <= 0 ||
		    status_get_party_id(bl) != target_sd->status.party_id ||
			pc_get_base_job(target_sd->s_class.job,1) == PC_JOB_GS )
		{
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
			if(skill_check_unit_range2(bl->m,bl->x,bl->y,cnd->id,cnd->lv)) {
				if(sd)
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
		return 0;

	case AM_TWILIGHT1:
		if(!sc || sc->data[SC_ALCHEMIST].timer == -1) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case AM_BERSERKPITCHER:
		if(target_sd && target_sd->status.base_level < 85) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case CR_PROVIDENCE:	// プロヴィデンス
		if(!target_sd)
			return 0;
		if(target_sd->s_class.job == PC_JOB_CR || target_sd->s_class.job == PC_JOB_LG) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case HP_ASSUMPTIO:	// アスムプティオ
	case CASH_ASSUMPTIO:	// パーティーアスムプティオ
		if(map[bl->m].flag.gvg && !battle_config.allow_assumptop_in_gvg) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SR_POWERVELOCITY:	/* 全気注入 */
		if( !target_sd ||
		    bl == target ||
		    target_sd->status.class_ == PC_CLASS_GS )
		{
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
	int i,hp,sp,ap,hp_rate,sp_rate,ap_rate,zeny,weapon,state,spiritball,coin,skilldb_id,arrow;
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];
	int item_nocost = 0;
	int soulenergy = 0, servantweapon = 0;
	struct block_list *bl = NULL, *target = NULL;
	struct unit_data  *ud = NULL;
	struct status_change *sc = NULL, *tsc = NULL;

	nullpo_retr(0, sd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, bl = &sd->bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	target = map_id2bl( cnd->target );
	sc = status_get_sc(bl);
	if(target != NULL) tsc = status_get_sc(target);

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
	if(pc_get_base_job(sd->s_class.job,2) == PC_JOB_SL) {
		switch(cnd->id) {
			case TK_READYSTORM:
			case TK_READYDOWN:
			case TK_READYTURN:
			case TK_READYCOUNTER:
			case TK_JUMPKICK:
				if( battle_config.soul_linker_battle_mode == 0 ||
				    (battle_config.soul_linker_battle_mode == 1 && sd->sc.data[SC_SOULLINKER].timer == -1) ) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
				break;
			case SL_KAIZEL:		/* カイゼル */
			case SL_KAAHI:		/* カアヒ */
			case SL_KAITE:		/* カイト */
			case SL_KAUPE:		/* カウプ */
				if(target == NULL || target->type != BL_PC) {
					// 対象が人以外失敗
					clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MSGID,0x75e,0);	// 騎乗生物に騎乗中は、スキル使用ができません。
				return 0;
		}
	}

	// 魔導ギア搭乗時
	if(pc_isgear(sd)) {
		switch(cnd->id) {
		// マーチャント系スキル
		case MC_IDENTIFY:			// アイテム鑑定
		case MC_VENDING:			// 露店開設
		case MC_MAMMONITE:			// メマーナイト
		// ブラックスミス系スキル
		case BS_REPAIRWEAPON:		// 武器修理
		case BS_HAMMERFALL:			// ハンマーフォール
		case BS_ADRENALINE:			// アドレナリンラッシュ
		case BS_WEAPONPERFECT:		// ウェポンパーフェクション
		case BS_OVERTHRUST:			// オーバートラスト
		case BS_MAXIMIZE:			// マキシマイズパワー
		case BS_ADRENALINE2:		// フルアドレナリンラッシュ
		case BS_GREED:				// グリード
		// ホワイトスミス系スキル
		case WS_MELTDOWN:			// メルトダウン
		case WS_CARTBOOST:			// カートブースト
		case WS_WEAPONREFINE:		// 武器精錬
		case WS_CARTTERMINATION:	// カートターミネーション
		case WS_OVERTHRUSTMAX:		// オーバートラストマックス
		// メカニック追加スキル
		case NC_MAGMA_ERUPTION:		//マグマイラプション
		// マイスター追加スキル
		case MT_MIGHTY_SMASH:		// マイティスマッシュ
		// その他
		case AL_TELEPORT:			// テレポート
		case ALL_BUYING_STORE:		// 買取露店開設
			break;
		default:
			// メカニックスキルはまとめて判定
			if(cnd->id >= NC_BOOSTKNUCKLE && cnd->id <= NC_DISJOINT)
				break;
			// マイスタースキルはまとめて判定
			if(cnd->id >= MT_AXE_STOMP && cnd->id <= MT_SUMMON_ABR_INFINITY)
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MADOGEAR_RIDE,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
	} else {
		if(sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
	}
	if(pc_is90overweight(sd)) {
		clif_skill_fail(sd,cnd->id,SKILLFAIL_WEIGHTOVER,0,0);
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
	ap         = skill_get_ap(cnd->id, cnd->lv);	/* 消費AP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	ap_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].ap_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	weapon     = skill_db[skilldb_id].weapon;
	state      = skill_db[skilldb_id].state;
	spiritball = (cnd->lv <= 0)? 0: skill_db[skilldb_id].spiritball[cnd->lv-1];
	coin       = (cnd->lv <= 0)? 0: skill_db[skilldb_id].coin[cnd->lv-1];
	arrow      = skill_get_arrow_cost(cnd->id,cnd->lv);

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// スキルLv毎の消費アイテム
	if(cnd->lv > 0 && cnd->lv <= MAX_SKILL_LEVEL) {
		itemid[i] = skill_db[skilldb_id].lv_itemid[cnd->lv-1];
		amount[i] = skill_db[skilldb_id].lv_amount[cnd->lv-1];
	}
	else {
		itemid[i] = 0;
		amount[i] = 0;
	}

	if(hp_rate > 0)
		hp += sd->status.hp * hp_rate / 100;
	else
		hp += sd->status.max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += sd->status.sp * sp_rate / 100;
	else
		sp += sd->status.max_sp * abs(sp_rate) / 100;
	if(ap_rate > 0)
		ap += sd->status.ap * ap_rate / 100;
	else
		ap += sd->status.max_ap * abs(ap_rate) / 100;

	if(sd->skill_used.id == BD_ENCORE && cnd->id == sd->skill_dance.id)	// アンコール時はSP消費が半分
		sp /= 2;
	if(sd->skill_used.id == TR_RETROSPECTION && cnd->id == sd->skill_4thdance.id)	// 回想時はSP消費が半分
		sp /= 2;
	if(sd->sc.data[SC_RECOGNIZEDSPELL].timer!=-1)		// リゴグナイズドスペル時は消費SP25%増加
		sp = sp * 125 / 100;
	if(sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].timer != -1) {	// エンドレスハミングボイス時は消費SP～15%増加
		int cost = 15;
		cost -= sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].val4 * 3;
		if(cost > 0)
			sp = sp * (100 + cost) / 100;
	}
	if(sd->sc.data[SC_HANDICAPSTATE_DEPRESSION].timer!=-1)		// 憂鬱時は消費SP3倍
		sp *= 3;
	if(sd->skill_addspcost.count > 0) {		// カードによるSP使用量増加
		for(i=0; i<sd->skill_addspcost.count; i++) {
			if(cnd->id == sd->skill_addspcost.id[i])
				sp += sd->skill_addspcost.rate[i];
		}
	}

#ifndef PRE_RENEWAL
	if(spiritball > 0)
		sd->spiritball.old = 0;
#endif

	// ソウルリーパーのスキルはspiritball要求をsoulenergyに置き換える
	if(cnd->id >= SP_SOULGOLEM && cnd->id <= SP_KAUTE && spiritball > 0) {
		soulenergy = spiritball;
		spiritball = 0;
	}

	// ドラゴンナイトのスキルはspiritball要求をservantweaponに置き換える
	if(cnd->id >= DK_SERVANTWEAPON && cnd->id <= DK_STORMSLASH && spiritball > 0) {
		servantweapon = spiritball;
		spiritball = 0;
	}

	switch( cnd->id ) {
	case SL_SMA:	/* エスマ */
		if(!(type&1) && sd->sc.data[SC_SMA].timer==-1){	// エスマ詠唱可能状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CG_LONGINGFREEDOM:
		// 合奏以外使えない
		if(sd->sc.data[SC_DANCING].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		} else {
			int dance_id = sd->sc.data[SC_DANCING].val1;
			if( (dance_id >= BA_WHISTLE && dance_id <= BA_APPLEIDUN) ||
			    (dance_id >= DC_HUMMING && dance_id <= DC_SERVICEFORYOU) ||
			    dance_id == CG_MOONLIT || dance_id == CG_HERMODE )
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
				return 0;
			}
		}
		break;
	case CG_MOONLIT:			/* 月明りの下で */
		{
			int x1,x2,y1,y2,j;
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case RA_WUGDASH:	// ウォーグダッシュ
		if(!pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SWHOO:	/* エスフ */
		if(!(type&1) && sd->sc.data[SC_SWHOO].timer == -1){	// エスフ詠唱可能状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
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
		case WH_CRESCIVE_BOLT:		/* クレッシブボルト */
			if(sd->sc.data[SC_CRESCIVEBOLT].timer != -1) {
				if(sd->sc.data[SC_CRESCIVEBOLT].val1 == 1) {
					sp += sp * 20 / 100;
				} else if(sd->sc.data[SC_CRESCIVEBOLT].val1 == 2) {
					sp += sp * 40 / 100;
				} else {
					sp += sp * 60 / 100;
				}
			}
			break;
	}
#ifndef PRE_RENEWAL
	// バードとダンサーの魂
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
		sp += sp * 50 / 100;	/* 消費SP増加 */
	// ウィザードの魂
	if(sd->sc.data[SC_WIZARD].timer != -1) {
		for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
			if(itemid[i] <= 0)
				continue;
			if(itemid[i] == 717)
				sp += sp * 50 / 100;	/* 消費SP増加 */
		}
	}
#endif

	if(sd->dsprate!=100)
		sp=sp*sd->dsprate/100;	/* 消費SP修正 */

	// マスカレード：レイジネス
	if(sd->sc.data[SC__LAZINESS].timer != -1)
		sp += sd->sc.data[SC__LAZINESS].val1 * 10;	/* 消費SP増加 */

	// マスカレード：アンラッキー
	if(sd->sc.data[SC__UNLUCKY].timer != -1)
		zeny += 1000;			/* 消費zeny増加 */

	switch(cnd->id) {
	case SA_CASTCANCEL:
	case SO_SPELLFIST:
		if(ud->skilltimer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
	case ML_AUTOGUARD:
	case KO_YAMIKUMO:		/* 闇雲 */
	case IG_GUARD_STANCE:		/* ガードスタンス */
	case IG_ATTACK_STANCE:		/* アタックスタンス */
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
					clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLPARENT:		/* ママ、パパ、来て */
		if(!sd->status.parent_id[0] && !sd->status.parent_id[1]){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLBABY:		/* 坊や、いらっしゃい */
		if(!sd->status.baby_id){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(sd->hom.homun_id > 0) {	// 作成済みホムが居る時にエンブリオ持ってたら失敗
			for(i=0; i<MAX_INVENTORY; i++) {
				if(sd->status.inventory[i].nameid == 7142) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
		break;
	case AM_REST:			/* 安息 */
		if(!homun_isalive(sd) || status_get_hp(&sd->hd->bl) < sd->hd->max_hp * 80 / 100) {
			// ホムのHPがMHPの80%以上であること
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case AM_RESURRECTHOMUN:			/* リザレクションホムンクルス */
		if(sd->hd || sd->hom.hp > 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GVGONLY,0,0);
			return 0;
		}
		// WPチェック？
		if(battle_config.hermode_wp_check && !skill_hermode_wp_check(bl))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_SUN_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[0]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_SUN_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[0] && (battle_config.allow_skill_without_day || is_day_of_sun()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_MOON_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[1]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_MOON_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[1] && (battle_config.allow_skill_without_day || is_day_of_moon()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_STAR_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[2]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_STAR_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[2] && (battle_config.allow_skill_without_day || is_day_of_star()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_HATE:
		if(status_get_class(target) == MOBID_EMPERIUM) {	// エンペは登録不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SG_FUSION:
		if(sd->sc.data[SC_FUSION].timer != -1) {	// 解除するときはsp消費なし
			sp = 0;
		}
		if(sd->sc.data[SC_STAR].timer == -1) {	// ケンセイの魂状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case PR_REDEMPTIO:
		if(battle_config.redemptio_penalty_type) {
			atn_bignumber exp = pc_nextbaseexp(sd);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_EXP,0,0);
				return 0;
			}
		}
		break;
	case GS_GLITTERING:		/* フリップザコイン */
		if(sd->coin.num >= MAX_COIN) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GS_FLING:		/* フライング */
		if(sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COIN,coin,0);
			return 0;
		}
		coin = 0;	// コインは状態付与時に消費させる
		break;
	case GS_MADNESSCANCEL:	/* マッドネスキャンセラー */
		if(sd->sc.data[SC_ADJUSTMENT].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		else if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {
			// 解除する場合は消費しない
			sp = 0;
			coin = 0;
		}
		break;
	case GS_ADJUSTMENT:		/* アジャストメント */
		if(sd->sc.data[SC_MADNESSCANCEL].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case HT_POWER:			/* ビーストストレイフィング */
		if(sd->sc.data[SC_DOUBLE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case RK_GIANTGROWTH:	// ジャイアントグロース
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 1) {		// ルーンマスタリーLv1が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_VITALITYACTIVATION:	// バイタリティアクティベーション
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 2) {		// ルーンマスタリーLv2が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STORMBLAST:		// ストームブラスト
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 3) {		// ルーンマスタリーLv3が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STONEHARDSKIN:	// ストーンハードスキン
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 4) {		// ルーンマスタリーLv4が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_FIGHTINGSPIRIT:	// ファイティングスピリット
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 5) {		// ルーンマスタリーLv5が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_ABUNDANCE:		// アバンダンス
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 6) {		// ルーンマスタリーLv6が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_CRUSHSTRIKE:	// クラッシュストライク
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 7) {		// ルーンマスタリーLv7が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_REFRESH:	// リフレッシュ
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 8) {		// ルーンマスタリーLv8が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_MILLENNIUMSHIELD:	// ミレニアムシールド
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 9) {		// ルーンマスタリーLv9が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_LUXANIMA:	// ラクスアニマ
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 10) {		// ルーンマスタリーLv10が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_WEAPONBLOCKING:	/* ウェポンブロッキング */
		if(sd->sc.data[SC_WEAPONBLOCKING].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_COUNTERSLASH:		/* カウンタースラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_WEAPONCRUSH:		/* ウェポンクラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCKING_POSTDELAY].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_VENOMPRESSURE:		/* ベナムプレッシャー */
	case GC_POISONSMOKE:		/* ポイズンスモーク */
		if(sd->sc.data[SC_POISONINGWEAPON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_POISONINGWEAPON,0,0);
			return 0;
		}
		break;
	case GC_CLOAKINGEXCEED:	/* クローキングエクシード */
		if(sd->sc.data[SC_CLOAKINGEXCEED].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
		if(sd->sc.data[SC_HALLUCINATIONWALK].timer != -1 || sd->sc.data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_CROSSRIPPERSLASHER:		/* クロスリッパースラッシャー */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case AB_ANCILLA:			/* アンシラ */
		{
			int idx = pc_search_inventory(sd,12333);
			if(idx >= 0 && sd->status.inventory[idx].amount >= 3 ) {	/* 作成前に所持限界数を超えている */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_ANCILLAOVER,0,0);
				return 0;
			}
		}
		break;
	case WL_TETRAVORTEX:		/* テトラボルテックス */
		{
			int c = 0;
			for(i = 0; i < 5; i++) {
				if(sd->sc.data[SC_SUMMONBALL1 + i].timer != -1) {
					c++;
				}
			}
			if(c < 4) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_NOTHING,0,0);
				return 0;
			}
		}
		break;
	case WL_SUMMONFB:		/* サモンファイアボール */
	case WL_SUMMONBL:		/* サモンボールライトニング */
	case WL_SUMMONWB:		/* サモンウォーターボール */
	case WL_SUMMONSTONE:	/* サモンストーン */
		for(i = 0; i < 5; i++) {
			if(sd->sc.data[SC_SUMMONBALL1 + i].timer == -1)
				break;
		}
		if(i >= 5) {	// 召喚数がいっぱい
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
			return 0;
		}
		break;
	case RA_CAMOUFLAGE:		/* カモフラージュ */
		if(sd->sc.data[SC_CAMOUFLAGE].timer != -1) {
			sp = 0;		// 解除する場合はSP消費しない
		}
		// Lv1～2は壁付近チェック
		else if(cnd->lv < 3) {
			int i;
			for(i=0; i<8;i++){
				if(map_getcell(bl->m,bl->x+dirx[i],bl->y+diry[i],CELL_CHKNOPASS))
					break;
			}
			if(i >= 8) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEERWALL,0,0);
				return 0;
			}
		}
		break;
	case NC_PILEBUNKER:			/* パイルバンカー */
		{
			// パイルバンカーの装備チェック
 			static const int pile_item[] = { 1549, 16044, 16045, 16046 };		// パイルバンカー系列の装備品
			static const int pile_max = sizeof(pile_item)/sizeof(pile_item[0]);
			for(i = 0; i < pile_max; i++) {
				if(pc_equippeditem(sd,pile_item[i]))
					break;	// 装備していたら判定OK
			}
			if(i >= pile_max) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,pile_item[0]);
				return 0;
			}
		}
		break;
	case NC_HOVERING:			/* ホバーリング */
		// ホバーリングブースターを装備しているか判定
		if(pc_equippeditem(sd,2801) == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,2801);
			return 0;
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
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
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
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,0,0);
			return 0;
		}
		break;
	case LG_PRESTIGE:	/* プレスティージ */
	case LG_BANDING:	/* バンディング */
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case LG_HESPERUSLIT:	/* ヘスペルスリット */
		if(sd->sc.data[SC_INSPIRATION].timer == -1 && (sd->sc.data[SC_BANDING].timer == -1 || sd->sc.data[SC_BANDING].val2 < 3)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case LG_INSPIRATION:	/* インスピレーション */
		if(sd->sc.data[SC_PRESTIGE].timer != -1 || sd->sc.data[SC_BANDING].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case SR_FALLENEMPIRE:		/* 大纏崩捶 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SR_DRAGONCOMBO) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SR_DRAGONCOMBO,0);
			return 0;
		}
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer != -1 || sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_TIGERCANNON:		/* 號砲 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_RAMPAGEBLASTER:		/* 爆気散弾 */
		if(sd->spiritball.num) {
			sd->spiritball.old = sd->spiritball.num;
			if(sd->sc.data[SC_MASSIVE_F_BLASTER].timer != -1) {
				spiritball = 0;
			} else {
				spiritball = sd->spiritball.num;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,0,0);
			return 0;
		}
		break;
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		if(sd->status.sp < sd->status.max_sp * 30 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
			return 0;
		}
		break;
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
		if(sd->sc.data[SC_MASSIVE_F_BLASTER].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_FLASHCOMBO:		/* 閃光連撃 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
				return 0;
			}
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				if(!(type&1)){
					map_foreachinarea(skill_check_condition_char_sub,bl->m,
						bl->x-15,bl->y-15,
						bl->x+15,bl->y+15,BL_PC,sd,&c,cnd);
					if(c<1){
						clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
						return 0;
					}
				}else{
					map_foreachinarea(skill_check_condition_use_sub,bl->m,
						bl->x-15,bl->y-15,
						bl->x+15,bl->y+15,BL_PC,sd,&c);
				}
			}
		}
		break;
	case SO_POISON_BUSTER:	/* ポイズンバスター */
		if(target) {
			struct status_change *sc = status_get_sc(target);

			if(sc && sc->data[SC_POISON].timer == -1) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		if(!map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
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
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case SO_EL_CURE:	/* エレメンタルキュアー */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		if(sd->status.sp < sd->status.max_sp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
			return 0;
		}
		if(sd->status.hp < sd->status.max_hp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
			return 0;
		}
		break;
	case KO_KAHU_ENTEN:	/* 火符‐炎天 */
	case KO_HYOUHU_HUBUKI:	/* 氷符‐吹雪 */
	case KO_KAZEHU_SEIRAN:	/* 風符‐青嵐 */
	case KO_DOHU_KOUKAI:	/* 土符‐剛塊 */
		if(sd->elementball.num >= MAX_ELEMENTBALL) {
			if(sd->elementball.ele == skill_get_pl(cnd->id)) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
				return 0;
			}
		}
		break;
	case KO_KAIHOU:	/* 術式解放 */
	case KO_ZENKAI:	/* 術式全開 */
		if(sd->elementball.num < 1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_NOTHING,0,0);
			return 0;
		}
		break;
	case RL_B_TRAP:	/* バインドトラップ */
		/* 数制限 */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;
	case RL_QD_SHOT:			/* クイックドローショット */
		if(sd->sc.data[SC_QD_SHOT_READY].timer == -1 || sd->sc.data[SC_QD_SHOT_READY].val2 == sd->bl.id)
			return 0;
		break;
	case GD_BATTLEORDER:		/* 臨戦態勢 */
	case GD_REGENERATION:		/* 激励 */
	case GD_RESTORE:		/* 治療 */
	case GD_EMERGENCYCALL:		/* 緊急招集 */
		if(!battle_config.guild_skill_available) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(battle_config.allow_guild_skill_in_gvg_only && !map[bl->m].flag.gvg) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GVGONLY,0,0);
			return 0;
		}
		if(battle_config.guild_skill_in_pvp_limit && map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		if(sd->sc.data[SC_BATTLEORDER_DELAY + cnd->id - GD_BATTLEORDER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(cnd->id == GD_EMERGENCYCALL && battle_config.no_emergency_call) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
		
	case SJ_SOLARBURST:		/* 太陽爆発 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SJ_PROMINENCEKICK){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SJ_PROMINENCEKICK,0);
			return 0;
		}
		//fall through
	case SJ_PROMINENCEKICK:		/* 紅焔脚 */
		if((sd->sc.data[SC_SUNSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSUN:		/* 太陽の光 */
		if(sd->sc.data[SC_SUNSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FULLMOONKICK:		/* 満月脚 */
		if(sd->sc.data[SC_NEWMOON].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		//fall through
	case SJ_NEWMOONKICK:		/* 朔月脚 */
		if((sd->sc.data[SC_LUNARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFMOON:		/* 月の光 */
		if(sd->sc.data[SC_LUNARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FLASHKICK:		/* 閃光脚 */
	case SJ_FALLINGSTAR:		/* 流星落下 */
		if((sd->sc.data[SC_STARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSTAR:		/* 星の光 */
		if(sd->sc.data[SC_STARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_GRAVITYCONTROL:		/* 重力調節 */
	case SJ_NOVAEXPLOSING:		/* 新星爆発 */
	case SJ_STAREMPEROR:		/* 星帝降臨 */
	case SJ_BOOKOFCREATINGSTAR:		/* 創星の書 */
	case SJ_BOOKOFDIMENSION:		/* 次元の書 */
		if(sd->sc.data[SC_UNIVERSESTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(battle_config.allow_se_univ_skill_limit && !map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		break;
	case SP_SOULGOLEM:		/* ゴーレムの魂 */
	case SP_SOULSHADOW:		/* 影の魂 */
	case SP_SOULFALCON:		/* 鷹の魂 */
	case SP_SOULFAIRY:		/* 妖精の魂 */
		if(target && target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		/* 使うスキル以外の魂状態かを判定 */
		if(tsc &&
		   (cnd->id == SP_SOULGOLEM && (tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULSHADOW && (tsc->data[SC_SOULGOLEM].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULFALCON && (tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULFAIRY && (tsc->data[SC_SOULGOLEM].timer != -1 || tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1)) ||
		   tsc->data[SC_ALCHEMIST].timer != -1 || tsc->data[SC_MONK].timer != -1 || tsc->data[SC_STAR].timer != -1 || tsc->data[SC_SAGE].timer != -1 ||
		   tsc->data[SC_CRUSADER].timer != -1 || tsc->data[SC_SUPERNOVICE].timer != -1 || tsc->data[SC_KNIGHT].timer != -1 || tsc->data[SC_WIZARD].timer != -1 ||
		   tsc->data[SC_PRIEST].timer != -1 || tsc->data[SC_BARDDANCER].timer != -1 || tsc->data[SC_ROGUE].timer != -1 || tsc->data[SC_ASSASIN].timer != -1 ||
		   tsc->data[SC_BLACKSMITH].timer != -1 || tsc->data[SC_HUNTER].timer != -1 || tsc->data[SC_SOULLINKER].timer != -1 || tsc->data[SC_HIGH].timer != -1 ||
		   tsc->data[SC_DEATHKINGHT].timer != -1 || tsc->data[SC_COLLECTOR].timer != -1 || tsc->data[SC_NINJA].timer != -1 || tsc->data[SC_GUNNER].timer != -1)
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SOULCURSE:		/* 死霊憑依 */
		if(target && target->type != BL_MOB) {		// MOB以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SPA:				/* エスパ */
	case SP_SWHOO:				/* エスフ */
		if(target && target->type != BL_MOB && !battle_config.allow_es_magic_all) {		// MOB以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULDIVISION:		/* 魂の分裂 */
		if(target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULREVOLVE:		/* 魂の循環 */
		if(target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		// 魂状態かを判定
		if(!tsc ||
		  (tsc->data[SC_ALCHEMIST].timer == -1 && tsc->data[SC_MONK].timer == -1 && tsc->data[SC_STAR].timer == -1 && tsc->data[SC_SAGE].timer == -1 &&
		   tsc->data[SC_CRUSADER].timer == -1 && tsc->data[SC_SUPERNOVICE].timer == -1 && tsc->data[SC_KNIGHT].timer == -1 && tsc->data[SC_WIZARD].timer == -1 &&
		   tsc->data[SC_PRIEST].timer == -1 && tsc->data[SC_BARDDANCER].timer == -1 && tsc->data[SC_ROGUE].timer == -1 && tsc->data[SC_ASSASIN].timer == -1 &&
		   tsc->data[SC_BLACKSMITH].timer == -1 && tsc->data[SC_HUNTER].timer == -1 && tsc->data[SC_SOULLINKER].timer == -1 && tsc->data[SC_HIGH].timer == -1 &&
		   tsc->data[SC_DEATHKINGHT].timer == -1 && tsc->data[SC_COLLECTOR].timer == -1 && tsc->data[SC_NINJA].timer == -1 && tsc->data[SC_GUNNER].timer == -1 &&
		   tsc->data[SC_SOULGOLEM].timer == -1 && tsc->data[SC_SOULSHADOW].timer == -1 && tsc->data[SC_SOULFALCON].timer == -1 && tsc->data[SC_SOULFAIRY].timer == -1))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SOULEXPLOSION:		/* 魂の崩壊 */
		if(status_get_hp(target) < 10) {	// 対象のHPが10未満は失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		// 魂状態かを判定
		if(!tsc ||
		  (tsc->data[SC_ALCHEMIST].timer == -1 && tsc->data[SC_MONK].timer == -1 && tsc->data[SC_STAR].timer == -1 && tsc->data[SC_SAGE].timer == -1 &&
		   tsc->data[SC_CRUSADER].timer == -1 && tsc->data[SC_SUPERNOVICE].timer == -1 && tsc->data[SC_KNIGHT].timer == -1 && tsc->data[SC_WIZARD].timer == -1 &&
		   tsc->data[SC_PRIEST].timer == -1 && tsc->data[SC_BARDDANCER].timer == -1 && tsc->data[SC_ROGUE].timer == -1 && tsc->data[SC_ASSASIN].timer == -1 &&
		   tsc->data[SC_BLACKSMITH].timer == -1 && tsc->data[SC_HUNTER].timer == -1 && tsc->data[SC_SOULLINKER].timer == -1 && tsc->data[SC_HIGH].timer == -1 &&
		   tsc->data[SC_DEATHKINGHT].timer == -1 && tsc->data[SC_COLLECTOR].timer == -1 && tsc->data[SC_NINJA].timer == -1 && tsc->data[SC_GUNNER].timer == -1 &&
		   tsc->data[SC_SOULGOLEM].timer == -1 && tsc->data[SC_SOULSHADOW].timer == -1 && tsc->data[SC_SOULFALCON].timer == -1 && tsc->data[SC_SOULFAIRY].timer == -1))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_KAUTE:		/* カウト */
		{
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!tsd) {
				// 対象が人以外失敗
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			// HPが30%以上必要
			if(sd->status.hp < sd->status.max_hp * 30 / 100) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
				return 0;
			}
			if(battle_config.soul_linker_battle_mode_ka == 0) {
				// ソウルリンカー系職業か家族以外、魂の連結状態効果中でなければ使用失敗
				if( pc_get_base_job(tsd->s_class.job,2) != PC_JOB_SL &&
					tsd->status.char_id != sd->status.char_id &&
				    tsd->status.char_id != sd->status.partner_id &&
				    tsd->status.char_id != sd->status.baby_id &&
					tsd->sc.data[SC_SOULUNITY].timer == -1) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
		break;
	case IQ_JUDGE:		/* 第二章：審判者 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FLAME:		/* 第二撃：滅魔の火 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FAITH:		/* 第二撃：信念 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_JUDGEMENT:		/* 第二撃：審判 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_PUNISH:		/* 第三撃：断罪 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_FLAME_BOMB:		/* 第三撃：滅火撃 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_CONSECRATION:		/* 第三撃：浄化 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_EXOR_FLAME:		/* 最終章：滅魔の炎 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_GUARDIAN_SHIELD:		/* ガーディアンシールド */
	case IG_ULTIMATE_SACRIFICE:		/* アルティメットサクリファイス */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_REBOUND_SHIELD:			/* リバウンドシールド */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		// ディボーション検査
		for(i=0; i<5; i++) {
			if(sd->dev.val1[i]) {
				break;
			}
		}
		// ディボーションを使用していない
		if(i >= 5) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IG_GRAND_JUDGEMENT:		/* グランドジャッジメント */
	case IG_SHIELD_SHOOTING:		/* シールドシューティング */
	case IG_OVERSLASH:				/* オーバースラッシュ */
		if(sd->sc.data[SC_ATTACK_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CD_REPARATIO:				/* レパラティオ */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC以外と不死属性には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case CD_MEDIALE_VOTUM:			/* メディアリボトゥム */
	case CD_DILECTIO_HEAL:			/* ディレクティオヒール */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC以外と不死属性には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case CD_ARGUTUS_VITA:		/* アルグトゥスヴィタ */
	case CD_ARGUTUS_TELUM:		/* アルグトゥステルム */
	case CD_PRESENS_ACIES:		/* プレセンスアキエース */
	case MT_D_MACHINE:			/* 防御装置有効化 */
	case EM_SPELL_ENCHANTING:	/* スペルエンチャンティング */
	case SOA_TALISMAN_OF_PROTECTION:	/* 守護符 */
	case SOA_TALISMAN_OF_WARRIOR:	/* 武士符 */
	case SOA_TALISMAN_OF_MAGICIAN:	/* 法師符 */
	case SOA_TALISMAN_OF_FIVE_ELEMENTS:	/* 五行符 */
		if(target->type != BL_PC) {		// PC以外には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SHC_ETERNAL_SLASH:		/* エターナルスラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case SHC_POTENT_VENOM:		/* ポテントベナム */
		if(sd->sc.data[SC_EDP].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SHC_IMPACT_CRATER:		/* インパクトクレーター */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case MT_A_MACHINE:			/* 攻撃装置有効化 */
		if(target->type != BL_PC) {		// PC以外には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
			if(abs(sd->status.base_level - tsd->status.base_level) > 15) {	// レベル差が15以上の相手は使用失敗
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR バトルウォリアー */
	case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR デュアルキャノン */
	case MT_SUMMON_ABR_MOTHER_NET:		/* ABR マザーネット */
	case MT_SUMMON_ABR_INFINITY:		/* ABR インフィニティ */
		{
			const int mob_id[4] = { MOBID_ABR_BATTLE_WARIOR, MOBID_ABR_DUAL_CANNON, MOBID_ABR_MOTHER_NET, MOBID_ABR_INFINITY };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, mob_id[cnd->id-MT_SUMMON_ABR_BATTLE_WARIOR]
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case BO_WOODENWARRIOR:		/* クリエイトウドゥンウォリアー */
	case BO_WOODEN_FAIRY:		/* クリエイトウドゥンフェアリー */
	case BO_CREEPER:			/* クリエイトクリーパー */
	case BO_HELLTREE:			/* クリエイトヘルツリー */
		{
			const int mob_id[5] = { MOBID_SUMMON_WOODENWARRIOR, MOBID_SUMMON_WOODEN_FAIRY, MOBID_SUMMON_CREEPER, 0, MOBID_SUMMON_HELLTREE };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, mob_id[cnd->id-BO_WOODENWARRIOR]
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case EM_ACTIVITY_BURN:					/* アクティビティバーン */
		if(target->type != BL_PC) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_INCREASING_ACTIVITY:			/* インクリーシングアクティビティ */
		if(target->type != BL_PC || bl == target) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_ARDOR:			/* サモンアルドール */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AGNI_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AQUA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_VENTUS_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_TERA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AGNI_L && sd->eld->status.class_ != ELEMID_EL_AQUA_L && sd->eld->status.class_ != ELEMID_EL_VENTUS_L && sd->eld->status.class_ != ELEMID_EL_TERA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_ELEMENTAL_BUSTER:	/* エレメンタルバスター */
	case EM_ELEMENTAL_VEIL:		/* エレメンタルヴェール */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		if(!elem_is4thclass(sd->eld)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SOA_SOUL_GATHERING:		/* 護魂一身 */
		if(sd->sc.data[SC_SOULCOLLECT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULCOLLECT,0,0);
			return 0;
		}
		break;
	case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* 死霊浄化 */
		if(sd->soulenergy.num == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULENERGY,0,0);
			return 0;
		}
		break;
	case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* 四方五行陣 */
		if(sd->sc.data[SC_T_FOURTH_GOD].timer == -1 && sd->sc.data[SC_T_FIVETH_GOD].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SH_BLESSING_OF_MYSTICAL_CREATURES:		/* にゃんブレッシング */
		if(bl == target) {		// 自分には使用不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(tsc && tsc->data[SC_BLESSING_OF_M_C_DEBUFF].timer != -1) {		// リバウンド状態には使用不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(tsd && pc_isdoram(tsd)) {			// ドラム系列には使用不可
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case SKE_NOON_BLAST:		/* 太天一陽 */
		if(sd->sc.data[SC_RISING_SUN].timer == -1 && sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_SUNSET_BLAST:		/* 天陽 */
		if(sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SUNSET_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_MIDNIGHT_KICK:		/* 太天一月 */
		if(sd->sc.data[SC_RISING_MOON].timer == -1 && sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_DAWN_BREAK:		/* 天月 */
		if(sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_DAWN_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_STAR_BURST:		/* 天命落星 */
	case SKE_STAR_CANNON:		/* 天星 */
		{
			// 天地万星の範囲内かチェック
			int range = skill_get_unit_range(SKE_TWINKLING_GALAXY, 1);
			if(map_foreachinarea(skill_check_unit_id,
				bl->m, bl->x-range, bl->y-range, bl->x+range, bl->y+range, BL_SKILL,
				bl->id, SKE_TWINKLING_GALAXY) == 0)
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TWINKLINGGALAXY,0,0);
				return 0;
			}
		}
		break;
	case SS_KUNAIKUSSETSU:		/* 苦無 -屈折- */
		{
			// 苦無トラップ判定
			int range = skill_get_area(cnd->id, cnd->lv);
			if(map_foreachinarea(skill_check_unit_id,
				bl->m, bl->x-range, bl->y-range, bl->x+range, bl->y+range, BL_SKILL,
				bl->id, SS_KUNAIWAIKYOKU) == 0)
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	}

	if(!(type&2)) {
		int w;

		if(!sd->skill_item.flag) {		// アイテムスキル由来ならSPチェックは不要
			if(sp > 0 && sd->status.sp < sp) {		/* SPチェック */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
				return 0;
			}
		}
		if(hp > 0 && sd->status.hp < hp) {			/* HPチェック */
			clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
			return 0;
		}
		if(ap > 0 && sd->status.ap < ap) {			/* APチェック */
			clif_skill_fail(sd,cnd->id,SKILLFAIL_AP,0,0);
			return 0;
		}
		if(zeny > 0 && sd->status.zeny < zeny) {
			sd->zenynage_damage = 0;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_ZENY,0,0);
			return 0;
		}

		w = sd->status.weapon;
		if(w >= WT_MAX)
			w -= WT_DOUBLE_DD + WT_MAX;

		if(!(weapon & (1<<w))) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_WEAPON,0,0);
			return 0;
		}
		if(spiritball > 0 && sd->spiritball.num < spiritball) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,spiritball,0);
			return 0;
		}
		if(coin > 0 && sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COIN,coin,0);
			return 0;
		}
		if(soulenergy > 0 && sd->soulenergy.num < soulenergy) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULENERGY,soulenergy,0);
			return 0;
		}
		if(servantweapon > 0 && sd->ball.num < servantweapon) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SERVANTWEAPOM,servantweapon,0);
			return 0;
		}
		if(arrow > 0) {						// 矢不足
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if( idx == -1 ||
			    !(sd->inventory_data[idx]->arrow_type & skill_get_arrow_type(cnd->id)) ||
			    sd->status.inventory[idx].amount < arrow )
			{
				// 矢の種類ごとに失敗メッセージを表示
				switch(skill_get_arrow_type(cnd->id)) {
				case 0x0004:		// ハンドガン専用弾
				case 0x0008:		// ライフル専用弾
				case 0x0010:		// ショットガン専用弾
				case 0x0020:		// ガトリンガン専用弾
				case 0x0040:		// グレネードランチャー専用弾
					clif_skill_fail(sd,cnd->id,SKILLFAIL_BULLET,0,0);
					break;
				case 0x0100:		// 苦無
					clif_skill_fail(sd,cnd->id,SKILLFAIL_KUNAI,0,0);
					break;
				case 0x0200:		// キャノンボール
					clif_skill_fail(sd,cnd->id,SKILLFAIL_CANONBALL,0,0);
					break;
				default:
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					break;
				}
				return 0;
			}
		}
	}

	switch(state) {
	case SST_HIDING:
		if(!(sd->sc.option&OPTION_HIDE)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CLOAKING:
		if(!pc_iscloaking(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CHASEWALKING:
		if(!pc_ischasewalk(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_HIDDEN:
		if(!pc_ishiding(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_RIDING:
		if(!pc_isriding(sd) && !pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_FALCON:
		if(!pc_isfalcon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CART:
		if(!pc_iscarton(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CART,0,0);
			return 0;
		}
		break;
	case SST_SHIELD:
		if(sd->status.shield <= 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_SIGHT:
		if(sd->sc.data[SC_SIGHT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(sd->sc.data[SC_CARTBOOST].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_NEN:
		if(sd->sc.data[SC_NEN].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_RECOV_WEIGHT_RATE:
		if(battle_config.natural_heal_weight_rate <= 100 && sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SST_DRAGON:
		if(!pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_DRAGON,0,0);
			return 0;
		}
		break;
	case SST_WOLF:
		if(!pc_iswolf(sd) && !pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_GEAR:
		if(!pc_isgear(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MADOGEAR,0,0);
			return 0;
		}
		break;
	}

	switch(cnd->id)
	{
		case SA_VOLCANO:		/* ボルケーノ */
		case SA_DELUGE:			/* デリュージ */
		case SA_VIOLENTGALE:	/* バイオレントゲイル */
			// 属性場用 出ている間はコスト無し
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
				item_nocost = 1;
			break;
		case SR_CURSEDCIRCLE:	/* 呪縛陣 */
			spiritball = 0;		// 気弾の消費はスキル効果発動時
			break;
		case DK_SERVANT_W_PHANTOM:		/* サーヴァントウェポン：ファントム */
		case DK_SERVANT_W_DEMOL:		/* サーヴァントウェポン：デモリッション */
			servantweapon = 0;	// 武器体の消費はスキル効果発動時
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
					if(cnd->lv < 5) {
						// 赤ポーション
						itemid[MAX_SKILL_DB_ITEM] = 501;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else if(cnd->lv < 10) {
						// 黄ポーション
						itemid[MAX_SKILL_DB_ITEM] = 503;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else {
						// 白ポーション
						itemid[MAX_SKILL_DB_ITEM] = 504;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
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
		if(ap > 0) {					// AP消費
			sd->status.ap -= ap;
			clif_updatestatus(sd,SP_AP);
		}
		if(zeny > 0)					// Zeny消費
			pc_payzeny(sd,zeny);
		if(spiritball > 0)				// 気球消費
			pc_delspiritball(sd,spiritball,0);
		if(coin > 0)					// コイン消費
			pc_delcoin(sd,coin,0);
		if(soulenergy > 0)				// ソウルエナジー消費
			pc_delsoulenergy(sd,soulenergy,0);
		if(servantweapon > 0)			// サーヴァントウェポン消費
			pc_delball(sd,servantweapon,0);
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
			if(md->state.special_mob_ai != MOB_AI_NONE) {
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
			if(md->master_id > 0 && md->state.special_mob_ai != MOB_AI_NONE) {
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
	int i,hp,sp,hp_rate,sp_rate,zeny,state,spiritball,skilldb_id;
	struct map_session_data* msd;
	struct block_list *bl;
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];

	nullpo_retr(0, hd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, msd = hd->msd);
	nullpo_retr(0, bl = &hd->bl);

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	spiritball = (cnd->lv <= 0)? 0: skill_db[skilldb_id].spiritball[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// スキルLv毎の消費アイテム
	if(cnd->lv > 0 && cnd->lv <= MAX_SKILL_LEVEL) {
		itemid[i] = skill_db[skilldb_id].lv_itemid[cnd->lv-1];
		amount[i] = skill_db[skilldb_id].lv_amount[cnd->lv-1];
	}
	else {
		itemid[i] = 0;
		amount[i] = 0;
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
				if(hd->intimate < 200) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_INTIMATE, 0, 0);
					return 0;
				}
				break;
			case HVAN_EXPLOSION:	/* バイオエクスプロージョン */
				if(hd->intimate < battle_config.hvan_explosion_intimate) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_INTIMATE, 0, 0);
					return 0;
				}
				break;
			case MH_LIGHT_OF_REGENE:	/* 再生の光 */
				if(hd->intimate < 91100) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_INTIMATE, 0, 0);
					return 0;
				}
				break;
			case MH_GOLDENE_FERSE:	/* ゴールデンペルジェ */
				if(hd->sc.data[SC_ANGRIFFS_MODUS].timer != -1)
					return 0;
				break;
			case MH_ANGRIFFS_MODUS:	/* アングリフスモドス */
				if(hd->sc.data[SC_GOLDENE_FERSE].timer != -1)
					return 0;
				break;
			case MH_TINDER_BREAKER:	/* ティンダーブレイカー */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 2)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_GRAPPLER, 1, 0);
					return 0;
				}
				break;
			case MH_SONIC_CRAW:		/* ソニッククロー */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 1)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_FIGHTER, 0, 0);
					return 0;
				}
				if(hd->spiritball < 1) {
					clif_skill_fail(hd->msd,cnd->id,SKILLFAIL_SPIRITBALL,1,0);
					return 0;
				}
				break;
			case MH_SILVERVEIN_RUSH:	/* シルバーベインラッシュ */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 1)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_FIGHTER, 0, 0);
					return 0;
				}
				if (!(hd->sc.data[SC_COMBO].timer != -1 && hd->sc.data[SC_COMBO].val1 == MH_SONIC_CRAW)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_COMBOSKILL, MH_SONIC_CRAW, 0);
					return 0;
				}
				break;
			case MH_MIDNIGHT_FRENZY:	/* ミッドナイトフレンジ */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 1)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_FIGHTER, 0, 0);
					return 0;
				}
				if (!(hd->sc.data[SC_COMBO].timer != -1 && hd->sc.data[SC_COMBO].val1 == MH_SILVERVEIN_RUSH)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_COMBOSKILL, MH_SILVERVEIN_RUSH, 0);
					return 0;
				}
				break;
			case MH_CBC:	/* C.B.C */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 2)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_GRAPPLER, 0, 0);
					return 0;
				}
				if (!(hd->sc.data[SC_COMBO].timer != -1 && hd->sc.data[SC_COMBO].val1 == MH_TINDER_BREAKER)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_COMBOSKILL, MH_TINDER_BREAKER, 0);
					return 0;
				}
				break;
			case MH_EQC:	/* E.Q.C */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 2)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_GRAPPLER, 0, 0);
					return 0;
				}
				if (!(hd->sc.data[SC_COMBO].timer != -1 && hd->sc.data[SC_COMBO].val1 == MH_CBC)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_COMBOSKILL, MH_CBC, 0);
					return 0;
				}
				break;
			case MH_POISON_MIST:		/* ポイズンミスト */
			case MH_LAVA_SLIDE:			/* ラーヴァスライド */
			case MH_VOLCANIC_ASH:		/* ボルカニックアッシュ */
				{
					int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
					if(maxcount > 0 && skill_count_unitgroup(&hd->ud,cnd->id) >= maxcount) {
						clif_skill_fail(msd, cnd->id, SKILLFAIL_MORESKILL, 0, 0);
						return 0;
					}
				}
				break;
		}
	}

	if(spiritball > 0 && hd->spiritball < spiritball) {
		clif_skill_fail(hd->msd,cnd->id,SKILLFAIL_SPIRITBALL,spiritball,0);
		return 0;
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
		if(spiritball > 0)				// 気球消費
			homun_delspiritball(hd,spiritball,0);
	}
	return 1;
}

// MERC用判定( 0: 使用失敗 1: 使用成功 )
static int skill_check_condition2_merc(struct merc_data *mcd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,hp_rate,sp_rate,zeny,state,skilldb_id;
	struct map_session_data* msd;
	struct block_list *bl;
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];

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

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// スキルLv毎の消費アイテム
	if(cnd->lv > 0 && cnd->lv <= MAX_SKILL_LEVEL) {
		itemid[i] = skill_db[skilldb_id].lv_itemid[cnd->lv-1];
		amount[i] = skill_db[skilldb_id].lv_amount[cnd->lv-1];
	}
	else {
		itemid[i] = 0;
		amount[i] = 0;
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
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];

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

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// スキルLv毎の消費アイテム
	if(cnd->lv > 0 && cnd->lv <= MAX_SKILL_LEVEL) {
		itemid[i] = skill_db[skilldb_id].lv_itemid[cnd->lv-1];
		amount[i] = skill_db[skilldb_id].lv_amount[cnd->lv-1];
	}
	else {
		itemid[i] = 0;
		amount[i] = 0;
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
	int i, idx[MAX_SKILL_DB_ITEM+1];

	nullpo_retr(0, bl);
	nullpo_retr(0, cnd);

	sd = map_bl2msd(bl);
	if(sd == NULL)
		return 0;

	sc = status_get_sc(bl);

	for(i=0; i<MAX_SKILL_DB_ITEM+1; i++) {

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
        if(itemid[i] == 6146 && sd->special_state.no_gearfuel)
			continue;

		idx[i] = pc_search_inventory(sd,itemid[i]);
		if(idx[i] < 0 || sd->status.inventory[idx[i]].amount < amount[i]) {
			// トラップ研究を習得中または使用スキルがエスケープで設置用トラップが足りなかった場合
			if((pc_checkskill(sd,RA_RESEARCHTRAP) || cnd->id == SC_ESCAPE) && itemid[i] ==1065) {
				// 改良型設置用トラップに置き換えて再検索
				itemid[i] = 7940;
				amount[i] = 1;
				i--;
				continue;
			}
			if(itemdb_isequip3(itemid[i]))
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,amount[i],itemid[i]);
			else if(itemid[i] == 716)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_REDJEMSTONE,amount[i],0);
			else if(itemid[i] == 717)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_BLUEJEMSTONE,amount[i],0);
			else if(itemid[i] == 523)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_HOLYWATER,amount[i],0);
			else if(itemid[i] == 12333)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_ANCILLA,amount[i],0);
			else if(itemid[i] == 6122)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_PAINTBRUSH,amount[i],0);
			else if(itemid[i] == 1000563)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TALISMAN,amount[i],0);
			else
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_ITEM,amount[i],itemid[i]);
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
			// リサーチレポート
			if(sc->data[SC_RESEARCHREPORT].timer != -1 && cnd->id >= BO_ACIDIFIED_ZONE_WATER && cnd->id <= BO_ACIDIFIED_ZONE_FIRE && amount[i] > 0) {
				amount[i] -= 1;
			}
		}
	}

	if(type&1 && (cnd->id != AL_WARP || type&2)) {
		if(cnd->id != AM_POTIONPITCHER && cnd->id != CR_SLIMPITCHER && cnd->id != GN_FIRE_EXPANSION) {
			for(i=0; i<MAX_SKILL_DB_ITEM+1; i++) {
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

			/* マスカレード：レイジネス */
			if(sc->data[SC__LAZINESS].timer != -1)
				reduce_time -= sc->data[SC__LAZINESS].val1 * 10;

			/* 十六夜 */
			if(sc->data[SC_IZAYOI].timer != -1)
				reduce_time += 50;

			/* テレキネシスインテンス */
			if(sc->data[SC_TELEKINESIS_INTENSE].timer != -1 && skill_get_pl(skillid) == ELE_GHOST)
				reduce_time += 10;

			/* 妖精の魂 */
			if(sc->data[SC_SOULFAIRY].timer != -1)
				reduce_time += sc->data[SC_SOULFAIRY].val3;
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

	// カードによる詠唱時間増減効果
	if(fixedtime > 0 && sd && sd->skill_addfixcast.count > 0) {
		for(i=0; i<sd->skill_addfixcast.count; i++) {
			if(skillid == sd->skill_addfixcast.id[i])
				fixedtime += sd->skill_addfixcast.time[i];
		}
	}
	if(sc) {
		/* ハウリングオブマンドラゴラ */
		if(sc->data[SC_MANDRAGORA].timer != -1) {
			fixedtime += sc->data[SC_MANDRAGORA].val3;		// 強制固定詠唱増加
		}
		/* 麻痺 */
		if(sc->data[SC_PARALYZE].timer != -1) {
			fixedtime += sc->data[SC_PARALYZE].val2;		// 強制固定詠唱増加
		}
	}

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
			// カードによる固定詠唱時間増減効果
			if(sd->skill_fixcastrate.count > 0) {
				for(i=0; i<sd->skill_fixcastrate.count; i++) {
					if(skillid == sd->skill_fixcastrate.id[i])
						reduce_time2 = (reduce_time2 < sd->skill_fixcastrate.rate[i])? sd->skill_fixcastrate.rate[i]: reduce_time2;
				}
			}
			reduce_time2 = ((reduce_time2 < sd->fixcastrate)? sd->fixcastrate: reduce_time2) + sd->fixcastrate_;
		}

		if(sc) {
			/* フロストミスティ */
			if(sc->data[SC_FROSTMISTY].timer != -1)
				reduce_time2 -= 15;

			/* 十六夜 */
			if(sc->data[SC_IZAYOI].timer != -1)
				reduce_time2 += 100;
		}

		fixedtime = fixedtime * (100 - reduce_time2) / 100;
	}

	// ニャンジャンプ習得時は緊急招集の詠唱時間2倍
	if(sd && skillid == GD_EMERGENCYCALL && pc_checkskill(sd,SU_LOPE) > 0) {
		casttime  <<= 1;
		fixedtime <<= 1;
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

				if(sc) {
					/* ブラギの詩 */
					if(sc->data[SC_POEMBRAGI].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI].val1 * rate + sc->data[SC_POEMBRAGI].val2 * 2
							+ (sc->data[SC_POEMBRAGI].val3 & 0xffff));
					} else if(sc->data[SC_POEMBRAGI_].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI_].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI_].val1 * rate + sc->data[SC_POEMBRAGI_].val2 * 2
							+ (sc->data[SC_POEMBRAGI_].val3 & 0xffff));
					}
					if(sc->data[SC_SOULDIVISION].timer != -1) {		// 魂の分裂
						reduce_time -= sc->data[SC_SOULDIVISION].val2;
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
		struct status_change* sc = status_get_sc(bl);
		if(skillid == SU_TUNABELLY && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// 大トロ
			cooldown -= 3000;
		else if( skillid == SJ_NOVAEXPLOSING && sc && (sc->data[SC_DIMENSION].timer != -1 || sc->data[SC_DIMENSION1].timer != -1 ) && sc->data[SC_DIMENSION2].timer == -1)
			return 0;

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
void skill_brandishspear_first(struct square *tc,int dir,int x,int y)
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
void skill_brandishspear_dir(struct square *tc,int dir,int are)
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

	if(unit_distance(&sd->bl, &tsd->bl) > 11) {	// 許容範囲を超えてた
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
	else if(flag&2 && (pc_checkskill(sd,TK_HPTIME) > 0 || pc_checkskill(sd,TK_SPTIME) > 0))
		sd->state.taekwonrest = 1;

	return 0;
}

static int skill_sit_out(struct block_list *bl,va_list ap)
{
	int flag;
	struct map_session_data *sd;

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

	if(pc_checkskill(sd,RG_GANGSTER) > 0 || sd->state.gangsterparadise)
		flag |= 1;
	if(pc_checkskill(sd,TK_HPTIME) > 0 || pc_checkskill(sd,TK_SPTIME) > 0 || sd->state.taekwonrest)
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

	if(NPC_WIDEHEALTHFEAR <= skillid && skillid <= NPC_KILLING_AURA)
		return 1;

	if(skillid == NPC_SELFDESTRUCTION2)
		return 1;

	return 0;
}

/*==========================================
 * アブラカダブラの使用スキル決定(決定スキルがダメなら0を返す)
 *------------------------------------------
 */
int skill_abra_dataset(struct map_session_data *sd, int skilllv)
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
int skill_clear_element_field(struct block_list *bl)
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
int skill_landprotector(struct block_list *bl, va_list ap )
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
int skill_tarot_card_of_fate(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int wheel)
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
			unit_heal(target, 2000, 0, 0, 0);
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
			case UNT_GROUNDDRIFT_WIND:	/* グラウンドドリフト */
			case UNT_GROUNDDRIFT_DARK:
			case UNT_GROUNDDRIFT_POISON:
			case UNT_GROUNDDRIFT_WATER:
			case UNT_GROUNDDRIFT_FIRE:
			case UNT_GROUNDDRIFT_NEUTRAL:
				battle_skill_attack(BF_WEAPON,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
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
				if(sg->skill_id == NPC_REVERBERATION) {
					skill_addtimerskill(ss,tick + 200,bl->id,0,0,NPC_REVERBERATION_ATK,sg->skill_lv,0,(0x0f<<20)|0x0500|splash_count);
				}
				else {
					skill_addtimerskill(ss,tick + 200,bl->id,0,0,WM_REVERBERATION_MELEE,sg->skill_lv,0,(0x0f<<20)|0x0500|splash_count);
					skill_addtimerskill(ss,tick + 400,bl->id,0,0,WM_REVERBERATION_MAGIC,sg->skill_lv,0,(0x0f<<20)|0x0500|splash_count);
				}
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

/*==========================================
 * ディティクト効果（隠れている相手を暴く）
 *------------------------------------------
 */
int skill_detect(struct block_list *bl)
{
	int result = 0;
	struct status_change *sc = NULL;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(sc) {
		// ハイディング
		if(sc->data[SC_HIDING].timer != -1) {
			status_change_end(bl, SC_HIDING, -1);
			result = 1;
		}
		// クローキング
		if(sc->data[SC_CLOAKING].timer != -1) {
			status_change_end(bl, SC_CLOAKING, -1);
			result = 1;
		}
		// インビジブル
		if(sc->data[SC_INVISIBLE].timer != -1) {
			status_change_end(bl, SC_INVISIBLE, -1);
			result = 1;
		}
		// クローキングエクシード
		if(sc->data[SC_CLOAKINGEXCEED].timer != -1) {
			status_change_end(bl, SC_CLOAKINGEXCEED, -1);
			result = 1;
		}
		// カモフラージュ
		if(sc->data[SC_CAMOUFLAGE].timer != -1) {
			status_change_end(bl, SC_CAMOUFLAGE, -1);
			result = 1;
		}
		// シャドウフォーム（ディテクト耐性あり）
		if(sc->data[SC__SHADOWFORM].timer != -1 && atn_rand()%100 < 100 - sc->data[SC__SHADOWFORM].val1 * 10) {
			status_change_end(bl, SC__SHADOWFORM, -1);
			result = 1;
		}
		// 朔月
		if(sc->data[SC_NEWMOON].timer != -1) {
			status_change_end(bl, SC_NEWMOON, -1);
			result = 1;
		}
	}

	return result;
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
int skill_delunit_by_ganbantein(struct block_list *bl, va_list ap )
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
		case NPC_CANE_OF_EVIL_EYE:
		case MH_STEINWAND:
		case MH_LAVA_SLIDE:
		case MH_VOLCANIC_ASH:
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
		case KO_MAKIBISHI:
		case KO_ZENKAI:
		case RL_FIRE_RAIN:
		case SJ_BOOKOFCREATINGSTAR:
		case SU_CN_METEOR:
		case SU_CN_METEOR2:
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

	// スキルユニットのtickがタイマ周期より早い場合は次周期に回す
	if(DIFF_TICK(tick,group->tick) < 0)
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

	// 城隍堂のカウント加算
	if(group->unit_id == UNT_TOTEM_OF_TUTELARY && DIFF_TICK(tick,group->tick)%group->interval < SKILLUNITTIMER_INVERVAL) {
		group->val1++;
	}

	// バイオレントクエイクとオールブルームのランダムユニット配置
	if((group->unit_id == UNT_VIOLENT_QUAKE && group->val1 != 4) || (group->unit_id == UNT_ALL_BLOOM && group->val1 != 4)) {
		struct block_list *src = map_id2bl(group->src_id);
		int diff = DIFF_TICK(tick,group->tick);
		// 時間切れと発動間隔を判定
		if(src && diff < group->limit && diff%group->interval < SKILLUNITTIMER_INVERVAL) {
			int i, max = 1;
			if((group->unit_id == UNT_VIOLENT_QUAKE && group->val1 == 1) ||		// バイオレントクエイクでクライマックスLv1
			   (group->unit_id == UNT_ALL_BLOOM && group->val1 == 2)) {			// オールブルームでクライマックスLv2
				max = 2;		// 2回ずつ発動
			}

			for(i = 0; i < max; i++ ) {
				int tmpx = bl->x + (atn_rand()%(range*2+1) - range);
				int tmpy = bl->y + (atn_rand()%(range*2+1) - range);
				clif_skill_poseffect(src,group->skill_id+1,-1,tmpx,tmpy,tick);
				skill_unitsetting(src,group->skill_id+1,group->skill_lv,tmpx,tmpy,group->val1);
			}
		}
	}
	// グレネーズドロッピング、ミッションボンバード、天地万星、天星のランダムセル攻撃
	if(group->unit_id == UNT_GRENADES_DROPPING || group->unit_id == UNT_MISSION_BOMBARD || group->unit_id == UNT_TWINKLING_GALAXY || group->unit_id == UNT_STAR_CANNON) {
		struct block_list *src = map_id2bl(group->src_id);
		int diff = DIFF_TICK(tick,group->tick);
		// 時間切れと発動間隔を判定
		if(src && diff < group->limit && diff%group->interval < SKILLUNITTIMER_INVERVAL) {
			int ar = skill_get_area(group->skill_id,group->skill_lv);
			int tmpx = bl->x + (atn_rand()%(range*2+1) - range);
			int tmpy = bl->y + (atn_rand()%(range*2+1) - range);
			map_foreachinarea(skill_area_sub,
				src->m,tmpx-ar,tmpy-ar,tmpx+ar,tmpy+ar,BL_CHAR,
				src,group->skill_id,group->skill_lv,tick,(0x0f<<20)|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
	}

	if(DIFF_TICK(tick,group->tick) >= group->limit || DIFF_TICK(tick,group->tick) >= unit->limit) {
		/* 時間切れ削除 */
		switch(group->unit_id) {
			case UNT_ATTACK_SKILLS:
				if(group->skill_id == HN_METEOR_STORM_BUSTER) {		/* メテオストームバスター */
					int ar = skill_get_unit_range(group->skill_id, group->skill_lv);
					map_foreachinarea(skill_area_sub,
						bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
						map_id2bl(group->src_id),group->skill_id,group->skill_lv,group->tick,BCT_ENEMY|1,
						skill_castend_damage_id);
				}
				break;
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
				{
					int ar = skill_get_area(group->skill_id, group->skill_lv);
					map_foreachinarea(skill_area_sub,
						bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
						map_id2bl(group->src_id),group->skill_id,group->skill_lv,group->tick,BCT_ENEMY|1,
						skill_castend_damage_id);
				}
				break;
			case UNT_BANDING:	/* バンディング */
				group->limit = DIFF_TICK(tick,group->tick)+600000;
				return 0;
			case UNT_REVERBERATION:	/* 振動残響 */
				{
					int ar = skill_get_area(group->skill_id, group->skill_lv);
					int splash_count = map_foreachinarea(skill_count_target,bl->m,
						bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
						(BL_CHAR|BL_SKILL),bl);
					map_foreachinarea(skill_trap_splash,
						bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
						(BL_CHAR|BL_SKILL),bl,tick,splash_count);
					group->unit_id = UNT_USED_TRAPS;
					clif_changelook(bl,LOOK_BASE,group->unit_id);
					group->limit = unit->limit = DIFF_TICK(tick,group->tick)+1500;
				}
				return 0;
			case UNT_ALL_BLOOM:		/* オールブルーム */
				if(group->val1 == 5) {		// クライマックスLv5：発動が終わった後に追撃
					struct block_list *src = map_id2bl(group->src_id);
					if(src) {
						clif_skill_poseffect(src,AG_ALL_BLOOM_ATK2,group->skill_lv,bl->x,bl->y,tick);
						skill_unitsetting(src,AG_ALL_BLOOM_ATK2,group->skill_lv,bl->x,bl->y,0);
					}
				}
				break;
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
	     group->unit_id != UNT_STEALTHFIELD &&
	     group->unit_id != UNT_KINGS_GRACE &&
	     group->unit_id != UNT_EARTHSTRAIN &&
	     group->unit_id != UNT_SHINKIROU)
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
int skill_count_unitgroup(struct unit_data *ud,int skillid)
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
	case PRD_M_MACHINE:	// 装置製造
	case PRD_BIONIC_PHARMACY:	// バイオニックファーマシー
		make_per = 10000;
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
			case PRD_M_MACHINE:
				amount = 6 + sd->skill_menu.lv + atn_rand()%3;			// 暫定：本来は武器研究Lv、BaseLevel,Dex,Luk,Crtに影響して変動
				clif_produceeffect(sd,0,nameid);
				clif_misceffect(&sd->bl,3);
				break;
			case PRD_BIONIC_PHARMACY:
				amount = 6 + sd->skill_menu.lv + atn_rand()%3;			// 暫定：本来はラーニングポーションLv、BaseLevel,Int,Luk,Crtに影響して変動
				clif_produceeffect(sd,2,nameid);	/* 製薬エフェクト */
				clif_misceffect(&sd->bl,5);		/* 他人にも成功を通知 */
				break;
		}
		pc_additem(sd,&tmp_item,amount,false);	// 重量オーバーなら消滅
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
				pc_heal(sd, -(sd->status.max_hp>>2), 0, 0, 0);
				break;
			case PRD_CONVERTER:
			case PRD_SYN_POTION:
			case PRD_RUNE:
			case PRD_NEWPOISON:
			case PRD_BIONIC_PHARMACY:
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
			case PRD_M_MACHINE:
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
					pc_additem(sd,&tmp_item,amount,false);
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
		pc_additem(sd, &tmp_item, amount,false);	// 重量オーバーなら消滅
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

int skill_am_twilight(struct map_session_data *sd, int skillid)
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
		if((flag = pc_additem(sd,&tmp_item,tmp_item.amount,false))) {
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
		clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		return;
	}

	if(sd != dstsd) {	// 対象が自分でないなら射程チェック
		int range = skill_get_fixed_range(&sd->bl,skillid,1);
		if(!battle_check_range(&sd->bl, &dstsd->bl, range+1)) {
			clif_item_repaireffect(sd, 1, idx);
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
		clif_item_repaireffect(sd, 1, idx);
	} else {
		clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,1,1);
		pc_delitem(sd,n,1,0,1);
		dstsd->status.inventory[idx].attribute = 0;
		clif_delitem(dstsd, 1, idx, 1);
		clif_additem(dstsd, idx, 1, 0);
		clif_item_repaireffect(sd, 0, idx);
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
	static const int msg[] = {
		0x5a3, 0x5a9, 0x5a8, 0x5a6, 0x5a2, 0x5a7, 0x5a5, 0x5a4
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
					clif_msgstringtable(sd, msg[i]);	// [xxx] 毒効果が武器に付与されました。
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
						status_change_start(&sd->bl,SC_SLEEP,1,0,0,0,30000,0);
						clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK_LEARN,0,0);
						break;
					}

					slot = skill_get_spellslot(spell[i]);

					/* スロットの上限チェック */
					if(sd->freeze_sp_slot + slot > 4 + pc_checkskill(sd,WL_FREEZE_SP) * 4 + sd->status.base_level/10 + sd->status.int_/10) {
						clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK_POINT,0,0);
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
					if( j >= MAX_FREEZE_SPELL )
						clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK_OVER,0,0);
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
						md->state.special_mob_ai = MOB_AI_SUMMON;
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

	if(skill_db[skill_get_skilldb_id(skillid)].autoshadowspell != 1)
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
			if((flag = pc_additem(sd, &tmp_item, tmp_item.amount,false))) {
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
		if((flag = pc_additem(sd, &tmp_item, tmp_item.amount,false))) {
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
int skill_get_spellslot(int skillid)
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
int skill_greed( struct block_list *bl,va_list ap )
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
int skill_balkyoung( struct block_list *bl,va_list ap )
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
int skill_detonator( struct block_list *bl, va_list ap )
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
			ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
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
				pc_heal(src_sd,0,sp,0,1);
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
int skill_trample( struct block_list *bl, va_list ap )
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
			ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
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
int skill_dominion_impulse( struct block_list *bl, va_list ap )
{
	struct skill_unit *unit;
	struct skill_unit_group *sg;

	nullpo_retr(0, bl);
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	if(sg->unit_id == UNT_REVERBERATION) {
		int ar = skill_get_area(sg->skill_id, sg->skill_lv);
		unsigned int tick = gettick();
		int splash_count = map_foreachinarea(skill_count_target,bl->m,
			bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
			(BL_CHAR|BL_SKILL),bl);
		map_foreachinarea(skill_trap_splash,
			bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
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
int skill_fire_expansion( struct block_list *bl, va_list ap )
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
 * フリッカー
 *------------------------------------------
 */
int skill_flicker( struct block_list *bl, va_list ap )
{
	int ar;
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	tick = va_arg(ap,unsigned int);

	if(!(skill_get_inf2(sg->skill_id)&INF2_TRAP))
		return 0;

	if(sg->unit_id == UNT_B_TRAP && sg->src_id == src->id) {
		ar = unit->range;

		// 罠を発動させる
		map_foreachinarea(skill_area_sub,
			bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
			src,RL_B_FLICKER_ATK,sg->skill_lv,tick,(0x0f<<20)|BCT_ENEMY|0x0500,
			skill_castend_damage_id);

		// 起動した罠の後処理
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(bl,LOOK_BASE,sg->unit_id);
		sg->limit = DIFF_TICK(gettick(),sg->tick) + 1500;
	}
	return 0;
}

/*==========================================
 * 影潜り
 *------------------------------------------
 */
int skill_shimiru( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	int i, x, y, dx, dy;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	if(sg->src_id == src->id && sg->unit_id == UNT_SHINKIROU) {
		i = 0;
		do {
			x = src->x + (atn_rand()%4 - 2);
			y = src->y + (atn_rand()%4 - 2);
		} while(map_getcell(src->m, x, y, CELL_CHKNOPASS) && (++i) < 50);
		if(i >= 50) {
			x = src->x;
			y = src->y;
		}
		dx = x - bl->x;
		dy = y - bl->y;
		skill_unit_move_unit_group(sg, src->m, dx, dy);
	}

	return 0;
}

/*==========================================
 * 蜃気楼分身
 *------------------------------------------
 */
int skill_shinkirou( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	unsigned int tick;
	int skillid;
	int skilllv;
	int ar;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	skillid = va_arg(ap,int);
	tick = va_arg(ap,unsigned int);

	if(sg->src_id == src->id && sg->unit_id == UNT_SHINKIROU) {
		if(src->type == BL_PC) {
			skilllv = pc_checkskill((struct map_session_data *)src,skillid);
		} else {
			skilllv = skill_get_max(skillid);
		}
		ar = skill_get_area(skillid,skilllv);
		clif_skill_nodamage(&unit->bl,&unit->bl,skillid,skilllv,1);
		map_foreachinarea(skill_area_sub,
			unit->bl.m,unit->bl.x-ar,unit->bl.y-ar,unit->bl.x+ar,unit->bl.y+ar,BL_CHAR,
			src,skillid,skilllv,tick,BCT_ENEMY|2,
			skill_castend_damage_id);
	}

	return 0;
}

/*==========================================
 * 風魔手裏剣 -構築-
 *------------------------------------------
 */
int skill_fuumakouchiku( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	unsigned int tick;
	int skilllv;
	int ar;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	skilllv = va_arg(ap,int);
	tick = va_arg(ap,unsigned int);

	if(sg->src_id == src->id && sg->unit_id == UNT_FUUMASHOUAKU) {
		ar = skill_get_area(SS_FUUMAKOUCHIKU,skilllv);
		skill_delunitgroup(sg);
		map_foreachinarea(skill_area_sub,
			unit->bl.m,unit->bl.x-ar,unit->bl.y-ar,unit->bl.x+ar,unit->bl.y+ar,BL_CHAR,
			src,SS_FUUMAKOUCHIKU,skilllv,tick,BCT_ENEMY|1,
			skill_castend_damage_id);
	}

	return 0;
}

/*==========================================
 * 苦無 -屈折-
 *------------------------------------------
 */
int skill_kunaikussetsu( struct block_list *bl, va_list ap )
{
	struct block_list *src;
	struct skill_unit *unit;
	struct skill_unit_group *sg;
	int skilllv;

	nullpo_retr(0, bl);
	nullpo_retr(0, src = va_arg(ap,struct block_list *));
	nullpo_retr(0, unit = (struct skill_unit *)bl);
	nullpo_retr(0, sg = unit->group);

	skilllv = va_arg(ap,int);

	if(sg->src_id == src->id && sg->unit_id == UNT_KUNAIWAIKYOKU) {
		skill_delunitgroup(sg);
		skill_unitsetting(src,SS_KUNAIKUSSETSU,skilllv,bl->x,bl->y,0);
	}

	return 0;
}

/*==========================================
 * キャスリングのターゲット変更
 *------------------------------------------
 */
int skill_castle_mob_changetarget(struct block_list *bl,va_list ap)
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
		case AB_DUPLELIGHT_MELEE:	// グレイアムライト
		case AB_DUPLELIGHT_MAGIC:	// ミリアムライト
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
	int i, skill = 0, rate = 0, t_rate = 0;

	nullpo_retr(0, src);

	sc = status_get_sc(src);
	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;
	if(bl){
		tsc = status_get_sc(bl);
		if(bl->type == BL_PC)
			tsd = (struct map_session_data *)bl;
	}

	// H.Plusによるヒール効果向上
	rate += status_get_hplus(src);

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
		if(pc_checkskill(sd,SU_POWEROFSEA) > 0) {
			skill += 50;
			if(pc_checkskill_summoner(sd, SU_POWEROFSEA) >= 20)
				skill += 100;
		}
		// 海の魂(新鮮なエビ)
		if(skill_id == SU_FRESHSHRIMP && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)
			skill += 30;
		// トランセンデンス
		skill += pc_checkskill(sd,NV_TRANSCENDENCE) * 3;
	}

#ifndef PRE_RENEWAL
	if(skill > 0)
		rate += skill;
#endif

	if(rate > 0)
		heal += heal * rate / 100;

#ifndef PRE_RENEWAL
	// Matkの加算
	if(skill_id == AL_HEAL || skill_id == AB_CHEAL || skill_id == AB_HIGHNESSHEAL || skill_id == CD_DILECTIO_HEAL)
		heal += battle_calc_base_magic_damage(src);
#endif

	if(tsd) {
		// ブレイクスルー
		t_rate += pc_checkskill(tsd,NV_BREAKTHROUGH) * 2;

		if(tsd->skill_subhealup.count > 0 && heal > 0 && skill_id > 0) {
			for(i = 0; i < tsd->skill_subhealup.count; i++) {
				if(skill_id == tsd->skill_subhealup.id[i]) {
					t_rate += tsd->skill_subhealup.rate[i];
					break;
				}
			}
		}
		if(t_rate > 0)
			heal += heal * t_rate / 100;
	}

	if(tsc && tsc->data[SC_CRITICALWOUND].timer != -1)
		heal = heal * (100 - tsc->data[SC_CRITICALWOUND].val2) / 100;
	if(tsc && tsc->data[SC_DEATHHURT].timer != -1)
		heal = heal * (100 - tsc->data[SC_DEATHHURT].val2) / 100;

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
			case RL_FIRE_RAIN:
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
	// ファイアーレイン
	firerain_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 3;
		if (i==2 || i==6) {		/* 	左右 */
			int dx[] = { 0, 0, 0};
			int dy[] = {-1, 0, 1};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		} else {			/* 上下 */
			int dx[] = {-1, 0, 1};
			int dy[] = { 0, 0, 0};
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
		"db/skill_require_db2.txt","db/pre/skill_require_db2_pre.txt","db/addon/skill_require_db2_add.txt",
		"db/skill_cast_db.txt",    "db/pre/skill_cast_db_pre.txt",    "db/addon/skill_cast_db_add.txt",
		"db/skill_unit_db.txt",    "db/pre/skill_unit_db_pre.txt",    "db/addon/skill_unit_db_add.txt",
		"db/produce_db.txt",       "db/pre/produce_db_pre.txt",       "db/addon/produce_db_add.txt"
	};
	const int max = 3;
#else
	const char *filename[] = {
		"db/skill_db.txt",         "db/addon/skill_db_add.txt",
		"db/skill_require_db.txt", "db/addon/skill_require_db_add.txt",
		"db/skill_require_db2.txt","db/addon/skill_require_db2_add.txt",
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
			j = skill_split_str(line,split,17);
			if(split[16]==NULL || j<17)
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
			skill_split_atoi(split[14],skill_db[i].area,MAX_SKILL_LEVEL);
			skill_split_atoi(split[15],skill_db[i].heal_ap,MAX_SKILL_LEVEL);
			memcpy(skill_db[i].name,split[16],31);
			skill_db[i].name[30] = '\0';	// froce \0 terminal
			strdb_insert(skillname_db,skill_db[i].name,&skill_db[i]);
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
		skill_db[i].autoshadowspell = atoi(split[7]);
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
			j = skill_split_str(line,split,33);
			if(split[32]==NULL || j<33)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].hp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[2],skill_db[i].sp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[3],skill_db[i].ap,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].hp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].sp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[6],skill_db[i].ap_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[7],skill_db[i].zeny,MAX_SKILL_LEVEL);

			skill_db[i].weapon = 0;
			p = split[8];
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

			if( strcmpi(split[9],"hiding") == 0 )                   skill_db[i].state = SST_HIDING;
			else if( strcmpi(split[9],"cloaking") == 0 )            skill_db[i].state = SST_CLOAKING;
			else if( strcmpi(split[9],"chasewalking") == 0 )        skill_db[i].state = SST_CHASEWALKING;
			else if( strcmpi(split[9],"hidden") == 0 )              skill_db[i].state = SST_HIDDEN;
			else if( strcmpi(split[9],"riding") == 0 )              skill_db[i].state = SST_RIDING;
			else if( strcmpi(split[9],"falcon") == 0 )              skill_db[i].state = SST_FALCON;
			else if( strcmpi(split[9],"cart") == 0 )                skill_db[i].state = SST_CART;
			else if( strcmpi(split[9],"shield") == 0 )              skill_db[i].state = SST_SHIELD;
			else if( strcmpi(split[9],"sight") == 0 )               skill_db[i].state = SST_SIGHT;
			else if( strcmpi(split[9],"explosionspirits") == 0 )    skill_db[i].state = SST_EXPLOSIONSPIRITS;
			else if( strcmpi(split[9],"cartboost") == 0 )           skill_db[i].state = SST_CARTBOOST;
			else if( strcmpi(split[9],"nen") == 0 )                 skill_db[i].state = SST_NEN;
			else if( strcmpi(split[9],"recover_weight_rate") == 0 ) skill_db[i].state = SST_RECOV_WEIGHT_RATE;
			else if( strcmpi(split[9],"move_enable") == 0 )         skill_db[i].state = SST_MOVE_ENABLE;
			else if( strcmpi(split[9],"water") == 0 )               skill_db[i].state = SST_WATER;
			else if( strcmpi(split[9],"dragon") == 0 )              skill_db[i].state = SST_DRAGON;
			else if( strcmpi(split[9],"wolf") == 0 )                skill_db[i].state = SST_WOLF;
			else if( strcmpi(split[9],"gear") == 0 )                skill_db[i].state = SST_GEAR;
			else                                                    skill_db[i].state = SST_NONE;

			skill_split_atoi(split[10],skill_db[i].spiritball,MAX_SKILL_LEVEL);
			skill_db[i].itemid[0] = atoi(split[11]);
			skill_db[i].amount[0] = atoi(split[12]);
			skill_db[i].itemid[1] = atoi(split[13]);
			skill_db[i].amount[1] = atoi(split[14]);
			skill_db[i].itemid[2] = atoi(split[15]);
			skill_db[i].amount[2] = atoi(split[16]);
			skill_db[i].itemid[3] = atoi(split[17]);
			skill_db[i].amount[3] = atoi(split[18]);
			skill_db[i].itemid[4] = atoi(split[19]);
			skill_db[i].amount[4] = atoi(split[20]);
			skill_db[i].itemid[5] = atoi(split[21]);
			skill_db[i].amount[5] = atoi(split[22]);
			skill_db[i].itemid[6] = atoi(split[23]);
			skill_db[i].amount[6] = atoi(split[24]);
			skill_db[i].itemid[7] = atoi(split[25]);
			skill_db[i].amount[7] = atoi(split[26]);
			skill_db[i].itemid[8] = atoi(split[27]);
			skill_db[i].amount[8] = atoi(split[28]);
			skill_db[i].itemid[9] = atoi(split[29]);
			skill_db[i].amount[9] = atoi(split[30]);
			skill_split_atoi(split[31],skill_db[i].lv_itemid,MAX_SKILL_LEVEL);
			skill_split_atoi(split[32],skill_db[i].lv_amount,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキル要求データベース2 */
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
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* キャスティングデータベース */
	for(m = max * 3; m < max * 4; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 3)
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
	for(m = max * 4; m < max * 5; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 4)
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
			skill_split_atoi(split[5],skill_db[i].unit_interval,MAX_SKILL_LEVEL);
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

	for(m = max * 5; m < max * 6; m++) {
		int count = 0;
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 5)
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
 * 終了
 *------------------------------------------
 */
int do_final_skill(void)
{
	if(skillname_db)
		strdb_final(skillname_db,NULL);
	return 0;
}

/*==========================================
 * スキル関係初期化処理
 *------------------------------------------
 */
int do_init_skill(void)
{
	unsigned int tick = gettick();

	skillname_db = strdb_init(31);

	skill_readdb();

	add_timer_func_list(skill_unit_timer);
	add_timer_func_list(skill_castend_id);
	add_timer_func_list(skill_castend_pos);
	add_timer_func_list(skill_timerskill_timer);
	add_timer_func_list(skill_castend_delay_sub);

	add_timer_interval(tick+SKILLUNITTIMER_INVERVAL,skill_unit_timer,0,NULL,SKILLUNITTIMER_INVERVAL);

	return 0;
}
