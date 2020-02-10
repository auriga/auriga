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
#include <math.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "battle.h"
#include "map.h"
#include "path.h"
#include "pc.h"
#include "bonus.h"
#include "skill.h"
#include "mob.h"
#include "homun.h"
#include "itemdb.h"
#include "clif.h"
#include "pet.h"
#include "guild.h"
#include "status.h"
#include "party.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"
#include "elem.h"

struct Battle_Config battle_config;

struct battle_delay_damage_ {
	struct block_list *src;
	int target;
	int damage;
	short skillid;
	short skilllv;
	int flag;
	int dist;
};

static int battle_attack_drain(struct block_list *bl,int damage,int damage2,int flag);
static struct Damage battle_calc_attack(int attack_type,struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag);

/*==========================================
 * ƒ_ƒ[ƒW‚Ì’x‰„
 *------------------------------------------
 */
static int battle_delay_damage_sub(int tid,unsigned int tick,int id,void *data)
{
	struct battle_delay_damage_ *dat = (struct battle_delay_damage_ *)data;

	if(dat) {
		struct block_list *target = map_id2bl(dat->target);

		if(map_id2bl(id) == dat->src && target && target->prev != NULL) {
			if(dat->src->m == target->m && dat->dist + 10 >= unit_distance(dat->src, target))
				battle_damage(dat->src,target,dat->damage,dat->skillid,dat->skilllv,dat->flag);
		}
		aFree(dat);
	}
	return 0;
}

int battle_delay_damage(unsigned int tick,struct block_list *src,struct block_list *target,int damage,int skillid,int skilllv,int flag)
{
	struct battle_delay_damage_ *dat;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	dat = (struct battle_delay_damage_*)aCalloc(1,sizeof(struct battle_delay_damage_));
	dat->src     = src;
	dat->target  = target->id;
	dat->damage  = damage;
	dat->skillid = skillid;
	dat->skilllv = skilllv;
	dat->flag    = flag;
	dat->dist    = unit_distance(src, target);
	add_timer2(tick,battle_delay_damage_sub,src->id,dat);

	return 0;
}

/*==========================================
 * ü•Ó‚Éƒ_ƒ[ƒW
 *------------------------------------------
 */
int battle_damage_area(struct block_list *bl,va_list ap)
{
	struct block_list *src;
	int damage,skillid,skilllv,flag;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	if((src = va_arg(ap,struct block_list*)) == NULL)
		return 0;

	damage  = va_arg(ap,int);
	skillid = va_arg(ap,int);
	skilllv = va_arg(ap,int);
	flag    = va_arg(ap,int);
	tick    = va_arg(ap,unsigned int);

	if(battle_check_target(src,bl,flag) > 0) {
		clif_damage(bl,bl,tick,status_get_amotion(bl),status_get_dmotion(bl),damage,0,9,0,0);
		battle_damage(src,bl,damage,skillid,skilllv,flag);

		if(skillid == LG_REFLECTDAMAGE) {
			// ƒXƒLƒ‹‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒI[ƒgƒXƒyƒ‹
			if(battle_config.weapon_reflect_autospell && src->type == BL_PC && atn_rand()%2)
				bonus_autospell_start(src,bl,EAS_ATTACK,tick,0);

			if(battle_config.weapon_reflect_drain && src != bl)
				battle_attack_drain(src,damage,0,battle_config.weapon_reflect_drain_enable_type);

			// ƒXƒLƒ‹‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒAƒNƒeƒBƒuƒAƒCƒeƒ€
			if(battle_config.weapon_reflect_autospell && src->type == BL_PC)
				bonus_activeitem_start((struct map_session_data *)src,EAS_ATTACK,tick);
		}
	}

	return 0;
}

/*==========================================
 * ÀÛ‚ÉHP‚ğ‘€ì
 *------------------------------------------
 */
int battle_damage(struct block_list *bl,struct block_list *target,int damage,int skillid,int skilllv,int flag)
{
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct mob_data   *tmd  = NULL;
	struct homun_data *thd  = NULL;
	struct merc_data  *tmcd = NULL;
	struct elem_data  *teld = NULL;

	nullpo_retr(0, target);	// bl‚ÍNULL‚ÅŒÄ‚Î‚ê‚é‚±‚Æ‚ª‚ ‚é‚Ì‚Å‘¼‚Åƒ`ƒFƒbƒN

	if(damage == 0 || target->type == BL_PET)
		return 0;

	if(target->prev == NULL)
		return 0;

	if(bl) {
		if(bl->prev == NULL)
			return 0;
		if(bl->type == BL_PC)
			sd = (struct map_session_data *)bl;
	}

	if(damage < 0)
		return battle_heal(bl,target,-damage,0,flag);

	map_freeblock_lock();

	if(target->type == BL_SKILL) {
		skill_unit_ondamaged((struct skill_unit *)target,bl,damage,gettick());
		map_freeblock_unlock();
		return 0;
	}

	tsd  = BL_DOWNCAST( BL_PC,   target );
	tmd  = BL_DOWNCAST( BL_MOB,  target );
	thd  = BL_DOWNCAST( BL_HOM,  target );
	tmcd = BL_DOWNCAST( BL_MERC, target );
	teld = BL_DOWNCAST( BL_ELEM, target );

	if(tsd) {
		// ƒfƒBƒ{[ƒVƒ‡ƒ“‚ğ‚©‚¯‚ç‚ê‚Ä‚¢‚é
		if( tsd &&
		    tsd->sc.data[SC_DEVOTION].timer != -1 &&
		    tsd->sc.data[SC_DEVOTION].val1 &&
		    skillid != PA_PRESSURE &&
		    skillid != SA_COMA &&
		    skillid != NPC_DARKBLESSING &&
		    (skillid != CR_GRANDCROSS || bl == NULL || bl != target) )
		{
			struct map_session_data *msd = map_id2sd(tsd->sc.data[SC_DEVOTION].val1);

			if(msd && skill_devotion3(msd,tsd->bl.id)) {
				skill_devotion(msd);
			} else if(msd && bl) {
				int i;
				unsigned int tick = gettick();
				for(i=0; i<5; i++) {
					if(msd->dev.val1[i] != target->id)
						continue;
					// ƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“•t‚«‚Åƒ_ƒ[ƒW•\¦
					clif_damage(&msd->bl,&msd->bl,tick,0,status_get_dmotion(&msd->bl),damage,0,0,0,0);
					battle_damage(bl,&msd->bl,damage,skillid,skilllv,flag);
					map_freeblock_unlock();
					return 0;
				}
			}
		}
		// ƒVƒƒƒhƒEƒtƒH[ƒ€‚ğ‚©‚¯‚ç‚ê‚Ä‚¢‚é
		if( tsd &&
		    tsd->sc.data[SC__SHADOWFORM].timer != -1 &&
		    tsd->sc.data[SC__SHADOWFORM].val2 &&
		    skillid != PA_PRESSURE &&
		    skillid != SA_COMA &&
		    skillid != NPC_DARKBLESSING &&
		    (skillid != CR_GRANDCROSS || bl == NULL || bl != target) )
		{
			struct map_session_data *msd = map_id2sd(tsd->sc.data[SC__SHADOWFORM].val2);

			if(msd && bl && tsd->shadowform_id != msd->bl.id && skill_shadowform(msd,tsd->bl.id) == 0) {
				// ‰ñ”‚ğ’´‚¦‚½‚çƒVƒƒƒhƒEƒtƒH[ƒ€‰ğœ
				if(--tsd->sc.data[SC__SHADOWFORM].val3 <= 0) {
					status_change_end(&tsd->bl,SC__SHADOWFORM,-1);
				}
				// ƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“•t‚«‚Åƒ_ƒ[ƒW•\¦
				clif_damage(&msd->bl,&msd->bl,gettick(),0,status_get_dmotion(&msd->bl),damage,0,0,0,0);
				battle_damage(bl,&msd->bl,damage,skillid,skilllv,flag);
				map_freeblock_unlock();
				return 0;
			}
		}
		// ƒEƒH[ƒ^[ƒXƒNƒŠ[ƒ“‚ğ‚©‚¯‚ç‚ê‚Ä‚¢‚é
		if( tsd && tsd->eld &&
		    tsd->sc.data[SC_WATER_SCREEN].timer != -1 &&
		    skillid != PA_PRESSURE &&
		    skillid != SA_COMA &&
		    skillid != NPC_DARKBLESSING &&
		    (skillid != CR_GRANDCROSS || bl == NULL || bl != target) )
		{
			struct elem_data *eld = tsd->eld;

			// ƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“•t‚«‚Åƒ_ƒ[ƒW•\¦
			clif_damage(&eld->bl,&eld->bl,gettick(),0,status_get_dmotion(&eld->bl),damage,0,0,0,0);
			battle_damage(bl,&eld->bl,damage,skillid,skilllv,flag);
			map_freeblock_unlock();
			return 0;
		}
	}

	status_change_attacked_end(target);	// “€Œ‹EÎ‰»E‡–°‚ğÁ‹
	unit_skillcastcancel(target,2);		// ‰r¥–WŠQ

	if(tsd)       pc_damage(bl,tsd,damage);
	else if(tmd)  mob_damage(bl,tmd,damage,0);
	else if(thd)  homun_damage(bl,thd,damage);
	else if(tmcd) merc_damage(bl,tmcd,damage);
	else if(teld) elem_damage(bl,teld,damage);

	// ƒJ[ƒhŒø‰Ê‚ÌƒR[ƒ}E‘¦€
	if(sd && target && target->prev && !unit_isdead(target) && flag&(BF_WEAPON|BF_NORMAL) && status_get_class(target) != MOBID_EMPERIUM)
	{
		int race = status_get_race(target);
		int ele  = status_get_elem_type(target);
		int mode = status_get_mode(target);

		if((!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_ele[ele]) ||
		   (!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race[race]) ||
		   (mode&MD_BOSS && atn_rand()%10000 < sd->weapon_coma_race[RCT_BOSS]) ||
		   (!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race[RCT_NONBOSS]) ||
		   (tsd && atn_rand()%10000 < sd->weapon_coma_race[RCT_PLAYER]))
		{
			int hp = status_get_hp(target);
			if(tsd)       pc_damage(bl,tsd,hp);
			else if(tmd)  mob_damage(bl,tmd,hp,0);
			else if(thd)  homun_damage(bl,thd,hp);
			else if(tmcd) merc_damage(bl,tmcd,hp);
			else if(teld) elem_damage(bl,teld,hp);
		}
		else if((!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_ele2[ele]) ||
			(!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race2[race]) ||
			(mode&MD_BOSS && atn_rand()%10000 < sd->weapon_coma_race2[RCT_BOSS]) ||
			(!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race2[RCT_NONBOSS]) ||
			(tsd && atn_rand()%10000 < sd->weapon_coma_race[RCT_PLAYER]))
		{
			int hp = status_get_hp(target) - 1;
			if(tsd)       pc_damage(bl,tsd,hp);
			else if(tmd)  mob_damage(bl,tmd,hp,0);
			else if(thd)  homun_damage(bl,thd,hp);
			else if(tmcd) merc_damage(bl,tmcd,hp);
			else if(teld) elem_damage(bl,teld,hp);
		}
	}

	/* ƒ\ƒEƒ‹ƒhƒŒƒCƒ“ */
	if(sd && tmd && unit_isdead(&tmd->bl) && flag&BF_MAGIC)
	{
		int level = pc_checkskill(sd,HW_SOULDRAIN);
		if(level > 0 && (skill_get_inf(skillid) & INF_ATTACK) && sd->ud.skilltarget == target->id) {
			int sp = 0;
			clif_skill_nodamage(bl,target,HW_SOULDRAIN,level,1);
			sp = (status_get_lv(target))*(95+15*level)/100;
			if(sd->status.sp + sp > sd->status.max_sp)
				sp = sd->status.max_sp - sd->status.sp;
			sd->status.sp += sp;
			clif_heal(sd->fd,SP_SP,sp);
		}
	}

	map_freeblock_unlock();

	return 0;
}

/*==========================================
 * HP/SP‰ñ•œ
 *------------------------------------------
 */
int battle_heal(struct block_list *bl,struct block_list *target,int hp,int sp,int flag)
{
	nullpo_retr(0, target);	// bl‚ÍNULL‚ÅŒÄ‚Î‚ê‚é‚±‚Æ‚ª‚ ‚é‚Ì‚Å‘¼‚Åƒ`ƒFƒbƒN

	if(target->type == BL_PET)
		return 0;
	if(unit_isdead(target))
		return 0;
	if(hp == 0 && sp == 0)
		return 0;

	if(hp < 0)
		return battle_damage(bl,target,-hp,0,0,flag);

	if(target->type == BL_MOB)
		return mob_heal((struct mob_data *)target,hp);
	else if(target->type == BL_PC)
		return pc_heal((struct map_session_data *)target,hp,sp);
	else if(target->type == BL_HOM)
		return homun_heal((struct homun_data *)target,hp,sp);
	else if(target->type == BL_MERC)
		return merc_heal((struct merc_data *)target,hp,sp);
	else if(target->type == BL_ELEM)
		return elem_heal((struct elem_data *)target,hp,sp);

	return 0;
}

/*==========================================
 * ƒ_ƒ[ƒW‚Ì‘®«C³
 *------------------------------------------
 */
int battle_attr_fix(int damage,int atk_elem,int def_elem)
{
	int def_type, def_lv, rate;

	// ‘®«–³‚µ(!=–³‘®«)
	if (atk_elem == ELE_NONE)
		return damage;

	def_type = def_elem%20;
	def_lv   = def_elem/20;

	if( atk_elem == ELE_MAX )
		atk_elem = atn_rand()%ELE_MAX;	// •Ší‘®«ƒ‰ƒ“ƒ_ƒ€‚Å•t‰Á

	if( atk_elem < ELE_NEUTRAL || atk_elem >= ELE_MAX ||
	    def_type < ELE_NEUTRAL || def_type >= ELE_MAX ||
	    def_lv <= 0 || def_lv > MAX_ELE_LEVEL )
	{
		// ‘®«’l‚ª‚¨‚©‚µ‚¢‚Ì‚Å‚Æ‚è‚ ‚¦‚¸‚»‚Ì‚Ü‚Ü•Ô‚·
		if(battle_config.error_log)
			printf("battle_attr_fix: unknown attr type: atk=%d def_type=%d def_lv=%d\n",atk_elem,def_type,def_lv);
		return damage;
	}

	rate = attr_fix_table[def_lv-1][atk_elem][def_type];
	if(damage < 0 && rate < 0)	// •‰~•‰‚Ìê‡‚ÍŒ‹‰Ê‚ğ•‰‚É‚·‚é
		rate = -rate;

#ifdef PRE_RENEWAL
	return damage * rate / 100;
#else
	return damage + (damage * (rate - 100) / 100);
#endif
}

/*==========================================
 * ƒ_ƒ[ƒWÅIŒvZ
 *------------------------------------------
 */
static int battle_calc_damage(struct block_list *src, struct block_list *bl, int damage, int div_, int skill_num, int skill_lv, int flag)
{
	struct map_session_data *tsd = NULL;
	struct mob_data         *tmd = NULL;
	struct unit_data *ud;
	struct status_change *sc, *src_sc;
	unsigned int tick = gettick();

	static const int manuk_mob[] = { 1986,1987,1988,1989,1990,1997,1998,1999 };
	static const int splendide_mob[] = { 1991,1992,1993,1994,1995 };

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	tsd    = BL_DOWNCAST( BL_PC,  bl );
	tmd    = BL_DOWNCAST( BL_MOB, bl );

	ud = unit_bl2ud(bl);
	sc = status_get_sc(bl);
	src_sc = status_get_sc(src);

	// ƒXƒLƒ‹ƒ_ƒ[ƒW•â³
	if(damage > 0 && skill_num > 0) {
		int damage_rate = 100;
		if(map[bl->m].flag.normal)
			damage_rate = skill_get_damage_rate(skill_num,0);
		else if(map[bl->m].flag.gvg)
			damage_rate = skill_get_damage_rate(skill_num,2);
		else if(map[bl->m].flag.pvp)
			damage_rate = skill_get_damage_rate(skill_num,1);
		else if(map[bl->m].flag.pk)
			damage_rate = skill_get_damage_rate(skill_num,3);
		if(damage_rate != 100)
			damage = damage*damage_rate/100;
		// ï¿½Jï¿½[ï¿½hï¿½ï¿½ï¿½Ê‚É‚ï¿½ï¿½ï¿½ï¿½ï¿½Xï¿½Lï¿½ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½Wï¿½Ïï¿½(ï¿½bï¿½ï¿½)
		if(tsd && tsd->sub_skill_damage.count > 0) {
			int i;
			for(i=0; i<tsd->sub_skill_damage.count; i++) {
				if(skill_num == tsd->sub_skill_damage.id[i]) {
					damage = damage*(100-tsd->sub_skill_damage.rate[i])/100;
					break;
				}
			}
		}
	}

	if(tmd && tmd->mode&MD_SKILLIMMUNITY && skill_num > 0)
		damage = 0;

	if(sc && sc->count > 0) {
		if(sc->data[SC_INVINCIBLE].timer != -1 && sc->data[SC_INVINCIBLEOFF].timer == -1) {
			if(skill_num == PR_SANCTUARY)
				damage = 1;
			else
				damage = 0;
		}

		if(sc->data[SC_WHITEIMPRISON].timer != -1) {
			// ƒzƒƒCƒgƒCƒ“ƒvƒŠƒYƒ“ó‘Ô‚Í”O‘®«ˆÈŠO‚Íƒ_ƒ[ƒW‚ğó‚¯‚È‚¢
			if( (flag&BF_SKILL && skill_get_pl(skill_num) != ELE_GHOST) ||
				(!(flag&BF_SKILL) && status_get_attack_element(src) != ELE_GHOST) )
			damage = 0;
		}
	}

	if(src_sc && src_sc->count > 0) {
#ifdef PRE_RENEWAL
		// ‘®«ê‚Ìƒ_ƒ[ƒW‘‰Á
		if(src_sc->data[SC_VOLCANO].timer != -1 && damage > 0) {	// ƒ{ƒ‹ƒP[ƒm
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE ) {
				damage += damage * src_sc->data[SC_VOLCANO].val4 / 100;
			}
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE ) {
				damage += damage * src_sc->data[SC_VOLCANO].val4 / 100;
			}
		}
		if(src_sc->data[SC_VIOLENTGALE].timer != -1 && damage > 0) {	// ƒoƒCƒIƒŒƒ“ƒgƒQƒCƒ‹
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_WIND )
				damage += damage * src_sc->data[SC_VIOLENTGALE].val4 / 100;
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_WIND )
				damage += damage * src_sc->data[SC_VIOLENTGALE].val4 / 100;
		}
		if(src_sc->data[SC_DELUGE].timer != -1 && damage > 0) {	// ƒfƒŠƒ…[ƒW
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_WATER )
				damage += damage * src_sc->data[SC_DELUGE].val4 / 100;
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_WATER )
				damage += damage * src_sc->data[SC_DELUGE].val4 / 100;
		}
#endif
		if(tmd) {
			int i;
			if(src_sc->data[SC_MANU_ATK].timer != -1 && damage > 0 && flag&BF_WEAPON) {	// ƒ}ƒkƒNƒtƒB[ƒ‹ƒhMOB•¨—ƒ_ƒ[ƒW‘‰Á
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_MANU_ATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_SPL_ATK].timer != -1 && damage > 0 && flag&BF_WEAPON) {	// ƒXƒvƒŒƒ“ƒeƒBƒbƒhƒtƒB[ƒ‹ƒhMOB•¨—ƒ_ƒ[ƒW‘‰Á
				for(i = 0; i < (sizeof(splendide_mob) / sizeof(splendide_mob[0])); i++) {
					if(splendide_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_SPL_ATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_MANU_MATK].timer != -1 && damage > 0 && flag&BF_MAGIC) {	// ƒ}ƒkƒNƒtƒB[ƒ‹ƒhMOB–‚–@ƒ_ƒ[ƒW‘‰Á
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_MANU_MATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_SPL_MATK].timer != -1 && damage > 0 && flag&BF_MAGIC) {	// ƒXƒvƒŒƒ“ƒeƒBƒbƒhƒtƒB[ƒ‹ƒhMOB–‚–@ƒ_ƒ[ƒW‘‰Á
				for(i = 0; i < (sizeof(splendide_mob) / sizeof(splendide_mob[0])); i++) {
					if(splendide_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_SPL_MATK].val1 / 100;
						break;
					}
				}
			}
		}

		if(src_sc->data[SC_INVINCIBLE].timer != -1 && src_sc->data[SC_INVINCIBLEOFF].timer == -1)
			damage += damage * 75 / 100;
		if(src_sc->data[SC_JP_EVENT01].timer != -1 && damage > 0 && flag&BF_WEAPON && status_get_race(bl) == RCT_FISH)
			damage += damage * src_sc->data[SC_JP_EVENT01].val1 / 100;
		if(src_sc->data[SC_JP_EVENT02].timer != -1 && damage > 0 && flag&BF_MAGIC && status_get_race(bl) == RCT_FISH)
			damage += damage * src_sc->data[SC_JP_EVENT02].val1 / 100;
		// ŒÃ‘ã¸—ì‚Ì‚¨ç‚è
		if(src_sc->data[SC_PHI_DEMON].timer != -1 && damage > 0 && flag&(BF_WEAPON|BF_MAGIC) && status_get_race(bl) == RCT_DEMON)
			damage += damage * 10 / 100;
		// p® -“WŠJ-‚Ì‘®«ƒ_ƒ[ƒW‘‰Á
		if(src_sc->data[SC_KO_ZENKAI].timer != -1 && damage > 0) {
			// val3‚É‘®«’l‚ª“ü‚Á‚Ä‚é‚Ì‚Åˆê’v‚·‚ê‚Îƒ_ƒ[ƒW‘‰Á
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == src_sc->data[SC_KO_ZENKAI].val3) ||
				(!(flag&BF_SKILL) && status_get_attack_element(src) == src_sc->data[SC_KO_ZENKAI].val3) )
					damage += damage * src_sc->data[SC_KO_ZENKAI].val4 / 100;
		}
		/* ƒeƒŒƒLƒlƒVƒXƒCƒ“ƒeƒ“ƒX */
		if(src_sc->data[SC_TELEKINESIS_INTENSE].timer != -1 && skill_get_pl(skill_num) == ELE_GHOST)
			damage += damage * src_sc->data[SC_TELEKINESIS_INTENSE].val2 / 100;
	}

	if(sc && sc->count > 0 && skill_num != PA_PRESSURE && skill_num != HW_GRAVITATION) {
		// ƒAƒXƒ€ƒvƒeƒBƒI
		if( (
#ifdef PRE_RENEWAL
			sc->data[SC_ASSUMPTIO].timer != -1 ||
#endif
			sc->data[SC_ASSUMPTIO2].timer != -1) && damage > 0) {
			if(map[bl->m].flag.pvp || map[bl->m].flag.gvg)
				damage = damage * 2 / 3;
			else
				damage = damage / 2;
		}

		// ƒSƒXƒyƒ‹‚Ì“Áêó‘ÔˆÙí
		if(sc->data[SC_INCDAMAGE].timer != -1 && damage > 0)
			damage += damage * sc->data[SC_INCDAMAGE].val1/100;

		// ƒoƒWƒŠƒJ
		if(sc->data[SC_BASILICA].timer != -1 && damage > 0 && !(status_get_mode(src)&MD_BOSS))
			damage = 0;

		// ƒEƒH[ƒ‹ƒIƒuƒtƒHƒO
		if((sc->data[SC_FOGWALL].timer != -1 || sc->data[SC_FOGWALLPENALTY].timer != -1)
			&& damage > 0 && flag&BF_LONG && skill_num!=PA_PRESSURE)
		{
			if(skill_num == 0) {	// ‰“‹——£’ÊíUŒ‚75%OFF
				damage = damage * 25 / 100;
			} else {		// ‰“‹——£ƒXƒLƒ‹25%OFF
				damage = damage * 75 / 100;
			}
		}

#ifdef PRE_RENEWAL
		// ƒZƒCƒtƒeƒBƒEƒH[ƒ‹
		if(sc->data[SC_SAFETYWALL].timer != -1 && flag&BF_SHORT) {
			struct skill_unit *unit = map_id2su(sc->data[SC_SAFETYWALL].val2);
			if(unit && unit->group) {
				if((--unit->group->val2) <= 0)
					skill_delunit(unit);
				damage = 0;
			} else {
				status_change_end(bl,SC_SAFETYWALL,-1);
			}
		}
#else
		// ƒLƒŠƒGƒGƒŒƒCƒ\ƒ“
		if(sc->data[SC_KYRIE].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_KYRIE];
			scd->val2 -= damage;
			if(flag&BF_WEAPON) {
				if(scd->val2 >= 0)
					damage = 0;
				else
					damage = -scd->val2;
			}
			if(--scd->val3 <= 0 || scd->val2 <= 0 || skill_num == AL_HOLYLIGHT)
				status_change_end(bl, SC_KYRIE, -1);
		}
		// ƒZƒCƒtƒeƒBƒEƒH[ƒ‹
		if(sc->data[SC_SAFETYWALL].timer != -1 && damage > 0 && flag&BF_SHORT) {
			struct skill_unit *unit = map_id2su(sc->data[SC_SAFETYWALL].val2);
			if(unit && unit->group) {
				unit->group->val1 -= damage;
				unit->group->val2--;
				if(unit->group->val1 > 0 && unit->group->val2 > 0)
					return 0;
				skill_delunit(unit);
				damage = 0;
			} else {
				status_change_end(bl,SC_SAFETYWALL,-1);
			}
		}
#endif

		// ƒJƒEƒv
		if(sc->data[SC_KAUPE].timer != -1 && atn_rand()%100 < sc->data[SC_KAUPE].val2) {
			status_change_end(bl,SC_KAUPE,-1);
			damage = 0;
		}

		// ƒjƒ…[ƒ}Eô•Ô‚µEƒjƒ…[ƒgƒ‰ƒ‹ƒoƒŠƒA[
		if((sc->data[SC_PNEUMA].timer != -1 || sc->data[SC_TATAMIGAESHI].timer != -1 || sc->data[SC_NEUTRALBARRIER].timer != -1) &&
			damage > 0 && flag&(BF_WEAPON|BF_MISC) && flag&BF_LONG) {
			switch(skill_num) {
				case AC_SHOWER:
				case SN_SHARPSHOOTING:
					if(src->type != BL_MOB) {
						damage = 0;
					}
					break;
				default:
					damage = 0;
					break;
			}
		}

		// ƒ}ƒOƒƒV[ƒ‹ƒh
		if(sc->data[SC_TUNAPARTY].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_TUNAPARTY];
			scd->val2 -= damage;
			if(scd->val2 >= 0)
				damage = 0;
			else
				damage = -scd->val2;
			if(scd->val2 <= 0)
				status_change_end(bl, SC_TUNAPARTY, -1);
		}

		// ƒ_[ƒNƒNƒ[
		if(sc->data[SC_DARKCROW].timer != -1 && flag&(BF_WEAPON|BF_SHORT))
			damage += damage * sc->data[SC_DARKCROW].val2 / 100;

		// ƒŒƒbƒNƒXƒG[ƒeƒ‹ƒi
		if(sc->data[SC_AETERNA].timer != -1 && damage > 0) {
			damage <<= 1;
			status_change_end(bl,SC_AETERNA,-1);
		}

		// ƒGƒiƒW[ƒR[ƒg
#ifdef PRE_RENEWAL
		if(sc->data[SC_ENERGYCOAT].timer != -1 && damage > 0 && flag&BF_WEAPON && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID)
#else
		if(sc->data[SC_ENERGYCOAT].timer != -1 && damage > 0 && flag&(BF_WEAPON|BF_MAGIC) && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID)
#endif
		{
			if(tsd) {
				if(tsd->status.sp > 0) {
					int per = tsd->status.sp * 5 / (tsd->status.max_sp + 1);
					tsd->status.sp -= tsd->status.sp * (per * 5 + 10) / 1000;
					if(tsd->status.sp < 0)
						tsd->status.sp = 0;
					damage -= damage * ((per + 1) * 6) / 100;
					clif_updatestatus(tsd,SP_SP);
				}
				if(tsd->status.sp <= 0)
					status_change_end(bl,SC_ENERGYCOAT,-1);
			} else {
				damage -= damage * (sc->data[SC_ENERGYCOAT].val1 * 6) / 100;
			}
		}

#ifdef PRE_RENEWAL
		// ƒLƒŠƒGƒGƒŒƒCƒ\ƒ“
		if(sc->data[SC_KYRIE].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_KYRIE];
			scd->val2 -= damage;
			if(flag&BF_WEAPON) {
				if(scd->val2 >= 0)
					damage = 0;
				else
					damage = -scd->val2;
			}
			if(--scd->val3 <= 0 || scd->val2 <= 0 || skill_num == AL_HOLYLIGHT)
				status_change_end(bl, SC_KYRIE, -1);
		}
#endif

		// ƒCƒ“ƒfƒ…ƒA
		if(sc->data[SC_ENDURE].timer != -1 && damage > 0 && flag&BF_WEAPON && src->type != BL_PC) {
			if((--sc->data[SC_ENDURE].val2) <= 0)
				status_change_end(bl, SC_ENDURE, -1);
		}

		// ƒI[ƒgƒK[ƒh
		if(sc->data[SC_AUTOGUARD].timer != -1 && damage > 0 && flag&BF_WEAPON && skill_num != WS_CARTTERMINATION) {
			if(atn_rand()%100 < sc->data[SC_AUTOGUARD].val2) {
				int delay;
				damage = 0;
				clif_skill_nodamage(bl,bl,CR_AUTOGUARD,sc->data[SC_AUTOGUARD].val1,1);
				if(sc->data[SC_AUTOGUARD].val1 <= 5)
					delay = 300;
				else if (sc->data[SC_AUTOGUARD].val1 > 5 && sc->data[SC_AUTOGUARD].val1 <= 9)
					delay = 200;
				else
					delay = 100;
				if(ud) {
					ud->canmove_tick = tick + delay;
					if(sc->data[SC_SHRINK].timer != -1 && atn_rand()%100 < 5*sc->data[SC_AUTOGUARD].val1)
						skill_blown(bl,src,2);
				}
			}
		}

		// ƒpƒŠƒCƒ“ƒO
		if(sc->data[SC_PARRYING].timer != -1 && damage > 0 && flag&BF_WEAPON && skill_num != WS_CARTTERMINATION) {
			if(atn_rand()%100 < sc->data[SC_PARRYING].val2)
			{
				int dir = path_calc_dir(bl,src->x,src->y);
				damage = 0;
				clif_skill_nodamage(bl,bl,sc->data[SC_PARRYING].val4,sc->data[SC_PARRYING].val1,1);	// val4‚ÍƒXƒLƒ‹ID
				clif_changedir(bl,dir,dir);
				if(ud)
					ud->attackabletime = tick + 500;	// ’l“K“–
			}
		}

		// ƒŠƒWƒFƒNƒgƒ\[ƒh
		if(sc->data[SC_REJECTSWORD].timer != -1 && damage > 0 && flag&BF_WEAPON && atn_rand()%100 < 15*sc->data[SC_REJECTSWORD].val1) {
			short weapon = WT_FIST;
			if(src->type == BL_PC)
				weapon = ((struct map_session_data *)src)->status.weapon;
			if(src->type == BL_MOB || weapon == WT_DAGGER || weapon == WT_1HSWORD || weapon == WT_2HSWORD) {
				damage = damage*50/100;
				battle_damage(bl,src,damage,ST_REJECTSWORD,sc->data[SC_REJECTSWORD].val1,0);
				clif_skill_nodamage(bl,bl,ST_REJECTSWORD,sc->data[SC_REJECTSWORD].val1,1);
				if((--sc->data[SC_REJECTSWORD].val2) <= 0)
					status_change_end(bl, SC_REJECTSWORD, -1);
			}
		}

#ifdef PRE_RENEWAL
		// ƒXƒpƒCƒ_[ƒEƒFƒu
		if(sc->data[SC_SPIDERWEB].timer != -1 && damage > 0) {
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				damage <<= 1;
				status_change_end(bl, SC_SPIDERWEB, -1);
			}
		}
#endif

		// ƒ~ƒŒƒjƒAƒ€ƒV[ƒ‹ƒh
		if(sc->data[SC_BERKANA].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_BERKANA];

			if(damage >= scd->val3) {
				scd->val3 = 1000;
				scd->val2--;
				if(tsd)
					clif_mshield(tsd,scd->val2);
			} else {
				scd->val3 -= damage;
			}
			damage = 0;
			if(scd->val2 <= 0)
				status_change_end(bl, SC_BERKANA, -1);
		}

		// ƒEƒFƒ|ƒ“ƒuƒƒbƒLƒ“ƒO
		if(sc->data[SC_WEAPONBLOCKING].timer != -1 && flag&BF_WEAPON && flag&BF_SHORT && skill_num != WS_CARTTERMINATION) {
			if(atn_rand()%100 < sc->data[SC_WEAPONBLOCKING].val2) {
				int lv = sc->data[SC_WEAPONBLOCKING].val1;
				damage = 0;
				clif_skill_nodamage(bl,bl,GC_WEAPONBLOCKING,lv,1);
				status_change_start(bl,SC_WEAPONBLOCKING2,lv,src->id,0,0,skill_get_time2(GC_WEAPONBLOCKING,lv),0);
			}
		}

		// ƒNƒ[ƒLƒ“ƒOƒGƒNƒV[ƒh
		if(sc->data[SC_CLOAKINGEXCEED].timer != -1 && damage > 0) {
			if((--sc->data[SC_CLOAKINGEXCEED].val2) <= 0)
				status_change_end(bl, SC_CLOAKINGEXCEED, -1);
		}

		// ƒnƒ‹ƒVƒl[ƒVƒ‡ƒ“ƒEƒH[ƒN
		if(sc->data[SC_HALLUCINATIONWALK].timer != -1 && damage > 0 && flag&BF_MAGIC) {
			if(atn_rand()%100 < sc->data[SC_HALLUCINATIONWALK].val1 * 10)
				damage = 0;
		}

		// ƒtƒH[ƒXƒIƒuƒoƒ“ƒK[ƒh
		if(sc->data[SC_FORCEOFVANGUARD].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_FORCEOFVANGUARD];
			int max = 5 + scd->val1 * 2;

			if(atn_rand()%100 < scd->val3) {
				if(scd->val4 < max) {
					scd->val4++;
					if(tsd)
						clif_mshield(tsd,scd->val4);
				}
			}
		}

		// ƒvƒŒƒXƒeƒB[ƒW
		if(sc->data[SC_PRESTIGE].timer != -1 && damage > 0 && flag&BF_MAGIC) {
			if(atn_rand()%100 < sc->data[SC_PRESTIGE].val3)
				damage = 0;
		}

		// ‘M“d•à
		if(sc->data[SC_LIGHTNINGWALK].timer != -1 && damage > 0 && flag&(BF_LONG|BF_MAGIC) && skill_get_inf(skill_num)&INF_ATTACK) {
			if(atn_rand()%100 < 88 + sc->data[SC_LIGHTNINGWALK].val1 * 2) {
				damage = 0;
				clif_skill_poseffect(bl,SR_LIGHTNINGWALK,sc->data[SC_LIGHTNINGWALK].val1,src->x,src->y,tick);
				clif_move(bl);
				status_change_end(bl, SC_LIGHTNINGWALK, -1);
				unit_movepos(bl,src->x,src->y,0);
			}
		}

		// “_ŒŠ -‹…-
		if(tsd && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && flag&BF_SHORT && damage > 0) {
			int max = (tsd->s_class.job == PC_JOB_MO || tsd->s_class.job == PC_JOB_SR)? pc_checkskill(tsd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sc->data[SC_RAISINGDRAGON].timer != -1)
				max += sc->data[SC_RAISINGDRAGON].val1;
			if(tsd->spiritball.num < max)
				pc_addspiritball(tsd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
		}

		// ƒ_ƒCƒ„ƒ‚ƒ“ƒhƒ_ƒXƒg
		if(sc->data[SC_DIAMONDDUST].timer != -1 && damage > 0) {

			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				status_change_end(bl, SC_DIAMONDDUST, -1);
			}
		}

		// ƒ\[ƒ“ƒgƒ‰ƒbƒv
		if(sc->data[SC_THORNS_TRAP].timer != -1 && damage > 0) {
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				status_change_end(bl, SC_THORNS_TRAP, -1);
			}
		}

		// ƒtƒ@ƒCƒA[ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“(‰Œ–‹)
		if(sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer != -1 && damage > 0 && flag&(BF_SHORT|BF_LONG) && skill_num != PA_PRESSURE) {
			damage -= damage * sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].val2 / 100;
		}

#ifndef PRE_RENEWAL
		// ƒTƒvƒ‰ƒCƒYƒAƒ^ƒbƒN
		if(sc->data[SC_RAID].timer != -1 && sc->data[SC_RAID].val1 > 0) {
			sc->data[SC_RAID].val1--;
			if(status_get_mode(bl)&MD_BOSS)
				damage += damage * 10 / 100;
			else
				damage += damage * 20 / 100;
		}
		// ƒXƒg[ƒ“ƒXƒLƒ“
		if(sc->data[SC_STONESKIN].timer != -1 && damage > 0) {
			if(flag&BF_WEAPON) {
				// ‚¤‚¸‚­‚Ü‚é
				if(sc->data[SC_SU_STOOP].timer != -1 && sc->data[SC_STONESKIN].val1 < 4) {
					damage = damage * 20 / 100;
				}
				else
					damage = damage * (100 - 20 * sc->data[SC_STONESKIN].val1) / 100;
			} else if(flag&BF_MAGIC) {
				damage = damage * (100 + 20 * sc->data[SC_STONESKIN].val1) / 100;
			}
		}
		// ƒAƒ“ƒ`ƒ}ƒWƒbƒN
		if(sc->data[SC_ANTIMAGIC].timer != -1 && damage > 0) {
			if(flag&BF_MAGIC) {
				// ‚¤‚¸‚­‚Ü‚é
				if(sc->data[SC_SU_STOOP].timer != -1 && sc->data[SC_STONESKIN].val1 < 4) {
					damage = damage * 20 / 100;
				}
				else
					damage = damage * (100 - 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
			} else if(flag&BF_WEAPON) {
				damage = damage * (100 + 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
			}
		}
#endif
		// ‚¤‚¸‚­‚Ü‚é
		if(sc->data[SC_SU_STOOP].timer != -1) {
			// ƒXƒg[ƒ“ƒXƒLƒ“AƒAƒ“ƒ`ƒ}ƒWƒbƒN‚Æ‹£‡‚µ‚È‚¢
			if(sc->data[SC_STONESKIN].timer == -1 && sc->data[SC_ANTIMAGIC].timer == -1)
				damage = damage * 20 / 100;
		}
		if(src->type == BL_MOB) {
			int i;
			if(sc->data[SC_MANU_DEF].timer != -1 && damage > 0) {	// ƒ}ƒkƒNƒtƒB[ƒ‹ƒhMOBƒ_ƒ[ƒWŒ¸­
				struct mob_data *md = (struct mob_data *)src;
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == md->class_) {
						damage = damage * sc->data[SC_MANU_DEF].val1 / 100;
						break;
					}
				}
			}
			if(sc->data[SC_SPL_DEF].timer != -1 && damage > 0) {	// ƒXƒvƒŒƒ“ƒeƒBƒbƒhƒtƒB[ƒ‹ƒhMOBƒ_ƒ[ƒWŒ¸­
				struct mob_data *md = (struct mob_data *)src;
				for(i = 0; i < (sizeof(splendide_mob) / sizeof(splendide_mob[0])); i++) {
					if(splendide_mob[i] == md->class_) {
						damage = damage * sc->data[SC_SPL_DEF].val1 / 100;
						break;
					}
				}
			}
		}

		if(sc->data[SC_JP_EVENT03].timer != -1 && damage > 0 && status_get_race(src) == RCT_FISH) {
			damage -= damage * sc->data[SC_JP_EVENT03].val1 / 100;
		}

		// –¾‹¾~…(Šm—¦b’è)
		if(sc->data[SC_MEIKYOUSISUI].timer != -1 && atn_rand()%100 < sc->data[SC_MEIKYOUSISUI].val1 * 2) {
			damage = 0;
		}
	}

	if(damage > 0) {
		struct guild_castle *gc = NULL;
		int noflag = 0;

		if(tmd && tmd->guild_id) {
			if(tmd->class_ == MOBID_EMPERIUM) {
				// ƒGƒ“ƒyƒŠƒEƒ€
				if(flag&BF_SKILL && skill_num != HW_GRAVITATION)
					return 0;
				if(src->type == BL_PC) {
					struct guild *g = guild_search(((struct map_session_data *)src)->status.guild_id);

					if(g == NULL)
						return 0;		// ƒMƒ‹ƒh–¢‰Á“ü‚È‚çƒ_ƒ[ƒW–³‚µ
					if(guild_checkskill(g,GD_APPROVAL) <= 0)
						return 0;		// ³‹KƒMƒ‹ƒh³”F‚ª‚È‚¢‚Æƒ_ƒ[ƒW–³‚µ
					if((gc = guild_mapid2gc(tmd->bl.m)) != NULL) {
						if(g->guild_id == gc->guild_id)
							return 0;	// ©è—ÌƒMƒ‹ƒh‚ÌƒGƒ“ƒy‚È‚çƒ_ƒ[ƒW–³‚µ
						if(guild_check_alliance(gc->guild_id, g->guild_id, 0))
							return 0;	// “¯–¿‚È‚çƒ_ƒ[ƒW–³‚µ
					} else {
						noflag = 1;
					}
				} else {
					return 0;
				}
			} else if(!tmd->master_id && !tmd->state.special_mob_ai) {
				// ‚»‚Ì‘¼‚ÌGvŠÖ˜A‚ÌMOB
				if(src->type == BL_PC) {
					struct guild *g = guild_search(((struct map_session_data *)src)->status.guild_id);
					if(g) {
						if((gc = guild_mapid2gc(tmd->bl.m)) != NULL) {
							if(g->guild_id == gc->guild_id)
								return 0;	// ©è—ÌƒMƒ‹ƒh‚È‚çƒ_ƒ[ƒW–³‚µ
							if(guild_check_alliance(gc->guild_id, g->guild_id, 0))
								return 0;	// “¯–¿‚È‚çƒ_ƒ[ƒW–³‚µ
						} else {
							noflag = 1;
						}
					}
				} else {
					return 0;
				}
			}
		}

		// GvG
		if(map[bl->m].flag.gvg && src->type != BL_HOM && skill_num != PA_PRESSURE && skill_num != HW_GRAVITATION) {
			if(tmd && tmd->guild_id) {
				if(gc == NULL && !noflag)	// ƒGƒ“ƒyƒŠƒEƒ€A‚»‚Ì‘¼‚ÌGvŠÖ˜A‚ÌMOB‚Ì€‚ÅŠù‚ÉŒŸõ‚µ‚ÄNULL‚È‚çÄ“xŒŸõ‚µ‚È‚¢
					gc = guild_mapid2gc(tmd->bl.m);
				if(gc) {	// defense‚ª‚ ‚ê‚Îƒ_ƒ[ƒW‚ªŒ¸‚é‚ç‚µ‚¢H
#ifndef PRE_RENEWAL
					if(tmd->class_ != MOBID_EMPERIUM)
#endif
						damage -= damage * gc->defense / 100 * battle_config.castle_defense_rate / 100;
				}
			}
			if(skill_num != NPC_SELFDESTRUCTION && skill_num != NPC_SELFDESTRUCTION2) {
				if(flag&BF_SKILL) {	// ƒXƒLƒ‹UŒ‚
					if(flag&BF_WEAPON)
						damage = damage * battle_config.gvg_normalskill_damage_rate / 100;
					if(flag&BF_MAGIC)
						damage = damage * battle_config.gvg_magic_damage_rate / 100;
					if(flag&BF_MISC)
						damage = damage * battle_config.gvg_misc_damage_rate / 100;
				} else {	// ’ÊíUŒ‚
					if(flag&BF_SHORT)
						damage = damage * battle_config.gvg_short_damage_rate / 100;
					if(flag&BF_LONG)
						damage = damage * battle_config.gvg_long_damage_rate / 100;
				}
			}
			if(damage < 1)
				damage = (!battle_config.skill_min_damage && flag&BF_MAGIC && src->type == BL_PC)? 0: 1;
		}

		// PK
		if(map[bl->m].flag.pk && bl->type == BL_PC && skill_num != PA_PRESSURE && skill_num != HW_GRAVITATION) {
			if(flag&BF_SKILL) {	// ƒXƒLƒ‹UŒ‚
				if(flag&BF_WEAPON)
					damage = damage * battle_config.pk_normalskill_damage_rate / 100;
				if(flag&BF_MAGIC)
					damage = damage * battle_config.pk_magic_damage_rate / 100;
				if(flag&BF_MISC)
					damage = damage * battle_config.pk_misc_damage_rate / 100;
			} else {	// ’ÊíUŒ‚
				if(flag&BF_SHORT)
					damage = damage * battle_config.pk_short_damage_rate / 100;
				if(flag&BF_LONG)
					damage = damage * battle_config.pk_long_damage_rate / 100;
			}
			if(damage < 1)
				damage = (!battle_config.skill_min_damage && flag&BF_MAGIC && src->type == BL_PC)? 0: 1;
		}
	}

	// –‚“±ƒMƒA‚Ì‰Á”M“xã¸
	if(tsd && src != &tsd->bl && tsd->status.hp > 0 && pc_isgear(tsd) && damage > 0) {
		int limit = status_get_lv(bl);
		int skill = pc_checkskill(tsd,NC_MAINFRAME);

		// ƒƒCƒ“ƒtƒŒ[ƒ€‰ü‘¢‚É‚æ‚éƒŠƒ~ƒbƒgã¸
		if(skill <= 1) {
			limit += 10;
		} else {
			limit += (skill - 1) * 18;
		}

		tsd->overheat++;
		if(tsd->overheat > limit) {
			status_change_start(bl,SC_OVERHEAT,1,0,0,0,300000,0);
			tsd->overheat = 0;
		}
	}

	if((battle_config.skill_min_damage || flag&BF_MISC) && damage > 0) {
		if(div_ == 255) {
			if(damage < 3)
				damage = 3;
		} else {
			if(damage < div_)
				damage = div_;
		}
	}

	if(tmd && tmd->hp > 0 && damage > 0)	// ”½Œ‚‚È‚Ç‚ÌMOBƒXƒLƒ‹”»’è
	{
		int mtg = tmd->target_id;
		if (battle_config.mob_changetarget_byskill != 0 || mtg == 0)
		{
			if(src->type & (BL_PC | BL_MOB | BL_MERC | BL_ELEM))
				tmd->target_id = src->id;
		}
		mobskill_event(tmd,flag);
		tmd->target_id = mtg;	// ƒ^[ƒQƒbƒg‚ğ–ß‚·
	}

	// PC‚Ì”½Œ‚ƒI[ƒgƒXƒyƒ‹
	if(tsd && src != &tsd->bl && !unit_isdead(src) && tsd->status.hp > 0 && damage > 0)
	{
		unsigned int asflag = EAS_REVENGE;

		if(skill_num == AM_DEMONSTRATION)
			flag = (flag&~BF_WEAPONMASK)|BF_MISC;

		if(flag&BF_WEAPON) {
			if(flag&BF_SKILL) {
				if(battle_config.weapon_attack_autospell)
					asflag += EAS_NORMAL;
				else
					asflag += EAS_SKILL;
			} else {
				asflag += EAS_NORMAL;
			}
			if(flag&BF_SHORT)
				asflag += EAS_SHORT;
			if(flag&BF_LONG)
				asflag += EAS_LONG;
		}
		if(flag&BF_MAGIC) {
			if(battle_config.magic_attack_autospell)
				asflag += EAS_SHORT|EAS_LONG;
			else
				asflag += EAS_MAGIC;
		}
		if(flag&BF_MISC) {
			if(battle_config.misc_attack_autospell)
				asflag += EAS_SHORT|EAS_LONG;
			else
				asflag += EAS_MISC;
		}
		bonus_autospell_start(&tsd->bl,src,asflag,tick,0);
		bonus_activeitem_start(tsd,asflag,tick);
	}

	// PC‚Ìó‘ÔˆÙí”½Œ‚
	if(tsd && src != &tsd->bl && tsd->addreveff_flag && !unit_isdead(src) && tsd->status.hp > 0 && damage > 0 && flag&BF_WEAPON)
	{
		int i;

		for(i = 0; i < MAX_EFF_TYPE; i++) {
			int rate = tsd->addreveff[i];
			if(battle_config.reveff_plus_addeff)
				rate += tsd->addeff[i] + tsd->arrow_addeff[i];

			status_change_addeff_start(bl,src,i,rate,0,tick);
		}
	}

	return damage;
}

/*==========================================
 * HP/SP‚Ì“‹zûŒvZ
 *------------------------------------------
 */
static int battle_calc_drain_per(int damage, int rate, int per)
{
	int diff = 0;

	if (damage <= 0 || rate <= 0)
		return 0;

	if (per && atn_rand()%100 < rate) {
		diff = damage * per / 100;
		if (diff == 0)
			diff = (per > 0)? 1: -1;
	}

	return diff;
}

/*==========================================
 * HP/SP‚Ìˆê’è‹zûŒvZ
 *------------------------------------------
 */
static int battle_calc_drain_value(int damage, int rate, int value)
{
	int diff = 0;

	if (damage <= 0 || rate <= 0)
		return 0;

	if (value && atn_rand()%100 < rate) {
		diff = value;
	}

	return diff;
}

/*==========================================
 * UŒ‚‚É‚æ‚éHP/SP‹zû
 *------------------------------------------
 */
static int battle_attack_drain(struct block_list *bl,int damage,int damage2,int flag)
{
	int hp = 0,sp = 0;
	struct map_session_data* sd = NULL;

	nullpo_retr(0, bl);

	if(damage <= 0 && damage2 <= 0)
		return 0;

	if(bl->type != BL_PC || (sd = (struct map_session_data *)bl) == NULL)
		return 0;

	if(flag & 1) {	// “‹zû
		if(!battle_config.left_cardfix_to_right) {
			// “ñ“—¬¶èƒJ[ƒh‚Ì‹zûŒnŒø‰Ê‚ğ‰Eè‚É’Ç‰Á‚µ‚È‚¢ê‡
			hp += battle_calc_drain_per(damage,  sd->hp_drain.p_rate,  sd->hp_drain.per );
			hp += battle_calc_drain_per(damage2, sd->hp_drain_.p_rate, sd->hp_drain_.per);
			sp += battle_calc_drain_per(damage,  sd->sp_drain.p_rate,  sd->sp_drain.per );
			sp += battle_calc_drain_per(damage2, sd->sp_drain_.p_rate, sd->sp_drain_.per);
		} else {
			// “ñ“—¬¶èƒJ[ƒh‚Ì‹zûŒnŒø‰Ê‚ğ‰Eè‚É’Ç‰Á‚·‚éê‡
			int hp_rate = sd->hp_drain.p_rate + sd->hp_drain_.p_rate;
			int hp_per  = sd->hp_drain.per + sd->hp_drain_.per;
			int sp_rate = sd->sp_drain.p_rate + sd->sp_drain_.p_rate;
			int sp_per  = sd->sp_drain.per + sd->sp_drain_.per;
			hp += battle_calc_drain_per(damage, hp_rate, hp_per);
			sp += battle_calc_drain_per(damage, sp_rate, sp_per);
		}
	}
	if(flag & 2) {	// ˆê’è‹zû
		if(!battle_config.left_cardfix_to_right) {
			// “ñ“—¬¶èƒJ[ƒh‚Ì‹zûŒnŒø‰Ê‚ğ‰Eè‚É’Ç‰Á‚µ‚È‚¢ê‡
			hp += battle_calc_drain_value(damage,  sd->hp_drain.v_rate,  sd->hp_drain.value );
			hp += battle_calc_drain_value(damage2, sd->hp_drain_.v_rate, sd->hp_drain_.value);
			sp += battle_calc_drain_value(damage,  sd->sp_drain.v_rate,  sd->sp_drain.value );
			sp += battle_calc_drain_value(damage2, sd->sp_drain_.v_rate, sd->sp_drain_.value);
		} else {
			// “ñ“—¬¶èƒJ[ƒh‚Ì‹zûŒnŒø‰Ê‚ğ‰Eè‚É’Ç‰Á‚·‚éê‡
			int hp_rate  = sd->hp_drain.v_rate + sd->hp_drain_.v_rate;
			int hp_value = sd->hp_drain.value + sd->hp_drain_.value;
			int sp_rate  = sd->sp_drain.v_rate + sd->sp_drain_.v_rate;
			int sp_value = sd->sp_drain.value + sd->sp_drain_.value;
			hp += battle_calc_drain_value(damage, hp_rate, hp_value);
			sp += battle_calc_drain_value(damage, sp_rate, sp_value);
		}
	}
	if(hp || sp)
		pc_heal(sd, hp, sp);

	return 1;
}

/*==========================================
 * C—ûƒ_ƒ[ƒW
 *------------------------------------------
 */
static int battle_addmastery(struct map_session_data *sd,struct block_list *target,int dmg,int type)
{
	int damage = 0, race, element, skill, weapon;

	nullpo_retr(0, sd);
	nullpo_retr(0, target);

	race = status_get_race(target);
	element = status_get_element(target)%20;

	// ƒf[ƒ‚ƒ“ƒxƒCƒ“ vs •s€ or ˆ«–‚ (€l‚ÍŠÜ‚ß‚È‚¢H)
	if((skill = pc_checkskill(sd,AL_DEMONBANE)) > 0 && (battle_check_undead(race,status_get_elem_type(target)) || race == RCT_DEMON) ) {
		damage += (300 + 5 * sd->status.base_level) * skill / 100;
	}

	// ƒr[ƒXƒgƒxƒCƒ“(+4 ` +40) vs “®•¨ or ©’
	if((skill = pc_checkskill(sd,HT_BEASTBANE)) > 0 && (race == RCT_BRUTE || race == RCT_INSECT) )
	{
		damage += (skill * 4);

		if(sd->sc.data[SC_HUNTER].timer != -1)
			damage += status_get_str(&sd->bl);
	}

#ifndef PRE_RENEWAL
	// •ŠíŒ¤‹†(+2 ` +20)
	if((skill = pc_checkskill(sd,BS_WEAPONRESEARCH)) > 0) {
		damage += (skill * 2);
	}
#endif

	// ƒŒƒ“ƒWƒƒ[ƒƒCƒ“(+5 ` +50) vs “®•¨ or A•¨ or ‹›—Ş
	if((skill = pc_checkskill(sd,RA_RANGERMAIN)) > 0 && (race == RCT_BRUTE || race == RCT_PLANT || race == RCT_FISH) )
	{
		damage += (skill * 5);
	}

	// –‚“±ƒMƒAƒ‰ƒCƒZƒ“ƒX(+15 ` +75)
	if(pc_isgear(sd) && (skill = pc_checkskill(sd,NC_MADOLICENCE)) > 0)
	{
		damage += (skill * 15);
	}

	// ‰Î‚Æ‘å’n‚ÌŒ¤‹†(+10 ` +50) vs ‰Î‘®« or ’n‘®«
	if((skill = pc_checkskill(sd,NC_RESEARCHFE)) > 0 && (element == ELE_FIRE || element == ELE_EARTH))
	{
		damage += (skill * 10);
	}

	weapon = (type == 0)? sd->weapontype1: sd->weapontype2;

	switch(weapon)
	{
		case WT_1HSWORD:
#ifndef PRE_RENEWAL
			// ƒAƒ‹ƒPƒ~ƒXƒg•€C—û(+3 ` +30)
			if((skill = pc_checkskill(sd,AM_AXEMASTERY)) > 0) {
				damage += (skill * 3);
			}
#endif
			// fall through
		case WT_DAGGER:
			// Œ•C—û(+4 ` +40) •ĞèŒ• ’ZŒ•ŠÜ‚Ş
			if((skill = pc_checkskill(sd,SM_SWORD)) > 0) {
				damage += (skill * 4);
			}
			// ƒWƒFƒlƒeƒBƒbƒNŒ•C—û(+10 ` +50)
			if((skill = pc_checkskill(sd,GN_TRAINING_SWORD)) > 0) {
				damage += (skill * 10);
			}
			break;
		case WT_2HSWORD:
			// —¼èŒ•C—û(+4 ` +40) —¼èŒ•
			if((skill = pc_checkskill(sd,SM_TWOHAND)) > 0) {
				damage += (skill * 4);
			}
			break;
		case WT_1HSPEAR:
			// ‘„C—û(+4 ` +40,+5 ` +50,+10 ` +100) ‘„
			if((skill = pc_checkskill(sd,KN_SPEARMASTERY)) > 0) {
				if(pc_isdragon(sd) && pc_checkskill(sd,RK_DRAGONTRAINING) >= 5)
					damage += (skill * 10);	// ƒhƒ‰ƒSƒ“‚Éæ‚Á‚Ä‚ÄƒgƒŒ[ƒjƒ“ƒOLvMAX
				else if(!pc_isriding(sd) && !pc_isdragon(sd))
					damage += (skill * 4);	// ƒyƒR‚Éæ‚Á‚Ä‚È‚¢
				else
					damage += (skill * 5);	// ƒyƒR‚Éæ‚Á‚Ä‚é
			}
			break;
		case WT_2HSPEAR:
			// ‘„C—û(+4 ` +40,+5 ` +50,+10 ` +100) ‘„
			if((skill = pc_checkskill(sd,KN_SPEARMASTERY)) > 0) {
				if(pc_isdragon(sd) && pc_checkskill(sd,RK_DRAGONTRAINING) >= 5)
					damage += (skill * 10);	// ƒhƒ‰ƒSƒ“‚Éæ‚Á‚Ä‚ÄƒgƒŒ[ƒjƒ“ƒOLvMAX
				else if(!pc_isriding(sd) && !pc_isdragon(sd))
					damage += (skill * 4);	// ƒyƒR‚Éæ‚Á‚Ä‚È‚¢
				else
					damage += (skill * 5);	// ƒyƒR‚Éæ‚Á‚Ä‚é
			}
			break;
		case WT_1HAXE:
			if((skill = pc_checkskill(sd,AM_AXEMASTERY)) > 0) {
				damage += (skill * 3);
			}
			if((skill = pc_checkskill(sd,NC_TRAININGAXE)) > 0) {
				damage += (skill * 5);
			}
			break;
		case WT_2HAXE:
			if((skill = pc_checkskill(sd,AM_AXEMASTERY)) > 0) {
				damage += (skill * 3);
			}
			if((skill = pc_checkskill(sd,NC_TRAININGAXE)) > 0) {
				damage += (skill * 5);
			}
			break;
		case WT_MACE:
			// ƒƒCƒXC—û(+3 ` +30) ƒƒCƒX
			if((skill = pc_checkskill(sd,PR_MACEMASTERY)) > 0) {
				damage += (skill * 3);
			}
			if((skill = pc_checkskill(sd,NC_TRAININGAXE)) > 0) {
				damage += (skill * 4);
			}
			break;
		case WT_2HMACE:
		case WT_STAFF:
		case WT_2HSTAFF:
		case WT_BOW:
			break;
		case WT_FIST:
			// ƒ^ƒCƒŠƒM(+10 ` +100) ‘fè
			if((skill = pc_checkskill(sd,TK_RUN)) > 0) {
				damage += (skill * 10);
			}
			// fall through
		case WT_KNUCKLE:
			// “SŒ(+3 ` +30) ‘fè,ƒiƒbƒNƒ‹
			if((skill = pc_checkskill(sd,MO_IRONHAND)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_MUSICAL:
			// ŠyŠí‚Ì—ûK(+3 ` +30) ŠyŠí
			if((skill = pc_checkskill(sd,BA_MUSICALLESSON)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_WHIP:
			// ƒ_ƒ“ƒX‚Ì—ûK(+3 ` +30) •Ú
			if((skill = pc_checkskill(sd,DC_DANCINGLESSON)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_BOOK:
			// ƒAƒhƒoƒ“ƒXƒhƒuƒbƒN(+3 ` +30) {
			if((skill = pc_checkskill(sd,SA_ADVANCEDBOOK)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_KATAR:
			// ƒJƒ^[ƒ‹C—û(+3 ` +30) ƒJƒ^[ƒ‹
			if((skill = pc_checkskill(sd,AS_KATAR)) > 0) {
				// ƒ\ƒjƒbƒNƒuƒ[‚Í•Êˆ—i1Œ‚‚É•t‚«1/8“K‰)
				damage += (skill * 3);
			}
			break;
		case WT_HANDGUN:
		case WT_RIFLE:
		case WT_SHOTGUN:
		case WT_GATLING:
		case WT_GRENADE:
		case WT_HUUMA:
			break;
	}
	return dmg+damage;
}

/*==========================================
 * Šî–{•Šíƒ_ƒ[ƒWŒvZ
 *------------------------------------------
 */
static int battle_calc_base_damage(struct block_list *src,struct block_list *target,int skill_num,int type,int lh)
{
	int damage = 0;
	int atkmin, atkmax;
#ifdef PRE_RENEWAL
	int weapon;
#endif
	struct map_session_data *sd   = NULL;
	struct status_change *sc = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	sc = status_get_sc(src);
	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;

	if(sd) {
		int watk   = (lh == 0)? status_get_atk(src): status_get_atk_(src);
		int dex    = status_get_dex(src);
		int idx    = (lh == 0)? sd->equip_index[EQUIP_INDEX_RARM]: sd->equip_index[EQUIP_INDEX_LARM];
#ifdef PRE_RENEWAL
		int t_size = status_get_size(target);
#else
		short wlv  = 0;
		int cost   = 0;
		int str    = status_get_str(src);

		// DexˆË‘¶•Ší‚ÍDex‚ğŠî–{’l‚Æ‚·‚é
		if( sd->status.weapon == WT_BOW ||
			sd->status.weapon == WT_MUSICAL ||
			sd->status.weapon == WT_WHIP ||
			(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) )
			str = dex;
#endif

		if(skill_num == HW_MAGICCRASHER || (skill_num == 0 && sc && sc->data[SC_CHANGE].timer != -1)) {
			// ƒ}ƒWƒbƒNƒNƒ‰ƒbƒVƒƒ[‚Ü‚½‚Íƒƒ“ƒ^ƒ‹ƒ`ƒFƒ“ƒW’†‚Ì’ÊíUŒ‚‚È‚çMATK‚Å‰£‚é
			damage = status_get_matk1(src);
#ifdef PRE_RENEWAL
		} else {
			damage = status_get_baseatk(src);
#endif
		}

		atkmin = dex;	// Å’áATK‚ÍDEX‚Å‰Šú‰»

#ifdef PRE_RENEWAL
		if(idx >= 0 && sd->inventory_data[idx])
			atkmin = atkmin * (80 + sd->inventory_data[idx]->wlv * 20) / 100;
		if(sd->state.arrow_atk)						// •Ší‚ª‹|–î‚Ìê‡
			atkmin = watk * ((atkmin < watk)? atkmin: watk) / 100;	// ‹|—pÅ’áATKŒvZ
		if(sc && sc->data[SC_IMPOSITIO].timer != -1)	// IM‚ª‚©‚©‚Á‚Ä‚¢‚½‚çÅ¬‰ÁZUŒ‚—Í‚É‰ÁZ
			atkmin += sc->data[SC_IMPOSITIO].val1*5;

		/* ƒTƒCƒYC³ */
		if(skill_num == MO_EXTREMITYFIST) {
			// ˆ¢C—…
			atkmax = watk;
		} else if(pc_isriding(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR) && t_size == 1) {
			// ƒyƒR‹Ræ‚µ‚Ä‚¢‚ÄA‘„‚Å’†Œ^‚ğUŒ‚‚µ‚½ê‡‚ÍƒTƒCƒYC³‚ğ100‚É‚·‚é
			atkmax = watk;
		} else if(pc_isdragon(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR)) {
			// ƒhƒ‰ƒSƒ“‹Ræ’†‚Ì‘„‚ÍƒTƒCƒYC³‚ğ100‚É‚·‚é
			atkmax = watk;
		} else {
			int rate = (lh == 0)? sd->atkmods[t_size]: sd->atkmods_[t_size];
			atkmax = (watk   * rate) / 100;
			atkmin = (atkmin * rate) / 100;
		}
		if(sc && sc->data[SC_WEAPONPERFECTION].timer != -1) {
			// ƒEƒFƒ|ƒ“ƒp[ƒtƒFƒNƒVƒ‡ƒ“
			atkmax = watk;
		} else if(sd->special_state.no_sizefix) {
			// ƒhƒŒƒCƒNƒJ[ƒh
			atkmax = watk;
		}
		if(!sd->state.arrow_atk && atkmin > atkmax)
			atkmin = atkmax;	// ‹|‚ÍÅ’á‚ªã‰ñ‚éê‡‚ ‚è
		if(lh && atkmin > atkmax)
			atkmin = atkmax;

		/* ‰ßè¸˜Bƒ{[ƒiƒX */
		if(!lh && sd->overrefine > 0)
			damage += (atn_rand() % sd->overrefine ) + 1;
		if(lh && sd->overrefine_ > 0)
			damage += (atn_rand() % sd->overrefine_) + 1;
#else
		// •Ší‚ª‚ ‚é‚È‚ç•ŠíLv‚ÆƒRƒXƒgŒvZ
		if(idx >= 0 && sd->inventory_data[idx]) {
			int dstr = str/10;
			damage = str + dstr*dstr*dstr/60;	// Strƒ{[ƒiƒXŒvZ
			wlv = sd->inventory_data[idx]->wlv;
			cost = (watk*2/3) - (dstr*dstr) * (80 + wlv * 20) / 100;
			if(cost < 0)	// ƒRƒXƒg‚Í0ˆÈ‰º‚É‚È‚ç‚È‚¢
				cost = 0;
		}
		// Å‘å•ŠíAtk‚ÆÅ’á•ŠíAtkŒvZ
		atkmin = atkmin * (80 + wlv * 20) / 100 - cost;
		atkmax = watk * (140 + wlv * 10) / 100 - cost;
		if(atkmin > atkmax)
			atkmin = atkmax;
#endif
	} else {
#ifdef PRE_RENEWAL
		if(battle_config.enemy_str)
			damage = status_get_baseatk(src);
		else
			damage = 0;
#endif
		if(skill_num == HW_MAGICCRASHER || (skill_num == 0 && sc && sc->data[SC_CHANGE].timer != -1)) {
			// ƒ}ƒWƒbƒNƒNƒ‰ƒbƒVƒƒ[‚Ü‚½‚Íƒƒ“ƒ^ƒ‹ƒ`ƒFƒ“ƒW’†‚Ì’ÊíUŒ‚‚È‚çMATK‚Å‰£‚é
			atkmin = status_get_matk1(src);
			atkmax = status_get_matk2(src);
		} else {
			atkmin = status_get_atk(src);
			atkmax = status_get_atk2(src);
		}
		if(atkmin > atkmax)
			atkmin = atkmax;
	}

	if(sc && sc->data[SC_MAXIMIZEPOWER].timer != -1) {
		// ƒ}ƒLƒVƒ}ƒCƒYƒpƒ[
		atkmin = atkmax;
	}

#ifdef PRE_RENEWAL
	if(type == 0x0a)
#else
	if(type == 0x0a || skill_num == NPC_CRITICALSLASH)
#endif
	{
		/* ƒNƒŠƒeƒBƒJƒ‹UŒ‚ */
		damage += atkmax;

		if(sc) {
			// “_ŒŠ -”½-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				damage += sc->data[SC_GENTLETOUCH_CHANGE].val2;
			}
			// ƒXƒgƒ‰ƒCƒLƒ“ƒO
			if(sc->data[SC_STRIKING].timer != -1) {
				damage += sc->data[SC_STRIKING].val3;
			}
		}
#ifdef PRE_RENEWAL
		if(sd) {
			int trans_bonus = 0;

			weapon = (lh == 0)? sd->weapontype1: sd->weapontype2;
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && (sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1276 || sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1884))
				trans_bonus = 25;
			if(weapon < WT_MAX) {
				if(sd->atk_rate != 100 || sd->weapon_atk_rate[weapon] != 0)
					damage = (damage * (sd->atk_rate + sd->weapon_atk_rate[weapon] + trans_bonus)) / 100;
			}

			// ƒNƒŠƒeƒBƒJƒ‹ƒ_ƒ[ƒW‘‰Á
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1002)
				trans_bonus = 5;
			damage += damage * (sd->critical_damage + trans_bonus) / 100;

			if(sd->state.arrow_atk)
				damage += sd->arrow_atk;
		}
#endif
	} else {
		/* ’ÊíUŒ‚EƒXƒLƒ‹UŒ‚ */
		if(atkmax > atkmin)
			damage += atkmin + atn_rand() % (atkmax - atkmin + 1);
		else
			damage += atkmin;

		if(sc) {
			// “_ŒŠ -”½-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				damage += sc->data[SC_GENTLETOUCH_CHANGE].val2;
			}
			// ƒXƒgƒ‰ƒCƒLƒ“ƒO
			if(sc->data[SC_STRIKING].timer != -1) {
				damage += sc->data[SC_STRIKING].val3;
			}
			// •—Ô‚ÉŒü‚©‚Á‚Ä“ËŒ‚
			if(sc->data[SC_RUSH_WINDMILL].timer != -1) {
				damage += sc->data[SC_RUSH_WINDMILL].val4;
			}
		}
#ifdef PRE_RENEWAL
		if(sd) {
			int trans_bonus = 0;

			weapon = (lh == 0)? sd->weapontype1: sd->weapontype2;
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && (sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1276 || sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1884))
				trans_bonus = 25;
			if(weapon < WT_MAX) {
				if(sd->atk_rate != 100 || sd->weapon_atk_rate[weapon] != 0) {
					damage = (damage * (sd->atk_rate + sd->weapon_atk_rate[weapon] + trans_bonus)) / 100;
				}
			}
		}
#endif
	}

#ifndef PRE_RENEWAL
	if(sd) {
		int t_size = status_get_size(target);

		switch(skill_num) {
		case NJ_ZENYNAGE:
		case KO_MUCHANAGE:
			break;
		default:
			if(!lh)
				damage += status_get_atk2(src);
			if(lh)
				damage += status_get_atk_2(src);
			break;
		}

		/* ‰ßè¸˜Bƒ{[ƒiƒX */
		if( sd->status.weapon != WT_BOW &&	// ‹|‚Æe‚É‚Í‰ßè¸˜Bƒ{[ƒiƒX‚ª‚È‚¢
			(sd->status.weapon < WT_HANDGUN || sd->status.weapon > WT_GRENADE) ) {
			if(!lh && sd->overrefine > 0)
				damage += (atn_rand() % sd->overrefine ) + 1;
			if(lh && sd->overrefine_ > 0)
				damage += (atn_rand() % sd->overrefine_) + 1;
		}

		/* ƒTƒCƒYC³ */
		if(pc_isriding(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR) && t_size == 1) {
			// ƒyƒR‹Ræ‚µ‚Ä‚¢‚ÄA‘„‚Å’†Œ^‚ğUŒ‚‚µ‚½ê‡‚ÍƒTƒCƒYC³‚ğ100‚É‚·‚é
		} else if(pc_isdragon(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR)) {
			// ƒhƒ‰ƒSƒ“‹Ræ’†‚Ì‘„‚ÍƒTƒCƒYC³‚ğ100‚É‚·‚é
		} else if(sc && sc->data[SC_WEAPONPERFECTION].timer != -1) {
			// ƒEƒFƒ|ƒ“ƒp[ƒtƒFƒNƒVƒ‡ƒ“
		} else if(sd->special_state.no_sizefix) {
			// ƒhƒŒƒCƒNƒJ[ƒh
		} else {
			int rate = (lh == 0)? sd->atkmods[t_size]: sd->atkmods_[t_size];
			damage = (damage * rate) / 100;
		}
	}
#endif

	return damage;
}

// ¶è”»’è‚ª‚ ‚é‚Æ‚«‚¾‚¯damage2‚ğŒvZ‚·‚é
#define DMG_FIX( a,b ) { wd.damage = wd.damage*(a+(add_rate*b/100))/(b); if(calc_flag.lh) wd.damage2 = wd.damage2*(a+(add_rate*b/100))/(b); }
#define DMG_ADD( a )   { wd.damage += (a); if(calc_flag.lh) wd.damage2 += (a); }
#define DMG_SET( a )   { wd.damage = (a); if(calc_flag.lh) wd.damage2 = (a); }

/*==========================================
 * •Šíƒ_ƒ[ƒWŒvZ
 *------------------------------------------
 */
static struct Damage battle_calc_weapon_attack(struct block_list *src,struct block_list *target,int skill_num,int skill_lv,int wflag)
{
	struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	struct map_session_data *src_sd  = NULL, *target_sd  = NULL;
	struct mob_data         *src_md  = NULL, *target_md  = NULL;
	struct pet_data         *src_pd  = NULL;
	struct homun_data       *src_hd  = NULL;
	struct merc_data        *src_mcd = NULL;
	struct elem_data        *src_eld = NULL;
	struct status_change    *sc      = NULL, *t_sc       = NULL;
	int s_ele, s_ele_, s_str;
	int t_vit, t_race, t_ele, t_enemy, t_size, t_mode, t_group, t_class;
	int t_flee, t_def1, t_def2;
	int cardfix, skill, damage_sbr = 0;
	int ignored_rate = 100, ignored_rate_ = 100;
	int i;
	int add_rate = 0;
	struct {
		int rh;			// ‰Eè
		int lh;			// ¶è
		int hitrate;		// ƒqƒbƒgŠm—¦
		int autocounter;	// ƒI[ƒgƒJƒEƒ“ƒ^[ON
		int da;			// ˜AŒ‚”»’èi0`2j
		int idef;		// DEF–³‹
		int idef_;		// DEf–³‹i¶èj
		int nocardfix;		// ƒJ[ƒh•â³‚È‚µ
	} calc_flag;

	memset(&calc_flag, 0, sizeof(calc_flag));

	// return‘O‚Ìˆ—‚ª‚ ‚é‚Ì‚Åî•ño—Í•”‚Ì‚İ•ÏX
	if(src == NULL || target == NULL) {
		nullpo_info(NLP_MARK);
		return wd;
	}

	src_sd  = BL_DOWNCAST( BL_PC,   src );
	src_md  = BL_DOWNCAST( BL_MOB,  src );
	src_pd  = BL_DOWNCAST( BL_PET,  src );
	src_hd  = BL_DOWNCAST( BL_HOM,  src );
	src_mcd = BL_DOWNCAST( BL_MERC, src );
	src_eld = BL_DOWNCAST( BL_ELEM, src );

	target_sd  = BL_DOWNCAST( BL_PC,   target );
	target_md  = BL_DOWNCAST( BL_MOB,  target );

	// ƒAƒ^ƒbƒJ[
	s_ele  = status_get_attack_element(src);	// ‘®«
	s_ele_ = status_get_attack_element2(src);	// ¶è‘®«
	s_str  = status_get_str(src);			// STR
	sc     = status_get_sc(src);		// ƒXƒe[ƒ^ƒXˆÙí

	// ƒ^[ƒQƒbƒg
	t_vit   = status_get_vit(target);
	t_race  = status_get_race(target);		// ‘ÎÛ‚Ìí‘°
	t_ele   = status_get_elem_type(target);	// ‘ÎÛ‚Ì‘®«
	t_enemy = status_get_enemy_type(target);	// ‘ÎÛ‚Ì“Gƒ^ƒCƒv
	t_size  = status_get_size(target);		// ‘ÎÛ‚ÌƒTƒCƒY
	t_mode  = status_get_mode(target);		// ‘ÎÛ‚ÌMode
	t_group = status_get_group(target);
	t_class = status_get_class(target);
	t_flee  = status_get_flee(target);
	t_def1  = status_get_def(target);
	t_def2  = status_get_def2(target);
	t_sc    = status_get_sc(target);		// ‘ÎÛ‚ÌƒXƒe[ƒ^ƒXˆÙí

	if(src_sd && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP &&
	   skill_num != LG_RAYOFGENESIS && skill_num != SO_VARETYR_SPEAR)
		src_sd->state.attack_type = BF_WEAPON;	// UŒ‚ƒ^ƒCƒv‚Í•ŠíUŒ‚

	/* ‚PDƒI[ƒgƒJƒEƒ“ƒ^[ˆ— */
	if(skill_lv >= 0 && (skill_num == 0 || (target_sd && battle_config.pc_auto_counter_type&2) ||
		(target_md && battle_config.monster_auto_counter_type&2))
	) {
		if( skill_num != CR_GRANDCROSS &&
		    skill_num != NPC_GRANDDARKNESS &&
		    skill_num != RA_CLUSTERBOMB &&
		    skill_num != RA_FIRINGTRAP &&
		    skill_num != RA_ICEBOUNDTRAP &&
		    skill_num != LG_RAYOFGENESIS &&
		    skill_num != SO_VARETYR_SPEAR &&
		    t_sc &&
		    t_sc->data[SC_AUTOCOUNTER].timer != -1 )
		{
			// ƒOƒ‰ƒ“ƒhƒNƒƒX‚Å‚È‚­A‘ÎÛ‚ªƒI[ƒgƒJƒEƒ“ƒ^[ó‘Ô‚Ìê‡
			int dir   = path_calc_dir(src,target->x,target->y);
			int t_dir = status_get_dir(target);
			int dist  = unit_distance(src,target);

			if(dist <= 0 || path_check_dir(dir,t_dir) ) {
				// ‘ÎÛ‚Æ‚Ì‹——£‚ª0ˆÈ‰ºA‚Ü‚½‚Í‘ÎÛ‚Ì³–ÊH
				t_sc->data[SC_AUTOCOUNTER].val3 = 0;
				t_sc->data[SC_AUTOCOUNTER].val4 = 1;
				if(sc && sc->data[SC_AUTOCOUNTER].timer == -1) {
					int range = status_get_range(target);
					// ©•ª‚ªƒI[ƒgƒJƒEƒ“ƒ^[ó‘Ô
					if( target_sd &&
						(target_sd->status.weapon != WT_BOW && !(target_sd->status.weapon >= WT_HANDGUN && target_sd->status.weapon <= WT_GRENADE))
						&& dist <= range+1)
					{
						// ‘ÎÛ‚ªPC‚Å•Ší‚ª‹|–î‚Å‚È‚­Ë’ö“à
						t_sc->data[SC_AUTOCOUNTER].val3 = src->id;
					}
					if( target_md && range <= 3 && dist <= range+1 ) {
						// ‚Ü‚½‚Í‘ÎÛ‚ªMob‚ÅË’ö‚ª3ˆÈ‰º‚ÅË’ö“à
						t_sc->data[SC_AUTOCOUNTER].val3 = src->id;
					}
				}
				return wd; // ƒ_ƒ[ƒW\‘¢‘Ì‚ğ•Ô‚µ‚ÄI—¹
			}
			calc_flag.autocounter = 1;
		}
	}

	// ƒLƒ“ƒOƒXƒOƒŒƒCƒX
	if(t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return wd;

	/* ‚QD‰Šú‰»•â³ */
	if( (src_sd && battle_config.pc_attack_attr_none) ||
	    (src_md && battle_config.mob_attack_attr_none) ||
	    (src_pd && battle_config.pet_attack_attr_none) ||
	     src_hd || src_mcd || src_eld )
	{
		// ‘®«–³‚µ(!=–³‘®«)
		if (s_ele == ELE_NEUTRAL)
			s_ele  = ELE_NONE;
		if (s_ele_ == ELE_NEUTRAL)
			s_ele_ = ELE_NONE;
	}

#ifdef PRE_RENEWAL
	calc_flag.hitrate = status_get_hit(src) - t_flee + 80;	// pre–½’†—¦ŒvZ
#else
	calc_flag.hitrate = status_get_hit(src) - t_flee;	// RE–½’†—¦ŒvZ
#endif

	if(t_sc && t_sc->data[SC_FOGWALL].timer != -1) {
		// –¶‚ÌHIT•â³
		calc_flag.hitrate -= 50;
	}
	if(src_sd) {
		// •€C—û
		if((skill = pc_checkskill(src_sd,NC_TRAININGAXE)) > 0) {
			if(src_sd->status.weapon == WT_1HAXE || src_sd->status.weapon == WT_2HAXE)
				calc_flag.hitrate += skill*3;
			if(src_sd->status.weapon == WT_MACE)
				calc_flag.hitrate += skill*2;
		}
		// •ŠíŒ¤‹†
		calc_flag.hitrate += calc_flag.hitrate * 2 * pc_checkskill(src_sd, BS_WEAPONRESEARCH) / 100;
	}

	/* ‚RDwd\‘¢‘Ì‚Ì‰Šúİ’è */
	wd.type      = 0;
	wd.div_      = skill_get_num(skill_num,skill_lv);
	wd.blewcount = skill_get_blewcount(skill_num,skill_lv);
	wd.flag      = BF_SHORT | BF_WEAPON | BF_NORMAL;	// UŒ‚‚Ìí—Ş‚Ìİ’è

	if(skill_num == GS_DESPERADO)
		wd.div_ = 1;
	else if(wd.div_ <= 0)
		wd.div_ = 1;

	if(src_sd) {
		if(src_sd->status.weapon == WT_BOW || (src_sd->status.weapon >= WT_HANDGUN && src_sd->status.weapon <= WT_GRENADE)) {	// •Ší‚ª‹|–î‚Ìê‡
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;	// ‰“‹——£UŒ‚ƒtƒ‰ƒO‚ğ—LŒø
			if(src_sd->arrow_ele > ELE_NEUTRAL)	// ‘®«–î‚È‚ç‘®«‚ğ–î‚Ì‘®«‚É•ÏX
				s_ele = src_sd->arrow_ele;
			src_sd->state.arrow_atk = 1;	// —LŒø‰»
		} else {
			src_sd->state.arrow_atk = 0;	// ‰Šú‰»
		}
	} else if(src_md || src_pd || src_mcd || src_eld) {
		if(status_get_range(src) > 3)
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
	}

	/* ‚SD‰EèE¶è”»’è */
	calc_flag.rh = 1;		// Šî–{‚Í‰Eè‚Ì‚İ
	if(src_sd && skill_num == 0) {	// ƒXƒLƒ‹UŒ‚‚Íí‚É‰Eè‚ğQÆ
		if((src_sd->weapontype1 == WT_FIST && src_sd->weapontype2 > WT_FIST) || (src_sd->status.weapon >= WT_DOUBLE_DD || src_sd->status.weapon == WT_KATAR))
			calc_flag.lh = 1;	// ¶è‚àŒvZ
	}

	/* ‚TD˜AŒ‚”»’è */
	if(src_sd && skill_num == 0 && skill_lv >= 0) {
		do {
			// ƒtƒBƒA[ƒuƒŠ[ƒY
			if(sc && sc->data[SC_FEARBREEZE].timer != -1) {
				if(atn_rand()%100 < sc->data[SC_FEARBREEZE].val2) {
					calc_flag.da = 2;
					break;
				}
			}
			// ƒ_ƒuƒ‹ƒAƒ^ƒbƒN
			if((skill = pc_checkskill(src_sd,TF_DOUBLE)) > 0 && src_sd->weapontype1 == WT_DAGGER && atn_rand()%100 < skill*5) {
				calc_flag.da = 1;
				calc_flag.hitrate = calc_flag.hitrate*(100+skill)/100;
				break;
			}
			// ‰e•Ò
			if(sc && sc->data[SC_KAGEMUSYA].timer != -1) {
				if((skill = sc->data[SC_KAGEMUSYA].val1) > 0 && atn_rand()%100 < skill*5) {
					calc_flag.da = 1;
					calc_flag.hitrate = calc_flag.hitrate*(100+skill)/100;
				}
				break;
			}
			// ƒ`ƒF[ƒ“ƒAƒNƒVƒ‡ƒ“
			if((skill = pc_checkskill(src_sd,GS_CHAINACTION)) > 0 && src_sd->weapontype1 == WT_HANDGUN && atn_rand()%100 < skill*5) {
				calc_flag.da = 1;
				break;
			}
			// ƒTƒCƒhƒƒCƒ“ƒ_[“™
			if(src_sd->double_rate > 0 && atn_rand()%100 < src_sd->double_rate) {
				calc_flag.da = 1;
				break;
			}
		} while(0);
	} else if (src_md && skill_num == 0) {
		do {
			// ƒ_ƒuƒ‹ƒAƒ^ƒbƒN
			if (mobdb_search(src_md->class_)->mode_opt[MDOPT_DOUBLE] && atn_rand() % 100 < mobdb_search(src_md->class_)->mode_opt[MDOPT_DOUBLE]*5)
			{
				calc_flag.da = 1;
				calc_flag.hitrate = calc_flag.hitrate * 110 / 100;
				break;
			}
		} while (0);
	}

	/* ‚UDƒNƒŠƒeƒBƒJƒ‹ŒvZ */
	if( calc_flag.da == 0 &&
	    (skill_num == 0 || skill_num == KN_AUTOCOUNTER || skill_num == SN_SHARPSHOOTING || skill_num == NJ_KIRIKAGE || skill_num == MA_SHARPSHOOTING || skill_num == LG_PINPOINTATTACK) &&
	    (!src_md || battle_config.enemy_critical || mobdb_search(src_md->class_)->mode_opt[MDOPT_CRITICAL]) &&
	    skill_lv >= 0 )
	{
		// ˜AŒ‚‚ª”­“®‚µ‚Ä‚È‚­‚ÄA’ÊíUŒ‚EƒI[ƒgƒJƒEƒ“ƒ^[EƒVƒƒ[ƒvƒVƒ…[ƒeƒBƒ“ƒOE‰ea‚è‚È‚ç‚Î
		int cri = status_get_critical(src);
		if(src_sd) {
			cri += src_sd->critical_race[t_race];
			if(src_sd->state.arrow_atk)
				cri += src_sd->arrow_cri;
			if(src_sd->status.weapon == WT_KATAR)
				cri <<= 1;	// ƒJƒ^[ƒ‹‚Ìê‡AƒNƒŠƒeƒBƒJƒ‹‚ğ”{‚É
		}
		cri -= status_get_luk(target) * 3;
		if(src_md && battle_config.enemy_critical_rate != 100) {
			cri = cri * battle_config.enemy_critical_rate / 100;
			if(cri < 1) cri = 1;
		}
		if(t_sc && t_sc->data[SC_SLEEP].timer != -1)
			cri <<= 1;		// ‡–°’†‚ÍƒNƒŠƒeƒBƒJƒ‹‚ª”{‚É
		if(sc && sc->data[SC_CAMOUFLAGE].timer != -1 && sc->data[SC_CAMOUFLAGE].val3 >= 0)	// ƒJƒ‚ƒtƒ‰[ƒWƒ…
			cri += 1000 - (10 - sc->data[SC_CAMOUFLAGE].val3) * 100;
		if(src_sd && pc_isdoram(src_sd) && t_race == RCT_HUMAN)
			cri += 20;
		if(calc_flag.autocounter)
			cri = 1000;

		if(skill_num == KN_AUTOCOUNTER) {
			if(!(battle_config.pc_auto_counter_type&1))
				cri = 1000;
			else
				cri <<= 1;
		} else if(skill_num == SN_SHARPSHOOTING || skill_num == MA_SHARPSHOOTING) {
			cri += 200;
		} else if(skill_num == NJ_KIRIKAGE) {
			cri += (250+skill_lv*50);
		} else if(skill_num == LG_PINPOINTATTACK) {
			cri = 1000;
		}

		if(target_sd && target_sd->critical_def) {
			if(target_sd->critical_def > 100)
				cri = 0;
			else
				cri = cri * (100 - target_sd->critical_def) / 100;
		}

		// Šm—¦”»’è
		if(atn_rand() % 1000 < cri) {
			if(skill_num == SN_SHARPSHOOTING || skill_num == NJ_KIRIKAGE || skill_num == MA_SHARPSHOOTING) {
				// DEF–³‹ƒtƒ‰ƒO
				calc_flag.idef = calc_flag.idef_ = 1;
			} else {
				wd.type = 0x0a;	// ƒNƒŠƒeƒBƒJƒ‹UŒ‚
			}
		}
	}

	/* ‚VDƒqƒbƒgE‘®«EƒŒƒ“ƒWEƒqƒbƒg‰ñ”C³ */
	if(wd.type == 0) {
		int e = ELE_NONE;

		// –î‚ª‚ ‚é‚È‚çƒqƒbƒg‚ğ‰ÁZ
		if(src_sd && src_sd->state.arrow_atk) {
			calc_flag.hitrate += src_sd->arrow_hit;
		}

		// ‘®«•ÏX
		if(skill_num > 0) {
			wd.flag = (wd.flag&~BF_SKILLMASK)|BF_SKILL;
			e = skill_get_pl(skill_num);
		}
		if(e != ELE_NONE && e != ELE_NEUTRAL) {
			s_ele = s_ele_ = e;
		} else {
			e = status_get_attack_element_nw(src);
			if(e != ELE_NEUTRAL) {
				// •Ší‚É‘®«‚ª•t—^‚³‚ê‚Ä‚¢‚é‚È‚çA•t—^‘®«‚É•ÏX
				s_ele = s_ele_ = e;
			}
		}

		// ‚±‚±‚©‚ç‹——£‚É‚æ‚é”»’è
		switch(skill_get_range_type(skill_num)) {
			case 0:	// ‹ß‹——£
				if(skill_num != 0)
					wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
				break;
			case 1:	// ’Êí‰“‹——£
				if(battle_config.calc_dist_flag&1 && (src->type != BL_PC || target->type != BL_PC)) {	// PC vs PC‚Í‹­§–³‹
					int target_dist = unit_distance(src,target);	// ‹——£‚ğæ“¾
					if(target_dist < battle_config.allow_sw_dist) {	// İ’è‚µ‚½‹——£‚æ‚è¬‚³‚¢‹ß‹——£‚©‚ç‚ÌUŒ‚
						if(src->type == BL_PC && battle_config.sw_def_type & 1) {	// lŠÔ‚©‚ç‚Ì‚ğ”»’è‚·‚é‚© +1‚Å‚·‚é
							wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
							break;
						} else if(src->type == BL_MOB && battle_config.sw_def_type & 2) {	// ƒ‚ƒ“ƒXƒ^[‚©‚ç‚Ì‚ğ”»’è‚·‚é‚© +2‚Å‚·‚é
							wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
							break;
						}
					}
				}
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
				break;
			case 2:	// ‹­§‰“‹——£
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
				break;
		}

		switch( skill_num ) {
		case SM_BASH:			// ƒoƒbƒVƒ…
		case MS_BASH:
			calc_flag.hitrate = calc_flag.hitrate*(100+5*skill_lv)/100;
			break;
		case KN_PIERCE:			// ƒsƒA[ƒX
		case ML_PIERCE:
			calc_flag.hitrate = calc_flag.hitrate*(100+5*skill_lv)/100;
			wd.div_ = t_size + 1;
			break;
		case SM_MAGNUM:			// ƒ}ƒOƒiƒ€ƒuƒŒƒCƒN
		case MS_MAGNUM:
			if(src_md && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over)
				calc_flag.hitrate = calc_flag.hitrate*10;
			else
				calc_flag.hitrate = calc_flag.hitrate*(100+10*skill_lv)/100;
			break;
		case KN_AUTOCOUNTER:		// ƒI[ƒgƒJƒEƒ“ƒ^[
			wd.flag = (wd.flag&~BF_SKILLMASK)|BF_NORMAL;
			if(battle_config.pc_auto_counter_type&1)
				calc_flag.hitrate += 20;
			else
				calc_flag.hitrate = 1000000;
			break;
		case AS_SONICBLOW:		// ƒ\ƒjƒbƒNƒuƒ[
			if(src_sd && pc_checkskill(src_sd,AS_SONICACCEL) > 0)
				calc_flag.hitrate = calc_flag.hitrate*150/100;
			break;
		case CR_SHIELDBOOMERANG:	// ƒV[ƒ‹ƒhƒu[ƒƒ‰ƒ“
			if(sc && sc->data[SC_CRUSADER].timer != -1)
				calc_flag.hitrate = 1000000;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case CR_ACIDDEMONSTRATION:	// ƒAƒVƒbƒhƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case GN_FIRE_EXPANSION_ACID:	// ƒtƒ@ƒCƒA[ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“(‰–_)
		case NPC_CRITICALSLASH:		// –hŒä–³‹UŒ‚
		case NPC_GUIDEDATTACK:		// ƒKƒCƒfƒbƒhƒAƒ^ƒbƒN
#ifdef PRE_RENEWAL
		case AM_ACIDTERROR:		// ƒAƒVƒbƒhƒeƒ‰[
		case MO_INVESTIGATE:		// ”­™¤
#endif
		case KO_BAKURETSU:		// ”š—ô‹ê–³
			calc_flag.hitrate = 1000000;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case MO_EXTREMITYFIST:		// ˆ¢C—…”e–PŒ
		case NJ_ISSEN:			// ˆê‘M
			calc_flag.hitrate = 1000000;
#ifdef PRE_RENEWAL
			s_ele = s_ele_ = ELE_NEUTRAL;
#endif
			break;
		case HVAN_EXPLOSION:		// ƒoƒCƒIƒGƒNƒXƒvƒ[ƒWƒ‡ƒ“
		case RG_BACKSTAP:		// ƒoƒbƒNƒXƒ^ƒu
#ifdef PRE_RENEWAL
		case CR_GRANDCROSS:		// ƒOƒ‰ƒ“ƒhƒNƒƒX
		case NPC_GRANDDARKNESS:		// ƒOƒ‰ƒ“ƒhƒ_[ƒNƒlƒX
		case AM_DEMONSTRATION:		// ƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
#endif
		case TK_COUNTER:		// ƒAƒvƒ`ƒƒƒIƒ‹ƒŠƒM
		case AS_SPLASHER:		// ƒxƒiƒ€ƒXƒvƒ‰ƒbƒVƒƒ[
#ifndef PRE_RENEWAL
		case MO_INVESTIGATE:		// ”­™¤
		case GS_MAGICALBULLET:	// ƒ}ƒWƒJƒ‹ƒoƒŒƒbƒg
		case ASC_BREAKER:		// ƒ\ƒEƒ‹ƒuƒŒƒCƒJ[
#endif
		case NPC_EXPULSION:		// ƒGƒNƒXƒpƒ‹ƒVƒIƒ“
		case RK_DRAGONBREATH:	// ƒtƒ@ƒCƒA[ƒhƒ‰ƒSƒ“ƒuƒŒƒX
		case RK_DRAGONBREATH_WATER:	// ƒEƒH[ƒ^[ƒhƒ‰ƒSƒ“ƒuƒŒƒX
		case GC_PHANTOMMENACE:		// ƒtƒ@ƒ“ƒgƒ€ƒƒiƒX
		case RA_SENSITIVEKEEN:		// ‰s•q‚ÈškŠo
		case NC_SELFDESTRUCTION:	// ƒZƒ‹ƒtƒfƒBƒXƒgƒ‰ƒNƒVƒ‡ƒ“
			calc_flag.hitrate = 1000000;
			break;
#ifndef PRE_RENEWAL
		case CR_GRANDCROSS:		// ƒOƒ‰ƒ“ƒhƒNƒƒX
		case NPC_GRANDDARKNESS:		// ƒOƒ‰ƒ“ƒhƒ_[ƒNƒlƒX
		case AM_DEMONSTRATION:		// ƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case AM_ACIDTERROR:		// ƒAƒVƒbƒhƒeƒ‰[
			if(src_sd) s_ele = s_ele_ = src_sd->atk_ele;
			e = status_get_attack_element_nw(src);
			if(e != ELE_NEUTRAL) {
				// •Ší‚É‘®«‚ª•t—^‚³‚ê‚Ä‚¢‚é‚È‚çA•t—^‘®«‚É•ÏX
				s_ele = s_ele_ = e;
			}
			calc_flag.hitrate = 1000000;
			break;
#endif
		case GS_TRACKING:		// ƒgƒ‰ƒbƒLƒ“ƒO
			calc_flag.hitrate = calc_flag.hitrate*4+5;
			break;
		case MO_FINGEROFFENSIVE:	// w’e
			if(src_sd && battle_config.finger_offensive_type == 0) {
				wd.div_ = src_sd->spiritball.old;
			} else {
				wd.div_ = 1;
			}
			break;
		case AS_VENOMKNIFE:		// ƒxƒiƒ€ƒiƒCƒt
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				if(src_sd->arrow_ele > ELE_NEUTRAL)	// ‘®«–î‚È‚ç‘®«‚ğ–î‚Ì‘®«‚É•ÏX
					s_ele = src_sd->arrow_ele;
			}
			break;
		case NPC_COMBOATTACK:		// ‘½’iUŒ‚
		case NPC_RANDOMATTACK:		// ƒ‰ƒ“ƒ_ƒ€ATKUŒ‚
		case NPC_RANGEATTACK:		// ‰“‹——£UŒ‚
		case NJ_ZENYNAGE:		// ‘K“Š‚°
		case NPC_CRITICALWOUND:		// ’v–½UŒ‚
		case KO_MUCHANAGE:			// –³’ƒ“Š‚°
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case PA_SHIELDCHAIN:		// ƒV[ƒ‹ƒhƒ`ƒFƒCƒ“
			calc_flag.hitrate += 20;
#ifdef PRE_RENEWAL
			s_ele = s_ele_ = ELE_NEUTRAL;
#endif
			break;
		case NPC_PIERCINGATT:		// “Ë‚«h‚µUŒ‚
		case CR_SHIELDCHARGE:		// ƒV[ƒ‹ƒhƒ`ƒƒ[ƒW
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case BA_MUSICALSTRIKE:		// ƒ~ƒ…[ƒWƒJƒ‹ƒXƒgƒ‰ƒCƒN
		case DC_THROWARROW:		// –îŒ‚‚¿
		case CG_ARROWVULCAN:		// ƒAƒ[ƒoƒ‹ƒJƒ“
			if(src_sd)
				s_ele = src_sd->arrow_ele;
			break;
		case NJ_SYURIKEN:		// è— Œ•“Š‚°
		case NJ_KUNAI:			// ‹ê–³“Š‚°
#ifndef PRE_RENEWAL
			calc_flag.hitrate = 1000000;
#endif
			if(src_sd && src_sd->arrow_ele > ELE_NEUTRAL)	// ‘®«–î‚È‚ç‘®«‚ğ–î‚Ì‘®«‚É•ÏX
				s_ele = src_sd->arrow_ele;
			break;
#ifndef PRE_RENEWAL
		case NJ_TATAMIGAESHI:	// ô•Ô‚µ
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			break;
#endif
		case GC_VENOMPRESSURE:	// ƒxƒiƒ€ƒvƒŒƒbƒVƒƒ[
			calc_flag.hitrate += 10 + skill_lv * 4;
			break;
		case RA_AIMEDBOLT:		// ƒGƒCƒ€ƒhƒ{ƒ‹ƒg
			if(t_sc && (t_sc->data[SC_ANKLE].timer != -1 || t_sc->data[SC_ELECTRICSHOCKER].timer != -1 || t_sc->data[SC_WUGBITE].timer != -1)) {
				status_change_end(target,SC_ANKLE,-1);
				status_change_end(target,SC_ELECTRICSHOCKER,-1);
				status_change_end(target,SC_WUGBITE,-1);
				wd.div_ = t_size + 2 + atn_rand()%2;
			}
			break;
		case RA_WUGDASH:		// ƒEƒH[ƒOƒ_ƒbƒVƒ…
		case RA_WUGSTRIKE:		// ƒEƒH[ƒOƒXƒgƒ‰ƒCƒN
		case RA_WUGBITE:		// ƒEƒH[ƒOƒoƒCƒg
			if(src_sd && src_sd->arrow_ele > ELE_NEUTRAL)	// ‘®«–î‚È‚ç‘®«‚ğ–î‚Ì‘®«‚É•ÏX
				s_ele = src_sd->arrow_ele;
			break;
		case NC_ARMSCANNON:
		case GN_CARTCANNON:		// ƒJ[ƒgƒLƒƒƒmƒ“
		case KO_HAPPOKUNAI:		// ”ª•û‹ê–³
			calc_flag.hitrate = 1000000;
			if(src_sd && src_sd->arrow_ele > ELE_NEUTRAL)	// ‘®«–î‚È‚ç‘®«‚ğ–î‚Ì‘®«‚É•ÏX
				s_ele = src_sd->arrow_ele;
			break;
		case SC_FATALMENACE:	// ƒtƒFƒCƒ^ƒ‹ƒƒiƒX
			calc_flag.hitrate -= 5 + (6 - skill_lv) * 5;
			break;
		case LG_BANISHINGPOINT:		// ƒoƒjƒVƒ“ƒOƒ|ƒCƒ“ƒg
			calc_flag.hitrate = calc_flag.hitrate*(100+3*skill_lv)/100;
			break;
		case LG_HESPERUSLIT:	// ƒwƒXƒyƒ‹ƒXƒŠƒbƒg
			if(sc) {
				if(sc->data[SC_BANDING].timer != -1 && sc->data[SC_BANDING].val2 > 0) {
					wd.div_ = sc->data[SC_BANDING].val2;
				}
				if(sc->data[SC_INSPIRATION].timer != -1) {
					wd.div_ += 2;
				}
			}
			if(wd.div_ == 5)
				s_ele = ELE_HOLY;
			break;
		case SR_GATEOFHELL:	// —…™‹”j™€Œ‚
			if(skill_lv >= 5)
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
			break;
		case MC_CARTREVOLUTION:		// ƒJ[ƒgƒŒƒ{ƒŠƒ…[ƒVƒ‡ƒ“
#ifndef PRE_RENEWAL
			calc_flag.hitrate = 1000000;
#endif
		case GN_CART_TORNADO:		// ƒJ[ƒgƒgƒ‹ƒl[ƒh
			if(src_sd && (skill = pc_checkskill(src_sd,GN_REMODELING_CART)) > 0)
				calc_flag.hitrate = calc_flag.hitrate+skill*4;
			break;
		}
	}

	// ƒTƒNƒŠƒtƒ@ƒCƒX
	if(sc && sc->data[SC_SACRIFICE].timer != -1 && !skill_num && t_class != MOBID_EMPERIUM) {
		calc_flag.hitrate = 1000000;
		s_ele = s_ele_ = ELE_NEUTRAL;
	}
	// ‘¾—z‚ÆŒ‚Æ¯‚Ì—Z‡
	if(sc && sc->data[SC_FUSION].timer != -1) {
		calc_flag.hitrate = 1000000;
	}
	// ƒXƒyƒ‹ƒtƒBƒXƒg
	if(sc && sc->data[SC_SPELLFIST].timer != -1 && !skill_num && t_class != MOBID_EMPERIUM) {
		calc_flag.hitrate = 1000000;
	}
	// ƒJ[ƒhŒø‰Ê‚É‚æ‚é•K’†ƒ{[ƒiƒX
	if(src_sd && src_sd->perfect_hit > 0) {
		if(atn_rand()%100 < src_sd->perfect_hit)
			calc_flag.hitrate = 1000000;
	}
	// ‘ÎÛ‚ªó‘ÔˆÙí’†‚Ìê‡‚Ì•K’†ƒ{[ƒiƒX
	if(calc_flag.hitrate < 1000000 && t_sc) {
		if( t_sc->data[SC_SLEEP].timer != -1 ||
		    t_sc->data[SC_STUN].timer != -1 ||
		    t_sc->data[SC_FREEZE].timer != -1 ||
		    (t_sc->data[SC_STONE].timer != -1 && t_sc->data[SC_STONE].val2 == 0) ||
		    t_sc->data[SC_DEEP_SLEEP].timer != -1 ) {
			calc_flag.hitrate = 1000000;
		}
	}
	if(calc_flag.hitrate < battle_config.min_hitrate)
		calc_flag.hitrate = battle_config.min_hitrate;

	/* ‚WD‰ñ”ğ”»’è */
	if(wd.type == 0 && atn_rand()%100 >= calc_flag.hitrate) {
		wd.dmg_lv = ATK_FLEE;
	}
	else if(wd.type == 0 && t_sc && t_sc->data[SC_UTSUSEMI].timer != -1) {	// ‹óä
		wd.dmg_lv = ATK_FLEE;
		clif_misceffect2(target,463);
		if(--t_sc->data[SC_UTSUSEMI].val3 == 0)
			status_change_end(target,SC_UTSUSEMI,-1);
		if(t_sc->data[SC_ANKLE].timer == -1) {
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(NJ_UTSUSEMI,t_sc->data[SC_UTSUSEMI].val1);
			if(target_sd) {
				dir = target_sd->dir;
				head_dir = target_sd->head_dir;
			}
			unit_stop_walking(target,1);
			skill_blown(src,target,count|SAB_NODAMAGE|SAB_NOPATHSTOP);
			if(target_sd)
				pc_setdir(target_sd, dir, head_dir);
			if(t_sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(target,SC_CLOSECONFINE,-1);
		}
	}
	else if(wd.type == 0 && t_sc && t_sc->data[SC_BUNSINJYUTSU].timer != -1) {	// ‰e•ªg
		wd.dmg_lv = ATK_FLEE;
		if(--t_sc->data[SC_BUNSINJYUTSU].val3 == 0)
			status_change_end(target,SC_BUNSINJYUTSU,-1);
	}
	else if(target_sd && t_sc && t_sc->data[SC_DODGE].timer != -1 && (wd.flag&BF_LONG || t_sc->data[SC_SPURT].timer != -1) && atn_rand()%100 < 20) {	// —–@
		int slv = pc_checkskill(target_sd,TK_DODGE);
		wd.dmg_lv = ATK_FLEE;
		clif_skill_nodamage(&target_sd->bl,&target_sd->bl,TK_DODGE,slv,1);
		status_change_start(&target_sd->bl,SC_DODGE_DELAY,slv,src->id,0,0,skill_get_time(TK_DODGE,slv),0);
	}
	else if(t_sc && (t_sc->data[SC_FOGWALL].timer != -1 || t_sc->data[SC_FOGWALLPENALTY].timer != -1) && wd.flag&BF_LONG && !skill_num && atn_rand()%100 < 75) {	// ƒEƒH[ƒ‹ƒIƒuƒtƒHƒO@‰“‹——£’ÊíUŒ‚‚Í75%‚ÌŠm—¦‚Åƒ~ƒX
		wd.dmg_lv = ATK_FLEE;	// ’Êí‰ñ”ğ
	}

	else {
		int damage_ot = 0, damage_ot2 = 0;
#ifdef PRE_RENEWAL
		int tk_power_damage = 0, tk_power_damage2 = 0;
#endif

		// ‰ñ”ğ‚Å‚«‚È‚©‚Á‚½‚Æ‚«‚Ì‚İstep9`18‚Ìƒ_ƒ[ƒWŒvZ‚ğs‚¤
		wd.dmg_lv = ATK_DEF;

		/* ‚XDŠî–{ƒ_ƒ[ƒW‚ÌZo */
		wd.damage = battle_calc_base_damage(src, target, skill_num, wd.type, 0);
#ifdef PRE_RENEWAL
		if(calc_flag.lh)
			wd.damage2 = battle_calc_base_damage(src, target, skill_num, wd.type, 1);
#else
		if(calc_flag.lh)
			wd.damage2 = battle_calc_base_damage(src, target, skill_num, 0, 1);
#endif

#ifdef PRE_RENEWAL
		if(wd.type == 0) {	// ƒNƒŠƒeƒBƒJƒ‹‚Å‚È‚¢‚Æ‚«–î‚Ìƒ_ƒ[ƒW‚ğ‰ÁZ
			if(src_sd && src_sd->state.arrow_atk && src_sd->arrow_atk > 0)
				wd.damage += atn_rand()%(src_sd->arrow_atk+1);
		}
#else
		// iREjƒ}ƒOƒiƒ€ƒuƒŒƒCƒNó‘Ô
		if(sc && sc->data[SC_MAGNUM].timer != -1) {
			int rate = 0;
			if(sc->data[SC_MAGNUM].val2 == ELE_FIRE && skill_num != GN_CART_TORNADO) {
				rate = 20;
			} else if(sc->data[SC_MAGNUM].val2 == ELE_POISON) {
				switch(skill_num) {
				case 0:
				case SM_BASH:
				case SM_MAGNUM:
				case MS_MAGNUM:
				case TF_POISON:
				case AS_SONICBLOW:
				case AS_GRIMTOOTH:
				case ASC_BREAKER:
				case GC_CROSSIMPACT:
				case GC_DARKILLUSION:
				case GC_VENOMPRESSURE:
				case GC_COUNTERSLASH:
				case GC_PHANTOMMENACE:
				case GC_ROLLINGCUTTER:
				case GC_CROSSRIPPERSLASHER:
					rate = 25;
					break;
				}
			}
			if(rate > 0) {
				int bonus_damage;
				bonus_damage = battle_attr_fix(wd.damage, sc->data[SC_MAGNUM].val2, status_get_element(target));
				if(bonus_damage > 0)
					wd.damage += bonus_damage * rate / 100;
				if(calc_flag.lh) {
					bonus_damage = battle_attr_fix(wd.damage2, sc->data[SC_MAGNUM].val2, status_get_element(target));
					if(bonus_damage > 0)
						wd.damage2 += bonus_damage * rate / 100;
				}
			}
		}

		// iREj“y•„F„‰ò
		if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
			wd.damage += (wd.damage * src_sd->elementball.num * 10) / 100;
			if(calc_flag.lh)
				wd.damage2 += (wd.damage2 * src_sd->elementball.num * 10) / 100;
		}

		/* iREj–hŒä–³‹”»’è‚¨‚æ‚ÑŒø‰Êƒ_ƒ[ƒWŒvZ */
		switch (skill_num) {
		case MC_CARTREVOLUTION:
		case KN_AUTOCOUNTER:
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
		case MO_EXTREMITYFIST:
		case AM_DEMONSTRATION:
		case AM_ACIDTERROR:
		case CR_ACIDDEMONSTRATION:
		case ASC_BREAKER:
		case NJ_SYURIKEN:
		case NJ_KUNAI:
		case NJ_ZENYNAGE:
		case LG_RAYOFGENESIS:
		case GN_FIRE_EXPANSION_ACID:
		case KO_MUCHANAGE:
			break;
		case MO_INVESTIGATE:
			wd.damage += t_def1 / 2;
			break;
		default:
			if( skill_num == WS_CARTTERMINATION && !battle_config.def_ratio_atk_to_carttermination )
				break;
			if( skill_num == PA_SHIELDCHAIN && !battle_config.def_ratio_atk_to_shieldchain )
				break;
			if(src_sd && t_def1 < 1000000)
			{
				// bIgnoreDefŒn”»’è
				ignored_rate  = ignored_rate  - src_sd->ignore_def_ele[t_ele]  - src_sd->ignore_def_race[t_race]  - src_sd->ignore_def_enemy[t_enemy];
				ignored_rate_ = ignored_rate_ - src_sd->ignore_def_ele_[t_ele] - src_sd->ignore_def_race_[t_race] - src_sd->ignore_def_enemy_[t_enemy];
				if(target_sd) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_PLAYER];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_PLAYER];
				}
				if(t_mode & MD_BOSS) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_BOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_BOSS];
				} else {
					ignored_rate  -= src_sd->ignore_def_race[RCT_NONBOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_NONBOSS];
				}

				if(battle_config.left_cardfix_to_right) {
					// ¶èƒJ[ƒh•â³İ’è‚ ‚è
					ignored_rate -= 100 - ignored_rate_;
					ignored_rate_ = ignored_rate;
				}

				// bDefRatioATKŒn”»’è
				if(skill_num != AM_ACIDTERROR && ignored_rate > 0) {
					int def_ratio = 0;
					int mask = (1<<t_race) | ( (t_mode&MD_BOSS)? (1<<RCT_BOSS): (1<<RCT_NONBOSS))  | ( (target_sd)? (1<<RCT_PLAYER): 0 );
					int def_fix = t_def1 * ignored_rate / 100;

					if(src_sd->def_ratio_atk_ele & (1<<t_ele) || src_sd->def_ratio_atk_race & mask || src_sd->def_ratio_atk_enemy & (1<<t_enemy) ||
					   src_sd->def_ratio_atk_ele_ & (1<<t_ele) || src_sd->def_ratio_atk_race_ & mask || src_sd->def_ratio_atk_enemy_ & (1<<t_enemy)
					)
						def_ratio = 1;

					// bIgnoreDefŒn•ª‚ğ‰Á–¡‚µ‚ÄŒvZ
					if(!calc_flag.idef && def_fix > 0 && def_ratio) {
						if(!calc_flag.idef_) {
							wd.damage  += def_fix / 2;
							wd.damage2 += def_fix / 2;
							calc_flag.idef  = 1;
							calc_flag.idef_ = 1;
						}
					}
					if(calc_flag.lh) {
						if(!calc_flag.idef_ && def_fix > 0 && def_ratio) {
							if(!calc_flag.idef) {
								wd.damage  += def_fix / 2;
								wd.damage2 += def_fix / 2;
								calc_flag.idef  = 1;
								calc_flag.idef_ = 1;
							}
						}
					}
				}
			}
			break;
		}

		// iREj•ŠíAtk‚Ì•â³
		if(src_sd) {
			int trans_bonus = 0;

			wd.damage += src_sd->plus_atk;
			if(calc_flag.lh)
				wd.damage2 += src_sd->plus_atk;
			if(src_sd->state.arrow_atk) {
				wd.damage += src_sd->arrow_atk;
				if(calc_flag.lh)
					wd.damage2 += src_sd->arrow_atk;
			}

			if(src_sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && (src_sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1276 || src_sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1884))
				trans_bonus += 25;
			if(src_sd->weapontype1 < WT_MAX && src_sd->weapontype2 < WT_MAX) {
				if(src_sd->atk_rate != 100 || src_sd->weapon_atk_rate[src_sd->weapontype1] != 0 || src_sd->weapon_atk_rate[src_sd->weapontype2] != 0 || trans_bonus) {
					wd.damage = (wd.damage * (src_sd->atk_rate + src_sd->weapon_atk_rate[src_sd->weapontype1] + trans_bonus)) / 100;
					if(calc_flag.lh)
						wd.damage2 = (wd.damage2 * (src_sd->atk_rate + src_sd->weapon_atk_rate[src_sd->weapontype2] + trans_bonus)) / 100;
				}
			}
		}
		if(skill_num == TF_POISON)
			wd.damage += 15*skill_lv;
#endif

#ifdef PRE_RENEWAL
		/* 10Dƒtƒ@ƒCƒeƒBƒ“ƒOŒvZ */
		if(src_sd && (skill = pc_checkskill(src_sd,TK_POWER)) > 0 && src_sd->status.party_id > 0)
		{
			int member_num = party_check_same_map_member_count(src_sd);
			if(member_num > 0)
			{
				tk_power_damage = wd.damage*member_num * skill/50;
				if(calc_flag.lh)
					tk_power_damage2 = wd.damage2*member_num * skill/50;
			}
		}
#endif

		/* 11DƒI[ƒo[ƒgƒ‰ƒXƒgŒn‚ÌƒXƒLƒ‹”{—¦ŒvZ‘O‚ÌUŒ‚—ÍŠm•Û */
		damage_ot += wd.damage;
		if(calc_flag.lh)
			damage_ot2 += wd.damage2;

#ifndef PRE_RENEWAL
		/* iREjƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒW’Ç‰Áˆ— */
		if( src_sd && wd.damage > 0 && calc_flag.rh ) {
			if(!src_sd->state.arrow_atk) {	// ‹|–îˆÈŠO
				if(!battle_config.left_cardfix_to_right) {	// ¶èƒJ[ƒh•â³İ’è–³‚µ
					if(target_sd)
						wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->addrace[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³
					else
						wd.damage = wd.damage*(100+src_sd->addsize[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³
					wd.damage = wd.damage*(100+src_sd->addele[t_ele])/100;	// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³
					wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³
					wd.damage = wd.damage*(100+src_sd->addgroup[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³
				} else {
					if(target_sd)
						wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race]+src_sd->addrace[RCT_PLAYER]+src_sd->addrace_[RCT_PLAYER])/100;		// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					else
						wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;		// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					wd.damage = wd.damage*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;		// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					wd.damage = wd.damage*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					wd.damage = wd.damage*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			} else { // ‹|–î
				if(target_sd)
					wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				else
					wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race]+src_sd->addrace[RCT_PLAYER]+src_sd->arrow_addrace[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				wd.damage = wd.damage*(100+src_sd->addsize[t_size]+src_sd->arrow_addsize[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				wd.damage = wd.damage*(100+src_sd->addele[t_ele]+src_sd->arrow_addele[t_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy]+src_sd->arrow_addenemy[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				wd.damage = wd.damage*(100+src_sd->addgroup[t_group]+src_sd->arrow_addgroup[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
			}
			if(t_mode & MD_BOSS) {	// ƒ{ƒX
				if(!src_sd->state.arrow_atk) {	// ‹|–îUŒ‚ˆÈŠO‚È‚ç
					if(!battle_config.left_cardfix_to_right) {
						// ¶èƒJ[ƒh•â³İ’è–³‚µ
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS])/100;					// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW
					} else {
						// ¶èƒJ[ƒh•â³İ’è‚ ‚è
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;	// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					}
				} else {	// ‹|–îUŒ‚
					wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS]+src_sd->arrow_addrace[RCT_BOSS])/100;		// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			} else {		// ƒ{ƒX‚¶‚á‚È‚¢
				if(!src_sd->state.arrow_atk) {	// ‹|–îUŒ‚ˆÈŠO
					if(!battle_config.left_cardfix_to_right) {
						// ¶èƒJ[ƒh•â³İ’è–³‚µ
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS])/100;				// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW
					} else {
						// ¶èƒJ[ƒh•â³İ’è‚ ‚è
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					}
				} else {
					wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->arrow_addrace[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			}
			// “Á’èClass—p•â³ˆ—(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
			for(i=0; i<src_sd->add_damage_class_count; i++) {
				if(src_sd->add_damage_classid[i] == t_class) {
					wd.damage = wd.damage*(100+src_sd->add_damage_classrate[i])/100;
					break;
				}
			}
		}

		/* iREjƒJ[ƒh‚É‚æ‚é¶èƒ_ƒ[ƒW’Ç‰Áˆ— */
		if( src_sd && wd.damage2 > 0 && calc_flag.lh ) {
//			if(!battle_config.left_cardfix_to_right) {	// ¶èƒJ[ƒh•â³İ’è–³‚µ
				if(target_sd)
					wd.damage2 = wd.damage2*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race]+src_sd->addrace[RCT_PLAYER]+src_sd->addrace_[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				else
					wd.damage2 = wd.damage2*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				wd.damage2 = wd.damage2*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				wd.damage2 = wd.damage2*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;	// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				wd.damage2 = wd.damage2*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				wd.damage2 = wd.damage2*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³¶è
				if(t_mode & MD_BOSS)	// ƒ{ƒX
					wd.damage2 = wd.damage2*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;		// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW¶è
				else
					wd.damage2 = wd.damage2*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW¶è
//			}
			// “Á’èClass—p•â³ˆ—¶è(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
			for(i=0; i<src_sd->add_damage_class_count_; i++) {
				if(src_sd->add_damage_classid_[i] == t_class) {
					wd.damage2 = wd.damage2*(100+src_sd->add_damage_classrate_[i])/100;
					break;
				}
			}
		}

		/* iREjƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒWŒ¸Šˆ— */
		if( target_sd && (wd.damage > 0 || wd.damage2 > 0 || damage_sbr > 0) && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != NPC_CRITICALSLASH) {	// ‘ÎÛ‚ªPC‚Ìê‡
			int s_enemy = status_get_enemy_type(src);
			int s_size  = status_get_size(src);
			int s_group = status_get_group(src);
			int ele_type= status_get_elem_type(src);
			cardfix = 100;
			if (s_ele == ELE_NONE)
				cardfix = cardfix*(100-target_sd->subele[ELE_NEUTRAL])/100;	// ‘®«–³‚µ‚Ì‘Ï«‚Í–³‘®«
			else
				cardfix = cardfix*(100-target_sd->subele[s_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			if (ele_type == ELE_NONE)
				cardfix = cardfix*(100-target_sd->def_eleenemy[ELE_NEUTRAL])/100;	// ‘®«–³‚µ‚Ì‘Ï«‚Í–³‘®«
			else
				cardfix = cardfix*(100-target_sd->def_eleenemy[ele_type])/100;		// “G‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-target_sd->subenemy[s_enemy])/100;		// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-target_sd->subsize[s_size])/100;			// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-target_sd->subgroup[s_group])/100;		// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«

			if(status_get_mode(src) & MD_BOSS)
				cardfix = cardfix*(100-target_sd->subrace[RCT_BOSS])/100;	// ƒ{ƒX‚©‚ç‚ÌUŒ‚‚Íƒ_ƒ[ƒWŒ¸­
			else
				cardfix = cardfix*(100-target_sd->subrace[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠO‚©‚ç‚ÌUŒ‚‚Íƒ_ƒ[ƒWŒ¸­

			// “Á’èClass—p•â³ˆ—¶è(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
			for(i=0; i<target_sd->add_def_class_count; i++) {
				if(target_sd->add_def_classid[i] == status_get_class(src)) {
					cardfix = cardfix*(100-target_sd->add_def_classrate[i])/100;
					break;
				}
			}
			if(wd.flag&BF_LONG && !(src_md && (skill_num == AC_SHOWER || skill_num == SN_SHARPSHOOTING)) )
				cardfix = cardfix*(100-target_sd->long_attack_def_rate)/100;	// ‰“‹——£UŒ‚‚Íƒ_ƒ[ƒWŒ¸­(ƒzƒ‹ƒ“C‚Æ‚©)
			if(wd.flag&BF_SHORT)
				cardfix = cardfix*(100-target_sd->near_attack_def_rate)/100;	// ‹ß‹——£UŒ‚‚Íƒ_ƒ[ƒWŒ¸­(ŠY“––³‚µH)
			DMG_FIX( cardfix, 100 );	// ƒJ[ƒh•â³‚É‚æ‚éƒ_ƒ[ƒWŒ¸­

			damage_sbr = damage_sbr * cardfix / 100;	// ƒJ[ƒh•â³‚É‚æ‚éƒ\ƒEƒ‹ƒuƒŒƒCƒJ[‚Ì–‚–@ƒ_ƒ[ƒWŒ¸­
		}

		// ƒGƒEƒJƒŠƒXƒeƒBƒJ
		if(target_sd && (skill = pc_checkskill(target_sd,AB_EUCHARISTICA)) > 0) {
			if(s_ele == ELE_UNDEAD || s_ele == ELE_DARK)
				DMG_FIX( 100-skill, 100 );
		}

		// ƒXƒpƒCƒ_[ƒEƒFƒu
		if(t_sc && t_sc->data[SC_SPIDERWEB].timer != -1 && s_ele == ELE_FIRE) {
			wd.damage <<= 1;
			if(calc_flag.lh)
				wd.damage2 <<= 1;
			status_change_end(target, SC_SPIDERWEB, -1);
		}

		/* iREj‘®«‚Ì“K—p */
		if(skill_num != MO_EXTREMITYFIST && skill_num != NJ_ISSEN) {
			wd.damage = battle_attr_fix(wd.damage, s_ele, status_get_element(target));
			if(calc_flag.lh)
				wd.damage2 = battle_attr_fix(wd.damage2, s_ele_, status_get_element(target));
		}

		/* iREj‘®«•â³ */
		if( (sc || t_sc) && (wd.damage > 0 || wd.damage2 > 0) && skill_num != MO_EXTREMITYFIST && skill_num != NJ_ISSEN) {
			cardfix = 100;
			if(sc) {
				// ƒ{ƒ‹ƒP[ƒm
				if(sc->data[SC_VOLCANO].timer != -1 && s_ele == ELE_FIRE)
					cardfix += sc->data[SC_VOLCANO].val4;
				// ƒoƒCƒIƒŒƒ“ƒgƒQƒCƒ‹
				if(sc->data[SC_VIOLENTGALE].timer != -1 && s_ele == ELE_WIND)
					cardfix += sc->data[SC_VIOLENTGALE].val4;
				// ƒfƒŠƒ…[ƒW
				if(sc->data[SC_DELUGE].timer != -1 && s_ele == ELE_FIRE)
					cardfix += sc->data[SC_DELUGE].val4;
			}
			if(t_sc) {
				// ƒJƒCƒg
				if(t_sc->data[SC_KAITE].timer != -1)
					cardfix += 300;
				// ƒxƒiƒ€ƒCƒ“ƒvƒŒƒX
				if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && s_ele == ELE_POISON)
					cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
				// ƒIƒ‰ƒeƒBƒI
				if(t_sc->data[SC_ORATIO].timer != -1 && s_ele == ELE_HOLY)
					cardfix += t_sc->data[SC_ORATIO].val2;
			}
			DMG_FIX( cardfix, 100 );
		}

		// ƒGƒ“ƒ`ƒƒƒ“ƒgƒfƒbƒhƒŠ[ƒ|ƒCƒYƒ“
		if(sc && sc->data[SC_EDP].timer != -1) {
			int edp_rate;

			switch(skill_num) {
			case 0:
			case SM_BASH:
			case SM_MAGNUM:
			case MS_MAGNUM:
			case TF_POISON:
			case AS_SONICBLOW:
			case ASC_BREAKER:
			case GC_CROSSIMPACT:
			case GC_DARKILLUSION:
			case GC_VENOMPRESSURE:
			case GC_COUNTERSLASH:
			case GC_PHANTOMMENACE:
			case GC_ROLLINGCUTTER:
			case GC_CROSSRIPPERSLASHER:
				if(map[src->m].flag.pk && target->type == BL_PC) {
					edp_rate = (150 + sc->data[SC_EDP].val1 * 50) * battle_config.pk_edp_down_rate / 100;
				} else if(map[src->m].flag.gvg) {
					edp_rate = (150 + sc->data[SC_EDP].val1 * 50) * battle_config.gvg_edp_down_rate / 100;
				} else if(map[src->m].flag.pvp) {
					edp_rate = (150 + sc->data[SC_EDP].val1 * 50) * battle_config.pvp_edp_down_rate / 100;
				} else {
					edp_rate = 150 + sc->data[SC_EDP].val1 * 50;
				}
				wd.damage = wd.damage * edp_rate / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * edp_rate / 100;
				break;
			}
		}

		// iREjƒXƒe[ƒ^ƒXAtk‚ğ‰ÁZ
		if(src_sd || (!src_sd && battle_config.enemy_str)) {
			int s_ele__ = ELE_NEUTRAL;		// Šî–{–³‘®«
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {	// ’g‚©‚¢•—‚ÍƒXƒe[ƒ^ƒXAtk‚É‚à‚©‚©‚é
				s_ele__ = sc->data[SC_SEVENWIND].val3;
			}
			wd.damage += battle_attr_fix(status_get_baseatk(src), s_ele__, status_get_element(target));
			/* iREj¶èƒ_ƒ[ƒW‚ÌŒvZˆ— */
			if(calc_flag.lh) {
				wd.damage2 = wd.damage2 * 75 / 100;
				wd.damage2 += battle_attr_fix(status_get_baseatk(src)/2, s_ele__, status_get_element(target));
			}
		}

		if(src_sd) {
			// ¯‚Ì‚©‚¯‚çA‹C‹…‚Ì“K—p
			int hit_bonus  = (src_sd->spiritball.old>0? src_sd->spiritball.old * 3: src_sd->spiritball.num * 3) + src_sd->coin.num * 3 + src_sd->bonus_damage;
			int hit_damage = hit_bonus + src_sd->star + src_sd->ranker_weapon_bonus;

			if(skill_num == NJ_KUNAI || skill_num == KO_HAPPOKUNAI) {	// ‹ê–³“Š‚°A”ª•û‹ê–³
				if(src_sd->arrow_atk) {
					hit_damage += src_sd->arrow_atk;
				}
				wd.damage += hit_damage;
			} else if(skill_num != MO_INVESTIGATE && skill_num != MO_EXTREMITYFIST && skill_num != GS_MAGICALBULLET && skill_num != GS_PIERCINGSHOT && skill_num != NC_ARMSCANNON && skill_num != SR_RAMPAGEBLASTER) {
				wd.damage += hit_damage;
				if(calc_flag.lh)
					wd.damage2 += hit_bonus + src_sd->star_ + src_sd->ranker_weapon_bonus_;
			}

			switch(skill_num) {
			case MC_CARTREVOLUTION:
			case MO_INVESTIGATE:
			case MO_EXTREMITYFIST:
			case CR_GRANDCROSS:
			case NPC_GRANDDARKNESS:
			case AM_DEMONSTRATION:
			case AM_ACIDTERROR:
			case PA_SHIELDCHAIN:
			case CR_ACIDDEMONSTRATION:
			case ASC_BREAKER:
			case NJ_ZENYNAGE:
			case RA_CLUSTERBOMB:
			case RA_FIRINGTRAP:
			case RA_ICEBOUNDTRAP:
			case SO_VARETYR_SPEAR:
			case LG_RAYOFGENESIS:
			case GN_FIRE_EXPANSION_ACID:
			case KO_MUCHANAGE:
				break;
			case NC_ARMSCANNON:
				if(pc_isgear(src_sd) && (skill = pc_checkskill(src_sd,NC_MADOLICENCE)) > 0) {	// –‚“±ƒMƒAƒ‰ƒCƒZƒ“ƒX
					wd.damage += 15 * skill;
				}
				break;
			case RA_WUGSTRIKE:
			case RA_WUGBITE:
				if((skill = pc_checkskill(src_sd,RA_TOOTHOFWUG)) > 0) {	// ƒgƒD[ƒXƒIƒuƒEƒH[ƒO‚É‚æ‚éƒ_ƒ[ƒW‘‰Á
					wd.damage += 6 * skill;
				}
			default:
				if(skill_lv < 0)
					break;
				wd.damage = battle_addmastery(src_sd,target,wd.damage,0);
				if(calc_flag.lh)
					wd.damage2 = battle_addmastery(src_sd,target,wd.damage2,1);
				break;
			}
		}

		/* iREjC—ûŒnBUFFˆ— */
		if(sc && skill_num != MO_EXTREMITYFIST) {
			// ƒCƒ€ƒ|ƒVƒeƒBƒIƒ}ƒkƒX
			if(sc->data[SC_IMPOSITIO].timer != -1) {
				wd.damage += sc->data[SC_IMPOSITIO].val1*5;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_IMPOSITIO].val1*5;
			}
			// í‘¾ŒÛ‚Ì‹¿‚«
			if(sc->data[SC_DRUMBATTLE].timer != -1) {
				wd.damage += sc->data[SC_DRUMBATTLE].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_DRUMBATTLE].val2;
			}
			// ƒj[ƒxƒ‹ƒ“ƒO‚Ìw—Ö
			if(sc->data[SC_NIBELUNGEN].timer != -1) {
				wd.damage += sc->data[SC_NIBELUNGEN].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_NIBELUNGEN].val2;
			}
			// ƒJƒ‚ƒtƒ‰[ƒWƒ…
			if(sc->data[SC_CAMOUFLAGE].timer != -1 && sc->data[SC_CAMOUFLAGE].val3 >= 0) {
				wd.damage += 300 - (10 - sc->data[SC_CAMOUFLAGE].val3) * 30;
				if(calc_flag.lh)
					wd.damage2 += 300 - (10 - sc->data[SC_CAMOUFLAGE].val3) * 30;
			}
			// ƒJ[ƒgƒu[ƒXƒg
			if(sc->data[SC_GN_CARTBOOST].timer != -1) {
				wd.damage += sc->data[SC_GN_CARTBOOST].val1 * 10;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_GN_CARTBOOST].val1 * 10;
			}
		}

		/* iREjƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒWŒ¸Šˆ—‚Q */
		if( target_sd && (wd.damage > 0 || wd.damage2 > 0) && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != NPC_CRITICALSLASH) {	// ‘ÎÛ‚ªPC‚Ìê‡
			int s_race  = status_get_race(src);
			cardfix = 100;
			if(src_sd)
				cardfix = cardfix*(100-target_sd->subrace[s_race]-target_sd->subrace[RCT_PLAYER])/100;			// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			else
				cardfix = cardfix*(100-target_sd->subrace[s_race])/100;			// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			if(!src_sd && pc_isdoram(target_sd) && s_race == RCT_HUMAN)
				cardfix = cardfix*110/100;
			else if(src_sd && pc_isdoram(target_sd))
				cardfix = cardfix*110/100;
			DMG_FIX( cardfix, 100 );	// ƒJ[ƒh•â³‚É‚æ‚éƒ_ƒ[ƒWŒ¸­
		}

		// ƒGƒEƒJƒŠƒXƒeƒBƒJ
		if(src_sd && (skill = pc_checkskill(src_sd,AB_EUCHARISTICA)) > 0) {
			if(t_ele == ELE_UNDEAD || t_ele == ELE_DARK) {
				wd.damage += wd.damage * skill / 100;
				if(calc_flag.lh)
					wd.damage2 += wd.damage2 * skill / 100;
			}
		}

		// iREjƒNƒŠƒeƒBƒJƒ‹ƒ_ƒ[ƒW‘‰Á
		if(wd.type == 0x0a || skill_num == LG_PINPOINTATTACK ||
			((calc_flag.idef || calc_flag.idef_) && (skill_num == SN_SHARPSHOOTING || skill_num == NJ_KIRIKAGE || skill_num == MA_SHARPSHOOTING))
		) {
			if(src_sd) {
				int trans_bonus = 100;

				// ƒNƒŠƒeƒBƒJƒ‹ƒ_ƒ[ƒW‘‰Á
				if(src_sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && src_sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1002)
					trans_bonus += 5;
				wd.damage = wd.damage * (src_sd->critical_damage + trans_bonus) / 100;
			}
		}
#endif

		/* ƒXƒLƒ‹”{—¦ŒvZ‚É‰ÁZ */
		if(sc) {
#ifndef PRE_RENEWAL
			// ƒI[ƒo[ƒgƒ‰ƒXƒg
			if(sc->data[SC_OVERTHRUST].timer != -1)
				add_rate += sc->data[SC_OVERTHRUST].val3;
			// ƒI[ƒo[ƒgƒ‰ƒXƒgƒ}ƒbƒNƒX
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1)
				add_rate += 20*sc->data[SC_OVERTHRUSTMAX].val1;
			// ƒuƒ‰ƒbƒfƒBƒ‰ƒXƒg
			if(sc->data[SC__BLOODYLUST].timer != -1)
				add_rate += 32;
			// ƒvƒƒ{ƒbƒN
			else if(sc->data[SC_PROVOKE].timer != -1)
				add_rate += 2 + 3 * sc->data[SC_PROVOKE].val1;
			// ƒgƒDƒ‹[ƒTƒCƒg
			if(sc->data[SC_TRUESIGHT].timer != -1)
				add_rate += 2*sc->data[SC_TRUESIGHT].val1;
			// ƒRƒ“ƒZƒ“ƒgƒŒ[ƒVƒ‡ƒ“
			if(sc->data[SC_CONCENTRATION].timer != -1)
				add_rate += 5*sc->data[SC_CONCENTRATION].val1;
			// ƒSƒXƒyƒ‹‚ÌAtk2”{
			if(sc->data[SC_INCATK2].timer != -1)
				add_rate += sc->data[SC_INCATK2].val1;
			// ƒo[ƒT[ƒN
			if(sc->data[SC_BERSERK].timer != -1)
				add_rate += 200;
			// ô‚¢
			if(sc->data[SC_CURSE].timer != -1)
				add_rate -= 25;
#endif
		}
#ifndef PRE_RENEWAL
		switch( skill_num ) {
		case NJ_SYURIKEN:	// è— Œ•“Š‚°
			if(src_sd) {
				skill = pc_checkskill(src_sd,NJ_TOBIDOUGU);
				DMG_ADD( skill * 3 );
				if(src_sd->arrow_atk) {
					DMG_ADD( src_sd->arrow_atk );
				}
			}
			DMG_ADD( skill_lv*4 );
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case NJ_KUNAI:		// ‹ê–³“Š‚°
			DMG_FIX( 300, 100 );
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case NJ_ISSEN:		// ˆê‘M
			{
				int maxhp = status_get_max_hp(src) / 100;
				int hp = status_get_hp(src);
				if(maxhp < hp) {
					wd.damage = wd.damage * skill_lv + hp;
					unit_heal(src,-(hp-maxhp),0);
					if(sc) {
						if(sc->data[SC_BUNSINJYUTSU].timer != -1 && sc->data[SC_BUNSINJYUTSU].val3 > 0) {
							wd.div_ = 2 + sc->data[SC_BUNSINJYUTSU].val3;
							wd.damage = wd.damage * (120+20*sc->data[SC_BUNSINJYUTSU].val3) / 100;
							status_change_end(src,SC_BUNSINJYUTSU,-1);
						}
						if(sc->data[SC_NEN].timer != -1)
							status_change_end(src,SC_NEN,-1);
					}
				}
				wd.damage = wd.damage - (t_def1 + t_def2);
			}
			break;
		case GS_MAGICALBULLET:	// ƒ}ƒWƒJƒ‹ƒoƒŒƒbƒg
			{
				static struct Damage mgd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

				mgd = battle_calc_attack(BF_MAGIC,src,target,skill_num,skill_lv,wd.flag);
				wd.damage += mgd.damage;
				wd.damage = wd.damage - (t_def1 + t_def2);
			}
			break;
		case LK_SPIRALPIERCE:	// ƒXƒpƒCƒ‰ƒ‹ƒsƒA[ƒX
		case ML_SPIRALPIERCE:
			{
				int weight = 0;
				if(src_sd && src_sd->equip_index[EQUIP_INDEX_RARM] >= 0) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid)) {
						weight = src_sd->inventory_data[idx]->weight/10;
					}
				}
				DMG_FIX( 100+50*skill_lv, 100 );
				DMG_ADD( weight*(skill_lv*(skill_lv+2)*25)/100 );
				if(add_rate > 0)
					DMG_ADD( weight/2*skill_lv*add_rate/100 );
			}
			break;
		case PA_SHIELDCHAIN:	// ƒV[ƒ‹ƒhƒ`ƒFƒCƒ“
			if(src_sd) {
				int idx  = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_ADD( src_sd->inventory_data[idx]->weight/10 );
					DMG_FIX( 100+30*skill_lv, 100 );
					DMG_ADD( src_sd->status.inventory[idx].refine*(375+skill_lv*125)/100 );
				} else {
					DMG_FIX( 100+30*skill_lv, 100 );
				}
			} else {
				DMG_FIX( 100+30*skill_lv, 100 );
			}
			break;
		case AM_DEMONSTRATION:	// ƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case AM_ACIDTERROR:	// ƒAƒVƒbƒhƒeƒ‰[
			{
				static struct Damage mgd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				int rate = 100+skill_lv*((skill_num==AM_ACIDTERROR)? 100: 20);

				mgd = battle_calc_attack(BF_MAGIC,src,target,skill_num,skill_lv,wd.flag);
				wd.damage += mgd.damage;
				wd.damage = wd.damage * rate / 100;
				wd.damage = wd.damage - (t_def1 + t_def2 + status_get_mdef(target) + status_get_mdef2(target));
				if(skill_num == AM_DEMONSTRATION) {
					int def_elem = status_get_element(target);
					int def_type = def_elem%20;
					int def_lv   = def_elem/20;

					if(def_type >= 0 && def_type < ELE_MAX && def_lv > 0 && def_lv <= MAX_ELE_LEVEL) {
						int rate = attr_fix_table[def_lv-1][ELE_FIRE][def_type];
						wd.damage -= wd.damage * (100 - rate) / 100;
					}
				} else if(t_mode&MD_BOSS) {
					wd.damage = wd.damage / 2;
				}
			}
			break;
		case ASC_BREAKER:	// ƒ\ƒEƒ‹ƒuƒŒƒCƒJ[
			{
				static struct Damage sbr = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				int rate = 300+50*skill_lv;

				if(sc && sc->data[SC_EDP].timer != -1)
					rate >>= 1;
				sbr = battle_calc_attack(BF_MAGIC,src,target,skill_num,skill_lv,wd.flag);
				wd.damage = wd.damage * (rate+add_rate) / 100;
				wd.damage += sbr.damage * rate / 100;
				wd.damage = wd.damage - (t_def1 + t_def2 + status_get_mdef(target) + status_get_mdef2(target));
			}
			break;
		case CR_ACIDDEMONSTRATION:	// ƒAƒVƒbƒhƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case GN_FIRE_EXPANSION_ACID:	// ƒtƒ@ƒCƒA[ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“(‰–_)
			{
				static struct Damage ads = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				atn_bignumber dmg;
				ads = battle_calc_attack(BF_MAGIC,src,target,skill_num,skill_lv,wd.flag);
				wd.damage = wd.damage * (100+add_rate) / 100;
				wd.damage += ads.damage;
				dmg = (atn_bignumber)wd.damage * t_vit * 7 / 10;
				dmg = (dmg - ((t_def1 + t_def2)/2 + (status_get_mdef(target) + status_get_mdef2(target))/2))/10 * skill_lv;
				if(target->type != BL_MOB)
					dmg /= 2;
				DMG_SET( (int)dmg );
			}
			break;
		case NC_ARMSCANNON:	// ƒA[ƒ€ƒYƒLƒƒƒmƒ“
			if(src_sd && src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
			DMG_FIX( (200 + (500 - 100 * t_size) * skill_lv) * status_get_lv(src) / 150, 100 );
			break;
		}

		if( src_sd && wd.damage > 0 && calc_flag.rh ) {
			// iREjƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒŒƒ“ƒWUŒ‚‚Ìƒ_ƒ[ƒW‘•
			if(wd.flag&BF_SHORT) {
				wd.damage = wd.damage * (100+src_sd->short_weapon_damege_rate) / 100;
			}
			if(wd.flag&BF_LONG) {
				wd.damage = wd.damage * (100+src_sd->long_weapon_damege_rate) / 100;
			}
		}
#endif

		// ƒAƒ“ƒŠƒ~ƒbƒg
		if(sc && sc->data[SC_UNLIMIT].timer != -1 && wd.flag&BF_LONG && skill_num != HT_BLITZBEAT && skill_num != SN_FALCONASSAULT)
			wd.damage += wd.damage * sc->data[SC_UNLIMIT].val2 / 100;

		/* 12DƒXƒLƒ‹C³‚PiUŒ‚—Í”{‰ÁŒnj*/
		switch( skill_num ) {
		case SM_BASH:		// ƒoƒbƒVƒ…
		case MS_BASH:
			DMG_FIX( 100+30*skill_lv, 100 );
			break;
		case SM_MAGNUM:		// ƒ}ƒOƒiƒ€ƒuƒŒƒCƒN
		case MS_MAGNUM:
			if(src_md && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
				DMG_FIX( 1000, 100 );
			} else {
				if(!wflag) {	// “àü
					DMG_FIX( 100+20*skill_lv, 100 );
				} else {	// ŠOü
					DMG_FIX( 100+10*skill_lv, 100 );
				}
			}
			break;
		case MC_MAMMONITE:	// ƒƒ}[ƒiƒCƒg
			DMG_FIX( 100+50*skill_lv, 100 );
			break;
		case AC_DOUBLE:		// ƒ_ƒuƒ‹ƒXƒgƒŒƒCƒtƒBƒ“ƒO
		case MA_DOUBLE:
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 90+10*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case HT_FREEZINGTRAP:		// ƒtƒŠ[ƒWƒ“ƒOƒgƒ‰ƒbƒv
			calc_flag.nocardfix = 1;
			break;
		case HT_POWER:		// ƒr[ƒXƒgƒXƒgƒŒƒCƒtƒBƒ“ƒO
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 100+16*s_str, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case AC_SHOWER:		// ƒAƒ[ƒVƒƒƒ[
		case MA_SHOWER:
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
#ifdef PRE_RENEWAL
			DMG_FIX( 75+5*skill_lv, 100 );
#else
			DMG_FIX( 150+10*skill_lv, 100 );
#endif
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			wd.blewcount = 0;
			break;
		case AC_CHARGEARROW:	// ƒ`ƒƒ[ƒWƒAƒ[
		case MA_CHARGEARROW:
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 150, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case HT_PHANTASMIC:	// ƒtƒ@ƒ“ƒ^ƒYƒ~ƒbƒNƒAƒ[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 150, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case KN_CHARGEATK:	// ƒ`ƒƒ[ƒWƒAƒ^ƒbƒN
			{
				int dist = unit_distance(src,target)-1;
				if(dist > 2)
					DMG_FIX( 100+100*(dist/3), 100 );
			}
			break;
		case AS_VENOMKNIFE:	// ƒxƒiƒ€ƒiƒCƒt
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			calc_flag.nocardfix = 1;
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case SG_SUN_WARM:	// ‘¾—z‚Ì‰·‚à‚è
		case SG_MOON_WARM:	// Œ‚Ì‰·‚à‚è
		case SG_STAR_WARM:	// ¯‚Ì‰·‚à‚è
			if(src_sd) {
				if(src_sd->status.sp < 2) {
					status_change_end(src,SC_WARM,-1);
					break;
				}
				// ‰£‚Á‚½‚Ì‚ÅSPÁ”ï
				src_sd->status.sp -= 2;
				clif_updatestatus(src_sd,SP_SP);
			}
			wd.blewcount = 0;
			break;
		case KN_PIERCE:		// ƒsƒA[ƒX
		case ML_PIERCE:
			DMG_FIX( 100+10*skill_lv, 100 );
			break;
		case KN_SPEARSTAB:	// ƒXƒsƒAƒXƒ^ƒu
#ifdef PRE_RENEWAL
			DMG_FIX( 100+15*skill_lv, 100 );
#else
			DMG_FIX( 100+20*skill_lv, 100 );
#endif
			wd.blewcount = 0;
			break;
		case KN_SPEARBOOMERANG:	// ƒXƒsƒAƒu[ƒƒ‰ƒ“
			DMG_FIX( 100+50*skill_lv, 100 );
			break;
		case KN_BRANDISHSPEAR:	// ƒuƒ‰ƒ“ƒfƒBƒbƒVƒ…ƒXƒsƒA
		case ML_BRANDISH:
			{
				int rate = 1000+200*skill_lv;
				int bds = 0;
				if(wflag == 1) {
					if(skill_lv > 3)
						bds += rate/2;
					if(skill_lv > 6)
						bds += rate/4;
					if(skill_lv > 9)
						bds += rate/8;
				} else if(wflag == 2) {
					if(skill_lv > 6)
						bds += rate/2;
					if(skill_lv > 9)
						bds += rate/4;
				} else if(wflag == 3) {
					if(skill_lv > 3)
						bds += rate/2;
				}
				DMG_FIX( rate+bds, 1000 );
			}
			break;
		case KN_BOWLINGBASH:	// ƒ{ƒEƒŠƒ“ƒOƒoƒbƒVƒ…
		case MS_BOWLINGBASH:
			DMG_FIX( 100+40*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case AS_SONICBLOW:	// ƒ\ƒjƒbƒNƒuƒ[
			{
#ifdef PRE_RENEWAL
				int rate = 300+50*skill_lv;
				if(src_sd && pc_checkskill(src_sd,AS_SONICACCEL) > 0)
					rate = rate*110/100;
#else
				int rate = 400+40*skill_lv;
				if(sc && sc->data[SC_EDP].timer != -1)
					rate >>= 1;
#endif
				if(sc && sc->data[SC_ASSASIN].timer != -1)
				{
					if(map[src->m].flag.gvg)
						rate = rate*125/100;
					else
						rate *= 2;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case AS_GRIMTOOTH:	// ƒOƒŠƒ€ƒgƒD[ƒX
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
		case TF_SPRINKLESAND:	// »‚Ü‚«
			DMG_FIX( 130, 100 );
			break;
		case MC_CARTREVOLUTION:	// ƒJ[ƒgƒŒƒ{ƒŠƒ…[ƒVƒ‡ƒ“
#ifdef PRE_RENEWAL
			if(src_sd && src_sd->cart_max_weight > 0 && src_sd->cart_weight > 0) {
				DMG_FIX( 150 + pc_checkskill(src_sd,BS_WEAPONRESEARCH) + src_sd->cart_weight*100/src_sd->cart_max_weight, 100 );
			} else {
				DMG_FIX( 150, 100 );
			}
#endif
			wd.blewcount = 0;
			break;
		case NPC_COMBOATTACK:	// ‘½’iUŒ‚
			DMG_FIX( 50, 100 );
			break;
		case NPC_RANDOMATTACK:	// ƒ‰ƒ“ƒ_ƒ€ATKUŒ‚
			DMG_FIX( 50+atn_rand()%150, 100 );
			break;
		case NPC_WATERATTACK:
		case NPC_GROUNDATTACK:
		case NPC_FIREATTACK:
		case NPC_WINDATTACK:
		case NPC_POISONATTACK:
		case NPC_HOLYATTACK:
		case NPC_DARKNESSATTACK:
		case NPC_TELEKINESISATTACK:
		case NPC_UNDEADATTACK:
			DMG_FIX( 25+75*skill_lv, 100 );
			break;
		case NPC_PIERCINGATT:
			DMG_FIX( 75, 100 );
			break;
		case RG_BACKSTAP:	// ƒoƒbƒNƒXƒ^ƒu
			{
				int rate = 300+40*skill_lv;
				if(src_sd && src_sd->status.weapon == WT_BOW) {	// ‹|‚È‚ç”¼Œ¸
					rate /= 2;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case RG_RAID:		// ƒTƒvƒ‰ƒCƒYƒAƒ^ƒbƒN
#ifdef PRE_RENEWAL
			DMG_FIX( 100+40*skill_lv, 100 );
#else
			DMG_FIX( 100+80*skill_lv, 100 );
#endif
			break;
		case RG_INTIMIDATE:	// ƒCƒ“ƒeƒBƒ~ƒfƒCƒg
			DMG_FIX( 100+30*skill_lv, 100 );
			break;
		case CR_SHIELDCHARGE:	// ƒV[ƒ‹ƒhƒ`ƒƒ[ƒW
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
#ifdef PRE_RENEWAL
		case CR_SHIELDBOOMERANG:	// ƒV[ƒ‹ƒhƒu[ƒƒ‰ƒ“
			if(src_sd && src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					wd.damage += src_sd->inventory_data[idx]->weight/10;
					wd.damage += src_sd->status.inventory[idx].refine * status_get_overrefine_bonus(0);
				}
			}
			break;
#endif
		case CR_HOLYCROSS:	// ƒz[ƒŠ[ƒNƒƒX
		case NPC_DARKCROSS:	// ƒ_[ƒNƒNƒƒX
			DMG_FIX( 100+35*skill_lv, 100 );
			break;
		case CR_GRANDCROSS:	// ƒOƒ‰ƒ“ƒhƒNƒƒX
		case NPC_GRANDDARKNESS:	// ƒOƒ‰ƒ“ƒhƒ_[ƒNƒlƒX
			if (!battle_config.gx_cardfix)
				calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case AM_DEMONSTRATION:	// ƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
			DMG_FIX( 100+20*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
		case AM_ACIDTERROR:	// ƒAƒVƒbƒhƒeƒ‰[
			DMG_FIX( 100+40*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
#endif
		case MO_TRIPLEATTACK:	// O’i¶
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
		case MO_FINGEROFFENSIVE:	// w’e
#ifdef PRE_RENEWAL
			DMG_FIX( 100+50*skill_lv, 100 );
#else
			DMG_FIX( 125+25*skill_lv, 100 );
#endif
			break;
		case MO_INVESTIGATE:	// ”­™¤
#ifdef PRE_RENEWAL
			if(t_def1 < 1000000) {
				DMG_FIX( (100+75*skill_lv) * (t_def1 + t_def2), 100*50 );
			}
#else
			DMG_FIX( 100+75*skill_lv, 100 );
#endif
			break;
		case MO_BALKYOUNG:
			DMG_FIX( 300, 100 );
			break;
		case MO_EXTREMITYFIST:	// ˆ¢C—…”e–PŒ
			if(src_sd) {
#ifdef PRE_RENEWAL
				DMG_FIX( 8+src_sd->status.sp/10, 1 );
#else
				wd.damage = wd.damage * (800+src_sd->status.sp*10) / 100;
#endif
				src_sd->status.sp = 0;
				clif_updatestatus(src_sd,SP_SP);
			} else {
				DMG_FIX( 8, 1 );
			}
			DMG_ADD( 250+150*skill_lv );
#ifndef PRE_RENEWAL
			wd.damage -= t_def1 + t_def2;
#endif
			break;
		case MO_CHAINCOMBO:	// ˜A‘Å¶
#ifdef PRE_RENEWAL
			DMG_FIX( 150+50*skill_lv, 100 );
#else
			DMG_FIX( 250+50*skill_lv, 100 );
#endif
			break;
		case MO_COMBOFINISH:	// –Ò—´Œ
#ifdef PRE_RENEWAL
			DMG_FIX( 240+60*skill_lv, 100 );
#else
			DMG_FIX( 450+50*skill_lv, 100 );
#endif
			// PT‚É‚Í“ü‚Á‚Ä‚¢‚é
			// ƒJƒEƒ“ƒ^[ƒAƒ^ƒbƒN‚ÌŠm—¦ã¸
			if(src_sd && src_sd->status.party_id > 0) {
				struct party *pt = party_search(src_sd->status.party_id);
				if(pt != NULL)
				{
					struct map_session_data* psrc_sd = NULL;
					for(i=0; i<MAX_PARTY; i++)
					{
						psrc_sd = pt->member[i].sd;
						if(!psrc_sd || src_sd == psrc_sd)
							continue;
						if(src_sd->bl.m == psrc_sd->bl.m && pc_checkskill(psrc_sd,TK_COUNTER) > 0)
						{
							status_change_start(&psrc_sd->bl,SC_COUNTER_RATE_UP,1,0,0,0,battle_config.tk_counter_rate_up_keeptime,0);
						}
					}
				}
			}
			break;
		case TK_STORMKICK:	// ù•—R‚è
			DMG_FIX( 160+20*skill_lv, 100 );
			break;
		case TK_DOWNKICK:	// ‰º’iR‚è
			DMG_FIX( 160+20*skill_lv, 100 );
			break;
		case TK_TURNKICK:	// ‰ñ“]R‚è
			DMG_FIX( 190+30*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case TK_COUNTER:	// ƒJƒEƒ“ƒ^[R‚è
			DMG_FIX( 190+30*skill_lv, 100 );
			// PT‚É‚Í“ü‚Á‚Ä‚¢‚é
			// O’i¶‚ÌŠm—¦ã¸
			if(src_sd && src_sd->status.party_id > 0 && (skill = pc_checkskill(src_sd,SG_FRIEND)) > 0) {
				struct party *pt = party_search(src_sd->status.party_id);
				if(pt != NULL)
				{
					struct map_session_data* psrc_sd = NULL;
					for(i=0; i<MAX_PARTY; i++)
					{
						psrc_sd = pt->member[i].sd;
						if(!psrc_sd || src_sd == psrc_sd)
							continue;
						if(src_sd->bl.m == psrc_sd->bl.m && pc_checkskill(psrc_sd,MO_TRIPLEATTACK) > 0)
						{
							status_change_start(&psrc_sd->bl,SC_TRIPLEATTACK_RATE_UP,skill,0,0,0,battle_config.tripleattack_rate_up_keeptime,0);
						}
					}
				}
			}
			break;
		case BA_MUSICALSTRIKE:	// ƒ~ƒ…[ƒWƒJƒ‹ƒXƒgƒ‰ƒCƒN
		case DC_THROWARROW:	// –îŒ‚‚¿
			DMG_FIX( 60+40*skill_lv, 100 );
			break;
		case CH_TIGERFIST:	// •šŒÕŒ
			DMG_FIX( 40+100*skill_lv, 100 );
			break;
		case CH_CHAINCRUSH:	// ˜A’Œ•öŒ‚
			DMG_FIX( 400+100*skill_lv, 100 );
			break;
		case CH_PALMSTRIKE:	// –ÒŒÕd”hR
			DMG_FIX( 200+100*skill_lv, 100 );
			break;
#ifdef PRE_RENEWAL
		case LK_SPIRALPIERCE:	// ƒXƒpƒCƒ‰ƒ‹ƒsƒA[ƒX
		case ML_SPIRALPIERCE:
			DMG_FIX( 80+40*skill_lv, 100 );
			break;
#endif
		case LK_HEADCRUSH:	// ƒwƒbƒhƒNƒ‰ƒbƒVƒ…
			DMG_FIX( 100+40*skill_lv, 100 );
			break;
		case LK_JOINTBEAT:	// ƒWƒ‡ƒCƒ“ƒgƒr[ƒg
			DMG_FIX( 50+10*skill_lv, 100 );
			break;
		case ASC_METEORASSAULT:	// ƒƒeƒIƒAƒTƒ‹ƒg
			DMG_FIX( 40+40*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case ASC_BREAKER:	// ƒ\ƒEƒ‹ƒuƒŒƒCƒJ[
			DMG_FIX( skill_lv, 1 );
			calc_flag.nocardfix = 1;
			break;
#endif
		case SN_SHARPSHOOTING:	// ƒVƒƒ[ƒvƒVƒ…[ƒeƒBƒ“ƒO
		case MA_SHARPSHOOTING:
			DMG_FIX( 200+50*skill_lv, 100 );
			break;
		case CG_ARROWVULCAN:	// ƒAƒ[ƒoƒ‹ƒJƒ“
			DMG_FIX( 200+100*skill_lv, 100 );
			break;
		case AS_SPLASHER:	// ƒxƒiƒ€ƒXƒvƒ‰ƒbƒVƒƒ[
			if(src_sd) {
#ifdef PRE_RENEWAL
				DMG_FIX( 500+50*skill_lv+20*pc_checkskill(src_sd,AS_POISONREACT), 100 );
#else
				DMG_FIX( 500+75*skill_lv, 100 );
#endif
			} else {
#ifdef PRE_RENEWAL
				DMG_FIX( 500+50*skill_lv, 100 );
#else
				DMG_FIX( 500+75*skill_lv, 100 );
#endif
			}
			if(wflag > 1) {
				DMG_FIX( 1, wflag );
			}
			calc_flag.nocardfix = 1;
			break;
		case AS_POISONREACT:	// ƒ|ƒCƒYƒ“ƒŠƒAƒNƒgiUŒ‚‚Å”½Œ‚j
			wd.damage = wd.damage*(100+30*skill_lv)/100;
			//wd.damage2 = wd.damage2	// ¶è‚É‚Íæ‚ç‚È‚¢
			break;
		case TK_JUMPKICK:	// ”ò‚ÑR‚è
			if(sc && (sc->data[SC_RUN].timer != -1 || sc->data[SC_DODGE_DELAY].timer != -1)) {
				DMG_FIX( 30 + (10+status_get_lv(src)/10)*skill_lv, 100 );
				if(sc->data[SC_DODGE_DELAY].timer != -1)
					status_change_end(src,SC_DODGE_DELAY,-1);
			} else {
				DMG_FIX( 30+10*skill_lv, 100 );
			}
			if(src_sd && sc && sc->data[SC_RUN].timer != -1 && sc->data[SC_SPURT].timer != -1) {
				// ƒ^ƒCƒŠƒM’†‚ÅŠ‚ÂƒXƒp[ƒgó‘Ô‚È‚çˆĞ—Í‚³‚ç‚ÉƒAƒbƒv
				// ŒvZ®•s–¾‚È‚Ì‚Å“K“–
				DMG_ADD( 10*pc_checkskill(src_sd,TK_RUN) );
			}
			// ƒeƒBƒIƒAƒvƒ`ƒƒƒM‚É‚æ‚é‘ÎÛ‚ÌƒXƒe[ƒ^ƒXˆÙí‰ğœ
			if(target_sd && target_sd->status.class_ == PC_CLASS_SL)	// ƒ\ƒEƒ‹ƒŠƒ“ƒJ[‚Í–³‹
				break;
			if(t_sc && t_sc->data[SC_PRESERVE].timer != -1)		// ƒvƒŠƒU[ƒu’†‚ÍØ‚ê‚È‚¢
				break;
			status_change_release(target,0x10);
			break;
#ifdef PRE_RENEWAL
		case PA_SHIELDCHAIN:	// ƒV[ƒ‹ƒhƒ`ƒFƒCƒ“
			if(src_sd) {
				int s_dex = status_get_dex(src);
				int s_luk = status_get_luk(src);
				int idx   = src_sd->equip_index[EQUIP_INDEX_LARM];
				DMG_SET( s_str+(s_str/10)*(s_str/10)+(s_dex/5)+(s_luk/5) );
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid))
					DMG_ADD( src_sd->status.inventory[idx].refine*4 + src_sd->inventory_data[idx]->weight/10 );
			} else {
				DMG_FIX( 100+30*skill_lv, 100 );
			}
			break;
#endif
		case WS_CARTTERMINATION:	// ƒJ[ƒgƒ^[ƒ~ƒl[ƒVƒ‡ƒ“
			{
				int rate = (skill_lv >= 16)? 1: 16-skill_lv;
				if(src_sd && src_sd->cart_max_weight > 0 && src_sd->cart_weight > 0) {
#ifdef PRE_RENEWAL
					DMG_FIX( src_sd->cart_weight, rate*100 );
					DMG_FIX( 8000, src_sd->cart_max_weight );
#else
					rate = src_sd->cart_weight / 10 / rate;
					DMG_FIX( rate, 100 );
#endif
				} else if(!src_sd) {
					DMG_FIX( 80, rate );
				}
			}
			calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case CR_ACIDDEMONSTRATION:	// ƒAƒVƒbƒhƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case GN_FIRE_EXPANSION_ACID:	// ƒtƒ@ƒCƒA[ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“(‰–_)
			{
				int s_int = status_get_int(src);
				atn_bignumber dmg = (atn_bignumber)s_int * s_int * t_vit * skill_lv * 7 / 10 / (s_int + t_vit);
				if(target->type != BL_MOB)
					dmg /= 2;
				DMG_SET( (int)dmg );
			}
			calc_flag.nocardfix = 1;
			break;
#endif
		case GS_TRIPLEACTION:	// ƒgƒŠƒvƒ‹ƒAƒNƒVƒ‡ƒ“
			DMG_FIX( 450, 100 );
			break;
		case GS_BULLSEYE:	// ƒuƒ‹ƒYƒAƒC
			DMG_FIX( 500, 100 );
			calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case GS_MAGICALBULLET:	// ƒ}ƒWƒJƒ‹ƒoƒŒƒbƒg
			{
				int matk1 = status_get_matk1(src);
				int matk2 = status_get_matk2(src);
				if(matk1 > matk2)
					wd.damage += matk2+atn_rand()%(matk1-matk2+1);
				else
					wd.damage += matk2;
			}
			break;
#endif
		case GS_TRACKING:	// ƒgƒ‰ƒbƒLƒ“ƒO
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 200+100*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DISARM:		// ƒfƒBƒXƒA[ƒ€
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_PIERCINGSHOT:	// ƒsƒA[ƒVƒ“ƒOƒVƒ‡ƒbƒg
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
#ifdef PRE_RENEWAL
			DMG_FIX( 100+20*skill_lv, 100 );
#else
			if(src_sd && src_sd->status.weapon == WT_RIFLE) {
				DMG_FIX( 150+30*skill_lv, 100 );
			} else {
				DMG_FIX( 100+20*skill_lv, 100 );
			}
#endif
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_RAPIDSHOWER:	// ƒ‰ƒsƒbƒhƒVƒƒƒ[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 500+50*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DESPERADO:	// ƒfƒXƒyƒ‰[ƒh
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 50+50*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DUST:		// ƒ_ƒXƒg
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 100+50*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_FULLBUSTER:	// ƒtƒ‹ƒoƒXƒ^[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 300+100*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_SPREADATTACK:	// ƒXƒvƒŒƒbƒhƒAƒ^ƒbƒN
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 80+20*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case NJ_SYURIKEN:	// è— Œ•“Š‚°
		case NJ_KUNAI:		// ‹ê–³“Š‚°
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case NJ_HUUMA:		// •—–‚è— Œ•“Š‚°
			{
				int rate = 150+150*skill_lv;
#ifdef PRE_RENEWAL
				if(wflag > 1)
					rate /= wflag;
#endif
				DMG_FIX( rate, 100 );
			}
			break;
		case NJ_ZENYNAGE:	// ‘K“Š‚°
			{
				int dmg = 0;
				if(src_sd) {
					dmg = src_sd->zenynage_damage;
					src_sd->zenynage_damage = 0;	// Œ‚‚Á‚½‚çƒŠƒZƒbƒg
				} else {
					dmg = skill_get_zeny(NJ_ZENYNAGE,skill_lv)/2;
					if(dmg > 0)
						dmg += atn_rand()%dmg;
					else
						dmg = 500*skill_lv + atn_rand()%(500*skill_lv);
				}
				if(target->type == BL_PC || t_mode & MD_BOSS) {
					dmg /= 2;
				}
				DMG_SET( dmg );
				calc_flag.nocardfix = 1;
			}
			break;
		case NJ_TATAMIGAESHI:	// ô•Ô‚µ
#ifdef PRE_RENEWAL
			DMG_FIX( 100+10*skill_lv, 100 );
#else
			DMG_FIX( 200+20*skill_lv, 100 );
			wd.damage = wd.damage - (t_def1 + t_def2);
#endif
			break;
		case NJ_KASUMIKIRI:	// ‰àa‚è
			DMG_FIX( 100+10*skill_lv, 100 );
			break;
		case NJ_KIRIKAGE:	// ‰ea‚è
			DMG_FIX( skill_lv, 1 );
			break;
#ifdef PRE_RENEWAL
		case NJ_ISSEN:		// ˆê‘M
			{
				int hp = status_get_hp(src);
				DMG_SET( (s_str*40)+(skill_lv*(hp-1)*8)/100 );
				unit_heal(src,-hp+1,0);
				if(sc && sc->data[SC_NEN].timer != -1)
					status_change_end(src,SC_NEN,-1);
			}
			break;
#endif
		case NPC_CRITICALSLASH:		// ƒNƒŠƒeƒBƒJƒ‹ƒXƒ‰ƒbƒVƒ…
		case NPC_FIREBREATH:		// ƒtƒ@ƒCƒAƒuƒŒƒX
		case NPC_ICEBREATH:		// ƒAƒCƒXƒuƒŒƒX
		case NPC_THUNDERBREATH:		// ƒTƒ“ƒ_[ƒuƒŒƒX
		case NPC_ACIDBREATH:		// ƒAƒVƒbƒhƒuƒŒƒX
		case NPC_DARKNESSBREATH:	// ƒ_[ƒNƒlƒXƒuƒŒƒX
		case NPC_HELLJUDGEMENT:		// ƒwƒ‹ƒWƒƒƒbƒWƒƒ“ƒg
		case NPC_DANCINGBLADE_ATK:	// ƒ_ƒ“ƒVƒ“ƒOƒuƒŒƒCƒh(˜A½)
		case NPC_DARKPIERCING:		// ƒ_[ƒNƒsƒA[ƒVƒ“ƒO
			DMG_FIX( 100*skill_lv, 100 );
			break;
		case NPC_PULSESTRIKE:		// ƒpƒ‹ƒXƒXƒgƒ‰ƒCƒN
			DMG_FIX( 100*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case NPC_VAMPIRE_GIFT:		/* ƒ”ƒ@ƒ“ƒpƒCƒAƒŠƒbƒNƒ^ƒbƒ` */
			DMG_FIX( 100 * ((skill_lv - 1) % 5 + 1), 100 );
			break;
		case HFLI_MOON:		// ƒ€[ƒ“ƒ‰ƒCƒg
			DMG_FIX( 110+110*skill_lv, 100 );
			break;
		case HFLI_SBR44:	// S.B.R.44
			if(src_hd) {
				atn_bignumber dmg = (atn_bignumber)( src_hd->intimate * skill_lv ) * ( 100-t_def1) / 100 + t_def2;
				DMG_SET( (int)dmg );
				src_hd->intimate = 200;
				if(battle_config.homun_skill_intimate_type)
					src_hd->status.intimate = 200;
				clif_send_homdata(src_hd->msd,1,src_hd->intimate/100);
			}
			break;
		case MER_CRASH:		// ƒNƒ‰ƒbƒVƒ…
			DMG_FIX( 100+10*skill_lv, 100 );
			break;
		case RK_SONICWAVE:	// ƒ\ƒjƒbƒNƒEƒF[ƒu
			DMG_FIX( (500 + 100 * skill_lv) * (status_get_lv(src)+100) / 200, 100 );
			break;
		case RK_HUNDREDSPEAR:	// ƒnƒ“ƒhƒŒƒbƒhƒXƒsƒA
			{
				int dmg = 600 + 80 * skill_lv;
				if(src_sd) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid))
						dmg += 1000 - src_sd->inventory_data[idx]->weight/10;
				}
				DMG_FIX( dmg * ((status_get_lv(src)/2+50) / 100) + (((src_sd)? pc_checkskill(src_sd,LK_SPIRALPIERCE): 0) * 50), 100 );
			}
			break;
		case RK_WINDCUTTER:	// ƒEƒBƒ“ƒhƒJƒbƒ^[
			DMG_FIX( (100 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RK_IGNITIONBREAK:	// ƒCƒOƒjƒbƒVƒ‡ƒ“ƒuƒŒƒCƒN
			{
				int dmg = 300 * skill_lv;
				int dist = unit_distance(src,target);
				if(dist > 3)			// ‰“‹——£
					dmg = 200 * skill_lv;
				else if(dist > 1)		// ’†‹——£
					dmg = 250 * skill_lv;
				dmg = dmg * status_get_lv(src) / 100;
				if(s_ele == ELE_FIRE)	// ‰Î‘®«•Ší‘•”õ
					dmg += 100 * skill_lv;
				DMG_FIX( dmg, 100 );
			}
			break;
		case RK_DRAGONBREATH:	// ƒtƒ@ƒCƒA[ƒhƒ‰ƒSƒ“ƒuƒŒƒX
		case RK_DRAGONBREATH_WATER:	// ƒEƒH[ƒ^[ƒhƒ‰ƒSƒ“ƒuƒŒƒX
			{
				int dmg = src_sd ? pc_checkskill(src_sd,RK_DRAGONTRAINING) : 0;
				dmg = (status_get_hp(src) / 75 + status_get_max_sp(src) / 6) * skill_lv * status_get_lv(src) / 100 * (95 + 5 * dmg) / 100;
				DMG_SET( battle_attr_fix(dmg, s_ele, status_get_element(target)) );
			}
			break;
		case RK_CRUSHSTRIKE:	// ƒNƒ‰ƒbƒVƒ…ƒXƒgƒ‰ƒCƒN
			{
				int dmg = 100;
				if(src_sd) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(idx >= 0 && src_sd->inventory_data[idx])
						dmg = itemdb_atk(src_sd->inventory_data[idx]->nameid) + 600 * src_sd->inventory_data[idx]->wlv + 100 * src_sd->status.inventory[idx].refine * src_sd->inventory_data[idx]->wlv;
				}
				DMG_FIX( dmg, 100 );
			}
			break;
		case RK_STORMBLAST:		// ƒXƒg[ƒ€ƒuƒ‰ƒXƒg
			DMG_FIX( ((src_sd)? pc_checkskill(src_sd,RK_RUNEMASTERY): 1) * 100 + (status_get_int(src) / 8) * 100, 100 );
			break;
		case RK_PHANTOMTHRUST:	// ƒtƒ@ƒ“ƒgƒ€ƒXƒ‰ƒXƒg
			DMG_FIX( (50 * skill_lv + ((src_sd)? pc_checkskill(src_sd,KN_SPEARMASTERY): 0) * 10) * status_get_lv(src) / 150, 100 );
			break;
		case GC_CROSSIMPACT:	// ƒNƒƒXƒCƒ“ƒpƒNƒg
			if(sc && sc->data[SC_EDP].timer != -1) {
				DMG_FIX( (1000 + 100 * skill_lv) * status_get_lv(src) / 120 / 2, 100 );
			} else {
				DMG_FIX( (1000 + 100 * skill_lv) * status_get_lv(src) / 120, 100 );
			}
			break;
		case GC_DARKILLUSION:	// ƒ_[ƒNƒCƒŠƒ…[ƒWƒ‡ƒ“
			DMG_FIX( 100, 100 );
			break;
		case GC_COUNTERSLASH:	// ƒJƒEƒ“ƒ^[ƒXƒ‰ƒbƒVƒ…
			if(src_sd) {
				int rate = (300 + 100 * skill_lv) * status_get_lv(src) / 120 + status_get_agi(src) * 2 + status_get_jlv(src) * 4;
				if(sc && sc->data[SC_EDP].timer != -1)
					rate >>= 1;
				DMG_FIX( rate, 100 );
			} else {
				DMG_FIX( (300 + 100 * skill_lv) * status_get_lv(src) / 120 + status_get_agi(src) * 2, 100 );
			}
			break;
		case GC_VENOMPRESSURE:	// ƒxƒiƒ€ƒvƒŒƒbƒVƒƒ[
			DMG_FIX( 1000, 100 );
			break;
		case GC_PHANTOMMENACE:	// ƒtƒ@ƒ“ƒgƒ€ƒƒiƒX
			DMG_FIX( 300, 100 );
			break;
		case GC_ROLLINGCUTTER:	// ƒ[ƒŠƒ“ƒOƒJƒbƒ^[
			if(sc && sc->data[SC_EDP].timer != -1) {
				DMG_FIX( (50 + 50 * skill_lv) * status_get_lv(src) / 100 / 2, 100 );
			} else {
				DMG_FIX( (50 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case GC_CROSSRIPPERSLASHER:	// ƒNƒƒXƒŠƒbƒp[ƒXƒ‰ƒbƒVƒƒ[
			{
				int dmg = (400 + 80 * skill_lv) * status_get_lv(src) / 100;
				if(sc && sc->data[SC_ROLLINGCUTTER].timer != -1) {
					dmg += sc->data[SC_ROLLINGCUTTER].val1 * status_get_agi(src) / 100;
				}
				if(sc && sc->data[SC_EDP].timer != -1) {
					dmg >>= 1;
				}
				DMG_FIX( dmg, 100 );
			}
			break;
		case GC_DARKCROW:	// ƒ_[ƒNƒNƒ[
			DMG_FIX( 100 * skill_lv, 100 );
			break;
		case AB_DUPLELIGHT_MELEE:	// ƒfƒ…ƒvƒŒƒ‰ƒCƒg(•¨—)
			DMG_FIX( 100 + 10 * skill_lv, 100 );
			break;
		case RA_CLUSTERBOMB:	// ƒNƒ‰ƒXƒ^[ƒ{ƒ€
			DMG_FIX( 200 + 100 * skill_lv, 100 );
			break;
		case RA_FIRINGTRAP:		// ƒtƒ@ƒCƒAƒŠƒ“ƒOƒgƒ‰ƒbƒv
		case RA_ICEBOUNDTRAP:	// ƒAƒCƒXƒoƒEƒ“ƒhƒgƒ‰ƒbƒv
			DMG_FIX( 100, 100 );
			break;
		case RA_ARROWSTORM:		// ƒAƒ[ƒXƒg[ƒ€
			DMG_FIX( (1000 + 80 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RA_AIMEDBOLT:		// ƒGƒCƒ€ƒhƒ{ƒ‹ƒg
			DMG_FIX( (500 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RA_WUGDASH:		// ƒEƒH[ƒOƒ_ƒbƒVƒ…
			DMG_FIX( 300, 100 );
			break;
		case RA_WUGSTRIKE:		// ƒEƒH[ƒOƒXƒgƒ‰ƒCƒN
			DMG_FIX( 250 * skill_lv, 100 );
			break;
		case RA_WUGBITE:		// ƒEƒH[ƒOƒoƒCƒg
			DMG_FIX( 800 + 200 * skill_lv, 100 );
			break;
		case RA_SENSITIVEKEEN:	// ‰s•q‚ÈškŠo
			DMG_FIX( 100 + 50 * skill_lv, 100 );
			break;
		case NC_BOOSTKNUCKLE:	// ƒu[ƒXƒgƒiƒbƒNƒ‹
			DMG_FIX( (200 + 100 * skill_lv + status_get_dex(src)) * status_get_lv(src) / 150, 100 );
			break;
		case NC_PILEBUNKER:	// ƒpƒCƒ‹ƒoƒ“ƒJ[
			DMG_FIX( (300 + 100 * skill_lv + status_get_str(src)) * status_get_lv(src) / 100, 100 );
			break;
		case NC_VULCANARM:	// ƒoƒ‹ƒJƒ“ƒA[ƒ€
			DMG_FIX( (70 * skill_lv + status_get_dex(src)) * status_get_lv(src) / 150, 100 );
			break;
		case NC_FLAMELAUNCHER:	// ƒtƒŒƒCƒ€ƒXƒ[ƒ[
		case NC_COLDSLOWER:		// ƒR[ƒ‹ƒhƒXƒ[ƒ[
			DMG_FIX( (300 + 300 * skill_lv) * status_get_lv(src) / 150, 100 );
			break;
		case NC_SELFDESTRUCTION:	// ƒZƒ‹ƒtƒfƒBƒXƒgƒ‰ƒNƒVƒ‡ƒ“
			{
				int lv = src_sd ? pc_checkskill(src_sd,NC_MAINFRAME) : 2;
				DMG_SET( (status_get_sp(src) + status_get_vit(src)) * 20 * skill_lv / 3 * status_get_lv(src) / 100 );
				wd.damage = wd.damage * (80 + 10 * lv) / 100;
				DMG_ADD( status_get_hp(src) );
			}
			break;
		case NC_AXEBOOMERANG:	// ƒAƒbƒNƒXƒu[ƒƒ‰ƒ“
			if(src_sd) {
				int dmg = 160 + 40 * skill_lv;
				int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid))
					dmg += src_sd->inventory_data[idx]->weight/10;
				DMG_FIX( dmg * status_get_lv(src) / 150, 100 );
			} else {
				DMG_FIX( (160 + 40 * skill_lv) * status_get_lv(src) / 150, 100 );
			}
			break;
		case NC_POWERSWING:	// ƒpƒ[ƒXƒCƒ“ƒO
			DMG_FIX( 180 + 20 * skill_lv + (status_get_str(src) + status_get_dex(src)) * status_get_lv(src) / 150, 100 );
			break;
		case NC_AXETORNADO:	// ƒAƒbƒNƒXƒgƒ‹ƒl[ƒh
			{
				int dmg = 200 + 100 * skill_lv + status_get_vit(src);
				int dist = unit_distance(src,target);
				if((skill_lv < 3 && dist > 1) || dist > 2)	// ŠOü
					dmg = dmg * 75 / 100;
				if(s_ele == ELE_WIND)	// •—‘®«•Ší‘•”õ
					dmg = dmg * 125 / 100;
				DMG_FIX( dmg * status_get_lv(src) / 100, 100 );
			}
			break;
#ifdef PRE_RENEWAL
		case NC_ARMSCANNON:	// ƒA[ƒ€ƒYƒLƒƒƒmƒ“
			if(src_sd && src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
			DMG_FIX( (200 + (500 - 100 * t_size) * skill_lv) * status_get_lv(src) / 150, 100 );
			break;
#endif
		case NC_MAGMA_ERUPTION:	/* ƒ}ƒOƒ}ƒCƒ‰ƒvƒVƒ‡ƒ“ */
			DMG_FIX( 450 + 50 * skill_lv, 100 );
			break;
		case SC_FATALMENACE:	// ƒtƒFƒCƒ^ƒ‹ƒƒiƒX
			DMG_FIX( 100 + 100 * skill_lv, 100 );
			break;
		case SC_TRIANGLESHOT:	// ƒgƒ‰ƒCƒAƒ“ƒOƒ‹ƒVƒ‡ƒbƒg
			DMG_FIX( 270 + 30 * skill_lv, 100 );
			break;
		case SC_FEINTBOMB:	// ƒtƒFƒCƒ“ƒgƒ{ƒ€
			DMG_FIX( 200 + 100 * skill_lv, 100 );
			break;
		case LG_CANNONSPEAR:	// ƒLƒƒƒmƒ“ƒXƒsƒA
			DMG_FIX( (50 + status_get_str(src)) * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case LG_BANISHINGPOINT:	// ƒoƒjƒVƒ“ƒOƒ|ƒCƒ“ƒg
			DMG_FIX( (50 * skill_lv + ((src_sd)? pc_checkskill(src_sd,SM_BASH): 0) * 30) * status_get_lv(src) / 100, 100 );
			break;
		case LG_SHIELDPRESS:	// ƒV[ƒ‹ƒhƒvƒŒƒX
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_FIX( (150 * skill_lv + status_get_str(src) + src_sd->inventory_data[idx]->weight/10) * status_get_lv(src) / 100, 100);
				}
			} else {
				DMG_FIX( (150 * skill_lv + status_get_str(src)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case LG_PINPOINTATTACK:	// ƒsƒ“ƒ|ƒCƒ“ƒgƒAƒ^ƒbƒN
			DMG_FIX( (100 * skill_lv + status_get_agi(src) * 5) * status_get_lv(src) / 120, 100 );
			break;
		case LG_RAGEBURST:	// ƒŒƒCƒWƒo[ƒXƒgƒAƒ^ƒbƒN
			{
				int rate;
				if(sc && sc->data[SC_FORCEOFVANGUARD].timer != -1 && sc->data[SC_FORCEOFVANGUARD].val4 > 0) {
					rate = 200 * sc->data[SC_FORCEOFVANGUARD].val4;
				} else {
					rate = 200;
				}
				rate += (status_get_max_hp(src) - status_get_hp(src)) / 100;
				rate = rate * status_get_lv(src) / 100;
				DMG_FIX( rate, 100 );
			}
			break;
		case LG_SHIELDSPELL:	// ƒV[ƒ‹ƒhƒXƒyƒ‹
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
#ifdef PRE_RENEWAL
					DMG_FIX( status_get_lv(src) * 4 + src_sd->inventory_data[idx]->def * 100 + status_get_vit(src) * 2, 100 );
#else
					DMG_FIX( status_get_lv(src) * 4 + src_sd->inventory_data[idx]->def * 10 + status_get_vit(src) * 2, 100 );
#endif
				}
			}
			else {
				DMG_FIX( status_get_lv(src) * 4 + status_get_vit(src) * 2, 100 );
			}
			break;
		case LG_OVERBRAND:	// ƒI[ƒo[ƒuƒ‰ƒ“ƒh
			DMG_FIX( (400 * skill_lv + ((src_sd)? pc_checkskill(src_sd,CR_SPEARQUICKEN): 0) * 50) * status_get_lv(src) / 150, 100 );
			break;
		case LG_OVERBRAND_BRANDISH:		// ƒI[ƒo[ƒuƒ‰ƒ“ƒh(“ã‚¬)
			DMG_FIX( (300 * skill_lv + status_get_str(src) + status_get_dex(src)) * status_get_lv(src) / 150, 100 );
			break;
		case LG_OVERBRAND_PLUSATK:		// ƒI[ƒo[ƒuƒ‰ƒ“ƒh(’ÇŒ‚)
			DMG_FIX( 200 * skill_lv, 100 );
			break;
		case LG_MOONSLASHER:	// ƒ€[ƒ“ƒXƒ‰ƒbƒVƒƒ[
			DMG_FIX( (120 * skill_lv + ((src_sd)? pc_checkskill(src_sd,LG_OVERBRAND): 0) * 80) * status_get_lv(src) / 100, 100 );
			break;
		case LG_RAYOFGENESIS:	// ƒŒƒCƒIƒuƒWƒFƒlƒVƒX
			DMG_FIX( (300 + 300 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case LG_HESPERUSLIT:	// ƒwƒXƒyƒ‹ƒXƒŠƒbƒg
			{
				int rate;
				rate = (120 * skill_lv + 200 * wd.div_) * status_get_lv(src) / 100;
				if(wd.div_ == 6) {
					rate = rate * 150 / 100;
				}
				DMG_FIX( rate, 100 );
				break;
			}
		case LG_EARTHDRIVE:	// ƒA[ƒXƒhƒ‰ƒCƒu
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid))
					DMG_FIX( ((100 + 100 * skill_lv) * src_sd->inventory_data[idx]->weight / 1000) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (100 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SR_DRAGONCOMBO:	// ‘o—³‹r
			DMG_FIX( ( 100 + 40 * skill_lv ) * status_get_lv(src) / 100, 100 );
			break;
		case SR_SKYNETBLOW:	// “V—…’n–Ô
			if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_DRAGONCOMBO) {
				DMG_FIX( (100 * skill_lv + status_get_agi(src) + 150) * status_get_lv(src) / 100, 100 );		// ƒRƒ“ƒ{”­“®
			} else {
				DMG_FIX( (80 * skill_lv + status_get_agi(src)) * status_get_lv(src) / 100, 100 );		// ’Êí
			}
			break;
		case SR_EARTHSHAKER:	// ’n—‹k
			if(!wflag) {	// ’Êí
				DMG_FIX( (50 * skill_lv * status_get_lv(src) / 100) + status_get_int(src) * 2, 100 );
			} else {	// ƒnƒCƒh‘Šè
				DMG_FIX( (150 * skill_lv * status_get_lv(src) / 100) + status_get_int(src) * 3, 100 );
			}
			break;
		case SR_FALLENEMPIRE:	// ‘å“Z•ö’Ä
			DMG_FIX( (100 + 150 * skill_lv) * status_get_lv(src) / 150, 100 );
			break;
		case SR_TIGERCANNON:	// åj–C
			if(src_sd) {
				int hp = (int)((atn_bignumber)status_get_max_hp(src) * (10 + skill_lv * 2) / 100);
				int sp = (int)((atn_bignumber)status_get_max_sp(src) * (5 + skill_lv) / 100 - 1);
				if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
					DMG_FIX( (hp + sp + 1) / 4 * 2 * status_get_lv(src) / 100 , 100 );		// ƒRƒ“ƒ{”­“®
				} else {
					DMG_FIX( (hp + sp + 1) / 4 * status_get_lv(src) / 100 , 100 );			// ’Êí
				}
				// HP,SPÁ”ï
				if(src_sd->status.hp > hp) {
					src_sd->status.hp -= hp;
				} else {
					src_sd->status.hp = 1;
				}
				clif_updatestatus(src_sd,SP_HP);

				if(src_sd->status.sp > sp) {
					src_sd->status.sp -= sp;
				} else {
					src_sd->status.sp = 0;
				}
				clif_updatestatus(src_sd,SP_SP);
			}
			break;
		case SR_RAMPAGEBLASTER:	// ”š‹CU’e
			if(src_sd && src_sd->spiritball.old) {
				if(sc && sc->data[SC_EXPLOSIONSPIRITS].timer != -1) {
					DMG_FIX( (125 + 25 * skill_lv) * status_get_lv(src) / 150 * src_sd->spiritball.old, 100 );
				} else {
					DMG_FIX( 20 * skill_lv * status_get_lv(src) / 150 * src_sd->spiritball.old, 100 );
				}
			} else if(sc && sc->data[SC_EXPLOSIONSPIRITS].timer != -1) {
				DMG_FIX( (125 + 25 * skill_lv) * status_get_lv(src) / 150, 100 );
			} else {
				DMG_FIX( 20 * skill_lv * status_get_lv(src) / 150, 100 );
			}
			break;
		case SR_KNUCKLEARROW:	// C—…g’e
			if(!wflag) {
				DMG_FIX( (500 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			} else if(target_sd) {		// Õ“Ëƒ_ƒ[ƒW
				DMG_FIX( (150 * skill_lv) + (status_get_lv(target) / 3 * 10) * status_get_lv(src) / 100 + (target_sd->weight / target_sd->max_weight * 10), 100 );
			} else {
				DMG_FIX( (150 * skill_lv) + (status_get_lv(target) / 3 * 10) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SR_WINDMILL:	// ù•—‘Ú
			DMG_FIX( (status_get_lv(src) + status_get_dex(src)) * status_get_lv(src) / 100, 100 );
			break;
		case SR_GATEOFHELL:	// —…™‹”j™€Œ‚
			DMG_FIX( 500 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case SR_GENTLETOUCH_QUIET:	// “_ŒŠ -àÒ-
			DMG_FIX( ( 100 * skill_lv + status_get_dex(src) ) * status_get_lv(src) / 100, 100 );
			break;
		case SR_HOWLINGOFLION:	// ‚q™á
			DMG_FIX( 200 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case SR_RIDEINLIGHTNING:	// —‹Œõ’e
			DMG_FIX( ( 200 * skill_lv + ((s_ele == ELE_WIND)? 50 * skill_lv: 0) ) * status_get_lv(src) / 100, 100 );
			break;
		case WM_REVERBERATION_MELEE:	// U“®c‹¿(•¨—)
			DMG_FIX( (300 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			if(wflag > 1) {
				DMG_FIX( 1, wflag );
			}
			break;
		case WM_SEVERE_RAINSTORM:		// ƒVƒrƒAƒŒƒCƒ“ƒXƒg[ƒ€
		case WM_SEVERE_RAINSTORM_MELEE:	// ƒVƒrƒAƒŒƒCƒ“ƒXƒg[ƒ€(UŒ‚)
			DMG_FIX( ( 40 * skill_lv + status_get_dex(src) ) * status_get_lv(src) / 100 + status_get_agi(src) / 4, 100 );
			break;
		case WM_GREAT_ECHO:		// ƒOƒŒ[ƒgƒGƒR[
			{
				int rate = 400 + 200 * skill_lv;
				if(wflag >= 3 && wflag <= 7) {
					rate += 100<<(wflag-3);
				}
				DMG_FIX( rate * status_get_lv(src) / 100, 100 );
			}
			break;
		case WM_SOUND_OF_DESTRUCTION:	// ƒTƒEƒ“ƒhƒIƒuƒfƒBƒXƒgƒ‰ƒNƒVƒ‡ƒ“
			DMG_FIX( 250, 100 );
			break;
		case SO_VARETYR_SPEAR:	// ƒ”ƒFƒ‰ƒ`ƒ…[ƒ‹ƒXƒsƒA
			if(sc && sc->data[SC_BLAST].timer != -1) {
				DMG_FIX( ( 50 * ( (src_sd)? pc_checkskill(src_sd,SO_STRIKING): 1 ) + 50 * skill_lv) * status_get_lv(src) / 100 + sc->data[SC_BLAST].val3, 100 );
			} else {
				DMG_FIX( ( 50 * ( (src_sd)? pc_checkskill(src_sd,SO_STRIKING): 1 ) + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case GN_CART_TORNADO:	// ƒJ[ƒgƒgƒ‹ƒl[ƒh
			DMG_FIX( 50 * skill_lv + ((src_sd)? pc_checkskill(src_sd,GN_REMODELING_CART): 1) * 50 + ((src_sd)? src_sd->cart_weight/10 / (150-src_sd->status.str): 1), 100 );
			break;
		case GN_CARTCANNON:		// ƒJ[ƒgƒLƒƒƒmƒ“
			DMG_FIX( 60 * skill_lv + (((src_sd)? pc_checkskill(src_sd,GN_REMODELING_CART): 1) * status_get_int(src) * 125 / 100), 100 );
			break;
		case GN_WALLOFTHORN:	// ƒ\[ƒ“ƒEƒH[ƒ‹
			DMG_FIX( 150 + 50 * skill_lv, 100 );
			break;
		case GN_CRAZYWEED_ATK:	// ƒNƒŒƒCƒW[ƒEƒB[ƒh
			DMG_FIX( 500 + 100 * skill_lv, 100 );
			break;
		case GN_SPORE_EXPLOSION: // ƒXƒ|ƒAƒGƒNƒXƒvƒ[ƒWƒ‡ƒ“
			if(wflag&1) {
				DMG_FIX( (100 * skill_lv + (200 + status_get_int(src)) * status_get_lv(src) / 100) * 75 / 100, 100 );
			} else {
				DMG_FIX( 100 * skill_lv + (200 + status_get_int(src)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case GN_SLINGITEM_RANGEMELEEATK:	// ƒXƒŠƒ“ƒOƒAƒCƒeƒ€(‰“‹——£UŒ‚)
			switch(skill_lv) {
			case 0:	/* ƒŠƒ“ƒS”š’e */
				DMG_FIX( 400, 100 );
				break;
			case 1:	/* ƒRƒRƒiƒbƒc”š’e */
				DMG_FIX( 1000, 100 );
				break;
			case 2:	/* ƒƒƒ“”š’e */
				DMG_FIX( 400, 100 );
				break;
			case 3:	/* ƒpƒCƒiƒbƒvƒ‹”š’e */
				DMG_FIX( 1000, 100 );
				break;
			case 4:	/* ƒoƒiƒi”š’e */
				DMG_FIX( 800, 100 );
				break;
			case 5:	/* •‚¢‰ò */
				DMG_FIX( 200, 100 );
				break;
			case 6:	/* d‚­‚Ä•‚¢‰ò */
				DMG_FIX( 300, 100 );
				break;
			case 7:	/* ‚Æ‚Ä‚àd‚¢‰ò */
				DMG_FIX( 400, 100 );
				break;
			}
			break;
		case KO_JYUMONJIKIRI:	// \•¶ša‚è
			{
				int rate = 150 * skill_lv * status_get_lv(src) / 120;

				if( t_sc && t_sc->data[SC_KO_JYUMONJIKIRI].timer != -1 )
					rate += status_get_lv(src) * skill_lv;
				DMG_FIX( rate, 100 );
			}
			break;
		case KO_SETSUDAN:		// ‰©ò•Ô‚µ
			{
				int rate = 150 * skill_lv;

				if(t_sc) {
					int soul;

					for(soul = SC_ALCHEMIST; soul <= SC_GUNNER; soul++) {
						if(t_sc->data[soul].timer != -1) {
							rate += rate;
						}
					}
				}

				DMG_FIX( rate * status_get_lv(src) / 100, 100 );
				status_change_soulclear(target);
			}
			break;
		case KO_BAKURETSU:		// ”š—ô‹ê–³
			DMG_FIX( ((skill_lv * (50 + status_get_dex(src) / 4)) * ((src_sd)? pc_checkskill(src_sd,NJ_TOBIDOUGU): 0) * 4 / 10 * status_get_lv(src) / 120) + status_get_jlv(src) * 10, 100);
			break;
		case KO_HAPPOKUNAI:		// ”ª•û‹ê–³
			DMG_FIX( 300 + 60 * skill_lv, 100 );
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case KO_MUCHANAGE:	// –³’ƒ“Š‚°
			{
				int dmg = 0;
				if(src_sd) {
					dmg = src_sd->zenynage_damage;
				} else {
					dmg = skill_get_zeny(KO_MUCHANAGE,skill_lv)/2;
					if(dmg > 0)
						dmg += atn_rand()%dmg;
					else
						dmg = 5000*skill_lv + atn_rand()%(5000*skill_lv);
				}
				if(wflag > 1)
					dmg /= wflag;
				if(t_mode & MD_BOSS)
					dmg /= 2;
				DMG_SET( dmg );
				calc_flag.nocardfix = 1;
			}
			break;
		case KO_HUUMARANKA:	// •—–‚è— Œ• -—‰Ø-
			DMG_FIX( 150 * skill_lv + status_get_agi(src) + status_get_dex(src) + ((src_sd)? pc_checkskill(src_sd, NJ_HUUMA): 0) * 100, 100 );
			break;
		case SU_BITE:	// ‚©‚İ‚Â‚­
			if(status_get_hp(target) / status_get_max_hp(target) * 100 <= 70) {
				DMG_FIX( 1500, 100 );
			} else {
				DMG_FIX( 1000, 100 );
			}
			break;
		case SU_SCRATCH:	// ‚Ğ‚Á‚©‚­
			DMG_FIX( 400 + 200 * skill_lv, 100 );
			break;
		case SU_PICKYPECK:	// ƒsƒbƒL“Ë‚«
			{
				int rate = 1250 + 50 * skill_lv;
				int t_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// ¶–½‚Ì°
					int s_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
					if(s_hp >= 100)
						rate = rate * 200 / 100;
					else if(s_hp >= 81)
						rate = rate * 150 / 100;
					else if(s_hp >= 51)
						rate = rate * 130 / 100;
					else if(s_hp >= 10)
						rate = rate * 110 / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case SU_PICKYPECK_DOUBLE_ATK:	// ƒsƒbƒL“Ë‚«(’ÇŒ‚)
			{
				int rate = 2500 + 100 * skill_lv;
				int t_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// ¶–½‚Ì°
					int s_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
					if(s_hp >= 100)
						rate = rate * 200 / 100;
					else if(s_hp >= 81)
						rate = rate * 150 / 100;
					else if(s_hp >= 51)
						rate = rate * 130 / 100;
					else if(s_hp >= 10)
						rate = rate * 110 / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case SU_SCAROFTAROU:	// ƒ^ƒƒE‚Ì
			{
				int rate = 4000 + 200 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// ¶–½‚Ì°
					int s_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
					if(s_hp >= 100)
						rate = rate * 200 / 100;
					else if(s_hp >= 81)
						rate = rate * 150 / 100;
					else if(s_hp >= 51)
						rate = rate * 130 / 100;
					else if(s_hp >= 10)
						rate = rate * 110 / 100;
				}
				if(t_mode & MD_BOSS)
					rate *= 2;
				if(t_sc && t_sc->data[SC_BITESCAR].timer != -1)	// ƒ^ƒƒE‚Ìó‘Ô
					rate *= 2;
				DMG_FIX( rate, 100 );
			}
			break;
		case SU_LUNATICCARROTBEAT:	// ƒLƒƒƒƒbƒgƒr[ƒg
			{
				int rate = 2000 + 100 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// ¶–½‚Ì°
					int s_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
					if(s_hp >= 100)
						rate = rate * 200 / 100;
					else if(s_hp >= 81)
						rate = rate * 150 / 100;
					else if(s_hp >= 51)
						rate = rate * 130 / 100;
					else if(s_hp >= 10)
						rate = rate * 110 / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case SU_SVG_SPIRIT:	// ƒTƒx[ƒW‚Ì°
			{
				int rate = 2500 + 100 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// ¶–½‚Ì°
					int s_hp = status_get_hp(target) / status_get_max_hp(target) * 100;
					if(s_hp >= 100)
						rate = rate * 200 / 100;
					else if(s_hp >= 81)
						rate = rate * 150 / 100;
					else if(s_hp >= 51)
						rate = rate * 130 / 100;
					else if(s_hp >= 10)
						rate = rate * 110 / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case EL_CIRCLE_OF_FIRE:	// ƒT[ƒNƒ‹ƒIƒuƒtƒ@ƒCƒA
			DMG_FIX( 300, 100 );
			break;
		case EL_FIRE_BOMB_ATK:	// ƒtƒ@ƒCƒA[ƒ{ƒ€(UŒ‚)
			DMG_FIX( 300, 100 );
			break;
		case EL_FIRE_WAVE_ATK:	// ƒtƒ@ƒCƒA[ƒEƒF[ƒu(UŒ‚)
			DMG_FIX( 600, 100 );
			break;
		case EL_WATER_SCREW_ATK:	// ƒEƒH[ƒ^[ƒXƒNƒŠƒ…[(UŒ‚)
			DMG_FIX( 1000, 100 );
			break;
		case EL_TIDAL_WEAPON:	// ƒ^ƒCƒ_ƒ‹ƒEƒFƒ|ƒ“
			DMG_FIX( 1500, 100 );
			break;
		case EL_WIND_SLASH:	// ƒEƒBƒ“ƒhƒXƒ‰ƒbƒVƒ…
			DMG_FIX( 200, 100 );
			break;
		case EL_HURRICANE:	// ƒnƒŠƒP[ƒ“ƒŒƒCƒW
			DMG_FIX( 700, 100 );
			break;
		case EL_TYPOON_MIS:	// ƒ^ƒCƒt[ƒ“ƒ~ƒTƒCƒ‹
			DMG_FIX( 1000, 100 );
			break;
		case EL_STONE_HAMMER:	// ƒXƒg[ƒ“ƒnƒ“ƒ}[
			DMG_FIX( 500, 100 );
			break;
		case EL_ROCK_CRUSHER:	// ƒƒbƒNƒ‰ƒ“ƒ`ƒƒ[
			DMG_FIX( 800, 100 );
			break;
		case EL_STONE_RAIN:	// ƒXƒg[ƒ“ƒŒƒCƒ“
			DMG_FIX( 800, 100 );
			break;
		case 0:			// ’ÊíUŒ‚
			DMG_FIX( 100, 100 );
			break;
		}
		if(skill_lv < 0)
			calc_flag.nocardfix = 1;

		/* ƒXƒLƒ‹”{—¦ŒvZ‚É‰ÁZI—¹ */
		if(add_rate > 0)
			add_rate = 0;

#ifdef PRE_RENEWAL
		/* 13Dƒtƒ@ƒCƒeƒBƒ“ƒO‚Ì’Ç‰Áƒ_ƒ[ƒW */
		wd.damage += tk_power_damage;
		if(calc_flag.lh)
			wd.damage2 += tk_power_damage2;

		/* 14D–hŒä–³‹”»’è‚¨‚æ‚ÑŒø‰Êƒ_ƒ[ƒWŒvZ */
		switch (skill_num) {
		case KN_AUTOCOUNTER:
		case MO_INVESTIGATE:
		case MO_EXTREMITYFIST:
		case CR_ACIDDEMONSTRATION:
		case NJ_ZENYNAGE:
		case GN_FIRE_EXPANSION_ACID:
		case KO_MUCHANAGE:
			break;
		default:
			if( wd.type != 0 )	// ƒNƒŠƒeƒBƒJƒ‹‚Í–³Œø
				break;
			if( skill_num == WS_CARTTERMINATION && !battle_config.def_ratio_atk_to_carttermination )
				break;
			if( skill_num == PA_SHIELDCHAIN && !battle_config.def_ratio_atk_to_shieldchain )
				break;
			if(src_sd && t_def1 < 1000000)
			{
				// bIgnoreDefŒn”»’è
				ignored_rate  = ignored_rate  - src_sd->ignore_def_ele[t_ele]  - src_sd->ignore_def_race[t_race]  - src_sd->ignore_def_enemy[t_enemy];
				ignored_rate_ = ignored_rate_ - src_sd->ignore_def_ele_[t_ele] - src_sd->ignore_def_race_[t_race] - src_sd->ignore_def_enemy_[t_enemy];
				if(target_sd) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_PLAYER];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_PLAYER];
				}
				if(t_mode & MD_BOSS) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_BOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_BOSS];
				} else {
					ignored_rate  -= src_sd->ignore_def_race[RCT_NONBOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_NONBOSS];
				}

				if(battle_config.left_cardfix_to_right) {
					// ¶èƒJ[ƒh•â³İ’è‚ ‚è
					ignored_rate -= 100 - ignored_rate_;
					ignored_rate_ = 100;
				}

				if(skill_num != CR_GRANDCROSS && skill_num != AM_ACIDTERROR && skill_num != LG_RAYOFGENESIS) {
					int mask = (1<<t_race) | ( (t_mode&MD_BOSS)? (1<<RCT_BOSS): (1<<RCT_NONBOSS))  | ( (target_sd)? (1<<RCT_PLAYER): 0 );

					// bDefRatioATKŒnAbIgnoreDefŒn‚ª–³‚¢‚Æ‚«‚Ì‚İŒø‰Ê—L‚è
					if( !calc_flag.idef && ignored_rate == 100 && (src_sd->def_ratio_atk_ele & (1<<t_ele) || src_sd->def_ratio_atk_race & mask || src_sd->def_ratio_atk_enemy & (1<<t_enemy)) ) {
						if(skill_num != ASC_BREAKER || !calc_flag.idef_) {
							wd.damage = (wd.damage * (t_def1 + t_def2)) / 100;
							calc_flag.idef = 1;
						}
					}
					if( calc_flag.lh || skill_num == ASC_BREAKER ) {
						if( !calc_flag.idef_ && ignored_rate_ == 100 && (src_sd->def_ratio_atk_ele_ & (1<<t_ele) || src_sd->def_ratio_atk_race_ & mask || src_sd->def_ratio_atk_enemy_ & (1<<t_enemy)) ) {
							if(skill_num != ASC_BREAKER || (!calc_flag.idef && battle_config.left_cardfix_to_right)) {
								wd.damage2 = (wd.damage2 * (t_def1 + t_def2)) / 100;
								calc_flag.idef_ = 1;
								if(!calc_flag.idef && battle_config.left_cardfix_to_right) {
									wd.damage = (wd.damage * (t_def1 + t_def2)) / 100;
									calc_flag.idef = 1;
								}
							}
						}
					}
				}
			}

			// ƒOƒ‰ƒ“ƒhƒNƒƒXAƒOƒ‰ƒ“ƒhƒ_[ƒNƒlƒX‚ÍDEF–³‹‚ğ‹­§‰ğœ
			if(skill_num == CR_GRANDCROSS || skill_num == NPC_GRANDDARKNESS) {
				calc_flag.idef  = 0;
				calc_flag.idef_ = 0;
			}
			break;
		}
#else
		/* iREjƒXƒLƒ‹C³‚Ti’Ç‰Áƒ_ƒ[ƒW‚Qj */
		if(src_sd && src_sd->status.weapon == WT_KATAR && skill_num != ASC_BREAKER && skill_lv >= 0) {
			// ƒJƒ^[ƒ‹Œ¤‹†
			if((skill = pc_checkskill(src_sd,ASC_KATAR)) > 0) {
				wd.damage += wd.damage*(10+(skill * 2))/100;
			}
		}

		/* iREj¸˜Bƒ_ƒ[ƒW‚Ì’Ç‰Á */
		if( src_sd ) {
			switch (skill_num) {
			case CR_SHIELDBOOMERANG:	// ƒV[ƒ‹ƒhƒu[ƒƒ‰ƒ“
				wd.damage = status_get_baseatk(src);
				if(src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
					int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
					if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
						wd.damage += src_sd->inventory_data[idx]->weight/10;
						wd.damage += src_sd->status.inventory[idx].refine * 4;
					}
				}
				break;
			}
		}
#endif

		/* 15D‘ÎÛ‚Ì–hŒä—Í‚É‚æ‚éƒ_ƒ[ƒW‚ÌŒ¸­ */
		switch (skill_num) {
#ifndef PRE_RENEWAL
		case MC_CARTREVOLUTION:
		case CR_SHIELDBOOMERANG:
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
		case AM_DEMONSTRATION:
		case AM_ACIDTERROR:
		case ASC_BREAKER:
		case PA_SHIELDCHAIN:
		case GS_MAGICALBULLET:
		case NJ_SYURIKEN:
		case NJ_KUNAI:
		case NJ_ISSEN:
		case NJ_TATAMIGAESHI:
#endif
		case KN_AUTOCOUNTER:
		case MO_INVESTIGATE:
		case MO_EXTREMITYFIST:
		case CR_ACIDDEMONSTRATION:
		case NJ_ZENYNAGE:
		case NPC_CRITICALSLASH:
		case GS_PIERCINGSHOT:
		case RA_CLUSTERBOMB:
		case RA_FIRINGTRAP:
		case RA_ICEBOUNDTRAP:
		case GC_COUNTERSLASH:
		case NC_ARMSCANNON:
		case NC_SELFDESTRUCTION:
		case LG_RAYOFGENESIS:
		case GN_FIRE_EXPANSION_ACID:
		case KO_MUCHANAGE:
			break;
		default:
#ifdef PRE_RENEWAL
			if(wd.type != 0)	// ƒNƒŠƒeƒBƒJƒ‹‚Í–³Œø
				break;
#endif
			// ‘¾—z‚ÆŒ‚Æ¯‚Ì—Z‡ DEF–³‹
			if(sc && sc->data[SC_FUSION].timer != -1)
				calc_flag.idef = 1;

			// DEF–³‹ƒtƒ‰ƒO‚ª‚È‚¢‚Æ‚«
			if( ((calc_flag.rh && !calc_flag.idef) || (calc_flag.lh && !calc_flag.idef_)) && t_def1 < 1000000 )
			{
				int vitbonusmax;

				// ƒGƒNƒXƒsƒAƒeƒBƒI
				if(sc && sc->data[SC_EXPIATIO].timer != -1 && wd.flag&BF_SHORT) {
					t_def1 -= t_def1 * sc->data[SC_EXPIATIO].val2 / 100;
				}

				// “_ŒŠ -Šˆ-
				if(t_sc && t_sc->data[SC_GENTLETOUCH_REVITALIZE].timer != -1) {
					t_def2 += t_sc->data[SC_GENTLETOUCH_REVITALIZE].val2;
				}

				if(battle_config.vit_penalty_type > 0 && (!t_sc || t_sc->data[SC_STEELBODY].timer == -1)) {
					int target_count = 1;

					if(target->type != BL_HOM) {
						target_count = unit_counttargeted(target,battle_config.vit_penalty_count_lv);
					}
					if(target_count >= battle_config.vit_penalty_count) {
						if(battle_config.vit_penalty_type == 1) {
							int rate = 100 - (target_count - (battle_config.vit_penalty_count - 1)) * battle_config.vit_penalty_num;
							t_def1 = t_def1 * rate / 100;
							t_def2 = t_def2 * rate / 100;
							t_vit  = t_vit  * rate / 100;
						} else if(battle_config.vit_penalty_type == 2) {
							int val = (target_count - (battle_config.vit_penalty_count - 1)) * battle_config.vit_penalty_num;
							t_def1 -= val;
							t_def2 -= val;
							t_vit  -= val;
						}
						if(t_def1 < 0) t_def1 = 0;
						if(t_def2 < 1) t_def2 = 1;
						if(t_vit  < 1) t_vit  = 1;
					}
				}

#ifdef PRE_RENEWAL
				// ƒtƒH[ƒXƒIƒuƒoƒ“ƒK[ƒh
				if(t_sc && t_sc->data[SC_FORCEOFVANGUARD].timer != -1) {
					t_def1 += (t_def1 * t_sc->data[SC_FORCEOFVANGUARD].val1 * 2) / 100;
				}
				// ƒJƒ‚ƒtƒ‰[ƒWƒ…
				if(t_sc && t_sc->data[SC_CAMOUFLAGE].timer != -1 && t_sc->data[SC_CAMOUFLAGE].val3 >= 0)
					t_def1 -= t_def1 * ((10 - t_sc->data[SC_CAMOUFLAGE].val3) * 5) / 100;
				// ƒGƒR[‚Ì‰Ì
				if(t_sc && t_sc->data[SC_ECHOSONG].timer != -1) {
					// ÀÛ‚É‚ÍœZDEF‘‰Á‚¾‚ªAb’è‚ÅŒ¸ZDEF
					t_def2 += t_def2 * t_sc->data[SC_ECHOSONG].val4 / 100;
				}
				// “y•„F„‰ò
				if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
					// ÀÛ‚É‚ÍœZDEF‘‰Á‚¾‚ªAb’è‚ÅŒ¸ZDEF
					t_def2 += t_def2 * src_sd->elementball.num * 10 / 100;
				}
#else
				if(t_sc) {
					short reduce = 100;
					// ƒAƒXƒ€ƒvƒeƒBƒI
					if(t_sc->data[SC_ASSUMPTIO].timer != -1) {
						if(map[target->m].flag.pvp || map[target->m].flag.gvg)
							reduce += 35;	// ƒV[ƒY‚Í35%
						else
							reduce += 100;	// ‚»‚êˆÈŠO‚Í100%
					}
					// ƒtƒH[ƒXƒIƒuƒoƒ“ƒK[ƒh
					if(t_sc->data[SC_FORCEOFVANGUARD].timer != -1) {
						reduce += t_sc->data[SC_FORCEOFVANGUARD].val1 * 2;
					}
					// ƒGƒR[‚Ì‰Ì
					if(t_sc->data[SC_ECHOSONG].timer != -1) {
						reduce += t_sc->data[SC_ECHOSONG].val4;
					}
					// ƒJƒ‚ƒtƒ‰[ƒWƒ…
					if(t_sc->data[SC_CAMOUFLAGE].timer != -1 && t_sc->data[SC_CAMOUFLAGE].val3 >= 0) {
						reduce -= (10 - t_sc->data[SC_CAMOUFLAGE].val3) * 5;
					}
					// “y•„F„‰ò
					if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
						reduce += src_sd->elementball.num * 10;
					}
					t_def1 = t_def1 * reduce / 100;
				}
#endif

				// ƒfƒBƒoƒCƒ“ƒvƒƒeƒNƒVƒ‡ƒ“
				if(target_sd && (skill = pc_checkskill(target_sd,AL_DP)) > 0) {
					int s_race = status_get_race(src);
					if(battle_check_undead(s_race,status_get_elem_type(src)) || s_race == RCT_DEMON)
						t_def2 += ((300 + 4 * target_sd->status.base_level) * skill) / 100;
				}
				// ƒŒƒ“ƒWƒƒ[ƒƒCƒ“
				if(target_sd && (skill = pc_checkskill(target_sd,RA_RANGERMAIN)) > 0) {
					int s_race = status_get_race(src);
					if(s_race == RCT_BRUTE || s_race == RCT_PLANT || s_race == RCT_FISH)
						t_def2 += skill * 5;
				}
				// ‰Î‚Æ‘å’n‚ÌŒ¤‹†
				if(target_sd && (skill = pc_checkskill(target_sd,NC_RESEARCHFE)) > 0) {
					int s_element = status_get_element(src)%20;
					if(s_element == ELE_FIRE || s_element ==  ELE_EARTH)
						t_def2 += skill * 10;
				}
				vitbonusmax = (t_vit / 20) * (t_vit / 20) - 1;

				if(calc_flag.rh && !calc_flag.idef) {
					if(ignored_rate > 0) {
						// bIgnoreDef‰EèŒvZ
						int t_def1_fix   = t_def1 * ignored_rate / 100;
						int t_def2_fix   = t_def2 * ignored_rate / 100;
						int vitbonus_fix = vitbonusmax * ignored_rate / 100;

						if(battle_config.player_defense_type) {
							wd.damage = wd.damage - (t_def1_fix * battle_config.player_defense_type) - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
							damage_ot = damage_ot - (t_def1_fix * battle_config.player_defense_type) - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
						} else {
#ifdef PRE_RENEWAL
							wd.damage = wd.damage * (100 - t_def1_fix) /100 - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
							damage_ot = damage_ot * (100 - t_def1_fix) /100;
#else
							wd.damage = wd.damage * (4000 + t_def1_fix) / (4000 + 10 * t_def1_fix) - t_def2_fix;
							damage_ot = damage_ot * (4000 + t_def1_fix) / (4000 + 10 * t_def1_fix);
#endif
						}
					}
				}
				if(calc_flag.lh && !calc_flag.idef_) {
					if(ignored_rate_ > 0) {
						// bIgnoreDef¶èŒvZ
						int t_def1_fix   = t_def1 * ignored_rate_ / 100;
						int t_def2_fix   = t_def2 * ignored_rate_ / 100;
						int vitbonus_fix = vitbonusmax * ignored_rate_ / 100;

						if(battle_config.player_defense_type) {
							wd.damage2 = wd.damage2 - (t_def1_fix * battle_config.player_defense_type) - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
							damage_ot2 = damage_ot2 - (t_def1_fix * battle_config.player_defense_type) - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
						} else {
#ifdef PRE_RENEWAL
							wd.damage2 = wd.damage2 * (100 - t_def1_fix) /100 - t_def2_fix - ((vitbonus_fix < 1)? 0: atn_rand()%(vitbonus_fix + 1) );
							damage_ot2 = damage_ot2 * (100 - t_def1_fix) /100;
#else
							wd.damage2 = wd.damage2 * (4000 + t_def1_fix) / (4000 + 10 * t_def1_fix) - t_def2_fix;
							damage_ot2 = damage_ot2 * (4000 + t_def1_fix) / (4000 + 10 * t_def1_fix);
#endif
						}
					}
				}
			}
			break;
		}

		/* 16Dó‘ÔˆÙí’†‚Ìƒ_ƒ[ƒW’Ç‰Á‚ÅƒNƒŠƒeƒBƒJƒ‹‚É‚à—LŒø‚ÈƒXƒLƒ‹ */
		if (sc) {
#ifdef PRE_RENEWAL
			// ƒI[ƒo[ƒgƒ‰ƒXƒg
			if(sc->data[SC_OVERTHRUST].timer != -1) {
				wd.damage += damage_ot*sc->data[SC_OVERTHRUST].val3/100;
				if(calc_flag.lh)
					wd.damage2 += damage_ot2*sc->data[SC_OVERTHRUST].val3/100;
			}
			// ƒI[ƒo[ƒgƒ‰ƒXƒgƒ}ƒbƒNƒX
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1) {
				wd.damage += damage_ot*(20*sc->data[SC_OVERTHRUSTMAX].val1)/100;
				if(calc_flag.lh)
					wd.damage2 += damage_ot2*(20*sc->data[SC_OVERTHRUSTMAX].val1)/100;
			}
			// ƒgƒDƒ‹[ƒTƒCƒg
			if(sc->data[SC_TRUESIGHT].timer != -1) {
				DMG_FIX( 100+2*sc->data[SC_TRUESIGHT].val1, 100 );
			}
			// ƒo[ƒT[ƒN
			if(sc->data[SC_BERSERK].timer != -1) {
				DMG_FIX( 200, 100 );
			}
			// ƒGƒ“ƒ`ƒƒƒ“ƒgƒfƒbƒhƒŠ[ƒ|ƒCƒYƒ“
			if(sc->data[SC_EDP].timer != -1 && !calc_flag.nocardfix) {
				// ‰Eè‚Ì‚İ‚ÉŒø‰Ê‚ª‚Ì‚éBƒJ[ƒhŒø‰Ê–³Œø‚ÌƒXƒLƒ‹‚É‚Íæ‚ç‚È‚¢
				if(map[src->m].flag.pk && target->type == BL_PC) {
					wd.damage *= (150 + sc->data[SC_EDP].val1 * 50) * battle_config.pk_edp_down_rate / 10000;
				} else if(map[src->m].flag.gvg) {
					wd.damage *= (150 + sc->data[SC_EDP].val1 * 50) * battle_config.gvg_edp_down_rate / 10000;
				} else if(map[src->m].flag.pvp) {
					wd.damage *= (150 + sc->data[SC_EDP].val1 * 50) * battle_config.pvp_edp_down_rate / 10000;
				} else {
					wd.damage *= (150 + sc->data[SC_EDP].val1 * 50) / 100;
				}
				// calc_flag.nocardfix = 1;
			}
#endif
			// ƒTƒNƒŠƒtƒ@ƒCƒX
			if(sc->data[SC_SACRIFICE].timer != -1 && !skill_num) {
				if(t_class != MOBID_EMPERIUM) {
					int dmg = (int)((atn_bignumber)status_get_max_hp(src) * 9 / 100);
					battle_heal(NULL, src, -dmg, 0, 0);
					wd.damage  = dmg * (90 + sc->data[SC_SACRIFICE].val1 * 10) / 100;
					wd.damage2 = 0;
					calc_flag.da = 0;
					clif_misceffect2(src,366);
				}
				if((--sc->data[SC_SACRIFICE].val2) <= 0)
					status_change_end(src, SC_SACRIFICE,-1);
			}
			// ƒCƒNƒV[ƒhƒuƒŒƒCƒN
			else if(sc->data[SC_EXEEDBREAK].timer != -1 && !skill_num) {
				wd.damage  = wd.damage * sc->data[SC_EXEEDBREAK].val2 / 100;
				wd.damage2 = 0;
				status_change_end(src, SC_EXEEDBREAK,-1);
			}
#ifdef PRE_RENEWAL
			// ƒGƒ“ƒ`ƒƒƒ“ƒgƒuƒŒƒCƒh
			if(sc->data[SC_ENCHANTBLADE].timer != -1 && (!skill_num || skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP) ) {
				static struct Damage ebd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				ebd = battle_calc_attack(BF_MAGIC,src,target,RK_ENCHANTBLADE,sc->data[SC_ENCHANTBLADE].val1,wd.flag);
				wd.damage += ebd.damage + ((100 + sc->data[SC_ENCHANTBLADE].val1 * 20) * status_get_lv(src) / 150);
			}
			// ƒWƒƒƒCƒAƒ“ƒgƒOƒ[ƒX
			if(sc->data[SC_TURISUSS].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
				if(atn_rand() % 10000 < 1500) {
					wd.damage *= 3;
					if(calc_flag.lh)
						wd.damage2 *= 3;
				}
				if(src_sd && atn_rand() % 10000 < 100) {
					pc_break_equip(src_sd, LOC_RARM);
				}
			}
#endif
			// ƒV[ƒ‹ƒhƒXƒyƒ‹
			if(sc->data[SC_SHIELDSPELL_REF].timer != -1 && sc->data[SC_SHIELDSPELL_REF].val2 == 1 && !skill_num) {
				if(target_sd && atn_rand() % 100 < sc->data[SC_SHIELDSPELL_REF].val3) {
					pc_break_equip(target_sd, LOC_BODY);
				}
			}

			// ƒAƒNƒ‰ƒEƒXƒ_ƒbƒVƒ…
			if(sc->data[SC_ARCLOUSEDASH].timer != -1 && src_sd && pc_isdoram(src_sd) && wd.flag&BF_LONG) {
				wd.damage += wd.damage * sc->data[SC_ARCLOUSEDASH].val3 / 100;
			}
		}

#ifdef PRE_RENEWAL
		/* 17D¸˜Bƒ_ƒ[ƒW‚Ì’Ç‰Á */
		if( src_sd ) {
			switch(skill_num) {
			case MO_INVESTIGATE:
			case MO_EXTREMITYFIST:
			case PA_SHIELDCHAIN:
			case CR_ACIDDEMONSTRATION:
			case NJ_ZENYNAGE:
			case GN_FIRE_EXPANSION_ACID:
			case KO_MUCHANAGE:
				break;
			default:
				wd.damage += status_get_atk2(src);
				if(calc_flag.lh)
					wd.damage2 += status_get_atk_2(src);
				break;
			}
			switch (skill_num) {
			case LK_SPIRALPIERCE:		// ƒXƒpƒCƒ‰ƒ‹ƒsƒA[ƒX
				if(src_sd->equip_index[EQUIP_INDEX_RARM] >= 0) {	// {((STR/10)^2 { •Šíd—Ê~ƒXƒLƒ‹”{—¦~0.8) ~ ƒTƒCƒY•â³ { ¸˜B}~ƒJ[ƒh”{—¦~‘®«”{—¦~5‚Ì–Í—l
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid)) {
						wd.damage = ( ( (s_str/10)*(s_str/10) + src_sd->inventory_data[idx]->weight * (skill_lv * 4 + 8 ) / 100 )
									* (5 - t_size) / 4 + status_get_atk2(src) ) * 5;
					}
				}
				break;
			case PA_SHIELDCHAIN:		// ƒV[ƒ‹ƒhƒ`ƒFƒCƒ“
				if(src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
					int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
					if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
						int refinedamage = 2*(src_sd->status.inventory[idx].refine-4) + src_sd->status.inventory[idx].refine * src_sd->status.inventory[idx].refine;
						wd.damage = wd.damage * (100+30*skill_lv)/100;
						if(refinedamage > 0)
							wd.damage += atn_rand() % refinedamage;
						wd.damage = (wd.damage+100) * 5;
					}
				}
				break;
			}
		}
		if(skill_num == CR_SHIELDBOOMERANG) {	// ƒV[ƒ‹ƒhƒu[ƒƒ‰ƒ“
			int rate = 100+30*skill_lv;
			if(sc && sc->data[SC_CRUSADER].timer != -1)
				rate *= 2;
			DMG_FIX( rate, 100 );
		}

		if(sc) {
			// ƒƒ‰ƒ“ƒRƒŠ[
			if(sc->data[SC_GLOOMYDAY].timer != -1 && (skill_num == KN_BRANDISHSPEAR || skill_num == LK_SPIRALPIERCE || skill_num == CR_SHIELDCHARGE ||
			   skill_num == CR_SHIELDBOOMERANG || skill_num == PA_SHIELDCHAIN || skill_num == LG_SHIELDPRESS)) {
				wd.damage = wd.damage * (175 + sc->data[SC_GLOOMYDAY].val1 * 25) / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * (175 + sc->data[SC_GLOOMYDAY].val1 * 25) / 100;
			}
			// ƒJ[ƒgƒu[ƒXƒg
			if(sc->data[SC_GN_CARTBOOST].timer != -1) {
				wd.damage += sc->data[SC_GN_CARTBOOST].val1 * 10;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_GN_CARTBOOST].val1 * 10;
			}
		}
#endif

		// 0–¢–‚¾‚Á‚½ê‡1‚É•â³
		if(wd.damage  < 1) wd.damage  = 1;
		if(wd.damage2 < 1) wd.damage2 = 1;

		/* 18DƒXƒLƒ‹C³‚QiC—ûŒnj*/
		// C—ûƒ_ƒ[ƒW(‰Eè‚Ì‚İ) ƒ\ƒjƒbƒNƒuƒ[‚Í•Êˆ—i1Œ‚‚É•t‚«1/8“K‰)
		if(src_sd) {
#ifdef PRE_RENEWAL
			switch(skill_num) {
		    case MO_INVESTIGATE:
		    case MO_EXTREMITYFIST:
		    case CR_GRANDCROSS:
		    case NPC_GRANDDARKNESS:
		    case LK_SPIRALPIERCE:
		   	case CR_ACIDDEMONSTRATION:
		    case NJ_ZENYNAGE:
		    case LG_RAYOFGENESIS:
		    case GN_FIRE_EXPANSION_ACID:
			case KO_MUCHANAGE:
				break;
			default:
				if(skill_lv < 0)
					break;
				wd.damage = battle_addmastery(src_sd,target,wd.damage,0);
				if(calc_flag.lh)
					wd.damage2 = battle_addmastery(src_sd,target,wd.damage2,1);
				break;
			}
#endif

			if(target->type & BL_CHAR) {
				int rate = 0;
				int s_dex = status_get_dex(src);
				int s_luk = status_get_luk(src);
				int tclass = status_get_class(target);

				if(sc && sc->data[SC_MIRACLE].timer != -1) {	// ‘¾—z‚ÆŒ‚Æ¯‚ÌŠïÕ
					// ‘S‚Ä‚Ì“G‚ª¯
					rate = (src_sd->status.base_level + s_dex + s_luk + s_str) / (12 - 3 * pc_checkskill(src_sd,SG_STAR_ANGER));
				} else {
					if(tclass == src_sd->hate_mob[0] && pc_checkskill(src_sd,SG_SUN_ANGER) > 0)		// ‘¾—z‚Ì“{‚è
						rate = (src_sd->status.base_level + s_dex + s_luk) / (12 - 3 * pc_checkskill(src_sd,SG_SUN_ANGER));
					else if(tclass == src_sd->hate_mob[1] && pc_checkskill(src_sd,SG_MOON_ANGER) > 0)	// Œ‚Ì“{‚è
						rate = (src_sd->status.base_level + s_dex + s_luk) / (12 - 3 * pc_checkskill(src_sd,SG_MOON_ANGER));
					else if(tclass == src_sd->hate_mob[2] && pc_checkskill(src_sd,SG_STAR_ANGER) > 0)	// ¯‚Ì“{‚è
						rate = (src_sd->status.base_level + s_dex + s_luk + s_str) / (12 - 3 * pc_checkskill(src_sd,SG_STAR_ANGER));
				}
				if(rate > 0) {
					DMG_FIX( 100 + rate, 100 );
				}
			}
		}
		if(sc) {
			if(sc->data[SC_AURABLADE].timer != -1)		// ƒI[ƒ‰ƒuƒŒ[ƒh
				DMG_ADD( sc->data[SC_AURABLADE].val1*20 );
		}
	}

#ifdef PRE_RENEWAL
	/* 19DƒXƒLƒ‹C³‚Ri•K’†ƒ_ƒ[ƒWj*/
	if( src_sd && (skill = pc_checkskill(src_sd,BS_WEAPONRESEARCH)) > 0) {
		DMG_ADD( skill*2 );
	}
#endif
	if( src_sd && (skill = pc_checkskill(src_sd,TK_RUN)) > 0) {	// ƒ^ƒCƒŠƒMƒpƒbƒVƒu‚ÅR‚è‚ÌˆĞ—Í‰ÁZ
		if( (skill_num == TK_DOWNKICK || skill_num == TK_STORMKICK || skill_num == TK_TURNKICK || skill_num == TK_COUNTER) &&
		    src_sd->weapontype1 == WT_FIST && src_sd->weapontype2 == WT_FIST ) {
			DMG_ADD( skill*10 );
		}
	}

#ifdef PRE_RENEWAL
	/* 20DƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒW’Ç‰Áˆ— */
	if( src_sd && wd.damage > 0 && calc_flag.rh ) {
		cardfix = 100;
		if(!calc_flag.nocardfix) {
			if(!src_sd->state.arrow_atk) {	// ‹|–îˆÈŠO
				if(!battle_config.left_cardfix_to_right) {	// ¶èƒJ[ƒh•â³İ’è–³‚µ
					if(target_sd)
						cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->addrace[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³
					else
						cardfix = cardfix*(100+src_sd->addrace[t_race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³
					cardfix = cardfix*(100+src_sd->addele[t_ele])/100;	// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³
					cardfix = cardfix*(100+src_sd->addenemy[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³
					cardfix = cardfix*(100+src_sd->addsize[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³
					cardfix = cardfix*(100+src_sd->addgroup[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³
				} else {
					if(target_sd)
						cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race]+src_sd->addrace[RCT_PLAYER]+src_sd->addrace_[RCT_PLAYER])/100;		// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					else
						cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;		// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					cardfix = cardfix*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					cardfix = cardfix*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					cardfix = cardfix*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;		// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					cardfix = cardfix*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			} else { // ‹|–î
				if(target_sd)
					cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race]+src_sd->addrace[RCT_PLAYER]+src_sd->arrow_addrace[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				else
					cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				cardfix = cardfix*(100+src_sd->addele[t_ele]+src_sd->arrow_addele[t_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				cardfix = cardfix*(100+src_sd->addenemy[t_enemy]+src_sd->arrow_addenemy[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				cardfix = cardfix*(100+src_sd->addsize[t_size]+src_sd->arrow_addsize[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				cardfix = cardfix*(100+src_sd->addgroup[t_group]+src_sd->arrow_addgroup[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
			}
			if(t_mode & MD_BOSS) {	// ƒ{ƒX
				if(!src_sd->state.arrow_atk) {	// ‹|–îUŒ‚ˆÈŠO‚È‚ç
					if(!battle_config.left_cardfix_to_right) {
						// ¶èƒJ[ƒh•â³İ’è–³‚µ
						cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS])/100;					// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW
					} else {
						// ¶èƒJ[ƒh•â³İ’è‚ ‚è
						cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;	// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					}
				} else {	// ‹|–îUŒ‚
					cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS]+src_sd->arrow_addrace[RCT_BOSS])/100;		// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			} else {		// ƒ{ƒX‚¶‚á‚È‚¢
				if(!src_sd->state.arrow_atk) {	// ‹|–îUŒ‚ˆÈŠO
					if(!battle_config.left_cardfix_to_right) {
						// ¶èƒJ[ƒh•â³İ’è–³‚µ
						cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS])/100;				// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW
					} else {
						// ¶èƒJ[ƒh•â³İ’è‚ ‚è
						cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(¶è‚É‚æ‚é’Ç‰Á‚ ‚è)
					}
				} else {
					cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->arrow_addrace[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW(‹|–î‚É‚æ‚é’Ç‰Á‚ ‚è)
				}
			}
			// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒŒƒ“ƒWUŒ‚‚Ìƒ_ƒ[ƒW‘•
			if(wd.flag&BF_SHORT) {
				cardfix = cardfix * (100+src_sd->short_weapon_damege_rate) / 100;
			}
			if(wd.flag&BF_LONG) {
				cardfix = cardfix * (100+src_sd->long_weapon_damege_rate) / 100;
			}
			// “Á’èClass—p•â³ˆ—(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
			for(i=0; i<src_sd->add_damage_class_count; i++) {
				if(src_sd->add_damage_classid[i] == t_class) {
					cardfix = cardfix*(100+src_sd->add_damage_classrate[i])/100;
					break;
				}
			}
		}
		if(skill_num > 0 && wd.damage > 0) {
			int rate = 100;

			// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i•ŠíƒXƒLƒ‹j
			if(src_sd->skill_dmgup.count > 0) {
				for(i=0; i<src_sd->skill_dmgup.count; i++) {
					if(skill_num == src_sd->skill_dmgup.id[i]) {
						rate += src_sd->skill_dmgup.rate[i];
						break;
					}
				}
			}
			// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’è‘®«ƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i•ŠíƒXƒLƒ‹j
			rate += src_sd->skill_eleweapon_dmgup[s_ele];
			cardfix = cardfix*rate/100;
		}
		wd.damage = wd.damage*cardfix/100;	// ƒJ[ƒh•â³‚É‚æ‚éƒ_ƒ[ƒW‘‰Á
	}

	/* 21DƒJ[ƒh‚É‚æ‚é¶èƒ_ƒ[ƒW’Ç‰Áˆ— */
	if( src_sd && wd.damage2 > 0 && calc_flag.lh && !calc_flag.nocardfix ) {
		cardfix = 100;
		if(!battle_config.left_cardfix_to_right) {	// ¶èƒJ[ƒh•â³İ’è–³‚µ
			if(target_sd)
				cardfix = cardfix*(100+src_sd->addrace_[t_race]+src_sd->addrace_[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			else
				cardfix = cardfix*(100+src_sd->addrace_[t_race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			cardfix = cardfix*(100+src_sd->addele_[t_ele])/100;	// ‘®«‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			cardfix = cardfix*(100+src_sd->addenemy_[t_enemy])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			cardfix = cardfix*(100+src_sd->addsize_[t_size])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			cardfix = cardfix*(100+src_sd->addgroup_[t_group])/100;	// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒWC³¶è
			if(t_mode & MD_BOSS)	// ƒ{ƒX
				cardfix = cardfix*(100+src_sd->addrace_[RCT_BOSS])/100;		// ƒ{ƒXƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW¶è
			else
				cardfix = cardfix*(100+src_sd->addrace_[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠOƒ‚ƒ“ƒXƒ^[‚É’Ç‰Áƒ_ƒ[ƒW¶è
		}
		// “Á’èClass—p•â³ˆ—¶è(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
		for(i=0; i<src_sd->add_damage_class_count_; i++) {
			if(src_sd->add_damage_classid_[i] == t_class) {
				cardfix = cardfix*(100+src_sd->add_damage_classrate_[i])/100;
				break;
			}
		}
		wd.damage2 = wd.damage2*cardfix/100;	// ƒJ[ƒh•â³‚É‚æ‚é¶èƒ_ƒ[ƒW‘‰Á
	}

	/* 22Dƒ\ƒEƒ‹ƒuƒŒƒCƒJ[‚Ì–‚–@ƒ_ƒ[ƒW‚Æƒ‰ƒ“ƒ_ƒ€ƒ_ƒ[ƒWŒvZ */
	if(skill_num == ASC_BREAKER) {
		damage_sbr = status_get_int(src) * skill_lv * 5;	// –‚–@ƒ_ƒ[ƒW
		damage_sbr += 500 + (atn_rand() % 500);	// ƒ‰ƒ“ƒ_ƒ€ƒ_ƒ[ƒW
	}

	/* 23DƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒWŒ¸Šˆ— */
	if( target_sd && (wd.damage > 0 || wd.damage2 > 0 || damage_sbr > 0) ) {	// ‘ÎÛ‚ªPC‚Ìê‡
		int s_race  = status_get_race(src);
		int s_enemy = status_get_enemy_type(src);
		int s_size  = status_get_size(src);
		int s_group = status_get_group(src);
		int ele_type= status_get_elem_type(src);
		cardfix = 100;
		if(src_sd)
			cardfix = cardfix*(100-target_sd->subrace[s_race]-target_sd->subrace[RCT_PLAYER])/100;			// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		else
			cardfix = cardfix*(100-target_sd->subrace[s_race])/100;			// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		if (s_ele == ELE_NONE)
			cardfix = cardfix*(100-target_sd->subele[ELE_NEUTRAL])/100;	// ‘®«–³‚µ‚Ì‘Ï«‚Í–³‘®«
		else
			cardfix = cardfix*(100-target_sd->subele[s_ele])/100;		// ‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		if (ele_type == ELE_NONE)
			cardfix = cardfix*(100-target_sd->def_eleenemy[ELE_NEUTRAL])/100;	// ‘®«–³‚µ‚Ì‘Ï«‚Í–³‘®«
		else
			cardfix = cardfix*(100-target_sd->def_eleenemy[ele_type])/100;		// “G‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-target_sd->subenemy[s_enemy])/100;		// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-target_sd->subsize[s_size])/100;			// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-target_sd->subgroup[s_group])/100;		// ƒOƒ‹[ƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«

		if(status_get_mode(src) & MD_BOSS)
			cardfix = cardfix*(100-target_sd->subrace[RCT_BOSS])/100;	// ƒ{ƒX‚©‚ç‚ÌUŒ‚‚Íƒ_ƒ[ƒWŒ¸­
		else
			cardfix = cardfix*(100-target_sd->subrace[RCT_NONBOSS])/100;	// ƒ{ƒXˆÈŠO‚©‚ç‚ÌUŒ‚‚Íƒ_ƒ[ƒWŒ¸­

		// “Á’èClass—p•â³ˆ—¶è(­—‚Ì“ú‹L¨ƒ{ƒ“ƒSƒ“—pH)
		for(i=0; i<target_sd->add_def_class_count; i++) {
			if(target_sd->add_def_classid[i] == status_get_class(src)) {
				cardfix = cardfix*(100-target_sd->add_def_classrate[i])/100;
				break;
			}
		}
		if(wd.flag&BF_LONG && !(src_md && (skill_num == AC_SHOWER || skill_num == SN_SHARPSHOOTING)) )
			cardfix = cardfix*(100-target_sd->long_attack_def_rate)/100;	// ‰“‹——£UŒ‚‚Íƒ_ƒ[ƒWŒ¸­(ƒzƒ‹ƒ“C‚Æ‚©)
		if(wd.flag&BF_SHORT)
			cardfix = cardfix*(100-target_sd->near_attack_def_rate)/100;	// ‹ß‹——£UŒ‚‚Íƒ_ƒ[ƒWŒ¸­(ŠY“––³‚µH)
		DMG_FIX( cardfix, 100 );	// ƒJ[ƒh•â³‚É‚æ‚éƒ_ƒ[ƒWŒ¸­

		damage_sbr = damage_sbr * cardfix / 100;	// ƒJ[ƒh•â³‚É‚æ‚éƒ\ƒEƒ‹ƒuƒŒƒCƒJ[‚Ì–‚–@ƒ_ƒ[ƒWŒ¸­
	}
	// ƒGƒEƒJƒŠƒXƒeƒBƒJ
	if(target_sd && (skill = pc_checkskill(target_sd,AB_EUCHARISTICA)) > 0) {
		if(s_ele == ELE_UNDEAD || s_ele == ELE_DARK)
			DMG_FIX( 100-skill, 100 );
	}
	if(src_sd && (skill = pc_checkskill(src_sd,AB_EUCHARISTICA)) > 0) {
		if(t_ele == ELE_UNDEAD || t_ele == ELE_DARK) {
			wd.damage += wd.damage * skill / 100;
			if(calc_flag.lh)
				wd.damage2 += wd.damage2 * skill / 100;
		}
	}
#else
	if(skill_num == PA_SHIELDCHAIN && wd.damage > 0) {
		wd.damage = wd.damage - (t_def1 + t_def2);
	}
	if(wd.damage > 0) {
		int rate = 100;

		if(src_sd) {
			if(skill_num > 0) {
				// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i•ŠíƒXƒLƒ‹j
				if(src_sd->skill_dmgup.count > 0) {
					for(i=0; i<src_sd->skill_dmgup.count; i++) {
						if(skill_num == src_sd->skill_dmgup.id[i]) {
							rate += src_sd->skill_dmgup.rate[i];
							break;
						}
					}
				}
				// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’è‘®«ƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i•ŠíƒXƒLƒ‹j
				rate += src_sd->skill_eleweapon_dmgup[s_ele];
				// ƒz[ƒŠ[ƒNƒƒX
				if(skill_num == CR_HOLYCROSS && src_sd->status.weapon == WT_2HSPEAR)
					rate += 100;
			}
			// ƒtƒ@ƒCƒeƒBƒ“ƒO
			if((skill = pc_checkskill(src_sd,TK_POWER)) > 0 && src_sd->status.party_id > 0) {
				int member_num = party_check_same_map_member_count(src_sd);
				if(member_num > 0) {
					rate += member_num * skill * 2;
				}
			}
		}
		if(sc) {
			// ƒƒ‰ƒ“ƒRƒŠ[
			if(sc->data[SC_GLOOMYDAY].timer != -1 && (skill_num == KN_BRANDISHSPEAR || skill_num == LK_SPIRALPIERCE || skill_num == CR_SHIELDCHARGE ||
			   skill_num == CR_SHIELDBOOMERANG || skill_num == PA_SHIELDCHAIN || skill_num == LG_SHIELDPRESS)) {
				rate += 75 + sc->data[SC_GLOOMYDAY].val1 * 25;
			}
		}
		wd.damage = wd.damage*rate/100;
	}

	if(wd.damage > 0) {
		switch (skill_num) {
		case MC_CARTREVOLUTION:	// ƒJ[ƒgƒŒƒ{ƒŠƒ…[ƒVƒ‡ƒ“
			wd.damage = wd.damage * src_sd->cart_weight/src_sd->cart_max_weight + wd.damage * 150 / 100;
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case CR_SHIELDBOOMERANG:
			{
				int rate = 100+30*skill_lv;
				if(sc && sc->data[SC_CRUSADER].timer != -1)
					rate *= 2;
				wd.damage = wd.damage - (t_def1 + t_def2);
				wd.damage = wd.damage * rate / 100;
			}
			break;
		case NC_ARMSCANNON:
		case NC_SELFDESTRUCTION:
		case SO_VARETYR_SPEAR:
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case RA_WUGDASH:
			if(src_sd && (skill = pc_checkskill(src_sd,RA_TOOTHOFWUG)) > 0) {	// ƒgƒD[ƒXƒIƒuƒEƒH[ƒO‚É‚æ‚éƒ_ƒ[ƒW‘‰Á
				DMG_ADD( ((src_sd->weight / 10 * 5 / 4) + skill * 6) * 3 );
			}
			break;
		}
	}
#endif

	/* 24DƒAƒCƒeƒ€ƒ{[ƒiƒX‚Ìƒtƒ‰ƒOˆ— */
	if(src_sd && wd.flag&BF_WEAPON) {
		// ó‘ÔˆÙí‚ÌƒŒƒ“ƒWƒtƒ‰ƒO
		//   addeff_range_flag  0:w’è–³‚µ 1:‹ß‹——£ 2:‰“‹——£ 3,4:‚»‚ê‚¼‚ê‚ÌƒŒƒ“ƒW‚Åó‘ÔˆÙí‚ğ”­“®‚³‚¹‚È‚¢
		//   flag‚ª‚ ‚èAUŒ‚ƒ^ƒCƒv‚Æflag‚ªˆê’v‚µ‚È‚¢‚Æ‚«‚ÍAflag+2‚·‚é

		for(i = 0; i < MAX_EFF_TYPE; i++) {
			if( (src_sd->addeff_range_flag[i] == 1 && wd.flag&BF_LONG ) ||
			    (src_sd->addeff_range_flag[i] == 2 && wd.flag&BF_SHORT) ) {
				src_sd->addeff_range_flag[i] += 2;
			}
		}
	}

	/* 25D‘ÎÛ‚ÉƒXƒe[ƒ^ƒXˆÙí‚ª‚ ‚éê‡‚Ìƒ_ƒ[ƒWŒ¸Zˆ— */
	if( t_sc && (wd.damage > 0 || wd.damage2 > 0) ) {
		cardfix = 100;
		if(t_sc->data[SC_DEFENDER].timer != -1 && wd.flag&BF_LONG && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID)	// ƒfƒBƒtƒFƒ“ƒ_[ó‘Ô‚Å‰“‹——£UŒ‚
			cardfix = cardfix*(100-t_sc->data[SC_DEFENDER].val2)/100;
		if(t_sc->data[SC_ADJUSTMENT].timer != -1 && wd.flag&BF_LONG)	// ƒAƒWƒƒƒXƒgƒƒ“ƒgó‘Ô‚Å‰“‹——£UŒ‚
			cardfix -= 20;
#ifdef PRE_RENEWAL
		if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && s_ele == ELE_POISON)		// ƒxƒiƒ€ƒCƒ“ƒvƒŒƒX
			cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
		if(t_sc->data[SC_ORATIO].timer != -1 && s_ele == ELE_HOLY)		// ƒIƒ‰ƒeƒBƒI
			cardfix += t_sc->data[SC_ORATIO].val1;
#endif
		if(t_sc->data[SC_DEEP_SLEEP].timer != -1)		// ˆÀ‘§‚Ìqç‰S
			cardfix += 50;
		if(cardfix != 100) {
			DMG_FIX( cardfix, 100 );	// ƒXƒe[ƒ^ƒXˆÙí•â³‚É‚æ‚éƒ_ƒ[ƒWŒ¸­
		}
	}

	/* ‘½’iƒqƒbƒgŒvZ */
	switch(skill_num) {
	case AC_DOUBLE:		// ƒ_ƒuƒ‹ƒXƒgƒŒƒCƒtƒBƒ“ƒO
	case MA_DOUBLE:
	case KN_PIERCE:		// ƒsƒA[ƒX
	case ML_PIERCE:
	case MO_FINGEROFFENSIVE:	// w’e
	case NPC_COMBOATTACK:	// ‘½’iUŒ‚
#ifndef PRE_RENEWAL
	case NJ_KUNAI:			// ‹ê–³“Š‚°
	case LK_SPIRALPIERCE:	// ƒXƒpƒCƒ‰ƒ‹ƒsƒA[ƒX
	case PA_SHIELDCHAIN:	// ƒV[ƒ‹ƒhƒ`ƒFƒCƒ“
#endif
	case RA_AIMEDBOLT:		// ƒGƒCƒ€ƒhƒ{ƒ‹ƒg
	case LG_HESPERUSLIT:	// ƒwƒXƒyƒ‹ƒXƒŠƒbƒg
		// Hit”•ªC—û“™‚ªæ‚éƒ^ƒCƒv
		if(wd.div_ > 1)
			wd.damage *= wd.div_;
		break;
	case AS_SONICBLOW:		// ƒ\ƒjƒbƒNƒuƒ[
	case CR_HOLYCROSS:		// ƒz[ƒŠ[ƒNƒƒX
	case MO_CHAINCOMBO:		// ˜A‘Å¶
	case CH_CHAINCRUSH:		// ˜A’Œ•öŒ‚
	case CG_ARROWVULCAN:	// ƒAƒ[ƒoƒ‹ƒJƒ“
	case RK_HUNDREDSPEAR:	// ƒnƒ“ƒhƒŒƒbƒhƒXƒsƒA
	case GC_CROSSIMPACT:	// ƒNƒƒXƒCƒ“ƒpƒNƒg
	case GC_DARKCROW:		// ƒ_[ƒNƒNƒ[
	case RA_ARROWSTORM:		// ƒAƒ[ƒXƒg[ƒ€
	case NC_AXETORNADO:		// ƒAƒbƒNƒXƒgƒ‹ƒl[ƒh
	case SC_TRIANGLESHOT:	// ƒgƒ‰ƒCƒAƒ“ƒOƒ‹ƒVƒ‡ƒbƒg
	case LG_RAYOFGENESIS:	// ƒŒƒCƒIƒuƒWƒFƒlƒVƒX
	case LG_EARTHDRIVE:		// ƒA[ƒXƒhƒ‰ƒCƒu
	case SR_DRAGONCOMBO:	// ‘o—´‹r
	case SR_SKYNETBLOW:		// “V—…’n–Ô
	case SR_FALLENEMPIRE:	// ‘å“Z•öx
		// 1Hit‚ğ•ªŠ„‚µ‚Ä•\¦‚·‚éƒXƒLƒ‹
		break;
	}

	if(wd.damage  < 0) wd.damage  = 0;
	if(wd.damage2 < 0) wd.damage2 = 0;

#ifdef PRE_RENEWAL
	/* 26D‘®«‚Ì“K—p */
	wd.damage = battle_attr_fix(wd.damage, s_ele, status_get_element(target));
	if(calc_flag.lh)
		wd.damage2 = battle_attr_fix(wd.damage2, s_ele_, status_get_element(target));

	/* 27DƒXƒLƒ‹C³‚Si’Ç‰Áƒ_ƒ[ƒWj */
	if(sc && sc->data[SC_MAGNUM].timer != -1) {	// ƒ}ƒOƒiƒ€ƒuƒŒƒCƒNó‘Ô
		int bonus_damage = battle_attr_fix(wd.damage, ELE_FIRE, status_get_element(target)) * 20/100;	// ‰Î‘®«UŒ‚ƒ_ƒ[ƒW‚Ì20%‚ğ’Ç‰Á
		if(bonus_damage > 0) {
			DMG_ADD( bonus_damage );
		}
	}
	if(skill_num == ASC_BREAKER) {			// ƒ\ƒEƒ‹ƒuƒŒƒCƒJ[
		wd.damage += damage_sbr;	// –‚–@ƒ_ƒ[ƒW‚Æƒ‰ƒ“ƒ_ƒ€ƒ_ƒ[ƒW‚ğ‰ÁZ
		if(t_def1 < 1000000) {
			int vitbonusmax = (t_vit/20)*(t_vit/20)-1;
			wd.damage -= (t_def1 + t_def2 + ((vitbonusmax < 1)? 0: atn_rand()%(vitbonusmax+1)) + status_get_mdef(target) + status_get_mdef2(target))/2;
		}
	}
#endif
	if(sc) {
#ifndef PRE_RENEWAL
		// ƒGƒ“ƒ`ƒƒƒ“ƒgƒuƒŒƒCƒh
		if(sc->data[SC_ENCHANTBLADE].timer != -1 && wd.damage > 0 && (!skill_num || skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP) ) {
			static struct Damage ebd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			ebd = battle_calc_attack(BF_MAGIC,src,target,RK_ENCHANTBLADE,sc->data[SC_ENCHANTBLADE].val1,wd.flag);
			wd.damage += ebd.damage + ((100 + sc->data[SC_ENCHANTBLADE].val1 * 20) * status_get_lv(src) / 150);
		}
		// ƒWƒƒƒCƒAƒ“ƒgƒOƒ[ƒX
		if(sc->data[SC_TURISUSS].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
			if(atn_rand() % 10000 < 1500) {
				wd.damage *= 3;
				if(calc_flag.lh)
					wd.damage2 *= 3;
			}
			if(src_sd && atn_rand() % 10000 < 100) {
				pc_break_equip(src_sd, LOC_RARM);
			}
		}
#endif
		if(sc->data[SC_SPELLFIST].timer != -1 && !skill_num) {	// ƒXƒyƒ‹ƒtƒBƒXƒg
			wd = battle_calc_attack(BF_MAGIC,src,target,sc->data[SC_SPELLFIST].val2,1,wd.flag);
			wd.damage = wd.damage * (sc->data[SC_SPELLFIST].val1 + sc->data[SC_SPELLFIST].val3);
			if((--sc->data[SC_SPELLFIST].val4) <= 0)
				status_change_end(src, SC_SPELLFIST,-1);
		}
	}

	/* 28D•K’†ƒ_ƒ[ƒW‚Ì‰ÁZ */
	switch(skill_num) {
#ifdef PRE_RENEWAL
	case NJ_SYURIKEN:	// è— Œ•“Š‚°
		if(src_sd) {
			skill = pc_checkskill(src_sd,NJ_TOBIDOUGU);
			DMG_ADD( skill * 3 );
			if(src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
		}
		DMG_ADD( skill_lv*4 );
		break;
#endif
	case LG_SHIELDPRESS:	// ƒV[ƒ‹ƒhƒvƒŒƒX
		if(src_sd) {
			if(src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_ADD( src_sd->status.inventory[idx].refine * status_get_vit(src) );
				}
			}
		}
		break;
	case SR_FALLENEMPIRE:	// ‘å“Z•öx
		if(target_sd) {
			DMG_ADD( status_get_str(src) * 4 + target_sd->weight * 65 / 10 );
		} else {
			DMG_ADD( status_get_str(src) * 4 + status_get_lv(target) * 30 );
		}
		break;
	case SR_TIGERCANNON:	// åj–C
		if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
			DMG_ADD( status_get_lv(target) * 40 + skill_lv * 500 );			// ƒRƒ“ƒ{”­“®
		} else {
			DMG_ADD( status_get_lv(target) * 40 + skill_lv * 240 );			// ’Êí
		}
		break;
	case SR_GATEOFHELL:	// —…™‹”j™€Œ‚
		if(src_sd) {
			int sp = 0;
			if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
				// ƒRƒ“ƒ{”­“®
				sp = (int)((atn_bignumber)status_get_max_sp(src) * skill_lv / 100);
				DMG_ADD( status_get_max_sp(src) * ( 100 + 20 * skill_lv ) / 100 + status_get_lv(src) * 20 + status_get_max_hp(src) - status_get_hp(src) );
			} else {
				// ’Êí
				sp = (int)((atn_bignumber)status_get_max_sp(src) * (10 + skill_lv) / 100);
				DMG_ADD( ( status_get_sp(src) - sp ) * ( 100 + 20 * skill_lv ) / 100 + status_get_lv(src) * 10 + status_get_max_hp(src) - status_get_hp(src) );
			}
			// SPÁ”ï
			if(src_sd->status.sp > sp) {
				src_sd->status.sp -= sp;
			} else {
				src_sd->status.sp = 0;
			}
			clif_updatestatus(src_sd,SP_SP);
		}
		break;
	}

#ifdef PRE_RENEWAL
	if(src_sd) {
		// ¯‚Ì‚©‚¯‚çA‹C‹…‚Ì“K—p
		int hit_bonus  = src_sd->spiritball.num * 3 + src_sd->coin.num * 3 + src_sd->bonus_damage;
		int hit_damage = hit_bonus + src_sd->star + src_sd->ranker_weapon_bonus;

		if(skill_num == NJ_KUNAI) {	// ‹ê–³“Š‚°
			if(src_sd->arrow_atk) {
				hit_damage += src_sd->arrow_atk * 3;
			}
			wd.damage += hit_damage * 3;
		} else if(skill_num != NC_ARMSCANNON) {
			wd.damage += hit_damage;
			if(calc_flag.lh)
				wd.damage2 += hit_bonus + src_sd->star_ + src_sd->ranker_weapon_bonus_;
		}
	}
#endif

#ifndef PRE_RENEWAL
	/* iREjƒNƒŠƒeƒBƒJƒ‹ */
	if(wd.type == 0x0a || skill_num == LG_PINPOINTATTACK ||
		((calc_flag.idef || calc_flag.idef_) && (skill_num == SN_SHARPSHOOTING || skill_num == NJ_KIRIKAGE || skill_num == MA_SHARPSHOOTING))
	)
		wd.damage = wd.damage * 140 / 100;
#endif

	/* 29D•K’†ŒÅ’èƒ_ƒ[ƒW */
	if(src_sd && src_sd->special_state.fix_damage)
		DMG_SET( src_sd->fix_damage );

	/* 30D¶èƒ_ƒ[ƒW‚Ì•â³ */
	if(calc_flag.rh == 0 && calc_flag.lh == 1) {	// ¶è‚Ì‚İ•Ší‘•”õ
		wd.damage = wd.damage2;
		wd.damage2 = 0;
		// ˆê‰¶‰E‚ğ“ü‚ê‘Ö‚¦‚Ä‚¨‚­
		calc_flag.rh = 1;
		calc_flag.lh = 0;
	} else if(src_sd && calc_flag.lh && src_sd->status.weapon != WT_KATAR) {		// ¶è‚ª‚ ‚é‚È‚ç‰EèE¶èC—û‚Ì“K—p
		int dmg = wd.damage, dmg2 = wd.damage2;
		// ‰e˜TEO‚Ìê‡
		if(src_sd->s_class.job == PC_JOB_KG || src_sd->s_class.job == PC_JOB_OB) {
			// ‰EèC—û(80% ` 120%) ‰Eè‘S”Ê
			skill = pc_checkskill(src_sd,KO_RIGHT);
			wd.damage = wd.damage * (70 + (skill * 10))/100;
			// ¶èC—û(60% ` 100%) ¶è‘S”Ê
			skill = pc_checkskill(src_sd,KO_LEFT);
			wd.damage2 = wd.damage2 * (50 + (skill * 10))/100;
		} else {
			// ‰EèC—û(60% ` 100%) ‰Eè‘S”Ê
			skill = pc_checkskill(src_sd,AS_RIGHT);
			wd.damage = wd.damage * (50 + (skill * 10))/100;
			// ¶èC—û(40% ` 80%) ¶è‘S”Ê
			skill = pc_checkskill(src_sd,AS_LEFT);
			wd.damage2 = wd.damage2 * (30 + (skill * 10))/100;
		}
		if(dmg > 0 && wd.damage < 1) wd.damage = 1;
		if(dmg2 > 0 && wd.damage2 < 1) wd.damage2 = 1;
	} else {
		wd.damage2 = 0;	// ”O‚Ì‚½‚ß0‚ğ–¾¦‚µ‚Ä‚¨‚­
	}

	if(calc_flag.da > 0) {
		wd.type = 0x08;
		switch (calc_flag.da) {
			case 1:		// ƒ_ƒuƒ‹ƒAƒ^ƒbƒN
				wd.div_ = 2;
				wd.damage += wd.damage;
				break;
			case 2:		// ƒtƒBƒA[ƒuƒŠ[ƒY
				if(sc && sc->data[SC_FEARBREEZE].timer != -1) {
					int div_ = 2;
					if((sc->data[SC_FEARBREEZE].val1) > 2)
						div_ += atn_rand()%(sc->data[SC_FEARBREEZE].val1 - 1);
					if(src_sd) {
						if(!battle_delarrow(src_sd,div_ - 1,0))
							break;
					}
					wd.div_ = div_;
					wd.damage = wd.damage * wd.div_;
				}
				break;
		}
	}

	/* 31DƒXƒLƒ‹C³‚Ti’Ç‰Áƒ_ƒ[ƒW‚Qj */
	if(src_sd && src_sd->status.weapon == WT_KATAR && skill_num != ASC_BREAKER && skill_lv >= 0) {
#ifdef PRE_RENEWAL
		// ƒJƒ^[ƒ‹Œ¤‹†
		if((skill = pc_checkskill(src_sd,ASC_KATAR)) > 0) {
			wd.damage += wd.damage*(10+(skill * 2))/100;
		}
#endif
		// ƒJƒ^[ƒ‹’ÇŒ‚ƒ_ƒ[ƒW
		skill = pc_checkskill(src_sd,TF_DOUBLE);
		wd.damage2 = wd.damage * (1 + (skill * 2))/100;
		if(wd.damage > 0 && wd.damage2 < 1)
			wd.damage2 = 1;
	}
#ifndef PRE_RENEWAL
	// ƒ\ƒjƒbƒNƒAƒNƒZƒ‰ƒŒ[ƒVƒ‡ƒ“
	if(src_sd && skill_num == AS_SONICBLOW && (skill = pc_checkskill(src_sd,AS_SONICACCEL)) > 0)
		wd.damage += wd.damage * (skill * 10) / 100;
#endif
	switch(skill_num) {
#ifdef PRE_RENEWAL
	case TF_POISON:
		wd.damage = battle_attr_fix(wd.damage + 15*skill_lv, s_ele, status_get_element(target) );
		break;
#else
	case GS_MAGICALBULLET:
		wd.damage = battle_attr_fix(wd.damage, ELE_GHOST, status_get_element(target) );
		break;
	case AM_ACIDTERROR:
	case MO_EXTREMITYFIST:
	case CR_ACIDDEMONSTRATION:
	case GN_FIRE_EXPANSION_ACID:
	case NJ_SYURIKEN:
	case NJ_KUNAI:
	case NJ_ISSEN:
	case CR_SHIELDBOOMERANG:
	case PA_SHIELDCHAIN:
#endif
	case MC_CARTREVOLUTION:
	case NC_ARMSCANNON:
	case NC_SELFDESTRUCTION:
	case LG_SHIELDPRESS:
	case SR_FALLENEMPIRE:
	case SR_TIGERCANNON:
	case SR_GATEOFHELL:
		wd.damage = battle_attr_fix(wd.damage, ELE_NEUTRAL, status_get_element(target) );
		break;
	}

	/* 32DŠ®‘S‰ñ”ğ‚Ì”»’è */
	if(skill_num == 0 && skill_lv >= 0 && target_sd != NULL && wd.div_ < 255 && atn_rand()%1000 < status_get_flee2(target) ) {
		wd.damage  = 0;
		wd.damage2 = 0;
		wd.type    = 0x0b;
		wd.dmg_lv  = ATK_LUCKY;
	}

	if (target_md != NULL && (battle_config.enemy_perfect_flee || mobdb_search(target_md->class_)->mode_opt[MDOPT_PERFECT_FREE]))	// ‘ÎÛ‚ªŠ®‘S‰ñ”ğ‚ğ‚·‚éİ’è‚ªON‚È‚ç
	{
		if(skill_num == 0 && skill_lv >= 0 && wd.div_ < 255 && atn_rand()%1000 < status_get_flee2(target) )
		{
			wd.damage  = 0;
			wd.damage2 = 0;
			wd.type    = 0x0b;
			wd.dmg_lv  = ATK_LUCKY;
		}
	}

	/* 33DŒÅ’èƒ_ƒ[ƒW2 */
	if(t_mode&MD_PLANT) {	// Mob‚ÌMode‚ÉŠæ‹­ƒtƒ‰ƒO‚ª—§‚Á‚Ä‚¢‚é‚Æ‚«‚Ìˆ—
		if(wd.damage > 0)
			wd.damage = 1;
		if(wd.damage2 > 0)
			wd.damage2 = 1;
		if(skill_num == MO_TRIPLEATTACK) {	// O’i¶
			wd.damage *= wd.div_;
			wd.damage2 *= wd.div_;
		}
	}

	if( target_sd && target_sd->special_state.no_weapon_damage && skill_num != CR_GRANDCROSS && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP &&
	    skill_num != NPC_GRANDDARKNESS && skill_num != LG_RAYOFGENESIS && skill_num != SO_VARETYR_SPEAR) {
		// bNoWeaponDamage‚ÅƒOƒ‰ƒ“ƒhƒNƒƒX‚¶‚á‚È‚¢ê‡‚Íƒ_ƒ[ƒW‚ª0
		wd.damage = wd.damage2 = 0;
	}

	/* 34Dƒ_ƒ[ƒWÅIŒvZ */
	if(skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP &&
	   skill_num != LG_RAYOFGENESIS && skill_num != SO_VARETYR_SPEAR) {
		if(wd.damage2 < 1) {		// ƒ_ƒ[ƒWÅIC³
			wd.damage  = battle_calc_damage(src,target,wd.damage,wd.div_,skill_num,skill_lv,wd.flag);
		} else if(wd.damage < 1) {	// ‰Eè‚ªƒ~ƒXH
			wd.damage2 = battle_calc_damage(src,target,wd.damage2,wd.div_,skill_num,skill_lv,wd.flag);
		} else {			// —¼èAƒJƒ^[ƒ‹‚Ìê‡‚Í‚¿‚å‚Á‚ÆŒvZ‚â‚â‚±‚µ‚¢
			int dmg = wd.damage+wd.damage2;
			wd.damage  = battle_calc_damage(src,target,dmg,wd.div_,skill_num,skill_lv,wd.flag);
			wd.damage2 = (int)((wd.damage2*100/(float)dmg)*wd.damage/100);
			if(wd.damage > 1 && wd.damage2 < 1) wd.damage2 = 1;
			wd.damage -= wd.damage2;
		}
	}
	/* 35. “_ŒŠ -‹…-‚É‚æ‚é‹C’e‚Ì¶¬ */
	if(src_sd && sc && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && (wd.damage > 0 || wd.damage2 > 0)) {
		int max = (src_sd->s_class.job == PC_JOB_MO || src_sd->s_class.job == PC_JOB_SR)? pc_checkskill(src_sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
		if(sc->data[SC_RAISINGDRAGON].timer != -1)
			max += sc->data[SC_RAISINGDRAGON].val1;
		if(src_sd->spiritball.num < max)
			pc_addspiritball(src_sd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
	}

	/* 36D•¨—UŒ‚ƒXƒLƒ‹‚É‚æ‚éƒI[ƒgƒXƒyƒ‹”­“®(item_bonus) */
	if(wd.flag&BF_SKILL && src_sd && target != &src_sd->bl && (wd.damage + wd.damage2) > 0)
	{
		unsigned int asflag = EAS_ATTACK;
		unsigned int tick = gettick();

		if(skill_num == AM_DEMONSTRATION) {
			asflag += EAS_MISC;
		} else {
			if(wd.flag&BF_LONG)
				asflag += EAS_LONG;
			else
				asflag += EAS_SHORT;
		}

		// ƒAƒNƒeƒBƒuƒAƒCƒeƒ€‚Í•¨—UŒ‚ƒXƒLƒ‹‚Å‚à”­“®‚·‚é
		bonus_activeitem_start(src_sd,asflag+EAS_NORMAL,tick);

		// weapon_attack_autospell–³Œø‚Å‚àA—Z‡ó‘Ô‚Å‚ ‚ê‚ÎƒI[ƒgƒXƒyƒ‹‚ª”­“®‚·‚é
		if(battle_config.weapon_attack_autospell || (sc && sc->data[SC_FUSION].timer != -1))
			asflag += EAS_NORMAL;
		else
			asflag += EAS_SKILL;

		bonus_autospell_start(&src_sd->bl,target,asflag,tick,0);
	}

	/* 37D‘¾—z‚ÆŒ‚Æ¯‚Ì—Z‡ HP2%Á”ï */
	if(src_sd && sc && sc->data[SC_FUSION].timer != -1)
	{
		int hp;
		if(src_sd->status.hp < src_sd->status.max_hp * 20 / 100)	// HP‚ª20“–¢–‚Ì‚ÉUŒ‚‚ğ‚·‚ê‚Î‘¦€
			hp = src_sd->status.hp;
		else if(target->type == BL_PC)
			hp = src_sd->status.max_hp * 8 / 100;
		else
			hp = src_sd->status.max_hp * 2 / 100;

		pc_heal(src_sd,-hp,0);
	}

	/* 38DƒJƒAƒq */
	if(skill_num == 0 && wd.flag&BF_WEAPON && t_sc && t_sc->data[SC_KAAHI].timer != -1)
	{
		int kaahi_lv = t_sc->data[SC_KAAHI].val1;
		if(status_get_hp(target) < status_get_max_hp(target))
		{
			if(target->type == BL_MOB || status_get_sp(target) >= 5*kaahi_lv)	// ‘ÎÛ‚ªmobˆÈŠO‚ÅSP‚ªŒ¸­—ÊˆÈ‰º‚Ì‚Æ‚«‚Í”­¶‚µ‚È‚¢
			{
				int heal = skill_fix_heal(src, target, SL_KAAHI, 200 * kaahi_lv);
				if(target_sd) {
					if(target_sd->status.hp + heal > target_sd->status.max_hp)
						heal = target_sd->status.max_hp - target_sd->status.hp;
					clif_heal(target_sd->fd,SP_HP,heal);
				}
				unit_heal(target,heal,-5*kaahi_lv);
			}
		}
	}

	/* 39D‘¾—z‚ÆŒ‚Æ¯‚ÌŠïÕ */
	if(src_sd && wd.flag&BF_WEAPON && src_sd->s_class.job == PC_JOB_SG && atn_rand()%10000 < battle_config.sg_miracle_rate)
		status_change_start(src,SC_MIRACLE,1,0,0,0,3600000,0);

	/* 40DŒvZŒ‹‰Ê‚ÌÅI•â³ */
	if(!calc_flag.lh)
		wd.damage2 = 0;
	wd.amotion = status_get_amotion(src);
	if(skill_num == KN_AUTOCOUNTER)
		wd.amotion >>= 1;
	wd.dmotion = status_get_dmotion(target);

	return wd;
}

/*==========================================
 * Šî–{•Šíƒ_ƒ[ƒWŒvZ
 *------------------------------------------
 */
int battle_calc_base_magic_damage(struct block_list *src)
{
	int matk1, matk2, damage = 0;
	struct status_change *sc = NULL;
#ifndef PRE_RENEWAL
	struct map_session_data *sd = NULL;
#endif

	nullpo_retr(1, src);

	matk1 = status_get_matk1(src);	// pre:Å‘åMatk, RE:•ŠíMatk
	matk2 = status_get_matk2(src);	// pre:Å’áMatk, RE:ƒXƒe[ƒ^ƒXMatk

	sc = status_get_sc(src);

#ifndef PRE_RENEWAL
	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;

	if(sd) {
		short wlv = 0;
		int cost  = 0;
		int int_  = status_get_int(src);
		int idx   = sd->equip_index[EQUIP_INDEX_RARM];

		damage = matk2;		// ƒXƒe[ƒ^ƒXMatk‚ğŠm•Û

		// •Ší‚ª‚ ‚é‚È‚ç•ŠíLv‚ÆƒRƒXƒgŒvZ
		if(idx >= 0 && sd->inventory_data[idx]) {
			wlv  = sd->inventory_data[idx]->wlv;
			cost = matk1-(int_/5)*(8+wlv);
			if(cost < 0)	// ƒRƒXƒg‚Í0ˆÈ‰º‚É‚È‚ç‚È‚¢
				cost = 0;
		}
		// Å‘å•ŠíMatk‚ÆÅ’á•ŠíMatkŒvZ
		matk1 = matk1 * (100+20*wlv)/100 - cost;
		matk2 = int_/5 * (200+50*wlv)/100 - cost;
		if(matk2 > matk1)
			matk2 = matk1;
	}
#endif

	// ƒŠƒRƒOƒiƒCƒYƒhƒXƒyƒ‹
	if(sc && sc->data[SC_RECOGNIZEDSPELL].timer != -1) {
		matk1 = (matk1 > matk2)? matk1: matk2;
		matk2 = (matk2 > matk1)? matk2: matk1;
	}

#ifdef PRE_RENEWAL
	if(matk1 > matk2)
		damage = matk2+atn_rand()%(matk1-matk2+1);
	else
		damage = matk2;
#else
	// ƒXƒe[ƒ^ƒXMatk+•ŠíMatkŒvZ
	if(matk1 > matk2)
		damage += matk2+atn_rand()%(matk1-matk2+1);
	else
		damage += matk2;
	// ‰ßè¸˜B‚ÌŒvZ
	if(sd && sd->overrefine)
		damage += (atn_rand()%sd->overrefine)+1;
#endif

	if(sc) {
		// –‚–@—Í‘•
		if(sc->data[SC_MAGICPOWER].timer != -1)
			damage += damage * (sc->data[SC_MAGICPOWER].val1 * 5) / 100;
		// Œ–¾‚©‚è‚ÌƒZƒŒƒi[ƒf
		if(sc->data[SC_MOONLIT_SERENADE].timer != -1)
			damage += sc->data[SC_MOONLIT_SERENADE].val4;
	}

	return ((damage>0)?damage:1);
}

#define MATK_FIX( a,b ) { mgd.damage = mgd.damage*(a+(add_rate*b/100))/(b); }

/*==========================================
 * –‚–@ƒ_ƒ[ƒWŒvZ
 *------------------------------------------
 */
static struct Damage battle_calc_magic_attack(struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag)
{
	struct Damage mgd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change    *sc = NULL, *t_sc = NULL;
	int ele, race;
	int mdef1, mdef2, t_ele, t_race, t_group, t_enemy, t_size, t_mode;
	int t_class, cardfix, i;
	int normalmagic_flag = 1;
	int add_rate = 0;
#ifndef PRE_RENEWAL
	int heal;
#endif

	// return‘O‚Ìˆ—‚ª‚ ‚é‚Ì‚Åî•ño—Í•”‚Ì‚İ•ÏX
	if( bl == NULL || target == NULL || target->type == BL_PET ) {
		nullpo_info(NLP_MARK);
		return mgd;
	}

	sd   = BL_DOWNCAST( BL_PC, bl );
	tsd  = BL_DOWNCAST( BL_PC, target );

	// ƒAƒ^ƒbƒJ[
	ele  = skill_get_pl(skill_num);
	race = status_get_race(bl);
	sc   = status_get_sc(bl);

	// ƒ^[ƒQƒbƒg
	mdef1   = status_get_mdef(target);
	mdef2   = status_get_mdef2(target);
	t_ele   = status_get_elem_type(target);
	t_race  = status_get_race(target);
	t_group = status_get_group(target);
	t_enemy = status_get_enemy_type(target);
	t_size  = status_get_size(target);
	t_mode  = status_get_mode(target);
	t_sc    = status_get_sc(target);

	if(sd) {
		sd->state.attack_type = BF_MAGIC;
		sd->state.arrow_atk = 0;
	}

	// ƒLƒ“ƒOƒXƒOƒŒƒCƒX
	if(t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return mgd;

	/* ‚PDmgd\‘¢‘Ì‚Ì‰Šúİ’è */
	mgd.div_      = skill_get_num(skill_num,skill_lv);
	mgd.blewcount = skill_get_blewcount(skill_num,skill_lv);
	mgd.flag      = BF_MAGIC|BF_LONG|BF_SKILL;

	// ‚±‚±‚©‚ç‹——£‚É‚æ‚é”»’è
	switch(skill_get_range_type(skill_num)) {
		case 0:	// ‹ß‹——£
		case 2: // ‹­§‰“‹——£
			break;
		case 1:	// ’Êí‰“‹——£
			if(battle_config.calc_dist_flag & 2) {	// –‚–@‚ÌŒvZ‚·‚é‚©H +2‚ÅŒvZ‚·‚é
				int target_dist = unit_distance(bl,target);	// ‹——£‚ğæ“¾
				if(target_dist < battle_config.allow_sw_dist) {	// SW‚Å–h‚°‚é‹——£‚æ‚è¬‚³‚¢‹ß‹——£‚©‚ç‚ÌUŒ‚
					if(bl->type == BL_PC && battle_config.sw_def_type & 1) {	// lŠÔ‚©‚ç‚Ì‚ğ”»’è‚·‚é‚© +1‚Å‚·‚é
						mgd.flag = (mgd.flag&~BF_RANGEMASK)|BF_SHORT;
						break;
					} else if(bl->type == BL_MOB && battle_config.sw_def_type & 2) {	// ƒ‚ƒ“ƒXƒ^[‚©‚ç‚Ì–‚–@‚ğ”»’è‚·‚é‚© +2‚Å‚·‚é
						mgd.flag = (mgd.flag&~BF_RANGEMASK)|BF_SHORT;
						break;
					}
				}
			}
			break;
	}

	/* ‚QD–‚–@UŒ‚Šî‘bŒvZ */
	mgd.damage = battle_calc_base_magic_damage(bl);

#ifndef PRE_RENEWAL
	// ƒq[ƒ‹‚ÌŒvZ—p‚ÉŠm•Û
	heal = mgd.damage;

	if(sd) {
		mgd.damage += sd->plus_matk;
		// iREjMATKæZˆ—(ñ•â³ˆÈŠO)
		if(sd->matk_rate != 100)
			MATK_FIX( sd->matk_rate, 100 );
	}

	// ƒtƒ@ƒCƒA[ƒsƒ‰[
	if(skill_num == WZ_FIREPILLAR) {
		if(bl->type == BL_MOB) {
			MATK_FIX( 200+100*skill_lv, 100 );
		} else {
			MATK_FIX( 40+20*skill_lv, 100 );
		}
		mgd.damage += 100+50*skill_lv;
	}

	/* iREjƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒW’Ç‰Áˆ— */
	if(sd && mgd.damage > 0) {
		cardfix = 100;
		if(tsd)
			cardfix = cardfix*(100+sd->magic_addrace[t_race]+sd->magic_addrace[RCT_PLAYER])/100;
		else
			cardfix = cardfix*(100+sd->magic_addrace[t_race])/100;
		cardfix = cardfix*(100+sd->magic_addele[t_ele])/100;
		cardfix = cardfix*(100+sd->magic_addenemy[t_enemy])/100;
		cardfix = cardfix*(100+sd->magic_addsize[t_size])/100;
		if(t_mode & MD_BOSS)
			cardfix = cardfix*(100+sd->magic_addrace[RCT_BOSS])/100;
		else
			cardfix = cardfix*(100+sd->magic_addrace[RCT_NONBOSS])/100;
		cardfix = cardfix*(100+sd->magic_addgroup[t_group])/100;
		t_class = status_get_class(target);
		for(i=0; i<sd->add_magic_damage_class_count; i++) {
			if(sd->add_magic_damage_classid[i] == t_class) {
				cardfix = cardfix*(100+sd->add_magic_damage_classrate[i])/100;
				break;
			}
		}
		mgd.damage = mgd.damage*cardfix/100;
	}
#endif

	/* ƒXƒLƒ‹”{—¦ŒvZ‚É‰ÁZ */
	if(sc) {
#ifndef PRE_RENEWAL
		if(sc->data[SC_MINDBREAKER].timer != -1) {
			add_rate += 20*sc->data[SC_MINDBREAKER].val1;
		}
#endif
	}

	/* ‚RDŠî–{ƒ_ƒ[ƒWŒvZ(ƒXƒLƒ‹‚²‚Æ‚Éˆ—) */
	switch(skill_num)
	{
		case AL_HEAL:	// ƒq[ƒ‹or¹‘Ì
		case PR_BENEDICTIO:
#ifdef PRE_RENEWAL
			mgd.damage = skill_calc_heal(bl,skill_lv)/2;
#else
			mgd.damage = skill_calc_heal(bl,skill_lv);
#endif
			if(sd) {	// ŒüãŒø‰Ê‚ğæ‚¹‚é
				int rate = 0;
#ifndef PRE_RENEWAL
				if(sd->skill_dmgup.count > 0) {
					for(i=0; i<sd->skill_dmgup.count; i++) {
						if(skill_num == sd->skill_dmgup.id[i]) {
							rate += sd->skill_dmgup.rate[i];
							break;
						}
					}
				}
#endif
				rate += pc_checkskill(sd,HP_MEDITATIO)*2;
				mgd.damage += mgd.damage * rate / 100;
			}
#ifndef PRE_RENEWAL
			mgd.damage += heal;	// Matk‚Ì‰ÁZ
			mgd.damage = mgd.damage / 2;
#endif
			normalmagic_flag = 0;
			break;
		case PR_ASPERSIO:		// ƒAƒXƒyƒ‹ƒVƒI
			mgd.damage = 40;	// ŒÅ’èƒ_ƒ[ƒW
			normalmagic_flag = 0;
			break;
		case PR_SANCTUARY:	// ƒTƒ“ƒNƒ`ƒ…ƒAƒŠ
			ele = ELE_HOLY;
			mgd.damage = (skill_lv > 6)? 388: 50*skill_lv;
#ifndef PRE_RENEWAL
			if(sd && sd->skill_dmgup.count > 0) {	// ŒüãŒø‰Ê‚ğæ‚¹‚é
				for(i=0; i<sd->skill_dmgup.count; i++) {
					if(skill_num == sd->skill_dmgup.id[i]) {
						mgd.damage += mgd.damage * sd->skill_dmgup.rate[i] / 100;
						break;
					}
				}
			}
#endif
			normalmagic_flag = 0;
			mgd.blewcount |= SAB_REVERSEBLOW;
			break;
		case PA_GOSPEL:		// ƒSƒXƒyƒ‹(ƒ‰ƒ“ƒ_ƒ€ƒ_ƒ[ƒW”»’è‚Ìê‡)
			mgd.damage = 1000+atn_rand()%9000;
			normalmagic_flag = 0;
			break;
		case ALL_RESURRECTION:
		case PR_TURNUNDEAD:	// UŒ‚ƒŠƒUƒŒƒNƒVƒ‡ƒ“‚Æƒ^[ƒ“ƒAƒ“ƒfƒbƒh
			if(battle_check_undead(t_race,t_ele)) {
				int hp, mhp, thres;
				hp = status_get_hp(target);
				mhp = status_get_max_hp(target);
				thres = skill_lv * 20 + status_get_luk(bl) + status_get_int(bl) + status_get_lv(bl) + 200 - (hp * 200 / mhp);
				if(thres > 700)
					thres = 700;
				if(atn_rand()%1000 < thres && !(t_mode&MD_BOSS))	// ¬Œ÷
					mgd.damage = hp;
				else					// ¸”s
					mgd.damage = status_get_lv(bl) + status_get_int(bl) + skill_lv * 10;
			}
			normalmagic_flag = 0;
			break;
		case AL_INCAGI:			/* ‘¬“x‘‰Á */
		case MER_INCAGI:
		case AL_BLESSING:		/* ƒuƒŒƒbƒVƒ“ƒO */
		case MER_BLESSING:
			mgd.damage = 1;
			normalmagic_flag = 0;
			break;

		case HW_NAPALMVULCAN:	// ƒiƒp[ƒ€ƒoƒ‹ƒJƒ“
		case MG_NAPALMBEAT:	// ƒiƒp[ƒ€ƒr[ƒgi•ªUŒvZ‚İj
			MATK_FIX( 70+10*skill_lv, 100 );
			if(flag > 0) {
				MATK_FIX( 1, flag );
			} else {
				if(battle_config.error_log)
					printf("battle_calc_magic_attack: NAPALM enemy count=0 !\n");
			}
			break;
		case MG_SOULSTRIKE:			// ƒ\ƒEƒ‹ƒXƒgƒ‰ƒCƒNi‘ÎƒAƒ“ƒfƒbƒhƒ_ƒ[ƒW•â³j
			if(battle_check_undead(t_race,t_ele))
				MATK_FIX( 20+skill_lv, 20 );	// MATK‚É•â³‚¶‚á‘Ê–Ú‚Å‚·‚©‚ËH
			break;
		case MG_COLDBOLT:	// ƒR[ƒ‹ƒhƒ{ƒ‹ƒg
			if(sc && sc->data[SC_AQUAPLAY].timer != -1) {
				MATK_FIX( 100+sc->data[SC_AQUAPLAY].val3, 100 );
			}
			break;
		case MG_FROSTDIVER:	// ƒtƒƒXƒgƒ_ƒCƒo[
			if(sc && sc->data[SC_AQUAPLAY].timer != -1) {
				MATK_FIX( 100+10*skill_lv+sc->data[SC_AQUAPLAY].val3, 100 );
			} else {
				MATK_FIX( 100+10*skill_lv, 100 );
			}
			break;
		case MG_FIREBALL:	// ƒtƒ@ƒCƒA[ƒ{[ƒ‹
			if(flag > 2) {
				mgd.damage = 0;
			} else {
				if(bl->type == BL_MOB && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
					MATK_FIX( 1000, 100 );
				} else {
#ifdef PRE_RENEWAL
					MATK_FIX( 70+10*skill_lv, 100 );
#else
					MATK_FIX( 140+20*skill_lv, 100 );
#endif
				}
				if(flag == 2)
					MATK_FIX( 3, 4 );
			}
			break;
		case MG_FIREWALL:	// ƒtƒ@ƒCƒA[ƒEƒH[ƒ‹
			if((t_ele == ELE_FIRE || battle_check_undead(t_race,t_ele)) && target->type != BL_PC)
				mgd.blewcount = 0;
			else
				mgd.blewcount |= SAB_REVERSEBLOW;
			if(sc && sc->data[SC_PYROTECHNIC].timer != -1) {
				MATK_FIX( 50+sc->data[SC_PYROTECHNIC].val3, 100 );
			} else {
				MATK_FIX( 50, 100 );
			}
			break;
		case MG_FIREBOLT:	// ƒtƒ@ƒCƒA[ƒ{ƒ‹ƒg
			if(sc && sc->data[SC_PYROTECHNIC].timer != -1) {
				MATK_FIX( 100+sc->data[SC_PYROTECHNIC].val3, 100 );
			}
			break;
		case MG_LIGHTNINGBOLT:	// ƒ‰ƒCƒgƒjƒ“ƒOƒ{ƒ‹ƒg
			if(sc && sc->data[SC_GUST].timer != -1) {
				MATK_FIX( 100+sc->data[SC_GUST].val3, 100 );
			}
			break;
		case MG_THUNDERSTORM:	// ƒTƒ“ƒ_[ƒXƒg[ƒ€
#ifdef PRE_RENEWAL
			if(sc && sc->data[SC_GUST].timer != -1) {
				MATK_FIX( 80+sc->data[SC_GUST].val3, 100 );
			} else {
				MATK_FIX( 80, 100 );
			}
#else
			if(sc && sc->data[SC_GUST].timer != -1) {
				MATK_FIX( 100+sc->data[SC_GUST].val3, 100 );
			}
#endif
			break;
		case WZ_FROSTNOVA:	// ƒtƒƒXƒgƒmƒ”ƒ@
#ifdef PRE_RENEWAL
			MATK_FIX( 200+20*skill_lv, 300 );
#else
			MATK_FIX( 100+10*skill_lv, 100 );
#endif
			break;
#ifdef PRE_RENEWAL
		case WZ_FIREPILLAR:	// ƒtƒ@ƒCƒA[ƒsƒ‰[
			if(mdef1 < 1000000)
				mdef1 = mdef2 = 0;	// MDEF–³‹
			if(bl->type == BL_MOB) {
				MATK_FIX( 200+100*skill_lv, 100 );
			} else {
				MATK_FIX( 40+20*skill_lv, 100 );
			}
			mgd.damage += 50;
			break;
#endif
		case WZ_SIGHTRASHER:
			if(bl->type == BL_MOB && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
				MATK_FIX( 1000, 100 );
			} else {
				MATK_FIX( 100+20*skill_lv, 100 );
			}
			break;
		case WZ_METEOR:
#ifndef PRE_RENEWAL
			MATK_FIX( 125, 100 );
			break;
#endif
		case NPC_DARKTHUNDER:	// ƒ_[ƒNƒTƒ“ƒ_[
			break;
		case WZ_JUPITEL:	// ƒ†ƒsƒeƒ‹ƒTƒ“ƒ_[
			if(bl->type == BL_MOB && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
				mgd.div_ = 30;
				mgd.blewcount = 14;
			}
			break;
		case WZ_VERMILION:	// ƒ[ƒhƒIƒuƒ”ƒ@[ƒ~ƒŠƒIƒ“
#ifdef PRE_RENEWAL
			MATK_FIX( 80+20*skill_lv, 100 );
#else
			MATK_FIX( 100+((skill_lv-1)*25)*skill_lv/10+(skill_lv >= 10? 5: 0), 100 );
#endif
			break;
		case WZ_WATERBALL:	// ƒEƒH[ƒ^[ƒ{[ƒ‹
			MATK_FIX( 100+30*skill_lv, 100 );
			break;
		case WZ_STORMGUST:	// ƒXƒg[ƒ€ƒKƒXƒg
#ifdef PRE_RENEWAL
			MATK_FIX( 100+40*skill_lv, 100 );
#else
			MATK_FIX( 70+50*skill_lv, 100 );
#endif
			//mgd.blewcount |= SAB_REVERSEBLOW;
			break;
		case WZ_EARTHSPIKE:	// ƒA[ƒXƒXƒpƒCƒN
			if(sc && sc->data[SC_PETROLOGY].timer != -1) {
				MATK_FIX( 100+sc->data[SC_PETROLOGY].val3, 100 );
			}
			break;
		case WZ_HEAVENDRIVE:	// ƒwƒ”ƒ“ƒYƒhƒ‰ƒCƒu
#ifdef PRE_RENEWAL
			if(sc && sc->data[SC_PETROLOGY].timer != -1) {
				MATK_FIX( 100+sc->data[SC_PETROLOGY].val3, 100 );
			}
#else
			if(sc && sc->data[SC_PETROLOGY].timer != -1) {
				MATK_FIX( 125+sc->data[SC_PETROLOGY].val3, 100 );
			} else {
				MATK_FIX( 125, 100 );
			}
#endif
			break;
		case AL_HOLYLIGHT:	// ƒz[ƒŠ[ƒ‰ƒCƒg
			MATK_FIX( 125, 100 );
			if(sc && sc->data[SC_PRIEST].timer != -1) {
				MATK_FIX( 500, 100 );
			}
			break;
		case AL_RUWACH:
			MATK_FIX( 145, 100 );
			break;
#ifndef PRE_RENEWAL
		case CR_GRANDCROSS:	// ƒOƒ‰ƒ“ƒhƒNƒƒX
		case NPC_GRANDDARKNESS:
			{
				static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
				if(bl == target)
					mgd.damage /= 2;	// ”½“®‚Í”¼•ª
				mgd.damage = (mgd.damage + wd.damage) / 2 * (100 + 40*skill_lv)/100;
				mgd.damage = mgd.damage - (mdef1 + mdef2 + status_get_def(target) + status_get_def2(target));
				if(bl == target) {
					if(bl->type & (BL_MOB | BL_HOM | BL_MERC | BL_ELEM))
						mgd.damage = 0;		// MOB,HOM,MERC,ELEM‚ªg‚¤ê‡‚Í”½“®–³‚µ
				} else {
//					if(battle_config.gx_dupele)
						mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));	// ‘®«2‰ñ‚©‚©‚é
					if(sd)
						mgd.damage = mgd.damage * (100+sd->long_weapon_damege_rate) / 100;
				}
				normalmagic_flag = 0;
			}
			break;
		case AM_DEMONSTRATION:	// ƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case AM_ACIDTERROR:	// ƒAƒVƒbƒhƒeƒ‰[
		case ASC_BREAKER:	// ƒ\ƒEƒ‹ƒuƒŒƒCƒJ[
		case CR_ACIDDEMONSTRATION:	// ƒAƒVƒbƒhƒfƒ‚ƒ“ƒXƒgƒŒ[ƒVƒ‡ƒ“
		case GN_FIRE_EXPANSION_ACID:	// ƒtƒ@ƒCƒA[ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“(‰–_)
			ele = ELE_NONE;
			normalmagic_flag = 0;
			break;
#endif
		case SL_STIN:	// ƒGƒXƒeƒBƒ“
			if(status_get_size(target) == 0) {
				MATK_FIX( 10*skill_lv, 100 );
			} else {
				MATK_FIX( skill_lv, 100 );
			}
			if(skill_lv >= 7)
				status_change_start(bl,SC_SMA,skill_lv,0,0,0,3000,0);
			break;
		case SL_STUN:	// ƒGƒXƒ^ƒ“
			MATK_FIX( 5*skill_lv, 100 );
			ele = status_get_attack_element(bl);
			if(skill_lv >= 7)
				status_change_start(bl,SC_SMA,skill_lv,0,0,0,3000,0);
			break;
		case SL_SMA:	// ƒGƒXƒ}
			MATK_FIX( 40+status_get_lv(bl), 100 );
			ele = status_get_attack_element_nw(bl);
			if(sc && sc->data[SC_SMA].timer != -1)
				status_change_end(bl,SC_SMA,-1);
			break;
		case NJ_KOUENKA:	// g‰Š‰Ø
			{
				int rate = 90;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 20;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_KAENSIN:	// ‰Î‰Šw
			{
				int rate = 50;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 10;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_HUUJIN:		// •—n
			{
#ifdef PRE_RENEWAL
				int rate = 100;
#else
				int rate = 150;
#endif
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WIND)
					rate += sd->elementball.num * 20;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_HYOUSENSOU:	// •X‘M‘„
			{
				int rate = 70;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WATER)
					rate += sd->elementball.num * 5;
				if(t_sc && t_sc->data[SC_SUITON].timer != -1)
					rate += 2 * t_sc->data[SC_SUITON].val1;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_BAKUENRYU:	// —´‰Šw
			{
				int rate = 150 + 150 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 15;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_HYOUSYOURAKU:	// •X’Œ—‚µ
			{
				int rate = 100 + 50 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WATER)
					rate += sd->elementball.num * 25;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_RAIGEKISAI:	// —‹Œ‚Ó
			{
				int rate = 160 + 40 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WIND)
					rate += sd->elementball.num * 15;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_KAMAITACHI:	// ñ•—
			{
				int rate = 100 + 100 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WIND)
					rate += sd->elementball.num * 10;
				MATK_FIX( rate, 100 );
			}
			break;
		case NPC_EARTHQUAKE:	// ƒA[ƒXƒNƒGƒCƒN
			{
				static const int dmg[10] = { 300, 500, 600, 800, 1000, 1200, 1300, 1500, 1600, 1800 };
				int matk1 = status_get_atk(bl);
				int matk2 = status_get_atk2(bl);

				if(matk2 > matk1)
					mgd.damage = matk1+atn_rand()%(matk2-matk1+1);
				else
					mgd.damage = matk1;
				if(mdef1 < 1000000)
					mdef1 = mdef2 = 0;	// MDEF–³‹
				if(skill_lv <= sizeof(dmg)/sizeof(dmg[0])) {
					MATK_FIX( dmg[skill_lv-1], 100 );
				} else {
					MATK_FIX( 100 + 200 * skill_lv, 100 );
				}
				if(flag > 1) {
					MATK_FIX( 1, flag );
				}
			}
			break;
		case NPC_EVILLAND:	// ƒC[ƒrƒ‹ƒ‰ƒ“ƒh
			mgd.damage = (skill_lv > 6)? 666: skill_lv*100;
			normalmagic_flag = 0;
			break;
		case NPC_PULSESTRIKE2:	// ƒpƒ‹ƒXƒXƒgƒ‰ƒCƒNII
			mgd.damage = status_get_matk1(bl);
			normalmagic_flag = 0;
			break;
		case NPC_FLAMECROSS:	// ƒtƒŒƒCƒ€ƒNƒƒX
			if((t_ele == ELE_FIRE || battle_check_undead(t_race,t_ele)) && target->type != BL_PC)
				mgd.blewcount = 0;
			else
				mgd.blewcount |= SAB_REVERSEBLOW;
			break;
		case RK_ENCHANTBLADE:	// ƒGƒ“ƒ`ƒƒƒ“ƒgƒuƒŒƒCƒh
			if(sc && sc->data[SC_ENCHANTBLADE].timer != -1) {
				mgd.damage += sc->data[SC_ENCHANTBLADE].val2;
			}
			break;
		case AB_HIGHNESSHEAL:	// ƒnƒCƒlƒXƒq[ƒ‹
			mgd.damage = skill_calc_heal(bl,10);
			if(sd) {	// ŒüãŒø‰Ê‚ğæ‚¹‚é
				int rate = 0;
#ifndef PRE_RENEWAL
				if(sd->skill_dmgup.count > 0) {
					for(i=0; i<sd->skill_dmgup.count; i++) {
						if(skill_num == sd->skill_dmgup.id[i]) {
							rate += sd->skill_dmgup.rate[i];
							break;
						}
					}
				}
#endif
				rate += pc_checkskill(sd,HP_MEDITATIO)*2;
				mgd.damage += mgd.damage * rate / 100;
			}
#ifndef PRE_RENEWAL
			mgd.damage += heal;	// Matk‚Ì‰ÁZ
#endif
			mgd.damage = mgd.damage * (170 + 30 * skill_lv) / 100;
			mgd.damage = mgd.damage / 2;
			normalmagic_flag = 0;
			break;
		case AB_JUDEX:		// ƒWƒ…ƒfƒbƒNƒX
			MATK_FIX( (450 + 30 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case AB_ADORAMUS:	// ƒAƒhƒ‰ƒ€ƒX
			MATK_FIX( (500 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case AB_EPICLESIS:	// ƒGƒsƒNƒŒƒVƒX
			ele = ELE_HOLY;
			mgd.damage = (skill_lv > 6)? 388: 50*skill_lv;
			normalmagic_flag = 0;
			break;
		case AB_DUPLELIGHT_MAGIC:	// ƒfƒ…ƒvƒŒƒ‰ƒCƒg(–‚–@)
			MATK_FIX( 200 + 20 * skill_lv, 100 );
			break;
		case WL_SOULEXPANSION:		// ƒ\ƒEƒ‹ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“
			MATK_FIX( (status_get_int(bl) + 400 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_FROSTMISTY:	// ƒtƒƒXƒgƒ~ƒXƒeƒB
			MATK_FIX( (200 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_JACKFROST:	// ƒWƒƒƒbƒNƒtƒƒXƒg
			if(t_sc && t_sc->data[SC_FROSTMISTY].timer != -1) {
				MATK_FIX( (1000 + 300 * skill_lv) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (500 + 100 * skill_lv) * status_get_lv(bl) / 150, 100 );
			}
			break;
		case WL_DRAINLIFE:	// ƒhƒŒƒCƒ“ƒ‰ƒCƒt
			MATK_FIX( (status_get_int(bl) + 200 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_CRIMSONROCK:	// ƒNƒŠƒ€ƒ]ƒ“ƒƒbƒN
			MATK_FIX( 1300 + (300 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_HELLINFERNO:	// ƒwƒ‹ƒCƒ“ƒtƒFƒ‹ƒm
			if(flag) {	// ˆÅ‘®«
				ele = ELE_DARK;
				MATK_FIX( 240 * skill_lv * status_get_lv(bl) / 100, 100 );
			} else {	// ‰Î‘®«
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100, 100 );
			}
			break;
		case WL_COMET:	// ƒRƒƒbƒg
			if(flag == 3) {			// ‰“‹——£
				MATK_FIX( 800 + 200 * skill_lv, 100 );
			} else if(flag == 2) {		// ’†‹——£
				MATK_FIX( 1200 + 300 * skill_lv, 100 );
			} else if(flag == 1) {		// ‹ß‹——£
				MATK_FIX( 1600 + 400 * skill_lv, 100 );
			} else {		// ’†S
				MATK_FIX( 2500 + 500 * skill_lv, 100 );
			}
			break;
		case WL_CHAINLIGHTNING:		// ƒ`ƒF[ƒ“ƒ‰ƒCƒgƒjƒ“ƒO
		case WL_CHAINLIGHTNING_ATK:	// ƒ`ƒF[ƒ“ƒ‰ƒCƒgƒjƒ“ƒO(˜A½)
			// TODO: -100*˜A½‰ñ”
			MATK_FIX( (300 + 100 * skill_lv) + (500 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_EARTHSTRAIN:	// ƒA[ƒXƒXƒgƒŒƒCƒ“
			MATK_FIX( (2000 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_TETRAVORTEX_FIRE:		/* ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(‰Î) */
		case WL_TETRAVORTEX_WATER:		/* ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(…) */
		case WL_TETRAVORTEX_WIND:		/* ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(•—) */
		case WL_TETRAVORTEX_GROUND:		/* ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(’n) */
			MATK_FIX( 500 + 500 * skill_lv, 100 );
			break;
		case WL_SUMMON_ATK_FIRE:		/* ƒTƒ‚ƒ“ƒtƒ@ƒCƒAƒ{[ƒ‹(UŒ‚) */
		case WL_SUMMON_ATK_WIND:		/* ƒTƒ‚ƒ“ƒ{[ƒ‹ƒ‰ƒCƒgƒjƒ“ƒO(UŒ‚) */
		case WL_SUMMON_ATK_WATER:		/* ƒTƒ‚ƒ“ƒEƒH[ƒ^[ƒ{[ƒ‹(UŒ‚) */
		case WL_SUMMON_ATK_GROUND:		/* ƒTƒ‚ƒ“ƒXƒg[ƒ“(UŒ‚) */
			MATK_FIX( (status_get_lv(bl) + status_get_jlv(bl)) * (1 + skill_lv / 2) * status_get_lv(bl) / 100, 100 );
			break;
		case LG_SHIELDSPELL:	// ƒV[ƒ‹ƒhƒXƒyƒ‹
			if(sd) {
				int idx = sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && sd->inventory_data[idx] && itemdb_isarmor(sd->inventory_data[idx]->nameid)) {
					MATK_FIX( status_get_lv(bl) * 4 + sd->inventory_data[idx]->mdef * 100 + status_get_int(bl) * 2, 100 );
				}
			}
			else {
				MATK_FIX( status_get_lv(bl) * 4 + status_get_int(bl) * 2, 100 );
			}
			break;
		case LG_RAYOFGENESIS:			/* ƒŒƒCƒIƒuƒWƒFƒlƒVƒX */
			if(sc && sc->data[SC_BANDING].timer != -1) {
				MATK_FIX( (300 * skill_lv + sc->data[SC_BANDING].val2 * 200) * status_get_jlv(bl) / 25, 100 );
			} else {
				MATK_FIX( (300 * skill_lv + 200) * status_get_jlv(bl) / 25, 100 );
			}
			break;
		case WM_METALICSOUND:	/* ƒƒ^ƒŠƒbƒNƒTƒEƒ“ƒh */
			if(t_sc && (t_sc->data[SC_SLEEP].timer != -1 || t_sc->data[SC_DEEP_SLEEP].timer != -1)) {
				MATK_FIX( ( ( 120 * skill_lv ) + ( (sd)? pc_checkskill(sd,WM_LESSON): 0 ) * 60 ) * status_get_lv(bl) / 100 * 2, 100 );
			}
			else {
				MATK_FIX( ( ( 120 * skill_lv ) + ( (sd)? pc_checkskill(sd,WM_LESSON): 0 ) * 60 ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case WM_REVERBERATION_MAGIC:	/* U“®c‹¿(–‚–@) */
			MATK_FIX( (100 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			if(flag > 1) {
				MATK_FIX( 1, flag );
			}
			break;
		case SO_FIREWALK:		/* ƒtƒ@ƒCƒA[ƒEƒH[ƒN */
			if(sc && sc->data[SC_HEATER].timer != -1) {
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100 + sc->data[SC_HEATER].val3, 100 );
			} else {
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_ELECTRICWALK:	/* ƒGƒŒƒNƒgƒŠƒbƒNƒEƒH[ƒN */
			if(sc && sc->data[SC_BLAST].timer != -1) {
				MATK_FIX( 90 * skill_lv + sc->data[SC_BLAST].val3, 100 );
			} else {
				MATK_FIX( 90 * skill_lv, 100 );
			}
			break;
		case SO_EARTHGRAVE:		/* ƒA[ƒXƒOƒŒƒCƒu */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_SEISMICWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_SEISMICWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_DIAMONDDUST:	/* ƒ_ƒCƒ„ƒ‚ƒ“ƒhƒ_ƒXƒg */
			if(sc && sc->data[SC_COOLER].timer != -1) {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_FROSTWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100 + sc->data[SC_COOLER].val3, 100 );
			} else {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_FROSTWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_POISON_BUSTER:	/* ƒ|ƒCƒYƒ“ƒoƒXƒ^[ */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( 1250 * status_get_lv(bl) / 150 + 250 * skill_lv * status_get_lv(bl) / 100 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( 1250 * status_get_lv(bl) / 150 + 250 * skill_lv * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_PSYCHIC_WAVE:	/* ƒTƒCƒLƒbƒNƒEƒF[ƒu */
			{
				int rate = 0;
				if(sc) {
					if(sc->data[SC_HEATER].timer != -1) {
						ele = ELE_FIRE;
						rate = sc->data[SC_HEATER].val3;
					} else if(sc->data[SC_COOLER].timer != -1) {
						ele = ELE_WATER;
						rate = sc->data[SC_COOLER].val3;
					} else if(sc->data[SC_BLAST].timer != -1) {
						ele = ELE_WIND;
						rate = sc->data[SC_BLAST].val3;
					} else if(sc->data[SC_CURSED_SOIL].timer != -1) {
						ele = ELE_EARTH;
						rate = sc->data[SC_CURSED_SOIL].val3;
					}
				}
				MATK_FIX( ( 70 * skill_lv + status_get_int(bl) * 3 ) * status_get_lv(bl) / 100 + rate, 100 );
			}
			break;
		case SO_CLOUD_KILL:		/* ƒNƒ‰ƒEƒhƒLƒ‹ */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( ( 40 * skill_lv ) * status_get_lv(bl) / 100 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( ( 40 * skill_lv ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_VARETYR_SPEAR:	/* ƒ”ƒFƒ‰ƒ`ƒ…[ƒ‹ƒXƒsƒA */
			if(sc && sc->data[SC_BLAST].timer != -1) {
				MATK_FIX( ( 50 * ( (sd)? pc_checkskill(sd,SA_LIGHTNINGLOADER): 1 ) + status_get_int(bl) * skill_lv) * status_get_lv(bl) / 100 + sc->data[SC_BLAST].val3, 100 );
			} else {
				MATK_FIX( ( 50 * ( (sd)? pc_checkskill(sd,SA_LIGHTNINGLOADER): 1 ) + status_get_int(bl) * skill_lv) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case GN_DEMONIC_FIRE:	// ƒfƒ‚ƒjƒbƒNƒtƒ@ƒCƒA[
			if(flag == 1) {		// –û
				MATK_FIX( (200 * skill_lv) + status_get_jlv(bl) + status_get_int(bl), 100 );
			} else if(flag == 2) {	// ”š”­
				MATK_FIX( 200 * skill_lv + status_get_int(bl) * 10, 100 );
			} else {
				MATK_FIX( 200 * skill_lv, 100 );
			}
			break;
		case KO_KAIHOU:	/* p® -‰ğ•ú- */
			MATK_FIX( 200 * status_get_lv(bl) / 100, 100 );
			if(sd) {
				// ¢Š«’†‚Ì‹…‘Ì‚Ì‘®«‚ğ“K—p‚·‚é
				ele = sd->elementball.ele;
				// ¢Š«’†‚Ì‹…‘Ì‚Ì”‚É‰‚¶‚ÄHIT‚ª•Ï‰»‚·‚é
				mgd.div_ = sd->elementball.num;
			} else {
				mgd.div_ = 10;
			}
			break;
		case SU_SV_STEMSPEAR:	/* ƒ}ƒ^ƒ^ƒrƒ‰ƒ“ƒX */
			{
				const int ele_type[5] = { ELE_GHOST, ELE_WATER, ELE_WIND, ELE_EARTH, ELE_FIRE };
				if(skill_lv <= 5)
					ele = ele_type[skill_lv-1];
				MATK_FIX( 5000, 100 );
			}
			break;
		case SU_CN_METEOR:	/* ƒCƒkƒnƒbƒJƒƒeƒI */
			MATK_FIX( 700, 100 );
			break;
		case EL_FIRE_MANTLE:	/* ƒtƒ@ƒCƒA[ƒ}ƒ“ƒgƒ‹ */
			if((t_ele == ELE_FIRE || battle_check_undead(t_race,t_ele)) && target->type != BL_PC)
				mgd.blewcount = 0;
			else
				mgd.blewcount |= SAB_REVERSEBLOW;
			MATK_FIX( 1000, 100 );
			break;
		case EL_FIRE_ARROW:		/* ƒtƒ@ƒCƒA[ƒAƒ[ */
			MATK_FIX( 300, 100 );
			break;
		case EL_FIRE_BOMB:		/* ƒtƒ@ƒCƒA[ƒ{ƒ€ */
			MATK_FIX( 500, 100 );
			break;
		case EL_FIRE_WAVE:		/* ƒtƒ@ƒCƒA[ƒEƒF[ƒu */
			MATK_FIX( 1200, 100 );
			break;
		case EL_WATER_SCREW:	/* ƒEƒH[ƒ^[ƒXƒNƒŠƒ…[ */
			MATK_FIX( 1000, 100 );
			break;
		case EL_HURRICANE_ATK:	/* ƒnƒŠƒP[ƒ“ƒŒƒCƒW(UŒ‚) */
			MATK_FIX( 500, 100 );
			break;
		case EL_TYPOON_MIS_ATK:	/* ƒ^ƒCƒt[ƒ“ƒ~ƒTƒCƒ‹(UŒ‚) */
			MATK_FIX( 1200, 100 );
			break;
		case EL_ROCK_CRUSHER_ATK:	/* ƒƒbƒNƒ‰ƒ“ƒ`ƒƒ[(UŒ‚) */
			MATK_FIX( 300, 100 );
			break;
	}

	/* ‚SDˆê”Ê–‚–@ƒ_ƒ[ƒWŒvZ */
	if(normalmagic_flag) {
		int rate = 100;
		if(sd) {
			rate = rate - sd->ignore_mdef_ele[t_ele] - sd->ignore_mdef_race[t_race] - sd->ignore_mdef_enemy[t_enemy];
			if(tsd)
				rate -= sd->ignore_mdef_race[RCT_PLAYER];
			if(t_mode & MD_BOSS)
				rate -= sd->ignore_mdef_race[RCT_BOSS];
			else
				rate -= sd->ignore_mdef_race[RCT_NONBOSS];
		}
		if(rate > 0) {
			mdef1 = mdef1 * rate / 100;
			mdef2 = mdef2 * rate / 100;

#ifdef PRE_RENEWAL
			// —öl‚½‚¿‚Ìˆ×‚ÌƒVƒ“ƒtƒHƒj[
			if(t_sc && t_sc->data[SC_SYMPHONY_LOVE].timer != -1) {
				// ÀÛ‚É‚ÍœZMDEF‘‰Á‚¾‚ªAb’è‚ÅŒ¸ZMDEF
				mdef2 += mdef2 * t_sc->data[SC_SYMPHONY_LOVE].val4 / 100;
			}
#else
			if(t_sc) {
				short reduce = 100;
				// ƒAƒXƒ€ƒvƒeƒBƒI
				if(t_sc->data[SC_ASSUMPTIO].timer != -1) {
					if(map[target->m].flag.pvp || map[target->m].flag.gvg)
						reduce += 35;	// ƒV[ƒY‚Í35%
					else
						reduce += 100;	// ‚»‚êˆÈŠO‚Í100%
				}
				// —öl‚½‚¿‚Ìˆ×‚ÌƒVƒ“ƒtƒHƒj[
				if(t_sc->data[SC_SYMPHONY_LOVE].timer != -1) {
					reduce += t_sc->data[SC_SYMPHONY_LOVE].val4;
				}
				// œZMDEFŠÑ’Ê‚Ì“ÁêŒvZ€”õ
				if(skill_num == MG_NAPALMBEAT || skill_num == WZ_FIREPILLAR || skill_num == HW_NAPALMVULCAN || skill_num == SO_VARETYR_SPEAR)
					mdef2 = (mdef1 + mdef2) * reduce / 100;
				else
					mdef1 = mdef1 * reduce / 100;
			}
#endif

			if(battle_config.magic_defense_type) {
				mgd.damage = mgd.damage - (mdef1 * battle_config.magic_defense_type) - mdef2;
			} else {
#ifdef PRE_RENEWAL
				mgd.damage = (mgd.damage*(100-mdef1))/100 - mdef2;
#else
				if(skill_num == RK_ENCHANTBLADE) {
					// ƒGƒ“ƒ`ƒƒƒ“ƒgƒuƒŒƒCƒh‚ÍœZMDEF‚ğŒ¸Zˆ—‚³‚¹‚é
					mgd.damage = mgd.damage - mdef1;
				} else if(skill_num != MG_NAPALMBEAT && skill_num != WZ_FIREPILLAR && skill_num != HW_NAPALMVULCAN && skill_num != SO_VARETYR_SPEAR){
					// ƒiƒp[ƒ€ƒr[ƒg,ƒiƒp[ƒ€ƒoƒ‹ƒJƒ“,ƒtƒ@ƒCƒA[ƒsƒ‰[,ƒ”ƒFƒ‰ƒ`ƒ…[ƒ‹ƒXƒsƒA‚ÍœZMDEFŠÑ’Ê
					mgd.damage = (mgd.damage*(1000+mdef1))/(1000+mdef1*10);
				}
#endif
			}
		}
		if(mgd.damage < 1)	// ƒvƒŒƒCƒ„[‚Ì–‚–@ƒXƒLƒ‹‚Í1ƒ_ƒ[ƒW•ÛØ–³‚µ
			mgd.damage = (!battle_config.skill_min_damage && bl->type == BL_PC)? 0: 1;
	}

#ifdef PRE_RENEWAL
	/* ‚TDƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒW’Ç‰Áˆ— */
	if(sd && mgd.damage > 0) {
		cardfix = 100;
		if(tsd)
			cardfix = cardfix*(100+sd->magic_addrace[t_race]+sd->magic_addrace[RCT_PLAYER])/100;
		else
			cardfix = cardfix*(100+sd->magic_addrace[t_race])/100;
		cardfix = cardfix*(100+sd->magic_addele[t_ele])/100;
		cardfix = cardfix*(100+sd->magic_addenemy[t_enemy])/100;
		cardfix = cardfix*(100+sd->magic_addsize[t_size])/100;
		if(t_mode & MD_BOSS)
			cardfix = cardfix*(100+sd->magic_addrace[RCT_BOSS])/100;
		else
			cardfix = cardfix*(100+sd->magic_addrace[RCT_NONBOSS])/100;
		cardfix = cardfix*(100+sd->magic_addgroup[t_group])/100;
		t_class = status_get_class(target);
		for(i=0; i<sd->add_magic_damage_class_count; i++) {
			if(sd->add_magic_damage_classid[i] == t_class) {
				cardfix = cardfix*(100+sd->add_magic_damage_classrate[i])/100;
				break;
			}
		}
		if(skill_num > 0 && mgd.damage > 0) {
			int rate = 100;

			// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i–‚–@ƒXƒLƒ‹j
			if(sd->skill_dmgup.count > 0) {
				for(i=0; i<sd->skill_dmgup.count; i++) {
					if(skill_num == sd->skill_dmgup.id[i]) {
						rate += sd->skill_dmgup.rate[i];
						break;
					}
				}
			}
			// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’è‘®«ƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i–‚–@ƒXƒLƒ‹j
			rate += sd->skill_elemagic_dmgup[ele];
			cardfix = cardfix*rate/100;
		}
		mgd.damage = mgd.damage*cardfix/100;
	}
#endif

	/* ‚UDƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒWŒ¸Šˆ— */
	if(tsd && mgd.damage > 0) {
		int s_class = status_get_class(bl);
		cardfix = 100;
		cardfix = cardfix*(100-tsd->subele[ele])/100;				// ‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-tsd->def_eleenemy[status_get_elem_type(bl)])/100;				// “G‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-tsd->subenemy[status_get_enemy_type(bl)])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		cardfix = cardfix*(100-tsd->magic_subsize[status_get_size(bl)])/100;		// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
		if(sd)
			cardfix = cardfix*(100-tsd->magic_subrace[race]-tsd->magic_subrace[RCT_PLAYER])/100;
		else
			cardfix = cardfix*(100-tsd->magic_subrace[race])/100;
		cardfix = cardfix*(100-tsd->long_attack_def_rate)/100;	// ‰“‹——£‘Ï«‚É‚æ‚éƒ_ƒ[ƒWŒ¸­
		if(status_get_mode(bl) & MD_BOSS)
			cardfix = cardfix*(100-tsd->magic_subrace[RCT_BOSS])/100;
		else
			cardfix = cardfix*(100-tsd->magic_subrace[RCT_NONBOSS])/100;
		for(i=0; i<tsd->add_mdef_class_count; i++) {
			if(tsd->add_mdef_classid[i] == s_class) {
				cardfix = cardfix*(100-tsd->add_mdef_classrate[i])/100;
				break;
			}
		}
		cardfix = cardfix*(100-tsd->magic_def_rate)/100;
		mgd.damage = mgd.damage*cardfix/100;
	}

#ifndef PRE_RENEWAL
	if(normalmagic_flag && mgd.damage > 0) {
		mgd.damage -= mdef2;
		if(mgd.damage < 1)	// ƒvƒŒƒCƒ„[‚Ì–‚–@ƒXƒLƒ‹‚Í1ƒ_ƒ[ƒW•ÛØ–³‚µ
			mgd.damage = (!battle_config.skill_min_damage && bl->type == BL_PC)? 0: 1;
	}
#endif

	if(skill_num == SO_VARETYR_SPEAR) {	// ƒ”ƒFƒ‰ƒ`ƒ…[ƒ‹ƒXƒsƒA
		static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
		mgd.damage += wd.damage;
	}

	if(mgd.damage < 0)
		mgd.damage = 0;

#ifndef PRE_RENEWAL
	if(t_sc && t_sc->data[SC_SPIDERWEB].timer != -1 && ele == ELE_FIRE && mgd.damage > 0 && normalmagic_flag) {	// ƒXƒpƒCƒ_[ƒEƒFƒu
		mgd.damage <<= 1;
		status_change_end(bl, SC_SPIDERWEB, -1);
	}
#endif

	/* ‚VD‘®«‚Ì“K—p */
	mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));

	/* ‚WD‘ÎÛ‚ÉƒXƒe[ƒ^ƒXˆÙí‚ª‚ ‚éê‡‚Ìƒ_ƒ[ƒWŒ¸Zˆ— */
	if( t_sc && mgd.damage > 0 && normalmagic_flag ) {
		cardfix = 100;

#ifndef PRE_RENEWAL
		// ƒ{ƒ‹ƒP[ƒm
		if(t_sc->data[SC_VOLCANO].timer != -1 && ele == ELE_FIRE)
			cardfix += t_sc->data[SC_VOLCANO].val4;
		// ƒoƒCƒIƒŒƒ“ƒgƒQƒCƒ‹
		if(t_sc->data[SC_VIOLENTGALE].timer != -1 && ele == ELE_WIND)
			cardfix += t_sc->data[SC_VIOLENTGALE].val4;
		// ƒfƒŠƒ…[ƒW
		if(t_sc->data[SC_DELUGE].timer != -1 && ele == ELE_FIRE)
			cardfix += t_sc->data[SC_DELUGE].val4;
#endif
		if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && ele == ELE_POISON)		// ƒxƒiƒ€ƒCƒ“ƒvƒŒƒX
			cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
		if(t_sc->data[SC_ORATIO].timer != -1 && ele == ELE_HOLY)		// ƒIƒ‰ƒeƒBƒI
			cardfix += t_sc->data[SC_ORATIO].val1;
		if(t_sc->data[SC_DEEP_SLEEP].timer != -1)		// ˆÀ‘§‚Ìqç‰Si‰ÁZ‚Å‚¢‚¢‚Ì‚©‚ÈHj
			cardfix += 50;
		if(cardfix != 100) {
			mgd.damage = mgd.damage*cardfix/100;	// ƒXƒe[ƒ^ƒXˆÙí•â³‚É‚æ‚éƒ_ƒ[ƒWŒ¸­
		}
	}

#ifndef PRE_RENEWAL
	if(sd && mgd.damage > 0 && normalmagic_flag) {
		cardfix = 100;
		// iREjƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i–‚–@ƒXƒLƒ‹j
		if(sd->skill_dmgup.count > 0 && skill_num > 0) {
			for(i=0; i<sd->skill_dmgup.count; i++) {
				if(skill_num == sd->skill_dmgup.id[i]) {
					cardfix += sd->skill_dmgup.rate[i];
					break;
				}
			}
		}
		// iREjƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’è‘®«ƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•i–‚–@ƒXƒLƒ‹j
		cardfix += sd->skill_elemagic_dmgup[ele];
		mgd.damage = mgd.damage*cardfix/100;
	}
#endif
#ifdef PRE_RENEWAL
	/* ‚XDƒXƒLƒ‹C³‚P */
	if(skill_num == CR_GRANDCROSS || skill_num == NPC_GRANDDARKNESS) {	// ƒOƒ‰ƒ“ƒhƒNƒƒX
		static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
		mgd.damage = (mgd.damage + wd.damage) * (100 + 40*skill_lv)/100;
		if(battle_config.gx_dupele)
			mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));	// ‘®«2‰ñ‚©‚©‚é
		if(bl == target) {
			if(bl->type & (BL_MOB | BL_HOM | BL_MERC | BL_ELEM))
				mgd.damage = 0;		// MOB,HOM,MERC,ELEM‚ªg‚¤ê‡‚Í”½“®–³‚µ
			else
				mgd.damage /= 2;	// ”½“®‚Í”¼•ª
		}
	}
#endif

	if(skill_num == LG_RAYOFGENESIS) {	// ƒŒƒCƒIƒuƒWƒFƒlƒVƒX
		static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
		mgd.damage += wd.damage;
		mgd.damage = mgd.damage / mgd.div_;
	}

	if(skill_num == WZ_WATERBALL)
		mgd.div_ = 1;

	/* 10D‘ÎÛ‚ÉƒXƒe[ƒ^ƒXˆÙí‚ª‚ ‚éê‡ */
	if(tsd && tsd->special_state.no_magic_damage)
		mgd.damage = 0;	// ‰©‹àå³ƒJ[ƒhi–‚–@ƒ_ƒ[ƒW‚O)

	if(t_sc && t_sc->data[SC_HERMODE].timer != -1 && t_sc->data[SC_HERMODE].val1 == 1)	// ƒwƒ‹ƒ‚[ƒh‚È‚ç–‚–@ƒ_ƒ[ƒW‚È‚µ
		mgd.damage = 0;

	if(skill_num == WL_SOULEXPANSION && t_sc && t_sc->data[SC_WHITEIMPRISON].timer != -1) {	// ƒ\ƒEƒ‹ƒGƒNƒXƒpƒ“ƒVƒ‡ƒ“
		status_change_end(target,SC_WHITEIMPRISON,-1);
		mgd.damage += mgd.damage;
	}

	/* 11DŒÅ’èƒ_ƒ[ƒW */
	if(skill_num == HW_GRAVITATION) {	// ƒOƒ‰ƒrƒe[ƒVƒ‡ƒ“ƒtƒB[ƒ‹ƒh
#ifdef PRE_RENEWAL
		mgd.damage = 200+200*skill_lv;
#else
		mgd.damage = 500+100*skill_lv;
#endif
	}

	/* 12Dƒqƒbƒg‰ñ”‚É‚æ‚éƒ_ƒ[ƒW”{‰Á */
	if(mgd.damage > 0) {
		switch(skill_num) {
			case MG_SOULSTRIKE:
			case MG_COLDBOLT:
			case MG_FIREBOLT:
			case MG_LIGHTNINGBOLT:
			case MG_THUNDERSTORM:
			case PR_MAGNUS:
			case WZ_METEOR:
			case WZ_JUPITEL:
			case WZ_EARTHSPIKE:
			case WZ_HEAVENDRIVE:
			case NPC_DARKSTRIKE:
			case NPC_DARKTHUNDER:
			case HW_NAPALMVULCAN:
			case SL_SMA:
			case NJ_KOUENKA:
			case NJ_HYOUSENSOU:
			case NJ_HUUJIN:
			case LG_RAYOFGENESIS:
			case KO_KAIHOU:	/* p® -‰ğ•ú- */
				if(t_mode&MD_PLANT) // ‘E‚«‚Ì‚±“™
					mgd.damage = mgd.div_;
				else
					mgd.damage *= mgd.div_;
				break;
			default:
				if(t_mode&MD_PLANT) {	 // ‘E‚«‚Ì‚±“™
					if(battle_config.skill_min_damage)
						mgd.damage = mgd.div_;
					else
						mgd.damage = 1;
				}
				break;
		}
	}

	/* 13Dƒ_ƒ[ƒWÅIŒvZ */
	if(skill_num != ASC_BREAKER && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID)
		mgd.damage = battle_calc_damage(bl,target,mgd.damage,mgd.div_,skill_num,skill_lv,mgd.flag);

	/* 14D–‚–@‚Å‚àƒI[ƒgƒXƒyƒ‹”­“®(item_bonus) */
	if(sd && target != &sd->bl && mgd.damage > 0)
	{
		unsigned int asflag = EAS_ATTACK;
		unsigned int tick = gettick();

		if(battle_config.magic_attack_autospell)
			asflag += EAS_SHORT|EAS_LONG;
		else
			asflag += EAS_MAGIC;

		bonus_autospell_start(&sd->bl,target,asflag,tick,0);
		bonus_activeitem_start(sd,EAS_MAGIC,tick);
	}

	/* 15D–‚–@‚Å‚àHP/SP‰ñ•œ(ŒŒõŒ•‚È‚Ç) */
	if(battle_config.magic_attack_drain && bl != target)
		battle_attack_drain(bl,mgd.damage,0,battle_config.magic_attack_drain_enable_type);

	/* 16DŒvZŒ‹‰Ê‚ÌÅI•â³ */
	mgd.amotion = status_get_amotion(bl);
	mgd.dmotion = status_get_dmotion(target);
	mgd.damage2 = 0;
	mgd.type    = 0;

	return mgd;
}

/*==========================================
 * ‚»‚Ì‘¼ƒ_ƒ[ƒWŒvZ
 *------------------------------------------
 */
static struct Damage battle_calc_misc_attack(struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag)
{
	struct Damage mid = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct mob_data *md = NULL;
	struct status_change    *t_sc = NULL;
	struct skill_unit       *unit = NULL;
	int int_, dex, race, ele;
	int skill;
	int damagefix = 1;

	// return‘O‚Ìˆ—‚ª‚ ‚é‚Ì‚Åî•ño—Í•”‚Ì‚İ•ÏX
	if( bl == NULL || target == NULL || target->type == BL_PET ) {
		nullpo_info(NLP_MARK);
		return mid;
	}

	// ƒOƒ‰ƒEƒ“ƒhƒhƒŠƒtƒg‚Ì‚Æ‚«‚Íbl‚ğİ’uÒ‚É’uŠ·‚·‚é
	if(bl->type == BL_SKILL) {
		unit = (struct skill_unit *)bl;
		if(unit && unit->group)
			bl = map_id2bl(unit->group->src_id);
	}

	sd  = BL_DOWNCAST( BL_PC, bl );
	tsd = BL_DOWNCAST( BL_PC, target );
	md  = BL_DOWNCAST( BL_MOB, bl );

	// ƒAƒ^ƒbƒJ[
	int_ = status_get_int(bl);
	dex  = status_get_dex(bl);
	race = status_get_race(bl);
	ele  = skill_get_pl(skill_num);

	// ƒ^[ƒQƒbƒg
	t_sc = status_get_sc(target);		// ‘ÎÛ‚ÌƒXƒe[ƒ^ƒXˆÙí

	if(sd) {
		sd->state.attack_type = BF_MISC;
		sd->state.arrow_atk = 0;
	}

	// ƒLƒ“ƒOƒXƒOƒŒƒCƒX
	if(skill_num != PA_PRESSURE && t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return mid;

	/* ‚PDmid\‘¢‘Ì‚Ì‰Šúİ’è */
	mid.div_      = skill_get_num(skill_num,skill_lv);
	mid.blewcount = skill_get_blewcount(skill_num,skill_lv);
	mid.flag      = BF_MISC|BF_SHORT|BF_SKILL;

	/* ‚QDŠî–{ƒ_ƒ[ƒWŒvZ(ƒXƒLƒ‹‚²‚Æ‚Éˆ—) */
	switch(skill_num)
	{
#ifdef PRE_RENEWAL
	case HT_LANDMINE:	// ƒ‰ƒ“ƒhƒ}ƒCƒ“
	case MA_LANDMINE:
		mid.damage = skill_lv*(dex+75)*(100+int_)/100;
		break;
	case HT_BLASTMINE:	// ƒuƒ‰ƒXƒgƒ}ƒCƒ“
		mid.damage = skill_lv*(dex/2+50)*(100+int_)/100;
		break;
	case HT_CLAYMORETRAP:	// ƒNƒŒƒCƒ‚ƒAƒgƒ‰ƒbƒv
		mid.damage = skill_lv*(dex/2+75)*(100+int_)/100;
		break;
#else
	case HT_LANDMINE:	// ƒ‰ƒ“ƒhƒ}ƒCƒ“
	case MA_LANDMINE:
	case HT_BLASTMINE:	// ƒuƒ‰ƒXƒgƒ}ƒCƒ“
	case HT_CLAYMORETRAP:	// ƒNƒŒƒCƒ‚ƒAƒgƒ‰ƒbƒv
		mid.damage = (int)(dex * (3+status_get_lv(bl)/(float)100) * (1+int_/(float)35) * skill_lv);
		mid.damage = (mid.damage * 90 / 100) + (mid.damage * (atn_rand()%20 + 1) / 100);
		if(sd)
			mid.damage += 40 * pc_checkskill(sd,RA_RESEARCHTRAP);
		break;
#endif

	case HT_BLITZBEAT:	// ƒuƒŠƒbƒcƒr[ƒg
		if(sd == NULL || (skill = pc_checkskill(sd,HT_STEELCROW)) <= 0)
			skill = 0;
		mid.damage = (dex/10 + int_/2 + skill*3 + 40)*2;
		if(flag > 1)
			mid.damage /= flag;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;

	case TF_THROWSTONE:	// Î“Š‚°
		mid.damage = 50;
		damagefix = 0;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;

	case BA_DISSONANCE:	// •s‹¦˜a‰¹
		mid.damage = skill_lv * 20;
		if(sd)
			mid.damage += pc_checkskill(sd,BA_MUSICALLESSON)*3;
		break;
	case NPC_SELFDESTRUCTION:	// ©”š
	case NPC_SELFDESTRUCTION2:	// ©”š2
		mid.damage = status_get_hp(bl)-((bl == target)? 1: 0);
		break;

	case NPC_DARKBREATH:
		{
			struct status_change *t_sc = status_get_sc(target);
#ifdef PRE_RENEWAL
			int hitrate = status_get_hit(bl) - status_get_flee(target) + 80;
#else
			int hitrate = status_get_hit(bl) - status_get_flee(target);
#endif
			int t_hp = status_get_hp(target);
			hitrate = (hitrate > 95)? 95: (hitrate < 5)? 5: hitrate;
			if(t_sc && (t_sc->data[SC_SLEEP].timer != -1 || t_sc->data[SC_STUN].timer != -1 ||
				t_sc->data[SC_FREEZE].timer != -1 || (t_sc->data[SC_STONE].timer != -1 && t_sc->data[SC_STONE].val2 == 0) ) )
				hitrate = 1000000;
			if(atn_rand()%100 < hitrate)
				mid.damage = t_hp*(skill_lv*6)/100;
		}
		break;
	case PA_PRESSURE:		// ƒvƒŒƒbƒVƒƒ[
		mid.damage = 500 + 300 * skill_lv;
		damagefix = 0;
		break;
	case SN_FALCONASSAULT:		// ƒtƒ@ƒ‹ƒRƒ“ƒAƒTƒ‹ƒg
		if(sd == NULL || (skill = pc_checkskill(sd,HT_STEELCROW)) <= 0)
			skill = 0;
		if (md && mobdb_search(md->class_)->mode_opt[MDOPT_STEELCROW])
			skill = mobdb_search(md->class_)->mode_opt[MDOPT_STEELCROW];
		mid.damage = ((dex/10+int_/2+skill*3+40)*2*(150+skill_lv*70)/100)*5;
		if(sd) {
			if(battle_config.allow_falconassault_elemet) {
				ele = sd->atk_ele;
			} else {
				// ˆê“I‚Éƒtƒ@ƒ‹ƒRƒ“ƒAƒTƒ‹ƒg‚Ì‘®«‚ğ•t—^‘®«‚É•ÏX‚·‚é
				int e;
				if((e = status_get_attack_element_nw(&sd->bl)) != ELE_NEUTRAL)	// ‘®«•t—^
					ele = e;
				else if(sd->arrow_ele > ELE_NEUTRAL)	// –î‚Ì‘®«
					ele = sd->arrow_ele;
				else if((e = status_get_attack_element(&sd->bl)) != ELE_NEUTRAL) // •Ší‘®«
					ele = e;
			}
		}
		flag &= ~(BF_WEAPONMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;
	case GS_GROUNDDRIFT:		// ƒOƒ‰ƒEƒ“ƒhƒhƒŠƒtƒg
		if(unit && unit->group)
		{
			const int ele_type[5] = { ELE_WIND, ELE_DARK, ELE_POISON, ELE_WATER, ELE_FIRE };
			ele = ele_type[unit->group->unit_id - UNT_GROUNDDRIFT_WIND];
			mid.damage = status_get_baseatk(bl);
		}
		break;
	case RA_CLUSTERBOMB:		// ƒNƒ‰ƒXƒ^[ƒ{ƒ€
		{
			static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
			mid.damage = wd.damage;
			mid.damage += ((dex * skill_lv + int_ * 5) * (150 + status_get_lv(bl)) / 100) * ((sd? pc_checkskill(sd,RA_RESEARCHTRAP): 5) * 20 / 100) * 2;
			mid.flag |= wd.flag;
			if(sd)
				mid.damage += 40 * pc_checkskill(sd,RA_RESEARCHTRAP);
		}
		break;
	case RA_FIRINGTRAP:			// ƒtƒ@ƒCƒAƒŠƒ“ƒOƒgƒ‰ƒbƒv
	case RA_ICEBOUNDTRAP:		// ƒAƒCƒXƒoƒEƒ“ƒhƒgƒ‰ƒbƒv
		{
			static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
			mid.damage = wd.damage;
			mid.damage += ((dex * skill_lv + int_ * 5) * (150 + status_get_lv(bl)) / 100) * ((sd? pc_checkskill(sd,RA_RESEARCHTRAP): 5) * 20 / 100);
			mid.flag |= wd.flag;
			if(sd)
				mid.damage += 40 * pc_checkskill(sd,RA_RESEARCHTRAP);
		}
		break;
	case NC_MAGMA_ERUPTION_DOTDAMAGE:	/* ƒ}ƒOƒ}ƒCƒ‰ƒvƒVƒ‡ƒ“(’ÇŒ‚) */
		mid.damage = 800 + 200 * skill_lv;
		damagefix = 0;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_SHORT|BF_WEAPON;
		break;
	case GN_THORNS_TRAP:		// ƒ\[ƒ“ƒgƒ‰ƒbƒv
		mid.damage = 100 + 200 * skill_lv + int_;
		damagefix = 0;
		break;
	case GN_BLOOD_SUCKER:		// ƒuƒ‰ƒbƒhƒTƒbƒJ[
		mid.damage = 200 + 100 * skill_lv + int_;
		damagefix = 0;
		break;
	case GN_HELLS_PLANT_ATK:	// ƒwƒ‹ƒYƒvƒ‰ƒ“ƒg
		mid.damage = 10 * skill_lv * status_get_lv(target) + 7 * int_ / 2 * (18 + status_get_jlv(target) / 4) * 5 / (10 - ((sd)? pc_checkskill(sd,AM_CANNIBALIZE) : 5));
		mid.damage = battle_attr_fix(mid.damage, ELE_NEUTRAL, status_get_element(target));
		damagefix = 0;
		break;
	case SU_SV_ROOTTWIST_ATK:	// ƒ}ƒ^ƒ^ƒr‚Ìª‚Á‚±(UŒ‚)
		mid.damage = 100;
		damagefix = 0;
		break;
	case HVAN_EXPLOSION:		// ƒoƒCƒIƒGƒNƒXƒvƒ[ƒWƒ‡ƒ“
		mid.damage = status_get_hp(bl)*(50+50*skill_lv)/100;
		break;
	case NPC_DISSONANCE:
		mid.damage = 30 + skill_lv * 10;
		break;
	default:
		mid.damage = status_get_baseatk(bl);
		break;
	}

	if(damagefix) {
		if(mid.damage < 1 && skill_num != NPC_DARKBREATH)
			mid.damage = 1;

		/* ‚RDƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒWŒ¸Šˆ— */
		if(tsd && mid.damage > 0) {
			int cardfix = 100;
			cardfix = cardfix*(100-tsd->subele[ele])/100;	// ‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-tsd->def_eleenemy[status_get_elem_type(bl)])/100;	// “G‘®«‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			if(sd)
				cardfix = cardfix*(100-tsd->subrace[race]-tsd->subrace[RCT_PLAYER])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			else
				cardfix = cardfix*(100-tsd->subrace[race])/100;	// í‘°‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-tsd->subenemy[status_get_enemy_type(bl)])/100;	// “Gƒ^ƒCƒv‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-tsd->subsize[status_get_size(bl)])/100;	// ƒTƒCƒY‚É‚æ‚éƒ_ƒ[ƒW‘Ï«
			cardfix = cardfix*(100-tsd->misc_def_rate)/100;
			mid.damage = mid.damage*cardfix/100;
		}
		if(mid.damage < 0)
			mid.damage = 0;

		if(skill_num == SN_FALCONASSAULT) {
			if(sd && !battle_config.allow_falconassault_elemet) {
				// ƒtƒ@ƒ‹ƒRƒ“ƒAƒTƒ‹ƒg‚Ì‘®«‚ğŒ³‚É–ß‚·
				ele = skill_get_pl(skill_num);
			}
		}

		/* ‚SD‘®«‚Ì“K—p */
		mid.damage = battle_attr_fix(mid.damage, ele, status_get_element(target));

		/* ‚TDƒXƒLƒ‹C³ */
		if(skill_num == GS_GROUNDDRIFT) {	// ŒÅ’èƒ_ƒ[ƒW‚ğ‰ÁZ‚µ‚Ä‚³‚ç‚É–³‘®«‚Æ‚µ‚Ä‘®«ŒvZ‚·‚é
			mid.damage += skill_lv*50;
			mid.damage = battle_attr_fix(mid.damage, ELE_NEUTRAL, status_get_element(target));
		}

	}

	/* ‚UDƒqƒbƒg‰ñ”‚É‚æ‚éƒ_ƒ[ƒW”{‰Á */
	if(mid.div_ > 1)
		mid.damage *= mid.div_;
	if( mid.damage > 0 && (mid.damage < mid.div_ || (status_get_def(target) >= 1000000 && status_get_mdef(target) >= 1000000)) ) {
		mid.damage = mid.div_;
	}

	/* ‚VDŒÅ’èƒ_ƒ[ƒW */
	if(status_get_mode(target)&MD_PLANT && mid.damage > 0)	// ‘E‚«‚Ì‚±“™
		mid.damage = 1;

	/* ‚WDƒJ[ƒh‚É‚æ‚éƒ_ƒ[ƒW’Ç‰Áˆ— */
	if(sd && sd->skill_dmgup.count > 0 && skill_num > 0 && mid.damage > 0) {	// ƒJ[ƒhŒø‰Ê‚É‚æ‚é“Á’èƒXƒLƒ‹‚Ìƒ_ƒ[ƒW‘•
		int i;
		for(i=0; i<sd->skill_dmgup.count; i++) {
			if(skill_num == sd->skill_dmgup.id[i]) {
				mid.damage += mid.damage * sd->skill_dmgup.rate[i] / 100;
				break;
			}
		}
	}

	/* ‚XDƒ_ƒ[ƒWÅIŒvZ */
	mid.damage = battle_calc_damage(bl,target,mid.damage,mid.div_,skill_num,skill_lv,mid.flag);

	/* 10Dmisc‚Å‚àƒI[ƒgƒXƒyƒ‹”­“®(bonus) */
	if(sd && target != &sd->bl && mid.damage > 0)
	{
		unsigned int asflag = EAS_ATTACK;
		unsigned int tick = gettick();

		if(battle_config.misc_attack_autospell)
			asflag += EAS_SHORT|EAS_LONG;
		else
			asflag += EAS_MISC;

		bonus_autospell_start(&sd->bl,target,asflag,tick,0);
		bonus_activeitem_start(sd,asflag,tick);
	}

	/* 11Dmisc‚Å‚àHP/SP‰ñ•œ(ŒŒõŒ•‚È‚Ç) */
	if(bl != target)
	{
		// ƒtƒ@ƒCƒAƒŠƒ“ƒOƒgƒ‰ƒbƒv‚ÆƒAƒCƒXƒoƒEƒ“ƒhƒgƒ‰ƒbƒv‚Í‰ñ•œ‚·‚é
		if(skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP)
			battle_attack_drain(bl,mid.damage,0,3);
		// ‚»‚Ì‘¼‚Íİ’èŸ‘æ
		else if(battle_config.misc_attack_drain)
			battle_attack_drain(bl,mid.damage,0,battle_config.misc_attack_drain_enable_type);
	}

	/* 12DŒvZŒ‹‰Ê‚ÌÅI•â³ */
	mid.amotion = status_get_amotion(bl);
	mid.dmotion = status_get_dmotion(target);
	mid.damage2 = 0;
	mid.type    = 0;

	return mid;
}

/*==========================================
 * ƒ_ƒ[ƒWŒvZˆêŠ‡ˆ——p
 *------------------------------------------
 */
static struct Damage battle_calc_attack(int attack_type,struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag)
{
	static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	switch(attack_type) {
		case BF_WEAPON:
			return battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
		case BF_MAGIC:
			return battle_calc_magic_attack(bl,target,skill_num,skill_lv,flag);
		case BF_MISC:
			return battle_calc_misc_attack(bl,target,skill_num,skill_lv,flag);
		default:
			if(battle_config.error_log)
				printf("battle_calc_attack: unknwon attack type ! %d\n",attack_type);
			break;
	}
	return wd;
}

/*==========================================
 * ’ÊíUŒ‚ˆ—‚Ü‚Æ‚ß
 *------------------------------------------
 */
int battle_weapon_attack( struct block_list *src,struct block_list *target,unsigned int tick,int flag)
{
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change *sc, *t_sc;
	int damage,rsdamage = 0,ridamage = 0;
	static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	if(src->prev == NULL || target->prev == NULL)
		return 0;
	if(unit_isdead(src) || unit_isdead(target))
		return 0;

	sd  = BL_DOWNCAST( BL_PC, src );
	tsd = BL_DOWNCAST( BL_PC, target );

	sc   = status_get_sc(src);
	t_sc = status_get_sc(target);

	if(sc && sc->opt1 > OPT1_NORMAL && sc->opt1 != OPT1_BURNNING) {
		unit_stopattack(src);
		return 0;
	}

	// ƒEƒH[ƒOƒ‰ƒCƒ_[’†
	if(sd && pc_iswolfmount(sd)) {
		unit_stopattack(src);
		return 0;
	}

	// ©•ª‚Ìó‘ÔˆÙí
	if(sc && (
		sc->data[SC_BLADESTOP].timer != -1 ||		// ”’‰Hæ‚è
		sc->data[SC_FORCEWALKING].timer != -1 ||	// ‹­§ˆÚ“®
		(sc->data[SC_WINKCHARM].timer != -1 && sc->data[SC_WINKCHARM].val2 == target->id) ||	// –£˜f‚ÌƒEƒBƒ“ƒN
		sc->data[SC__SHADOWFORM].timer != -1 ||		// ƒVƒƒƒhƒEƒtƒH[ƒ€
		sc->data[SC__MANHOLE].timer != -1 ||		// ƒ}ƒ“ƒz[ƒ‹
		sc->data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// ô”›w(g—pÒ)
		sc->data[SC_CURSEDCIRCLE].timer != -1 ||		// ô”›w
		(sc->data[SC_SIREN].timer != -1 && sc->data[SC_SIREN].val2 == target->id) ||		// ƒZƒCƒŒ[ƒ“‚Ìº
		sc->data[SC_DEEP_SLEEP].timer != -1 ||		// ˆÀ‚ç‚¬‚Ìqç‰S
		sc->data[SC_DIAMONDDUST].timer != -1 ||		// ƒ_ƒCƒ„ƒ‚ƒ“ƒhƒ_ƒXƒg
		sc->data[SC_SUHIDE].timer != -1			// ‚©‚­‚ê‚é
	)) {
		unit_stopattack(src);
		return 0;
	}

	// ‘Šè‚Ìó‘ÔˆÙí
	if(t_sc && (
		t_sc->data[SC_FORCEWALKING].timer != -1 ||	// ‹­§ˆÚ“®
		t_sc->data[SC__MANHOLE].timer != -1			// ƒ}ƒ“ƒz[ƒ‹
	)) {
		unit_stopattack(src);
		return 0;
	}

	if(battle_check_target(src,target,BCT_ENEMY) <= 0 && !battle_check_range(src,target,0))
		return 0;	// UŒ‚‘ÎÛŠO

	// ƒ^[ƒQƒbƒg‚ªMOB GMƒnƒCƒh’†‚ÅAƒRƒ“ƒtƒBƒO‚ÅƒnƒCƒh’†UŒ‚•s‰Â GMƒŒƒxƒ‹‚ªw’è‚æ‚è‘å‚«‚¢ê‡
	if(battle_config.hide_attack == 0 && target->type == BL_MOB && sd && sd->sc.option&OPTION_SPECIALHIDING && pc_isGM(sd) < battle_config.gm_hide_attack_lv)
		return 0;

	if(sd) {
		if(!battle_delarrow(sd,1,0))
			return 0;
	}

	if(flag&0x8000) {
		if(sd && battle_config.pc_attack_direction_change)
			sd->dir = sd->head_dir = path_calc_dir(src, target->x,target->y);
		else if(src->type == BL_MOB && battle_config.monster_attack_direction_change)
			((struct mob_data *)src)->dir = path_calc_dir(src, target->x,target->y);
		else if(src->type == BL_HOM && battle_config.monster_attack_direction_change)	// homun_attack_direction_change
			((struct homun_data *)src)->dir = path_calc_dir(src, target->x,target->y);
		else if(src->type == BL_MERC && battle_config.monster_attack_direction_change)	// merc_attack_direction_change
			((struct merc_data *)src)->dir = path_calc_dir(src, target->x,target->y);
		else if(src->type == BL_ELEM && battle_config.monster_attack_direction_change)	// elem_attack_direction_change
			((struct elem_data *)src)->dir = path_calc_dir(src, target->x,target->y);
		wd = battle_calc_weapon_attack(src,target,KN_AUTOCOUNTER,flag&0xff,0);
	} else {
		wd = battle_calc_weapon_attack(src,target,0,0,0);
	}

	// O’i¶
	if(sd) {
		int skill = pc_checkskill(sd,MO_TRIPLEATTACK);
		if(skill > 0) {
			int triple_rate = 30 - skill;
			if(sc && sc->data[SC_TRIPLEATTACK_RATE_UP].timer != -1) {
				triple_rate += triple_rate * (50 + 50 * sc->data[SC_TRIPLEATTACK_RATE_UP].val1) / 100;
				status_change_end(src,SC_TRIPLEATTACK_RATE_UP,-1);
			}
			if(atn_rand()%100 < triple_rate) {
				battle_skill_attack(BF_WEAPON,src,src,target,MO_TRIPLEATTACK,skill,tick,0);
				return wd.dmg_lv;
			}
		}
	}

	if((damage = wd.damage + wd.damage2) > 0 && src != target && (t_sc && t_sc->data[SC_KYOMU].timer == -1)) {
		if(t_sc && t_sc->data[SC_REFLECTDAMAGE].timer != -1 && atn_rand()%100 < 30 + t_sc->data[SC_REFLECTDAMAGE].val1 * 10) {	// ƒŠƒtƒŒƒNƒgƒ_ƒ[ƒW”½Ë
			int maxdamage, rddamage;
			maxdamage = (int)((atn_bignumber)status_get_max_hp(target) * status_get_lv(target) / 100);
			rddamage = damage * t_sc->data[SC_REFLECTDAMAGE].val3 / 100;
			rddamage = (rddamage > maxdamage) ? maxdamage: rddamage;

			map_foreachinarea(battle_damage_area,target->m,
				target->x-3,target->y-3,target->x+3,target->y+3,BL_CHAR,
				target,rddamage,LG_REFLECTDAMAGE,t_sc->data[SC_REFLECTDAMAGE].val1,flag|BCT_ENEMY|1,tick);

			if(--t_sc->data[SC_REFLECTDAMAGE].val3 <= 0)
				status_change_end(target,SC_REFLECTDAMAGE,-1);

			if(wd.flag&BF_SHORT && tsd && tsd->short_weapon_damage_return > 0) {
				ridamage += damage * tsd->short_weapon_damage_return / 100;
			}
		} else if(wd.flag&BF_SHORT) {
			if(tsd && tsd->short_weapon_damage_return > 0) {
				ridamage += damage * tsd->short_weapon_damage_return / 100;
			}
			if(t_sc &&
			   t_sc->data[SC_REFLECTSHIELD].timer != -1 &&
			   (sd || t_sc->data[SC_DEVOTION].timer == -1))	// ”íƒfƒBƒ{[ƒVƒ‡ƒ“Ò‚È‚çPC‚©‚çˆÈŠO‚Í”½‰‚µ‚È‚¢
			{
				rsdamage += damage * t_sc->data[SC_REFLECTSHIELD].val2 / 100;
#ifndef PRE_RENEWAL
				if(rsdamage > status_get_max_hp(target))
					rsdamage = status_get_max_hp(target);
#endif
			}
			// ƒfƒXƒoƒEƒ“ƒh”½Ë
			if(t_sc && t_sc->data[SC_DEATHBOUND].timer != -1 && !(status_get_mode(src)&MD_BOSS) && path_check_dir(path_calc_dir(src,target->x,target->y),status_get_dir(target)))
			{
				rsdamage += damage * t_sc->data[SC_DEATHBOUND].val2 / 100;
				if(rsdamage < 1) rsdamage = 1;
				wd.damage = rsdamage / 2;	// ”½Ëƒ_ƒ[ƒW‚Ì”¼•ªg—pÒ‚É•Ô‚é
				clif_skill_damage(target, src, tick, wd.amotion, wd.dmotion, rsdamage, 0, RK_DEATHBOUND, t_sc->data[SC_DEATHBOUND].val1, 1);
				clif_skill_nodamage(target, target, RK_DEATHBOUND, t_sc->data[SC_DEATHBOUND].val1, 1);
				status_change_end(target,SC_DEATHBOUND,-1);
			}
			// ƒV[ƒ‹ƒhƒXƒyƒ‹(DEF)
			if(t_sc && t_sc->data[SC_SHIELDSPELL_DEF].timer != -1 && t_sc->data[SC_SHIELDSPELL_DEF].val2 == 1)
			{
				rsdamage += damage * t_sc->data[SC_SHIELDSPELL_DEF].val3 / 100;
			}
			// ƒCƒ“ƒXƒsƒŒ[ƒVƒ‡ƒ“
			if(sc && sc->data[SC_INSPIRATION].timer != -1)
			{
				rsdamage += damage / 100;
			}
			// ”jÓ’Œ”½Ë
			if(t_sc && t_sc->data[SC_CRESCENTELBOW].timer != -1 && !(status_get_mode(src)&MD_BOSS) && atn_rand()%100 < 94 + t_sc->data[SC_CRESCENTELBOW].val1)
			{
				rsdamage += damage * (50 * t_sc->data[SC_CRESCENTELBOW].val1) / 100;
				if(rsdamage < 1) rsdamage = 1;
				wd.damage = rsdamage / 10;
				clif_skill_damage(target, src, tick, wd.amotion, wd.dmotion, rsdamage, 0, SR_CRESCENTELBOW_AUTOSPELL, t_sc->data[SC_CRESCENTELBOW].val1, 1);
				clif_skill_nodamage(target, target, SR_CRESCENTELBOW, t_sc->data[SC_CRESCENTELBOW].val1, 1);
				skill_blown(target,src,skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,t_sc->data[SC_CRESCENTELBOW].val1)|SAB_NODAMAGE);
				status_change_end(target,SC_CRESCENTELBOW,-1);
				if(tsd)
					pc_delspiritball(tsd,2,0);
			}
		} else if(wd.flag&BF_LONG) {
			if(tsd && tsd->long_weapon_damage_return > 0) {
				ridamage += damage * tsd->long_weapon_damage_return / 100;
			}
		}
		if(rsdamage > 0)
			clif_damage(src,src,tick,wd.amotion,wd.dmotion,rsdamage,1,4,0,0);
		if(ridamage > 0)
			clif_damage(src,src,tick,wd.amotion,wd.dmotion,ridamage,1,4,0,0);
	}
#ifndef PRE_RENEWAL
	if(t_sc && t_sc->data[SC_STEELBODY].timer != -1 && (wd.damage > 0 || wd.damage2 > 0)) {
		wd.damage  = wd.damage  * 10 / 100;
		wd.damage2 = wd.damage2 * 10 / 100;
	}
#endif

	clif_damage(src, target, tick, wd.amotion, wd.dmotion, wd.damage, wd.div_, wd.type, wd.damage2, 0);

	// “ñ“—¬¶è‚ÆƒJƒ^[ƒ‹’ÇŒ‚‚Ìƒ~ƒX•\¦(–³—‚â‚è`)
	if(sd && (sd->status.weapon >= WT_DOUBLE_DD || sd->status.weapon == WT_KATAR) && wd.damage2 == 0)
		clif_damage(src, target, tick+10, wd.amotion, wd.dmotion, 0, 1, 0, 0, 0);

	if(sd && sd->splash_range > 0 && (wd.damage > 0 || wd.damage2 > 0) && (!sc || sc->data[SC_SACRIFICE].timer == -1))
		skill_castend_damage_id(src,target,0,-1,tick,0);

	map_freeblock_lock();
	battle_delay_damage(tick+wd.amotion,src,target,(wd.damage+wd.damage2),0,0,wd.flag);

	if(target->prev != NULL && !unit_isdead(target)) {
		if(wd.damage > 0 || wd.damage2 > 0
#ifndef PRE_RENEWAL
			|| wd.dmg_lv == ATK_DEF
#endif
		) {
			skill_additional_effect(src,target,0,0,BF_WEAPON,tick);
			if(sd && tsd) {
				if(sd->break_weapon_rate > 0 && atn_rand()%10000 < sd->break_weapon_rate)
					pc_break_equip(tsd, LOC_RARM);
				if(sd->break_armor_rate > 0 && atn_rand()%10000 < sd->break_armor_rate)
					pc_break_equip(tsd, LOC_BODY);
			}
		}
	}

	/* ó‘ÔˆÙí */
	if(sc) {
		// ƒI[ƒgƒXƒyƒ‹
		if(sc->data[SC_AUTOSPELL].timer != -1 && atn_rand()%100 < sc->data[SC_AUTOSPELL].val4) {
			int spellid = sc->data[SC_AUTOSPELL].val2;
			int spelllv = sc->data[SC_AUTOSPELL].val3;
			int r = atn_rand()%100;
			int sp = 0, fail = 0;

			if(r >= 50)
				spelllv -= 2;
			else if(r >= 15)
				spelllv--;
			if(spelllv < 1)
				spelllv = 1;

			if(sd) {
				if(sc->data[SC_SAGE].timer != -1)	// ƒZ[ƒW‚Ì°
					spelllv = pc_checkskill(sd,spellid);
				sp = skill_get_sp(spellid,spelllv)*2/3;
				if(sd->status.sp < sp)
					fail = 1;
			}
			if(!fail) {
				if(battle_config.skill_autospell_delay_enable) {
					struct unit_data *ud = unit_bl2ud(src);
					if(ud) {
						int delay = skill_delayfix(src, spellid, spelllv);
						ud->canact_tick = tick + delay;
					}
				}
				if(skill_get_inf(spellid) & INF_GROUND) {
					fail = skill_castend_pos2(src,target->x,target->y,spellid,spelllv,tick,flag);
				} else {
					switch(skill_get_nk(spellid) & 3) {
					case 0:
					case 2:	/* UŒ‚Œn */
						fail = skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
						break;
					case 1:	/* x‰‡Œn */
						if( (spellid == AL_HEAL || (spellid == ALL_RESURRECTION && target->type != BL_PC)) &&
						    battle_check_undead(status_get_race(target),status_get_elem_type(target)) )
							fail = skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
						else
							fail = skill_castend_nodamage_id(src,target,spellid,spelllv,tick,flag);
						break;
					}
				}
				if(sd && !fail)
					pc_heal(sd,0,-sp);
			}
		}

		// ƒfƒ…ƒvƒŒƒ‰ƒCƒg
		if(sc->data[SC_DUPLELIGHT].timer != -1) {
			if(atn_rand()%100 < sc->data[SC_DUPLELIGHT].val2) {
				skill_addtimerskill(src,tick+status_get_adelay(src) / 2,target->id,0,0,AB_DUPLELIGHT_MELEE,sc->data[SC_DUPLELIGHT].val1,tick,flag);
			}
			else if(atn_rand()%100 < sc->data[SC_DUPLELIGHT].val3) {
				skill_addtimerskill(src,tick+status_get_adelay(src) / 2,target->id,0,0,AB_DUPLELIGHT_MAGIC,sc->data[SC_DUPLELIGHT].val1,tick,flag);
			}
		}

		// ƒVƒƒƒhƒEƒI[ƒgƒXƒyƒ‹
		if(sc->data[SC__AUTOSHADOWSPELL].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%100 < sc->data[SC__AUTOSHADOWSPELL].val4) {
			int spellid = sc->data[SC__AUTOSHADOWSPELL].val2;
			int spelllv = sc->data[SC__AUTOSHADOWSPELL].val3;

			if(skill_get_inf(spellid) & INF_GROUND) {
				skill_castend_pos2(src,target->x,target->y,spellid,spelllv,tick,flag);
			} else {
				switch(skill_get_nk(spellid) & 3) {
				case 0:
				case 2:	/* UŒ‚Œn */
					skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
					break;
				case 1:	/* x‰‡Œn */
					if( (spellid == AL_HEAL || (spellid == ALL_RESURRECTION && target->type != BL_PC)) &&
					    battle_check_undead(status_get_race(target),status_get_elem_type(target)) )
						skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
					else
						skill_castend_nodamage_id(src,target,spellid,spelllv,tick,flag);
					break;
				}
			}
		}

		// ƒfƒbƒhƒŠ[ƒCƒ“ƒtƒFƒNƒg
		if(sc->data[SC__DEADLYINFECT].timer != -1 && (wd.damage > 0 || wd.damage2 > 0)) {
			status_change_copy(src,target);
		}

		// “_ŒŠ -‹…-
		if(sd && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? pc_checkskill(sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sc->data[SC_RAISINGDRAGON].timer != -1)
				max += sc->data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num < max)
				pc_addspiritball(sd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
		}

		// ƒgƒƒsƒbƒN
		if(sc->data[SC_TROPIC].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_FIREBOLT,5,tick,flag);
		}

		// ƒN[ƒ‹ƒGƒA[
		if(sc->data[SC_CHILLY_AIR].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_COLDBOLT,5,tick,flag);
		}

		// ƒƒCƒ‹ƒhƒXƒg[ƒ€
		if(sc->data[SC_WILD_STORM].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_LIGHTNINGBOLT,5,tick,flag);
		}

		// ƒAƒbƒvƒwƒCƒoƒ‹
		if(sc->data[SC_UPHEAVAL].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,WZ_EARTHSPIKE,5,tick,flag);
		}
	}

	// ƒJ[ƒh‚É‚æ‚éƒI[ƒgƒXƒyƒ‹
	if(sd && target != &sd->bl && (wd.damage > 0 || wd.damage2 > 0))
	{
		unsigned int asflag = EAS_ATTACK | EAS_NORMAL;
		unsigned int tick = gettick();

		if(wd.flag&BF_LONG)
			asflag += EAS_LONG;
		else
			asflag += EAS_SHORT;

		bonus_autospell_start(&sd->bl,target,asflag,tick,0);
		bonus_activeitem_start(sd,asflag,tick);
	}

	if(sd && target != &sd->bl && wd.flag&BF_WEAPON && (wd.damage > 0 || wd.damage2 > 0))
	{
		// SPÁ¸
		if(tsd && atn_rand()%100 < sd->sp_vanish.rate)
		{
			int sp = status_get_sp(target) * sd->sp_vanish.per/100;
			if(sp > 0)
				pc_heal(tsd, 0, -sp);
		}
	}

	if(sd && target != &sd->bl && wd.flag&BF_WEAPON && (wd.damage > 0 || wd.damage2 > 0)) {
		// “‹zûAˆê’è‹zû‚Æ‚à‚É
		battle_attack_drain(src, wd.damage, wd.damage2, 3);
	}

	if(rsdamage > 0) {
		battle_delay_damage(tick+wd.amotion,target,src,rsdamage,0,0,0);

		// ƒXƒLƒ‹‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒI[ƒgƒXƒyƒ‹
		if(battle_config.weapon_reflect_autospell && target->type == BL_PC && atn_rand()%2)
			bonus_autospell_start(target,src,EAS_ATTACK,tick,0);

		if(battle_config.weapon_reflect_drain && src != target)
			battle_attack_drain(target,rsdamage,0,battle_config.weapon_reflect_drain_enable_type);

		// ƒXƒLƒ‹‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒAƒNƒeƒBƒuƒAƒCƒeƒ€
		if(battle_config.weapon_reflect_autospell && tsd)
			bonus_activeitem_start(tsd,EAS_ATTACK,tick);
	}
	if(ridamage > 0) {
		battle_delay_damage(tick+wd.amotion,target,src,ridamage,0,0,0);

		// ƒAƒCƒeƒ€‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒI[ƒgƒXƒyƒ‹
		if(battle_config.weapon_reflect_autospell && target->type == BL_PC && atn_rand()%2)
			bonus_autospell_start(target,src,EAS_ATTACK,tick,0);

		if(battle_config.weapon_reflect_drain && src != target)
			battle_attack_drain(target,ridamage,0,battle_config.weapon_reflect_drain_enable_type);

		// ƒAƒCƒeƒ€‚Ì”½Ëƒ_ƒ[ƒW‚ÌƒAƒNƒeƒBƒuƒAƒCƒeƒ€
		if(battle_config.weapon_reflect_autospell && tsd)
			bonus_activeitem_start(tsd,EAS_ATTACK,tick);
	}

	// ‘ÎÛ‚ÉƒXƒe[ƒ^ƒXˆÙí‚ª‚ ‚éê‡
	if(t_sc && t_sc->count > 0)
	{
		if(t_sc->data[SC_AUTOCOUNTER].timer != -1 && t_sc->data[SC_AUTOCOUNTER].val4 > 0) {
			if(t_sc->data[SC_AUTOCOUNTER].val3 == src->id)
				battle_weapon_attack(target,src,tick,0x8000|t_sc->data[SC_AUTOCOUNTER].val1);
			status_change_end(target,SC_AUTOCOUNTER,-1);
		}
		if(t_sc->data[SC_BLADESTOP_WAIT].timer != -1 &&
		   !(status_get_mode(src)&MD_BOSS) &&
		   (map[target->m].flag.pvp || unit_distance(src,target) <= 2)) {	// PvPˆÈŠO‚Å‚Ì—LŒøË’ö‚Í2ƒZƒ‹
			int lv  = t_sc->data[SC_BLADESTOP_WAIT].val1;
			int sec = skill_get_time2(MO_BLADESTOP,lv);
			status_change_end(target,SC_BLADESTOP_WAIT,-1);
			status_change_start(src,SC_BLADESTOP,lv,1,src->id,target->id,sec,0);
			status_change_start(target,SC_BLADESTOP,lv,2,target->id,src->id,sec,0);
		}
		if(t_sc->data[SC_POISONREACT].timer != -1) {
			if( (src->type == BL_MOB && status_get_elem_type(src) == ELE_POISON) || status_get_attack_element(src) == ELE_POISON ) {
				// “Å‘®«mob‚Ü‚½‚Í“Å‘®«‚É‚æ‚éUŒ‚‚È‚ç‚Î”½Œ‚
				if( battle_check_range(target,src,status_get_range(target)+1) ) {
					t_sc->data[SC_POISONREACT].val2 = 0;
					battle_skill_attack(BF_WEAPON,target,target,src,AS_POISONREACT,t_sc->data[SC_POISONREACT].val1,tick,0);
				}
			} else {
				// ‚»‚êˆÈŠO‚Ì’ÊíUŒ‚‚É‘Î‚·‚éƒCƒ“ƒx”½Œ‚iËüƒ`ƒFƒbƒN‚È‚µj
				--t_sc->data[SC_POISONREACT].val2;
				if(atn_rand()&1) {
					if( tsd == NULL || pc_checkskill(tsd,TF_POISON) >= 5 )
						battle_skill_attack(BF_WEAPON,target,target,src,TF_POISON,5,tick,flag);
				}
			}
			if(t_sc->data[SC_POISONREACT].val2 <= 0)
				status_change_end(target,SC_POISONREACT,-1);
		}
		if(t_sc->data[SC_HAGALAZ].timer != -1 && wd.flag&BF_WEAPON) {	// ƒXƒg[ƒ“ƒn[ƒhƒXƒLƒ“
			t_sc->data[SC_HAGALAZ].val3 -= (wd.damage + wd.damage2);
			if(t_sc->data[SC_HAGALAZ].val3 <= 0)
				status_change_end(target,SC_HAGALAZ,-1);
			if(sd && atn_rand() % 10000 < 500) {
				pc_break_equip(sd, LOC_RARM);
			} else {
				status_change_start(src,SC_STRIPWEAPON,1,0,0,0,10000,0);
			}
		}
		if(t_sc->data[SC__DEADLYINFECT].timer != -1 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {	// ƒfƒbƒhƒŠ[ƒCƒ“ƒtƒFƒNƒg
			status_change_copy(target,src);
		}
		if(t_sc->data[SC_CIRCLE_OF_FIRE].timer != -1 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {	// ƒT[ƒNƒ‹ƒIƒuƒtƒ@ƒCƒA
			battle_skill_attack(BF_WEAPON,target,target,src,EL_CIRCLE_OF_FIRE,t_sc->data[SC_CIRCLE_OF_FIRE].val1,tick,(0x0f<<20)|0x0500);
		}
	}

	map_freeblock_unlock();
	return wd.dmg_lv;
}

/*=========================================================================
 * ƒXƒLƒ‹UŒ‚Œø‰Êˆ—‚Ü‚Æ‚ß
 * flag‚Ìà–¾B16i}
 * 	0XYRTTff
 *  ff = battle_calc_attack‚ÅŠeíŒvZ‚É—˜—p
 *  TT = ƒpƒPƒbƒg‚Ìtype•”•ªi0‚ÅƒfƒtƒHƒ‹ƒgj
 *   R = —\–ñiskill_area_sub‚Åg—p‚³‚ê‚½BCT_*j
 *   Y = ƒpƒPƒbƒg‚ÌƒXƒLƒ‹Lvif‚Ì‚Æ‚«‚Í-1‚É•ÏŠ·j
 *   X = ƒGƒtƒFƒNƒg‚Ì‚İ‚Åƒ_ƒ[ƒW‚È‚µƒtƒ‰ƒO
 *-------------------------------------------------------------------------
 */
int battle_skill_attack(int attack_type,struct block_list* src,struct block_list *dsrc,
	struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct Damage dmg;
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change *sc;
	struct status_change *ssc;
	int type, lv, damage, rdamage = 0;

	nullpo_retr(0, src);
	nullpo_retr(0, dsrc);
	nullpo_retr(0, bl);

	sc  = status_get_sc(bl);
	ssc = status_get_sc(src);

	sd  = BL_DOWNCAST( BL_PC, src );
	tsd = BL_DOWNCAST( BL_PC, bl );

	if(dsrc->m != bl->m)	// ‘ÎÛ‚ª“¯‚¶ƒ}ƒbƒv‚É‚¢‚È‚¯‚ê‚Î‰½‚à‚µ‚È‚¢
		return 0;
	if(src->prev == NULL || dsrc->prev == NULL || bl->prev == NULL)
		return 0;
	if(unit_isdead(src) || unit_isdead(dsrc) || unit_isdead(bl))	// ‚·‚Å‚É€‚ñ‚Å‚¢‚½‚ç‰½‚à‚µ‚È‚¢
		return 0;

	if(ssc) {		// ©•ª‚Ìó‘ÔˆÙí
		if( ssc->data[SC_FORCEWALKING].timer != -1 ||
			ssc->data[SC_WINKCHARM].timer != -1 ||
			ssc->data[SC__MANHOLE].timer != -1 ||
			ssc->data[SC_SIREN].timer != -1 ||
			ssc->data[SC_DEEP_SLEEP].timer != -1 ||
			ssc->data[SC_DIAMONDDUST].timer != -1 ||
			(ssc->opt1 > OPT1_NORMAL && ssc->opt1 != OPT1_BURNNING))
			return 0;
	}
	if(sc) {
		if(sc->data[SC_HIDING].timer != -1 && !(status_get_mode(src)&MD_BOSS) && skill_get_pl(skillid) != ELE_EARTH && skillid != HW_GRAVITATION)	// ƒnƒCƒfƒBƒ“ƒOó‘Ô‚ÅBOSS‚Å‚È‚­ƒXƒLƒ‹‚Ì‘®«‚ª’n‘®«‚Å‚È‚­ƒOƒ‰ƒrƒe[ƒVƒ‡ƒ“ƒtƒB[ƒ‹ƒh‚Å‚È‚¢‚È‚ç‰½‚à‚µ‚È‚¢
			return 0;
		if(sc->data[SC_CHASEWALK].timer != -1 && skillid == AL_RUWACH)	// ƒ`ƒFƒCƒXƒEƒH[ƒNó‘Ô‚Åƒ‹ƒAƒt–³Œø
			return 0;
		if(sc->data[SC_TRICKDEAD].timer != -1) 				// €‚ñ‚¾‚Ó‚è’†‚Í‰½‚à‚µ‚È‚¢
			return 0;
		if(sc->data[SC_FORCEWALKING].timer != -1) 			// ‹­§ˆÚ“®’†‚Í‰½‚à‚µ‚È‚¢
			return 0;
		// “€Œ‹ó‘Ô‚ÅƒXƒg[ƒ€ƒKƒXƒgAƒtƒƒXƒgƒmƒ”ƒ@A•XÕ—‚Í–³Œø
		if(sc->data[SC_FREEZE].timer != -1 && (skillid == WZ_STORMGUST || skillid == WZ_FROSTNOVA || skillid == NJ_HYOUSYOURAKU))
			return 0;
		if(sc->data[SC__MANHOLE].timer != -1) 			// ƒ}ƒ“ƒz[ƒ‹’†‚Í‰½‚à‚µ‚È‚¢
			return 0;
	}
	if(sd && sd->chatID)	// ”­“®Œ³‚ªPC‚Åƒ`ƒƒƒbƒg’†‚È‚ç‰½‚à‚µ‚È‚¢
		return 0;

	type = (flag >> 8) & 0xff;
	if(skillid == 0)
		type = 5;

	/* –î‚ÌÁ”ï */
	if(sd) {
		int cost = skill_get_arrow_cost(skillid,skilllv);
		if(cost > 0) {
			switch(skillid) {
				case AC_SHOWER:
				case MA_SHOWER:
				case GS_DESPERADO:
				case GS_GROUNDDRIFT:
				case RA_ARROWSTORM:
				case RA_AIMEDBOLT:
				case NC_ARMSCANNON:
				case KO_HAPPOKUNAI:
					// Šù‚ÉÁ”ïˆ—‚ÍŠ®—¹‚µ‚Ä‚¢‚é‚Ì‚ÅœŠO
					break;
				case SN_SHARPSHOOTING:
				case GS_SPREADATTACK:
					if( type == 0 && !battle_delarrow(sd, cost, skillid) )
						return 0;
					break;
				default:
					if( !battle_delarrow(sd, cost, skillid) )
						return 0;
					break;
			}
		}
	}

	/* ƒtƒ‰ƒO’lƒ`ƒFƒbƒN */
	lv = (flag >> 20) & 0x0f;
	if(lv == 0)
		lv = skilllv;
	else if(lv == 0x0f)
		lv = -1;

	if(flag & 0x01000000) {	// ƒGƒtƒFƒNƒg‚¾‚¯o‚µ‚Äƒ_ƒ[ƒW‚È‚µ‚ÅI—¹
		clif_skill_damage(dsrc, bl, tick, status_get_amotion(src), 0, -1, 1, skillid, lv, type);
		return -1;
	}

	/* ƒ_ƒ[ƒWŒvZ */
	dmg = battle_calc_attack(attack_type,(skillid == GS_GROUNDDRIFT)? dsrc: src,bl,skillid,skilllv,flag&0xff);

	/* ƒ}ƒWƒbƒNƒƒbƒh */
	if(attack_type&BF_MAGIC && sc && sc->data[SC_MAGICROD].timer != -1 && src == dsrc) {
		dmg.damage = dmg.damage2 = 0;
		if(tsd) {	// ‘ÎÛ‚ªPC‚Ìê‡
			int sp = skill_get_sp(skillid,skilllv);		// g—p‚³‚ê‚½ƒXƒLƒ‹‚ÌSP‚ğ‹zû
			sp = sp * sc->data[SC_MAGICROD].val2 / 100;
			if(skillid == WZ_WATERBALL && skilllv > 1)
				sp = sp/((skilllv|1)*(skilllv|1));	// ƒEƒH[ƒ^[ƒ{[ƒ‹‚Í‚³‚ç‚ÉŒvZH
			if(sp > 0x7fff)
				sp = 0x7fff;
			else if(sp < 1)
				sp = 1;
			if(tsd->status.sp + sp > tsd->status.max_sp) {
				sp = tsd->status.max_sp - tsd->status.sp;
				tsd->status.sp = tsd->status.max_sp;
			} else {
				tsd->status.sp += sp;
			}
			clif_heal(tsd->fd,SP_SP,sp);
			tsd->ud.canact_tick = tick + skill_delayfix(&tsd->bl, SA_MAGICROD, sc->data[SC_MAGICROD].val1);
		}
		clif_skill_nodamage(bl,bl,SA_MAGICROD,sc->data[SC_MAGICROD].val1,1);	// ƒ}ƒWƒbƒNƒƒbƒhƒGƒtƒFƒNƒg‚ğ•\¦
	}

	damage = dmg.damage + dmg.damage2;

	if(damage <= 0 || damage < dmg.div_)	// ‚«”ò‚Î‚µ”»’è
		dmg.blewcount = 0;

	if(skillid == CR_GRANDCROSS || skillid == NPC_GRANDDARKNESS) {	// ƒOƒ‰ƒ“ƒhƒNƒƒX
		if(battle_config.gx_disptype)
			dsrc = src;	// “Gƒ_ƒ[ƒW”’•¶š•\¦
		if(src == bl)
			type = 4;	// ”½“®‚Íƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“‚È‚µ
	}

	/* ƒRƒ“ƒ{ */
	if(sd) {
		int delay = 0;

		switch(skillid) {
		case MO_TRIPLEATTACK:	// O’i¶
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ˜A‘Å¶A•šŒÕŒA˜A’Œ•öŒ‚æ“¾‚Í+300ms
				if((pc_checkskill(sd, MO_CHAINCOMBO) > 0) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔ‚ÌÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,MO_TRIPLEATTACK,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case MO_CHAINCOMBO:	// ˜A‘Å¶
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// –Ò—´ŒA•šŒÕŒA˜A’Œ•öŒ‚æ“¾‚Í+300ms
				if((pc_checkskill(sd, MO_COMBOFINISH) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔ‚ÌÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,MO_CHAINCOMBO,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case MO_COMBOFINISH:	// –Ò—´Œ
			delay = 700 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ˆ¢C—…”e™€Œæ“¾•‹C‹…4ŒÂ•Û•”š—ô”g“®ó‘Ô‚Í+300ms
				// •šŒÕŒA˜A’Œ•öŒ‚æ“¾‚à+300ms
				if((pc_checkskill(sd, MO_EXTREMITYFIST) > 0 && sd->spiritball.num >= 4 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,MO_COMBOFINISH,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case CH_TIGERFIST:	// •šŒÕŒ
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ˜A’Œ•öŒ‚æ“¾‚Í+300ms
				if(pc_checkskill(sd, CH_CHAINCRUSH) > 0) {
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,CH_TIGERFIST,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case CH_CHAINCRUSH:	// ˜A’Œ•öŒ‚
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ˆ¢C—…K“¾•‹C‹…1ŒÂ•Û•”š—ô”g“®ƒfƒBƒŒƒC
				if(pc_checkskill(sd, MO_EXTREMITYFIST) > 0 && sd->spiritball.num >= 1 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
				{
					delay += (600+(skilllv/5)*200) * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,CH_CHAINCRUSH,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case TK_STORMKICK:
		case TK_DOWNKICK:
		case TK_TURNKICK:
		case TK_COUNTER:
			if(ranking_get_pc_rank(sd,RK_TAEKWON) > 0) {	// ƒeƒRƒ“ƒ‰ƒ“ƒJ[‚ÍƒRƒ“ƒ{‘±s
				delay = status_get_adelay(src);
				if(damage < status_get_hp(bl)) {
					delay += 2000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);	// eA•û®
					// TKƒRƒ“ƒ{“ü—ÍŠÔÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.tkcombo_delay_lower_limits)
						delay = battle_config.tkcombo_delay_lower_limits;
					status_change_start(src,SC_TKCOMBO,skillid,0,0,TK_MISSION,delay,0);
				}
				if(delay > 0)
					sd->ud.attackabletime = tick + delay;
			} else {
				status_change_end(src,SC_TKCOMBO,-1);
			}
			break;
		case SR_DRAGONCOMBO:	// ‘o—´‹r
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				 // ‘å“Z•öxæ“¾•‹C‹…2ŒÂ•ÛƒfƒBƒŒƒC
				if(pc_checkskill(sd, SR_FALLENEMPIRE) > 0 && sd->spiritball.num >= 2)
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔ‚ÌÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,SR_DRAGONCOMBO,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				sd->ud.attacktarget = bl->id;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case SR_FALLENEMPIRE:	// ‘å“Z•öx
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl))
			{
				 // åj–Cæ“¾•‹C‹…2ŒÂ•Û•”š—ô”g“®ó‘Ô@‚Ü‚½‚Í@—…™‹”j™€Œ‚æ“¾•‹C‹…5ŒÂ•Û
				if( (pc_checkskill(sd, SR_TIGERCANNON) > 0 && sd->spiritball.num >= 2 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) ||
					(pc_checkskill(sd, SR_GATEOFHELL)  > 0 && sd->spiritball.num >= 5))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// ƒRƒ“ƒ{“ü—ÍŠÔ‚ÌÅ’á•Ûá’Ç‰Á
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,SR_FALLENEMPIRE,skilllv,0,0,delay,0);
			}
			if(delay > 0)
			{
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		}
	}

	/* ƒ_ƒ[ƒW”½Ë */
	if(attack_type&BF_WEAPON && damage > 0 && src != bl && (sc && sc->data[SC_KYOMU].timer == -1)) {	// •ŠíƒXƒLƒ‹•ƒ_ƒ[ƒW‚ ‚è•g—pÒ‚Æ‘ÎÛÒ‚ªˆá‚¤•‹•–³‚Ì‰e‚Å‚Í‚È‚¢
		if(src == dsrc || (dsrc->type == BL_SKILL && (skillid == SG_SUN_WARM || skillid == SG_MOON_WARM || skillid == SG_STAR_WARM || skillid == GS_DESPERADO))) {
			if(dmg.flag&BF_SHORT) {	// ‹ß‹——£UŒ‚
				if(tsd) {	// ‘ÎÛ‚ªPC‚Ì
					if(tsd->short_weapon_damage_return > 0) {	// ‹ß‹——£UŒ‚’µ‚Ë•Ô‚µ
						rdamage += damage * tsd->short_weapon_damage_return / 100;
						if(rdamage < 1) rdamage = 1;
					}
				}

				// ƒŠƒtƒŒƒNƒgƒV[ƒ‹ƒh
				if(sc &&
				   sc->data[SC_REFLECTSHIELD].timer != -1 &&
				   (sd || sc->data[SC_DEVOTION].timer == -1) &&	// ”íƒfƒBƒ{[ƒVƒ‡ƒ“Ò‚È‚çPC‚©‚çˆÈŠO‚Í”½‰‚µ‚È‚¢
				   skillid != WS_CARTTERMINATION &&
				   skillid != CR_ACIDDEMONSTRATION &&
				   skillid != GN_FIRE_EXPANSION_ACID)
				{
					rdamage += damage * sc->data[SC_REFLECTSHIELD].val2 / 100;	// ’µ‚Ë•Ô‚µŒvZ
#ifndef PRE_RENEWAL
					if(rdamage > status_get_max_hp(bl))
						rdamage = status_get_max_hp(bl);
#endif
					if(rdamage < 1) rdamage = 1;
				}
				// ƒfƒXƒoƒEƒ“ƒh
				if(sc && sc->data[SC_DEATHBOUND].timer != -1 && !(status_get_mode(src)&MD_BOSS) && path_check_dir(path_calc_dir(src,bl->x,bl->y),status_get_dir(bl)))
				{
					rdamage += damage * sc->data[SC_DEATHBOUND].val2 / 100;
					if(rdamage < 1) rdamage = 1;
					damage = rdamage / 2;	// ”½Ëƒ_ƒ[ƒW‚Ì”¼•ªg—pÒ‚É•Ô‚é
					clif_skill_damage(dsrc, src, tick, dmg.amotion, dmg.dmotion, rdamage, 0, RK_DEATHBOUND, sc->data[SC_DEATHBOUND].val1, 1);
					clif_skill_nodamage(dsrc, dsrc, RK_DEATHBOUND, sc->data[SC_DEATHBOUND].val1, 1);
					status_change_end(dsrc,SC_DEATHBOUND,-1);
				}
				// ƒV[ƒ‹ƒhƒXƒyƒ‹(DEF)
				if(sc && sc->data[SC_SHIELDSPELL_DEF].timer != -1 && sc->data[SC_SHIELDSPELL_DEF].val2 == 1)
				{
					rdamage += damage * sc->data[SC_SHIELDSPELL_DEF].val3 / 100;
				}
				// ƒCƒ“ƒXƒsƒŒ[ƒVƒ‡ƒ“
				if(ssc && ssc->data[SC_INSPIRATION].timer != -1)
				{
					rdamage += damage / 100;
				}
				// ”jÓ’Œ”½Ë
				if(sc && sc->data[SC_CRESCENTELBOW].timer != -1 && !(status_get_mode(src)&MD_BOSS) && atn_rand()%100 < 94 + sc->data[SC_CRESCENTELBOW].val1)
				{
					rdamage += damage * (50 * sc->data[SC_CRESCENTELBOW].val1) / 100;
					if(rdamage < 1) rdamage = 1;
					damage = rdamage / 10;
					clif_skill_damage(dsrc, src, tick, dmg.amotion, dmg.dmotion, rdamage, 0, SR_CRESCENTELBOW_AUTOSPELL, sc->data[SC_CRESCENTELBOW].val1, 1);
					clif_skill_nodamage(dsrc, dsrc, SR_CRESCENTELBOW, sc->data[SC_CRESCENTELBOW].val1, 1);
					skill_blown(dsrc,src,skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,sc->data[SC_CRESCENTELBOW].val1)|SAB_NODAMAGE);
					status_change_end(dsrc,SC_CRESCENTELBOW,-1);
					if(tsd)
						pc_delspiritball(tsd,2,0);
				}
			} else if(dmg.flag&BF_LONG) {	// ‰“‹——£UŒ‚
				if(tsd) {		// ‘ÎÛ‚ªPC‚Ì
					if(tsd->long_weapon_damage_return > 0) { // ‰“‹——£UŒ‚’µ‚Ë•Ô‚µ
						rdamage += damage * tsd->long_weapon_damage_return / 100;
						if(rdamage < 1) rdamage = 1;
					}
				}
			}
			if(rdamage > 0)
				clif_damage(src,src,tick, dmg.amotion,0,rdamage,1,4,0,0);
		}
	}
	if(attack_type&BF_MAGIC && damage > 0 && src != bl && (sc && sc->data[SC_KYOMU].timer == -1)) {	// –‚–@ƒXƒLƒ‹•ƒ_ƒ[ƒW‚ ‚è•g—pÒ‚Æ‘ÎÛÒ‚ªˆá‚¤•‹•–³‚Ì‰eó‘Ô‚Å‚Í‚È‚¢
		if(tsd && src == dsrc) {	// ‘ÎÛ‚ªPC‚Ì
			if(tsd->magic_damage_return > 0 && atn_rand()%100 < tsd->magic_damage_return) {	// –‚–@UŒ‚’µ‚Ë•Ô‚µH¦
				rdamage = damage;
				damage  = -1;	// ƒ_ƒ[ƒW0‚¾‚ªmiss‚ğo‚³‚È‚¢
			}
		}
		// ƒJƒCƒg
		if(damage > 0 && sc && sc->data[SC_KAITE].timer != -1 && skillid != HW_GRAVITATION
#ifndef PRE_RENEWAL
			 && src == dsrc && atn_rand()%100 < 50
#endif
		) {
			if(src->type == BL_PC || (status_get_lv(src) < 80 && !(status_get_mode(src)&MD_BOSS)))
			{
				int idx;
				clif_misceffect2(bl,438);
				clif_skill_nodamage(bl,src,skillid,skilllv,1);
				if(--sc->data[SC_KAITE].val2 == 0)
					status_change_end(bl,SC_KAITE,-1);

				if( sd && ssc && ssc->data[SC_WIZARD].timer != -1 &&
				    (idx = pc_search_inventory(sd,7321)) >= 0 ) {
					pc_delitem(sd,idx,1,0,1);
				} else {
					rdamage += damage;
				}
				damage = -1;	// ƒ_ƒ[ƒW0‚¾‚ªmiss‚ğo‚³‚È‚¢
			}
		}
		// ƒ}ƒWƒbƒNƒ~ƒ‰[
		if(damage > 0 && sc && sc->data[SC_MAGICMIRROR].timer != -1) {
			if(atn_rand()%100 < sc->data[SC_MAGICMIRROR].val1 * 20) {
				clif_misceffect2(bl,675);
				clif_skill_nodamage(bl,src,skillid,skilllv,1);
				rdamage += damage;
				damage = -1;	// ƒ_ƒ[ƒW0‚¾‚ªmiss‚ğo‚³‚È‚¢
			}
		}
		// Œ¶p -OŒ¶‘z-
		if(damage > 0 && sc && sc->data[SC_GENSOU].timer != -1) {
			int odamage = damage * sc->data[SC_GENSOU].val2 / 100;

			map_foreachinarea(battle_damage_area,bl->m,
				bl->x-3,bl->y-3,bl->x+3,bl->y+3,BL_CHAR,
				bl,odamage,OB_OBOROGENSOU,sc->data[SC_GENSOU].val1,flag|BCT_ENEMY|1,tick);
		}
		if(rdamage > 0) {
			clif_skill_damage(src, src, tick, dmg.amotion, dmg.dmotion, rdamage, dmg.div_, skillid, ((src == dsrc)? lv: -1), type);
			if(dmg.blewcount > 0 && !map[src->m].flag.gvg) {
				int dir = path_calc_dir(src,bl->x,bl->y);
				if(dir == 0)
					dir = 8;
				skill_blown(src,src,dmg.blewcount|(dir<<20));	// ‘ÎÛ‚É‘Î‚·‚éŒü‚«‚Æ‹t•ûŒü‚É”ò‚Î‚·
			}
			memset(&dmg,0,sizeof(dmg));
		}
	}
#ifndef PRE_RENEWAL
	if(sc && sc->data[SC_STEELBODY].timer != -1 && damage > 0) {
		damage = damage * 10 / 100;
	}
#endif

	/* ƒ_ƒ[ƒWƒpƒPƒbƒg‘—M */
	if(damage != -1) {
		switch(skillid) {
		case NPC_SELFDESTRUCTION:
		case NPC_SELFDESTRUCTION2:
			dmg.blewcount |= SAB_NODAMAGE;
			break;
		case WL_TETRAVORTEX_FIRE:	// ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(‰Î)
		case WL_TETRAVORTEX_WATER:	// ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(…)
		case WL_TETRAVORTEX_WIND:	// ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(•—)
		case WL_TETRAVORTEX_GROUND:	// ƒeƒgƒ‰ƒ{ƒ‹ƒeƒbƒNƒX(’n)
			clif_skill_damage(dsrc, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, WL_TETRAVORTEX, lv, type);
			break;
		default:
			clif_skill_damage(dsrc, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, skillid, lv, type);
			break;
		}
	} else {	// ƒ_ƒ[ƒWÁ¸‚ÍƒpƒPƒbƒg‘—M‚µ‚È‚¢
		damage = 0;
	}

	/* ‚«”ò‚Î‚µ•â³ */
	if(skillid == WZ_STORMGUST) {
		// ƒAƒ“ƒfƒbƒhˆÈŠO‚Ì’ÊíMOB‚ÍƒXƒg[ƒ€ƒKƒXƒg‚Ì3HIT–Ú‚Å’e‚©‚ê‚È‚¢(ŠŠ‚è‚Ì•zÎ)
		if(sc && sc->data[SC_FREEZE].val3 == 2 && !(status_get_mode(bl)&MD_BOSS) && !battle_check_undead(status_get_race(bl), status_get_elem_type(bl))) {
			dmg.blewcount = 0;
		}
	}

	/* ‚«”ò‚Î‚µˆ—‚Æ‚»‚ÌƒpƒPƒbƒg */
	if(dmg.blewcount > 0 && !map[src->m].flag.gvg) {
		skill_blown(dsrc,bl,dmg.blewcount);
	}
	/* ‚«”ò‚Î‚µˆ—‚Æ‚»‚ÌƒpƒPƒbƒg ƒJ[ƒhŒø‰Ê */
	if(dsrc->type == BL_PC && bl->type != BL_SKILL && !map[src->m].flag.gvg) {
		skill_add_blown(dsrc,bl,skillid,SAB_REVERSEBLOW);
	}

	map_freeblock_lock();

	/* ƒŠƒvƒƒfƒ…[ƒX & ƒNƒ[ƒ“ƒXƒLƒ‹ */
	if(damage > 0 && dmg.flag&BF_SKILL && tsd && sc) {
		/* ƒŠƒvƒƒfƒ…[ƒX”»’è */
		if(sc->data[SC__REPRODUCE].timer != -1 && pc_checkskill(tsd,SC_REPRODUCE)) {
			skill_reproduce(tsd,skillid,skilllv);
		}
		/* ƒNƒ[ƒ“ƒXƒLƒ‹”»’è */
		else if(sc->data[SC_PRESERVE].timer == -1 && pc_checkskill(tsd,RG_PLAGIARISM)) {
			skill_clone(tsd,skillid,skilllv);
		}
	}

	/* ÀÛ‚Éƒ_ƒ[ƒWˆ—‚ğs‚¤ */
	if(skillid || flag) {
		switch(skillid) {
		case WZ_METEOR:
		case WZ_VERMILION:
		case WZ_STORMGUST:
		case NPC_SELFDESTRUCTION:
		case NPC_SELFDESTRUCTION2:
			battle_damage(src,bl,damage,skillid,skilllv,dmg.flag);
			break;
		case SR_TIGERCANNON:
			{
				int ar = (skilllv < 5)? 1: 2;
				/* ‘ÎÛü•Ó‚É‚à“¯ƒ_ƒ[ƒW */
				map_foreachinarea(battle_damage_area,bl->m,
					bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
					src,damage,skillid,skilllv,flag|BCT_ENEMY|1,tick);
			}
			break;
		default:
			battle_delay_damage(tick+dmg.amotion,src,bl,damage,skillid,skilllv,dmg.flag);
		}
	}

	if(skillid == RG_INTIMIDATE) {
		/* ƒCƒ“ƒeƒBƒ~ƒfƒCƒg */
		if(damage > 0 && !(status_get_mode(bl)&MD_BOSS) && !map[src->m].flag.gvg) {
			int rate = 90 + status_get_lv(src) - status_get_lv(bl);
			if(atn_rand()%100 < rate)
				skill_addtimerskill(src,tick + status_get_amotion(src) + 500,bl->id,0,0,skillid,skilllv,0,flag);
		}
	} else if(skillid == NPC_EXPULSION) {
		/* ƒGƒNƒXƒpƒ‹ƒVƒIƒ“ */
		if(damage > 0 && !map[src->m].flag.gvg)
			skill_addtimerskill(src,tick + status_get_amotion(src) + 500,bl->id,0,0,skillid,skilllv,0,flag);
	}

	/* ƒ_ƒ[ƒW‚ª‚ ‚é‚È‚ç’Ç‰ÁŒø‰Ê”»’è */
	if(bl->prev != NULL && !unit_isdead(bl)) {
		if((damage > 0 || skillid == SL_STUN
#ifndef PRE_RENEWAL
			|| dmg.dmg_lv == ATK_DEF
#endif
		) && skilllv >= 0) {
			// ƒOƒ‰ƒEƒ“ƒhƒhƒŠƒtƒg‚Ídsrc‚ğˆø”‚Æ‚µ‚Ä“n‚·
			if(skillid == GS_GROUNDDRIFT)
				skill_additional_effect(dsrc,bl,skillid,skilllv,attack_type,tick);
			else if(skillid != TK_TURNKICK)
				skill_additional_effect(src,bl,skillid,skilllv,attack_type,tick);

			if(tsd) {
				// åj–C‚ÌSPÁ”ï
				if(skillid == SR_TIGERCANNON) {
					pc_heal(tsd,0,-(damage / 10));
				}
				// ƒƒ^ƒŠƒbƒNƒTƒEƒ“ƒh‚ÌSPÁ”ï
				if(skillid == WM_METALICSOUND) {
					int sp = damage;
					int lesson_lv = (sd)? pc_checkskill(sd,WM_LESSON): 0;
					lesson_lv = (lesson_lv > 10)? 10: lesson_lv;
					sp = sp / (110 - 10 * lesson_lv);
					pc_heal(tsd,0,-sp);
				}
			}
		}

		if(bl->type == BL_MOB && src != bl)	// ƒXƒLƒ‹g—pğŒ‚ÌMOBƒXƒLƒ‹
		{
			struct mob_data *md = (struct mob_data *)bl;
			if(md) {
				int target = md->target_id;
				if(battle_config.mob_changetarget_byskill == 1 || target == 0)
				{
					if(src->type & (BL_PC | BL_HOM | BL_MERC | BL_ELEM))
						md->target_id = src->id;
				}
				mobskill_use(md,tick,MSC_SKILLUSED|(skillid<<16));
				md->target_id = target;
			}
		}
	}

	/* HP,SP‹zû */
	if(sd && dmg.flag&BF_WEAPON && src != bl && damage > 0) {
		if(src == dsrc || (dsrc->type == BL_SKILL && (skillid == SG_SUN_WARM || skillid == SG_MOON_WARM || skillid == SG_STAR_WARM || skillid == GS_DESPERADO || skillid == KO_HUUMARANKA))) {
			// “‹zûAˆê’è‹zû‚Æ‚à‚É
			battle_attack_drain(src, dmg.damage, dmg.damage2, 3);
		}
	}

	/* ”½Ëƒ_ƒ[ƒW‚ÌÀÛ‚Ìˆ— */
	if((skillid || flag) && rdamage > 0) {
		unsigned int asflag = EAS_WEAPON | EAS_ATTACK | EAS_NORMAL;

		if(attack_type&BF_WEAPON) {
			battle_delay_damage(tick+dmg.amotion,src,src,rdamage,skillid,skilllv,0);
			if(sd) {
				// ”½Ëƒ_ƒ[ƒW‚ÌƒI[ƒgƒXƒyƒ‹
				if(battle_config.weapon_reflect_autospell) {
					bonus_autospell_start(bl,src,asflag,tick,0);
				}
				if(battle_config.weapon_reflect_drain && src != bl)
					battle_attack_drain(bl,rdamage,0,battle_config.weapon_reflect_drain_enable_type);
			}
			if(tsd) {
				// ”½Ëƒ_ƒ[ƒW‚ÌƒAƒNƒeƒBƒuƒAƒCƒeƒ€
				if(battle_config.weapon_reflect_autospell)
					bonus_activeitem_start(tsd,asflag,tick);
			}
		} else {
			battle_damage(src,src,rdamage,skillid,skilllv,0);
			if(sd) {
				// ”½Ëƒ_ƒ[ƒW‚ÌƒI[ƒgƒXƒyƒ‹
				if(battle_config.magic_reflect_autospell) {
					bonus_autospell_start(bl,src,asflag,tick,0);
				}
				if(battle_config.magic_reflect_drain && src != bl)
					battle_attack_drain(bl,rdamage,0,battle_config.magic_reflect_drain_enable_type);
			}
			if(tsd) {
				// ”½Ëƒ_ƒ[ƒW‚ÌƒAƒNƒeƒBƒuƒAƒCƒeƒ€
				if(battle_config.magic_reflect_autospell)
					bonus_activeitem_start(tsd,asflag,tick);
			}
		}
	}

	/* ƒI[ƒgƒJƒEƒ“ƒ^[ */
	if(attack_type&BF_WEAPON && sc && sc->data[SC_AUTOCOUNTER].timer != -1 && sc->data[SC_AUTOCOUNTER].val4 > 0) {
		if(sc->data[SC_AUTOCOUNTER].val3 == dsrc->id)
			battle_weapon_attack(bl,dsrc,tick,0x8000|sc->data[SC_AUTOCOUNTER].val1);
		status_change_end(bl,SC_AUTOCOUNTER,-1);
	}
	/* ƒ_ƒuƒ‹ƒLƒƒƒXƒeƒBƒ“ƒO */
	if ((skillid == MG_COLDBOLT || skillid == MG_FIREBOLT || skillid == MG_LIGHTNINGBOLT) &&
		ssc && ssc->data[SC_DOUBLECASTING].timer != -1 &&
		atn_rand() % 100 < 30+10*ssc->data[SC_DOUBLECASTING].val1) {
		if (!(flag & 1)) {
			//skill_castend_delay (src, bl, skillid, skilllv, tick + dmg.div_*dmg.amotion, flag|1);
			skill_castend_delay (src, bl, skillid, skilllv, tick + 100, flag|1);
		}
	}
	/* ƒuƒ‰ƒbƒhƒ‰ƒXƒg */
	if(src->type == BL_HOM && ssc && ssc->data[SC_BLOODLUST].timer != -1 && dmg.flag&BF_WEAPON && src != bl && src == dsrc && damage > 0)
	{
		struct homun_data *hd = (struct homun_data *)src;
		if(hd && atn_rand()%100 < ssc->data[SC_BLOODLUST].val1*9)
		{
			homun_heal(hd,damage/5,0);
		}
	}
	/* ƒXƒg[ƒ“ƒn[ƒhƒXƒLƒ“ */
	if(attack_type&BF_WEAPON && sc && sc->data[SC_HAGALAZ].timer != -1) {
		sc->data[SC_HAGALAZ].val3 -= (dmg.damage + dmg.damage2);
		if(sc->data[SC_HAGALAZ].val3 <= 0)
			status_change_end(bl,SC_HAGALAZ,-1);
		if(sd && atn_rand() % 10000 < 500) {
			pc_break_equip(sd, LOC_RARM);
		} else {
			status_change_start(src,SC_STRIPWEAPON,1,0,0,0,10000,0);
		}
	}
	/* ƒfƒbƒhƒŠ[ƒCƒ“ƒtƒFƒNƒg */
	if(ssc && ssc->data[SC__DEADLYINFECT].timer != -1 && damage > 0) {
		status_change_copy(src,bl);
	}
	if(dmg.flag&BF_SHORT && sc && sc->data[SC__DEADLYINFECT].timer != -1 && damage > 0) {
		status_change_copy(bl,src);
	}
	/* ƒT[ƒNƒ‹ƒIƒuƒtƒ@ƒCƒA */
	if(dmg.flag&BF_SHORT && sc && sc->data[SC_CIRCLE_OF_FIRE].timer != -1 && src != bl && damage > 0) {
		battle_skill_attack(BF_WEAPON,bl,bl,src,EL_CIRCLE_OF_FIRE,sc->data[SC_CIRCLE_OF_FIRE].val1,tick,(0x0f<<20)|0x0500);
	}

	map_freeblock_unlock();

	return dmg.damage+dmg.damage2;	/* —^ƒ_ƒ‚ğ•Ô‚· */
}

/*==========================================
 *
 *------------------------------------------
 */
int battle_skill_attack_area(struct block_list *bl,va_list ap)
{
	struct block_list *src,*dsrc;
	int atk_type,skillid,skilllv,flag,type;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	atk_type = va_arg(ap,int);
	if((src = va_arg(ap,struct block_list*)) == NULL)
		return 0;
	if((dsrc = va_arg(ap,struct block_list*)) == NULL)
		return 0;

	skillid = va_arg(ap,int);
	skilllv = va_arg(ap,int);
	tick    = va_arg(ap,unsigned int);
	flag    = va_arg(ap,int);
	type    = va_arg(ap,int);

	if(battle_check_target(dsrc,bl,type) > 0)
		battle_skill_attack(atk_type,src,dsrc,bl,skillid,skilllv,tick,flag);

	return 0;
}

/*==========================================
 * •s€”»’è
 *------------------------------------------
 */
int battle_check_undead(int race,int element)
{
	// element ‚É‘®«’l{lv(status_get_element ‚Ì–ß‚è’l)‚ª“n‚³‚ê‚éƒ~ƒX‚É
	// ‘Î‰‚·‚éˆ×Aelement‚©‚ç‘®«ƒ^ƒCƒv‚¾‚¯‚ğ”²‚«o‚·B
	element %= 20;

	if(battle_config.undead_detect_type == 0) {
		if(element == ELE_UNDEAD)
			return 1;
	}
	else if(battle_config.undead_detect_type == 1) {
		if(race == RCT_UNDEAD)
			return 1;
	}
	else {
		if(element == ELE_UNDEAD || race == RCT_UNDEAD)
			return 1;
	}
	return 0;
}

/*==========================================
 * “G–¡•û”»’è(1=m’è, 0=”Û’è, -1=ƒGƒ‰[)
 * flag&0xf0000
 *   0x00000 BCT_NOENEMY: “G‚¶‚á‚È‚¢‚©”»’èiret:1“G‚Å‚Í‚È‚¢j
 *   0x10000 BCT_PARTY:   ƒp[ƒeƒB[”»’èiret:1=ƒp[ƒeƒB[ƒƒ“ƒo)
 *   0x20000 BCT_ALL:     ‘S‚Ä(ret:1=“G–¡•û—¼•û)
 *   0x40000 BCT_ENEMY:   “G‚©”»’è(ret:1=“G)
 *   0x50000 BCT_NOPARTY: ƒp[ƒeƒB[‚¶‚á‚È‚¢‚©”»’è(ret:1=ƒp[ƒeƒB‚Å‚È‚¢)
 *------------------------------------------
 */
int battle_check_target( struct block_list *src, struct block_list *target, int flag)
{
	int s_p, s_g, t_p, t_g;
	struct block_list *ss = src;

	nullpo_retr(-1, src);
	nullpo_retr(-1, target);

	if( flag & BCT_ENEMY ) {	// ”½“]ƒtƒ‰ƒO
		int ret = battle_check_target(src, target, flag & (BCT_PARTY | BCT_ALL));
		if(ret != -1)
			return !ret;
		return -1;
	}

	if( flag & BCT_ALL ) {
		if( target->type == BL_MOB || (target->type == BL_PC && !pc_isinvisible((struct map_session_data *)target)) )
			return 1;
		if( target->type == BL_HOM && src->type != BL_SKILL )	// ƒzƒ€‚ÍƒXƒLƒ‹ƒ†ƒjƒbƒg‚Ì‰e‹¿‚ğó‚¯‚È‚¢
			return 1;
		else
			return -1;
	}

	switch(target->type) {
		case BL_PC:
			if(((struct map_session_data *)target)->invincible_timer != -1)
				return -1;
			break;
		case BL_PET:
			return -1;
		case BL_SKILL:
			if(src->type == BL_SKILL)
				return -1;	// ƒXƒLƒ‹ƒ†ƒjƒbƒg“¯m‚È‚ç–³ğŒm’è

			switch(((struct skill_unit *)target)->group->unit_id) {
				case UNT_ICEWALL:
				case UNT_BLASTMINE:
				case UNT_CLAYMORETRAP:
				case UNT_REVERBERATION:
				case UNT_WALLOFTHORN:
					return 0;
			}
			break;
	}

	// ƒXƒLƒ‹ƒ†ƒjƒbƒg‚Ìê‡Ae‚ğ‹‚ß‚é
	if( src->type == BL_SKILL) {
		struct skill_unit_group *sg = ((struct skill_unit *)src)->group;
		int inf2;
		if( sg == NULL )
			return -1;
		inf2 = skill_get_inf2(sg->skill_id);
		if( (ss = map_id2bl(sg->src_id)) == NULL )
			return -1;
		if(ss->prev == NULL)
			return -1;
		if( target->type != BL_PC || !pc_isinvisible((struct map_session_data *)target) ) {
			if(inf2&INF2_DMG_PK && map[src->m].flag.pk)
				return 0;
			if(inf2&INF2_DMG_GVG && map[src->m].flag.gvg)
				return 0;
			if(inf2&INF2_PVP_DMG   && map[src->m].flag.pvp)
				return 0;
		}
		if(ss == target) {
			if(inf2&INF2_DMG_SELF)
				return 0;
			if(inf2&INF2_NO_SELF)
				return -1;
		}
	}

	// Mob‚Åmaster_id‚ª‚ ‚Á‚Äspecial_mob_ai‚È‚çA¢Š«å‚ğ‹‚ß‚é
	if( src->type == BL_MOB ) {
		struct mob_data *md = (struct mob_data *)src;
		if(md && md->master_id > 0) {
			if(md->master_id == target->id)	// å‚È‚çm’è
				return 1;
			if(md->state.special_mob_ai) {
				if(target->type == BL_MOB) {	// special_mob_ai‚Å‘ÎÛ‚ªMob
					struct mob_data *tmd = (struct mob_data *)target;
					if(tmd) {
						if(tmd->master_id != md->master_id)	// ¢Š«å‚ªˆê‚Å‚È‚¯‚ê‚Î”Û’è
							return 0;
						else if(md->state.special_mob_ai > 2)	// ¢Š«å‚ªˆê‚È‚Ì‚Åm’è‚µ‚½‚¢‚¯‚Ç©”š‚Í”Û’è
							return 0;
						else
							return 1;
					}
				} else if(target->type & (BL_HOM | BL_MERC | BL_ELEM)) {
					// special_mob_ai‚Å‘ÎÛ‚ªƒzƒ€A—b•ºA¸—ì‚È‚çƒGƒ‰[‚Å•Ô‚·
					return -1;
				}
			}
			if((ss = map_id2bl(md->master_id)) == NULL)
				return -1;
		}
	}

	if( src == target || ss == target )	// “¯‚¶‚È‚çm’è
		return 1;

	if(target->type == BL_PC && pc_isinvisible((struct map_session_data *)target))
		return -1;

	if( src->prev == NULL || unit_isdead(src) ) // €‚ñ‚Å‚é‚È‚çƒGƒ‰[
		return -1;

	// PC‚©‚çMOB
	if(ss->type == BL_PC && target->type == BL_MOB) {
		int guardian = 0;
		struct mob_data *md         = (struct mob_data *)target;
		struct map_session_data *sd = (struct map_session_data *)ss;
		struct guild_castle *gc = NULL;

		// Ô‚ÌƒK[ƒfƒBƒAƒ“‚©‚Ç‚¤‚©
		if(md->guild_id > 0) {
			gc = guild_mapid2gc(md->bl.m);
			if(gc) {
				int i;
				for(i = 0; i < sizeof(gc->guardian) / sizeof(gc->guardian[0]); i++) {
					if(gc->guardian[i].id == md->bl.id) {
						guardian = 1;
						break;
					}
				}
			}
		}

		// GvGŠÔŠO
		if(!map[ss->m].flag.gvg) {
			// ƒK[ƒfƒBƒAƒ“‚Æ”O‚Ì‚½‚ßƒGƒ“ƒy‚Í–¡•û
			if(md->class_ == MOBID_EMPERIUM || guardian)
				return 1;
			// ‚»‚êˆÈŠO‚Í“G
			return 0;
		}

		/* ‚±‚±‚©‚ç flag.gvg ‚ª‚ ‚éˆ— */

		// ƒMƒ‹ƒh–³‚µPC‚Í‘S•”“G
		if(sd->status.guild_id <= 0)
			return 0;

		// ƒMƒ‹ƒhéî•ñ‚Ì•âŠ®
		if(md->guild_id <= 0)
			gc = guild_mapid2gc(md->bl.m);

		// ©•ª‚ÌƒMƒ‹ƒh‚©“¯–¿ƒMƒ‹ƒhÔ
		if(gc) {
			struct guild *g = guild_search(sd->status.guild_id);
			if(g == NULL)
				return 0;

			if(g->guild_id == gc->guild_id || guild_check_alliance(md->guild_id, sd->status.guild_id, 0)) {
				// ƒGƒ“ƒy‚ÆƒK[ƒfƒBƒAƒ“‚Í–¡•û
				if(md->class_ == MOBID_EMPERIUM || guardian)
					return 1;
				// ‚»‚êˆÈŠO‚ÌƒoƒCƒIƒvƒ‰ƒ“ƒgAƒXƒtƒBƒAƒ}ƒCƒ“‚È‚Ç‚Í“GiUŒ‚‰Â”\j
				return 0;
			}
		}

		// ‘¼l‚ÌÔAÔˆÈŠO‚ÌGvGƒ‚[ƒh‚È‚ç‘S•”“G
		return 0;
	}
	if(ss->type == BL_MOB && target->type == BL_PC) {
		return 0;	// MOB¨PC‚È‚ç“G
	}

	if(ss->type == BL_PET && target->type == BL_MOB) {
		struct pet_data *pd = (struct pet_data*)ss;
		struct mob_data *md = (struct mob_data*)target;
		int mode = mobdb_search(pd->class_)->mode;
		int race = mobdb_search(pd->class_)->race;
		if(mobdb_search(pd->class_)->mexp <= 0 && !(mode&MD_BOSS) && (md->sc.option & (OPTION_HIDE | OPTION_CLOAKING) && race != RCT_INSECT && race != RCT_DEMON) ) {
			return 1; // ¸”s
		} else {
			return 0; // ¬Œ÷
		}
	}

	s_p = status_get_party_id(ss);
	s_g = status_get_guild_id(ss);

	t_p = status_get_party_id(target);
	t_g = status_get_guild_id(target);

	if(flag & BCT_PARTY) {
		if(s_p && t_p && s_p == t_p)
			return 1;	// “¯‚¶ƒp[ƒeƒB‚È‚çm’èi–¡•ûj
		else
			return 0;	// ƒp[ƒeƒBŒŸõ‚È‚ç“¯‚¶ƒp[ƒeƒB‚¶‚á‚È‚¢“_‚Å”Û’è
	}

	if(ss->type == BL_MOB && s_g > 0 && t_g > 0 && s_g == t_g )	// “¯‚¶ƒMƒ‹ƒh/mobƒNƒ‰ƒX‚È‚çm’èi–¡•ûj
		return 1;

	if(ss->type == BL_PC && target->type == BL_PC) {	// —¼•ûPVPƒ‚[ƒh‚È‚ç”Û’èi“Gj
		struct skill_unit *su = NULL;
		if(src->type == BL_SKILL)
			su = (struct skill_unit *)src;
		// PK
		if(map[ss->m].flag.pk) {
			struct guild *g = NULL;
			struct map_session_data* ssd = (struct map_session_data*)ss;
			struct map_session_data* tsd = (struct map_session_data*)target;

			// battle_config.no_pk_levelˆÈ‰º@1Ÿ‚Í–¡•û@“]¶‚Í‘Ê–Ú
			if(ssd->sc.data[SC_PK_PENALTY].timer != -1)
				return 1;
			if(ssd->status.base_level <= battle_config.no_pk_level && (ssd->s_class.job <= PC_JOB_MC || ssd->s_class.job == PC_JOB_TK) && ssd->s_class.upper != PC_UPPER_HIGH)
				return 1;
			if(tsd->status.base_level <= battle_config.no_pk_level && (tsd->s_class.job <= PC_JOB_MC || tsd->s_class.job == PC_JOB_TK) && tsd->s_class.upper != PC_UPPER_HIGH)
				return 1;
			if(su && su->group && su->group->target_flag == BCT_NOENEMY)
				return 1;
			if(s_p > 0 && t_p > 0 && s_p == t_p)
				return 1;
			else if(s_g > 0 && t_g > 0 && s_g == t_g)
				return 1;
			if((g = guild_search(s_g)) != NULL) {
				int i;
				for(i=0; i<MAX_GUILDALLIANCE; i++) {
					if(g->alliance[i].guild_id > 0 && g->alliance[i].guild_id == t_g) {
						if(g->alliance[i].opposition)
							return 0;	// “G‘ÎƒMƒ‹ƒh‚È‚ç–³ğŒ‚É“G
						else
							return 1;	// “¯–¿ƒMƒ‹ƒh‚È‚ç–³ğŒ‚É–¡•û
					}
				}
			}
			return 0;
		}
		// PVP
		if(map[ss->m].flag.pvp) {
			if(su && su->group->target_flag == BCT_NOENEMY)
				return 1;
			if(map[ss->m].flag.pvp_noparty && s_p > 0 && t_p > 0 && s_p == t_p)
				return 1;
			else if(map[ss->m].flag.pvp_noguild && s_g > 0 && t_g > 0 && s_g == t_g)
				return 1;
			return 0;
		}
		// GVG
		if(map[src->m].flag.gvg) {
			struct guild *g = NULL;
			if(su && su->group->target_flag == BCT_NOENEMY)
				return 1;
			if(s_g > 0 && s_g == t_g)
				return 1;
			if(map[src->m].flag.gvg_noparty && s_p > 0 && t_p > 0 && s_p == t_p)
				return 1;
			if((g = guild_search(s_g)) != NULL) {
				int i;
				for(i=0; i<MAX_GUILDALLIANCE; i++) {
					if(g->alliance[i].guild_id > 0 && g->alliance[i].guild_id == t_g) {
						if(g->alliance[i].opposition)
							return 0;	// “G‘ÎƒMƒ‹ƒh‚È‚ç–³ğŒ‚É“G
						else
							return 1;	// “¯–¿ƒMƒ‹ƒh‚È‚ç–³ğŒ‚É–¡•û
					}
				}
			}
			return 0;
		}
	}

	if(ss->type == BL_MOB && (target->type & (BL_HOM | BL_MERC | BL_ELEM)))
		return 0;	// MOB vs HOM, MERC, ELEM ‚È‚ç“G

	if((ss->type & (BL_HOM | BL_MERC | BL_ELEM)) && target->type == BL_MOB)
		return 0;	// HOM, MERC, ELEM vs MOB ‚È‚ç“G

	if(!(map[ss->m].flag.pvp || map[ss->m].flag.gvg)) {
		if(ss->type == BL_PC && (target->type & (BL_HOM | BL_MERC | BL_ELEM)))
			return 1;	// Pv‚Å‚àGv‚Å‚à‚È‚¢‚È‚çAPC vs HOM, MERC, ELEM ‚Í–¡•û

		if((ss->type & (BL_HOM | BL_MERC | BL_ELEM)) && target->type == BL_PC)
			return 1;	// Pv‚Å‚àGv‚Å‚à‚È‚¢‚È‚çAHOM, MERC, ELEM vs PC ‚Í–¡•û
	}

	// “¯PT‚Æ‚©“¯–¿Guild‚Æ‚©‚ÍŒã‰ñ‚µi
	if(ss->type & (BL_HOM | BL_MERC | BL_ELEM)) {
		if(map[ss->m].flag.pvp) {	// PVP
			if(target->type & (BL_HOM | BL_MERC | BL_ELEM))
				return 0;
			if(target->type == BL_PC) {
				struct map_session_data *msd = map_bl2msd(ss);

				if(msd == NULL || target != &msd->bl)
					return 0;
			}
		}
		if(map[ss->m].flag.gvg) {	// GVG
			if(target->type & (BL_HOM | BL_MERC | BL_ELEM))
				return 0;
		}
	}
	if(ss->type == BL_PC && (target->type & (BL_HOM | BL_MERC | BL_ELEM))) {
		if(map[ss->m].flag.pvp) {	// PVP
			struct map_session_data *msd = map_bl2msd(target);

			if(msd == NULL || ss != &msd->bl)
				return 0;
		}
		if(map[ss->m].flag.gvg) {	// GVG
			return 0;
		}
	}
	return 1;	// ŠY“–‚µ‚È‚¢‚Ì‚Å–³ŠÖŒWl•¨i‚Ü‚ “G‚¶‚á‚È‚¢‚Ì‚Å–¡•ûj
}

/*==========================================
 * Ë’ö”»’è
 *------------------------------------------
 */
int battle_check_range(struct block_list *src,struct block_list *bl,int range)
{
	int arange;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	arange = path_distance(src->x,src->y,bl->x,bl->y);

	if(src->m != bl->m)	// ˆá‚¤ƒ}ƒbƒv
		return 0;

	if(range > 0 && range < arange)	// ‰“‚·‚¬‚é
		return 0;

	if(arange < 2)	// “¯‚¶ƒ}ƒX‚©—×Ú
		return 1;

	// áŠQ•¨”»’è
	return path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y);
}

/*==========================================
 * –î‚ÌÁ”ï
 *------------------------------------------
 */
int battle_delarrow(struct map_session_data* sd,int num,int skillid)
{
	int mask = 0, idx = -1;

	nullpo_retr(0, sd);

	if(skillid == 0) {	// ’ÊíUŒ‚
		switch(sd->status.weapon) {
			case WT_BOW:
				mask = 1;
				break;
			case WT_HANDGUN:
				mask = 4;
				break;
			case WT_RIFLE:
				mask = 8;
				break;
			case WT_SHOTGUN:
				mask = 16;
				break;
			case WT_GATLING:
				mask = 32;
				break;
			case WT_GRENADE:
				mask = 64;
				break;
			default:
				return 1;
		}
	} else {		// ƒXƒLƒ‹UŒ‚
		mask = skill_get_arrow_type(skillid);
	}

	idx = sd->equip_index[EQUIP_INDEX_ARROW];
	if(idx >= 0 && sd->status.inventory[idx].amount >= num && sd->inventory_data[idx]->arrow_type & mask) {
		if(battle_config.arrow_decrement)
			pc_delitem(sd,idx,num,0,0);
	} else {
		clif_arrow_fail(sd,0);
		return 0;
	}
	return 1;
}

/*==========================================
 * ƒ_ƒ[ƒW‚È‚µ‚Å‹¤“¬‚ÉQ‰Á
 *------------------------------------------
 */
void battle_join_struggle(struct mob_data *md,struct block_list *src)
{
	nullpo_retv(md);
	nullpo_retv(src);

	if(src->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)src;
		if(sd) {
			if(!linkdb_exists( &md->dmglog, INT2PTR(sd->status.char_id) )) {
				// ƒ_ƒ[ƒW‚È‚µ‚Åí“¬Q‰ÁÒ“ü‚è
				linkdb_insert( &md->dmglog, INT2PTR(sd->status.char_id), INT2PTR(0) );
			}
		}
	}
	return;
}

/*==========================================
 * İ’èƒtƒ@ƒCƒ‹“Ç‚İ‚İ—piƒtƒ‰ƒOj
 *------------------------------------------
 */
static int battle_config_switch(const char *str)
{
	if(strcmpi(str,"on") == 0 || strcmpi(str,"yes") == 0)
		return 1;
	if(strcmpi(str,"off") == 0 || strcmpi(str,"no") == 0)
		return 0;
	return atoi(str);
}

/*==========================================
 * İ’èƒtƒ@ƒCƒ‹‚ğ“Ç‚İ‚Ş
 *------------------------------------------
 */
int battle_config_read(const char *cfgName)
{
	int i;
	char line[1024],w1[1024],w2[1024];
	FILE *fp;
	static int count = 0;
	static const struct {
		const char *str;
		int *val;
		int defval;
	} data[] = {
		{ "warp_point_debug",                   &battle_config.warp_point_debug,                   0        },
		{ "enemy_critical",                     &battle_config.enemy_critical,                     0        },
		{ "enemy_critical_rate",                &battle_config.enemy_critical_rate,                100      },
		{ "enemy_str",                          &battle_config.enemy_str,                          1        },
		{ "enemy_perfect_flee",                 &battle_config.enemy_perfect_flee,                 0        },
		{ "casting_rate",                       &battle_config.cast_rate,                          100      },
		{ "no_casting_dex",                     &battle_config.no_cast_dex,                        150      },
		{ "delay_rate",                         &battle_config.delay_rate,                         100      },
		{ "delay_dependon_dex",                 &battle_config.delay_dependon_dex,                 0        },
		{ "no_delay_dex",                       &battle_config.no_delay_dex,                       150      },
		{ "skill_delay_attack_enable",          &battle_config.sdelay_attack_enable,               1        },
		{ "left_cardfix_to_right",              &battle_config.left_cardfix_to_right,              1        },
		{ "player_skill_add_range",             &battle_config.pc_skill_add_range,                 0        },
		{ "skill_out_range_consume",            &battle_config.skill_out_range_consume,            1        },
		{ "monster_skill_add_range",            &battle_config.mob_skill_add_range,                0        },
		{ "player_damage_delay",                &battle_config.pc_damage_delay,                    1        },
		{ "player_damage_delay_rate",           &battle_config.pc_damage_delay_rate,               10       },
		{ "defunit_not_enemy",                  &battle_config.defnotenemy,                        0        },
		{ "random_monster_checklv",             &battle_config.random_monster_checklv,             1        },
		{ "attribute_recover",                  &battle_config.attr_recover,                       1        },
		{ "flooritem_lifetime",                 &battle_config.flooritem_lifetime,                 60000    },
		{ "item_auto_get",                      &battle_config.item_auto_get,                      0        },
		{ "item_first_get_time",                &battle_config.item_first_get_time,                3000     },
		{ "item_second_get_time",               &battle_config.item_second_get_time,               1000     },
		{ "item_third_get_time",                &battle_config.item_third_get_time,                1000     },
		{ "mvp_item_first_get_time",            &battle_config.mvp_item_first_get_time,            10000    },
		{ "mvp_item_second_get_time",           &battle_config.mvp_item_second_get_time,           10000    },
		{ "mvp_item_third_get_time",            &battle_config.mvp_item_third_get_time,            2000     },
		{ "item_rate",                          &battle_config.item_rate,                          100      },
		{ "drop_rate0item",                     &battle_config.drop_rate0item,                     0        },
		{ "base_exp_rate",                      &battle_config.base_exp_rate,                      100      },
		{ "job_exp_rate",                       &battle_config.job_exp_rate,                       100      },
		{ "death_penalty_type",                 &battle_config.death_penalty_type,                 3        },
		{ "death_penalty_base",                 &battle_config.death_penalty_base,                 100      },
		{ "death_penalty_job",                  &battle_config.death_penalty_job,                  100      },
		{ "zeny_penalty",                       &battle_config.zeny_penalty,                       0        },
		{ "zeny_penalty_percent",               &battle_config.zeny_penalty_percent,               0        },
		{ "zeny_penalty_by_lvl",                &battle_config.zeny_penalty_by_lvl,                0        },
		{ "restart_hp_rate",                    &battle_config.restart_hp_rate,                    0        },
		{ "restart_sp_rate",                    &battle_config.restart_sp_rate,                    0        },
		{ "mvp_hp_rate",                        &battle_config.mvp_hp_rate,                        100      },
		{ "mvp_item_rate",                      &battle_config.mvp_item_rate,                      100      },
		{ "mvp_exp_rate",                       &battle_config.mvp_exp_rate,                       100      },
		{ "monster_hp_rate",                    &battle_config.monster_hp_rate,                    100      },
		{ "monster_max_aspd",                   &battle_config.monster_max_aspd,                   200      },
		{ "homun_max_aspd",                     &battle_config.homun_max_aspd,                     200      },
		{ "merc_max_aspd",                      &battle_config.merc_max_aspd,                      200      },
		{ "elem_max_aspd",                      &battle_config.elem_max_aspd,                      200      },
		{ "atcommand_gm_only",                  &battle_config.atc_gmonly,                         1        },
		{ "gm_all_skill",                       &battle_config.gm_allskill,                        1        },
		{ "gm_all_skill_add_abra",              &battle_config.gm_allskill_addabra,                0        },
		{ "gm_all_equipment",                   &battle_config.gm_allequip,                        0        },
		{ "gm_skill_unconditional",             &battle_config.gm_skilluncond,                     0        },
		{ "player_skillfree",                   &battle_config.skillfree,                          0        },
		{ "player_skillup_limit",               &battle_config.skillup_limit,                      0        },
		{ "weapon_produce_rate",                &battle_config.wp_rate,                            100      },
		{ "potion_produce_rate",                &battle_config.pp_rate,                            100      },
		{ "deadly_potion_produce_rate",         &battle_config.cdp_rate,                           100      },
		{ "monster_active_enable",              &battle_config.monster_active_enable,              1        },
		{ "monster_damage_delay_rate",          &battle_config.monster_damage_delay_rate,          100      },
		{ "monster_loot_type",                  &battle_config.monster_loot_type,                  0        },
		{ "mob_skill_use",                      &battle_config.mob_skill_use,                      1        },
		{ "mob_count_rate",                     &battle_config.mob_count_rate,                     100      },
		{ "mob_delay_rate",                     &battle_config.mob_delay_rate,                     100      },
		{ "mob_middle_boss_delay_rate",         &battle_config.mob_middle_boss_delay_rate,         100      },
		{ "mob_mvp_boss_delay_rate",            &battle_config.mob_mvp_boss_delay_rate,            100      },
		{ "quest_skill_learn",                  &battle_config.quest_skill_learn,                  0        },
		{ "quest_skill_reset",                  &battle_config.quest_skill_reset,                  1        },
		{ "basic_skill_check",                  &battle_config.basic_skill_check,                  1        },
		{ "guild_emperium_check",               &battle_config.guild_emperium_check,               1        },
		{ "guild_emblem_colors",                &battle_config.guild_emblem_colors,                3        },
		{ "guild_exp_limit",                    &battle_config.guild_exp_limit,                    50       },
		{ "player_invincible_time" ,            &battle_config.pc_invincible_time,                 5000     },
		{ "pet_catch_rate",                     &battle_config.pet_catch_rate,                     100      },
		{ "pet_rename",                         &battle_config.pet_rename,                         0        },
		{ "pet_friendly_rate",                  &battle_config.pet_friendly_rate,                  100      },
		{ "pet_hungry_delay_rate",              &battle_config.pet_hungry_delay_rate,              100      },
		{ "pet_hungry_friendly_decrease",       &battle_config.pet_hungry_friendly_decrease,       5        },
		{ "pet_str",                            &battle_config.pet_str,                            1        },
		{ "pet_status_support",                 &battle_config.pet_status_support,                 1        },
		{ "pet_attack_support",                 &battle_config.pet_attack_support,                 0        },
		{ "pet_damage_support",                 &battle_config.pet_damage_support,                 0        },
		{ "pet_support_rate",                   &battle_config.pet_support_rate,                   100      },
		{ "pet_attack_exp_to_master",           &battle_config.pet_attack_exp_to_master,           0        },
		{ "pet_attack_exp_rate",                &battle_config.pet_attack_exp_rate,                100      },
		{ "skill_min_damage",                   &battle_config.skill_min_damage,                   0        },
		{ "finger_offensive_type",              &battle_config.finger_offensive_type,              0        },
		{ "heal_exp",                           &battle_config.heal_exp,                           0        },
		{ "resurrection_exp",                   &battle_config.resurrection_exp,                   0        },
		{ "shop_exp",                           &battle_config.shop_exp,                           0        },
		{ "combo_delay_rate",                   &battle_config.combo_delay_rate,                   100      },
		{ "item_check",                         &battle_config.item_check,                         0        },
		{ "wedding_modifydisplay",              &battle_config.wedding_modifydisplay,              1        },
		{ "natural_healhp_interval",            &battle_config.natural_healhp_interval,            6000     },
		{ "natural_healsp_interval",            &battle_config.natural_healsp_interval,            8000     },
		{ "natural_heal_skill_interval",        &battle_config.natural_heal_skill_interval,        10000    },
		{ "natural_heal_weight_rate",           &battle_config.natural_heal_weight_rate,           50       },
		{ "natural_heal_weight_rate_icon",      &battle_config.natural_heal_weight_rate_icon,      0        },
		{ "item_name_override_grffile",         &battle_config.item_name_override_grffile,         0        },
		{ "arrow_decrement",                    &battle_config.arrow_decrement,                    1        },
		{ "allow_any_weapon_autoblitz",         &battle_config.allow_any_weapon_autoblitz,         0        },
		{ "max_aspd",                           &battle_config.max_aspd,                           200      },
		{ "pk_max_aspd",                        &battle_config.pk_max_aspd,                        200      },
		{ "gvg_max_aspd",                       &battle_config.gvg_max_aspd,                       200      },
		{ "pvp_max_aspd",                       &battle_config.pvp_max_aspd,                       200      },
		{ "max_hp",                             &battle_config.max_hp,                             999999   },
		{ "max_sp",                             &battle_config.max_sp,                             999999   },
		{ "max_parameter",                      &battle_config.max_parameter,                      99       },
		{ "max_cart_weight",                    &battle_config.max_cart_weight,                    8000     },
		{ "player_skill_log",                   &battle_config.pc_skill_log,                       0        },
		{ "monster_skill_log",                  &battle_config.mob_skill_log,                      0        },
		{ "battle_log",                         &battle_config.battle_log,                         0        },
		{ "save_log",                           &battle_config.save_log,                           0        },
		{ "error_log",                          &battle_config.error_log,                          1        },
		{ "etc_log",                            &battle_config.etc_log,                            1        },
		{ "save_clothcolor",                    &battle_config.save_clothcolor,                    0        },
		{ "undead_detect_type",                 &battle_config.undead_detect_type,                 0        },
		{ "player_auto_counter_type",           &battle_config.pc_auto_counter_type,               0        },
		{ "monster_auto_counter_type",          &battle_config.monster_auto_counter_type,          1        },
		{ "min_hitrate",                        &battle_config.min_hitrate,                        5        },
		{ "agi_penalty_type",                   &battle_config.agi_penalty_type,                   1        },
		{ "agi_penalty_count",                  &battle_config.agi_penalty_count,                  3        },
		{ "agi_penalty_num",                    &battle_config.agi_penalty_num,                    10       },
		{ "agi_penalty_count_lv",               &battle_config.agi_penalty_count_lv,               ATK_FLEE },
		{ "vit_penalty_type",                   &battle_config.vit_penalty_type,                   1        },
		{ "vit_penalty_count",                  &battle_config.vit_penalty_count,                  3        },
		{ "vit_penalty_num",                    &battle_config.vit_penalty_num,                    5        },
		{ "vit_penalty_count_lv",               &battle_config.vit_penalty_count_lv,               ATK_DEF  },
		{ "player_defense_type",                &battle_config.player_defense_type,                0        },
		{ "monster_defense_type",               &battle_config.monster_defense_type,               0        },
		{ "pet_defense_type",                   &battle_config.pet_defense_type,                   0        },
		{ "magic_defense_type",                 &battle_config.magic_defense_type,                 0        },
		{ "player_skill_reiteration",           &battle_config.pc_skill_reiteration,               0        },
		{ "monster_skill_reiteration",          &battle_config.monster_skill_reiteration,          0        },
		{ "player_skill_nofootset",             &battle_config.pc_skill_nofootset,                 1        },
		{ "monster_skill_nofootset",            &battle_config.monster_skill_nofootset,            0        },
		{ "player_cloak_check_type",            &battle_config.pc_cloak_check_type,                0        },
		{ "monster_cloak_check_type",           &battle_config.monster_cloak_check_type,           1        },
		{ "gvg_short_attack_damage_rate",       &battle_config.gvg_short_damage_rate,              100      },
		{ "gvg_long_attack_damage_rate",        &battle_config.gvg_long_damage_rate,               60       },
		{ "gvg_normal_attack_damage_rate",      &battle_config.gvg_normalskill_damage_rate,        60       },
		{ "gvg_magic_attack_damage_rate",       &battle_config.gvg_magic_damage_rate,              60       },
		{ "gvg_misc_attack_damage_rate",        &battle_config.gvg_misc_damage_rate,               60       },
		{ "gvg_eliminate_time",                 &battle_config.gvg_eliminate_time,                 7000     },
		{ "mob_changetarget_byskill",           &battle_config.mob_changetarget_byskill,           0        },
		{ "gvg_edp_down_rate",                  &battle_config.gvg_edp_down_rate,                  100      },
		{ "pvp_edp_down_rate",                  &battle_config.pvp_edp_down_rate,                  100      },
		{ "pk_edp_down_rate",                   &battle_config.pk_edp_down_rate,                   100      },
		{ "gvg_chargeattack_move",              &battle_config.gvg_chargeattack_move,              0        },
		{ "player_attack_direction_change",     &battle_config.pc_attack_direction_change,         1        },
		{ "monster_attack_direction_change",    &battle_config.monster_attack_direction_change,    0        },
		{ "player_land_skill_limit",            &battle_config.pc_land_skill_limit,                1        },
		{ "monster_land_skill_limit",           &battle_config.monster_land_skill_limit,           1        },
		{ "party_skill_penalty",                &battle_config.party_skill_penalty,                1        },
		{ "monster_class_change_full_recover",  &battle_config.monster_class_change_full_recover,  1        },
		{ "produce_item_name_input",            &battle_config.produce_item_name_input,            0        },
		{ "produce_potion_name_input",          &battle_config.produce_potion_name_input,          1        },
		{ "making_arrow_name_input",            &battle_config.making_arrow_name_input,            0        },
		{ "holywater_name_input",               &battle_config.holywater_name_input,               0        },
		{ "display_delay_skill_fail",           &battle_config.display_delay_skill_fail,           0        },
		{ "display_snatcher_skill_fail",        &battle_config.display_snatcher_skill_fail,        1        },
		{ "chat_warpportal",                    &battle_config.chat_warpportal,                    0        },
		{ "mob_warpportal",                     &battle_config.mob_warpportal,                     0        },
		{ "dead_branch_active",                 &battle_config.dead_branch_active,                 1        },
		{ "vending_max_value",                  &battle_config.vending_max_value,                  99990000 },
		{ "pet_lootitem",                       &battle_config.pet_lootitem,                       0        },
		{ "pet_weight",                         &battle_config.pet_weight,                         1000     },
		{ "show_steal_in_same_party",           &battle_config.show_steal_in_same_party,           0        },
		{ "enable_upper_class",                 &battle_config.enable_upper_class,                 1        },
		{ "pet_attack_attr_none",               &battle_config.pet_attack_attr_none,               0        },
		{ "mob_attack_attr_none",               &battle_config.mob_attack_attr_none,               1        },
		{ "pc_attack_attr_none",                &battle_config.pc_attack_attr_none,                0        },
		{ "gx_allhit",                          &battle_config.gx_allhit,                          0        },
		{ "gx_cardfix",                         &battle_config.gx_cardfix,                         0        },
		{ "gx_dupele",                          &battle_config.gx_dupele,                          1        },
		{ "gx_disptype",                        &battle_config.gx_disptype,                        1        },
		{ "devotion_level_difference",          &battle_config.devotion_level_difference,          10       },
		{ "player_skill_partner_check",         &battle_config.player_skill_partner_check,         1        },
		{ "sole_concert_type",                  &battle_config.sole_concert_type,                  2        },
		{ "hide_GM_session",                    &battle_config.hide_GM_session,                    0        },
		{ "invite_request_check",               &battle_config.invite_request_check,               1        },
		{ "gvg_trade_request_refused",          &battle_config.gvg_trade_request_refused,          1        },
		{ "pvp_trade_request_refused",          &battle_config.pvp_trade_request_refused,          1        },
		{ "skill_removetrap_type",              &battle_config.skill_removetrap_type,              0        },
		{ "disp_experience",                    &battle_config.disp_experience,                    1        },
		{ "castle_defense_rate",                &battle_config.castle_defense_rate,                100      },
		{ "riding_weight",                      &battle_config.riding_weight,                      10000    },
		{ "hp_rate",                            &battle_config.hp_rate,                            100      },
		{ "sp_rate",                            &battle_config.sp_rate,                            100      },
		{ "gm_can_drop_lv",                     &battle_config.gm_can_drop_lv,                     0        },
		{ "disp_hpmeter",                       &battle_config.disp_hpmeter,                       0        },
		{ "bone_drop",                          &battle_config.bone_drop,                          0        },
		{ "bone_drop_itemid",                   &battle_config.bone_drop_itemid,                   7005     },
		{ "item_rate_details",                  &battle_config.item_rate_details,                  0        },
		{ "item_rate_1",                        &battle_config.item_rate_1,                        100      },
		{ "item_rate_10",                       &battle_config.item_rate_10,                       100      },
		{ "item_rate_100",                      &battle_config.item_rate_100,                      100      },
		{ "item_rate_1000",                     &battle_config.item_rate_1000,                     100      },
		{ "item_rate_1_min",                    &battle_config.item_rate_1_min,                    1        },
		{ "item_rate_1_max",                    &battle_config.item_rate_1_max,                    9        },
		{ "item_rate_10_min",                   &battle_config.item_rate_10_min,                   10       },
		{ "item_rate_10_max",                   &battle_config.item_rate_10_max,                   99       },
		{ "item_rate_100_min",                  &battle_config.item_rate_100_min,                  100      },
		{ "item_rate_100_max",                  &battle_config.item_rate_100_max,                  999      },
		{ "item_rate_1000_min",                 &battle_config.item_rate_1000_min,                 1000     },
		{ "item_rate_1000_max",                 &battle_config.item_rate_1000_max,                 10000    },
		{ "monster_damage_delay",               &battle_config.monster_damage_delay,               0        },
		{ "card_drop_rate",                     &battle_config.card_drop_rate,                     100      },
		{ "equip_drop_rate",                    &battle_config.equip_drop_rate,                    100      },
		{ "consume_drop_rate",                  &battle_config.consume_drop_rate,                  100      },
		{ "refine_drop_rate",                   &battle_config.refine_drop_rate,                   100      },
		{ "etc_drop_rate",                      &battle_config.etc_drop_rate,                      100      },
		{ "potion_drop_rate",                   &battle_config.potion_drop_rate,                   100      },
		{ "arrow_drop_rate",                    &battle_config.arrow_drop_rate,                    100      },
		{ "petequip_drop_rate",                 &battle_config.petequip_drop_rate,                 100      },
		{ "weapon_drop_rate",                   &battle_config.weapon_drop_rate,                   100      },
		{ "other_drop_rate",                    &battle_config.other_drop_rate,                    100      },
		{ "item_res",                           &battle_config.item_res,                           1        },
		{ "next_exp_limit",                     &battle_config.next_exp_limit,                     0        },
		{ "monster_skill_over",                 &battle_config.monster_skill_over,                 10       },
		{ "finding_ore_drop_rate",              &battle_config.finding_ore_drop_rate,              100      },
		{ "joint_struggle_exp_bonus",           &battle_config.joint_struggle_exp_bonus,           25       },
		{ "joint_struggle_limit",               &battle_config.joint_struggle_limit,               600      },
		{ "pt_bonus_b",                         &battle_config.pt_bonus_b,                         0        },
		{ "pt_bonus_j",                         &battle_config.pt_bonus_j,                         0        },
		{ "mvp_announce",                       &battle_config.mvp_announce,                       0        },
		{ "petowneditem",                       &battle_config.petowneditem,                       0        },
		{ "pet_loot_type",                      &battle_config.pet_loot_type,                      1        },
		{ "buyer_name",                         &battle_config.buyer_name,                         0        },
		{ "noportal_flag",                      &battle_config.noportal_flag,                      1        },
		{ "once_autospell",                     &battle_config.once_autospell,                     1        },
		{ "allow_same_autospell",               &battle_config.allow_same_autospell,               1        },
		{ "combo_delay_lower_limits",           &battle_config.combo_delay_lower_limits,           0        },
		{ "tkcombo_delay_lower_limits",         &battle_config.tkcombo_delay_lower_limits,         0        },
		{ "new_marrige_skill",                  &battle_config.new_marrige_skill,                  1        },
		{ "reveff_plus_addeff",                 &battle_config.reveff_plus_addeff,                 0        },
		{ "summonslave_no_drop",                &battle_config.summonslave_no_drop,                0        },
		{ "summonslave_no_exp",                 &battle_config.summonslave_no_exp,                 0        },
		{ "summonslave_no_mvp",                 &battle_config.summonslave_no_mvp,                 0        },
		{ "summonmonster_no_drop",              &battle_config.summonmonster_no_drop,              0        },
		{ "summonmonster_no_exp",               &battle_config.summonmonster_no_exp,               0        },
		{ "summonmonster_no_mvp",               &battle_config.summonmonster_no_mvp,               0        },
		{ "cannibalize_no_drop",                &battle_config.cannibalize_no_drop,                1        },
		{ "cannibalize_no_exp",                 &battle_config.cannibalize_no_exp,                 1        },
		{ "cannibalize_no_mvp",                 &battle_config.cannibalize_no_mvp,                 1        },
		{ "spheremine_no_drop",                 &battle_config.spheremine_no_drop,                 1        },
		{ "spheremine_no_exp",                  &battle_config.spheremine_no_exp,                  1        },
		{ "spheremine_no_mvp",                  &battle_config.spheremine_no_mvp,                  1        },
		{ "branch_mob_no_drop",                 &battle_config.branch_mob_no_drop,                 0        },
		{ "branch_mob_no_exp",                  &battle_config.branch_mob_no_exp,                  0        },
		{ "branch_mob_no_mvp",                  &battle_config.branch_mob_no_mvp,                  0        },
		{ "branch_boss_no_drop",                &battle_config.branch_boss_no_drop,                0        },
		{ "branch_boss_no_exp",                 &battle_config.branch_boss_no_exp,                 0        },
		{ "branch_boss_no_mvp",                 &battle_config.branch_boss_no_mvp,                 0        },
		{ "pc_hit_stop_type",                   &battle_config.pc_hit_stop_type,                   0        },
		{ "nomanner_mode",                      &battle_config.nomanner_mode,                      1        },
		{ "death_by_unrig_penalty",             &battle_config.death_by_unrig_penalty,             0        },
		{ "dance_and_play_duration",            &battle_config.dance_and_play_duration,            20000    },
		{ "soulcollect_max_fail",               &battle_config.soulcollect_max_fail,               0        },
		{ "gvg_flee_rate",                      &battle_config.gvg_flee_rate,                      100      },
		{ "gvg_flee_penalty",                   &battle_config.gvg_flee_penalty,                   0        },
		{ "equip_sex",                          &battle_config.equip_sex,                          0        },
		{ "noexp_hiding",                       &battle_config.noexp_hiding,                       0        },
		{ "noexp_trickdead",                    &battle_config.noexp_trickdead,                    1        },
		{ "hide_attack",                        &battle_config.hide_attack,                        1        },
		{ "gm_hide_attack_lv",                  &battle_config.gm_hide_attack_lv,                  1        },
		{ "weapon_attack_autospell",            &battle_config.weapon_attack_autospell,            0        },
		{ "magic_attack_autospell",             &battle_config.magic_attack_autospell,             0        },
		{ "misc_attack_autospell",              &battle_config.misc_attack_autospell,              0        },
		{ "magic_attack_drain",                 &battle_config.magic_attack_drain,                 1        },
		{ "misc_attack_drain",                  &battle_config.misc_attack_drain,                  1        },
		{ "magic_attack_drain_enable_type",     &battle_config.magic_attack_drain_enable_type,     2        },
		{ "misc_attack_drain_enable_type",      &battle_config.misc_attack_drain_enable_type,      2        },
		{ "hallucianation_off",                 &battle_config.hallucianation_off,                 0        },
		{ "weapon_reflect_autospell",           &battle_config.weapon_reflect_autospell,           1        },
		{ "magic_reflect_autospell",            &battle_config.magic_reflect_autospell,            0        },
		{ "weapon_reflect_drain",               &battle_config.weapon_reflect_drain,               1        },
		{ "weapon_reflect_drain_enable_type",   &battle_config.weapon_reflect_drain_enable_type,   2        },
		{ "magic_reflect_drain",                &battle_config.magic_reflect_drain,                0        },
		{ "magic_reflect_drain_enable_type",    &battle_config.magic_reflect_drain_enable_type,    2        },
		{ "max_parameter_str",                  &battle_config.max_parameter_str,                  999      },
		{ "max_parameter_agi",                  &battle_config.max_parameter_agi,                  999      },
		{ "max_parameter_vit",                  &battle_config.max_parameter_vit,                  999      },
		{ "max_parameter_int",                  &battle_config.max_parameter_int,                  999      },
		{ "max_parameter_dex",                  &battle_config.max_parameter_dex,                  999      },
		{ "max_parameter_luk",                  &battle_config.max_parameter_luk,                  999      },
		{ "cannibalize_nocost",                 &battle_config.cannibalize_nocost,                 0        },
		{ "spheremine_nocost",                  &battle_config.spheremine_nocost,                  0        },
		{ "demonstration_nocost",               &battle_config.demonstration_nocost,               0        },
		{ "acidterror_nocost",                  &battle_config.acidterror_nocost,                  0        },
		{ "aciddemonstration_nocost",           &battle_config.aciddemonstration_nocost,           0        },
		{ "chemical_nocost",                    &battle_config.chemical_nocost,                    0        },
		{ "slimpitcher_nocost",                 &battle_config.slimpitcher_nocost,                 0        },
		{ "mes_send_type",                      &battle_config.mes_send_type,                      0        },
		{ "allow_assumptop_in_gvg",             &battle_config.allow_assumptop_in_gvg,             1        },
		{ "allow_falconassault_elemet",         &battle_config.allow_falconassault_elemet,         0        },
		{ "allow_guild_invite_in_gvg",          &battle_config.allow_guild_invite_in_gvg,          0        },
		{ "allow_guild_leave_in_gvg",           &battle_config.allow_guild_leave_in_gvg,           0        },
		{ "allow_guild_alliance_in_agit",       &battle_config.allow_guild_alliance_in_agit,       0        },
		{ "guild_skill_available",              &battle_config.guild_skill_available,              1        },
		{ "guild_hunting_skill_available",      &battle_config.guild_hunting_skill_available,      1        },
		{ "guild_skill_check_range",            &battle_config.guild_skill_check_range,            0        },
		{ "allow_guild_skill_in_gvg_only",      &battle_config.allow_guild_skill_in_gvg_only,      1        },
		{ "allow_me_guild_skill",               &battle_config.allow_me_guild_skill,               0        },
		{ "emergencycall_point_type",           &battle_config.emergencycall_point_type,           1        },
		{ "emergencycall_call_limit",           &battle_config.emergencycall_call_limit,           0        },
		{ "allow_guild_skill_in_gvgtime_only",  &battle_config.allow_guild_skill_in_gvgtime_only,  0        },
		{ "guild_skill_in_pvp_limit",           &battle_config.guild_skill_in_pvp_limit,           1        },
		{ "guild_exp_rate",                     &battle_config.guild_exp_rate,                     100      },
		{ "guild_skill_effective_range",        &battle_config.guild_skill_effective_range,        2        },
		{ "tarotcard_display_position",         &battle_config.tarotcard_display_position,         2        },
		{ "serverside_friendlist",              &battle_config.serverside_friendlist,              1        },
		{ "pet0078_hair_id",                    &battle_config.pet0078_hair_id,                    100      },
		{ "job_soul_check",                     &battle_config.job_soul_check,                     1        },
		{ "repeal_die_counter_rate",            &battle_config.repeal_die_counter_rate,            100      },
		{ "disp_job_soul_state_change",         &battle_config.disp_job_soul_state_change,         0        },
		{ "check_knowlege_map",                 &battle_config.check_knowlege_map,                 1        },
		{ "tripleattack_rate_up_keeptime",      &battle_config.tripleattack_rate_up_keeptime,      2000     },
		{ "tk_counter_rate_up_keeptime",        &battle_config.tk_counter_rate_up_keeptime,        2000     },
		{ "allow_skill_without_day",            &battle_config.allow_skill_without_day,            0        },
		{ "save_feel_map",                      &battle_config.save_feel_map,                      1        },
		{ "save_hate_mob",                      &battle_config.save_hate_mob,                      1        },
		{ "twilight_party_check",               &battle_config.twilight_party_check,               1        },
		{ "alchemist_point_type",               &battle_config.alchemist_point_type,               0        },
		{ "marionette_type",                    &battle_config.marionette_type,                    0        },
		{ "max_marionette_str",                 &battle_config.max_marionette_str,                 99       },
		{ "max_marionette_agi",                 &battle_config.max_marionette_agi,                 99       },
		{ "max_marionette_vit",                 &battle_config.max_marionette_vit,                 99       },
		{ "max_marionette_int",                 &battle_config.max_marionette_int,                 99       },
		{ "max_marionette_dex",                 &battle_config.max_marionette_dex,                 99       },
		{ "max_marionette_luk",                 &battle_config.max_marionette_luk,                 99       },
		{ "max_marionette_pk_str",              &battle_config.max_marionette_pk_str,              99       },
		{ "max_marionette_pk_agi",              &battle_config.max_marionette_pk_agi,              99       },
		{ "max_marionette_pk_vit",              &battle_config.max_marionette_pk_vit,              99       },
		{ "max_marionette_pk_int",              &battle_config.max_marionette_pk_int,              99       },
		{ "max_marionette_pk_dex",              &battle_config.max_marionette_pk_dex,              99       },
		{ "max_marionette_pk_luk",              &battle_config.max_marionette_pk_luk,              99       },
		{ "max_marionette_pvp_str",             &battle_config.max_marionette_pvp_str,             99       },
		{ "max_marionette_pvp_agi",             &battle_config.max_marionette_pvp_agi,             99       },
		{ "max_marionette_pvp_vit",             &battle_config.max_marionette_pvp_vit,             99       },
		{ "max_marionette_pvp_int",             &battle_config.max_marionette_pvp_int,             99       },
		{ "max_marionette_pvp_dex",             &battle_config.max_marionette_pvp_dex,             99       },
		{ "max_marionette_pvp_luk",             &battle_config.max_marionette_pvp_luk,             99       },
		{ "max_marionette_gvg_str",             &battle_config.max_marionette_gvg_str,             99       },
		{ "max_marionette_gvg_agi",             &battle_config.max_marionette_gvg_agi,             99       },
		{ "max_marionette_gvg_vit",             &battle_config.max_marionette_gvg_vit,             99       },
		{ "max_marionette_gvg_int",             &battle_config.max_marionette_gvg_int,             99       },
		{ "max_marionette_gvg_dex",             &battle_config.max_marionette_gvg_dex,             99       },
		{ "max_marionette_gvg_luk",             &battle_config.max_marionette_gvg_luk,             99       },
		{ "baby_status_max",                    &battle_config.baby_status_max,                    80       },
		{ "baby_hp_rate",                       &battle_config.baby_hp_rate,                       70       },
		{ "baby_sp_rate",                       &battle_config.baby_sp_rate,                       70       },
		{ "upper_hp_rate",                      &battle_config.upper_hp_rate,                      125      },
		{ "upper_sp_rate",                      &battle_config.upper_sp_rate,                      125      },
		{ "normal_hp_rate",                     &battle_config.normal_hp_rate,                     100      },
		{ "normal_sp_rate",                     &battle_config.normal_sp_rate,                     100      },
		{ "baby_weight_rate",                   &battle_config.baby_weight_rate,                   100      },
		{ "upper_weight_rate",                  &battle_config.upper_weight_rate,                  100      },
		{ "normal_weight_rate",                 &battle_config.normal_weight_rate,                 100      },
		{ "no_emergency_call",                  &battle_config.no_emergency_call,                  0        },
		{ "save_am_pharmacy_success",           &battle_config.save_am_pharmacy_success,           1        },
		{ "save_all_ranking_point_when_logout", &battle_config.save_all_ranking_point_when_logout, 0        },
		{ "soul_linker_battle_mode",            &battle_config.soul_linker_battle_mode,            0        },
		{ "soul_linker_battle_mode_ka",         &battle_config.soul_linker_battle_mode_ka,         0        },
		{ "skillup_type",                       &battle_config.skillup_type,                       1        },
		{ "allow_me_dance_effect",              &battle_config.allow_me_dance_effect,              0        },
		{ "allow_me_concert_effect",            &battle_config.allow_me_concert_effect,            0        },
		{ "allow_me_rokisweil",                 &battle_config.allow_me_rokisweil,                 0        },
		{ "pharmacy_get_point_type",            &battle_config.pharmacy_get_point_type,            0        },
		{ "soulskill_can_be_used_for_myself",   &battle_config.soulskill_can_be_used_for_myself,   0        },
		{ "hermode_wp_check_range",             &battle_config.hermode_wp_check_range,             3        },
		{ "hermode_wp_check",                   &battle_config.hermode_wp_check,                   1        },
		{ "hermode_no_walking",                 &battle_config.hermode_no_walking,                 0        },
		{ "hermode_gvg_only",                   &battle_config.hermode_gvg_only,                   1        },
		{ "redemptio_penalty_type",             &battle_config.redemptio_penalty_type,             1        },
		{ "allow_weaponrearch_to_weaponrefine", &battle_config.allow_weaponrearch_to_weaponrefine, 0        },
		{ "boss_no_knockbacking",               &battle_config.boss_no_knockbacking,               1        },
		{ "boss_no_element_change",             &battle_config.boss_no_element_change,             1        },
		{ "boss_teleport_on_landprotector",     &battle_config.boss_teleport_on_landprotector,     1        },
		{ "scroll_produce_rate",                &battle_config.scroll_produce_rate,                100      },
		{ "scroll_item_name_input",             &battle_config.scroll_item_name_input,             0        },
		{ "pet_leave",                          &battle_config.pet_leave,                          1        },
		{ "pk_short_attack_damage_rate",        &battle_config.pk_short_damage_rate,               100      },
		{ "pk_long_attack_damage_rate",         &battle_config.pk_long_damage_rate,                60       },
		{ "pk_normal_attack_damage_rate",       &battle_config.pk_normalskill_damage_rate,         60       },
		{ "pk_magic_attack_damage_rate",        &battle_config.pk_magic_damage_rate,               60       },
		{ "pk_misc_attack_damage_rate",         &battle_config.pk_misc_damage_rate,                60       },
		{ "cooking_rate",                       &battle_config.cooking_rate,                       100      },
		{ "making_rate",                        &battle_config.making_rate,                        100      },
		{ "extended_abracadabra",               &battle_config.extended_abracadabra,               0        },
		{ "no_pk_level",                        &battle_config.no_pk_level,                        60       },
		{ "allow_cloneskill_at_autospell",      &battle_config.allow_cloneskill_at_autospell,      0        },
		{ "pk_noshift",                         &battle_config.pk_noshift,                         0        },
		{ "pk_penalty_time",                    &battle_config.pk_penalty_time,                    60000    },
		{ "dropitem_itemrate_fix",              &battle_config.dropitem_itemrate_fix,              1        },
		{ "gm_nomanner_lv",                     &battle_config.gm_nomanner_lv,                     50       },
		{ "clif_fixpos_type",                   &battle_config.clif_fixpos_type,                   1        },
		{ "romailuse",                          &battle_config.romail,                             0        },
		{ "pc_die_script",                      &battle_config.pc_die_script,                      0        },
		{ "pc_kill_script",                     &battle_config.pc_kill_script,                     0        },
		{ "pc_movemap_script",                  &battle_config.pc_movemap_script,                  0        },
		{ "pc_login_script",                    &battle_config.pc_login_script,                    0        },
		{ "pc_logout_script",                   &battle_config.pc_logout_script,                   0        },
		{ "pc_mapin_script",                    &battle_config.pc_mapin_script,                    0        },
		{ "pc_mapout_script",                   &battle_config.pc_mapout_script,                   0        },
		{ "md_delete_script",                   &battle_config.md_delete_script,                   0        },
		{ "save_pckiller_type",                 &battle_config.save_pckiller_type,                 0        },
		{ "def_ratio_atk_to_shieldchain",       &battle_config.def_ratio_atk_to_shieldchain,       0        },
		{ "def_ratio_atk_to_carttermination",   &battle_config.def_ratio_atk_to_carttermination,   1        },
		{ "player_gravitation_type",            &battle_config.player_gravitation_type,            0        },
		{ "enemy_gravitation_type",             &battle_config.enemy_gravitation_type,             0        },
		{ "mob_attack_fixwalkpos",              &battle_config.mob_attack_fixwalkpos,              0        },
		{ "mob_ai_limiter",                     &battle_config.mob_ai_limiter,                     0        },
		{ "mob_ai_cpu_usage",                   &battle_config.mob_ai_cpu_usage,                   80       },
		{ "itemidentify",                       &battle_config.itemidentify,                       0        },
		{ "casting_penalty_type",               &battle_config.casting_penalty_type,               0        },
		{ "casting_penalty_weapon",             &battle_config.casting_penalty_weapon,             0        },
		{ "casting_penalty_shield",             &battle_config.casting_penalty_shield,             0        },
		{ "casting_penalty_armor",              &battle_config.casting_penalty_armor,              0        },
		{ "casting_penalty_helm",               &battle_config.casting_penalty_helm,               0        },
		{ "casting_penalty_robe",               &battle_config.casting_penalty_robe,               0        },
		{ "casting_penalty_shoes",              &battle_config.casting_penalty_shoes,              0        },
		{ "casting_penalty_acce",               &battle_config.casting_penalty_acce,               0        },
		{ "casting_penalty_arrow",              &battle_config.casting_penalty_arrow,              0        },
		{ "show_always_party_name",             &battle_config.show_always_party_name,             0        },
		{ "check_player_name_global_msg",       &battle_config.check_player_name_global_msg,       0        },
		{ "check_player_name_party_msg",        &battle_config.check_player_name_party_msg,        0        },
		{ "check_player_name_guild_msg",        &battle_config.check_player_name_guild_msg,        0        },
		{ "check_player_name_battle_msg",       &battle_config.check_player_name_battle_msg,       0        },
		{ "save_player_when_drop_item",         &battle_config.save_player_when_drop_item,         0        },
		{ "save_player_when_storage_closed",    &battle_config.save_player_when_storage_closed,    0        },
		{ "allow_homun_status_change",          &battle_config.allow_homun_status_change,          0        },
		{ "save_homun_temporal_intimate",       &battle_config.save_homun_temporal_intimate,       1        },
		{ "homun_intimate_rate",                &battle_config.homun_intimate_rate,                100      },
		{ "homun_temporal_intimate_resilience", &battle_config.homun_temporal_intimate_resilience, 50       },
		{ "hvan_explosion_intimate",            &battle_config.hvan_explosion_intimate,            45000    },
		{ "homun_speed_is_same_as_pc",          &battle_config.homun_speed_is_same_as_pc,          1        },
		{ "homun_skill_intimate_type",          &battle_config.homun_skill_intimate_type,          0        },
		{ "master_get_homun_base_exp",          &battle_config.master_get_homun_base_exp,          100      },
		{ "master_get_homun_job_exp",           &battle_config.master_get_homun_job_exp,           0        },
		{ "extra_system_flag",                  &battle_config.extra_system_flag,                  0        },
		{ "mob_take_over_sp",                   &battle_config.mob_take_over_sp,                   0        },
		{ "party_join_limit",                   &battle_config.party_join_limit,                   1        },
		{ "check_skillpos_range",               &battle_config.check_skillpos_range,               0        },
		{ "pet_speed_is_same_as_pc",            &battle_config.pet_speed_is_same_as_pc,            1        },
		{ "tax_rate",                           &battle_config.tax_rate,                           0        },
		{ "steal_rate",                         &battle_config.steal_rate,                         100      },
		{ "sw_def_type",                        &battle_config.sw_def_type,                        2        },
		{ "calc_dist_flag",                     &battle_config.calc_dist_flag,                     1        },
		{ "allow_sw_dist",                      &battle_config.allow_sw_dist,                      4        },
		{ "personal_storage_sort",              &battle_config.personal_storage_sort,              1        },
		{ "guild_storage_sort",                 &battle_config.guild_storage_sort,                 1        },
		{ "allow_es_magic_all",                 &battle_config.allow_es_magic_all,                 0        },
		{ "trap_is_invisible",                  &battle_config.trap_is_invisible,                  0        },
		{ "anklesnare_no_knockbacking",         &battle_config.anklesnare_no_knockbacking,         1        },
		{ "gm_perfect_hide",                    &battle_config.gm_perfect_hide,                    0        },
		{ "pcview_mob_clear_type",              &battle_config.pcview_mob_clear_type,              1        },
		{ "party_item_share_type",              &battle_config.party_item_share_type,              1        },
		{ "party_item_share_show",              &battle_config.party_item_share_show,              1        },
		{ "pk_murderer_point",                  &battle_config.pk_murderer_point,                  100      },
		{ "sg_miracle_rate",                    &battle_config.sg_miracle_rate,                    1        },
		{ "sg_angel_rate",                      &battle_config.sg_angel_rate,                      2        },
		{ "baby_copy_skilltree",                &battle_config.baby_copy_skilltree,                1        },
		{ "skill_autospell_delay_enable",       &battle_config.skill_autospell_delay_enable,       1        },
		{ "bonus_autospell_delay_enable",       &battle_config.bonus_autospell_delay_enable,       1        },
		{ "merc_speed_is_same_as_pc",           &battle_config.merc_speed_is_same_as_pc,           1        },
		{ "master_get_merc_base_exp",           &battle_config.master_get_merc_base_exp,           100      },
		{ "master_get_merc_job_exp",            &battle_config.master_get_merc_job_exp,            0        },
		{ "party_invite_range_check",           &battle_config.party_invite_range_check,           0        },
		{ "homun_skilldelay_reset",             &battle_config.homun_skilldelay_reset,             1        },
		{ "homun_statuschange_reset",           &battle_config.homun_statuschange_reset,           1        },
		{ "free_sc_data_dynamically",           &battle_config.free_sc_data_dynamically,           0        },
		{ "snovice_maxexp_border",              &battle_config.snovice_maxexp_border,              99999999 },
		{ "homun_rename",                       &battle_config.homun_rename,                       0        },
		{ "equip_window_type",                  &battle_config.equip_window_type,                  1        },
		{ "str_weight",                         &battle_config.str_weight,                         300      },
		{ "summonslave_generation",             &battle_config.summonslave_generation,             2        },
		{ "pvp_send_guild_xy",                  &battle_config.pvp_send_guild_xy,                  1        },
		{ "mvpitem_weight_limit",               &battle_config.mvpitem_weight_limit,               50       },
		{ "roki_item_autospell",                &battle_config.roki_item_autospell,                0        },
		{ "trap_splash_on",                     &battle_config.trap_splash_on,                     0        },
		{ "firepillar_splash_on",               &battle_config.firepillar_splash_on,               0        },
		{ "mob_nohitstop_rate",                 &battle_config.mob_nohitstop_rate,                 0        },
		{ "refinery_research_lv",               &battle_config.refinery_research_lv,               0        },
		{ "maprespawnguildid_all_players",      &battle_config.maprespawnguildid_all_players,      0        },
		{ "party_booking_lv",                   &battle_config.party_booking_lv,                   15       },
		{ "new_statusup_calc",                  &battle_config.new_statusup_calc,                  1        },
		{ "third_status_max",                   &battle_config.third_status_max,                   120      },
		{ "third_baby_status_max",              &battle_config.third_baby_status_max,              108      },
		{ "third_max_aspd",                     &battle_config.third_max_aspd,                     140      },
		{ "third_song_overlap",                 &battle_config.third_song_overlap,                 0        },
		{ "clif_fix_level",                     &battle_config.clif_fix_level,                     0        },
		{ "get_status_point_over_lv100",        &battle_config.get_status_point_over_lv100,        1        },
		{ "max_buyingstore_zeny",               &battle_config.max_buyingstore_zeny,               99990000 },
		{ "max_buyingstore_amount",             &battle_config.max_buyingstore_amount,             9999     },
		{ "allow_same_activeitem",              &battle_config.allow_same_activeitem,              0        },
		{ "disable_transform_when_gvg",         &battle_config.disable_transform_when_gvg,         1        },
		{ "esnv_status_max",                    &battle_config.esnv_status_max,                    120      },
		{ "esnv_baby_status_max",               &battle_config.esnv_baby_status_max,               108      },
		{ "esnv_max_aspd",                      &battle_config.esnv_max_aspd,                      140      },
		{ "ko_status_max",                      &battle_config.ko_status_max,                      120      },
		{ "ko_max_aspd",                        &battle_config.ko_max_aspd,                        140      },
		{ "sum_status_max",                     &battle_config.sum_status_max,                     125      },
		{ "sum_max_aspd",                       &battle_config.sum_max_aspd,                       140      },
		{ "disable_costume_when_gvg",           &battle_config.disable_costume_when_gvg,           1        },
		{ "elem_attackskill_rate",              &battle_config.elem_attackskill_rate,              500      },
		{ "slave_inherit_mode",                 &battle_config.slave_inherit_mode,                 2        },
		{ "no_casting_int",                     &battle_config.no_cast_int,                        115      },
		{ "monster_atk2_to_matk",               &battle_config.monster_atk2_to_matk,               1        },
		{ "npc_timeout_time",                   &battle_config.npc_timeout_time,                   60       },
		{ "use_packet_obfuscation",             &battle_config.use_packet_obfuscation,             1        },
		{ "greed_use_town",                     &battle_config.greed_use_town,                     0        },
		{ "alliance_message",                   &battle_config.alliance_message,                   0        },
		{ "ranker_potion_bonus",                &battle_config.ranker_potion_bonus,                150      },
		{ "ranker_potion_bonus_rogue",          &battle_config.ranker_potion_bonus_rogue,          200      },
		{ "ranker_weapon_bonus",                &battle_config.ranker_weapon_bonus,                10       },
		{ "min_lv100_aspdfix",                  &battle_config.min_lv100_aspdfix,                  1        },
		{ "min_npc_vendchat_distance",          &battle_config.min_npc_vendchat_distance,          3        },
		{ NULL,                                 NULL,                                              0        },
	};

	if(count++ == 0) {
		for(i=0; data[i].val; i++) {
			*data[i].val = data[i].defval;
		}
	}

	fp = fopen(cfgName,"r");
	if(fp == NULL) {
		printf("battle_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}
	while(fgets(line,1020,fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line,"%1023[^:]:%1023s",w1,w2) != 2)
			continue;

		if(strcmpi(w1,"import") == 0) {
			battle_config_read(w2);
		} else {
			for(i=0; data[i].val; i++) {
				if(strcmpi(w1,data[i].str) == 0) {
					*data[i].val = battle_config_switch(w2);
					break;
				}
			}
			if(data[i].val == NULL)
				printf("unknown battle config : %s\a\n",w1);
		}
	}
	fclose(fp);

	// ƒtƒ‰ƒO’²®
	if(battle_config.allow_guild_skill_in_gvgtime_only)
		battle_config.guild_skill_available = 0;

	if(--count == 0) {
		if(battle_config.flooritem_lifetime < 1000)
			battle_config.flooritem_lifetime = 60*1000;
		if(battle_config.restart_hp_rate < 0)
			battle_config.restart_hp_rate = 0;
		else if(battle_config.restart_hp_rate > 100)
			battle_config.restart_hp_rate = 100;
		if(battle_config.restart_sp_rate < 0)
			battle_config.restart_sp_rate = 0;
		else if(battle_config.restart_sp_rate > 100)
			battle_config.restart_sp_rate = 100;
		if(battle_config.natural_healhp_interval < NATURAL_HEAL_INTERVAL)
			battle_config.natural_healhp_interval = NATURAL_HEAL_INTERVAL;
		if(battle_config.natural_healsp_interval < NATURAL_HEAL_INTERVAL)
			battle_config.natural_healsp_interval = NATURAL_HEAL_INTERVAL;
		if(battle_config.natural_heal_skill_interval < NATURAL_HEAL_INTERVAL)
			battle_config.natural_heal_skill_interval = NATURAL_HEAL_INTERVAL;
		if(battle_config.natural_heal_weight_rate < 50)
			battle_config.natural_heal_weight_rate = 50;
		else if(battle_config.natural_heal_weight_rate > 101)
			battle_config.natural_heal_weight_rate = 101;
		if(battle_config.hp_rate < 0)
			battle_config.hp_rate = 1;
		if(battle_config.sp_rate < 0)
			battle_config.sp_rate = 1;
		if(battle_config.max_hp > 1000000)
			battle_config.max_hp = 1000000;
		else if(battle_config.max_hp < 100)
			battle_config.max_hp = 100;
		if(battle_config.max_sp > 1000000)
			battle_config.max_sp = 1000000;
		else if(battle_config.max_sp < 100)
			battle_config.max_sp = 100;

		if(battle_config.max_parameter < 10)
			battle_config.max_parameter = 10;
		else if(battle_config.max_parameter > 10000)
			battle_config.max_parameter = 10000;
		if(battle_config.max_parameter_str < 1)
			battle_config.max_parameter_str = 1;
		else if(battle_config.max_parameter_str > battle_config.max_parameter)
			battle_config.max_parameter_str = battle_config.max_parameter;
		if(battle_config.max_parameter_agi < 1)
			battle_config.max_parameter_agi = 1;
		else if(battle_config.max_parameter_agi > battle_config.max_parameter)
			battle_config.max_parameter_agi = battle_config.max_parameter;
		if(battle_config.max_parameter_vit < 1)
			battle_config.max_parameter_vit = 1;
		else if(battle_config.max_parameter_vit > battle_config.max_parameter)
			battle_config.max_parameter_vit = battle_config.max_parameter;
		if(battle_config.max_parameter_int < 1)
			battle_config.max_parameter_int = 1;
		else if(battle_config.max_parameter_int > battle_config.max_parameter)
			battle_config.max_parameter_int = battle_config.max_parameter;
		if(battle_config.max_parameter_dex < 1)
			battle_config.max_parameter_dex = 1;
		else if(battle_config.max_parameter_dex > battle_config.max_parameter)
			battle_config.max_parameter_dex = battle_config.max_parameter;
		if(battle_config.max_parameter_luk < 1)
			battle_config.max_parameter_luk = 1;
		else if(battle_config.max_parameter_luk > battle_config.max_parameter)
			battle_config.max_parameter_luk = battle_config.max_parameter;

		if(battle_config.max_cart_weight > 1000000)
			battle_config.max_cart_weight = 1000000;
		else if(battle_config.max_cart_weight < 100)
			battle_config.max_cart_weight = 100;
		battle_config.max_cart_weight *= 10;

		if(battle_config.agi_penalty_count < 2)
			battle_config.agi_penalty_count = 2;
		if(battle_config.vit_penalty_count < 2)
			battle_config.vit_penalty_count = 2;

		if(battle_config.guild_exp_limit > 99)
			battle_config.guild_exp_limit = 99;
		if(battle_config.guild_exp_limit < 0)
			battle_config.guild_exp_limit = 0;
		if(battle_config.pet_weight < 0)
			battle_config.pet_weight = 0;

		if(battle_config.castle_defense_rate < 0)
			battle_config.castle_defense_rate = 0;
		if(battle_config.castle_defense_rate > 100)
			battle_config.castle_defense_rate = 100;

		if(battle_config.next_exp_limit < 0)
			battle_config.next_exp_limit = 0;

		if(battle_config.card_drop_rate < 0)
			battle_config.card_drop_rate = 0;
		if(battle_config.equip_drop_rate < 0)
			battle_config.equip_drop_rate = 0;
		if(battle_config.consume_drop_rate < 0)
			battle_config.consume_drop_rate = 0;
		if(battle_config.refine_drop_rate < 0)
			battle_config.refine_drop_rate = 0;
		if(battle_config.etc_drop_rate < 0)
			battle_config.etc_drop_rate = 0;

		if(battle_config.potion_drop_rate < 0)
			battle_config.potion_drop_rate = 0;
		if(battle_config.arrow_drop_rate < 0)
			battle_config.arrow_drop_rate = 0;
		if(battle_config.petequip_drop_rate < 0)
			battle_config.petequip_drop_rate = 0;
		if(battle_config.weapon_drop_rate < 0)
			battle_config.weapon_drop_rate = 0;
		if(battle_config.other_drop_rate < 0)
			battle_config.other_drop_rate = 0;

		if(battle_config.monster_skill_over < 0)
			battle_config.monster_skill_over = 0;
		if (battle_config.finding_ore_drop_rate < 0)
			battle_config.finding_ore_drop_rate = 0;
		else if (battle_config.finding_ore_drop_rate > 10000)
			battle_config.finding_ore_drop_rate = 10000;

		if(battle_config.max_marionette_str < 1)
			battle_config.max_marionette_str = battle_config.max_parameter;
		if(battle_config.max_marionette_agi < 1)
			battle_config.max_marionette_agi = battle_config.max_parameter;
		if(battle_config.max_marionette_vit < 1)
			battle_config.max_marionette_vit = battle_config.max_parameter;
		if(battle_config.max_marionette_int < 1)
			battle_config.max_marionette_int = battle_config.max_parameter;
		if(battle_config.max_marionette_dex < 1)
			battle_config.max_marionette_dex = battle_config.max_parameter;
		if(battle_config.max_marionette_luk < 1)
			battle_config.max_marionette_luk = battle_config.max_parameter;

		if(battle_config.max_marionette_pk_str < 1)
			battle_config.max_marionette_pk_str = battle_config.max_parameter;
		if(battle_config.max_marionette_pk_agi < 1)
			battle_config.max_marionette_pk_agi = battle_config.max_parameter;
		if(battle_config.max_marionette_pk_vit < 1)
			battle_config.max_marionette_pk_vit = battle_config.max_parameter;
		if(battle_config.max_marionette_pk_int < 1)
			battle_config.max_marionette_pk_int = battle_config.max_parameter;
		if(battle_config.max_marionette_pk_dex < 1)
			battle_config.max_marionette_pk_dex = battle_config.max_parameter;
		if(battle_config.max_marionette_pk_luk < 1)
			battle_config.max_marionette_pk_luk = battle_config.max_parameter;

		if(battle_config.max_marionette_pvp_str < 1)
			battle_config.max_marionette_pvp_str = battle_config.max_parameter;
		if(battle_config.max_marionette_pvp_agi < 1)
			battle_config.max_marionette_pvp_agi = battle_config.max_parameter;
		if(battle_config.max_marionette_pvp_vit < 1)
			battle_config.max_marionette_pvp_vit = battle_config.max_parameter;
		if(battle_config.max_marionette_pvp_int < 1)
			battle_config.max_marionette_pvp_int = battle_config.max_parameter;
		if(battle_config.max_marionette_pvp_dex < 1)
			battle_config.max_marionette_pvp_dex = battle_config.max_parameter;
		if(battle_config.max_marionette_pvp_luk < 1)
			battle_config.max_marionette_pvp_luk = battle_config.max_parameter;

		if(battle_config.max_marionette_gvg_str < 1)
			battle_config.max_marionette_gvg_str = battle_config.max_parameter;
		if(battle_config.max_marionette_gvg_agi < 1)
			battle_config.max_marionette_gvg_agi = battle_config.max_parameter;
		if(battle_config.max_marionette_gvg_vit < 1)
			battle_config.max_marionette_gvg_vit = battle_config.max_parameter;
		if(battle_config.max_marionette_gvg_int < 1)
			battle_config.max_marionette_gvg_int = battle_config.max_parameter;
		if(battle_config.max_marionette_gvg_dex < 1)
			battle_config.max_marionette_gvg_dex = battle_config.max_parameter;
		if(battle_config.max_marionette_gvg_luk < 1)
			battle_config.max_marionette_gvg_luk = battle_config.max_parameter;
		if(battle_config.tax_rate < 0)
			battle_config.tax_rate = 0;
		if(battle_config.tax_rate > 100)
			battle_config.tax_rate = 100;
		if(battle_config.steal_rate < 0)
			battle_config.steal_rate = 0;
		if(battle_config.pk_murderer_point < 0)
			battle_config.pk_murderer_point = 0;
	}

	return 0;
}

/*==========================================
 * ‰Šú‰»
 *------------------------------------------
 */
int do_init_battle(void)
{
	add_timer_func_list(battle_delay_damage_sub);

	return 0;
}

/*==========================================
 * I—¹
 *------------------------------------------
 */
int do_final_battle(void)
{
	// nothing to do
	return 0;
}
