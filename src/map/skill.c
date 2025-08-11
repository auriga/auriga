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

/* �X�L���ԍ������X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable[MAX_SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - SECOND_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable2[MAX_SECONDSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
	/* 1001- */
	-1,SC_SHRINK,-1,-1,SC_CLOSECONFINE,SC_SIGHTBLASTER,-1,SC_ELEMENTWATER,-1,-1,
	/* 1011- */
	SC_WINKCHARM,-1,-1,-1,-1,-1,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,
};

/* (�X�L���ԍ� - THIRD1_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable3_1[MAX_THIRD1SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - THIRD2_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable3_2[MAX_THIRD2SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - THIRD3_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable3_3[MAX_THIRD3SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - THIRD4_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable3_4[MAX_THIRD4SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - FOURTH1_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable4_1[MAX_FOURTH1SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - FOURTH2_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int SkillStatusChangeTable4_2[MAX_FOURTH2SKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
	/* 6001- */
	-1,-1,-1,-1,-1,-1,
};

/* (�X�L���ԍ� - HOM_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int HomSkillStatusChangeTable[MAX_HOMSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - MERC_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int MercSkillStatusChangeTable[MAX_MERCSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - ELEM_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int ElemSkillStatusChangeTable[MAX_ELEMSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
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

/* (�X�L���ԍ� - ABR_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int AbrSkillStatusChangeTable[MAX_ABRSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
	/* 8601- */
	-1,-1,-1,-1,-1,
};

/* (�X�L���ԍ� - GUILD_SKILLID)�����X�e�[�^�X�ُ�ԍ��ϊ��e�[�u�� */
int GuildSkillStatusChangeTable[MAX_GUILDSKILL] = {	/* status.h��enum��SC_***�Ƃ��킹�邱�� */
	/* 10000- */
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	/* 10010- */
	SC_BATTLEORDER,SC_REGENERATION,-1,-1,-1,-1,-1,-1,-1,-1,
};

/* �X�L���f�[�^�x�[�X */
struct skill_db skill_db[MAX_SKILL_DB];

/* �A�C�e���쐬�f�[�^�x�[�X */
struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

/* ��쐬�X�L���f�[�^�x�[�X */
struct skill_arrow_db skill_arrow_db[MAX_SKILL_ARROW_DB];

/* �A�u���J�_�u�������X�L���f�[�^�x�[�X */
struct skill_abra_db skill_abra_db[MAX_SKILL_ABRA_DB];

/* �����_�������X�L���f�[�^ */
struct skill_rand_db skill_rand_db[MAX_SKILL_RAND_DB];

/* �`�F���W�}�e���A�������f�[�^�x�[�X */
struct skill_material_db skill_material_db[MAX_SKILL_PRODUCE_DB];

/* �v���g�^�C�v */
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
static int skill_flicker(struct block_list *bl, va_list ap);
static int skill_shimiru(struct block_list *bl,va_list ap);
static int skill_shinkirou(struct block_list *bl,va_list ap);
static int skill_fuumakouchiku(struct block_list *bl, va_list ap);
static int skill_kunaikussetsu(struct block_list *bl,va_list ap);

/* �X�L�����j�b�g�̔z�u����Ԃ� */
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

/* �␳�ςݎ˒���Ԃ� */
int skill_get_fixed_range(struct block_list *bl,int id,int lv)
{
	int range;

	nullpo_retr(0, bl);

	range = skill_get_range(id,lv);
	if(range < 0)
		range = status_get_range(bl) - (range + 1);

	// �X�L�����̎˒���������
	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			int skill;
			switch(id) {
				case RA_ARROWSTORM:			/* �A���[�X�g�[�� */
				case RA_AIMEDBOLT:			/* �G�C���h�{���g */
				case WH_HAWKRUSH:			/* �z�[�N���b�V�� */
				case WH_HAWKBOOMERANG:		/* �z�[�N�u�[������ */
				case WH_GALESTORM:			/* �Q�C���X�g�[�� */
				case WH_CRESCIVE_BOLT:		/* �N���b�V�u�{���g */
				case TR_RHYTHMSHOOTING:		/* ���Y���V���[�e�B���O */
					if((skill = pc_checkskill(sd,AC_VULTURE)) > 0)	// ���V�̖�
						range += skill;
					break;
				case GS_TRACKING:			/* �g���b�L���O */
				case GS_PIERCINGSHOT:		/* �s�A�[�V���O�V���b�g */
				case GS_RAPIDSHOWER:		/* ���s�b�h�V�����[ */
				case GS_FULLBUSTER:			/* �t���o�X�^�[ */
				case GS_SPREADATTACK:		/* �X�v���b�h�A�^�b�N */
				case GS_GROUNDDRIFT:		/* �O���E���h�h���t�g */
					if((skill = pc_checkskill(sd,GS_SNAKEEYE)) > 0)	// �X�l�[�N�A�C
						range += skill;
					break;
				case NJ_KIRIKAGE:			/* �e�a�� */
					if((skill = pc_checkskill(sd,NJ_SHADOWJUMP)) > 0)	// �e����
						range = skill_get_range(NJ_SHADOWJUMP,skill);	// �e���т̏K�����x���Ŏ˒����ϓ�
					break;
				case HT_LANDMINE:			/* �����h�}�C�� */
				case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
				case HT_BLASTMINE:			/* �u���X�g�}�C�� */
				case HT_CLAYMORETRAP:		/* �N���C���A�g���b�v */
				case RA_CLUSTERBOMB:		/* �N���X�^�[�{�� */
				case RA_FIRINGTRAP:			/* �t�@�C�A�����O�g���b�v */
				case RA_ICEBOUNDTRAP:		/* �A�C�X�o�E���h�g���b�v */
				case WH_DEEPBLINDTRAP:		/* �f�B�[�v�u���C���h�g���b�v */
				case WH_SOLIDTRAP:			/* �\���b�h�g���b�v */
				case WH_SWIFTTRAP:			/* �X�C�t�g�g���b�v */
				case WH_FLAMETRAP:			/* �t���C���g���b�v */
					if((skill = pc_checkskill(sd,RA_RESEARCHTRAP)) > 0)	// �g���b�v���� 
						range += (skill + 1) / 2;
					break;
				case WL_WHITEIMPRISON:		/* �z���C�g�C���v���Y�� */
				case WL_SOULEXPANSION:		/* �\�E���G�N�X�p���V���� */
				case WL_MARSHOFABYSS:		/* �}�[�V���I�u�A�r�X */
				case WL_SIENNAEXECRATE:		/* �V�G�i�G�N�Z�N���C�g */
				case WL_DRAINLIFE:			/* �h���C�����C�t */
				case WL_CRIMSONROCK:		/* �N�����]�����b�N */
				case WL_HELLINFERNO:		/* �w���C���t�F���m */
				case WL_COMET:				/* �R���b�g */
				case WL_CHAINLIGHTNING:		/* �`�F�[�����C�g�j���O */
				case WL_EARTHSTRAIN:		/* �A�[�X�X�g���C�� */
				case WL_TETRAVORTEX:		/* �e�g���{���e�b�N�X */
				case WL_RELEASE:			/* �����[�X */
					if((skill = pc_checkskill(sd,WL_RADIUS)) > 0)		// ���f�B�E�X
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
 * �����_�������X�L������
 *------------------------------------------
 */
int skill_searchrandomid(int type)
{
	int c;

	// type��1�ȏ�Ȃ̂Ńf�N�������g����
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
 * �X�L���ǉ�����
 *------------------------------------------
 */
int skill_additional_effect( struct block_list* src, struct block_list *bl,int skillid,int skilllv,int attack_type,unsigned int tick)
{
	/* MOB�ǉ����ʃX�L���p */
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

	// PC,MOB,PET,MERC,ELEM�ȊO�͒ǉ����ʂ̑ΏۊO
	if(!(bl->type & (BL_PC | BL_MOB | BL_PET | BL_MERC | BL_ELEM)))
		return 0;

	// �O���E���h�h���t�g�̂Ƃ���src��ݒu�҂ɒu��
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
			/* ������ */
			if( pc_isfalcon(sd) &&
			    (skill = pc_checkskill(sd,HT_BLITZBEAT)) > 0 &&
			    (sd->status.weapon == WT_BOW || battle_config.allow_any_weapon_autoblitz) &&
			    atn_rand()%10000 < sd->paramc[5]*30+100 )
			{
				if(pc_is3rdclass(sd) || pc_is4thclass(sd)) {
					// 3���E�E4���E�͏K�����x���Ŕ���
					skill_castend_damage_id(src,bl,HT_BLITZBEAT,skill,tick,0xf00000);
				} else {
					int lv = (sd->status.job_level+9)/10;
					skill_castend_damage_id(src,bl,HT_BLITZBEAT,(skill < lv)? skill: lv,tick,0xf00000);
				}
			}
			/* �����E�H�[�O�X�g���C�N */
			if( pc_iswolf(sd) && (skill = pc_checkskill(sd,RA_WUGSTRIKE)) > 0) {
				int rate = sd->paramc[5]*30;
				if(pc_isfalcon(sd))
					rate = rate / 3;
				if(atn_rand()%10000 < rate)
					skill_castend_damage_id(src,bl,RA_WUGSTRIKE,skill,tick,0xf00000);
			}
			/* �����z�[�N���b�V�� */
			if( pc_isfalcon(sd) && (skill = pc_checkskill(sd,WH_HAWKRUSH)) > 0) {
				int rate = sd->paramc[10]*30;
				rate += rate * (pc_checkskill(sd,WH_NATUREFRIENDLY) * 20) / 100;
				if(atn_rand()%10000 < rate)
					skill_castend_damage_id(src,bl,WH_HAWKRUSH,skill,tick,0xf00000);
			}
			/* �X�i�b�`���[ */
			if(sd->status.weapon != WT_BOW && (skill = pc_checkskill(sd,RG_SNATCHER)) > 0) {
				int skill2;
				if((skill*15 + 55) + (skill2 = pc_checkskill(sd,TF_STEAL))*10 > atn_rand()%1000) {
					if(dstmd && pc_steal_item(sd,dstmd))
						clif_skill_nodamage(src,bl,TF_STEAL,skill2,1);
					else if(battle_config.display_snatcher_skill_fail)
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				}
			}
			/* �e�R���R��\�� */
			if(sd->sc.data[SC_TKCOMBO].timer == -1) {
				int id = 0, lv = 0;
				if(sd->sc.data[SC_READYSTORM].timer != -1 && (lv = pc_checkskill(sd,TK_STORMKICK)) > 0 && atn_rand()%100 < 15) {
					// �t�F�I���`���M
					id = TK_STORMKICK;
				}
				else if(sd->sc.data[SC_READYDOWN].timer != -1 && (lv = pc_checkskill(sd,TK_DOWNKICK)) > 0 && atn_rand()%100 < 15) {
					// �l�����`���M
					id = TK_DOWNKICK;
				}
				else if(sd->sc.data[SC_READYTURN].timer != -1 && (lv = pc_checkskill(sd,TK_TURNKICK)) > 0 && atn_rand()%100 < 15) {
					// �g�������`���M
					id = TK_TURNKICK;
				}
				else if(sd->sc.data[SC_READYCOUNTER].timer != -1 && (lv = pc_checkskill(sd,TK_COUNTER)) > 0) {
					// �A�v�`���I�����M
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
					// TK�R���{���͎��Ԃ̍Œ�ۏ�ǉ�
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
			/* �G���`�����g�f�b�g���[�|�C�Y��(�ғŌ���) */
			if(sd->sc.data[SC_EDP].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DPOISON,sd->sc.data[SC_EDP].val2,sd->status.base_level)) {
					int lv = sd->sc.data[SC_EDP].val1;
					status_change_pretimer(bl,SC_DPOISON,lv,0,0,0,skill_get_time2(ASC_EDP,lv),0,tick+status_get_amotion(src));
				}
			}
			/* �����g�_�E�� */
			if(sd->sc.data[SC_MELTDOWN].timer != -1) {
				if(atn_rand() % 100 < sd->sc.data[SC_MELTDOWN].val1) {
					// ����j��
					if(dstsd) {
						pc_break_equip(dstsd, LOC_RARM);
					} else {
						status_change_start(bl,SC_STRIPWEAPON,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
				if(atn_rand() % 1000 < sd->sc.data[SC_MELTDOWN].val1*7) {
					// �Z�j��
					if(dstsd) {
						pc_break_equip(dstsd, LOC_BODY);
					} else {
						status_change_start(bl,SC_STRIPARMOR,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
			}
			/* �|�C�Y�j���O�E�F�|�� */
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				int lv   = sd->sc.data[SC_POISONINGWEAPON].val1;
				int type = sd->sc.data[SC_POISONINGWEAPON].val2;
				if(atn_rand() % 10000 < status_change_rate(bl,type,sd->sc.data[SC_POISONINGWEAPON].val3,status_get_lv(src)))
					status_change_start(bl,type,lv,0,0,0,skill_get_time2(GC_POISONINGWEAPON,lv),0);
			}
		}
		break;
	case SM_BASH:			/* �o�b�V���i�}���U���j */
		if( sd && pc_checkskill(sd,SM_FATALBLOW) > 0 ) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*(skilllv-5)+(sd->status.base_level/3),sd->status.base_level))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0,tick+status_get_amotion(src));
		}
		else if (md && mobdb_search(md->class_)->mode_opt[MDOPT_FATALBLOW] > 0) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*(skilllv-5)+(status_get_lv(src)/3),mobdb_search(md->class_)->lv))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case TF_POISON:			/* �C���x�i�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,400*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;

	case AS_SPLASHER:		/* �x�i���X�v���b�V���[ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,200*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case AS_VENOMKNIFE:		/* �x�i���i�C�t */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,TF_POISON,SKILLFAIL_FAILED,0,0);
		break;

	case AS_SONICBLOW:		/* �\�j�b�N�u���[ */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,200*skilllv+1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
	case MA_FREEZINGTRAP:
		if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_FLASHER:		/* �t���b�V���[ */
		if( !(status_get_mode(bl)&MD_BOSS) && status_get_race(bl) != RCT_PLANT ) { // �{�X�ƐA������
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case WZ_METEOR:			/* ���e�I�X�g�[�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case WZ_VERMILION:		/* ���[�h�I�u���@�[�~���I�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,400*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case WZ_FROSTNOVA:		/* �t���X�g�m���@ */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv*500+3300,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case WZ_STORMGUST:		/* �X�g�[���K�X�g */
#ifdef PRE_RENEWAL
#ifdef DYNAMIC_SC_DATA
		status_calloc_sc_data(tsc);
#endif
		if(tsc) {	// �{�X�����Ƃ��̑���val3�̗p�r���Ⴄ���߉��Z�ʒu�𒲐�
			if(status_get_mode(bl)&MD_BOSS) {
				// �{�X����
				if(tsc->data[SC_FREEZE].val3 >= 3)
					tsc->data[SC_FREEZE].val3 = 0;
				tsc->data[SC_FREEZE].val3++;	// �d���_���[�W�̃^�C�~���O�Ɏg�p(skill_unit_onplace_timer()���ɂĎg�p)
			} else {
				// ��{�X����
				if(++tsc->data[SC_FREEZE].val3 >= 3) {	// �ʏ�ʂ蓀���^�C�~���O�Ɏg�p 
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

	case HT_LANDMINE:		/* �����h�}�C�� */
	case MA_LANDMINE:
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case HT_SHOCKWAVE:		/* �V���b�N�E�F�[�u�g���b�v */
		if(dstsd) {
			dstsd->status.sp -= dstsd->status.sp*(5+15*skilllv)/100;
			if(dstsd->status.sp <= 0)
				dstsd->status.sp = 0;
			clif_updatestatus(dstsd,SP_SP);
		}
		break;
	case HT_SANDMAN:		/* �T���h�}�� */
	case MA_SANDMAN:
		if(!(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,1000*skilllv+4000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case TF_SPRINKLESAND:		/* ���܂� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case TF_THROWSTONE:		/* �Γ��� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,300,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case CR_HOLYCROSS:		/* �z�[���[�N���X */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case CR_GRANDCROSS:		/* �O�����h�N���X */
	case NPC_GRANDDARKNESS:		/* �O�����h�_�[�N�l�X */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {	// �����t�^�������S�ϐ��ɂ͖���
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;

	case CR_SHIELDCHARGE:		/* �V�[���h�`���[�W */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1500+skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case RG_RAID:			/* �T�v���C�Y�A�^�b�N */
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
	case BA_FROSTJOKE:		/* �����W���[�N */
		if(status_get_hp(bl) > 0) {	// �Ώۂ�����ł��Ȃ�
			int rate = 0;
			if(battle_check_target(src,bl,BCT_ENEMY) > 0)
				rate = 1500 + 500 * skilllv;
			else if(battle_check_target(src,bl,BCT_PARTY) > 0)	// PT�����o�ɂ���m���ł�����
				rate = (skilllv > 5) ? 1000 : (375 + 125 * skilllv) / 10 * 10;

			if(rate > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case DC_SCREAM:		/* �X�N���[�� */
		if(status_get_hp(bl) > 0) {	// �Ώۂ�����ł��Ȃ�
			int rate = 0;
			if(battle_check_target(src,bl,BCT_ENEMY) > 0)
				rate = 2500 + 500 * skilllv;
			else if(battle_check_target(src,bl,BCT_PARTY) > 0)	// PT�����o�ɂ���m���ł�����
				rate = (skilllv > 5) ? 1250 : (625 + 125 * skilllv) / 10 * 10;

			if(rate > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_STUN,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;

	case DC_UGLYDANCE:	/* ��������ȃ_���X */
		if(dstsd) {
			int sp = 5+skilllv*(5+pc_checkskill(dstsd,DC_DANCINGLESSON));
			pc_heal(dstsd,0,-sp,0,0);
		}
		break;

	case BD_LULLABY:	/* �q��S */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,2550,status_get_lv(src)))
			status_change_pretimer(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case AM_ACIDTERROR:		/* �A�V�b�h�e���[ */
		if(bl->type == BL_PC && atn_rand()%100 < skill_get_time(skillid,skilllv)) {
			pc_break_equip((struct map_session_data *)bl, LOC_BODY);
			clif_emotion(bl,23);
		}
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	/* MOB�̒ǉ����ʕt���X�L�� */

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

	case LK_HEADCRUSH:		/* �w�b�h�N���b�V�� */
		{
			int race = status_get_race(bl);
			if( !battle_check_undead(race,status_get_elem_type(bl)) && race != RCT_DEMON ) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,5000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;
	case LK_JOINTBEAT:		/* �W���C���g�r�[�g */
		if( atn_rand()%100 < skilllv*5+5-status_get_str(bl)*27/100 )
			status_change_pretimer(bl,SC_JOINTBEAT,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case PF_SPIDERWEB:		/* �X�p�C�_�[�E�F�u */
		{
			int sec = skill_get_time2(skillid,skilllv);
			if( map[src->m].flag.pvp || map[src->m].flag.gvg ) // �ΐl�t�B�[���h�ł͍S�����Ԕ���
				sec = sec/2;
			unit_stop_walking(bl,1);
			status_change_start(bl,SC_SPIDERWEB,skilllv,0,0,0,sec,0);
		}
		break;
	case ASC_METEORASSAULT:		/* ���e�I�A�T���g */
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
	case MO_EXTREMITYFIST:		/* ���C���e���� */
		// ���C�����g����5���Ԏ��R�񕜂��Ȃ��悤�ɂȂ�
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0 );
		break;
	case HW_NAPALMVULCAN:			/* �i�p�[���o���J�� */
		// skilllv*5%�̊m���ŏ�Ԉُ픻����s���A���̌�100%�̊m���Ŏ􂢔�����s��
		if(atn_rand() % 10000 < skilllv*500) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
		}
		break;
	case PA_PRESSURE:		/* �v���b�V���[ */
		if(dstsd) {
			// �Ώۂ�15% + skilllv*5%��SP�U��(�K��)
			int sp = dstsd->status.sp*(15+5*skilllv)/100;
			pc_heal(dstsd,0,-sp,0,0);
		}
		break;
	case WS_CARTTERMINATION:
		// skilllv*5%�̊m���ŃX�^��
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,500*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,skill_get_time2(NPC_STUNATTACK,7),0,tick+status_get_amotion(src));
		break;
	case CR_ACIDDEMONSTRATION:	/* �A�V�b�h�f�����X�g���[�V���� */
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
	case TK_DOWNKICK:		/* �l�����`���M */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,33330,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,5000,0,tick+status_get_amotion(src));
		break;
	case TK_TURNKICK:		/* �g�������`���M */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,20000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case CH_TIGERFIST:		/* ���Ռ� */
		if( atn_rand()%100 < 10 + skilllv*10 ) {
			int sec = skill_get_time2(skillid,skilllv) - status_get_agi(bl)*50;
			// �Œ�S�����ԕ⏞�i�Ƃ肠�����A���N����1/2�j
			if(sec < 1500 + 15*skilllv)
				sec = 1500 + 15*skilllv;
			status_change_start(bl,SC_TIGERFIST,skilllv,0,0,0,sec,0);
			unit_stop_walking(bl,1);
		}
		break;
	case SL_STUN:			/* �G�X�g�� */
		if(status_get_size(bl) == 1 && atn_rand() % 10000 < status_change_rate(bl,SC_STUN,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,7,0,0,0,2000,0,tick+status_get_amotion(src));
		break;
	case GS_FLING:			/* �t���C���O */
		if(sd) {
			int coin = 5;
			if(sd->coin.num < 5)
				coin = sd->coin.num;
			pc_delcoin(sd,coin,0);
			status_change_start(bl,SC_FLING,skilllv,coin,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case GS_BULLSEYE:		/* �u���Y�A�C */
		{
			int race = status_get_race(bl);
			if(!(status_get_mode(bl)&MD_BOSS) && (race == RCT_BRUTE || race == RCT_DEMIHUMAN || race == RCT_PLAYER_HUMAN || race == RCT_PLAYER_DORAM) && atn_rand()%10000 < 10)
				skill_castend_nodamage_id(src,bl,SA_COMA,skilllv,tick,0);
		}
		break;
	case GS_DISARM:			/* �f�B�X�A�[�� */
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
	case GS_PIERCINGSHOT:		/* �s�A�[�V���O�V���b�g */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,300*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GS_FULLBUSTER:		/* �t���o�X�^�[ */
		{
			if(atn_rand() % 10000 < status_change_rate(src,SC_BLIND,200*skilllv,status_get_lv(src)))
				status_change_pretimer(src,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case GS_GROUNDDRIFT:		/* �O���E���h�h���t�g */
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

			// �m����50%
			if(type > 0 && atn_rand() % 10000 < status_change_rate(bl,type,5000,status_get_lv(src)))
				status_change_pretimer(bl,type,7,0,0,0,skill_get_time2(timeid,7),0,tick+status_get_amotion(src));
		}
		break;
	case NJ_KASUMIKIRI:		/* ���a�� */
		status_change_start(src,SC_HIDING,skilllv,0,1,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NJ_HYOUSYOURAKU:		/* �X������ */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,1000+skilllv*1000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NPC_ICEBREATH:		/* �A�C�X�u���X */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,7000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NPC_ACIDBREATH:		/* �A�V�b�h�u���X */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,7000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_BLEEDING:		/* �o���U�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,(skilllv < 5)? skilllv*2000:10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_HELLJUDGEMENT:		/* �w���W���b�W�����g */
	case NPC_HELLJUDGEMENT2:		/* �f���j�b�N�w���W���b�W�����g */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_EVILLAND:		/* �C�r�������h */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_CRITICALWOUND:		/* �v�����U�� */
		status_change_start(bl,SC_CRITICALWOUND,skilllv,skilllv*10,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_WIDECRITICALWOUND:		/* ���C�h�N���e�B�J���E�[���Y */
		status_change_start(bl,SC_CRITICALWOUND,skilllv,skilllv>=6? (skilllv-5)*20: skilllv*20,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_VENOMIMPRESS:		/* M�x�i���C���v���X */
		status_change_start(bl,SC_VENOMIMPRESS,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_MAGMA_ERUPTION:	/* M�}�O�}�C���v�V���� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,9000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_MAGMA_ERUPTION_DOTDAMAGE:	/* M�}�O�}�C���v�V����(�ǌ�) */
		status_change_start(bl,SC_HELLINFERNO,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_RAYOFGENESIS:	/* M���C�I�u�W�F�l�V�X */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,(skilllv<8? 500: 1000),status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NPC_DRAGONBREATH:	/* M�h���S���u���X */
		if(atn_rand() % 10000 < 5000) {
			if(skilllv < 6)
				status_change_pretimer(bl,SC_HELLINFERNO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			else
				status_change_pretimer(bl,SC_FROSTMISTY,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case MH_NEEDLE_OF_PARALYZE:	/* �j�[�h���I�u�p�����C�Y */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_PARALYZE,2500+skilllv*1500,status_get_lv(src)))
			status_change_start(bl,SC_PARALYZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case MH_POISON_MIST:	/* �|�C�Y���~�X�g */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_STAHL_HORN:	/* �V���^�[���z�[�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_SILVERVEIN_RUSH:	/* �V���o�[�x�C�����b�V�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_MIDNIGHT_FRENZY:	/* �~�b�h�i�C�g�t�����W */
		if(atn_rand() % 10000 < 1000+skilllv*200+(hd? hd->spiritball * 100: 0))
			status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MH_TINDER_BREAKER:	/*�e�B���_�[�u���C�J�[ */
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
	case MH_LAVA_SLIDE:		/* ���[���@�X���C�h */
		if(atn_rand() % 10000 < skilllv * 1000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case MER_CRASH:			/* �N���b�V�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*600,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RK_WINDCUTTER:		/* �E�B���h�J�b�^�[ */
		if(atn_rand() % 10000 < 300 + skilllv * 200)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RK_DRAGONBREATH:	/* �t�@�C�A�[�h���S���u���X */
		if(atn_rand() % 10000 < 1500) {
			int sec = skill_get_time(skillid,skilllv) - (status_get_lv(bl) * 20) - (status_get_agi(bl) * 20) - (status_get_luk(bl) * 10);
			if(sec > 0)
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0,tick+status_get_amotion(src));
		}
		break;
	case RK_DRAGONBREATH_WATER:	// �E�H�[�^�[�h���S���u���X
		if(atn_rand() % 10000 < 1500) {
			int sec = skill_get_time(skillid,skilllv) - (status_get_vit(bl) * 50) - (status_get_dex(bl) * 50);
			if(sec > 0)
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,sec,0,tick+status_get_amotion(src));
		}
		break;
	case AB_ADORAMUS:		/* �A�h�����X */
		if(atn_rand() % 10000 < skilllv * 400) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_JACKFROST:		/* �W���b�N�t���X�g */
	case NPC_JACKFROST:		/* M�W���b�N�t���X�g */
		if(!tsc || tsc->data[SC_FREEZE].timer == -1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_CRIMSONROCK:	/* �N�����]�����b�N */
		if(atn_rand() % 10000 < 4000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WL_COMET:			/* �R���b�g */
	case NPC_COMET:			/* M�R���b�g */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WL_EARTHSTRAIN:	/* �A�[�X�X�g���C�� */
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
	case RA_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
		if(!tsc || tsc->data[SC_ELECTRICSHOCKER].timer == -1) {
			int sec = skill_get_time2(skillid,skilllv) - (status_get_agi(bl) + status_get_vit(bl)) * 70;
			if(sec > 0) {
				unit_stop_walking(bl,1);
				status_change_start(bl,SC_ELECTRICSHOCKER,skilllv,0,0,0,sec,0);
			}
		}
		break;
	case RA_WUGBITE:	/* �E�H�[�O�o�C�g */
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
	case RA_MAGENTATRAP:	/* �}�[���^�g���b�v */
	case RA_COBALTTRAP:		/* �R�o���g�g���b�v */
	case RA_MAIZETRAP:		/* ���C�Y�g���b�v */
	case RA_VERDURETRAP:	/* ���F���f���[���g���b�v */
		if(dstmd) {
			// �{�X�����ɂ͖���
			if((battle_config.boss_no_element_change && dstmd->mode&MD_BOSS))
				break;
			// �G�͑������x�����ێ�����
			switch(skillid) {
				case RA_MAGENTATRAP:	// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_FIRE;
					break;
				case RA_COBALTTRAP:		// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WATER;
					break;
				case RA_MAIZETRAP:		// �n
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_EARTH;
					break;
				case RA_VERDURETRAP:	// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WIND;
					break;
			}
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case RA_FIRINGTRAP:		/* �t�@�C�A�����O�g���b�v */
	case RA_ICEBOUNDTRAP:	/* �A�C�X�o�E���h�g���b�v */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*1000+4000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_PILEBUNKER:		/* �p�C���o���J�[ */
		if(atn_rand() % 10000 < 500 + skilllv * 1500)
			status_change_release(bl,0x100); 	// �h�䖂�@����
		break;
	case NC_FLAMELAUNCHER:	/* �t���C���X���[���[ */
		if(atn_rand() % 10000 < 5000 + skilllv * 1000)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_COLDSLOWER:		/* �R�[���h�X���[���[ */
		if((!tsc || tsc->data[SC_FREEZE].timer == -1) &&
			(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv * 1000,status_get_lv(src)))) {
			status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		} else if(atn_rand() % 10000 < 2000 + skilllv * 1000) {
			status_change_pretimer(bl,SC_FROSTMISTY,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case NC_POWERSWING:	/* �p���[�X�C���O */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case NC_MAGMA_ERUPTION_DOTDAMAGE:	/* �}�O�}�C���v�V����(�ǌ�) */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case LG_PINPOINTATTACK:	/* �s���|�C���g�A�^�b�N */
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
	case LG_MOONSLASHER:	/* ���[���X���b�V���[ */
		if(atn_rand() % 10000 < 2000 + skilllv * 1600)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case LG_RAYOFGENESIS:	/* ���C�I�u�W�F�l�V�X */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,5000,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		break;
	case LG_EARTHDRIVE:		/* �A�[�X�h���C�u */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_DRAGONCOMBO:	/* �o���r */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,100+skilllv*100,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_FALLENEMPIRE:	/* ��Z���x */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_WINDMILL:		/* ������ */
		if(dstsd)
			status_change_start(bl,SC_SITDOWN_FORCE,skilllv,0,0,0,1000,0);
		else if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_GENTLETOUCH_QUIET:	/* �_�� -��- */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SILENCE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SR_HOWLINGOFLION:	/* ���q�� */
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

	case WM_SOUND_OF_DESTRUCTION:	/* �T�E���h�I�u�f�B�X�g���N�V���� */
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
	case SO_EARTHGRAVE:		/* �A�[�X�O���C�� */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_DIAMONDDUST:	/* �_�C�������h�_�X�g */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500 + skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_CLOUD_KILL:		/* �N���E�h�L�� */
	case NPC_CLOUD_KILL:		/* M�N���E�h�L�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SO_VARETYR_SPEAR:		/* ���F���`���[���X�s�A�[ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_HELLS_PLANT_ATK:	/* �w���Y�v�����g(�U��) */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,500 + skilllv * 500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,2000 + skilllv * 1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_DEMONIC_FIRE:	/* �f���j�b�N�t�@�C�A�[ */
		if(atn_rand() % 10000 < 400 + skilllv * 400)
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case GN_SLINGITEM_RANGEMELEEATK:	/* �X�����O�A�C�e��(�������U��) */
		switch(skilllv) {
		case 1:		// �R�R�i�b�c���e
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,5000,status_get_lv(src)))
				status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,5000,status_get_lv(src)))
				status_change_pretimer(bl,SC_STUN,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			break;
		case 2:		// ���������e
			status_change_start(bl,SC_MELON_BOMB,15,0,0,0,skill_get_time(skillid,skilllv),0);
			break;
		case 4:		// �o�i�i���e
			status_change_start(bl,SC_BANANA_BOMB,15,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		}
		break;
	case KO_JYUMONJIKIRI:	/* �\�����a�� */
		if(!tsc || tsc->data[GetSkillStatusChangeTable(skillid)].timer == -1)
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case KO_MAKIBISHI:		/* �T�H */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RL_MASS_SPIRAL:		/* �}�X�X�p�C���� */
		if(!(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,3000+1000*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RL_BANISHING_BUSTER:	/* �o�j�V���O�o�X�^�[ */
		if(atn_rand()%100 < skilllv*10+50)
			status_change_release(bl,0x02);	// �f�B�X�y������
		break;
	case RL_AM_BLAST:		/* �A���`�}�e���A���u���X�g */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RL_S_STORM:		/* �V���b�^�[�X�g�[�� */
		if(dstsd && atn_rand()%10000 <= 500 * skilllv) {
			pc_break_equip2(dstsd, EQUIP_INDEX_HEAD2);
		}
		break;
	case SJ_FULLMOONKICK:	/* �����r */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SJ_STAREMPEROR:		/* ����~�� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src)))
			status_change_pretimer(bl,SC_SILENCE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SP_SPA:			/* �G�X�p */
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SHA:			/* �G�X�n */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SP_SOULEXPLOSION:	/* ���̕��� */
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
	case SU_SCRATCH:	/* �Ђ����� */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,500 + skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SU_SV_STEMSPEAR:	/* �}�^�^�r�����X */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_BLEED,1,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SU_SCAROFTAROU:	/* �^���E�̏� */
		if(atn_rand() % 10000 < 60 + status_get_jlv(src)/3 + status_get_dex(src)/10) {	// �b��m��
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_CN_METEOR2:	/* �C�k�n�b�J���e�I(��) */
		if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,2000,status_get_lv(src)))
			status_change_pretimer(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case NPC_UGLYDANCE:
		if(dstsd) {
			int sp = 5+skilllv*5;
			pc_heal(dstsd,0,-sp,0,0);
		}
		break;
	case DK_SERVANT_W_PHANTOM:	/* �T�[���@���g�E�F�|���F�t�@���g�� */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case AG_DEADLY_PROJECTION:	/* �f�b�h���[�v���W�F�N�V���� */
		status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case IQ_FIRST_BRAND:		/* ��ꌂ�F���� */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case IQ_SECOND_FLAME:		/* ��񌂁F�Ŗ��̉� */
	case IQ_SECOND_FAITH:		/* ��񌂁F�M�O */
	case IQ_SECOND_JUDGEMENT:	/* ��񌂁F�R�� */
		if(tsc && tsc->data[SC_FIRST_BRAND].timer != -1)
			status_change_end(bl,SC_FIRST_BRAND,-1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case IQ_THIRD_PUNISH:		/* ��O���F�f�� */
	case IQ_THIRD_FLAME_BOMB:	/* ��O���F�ŉΌ� */
	case IQ_THIRD_CONSECRATION:	/* ��O���F�� */
		if(tsc && tsc->data[SC_SECOND_BRAND].timer != -1)
			status_change_end(bl,SC_SECOND_BRAND,-1);
		break;
	case CD_ARBITRIUM:	/* �A���r�g���E�� */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*200,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case ABC_UNLUCKY_RUSH:	/* �A�����b�L�[���b�V�� */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000*skilllv,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case WH_DEEPBLINDTRAP:	/* �f�B�[�v�u���C���h�g���b�v */
	case WH_SOLIDTRAP:		/* �\���b�h�g���b�v */
	case WH_SWIFTTRAP:		/* �X�C�t�g�g���b�v */
	case WH_FLAMETRAP:		/* �t���C���g���b�v */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case BO_ACIDIFIED_ZONE_WATER:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case BO_ACIDIFIED_ZONE_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(�n) */
	case BO_ACIDIFIED_ZONE_WIND:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case BO_ACIDIFIED_ZONE_FIRE:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
		if(atn_rand()%100 < skilllv)
			skill_unitsetting(src,BO_ACIDIFIED_ZONE_WATER_INSTALL_ON_GROUND+skillid-BO_ACIDIFIED_ZONE_WATER,skilllv,bl->x,bl->y,0);
		break;
	case TR_ROSEBLOSSOM:	/* ���[�u���b�T�� */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case EM_DIAMOND_STORM:		/* �_�C�������h�X�g�[�� */
	case EM_TERRA_DRIVE:		/* �e���h���C�u */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),750+skilllv*1250,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case EM_LIGHTNING_LAND:		/* ���C�g�j���O�����h */
	case EM_VENOM_SWAMP:		/* �x�i���X�����v */
	case EM_CONFLAGRATION:		/* �R���t���O���[�V���� */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),500+skilllv*1000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SH_HOWLING_OF_CHUL_HO:	/* �^�C�K�[�n�E�����O */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case HN_MEGA_SONIC_BLOW:	/* ���K�\�j�b�N�u���[ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),3000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_SHIELD_CHAIN_RUSH:	/* �V�[���h�`�F�[�����b�V�� */
	case HN_SPIRAL_PIERCE_MAX:	/* �X�p�C�����s�A�[�X�}�b�N�X */
		if(!(status_get_mode(bl)&MD_BOSS))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_METEOR_STORM_BUSTER:	/* ���e�I�X�g�[���o�X�^�[ */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),3000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case HN_NAPALM_VULCAN_STRIKE:	/* �i�p�[���o���J���X�g���C�N */
		if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),2000,status_get_lv(src)))
			status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case SKE_ALL_IN_THE_SKY:	/* �V������ */
		unit_heal(bl,0,0,-(status_get_ap(bl)),1);
		break;
	case SS_KAGEGARI:			/* �e��� */
	case SS_FUUMASHOUAKU:		/* �����藠�� -����- */
	case SS_KUNAIWAIKYOKU:		/* �ꖳ -�c��- */
	case SS_ANTENPOU:			/* �Ó]�C */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	}

	// �ǉ���Ԉُ�
	switch(skillid) {
	case HT_FREEZINGTRAP:	// �J�[�h���ʖ����̃X�L��
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
		if(sd && attack_type&BF_WEAPON && skillid > 0) {	// �����U���X�L��
			/* �G���`�����g�f�b�g���[�|�C�Y��(�ғŌ���) */
			if(sd->sc.data[SC_EDP].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DPOISON,sd->sc.data[SC_EDP].val2,sd->status.base_level)) {
					int lv = sd->sc.data[SC_EDP].val1;
					status_change_pretimer(bl,SC_DPOISON,lv,0,0,0,skill_get_time2(ASC_EDP,lv),0,tick+status_get_amotion(src));
				}
			}
			/* �����g�_�E�� */
			if(sd->sc.data[SC_MELTDOWN].timer != -1) {
				if(atn_rand() % 100 < sd->sc.data[SC_MELTDOWN].val1) {
					// ����j��
					if(dstsd) {
						pc_break_equip(dstsd, LOC_RARM);
					} else {
						status_change_start(bl,SC_STRIPWEAPON,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
				if(atn_rand() % 1000 < sd->sc.data[SC_MELTDOWN].val1*7) {
					// �Z�j��
					if(dstsd) {
						pc_break_equip(dstsd, LOC_BODY);
					} else {
						status_change_start(bl,SC_STRIPARMOR,1,0,0,0,skill_get_time2(WS_MELTDOWN,sd->sc.data[SC_MELTDOWN].val1),0);
					}
				}
			}
			/* �|�C�Y�j���O�E�F�|�� */
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1 && !(status_get_mode(bl)&MD_BOSS)) {
				int lv   = sd->sc.data[SC_POISONINGWEAPON].val1;
				int type = sd->sc.data[SC_POISONINGWEAPON].val2;
				if(atn_rand() % 10000 < status_change_rate(bl,type,sd->sc.data[SC_POISONINGWEAPON].val3,status_get_lv(src)))
					status_change_start(bl,type,lv,0,0,0,skill_get_time2(GC_POISONINGWEAPON,lv),0);
			}
		}
	}

	// �X�L���̒ǉ���Ԉُ�
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
		// �����ʏ�U���Ȃ獬���I��
		if(tsc && tsc->data[SC_CONFUSION].timer != -1 && skillid == 0)
			status_change_end(bl,SC_CONFUSION,-1);

		// �J�[�h�ɂ��ǉ�����
		if(sd) {
			int i, rate;

			for(i = 0; i < MAX_EFF_TYPE; i++) {
				if(!dstmd || dstmd->class_ != MOBID_EMPERIUM) {
					if(sd->addeff_range_flag[i] > 2) {
						sd->addeff_range_flag[i] -= 2;	// �����W�t���O������Ό��ɖ߂�
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

		// �����ɂ���
		if(sd && sd->curse_by_muramasa > 0)
		{
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_CURSE,sd->curse_by_muramasa,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
		}

		// �����ăA�C�e������
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

		// �����ăA�C�e���u���C�N
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

		// ������mob�ω�
		if(sd && dstmd && mobdb_search(dstmd->class_)->race != RCT_DEMIHUMAN && !map[dstmd->bl.m].flag.nobranch &&
		   !(mobdb_search(dstmd->class_)->mode&MD_BOSS) && dstmd->class_ != MOBID_EMPERIUM && dstmd->state.special_mob_ai == MOB_AI_NONE)
		{
			if(atn_rand()%10000 < sd->mob_class_change_rate)
			{
				//clif_skill_nodamage(src,bl,SA_CLASSCHANGE,1,1);
				mob_class_change_randam(dstmd,sd->status.base_level);
			}
		}

	// ���@�ɂ��ǉ���Ԉُ�
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
 * �X�L���U��������΂�����
 *  count -> 0x00XYZZZZ
 *	X: ������΂������w��(�t����)
 *	   ������0�i�^�k�w��A�^��ɔ�΂��j�Ȃ�8�Ƃ��đ��
 *	Y: �t���O
 *		SAB_NOMALBLOW   : src��target�̈ʒu�֌W�Ő���΂�����������
 *		SAB_REVERSEBLOW : target�̌����Ƌt�����ɐ����
 *		SAB_NODAMAGE    : �_���[�W�𔭐��������ɐ���΂�
 *		SAB_NOPATHSTOP  : ������ьo�H�ɕǂ��������炻���Ŏ~�܂�
 *�@	SAB_NOTKNOCK    : �m�b�N�o�b�N�ł͂Ȃ��X�L���p�̓���t���O
 *	Z: ������΂��Z����
 *-------------------------------------------------------------------------
 */
int skill_blown( struct block_list *src, struct block_list *target,int count)
{
	int dx=0,dy=0,nx,ny;
	int dir,ret;
	struct status_change *sc = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	// �V�[�Y�Ȃ琁����΂����s
	if(map[target->m].flag.gvg)
		return 0;

	// ������΂��Z������0
	if((count&0xffff) == 0)
		return 0;

	sc = status_get_sc(target);

	if(sc) {
		if(sc->data[SC_ANKLE].timer != -1)	// �A���N�����͖������Ő�����΂���Ȃ�
			return 0;
		if(sc->data[SC_SU_STOOP].timer != -1)	// �������܂����
			status_change_end(target, SC_SU_STOOP, -1);
	}

	if(target->type == BL_PC) {
		if(!(count&SAB_NOTKNOCK) && ((struct map_session_data *)target)->special_state.no_knockback)
			return 0;
		// �o�W���J���͐�����΂���Ȃ�
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
		;	// �������Ȃ�
	} else {
		return 0;
	}

	if(count&0xf00000) {
		dir = (count>>20)&0xf;
		if(dir == 8)	// 0�ɒu������
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
		unit_stop_walking(target,0);	// �_���[�W�f�B���C����
	else
		unit_stop_walking(target,2);	// �_���[�W�f�B���C�L��

	if(target->type == BL_SKILL) {
		struct skill_unit *su = (struct skill_unit *)target;
		skill_unit_move_unit_group(su->group,target->m,nx-target->x,ny-target->y);
	} else {
		unit_movepos(target,nx,ny,(count&SAB_NODAMAGE)? 0: 1);
	}

	return 1;
}

/*=========================================================================
 * �X�L���U��������΂�����(�J�[�h�ǉ����ʗp)
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
 * �X�L���͈͍U���p(map_foreachinarea����Ă΂��)
 * flag�ɂ��āF16�i�}���m�F
 * MSB <- 0ffTffff -> LSB
 *  ffff = ���R�Ɏg�p�\
 *     T = �^�[�Q�b�g�I��p(BCT_*)
 *     0 = �\��B0�ɌŒ�
 *------------------------------------------
 */
static int skill_area_temp[8];	/* �ꎞ�ϐ��B�K�v�Ȃ�g���B */
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

	src      = va_arg(ap,struct block_list *); // �����ł�src�̒l���Q�Ƃ��Ă��Ȃ��̂�NULL�`�F�b�N�͂��Ȃ�
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

	// battle_check_target�ŊY�����Ȃ�㩂��U���Ώ�
	switch (unit->group->unit_id) {
		case UNT_FIREPILLAR_WAITING:	/* �t�@�C�A�[�s���[(�����O) */
		case UNT_SKIDTRAP:	/* �X�L�b�h�g���b�v */
		case UNT_LANDMINE:	/* �����h�}�C�� */
		case UNT_SHOCKWAVE:	/* �V���b�N�E�F�[�u�g���b�v */
		case UNT_SANDMAN:	/* �T���h�}�� */
		case UNT_FLASHER:	/* �t���b�V���[ */
		case UNT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
		case UNT_TALKIEBOX:	/* �g�[�L�[�{�b�N�X */
		case UNT_MAGENTATRAP:	/* �}�[���^�g���b�v */
		case UNT_COBALTTRAP:	/* �R�o���g�g���b�v */
		case UNT_MAIZETRAP:		/* ���C�Y�g���b�v */
		case UNT_VERDURETRAP:	/* ���F���f���[���g���b�v */
		case UNT_FIRINGTRAP:	/* �t�@�C�A�����O�g���b�v */
		case UNT_ICEBOUNDTRAP:	/* �A�C�X�o�E���h�g���b�v */
		case UNT_CLUSTERBOMB:	/* �N���X�^�[�{�� */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN)
				break;
			return 0;
		case UNT_ANKLESNARE:	/* �A���N���X�l�A */
			if(skill_id == AC_SHOWER || skill_id == MA_SHOWER || skill_id == WZ_SIGHTRASHER || skill_id == SM_MAGNUM || skill_id == MS_MAGNUM || skill_id == RA_SENSITIVEKEEN || unit->group->val2 > 0)
				break;
			return 0;
		case UNT_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
			if(skill_id == RA_SENSITIVEKEEN)
				break;
			return 0;
		default:
			return 0;
	}

	return func(src,bl,skill_id,skill_lv,tick,flag);
}

/*==========================================
 * �X�L�����j�b�g�̏d�˒u���`�F�b�N
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
		case RA_ELECTRICSHOCKER:	// �G���N�g���b�N�V���b�J�[
		case RA_CLUSTERBOMB:		// �N���X�^�[�{��
		case RA_MAGENTATRAP:		// �}�[���^�g���b�v
		case RA_COBALTTRAP:			// �R�o���g�g���b�v
		case RA_MAIZETRAP:			// ���C�Y�g���b�v
		case RA_VERDURETRAP:		// ���F���f���[���g���b�v
		case RA_FIRINGTRAP:			// �t�@�C�A�����O�g���b�v
		case RA_ICEBOUNDTRAP:		// �A�C�X�o�E���h�g���b�v
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
		default:	// �����X�L�����j�b�g�łȂ���΋���
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

	// �Ƃ肠���������`�̃��j�b�g���C�A�E�g�̂ݑΉ�
	range += layout_type;
	return map_foreachinarea(skill_check_unit_range_sub,m,
			x-range,y-range,x+range,y+range,BL_SKILL,skillid);
}

/*==========================================
 * �X�L�����j�b�g�̑����u���`�F�b�N
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

	// �Ƃ肠���������`�̃��j�b�g���C�A�E�g�̂ݑΉ�
	range += layout_type;
	return map_foreachinarea(skill_check_unit_range2_sub,m,
			x-range,y-range,x+range,y+range,BL_CHAR,skillid);
}

/*==========================================
 * �X�L�������̒x��
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
 * �͈̓X�L���g�p������������������
 */
/* �Ώۂ̐����J�E���g����B�iskill_area_temp[0]�����������Ă������Ɓj */
static int skill_area_sub_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
{
	if(skill_area_temp[0] < 0xffff)
		skill_area_temp[0]++;
	return 1;
}

/*==========================================
 * ����̐��𐔂���
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
 * �p�[�e�B���̃~���X�g�����A�����_���[�̐����J�E���g����B�iskill_area_temp[0]�����������Ă������Ɓj
 *------------------------------------------
 */
static int skill_partner_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
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
 * �p�[�e�B���̃g���o�h�D�[���A�g�����F�[���̐����J�E���g����B�iskill_area_temp[0]�����������Ă������Ɓj
 *-------------------------------------------------------------------------
 */
static int skill_4thpartner_count(struct block_list *src,struct block_list *target,int skillid,int skilllv,unsigned int tick,int flag)
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
* �͈͓��Ɏ��g���z�u�����w��X�L�����j�b�g�����邩�`�F�b�N(map_foreachinarea)
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

			// �C���e�B�~�f�C�g�ƃG�N�X�p���V�I����target�����݂��Ȃ��Ă��ǂ��̂ł����̔���͏��O
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
			case BA_FROSTJOKE:			/* �����W���[�N */
			case DC_SCREAM:				/* �X�N���[�� */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_frostjoke_scream,src->m,src->x-range,src->y-range,
					src->x+range,src->y+range,BL_CHAR,src,skl->skill_id,skl->skill_lv,tick);
				break;
			case WZ_WATERBALL:
				if (skl->type>1) {
					skl->timer = 0;	// skill_addtimerskill�Ŏg�p����Ȃ��悤��
					skill_addtimerskill(src,tick+150,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type-1,skl->flag);
					skl->timer = -1;
				}
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case RK_HUNDREDSPEAR:		/* �n���h���b�h�X�s�A�̃X�s�A�u�[�������ǌ� */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,KN_SPEARBOOMERANG);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,KN_SPEARBOOMERANG,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,KN_SPEARBOOMERANG,1,tick,skl->flag);
				}
				break;
			case GC_DARKILLUSION:		/* �_�[�N�C�����[�W�����̃N���X�C���p�N�g�ǌ� */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,GC_CROSSIMPACT);
					if(lv > 0)
						battle_skill_attack(BF_WEAPON,src,src,target,GC_CROSSIMPACT,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,GC_CROSSIMPACT,1,tick,skl->flag);
				}
				break;
			case NC_POWERSWING:		/* �p���[�X�C���O�̃A�b�N�X�u�[�������ǌ� */
				if(src->type == BL_PC) {
					int lv = pc_checkskill((struct map_session_data *)src,NC_AXEBOOMERANG);
					if(lv > 0 && (((struct map_session_data *)src)->weapontype1 == WT_1HAXE || ((struct map_session_data *)src)->weapontype1 == WT_2HAXE))
						battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,lv,tick,skl->flag);
				} else {
					battle_skill_attack(BF_WEAPON,src,src,target,NC_AXEBOOMERANG,1,tick,skl->flag);
				}
				break;
			case AB_DUPLELIGHT_MELEE:		/* �O���C�A�����C�g */
			case SR_CRESCENTELBOW:			/* �j�ꒌ */
			case WM_REVERBERATION_MELEE:	/* �U���c��(����) */
			case NPC_REVERBERATION_ATK:		/* M�U���c��(�U��) */
				battle_skill_attack(BF_WEAPON,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case AB_DUPLELIGHT_MAGIC:		/* �~���A�����C�g */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_CHAINLIGHTNING_ATK:		/* �`�F�[�����C�g�j���O(�A��) */
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
			case NPC_EARTHQUAKE:			/* �A�[�X�N�G�C�N */
			case WL_HELLINFERNO:			/* �w���C���t�F���m */
			case WL_SUMMON_ATK_FIRE:		/* �T�����t�@�C�A�{�[��(�U��) */
			case WL_SUMMON_ATK_WIND:		/* �T�����{�[�����C�g�j���O(�U��) */
			case WL_SUMMON_ATK_WATER:		/* �T�����E�H�[�^�[�{�[��(�U��) */
			case WL_SUMMON_ATK_GROUND:		/* �T�����X�g�[��(�U��) */
			case WM_REVERBERATION_MAGIC:	/* �U���c��(���@) */
			case SS_ANKOKURYUUAKUMU:		/* ���p -�Í���- */
				battle_skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
			case WL_TETRAVORTEX_FIRE:		/* �e�g���{���e�b�N�X(��) */
			case WL_TETRAVORTEX_WATER:		/* �e�g���{���e�b�N�X(��) */
			case WL_TETRAVORTEX_WIND:		/* �e�g���{���e�b�N�X(��) */
			case WL_TETRAVORTEX_GROUND:		/* �e�g���{���e�b�N�X(�n) */
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
			case RA_SENSITIVEKEEN:		/* �s�q�Țk�o�̃E�H�O�o�C�g�ǌ� */
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
			case NPC_PULSESTRIKE2:		/* �p���X�X�g���C�NII�̘A�� */
				skill_castend_damage_id(src,target,skl->skill_id,skl->skill_lv,tick,0);
				break;
			case NPC_DANCINGBLADE_ATK:		/* �_���V���O�u���C�h(�A��) */
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
			case SJ_FALLINGSTAR_ATK2:	/* ��������(�ǌ�) */
				clif_skill_nodamage(src,target,skl->skill_id,skl->skill_lv,1);
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,target->m,
					target->x-range,target->y-range,target->x+range,target->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				break;
			case AG_DESTRUCTIVE_HURRICANE:		/* �f�B�X�g���N�e�B�u�n���P�[�� */
			case AG_CRYSTAL_IMPACT_ATK:	/* �N���X�^���C���p�N�g(�ǌ�) */
			case AG_CRIMSON_ARROW_ATK:	/* �N�����]���A���[(�U��) */
			case CD_ARBITRIUM_ATK:		/* �A���r�g���E��(�ǌ�) */
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
			case SU_CN_METEOR:				/* �C�k�n�b�J���e�I */
			case SU_CN_METEOR2:				/* �C�k�n�b�J���e�I(��) */
			case HN_METEOR_STORM_BUSTER:	/* ���e�I�X�g�[���o�X�^�[ */
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
			case WL_EARTHSTRAIN:    /* �A�[�X�X�g���C�� */
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
			case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
			case NPC_MAGMA_ERUPTION:	/* M�}�O�}�C���v�V���� */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				break;
			case LG_OVERBRAND_BRANDISH:		/* �I�[�o�[�u�����h(�ガ) */
				{
					int dir = path_calc_dir(src,skl->x,skl->y);
					map_foreachinshootpath(
						skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],3,5,(BL_CHAR|BL_SKILL),
						src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY,skill_castend_damage_id
					);
				}
				break;
			case GN_CRAZYWEED:		/* �N���C�W�[�E�B�[�h */
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS)) {
					range = skill_get_area(skl->skill_id,skl->skill_lv);
					map_foreachinarea(skill_delunit_by_ganbantein,
						src->m,skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_SKILL);
					skill_unitsetting(src,GN_CRAZYWEED_ATK,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			case RL_FIRE_RAIN:	/* �t�@�C�A�[���C�� */
				if(map_getcell(src->m,skl->x,skl->y,CELL_CHKPASS)) {
					if(atn_rand()%100 < 20 * skl->skill_lv) {
						range = skill_get_area(skl->skill_id,skl->skill_lv);
						map_foreachinarea(skill_delunit_by_ganbantein,src->m,skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_SKILL);
					}
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				}
				break;
			case NPC_WIDESUCK:		/* ���C�h�u���b�h */
				range = skill_get_area(skl->skill_id,skl->skill_lv);
				map_foreachinarea(skill_area_sub,skl->m,
					skl->x-range,skl->y-range,skl->x+range,skl->y+range,BL_CHAR,
					src,skl->skill_id,skl->skill_lv,tick,skl->flag|BCT_ENEMY|1,
					skill_castend_nodamage_id);
				break;
			case NW_HASTY_FIRE_IN_THE_HOLE:	/* �w�C�X�e�B�t�@�C�A�C���U�z�[�� */
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

/* �͈̓X�L���g�p���������������܂�
 * -------------------------------------------------------------------------
 */

/*==========================================
 * �X�L���g�p�i�r�������AID�w��j
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

	if( src->prev == NULL ) // prev�������̂͂���Ȃ́H
		return 0;

	src_sd  = BL_DOWNCAST( BL_PC,   src );
	src_md  = BL_DOWNCAST( BL_MOB,  src );
	src_hd  = BL_DOWNCAST( BL_HOM,  src );
	src_mcd = BL_DOWNCAST( BL_MERC, src );
	src_eld = BL_DOWNCAST( BL_ELEM, src );

	if(src_ud->skillid != SA_CASTCANCEL && !(src_ud->skillid == SO_SPELLFIST && (src_sd && (src_sd->skill_used.id == MG_FIREBOLT || src_sd->skill_used.id == MG_COLDBOLT || src_sd->skill_used.id == MG_LIGHTNINGBOLT)))) {
		if( src_ud->skilltimer != tid )	// �^�C�}ID�̊m�F
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

	// �X�L�������m�F
	do {
		int inf2;

		if(!target || target->prev == NULL)
			break;
		if(src->m != target->m || unit_isdead(src))
			break;

		// �E�H�[���I�u�t�H�O �s������
		if(tsc && (tsc->data[SC_FOGWALL].timer != -1 || tsc->data[SC_FOGWALLPENALTY].timer != -1) && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 75)
			break;

		// �ΎR�D �s������
		if(sc && sc->data[SC_VOLCANIC_ASH].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 50)
			break;

		// �s�K �s������
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

		// ���ق��Ԉُ�Ȃ�
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
			switch(src_ud->skillid) {	// �G�ȊO���^�[�Q�b�g�ɂ��Ă��ǂ��X�L��
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
					if(map[src->m].flag.town)	// �X���̂�PC�ɗL��
						fail_flag = 0;
					break;
			}
			if(fail_flag) {
				if(battle_check_target(src,target,BCT_ENEMY) <= 0)	// �މ�G�Ί֌W�`�F�b�N
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
			// �ː��`�F�b�N
			if(!path_search_long(NULL,src->m,src->x,src->y,target->x,target->y)) {
				if(src_sd && battle_config.skill_out_range_consume)
					skill_check_condition(&src_sd->bl,1);	// �A�C�e������
				break;
			}
		}

		// PC,HOM,MERC,ELEM�͎g�p�����`�F�b�N
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
		// �ړ����Ȃ���g�p�\�ȃX�L��
		if( src_ud->skillid != RA_WUGRIDER )	// �E�H�[�O���C�_�[
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
			if(src_sd->skill_used.id == TR_RETROSPECTION)	// ��z
				heal_ap *= 2;
			if(src_ud->skillid == SH_HOGOGONG_STRIKE && (pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO) || src_sd->sc.data[SC_TEMPORARY_COMMUNION].timer != -1))
				heal_ap += 1;
			if(src_ud->skillid == SH_HYUN_ROK_CANNON && (pc_checkskill(src_sd,SH_COMMUNE_WITH_HYUN_ROK) || src_sd->sc.data[SC_TEMPORARY_COMMUNION].timer != -1))
				heal_ap += 1;

			if(heal_ap > 0)
				pc_heal(src_sd,0,0,heal_ap,0);
		}

		// �G���A�`���b�g
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
		case 0:	/* �U���n */
		case 2:	/* ������΂��n */
			skill_castend_damage_id(src,target,src_ud->skillid,src_ud->skilllv,tick,0);
			break;
		case 1:	/* �x���n */
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
			    !(src_md && target->type == BL_MOB) )	// MOB��MOB�Ȃ�A���f�b�h�ł���
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

		// �X�L���g�p�Ŕ�������I�[�g�X�y��,�A�N�e�B�u�A�C�e��
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

	// �X�L���g�p���s
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
 * �X�L���g�p�i�r�������AID�w��U���n�j
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
			// skill_castend_id�ŋ������X�L���͂����œG�`�F�b�N
			if(skill_get_inf2(skillid) & INF2_ATTACK || skill_get_inf(skillid) & INF_ATTACK) {
				if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
					is_enemy = 0;
			}
			break;
	}

	map_freeblock_lock();

	switch(skillid)
	{
	/* ����U���n�X�L�� */
	case SM_BASH:			/* �o�b�V�� */
	case MC_MAMMONITE:		/* ���}�[�i�C�g */
	case KN_PIERCE:			/* �s�A�[�X */
	case KN_SPEARBOOMERANG:	/* �X�s�A�u�[������ */
	case TF_POISON:			/* �C���x�i�� */
	case TF_SPRINKLESAND:	/* ���܂� */
	case AC_CHARGEARROW:	/* �`���[�W�A���[ */
	case ASC_METEORASSAULT:	/* ���e�I�A�T���g */
	case RG_INTIMIDATE:		/* �C���e�B�~�f�C�g */
	case AM_ACIDTERROR:		/* �A�V�b�h�e���[ */
	case BA_MUSICALSTRIKE:	/* �~���[�W�J���X�g���C�N */
	case DC_THROWARROW:		/* ��� */
	case BA_DISSONANCE:		/* �s���a�� */
	case CR_HOLYCROSS:		/* �z�[���[�N���X */
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
	case LK_SPIRALPIERCE:		/* �X�p�C�����s�A�[�X */
	case LK_HEADCRUSH:			/* �w�b�h�N���b�V�� */
	case LK_JOINTBEAT:			/* �W���C���g�r�[�g */
	case ASC_BREAKER:			/* �\�E���u���C�J�[ */
	case HW_MAGICCRASHER:		/* �}�W�b�N�N���b�V���[ */
	case PA_SHIELDCHAIN:		/* �V�[���h�`�F�C�� */
	case WS_CARTTERMINATION:	/* �J�[�g�^�[�~�l�[�V���� */
	case CR_ACIDDEMONSTRATION:	/* �A�V�b�h�f�����X�g���[�V���� */
	case ITM_TOMAHAWK:			/* �g�}�z�[�N���� */
	case AS_VENOMKNIFE:			/* �x�i���i�C�t */
	case HT_PHANTASMIC:			/* �t�@���^�Y�~�b�N�A���[ */
	case CH_TIGERFIST:		/* ���Ռ� */
	case CH_CHAINCRUSH:		/* �A������ */
	case TK_DOWNKICK:	/* �l�����`���M */
	case TK_COUNTER:	/* �A�v�`���I�����M */
	case GS_FLING:			/* �t���C���O */
	case GS_TRIPLEACTION:	/* �g���v���A�N�V���� */
	case GS_BULLSEYE:		/* �u���Y�A�C */
	case GS_MAGICALBULLET:	/* �}�W�J���o���b�g */
	case GS_TRACKING:		/* �g���b�L���O */
	case GS_RAPIDSHOWER:	/* ���s�b�h�V�����[ */
	case GS_DUST:			/* �_�X�g */
	case GS_PIERCINGSHOT:	/* �s�A�[�V���O�V���b�g */
	case GS_FULLBUSTER:		/* �t���o�X�^�[ */
	case NJ_SYURIKEN:		/* �藠������ */
	case NJ_KUNAI:			/* �ꖳ���� */
	case NJ_ZENYNAGE:		/* �K���� */
	case NJ_KASUMIKIRI:		/* ���a�� */
	case HFLI_MOON:
	case HFLI_SBR44:
	case NPC_BLEEDING:		/* �o���U�� */
	case NPC_CRITICALWOUND:		/* �v�����U�� */
	case NPC_EXPULSION:		/* �G�N�X�p���V�I�� */
	case NPC_DRAGONBREATH:	/* M�h���S���u���X */
	case MS_BASH:
	case MA_CHARGEARROW:
	case ML_PIERCE:
	case ML_SPIRALPIERCE:
	case MER_CRASH:			/* �N���b�V�� */
	case RK_SONICWAVE:			/* �\�j�b�N�E�F�[�u */
	case RK_DRAGONBREATH:	/* �t�@�C�A�[�h���S���u���X */
	case RK_DRAGONBREATH_WATER:	/* �E�H�[�^�[�h���S���u���X */
	case AB_DUPLELIGHT_MELEE:	/* �O���C�A�����C�g */
	case RA_WUGBITE:		/* �E�H�[�O�o�C�g */
	case NC_BOOSTKNUCKLE:	/* �u�[�X�g�i�b�N�� */
	case NC_PILEBUNKER:		/* �p�C���o���J�[ */
	case NC_COLDSLOWER:		/* �R�[���h�X���[���[ */
	case NC_AXEBOOMERANG:	/* �A�b�N�X�u�[������ */
	case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
	case NPC_MAGMA_ERUPTION:	/* M�}�O�}�C���v�V���� */
	case LG_BANISHINGPOINT:	/* �o�j�V���O�|�C���g */
	case LG_SHIELDPRESS:	/* �V�[���h�v���X */
	case LG_OVERBRAND:		/* �I�[�o�[�u�����h */
	case LG_HESPERUSLIT:	/* �w�X�y���X���b�g */
	case SR_DRAGONCOMBO:	/* �o���r */
	case SR_FALLENEMPIRE:	/* ��Z���x */
	case SR_RIDEINLIGHTNING:	/* �����e */
	case WM_GREAT_ECHO:		/* �O���[�g�G�R�[ */
	case GN_DEMONIC_FIRE:	/* �f���j�b�N�t�@�C�A�[ */
	case GN_FIRE_EXPANSION_ACID:	/* �t�@�C�A�[�G�N�X�p���V����(���_) */
	case GN_SLINGITEM_RANGEMELEEATK:	/* �X�����O�A�C�e��(�������U��) */
	case KO_SETSUDAN:		/* �썰��f */
	case EL_WIND_SLASH:		/* �E�B���h�X���b�V�� */
	case EL_STONE_HAMMER:	/* �X�g�[���n���}�[ */
	case NPC_DISSONANCE:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NPC_GUIDEDATTACK:	/* �K�C�f�b�h�A�^�b�N */
		status_change_start(src,SC_INCHIT,status_get_dex(src)/2,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case KN_BRANDISHSPEAR:		/* �u�����f�B�b�V���X�s�A */
	case ML_BRANDISH:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_area_temp[1]++;
		break;
	case AC_DOUBLE:			/* �_�u���X�g���C�t�B���O */
	case MA_DOUBLE:
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case GS_DISARM:			/* �f�B�X�A�[�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AS_SONICBLOW:		/* �\�j�b�N�u���[ */
	case CG_ARROWVULCAN:		/* �A���[�o���J�� */
	case GC_CROSSIMPACT:	/* �N���X�C���p�N�g */
		{
			struct unit_data *ud = unit_bl2ud(src);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if(ud) {
				// �X�L�����[�V�����f�B���C�͍ő��3�b���炢�H
				int delay = status_get_adelay(src);
				ud->canmove_tick = tick + ( (delay>2000)? 3000: 6000*1000/(4000-delay) );
			}
		}
		break;
	case HT_POWER:			/* �s�[�X�g�X�g���C�t�B���O*/
		status_change_end(src,SC_DOUBLE,-1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case MO_INVESTIGATE:	/* ���� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case RG_RAID:			/* �T�v���C�Y�A�^�b�N */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
#ifndef PRE_RENEWAL
		status_change_start(bl,SC_RAID,7,0,0,0,skill_get_time(skillid,skilllv),0 );
#endif
		break;
	case RG_BACKSTAP:		/* �o�b�N�X�^�u */
		{
			int dir   = path_calc_dir(src,bl->x,bl->y);
			int t_dir = status_get_dir(bl);
			int dist  = unit_distance(src,bl);
			if((dist > 0 && !path_check_dir(dir,t_dir)) || bl->type == BL_SKILL) {
				sc = status_get_sc(src);
				if(sc && sc->data[SC_HIDING].timer != -1)
					status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)>0) { // �U�����󂯂��ڕW�͐U�����
					unit_setdir(bl, path_calc_dir(bl,src->x,src->y));
				}
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case MO_FINGEROFFENSIVE:	/* �w�e */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(md && !mob_is_pcview(md->class_)) {
			// �����ڂ�PC�łȂ��ꍇ�͉��̂��p�������Ă��܂��̂ŗ}������
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
	case MO_CHAINCOMBO:		/* �A�ŏ� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case TK_STORMKICK:	/* �t�F�I���`���M */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1]=src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;

	case TK_TURNKICK:	/* �g�������`���M */
		if(flag&1){
			/* �ʏ��� */
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
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			if(!battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔���MOB�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,skill_area_temp[2]-ar,skill_area_temp[3]-ar,skill_area_temp[2]+ar,skill_area_temp[3]+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case KN_CHARGEATK:	/* �`���[�W�A�^�b�N */
	case TK_JUMPKICK:	/* �e�B�I�A�v�`���M */
	case NJ_ISSEN:		/* ��M */
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
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
	case MO_COMBOFINISH:	/* �җ��� */
		sc = status_get_sc(src);
		/* �����N�̍���Ԃ̏ꍇ�͔͈͍U�� */
		if(sc && sc->data[SC_MONK].timer != -1) {
			if(flag&1) {
				if(bl->id != skill_area_temp[1])
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = bl->x;
				skill_area_temp[3] = bl->y;
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				map_foreachinarea(skill_area_sub,
					src->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case CH_PALMSTRIKE:		/* �ҌՍd঎R */
		clif_damage(src,bl,tick,status_get_amotion(src),0,-1,1,4,0,0);	// �U�����[�V�����̂ݓ����
		skill_addtimerskill(src,tick+1000,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		break;
	case MO_EXTREMITYFIST:	/* ���C���e�P�� */
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
	case NJ_KIRIKAGE:		/* �e�a�� */
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
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
						status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
						break;
					}
				}
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
		}
		break;
	/* ����n�͈͍U���X�L�� */
	case AC_SHOWER:			/* �A���[�V�����[ */
	case MA_SHOWER:
		{
			// �w��Z�����U�����S�ɂ��邽�߂�src�̑����p�ӂ���
			struct block_list pos;
			memset(&pos,0,sizeof(struct block_list));
			pos.m = bl->m;
			pos.x = skill_area_temp[2];
			pos.y = skill_area_temp[3];
			if( battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500) ) {
				int count = skill_get_blewcount(skillid,skilllv)|SAB_NOPATHSTOP;
				if(bl->x == pos.x && bl->y == pos.y)
					count |= 6<<20;		// �w����W�Ɠ���Ȃ琼�փm�b�N�o�b�N
				skill_blown(&pos,bl,count);
			}
		}
		break;
	case SM_MAGNUM:			/* �}�O�i���u���C�N */
	case MS_MAGNUM:
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				int x = skill_area_temp[2], y = skill_area_temp[3];
				int type;
				if(path_distance(bl->x,bl->y,x,y) > 1)
					type = 1;	// �O��
				else
					type = 0;	// ����
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500|type);
			}
		} else {
			int ar = (md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)? 4: skill_get_area(skillid,skilllv);

			/* �X�L���G�t�F�N�g�\�� */
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
	case NPC_SPLASHATTACK:	/* �X�v���b�V���A�^�b�N */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_SPLASHER:		/* �x�i���X�v���b�V���[ */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x500|skill_area_temp[0]);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			//���U�͈͂�3x3 �U���͈͂�5x5
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar-1,bl->y-ar-1,bl->x+ar-1,bl->y+ar-1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_GRIMTOOTH:		/* �O�����g�D�[�X */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
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
	case MC_CARTREVOLUTION:	/* �J�[�g���{�����[�V���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
			{
				if(bl->x == skill_area_temp[2] && bl->y == skill_area_temp[3]) {
					skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// �^�[�Q�b�g�Ɠ�����W�Ȃ琼�փm�b�N�o�b�N
				} else {
					struct block_list pos;
					memset(&pos,0,sizeof(pos));
					pos.m = bl->m;
					pos.x = skill_area_temp[2];
					pos.y = skill_area_temp[3];
					skill_blown(&pos,bl,skill_area_temp[4]);		// �^�[�Q�b�g�Ƃ̈ʒu�֌W�Ŕ�΂����������߂�
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int x = bl->x, y = bl->y;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// ���ɋ����m�b�N�o�b�N

			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KN_BOWLINGBASH:	/* �{�E�����O�o�b�V�� */
	case MS_BOWLINGBASH:
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id!=skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int i,c,dir;	/* ���l���畷���������Ȃ̂ŊԈ���Ă�\���偕������������������ */
			int ar = skill_get_area(skillid,skilllv);
			/* �܂��^�[�Q�b�g�ɍU���������� */
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
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY ,
					skill_area_sub_count);
				if(skill_area_temp[0] > 1)
					break;
			}
			unit_stop_walking(bl,2);	// �Ō�Ƀ_���[�W�f�B���C������
			skill_area_temp[1] = bl->id;
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case MO_BALKYOUNG:
		{
			int ar = skill_get_area(skillid,skilllv);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			map_foreachinarea(skill_balkyoung,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),src,bl);
		}
		break;
	case KN_SPEARSTAB:		/* �X�s�A�X�^�u */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
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
			/* �܂��^�[�Q�b�g�ɍU���������� */
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
	case SN_SHARPSHOOTING:			/* �V���[�v�V���[�e�B���O */
	case MA_SHARPSHOOTING:
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],12,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case GS_SPREADATTACK:	/* �X�v���b�h�A�^�b�N */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			map_foreachinarea(skill_area_sub,
				src->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NJ_HUUMA:		/* �����藠������ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_EARTHQUAKE:		/* �A�[�X�N�G�C�N */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				skill_addtimerskill(src,tick+200,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+400,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+600,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
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
	case NPC_FIREBREATH:		/* �t�@�C�A�u���X */
	case NPC_ICEBREATH:		/* �A�C�X�u���X */
	case NPC_THUNDERBREATH:		/* �T���_�[�u���X */
	case NPC_ACIDBREATH:		/* �A�V�b�h�u���X */
	case NPC_DARKNESSBREATH:	/* �_�[�N�l�X�u���X */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case NPC_PULSESTRIKE:		/* �p���X�X�g���C�N */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_HELLJUDGEMENT:		/* �w���W���b�W�����g */
	case NPC_HELLJUDGEMENT2:		/* �f���j�b�N�w���W���b�W�����g */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_VAMPIRE_GIFT:		/* ���@���p�C�A���b�N�^�b�` */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			int heal = battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			if(heal) {
				clif_skill_nodamage(src,src,AL_HEAL,heal,1);
				battle_heal(NULL,src,heal,0,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_PULSESTRIKE2:		/* �p���X�X�g���C�NII */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,-1,src->x,src->y,tick);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_DANCINGBLADE:		/* �_���V���O�u���C�h */
		clif_skill_poseffect(src,skillid,-1,bl->x,bl->y,tick);
		skill_addtimerskill(src,tick+150,bl->id,0,0,NPC_DANCINGBLADE_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case NPC_DARKPIERCING:		/* �_�[�N�s�A�[�V���O */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		}
		break;
	case NPC_VENOMIMPRESS:		/* M�x�i���C���v���X */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_IGNITIONBREAK:	/* M�C�O�j�b�V�����u���C�N */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src, src, skillid, skilllv, 1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_POISON_BUSTER:		/* M�|�C�Y���o�X�^�[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �^�[�Q�b�g�ɍU����������(�X�L���G�t�F�N�g�\��) */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			/* �^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_WIDECRITICALWOUND:		/* ���C�h�N���e�B�J���E�[���Y */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_KILLING_AURA:	/* �L�����O�I�[�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	/* ���@�n�X�L�� */
	case MG_SOULSTRIKE:			/* �\�E���X�g���C�N */
	case NPC_DARKSTRIKE:		/* �_�[�N�X�g���C�N */
	case MG_COLDBOLT:			/* �R�[���h�{���g */
	case MG_FIREBOLT:			/* �t�@�C�A�[�{���g */
	case MG_LIGHTNINGBOLT:		/* ���C�g�j���O�{���g*/
	case WZ_EARTHSPIKE:			/* �A�[�X�X�p�C�N */
	case AL_HEAL:				/* �q�[�� */
	case AL_HOLYLIGHT:			/* �z�[���[���C�g */
	case WZ_JUPITEL:			/* ���s�e���T���_�[ */
	case NPC_DARKTHUNDER:		/* �_�[�N�T���_�[ */
	case NPC_MAGICALATTACK:		/* ���@�Ō��U�� */
	case PR_ASPERSIO:			/* �A�X�y���V�I */
	case NJ_KOUENKA:			/* �g���� */
	case NJ_HYOUSENSOU:			/* �X�M�� */
	case NJ_HUUJIN:				/* ���n */
	case AB_RENOVATIO:			/* ���m���@�e�B�I */
	case AB_HIGHNESSHEAL:		/* �n�C�l�X�q�[�� */
	case AB_ADORAMUS:			/* �A�h�����X */
	case AB_DUPLELIGHT_MAGIC:	/* �~���A�����C�g */
	case WL_TETRAVORTEX_FIRE:	/* �e�g���{���e�b�N�X(��) */
	case WL_TETRAVORTEX_WATER:	/* �e�g���{���e�b�N�X(��) */
	case WL_TETRAVORTEX_WIND:	/* �e�g���{���e�b�N�X(��) */
	case WL_TETRAVORTEX_GROUND:	/* �e�g���{���e�b�N�X(�n) */
	case LG_RAYOFGENESIS:		/* ���C�I�u�W�F�l�V�X */
	case WM_METALICSOUND:		/* ���^���b�N�T�E���h */
	case EL_FIRE_ARROW:			/* �t�@�C�A�[�A���[ */
	case EL_ICE_NEEDLE:			/* �A�C�X�j�[�h�� */
	case NPC_RAYOFGENESIS:		/* M���C�I�u�W�F�l�V�X */
	case IG_JUDGEMENT_CROSS:	/* �W���b�W�����g�N���X */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case ALL_RESURRECTION:		/* ���U���N�V���� */
	case PR_TURNUNDEAD:			/* �^�[���A���f�b�h */
		if(battle_check_undead(status_get_race(bl),status_get_elem_type(bl))) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			map_freeblock_unlock();
			return 1;
		}
		break;
	case HVAN_CAPRICE:		/* �J�v���X */
		{
			static const int caprice[4] = { MG_COLDBOLT,MG_FIREBOLT,MG_LIGHTNINGBOLT,WZ_EARTHSPIKE};
			battle_skill_attack(BF_MAGIC,src,src,bl,caprice[atn_rand()%4],skilllv,tick,flag);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;
	case CG_TAROTCARD:		/* �^���̃^���b�g�J�[�h */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_TRICKDEAD].timer != -1) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		skill_tarot_card_of_fate(src,bl,skillid,skilllv,tick,0);
		break;
	case MG_FROSTDIVER:		/* �t���X�g�_�C�o�[ */
		{
			int damage;

			sc = status_get_sc(bl);
			if(sc && sc->data[SC_FREEZE].timer != -1) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			damage = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(status_get_hp(bl) > 0 && damage > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv*300+3500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case WZ_WATERBALL:			/* �E�H�[�^�[�{�[�� */
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

	case PR_BENEDICTIO:			/* ���̍~�� */
		{
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(bl->type == BL_MOB || !map[bl->m].flag.normal)
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;

	case SL_SMA:				/* �G�X�} */
	case SL_STUN:				/* �G�X�g�� */
	case SL_STIN:				/* �G�X�e�B�� */
		if(sd && bl->type != BL_MOB && !battle_config.allow_es_magic_all)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		else
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	/* ���@�n�͈͍U���X�L�� */
	case MG_NAPALMBEAT:			/* �i�p�[���r�[�g */
	case MG_FIREBALL:			/* �t�@�C�A�[�{�[�� */
	case WZ_SIGHTRASHER:		/* �T�C�g���b�V���[ */
	case HW_NAPALMVULCAN:		/* �i�p�[���o���J�� */
	case AB_JUDEX:				/* �W���f�b�N�X */
	case WL_SOULEXPANSION:		/* �\�E���G�N�X�p���V���� */
	case SO_POISON_BUSTER:		/* �|�C�Y���o�X�^�[ */
	case SO_VARETYR_SPEAR:		/* ���F���`���[���X�s�A */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				int count;
				if(skillid == MG_FIREBALL) {
					/* �t�@�C�A�[�{�[���Ȃ璆�S����̋������v�Z */
					count = path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]);
				} else {
					count = skill_area_temp[0];
				}
				if(skillid != HW_NAPALMVULCAN && skillid != AB_JUDEX && skillid != WL_SOULEXPANSION && skillid != WL_CRIMSONROCK)
					count |= 0x0500;
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,count);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int srcflg = 0;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			switch (skillid) {
				case MG_NAPALMBEAT:
				case HW_NAPALMVULCAN:
					/* �i�p�[���r�[�g�E�i�p�[���o���J���͕��U�_���[�W�Ȃ̂œG�̐��𐔂��� */
					map_foreachinarea(skill_area_sub,
							bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick,flag|BCT_ENEMY,
							skill_area_sub_count);
					break;
				case MG_FIREBALL:
				case AB_JUDEX:				/* �W���f�b�N�X */
				case WL_SOULEXPANSION:		/* �\�E���G�N�X�p���V���� */
				case SO_POISON_BUSTER:	/* �|�C�Y���o�X�^�[ */
				case SO_VARETYR_SPEAR:	/* ���F���`���[���X�s�A */
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case WZ_SIGHTRASHER:
					srcflg = 1;
					bl = src;
					status_change_end(src,SC_SIGHT,-1);
					break;
			}
			if(srcflg) {
				/* �X�L���G�t�F�N�g�\�� */
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			} else {
				/* �^�[�Q�b�g�ɍU����������(�X�L���G�t�F�N�g�\��) */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
			}
			/* �^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
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
	case WZ_FROSTNOVA:			/* �t���X�g�m���@ */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_HYOUSYOURAKU:		/* �X������ */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_RAIGEKISAI:			/* ������ */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_KAMAITACHI:			/* �� */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : flag));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],skill_get_fixed_range(src,skillid,skilllv),skill_get_area(skillid,skilllv),
				(BL_CHAR|BL_SKILL),src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;

	/* ���̑� */
	case TF_THROWSTONE:			/* �Γ��� */
	case PA_PRESSURE:			/* �v���b�V���[ */
	case SN_FALCONASSAULT:			/* �t�@���R���A�T���g */
	case GN_HELLS_PLANT_ATK:	/* �w���Y�v�����g */
	case NPC_DARKBREATH:
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case HT_BLITZBEAT:			/* �u���b�c�r�[�g */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if(flag&0xf00000) {
				map_foreachinarea(skill_area_sub,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY,skill_area_sub_count);
			}
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
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

	case CR_GRANDCROSS:			/* �O�����h�N���X */
	case NPC_GRANDDARKNESS:			/* �O�����h�_�[�N�l�X */
		{
			struct unit_data *ud = unit_bl2ud(src);
			if(status_check_no_magic_damage(src))
				break;
			status_change_start(src,SC_STRIPSHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			/* �X�L�����j�b�g�z�u */
			skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
			if(ud)
				ud->canmove_tick = tick + 900;
		}
		break;
	case PF_SOULBURN:		/* �\�E���o�[�� */
		if(bl->type == BL_PC) {
			struct block_list *dstbl;
			int sp, rate;
			if(status_check_no_magic_damage(bl))
				break;
			if(sd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk)
				break;
			rate = (skilllv >= 5)? 70: 10 * skilllv + 30;
			if(atn_rand() % 100 >= rate) {
				dstbl = src;	// �����ɑ΂��ă_���[�W
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			} else {
				dstbl = bl;
			}
			clif_skill_nodamage(src,dstbl,skillid,skilllv,1);
			sp = status_get_sp(dstbl);
			// SP��0�ɂ���
			if(dstbl->type == BL_PC)
				unit_heal(dstbl,0,-sp,0,0);
			if(skilllv >= 5) {
				// SP*2�̃_���[�W��^����(MDEF�Ōv�Z)
				int damage = sp * 2 * (100 - status_get_mdef(dstbl)) / 100 - status_get_mdef2(dstbl);
				if(damage < 1)
					damage = 1;
				battle_damage(src,dstbl,damage,skillid,skilllv,0);
			}
			if(sd)
				sd->skillstatictimer[PF_SOULBURN] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case NPC_SELFDESTRUCTION2:	/* ����2 */
		if(flag&1) {
			if(bl->type == BL_PC && !map[src->m].flag.pvp && !map[src->m].flag.gvg)
				break;
		}
		// fall through
	case NPC_SELFDESTRUCTION:	/* ���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
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
				int ar = skill_get_area(skillid,skilllv);
				if(skillid == NPC_SELFDESTRUCTION2 && md->hp >= status_get_max_hp(&md->bl)) {
					// ����2��HP�S�񕜏�ԂȂ甭�����Ȃ�
					break;
				}
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = md->hp;
				clif_skill_nodamage(src,src,NPC_SELFDESTRUCTION,-1,1);
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ALL|1,
					skill_castend_damage_id);
				mob_damage(NULL,md,md->hp,1);
			}
		}
		break;
	case HVAN_EXPLOSION:	/* �o�C�I�G�N�X�v���[�W���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
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
	case MH_NEEDLE_OF_PARALYZE:	/* �j�[�h���I�u�p�����C�Y */
	case MH_SONIC_CRAW:			/* �\�j�b�N�N���[ */
	case MH_SILVERVEIN_RUSH:	/* �V���o�[�x�C�����b�V�� */
	case MH_MIDNIGHT_FRENZY:	/* �~�b�h�i�C�g�t�����W */
	case MH_STAHL_HORN:			/* �V���^�[���z�[�� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_TINDER_BREAKER:	/* �e�B���_�[�u���C�J�[ */
		{
			int dist = unit_distance(src,bl);
			if(hd && !map[hd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - hd->bl.x;
				int dy = bl->y - hd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,hd->bl.x,hd->bl.y,hd->bl.x+dx,hd->bl.y+dy,1) == -1) {
					dx = bl->x - hd->bl.x;
					dy = bl->y - hd->bl.y;
					if(path_search(NULL,src->m,hd->bl.x,hd->bl.y,hd->bl.x+dx,hd->bl.y+dy,1) == -1) {
						clif_skill_fail(hd->msd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				hd->ud.to_x = hd->bl.x + dx;
				hd->ud.to_y = hd->bl.y + dy;
				clif_skill_poseffect(&hd->bl,skillid,skilllv,hd->bl.x,hd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
				clif_move(&hd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				hd->ud.attackabletime = hd->ud.canmove_tick = tick + hd->speed * ((dx > dy)? dx:dy);
				if(hd->ud.canact_tick < hd->ud.canmove_tick)
					hd->ud.canact_tick = hd->ud.canmove_tick;
				unit_movepos(&hd->bl,hd->ud.to_x,hd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			if(hd && hd->spiritball >= 1) {
				hd->spiritball--;
			}
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_CBC:	/* C.B.C */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_TINDER_BREAKER].timer != -1) {
			int duration = status_get_str(src) / 7 - status_get_str(bl) / 10;
			int val3 = 50 * skilllv * status_get_lv(src) / 150;	// HP�����l(�b��)
			int val4 = 10 + (status_get_dex(src) + status_get_lv(src)) / 15;	// SP�����l(�b��)
			if(duration < skilllv)
				duration = skilllv;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_end(bl,SC_TINDER_BREAKER,-1);
			status_change_start(bl,SC_CBC,skilllv,0,val3,val4,duration*1000,0);
			if(hd && hd->spiritball >= 1) {
				status_change_start(src,SC_COMBO,skillid,skilllv,0,0,1000,0);
				clif_combo_delay(src,1000);
			}
		}
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_EQC:	/* E.Q.C */
		{
			int t_hp = status_get_hp(bl);
			status_change_start(bl,SC_EQC,skilllv,t_hp,0,0,skill_get_time2(skillid,skilllv),0);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_ERASER_CUTTER:	/* �C���C�T�[�J�b�^�[ */
	case MH_XENO_SLASHER:		/* �[�m�X���b�V���[ */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_HEILIGE_STANGE:	/* �n�C���G�[�W���X�^���W�F */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_MAGMA_FLOW:	/* �}�O�}�t���[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case NJ_TATAMIGAESHI:	/* ���Ԃ� */
		status_change_start(src,SC_TATAMIGAESHI,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_KAENSIN:	/* �Ή��w */
		bl = src;
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_BAKUENRYU:	/* �����w */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case GS_DESPERADO:	/* �f�X�y���[�h */
		{
			int tmpx, tmpy, i, num;
			int fa = 0;
			int ar = skill_get_area(skillid,skilllv);
			bl = src;
			sc = status_get_sc(src);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// �e�̏���
					break;
			}
			num = skill_get_num(skillid,skilllv);
			if(sc && sc->data[SC_FALLEN_ANGEL].timer != -1)
				fa = 1;
			for(i=0; i<num; i++) {
				tmpx = src->x + (atn_rand()%(ar*2+1) - ar);
				tmpy = src->y + (atn_rand()%(ar*2+1) - ar);
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,fa);
			}
			status_change_end(src,SC_FALLEN_ANGEL,-1);
		}
		break;

	/* HP�z��/HP�z�����@ */
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
	case RK_HUNDREDSPEAR:	/* �n���h���b�h�X�s�A */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < (10 + 3*skilllv)) {
			skill_blown(src,bl,6|SAB_NOPATHSTOP);
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case RK_IGNITIONBREAK:	/* �C�O�j�b�V�����u���C�N */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case RK_WINDCUTTER:		/* �E�B���h�J�b�^�[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			}
		}
		break;
	case RK_CRUSHSTRIKE:	/* �N���b�V���X�g���C�N */
		if(sd && battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag))
			pc_break_equip(sd, LOC_RARM);
		break;
	case RK_STORMBLAST:		/* �X�g�[���u���X�g */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
					skill_blown(src,bl,7 - path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case RK_PHANTOMTHRUST:	/* �t�@���g���X���X�g */
	case NPC_PHANTOMTHRUST:	/* M�t�@���g���X���X�g */
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
	case GC_DARKILLUSION:	/* �_�[�N�C�����[�W���� */
	case RA_WUGSTRIKE:		/* �E�H�[�O�X�g���C�N */
	case LG_PINPOINTATTACK:	/* �s���|�C���g�A�^�b�N */
	case KO_JYUMONJIKIRI:	/* �\�����a�� */
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
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
	case GC_COUNTERSLASH:	/* �J�E���^�[�X���b�V�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_WEAPONCRUSH:	/* �E�F�|���N���b�V�� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_castend_nodamage_id(src,bl,RG_STRIPWEAPON,skilllv,tick,0);	// �X�g���b�v�E�F�|�����s
		break;
	case GC_VENOMPRESSURE:	/* �x�i���v���b�V���[ */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			sc = status_get_sc(src);
			if(sc && sc->data[SC_POISONINGWEAPON].timer != -1) {
				if(atn_rand() % 10000 < status_change_rate(bl,sc->data[SC_POISONINGWEAPON].val2,7000+skilllv*500,status_get_lv(src)))
					status_change_start(bl,sc->data[SC_POISONINGWEAPON].val2,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				else if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				status_change_end(src,SC_POISONINGWEAPON,-1);
			}
		}
		break;
	case GC_PHANTOMMENACE:	/* �t�@���g�����i�X */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl)) {		// �f�B�e�N�g���ʂŖ\���������
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_ROLLINGCUTTER:	/* ���[�����O�J�b�^�[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_ROLLINGCUTTER].timer == -1) {
					status_change_start(src,SC_ROLLINGCUTTER,1,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_ROLLINGCUTTER].val1 < 10) {
					int rolling = ++sc->data[SC_ROLLINGCUTTER].val1;
					status_change_start(src,SC_ROLLINGCUTTER,rolling,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}

			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_CROSSRIPPERSLASHER:	/* �N���X���b�p�[�X���b�V���[ */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_end(src,SC_ROLLINGCUTTER,-1);
		break;
	case GC_DARKCROW:	/* �_�[�N�N���[ */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WL_FROSTMISTY:		/* �t���X�g�~�X�e�B */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				if(path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y)) {
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				}
				if(atn_rand() % 10000 < 2500 + skilllv * 500)
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_poseffect(src,skillid,skilllv,src->x,src->y,tick);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_JACKFROST:		/* �W���b�N�t���X�g */
	case NPC_JACKFROST:		/* M�W���b�N�t���X�g */
		if(flag&1) {
			if(!path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y))
				break;
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_DRAINLIFE:		/* �h���C�����C�t */
		{
			int heal = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(heal > 0 && atn_rand() % 100 < 70 + skilllv * 5) {
				heal = heal * (skilllv * 8 * status_get_lv(src) / 100) / 100;
				unit_heal(src,heal,0,0,1);
			}
		}
		break;
	case WL_CRIMSONROCK:		/* �N�����]�����b�N */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_HELLINFERNO:		/* �w���C���t�F���m */
		if(battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand() % 10000 < 5500 + skilllv * 500) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		skill_addtimerskill(src,tick + 300,bl->id,0,0,WL_HELLINFERNO,skilllv,0,(0x0f<<20)|0x500|flag|1);
		break;
	case WL_CHAINLIGHTNING:		/* �`�F�[�����C�g�j���O */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_addtimerskill(src,tick + 650,bl->id,0,0,WL_CHAINLIGHTNING_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case RA_ARROWSTORM:		/* �A���[�X�g�[�� */
	case NPC_ARROWSTORM:	/* M�A���[�X�g�[�� */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_AIMEDBOLT:      /* �G�C���h�{���g */
		{
			int div_ = 2 + status_get_size(bl) + atn_rand()%2;
			if(sd && !battle_delarrow(sd,div_,skillid))   // ��̏���
				break;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,div_);
		}
		break;
	case RA_WUGDASH:		/* �E�H�[�O�_�b�V�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_SENSITIVEKEEN:	/* �s�q�Țk�o */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl)) {		// �f�B�e�N�g���ʂŖ\���������
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
				if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2)		// �⑫���̃A���N���X�l�A�͏��O
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
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
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
	case NC_VULCANARM:		/* �o���J���A�[�� */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_FLAMELAUNCHER:	/* �t���C���X���[���[ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_ARMSCANNON:		/* �A�[���Y�L���m�� */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_SELFDESTRUCTION:	/* �Z���t�f�B�X�g���N�V���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);

			if(sd) {
				if(!pc_isgear(sd)) {
					clif_skill_fail(sd,skillid,SKILLFAIL_MADOGEAR,0,0);
					break;
				}
			}

			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				/* �����M�A������ */
				pc_setoption(sd, (sd->sc.option & ~OPTION_MADOGEAR));
				sd->status.sp = 0;
				clif_updatestatus(sd,SP_SP);
			}
		}
		break;
	case NC_AXETORNADO:	/* �A�b�N�X�g���l�[�h */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
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
	case NC_POWERSWING:		/* �p���[�X�C���O */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < 5 * skilllv) {
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case NC_DISJOINT:		/* FAW���� */
		if(bl->type == BL_MOB) {
			struct mob_data* tmd = (struct mob_data*)bl;
			if(tmd->class_ >= 2042 && tmd->class_ <= 2046 && tmd->master_id != 0) {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, skilllv, 0);
				mob_damage(src, tmd, tmd->hp, 2);
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case SC_FATALMENACE:	/* �t�F�C�^�����i�X */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SC_TRIANGLESHOT:	/* �g���C�A���O���V���b�g */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand()%10000 < 100 + 100 * skilllv) {
				skill_blown(src,bl,5|SAB_REVERSEBLOW|SAB_NOPATHSTOP);
			}
		}
		break;
	case SC_FEINTBOMB:		/* �t�F�C���g�{�� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		break;
	case LG_CANNONSPEAR:	/* �L���m���X�s�A */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],10,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case LG_RAGEBURST:		/* ���C�W�o�[�X�g�A�^�b�N */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_FORCEOFVANGUARD].timer != -1 && sc->data[SC_FORCEOFVANGUARD].val4 > 0) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			sc->data[SC_FORCEOFVANGUARD].val4 = 0;
			if(sd)
				clif_mshield(sd,0);
		}
		break;
	case LG_SHIELDSPELL:	/* �V�[���h�X�y�� */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		else if(flag&2) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case LG_OVERBRAND_BRANDISH:		/* �I�[�o�[�u�����h(�ガ) */
		{
			int dist = unit_distance(src,bl);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv) + dist) {
				battle_skill_attack(BF_WEAPON,src,src,bl,LG_OVERBRAND_PLUSATK,skilllv,tick,0x0500);
			}
		}
		break;
	case LG_MOONSLASHER:	/* ���[���X���b�V���[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case LG_EARTHDRIVE:		/* �A�[�X�h���C�u */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
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
	case SR_SKYNETBLOW:	/* �V���n�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_EARTHSHAKER:	/* �n���k */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl))		// �f�B�e�N�g���ʂŖ\���������
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|1);
				else
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag&~1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_TIGERCANNON:	/* �j�C */
	case SR_GATEOFHELL:		/* �����j���� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
		break;
	case SR_KNUCKLEARROW:	/* �C���g�e */
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
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
	case SR_WINDMILL:	/* ������ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case SR_RAMPAGEBLASTER:		/* ���C�U�e */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_GENTLETOUCH_QUIET:	/* �_�� -��- */
		if(atn_rand()%100 < skilllv * 5 + (status_get_lv(src) + status_get_dex(src)) / 10) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case SR_HOWLINGOFLION:	/* ���q�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case WM_SOUND_OF_DESTRUCTION:	/* �T�E���h�I�u�f�B�X�g���N�V���� */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_CART_TORNADO:	/* �J�[�g�g���l�[�h */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case GN_CARTCANNON:		/* �J�[�g�L���m�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_BLOOD_SUCKER:	/* �u���b�h�T�b�J�[ */
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
	case GN_SPORE_EXPLOSION:	/* �X�|�A�G�N�X�v���[�W���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_ILLUSIONDOPING:	/* �C�����[�W�����h�[�s���O */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
			}
			if( atn_rand() % 10000 < 9000-1000*skilllv )
				status_change_start(bl,SC_ILLUSIONDOPING,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,9000-1000*skilllv,status_get_lv(src)) )
				status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20));
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_BAKURETSU:		/* ����ꖳ */
	case KO_HUUMARANKA:		/* �����藠�� -����- */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_HAPPOKUNAI:		/* �����ꖳ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
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
	case KO_MUCHANAGE:	/* �������� */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		break;
	case KO_MAKIBISHI:			/* �T�H */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case KO_KAIHOU:				/* �p�� -���- */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case RL_MASS_SPIRAL:		/* �}�X�X�p�C���� */
	case RL_BANISHING_BUSTER:	/* �o�j�V���O�o�X�^�[ */
	case RL_AM_BLAST:			/* �A���`�}�e���A���u���X�g */
	case RL_SLUGSHOT:			/* �X���b�O�V���b�g */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case RL_B_FLICKER_ATK:		/* �o�C���h�g���b�v(����) */
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		status_change_end(bl, SC_B_TRAP, -1);
		break;
	case RL_S_STORM:		/* �V���b�^�[�X�g�[�� */
	case RL_D_TAIL:			/* �h���S���e�C�� */
	case RL_HAMMER_OF_GOD:	/* �n���}�[�I�u�S�b�h */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int tx = bl->x, ty = bl->y;
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			if(skillid == RL_HAMMER_OF_GOD)
				pc_delcoin(sd,MAX_COIN,0);
		}
		break;
	case RL_QD_SHOT:	/* �N�C�b�N�h���[�V���b�g */
		if(flag&0x10) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_C_MARKER].timer != -1 && sc->data[SC_C_MARKER].val2 == src->id && skill_area_temp[1] != bl->id)
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int div_ = 1;
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				div_ += sd->status.job_level / 20;
				if(div_ > 4)
					div_ = 4;
				if(!battle_delarrow(sd,div_,0))
					break;
			}
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|div_);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|0x10|div_,
				skill_castend_damage_id);
			status_change_end(src, SC_QD_SHOT_READY, -1);
		}
		break;
	case RL_FIREDANCE:	/* �t�@�C�A�[�_���X */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
		}
		break;
	case RL_H_MINE:		/* �n�E�����O�}�C�� */
		if(flag&2) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag|0x500);
		} else if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_H_MINE].timer != -1 && sc->data[SC_H_MINE].val2 == src->id) {
				int ar = skill_get_area(skillid,skilllv);
				status_change_start(bl,SC_H_MINE_SPLASH,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				map_foreachinarea(skill_area_sub,bl->m,
					bl->x-ar,bl->y-ar,
					bl->x+ar,bl->y+ar,
					BL_CHAR,src,skillid,sc->data[SC_H_MINE].val1,tick,flag|BCT_ENEMY|2,
					skill_castend_damage_id);
				status_change_end(bl,SC_H_MINE,-1);
			}
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RL_R_TRIP:	/* ���E���h�g���b�v */
		if(flag&1) {
			int dist = unit_distance(src,bl);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv) + dist) {
				battle_skill_attack(BF_WEAPON,src,src,bl,RL_R_TRIP_PLUSATK,skilllv,tick,(0x0f<<20)|flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
		}
		break;
	case SJ_FULLMOONKICK:		/* �����r */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			status_change_end(src, SC_NEWMOON, -1);
			/* �X�L���G�t�F�N�g�\�� */
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
	case SJ_NEWMOONKICK:	/* �񌎋r */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				status_change_end(src, GetSkillStatusChangeTable(skillid), -1);
			} else {
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SJ_FLASHKICK:	/* �M���r */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag) > 0) {
			if(sd) {
				int i;

				sc = status_get_sc(bl);
				if(sc && sc->data[SC_FLASHKICK].timer != -1 && sc->data[SC_FLASHKICK].val2 != src->id)
					status_change_end(bl, SC_FLASHKICK, -1);

				for(i=0; i<MAX_STELLAR_MARKS; i++) {
					if(sd->stellar_mark[i] == bl->id || sd->stellar_mark[i] == 0)
						break;
				}
				if(i < MAX_STELLAR_MARKS) {
					sd->stellar_mark[i] = bl->id;
					status_change_start(bl,SC_FLASHKICK,skilllv,src->id,i,0,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SJ_STAREMPEROR:		/* ����~�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_DIMENSION].timer != -1){
					status_change_end(src,SC_DIMENSION,-1);
					status_change_start(src,SC_DIMENSION2,skilllv,0,0,status_get_max_sp(src)*2,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SJ_NOVAEXPLOSING:	// �V������
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc) {
			if( sc->data[SC_DIMENSION].timer != -1 ){
				status_change_end(src,SC_DIMENSION,-1);
				status_change_start(src,SC_DIMENSION1,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			}
			else if( sc->data[SC_DIMENSION1].timer != -1 ){
				//Do nothing
			}
			else{
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SJ_SOLARBURST:		/* ���z���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
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
	case SJ_PROMINENCEKICK:	/* �g���r */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_FALLINGSTAR_ATK:	/* ��������(�U��) */
		if(flag&1) {
			sc = status_get_sc(bl);
			if (sc && sc->data[SC_FLASHKICK].timer != -1 && sc->data[SC_FLASHKICK].val2 == src->id) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_skill_attack(BF_WEAPON, src, src, bl, skillid, skilllv, tick, flag);
				skill_addtimerskill(src,tick+300,bl->id,0,0,SJ_FALLINGSTAR_ATK2,skilllv,0,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_FALLINGSTAR_ATK2:	/* ��������(�ǌ�) */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SP_CURSEEXPLOSION:		// ���씚��
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SP_SPA:				// �G�X�p
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SP_SHA:			// �G�X�n
		if(flag&1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,SC_SMA,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(bl->type != BL_MOB && !battle_config.allow_es_magic_all)
				status_change_start(src,SC_STUN,skilllv,0,0,0,5000,0);
		}
		break;
	case SP_SWHOO:			// �G�X�t
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				battle_config.allow_es_magic_all? (BL_CHAR|BL_SKILL): BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sc && sc->data[SC_SWHOO].timer != -1)
				status_change_end(bl,SC_SWHOO,-1);
			status_change_start(src,SC_SMA,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SP_SOULEXPLOSION:		// ���̕���
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SU_BITE:			// ���݂�
	case SU_SCAROFTAROU:	// �^���E�̏�
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SU_SCRATCH:	// �Ђ�����
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_PICKYPECK:	// �s�b�L�˂�
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if((int)((atn_bignumber)status_get_hp(bl) * 100 / status_get_max_hp(bl)) <= 20 + skilllv * 10) {	// �G��HP�����ȉ��Ȃ�
			battle_skill_attack(BF_WEAPON,src,src,bl,SU_PICKYPECK_DOUBLE_ATK,skilllv,tick,flag);
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// �L�����b�g�r�[�g
	case SU_LUNATICCARROTBEAT2:	// �L�����b�g�r�[�g(�X�^��)
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,SU_LUNATICCARROTBEAT,skilllv,tick,flag) > 0) {
				if(skillid == SU_LUNATICCARROTBEAT2 && atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,5000,status_get_lv(src)))
					status_change_pretimer(&sd->bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �܂��^�[�Q�b�g�ɍU���������� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* ���̌�^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_SVG_SPIRIT:	// �T�x�[�W�̍�
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
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
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case SU_SV_STEMSPEAR:	/* �}�^�^�r�����X */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NPC_MAXPAIN_ATK:		/* �}�b�N�X�y�C�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MISC,src,src,bl,NPC_MAXPAIN_ATK,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_SERVANTWEAPON_ATK:		/* �T�[���@���g�E�F�|��(�U��) */
	case SHC_DANCING_KNIFE:			/* �_���V���O�i�C�t */
	case MT_A_MACHINE:			/* �U�����u�L���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_SERVANT_W_PHANTOM:		/* �T�[���@���g�E�F�|���F�t�@���g�� */
		if(flag&0x20) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(flag&0x0f));
		} else if(flag&0x10) {
			// �T�[���@���g�T�C������
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_SERVANT_SIGN].timer != -1) {
				/* �Ώۂ̓G���͂ɏ������s�� */
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|0x20|(flag&0x0f),
					skill_castend_damage_id);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			int num = 1;
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			if(sd) {
				num = sd->ball.num;
				pc_delball(sd,sd->ball.num,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|num,
				skill_castend_damage_id);

		}
		break;
	case DK_SERVANT_W_DEMOL:		/* �T�[���@���g�E�F�|���F�f�����b�V���� */
		if(flag&0x10) {
			// �T�[���@���g�T�C������
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_SERVANT_SIGN].timer != -1) {
				/* �ʂɃ_���[�W��^���� */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(flag&0x0f));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int num = 1;
			if(sd) {
				num = sd->ball.num;
				pc_delball(sd,sd->ball.num,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|num,
				skill_castend_damage_id);
		}
		break;
	case DK_DRAGONIC_AURA:		/* �h���S�j�b�N�I�[�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case DK_HACKANDSLASHER:		/* �n�b�N�A���h�X���b�V���[ */
	case DK_HACKANDSLASHER_ATK:	/* �n�b�N�A���h�X���b�V���[(�U��) */
	case DK_MADNESS_CRUSHER:	/* �}�b�h�l�X�N���b�V���[ */
	case DK_DRAGONIC_BREATH:	/* �h���S�j�b�N�u���X */
	case CD_PETITIO:			/* �y�e�B�e�B�I */
	case IQ_OLEUM_SANCTUM:		/* �������� */
	case IQ_EXPOSION_BLASTER:	/* ���ΐ_�e */
	case IQ_FIRST_BRAND:		/* ��ꌂ�F���� */
	case IQ_SECOND_FLAME:		/* ��񌂁F�Ŗ��̉� */
	case IQ_SECOND_FAITH:		/* ��񌂁F�M�O */
	case IQ_SECOND_JUDGEMENT:	/* ��񌂁F�R�� */
	case IQ_THIRD_FLAME_BOMB:	/* ��O���F�ŉΌ� */
	case BO_ACIDIFIED_ZONE_WATER:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case BO_ACIDIFIED_ZONE_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(�n) */
	case BO_ACIDIFIED_ZONE_WIND:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case BO_ACIDIFIED_ZONE_FIRE:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case NPC_BO_THROWROCK:		/* �X���[���b�N */
	case NPC_BO_WOODEN_ATTACK:	/* �E�h�D���A�^�b�N */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_STORMSLASH:		/* �X�g�[���X���b�V�� */
	case CD_EFFLIGO:		/* �G�t�B���S */
	case SHC_SHADOW_STAB:	/* �V���h�E�X�^�u */
	case ABC_FRENZY_SHOT:	/* �t�����W�V���b�g */
	case WH_HAWKRUSH:		/* �z�[�N���b�V�� */
	case WH_HAWKBOOMERANG:	/* �z�[�N�u�[������ */
	case TR_RHYTHMSHOOTING:		/*���Y���V���[�e�B���O */
	case MT_TRIPLE_LASER:		/* �g���v�����[�U�[ */
	case ABR_BATTLE_BUSTER:		/* �o�g���o�X�^�[ */
	case ABR_DUAL_CANNON_FIRE:	/* �f���A���L���m���t�@�C���[ */
	case ABR_INFINITY_BUSTER:	/* �C���t�B�j�e�B�o�X�^�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AG_DEADLY_PROJECTION:		/* �f�b�h���[�v���W�F�N�V���� */
	case TR_ROSEBLOSSOM:	/* ���[�u���b�T�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AG_DESTRUCTIVE_HURRICANE:		/* �f�B�X�g���N�e�B�u�n���P�[�� */
		if(flag&0x20) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x10);
		} else if(flag&0x10) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag&0xf);
			if((flag&0xf) == 1) {	// �N���C�}�b�N�XLv1�F�������ǉ��_���[�W
				skill_addtimerskill(src,tick+300,bl->id,0,0,skillid,skilllv,0,flag|0x20);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int climax = 0;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				climax = sc->data[SC_CLIMAX].val1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(climax == 4) {		// �N���C�}�b�N�XLv4�F���g�ɃN���C�}�b�N�X�n���P�[����ԕt�^
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				if(climax == 5)		// �N���C�}�b�N�XLv5�F�͈͂�19x19�Ɋg��
					ar = 9;
				/* �͈͓��̓G�S�̂ɏ������s�� */
				skill_area_temp[1] = src->id;
				map_foreachinarea(skill_area_sub,
					src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|climax,
					skill_castend_damage_id);
			}
		}
		break;
	case AG_RAIN_OF_CRYSTAL:		/* ���C���I�u�N���X�^�� */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case AG_SOUL_VC_STRIKE:		/* �\�E���o���J���X�g���C�N */
	case AG_ROCK_DOWN:			/* ���b�N�_�E�� */
	case AG_FROZEN_SLASH:		/* �t���[�Y���X���b�V�� */
	case CD_FRAMEN:				/* �t���[���� */
	case TR_METALIC_FURY:		/* ���^���b�N�t���[���[ */
	case NPC_BO_HELL_HOWLING:	/* �w���n�E�����O */
	case NPC_BO_FAIRY_DUSTY:	/* �t�F�A���[�_�X�e�B */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AG_CRYSTAL_IMPACT:		/* �N���X�^���C���p�N�g */
		if(flag&0x20) {
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(flag&0x10) {
			/* �ʂɃ_���[�W��^���� */
			if(bl->id != skill_area_temp[1]) {
				if((flag&0xf) == 2) {		// �N���C�}�b�N�XLv2�F2��A���U��
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x800|flag&0xf);
				} else {
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag&0xf);
				}
				skill_addtimerskill(src,tick+300,bl->id,0,0,AG_CRYSTAL_IMPACT_ATK,skilllv,0,flag&0xf);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int climax = 0;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				climax = sc->data[SC_CLIMAX].val1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			if(climax == 5)		// �N���C�}�b�N�XLv5�F�͈͂�19x19�Ɋg��
				ar = 9;
			/* �͈͓��̓G�S�̂ɏ������s�� */
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|climax,
				skill_castend_damage_id);
			if(climax == 1) {		// �N���C�}�b�N�XLv1�F�͈͓��̖����ɕt�^����
				map_foreachinarea(skill_area_sub,
					src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_NOENEMY|0x20,
					skill_castend_damage_id);
			}
		}
		break;
	case AG_CRYSTAL_IMPACT_ATK:		/* �N���X�^���C���p�N�g(�ǌ�) */
		if((flag&0x0f) != 5 || flag&0x10) {		// �N���C�}�b�N�XLv5�F�ǌ��_���[�W�͈̔͊g��
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10,
				skill_castend_damage_id);
		}
		break;
	case AG_ASTRAL_STRIKE_ATK:	/* �A�X�g�����X�g���C�N(����) */
	case TR_SOUNDBLEND:			/* �T�E���h�u�����h */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20));
		break;
	case AG_STORM_CANNON:	/* �X�g�[���L���m�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],unit_distance(src,bl),skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;
	case AG_CRIMSON_ARROW:	/* �N�����]���A���[ */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],unit_distance(src,bl),skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* �^�[�Q�b�g�ɍU�� */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
			skill_addtimerskill(src,tick+300,bl->id,0,0,AG_CRIMSON_ARROW_ATK,skilllv,0,flag);
		}
		break;
	case AG_CRIMSON_ARROW_ATK:	/* �N�����]���A���[(�U��) */
	case CD_ARBITRIUM_ATK:		/* �A���r�g���E��(�ǌ�) */
	case ABC_FROM_THE_ABYSS_ATK:	/* �t�����W�A�r�X(�U��) */
	case TR_ROSEBLOSSOM_ATK:	/* ���[�u���b�T��(�U��) */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case IQ_MASSIVE_F_BLASTER:		/* ���ΖŖ��_�e */
	case IG_GRAND_JUDGEMENT:		/* �O�����h�W���b�W�����g */
	case IG_SHIELD_SHOOTING:		/* �V�[���h�V���[�e�B���O */
	case SHC_IMPACT_CRATER:			/* �C���p�N�g�N���[�^�[ */
	case MT_AXE_STOMP:				/* �A�b�N�X�X�g���v */
	case ABC_ABYSS_DAGGER:			/* �A�r�X�_�K�[ */
	case ABC_DEFT_STAB:				/* �f�t�g�X�^�u */
	case MT_SPARK_BLASTER:			/* �X�p�[�N�u���X�^�[ */
	case MT_MIGHTY_SMASH:			/* �}�C�e�B�X�}�b�V�� */
	case BO_EXPLOSIVE_POWDER:		/* �G�N�X�v���b�V�u�p�E�_�[ */
	case BO_MAYHEMIC_THORNS:		/* ���C�w�~�b�N�\�[���Y */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case IQ_THIRD_PUNISH:			/* ��O���F�f�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),MAX_SPIRITBALL);
		}
		break;
	case IQ_THIRD_CONSECRATION:		/* ��O���F�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int hp = (int)((atn_bignumber)status_get_max_hp(src) * skilllv * 6 / 100);
			int sp = (int)((atn_bignumber)status_get_max_sp(src) * skilllv * 6 / 100);
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			unit_heal(src,hp,sp,0,1);
		}
		break;
	case IG_OVERSLASH:		/* �I�[�o�[�X���b�V�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(skill_area_temp[0]&0xff));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case CD_ARBITRIUM:	/* �A���r�g���E�� */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		skill_addtimerskill(src,tick+500,bl->id,0,0,CD_ARBITRIUM_ATK,skilllv,0,flag);
		break;
	case SHC_SAVAGE_IMPACT:		/* �T�x�[�W�C���p�N�g */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);

		}
		break;
	case SHC_ETERNAL_SLASH:		/*�G�^�[�i���X���b�V�� */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_E_SLASH_COUNT].timer != -1) {
			if(sc->data[SC_E_SLASH_COUNT].val1 < 5) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),sc->data[SC_E_SLASH_COUNT].val1+1,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		else {
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SHC_FATAL_SHADOW_CROW:		/* �t�F�C�^���V���h�E�N���[ */
		if(flag&1) {
			int skill;
			if(sd && (skill = pc_checkskill(sd,GC_DARKCROW)) > 0) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skill,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);

		}
		break;
	case MT_RUSH_QUAKE:				/* ���b�V���N�G�C�N */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case ABC_UNLUCKY_RUSH:		/* �A�����b�L�[���b�V�� */
		{
			int dist = unit_distance(src,bl);
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case ABC_CHAIN_REACTION_SHOT:	/* �`�F�[�����A�N�V�����V���b�g */
	case ABC_CHAIN_REACTION_SHOT_ATK:	/* �`�F�[�����A�N�V�����V���b�g(�U��) */
	case WH_GALESTORM:		/* �Q�C���X�g�[�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case WH_CRESCIVE_BOLT:	/* �N���b�V�u�{���g */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			int count = sc->data[GetSkillStatusChangeTable(skillid)].val1;
			if(count < 3) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),count+1,0,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				status_change_start(src,GetSkillStatusChangeTable(skillid),count,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EM_ELEMENTAL_BUSTER:		/* �G�������^���o�X�^�[ */
		{
			int busterid = EM_ELEMENTAL_BUSTER;
			if(sd && sd->eld) {
				switch(sd->eld->status.class_) {
					case ELEMID_EM_ARDOR:      busterid = EM_ELEMENTAL_BUSTER_FIRE;   break;
					case ELEMID_EM_DILUVIO:    busterid = EM_ELEMENTAL_BUSTER_WATER;  break;
					case ELEMID_EM_PROCELLA:   busterid = EM_ELEMENTAL_BUSTER_WIND;   break;
					case ELEMID_EM_TERREMOTUS: busterid = EM_ELEMENTAL_BUSTER_GROUND; break;
					case ELEMID_EM_SERPENS:    busterid = EM_ELEMENTAL_BUSTER_POISON; break;
				}
			}
			clif_skill_nodamage(src,bl,busterid,skilllv,1);
			skill_unitsetting(src,busterid,skilllv,src->x,src->y,0);
		}
		break;
	case NW_THE_VIGILANTE_AT_NIGHT:		/* �r�W�����g�A�b�g�i�C�g */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar;
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			if(sd && sd->status.weapon == WT_GATLING) {
				clif_skill_nodamage(src,bl,NW_THE_VIGILANTE_AT_NIGHT_GUN_GATLING,skilllv,1);
				ar = skill_get_area(NW_THE_VIGILANTE_AT_NIGHT_GUN_GATLING,skilllv);
			} else {
				clif_skill_nodamage(src,bl,NW_THE_VIGILANTE_AT_NIGHT_GUN_SHOTGUN,skilllv,1);
				ar = skill_get_area(NW_THE_VIGILANTE_AT_NIGHT_GUN_SHOTGUN,skilllv);
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_ONLY_ONE_BULLET:		/* �I�����[�����o���b�g */
	case NW_MAGAZINE_FOR_ONE:		/* �}�K�W���t�H�[���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
			status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		break;
	case NW_SPIRAL_SHOOTING:		/* �X�p�C�����V���[�e�B���O */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
				if(sd->status.weapon == WT_GRENADE)
					ar += 2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_WILD_FIRE:			/* ���C���h�t�@�C�A */
	case NW_HASTY_FIRE_IN_THE_HOLE:	/* �w�C�X�e�B�t�@�C�A�C���U�z�[�� */
	case NW_GRENADES_DROPPING:	/* �O���l�[�Y�h���b�s���O */
	case NW_MISSION_BOMBARD:	/* �~�b�V�����{���o�[�h */
	case SS_KAGEGARI:			/* �e��� */
	case SS_FUUMAKOUCHIKU:		/* �����藠�� -�\�z- */
	case SS_KUNAIWAIKYOKU:		/* �ꖳ -�c��- */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NW_BASIC_GRENADE:		/* �x�[�V�b�N�O���l�[�h */
	case HN_SHIELD_CHAIN_RUSH:	/* �V�[���h�`�F�[�����b�V�� */
	case SKE_NOON_BLAST:		/* ���V��z */
	case SKE_SUNSET_BLAST:		/* �V�z */
	case SKE_MIDNIGHT_KICK:		/* ���V�ꌎ */
	case SKE_DAWN_BREAK:		/* �V�� */
	case SS_KAGEGISSEN:			/* �e��M */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SOA_TALISMAN_OF_SOUL_STEALING:		/* �쓹�� */
		if(battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag)) {
			int sp = (status_get_lv(src) - 100) * skilllv;
			if(sp)
				unit_heal(src,0,sp,0,1);
		}
		break;
	case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* ����� */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd)
				pc_delsoulenergy(sd,MAX_SOULENERGY,0);
		}
		break;
	case SOA_TALISMAN_OF_BLUE_DRAGON:		/* ���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_T_SECOND_GOD].timer == -1 && sc->data[SC_T_THIRD_GOD].timer == -1 && sc->data[SC_T_FOURTH_GOD].timer == -1 && sc->data[SC_T_FIVETH_GOD].timer == -1) {
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SOA_TALISMAN_OF_WHITE_TIGER:		/* ���Օ� */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_FIRST_GOD].timer != -1) {
				status_change_end(src, SC_T_FIRST_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SOA_TALISMAN_OF_RED_PHOENIX:		/* �鐝�� */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_SECOND_GOD].timer != -1) {
				status_change_end(src, SC_T_SECOND_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SOA_TALISMAN_OF_BLACK_TORTOISE:	/* ������ */
	case HN_METEOR_STORM_BUSTER:	/* ���e�I�X�g�[���o�X�^�[ */
	case HN_JACK_FROST_NOVA:		/* �W���b�N�t���X�g�m���@ */
	case SS_TOKEDASU:				/* �e�n�� */
	case SS_REIKETSUHOU:			/* �⌌�C */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SOA_TALISMAN_OF_FOUR_BEARING_GOD:	/* �l���_�� */
	case HN_JUPITEL_THUNDER_STORM:	/* ���s�e���T���_�[�X�g�[�� */
	case HN_HELLS_DRIVE:			/* �w���Y�h���C�u */
	case HN_NAPALM_VULCAN_STRIKE:	/* �i�p�[���o���J���X�g���C�N */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* �l���܍s�w */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_FOURTH_GOD].timer != -1) {
				status_change_end(src, SC_T_FOURTH_GOD, -1);
			}
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SH_CHUL_HO_SONIC_CLAW:		/* �^�C�K�[�X���b�V�� */
	case HN_MEGA_SONIC_BLOW:		/* ���K�\�j�b�N�u���[ */
	case HN_SPIRAL_PIERCE_MAX:		/* �X�p�C�����s�A�[�X�}�b�N�X */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SH_HOWLING_OF_CHUL_HO:		/* �^�C�K�[�n�E�����O */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				ar += 3;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SH_HOGOGONG_STRIKE:		/* �^�C�K�[�X�g���C�N */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_HOGOGONG].timer != -1) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SH_HYUN_ROK_CANNON:		/* �f�B�A�[�L���m�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case HN_DOUBLEBOWLINGBASH:		/* �_�u���{�E�����O�o�b�V�� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(skill_area_temp[0]&0xff));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			/* �͈͓��̓G�S�̂ɏ������s�� */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case HN_GROUND_GRAVITATION:		/* �O���E���h�O���r�e�[�V���� */
		if(flag&1) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		}
		break;
	case SKE_RISING_SUN:		/* �V�n��z */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc) {
			if(sc->data[SC_RISING_SUN].timer != -1) {		// ���o->����
				status_change_end(src,SC_RISING_SUN,-1);
				status_change_start(src,SC_NOON_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else if(sc->data[SC_NOON_SUN].timer != -1) {	// ����->���v
				status_change_end(src,SC_NOON_SUN,-1);
				status_change_start(src,SC_SUNSET_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else if(sc->data[SC_SUNSET_SUN].timer == -1 && sc->data[SC_RISING_MOON].timer == -1 && sc->data[SC_MIDNIGHT_MOON].timer == -1 && sc->data[SC_SKY_ENCHANT].timer == -1) {	// ���v�E���o�E���q�E�V�C�̐g�ł͂Ȃ�
				if(sc->data[SC_DAWN_MOON].timer != -1)		// ���v�͉���
					status_change_end(src,SC_DAWN_MOON,-1);
				status_change_start(src,SC_RISING_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SKE_RISING_MOON:		/* �V�n�ꌎ */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_RISING_MOON].timer != -1) {		// ���o->���q
					status_change_end(src,SC_RISING_MOON,-1);
					status_change_start(src,SC_MIDNIGHT_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_MIDNIGHT_MOON].timer != -1) {	// ���q->���v
					status_change_end(src,SC_MIDNIGHT_MOON,-1);
					status_change_start(src,SC_DAWN_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_DAWN_MOON].timer == -1 && sc->data[SC_RISING_SUN].timer == -1 && sc->data[SC_NOON_SUN].timer == -1 && sc->data[SC_SKY_ENCHANT].timer == -1) {	// ���v�E���o�E���q�E�V�C�̐g�ł͂Ȃ�
					if(sc->data[SC_SUNSET_SUN].timer != -1)		// ���v�͉���
						status_change_end(src,SC_SUNSET_SUN,-1);
					status_change_start(src,SC_RISING_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SKE_TWINKLING_GALAXY:	/* �V�n���� */
	case SKE_STAR_CANNON:		/* �V�� */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		}
		break;
	case SKE_STAR_BURST:		/* �V������ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case SKE_ALL_IN_THE_SKY:	/* �V������ */
		{
			int dist = unit_distance(src,bl);
			// �^�[�Q�b�g�̗אڃZ���ړ�
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case SS_SHIMIRU:	/* �e���� */
		{
			int dist = unit_distance(src,bl);
			int ar = skill_get_area(skillid,skilllv);
			// �^�[�Q�b�g�̗אڃZ���ړ�
			if(sd && !map[sd->bl.m].flag.gvg && dist > 0) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx--;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
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
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			map_foreachinarea(skill_shimiru,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src);
		}
		break;
	case SS_KAGENOMAI:		/* �e�̕� */
		if(flag&3) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				bl->m,bl->x-ar2,bl->y-ar2,bl->x+ar2,bl->y+ar2,BL_SKILL,
				src,skillid,tick);
		}
		break;
	case SS_KUNAIKAITEN:		/* �ꖳ -��]- */
		if(sd) {
			int cost = skill_get_arrow_cost(skillid,skilllv);
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
				break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		skill_unitsetting(src,SS_KUNAIWAIKYOKU,skilllv,bl->x,bl->y,0);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SS_KUNAIKUSSETSU:		/* �ꖳ -����- */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_kunaikussetsu,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skilllv);
		}
		break;
	case SS_SEKIENHOU:		/* �ԉ��C */
	case SS_RAIDENPOU:		/* ���d�C */
	case SS_KINRYUUHOU:		/* �����C */
	case SS_ANTENPOU:		/* �Ó]�C */
		if(flag&3) {
			/* �ʂɃ_���[�W��^���� */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_poseffect(src,skillid,skilllv,bl->x,bl->y,tick);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,SS_ANTENPOU,tick);
		}
		break;
	case SS_KAGEAKUMU:			/* ���p -�e�D��- */
	case SS_HITOUAKUMU:			/* ���p -�ꖳ- */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_end(bl,SC_NIGHTMARE,-1);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SS_ANKOKURYUUAKUMU:	/* ���p -�Í���- */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_NIGHTMARE].timer != -1) {
				skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|flag|2);
				status_change_end(bl,SC_NIGHTMARE,-1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case EL_FIRE_BOMB:		/* �t�@�C�A�[�{�� */
	case EL_FIRE_WAVE:		/* �t�@�C�A�[�E�F�[�u */
	case EL_WATER_SCREW:	/* �E�H�[�^�[�X�N�����[ */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TIDAL_WEAPON:	/* �^�C�_���E�F�|�� */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else if(eld && eld->msd) {
			clif_skill_nodamage(src,&eld->msd->bl,skillid,skilllv,1);
			//clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_HURRICANE:		/* �n���P�[�����C�W */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TYPOON_MIS:		/* �^�C�t�[���~�T�C�� */
	case EL_ROCK_CRUSHER:	/* ���b�N�����`���[ */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,flag);
		}
		break;
	case EL_STONE_RAIN:		/* �X�g�[�����C�� */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EM_EL_FLAMEROCK:		/* �t���C�����b�N */
	case EM_EL_STORM_WIND:		/* �X�g�[���E�C���h */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case EM_EL_AGE_OF_ICE:		/* �G�C�W�I�u�A�C�X */
	case EM_EL_AVALANCHE:		/* �A�o�����`�F */
	case EM_EL_DEADLY_POISON:	/* �f�b�h���[�|�C�Y�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
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
 * �X�L���g�p�i�r�������AID�w��x���n�j
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
			// skill_castend_id�ŋ������X�L���͂����œG�`�F�b�N
			if(skill_get_inf2(skillid) & INF2_ATTACK || skill_get_inf(skillid) & INF_ATTACK) {
				if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
					is_enemy = 0;
			}
			break;
	}

	map_freeblock_lock();

	switch(skillid)
	{
	case AL_HEAL:				/* �q�[�� */
	case AB_HIGHNESSHEAL:		/* �n�C�l�X�q�[�� */
		{
			int heal;
			int heal_get_jobexp;
			int lv;
			lv = (skillid == AB_HIGHNESSHEAL)? 10: skilllv;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, lv));
			sc = status_get_sc(bl);
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999�q�[��
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// ����峃J�[�h�i�q�[���ʂO�j
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0; 	// �o�[�T�[�N���̓q�[���O
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// �����M�A���撆�̓q�[���O
			if(sd && dstsd && sd->status.partner_id == dstsd->status.char_id && (sd->s_class.job == PC_CLASS_SNV || sd->s_class.job == PC_CLASS_ESNV) && sd->sex == SEX_FEMALE)
				heal *= 2;	// �X�p�m�r�̉ł��U�߂Ƀq�[�������2�{�ɂȂ�
			if(skillid == AB_HIGHNESSHEAL)
				heal = heal * (170 + 30 * skilllv) / 100;
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// �J�C�g
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// �������g�ɑ΂��Ă͉񕜗�0
					heal = 0;
				} else {		// �q�[������
					bl = src;
					dstsd = sd;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			heal_get_jobexp = battle_heal(NULL,bl,heal,0,0);

			// JOB�o���l�l��
			if(sd && dstsd && heal > 0 && src != bl && battle_config.heal_exp > 0) {
				heal_get_jobexp = heal_get_jobexp * battle_config.heal_exp / 100;
				if(heal_get_jobexp <= 0)
					heal_get_jobexp = 1;
				pc_gainexp(sd,NULL,0,heal_get_jobexp,0);
			}
		}
		break;

	case HLIF_HEAL:		/* �����̎菕�� */
		{
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));
			sc = status_get_sc(bl);
			if(hd) {
				int skill = homun_checkskill(hd,HLIF_BRAIN);
				if(skill > 0)
					heal += heal * skill / 50;
			}
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999�q�[��
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// ����峃J�[�h�i�q�[���ʂO�j
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0;	// �o�[�T�[�N���̓q�[���O
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// �����M�A���撆�̓q�[���O
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// �J�C�g
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// �������g�ɑ΂��Ă͉񕜗�0
					heal = 0;
				} else {		// �q�[������
					bl = src;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case ALL_RESURRECTION:		/* ���U���N�V���� */
		if(!dstsd)
			break;
		if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVP�ŕ����s�\���
			break;
		if(!unit_isdead(&dstsd->bl))			// ���S����
			break;
		if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// �w���p���[��Ԃ͑h���s��
			break;

		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		dstsd->status.hp = dstsd->status.max_hp * ((skilllv >= 4)? 80: skilllv*20-10)/100;
		if(dstsd->status.hp <= 0)
			dstsd->status.hp = 1;
		if(dstsd->special_state.restart_full_recover) {	// �I�V���X�J�[�h
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

	case AL_DECAGI:			/* ���x���� */
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
		status_change_release(bl,0x80); // ���x�����ɂ���Ԉُ����
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
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;

	case PR_LEXDIVINA:		/* ���b�N�X�f�B�r�[�i */
	case MER_LEXDIVINA:
		sc = status_get_sc(bl);
		if(sc) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if(sc->data[SC_SILENCE].timer != -1) {
				// ���ْ��Ȃ�G������킸���ى���
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
			sd->skill_item.flag    = 1;		// �g�p�������肷��
			clif_item_skill(sd, abra_skillid, abra_skilllv, msg_txt(179)); // �A�u���J�_�u��
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
	case NPC_ALLHEAL:		/* ���C�t�X�g���[�� */
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
				pc_heal(dstsd,heal,dstsd->status.max_sp,0,0);
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
		if(sd && pc_nextbaseexp(sd) > 0)
			pc_gainexp(sd,NULL,pc_nextbaseexp(sd)*10/100,0,0);
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
			// �N���X�`�F���W�p�{�X�����X�^�[ID
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
			// �`�F���W�|�����p�����X�^�[ID
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
	case PF_SPIDERWEB:		/* �X�p�C�_�[�E�F�u */
	case NPC_FLAMECROSS:		/* �t���C���N���X */
	case NPC_VENOMFOG:		/* �x�i���t�H�O */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case AL_INCAGI:			/* ���x���� */
	case MER_INCAGI:
	case AL_BLESSING:		/* �u���b�V���O */
	case MER_BLESSING:
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_HIGH].timer != -1)
			status_change_end(bl,SC_HIGH,-1);
        if(dstsd && dstsd->sc.data[SC_ELEMENTUNDEAD].timer != -1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
            break;
		}
        /* fall through */
    case PR_SLOWPOISON:
	case PR_IMPOSITIO:		/* �C���|�V�e�B�I�}�k�X */
	case PR_LEXAETERNA:		/* ���b�N�X�G�[�e���i */
	case PR_SUFFRAGIUM:		/* �T�t���M�E�� */
	case CR_PROVIDENCE:		/* �v�����B�f���X */
	case SA_FLAMELAUNCHER:		/* �t���C�������`���[ */
	case SA_FROSTWEAPON:		/* �t���X�g�E�F�|�� */
	case SA_LIGHTNINGLOADER:	/* ���C�g�j���O���[�_�[ */
	case SA_SEISMICWEAPON:		/* �T�C�Y�~�b�N�E�F�|�� */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_BENEDICTIO:		/* ���̍~�� */
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
	case SA_ELEMENTWATER:	/* �E�H�[�^�[�G�������^���`�F���W */
	case SA_ELEMENTGROUND:	/* �A�[�X�G�������^���`�F���W */
	case SA_ELEMENTFIRE:	/* �t�@�C�A�[�G�������^���`�F���W */
	case SA_ELEMENTWIND:	/* �E�B���h�G�������^���`�F���W */
		if(dstmd) {
			// �{�X�����������ꍇ�Ǝb���40%�̊m���Ŏg�p���s
			if((battle_config.boss_no_element_change && dstmd && dstmd->mode&MD_BOSS) || atn_rand() % 100 < 40) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			// �G�͑������x�����ێ�����
			switch(skillid) {
				case SA_ELEMENTWATER:	// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WATER;
					break;
				case SA_ELEMENTGROUND:	// �y
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_EARTH;
					break;
				case SA_ELEMENTFIRE:	// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_FIRE;
					break;
				case SA_ELEMENTWIND:	// ��
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WIND;
					break;
			}
			// �f�B�X�y���΍���ꉞ���H
			//status_change_start(bl,GetSkillStatusChangeTable(skillid),dstmd->def_ele/20,0,0,0,skill_get_time(skillid,skilllv),0 );
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		else if(!dstsd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NPC_CHANGEUNDEAD:		/* �s�������t�^ */
		if( dstsd && dstsd->special_state.no_magic_damage ) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else {
			if(status_get_elem_type(bl) == ELE_DARK || status_get_race(bl) == RCT_DEMON)
				break;
			status_change_start(bl,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;

	case BA_PANGVOICE:	/* �p���{�C�X */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_CONFUSION].timer != -1)
			status_change_end(bl,SC_CONFUSION,-1);
		else if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,7000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case DC_WINKCHARM:	/* ���f�̃E�B���N */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd) {
			if(atn_rand() % 10000 < status_change_rate(&dstsd->bl,SC_CONFUSION,1000,status_get_lv(src))) {
				status_change_pretimer(&dstsd->bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
				break;
			}
		} else if(dstmd) {
			int race = status_get_race(&dstmd->bl);
			if( !(dstmd->mode&MD_BOSS) && (race == RCT_DEMON || race == RCT_DEMIHUMAN || race == RCT_ANGEL) ) {
				if(atn_rand() % 100 < 40 + status_get_lv(src) - status_get_lv(bl)) {
					status_change_start(&dstmd->bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,10000,0);
					break;
				}
			}
		}
		if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case TK_RUN:		/* �^�C���M */
		if(sd) {
			if(sd->sc.data[SC_RUN].timer != -1) {
				// 5�Z���ȓ���Lv7�ȏ�őf��Ȃ�X�p�[�g�J�n
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
	case TK_HIGHJUMP:	/* �m�s�e�B�M */
		{
			int dir = status_get_dir(src);
			int x,y;
			if(dir & 1) {	// �΂߈ړ��̏ꍇ
				x = src->x + dirx[dir] * (skilllv+skilllv/3);
				y = src->y + diry[dir] * (skilllv+skilllv/3);
			} else {
				x = src->x + dirx[dir] * skilllv*2;
				y = src->y + diry[dir] * skilllv*2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// ���n�n�_�Ƃ��̈���悪�ړ��\�Z����PC,MOB,NPC����������Ȃ��Ȃ�
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
						if(mobdb_search(sd->tk_mission_target)->max_hp <= 0)
							continue;
						if(mobdb_search(sd->tk_mission_target)->mode&MD_BOSS)	// �{�X�������O
							continue;
						break;
					}
					if(i >= 1000)
						sd->tk_mission_target = 0;
					pc_setglobalreg(sd,"PC_MISSION_TARGET",sd->tk_mission_target);
				}
				clif_mission_mob(sd,sd->tk_mission_target,count);
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SG_SUN_WARM:		/* ���z�̉����� */
	case SG_MOON_WARM:		/* ���̉����� */
	case SG_STAR_WARM:		/* ���̉����� */
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
	case TK_SEVENWIND:		/* �g������ */
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
	case SL_SWOO:			/* �G�X�E */
		if(sd && !dstmd && !battle_config.allow_es_magic_all) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,10000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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

	case SL_SKA:			/* �G�X�J */
	case SL_SKE:			/* �G�X�N */
		if( sd && !dstmd && !battle_config.allow_es_magic_all ) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,1000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(skillid == SL_SKE)
			status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		break;
	case SL_KAAHI:			/* �J�A�q */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_KAAHI].timer != -1) {
			status_change_end(src,SC_KAAHI,-1);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_ASPERSIO:		/* �A�X�y���V�I */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_KYRIE:			/* �L���G�G���C�\�� */
	case MER_KYRIE:
		clif_skill_nodamage(bl,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SM_AUTOBERSERK:
	case KN_AUTOCOUNTER:		/* �I�[�g�J�E���^�[ */
	case KN_TWOHANDQUICKEN:		/* �c�[�n���h�N�C�b�P�� */
	case CR_SPEARQUICKEN:		/* �X�s�A�N�C�b�P�� */
	case CR_REFLECTSHIELD:
	case AS_ENCHANTPOISON:		/* �G���`�����g�|�C�Y�� */
	case AS_POISONREACT:		/* �|�C�Y�����A�N�g */
	case MC_LOUD:			/* ���E�h�{�C�X */
	case MG_ENERGYCOAT:		/* �G�i�W�[�R�[�g */
	case AL_RUWACH:			/* ���A�t */
	case MO_EXPLOSIONSPIRITS:	/* �����g�� */
	case MO_STEELBODY:		/* ���� */
	case WE_BABY:
	case LK_AURABLADE:		/* �I�[���u���C�h */
	case WS_CARTBOOST:		/* �J�[�g�u�[�X�g */
	case SN_SIGHT:			/* �g�D���[�T�C�g */
	case WS_MELTDOWN:		/* �����g�_�E�� */
	case ST_REJECTSWORD:		/* ���W�F�N�g�\�[�h */
	case HW_MAGICPOWER:		/* ���@�͑��� */
	case PF_MEMORIZE:		/* �������C�Y */
	case PF_DOUBLECASTING:		/* �_�u���L���X�e�B���O */
	case PA_SACRIFICE:		/* �T�N���t�@�C�X */
	case ST_PRESERVE:		/* �v���U�[�u */
	case WS_OVERTHRUSTMAX:		/* �I�[�o�[�g���X�g�}�b�N�X */
	case WZ_SIGHTBLASTER:		/* �T�C�g�u���X�^�[ */
	case KN_ONEHAND:		/* �����n���h�N�C�b�P�� */
	case TK_READYSTORM:
	case TK_READYDOWN:
	case TK_READYTURN:
	case TK_READYCOUNTER:
	case TK_DODGE:
	case SG_SUN_COMFORT:
	case SG_MOON_COMFORT:
	case SG_STAR_COMFORT:
	case SJ_LUNARSTANCE:	/* ���̍\�� */
	case SJ_STARSTANCE:		/* ���̍\�� */
	case SJ_UNIVERSESTANCE:	/* �F���̍\�� */
	case SJ_SUNSTANCE:		/* ���z�̍\�� */
	case SJ_LIGHTOFMOON:	/* ���̌� */
	case SJ_LIGHTOFSTAR:	/* ���̌� */
	case SJ_LIGHTOFSUN:		/* ���z�̌� */
	case SJ_FALLINGSTAR:	/* �������� */
	case SJ_BOOKOFDIMENSION:	/* �����̏� */
	case SL_KAIZEL:			/* �J�C�[�� */
	case SL_KAITE:			/* �J�C�g */
	case SL_KAUPE:			/* �J�E�v */
	case GS_INCREASING:		/* �C���N���[�W���O�A�L�����V�[ */
	case GS_MAGICALBULLET:	/* �}�W�J���o���b�g */
	case NJ_UTSUSEMI:		/* ���̏p */
	case NJ_NEN:			/* �O */
	case NPC_POWERUP:		/* ���b�V���A�^�b�N */
	case NPC_AGIUP:			/* ���x���� */
	case NPC_DEFENDER:
	case NPC_MAGICMIRROR:		/* �}�W�b�N�~���[ */
	case NPC_HELLPOWER:			/* �w���p���[ */
	case NPC_MAXPAIN:			/* �}�b�N�X�y�C�� */
	case RK_DEATHBOUND:			/* �f�X�o�E���h */
	case RK_MILLENNIUMSHIELD:	/* �~���j�A���V�[���h */
	case RK_GIANTGROWTH:		/* �W���C�A���g�O���[�X */
	case RK_VITALITYACTIVATION:	/* �o�C�^���e�B�A�N�e�B�x�[�V���� */
	case RK_ABUNDANCE:			/* �A�o���_���X */
	case GC_VENOMIMPRESS:		/* �x�i���C���v���X */
	case GC_WEAPONBLOCKING:		/* �E�F�|���u���b�L���O */
	case GC_HALLUCINATIONWALK:	/* �n���V�l�[�V�����E�H�[�N */
	case AB_DUPLELIGHT:			/* �f���v�����C�g */
	case AB_OFFERTORIUM:		/* �I�t�F���g���E�� */
	case WL_MARSHOFABYSS:		/* �}�[�V���I�u�A�r�X */
	case WL_RECOGNIZEDSPELL:	/* ���S�O�i�C�Y�h�X�y�� */
	case WL_TELEKINESIS_INTENSE:	/* �e���L�l�V�X�C���e���X */
	case RA_FEARBREEZE:			/* �t�B�A�[�u���[�Y */
	case RA_UNLIMIT:			/* �A�����~�b�g */
	case NC_ACCELERATION:		/* �A�N�Z�����[�V���� */
	case NC_HOVERING:			/* �z�o�[�����O */
	case NC_SHAPESHIFT:			/* �V�F�C�v�V�t�g */
	case SC_REPRODUCE:			/* ���v���f���[�X */
	case SC_DEADLYINFECT:		/* �f�b�h���[�C���t�F�N�g */
	case LG_REFLECTDAMAGE:		/* ���t���N�g�_���[�W */
	case LG_FORCEOFVANGUARD:	/* �t�H�[�X�I�u�o���K�[�h */
	case LG_EXEEDBREAK:			/* �C�N�V�[�h�u���C�N */
	case LG_PRESTIGE:			/* �v���X�e�B�[�W */
	case SR_CRESCENTELBOW:		/* �j�ꒌ */
	case SR_LIGHTNINGWALK:		/* �M�d�� */
	case SR_GENTLETOUCH_ENERGYGAIN:	/* �_�� -��- */
	case WM_GLOOMYDAY:			/* �������R���[ */
	case GN_CARTBOOST:			/* �J�[�g�u�[�X�g */
	case ALL_ODINS_POWER:		/* �I�[�f�B���̗� */
	case KO_MEIKYOUSISUI:		/* �����~�� */
	case RL_E_CHAIN:			/* �G�^�[�i���`�F�[�� */
	case DK_SERVANTWEAPON:		/* �T�[���@���g�E�F�|�� */
	case DK_SERVANT_W_SIGN:		/* �T�[���@���g�E�F�|���F�T�C�� */
	case DK_CHARGINGPIERCE:		/* �`���[�W���O�s�A�[�X */
	case DK_VIGOR:				/* ���B�S�[�� */
	case AG_CLIMAX:				/* �N���C�}�b�N�X */
	case IQ_POWERFUL_FAITH:		/* ���x�ȐM�O */
	case IQ_FIRM_FAITH:			/* ���łȐM�O */
	case IQ_SINCERE_FAITH:		/* �����ȐM�O */
	case IQ_FIRST_FAITH_POWER:	/* ���́F�M�O�̗� */
	case IQ_JUDGE:				/* ���́F�R���� */
	case IQ_THIRD_EXOR_FLAME:	/* �ŏI�́F�Ŗ��̉� */
	case IG_GUARD_STANCE:		/* �K�[�h�X�^���X */
	case IG_ATTACK_STANCE:		/* �A�^�b�N�X�^���X */
	case IG_HOLY_SHIELD:		/* �z�[���[�V�[���h */
	case IG_REBOUND_SHIELD:		/* ���o�E���h�V�[���h */
	case CD_ARGUTUS_VITA:		/* �A���O�g�D�X���B�^ */
	case CD_ARGUTUS_TELUM:		/* �A���O�g�D�X�e���� */
	case CD_PRESENS_ACIES:		/* �v���Z���X�A�L�G�[�X */
	case CD_RELIGIO:			/* �����M�I */
	case CD_BENEDICTUM:			/* �x�l�f�B�N�g�D�� */
	case SHC_SHADOW_EXCEED:		/* �V���h�E�G�N�V�[�h */
	case SHC_DANCING_KNIFE:		/* �_���V���O�i�C�t */
	case SHC_POTENT_VENOM:		/* �|�e���g�x�i�� */
	case SHC_ENCHANTING_SHADOW:	/* �G���`�����e�B���O�V���h�E */
	case MT_A_MACHINE:			/* �U�����u�L���� */
	case MT_D_MACHINE:			/* �h�䑕�u�L���� */
	case ABC_FROM_THE_ABYSS:	/* �t�����W�A�r�X */
	case WH_WIND_SIGN:			/* �E�B���h�T�C�� */
	case BO_ADVANCE_PROTECTION:	/* �t���V���h�E�`���[�W */
	case BO_RESEARCHREPORT:		/* ���T�[�`���|�[�g */
	case TR_MYSTIC_SYMPHONY:	/* �~�X�e�B�b�N�V���t�H�j�[ */
	case TR_KVASIR_SONATA:		/* �\�i�^�I�u�N���@�V�� */
	case EM_SPELL_ENCHANTING:	/* �X�y���G���`�����e�B���O */
	case NPC_BO_HELL_DUSTY:		/* �w���_�X�e�B */
	case NW_INTENSIVE_AIM:		/* �C���e���V�u�G�C�� */
	case NW_AUTO_FIRING_LAUNCHER:	/* �I�[�g�t�@�C�A�����O�����`���[ */
	case NW_HIDDEN_CARD:		/* �q�h�D���J�[�h */
	case SOA_TALISMAN_OF_WARRIOR:	/* ���m�� */
	case SOA_TALISMAN_OF_MAGICIAN:	/* �@�t�� */
	case SOA_TALISMAN_OF_FIVE_ELEMENTS:	/* �܍s�� */
	case SH_TEMPORARY_COMMUNION:	/* �O���� */
	case HN_BREAKINGLIMIT:		/* �u���C�L���O���~�b�g */
	case HN_RULEBREAK:			/* ���[���u���C�N */
	case SKE_ENCHANTING_SKY:	/* �V�C�̐g */
	case MS_REFLECTSHIELD:
	case MER_QUICKEN:			/* �E�F�|���N�C�b�P�� */
	case MER_AUTOBERSERK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_STONESKIN:		/* �X�g�[���X�L�� */
	case NPC_ANTIMAGIC:		/* �A���`�}�W�b�N */
		//clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_PARRYING:		/* �p���C���O */
	case MG_SIGHT:			/* �T�C�g */
	case MS_PARRYING:
	case MER_SIGHT:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case HP_ASSUMPTIO:		/* �A�X���v�e�B�I */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);	// �A�C�R���p�P�b�g���M��ɑ���
		break;
	case CASH_ASSUMPTIO:	/* �p�[�e�B�[�A�X���v�e�B�I */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* �ʂ̏��� */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// �A�C�R���p�P�b�g���M��ɑ���
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LK_CONCENTRATION:	/* �R���Z���g���C�V���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick;
		status_change_start(bl,SC_ENDURE,1,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_BERSERK:		/* �o�[�T�[�N */
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
	case SM_ENDURE:			/* �C���f���A */
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick + 10000;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_TENSIONRELAX:	/* �e���V���������b�N�X */
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
	case AC_CONCENTRATION:	/* �W���͌��� */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			map_foreachinarea(status_change_timer_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,GetSkillStatusChangeTable(skillid),skilllv,tick);
		}
		break;
	case SM_PROVOKE:		/* �v���{�b�N */
	case SM_SELFPROVOKE:	/* �Z���t�v���{�b�N */
	case MER_PROVOKE:
		// MVPmob�ƕs���ɂ͌����Ȃ��E��������
		if( status_get_mode(bl)&MD_BOSS || battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) || atn_rand()%100 > 70 + skilllv * 3 + status_get_lv(src) - status_get_lv(bl) ) {
			if(skillid != SM_SELFPROVOKE) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 1;
			}
		}
		clif_skill_nodamage(src,bl,(skillid == SM_SELFPROVOKE)? SM_PROVOKE : skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );

		// �����E�Ή��E����������
		status_change_attacked_end(bl);

		if(dstmd) {
			int range = skill_get_fixed_range(src,skillid,skilllv);
			mob_target(dstmd,src,range);
			battle_join_struggle(dstmd, src);
			if(dstmd->state.angry)
				dstmd->state.angry = 0;
		}
		if(sd)	// �g�p�҂��v���C���[�̂Ƃ��r���W�Q
			unit_skillcastcancel(bl,2);
		break;

	case CG_MARIONETTE:		/* �}���I�l�b�g�R���g���[�� */
		if(sd && dstsd)
		{
			status_change_start(src,SC_MARIONETTE,1,bl->id,0,0,60000,0);
			status_change_start(bl,SC_MARIONETTE2,1,src->id,0,0,60000,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// �A�C�R���p�P�b�g���M��ɑ���
		}
		break;
	case CR_DEVOTION:		/* �f�B�{�[�V���� */
		if(sd && dstsd) {
			int i, n;
			int lv   = abs(sd->status.base_level - dstsd->status.base_level);
			int type = GetSkillStatusChangeTable(skillid);

			if( sd->bl.id == dstsd->bl.id ||			// ����͎����̓_��
			    lv > battle_config.devotion_level_difference ||	// ���x����
			    sd->status.party_id <= 0 ||				// ������PT���������ƃ_��
			    dstsd->status.party_id <= 0 ||			// ���肪PT���������ƃ_��
			    sd->status.party_id != dstsd->status.party_id ||	// �����p�[�e�B����Ȃ��ƃ_��
			    dstsd->s_class.job == PC_JOB_CR ||		// ���肪�N���Z�C�_�[���ƃ_��
			    dstsd->s_class.job == PC_JOB_LG ||		// ���肪���C�����K�[�h���ƃ_��
			    (type >= 0 && dstsd->sc.data[type].timer != -1 && dstsd->sc.data[type].val1 != sd->bl.id) )	// �Ⴄ�N���Z����f�B�{�[�V�����ς݂Ȃ�_��
			{
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 1;
			}

			for(i = 0, n = -1; i < skilllv && i < 5; i++) {
				if(sd->dev.val1[i] == dstsd->bl.id) {	// ���Ƀf�B�{�[�V�����ς݂̑���
					n = i;
					break;
				}
				if(!sd->dev.val1[i])	// �󂫂���������m�ۂ���
					n = i;
			}
			if(n < 0) {	// ���̂��󂫂��Ȃ�����
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
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case MO_CALLSPIRITS:	/* �C�� */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case CH_SOULCOLLECT:	/* ���C�� */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),MAX_SPIRITBALL);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case MO_BLADESTOP:	/* ���n��� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;
	case MO_ABSORBSPIRITS:	/* �C�D */
		{
			int val = 0;
			if(dstsd && dstsd->spiritball.num > 0) {
				if( sd && sd != dstsd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk )
					break;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				val = dstsd->spiritball.num * 7;
				pc_delspiritball(dstsd,dstsd->spiritball.num,0);
			} else if(dstmd && !(dstmd->mode&MD_BOSS)) { // �Ώۂ������X�^�[��BOSS�����łȂ��ꍇ
				// 20%�̊m���őΏۂ�Lv*2��SP���񕜂���B���������Ƃ��̓^�[�Q�b�e�B���O����B
				if(atn_rand()%100 < 20) {
					val = 2 * mobdb_search(dstmd->class_)->lv;
					mob_target(dstmd,src,0);
					battle_join_struggle(dstmd, src);
					unit_skillcastcancel(bl,2);	// �r���W�Q

					// �����E�Ή��E����������
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
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				}
			}
		}
		break;

	case AC_MAKINGARROW:		/* ��쐬 */
		if(sd) {
			clif_arrow_create_list(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_PHARMACY:			/* �|�[�V�����쐬 */
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
	case AM_CALLHOMUN:	/* �R�[���z�����N���X */
		if(sd && !sd->hd) {
			homun_callhom(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_REST:				/* ���� */
		if(sd && homun_isalive(sd)) {
			homun_return_embryo(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_RESURRECTHOMUN:				/* ���U���N�V�����z�����N���X */
		if(sd && !sd->hd && sd->hom.hp <= 0) {
			homun_revive(sd,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ASC_CDP:				/* �f�b�h���[�|�C�Y���쐬 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_CDP,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATECOIN:			/* �N���G�C�g�R�C�� */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_COIN,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATENUGGET:			/* �򐻑� */
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
	case BS_HAMMERFALL:		/* �n���}�[�t�H�[�� */
		if( dstsd && dstsd->special_state.no_weapon_damage )
			break;
		if( atn_rand() % 10000 < status_change_rate(bl,SC_STUN,(skilllv > 5)? 10000: 2000+skilllv*1000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RG_RAID:			/* �T�v���C�Y�A�^�b�N */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,SC_RAID,0,10,0,0,skill_get_time(skillid,skilllv),0 );
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
		}
		break;
	case ASC_METEORASSAULT:	/* ���e�I�A�T���g */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KN_BRANDISHSPEAR:	/* �u�����f�B�b�V���X�s�A */
	case ML_BRANDISH:
		{
			int c, n = 4;
			int dir = path_calc_dir(src,bl->x,bl->y);
			struct square tc;

			skill_brandishspear_first(&tc,dir,bl->x,bl->y);
			skill_brandishspear_dir(&tc,dir,4);

			skill_area_temp[1] = 0;

			/* �͈�4 */
			if(skilllv > 9) {
				for(c=1; c<4; c++) {
					map_foreachinarea(skill_area_sub,
						bl->m,tc.val1[c],tc.val2[c],tc.val1[c],tc.val2[c],(BL_CHAR|BL_SKILL),
						src,skillid,skilllv,tick, flag|BCT_ENEMY|n,
						skill_castend_damage_id);
				}
			}
			/* �͈�3,2 */
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
			/* �͈�1 */
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
	case GS_GLITTERING:		/* �t���b�v�U�R�C�� */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(atn_rand()%100 < 20 + skilllv * 10) {
				pc_addcoin(sd,skill_get_time(skillid,skilllv),MAX_COIN);
			} else {
				if(pc_checkskill(sd,RL_RICHS_COIN) < 1)
					pc_delcoin(sd,1,0);
			}
		}
		break;

	/* �p�[�e�B�X�L�� */
	case AL_ANGELUS:		/* �G���W�F���X */
	case PR_MAGNIFICAT:		/* �}�O�j�t�B�J�[�g */
	case PR_GLORIA:			/* �O�����A */
	case SN_WINDWALK:		/* �E�C���h�E�H�[�N */
	case CASH_BLESSING:		/* �p�[�e�B�[�u���b�V���O */
	case CASH_INCAGI:		/* �p�[�e�B�[���x���� */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* �ʂ̏��� */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case BS_ADRENALINE:		/* �A�h���i�������b�V�� */
	case BS_ADRENALINE2:		/* �t���A�h���i�������b�V�� */
	case BS_WEAPONPERFECT:		/* �E�F�|���p�[�t�F�N�V���� */
	case BS_OVERTHRUST:		/* �I�[�o�[�g���X�g */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* �ʂ̏��� */
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((src == bl)? 1: 0),0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
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
			// �b���Ȃ�ق���ɂ�
			if( mcd->msd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(&mcd->msd->bl,&mcd->msd->bl,skillid,skilllv,1);
			status_change_start(&mcd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	/*�i�t���Ɖ������K�v�j */
	case BS_MAXIMIZE:		/* �}�L�V�}�C�Y�p���[ */
	case NV_TRICKDEAD:		/* ���񂾂ӂ� */
	case CR_DEFENDER:		/* �f�B�t�F���_�[ */
	case CR_AUTOGUARD:		/* �I�[�g�K�[�h */
	case CR_SHRINK:			/* �V�������N */
	case GS_GATLINGFEVER:			/* �K�g�����O�t�B�[�o�[ */
	case ML_DEFENDER:
	case ML_AUTOGUARD:
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* �������� */
				status_change_end(bl, type, -1);
			} else {
				/* �t������ */
				if(skillid == BS_MAXIMIZE)
					status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
				else
					status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case TF_HIDING:			/* �n�C�f�B���O */
	case KO_YAMIKUMO:		/* �ŉ_ */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* �������� */
				status_change_end(bl, type, -1);
			} else {
				/* �t������ */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			if(sc && sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(bl,SC_CLOSECONFINE,-1);
		}
		break;

	case ST_CHASEWALK:		/* �`�F�C�X�E�H�[�N */
	case AS_CLOAKING:		/* �N���[�L���O */
	case GC_CLOAKINGEXCEED:	/* �N���[�L���O�G�N�V�[�h */
	case SC_INVISIBILITY:	/* �C���r�W�r���e�B */
	case RA_CAMOUFLAGE:		/* �J���t���[�W�� */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* �������� */
				status_change_end(bl, type, -1);
			} else {
				/* �t������ */
				status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
			}
			if(skillid == AS_CLOAKING && skilllv < 3)
				skill_check_cloaking(bl);
		}
		break;
	case NPC_INVISIBLE:		/* �C���r�W�u�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	/* �Βn�X�L�� */
	case HP_BASILICA:			/* �o�W���J */
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
	case BD_LULLABY:			/* �q��S */
	case BD_RICHMANKIM:			/* �j�����h�̉� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:			/* ���L�̋��� */
	case BD_INTOABYSS:			/* �[���̒��� */
	case BD_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
	case BA_DISSONANCE:			/* �s���a�� */
	case BA_POEMBRAGI:			/* �u���M�̎� */
	case BA_WHISTLE:			/* ���J */
	case BA_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
	case DC_UGLYDANCE:			/* ��������ȃ_���X */
	case DC_HUMMING:			/* �n�~���O */
	case DC_DONTFORGETME:		/* ����Y��Ȃ��Łc */
	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
	case CG_MOONLIT:			/* ������̉��� */
	case CG_HERMODE:			/* �w�����[�h�̏� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case CG_LONGINGFREEDOM:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,SC_LONGINGFREEDOM,skilllv,0,0,0,1000,0);
		break;

	case PA_GOSPEL:				/* �S�X�y�� */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_GOSPEL].timer != -1) {
			status_change_end(bl,SC_GOSPEL,-1);
		} else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			status_change_release(src,0x04);	// �S�X�y���p�҂̃X�e�[�^�X�ُ����
			if(sg) {
				clif_skill_poseffect(src,skillid,skilllv,src->x,src->y,tick);
				status_change_start(bl,SC_GOSPEL,skilllv,bl->id,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case BD_ADAPTATION:			/* �A�h���u */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_DANCING].timer != -1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_stop_dancing(src,0);
		}
		break;

	case BA_FROSTJOKE:			/* �����W���[�N */
	case DC_SCREAM:				/* �X�N���[�� */
		if( sd || (md && mob_is_pcview(md->class_)) ) {
			// �����ڂ�PC�łȂ��ꍇ�͉��̂��p�������Ă��܂��̂ŏ��O����
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		skill_addtimerskill(src,tick+3000,bl->id,0,0,skillid,skilllv,0,flag);
		if(md) {		// Mob�͒���Ȃ�����A�X�L���������΂��Ă݂�
			char output[100];
			if(skillid == BA_FROSTJOKE)
				snprintf(output, sizeof(output), msg_txt(181), md->name); // %s : �����W���[�N !!
			else
				snprintf(output, sizeof(output), msg_txt(182), md->name); // %s : �X�N���[�� !!
			clif_GlobalMessage(&md->bl, output, AREA_CHAT_WOC);
		}
		break;

	case TF_STEAL:			/* �X�e�B�[�� */
		if(sd) {
			if(dstmd && pc_steal_item(sd,dstmd))
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			else
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;

	case RG_STEALCOIN:		/* �X�e�B�[���R�C�� */
		if(sd) {
			if(dstmd && pc_steal_coin(sd,dstmd)) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;

	case MG_STONECURSE:			/* �X�g�[���J�[�X */
		if(status_get_mode(bl)&MD_BOSS) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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

			// �����Ȃ̂�Lv6�ȏ�̓W�F�������
			if(skilllv >= 6) {
				int i, val;
				struct map_session_data *msd = map_bl2msd(src);

				if(msd == NULL)
					break;

				for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
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
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;

	case NV_FIRSTAID:			/* ���}�蓖 */
		{
			int heal = skill_fix_heal(src, bl, skillid, 5);
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case AL_CURE:				/* �L���A�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		break;

	case TF_DETOXIFY:			/* ��� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_DPOISON, -1);
		break;

	case PR_STRECOVERY:			/* ���J�o���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_STUN, -1);
		if( battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) ) {	// �A���f�b�h�Ȃ�ÈŌ���
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
				status_change_pretimer(bl, SC_BLIND,1,0,0,0,30000,0,tick+status_get_amotion(src));
		}
		if(dstmd) {
			mob_unlocktarget(dstmd,tick);
			dstmd->attacked_id = 0;
			dstmd->attacked_players = 0;
		}
		break;

	case WZ_ESTIMATION:			/* �����X�^�[��� */
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

	case MC_IDENTIFY:			/* �A�C�e���Ӓ� */
		if(sd)
			clif_item_identify_list(sd);
		break;

	case WS_WEAPONREFINE:		/* ���퐸�B */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			clif_weapon_refine_list(sd);
		break;

	case BS_REPAIRWEAPON:			/* ����C�� */
		if(sd && dstsd)
			clif_item_repair_list(sd,dstsd);
		break;

	case MC_VENDING:			/* �I�X�J�� */
		if(sd && pc_iscarton(sd)) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,SKILLFAIL_NEARNPC,0,0);
				return 1;
			}
			clif_openvendingreq(sd,2+sd->ud.skilllv);
		}
		break;

	case AL_TELEPORT:			/* �e���|�[�g */
		{
			int alive = 1;
			if(!md || !(md->mode&MD_BOSS) || !battle_config.boss_teleport_on_landprotector) {
				// PC����ш��MOB�̓����h�v���e�N�^�[��ł̓e���|�[�g�s��
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

	case AL_HOLYWATER:			/* �A�N�A�x�l�f�B�N�^ */
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
				*((int *)(&item_tmp.card[2]))=sd->status.char_id;	// �L����ID
			}
			eflag = pc_additem(sd,&item_tmp,1,false);
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
			eflag = pc_additem(sd,&item_tmp,1,false);
			if(eflag) {
				clif_additem(sd,0,0,eflag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		break;

	case RG_STRIPWEAPON:		/* �X�g���b�v�E�F�|�� */
	case RG_STRIPSHIELD:		/* �X�g���b�v�V�[���h */
	case RG_STRIPARMOR:			/* �X�g���b�v�A�[�}�[ */
	case RG_STRIPHELM:			/* �X�g���b�v�w���� */
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
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			strip_fix = 2 * (status_get_dex(src) - status_get_dex(bl));

			if(atn_rand()%1000 > 50 + skilllv*50 + strip_fix)
				break;

			if(dstsd) {
				int i;
				if(equip == LOC_LARM) {
					// �X�g���b�v�V�[���h�͋|�ȊO�̗��蕐��ɂ͎��s
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
				if(i >= MAX_INVENTORY && !md) {	// MOB -> PC �͑��������Ă��Ȃ��Ă�����
					if(sd)
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					break;
				}
			}
			if(bl->type == BL_PC)	// PC�̏ꍇ�̂݌v�Z�����Ⴄ
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));
			status_change_start(bl,scid,skilllv,0,0,0,strip_time,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ST_FULLSTRIP:		/* �t���X�g���b�v */
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
			if(bl->type == BL_PC)	// PC�̏ꍇ�̂݌v�Z�����Ⴄ
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));

			sc = status_get_sc(bl);
			if(dstsd) {
				int i;

				status_calc_pc_stop_begin(&dstsd->bl);
				for(i=0; i<MAX_INVENTORY; i++) {
					if( dstsd->status.inventory[i].equip & LOC_RARM &&
					    (!sc || (sc->data[SC_CP_WEAPON].timer == -1 && sc->data[SC_STRIPWEAPON].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
					if( dstsd->status.inventory[i].equip & LOC_LARM ) {
						// �X�g���b�v�V�[���h�͋|�ȊO�̗��蕐��ɂ͎��s
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
	case AM_POTIONPITCHER:		/* �|�[�V�����s�b�`���[ */
		{
			struct block_list tbl;
			int hp = 0, sp = 0;
			if(sd) {
				int i = pc_search_inventory(sd,skill_db[skillid].lv_itemid[skilllv-1]);

				if(i < 0 || skill_db[skillid].lv_itemid[skilllv-1] <= 0) {
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					map_freeblock_unlock();
					return 1;
				}
				if(sd->inventory_data[i] == NULL || sd->status.inventory[i].amount < skill_db[skillid].lv_amount[skilllv-1]) {
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					map_freeblock_unlock();
					return 1;
				}
				sd->state.potionpitcher_flag = 1;
				memset(&sd->potion,0,sizeof(sd->potion));
				sd->ud.skilltarget = bl->id;
				if(sd->inventory_data[i]->use_script) {
					run_script(sd->inventory_data[i]->use_script,0,sd->bl.id,0);
				}
				pc_delitem(sd,i,skill_db[skillid].lv_amount[skilllv-1],0,1);
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

	case CR_SLIMPITCHER:	/* �X�����|�[�V�����s�b�`���[ */
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

	case AM_BERSERKPITCHER:		/* �o�[�T�[�N�s�b�`���[ */
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
	case CR_FULLPROTECTION:			/* �t���P�~�J���`���[�W */
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

	case SA_DISPELL:			/* �f�B�X�y�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		// �\�E�������J�[�͖���
		if(dstsd && dstsd->status.class_ == PC_CLASS_SL)
			break;
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_ROGUE].timer != -1)	// ���[�O�̍����͖���
			break;
		if(atn_rand()%100 >= skilllv*10+50)
			break;
		status_change_release(bl,0x02);	// �f�B�X�y���ɂ��X�e�[�^�X�ُ����
		break;

	case TF_BACKSLIDING:		/* �o�b�N�X�e�b�v */
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// ������ۑ����Ă����āA������΂���ɖ߂�
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
				pc_heal(sd,0,-sp,0,0);
		}
		break;
	case SA_SPELLBREAKER:	/* �X�y���u���C�J�[ */
		if(sd && status_get_mode(bl)&MD_BOSS && atn_rand()%100 < 90) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
				pc_heal(sd,0,-sp,0,0);
			}
		} else {
			struct unit_data *ud = unit_bl2ud(bl);
			if(ud && ud->skilltimer != -1 && ud->skillid > 0 && skill_get_skill_type(ud->skillid) == BF_MAGIC) {
				int sp = skill_get_sp(ud->skillid,ud->skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				unit_skillcastcancel(bl,0);
				if(dstsd)
					pc_heal(dstsd,0,-sp,0,0);
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
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SA_MAGICROD:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SA_AUTOSPELL:			/* �I�[�g�X�y�� */
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

			// �����E�Ή��E����������
			status_change_attacked_end(bl);

			if(dstmd) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			}
			unit_skillcastcancel(bl,2);	// �r���W�Q
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case PF_SOULCHANGE:		/* �\�E���`�F���W */
		if(sd && dstsd) {
			int sp;
			// PVP,GVG�ȊO�ł�PT�����o�[�ɂ̂ݎg�p��
			if(!map[src->m].flag.pvp && !map[src->m].flag.gvg && battle_check_target(src,bl,BCT_PARTY) <= 0)
				break;
			// �Ώۂ��o�[�T�[�N���łȂ��ꍇ�̂ݎg�p��
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sp = sd->status.sp - dstsd->status.sp;
#ifndef PRE_RENEWAL
			sp = sp / 2;
#endif
			pc_heal(sd,0,-sp,0,0);
			pc_heal(dstsd,0,sp,0,1);
		}
		break;
	case NPC_ATTRICHANGE:	/* �����_�������ω� */
		if(md) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			md->def_ele = atn_rand()%ELE_MAX;
			if(md->def_ele == ELE_UNDEAD)		// �s���͏���
				md->def_ele = ELE_NEUTRAL;
			md->def_ele += (1 + atn_rand()%4) * 20;	// �������x���̓����_��
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
			md->def_ele += (1 + atn_rand()%4) * 20;	// �������x���̓����_��
		} else if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_PROVOCATION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(md && md->skillidx != -1)
			clif_pet_performance(src,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
		break;

	case NPC_SMOKING:			/* �i�� */
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
					pc_heal(dstsd,-hp,0,0,0);
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
			pc_heal(dstsd,0,-100,0,0);
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case NPC_SUICIDE:			/* ���� */
		if(md) {
			md->state.noexp  = 1;
			md->state.nodrop = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			mob_damage(NULL,md,md->hp,3);
		}
		break;

	case NPC_SUMMONSLAVE:		/* �艺���� */
	case NPC_SUMMONMONSTER:		/* MOB���� */
	case NPC_DEATHSUMMON:		/* �f�X�T���� */
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mobdb_search(md->class_)->skill[md->skillidx];
			mob_summonslave(md,ms->val,sizeof(ms->val)/sizeof(ms->val[0]),skilllv,skillid);
		}
		break;
	case NPC_CALLSLAVE:		/* ��芪���Ăі߂� */
		if(md) {
			int mobcount;
			md->recallcount       = 0;	// ������
			md->state.recall_flag = 0;
			mobcount = mob_countslave(md);
			if(mobcount > 0) {
				md->state.recall_flag = 1;	// mob.c��[��芪�������X�^�[�̏���]�ŗ��p
				md->recallmob_count   = mobcount;
			}
		}
		break;
	case NPC_REBIRTH:
		if(md && !md->state.rebirth) {
			// 1�x�����o�[�X���g���ĂȂ��ꍇ�̂ݔ���
			status_change_start(src,SC_REBIRTH,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_RUN:		/* ��� */
		if(md) {
			int dx = dirx[md->dir] * skilllv;
			int dy = diry[md->dir] * skilllv;
			mob_unlocktarget(md,tick);
			unit_walktoxy(&md->bl,md->bl.x-dx,md->bl.y-dy);	// �����̌����Ă�������Ƌt�����Ɉړ�
		}
		break;

	case NPC_TRANSFORMATION:
	case NPC_METAMORPHOSIS:
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mobdb_search(md->class_)->skill[md->skillidx];
			int size = sizeof(ms->val)/sizeof(ms->val[0]);
			if(skilllv > 1)
				mob_summonslave(md,ms->val,size,skilllv-1,0);
			mob_class_change(md,ms->val,size);
		}
		break;

	case NPC_EMOTION:			/* �G���[�V���� */
	case NPC_EMOTION_ON:			/* ���[�h�`�F���W */
		if(md && md->skillidx != -1) {
			clif_emotion(&md->bl,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
			if(mobdb_search(md->class_)->skill[md->skillidx].val[1]) {	// ���[�h�`�F���W
				md->mode = mobdb_search(md->class_)->skill[md->skillidx].val[1];
				unit_stop_walking(&md->bl,1);
				unit_stopattack(&md->bl);
				mob_unlocktarget(md, tick);
				if( md->state.norandomwalk )
					md->state.norandomwalk = 0;
			}
			status_change_end(src,SC_MODECHANGE,-1);
			if(skillid == NPC_EMOTION_ON)
				status_change_start(src,SC_MODECHANGE,skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case WE_MALE:				/* �N�����͌��� */
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
	case WE_FEMALE:				/* ���Ȃ��ɐs�����܂� */
		if(sd && dstsd) {
			int sp_rate = (skilllv <= 0)? 0: skill_db[skillid].sp_rate[skilllv-1];
			int gain_sp;
			// �o�[�T�[�N���̑Ώۂɂ͖���
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			if(battle_config.new_marrige_skill)
				gain_sp = dstsd->status.max_sp;
			else
				gain_sp = sd->status.max_sp;
			gain_sp = gain_sp * abs(sp_rate) / 100;
			clif_skill_nodamage(src,bl,skillid,gain_sp,1);
			battle_heal(NULL,bl,0,gain_sp,0);

			// �X�p�m�r�̉ł��U�߂Ɏg�p�����10%�̊m���ŃX�e�[�^�X�t�^
			if((sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) && sd->sex == SEX_FEMALE && atn_rand()%100 < 10) {
				int sec = skill_get_time2(skillid,skilllv);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,0,sec,0);
				status_change_start(&dstsd->bl,GetSkillStatusChangeTable(skillid),skilllv,2,0,0,sec,0);
			}
		}
		break;

	case WE_CALLPARTNER:			/* ���Ȃ��Ɉ������� */
	case WE_CALLPARENT:			/* �}�}�A�p�p�A���� */
	case WE_CALLBABY:			/* �V��A��������Ⴂ */
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
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						sd->ud.canact_tick  = tick;
						sd->ud.canmove_tick = tick;
						map_freeblock_unlock();
						return 0;
					}
				}
			}
			// �ڂ̑O�ɌĂяo��
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
	case PF_HPCONVERSION:			/* �����͕ϊ� */
		if(sd) {
			if(sd->status.hp <= sd->status.max_hp / 10) {
				clif_skill_fail(sd,skillid,SKILLFAIL_HP,0,0);
			} else {
				int conv_hp = 0, conv_sp = 0;
				clif_skill_nodamage(src, bl, skillid, skilllv, 1);
				conv_hp = sd->status.max_hp / 10; // ��{��MAXHP��10%
				conv_sp = conv_hp * 10 * skilllv / 100;
				if(sd->status.sp + conv_sp > sd->status.max_sp)
					conv_sp = sd->status.max_sp - sd->status.sp;
				pc_heal(sd, -conv_hp, conv_sp,0,1);
			}
		}
		break;
	case HT_REMOVETRAP:				/* �����[�u�g���b�v */
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
				// 㩂����Ԃ�
				struct item item_tmp;
				int eflag;
				if(battle_config.skill_removetrap_type == 1) {
					int i;
					for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
						if(skill_db[su->group->skill_id].itemid[i] <= 0)
							continue;
						memset(&item_tmp,0,sizeof(item_tmp));
						// �ݒu�p�g���b�v�̑���ɉ��ǌ^�ݒu�p�g���b�v������Ă����ꍇ
						if(skill_db[su->group->skill_id].itemid[i] == 1065 && su->group->val3 == 7940) {
							item_tmp.nameid = 7940;
							item_tmp.amount = 1;
						} else {
							item_tmp.nameid = skill_db[su->group->skill_id].itemid[i];
							item_tmp.amount = skill_db[su->group->skill_id].amount[i];
						}
						item_tmp.identify = 1;
						if((eflag = pc_additem(sd,&item_tmp,item_tmp.amount,false))) {
							clif_additem(sd,0,0,eflag);
							map_addflooritem(&item_tmp,item_tmp.amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
						}
					}
				} else {
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid   = su->group->val3;
					item_tmp.identify = 1;
					if((eflag = pc_additem(sd,&item_tmp,1,false))) {
						clif_additem(sd,0,0,eflag);
						map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
					}
				}

			}
			skill_delunit(su);
		}
		break;
	case HT_SPRINGTRAP:				/* �X�v�����O�g���b�v */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(bl->type == BL_SKILL) {
			struct skill_unit *su = (struct skill_unit *)bl;
			if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
				break;
			if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2 > 0)		// �⑫���͔j��s��
				break;
			su->group->unit_id = UNT_USED_TRAPS;
			clif_changelook(bl,LOOK_BASE,su->group->unit_id);
			su->group->limit = su->limit = DIFF_TICK(tick+1500,su->group->tick);
		}
		break;
	case BD_ENCORE:					/* �A���R�[�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			unit_skilluse_id(&sd->bl,src->id,sd->skill_dance.id,sd->skill_dance.lv);
		break;
	case AS_SPLASHER:		/* �x�i���X�v���b�V���[ */
		if(
#ifdef PRE_RENEWAL
			(atn_bignumber)status_get_max_hp(bl)*3/4 < status_get_hp(bl) ||
#endif
			status_get_mode(bl)&MD_BOSS) {
			// HP��3/4�ȏ�c���Ă��邩���肪�{�X�����Ȃ玸�s
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			map_freeblock_unlock();
			return 1;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case ASC_EDP:			/* �G���`�����g�f�b�h���[�|�C�Y�� */
		{
			int time = skill_get_time(skillid,skilllv);
			if(sd)
				time += pc_checkskill(sd,GC_RESEARCHNEWPOISON) * 3000;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,time,0);
#ifndef PRE_RENEWAL
			// pre���̌v�Z�����s���̂���RE����
			status_change_start(bl,SC_MAGNUM,skilllv,ELE_POISON,0,0,time,0);
#endif
		}
		break;
	case RG_CLOSECONFINE:		/* �N���[�Y�R���t�@�C�� */
		{
			int dir;
			if(status_get_mode(bl)&MD_BOSS) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
	case NPC_STOP:			/* �z�[���h�E�F�u */
		status_change_start(src,GetSkillStatusChangeTable(skillid),1,1,src->id,bl->id,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),1,2,bl->id,src->id,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_REDEMPTIO:		/* ���f���v�e�B�I */
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
			pc_heal(sd, -sd->status.hp + 1, -sd->status.sp, 0, 0);

			// �o���l�y�i���e�B
			if(skill_area_temp[0] < 5) {
				int per = (5 - skill_area_temp[0]) * 20;
				pc_exp_penalty(sd, NULL, per, 3);
			}
		}
		break;

	case MO_KITRANSLATION:		/* �C���]�� */
		if(dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),1);
		}
		break;
	case BS_GREED:			/* �O���[�h */
		if (sd && (battle_config.greed_use_town || !map[src->m].flag.town) && !map[src->m].flag.pvp && !map[src->m].flag.gvg) {	// �X�EPvP�EGvG�ł͎g�p�s��
			struct party *p = NULL;
			int ar = skill_get_area(skillid,skilllv);
			if(sd->status.party_id > 0)
				p = party_search(sd->status.party_id);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_greed,sd->bl.m,sd->bl.x-ar,sd->bl.y-ar,sd->bl.x+ar,sd->bl.y+ar,BL_ITEM,sd,p);
		}
		break;

	case GD_BATTLEORDER:		/* �Ր�Ԑ� */
	case GD_REGENERATION:		/* ���� */
	case GD_RESTORE:		/* ���� */
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
						// �o�[�T�[�N���̃����o�[�ɂ͎g�p�s��
						if(member->sc.data[SC_BERSERK].timer != -1)
							continue;
						pc_heal(member, member->status.max_hp * 90 / 100, member->status.max_sp * 90 / 100, 0, 0);
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
	case GD_EMERGENCYCALL:		/* �ً}���W */
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
				if(member->bl.id == sd->bl.id)	// �������g�͏��O
					continue;
				if(battle_config.emergencycall_call_limit && sd->bl.m != member->bl.m)	// ���}�b�v�̂�
					continue;
				if(member->state.refuse_emergencycall)
					continue;

				if(count <= 0) {
					// ����
					px = sd->bl.x;
					py = sd->bl.y;
				} else {
					int idx = atn_rand()%count;
					px = free_cell[idx].x;
					py = free_cell[idx].y;
					if(battle_config.emergencycall_point_type == 2 &&
					   path_search(NULL,sd->bl.m,sd->bl.x,sd->bl.y,px,py,0))
					{
						// �R�z��EMC�֎~
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
			// ���ɓo�^�ς�
			if(sd->hate_mob[skilllv-1] != -1) {
				clif_hate_info(sd,skilllv,sd->hate_mob[skilllv-1]);
				break;
			}
			if(dstsd) {	// �o�^���肪PC
				sd->hate_mob[skilllv-1] = dstsd->status.class_;
				if(battle_config.save_hate_mob)
					pc_setglobalreg(sd,"PC_HATE_MOB_STAR",sd->hate_mob[skilllv-1]+1);
				clif_skill_nodamage(src,src,skillid,skilllv,1);
				clif_hate_mob(sd,skilllv,sd->hate_mob[skilllv-1]);
			} else if(dstmd) {	// �o�^���肪MOB
				switch(skilllv) {
				case 1:
					if(status_get_size(bl) == 0) {
						sd->hate_mob[0] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_SUN", sd->hate_mob[0]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[0]);
					} else {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					}
					break;
				default:
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
	case SL_ALCHEMIST:		/* �A���P�~�X�g�̍� */
	case SL_MONK:			/* �����N�̍� */
	case SL_STAR:			/* �P���Z�C�̍� */
	case SL_SAGE:			/* �Z�[�W�̍� */
	case SL_CRUSADER:		/* �N���Z�C�_�[�̍� */
	case SL_KNIGHT:			/* �i�C�g�̍� */
	case SL_WIZARD:			/* �E�B�U�[�h�̍� */
	case SL_PRIEST:			/* �v���[�X�g�̍� */
	case SL_SUPERNOVICE:		/* �X�[�p�[�m�[�r�X�̍� */
	case SL_BARDDANCER:		/* �o�[�h�ƃ_���T�[�̍� */
	case SL_ROGUE:			/* ���[�O�̍� */
	case SL_ASSASIN:		/* �A�T�V���̍� */
	case SL_BLACKSMITH:		/* �u���b�N�X�~�X�̍� */
	case SL_HUNTER:			/* �n���^�[�̍� */
	case SL_SOULLINKER:		/* �\�E�������J�[�̍� */
	case SL_DEATHKNIGHT:		/* �f�X�i�C�g�̍� */
	case SL_COLLECTOR:		/* �_�[�N�R���N�^�[�̍� */
	case SL_NINJA:			/* �E�҂̍� */
	case SL_GUNNER:			/* �K���X�����K�[�̍� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SL_HIGH:			/* �]���ꎟ�E�Ƃ̍� */
		if(status_get_lv(bl) < 11 || status_get_lv(bl) > 70) {   // �Ώۂ̃x�[�X���x����11�ȉ��A�܂���70�ȏゾ�Ǝg�p�s��
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_MADNESSCANCEL:		/* �}�b�h�l�X�L�����Z���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			status_change_end(bl, GetSkillStatusChangeTable(skillid), -1);
		} else {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case GS_ADJUSTMENT:			/* �A�W���X�g�����g */
		sc = status_get_sc(bl);
		if(!sc || sc->data[SC_MADNESSCANCEL].timer == -1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case GS_CRACKER:			/* �N���b�J�[ */
		{
			int cost = skill_get_arrow_cost(skillid,skilllv);
			int rate;
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// �e�̏���
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			rate = 5000 - (unit_distance(src,bl) / 3) * 1000;
			if(rate < 2000)
				rate = 2000;

			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,rate,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case NJ_BUNSINJYUTSU:		/* �e���g */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_NEN].timer != -1)
			status_change_end(bl,SC_NEN,-1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case ALL_BUYING_STORE:			/* ����I�X�J�� */
		if(sd) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,SKILLFAIL_NEARNPC,0,0);
				return 1;
			}
			buyingstore_openstorewindow(sd, MAX_BUYINGSTORE_COUNT);
		}
		break;
	case ALL_WEWISH:			/* �z�[���[�i�C�g */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case RETURN_TO_ELDICASTES:		/* �G���f�B�J�X�e�B�X�ւ̋A�� */
	case ALL_GUARDIAN_RECALL:		/* ���[���ւ̋A�� */
	case ECLAGE_RECALL:		/* �G�N���[�W���ւ̋A�� */
	case ALL_NIFLHEIM_RECALL:		/* �j�u���w�C���ւ̋A�� */
	case ALL_PRONTERA_RECALL:		/* �v�����e���ւ̋A�� */
	case ALL_GLASTHEIM_RECALL:		/* �O���X�g�w�C���ւ̋A�� */
	case ALL_THANATOS_RECALL:		/* �^�i�g�X�^���[�ւ̋A�� */
	case ALL_LIGHTHALZEN_RECALL:	/* ���q�^���[���ւ̋A�� */
		if(sd) {
			int x, y;
			const char *mapname;

			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportal�ŋ֎~
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
			} else if(skillid == ALL_NIFLHEIM_RECALL) {
				x = 193;
				y = 186;
				mapname = "niflheim.gat";
			} else if(skillid == ALL_PRONTERA_RECALL) {
				x = (skilllv==1)? 115: 159;
				y = (skilllv==1)? 72: 192;
				mapname = "prontera.gat";
			} else if(skillid == ALL_GLASTHEIM_RECALL) {
				x = 200;
				y = 268;
				mapname = "glast_01.gat";
			} else if(skillid == ALL_THANATOS_RECALL) {
				x = 139;
				y = 156;
				mapname = "hu_fild01.gat";
			} else if(skillid == ALL_LIGHTHALZEN_RECALL) {
				x = 307;
				y = 307;
				mapname = "lighthalzen.gat";
			} else {
				x = 47;
				y = 31;
				mapname = "ecl_in01.gat";
			}

			if(pc_setpos(sd,mapname,x,y,0)) {
				// �}�b�v�����݂��Ȃ�����
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 0;
			}
		}
		break;
	case HAMI_CASTLE:		/* �L���X�����O */
		if(hd && hd->msd && atn_rand()%100 < 20*skilllv)
		{
			int x, y;
			struct map_session_data *msd = hd->msd;
			if( path_search(NULL,hd->bl.m,hd->bl.x,hd->bl.y,msd->bl.x,msd->bl.y,0) != 0 ) {
				// �L���X�����O��p�����ǉz���֎~
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
	case HVAN_CHAOTIC:		/* �J�I�e�B�b�N�x�l�f�B�N�V���� */
		if(hd) {
			struct block_list* heal_target = NULL;
			int n = (skilllv < 5)? skilllv - 1: 4;
			int rnd = atn_rand()%100;
			static const int per[5][2] = {
				{20,50},{50,60},{25,75},{60,64},{34,67}
			};

			if(rnd < per[n][0]) {
				// �z��
				heal_target = &hd->bl;
			} else if(rnd < per[n][1]) {
				// ��l
				if(!unit_isdead(&hd->msd->bl))	// ����
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
				// �G�t�F�N�g�o�Ȃ��̂Ńq�[��
				clif_skill_nodamage(src,heal_target,AL_HEAL,heal,1);
				clif_skill_nodamage(src,heal_target,skillid,heal,1);
				battle_heal(NULL,heal_target,heal,0,0);
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
			}
		}
		break;
	case HLIF_AVOID:		/* �ً}��� */
	case HAMI_DEFENCE:		/* �f�B�t�F���X */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			// ��l�ɂ�
			if(hd->msd && !unit_isdead(&hd->msd->bl)) {
				clif_skill_nodamage(src,&hd->msd->bl,skillid,skilllv,1);
				status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HAMI_BLOODLUST:		/* �u���b�h���X�g */
	case HFLI_FLEET:		/* �t���[�g���[�u */
	case HFLI_SPEED:		/* �I�[�o�[�h�X�s�[�h */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HLIF_CHANGE:		/* �����^���`�F���W */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		unit_heal(src,status_get_max_hp(src),0,0,0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case MH_GOLDENE_FERSE:	/* �S�[���f���y���W�F */
	case MH_ANGRIFFS_MODUS:	/* �A���O���t�X���h�X */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_SUMMON_LEGION:	/* �T�������M�I�� */
		if(hd && hd->msd) {
			const int summons[5] = {2158, 2159, 2159, 2160, 2160};
			const int qty[5]     = {3   , 3   , 4   , 4   , 5};
			struct mob_data *tmpmd = NULL;
			int i,id;

			// ���M�I�������X�^�[�̍폜
			homun_deletelegion(hd);

			for(i=0; i<qty[skilllv - 1]; i++){
				id = mob_once_spawn_area(hd->msd, src->m, src->x-2, src->y-2, src->x+2, src->y+2, "--ja--", summons[skilllv - 1], 1, "");
				if((tmpmd = map_id2md(id)) != NULL) {
					tmpmd->master_id =  src->id;
					tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
					tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
					tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
					tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
					tmpmd->target_id = bl->id;
					tmpmd->min_chase = 5 + path_distance(src->x,src->y,bl->x,bl->y);
					tmpmd->state.master_check = 1;
					tmpmd->state.norandomwalk = 1;
					tmpmd->state.special_mob_ai = MOB_AI_LEGION;
				}
			}
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_PAIN_KILLER:	/* �y�C���L���[ */
		if(hd && hd->msd && bl->type != BL_PC && bl->type != BL_HOM) {
			clif_emotion(src,9);
			clif_skill_fail(hd->msd, skillid, SKILLFAIL_TOTARGET, 0, 0);
			return 0;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,status_get_lv(src),status_get_lv(bl),0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_ENDURE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_LIGHT_OF_REGENE:	/* �Đ��̌� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(hd) {
			hd->intimate -= 10000;
			if(battle_config.homun_skill_intimate_type)
				hd->status.intimate = 1;
			clif_send_homdata(hd->msd,1,hd->intimate/100);
			status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_OVERED_BOOST:	/* �I�[�o�[�h�u�[�X�g */
	case MH_GRANITIC_ARMOR:	/* �O���j�e�B�b�N�A�[�}�[ */
	case MH_PYROCLASTIC:	/* �p�C���N���X�e�B�b�N */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(hd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid==MH_PYROCLASTIC? status_get_lv(bl): 0,skill_get_time(skillid,skilllv),0);
			status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid==MH_PYROCLASTIC? status_get_lv(bl): 0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_SILENT_BREEZE:	/* �T�C�����g�u���[�Y */
		{
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));

			// �G�t�F�N�g�o�Ȃ��̂Ńq�[��
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
			status_change_end(bl, SC_HALLUCINATION, -1);
			status_change_end(bl, SC_CONFUSION, -1);
			status_change_end(bl, SC_SLEEP, -1);
			status_change_end(bl, SC_HARMONIZE, -1);
			status_change_end(bl, SC_DEEP_SLEEP, -1);
			status_change_end(bl, SC_MANDRAGORA, -1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(hd) {
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
			}
		}
		break;
	case MH_STYLE_CHANGE:	/* �X�^�C���`�F���W */
		if(hd) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_STYLE_CHANGE].timer != -1) {
				if(sc->data[SC_STYLE_CHANGE].val1 == 1) sc->data[SC_STYLE_CHANGE].val1 = 2;
				else sc->data[SC_STYLE_CHANGE].val1 = 1;
			}
			else
				status_change_start(bl,SC_STYLE_CHANGE,1,0,0,0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case MH_MAGMA_FLOW:		/* �}�O�}�t���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_STEINWAND:			/* �V���^�C�������h */
		if(hd && hd->msd) {
			skill_castend_pos2(src,src->x,src->y,skillid,skilllv,tick,0);
			skill_castend_pos2(src,hd->msd->bl.x,hd->msd->bl.y,skillid,skilllv,tick,0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case NPC_DRAGONFEAR:		/* �h���S���t�B�A�[ */
	case NPC_WIDESILENCE:		/* �͈͒��ٍU�� */
	case NPC_WIDEFREEZE:		/* �͈͓����U�� */
	case NPC_WIDEBLEEDING:		/* �͈͏o���U�� */
	case NPC_WIDESTONE:		/* �͈͐Ή��U�� */
	case NPC_WIDECONFUSE:		/* �͈͍����U�� */
	case NPC_WIDESLEEP:		/* �͈͐����U�� */
	case NPC_WIDECURSE:		/* �͈͎􂢍U�� */
	case NPC_WIDESTUN:		/* �͈̓X�^���U�� */
	case NPC_WIDEHELLDIGNITY:	/* �w���f�B�O�j�e�B */
		if(flag&1) {
			if(skillid == NPC_DRAGONFEAR) {
				const int sc_type[4] = { SC_STUN, SC_CONFUSION, SC_SILENCE, SC_BLEED };
				int n = atn_rand() % 4;
				// upkeep_time2�͔z��̓Y�����ɏ]��
				if(atn_rand() % 10000 < status_change_rate(bl,sc_type[n],10000,status_get_lv(src)))
					status_change_pretimer(bl,sc_type[n],skilllv,0,0,0,skill_get_time2(skillid,n+1),0,tick+status_get_amotion(src));
			} else {
				if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			//clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESIGHT:		/* ���C�h�T�C�g */
		clif_skill_nodamage(src,bl,MG_SIGHT,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_SLOWCAST:		/* �X���E�L���X�g */
		if(flag&1) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESOULDRAIN:	/* �}�i�o�[�� */
		if(flag&1) {
			if(dstsd) {
				int sp = dstsd->status.max_sp * (((skilllv - 1) % 5 + 1) * 20) / 100;
				if(sp < 1) sp = 1;
				pc_heal(dstsd,0,-sp,0,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_TALK:			/* �g�[�N */
		if(md && md->skillidx != -1) {
			mob_talk(md,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
		}
		break;
	case NPC_INVINCIBLE:		/* �C���r���V�u�� */
		status_change_end(bl, SC_INVINCIBLEOFF, -1);
	case NPC_INVINCIBLEOFF:		/* �C���r���V�u���I�t */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_PULSESTRIKE2:		/* �p���X�X�g���C�NII */
		{
			int i;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i = 0; i < 3; i++) {
				skill_addtimerskill(src,tick + 1000 * i,bl->id,0,0,skillid,skilllv,0,0x0500);
			}
		}
		break;
	case NPC_LEX_AETERNA:		/* M���b�N�X�G�[�e���i */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_WIDEWEB:		/* ���C�h�E�F�u */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(flag&1) {
			skill_castend_pos2(src,bl->x,bl->y,PF_SPIDERWEB,skilllv,tick,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_FIRESTORM:		/* ���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESUCK:		/* ���C�h�u���b�h */
		{
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 15 / 100);
			if(heal > 0) {
				struct block_list tbl;
				memset(&tbl, 0, sizeof(tbl));
				tbl.m = src->m;
				tbl.x = skill_area_temp[2];
				tbl.y = skill_area_temp[3];
				clif_damage(src,bl,tick,0,0,heal,0,0,0,0);
				clif_skill_nodamage(&tbl,src,AL_HEAL,heal,1);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_heal(NULL,bl,-heal,0,0);
				battle_heal(NULL,src,heal,0,0);
			}
		}
		break;
	case NPC_ELECTRICWALK:	/* M�G���N�g���b�N�E�H�[�N */
	case NPC_FIREWALK:		/* M�t�@�C�A�[�E�H�[�N */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_MANDRAGORA:		/* M�n�E�����O�I�u�}���h���S�� */
		if(flag&1) {
			if(atn_rand() % 10000 < 2000 * skilllv) {
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
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_LEASH:	/* �f�X�n���h */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(battle_check_target(src,bl,BCT_ENEMY) > 0 && !map[bl->m].flag.gvg && !(status_get_mode(bl)&MD_BOSS)) {
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
		break;
	case NPC_WIDELEASH:		/* ���C�h�f�X�n���h */
		if(flag&1) {
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
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDEDISPEL:			/* ���C�h�f�B�X�y�� */
		if(flag&1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			// �\�E�������J�[�͖���
			if(dstsd && dstsd->status.class_ == PC_CLASS_SL)
				break;
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_ROGUE].timer != -1)	// ���[�O�̍����͖���
				break;
			status_change_release(bl,0x02);	// �f�B�X�y���ɂ��X�e�[�^�X�ُ����
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_ALL_STAT_DOWN:		/* �I�[���X�e�[�^�X�_�E�� */
		{
			int val = (skilllv>=5)? 100: skilllv*20 - 10;
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_GRADUAL_GRAVITY:		/* �O���f���A���O���r�e�B */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skilllv*30,0,0,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src, bl, skillid, skilllv, 1);
		break;
	case NPC_DAMAGE_HEAL:		/* �_���[�W�q�[�� */
	case NPC_KILLING_AURA:	/* �L�����O�I�[�� */
		clif_skill_nodamage(src, bl, skillid, skilllv, 1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_IMMUNE_PROPERTY:		/* �C�~���[���v���p�e�B */
		{
			const int sc_type[10] = {
				SC_IMMUNE_PROPERTY_NOTHING, SC_IMMUNE_PROPERTY_WATER,
				SC_IMMUNE_PROPERTY_GROUND, SC_IMMUNE_PROPERTY_FIRE, 
				SC_IMMUNE_PROPERTY_WIND, SC_IMMUNE_PROPERTY_DARKNESS,
				SC_IMMUNE_PROPERTY_SAINT, SC_IMMUNE_PROPERTY_POISON,
				SC_IMMUNE_PROPERTY_TELEKINESIS, SC_IMMUNE_PROPERTY_UNDEAD
			};
			if(skilllv >= 1 && skilllv <= 10) {
				clif_skill_nodamage(src, bl, skillid, skilllv, 1);
				status_change_start(bl,sc_type[skilllv-1],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case NPC_MOVE_COORDINATE:		/* �|�W�V�����`�F���W */
		{
			int tx = bl->x, ty = bl->y;
			if (unit_movepos(bl, src->x, src->y, 0))
				return 0;

			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);
			clif_blown(bl,src->x,src->y);

			if(!(status_get_mode(src)&MD_BOSS)) {
				if (unit_movepos(src, tx, ty, 0))
					return 0;
				clif_blown(src,tx,ty);
			}
		}
		break;
	case MER_REGAIN:		/* ���Q�C�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_SLEEP, -1);
		break;
	case MER_TENDER:		/* �e���_�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		break;
	case MER_BENEDICTION:		/* �x�l�f�B�N�V���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		break;
	case MER_RECUPERATE:		/* ���L���|���C�g */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_POISON, -1);
		break;
	case MER_MENTALCURE:		/* �����^���L���A */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		break;
	case MER_COMPRESS:		/* �R���v���X */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_BLEED, -1);
		break;
	case MER_SCAPEGOAT:		/* �g���� */
		if(mcd && mcd->msd) {
			int hp = status_get_hp(&mcd->bl);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_heal(mcd->msd,hp,0,0,0);
			battle_damage(NULL,&mcd->bl,hp,skillid,skilllv,flag);
		}
		break;
	case MER_INVINCIBLEOFF2:	/* �}�C���h�u���X�^�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		if(mcd)
			mcd->skillstatictimer[skillid-MERC_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case RK_ENCHANTBLADE:		/* �G���`�����g�u���C�h */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,status_get_int(src),0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_DRAGONHOWLING:	/* �h���S���n�E�����O */
		if(flag&1) {
			if(atn_rand() % 100 < 50 + skilllv * 6)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case RK_CRUSHSTRIKE:		/* �N���b�V���X�g���C�N */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_STONEHARDSKIN:		/* �X�g�[���n�[�h�X�L�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),((sd)? sd->status.job_level: 0),0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_REFRESH:			/* ���t���b�V�� */
		{
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 25 / 100);
			battle_heal(NULL,bl,heal,0,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x08);		// �b��ŃS�X�y���S��Ԉُ햳���Ɠ�����
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_FIGHTINGSPIRIT:		/* �t�@�C�e�B���O�X�s���b�g */
		if(flag&1) {
			if(src != bl && skill_area_temp[0])
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7/4,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			skill_area_temp[0] = 0;
			if(sd && sd->status.party_id > 0) {
				skill_area_temp[0] = party_check_same_map_member_count(sd);
				/* �p�[�e�B�S�̂ւ̏��� */
				party_foreachsamemap(skill_area_sub,
					sd,skill_get_area(skillid,skilllv),
					src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_LUXANIMA:		/* ���N�X�A�j�} */
		{
			const int runes[6] = { SC_MILLENNIUMSHIELD, SC_REFRESH, SC_GIANTGROWTH, SC_STONEHARDSKIN, SC_VITALITYACTIVATION, SC_ABUNDANCE };

			if(sd == NULL || sd->status.party_id == 0 || flag&1) {
				if(src->id == bl->id)
					break;

				status_change_start(bl, runes[skill_area_temp[5]], skilllv, 0, 0, 0, skill_get_time(skillid, skilllv),0);
			} else if(sd) {
				int recent = 0, result = -1;
				int i;

				for(i = 0; i < 6; i++) {
					if(sd->sc.data[runes[i]].timer != -1 && ((sd->sc.data[runes[i]].timer * (runes[i] == SC_REFRESH? 3 : 1)) > recent || recent == 0)) {
						recent = sd->sc.data[runes[i]].timer;
						result = i;
					}
				}

				if(result != -1) {
					skill_area_temp[5] = result;
					status_change_end(src, runes[result], -1);
					party_foreachsamemap(skill_area_sub,sd,skill_get_area(skillid,skilllv),src,skillid,skilllv,tick, flag|BCT_PARTY|1,skill_castend_nodamage_id);
					clif_skill_nodamage(src, src, skillid, skilllv, 1);
				}
			}
		}
		break;
	case GC_CREATENEWPOISON:	/* �V�Ő��� */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_NEWPOISON,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GC_ANTIDOTE:			/* �A���`�h�[�g */
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
	case GC_POISONINGWEAPON:	/* �|�C�Y�j���O�E�F�|�� */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_poison_list(sd,skilllv);
		}
		break;
	case AB_ANCILLA:			/* �A���V�� */
		if(sd) {
			struct item item_tmp;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 12333;
			item_tmp.identify = 1;
			pc_additem(sd,&item_tmp,1,false);
		}
		break;
	case AB_CLEMENTIA:		/* �N�������e�B�A */
	case AB_CANTO:			/* �J���g�L�����f�B�_�X */
	case AB_CHEAL:			/* �R���Z�I�q�[�� */
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
						heal = 0; 	// �o�[�T�[�N���̓q�[���O

					if(pc_isgear(dstsd))
						heal = 0; 	// �����M�A���撆�̓q�[���O
				}

				clif_skill_nodamage(&sd->bl,bl,skillid,heal,1);
				battle_heal(&sd->bl,bl,heal,0,0);
			} else {
				clif_skill_nodamage(&sd->bl,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),lv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(skillid == AB_CHEAL) {
				// �l�����m�F
				skill_area_temp[0] = 0;

				party_foreachsamemap(skill_area_sub,
					sd,ar,
					src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_area_sub_count);
			}
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_PRAEFATIO:		/* �v���G�t�@�e�B�I */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* �ʂ̏��� */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if( sd == NULL || sd->status.party_id == 0 )
				skill_area_temp[0] = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skill_area_temp[0],skill_get_time(skillid,skilllv),0);	// �L���G�G���C�\���Ƌ�ʂ��邽�߂�val4��skillid���i�[
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			/* �p�[�e�B�S�̂ւ̏��� */
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
	case AB_ORATIO:	/* �I���e�B�I */
		if(flag&1) {
			if(atn_rand() % 100 < 40 + skilllv * 5)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_LAUDAAGNUS:		/* ���E�_�A�O�k�X */
	case AB_LAUDARAMUS:		/* ���E�_�����X */
		if(sd == NULL)
			break;
		if(flag&1 || sd->status.party_id == 0) {
			/* �ʂ̏��� */
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
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_RENOVATIO:			/* ���m���@�e�B�I */
		{	// �t�^�Ɠ����Ƀq�[��
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * (skilllv * 2 + 1) / 100);
			if(heal) {
				if(sc && sc->data[SC_AKAITSUKI].timer != -1)
					unit_fixdamage(bl,bl,gettick(),0,status_get_dmotion(bl),heal,0,0,0,0);
				else
					unit_heal(bl,heal,0,0,1);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case AB_EXPIATIO:			/* �G�N�X�s�A�e�B�I */
	case AB_SECRAMENT:			/* �T�N�������g */
		if(battle_check_target(src,bl,BCT_NOENEMY) > 0) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		break;
	case AB_CLEARANCE:		/* �N���A�����X */
		if(atn_rand() % 100 < 60 + skilllv * 8) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x200);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case AB_SILENTIUM:	/* �V�����e�B�E�� */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_WHITEIMPRISON:	/* �z���C�g�C���v���Y�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if( src == bl || (sc && sc->data[SC_WHITEIMPRISON].timer == -1) && (battle_check_target(src,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS) )) {
			int rate = 0;

			if(src == bl) rate = 100;
			else if(bl->type == BL_PC) rate = 20 + skilllv * 10;
			else rate = 40 + skilllv * 10;

			if( atn_rand() % 100 < rate )
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,(src == bl)? 5000: skill_get_time(skillid,skilllv),0);
			else if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		break;
	case WL_SIENNAEXECRATE:	/* �V�G�i�G�N�Z�N���C�g */
		if(flag&1) {
			if(!battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) && atn_rand() % 10000 < status_change_rate(bl,SC_STONE,skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STONE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_STASIS:		/* �X�e�C�V�X */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_TETRAVORTEX:		/* �e�g���{���e�b�N�X */
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
								case 1:		// �T�����{�[�����C�g�j���O
									summon_id[c] = WL_TETRAVORTEX_WIND;
									break;
								case 2:		// �T�����E�H�[�^�[�{�[��
									summon_id[c] = WL_TETRAVORTEX_WATER;
									break;
								case 3:		// �T�����X�g�[��
									summon_id[c] = WL_TETRAVORTEX_GROUND;
									break;
								default:	// �T�����t�@�C�A�[�{�[��
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
				skill_addtimerskill(src,tick + 200 * i,bl->id,0,0,summon_id[i],skilllv,0,0x0500);
			}
			status_change_pretimer(bl,GetSkillStatusChangeTable(summon_id[atn_rand()%4]),skilllv,0,0,0,skill_get_time(summon_id[atn_rand()%4],skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_SUMMONFB:		/* �T�����t�@�C�A�{�[�� */
	case WL_SUMMONBL:		/* �T�����{�[�����C�g�j���O */
	case WL_SUMMONWB:		/* �T�����E�H�[�^�[�{�[�� */
	case WL_SUMMONSTONE:	/* �T�����X�g�[�� */
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
				clif_skill_fail(sd,skillid,SKILLFAIL_SUMMON_OVER,0,0);
		}
		break;
	case WL_RELEASE:	/* �����[�X */
		sc = status_get_sc(src);
		if(sc) {
			/* �ێ��X�y��������ꍇ */
			if(sd && pc_checkskill(sd,sd->freeze_sp_skill[0]) > 0 && sc->data[SC_SPELLBOOK].timer != -1) {
				int freeze_skillid = sd->freeze_sp_skill[0];
				int freeze_skilliv = pc_checkskill(sd,freeze_skillid);

				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				if(skill_get_inf(freeze_skillid)&INF_GROUND) {	// �ꏊ�w��̃X�L��
					skill_castend_pos2(src,bl->x,bl->y,freeze_skillid,freeze_skilliv,tick,0);
				} else if(skill_get_nk(freeze_skillid)&1){
					skill_castend_nodamage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				} else {
					skill_castend_damage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				}
				memmove(&sd->freeze_sp_skill[0],&sd->freeze_sp_skill[1],sizeof(sd->freeze_sp_skill[0])*(MAX_FREEZE_SPELL-1));
				memset(&sd->freeze_sp_skill[MAX_FREEZE_SPELL-1], 0, sizeof(sd->freeze_sp_skill[0]));
				sd->freeze_sp_slot -= skill_get_spellslot(freeze_skillid);

				// �ۑ��X�L����S�Ďg�p
				if(sd->freeze_sp_skill[0] == 0) {
					status_change_end(src,SC_SPELLBOOK,-1);
				}
			} else {
				int i, j = 0;
				for(i = 0; i < 5; i++) {
					if(sc->data[SC_SUMMONBALL1 + i].timer != -1) {
						if(j == 0) {	// �G�t�F�N�g��1���ڂ̂�
							clif_skill_nodamage(src,bl,skillid,skilllv,1);
						}
						skill_addtimerskill(src,tick + status_get_adelay(src) * j,bl->id,0,0,WL_SUMMON_ATK_FIRE + sc->data[SC_SUMMONBALL1 + i].val2,sc->data[SC_SUMMONBALL1 + i].val1,0,(0x0f<<20)|flag);
						status_change_end(src,SC_SUMMONBALL1 + i,-1);
						j++;
						if(skilllv < 2) {		// SkillLv2�͑S�ẴT�����{�[��������
							break;
						}
					}
				}
				if(j <= 0 && sd) {	// �T�����{�[������������
					clif_skill_fail(sd,skillid,SKILLFAIL_SUMMON_NOTHING,0,0);
				}
			}
		}
		break;
	case WL_READING_SB:	/* ���[�f�B���O�X�y���u�b�N */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_reading_sb_list(sd);
		}
		break;
	case RA_WUGMASTERY:	/* �E�H�[�O�}�X�^���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd) && pc_checkskill(sd,WH_HAWK_M) > 0) {	// ���A��Ă��ăz�[�N�}�X�^���[�K���ς�
				if(pc_iswolf(sd)) {
					pc_setoption(sd,sd->sc.option & ~OPTION_WUG);
				} else {
					pc_setoption(sd,OPTION_WUG | OPTION_FALCON);
				}
			}
			else if(pc_iswolf(sd)) {
				pc_setoption(sd,OPTION_NOTHING);
			} else {
				pc_setoption(sd,OPTION_WUG);
			}
		}
		break;
	case RA_WUGRIDER:	/* �E�H�[�O���C�_�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd) && pc_checkskill(sd,WH_HAWK_M) > 0) {	// ���A��Ă��ăz�[�N�}�X�^���[�K���ς�
				if(pc_iswolfmount(sd)) {
					pc_setoption(sd,OPTION_WUG | OPTION_FALCON);
				} else {
					pc_setoption(sd,OPTION_WUGRIDER | OPTION_FALCON);
				}
			}
			else if(pc_iswolfmount(sd)) {
				pc_setoption(sd,OPTION_WUG);
			} else {
				pc_setoption(sd,OPTION_WUGRIDER);
			}
		}
		break;
	case RA_WUGDASH:	/* �E�H�[�O�_�b�V�� */
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
	case NC_F_SIDESLIDE:	/* �t�����g�T�C�h�X���C�h */
	case NC_B_SIDESLIDE:	/* ���A�T�C�h�X���C�h */
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

			// ������ۑ����Ă����āA������΂���ɖ߂�
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
	case NC_EMERGENCYCOOL:	/* �G�}�[�W�F���V�[�N�[�� */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_OVERHEAT_LIMITPOINT].timer != -1) {
			int heat = sc->data[SC_OVERHEAT_LIMITPOINT].val1;
			heat -= 45;
			if(heat > 0)
				sc->data[SC_OVERHEAT_LIMITPOINT].val1 = heat;
			else
				status_change_end(bl, SC_OVERHEAT_LIMITPOINT, -1);
			// �I�[�o�[�q�[�g�̏I�������status_change_timer�Ŕ���
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NC_INFRAREDSCAN:	/* �C���t�����b�h�X�L���� */
		if(flag&1) {
			skill_detect(bl);		// �f�B�e�B�N�g����
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_ANALYZE:		/* �A�i���C�Y */
		if(atn_rand() % 10000 < 2000 + (skilllv - 1) * 4000) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case NC_MAGNETICFIELD:	/* �}�O�l�e�B�b�N�t�B�[���h */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				unit_stop_walking(bl,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			// �z�o�[�����O��Ԃ���Ȃ���Ύ��M�ɂ���Ԉُ�
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_NEUTRALBARRIER:		/* �j���[�g�����o���A�[ */
	case NC_STEALTHFIELD:		/* �X�e���X�t�B�[���h */
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
	case NC_REPAIR:			/* ���y�A */
		if(dstsd && pc_isgear(dstsd)) {
			static const int repair[] = { 20, 23, 35, 40, 50 };
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * ((skilllv > 5)? repair[4]: repair[skilllv-1]) / 100);
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		}
		break;
	case SC_AUTOSHADOWSPELL:	/* �I�[�g�V���h�E�X�y�� */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_autoshadowspell(sd,skilllv);
		}
		break;
	case SC_SHADOWFORM:			/* �V���h�E�t�H�[�� */
		if(sd) {
			if(dstsd && dstsd->shadowform_id == 0) {
				if(sd->bl.id == dstsd->bl.id ||
				   ((!map[src->m].flag.pvp && !map[src->m].flag.gvg) &&
				    (sd->status.party_id <= 0 || dstsd->status.party_id <= 0 ||
				    sd->status.party_id != dstsd->status.party_id)))
				{
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					break;
				}
				clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,skilllv,1);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,dstsd->bl.id,0,0,skill_get_time(skillid,skilllv),0 );
				dstsd->shadowform_id = sd->bl.id;
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SC_BODYPAINT:	/* �{�f�B�y�C���e�B���O */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				skill_detect(bl);		// �f�B�e�B�N�g����
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300+200*skilllv,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
				if(atn_rand() % 10000 < 500 * skilllv)
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SC_ENERVATION:		/* �}�X�J���[�h�F�G�i�x�[�V���� */
	case SC_GROOMY:			/* �}�X�J���[�h�F�O���[�~�[ */
	case SC_IGNORANCE:		/* �}�X�J���[�h�F�C�O�m�A�����X */
	case SC_LAZINESS:		/* �}�X�J���[�h�F���C�W�l�X */
	case SC_UNLUCKY:		/* �}�X�J���[�h�F�A�����b�L�[ */
	case SC_WEAKNESS:		/* �}�X�J���[�h�F�E�B�[�N�l�X */
		{
			int mask_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			mask_fix = (status_get_dex(src) + status_get_lv(src)) - (status_get_agi(bl) - status_get_lv(bl));
			if(mask_fix < 0)
				mask_fix = 0;

			if(atn_rand()%100 >= 5 + 2 * skilllv + mask_fix / 5) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			// �X�L�����Ƃ̌ʏ���
			switch(skillid) {
			case SC_ENERVATION:	/* �}�X�J���[�h�F�G�i�x�[�V���� */
				if(dstsd)
					pc_delspiritball(dstsd,dstsd->spiritball.num,0);	// �C�e���폜
				break;
			case SC_GROOMY:		/* �}�X�J���[�h�F�O���[�~�[ */
				if(dstsd) {
					pc_setoption(dstsd,(dstsd->sc.option & ~(OPTION_CARTMASK | OPTION_FALCON |
						OPTION_PECO | OPTION_DRAGONMASK | OPTION_WUG | OPTION_WUGRIDER)));	// �J�[�g�Ȃǂ̕t���i���폜
					if(dstsd->pd) pet_return_egg(dstsd);
					if(dstsd->hd) homun_return_embryo(dstsd);
					status_change_end(bl,SC_ALL_RIDING,-1);
					status_change_end(bl,SC_ON_PUSH_CART,-1);
				}
				break;
			case SC_IGNORANCE:		/* �}�X�J���[�h�F�C�O�m�A�����X */
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
			case SC_WEAKNESS:		/* �}�X�J���[�h�F�E�B�[�N�l�X */
				if(dstsd) {
					int i;

					for(i=0; i<MAX_INVENTORY; i++) {
						if(dstsd->status.inventory[i].equip & LOC_RLARM) {
							pc_unequipitem(dstsd,i,0);	// ����Ə�������
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
	case SC_STRIPACCESSARY:		/* �X�g���b�v�A�N�Z�T���[ */
		{
			int strip_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			strip_fix = status_get_dex(src) - status_get_dex(bl);
			if(strip_fix < 0)
				strip_fix = 0;
			if(atn_rand()%100 >= 12 + 2 * skilllv + ((strip_fix)? strip_fix / 5: 0)) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
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
	case SC_FEINTBOMB:		/* �t�F�C���g�{�� */
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// �o�b�N�X�e�b�v
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
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case SC_ESCAPE:			/* �G�X�P�[�v */
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// �o�b�N�X�e�b�v
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
	case LG_TRAMPLE:		/* �g�����v�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_trample,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,src,skilllv);
		}
		break;
	case LG_SHIELDSPELL:		/* �V�[���h�X�y�� */
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
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// �͈͕����U��
						int ar = (val>80? 3: (val>40? 2: 1));
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_damage_id);
					}
					else if(rate < 75) {	// �����U������
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,1,val/10,0,val*2000,0);
					}
					else {					// �U���͑���
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,2,val,0,val*3000,0);
					}
					break;
				case 2:
					val = sd->inventory_data[idx]->mdef;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 30) {			// �͈͖��@�U��
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|2,
							skill_castend_damage_id);
					}
					else if(rate < 60) {	// ���ٍU��
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_nodamage_id);
					}
					else {					// �}�O�j�t�B�J�[�g
						status_change_start(bl,SC_SHIELDSPELL_MDEF,skilllv,0,0,0,val*30000,0);
					}
					break;
				case 3:
					val = sd->status.inventory[idx].refine;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// HP��
						int heal = sd->status.max_hp * (1 + sd->status.base_level / 10 + val) / 100;
						clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
						pc_heal(sd,heal,0,0,0);
					}
					else if(rate < 75) {	// �Z�j��
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,1,val*10,0,val*30000,0);
					}
					else {					// DEF����
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,2,val*10*sd->status.base_level/100,0,val*20000,0);
					}
					break;
				}
			}
		}
		break;
	case LG_BANDING:			/* �o���f�B���O */
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
	case LG_PIETY:		/* �p�C�G�e�B */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LG_INSPIRATION:		/* �C���X�s���[�V���� */
		if(sd) {
			atn_bignumber loss_exp = pc_nextbaseexp(sd) / 1000;
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
	case SR_CURSEDCIRCLE:		/* �����w */
	case NPC_SR_CURSEDCIRCLE:		/* M�����w */
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
			int ar = skill_get_area(skillid,skilllv);
			if(skillid==SR_CURSEDCIRCLE)
				status_change_start(bl,SC_CURSEDCIRCLE_USER,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_RAISINGDRAGON:		/* �������V */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd) {
			if(pc_checkskill(sd,MO_EXPLOSIONSPIRITS) > 0)		// �����g���̏K�����x���Ŕ���
				status_change_start(bl,SC_EXPLOSIONSPIRITS,pc_checkskill(sd,MO_EXPLOSIONSPIRITS),0,0,0,skill_get_time(skillid,skilllv),0);
			pc_addspiritball(sd,skill_get_time2(skillid,skilllv),MAX_SPIRITBALL);
		}
		else
			status_change_start(bl,SC_EXPLOSIONSPIRITS,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SR_ASSIMILATEPOWER:	/* �z�C�� */
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
			int ar = skill_get_area(skillid,skilllv);
			/* �X�L���G�t�F�N�g�\�� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_POWERVELOCITY:		/* �S�C���� */
		if(sd && dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),sd->spiritball.num);
			pc_delspiritball(sd,sd->spiritball.num,0);
		}
		break;
	case SR_GENTLETOUCH_CURE:	/* �_�� -��- */
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
	case SR_GENTLETOUCH_CHANGE:		/* �_�� -��- */
		{
			int val1 = (status_get_str(src) / 2 + status_get_dex(src) / 4) * skilllv / 5;
			int val2 = (200 / (status_get_int(src)>1? status_get_int(src): 1) ) * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val1,val2>0? val2: 0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_GENTLETOUCH_REVITALIZE:	/* �_�� -��- */
		{
			int val = status_get_vit(src) / 2 * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_FLASHCOMBO:		/* �M���A�� */
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
					combo_id[i],(sd ? pc_checkskill(sd,combo_id[i]) : combo_lv[i]),BF_WEAPON,flag|1);
			}
		}
		break;
	case WA_SWING_DANCE:		/* �X�C���O�_���X */
	case WA_SYMPHONY_OF_LOVE:	/* ���l�����ׂ̈̃V���t�H�j�[ */
	case WA_MOONLIT_SERENADE:	/* ��������̃Z���i�[�f */
	case MI_RUSH_WINDMILL:		/* ���ԂɌ������ēˌ� */
	case MI_ECHOSONG:			/* �G�R�[�̉� */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* �ʂ̏��� */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? sd->status.job_level: 0),((sd)? pc_checkskill(sd,WM_LESSON): 0),0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MI_HARMONIZE:			/* �n�[���i�C�Y */
		{
			int param = 5 + skilllv * 5;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
			if(src != bl)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case WM_VOICEOFSIREN:	/* �Z�C���[���̐� */
		if(flag&1) {
			if(atn_rand() % 10000 < 2000 + 1000 * skilllv) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_DEADHILLHERE:		/* �����̋��� */
		if(dstsd) {
			if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVP�ŕ����s�\���
				break;
			if(!unit_isdead(&dstsd->bl))			// ���S����
				break;
			if(atn_rand() % 10000 >= 9000 + 200 * skilllv)
				break;
			if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// �w���p���[��Ԃ͑h���s��
				break;
			if(dstsd->special_state.no_magic_damage)
				break;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd->special_state.restart_full_recover) {	// �I�V���X�J�[�h
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
	case WM_LULLABY_DEEPSLEEP:	/* ���炬�̎q��S */
		if(flag&1) {
			if(bl->id != skill_area_temp[0]) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DEEP_SLEEP,400 * skilllv,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = src->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_SIRCLEOFNATURE:		/* �z���鎩�R�̉� */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_RANDOMIZESPELL:		/* �s�m��v�f�̌��� */
		if(sd) {
			int rand_skillid = skill_searchrandomid(2);
			int rand_skilllv = skill_get_max(rand_skillid);

			if(rand_skilllv > skilllv + 5)
				rand_skilllv = skilllv + 5;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sd->skill_item.id      = rand_skillid;
			sd->skill_item.lv      = rand_skilllv;
			sd->skill_item.flag    = 1;		// �g�p�������肷��
			clif_item_skill(sd, rand_skillid, rand_skilllv, "");
		}
		break;
	case WM_SONG_OF_MANA:		/* �}�i�̉� */
	case WM_DANCE_WITH_WUG:		/* �_���X�E�B�Y�E�H�[�O */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
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
	case WM_SATURDAY_NIGHT_FEVER:		/* �t���C�f�[�i�C�g�t�B�[�o�[ */
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
			int ar = skill_get_area(skillid,skilllv);
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
	case WM_LERADS_DEW:			/* ���[���Y�̖� */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_BEYOND_OF_WARCRY:	/* �r�����h�I�u�E�H�[�N���C */
	case WM_MELODYOFSINK:		/* �����f�B�[�I�u�V���N */
		if(flag&1) {
			int rate = 1500 + 500 * skilllv;
			if(skill_area_temp[0] >= 3 && skill_area_temp[0] <= 7)
				rate += 5 * (skill_area_temp[0]-2);
			if(atn_rand() % 10000 < rate) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
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
	case WM_UNLIMITED_HUMMING_VOICE:	/* �G���h���X�n�~���O�{�C�X */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_FRIGG_SONG:		/* �t���b�O�̉� */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// �ʏ�}�b�v�͑S�v���C���[�A�ΐlMAP�ł�PARTY�̂�
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
	case SO_FIREWALK:		/* �t�@�C�A�[�E�H�[�N */
	case SO_ELECTRICWALK:	/* �G���N�g���b�N�E�H�[�N */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SO_SPELLFIST:		/* �X�y���t�B�X�g */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_skillcastcancel(src,1);
		if(sd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,sd->skill_used.id,sd->skill_used.lv,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_STRIKING:		/* �X�g���C�L���O */
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
	case SO_ARRULLO:	/* �A���[�W�� */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SO_EL_CONTROL:		/* �G�������^���R���g���[�� */
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
	case SO_SUMMON_AGNI:	/* �T�����A�O�j */
	case SO_SUMMON_AQUA:	/* �T�����A�N�A */
	case SO_SUMMON_VENTUS:	/* �T�����x���g�X */
	case SO_SUMMON_TERA:	/* �T�����e�� */
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

			// ���쏢�����̏ꍇ�͈�U��������
			if(sd->sc.data[type].timer != -1)
				status_change_end(src,type,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_ARDOR].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_ARDOR,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_DILUVIO].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_DILUVIO,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_PROCELLA].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_PROCELLA,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_TERREMOTUS].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_TERREMOTUS,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_SERPENS].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_SERPENS,-1);

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_create_data(sd,elem_id,skill_get_time(skillid,skilllv)/1000);
			status_change_start(src,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_EL_ACTION:	/* �G�������^���A�N�V���� */
		if(sd && sd->eld) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_skilluse(sd->eld, bl, ELMODE_OFFENSIVE);
		}
		break;
	case SO_EL_ANALYSIS:	/* �G�������^���A�i���C�V�X */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,skilllv);
		}
		break;
	case SO_EL_CURE:	/* �G�������^���L���A�[ */
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
	case SO_ELEMENTAL_SHIELD:	/* �G�������^���V�[���h */
		if(flag&1 || sd == NULL) {
			if(unit_isdead(bl))			// ���S����
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
	case GN_BLOOD_SUCKER:		/* �u���b�h�T�b�J�[ */
	case GN_SPORE_EXPLOSION:	/* �X�|�A�G�N�X�v���[�W���� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case LG_KINGS_GRACE:	/* �L���O�X�O���C�X */
	case GN_WALLOFTHORN:	/* �\�[���E�H�[�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case GN_MANDRAGORA:		/* �n�E�����O�I�u�}���h���S�� */
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
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_SLINGITEM:		/* �X�����O�A�C�e�� */
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

				// �������ɂ���Č��ʌ���
				switch(nameid) {
				case 13260:		// �����S���e
				case 13261:		// �R�R�i�b�c���e
				case 13262:		// ���������e
				case 13264:		// �o�i�i���e
				case 13265:		// ������
				case 13266:		// �d���č�����
				case 13267:		// �ƂĂ��d����
					if(battle_check_target(src,bl,BCT_ENEMY) > 0)
						battle_skill_attack(BF_WEAPON,src,src,bl,GN_SLINGITEM_RANGEMELEEATK,nameid - 13260,tick,flag|(0x0f<<20));
					break;
				case 13263:		// �p�C�i�b�v�����e
					if(battle_check_target(src,bl,BCT_ENEMY) > 0) {
						int ar = skill_get_area(GN_SLINGITEM_RANGEMELEEATK,skilllv);
						map_foreachinarea(skill_area_sub,
							bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
							src,GN_SLINGITEM_RANGEMELEEATK,3,tick,flag|BCT_ENEMY|(0x0f<<20),
							skill_castend_damage_id);
					}
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
	case GN_CHANGEMATERIAL:	/* �`�F���W�}�e���A�� */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,0);
		}
		break;
	case GN_MIX_COOKING:	/* �~�b�N�X�N�b�L���O */
		if(sd) {
			clif_making_list(sd,PRD_MIX_COOKING,skillid,skilllv,4);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_MAKEBOMB:		/* ���e���� */
		if(sd) {
			clif_making_list(sd,PRD_MAKEBOMB,skillid,skilllv,5);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_S_PHARMACY:		/* �X�y�V�����t�@�[�}�V�[ */
		if(sd) {
			clif_making_list(sd,PRD_S_PHARMACY,skillid,skilllv,6);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case KO_ZANZOU:		/* ���p -�e����- */
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
				// �o�b�N�X�e�b�v
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
	case KO_KYOUGAKU:		/* ���p -����- */
		{
			int rate;
			// �v���C���[�ȊO�܂��͖����ɂ͎g�p�s��
			if(bl->type != BL_PC || battle_check_target(src,bl,BCT_PARTY) > 0) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
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
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_JYUSATSU:		/* ���p -��E- */
		{
			int rate;
			// �v���C���[�ȊO�ɂ͎g�p�s��
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
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
						// �R�[�}
						if(dstsd) {
							dstsd->status.hp = 1;
							clif_updatestatus(dstsd,SP_HP);
						}
					}
				}
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_KAHU_ENTEN:	/* �Ε��F���V */
	case KO_HYOUHU_HUBUKI:	/* �X���F���� */
	case KO_KAZEHU_SEIRAN:	/* �����F�� */
	case KO_DOHU_KOUKAI:	/* �y���F���� */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// ���������������Ă���ꍇ�͍폜
			if(sd->elementball.num) {
				if(sd->elementball.ele != skill_get_pl(skillid)) {
					pc_delelementball(sd,sd->elementball.num,0);
				}
			}
			pc_addelementball(sd,skill_get_time(skillid,skilllv),MAX_ELEMENTBALL,skill_get_pl(skillid));
		}
		break;
	case KO_GENWAKU:		/* ���p -���f- */
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
				if(!(status_get_mode(bl)&MD_BOSS))	// �{�X�����ȊO
					unit_movepos(bl,x,y,0);
				if(atn_rand() % 10000 < 7500) {
					t_bl = bl;
				}
				status_change_pretimer(t_bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_IZAYOI:		/* �\�Z�� */
	case KG_KYOMU:		/* ���p -�����̉e- */
	case KG_KAGEMUSYA:	/* ���p -���g- */
	case OB_ZANGETSU:	/* ���p -�c��- */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case KG_KAGEHUMI:	/* ���p -�e����- */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc) {
				if(sc->data[SC_HIDING].timer != -1 || sc->data[SC_CLOAKING].timer != -1 || sc->data[SC_CLOAKINGEXCEED].timer != -1 ||
				   sc->data[SC__SHADOWFORM].timer != -1 || sc->data[SC_CAMOUFLAGE].timer != -1 || sc->data[SC_MARIONETTE].timer != -1 ||
				   sc->data[SC_MARIONETTE2].timer != -1 || sc->data[SC_HARMONIZE].timer != -1 || sc->data[SC_NEWMOON].timer != -1)
				{
					status_change_end(bl, SC_HIDING, -1);
					status_change_end(bl, SC_CLOAKING, -1);
					status_change_end(bl, SC_CLOAKINGEXCEED, -1);
					status_change_end(bl, SC_NEWMOON, -1);
					status_change_end(bl, SC__SHADOWFORM, -1);
					status_change_end(bl, SC_CAMOUFLAGE, -1);
					status_change_end(bl, SC_MARIONETTE, -1);
					status_change_end(bl, SC_MARIONETTE2, -1);
					status_change_end(bl, SC_HARMONIZE, -1);
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case OB_OBOROGENSOU:	/* ���p -�O���z- */
		{
			int hp = 0, hp_val, hp_max, hp_per = 0, hp_lv;
			int sp = 0, sp_val, sp_max, sp_per = 0, sp_lv;

			// �v���C���[�ȊO�ɂ͖���
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u

			// HP�̊����Z�o
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

			// SP�̊����Z�o
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

			unit_heal(bl,hp,sp,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case OB_AKAITSUKI:	/* ���p -�g��- */
		// �ΐlMAP�ȊO�ł̓v���C���[�Ɏg�p�s�܂���BOSS�A�����ɂ͎g�p�s��
		if((!map[src->m].flag.pvp && !map[src->m].flag.gvg && !map[src->m].flag.pk && bl->type == BL_PC) || status_get_mode(bl)&MD_BOSS || battle_check_target(src,bl,BCT_PARTY) > 0) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RL_RICHS_COIN:		/* ���b�`�Y�R�C�� */
		if(sd) {
			int i;
			if(sd->coin.num >= MAX_COIN) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i=0;i<MAX_COIN && sd->coin.num<MAX_COIN;i++)
				pc_addcoin(sd,skill_get_time(skillid,skilllv),MAX_COIN);
		}
		break;
	case RL_C_MARKER:		/* �N�����]���}�[�J�[ */
		if(sd) {
			int i;

			sc = status_get_sc(bl);
			if(sc && sc->data[SC_C_MARKER].timer != -1 && sc->data[SC_C_MARKER].val2 != src->id)
				status_change_end(bl, SC_C_MARKER, -1);

			for(i=0;i<3;i++) {
				if(sd->c_marker[i] == bl->id || sd->c_marker[i] == 0)
					break;
			}
			if(i == 3) {
				clif_skill_fail(sd,skillid,SKILLFAIL_MORESKILL,0,0);
				break;
			}
			sd->c_marker[i] = bl->id;
			status_change_start(bl,SC_C_MARKER,skilllv,src->id,i,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		else {
			status_change_start(bl,SC_C_MARKER,skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case RL_FLICKER:		/* �t���b�J�[ */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_flicker,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,src,tick);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,RL_H_MINE,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RL_B_TRAP:			/* �o�C���h�g���b�v */
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case RL_HEAT_BARREL:	/* �q�[�g�o���� */
	case RL_P_ALTER:	/* �v���`�i���A���^�[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,(sd)? sd->coin.num: 10,skill_get_time(skillid,skilllv),0);
		if(sd)
			pc_delcoin(sd,MAX_COIN,0);
		break;
	case SJ_DOCUMENT:	/* ���z�ƌ��Ɛ��̋L�^ */
		{
			int i;
			if( skilllv & 0x01 ){
				for (i = 0; i < 3; i++ ) {
					sd->feel_index[i] = -1;
					memset(&sd->status.feel_map[i], 0, sizeof(sd->status.feel_map[0]));
				}
			}
			if( skilllv & 0x02 ){
				const char *reg[] = { "PC_HATE_MOB_SUN", "PC_HATE_MOB_MOON", "PC_HATE_MOB_STAR" };
				for (i = 0; i < 3; i++ ) {
					sd->hate_mob[i] = -1;
					pc_setglobalreg(sd,reg[i],0);
				}
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SJ_GRAVITYCONTROL:	/* �d�͒��� */
		{
			int type = GetSkillStatusChangeTable(skillid);
			sc = status_get_sc(bl);
			if(sc && sc->data[type].timer != -1 ){
				sc->data[type].val2 = 0;
				status_change_end(bl, type, -1);
			}
			else{
				int fall_damage = status_get_baseatk(src) + status_get_atk(src) - status_get_def2(bl);

				if (bl->type == BL_PC)
					fall_damage += dstsd->weight / 10 - status_get_def(bl);
				else // Monster's don't have weight. Put something in its place.
					fall_damage += 50 * status_get_lv(src) - status_get_def(bl);

				fall_damage = max(1, fall_damage);
				status_change_start(bl,type,skilllv,fall_damage,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SP_SOULGOLEM:			/* �S�[�����̍� */
	case SP_SOULSHADOW:			/* �e�̍� */
	case SP_SOULFALCON:			/* ��̍� */
	case SP_SOULFAIRY:			/* �d���̍� */
	case SP_SOULREAPER:			/* ���̎��n */
	case SP_SOULCOLLECT:		/* ���̒~�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SOULDIVISION:		/* ���̕��� */
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SOULCURSE:			/* ����߈� */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,(status_get_mode(bl)&MD_BOSS)? 20: 100,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SP_SOULUNITY:	/* ���̘A�� */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SP_SOULREVOLVE:		/* ���̏z�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
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
		unit_heal(bl,0,460,0,1);
		break;
	case SP_KAUTE:	/* �J�E�g */
		if(sd) {
			int heal_sp = 0;
			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			heal_sp = (int)((atn_bignumber)status_get_max_sp(bl) * (13+skilllv*3) / 100);
			unit_heal(bl,0,heal_sp,0,1);
		}
		break;
	case SU_HIDE:	/* ������� */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* �������� */
				status_change_end(bl, type, -1);
			} else {
				/* �t������ */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			break;
		}
	case SU_STOOP:	/* �������܂� */
	case SU_CHATTERING:	/* �`���^�����O */
	case SU_ARCLOUSEDASH:	/* �A�N���E�X�_�b�V�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_TUNAPARTY:	/* �}�O���V�[���h */
		{
			int rate;

			rate = (int)(skilllv * 10 * (atn_bignumber)status_get_max_hp(bl) / 100);
			if(sd && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// �C�̍�
				rate *= 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,rate,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_CN_POWDERING:	/* �C�k�n�b�J�V�����[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case SU_SV_ROOTTWIST:	/* �}�^�^�r�̍����� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_HISS:	/* �x�� */
		if(flag&1 || sd == NULL) {
			int val2 = (skilllv >= 5)? 500: ((skilllv == 4)? 250: skilllv * 50);	// ���S��𑝉�
			int val3 = (skilllv >= 4)? 60: ((skilllv == 3)? 40: 25);	// �ړ����x����

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),15,val2,val3,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_POWEROFFLOCK:	/* �Q��̗� */
		if(flag&1) {
			int rate = 1000 + 500 * skilllv + status_get_dex(src) * 10 + status_get_luk(src) * 10;	// �b��m��
			if(atn_rand() % 10000 < rate)
				status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_GROOMING:	/* �O���[�~���O */
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
	case SU_PURRING:	/* �̂ǂ�炷 */
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
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_MEOWMEOW:	/* �~���E�~���E */
		if(flag&1) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_FRESHSHRIMP:	/* �V�N�ȃG�r */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv)),skill_get_time(skillid,skilllv),0);
		break;
	case SU_BUNCHOFSHRIMP:	/* �G�r�O�� */
		if(flag&1) {
			int heal;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));

			if(sc) {
				if(sc->data[SC_CRITICALWOUND].timer != -1)
					heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
				if(sc->data[SC_DEATHHURT].timer != -1)	/* �f�X�n�[�g */
					heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
				if(sc->data[SC_BERSERK].timer != -1) /* �o�[�T�[�N���̓q�[���O */
					heal = 0;
			}
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,((sd)? pc_checkskill(sd, SU_SPIRITOFSEA): 0)*30000 + skill_get_time(skillid,skilllv),0);
		} else {
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_TUNABELLY:	/* ��g�� */
		{
			int heal = (int)((5 + skilllv * 5 + (skilllv>=5? 20: (skilllv==4? 10: 0))) * (atn_bignumber)status_get_max_hp(bl) / 100);

			if(sc) {
				if(sc->data[SC_CRITICALWOUND].timer != -1)
					heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
				if(sc->data[SC_DEATHHURT].timer != -1)	/* �f�X�n�[�g */
					heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
				if(sc->data[SC_BERSERK].timer != -1) /* �o�[�T�[�N���̓q�[���O */
					heal = 0;
			}
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;
	case SU_SHRIMPARTY:	/* �G�r�p�[�e�B�[ */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// �L�����b�g�r�[�g
		if(sd) {
			int nameid, amount, idx = 0;

			nameid = 515;	// �j���W��
			amount = 1;

			idx = pc_search_inventory(sd,nameid);

			if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {	// �j���W�������Ă������
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
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		break;
	case ECL_PEONYMAMY:
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_FROSTMISTY, -1);
		status_change_end(bl, SC_DIAMONDDUST, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		break;
	case ECL_SADAGUI:
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		status_change_end(bl, SC_FEAR, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		break;
	case ECL_SEQUOIADUST:
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_DECREASEAGI, -1);
		status_change_end(bl, SC_REVERSEORCISH, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
		break;
	case EVT_FULL_THROTTLE:	/* �t���X���b�g�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(src,status_get_max_hp(src),0,0,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NV_HELPANGEL:	/* �V�g���܏����� */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case IG_GUARDIAN_SHIELD:	/* �K�[�f�B�A���V�[���h */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			int val = (int)((atn_bignumber)(status_get_max_hp(src)*5/100 + status_get_sta(src)*status_get_lv(src)*2) * (50+50*skilllv)/100);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case IG_ULTIMATE_SACRIFICE:		/* �A���e�B���b�g�T�N���t�@�C�X */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			skill_area_temp[1] = src->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* �p�[�e�B�S�̂ւ̏��� */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
			unit_heal(src,-status_get_hp(src)+1,0,0,0);
		}
		break;
	case CD_REPARATIO:		/* ���p���e�B�I */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_misceffect_value(bl, 657, status_get_max_hp(bl));
		unit_heal(src,status_get_max_hp(bl),0,0,0);
		break;
	case CD_MEDIALE_VOTUM:		/* ���f�B�A���{�g�D�� */
		if(flag&0x20) {
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 5 / 100);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
		} else if(flag&0x10) {
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-(flag&0x0f),bl->y-(flag&0x0f),bl->x+(flag&0x0f),bl->y+(flag&0x0f),
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|0x20,
				skill_castend_nodamage_id);
		} else {
			int ar = skill_get_area(skillid,skilllv) + status_get_hplus(src)/100;
			if(ar > 10) ar = 10;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,ar,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case CD_COMPETENTIA:	/* �R���y�e���e�B�A */
		if(flag&1) {
			int hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(bl) * ((skilllv < 4)? (65 + skilllv * 5): (75 + skilllv * 5)) / 100);
			int sp = BIGNUM2INT((atn_bignumber)status_get_max_sp(bl) * ((skilllv < 5)? (15 + skilllv * 15): 100) / 100);
			unit_heal(bl,hp,sp,0,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case CD_DILECTIO_HEAL:			/* �f�B���N�e�B�I�q�[�� */
		if(flag&1) {
			int heallv = (sd)? pc_checkskill(sd, AL_HEAL): skilllv;
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, heallv));
			heal = BIGNUM2INT((atn_bignumber)heal * (500 + skilllv * 25) / 100 + status_get_hplus(src) * skilllv);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MT_M_MACHINE:	/* ���u���� */
		if(sd) {
			clif_making_list(sd,PRD_M_MACHINE,skillid,skilllv,7);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ABC_STRIP_SHADOW:		/* �X�g���b�v�V���h�E */
		{
			int strip_fix;

			strip_fix = status_get_crt(src) - status_get_crt(bl);
			if(strip_fix < 0)
				strip_fix = 0;
			if(atn_rand()%100 >= 5 * skilllv + ((strip_fix)? strip_fix / 4: 0)) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_SHADOW_ALL)) {
						pc_unequipitem(dstsd,i,0);
					}
				}
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ABC_ABYSS_SLAYER:		/* �A�r�X�X���C���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(src,status_get_max_hp(bl),status_get_max_sp(bl),0,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WH_HAWK_M:		/* �z�[�N�}�X�^���[ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd)) {
				pc_setoption(sd,sd->sc.option & ~OPTION_FALCON);
			} else {
				pc_setoption(sd,sd->sc.option | OPTION_FALCON);
			}
		}
		break;
	case WH_CALAMITYGALE:		/* �J���~�e�B�Q�C�� */
		{
			int skill;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(sd && ((skill = pc_checkskill(sd,RA_UNLIMIT)) > 0)) {
				status_change_start(bl,SC_UNLIMIT,skill,0,0,0,skill_get_time2(skillid,skill),0);
			}
		}
		break;
	case BO_BIONIC_PHARMACY:	/* �o�C�I�j�b�N�t�@�[�}�V�[ */
		if(sd) {
			clif_making_list(sd,PRD_BIONIC_PHARMACY,skillid,skilllv,8);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case BO_THE_WHOLE_PROTECTION:	/* �z�[���t���P�~�J���`���[�W */
		if(flag&1) {
			status_change_start(bl,SC_CP_HELM,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_SHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_ARMOR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_WEAPON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case EL_CIRCLE_OF_FIRE:	/* �T�[�N���I�u�t�@�C�A */
	case EL_FIRE_CLOAK:		/* �t�@�C�A�[�N���[�N */
	case EL_WATER_SCREEN:	/* �E�H�[�^�[�X�N���[�� */
	case EL_WATER_DROP:		/* �E�H�[�^�[�h���b�v */
	case EL_WIND_STEP:		/* �E�B���h�X�e�b�v */
	case EL_WIND_CURTAIN:	/* �E�B���h�J�[�e�� */
	case EL_SOLID_SKIN:		/* �\���b�h�X�L�� */
	case EL_STONE_SHIELD:	/* �X�g�[���V�[���h */
	case EL_PYROTECHNIC:	/* �p�C���e�N�j�b�N */
	case EL_HEATER:			/* �q�[�^�[ */
	case EL_TROPIC:			/* �g���s�b�N */
	case EL_AQUAPLAY:		/* �A�N�A�v���C */
	case EL_COOLER:			/* �N�[���[ */
	case EL_CHILLY_AIR:		/* �N�[���G�A�[ */
	case EL_GUST:			/* �K�X�g */
	case EL_BLAST:			/* �u���X�g */
	case EL_WILD_STORM:		/* ���C���h�X�g�[�� */
	case EL_PETROLOGY:		/* �y�g���W�[ */
	case EL_CURSED_SOIL:	/* �J�[�X�h�\�C�� */
	case EL_UPHEAVAL:		/* �A�b�v�w�C�o�� */
		if(eld && eld->msd) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_FIRE_MANTLE:		/* �t�@�C�A�[�}���g�� */
	case EL_WATER_BARRIER:		/* �E�H�[�^�[�o���A�[ */
	case EL_ZEPHYR:				/* �[�t�@�[ */
	case EL_POWER_OF_GAIA:		/* �p���[�I�u�K�C�A */
		if(eld && eld->msd) {
			clif_skill_poseffect(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,tick);
			skill_unitsetting(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,0);
		}
		break;
	case EM_EL_FLAMETECHNIC:		/* �t���C���e�N�j�b�N */
	case EM_EL_FLAMEARMOR:			/* �t���C���A�[�}�[ */
	case EM_EL_COLD_FORCE:			/* �R�[���h�t�H�[�X */
	case EM_EL_CRYSTAL_ARMOR:		/* �N���X�^���A�[�}�[ */
	case EM_EL_GRACE_BREEZE:		/* �O���C�X�u���[�Y */
	case EM_EL_EYES_OF_STORM:		/* �A�C�Y�I�u�X�g�[�� */
	case EM_EL_EARTH_CARE:			/* �A�[�X�P�A */
	case EM_EL_STRONG_PROTECTION:	/* �X�g�����O�v���e�N�V���� */
	case EM_EL_DEEP_POISONING:		/* �f�B�[�v�|�C�Y�j���O */
	case EM_EL_POISON_SHIELD:		/* �|�C�Y���V�[���h */
		if(eld && eld->msd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(src,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
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
	case NPC_CHEAL:			/* M�n�C�l�X�q�[�� */
		if(flag&1) {
			int heal = (status_get_lv(src) + status_get_int(src)) / 5 * 30;

			clif_skill_nodamage(src,bl,AB_CHEAL,heal,1);
			battle_heal(src,bl,heal,0,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_NOENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR �o�g���E�H���A�[ */
	case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR �f���A���L���m�� */
	case MT_SUMMON_ABR_MOTHER_NET:		/* ABR �}�U�[�l�b�g */
	case MT_SUMMON_ABR_INFINITY:		/* ABR �C���t�B�j�e�B */
		if(sd) {
			const int mob_id[4] = { MOBID_ABR_BATTLE_WARIOR, MOBID_ABR_DUAL_CANNON, MOBID_ABR_MOTHER_NET, MOBID_ABR_INFINITY };
			int id;
			struct mob_data *tmpmd = NULL;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			id = mob_once_spawn_area(sd, sd->bl.m, sd->bl.x-1, sd->bl.y-1, sd->bl.x+1, sd->bl.y+1, "--ja--", mob_id[ skillid-MT_SUMMON_ABR_BATTLE_WARIOR ], 1, "");
			if((tmpmd = map_id2md(id)) != NULL) {
				const int add_abr_max_hp[11] = { 0, 25000, 50000, 75000, 112500, 150000, 187500, 225000, 275000, 375000, 500000 };
				const int add_abr_atk[11] = { 0, 100, 300, 500, 800, 1100, 1400, 1700, 2000, 2500, 3000 };
				int n = pc_checkskill(sd,MT_ABR_M);
				if(n > 10)
					n = 10;
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->speed        = sd->speed;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.norandomwalk = 1;
				tmpmd->state.special_mob_ai = MOB_AI_ABR;
				// ABR�̃X�e�[�^�X�ύX
				switch(skillid){
				case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR �o�g���E�H���A�[ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 12 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->base_atk) * 12 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->plus_atk) * 12 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 8 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 3 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR �f���A���L���m�� */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 9 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 12 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 12 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 6 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 4 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_MOTHER_NET:		/* ABR �}�U�[�l�b�g */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 8 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 8 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 8 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 5 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 8 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_INFINITY:		/* ABR �C���t�B�j�e�B */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 15 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 15 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 15 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 9 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 9 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				}
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case ABR_NET_REPAIR:	/* �l�b�g���y�A */
	case ABR_NET_SUPPORT:	/* �l�b�g�T�|�[�g */
		if(flag&1) {
			int hp = (skillid == ABR_NET_REPAIR)? BIGNUM2INT((atn_bignumber)status_get_max_hp(bl) * 10 / 100): 0;
			int sp = (skillid == ABR_NET_SUPPORT)? BIGNUM2INT((atn_bignumber)status_get_max_sp(bl) * 5 / 100): 0;
			unit_heal(bl,hp,sp,0,1);
		} else {
			// ��̏����擾
			if(md && md->master_id) {
				struct block_list *master = map_id2bl(md->master_id);
				if(master && master->type == BL_PC) {
					int ar = skill_get_area(skillid,skilllv);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					map_foreachinarea(skill_area_sub,src->m,
						src->x-ar,src->y-ar,
						src->x+ar,src->y+ar,
						BL_CHAR,master,skillid,skilllv,tick,flag|BCT_PARTY|1,
						skill_castend_nodamage_id);
				}
			}
		}
		break;
	case BO_WOODENWARRIOR:		/* �N���G�C�g�E�h�D���E�H���A�[ */
	case BO_WOODEN_FAIRY:		/* �N���G�C�g�E�h�D���t�F�A���[ */
	case BO_CREEPER:			/* �N���G�C�g�N���[�p�[ */
	case BO_HELLTREE:			/* �N���G�C�g�w���c���[ */
		if(sd) {
			const int mob_id[5] = { MOBID_SUMMON_WOODENWARRIOR, MOBID_SUMMON_WOODEN_FAIRY, MOBID_SUMMON_CREEPER, 0, MOBID_SUMMON_HELLTREE };
			int id;
			struct mob_data *tmpmd = NULL;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			id = mob_once_spawn_area(sd, sd->bl.m, sd->bl.x-1, sd->bl.y-1, sd->bl.x+1, sd->bl.y+1, "--ja--", mob_id[ skillid-BO_WOODENWARRIOR ], 1, "");
			if((tmpmd = map_id2md(id)) != NULL) {
				const int add_bionic_max_hp[11] = { 0, 25000, 50000, 75000, 112500, 150000, 187500, 225000, 275000, 375000, 500000 };
				const int add_bionic_atk[11] = { 0, 100, 300, 500, 800, 1100, 1400, 1700, 2000, 2500, 3000 };
				const int add_bionic_matk[11] = { 0, 50, 150, 250, 400, 550, 700, 850, 1000, 1500, 2000 };
				int n = pc_checkskill(sd,BO_BIONICS_M);
				if(n > 10)
					n = 10;
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->speed        = sd->speed;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.norandomwalk = 1;
				tmpmd->state.special_mob_ai = MOB_AI_BIONIC;
				// �o�C�I�j�b�N�����X�^�[�̃X�e�[�^�X�ύX
				switch(skillid){
				case BO_WOODENWARRIOR:		/* �N���G�C�g�E�h�D���E�H���A�[ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 12 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->base_atk) * 12 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->plus_atk) * 12 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 12 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 8 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 3 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_WOODEN_FAIRY:		/* �N���G�C�g�E�h�D���t�F�A���[ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 9 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 12 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 12 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 12 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 6 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 4 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_CREEPER:			/* �N���G�C�g�N���[�p�[ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 8 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 8 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 8 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 8 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 5 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 8 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_HELLTREE:			/* �N���G�C�g�w���c���[ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 15 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 15 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 15 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 15 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 9 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 9 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				}
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TR_RETROSPECTION:		/* ��z */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			unit_skilluse_id(&sd->bl,src->id,sd->skill_4thdance.id,sd->skill_4thdance.lv);
		break;
	case TR_SOUNDBLEND:			/* �T�E���h�u�����h */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case TR_GEF_NOCTURN:		/* �Q�t�F�j�A�m�N�^�[�� */
	case TR_AIN_RHAPSODY:		/* �z���̃��v�\�f�B */
		if(flag&1) {
			if(!(status_get_mode(bl)&MD_BOSS)) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case TR_ROKI_CAPRICCIO:		/* ���L�̋C�܂��� */
	case TR_NIPELHEIM_REQUIEM:	/* ���҂����ւ̃��N�C�G�� */
		if(flag&1) {
			if(bl->type == BL_PC) {
				int rate = 10 * skilllv;
				if(skill_area_temp[0] > 1) {		// �p�[�g�i�[������ꍇ
					rate = rate * 15 / 10;
				}
				if(atn_rand()%100 < rate) {
					if(skillid == TR_ROKI_CAPRICCIO) {
						status_change_start(bl,SC_HANDICAPSTATE_MISFORTUNE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
						status_change_start(bl,SC_CONFUSION,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					} else {
						status_change_start(bl,SC_HANDICAPSTATE_DEPRESSION,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
						status_change_start(bl,SC_CURSE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					}
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case TR_MUSICAL_INTERLUDE:		/* �~���[�W�J���C���^�[���[�h */
	case TR_JAWAII_SERENADE:		/* �[�Ă��̃Z���i�[�f */
	case TR_PRON_MARCH:				/* �v�����e���}�[�` */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case EM_ACTIVITY_BURN:		/* �A�N�e�B�r�e�B�o�[�� */
		{
			const int damage_ap[5] = { 60, 80, 110, 150, 200 };
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			unit_heal(bl,0,0,-(damage_ap[(skilllv <= 5)? skilllv-1: 5]),0);
		}
		break;
	case EM_INCREASING_ACTIVITY:		/* �C���N���[�V���O�A�N�e�B�r�e�B */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(bl,0,0,50+20*skilllv,0);
		break;
	case EM_SUMMON_ELEMENTAL_ARDOR:			/* �T�����A���h�[�� */
	case EM_SUMMON_ELEMENTAL_DILUVIO:		/* �T�����f�B���r�I */
	case EM_SUMMON_ELEMENTAL_PROCELLA:		/* �T�����v���Z�� */
	case EM_SUMMON_ELEMENTAL_TERREMOTUS:	/* �T�����e�����g�D�X */
	case EM_SUMMON_ELEMENTAL_SERPENS:		/* �T�����T�[�y���X */
		if(sd) {
			int elem_id = 0;

			switch(skillid) {
				case EM_SUMMON_ELEMENTAL_ARDOR:      elem_id = ELEMID_EM_ARDOR;      break;
				case EM_SUMMON_ELEMENTAL_DILUVIO:    elem_id = ELEMID_EM_DILUVIO;    break;
				case EM_SUMMON_ELEMENTAL_PROCELLA:   elem_id = ELEMID_EM_PROCELLA;   break;
				case EM_SUMMON_ELEMENTAL_TERREMOTUS: elem_id = ELEMID_EM_TERREMOTUS; break;
				case EM_SUMMON_ELEMENTAL_SERPENS:    elem_id = ELEMID_EM_SERPENS;    break;
			}

			// ���쏢�����̏ꍇ�͈�U��������
			if(sd->sc.data[SC_SUMMON_ELEM].timer != -1)
				status_change_end(src,SC_SUMMON_ELEM,-1);

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_create_data(sd,elem_id,skill_get_time(skillid,skilllv)/1000);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EM_ELEMENTAL_VEIL:				/* �G�������^�����F�[�� */
		if(sd && sd->eld) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(&sd->eld->bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NW_GRENADE_FRAGMENT:		/* �O���l�[�h�t���O�����g */
	case SH_COLORS_OF_HYUN_ROK:		/* ���C���{�[�z�[�� */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(skilllv < 7) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+skilllv-1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			sc = status_get_sc(bl);
			if(sc) {
				int i;
				for(i = GetSkillStatusChangeTable(skillid); i < GetSkillStatusChangeTable(skillid)+6; i++) {
					if(sc->data[i].timer != -1) {
						status_change_end(bl,i,-1);
					}
				}
			}
		}
		break;
	case SOA_TALISMAN_OF_PROTECTION:	/* ��아 */
		{	// �t�^�Ɠ����Ƀq�[��
			int heal = skill_fix_heal(src, bl, AL_HEAL, skill_calc_heal(src, skilllv));
			heal += (1000 + skilllv * 500 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * skilllv * 50: 0)) * status_get_lv(src) / 100;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,heal,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SOA_SOUL_GATHERING:	/* �썰��g */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addsoulenergy(sd,600000,MAX_SOULENERGY);
		}
		break;
	case SOA_SOUL_OF_HEAVEN_AND_EARTH:	/* �V�n�_�� */
		if(flag&1) {
			unit_heal(bl,0,status_get_max_sp(bl),0,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_KI_SUL_WATER_SPRAYING:	/* �^�[�g���X�v�����N���[ */
		if(flag&1) {
			clif_misceffect_value(bl, 312, skill_area_temp[0]);
			clif_misceffect_value(bl, 657, skill_area_temp[0]);
			unit_heal(bl,skill_area_temp[0],0,0,0);
		} else {
			int heal = skill_fix_heal(src, bl, AL_HEAL, skill_calc_heal(src, skilllv));
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				heal += (4500 + skilllv * 1500 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 150: 0)) * status_get_lv(src) / 100;
				ar += 2;
			} else {
				heal += (3000 + skilllv * 1000 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 100: 0)) * status_get_lv(src) / 100;
			}
			skill_area_temp[0] = heal;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_MARINE_FESTIVAL_OF_KI_SUL:	/* �}�����t�F�X�e�B�o�� */
	case SH_SANDY_FESTIVAL_OF_KI_SUL:	/* �T���h�t�F�X�e�B�o�� */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				ar += 2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_KI_SUL_RAMPAGE:		/* �^�[�g�������y�[�W */
		if(flag&0x20) {
			if(src != bl) {
				int ap = 2;
				if(flag&0x0f) {
					ap *= 3;
				}
				unit_heal(bl,0,0,ap,1);
			}
		} else if(flag&0x10) {
			int ar = skill_get_area(skillid,skilllv);
			if(flag&0x0f) {
				ar += 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|0x20,
				skill_castend_nodamage_id);
		} else {
			int increases = 0;	// �����t���O
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				increases = 1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,increases,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SH_BLESSING_OF_MYSTICAL_CREATURES:		/* �ɂ��u���b�V���O */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(bl,0,0,200,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SS_AKUMUKESU:			/* �������� */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_NIGHTMARE].timer != -1 ) {
				status_change_end(bl,SC_NIGHTMARE,-1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
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
 * �X�L���g�p�i�r�������A�ꏊ�w��j
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

	if( src_ud->skilltimer != tid )	// �^�C�}ID�̊m�F
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

		// �ΎR�D �s������
		if(sc && sc->data[SC_VOLCANIC_ASH].timer != -1 && skill_get_misfire(src_ud->skillid) && atn_rand()%100 < 50)
			break;
		// �s�K �s������
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

		if(!src_sd || battle_config.check_skillpos_range) {	// ��������PC�Ŏ˒��`�F�b�N�����Ȃ炱�̏����͖������ăN���C�A���g�̏���M������
			if(range < path_distance(src->x,src->y,src_ud->skillx,src_ud->skilly)) {
				if(src_sd && battle_config.skill_out_range_consume)
					skill_check_condition(&src_sd->bl,1);	// �A�C�e������
				break;
			}
		}

		// PC,HOM,MERC,ELEM�͎g�p�����`�F�b�N
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

		// �G���A�`���b�g
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

		// �X�L���g�p�Ŕ�������I�[�g�X�y��,�A�N�e�B�u�A�C�e��
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

	// �X�L���g�p���s
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
 * �X�L���g�p�i�r�������A�ꏊ�w��̎��ۂ̏����j
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
	case SC_ESCAPE:
	case SU_CN_METEOR:
	case SU_CN_METEOR2:
	case HN_METEOR_STORM_BUSTER:
		break;
	default:
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
	}

	switch(skillid)
	{
	case AC_SHOWER:				/* �A���[�V�����[ */
	case MA_SHOWER:
		{
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
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

	case PR_BENEDICTIO:			/* ���̍~�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_damage_id);
		}
		break;

	case BS_HAMMERFALL:			/* �n���}�[�t�H�[�� */
		skill_addtimerskill(src,tick+skill_get_time(skillid,skilllv),0,x,y,skillid,skilllv,BF_WEAPON,flag|BCT_ENEMY|2);
		break;

	case HT_DETECTING:				/* �f�B�e�N�e�B���O */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(status_change_timer_sub,src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,src,SC_SIGHT,skilllv,tick);
		}
		break;

	case WZ_ICEWALL:			/* �A�C�X�E�H�[�� */
		if(map[src->m].flag.noicewall) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_MAP,0,0);
		} else {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case MG_SAFETYWALL:			/* �Z�C�t�e�B�E�H�[�� */
	case MG_FIREWALL:			/* �t�@�C�A�[�E�H�[�� */
	case MG_THUNDERSTORM:		/* �T���_�[�X�g�[�� */
	case AL_PNEUMA:				/* �j���[�} */
	case WZ_FIREPILLAR:			/* �t�@�C�A�s���[ */
	case WZ_VERMILION:			/* ���[�h�I�u���@�[�~���I�� */
	case WZ_FROSTNOVA:          /* �t���X�g�m���@ */ 
	case WZ_HEAVENDRIVE:		/* �w�����Y�h���C�u */
	case WZ_QUAGMIRE:			/* �N�@�O�}�C�A */
	case PR_SANCTUARY:			/* �T���N�`���A�� */
	case PR_MAGNUS:				/* �}�O�k�X�G�N�\�V�Y�� */
	case CR_GRANDCROSS:			/* �O�����h�N���X */
	case NPC_GRANDDARKNESS:			/* �O�����h�_�[�N�l�X */
	case AS_VENOMDUST:			/* �x�i���_�X�g */
	case AM_DEMONSTRATION:		/* �f�����X�g���[�V���� */
	case PF_SPIDERWEB:			/* �X�p�C�_�[�E�F�u */
	case PF_FOGWALL:			/* �E�H�[���I�u�t�H�O */
	case NJ_TATAMIGAESHI:		/* ���Ԃ� */
	case NJ_BAKUENRYU:			/* �����w */
	case NJ_HYOUSYOURAKU:		/* �X������ */
	case MH_POISON_MIST:		/* �|�C�Y���~�X�g */
	case MH_STEINWAND:			/* �V���^�C�������h */
	case MH_LAVA_SLIDE:			/* ���[���@�X���C�h */
	case MH_VOLCANIC_ASH:		/* �{���J�j�b�N�A�b�V�� */
	case NPC_EVILLAND:			/* �C�[�r�������h */
	case NPC_VENOMFOG:			/* �x�i���t�H�O */
	case NPC_FLAMECROSS:		/* �t���C���N���X */
	case NPC_HELLBURNING:		/* �w���o�[�j���O */
	case NPC_REVERBERATION:		/* M�U���c�� */
	case NPC_CLOUD_KILL:			/* M�N���E�h�L�� */
	case NPC_PSYCHIC_WAVE:		/* M�T�C�L�b�N�E�F�[�u */
	case NPC_CANE_OF_EVIL_EYE:		/* �P�[���I�u�C�r���A�C */
	case GC_POISONSMOKE:		/* �|�C�Y���X���[�N */
	case WL_COMET:				/* �R���b�g */
	case NPC_COMET:				/* M�R���b�g */
	case SC_MANHOLE:			/* �}���z�[�� */
	case SC_DIMENSIONDOOR:		/* �f�B�����V�����h�A */
	case SC_CHAOSPANIC:			/* �J�I�X�p�j�b�N */
	case SC_MAELSTROM:			/* ���C���X�g�[�� */
	case SC_BLOODYLUST:			/* �u���b�f�B���X�g */
	case WM_REVERBERATION:		/* �U���c�� */
	case WM_POEMOFNETHERWORLD:	/* �n���̉� */
	case SO_EARTHGRAVE:			/* �A�[�X�O���C�u */
	case SO_DIAMONDDUST:		/* �_�C�������h�_�X�g */
	case SO_PSYCHIC_WAVE:		/* �T�C�L�b�N�E�F�[�u */
	case SO_CLOUD_KILL:			/* �N���E�h�L�� */
	case SO_WARMER:				/* �E�H�[�}�[ */
	case SO_VACUUM_EXTREME:		/* �o�L���[���G�N�X�g���[�� */
	case SO_FIRE_INSIGNIA:		/* �t�@�C�A�[�C���V�O�j�A */
	case SO_WATER_INSIGNIA:		/* �E�H�[�^�[�C���V�O�j�A */
	case SO_WIND_INSIGNIA:		/* �E�B���h�C���V�O�j�A */
	case SO_EARTH_INSIGNIA:		/* �A�[�X�C���V�O�j�A */
	case GN_THORNS_TRAP:		/* �\�[���g���b�v */
	case GN_DEMONIC_FIRE:		/* �f���j�b�N�t�@�C�A�[ */
	case GN_HELLS_PLANT:		/* �w���Y�v�����g */
	case SU_NYANGGRASS:			/* �j�����O���X */
	case SJ_BOOKOFCREATINGSTAR:	/* �n���̏� */
	case AG_RAIN_OF_CRYSTAL:	/* ���C���I�u�N���X�^�� */
	case AG_MYSTERY_ILLUSION:	/* �~�X�e���[�C�����[�W���� */
	case AG_STRANTUM_TREMOR:	/* �X�g���^���g���}�[ */
	case AG_TORNADO_STORM:		/* �g���l�[�h�X�g�[�� */
	case AG_FLORAL_FLARE_ROAD:	/* �t���[�����t���A���[�h */
	case IG_CROSS_RAIN:			/* �N���X���C�� */
	case CD_PNEUMATICUS_PROCELLA:	/* �j���[�}�e�B�b�N�v���Z�� */
	case ABC_ABYSS_STRIKE:		/* �I���K�A�r�X�X�g���C�N */
	case ABC_ABYSS_SQUARE:		/* �A�r�X�X�N�G�A */
	case WH_DEEPBLINDTRAP:		/* �f�B�[�v�u���C���h�g���b�v */
	case WH_SOLIDTRAP:			/* �\���b�h�g���b�v */
	case WH_SWIFTTRAP:			/* �X�C�t�g�g���b�v */
	case WH_FLAMETRAP:			/* �t���C���g���b�v */
	case EM_DIAMOND_STORM:		/* �_�C�������h�X�g�[�� */
	case EM_LIGHTNING_LAND:		/* ���C�g�j���O�����h */
	case EM_VENOM_SWAMP:		/* �x�i���X�����v */
	case EM_CONFLAGRATION:		/* �R���t���O���[�V���� */
	case EM_TERRA_DRIVE:		/* �e���h���C�u */
	case NW_GRENADES_DROPPING:	/* �O���l�[�Y�h���b�s���O */
	case SOA_TOTEM_OF_TUTELARY:	/* ��褓� */
	case SH_HYUN_ROKS_BREEZE:	/* �f�B�A�[�u���[�Y */
	case SS_SHINKIROU:			/* 凋C�O���g */
	case SS_FUUMASHOUAKU:		/* �����藠�� -����- */
	case MA_SKIDTRAP:
	case MA_LANDMINE:
	case MA_SANDMAN:
	case MA_FREEZINGTRAP:
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case HT_SKIDTRAP:			/* �X�L�b�h�g���b�v */
	case HT_LANDMINE:			/* �����h�}�C�� */
	case HT_ANKLESNARE:			/* �A���N���X�l�A */
	case HT_SHOCKWAVE:			/* �V���b�N�E�F�[�u�g���b�v */
	case HT_SANDMAN:			/* �T���h�}�� */
	case HT_FLASHER:			/* �t���b�V���[ */
	case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
	case HT_BLASTMINE:			/* �u���X�g�}�C�� */
	case HT_CLAYMORETRAP:		/* �N���C���A�g���b�v */
	case HT_TALKIEBOX:			/* �g�[�L�[�{�b�N�X */
		if(sd) {
			int i, nameid, amount, idx, trapid = 0;
			for(i = 0; i < MAX_SKILL_DB_ITEM; i++) {
				nameid = skill_db[skill_get_skilldb_id(skillid)].itemid[i];
				amount = skill_db[skill_get_skilldb_id(skillid)].amount[i];
				if(nameid <= 0 || amount <= 0)
					continue;
				idx = pc_search_inventory(sd,nameid);

				// �g���b�v�������K�����Őݒu�p�g���b�v������Ȃ������ꍇ
				if((idx < 0 || sd->status.inventory[idx].amount < amount) &&
					pc_checkskill(sd,RA_RESEARCHTRAP) && nameid == 1065)
				{
					// ���ǌ^�ݒu�p�g���b�v������
					nameid = 7940;
					amount = 1;
					idx = pc_search_inventory(sd,nameid);
				}

				if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {
					pc_delitem(sd,idx,amount,0,1);
					// ������̂��g���b�v�n�A�C�e���̏ꍇ
					if(nameid == 1065 || nameid == 7940)
						trapid = nameid;
				}
			}
			skill_unitsetting(src,skillid,skilllv,x,y,trapid);
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case HW_GRAVITATION:		/* �O���r�e�[�V�����t�B�[���h */
		{
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,x,y,0);
			if(sg) {
				struct unit_data *ud = unit_bl2ud(src);
				if(ud && DIFF_TICK(ud->canact_tick, tick) < 5000) {
					// ������5�b�Ԃ̓����O�֎~
					ud->canact_tick = tick + 5000;
				}
				status_change_start(src,SC_GRAVITATION_USER,skilllv,0,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case RG_GRAFFITI:			/* �O���t�B�e�B */
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,x,y,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_GROUNDDRIFT:			/* �O���E���h�h���t�g */
		if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if(idx >= 0 && sd->inventory_data[idx]) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// �e�̏���
					break;
				skill_unitsetting(src,skillid,skilllv,x,y,sd->arrow_ele);
			}
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case SA_VOLCANO:		/* �{���P�[�m */
	case SA_DELUGE:			/* �f�����[�W */
	case SA_VIOLENTGALE:		/* �o�C�I�����g�Q�C�� */
	case SA_LANDPROTECTOR:		/* �����h�v���e�N�^�[ */
	case NJ_SUITON:			/* ���� */
	case NJ_KAENSIN:		/* �Ή��w */
		skill_clear_element_field(src);	// ���Ɏ������������Ă��鑮������N���A
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case WZ_METEOR:			/* ���e�I�X�g�[�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int interval = (skilllv > 10)? 2500: 1000;
			int loop = skilllv / 2 + 2;
			for(i=0; i < loop; i++) {
				if(skilllv > 10) {
					tmpx = x + (atn_rand()%29 - 14);
					tmpy = y + (atn_rand()%29 - 14);
				} else {
					tmpx = x + (atn_rand()%(ar*2+1) - ar);
					tmpy = y + (atn_rand()%(ar*2+1) - ar);
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

	case WZ_STORMGUST:          /* �X�g�[���K�X�g */ 
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, j;

			// ���j�b�g��쐼���k���܂�81���
			for(i = 0; i < (ar*2+1); i++) {
				for(j = 0; j < (ar*2+1); j++) {
					skill_unitsetting(src,skillid,skilllv,x-ar+i,y-ar+j,0);
				}
			}
		}
		break;

	case AL_WARP:				/* ���[�v�|�[�^�� */
		if(sd) {
			const char *p[3];
			int i = 0;
			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportal�ŋ֎~
					break;
			} else {
				if(map[sd->bl.m].flag.noteleport)	// noteleport�ŋ֎~
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
	case HW_GANBANTEIN:			/* �K���o���e�C�� */
		if(atn_rand()%100 < 80) {
			map_foreachinarea(skill_delunit_by_ganbantein,src->m,x-1,y-1,x+1,y+1,BL_SKILL);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case MO_BODYRELOCATION:			/* �c�e */
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
	case AM_CANNIBALIZE:	/* �o�C�I�v�����g */
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

				// ��ړ��ŃA�N�e�B�u�Ŕ�������[0x0:��ړ� 0x1:�ړ� 0x4:ACT 0x8:��ACT 0x40:������ 0x80:�����L]
				tmpmd->mode = MD_AGGRESSIVE + MD_CANATTACK;

				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.special_mob_ai = MOB_AI_SUMMON;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_CULTIVATION:	/* �A���͔| */
		if(sd) {
			int id, n = (skilllv >= 2)? 1: 0;
			const int summons[2][6] = {
				{ 1084, 1085, 1084, 1085, 1084, 1085 },
				{ 1078, 1079, 1080, 1081, 1082, 1083 }
			};
			int i = skilllv - 1;
			int j = pc_search_inventory(sd,skill_db[skillid].lv_itemid[i]);
			struct mob_data *tmpmd = NULL;

			if(j < 0 || skill_db[skillid].lv_itemid[i] <= 0 || sd->inventory_data[j] == NULL ||
				sd->status.inventory[j].amount < skill_db[skillid].lv_amount[i] ||
				map_count_oncell(src->m,x,y,BL_MOB) || atn_rand()%100 < 50)
			{
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			id = mob_once_spawn(sd, sd->bl.m, x, y, "--ja--", summons[n][atn_rand()%6], 1, "");

			if((tmpmd = map_id2md(id)) != NULL)
				tmpmd->deletetimer = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case AM_SPHEREMINE:	/* �X�t�B�A�[�}�C�� */
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
				tmpmd->state.special_mob_ai = MOB_AI_SPHERE1;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_SLIMPITCHER:
		if(sd) {
			int ar = skill_get_area(skillid,skilllv);
			int i = (skilllv > 10)? 9: skilllv - 1;
			int j, itemid;

			if(battle_config.slimpitcher_nocost && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg) {
				const int potion[10] = { 501, 501, 501, 501, 501, 503, 503, 503, 503, 504 };
				itemid = potion[i];
			} else {
				itemid = skill_db[skillid].lv_itemid[i];
			}
			j = pc_search_inventory(sd,itemid);
			if(j < 0 || itemid <= 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[skillid].lv_amount[i]) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				return 1;
			}
			sd->state.potionpitcher_flag = 1;
			sd->potion.hp = 0;
			if(sd->inventory_data[j]->use_script) {
				run_script(sd->inventory_data[j]->use_script,0,sd->bl.id,0);
			}
			pc_delitem(sd,j,skill_db[skillid].lv_amount[i],0,1);
			sd->state.potionpitcher_flag = 0;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			if(sd->potion.hp > 0) {
				map_foreachinarea(skill_area_sub,
					src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
		}
		break;
	case NJ_HUUMA:		/* �����藠������ */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NJ_RAIGEKISAI:	/* ������ */
#ifndef PRE_RENEWAL
		clif_skill_nodamage(src,src,skillid,skilllv,1);
#endif
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NJ_SHADOWJUMP:	/* �e���� */
		if(sd && map[sd->bl.m].flag.gvg) {
			clif_skill_fail(sd,skillid,SKILLFAIL_MAP,0,0);
		} else {
			struct status_change *sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// �R�ł��\�Z���͖������Ĉړ�
				if(map_getcellp(&map[src->m],x,y,CELL_CHKPASS)) {
					unit_movepos(src,x,y,0x21);
					status_change_end(src, SC_HIDING, -1);
				}
			}
		}
		break;
	case MH_XENO_SLASHER:		/*�[�m�X���b�V���[ */
		{
			int ar = skill_get_area(skillid,skilllv);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_WINDCUTTER:	/* �E�B���h�J�b�^�[ */
		{
			int dir = path_calc_dir(src,x,y);
			skill_area_temp[1] = src->id;
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],7,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case RK_DRAGONBREATH:		/* �t�@�C�A�[�h���S���u���X */
	case RK_DRAGONBREATH_WATER:	/* �E�H�[�^�[�h���S���u���X */
		{
			int ar = skill_get_area(skillid,skilllv);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AB_EPICLESIS:			/* �G�s�N���V�X */
		{
			int ar = skill_get_unit_range(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_PC,
				src,ALL_RESURRECTION,3,tick,flag|BCT_NOENEMY|1,
				skill_castend_nodamage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case WL_EARTHSTRAIN:		/* �A�[�X�X�g���C�� */
		{
			int dir = 4;
			int tmpx, tmpy;
			int addx = 0, addy = 0;
			int i, loop = skilllv + 4;
			struct skill_unit_group *sg = NULL;

			if(src->type == BL_PC)
				dir = (src->x == x && src->y == y)? 4: path_calc_dir(src,x,y);

			// �c��D��
			addy = diry[dir];
			addx = (addy == 0)? dirx[dir]: 0;

			// �����ʒu���w��
			tmpx = src->x + addx;
			tmpy = src->y + addy;

			sg = skill_unitsetting(src,skillid,skilllv,tmpx,tmpy,0);
			if(sg) {
				for(i = 1; i < loop; i++) {
					tmpx += addx;
					tmpy += addy;

					skill_addtimerskill(src,tick+i*200,0,addx,addy,skillid,skilllv,sg->bl.id,(tmpx<<16)|tmpy);
				}
			}
		}
		break;
	case RA_DETONATOR:				/* �f�g�l�C�^�[ */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// �G�t�F�N�g���o�����߂̎b�菈�u
			map_foreachinarea(skill_detonator,src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,src);
		}
		break;
	case RA_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
	case RA_CLUSTERBOMB:		/* �N���X�^�[�{�� */
	case RA_MAGENTATRAP:		/* �}�[���^�g���b�v */
	case RA_COBALTTRAP:			/* �R�o���g�g���b�v */
	case RA_MAIZETRAP:			/* ���C�Y�g���b�v */
	case RA_VERDURETRAP:		/* ���F���f���[���g���b�v */
	case RA_FIRINGTRAP:			/* �t�@�C�A�����O�g���b�v */
	case RA_ICEBOUNDTRAP:		/* �A�C�X�o�E���h�g���b�v */
		if(sd)
			skill_unitsetting(src,skillid,skilllv,x,y,7940);
		else
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NC_COLDSLOWER:	/* �R�[���h�X���[���[ */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_SILVERSNIPER:	/* FAW �V���o�[�X�i�C�p�[ */
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
				tmpmd->state.special_mob_ai = MOB_AI_SUMMON;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case NC_MAGICDECOY:		/* FAW �}�W�b�N�f�R�C */
		if(sd) {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			clif_magicdecoy_list(sd,skilllv,x,y);
		}
		break;
	case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
	case NPC_MAGMA_ERUPTION:	/* M�}�O�}�C���v�V���� */
		skill_addtimerskill(src,tick+1000,0,x,y,skillid,skilllv,0,flag);
		break;
	case LG_OVERBRAND:		/* �I�[�o�[�u�����h */
		{
			int dir = path_calc_dir(src,x,y);
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],6,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,skill_castend_damage_id
			);
			skill_addtimerskill(src,tick+200,0,x,y,LG_OVERBRAND_BRANDISH,skilllv,0,flag);
		}
		break;
	case LG_RAYOFGENESIS:	/* ���C�I�u�W�F�l�V�X */
	case NPC_RAYOFGENESIS:	/* M���C�I�u�W�F�l�V�X */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_RIDEINLIGHTNING:	/* �����e */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WM_DOMINION_IMPULSE:		/* �h�~�j�I���C���p���X */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_dominion_impulse,src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL);
		}
		break;
	case WM_SEVERE_RAINSTORM:	/* �V�r�A���C���X�g�[�� */
		if(sd) {
			int cost = skill_get_arrow_cost(skillid,skilllv);
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
				break;
		}
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case WM_LULLABY_DEEPSLEEP:		/* ���炬�̎q��S */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_GREAT_ECHO:			/* �O���[�g�G�R�[ */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SO_ARRULLO:	/* �A���[�W�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_CRAZYWEED:		/* �N���C�W�[�E�B�[�h */
		{
			int ar = skill_get_area(skillid,skilllv);
			int tmpx, tmpy, i, num;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			num = skill_get_num(skillid,skilllv);
			for(i=0; i<num; i++) {
				tmpx = x + (atn_rand()%(ar*2+1) - ar);
				tmpy = y + (atn_rand()%(ar*2+1) - ar);
				skill_addtimerskill(src,tick+i*200,0,tmpx,tmpy,skillid,skilllv,0,0);
			}
		}
		break;
	case GN_FIRE_EXPANSION:		/* �t�@�C�A�[�G�N�X�p���V���� */
		if(sd) {
			int i = (skilllv > skill_get_max(skillid))? skill_get_max(skillid) - 1: skilllv - 1;
			int id, j;

			if(i >= 10) {
				i = 9;
			}
			id = skill_get_skilldb_id(skillid);
			j  = pc_search_inventory(sd,skill_db[id].lv_itemid[i]);

			if(j < 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[id].lv_amount[i]) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			pc_delitem(sd,j,skill_db[id].lv_amount[i],0,1);
		}
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		map_foreachinarea(skill_fire_expansion,src->m,x-2,y-2,x+2,y+2,BL_SKILL,src,skilllv,tick);
		break;
	case KO_MUCHANAGE:		/* �������� */
		{
			int ar = skill_get_area(skillid,skilllv);
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
	case KO_MAKIBISHI:			/* �T�H */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i;
			for(i = 0; i < skilllv+2; i++) {
				x = src->x - ar + atn_rand()%(ar*2+1);
				y = src->y - ar + atn_rand()%(ar*2+1);
				skill_unitsetting(src,skillid,skilllv,x,y,0);
			}
		}
		break;
	case KO_ZENKAI:		/* �p���S�J */
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case RL_FALLEN_ANGEL:		/* �t�H�[�����G���W�F�� */
		if( !map[src->m].flag.turbo && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
		    map_getcell(src->m,x,y,CELL_CHKPASS)
		) {
			unit_movepos(src,x,y,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			status_change_start(src,SC_FALLEN_ANGEL,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case RL_FIRE_RAIN:	/* �t�@�C�A�[���C�� */
		{
			int dir = (src->x == x && src->y == y)? 0: path_calc_dir(src,x,y);
			int tmpx, tmpy;
			int addx = 0, addy = 0;
			int dist = path_distance(src->x,src->y,x,y);
			int i;

			// �c��D��
			addy = diry[dir];
			addx = (addy == 0)? dirx[dir]: 0;

			// �����ʒu���w��
			tmpx = src->x + addx * dist;
			tmpy = src->y + addy * dist;

			clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
			for(i = 1; i <= 10; i++) {
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,flag);
				tmpx += addx;
				tmpy += addy;
			}
		}
		break;
	case SU_LOPE:		/* �j�����W�����v */
		if( !map[src->m].flag.turbo && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
		    map_getcell(src->m,x,y,CELL_CHKPASS) && !map_count_oncell(src->m,x,y,BL_PC|BL_MOB|BL_NPC)
		) {
			unit_movepos(src,x,y,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case SU_CN_METEOR:	/* �C�k�n�b�J���e�I */
	case SU_CN_METEOR2:			/* �C�k�n�b�J���e�I(��) */
		{
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int ar = skill_get_area(skillid,skilllv);
			int interval = 650;
			int skill = SU_CN_METEOR;
			if(sd) {
				int nameid, amount, idx = 0;

				nameid = 11602;	// �C�k�n�b�J�̎�
				amount = 1;

				idx = pc_search_inventory(sd,nameid);

				if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {	// �C�k�n�b�J�̎��������Ă������
					pc_delitem(sd,idx,amount,0,1);
					skill = SU_CN_METEOR2;
				}
			}
			for(i=0; i < 7; i++) {
				tmpx = x + atn_rand()%(ar*2+1) - ar;
				tmpy = y + atn_rand()%(ar*2+1) - ar;
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skill,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skill,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skill,skilllv,-1,0);
		}
		break;
	case NPC_LEX_AETERNA:		/* M���b�N�X�G�[�e���i */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_DRAGONBREATH:	/* M�h���S���u���X */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_WIDESUCK:		/* ���C�h�u���b�h */
		skill_area_temp[1] = src->id;
		skill_area_temp[2] = x;
		skill_area_temp[3] = y;
		skill_addtimerskill(src,tick+500,0,x,y,skillid,skilllv,0,0);
		skill_addtimerskill(src,tick+1500,0,x,y,skillid,skilllv,0,0);
		skill_addtimerskill(src,tick+2500,0,x,y,skillid,skilllv,0,0);
		break;
	case AG_VIOLENT_QUAKE:		/* �o�C�I�����g�N�G�C�N */
	case AG_ALL_BLOOM:			/* �I�[���u���[�� */
		{
			int climax = 0;
			struct status_change *sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1)
				climax = sc->data[SC_CLIMAX].val1;
			skill_unitsetting(src,skillid,skilllv,x,y,climax);
		}
		break;
	case AG_ASTRAL_STRIKE:		/* �A�X�g�����X�g���C�N */
		{
			int ar = skill_get_area(AG_ASTRAL_STRIKE_ATK,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,AG_ASTRAL_STRIKE_ATK,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case NW_WILD_FIRE:		/* ���C���h�t�@�C�A */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
				if(sd->status.weapon == WT_GRENADE)
					ar += 1;
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_HASTY_FIRE_IN_THE_HOLE:	/* �w�C�X�e�B�t�@�C�A�C���U�z�[�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_addtimerskill(src,tick+300,0,x,y,skillid,skilllv,BF_WEAPON,flag);
			skill_addtimerskill(src,tick+600,0,x,y,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case NW_MISSION_BOMBARD:	/* �~�b�V�����{���o�[�h */
		{
			int ar = skill_get_unit_range(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case SOA_TALISMAN_OF_BLACK_TORTOISE:	/* ������ */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sc && sc->data[SC_T_THIRD_GOD].timer != -1) {
				status_change_end(src, SC_T_THIRD_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case HN_METEOR_STORM_BUSTER:	/* ���e�I�X�g�[���o�X�^�[ */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int loop = skilllv / 2 + 3;
			for(i=0; i < loop; i++) {
				tmpx = x + (atn_rand()%(ar*2+1) - ar);
				tmpy = y + (atn_rand()%(ar*2+1) - ar);
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*500,0,tmpx,tmpy,skillid,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*500,0,tmpx,tmpy,skillid,skilllv,-1,0);
		}
		break;
	case HN_JACK_FROST_NOVA:	/* �W���b�N�t���X�g�m���@ */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case SS_TOKEDASU:		/* �e�n�� */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// �o�b�N�X�e�b�v
				int dir = 0, head_dir = 0;
				int count = skill_get_blewcount(skillid,skilllv);
				struct block_list pos;
				memset(&pos,0,sizeof(pos));
				pos.m = src->m;
				pos.x = x;
				pos.y = y;

				if(sd) {
					dir = sd->dir;
					head_dir = sd->head_dir;
				}
				unit_stop_walking(src,1);
				skill_blown(&pos,src,count|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
				if(sd)
					pc_setdir(sd, dir, head_dir);
			}
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SS_KAGEGARI:			/* �e��� */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
		}
		break;
	case SS_FUUMAKOUCHIKU:		/* �����藠�� -�\�z- */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			map_foreachinarea(skill_fuumakouchiku,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,
				src,skilllv,tick);
		}
		break;
	case SS_KUNAIWAIKYOKU:		/* �ꖳ -�c��- */
		{
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// ��̏���
					break;
			}
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,skillid,tick);
		}
		break;
	case SS_REIKETSUHOU:		/* �⌌�C */
		{
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,SS_ANTENPOU,tick);
		}
		break;
	}
	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������Amap�w��j
 *------------------------------------------
 */
void skill_castend_map( struct map_session_data *sd,int skill_num, const char *mapname)
{
	nullpo_retv(sd);

	if( sd->bl.prev == NULL || unit_isdead(&sd->bl) )
		return;

	// �s���p�P�b�g
	if(skill_num != sd->ud.skillid)
		return;

	if( (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->sc.option&OPTION_HIDE )
		return;

	// �X�L�����g���Ȃ���Ԉُ풆
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
	case AL_TELEPORT:		/* �e���|�[�g */
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
	case AL_WARP:			/* ���[�v�|�[�^�� */
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
			if(x == 0 || y == 0)	// �s���p�P�b�g�H
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
 * �X�L�����j�b�g�ݒ菈��
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
	case MG_SAFETYWALL:			/* �Z�C�t�e�B�E�H�[�� */
#ifndef PRE_RENEWAL
		val1 = 13000+300*skilllv;
		if(sd) val1 += sd->status.max_sp;
#endif
		val2 = skilllv+1;
		break;
	case WZ_METEOR:
		/* ���e�I�X�g�[��(�I�[�o�[���x��) */
		if(src->type == BL_MOB && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
			range = 10;
		break;
	case WZ_VERMILION:
		/* ���[�h�I�u���@�[�~���I��(�I�[�o�[���x��) */
		if(src->type == BL_MOB && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
			range = 20;
		break;
	case MG_FIREWALL:			/* �t�@�C�A�[�E�H�[�� */
	case NPC_FLAMECROSS:		/* �t���C���N���X */
		val2 = 4+skilllv;
		break;
	case AL_WARP:				/* ���[�v�|�[�^�� */
		val1 = skilllv+6;
		if(flag)
			unit_id = skill_get_unit_id(skillid,1);
		else
			limit=2000;
		break;
	case PR_SANCTUARY:			/* �T���N�`���A�� */
		val1 = skilllv*2+6;
		val2 = skill_fix_heal(src, NULL, skillid, ((skilllv > 6)? 777: skilllv * 100));
		interval = interval + 500;
		break;
	case WZ_FIREPILLAR:			/* �t�@�C�A�[�s���[ */
		if(flag) {
			unit_id = skill_get_unit_id(skillid,1);
			limit = 150;
		}
		break;
	case HT_SKIDTRAP:			/* �X�L�b�h�g���b�v */
	case MA_SKIDTRAP:
		val1 = src->x;
		val2 = src->y;
		val3 = flag;		// 㩃A�C�e��ID
		if(map[src->m].flag.gvg)
			limit <<= 2;
		break;
	case HT_LANDMINE:		/* �����h�}�C�� */
	case HT_ANKLESNARE:		/* �A���N���X�l�A */
	case HT_SHOCKWAVE:		/* �V���b�N�E�F�[�u�g���b�v */
	case HT_SANDMAN:		/* �T���h�}�� */
	case HT_FLASHER:		/* �t���b�V���[ */
	case HT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
	case HT_BLASTMINE:		/* �u���X�g�}�C�� */
	case HT_CLAYMORETRAP:	/* �N���C���A�g���b�v */
	case HT_TALKIEBOX:		/* �g�[�L�[�{�b�N�X */
	case MA_LANDMINE:
	case MA_SANDMAN:
	case MA_FREEZINGTRAP:
		val3 = flag;		// 㩃A�C�e��ID
		if(map[src->m].flag.gvg)
			limit <<= 2;
		break;
	case BA_WHISTLE:			/* ���J */
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
	case DC_HUMMING:			/* �n�~���O */
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
	case DC_DONTFORGETME:		/* ����Y��Ȃ��Łc */
		val1 = status_get_dex(src)/10 + 3*skilllv + 5;
		val2 = status_get_agi(src)/10 + 3*skilllv + 5;
		if(sd){
			val1 += pc_checkskill(sd,DC_DANCINGLESSON);
			val2 += pc_checkskill(sd,DC_DANCINGLESSON);
		}
		break;
	case BA_POEMBRAGI:			/* �u���M�̎� */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = (status_get_dex(src)/10) << 16;
		val2 |= status_get_int(src)/5;
		break;
	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = status_get_vit(src);
		val3 = 0;
		break;
	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON)>>1;
		val2 = status_get_int(src)/10;
		break;
	case BA_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
		if(sd)
			val1 = pc_checkskill(sd,BA_MUSICALLESSON);
		val2 = (val1/2 + status_get_agi(src)/20) + skilllv;
		break;
	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
		if(sd)
			val1 = pc_checkskill(sd,DC_DANCINGLESSON)>>1;
		val2 = status_get_luk(src)/10;
		break;
	case HP_BASILICA:
		val1 = src->id;
		break;
	case SA_VOLCANO:		/* �{���P�[�m */
	case SA_DELUGE:			/* �f�����[�W */
	case SA_VIOLENTGALE:	/* �o�C�I�����g�Q�C�� */
		if(sd) {
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
			{
				// ���x���̒Ⴂ���̂��g�����ꍇ�������Ԍ����H
				// ������̎c�莞�ԎZ�o
				limit = sd->sc.data[SC_ELEMENTFIELD].val2 - DIFF_TICK(tick, (unsigned int)sd->sc.data[SC_ELEMENTFIELD].val3);
			} else {
				status_change_start(src,SC_ELEMENTFIELD,1,skill_get_time(skillid,skilllv),tick,0,0,0);
			}
		}
		break;
	case GS_DESPERADO:	/* �f�X�y���[�h */
		val2 = flag;
		break;
	case GS_GROUNDDRIFT:	/* �O���E���h�h���t�g */
		// flag = �e�̑�����Unit������
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
	case NPC_EVILLAND:		/* �C�[�r�������h */
		val1 = (skilllv > 6)? 666: skilllv*100;
		interval += 500;
		break;
	case NPC_VENOMFOG:			// �x�i���t�H�O
		if(src->type == BL_MOB)
			val1 = mobdb_search(((struct mob_data *)src)->class_)->atk1;
		else
			val1 = status_get_atk(src);
		interval += 500;
		break;
	case GC_POISONSMOKE:	/* �|�C�Y���X���[�N */
		if(sd) {
			if(sd->sc.data[SC_POISONINGWEAPON].timer != -1) {
				val1 = sd->sc.data[SC_POISONINGWEAPON].val2;
				//status_change_end(&sd->bl,SC_POISONINGWEAPON,-1);
			}
		}
		break;
	case RA_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
	case RA_CLUSTERBOMB:		/* �N���X�^�[�{�� */
	case RA_MAGENTATRAP:		/* �}�[���^�g���b�v */
	case RA_COBALTTRAP:			/* �R�o���g�g���b�v */
	case RA_MAIZETRAP:			/* ���C�Y�g���b�v */
	case RA_VERDURETRAP:		/* ���F���f���[���g���b�v */
	case RA_FIRINGTRAP:			/* �t�@�C�A�����O�g���b�v */
	case RA_ICEBOUNDTRAP:		/* �A�C�X�o�E���h�g���b�v */
		val3 = flag;		// 㩃A�C�e��ID
		break;
	case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
	case NPC_MAGMA_ERUPTION:	/* M�}�O�}�C���v�V���� */
		limit = interval * 10;
		break;
	case LG_BANDING:	/* �o���f�B���O */
		limit = 600000;		// ���Ԑ؂ꖳ��
		break;
	case KO_ZENKAI:		/* �p���S�J */
		if(sd) {
			// �������̋��̂̑����ɉ�����unit_id��ω�������
			switch(sd->elementball.ele) {
				case ELE_WATER:
					unit_id = UNT_ZENKAI_WATER;
					val1    = ELE_WATER;	// val1�͑����l
					break;
				case ELE_EARTH:
					unit_id = UNT_ZENKAI_GROUND;
					val1    = ELE_EARTH;	// val1�͑����l
					break;
				case ELE_FIRE:
					unit_id = UNT_ZENKAI_FIRE;
					val1    = ELE_FIRE;	// val1�͑����l
					break;
				case ELE_WIND:
					unit_id = UNT_ZENKAI_WIND;
					val1    = ELE_WIND;	// val1�͑����l
					break;
			}
			// �������̋��̂̐��ɉ�����limit�����т�
			limit *= sd->elementball.num;
		} else {
			val1 = ELE_FIRE;	// val1�͑����l
		}
		break;
	case AG_VIOLENT_QUAKE:		/* �o�C�I�����g�N�G�C�N */
		if(flag == 5) {		// �N���C�}�b�N�XLv5�F�����͈͂����܂�
			range -= 1;
		}
		val1 = flag;
		break;
	case AG_VIOLENT_QUAKE_ATK:	/* �o�C�I�����g�N�G�C�N(�U��) */
		if(flag == 2) {		// �N���C�}�b�N�XLv2�F�_���[�W�͈͂��g��
			range *= 2;
		}
		val1 = flag;
		break;
	case AG_ALL_BLOOM:			/* �I�[���u���[�� */
		if(flag == 1) {		// �N���C�}�b�N�XLv1�F�����Ԋu������
			interval /= 2;
			limit /= 2;
		}
		val1 = flag;
		break;
	case AG_ALL_BLOOM_ATK:		/* �I�[���u���[��(�U��) */
		val1 = flag;
		break;
	case WH_DEEPBLINDTRAP:	/* �f�B�[�v�u���C���h�g���b�v */
	case WH_SOLIDTRAP:		/* �\���b�h�g���b�v */
	case WH_SWIFTTRAP:		/* �X�C�t�g�g���b�v */
	case WH_FLAMETRAP:		/* �t���C���g���b�v */
		if(sd && pc_checkskill(sd,WH_ADVANCED_TRAP) > 0) {
			limit += 500 + pc_checkskill(sd,WH_ADVANCED_TRAP) * 500;
		}
		break;
	case MH_STEINWAND:			/* �V���^�C�������h */
		val1 = 300*skilllv;
		if(sd && sd->hd) val1 += 65 * (sd->hom.int_ + sd->hom.base_level) + sd->hom.max_sp;
		val2 = skilllv+4;
		break;
	case MH_LAVA_SLIDE:			/* ���[���@�X���C�h */
		val2 = 5;
		break;
	case EL_FIRE_MANTLE:		/* �t�@�C�A�[�}���g�� */
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
		// ���t�X�L���͑������_���X��Ԃɂ���
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
			case MG_FIREWALL:		/* �t�@�C�A�[�E�H�[�� */
				val2 = group->val2;
				// �Q�C����Ȃ玞�Ԕ{
				if(map_find_skill_unit_oncell(src,ux,uy,SA_VIOLENTGALE,NULL)!=NULL)
				{
					limit = limit*150/100;
					on_flag = 1;
				}
				break;
			case WZ_ICEWALL:		/* �A�C�X�E�H�[�� */
				val1 = (skilllv<=1)? 500: 200+200*skilllv;
				break;
			case PF_FOGWALL:
				// �f�����[�W��Ȃ玞�Ԕ{
				if(map_find_skill_unit_oncell(src,ux,uy,SA_DELUGE,NULL)!=NULL)
				{
					limit = limit*2;
					on_flag = 1;
				}
				break;
			case WZ_FIREPILLAR:		/* �t�@�C�A�[�s���[ */
			case HT_LANDMINE:		/* �����h�}�C�� */
			case HT_ANKLESNARE:		/* �A���N���X�l�A */
			case HT_SHOCKWAVE:		/* �V���b�N�E�F�[�u�g���b�v */
			case HT_SANDMAN:		/* �T���h�}�� */
			case HT_FLASHER:		/* �t���b�V���[ */
			case HT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
			case HT_SKIDTRAP:		/* �X�L�b�h�g���b�v */
			case MA_SKIDTRAP:
			case MA_LANDMINE:
			case MA_SANDMAN:
			case MA_FREEZINGTRAP:
				val1 = 3500;	// 㩂̑ϋvHP
				break;
			case HT_TALKIEBOX:		/* �g�[�L�[�{�b�N�X */
				val1 = 70000;	// 㩂̑ϋvHP
				break;
			case NJ_KAENSIN:		/* �Ή��w */
				val1 = 4+(skilllv+1)/2;
				break;
			case SO_FIREWALK:			/* �t�@�C�A�[�E�H�[�N */
			case SO_ELECTRICWALK:		/* �G���N�g���b�N�E�H�[�N */
				val1 = 1 + atn_rand()%3;	// ��
				break;
			case WM_REVERBERATION:	/* �U���c�� */
			case NPC_REVERBERATION:	/* M�U���c�� */
				val1 = 1+skilllv;
				break;
			case GN_WALLOFTHORN:	/* �\�[���E�H�[�� */
				val1 = 2000+2000*skilllv;
				break;
		}

		// �����h�v���e�N�^�[���Ȃ����`�F�b�N
		switch(skillid) {
			case HT_SKIDTRAP:		/* �X�L�b�h�g���b�v */
			case HT_LANDMINE:		/* �����h�}�C�� */
			case HT_ANKLESNARE:		/* �A���N���X�l�A */
			case HT_SHOCKWAVE:		/* �V���b�N�E�F�[�u�g���b�v */
			case HT_SANDMAN:		/* �T���h�}�� */
			case HT_FLASHER:		/* �t���b�V���[ */
			case HT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
			case HT_BLASTMINE:		/* �u���X�g�}�C�� */
			case HT_CLAYMORETRAP:	/* �N���C���A�g���b�v */
			case BD_LULLABY:		/* �q��� */
			case BA_DISSONANCE:		/* �s���a�� */
			case BA_WHISTLE:		/* ���J */
			case BA_ASSASSINCROSS:	/* �[�z�̃A�T�V���N���X */
			case BA_POEMBRAGI:		/* �u���M�̎�*/
			case BA_APPLEIDUN:		/* �C�h�D���̗ь� */
			case DC_UGLYDANCE:		/* ��������ȃ_���X */
			case DC_HUMMING:		/* �n�~���O */
			case DC_DONTFORGETME:	/* ����Y��Ȃ��Łc */
			case DC_FORTUNEKISS:	/* �K�^�̃L�X */
			case DC_SERVICEFORYOU:	/* �T�[�r�X�t�H�[���[ */
			case CG_HERMODE:		/* �w�����[�h�̏� */
			case RL_B_TRAP:			/* �o�C���h�g���b�v */
			case NPC_EVILLAND:		/* �C�[�r�������h */
			case NPC_VENOMFOG:		/* �x�i���t�H�O */
			case MA_SKIDTRAP:		/* �X�L�b�h�g���b�v */
			case MA_LANDMINE:		/* �����h�}�C�� */
			case MA_SANDMAN:		/* �T���h�}�� */
			case MA_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
			case NPC_DISSONANCE:
			case NPC_UGLYDANCE:
				break;
			default:
				map_foreachinarea(skill_landprotector,src->m,ux,uy,ux,uy,BL_SKILL,skillid,&alive);
				if(alive)
					map_foreachinarea(skill_maelstrom,src->m,ux-2,uy-2,ux+2,uy+2,BL_SKILL,skilllv,&alive,&mael_flag);
				break;
		}

		if(unit_flag&UF_PATHCHECK && alive) { // �ː��`�F�b�N
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

	// �S�Ẵ��j�b�g�̐ݒu���I����Ă���X�L�����ʂ𔭓�������
	for(i=0; i<layout->count; i++) {
		struct skill_unit *unit = &group->unit[i];

		if(unit->alive && unit->range == 0) {
			map_foreachinarea(skill_unit_effect,unit->bl.m,
				unit->bl.x,unit->bl.y,unit->bl.x,unit->bl.y,
				(BL_PC|BL_MOB|BL_MERC|BL_ELEM),&unit->bl,tick,1);
		}
	}

	// �X�L�����j�b�g�O���[�v�����ɏ��ł��Ă���\��������̂ōĎ擾
	group = map_id2sg(group->bl.id);

	map_freeblock_unlock();

	if(group && group->alive_count <= 0) {
		// ���j�b�g���������Ȃ�����
		skill_delunitgroup(group);
		group = NULL;
	}

	return group;
}

/*==========================================
 * �X�L�����j�b�g�̔����C�x���g(�ʒu����)
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
		return 0; // ���G�^�C�}�[��

	nullpo_retr(0, sg = src->group);

	if(battle_check_target(&src->bl,bl,sg->target_flag) <= 0)
		return 0;

	sc = status_get_sc(bl);

	// �Ώۂ��z�o�[�����O��Ԃ̏ꍇ�͈ꕔ����
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
//	case UNT_PNEUMA:	/* �j���[�} */
	case UNT_SAFETYWALL:	/* �Z�C�t�e�B�E�H�[�� */
		if(!sc || sc->data[type].timer==-1)
			status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,sg->limit,0);
		break;
	case UNT_QUAGMIRE:	/* �N�@�O�}�C�A */
		if (bl->type==BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
			break;
		if (sc && sc->data[type].timer!=-1)
			break;
		status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_VOLCANO:	/* �{���P�[�m */
	case UNT_DELUGE:	/* �f�����[�W */
	case UNT_VIOLENTGALE:	/* �o�C�I�����g�Q�C�� */
		if (sc && sc->data[type].timer!=-1) {
			unit2 = map_id2su(sc->data[type].val2);
			if (unit2 && unit2->group && (unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_SUITON:	/* ���� */
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
	case UNT_LULLABY:		/* �q��S */
	case UNT_RICHMANKIM:		/* �j�����h�̉� */
	case UNT_ETERNALCHAOS:		/* �i���̍��� */
	case UNT_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case UNT_RINGNIBELUNGEN:	/* �j�[�x�����O�̎w�� */
	case UNT_ROKISWEIL:		/* ���L�̋��� */
	case UNT_INTOABYSS:		/* �[���̒��� */
	case UNT_SIEGFRIED:		/* �s���g�̃W�[�N�t���[�h */
	case UNT_DISSONANCE:		/* �s���a�� */
	case UNT_UGLYDANCE:		/* ��������ȃ_���X */
		// �_���X���ʂ������ɂ�����H
		if (sg->src_id==bl->id && battle_config.allow_me_concert_effect==0)
			break;

		if (sg->unit_id == UNT_ROKISWEIL) {
			// ���L�������ɓK�p���Ȃ�
			if(sg->src_id==bl->id && battle_config.allow_me_concert_effect==1 && battle_config.allow_me_rokisweil==1)
				break;
			// ���L�̓{�X����
			if(status_get_mode(bl)&MD_BOSS)
				break;
		}
		// �i���̍��ׂ̓{�X����
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
	case UNT_WHISTLE:		/* ���J */
	case UNT_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
	case UNT_POEMBRAGI:		/* �u���M�̎� */
	case UNT_APPLEIDUN:		/* �C�h�D���̗ь� */
	case UNT_HUMMING:		/* �n�~���O */
	case UNT_DONTFORGETME:		/* ����Y��Ȃ��Łc */
	case UNT_FORTUNEKISS:		/* �K�^�̃L�X */
	case UNT_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
		// �_���X���ʂ������ɂ�����H
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
	case UNT_CALLFAMILY:				/* ���Ȃ��Ɉ������� or �}�}�A�p�p�A���� or �V��A��������Ⴂ */
		break;
	case UNT_FOGWALL:				/* �E�H�[���I�u�t�H�O */
		if(status_check_no_magic_damage(bl))
			break;
		// ���̒�
		if(map[bl->m].flag.normal) {	// �ʏ�}�b�v
			if(bl->type==BL_PC || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		} else if(status_get_party_id(&src->bl)>0) {	// ����ȊO��PT��
			if(battle_check_target(bl,&src->bl,BCT_ENEMY)<=0 || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		} else {	// ����ȊO�Ń\����
			if(bl->id==sg->src_id || status_get_mode(bl)&MD_BOSS) {
				status_change_start(bl,SC_FOGWALL,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			} else {
				status_change_start(bl,SC_FOGWALLPENALTY,sg->skill_id,sg->skill_lv,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
			}
		}
		break;
	case UNT_MOONLIT:		/* ������̉��� */
		break;
	case UNT_GRAVITATION:		/* �O���r�e�[�V�����t�B�[���h */
		if (battle_check_target(&src->bl,bl,BCT_ENEMY)>0)	// �G�Ώ�
		{
			status_change_start(bl,SC_GRAVITATION,sg->skill_lv,0,0,0,9000,0);
		}
		break;
	case UNT_HERMODE:		/* �w�����[�h�̏� */
		{
			int same_flag = 0;

			// �����͏��O
			if(sg->src_id==bl->id)
				break;

			// �M���h�ƃp�[�e�B�[�������Ȃ�x���X�L�������Ώ�
			if( status_get_guild_id(&src->bl)==status_get_guild_id(bl) ||
			    status_get_party_id(&src->bl)==status_get_guild_id(bl) )
			{
				same_flag = 1;
				// �\�E�������J�[�ȊO�͎x���X�L������
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
	case UNT_NEUTRALBARRIER:	/* �j���[�g�����o���A�[ */
		if(sc && sc->data[type].timer != -1) {
			unit2 = map_id2su(sc->data[type].val4);
			if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
				break;
		}
		status_change_start(bl,SC_NEUTRALBARRIER,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_STEALTHFIELD:	/* �X�e���X�t�B�[���h */
		// �g�p�҂ɂ͌��ʂȂ�
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
	case UNT_KINGS_GRACE:	/* �L���O�X�O���C�X */
		if(sc && sc->data[type].timer != -1) {
			unit2 = map_id2su(sc->data[type].val4);
			if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
				break;
		}
		status_change_start(bl,SC_KINGS_GRACE,sg->skill_lv,sg->val1,sg->val2,
				src->bl.id,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_BLOODYLUST:	/* �u���b�f�B���X�g */
		if(status_get_party_id(&src->bl)>0 && battle_check_target(&src->bl,bl,BCT_ENEMY)<=0) {
			if(sc && sc->data[type].timer != -1) {
				unit2 = map_id2su(sc->data[type].val4);
				if(unit2 && unit2->group && (unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0))
					break;
			}
			status_change_start(bl,SC_BERSERK,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_ZENKAI_WATER:	/* �p���S�J(������) */
	case UNT_ZENKAI_GROUND:	/* �p���S�J(�n����) */
	case UNT_ZENKAI_FIRE:	/* �p���S�J(�Α���) */
	case UNT_ZENKAI_WIND:	/* �p���S�J(������) */
		if( sc && sc->data[type].timer != -1 ) {
			unit2 = map_id2su(sc->data[type].val2);
			if( unit2 && unit2->group && ( unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick) <= 0 ) )
				break;
		}
		status_change_start(bl,type,sg->skill_lv,src->bl.id,sg->val1,15,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		// �G�Ȃ烆�j�b�g�ɉ����ď�Ԉُ��t�^����
		if( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 ) {
			switch(sg->unit_id) {
				case UNT_ZENKAI_WATER:	/* �p���S�J(������) */
					switch(atn_rand()%3) {
					case 0:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_FREEZE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// �X��
						status_change_pretimer(bl,SC_FROSTMISTY,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// �Ⓚ
						status_change_pretimer(bl,SC_DIAMONDDUST,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_GROUND:	/* �p���S�J(�n����) */
					switch(atn_rand()%2) {
					case 0:	// �Ή�
						if(atn_rand() % 10000 < status_change_rate(bl,SC_STONE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_STONE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// ��
						if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_FIRE:	/* �p���S�J(�Α���) */
					// ����
					status_change_pretimer(bl,SC_HELLINFERNO,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
					break;
				case UNT_ZENKAI_WIND:	/* �p���S�J(������) */
					switch(atn_rand()%3) {
					case 0:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SILENCE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// �[������
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
 * �X�L�����j�b�g�̔����C�x���g(�^�C�}�[����)
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

	// �Ώۂ��z�o�[�����O��Ԃ̏ꍇ�͈ꕔ����
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

	// ���Ԑ؂�ԍۂ͔��������Ȃ��悤�ɂ��邩����
	if(battle_config.skill_unit_interval_limit && ((sg->limit > 0 && DIFF_TICK(tick,sg->tick) >= sg->limit) || (src->limit > 0 && DIFF_TICK(tick,sg->tick) >= src->limit))) {
		return 0;
	}

	// �O�ɉe�����󂯂Ă���interval�̊Ԃ͉e�����󂯂Ȃ�
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
		diff += 500; // �V�K�ɉ񕜂������j�b�g�����J�E���g���邽�߂̎d�|��
	}

	if(diff < 0) {
		if(sg->skill_id == WZ_STORMGUST && status_get_mode(bl)&MD_BOSS) {
			// �{�X�����ɂ̓X�g�[���K�X�g��3HIT����2HIT�̃_���[�W���d�Ȃ�
			if(!sc || sc->data[SC_FREEZE].val3 != 3)
				return 0;
		} else {
			return 0;
		}
	}

	tickset_tick = tick + sg->interval;

	// GX�͏d�Ȃ��Ă�����3HIT���Ȃ�
	if(sg->skill_id == CR_GRANDCROSS && !battle_config.gx_allhit) {
		int count = map_count_oncell(bl->m,bl->x,bl->y,BL_PC|BL_MOB);
		if(count > 0)
			tickset_tick += sg->interval * (count-1);
	}
	linkdb_replace( node, INT2PTR(tickset_id), UINT2PTR(tickset_tick) );

	switch (sg->unit_id) {
	case UNT_PNEUMA:	/* �j���[�} */
		status_change_start(bl,SC_PNEUMA,sg->skill_lv,src->bl.id,0,0,sg->interval+100,0);
		break;
	case UNT_WARP_ACTIVE:	/* ���[�v�|�[�^��(������) */
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
	case UNT_SANCTUARY:	/* �T���N�`���A�� */
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
					sg->val1 = sg->val1-2;	// �`���b�g�L�����Z���ɑΉ�
			} else {
				int heal;
				if (status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				heal = sg->val2;
				if(sc) {
					if(sc->data[SC_CRITICALWOUND].timer != -1)
						heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
					if(sc->data[SC_DEATHHURT].timer != -1)	/* �f�X�n�[�g */
						heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
					if(sc->data[SC_BERSERK].timer != -1) /* �o�[�T�[�N���̓q�[���O */
						heal = 0;
				}
				if(bl->type == BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
					heal = 0;	/* ����峃J�[�h�i�q�[���ʂO�j */

				clif_skill_nodamage(&src->bl,bl,AL_HEAL,heal,1);
				battle_heal(NULL,bl,heal,0,0);
				if (diff >= 500)
					sg->val1--;	// �V�K�ɓ��������j�b�g�����J�E���g
			}
			if (sg->val1 <= 0)
				skill_delunitgroup(sg);
		}
		break;
	case UNT_MAGNUS:	/* �}�O�k�X�G�N�\�V�Y�� */
		{
			int race = status_get_race(bl);
			if (!battle_check_undead(race,status_get_elem_type(bl)) && race != RCT_DEMON)
				return 0;
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			src->val2++;
		}
		break;
	case UNT_FIREWALL:		/* �t�@�C�A�[�E�H�[�� */
	case UNT_FLAMECROSS:	/* �t���C���N���X */
		do {
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_ATTACK_SKILLS:	/* �U���n�X�L���S�� */
		switch(sg->skill_id) {
		case GS_DESPERADO:	/* �f�X�y���[�h */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2|0x0500);
			break;
		case GN_CRAZYWEED_ATK:	/* �N���C�W�[�E�B�[�h */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
			break;
		case SG_SUN_WARM:	/* ������ */
		case SG_MOON_WARM:	/* ������ */
		case SG_STAR_WARM:	/* ������ */
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
		case WL_COMET:				/* �R���b�g */
		case NPC_COMET:				/* M�R���b�g */
			{
				struct skill_unit *su = (struct skill_unit *)(sg->unit);
				if(su) {
					int dist = path_distance(bl->x,bl->y,su->bl.x,su->bl.y);
					clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,(dist > 7)? 3: (dist > 5)? 2: (dist > 3)? 1: 0);
				}
			}
			break;
		case AG_VIOLENT_QUAKE_ATK:		/* �o�C�I�����g�N�G�C�N(�U��) */
		case AG_ALL_BLOOM_ATK:			/* �I�[���u���[��(�U��) */
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val1);
			break;
		case SKE_STAR_BURST:			/* �V������ */
		case SS_KUNAIKAITEN:			/* �ꖳ -��]- */
		case SS_KUNAIKUSSETSU:			/* �ꖳ -����- */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			break;
		default:
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_EARTHSTRAIN:	/* �A�[�X�X�g���C�� */
	case UNT_PSYCHIC_WAVE:	/* �T�C�L�b�N�E�F�[�u */
	case UNT_CLOUD_KILL:	/* �N���E�h�L�� */
	case UNT_POISON_MIST:	/* �|�C�Y���~�X�g */
	case UNT_RAIN_OF_CRYSTAL:	/* ���C���I�u�N���X�^�� */
	case UNT_MYSTERY_ILLUSION:	/* �~�X�e���[�C�����[�W���� */
	case UNT_STRANTUM_TREMOR:	/* �X�g���^���g���}�[ */
	case UNT_TORNADO_STORM:		/* �g���l�[�h�X�g�[�� */
	case UNT_FLORAL_FLARE_ROAD:	/* �t���[�����t���A���[�h */
	case UNT_CROSS_RAIN:	/* �N���X���C�� */
	case UNT_PNEUMATICUS_PROCELLA:	/* �j���[�}�e�B�b�N�v���Z�� */
	case UNT_LIGHTNING_LAND:	/* ���C�g�j���O�����h */
	case UNT_VENOM_SWAMP:		/* �x�i���X�����v */
	case UNT_CONFLAGRATION:		/* �R���t���O���[�V���� */
	case UNT_HYUN_ROKS_BREEZE:	/* �f�B�A�[�u���[�Y */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_FIREPILLAR_WAITING:	/* �t�@�C�A�[�s���[(�����O) */
		skill_unitsetting(ss,sg->skill_id,sg->skill_lv,src->bl.x,src->bl.y,1);
		skill_delunit(src);
		break;
	case UNT_FIREPILLAR_ACTIVE:	/* �t�@�C�A�[�s���[(������) */
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
	case UNT_SKIDTRAP:	/* �X�L�b�h�g���b�v */
		{
			// 㩐ݒu���̃L�����̍��W�ƃ^�[�Q�b�g�̈ʒu�֌W�Ŕ�ԕ��������߂�
			int xs = sg->val1, ys = sg->val2, dir;
			int count = skill_get_blewcount(sg->skill_id,sg->skill_lv);
			if( (bl->x == src->bl.x && bl->y == src->bl.y) || (bl->x == xs && bl->y == ys) ) {
				dir = 6;	// 㩂̒��ォ�ݒu���̈ʒu�ɋ���Ȃ�^���ɔ��
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
	case UNT_LANDMINE:	/* �����h�}�C�� */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick)+1500;
		break;

	case UNT_BLASTMINE:	/* �u���X�g�}�C�� */
	case UNT_SHOCKWAVE:	/* �V���b�N�E�F�[�u�g���b�v */
	case UNT_SANDMAN:	/* �T���h�}�� */
	case UNT_FLASHER:	/* �t���b�V���[ */
	case UNT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
	case UNT_CLAYMORETRAP:	/* �N���C���A�g���b�v */
	case UNT_MAGENTATRAP:		/* �}�[���^�g���b�v */
	case UNT_COBALTTRAP:		/* �R�o���g�g���b�v */
	case UNT_MAIZETRAP:			/* ���C�Y�g���b�v */
	case UNT_VERDURETRAP:		/* ���F���f���[���g���b�v */
	case UNT_FIRINGTRAP:		/* �t�@�C�A�����O�g���b�v */
	case UNT_ICEBOUNDTRAP:		/* �A�C�X�o�E���h�g���b�v */
		{
			int splash_count = 0;
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
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

	case UNT_ANKLESNARE:	/* �A���N���X�l�A */
		{
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if (sg->val2 == 0 && (!sc || sc->data[type].timer == -1)) {
				int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
				if(status_get_mode(bl)&MD_BOSS)
					sec /= 5;
				// �Œ�S�����ԕ⏞�i����eA�̂��̂��Ƃ肠�����̗p�j
				if(sec < 3000 + 30 * sg->skill_lv)
					sec = 3000 + 30 * sg->skill_lv;
				status_change_start(bl,type,sg->skill_lv,sg->bl.id,0,0,sec,0);
				// �{���Ȃ�{�X�����Ȃ�z���񂹂��Ȃ����Askill_delunitgroup() ���̏����Ə�肭�܂荇�����t���Ȃ��̂ŕۗ�
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
	case UNT_VENOMDUST:	/* �x�i���_�X�g */
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
	case UNT_DEMONSTRATION:	/* �f�����X�g���[�V���� */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(bl->type == BL_PC && atn_rand()%100 < sg->skill_lv)
			pc_break_equip((struct map_session_data *)bl, LOC_RARM);
		break;
	case UNT_TALKIEBOX:				/* �g�[�L�[�{�b�N�X */
		if(sg->src_id == bl->id) // ����������ł��������Ȃ�
			break;
		if(sg->val2 == 0) {
			clif_talkiebox(&src->bl,sg->valstr);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 5000;
			sg->val2  = -1; // ����
		}
		break;
	case UNT_GOSPEL:	/* �S�X�y�� */
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
			if (battle_check_target(&src->bl,bl,BCT_PARTY) > 0) {	// ����(PT)�Ώ�
				int type = 0;
				switch(atn_rand()%13) {
				case 0:		// HP����(1000�`9999�H)
					battle_heal(NULL,bl,1000+atn_rand()%9000,0,0);
					break;
				case 1:		// MHP��100%����(��������60�b)
					status_change_start(bl,SC_INCMHP2,100,0,0,0,60000,0);
					type = 0x17;
					break;
				case 2:		// MSP��100%����(��������60�b)
					status_change_start(bl,SC_INCMSP2,100,0,0,0,60000,0);
					type = 0x18;
					break;
				case 3:		// �S�ẴX�e�[�^�X+20(��������60�b)
					status_change_start(bl,SC_INCALLSTATUS,20,0,0,0,60000,0);
					type = 0x19;
					break;
				case 4:		// �u���b�V���OLv10���ʕt�^
					status_change_start(bl,SC_BLESSING,10,0,0,0,skill_get_time(AL_BLESSING,10),0);
					break;
				case 5:		// ���x����Lv10���ʕt�^
					status_change_start(bl,SC_INCREASEAGI,10,0,0,0,skill_get_time(AL_INCAGI,10),0);
					break;
				case 6:		// ����ɐ��������ʕt�^
					status_change_start(bl,SC_ASPERSIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1c;
					break;
				case 7:		// �Z�ɐ��������ʕt�^
					status_change_start(bl,SC_BENEDICTIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1d;
					break;
				case 8:		// ATK��100%����
					status_change_start(bl,SC_INCATK2,100,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1f;
					break;
				case 9:		// HIT, FLEE��+50(��������60�b)
					status_change_start(bl,SC_INCHIT,50,0,0,0,60000,0);
					status_change_start(bl,SC_INCFLEE,50,0,0,0,60000,0);
					type = 0x20;
					break;
				case 10:	// �S�Ă̏�Ԉُ������
					status_change_release(bl,0x08);
					type = 0x15;
					break;
				case 11:	// �S��Ԉُ�̑ϐ�(��������60�b)
					status_change_start(bl,SC_STATUS_UNCHANGE,0,0,0,0,60000,0);
					type = 0x16;
					break;
				case 12:	// �h��͑���(��������10�b)
					status_change_start(bl,SC_INCDAMAGE,-50,0,0,0,10000,0);
					type = 0x1e;
					break;
				}
				if(type > 0 && sd)
					clif_gospel_message(sd,type);
			}
			else if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS)) {	// �G�ΏۂŃ{�X�ȊO
				switch(atn_rand()%8) {
				case 0:		// �����_���_���[�W(1000�`9999�H)
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
					break;
				case 1:		// �􂢌��ʕt�^
					if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_CURSE,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 2:		// �Í����ʕt�^
					if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_BLIND,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 3:		// �Ō��ʕt�^
					if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 4:		// �v���{�b�NLv10���ʕt�^
					status_change_start(bl,SC_PROVOKE,10,0,0,0,skill_get_time(SM_PROVOKE,10),0);
					break;
				case 5:		// ATK��0�Ɍ���(��������20�b)
					status_change_start(bl,SC_INCATK2,-100,0,0,0,20000,0);
					break;
				case 6:		// FLEE��0�Ɍ���(��������20�b)
					status_change_start(bl,SC_INCFLEE2,-100,0,0,0,20000,0);
					break;
				case 7:		// HIT��0�Ɍ���(��������50�b)
					status_change_start(bl,SC_INCHIT2,-100,0,0,0,50000,0);
					break;
				}
			}
		}
		break;
	case UNT_BASILICA:	/* �o�W���J */
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
	case UNT_SPIDERWEB:	/* �X�p�C�_�[�E�F�u */
		if((!sc || sc->data[SC_SPIDERWEB].timer == -1) && sg->val2 == 0) {
			skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
			unit_movepos(bl, src->bl.x, src->bl.y, 0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + skill_get_time2(sg->skill_id,sg->skill_lv);
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_MOONLIT: 	/* ������̉��� */
		if(!(bl->type & (BL_MOB | BL_PC)))
			break;
		if (sg->src_id == bl->id)
			break;
		// ����
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
		if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)		// �G�Ώ�
		{
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		//	unit_fixdamage(&src->bl,bl,0, 0, 0,sg->skill_lv*200+200,1, 4, 0, 0);
		}
		break;
	case UNT_TATAMIGAESHI:	/* ���Ԃ� */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
		break;
	case UNT_KAEN:	/* �Ή��w */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(--src->val1 <= 0)
			skill_delunit(src);
		break;
	case UNT_GROUNDDRIFT_WIND:	/* �O���E���h�h���t�g */
	case UNT_GROUNDDRIFT_DARK:
	case UNT_GROUNDDRIFT_POISON:
	case UNT_GROUNDDRIFT_WATER:
	case UNT_GROUNDDRIFT_FIRE:
	case UNT_GROUNDDRIFT_NEUTRAL:
#ifdef PRE_RENEWAL
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
#else
		int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
		map_foreachinarea(skill_trap_splash,src->bl.m,
					src->bl.x-ar,src->bl.y-ar,
					src->bl.x+ar,src->bl.y+ar,
					(BL_CHAR|BL_SKILL),src,tick,1);
#endif
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick) + 1500;
		break;
	case UNT_EVILLAND:	/* �C�[�r�������h */
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
	case UNT_POISONSMOKE:	/* �|�C�Y���X���[�N */
		if(atn_rand() % 10000 < status_change_rate(bl,sg->val1,5000,status_get_lv(&src->bl)))
			status_change_start(bl,sg->val1,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_EPICLESIS:	/* �G�s�N���V�X */
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
		skill_detect(bl);		// �f�B�e�B�N�g����
		break;
	case UNT_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
		{
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
			unit_movepos(bl, src->bl.x, src->bl.y, 0);		// ���񂾑Ώێ҂݈̂ړ�
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			//clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_CLUSTERBOMB:		/* �N���X�^�[�{�� */
		// ���ʔ͈�(�ݒu�֎~�̈�)�ł͂Ȃ�㩏�ɏd�Ȃ����甭��
		if(src->bl.m == bl->m && src->bl.x == bl->x && src->bl.y == bl->y){
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 1000;
		}
		break;
	case UNT_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
		if(sg->skill_id == NC_MAGMA_ERUPTION)
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		else
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NPC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		break;
	case UNT_MANHOLE:	/* �}���z�[�� */
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
	case UNT_DIMENSIONDOOR:	/* �f�B�����V�����h�A */
		if(bl->type == BL_PC)
			pc_randomwarp((struct map_session_data *)bl,3);
		else if(bl->type == BL_MOB)
			mob_warp((struct mob_data *)bl,-1,-1,-1,3);
		break;
	case UNT_CHAOSPANIC:	/* �J�I�X�p�j�b�N */
		if(sc && sc->data[SC_CONFUSION].timer == -1)
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
		break;
	case UNT_SEVERE_RAINSTORM:	/* �V�r�A���C���X�g�[�� */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,WM_SEVERE_RAINSTORM_MELEE,sg->skill_lv,tick,0);
		break;
	case UNT_REVERBERATION:		/* �U���c�� */
		{
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
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
	case UNT_POEMOFNETHERWORLD:	/* �n���̉� */
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
	case UNT_FIREWALK:		/* �t�@�C�A�[�E�H�[�N */
	case UNT_ELECTRICWALK:	/* �G���N�g���b�N�E�H�[�N */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(--src->val1 <= 0)
			skill_delunit(src);
		break;
	case UNT_WARMER:	/* �E�H�[�}�[ */
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
		status_change_end(bl,SC_DIAMONDDUST,-1);// �Ⓚ
		status_change_end(bl,SC_FREEZE,-1);		// ����
		status_change_end(bl,SC_FROSTMISTY,-1);	// �X��
		break;
	case UNT_VACUUM_EXTREME:	/* �o�L���[���G�N�X�g���[�� */
		{
			int sec = skill_get_time(sg->skill_id,sg->skill_lv) - status_get_str(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			// �Œ�S�����ԕ⏞
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			if(!(status_get_mode(bl)&MD_BOSS) && !map[bl->m].flag.gvg && bl->x != src->bl.x && bl->y != src->bl.y)
				unit_movepos(bl, src->bl.x, src->bl.y, 0);
			//sg->limit=DIFF_TICK(tick,sg->tick)+sec;
		}
		break;
	case UNT_THORNS_TRAP:		/* �\�[���g���b�v */
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
	case UNT_WALLOFTHORN:	/* �\�[���E�H�[�� */
		if(!(status_get_mode(bl)&MD_BOSS))
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_DEMONIC_FIRE:	/* �f���j�b�N�t�@�C�A�[ */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2);
		break;
	case UNT_FIRE_EXPANSION_SMOKE_POWDER:	/* �t�@�C�A�[�G�N�X�p���V����(����) */
		if(sc && sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv),0);
		break;
	case UNT_FIRE_EXPANSION_TEAR_GAS:		/* �t�@�C�A�[�G�N�X�p���V����(�×܃K�X) */
		if(sc && sc->data[SC_FIRE_EXPANSION_TEAR_GAS].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv),0);
		break;
	case UNT_HELLS_PLANT:	/* �w���Y�v�����g */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,GN_HELLS_PLANT_ATK,sg->skill_lv,tick,0);
		skill_delunit(src);
		break;
	case UNT_FIRE_MANTLE:	/* �t�@�C�A�[�}���g�� */
		do {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_MAKIBISHI:	/* �T�H */
		unit_fixdamage(ss,bl,tick,0,status_get_dmotion(bl),20*sg->skill_lv,0,0,0,0);
		skill_delunit(src);
		break;
	case UNT_ZENKAI_WATER:	/* �p���S�J(������) */
	case UNT_ZENKAI_GROUND:	/* �p���S�J(�n����) */
	case UNT_ZENKAI_FIRE:	/* �p���S�J(�Α���) */
	case UNT_ZENKAI_WIND:	/* �p���S�J(������) */
		// �G�Ȃ烆�j�b�g�ɉ����ď�Ԉُ��t�^����
		if( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 ) {
			switch(sg->unit_id) {
				case UNT_ZENKAI_WATER:	/* �p���S�J(������) */
					switch(atn_rand()%3) {
					case 0:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_FREEZE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// �X��
						status_change_pretimer(bl,SC_FROSTMISTY,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// �Ⓚ
						status_change_pretimer(bl,SC_DIAMONDDUST,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_GROUND:	/* �p���S�J(�n����) */
					switch(atn_rand()%2) {
					case 0:	// �Ή�
						if(atn_rand() % 10000 < status_change_rate(bl,SC_STONE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_STONE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// ��
						if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_FIRE:	/* �p���S�J(�Α���) */
					// ����
					status_change_pretimer(bl,SC_HELLINFERNO,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
					break;
				case UNT_ZENKAI_WIND:	/* �p���S�J(������) */
					switch(atn_rand()%3) {
					case 0:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SILENCE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// ����
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// �[������
						status_change_pretimer(bl,SC_DEEP_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
			}
		}
		break;
	case UNT_B_TRAP:		/* �o�C���h�g���b�v */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_FIRE_RAIN:		/* �t�@�C�A�[���C�� */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		break;
	case UNT_CATNIPPOWDER:	/* �C�k�n�b�J�V�����[ */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		break;
	case UNT_NYANGGRASS:	/* �j�����O���X */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_NYANGGRASS].timer == -1)
				status_change_start(bl,SC_NYANGGRASS,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_VENOMFOG:	/* �x�i���t�H�O */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,NPC_VENOMFOG,sg->skill_lv,tick,0);
		} else if(bl->type == BL_MOB) {
			if(status_get_hp(bl) < status_get_max_hp(bl)) {
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,sg->val1*sg->skill_lv,1);
				battle_heal(NULL,bl,sg->val1*sg->skill_lv,0,0);
			}
		}
		break;
	case UNT_CANE_OF_EVIL_EYE:		/* �P�[���I�u�C�r���A�C */
		// ����_���[�W���o�Ȃ��H
		if(sg->val2 == 1 && battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,NPC_CANE_OF_EVIL_EYE,sg->skill_lv,tick,0x500);
		sg->val2 = 1;
 		break;
	case UNT_LAVA_SLIDE:			/* ���[���@�X���C�h */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,MH_LAVA_SLIDE,sg->skill_lv,tick,0);
		if(--sg->val2 <= 0)
			skill_delunitgroup(sg);
		break;
	case UNT_VOLCANIC_ASH:		/* �{���J�j�b�N�A�b�V�� */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_VOLCANIC_ASH].timer == -1)
				status_change_start(bl,SC_VOLCANIC_ASH,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_CREATINGSTAR:	/* �n���̏� */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		status_change_start(bl,SC_CREATINGSTAR,sg->skill_lv,0,0,0,sg->interval+100,0);
		break;
	case UNT_VIOLENT_QUAKE:	/* �o�C�I�����g�N�G�C�N */
	case UNT_ALL_BLOOM:		/* �I�[���u���[�� */
		if(sg->val1 == 4) {		// �N���C�}�b�N�XLv4�F�����͈͓��̓G����Ԉُ�
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_ASTRAL_STRIKE:		/* �A�X�g�����X�g���C�N */
		if(DIFF_TICK(tick,sg->tick) >= 500) {	// �ݒu����͍U���Ȃ�
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_ABYSS_SQUARE:		/* �A�r�X�X�N�G�A */
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
	case UNT_DEEPBLIND_TRAP:	/* �f�B�[�v�u���C���h�g���b�v */
	case UNT_SOLID_TRAP:		/* �\���b�h�g���b�v */
	case UNT_SWIFT_TRAP:		/* �X�C�t�g�g���b�v */
	case UNT_FLAME_TRAP:		/* �t���C���g���b�v */
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer != -1)
			break;
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_ACIDIFIED_ZONE_WATER:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case UNT_ACIDIFIED_ZONE_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(�n) */
	case UNT_ACIDIFIED_ZONE_WIND:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case UNT_ACIDIFIED_ZONE_FIRE:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
	case UNT_FUUMASHOUAKU:				/* �����藠�� -����- */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_TOTEM_OF_TUTELARY:			/* ��褓� */
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
	case UNT_JACK_FROST_NOVA:		/* �W���b�N�t���X�g�m���@ */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,1);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_GROUND_GRAVITATION:	/* �O���E���h�O���r�e�[�V���� */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,2);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	}

	if(bl->type == BL_MOB && ss != bl)	/* �X�L���g�p������MOB�X�L�� */
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
 * �X�L�����j�b�g���痣�E
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
		return 0; // ���G�^�C�}�[��

	switch(sg->unit_id){
	case UNT_SAFETYWALL:	/* �Z�C�t�e�B�E�H�[�� */
	case UNT_PNEUMA:	/* �j���[�} */
	case UNT_QUAGMIRE:	/* �N�@�O�}�C�A */
	case UNT_VOLCANO:	/* �{���P�[�m */
	case UNT_DELUGE:	/* �f�����[�W */
	case UNT_VIOLENTGALE:	/* �o�C�I�����g�Q�C�� */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (type==SC_QUAGMIRE && bl->type==BL_MOB)
			break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val2==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_SUITON:	/* ���� */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val2==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_ANKLESNARE:	/* �A���N���X�l�A */
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
	case UNT_LULLABY:	/* �q��S */
	case UNT_RICHMANKIM:	/* �j�����h�̉� */
	case UNT_ETERNALCHAOS:	/* �i���̍��� */
	case UNT_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case UNT_RINGNIBELUNGEN:	/* �j�[�x�����O�̎w�� */
	case UNT_ROKISWEIL:	/* ���L�̋��� */
	case UNT_INTOABYSS:	/* �[���̒��� */
	case UNT_SIEGFRIED:	/* �s���g�̃W�[�N�t���[�h */
	case UNT_DISSONANCE:	/* �s���a�� */
	case UNT_WHISTLE:	/* ���J */
	case UNT_ASSASSINCROSS:	/* �[�z�̃A�T�V���N���X */
	case UNT_POEMBRAGI:	/* �u���M�̎� */
	case UNT_APPLEIDUN:	/* �C�h�D���̗ь� */
	case UNT_UGLYDANCE:	/* ��������ȃ_���X */
	case UNT_HUMMING:	/* �n�~���O */
	case UNT_FORTUNEKISS:	/* �K�^�̃L�X */
	case UNT_SERVICEFORYOU:	/* �T�[�r�X�t�H�[���[ */
	case UNT_DONTFORGETME:	/* ����Y��Ȃ��Łc */
	case UNT_BASILICA:	/* �o�W���J */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer!=-1 && sc->data[type].val4==src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_FOGWALL:	/* �E�H�[���I�u�t�H�O */
		sc = status_get_sc(bl);
		if(sc){
			if(sc->data[SC_FOGWALL].timer!=-1 && !(status_get_mode(bl)&MD_BOSS))	// �{�X����MOB�͌��ʎ��Ԓ�����
				status_change_end(bl,SC_FOGWALL,-1);
			// PC�Ȃ���ʏ�����
			if(bl->type==BL_PC && sc->data[SC_FOGWALLPENALTY].timer!=-1)
				status_change_end(bl,SC_FOGWALLPENALTY,-1);
		}
		break;
	case UNT_MOONLIT: 	/* ������̉��� */
		break;
	case UNT_SPIDERWEB:	/* �X�p�C�_�[�E�F�u */
		{
			struct block_list *target = map_id2bl(sg->val2);
			if (target && target==bl)
				status_change_end(bl,SC_SPIDERWEB,-1);
			sg->limit = DIFF_TICK(tick,sg->tick)+1000;
			break;
		}

	case UNT_GRAVITATION:	/* �O���r�e�[�V�����t�B�[���h */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_GRAVITATION].timer!=-1)
			status_change_end(bl,SC_GRAVITATION,-1);
		break;
	case UNT_HERMODE:	/* �w�����[�h�̏� */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_HERMODE].timer!=-1)
			status_change_end(bl,SC_HERMODE,-1);
		break;
	case UNT_EPICLESIS:		/* �G�s�N���V�X */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_EPICLESIS].timer != -1)
			status_change_end(bl,SC_EPICLESIS,-1);
		break;
	case UNT_NEUTRALBARRIER:	/* �j���[�g�����o���A�[ */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_NEUTRALBARRIER].timer != -1)
			status_change_end(bl,SC_NEUTRALBARRIER,-1);
		break;
	case UNT_STEALTHFIELD:		/* �X�e���X�t�B�[���h */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_STEALTHFIELD].timer != -1)
			status_change_end(bl,SC_STEALTHFIELD,-1);
		break;
	case UNT_KINGS_GRACE:	/* �L���O�X�O���C�X */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_KINGS_GRACE].timer != -1)
			status_change_end(bl,SC_KINGS_GRACE,-1);
		break;
	case UNT_BLOODYLUST:	/* �u���b�f�B���X�g */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_BERSERK].timer != -1)
			status_change_end(bl,SC_BERSERK,-1);
		break;
	case UNT_WARMER:		/* �E�H�[�}�[ */
		sc = status_get_sc(bl);
		if (sc && sc->data[SC_WARMER].timer != -1)
			status_change_end(bl,SC_WARMER,-1);
		break;
	case UNT_THORNS_TRAP:	/* �\�[���g���b�v */
		{
			struct block_list *target = map_id2bl(sg->val2);
			if (target && target == bl)
				status_change_end(bl,SC_THORNS_TRAP,-1);
			sg->limit = DIFF_TICK(tick,sg->tick)+1000;
		}
		break;
	case UNT_ZENKAI_WATER:	/* �p���S�J(������) */
	case UNT_ZENKAI_GROUND:	/* �p���S�J(�n����) */
	case UNT_ZENKAI_FIRE:	/* �p���S�J(�Α���) */
	case UNT_ZENKAI_WIND:	/* �p���S�J(������) */
		sc = status_get_sc(bl);
		type = GetSkillStatusChangeTable(sg->skill_id);
		if( type == -1 ) break;
		if (sc && sc->data[type].timer != -1 && sc->data[type].val2 == src->bl.id) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_NYANGGRASS:	/* �j�����O���X */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_NYANGGRASS].timer != -1 && sc->data[SC_NYANGGRASS].val2 == src->bl.id)
			status_change_end(bl,SC_NYANGGRASS,-1);
		break;
	case UNT_CREATINGSTAR:	/* �n���̏� */
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
 * �X�L�����j�b�g���ʔ���/���E����(foreachinarea)
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
 * �X�L�����j�b�g�̌��E�C�x���g
 *------------------------------------------
 */
static int skill_unit_onlimit(struct skill_unit *src,unsigned int tick)
{
	struct skill_unit_group *sg;

	nullpo_retr(0, src);
	nullpo_retr(0, sg=src->group);

	switch(sg->unit_id){
	case UNT_ICEWALL:	/* �A�C�X�E�H�[�� */
		map_setcell(src->bl.m,src->bl.x,src->bl.y,src->val2);
		clif_changemapcell(src->bl.m,src->bl.x,src->bl.y,src->val2,1);
		break;
	case UNT_CALLFAMILY:
		{
			struct map_session_data *sd = map_id2sd(sg->src_id);
			if(sd == NULL)
				break;
			if(sg->skill_id == WE_CALLPARTNER) {		/* ���Ȃ��Ɉ������� */
				if(sd->status.partner_id)
					intif_charmovereq2(sd,map_charid2nick(sd->status.partner_id),map[src->bl.m].name,src->bl.x,src->bl.y,0);
			}
			else if(sg->skill_id == WE_CALLPARENT) {	/* �}�}�A�p�p�A���� */
				if(sd->status.parent_id[0] && sd->status.parent_id[1]) {
					intif_charmovereq2(sd,map_charid2nick(sd->status.parent_id[0]),map[src->bl.m].name,src->bl.x,src->bl.y,2);
					intif_charmovereq2(sd,map_charid2nick(sd->status.parent_id[1]),map[src->bl.m].name,src->bl.x,src->bl.y,2);
				}
			}
			else if(sg->skill_id == WE_CALLBABY) {		/* �V��A��������Ⴂ */
				if(sd->status.baby_id)
					intif_charmovereq2(sd,map_charid2nick(sd->status.baby_id),map[src->bl.m].name,src->bl.x,src->bl.y,2);
			}
		}
		break;
	}
	return 0;
}

/*==========================================
 * �X�L�����j�b�g�̃_���[�W�C�x���g
 *------------------------------------------
 */
int skill_unit_ondamaged(struct skill_unit *src,struct block_list *bl,int damage,unsigned int tick)
{
	struct skill_unit_group *sg;

	nullpo_retr(0, src);
	nullpo_retr(0, sg = src->group);

	switch(sg->unit_id) {
	case UNT_FIREPILLAR_WAITING:	/* �t�@�C�A�[�s���[(�����O) */
	case UNT_ICEWALL:		/* �A�C�X�E�H�[�� */
	case UNT_SKIDTRAP:		/* �X�L�b�h�g���b�v */
	case UNT_LANDMINE:		/* �����h�}�C�� */
	case UNT_SHOCKWAVE:		/* �V���b�N�E�F�[�u�g���b�v */
	case UNT_SANDMAN:		/* �T���h�}�� */
	case UNT_FLASHER:		/* �t���b�V���[ */
	case UNT_FREEZINGTRAP:		/* �t���[�W���O�g���b�v */
	case UNT_TALKIEBOX:		/* �g�[�L�[�{�b�N�X */
	case UNT_ANKLESNARE:		/* �A���N���X�l�A */
	case UNT_WALLOFTHORN:	/* �\�[���E�H�[�� */
		src->val1 -= damage;
		break;
	case UNT_BLASTMINE:		/* �u���X�g�}�C�� */
		if(bl == NULL) {
			damage = 0;
			break;
		}
		skill_blown(bl,&src->bl,2);	// ������΂��Ă݂�
		break;
	case UNT_REVERBERATION:	/* �U���c�� */
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
 * �͈͓��L�������݊m�F���菈��(foreachinarea)
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

	// �`�F�b�N���Ȃ��ݒ�Ȃ�c�ɂ��肦�Ȃ��傫�Ȑ�����Ԃ��ďI��
	// �{����foreach�̑O�ɂ�肽�����ǐݒ�K�p�ӏ����܂Ƃ߂邽�߂ɂ�����
	if(!battle_config.player_skill_partner_check) {
		(*c) = 0x7fffffff;
		return 0;
	}

	if(sd == ssd)
		return 0;

	sp = skill_get_sp(cnd->id,cnd->lv);

	switch(cnd->id){
	case PR_BENEDICTIO:		/* ���̍~�� */
		if( (*c) < 2 &&
		    (sd->s_class.job == PC_JOB_AL || sd->s_class.job == PC_JOB_PR || sd->s_class.job == PC_JOB_MO ||
		     sd->s_class.job == PC_JOB_AB || sd->s_class.job == PC_JOB_SR) &&
		    (sd->bl.y == ssd->bl.y && (sd->bl.x == ssd->bl.x-1 || sd->bl.x == ssd->bl.x+1)) &&
		    sd->status.sp >= sp/2 )
			(*c)++;
		break;
	case BD_LULLABY:		/* �q��� */
	case BD_RICHMANKIM:		/* �j�����h�̉� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:		/* ���L�̋��� */
	case BD_INTOABYSS:		/* �[���̒��� */
	case BD_SIEGFRIED:		/* �s���g�̃W�[�N�t���[�h */
	case BD_RAGNAROK:		/* �_�X�̉��� */
	case CG_MOONLIT:		/* ������̉��� */
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
	case WM_GREAT_ECHO:					/* �O���[�g�G�R�[ */
	case WM_SONG_OF_MANA:				/* �}�i�̉� */
	case WM_DANCE_WITH_WUG:				/* �_���X�E�B�Y�E�H�[�O */
	case WM_SOUND_OF_DESTRUCTION:		/* �T�E���h�I�u�f�B�X�g���N�V���� */
	case WM_SATURDAY_NIGHT_FEVER:		/* �t���C�f�[�i�C�g�t�B�[�o�[ */
	case WM_LERADS_DEW:					/* ���[���Y�̖� */
	case WM_MELODYOFSINK:				/* �����f�B�[�I�u�V���N */
	case WM_BEYOND_OF_WARCRY:			/* �r�����h�I�u�E�H�[�N���C */
	case WM_UNLIMITED_HUMMING_VOICE:	/* �G���h���X�n�~���O�{�C�X */
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
 * �͈͓��L�������݊m�F�����X�L���g�p����(foreachinarea)
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

	// �`�F�b�N���Ȃ��ݒ�Ȃ�c�ɂ��肦�Ȃ��傫�Ȑ�����Ԃ��ďI��
	// �{����foreach�̑O�ɂ�肽�����ǐݒ�K�p�ӏ����܂Ƃ߂邽�߂ɂ�����
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
	case PR_BENEDICTIO:		/* ���̍~�� */
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
	case BD_LULLABY:		/* �q��� */
	case BD_RICHMANKIM:		/* �j�����h�̉� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:		/* ���L�̋��� */
	case BD_INTOABYSS:		/* �[���̒��� */
	case BD_SIEGFRIED:		/* �s���g�̃W�[�N�t���[�h */
	case BD_RAGNAROK:		/* �_�X�̉��� */
	case CG_MOONLIT:		/* ������̉��� */
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
	case WM_GREAT_ECHO:					/* �O���[�g�G�R�[ */
	case WM_SONG_OF_MANA:				/* �}�i�̉� */
	case WM_DANCE_WITH_WUG:				/* �_���X�E�B�Y�E�H�[�O */
	case WM_SOUND_OF_DESTRUCTION:		/* �T�E���h�I�u�f�B�X�g���N�V���� */
	case WM_SATURDAY_NIGHT_FEVER:		/* �t���C�f�[�i�C�g�t�B�[�o�[ */
	case WM_LERADS_DEW:					/* ���[���Y�̖� */
	case WM_MELODYOFSINK:				/* �����f�B�[�I�u�V���N */
	case WM_BEYOND_OF_WARCRY:			/* �r�����h�I�u�E�H�[�N���C */
	case WM_UNLIMITED_HUMMING_VOICE:	/* �G���h���X�n�~���O�{�C�X */
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
 * �͈͓��o�C�I�v�����g�A�X�t�B�A�}�C���pMob���݊m�F���菈��(foreachinarea)
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
 * �X�L���g�p�����i�U�Ŏg�p���s�j
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
	// skill_check_condition �����ŏ����������l��߂�
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
		// �X�L���Ώۂ�PC,MOB,HOM,MERC�̂�
		target = NULL;
	}

	sd        = BL_DOWNCAST( BL_PC, bl );
	target_sd = BL_DOWNCAST( BL_PC, target );

	sc = status_get_sc(bl);

	// PC, MOB, PET, HOM, MERC, ELEM ���ʂ̎��s�͂����ɋL�q

	// ��Ԉُ�֘A
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
			if(sc->data[SC_BLADESTOP].val2 == 1) return 0;	// ���H���ꂽ���Ȃ̂Ń_��
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

		/* ���t/�_���X�� */
		if(sc->data[SC_DANCING].timer != -1 && sc->data[SC_LONGINGFREEDOM].timer == -1)
		{
			if(sd && pc_checkskill(sd,WM_LESSON) >= 5 && cnd->id >= WA_SWING_DANCE && cnd->id <= WM_UNLIMITED_HUMMING_VOICE) {
				;
			}
			else {
				if(!battle_config.player_skill_partner_check &&
				   !(battle_config.sole_concert_type & 2) &&	// �P�ƍ��t���ɖ��/MS���ł��Ȃ��ݒ�
				   cnd->id != BD_ADAPTATION && cnd->id != CG_LONGINGFREEDOM)
				{
					switch (sc->data[SC_DANCING].val1)
					{
					case BD_LULLABY:			// �q���
					case BD_RICHMANKIM:			// �j�����h�̉�
					case BD_ETERNALCHAOS:		// �i���̍���
					case BD_DRUMBATTLEFIELD:	// �푾�ۂ̋���
					case BD_RINGNIBELUNGEN:		// �j�[�x�����O�̎w��
					case BD_ROKISWEIL:			// ���L�̋���
					case BD_INTOABYSS:			// �[���̒���
					case BD_SIEGFRIED:			// �s���g�̃W�[�N�t���[�h
					case BD_RAGNAROK:			// �_�X�̉���
					case CG_MOONLIT:			// ������̉���
						return 0;
					}
				}
				switch(cnd->id) {
				case BD_ADAPTATION:
				case BA_MUSICALSTRIKE:
				case DC_THROWARROW:
				case CG_LONGINGFREEDOM:
				case TR_RETROSPECTION:		// ��z
				case TR_MYSTIC_SYMPHONY:	// �~�X�e�B�b�N�V���t�H�j�[
				case TR_KVASIR_SONATA:		// �\�i�^�I�u�N���@�V��
				case TR_ROSEBLOSSOM:		// ���[�u���b�T��
				case TR_RHYTHMSHOOTING:		// ���Y���V���[�e�B���O
				case TR_METALIC_FURY:		// ���^���b�N�t���[���[
				case TR_SOUNDBLEND:			// �T�E���h�u�����h
				case TR_GEF_NOCTURN:		// �Q�t�F�j�A�m�N�^�[��
				case TR_ROKI_CAPRICCIO:		// ���L�̋C�܂���
				case TR_AIN_RHAPSODY:		// �z���̃��v�\�f�B
				case TR_MUSICAL_INTERLUDE:	// �~���[�W�J���C���^�[���[�h
				case TR_JAWAII_SERENADE:	// �[�Ă��̃Z���i�[�f
				case TR_NIPELHEIM_REQUIEM:	// ���҂����ւ̃��N�C�G��
				case TR_PRON_MARCH:			// �v�����e���}�[�`
					break;
				default:
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
	}

	// ���X�L�����ǂ����̔���
	if( cnd->id == SL_ALCHEMIST ||
	    (cnd->id >= SL_MONK && cnd->id <= SL_SOULLINKER && cnd->id != BS_ADRENALINE2) ||
	    cnd->id == SL_HIGH ||
	    (cnd->id >= SL_DEATHKNIGHT && cnd->id <= SL_GUNNER) )
	{
		int job, fail = 0;

		// ���؂Ɏ��Ԃ�������̂ŉ�n�łQ�v���C���[�����Ȃ��ꍇ�͈ꗥ�e��
		if(!sd || !target_sd)
			return 0;

		job = target_sd->s_class.job;

		switch(cnd->id)
		{
			case SL_ALCHEMIST:   if(pc_get_base_job(job,2) != PC_JOB_AM) fail = 1; break; // �A���P�~�X�g�̍�
			case SL_MONK:        if(pc_get_base_job(job,2) != PC_JOB_MO) fail = 1; break; // �����N�̍�
			case SL_STAR:        if(pc_get_base_job(job,2) != PC_JOB_SG) fail = 1; break; // �P���Z�C�̍�
			case SL_SAGE:        if(pc_get_base_job(job,2) != PC_JOB_SA) fail = 1; break; // �Z�[�W�̍�
			case SL_CRUSADER:    if(pc_get_base_job(job,2) != PC_JOB_CR) fail = 1; break; // �N���Z�C�_�[�̍�
			case SL_SUPERNOVICE: if(pc_get_base_job(job,1) != PC_JOB_SNV) fail = 1; break; // �X�[�p�[�m�[�r�X�̍�
			case SL_KNIGHT:      if(pc_get_base_job(job,2) != PC_JOB_KN) fail = 1; break; // �i�C�g�̍�
			case SL_WIZARD:      if(pc_get_base_job(job,2) != PC_JOB_WZ) fail = 1; break; // �E�B�U�[�h�̍�
			case SL_PRIEST:      if(pc_get_base_job(job,2) != PC_JOB_PR) fail = 1; break; // �v���[�X�g�̍�
			case SL_BARDDANCER:  if(pc_get_base_job(job,2) != PC_JOB_BA && pc_get_base_job(job,2) != PC_JOB_DC) fail = 1; break; // �o�[�h�ƃ_���T�[�̍�
			case SL_ROGUE:       if(pc_get_base_job(job,2) != PC_JOB_RG) fail = 1; break; // ���[�O�̍�
			case SL_ASSASIN:     if(pc_get_base_job(job,2) != PC_JOB_AS) fail = 1; break; // �A�T�V���̍�
			case SL_BLACKSMITH:  if(pc_get_base_job(job,2) != PC_JOB_BS) fail = 1; break; // �u���b�N�X�~�X�̍�
			case SL_HUNTER:      if(pc_get_base_job(job,2) != PC_JOB_HT) fail = 1; break; // �n���^�[�̍�
			case SL_SOULLINKER:  if(pc_get_base_job(job,2) != PC_JOB_SL) fail = 1; break; // �\�E�������J�[�̍�
			case SL_HIGH:        if(job < PC_JOB_SM || job > PC_JOB_TF || target_sd->s_class.upper != PC_UPPER_HIGH) fail = 1; break; // �]���ꎟ�E�Ƃ̍�
			default: fail = 1;
		}
		if(battle_config.job_soul_check && fail) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		// �ŏI����
		if(!battle_config.soulskill_can_be_used_for_myself && sd == target_sd)
		{
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,0))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,3000,0,gettick()+status_get_amotion(&sd->bl));
			return 0;
		}
	}

	// �X�L�����Ƃ̓��ꔻ��
	switch( cnd->id ) {
	case PR_TURNUNDEAD:			/* �^�[���A���f�b�h */
		if(!target)
			return 0;
		if(!battle_check_undead(status_get_race(target),status_get_elem_type(target)))
			return 0;
		break;
	case AM_POTIONPITCHER:		/* �|�[�V�����s�b�`���[ */
		if(target) {
			if(bl == target)	// �Ώۂ������Ȃ�OK
				break;
			if(target->type == BL_HOM) {
				struct homun_data *thd = (struct homun_data *)target;
				if(thd && thd->msd) {
					int pid;
					if(sd && sd == thd->msd)	// �����̃z����OK
						break;
					pid = status_get_party_id(bl);
					if(pid > 0 && pid == status_get_party_id(&thd->msd->bl))	// PTM�̃z����OK
						break;
				}
			} else {
				int pid, gid;
				pid = status_get_party_id(bl);
				if(pid > 0 && pid == status_get_party_id(target))	// ����PT��OK
					break;
				gid = status_get_guild_id(bl);
				if(gid > 0 && gid == status_get_guild_id(target))	// �����M���h��OK
					break;
				if(guild_check_alliance(gid,status_get_guild_id(target),0))	// �����M���h��OK
					break;
			}
		}
		if(sd)
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
		return 0;

	case MO_KITRANSLATION:	/* �C���]�� */
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
	case ALL_RESURRECTION:	/* ���U���N�V���� */
		if(!target)
			return 0;
		if(!unit_isdead(target) && !battle_check_undead(status_get_race(target),status_get_elem_type(target)))
			return 0;
		break;
	case HP_BASILICA:		/* �o�W���J */
		if(!type) {	// �r���J�n���̂݃`�F�b�N
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
	case HT_POWER:		/* �r�[�X�g�X�g���C�s���O */
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
	case NPC_DEATHSUMMON:		/* �f�X�T���� */
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
	case CR_PROVIDENCE:	// �v�����B�f���X
		if(!target_sd)
			return 0;
		if(target_sd->s_class.job == PC_JOB_CR || target_sd->s_class.job == PC_JOB_LG) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case HP_ASSUMPTIO:	// �A�X���v�e�B�I
	case CASH_ASSUMPTIO:	// �p�[�e�B�[�A�X���v�e�B�I
		if(map[bl->m].flag.gvg && !battle_config.allow_assumptop_in_gvg) {
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case CG_MARIONETTE:	// �}���I�l�b�g
		if(!sd || !target_sd)
			return 0;

		// ���Ɏ������ڑ����Ă�������Ȃ�~�߂�
		if(sc && sc->data[SC_MARIONETTE].timer != -1 && sc->data[SC_MARIONETTE].val2 == target_sd->bl.id) {
			status_change_end(bl,SC_MARIONETTE,-1);
			return 0;
		}

		// �����E�����N���X�E�}���I�l�b�g��ԂȂ玸�s
		if( sd == target_sd || sd->s_class.job == target_sd->s_class.job ||
		    sd->sc.data[SC_MARIONETTE].timer != -1 || sd->sc.data[SC_MARIONETTE2].timer != -1 ||
		    target_sd->sc.data[SC_MARIONETTE].timer != -1 || target_sd->sc.data[SC_MARIONETTE2].timer != -1)
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SR_POWERVELOCITY:	/* �S�C���� */
		if( !target_sd ||
		    bl == target ||
		    target_sd->status.class_ == PC_CLASS_GS )
		{
			if(sd)
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case WM_DEADHILLHERE:	/* �����̋��� */
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

// PC�p����( 0: �g�p���s 1: �g�p���� )
static int skill_check_condition2_pc(struct map_session_data *sd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,ap,hp_rate,sp_rate,ap_rate,zeny,weapon,state,spiritball,coin,skilldb_id,arrow;
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];
	int item_nocost = 0;
	int soulenergy = 0, servantweapon = 0;
    struct block_list *bl = NULL, *target = NULL;
    struct unit_data  *ud = NULL;
    struct status_change */*sc = NULL,*/ *tsc = NULL;

	nullpo_retr(0, sd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, bl = &sd->bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	target = map_id2bl( cnd->target );
    /* sc = status_get_sc(bl); */
	if(target != NULL) tsc = status_get_sc(target);

	// �`�F�C�X�A�n�C�h�A�N���[�L���O���̃X�L��
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

	if(pc_ischasewalk(sd) && cnd->id != ST_CHASEWALK)	// �`�F�C�X�E�H�[�N
	 	return 0;

	// �\�E�������J�[�Ŏg���Ȃ��X�L��
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
			case SL_KAIZEL:		/* �J�C�[�� */
			case SL_KAAHI:		/* �J�A�q */
			case SL_KAITE:		/* �J�C�g */
			case SL_KAUPE:		/* �J�E�v */
				if(target == NULL || target->type != BL_PC) {
					// �Ώۂ��l�ȊO���s
					clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
					return 0;
				}
				if(battle_config.soul_linker_battle_mode_ka == 0) {
					struct map_session_data *target_sd = (struct map_session_data *)target;
					if( target_sd->status.char_id == sd->status.char_id ||
					    target_sd->status.char_id == sd->status.partner_id ||
					    target_sd->status.char_id == sd->status.baby_id ||
					    sd->sc.data[SC_SOULLINKER].timer != -1 ) {
						;	// �������Ȃ�
					} else {
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
						return 0;
					}
				}
				break;
		}
	}

	// �E�H�[�O���C�_�[��
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
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MSGID,0x75e,0);	// �R�搶���ɋR�撆�́A�X�L���g�p���ł��܂���B
				return 0;
		}
	}

	// �����M�A���掞
	if(pc_isgear(sd)) {
		switch(cnd->id) {
		// �}�[�`�����g�n�X�L��
		case MC_IDENTIFY:			// �A�C�e���Ӓ�
		case MC_VENDING:			// �I�X�J��
		case MC_MAMMONITE:			// ���}�[�i�C�g
		// �u���b�N�X�~�X�n�X�L��
		case BS_REPAIRWEAPON:		// ����C��
		case BS_HAMMERFALL:			// �n���}�[�t�H�[��
		case BS_ADRENALINE:			// �A�h���i�������b�V��
		case BS_WEAPONPERFECT:		// �E�F�|���p�[�t�F�N�V����
		case BS_OVERTHRUST:			// �I�[�o�[�g���X�g
		case BS_MAXIMIZE:			// �}�L�V�}�C�Y�p���[
		case BS_ADRENALINE2:		// �t���A�h���i�������b�V��
		case BS_GREED:				// �O���[�h
		// �z���C�g�X�~�X�n�X�L��
		case WS_MELTDOWN:			// �����g�_�E��
		case WS_CARTBOOST:			// �J�[�g�u�[�X�g
		case WS_WEAPONREFINE:		// ���퐸�B
		case WS_CARTTERMINATION:	// �J�[�g�^�[�~�l�[�V����
		case WS_OVERTHRUSTMAX:		// �I�[�o�[�g���X�g�}�b�N�X
		// ���J�j�b�N�ǉ��X�L��
		case NC_MAGMA_ERUPTION:		//�}�O�}�C���v�V����
		// �}�C�X�^�[�ǉ��X�L��
		case MT_MIGHTY_SMASH:		// �}�C�e�B�X�}�b�V��
		// ���̑�
		case AL_TELEPORT:			// �e���|�[�g
		case ALL_BUYING_STORE:		// ����I�X�J��
			break;
		default:
			// ���J�j�b�N�X�L���͂܂Ƃ߂Ĕ���
			if(cnd->id >= NC_BOOSTKNUCKLE && cnd->id <= NC_DISJOINT)
				break;
			// �}�C�X�^�[�X�L���͂܂Ƃ߂Ĕ���
			if(cnd->id >= MT_AXE_STOMP && cnd->id <= MT_SUMMON_ABR_INFINITY)
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MADOGEAR_RIDE,0,0);
			return 0;
		}
	}

	// GM�n�C�h���ŁA�R���t�B�O�Ńn�C�h���U���s�� GM���x�����w����傫���ꍇ
	if(sd->sc.option&OPTION_SPECIALHIDING && battle_config.hide_attack == 0 && pc_isGM(sd) < battle_config.gm_hide_attack_lv)
		return 0;	// �B��ăX�L���g���Ȃ�Ĕڋ���GM�f�X�l

	if(battle_config.gm_skilluncond > 0 && pc_isGM(sd) >= battle_config.gm_skilluncond)
		return 1;
	// �_��-��-�͐�����Ԃł͎g���Ȃ�
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

	// �삯�����ɃX�L�����g�����ꍇ�I��
	// �ēx�̋삯������яR��͏��O
	if(sd->sc.data[SC_RUN].timer != -1 && cnd->id != TK_RUN && cnd->id != TK_JUMPKICK)
		status_change_end(bl,SC_RUN,-1);

	// �E�H�[�O�_�b�V�����̃X�L���g�p
	if(sd->sc.data[SC_WUGDASH].timer != -1 && cnd->id != RA_WUGDASH)
		status_change_end(bl,SC_WUGDASH,-1);

	/* �A�C�e���̏ꍇ�̔��� */
	if(sd->skill_item.id == cnd->id) {
		if(type == 0)			// ����̌Ăяo���iunit.c���j�Ȃ疳�����ŋ���
			return 1;
		sd->skill_item.id   = -1;
		sd->skill_item.lv   = -1;
		if( !sd->skill_item.flag )	// �t���O�Ȃ��Ȃ狖��
			return 1;
	}

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* ����HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* ����SP */
	ap         = skill_get_ap(cnd->id, cnd->lv);	/* ����AP */
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
	// �X�L��Lv���̏���A�C�e��
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

	if(sd->skill_used.id == BD_ENCORE && cnd->id == sd->skill_dance.id)	// �A���R�[������SP�������
		sp /= 2;
	if(sd->skill_used.id == TR_RETROSPECTION && cnd->id == sd->skill_4thdance.id)	// ��z����SP�������
		sp /= 2;
	if(sd->sc.data[SC_RECOGNIZEDSPELL].timer!=-1)		// ���S�O�i�C�Y�h�X�y�����͏���SP25%����
		sp = sp * 125 / 100;
	if(sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].timer != -1) {	// �G���h���X�n�~���O�{�C�X���͏���SP�`15%����
		int cost = 15;
		cost -= sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].val4 * 3;
		if(cost > 0)
			sp = sp * (100 + cost) / 100;
	}
	if(sd->sc.data[SC_HANDICAPSTATE_DEPRESSION].timer!=-1)		// �J�T���͏���SP3�{
		sp *= 3;
	if(sd->skill_addspcost.count > 0) {		// �J�[�h�ɂ��SP�g�p�ʑ���
		for(i=0; i<sd->skill_addspcost.count; i++) {
			if(cnd->id == sd->skill_addspcost.id[i])
				sp += sd->skill_addspcost.rate[i];
		}
	}

#ifndef PRE_RENEWAL
	if(spiritball > 0)
		sd->spiritball.old = 0;
#endif

	// �\�E�����[�p�[�̃X�L����spiritball�v����soulenergy�ɒu��������
	if(cnd->id >= SP_SOULGOLEM && cnd->id <= SP_KAUTE && spiritball > 0) {
		soulenergy = spiritball;
		spiritball = 0;
	}

	// �h���S���i�C�g�̃X�L����spiritball�v����servantweapon�ɒu��������
	if(cnd->id >= DK_SERVANTWEAPON && cnd->id <= DK_STORMSLASH && spiritball > 0) {
		servantweapon = spiritball;
		spiritball = 0;
	}

	switch( cnd->id ) {
	case SL_SMA:	/* �G�X�} */
		if(!(type&1) && sd->sc.data[SC_SMA].timer==-1){	// �G�X�}�r���\���
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CG_LONGINGFREEDOM:
		// ���t�ȊO�g���Ȃ�
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
	case CG_MOONLIT:			/* ������̉��� */
		{
			int x1,x2,y1,y2,j;
			int range = skill_get_unit_range(cnd->id,cnd->lv)+1;
			x1 = bl->x - range;
			x2 = bl->x + range;
			y1 = bl->y - range;
			y2 = bl->y + range;
			// �I�n�_���}�b�v�O
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
	case BD_LULLABY:				/* �q��� */
	case BD_RICHMANKIM:				/* �j�����h�̉� */
	case BD_ETERNALCHAOS:			/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:		/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:			/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:				/* ���L�̋��� */
	case BD_INTOABYSS:				/* �[���̒��� */
	case BD_SIEGFRIED:				/* �s���g�̃W�[�N�t���[�h */
	case BD_RAGNAROK:				/* �_�X�̉��� */
		{
			int range=1;
			int c=0;
			map_foreachinarea(skill_check_condition_char_sub,bl->m,
				bl->x-range,bl->y-range,
				bl->x+range,bl->y+range,BL_PC,sd,&c,cnd);
			// �_���X�J�n�ʒu(���t�p)
			sd->dance.x = bl->x;
			sd->dance.y = bl->y;
			if(c<1){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
				return 0;
			}else if(c==0x7fffffff){ // �����s�v�ݒ肾����
				;
			}else{
				cnd->lv = (c + cnd->lv)/2;
			}
		}
		break;
	case SA_ELEMENTWATER:	// ��
	case SA_ELEMENTGROUND:	// �y
	case SA_ELEMENTFIRE:	// ��
	case SA_ELEMENTWIND:	// ��
		{
			// PC -> PC�����֎~����
			if( target && target->type == BL_PC )
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case RA_WUGDASH:	// �E�H�[�O�_�b�V��
		if(!pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SWHOO:	/* �G�X�t */
		if(!(type&1) && sd->sc.data[SC_SWHOO].timer == -1){	// �G�X�t�r���\���
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	}

	// ����ȏ����
	switch(cnd->id)
	{
		case MC_MAMMONITE:	/* ���}�[�i�C�g */
			if(pc_checkskill(sd,BS_UNFAIRLYTRICK)>0)
				zeny = zeny*90/100;
			break;
		case AL_HOLYLIGHT:	/* �z�[���[���C�g */
			// �v���[�X�g�̍�����SP����ʑ���
			if(sd->sc.data[SC_PRIEST].timer!=-1)
				sp = sp * 5;
			break;
#ifndef PRE_RENEWAL
		case AS_SONICBLOW:	/* �\�j�b�N�u���[ */
			if(sd->sc.data[SC_ASSASIN].timer != -1)
				sp = sp * 2;
			break;
#endif
		case SL_SMA:		/* �G�X�} */
		case SL_STUN:		/* �G�X�^�� */
		case SL_STIN:		/* �G�X�e�B�� */
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
			// �����N�̍��@�A�g�X�L����SP�����
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
					// ����������̃f�t�H���g�_���[�W
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
			// �e���L�l�V�X�C���e���X
			if(sd->sc.data[SC_TELEKINESIS_INTENSE].timer != -1)
				sp -= sp*sd->sc.data[SC_TELEKINESIS_INTENSE].val3/100;
			break;
		case KO_MUCHANAGE:
			if(!(type&1) && cnd->lv > 0) {
				sd->zenynage_damage = 5000*cnd->lv + atn_rand()%(5000*cnd->lv);
			}
			break;
		case WH_CRESCIVE_BOLT:		/* �N���b�V�u�{���g */
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
	// �o�[�h�ƃ_���T�[�̍�
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
		sp += sp * 50 / 100;	/* ����SP���� */
	// �E�B�U�[�h�̍�
	if(sd->sc.data[SC_WIZARD].timer != -1) {
		for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
			if(itemid[i] <= 0)
				continue;
			if(itemid[i] == 717)
				sp += sp * 50 / 100;	/* ����SP���� */
		}
	}
#endif

	if(sd->dsprate!=100)
		sp=sp*sd->dsprate/100;	/* ����SP�C�� */

	// �}�X�J���[�h�F���C�W�l�X
	if(sd->sc.data[SC__LAZINESS].timer != -1)
		sp += sd->sc.data[SC__LAZINESS].val1 * 10;	/* ����SP���� */

	// �}�X�J���[�h�F�A�����b�L�[
	if(sd->sc.data[SC__UNLUCKY].timer != -1)
		zeny += 1000;			/* ����zeny���� */

	switch(cnd->id) {
	case SA_CASTCANCEL:
	case SO_SPELLFIST:
		if(ud->skilltimer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case BS_MAXIMIZE:		/* �}�L�V�}�C�Y�p���[ */
	case NV_TRICKDEAD:		/* ���񂾂ӂ� */
	case TF_HIDING:			/* �n�C�f�B���O */
	case AS_CLOAKING:		/* �N���[�L���O */
	case CR_AUTOGUARD:		/* �I�[�g�K�[�h */
	case PA_GOSPEL:			/* �S�X�y�� */
	case ST_CHASEWALK:		/* �`�F�C�X�E�H�[�N */
	case NPC_INVISIBLE:		/* �C���r�W�u�� */
	case TK_RUN:			/* �^�C���M */
	case GS_GATLINGFEVER:		/* �K�g�����O�t�B�[�o�[ */
	case CR_SHRINK:			/* �V�������N */
	case ML_AUTOGUARD:
	case KO_YAMIKUMO:		/* �ŉ_ */
	case IG_GUARD_STANCE:		/* �K�[�h�X�^���X */
	case IG_ATTACK_STANCE:		/* �A�^�b�N�X�^���X */
		{
			int sc_type = GetSkillStatusChangeTable(cnd->id);
			if(sc_type > 0 && sd->sc.data[sc_type].timer != -1)
				sp = 0;	// ��������ꍇ��SP����Ȃ�
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
	case MO_CALLSPIRITS:		/* �C�� */
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
	case MO_BODYRELOCATION:		/* �c�e */
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
			spiritball = 0;
		break;
	case CH_SOULCOLLECT:		/* ���C�� */
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
	case MO_FINGEROFFENSIVE:	/* �w�e */
		if (sd->spiritball.num > 0 && sd->spiritball.num < spiritball) {
			spiritball = sd->spiritball.num;
			sd->spiritball.old = sd->spiritball.num;
		} else {
			sd->spiritball.old = cnd->lv;
		}
		break;
	case MO_CHAINCOMBO:		/* �A�ŏ� */
		if(sd->sc.data[SC_BLADESTOP].timer==-1){
			if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_TRIPLEATTACK)
				return 0;
		}
		break;
	case MO_COMBOFINISH:		/* �җ��� */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_CHAINCOMBO)
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_TIGERFIST:		/* ���Ռ� */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_CHAINCRUSH))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_CHAINCRUSH:		/* �A������ */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_TIGERFIST))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case MO_EXTREMITYFIST:		/* ���C���e�P�� */
		if((sd->sc.data[SC_COMBO].timer != -1 && (sd->sc.data[SC_COMBO].val1 == MO_COMBOFINISH || sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)) || sd->sc.data[SC_BLADESTOP].timer!=-1)
		{
			if(sd->sc.data[SC_COMBO].timer != -1 && sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)
				spiritball = 1;
			else
				spiritball--;	// =4�ł��ǂ���
			if(spiritball<0)
				spiritball=0;
		}
		break;
	case TK_STORMKICK:		/* �t�F�I���`���M */
	case TK_DOWNKICK:		/* �l�����`���M */
	case TK_TURNKICK:		/* �g�������`���M */
	case TK_COUNTER:		/* �A�v�`���I�����M */
		if(sd->sc.data[SC_TKCOMBO].timer == -1 ||
		   (sd->sc.data[SC_TKCOMBO].val4 != TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 != cnd->id) ||
		   (sd->sc.data[SC_TKCOMBO].val4 == TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 == cnd->id)	// �����J�[�͒��O�̃X�L���Ɠ���Ȃ�R���{�I��
		) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,0,0);
			status_change_end(&sd->bl,SC_TKCOMBO,-1);
			return 0;
		}
		break;
	case BD_ADAPTATION:		/* �A�h���u */
		{
			struct skill_unit_group *group=NULL;
			if(
				sd->sc.data[SC_DANCING].timer==-1 ||
				((group=map_id2sg(sd->sc.data[SC_DANCING].val2)) &&
				(skill_get_time(sd->sc.data[SC_DANCING].val1,group->skill_lv) -
				sd->sc.data[SC_DANCING].val3*1000) <= skill_get_time2(cnd->id,cnd->lv))
			){
				// �_���X���Ŏg�p��5�b�ȏ�̂݁H
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case PR_BENEDICTIO:		/* ���̍~�� */
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
	case WE_CALLPARTNER:		/* ���Ȃ��Ɉ������� */
		if(!sd->status.partner_id){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLPARENT:		/* �}�}�A�p�p�A���� */
		if(!sd->status.parent_id[0] && !sd->status.parent_id[1]){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLBABY:		/* �V��A��������Ⴂ */
		if(!sd->status.baby_id){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case AM_CANNIBALIZE:		/* �o�C�I�v�����g */
	case AM_SPHEREMINE:		/* �X�t�B�A�[�}�C�� */
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
					// ���񏢊�����mob�Ƃ͕ʂ̎�ނ�mob���������Ă��Ȃ������`�F�b�N
					if((cnd->id==AM_CANNIBALIZE && ((c > 0 && n != cnd->lv-1) || (n == cnd->lv-1 && c >= maxcount)))
						|| (cnd->id==AM_SPHEREMINE && c >= maxcount)){
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
						return 0;
					}
				}while(cnd->id != AM_SPHEREMINE && ++n < 5);
			}
		}
		break;
	case AM_CALLHOMUN:			/* �R�[���z�����N���X */
		// �쐬�ς݂ň�����
		if(sd->hom.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id && !sd->hom.incubate)
			break;
		if(sd->hd) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(sd->hom.homun_id > 0) {	// �쐬�ς݃z�������鎞�ɃG���u���I�����Ă��玸�s
			for(i=0; i<MAX_INVENTORY; i++) {
				if(sd->status.inventory[i].nameid == 7142) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
		break;
	case AM_REST:			/* ���� */
		if(!homun_isalive(sd) || status_get_hp(&sd->hd->bl) < sd->hd->max_hp * 80 / 100) {
			// �z����HP��MHP��80%�ȏ�ł��邱��
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case AM_RESURRECTHOMUN:			/* ���U���N�V�����z�����N���X */
		if(sd->hd || sd->hom.hp > 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WZ_FIREPILLAR:
		if(cnd->lv <= 5)	// no gems required at level 1-5
			item_nocost = 1;
		// fall through
	case PF_SPIDERWEB:		/* �X�p�C�_�[�E�F�u */
	case MG_FIREWALL:		/* �t�@�C�A�[�E�H�[�� */
	case GN_THORNS_TRAP:	/* �\�[���g���b�v */
	case GN_WALLOFTHORN:	/* �\�[���E�H�[�� */
		/* ������ */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;
	case PF_HPCONVERSION:		/* �����͕ϊ� */
		if(sd->status.sp >= sd->status.max_sp)
			return 0;
		break;
	case PA_PRESSURE:		/* �v���b�V���[ */
		if(status_get_class(target) == MOBID_EMPERIUM) {	// �G���y�͎g�p�s��
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case CR_DEVOTION:		/* �f�B�{�[�V���� */
		if(target && target->type == BL_PC) {
			for(i = 0; i < cnd->lv && i < 5; i++) {
				if(sd->dev.val1[i] <= 0)
					break;
			}
			if(i >= cnd->lv || i >= 5) {
				// ����I�[�o�[
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;

	case BD_LULLABY:			/* �q��S */
	case BD_RICHMANKIM:			/* �j�����h�̉� */
	case BD_ETERNALCHAOS:		/* �i���̍��� */
	case BD_DRUMBATTLEFIELD:	/* �푾�ۂ̋��� */
	case BD_RINGNIBELUNGEN:		/* �j�[�x�����O�̎w�� */
	case BD_ROKISWEIL:			/* ���L�̋��� */
	case BD_INTOABYSS:			/* �[���̒��� */
	case BD_SIEGFRIED:			/* �s���g�̃W�[�N�t���[�h */
	case BA_DISSONANCE:			/* �s���a�� */
	case BA_POEMBRAGI:			/* �u���M�̎� */
	case BA_WHISTLE:			/* ���J */
	case BA_ASSASSINCROSS:		/* �[�z�̃A�T�V���N���X */
	case BA_APPLEIDUN:			/* �C�h�D���̗ь� */
	case DC_UGLYDANCE:			/* ��������ȃ_���X */
	case DC_HUMMING:			/* �n�~���O */
	case DC_DONTFORGETME:		/* ����Y��Ȃ��Łc */
	case DC_FORTUNEKISS:		/* �K�^�̃L�X */
	case DC_SERVICEFORYOU:		/* �T�[�r�X�t�H�[���[ */
	case CG_MOONLIT:			/* ������̉��� */
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		break;
	case CG_HERMODE:			/* �w�����[�h�̏� */
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		if(battle_config.hermode_gvg_only && map[bl->m].flag.gvg==0){	// �V�[�Y�ȊO�g���Ȃ�
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GVGONLY,0,0);
			return 0;
		}
		// WP�`�F�b�N�H
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
		if(status_get_class(target) == MOBID_EMPERIUM) {	// �G���y�͓o�^�s��
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SG_FUSION:
		if(sd->sc.data[SC_FUSION].timer != -1) {	// ��������Ƃ���sp����Ȃ�
			sp = 0;
		}
		if(sd->sc.data[SC_STAR].timer == -1) {	// �P���Z�C�̍����
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case PR_REDEMPTIO:
		if(battle_config.redemptio_penalty_type) {
			atn_bignumber exp = pc_nextbaseexp(sd);
			if(exp <= 0) {
				// �I�[���̏ꍇ�͌��݂̃��x���ɕK�v�Ȍo���l���Q�Ƃ���
				sd->status.base_level--;
				exp = pc_nextbaseexp(sd);
				sd->status.base_level++;
				if(exp <= 0) {
					// ����ł�exp�����ݒ�Ȃ狖��
					break;
				}
			}
			if(sd->status.base_exp < exp / 100 * battle_config.death_penalty_base / 100) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_EXP,0,0);
				return 0;
			}
		}
		break;
	case GS_GLITTERING:		/* �t���b�v�U�R�C�� */
		if(sd->coin.num >= MAX_COIN) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GS_FLING:		/* �t���C���O */
		if(sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COIN,coin,0);
			return 0;
		}
		coin = 0;	// �R�C���͏�ԕt�^���ɏ������
		break;
	case GS_MADNESSCANCEL:	/* �}�b�h�l�X�L�����Z���[ */
		if(sd->sc.data[SC_ADJUSTMENT].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		else if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {
			// ��������ꍇ�͏���Ȃ�
			sp = 0;
			coin = 0;
		}
		break;
	case GS_ADJUSTMENT:		/* �A�W���X�g�����g */
		if(sd->sc.data[SC_MADNESSCANCEL].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case HT_POWER:			/* �r�[�X�g�X�g���C�t�B���O */
		if(sd->sc.data[SC_DOUBLE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case RK_GIANTGROWTH:	// �W���C�A���g�O���[�X
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 1) {		// ���[���}�X�^���[Lv1���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_VITALITYACTIVATION:	// �o�C�^���e�B�A�N�e�B�x�[�V����
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 2) {		// ���[���}�X�^���[Lv2���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STORMBLAST:		// �X�g�[���u���X�g
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 3) {		// ���[���}�X�^���[Lv3���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STONEHARDSKIN:	// �X�g�[���n�[�h�X�L��
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 4) {		// ���[���}�X�^���[Lv4���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_FIGHTINGSPIRIT:	// �t�@�C�e�B���O�X�s���b�g
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 5) {		// ���[���}�X�^���[Lv5���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_ABUNDANCE:		// �A�o���_���X
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 6) {		// ���[���}�X�^���[Lv6���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_CRUSHSTRIKE:	// �N���b�V���X�g���C�N
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 7) {		// ���[���}�X�^���[Lv7���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_REFRESH:	// ���t���b�V��
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 8) {		// ���[���}�X�^���[Lv8���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_MILLENNIUMSHIELD:	// �~���j�A���V�[���h
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 9) {		// ���[���}�X�^���[Lv9���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_LUXANIMA:	// ���N�X�A�j�}
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 10) {		// ���[���}�X�^���[Lv10���K�v
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_WEAPONBLOCKING:	/* �E�F�|���u���b�L���O */
		if(sd->sc.data[SC_WEAPONBLOCKING].timer != -1)
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		break;
	case GC_COUNTERSLASH:		/* �J�E���^�[�X���b�V�� */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_WEAPONCRUSH:		/* �E�F�|���N���b�V�� */
		if(sd->sc.data[SC_WEAPONBLOCKING_POSTDELAY].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_VENOMPRESSURE:		/* �x�i���v���b�V���[ */
	case GC_POISONSMOKE:		/* �|�C�Y���X���[�N */
		if(sd->sc.data[SC_POISONINGWEAPON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_POISONINGWEAPON,0,0);
			return 0;
		}
		break;
	case GC_CLOAKINGEXCEED:	/* �N���[�L���O�G�N�V�[�h */
		if(sd->sc.data[SC_CLOAKINGEXCEED].timer != -1)
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		break;
	case GC_HALLUCINATIONWALK:	/* �n���V�l�[�V�����E�H�[�N */
		if(sd->sc.data[SC_HALLUCINATIONWALK].timer != -1 || sd->sc.data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_CROSSRIPPERSLASHER:		/* �N���X���b�p�[�X���b�V���[ */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case AB_ANCILLA:			/* �A���V�� */
		{
			int idx = pc_search_inventory(sd,12333);
			if(idx >= 0 && sd->status.inventory[idx].amount >= 3 ) {	/* �쐬�O�ɏ������E���𒴂��Ă��� */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_ANCILLAOVER,0,0);
				return 0;
			}
		}
		break;
	case WL_TETRAVORTEX:		/* �e�g���{���e�b�N�X */
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
	case WL_SUMMONFB:		/* �T�����t�@�C�A�{�[�� */
	case WL_SUMMONBL:		/* �T�����{�[�����C�g�j���O */
	case WL_SUMMONWB:		/* �T�����E�H�[�^�[�{�[�� */
	case WL_SUMMONSTONE:	/* �T�����X�g�[�� */
		for(i = 0; i < 5; i++) {
			if(sd->sc.data[SC_SUMMONBALL1 + i].timer == -1)
				break;
		}
		if(i >= 5) {	// �������������ς�
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
			return 0;
		}
		break;
	case RA_CAMOUFLAGE:		/* �J���t���[�W�� */
		if(sd->sc.data[SC_CAMOUFLAGE].timer != -1) {
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		}
		// Lv1�`2�͕Ǖt�߃`�F�b�N
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
	case NC_PILEBUNKER:			/* �p�C���o���J�[ */
		{
			// �p�C���o���J�[�̑����`�F�b�N
 			static const int pile_item[] = { 1549, 16044, 16045, 16046 };		// �p�C���o���J�[�n��̑����i
			static const int pile_max = sizeof(pile_item)/sizeof(pile_item[0]);
			for(i = 0; i < pile_max; i++) {
				if(pc_equippeditem(sd,pile_item[i]))
					break;	// �������Ă����画��OK
			}
			if(i >= pile_max) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,pile_item[0]);
				return 0;
			}
		}
		break;
	case NC_HOVERING:			/* �z�o�[�����O */
		// �z�o�[�����O�u�[�X�^�[�𑕔����Ă��邩����
		if(pc_equippeditem(sd,2801) == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,2801);
			return 0;
		}
		break;
	case NC_SILVERSNIPER:		/* FAW �V���o�[�X�i�C�p�[ */
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
	case NC_MAGICDECOY:      /* FAW �}�W�b�N�f�R�C */
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
	case SC_REPRODUCE:	/* ���v���f���[�X */
		if(sd->sc.data[SC__REPRODUCE].timer != -1)
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		break;
	case SC_INVISIBILITY:	/* �C���r�W�r���e�B */
		if(sd->sc.data[SC__INVISIBILITY].timer != -1)
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		break;
	case SC_DIMENSIONDOOR:	/* �f�B�����V�����h�A */
		if(map[bl->m].flag.noteleport) {
			clif_skill_teleportmessage(sd,2);
			return 0;
		}
		break;
	case LG_FORCEOFVANGUARD:	/* �t�H�[�X�I�u�o���K�[�h */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer != -1)
			sp = 0;		// ��������ꍇ��SP����Ȃ�
		break;
	case LG_RAGEBURST:	/* ���C�W�o�[�X�g�A�^�b�N */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer == -1 || sd->sc.data[SC_FORCEOFVANGUARD].val4 < 1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,0,0);
			return 0;
		}
		break;
	case LG_PRESTIGE:	/* �v���X�e�B�[�W */
	case LG_BANDING:	/* �o���f�B���O */
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case LG_HESPERUSLIT:	/* �w�X�y���X���b�g */
		if(sd->sc.data[SC_INSPIRATION].timer == -1 && (sd->sc.data[SC_BANDING].timer == -1 || sd->sc.data[SC_BANDING].val2 < 3)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case LG_INSPIRATION:	/* �C���X�s���[�V���� */
		if(sd->sc.data[SC_PRESTIGE].timer != -1 || sd->sc.data[SC_BANDING].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case SR_FALLENEMPIRE:		/* ��Z���x */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SR_DRAGONCOMBO) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SR_DRAGONCOMBO,0);
			return 0;
		}
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer != -1 || sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_TIGERCANNON:		/* �j�C */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_RAMPAGEBLASTER:		/* ���C�U�e */
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
	case SR_GATEOFHELL:		/* �����j���� */
		if(sd->status.sp < sd->status.max_sp * 30 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
			return 0;
		}
		break;
	case SR_RIDEINLIGHTNING:	/* �����e */
		if(sd->sc.data[SC_MASSIVE_F_BLASTER].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_FLASHCOMBO:		/* �M���A�� */
		if(sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case WM_GREAT_ECHO:					/* �O���[�g�G�R�[ */
	case WM_SONG_OF_MANA:				/* �}�i�̉� */
	case WM_DANCE_WITH_WUG:				/* �_���X�E�B�Y�E�H�[�O */
	case WM_SOUND_OF_DESTRUCTION:		/* �T�E���h�I�u�f�B�X�g���N�V���� */
	case WM_SATURDAY_NIGHT_FEVER:		/* �t���C�f�[�i�C�g�t�B�[�o�[ */
	case WM_LERADS_DEW:					/* ���[���Y�̖� */
	case WM_MELODYOFSINK:				/* �����f�B�[�I�u�V���N */
	case WM_BEYOND_OF_WARCRY:			/* �r�����h�I�u�E�H�[�N���C */
	case WM_UNLIMITED_HUMMING_VOICE:	/* �G���h���X�n�~���O�{�C�X */
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
	case SO_POISON_BUSTER:	/* �|�C�Y���o�X�^�[ */
		if(target) {
			struct status_change *sc = status_get_sc(target);

			if(sc && sc->data[SC_POISON].timer == -1) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SO_ARRULLO:	/* �A���[�W�� */
		if(!map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		break;
	case SO_SUMMON_AGNI:	/* �T�����A�O�j */
	case SO_SUMMON_AQUA:	/* �T�����A�N�A */
	case SO_SUMMON_VENTUS:	/* �T�����x���g�X */
	case SO_SUMMON_TERA:	/* �T�����e�� */
		{
			int skill = pc_checkskill(sd,SO_EL_SYMPATHY);
			if(skill > 0) {
				sp -= sp * (5 + skill * 5) / 100;
			}
		}
		break;
	case SO_EL_CONTROL:	/* �G�������^���R���g���[�� */
	case SO_EL_ACTION:	/* �G�������^���A�N�V���� */
	case SO_ELEMENTAL_SHIELD:	/* �G�������^���V�[���h */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case SO_EL_CURE:	/* �G�������^���L���A�[ */
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
	case KO_KAHU_ENTEN:	/* �Ε��]���V */
	case KO_HYOUHU_HUBUKI:	/* �X���]���� */
	case KO_KAZEHU_SEIRAN:	/* �����]�� */
	case KO_DOHU_KOUKAI:	/* �y���]���� */
		if(sd->elementball.num >= MAX_ELEMENTBALL) {
			if(sd->elementball.ele == skill_get_pl(cnd->id)) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
				return 0;
			}
		}
		break;
	case KO_KAIHOU:	/* �p����� */
	case KO_ZENKAI:	/* �p���S�J */
		if(sd->elementball.num < 1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_NOTHING,0,0);
			return 0;
		}
		break;
	case RL_B_TRAP:	/* �o�C���h�g���b�v */
		/* ������ */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;
	case RL_QD_SHOT:			/* �N�C�b�N�h���[�V���b�g */
		if(sd->sc.data[SC_QD_SHOT_READY].timer == -1 || sd->sc.data[SC_QD_SHOT_READY].val2 == sd->bl.id)
			return 0;
		break;
	case GD_BATTLEORDER:		/* �Ր�Ԑ� */
	case GD_REGENERATION:		/* ���� */
	case GD_RESTORE:		/* ���� */
	case GD_EMERGENCYCALL:		/* �ً}���W */
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
		
	case SJ_SOLARBURST:		/* ���z���� */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SJ_PROMINENCEKICK){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SJ_PROMINENCEKICK,0);
			return 0;
		}
		//fall through
	case SJ_PROMINENCEKICK:		/* �g���r */
		if((sd->sc.data[SC_SUNSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSUN:		/* ���z�̌� */
		if(sd->sc.data[SC_SUNSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FULLMOONKICK:		/* �����r */
		if(sd->sc.data[SC_NEWMOON].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		//fall through
	case SJ_NEWMOONKICK:		/* �񌎋r */
		if((sd->sc.data[SC_LUNARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFMOON:		/* ���̌� */
		if(sd->sc.data[SC_LUNARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FLASHKICK:		/* �M���r */
	case SJ_FALLINGSTAR:		/* �������� */
		if((sd->sc.data[SC_STARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSTAR:		/* ���̌� */
		if(sd->sc.data[SC_STARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_GRAVITYCONTROL:		/* �d�͒��� */
	case SJ_NOVAEXPLOSING:		/* �V������ */
	case SJ_STAREMPEROR:		/* ����~�� */
	case SJ_BOOKOFCREATINGSTAR:		/* �n���̏� */
	case SJ_BOOKOFDIMENSION:		/* �����̏� */
		if(sd->sc.data[SC_UNIVERSESTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(battle_config.allow_se_univ_skill_limit && !map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		break;
	case SP_SOULGOLEM:		/* �S�[�����̍� */
	case SP_SOULSHADOW:		/* �e�̍� */
	case SP_SOULFALCON:		/* ��̍� */
	case SP_SOULFAIRY:		/* �d���̍� */
		if(target && target->type != BL_PC) {		// PC�ȊO�͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		/* �g���X�L���ȊO�̍���Ԃ��𔻒� */
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
	case SP_SOULCURSE:		/* ����߈� */
		if(target && target->type != BL_MOB) {		// MOB�ȊO�͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SPA:				/* �G�X�p */
	case SP_SWHOO:				/* �G�X�t */
		if(target && target->type != BL_MOB && !battle_config.allow_es_magic_all) {		// MOB�ȊO�͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULDIVISION:		/* ���̕��� */
		if(target->type != BL_PC) {		// PC�ȊO�͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULREVOLVE:		/* ���̏z�� */
		if(target->type != BL_PC) {		// PC�ȊO�͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// �����p�[�e�B����Ȃ��ƃ_��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		// ����Ԃ��𔻒�
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
	case SP_SOULEXPLOSION:		/* ���̕��� */
		if(status_get_hp(target) < 10) {	// �Ώۂ�HP��10�����͎��s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		// ����Ԃ��𔻒�
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
	case SP_KAUTE:		/* �J�E�g */
		{
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!tsd) {
				// �Ώۂ��l�ȊO���s
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			// HP��30%�ȏ�K�v
			if(sd->status.hp < sd->status.max_hp * 30 / 100) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
				return 0;
			}
			if(battle_config.soul_linker_battle_mode_ka == 0) {
				// �\�E�������J�[�n�E�Ƃ��Ƒ��ȊO�A���̘A����Ԍ��ʒ��łȂ���Ύg�p���s
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
	case IQ_JUDGE:		/* ���́F�R���� */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FLAME:		/* ��񌂁F�Ŗ��̉� */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FAITH:		/* ��񌂁F�M�O */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_JUDGEMENT:		/* ��񌂁F�R�� */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_PUNISH:		/* ��O���F�f�� */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_FLAME_BOMB:		/* ��O���F�ŉΌ� */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_CONSECRATION:		/* ��O���F�� */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_EXOR_FLAME:		/* �ŏI�́F�Ŗ��̉� */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_GUARDIAN_SHIELD:		/* �K�[�f�B�A���V�[���h */
	case IG_ULTIMATE_SACRIFICE:		/* �A���e�B���b�g�T�N���t�@�C�X */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_REBOUND_SHIELD:			/* ���o�E���h�V�[���h */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		// �f�B�{�[�V��������
		for(i=0; i<5; i++) {
			if(sd->dev.val1[i]) {
				break;
			}
		}
		// �f�B�{�[�V�������g�p���Ă��Ȃ�
		if(i >= 5) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IG_GRAND_JUDGEMENT:		/* �O�����h�W���b�W�����g */
	case IG_SHIELD_SHOOTING:		/* �V�[���h�V���[�e�B���O */
	case IG_OVERSLASH:				/* �I�[�o�[�X���b�V�� */
		if(sd->sc.data[SC_ATTACK_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CD_REPARATIO:				/* ���p���e�B�I */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC�ȊO�ƕs�������ɂ͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case CD_MEDIALE_VOTUM:			/* ���f�B�A���{�g�D�� */
	case CD_DILECTIO_HEAL:			/* �f�B���N�e�B�I�q�[�� */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC�ȊO�ƕs�������ɂ͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// �����p�[�e�B����Ȃ��ƃ_��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case CD_ARGUTUS_VITA:		/* �A���O�g�D�X���B�^ */
	case CD_ARGUTUS_TELUM:		/* �A���O�g�D�X�e���� */
	case CD_PRESENS_ACIES:		/* �v���Z���X�A�L�G�[�X */
	case MT_D_MACHINE:			/* �h�䑕�u�L���� */
	case EM_SPELL_ENCHANTING:	/* �X�y���G���`�����e�B���O */
	case SOA_TALISMAN_OF_PROTECTION:	/* ��아 */
	case SOA_TALISMAN_OF_WARRIOR:	/* ���m�� */
	case SOA_TALISMAN_OF_MAGICIAN:	/* �@�t�� */
	case SOA_TALISMAN_OF_FIVE_ELEMENTS:	/* �܍s�� */
		if(target->type != BL_PC) {		// PC�ȊO�ɂ͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// �����p�[�e�B����Ȃ��ƃ_��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SHC_ETERNAL_SLASH:		/* �G�^�[�i���X���b�V�� */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case SHC_POTENT_VENOM:		/* �|�e���g�x�i�� */
		if(sd->sc.data[SC_EDP].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SHC_IMPACT_CRATER:		/* �C���p�N�g�N���[�^�[ */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case MT_A_MACHINE:			/* �U�����u�L���� */
		if(target->type != BL_PC) {		// PC�ȊO�ɂ͎g�p���s
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// �����p�[�e�B����Ȃ��ƃ_��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
			if(abs(sd->status.base_level - tsd->status.base_level) > 15) {	// ���x������15�ȏ�̑���͎g�p���s
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR �o�g���E�H���A�[ */
	case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR �f���A���L���m�� */
	case MT_SUMMON_ABR_MOTHER_NET:		/* ABR �}�U�[�l�b�g */
	case MT_SUMMON_ABR_INFINITY:		/* ABR �C���t�B�j�e�B */
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
	case BO_WOODENWARRIOR:		/* �N���G�C�g�E�h�D���E�H���A�[ */
	case BO_WOODEN_FAIRY:		/* �N���G�C�g�E�h�D���t�F�A���[ */
	case BO_CREEPER:			/* �N���G�C�g�N���[�p�[ */
	case BO_HELLTREE:			/* �N���G�C�g�w���c���[ */
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
	case EM_ACTIVITY_BURN:					/* �A�N�e�B�r�e�B�o�[�� */
		if(target->type != BL_PC) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_INCREASING_ACTIVITY:			/* �C���N���[�V���O�A�N�e�B�r�e�B */
		if(target->type != BL_PC || bl == target) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_ARDOR:			/* �T�����A���h�[�� */
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
	case EM_SUMMON_ELEMENTAL_DILUVIO:		/* �T�����f�B���r�I */
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
	case EM_SUMMON_ELEMENTAL_PROCELLA:		/* �T�����v���Z�� */
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
	case EM_SUMMON_ELEMENTAL_TERREMOTUS:	/* �T�����e�����g�D�X */
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
	case EM_SUMMON_ELEMENTAL_SERPENS:		/* �T�����T�[�y���X */
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
	case EM_ELEMENTAL_BUSTER:	/* �G�������^���o�X�^�[ */
	case EM_ELEMENTAL_VEIL:		/* �G�������^�����F�[�� */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		if(!elem_is4thclass(sd->eld)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SOA_SOUL_GATHERING:		/* �썰��g */
		if(sd->sc.data[SC_SOULCOLLECT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULCOLLECT,0,0);
			return 0;
		}
		break;
	case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* ����� */
		if(sd->soulenergy.num == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULENERGY,0,0);
			return 0;
		}
		break;
	case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* �l���܍s�w */
		if(sd->sc.data[SC_T_FOURTH_GOD].timer == -1 && sd->sc.data[SC_T_FIVETH_GOD].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SH_BLESSING_OF_MYSTICAL_CREATURES:		/* �ɂ��u���b�V���O */
		if(bl == target) {		// �����ɂ͎g�p�s��
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(tsc && tsc->data[SC_BLESSING_OF_M_C_DEBUFF].timer != -1) {		// ���o�E���h��Ԃɂ͎g�p�s��
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(tsd && pc_isdoram(tsd)) {			// �h�����n��ɂ͎g�p�s��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// �����p�[�e�B����Ȃ��ƃ_��
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case SKE_NOON_BLAST:		/* ���V��z */
		if(sd->sc.data[SC_RISING_SUN].timer == -1 && sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_SUNSET_BLAST:		/* �V�z */
		if(sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SUNSET_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_MIDNIGHT_KICK:		/* ���V�ꌎ */
		if(sd->sc.data[SC_RISING_MOON].timer == -1 && sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_DAWN_BREAK:		/* �V�� */
		if(sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_DAWN_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_STAR_BURST:		/* �V������ */
	case SKE_STAR_CANNON:		/* �V�� */
		{
			// �V�n�����͈͓̔����`�F�b�N
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
	case SS_KUNAIKUSSETSU:		/* �ꖳ -����- */
		{
			// �ꖳ�g���b�v����
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

		if(!sd->skill_item.flag) {		// �A�C�e���X�L���R���Ȃ�SP�`�F�b�N�͕s�v
			if(sp > 0 && sd->status.sp < sp) {		/* SP�`�F�b�N */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
				return 0;
			}
		}
		if(hp > 0 && sd->status.hp < hp) {			/* HP�`�F�b�N */
			clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
			return 0;
		}
		if(ap > 0 && sd->status.ap < ap) {			/* AP�`�F�b�N */
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
		if(arrow > 0) {						// ��s��
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if( idx == -1 ||
			    !(sd->inventory_data[idx]->arrow_type & skill_get_arrow_type(cnd->id)) ||
			    sd->status.inventory[idx].amount < arrow )
			{
				// ��̎�ނ��ƂɎ��s���b�Z�[�W��\��
				switch(skill_get_arrow_type(cnd->id)) {
				case 0x0004:		// �n���h�K����p�e
				case 0x0008:		// ���C�t����p�e
				case 0x0010:		// �V���b�g�K����p�e
				case 0x0020:		// �K�g�����K����p�e
				case 0x0040:		// �O���l�[�h�����`���[��p�e
					clif_skill_fail(sd,cnd->id,SKILLFAIL_BULLET,0,0);
					break;
				case 0x0100:		// �ꖳ
					clif_skill_fail(sd,cnd->id,SKILLFAIL_KUNAI,0,0);
					break;
				case 0x0200:		// �L���m���{�[��
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
			// ���ꔻ��
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
		case SA_VOLCANO:		/* �{���P�[�m */
		case SA_DELUGE:			/* �f�����[�W */
		case SA_VIOLENTGALE:	/* �o�C�I�����g�Q�C�� */
			// ������p �o�Ă���Ԃ̓R�X�g����
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
				item_nocost = 1;
			break;
		case SR_CURSEDCIRCLE:	/* �����w */
			spiritball = 0;		// �C�e�̏���̓X�L�����ʔ�����
			break;
		case DK_SERVANT_W_PHANTOM:		/* �T�[���@���g�E�F�|���F�t�@���g�� */
		case DK_SERVANT_W_DEMOL:		/* �T�[���@���g�E�F�|���F�f�����b�V���� */
			servantweapon = 0;	// ����̂̏���̓X�L�����ʔ�����
			break;
	}

	// GVG PVP�ȊO�̃}�b�v�ł̓��ꏈ��
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
						// �ԃ|�[�V����
						itemid[MAX_SKILL_DB_ITEM] = 501;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else if(cnd->lv < 10) {
						// ���|�[�V����
						itemid[MAX_SKILL_DB_ITEM] = 503;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else {
						// ���|�[�V����
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
		if(!sd->skill_item.flag) {	// �A�C�e���X�L���R���Ȃ�SP����Ȃ�
			if(sp > 0) {				// SP����
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
			}
		}
		if(hp > 0) {					// HP����
			sd->status.hp -= hp;
			clif_updatestatus(sd,SP_HP);
		}
		if(ap > 0) {					// AP����
			sd->status.ap -= ap;
			clif_updatestatus(sd,SP_AP);
		}
		if(zeny > 0)					// Zeny����
			pc_payzeny(sd,zeny);
		if(spiritball > 0)				// �C������
			pc_delspiritball(sd,spiritball,0);
		if(coin > 0)					// �R�C������
			pc_delcoin(sd,coin,0);
		if(soulenergy > 0)				// �\�E���G�i�W�[����
			pc_delsoulenergy(sd,soulenergy,0);
		if(servantweapon > 0)			// �T�[���@���g�E�F�|������
			pc_delball(sd,servantweapon,0);
	}
	return 1;
}

// MOB�p����( 0: �g�p���s 1: �g�p���� )
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
				// ���Ҏ傪PC�Ȃ�g�p�s��
				return 0;
			}
			break;
		case NPC_SUMMONSLAVE:
			if(md->master_id <= 0)
				break;
			if(md->state.special_mob_ai != MOB_AI_NONE) {
				// ���Ҏ傪PC�Ȃ�g�p�s��
				return 0;
			}
			if(battle_config.summonslave_generation > 0) {
				// ���Ґ�����v�Z����
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
		case NPC_DEATHSUMMON:		/* �f�X�T���� */
			if(md->master_id > 0 && md->state.special_mob_ai != MOB_AI_NONE) {
				// ���Ҏ傪PC�Ȃ�g�p�s��
				return 0;
			}
			if(md->state.skillstate != MSS_DEAD) {
				// �����Ă�����g�p�s��
				return 0;
			}
			break;
	}

	return 1;
}

// PET�p����( 0: �g�p���s 1: �g�p���� )
static int skill_check_condition2_pet(struct pet_data *pd, struct skill_condition *cnd, int type)
{
	nullpo_retr(0, pd);
	nullpo_retr(0, cnd);

	// �y�b�g���g���Ȃ��ق����悢�X�L��
	switch(cnd->id)
	{
		case CG_MOONLIT:	/* ������̉��� */
			// �y�b�g�Ɏg����ƒʍs�̎ז�
			return 0;
	}
	return 1;
}

// HOM�p����( 0: �g�p���s 1: �g�p���� )
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
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* ����HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* ����SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	spiritball = (cnd->lv <= 0)? 0: skill_db[skilldb_id].spiritball[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// �X�L��Lv���̏���A�C�e��
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
		if(hp > 0 && hd->status.hp < hp)	/* HP�`�F�b�N */
			return 0;
		if(sp > 0 && hd->status.sp < sp)	/* SP�`�F�b�N */
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
			case HVAN_EXPLOSION:	/* �o�C�I�G�N�X�v���[�W���� */
				if(hd->intimate < battle_config.hvan_explosion_intimate) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_INTIMATE, 0, 0);
					return 0;
				}
				break;
			case MH_LIGHT_OF_REGENE:	/* �Đ��̌� */
				if(hd->intimate < 91100) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_INTIMATE, 0, 0);
					return 0;
				}
				break;
			case MH_GOLDENE_FERSE:	/* �S�[���f���y���W�F */
				if(hd->sc.data[SC_ANGRIFFS_MODUS].timer != -1)
					return 0;
				break;
			case MH_ANGRIFFS_MODUS:	/* �A���O���t�X���h�X */
				if(hd->sc.data[SC_GOLDENE_FERSE].timer != -1)
					return 0;
				break;
			case MH_TINDER_BREAKER:	/* �e�B���_�[�u���C�J�[ */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 2)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_GRAPPLER, 1, 0);
					return 0;
				}
				break;
			case MH_SONIC_CRAW:		/* �\�j�b�N�N���[ */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 1)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_FIGHTER, 0, 0);
					return 0;
				}
				if(hd->spiritball < 1) {
					clif_skill_fail(hd->msd,cnd->id,SKILLFAIL_SPIRITBALL,1,0);
					return 0;
				}
				break;
			case MH_SILVERVEIN_RUSH:	/* �V���o�[�x�C�����b�V�� */
				if (!(hd->sc.data[SC_STYLE_CHANGE].timer != -1 && hd->sc.data[SC_STYLE_CHANGE].val1 == 1)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_STYLE_FIGHTER, 0, 0);
					return 0;
				}
				if (!(hd->sc.data[SC_COMBO].timer != -1 && hd->sc.data[SC_COMBO].val1 == MH_SONIC_CRAW)) {
					clif_skill_fail(msd, cnd->id, SKILLFAIL_COMBOSKILL, MH_SONIC_CRAW, 0);
					return 0;
				}
				break;
			case MH_MIDNIGHT_FRENZY:	/* �~�b�h�i�C�g�t�����W */
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
			case MH_POISON_MIST:		/* �|�C�Y���~�X�g */
			case MH_LAVA_SLIDE:			/* ���[���@�X���C�h */
			case MH_VOLCANIC_ASH:		/* �{���J�j�b�N�A�b�V�� */
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
			// ���ꔻ��
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
		if(sp > 0) {				// SP����
			hd->status.sp -= sp;
			clif_send_homstatus(msd,0);
		}
		if(hp > 0) {				// HP����
			hd->status.hp -= hp;
			clif_send_homstatus(msd,0);
		}
		if(zeny > 0)				// Zeny����
			pc_payzeny(msd,zeny);
		if(spiritball > 0)				// �C������
			homun_delspiritball(hd,spiritball,0);
	}
	return 1;
}

// MERC�p����( 0: �g�p���s 1: �g�p���� )
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
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* ����HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* ����SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// �X�L��Lv���̏���A�C�e��
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
		if(hp > 0 && mcd->status.hp < hp)	/* HP�`�F�b�N */
			return 0;
		if(sp > 0 && mcd->status.sp < sp)	/* SP�`�F�b�N */
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
			// ���ꔻ��
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
		if(sp > 0) {				// SP����
			mcd->status.sp -= sp;
			clif_mercupdatestatus(msd,SP_SP);
		}
		if(hp > 0) {				// HP����
			mcd->status.hp -= hp;
			clif_mercupdatestatus(msd,SP_HP);
		}
		if(zeny > 0)				// Zeny����
			pc_payzeny(msd,zeny);
	}
	return 1;
}

// ELEM�p����( 0: �g�p���s 1: �g�p���� )
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
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* ����HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* ����SP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	state      = skill_db[skilldb_id].state;

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// �X�L��Lv���̏���A�C�e��
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
		if(hp > 0 && eld->status.hp < hp)	/* HP�`�F�b�N */
			return 0;
		if(sp > 0 && eld->status.sp < sp)	/* SP�`�F�b�N */
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
			// ���ꔻ��
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
		if(sp > 0) {				// SP����
			eld->status.sp -= sp;
			clif_elemupdatestatus(msd,SP_SP);
		}
		if(hp > 0) {				// HP����
			eld->status.hp -= hp;
			clif_elemupdatestatus(msd,SP_HP);
		}
		if(zeny > 0)				// Zeny����
			pc_payzeny(msd,zeny);
	}
	return 1;
}

/*==========================================
 * �X�L���ɂ��A�C�e������
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
			// �g���b�v�������K�����܂��͎g�p�X�L�����G�X�P�[�v�Őݒu�p�g���b�v������Ȃ������ꍇ
			if((pc_checkskill(sd,RA_RESEARCHTRAP) || cnd->id == SC_ESCAPE) && itemid[i] ==1065) {
				// ���ǌ^�ݒu�p�g���b�v�ɒu�������čČ���
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

		// �X�g�[���J�[�XLv6�ȏ�̓W�F������Ȃ��ɂ��Ă���
		if(cnd->id == MG_STONECURSE && cnd->lv >= 6 && itemid[i] >= 715 && itemid[i] <= 717) {
			idx[i] = -1;
		}
		// �n���^�[�̃g���b�v�X�L���̓��j�b�g�ݒu���ɃA�C�e������
		if(cnd->id >= HT_SKIDTRAP && (cnd->id <= HT_CLAYMORETRAP || cnd->id == HT_TALKIEBOX)) {
			idx[i] = -1;
		}

		if(sc) {
			// �g���s�b�N���A50%�̊m���ŏ���Ȃ�
			if(sc->data[SC_TROPIC].timer != -1 && (cnd->id == SA_FLAMELAUNCHER || cnd->id == SA_VOLCANO) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// �N�[���G�A�[���A50%�̊m���ŏ���Ȃ�
			if(sc->data[SC_CHILLY_AIR].timer != -1 && (cnd->id == SA_FROSTWEAPON || cnd->id == SA_DELUGE) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// ���C���h�X�g�[�����A50%�̊m���ŏ���Ȃ�
			if(sc->data[SC_WILD_STORM].timer != -1 && (cnd->id == SA_LIGHTNINGLOADER || cnd->id == SA_VIOLENTGALE) && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// �A�b�v�w�C�o�����A50%�̊m���ŏ���Ȃ�
			if(sc->data[SC_UPHEAVAL].timer != -1 && cnd->id == SA_SEISMICWEAPON && atn_rand()%100 < 50) {
				idx[i] = -1;
			}
			// ���T�[�`���|�[�g
			if(sc->data[SC_RESEARCHREPORT].timer != -1 && cnd->id >= BO_ACIDIFIED_ZONE_WATER && cnd->id <= BO_ACIDIFIED_ZONE_FIRE && amount[i] > 0) {
				amount[i] -= 1;
			}
		}
	}

	if(type&1 && (cnd->id != AL_WARP || type&2)) {
		if(cnd->id != AM_POTIONPITCHER && cnd->id != CR_SLIMPITCHER && cnd->id != GN_FIRE_EXPANSION) {
			for(i=0; i<MAX_SKILL_DB_ITEM+1; i++) {
				if(idx[i] >= 0)
					pc_delitem(sd,idx[i],amount[i],0,1);	// �A�C�e������
			}
		}
	}

	return 1;
}

/*==========================================
 * �r�����Ԍv�Z
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
		// ���@�͑����̌��ʏI��
		if(sc->data[SC_MAGICPOWER].timer != -1) {
			if(sc->data[SC_MAGICPOWER].val2 > 0) {
				/* �ŏ��ɒʂ������ɂ̓A�C�R���������� */
				sc->data[SC_MAGICPOWER].val2--;
				clif_status_change(bl, SI_MAGICPOWER, 0, 0, 0, 0, 0);
			} else {
				status_change_end(bl, SC_MAGICPOWER, -1);
			}
		}
		// �f�X�o�E���h�ҋ@��
		if(sc->data[SC_DEATHBOUND].timer != -1)
			fixedtime += 1000;
	}

	// �J�[�h�ɂ��r�����ԑ�������
	if(casttime > 0 && sd && sd->skill_addcast.count > 0) {
		for(i=0; i<sd->skill_addcast.count; i++) {
			if(skillid == sd->skill_addcast.id[i])
				casttime += sd->skill_addcast.time[i];
		}
	}

	if(casttime > 0) {
		int reduce_time = 0;	// �팸����

		/* �T�t���M�E�� */
		if(sc && sc->data[SC_SUFFRAGIUM].timer != -1) {
			reduce_time += sc->data[SC_SUFFRAGIUM].val1 * 15;
			status_change_end(bl, SC_SUFFRAGIUM, -1);
		}

		// �X�e�[�^�X�̉e�����v�Z����
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

			/* �u���M�̎� */
			if(sc->data[SC_POEMBRAGI].timer != -1)
				type = SC_POEMBRAGI;
			else if(sc->data[SC_POEMBRAGI_].timer != -1)
				type = SC_POEMBRAGI_;

			if(type >= 0) {
				reduce_time += (sc->data[type].val1*3 + sc->data[type].val2 + (sc->data[type].val3>>16));
			}

#ifndef PRE_RENEWAL
			/* �E�B�U�[�h�̍� */
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

			/* �X���E�L���X�g */
			if(sc->data[SC_SLOWCAST].timer != -1)
				reduce_time -= sc->data[SC_SLOWCAST].val1 * 20;

			/* �}�X�J���[�h�F���C�W�l�X */
			if(sc->data[SC__LAZINESS].timer != -1)
				reduce_time -= sc->data[SC__LAZINESS].val1 * 10;

			/* �\�Z�� */
			if(sc->data[SC_IZAYOI].timer != -1)
				reduce_time += 50;

			/* �e���L�l�V�X�C���e���X */
			if(sc->data[SC_TELEKINESIS_INTENSE].timer != -1 && skill_get_pl(skillid) == ELE_GHOST)
				reduce_time += 10;

			/* �d���̍� */
			if(sc->data[SC_SOULFAIRY].timer != -1)
				reduce_time += sc->data[SC_SOULFAIRY].val3;
		}

		// �J�[�h�ɂ��r�����ԑ�������
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

	// �J�[�h�ɂ��r�����ԑ�������
	if(fixedtime > 0 && sd && sd->skill_addfixcast.count > 0) {
		for(i=0; i<sd->skill_addfixcast.count; i++) {
			if(skillid == sd->skill_addfixcast.id[i])
				fixedtime += sd->skill_addfixcast.time[i];
		}
	}
	if(sc) {
		/* �n�E�����O�I�u�}���h���S�� */
		if(sc->data[SC_MANDRAGORA].timer != -1) {
			fixedtime += sc->data[SC_MANDRAGORA].val3;		// �����Œ�r������
		}
		/* ��� */
		if(sc->data[SC_PARALYZE].timer != -1) {
			fixedtime += sc->data[SC_PARALYZE].val2;		// �����Œ�r������
		}
	}

	if(fixedtime > 0) {
		int reduce_time2 = 0;	// �Œ�r���팸����

		/* ���f�B�E�X */
		if(sd && pc_checkskill(sd,WL_RADIUS)) {
			reduce_time2 += (5 + pc_checkskill(sd,WL_RADIUS) * 5);
		}

		if(sc) {
			/* �T�N�������g */
			if(sc->data[SC_SACRAMENT].timer != -1) {
				if(reduce_time2 < sc->data[SC_SACRAMENT].val2)
					reduce_time2 = sc->data[SC_SACRAMENT].val2;
			}

			/* �_���X�E�B�Y�E�H�[�O */
			if(sc->data[SC_DANCE_WITH_WUG].timer != -1) {
				int val = 20 + sc->data[SC_DANCE_WITH_WUG].val4 * 10;
				if(reduce_time2 < val)
					reduce_time2 = val;
			}
		}

		if(sd) {
			// �J�[�h�ɂ��Œ�r�����ԑ�������
			if(sd->skill_fixcastrate.count > 0) {
				for(i=0; i<sd->skill_fixcastrate.count; i++) {
					if(skillid == sd->skill_fixcastrate.id[i])
						reduce_time2 = (reduce_time2 < sd->skill_fixcastrate.rate[i])? sd->skill_fixcastrate.rate[i]: reduce_time2;
				}
			}
			reduce_time2 = ((reduce_time2 < sd->fixcastrate)? sd->fixcastrate: reduce_time2) + sd->fixcastrate_;
		}

		if(sc) {
			/* �t���X�g�~�X�e�B */
			if(sc->data[SC_FROSTMISTY].timer != -1)
				reduce_time2 -= 15;

			/* �\�Z�� */
			if(sc->data[SC_IZAYOI].timer != -1)
				reduce_time2 += 100;
		}

		fixedtime = fixedtime * (100 - reduce_time2) / 100;
	}

	// �j�����W�����v�K�����ً͋}���W�̉r������2�{
	if(sd && skillid == GD_EMERGENCYCALL && pc_checkskill(sd,SU_LOPE) > 0) {
		casttime  <<= 1;
		fixedtime <<= 1;
	}
	if(fixedtime < 0)
		fixedtime = 0;

	return casttime + fixedtime;
}

/*==========================================
 * �f�B���C�v�Z
 *------------------------------------------
 */
int skill_delayfix(struct block_list *bl, int skillid, int skilllv)
{
	struct status_change *sc;
	int delay = skill_get_delay(skillid, skilllv);
	int reduce_time = 0;	// �팸����

	nullpo_retr(0, bl);

	if(skillid == SA_MAGICROD)
		return 0;
	if(bl->type == BL_MOB) // MOB�̓X�L���f�B���C0
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
					if(battle_config.delay_dependon_dex) {	// dex�̉e�����v�Z����
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
					/* �u���M�̎� */
					if(sc->data[SC_POEMBRAGI].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI].val1 * rate + sc->data[SC_POEMBRAGI].val2 * 2
							+ (sc->data[SC_POEMBRAGI].val3 & 0xffff));
					} else if(sc->data[SC_POEMBRAGI_].timer != -1) {
						int rate = (sc->data[SC_POEMBRAGI_].val1 < 10)? 3: 5;
						reduce_time += (sc->data[SC_POEMBRAGI_].val1 * rate + sc->data[SC_POEMBRAGI_].val2 * 2
							+ (sc->data[SC_POEMBRAGI_].val3 & 0xffff));
					}
					if(sc->data[SC_SOULDIVISION].timer != -1) {		// ���̕���
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
 * �N�[���_�E���v�Z
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
		if(skillid == SU_TUNABELLY && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// ��g��
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
 * �u�����f�B�b�V���X�s�A �����͈͌���
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
 * �u�����f�B�b�V���X�s�A �������� �͈͊g��
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
 * �ʃX�L���̊֐�
 */

/*==========================================
 * �f�B�{�[�V�����L���̑��m�F
 *------------------------------------------
 */
void skill_devotion(struct map_session_data *msd)
{
	int n;

	nullpo_retv(msd);

	for(n=0; n<5; n++) {
		if(msd->dev.val1[n]) {
			struct map_session_data *sd = map_id2sd(msd->dev.val1[n]);
			// ���肪������Ȃ� or ������f�B�{���Ă�̂���������Ȃ� or ����������Ă�
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
 * ��f�B�{�[�V���������������̋����`�F�b�N
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
 * �N���Z�����������̋����`�F�b�N
 *------------------------------------------
 */
int skill_devotion3(struct map_session_data *msd,int target_id)
{
	struct map_session_data *sd;

	nullpo_retr(1, msd);

	if((sd = map_id2sd(target_id)) == NULL)
		return 1;

	if(unit_distance(&msd->bl, &sd->bl) > pc_checkskill(msd,CR_DEVOTION) + 6) {	// ���e�͈͂𒴂��Ă�
		int n;
		for(n=0; n<5; n++) {
			if(msd->dev.val1[n] == sd->bl.id) {
				if(msd->dev.val2[n]) {
					msd->dev.val2[n] = 0;	// ���ꂽ���́A����؂邾��
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
 * �}���I�l�b�g�傪���������̋����`�F�b�N
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

	if(unit_distance(&sd->bl, &tsd->bl) > 7) {	// ���e�͈͂𒴂��Ă�
		status_change_end(&sd->bl,SC_MARIONETTE,-1);
		return 1;
	}

	return 0;
}

/*==========================================
 * ��}���I�l�b�g�����������̋����`�F�b�N
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
 * �V���h�E�t�H�[���傪���������̋����`�F�b�N
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

	if(unit_distance(&sd->bl, &tsd->bl) > 11) {	// ���e�͈͂𒴂��Ă�
		status_change_end(&sd->bl,SC__SHADOWFORM,-1);
		return 1;
	}

	return 0;
}

/*==========================================
 * ��V���h�E�t�H�[�������������̋����`�F�b�N
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
 * �I�[�g�X�y��
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

	status_change_start(&sd->bl,SC_AUTOSPELL,skilllv,skillid,maxlv,0,	// val1:�X�L��ID val2:�g�p�ő�Lv
		skill_get_time(SA_AUTOSPELL,skilllv),0);// �ɂ��Ă݂�����bscript�������Ղ��E�E�E�H

	return;
}

/*==========================================
 * �M�����O�X�^�[�p���_�C�X����уe�R���x��
 * ���菈�����菈��
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
		// ���������̏���
		int c = map_foreachinarea(skill_sit_count,sd->bl.m,
			sd->bl.x-1,sd->bl.y-1,
			sd->bl.x+1,sd->bl.y+1,BL_PC,flag);
		if(c > 1) {
			// ������������ʕt�^
			map_foreachinarea(skill_sit_in,sd->bl.m,
				sd->bl.x-1,sd->bl.y-1,
				sd->bl.x+1,sd->bl.y+1,BL_PC,flag);
		}
	} else {
		// �����オ�����Ƃ��̏���
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
 * �����W���[�N�E�X�N���[�����菈��(foreachinarea)
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

	if(src == bl)	// �����ɂ͌����Ȃ�
		return 0;

	skill_additional_effect(src,bl,skillnum,skilllv,BF_MISC,tick);

	return 0;
}

/*==========================================
 * �]���X�L�����H
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
 * �G�̃X�L�����H
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
 * �A�u���J�_�u���̎g�p�X�L������(����X�L�����_���Ȃ�0��Ԃ�)
 *------------------------------------------
 */
static int skill_abra_dataset(struct map_session_data *sd, int skilllv)
{
	int skill = atn_rand()%MAX_SKILL_ABRA_DB;

	nullpo_retr(0, sd);

	// �Z�[�W�̓]���X�L���g�p�������Ȃ�
	if( battle_config.extended_abracadabra == 0 &&
	    sd->s_class.upper == PC_UPPER_NORMAL &&
	    skill_upperskill(skill_abra_db[skill].nameid) )
		return 0;

	// db�Ɋ�Â����x���E�m������
	if(skill_abra_db[skill].req_lv > skilllv || atn_rand()%10000 >= skill_abra_db[skill].per)
		return 0;
	// NPC�E�����E�{�q�E�A�C�e���X�L���̓_��
	if( skill_mobskill( skill_abra_db[skill].nameid ) ||
	   (skill_abra_db[skill].nameid >= WE_BABY && skill_abra_db[skill].nameid <= WE_CALLBABY))
		return 0;

	// ���t�X�L���̓_��
	if (skill_get_unit_flag(skill_abra_db[skill].nameid, skilllv)&UF_DANCE)
		return 0;

	return skill_abra_db[skill].nameid;
}

/*==========================================
 * �o�W���J�̃Z����ݒ肷��
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
 * �o�W���J�̔������~�߂�
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
 * �����h�v���e�N�^�[�`�F�b�N(foreachinarea)
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
		if(alive && unit->group->skill_id == WZ_ICEWALL)	// �A�C�X�E�H�[��������Z���ɂ̓����h�v���e�N�^�[���o�Ȃ�
			(*alive)=0;
		switch(unit->group->skill_id) {
		case WZ_ICEWALL:	// �A�C�X�E�H�[��
		case HT_SKIDTRAP:	// �X�L�b�h�g���b�v
		case HT_LANDMINE:	// �����h�}�C��
		case HT_ANKLESNARE:	// �A���N���X�l�A
		case HT_SHOCKWAVE:	// �V���b�N�E�F�[�u�g���b�v
		case HT_SANDMAN:	// �T���h�}��
		case HT_FLASHER:	// �t���b�V���[
		case HT_FREEZINGTRAP:	// �t���[�W���O�g���b�v
		case HT_BLASTMINE:	// �u���X�g�}�C��
		case HT_CLAYMORETRAP:	// �N���C���A�g���b�v
		case MA_SKIDTRAP:	// �X�L�b�h�g���b�v
		case MA_LANDMINE:	// �����h�}�C��
		case MA_SANDMAN:	// �T���h�}��
		case MA_FREEZINGTRAP:	// �t���[�W���O�g���b�v
		case BA_DISSONANCE:	// �s���a��
		case BA_WHISTLE:	// ���J
		case BA_ASSASSINCROSS:	// �[�z�̃A�T�V���N���X
		case BA_POEMBRAGI:	// �u���M�̎�
		case BA_APPLEIDUN:	// �C�h�D���̗ь�
		case DC_UGLYDANCE:	// ��������ȃ_���X
		case DC_HUMMING:	// �n�~���O
		case DC_DONTFORGETME:	// ����Y��Ȃ��Łc
		case DC_FORTUNEKISS:	// �K�^�̃L�X
		case DC_SERVICEFORYOU:	// �T�[�r�X�t�H�[���[
		case CG_HERMODE:	// �w�����[�h�̏�
		case NPC_EVILLAND:	// �C�[�r�������h
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
		if(alive && unit->group->skill_id == WZ_ICEWALL) {	// �A�C�X�E�H�[��������Z���̓I�u�W�F�N�g�X�L�����o�Ȃ�
			if(skillid != AL_TELEPORT)
				(*alive)=0;
		}
	}
	return 0;
}

/*==========================================
 * �C�h�D���̗ь�̉񕜏���(foreachinarea)
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
 * �^���̃^���b�g�J�[�h
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

	// �^���̗ւ���100%����
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

	if(wheel == 0)	// �^���̗ւ��ƃG�t�F�N�g�Ȃ��H
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
			/* ����(The Fool) - SP��0�ɂȂ� */
			if(tsd) {
				tsd->status.sp = 0;
				clif_updatestatus(tsd,SP_SP);
			}
			break;
		case 1:
			/* ���@�t(The Magician) - 30�b��Matk�������ɗ����� */
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
				status_change_start(target,SC_THE_MAGICIAN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		case 2:
			/* �����c(The High Priestess) - ���ׂĂ̕⏕���@�������� */
			status_change_release(target,0x40);
			break;
		case 3:
			/* ���(The Chariot) - �h��͖�����1000�_���[�W �h������_���Ɉ�j�󂳂�� */
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
			/* ��(Strength) - 30�b��ATK�������ɗ����� */
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
				status_change_start(target,SC_STRENGTH,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
		case 5:
			/* ���l(The Lovers) - �ǂ����Ƀe���|�[�g������- HP��2000�񕜂���� */
			unit_heal(target, 2000, 0, 0, 0);
			// �e���|�[�g�s�̏ꍇ�͉񕜂̂�
			if(tsd) {
				if(!map[tsd->bl.m].flag.noteleport)
					pc_randomwarp(tsd,0);
			} else if(tmd) {
				if(!map[tmd->bl.m].flag.monster_noteleport)
					mob_warp(tmd,tmd->bl.m,-1,-1,0);
			}
			break;
		case 6:
			/* �^���̗�(Wheel of Fortune) - �����_���ɑ��̃^���b�g�J�[�h�񖇂̌��ʂ𓯎��ɗ^���� */
			if(wheel > 0 && wheel < 50) {	// ����1�x���s�i50��őł��؂�j
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,wheel+1);
			} else {			// �Q���s
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,1);
				skill_tarot_card_of_fate(src,target,skillid,skilllv,tick,1);
			}
			break;
		case 7:
			/* �݂�ꂽ�j(The Hanged Man) - �����A�����A�Ή��̒������������������� */
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
			{
				switch(atn_rand()%3)
				{
					case 0:	// ����
						if(atn_rand() % 10000 < status_change_rate(target,SC_SLEEP,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_SLEEP,7,0,0,0,skill_get_time2(NPC_SLEEPATTACK,7),0,tick+status_get_amotion(src));
						break;
					case 1:	// ����
						if(atn_rand() % 10000 < status_change_rate(target,SC_FREEZE,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_FREEZE,7,0,0,0,skill_get_time2(MG_FROSTDIVER,7),0,tick+status_get_amotion(src));
						break;
					case 2:	// �Ή�
						if(atn_rand() % 10000 < status_change_rate(target,SC_STONE,10000,status_get_lv(src)))
							status_change_pretimer(target,SC_STONE,7,0,0,0,skill_get_time2(MG_STONECURSE,7),0,tick+status_get_amotion(src));
						break;
				}
			}
			break;
		case 8:
			/* ���_(Death) - �� + �R�[�} + �łɂ����� */
			if(atn_rand() % 10000 < status_change_rate(target,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(target,SC_POISON,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_POISON,7,0,0,0,skill_get_time2(TF_POISON,7),0,tick+status_get_amotion(src));
			// �R�[�}
			if(tsd) {
				tsd->status.hp = 1;
				clif_updatestatus(tsd,SP_HP);
			} else if(tmd && !(status_get_mode(&tmd->bl)&MD_BOSS)) {	// �{�X�����ȊO
				tmd->hp = 1;
			}
			break;
		case 9:
			/* �ߐ�(Temperance) - 30�b�ԍ����ɂ����� */
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
				if(atn_rand() % 10000 < status_change_rate(target,SC_CONFUSION,10000,status_get_lv(src)))
					status_change_pretimer(target,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
			break;
		case 10:
			/* ����(The Devil) - �h��͖���6666�_���[�W + 30�b��ATK�����AMATK�����A�� */
			if(atn_rand() % 10000 < status_change_rate(target,SC_CURSE,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0,tick+status_get_amotion(src));
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
				status_change_start(target,SC_THE_DEVIL,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			unit_fixdamage(src,target,0, 0, 0,6666,1, 4, 0, 0);
			break;
		case 11:
			/* ��(The Tower) - �h��͖���4444�Œ�_���[�W */
			unit_fixdamage(src,target,0, 0, 0,4444,1, 4, 0, 0);
			break;
		case 12:
			/* ��(The Star) - ������� ���Ȃ킿�A5�b�ԃX�^���ɂ����� */
			if(atn_rand() % 10000 < status_change_rate(target,SC_STUN,10000,status_get_lv(src)))
				status_change_pretimer(target,SC_STUN,7,0,0,0,5000,0,tick+status_get_amotion(src));
			break;
		case 13:
			/* ���z(The Sun) - 30�b��ATK�AMATK�A����A�����A�h��͂��S��20%���������� */
			if(!(status_get_mode(target)&MD_BOSS))	// �{�X�����ȊO
				status_change_start(target,SC_THE_SUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			break;
	}
	return 1;
}

/*==========================================
 * �w��͈͓���src�ɑ΂��ėL���ȃ^�[�Q�b�g��bl�̐��𐔂���(foreachinarea)
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
 * �g���b�v�͈͏���(foreachinarea)
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
			case UNT_FIREPILLAR_ACTIVE:	/* �t�@�C�A�[�s���[(������) */
				if(battle_config.firepillar_splash_on) {
					int i;
					for(i = 0; i < splash_count; i++)
						battle_skill_attack(BF_MAGIC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				} else {
					battle_skill_attack(BF_MAGIC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				}
				break;
			case UNT_SANDMAN:	/* �T���h�}�� */
			case UNT_FLASHER:	/* �t���b�V���[ */
			case UNT_SHOCKWAVE:	/* �V���b�N�E�F�[�u�g���b�v */
			case UNT_MAGENTATRAP:		/* �}�[���^�g���b�v */
			case UNT_COBALTTRAP:		/* �R�o���g�g���b�v */
			case UNT_MAIZETRAP:			/* ���C�Y�g���b�v */
			case UNT_VERDURETRAP:		/* ���F���f���[���g���b�v */
				skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
				break;
			case UNT_BLASTMINE:	/* �u���X�g�}�C�� */
			case UNT_CLAYMORETRAP:	/* �N���C���A�g���b�v */
				if(battle_config.trap_splash_on) {
					int i;
					for(i = 0; i < splash_count; i++) {
						battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
					}
				} else {
					battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				}
				break;
			case UNT_GROUNDDRIFT_WIND:	/* �O���E���h�h���t�g */
			case UNT_GROUNDDRIFT_DARK:
			case UNT_GROUNDDRIFT_POISON:
			case UNT_GROUNDDRIFT_WATER:
			case UNT_GROUNDDRIFT_FIRE:
			case UNT_GROUNDDRIFT_NEUTRAL:
				battle_skill_attack(BF_WEAPON,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
				break;
			case UNT_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
				break;
			case UNT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				battle_skill_attack(BF_WEAPON,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				break;
			case UNT_FIRINGTRAP:	/* �t�@�C�A�����O�g���b�v */
			case UNT_ICEBOUNDTRAP:	/* �A�C�X�o�E���h�g���b�v */
			case UNT_CLUSTERBOMB:	/* �N���X�^�[�{�� */
				clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
				battle_skill_attack(BF_MISC,ss,&unit->bl,bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
				break;
			case UNT_REVERBERATION:	/* �U���c�� */
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
 * �X�e�[�^�X�ُ�
 *----------------------------------------------------------------------------
 */

/* �N���[�L���O�����i����Ɉړ��s�\�n�т����邩�j */
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
		sc->option &= ~OPTION_CLOAKING;	/* �O�̂��߂̏��� */

	return 1;
}

/*==========================================
 * �f�B�e�B�N�g���ʁi�B��Ă��鑊���\���j
 *------------------------------------------
 */
int skill_detect(struct block_list *bl)
{
	int result = 0;
	struct status_change *sc = NULL;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(sc) {
		// �n�C�f�B���O
		if(sc->data[SC_HIDING].timer != -1) {
			status_change_end(bl, SC_HIDING, -1);
			result = 1;
		}
		// �N���[�L���O
		if(sc->data[SC_CLOAKING].timer != -1) {
			status_change_end(bl, SC_CLOAKING, -1);
			result = 1;
		}
		// �C���r�W�u��
		if(sc->data[SC_INVISIBLE].timer != -1) {
			status_change_end(bl, SC_INVISIBLE, -1);
			result = 1;
		}
		// �N���[�L���O�G�N�V�[�h
		if(sc->data[SC_CLOAKINGEXCEED].timer != -1) {
			status_change_end(bl, SC_CLOAKINGEXCEED, -1);
			result = 1;
		}
		// �J���t���[�W��
		if(sc->data[SC_CAMOUFLAGE].timer != -1) {
			status_change_end(bl, SC_CAMOUFLAGE, -1);
			result = 1;
		}
		// �V���h�E�t�H�[���i�f�B�e�N�g�ϐ�����j
		if(sc->data[SC__SHADOWFORM].timer != -1 && atn_rand()%100 < 100 - sc->data[SC__SHADOWFORM].val1 * 10) {
			status_change_end(bl, SC__SHADOWFORM, -1);
			result = 1;
		}
		// ��
		if(sc->data[SC_NEWMOON].timer != -1) {
			status_change_end(bl, SC_NEWMOON, -1);
			result = 1;
		}
	}

	return result;
}

/*
 *----------------------------------------------------------------------------
 * �X�L�����j�b�g
 *----------------------------------------------------------------------------
 */

/*==========================================
 * ���t/�_���X����߂�
 * flag 1�ō��t���Ȃ瑊���Ƀ��j�b�g��C����
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

	group = map_id2sg(sc->data[SC_DANCING].val2); // �_���X�̃X�L�����j�b�gID��val2�ɓ����Ă�

	if(sd && group && sc->data[SC_DANCING].val4) { // ���t���f
		struct map_session_data* dsd = map_id2sd(sc->data[SC_DANCING].val4); // ������sd�擾
		if(flag) { // ���O�A�E�g�ȂǕЕ��������Ă����t���p�������
			if(dsd && src->id == group->src_id) { // �O���[�v�������Ă�PC��������
				group->src_id = dsd->bl.id; // �����ɃO���[�v��C����
				linkdb_insert( &dsd->ud.skillunit, INT2PTR(group->bl.id), group );
				linkdb_erase( &sd->ud.skillunit, INT2PTR(group->bl.id) );
				if(flag&1) // ���O�A�E�g
					dsd->sc.data[SC_DANCING].val4 = 0; // �����̑�����0�ɂ��č��t�I�����ʏ�̃_���X���
				if(flag&2) // �n�G��тȂ�
					return; // ���t���_���X��Ԃ��I�������Ȃ����X�L�����j�b�g�͒u���Ă��ڂ�
			} else if(dsd && dsd->bl.id == group->src_id) { // �������O���[�v�������Ă���PC��������(�����̓O���[�v�������Ă��Ȃ�)
				if(flag&1) // ���O�A�E�g
					dsd->sc.data[SC_DANCING].val4 = 0; // �����̑�����0�ɂ��č��t�I�����ʏ�̃_���X���
				if(flag&2) // �n�G��тȂ�
					return; // ���t���_���X��Ԃ��I�������Ȃ����X�L�����j�b�g�͒u���Ă��ڂ�
			}
			status_change_end(src, SC_DANCING, -1);	// �����̃X�e�[�^�X���I��������
			// �����ăO���[�v�͏����Ȃ��������Ȃ��̂ŃX�e�[�^�X�v�Z������Ȃ��H
			return;
		} else {
			if(dsd && src->id == group->src_id) { // �O���[�v�������Ă�PC���~�߂�
				status_change_end(&dsd->bl, SC_DANCING, -1);// ����̃X�e�[�^�X���I��������
			}
			else if(dsd && dsd->bl.id == group->src_id) { // �������O���[�v�������Ă���PC���~�߂�(�����̓O���[�v�������Ă��Ȃ�)
				status_change_end(src, SC_DANCING, -1);// �����̃X�e�[�^�X���I��������
			}
		}
	}
	if(flag&2 && sd && group) { // �n�G�Ŕ�񂾂Ƃ��Ƃ��̓��j�b�g�����
		skill_unit_move_unit_group(group, sd->bl.m, (sd->ud.to_x - sd->bl.x), (sd->ud.to_y - sd->bl.y));
		return;
	}
	if(group)
		skill_delunitgroup(group);
	if(sd)
		status_calc_pc(sd,0);
}

/*==========================================
 * �w�����[�h�̏�`�F�b�N
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
 * �K���o���e�C���ɂ�郆�j�b�g�폜
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
 * �X�L�����j�b�g������
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
 * �X�L�����j�b�g�폜
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

	/* onlimit�C�x���g�Ăяo�� */
	skill_unit_onlimit(unit,tick);

	/* onout�C�x���g�Ăяo�� */
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
 * �X�L�����j�b�g�O���[�v������
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
 * �X�L�����j�b�g�O���[�v�폜
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

	// �_���X�X�L���̓_���X��Ԃ���������
	if(skill_get_unit_flag(group->skill_id,group->skill_lv)&UF_DANCE) {
		if(src)
			status_change_end(src,SC_DANCING,-1);
	}

	// ��Ԉُ�Ƀ��j�b�g�O���[�v���ۑ�����Ă���ꍇ�̓N���A����
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

	// ��Ԉُ�Ƀ��j�b�g�O���[�v���ۑ�����Ă���ꍇ�̓N���A����
	switch(group->skill_id) {
	case SG_SUN_WARM:	// ���z�̉�����
	case SG_MOON_WARM:	// ���̉�����
	case SG_STAR_WARM:	// ���̉�����
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
			// ������Ȃ�����
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
	map_freeblock(group->unit);	/* free()�̑ւ�� */
	map_delobject(group->bl.id);

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�O���[�v�S�폜
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
 * �X�L�����j�b�g�^�C�}�[���������p(foreachinarea)
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

	// �ǔ����h�~�̎ː��`�F�b�N
	if(!path_search_long(NULL,bl->m,bl->x,bl->y,unit->bl.x,unit->bl.y))
		return 0;

	skill_unit_onplace_timer(unit,bl,tick);

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�^�C�}�[�����p(foreachobject)
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

	// �X�L�����j�b�g��tick���^�C�}������葁���ꍇ�͎������ɉ�
	if(DIFF_TICK(tick,group->tick) < 0)
		return 0;

	range = unit->range;

	/* onplace_timer�C�x���g�Ăяo�� */
	if(range >= 0 && group->interval != -1)
	{
		map_foreachinarea(skill_unit_timer_sub_onplace, bl->m,
			bl->x-range,bl->y-range,bl->x+range,bl->y+range,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),unit,tick);
		if(!unit->alive)
			return 0;
		// �}�O�k�X�͔����������j�b�g�͍폜����
		if(group->skill_id == PR_MAGNUS && unit->val2) {
			skill_delunit(unit);
			return 0;
		}
	}

	// �C�h�D���̗ь�ɂ���
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

	// ��褓��̃J�E���g���Z
	if(group->unit_id == UNT_TOTEM_OF_TUTELARY && DIFF_TICK(tick,group->tick)%group->interval < SKILLUNITTIMER_INVERVAL) {
		group->val1++;
	}

	// �o�C�I�����g�N�G�C�N�ƃI�[���u���[���̃����_�����j�b�g�z�u
	if((group->unit_id == UNT_VIOLENT_QUAKE && group->val1 != 4) || (group->unit_id == UNT_ALL_BLOOM && group->val1 != 4)) {
		struct block_list *src = map_id2bl(group->src_id);
		int diff = DIFF_TICK(tick,group->tick);
		// ���Ԑ؂�Ɣ����Ԋu�𔻒�
		if(src && diff < group->limit && diff%group->interval < SKILLUNITTIMER_INVERVAL) {
			int i, max = 1;
			if((group->unit_id == UNT_VIOLENT_QUAKE && group->val1 == 1) ||		// �o�C�I�����g�N�G�C�N�ŃN���C�}�b�N�XLv1
			   (group->unit_id == UNT_ALL_BLOOM && group->val1 == 2)) {			// �I�[���u���[���ŃN���C�}�b�N�XLv2
				max = 2;		// 2�񂸂���
			}

			for(i = 0; i < max; i++ ) {
				int tmpx = bl->x + (atn_rand()%(range*2+1) - range);
				int tmpy = bl->y + (atn_rand()%(range*2+1) - range);
				clif_skill_poseffect(src,group->skill_id+1,-1,tmpx,tmpy,tick);
				skill_unitsetting(src,group->skill_id+1,group->skill_lv,tmpx,tmpy,group->val1);
			}
		}
	}
	// �O���l�[�Y�h���b�s���O�A�~�b�V�����{���o�[�h�A�V�n�����A�V���̃����_���Z���U��
	if(group->unit_id == UNT_GRENADES_DROPPING || group->unit_id == UNT_MISSION_BOMBARD || group->unit_id == UNT_TWINKLING_GALAXY || group->unit_id == UNT_STAR_CANNON) {
		struct block_list *src = map_id2bl(group->src_id);
		int diff = DIFF_TICK(tick,group->tick);
		// ���Ԑ؂�Ɣ����Ԋu�𔻒�
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
		/* ���Ԑ؂�폜 */
		switch(group->unit_id) {
			case UNT_ATTACK_SKILLS:
				if(group->skill_id == HN_METEOR_STORM_BUSTER) {		/* ���e�I�X�g�[���o�X�^�[ */
					int ar = skill_get_unit_range(group->skill_id, group->skill_lv);
					map_foreachinarea(skill_area_sub,
						bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
						map_id2bl(group->src_id),group->skill_id,group->skill_lv,group->tick,BCT_ENEMY|1,
						skill_castend_damage_id);
				}
				break;
			case UNT_WARP_WAITING:	/* ���[�v�|�[�^��(�����O) */
				group->unit_id = UNT_WARP_ACTIVE;
				clif_changelook(bl,LOOK_BASE,group->unit_id);
				group->limit = unit->limit = skill_get_time(group->skill_id,group->skill_lv);
				return 0;
			case UNT_BLASTMINE:		/* �u���X�g�}�C�� */
				group->unit_id = UNT_USED_TRAPS;
				clif_changelook(bl,LOOK_BASE,group->unit_id);
				group->limit = unit->limit = DIFF_TICK(tick+1500,group->tick);
				return 0;

			case UNT_ANKLESNARE:	/* �A���N���X�l�A */
				if(group->val2 > 0) {
					break;
				}
				// fall through
			case UNT_SKIDTRAP:	/* �X�L�b�h�g���b�v */
			case UNT_LANDMINE:	/* �����h�}�C�� */
			case UNT_SHOCKWAVE:	/* �V���b�N�E�F�[�u�g���b�v */
			case UNT_SANDMAN:	/* �T���h�}�� */
			case UNT_FLASHER:	/* �t���b�V���[ */
			case UNT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
			case UNT_TALKIEBOX:	/* �g�[�L�[�{�b�N�X */
				if(unit->val1 <= 0) {
					break;
				}
				// fall through
			case UNT_CLAYMORETRAP:		/* �N���C���A�g���b�v */
			case UNT_MAGENTATRAP:		/* �}�[���^�g���b�v */
			case UNT_COBALTTRAP:		/* �R�o���g�g���b�v */
			case UNT_MAIZETRAP:			/* ���C�Y�g���b�v */
			case UNT_VERDURETRAP:		/* ���F���f���[���g���b�v */
			case UNT_FIRINGTRAP:		/* �t�@�C�A�����O�g���b�v */
			case UNT_ICEBOUNDTRAP:		/* �A�C�X�o�E���h�g���b�v */
			case UNT_ELECTRICSHOCKER:	/* �G���N�g���b�N�V���b�J�[ */
			case UNT_CLUSTERBOMB:		/* �N���X�^�[�{�� */
				if(itemdb_exists(unit->group->val3)) {
					struct block_list *src = map_id2bl(group->src_id);
					if(src && src->type == BL_PC) {
						struct item item_tmp;
						memset(&item_tmp,0,sizeof(item_tmp));
						item_tmp.nameid   = unit->group->val3;
						item_tmp.identify = 1;
						map_addflooritem(&item_tmp,1,bl->m,bl->x,bl->y,0,0,0,0);	// 㩕Ԋ�
					}
				}
				break;
			case UNT_FEINTBOMB:		/* �t�F�C���g�{�� */
				{
					int ar = skill_get_area(group->skill_id, group->skill_lv);
					map_foreachinarea(skill_area_sub,
						bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
						map_id2bl(group->src_id),group->skill_id,group->skill_lv,group->tick,BCT_ENEMY|1,
						skill_castend_damage_id);
				}
				break;
			case UNT_BANDING:	/* �o���f�B���O */
				group->limit = DIFF_TICK(tick,group->tick)+600000;
				return 0;
			case UNT_REVERBERATION:	/* �U���c�� */
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
			case UNT_ALL_BLOOM:		/* �I�[���u���[�� */
				if(group->val1 == 5) {		// �N���C�}�b�N�XLv5�F�������I�������ɒǌ�
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
		/* �ϋv�؂�`�F�b�N */
		switch(group->unit_id) {
			case UNT_ICEWALL:	/* �A�C�X�E�H�[�� */
				unit->val1 -= 5;
				if(unit->val1 <= 0 && unit->limit + group->tick > tick + 700)
					unit->limit = DIFF_TICK(tick+700,group->tick);
				break;
			case UNT_FIREPILLAR_WAITING:	/* �t�@�C�A�[�s���[(�����O) */
			case UNT_SKIDTRAP:	/* �X�L�b�h�g���b�v */
			case UNT_ANKLESNARE:	/* �A���N���X�l�A */
			case UNT_LANDMINE:	/* �����h�}�C�� */
			case UNT_SHOCKWAVE:	/* �V���b�N�E�F�[�u�g���b�v */
			case UNT_SANDMAN:	/* �T���h�}�� */
			case UNT_FLASHER:	/* �t���b�V���[ */
			case UNT_FREEZINGTRAP:	/* �t���[�W���O�g���b�v */
			case UNT_TALKIEBOX:	/* �g�[�L�[�{�b�N�X */
				if(unit->val1 <= 0) {
					if(group->unit_id == UNT_ANKLESNARE && group->val2 > 0) {	// �ߊl���̃A���N���Ȃ瑦���ɍ폜
						skill_delunit(unit);
					} else {
						group->unit_id = UNT_USED_TRAPS;
						group->limit = DIFF_TICK(tick,group->tick)+1500;
					}
				}
				break;
			case UNT_REVERBERATION:	/* �U���c�� */
			case UNT_WALLOFTHORN:	/* �\�[���E�H�[�� */
				if(unit->val1 <= 0)
					skill_delunit(unit);
				break;
		}
	}

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�^�C�}�[����
 *------------------------------------------
 */
static int skill_unit_timer( int tid,unsigned int tick,int id,void *data)
{
	map_foreachobject( skill_unit_timer_sub, BL_SKILL, tick );

	return 0;
}

/*==========================================
 * ���j�b�g�ړ������p(foreachinarea)
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
 * ���j�b�g�ړ�������
 *   flag 0:�ړ��O����(���j�b�g�ʒu�̃X�L�����j�b�g�𗣒E)
 *        1:�ړ��㏈��(���j�b�g�ʒu�̃X�L�����j�b�g�𔭓�)
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
 * �X�L�����j�b�g���̂̈ړ�������
 * �����̓O���[�v�ƈړ���
 *------------------------------------------
 */
int skill_unit_move_unit_group(struct skill_unit_group *group,int m,int dx,int dy)
{
	int i,j,moveblock;
	unsigned int tick = gettick();
	unsigned char m_flag[MAX_SKILL_UNIT_COUNT];	// group->unit_count��MAX_SKILL_UNIT_COUNT���z���邱�Ƃ͂Ȃ�
	struct skill_unit *unit1, *unit2;

	nullpo_retr(0, group);

	if(group->unit_count <= 0)
		return 0;
	if(group->unit == NULL)
		return 0;

	// �ړ��\�ȃX�L���̓_���X�n��㩂ƃt�@�C�A�[�s���[�Ɖ�����̂�
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
	if( group->unit_id == UNT_ANKLESNARE && (battle_config.anklesnare_no_knockbacking || group->val2 > 0) )	// �⑫���̃A���N���͈ړ��s��
		return 0;

	// �ړ��t���O
	memset(m_flag, 0, sizeof(m_flag));

	// ��Ƀt���O��S�����߂�
	//   m_flag
	//     0: �P���ړ�
	//     1: ���j�b�g���ړ�����(���ʒu���烆�j�b�g���Ȃ��Ȃ�)
	//     2: �c�����V�ʒu���ړ���ƂȂ�(�ړ���Ƀ��j�b�g�����݂��Ȃ�)
	//     3: �c��
	for(i=0; i<group->unit_count; i++) {
		unit1= &group->unit[i];
		if(!unit1->alive || unit1->bl.m != m)
			continue;
		for(j=0; j<group->unit_count; j++) {
			unit2 = &group->unit[j];
			if(!unit2->alive)
				continue;
			if(unit1->bl.x + dx == unit2->bl.x && unit1->bl.y + dy == unit2->bl.y) {
				// �ړ���Ƀ��j�b�g�����Ԃ��Ă���
				m_flag[i] |= 0x1;
			}
			if(unit1->bl.x - dx == unit2->bl.x && unit1->bl.y - dy == unit2->bl.y) {
				// ���j�b�g�����̏ꏊ�ɂ���Ă���
				m_flag[i] |= 0x2;
			}
		}
	}
	// �t���O�Ɋ�Â��ă��j�b�g�ړ�
	// �t���O��1��unit��T���A�t���O��2��unit�̈ړ���Ɉڂ�
	j = 0;
	for(i=0; i<group->unit_count; i++) {
		unit1 = &group->unit[i];
		if(!unit1->alive)
			continue;
		if(!(m_flag[i]&0x2)) {
			// ���j�b�g���Ȃ��Ȃ�ꏊ�ŃX�L�����j�b�g�e��������
			map_foreachinarea(skill_unit_effect,unit1->bl.m,
				unit1->bl.x,unit1->bl.y,unit1->bl.x,unit1->bl.y,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),
				&unit1->bl,tick,0);
		}
		if(m_flag[i] == 0) {
			// �P���ړ�
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
			// �t���O��2�̂��̂�T���Ă��̃��j�b�g�̈ړ���Ɉړ�
			for( ; j<group->unit_count; j++) {
				if(m_flag[j] == 2) {
					// �p���ړ�
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
			// �ړ���̏ꏊ�ŃX�L�����j�b�g�𔭓�
			map_foreachinarea(skill_unit_effect,unit1->bl.m,
				unit1->bl.x,unit1->bl.y,unit1->bl.x,unit1->bl.y,(BL_PC|BL_MOB|BL_MERC|BL_ELEM),
				&unit1->bl,tick,1);
		}
	}
	return 0;
}

/*==========================================
 * �ݒu�ς݃X�L�����j�b�g�̐���Ԃ�
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
 * �A�C�e������
 *----------------------------------------------------------------------------
 */

/*==========================================
 * �A�C�e�������\����
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

	// req_skill��0�ȉ��̂Ƃ���req_skilllv�̔�������Ȃ�
	if((req_skill = skill_produce_db[idx].req_skill) > 0 && pc_checkskill(sd,req_skill) < skill_produce_db[idx].req_skilllv)
		return 0;

	for(i=0; i<MAX_PRODUCE_RESOURCE; i++) {
		int amount, count = 0;
		int id = skill_produce_db[idx].mat_id[i];

		if(id <= 0)	// ����ȏ�͍ޗ��v��Ȃ�
			break;
		amount = skill_produce_db[idx].mat_amount[i];
		if((sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB) && sd->skill_menu.lv > 1)
			amount = amount * 10;
		if(amount <= 0)
			amount = 1;	// ���Ղ���Ȃ�����鎞�K�v�ȃA�C�e��

		for(j=0; j<MAX_INVENTORY; j++) {
			if(sd->status.inventory[j].nameid == id) {
				count += sd->status.inventory[j].amount;
				if(count >= amount)
					break;	// ���肽�̂Ō����I��
			}
		}
		if(count < amount)	// �A�C�e��������Ȃ�
			return 0;
	}
	return 1;
}

/*==========================================
 * �A�C�e�������̐����m���v�Z
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

	/* ��{�m�����Z�o����make_per�ɉ��Z */

	switch (skill_produce_db[idx].itemlv)
	{
	case PRD_WEAPON_L1:	// ���퐻��
	case PRD_WEAPON_L2:
	case PRD_WEAPON_L3:
		make_per += sd->status.job_level*20 + dex*10 + luk*10 + skill_lv*500 + pc_checkskill(sd,BS_WEAPONRESEARCH)*100;

		if(pc_search_inventory(sd,989) >= 0)		// �G���y���E���̋��~
			make_per += 1000;
		else if(pc_search_inventory(sd,988) >= 0)	// �����̋��~
			make_per += 500;
		else if(pc_search_inventory(sd,987) >= 0)	// �I���f�I�R���̋��~
			make_per += 300;
		//else if(pc_search_inventory(sd,986) >= 0)	// ���~
		//	make_per += 0:

		if(ele)
			make_per -= 2000;	// �����΂̊m���ቺ
		if(sc > 0)
			make_per -= sc * 1500;	// ���̊m���ቺ

		if(skill_produce_db[idx].itemlv == PRD_WEAPON_L3)
			make_per += pc_checkskill(sd,BS_ORIDEOCON)*100;	// �I���f�I�R�������͎b��

		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;

	case PRD_ORE:		// �z��
		make_per += sd->status.job_level*20 + dex*10 + luk*10 + skill_lv*500;
		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;

	case PRD_PHARMACY:	// �t�@�[�}�V�[
		if(skill_produce_db[idx].nameid == 7142 && pc_checkskill(sd,AM_BIOETHICS) <= 0) {	// �����ϗ����C�����͐�����0
			make_per = 0;
		} else {
			make_per += pc_checkskill(sd,AM_LEARNINGPOTION)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
			if(battle_config.pp_rate != 100)
				make_per = make_per * battle_config.pp_rate/100;
		}
		break;

	case PRD_CDP:		// �f�b�h���[�|�C�Y��
		make_per += dex*40 + luk*20;
		if(battle_config.cdp_rate != 100)
			make_per = make_per * battle_config.cdp_rate/100;
		break;

	case PRD_CONVERTER:	// �R���o�[�^�[
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

	case PRD_COOKING:	// ����
		make_per += sd->skill_menu.lv + sd->status.job_level*20 + dex*20 + luk*10;
		if(battle_config.cooking_rate != 100)
			make_per = make_per * battle_config.cooking_rate/100;
		break;

	/* �ȉ����������� */
	case PRD_SCROLL:	// �X�N���[��
		make_per += sd->skill_menu.lv + sd->status.job_level*10 + int_*10 + dex*10;
		if(battle_config.scroll_produce_rate != 100)
			make_per = make_per * battle_config.scroll_produce_rate/100;
		break;

	case PRD_SYN_POTION:	// �|�[�V��������
		make_per += sd->skill_menu.lv + sd->status.job_level*10 + int_*10 + dex*10 - skill_lv*200;
		if(battle_config.making_rate != 100)
			make_per = make_per * battle_config.making_rate/100;
		break;

	case PRD_COIN:		// �R�C��
	case PRD_NUGGET:	// ��
	case PRD_ORIDEOCON:	// �I���f�I�R������
		make_per += sd->status.base_level*30 + dex*20 + luk*10 + skill_lv*500;
		if(battle_config.wp_rate != 100)
			make_per = make_per * battle_config.wp_rate/100;
		break;
	case PRD_RUNE:		// ���[���X�g�[������
		make_per += skill_lv*200 + sd->status.job_level*20 + (dex + luk)*5;
		break;
	case PRD_NEWPOISON:	// �V�Ő���
		make_per += pc_checkskill(sd,GC_RESEARCHNEWPOISON)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
		break;
	case PRD_MIX_COOKING:	// �~�b�N�X�N�b�L���O
		make_per += 3000 + sd->status.job_level*20 + dex*20 + luk*10;
		break;
	case PRD_MAKEBOMB:	// ���e����
		make_per += 5000 + sd->status.job_level*20 + dex*20 + luk*10;
		break;
	case PRD_S_PHARMACY:	// �X�y�V�����t�@�[�}�V�[
		make_per += pc_checkskill(sd,AM_LEARNINGPOTION)*100 + skill_lv*300 + sd->status.job_level*20 + dex*10 + luk*10 + int_*5;
		if(battle_config.pp_rate != 100)
			make_per = make_per * battle_config.pp_rate/100;
		break;
	case PRD_M_MACHINE:	// ���u����
	case PRD_BIONIC_PHARMACY:	// �o�C�I�j�b�N�t�@�[�}�V�[
		make_per = 10000;
		break;
	}

	if(make_per < 1)
		make_per = 1;

	// �{�q�̐�����70%
	if(pc_isbaby(sd))
		make_per = make_per * 70/100;

	return make_per;
}

/*==========================================
 * �t�@�[�}�V�[�ɂ�郉���L���O�|�C���g�v�Z
 *------------------------------------------
 */
static int skill_am_ranking_point(struct map_session_data *sd, int nameid, int success)
{
	int point = 0;

	nullpo_retr(0, sd);

	// ������
	if(success) {
		// �S�Ẵt�@�[�}�V�[�Ώېݒ肩�A�X�����n�̏ꍇ�ɏ���
		if(battle_config.pharmacy_get_point_type || nameid == 545 || nameid == 546 || nameid == 547) {
			// �A������������
			sd->am_pharmacy_success++;
			if(sd->am_pharmacy_success > 10) {
				sd->am_pharmacy_success = 10;
			}
			// +10���������獇�v�|�C���g+64?
			// ���� �K�萬�������ƂɃ|�C���g��Ⴆ��悤�ɐݒ�
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
	} else {	// ���s��
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
 * �A�C�e������
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

	if(!skill_can_produce_mix(sd,idx,-1)) {	/* �����s�� */
		if(sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB)
			clif_skill_message(sd, sd->skill_menu.id, 808);	// �ޗ�������܂���B
		return;
	}

	slot[0] = slot1;
	slot[1] = slot2;
	slot[2] = slot3;

	/* ���ߍ��ݏ��� */
	for(i=0, sc=0, ele=0; i<3; i++) {
		int j;
		if(slot[i] <= 0)
			continue;
		j = pc_search_inventory(sd,slot[i]);
		if(j < 0)	/* �s���p�P�b�g(�A�C�e������)�`�F�b�N */
			continue;
		if(slot[i] == 1000) {	/* ���̂����� */
			pc_delitem(sd,j,1,1,1);
			sc++;
			cnt++;
		}
		if(slot[i] >= 994 && slot[i] <= 997 && ele == 0) {	/* ������ */
			static const int ele_table[4] = { ELE_FIRE, ELE_WATER, ELE_WIND, ELE_EARTH };
			pc_delitem(sd,j,1,1,1);
			ele = ele_table[slot[i]-994];
			cnt++;
		}
	}

	type = skill_produce_db[idx].itemlv;

	if(type == PRD_RUNE) {
		i = pc_search_inventory(sd,nameid);
		if(i >= 0 && sd->status.inventory[i].amount >= 20 ) {	/* �쐬�O�ɏ������E���𒴂��Ă��� */
			clif_msgstringtable(sd, 0x61b);	// �ő及���ʂ�葽�����[���X�g�[�����쐬���邱�Ƃ͂ł��܂���B
			return;
		}
	}

	/* �ޗ����� */
	for(i=0; i<MAX_PRODUCE_RESOURCE; i++) {
		int amount;
		int id = skill_produce_db[idx].mat_id[i];

		if(id <= 0)	// ����ȏ�͍ޗ��v��Ȃ�
			break;
		amount = skill_produce_db[idx].mat_amount[i];	/* �K�v�Ȍ� */
		if((sd->skill_menu.id == GN_MIX_COOKING || sd->skill_menu.id == GN_MAKEBOMB) && sd->skill_menu.lv > 1)
			amount = amount * 10;
		do {	/* �Q�ȏ�̃C���f�b�N�X�ɂ܂������Ă��邩������Ȃ� */
			int j, c = 0;

			j = pc_search_inventory(sd,id);
			if(j >= 0) {
				c = sd->status.inventory[j].amount;
				if(c > amount)
					c = amount;	/* ����Ă��� */
				pc_delitem(sd,j,c,0,1);
			} else {
				if(battle_config.error_log)
					printf("skill_produce_mix: material item error\n");
				return;
			}
			amount -= c;	/* �܂�����Ȃ������v�Z */
		} while(amount > 0);	/* �ޗ��������܂ŌJ��Ԃ� */
	}

	if(atn_rand()%10000 < skill_calc_produce_rate(sd, idx, sc, ele) || type == PRD_S_PHARMACY) {	// �m������
		/* ���� */
		struct item tmp_item;
		int amount = 1;
		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid   = nameid;
		tmp_item.amount   = 1;
		tmp_item.identify = 1;

		if(type == PRD_WEAPON_L1 || type == PRD_WEAPON_L2 || type == PRD_WEAPON_L3)
		{
			tmp_item.card[0] = 0x00ff;					// ��������t���O
			tmp_item.card[1] = ((sc * 5) << 8) + ele;			// �����΂Ɛ�
			*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// �L����ID
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
				*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// �L����ID
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
				clif_produceeffect(sd,2,nameid);	/* ����G�t�F�N�g */
				clif_misceffect(&sd->bl,5);		/* ���l�ɂ�������ʒm */
				break;
			}
			case PRD_CDP:
			case PRD_CONVERTER:
			case PRD_SYN_POTION:
				clif_produceeffect(sd,2,nameid);	/* �b��Ő���G�t�F�N�g */
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
				clif_produceeffect(sd,0,nameid);	/* ���퐻���G�t�F�N�g */
				clif_misceffect(&sd->bl,3);
				break;
			case PRD_ORE:
			case PRD_COIN:
			case PRD_NUGGET:
			case PRD_ORIDEOCON:
				clif_produceeffect(sd,0,nameid);	/* ���퐻���G�t�F�N�g */
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
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// �������܂����B
				break;
			case PRD_MIX_COOKING:
				if(sd->skill_menu.lv > 1)
					amount = 1 + atn_rand()%15;
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// �������܂����B
				break;
			case PRD_MAKEBOMB:
				if(sd->skill_menu.lv > 1)
					amount = 5 + atn_rand()%11;
				clif_skill_message(sd, sd->skill_menu.id, 1574);	// �������܂����B
				break;
			case PRD_M_MACHINE:
				amount = 6 + sd->skill_menu.lv + atn_rand()%3;			// �b��F�{���͕��팤��Lv�ABaseLevel,Dex,Luk,Crt�ɉe�����ĕϓ�
				clif_produceeffect(sd,0,nameid);
				clif_misceffect(&sd->bl,3);
				break;
			case PRD_BIONIC_PHARMACY:
				amount = 6 + sd->skill_menu.lv + atn_rand()%3;			// �b��F�{���̓��[�j���O�|�[�V����Lv�ABaseLevel,Int,Luk,Crt�ɉe�����ĕϓ�
				clif_produceeffect(sd,2,nameid);	/* ����G�t�F�N�g */
				clif_misceffect(&sd->bl,5);		/* ���l�ɂ�������ʒm */
				break;
		}
		pc_additem(sd,&tmp_item,amount,false);	// �d�ʃI�[�o�[�Ȃ����
	} else {
		/* ���s */
		switch (type) {
			case PRD_PHARMACY:
				{
					int point = skill_am_ranking_point(sd, nameid, 0);
					if(point > 0) {
						ranking_gain_point(sd,RK_ALCHEMIST,point);
						ranking_setglobalreg(sd,RK_ALCHEMIST);
						ranking_update(sd,RK_ALCHEMIST);
					}
					clif_produceeffect(sd,3,nameid);	/* ���򎸔s�G�t�F�N�g */
					clif_misceffect(&sd->bl,6);		/* ���l�ɂ����s��ʒm */
				}
				break;
			case PRD_CDP:
				clif_produceeffect(sd,3,nameid);	/* �b��Ő���G�t�F�N�g */
				clif_misceffect(&sd->bl,6);		/* ���l�ɂ����s��ʒm */
				pc_heal(sd, -(sd->status.max_hp>>2), 0, 0, 0);
				break;
			case PRD_CONVERTER:
			case PRD_SYN_POTION:
			case PRD_RUNE:
			case PRD_NEWPOISON:
			case PRD_BIONIC_PHARMACY:
				clif_produceeffect(sd,3,nameid);	/* �b��Ő���G�t�F�N�g */
				clif_misceffect(&sd->bl,6);		/* ���l�ɂ����s��ʒm */
				break;
			case PRD_WEAPON_L1:
			case PRD_WEAPON_L2:
			case PRD_WEAPON_L3:
			case PRD_ORE:
			case PRD_COIN:
			case PRD_NUGGET:
			case PRD_ORIDEOCON:
			case PRD_M_MACHINE:
				clif_produceeffect(sd,1,nameid);	/* ���퐻�����s�G�t�F�N�g */
				clif_misceffect(&sd->bl,2);		/* ���l�ɂ����s��ʒm */
				break;
			case PRD_COOKING:
				clif_misceffect2(&sd->bl,609);
				break;
			case PRD_SCROLL:
				clif_misceffect2(&sd->bl,611);
				break;
			case PRD_S_PHARMACY:
				clif_skill_message(sd, sd->skill_menu.id, 1575);	// ���s���܂����B
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
						clif_skill_message(sd, sd->skill_menu.id, 1576);	// ���s���A�S�Ă̍ޗ����Ȃ��Ȃ�܂����B
					} else {
						clif_skill_message(sd, sd->skill_menu.id, 1575);	// ���s���܂����B
					}
					pc_additem(sd,&tmp_item,amount,false);
				}
				break;
			case PRD_MAKEBOMB:
				if(sd->skill_menu.lv > 1)
					clif_skill_message(sd, sd->skill_menu.id, 1576);	// ���s���A�S�Ă̍ޗ����Ȃ��Ȃ�܂����B
				else
					clif_skill_message(sd, sd->skill_menu.id, 1575);	// ���s���܂����B
				break;
		}
	}
	return;
}

/*==========================================
 * �g���C���C�g�t�@�[�}�V�[
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
		return 0;	// ���݂��Ȃ������A�C�e��

	make_per = skill_calc_produce_rate(sd, i, 0, 0);

	for(i=0; i<count; i++) {
		int n = (atn_rand()%10000 < make_per)? 1: 0;
		amount += n;
		point += skill_am_ranking_point(sd, nameid, n);
	}

	if(amount > 0) {
		struct item tmp_item;
		clif_produceeffect(sd,2,nameid);	/* ����G�t�F�N�g */
		clif_misceffect(&sd->bl,5);		/* ���l�ɂ�������ʒm */

		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid   = nameid;
		tmp_item.amount   = amount;
		tmp_item.identify = 1;

		if(battle_config.produce_potion_name_input)
		{
			tmp_item.card[0] = 0x00fe;
			tmp_item.card[1] = 0;
			*((int *)(&tmp_item.card[2])) = sd->status.char_id;	// �L����ID
		}
		pc_additem(sd, &tmp_item, amount,false);	// �d�ʃI�[�o�[�Ȃ����
	} else {
		// ���s
		clif_produceeffect(sd,3,nameid);	/* ���򎸔s�G�t�F�N�g */
		clif_misceffect(&sd->bl,6);		/* ���l�ɂ����s��ʒm */
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
			*((int *)(&tmp_item.card[2]))=sd->status.char_id;	/* �L����ID */
		}
		if((flag = pc_additem(sd,&tmp_item,tmp_item.amount,false))) {
			clif_additem(sd,0,0,flag);
			map_addflooritem(&tmp_item,tmp_item.amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
		}
	}

	return;
}

/*==========================================
 * ����C��
 *------------------------------------------
 */
void skill_repair_weapon(struct map_session_data *sd, int idx)
{
	const int material[5] = { 999, 1002, 998, 999, 756 };	// �|�S�E�S�z�΁E�S�E�|�S�E�I���f�I�R������
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

	if(sd != dstsd) {	// �Ώۂ������łȂ��Ȃ�˒��`�F�b�N
		int range = skill_get_fixed_range(&sd->bl,skillid,1);
		if(!battle_check_range(&sd->bl, &dstsd->bl, range+1)) {
			clif_item_repaireffect(sd, 1, idx);
			return;
		}
	}

	data = dstsd->inventory_data[idx];

	if(data && itemdb_isweapon(data->nameid)) {	// ����
		if(data->wlv >= 1 && data->wlv <= 4)
			itemid = material[data->wlv];
		else
			itemid = material[4];		// ����Lv��5�ȏ�Ȃ�Lv4�Ɠ����ޗ��ɂ��Ă���
	} else {			// �h��
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
 * �|�C�Y�j���O�E�F�|��
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
					clif_msgstringtable(sd, msg[i]);	// [xxx] �Ō��ʂ�����ɕt�^����܂����B
				}
				break;
			}
		}
	}

	return;
}

/*==========================================
 * ���[�f�B���O�X�y���u�b�N
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

					/* �X�L���̏K���`�F�b�N */
					if(pc_checkskill(sd,spell[i]) <= 0) {
						status_change_start(&sd->bl,SC_SLEEP,1,0,0,0,30000,0);
						clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK_LEARN,0,0);
						break;
					}

					slot = skill_get_spellslot(spell[i]);

					/* �X���b�g�̏���`�F�b�N */
					if(sd->freeze_sp_slot + slot > 4 + pc_checkskill(sd,WL_FREEZE_SP) * 4 + sd->status.base_level/10 + sd->status.int_/10) {
						clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK_POINT,0,0);
						break;
					}

					/* �ێ��X�y���̋󂫃`�F�b�N */
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
 * FAW �}�W�b�N�f�R�C
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
					int x = sd->skill_menu.val>>16;		// X���W�͏�ʃo�C�g
					int y = sd->skill_menu.val&0xffff;	// Y���W�͉��ʃo�C�g
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
 * �I�[�g�V���h�E�X�y��
 *------------------------------------------
 */
void skill_autoshadowspell(struct map_session_data *sd, int skillid)
{
	int skilllv;

	nullpo_retv(sd);

	if(skill_db[skill_get_skilldb_id(skillid)].autoshadowspell != 1)
		return;

	if((skilllv = pc_checkskill(sd,skillid)) > 0) {
		/* �V���h�E�I�[�g�X�y���̎g�p�����x���ŃI�[�g�X�y���̃��x�������� */
		int shadowlv = (sd->skill_menu.lv + 1) / 2;

		skilllv = (skilllv > shadowlv)? shadowlv: skilllv;
		status_change_start(&sd->bl,SC__AUTOSHADOWSPELL,sd->skill_menu.lv,skillid,skilllv,0,skill_get_time(SC_AUTOSHADOWSPELL,sd->skill_menu.lv),0);
	}

	return;
}

/*==========================================
 * �`�F���W�}�e���A��
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
				pc_delitem(sd, idx, item_list[k * 2 + 1], 0, 1);	// �A�C�e������
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
			clif_skill_message(sd, GN_CHANGEMATERIAL, 1574);	// �������܂����B
			return;
		}
	}

	clif_skill_message(sd, GN_CHANGEMATERIAL, 1575);	// ���s���܂����B

	return;
}

/*==========================================
 * �G�������^���A�i���C�V�X
 *------------------------------------------
 */
void skill_el_analysis(struct map_session_data *sd, int num, int skilllv, unsigned short *item_list)
{
	int i, nameid, amount, result, addnum, flag;
	struct item tmp_item;

	nullpo_retv(sd);
	nullpo_retv(item_list);

	if(num <= 0) {
		clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
		return;
	}

	for(i = 0; i < num; i++) {
		int idx = item_list[i * 2] - 2;
		if(idx < 0 || idx >= MAX_INVENTORY) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
			return;
		}
		nameid = sd->status.inventory[idx].nameid;
		amount = item_list[i * 2 + 1];
		if(amount <= 0) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
			return;
		}

		switch(nameid) {
			case 994: result = 990; break;	// �t���C���n�[�g > ���b�h�u���b�h
			case 995: result = 991; break;	// �~�X�e�B�b�N�t���[�Y�� > �N���X�^���u���[
			case 996: result = 992; break;	// ���t�E�B���h > �E�B���h�I�u���F���f���[��
			case 997: result = 993; break;	// �O���C�g�l�C�`�� > �C�G���[���C�u
			case 990: result = 994; break;	// ���b�h�u���b�h > �t���C���n�[�g
			case 991: result = 995; break;	// �N���X�^���u���[ > �~�X�e�B�b�N�t���[�Y��
			case 992: result = 996; break;	// �E�B���h�I�u���F���f���[�� > ���t�E�B���h
			case 993: result = 997; break;	// �C�G���[���C�u > �O���C�g�l�C�`��
			default:
				clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
				return;
		}

		switch(skilllv) {
			case 1:		// �G�������^���A�i���C�V�X Lv1
				addnum = amount * (atn_rand()%5 + 5);
				break;
			case 2:		// �G�������^���A�i���C�V�X Lv2
				addnum = amount / 10;
				break;
			default:
				clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
				return;
		}

		if(addnum <= 0) {
			// anti hacker
			clif_skill_message(sd, SO_EL_ANALYSIS, 1575);	// ���s���܂����B
			return;
		}

		pc_delitem(sd, idx, amount, 0, 1);	// �A�C�e������

		memset(&tmp_item, 0, sizeof(tmp_item));
		tmp_item.nameid = result;
		tmp_item.amount = addnum;
		tmp_item.identify = 1;
		if((flag = pc_additem(sd, &tmp_item, tmp_item.amount,false))) {
			clif_additem(sd, 0, 0, flag);
			map_addflooritem(&tmp_item, tmp_item.amount, sd->bl.m, sd->bl.x, sd->bl.y, 0, 0, 0, 0);
		}
	}

	clif_skill_message(sd, SO_EL_ANALYSIS, 1574);	// �������܂����B

	return;
}

/*==========================================
 * �t���[�W���O�X�y���Ŏg�p����X�L���̃X���b�g�����擾
 *------------------------------------------
 */
static int skill_get_spellslot(int skillid)
{
	int slot = 0;

	switch(skillid) {
		case MG_FIREBOLT:		// �t�@�C�A�[�{���g
		case MG_COLDBOLT:		// �R�[���h�{���g
		case MG_LIGHTNINGBOLT:	// ���C�g�j���O�{���g
			slot = 7;
			break;
		case WZ_EARTHSPIKE:		// �A�[�X�X�p�C�N
		case WL_DRAINLIFE:		// �h���C�����C�t
			slot = 8;
			break;
		case MG_THUNDERSTORM:	// �T���_�[�X�g�[��
		case WZ_JUPITEL:		// ���s�e���T���_�[
		case WZ_WATERBALL:		// �E�H�[�^�[�{�[��
		case WZ_HEAVENDRIVE:	// �w�����Y�h���C�u
			slot = 9;
			break;
		case WZ_STORMGUST:		// �X�g�[���K�X�g
		case WZ_VERMILION:		// ���[�h�I�u���@�[�~���I��
		case WZ_METEOR:			// ���e�I�X�g�[��
			slot = 10;
			break;
		case WL_EARTHSTRAIN:	// �A�[�X�X�g���C��
		case WL_CHAINLIGHTNING:	// �`�F�[�����C�g�j���O
		case WL_CRIMSONROCK:	// �N�����]�����b�N
			slot = 12;
			break;
		case WL_COMET:			// �R���b�g
		case WL_TETRAVORTEX:	// �e�g���{���e�b�N�X
			slot = 22;
			break;
	}

	return slot;
}

/*==========================================
 * ���퐸�B
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

	// �s���`�F�b�N
	if( wlv <= 0 ||
	    sd->status.inventory[idx].nameid <= 0 ||
	    sd->status.inventory[idx].identify != 1 ||
	    !sd->inventory_data[idx]->refine )
		return;
	if(sd->status.inventory[idx].refine >= skilllv){
		clif_weapon_refine_res(sd,2,sd->status.inventory[idx].nameid);
		return;
	}

	if(wlv > 4)	// ����Lv5�ȏ��Lv4�Ɠ����Ƃ݂Ȃ�
		wlv = 4;

	// �A�C�e���`�F�b�N
	n = pc_search_inventory(sd,refine_item[wlv]);
	if(n < 0) {
		clif_weapon_refine_res(sd,3,refine_item[wlv]);
		return;
	}

	if(atn_rand()%1000 < status_percentrefinery_weaponrefine(sd,&sd->status.inventory[idx])) {
		// ����
		clif_weapon_refine_res(sd,0,sd->status.inventory[idx].nameid);
		skill_success_weaponrefine(sd,idx);
	} else {
		// ���s
		clif_weapon_refine_res(sd,1,sd->status.inventory[idx].nameid);
		skill_fail_weaponrefine(sd,idx);
	}

	// �A�C�e������
	pc_delitem(sd,n,1,0,1);

	return;
}

/*==========================================
 * ���퐸�B����
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

	// �u���b�N�X�~�X �����l
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
 * ���퐸�B���s
 *------------------------------------------
 */
int skill_fail_weaponrefine(struct map_session_data *sd,int idx)
{
	nullpo_retr(0, sd);

	if(idx < 0)
		return 0;

	sd->status.inventory[idx].refine = 0;
	pc_delitem(sd,idx,1,0,2);
	// ���B���s�G�t�F�N�g�̃p�P�b�g
	clif_refine(sd->fd,1,idx,sd->status.inventory[idx].refine);
	// ���̐l�ɂ����s��ʒm
	clif_misceffect(&sd->bl,2);

	return 0;
}

/*==========================================
 * �×~
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
 * ����
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

	// �{�l�ɂ͓K�p���Ȃ�?
	if(bl->id == tbl->id)
		return 0;
	if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
		return 0;

	skill_blown(src,bl,4);	// ������΂��Ă݂�
	if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,7000,status_get_lv(src)))
		status_change_pretimer(bl,SC_STUN,1,0,0,0,5000,0,gettick()+status_get_amotion(src));

	return 0;
}

/*==========================================
 * �`�F�[�����C�g�j���O�A���Ώ�
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

	// ��������̏ꍇ�͖���
	if(bl->id == tid)
		return 0;

	if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
		return 0;

	if(atn_rand()%1000 < 1000/(++(*c)))
		*tbl = bl;

	return 1;
}

/*==========================================
 * �f�g�l�C�^�[
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

	// �������ݒu�����g���b�v�̂�
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
			ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: ((sg->unit_id == UNT_CLUSTERBOMB)? 1000: 1500);

			// 㩂𔭓�������
			map_foreachinarea(skill_trap_splash,unit->bl.m,
						unit->bl.x-ar,unit->bl.y-ar,
						unit->bl.x+ar,unit->bl.y+ar,
						(BL_CHAR|BL_SKILL),unit,sg->tick,1);

			// �N������㩂̌㏈��
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
				sg->val2  = -1; // ����
			}
			break;
	}
	return 0;
}

/*==========================================
 * ���C���X�g�[��
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

	/* �͈͓��Ƀ��C���X�g�[�������݂��邩�H */
	if(src && unit->group->skill_id == SC_MAELSTROM) {
		int ar = skill_get_unit_range(unit->group->skill_id, unit->group->skill_lv);
		/* �͈͓��Ɏg�p�҂����݂��邩 */
		if((src->m == bl->m) && (src->x >= bl->x-ar) && (src->x <= bl->x+ar) && (src->y >= bl->y-ar) && (src->y <= bl->y+ar)) {
			(*alive)=0;

			/* �g�p�҂�PC�̏ꍇ */
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
 * �g�����v��
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
			ar = skill_get_area(sg->skill_id,sg->skill_lv);		// ���ʔ͈͂�skill_db��area�Q��
			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: ((sg->unit_id == UNT_CLUSTERBOMB)? 1000: 1500);

			// 㩂𔭓�������
			map_foreachinarea(skill_trap_splash,unit->bl.m,
						unit->bl.x-ar,unit->bl.y-ar,
						unit->bl.x+ar,unit->bl.y+ar,
						(BL_CHAR|BL_SKILL),unit,sg->tick,1);

			// �N������㩂̌㏈��
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
				sg->val2  = -1; // ����
			}
			break;
		default:
			skill_delunit(unit);
			break;
	}
	return 0;
}

/*==========================================
 * �h�~�j�I���C���p���X
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
 * �t�@�C�A�[�G�N�X�p���V����
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
		case 1:		// ��
			sg->val2 = 1;
			sg->limit = unit->limit += 10000;
			break;
		case 2:		// ����
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-2,bl->y-2,bl->x+2,bl->y+2,(BL_CHAR|BL_SKILL),
				src,sg->skill_id,sg->skill_lv,tick,(0x0f<<20)|BCT_ENEMY|2,
				skill_castend_damage_id);
			skill_delunitgroup(sg);
			break;
		case 3:		// ����
			sg->unit_id = UNT_FIRE_EXPANSION_SMOKE_POWDER;
			sg->target_flag = skill_get_unit_target(GN_FIRE_EXPANSION_SMOKE_POWDER);
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			break;
		case 4:		// �×܃K�X
			sg->unit_id = UNT_FIRE_EXPANSION_TEAR_GAS;
			clif_changelook(bl,LOOK_BASE,sg->unit_id);
			break;
		case 5:		// ���_
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
 * �t���b�J�[
 *------------------------------------------
 */
static int skill_flicker( struct block_list *bl, va_list ap )
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

		// 㩂𔭓�������
		map_foreachinarea(skill_area_sub,
			bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
			src,RL_B_FLICKER_ATK,sg->skill_lv,tick,(0x0f<<20)|BCT_ENEMY|0x0500,
			skill_castend_damage_id);

		// �N������㩂̌㏈��
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(bl,LOOK_BASE,sg->unit_id);
		sg->limit = DIFF_TICK(gettick(),sg->tick) + 1500;
	}
	return 0;
}

/*==========================================
 * �e����
 *------------------------------------------
 */
static int skill_shimiru( struct block_list *bl, va_list ap )
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
 * 凋C�O���g
 *------------------------------------------
 */
static int skill_shinkirou( struct block_list *bl, va_list ap )
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
 * �����藠�� -�\�z-
 *------------------------------------------
 */
static int skill_fuumakouchiku( struct block_list *bl, va_list ap )
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
 * �ꖳ -����-
 *------------------------------------------
 */
static int skill_kunaikussetsu( struct block_list *bl, va_list ap )
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
 * �L���X�����O�̃^�[�Q�b�g�ύX
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
 * �N���[���X�L��
 *------------------------------------------
 */
int skill_clone(struct map_session_data* sd,int skillid,int skilllv)
{
	nullpo_retr(0, sd);

	if(skillid <= 0 || skilllv <= 0)
		return 0;
	// �����x�����擾���Ă���
	if(pc_checkskill(sd,skillid) >= skilllv)
		return 0;

	// �擾�\�X�L�����H
	if(skill_get_cloneable(skillid)&(1<<sd->s_class.upper))
	{
		int cloneskilllv;
		// �T���N�`���A�����󂯂��ꍇ�A��Lv�̃q�[�����N���[��
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
 * ���v���f���[�X
 *------------------------------------------
 */
int skill_reproduce(struct map_session_data* sd,int skillid,int skilllv)
{
	nullpo_retr(0, sd);

	if(skillid <= 0 || skilllv <= 0)
		return 0;

	// �T�u�X�L���̏ꍇ�̓��C���ɒu������
	switch(skillid) {
		case AB_DUPLELIGHT_MELEE:	// �O���C�A�����C�g
		case AB_DUPLELIGHT_MAGIC:	// �~���A�����C�g
			skillid = AB_DUPLELIGHT;
			break;
		case WL_CHAINLIGHTNING_ATK:	// �`�F�[�����C�g�j���O(�A��)
			skillid = WL_CHAINLIGHTNING;
			break;
		case WL_TETRAVORTEX_FIRE:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_WATER:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_WIND:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_GROUND:	// �e�g���{���e�b�N�X(�n)
			skillid = WL_TETRAVORTEX;
			break;
		case WL_SUMMON_ATK_FIRE:	// �T�����t�@�C�A�{�[��(�U��)
			skillid = WL_SUMMONFB;
			break;
		case WL_SUMMON_ATK_WIND:	// �T�����{�[�����C�g�j���O(�U��)
			skillid = WL_SUMMONBL;
			break;
		case WL_SUMMON_ATK_WATER:	// �T�����E�H�[�^�[�{�[��(�U��)
			skillid = WL_SUMMONWB;
			break;
		case WL_SUMMON_ATK_GROUND:	// �T�����X�g�[��(�U��)
			skillid = WL_SUMMONSTONE;
			break;
		case LG_OVERBRAND_BRANDISH:	// �I�[�o�[�u�����h(�ガ)
		case LG_OVERBRAND_PLUSATK:	// �I�[�o�[�u�����h(�ǌ�)
			skillid = LG_OVERBRAND;
			break;
		case WM_REVERBERATION_MELEE:	// �U���c��(����)
		case WM_REVERBERATION_MAGIC:	// �U���c��(���@)
			skillid = WM_REVERBERATION;
			break;
		case WM_SEVERE_RAINSTORM_MELEE:	// �V�r�A���C���X�g�[��(�U��)
			skillid = WM_SEVERE_RAINSTORM;
			break;
		case GN_CRAZYWEED_ATK:	// �N���C�W�[�E�B�[�h(�U��)
			skillid = GN_CRAZYWEED;
			break;
		case GN_FIRE_EXPANSION_SMOKE_POWDER:	// �t�@�C�A�[�G�N�X�p���V����(����)
		case GN_FIRE_EXPANSION_TEAR_GAS:		// �t�@�C�A�[�G�N�X�p���V����(�×܃K�X)
		case GN_FIRE_EXPANSION_ACID:			// �t�@�C�A�[�G�N�X�p���V����(���_)
			skillid = GN_FIRE_EXPANSION;
			break;
		case GN_HELLS_PLANT_ATK:	// �w���Y�v�����g(�U��)
			skillid = GN_HELLS_PLANT;
			break;
		case GN_SLINGITEM_RANGEMELEEATK:	// �X�����O�A�C�e��(�������U��)
			skillid = GN_SLINGITEM;
			break;
		case NC_MAGMA_ERUPTION_DOTDAMAGE:	// �}�O�}�C���v�V����
			skillid = NC_MAGMA_ERUPTION;
			break;
	}

	// �����x�����擾���Ă���
	if(pc_checkskill(sd,skillid) >= skilllv)
		return 0;

	if(sd->sc.data[SC__REPRODUCE].timer != -1) {
		// �擾�\�X�L�����H
		if((skill_get_cloneable(skillid)&(1<<(sd->s_class.upper))) || (skill_get_cloneable(skillid)&0x08))
		{
			int reproducelv = sd->sc.data[SC__REPRODUCE].val1;
			sd->skill_reproduce.id = skillid;
			// �X�L�����x���̓��v���f���[�X�̃��x���ŏK��
			sd->skill_reproduce.lv = (reproducelv > skill_get_max(skillid))? skill_get_max(skillid): reproducelv;
			clif_skillinfoblock(sd);
			return 1;
		}
	}
	return 0;
}

/*==========================================
 * �񕜗ʕ␳
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

	// H.Plus�ɂ��q�[�����ʌ���
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

		// ���f�B�^�e�B�I
		skill += pc_checkskill(sd,HP_MEDITATIO) * 2;
		// �C�̗�
		if(pc_checkskill(sd,SU_POWEROFSEA) > 0) {
			skill += 50;
			if(pc_checkskill_summoner(sd, SU_POWEROFSEA) >= 20)
				skill += 100;
		}
		// �C�̍�(�V�N�ȃG�r)
		if(skill_id == SU_FRESHSHRIMP && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)
			skill += 30;
		// �g�����Z���f���X
		skill += pc_checkskill(sd,NV_TRANSCENDENCE) * 3;
	}

#ifndef PRE_RENEWAL
	if(skill > 0)
		rate += skill;
#endif

	if(rate > 0)
		heal += heal * rate / 100;

#ifndef PRE_RENEWAL
	// Matk�̉��Z
	if(skill_id == AL_HEAL || skill_id == AB_CHEAL || skill_id == AB_HIGHNESSHEAL || skill_id == CD_DILECTIO_HEAL)
		heal += battle_calc_base_magic_damage(src);
#endif

	if(tsd) {
		// �u���C�N�X���[
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
	if(skill > 0)	// ���f�B�^�e�B�I
		heal += heal * skill / 100;
#endif

	return heal;
}

/*----------------------------------------------------------------------------
 * �������n
 */

/*==========================================
 * �����񏈗�
 *   ',' �ŋ�؂���val�ɖ߂�
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
 * �����񏈗�
 *   ':' �ŋ�؂���atoi����val�ɖ߂�
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
 * �����񏈗�
 *   ':' �ŋ�؂���strtol����val�ɖ߂�
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
 * �X�L�����j�b�g�̔z�u���쐬
 *------------------------------------------
 */
static void skill_init_unit_layout(void)
{
	int i,j,pos = 0;

	memset(skill_unit_layout,0,sizeof(skill_unit_layout));
	// ��`�̃��j�b�g�z�u���쐬����
	for (i=0; i<=MAX_SQUARE_LAYOUT; i++) {
		int size = i*2+1;
		skill_unit_layout[i].count = size*size;
		for (j=0; j<size*size; j++) {
			skill_unit_layout[i].dx[j] = (j%size-i);
			skill_unit_layout[i].dy[j] = (j/size-i);
		}
	}
	pos = i;
	// ��`�ȊO�̃��j�b�g�z�u���쐬����
	for (i=0;i<MAX_SKILL_DB;i++) {
		if (!skill_db[i].unit_id[0] || skill_db[i].unit_layout_type[0] != -1)
			continue;
		switch (skill_db[i].id) {
			case MG_FIREWALL:
			case WZ_ICEWALL:
			case WL_EARTHSTRAIN:
			case RL_FIRE_RAIN:
				// �t�@�C�A�[�E�H�[���A�A�C�X�E�H�[���͕����ŕς��̂ŕʏ���
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
				// Lv1�i3x3�Ńg�[�^��4�Z���j
				const int dx1[] = {-1, 1, 0, 0};
				const int dy1[] = { 0, 0,-1, 1};
				// Lv2,3�i5x5�Ńg�[�^��8�Z���j
				const int dx2[] = {-2,-1, 1, 2, 0, 0, 0, 0};
				const int dy2[] = { 0, 0, 0, 0,-2,-1, 1, 2};
				// Lv4,5�i7x7�Ńg�[�^��12�Z���j
				const int dx3[] = {-3,-2,-1, 1, 2, 3, 0, 0, 0, 0, 0, 0};
				const int dy3[] = { 0, 0, 0, 0, 0, 0,-3,-2,-1, 1, 2, 3};
				// Lv1�̃Z�b�g
				j = 0;
				skill_unit_layout[pos].count = 4;
				memcpy(skill_unit_layout[pos].dx,dx1,sizeof(dx1));
				memcpy(skill_unit_layout[pos].dy,dy1,sizeof(dy1));
				skill_db[i].unit_layout_type[j] = pos;
				// Lv2,3�̃Z�b�g
				j++;
				pos++;
				skill_unit_layout[pos].count = 8;
				memcpy(skill_unit_layout[pos].dx,dx2,sizeof(dx2));
				memcpy(skill_unit_layout[pos].dy,dy2,sizeof(dy2));
				skill_db[i].unit_layout_type[j] = pos;
				skill_db[i].unit_layout_type[++j] = pos;
				// Lv4,5�̃Z�b�g
				j++;
				pos++;
				skill_unit_layout[pos].count = 12;
				memcpy(skill_unit_layout[pos].dx,dx3,sizeof(dx3));
				memcpy(skill_unit_layout[pos].dy,dy3,sizeof(dy3));
				skill_db[i].unit_layout_type[j] = pos;
				skill_db[i].unit_layout_type[++j] = pos;
				// Lv6�ȏ�͓���type�Ŗ��߂�
				for (;j<MAX_SKILL_LEVEL;j++)
					skill_db[i].unit_layout_type[j] = pos;
				pos++;
				continue;	// ����Lv����pos��ݒ肵���̂ňȉ��̏����͔�΂�
			}
			case NPC_FLAMECROSS:		/* �t���C���N���X */
			{
				const int dx[] = {-2,-1, 1, 2, 0, 0, 0, 0};
				const int dy[] = { 0, 0, 0, 0,-2,-1, 1, 2};
				skill_unit_layout[pos].count = 8;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case GN_WALLOFTHORN:		/* �\�[���E�H�[�� */
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
			case EL_FIRE_MANTLE:		/* �t�@�C�A�[�}���g�� */
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
	// �t�@�C���[�E�H�[��
	firewall_unit_pos = pos;
	for (i=0;i<8;i++) {
		if (i&1) {	/* �΂ߔz�u */
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
		} else {	/* �c���z�u */
			skill_unit_layout[pos].count = 3;
			if (i%4==0) {	/* �㉺ */
				int dx[] = {-1, 0, 1};
				int dy[] = { 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			/* ���E */
				int dx[] = { 0, 0, 0};
				int dy[] = {-1, 0, 1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
	// �A�C�X�E�H�[��
	icewall_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 5;
		if (i&1) {	/* �΂ߔz�u */
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
		} else {	/* �c���z�u */
			if (i%4==0) {	/* �㉺ */
				int dx[] = {-2,-1, 0, 1, 2};
				int dy[] = { 0, 0, 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			/* ���E */
				int dx[] = { 0, 0, 0, 0, 0};
				int dy[] = {-2,-1, 0, 1, 2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
	// �A�[�X�X�g���C��
	earthstrain_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 15;
		if (i==2 || i==6) {		/* 	���E */
			int dx[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			int dy[] = {-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		} else {			/* �㉺ */
			int dx[] = {-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7};
			int dy[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		}
		pos++;
	}
	// �t�@�C�A�[���C��
	firerain_unit_pos = pos;
	for (i=0;i<8;i++) {
		skill_unit_layout[pos].count = 3;
		if (i==2 || i==6) {		/* 	���E */
			int dx[] = { 0, 0, 0};
			int dy[] = {-1, 0, 1};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		} else {			/* �㉺ */
			int dx[] = {-1, 0, 1};
			int dy[] = { 0, 0, 0};
			memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
			memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
		}
		pos++;
	}
}

/*==========================================
 * �X�L���֌W�t�@�C���ǂݍ���
 * skill_db.txt �X�L���f�[�^
 * skill_cast_db.txt �X�L���̉r�����Ԃƃf�B���C�f�[�^
 * produce_db.txt �A�C�e���쐬�X�L���p�f�[�^
 * create_arrow_db.txt ��쐬�X�L���p�f�[�^
 * abra_db.txt �A�u���J�_�u�������X�L���f�[�^
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

	/* �X�L���f�[�^�x�[�X */
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

			if(strcasecmp(split[8],"yes") == 0)
				skill_db[i].castcancel = 1;
			else
				skill_db[i].castcancel = 0;
			skill_db[i].cast_def_rate = atoi(split[9]);
			skill_db[i].inf2          = (int)strtol(split[10], NULL, 0);
			skill_split_atoi(split[11],skill_db[i].maxcount,MAX_SKILL_LEVEL);
			if(strcasecmp(split[12],"weapon") == 0)
				skill_db[i].skill_type = BF_WEAPON;
			else if(strcasecmp(split[12],"magic") == 0)
				skill_db[i].skill_type = BF_MAGIC;
			else if(strcasecmp(split[12],"misc") == 0)
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

	/* �X�L���f�[�^�x�[�X2 */
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

	/* �X�L���v���f�[�^�x�[�X */
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

			if( strcasecmp(split[9],"hiding") == 0 )                   skill_db[i].state = SST_HIDING;
			else if( strcasecmp(split[9],"cloaking") == 0 )            skill_db[i].state = SST_CLOAKING;
			else if( strcasecmp(split[9],"chasewalking") == 0 )        skill_db[i].state = SST_CHASEWALKING;
			else if( strcasecmp(split[9],"hidden") == 0 )              skill_db[i].state = SST_HIDDEN;
			else if( strcasecmp(split[9],"riding") == 0 )              skill_db[i].state = SST_RIDING;
			else if( strcasecmp(split[9],"falcon") == 0 )              skill_db[i].state = SST_FALCON;
			else if( strcasecmp(split[9],"cart") == 0 )                skill_db[i].state = SST_CART;
			else if( strcasecmp(split[9],"shield") == 0 )              skill_db[i].state = SST_SHIELD;
			else if( strcasecmp(split[9],"sight") == 0 )               skill_db[i].state = SST_SIGHT;
			else if( strcasecmp(split[9],"explosionspirits") == 0 )    skill_db[i].state = SST_EXPLOSIONSPIRITS;
			else if( strcasecmp(split[9],"cartboost") == 0 )           skill_db[i].state = SST_CARTBOOST;
			else if( strcasecmp(split[9],"nen") == 0 )                 skill_db[i].state = SST_NEN;
			else if( strcasecmp(split[9],"recover_weight_rate") == 0 ) skill_db[i].state = SST_RECOV_WEIGHT_RATE;
			else if( strcasecmp(split[9],"move_enable") == 0 )         skill_db[i].state = SST_MOVE_ENABLE;
			else if( strcasecmp(split[9],"water") == 0 )               skill_db[i].state = SST_WATER;
			else if( strcasecmp(split[9],"dragon") == 0 )              skill_db[i].state = SST_DRAGON;
			else if( strcasecmp(split[9],"wolf") == 0 )                skill_db[i].state = SST_WOLF;
			else if( strcasecmp(split[9],"gear") == 0 )                skill_db[i].state = SST_GEAR;
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

	/* �X�L���v���f�[�^�x�[�X2 */
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

	/* �L���X�e�B���O�f�[�^�x�[�X */
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

	/* �X�L�����j�b�g�f�[�^�x�[�X */
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

	/* �����n�X�L���f�[�^�x�[�X */
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

	/* ��쐬�f�[�^�x�[�X */
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

	/* �A�u���J�^�u���f�[�^�x�[�X */
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

	/* �����_�������X�L���f�[�^�x�[�X */
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

	/* �`�F���W�}�e���A���f�[�^�x�[�X */
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
 * �I��
 *------------------------------------------
 */
int do_final_skill(void)
{
	if(skillname_db)
		strdb_final(skillname_db,NULL);
	return 0;
}

/*==========================================
 * �X�L���֌W����������
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

