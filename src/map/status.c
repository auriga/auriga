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

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "db.h"
#include "malloc.h"
#include "nullpo.h"
#include "timer.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "path.h"
#include "pet.h"
#include "homun.h"
#include "mob.h"
#include "clif.h"
#include "skill.h"
#include "itemdb.h"
#include "battle.h"
#include "status.h"
#include "status_calc_ctrl.h"
#include "status_internal.h"
#include "script.h"
#include "guild.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"
#include "elem.h"
#include "msg.h"
#include "bonus.h"
#include "date.h"

int atkmods[MAX_SIZE_FIX][WT_MAX];	// 武器ATKサイズ修正(size_fix.txt)

struct refine_db refine_db[MAX_WEAPON_LEVEL+1];

struct job_db job_db[PC_JOB_MAX];

int current_equip_item_index;	// ステータス計算用
int current_equip_name_id;

#ifdef DYNAMIC_SC_DATA
struct status_change_data dummy_sc_data[MAX_STATUSCHANGE];
#endif

static struct scdata_db scdata_db[MAX_STATUSCHANGE];	// ステータス異常データベース

int StatusIconChangeTable[MAX_STATUSCHANGE] = {
	/* 0- */
	SI_PROVOKE,SI_ENDURE,SI_TWOHANDQUICKEN,SI_CONCENTRATE,SI_BLANK,SI_CLOAKING,SI_ENCPOISON,SI_POISONREACT,SI_QUAGMIRE,SI_ANGELUS,
	/* 10- */
	SI_BLESSING,SI_SIGNUMCRUCIS,SI_INCREASEAGI,SI_DECREASEAGI,SI_SLOWPOISON,SI_IMPOSITIO,SI_SUFFRAGIUM,SI_ASPERSIO,SI_BENEDICTIO,SI_KYRIE,
	/* 20- */
	SI_MAGNIFICAT,SI_GLORIA,SI_AETERNA,SI_ADRENALINE,SI_WEAPONPERFECTION,SI_OVERTHRUST,SI_MAXIMIZEPOWER,SI_BLANK,SI_BLANK,SI_TRICKDEAD,
	/* 30- */
	SI_LOUD,SI_ENERGYCOAT,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_SPEEDPOTION0,SI_SPEEDPOTION1,SI_SPEEDPOTION2,
	/* 40- */
	SI_MOVHASTE_HORSE,SI_MOVHASTE_POT,SI_BLANK,SI_MOVESLOW_POTION,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 50- */
	SI_STRIPWEAPON,SI_STRIPSHIELD,SI_STRIPARMOR,SI_STRIPHELM,SI_CP_WEAPON,SI_CP_SHIELD,SI_CP_ARMOR,SI_CP_HELM,SI_AUTOGUARD,SI_REFLECTSHIELD,
	/* 60- */
	SI_DEVOTION,SI_PROVIDENCE,SI_DEFENDER,SI_BLANK,SI_BLANK,SI_AUTOSPELL,SI_BLANK,SI_BLANK,SI_SPEARQUICKEN,SI_BLANK,
	/* 70- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 80- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_EXPLOSIONSPIRITS,SI_STEELBODY,SI_BLANK,SI_COMBO,
	/* 90- */
	SI_FLAMELAUNCHER,SI_FROSTWEAPON,SI_LIGHTNINGLOADER,SI_SEISMICWEAPON,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 100- */
	SI_BLANK,SI_BLANK,SI_WE_FEMALE,SI_AURABLADE,SI_PARRYING,SI_CONCENTRATION,SI_TENSIONRELAX,SI_BERSERK,SI_BLANK,SI_BLANK,
	/* 110- */
	SI_ASSUMPTIO,SI_BLANK,SI_BLANK,SI_MAGICPOWER,SI_EDP,SI_TRUESIGHT,SI_WINDWALK,SI_MELTDOWN,SI_CARTBOOST,SI_CHASEWALK,
	/* 120- */
	SI_REJECTSWORD,SI_MARIONETTE,SI_MARIONETTE2,SI_BLANK,SI_HEADCRUSH,SI_JOINTBEAT,SI_BLANK,SI_BLANK,SI_BODYSTATE_STONECURSE,SI_BODYSTATE_FREEZING,
	/* 130- */
	SI_BODYSTATE_STUN,SI_BODYSTATE_SLEEP,SI_HEALTHSTATE_POISON,SI_HEALTHSTATE_CURSE,SI_HEALTHSTATE_SILENCE,SI_HEALTHSTATE_CONFUSION,SI_HEALTHSTATE_BLIND,SI_HEADCRUSH,SI_BLANK,SI_BLANK,
	/* 140- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 150- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 160- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 170- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 180- */
	SI_BLANK,SI_BLANK,SI_HEALTHSTATE_HEAVYPOISON,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 190- */
	SI_BLANK,SI_MAGNUM,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 200- */
	SI_BLANK,SI_PRESERVE,SI_OVERTHRUSTMAX,SI_CHASEWALK_STR,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 210- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 220- */
	SI_TAROTCARD,SI_TAROTCARD,SI_TAROTCARD,SI_TAROTCARD,SI_MEAL_INCSTR,SI_MEAL_INCAGI,SI_MEAL_INCVIT,SI_MEAL_INCINT,SI_MEAL_INCDEX,SI_MEAL_INCLUK,
	/* 230- */
	SI_RUN,SI_SPURT,SI_BLANK,SI_DODGE,SI_BLANK,SI_BLANK,SI_BLANK,SI_WARM,SI_BLANK,SI_BLANK,
	/* 240- */
	SI_SUN_COMFORT,SI_MOON_COMFORT,SI_STAR_COMFORT,SI_BLANK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,
	/* 250- */
	SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,
	/* 260- */
	SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_KAIZEL,SI_KAAHI,SI_KAUPE,SI_KAITE,SI_SMA,SI_BLANK,
	/* 270- */
	SI_BLANK,SI_BLANK,SI_ONEHAND,SI_READYSTORM,SI_READYDOWN,SI_READYTURN,SI_READYCOUNTER,SI_BLANK,SI_AUTOBERSERK,SI_BLANK,
	/* 280- */
	SI_DOUBLECASTING,SI_ELEMENTFIELD,SI_DARKELEMENT,SI_ATTENELEMENT,SI_MIRACLE,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BABY,
	/* 290- */
	SI_BLANK,SI_SHRINK,SI_CLOSECONFINE,SI_SIGHTBLASTER,SI_BLANK,SI_MEAL_INCHIT,SI_MEAL_INCFLEE,SI_BLANK,SI_MEAL_INCCRITICAL,SI_BLANK,
	/* 300- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 310- */
	SI_BLANK,SI_BLANK,SI_UNDEAD,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 320- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 330- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_TIGEREYE,SI_BLANK,SI_BLANK,
	/* 340- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_STOP,SI_BLANK,SI_BLANK,SI_BLANK,SI_MADNESSCANCEL,SI_ADJUSTMENT,
	/* 350- */
	SI_INCREASING,SI_BLANK,SI_GATLINGFEVER,SI_BLANK,SI_BLANK,SI_UTSUSEMI,SI_BUNSINJYUTSU,SI_BLANK,SI_NEN,SI_BLANK,
	/* 360- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_ADRENALINE2,SI_BLANK,SI_BLANK,SI_COMBATHAN,SI_LIFEINSURANCE,
	/* 370- */
	SI_ITEMDROPRATE,SI_BOSSMAPINFO,SI_MEAL_INCSTR2,SI_MEAL_INCAGI2,SI_MEAL_INCVIT2,SI_MEAL_INCDEX2,SI_MEAL_INCINT2,SI_MEAL_INCLUK2,SI_SLOWCAST,SI_CRITICALWOUND,
	/* 380- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_HAPPY,SI_BLANK,SI_BLANK,SI_HELLPOWER,SI_ENCHANTBLADE,SI_BLANK,
	/* 390- */
	SI_REFRESH,SI_GIANTGROWTH,SI_STONEHARDSKIN,SI_VITALITYACTIVATION,SI_FIGHTINGSPIRIT,SI_ABUNDANCE,SI_DEATHBOUND,SI_HEALTHSTATE_FEAR,SI_VENOMIMPRESS,SI_POISONINGWEAPON,
	/* 400- */
	SI_WEAPONBLOCKING,SI_WEAPONBLOCKING_POSTDELAY,SI_CLOAKINGEXCEED,SI_HALLUCINATIONWALK,SI_HALLUCINATIONWALK_POSTDELAY,SI_ROLLINGCUTTER,SI_TOXIN,SI_PARALIZE,SI_VENOMBLEED,SI_MAGICMUSHROOM,
	/* 410- */
	SI_DEATHHURT,SI_PYREXIA,SI_OBLIVIONCURSE,SI_LEECHEND,SI_EPICLESIS,SI_ORATIO,SI_LAUDAAGNUS,SI_LAUDARAMUS,SI_RENOVATIO,SI_EXPIATIO,
	/* 420- */
	SI_DUPLELIGHT,SI_SACRAMENT,SI_BODYSTATE_IMPRISON,SI_FROSTMISTY,SI_MARSHOFABYSS,SI_RECOGNIZEDSPELL,SI_STASIS,SI_BODYSTATE_BURNNING,SI_SUMMONBALL1,SI_SUMMONBALL2,
	/* 430- */
	SI_SUMMONBALL3,SI_SUMMONBALL4,SI_SUMMONBALL5,SI_BLANK,SI_FEARBREEZE,SI_ELECTRICSHOCKER,SI_WUGDASH,SI_WUGBITE,SI_CAMOUFLAGE,SI_ACCELERATION,
	/* 440- */
	SI_HOVERING,SI_OVERHEAT,SI_SHAPESHIFT,SI_INFRAREDSCAN,SI_ANALYZE,SI_MAGNETICFIELD,SI_NEUTRALBARRIER_MASTER,SI_NEUTRALBARRIER,SI_STEALTHFIELD_MASTER,SI_STEALTHFIELD,
	/* 450- */
	SI_MANU_ATK,SI_MANU_DEF,SI_MANU_MATK,SI_SPL_ATK,SI_SPL_DEF,SI_SPL_MATK,SI_REPRODUCE,SI_AUTOSHADOWSPELL,SI_SHADOWFORM,SI_BODYPAINT,
	/* 460- */
	SI_INVISIBILITY,SI_DEADLYINFECT,SI_ENERVATION,SI_GROOMY,SI_IGNORANCE,SI_LAZINESS,SI_UNLUCKY,SI_WEAKNESS,SI_STRIPACCESSARY,SI_MANHOLE,
	/* 470- */
	SI_BLOODYLUST,SI_REFLECTDAMAGE,SI_FORCEOFVANGUARD,SI_SHIELDSPELL_DEF,SI_SHIELDSPELL_MDEF,SI_SHIELDSPELL_REF,SI_EXEEDBREAK,SI_PRESTIGE,SI_BANDING,SI_SITDOWN_FORCE,
	/* 480- */
	SI_EARTHDRIVE,SI_INSPIRATION,SI_FALLENEMPIRE,SI_CRESCENTELBOW,SI_CURSEDCIRCLE_ATKER,SI_CURSEDCIRCLE_TARGET,SI_LIGHTNINGWALK,SI_RAISINGDRAGON,SI_GENTLETOUCH_ENERGYGAIN,SI_GENTLETOUCH_CHANGE,
	/* 490- */
	SI_GENTLETOUCH_REVITALIZE,SI_SWING,SI_SYMPHONY_LOVE,SI_MOONLIT_SERENADE,SI_RUSH_WINDMILL,SI_ECHOSONG,SI_HARMONIZE,SI_NETHERWORLD,SI_SIREN,SI_DEEP_SLEEP,
	/* 500- */
	SI_SIRCLEOFNATURE,SI_GLOOMYDAY,SI_SONG_OF_MANA,SI_DANCE_WITH_WUG,SI_SATURDAY_NIGHT_FEVER,SI_LERADS_DEW,SI_MELODYOFSINK,SI_BEYOND_OF_WARCRY,SI_UNLIMITED_HUMMING_VOICE,SI_PROPERTYWALK,
	/* 510- */
	SI_SPELLFIST,SI_DIAMONDDUST,SI_BLANK,SI_STRIKING,SI_WARMER,SI_VACUUM_EXTREME,SI_GN_CARTBOOST,SI_THORNS_TRAP,SI_BLOOD_SUCKER,SI_SPORE_EXPLOSION,
	/* 520- */
	SI_FIRE_EXPANSION_SMOKE_POWDER,SI_FIRE_EXPANSION_TEAR_GAS,SI_MANDRAGORA,SI_MELON_BOMB,SI_BANANA_BOMB,SI_MYSTERIOUS_POWDER,SI_BOOST500,SI_FULL_SWING_K,SI_MANA_PLUS,SI_MUSTLE_M,
	/* 530- */
	SI_LIFE_FORCE_F,SI_PROMOTE_HEALTH_RESERCH,SI_ENERGY_DRINK_RESERCH,SI_EXTRACT_WHITE_POTION_Z,SI_VITATA_500,SI_EXTRACT_SALAMINE_JUICE,SI_SAVAGE_STEAK,SI_COCKTAIL_WARG_BLOOD,SI_MINOR_BBQ,SI_SIROMA_ICE_TEA,
	/* 540- */
	SI_DROCERA_HERB_STEAMED,SI_PUTTI_TAILS_NOODLES,SI_STOMACHACHE,SI_MONSTER_TRANSFORM,SI_IZAYOI,SI_KG_KAGEHUMI,SI_KYOMU,SI_KAGEMUSYA,SI_AKAITSUKI,SI_ALL_RIDING,
	/* 550- */
	SI_MEIKYOUSISUI,SI_KYOUGAKU,SI_ODINS_POWER,SI_CPLUSONLYJOBEXP,SI_MER_FLEE,SI_MER_ATK,SI_MER_HP,SI_MER_SP,SI_MER_HIT,SI_ON_PUSH_CART,
	/* 560- */
	SI_ZENKAI,SI_KO_JYUMONJIKIRI,SI_SUMMON_AGNI,SI_CIRCLE_OF_FIRE,SI_CIRCLE_OF_FIRE_OPTION,SI_FIRE_CLOAK,SI_FIRE_CLOAK_OPTION,SI_WATER_SCREEN,SI_WATER_SCREEN_OPTION,SI_WATER_DROP,
	/* 570- */
	SI_WATER_DROP_OPTION,SI_WATER_BARRIER,SI_WIND_STEP,SI_WIND_STEP_OPTION,SI_WIND_CURTAIN,SI_WIND_CURTAIN_OPTION,SI_ZEPHYR,SI_SOLID_SKIN,SI_SOLID_SKIN_OPTION,SI_STONE_SHIELD,
	/* 580- */
	SI_STONE_SHIELD_OPTION,SI_POWER_OF_GAIA,SI_PYROTECHNIC,SI_PYROTECHNIC_OPTION,SI_HEATER,SI_HEATER_OPTION,SI_TROPIC,SI_TROPIC_OPTION,SI_AQUAPLAY,SI_AQUAPLAY_OPTION,
	/* 590- */
	SI_COOLER,SI_COOLER_OPTION,SI_CHILLY_AIR,SI_CHILLY_AIR_OPTION,SI_GUST,SI_GUST_OPTION,SI_BLAST,SI_BLAST_OPTION,SI_WILD_STORM,SI_WILD_STORM_OPTION,
	/* 600- */
	SI_PETROLOGY,SI_PETROLOGY_OPTION,SI_CURSED_SOIL,SI_CURSED_SOIL_OPTION,SI_UPHEAVAL,SI_UPHEAVAL_OPTION,SI_TIDAL_WEAPON,SI_TIDAL_WEAPON_OPTION,SI_ROCK_CRUSHER,SI_ROCK_CRUSHER_ATK,
	/* 610- */
	SI_FIRE_INSIGNIA,SI_WATER_INSIGNIA,SI_WIND_INSIGNIA,SI_EARTH_INSIGNIA,SI_HAT_EFFECT,SI_JP_EVENT01,SI_JP_EVENT02,SI_JP_EVENT03,SI_JP_EVENT04,SI_ACTIVE_MONSTER_TRANSFORM,
	/* 620- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_ZANGETSU,SI_GENSOU,SI_ASSUMPTIO2,SI_PHI_DEMON,SI_PLUSATTACKPOWER,SI_PLUSMAGICPOWER,SI_ALMIGHTY,
	/* 630- */
	SI_DARKCROW,SI_UNLIMIT,SI_BLANK,SI_FRIGG_SONG,SI_OFFERTORIUM,SI_TELEKINESIS_INTENSE,SI_KINGS_GRACE,SI_FULL_THROTTLE,SI_REBOUND,SI_BLANK,
	/* 640- */
	SI_SUHIDE,SI_SU_STOOP,SI_CATNIPPOWDER,SI_SV_ROOTTWIST,SI_BITESCAR,SI_ARCLOUSEDASH,SI_TUNAPARTY,SI_SHRIMP,SI_FRESHSHRIMP,SI_HISS,
	/* 650- */
	SI_NYANGGRASS,SI_CHATTERING,SI_GROOMING,SI_PROTECTIONOFSHRIMP,SI_BLANK,SI_BURNT,SI_CHILL,SI_MAXPAIN,SI_HEAT_BARREL,SI_BLANK,
	/* 660- */
	SI_P_ALTER,SI_E_CHAIN,SI_C_MARKER,SI_ANTI_M_BLAST,SI_B_TRAP,SI_H_MINE,SI_E_QD_SHOT_READY,SI_OVERLAPEXPUP,SI_JP_OTP,SI_MOVHASTE_INFINITY,
	/* 670- */
	SI_NEEDLE_OF_PARALYZE,SI_PAIN_KILLER,SI_LIGHT_OF_REGENE,SI_OVERED_BOOST,SI_STYLE_CHANGE,SI_TINDER_BREAKER,SI_CBC,SI_EQC,SI_GOLDENE_FERSE,SI_ANGRIFFS_MODUS,
	/* 680- */
	SI_MAGMA_FLOW,SI_GRANITIC_ARMOR,SI_PYROCLASTIC,SI_VOLCANIC_ASH,SI_ALL_STAT_DOWN,SI_GRADUAL_GRAVITY,SI_DAMAGE_HEAL,SI_IMMUNE_PROPERTY_NOTHING,SI_IMMUNE_PROPERTY_WATER,SI_IMMUNE_PROPERTY_GROUND,
	/* 690- */
	SI_IMMUNE_PROPERTY_FIRE,SI_IMMUNE_PROPERTY_WIND,SI_IMMUNE_PROPERTY_DARKNESS,SI_IMMUNE_PROPERTY_SAINT,SI_IMMUNE_PROPERTY_POISON,SI_IMMUNE_PROPERTY_TELEKINESIS,SI_IMMUNE_PROPERTY_UNDEAD,SI_KILLING_AURA,SI_PC_STOP,SI_LIGHTOFMOON,
	/* 700- */
	SI_LIGHTOFSUN,SI_LIGHTOFSTAR,SI_LUNARSTANCE,SI_UNIVERSESTANCE,SI_SUNSTANCE,SI_BLANK,SI_NEWMOON,SI_STARSTANCE,SI_DIMENSION,SI_DIMENSION1,
	/* 710- */
	SI_DIMENSION2,SI_CREATINGSTAR,SI_FALLINGSTAR,SI_NOVAEXPLOSING,SI_GRAVITYCONTROL,SI_SOULCOLLECT,SI_SOULREAPER,SI_SOULUNITY,SI_SOULSHADOW,SI_SOULFAIRY,
	/* 720- */
	SI_SOULFALCON,SI_SOULGOLEM,SI_SOULDIVISION,SI_BLANK,SI_BLANK,SI_BLANK,SI_SHA,SI_SOULCURSE,SI_CRUSHSTRIKE,SI_WEAPONBLOCK_ON,
	/* 730- */
	SI_ADORAMUS,SI_OVERHEAT_LIMITPOINT,SI_BLANK,SI_GS_MAGICAL_BULLET,SI_HELPANGEL,SI_HANDICAPSTATE_DEEPBLIND,SI_HANDICAPSTATE_DEEPSILENCE,SI_HANDICAPSTATE_LASSITUDE,SI_HANDICAPSTATE_FROSTBITE,SI_HANDICAPSTATE_SWOONING,
	/* 740- */
	SI_HANDICAPSTATE_LIGHTNINGSTRIKE,SI_HANDICAPSTATE_CRYSTALLIZATION,SI_HANDICAPSTATE_CONFLAGRATION,SI_HANDICAPSTATE_MISFORTUNE,SI_HANDICAPSTATE_DEADLYPOISON,SI_HANDICAPSTATE_DEPRESSION,SI_HANDICAPSTATE_HOLYFLAME,SI_SERVANTWEAPON,SI_SERVANT_SIGN,SI_CHARGINGPIERCE,
	/* 750- */
	SI_CHARGINGPIERCE_COUNT,SI_DRAGONIC_AURA,SI_VIGOR,SI_DEADLY_DEFEASANCE,SI_CLIMAX_DES_HU,SI_CLIMAX,SI_CLIMAX_EARTH,SI_CLIMAX_BLOOM,SI_CLIMAX_CRYIMP,SI_POWERFUL_FAITH,
	/* 760- */
	SI_FIRM_FAITH,SI_HOLY_OIL,SI_SINCERE_FAITH,SI_MASSIVE_F_BLASTER,SI_FIRST_BRAND,SI_FIRST_FAITH_POWER,SI_SECOND_JUDGE,SI_SECOND_BRAND,SI_THIRD_EXOR_FLAME,SI_GUARD_STANCE,
	/* 770- */
	SI_GUARDIAN_S,SI_REBOUND_S,SI_ATTACK_STANCE,SI_ULTIMATE_S,SI_HOLY_S,SI_SPEAR_SCAR,SI_SHIELD_POWER,SI_MEDIALE,SI_A_VITA,SI_A_TELUM,
	/* 780- */
	SI_PRE_ACIES,SI_COMPETENTIA,SI_RELIGIO,SI_BENEDICTUM,SI_SHADOW_EXCEED,SI_DANCING_KNIFE,SI_E_SLASH_COUNT,SI_POTENT_VENOM,SI_SHADOW_WEAPON,SI_SHADOW_SCAR,
	/* 790- */
	SI_AXE_STOMP,SI_RUSH_QUAKE1,SI_RUSH_QUAKE2,SI_A_MACHINE,SI_D_MACHINE,SI_ABR_BATTLE_WARIOR,SI_ABR_DUAL_CANNON,SI_ABR_MOTHER_NET,SI_ABR_INFINITY,SI_SHADOW_STRIP,
	/* 800- */
	SI_ABYSS_DAGGER,SI_ABYSSFORCEWEAPON,SI_ABYSS_SLAYER,SI_WINDSIGN,SI_CALAMITYGALE,SI_CRESCIVEBOLT,SI_PROTECTSHADOWEQUIP,SI_RESEARCHREPORT,SI_BO_HELL_DUSTY,SI_BLANK,
	/* 810- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_MYSTIC_SYMPHONY,SI_KVASIR_SONATA,SI_ROSEBLOSSOM,SI_SOUNDBLEND,SI_GEF_NOCTURN,SI_AIN_RHAPSODY,SI_MUSICAL_INTERLUDE,
	/* 820- */
	SI_JAWAII_SERENADE,SI_PRON_MARCH,SI_SPELL_ENCHANTING,SI_SUMMON_ELEMENTAL_ARDOR,SI_SUMMON_ELEMENTAL_DILUVIO,SI_SUMMON_ELEMENTAL_PROCELLA,SI_SUMMON_ELEMENTAL_TERREMOTUS,SI_SUMMON_ELEMENTAL_SERPENS,SI_FLAMETECHNIC,SI_FLAMETECHNIC_OPTION,
	/* 830- */
	SI_FLAMEARMOR,SI_FLAMEARMOR_OPTION,SI_COLD_FORCE,SI_COLD_FORCE_OPTION,SI_CRYSTAL_ARMOR,SI_CRYSTAL_ARMOR_OPTION,SI_GRACE_BREEZE,SI_GRACE_BREEZE_OPTION,SI_EYES_OF_STORM,SI_EYES_OF_STORM_OPTION,
	/* 840- */
	SI_EARTH_CARE,SI_EARTH_CARE_OPTION,SI_STRONG_PROTECTION,SI_STRONG_PROTECTION_OPTION,SI_DEEP_POISONING,SI_DEEP_POISONING_OPTION,SI_POISON_SHIELD,SI_POISON_SHIELD_OPTION,SI_ELEMENTAL_VEIL,SI_H_MINE_SPLASH,
	/* 850- */
	SI_INTENSIVE_AIM,SI_INTENSIVE_AIM_COUNT,SI_GRENADE_FRAGMENT_1,SI_GRENADE_FRAGMENT_2,SI_GRENADE_FRAGMENT_3,SI_GRENADE_FRAGMENT_4,SI_GRENADE_FRAGMENT_5,SI_GRENADE_FRAGMENT_6,SI_AUTO_FIRING_LAUNCHEREFST,SI_HIDDEN_CARD,
	/* 860- */
	SI_TALISMAN_OF_PROTECTION,SI_TALISMAN_OF_WARRIOR,SI_TALISMAN_OF_MAGICIAN,SI_TALISMAN_OF_FIVE_ELEMENTS,SI_T_FIRST_GOD,SI_T_SECOND_GOD,SI_T_THIRD_GOD,SI_T_FOURTH_GOD,SI_T_FIVETH_GOD,SI_HEAVEN_AND_EARTH,
	/* 870- */
	SI_HOGOGONG,SI_MARINE_FESTIVAL,SI_SANDY_FESTIVAL,SI_KI_SUL_RAMPAGE,SI_COLORS_OF_HYUN_ROK_1,SI_COLORS_OF_HYUN_ROK_2,SI_COLORS_OF_HYUN_ROK_3,SI_COLORS_OF_HYUN_ROK_4,SI_COLORS_OF_HYUN_ROK_5,SI_COLORS_OF_HYUN_ROK_6,
	/* 880- */
	SI_COLORS_OF_HYUN_ROK_BUFF,SI_TEMPORARY_COMMUNION,SI_BLESSING_OF_M_CREATURES,SI_BLESSING_OF_M_C_DEBUFF,SI_SHIELDCHAINRUSHF,SI_MISTYFROST,SI_GROUNDGRAVITY,SI_BREAKINGLIMIT,SI_RULEBREAK,SI_RISING_SUN,
	/* 890- */
	SI_NOON_SUN,SI_SUNSET_SUN,SI_RISING_MOON,SI_MIDNIGHT_MOON,SI_DAWN_MOON,SI_STAR_BURST,SI_SKY_ENCHANT,SI_SHADOW_CLOCK,SI_SHINKIROU_CALL,SI_NIGHTMARE,
};

/*==========================================
 * 過剰精錬ボーナス
 *------------------------------------------
 */
int status_get_overrefine_bonus(int lv)
{
	if(lv >= 0 && lv <= MAX_WEAPON_LEVEL)
		return refine_db[lv].over_bonus;
	return 0;
}

/*==========================================
 * 精錬成功率
 *------------------------------------------
 */
int status_percentrefinery(struct map_session_data *sd,struct item *item)
{
	int percent;

	nullpo_retr(0, item);

	if(item->refine < 0 || item->refine >= MAX_REFINE)	// 値がエラーもしくは既に最大値なら0%
		return 0;

	percent = refine_db[itemdb_wlv(item->nameid)].per[(int)item->refine];

	if(battle_config.refinery_research_lv)
		percent += pc_checkskill(sd,BS_WEAPONRESEARCH);	// 武器研究スキル所持

	// 確率の有効範囲チェック
	if(percent > 100) {
		percent = 100;
	}
	if(percent < 0) {
		percent = 0;
	}

	return percent;
}

/*==========================================
 * 精錬成功率 千分率
 *------------------------------------------
 */
int status_percentrefinery_weaponrefine(struct map_session_data *sd,struct item *item)
{
	int percent;
	int joblv;
	int diff;

	nullpo_retr(0, sd);
	nullpo_retr(0, item);

	if(item->refine < 0 || item->refine >= MAX_REFINE)	// 値がエラーもしくは既に最大値なら0%
		return 0;

	if(sd->status.class_ == PC_CLASS_NC || sd->status.class_ == PC_CLASS_NC_H || sd->status.class_ == PC_CLASS_NC_B)
		joblv = 70;
	else if(sd->status.job_level > 70)
		joblv = 70;
	else
		joblv = sd->status.job_level;

	diff = joblv - 50;
	percent = refine_db[itemdb_wlv(item->nameid)].per[(int)item->refine]*10 + diff + 4 * diff;

	if(battle_config.allow_weaponrearch_to_weaponrefine)
		percent += pc_checkskill(sd,BS_WEAPONRESEARCH)*10;	// 武器研究スキル所持

	// 確率の有効範囲チェック
	if(percent > 1000) {
		percent = 1000;
	}
	if(percent < 0) {
		percent = 0;
	}

	return percent;
}

/*==========================================
 * セーブ可能なステータス異常かどうか
 *------------------------------------------
 */
int status_can_save(int type)
{
	if(type >= 0 && type < MAX_STATUSCHANGE) {
		if(scdata_db[type].save > 0)
			return 1;
	}
	return 0;
}

/*==========================================
 * diableなステータス異常かどうか
 *------------------------------------------
 */
int status_is_disable(int type,int mask)
{
	if(type >= 0 && type < MAX_STATUSCHANGE) {
		if(scdata_db[type].disable & mask)
			return 1;
	}
	return 0;
}

/*==========================================
 * 対象のgroupを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_group(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mobdb_search(((struct mob_data *)bl)->class_)->group_id;
	// PC PETは0（未設定)

	return 0;
}

/*==========================================
 * 対象のClassを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_class(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->class_;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.class_;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->class_;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.class_;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.class_;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->status.class_;

	return 0;
}

/*==========================================
 * 対象の方向を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_dir(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->dir;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->dir;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->dir;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->dir;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->dir;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->dir;

	return 0;
}

/*==========================================
 * 対象のレベルを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_lv(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mobdb_search(((struct mob_data *)bl)->class_)->lv;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.base_level;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->msd->pet.level;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.base_level;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->base_level;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->base_level;

	return 0;
}

/*==========================================
 * 対象の職業レベルを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_jlv(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mobdb_search(((struct mob_data *)bl)->class_)->lv;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.job_level;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->msd->pet.level;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.base_level;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->base_level;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->base_level;

	return 0;
}

/*==========================================
 * 対象の射程を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_range(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mobdb_search(((struct mob_data *)bl)->class_)->range;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->range.attackrange;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return mobdb_search(((struct pet_data *)bl)->class_)->range;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return 2;//((struct homun_data *)bl)->attackrange;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->attackrange;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->attackrange;

	return 0;
}

/*==========================================
 * 対象のHPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_hp(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->hp;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.hp;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.hp;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.hp;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->status.hp;

	return 1;
}

/*==========================================
 * 対象のSPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_sp(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.sp;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.sp;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.sp;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return ((struct elem_data *)bl)->status.sp;

	return 0;
}

/*==========================================
 * 対象のAPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_ap(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.ap;

	return 0;
}

/*==========================================
 * 対象のMHPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_max_hp(struct block_list *bl)
{
	int max_hp = 1;

	nullpo_retr(1, bl);

	if(bl->type == BL_PC && ((struct map_session_data *)bl)) {
		max_hp = ((struct map_session_data *)bl)->status.max_hp;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		max_hp = ((struct homun_data *)bl)->max_hp;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		max_hp = ((struct merc_data *)bl)->max_hp;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		max_hp = ((struct elem_data *)bl)->max_hp;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && ((struct mob_data*)bl)) {
			atn_bignumber hp = ((struct mob_data*)bl)->st.max_hp;
			struct guild_castle *gc = guild_mapid2gc(bl->m);
			if(mobdb_search(((struct mob_data*)bl)->class_)->mexp > 0) {
				if(battle_config.mvp_hp_rate != 100) {
					hp = hp * battle_config.mvp_hp_rate / 100;
				}
			} else {
				if(battle_config.monster_hp_rate != 100)
					hp = hp * battle_config.monster_hp_rate / 100;
			}
			if(gc && ((struct mob_data*)bl)->guild_id == gc->guild_id) {
				hp += gc->defense * 1000;
			}
			max_hp = (hp > 0x7FFFFFFF ? 0x7FFFFFFF : (int)hp);
		} else if(bl->type == BL_PET && ((struct pet_data*)bl)) {
			max_hp = mobdb_search(((struct pet_data*)bl)->class_)->max_hp;
			if(mobdb_search(((struct pet_data*)bl)->class_)->mexp > 0) {
				if(battle_config.mvp_hp_rate != 100) {
					atn_bignumber hp = (atn_bignumber)max_hp * battle_config.mvp_hp_rate / 100;
					max_hp = (hp > 0x7FFFFFFF ? 0x7FFFFFFF : (int)hp);
				}
			} else {
				if(battle_config.monster_hp_rate != 100)
					max_hp = (max_hp * battle_config.monster_hp_rate)/100;
			}
		}
		if(sc) {
#ifndef PRE_RENEWAL
			if(sc->data[SC_DELUGE].timer != -1)
				max_hp += sc->data[SC_DELUGE].val3 * max_hp / 100;
#endif
			if(sc->data[SC_APPLEIDUN].timer != -1)
				max_hp += ((5+sc->data[SC_APPLEIDUN].val1*2+((sc->data[SC_APPLEIDUN].val2+1)>>1)
						+sc->data[SC_APPLEIDUN].val3/10) * max_hp)/100;
			if(sc->data[SC_FRIGG_SONG].timer != -1)
				max_hp += sc->data[SC_FRIGG_SONG].val3 * max_hp / 100;
			if(sc->data[SC_EQC].timer != -1)
				max_hp -= sc->data[SC_EQC].val3 * max_hp / 100;
		}
		if(max_hp < 1) max_hp = 1;
	}

	return max_hp;
}

/*==========================================
 * 対象のMSPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_max_sp(struct block_list *bl)
{
	int max_sp = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && ((struct map_session_data *)bl)) {
		max_sp = ((struct map_session_data *)bl)->status.max_sp;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		max_sp = ((struct homun_data *)bl)->max_sp;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		max_sp = ((struct merc_data *)bl)->max_sp;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		max_sp = ((struct elem_data *)bl)->max_sp;
	}

	return max_sp;
}

/*==========================================
 * 対象のMaxAPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_max_ap(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && ((struct map_session_data *)bl))
		return ((struct map_session_data *)bl)->status.max_ap;

	return 0;
}

/*==========================================
 * 対象のStrを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_str(struct block_list *bl)
{
	int str = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && ((struct mob_data *)bl))
		str = ((struct mob_data *)bl)->st.str;
	else if(bl->type == BL_PC && ((struct map_session_data *)bl))
		return ((struct map_session_data *)bl)->paramc[0];
	else if(bl->type == BL_PET && ((struct pet_data *)bl))
		str = mobdb_search(((struct pet_data *)bl)->class_)->str;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		str = ((struct homun_data *)bl)->status.str;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		str = ((struct merc_data *)bl)->str;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		str = ((struct elem_data *)bl)->str;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_LOUD].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			str += 4;
		if( sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				str >>= 1;				// 悪魔/不死
			else
				str += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			str += 5;
		if(sc->data[SC_CHASEWALK_STR].timer != -1)
			str += sc->data[SC_CHASEWALK_STR].val1;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			str -= sc->data[SC_ALL_STAT_DOWN].val2;
	}
	if(str < 0) str = 0;
	return str;
}

/*==========================================
 * 対象のAgiを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_agi(struct block_list *bl)
{
	int agi = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		agi = ((struct mob_data *)bl)->st.agi;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		agi = ((struct map_session_data *)bl)->paramc[1];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		agi = mobdb_search(((struct pet_data *)bl)->class_)->agi;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		agi = ((struct homun_data *)bl)->agi;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		agi = ((struct merc_data *)bl)->agi;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		agi = ((struct elem_data *)bl)->agi;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_SPEEDUP1].timer != -1 && bl->type != BL_PC)	// 速度強化
			agi *= 3;
		if(sc->data[SC_INCREASEAGI].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1 && bl->type != BL_PC)	// 速度増加(PCはpc.cで)
			agi += 2+sc->data[SC_INCREASEAGI].val1;
		if(sc->data[SC_SUITON].timer != -1 && sc->data[SC_SUITON].val3 != 0 && bl->type != BL_PC)	// 水遁
			agi += sc->data[SC_SUITON].val3;
		if(sc->data[SC_CONCENTRATE].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			agi += agi*(2+sc->data[SC_CONCENTRATE].val1)/100;
		if(sc->data[SC_DECREASEAGI].timer != -1)	// 速度減少（オーバースキル仕様はAGI-50）
			agi -= (sc->data[SC_DECREASEAGI].val2)? 50: 2+sc->data[SC_DECREASEAGI].val1;
		if(sc->data[SC_QUAGMIRE].timer != -1)	// クァグマイア
#ifdef PRE_RENEWAL
			agi -= agi * sc->data[SC_QUAGMIRE].val1*10 / 100;
#else
			agi -= (agi/2 < sc->data[SC_QUAGMIRE].val1*10) ? agi/2 : sc->data[SC_QUAGMIRE].val1*10;
#endif
		if(sc->data[SC_MARSHOFABYSS].timer != -1)	// マーシュオブアビス
			agi -= agi * sc->data[SC_MARSHOFABYSS].val3 / 100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			agi += 5;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			agi -= sc->data[SC_ALL_STAT_DOWN].val2;
	}
	if(agi < 0) agi = 0;
	return agi;
}

/*==========================================
 * 対象のVitを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_vit(struct block_list *bl)
{
	int vit = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		vit = ((struct mob_data *)bl)->st.vit;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		vit = ((struct map_session_data *)bl)->paramc[2];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		vit = mobdb_search(((struct pet_data *)bl)->class_)->vit;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		vit = ((struct homun_data *)bl)->vit;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		vit = ((struct merc_data *)bl)->vit;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		vit = ((struct elem_data *)bl)->vit;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_STRIPARMOR].timer != -1 && bl->type != BL_PC)
			vit = vit*60/100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			vit += 5;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			vit -= sc->data[SC_ALL_STAT_DOWN].val2;
	}

	if(vit < 0) vit = 0;
	return vit;
}

/*==========================================
 * 対象のIntを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_int(struct block_list *bl)
{
	int int_ = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		int_ = ((struct mob_data *)bl)->st.int_;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		int_ = ((struct map_session_data *)bl)->paramc[3];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		int_ = mobdb_search(((struct pet_data *)bl)->class_)->int_;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		int_ = ((struct homun_data *)bl)->int_;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		int_ = ((struct merc_data *)bl)->int_;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		int_ = ((struct elem_data *)bl)->int_;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				int_ >>= 1;	// 悪魔/不死
			else
				int_ += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_STRIPHELM].timer != -1 && bl->type != BL_PC)
			int_ = int_*60/100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			int_ += 5;
		if(sc->data[SC__STRIPACCESSARY].timer != -1 && bl->type != BL_PC)	// ストリップアクセサリー
			int_ = int_ * 80 / 100;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			int_ -= sc->data[SC_ALL_STAT_DOWN].val2;
	}
	if(int_ < 0) int_ = 0;
	return int_;
}

/*==========================================
 * 対象のDexを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_dex(struct block_list *bl)
{
	int dex = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		dex = ((struct mob_data *)bl)->st.dex;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		dex = ((struct map_session_data *)bl)->paramc[4];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		dex = mobdb_search(((struct pet_data *)bl)->class_)->dex;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		dex = ((struct homun_data *)bl)->dex;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		dex = ((struct merc_data *)bl)->dex;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		dex = ((struct elem_data *)bl)->dex;

	if(sc && bl->type != BL_HOM) {
#ifdef PRE_RENEWAL
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)
			dex *= 3;	// NPC爆裂波動
#endif
		if(sc->data[SC_CONCENTRATE].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			dex += dex*(2+sc->data[SC_CONCENTRATE].val1)/100;

		if(sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				dex >>= 1;	// 悪魔/不死
			else
				dex += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_QUAGMIRE].timer != -1)	// クァグマイア
#ifdef PRE_RENEWAL
			dex -= dex * sc->data[SC_QUAGMIRE].val1*10 / 100;
#else
			dex -= (dex/2 < sc->data[SC_QUAGMIRE].val1*10) ? dex/2 : sc->data[SC_QUAGMIRE].val1*10;
#endif
		if(sc->data[SC_MARSHOFABYSS].timer != -1)	// マーシュオブアビス
			dex -= dex * sc->data[SC_MARSHOFABYSS].val3 / 100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			dex += 5;
		if(sc->data[SC__STRIPACCESSARY].timer != -1 && bl->type != BL_PC)	// ストリップアクセサリー
			dex = dex * 80 / 100;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			dex -= sc->data[SC_ALL_STAT_DOWN].val2;
	}
	if(dex < 0) dex = 0;
	return dex;
}

/*==========================================
 * 対象のLukを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_luk(struct block_list *bl)
{
	int luk = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		luk = ((struct mob_data *)bl)->st.luk;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		luk = ((struct map_session_data *)bl)->paramc[5];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		luk = mobdb_search(((struct pet_data *)bl)->class_)->luk;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		luk = ((struct homun_data *)bl)->luk;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		luk = ((struct merc_data *)bl)->luk;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		luk = ((struct elem_data *)bl)->luk;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_GLORIA].timer != -1 && bl->type != BL_PC)	// グロリア(PCはpc.cで)
			luk += 30;
		if(sc->data[SC_CURSE].timer != -1 )		// 呪い
			luk = 0;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			luk += 5;
		if(sc->data[SC__STRIPACCESSARY].timer != -1 && bl->type != BL_PC)	// ストリップアクセサリー
			luk = luk * 80 / 100;
		if(sc->data[SC_BANANA_BOMB].timer != -1 && bl->type != BL_PC)	// バナナ爆弾
			luk -= luk * sc->data[SC_BANANA_BOMB].val1 / 100;
		if(sc->data[SC_ALL_STAT_DOWN].timer != -1 && bl->type != BL_PC)	// オールステータスダウン
			luk -= sc->data[SC_ALL_STAT_DOWN].val2;
	}
	if(luk < 0) luk = 0;
	return luk;
}

/*==========================================
 * 対象のPowを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_pow(struct block_list *bl)
{
	int pow = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		pow = ((struct map_session_data *)bl)->paramc[6];

	if(pow < 0) pow = 0;
	return pow;
}

/*==========================================
 * 対象のStaを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_sta(struct block_list *bl)
{
	int sta = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		sta = ((struct map_session_data *)bl)->paramc[7];

	if(sta < 0) sta = 0;
	return sta;
}

/*==========================================
 * 対象のWisを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_wis(struct block_list *bl)
{
	int wis = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		wis = ((struct map_session_data *)bl)->paramc[8];

	if(wis < 0) wis = 0;
	return wis;
}

/*==========================================
 * 対象のSplを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_spl(struct block_list *bl)
{
	int spl = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		spl = ((struct map_session_data *)bl)->paramc[9];

	if(spl < 0) spl = 0;
	return spl;
}

/*==========================================
 * 対象のConを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_con(struct block_list *bl)
{
	int con = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		con = ((struct map_session_data *)bl)->paramc[10];

	if(con < 0) con = 0;
	return con;
}

/*==========================================
 * 対象のCrtを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_crt(struct block_list *bl)
{
	int crt = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		crt = ((struct map_session_data *)bl)->paramc[11];

	if(crt < 0) crt = 0;
	return crt;
}

/*==========================================
 * 対象のFleeを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_flee(struct block_list *bl)
{
	int flee = 1, target_count = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		flee = ((struct map_session_data *)bl)->flee;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		flee = ((struct homun_data *)bl)->flee;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		flee = ((struct merc_data *)bl)->flee;
	else if(bl->type == BL_ELEM && ((struct elem_data *)bl))
		flee = ((struct elem_data *)bl)->flee;
	else if(bl->type == BL_MOB && ((struct mob_data *)bl))
		flee = ((struct mob_data *)bl)->st.flee;
	else
		flee = status_get_agi(bl) + status_get_lv(bl);

#ifndef PRE_RENEWAL
	if(bl->type != BL_PC && bl->type != BL_HOM)
		flee += 100;
#endif

	/* 捕獲 */
	if(sc && (sc->data[SC_TINDER_BREAKER].timer != -1 || sc->data[SC_CBC].timer != -1))
		return 0;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_WHISTLE].timer != -1 && bl->type != BL_PC)
			flee += sc->data[SC_WHISTLE].val1 + sc->data[SC_WHISTLE].val2 + sc->data[SC_WHISTLE].val3;
		if(sc->data[SC_BLIND].timer != -1 && bl->type != BL_PC)
			flee -= flee*25/100;
		if(sc->data[SC_WINDWALK].timer != -1 && bl->type != BL_PC)		// ウィンドウォーク
			flee += sc->data[SC_WINDWALK].val2;
		if(sc->data[SC_SPIDERWEB].timer != -1 && bl->type != BL_PC)	// スパイダーウェブ
			flee -= 50;
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)	// THE SUN
			flee = flee*80/100;
		if(sc->data[SC_GATLINGFEVER].timer != -1 && bl->type != BL_PC)	// ガトリングフィーバー
			flee -= sc->data[SC_GATLINGFEVER].val1*5;
		if(sc->data[SC_ADJUSTMENT].timer != -1 && bl->type != BL_PC)	// アジャストメント
			flee += 30;
		if(sc->data[SC_FEAR].timer != -1 && bl->type != BL_PC)		// 恐怖
			flee -= flee*20/100;
		if(sc->data[SC_HALLUCINATIONWALK].timer != -1 && bl->type != BL_PC)		// ハルシネーションウォーク
			flee += sc->data[SC_HALLUCINATIONWALK].val1 * 50;
		if(sc->data[SC_INFRAREDSCAN].timer != -1 && bl->type != BL_PC)	// インフラレッドスキャン
			flee  -= flee*30/100;
		if(sc->data[SC__LAZINESS].timer != -1 && bl->type != BL_PC)		// マスカレード：レイジネス
			flee  -= flee*10/100;
		if(sc->data[SC_GLOOMYDAY].timer != -1 && bl->type != BL_PC)		// メランコリー
			flee -= sc->data[SC_GLOOMYDAY].val1 * 5 + 20;
		if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1 && bl->type != BL_PC)		// フライデーナイトフィーバー
			flee -= flee * (40 + sc->data[SC_SATURDAY_NIGHT_FEVER].val1 * 10) / 100;
		if(sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer != -1 && bl->type != BL_PC)	// ファイアーエクスパンション(煙幕)
			flee += flee * sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].val2 / 100;
		if(sc->data[SC_FIRE_EXPANSION_TEAR_GAS].timer != -1 && bl->type != BL_PC)	// ファイアーエクスパンション(催涙)
			flee -= flee * sc->data[SC_FIRE_EXPANSION_TEAR_GAS].val2 / 100;
#ifndef PRE_RENEWAL
		if(sc->data[SC_SPEARQUICKEN].timer != -1 && bl->type != BL_PC)      // スピアクイッケン
			flee += sc->data[SC_SPEARQUICKEN].val1 * 2;
#endif
		if(sc->data[SC_GROOMING].timer != -1 && bl->type != BL_PC)	// グルーミング
			flee += sc->data[SC_GROOMING].val2;
		if(sc->data[SC_C_MARKER].timer != -1 && bl->type != BL_PC)  // クリムゾンマーカー
			flee -= sc->data[SC_C_MARKER].val1 * 10;
		if(sc->data[SC_VOLCANIC_ASH].timer != -1 && sc->data[SC_VOLCANIC_ASH].val4 > 0) 	// 火山灰
			flee -= flee * sc->data[SC_VOLCANIC_ASH].val4 / 100;
		if(sc->data[SC_HANDICAPSTATE_DEEPBLIND].timer != -1 && bl->type != BL_PC)	// 漆黒
			flee = 0;
	}

	// 回避率補正
	if(bl->type != BL_HOM)
		target_count = unit_counttargeted(bl,battle_config.agi_penalty_count_lv);

	if(battle_config.agi_penalty_type > 0 && target_count >= battle_config.agi_penalty_count) {
		// ペナルティ設定より対象が多い
		if(battle_config.agi_penalty_type == 1) {
			// 回避率がagi_penalty_num%ずつ減少
			int flee_rate = (target_count-(battle_config.agi_penalty_count-1)) * battle_config.agi_penalty_num;
			flee = flee * (100 - flee_rate) / 100;
		} else if(battle_config.agi_penalty_type == 2) {
			// 回避率がagi_penalty_num分減少
			flee -= (target_count - (battle_config.agi_penalty_count - 1))*battle_config.agi_penalty_num;
		}
	}
	// 対人MAPでの減少効果
	if(battle_config.gvg_flee_penalty & 1 && map[bl->m].flag.gvg) {
		flee = flee*(200 - battle_config.gvg_flee_rate)/100;	// 実際にGvGでFleeを減少
	}
	if(battle_config.gvg_flee_penalty & 2 && map[bl->m].flag.pvp) {
		flee = flee*(200 - battle_config.gvg_flee_rate)/100;	// 実際にPvPでFleeを減少
	}
	if(flee < 1) flee = 1;

	return flee;
}

/*==========================================
 * 対象のHitを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_hit(struct block_list *bl)
{
	int hit = 0;

	nullpo_retr(1, bl);

#ifndef PRE_RENEWAL
	if(!(bl->type & (BL_PC | BL_HOM)))
		hit = 150;
#endif
	if(bl->type == BL_PC) {
		hit = ((struct map_session_data *)bl)->hit;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		hit += ((struct homun_data *)bl)->hit;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		hit += ((struct merc_data *)bl)->hit;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		hit += ((struct elem_data *)bl)->hit;
	} else if(bl->type == BL_MOB && ((struct mob_data *)bl)) {
		hit += ((struct mob_data *)bl)->st.hit;
	} else {
		struct status_change *sc = status_get_sc(bl);

		hit += status_get_dex(bl) + status_get_lv(bl);
		if(sc) {
#ifndef PRE_RENEWAL
			if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)	// NPC爆裂波動
				hit *= 2;
#endif
			if(sc->data[SC_HUMMING].timer != -1)
				hit += hit*(sc->data[SC_HUMMING].val1*2+sc->data[SC_HUMMING].val2 + sc->data[SC_HUMMING].val3)/100;
			if(sc->data[SC_TRUESIGHT].timer != -1)		// トゥルーサイト
				hit += 3*(sc->data[SC_TRUESIGHT].val1);
			if(sc->data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
				hit += 10*(sc->data[SC_CONCENTRATION].val1);
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				hit = hit*80/100;
			if(sc->data[SC_ADJUSTMENT].timer != -1 && bl->type != BL_PC) // アジャストメント
				hit -= 30;
			if(sc->data[SC_INCREASING].timer != -1 && bl->type != BL_PC) // インクリージングアキュラシー
				hit += 20;
			if(sc->data[SC_INCHIT].timer!=-1 && bl->type != BL_PC)	// ガイデッドアタック
				hit += sc->data[SC_INCHIT].val1;
			if(sc->data[SC_FEAR].timer != -1 && bl->type != BL_PC)	// 恐怖
				hit -= hit*20/100;
			if(sc->data[SC__GROOMY].timer != -1 && bl->type != BL_PC)	// マスカレード：グルーミー
				hit -= hit*(20*sc->data[SC__GROOMY].val1)/100;
			if(sc->data[SC_FIRE_EXPANSION_TEAR_GAS].timer != -1 && bl->type != BL_PC)	// ファイアーエクスパンション(催涙)
				hit -= hit*(sc->data[SC_FIRE_EXPANSION_TEAR_GAS].val2)/100;
			if(sc->data[SC_ILLUSIONDOPING].timer != -1 && bl->type != BL_PC)	// イリュージョンドーピング
				hit -= 50;
			if(sc->data[SC_HEAT_BARREL].timer != -1 && bl->type != BL_PC)  // ヒートバレル
				hit -= sc->data[SC_HEAT_BARREL].val4;
			if(sc->data[SC_VOLCANIC_ASH].timer != -1 && sc->data[SC_VOLCANIC_ASH].val2 > 0) 	// 火山灰
				hit -= hit * sc->data[SC_VOLCANIC_ASH].val2 / 100;
			if(sc->data[SC_HANDICAPSTATE_MISFORTUNE].timer != -1 && bl->type != BL_PC)	// 不幸
				hit = 0;
		}
	}
	if(hit < 1) hit = 1;

	return hit;
}

/*==========================================
 * 対象の完全回避を返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_flee2(struct block_list *bl)
{
	int flee2 = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		flee2 = status_get_luk(bl) + 10;
		flee2 += ((struct map_session_data *)bl)->flee2 - (((struct map_session_data *)bl)->paramc[5] + 10);
	} else {
		flee2 = status_get_luk(bl)+1;
	}

	if(sc) {
		if(sc->data[SC__UNLUCKY].timer != -1 && bl->type != BL_PC)	// マスカレード：アンラッキー
			flee2 -= sc->data[SC__UNLUCKY].val1 * 10;
		if(sc->data[SC_HANDICAPSTATE_DEEPBLIND].timer != -1 && bl->type != BL_PC)	// 漆黒
			flee2 = 0;
	}

	if(flee2 < 1) flee2 = 1;
	return flee2;
}

/*==========================================
 * 対象のクリティカルを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_critical(struct block_list *bl)
{
	int critical = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
#ifdef PRE_RENEWAL
		critical = status_get_luk(bl)*3 + 10;
		critical += ((struct map_session_data *)bl)->critical - ((((struct map_session_data *)bl)->paramc[5]*3) + 10);
#else
		critical = status_get_luk(bl)*33/10 + 10;
		critical += ((struct map_session_data *)bl)->critical - ((((struct map_session_data *)bl)->paramc[5]*33/10) + 10);
#endif
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		critical = ((struct homun_data *)bl)->critical;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		critical = ((struct merc_data *)bl)->critical;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		critical = ((struct elem_data *)bl)->critical;
	} else {
		critical = status_get_luk(bl)*3 + 1;
	}

	if(sc) {
		if(sc->data[SC_FORTUNE].timer != -1 && bl->type != BL_PC)
			critical += (10+sc->data[SC_FORTUNE].val1+sc->data[SC_FORTUNE].val2+sc->data[SC_FORTUNE].val3)*10;
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)
			critical += sc->data[SC_EXPLOSIONSPIRITS].val2;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			critical += 10*sc->data[SC_TRUESIGHT].val1;
		if(sc->data[SC__INVISIBILITY].timer != -1 && bl->type != BL_PC)	// インビジビリティ
			critical += critical * (sc->data[SC__INVISIBILITY].val1 * 20) / 100;
		if(sc->data[SC__UNLUCKY].timer != -1 && bl->type != BL_PC)	// マスカレード：アンラッキー
			critical -= critical * (sc->data[SC__UNLUCKY].val1 * 10) / 100;
		if(sc->data[SC_STRIKING].timer != -1 && bl->type != BL_PC)	// ストライキング
			critical += 10 * sc->data[SC_STRIKING].val1;
#ifndef PRE_RENEWAL
		if(sc->data[SC_SPEARQUICKEN].timer != -1 && bl->type != BL_PC)   // スピアクイッケン
			critical += 30*sc->data[SC_SPEARQUICKEN].val1;
#endif
		if(sc->data[SC_HANDICAPSTATE_LASSITUDE].timer != -1 && bl->type != BL_PC)	// 無気力
			critical = 0;
	}
	if(critical < 1) critical = 1;
	return critical;
}

/*==========================================
 * base_atkの取得
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_baseatk(struct block_list *bl)
{
	struct status_change *sc;
	int batk = 1;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			batk = sd->base_atk;	// 設定されているbase_atk
#ifdef PRE_RENEWAL
			if(sd->status.weapon < WT_MAX) {
				batk += sd->weapon_atk[sd->status.weapon];
			}
#endif
		}
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
#ifdef PRE_RENEWAL
		batk = 1;
#else
		batk = status_get_str(bl) + status_get_lv(bl) * 2;
#endif
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		batk = 1;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		batk = 1;
	} else {	// それ以外なら
#ifdef PRE_RENEWAL
		int str, dstr;
		str  = status_get_str(bl);	// STR
		dstr = str/10;
		batk = dstr*dstr + str;	// base_atkを計算する
#else
		batk = status_get_str(bl) + status_get_lv(bl);	// base_atkを計算する
#endif
	}
	if(sc) {	// 状態異常あり
#ifdef PRE_RENEWAL
		if(sc->data[SC__BLOODYLUST].timer != -1 && bl->type != BL_PC)	// ブラッディラスト
			batk = batk*(100+32)/100;	// base_atk増加
		else if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)	// PCでプロボック(SM_PROVOKE)状態
			batk = batk*(100+2+3*sc->data[SC_PROVOKE].val1)/100;	// base_atk増加
		if(sc->data[SC_CURSE].timer != -1)	// 呪われていたら
			batk -= batk*25/100;	// base_atkが25%減少
		if(sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)	// コンセントレーション
			batk += batk*(5*sc->data[SC_CONCENTRATION].val1)/100;
#endif
		if(sc->data[SC_JOINTBEAT].timer != -1 && sc->data[SC_JOINTBEAT].val4 == 4)	// ジョイントビートで腰
			batk -= batk*25/100;
		if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
			batk += 100;
		if(sc->data[SC_THE_MAGICIAN].timer != -1)
			batk = batk*50/100;
		if(sc->data[SC_THE_DEVIL].timer != -1)
			batk = batk*50/100;
		if(sc->data[SC_THE_SUN].timer != -1)
			batk = batk*80/100;
		if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)	// エスク
			batk *= 4;
		if(sc->data[SC__ENERVATION].timer != -1 && bl->type == BL_MOB)	// マスカレード：エナベーション
			batk -= batk * (20 + sc->data[SC__ENERVATION].val1 * 10) / 100;
		if(sc->data[SC_SHIELDSPELL_DEF].timer != -1 && sc->data[SC_SHIELDSPELL_DEF].val2 == 2 && bl->type == BL_MOB)	// シールドスペル(DEF)
			batk += sc->data[SC_SHIELDSPELL_DEF].val3;
		if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1 && bl->type == BL_MOB)	// フライデーナイトフィーバー
			batk += 100 * sc->data[SC_SATURDAY_NIGHT_FEVER].val1;
		if(sc->data[SC_ODINS_POWER].timer != -1 && bl->type == BL_MOB)	// オーディンの力
			batk += 60 + 10 * sc->data[SC_ODINS_POWER].val1;
		if(sc->data[SC_CHATTERING].timer != -1 && bl->type == BL_MOB)	// チャタリング
			batk += sc->data[SC_CHATTERING].val2;
	}
	if(batk < 1) batk = 1;	// base_atkは最低でも1
	return batk;
}

/*==========================================
 * 対象のAtkを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk(struct block_list *bl)
{
	struct status_change *sc;
	int atk = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		atk = ((struct map_session_data*)bl)->watk;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		atk = ((struct homun_data *)bl)->atk-((struct homun_data *)bl)->atk/10;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		atk = ((struct merc_data *)bl)->atk1;
	} else if(bl->type == BL_ELEM && ((struct elem_data *)bl)) {
		atk = ((struct elem_data *)bl)->atk1;
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		if(md) {
			int guardup_lv = md->guardup_lv;
#ifndef PRE_RENEWAL
			if(battle_config.monster_atk2_to_matk)
				atk = md->st.atk * 8 / 10;
			else
#endif
				atk = md->st.atk;
			if(guardup_lv > 0)
				atk += 1000*guardup_lv;
		}
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		atk = mobdb_search(((struct pet_data*)bl)->class_)->atk1;
	}

	if(sc) {
		int rate = 100;
#ifdef PRE_RENEWAL
		if(sc->data[SC__BLOODYLUST].timer != -1 && bl->type != BL_PC)
			atk = atk*(100+32)/100;
		else if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
			atk = atk*(100+2+3*sc->data[SC_PROVOKE].val1)/100;
		if(sc->data[SC_CURSE].timer != -1)
			atk -= atk*25/100;
		if(sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)	// コンセントレーション
			atk += atk*(5*sc->data[SC_CONCENTRATION].val1)/100;
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)	// NPC爆裂波動
			rate += 200;
		if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)		// エスク
			rate += 300;
#endif
		if(sc->data[SC_STRIPWEAPON].timer != -1 && bl->type != BL_PC)
			atk -= atk*25/100;
		if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
			atk += 100;
		if(sc->data[SC_THE_MAGICIAN].timer != -1 && bl->type != BL_PC)
			atk = atk*50/100;
		if(sc->data[SC_THE_DEVIL].timer != -1 && bl->type != BL_PC)
			atk = atk*50/100;
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
			atk = atk*80/100;
		if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)		// エスク
			rate += 300;
		if(sc->data[SC__ENERVATION].timer != -1 && bl->type == BL_MOB)	// マスカレード：エナベーション
			atk -= atk * (20 + sc->data[SC__ENERVATION].val1 * 10) / 100;
		if(sc->data[SC_SHIELDSPELL_DEF].timer != -1 && sc->data[SC_SHIELDSPELL_DEF].val2 == 2 && bl->type == BL_MOB)	// シールドスペル(DEF)
			atk += sc->data[SC_SHIELDSPELL_DEF].val3;
		if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1 && bl->type == BL_MOB)	// フライデーナイトフィーバー
			atk += 100 * sc->data[SC_SATURDAY_NIGHT_FEVER].val1;
		if(sc->data[SC_ODINS_POWER].timer != -1 && bl->type == BL_MOB)	// オーディンの力
			atk += 60 + 10 * sc->data[SC_ODINS_POWER].val1;
		if(sc->data[SC_CATNIPPOWDER].timer != -1 && bl->type != BL_PC)		// イヌハッカシャワー
			atk -= atk * sc->data[SC_CATNIPPOWDER].val2 / 100;
		if(sc->data[SC_SHRIMP].timer != -1)		// エビ三昧
			atk += atk * sc->data[SC_SHRIMP].val3 / 100;
		if(sc->data[SC_EQC].timer != -1 && bl->type == BL_MOB)		// E.Q.C
			atk -= atk * sc->data[SC_EQC].val4 / 100;
		if(sc->data[SC_VOLCANIC_ASH].timer != -1 && sc->data[SC_VOLCANIC_ASH].val4 > 0) 	// 火山灰
			atk -= atk * sc->data[SC_VOLCANIC_ASH].val4 / 100;
		if(rate != 100)	// NPC爆裂波動とエスクを倍率加算させる
			atk = atk * rate / 100;
	}
	if(atk < 0) atk = 0;
	return atk;
}

/*==========================================
 * 対象の左手Atkを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk_(struct block_list *bl)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (sd = (struct map_session_data *)bl)) {
		int atk = sd->watk_;

#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_CURSE].timer != -1)
			atk -= atk*25/100;
#endif
		if(sd->sc.data[SC_SHRIMP].timer != -1)		// エビ三昧
			atk += atk * sd->sc.data[SC_SHRIMP].val3 / 100;
		return atk;
	}
	return 0;
}

/*==========================================
 * 対象のAtk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk2(struct block_list *bl)
{
	int atk2 = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		atk2 = ((struct map_session_data*)bl)->watk2;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		atk2 = ((struct homun_data *)bl)->atk;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		atk2 = ((struct merc_data *)bl)->atk2;
	} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		atk2 = ((struct elem_data *)bl)->atk2;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB) {
			struct mob_data *md = (struct mob_data *)bl;
			if(md) {
				int guardup_lv = md->guardup_lv;
#ifndef PRE_RENEWAL
				if(battle_config.monster_atk2_to_matk)
					atk2 = md->st.atk * 12 / 10;
				else
#endif
					atk2 = md->st.matk;
				if(guardup_lv > 0)
					atk2 += 1000*guardup_lv;
			}
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			atk2 = mobdb_search(((struct pet_data*)bl)->class_)->atk2;
		}
		if(sc) {
			int rate = 100;
#ifdef PRE_RENEWAL
			if(sc->data[SC_IMPOSITIO].timer != -1)
				atk2 += sc->data[SC_IMPOSITIO].val1*5;
			if(sc->data[SC__BLOODYLUST].timer != -1)
				atk2 = atk2*(100+32)/100;
			else if(sc->data[SC_PROVOKE].timer != -1)
				atk2 = atk2*(100+2+3*sc->data[SC_PROVOKE].val1)/100;
			if(sc->data[SC_CURSE].timer != -1)
				atk2 -= atk2*25/100;
			if(sc->data[SC_DRUMBATTLE].timer != -1)
				atk2 += sc->data[SC_DRUMBATTLE].val2;
			if(sc->data[SC_NIBELUNGEN].timer != -1 && (status_get_element(bl)/10) >= 8 )
				atk2 += sc->data[SC_NIBELUNGEN].val2;
#endif
			if(sc->data[SC_STRIPWEAPON].timer != -1)
				atk2 -= atk2*25/100;
#ifdef PRE_RENEWAL
			if(sc->data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
				atk2 += atk2*(5*sc->data[SC_CONCENTRATION].val1)/100;
			if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)	// NPC爆裂波動
				rate += 200;
			if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)		// エスク
				rate += 300;
#endif
			if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
				atk2 += 100;
			if(sc->data[SC_THE_MAGICIAN].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*50/100;
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*80/100;
			if(sc->data[SC__ENERVATION].timer != -1 && bl->type == BL_MOB)	// マスカレード：エナベーション
				atk2 -= atk2 * (20 + sc->data[SC__ENERVATION].val1 * 10) / 100;
			if(sc->data[SC_SHIELDSPELL_DEF].timer != -1 && sc->data[SC_SHIELDSPELL_DEF].val2 == 2 && bl->type == BL_MOB)	// シールドスペル(DEF)
				atk2 += sc->data[SC_SHIELDSPELL_DEF].val3;
			if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1 && bl->type == BL_MOB)	// フライデーナイトフィーバー
				atk2 += 100 * sc->data[SC_SATURDAY_NIGHT_FEVER].val1;
			if(sc->data[SC_ODINS_POWER].timer != -1 && bl->type == BL_MOB)	// オーディンの力
				atk2 += 60 + 10 * sc->data[SC_ODINS_POWER].val1;
			if(sc->data[SC_CATNIPPOWDER].timer != -1 && bl->type != BL_PC)		// イヌハッカシャワー
				atk2 -= atk2 * sc->data[SC_CATNIPPOWDER].val2 / 100;
			if(rate != 100)	// NPC爆裂波動とエスクを倍率加算させる
				atk2 = atk2 * rate / 100;
		}
		if(atk2 < 0) atk2 = 0;
	}
	return atk2;
}

/*==========================================
 * 対象の左手Atk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk_2(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data*)bl)->watk_2;

	return 0;
}

/*==========================================
 * 対象のMAtk1を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_matk1(struct block_list *bl)
{
	int matk1 = 0;

	nullpo_retr(0, bl);

	if (bl->type == BL_PC) {
		matk1 = ((struct map_session_data *)bl)->matk1;
	} else if (bl->type == BL_HOM) {
#ifdef PRE_RENEWAL
		matk1 = ((struct homun_data *)bl)->matk-((struct homun_data *)bl)->matk/10;
#else
		matk1 = ((struct homun_data *)bl)->matk;
#endif
	} else if (bl->type == BL_MERC) {
		matk1 = ((struct merc_data *)bl)->matk1;
	} else if (bl->type == BL_ELEM) {
		matk1 = ((struct elem_data *)bl)->matk1;
	} else if (!(bl->type & (BL_PET | BL_MOB))) {
		matk1 = 0;
	} else {
		struct status_change *sc = status_get_sc(bl);
		int int_ = status_get_int(bl);

#ifndef PRE_RENEWAL
		if(battle_config.monster_atk2_to_matk && bl->type == BL_MOB)
			matk1 = ((struct mob_data *)bl)->st.matk * 13 / 10 + int_ + status_get_lv(bl);
		else
#endif
			matk1 = int_+(int_/5)*(int_/5);

		// MOBのmax_sp値をMATK補正値で乗っ取る時
		if(battle_config.mob_take_over_sp == 1) {
			if(bl->type == BL_MOB) {
				int b_class = status_get_class(bl);		// 直接maxsp取得無理の為ムリヤリ
				if(mobdb_search(b_class)->max_sp > 0) {		// 1以上の時のみ
					matk1 = matk1 * (mobdb_search(b_class)->max_sp/100);
				}
			}
		}

		if(sc) {
#ifdef PRE_RENEWAL
			if(sc->data[SC_MINDBREAKER].timer != -1)
				matk1 += (matk1*20*sc->data[SC_MINDBREAKER].val1)/100;
#endif
			if(sc->data[SC_STRENGTH].timer != -1)
				matk1 = matk1*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1)
				matk1 = matk1*50/100;
			if(sc->data[SC_THE_SUN].timer != -1)
				matk1 = matk1*80/100;
			if(sc->data[SC_ODINS_POWER].timer != -1)	// オーディンの力
				matk1 += 60 + 10 * sc->data[SC_ODINS_POWER].val1;
#ifdef PRE_RENEWAL
			if(sc->data[SC_CHATTERING].timer != -1)	// チャタリング
				matk1 += sc->data[SC_CHATTERING].val2;
#endif
			if(sc->data[SC_SHRIMP].timer != -1)		// エビ三昧
				matk1 += matk1 * sc->data[SC_SHRIMP].val3 / 100;
			if(sc->data[SC_CATNIPPOWDER].timer != -1)		// イヌハッカシャワー
				matk1 -= matk1 * sc->data[SC_CATNIPPOWDER].val2 / 100;
		}
	}
	return matk1;
}

/*==========================================
 * 対象のMAtk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_matk2(struct block_list *bl)
{
	int matk2 = 0;

	nullpo_retr(0, bl);

	if (bl->type == BL_PC) {
		matk2 = ((struct map_session_data *)bl)->matk2;
	} else if (bl->type == BL_HOM) {
#ifdef PRE_RENEWAL
		matk2 = ((struct homun_data *)bl)->matk;
#else
		matk2 = ((struct homun_data *)bl)->matk-((struct homun_data *)bl)->matk/10;
#endif
	} else if (bl->type == BL_MERC) {
		matk2 = ((struct merc_data *)bl)->matk2;
	} else if (bl->type == BL_ELEM) {
		matk2 = ((struct elem_data *)bl)->matk2;
	} else if (!(bl->type & (BL_PET | BL_MOB))) {
		matk2 = 0;
	} else {
		struct status_change *sc = status_get_sc(bl);
		int int_ = status_get_int(bl);

#ifndef PRE_RENEWAL
		if(battle_config.monster_atk2_to_matk && bl->type == BL_MOB)
			matk2 = ((struct mob_data *)bl)->st.matk * 7 / 10 + int_ + status_get_lv(bl);
		else
#endif
			matk2 = int_+(int_/7)*(int_/7);

		// MOBのmax_sp値をMATK補正値で乗っ取る時
		if(battle_config.mob_take_over_sp == 1) {
			if(bl->type == BL_MOB) {
				int b_class = status_get_class(bl);		// 直接maxsp取得無理の為ムリヤリ
				if(mobdb_search(b_class)->max_sp > 0) {		// 1以上の時のみ
					matk2 = matk2 * (mobdb_search(b_class)->max_sp/100);
				}
			}
		}

		if(sc) {
#ifdef PRE_RENEWAL
			if(sc->data[SC_MINDBREAKER].timer != -1)
				matk2 += (matk2*20*sc->data[SC_MINDBREAKER].val1)/100;
#endif
			if(sc->data[SC_STRENGTH].timer != -1)
				matk2 = matk2*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1)
				matk2 = matk2*50/100;
			if(sc->data[SC_THE_SUN].timer != -1)
				matk2 = matk2*80/100;
			if(sc->data[SC_ODINS_POWER].timer != -1)	// オーディンの力
				matk2 += 60 + 10 * sc->data[SC_ODINS_POWER].val1;
			if(sc->data[SC_CHATTERING].timer != -1)	// チャタリング
				matk2 += sc->data[SC_CHATTERING].val2;
			if(sc->data[SC_CATNIPPOWDER].timer != -1)		// イヌハッカシャワー
				matk2 -= matk2 * sc->data[SC_CATNIPPOWDER].val2 / 100;
		}
	}
	return matk2;
}

/*==========================================
 * 対象のDefを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_def(struct block_list *bl)
{
	struct unit_data *ud= NULL;
	struct status_change *sc;
	int def;

	nullpo_retr(0, bl);

	ud = unit_bl2ud(bl);
	sc = status_get_sc(bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		def = ((struct map_session_data *)bl)->def;
	} else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		def = ((struct mob_data *)bl)->st.def;
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		def = mobdb_search(((struct pet_data *)bl)->class_)->def;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		def = ((struct merc_data *)bl)->def;
	} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		def = ((struct elem_data *)bl)->def;
	} else {
		def = 0;
	}

	if(def < 1000000) {
		if(sc) {
			// キーピング時はDEF100
			if(sc->data[SC_KEEPING].timer != -1)
				def *= 2;
			// プロボック時は減算
			if(sc->data[SC__BLOODYLUST].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 55) / 100;
			else if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 5 - 5 * sc->data[SC_PROVOKE].val1) / 100;
			// 戦太鼓の響き時は加算
			if(sc->data[SC_DRUMBATTLE].timer != -1 && bl->type != BL_PC)
				def += sc->data[SC_DRUMBATTLE].val3;
			// 毒にかかっている時は減算
			if(sc->data[SC_POISON].timer != -1 && bl->type != BL_PC)
				def = def*75/100;
			// ストリップシールド時は減算
			if(sc->data[SC_STRIPSHIELD].timer != -1 && bl->type != BL_PC)
				def = def*85/100;
			// シグナムクルシス時は減算
			if(sc->data[SC_SIGNUMCRUCIS].timer != -1 && bl->type != BL_PC)
				def = def * (100 - sc->data[SC_SIGNUMCRUCIS].val2)/100;
			// 永遠の混沌時はPC以外DEFが0になる
			if(sc->data[SC_ETERNALCHAOS].timer != -1 && bl->type != BL_PC)
				def = 0;
			// 凍結、石化時は右シフト
			if(sc->data[SC_FREEZE].timer != -1 || (sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0))
				def >>= 1;
			// コンセントレーション時は減算
			if( sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 5*sc->data[SC_CONCENTRATION].val1) / 100;
			// NPCディフェンダー
			if(sc->data[SC_NPC_DEFENDER].timer != -1 && bl->type != BL_PC)
				def += 100;
			// THE SUN
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				def = def*80/100;
			// フライング
			if(sc->data[SC_FLING].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 5*sc->data[SC_FLING].val2)/100;
			// エスク
			if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)
				def = def/2;
#ifdef PRE_RENEWAL
			// ストーンスキン
			if(sc->data[SC_STONESKIN].timer != -1 && bl->type != BL_PC)
				def = def * (100 + 20 * sc->data[SC_STONESKIN].val1) / 100;
			// アンチマジック
			if(sc->data[SC_ANTIMAGIC].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
#endif
			// フロストミスティ
			if(sc->data[SC_FROSTMISTY].timer != -1 && bl->type != BL_PC)
				def = def * 90 / 100;
			// アナライズ
			if(sc->data[SC_ANALYZE].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 14 * sc->data[SC_ANALYZE].val1) / 100;
			// ニュートラルバリアー
			if(sc->data[SC_NEUTRALBARRIER].timer != -1 && bl->type != BL_PC)
				def = def * (110 + 5 * sc->data[SC_NEUTRALBARRIER].val1) / 100;
			// アースドライブ
			if(sc->data[SC_EARTHDRIVE].timer != -1 && bl->type != BL_PC)
				def = def * 85 / 100;
			// フライデーナイトフィーバー
			if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1 && bl->type != BL_PC)
				def = def * (90 - 10 * sc->data[SC_SATURDAY_NIGHT_FEVER].val1) / 100;
			// オーディンの力
			if(sc->data[SC_ODINS_POWER].timer != -1 && bl->type != BL_PC)
				def -= 10 + 10 * sc->data[SC_ODINS_POWER].val1;
			// ニャングラス
			if(sc->data[SC_NYANGGRASS].timer != -1 && bl->type != BL_PC)
				def >>= 1;
			// 火山灰
			if(sc->data[SC_VOLCANIC_ASH].timer != -1 && sc->data[SC_VOLCANIC_ASH].val3 > 0)
				def -= def * sc->data[SC_VOLCANIC_ASH].val3 / 100;
			// 急冷
			if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 && bl->type != BL_PC)
				def -= def * sc->data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
			// アンリミット
			if(sc->data[SC_UNLIMIT].timer != -1)
				def = 1;
			// 強毒
			if(sc->data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1 && bl->type != BL_PC)
				def = 0;
		}
		// 詠唱中は詠唱時減算率に基づいて減算
		if(ud && ud->skilltimer != -1) {
			int def_rate = skill_get_castdef(ud->skillid);
			if(def_rate != 0)
				def = (def * (100 - def_rate))/100;
		}
	}
	if(def < 0) def = 0;
	return def;
}

/*==========================================
 * 対象のMDefを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_mdef(struct block_list *bl)
{
	struct status_change *sc;
	int mdef = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		mdef = ((struct map_session_data *)bl)->mdef;
	else if(bl->type == BL_MOB && (struct mob_data *)bl)
		mdef = ((struct mob_data *)bl)->st.mdef;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		mdef = ((struct homun_data *)bl)->mdef;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		mdef = ((struct merc_data *)bl)->mdef;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		mdef = ((struct elem_data *)bl)->mdef;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		mdef = mobdb_search(((struct pet_data *)bl)->class_)->mdef;

	if(mdef < 1000000) {
		if(sc) {
			// バリアー状態時はMDEF100
			if(sc->data[SC_BARRIER].timer != -1)
				mdef += 100;
			// 凍結、石化時は1.25倍
			if(sc->data[SC_FREEZE].timer != -1 || (sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0))
				mdef = mdef*125/100;
#ifdef PRE_RENEWAL
			// ストーンスキン
			if(sc->data[SC_STONESKIN].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (100 - 20 * sc->data[SC_STONESKIN].val1) / 100;
			// アンチマジック
			if(sc->data[SC_ANTIMAGIC].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (100 + 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
#endif
			// アナライズ
			if(sc->data[SC_ANALYZE].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (100 - 14 * sc->data[SC_ANALYZE].val1) / 100;
			// ニュートラルバリアー
			if(sc->data[SC_NEUTRALBARRIER].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (110 + 5 * sc->data[SC_NEUTRALBARRIER].val1) / 100;
			// オーディンの力
			if(sc->data[SC_ODINS_POWER].timer != -1 && bl->type != BL_PC)
				mdef -= 10 + 10 * sc->data[SC_ODINS_POWER].val1;
			// 点穴 -反-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1)
				mdef -= sc->data[SC_GENTLETOUCH_CHANGE].val3;
			// ニャングラス
			if(sc->data[SC_NYANGGRASS].timer != -1 && bl->type != BL_PC)
				mdef >>= 1;
			// 急冷
			if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 && bl->type != BL_PC)
				mdef -= mdef * sc->data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
			// アンリミット
			if(sc->data[SC_UNLIMIT].timer != -1)
				mdef = 1;
			// 結晶化
			if(sc->data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1 && bl->type != BL_PC)
				mdef = 0;
		}
	}
	if(mdef < 0) mdef = 0;
	return mdef;
}

/*==========================================
 * 対象のDef2を返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_def2(struct block_list *bl)
{
	struct status_change *sc;
	int def2 = 1;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		def2 = ((struct map_session_data *)bl)->def2;
	else if(bl->type == BL_MOB && (struct mob_data *)bl)
#ifdef PRE_RENEWAL
		def2 = mobdb_search(((struct mob_data *)bl)->class_)->vit;
#else
		def2 = (int)(mobdb_search(((struct mob_data *)bl)->class_)->vit/(float)2 + mobdb_search(((struct mob_data *)bl)->class_)->lv/(float)2);
#endif
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		def2 = mobdb_search(((struct pet_data *)bl)->class_)->vit;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		def2 = ((struct homun_data *)bl)->def;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		def2 = ((struct merc_data *)bl)->vit;
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		def2 = ((struct elem_data *)bl)->vit;

	if(sc) {
		if(sc->data[SC_ANGELUS].timer != -1 && bl->type != BL_PC) {
#ifdef PRE_RENEWAL
			def2 = def2*(110+5*sc->data[SC_ANGELUS].val1)/100;
#else
			def2 = def2*(100+5*sc->data[SC_ANGELUS].val1)/100;
#endif
		}
		if(sc->data[SC__BLOODYLUST].timer != -1 && bl->type != BL_PC)
			def2 = def2 * (100 - 55) / 100;
		else if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
			def2 = def2 * (100 - 5 - 5 * sc->data[SC_PROVOKE].val1) / 100;
		if(sc->data[SC_POISON].timer != -1 && bl->type != BL_PC)
			def2 = def2*75/100;
		// コンセントレーション時は減算
		if( sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)
			def2 = def2*(100 - 5*sc->data[SC_CONCENTRATION].val1)/100;
		// ジョイントビート時なら減算
		if(sc->data[SC_JOINTBEAT].timer != -1) {
			if(sc->data[SC_JOINTBEAT].val4 == 3)	// 肩
				def2 -= def2*50/100;
			if(sc->data[SC_JOINTBEAT].val4 == 4)	// 腰
				def2 -= def2*25/100;
		}
		// 永遠の混沌時はDEF2が0になる
		if(sc->data[SC_ETERNALCHAOS].timer != -1)
			def2 = 0;
		// THE SUN
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
			def2 = def2*80/100;
		// フライング
		if(sc->data[SC_FLING].timer != -1 && bl->type != BL_PC)
			def2 = def2 * (100 - 5*sc->data[SC_FLING].val2)/100;
		// エスカ
		if(sc->data[SC_SKA].timer != -1 && bl->type == BL_MOB)
			def2 += 90;
		// シールドスペル
		if(sc->data[SC_SHIELDSPELL_REF].timer != -1 && sc->data[SC_SHIELDSPELL_REF].val2 == 2 && bl->type == BL_MOB)
			def2 += sc->data[SC_SHIELDSPELL_REF].val2;
		// プレスティージ
		if(sc->data[SC_PRESTIGE].timer != -1 && bl->type == BL_MOB)
			def2 += sc->data[SC_PRESTIGE].val2;
		// 急冷
		if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 && bl->type != BL_PC)
			def2 -= def2 * sc->data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
		// アンリミット
		if(sc->data[SC_UNLIMIT].timer != -1)
			def2 = 1;
		// E.Q.C
		if(sc->data[SC_EQC].timer != -1 && bl->type == BL_MOB)
			def2 -= def2 * sc->data[SC_EQC].val4 / 100;
		// 強毒
		if(sc->data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1 && bl->type != BL_PC)
			def2 = 0;
	}
	if(def2 < 1) def2 = 1;
	return def2;
}

/*==========================================
 * 対象のMDef2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_mdef2(struct block_list *bl)
{
	struct status_change *sc;
	int mdef2 = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
#ifdef PRE_RENEWAL
		mdef2 = mobdb_search(((struct mob_data *)bl)->class_)->int_ + (mobdb_search(((struct mob_data *)bl)->class_)->vit>>1);
#else
		mdef2 = (int)(mobdb_search(((struct mob_data *)bl)->class_)->int_/(float)4 + mobdb_search(((struct mob_data *)bl)->class_)->lv/(float)4);
#endif
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
#ifdef PRE_RENEWAL
		mdef2 = ((struct map_session_data *)bl)->mdef2 + (((struct map_session_data *)bl)->paramc[2]>>1);
#else
		mdef2 = ((struct map_session_data *)bl)->mdef2;
#endif
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		mdef2 = mobdb_search(((struct pet_data *)bl)->class_)->int_ + (mobdb_search(((struct pet_data *)bl)->class_)->vit>>1);
	else if (bl->type == BL_HOM && (struct homun_data *)bl)
		mdef2 = ((struct homun_data *)bl)->mdef;
	else if (bl->type == BL_MERC && (struct merc_data *)bl)
		mdef2 = ((struct merc_data *)bl)->int_ + (((struct merc_data *)bl)->vit>>1);
	else if (bl->type == BL_ELEM && (struct elem_data *)bl)
		mdef2 = ((struct elem_data *)bl)->int_ + (((struct elem_data *)bl)->vit>>1);

	if(sc) {
		// エスカ
		if(sc->data[SC_SKA].timer != -1 && bl->type == BL_MOB)
			mdef2 = 90;
		// マインドブレイカー
		if(sc->data[SC_MINDBREAKER].timer != -1 && bl->type != BL_PC)
			mdef2 -= (mdef2*12*sc->data[SC_MINDBREAKER].val1)/100;
		// 急冷
		if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 && bl->type != BL_PC)
			mdef2 -= mdef2 * sc->data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
		// アンリミット
		if(sc->data[SC_UNLIMIT].timer != -1)
			mdef2 = 1;
		// 結晶化
		if(sc->data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1 && bl->type != BL_PC)
			mdef2 = 0;
	}
	return mdef2;
}

/*==========================================
 * 対象のSpeed(移動速度)を返す
 * 戻りは整数で1以上
 * Speedは小さいほうが移動速度が速い
 *------------------------------------------
 */
int status_get_speed(struct block_list *bl)
{
	int speed = 1000;

	nullpo_retr(1000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		speed = ((struct map_session_data *)bl)->speed;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		if(battle_config.homun_speed_is_same_as_pc)
			speed = ((struct homun_data *)bl)->msd->speed;
		else
			speed = ((struct homun_data *)bl)->speed;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		if(battle_config.merc_speed_is_same_as_pc)
			speed = ((struct merc_data *)bl)->msd->speed;
		else
			speed = ((struct merc_data *)bl)->speed;
	} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		speed = ((struct elem_data *)bl)->speed;
 	} else if(bl->type == BL_NPC && (struct npc_data *)bl) {
		speed = ((struct npc_data *)bl)->speed;
	} else {
		int bonus_rate;
		int haste_val  = 0;
		int slow_val   = 0;
		char defender_flag = 0;
		char walkspeed_flag = 0;
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl)
			speed = ((struct mob_data *)bl)->speed;
		else if(bl->type == BL_PET && (struct pet_data *)bl)
			speed = ((struct pet_data *)bl)->speed;

		/* speedが変化するステータスの計算 */
		if(sc) {
			/* speedが増加するステータスの計算 */

			// 金剛は移動速度固定
			if(sc->data[SC_STEELBODY].timer != -1)
				return 200;

			// 速度減少
			if(sc->data[SC_DECREASEAGI].timer != -1)
				slow_val = 25;

			// クァグマイア
			if(sc->data[SC_QUAGMIRE].timer != -1) {
				if(slow_val < 50)
					slow_val = 50;
			}

			// 私を忘れないで
			if(sc->data[SC_DONTFORGETME].timer != -1) {
				if(slow_val < sc->data[SC_DONTFORGETME].val2)
					slow_val = sc->data[SC_DONTFORGETME].val2;
			}

			// 呪い
			if(sc->data[SC_CURSE].timer != -1) {
				if(slow_val < 300)
					slow_val = 300;
			}

			// マーシュオブアビス
			if(sc->data[SC_MARSHOFABYSS].timer != -1) {
				if(slow_val < sc->data[SC_MARSHOFABYSS].val2)
					slow_val = sc->data[SC_MARSHOFABYSS].val2;
			}

			// ハルシネーションウォーク(ペナルティ)
			if(sc->data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// ジョイントビート
			if(sc->data[SC_JOINTBEAT].timer != -1) {
				int penalty = 0;
				switch (sc->data[SC_JOINTBEAT].val4) {
				case 0:	// 足首
					penalty = 50;
					break;
				case 2:	// 膝
					penalty = 30;
					break;
				}
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// ガトリングフィーバー
			if(sc->data[SC_GATLINGFEVER].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// エスウ
			if(sc->data[SC_SWOO].timer != -1) {
				if(slow_val < 300)
					slow_val = 300;
			}

			// パラライズ
			if(sc->data[SC_PARALIZE].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// フロストミスティ
			if(sc->data[SC_FROSTMISTY].timer != -1) {
				if(slow_val < 50)
					slow_val = 50;
			}

			// マスカレード：レイジネス
			if(sc->data[SC__LAZINESS].timer != -1) {
				if(slow_val < 10)
					slow_val = 10;
			}

			// マスカレード：グルーミー
			if(sc->data[SC__GROOMY].timer != -1) {
				int penalty = 5 + 5 * sc->data[SC__GROOMY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// メロン爆弾
			if(sc->data[SC_MELON_BOMB].timer != -1) {
				int penalty = sc->data[SC_MELON_BOMB].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// グラビテーションフィールド
			if(battle_config.enemy_gravitation_type && sc->data[SC_GRAVITATION].timer != -1) {
				int penalty = sc->data[SC_GRAVITATION].val1 * 5;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// バインドトラップ
			if(sc->data[SC_B_TRAP].timer != -1) {
				int penalty = sc->data[SC_B_TRAP].val3;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// エスハ
			if(sc->data[SC_SHA].timer != -1) {
				if(slow_val < sc->data[SC_SHA].val2)
					slow_val = sc->data[SC_SHA].val2;
			}

			// シールドチェーンラッシュ
			if(sc->data[SC_SHIELDCHAINRUSH].timer != -1) {
				if(slow_val < sc->data[SC_SHIELDCHAINRUSH].val3)
					slow_val = sc->data[SC_SHIELDCHAINRUSH].val3;
			}

			// グラウンドグラビテーション
			if(sc->data[SC_GROUNDGRAVITY].timer != -1) {
				if(slow_val < sc->data[SC_GROUNDGRAVITY].val3)
					slow_val = sc->data[SC_GROUNDGRAVITY].val3;
			}

			/* speedが減少するステータス計算 */

			// 速度強化
			if(sc->data[SC_SPEEDUP1].timer != -1)
				haste_val = 50;

			// 速度増加
			if(sc->data[SC_INCREASEAGI].timer != -1) {
				if(haste_val < 25)
					haste_val = 25;
			}

			// ウインドウォーク
			if(sc->data[SC_WINDWALK].timer != -1) {
				int bonus = 2 * sc->data[SC_WINDWALK].val1;
				if(haste_val < bonus)
					haste_val = bonus;
			}

			// インビンシブル
			if(sc->data[SC_INVINCIBLE].timer != -1 && sc->data[SC_INVINCIBLEOFF].timer == -1) {
				if(haste_val < 75)
					haste_val = 75;
			}

			/* その他 */

			// ディフェンダー
			if(sc->data[SC_DEFENDER].timer != -1)
				defender_flag = 1;

			// WALKSPEED
			if(sc->data[SC_WALKSPEED].timer != -1 && sc->data[SC_WALKSPEED].val1 > 0)
				walkspeed_flag = 1;
		}

		/* bonus_rateの最低値を設定 */
		bonus_rate = slow_val - haste_val;
		if(bonus_rate < -60)
			bonus_rate = -60;

		/* speedの最終計算 */
		if(bonus_rate != 0)	// bonus_rate
			speed = speed * (bonus_rate+100) / 100;
		if(defender_flag && speed < 200)	// ディフェンダー
			speed = 200;
		if(walkspeed_flag)	// スクリプト用ステータス
			speed = speed * 100 / sc->data[SC_WALKSPEED].val1;

		/* 最低値、最大値を設定する */
		if(speed < MIN_WALK_SPEED)
			speed = MIN_WALK_SPEED;
		if(speed > MAX_WALK_SPEED)
			speed = MAX_WALK_SPEED;
	}

	return speed;
}

/*==========================================
 * 対象のaDelay(攻撃時ディレイ)を返す
 * aDelayは小さいほうが攻撃速度が速い
 *------------------------------------------
 */
int status_get_adelay(struct block_list *bl)
{
	int adelay = 4000;

	nullpo_retr(4000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		adelay = (((struct map_session_data *)bl)->aspd);
	} else {
		double calc_adelay = 0;
		int haste_val1     = 0;
		int haste_val2     = 0;
		int slow_val       = 0;
		int bonus_rate     = 0;
		int ferver_bonus   = 0;
		int tmp            = 0;
		int add_val        = 0;
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			int guardup_lv = ((struct mob_data*)bl)->guardup_lv;
			if(mobdb_search(((struct mob_data *)bl)->class_)->adelay < mobdb_search(((struct mob_data *)bl)->class_)->amotion)
				calc_adelay = mobdb_search(((struct mob_data *)bl)->class_)->amotion;
			else
				calc_adelay = mobdb_search(((struct mob_data *)bl)->class_)->adelay;

			if(guardup_lv > 0)
				bonus_rate -= 5 + 5*guardup_lv;
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			if(mobdb_search(((struct pet_data *)bl)->class_)->adelay < mobdb_search(((struct pet_data *)bl)->class_)->amotion)
				calc_adelay = mobdb_search(((struct pet_data *)bl)->class_)->amotion;
			else
				calc_adelay = mobdb_search(((struct pet_data *)bl)->class_)->adelay;
		} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
			calc_adelay = (((struct homun_data *)bl)->aspd);
		} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
			calc_adelay = ((struct merc_data *)bl)->adelay;
		} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
			calc_adelay = ((struct elem_data *)bl)->adelay;
		}

		/* amotionが変化する状態異常の計算 */
		if(sc) {

			/* amotionが増加するステータスの計算 */

			// 私を忘れないで
			if(sc->data[SC_DONTFORGETME].timer != -1) {
				slow_val = sc->data[SC_DONTFORGETME].val1;
			}

			// 金剛
			if(sc->data[SC_STEELBODY].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// ジョイントビート
			if(sc->data[SC_JOINTBEAT].timer != -1) {
				switch (sc->data[SC_JOINTBEAT].val4) {
					case 1:		// 手首
						if(slow_val < 25)
							slow_val = 25;
						break;
					case 2:		// 膝
						if(slow_val < 10)
							slow_val = 10;
						break;
				}
			}

			// グラビテーションフィールド
			if(sc->data[SC_GRAVITATION].timer != -1) {
				int penalty = sc->data[SC_GRAVITATION].val1*5;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// フロストミスティ
			if(sc->data[SC_FROSTMISTY].timer != -1) {
				if(slow_val < 15)
					slow_val = 15;
			}

			// ボディペインティング
			if(sc->data[SC__BODYPAINT].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// インビジビリティ
			if(sc->data[SC__INVISIBILITY].timer != -1) {
				int penalty = 50 - 10 * sc->data[SC__INVISIBILITY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// マスカレード：グルーミー
			if(sc->data[SC__GROOMY].timer != -1) {
				int penalty = 20 + 10 * sc->data[SC__GROOMY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// アースドライブ
			if(sc->data[SC_EARTHDRIVE].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// メランコリー
			if(sc->data[SC_GLOOMYDAY].timer != -1) {
				int penalty = 15 + 5 * sc->data[SC_GLOOMYDAY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// メロン爆弾
			if(sc->data[SC_MELON_BOMB].timer != -1) {
				int penalty = sc->data[SC_MELON_BOMB].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			/* amotionが減少するステータスの計算1 */

			// 増速ポーション
			if(sc->data[tmp = SC_SPEEDPOTION2].timer != -1 || sc->data[tmp = SC_SPEEDPOTION1].timer != -1 || sc->data[tmp = SC_SPEEDPOTION0].timer != -1)
				haste_val1 = sc->data[tmp].val2;

			/* amotionが減少するステータスの計算2 */

			// ツーハンドクィッケン
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				haste_val2 = sc->data[SC_TWOHANDQUICKEN].val2;

			// スピアクィッケン
			if(sc->data[SC_SPEARQUICKEN].timer != -1) {
				if(haste_val2 < sc->data[SC_SPEARQUICKEN].val2)
					haste_val2 = sc->data[SC_SPEARQUICKEN].val2;
			}

			// ワンハンドクィッケン
			if(sc->data[SC_ONEHAND].timer != -1) {
				if(haste_val2 < 30)
					haste_val2 = 30;
			}

			// アドレナリンラッシュ
			if(sc->data[SC_ADRENALINE].timer != -1) {
				int bonus;
				if(sc->data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
					bonus = 30;
				else
					bonus = 25;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// アドレナリンラッシュ2
			if(sc->data[SC_ADRENALINE2].timer != -1) {
				int bonus;
				if(sc->data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
					bonus = 30;
				else
					bonus = 25;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// 夕陽のアサシンクロス
			if(sc->data[SC_ASSNCROS].timer != -1) {
				int bonus = sc->data[SC_ASSNCROS].val2;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// ガトリングフィーバー
			if(sc->data[SC_GATLINGFEVER].timer != -1) {
				ferver_bonus = sc->data[SC_GATLINGFEVER].val1*2;
				if(haste_val2 < ferver_bonus)
					haste_val2 = ferver_bonus;
			}

			// マッドネスキャンセラー
			if(sc->data[SC_MADNESSCANCEL].timer != -1) {
				int bonus = 20+ferver_bonus;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// 点穴 -反-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				int bonus = sc->data[SC_GENTLETOUCH_CHANGE].val4;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			/* その他 */

			// ディフェンダー
			if(sc->data[SC_DEFENDER].timer != -1)
				add_val += sc->data[SC_DEFENDER].val3;

			// ヒートバレル
			if(sc->data[SC_HEAT_BARREL].timer != -1)
				add_val -= sc->data[SC_HEAT_BARREL].val1 * 10;

			// 静寂
			if(sc->data[SC_HANDICAPSTATE_DEEPSILENCE].timer != -1)
				add_val += sc->data[SC_HANDICAPSTATE_DEEPSILENCE].val2;
		}

		/* slow_valとhaste_val1とhaste_val2を加算する */
		bonus_rate = slow_val - haste_val1 - haste_val2;

		/* bonus_rateの計算 */
		if(bonus_rate != 0)
			calc_adelay = calc_adelay * (bonus_rate+100) / 100;

		/* add_valの加算 */
		if(add_val != 0)
			calc_adelay += add_val;

		/* 小数切り上げ */
		adelay = (int)ceil(calc_adelay);

		/* 最低値の設定 */
		switch(bl->type)
		{
			case BL_MOB:
			case BL_PET:
				if(adelay < (battle_config.monster_max_aspd>>1) )
					adelay = battle_config.monster_max_aspd>>1;
				break;
			case BL_HOM:
#ifdef PRE_RENEWAL
				if(adelay < battle_config.homun_max_aspd)
					adelay = battle_config.homun_max_aspd;
#else
				if(adelay < (battle_config.homun_max_aspd>>1) )
					adelay = battle_config.homun_max_aspd>>1;
#endif
				break;
			case BL_MERC:
				if(adelay < (battle_config.merc_max_aspd>>1) )
					adelay = battle_config.merc_max_aspd>>1;
			case BL_ELEM:
				if(adelay < (battle_config.elem_max_aspd>>1) )
					adelay = battle_config.elem_max_aspd>>1;
				break;
		}
	}

	return adelay;
}

/*==========================================
 * 対象のamotionを返す
 *------------------------------------------
 */
int status_get_amotion(struct block_list *bl)
{
	int amotion = 2000;

	nullpo_retr(2000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		amotion = ((struct map_session_data *)bl)->amotion;
	} else {
		double calc_amotion = 0;
		int haste_val1      = 0;
		int haste_val2      = 0;
		int slow_val        = 0;
		int bonus_rate      = 0;
		int ferver_bonus    = 0;
		int tmp             = 0;
		char defender_flag  = 0;
		char heatbarrel_flag = 0;
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			int guardup_lv = ((struct mob_data*)bl)->guardup_lv;
			calc_amotion = mobdb_search(((struct mob_data *)bl)->class_)->amotion;
			if(guardup_lv > 0)
				bonus_rate -= 5 + 5*guardup_lv;
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			calc_amotion = mobdb_search(((struct pet_data *)bl)->class_)->amotion;
		} else if(bl->type == BL_HOM && (struct homun_data *)bl && ((struct homun_data *)bl)->msd) {
			calc_amotion = ((struct homun_data *)bl)->aspd;
		} else if(bl->type == BL_MERC && (struct merc_data *)bl && ((struct merc_data *)bl)->msd) {
			calc_amotion = ((struct merc_data *)bl)->amotion;
		} else if(bl->type == BL_ELEM && (struct elem_data *)bl && ((struct elem_data *)bl)->msd) {
			calc_amotion = ((struct elem_data *)bl)->amotion;
		}

		/* amotionが変化する状態異常の計算 */
		if(sc) {

			/* amotionが増加するステータスの計算 */

			// 私を忘れないで
			if(sc->data[SC_DONTFORGETME].timer != -1) {
				slow_val = sc->data[SC_DONTFORGETME].val1;
			}

			// 金剛
			if(sc->data[SC_STEELBODY].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// ジョイントビート
			if(sc->data[SC_JOINTBEAT].timer != -1) {
				switch (sc->data[SC_JOINTBEAT].val4) {
					case 1:		// 手首
						if(slow_val < 25)
							slow_val = 25;
						break;
					case 2:		// 膝
						if(slow_val < 10)
							slow_val = 10;
						break;
				}
			}

			// グラビテーションフィールド
			if(sc->data[SC_GRAVITATION].timer != -1) {
				int penalty = sc->data[SC_GRAVITATION].val1*5;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// フロストミスティ
			if(sc->data[SC_FROSTMISTY].timer != -1) {
				if(slow_val < 15)
					slow_val = 15;
			}

			// ボディペインティング
			if(sc->data[SC__BODYPAINT].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// インビジビリティ
			if(sc->data[SC__INVISIBILITY].timer != -1) {
				int penalty = 50 - 10 * sc->data[SC__INVISIBILITY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// マスカレード：グルーミー
			if(sc->data[SC__GROOMY].timer != -1) {
				int penalty = 20 + 10 * sc->data[SC__GROOMY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// アースドライブ
			if(sc->data[SC_EARTHDRIVE].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// メランコリー
			if(sc->data[SC_GLOOMYDAY].timer != -1) {
				int penalty = 15 + 5 * sc->data[SC_GLOOMYDAY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// メロン爆弾
			if(sc->data[SC_MELON_BOMB].timer != -1) {
				int penalty = sc->data[SC_MELON_BOMB].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			/* amotionが減少するステータスの計算1 */

			// 増速ポーション
			if(sc->data[tmp = SC_SPEEDPOTION2].timer != -1 || sc->data[tmp = SC_SPEEDPOTION1].timer != -1 || sc->data[tmp = SC_SPEEDPOTION0].timer != -1)
				haste_val1 = sc->data[tmp].val2;

			/* amotionが減少するステータスの計算2 */

			// ツーハンドクィッケン
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				haste_val2 = sc->data[SC_TWOHANDQUICKEN].val2;

			// スピアクィッケン
			if(sc->data[SC_SPEARQUICKEN].timer != -1) {
				if(haste_val2 < sc->data[SC_SPEARQUICKEN].val2)
					haste_val2 = sc->data[SC_SPEARQUICKEN].val2;
			}

			// ワンハンドクィッケン
			if(sc->data[SC_ONEHAND].timer != -1) {
				if(haste_val2 < 30)
					haste_val2 = 30;
			}

			// アドレナリンラッシュ
			if(sc->data[SC_ADRENALINE].timer != -1) {
				int bonus;
				if(sc->data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
					bonus = 30;
				else
					bonus = 25;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// アドレナリンラッシュ2
			if(sc->data[SC_ADRENALINE2].timer != -1) {
				int bonus;
				if(sc->data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
					bonus = 30;
				else
					bonus = 25;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// 夕陽のアサシンクロス
			if(sc->data[SC_ASSNCROS].timer != -1) {
				int bonus = sc->data[SC_ASSNCROS].val2;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// ガトリングフィーバー
			if(sc->data[SC_GATLINGFEVER].timer != -1) {
				ferver_bonus = sc->data[SC_GATLINGFEVER].val1*2;
				if(haste_val2 < ferver_bonus)
					haste_val2 = ferver_bonus;
			}

			// マッドネスキャンセラー
			if(sc->data[SC_MADNESSCANCEL].timer != -1) {
				int bonus = 20+ferver_bonus;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			// 点穴 -反-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				int bonus = sc->data[SC_GENTLETOUCH_CHANGE].val4;
				if(haste_val2 < bonus)
					haste_val2 = bonus;
			}

			/* その他 */

			// ディフェンダー
			if(sc->data[SC_DEFENDER].timer != -1)
				defender_flag = 1;

			// ヒートバレル
			if(sc->data[SC_HEAT_BARREL].timer != -1)
				heatbarrel_flag = 1;
		}

		/* slow_valとhaste_val1とhaste_val2を加算する */
		bonus_rate = slow_val - haste_val1 - haste_val2;

		/* bonus_rateの計算 */
		if(bonus_rate != 0)
			calc_amotion = calc_amotion * (bonus_rate+100) / 100;

		/* ディフェンダー */
		if(defender_flag)
			calc_amotion += sc->data[SC_DEFENDER].val3;

		/* ヒートバレル */
		if(heatbarrel_flag)
			calc_amotion -= sc->data[SC_HEAT_BARREL].val1 * 10;

		/* 小数切り上げ */
		amotion = (int)ceil(calc_amotion);

		/* 最低値の設定 */
		switch(bl->type)
		{
			case BL_MOB:
			case BL_PET:
				if(amotion < battle_config.monster_max_aspd)
					amotion = battle_config.monster_max_aspd;
				break;
			case BL_HOM:
				if(amotion < battle_config.homun_max_aspd)
					amotion = battle_config.homun_max_aspd;
				break;
			case BL_MERC:
				if(amotion < battle_config.merc_max_aspd)
					amotion = battle_config.merc_max_aspd;
				break;
			case BL_ELEM:
				if(amotion < battle_config.elem_max_aspd)
					amotion = battle_config.elem_max_aspd;
				break;
		}
	}

	return amotion;
}

/*==========================================
 * 対象のdmotionを返す
 *------------------------------------------
 */
int status_get_dmotion(struct block_list *bl)
{
	int dmotion = 2000;

	nullpo_retr(2000, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		dmotion = mobdb_search(((struct mob_data *)bl)->class_)->dmotion;
		if(battle_config.monster_damage_delay_rate != 100)
			dmotion = dmotion*battle_config.monster_damage_delay_rate/100;
	}
	else if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			if((sd->sc.data[SC_ENDURE].timer != -1 || sd->special_state.infinite_endure) && !map[sd->bl.m].flag.gvg) {
				dmotion = 0;
			} else {
				dmotion = sd->dmotion;
				if(battle_config.pc_damage_delay_rate != 100)
					dmotion = dmotion*battle_config.pc_damage_delay_rate/100;
			}
		}
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl && ((struct homun_data *)bl)->msd) {
		dmotion = 800 - ((struct homun_data *)bl)->status.agi*4;
		if(dmotion < 400)
			dmotion = 400;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl && ((struct merc_data *)bl)->msd) {
		dmotion = ((struct merc_data *)bl)->dmotion;
	}
	else if(bl->type == BL_ELEM && (struct elem_data *)bl && ((struct elem_data *)bl)->msd) {
		dmotion = ((struct elem_data *)bl)->dmotion;
	}
	else if(bl->type == BL_PET && (struct pet_data *)bl) {
		dmotion = mobdb_search(((struct pet_data *)bl)->class_)->dmotion;
	}

	return dmotion;
}

/*==========================================
 * 対象のP.Atkを返す
 *------------------------------------------
 */
int status_get_patk(struct block_list *bl)
{
	int patk = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		patk = ((struct map_session_data *)bl)->patk;

	if(patk < 0) patk = 0;
	return patk;
}

/*==========================================
 * 対象のS.Matkを返す
 *------------------------------------------
 */
int status_get_smatk(struct block_list *bl)
{
	int smatk = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		smatk = ((struct map_session_data *)bl)->smatk;

	if(smatk < 0) smatk = 0;
	return smatk;
}

/*==========================================
 * 対象のResを返す
 *------------------------------------------
 */
int status_get_res(struct block_list *bl)
{
	int res = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		res = ((struct map_session_data *)bl)->res;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			res = ((struct mob_data *)bl)->st.res;
		}
		if(sc) {
			if(sc->data[SC_SHADOW_STRIP].timer != -1) 	// ストリップシャドウ
				res -= sc->data[SC_SHADOW_STRIP].val2;
			if(sc->data[SC_AIN_RHAPSODY].timer != -1) 	// 鉱員のラプソディ
				res -= sc->data[SC_AIN_RHAPSODY].val3;
		}
	}

	if(res < 0) res = 0;
	return res;
}

/*==========================================
 * 対象のMresを返す
 *------------------------------------------
 */
int status_get_mres(struct block_list *bl)
{
	int mres = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		mres = ((struct map_session_data *)bl)->mres;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			mres = ((struct mob_data *)bl)->st.mres;
		}
		if(sc) {
			if(sc->data[SC_SHADOW_STRIP].timer != -1) 	// ストリップシャドウ
				mres -= sc->data[SC_SHADOW_STRIP].val2;
			if(sc->data[SC_GEF_NOCTURN].timer != -1) 	// ゲフェニアノクターン
				mres -= sc->data[SC_GEF_NOCTURN].val3;
		}
	}

	if(mres < 0) mres = 0;
	return mres;
}

/*==========================================
 * 対象のH.Plusを返す
 *------------------------------------------
 */
int status_get_hplus(struct block_list *bl)
{
	int hplus = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		hplus = ((struct map_session_data *)bl)->hplus;

	if(hplus < 0) hplus = 0;
	return hplus;
}

/*==========================================
 * 対象のC.Rateを返す
 *------------------------------------------
 */
int status_get_crate(struct block_list *bl)
{
	int crate = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		crate = ((struct map_session_data *)bl)->crate;

	if(crate < 0) crate = 0;
	return crate;
}

/*==========================================
 * 対象の属性を返す
 *------------------------------------------
 */
int status_get_element(struct block_list *bl)
{
	int ret = 20;
	struct status_change *sc;

	nullpo_retr(ret, bl);

	sc = status_get_sc(bl);
	if(sc) {
		if(sc->data[SC_BENEDICTIO].timer != -1)		// 聖体降福
			ret = 20 + ELE_HOLY;
		if(sc->data[SC_ELEMENTWATER].timer != -1)	// 水
			ret = 20*sc->data[SC_ELEMENTWATER].val1 + ELE_WATER;
		if(sc->data[SC_ELEMENTGROUND].timer != -1)	// 土
			ret = 20*sc->data[SC_ELEMENTGROUND].val1 + ELE_EARTH;
		if(sc->data[SC_ELEMENTFIRE].timer != -1)		// 火
			ret = 20*sc->data[SC_ELEMENTFIRE].val1 + ELE_FIRE;
		if(sc->data[SC_ELEMENTWIND].timer != -1)		// 風
			ret = 20*sc->data[SC_ELEMENTWIND].val1 + ELE_WIND;
		if(sc->data[SC_ELEMENTPOISON].timer != -1)	// 毒
			ret = 20*sc->data[SC_ELEMENTPOISON].val1 + ELE_POISON;
		if(sc->data[SC_ELEMENTHOLY].timer != -1)		// 聖
			ret = 20*sc->data[SC_ELEMENTHOLY].val1 + ELE_HOLY;
		if(sc->data[SC_ELEMENTDARK].timer != -1)		// 闇
			ret = 20*sc->data[SC_ELEMENTDARK].val1 + ELE_DARK;
		if(sc->data[SC_ELEMENTELEKINESIS].timer != -1)	// 念
			ret = 20*sc->data[SC_ELEMENTELEKINESIS].val1 + ELE_GHOST;
		if(sc->data[SC_ELEMENTUNDEAD].timer != -1)	// 不死
			ret = 20*sc->data[SC_ELEMENTUNDEAD].val1 + ELE_UNDEAD;
		if(sc->data[SC_FLAMEARMOR].timer != -1)	// フレイムアーマー
			ret = 20 + ELE_FIRE;
		if(sc->data[SC_CRYSTAL_ARMOR].timer != -1)	// クリスタルアーマー
			ret = 20 + ELE_WATER;
		if(sc->data[SC_EYES_OF_STORM].timer != -1)	// アイズオブストーム
			ret = 20 + ELE_WIND;
		if(sc->data[SC_STRONG_PROTECTION].timer != -1)	// ストロングプロテクション
			ret = 20 + ELE_EARTH;
		if(sc->data[SC_POISON_SHIELD].timer != -1)	// ポイズンシールド
			ret = 20 + ELE_POISON;
		if(sc->data[SC_FREEZE].timer != -1)		// 凍結
			ret = 20 + ELE_WATER;
		if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0)
			ret = 20 + ELE_EARTH;
		if(sc->data[SC_SHAPESHIFT].timer != -1)		// シェイプシフト
			ret = 20 + sc->data[SC_SHAPESHIFT].val2;
		if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1)		// 急冷
			ret = 20 + ELE_WATER;
		if(sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1)	// 激流
			ret = 20 + ELE_WIND;
		if(sc->data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1)	// 結晶化
			ret = 20 + ELE_EARTH;
		if(sc->data[SC_HANDICAPSTATE_CONFLAGRATION].timer != -1)	// 火災
			ret = 20 + ELE_FIRE;

		if(ret != 20)
			return ret;
	}

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		// 10の位＝Lv*2、１の位＝属性
		ret = ((struct mob_data *)bl)->def_ele;
	}
	else if(bl->type == BL_PC && (struct map_session_data *)bl) {
		// 防御属性Lv1
		ret = 20+((struct map_session_data *)bl)->def_ele;
	}
	else if(bl->type == BL_PET && (struct pet_data *)bl) {
		ret = mobdb_search(((struct pet_data *)bl)->class_)->element;
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		ret = homun_db[hom_dbcheck_id(((struct homun_data *)bl)->status.class_)].element;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		struct merc_db *db = merc_search_data(((struct merc_data *)bl)->status.class_);
		if(db)
			ret = db->element;
	}
	else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		struct elem_db *db = elem_search_data(((struct elem_data *)bl)->status.class_);
		if(db)
			ret = db->element;
	}

	return ret;
}

/*==========================================
 * 対象の攻撃属性を返す
 *------------------------------------------
 */
int status_get_attack_element(struct block_list *bl)
{
	int ret = ELE_NEUTRAL;
	struct status_change *sc = NULL;

	nullpo_retr(ELE_NEUTRAL, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		ret = ELE_NEUTRAL;
	else if(bl->type == BL_PC && (struct map_session_data *)bl) {
		ret = ((struct map_session_data *)bl)->atk_ele;
	}
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		ret = ELE_NEUTRAL;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		ret = ELE_NONE;	// 無属性

	if(sc) {
		if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
			ret = ELE_WATER;
		if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
			ret = ELE_EARTH;
		if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
			ret = ELE_FIRE;
		if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
			ret = ELE_WIND;
		if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
			ret = ELE_POISON;
		if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
			ret = ELE_HOLY;
		if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
			ret = ELE_DARK;
		if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
			ret = ELE_GHOST;
		if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
			ret = ELE_UNDEAD;
		if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
			ret = sc->data[SC_SEVENWIND].val3;
		if(sc->data[SC_TIDAL_WEAPON].timer != -1 || sc->data[SC_TIDAL_WEAPON_OPTION].timer != -1)	// タイダルウェポン
			ret = ELE_WATER;
	}
	return ret;
}

/*==========================================
 * 対象の攻撃属性（左手）を返す
 *------------------------------------------
 */
int status_get_attack_element2(struct block_list *bl)
{
	nullpo_retr(ELE_NEUTRAL, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		int ret;
		struct status_change *sc = status_get_sc(bl);
		ret = ((struct map_session_data *)bl)->atk_ele_;

		if(sc) {
			if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
				ret = ELE_WATER;
			if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
				ret = ELE_EARTH;
			if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
				ret = ELE_FIRE;
			if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
				ret = ELE_WIND;
			if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
				ret = ELE_POISON;
			if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
				ret = ELE_HOLY;
			if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
				ret = ELE_DARK;
			if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
				ret = ELE_GHOST;
			if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
				ret = ELE_UNDEAD;
			if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
				ret = sc->data[SC_SEVENWIND].val3;
		}
		return ret;
	}
	return ELE_NEUTRAL;
}

/*==========================================
 * 対象の武器属性を除いた攻撃属性を返す
 *------------------------------------------
 */
int status_get_attack_element_nw(struct block_list *bl)
{
	int ret = ELE_NEUTRAL;
	struct status_change *sc = NULL;

	nullpo_retr(ELE_NEUTRAL, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_HOM && (struct homun_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_ELEM && (struct elem_data *)bl)
		ret = ELE_NONE;	// 無属性

	if(sc) {
		if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
			ret = ELE_WATER;
		if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
			ret = ELE_EARTH;
		if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
			ret = ELE_FIRE;
		if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
			ret = ELE_WIND;
		if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
			ret = ELE_POISON;
		if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
			ret = ELE_HOLY;
		if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
			ret = ELE_DARK;
		if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
			ret = ELE_GHOST;
		if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
			ret = ELE_UNDEAD;
		if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
			ret = sc->data[SC_SEVENWIND].val3;
		if(sc->data[SC__INVISIBILITY].timer != -1)	// インビジビリティ
			ret = ELE_GHOST;
		if(sc->data[SC_PYROCLASTIC].timer != -1)	// パイロクラスティック
			ret = ELE_FIRE;
	}
	return ret;
}

/*==========================================
 * 対象のパーティIDを返す
 *------------------------------------------
 */
int status_get_party_id(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		return ((struct map_session_data *)bl)->status.party_id;
	}
	else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		struct mob_data *md = (struct mob_data *)bl;
		return (md->master_id > 0)? -md->master_id: -md->bl.id;
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		//struct homun_data *hd = (struct homun_data *)bl;
		//return status_get_party_id(&hd->msd->bl);
		return 0;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		//struct merc_data *mcd = (struct merc_data *)bl;
		//return status_get_party_id(&mcd->msd->bl);
		return 0;
	}
	else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		//struct elem_data *eld = (struct elem_data *)bl;
		//return status_get_party_id(&eld->msd->bl);
		return 0;
	}
	else if(bl->type == BL_SKILL && (struct skill_unit *)bl) {
		return ((struct skill_unit *)bl)->group->party_id;
	}

	return 0;
}

/*==========================================
 * 対象のギルドIDを返す
 *------------------------------------------
 */
int status_get_guild_id(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		return ((struct map_session_data *)bl)->status.guild_id;
	} else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		return ((struct mob_data *)bl)->class_;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		//struct homun_data *hd = (struct homun_data *)bl;
		//return status_get_guild_id(&hd->msd->bl);
		return 0;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		//struct merc_data *mcd = (struct merc_data *)bl;
		//return status_get_guild_id(&mcd->msd->bl);
		return 0;
	} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		//struct elem_data *eld = (struct elem_data *)bl;
		//return status_get_guild_id(&eld->msd->bl);
		return 0;
	} else if(bl->type == BL_SKILL && (struct skill_unit *)bl) {
		return ((struct skill_unit *)bl)->group->guild_id;
	}

	return 0;
}

/*==========================================
 * 対象の種族を返す
 *------------------------------------------
 */
int status_get_race(struct block_list *bl)
{
	int race = RCT_FORMLESS;
	struct status_change *sc;

	nullpo_retr(RCT_FORMLESS, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		race = mobdb_search(((struct mob_data *)bl)->class_)->race;
	}
	else if(bl->type == BL_PC && (struct map_session_data *)bl) {
		race = ((struct map_session_data *)bl)->race;
	}
	else if(bl->type == BL_PET && (struct pet_data *)bl) {
		return mobdb_search(((struct pet_data *)bl)->class_)->race;
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		return homun_db[hom_dbcheck_id(((struct homun_data *)bl)->status.class_)].race;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		struct merc_db *db = merc_search_data(((struct merc_data *)bl)->status.class_);
		if(db)
			return db->race;
	}
	else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		struct elem_db *db = elem_search_data(((struct elem_data *)bl)->status.class_);
		if(db)
			return db->race;
	}
	else {
		return RCT_FORMLESS;
	}

	sc = status_get_sc(bl);

	if(sc) {
		if(sc->data[SC_RACEUNKNOWN].timer != -1)	// 無形
			race = RCT_FORMLESS;
		if(sc->data[SC_RACEUNDEAD].timer != -1)	// 不死
			race = RCT_UNDEAD;
		if(sc->data[SC_RACEBEAST].timer != -1)	// 動物
			race = RCT_BRUTE;
		if(sc->data[SC_RACEPLANT].timer != -1)	// 植物
			race = RCT_PLANT;
		if(sc->data[SC_RACEINSECT].timer != -1)	// 昆虫
			race = RCT_INSECT;
		if(sc->data[SC_RACEFISH].timer != -1)	// 魚貝
			race = RCT_FISH;
		if(sc->data[SC_RACEDEVIL].timer != -1)	// 悪魔
			race = RCT_DEMON;
		if(sc->data[SC_RACEHUMAN].timer != -1)	// 人間
			race = RCT_DEMIHUMAN;
		if(sc->data[SC_RACEANGEL].timer != -1)	// 天使
			race = RCT_ANGEL;
		if(sc->data[SC_RACEDRAGON].timer != -1)	// 竜
			race = RCT_DRAGON;
	}

	return race;
}

/*==========================================
 * 対象のサイズを返す
 *------------------------------------------
 */
int status_get_size(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		return mobdb_search(((struct mob_data *)bl)->class_)->size;
	} else if(bl->type == BL_PC && (struct map_session_data *)bl) {
		if(pc_isbaby((struct map_session_data *)bl) || pc_isdoram((struct map_session_data *)bl))
			return 0;
		else
			return 1;
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		return mobdb_search(((struct pet_data *)bl)->class_)->size;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		return homun_db[hom_dbcheck_id(((struct homun_data *)bl)->status.class_)].size;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		struct merc_db *db = merc_search_data(((struct merc_data *)bl)->status.class_);
		if(db)
			return db->size;
	} else if(bl->type == BL_ELEM && (struct elem_data *)bl) {
		struct elem_db *db = elem_search_data(((struct elem_data *)bl)->status.class_);
		if(db)
			return db->size;
	}

	return 1;
}

/*==========================================
 * 対象のモードを返す
 *------------------------------------------
 */
int status_get_mode(struct block_list *bl)
{
	nullpo_retr(0x01, bl);

	if(bl->type == BL_MOB) {
		struct mob_data* md = (struct mob_data*)bl;
		return (md->mode ? md->mode : mobdb_search(md->class_)->mode);
	}
	else if(bl->type == BL_PET) {
		return mobdb_search(((struct pet_data *)bl)->class_)->mode;
	}

	return MD_CANMOVE;	// とりあえず動くということで1
}

/*==========================================
 * 対象のMVPExpを返す
 *------------------------------------------
 */
int status_get_mexp(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mobdb_search(((struct mob_data *)bl)->class_)->mexp;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return mobdb_search(((struct pet_data *)bl)->class_)->mexp;

	return 0;
}

/*==========================================
 * 対象の敵タイプを返す
 *------------------------------------------
 */
int status_get_enemy_type(struct block_list *bl)
{
	nullpo_retr(EMY_ETC, bl);

	if( bl->type == BL_PC )
		return EMY_PC;
	else if( bl->type == BL_MOB && !(status_get_mode(bl)&MD_BOSS) )
		return EMY_MOB;
	else if( bl->type == BL_HOM )
		return EMY_HOM;
	else if( bl->type == BL_MERC )
		return EMY_MERC;

	return EMY_ETC;
}

/*==========================================
 * 対象の服色を返す
 *------------------------------------------
 */
short status_get_clothes_color(struct block_list *bl)
{
	short color = -1;

	nullpo_retr(-1, bl);

	if(bl->type == BL_PC) {
		color = ((struct map_session_data *)bl)->status.clothes_color;
	} else if(bl->type & (BL_MOB | BL_PET)) {
		int id = status_get_class(bl);
		if(id >= 0 && mob_is_pcview(id))
			color = mob_get_clothes_color(id);
	}
	if(color >= 0 && color < MAX_CLOTH_COLOR)
		return color;

	return -1;
}

/*==========================================
 * StatusChangeの取得
 *------------------------------------------
 */
struct status_change *status_get_sc(struct block_list *bl)
{
	nullpo_retr(NULL, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return &((struct mob_data*)bl)->sc;
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return &((struct map_session_data*)bl)->sc;
	if(bl->type == BL_HOM && (struct homun_data *)bl)
		return &((struct homun_data*)bl)->sc;
	if(bl->type == BL_MERC && (struct merc_data *)bl)
		return &((struct merc_data*)bl)->sc;
	if(bl->type == BL_ELEM && (struct elem_data *)bl)
		return &((struct elem_data*)bl)->sc;

	return NULL;
}

/*==========================================
 * 魔法無効かどうか
 *------------------------------------------
 */
int status_check_no_magic_damage(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
	{
		if(((struct map_session_data*)bl)->special_state.no_magic_damage)
			return 1;
	}
	return 0;
}

/*==========================================
 * 状態異常の耐性計算
 *------------------------------------------
 */
int status_change_rate(struct block_list *bl,int type,int rate,int src_level)
{
	int sc_flag = 0;
#ifndef PRE_RENEWAL
	int cap;
#endif

	nullpo_retr(0, bl);

	if(type < 0)	// typeが0未満の場合失敗
		return 0;

	if(rate <= 0)	// 確率が0以下のものは失敗
		return 0;

#ifndef PRE_RENEWAL
	cap = src_level - status_get_lv(bl);
	if(cap <= 0)	// 対象のほうがレベルが高い場合は0
		cap = 0;
	else
		cap = cap * cap / 5;
#endif

	switch(type) {	// 状態異常耐性ステータス rateは万分率
#ifdef PRE_RENEWAL
		case SC_STONE:	// 石化
		case SC_FREEZE:	// 凍結
			rate += src_level*10 - rate * status_get_mdef(bl)*10 / 1000 - status_get_luk(bl)*10 - status_get_lv(bl)*10;
			sc_flag = 1;
			break;
		case SC_STUN:	// スタン
		case SC_SILENCE:	// 沈黙
		case SC_POISON:	// 毒
		case SC_DPOISON:	// 猛毒
		case SC_BLEED:	// 出血
			rate += src_level*10 - rate * status_get_vit(bl)*10 / 1000 - status_get_luk(bl)*10 - status_get_lv(bl)*10;
			sc_flag = 1;
			break;
		case SC_SLEEP:	// 睡眠
			rate += src_level*10 - rate * status_get_int(bl)*10 / 1000 - status_get_luk(bl)*10 - status_get_lv(bl)*10;
			sc_flag = 1;
			break;
		case SC_BLIND:	// 暗黒
			rate += src_level*10 - rate * (status_get_vit(bl)*10 + status_get_int(bl)*10) / 2000 - status_get_luk(bl)*10 - status_get_lv(bl)*10;
			sc_flag = 1;
			break;
		case SC_CURSE:	// 呪い
			rate += src_level*10 - rate * status_get_luk(bl)*10 / 1000 - status_get_luk(bl)*10;
			sc_flag = 1;
			break;
		case SC_CONFUSION:	// 混乱
			rate += status_get_luk(bl)*10 + -(rate * (status_get_str(bl)*10 + status_get_int(bl)*10) / 2000) - src_level*10 + status_get_lv(bl)*10;
			sc_flag = 1;
			break;
#else
		case SC_STONE:	// 石化
		case SC_FREEZE:	// 凍結
			rate = rate * (100 - (status_get_mdef(bl) - cap)) / 100;
			sc_flag = 1;
			break;
		case SC_STUN:	// スタン
		case SC_POISON:	// 毒
		case SC_DPOISON:	// 猛毒
			rate = rate * (100 - (status_get_vit(bl) - cap)) / 100;
			sc_flag = 1;
			break;
		case SC_SLEEP:	// 睡眠
		case SC_BLEED:	// 出血
			rate = rate * (100 - (status_get_agi(bl) - cap)) / 100;
			sc_flag = 1;
			break;
		case SC_BLIND:	// 暗黒
		case SC_SILENCE:	// 沈黙
			rate = rate * (100 - (status_get_int(bl) - cap)) / 100;
			sc_flag = 1;
			break;
		case SC_CONFUSION:	// 混乱
		case SC_CURSE:	// 呪い
			rate = rate * (100 - (status_get_luk(bl) - cap)) / 100;
			sc_flag = 1;
			break;
#endif
		case SC_TOXIN:
		case SC_PARALIZE:
		case SC_VENOMBLEED:
		case SC_MAGICMUSHROOM:
		case SC_DEATHHURT:
		case SC_PYREXIA:
		case SC_OBLIVIONCURSE:
		case SC_LEECHEND:
			if(bl->type == BL_PC)
				rate -= rate * pc_checkskill((struct map_session_data *)bl,GC_RESEARCHNEWPOISON) * 5 / 100;
			break;
		case SC_PARALYZE:
			rate = rate * (100 - (status_get_vit(bl)/5 + status_get_luk(bl)/10)) / 100;
			break;
		case SC_HANDICAPSTATE_DEEPBLIND:		// 漆黒
		case SC_HANDICAPSTATE_DEEPSILENCE:		// 静寂
		case SC_HANDICAPSTATE_LASSITUDE:		// 無気力
		case SC_HANDICAPSTATE_FROSTBITE:		// 急冷
		case SC_HANDICAPSTATE_SWOONING:			// 失神
		case SC_HANDICAPSTATE_LIGHTNINGSTRIKE:	// 激流
		case SC_HANDICAPSTATE_CRYSTALLIZATION:	// 結晶化
		case SC_HANDICAPSTATE_CONFLAGRATION:	// 火災
		case SC_HANDICAPSTATE_MISFORTUNE:		// 不幸
		case SC_HANDICAPSTATE_DEADLYPOISON:		// 強毒
		case SC_HANDICAPSTATE_DEPRESSION:		// 憂鬱
		case SC_HANDICAPSTATE_HOLYFLAME:		// 聖火
			rate = rate * (100 - (status_get_lv(bl) - src_level)) / 100;
			break;
		default:
			break;
	}
	if(sc_flag) {
		struct status_change *sc = status_get_sc(bl);
		if(sc) {
			if(sc->data[SC_STATUS_UNCHANGE].timer != -1 && status_is_disable(type,0x10)) {
				rate = 0;	// ゴスペルの全状態異常耐性中なら無効
			}
			if(sc->data[SC_REFRESH].timer != -1 && status_is_disable(type,0x10)) {
				rate = 0;	// リフレッシュ効果中は無効
			}
			if(sc->data[SC_INSPIRATION].timer != -1 && status_is_disable(type,0x10)) {
				rate = 0;	// インスピレーション効果中なら無効
			}
		}
	}

	return rate;
}

/*==========================================
 * 状態異常の複写（デッドリーインフェクト）
 *------------------------------------------
 */
int status_change_copy(struct block_list *src,struct block_list *bl)
{
	int type;
	unsigned int tick;
	struct status_change *sc;
	struct TimerData *td = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(src));

	if(sc->count <= 0)
		return 0;
	if(sc->data[SC__DEADLYINFECT].timer != -1 && atn_rand()%100 > sc->data[SC__DEADLYINFECT].val1*20)
		return 0;

	tick = gettick();
	status_calc_pc_stop_begin(bl);

	for(type = 0; type < MAX_STATUSCHANGE; type++) {
		if(scdata_db[type].copyable) {
			if(sc->data[type].timer != -1)
			{
				td = get_timer(sc->data[type].timer);
				if (td == NULL || td->func != status_change_timer || DIFF_TICK(td->tick,tick) < 0)
					continue;
				status_change_start(bl,type,sc->data[type].val1,sc->data[type].val2,sc->data[type].val3,sc->data[type].val4,DIFF_TICK(td->tick,tick),0);
			}
		}
	}
	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * ステータス異常データの動的確保
 *------------------------------------------
 */
#ifdef DYNAMIC_SC_DATA

int status_calloc_sc_data(struct status_change *sc)
{
	if(sc && sc->data == dummy_sc_data)
	{
		int i;
		sc->data = (struct status_change_data *)aCalloc(MAX_STATUSCHANGE, sizeof(struct status_change_data));
		for(i=0; i<MAX_STATUSCHANGE; i++) {
			sc->data[i].timer = -1;
			sc->data[i].val1  = 0;
			sc->data[i].val2  = 0;
			sc->data[i].val3  = 0;
			sc->data[i].val4  = 0;
		}
		sc->count = 0;
		return 1;	// calloced
	}

	return 0;
}

int status_free_sc_data(struct status_change *sc)
{
	if(sc && sc->data != dummy_sc_data)
	{
		map_freeblock(sc->data);
		sc->data  = dummy_sc_data;
		sc->count = 0;
	}

	return 0;
}

#endif

/*==========================================
 * ステータス再計算を一時停止する
 *------------------------------------------
 */
int status_calc_pc_stop_begin(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
		status_calc_pc_ctrl_stop_begin(&((struct map_session_data *)bl)->stop_status_calc_pc);
	return 0;
}

/*==========================================
 * ステータス再計算を再開する
 *------------------------------------------
 */
int status_calc_pc_stop_end(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		int stop_ret = status_calc_pc_ctrl_stop_end(&sd->stop_status_calc_pc, &sd->call_status_calc_pc_while_stopping);
		if(stop_ret > 0)
			status_calc_pc(sd,0);
		if(stop_ret < 0) {
			printf("status_calc_pc_stop_endが不正に呼び出されています\n");
		}
	}
	return 0;
}
/*==========================================
 * ステータス異常開始タイマー
 *------------------------------------------
 */
static int status_pretimer_timer(int tid, unsigned int tick, int id, void *data)
{
	struct block_list *bl = map_id2bl(id);
	struct status_pretimer *stpt = NULL;
	struct unit_data *ud;

	if(bl == NULL)
		return 0;	// 該当IDがすでに消滅している

	nullpo_retr(0, ud = unit_bl2ud(bl));

	do {
		if(bl->prev == NULL)
			break;

		stpt = (struct status_pretimer*)data;
		stpt->timer = -1;

		if(linkdb_erase(&ud->statuspretimer, stpt) == NULL) {
			printf("status_pretimer: data lost !!\n");
			break;
		}

		if(stpt->target_id) {
			struct block_list *target = map_id2bl(stpt->target_id);
			if( target == NULL || bl->m != target->m || unit_isdead(bl) || unit_isdead(target) )
				break;
		} else {
			if(bl->m != stpt->m)
				break;
		}

		status_change_start(bl, stpt->type, stpt->val1, stpt->val2, stpt->val3, stpt->val4, stpt->tick, stpt->flag);
	} while(0);

	aFree(stpt);

	return 0;
}

/*==========================================
 * ステータス異常開始タイマーの削除
 *------------------------------------------
 */
int status_clearpretimer(struct block_list *bl)
{
	struct unit_data *ud;
	struct linkdb_node *node1, *node2;

	nullpo_retr(0, bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	node1 = ud->statuspretimer;
	while(node1) {
		struct status_pretimer *stpt = (struct status_pretimer *)node1->data;
		if(stpt->timer != -1) {
			delete_timer(stpt->timer, status_pretimer_timer);
		}
		node2 = node1->next;
		aFree(stpt);
		node1 = node2;
	}
	linkdb_final(&ud->statuspretimer);

	return 0;
}

/*==========================================
 * ステータス異常開始タイマーのセット
 *------------------------------------------
 */
int status_change_pretimer(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag,int pre_tick)
{
	struct unit_data *ud;
	struct status_pretimer *stpt;

	nullpo_retr(1, bl);
	ud = unit_bl2ud(bl);
	if(ud == NULL)
		return 0;

	stpt = (struct status_pretimer *)aCalloc(1, sizeof(struct status_pretimer));
	stpt->timer     = add_timer(pre_tick, status_pretimer_timer, bl->id, stpt);
	stpt->target_id = bl->id;
	stpt->m         = bl->m;
	stpt->type      = type;
	stpt->val1      = val1;
	stpt->val2      = val2;
	stpt->val3      = val3;
	stpt->val4      = val4;
	stpt->tick      = tick;
	stpt->flag      = flag;

	linkdb_insert(&ud->statuspretimer, stpt, stpt);

	return 0;
}

/*==========================================
 * ステータス異常終了タイマー
 *
 * ソースを修正する方への注意
 *
 * ・状態異常継続時には、add_timer() した直後に break すること
 * ・状態異常終了時には、関数の最後にあるstatus_change_end() の
 *   呼び出し前に return しないこと
 *
 * この２点が守られていないと、他人の状態異常が勝手に解除されたり、
 * delete_timer errorが出てくるなどのバグが発生します。
 *------------------------------------------
 */
int status_change_timer(int tid, unsigned int tick, int id, void *data)
{
	int type  = PTR2INT(data);
	int timer = -1;
	struct block_list *bl;
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;

	if(type < 0 || type >= MAX_STATUSCHANGE)
		return 0;

	if((bl = map_id2bl(id)) == NULL)
		return 0;	// 該当IDがすでに消滅しているというのはいかにもありそうなのでスルーしてみる

	nullpo_retr(0, sc = status_get_sc(bl));

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );
	eld = BL_DOWNCAST( BL_ELEM, bl );

	if(sc->data[type].timer != tid) {
		if(battle_config.error_log)
			printf("status_change_timer %d != %d (type = %d)\n",tid,sc->data[type].timer,type);
		return 0;
	}

	map_freeblock_lock();

	switch(type) {	/* 特殊な処理になる場合 */
	case SC_MAXIMIZEPOWER:	/* マキシマイズパワー */
	case SC_CLOAKING:	/* クローキング */
		if(sd) {
			if(sd->status.sp > 0) {	/* SP切れるまで持続 */
				sd->status.sp--;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(	/* タイマー再設定 */
					sc->data[type].val2+tick, status_change_timer,
					bl->id, data);
			}
		}
		break;

	case SC_CHASEWALK:	/* チェイスウォーク */
		if(sd) {
			int sp = 10+sc->data[SC_CHASEWALK].val1*2;
			if(map[sd->bl.m].flag.gvg)
				sp *= 5;
			if(sd->status.sp > sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				if((++sc->data[SC_CHASEWALK].val4) == 1) {
					// ローグの魂なら効果時間10倍
					status_change_start(
						bl, SC_CHASEWALK_STR, 1<<(sc->data[SC_CHASEWALK].val1-1), 0, 0, 0,
						((sc->data[SC_ROGUE].timer != -1)? 300000: 30000), 0
					);
				}
				timer = add_timer( /* タイマー再設定 */
					sc->data[type].val2+tick, status_change_timer, bl->id, data);
			}
		}
		break;

	case SC_HIDING:		/* ハイディング */
		if(sd) {		/* SPがあって、時間制限の間は持続 */
			if(sd->status.sp > 0 && (--sc->data[type].val2) > 0) {
#ifdef PRE_RENEWAL
				if(sc->data[type].val2 % (sc->data[type].val1+3) == 0) {
#else
				if(sc->data[type].val2 % (sc->data[type].val1+4) == 0) {
#endif
					sd->status.sp--;
					clif_updatestatus(sd,SP_SP);
				}
				timer = add_timer(	/* タイマー再設定 */
					1000+tick, status_change_timer,
					bl->id, data);
			}
		}
		break;

	case SC_SIGHTBLASTER:
	case SC_SIGHT:		/* サイト */
	case SC_RUWACH:		/* ルアフ */
		{
			int range;
			if(type == SC_RUWACH)
				range = 2;
			else if(type == SC_SIGHTBLASTER)
				range = 1;
			else
				range = (sc->data[type].val4 == NPC_WIDESIGHT)? 14: 3;

			map_foreachinarea(status_change_timer_sub,
				bl->m, bl->x-range, bl->y-range, bl->x+range,bl->y+range, BL_CHAR,
				bl, type, sc->data[type].val1, tick);

			if((--sc->data[type].val2) > 0) {
				timer = add_timer(	/* タイマー再設定 */
					250+tick, status_change_timer,
					bl->id, data);
			}
		}
		break;

	case SC_SIGNUMCRUCIS:		/* シグナムクルシス */
		{
			int race = status_get_race(bl);
			if(race == RCT_DEMON || battle_check_undead(race,status_get_elem_type(bl))) {
				timer = add_timer(1000*600+tick, status_change_timer, bl->id, data);
			}
		}
		break;

	case SC_PROVOKE:	/* プロボック/オートバーサーク */
		if(sc->data[type].val2 != 0) {	/* オートバーサーク（１秒ごとにHPチェック） */
			if(status_get_hp(bl) > status_get_max_hp(bl)>>2)	/* 停止 */
				break;
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;

	case SC_DISSONANCE:	/* 不協和音 */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			struct block_list *src;
			if(!unit || !unit->group)
				break;
			src = map_id2bl(unit->group->src_id);
			if(!src)
				break;
			battle_skill_attack(BF_MISC,src,&unit->bl,bl,unit->group->skill_id,sc->data[type].val1,tick,0);
			timer = add_timer(
				skill_get_time2(unit->group->skill_id,unit->group->skill_lv)+tick, status_change_timer,
				bl->id, data);
		}
		break;
	case SC_UGLYDANCE:	/* 自分勝手なダンス */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			struct block_list *src;
			if(!unit || !unit->group)
				break;
			src = map_id2bl(unit->group->src_id);
			if(!src)
				break;
			skill_additional_effect(src,bl,unit->group->skill_id,sc->data[type].val1,0,tick);
			timer = add_timer(
				skill_get_time2(unit->group->skill_id,unit->group->skill_lv)+tick, status_change_timer,
				bl->id, data);
		}
		break;

	case SC_LULLABY:	/* 子守唄 */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			int interval;

			if(!unit || !unit->group || unit->group->src_id == bl->id)
				break;
#ifdef PRE_RENEWAL
			interval = skill_get_time(unit->group->skill_id,unit->group->skill_lv)/10;
#else
			interval = skill_get_time(unit->group->skill_id,unit->group->skill_lv)/15;
#endif
			skill_additional_effect(bl,bl,unit->group->skill_id,sc->data[type].val1,BF_LONG|BF_SKILL|BF_MISC,tick);
			timer = add_timer(interval+tick, status_change_timer, bl->id, data);
		}
		break;

	case SC_STONE:
		if(sc->data[type].val2 != 0) {
			sc->data[type].val2 = 0;
			sc->data[type].val4 = 0;
			unit_stop_walking(bl,1);
			sc->opt1 = OPT1_STONECURSE;
			clif_changeoption(bl);
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		else if((--sc->data[type].val3) > 0) {
			int hp = status_get_max_hp(bl);
			if((++sc->data[type].val4)%5 == 0 && status_get_hp(bl) > hp>>2) {
				hp = (hp < 100)? 1: hp/100;
				unit_heal(bl,-hp,0,0,0);
			}
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_POISON:
		if(sc->data[SC_SLOWPOISON].timer == -1 && (--sc->data[type].val3) > 0) {
			int hp    = status_get_hp(bl);
			int p_dmg = status_get_max_hp(bl);
			if(hp > p_dmg>>2) {		// 最大HPの25%以上
				p_dmg = 3 + p_dmg*3/200;
				if(p_dmg >= hp)
					p_dmg = hp-1;	// 毒では死なない
				unit_heal(bl, -p_dmg, 0, 0, 0);
			}
		}
		if(sc->data[type].val3 > 0) {
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_DPOISON:
		if(sc->data[SC_SLOWPOISON].timer == -1 && (--sc->data[type].val3) > 0) {
			int hp = status_get_max_hp(bl);
			if(status_get_hp(bl) > hp>>2) {
				hp = 3 + hp/50;
				unit_heal(bl, -hp, 0, 0, 0);
			}
		}
		if(sc->data[type].val3 > 0 && !unit_isdead(bl) && sc->data[type].timer != -1) {
			// 生きていて解除済みでないなら継続
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_BLEED:
		if(--sc->data[type].val3 > 0) {
			int dmg = atn_rand()%600 + 200;
			if(md) {
				// mobはHP50以下にならない
				md->hp = (md->hp - dmg < 50)? 50: md->hp - dmg;
			} else {
				unit_heal(bl, -dmg, 0, 0, 0);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(10000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_TENSIONRELAX:	/* テンションリラックス */
		if(sd) {		/* HPが満タンでなければ継続 */
			if(sd->status.max_hp > sd->status.hp) {
				if(sc->data[type].val2 % (sc->data[type].val1+3) == 0)
					timer = add_timer(	/* タイマー再設定 */
						10000+tick, status_change_timer,
						bl->id, data);
			} else if(sd->status.max_hp <= sd->status.hp) {
				status_change_end(&sd->bl,SC_TENSIONRELAX,-1);
			}
		}
		break;

	/* 時間切れ無し？？ */
	case SC_AETERNA:
	case SC_TRICKDEAD:
	case SC_REJECTSWORD:		/* リジェクトソード */
	case SC_MEMORIZE:		/* メモライズ */
	case SC_SACRIFICE:		/* サクリファイス */
	case SC_READYSTORM:
	case SC_READYDOWN:
	case SC_READYTURN:
	case SC_READYCOUNTER:
	case SC_LUNARSTANCE:
	case SC_UNIVERSESTANCE:
	case SC_SUNSTANCE:
	case SC_STARSTANCE:
	case SC_DODGE:
	case SC_AUTOBERSERK:
	case SC_RUN:
	case SC_MARIONETTE:
	case SC_MARIONETTE2:
	case SC_REBIRTH:
	case SC_WUGDASH:
	case SC_EXEEDBREAK:
	case SC_SUHIDE:
	case SC_ALL_RIDING:	/* 騎乗システム */
	case SC_ON_PUSH_CART:	/* カート */
	case SC_HAT_EFFECT:	/* 頭装備エフェクト */
	case SC_ACTIVE_MONSTER_TRANSFORM:	/* アクティブモンスター変身 */
	case SC_INVINCIBLE:	/* インビンシブル */
	case SC_STYLE_CHANGE:		/* スタイルチェンジ */
	case SC_GUARD_STANCE:		/* ガードスタンス */
	case SC_ATTACK_STANCE:		/* アタックスタンス */
	case SC_INTENSIVE_AIM_COUNT:	/* インテンシブエイム(カウント) */
		timer = add_timer(1000 * 600 + tick, status_change_timer, bl->id, data);
		break;
	case SC_MODECHANGE:
		clif_emotion(bl,1);
		timer = add_timer(1500 + tick, status_change_timer, bl->id, data);
		break;
	case SC_LONGINGFREEDOM:
		if(sd && sd->status.sp >= 3) {
			if(--sc->data[type].val3 <= 0)
			{
				sd->status.sp -= 3;
				clif_updatestatus(sd, SP_SP);
				sc->data[type].val3 = 3;
			}
			timer = add_timer(1000 + tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_DANCING:
		if(sd) {	// ダンススキルの時間SP消費
			int cost = 1;
			if(sc->data[type].val1 == CG_HERMODE)
				cost = 5;
			if(sd->status.sp < cost) {
				skill_stop_dancing(&sd->bl,0);
			} else if(--sc->data[type].val3 > 0) {
				int s = 0;

				switch(sc->data[type].val1) {
				case BD_RICHMANKIM:			/* ニヨルドの宴 3秒にSP1 */
				case BD_DRUMBATTLEFIELD:		/* 戦太鼓の響き 3秒にSP1 */
				case BD_RINGNIBELUNGEN:			/* ニーベルングの指輪 3秒にSP1 */
				case BD_SIEGFRIED:			/* 不死身のジークフリード 3秒にSP1 */
				case BA_DISSONANCE:			/* 不協和音 3秒でSP1 */
				case BA_ASSASSINCROSS:			/* 夕陽のアサシンクロス 3秒でSP1 */
				case DC_UGLYDANCE:			/* 自分勝手なダンス 3秒でSP1 */
				case CG_LONGINGFREEDOM:
					s = 3;
					break;
				case BD_LULLABY:			/* 子守歌 4秒にSP1 */
				case BD_ETERNALCHAOS:			/* 永遠の混沌 4秒にSP1 */
				case BD_ROKISWEIL:			/* ロキの叫び 4秒にSP1 */
				case DC_FORTUNEKISS:			/* 幸運のキス 4秒でSP1 */
					s = 4;
					break;
				case BD_INTOABYSS:			/* 深淵の中に 5秒にSP1 */
				case BA_WHISTLE:			/* 口笛 5秒でSP1 */
				case DC_HUMMING:			/* ハミング 5秒でSP1 */
				case BA_POEMBRAGI:			/* ブラギの詩 5秒でSP1 */
				case DC_SERVICEFORYOU:			/* サービスフォーユー 5秒でSP1 */
				case CG_HERMODE:			/* ヘルモードの杖 */
					s = 5;
					break;
				case BA_APPLEIDUN:			/* イドゥンの林檎 6秒でSP1 */
					s = 6;
					break;
				case DC_DONTFORGETME:			/* 私を忘れないで… 10秒でSP1 */
				case CG_MOONLIT:			/* 月明りの下で 10秒でSP1？ */
					s = 10;
					break;
				}
				if(s && (sc->data[type].val3 % s) == 0) {
					sd->status.sp -= cost;
					clif_updatestatus(sd,SP_SP);
				}
				timer = add_timer(	/* タイマー再設定 */
					1000+tick, status_change_timer,
					bl->id, data);
			}
		} else if(md)
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		break;
	case SC_BERSERK:		/* バーサーク */
		{
			int dmg = (int)((atn_bignumber)status_get_max_hp(bl) * 5 / 100);
			if(status_get_hp(bl) - dmg > 100) {
				if(sd) {
					sd->status.hp -= dmg;
					clif_updatestatus(sd,SP_HP);
				} else if(hd) {
					hd->status.hp -= dmg;
					clif_send_homstatus(hd->msd,0);
				} else if(mcd) {
					mcd->status.hp -= dmg;
					clif_mercupdatestatus(mcd->msd,SP_HP);
				}
				timer = add_timer(	/* タイマー再設定 */
					10000+tick, status_change_timer,
					bl->id, data);
			} else {
				if(sd) {
					sd->status.hp = 100;
					clif_updatestatus(sd,SP_HP);
				} else if(hd) {
					hd->status.hp = 100;
					clif_send_homstatus(hd->msd,0);
				} else if(mcd) {
					mcd->status.hp = 100;
					clif_mercupdatestatus(mcd->msd,SP_HP);
				}
			}
		}
		break;
	case SC_NOCHAT:			/* チャット禁止状態 */
		if(sd) {
			if(++sd->status.manner && time(NULL) < (sc->data[type].val2 - 60*sd->status.manner)) {	// 開始からstatus.manner分経ってないので継続
				clif_updatestatus(sd,SP_MANNER);
				timer = add_timer(	/* タイマー再設定(60秒) */
					60000+tick, status_change_timer,
					bl->id, data);
			}
		}
		break;
	case SC_SELFDESTRUCTION:		/* 自爆 */
		if(md && unit_iscasting(&md->bl) && md->state.special_mob_ai == 3 && md->mode&MD_CANMOVE && md->speed > 0) {
			md->speed -= 5;
			if(md->speed <= 0)
				md->speed = 1;
			md->dir = sc->data[type].val4;
			unit_walktodir(&md->bl,1);	// 速度が変わるので毎回呼び出す

			/* タイマー再設定 */
			timer = add_timer(100+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_BOSSMAPINFO:			/* 凸面鏡 */
		if(sd && --sc->data[type].val2 > 0) {
			struct mob_data *mmd = map[sd->bl.m].mvpboss;
			if(mmd == NULL)
				break;
			if(mmd->bl.prev == NULL) {
				if(sc->data[type].val3 >= 0) {
					// 倒されたので次回の出現時間をアナウンスして終了
					int diff = DIFF_TICK(mmd->last_spawntime, gettick());
					if(diff < 0)
						diff = 0;
					clif_bossmapinfo(sd, mmd->name, 0, 0, diff, 3);
					break;
				}
			} else {
				if(sc->data[type].val3 < 0) {
					// 出現したのでアナウンス
					clif_bossmapinfo(sd, mmd->name, 0, 0, 0, 2);
				}
				if(sc->data[type].val3 != mmd->bl.m || sc->data[type].val4 != mmd->bl.x + (mmd->bl.y << 16)) {
					// 出現中で座標が変化しているのでミニMAPのドットを更新
					if(mmd->bl.m == sd->bl.m) {
						clif_bossmapinfo(sd, "", mmd->bl.x, mmd->bl.y, 0, 1);
					} else {
						clif_bossmapinfo(sd, "", -1, -1, 0, 1);
					}
					sc->data[type].val3 = mmd->bl.m;
					sc->data[type].val4 = mmd->bl.x + (mmd->bl.y << 16);
				}
			}
			/* タイマー再設定 */
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_CHANGE:		/* メンタルチェンジ */
		unit_heal(bl, -status_get_hp(bl)+10, -status_get_sp(bl)+10, 0, 0);	// 時間切れのときのみHP,SPが10になる
		break;
	case SC_ABUNDANCE:		/* アバンダンス */
		if((--sc->data[type].val3) > 0) {
			unit_heal(bl, 0, 60, 0, 1);
			timer = add_timer(10000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_FEAR:				/* 恐怖 */
		if(sc->data[type].val3 > 0) {
			timer = add_timer(sc->data[type].val3+tick, status_change_timer, bl->id, data);
			sc->data[type].val3 = 0;
		}
		break;
	case SC_WEAPONBLOCKING:		/* ウェポンブロッキング */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				if(sd->status.sp < 3)
					break;
				sd->status.sp -= 3;
				clif_updatestatus(sd,SP_SP);
			}
			timer = add_timer(5000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_CLOAKINGEXCEED:	/* クローキングエクシード */
		if(sd) {
			int sp = 10 - sc->data[type].val1;
			if(sp > 0 && sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_TOXIN:		/* トキシン */
		if((--sc->data[type].val2) > 0) {
			int damage = (int)((atn_bignumber)status_get_max_sp(bl) * 3 / 100);
			if(damage)
				unit_heal(bl, 0, -damage, 0, 0);
			clif_damage(bl,bl,tick,0,status_get_dmotion(bl),1,0,0,0,0);
			unit_skillcastcancel(bl,0);		// 詠唱妨害
			timer = add_timer(10000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_MAGICMUSHROOM:	/* マジックマッシュルーム */
		if((--sc->data[type].val2) > 0) {
			clif_emotion(bl,18);
			if(sc->data[type].val2 % 2 == 0) {
				int damage = (int)((atn_bignumber)status_get_max_hp(bl) * 3 / 100);
				if(sd) {
					sd->skill_item.id = skill_searchrandomid(1);
					sd->skill_item.lv = 1;
					sd->skill_item.flag = 1;
					clif_item_skill(sd, sd->skill_item.id, sd->skill_item.lv, "");
				}
				if(damage)
					unit_heal(bl, -damage, 0, 0, 0);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(2000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_PYREXIA:	/* パイレックシア */
		if((--sc->data[type].val2) > 0) {
			clif_damage(bl,bl,tick,0,status_get_dmotion(bl),100,0,0,0,0);
			battle_damage(bl,bl,100,0,0,0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(3000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_OBLIVIONCURSE:	/* オブリビオンカース */
		if((--sc->data[type].val2) > 0) {
			clif_emotion(bl,1);
			timer = add_timer(2000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_LEECHEND:		/* リーチエンド */
		if((--sc->data[type].val2) > 0) {
			int damage = status_get_max_hp(bl) / 100;
			if(damage)
				unit_heal(bl, -damage, 0, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_RENOVATIO:		/* レノヴァティオ */
		if((--sc->data[type].val3) > 0) {
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * sc->data[type].val2 / 100);
			if(heal) {
				if(sc->data[SC_AKAITSUKI].timer != -1)
					unit_fixdamage(bl,bl,gettick(),0,status_get_dmotion(bl),heal,0,0,0,0);
				else
					unit_heal(bl,heal,0,0,1);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(5000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_SUMMONBALL1:		/* サモンボール(1個目) */
	case SC_SUMMONBALL2:		/* サモンボール(2個目) */
	case SC_SUMMONBALL3:		/* サモンボール(3個目) */
	case SC_SUMMONBALL4:		/* サモンボール(4個目) */
	case SC_SUMMONBALL5:		/* サモンボール(5個目) */
		if((--sc->data[type].val3) > 0) {
			// SP消費
			if(sd) {
				int sp = 6 - sc->data[type].val1;
				if(sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000 + tick, status_change_timer, bl->id, data);
				}
			}
			else
				timer = add_timer(1000 + tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_HELLINFERNO:	/* ヘルインフェルノ */
		if((--sc->data[type].val2) > 0) {
			if(++sc->data[type].val3 % 3 == 0) {
				int damage = (int)((atn_bignumber)status_get_max_hp(bl) * 3 / 100);
				sc->data[type].val3 = 0;
				clif_damage(bl,bl,tick,0,0,1000 + damage,0,9,0,0);
				battle_damage(bl,bl,1000 + damage,0,0,0);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_SPELLBOOK:	/* スペルブック */
		if(sd) {
			int sp = sd->freeze_sp_slot;
			if(sp > 0 && sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(10000 + tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		if((--sc->data[type].val2) > 0) {
			int damage = (int)((atn_bignumber)status_get_max_sp(bl) * sc->data[type].val1 * 5 / 100);
			if(damage)
				unit_heal(bl, 0, -damage, 0, 0);
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_CAMOUFLAGE:	/* カモフラージュ */
		if((++sc->data[type].val2) > 10)
			sc->data[type].val2 = 10;
		if(sd) {
			int sp = 7 - sc->data[type].val1;
			if(sp > 0 && sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		} else {
			timer = add_timer(1000+tick, status_change_timer,bl->id, data);
		}
		break;
	case SC_OVERHEAT_LIMITPOINT:		/* オーバーヒート加熱値 */
		if(sd && !pc_isgear(sd))		// 魔導ギア非搭乗ならば止める
			break;
		if(sc->data[type].val2 > 0)		// 冷却時間（10秒）が残っている
			sc->data[type].val2--;
		if(sc->data[type].val2 <= 0)	// 冷却時間が満了していたら加熱値を減算
			sc->data[type].val1--;
		if(sc->data[type].val1 > 0)		// 加熱値が残っているため継続
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		break;
	case SC_OVERHEAT:			/* オーバーヒート */
		if(sd && !pc_isgear(sd))		// 魔導ギア非搭乗ならば止める
			break;
		if(sc->data[SC_OVERHEAT_LIMITPOINT].timer == -1)	// オーバーヒート加熱値が加算されてなければ止める
			break;
		else {
			int damage = status_get_max_hp(bl) / 100;
			int hp = status_get_hp(bl);
			if(damage && hp) {
				if(damage >= hp)
					damage = hp - 1;	// オーバーヒートでは死なない
				unit_heal(bl, -damage, 0, 0, 0);
			}
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_MAGNETICFIELD:		/* マグネティックフィールド */
		if((--sc->data[type].val2) > 0) {
			unit_heal(bl, 0, -50, 0, 0);
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_STEALTHFIELD_MASTER:	/* ステルスフィールド(使用者) */
		if(sd && !pc_isgear(sd))		// 魔導ギア非搭乗ならば止める
			break;
		else if((--sc->data[type].val2) > 0) {
			int damage = status_get_max_sp(bl) / 100;
			if(damage)
				unit_heal(bl, 0, -damage, 0, 0);
			timer = add_timer(tick+sc->data[type].val3, status_change_timer, bl->id, data);
		}
		break;
	case SC__REPRODUCE:		/* リプロデュース */
		if(sd) {
			int sp = 9 - (sc->data[type].val1 + 1) / 2;
			if(sp > 0 && sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		} else {
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC__SHADOWFORM:		/* シャドウフォーム */
		if((--sc->data[type].val4) > 0) {
			if(sd) {
				int sp = 11 - sc->data[type].val1;
				if(sp > 0 && sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer, bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC__INVISIBILITY:		/* インビジビリティ */
		if(sd) {
			int sp = sd->status.max_sp * 5 / 100;
			if(sp > 0 && sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_REFLECTDAMAGE:		/* リフレクトダメージ */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int sp = 20 + sc->data[type].val1 * 10;
				if(sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(10000+tick, status_change_timer,bl->id, data);
				}
			} else {
				timer = add_timer(10000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_FORCEOFVANGUARD:	/* フォースオブバンガード */
		if(sd) {
			int sp = 24 - sc->data[type].val1 * 4;
			if(sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(10000+tick, status_change_timer,bl->id, data);	
			}
		}
		break;
	case SC_BANDING:		/* バンディング */
		if(sd) {
			int sp = 7 - sc->data[type].val1;
			if(sd->status.sp >= sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				timer = add_timer(5000+tick, status_change_timer,bl->id, data);	
			}
		}
		break;
	case SC_INSPIRATION:	/* インスピレーション */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int hp = sd->status.max_hp / 100;
				int sp = sd->status.max_sp / 100;
				unit_heal(bl, -hp, -sp, 0, 0);
				if(sd->status.sp > 0 && !unit_isdead(bl) && sc->data[type].timer != -1) {
					// 生きていて解除済みでないなら継続
					timer = add_timer(6000+tick, status_change_timer,bl->id, data);
				}
			} else {
				timer = add_timer(6000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_KINGS_GRACE:	/* キングスグレイス */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int hp = sd->status.max_hp * sc->data[type].val4 / 100;
				unit_heal(bl, hp, 0, 0, 0);
			}
			timer = add_timer(1000+tick, status_change_timer,bl->id, data);
		}
		break;
	case SC_RAISINGDRAGON:		/* 潜龍昇天 */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int hp = sd->status.max_hp / 100;
				if(hp > 0 && sd->status.hp >= hp) {
					sd->status.hp -= hp;
					clif_updatestatus(sd,SP_HP);
					if(sd->status.max_hp * 15 / 100 < sd->status.hp) {
						timer = add_timer(5000+tick, status_change_timer, bl->id, data);
					}
				}
			} else {
				timer = add_timer(5000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_WINKCHARM:	/* 魅惑のウィンク */
	case SC_SIREN:		/* セイレーンの声 */
		if((--sc->data[type].val3) > 0) {
			clif_emotion(bl,3);
			timer = add_timer(3000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_DEEP_SLEEP:		/* 安らぎの子守唄 */
		if((--sc->data[type].val2) > 0) {
			int hp, sp = 0;
			hp = (int)((atn_bignumber)status_get_max_hp(bl) * 3 / 100);
			if(sd)
				sp = (int)((atn_bignumber)status_get_max_sp(bl) * 3 / 100);
			if(hp || sp)
				unit_heal(bl, hp, sp, 0, 0);
			timer = add_timer(2000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_SIRCLEOFNATURE:		/* 循環する自然の音 */
		if((--sc->data[type].val2) > 0) {
			int hp = 300 * sc->data[type].val1;
			if(sd) {
				int sp = 4 * sc->data[type].val1;
				if(sd && sd->status.sp >= sp) {
					unit_heal(bl, hp, -sp, 0, 0);
					timer = add_timer(1000+tick, status_change_timer,bl->id, data);	
				}
			} else {
				unit_heal(bl, hp, 0, 0, 0);
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);	
			}
		}
		break;
	case SC_MELODYOFSINK:		/* メロディーオブシンク */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				unit_heal(bl, 0, -(sd->status.max_sp * sc->data[type].val3 / 100), 0, 0);
			}
			timer = add_timer(1000+tick, status_change_timer,bl->id, data);	
		}
		break;
	case SC_SONG_OF_MANA:		/* マナの歌 */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int sp = 10 + 2 * sc->data[type].val4;
				if(sd->status.sp + sp > sd->status.max_sp) {
					sp = sd->status.max_sp - sd->status.sp;
					sd->status.sp = sd->status.max_sp;
				} else {
					sd->status.sp += sp;
				}
				clif_updatestatus(sd,SP_SP);
			}
			timer = add_timer(5000+tick, status_change_timer,bl->id, data);	
		}
		break;
	case SC_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
		if(--sc->data[type].val2 > 0) {
			int hp = 0,sp = 0;
			hp = (int)((atn_bignumber)status_get_max_hp(bl) / 100);
			if(sd)
				sp = (int)((atn_bignumber)status_get_max_sp(bl) / 100);
			unit_heal(bl, -hp, -sp, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1)
				timer = add_timer(sc->data[type].val3+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_FRIGG_SONG:			/* フリッグの歌 */
		if(--sc->data[type].val2 > 0) {
			unit_heal(bl, sc->data[type].val4, 0, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1)
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_DIAMONDDUST:		/* ダイヤモンドダスト */
		if(--sc->data[type].val2 > 0) {
			int hp = 0,sp = 0;
			hp = (int)((atn_bignumber)status_get_max_hp(bl) * 2 / 100);
			if(sd)
				sp = status_get_max_sp(bl) / 100;
			if(hp >= status_get_hp(bl))
				hp = status_get_hp(bl) - 1;
			unit_heal(bl, -hp, -sp, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1)
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_STRIKING:		/* ストライキング */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int sp = 6 - sc->data[type].val1;
				if(sp > 0 && sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer, bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_BLOOD_SUCKER:		/* ブラッドサッカー */
		if((--sc->data[type].val4) > 0) {
			struct block_list *src = map_id2bl(sc->data[type].val3);
			if(src && tid != -1) {
				skill_castend_damage_id(src,bl,sc->data[type].val2,sc->data[type].val1,gettick(),0);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_FIRE_EXPANSION_TEAR_GAS:		/* ファイアーエクスパンション(催涙) */
		if((--sc->data[type].val3) > 0) {
			int hp = (int)((atn_bignumber)status_get_max_hp(bl) / 100);
			clif_emotion(bl,28);
			// ファイアーエクスパンション(催涙)では死なないことにする（仮）
			if(hp >= status_get_hp(bl))
				hp = status_get_hp(bl) - 1;
			unit_heal(bl, -hp, 0, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1)
				timer = add_timer(3000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_MEIKYOUSISUI:		/* 明鏡止水 */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				int hp = (int)((atn_bignumber)status_get_max_hp(&sd->bl) * (sc->data[type].val1 * 2) / 100);
				int sp = (int)((atn_bignumber)status_get_max_sp(&sd->bl) * sc->data[type].val1 / 100);
				if(sd->status.max_hp >= sd->status.hp + hp) {
					sd->status.hp += hp;
					clif_updatestatus(sd,SP_HP);
				} else {
					sd->status.hp = sd->status.max_hp;
					clif_updatestatus(sd,SP_HP);
				}
				if(sd->status.max_sp >= sd->status.sp + sp) {
					sd->status.sp += sp;
					clif_updatestatus(sd,SP_SP);
				} else {
					sd->status.sp = sd->status.max_sp;
					clif_updatestatus(sd,SP_SP);
				}
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_IZAYOI:		/* 十六夜 */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				int sp = 1 * sc->data[type].val1;
				if(sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer, bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_KAGEMUSYA:	/* 幻術 -分身- */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				if(sd->status.sp >= 1) {
					sd->status.sp -= 1;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer,bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_C_MARKER:	/* クリムゾンマーカー */
		{
			struct map_session_data *tmpsd = map_id2sd(sc->data[type].val2);
			if((--sc->data[type].val4) > 0) {
				if(tmpsd && tmpsd->c_marker[sc->data[type].val3] == bl->id) {
					clif_crimson_marker(tmpsd, bl, false);
				}
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
			else if(sd) {
				sd->c_marker[sc->data[type].val3] = 0;
				clif_crimson_marker(sd, bl, true);
			}
		}
		break;
	case SC_FRESHSHRIMP:		/* 新鮮なエビ */
		if((--sc->data[type].val2) > 0) {
			unit_heal(bl, sc->data[type].val4, 0, 0, 1);
			timer = add_timer(sc->data[type].val3+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_HISS:				/* 警戒 */
		if((--sc->data[type].val4) > 0) {
			if(sc->data[type].val1 > 0)
				sc->data[type].val1--;
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_SV_ROOTTWIST:	/* マタタビの根っこ */
		if((--sc->data[type].val3) > 0) {
			struct block_list *src = map_id2bl(sc->data[type].val2);
			if(src && tid != -1) {
				battle_skill_attack(BF_MISC,src,src,bl,SU_SV_ROOTTWIST_ATK,sc->data[type].val1,tick,(0x0f<<20)|0x500);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_BURNT:			/* 獄炎呪 */
		if((--sc->data[type].val3) > 0) {
			int hp = 2000;
			// 獄炎呪では死なないことにする（仮）
			if(hp >= status_get_hp(bl))
				hp = status_get_hp(bl) - 1;
			unit_heal(bl, -hp, 0, 0, 0);
			if(!unit_isdead(bl) && sc->data[type].timer != -1)
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEM:	/* サモンエレメンタル */
		if((--sc->data[type].val2) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->status.sp >= sc->data[type].val3) {
					sd->status.sp -= sc->data[type].val3;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(10000+tick, status_change_timer, bl->id, data);
				}
			} else {
				timer = add_timer(10000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_WATER_SCREEN:	/* ウォータースクリーン */
		if((--sc->data[type].val2) > 0) {
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 3 / 100);
			if(heal)
				unit_heal(bl, heal, 0, 0, 1);
			timer = add_timer(5000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_CIRCLE_OF_FIRE_OPTION:	/* サークルオブファイア(精霊) */
	case SC_FIRE_CLOAK_OPTION:		/* ファイアークローク(精霊) */
	case SC_WATER_SCREEN_OPTION:	/* ウォータースクリーン(精霊) */
	case SC_WATER_DROP_OPTION:		/* ウォータードロップ(精霊) */
	case SC_WIND_STEP_OPTION:		/* ウィンドステップ(精霊) */
	case SC_WIND_CURTAIN_OPTION:	/* ウィンドカーテン(精霊) */
	case SC_SOLID_SKIN_OPTION:		/* ソリッドスキン(精霊) */
	case SC_STONE_SHIELD_OPTION:	/* ストーンシールド(精霊) */
		if((--sc->data[type].val2) > 0) {
			if(eld) {
				if(eld->status.sp >= sc->data[type].val3) {
					eld->status.sp -= sc->data[type].val3;
					clif_elemupdatestatus(eld->msd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer,bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_PYROTECHNIC_OPTION:	/* パイロテクニック(精霊) */
	case SC_AQUAPLAY_OPTION:	/* アクアプレイ(精霊) */
	case SC_GUST_OPTION:		/* ガスト(精霊) */
	case SC_PETROLOGY_OPTION:	/* ペトロジー(精霊) */
	case SC_HEATER_OPTION:		/* ヒーター(精霊) */
	case SC_COOLER_OPTION:		/* クーラー(精霊) */
	case SC_BLAST_OPTION:		/* ブラスト(精霊) */
	case SC_CURSED_SOIL_OPTION:	/* カースドソイル(精霊) */
	case SC_TROPIC_OPTION:		/* トロピック(精霊) */
	case SC_CHILLY_AIR_OPTION:	/* クールエアー(精霊) */
	case SC_WILD_STORM_OPTION:	/* ワイルドストーム(精霊) */
	case SC_UPHEAVAL_OPTION:	/* アップヘイバル(精霊) */
		if((--sc->data[type].val2) > 0) {
			if(eld) {
				if(eld->status.sp >= sc->data[type].val3) {
					eld->status.sp -= sc->data[type].val3;
					clif_elemupdatestatus(eld->msd,SP_SP);
					timer = add_timer(10000+tick, status_change_timer,bl->id, data);
				}
			} else {
				timer = add_timer(10000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_ANGRIFFS_MODUS:		/* アングリフスモドス */
		if((--sc->data[type].val2) > 0) {
			if(hd && hd->status.sp > 0) {
				if(hd->status.hp >= 100)
					hd->status.hp -= 100;
				if(hd->status.sp < 20)
					hd->status.sp = 0;
				else
					hd->status.sp -= 20;
				clif_send_homstatus(hd->msd,0);
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_CBC:				/* 絞め技 */
		if((--sc->data[type].val2) > 0) {
			int hp = 0, sp = 0;
			if(sc->data[type].val2 % 2) {	// 2秒毎
				hp = sc->data[type].val3;
			}
			if(sc->data[type].val2 % 3) {	// 3秒毎
				if(bl->type != BL_MOB)
					sp = sc->data[type].val4;
				else
					hp = sc->data[type].val4 * 10;
			}
			unit_heal(bl, -hp, -sp, 0, 0);
			timer = add_timer(1000+tick, status_change_timer,bl->id, data);
		}
		break;
	case SC_FULL_THROTTLE:		/* フルスロットル */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				int sp = (int)((atn_bignumber)status_get_max_sp(&sd->bl) * 5 / 100);
				if(sp > 0) {
					if(sd->status.sp >= sp) {
						sd->status.sp -= sp;
						clif_updatestatus(sd,SP_SP);
						timer = add_timer(1000+tick, status_change_timer, bl->id, data);
					}
					else if(sd->status.sp > 0) {
						sd->status.sp = 0;
						clif_updatestatus(sd,SP_SP);
						timer = add_timer(1000+tick, status_change_timer, bl->id, data);
					}
				}
			}
		}
		break;
	case SC_REBOUND:	/* リバウンド */
		clif_emotion(bl,4);
		if((--sc->data[type].val2) > 0) {
			timer = add_timer(2000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_GRADUAL_GRAVITY:	/* 重力増加 */
		if((--sc->data[type].val3) >= 0) {
			if(sd) {
				int hp = (int)((atn_bignumber)status_get_max_hp(&sd->bl) * sc->data[type].val2 / 100);
				unit_heal(bl, -hp, 0, 0, 0);
				if(!unit_isdead(bl) && sc->data[type].timer != -1) {
					// 生きていて解除済みでないなら継続
					timer = add_timer(1000+tick, status_change_timer, bl->id, data);
				}
			} else {
				timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_KILLING_AURA:	/* キリングオーラ */
		if((--sc->data[type].val3) > 0) {
			if(bl && tid != -1) {
				skill_castend_damage_id(bl,bl,NPC_KILLING_AURA,sc->data[type].val1,gettick(),0);
			}
			if(!unit_isdead(bl) && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(1000+tick, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_NEWMOON:	/* 朔月脚 */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				int sp = 1;
				if(sp > 0 && sd->status.sp >= sp) {
					sd->status.sp -= sp;
					clif_updatestatus(sd,SP_SP);
					timer = add_timer(1000+tick, status_change_timer,bl->id, data);
				}
			}
		}
		break;
	case SC_FLASHKICK:		/* 星の印 */
		{
			struct map_session_data *tsd = map_id2sd(sc->data[type].val2);
			if( tsd )
				tsd->stellar_mark[sc->data[type].val3] = 0;
		}
		break;
	case SC_SOULCOLLECT:		/* 魂の蓄積 */
		if(sd) {
			pc_addsoulenergy(sd,600000,1);
			timer = add_timer(tick+sc->data[type].val2, status_change_timer,bl->id, data);
		}
		break;
	case SC_SOULUNITY:		/* 魂の連結 */
		if((--sc->data[type].val3) > 0) {
			unit_heal(bl, sc->data[type].val2, 0, 0, 1);
			timer = add_timer(3000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_HELPANGEL:		/* 天使さま助けて */
		if((--sc->data[type].val2) > 0) {
			unit_heal(bl, 1000, 350, 0, 1);
			timer = add_timer(1000+tick, status_change_timer, bl->id, data);
		}
		break;
	case SC_HANDICAPSTATE_CONFLAGRATION:	/* 火災 */
		{
			int hp = (int)((atn_bignumber)status_get_max_hp(bl) * 15 / 100);
			unit_heal(bl,-hp,0,0,0);
			if(!unit_isdead(bl) && (--sc->data[type].val2) > 0 && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(tick+3000, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_HANDICAPSTATE_DEADLYPOISON:		/* 強毒 */
		{
			int hp = (int)((atn_bignumber)status_get_max_hp(bl) * 10 / 100);
			unit_heal(bl,-hp,0,0,0);
			if(!unit_isdead(bl) && (--sc->data[type].val3) > 0 && sc->data[type].timer != -1) {
				// 生きていて解除済みでないなら継続
				timer = add_timer(tick+1000, status_change_timer,bl->id, data);
			}
		}
		break;
	case SC_HANDICAPSTATE_DEPRESSION:		/* 憂鬱 */
		unit_heal(bl,0,-(status_get_max_sp(bl)/100),0,0);
		if((--sc->data[type].val2) > 0) {
			timer = add_timer(tick+3000, status_change_timer, bl->id, data);
		}
		break;
	case SC_SERVANTWEAPON:		/* サーヴァントウェポン */
		if((--sc->data[type].val4) > 0) {
			if(sd)
				pc_addball(sd,600000,1);
			timer = add_timer(tick+sc->data[type].val3, status_change_timer,bl->id, data);
		}
		break;
	case SC_DANCING_KNIFE:		/* ダンシングナイフ */
		if((--sc->data[type].val3) > 0) {
			skill_castend_damage_id(bl,bl,SHC_DANCING_KNIFE,sc->data[type].val1,tick,0);
			timer = add_timer(tick+sc->data[type].val2, status_change_timer,bl->id, data);
		}
		break;
	case SC_MEDIALE:		/* メディアリボトゥム */
		if((--sc->data[type].val4) > 0) {
			skill_castend_nodamage_id(bl,bl,CD_MEDIALE_VOTUM,sc->data[type].val1,tick,0x10|sc->data[type].val2);
			timer = add_timer(tick+sc->data[type].val3, status_change_timer,bl->id, data);
		}
		break;
	case SC_A_MACHINE:		/* 攻撃装置有効化 */
		if((--sc->data[type].val3) > 0) {
			skill_castend_damage_id(bl,bl,MT_A_MACHINE,sc->data[type].val1,tick,0);
			timer = add_timer(tick+sc->data[type].val2, status_change_timer,bl->id, data);
		}
		break;
	case SC_ABYSSFORCEWEAPON:		/* フロムジアビス */
		if((--sc->data[type].val4) > 0) {
			if(sd)
				pc_addball(sd,600000,1);
			timer = add_timer(tick+sc->data[type].val3, status_change_timer,bl->id, data);
		}
		break;
	case SC_SOUNDBLEND:			/* サウンドブレンド */
		if(sc->data[type].val2 != 0) {
			struct block_list *src = map_id2bl(sc->data[type].val2);
			if(src) {
				skill_castend_damage_id(src,bl,TR_SOUNDBLEND,sc->data[type].val1,tick,0);
			}
			sc->data[type].val2 = 0;
			timer = add_timer(tick+200, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEMENTAL_ARDOR:		/* サモンアルドール */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->eld->status.class_ != ELEMID_EM_ARDOR)
					break;
			}
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->eld->status.class_ != ELEMID_EM_DILUVIO)
					break;
			}
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->eld->status.class_ != ELEMID_EM_PROCELLA)
					break;
			}
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->eld->status.class_ != ELEMID_EM_TERREMOTUS)
					break;
			}
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	case SC_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
		if((--sc->data[type].val3) > 0) {
			if(sd) {
				// 召喚している精霊がいなければ終了
				if(!sd->eld)
					break;
				if(sd->eld->status.class_ != ELEMID_EM_SERPENS)
					break;
			}
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	case SC_FLAMETECHNIC_OPTION:		/* フレイムテクニック(精霊) */
	case SC_COLD_FORCE_OPTION:			/* コールドフォース(精霊) */
	case SC_GRACE_BREEZE_OPTION:		/* グレイスブリーズ(精霊) */
	case SC_EARTH_CARE_OPTION:			/* アースケア(精霊) */
	case SC_DEEP_POISONING_OPTION:		/* ディープポイズニング(精霊) */
		if((--sc->data[type].val2) > 0) {
			if(eld) {
				if(eld->status.sp >= sc->data[type].val3) {
					eld->status.sp -= sc->data[type].val3;
					clif_elemupdatestatus(eld->msd,SP_SP);
					timer = add_timer(tick+10000, status_change_timer,bl->id, data);
				} else {
					eld->status.sp = 0;
					clif_elemupdatestatus(eld->msd,SP_SP);
					elem_change_mode(eld,ELMODE_WAIT);
				}
			} else {
				timer = add_timer(tick+10000, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_FLAMEARMOR_OPTION:			/* フレイムアーマー(精霊) */
	case SC_CRYSTAL_ARMOR_OPTION:		/* クリスタルアーマー(精霊) */
	case SC_EYES_OF_STORM_OPTION:		/* アイズオブストーム(精霊) */
	case SC_STRONG_PROTECTION_OPTION:	/* ストロングプロテクション(精霊) */
	case SC_POISON_SHIELD_OPTION:		/* ポイズンシールド(精霊) */
		if((--sc->data[type].val2) > 0) {
			if(eld) {
				if(eld->status.sp >= sc->data[type].val3) {
					eld->status.sp -= sc->data[type].val3;
					clif_elemupdatestatus(eld->msd,SP_SP);
					timer = add_timer(tick+1000, status_change_timer,bl->id, data);
				} else {
					eld->status.sp = 0;
					clif_elemupdatestatus(eld->msd,SP_SP);
					elem_change_mode(eld,ELMODE_WAIT);
				}
			} else {
				timer = add_timer(tick+1000, status_change_timer, bl->id, data);
			}
		}
		break;
	case SC_INTENSIVE_AIM:			/* インテンシブエイム */
		if(sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
			if(sc->data[SC_INTENSIVE_AIM_COUNT].val1 < 10) {
				status_change_start(bl,SC_INTENSIVE_AIM_COUNT,sc->data[SC_INTENSIVE_AIM_COUNT].val1+1,0,0,0,0,0);
			}
		} else {
			status_change_start(bl,SC_INTENSIVE_AIM_COUNT,1,0,0,0,0,0);
		}
		timer = add_timer(tick+300, status_change_timer, bl->id, data);
		break;
	case SC_TALISMAN_OF_PROTECTION:		/* 守護符 */
		if((--sc->data[type].val3) > 0) {
			clif_misceffect_value(bl, 312, sc->data[type].val2);
			clif_misceffect_value(bl, 657, sc->data[type].val2);
			unit_heal(bl,sc->data[type].val2,0,0,1);
			timer = add_timer(tick+3000, status_change_timer, bl->id, data);
		}
		break;
	case SC_KI_SUL_RAMPAGE:		/* タートルランページ */
		if((--sc->data[type].val3) > 0) {
			skill_castend_nodamage_id(bl,bl,SH_KI_SUL_RAMPAGE,sc->data[type].val1,tick,0x10|sc->data[type].val2);
			timer = add_timer(tick+1000, status_change_timer, bl->id, data);
		}
		break;
	}

	if(timer == -1 && sd && sd->eternal_status_change[type] > 0 && !unit_isdead(&sd->bl))
	{
		timer = add_timer(	/* タイマー再設定 */
			sd->eternal_status_change[type]+tick, status_change_timer,
			bl->id, data);
	}

	map_freeblock_unlock();

	if(timer != -1) {
		// タイマーIDを保存して継続する
		sc->data[type].timer = timer;
		return 0;
	}

	return status_change_end(bl, type, tid);
}

/*==========================================
 * ステータス異常タイマー範囲処理
 *------------------------------------------
 */
int status_change_timer_sub(struct block_list *bl, va_list ap)
{
	struct block_list *src;
	struct status_change *sc;
	int type, skilllv;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, src = va_arg(ap,struct block_list*));

	type    = va_arg(ap,int);
	skilllv = va_arg(ap,int);
	tick    = va_arg(ap,unsigned int);

	if(!(bl->type & (BL_PC | BL_MOB | BL_MERC)))
		return 0;

	nullpo_retr(0, sc = status_get_sc(bl));

	switch( type ) {
	case SC_SIGHT:	/* サイト */
	case SC_CONCENTRATE:	/* 集中力向上 */
		skill_detect(bl);		// ディティクト効果
		break;
	case SC_RUWACH:	/* ルアフ */
		if(skill_detect(bl)) {		// ディテクト効果で暴いた相手に
			battle_skill_attack(BF_MAGIC,src,src,bl,AL_RUWACH,skilllv,tick,0);
		}
		break;
	case SC_SIGHTBLASTER:
		if(battle_check_target(src, bl, BCT_ENEMY) > 0 && !unit_isdead(bl)) {
			struct status_change *ssc;
			battle_skill_attack(BF_MAGIC,src,src,bl,WZ_SIGHTBLASTER,skilllv,tick,0);
			ssc = status_get_sc(src);
			if(ssc) {
				ssc->data[type].val2 = 0;
			}
			status_change_end(src,SC_SIGHTBLASTER,-1);
		}
		break;
	}
	return 0;
}

/*==========================================
 * ステータス異常全解除
 *------------------------------------------
 */
int status_change_clear(struct block_list *bl,int type)
{
	struct status_change *sc;
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

#ifdef DYNAMIC_SC_DATA
	if(sc->data == dummy_sc_data)
		return 0;
#endif

	if(sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);
	for(i = 0; i < MAX_STATUSCHANGE; i++) {
		if(i == SC_BABY && type == 0 && unit_isdead(bl))
			continue;

		/* 異常があるならタイマーを削除する */
		if(i == SC_DANCING) {
			skill_stop_dancing(bl,0);
		} else {
			if(i == SC_BASILICA)
				skill_basilica_cancel(bl);
			status_change_end(bl,i,-1);
		}
	}
	status_calc_pc_stop_end(bl);

	sc->opt1 = OPT1_NORMAL;
	sc->opt2 = OPT2_NORMAL;
	sc->opt3 = OPT3_NORMAL;
	sc->option &= OPTION_MASK;

	if(type != 1) {
		clif_changeoption(bl);
	}

	return 0;
}

/*==========================================
 * 特定条件下におけるステータス異常解除
 *------------------------------------------
 */
int status_change_release(struct block_list *bl,int mask)
{
	struct status_change *sc;
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

#ifdef DYNAMIC_SC_DATA
	if(sc->data == dummy_sc_data)
		return 0;
#endif

	if(sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);
	for(i = 0; i < MAX_STATUSCHANGE; i++) {
		// 異常があって且つフラグがあるならタイマーを削除
		if( (scdata_db[i].releasable & mask) && sc->data[i].timer != -1 ) {
			if(i == SC_DANCING) {
				skill_stop_dancing(bl,0);
			} else {
				if(i == SC_BASILICA)
					skill_basilica_cancel(bl);
				status_change_end(bl,i,-1);
			}
		}
	}
	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * ステータス異常(武器の属性)終了
 *------------------------------------------
 */
int status_enchant_elemental_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_ENCPOISON && sc->data[SC_ENCPOISON].timer != -1 )	/* エンチャントポイズン解除 */
		status_change_end(bl,SC_ENCPOISON,-1);
	if( type != SC_ASPERSIO && sc->data[SC_ASPERSIO].timer != -1 )	/* アスペルシオ解除 */
		status_change_end(bl,SC_ASPERSIO,-1);
	if( type != SC_FLAMELAUNCHER && sc->data[SC_FLAMELAUNCHER].timer != -1 )	/* フレイムランチャ解除 */
		status_change_end(bl,SC_FLAMELAUNCHER,-1);
	if( type != SC_FROSTWEAPON && sc->data[SC_FROSTWEAPON].timer != -1 )	/* フロストウェポン解除 */
		status_change_end(bl,SC_FROSTWEAPON,-1);
	if( type != SC_LIGHTNINGLOADER && sc->data[SC_LIGHTNINGLOADER].timer != -1 )	/* ライトニングローダー解除 */
		status_change_end(bl,SC_LIGHTNINGLOADER,-1);
	if( type != SC_SEISMICWEAPON && sc->data[SC_SEISMICWEAPON].timer != -1 )	/* サイスミックウェポン解除 */
		status_change_end(bl,SC_SEISMICWEAPON,-1);
	if( type != SC_DARKELEMENT && sc->data[SC_DARKELEMENT].timer != -1 )		// 闇
		status_change_end(bl,SC_DARKELEMENT,-1);
	if( type != SC_ATTENELEMENT && sc->data[SC_ATTENELEMENT].timer != -1 )	// 念
		status_change_end(bl,SC_ATTENELEMENT,-1);
	if( type != SC_UNDEADELEMENT && sc->data[SC_UNDEADELEMENT].timer != -1 )	// 不死
		status_change_end(bl,SC_UNDEADELEMENT,-1);
	if( type != SC_SEVENWIND && sc->data[SC_SEVENWIND].timer != -1 )		/* 暖かい風解除 */
		status_change_end(bl,SC_SEVENWIND,-1);

	return 0;
}

/*==========================================
 * ステータス異常(体の属性)終了
 *------------------------------------------
 */
int status_enchant_armor_elemental_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_BENEDICTIO && sc->data[SC_BENEDICTIO].timer != -1 )	// 聖体
		status_change_end(bl,SC_BENEDICTIO,-1);
	if( type != SC_ELEMENTWATER && sc->data[SC_ELEMENTWATER].timer != -1 )	// 水
		status_change_end(bl,SC_ELEMENTWATER,-1);
	if( type != SC_ELEMENTGROUND && sc->data[SC_ELEMENTGROUND].timer != -1 )	// 地
		status_change_end(bl,SC_ELEMENTGROUND,-1);
	if( type != SC_ELEMENTWIND && sc->data[SC_ELEMENTWIND].timer != -1 )		// 風
		status_change_end(bl,SC_ELEMENTWIND,-1);
	if( type != SC_ELEMENTFIRE && sc->data[SC_ELEMENTFIRE].timer != -1 )		// 火
		status_change_end(bl,SC_ELEMENTFIRE,-1);
	if( type != SC_ELEMENTHOLY && sc->data[SC_ELEMENTHOLY].timer != -1 )	// 光
		status_change_end(bl,SC_ELEMENTHOLY,-1);
	if( type != SC_ELEMENTDARK && sc->data[SC_ELEMENTDARK].timer != -1 )		// 闇
		status_change_end(bl,SC_ELEMENTDARK,-1);
	if( type != SC_ELEMENTELEKINESIS && sc->data[SC_ELEMENTELEKINESIS].timer != -1 )	// 念
		status_change_end(bl,SC_ELEMENTELEKINESIS,-1);
	if( type != SC_ELEMENTPOISON && sc->data[SC_ELEMENTPOISON].timer != -1 )	// 毒
		status_change_end(bl,SC_ELEMENTPOISON,-1);
	if( type != SC_ELEMENTUNDEAD && sc->data[SC_ELEMENTUNDEAD].timer != -1 )	// 不死
		status_change_end(bl,SC_ELEMENTUNDEAD,-1);

	return 0;
}

/*==========================================
 * ステータス異常(種族変更)終了
 *------------------------------------------
 */
int status_change_race_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_RACEUNDEAD && sc->data[SC_RACEUNDEAD].timer != -1 )
		status_change_end(bl,SC_RACEUNDEAD,-1);
	if( type != SC_RACEBEAST && sc->data[SC_RACEBEAST].timer != -1 )
		status_change_end(bl,SC_RACEBEAST,-1);
	if( type != SC_RACEPLANT && sc->data[SC_RACEPLANT].timer != -1 )
		status_change_end(bl,SC_RACEPLANT,-1);
	if( type != SC_RACEINSECT && sc->data[SC_RACEINSECT].timer != -1 )
		status_change_end(bl,SC_RACEINSECT,-1);
	if( type != SC_RACEFISH && sc->data[SC_RACEFISH].timer != -1 )
		status_change_end(bl,SC_RACEFISH,-1);
	if( type != SC_RACEDEVIL && sc->data[SC_RACEDEVIL].timer != -1 )
		status_change_end(bl,SC_RACEDEVIL,-1);
	if( type != SC_RACEHUMAN && sc->data[SC_RACEHUMAN].timer != -1 )
		status_change_end(bl,SC_RACEHUMAN,-1);
	if( type != SC_RACEANGEL && sc->data[SC_RACEANGEL].timer != -1 )
		status_change_end(bl,SC_RACEANGEL,-1);
	if( type != SC_RACEDRAGON && sc->data[SC_RACEDRAGON].timer != -1 )
		status_change_end(bl,SC_RACEDRAGON,-1);

	return 0;
}

/*==========================================
 * ステータス異常(種族変更)終了
 *------------------------------------------
 */
int status_change_resistclear(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	status_calc_pc_stop_begin(bl);

	if(sc->data[SC_RESISTWATER].timer != -1)
		status_change_end(bl,SC_RESISTWATER,-1);
	if(sc->data[SC_RESISTGROUND].timer != -1)
		status_change_end(bl,SC_RESISTGROUND,-1);
	if(sc->data[SC_RESISTFIRE].timer != -1)
		status_change_end(bl,SC_RESISTFIRE,-1);
	if(sc->data[SC_RESISTWIND].timer != -1)
		status_change_end(bl,SC_RESISTWIND,-1);
	if(sc->data[SC_RESISTPOISON].timer != -1)
		status_change_end(bl,SC_RESISTPOISON,-1);
	if(sc->data[SC_RESISTHOLY].timer != -1)
		status_change_end(bl,SC_RESISTHOLY,-1);
	if(sc->data[SC_RESISTDARK].timer != -1)
		status_change_end(bl,SC_RESISTDARK,-1);
	if(sc->data[SC_RESISTTELEKINESIS].timer != -1)
		status_change_end(bl,SC_RESISTTELEKINESIS,-1);
	if(sc->data[SC_RESISTUNDEAD].timer != -1)
		status_change_end(bl,SC_RESISTUNDEAD,-1);

	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * ステータス異常(魂)開始
 *------------------------------------------
 */
int status_change_soulstart(struct block_list *bl,int val1,int val2,int val3,int val4,int tick,int flag)
{
	int type = -1;
	struct map_session_data *sd;

	nullpo_retr(0, bl);

	if(bl->type != BL_PC || (sd = (struct map_session_data *)bl) == NULL)
		return 0;

	switch(sd->s_class.job) {
		case PC_JOB_MO:
		case PC_JOB_SR:
			type = SC_MONK;
			break;
		case PC_JOB_SG:
		case PC_JOB_SJ:
			type = SC_STAR;
			break;
		case PC_JOB_SA:
		case PC_JOB_SO:
			type = SC_SAGE;
		 	break;
		case PC_JOB_CR:
		case PC_JOB_LG:
			type = SC_CRUSADER;
			break;
		case PC_JOB_WZ:
		case PC_JOB_WL:
			type = SC_WIZARD;
			break;
		case PC_JOB_PR:
		case PC_JOB_AB:
			type = SC_PRIEST;
			break;
		case PC_JOB_RG:
		case PC_JOB_SC:
			type = SC_ROGUE;
			break;
		case PC_JOB_AS:
		case PC_JOB_GC:
			type = SC_ASSASIN;
			break;
		case PC_JOB_SL:
		case PC_JOB_SP:
			type = SC_SOULLINKER;
			break;
		case PC_JOB_KN:
		case PC_JOB_RK:
			type = SC_KNIGHT;
			break;
		case PC_JOB_AM:
		case PC_JOB_GN:
			type = SC_ALCHEMIST;
			break;
		case PC_JOB_BA:
		case PC_JOB_DC:
		case PC_JOB_MI:
		case PC_JOB_WA:
			type = SC_BARDDANCER;
			break;
		case PC_JOB_BS:
		case PC_JOB_NC:
			type = SC_BLACKSMITH;
			break;
		case PC_JOB_HT:
		case PC_JOB_RA:
			type = SC_HUNTER;
			break;
		case PC_JOB_SNV:
		case PC_JOB_ESNV:
			type = SC_SUPERNOVICE;
			break;
		case PC_JOB_GS:
			type = SC_GUNNER;
			break;
		case PC_JOB_NJ:
			type = SC_NINJA;
			break;
		case PC_JOB_DE:
			type = SC_DEATHKINGHT;
			break;
		case PC_JOB_DA:
			type = SC_COLLECTOR;
			break;
		default:
			if(sd->s_class.upper == PC_UPPER_HIGH && sd->s_class.job >= PC_JOB_SM && sd->s_class.job <= PC_JOB_TF)
				type = SC_HIGH;
			break;
	}
	if(type >= 0)
		status_change_start(bl,type,val1,val2,val3,val4,tick,flag);
	return 0;
}

/*==========================================
 * ステータス異常(魂)終了
 *------------------------------------------
 */
int status_change_soulclear(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(sc->data[SC_MONK].timer != -1)
		status_change_end(bl,SC_MONK,-1);
	if(sc->data[SC_STAR].timer != -1)
		status_change_end(bl,SC_STAR,-1);
	if(sc->data[SC_SAGE].timer != -1)
		status_change_end(bl,SC_SAGE,-1);
	if(sc->data[SC_CRUSADER].timer != -1)
		status_change_end(bl,SC_CRUSADER,-1);
	if(sc->data[SC_WIZARD].timer != -1)
		status_change_end(bl,SC_WIZARD,-1);
	if(sc->data[SC_PRIEST].timer != -1)
		status_change_end(bl,SC_PRIEST,-1);
	if(sc->data[SC_ROGUE].timer != -1)
		status_change_end(bl,SC_ROGUE,-1);
	if(sc->data[SC_ASSASIN].timer != -1)
		status_change_end(bl,SC_ASSASIN,-1);
	if(sc->data[SC_SOULLINKER].timer != -1)
		status_change_end(bl,SC_SOULLINKER,-1);
	if(sc->data[SC_KNIGHT].timer != -1)
		status_change_end(bl,SC_KNIGHT,-1);
	if(sc->data[SC_ALCHEMIST].timer != -1)
		status_change_end(bl,SC_ALCHEMIST,-1);
	if(sc->data[SC_BARDDANCER].timer != -1)
		status_change_end(bl,SC_BARDDANCER,-1);
	if(sc->data[SC_BLACKSMITH].timer != -1)
		status_change_end(bl,SC_BLACKSMITH,-1);
	if(sc->data[SC_HUNTER].timer != -1)
		status_change_end(bl,SC_HUNTER,-1);
	if(sc->data[SC_HIGH].timer != -1)
		status_change_end(bl,SC_HIGH,-1);
	if(sc->data[SC_SUPERNOVICE].timer != -1)
		status_change_end(bl,SC_SUPERNOVICE,-1);
	if(sc->data[SC_GUNNER].timer != -1)
		status_change_end(bl,SC_GUNNER,-1);
	if(sc->data[SC_NINJA].timer != -1)
		status_change_end(bl,SC_NINJA,-1);
	if(sc->data[SC_DEATHKINGHT].timer != -1)
		status_change_end(bl,SC_DEATHKINGHT,-1);
	if(sc->data[SC_COLLECTOR].timer != -1)
		status_change_end(bl,SC_COLLECTOR,-1);

	return 0;
}

/*==========================================
 * ステータス異常(精霊)終了
 *------------------------------------------
 */
int status_change_elemclear(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(sc->data[SC_CIRCLE_OF_FIRE].timer != -1)
		status_change_end(bl,SC_CIRCLE_OF_FIRE,-1);
	if(sc->data[SC_CIRCLE_OF_FIRE_OPTION].timer != -1)
		status_change_end(bl,SC_CIRCLE_OF_FIRE_OPTION,-1);
	if(sc->data[SC_FIRE_CLOAK].timer != -1)
		status_change_end(bl,SC_FIRE_CLOAK,-1);
	if(sc->data[SC_FIRE_CLOAK_OPTION].timer != -1)
		status_change_end(bl,SC_FIRE_CLOAK_OPTION,-1);
	if(sc->data[SC_WATER_SCREEN].timer != -1)
		status_change_end(bl,SC_WATER_SCREEN,-1);
	if(sc->data[SC_WATER_SCREEN_OPTION].timer != -1)
		status_change_end(bl,SC_WATER_SCREEN_OPTION,-1);
	if(sc->data[SC_WATER_DROP].timer != -1)
		status_change_end(bl,SC_WATER_DROP,-1);
	if(sc->data[SC_WATER_DROP_OPTION].timer != -1)
		status_change_end(bl,SC_WATER_DROP_OPTION,-1);
	//if(sc->data[SC_WATER_BARRIER].timer != -1)
	//	status_change_end(bl,SC_WATER_BARRIER,-1);
	if(sc->data[SC_WIND_STEP].timer != -1)
		status_change_end(bl,SC_WIND_STEP,-1);
	if(sc->data[SC_WIND_STEP_OPTION].timer != -1)
		status_change_end(bl,SC_WIND_STEP_OPTION,-1);
	if(sc->data[SC_WIND_CURTAIN].timer != -1)
		status_change_end(bl,SC_WIND_CURTAIN,-1);
	if(sc->data[SC_WIND_CURTAIN_OPTION].timer != -1)
		status_change_end(bl,SC_WIND_CURTAIN_OPTION,-1);
	//if(sc->data[SC_ZEPHYR].timer != -1)
	//	status_change_end(bl,SC_ZEPHYR,-1);
	if(sc->data[SC_SOLID_SKIN].timer != -1)
		status_change_end(bl,SC_SOLID_SKIN,-1);
	if(sc->data[SC_SOLID_SKIN_OPTION].timer != -1)
		status_change_end(bl,SC_SOLID_SKIN_OPTION,-1);
	if(sc->data[SC_STONE_SHIELD].timer != -1)
		status_change_end(bl,SC_STONE_SHIELD,-1);
	if(sc->data[SC_STONE_SHIELD_OPTION].timer != -1)
		status_change_end(bl,SC_STONE_SHIELD_OPTION,-1);
	//if(sc->data[SC_POWER_OF_GAIA].timer != -1)
	//	status_change_end(bl,SC_POWER_OF_GAIA,-1);
	if(sc->data[SC_PYROTECHNIC].timer != -1)
		status_change_end(bl,SC_PYROTECHNIC,-1);
	if(sc->data[SC_PYROTECHNIC_OPTION].timer != -1)
		status_change_end(bl,SC_PYROTECHNIC_OPTION,-1);
	if(sc->data[SC_HEATER].timer != -1)
		status_change_end(bl,SC_HEATER,-1);
	if(sc->data[SC_HEATER_OPTION].timer != -1)
		status_change_end(bl,SC_HEATER_OPTION,-1);
	if(sc->data[SC_TROPIC].timer != -1)
		status_change_end(bl,SC_TROPIC,-1);
	if(sc->data[SC_TROPIC_OPTION].timer != -1)
		status_change_end(bl,SC_TROPIC_OPTION,-1);
	if(sc->data[SC_AQUAPLAY].timer != -1)
		status_change_end(bl,SC_AQUAPLAY,-1);
	if(sc->data[SC_AQUAPLAY_OPTION].timer != -1)
		status_change_end(bl,SC_AQUAPLAY_OPTION,-1);
	if(sc->data[SC_COOLER].timer != -1)
		status_change_end(bl,SC_COOLER,-1);
	if(sc->data[SC_COOLER_OPTION].timer != -1)
		status_change_end(bl,SC_COOLER_OPTION,-1);
	if(sc->data[SC_CHILLY_AIR].timer != -1)
		status_change_end(bl,SC_CHILLY_AIR,-1);
	if(sc->data[SC_CHILLY_AIR_OPTION].timer != -1)
		status_change_end(bl,SC_CHILLY_AIR_OPTION,-1);
	if(sc->data[SC_GUST].timer != -1)
		status_change_end(bl,SC_GUST,-1);
	if(sc->data[SC_GUST_OPTION].timer != -1)
		status_change_end(bl,SC_GUST_OPTION,-1);
	if(sc->data[SC_BLAST].timer != -1)
		status_change_end(bl,SC_BLAST,-1);
	if(sc->data[SC_BLAST_OPTION].timer != -1)
		status_change_end(bl,SC_BLAST_OPTION,-1);
	if(sc->data[SC_WILD_STORM].timer != -1)
		status_change_end(bl,SC_WILD_STORM,-1);
	if(sc->data[SC_WILD_STORM_OPTION].timer != -1)
		status_change_end(bl,SC_WILD_STORM_OPTION,-1);
	if(sc->data[SC_PETROLOGY].timer != -1)
		status_change_end(bl,SC_PETROLOGY,-1);
	if(sc->data[SC_PETROLOGY_OPTION].timer != -1)
		status_change_end(bl,SC_PETROLOGY_OPTION,-1);
	if(sc->data[SC_CURSED_SOIL].timer != -1)
		status_change_end(bl,SC_CURSED_SOIL,-1);
	if(sc->data[SC_CURSED_SOIL_OPTION].timer != -1)
		status_change_end(bl,SC_CURSED_SOIL_OPTION,-1);
	if(sc->data[SC_UPHEAVAL].timer != -1)
		status_change_end(bl,SC_UPHEAVAL,-1);
	if(sc->data[SC_UPHEAVAL_OPTION].timer != -1)
		status_change_end(bl,SC_UPHEAVAL_OPTION,-1);
	if(sc->data[SC_TIDAL_WEAPON].timer != -1)
		status_change_end(bl,SC_TIDAL_WEAPON,-1);
	if(sc->data[SC_TIDAL_WEAPON_OPTION].timer != -1)
		status_change_end(bl,SC_TIDAL_WEAPON_OPTION,-1);
	//if(sc->data[SC_ROCK_CRUSHER].timer != -1)
	//	status_change_end(bl,SC_ROCK_CRUSHER,-1);
	//if(sc->data[SC_ROCK_CRUSHER_ATK].timer != -1)
	//	status_change_end(bl,SC_ROCK_CRUSHER_ATK,-1);
	if(sc->data[SC_FLAMETECHNIC].timer != -1)
		status_change_end(bl,SC_FLAMETECHNIC,-1);
	if(sc->data[SC_FLAMETECHNIC_OPTION].timer != -1)
		status_change_end(bl,SC_FLAMETECHNIC_OPTION,-1);
	if(sc->data[SC_FLAMEARMOR].timer != -1)
		status_change_end(bl,SC_FLAMEARMOR,-1);
	if(sc->data[SC_FLAMEARMOR_OPTION].timer != -1)
		status_change_end(bl,SC_FLAMEARMOR_OPTION,-1);
	if(sc->data[SC_COLD_FORCE].timer != -1)
		status_change_end(bl,SC_COLD_FORCE,-1);
	if(sc->data[SC_COLD_FORCE_OPTION].timer != -1)
		status_change_end(bl,SC_COLD_FORCE_OPTION,-1);
	if(sc->data[SC_CRYSTAL_ARMOR].timer != -1)
		status_change_end(bl,SC_CRYSTAL_ARMOR,-1);
	if(sc->data[SC_CRYSTAL_ARMOR_OPTION].timer != -1)
		status_change_end(bl,SC_CRYSTAL_ARMOR_OPTION,-1);
	if(sc->data[SC_GRACE_BREEZE].timer != -1)
		status_change_end(bl,SC_GRACE_BREEZE,-1);
	if(sc->data[SC_GRACE_BREEZE_OPTION].timer != -1)
		status_change_end(bl,SC_GRACE_BREEZE_OPTION,-1);
	if(sc->data[SC_EYES_OF_STORM].timer != -1)
		status_change_end(bl,SC_EYES_OF_STORM,-1);
	if(sc->data[SC_EYES_OF_STORM_OPTION].timer != -1)
		status_change_end(bl,SC_EYES_OF_STORM_OPTION,-1);
	if(sc->data[SC_EARTH_CARE].timer != -1)
		status_change_end(bl,SC_EARTH_CARE,-1);
	if(sc->data[SC_EARTH_CARE_OPTION].timer != -1)
		status_change_end(bl,SC_EARTH_CARE_OPTION,-1);
	if(sc->data[SC_STRONG_PROTECTION].timer != -1)
		status_change_end(bl,SC_STRONG_PROTECTION,-1);
	if(sc->data[SC_STRONG_PROTECTION_OPTION].timer != -1)
		status_change_end(bl,SC_STRONG_PROTECTION_OPTION,-1);
	if(sc->data[SC_DEEP_POISONING].timer != -1)
		status_change_end(bl,SC_DEEP_POISONING,-1);
	if(sc->data[SC_DEEP_POISONING_OPTION].timer != -1)
		status_change_end(bl,SC_DEEP_POISONING_OPTION,-1);
	if(sc->data[SC_POISON_SHIELD].timer != -1)
		status_change_end(bl,SC_POISON_SHIELD,-1);
	if(sc->data[SC_POISON_SHIELD_OPTION].timer != -1)
		status_change_end(bl,SC_POISON_SHIELD_OPTION,-1);

	return 0;
}

/*==========================================
 * ステータス異常(凍結・石化・睡眠)終了
 *------------------------------------------
 */
int status_change_attacked_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(sc->data[SC_FREEZE].timer != -1)
		status_change_end(bl,SC_FREEZE,-1);
	if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0)
		status_change_end(bl,SC_STONE,-1);
	if(sc->data[SC_SLEEP].timer != -1)
		status_change_end(bl,SC_SLEEP,-1);
	if(sc->data[SC_WINKCHARM].timer != -1)
		status_change_end(bl,SC_WINKCHARM,-1);
	if(sc->data[SC_DEEP_SLEEP].timer != -1)
		status_change_end(bl,SC_DEEP_SLEEP,-1);
	if(sc->data[SC_SIREN].timer != -1)
		status_change_end(bl,SC_SIREN,-1);
	if(sc->data[SC_HANDICAPSTATE_FROSTBITE].timer != -1)
		status_change_end(bl,SC_HANDICAPSTATE_FROSTBITE,-1);
	if(sc->data[SC_HANDICAPSTATE_SWOONING].timer != -1)
		status_change_end(bl,SC_HANDICAPSTATE_SWOONING,-1);
	if(sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1)
		status_change_end(bl,SC_HANDICAPSTATE_LIGHTNINGSTRIKE,-1);
	if(sc->data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1)
		status_change_end(bl,SC_HANDICAPSTATE_CRYSTALLIZATION,-1);

	return 0;
}

/*==========================================
 * ステータス異常(ハイド)終了
 *------------------------------------------
 */
int status_change_hidden_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);

	if(sc) {
		if(sc->option > 0) {
			if(sc->option & OPTION_HIDE)
				status_change_end(bl,SC_HIDING,-1);
			if((sc->option & (OPTION_CLOAKING | OPTION_FOOTPRINT)) == OPTION_CLOAKING)
				status_change_end(bl,SC_CLOAKING,-1);
			if((sc->option & (OPTION_CLOAKING | OPTION_FOOTPRINT)) == (OPTION_CLOAKING | OPTION_FOOTPRINT))
				status_change_end(bl,SC_CHASEWALK,-1);
		}
	 	if(sc->data[SC_CAMOUFLAGE].timer != -1)
			status_change_end(bl,SC_CAMOUFLAGE,-1);
	 	if(sc->data[SC_STEALTHFIELD].timer != -1)
			status_change_end(bl,SC_STEALTHFIELD,-1);
	 	if(sc->data[SC_SUHIDE].timer != -1)
			status_change_end(bl,SC_SUHIDE,-1);
	 	if(sc->data[SC_NEWMOON].timer != -1)
			status_change_end(bl,SC_NEWMOON,-1);
	}
	return 0;
}

/*==========================================
 * ステータス異常(マップ離脱時)終了
 *------------------------------------------
 */
int status_change_removemap_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(sc == NULL || sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);

	if(sc->data[SC_BLADESTOP].timer != -1)
		status_change_end(bl, SC_BLADESTOP, -1);
	if(sc->data[SC_GRAFFITI].timer != -1)
		status_change_end(bl, SC_GRAFFITI, -1);
	if(sc->data[SC_ANKLE].timer != -1)
		status_change_end(bl, SC_ANKLE, -1);
	if(sc->data[SC_GOSPEL].timer != -1)
		status_change_end(bl, SC_GOSPEL, -1);
	if(sc->data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(bl, SC_GRAVITATION_USER, -1);
	if(sc->data[SC_TRICKDEAD].timer != -1)
		status_change_end(bl, SC_TRICKDEAD, -1);
	if(sc->data[SC_RUN].timer != -1)
		status_change_end(bl, SC_RUN, -1);
	if(sc->data[SC_MARIONETTE].timer != -1)
		status_change_end(bl, SC_MARIONETTE, -1);
	if(sc->data[SC_MARIONETTE2].timer != -1)
		status_change_end(bl, SC_MARIONETTE2, -1);
	if(sc->data[SC_BASILICA].timer != -1) {
		skill_basilica_cancel(bl);
		status_change_end(bl, SC_BASILICA, -1);
	}
	if(sc->data[SC_WUGDASH].timer != -1)
		status_change_end(bl, SC_WUGDASH, -1);

	if(battle_config.homun_statuschange_reset) {
		if(sc->data[SC_AVOID].timer != -1)
			status_change_end(bl, SC_AVOID, -1);
		if(sc->data[SC_CHANGE].timer != -1)
			status_change_end(bl, SC_CHANGE, -1);
		if(sc->data[SC_DEFENCE].timer != -1)
			status_change_end(bl, SC_DEFENCE, -1);
		if(sc->data[SC_BLOODLUST].timer != -1)
			status_change_end(bl, SC_BLOODLUST, -1);
		if(sc->data[SC_FLEET].timer != -1)
			status_change_end(bl, SC_FLEET, -1);
		if(sc->data[SC_SPEED].timer != -1)
			status_change_end(bl, SC_SPEED, -1);
	}
	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * アイテムによるステータス異常開始
 *------------------------------------------
 */
int status_change_addeff_start(struct block_list *src, struct block_list *bl, int id, int rate, int type, unsigned int tick)
{
	struct map_session_data *sd = NULL;

	static const int sc2[] = {
		MG_STONECURSE,MG_FROSTDIVER,NPC_STUNATTACK,
		NPC_SLEEPATTACK,TF_POISON,NPC_CURSEATTACK,
		NPC_SILENCEATTACK,0,NPC_BLINDATTACK,LK_HEADCRUSH,
		NPC_WIDEHEALTHFEAR,NPC_WIDEBODYBURNNING,NPC_WIDE_DEEP_SLEEP,
		NPC_WIDEFROSTMISTY,NPC_WIDECOLD,NPC_WIDESIREN
	};
	static const int sc_id[] = {
		SC_STONE,SC_FREEZE,SC_STUN,
		SC_SLEEP,SC_POISON,SC_CURSE,
		SC_SILENCE,SC_CONFUSION,SC_BLIND,SC_BLEED,
		SC_FEAR,SC_HELLINFERNO,SC_DEEP_SLEEP,
		SC_FROSTMISTY,SC_DIAMONDDUST,SC_SIREN
	};

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if(src->type != BL_PC || !(bl->type & BL_CHAR))
		return 0;

	sd = (struct map_session_data *)src;

	if(atn_rand() % 10000 < status_change_rate(bl,sc_id[id],rate,sd->status.base_level)) {

		if(battle_config.battle_log) {
			if(type==1)
				printf("PC %d skill_skilladdeff: cardによる状態異常発動 %d %d %d\n",sd->bl.id,sd->skill_addeff.id[id],id,rate);
			else if(type==2)
				printf("PC %d skill_addeff: cardによる状態異常発動 %d %d\n",sd->bl.id,id,rate);
			else if(type==3)
				printf("PC %d skill_addeff2: cardによる状態異常発動 %d %d\n",sd->bl.id,id,rate);
			else if(type==4)
				printf("PC %d magic_addeff: cardによる状態異常発動 %d %d\n",sd->bl.id,id,rate);
			else
				printf("PC %d skill_addreveff: cardによる異常発動 %d %d\n",sd->bl.id,id,sd->addreveff[id]);
		}

		switch(sc_id[id]) {
			case SC_STONE:
			case SC_FREEZE:
			case SC_STUN:
			case SC_SLEEP:
			case SC_POISON:
			case SC_CURSE:
			case SC_SILENCE:
			case SC_CONFUSION:
			case SC_BLIND:
			case SC_BLEED:
				if(type)
					status_change_pretimer(bl,sc_id[id],7,0,0,0,((sc_id[id] == SC_CONFUSION)? 10000+7000: skill_get_time2(sc2[id],7)),0,tick+status_get_amotion(src)+500);
				else
					status_change_start(bl,sc_id[id],7,0,0,0,((sc_id[id] == SC_CONFUSION)? 10000+7000: skill_get_time2(sc2[id],7)),0);
				break;
			case SC_FEAR:
				if(type)
					status_change_pretimer(bl,sc_id[id],1,0,0,0,skill_get_time2(sc2[id],1),0,tick+status_get_amotion(src)+500);
				else
					status_change_start(bl,sc_id[id],1,0,0,0,skill_get_time2(sc2[id],1),0);
				break;
			case SC_FROSTMISTY:
			case SC_HELLINFERNO:
				if(type)
					status_change_pretimer(bl,sc_id[id],1,0,0,0,10000+skill_get_time2(sc2[id],1),0,tick+status_get_amotion(src)+500);
				else
					status_change_start(bl,sc_id[id],1,0,0,0,10000+skill_get_time2(sc2[id],1),0);
				break;
			case SC_DEEP_SLEEP:
			case SC_DIAMONDDUST:
				if(type)
					status_change_pretimer(bl,sc_id[id],1,0,0,0,3000+skill_get_time2(sc2[id],1),0,tick+status_get_amotion(src)+500);
				else
					status_change_start(bl,sc_id[id],1,0,0,0,3000+skill_get_time2(sc2[id],1),0);
				break;
			case SC_SIREN:
				if(type)
					status_change_pretimer(bl,sc_id[id],1,src->id,0,0,skill_get_time2(sc2[id],1),0,tick+status_get_amotion(src)+500);
				else
					status_change_start(bl,sc_id[id],1,src->id,0,0,skill_get_time2(sc2[id],1),0);
				break;
		}
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void status_split_atoi(char *str, int *num1, int *num2)
{
	int i, val[2];

	for (i=0; i<2; i++) {
		if(str) {
			val[i] = atoi(str);
			str = strchr(str,':');
			if (str)
				*str++=0;
		} else {
			val[i] = 0;
		}
	}
	if(val[0])
		*num1 = val[0];
	if(val[1])
		*num2 = val[1];
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int status_split_atoi2(char *str,int *val,int num)
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
 * データベース読み込み
 *------------------------------------------
 */
int status_readdb(void)
{
	int i,j,k,m;
	FILE *fp;
	char line[1024],*p;
#ifdef PRE_RENEWAL
	const char *filename[] = {
		"db/job_db1.txt", "db/pre/job_db1_pre.txt", "db/addon/job_db1_add.txt"
	};
	const int max = 3;
#else
	const char *filename[] = {
		"db/job_db1.txt", "db/addon/job_db1_add.txt"
	};
	const int max = 2;
#endif
	const char *filename2;

	memset(&job_db, 0, sizeof(job_db));

	// JOB補正数値1
	for(m = 0; m < max; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > 0)
				continue;
			printf("status_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}

		while(fgets(line,1020,fp)){
			char *split[10+WT_MAX];
			int hp_coefficient, sp_coefficient;
			int hp_coefficient2, sigma;

			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			memset(split,0,sizeof(split));
			for(j=0,p=line;j<9+WT_MAX && p;j++){
				split[j]=p;
				p=strchr(p,',');
				if(p) *p++=0;
			}
			if(j < 9)
				continue;

			i = atoi(split[0]);
			if(i < 0 || i >= PC_JOB_MAX)
				continue;

			status_split_atoi2(split[1],job_db[i].max_joblv,PC_UPPER_MAX);
			status_split_atoi2(split[2],job_db[i].base_exp_table,PC_UPPER_MAX);
			status_split_atoi2(split[3],job_db[i].job_exp_table,PC_UPPER_MAX);
			job_db[i].max_weight_base = atoi(split[4]);
			if((hp_coefficient = atoi(split[5])) < 0)
				hp_coefficient = 0;
			if((hp_coefficient2 = atoi(split[6])) < 0)
				hp_coefficient2 = 500;
			sigma = 0;
			for(j = 1; j <= MAX_LEVEL; j++) {
				// 基本HP = 35 + BaseLevel * Job倍率 + Jobボーナス
				job_db[i].hp_base[j-1] = (3500 + j * hp_coefficient2 + sigma) / 100;
				sigma += hp_coefficient * (j + 1) + 50;
				sigma -= sigma % 100;
			}

			if((sp_coefficient = atoi(split[7])) < 0)
				sp_coefficient = 100;
			for(j = 1; j <= MAX_LEVEL; j++) {
				// 基本SP = 10 + BaseLevel * Job係数
				job_db[i].sp_base[j-1] = (1000 + j * sp_coefficient) / 100;
			}

			job_db[i].max_ap = atoi(split[8]);

			for(j=0; j<=WT_MAX && split[9+j]; j++) {
				job_db[i].aspd_base[j] = atoi(split[9+j]);
			}
		}
		fclose(fp);
		printf("read %s done\n", filename[m]);
	}

	// 基本HP個別設定
	filename2 = "db/job_hp_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<PC_JOB_MAX && p;j++){
			if(sscanf(p,"%d",&k) == 0)
				break;
			if(k > 0) {
				job_db[j].hp_base[i] = k;
			}
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(++i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// 基本SP個別設定
	filename2 = "db/job_sp_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<PC_JOB_MAX && p;j++){
			if(sscanf(p,"%d",&k) == 0)
				break;
			if(k > 0) {
				job_db[j].sp_base[i] = k;
			}
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(++i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// JOBボーナス
	filename2 = "db/job_db2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_LEVEL && p;j++){
			if(sscanf(p,"%d",&k)==0)
				break;
			job_db[i].bonus[PC_UPPER_NORMAL][j] = k;
			job_db[i].bonus[PC_UPPER_BABY][j] = k;
			p=strchr(p,',');
			if(p) p++;
		}
		if(++i >= PC_JOB_MAX)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// JOBボーナス2 転生職用
	filename2 = "db/job_db2-2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_LEVEL && p;j++){
			if(sscanf(p,"%d",&k)==0)
				break;
			job_db[i].bonus[PC_UPPER_HIGH][j] = k;
			p=strchr(p,',');
			if(p) p++;
		}
		if(++i >= PC_JOB_MAX)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// 精錬データテーブル
	for(i=0; i<MAX_WEAPON_LEVEL+1; i++) {
		for(j=0; j<MAX_REFINE; j++)
			refine_db[i].safety_bonus[j] = 0;
		refine_db[i].over_bonus   = 0;
		refine_db[i].limit        = MAX_REFINE;
		for(j=0; j<MAX_REFINE; j++)
			refine_db[i].per[j] = 0;
	}

#ifdef PRE_RENEWAL
	filename2 = "db/pre/refine_db_pre.txt";
#else
	filename2 = "db/refine_db.txt";
#endif
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[MAX_REFINE+3];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(atoi(line) <= 0)
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<MAX_REFINE+3 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		for(j=0; j<MAX_REFINE; j++) {
			refine_db[i].safety_bonus[j] = atoi(split[0]) * (j+1);	// 精錬ボーナス
		}
		refine_db[i].over_bonus   = atoi(split[1]);	// 過剰精錬ボーナス
		refine_db[i].limit        = atoi(split[2]);	// 安全精錬限界
		for(j=0; j<MAX_REFINE && split[j+3]; j++) {
			status_split_atoi(split[j+3], &refine_db[i].per[j], &refine_db[i].safety_bonus[j]);
		}
		if(++i > MAX_WEAPON_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// サイズ補正テーブル
	for(i=0; i<MAX_SIZE_FIX; i++) {
		for(j=0; j<WT_MAX; j++)
			atkmods[i][j] = 100;
	}

	filename2 = "db/size_fix.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[WT_MAX];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(atoi(line) <= 0)
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<WT_MAX && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		for(j=0; j<WT_MAX && split[j]; j++) {
			atkmods[i][j] = atoi(split[j]);
		}
		if(++i > MAX_SIZE_FIX)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename2);

	// ステータス異常テーブル
	memset(&scdata_db, 0, sizeof(scdata_db));
	filename2 = "db/scdata_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("status_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[6];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<6 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		j = atoi(split[0]);
		if(j < 0 || j >= MAX_STATUSCHANGE)
			continue;
		scdata_db[j].save       = (short)atoi(split[2]);
		scdata_db[j].releasable = atoi(split[3]);
		scdata_db[j].disable    = atoi(split[4]);
		scdata_db[j].copyable   = atoi(split[5]);
		i++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, i);

#ifdef DYNAMIC_SC_DATA
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		dummy_sc_data[i].timer = -1;
		dummy_sc_data[i].val1  = 0;
		dummy_sc_data[i].val2  = 0;
		dummy_sc_data[i].val3  = 0;
		dummy_sc_data[i].val4  = 0;
	}
	printf("status_readdb: enable dynamic sc_data.\n");
#endif

	return 0;
}

/*==========================================
 * スキル関係初期化処理
 *------------------------------------------
 */
int do_init_status(void)
{
	status_readdb();
	status_change_handlers_init();

	add_timer_func_list(status_change_timer);
	add_timer_func_list(status_pretimer_timer);

	return 0;
}
