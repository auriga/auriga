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
	atn_bignumber damage;
	short skillid;
	short skilllv;
	int flag;
	int dist;
};

static int battle_attack_drain(struct block_list *bl,atn_bignumber damage,atn_bignumber damage2,int flag);
static struct Damage battle_calc_attack(int attack_type,struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag);

/*==========================================
 * �_���[�W�̒x��
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

int battle_delay_damage(unsigned int tick,struct block_list *src,struct block_list *target,atn_bignumber damage,int skillid,int skilllv,int flag)
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
 * ���ӂɃ_���[�W
 *------------------------------------------
 */
int battle_damage_area(struct block_list *bl,va_list ap)
{
	struct block_list *src;
	atn_bignumber damage;
	int skillid,skilllv,flag;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);

	if((src = va_arg(ap,struct block_list*)) == NULL)
		return 0;

	damage  = va_arg(ap,atn_bignumber);
	skillid = va_arg(ap,int);
	skilllv = va_arg(ap,int);
	flag    = va_arg(ap,int);
	tick    = va_arg(ap,unsigned int);

	if(battle_check_target(src,bl,flag) > 0) {
		clif_damage(bl,bl,tick,status_get_amotion(bl),status_get_dmotion(bl),damage,0,9,0,0);
		battle_damage(src,bl,damage,skillid,skilllv,flag);

		if(skillid == LG_REFLECTDAMAGE) {
			// �X�L���̔��˃_���[�W�̃I�[�g�X�y��
			if(battle_config.weapon_reflect_autospell && src->type == BL_PC && atn_rand()%2)
				bonus_autospell_start(src,bl,EAS_ATTACK,tick,0);

			if(battle_config.weapon_reflect_drain && src != bl)
				battle_attack_drain(src,damage,0,battle_config.weapon_reflect_drain_enable_type);

			// �X�L���̔��˃_���[�W�̃A�N�e�B�u�A�C�e��
			if(battle_config.weapon_reflect_autospell && src->type == BL_PC)
				bonus_activeitem_start((struct map_session_data *)src,EAS_ATTACK,tick);
		}
	}

	return 0;
}

/*==========================================
 * ���ۂ�HP�𑀍�
 *------------------------------------------
 */
int battle_damage(struct block_list *bl,struct block_list *target,atn_bignumber damage,int skillid,int skilllv,int flag)
{
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct mob_data   *tmd  = NULL;
	struct homun_data *thd  = NULL;
	struct merc_data  *tmcd = NULL;
	struct elem_data  *teld = NULL;

	nullpo_retr(0, target);	// bl��NULL�ŌĂ΂�邱�Ƃ�����̂ő��Ń`�F�b�N

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
		return battle_heal(bl,target,BIGNUM2INT(-damage),0,flag);

	map_freeblock_lock();

	if(target->type == BL_SKILL) {
		skill_unit_ondamaged((struct skill_unit *)target,bl,BIGNUM2INT(damage),gettick());
		map_freeblock_unlock();
		return 0;
	}

	tsd  = BL_DOWNCAST( BL_PC,   target );
	tmd  = BL_DOWNCAST( BL_MOB,  target );
	thd  = BL_DOWNCAST( BL_HOM,  target );
	tmcd = BL_DOWNCAST( BL_MERC, target );
	teld = BL_DOWNCAST( BL_ELEM, target );

	if(tsd) {
		// �f�B�{�[�V�������������Ă���
		if( tsd->sc.data[SC_DEVOTION].timer != -1 &&
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
					if(msd->sc.data[SC_REBOUND_S].timer != -1) {		// ���o�E���h�V�[���h
						damage -= damage * (25 + msd->sc.data[SC_REBOUND_S].val1 * 5) / 100;
					}
					// �_���[�W���[�V�����t���Ń_���[�W�\��
					clif_damage(&msd->bl,&msd->bl,tick,0,status_get_dmotion(&msd->bl),damage,0,0,0,0);
					battle_damage(bl,&msd->bl,damage,skillid,skilllv,flag);
					map_freeblock_unlock();
					return 0;
				}
			}
		}
		// �V���h�E�t�H�[�����������Ă���
		if( tsd->sc.data[SC__SHADOWFORM].timer != -1 &&
		    tsd->sc.data[SC__SHADOWFORM].val2 &&
		    skillid != PA_PRESSURE &&
		    skillid != SA_COMA &&
		    skillid != NPC_DARKBLESSING &&
		    (skillid != CR_GRANDCROSS || bl == NULL || bl != target) )
		{
			struct map_session_data *msd = map_id2sd(tsd->sc.data[SC__SHADOWFORM].val2);

			if(msd && bl && tsd->shadowform_id != msd->bl.id && skill_shadowform(msd,tsd->bl.id) == 0) {
				// �񐔂𒴂�����V���h�E�t�H�[������
				if(--tsd->sc.data[SC__SHADOWFORM].val3 <= 0) {
					status_change_end(&tsd->bl,SC__SHADOWFORM,-1);
				}
				// �_���[�W���[�V�����t���Ń_���[�W�\��
				clif_damage(&msd->bl,&msd->bl,gettick(),0,status_get_dmotion(&msd->bl),damage,0,0,0,0);
				battle_damage(bl,&msd->bl,damage,skillid,skilllv,flag);
				map_freeblock_unlock();
				return 0;
			}
		}
		// �E�H�[�^�[�X�N���[�����������Ă���
		if( tsd->eld &&
		    tsd->sc.data[SC_WATER_SCREEN].timer != -1 &&
		    skillid != PA_PRESSURE &&
		    skillid != SA_COMA &&
		    skillid != NPC_DARKBLESSING &&
		    (skillid != CR_GRANDCROSS || bl == NULL || bl != target) )
		{
			struct elem_data *eld = tsd->eld;

			// �_���[�W���[�V�����t���Ń_���[�W�\��
			clif_damage(&eld->bl,&eld->bl,gettick(),0,status_get_dmotion(&eld->bl),damage,0,0,0,0);
			battle_damage(bl,&eld->bl,damage,skillid,skilllv,flag);
			map_freeblock_unlock();
			return 0;
		}
	}

	status_change_attacked_end(target);	// �����E�Ή��E����������
	unit_skillcastcancel(target,2);		// �r���W�Q

	if(tsd)       pc_damage(bl,tsd,BIGNUM2INT(damage));
	else if(tmd)  mob_damage(bl,tmd,BIGNUM2INT(damage),0);
	else if(thd)  homun_damage(bl,thd,BIGNUM2INT(damage));
	else if(tmcd) merc_damage(bl,tmcd,BIGNUM2INT(damage));
	else if(teld) elem_damage(bl,teld,BIGNUM2INT(damage));

	// �J�[�h���ʂ̃R�[�}�E����
	if(sd && target && target->prev && !unit_isdead(target) && flag&(BF_WEAPON|BF_NORMAL) && status_get_class(target) != MOBID_EMPERIUM)
	{
		int race = status_get_race(target);
		int ele  = status_get_elem_type(target);
		int mode = status_get_mode(target);

		if((!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_ele[ele]) ||
		   (!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race[race]) ||
		   (mode&MD_BOSS && atn_rand()%10000 < sd->weapon_coma_race[RCT_BOSS]) ||
		   (!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race[RCT_NONBOSS]))
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
			(!(mode&MD_BOSS) && atn_rand()%10000 < sd->weapon_coma_race2[RCT_NONBOSS]))
		{
			int hp = status_get_hp(target) - 1;
			if(tsd)       pc_damage(bl,tsd,hp);
			else if(tmd)  mob_damage(bl,tmd,hp,0);
			else if(thd)  homun_damage(bl,thd,hp);
			else if(tmcd) merc_damage(bl,tmcd,hp);
			else if(teld) elem_damage(bl,teld,hp);
		}
	}

	/* �\�E���h���C�� */
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
 * HP/SP��
 *------------------------------------------
 */
int battle_heal(struct block_list *bl,struct block_list *target,int hp,int sp,int flag)
{
	nullpo_retr(0, target);	// bl��NULL�ŌĂ΂�邱�Ƃ�����̂ő��Ń`�F�b�N

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
		return pc_heal((struct map_session_data *)target,hp,sp,0,0);
	else if(target->type == BL_HOM)
		return homun_heal((struct homun_data *)target,hp,sp);
	else if(target->type == BL_MERC)
		return merc_heal((struct merc_data *)target,hp,sp);
	else if(target->type == BL_ELEM)
		return elem_heal((struct elem_data *)target,hp,sp);

	return 0;
}

/*==========================================
 * �_���[�W�̑����C��
 *------------------------------------------
 */
atn_bignumber battle_attr_fix(atn_bignumber damage,int atk_elem,int def_elem)
{
	int def_type, def_lv, rate;

	// ��������(!=������)
	if (atk_elem == ELE_NONE)
		return damage;

	def_type = def_elem%20;
	def_lv   = def_elem/20;

	if( atk_elem == ELE_MAX )
		atk_elem = atn_rand()%ELE_MAX;	// ���푮�������_���ŕt��

	if( atk_elem < ELE_NEUTRAL || atk_elem >= ELE_MAX ||
	    def_type < ELE_NEUTRAL || def_type >= ELE_MAX ||
	    def_lv <= 0 || def_lv > MAX_ELE_LEVEL )
	{
		// �����l�����������̂łƂ肠�������̂܂ܕԂ�
		if(battle_config.error_log)
			printf("battle_attr_fix: unknown attr type: atk=%d def_type=%d def_lv=%d\n",atk_elem,def_type,def_lv);
		return damage;
	}

	rate = attr_fix_table[def_lv-1][atk_elem][def_type];
	if(damage < 0 && rate < 0)	// ���~���̏ꍇ�͌��ʂ𕉂ɂ���
		rate = -rate;

#ifdef PRE_RENEWAL
	return damage * rate / 100;
#else
	return damage + (damage * (rate - 100) / 100);
#endif
}

/*==========================================
 * �_���[�W�ŏI�v�Z
 *------------------------------------------
 */
static atn_bignumber battle_calc_damage(struct block_list *src, struct block_list *bl, atn_bignumber damage, int div_, int skill_num, int skill_lv, int flag)
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

	// �X�L���_���[�W�␳
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
		// �J�[�h���ʂɂ�����X�L���̃_���[�W�ϐ�(�b��)
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

	if(tmd && ((tmd->mode&MD_SKILLIMMUNITY && (flag&BF_SKILL)) ||
				(tmd->mode&MD_IGNORE_MELEE && (flag&BF_WEAPON)) ||
				(tmd->mode&MD_IGNORE_MAGIC && (flag&BF_MAGIC)) ||
				(tmd->mode&MD_IGNORE_RANGED && (flag&BF_LONG)) ||
				(tmd->mode&MD_IGNORE_MISC && (flag&BF_MISC)) ))
		damage = 0;

	if(sc && sc->count > 0) {
		if(sc->data[SC_INVINCIBLE].timer != -1 && sc->data[SC_INVINCIBLEOFF].timer == -1) {
			if(skill_num == PR_SANCTUARY)
				damage = 1;
			else
				damage = 0;
		}

		if(sc->data[SC_MAXPAIN].timer != -1)
			return damage;

		if(sc->data[SC_WHITEIMPRISON].timer != -1) {
			// �z���C�g�C���v���Y����Ԃ͔O�����ȊO�̓_���[�W���󂯂Ȃ�
			if( (flag&BF_SKILL && skill_get_pl(skill_num) != ELE_GHOST) ||
				(!(flag&BF_SKILL) && status_get_attack_element(src) != ELE_GHOST) )
			damage = 0;
		}

		if( sc->data[SC_GRAVITYCONTROL].timer != -1 )
			damage = 0;

		if(damage > 0) {
			int ele = (flag&BF_SKILL)? skill_get_pl(skill_num): status_get_attack_element(src);
			switch(ele) {
			case ELE_NEUTRAL:	if(sc->data[SC_IMMUNE_PROPERTY_NOTHING].timer != -1) damage = 0; break;
			case ELE_WATER:	if(sc->data[SC_IMMUNE_PROPERTY_WATER].timer != -1)	damage = 0; break;
			case ELE_EARTH:		if(sc->data[SC_IMMUNE_PROPERTY_GROUND].timer != -1)	damage = 0; break;
			case ELE_FIRE:		if(sc->data[SC_IMMUNE_PROPERTY_FIRE].timer != -1)		damage = 0; break;
			case ELE_WIND:		if(sc->data[SC_IMMUNE_PROPERTY_WIND].timer != -1)	damage = 0; break;
			case ELE_DARK:		if(sc->data[SC_IMMUNE_PROPERTY_DARKNESS].timer != -1)	damage = 0; break;
			case ELE_HOLY:		if(sc->data[SC_IMMUNE_PROPERTY_SAINT].timer != -1)		damage = 0; break;
			case ELE_POISON:	if(sc->data[SC_IMMUNE_PROPERTY_POISON].timer != -1)		damage = 0; break;
			case ELE_GHOST:	if(sc->data[SC_IMMUNE_PROPERTY_TELEKINESIS].timer != -1)	damage = 0; break;
			case ELE_UNDEAD:	if(sc->data[SC_IMMUNE_PROPERTY_UNDEAD].timer != -1)		damage = 0; break;
			}
		}
	}

	if(src_sc && src_sc->count > 0) {
#ifdef PRE_RENEWAL
		// ������̃_���[�W����
		if(src_sc->data[SC_VOLCANO].timer != -1 && damage > 0) {	// �{���P�[�m
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE ) {
				damage += damage * src_sc->data[SC_VOLCANO].val4 / 100;
			}
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE ) {
				damage += damage * src_sc->data[SC_VOLCANO].val4 / 100;
			}
		}
		if(src_sc->data[SC_VIOLENTGALE].timer != -1 && damage > 0) {	// �o�C�I�����g�Q�C��
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_WIND )
				damage += damage * src_sc->data[SC_VIOLENTGALE].val4 / 100;
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_WIND )
				damage += damage * src_sc->data[SC_VIOLENTGALE].val4 / 100;
		}
		if(src_sc->data[SC_DELUGE].timer != -1 && damage > 0) {	// �f�����[�W
			if( flag&BF_SKILL && skill_get_pl(skill_num) == ELE_WATER )
				damage += damage * src_sc->data[SC_DELUGE].val4 / 100;
			else if( !(flag&BF_SKILL) && status_get_attack_element(src) == ELE_WATER )
				damage += damage * src_sc->data[SC_DELUGE].val4 / 100;
		}
#endif
		if(tmd) {
			int i;
			if(src_sc->data[SC_MANU_ATK].timer != -1 && damage > 0 && flag&BF_WEAPON) {	// �}�k�N�t�B�[���hMOB�����_���[�W����
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_MANU_ATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_SPL_ATK].timer != -1 && damage > 0 && flag&BF_WEAPON) {	// �X�v�����e�B�b�h�t�B�[���hMOB�����_���[�W����
				for(i = 0; i < (sizeof(splendide_mob) / sizeof(splendide_mob[0])); i++) {
					if(splendide_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_SPL_ATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_MANU_MATK].timer != -1 && damage > 0 && flag&BF_MAGIC) {	// �}�k�N�t�B�[���hMOB���@�_���[�W����
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == tmd->class_) {
						damage = damage * src_sc->data[SC_MANU_MATK].val1 / 100;
						break;
					}
				}
			}
			if(src_sc->data[SC_SPL_MATK].timer != -1 && damage > 0 && flag&BF_MAGIC) {	// �X�v�����e�B�b�h�t�B�[���hMOB���@�_���[�W����
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
		// �Ñ㐸��̂����
		if(src_sc->data[SC_PHI_DEMON].timer != -1 && damage > 0 && flag&(BF_WEAPON|BF_MAGIC) && status_get_race(bl) == RCT_DEMON)
			damage += damage * 10 / 100;
		// �p�� -�W�J-�̑����_���[�W����
		if(src_sc->data[SC_KO_ZENKAI].timer != -1 && damage > 0) {
			// val3�ɑ����l�������Ă�̂ň�v����΃_���[�W����
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == src_sc->data[SC_KO_ZENKAI].val3) ||
				(!(flag&BF_SKILL) && status_get_attack_element(src) == src_sc->data[SC_KO_ZENKAI].val3) )
					damage += damage * src_sc->data[SC_KO_ZENKAI].val4 / 100;
		}
		/* �e���L�l�V�X�C���e���X */
		if(src_sc->data[SC_TELEKINESIS_INTENSE].timer != -1 && skill_get_pl(skill_num) == ELE_GHOST)
			damage += damage * src_sc->data[SC_TELEKINESIS_INTENSE].val2 / 100;
		// �X�^�C���`�F���W(�t�@�C�^�[�X�^�C��)
		if(src_sc->data[SC_STYLE_CHANGE].timer != -1 && src_sc->data[SC_STYLE_CHANGE].val1 == 1 && atn_rand()%100 < 30 && damage > 0) {
			struct homun_data *hd = (struct homun_data *)src;
			if(hd && hd->spiritball < 10)
				homun_addspiritball(hd,10);
		}
		// �G���`�����e�B���O�V���h�E
		if(src_sc->data[SC_SHADOW_WEAPON].timer != -1 && atn_rand()%100 < src_sc->data[SC_SHADOW_WEAPON].val2) {
			if(sc && sc->data[SC_SHADOW_SCAR].timer != -1) {
				if(sc->data[SC_SHADOW_SCAR].val1 < 20) {
					status_change_start(bl,SC_SHADOW_SCAR,sc->data[SC_SHADOW_SCAR].val1+1,0,0,0,skill_get_time2(SHC_ENCHANTING_SHADOW,1),0);
				}
			} else {
				status_change_start(bl,SC_SHADOW_SCAR,1,0,0,0,skill_get_time2(SHC_ENCHANTING_SHADOW,1),0);
			}
		}
	}

	if(sc && sc->count > 0 && skill_num != PA_PRESSURE && skill_num != HW_GRAVITATION) {
		// �A�X���v�e�B�I
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

		// �S�X�y���̓����Ԉُ�
		if(sc->data[SC_INCDAMAGE].timer != -1 && damage > 0)
			damage += damage * sc->data[SC_INCDAMAGE].val1/100;

		// �o�W���J
		if(sc->data[SC_BASILICA].timer != -1 && damage > 0 && !(status_get_mode(src)&MD_BOSS))
			damage = 0;

		// �E�H�[���I�u�t�H�O
		if((sc->data[SC_FOGWALL].timer != -1 || sc->data[SC_FOGWALLPENALTY].timer != -1)
			&& damage > 0 && flag&BF_LONG && skill_num!=PA_PRESSURE)
		{
			if(skill_num == 0) {	// �������ʏ�U��75%OFF
				damage = damage * 25 / 100;
			} else {		// �������X�L��25%OFF
				damage = damage * 75 / 100;
			}
		}

#ifdef PRE_RENEWAL
		// �Z�C�t�e�B�E�H�[��
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
		// �L���G�G���C�\��
		if(sc->data[SC_KYRIE].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_KYRIE];
			scd->val2 -= BIGNUM2INT(damage);
			if(flag&BF_WEAPON) {
				if(scd->val2 >= 0)
					damage = 0;
				else
					damage = -scd->val2;
			}
			if(--scd->val3 <= 0 || scd->val2 <= 0 || skill_num == AL_HOLYLIGHT)
				status_change_end(bl, SC_KYRIE, -1);
		}
		// �v���`�i���A���^�[
		if(sc->data[SC_P_ALTER].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_P_ALTER];
			clif_misceffect2(bl,336);
			if(scd->val3 > 0 && scd->val4 > 0) {
				scd->val3 -= BIGNUM2INT(damage);
				if(flag&BF_WEAPON) {
					if(scd->val3 >= 0)
						damage = 0;
					else
						damage = -scd->val3;
				}
				scd->val4--;
			}
		}
		// �Z�C�t�e�B�E�H�[��
		if(sc->data[SC_SAFETYWALL].timer != -1 && damage > 0 && flag&BF_SHORT) {
			struct skill_unit *unit = map_id2su(sc->data[SC_SAFETYWALL].val2);
			if(unit && unit->group) {
				unit->group->val1 -= BIGNUM2INT(damage);
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

		// �J�E�v
		if(sc->data[SC_KAUPE].timer != -1 && atn_rand()%100 < sc->data[SC_KAUPE].val2) {
			status_change_end(bl,SC_KAUPE,-1);
			damage = 0;
		}

		// �j���[�}�E���Ԃ��E�j���[�g�����o���A�[
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

		// �}�O���V�[���h
		if(sc->data[SC_TUNAPARTY].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_TUNAPARTY];
			scd->val2 -= BIGNUM2INT(damage);
			if(scd->val2 >= 0)
				damage = 0;
			else
				damage = -scd->val2;
			if(scd->val2 <= 0)
				status_change_end(bl, SC_TUNAPARTY, -1);
		}

		// �����̏�(����~��)
		if(sc->data[SC_DIMENSION2].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_DIMENSION2];

			if(damage >= scd->val3) {
				scd->val3 = scd->val4;
				scd->val2--;
				if(tsd)
					clif_mshield(tsd,scd->val2);
			} else {
				scd->val3 -= BIGNUM2INT(damage);
			}
			damage = 0;
			if(scd->val2 <= 0)
				status_change_end(bl, SC_DIMENSION2, -1);
		}

		// �_�[�N�N���[
		if(sc->data[SC_DARKCROW].timer != -1 && flag&(BF_WEAPON|BF_SHORT))
			damage += damage * sc->data[SC_DARKCROW].val2 / 100;

		// �V���h�E�y�C��
		if(sc->data[SC_SHADOW_SCAR].timer != -1 && flag&(BF_WEAPON|BF_SHORT)) {
			damage += damage * sc->data[SC_SHADOW_SCAR].val2 / 100;
		}

		// ���b�N�X�G�[�e���i
		if(sc->data[SC_AETERNA].timer != -1 && damage > 0) {
			damage <<= 1;
			status_change_end(bl,SC_AETERNA,-1);
		}

		// �G�i�W�[�R�[�g
#ifdef PRE_RENEWAL
		if(sc->data[SC_ENERGYCOAT].timer != -1 && damage > 0 && flag&BF_WEAPON && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID && (src != bl && skill_num == NPC_EARTHQUAKE))
#else
		if(sc->data[SC_ENERGYCOAT].timer != -1 && damage > 0 && flag&(BF_WEAPON|BF_MAGIC) && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID && (src != bl && skill_num == NPC_EARTHQUAKE))
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
		// �L���G�G���C�\��
		if(sc->data[SC_KYRIE].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_KYRIE];
			scd->val2 -= BIGNUM2INT(damage);
			if(flag&BF_WEAPON) {
				if(scd->val2 >= 0)
					damage = 0;
				else
					damage = -scd->val2;
			}
			if(--scd->val3 <= 0 || scd->val2 <= 0 || skill_num == AL_HOLYLIGHT)
				status_change_end(bl, SC_KYRIE, -1);
		}
		// �v���`�i���A���^�[
		if(sc->data[SC_P_ALTER].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_P_ALTER];
			clif_misceffect2(bl,336);
			if(scd->val3 > 0 && scd->val4 > 0) {
				scd->val3 -= BIGNUM2INT(damage);
				if(flag&BF_WEAPON) {
					if(scd->val3 >= 0)
						damage = 0;
					else
						damage = -scd->val3;
				}
				scd->val4--;
			}
		}
#endif

		// �C���f���A
		if(sc->data[SC_ENDURE].timer != -1 && damage > 0 && flag&BF_WEAPON && src->type != BL_PC) {
			if((--sc->data[SC_ENDURE].val2) <= 0)
				status_change_end(bl, SC_ENDURE, -1);
		}

		// �I�[�g�K�[�h
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

		// �p���C���O
		if(sc->data[SC_PARRYING].timer != -1 && damage > 0 && flag&BF_WEAPON && skill_num != WS_CARTTERMINATION) {
			if(atn_rand()%100 < sc->data[SC_PARRYING].val2)
			{
				int dir = path_calc_dir(bl,src->x,src->y);
				damage = 0;
				clif_skill_nodamage(bl,bl,sc->data[SC_PARRYING].val4,sc->data[SC_PARRYING].val1,1);	// val4�̓X�L��ID
				clif_changedir(bl,dir,dir);
				if(ud)
					ud->attackabletime = tick + 500;	// �l�K��
			}
		}

		// ���W�F�N�g�\�[�h
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
		// �X�p�C�_�[�E�F�u
		if(sc->data[SC_SPIDERWEB].timer != -1 && damage > 0) {
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				damage <<= 1;
				status_change_end(bl, SC_SPIDERWEB, -1);
			}
		}
#endif

		// �~���j�A���V�[���h
		if(sc->data[SC_MILLENNIUMSHIELD].timer != -1 && damage > 0) {
			struct status_change_data *scd = &sc->data[SC_MILLENNIUMSHIELD];

			if(damage >= scd->val3) {
				scd->val3 = 1000;
				scd->val2--;
				if(tsd)
					clif_mshield(tsd,scd->val2);
			} else {
				scd->val3 -= BIGNUM2INT(damage);
			}
			damage = 0;
			if(scd->val2 <= 0)
				status_change_end(bl, SC_MILLENNIUMSHIELD, -1);
		}

		// �E�F�|���u���b�L���O
		if(sc->data[SC_WEAPONBLOCKING].timer != -1 && flag&BF_WEAPON && flag&BF_SHORT && skill_num != WS_CARTTERMINATION) {
			if(atn_rand()%100 < sc->data[SC_WEAPONBLOCKING].val2) {
				int lv = sc->data[SC_WEAPONBLOCKING].val1;
				damage = 0;
				clif_skill_nodamage(bl,bl,GC_WEAPONBLOCKING,lv,1);
				status_change_start(bl,SC_WEAPONBLOCKING_POSTDELAY,lv,src->id,0,0,skill_get_time2(GC_WEAPONBLOCKING,lv),0);
				status_change_start(bl,SC_WEAPONBLOCK_ON,lv,src->id,0,0,skill_get_time(GC_COUNTERSLASH,lv),0);
			}
		}

		// �N���[�L���O�G�N�V�[�h
		if(sc->data[SC_CLOAKINGEXCEED].timer != -1 && damage > 0) {
			if((--sc->data[SC_CLOAKINGEXCEED].val2) <= 0)
				status_change_end(bl, SC_CLOAKINGEXCEED, -1);
		}

		// �n���V�l�[�V�����E�H�[�N
		if(sc->data[SC_HALLUCINATIONWALK].timer != -1 && damage > 0 && flag&BF_MAGIC) {
			if(atn_rand()%100 < sc->data[SC_HALLUCINATIONWALK].val1 * 10)
				damage = 0;
		}

		// �t�H�[�X�I�u�o���K�[�h
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

		// �v���X�e�B�[�W
		if(sc->data[SC_PRESTIGE].timer != -1 && damage > 0 && flag&BF_MAGIC) {
			if(atn_rand()%100 < sc->data[SC_PRESTIGE].val3)
				damage = 0;
		}

		// �M�d��
		if(sc->data[SC_LIGHTNINGWALK].timer != -1 && damage > 0 && flag&(BF_LONG|BF_MAGIC) && skill_get_inf(skill_num)&INF_ATTACK && atn_rand()%100 < sc->data[SC_LIGHTNINGWALK].val2) {
			damage = 0;
			clif_skill_poseffect(bl,SR_LIGHTNINGWALK,sc->data[SC_LIGHTNINGWALK].val1,src->x,src->y,tick);
			clif_move(bl);
			status_change_end(bl, SC_LIGHTNINGWALK, -1);
			unit_movepos(bl,src->x,src->y,0);
		}

		// �_�� -��-
		if(tsd && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && flag&BF_SHORT && damage > 0) {
			int max = (tsd->s_class.job == PC_JOB_MO || tsd->s_class.job == PC_JOB_SR)? pc_checkskill(tsd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sc->data[SC_RAISINGDRAGON].timer != -1)
				max += sc->data[SC_RAISINGDRAGON].val1;
			if(tsd->spiritball.num < max)
				pc_addspiritball(tsd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
		}

		// �_�C�������h�_�X�g
		if(sc->data[SC_DIAMONDDUST].timer != -1 && damage > 0) {

			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				status_change_end(bl, SC_DIAMONDDUST, -1);
			}
		}

		// �\�[���g���b�v
		if(sc->data[SC_THORNS_TRAP].timer != -1 && damage > 0) {
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				status_change_end(bl, SC_THORNS_TRAP, -1);
			}
		}

		// �t�@�C�A�[�G�N�X�p���V����(����)
		if(sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer != -1 && damage > 0 && flag&(BF_SHORT|BF_LONG) && skill_num != PA_PRESSURE) {
			damage -= damage * sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].val2 / 100;
		}

#ifndef PRE_RENEWAL
		// �T�v���C�Y�A�^�b�N
		if(sc->data[SC_RAID].timer != -1 && sc->data[SC_RAID].val1 > 0) {
			sc->data[SC_RAID].val1--;
			if(status_get_mode(bl)&MD_BOSS)
				damage += damage * 10 / 100;
			else
				damage += damage * 20 / 100;
		}
		// �X�g�[���X�L��
		if(sc->data[SC_STONESKIN].timer != -1 && damage > 0) {
			if(flag&BF_WEAPON) {
				// �������܂�
				if(sc->data[SC_SU_STOOP].timer != -1 && sc->data[SC_STONESKIN].val1 < 4) {
					damage = damage * 20 / 100;
				}
				else
					damage = damage * (100 - 20 * sc->data[SC_STONESKIN].val1) / 100;
			} else if(flag&BF_MAGIC) {
				damage = damage * (100 + 20 * sc->data[SC_STONESKIN].val1) / 100;
			}
		}
		// �A���`�}�W�b�N
		if(sc->data[SC_ANTIMAGIC].timer != -1 && damage > 0) {
			if(flag&BF_MAGIC) {
				// �������܂�
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
		// �񌎋r
		if(sc->data[SC_NEWMOON].timer != -1 && damage > 0) {
			if((--sc->data[SC_NEWMOON].val2) <= 0)
				status_change_end(bl, SC_NEWMOON, -1);
		}
		// �������܂�
		if(sc->data[SC_SU_STOOP].timer != -1) {
			// �X�g�[���X�L���A�A���`�}�W�b�N�Ƌ������Ȃ�
			if(sc->data[SC_STONESKIN].timer == -1 && sc->data[SC_ANTIMAGIC].timer == -1)
				damage = damage * 20 / 100;
		}
		// �K�[�f�B�A���V�[���h
		if(sc->data[SC_GUARDIAN_S].timer != -1 && damage > 0 && flag&BF_WEAPON) {
			if(damage >= sc->data[SC_GUARDIAN_S].val2) {
				damage -= sc->data[SC_GUARDIAN_S].val2;
				status_change_end(bl, SC_GUARDIAN_S, -1);
			} else {
				clif_misceffect2(bl,336);
				sc->data[SC_GUARDIAN_S].val2 -= BIGNUM2INT(damage);
				damage = 0;
			}
		}
		if(src->type == BL_MOB) {
			int i;
			if(sc->data[SC_MANU_DEF].timer != -1 && damage > 0) {	// �}�k�N�t�B�[���hMOB�_���[�W����
				struct mob_data *md = (struct mob_data *)src;
				for(i = 0; i < (sizeof(manuk_mob) / sizeof(manuk_mob[0])); i++) {
					if(manuk_mob[i] == md->class_) {
						damage = damage * sc->data[SC_MANU_DEF].val1 / 100;
						break;
					}
				}
			}
			if(sc->data[SC_SPL_DEF].timer != -1 && damage > 0) {	// �X�v�����e�B�b�h�t�B�[���hMOB�_���[�W����
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

		// �O���j�e�B�b�N�A�[�}�[
		if(sc->data[SC_GRANITIC_ARMOR].timer != -1 && damage > 0) {
			damage -= damage * sc->data[SC_GRANITIC_ARMOR].val2 / 100;
		}

		// �ΎR�D
		if(sc->data[SC_VOLCANIC_ASH].timer != -1 && damage > 0) {
			if( (flag&BF_SKILL && skill_get_pl(skill_num) == ELE_FIRE) ||
			    (!(flag&BF_SKILL) && status_get_attack_element(src) == ELE_FIRE) )
			{
				damage += damage * sc->data[SC_VOLCANIC_ASH].val2 / 100;
			}
		}

		// �X�^�C���`�F���W(�O���b�v���[�X�^�C��)
		if(sc->data[SC_STYLE_CHANGE].timer != -1 && sc->data[SC_STYLE_CHANGE].val1 == 2 && atn_rand()%100 < 30 && damage > 0) {
			struct homun_data *t_hd = (struct homun_data *)bl;
			if(t_hd && t_hd->spiritball < 10)
				homun_addspiritball(t_hd,10);
		}

		// �����~��(�m���b��)
		if(sc->data[SC_MEIKYOUSISUI].timer != -1 && atn_rand()%100 < sc->data[SC_MEIKYOUSISUI].val1 * 2)
			damage = 0;

		// �_���[�W�q�[��
		if(sc->data[SC_DAMAGE_HEAL].timer != -1 && damage > 0) {
			if(flag & sc->data[SC_DAMAGE_HEAL].val2) {
				int heal = BIGNUM2INT(damage);
				if(flag & BF_WEAPON) {
					clif_misceffect_value(bl, 312, heal);
				} else {
					clif_misceffect_value(bl, 1143, heal);
				}
				clif_misceffect_value(bl, 657, heal);
				unit_heal(bl, BIGNUM2INT(damage), 0, 0, 0);
				damage = 0;
			}
		}
	}

	if(damage > 0) {
		struct guild_castle *gc = NULL;
		int noflag = 0;

		if(tmd && tmd->guild_id) {
			if(tmd->class_ == MOBID_EMPERIUM) {
				// �G���y���E��
				if(flag&BF_SKILL && skill_num != HW_GRAVITATION)
					return 0;
				if(src->type == BL_PC) {
					struct guild *g = guild_search(((struct map_session_data *)src)->status.guild_id);

					if(g == NULL)
						return 0;		// �M���h�������Ȃ�_���[�W����
					if(guild_checkskill(g,GD_APPROVAL) <= 0)
						return 0;		// ���K�M���h���F���Ȃ��ƃ_���[�W����
					if((gc = guild_mapid2gc(tmd->bl.m)) != NULL) {
						if(g->guild_id == gc->guild_id)
							return 0;	// ����̃M���h�̃G���y�Ȃ�_���[�W����
						if(guild_check_alliance(gc->guild_id, g->guild_id, 0))
							return 0;	// �����Ȃ�_���[�W����
					} else {
						noflag = 1;
					}
				} else {
					return 0;
				}
			} else if(!tmd->master_id && tmd->state.special_mob_ai == MOB_AI_NONE) {
				// ���̑���Gv�֘A��MOB
				if(src->type == BL_PC) {
					struct guild *g = guild_search(((struct map_session_data *)src)->status.guild_id);
					if(g) {
						if((gc = guild_mapid2gc(tmd->bl.m)) != NULL) {
							if(g->guild_id == gc->guild_id)
								return 0;	// ����̃M���h�Ȃ�_���[�W����
							if(guild_check_alliance(gc->guild_id, g->guild_id, 0))
								return 0;	// �����Ȃ�_���[�W����
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
				if(gc == NULL && !noflag)	// �G���y���E���A���̑���Gv�֘A��MOB�̍��Ŋ��Ɍ�������NULL�Ȃ�ēx�������Ȃ�
					gc = guild_mapid2gc(tmd->bl.m);
				if(gc) {	// defense������΃_���[�W������炵���H
#ifndef PRE_RENEWAL
					if(tmd->class_ != MOBID_EMPERIUM)
#endif
						damage -= damage * gc->defense / 100 * battle_config.castle_defense_rate / 100;
				}
			}
			if(skill_num != NPC_SELFDESTRUCTION && skill_num != NPC_SELFDESTRUCTION2) {
				if(flag&BF_SKILL) {	// �X�L���U��
					if(flag&BF_WEAPON)
						damage = damage * battle_config.gvg_normalskill_damage_rate / 100;
					if(flag&BF_MAGIC)
						damage = damage * battle_config.gvg_magic_damage_rate / 100;
					if(flag&BF_MISC)
						damage = damage * battle_config.gvg_misc_damage_rate / 100;
				} else {	// �ʏ�U��
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
			if(flag&BF_SKILL) {	// �X�L���U��
				if(flag&BF_WEAPON)
					damage = damage * battle_config.pk_normalskill_damage_rate / 100;
				if(flag&BF_MAGIC)
					damage = damage * battle_config.pk_magic_damage_rate / 100;
				if(flag&BF_MISC)
					damage = damage * battle_config.pk_misc_damage_rate / 100;
			} else {	// �ʏ�U��
				if(flag&BF_SHORT)
					damage = damage * battle_config.pk_short_damage_rate / 100;
				if(flag&BF_LONG)
					damage = damage * battle_config.pk_long_damage_rate / 100;
			}
			if(damage < 1)
				damage = (!battle_config.skill_min_damage && flag&BF_MAGIC && src->type == BL_PC)? 0: 1;
		}

		// mapflag
		if(map[bl->m].flag.damage_rate && src->type != BL_MOB) {
			damage = (map[bl->m].flag.damage_rate < 0)? 0: damage * map[bl->m].flag.damage_rate / 100;
			if(damage < 1)
				damage = (!battle_config.skill_min_damage && flag&BF_MAGIC && src->type == BL_PC)? 0: 1;
		}

		// mob mode
		if(bl->type == BL_MOB) {
			// �{���͏d�����邪�r�������Ŏ������Ă���
			if(status_get_mode(bl)&MD_DAMAGEREDUCTION_1000)
				damage = damage / 1000;
			else if(status_get_mode(bl)&MD_DAMAGEREDUCTION_100)
				damage = damage / 100;
			else if(status_get_mode(bl)&MD_DAMAGEREDUCTION_10)
				damage = damage / 10;
		}
	}

	// �����M�A�̉��M�l�㏸
	if(tsd && src != &tsd->bl && tsd->status.hp > 0 && pc_isgear(tsd) && damage > 0) {
		int heat = 1;

		if(((flag&BF_SKILL)? skill_get_pl(skill_num): status_get_attack_element(src)) == ELE_FIRE)
			heat += 2;	// �Α����U���̏ꍇ�͉��Z�l+2

		if(sc && sc->data[SC_OVERHEAT_LIMITPOINT].timer != -1) {	// ���ɉ��M���
			heat += sc->data[SC_OVERHEAT_LIMITPOINT].val1;	// ���݂̉��M�l���擾
			if(heat > 1000)
				heat = 1000;
		}
		status_change_start(bl,SC_OVERHEAT_LIMITPOINT,heat,10,0,0,1000,0);

		// �I�[�o�[�q�[�g����
		if(sc && sc->data[SC_OVERHEAT].timer != -1) {	// ���ɃI�[�o�[�q�[�g���
			// �������Ȃ�
		}
		else {
			int limit = 150;
			int skill = pc_checkskill(tsd,NC_MAINFRAME);

			if(skill)
			limit += 120 + 80 * skill + ((skill >= 4)? 10: 0);
			if(heat >= limit)
				status_change_start(bl,SC_OVERHEAT,heat,0,0,0,1000,0);
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

	if(tmd && tmd->hp > 0 && damage > 0)	// �����Ȃǂ�MOB�X�L������
	{
		int mtg = tmd->target_id;
		if (battle_config.mob_changetarget_byskill != 0 || mtg == 0)
		{
			if(src->type & (BL_PC | BL_MOB | BL_MERC | BL_ELEM))
				tmd->target_id = src->id;
		}
		mobskill_event(tmd,flag);
		tmd->target_id = mtg;	// �^�[�Q�b�g��߂�
	}

	// PC�̔����I�[�g�X�y��
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

	// PC�̏�Ԉُ픽��
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
 * HP/SP�́��z���v�Z
 *------------------------------------------
 */
static atn_bignumber battle_calc_drain_per(atn_bignumber damage, int rate, int per)
{
	atn_bignumber diff = 0;

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
 * HP/SP�̈��z���v�Z
 *------------------------------------------
 */
static atn_bignumber battle_calc_drain_value(atn_bignumber damage, int rate, int value)
{
	atn_bignumber diff = 0;

	if (damage <= 0 || rate <= 0)
		return 0;

	if (value && atn_rand()%100 < rate) {
		diff = value;
	}

	return diff;
}

/*==========================================
 * �U���ɂ��HP/SP�z��
 *------------------------------------------
 */
static int battle_attack_drain(struct block_list *bl,atn_bignumber damage,atn_bignumber damage2,int flag)
{
	int hp = 0,sp = 0;
	struct map_session_data* sd = NULL;

	nullpo_retr(0, bl);

	if(damage <= 0 && damage2 <= 0)
		return 0;

	if(bl->type != BL_PC || (sd = (struct map_session_data *)bl) == NULL)
		return 0;

	if(flag & 1) {	// ���z��
		if(!battle_config.left_cardfix_to_right) {
			// �񓁗�����J�[�h�̋z���n���ʂ��E��ɒǉ����Ȃ��ꍇ
			hp += BIGNUM2INT(battle_calc_drain_per(damage,  sd->hp_drain.p_rate,  sd->hp_drain.per ));
			hp += BIGNUM2INT(battle_calc_drain_per(damage2, sd->hp_drain_.p_rate, sd->hp_drain_.per));
			sp += BIGNUM2INT(battle_calc_drain_per(damage,  sd->sp_drain.p_rate,  sd->sp_drain.per ));
			sp += BIGNUM2INT(battle_calc_drain_per(damage2, sd->sp_drain_.p_rate, sd->sp_drain_.per));
		} else {
			// �񓁗�����J�[�h�̋z���n���ʂ��E��ɒǉ�����ꍇ
			int hp_rate = sd->hp_drain.p_rate + sd->hp_drain_.p_rate;
			int hp_per  = sd->hp_drain.per + sd->hp_drain_.per;
			int sp_rate = sd->sp_drain.p_rate + sd->sp_drain_.p_rate;
			int sp_per  = sd->sp_drain.per + sd->sp_drain_.per;
			hp += BIGNUM2INT(battle_calc_drain_per(damage, hp_rate, hp_per));
			sp += BIGNUM2INT(battle_calc_drain_per(damage, sp_rate, sp_per));
		}
	}
	if(flag & 2) {	// ���z��
		if(!battle_config.left_cardfix_to_right) {
			// �񓁗�����J�[�h�̋z���n���ʂ��E��ɒǉ����Ȃ��ꍇ
			hp += BIGNUM2INT(battle_calc_drain_value(damage,  sd->hp_drain.v_rate,  sd->hp_drain.value ));
			hp += BIGNUM2INT(battle_calc_drain_value(damage2, sd->hp_drain_.v_rate, sd->hp_drain_.value));
			sp += BIGNUM2INT(battle_calc_drain_value(damage,  sd->sp_drain.v_rate,  sd->sp_drain.value ));
			sp += BIGNUM2INT(battle_calc_drain_value(damage2, sd->sp_drain_.v_rate, sd->sp_drain_.value));
		} else {
			// �񓁗�����J�[�h�̋z���n���ʂ��E��ɒǉ�����ꍇ
			int hp_rate  = sd->hp_drain.v_rate + sd->hp_drain_.v_rate;
			int hp_value = sd->hp_drain.value + sd->hp_drain_.value;
			int sp_rate  = sd->sp_drain.v_rate + sd->sp_drain_.v_rate;
			int sp_value = sd->sp_drain.value + sd->sp_drain_.value;
			hp += BIGNUM2INT(battle_calc_drain_value(damage, hp_rate, hp_value));
			sp += BIGNUM2INT(battle_calc_drain_value(damage, sp_rate, sp_value));
		}
	}
	if(hp || sp)
		pc_heal(sd, hp, sp, 0, 0);

	return 1;
}

/*==========================================
 * �C���_���[�W
 *------------------------------------------
 */
static atn_bignumber battle_addmastery(struct map_session_data *sd,struct block_list *target,atn_bignumber dmg,int type)
{
	atn_bignumber damage = 0;
	int race, element, skill, weapon;

	nullpo_retr(0, sd);
	nullpo_retr(0, target);

	race = status_get_race(target);
	element = status_get_element(target)%20;

	// �f�[�����x�C�� vs �s�� or ���� (���l�͊܂߂Ȃ��H)
	if((skill = pc_checkskill(sd,AL_DEMONBANE)) > 0 && (battle_check_undead(race,status_get_elem_type(target)) || race == RCT_DEMON) ) {
		damage += (300 + 5 * sd->status.base_level) * skill / 100;
	}

	// �r�[�X�g�x�C��(+4 �` +40) vs ���� or ����
	if((skill = pc_checkskill(sd,HT_BEASTBANE)) > 0 && (race == RCT_BRUTE || race == RCT_INSECT) )
	{
		damage += (skill * 4);

		if(sd->sc.data[SC_HUNTER].timer != -1)
			damage += status_get_str(&sd->bl);
	}

#ifndef PRE_RENEWAL
	// �q���g�o�C���f�B���O(+4)
	if((skill = pc_checkskill(sd,BS_HILTBINDING)) > 0) {
		damage += 4;
	}

	// ���팤��(+2 �` +20)
	if((skill = pc_checkskill(sd,BS_WEAPONRESEARCH)) > 0) {
		damage += (skill * 2);
	}
#endif

	// �����W���[���C��(+5 �` +50) vs ���� or �A�� or ����
	if((skill = pc_checkskill(sd,RA_RANGERMAIN)) > 0 && (race == RCT_BRUTE || race == RCT_PLANT || race == RCT_FISH) )
	{
		damage += (skill * 5);
	}

	// �����M�A���C�Z���X(+20 �` +100)
	if(pc_isgear(sd) && (skill = pc_checkskill(sd,NC_MADOLICENCE)) > 0)
	{
		damage += (skill * 20);
	}

	// �΂Ƒ�n�̌���(+10 �` +50) vs �Α��� or �n����
	if((skill = pc_checkskill(sd,NC_RESEARCHFE)) > 0 && (element == ELE_FIRE || element == ELE_EARTH))
	{
		damage += (skill * 10);
	}

	weapon = (type == 0)? sd->weapontype1: sd->weapontype2;

	switch(weapon)
	{
		case WT_1HSWORD:
#ifndef PRE_RENEWAL
			// �A���P�~�X�g���C��(+3 �` +30)
			if((skill = pc_checkskill(sd,AM_AXEMASTERY)) > 0) {
				damage += (skill * 3);
			}
#endif
			// fall through
		case WT_DAGGER:
			// ���C��(+4 �` +40) �Ў茕 �Z���܂�
			if((skill = pc_checkskill(sd,SM_SWORD)) > 0) {
				damage += (skill * 4);
			}
			// �W�F�l�e�B�b�N���C��(+10 �` +50)
			if((skill = pc_checkskill(sd,GN_TRAINING_SWORD)) > 0) {
				damage += (skill * 10);
			}
			break;
		case WT_2HSWORD:
			// ���茕�C��(+4 �` +40) ���茕
			if((skill = pc_checkskill(sd,SM_TWOHAND)) > 0) {
				damage += (skill * 4);
			}
			break;
		case WT_1HSPEAR:
			// ���C��(+4 �` +40,+5 �` +50,+10 �` +100) ��
			if((skill = pc_checkskill(sd,KN_SPEARMASTERY)) > 0) {
				if(pc_isdragon(sd) && pc_checkskill(sd,RK_DRAGONTRAINING) > 0)
					damage += (skill * 10);	// �h���S���ɏ���Ăăg���[�j���O�K���ς�
				else if(!pc_isriding(sd) && !pc_isdragon(sd))
					damage += (skill * 4);	// �y�R�ɏ���ĂȂ�
				else
					damage += (skill * 5);	// �y�R�ɏ���Ă�
			}
			break;
		case WT_2HSPEAR:
			// ���C��(+4 �` +40,+5 �` +50,+10 �` +100) ��
			if((skill = pc_checkskill(sd,KN_SPEARMASTERY)) > 0) {
				if(pc_isdragon(sd) && pc_checkskill(sd,RK_DRAGONTRAINING) > 0)
					damage += (skill * 10);	// �h���S���ɏ���Ăăg���[�j���O�K���ς�
				else if(!pc_isriding(sd) && !pc_isdragon(sd))
					damage += (skill * 4);	// �y�R�ɏ���ĂȂ�
				else
					damage += (skill * 5);	// �y�R�ɏ���Ă�
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
			// ���C�X�C��(+3 �` +30) ���C�X
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
			// �^�C���M(+10 �` +100) �f��
			if((skill = pc_checkskill(sd,TK_RUN)) > 0) {
				damage += (skill * 10);
			}
			// fall through
		case WT_KNUCKLE:
			// �S��(+3 �` +30) �f��,�i�b�N��
			if((skill = pc_checkskill(sd,MO_IRONHAND)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_MUSICAL:
			// �y��̗��K(+3 �` +30) �y��
			if((skill = pc_checkskill(sd,BA_MUSICALLESSON)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_WHIP:
			// �_���X�̗��K(+3 �` +30) ��
			if((skill = pc_checkskill(sd,DC_DANCINGLESSON)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_BOOK:
			// �A�h�o���X�h�u�b�N(+3 �` +30) {
			if((skill = pc_checkskill(sd,SA_ADVANCEDBOOK)) > 0) {
				damage += (skill * 3);
			}
			break;
		case WT_KATAR:
			// �J�^�[���C��(+3 �` +30) �J�^�[��
			if((skill = pc_checkskill(sd,AS_KATAR)) > 0) {
				// �\�j�b�N�u���[���͕ʏ����i1���ɕt��1/8�K��)
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
 * ��{����_���[�W�v�Z
 *------------------------------------------
 */
static atn_bignumber battle_calc_base_damage(struct block_list *src,struct block_list *target,int skill_num,int type,int lh)
{
	atn_bignumber damage = 0;
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

		// Dex�ˑ������Dex����{�l�Ƃ���
		if( sd->status.weapon == WT_BOW ||
			sd->status.weapon == WT_MUSICAL ||
			sd->status.weapon == WT_WHIP ||
			(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) )
			str = dex;
#endif

		if(skill_num == HW_MAGICCRASHER || (skill_num == 0 && sc && sc->data[SC_CHANGE].timer != -1)) {
			// �}�W�b�N�N���b�V���[�܂��̓����^���`�F���W���̒ʏ�U���Ȃ�MATK�ŉ���
			damage = status_get_matk1(src);
#ifdef PRE_RENEWAL
		} else {
			damage = status_get_baseatk(src);
#endif
		}

		atkmin = dex;	// �Œ�ATK��DEX�ŏ�����

#ifdef PRE_RENEWAL
		if(idx >= 0 && sd->inventory_data[idx])
			atkmin = atkmin * (80 + sd->inventory_data[idx]->wlv * 20) / 100;
		if(sd->state.arrow_atk)						// ���킪�|��̏ꍇ
			atkmin = watk * ((atkmin < watk)? atkmin: watk) / 100;	// �|�p�Œ�ATK�v�Z
		if(sc && sc->data[SC_IMPOSITIO].timer != -1)	// IM���������Ă�����ŏ����Z�U���͂ɉ��Z
			atkmin += sc->data[SC_IMPOSITIO].val1*5;

		/* �T�C�Y�C�� */
		if(skill_num == MO_EXTREMITYFIST) {
			// ���C��
			atkmax = watk;
		} else if(pc_isriding(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR) && t_size == 1) {
			// �y�R�R�悵�Ă��āA���Œ��^���U�������ꍇ�̓T�C�Y�C����100�ɂ���
			atkmax = watk;
		} else if(pc_isdragon(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR)) {
			// �h���S���R�撆�̑��̓T�C�Y�C����100�ɂ���
			atkmax = watk;
		} else {
			int rate = (lh == 0)? sd->atkmods[t_size]: sd->atkmods_[t_size];
			atkmax = (watk   * rate) / 100;
			atkmin = (atkmin * rate) / 100;
		}
		if(sc && sc->data[SC_WEAPONPERFECTION].timer != -1) {
			// �E�F�|���p�[�t�F�N�V����
			atkmax = watk;
		} else if(sd->special_state.no_sizefix) {
			// �h���C�N�J�[�h
			atkmax = watk;
		}
		if(!sd->state.arrow_atk && atkmin > atkmax)
			atkmin = atkmax;	// �|�͍ŒႪ����ꍇ����
		if(lh && atkmin > atkmax)
			atkmin = atkmax;

		/* �ߏ萸�B�{�[�i�X */
		if(!lh && sd->overrefine > 0)
			damage += (atn_rand() % sd->overrefine ) + 1;
		if(lh && sd->overrefine_ > 0)
			damage += (atn_rand() % sd->overrefine_) + 1;
#else
		// ���킪����Ȃ畐��Lv�ƃR�X�g�v�Z
		if(idx >= 0 && sd->inventory_data[idx]) {
			int dstr = str/10;
			damage = str + dstr*dstr/3;	// Str�{�[�i�X�v�Z
			wlv = sd->inventory_data[idx]->wlv;
			cost = (watk*2/3) - (dstr*dstr) * 4 / wlv;
			if(cost < 0)	// �R�X�g��0�ȉ��ɂȂ�Ȃ�
				cost = 0;
		}
		// �ő啐��Atk�ƍŒᕐ��Atk�v�Z
		atkmax = watk * (100 + wlv * 10) / 100 - cost;
		atkmin = (watk * 5 + atkmin * (wlv*3+18) + 14) / 15 - cost;
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
			// �}�W�b�N�N���b�V���[�܂��̓����^���`�F���W���̒ʏ�U���Ȃ�MATK�ŉ���
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
		// �}�L�V�}�C�Y�p���[
		atkmin = atkmax;
	}
	if(skill_num == NPC_EARTHQUAKE)
		// �A�[�X�N�G�C�N
		atkmin = atkmax;

	if(type == 0x0a) {
		/* �N���e�B�J���U�� */
		damage += atkmax;

		if(sc) {
			// �_�� -��-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				damage += sc->data[SC_GENTLETOUCH_CHANGE].val2;
			}
			// �X�g���C�L���O
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

			// �N���e�B�J�����_���[�W����
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1002)
				trans_bonus = 5;
			damage += damage * (sd->critical_damage + sd->crate + trans_bonus) / 100;

			if(sd->state.arrow_atk)
				damage += sd->arrow_atk;
		}
#endif
	} else {
		/* �ʏ�U���E�X�L���U�� */
		if(atkmax > atkmin)
			damage += atkmin + atn_rand() % (atkmax - atkmin + 1);
		else
			damage += atkmin;

		if(sc) {
			// �_�� -��-
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1) {
				damage += sc->data[SC_GENTLETOUCH_CHANGE].val2;
			}
			// �X�g���C�L���O
			if(sc->data[SC_STRIKING].timer != -1) {
				damage += sc->data[SC_STRIKING].val3;
			}
			// ���ԂɌ������ēˌ�
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

		/* �ߏ萸�B�{�[�i�X */
		if( sd->status.weapon != WT_BOW &&	// �|�Əe�ɂ͉ߏ萸�B�{�[�i�X���Ȃ�
			(sd->status.weapon < WT_HANDGUN || sd->status.weapon > WT_GRENADE) ) {
			if(!lh && sd->overrefine > 0)
				damage += (atn_rand() % sd->overrefine ) + 1;
			if(lh && sd->overrefine_ > 0)
				damage += (atn_rand() % sd->overrefine_) + 1;
		}

		/* �T�C�Y�C�� */
		if(pc_isriding(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR) && t_size == 1) {
			// �y�R�R�悵�Ă��āA���Œ��^���U�������ꍇ�̓T�C�Y�C����100�ɂ���
		} else if(pc_isdragon(sd) && (sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR)) {
			// �h���S���R�撆�̑��̓T�C�Y�C����100�ɂ���
		} else if(sc && sc->data[SC_WEAPONPERFECTION].timer != -1) {
			// �E�F�|���p�[�t�F�N�V����
		} else if(sd->special_state.no_sizefix) {
			// �h���C�N�J�[�h
		} else {
			int rate = (lh == 0)? sd->atkmods[t_size]: sd->atkmods_[t_size];
			damage = (damage * rate) / 100;
		}
	}
#endif

	return damage;
}

// ���蔻�肪����Ƃ�����damage2���v�Z����
#define DMG_FIX( a,b ) { wd.damage = wd.damage*(a+(add_rate*b/100))/(b); if(calc_flag.lh) wd.damage2 = wd.damage2*(a+(add_rate*b/100))/(b); }
#define DMG_ADD( a )   { wd.damage += (a); if(calc_flag.lh) wd.damage2 += (a); }
#define DMG_SET( a )   { wd.damage = (a); if(calc_flag.lh) wd.damage2 = (a); }

/*==========================================
 * ����_���[�W�v�Z
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
	int t_flee, t_def1, t_def2, t_res;
	int cardfix, skill, damage_sbr = 0;
	int ignored_rate = 100, ignored_rate_ = 100;
	int i;
	int add_rate = 0;
	struct {
		int rh;			// �E��
		int lh;			// ����
		int hitrate;		// �q�b�g�m��
		int autocounter;	// �I�[�g�J�E���^�[ON
		int da;			// �A������i0�`2�j
		int idef;		// DEF����
		int idef_;		// DEf�����i����j
		int nocardfix;		// �J�[�h�␳�Ȃ�
		int critical;	// �N���e�B�J������i0:�Ȃ��A1:���蒆�A2:�N���e�B�J���m��j
	} calc_flag;

	memset(&calc_flag, 0, sizeof(calc_flag));

	// return�O�̏���������̂ŏ��o�͕��̂ݕύX
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

	// �A�^�b�J�[
	s_ele   = status_get_attack_element(src);	// ����
	s_ele_  = status_get_attack_element2(src);	// ���葮��
	s_str   = status_get_str(src);			// STR
	sc      = status_get_sc(src);		// �X�e�[�^�X�ُ�

	// �^�[�Q�b�g
	t_vit   = status_get_vit(target);
	t_race  = status_get_race(target);		// �Ώۂ̎푰
	t_ele   = status_get_elem_type(target);	// �Ώۂ̑���
	t_enemy = status_get_enemy_type(target);	// �Ώۂ̓G�^�C�v
	t_size  = status_get_size(target);		// �Ώۂ̃T�C�Y
	t_mode  = status_get_mode(target);		// �Ώۂ�Mode
	t_group = status_get_group(target);
	t_class = status_get_class(target);
	t_flee  = status_get_flee(target);
	t_def1  = status_get_def(target);
	t_def2  = status_get_def2(target);
	t_res   = status_get_res(target);		// �Ώۂ�Res
	t_sc    = status_get_sc(target);		// �Ώۂ̃X�e�[�^�X�ُ�

	if(src_sd && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP)
		src_sd->state.attack_type = BF_WEAPON;	// �U���^�C�v�͕���U��

	/* �P�D�I�[�g�J�E���^�[���� */
	if(skill_lv >= 0 && (skill_num == 0 || (target_sd && battle_config.pc_auto_counter_type&2) ||
		(target_md && battle_config.monster_auto_counter_type&2))
	) {
		if( skill_num != CR_GRANDCROSS &&
		    skill_num != NPC_GRANDDARKNESS &&
		    skill_num != NPC_EARTHQUAKE &&
		    skill_num != RA_CLUSTERBOMB &&
		    skill_num != RA_FIRINGTRAP &&
		    skill_num != RA_ICEBOUNDTRAP &&
		    t_sc &&
		    t_sc->data[SC_AUTOCOUNTER].timer != -1 )
		{
			// �O�����h�N���X�łȂ��A�Ώۂ��I�[�g�J�E���^�[��Ԃ̏ꍇ
			int dir   = path_calc_dir(src,target->x,target->y);
			int t_dir = status_get_dir(target);
			int dist  = unit_distance(src,target);

			if(dist <= 0 || path_check_dir(dir,t_dir) ) {
				// �ΏۂƂ̋�����0�ȉ��A�܂��͑Ώۂ̐��ʁH
				t_sc->data[SC_AUTOCOUNTER].val3 = 0;
				t_sc->data[SC_AUTOCOUNTER].val4 = 1;
				if(sc && sc->data[SC_AUTOCOUNTER].timer == -1) {
					int range = status_get_range(target);
					// �������I�[�g�J�E���^�[���
					if( target_sd &&
						(target_sd->status.weapon != WT_BOW && !(target_sd->status.weapon >= WT_HANDGUN && target_sd->status.weapon <= WT_GRENADE))
						&& dist <= range+1)
					{
						// �Ώۂ�PC�ŕ��킪�|��łȂ��˒���
						t_sc->data[SC_AUTOCOUNTER].val3 = src->id;
					}
					if( target_md && range <= 3 && dist <= range+1 ) {
						// �܂��͑Ώۂ�Mob�Ŏ˒���3�ȉ��Ŏ˒���
						t_sc->data[SC_AUTOCOUNTER].val3 = src->id;
					}
				}
				return wd; // �_���[�W�\���̂�Ԃ��ďI��
			}
			calc_flag.autocounter = 1;
		}
	}

	// �L���O�X�O���C�X
	if(t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return wd;

	/* �Q�D�������␳ */
	if( (src_sd && battle_config.pc_attack_attr_none) ||
	    (src_md && battle_config.mob_attack_attr_none) ||
	    (src_pd && battle_config.pet_attack_attr_none) ||
	     src_hd || src_mcd || src_eld )
	{
		// ��������(!=������)
		if (s_ele == ELE_NEUTRAL)
			s_ele  = ELE_NONE;
		if (s_ele_ == ELE_NEUTRAL)
			s_ele_ = ELE_NONE;
	}

#ifdef PRE_RENEWAL
	calc_flag.hitrate = status_get_hit(src) - t_flee + 80;	// pre�������v�Z
#else
	calc_flag.hitrate = status_get_hit(src) - t_flee;	// RE�������v�Z
#endif

	if(t_sc && t_sc->data[SC_FOGWALL].timer != -1) {
		// ����HIT�␳
		calc_flag.hitrate -= 50;
	}
	if(src_sd) {
		// ���b�B
		if((skill = pc_checkskill(src_sd,NC_TRAININGAXE)) > 0) {
			if(src_sd->status.weapon == WT_1HAXE || src_sd->status.weapon == WT_2HAXE)
				calc_flag.hitrate += skill*3;
			if(src_sd->status.weapon == WT_MACE)
				calc_flag.hitrate += skill*2;
		}
		// ���팤��
		calc_flag.hitrate += calc_flag.hitrate * 2 * pc_checkskill(src_sd, BS_WEAPONRESEARCH) / 100;
	}

	/* �R�Dwd�\���̂̏����ݒ� */
	wd.type      = 0;
	wd.div_      = skill_get_num(skill_num,skill_lv);
	wd.blewcount = skill_get_blewcount(skill_num,skill_lv);
	wd.flag      = BF_SHORT | BF_WEAPON | BF_NORMAL;	// �U���̎�ނ̐ݒ�

	if(skill_num == GS_DESPERADO)
		wd.div_ = 1;
	else if(wd.div_ <= 0)
		wd.div_ = 1;

	if(src_sd) {
		if(src_sd->status.weapon == WT_BOW || (src_sd->status.weapon >= WT_HANDGUN && src_sd->status.weapon <= WT_GRENADE)) {	// ���킪�|��̏ꍇ
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;	// �������U���t���O��L��
			if(src_sd->arrow_ele > ELE_NEUTRAL)	// ������Ȃ瑮�����̑����ɕύX
				s_ele = src_sd->arrow_ele;
			src_sd->state.arrow_atk = 1;	// �L����
		} else {
			src_sd->state.arrow_atk = 0;	// ������
		}
		if(pc_checkskill(src_sd,SU_SOULATTACK) > 0 && skill_num == 0) 	// �\�E���A�^�b�N
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;	// �������U���t���O��L��
	} else if(src_md || src_pd || src_mcd || src_eld) {
		if(status_get_range(src) > 3)
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
	}

	/* �S�D�E��E���蔻�� */
	calc_flag.rh = 1;		// ��{�͉E��̂�
	if(src_sd && skill_num == 0) {	// �X�L���U���͏�ɉE����Q��
		if((src_sd->weapontype1 == WT_FIST && src_sd->weapontype2 > WT_FIST) || (src_sd->status.weapon >= WT_DOUBLE_DD || src_sd->status.weapon == WT_KATAR))
			calc_flag.lh = 1;	// ������v�Z
	}

	/* �T�D�A������ */
	if(src_sd && skill_num == 0 && skill_lv >= 0) {
		do {
			// �_�u���A�^�b�N
			if((skill = pc_checkskill(src_sd,TF_DOUBLE)) > 0 && src_sd->weapontype1 == WT_DAGGER && atn_rand()%100 < skill*5) {
				calc_flag.da = 1;
				calc_flag.hitrate = calc_flag.hitrate*(100+skill)/100;
				break;
			}
			// �e����
			if(sc && sc->data[SC_KAGEMUSYA].timer != -1) {
				if((skill = sc->data[SC_KAGEMUSYA].val1) > 0 && atn_rand()%100 < skill*5) {
					calc_flag.da = 1;
					calc_flag.hitrate = calc_flag.hitrate*(100+skill)/100;
				}
				break;
			}
			// �G�^�[�i���`�F�[��
			if(sc && sc->data[SC_E_CHAIN].timer != -1) {
				if((skill = sc->data[SC_E_CHAIN].val1) > 0 && src_sd->weapontype1 != WT_FIST && atn_rand()%100 < skill*5) {
					calc_flag.da = 1;
					status_change_start(src,SC_QD_SHOT_READY,skill,target->id,0,0,skill_get_time2(RL_QD_SHOT,skill),0);
					break;
				}
			}
			// �`�F�[���A�N�V����
			else {
				if((skill = pc_checkskill(src_sd,GS_CHAINACTION)) > 0 && src_sd->weapontype1 == WT_HANDGUN && atn_rand()%100 < skill*5) {
					calc_flag.da = 1;
					if(pc_checkskill(src_sd,RL_QD_SHOT) > 0)
						status_change_start(src,SC_QD_SHOT_READY,skill,target->id,0,0,skill_get_time2(RL_QD_SHOT,skill),0);
					break;
				}
			}
			// �T�C�h���C���_�[��
			if(src_sd->double_rate > 0 && atn_rand()%100 < src_sd->double_rate) {
				calc_flag.da = 1;
				break;
			}
		} while(0);
	} else if (src_md && skill_num == 0) {
		do {
			// �_�u���A�^�b�N
			if (mobdb_search(src_md->class_)->mode_opt[MDOPT_DOUBLE] && atn_rand() % 100 < mobdb_search(src_md->class_)->mode_opt[MDOPT_DOUBLE]*5)
			{
				calc_flag.da = 1;
				calc_flag.hitrate = calc_flag.hitrate * 110 / 100;
				break;
			}
		} while (0);
	}

	/* �U�D�N���e�B�J���v�Z */
	switch(skill_num) {
	case 0:						// �ʏ�U��
	case KN_AUTOCOUNTER:		// �I�[�g�J�E���^�[
	case SN_SHARPSHOOTING:		// �V���[�v�V���[�e�B���O
	case NJ_KIRIKAGE:			// �e�a��
	case LG_PINPOINTATTACK:		// �s���|�C���g�A�^�b�N
	case DK_SERVANTWEAPON_ATK:	// �T�[���@���g�E�F�|��(�U��)
	case DK_SERVANT_W_PHANTOM:	// �T�[���@���g�E�F�|���F�t�@���g��
	case DK_SERVANT_W_DEMOL:	// �T�[���@���g�E�F�|���F�f�����b�V����
	case DK_HACKANDSLASHER:		// �n�b�N�A���h�X���b�V���[
	case DK_HACKANDSLASHER_ATK:	// �n�b�N�A���h�X���b�V���[(�U��)
	case DK_STORMSLASH:			// �X�g�[���X���b�V��
	case IQ_MASSIVE_F_BLASTER:	// ���ΖŖ��_�e
	case IQ_EXPOSION_BLASTER:	// ���ΐ_�e
	case IQ_THIRD_PUNISH:		// ��O���F�f��
	case CD_EFFLIGO:			// �G�t�B���S
	case CD_PETITIO:			// �y�e�B�e�B�I
	case SHC_SAVAGE_IMPACT:		// �T�x�[�W�C���p�N�g
	case SHC_ETERNAL_SLASH:		// �G�^�[�i���X���b�V��
	case SHC_IMPACT_CRATER:		// �C���p�N�g�N���[�^�[
	case SHC_FATAL_SHADOW_CROW:	// �t�F�C�^���V���h�E�N���[
	case ABC_FRENZY_SHOT:		// �t�����W�V���b�g
	case WH_HAWKRUSH:			// �z�[�N���b�V��
	case WH_HAWKBOOMERANG:		// �z�[�N�u�[������
	case SH_HOGOGONG_STRIKE:	// �^�C�K�[�X�g���C�N
	case HN_MEGA_SONIC_BLOW:	// ���K�\�j�b�N�u���[
	case SKE_ALL_IN_THE_SKY:	// �V������
	case SS_KAGEGISSEN:			// �e��M/
	case MT_TRIPLE_LASER:		// �g���v�����[�U�[
	case BO_MAYHEMIC_THORNS:	// ���C�w�~�b�N�\�[���Y
	case MA_SHARPSHOOTING:		// �V���[�v�V���[�e�B���O�i�b���j
		calc_flag.critical = 1;		// �N���e�B�J������𔻒蒆��
		break;
	case WH_GALESTORM:			// �Q�C���X�g�[��
		if(sc && sc->data[SC_CALAMITYGALE].timer != -1)
			calc_flag.critical = 1;		// �J���~�e�B�Q�C�����̂݃N���e�B�J������
		break;
	case NW_ONLY_ONE_BULLET:	// �I�����[�����o���b�g
	case NW_SPIRAL_SHOOTING:	// �X�p�C�����V���[�e�B���O
		if(src_sd && src_sd->status.weapon == WT_RIFLE)
			calc_flag.critical = 1;
		break;
	case NW_MAGAZINE_FOR_ONE:	// �}�K�W���t�H�[����
		if(src_sd && src_sd->status.weapon == WT_HANDGUN)
			calc_flag.critical = 1;
		break;
	case SH_CHUL_HO_SONIC_CLAW:	// �^�C�K�[�X���b�V��
		if((src_sd && pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1))
			calc_flag.critical = 1;
		break;
	case SKE_NOON_BLAST:		// ���V��z
		if(sc && (sc->data[SC_NOON_SUN].timer != -1 || sc->data[SC_SKY_ENCHANT].timer != -1))
			calc_flag.critical = 1;
		break;
	case SKE_SUNSET_BLAST:		// �V�z
		if(sc && (sc->data[SC_SUNSET_SUN].timer != -1 || sc->data[SC_SKY_ENCHANT].timer != -1))
			calc_flag.critical = 1;
		break;

	}
	if( calc_flag.critical != 0 && (!src_md || battle_config.enemy_critical || mobdb_search(src_md->class_)->mode_opt[MDOPT_CRITICAL]) &&
#ifdef PRE_RENEWAL
		calc_flag.da == 0 &&		// PRE�͘A�����������Ă��Ȃ��ꍇ
#endif
		skill_lv >= 0 )
	{
		int cri = status_get_critical(src);
		if(src_sd) {
			if(target_sd && !pc_isdoram(target_sd))
				cri += src_sd->critical_race[RCT_DEMIHUMAN];
			else if(t_race < RCT_ALL)
				cri += src_sd->critical_race[t_race];
			if(src_sd->state.arrow_atk)
				cri += src_sd->arrow_cri;
			if(src_sd->status.weapon == WT_KATAR)
				cri <<= 1;	// �J�^�[���̏ꍇ�A�N���e�B�J����{��
		}
#ifdef PRE_RENEWAL
		cri -= status_get_luk(target) * 3;	// pre�N���e�B�J�����v�Z
#else
		cri -= status_get_luk(target) / 5 * 10;	// RE�N���e�B�J�����v�Z
#endif
		if(src_md && battle_config.enemy_critical_rate != 100) {
			cri = cri * battle_config.enemy_critical_rate / 100;
			if(cri < 1) cri = 1;
		}
		if(src_sd) {
			if(target_sd && !pc_isdoram(target_sd))
				cri += cri * (100 + src_sd->critical_race_rate[RCT_DEMIHUMAN]) / 100;
			else if(t_race < RCT_ALL)
				cri += cri * (100 + src_sd->critical_race_rate[t_race]) / 100;
			if(cri < 1) cri = 1;
		}
		if(t_sc && t_sc->data[SC_SLEEP].timer != -1)
			cri <<= 1;		// �������̓N���e�B�J�����{��
		if(sc && sc->data[SC_CAMOUFLAGE].timer != -1)	// �J���t���[�W��
			cri += 1000 - (10 - sc->data[SC_CAMOUFLAGE].val2) * 100;
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
		} else if(skill_num == LG_PINPOINTATTACK || skill_num == SHC_FATAL_SHADOW_CROW) {
			cri = 1000;
		}

		if(target_sd && target_sd->critical_def) {
			if(target_sd->critical_def > 100)
				cri = 0;
			else
				cri = cri * (100 - target_sd->critical_def) / 100;
		}

		// �m������
		if(atn_rand() % 1000 < cri) {
			if(skill_num != 0 && skill_num != KN_AUTOCOUNTER) {
				// DEF�����t���O
				calc_flag.idef = calc_flag.idef_ = 1;
			} else {
				wd.type = 0x0a;	// �N���e�B�J���U��
			}
			calc_flag.critical = 2;		// �N���e�B�J��������m���
		}
	}

	/* �V�D�q�b�g�E�����E�����W�E�q�b�g�񐔏C�� */
	if(wd.type == 0) {
		int e = ELE_NONE;

		// �����Ȃ�q�b�g�����Z
		if(src_sd && src_sd->state.arrow_atk) {
			calc_flag.hitrate += src_sd->arrow_hit;
		}

		// �����ύX
		if(skill_num > 0) {
			wd.flag = (wd.flag&~BF_SKILLMASK)|BF_SKILL;
			e = skill_get_pl(skill_num);
		}
		if(e != ELE_NONE && e != ELE_NEUTRAL) {
			s_ele = s_ele_ = e;
		} else {
			e = status_get_attack_element_nw(src);
			if(e != ELE_NEUTRAL) {
				// ����ɑ������t�^����Ă���Ȃ�A�t�^�����ɕύX
				s_ele = s_ele_ = e;
			}
		}

		// �������狗���ɂ�锻��
		switch(skill_get_range_type(skill_num)) {
			case 0:	// �ߋ���
				if(skill_num != 0)
					wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
				break;
			case 1:	// �ʏ퉓����
				if(battle_config.calc_dist_flag&1 && (src->type != BL_PC || target->type != BL_PC)) {	// PC vs PC�͋�������
					int target_dist = unit_distance(src,target);	// �������擾
					if(target_dist < battle_config.allow_sw_dist) {	// �ݒ肵��������菬�������ߋ�������̍U��
						if(src->type == BL_PC && battle_config.sw_def_type & 1) {	// �l�Ԃ���̂𔻒肷�邩 +1�ł���
							wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
							break;
						} else if(src->type == BL_MOB && battle_config.sw_def_type & 2) {	// �����X�^�[����̂𔻒肷�邩 +2�ł���
							wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
							break;
						}
					}
				}
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
				break;
			case 2:	// ����������
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
				break;
		}

		switch( skill_num ) {
		case SM_BASH:			// �o�b�V��
		case MS_BASH:
			calc_flag.hitrate = calc_flag.hitrate*(100+5*skill_lv)/100;
			break;
		case KN_PIERCE:			// �s�A�[�X
		case ML_PIERCE:
			calc_flag.hitrate = calc_flag.hitrate*(100+5*skill_lv)/100;
			wd.div_ = t_size + 1;
			break;
		case SM_MAGNUM:			// �}�O�i���u���C�N
		case MS_MAGNUM:
			if(src_md && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over)
				calc_flag.hitrate = calc_flag.hitrate*10;
			else
				calc_flag.hitrate = calc_flag.hitrate*(100+10*skill_lv)/100;
			break;
		case KN_AUTOCOUNTER:		// �I�[�g�J�E���^�[
			wd.flag = (wd.flag&~BF_SKILLMASK)|BF_NORMAL;
			if(battle_config.pc_auto_counter_type&1)
				calc_flag.hitrate += 20;
			else
				calc_flag.hitrate = 1000000;
			break;
		case AS_SONICBLOW:		// �\�j�b�N�u���[
			if(src_sd && pc_checkskill(src_sd,AS_SONICACCEL) > 0)
				calc_flag.hitrate = calc_flag.hitrate*150/100;
			break;
		case CR_SHIELDBOOMERANG:	// �V�[���h�u�[������
			if(sc && sc->data[SC_CRUSADER].timer != -1)
				calc_flag.hitrate = 1000000;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case CR_ACIDDEMONSTRATION:	// �A�V�b�h�f�����X�g���[�V����
		case GN_FIRE_EXPANSION_ACID:	// �t�@�C�A�[�G�N�X�p���V����(���_)
		case NPC_CRITICALSLASH:		// �h�䖳���U��
		case NPC_GUIDEDATTACK:		// �K�C�f�b�h�A�^�b�N
#ifdef PRE_RENEWAL
		case AM_ACIDTERROR:		// �A�V�b�h�e���[
		case MO_INVESTIGATE:		// ����
#endif
		case KO_BAKURETSU:		// ����ꖳ
			calc_flag.hitrate = 1000000;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case MO_EXTREMITYFIST:		// ���C���e�P��
		case NJ_ISSEN:			// ��M
			calc_flag.hitrate = 1000000;
#ifdef PRE_RENEWAL
			s_ele = s_ele_ = ELE_NEUTRAL;
#endif
			break;
		case HVAN_EXPLOSION:		// �o�C�I�G�N�X�v���[�W����
		case RG_BACKSTAP:		// �o�b�N�X�^�u
#ifdef PRE_RENEWAL
		case CR_GRANDCROSS:		// �O�����h�N���X
		case NPC_GRANDDARKNESS:		// �O�����h�_�[�N�l�X
		case AM_DEMONSTRATION:		// �f�����X�g���[�V����
#endif
		case TK_COUNTER:		// �A�v�`���I�����M
		case AS_SPLASHER:		// �x�i���X�v���b�V���[
#ifndef PRE_RENEWAL
		case MO_INVESTIGATE:		// ����
		case GS_MAGICALBULLET:	// �}�W�J���o���b�g
		case ASC_BREAKER:		// �\�E���u���C�J�[
#endif
		case NPC_EARTHQUAKE:	// �A�[�X�N�G�C�N
		case NPC_EXPULSION:		// �G�N�X�p���V�I��
		case NPC_VENOMFOG:		// �x�i���t�H�O
		case RK_DRAGONBREATH:	// �t�@�C�A�[�h���S���u���X
		case RK_DRAGONBREATH_WATER:	// �E�H�[�^�[�h���S���u���X
		case GC_PHANTOMMENACE:		// �t�@���g�����i�X
		case RA_SENSITIVEKEEN:		// �s�q�Țk�o
		case NC_SELFDESTRUCTION:	// �Z���t�f�B�X�g���N�V����
			calc_flag.hitrate = 1000000;
			break;
#ifndef PRE_RENEWAL
		case CR_GRANDCROSS:		// �O�����h�N���X
		case NPC_GRANDDARKNESS:		// �O�����h�_�[�N�l�X
		case AM_DEMONSTRATION:		// �f�����X�g���[�V����
		case AM_ACIDTERROR:		// �A�V�b�h�e���[
			if(src_sd) s_ele = s_ele_ = src_sd->atk_ele;
			e = status_get_attack_element_nw(src);
			if(e != ELE_NEUTRAL) {
				// ����ɑ������t�^����Ă���Ȃ�A�t�^�����ɕύX
				s_ele = s_ele_ = e;
			}
			calc_flag.hitrate = 1000000;
			break;
#endif
		case GS_TRACKING:		// �g���b�L���O
			calc_flag.hitrate = calc_flag.hitrate*4+5;
			break;
		case MO_FINGEROFFENSIVE:	// �w�e
			if(src_sd && battle_config.finger_offensive_type == 0) {
				wd.div_ = src_sd->spiritball.old;
			} else {
				wd.div_ = 1;
			}
			break;
		case AS_VENOMKNIFE:		// �x�i���i�C�t
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				if(src_sd->arrow_ele > ELE_NEUTRAL)	// ������Ȃ瑮�����̑����ɕύX
					s_ele = src_sd->arrow_ele;
			}
			break;
		case NPC_COMBOATTACK:		// ���i�U��
		case NPC_RANDOMATTACK:		// �����_��ATK�U��
		case NPC_RANGEATTACK:		// �������U��
		case NJ_ZENYNAGE:		// �K����
		case NPC_CRITICALWOUND:		// �v�����U��
		case KO_MUCHANAGE:			// ��������
		case RL_HAMMER_OF_GOD:	// �n���}�[�I�u�S�b�h
		case RL_D_TAIL:			// �h���S���e�C��
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case PA_SHIELDCHAIN:		// �V�[���h�`�F�C��
			calc_flag.hitrate += 20;
#ifdef PRE_RENEWAL
			s_ele = s_ele_ = ELE_NEUTRAL;
#endif
			break;
		case NPC_PIERCINGATT:		// �˂��h���U��
		case CR_SHIELDCHARGE:		// �V�[���h�`���[�W
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case BA_MUSICALSTRIKE:		// �~���[�W�J���X�g���C�N
		case DC_THROWARROW:		// ���
		case CG_ARROWVULCAN:		// �A���[�o���J��
			if(src_sd)
				s_ele = src_sd->arrow_ele;
			break;
		case NJ_SYURIKEN:		// �藠������
		case NJ_KUNAI:			// �ꖳ����
		case SS_FUUMASHOUAKU:	// �����藠�� -����-
		case SS_FUUMAKOUCHIKU:	// �����藠�� -�\�z-
		case SS_KUNAIWAIKYOKU:	// �ꖳ -�c��-
		case SS_KUNAIKAITEN:	// �ꖳ -��]-
		case SS_KUNAIKUSSETSU:	// �ꖳ -����-
			if(src_sd && src_sd->arrow_ele > ELE_NEUTRAL)	// ������Ȃ瑮�����̑����ɕύX
				s_ele = src_sd->arrow_ele;
			break;
#ifndef PRE_RENEWAL
		case NJ_TATAMIGAESHI:	// ���Ԃ�
			wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			break;
#endif
		case MH_STAHL_HORN:		// �V���^�[���z�[��
			if(sc && sc->data[SC_GOLDENE_FERSE].timer != -1) {
				if(atn_rand()%100 < sc->data[SC_GOLDENE_FERSE].val1 * 20)
					s_ele = s_ele_ = ELE_HOLY;
			}
			break;
		case MH_SONIC_CRAW:	// �\�j�b�N�N���[
			if(src_hd) {
				wd.div_ = src_hd->spiritball;
			} else {
				wd.div_ = 1;
			}
			break;
		case NPC_DRAGONBREATH:	/* M�h���S���u���X */
			calc_flag.hitrate = 1000000;
			if(skill_lv < 6)
				s_ele = s_ele_ = ELE_FIRE;
			else
				s_ele = s_ele_ = ELE_WATER;
			break;
		case RK_SONICWAVE:		// �\�j�b�N�E�F�[�u
			calc_flag.hitrate += 7 * skill_lv;
			break;
		case GC_VENOMPRESSURE:	// �x�i���v���b�V���[
			calc_flag.hitrate += 10 + skill_lv * 4;
			break;
		case RA_WUGDASH:		// �E�H�[�O�_�b�V��
		case RA_WUGSTRIKE:		// �E�H�[�O�X�g���C�N
		case RA_WUGBITE:		// �E�H�[�O�o�C�g
			s_ele = s_ele_ = ELE_NEUTRAL;
			break;
		case NC_ARMSCANNON:
		case GN_CARTCANNON:		// �J�[�g�L���m��
		case KO_HAPPOKUNAI:		// �����ꖳ
			calc_flag.hitrate = 1000000;
			if(src_sd && src_sd->arrow_ele > ELE_NEUTRAL)	// ������Ȃ瑮�����̑����ɕύX
				s_ele = src_sd->arrow_ele;
			break;
		case SC_FATALMENACE:	// �t�F�C�^�����i�X
			if(skill_lv > 5)
				calc_flag.hitrate += (skill_lv - 6) * 5;
			else
				calc_flag.hitrate -= 5 + (6 - skill_lv) * 5;
			break;
		case LG_BANISHINGPOINT:		// �o�j�V���O�|�C���g
			calc_flag.hitrate = calc_flag.hitrate*(100+3*skill_lv)/100;
			break;
		case LG_HESPERUSLIT:	// �w�X�y���X���b�g
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
		case SR_GATEOFHELL:	// �����j����
			if(skill_lv >= 5)
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
			break;
		case MC_CARTREVOLUTION:		// �J�[�g���{�����[�V����
#ifndef PRE_RENEWAL
			calc_flag.hitrate = 1000000;
#endif
		case GN_CART_TORNADO:		// �J�[�g�g���l�[�h
			if(src_sd && (skill = pc_checkskill(src_sd,GN_REMODELING_CART)) > 0)
				calc_flag.hitrate = calc_flag.hitrate+skill*4;
			break;
		case RL_SLUGSHOT:		// �X���b�O�V���b�g
			{
				int dist = unit_distance(src,target)-1;
				if(dist > 3)
					calc_flag.hitrate = calc_flag.hitrate*(100-((11 - skill_lv) * (dist-3)))/100;
				s_ele = s_ele_ = ELE_NEUTRAL;
			}
			break;
		case RL_H_MINE:		// �n�E�����O�}�C��(�ǌ�)
			if(wflag&1)
				s_ele = s_ele_ = ELE_FIRE;
			break;
		case DK_HACKANDSLASHER:			// �n�b�N�A���h�X���b�V���[
		case DK_HACKANDSLASHER_ATK:		// �n�b�N�A���h�X���b�V���[(�U��)
			if(src_sd && src_sd->status.weapon == WT_2HSWORD) {
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			} else if(src_sd && src_sd->status.weapon == WT_2HSPEAR) {
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
			}
			break;
		case CD_PETITIO:	// �y�e�B�e�B�I
			if(src_sd && src_sd->status.weapon == WT_MACE) {
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_LONG;
			} else if(src_sd && src_sd->status.weapon == WT_BOOK) {
				wd.flag = (wd.flag&~BF_RANGEMASK)|BF_SHORT;
			}
			break;
		case NW_BASIC_GRENADE:			/* �x�[�V�b�N�O���l�[�h */
		case NW_HASTY_FIRE_IN_THE_HOLE:	/* �w�C�X�e�B�t�@�C�A�C���U�z�[�� */
		case NW_GRENADES_DROPPING:		/* �O���l�[�Y�h���b�s���O */
			if(sc) {
				if(sc->data[SC_GRENADE_FRAGMENT_1].timer != -1)
					s_ele = s_ele_ = ELE_WATER;
				else if(sc->data[SC_GRENADE_FRAGMENT_2].timer != -1)
					s_ele = s_ele_ = ELE_WIND;
				else if(sc->data[SC_GRENADE_FRAGMENT_3].timer != -1)
					s_ele = s_ele_ = ELE_EARTH;
				else if(sc->data[SC_GRENADE_FRAGMENT_4].timer != -1)
					s_ele = s_ele_ = ELE_FIRE;
				else if(sc->data[SC_GRENADE_FRAGMENT_5].timer != -1)
					s_ele = s_ele_ = ELE_DARK;
				else if(sc->data[SC_GRENADE_FRAGMENT_6].timer != -1)
					s_ele = s_ele_ = ELE_HOLY;
			}
			break;
		}
	}

	// �T�N���t�@�C�X
	if(sc && sc->data[SC_SACRIFICE].timer != -1 && !skill_num && t_class != MOBID_EMPERIUM) {
		calc_flag.hitrate = 1000000;
		s_ele = s_ele_ = ELE_NEUTRAL;
	}
	// ���z�ƌ��Ɛ��̗Z��
	if(sc && sc->data[SC_FUSION].timer != -1) {
		calc_flag.hitrate = 1000000;
	}
	// �X�y���t�B�X�g
	if(sc && sc->data[SC_SPELLFIST].timer != -1 && !skill_num && t_class != MOBID_EMPERIUM) {
		calc_flag.hitrate = 1000000;
	}
	// �J�[�h���ʂɂ��K���{�[�i�X
	if(src_sd && src_sd->perfect_hit > 0) {
		if(atn_rand()%100 < src_sd->perfect_hit)
			calc_flag.hitrate = 1000000;
	}
	// �Ώۂ���Ԉُ풆�̏ꍇ�̕K���{�[�i�X
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

	/* �W�D��𔻒� */
	if(wd.type == 0 && atn_rand()%100 >= calc_flag.hitrate) {
		wd.dmg_lv = ATK_FLEE;
	}
	else if(wd.type == 0 && t_sc && t_sc->data[SC_UTSUSEMI].timer != -1) {	// ���
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
	else if(wd.type == 0 && t_sc && t_sc->data[SC_BUNSINJYUTSU].timer != -1) {	// �e���g
		wd.dmg_lv = ATK_FLEE;
		if(--t_sc->data[SC_BUNSINJYUTSU].val3 == 0)
			status_change_end(target,SC_BUNSINJYUTSU,-1);
	}
	else if(target_sd && t_sc && t_sc->data[SC_DODGE].timer != -1 && (wd.flag&BF_LONG || t_sc->data[SC_SPURT].timer != -1) && atn_rand()%100 < 20) {	// ���@
		int slv = pc_checkskill(target_sd,TK_DODGE);
		wd.dmg_lv = ATK_FLEE;
		clif_skill_nodamage(&target_sd->bl,&target_sd->bl,TK_DODGE,slv,1);
		status_change_start(&target_sd->bl,SC_DODGE_DELAY,slv,src->id,0,0,skill_get_time(TK_DODGE,slv),0);
	}
	else if(t_sc && (t_sc->data[SC_FOGWALL].timer != -1 || t_sc->data[SC_FOGWALLPENALTY].timer != -1) && wd.flag&BF_LONG && !skill_num && atn_rand()%100 < 75) {	// �E�H�[���I�u�t�H�O�@�������ʏ�U����75%�̊m���Ń~�X
		wd.dmg_lv = ATK_FLEE;	// �ʏ���
	}

	else {
		atn_bignumber damage_ot = 0, damage_ot2 = 0;
#ifdef PRE_RENEWAL
		atn_bignumber tk_power_damage = 0, tk_power_damage2 = 0;
#endif

		// ����ł��Ȃ������Ƃ��̂�step9�`18�̃_���[�W�v�Z���s��
		wd.dmg_lv = ATK_DEF;

		/* �X�D��{�_���[�W�̎Z�o */
		wd.damage = battle_calc_base_damage(src, target, skill_num, wd.type, 0);
#ifdef PRE_RENEWAL
		if(calc_flag.lh)
			wd.damage2 = battle_calc_base_damage(src, target, skill_num, wd.type, 1);
#else
		if(calc_flag.lh)
			wd.damage2 = battle_calc_base_damage(src, target, skill_num, 0, 1);
#endif

		// �S�[���f���y���W�F���
		if(sc && sc->data[SC_GOLDENE_FERSE].timer != -1 && (!skill_num || skill_num == MH_STAHL_HORN)) {
			if(atn_rand()%100 < sc->data[SC_GOLDENE_FERSE].val1 * 20) {
				atn_bignumber bonus_damage;
				bonus_damage = battle_attr_fix(wd.damage, ELE_HOLY, status_get_element(target));
				if(bonus_damage > 0)
					wd.damage += bonus_damage * sc->data[SC_GOLDENE_FERSE].val4 / 100;
			}
		}
#ifdef PRE_RENEWAL
		if(wd.type == 0) {	// �N���e�B�J���łȂ��Ƃ���̃_���[�W�����Z
			if(src_sd && src_sd->state.arrow_atk && src_sd->arrow_atk > 0)
				wd.damage += atn_rand()%(src_sd->arrow_atk+1);
		}
#else
		// �iRE�j�}�O�i���u���C�N���
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
				atn_bignumber bonus_damage;
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

		// �iRE�j�y���F����
		if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
			wd.damage += (wd.damage * src_sd->elementball.num * 10) / 100;
			if(calc_flag.lh)
				wd.damage2 += (wd.damage2 * src_sd->elementball.num * 10) / 100;
		}

		if(wd.flag&BF_LONG) {
			if(src_sd && pc_checkskill(src_sd, SU_POWEROFLIFE) > 0 && pc_checkskill_summoner(src_sd, SU_POWEROFLIFE) >= 20) {
				wd.damage += wd.damage * 10 / 100;
				if(calc_flag.lh)
					wd.damage2 += wd.damage2 * 10 / 100;
			}
		}

		/* �iRE�j�h�䖳�����肨��ѐ����ʃ_���[�W�v�Z */
		switch (skill_num) {
		case MC_CARTREVOLUTION:
		case KN_AUTOCOUNTER:
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
		case NPC_EARTHQUAKE:
		case MO_EXTREMITYFIST:
		case AM_DEMONSTRATION:
		case AM_ACIDTERROR:
		case CR_ACIDDEMONSTRATION:
		case ASC_BREAKER:
		case GS_FLING:
		case NJ_ZENYNAGE:
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
				// bIgnoreDef�n����
				ignored_rate  = ignored_rate  - src_sd->ignore_def_ele[t_ele]  - src_sd->ignore_def_race[t_race]  - src_sd->ignore_def_enemy[t_enemy];
				ignored_rate_ = ignored_rate_ - src_sd->ignore_def_ele_[t_ele] - src_sd->ignore_def_race_[t_race] - src_sd->ignore_def_enemy_[t_enemy];
				if(t_mode & MD_BOSS) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_BOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_BOSS];
				} else {
					ignored_rate  -= src_sd->ignore_def_race[RCT_NONBOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_NONBOSS];
				}

				if(battle_config.left_cardfix_to_right) {
					// ����J�[�h�␳�ݒ肠��
					ignored_rate -= 100 - ignored_rate_;
					ignored_rate_ = ignored_rate;
				}

				// bDefRatioATK�n����
				if(skill_num != AM_ACIDTERROR && ignored_rate > 0) {
					int def_ratio = 0;
					int mask = (1<<t_race) | ( (t_mode&MD_BOSS)? (1<<RCT_BOSS): (1<<RCT_NONBOSS));
					int def_fix = t_def1 * ignored_rate / 100;

					if(src_sd->def_ratio_atk_ele & (1<<t_ele) || src_sd->def_ratio_atk_race & mask || src_sd->def_ratio_atk_enemy & (1<<t_enemy) ||
					   src_sd->def_ratio_atk_ele_ & (1<<t_ele) || src_sd->def_ratio_atk_race_ & mask || src_sd->def_ratio_atk_enemy_ & (1<<t_enemy)
					)
						def_ratio = 1;

					// bIgnoreDef�n�����������Čv�Z
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

		// �iRE�j����Atk�̕␳
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
		/* 10�D�t�@�C�e�B���O�v�Z */
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

		/* 11�D�I�[�o�[�g���X�g�n�̃X�L���{���v�Z�O�̍U���͊m�� */
		damage_ot += wd.damage;
		if(calc_flag.lh)
			damage_ot2 += wd.damage2;

#ifndef PRE_RENEWAL
		/* �iRE�j�J�[�h�ɂ��_���[�W�ǉ����� */
		if( src_sd && wd.damage > 0 && calc_flag.rh ) {
			if(!src_sd->state.arrow_atk) {	// �|��ȊO
				if(!battle_config.left_cardfix_to_right) {	// ����J�[�h�␳�ݒ薳��
					wd.damage = wd.damage*(100+src_sd->addrace[t_race])/100;	// �푰�ɂ��_���[�W�C��
					wd.damage = wd.damage*(100+src_sd->addsize[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C��
					wd.damage = wd.damage*(100+src_sd->addele[t_ele])/100;	// �����ɂ��_���[�W�C��
					wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��
					wd.damage = wd.damage*(100+src_sd->addgroup[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��
				} else {
					wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;		// �푰�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					wd.damage = wd.damage*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;		// �T�C�Y�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					wd.damage = wd.damage*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;		// �����ɂ��_���[�W�C��(����ɂ��ǉ�����)
					wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					wd.damage = wd.damage*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��(����ɂ��ǉ�����)
				}
			} else { // �|��
				wd.damage = wd.damage*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race])/100;	// �푰�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				wd.damage = wd.damage*(100+src_sd->addsize[t_size]+src_sd->arrow_addsize[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				wd.damage = wd.damage*(100+src_sd->addele[t_ele]+src_sd->arrow_addele[t_ele])/100;		// �����ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				wd.damage = wd.damage*(100+src_sd->addenemy[t_enemy]+src_sd->arrow_addenemy[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				wd.damage = wd.damage*(100+src_sd->addgroup[t_group]+src_sd->arrow_addgroup[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
			}
			if(t_mode & MD_BOSS) {	// �{�X
				if(!src_sd->state.arrow_atk) {	// �|��U���ȊO�Ȃ�
					if(!battle_config.left_cardfix_to_right) {
						// ����J�[�h�␳�ݒ薳��
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS])/100;					// �{�X�����X�^�[�ɒǉ��_���[�W
					} else {
						// ����J�[�h�␳�ݒ肠��
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;	// �{�X�����X�^�[�ɒǉ��_���[�W(����ɂ��ǉ�����)
					}
				} else {	// �|��U��
					wd.damage = wd.damage*(100+src_sd->addrace[RCT_BOSS]+src_sd->arrow_addrace[RCT_BOSS])/100;		// �{�X�����X�^�[�ɒǉ��_���[�W(�|��ɂ��ǉ�����)
				}
			} else {		// �{�X����Ȃ�
				if(!src_sd->state.arrow_atk) {	// �|��U���ȊO
					if(!battle_config.left_cardfix_to_right) {
						// ����J�[�h�␳�ݒ薳��
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS])/100;				// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W
					} else {
						// ����J�[�h�␳�ݒ肠��
						wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W(����ɂ��ǉ�����)
					}
				} else {
					wd.damage = wd.damage*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->arrow_addrace[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W(�|��ɂ��ǉ�����)
				}
			}
			// ����Class�p�␳����(�����̓��L���{���S���p�H)
			for(i=0; i<src_sd->add_damage_class_count; i++) {
				if(src_sd->add_damage_classid[i] == t_class) {
					wd.damage = wd.damage*(100+src_sd->add_damage_classrate[i])/100;
					break;
				}
			}
		}

		/* �iRE�j�J�[�h�ɂ�鍶��_���[�W�ǉ����� */
		if( src_sd && wd.damage2 > 0 && calc_flag.lh ) {
//			if(!battle_config.left_cardfix_to_right) {	// ����J�[�h�␳�ݒ薳��
				wd.damage2 = wd.damage2*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;	// �푰�ɂ��_���[�W�C������
				wd.damage2 = wd.damage2*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C������
				wd.damage2 = wd.damage2*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;	// �����ɂ��_���[�W�C������
				wd.damage2 = wd.damage2*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C������
				wd.damage2 = wd.damage2*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// �O���[�v�ɂ��_���[�W�C������
				if(t_mode & MD_BOSS)	// �{�X
					wd.damage2 = wd.damage2*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;		// �{�X�����X�^�[�ɒǉ��_���[�W����
				else
					wd.damage2 = wd.damage2*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W����
//			}
			// ����Class�p�␳��������(�����̓��L���{���S���p�H)
			for(i=0; i<src_sd->add_damage_class_count_; i++) {
				if(src_sd->add_damage_classid_[i] == t_class) {
					wd.damage2 = wd.damage2*(100+src_sd->add_damage_classrate_[i])/100;
					break;
				}
			}
		}

		/* �iRE�j�J�[�h�ɂ��_���[�W�������� */
		if( target_sd && (wd.damage > 0 || wd.damage2 > 0 || damage_sbr > 0) && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != NPC_CRITICALSLASH) {	// �Ώۂ�PC�̏ꍇ
			int s_enemy = status_get_enemy_type(src);
			int s_size  = status_get_size(src);
			int s_group = status_get_group(src);
			int ele_type= status_get_elem_type(src);
			cardfix = 100;
			if (s_ele == ELE_NONE)
				cardfix = cardfix*(100-target_sd->subele[ELE_NEUTRAL])/100;	// ���������̑ϐ��͖�����
			else
				cardfix = cardfix*(100-target_sd->subele[s_ele])/100;		// �����ɂ��_���[�W�ϐ�
			if (ele_type == ELE_NONE)
				cardfix = cardfix*(100-target_sd->def_eleenemy[ELE_NEUTRAL])/100;	// ���������̑ϐ��͖�����
			else
				cardfix = cardfix*(100-target_sd->def_eleenemy[ele_type])/100;		// �G�����ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-target_sd->subenemy[s_enemy])/100;		// �G�^�C�v�ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-target_sd->subsize[s_size])/100;			// �T�C�Y�ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-target_sd->subgroup[s_group])/100;		// �O���[�v�ɂ��_���[�W�ϐ�

			if(status_get_mode(src) & MD_BOSS)
				cardfix = cardfix*(100-target_sd->subrace[RCT_BOSS])/100;	// �{�X����̍U���̓_���[�W����
			else
				cardfix = cardfix*(100-target_sd->subrace[RCT_NONBOSS])/100;	// �{�X�ȊO����̍U���̓_���[�W����

			// ����Class�p�␳��������(�����̓��L���{���S���p�H)
			for(i=0; i<target_sd->add_def_class_count; i++) {
				if(target_sd->add_def_classid[i] == status_get_class(src)) {
					cardfix = cardfix*(100-target_sd->add_def_classrate[i])/100;
					break;
				}
			}
			if(wd.flag&BF_LONG && !(src_md && (skill_num == AC_SHOWER || skill_num == SN_SHARPSHOOTING)) )
				cardfix = cardfix*(100-target_sd->long_attack_def_rate)/100;	// �������U���̓_���[�W����(�z����C�Ƃ�)
			if(wd.flag&BF_SHORT)
				cardfix = cardfix*(100-target_sd->near_attack_def_rate)/100;	// �ߋ����U���̓_���[�W����(�Y�������H)
			DMG_FIX( cardfix, 100 );	// �J�[�h�␳�ɂ��_���[�W����

			damage_sbr = damage_sbr * cardfix / 100;	// �J�[�h�␳�ɂ��\�E���u���C�J�[�̖��@�_���[�W����
		}

		// �G�E�J���X�e�B�J
		if(target_sd && (skill = pc_checkskill(target_sd,AB_EUCHARISTICA)) > 0) {
			if(s_ele == ELE_UNDEAD || s_ele == ELE_DARK)
				DMG_FIX( 100-skill, 100 );
		}

		// �X�p�C�_�[�E�F�u
		if(t_sc && t_sc->data[SC_SPIDERWEB].timer != -1 && s_ele == ELE_FIRE) {
			wd.damage <<= 1;
			if(calc_flag.lh)
				wd.damage2 <<= 1;
			status_change_end(target, SC_SPIDERWEB, -1);
		}

		/* �iRE�j�����̓K�p */
		if(skill_num != MO_EXTREMITYFIST && skill_num != NJ_ISSEN && skill_num != SJ_NOVAEXPLOSING) {
			wd.damage = battle_attr_fix(wd.damage, s_ele, status_get_element(target));
			if(calc_flag.lh)
				wd.damage2 = battle_attr_fix(wd.damage2, s_ele_, status_get_element(target));
		}

		/* �iRE�j�����␳ */
		if( (sc || t_sc) && (wd.damage > 0 || wd.damage2 > 0) && skill_num != MO_EXTREMITYFIST && skill_num != NJ_ISSEN && skill_num != SJ_NOVAEXPLOSING) {
			cardfix = 100;
			if(sc) {
				// �{���P�[�m
				if(sc->data[SC_VOLCANO].timer != -1 && s_ele == ELE_FIRE)
					cardfix += sc->data[SC_VOLCANO].val4;
				// �o�C�I�����g�Q�C��
				if(sc->data[SC_VIOLENTGALE].timer != -1 && s_ele == ELE_WIND)
					cardfix += sc->data[SC_VIOLENTGALE].val4;
				// �f�����[�W
				if(sc->data[SC_DELUGE].timer != -1 && s_ele == ELE_FIRE)
					cardfix += sc->data[SC_DELUGE].val4;
			}
			if(t_sc) {
				// �J�C�g
				if(t_sc->data[SC_KAITE].timer != -1)
					cardfix += 300;
				// �x�i���C���v���X
				if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && s_ele == ELE_POISON)
					cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
				// �I���e�B�I
				if(t_sc->data[SC_ORATIO].timer != -1 && s_ele == ELE_HOLY)
					cardfix += t_sc->data[SC_ORATIO].val2;
				// ����߈�
				if(t_sc->data[SC_SOULCURSE].timer != -1 && s_ele == ELE_DARK)
					cardfix += t_sc->data[SC_SOULCURSE].val2;
				// ����
				if(t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 && s_ele == ELE_EARTH)
					cardfix += t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].val2;
				// ����
				if(t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1 && s_ele == ELE_POISON)
					cardfix += t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].val2;
				// �N���C�}�b�N�X�N�G�C�N
				if(t_sc->data[SC_CLIMAX_EARTH].timer != -1 && s_ele == ELE_EARTH)
					cardfix += t_sc->data[SC_CLIMAX_EARTH].val2;
				// �N���C�}�b�N�X�u���[��
				if(t_sc->data[SC_CLIMAX_BLOOM].timer != -1 && s_ele == ELE_FIRE)
					cardfix += t_sc->data[SC_CLIMAX_BLOOM].val2;
				// �W���b�N�t���X�g�m���@
				if(t_sc->data[SC_MISTYFROST].timer != -1 && s_ele == ELE_WATER)
					cardfix += t_sc->data[SC_MISTYFROST].val2;
			}
			DMG_FIX( cardfix, 100 );
		}

		// �G���`�����g�f�b�h���[�|�C�Y��
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
			case NPC_EARTHQUAKE:
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

		// �iRE�j�X�e�[�^�XAtk�����Z
		if(src_sd || (!src_sd && battle_config.enemy_str)) {
			int s_ele__ = ELE_NEUTRAL;		// ��{������
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {	// �g�������̓X�e�[�^�XAtk�ɂ�������
				s_ele__ = sc->data[SC_SEVENWIND].val3;
			}
			wd.damage += battle_attr_fix(status_get_baseatk(src), s_ele__, status_get_element(target));
			/* �iRE�j����_���[�W�̌v�Z���� */
			if(calc_flag.lh) {
				wd.damage2 = wd.damage2 * 75 / 100;
				wd.damage2 += battle_attr_fix(status_get_baseatk(src)/2, s_ele__, status_get_element(target));
			}
		}

		if(src_sd) {
			// ���̂�����A�C���̓K�p
			int hit_bonus  = (src_sd->spiritball.old>0? src_sd->spiritball.old * 3: src_sd->spiritball.num * 3) + src_sd->coin.num * 3 + src_sd->bonus_damage;
			int hit_damage = hit_bonus + src_sd->star + src_sd->ranker_weapon_bonus;

			if(skill_num == NJ_KUNAI || skill_num == KO_HAPPOKUNAI) {	// �ꖳ�����A�����ꖳ
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
			case NPC_EARTHQUAKE:
			case AM_DEMONSTRATION:
			case AM_ACIDTERROR:
			case PA_SHIELDCHAIN:
			case CR_ACIDDEMONSTRATION:
			case ASC_BREAKER:
			case GS_FLING:
			case NJ_ZENYNAGE:
			case RA_CLUSTERBOMB:
			case RA_FIRINGTRAP:
			case RA_ICEBOUNDTRAP:
			case GN_FIRE_EXPANSION_ACID:
			case KO_MUCHANAGE:
				break;
			case RA_WUGSTRIKE:
			case RA_WUGBITE:
				if((skill = pc_checkskill(src_sd,RA_TOOTHOFWUG)) > 0) {	// �g�D�[�X�I�u�E�H�[�O�ɂ��_���[�W����
					wd.damage += 10 * skill;
				}
				break;
			default:
				if(skill_lv < 0)
					break;
				wd.damage = battle_addmastery(src_sd,target,wd.damage,0);
				if(calc_flag.lh)
					wd.damage2 = battle_addmastery(src_sd,target,wd.damage2,1);
				break;
			}
		}

		/* �iRE�j�C���nBUFF���� */
		if(sc && skill_num != MO_EXTREMITYFIST) {
			// �C���|�V�e�B�I�}�k�X
			if(sc->data[SC_IMPOSITIO].timer != -1) {
				wd.damage += sc->data[SC_IMPOSITIO].val1*5;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_IMPOSITIO].val1*5;
			}
			// �푾�ۂ̋���
			if(sc->data[SC_DRUMBATTLE].timer != -1) {
				wd.damage += sc->data[SC_DRUMBATTLE].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_DRUMBATTLE].val2;
			}
			// �j�[�x�����O�̎w��
			if(sc->data[SC_NIBELUNGEN].timer != -1) {
				wd.damage += sc->data[SC_NIBELUNGEN].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_NIBELUNGEN].val2;
			}
			// �J���t���[�W��
			if(sc->data[SC_CAMOUFLAGE].timer != -1) {
				wd.damage += 300 - (10 - sc->data[SC_CAMOUFLAGE].val2) * 30;
				if(calc_flag.lh)
					wd.damage2 += 300 - (10 - sc->data[SC_CAMOUFLAGE].val2) * 30;
			}
			// �J�[�g�u�[�X�g
			if(sc->data[SC_GN_CARTBOOST].timer != -1) {
				wd.damage += sc->data[SC_GN_CARTBOOST].val1 * 10;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_GN_CARTBOOST].val1 * 10;
			}
			// �v���`�i���A���^�[
			if(sc->data[SC_P_ALTER].timer != -1) {
				wd.damage += sc->data[SC_P_ALTER].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_P_ALTER].val2;
			}
		}

		/* �iRE�j�J�[�h�ɂ��_���[�W���������Q */
		if( target_sd && (wd.damage > 0 || wd.damage2 > 0) && skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != NPC_CRITICALSLASH && skill_num != NPC_EARTHQUAKE) {	// �Ώۂ�PC�̏ꍇ
			int s_race  = status_get_race(src);
			cardfix = 100;
			if(t_sc && t_sc->data[SC_ANTI_M_BLAST].timer != -1)
				cardfix = cardfix*(100-target_sd->subrace[s_race]-t_sc->data[SC_ANTI_M_BLAST].val2)/100;			// �푰�ɂ��_���[�W�ϐ�
			else
				cardfix = cardfix*(100-target_sd->subrace[s_race])/100;			// �푰�ɂ��_���[�W�ϐ�
			DMG_FIX( cardfix, 100 );	// �J�[�h�␳�ɂ��_���[�W����
		}

		// �G�E�J���X�e�B�J
		if(src_sd && (skill = pc_checkskill(src_sd,AB_EUCHARISTICA)) > 0) {
			if(t_ele == ELE_UNDEAD || t_ele == ELE_DARK) {
				wd.damage += wd.damage * skill / 100;
				if(calc_flag.lh)
					wd.damage2 += wd.damage2 * skill / 100;
			}
		}

		// �iRE�j�N���e�B�J���_���[�W����
		if(calc_flag.critical == 2) {
			if(src_sd) {
				int add_rate = src_sd->critical_damage;

				// �N���e�B�J�����_���[�W����
				if(src_sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && src_sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1002)
					add_rate += 5;

				if(skill_num == WH_HAWKRUSH) {			// �z�[�N���b�V���̏ꍇ�̓_���[�W�{����1/4��
					add_rate = add_rate/4;
				} else if(skill_num == WH_HAWKBOOMERANG) {		// �z�[�N�u�[�������̏ꍇ�̓_���[�W�{����1.25�{��
					add_rate = add_rate * 125 / 100;
				} else if(skill_num != 0) {					// ���̑��̃X�L���U���̏ꍇ�̓_���[�W�{����1/2��
					add_rate = add_rate/2;
				}
				wd.damage = wd.damage * (100 + add_rate) / 100;
			}
		}
#endif

		/* �X�L���{���v�Z�ɉ��Z */
		if(sc && skill_num != NPC_EARTHQUAKE) {
#ifndef PRE_RENEWAL
			// �I�[�o�[�g���X�g
			if(sc->data[SC_OVERTHRUST].timer != -1)
				add_rate += sc->data[SC_OVERTHRUST].val3;
			// �I�[�o�[�g���X�g�}�b�N�X
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1)
				add_rate += 20*sc->data[SC_OVERTHRUSTMAX].val1;
			// �u���b�f�B���X�g
			if(sc->data[SC__BLOODYLUST].timer != -1)
				add_rate += 32;
			// �v���{�b�N
			else if(sc->data[SC_PROVOKE].timer != -1)
				add_rate += 2 + 3 * sc->data[SC_PROVOKE].val1;
			// �g�D���[�T�C�g
			if(sc->data[SC_TRUESIGHT].timer != -1)
				add_rate += 2*sc->data[SC_TRUESIGHT].val1;
			// �R���Z���g���[�V����
			if(sc->data[SC_CONCENTRATION].timer != -1)
				add_rate += 5*sc->data[SC_CONCENTRATION].val1;
			// �S�X�y����Atk2�{
			if(sc->data[SC_INCATK2].timer != -1)
				add_rate += sc->data[SC_INCATK2].val1;
			// �o�[�T�[�N
			if(sc->data[SC_BERSERK].timer != -1)
				add_rate += 200;
			// ��
			if(sc->data[SC_CURSE].timer != -1)
				add_rate -= 25;
			// NPC�����g��
			if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && !src_sd)
				add_rate += 200;
			// �G�X�N
			if(sc->data[SC_SKE].timer != -1 && src_md)
				add_rate += 300;
#endif
			// �q�[�g�o����
			if(sc->data[SC_HEAT_BARREL].timer != -1)
				add_rate += sc->data[SC_HEAT_BARREL].val3;
		}
		// �h���S�m���W�[
		if(src_sd && t_race == RCT_DRAGON && (skill = pc_checkskill(src_sd,SA_DRAGONOLOGY)) > 0)
			add_rate += skill*4;

#ifndef PRE_RENEWAL
		switch( skill_num ) {
		case NJ_ISSEN:		// ��M
			{
				int maxhp = status_get_max_hp(src) / 100;
				int hp = status_get_hp(src);
				if(maxhp < hp) {
					wd.damage = wd.damage * skill_lv + hp;
					unit_heal(src,-(hp-maxhp),0,0,0);
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
		case GS_MAGICALBULLET:	// �}�W�J���o���b�g
			{
				static struct Damage mgd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

				mgd = battle_calc_attack(BF_MAGIC,src,target,skill_num,skill_lv,wd.flag);
				wd.damage += mgd.damage;
				wd.damage = wd.damage - (t_def1 + t_def2);
			}
			break;
		case LK_SPIRALPIERCE:	// �X�p�C�����s�A�[�X
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
		case PA_SHIELDCHAIN:	// �V�[���h�`�F�C��
			if(src_sd) {
				int idx  = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_ADD( src_sd->inventory_data[idx]->weight/10 );
					if(src_sd->sc.data[SC_SHIELD_POWER].timer != -1) {
						DMG_FIX( 300+60*skill_lv, 100 );
						DMG_ADD( src_sd->status.inventory[idx].refine*(1200+skill_lv*240)/100 );
					} else {
						DMG_FIX( 100+30*skill_lv, 100 );
						DMG_ADD( src_sd->status.inventory[idx].refine*(400+skill_lv*120)/100 );
					}
				} else {
					DMG_FIX( 100+30*skill_lv, 100 );
				}
			} else {
				DMG_FIX( 100+30*skill_lv, 100 );
			}
			break;
		case AM_DEMONSTRATION:	// �f�����X�g���[�V����
		case AM_ACIDTERROR:	// �A�V�b�h�e���[
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
						int r = attr_fix_table[def_lv-1][ELE_FIRE][def_type];
						wd.damage -= wd.damage * (100 - r) / 100;
					}
				} else if(t_mode&MD_BOSS) {
					wd.damage = wd.damage / 2;
				}
			}
			break;
		case ASC_BREAKER:	// �\�E���u���C�J�[
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
		case CR_ACIDDEMONSTRATION:	// �A�V�b�h�f�����X�g���[�V����
		case GN_FIRE_EXPANSION_ACID:	// �t�@�C�A�[�G�N�X�p���V����(���_)
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
		case NC_ARMSCANNON:	// �A�[���Y�L���m��
			if(src_sd && src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
			DMG_FIX( (300 + (400 - 50 * t_size) * skill_lv) * status_get_lv(src) / 120, 100 );
			if(sc && sc->data[SC_ABR_DUAL_CANNON].timer != -1) {
				wd.div_ = 2;
			}
			break;
		case NPC_CRITICALSLASH:	// �N���e�B�J���X���b�V��
			if(src_md) {
				if(battle_config.monster_atk2_to_matk) {
					wd.damage = mobdb_search(src_md->class_)->atk1 + mobdb_search(src_md->class_)->atk2;
				}
				else {
					int int_ = mobdb_search(src_md->class_)->int_;

					wd.damage  = (mobdb_search(src_md->class_)->atk1 + mobdb_search(src_md->class_)->atk2) / 2;
					wd.damage += ((int_+(int_/5)*(int_/5)) + (int_+(int_/7)*(int_/7))) / 2;
				}
			}
		}

		if( src_sd && wd.damage > 0 && calc_flag.rh ) {
			// �iRE�j�J�[�h���ʂɂ����背���W�U���̃_���[�W����
			if(wd.flag&BF_SHORT) {
				wd.damage = wd.damage * (100+src_sd->short_weapon_damege_rate) / 100;
			}
			if(wd.flag&BF_LONG) {
				wd.damage = wd.damage * (100+src_sd->long_weapon_damege_rate) / 100;
			}
		}
#endif

		// �A�����~�b�g
		if(sc && sc->data[SC_UNLIMIT].timer != -1 && wd.flag&BF_LONG && skill_num != HT_BLITZBEAT && skill_num != SN_FALCONASSAULT
		 && skill_num != RA_WUGDASH && skill_num != RA_WUGSTRIKE && skill_num != RA_WUGBITE)
			wd.damage += wd.damage * sc->data[SC_UNLIMIT].val2 / 100;

		/* 12�D�X�L���C���P�i�U���͔{���n�j*/
		switch( skill_num ) {
		case SM_BASH:		// �o�b�V��
		case MS_BASH:
			DMG_FIX( 100+30*skill_lv, 100 );
			break;
		case SM_MAGNUM:		// �}�O�i���u���C�N
		case MS_MAGNUM:
			if(src_md && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
				DMG_FIX( 1000, 100 );
			} else {
				if(!wflag) {	// ����
					DMG_FIX( 100+20*skill_lv, 100 );
				} else {	// �O��
					DMG_FIX( 100+10*skill_lv, 100 );
				}
			}
			break;
		case MC_MAMMONITE:	// ���}�[�i�C�g
			DMG_FIX( 100+50*skill_lv, 100 );
			break;
		case AC_DOUBLE:		// �_�u���X�g���C�t�B���O
		case MA_DOUBLE:
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 90+10*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case HT_FREEZINGTRAP:		// �t���[�W���O�g���b�v
			calc_flag.nocardfix = 1;
			break;
		case HT_POWER:		// �r�[�X�g�X�g���C�t�B���O
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 100+16*s_str, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case AC_SHOWER:		// �A���[�V�����[
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
		case AC_CHARGEARROW:	// �`���[�W�A���[
		case MA_CHARGEARROW:
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 150, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case HT_PHANTASMIC:	// �t�@���^�Y�~�b�N�A���[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 150, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case KN_CHARGEATK:	// �`���[�W�A�^�b�N
			{
				int dist = unit_distance(src,target)-1;
				if(dist > 2)
					DMG_FIX( 100+100*(dist/3), 100 );
			}
			break;
		case AS_VENOMKNIFE:	// �x�i���i�C�t
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			calc_flag.nocardfix = 1;
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case SG_SUN_WARM:	// ���z�̉�����
		case SG_MOON_WARM:	// ���̉�����
		case SG_STAR_WARM:	// ���̉�����
			if(src_sd) {
				if(src_sd->status.sp < 2) {
					status_change_end(src,SC_WARM,-1);
					break;
				}
				// �������̂�SP����
				src_sd->status.sp -= 2;
				clif_updatestatus(src_sd,SP_SP);
			}
			wd.blewcount = 0;
			break;
		case KN_PIERCE:		// �s�A�[�X
		case ML_PIERCE:
			DMG_FIX( 100+10*skill_lv, 100 );
			break;
		case KN_SPEARSTAB:	// �X�s�A�X�^�u
#ifdef PRE_RENEWAL
			DMG_FIX( 100+15*skill_lv, 100 );
#else
			DMG_FIX( 100+20*skill_lv, 100 );
#endif
			wd.blewcount = 0;
			break;
		case KN_SPEARBOOMERANG:	// �X�s�A�u�[������
			DMG_FIX( 100+50*skill_lv, 100 );
			break;
		case KN_BRANDISHSPEAR:	// �u�����f�B�b�V���X�s�A
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
		case KN_BOWLINGBASH:	// �{�E�����O�o�b�V��
		case MS_BOWLINGBASH:
			DMG_FIX( 100+40*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case AS_SONICBLOW:	// �\�j�b�N�u���[
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
		case AS_GRIMTOOTH:	// �O�����g�D�[�X
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
		case TF_SPRINKLESAND:	// ���܂�
			DMG_FIX( 130, 100 );
			break;
		case MC_CARTREVOLUTION:	// �J�[�g���{�����[�V����
#ifdef PRE_RENEWAL
			if(src_sd && src_sd->cart_max_weight > 0 && src_sd->cart_weight > 0) {
				DMG_FIX( 150 + pc_checkskill(src_sd,BS_WEAPONRESEARCH) + src_sd->cart_weight*100/src_sd->cart_max_weight, 100 );
			} else {
				DMG_FIX( 150, 100 );
			}
#endif
			wd.blewcount = 0;
			break;
		case NPC_COMBOATTACK:	// ���i�U��
			DMG_FIX( 50, 100 );
			break;
		case NPC_RANDOMATTACK:	// �����_��ATK�U��
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
		case RG_BACKSTAP:	// �o�b�N�X�^�u
			{
				int rate = 300+40*skill_lv;
				if(src_sd && src_sd->status.weapon == WT_BOW) {	// �|�Ȃ甼��
					rate /= 2;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case RG_RAID:		// �T�v���C�Y�A�^�b�N
#ifdef PRE_RENEWAL
			DMG_FIX( 100+40*skill_lv, 100 );
#else
			DMG_FIX( 100+80*skill_lv, 100 );
#endif
			break;
		case RG_INTIMIDATE:	// �C���e�B�~�f�C�g
			DMG_FIX( 100+30*skill_lv, 100 );
			break;
		case CR_SHIELDCHARGE:	// �V�[���h�`���[�W
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
#ifdef PRE_RENEWAL
		case CR_SHIELDBOOMERANG:	// �V�[���h�u�[������
			if(src_sd && src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					wd.damage += src_sd->inventory_data[idx]->weight/10;
					wd.damage += src_sd->status.inventory[idx].refine * status_get_overrefine_bonus(0);
				}
			}
			break;
#endif
		case CR_HOLYCROSS:	// �z�[���[�N���X
		case NPC_DARKCROSS:	// �_�[�N�N���X
			DMG_FIX( 100+35*skill_lv, 100 );
			break;
		case CR_GRANDCROSS:	// �O�����h�N���X
		case NPC_GRANDDARKNESS:	// �O�����h�_�[�N�l�X
			if (!battle_config.gx_cardfix)
				calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case AM_DEMONSTRATION:	// �f�����X�g���[�V����
			DMG_FIX( 100+20*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
		case AM_ACIDTERROR:	// �A�V�b�h�e���[
			DMG_FIX( 100+40*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
#endif
		case MO_TRIPLEATTACK:	// �O�i��
			DMG_FIX( 100+20*skill_lv, 100 );
			break;
		case MO_FINGEROFFENSIVE:	// �w�e
#ifdef PRE_RENEWAL
			DMG_FIX( 100+50*skill_lv, 100 );
#else
			DMG_FIX( 125+25*skill_lv, 100 );
#endif
			break;
		case MO_INVESTIGATE:	// ����
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
		case MO_EXTREMITYFIST:	// ���C���e�P��
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
		case MO_CHAINCOMBO:	// �A�ŏ�
#ifdef PRE_RENEWAL
			DMG_FIX( 150+50*skill_lv, 100 );
#else
			DMG_FIX( 250+50*skill_lv, 100 );
#endif
			break;
		case MO_COMBOFINISH:	// �җ���
#ifdef PRE_RENEWAL
			DMG_FIX( 240+60*skill_lv, 100 );
#else
			DMG_FIX( 450+50*skill_lv, 100 );
#endif
			// PT�ɂ͓����Ă���
			// �J�E���^�[�A�^�b�N�̊m���㏸
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
		case TK_STORMKICK:	// �����R��
			DMG_FIX( 160+20*skill_lv, 100 );
			break;
		case TK_DOWNKICK:	// ���i�R��
			DMG_FIX( 160+20*skill_lv, 100 );
			break;
		case TK_TURNKICK:	// ��]�R��
			DMG_FIX( 190+30*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case TK_COUNTER:	// �J�E���^�[�R��
			DMG_FIX( 190+30*skill_lv, 100 );
			// PT�ɂ͓����Ă���
			// �O�i���̊m���㏸
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
		case BA_MUSICALSTRIKE:	// �~���[�W�J���X�g���C�N
		case DC_THROWARROW:	// ���
			DMG_FIX( 60+40*skill_lv, 100 );
			break;
		case CH_TIGERFIST:	// ���Ռ�
			DMG_FIX( 40+100*skill_lv, 100 );
			break;
		case CH_CHAINCRUSH:	// �A������
			DMG_FIX( 400+100*skill_lv, 100 );
			break;
		case CH_PALMSTRIKE:	// �ҌՍd�h�R
			DMG_FIX( 200+100*skill_lv, 100 );
			break;
#ifdef PRE_RENEWAL
		case LK_SPIRALPIERCE:	// �X�p�C�����s�A�[�X
		case ML_SPIRALPIERCE:
			DMG_FIX( 80+40*skill_lv, 100 );
			break;
#endif
		case LK_HEADCRUSH:	// �w�b�h�N���b�V��
			DMG_FIX( 100+40*skill_lv, 100 );
			break;
		case LK_JOINTBEAT:	// �W���C���g�r�[�g
			DMG_FIX( 50+10*skill_lv, 100 );
			break;
		case ASC_METEORASSAULT:	// ���e�I�A�T���g
			DMG_FIX( 40+40*skill_lv, 100 );
			calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case ASC_BREAKER:	// �\�E���u���C�J�[
			DMG_FIX( skill_lv, 1 );
			calc_flag.nocardfix = 1;
			break;
#endif
		case SN_SHARPSHOOTING:	// �V���[�v�V���[�e�B���O
		case MA_SHARPSHOOTING:
			DMG_FIX( 200+50*skill_lv, 100 );
			break;
		case CG_ARROWVULCAN:	// �A���[�o���J��
			DMG_FIX( 200+100*skill_lv, 100 );
			break;
		case AS_SPLASHER:	// �x�i���X�v���b�V���[
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
		case AS_POISONREACT:	// �|�C�Y�����A�N�g�i�U���Ŕ����j
			wd.damage = wd.damage*(100+30*skill_lv)/100;
			//wd.damage2 = wd.damage2	// ����ɂ͏��Ȃ�
			break;
		case TK_JUMPKICK:	// ��яR��
			if(sc && (sc->data[SC_RUN].timer != -1 || sc->data[SC_DODGE_DELAY].timer != -1)) {
				DMG_FIX( 30 + (10+status_get_lv(src)/10)*skill_lv, 100 );
				if(sc->data[SC_DODGE_DELAY].timer != -1)
					status_change_end(src,SC_DODGE_DELAY,-1);
			} else {
				DMG_FIX( 30+10*skill_lv, 100 );
			}
			if(src_sd && sc && sc->data[SC_RUN].timer != -1 && sc->data[SC_SPURT].timer != -1) {
				// �^�C���M���Ŋ��X�p�[�g��ԂȂ�З͂���ɃA�b�v
				// �v�Z���s���Ȃ̂œK��
				DMG_ADD( 10*pc_checkskill(src_sd,TK_RUN) );
			}
			// �e�B�I�A�v�`���M�ɂ��Ώۂ̃X�e�[�^�X�ُ����
			if(target_sd && target_sd->status.class_ == PC_CLASS_SL)	// �\�E�������J�[�͖���
				break;
			if(t_sc && t_sc->data[SC_PRESERVE].timer != -1)		// �v���U�[�u���͐؂�Ȃ�
				break;
			status_change_release(target,0x10);
			break;
#ifdef PRE_RENEWAL
		case PA_SHIELDCHAIN:	// �V�[���h�`�F�C��
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
		case WS_CARTTERMINATION:	// �J�[�g�^�[�~�l�[�V����
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
		case CR_ACIDDEMONSTRATION:	// �A�V�b�h�f�����X�g���[�V����
		case GN_FIRE_EXPANSION_ACID:	// �t�@�C�A�[�G�N�X�p���V����(���_)
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
		case GS_FLING:	// �t���C���O
			DMG_SET( status_get_jlv(src) );
			calc_flag.nocardfix = 1;
			break;
		case GS_TRIPLEACTION:	// �g���v���A�N�V����
			DMG_FIX( 150, 100 );
			break;
		case GS_BULLSEYE:	// �u���Y�A�C
			if(t_race == RCT_BRUTE || t_race == RCT_DEMIHUMAN || t_race == RCT_PLAYER_HUMAN || t_race == RCT_PLAYER_DORAM)
				DMG_FIX( 500, 100 );
			calc_flag.nocardfix = 1;
			break;
#ifdef PRE_RENEWAL
		case GS_MAGICALBULLET:	// �}�W�J���o���b�g
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
		case GS_TRACKING:	// �g���b�L���O
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 200+100*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DISARM:		// �f�B�X�A�[��
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_PIERCINGSHOT:	// �s�A�[�V���O�V���b�g
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
#ifdef PRE_RENEWAL
			DMG_FIX( 100+20*skill_lv, 100 );
#else
			if(src_sd && src_sd->status.weapon == WT_RIFLE) {
				DMG_FIX( 250+30*skill_lv, 100 );
			} else {
				DMG_FIX( 200+20*skill_lv, 100 );
			}
#endif
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_RAPIDSHOWER:	// ���s�b�h�V�����[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 500+50*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DESPERADO:	// �f�X�y���[�h
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 50+50*skill_lv, 100 );
			if(wflag&1)	// �t�H�[�����G���W�F��
				DMG_FIX( 200, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_DUST:		// �_�X�g
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 100+50*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_FULLBUSTER:	// �t���o�X�^�[
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
			DMG_FIX( 300+100*skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case GS_SPREADATTACK:	// �X�v���b�h�A�^�b�N
			if(src_sd && !src_sd->state.arrow_atk && src_sd->arrow_atk > 0) {
				int arr = atn_rand()%(src_sd->arrow_atk+1);
				DMG_ADD( arr );
			}
#ifdef PRE_RENEWAL
			DMG_FIX( 80+20*skill_lv, 100 );
#else
			DMG_FIX( 200+30*skill_lv, 100 );
#endif
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
	case GS_GROUNDDRIFT:		// �O���E���h�h���t�g
			DMG_FIX( 200+20*skill_lv, 100 );
			break;
#ifdef PRE_RENEWAL
		case NJ_SYURIKEN:	// �藠������
		case NJ_KUNAI:		// �ꖳ����
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
#else
		case NJ_SYURIKEN:	// �藠������
			if(src_sd) {
				skill = pc_checkskill(src_sd,NJ_TOBIDOUGU);
				DMG_ADD( skill * 3 );
				if(src_sd->arrow_atk) {
					DMG_ADD( src_sd->arrow_atk );
				}
			}
			DMG_FIX( 100 + skill_lv * 5, 100 );
			break;
		case NJ_KUNAI:		// �ꖳ����
			if(src_sd) {
				skill = pc_checkskill(src_sd,NJ_TOBIDOUGU);
				DMG_ADD( skill * 3 );
			}
			DMG_FIX( 100 * skill_lv, 100 );
			break;
#endif
		case NJ_HUUMA:		// �����藠������
			{
#ifdef PRE_RENEWAL
				int rate = 150+150*skill_lv;
				if(wflag > 1)
					rate /= wflag;
#else
				int rate = 250*skill_lv-50;
				if(src_sd) {
					skill = pc_checkskill(src_sd,NJ_TOBIDOUGU);
					DMG_ADD( skill * 3 );
				}
#endif
				DMG_FIX( rate, 100 );
			}
			break;
		case NJ_ZENYNAGE:	// �K����
			{
				int dmg = 0;
				if(src_sd) {
					dmg = src_sd->zenynage_damage;
					src_sd->zenynage_damage = 0;	// �������烊�Z�b�g
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
		case NJ_TATAMIGAESHI:	// ���Ԃ�
#ifdef PRE_RENEWAL
			DMG_FIX( 100+10*skill_lv, 100 );
#else
			DMG_FIX( 200+20*skill_lv, 100 );
			wd.damage = wd.damage - (t_def1 + t_def2);
#endif
			break;
		case NJ_KASUMIKIRI:	// ���a��
#ifdef PRE_RENEWAL
			DMG_FIX( 100+10*skill_lv, 100 );
#else
			DMG_FIX( 100+20*skill_lv, 100 );
#endif
			break;
		case NJ_KIRIKAGE:	// �e�a��
#ifdef PRE_RENEWAL
			DMG_FIX( skill_lv, 1 );
#else
			DMG_FIX( 50+150*skill_lv, 100 );
#endif
			break;
#ifdef PRE_RENEWAL
		case NJ_ISSEN:		// ��M
			{
				int hp = status_get_hp(src);
				DMG_SET( (s_str*40)+(skill_lv*(hp-1)*8)/100 );
				unit_heal(src,-hp+1,0,0,0);
				if(sc && sc->data[SC_NEN].timer != -1)
					status_change_end(src,SC_NEN,-1);
			}
			break;
#endif
		case NPC_CRITICALSLASH:		// �N���e�B�J���X���b�V��
			DMG_FIX( 100, 100 );
			break;
		case NPC_FIREBREATH:		// �t�@�C�A�u���X
		case NPC_ICEBREATH:		// �A�C�X�u���X
		case NPC_THUNDERBREATH:		// �T���_�[�u���X
		case NPC_ACIDBREATH:		// �A�V�b�h�u���X
		case NPC_DARKNESSBREATH:	// �_�[�N�l�X�u���X
		case NPC_HELLJUDGEMENT:		// �w���W���b�W�����g
		case NPC_DANCINGBLADE_ATK:	// �_���V���O�u���C�h(�A��)
		case NPC_DARKPIERCING:		// �_�[�N�s�A�[�V���O
			DMG_FIX( 100*skill_lv, 100 );
			break;
		case NPC_PULSESTRIKE:		// �p���X�X�g���C�N
			DMG_FIX( 100*skill_lv, 100 );
			wd.blewcount = 0;
			break;
		case NPC_VAMPIRE_GIFT:		// ���@���p�C�A���b�N�^�b�`
			DMG_FIX( 100 * ((skill_lv - 1) % 5 + 1), 100 );
			break;
		case NPC_VENOMFOG:			// �x�i���t�H�O
			if(src_md)
				wd.damage = mobdb_search(src_md->class_)->atk1;
			else
				wd.damage = status_get_atk(src);
			DMG_FIX( 100 * skill_lv, 100 );
			wd.damage = battle_attr_fix(wd.damage, s_ele, status_get_element(target));
			break;
		case NPC_REVERBERATION_ATK:	// M�U���c��(�U��)
			DMG_FIX( 400 + 200 * skill_lv, 100 );
			if(wflag > 1) {
				DMG_FIX( 1, wflag );
			}
			break;
		case NPC_IGNITIONBREAK:	// M�C�O�j�b�V�����u���C�N
			{
				int dmg = 500 + 500 * skill_lv;
				int dist = unit_distance(src,target);
				if(dist > 3)			// ������
					dmg -= 500;
				else if(dist > 1)		// ������
					dmg -= 250;
				DMG_FIX( dmg, 100 );
			}
			break;
		case NPC_ARROWSTORM:		// M�A���[�X�g�[��
			DMG_FIX( 1000 + 1000 * (skill_lv >= 5), 100 );
			break;
		case NPC_DRAGONBREATH:	/* M�h���S���u���X */
			if(skill_lv < 6) {
				DMG_FIX( 500 + 500 * skill_lv, 100 );
			}
			else {
				DMG_FIX( 500 + 500 * (skill_lv-5), 100 );
			}
			break;
		case NPC_PHANTOMTHRUST:	// M�t�@���g���X���X�g
			DMG_FIX( 100, 100 );
			break;
		case NPC_HELLJUDGEMENT2:		// �f���j�b�N�w���W���b�W�����g
			DMG_FIX( 1000*skill_lv, 100 );
			break;
		case HFLI_MOON:		// ���[�����C�g
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
		case MH_NEEDLE_OF_PARALYZE:	// �j�[�h���I�u�p�����C�Y
			DMG_FIX( 700+100*skill_lv, 100 );
			break;
		case MH_SONIC_CRAW:	// �\�j�b�N�N���[
			DMG_FIX( 40*skill_lv * status_get_lv(src) / 150, 100 );
			break;
		case MH_SILVERVEIN_RUSH:	// �V���o�[�x�C�����b�V��
			DMG_FIX( 150 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case MH_MIDNIGHT_FRENZY:	// �~�b�h�i�C�g�t�����W
			DMG_FIX( 300 * skill_lv * status_get_lv(src) / 150, 100 );
			break;
		case MH_STAHL_HORN:	// �V���^�[���z�[��
			DMG_FIX( 500 + 100 * skill_lv * status_get_lv(src) / 150, 100 );
			break;
		case MH_TINDER_BREAKER:	// �e�B���_�[�u���C�J�[
			DMG_FIX( 100 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case MH_EQC:			// E.Q.C
			if(t_sc && t_sc->data[SC_EQC].timer != -1 && t_sc->data[SC_EQC].val2 > 0) {
				if(t_sc->data[SC_EQC].val2 < status_get_max_hp(src)) {
					DMG_SET( status_get_max_hp(src) );
				}
				else {
					DMG_SET( t_sc->data[SC_EQC].val2 - status_get_max_hp(src) );
				}
				t_sc->data[SC_EQC].val2 = 0;
			}
			break;
		case MH_LAVA_SLIDE:	// ���[���@�X���C�h
			DMG_FIX( (20 * skill_lv + 3 * status_get_lv(src)) * status_get_lv(src) / 120, 100 );
			break;
		case MH_MAGMA_FLOW:	// �}�O�}�t���[
			DMG_FIX( (100 * skill_lv + 3 * status_get_lv(src)) * status_get_lv(src) / 120, 100 );
			break;
		case MER_CRASH:		// �N���b�V��
			DMG_FIX( 100+10*skill_lv, 100 );
			break;
		case RK_SONICWAVE:	// �\�j�b�N�E�F�[�u
			DMG_FIX( (700 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RK_HUNDREDSPEAR:	// �n���h���b�h�X�s�A
			{
				int dmg = 600 + 80 * skill_lv;
				if(sc && sc->data[SC_DRAGONIC_AURA].timer != -1)
					dmg = 700 + 200 * skill_lv;
				if(src_sd) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid))
						dmg += 1000 - src_sd->inventory_data[idx]->weight/10;
				}
				DMG_FIX( (dmg * (status_get_lv(src)/2+50) / 100) + (((src_sd)? pc_checkskill(src_sd,LK_SPIRALPIERCE): 0) * 50), 100 );
			}
			break;
		case RK_WINDCUTTER:	// �E�B���h�J�b�^�[
			DMG_FIX( (100 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RK_IGNITIONBREAK:	// �C�O�j�b�V�����u���C�N
			{
				int dmg = 300 * skill_lv;
				int dist = unit_distance(src,target);
				if(dist > 3)			// ������
					dmg = 200 * skill_lv;
				else if(dist > 1)		// ������
					dmg = 250 * skill_lv;
				dmg = dmg * status_get_lv(src) / 100;
				if(s_ele == ELE_FIRE)	// �Α������푕����
					dmg += 100 * skill_lv;
				DMG_FIX( dmg, 100 );
			}
			break;
		case RK_DRAGONBREATH:	// �t�@�C�A�[�h���S���u���X
		case RK_DRAGONBREATH_WATER:	// �E�H�[�^�[�h���S���u���X
			{
				atn_bignumber dmg = (status_get_hp(src) / 50 + status_get_max_sp(src) / 4) * skill_lv;
				int aura = 0;
				if(src_sd) {
					dmg = dmg * ( 95 + pc_checkskill(src_sd,RK_DRAGONTRAINING) * 5 ) / 100;
					aura = pc_checkskill(src_sd,DK_DRAGONIC_AURA);
				}
				dmg *= status_get_lv(src) / 100;
				if(aura > 0)
				dmg *= (atn_bignumber)(1 + (pow((double)(status_get_pow(src) + status_get_patk(src)), 1.05555) / 100 * 250 / 300));
				DMG_SET( battle_attr_fix(dmg, s_ele, status_get_element(target)) );
			}
			break;
		case RK_STORMBLAST:		// �X�g�[���u���X�g
			DMG_FIX( ((src_sd)? pc_checkskill(src_sd,RK_RUNEMASTERY): 1) * 100 + (status_get_int(src) / 8) * 100, 100 );
			break;
		case RK_PHANTOMTHRUST:	// �t�@���g���X���X�g
			DMG_FIX( (50 * skill_lv + ((src_sd)? pc_checkskill(src_sd,KN_SPEARMASTERY): 0) * 10) * status_get_lv(src) / 150, 100 );
			break;
		case GC_CROSSIMPACT:	// �N���X�C���p�N�g
			if(sc && sc->data[SC_EDP].timer != -1) {
				DMG_FIX( (1000 + 100 * skill_lv) * status_get_lv(src) / 120 / 2, 100 );
			} else {
				DMG_FIX( (1000 + 100 * skill_lv) * status_get_lv(src) / 120, 100 );
			}
			break;
		case GC_DARKILLUSION:	// �_�[�N�C�����[�W����
			DMG_FIX( 100, 100 );
			break;
		case GC_COUNTERSLASH:	// �J�E���^�[�X���b�V��
			if(src_sd) {
				int rate = (300 + 150 * skill_lv) * status_get_lv(src) / 120 + status_get_agi(src) * 2 + status_get_jlv(src) * 4;
				if(sc && sc->data[SC_EDP].timer != -1)
					rate >>= 1;
				DMG_FIX( rate, 100 );
			} else {
				DMG_FIX( (300 + 150 * skill_lv) * status_get_lv(src) / 120 + status_get_agi(src) * 2, 100 );
			}
			break;
		case GC_VENOMPRESSURE:	// �x�i���v���b�V���[
			DMG_FIX( 1000, 100 );
			break;
		case GC_PHANTOMMENACE:	// �t�@���g�����i�X
			DMG_FIX( 300, 100 );
			break;
		case GC_ROLLINGCUTTER:	// ���[�����O�J�b�^�[
			if(sc && sc->data[SC_EDP].timer != -1) {
				DMG_FIX( (50 + 50 * skill_lv) * status_get_lv(src) / 100 / 2, 100 );
			} else {
				DMG_FIX( (50 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case GC_CROSSRIPPERSLASHER:	// �N���X���b�p�[�X���b�V���[
			{
				int dmg = (400 + 80 * skill_lv) * status_get_lv(src) / 100;
				if(sc && sc->data[SC_ROLLINGCUTTER].timer != -1) {
					dmg += sc->data[SC_ROLLINGCUTTER].val1 * status_get_agi(src);
				}
				if(sc && sc->data[SC_EDP].timer != -1) {
					dmg >>= 1;
				}
				DMG_FIX( dmg, 100 );
			}
			break;
		case GC_DARKCROW:	// �_�[�N�N���[
			DMG_FIX( 100 * skill_lv, 100 );
			break;
		case AB_DUPLELIGHT_MELEE:	// �O���C�A�����C�g
			DMG_FIX( 100 + 10 * skill_lv, 100 );
			break;
		case RA_CLUSTERBOMB:	// �N���X�^�[�{��
			DMG_FIX( 200 + 100 * skill_lv, 100 );
			break;
		case RA_FIRINGTRAP:		// �t�@�C�A�����O�g���b�v
		case RA_ICEBOUNDTRAP:	// �A�C�X�o�E���h�g���b�v
			DMG_FIX( 100, 100 );
			break;
		case RA_ARROWSTORM:		// �A���[�X�g�[��
			DMG_FIX( (1000 + 80 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RA_AIMEDBOLT:		// �G�C���h�{���g
			wd.div_ = wflag;	// �����莞��Hit�����g�p
			DMG_FIX( ((500 + 50 * skill_lv) * status_get_lv(src) / 100) * wd.div_, 100 );
			break;
		case RA_WUGDASH:		// �E�H�[�O�_�b�V��
			DMG_FIX( 300, 100 );
			break;
		case RA_WUGSTRIKE:		// �E�H�[�O�X�g���C�N
			DMG_FIX( 250 * skill_lv, 100 );
			break;
		case RA_WUGBITE:		// �E�H�[�O�o�C�g
			DMG_FIX( 800 + 200 * skill_lv, 100 );
			break;
		case RA_SENSITIVEKEEN:	// �s�q�Țk�o
			DMG_FIX( 100 + 50 * skill_lv, 100 );
			break;
		case NC_BOOSTKNUCKLE:	// �u�[�X�g�i�b�N��
			DMG_FIX( (200 + 100 * skill_lv + status_get_dex(src)) * status_get_lv(src) / 120, 100 );
			if(sc && sc->data[SC_ABR_DUAL_CANNON].timer != -1) {
				wd.div_ = 2;
			}
			break;
		case NC_PILEBUNKER:	// �p�C���o���J�[
			DMG_FIX( (300 + 100 * skill_lv + status_get_str(src)) * status_get_lv(src) / 100, 100 );
			break;
		case NC_VULCANARM:	// �o���J���A�[��
			DMG_FIX( (70 * skill_lv + status_get_dex(src)) * status_get_lv(src) / 120, 100 );
			if(sc && sc->data[SC_ABR_DUAL_CANNON].timer != -1) {
				wd.div_ = 2;
			}
			break;
		case NC_FLAMELAUNCHER:	// �t���C���X���[���[
		case NC_COLDSLOWER:		// �R�[���h�X���[���[
			DMG_FIX( (300 + 300 * skill_lv) * status_get_lv(src) / 150, 100 );
			break;
		case NC_SELFDESTRUCTION:	// �Z���t�f�B�X�g���N�V����
			{
				int mf_lv = src_sd ? pc_checkskill(src_sd,NC_MAINFRAME) : 2;
				DMG_SET( (skill_lv + 1) * (mf_lv + 8) * (status_get_sp(src) + status_get_vit(src)) * status_get_lv(src) / 100 + status_get_hp(src) );
			}
			break;
		case NC_AXEBOOMERANG:	// �A�b�N�X�u�[������
			if(src_sd) {
				int dmg = 250 + 50 * skill_lv;
				int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid))
					dmg += src_sd->inventory_data[idx]->weight/10;
				DMG_FIX( dmg * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (250 + 50 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case NC_POWERSWING:	// �p���[�X�C���O
			if(sc && sc->data[SC_ABR_BATTLE_WARIOR].timer != -1) {
				DMG_FIX( 500 + 150 * skill_lv + (status_get_str(src) + status_get_dex(src)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( 300 + 100 * skill_lv + (status_get_str(src) + status_get_dex(src)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case NC_AXETORNADO:	// �A�b�N�X�g���l�[�h
			if(sc && sc->data[SC_AXE_STOMP].timer != -1) {
				DMG_FIX( (230 + 230 * skill_lv + status_get_vit(src)*2) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (200 + 180 * skill_lv + status_get_vit(src)) * status_get_lv(src) / 100, 100 );
			}
			break;
#ifdef PRE_RENEWAL
		case NC_ARMSCANNON:	// �A�[���Y�L���m��
			if(src_sd && src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
			DMG_FIX( (300 + (400 - 50 * t_size) * skill_lv) * status_get_lv(src) / 120, 100 );
			if(sc && sc->data[SC_ABR_DUAL_CANNON].timer != -1) {
				wd.div_ = 2;
			}
			break;
#endif
		case NC_MAGMA_ERUPTION:	/* �}�O�}�C���v�V���� */
			DMG_FIX( 450 + 50 * skill_lv, 100 );
			break;
		case SC_FATALMENACE:	// �t�F�C�^�����i�X
			if(sc && sc->data[SC_ABYSS_DAGGER].timer != -1) {
				DMG_FIX( (120 + 120 * skill_lv) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (100 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			if(src_sd && src_sd->status.weapon == WT_DAGGER)
				wd.div_ = 2;
			break;
		case SC_TRIANGLESHOT:	// �g���C�A���O���V���b�g
			DMG_FIX( ((skill_lv - 1) * status_get_agi(src) / 2 + 300) * status_get_lv(src) / 120, 100 );
			break;
		case SC_FEINTBOMB:	// �t�F�C���g�{��
			DMG_FIX( (1 + ((skill_lv == 1)? 2: 3) + (skill_lv - 1) / 3) * status_get_dex(src) / 2 * status_get_jlv(src) / 10 * status_get_lv(src) / 120, 100 );
			wd.blewcount = 0;
			break;
		case LG_CANNONSPEAR:	// �L���m���X�s�A
			if(sc && sc->data[SC_SPEAR_SCAR].timer != -1) {
				DMG_FIX( (200 + status_get_str(src)) * skill_lv * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (50 + status_get_str(src)) * skill_lv * status_get_lv(src) / 100, 100 );
			}
			break;
		case LG_BANISHINGPOINT:	// �o�j�V���O�|�C���g
			if(sc && sc->data[SC_SPEAR_SCAR].timer != -1) {
				DMG_FIX( (100 * skill_lv + ((src_sd)? pc_checkskill(src_sd,SM_BASH): 0) * 60) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (50 * skill_lv + ((src_sd)? pc_checkskill(src_sd,SM_BASH): 0) * 30) * status_get_lv(src) / 100, 100 );
			}
			break;
		case LG_SHIELDPRESS:	// �V�[���h�v���X
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					if(src_sd->sc.data[SC_SHIELD_POWER].timer != -1) {
						DMG_FIX( (300 * skill_lv + status_get_str(src) + src_sd->inventory_data[idx]->weight/10) * status_get_lv(src) / 100, 100);
					} else {
						DMG_FIX( (200 * skill_lv + status_get_str(src) + src_sd->inventory_data[idx]->weight/10) * status_get_lv(src) / 100, 100);
					}
				}
			} else {
				DMG_FIX( (200 * skill_lv + status_get_str(src)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case LG_PINPOINTATTACK:	// �s���|�C���g�A�^�b�N
			DMG_FIX( (100 * skill_lv + status_get_agi(src) * 5) * status_get_lv(src) / 120, 100 );
			break;
		case LG_RAGEBURST:	// ���C�W�o�[�X�g�A�^�b�N
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
		case LG_SHIELDSPELL:	// �V�[���h�X�y��
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
		case LG_OVERBRAND:	// �I�[�o�[�u�����h
			DMG_FIX( (400 * skill_lv + ((src_sd)? pc_checkskill(src_sd,CR_SPEARQUICKEN): 0) * 50) * status_get_lv(src) / 150, 100 );
			break;
		case LG_OVERBRAND_BRANDISH:		// �I�[�o�[�u�����h(�ガ)
			DMG_FIX( (300 * skill_lv + status_get_str(src) + status_get_dex(src)) * status_get_lv(src) / 150, 100 );
			break;
		case LG_OVERBRAND_PLUSATK:		// �I�[�o�[�u�����h(�ǌ�)
			DMG_FIX( 200 * skill_lv, 100 );
			break;
		case LG_MOONSLASHER:	// ���[���X���b�V���[
			DMG_FIX( (120 * skill_lv + ((src_sd)? pc_checkskill(src_sd,LG_OVERBRAND): 0) * 80) * status_get_lv(src) / 100, 100 );
			break;
		case LG_HESPERUSLIT:	// �w�X�y���X���b�g
			{
				int rate;
				rate = (120 * skill_lv + 200 * wd.div_) * status_get_lv(src) / 100;
				if(wd.div_ == 6) {
					rate = rate * 150 / 100;
				}
				DMG_FIX( rate, 100 );
				break;
			}
		case LG_EARTHDRIVE:	// �A�[�X�h���C�u
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid))
					if(src_sd->sc.data[SC_SHIELD_POWER].timer != -1) {
						DMG_FIX( ((300 + 100 * skill_lv) * src_sd->inventory_data[idx]->weight / 1000) * status_get_lv(src) / 100, 100 );
					} else {
						DMG_FIX( ((100 + 100 * skill_lv) * src_sd->inventory_data[idx]->weight / 1000) * status_get_lv(src) / 100, 100 );
					}
			} else {
				DMG_FIX( (100 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SR_DRAGONCOMBO:	// �o���r
			DMG_FIX( ( 100 + 40 * skill_lv ) * status_get_lv(src) / 100, 100 );
			break;
		case SR_SKYNETBLOW:	// �V���n��
			if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_DRAGONCOMBO) {
				DMG_FIX( (100 * skill_lv + status_get_agi(src) + 150) * status_get_lv(src) / 100, 100 );		// �R���{������
			} else {
				DMG_FIX( (80 * skill_lv + status_get_agi(src)) * status_get_lv(src) / 100, 100 );		// �ʏ펞
			}
			break;
		case SR_EARTHSHAKER:	// �n���k
			if(!wflag) {	// �ʏ�
				DMG_FIX( (50 * skill_lv * status_get_lv(src) / 100) + status_get_int(src) * 2, 100 );
			} else {	// �n�C�h����
				DMG_FIX( (150 * skill_lv * status_get_lv(src) / 100) + status_get_int(src) * 3, 100 );
			}
			break;
		case SR_FALLENEMPIRE:	// ��Z����
			DMG_FIX( (100 + 250 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case SR_TIGERCANNON:	// �j�C
			if(src_sd) {
				int hp = 0, sp = 0;
				if(!wflag) {
					hp = (int)((atn_bignumber)status_get_max_hp(src) * (10 + skill_lv * 2) / 100);
					sp = (int)((atn_bignumber)status_get_max_sp(src) * (5 + skill_lv) / 100);
				}
				if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
					DMG_FIX( (hp + sp) / 2 * status_get_lv(src) / 100 , 100 );		// �R���{������
				} else {
					DMG_FIX( (hp + sp) / 4 * status_get_lv(src) / 100 , 100 );			// �ʏ펞
				}
			}
			break;
		case SR_RAMPAGEBLASTER:	// ���C�U�e
			if(src_sd && src_sd->spiritball.old) {
				if(sc && sc->data[SC_EXPLOSIONSPIRITS].timer != -1) {
					DMG_FIX( (75 + 25 * skill_lv) * status_get_lv(src) / 150 * src_sd->spiritball.old, 100 );
				} else {
					DMG_FIX( 20 * skill_lv * status_get_lv(src) / 150 * src_sd->spiritball.old, 100 );
				}
			} else if(sc && sc->data[SC_EXPLOSIONSPIRITS].timer != -1) {
				DMG_FIX( (75 + 25 * skill_lv) * status_get_lv(src) / 150, 100 );
			} else {
				DMG_FIX( 20 * skill_lv * status_get_lv(src) / 150, 100 );
			}
			break;
		case SR_CRESCENTELBOW:	// �j�Ӓ�(�Փ�)
			DMG_FIX( 200 * skill_lv, 100 );
			break;
		case SR_CRESCENTELBOW_AUTOSPELL:	// �j�Ӓ�(����)
			{
				int hp = status_get_hp(target);
				if(hp > 100000)
					hp = 100000;
				DMG_FIX( skill_lv * hp / 100 * status_get_lv(src) / 125, 100 );
			}
			break;
		case SR_KNUCKLEARROW:	// �C���g�e
			if(!wflag) {
				DMG_FIX( (500 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			} else if(target_sd) {		// �Փ˃_���[�W
				DMG_FIX( (150 * skill_lv) + (status_get_lv(target) / 3 * 10) * status_get_lv(src) / 100 + (target_sd->weight / target_sd->max_weight * 10), 100 );
			} else {
				DMG_FIX( (150 * skill_lv) + (status_get_lv(target) / 3 * 10) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SR_WINDMILL:	// ������
			DMG_FIX( (status_get_lv(src) + status_get_dex(src)) * status_get_lv(src) / 100, 100 );
			break;
		case SR_GATEOFHELL:	// �����j����
			if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
				DMG_FIX( 800 * skill_lv * status_get_lv(src) / 100, 100 );		// �R���{������
			} else {
				DMG_FIX( 500 * skill_lv * status_get_lv(src) / 100, 100 );		// �ʏ펞
			}
			break;
		case SR_GENTLETOUCH_QUIET:	// �_�� -��-
			DMG_FIX( ( 100 * skill_lv + status_get_dex(src) ) * status_get_lv(src) / 100, 100 );
			break;
		case SR_HOWLINGOFLION:	// ���q��
			DMG_FIX( 200 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case SR_RIDEINLIGHTNING:	// �����e
			DMG_FIX( ( 200 * skill_lv + ((s_ele == ELE_WIND)? 50 * skill_lv: 0) ) * status_get_lv(src) / 100, 100 );
			break;
		case WM_REVERBERATION_MELEE:	// �U���c��(����)
			DMG_FIX( (300 + 100 * skill_lv) * status_get_lv(src) / 100, 100 );
			if(wflag > 1) {
				DMG_FIX( 1, wflag );
			}
			break;
		case WM_SEVERE_RAINSTORM:		// �V�r�A���C���X�g�[��
		case WM_SEVERE_RAINSTORM_MELEE:	// �V�r�A���C���X�g�[��(�U��)
			if(src_sd && (src_sd->status.weapon == WT_MUSICAL || src_sd->status.weapon == WT_WHIP)) {
				DMG_FIX( (status_get_agi(src) + status_get_dex(src)) * skill_lv / 5 * status_get_lv(src) / 60, 100 );
			} else {
				DMG_FIX( (status_get_agi(src) + status_get_dex(src)) * skill_lv / 5 * status_get_lv(src) / 100, 100 );
			}
			break;
		case WM_GREAT_ECHO:		// �O���[�g�G�R�[
			{
				int rate = 400 + 200 * skill_lv;
				if(wflag >= 3 && wflag <= 7) {
					rate += 100<<(wflag-3);
				}
				DMG_FIX( rate * status_get_lv(src) / 100, 100 );
			}
			break;
		case WM_SOUND_OF_DESTRUCTION:	// �T�E���h�I�u�f�B�X�g���N�V����
			DMG_FIX( 250, 100 );
			break;
		case GN_CART_TORNADO:	// �J�[�g�g���l�[�h
			DMG_FIX( 100 * skill_lv + ((src_sd)? pc_checkskill(src_sd,GN_REMODELING_CART): 1) * 50 + ((src_sd)? src_sd->cart_weight/10 / (150-src_sd->status.str): 1), 100 );
			break;
		case GN_CARTCANNON:		// �J�[�g�L���m��
			if(src_sd && src_sd->arrow_atk) {
				DMG_ADD( src_sd->arrow_atk );
			}
			DMG_FIX( 60 * skill_lv + (((src_sd)? pc_checkskill(src_sd,GN_REMODELING_CART): 1) * 50 * status_get_int(src) / 40), 100 );
			break;
		case GN_WALLOFTHORN:	// �\�[���E�H�[��
			DMG_FIX( 150 + 50 * skill_lv, 100 );
			break;
		case GN_CRAZYWEED_ATK:	// �N���C�W�[�E�B�[�h
			DMG_FIX( 500 + 100 * skill_lv, 100 );
			break;
		case GN_SPORE_EXPLOSION: // �X�|�A�G�N�X�v���[�W����
			DMG_FIX( ( 200 + 150 * skill_lv + status_get_int(src)) * status_get_lv(src) / 100, 100 );
			break;
		case GN_SLINGITEM_RANGEMELEEATK:	// �X�����O�A�C�e��(�������U��)
			switch(skill_lv) {
			case 0:	/* �����S���e */
				DMG_FIX( 400, 100 );
				break;
			case 1:	/* �R�R�i�b�c���e */
				DMG_FIX( 1000, 100 );
				break;
			case 2:	/* ���������e */
				DMG_FIX( 400, 100 );
				break;
			case 3:	/* �p�C�i�b�v�����e */
				DMG_FIX( 1000, 100 );
				break;
			case 4:	/* �o�i�i���e */
				DMG_FIX( 800, 100 );
				break;
			case 5:	/* ������ */
				DMG_FIX( 200, 100 );
				break;
			case 6:	/* �d���č����� */
				DMG_FIX( 300, 100 );
				break;
			case 7:	/* �ƂĂ��d���� */
				DMG_FIX( 400, 100 );
				break;
			}
			break;
		case KO_JYUMONJIKIRI:	// �\�����a��
			if(t_sc && t_sc->data[SC_KO_JYUMONJIKIRI].timer != -1) {
				DMG_FIX( 300 * skill_lv * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( 200 * skill_lv * status_get_lv(src) / 100, 100 );
			}
			break;
		case KO_SETSUDAN:		// ����Ԃ�
			{
				int rate = 100 * skill_lv;

				if(t_sc) {
					int soul;

					for(soul = SC_ALCHEMIST; soul <= SC_GUNNER; soul++) {
						if(t_sc->data[soul].timer != -1) {
							rate += 200 * t_sc->data[soul].val1;
							break;
						}
					}
					for(soul = SC_SOULSHADOW; soul <= SC_SOULGOLEM; soul++) {
						if(t_sc->data[soul].timer != -1) {
							rate += 200 * t_sc->data[soul].val1;
							status_change_end(target,soul,-1);
							break;
						}
					}
				}

				DMG_FIX( rate * status_get_lv(src) / 100, 100 );
				status_change_soulclear(target);
			}
			break;
		case KO_BAKURETSU:		// ����ꖳ
			DMG_FIX( ((skill_lv * (50 + status_get_dex(src) / 4)) * ((src_sd)? pc_checkskill(src_sd,NJ_TOBIDOUGU): 1) * 4 / 10 * status_get_lv(src) / 100) + status_get_jlv(src) * 10, 100);
			break;
		case KO_HAPPOKUNAI:		// �����ꖳ
			DMG_FIX( 300 + 60 * skill_lv, 100 );
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case KO_MUCHANAGE:	// ��������
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
		case KO_HUUMARANKA:	// �����藠�� -����-
			DMG_FIX( (150 * skill_lv + status_get_str(src) + ((src_sd)? pc_checkskill(src_sd, NJ_HUUMA): 0) * 100) * status_get_lv(src) / 100, 100 );
			break;
		case RL_MASS_SPIRAL:		// �}�X�X�p�C����
			{
				int rate = status_get_def(target);
				rate = (200 + (rate > 500? 500: rate)) * skill_lv;
				DMG_FIX( rate, 100 );
				if(src_sd)
					src_sd->state.arrow_atk = 1;
			}
			break;
		case RL_BANISHING_BUSTER:	// �o�j�V���O�o�X�^�[
			DMG_FIX( 200 * skill_lv * status_get_lv(src) / 100, 100 );
			break;
		case RL_S_STORM:		// �V���b�^�[�X�g�[��
			DMG_FIX( 1700 + 200 * skill_lv, 100 );
			break;
		case RL_QD_SHOT:		// �N�C�b�N�h���[�V���b�g
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			wd.div_ = wflag&0xf;
			break;
		case RL_FIREDANCE:		// �t�@�C�A�[�_���X
			DMG_FIX( (1000 + 100 * skill_lv + ((src_sd)? pc_checkskill(src_sd,GS_DESPERADO): 0) * 20) * status_get_lv(src) / 100, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case RL_H_MINE:			// �n�E�����O�}�C��
			if(wflag&1) {		// �n�E�����O�}�C��(�ǌ�)
				DMG_FIX( 1000 + 400 * skill_lv, 100 );
			} else {
				DMG_FIX( 400 * skill_lv, 100 );
			}
			break;
		case RL_R_TRIP:			// ���E���h�g���b�v
		case RL_R_TRIP_PLUSATK:	// ���E���h�g���b�v(�ǌ�)
			DMG_FIX( (100 + 40 * skill_lv) * status_get_lv(src) / 100, 100 );
			break;
		case RL_D_TAIL:			// �h���S���e�C��
			if(t_sc && t_sc->data[SC_C_MARKER].timer != -1) {
				DMG_FIX( (1000 + 400 * skill_lv) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (500 + 200 * skill_lv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case RL_FIRE_RAIN:		// �t�@�C�A�[���C��
			DMG_FIX( 500 + 500 * skill_lv, 100 );
			break;
		case RL_AM_BLAST:		// �A���`�}�e���A���u���X�g
			DMG_FIX( 1500 + 300 * skill_lv, 100 );
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case RL_SLUGSHOT:		// �X���b�O�V���b�g
			{
				int rate = 1200 * skill_lv * (t_size+2);
				if(target->type == BL_PC)
					rate /= 2;
				DMG_FIX( rate, 100 );
				if(src_sd)
					src_sd->state.arrow_atk = 1;
			}
			break;
		case RL_HAMMER_OF_GOD:	// �n���}�[�I�u�S�b�h
			if(t_sc && t_sc->data[SC_C_MARKER].timer != -1) {
				DMG_FIX( (500 + 100 * skill_lv + ((src_sd)? src_sd->coin.num: 0) * 200) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (500 + 100 * skill_lv + ((src_sd)? src_sd->coin.num: 0) * 50) * status_get_lv(src) / 100, 100 );
			}
			if(src_sd)
				src_sd->state.arrow_atk = 1;
			break;
		case SJ_FULLMOONKICK:	// �����r
			{
				int rate = ( 500 + 150 * skill_lv ) * status_get_lv(src) / 100;
				if(sc && sc->data[SC_LIGHTOFMOON].timer != -1 ) {
					rate += ( rate * sc->data[SC_LIGHTOFMOON].val2 ) / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case SJ_NEWMOONKICK:	// �񌎋r
			DMG_FIX( 1650 + 50 * skill_lv, 100 );
			break;
		case SJ_FLASHKICK:		// �M���r
			DMG_FIX( 100, 100 );
			break;
		case SJ_PROMINENCEKICK:	// �g���r
			DMG_FIX( 650 + 50 * skill_lv, 100 );
			break;
		case SJ_SOLARBURST:	// ���z����
			{
				int rate = ( 1000 + 220 * skill_lv ) * status_get_lv(src) / 100;
				if(sc && sc->data[SC_LIGHTOFSUN].timer != -1 ) {
					rate += ( rate * sc->data[SC_LIGHTOFSUN].val2 ) / 100;
				}
				DMG_FIX( rate, 100 );
			}
			break;
		case SJ_FALLINGSTAR_ATK:	// ��������
		case SJ_FALLINGSTAR_ATK2:
			{
				int rate = ( 100 + 100 * skill_lv ) * status_get_lv(src) / 100;
				if (sc && sc->data[SC_LIGHTOFSTAR].timer != -1 )
					rate += ( rate * sc->data[SC_LIGHTOFSTAR].val2 ) / 100;
				DMG_FIX( rate, 100 );
			}
			break;
		case SJ_STAREMPEROR:		// ����~��
			DMG_FIX( 1500 + 500 * skill_lv, 100 );
			break;
		case SJ_NOVAEXPLOSING:	// �V������
			DMG_FIX( 500 + 500 * skill_lv, 100 );
			DMG_ADD(status_get_max_hp(src) * skill_lv / 5  + status_get_max_sp(src) * skill_lv * 2);
			break;
		case SJ_BOOKOFCREATINGSTAR:	// �n���̏�
			DMG_FIX( 500 + 500 * skill_lv, 100 );
			break;
		case SU_BITE:	// ���݂�
			if(status_get_hp(target) / status_get_max_hp(target) * 100 <= 70) {
				DMG_FIX( 1500, 100 );
			} else {
				DMG_FIX( 1000, 100 );
			}
			break;
		case SU_SCRATCH:	// �Ђ�����
			DMG_FIX( 400 + 200 * skill_lv, 100 );
			break;
		case SU_PICKYPECK:	// �s�b�L�˂�
			{
				int rate = 1250 + 50 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// �����̍�
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
		case SU_PICKYPECK_DOUBLE_ATK:	// �s�b�L�˂�(�ǌ�)
			{
				int rate = 2500 + 100 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// �����̍�
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
		case SU_SCAROFTAROU:	// �^���E�̏�
			{
				int rate = 4000 + 200 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// �����̍�
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
				if(t_sc && t_sc->data[SC_BITESCAR].timer != -1)	// �^���E�̏����
					rate *= 2;
				DMG_FIX( rate, 100 );
			}
			break;
		case SU_LUNATICCARROTBEAT:	// �L�����b�g�r�[�g
		case SU_LUNATICCARROTBEAT2:	// �L�����b�g�r�[�g
			{
				int rate = 1000 + 100 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// �����̍�
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
				DMG_FIX( rate * (status_get_lv(src) >= 100? status_get_lv(src): 100) / 100, 100 );
			}
			break;
		case SU_SVG_SPIRIT:	// �T�x�[�W�̍�
			{
				int rate = 2500 + 100 * skill_lv;
				if(src_sd && pc_checkskill(src_sd,SU_SPIRITOFLIFE)) {	// �����̍�
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
		case DK_SERVANTWEAPON_ATK:	// �T�[���@���g�E�F�|��(�U��)
			DMG_FIX( (1250 + skill_lv*50 + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			break;
		case DK_SERVANT_W_PHANTOM:	// �T�[���@���g�E�F�|���F�t�@���g��
			DMG_FIX( (1250 + skill_lv*50 + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			wd.div_ = wflag;		// wflag�i����̂̐��j���U���񐔂Ƃ���
			break;
		case DK_SERVANT_W_DEMOL:	// �T�[���@���g�E�F�|���F�f�����b�V����
			DMG_FIX( (1250 + skill_lv*50 + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			wd.div_ = wflag;		// wflag�i����̂̐��j���U���񐔂Ƃ���
			break;
		case DK_HACKANDSLASHER:		// �n�b�N�A���h�X���b�V���[
		case DK_HACKANDSLASHER_ATK:	// �n�b�N�A���h�X���b�V���[(�U��)
			DMG_FIX( (1400 + skill_lv*100 + status_get_pow(src)*8) * status_get_lv(src) / 100, 100 );
			break;
		case DK_DRAGONIC_AURA:	// �h���S�j�b�N�I�[��
			DMG_FIX( (7000 + skill_lv*2000 + status_get_pow(src)*90) * status_get_lv(src) / 100, 100 );
			break;
		case DK_MADNESS_CRUSHER:	// �}�b�h�l�X�N���b�V���[
			{
				int weight = 0, wlv = 0;
				if(src_sd && src_sd->equip_index[EQUIP_INDEX_RARM] >= 0) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid)) {
						weight = src_sd->inventory_data[idx]->weight/10;
						wlv = src_sd->inventory_data[idx]->wlv;
					}
				}
				DMG_FIX( (3000 + skill_lv*900 + status_get_pow(src)*(10+skill_lv*3) + weight * wlv) * status_get_lv(src) / 100, 100 );
			}
			break;
		case DK_STORMSLASH:		//�X�g�[���X���b�V��
			DMG_FIX( (1250 + skill_lv*50 + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			if(sc && sc->data[SC_GIANTGROWTH].timer != -1 && atn_rand() % 100 < 15) {		// �W���C�A���g�O���[�X���
				DMG_FIX( 200, 100 );
			}
			break;
		case IQ_OLEUM_SANCTUM:		/* �������� */
			DMG_FIX( (2000 + skill_lv*500 + status_get_pow(src)*15) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_MASSIVE_F_BLASTER:	/* ���ΖŖ��_�e */
			DMG_FIX( (3500 + skill_lv*1000 + status_get_pow(src)*45) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_EXPOSION_BLASTER:	/* ���ΐ_�e */
			DMG_FIX( (2000 + skill_lv*500 + status_get_pow(src)*15) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_FIRST_BRAND:		/* ��ꌂ�F���� */
			DMG_FIX( (2000 + skill_lv*500 + status_get_pow(src)*15) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_SECOND_FLAME:		/* ��񌂁F�Ŗ��̉� */
			DMG_FIX( (3600 + skill_lv*900 + status_get_pow(src)*27) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_SECOND_FAITH:		/* ��񌂁F�M�O */
			DMG_FIX( (3150 + skill_lv*750 + status_get_pow(src)*23) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_SECOND_JUDGEMENT:	/* ��񌂁F�R�� */
			DMG_FIX( (3375 + skill_lv*825 + status_get_pow(src)*25) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_THIRD_PUNISH:		/* ��O���F�f�� */
			DMG_FIX( (7000 + skill_lv*1000 + status_get_pow(src)*40) * status_get_lv(src) / 100, 100 );
			break;
		case IQ_THIRD_FLAME_BOMB:	/* ��O���F�ŉΌ� */
			DMG_FIX( (7000 + skill_lv*1000 + status_get_pow(src)*40) * status_get_lv(src) / 100, 100 );
			if(src_sd) {
				if(src_sd->spiritball.num >= 11) {
					wd.div_ = 3;
				} else if(src_sd->spiritball.num >= 6) {
					wd.div_ = 2;
				}
			}
			break;
		case IQ_THIRD_CONSECRATION:	/* ��O���F�� */
			DMG_FIX( (7000 + skill_lv*1000 + status_get_pow(src)*40) * status_get_lv(src) / 100, 100 );
			break;
		case IG_GRAND_JUDGEMENT:	/* �O�����h�W���b�W�����g */
			DMG_FIX( (7000 + skill_lv*2000 + status_get_pow(src)*35) * status_get_lv(src) / 100, 100 );
			break;
		case IG_SHIELD_SHOOTING:	/* �V�[���h�V���[�e�B���O */
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(idx >= 0 && src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_FIX( (600 + (800 + pc_checkskill(src_sd,IG_SHIELD_MASTERY)*40) * skill_lv + src_sd->status.inventory[idx].refine*200 + src_sd->inventory_data[idx]->weight/10 + status_get_pow(src)*30) * status_get_lv(src) / 100, 100);
				}
			} else {
				DMG_FIX( (600 + 800 * skill_lv + status_get_pow(src)*30) * status_get_lv(src) / 100, 100 );
			}
			break;
		case IG_OVERSLASH:	/* �I�[�o�[�X���b�V�� */
			DMG_FIX( (skill_lv*70 + ((src_sd)? pc_checkskill(src_sd,IG_SPEAR_SWORD_M): 0) * (skill_lv * 5) + status_get_pow(src)*3) * status_get_lv(src) / 100, 100);
			if(wflag < 2) {
				wd.div_ = skill_get_num(skill_num,1);
			} else if(wflag < 4) {
				wd.div_ = skill_get_num(skill_num,2);
			} else {
				wd.div_ = skill_get_num(skill_num,3);
			}
			break;
		case CD_EFFLIGO:	/* �G�t�B���S */
			if(t_race == RCT_UNDEAD || t_race == RCT_DEMON) {
				DMG_FIX( (4000 + 500 * skill_lv + ((src_sd)? pc_checkskill(src_sd,CD_MACE_BOOK_M): 0) * (400 + skill_lv * 50) + status_get_pow(src)*60) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (3000 + 375 * skill_lv + ((src_sd)? pc_checkskill(src_sd,CD_MACE_BOOK_M): 0) * (200 + skill_lv * 25) + status_get_pow(src)*30) * status_get_lv(src) / 100, 100 );
			}
			break;
		case CD_PETITIO:	/* �y�e�B�e�B�I */
			DMG_FIX( (250 * skill_lv + ((src_sd)? pc_checkskill(src_sd,CD_MACE_BOOK_M): 0) * (skill_lv * 20) + status_get_pow(src)*15) * status_get_lv(src) / 100, 100 );
			break;
		case SHC_DANCING_KNIFE:		/* �_���V���O�i�C�t */
			DMG_FIX( (100 + 100 * skill_lv + status_get_pow(src)*2) * status_get_lv(src) / 100, 100 );
			break;
		case SHC_SAVAGE_IMPACT:		/* �T�x�[�W�C���p�N�g */
			if(sc && sc->data[SC_SHADOW_EXCEED].timer != -1) {
				DMG_FIX( (1000 + 200 * skill_lv + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (500 + 100 * skill_lv + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			}
			if(sc && sc->data[SC_CLOAKINGEXCEED].timer != -1) {
				wd.div_ = 2;
			}
			break;
		case SHC_ETERNAL_SLASH:		/* �G�^�[�i���X���b�V�� */
			if(sc && sc->data[SC_SHADOW_EXCEED].timer != -1) {
				DMG_FIX( (100 + 100 * skill_lv + status_get_pow(src)*2) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (50 + 50 * skill_lv + status_get_pow(src)) * status_get_lv(src) / 100, 100 );
			}
			if(sc && sc->data[SC_E_SLASH_COUNT].timer != -1) {
				wd.div_ = sc->data[SC_E_SLASH_COUNT].val1;
			}
			break;
		case SHC_SHADOW_STAB:		/* �V���h�E�X�^�u */
			if(sc && sc->data[SC_CLOAKINGEXCEED].timer != -1) {
				DMG_FIX( (1250 + 1250 * skill_lv + status_get_pow(src)*25) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (500 + 500 * skill_lv + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
			}
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case SHC_IMPACT_CRATER:		/* �C���p�N�g�N���[�^�[ */
			DMG_FIX( (50 + 50 * skill_lv + status_get_pow(src)) * status_get_lv(src) / 100, 100 );
			if(sc && sc->data[SC_ROLLINGCUTTER].timer != -1) {
				wd.div_ = sc->data[SC_ROLLINGCUTTER].val1;
			}
			break;
		case SHC_FATAL_SHADOW_CROW:		/* �t�F�C�^���V���h�E�N���[ */
			DMG_FIX( (600 + 150 * skill_lv + status_get_pow(src)*7) * status_get_lv(src) / 100, 100 );
			break;
		case MT_AXE_STOMP:		/* �A�b�N�X�X�g���v */
			DMG_FIX( (3150 + 750 * skill_lv + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
			if(src_sd && src_sd->status.weapon == WT_2HAXE) {
				wd.div_ = 2;
			}
			break;
		case MT_RUSH_QUAKE:		/* ���b�V���N�G�C�N */
			DMG_FIX( (2700 * skill_lv + status_get_pow(src)*40) * status_get_lv(src) / 100, 100 );
			break;
		case MT_A_MACHINE:		/* �U�����u�L���� */
			DMG_FIX( (300 * skill_lv + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			break;
		case ABC_ABYSS_DAGGER:		/* �A�r�X�_�K�[ */
			DMG_FIX( (3150 + 750 * skill_lv + status_get_pow(src)*23) * status_get_lv(src) / 100, 100 );
			break;
		case ABC_UNLUCKY_RUSH:		/* �A�����b�L�[���b�V�� */
			DMG_FIX( (2100 + 600 * skill_lv + status_get_pow(src)*17) * status_get_lv(src) / 100, 100 );
			break;
		case ABC_CHAIN_REACTION_SHOT:		/* �`�F�[�����A�N�V�����V���b�g */
		case ABC_CHAIN_REACTION_SHOT_ATK:	/* �`�F�[�����A�N�V�����V���b�g(�U��) */
			DMG_FIX( (2350 + 550 * skill_lv + status_get_con(src)*17) * status_get_lv(src) / 100, 100 );
			break;
		case ABC_DEFT_STAB:		/* �f�t�g�X�^�u */
			DMG_FIX( (3400 + 350 * skill_lv + status_get_pow(src)*23) * status_get_lv(src) / 100, 100 );
			break;
		case ABC_FRENZY_SHOT:	/* �t�����W�V���b�g */
			DMG_FIX( (1100 + 100 * skill_lv + status_get_con(src)*7) * status_get_lv(src) / 100, 100 );
			if(atn_rand()%100 < skill_lv * 5) {
				wd.div_ = 3;
			}
			break;
		case WH_HAWKRUSH:		/* �z�[�N���b�V�� */
			DMG_FIX( (1000 + 100 * skill_lv + status_get_con(src)*5) * ((src_sd)? 100+pc_checkskill(src_sd,WH_NATUREFRIENDLY)*20: 100) / 100 * status_get_lv(src) / 100, 100 );
			break;
		case WH_GALESTORM:		/* �Q�C���X�g�[�� */
			DMG_FIX( (1000 + 200 * skill_lv + status_get_con(src)*10) * status_get_lv(src) / 100, 100 );
			if(sc && sc->data[SC_CALAMITYGALE].timer != -1 && (t_race == RCT_BRUTE || t_race == RCT_FISH)) {
				DMG_FIX( 200, 100);
			}
			break;
		case WH_HAWKBOOMERANG:	/* �z�[�N�u�[������ */
			DMG_FIX( (1000 + 100 * skill_lv + status_get_con(src)*5) * ((src_sd)? 100+pc_checkskill(src_sd,WH_NATUREFRIENDLY)*20: 100) / 100 * status_get_lv(src) / 100, 100 );
			break;
		case WH_CRESCIVE_BOLT:		/* �N���b�V�u�{���g */
			DMG_FIX( (1000 + 200 * skill_lv + status_get_con(src)*10) * status_get_lv(src) / 100, 100 );
			if(sc && sc->data[SC_CRESCIVEBOLT].timer != -1) {
				if(sc->data[SC_CRESCIVEBOLT].val1 == 1) {
					DMG_FIX( 110, 100);
				} else if(sc->data[SC_CRESCIVEBOLT].val1 == 2) {
					DMG_FIX( 125, 100);
				} else {
					DMG_FIX( 150, 100);
				}
			}
			if(sc && sc->data[SC_CALAMITYGALE].timer != -1) {
				if(t_race == RCT_BRUTE || t_race == RCT_FISH) {
					DMG_FIX( 200, 100);
				} else {
					DMG_FIX( 125, 100);
				}
			}
			break;
		case WH_DEEPBLINDTRAP:	/* �f�B�[�v�u���C���h�g���b�v */
		case WH_SOLIDTRAP:		/* �\���b�h�g���b�v */
		case WH_SWIFTTRAP:		/* �X�C�t�g�g���b�v */
		case WH_FLAMETRAP:		/* �t���C���g���b�v */
			DMG_FIX( (1500 + 300 * skill_lv + status_get_con(src)*10) * ((src_sd)? 100+pc_checkskill(src_sd,WH_ADVANCED_TRAP)*20: 100) / 100 * status_get_lv(src) / 100, 100 );
			break;
		case BO_ACIDIFIED_ZONE_WATER:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
		case BO_ACIDIFIED_ZONE_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(�n) */
		case BO_ACIDIFIED_ZONE_WIND:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
		case BO_ACIDIFIED_ZONE_FIRE:		/* �A�V�f�B�t�@�C�h�]�[��(��) */
			if(sc && sc->data[SC_RESEARCHREPORT].timer != -1) {
				DMG_FIX( (2500 + 250 * skill_lv + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
				if(t_race == RCT_FORMLESS || t_race == RCT_PLANT) {
					DMG_FIX( 150, 100);
				}
			} else {
				DMG_FIX( (2000 + 200 * skill_lv + status_get_pow(src)*5) * status_get_lv(src) / 100, 100 );
			}
			break;
		case BO_ACIDIFIED_ZONE_WATER_INSTALL_ON_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(��)(�ݒu) */
		case BO_ACIDIFIED_ZONE_GROUND_INSTALL_ON_GROUND:	/* �A�V�f�B�t�@�C�h�]�[��(�n)(�ݒu) */
		case BO_ACIDIFIED_ZONE_WIND_INSTALL_ON_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(��)(�ݒu) */
		case BO_ACIDIFIED_ZONE_FIRE_INSTALL_ON_GROUND:		/* �A�V�f�B�t�@�C�h�]�[��(��)(�ݒu) */
			DMG_FIX( (625 * skill_lv / 10) * status_get_lv(src) / 100, 100 );
			break;
		case TR_RHYTHMSHOOTING:		/*���Y���V���[�e�B���O */
			if(t_sc && t_sc->data[SC_SOUNDBLEND].timer != -1) {
				DMG_FIX( (1250 + 350 * skill_lv + status_get_con(src)*10) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (750 + 150 * skill_lv + status_get_con(src)*5) * status_get_lv(src) / 100, 100 );
			}
			break;

		case NPC_BO_THROWROCK:		/* �X���[���b�N */
			DMG_FIX( 20000 * status_get_lv(src) / 100, 100 );
			break;
		case NPC_BO_WOODEN_ATTACK:	/* �E�h�D���A�^�b�N */
			DMG_FIX( 20000 * status_get_lv(src) / 100, 100 );
			break;
		case NW_THE_VIGILANTE_AT_NIGHT:		/* �r�W�����g�A�b�g�i�C�g */
			if(src_sd && src_sd->status.weapon == WT_GATLING) {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (375 + skill_lv * 85 + status_get_con(src) * 2 + (125 + skill_lv * 25) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (375 + skill_lv * 85 + status_get_con(src) * 2) * status_get_lv(src) / 100, 100 );
				}
				wd.div_ = 7;
				calc_flag.idef = calc_flag.idef_ = 1;
			} else {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (700 + skill_lv * 150 + status_get_con(src) * 3 + (300 + skill_lv * 50) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (700 + skill_lv * 150 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
			}
			break;
		case NW_ONLY_ONE_BULLET:		/* �I�����[�����o���b�g */
			if(src_sd && src_sd->status.weapon == WT_RIFLE) {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (2800 + skill_lv * 500 + status_get_con(src) * 3 + (950 + skill_lv * 150) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (2800 + skill_lv * 500 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
			} else {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (6000 + skill_lv * 900 + status_get_con(src) * 3 + (950 + skill_lv * 150) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (6000 + skill_lv * 900 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
				calc_flag.idef = calc_flag.idef_ = 1;
			}
			break;
		case NW_SPIRAL_SHOOTING:		/* �X�p�C�����V���[�e�B���O */
			if(src_sd && src_sd->status.weapon == WT_GRENADE) {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (1700 + skill_lv * 300 + status_get_con(src) * 3 + (550 + skill_lv * 100) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (1700 + skill_lv * 300 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
				wd.div_ += 1;
			} else {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (1950 + skill_lv * 350 + status_get_con(src) * 3 + (550 + skill_lv * 100) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (1950 + skill_lv * 350 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
			}
			break;
		case NW_MAGAZINE_FOR_ONE:		/* �}�K�W���t�H�[���� */
			if(src_sd && src_sd->status.weapon == WT_GATLING) {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (430 + skill_lv * 90 + status_get_con(src) * 2 + (125 + skill_lv * 25) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (430 + skill_lv * 90 + status_get_con(src) * 2) * status_get_lv(src) / 100, 100 );
				}
				wd.div_ += 4;
			} else {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (500 + skill_lv * 50 + status_get_con(src) * 2 + (125 + skill_lv * 25) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (500 + skill_lv * 50 + status_get_con(src) * 2) * status_get_lv(src) / 100, 100 );
				}
			}
			break;
		case NW_WILD_FIRE:		/* ���C���h�t�@�C�A */
			if(src_sd && src_sd->status.weapon == WT_GRENADE) {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (3700 + skill_lv * 600 + status_get_con(src) * 3 + (950 + skill_lv * 150) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (3700 + skill_lv * 600 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
			} else {
				if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1) {
					DMG_FIX( (3700 + skill_lv * 600 + status_get_con(src) * 3 + (950 + skill_lv * 150) * sc->data[SC_INTENSIVE_AIM_COUNT].val1) * status_get_lv(src) / 100, 100 );
				} else {
					DMG_FIX( (3700 + skill_lv * 600 + status_get_con(src) * 3) * status_get_lv(src) / 100, 100 );
				}
			}
			break;
		case NW_BASIC_GRENADE:		/* �x�[�V�b�N�O���l�[�h */
			DMG_FIX( (3000 + skill_lv * 600 + status_get_con(src) * 5 + ((src_sd)? pc_checkskill(src_sd,NW_GRENADE_MASTERY) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case NW_HASTY_FIRE_IN_THE_HOLE:	/* �w�C�X�e�B�t�@�C�A�C���U�z�[�� */
			DMG_FIX( (3000 + skill_lv * 600 + status_get_con(src) * 2 + ((src_sd)? pc_checkskill(src_sd,NW_GRENADE_MASTERY) * 20: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case NW_GRENADES_DROPPING:	/* �O���l�[�Y�h���b�s���O */
			DMG_FIX( (1350 + skill_lv * 300 + status_get_con(src) * 3 + ((src_sd)? pc_checkskill(src_sd,NW_GRENADE_MASTERY) * 30: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case NW_MISSION_BOMBARD:	/* �~�b�V�����{���o�[�h */
			if(wflag&1) {		// �ݒu�U��
				DMG_FIX( (5000 + skill_lv * 1000 + status_get_con(src) * 5 + ((src_sd)? pc_checkskill(src_sd,NW_GRENADE_MASTERY) * 30: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (2500 + skill_lv * 750 + status_get_con(src) * 5 + ((src_sd)? pc_checkskill(src_sd,NW_GRENADE_MASTERY) * 100: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SH_CHUL_HO_SONIC_CLAW:	/* �^�C�K�[�X���b�V�� */
			if((src_sd && pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				DMG_FIX( (3000 + skill_lv * 500 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 150: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (2050 + skill_lv * 350 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 100: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SH_HOWLING_OF_CHUL_HO:	/* �^�C�K�[�n�E�����O */
			if((src_sd && pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				DMG_FIX( (2400 + skill_lv * 300 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 100: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (1600 + skill_lv * 200 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 50: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SH_HOGOGONG_STRIKE:	/* �^�C�K�[�X�g���C�N */
			if((src_sd && pc_checkskill(src_sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				DMG_FIX( (450 + skill_lv * 150 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 20: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (300 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SH_MYSTICAL_CREATURE_MASTERY) * 10: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case HN_DOUBLEBOWLINGBASH:	/* �_�u���{�E�����O�o�b�V�� */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (src_sd)? pc_checkskill(src_sd,HN_SELFSTUDY_TATICS): 0;
				int rate = (850 + ss_lv * 3 * skill_lv + status_get_pow(src) * 2) * status_get_lv(src) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// �u���C�L���O���~�b�g
				if(sc && sc->data[SC_BREAKINGLIMIT].timer != -1)
					rate = rate * 150 / 100;

				DMG_FIX( rate, 100 );
				if(wflag >= 4) {
					wd.div_ += 2;
				} else if(wflag >= 2) {
					wd.div_ += 1;
				}
			}
			break;
		case HN_MEGA_SONIC_BLOW:	/* ���K�\�j�b�N�u���[ */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (src_sd)? pc_checkskill(src_sd,HN_SELFSTUDY_TATICS): 0;
				int rate = (1650 + skill_lv * 50 + ss_lv * 5 * skill_lv + status_get_pow(src) * 4) * status_get_lv(src) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// �u���C�L���O���~�b�g
				if(sc && sc->data[SC_BREAKINGLIMIT].timer != -1)
					rate = rate * 150 / 100;

				DMG_FIX( rate, 100 );
				if(status_get_hp(target) < status_get_max_hp(target)/2) {
					wd.damage <<= 1;
					if(calc_flag.lh)
						wd.damage2 <<= 1;
				}
			}
			break;
		case HN_SHIELD_CHAIN_RUSH:	/* �V�[���h�`�F�[�����b�V�� */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (src_sd)? pc_checkskill(src_sd,HN_SELFSTUDY_TATICS): 0;
				int rate = (3050 + skill_lv * 175 + ss_lv * 3 * skill_lv + status_get_pow(src) * 3) * status_get_lv(src) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// �u���C�L���O���~�b�g
				if(sc && sc->data[SC_BREAKINGLIMIT].timer != -1)
					rate = rate * 150 / 100;

				DMG_FIX( rate, 100 );
			}
			break;
		case HN_SPIRAL_PIERCE_MAX:	/* �X�p�C�����s�A�[�X�}�b�N�X */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (src_sd)? pc_checkskill(src_sd,HN_SELFSTUDY_TATICS): 0;
				int rate = 4475 + skill_lv * 125 + ss_lv * 3 * skill_lv;
				switch(t_size) {
					case 0: rate = rate * 150 / 100; break;		// ���^
					case 1: rate = rate * 130 / 100; break;		// ���^
					case 2: rate = rate * 120 / 100; break;		// ��^
				}
				rate = (rate + status_get_pow(src) * 3) * status_get_lv(src) / 100;		// �����X�e�[�^�X�ƃx�[�X���x���ɂ��␳�̓T�C�Y�̉e�����󂯂Ȃ�

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// �u���C�L���O���~�b�g
				if(sc && sc->data[SC_BREAKINGLIMIT].timer != -1)
					rate = rate * 150 / 100;

				DMG_FIX( rate, 100 );
			}
			break;
		case SKE_RISING_SUN:		/* �V�n��z */
			DMG_FIX( (250 + skill_lv * 50 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_NOON_BLAST:		/* ���V��z */
			DMG_FIX( (1125 + skill_lv * 175 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_SUNSET_BLAST:		/* �V�z */
			DMG_FIX( (1575 + skill_lv * 225 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_RISING_MOON:		/* �V�n�ꌎ */
			DMG_FIX( (175 + skill_lv * 25 + status_get_pow(src) * 3 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_MIDNIGHT_KICK:		/* ���V�ꌎ */
			if(sc && (sc->data[SC_MIDNIGHT_MOON].timer != -1 || sc->data[SC_SKY_ENCHANT].timer != -1)) {
				DMG_FIX( (1500 + skill_lv * 200 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (750 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SKE_DAWN_BREAK:		/* �V�� */
			if(sc && (sc->data[SC_DAWN_MOON].timer != -1 || sc->data[SC_SKY_ENCHANT].timer != -1)) {
				DMG_FIX( (1750 + skill_lv * 300 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (875 + skill_lv * 150 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SKE_TWINKLING_GALAXY:	/* �V�n���� */
			DMG_FIX( (250 + skill_lv * 100 + status_get_pow(src) * 3 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 3 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_STAR_BURST:		/* �V������ */
			DMG_FIX( (150 + skill_lv * 100 + status_get_pow(src) * 3 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_STAR_CANNON:		/* �V�� */
			DMG_FIX( (750 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SKE_SKY_MASTERY) * 5 * skill_lv: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SKE_ALL_IN_THE_SKY:	/* �V������ */
			DMG_FIX( (skill_lv * 300 + status_get_pow(src) * 10) * status_get_lv(src) / 100, 100 );
			if(t_race == RCT_DEMON || t_race == RCT_DEMIHUMAN) {
				wd.div_ += 2;
			}
			break;
		case SS_SHIMIRU:			/* �e���� */
			DMG_FIX( (2500 + skill_lv * 500 + status_get_con(src) * 5) * status_get_lv(src) / 100, 100 );
			break;
		case SS_KAGEGARI:			/* �e��� */
			DMG_FIX( (3500 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KAGEGISSEN) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SS_KAGENOMAI:			/* �e�̕� */
			DMG_FIX( (3500 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KAGEGARI) * 50: 0)) * status_get_lv(src) / 100, 100 );
			if(wflag&2) {	// ���g�U��
				wd.damage = wd.damage * 30 / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * 30 / 100;
			}
			break;
		case SS_KAGEGISSEN:			/* �e��M */
			DMG_FIX( (2000 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KAGENOMAI) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SS_FUUMASHOUAKU:		/* �����藠�� -����- */
			DMG_FIX( (skill_lv * 50 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_FUUMAKOUCHIKU) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SS_FUUMAKOUCHIKU:		/* �����藠�� -�\�z- */
			if(wflag) {	// ����
				DMG_FIX( (10500 + skill_lv * 200 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_FUUMASHOUAKU) * 50: 0)) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (3800 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_FUUMASHOUAKU) * 50: 0)) * status_get_lv(src) / 100, 100 );
			}
			break;
		case SS_KUNAIWAIKYOKU:		/* �ꖳ -�c��- */
			DMG_FIX( (3900 + skill_lv * 100 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KUNAIKUSSETSU) * 50: 0)) * status_get_lv(src) / 100, 100 );
			if(wflag&2) {	// ���g�U��
				wd.damage = wd.damage * 30 / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * 30 / 100;
			}
			break;
		case SS_KUNAIKAITEN:		/* �ꖳ -��]- */
			DMG_FIX( (1500 + skill_lv * 200 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KUNAIWAIKYOKU) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SS_KUNAIKUSSETSU:		/* �ꖳ -����- */
			DMG_FIX( (500 + skill_lv * 50 + status_get_pow(src) * 5 + ((src_sd)? pc_checkskill(src_sd,SS_KUNAIKAITEN) * 50: 0)) * status_get_lv(src) / 100, 100 );
			break;
		case SS_KAGEAKUMU:			/* ���p -�e�D��- */
			DMG_FIX( (23000 + status_get_pow(src) * 10) * status_get_lv(src) / 100, 100 );
			if(t_sc && t_sc->data[SC_NIGHTMARE].timer != -1) {
				wd.damage = wd.damage * 150 / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * 150 / 100;
			}
			break;
		case SS_HITOUAKUMU:			/* ���p -�ꖳ- */
			DMG_FIX( (23000 + status_get_pow(src) * 10) * status_get_lv(src) / 100, 100 );
			if(t_sc && t_sc->data[SC_NIGHTMARE].timer != -1) {
				wd.damage = wd.damage * 150 / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * 150 / 100;
			}
			break;
		case DK_DRAGONIC_BREATH:	/* �h���S�j�b�N�u���X */
			if(sc && sc->data[SC_DRAGONIC_AURA].timer != -1) {
				DMG_FIX( (3500 + skill_lv*400 + status_get_pow(src)*20 + status_get_max_hp(src)/500 + status_get_max_sp(src)/20) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (2750 + skill_lv*325 + status_get_pow(src)*10 + status_get_max_hp(src)/500 + status_get_max_sp(src)/20) * status_get_lv(src) / 100, 100 );
			}
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case MT_SPARK_BLASTER:		/* �X�p�[�N�u���X�^�[ */
			DMG_FIX( (3750 + skill_lv*375 + status_get_pow(src)*20) * status_get_lv(src) / 100, 100 );
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case MT_TRIPLE_LASER:		/* �g���v�����[�U�[ */
			DMG_FIX( (1100 + skill_lv*200 + status_get_pow(src)*7) * status_get_lv(src) / 100, 100 );
			break;
		case MT_MIGHTY_SMASH:		/* �}�C�e�B�X�}�b�V�� */
			if(sc && sc->data[SC_AXE_STOMP].timer != -1) {
				DMG_FIX( (4700 + skill_lv*400 + status_get_pow(src)*20) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (3400 + skill_lv*350 + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
			}
			break;
		case BO_EXPLOSIVE_POWDER:	/* �G�N�X�v���b�V�u�p�E�_�[ */
			if(sc && sc->data[SC_RESEARCHREPORT].timer != -1) {
				DMG_FIX( (3700 + skill_lv*1000 + status_get_pow(src)*29) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (3150 + skill_lv*750 + status_get_pow(src)*23) * status_get_lv(src) / 100, 100 );
			}
			break;
		case BO_MAYHEMIC_THORNS:	/* ���C�w�~�b�N�\�[���Y */
			if(sc && sc->data[SC_RESEARCHREPORT].timer != -1) {
				DMG_FIX( (2500 + skill_lv*200 + status_get_pow(src)*15) * status_get_lv(src) / 100, 100 );
			} else {
				DMG_FIX( (2000 + skill_lv*100 + status_get_pow(src)*10) * status_get_lv(src) / 100, 100 );
			}
			break;
		case EL_CIRCLE_OF_FIRE:	// �T�[�N���I�u�t�@�C�A
			DMG_FIX( 300, 100 );
			break;
		case EL_FIRE_BOMB_ATK:	// �t�@�C�A�[�{��(�U��)
			DMG_FIX( 300, 100 );
			break;
		case EL_FIRE_WAVE_ATK:	// �t�@�C�A�[�E�F�[�u(�U��)
			DMG_FIX( 600, 100 );
			break;
		case EL_WATER_SCREW_ATK:	// �E�H�[�^�[�X�N�����[(�U��)
			DMG_FIX( 1000, 100 );
			break;
		case EL_TIDAL_WEAPON:	// �^�C�_���E�F�|��
			DMG_FIX( 1500, 100 );
			break;
		case EL_WIND_SLASH:	// �E�B���h�X���b�V��
			DMG_FIX( 200, 100 );
			break;
		case EL_HURRICANE:	// �n���P�[�����C�W
			DMG_FIX( 700, 100 );
			break;
		case EL_TYPOON_MIS:	// �^�C�t�[���~�T�C��
			DMG_FIX( 1000, 100 );
			break;
		case EL_STONE_HAMMER:	// �X�g�[���n���}�[
			DMG_FIX( 500, 100 );
			break;
		case EL_ROCK_CRUSHER:	// ���b�N�����`���[
			DMG_FIX( 800, 100 );
			break;
		case EL_STONE_RAIN:	// �X�g�[�����C��
			DMG_FIX( 800, 100 );
			break;
		case ABR_BATTLE_BUSTER:		/* �o�g���o�X�^�[ */
			DMG_FIX( 300 * status_get_lv(src) / 100, 100 );
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case ABR_DUAL_CANNON_FIRE:	/* �f���A���L���m���t�@�C���[ */
			DMG_FIX( 150 * status_get_lv(src) / 100, 100 );
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case ABR_INFINITY_BUSTER:	/* �C���t�B�j�e�B�o�X�^�[ */
			DMG_FIX( 500 * status_get_lv(src) / 100, 100 );
			calc_flag.idef = calc_flag.idef_ = 1;
			break;
		case 0:			// �ʏ�U��
			DMG_FIX( 100, 100 );
			break;
		}
		if(skill_lv < 0)
			calc_flag.nocardfix = 1;

		/* �X�L���{���v�Z�ɉ��Z�I�� */
		if(add_rate > 0)
			add_rate = 0;

		/* 13. P.Atk�ɂ�镨���U���_���[�W���� */
		DMG_FIX( 100 + status_get_patk(src), 100 );

#ifdef PRE_RENEWAL
		/* 14�D�t�@�C�e�B���O�̒ǉ��_���[�W */
		wd.damage += tk_power_damage;
		if(calc_flag.lh)
			wd.damage2 += tk_power_damage2;

		/* 15�D�h�䖳�����肨��ѐ����ʃ_���[�W�v�Z */
		switch (skill_num) {
		case KN_AUTOCOUNTER:
		case MO_INVESTIGATE:
		case MO_EXTREMITYFIST:
		case CR_ACIDDEMONSTRATION:
		case NPC_EARTHQUAKE:
		case GS_FLING:
		case NJ_ZENYNAGE:
		case GN_FIRE_EXPANSION_ACID:
		case KO_MUCHANAGE:
			break;
		default:
			if( wd.type != 0 )	// �N���e�B�J�����͖���
				break;
			if( skill_num == WS_CARTTERMINATION && !battle_config.def_ratio_atk_to_carttermination )
				break;
			if( skill_num == PA_SHIELDCHAIN && !battle_config.def_ratio_atk_to_shieldchain )
				break;
			if(src_sd && t_def1 < 1000000)
			{
				// bIgnoreDef�n����
				ignored_rate  = ignored_rate  - src_sd->ignore_def_ele[t_ele]  - src_sd->ignore_def_race[t_race]  - src_sd->ignore_def_enemy[t_enemy];
				ignored_rate_ = ignored_rate_ - src_sd->ignore_def_ele_[t_ele] - src_sd->ignore_def_race_[t_race] - src_sd->ignore_def_enemy_[t_enemy];
				if(t_mode & MD_BOSS) {
					ignored_rate  -= src_sd->ignore_def_race[RCT_BOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_BOSS];
				} else {
					ignored_rate  -= src_sd->ignore_def_race[RCT_NONBOSS];
					ignored_rate_ -= src_sd->ignore_def_race_[RCT_NONBOSS];
				}

				if(battle_config.left_cardfix_to_right) {
					// ����J�[�h�␳�ݒ肠��
					ignored_rate -= 100 - ignored_rate_;
					ignored_rate_ = 100;
				}

				if(skill_num != CR_GRANDCROSS && skill_num != AM_ACIDTERROR) {
					int mask = (1<<t_race) | ( (t_mode&MD_BOSS)? (1<<RCT_BOSS): (1<<RCT_NONBOSS));

					// bDefRatioATK�n�AbIgnoreDef�n�������Ƃ��̂݌��ʗL��
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

			// �O�����h�N���X�A�O�����h�_�[�N�l�X��DEF��������������
			if(skill_num == CR_GRANDCROSS || skill_num == NPC_GRANDDARKNESS) {
				calc_flag.idef  = 0;
				calc_flag.idef_ = 0;
			}
			break;
		}
#else
		/* �iRE�j�X�L���C���T�i�ǉ��_���[�W�Q�j */
		if(src_sd && src_sd->status.weapon == WT_KATAR && skill_num != ASC_BREAKER && skill_lv >= 0) {
			// �J�^�[������
			if((skill = pc_checkskill(src_sd,ASC_KATAR)) > 0) {
				wd.damage += wd.damage*(10+(skill * 2))/100;
			}
		}

		/* �iRE�j���B�_���[�W�̒ǉ� */
		if( src_sd ) {
			switch (skill_num) {
			case CR_SHIELDBOOMERANG:	// �V�[���h�u�[������
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

		/* 16�DRes�ɂ�镨���_���[�W���� */
		if(t_res > 0) {
			int res_rate = 100;
			if(sc) {
				if(sc->data[SC_A_TELUM].timer != -1) {		// �A���O�g�D�X�e����
					res_rate -= sc->data[SC_A_TELUM].val2;
				}
				if(sc->data[SC_POTENT_VENOM].timer != -1) {		// �|�e���g�x�i��
					res_rate -= sc->data[SC_POTENT_VENOM].val2;
				}
			}

			if(res_rate < 50) {
				res_rate = 50;
			}
			if(res_rate != 100) {
				t_res = t_res * res_rate / 100;
			}
			wd.damage = wd.damage * (2000 + t_res) / (2000 + t_res * 5);
			if(calc_flag.lh)
				wd.damage2 = wd.damage2 * (2000 + t_res) / (2000 + t_res * 5);
		}

		/* 17�D�Ώۂ̖h��͂ɂ��_���[�W�̌��� */
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
		case NJ_ISSEN:
		case NJ_TATAMIGAESHI:
#endif
		case KN_AUTOCOUNTER:
		case MO_INVESTIGATE:
		case MO_EXTREMITYFIST:
		case CR_ACIDDEMONSTRATION:
		case NJ_ZENYNAGE:
		case NPC_CRITICALSLASH:
		case NPC_VENOMFOG:
		case NPC_EARTHQUAKE:
		case GS_FLING:
		case GS_PIERCINGSHOT:
		case RA_CLUSTERBOMB:
		case RA_FIRINGTRAP:
		case RA_ICEBOUNDTRAP:
		case GC_COUNTERSLASH:
		case NC_ARMSCANNON:
		case NC_SELFDESTRUCTION:
		case GN_FIRE_EXPANSION_ACID:
		case KO_MUCHANAGE:
		case MH_EQC:
			break;
		default:
#ifdef PRE_RENEWAL
			if(wd.type != 0)	// �N���e�B�J�����͖���
				break;
#endif
			// ���z�ƌ��Ɛ��̗Z�� DEF����
			if(sc && sc->data[SC_FUSION].timer != -1)
				calc_flag.idef = 1;

			// DEF�����t���O���Ȃ��Ƃ�
			if( ((calc_flag.rh && !calc_flag.idef) || (calc_flag.lh && !calc_flag.idef_)) && t_def1 < 1000000 )
			{
				int vitbonusmax;

				// �G�N�X�s�A�e�B�I
				if(sc && sc->data[SC_EXPIATIO].timer != -1 && wd.flag&BF_SHORT) {
					t_def1 -= t_def1 * sc->data[SC_EXPIATIO].val2 / 100;
				}

				// �_�� -��-
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
				if(t_sc) {
					// �t�H�[�X�I�u�o���K�[�h
					if(t_sc->data[SC_FORCEOFVANGUARD].timer != -1) {
						t_def1 += (t_def1 * t_sc->data[SC_FORCEOFVANGUARD].val1 * 2) / 100;
					}
					// �J���t���[�W��
					if(t_sc->data[SC_CAMOUFLAGE].timer != -1)
						t_def1 -= t_def1 * ((10 - t_sc->data[SC_CAMOUFLAGE].val2) * 5) / 100;
					// �G�R�[�̉�
					if(t_sc->data[SC_ECHOSONG].timer != -1) {
						// ���ۂɂ͏��ZDEF���������A�b��Ō��ZDEF
						t_def2 += t_def2 * t_sc->data[SC_ECHOSONG].val4 / 100;
					}
					// ���
					if(t_sc->data[SC_PARALYZE].timer != -1) {
						t_def1 -= t_def1 * t_sc->data[SC_PARALYZE].val3 / 100;
					}
					// �I�[�o�[�h�u�[�X�g
					if(t_sc->data[SC_OVERED_BOOST].timer != -1) {
						t_def1 /= 2;
					}
				}
				// �y���F����
				if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
					// ���ۂɂ͏��ZDEF���������A�b��Ō��ZDEF
					t_def2 += t_def2 * src_sd->elementball.num * 10 / 100;
				}
#else
				if(t_sc) {
					short reduce = 100;
					// �A�X���v�e�B�I
					if(t_sc->data[SC_ASSUMPTIO].timer != -1) {
						if(map[target->m].flag.pvp || map[target->m].flag.gvg)
							reduce += 35;	// �V�[�Y��35%
						else
							reduce += 100;	// ����ȊO��100%
					}
					// �t�H�[�X�I�u�o���K�[�h
					if(t_sc->data[SC_FORCEOFVANGUARD].timer != -1) {
						reduce += t_sc->data[SC_FORCEOFVANGUARD].val1 * 2;
					}
					// �G�R�[�̉�
					if(t_sc->data[SC_ECHOSONG].timer != -1) {
						reduce += t_sc->data[SC_ECHOSONG].val4;
					}
					// �J���t���[�W��
					if(t_sc->data[SC_CAMOUFLAGE].timer != -1) {
						reduce -= (10 - t_sc->data[SC_CAMOUFLAGE].val2) * 5;
					}
					// ���
					if(t_sc->data[SC_PARALYZE].timer != -1) {
						reduce -= t_sc->data[SC_PARALYZE].val3;
					}
					// �I�[�o�[�h�u�[�X�g
					if(t_sc->data[SC_OVERED_BOOST].timer != -1) {
						reduce -= 50;
					}
					// �y���F����
					if(src_sd && src_sd->elementball.num && src_sd->elementball.ele == ELE_EARTH) {
						reduce += src_sd->elementball.num * 10;
					}
					if(reduce)
						t_def1 = t_def1 * reduce / 100;
					else
						t_def1 = 0;
				}
#endif

				// �f�B�o�C���v���e�N�V����
				if(target_sd && (skill = pc_checkskill(target_sd,AL_DP)) > 0) {
					int s_race = status_get_race(src);
					if(battle_check_undead(s_race,status_get_elem_type(src)) || s_race == RCT_DEMON)
						t_def2 += ((300 + 4 * target_sd->status.base_level) * skill) / 100;
				}
				// �����W���[���C��
				if(target_sd && (skill = pc_checkskill(target_sd,RA_RANGERMAIN)) > 0) {
					int s_race = status_get_race(src);
					if(s_race == RCT_BRUTE || s_race == RCT_PLANT || s_race == RCT_FISH)
						t_def2 += skill * 5;
				}
				// �΂Ƒ�n�̌���
				if(target_sd && (skill = pc_checkskill(target_sd,NC_RESEARCHFE)) > 0) {
					int s_element = status_get_element(src)%20;
					if(s_element == ELE_FIRE || s_element ==  ELE_EARTH)
						t_def2 += skill * 10;
				}
				vitbonusmax = (t_vit / 20) * (t_vit / 20) - 1;

				if(calc_flag.rh && !calc_flag.idef) {
					if(ignored_rate > 0) {
						// bIgnoreDef�E��v�Z
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
						// bIgnoreDef����v�Z
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

		// �y�C���L���[
		if(t_sc && t_sc->data[SC_PAIN_KILLER].timer != -1) {
			wd.damage -= t_sc->data[SC_PAIN_KILLER].val4;
			if(calc_flag.lh)
				wd.damage2 -= t_sc->data[SC_PAIN_KILLER].val4;
		}

		/* 18�D��Ԉُ풆�̃_���[�W�ǉ��ŃN���e�B�J���ɂ��L���ȃX�L�� */
		if (sc) {
#ifdef PRE_RENEWAL
			// �I�[�o�[�g���X�g
			if(sc->data[SC_OVERTHRUST].timer != -1) {
				wd.damage += damage_ot*sc->data[SC_OVERTHRUST].val3/100;
				if(calc_flag.lh)
					wd.damage2 += damage_ot2*sc->data[SC_OVERTHRUST].val3/100;
			}
			// �I�[�o�[�g���X�g�}�b�N�X
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1) {
				wd.damage += damage_ot*(20*sc->data[SC_OVERTHRUSTMAX].val1)/100;
				if(calc_flag.lh)
					wd.damage2 += damage_ot2*(20*sc->data[SC_OVERTHRUSTMAX].val1)/100;
			}
			// �g�D���[�T�C�g
			if(sc->data[SC_TRUESIGHT].timer != -1) {
				DMG_FIX( 100+2*sc->data[SC_TRUESIGHT].val1, 100 );
			}
			// �o�[�T�[�N
			if(sc->data[SC_BERSERK].timer != -1) {
				DMG_FIX( 200, 100 );
			}
			// �G���`�����g�f�b�h���[�|�C�Y��
			if(sc->data[SC_EDP].timer != -1 && !calc_flag.nocardfix) {
				// �E��݂̂Ɍ��ʂ��̂�B�J�[�h���ʖ����̃X�L���ɂ͏��Ȃ�
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
			// �T�N���t�@�C�X
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
			// �C�N�V�[�h�u���C�N
			else if(sc->data[SC_EXEEDBREAK].timer != -1 && !skill_num) {
				wd.damage  = wd.damage * sc->data[SC_EXEEDBREAK].val2 / 100;
				wd.damage2 = 0;
				status_change_end(src, SC_EXEEDBREAK,-1);
			}
#ifdef PRE_RENEWAL
			// �G���`�����g�u���C�h
			if(sc->data[SC_ENCHANTBLADE].timer != -1 && (!skill_num || skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP) ) {
				static struct Damage ebd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				ebd = battle_calc_attack(BF_MAGIC,src,target,RK_ENCHANTBLADE,sc->data[SC_ENCHANTBLADE].val1,wd.flag);
				wd.damage += ebd.damage + ((100 + sc->data[SC_ENCHANTBLADE].val1 * 20) * status_get_lv(src) / 150);
			}
			// �N���b�V���X�g���C�N
			if(sc->data[SC_CRUSHSTRIKE].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
				if(src_sd) {
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(idx >= 0 && src_sd->inventory_data[idx]) {
						wd.damage *= (6 + src_sd->status.inventory[idx].refine) * src_sd->inventory_data[idx]->wlv + (itemdb_atk(src_sd->inventory_data[idx]->nameid) + src_sd->inventory_data[idx]->weight/10) / 100;
					}

					if(atn_rand() % 100 < 20) {	// 20%�̊m���ŕ���j��
						pc_break_equip(src_sd, LOC_RARM);
					}
				}
				status_change_end(src, SC_CRUSHSTRIKE,-1);
			}
			// �W���C�A���g�O���[�X
			else if(sc->data[SC_GIANTGROWTH].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
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
			// �V�[���h�X�y��
			if(sc->data[SC_SHIELDSPELL_REF].timer != -1 && sc->data[SC_SHIELDSPELL_REF].val2 == 1 && !skill_num) {
				if(target_sd && atn_rand() % 100 < sc->data[SC_SHIELDSPELL_REF].val3) {
					pc_break_equip(target_sd, LOC_BODY);
				}
			}
			// �A�N���E�X�_�b�V��
			if(sc->data[SC_ARCLOUSEDASH].timer != -1 && src_sd && pc_isdoram(src_sd) && wd.flag&BF_LONG) {
				wd.damage += wd.damage * sc->data[SC_ARCLOUSEDASH].val3 / 100;
			}
			// �`���[�W���O�X�s�A
			if(sc && sc->data[SC_CHARGINGPIERCE].timer != -1 && sc->data[SC_CHARGINGPIERCE_COUNT].timer != -1 && sc->data[SC_CHARGINGPIERCE_COUNT].val1 >= 10) {
				switch(skill_num) {
				case KN_PIERCE:			// �s�A�[�X
					DMG_FIX( 100 + sc->data[SC_CHARGINGPIERCE].val1 * 150, 100 );
					break;
				case LK_SPIRALPIERCE:	// �X�p�C�����s�A�[�X
					DMG_FIX( 100 + sc->data[SC_CHARGINGPIERCE].val1 * 100, 100 );
					break;
				case RK_HUNDREDSPEAR:	// �n���h���b�h�X�s�A
					DMG_FIX( 100 + sc->data[SC_CHARGINGPIERCE].val1 * 50, 100 );
					break;
				case DK_MADNESS_CRUSHER:	// �}�b�h�l�X�N���b�V���[
					DMG_FIX( 100 + sc->data[SC_CHARGINGPIERCE].val1 * 10, 100 );
					break;
				}
			}
			// ���B�S�[��
			if(sc && sc->data[SC_VIGOR].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
				DMG_FIX( 100 + sc->data[SC_VIGOR].val1 * 100, 100 );
			}
			// �h���S�j�b�N�I�[����Ԓ��̃h���S���u���X
			if(sc && sc->data[SC_DRAGONIC_AURA].timer != -1 && (skill_num == RK_DRAGONBREATH || skill_num ==RK_DRAGONBREATH_WATER)) {
				DMG_FIX( 100 + sc->data[SC_DRAGONIC_AURA].val1 * 15, 100 );
			}
		}

#ifdef PRE_RENEWAL
		/* 19�D���B�_���[�W�̒ǉ� */
		if( src_sd ) {
			switch(skill_num) {
			case MO_INVESTIGATE:
			case MO_EXTREMITYFIST:
			case PA_SHIELDCHAIN:
			case CR_ACIDDEMONSTRATION:
			case GS_FLING:
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
			case LK_SPIRALPIERCE:		// �X�p�C�����s�A�[�X
				if(src_sd->equip_index[EQUIP_INDEX_RARM] >= 0) {	// {((STR/10)^2 �{ ����d�ʁ~�X�L���{���~0.8) �~ �T�C�Y�␳ �{ ���B}�~�J�[�h�{���~�����{���~5�̖͗l
					int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
					if(src_sd->inventory_data[idx] && itemdb_isweapon(src_sd->inventory_data[idx]->nameid)) {
						wd.damage = ( ( (s_str/10)*(s_str/10) + src_sd->inventory_data[idx]->weight * (skill_lv * 4 + 8 ) / 100 )
									* (5 - t_size) / 4 + status_get_atk2(src) ) * 5;
					}
				}
				break;
			case PA_SHIELDCHAIN:		// �V�[���h�`�F�C��
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
		if(skill_num == CR_SHIELDBOOMERANG) {	// �V�[���h�u�[������
			int rate = 100+30*skill_lv;
			if(sc && sc->data[SC_CRUSADER].timer != -1)
				rate *= 2;
			DMG_FIX( rate, 100 );
		}

		if(sc) {
			// �������R���[
			if(sc->data[SC_GLOOMYDAY].timer != -1 && (skill_num == KN_BRANDISHSPEAR || skill_num == LK_SPIRALPIERCE || skill_num == CR_SHIELDCHARGE ||
			   skill_num == CR_SHIELDBOOMERANG || skill_num == PA_SHIELDCHAIN || skill_num == LG_SHIELDPRESS)) {
				wd.damage = wd.damage * (175 + sc->data[SC_GLOOMYDAY].val1 * 25) / 100;
				if(calc_flag.lh)
					wd.damage2 = wd.damage2 * (175 + sc->data[SC_GLOOMYDAY].val1 * 25) / 100;
			}
			// �J�[�g�u�[�X�g
			if(sc->data[SC_GN_CARTBOOST].timer != -1) {
				wd.damage += sc->data[SC_GN_CARTBOOST].val1 * 10;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_GN_CARTBOOST].val1 * 10;
			}
			// �v���`�i���A���^�[
			if(sc->data[SC_P_ALTER].timer != -1) {
				wd.damage += sc->data[SC_P_ALTER].val2;
				if(calc_flag.lh)
					wd.damage2 += sc->data[SC_P_ALTER].val2;
			}
		}
#endif

		// 0�����������ꍇ1�ɕ␳
		if(wd.damage  < 1) wd.damage  = 1;
		if(wd.damage2 < 1) wd.damage2 = 1;

		/* 20�D�X�L���C���Q�i�C���n�j*/
		// �C���_���[�W(�E��̂�) �\�j�b�N�u���[���͕ʏ����i1���ɕt��1/8�K��)
		if(src_sd) {
#ifdef PRE_RENEWAL
			switch(skill_num) {
		    case MO_INVESTIGATE:
		    case MO_EXTREMITYFIST:
		    case CR_GRANDCROSS:
		    case NPC_GRANDDARKNESS:
		    case NPC_EARTHQUAKE:
		    case LK_SPIRALPIERCE:
		   	case CR_ACIDDEMONSTRATION:
			case GS_FLING:
		    case NJ_ZENYNAGE:
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
				int skill = 0;
				int rate = 0;
				int tclass = status_get_class(target);

				if((skill = pc_checkskill(src_sd,SG_STAR_ANGER)) > 0 && ((sc && sc->data[SC_MIRACLE].timer != -1) || tclass == src_sd->hate_mob[2])) {	//  ���̓{��
					rate = (src_sd->status.base_level + status_get_dex(src) + status_get_luk(src) + s_str) / (12 - 3 * skill);
					if(rate > skill * 70)
						rate = skill * 70;
				} else if((skill = pc_checkskill(src_sd,SG_SUN_ANGER)) > 0 && tclass == src_sd->hate_mob[0]) {		// ���z�̓{��
					rate = (src_sd->status.base_level + status_get_dex(src) + status_get_luk(src)) / (12 - 3 * skill);
					if(rate > skill * 50)
						rate = skill * 50;
				} else if((skill = pc_checkskill(src_sd,SG_MOON_ANGER)) > 0 && tclass == src_sd->hate_mob[1]) {		// ���̓{��
					rate = (src_sd->status.base_level + status_get_dex(src) + status_get_luk(src)) / (12 - 3 * skill);
					if(rate > skill * 50)
						rate = skill * 50;
				}
				if(rate > 0) {
					DMG_FIX( 100 + rate, 100 );
				}
			}
		}
		if(sc) {
			if(sc->data[SC_AURABLADE].timer != -1)		// �I�[���u���[�h
				DMG_ADD( sc->data[SC_AURABLADE].val1*20 );
		}
	}

#ifdef PRE_RENEWAL
	/* 21�D�X�L���C���R�i�K���_���[�W�j*/
	if( src_sd && (skill = pc_checkskill(src_sd,BS_WEAPONRESEARCH)) > 0) {
		DMG_ADD( skill*2 );
	}
#endif
	if( src_sd && (skill = pc_checkskill(src_sd,TK_RUN)) > 0) {	// �^�C���M�p�b�V�u�ŏR��̈З͉��Z
		if( (skill_num == TK_DOWNKICK || skill_num == TK_STORMKICK || skill_num == TK_TURNKICK || skill_num == TK_COUNTER) &&
		    src_sd->weapontype1 == WT_FIST && src_sd->weapontype2 == WT_FIST ) {
			DMG_ADD( skill*10 );
		}
	}

#ifdef PRE_RENEWAL
	/* 22�D�J�[�h�ɂ��_���[�W�ǉ����� */
	if( src_sd && wd.damage > 0 && calc_flag.rh ) {
		cardfix = 100;
		if(!calc_flag.nocardfix) {
			if(!src_sd->state.arrow_atk) {	// �|��ȊO
				if(!battle_config.left_cardfix_to_right) {	// ����J�[�h�␳�ݒ薳��
					cardfix = cardfix*(100+src_sd->addrace[t_race])/100;	// �푰�ɂ��_���[�W�C��
					cardfix = cardfix*(100+src_sd->addele[t_ele])/100;	// �����ɂ��_���[�W�C��
					cardfix = cardfix*(100+src_sd->addenemy[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��
					cardfix = cardfix*(100+src_sd->addsize[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C��
					cardfix = cardfix*(100+src_sd->addgroup[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��
				} else {
					cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->addrace_[t_race])/100;		// �푰�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					cardfix = cardfix*(100+src_sd->addele[t_ele]+src_sd->addele_[t_ele])/100;		// �����ɂ��_���[�W�C��(����ɂ��ǉ�����)
					cardfix = cardfix*(100+src_sd->addenemy[t_enemy]+src_sd->addenemy_[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					cardfix = cardfix*(100+src_sd->addsize[t_size]+src_sd->addsize_[t_size])/100;		// �T�C�Y�ɂ��_���[�W�C��(����ɂ��ǉ�����)
					cardfix = cardfix*(100+src_sd->addgroup[t_group]+src_sd->addgroup_[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��(����ɂ��ǉ�����)
				}
			} else { // �|��
				cardfix = cardfix*(100+src_sd->addrace[t_race]+src_sd->arrow_addrace[t_race])/100;	// �푰�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				cardfix = cardfix*(100+src_sd->addele[t_ele]+src_sd->arrow_addele[t_ele])/100;		// �����ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				cardfix = cardfix*(100+src_sd->addenemy[t_enemy]+src_sd->arrow_addenemy[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				cardfix = cardfix*(100+src_sd->addsize[t_size]+src_sd->arrow_addsize[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
				cardfix = cardfix*(100+src_sd->addgroup[t_group]+src_sd->arrow_addgroup[t_group])/100;	// �O���[�v�ɂ��_���[�W�C��(�|��ɂ��ǉ�����)
			}
			if(t_mode & MD_BOSS) {	// �{�X
				if(!src_sd->state.arrow_atk) {	// �|��U���ȊO�Ȃ�
					if(!battle_config.left_cardfix_to_right) {
						// ����J�[�h�␳�ݒ薳��
						cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS])/100;					// �{�X�����X�^�[�ɒǉ��_���[�W
					} else {
						// ����J�[�h�␳�ݒ肠��
						cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS]+src_sd->addrace_[RCT_BOSS])/100;	// �{�X�����X�^�[�ɒǉ��_���[�W(����ɂ��ǉ�����)
					}
				} else {	// �|��U��
					cardfix = cardfix*(100+src_sd->addrace[RCT_BOSS]+src_sd->arrow_addrace[RCT_BOSS])/100;		// �{�X�����X�^�[�ɒǉ��_���[�W(�|��ɂ��ǉ�����)
				}
			} else {		// �{�X����Ȃ�
				if(!src_sd->state.arrow_atk) {	// �|��U���ȊO
					if(!battle_config.left_cardfix_to_right) {
						// ����J�[�h�␳�ݒ薳��
						cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS])/100;				// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W
					} else {
						// ����J�[�h�␳�ݒ肠��
						cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->addrace_[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W(����ɂ��ǉ�����)
					}
				} else {
					cardfix = cardfix*(100+src_sd->addrace[RCT_NONBOSS]+src_sd->arrow_addrace[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W(�|��ɂ��ǉ�����)
				}
			}
			// �J�[�h���ʂɂ����背���W�U���̃_���[�W����
			if(wd.flag&BF_SHORT) {
				cardfix = cardfix * (100+src_sd->short_weapon_damege_rate) / 100;
			}
			if(wd.flag&BF_LONG) {
				cardfix = cardfix * (100+src_sd->long_weapon_damege_rate) / 100;
			}
			// ����Class�p�␳����(�����̓��L���{���S���p�H)
			for(i=0; i<src_sd->add_damage_class_count; i++) {
				if(src_sd->add_damage_classid[i] == t_class) {
					cardfix = cardfix*(100+src_sd->add_damage_classrate[i])/100;
					break;
				}
			}
		}
		if(skill_num > 0 && wd.damage > 0) {
			int rate = 100;

			// �J�[�h���ʂɂ�����X�L���̃_���[�W�����i����X�L���j
			if(src_sd->skill_dmgup.count > 0) {
				for(i=0; i<src_sd->skill_dmgup.count; i++) {
					if(skill_num == src_sd->skill_dmgup.id[i]) {
						rate += src_sd->skill_dmgup.rate[i];
						break;
					}
				}
			}
			// �J�[�h���ʂɂ����葮���X�L���̃_���[�W�����i����X�L���j
			rate += src_sd->skill_eleweapon_dmgup[s_ele];
			cardfix = cardfix*rate/100;
		}
		wd.damage = wd.damage*cardfix/100;	// �J�[�h�␳�ɂ��_���[�W����
	}

	/* 23�D�J�[�h�ɂ�鍶��_���[�W�ǉ����� */
	if( src_sd && wd.damage2 > 0 && calc_flag.lh && !calc_flag.nocardfix ) {
		cardfix = 100;
		if(!battle_config.left_cardfix_to_right) {	// ����J�[�h�␳�ݒ薳��
			cardfix = cardfix*(100+src_sd->addrace_[t_race])/100;	// �푰�ɂ��_���[�W�C������
			cardfix = cardfix*(100+src_sd->addele_[t_ele])/100;	// �����ɂ��_���[�W�C������
			cardfix = cardfix*(100+src_sd->addenemy_[t_enemy])/100;	// �G�^�C�v�ɂ��_���[�W�C������
			cardfix = cardfix*(100+src_sd->addsize_[t_size])/100;	// �T�C�Y�ɂ��_���[�W�C������
			cardfix = cardfix*(100+src_sd->addgroup_[t_group])/100;	// �O���[�v�ɂ��_���[�W�C������
			if(t_mode & MD_BOSS)	// �{�X
				cardfix = cardfix*(100+src_sd->addrace_[RCT_BOSS])/100;		// �{�X�����X�^�[�ɒǉ��_���[�W����
			else
				cardfix = cardfix*(100+src_sd->addrace_[RCT_NONBOSS])/100;	// �{�X�ȊO�����X�^�[�ɒǉ��_���[�W����
		}
		// ����Class�p�␳��������(�����̓��L���{���S���p�H)
		for(i=0; i<src_sd->add_damage_class_count_; i++) {
			if(src_sd->add_damage_classid_[i] == t_class) {
				cardfix = cardfix*(100+src_sd->add_damage_classrate_[i])/100;
				break;
			}
		}
		wd.damage2 = wd.damage2*cardfix/100;	// �J�[�h�␳�ɂ�鍶��_���[�W����
	}

	/* 24�D�\�E���u���C�J�[�̖��@�_���[�W�ƃ����_���_���[�W�v�Z */
	if(skill_num == ASC_BREAKER) {
		damage_sbr = status_get_int(src) * skill_lv * 5;	// ���@�_���[�W
		damage_sbr += 500 + (atn_rand() % 500);	// �����_���_���[�W
	}

	/* 25�D�J�[�h�ɂ��_���[�W�������� */
	if( target_sd && (wd.damage > 0 || wd.damage2 > 0 || damage_sbr > 0) ) {	// �Ώۂ�PC�̏ꍇ
		int s_race  = status_get_race(src);
		int s_enemy = status_get_enemy_type(src);
		int s_size  = status_get_size(src);
		int s_group = status_get_group(src);
		int ele_type= status_get_elem_type(src);
		cardfix = 100;
		cardfix = cardfix*(100-target_sd->subrace[s_race])/100;			// �푰�ɂ��_���[�W�ϐ�
		if (s_ele == ELE_NONE)
			cardfix = cardfix*(100-target_sd->subele[ELE_NEUTRAL])/100;	// ���������̑ϐ��͖�����
		else
			cardfix = cardfix*(100-target_sd->subele[s_ele])/100;		// �����ɂ��_���[�W�ϐ�
		if (ele_type == ELE_NONE)
			cardfix = cardfix*(100-target_sd->def_eleenemy[ELE_NEUTRAL])/100;	// ���������̑ϐ��͖�����
		else
			cardfix = cardfix*(100-target_sd->def_eleenemy[ele_type])/100;		// �G�����ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-target_sd->subenemy[s_enemy])/100;		// �G�^�C�v�ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-target_sd->subsize[s_size])/100;			// �T�C�Y�ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-target_sd->subgroup[s_group])/100;		// �O���[�v�ɂ��_���[�W�ϐ�

		if(status_get_mode(src) & MD_BOSS)
			cardfix = cardfix*(100-target_sd->subrace[RCT_BOSS])/100;	// �{�X����̍U���̓_���[�W����
		else
			cardfix = cardfix*(100-target_sd->subrace[RCT_NONBOSS])/100;	// �{�X�ȊO����̍U���̓_���[�W����

		// ����Class�p�␳��������(�����̓��L���{���S���p�H)
		for(i=0; i<target_sd->add_def_class_count; i++) {
			if(target_sd->add_def_classid[i] == status_get_class(src)) {
				cardfix = cardfix*(100-target_sd->add_def_classrate[i])/100;
				break;
			}
		}
		if(wd.flag&BF_LONG && !(src_md && (skill_num == AC_SHOWER || skill_num == SN_SHARPSHOOTING)) )
			cardfix = cardfix*(100-target_sd->long_attack_def_rate)/100;	// �������U���̓_���[�W����(�z����C�Ƃ�)
		if(wd.flag&BF_SHORT)
			cardfix = cardfix*(100-target_sd->near_attack_def_rate)/100;	// �ߋ����U���̓_���[�W����(�Y�������H)

		DMG_FIX( cardfix, 100 );	// �J�[�h�␳�ɂ��_���[�W����

		damage_sbr = damage_sbr * cardfix / 100;	// �J�[�h�␳�ɂ��\�E���u���C�J�[�̖��@�_���[�W����
	}
	// �G�E�J���X�e�B�J
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
				// �J�[�h���ʂɂ�����X�L���̃_���[�W�����i����X�L���j
				if(src_sd->skill_dmgup.count > 0) {
					for(i=0; i<src_sd->skill_dmgup.count; i++) {
						if(skill_num == src_sd->skill_dmgup.id[i]) {
							rate += src_sd->skill_dmgup.rate[i];
							break;
						}
					}
				}
				// �J�[�h���ʂɂ����葮���X�L���̃_���[�W�����i����X�L���j
				rate += src_sd->skill_eleweapon_dmgup[s_ele];
				// �z�[���[�N���X
				if(skill_num == CR_HOLYCROSS && src_sd->status.weapon == WT_2HSPEAR)
					rate += 100;
			}
			// �t�@�C�e�B���O
			if((skill = pc_checkskill(src_sd,TK_POWER)) > 0) {
				rate += skill * 20;
			}
		}
		if(sc) {
			// �������R���[
			if(sc->data[SC_GLOOMYDAY].timer != -1 && (skill_num == KN_BRANDISHSPEAR || skill_num == LK_SPIRALPIERCE || skill_num == CR_SHIELDCHARGE ||
			   skill_num == CR_SHIELDBOOMERANG || skill_num == PA_SHIELDCHAIN || skill_num == LG_SHIELDPRESS)) {
				rate += 75 + sc->data[SC_GLOOMYDAY].val1 * 25;
			}
		}
		wd.damage = wd.damage*rate/100;
	}

	if(wd.damage > 0) {
		switch (skill_num) {
		case MC_CARTREVOLUTION:	// �J�[�g���{�����[�V����
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
		case NPC_VENOMFOG:
		case NC_ARMSCANNON:
		case NC_SELFDESTRUCTION:
			wd.damage = wd.damage - (t_def1 + t_def2);
			break;
		case RA_WUGDASH:
			if(src_sd && (skill = pc_checkskill(src_sd,RA_TOOTHOFWUG)) > 0) {	// �g�D�[�X�I�u�E�H�[�O�ɂ��_���[�W����
				DMG_ADD( ((src_sd->weight / 10 * 5 / 4) + skill * 6) * 3 );
			}
			break;
		}
	}
#endif

	/* 26�D�A�C�e���{�[�i�X�̃t���O���� */
	if(src_sd && wd.flag&BF_WEAPON) {
		// ��Ԉُ�̃����W�t���O
		//   addeff_range_flag  0:�w�薳�� 1:�ߋ��� 2:������ 3,4:���ꂼ��̃����W�ŏ�Ԉُ�𔭓������Ȃ�
		//   flag������A�U���^�C�v��flag����v���Ȃ��Ƃ��́Aflag+2����

		for(i = 0; i < MAX_EFF_TYPE; i++) {
			if( (src_sd->addeff_range_flag[i] == 1 && wd.flag&BF_LONG ) ||
			    (src_sd->addeff_range_flag[i] == 2 && wd.flag&BF_SHORT) ) {
				src_sd->addeff_range_flag[i] += 2;
			}
		}
	}

	/* 27�D�ΏۂɃX�e�[�^�X�ُ킪����ꍇ�̃_���[�W���Z���� */
	if( t_sc && (wd.damage > 0 || wd.damage2 > 0) ) {
		cardfix = 100;
		if(t_sc->data[SC_DEFENDER].timer != -1 && wd.flag&BF_LONG && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID)	// �f�B�t�F���_�[��Ԃŉ������U��
			cardfix = cardfix*(100-t_sc->data[SC_DEFENDER].val2)/100;
		if(t_sc->data[SC_ADJUSTMENT].timer != -1 && wd.flag&BF_LONG)	// �A�W���X�g�����g��Ԃŉ������U��
			cardfix -= 20;
#ifdef PRE_RENEWAL
		if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && s_ele == ELE_POISON)		// �x�i���C���v���X
			cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
		if(t_sc->data[SC_ORATIO].timer != -1 && s_ele == ELE_HOLY)		// �I���e�B�I
			cardfix += t_sc->data[SC_ORATIO].val1;
		if(t_sc->data[SC_SOULCURSE].timer != -1 && s_ele == ELE_DARK)		// ����߈�
			cardfix += t_sc->data[SC_SOULCURSE].val2;
		if(t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 && s_ele == ELE_EARTH)		// ����
			cardfix += t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].val2;
		if(t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1 && s_ele == ELE_POISON)		// ����
			cardfix += t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].val2;
		// �N���C�}�b�N�X�N�G�C�N
		if(t_sc->data[SC_CLIMAX_EARTH].timer != -1 && s_ele == ELE_EARTH)
			cardfix += t_sc->data[SC_CLIMAX_EARTH].val2;
		// �N���C�}�b�N�X�u���[��
		if(t_sc->data[SC_CLIMAX_BLOOM].timer != -1 && s_ele == ELE_FIRE)
			cardfix += t_sc->data[SC_CLIMAX_BLOOM].val2;
		// �W���b�N�t���X�g�m���@
		if(t_sc->data[SC_MISTYFROST].timer != -1 && s_ele == ELE_WATER)
			cardfix += t_sc->data[SC_MISTYFROST].val2;
#endif
		if(t_sc->data[SC_DEEP_SLEEP].timer != -1)		// �����̎q��S
			cardfix += 50;
		if(cardfix != 100) {
			DMG_FIX( cardfix, 100 );	// �X�e�[�^�X�ُ�␳�ɂ��_���[�W����
		}
	}

	/* ���i�q�b�g�v�Z */
	switch(skill_num) {
	case AC_DOUBLE:		// �_�u���X�g���C�t�B���O
	case MA_DOUBLE:
	case KN_PIERCE:		// �s�A�[�X
	case ML_PIERCE:
	case MO_FINGEROFFENSIVE:	// �w�e
	case NPC_COMBOATTACK:	// ���i�U��
	case GS_TRIPLEACTION:	// �g���v���A�N�V����
#ifndef PRE_RENEWAL
	case LK_SPIRALPIERCE:	// �X�p�C�����s�A�[�X
	case PA_SHIELDCHAIN:	// �V�[���h�`�F�C��
#endif
	case NC_BOOSTKNUCKLE:	// �u�[�X�g�i�b�N��
	case NC_VULCANARM:		// �o���J���A�[��
	case NC_ARMSCANNON:		// �A�[���Y�L���m��
	case SC_FATALMENACE:	// �t�F�C�^�����i�X
	case LG_HESPERUSLIT:	// �w�X�y���X���b�g
	case SR_DRAGONCOMBO:	// �o���r
	case RL_QD_SHOT:		// �N�C�b�N�h���[�V���b�g
	case DK_SERVANTWEAPON_ATK:	// �T�[���@���g�E�F�|��(�U��)
	case DK_SERVANT_W_PHANTOM:	// �T�[���@���g�E�F�|���F�t�@���g��
	case DK_SERVANT_W_DEMOL:	// �T�[���@���g�E�F�|���F�f�����b�V����
	case DK_HACKANDSLASHER:		// �n�b�N�A���h�X���b�V���[
	case DK_HACKANDSLASHER_ATK:	// �n�b�N�A���h�X���b�V���[(�U��)
	case DK_STORMSLASH:		// �X�g�[���X���b�V��
	case IQ_THIRD_FLAME_BOMB:	// ��O���F�ŉΌ�
	case IQ_THIRD_CONSECRATION:	// ��O���F��
	case IG_OVERSLASH:		// �I�[�o�[�X���b�V��
	case SHC_SAVAGE_IMPACT:		// �T�x�[�W�C���p�N�g
	case SHC_ETERNAL_SLASH:		// �G�^�[�i���X���b�V��
	case SHC_IMPACT_CRATER:		// �C���p�N�g�N���[�^�[
	case MT_AXE_STOMP:		// �A�b�N�X�X�g���v
	case MH_SONIC_CRAW:		// �\�j�b�N�N���[
	case ABC_FRENZY_SHOT:	// �t�����W�V���b�g
	case BO_ACIDIFIED_ZONE_WATER:	// �A�V�f�B�t�@�C�h�]�[��(��)
	case BO_ACIDIFIED_ZONE_GROUND:	// �A�V�f�B�t�@�C�h�]�[��(�n)
	case BO_ACIDIFIED_ZONE_WIND:	// �A�V�f�B�t�@�C�h�]�[��(��)
	case BO_ACIDIFIED_ZONE_FIRE:	// �A�V�f�B�t�@�C�h�]�[��(��)
	case TR_RHYTHMSHOOTING:		// ���Y���V���[�e�B���O
	case NW_THE_VIGILANTE_AT_NIGHT:		// �r�W�����g�A�b�g�i�C�g
	case NW_SPIRAL_SHOOTING:	// �X�p�C�����V���[�e�B���O
	case NW_MAGAZINE_FOR_ONE:	// �}�K�W���t�H�[����
	case SH_HOGOGONG_STRIKE:	// �^�C�K�[�X�g���C�N
	case HN_DOUBLEBOWLINGBASH:	// �_�u���{�E�����O�o�b�V��
 	case SKE_ALL_IN_THE_SKY:	// �V������
	case MT_TRIPLE_LASER:		// �g���v�����[�U�[
		// Hit�����C���������^�C�v
		if(wd.div_ > 1)
			wd.damage *= wd.div_;
		break;
	case AS_SONICBLOW:		// �\�j�b�N�u���[
	case CR_HOLYCROSS:		// �z�[���[�N���X
	case MO_CHAINCOMBO:		// �A�ŏ�
	case CH_CHAINCRUSH:		// �A������
	case CG_ARROWVULCAN:	// �A���[�o���J��
	case RK_HUNDREDSPEAR:	// �n���h���b�h�X�s�A
	case GC_CROSSIMPACT:	// �N���X�C���p�N�g
	case GC_DARKCROW:		// �_�[�N�N���[
	case RA_ARROWSTORM:		// �A���[�X�g�[��
	case NC_AXETORNADO:		// �A�b�N�X�g���l�[�h
	case SC_TRIANGLESHOT:	// �g���C�A���O���V���b�g
	case LG_EARTHDRIVE:		// �A�[�X�h���C�u
	case SR_SKYNETBLOW:		// �V���n��
	case SR_FALLENEMPIRE:	// ��Z���x
	case NPC_ARROWSTORM:	// M�A���[�X�g�[��
		// 1Hit�𕪊����ĕ\������X�L��
		break;
	}

	if(wd.damage  < 0) wd.damage  = 0;
	if(wd.damage2 < 0) wd.damage2 = 0;

#ifdef PRE_RENEWAL
	/* 28�D�����̓K�p */
	wd.damage = battle_attr_fix(wd.damage, s_ele, status_get_element(target));
	if(calc_flag.lh)
		wd.damage2 = battle_attr_fix(wd.damage2, s_ele_, status_get_element(target));

	/* 29�D�X�L���C���S�i�ǉ��_���[�W�j */
	if(sc && sc->data[SC_MAGNUM].timer != -1) {	// �}�O�i���u���C�N���
		int bonus_damage = BIGNUM2INT(battle_attr_fix(wd.damage, ELE_FIRE, status_get_element(target)) * 20/100);	// �Α����U���_���[�W��20%��ǉ�
		if(bonus_damage > 0) {
			DMG_ADD( bonus_damage );
		}
	}
	if(skill_num == ASC_BREAKER) {			// �\�E���u���C�J�[
		wd.damage += damage_sbr;	// ���@�_���[�W�ƃ����_���_���[�W�����Z
		if(t_def1 < 1000000) {
			int vitbonusmax = (t_vit/20)*(t_vit/20)-1;
			wd.damage -= (t_def1 + t_def2 + ((vitbonusmax < 1)? 0: atn_rand()%(vitbonusmax+1)) + status_get_mdef(target) + status_get_mdef2(target))/2;
		}
	}
#endif
	if(sc) {
#ifndef PRE_RENEWAL
		// �}�W�J���o���b�g
		if(sc->data[SC_MAGICALBULLET].timer != -1 && !skill_num ) {
			static struct Damage ebd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			ebd = battle_calc_attack(BF_MAGIC,src,target,GS_MAGICALBULLET,sc->data[SC_MAGICALBULLET].val1,wd.flag);
			wd.damage += ebd.damage;
		}
		// �G���`�����g�u���C�h
		if(sc->data[SC_ENCHANTBLADE].timer != -1 && wd.damage > 0 && (!skill_num || skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP) ) {
			static struct Damage ebd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			ebd = battle_calc_attack(BF_MAGIC,src,target,RK_ENCHANTBLADE,sc->data[SC_ENCHANTBLADE].val1,wd.flag);
			wd.damage += ebd.damage + ((100 + sc->data[SC_ENCHANTBLADE].val1 * 20) * status_get_lv(src) / 150);
		}
		// �N���b�V���X�g���C�N
		if(sc->data[SC_CRUSHSTRIKE].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
			if(src_sd) {
				int idx = src_sd->equip_index[EQUIP_INDEX_RARM];
				if(idx >= 0 && src_sd->inventory_data[idx]) {
					wd.damage *= (6 + src_sd->status.inventory[idx].refine) * src_sd->inventory_data[idx]->wlv + (itemdb_atk(src_sd->inventory_data[idx]->nameid) + src_sd->inventory_data[idx]->weight/10) / 100;
				}

				if(atn_rand() % 100 < 20) {	// 20%�̊m���ŕ���j��
					pc_break_equip(src_sd, LOC_RARM);
				}
			}
			status_change_end(src, SC_CRUSHSTRIKE,-1);
		}
		// �W���C�A���g�O���[�X
		else if(sc->data[SC_GIANTGROWTH].timer != -1 && wd.flag&BF_SHORT && !skill_num) {
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
		// �X�y���t�B�X�g
		if(sc->data[SC_SPELLFIST].timer != -1 && !skill_num) {
			wd = battle_calc_attack(BF_MAGIC,src,target,sc->data[SC_SPELLFIST].val2,1,wd.flag);
			wd.damage = wd.damage * (((sc->data[SC_SPELLFIST].val1 > 5)? (sc->data[SC_SPELLFIST].val1-5)*3+5: sc->data[SC_SPELLFIST].val1) + sc->data[SC_SPELLFIST].val3);
			if((--sc->data[SC_SPELLFIST].val4) <= 0)
				status_change_end(src, SC_SPELLFIST,-1);
		}
	}

	/* 30�D�K���_���[�W�̉��Z */
	switch(skill_num) {
#ifdef PRE_RENEWAL
	case NJ_SYURIKEN:	// �藠������
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
	case LG_SHIELDPRESS:	// �V�[���h�v���X
		if(src_sd) {
			if(src_sd->equip_index[EQUIP_INDEX_LARM] >= 0) {
				int idx = src_sd->equip_index[EQUIP_INDEX_LARM];
				if(src_sd->inventory_data[idx] && itemdb_isarmor(src_sd->inventory_data[idx]->nameid)) {
					DMG_ADD( src_sd->status.inventory[idx].refine * status_get_vit(src) );
				}
			}
		}
		break;
	case SR_FALLENEMPIRE:	// ��Z���x
		if(target_sd) {
			DMG_ADD( status_get_str(src) * (status_get_size(target)*2+1 + skill_lv ) + status_get_dex(src) * target_sd->weight/10 / 120 );		// ��PC
		} else {
			DMG_ADD( status_get_str(src) * (status_get_size(target)*2+1 + skill_lv ) + status_get_dex(src) * status_get_lv(target) * 50 / 120 );		// ��MOB
		}
		break;
	case SR_TIGERCANNON:	// �j�C
		if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
			DMG_ADD( status_get_lv(target) * 40 + skill_lv * 500 );			// �R���{������
		} else {
			DMG_ADD( status_get_lv(target) * 40 + skill_lv * 240 );			// �ʏ펞
		}
		break;
	case SR_GATEOFHELL:	// �����j����
		if(src_sd) {
			int sp = 0;
			if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
				// �R���{������
				sp = (int)((atn_bignumber)status_get_max_sp(src) * skill_lv / 100);
				DMG_ADD( status_get_max_sp(src) * ( 100 + 20 * skill_lv ) / 100 + status_get_lv(src) * 20 + status_get_max_hp(src) - status_get_hp(src) );
			} else {
				// �ʏ펞
				sp = (int)((atn_bignumber)status_get_max_sp(src) * (10 + skill_lv) / 100);
				DMG_ADD( ( status_get_sp(src) - sp ) * ( 100 + 20 * skill_lv ) / 100 + status_get_lv(src) * 10 + status_get_max_hp(src) - status_get_hp(src) );
			}
			// SP����
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
		// ���̂�����A�C���̓K�p
		int hit_bonus  = src_sd->spiritball.num * 3 + src_sd->coin.num * 3 + src_sd->bonus_damage;
		int hit_damage = hit_bonus + src_sd->star + src_sd->ranker_weapon_bonus;

		if(skill_num == NJ_KUNAI) {	// �ꖳ����
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
	/* �iRE�j�N���e�B�J�� */
	if(calc_flag.critical == 2)
		wd.damage = wd.damage * (140 + status_get_crate(src)) / 100;
#endif

	/* 31�D�K���Œ�_���[�W */
	if(src_sd && src_sd->special_state.fix_damage)
		DMG_SET( src_sd->fix_damage );

	/* 32�D����_���[�W�̕␳ */
	if(calc_flag.rh == 0 && calc_flag.lh == 1) {	// ����̂ݕ��푕��
		wd.damage = wd.damage2;
		wd.damage2 = 0;
		// �ꉞ���E�����ւ��Ă���
		calc_flag.rh = 1;
		calc_flag.lh = 0;
	} else if(src_sd && calc_flag.lh && src_sd->status.weapon != WT_KATAR) {		// ���肪����Ȃ�E��E����C���̓K�p
		atn_bignumber dmg = wd.damage, dmg2 = wd.damage2;
		// �e�T�E�O�̏ꍇ
		if(src_sd->s_class.job == PC_JOB_KG || src_sd->s_class.job == PC_JOB_OB) {
			// �E��C��(80% �` 120%) �E��S��
			skill = pc_checkskill(src_sd,KO_RIGHT);
			wd.damage = wd.damage * (70 + (skill * 10))/100;
			// ����C��(60% �` 100%) ����S��
			skill = pc_checkskill(src_sd,KO_LEFT);
			wd.damage2 = wd.damage2 * (50 + (skill * 10))/100;
		} else {
			// �E��C��(60% �` 100%) �E��S��
			skill = pc_checkskill(src_sd,AS_RIGHT);
			wd.damage = wd.damage * (50 + (skill * 10))/100;
			// ����C��(40% �` 80%) ����S��
			skill = pc_checkskill(src_sd,AS_LEFT);
			wd.damage2 = wd.damage2 * (30 + (skill * 10))/100;
		}
		if(dmg > 0 && wd.damage < 1) wd.damage = 1;
		if(dmg2 > 0 && wd.damage2 < 1) wd.damage2 = 1;
	} else {
		wd.damage2 = 0;	// �O�̂���0�𖾎����Ă���
	}

	// �t�B�A�[�u���[�Y�A������
	if(skill_num == 0 && skill_lv >= 0 && sc && sc->data[SC_FEARBREEZE].timer != -1) {
		int div_ = 0;
		int rate = atn_rand()%100;

		if(rate < 20)	// Lv1~2:2Hit�m��20%
			div_ = 2;
		else if(sc->data[SC_FEARBREEZE].val1 >= 3 && rate >= 20 && rate < 35)	// Lv3:3Hit�m��15%
			div_ = 3;
		else if(sc->data[SC_FEARBREEZE].val1 >= 4 && rate >= 35 && rate < 45)	// Lv4:4Hit�m��10%
			div_ = 4;
		else if(sc->data[SC_FEARBREEZE].val1 >= 5 && rate >= 45 && rate < 50)	// Lv5:5Hit�m��=5%
			div_ = 5;

		if(div_ > 0){
			if(src_sd && !battle_delarrow(src_sd,div_ - 1,0))	// �����`�F�b�N
				div_ = 0;
			else{
				if(wd.type == 0x0a)		// �N���e�B�J���U���̏ꍇ�͘A���N���e�B�J���\��
					wd.type = 0x0d;
				else
					wd.type = 0x08;
				wd.div_ = div_;
				wd.damage *= div_;
			}
		}
	}
	/* �A���_���[�W�v�Z */
	else if(calc_flag.da > 0) {
		if(wd.type == 0x0a)		// �N���e�B�J���U���̏ꍇ�͘A���N���e�B�J���\��
			wd.type = 0x0d;
		else
			wd.type = 0x08;
		wd.div_ = 2;
		wd.damage += wd.damage;
	}

	/* 33�D�X�L���C���T�i�ǉ��_���[�W�Q�j */
	if(src_sd && src_sd->status.weapon == WT_KATAR && skill_num != ASC_BREAKER && skill_lv >= 0) {
#ifdef PRE_RENEWAL
		// �J�^�[������
		if((skill = pc_checkskill(src_sd,ASC_KATAR)) > 0) {
			wd.damage += wd.damage*(10+(skill * 2))/100;
		}
#endif
		// �J�^�[���ǌ��_���[�W
		skill = pc_checkskill(src_sd,TF_DOUBLE);
		wd.damage2 = wd.damage * (1 + (skill * 2))/100;
		if(wd.damage > 0 && wd.damage2 < 1)
			wd.damage2 = 1;
	}
#ifndef PRE_RENEWAL
	// �\�j�b�N�A�N�Z�����[�V����
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
	case NPC_CRITICALSLASH:
	case AM_ACIDTERROR:
	case MO_EXTREMITYFIST:
	case CR_ACIDDEMONSTRATION:
	case GN_FIRE_EXPANSION_ACID:
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
	case MH_EQC:
		wd.damage = battle_attr_fix(wd.damage, ELE_NEUTRAL, status_get_element(target) );
		break;
	}

	/* 34�D���S����̔��� */
	if(skill_num == 0 && skill_lv >= 0 && target_sd != NULL && wd.div_ < 255 && atn_rand()%1000 < status_get_flee2(target) ) {
		wd.damage  = 0;
		wd.damage2 = 0;
		wd.type    = 0x0b;
		wd.dmg_lv  = ATK_LUCKY;
	}

	if (target_md != NULL && (battle_config.enemy_perfect_flee || mobdb_search(target_md->class_)->mode_opt[MDOPT_PERFECT_FREE]))	// �Ώۂ����S���������ݒ肪ON�Ȃ�
	{
		if(skill_num == 0 && skill_lv >= 0 && wd.div_ < 255 && atn_rand()%1000 < status_get_flee2(target) )
		{
			wd.damage  = 0;
			wd.damage2 = 0;
			wd.type    = 0x0b;
			wd.dmg_lv  = ATK_LUCKY;
		}
	}

	/* 35�D�Œ�_���[�W2 */
	if(t_mode&MD_PLANT) {	// Mob��Mode�Ɋ拭�t���O�������Ă���Ƃ��̏���
		if(wd.damage > 0)
			wd.damage = 1;
		if(wd.damage2 > 0)
			wd.damage2 = 1;
		if(skill_num == MO_TRIPLEATTACK) {	// �O�i��
			wd.damage *= wd.div_;
			wd.damage2 *= wd.div_;
		}
	}

	if( target_sd && target_sd->special_state.no_weapon_damage && skill_num != CR_GRANDCROSS && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP &&
	    skill_num != NPC_GRANDDARKNESS) {
		// bNoWeaponDamage�ŃO�����h�N���X����Ȃ��ꍇ�̓_���[�W��0
		wd.damage = wd.damage2 = 0;
	}

	/* 36�D�_���[�W�ŏI�v�Z */
	if(skill_num != CR_GRANDCROSS && skill_num != NPC_GRANDDARKNESS && skill_num != NPC_EARTHQUAKE && skill_num != RA_CLUSTERBOMB && skill_num != RA_FIRINGTRAP && skill_num != RA_ICEBOUNDTRAP) {
		if(wd.damage2 < 1) {		// �_���[�W�ŏI�C��
			wd.damage  = battle_calc_damage(src,target,wd.damage,wd.div_,skill_num,skill_lv,wd.flag);
		} else if(wd.damage < 1) {	// �E�肪�~�X�H
			wd.damage2 = battle_calc_damage(src,target,wd.damage2,wd.div_,skill_num,skill_lv,wd.flag);
		} else {			// ����A�J�^�[���̏ꍇ�͂�����ƌv�Z��₱����
			atn_bignumber dmg = wd.damage+wd.damage2;
			wd.damage  = battle_calc_damage(src,target,dmg,wd.div_,skill_num,skill_lv,wd.flag);
			wd.damage2 = (int)((wd.damage2*100/(float)dmg)*wd.damage/100);
			if(wd.damage > 1 && wd.damage2 < 1) wd.damage2 = 1;
			wd.damage -= wd.damage2;
		}
	}
	/* 37. �_�� -��-�ɂ��C�e�̐��� */
	if(src_sd && sc && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && (wd.damage > 0 || wd.damage2 > 0)) {
		int max = (src_sd->s_class.job == PC_JOB_MO || src_sd->s_class.job == PC_JOB_SR)? pc_checkskill(src_sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
		if(sc->data[SC_RAISINGDRAGON].timer != -1)
			max += sc->data[SC_RAISINGDRAGON].val1;
		if(src_sd->spiritball.num < max)
			pc_addspiritball(src_sd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
	}
	// �}�O�}�t���[
	if(t_sc && t_sc->data[SC_MAGMA_FLOW].timer != -1 && atn_rand()%100 < t_sc->data[SC_MAGMA_FLOW].val2 && (wd.damage > 0 || wd.damage2 > 0)) {
		skill_castend_damage_id(target, target, MH_MAGMA_FLOW, t_sc->data[SC_MAGMA_FLOW].val1, gettick(), 0);
	}
	// �p�C���N���X�e�B�b�N
	if(sc && sc->data[SC_PYROCLASTIC].timer != -1 && atn_rand()%100 < sc->data[SC_PYROCLASTIC].val3 && (wd.damage > 0 || wd.damage2 > 0)) {
		skill_castend_pos2(src,target->x,target->y,BS_HAMMERFALL,sc->data[SC_PYROCLASTIC].val1,gettick(),0);
	}

	/* 38�D�����U���X�L���ɂ��I�[�g�X�y������(item_bonus) */
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

		// �A�N�e�B�u�A�C�e���͕����U���X�L���ł���������
		bonus_activeitem_start(src_sd,asflag+EAS_NORMAL,tick);

		// weapon_attack_autospell�������ł��A�Z����Ԃł���΃I�[�g�X�y������������
		if(battle_config.weapon_attack_autospell || (sc && sc->data[SC_FUSION].timer != -1))
			asflag += EAS_NORMAL;
		else
			asflag += EAS_SKILL;

		bonus_autospell_start(&src_sd->bl,target,asflag,tick,0);
	}

	/* 39�D���z�ƌ��Ɛ��̗Z�� HP2%���� */
	if(src_sd && sc && sc->data[SC_FUSION].timer != -1)
	{
		int hp;
		if(src_sd->status.hp < src_sd->status.max_hp * 20 / 100)	// HP��20�������̎��ɍU��������Α���
			hp = src_sd->status.hp;
		else if(target->type == BL_PC)
			hp = src_sd->status.max_hp * 8 / 100;
		else
			hp = src_sd->status.max_hp * 2 / 100;

		pc_heal(src_sd,-hp,0,0,0);
	}

	/* 40�D�J�A�q */
	if(skill_num == 0 && wd.flag&BF_WEAPON && t_sc && t_sc->data[SC_KAAHI].timer != -1)
	{
		int kaahi_lv = t_sc->data[SC_KAAHI].val1;
		if(status_get_hp(target) < status_get_max_hp(target))
		{
			if(target->type == BL_MOB || status_get_sp(target) >= 5*kaahi_lv)	// �Ώۂ�mob�ȊO��SP�������ʈȉ��̂Ƃ��͔������Ȃ�
			{
				int heal = skill_fix_heal(src, target, SL_KAAHI, 200 * kaahi_lv);
				unit_heal(target,heal,-5*kaahi_lv,0,1);
			}
		}
	}

	/* 41�D���z�ƌ��Ɛ��̊�� */
	if(src_sd && wd.flag&BF_WEAPON && src_sd->s_class.job == PC_JOB_SG && atn_rand()%10000 < battle_config.sg_miracle_rate)
		status_change_start(src,SC_MIRACLE,1,0,0,0,3600000,0);

	/* 42�D�v�Z���ʂ̍ŏI�␳ */
	if(!calc_flag.lh)
		wd.damage2 = 0;
	wd.amotion = status_get_amotion(src);
	if(skill_num == KN_AUTOCOUNTER)
		wd.amotion >>= 1;
	wd.dmotion = status_get_dmotion(target);

	return wd;
}

/*==========================================
 * ��{����_���[�W�v�Z
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

	matk1 = status_get_matk1(src);	// pre:�ő�Matk, RE:����Matk
	matk2 = status_get_matk2(src);	// pre:�Œ�Matk, RE:�X�e�[�^�XMatk

	sc = status_get_sc(src);

#ifndef PRE_RENEWAL
	if(src->type == BL_PC)
		sd = (struct map_session_data *)src;

	if(sd) {
		short wlv = 0;
		int cost  = 0;
		int int_  = status_get_int(src);
		int dex   = status_get_dex(src);
		int idx   = sd->equip_index[EQUIP_INDEX_RARM];

		damage = matk2;		// �X�e�[�^�XMatk���m��

		// ���킪����Ȃ畐��Lv�ƃR�X�g�v�Z
		if(idx >= 0 && sd->inventory_data[idx]) {
			wlv  = sd->inventory_data[idx]->wlv;
			cost = matk1*2/3 - (int_/5)*(int_/5)/wlv;
			if(cost < 0)	// �R�X�g��0�ȉ��ɂȂ�Ȃ�
				cost = 0;
		}
		// �ő啐��Matk�ƍŒᕐ��Matk�v�Z
		matk2 = (matk1 * 5 + dex * (12+2*wlv))/15 - cost;
		matk1 = matk1 * (100+10*wlv)/100 - cost;
		if(matk2 > matk1)
			matk2 = matk1;
	}
#endif

	// ���R�O�i�C�Y�h�X�y��
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
	// �X�e�[�^�XMatk+����Matk�v�Z
	if(matk1 > matk2)
		damage += matk2+atn_rand()%(matk1-matk2+1);
	else
		damage += matk2;
	// �ߏ萸�B�̌v�Z
	if(sd && sd->overrefine)
		damage += (atn_rand()%sd->overrefine)+1;
#endif

	if(sc) {
		// ���@�͑���
		if(sc->data[SC_MAGICPOWER].timer != -1)
			damage += damage * (sc->data[SC_MAGICPOWER].val1 * 5) / 100;
		// ��������̃Z���i�[�f
		if(sc->data[SC_MOONLIT_SERENADE].timer != -1)
			damage += sc->data[SC_MOONLIT_SERENADE].val4;
	}

	return ((damage>0)?damage:1);
}

#define MATK_FIX( a,b ) { mgd.damage = mgd.damage*(a+(add_rate*b/100))/(b); }

/*==========================================
 * ���@�_���[�W�v�Z
 *------------------------------------------
 */
static struct Damage battle_calc_magic_attack(struct block_list *bl,struct block_list *target,int skill_num,int skill_lv,int flag)
{
	struct Damage mgd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change    *sc = NULL, *t_sc = NULL;
	int ele, race;
	int mdef1, mdef2, mres, t_ele, t_race, t_group, t_enemy, t_size, t_mode;
	int t_class, cardfix, i;
	int normalmagic_flag = 1;
	int add_rate = 0;
#ifndef PRE_RENEWAL
	atn_bignumber heal;
#endif

	// return�O�̏���������̂ŏ��o�͕��̂ݕύX
	if( bl == NULL || target == NULL || target->type == BL_PET ) {
		nullpo_info(NLP_MARK);
		return mgd;
	}

	sd   = BL_DOWNCAST( BL_PC, bl );
	tsd  = BL_DOWNCAST( BL_PC, target );

	// �A�^�b�J�[
	ele  = skill_get_pl(skill_num);
	race = status_get_race(bl);
	sc   = status_get_sc(bl);

	// �^�[�Q�b�g
	mdef1   = status_get_mdef(target);
	mdef2   = status_get_mdef2(target);
	mres    = status_get_mres(target);
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

	// �L���O�X�O���C�X
	if(t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return mgd;

	/* �P�Dmgd�\���̂̏����ݒ� */
	mgd.div_      = skill_get_num(skill_num,skill_lv);
	mgd.blewcount = skill_get_blewcount(skill_num,skill_lv);
	mgd.flag      = BF_MAGIC|BF_LONG|BF_SKILL;

	// �������狗���ɂ�锻��
	switch(skill_get_range_type(skill_num)) {
		case 0:	// �ߋ���
		case 2: // ����������
			break;
		case 1:	// �ʏ퉓����
			if(battle_config.calc_dist_flag & 2) {	// ���@�̎��v�Z���邩�H +2�Ōv�Z����
				int target_dist = unit_distance(bl,target);	// �������擾
				if(target_dist < battle_config.allow_sw_dist) {	// SW�Ŗh���鋗����菬�������ߋ�������̍U��
					if(bl->type == BL_PC && battle_config.sw_def_type & 1) {	// �l�Ԃ���̂𔻒肷�邩 +1�ł���
						mgd.flag = (mgd.flag&~BF_RANGEMASK)|BF_SHORT;
						break;
					} else if(bl->type == BL_MOB && battle_config.sw_def_type & 2) {	// �����X�^�[����̖��@�𔻒肷�邩 +2�ł���
						mgd.flag = (mgd.flag&~BF_RANGEMASK)|BF_SHORT;
						break;
					}
				}
			}
			break;
	}

	/* �Q�D���@�U����b�v�Z */
	mgd.damage = battle_calc_base_magic_damage(bl);

#ifndef PRE_RENEWAL
	// �q�[���̌v�Z�p�Ɋm��
	heal = mgd.damage;

	if(sd) {
		mgd.damage += sd->plus_matk;
		// �iRE�jMATK��Z����(��␳�ȊO)
		if(sd->matk_rate != 100)
			MATK_FIX( sd->matk_rate, 100 );
		if(pc_checkskill(sd, SU_POWEROFLAND) > 0 && pc_checkskill_summoner(sd, SU_POWEROFLAND) >= 20)
			MATK_FIX( 110, 100 );
	}

	// �t�@�C�A�[�s���[
	if(skill_num == WZ_FIREPILLAR) {
		if(bl->type == BL_MOB) {
			MATK_FIX( 200+100*skill_lv, 100 );
		} else {
			MATK_FIX( 40+20*skill_lv, 100 );
		}
		mgd.damage += 100+50*skill_lv;
	}

	/* �iRE�j�J�[�h�ɂ��_���[�W�ǉ����� */
	if(sd && mgd.damage > 0) {
		cardfix = 100;
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

	/* �X�L���{���v�Z�ɉ��Z */
	if(sc) {
#ifndef PRE_RENEWAL
		if(sc->data[SC_MINDBREAKER].timer != -1) {
			add_rate += 20*sc->data[SC_MINDBREAKER].val1;
		}
#endif
	}
	// �h���S�m���W�[
	if(sd && t_race == RCT_DRAGON && pc_checkskill(sd,SA_DRAGONOLOGY) > 0)
		add_rate += pc_checkskill(sd,SA_DRAGONOLOGY)*2;

	/* �R�D��{�_���[�W�v�Z(�X�L�����Ƃɏ���) */
	switch(skill_num)
	{
		case AL_HEAL:	// �q�[��or����
		case PR_BENEDICTIO:
#ifdef PRE_RENEWAL
			mgd.damage = skill_calc_heal(bl,skill_lv)/2;
#else
			mgd.damage = skill_calc_heal(bl,skill_lv);
#endif
			if(sd) {	// ������ʂ��悹��
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
			mgd.damage += heal;	// Matk�̉��Z
			mgd.damage = mgd.damage / 2;
#endif
			normalmagic_flag = 0;
			break;
		case PR_ASPERSIO:		// �A�X�y���V�I
			mgd.damage = 40;	// �Œ�_���[�W
			normalmagic_flag = 0;
			break;
		case PR_SANCTUARY:	// �T���N�`���A��
			ele = ELE_HOLY;
			mgd.damage = (skill_lv > 6)? 388: 50*skill_lv;
#ifndef PRE_RENEWAL
			if(sd && sd->skill_dmgup.count > 0) {	// ������ʂ��悹��
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
		case PA_GOSPEL:		// �S�X�y��(�����_���_���[�W����̏ꍇ)
			mgd.damage = 1000+atn_rand()%9000;
			normalmagic_flag = 0;
			break;
		case ALL_RESURRECTION:
		case PR_TURNUNDEAD:	// �U�����U���N�V�����ƃ^�[���A���f�b�h
			if(battle_check_undead(t_race,t_ele)) {
				int hp, mhp, thres;
				hp = status_get_hp(target);
				mhp = status_get_max_hp(target);
				thres = skill_lv * 20 + status_get_luk(bl) + status_get_int(bl) + status_get_lv(bl) + 200 - (hp * 200 / mhp);
				if(thres > 700)
					thres = 700;
				if(atn_rand()%1000 < thres && !(t_mode&MD_BOSS))	// ����
					mgd.damage = hp;
				else					// ���s
					mgd.damage = status_get_lv(bl) + status_get_int(bl) + skill_lv * 10;
			}
			normalmagic_flag = 0;
			break;
		case AL_INCAGI:			/* ���x���� */
		case MER_INCAGI:
		case AL_BLESSING:		/* �u���b�V���O */
		case MER_BLESSING:
			mgd.damage = 1;
			normalmagic_flag = 0;
			break;

		case HW_NAPALMVULCAN:	// �i�p�[���o���J��
		case MG_NAPALMBEAT:	// �i�p�[���r�[�g�i���U�v�Z���݁j
			MATK_FIX( 70+10*skill_lv, 100 );
			if(flag > 0) {
				MATK_FIX( 1, flag );
			} else {
				if(battle_config.error_log)
					printf("battle_calc_magic_attack: NAPALM enemy count=0 !\n");
			}
			break;
		case MG_SOULSTRIKE:			// �\�E���X�g���C�N�i�΃A���f�b�h�_���[�W�␳�j
			if(battle_check_undead(t_race,t_ele))
				MATK_FIX( 20+skill_lv, 20 );	// MATK�ɕ␳����ʖڂł����ˁH
			break;
		case MG_COLDBOLT:	// �R�[���h�{���g
			if(sc && sc->data[SC_AQUAPLAY].timer != -1) {
				MATK_FIX( 100+sc->data[SC_AQUAPLAY].val3, 100 );
			}
			break;
		case MG_FROSTDIVER:	// �t���X�g�_�C�o�[
			if(sc && sc->data[SC_AQUAPLAY].timer != -1) {
				MATK_FIX( 100+10*skill_lv+sc->data[SC_AQUAPLAY].val3, 100 );
			} else {
				MATK_FIX( 100+10*skill_lv, 100 );
			}
			break;
		case MG_FIREBALL:	// �t�@�C�A�[�{�[��
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
		case MG_FIREWALL:	// �t�@�C�A�[�E�H�[��
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
		case MG_FIREBOLT:	// �t�@�C�A�[�{���g
			if(sc && sc->data[SC_PYROTECHNIC].timer != -1) {
				MATK_FIX( 100+sc->data[SC_PYROTECHNIC].val3, 100 );
			}
			break;
		case MG_LIGHTNINGBOLT:	// ���C�g�j���O�{���g
			if(sc && sc->data[SC_GUST].timer != -1) {
				MATK_FIX( 100+sc->data[SC_GUST].val3, 100 );
			}
			break;
		case MG_THUNDERSTORM:	// �T���_�[�X�g�[��
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
		case WZ_FROSTNOVA:	// �t���X�g�m���@
#ifdef PRE_RENEWAL
			MATK_FIX( 200+20*skill_lv, 300 );
#else
			MATK_FIX( 100+10*skill_lv, 100 );
#endif
			break;
#ifdef PRE_RENEWAL
		case WZ_FIREPILLAR:	// �t�@�C�A�[�s���[
			if(mdef1 < 1000000)
				mdef1 = mdef2 = 0;	// MDEF����
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
		case NPC_DARKTHUNDER:	// �_�[�N�T���_�[
			break;
		case WZ_JUPITEL:	// ���s�e���T���_�[
			if(bl->type == BL_MOB && battle_config.monster_skill_over && skill_lv >= battle_config.monster_skill_over) {
				mgd.div_ = 30;
				mgd.blewcount = 14;
			}
			break;
		case WZ_VERMILION:	// ���[�h�I�u���@�[�~���I��
#ifdef PRE_RENEWAL
			MATK_FIX( 80+20*skill_lv, 100 );
#else
			MATK_FIX( 100+((skill_lv-1)*25)*skill_lv/10+(skill_lv >= 10? 5: 0), 100 );
#endif
			break;
		case WZ_WATERBALL:	// �E�H�[�^�[�{�[��
			MATK_FIX( 100+30*skill_lv, 100 );
			break;
		case WZ_STORMGUST:	// �X�g�[���K�X�g
#ifdef PRE_RENEWAL
			MATK_FIX( 100+40*skill_lv, 100 );
#else
			MATK_FIX( 70+50*skill_lv, 100 );
#endif
			//mgd.blewcount |= SAB_REVERSEBLOW;
			break;
		case WZ_EARTHSPIKE:	// �A�[�X�X�p�C�N
			if(sc && sc->data[SC_PETROLOGY].timer != -1) {
				MATK_FIX( 100+sc->data[SC_PETROLOGY].val3, 100 );
			}
			break;
		case WZ_HEAVENDRIVE:	// �w�����Y�h���C�u
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
		case AL_HOLYLIGHT:	// �z�[���[���C�g
			MATK_FIX( 125, 100 );
			if(sc && sc->data[SC_PRIEST].timer != -1) {
				MATK_FIX( 500, 100 );
			}
			break;
		case AL_RUWACH:
			MATK_FIX( 145, 100 );
			break;
#ifndef PRE_RENEWAL
		case CR_GRANDCROSS:	// �O�����h�N���X
		case NPC_GRANDDARKNESS:
			{
				static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
				if(bl == target)
					mgd.damage /= 2;	// �����͔���
				mgd.damage = (mgd.damage + wd.damage) / 2 * (100 + 40*skill_lv)/100;
				mgd.damage = mgd.damage - (mdef1 + mdef2 + status_get_def(target) + status_get_def2(target));
				if(bl == target) {
					if(bl->type & (BL_MOB | BL_HOM | BL_MERC | BL_ELEM))
						mgd.damage = 0;		// MOB,HOM,MERC,ELEM���g���ꍇ�͔�������
				} else {
//					if(battle_config.gx_dupele)
						mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));	// ����2�񂩂���
					if(sd)
						mgd.damage = mgd.damage * (100+sd->long_weapon_damege_rate) / 100;
				}
				normalmagic_flag = 0;
			}
			break;
		case AM_DEMONSTRATION:	// �f�����X�g���[�V����
		case AM_ACIDTERROR:	// �A�V�b�h�e���[
		case ASC_BREAKER:	// �\�E���u���C�J�[
		case CR_ACIDDEMONSTRATION:	// �A�V�b�h�f�����X�g���[�V����
		case GN_FIRE_EXPANSION_ACID:	// �t�@�C�A�[�G�N�X�p���V����(���_)
			ele = ELE_NONE;
			normalmagic_flag = 0;
			break;
#endif
		case SL_STIN:	// �G�X�e�B��
			if(status_get_size(target) == 0) {
				MATK_FIX( 10*skill_lv, 100 );
			} else {
				MATK_FIX( skill_lv, 100 );
			}
			if(skill_lv >= 7)
				status_change_start(bl,SC_SMA,skill_lv,0,0,0,3000,0);
			break;
		case SL_STUN:	// �G�X�^��
			MATK_FIX( 5*skill_lv, 100 );
			ele = status_get_attack_element(bl);
			if(skill_lv >= 7)
				status_change_start(bl,SC_SMA,skill_lv,0,0,0,3000,0);
			break;
		case SL_SMA:	// �G�X�}
			MATK_FIX( 40+status_get_lv(bl), 100 );
			ele = status_get_attack_element_nw(bl);
			if(sc && sc->data[SC_SMA].timer != -1)
				status_change_end(bl,SC_SMA,-1);
			break;
		case NJ_KOUENKA:	// �g����
			{
				int rate = 90;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 20;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_KAENSIN:	// �Ή��w
			{
				int rate = 50;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 20;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_HUUJIN:		// ���n
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
		case NJ_HYOUSENSOU:	// �X�M��
			{
				int rate = 70;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WATER)
					rate += sd->elementball.num * 20;
				if(t_sc && t_sc->data[SC_SUITON].timer != -1)
					rate += 2 * t_sc->data[SC_SUITON].val1;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_BAKUENRYU:	// �����w
			{
				int rate = 150 + 150 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_FIRE)
					rate += sd->elementball.num * 100;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_HYOUSYOURAKU:	// �X������
			{
#ifdef PRE_RENEWAL
				int rate = 100 + 50 * skill_lv;
#else
				int rate = 150 + 150 * skill_lv;
#endif
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WATER)
					rate += sd->elementball.num * 100;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_RAIGEKISAI:	// ������
			{
#ifdef PRE_RENEWAL
				int rate = 160 + 40 * skill_lv;
#else
				int rate = 100 + 100 * skill_lv;
#endif
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WIND)
					rate += sd->elementball.num * 20;
				MATK_FIX( rate, 100 );
			}
			break;
		case NJ_KAMAITACHI:	// ��
			{
				int rate = 100 + 100 * skill_lv;
				if(sd && sd->elementball.num && sd->elementball.ele == ELE_WIND)
					rate += sd->elementball.num * 100;
				MATK_FIX( rate, 100 );
			}
			break;
		case NPC_EARTHQUAKE:	// �A�[�X�N�G�C�N
			{
				static const int dmg[10] = { 300, 500, 600, 800, 1000, 1200, 1300, 1500, 1600, 1800 };
				static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

				wd = battle_calc_weapon_attack(bl,bl,skill_num,skill_lv,flag);

				mgd.damage = wd.damage;
				if(mdef1 < 1000000)
					mdef1 = mdef2 = 0;	// MDEF����
				if(skill_lv <= sizeof(dmg)/sizeof(dmg[0])) {
					MATK_FIX( dmg[skill_lv-1], 100 );
				} else {
					MATK_FIX( 100 + 200 * skill_lv, 100 );
				}
				if(flag > 1) {
					MATK_FIX( 1, flag );
				}
				normalmagic_flag = 0;
			}
			break;
		case NPC_EVILLAND:	// �C�[�r�������h
			mgd.damage = (skill_lv > 6)? 666: skill_lv*100;
			normalmagic_flag = 0;
			break;
		case NPC_PULSESTRIKE2:	// �p���X�X�g���C�NII
			mgd.damage = status_get_matk1(bl);
			normalmagic_flag = 0;
			MATK_FIX( 200, 100 );
			break;
		case NPC_FLAMECROSS:	// �t���C���N���X
			if((t_ele == ELE_FIRE || battle_check_undead(t_race,t_ele)) && target->type != BL_PC)
				mgd.blewcount = 0;
			else
				mgd.blewcount |= SAB_REVERSEBLOW;
			MATK_FIX( 20 * skill_lv, 100 );		// TODO: Atk * per
			break;
		case NPC_COMET:	// M�R���b�g
			if(flag == 3) {			// ������
				MATK_FIX( 1000 + 500 * skill_lv, 100 );
			} else if(flag == 2) {		// ������
				MATK_FIX( 1500 + 500 * skill_lv, 100 );
			} else if(flag == 1) {		// �ߋ���
				MATK_FIX( 2000 + 500 * skill_lv, 100 );
			} else {		// ���S
				MATK_FIX( 2500 + 500 * skill_lv, 100 );
			}
			break;
		case NPC_JACKFROST:		// M�W���b�N�t���X�g
			MATK_FIX( 1000 + 300 * skill_lv, 100 );
			break;
		case NPC_FIRESTORM:		// ����
			MATK_FIX( 300, 100 );
			break;
		case NPC_PSYCHIC_WAVE:	// M�T�C�L�b�N�E�F�[�u
			MATK_FIX( 500 * skill_lv, 100 );
			break;
		case NPC_RAYOFGENESIS:	// M���C�I�u�W�F�l�V�X
			MATK_FIX( 200 * skill_lv, 100 );
			break;
		case NPC_POISON_BUSTER:	/* M�|�C�Y���o�X�^�[ */
			MATK_FIX( 1500 * skill_lv, 100 );
			break;
		case NPC_CLOUD_KILL:		/* M�N���E�h�L�� */
			MATK_FIX( 50 * skill_lv, 100 );
			break;
		case NPC_ELECTRICWALK:	// M�G���N�g���b�N�E�H�[�N
		case NPC_FIREWALK:		// M�t�@�C�A�[�E�H�[�N
			MATK_FIX( 100 * skill_lv, 100 );
			break;
		case NPC_CANE_OF_EVIL_EYE:	// �P�[���I�u�C�r���A�C
			mgd.damage = 150000;
			normalmagic_flag = 0;
			break;
		case MH_POISON_MIST:		// �|�C�Y���~�X�g
			MATK_FIX( 40 * skill_lv * status_get_lv(bl) / 100, 100 );
			break;
		case MH_ERASER_CUTTER:	// �C���C�T�[�J�b�^�[
			if(skill_lv%2) {
				ele = ELE_WIND;
				MATK_FIX( 500 + 100 * skill_lv, 100 );
			}
			else
				MATK_FIX( 800 + 100 * skill_lv, 100 );
			break;
		case MH_XENO_SLASHER:	// �[�m�X���b�V���[
			if(skill_lv%2) {
				ele = ELE_WIND;
				MATK_FIX( 450 + 50 * skill_lv, 100 );
			}
			else
				MATK_FIX( 500 + 100 * skill_lv, 100 );
			break;
		case MH_HEILIGE_STANGE:	// �n�C���G�[�W���X�^���W�F
			MATK_FIX( 500 + 250 * skill_lv * status_get_lv(bl) / 150, 100 );
			break;
		case RK_ENCHANTBLADE:	// �G���`�����g�u���C�h
			if(sc && sc->data[SC_ENCHANTBLADE].timer != -1) {
				mgd.damage += sc->data[SC_ENCHANTBLADE].val2;
			}
			break;
		case AB_HIGHNESSHEAL:	// �n�C�l�X�q�[��
			mgd.damage = skill_calc_heal(bl,10);
			if(sd) {	// ������ʂ��悹��
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
			mgd.damage += heal;	// Matk�̉��Z
#endif
			mgd.damage = mgd.damage * (170 + 30 * skill_lv) / 100;
			mgd.damage = mgd.damage / 2;
			normalmagic_flag = 0;
			break;
		case AB_JUDEX:		// �W���f�b�N�X
			MATK_FIX( (360 + 48 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case AB_ADORAMUS:	// �A�h�����X
			MATK_FIX( (500 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case AB_RENOVATIO:	// ���m���@�e�B�I
			ele = ELE_HOLY;
			mgd.damage = (status_get_lv(bl) * 10 + status_get_int(bl));
			normalmagic_flag = 0;
			break;
		case AB_DUPLELIGHT_MAGIC:	// �~���A�����C�g
			MATK_FIX( 200 + 20 * skill_lv, 100 );
			break;
		case WL_SOULEXPANSION:		// �\�E���G�N�X�p���V����
			MATK_FIX( (status_get_int(bl) + 400 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_FROSTMISTY:	// �t���X�g�~�X�e�B
			MATK_FIX( (200 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_JACKFROST:	// �W���b�N�t���X�g
			if(t_sc && t_sc->data[SC_FROSTMISTY].timer != -1) {
				MATK_FIX( (1000 + 300 * skill_lv) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (500 + 100 * skill_lv) * status_get_lv(bl) / 150, 100 );
			}
			break;
		case WL_DRAINLIFE:	// �h���C�����C�t
			MATK_FIX( (status_get_int(bl) + 200 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_CRIMSONROCK:	// �N�����]�����b�N
			MATK_FIX( 1300 + (300 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_HELLINFERNO:	// �w���C���t�F���m
			if(flag) {	// �ő���
				ele = ELE_DARK;
				MATK_FIX( 240 * skill_lv * status_get_lv(bl) / 100, 100 );
			} else {	// �Α���
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100, 100 );
			}
			break;
		case WL_COMET:	// �R���b�g
			if(flag == 3) {			// ������
				MATK_FIX( 800 + 200 * skill_lv, 100 );
			} else if(flag == 2) {		// ������
				MATK_FIX( 1200 + 300 * skill_lv, 100 );
			} else if(flag == 1) {		// �ߋ���
				MATK_FIX( 1600 + 400 * skill_lv, 100 );
			} else {		// ���S
				MATK_FIX( 2500 + 500 * skill_lv, 100 );
			}
			break;
		case WL_CHAINLIGHTNING:		// �`�F�[�����C�g�j���O
		case WL_CHAINLIGHTNING_ATK:	// �`�F�[�����C�g�j���O(�A��)
			MATK_FIX( (300 + 100 * skill_lv) + (500 + 100 * skill_lv) * status_get_lv(bl) / 100 - (flag - 1) * 100, 100 );		// flag:�A����
			break;
		case WL_EARTHSTRAIN:	// �A�[�X�X�g���C��
			MATK_FIX( (2000 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WL_TETRAVORTEX_FIRE:		/* �e�g���{���e�b�N�X(��) */
		case WL_TETRAVORTEX_WATER:		/* �e�g���{���e�b�N�X(��) */
		case WL_TETRAVORTEX_WIND:		/* �e�g���{���e�b�N�X(��) */
		case WL_TETRAVORTEX_GROUND:		/* �e�g���{���e�b�N�X(�n) */
			MATK_FIX( 500 + 500 * skill_lv, 100 );
			break;
		case WL_SUMMON_ATK_FIRE:		/* �T�����t�@�C�A�{�[��(�U��) */
		case WL_SUMMON_ATK_WIND:		/* �T�����{�[�����C�g�j���O(�U��) */
		case WL_SUMMON_ATK_WATER:		/* �T�����E�H�[�^�[�{�[��(�U��) */
		case WL_SUMMON_ATK_GROUND:		/* �T�����X�g�[��(�U��) */
			MATK_FIX( (status_get_lv(bl) + status_get_jlv(bl)) * ((1 + skill_lv) / 2) * status_get_lv(bl) / 100, 100 );
			break;
		case LG_SHIELDSPELL:	// �V�[���h�X�y��
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
		case LG_RAYOFGENESIS:			/* ���C�I�u�W�F�l�V�X */
			MATK_FIX( (200 * skill_lv) * status_get_lv(bl) / 100, 100 );
			break;
		case WM_METALICSOUND:	/* ���^���b�N�T�E���h */
			MATK_FIX( ( ( 120 * skill_lv ) + ( (sd)? pc_checkskill(sd,WM_LESSON): 0 ) * 60 ) * status_get_lv(bl) / 100, 100 );
			if(t_sc && (t_sc->data[SC_SLEEP].timer != -1 || t_sc->data[SC_DEEP_SLEEP].timer != -1)) {
				MATK_FIX( 150, 100 );
			}
			break;
		case WM_REVERBERATION_MAGIC:	/* �U���c��(���@) */
			MATK_FIX( (100 + 100 * skill_lv) * status_get_lv(bl) / 100, 100 );
			if(flag > 1) {
				MATK_FIX( 1, flag );
			}
			break;
		case SO_FIREWALK:		/* �t�@�C�A�[�E�H�[�N */
			if(sc && sc->data[SC_HEATER].timer != -1) {
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100 + sc->data[SC_HEATER].val3, 100 );
			} else {
				MATK_FIX( 60 * skill_lv * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_ELECTRICWALK:	/* �G���N�g���b�N�E�H�[�N */
			if(sc && sc->data[SC_BLAST].timer != -1) {
				MATK_FIX( 90 * skill_lv + sc->data[SC_BLAST].val3, 100 );
			} else {
				MATK_FIX( 90 * skill_lv, 100 );
			}
			break;
		case SO_EARTHGRAVE:		/* �A�[�X�O���C�u */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_SEISMICWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_SEISMICWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_DIAMONDDUST:	/* �_�C�������h�_�X�g */
			if(sc && sc->data[SC_COOLER].timer != -1) {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_FROSTWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100 + sc->data[SC_COOLER].val3, 100 );
			} else {
				MATK_FIX( ( ( (sd)? pc_checkskill(sd,SA_FROSTWEAPON): 1 ) * 200 + skill_lv * status_get_int(bl) ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_POISON_BUSTER:	/* �|�C�Y���o�X�^�[ */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( ( 1000 + 300 * skill_lv ) * status_get_lv(bl) / 120 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( ( 1000 + 300 * skill_lv ) * status_get_lv(bl) / 120, 100 );
			}
			break;
		case SO_PSYCHIC_WAVE:	/* �T�C�L�b�N�E�F�[�u */
			if(sc) {
				if(sc->data[SC_HEATER].timer != -1 || sc->data[SC_FLAMETECHNIC].timer != -1) {
					ele = ELE_FIRE;
				} else if(sc->data[SC_COOLER].timer != -1 || sc->data[SC_COLD_FORCE].timer != -1) {
					ele = ELE_WATER;
				} else if(sc->data[SC_BLAST].timer != -1 || sc->data[SC_GRACE_BREEZE].timer != -1) {
					ele = ELE_WIND;
				} else if(sc->data[SC_CURSED_SOIL].timer != -1 || sc->data[SC_EARTH_CARE].timer != -1) {
					ele = ELE_EARTH;
				} else if(sc->data[SC_DEEP_POISONING].timer != -1) {
					ele = ELE_POISON;
				}
			}
			MATK_FIX( ( 70 * skill_lv + status_get_int(bl) * 3 ) * status_get_lv(bl) / 100, 100 );
			break;
		case SO_CLOUD_KILL:		/* �N���E�h�L�� */
			if(sc && sc->data[SC_CURSED_SOIL].timer != -1) {
				MATK_FIX( ( 40 * skill_lv ) * status_get_lv(bl) / 100 + sc->data[SC_CURSED_SOIL].val3, 100 );
			} else {
				MATK_FIX( ( 40 * skill_lv ) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SO_VARETYR_SPEAR:	/* ���F���`���[���X�s�A */
			if(sc && sc->data[SC_BLAST].timer != -1) {
				MATK_FIX( ( 120 * ( (sd)? (pc_checkskill(sd,SA_LIGHTNINGLOADER) + pc_checkskill(sd,SO_STRIKING)): 1 ) + status_get_int(bl) * skill_lv / 2) * status_get_lv(bl) / 100 + sc->data[SC_BLAST].val3, 100 );
			} else {
				MATK_FIX( ( 120 * ( (sd)? (pc_checkskill(sd,SA_LIGHTNINGLOADER) + pc_checkskill(sd,SO_STRIKING)): 1 ) + status_get_int(bl) * skill_lv / 2) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case GN_DEMONIC_FIRE:	// �f���j�b�N�t�@�C�A�[
			if(flag == 1) {		// ��
				MATK_FIX( (200 * skill_lv) + status_get_jlv(bl) + status_get_int(bl), 100 );
			} else if(flag == 2) {	// ����
				MATK_FIX( 200 * skill_lv + status_get_int(bl) * 10, 100 );
			} else {
				MATK_FIX( 200 * skill_lv, 100 );
			}
			break;
		case KO_KAIHOU:	/* �p�� -���- */
			MATK_FIX( 200 * status_get_lv(bl) / 100, 100 );
			if(sd) {
				// �������̋��̂̑�����K�p����
				ele = sd->elementball.ele;
				// �������̋��̂̐��ɉ�����HIT���ω�����
				mgd.div_ = sd->elementball.num;
			} else {
				mgd.div_ = 10;
			}
			break;
		case SP_CURSEEXPLOSION:	// ���씚��
			if(t_sc && t_sc->data[SC_SOULCURSE].timer != -1) {
				MATK_FIX( (2500 + 250 * skill_lv) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (2300 + 50 * skill_lv) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case SP_SPA:	// �G�X�p
			MATK_FIX( (500 + 250 * skill_lv) * status_get_lv(bl) / 100, 100 );
			ele = status_get_attack_element_nw(bl);
			break;
		case SP_SHA:	//�G�X�n
			MATK_FIX( 2000 + 100 * skill_lv, 100 );
			ele = status_get_attack_element_nw(bl);
			break;
		case SP_SWHOO:	//�G�X�t
			MATK_FIX( (1500 + 250 * skill_lv) * status_get_lv(bl) / 100, 100 );
			ele = status_get_attack_element_nw(bl);
			break;
		case SU_SV_STEMSPEAR:	/* �}�^�^�r�����X */
			{
				const int ele_type[5] = { ELE_GHOST, ELE_WATER, ELE_WIND, ELE_EARTH, ELE_FIRE };
				if(skill_lv <= 5)
					ele = ele_type[skill_lv-1];
				MATK_FIX( 5000, 100 );
			}
			break;
		case SU_CN_METEOR:	/* �C�k�n�b�J���e�I */
		case SU_CN_METEOR2:	/* �C�k�n�b�J���e�I(��) */
			MATK_FIX( 400 * (status_get_lv(bl) >= 100? status_get_lv(bl): 100) / 100, 100 );
			if(sc) {
				if(sc->data[SC_COLORS_OF_HYUN_ROK_1].timer != -1)
					ele = ELE_WATER;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_2].timer != -1)
					ele = ELE_WIND;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_3].timer != -1)
					ele = ELE_EARTH;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_4].timer != -1)
					ele = ELE_FIRE;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_5].timer != -1)
					ele = ELE_DARK;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_6].timer != -1)
					ele = ELE_HOLY;
			}
			break;
		case AG_DEADLY_PROJECTION:	/* �f�b�h���[�v���W�F�N�V���� */
			MATK_FIX( (2000 + 500 * skill_lv + status_get_spl(bl) * 15) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_DESTRUCTIVE_HURRICANE:		/* �f�B�X�g���N�e�B�u�n���P�[�� */
			if(flag == 0x10) {		// �N���C�}�b�N�XLv1�F�ǉ����������@�_���[�W
				MATK_FIX( 5000, 100 );
			} else {
				MATK_FIX( (8500 + 2500 * skill_lv + status_get_spl(bl) * 70) * status_get_lv(bl) / 100, 100 );
			}
			if(flag != 2) {		// �N���C�}�b�N�XLv2�F�m�b�N�o�b�N����
				mgd.blewcount = 0;
			}
			if(flag == 3) {		// �N���C�}�b�N�XLv3�F�_���[�W+100%
				MATK_FIX( 200, 100 );
			} else if(flag == 5) {		// �N���C�}�b�N�XLv5�F�_���[�W+50%
				MATK_FIX( 150, 100 );
			}
			break;
		case AG_RAIN_OF_CRYSTAL:		/* ���C���I�u�N���X�^�� */
			MATK_FIX( (2000 + 200 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_MYSTERY_ILLUSION:		/* �~�X�e���[�C�����[�W���� */
			MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_VIOLENT_QUAKE_ATK:		/* �o�C�I�����g�N�G�C�N(�U��) */
			MATK_FIX( (2000 + 200 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			if(flag == 1) {			// �N���C�}�b�N�XLv1�F�_���[�W-50%
				MATK_FIX( 50, 100 );
			} else if(flag == 3) {	// �N���C�}�b�N�XLv3�F�_���[�W+50%
				MATK_FIX( 150, 100 );
			}
			break;
		case AG_SOUL_VC_STRIKE:		/* �\�E���o���J���X�g���C�N */
			MATK_FIX( (350 + 50 * skill_lv + status_get_spl(bl) * 2) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_STRANTUM_TREMOR:		/* �X�g���^���g���}�[ */
			MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_ALL_BLOOM_ATK:		/* �I�[���u���[��(�U��) */
			MATK_FIX( (2000 + 200 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			if(flag == 2) {			// �N���C�}�b�N�XLv2�F�_���[�W-50%
				MATK_FIX( 50, 100 );
			} else if(flag == 3) {	// �N���C�}�b�N�XLv3�F�_���[�W+50%
				MATK_FIX( 150, 100 );
			}
			break;
		case AG_ALL_BLOOM_ATK2:		/* �I�[���u���[��(�ǌ�) */
			MATK_FIX( 25000 + 5000 * skill_lv, 100 );
			break;
		case AG_CRYSTAL_IMPACT:		/* �N���X�^���C���p�N�g */
			MATK_FIX( (8500 + 2500 * skill_lv + status_get_spl(bl) * 70) * status_get_lv(bl) / 100, 100 );
			if(flag == 2) {			// �N���C�}�b�N�XLv2�F2��A���U��
				mgd.div_ = 2;
			} else if(flag == 3) {	// �N���C�}�b�N�XLv3�F�_���[�W+50%
				MATK_FIX( 150, 100 );
			}
			break;
		case AG_CRYSTAL_IMPACT_ATK:		/* �N���X�^���C���p�N�g(�ǌ�) */
			if(flag == 4) {			// �N���C�}�b�N�XLv4�F�_���[�W+5000%
				MATK_FIX( (5100 + status_get_spl(bl)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (100 + status_get_spl(bl)) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case AG_TORNADO_STORM:		/* �g���l�[�h�X�g�[�� */
			MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_FLORAL_FLARE_ROAD:	/* �t���[�����t���A���[�h */
			MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_ASTRAL_STRIKE:		/* �A�X�g�����X�g���C�N */
			MATK_FIX( (1500 + 150 * skill_lv + (skill_lv > 5)? status_get_spl(bl) * 10: status_get_spl(bl) * 5) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_ASTRAL_STRIKE_ATK:	/* �A�X�g�����X�g���C�N(����) */
			MATK_FIX( (7000 + 2000 * skill_lv + status_get_spl(bl) * 90) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_ROCK_DOWN:		/* ���b�N�_�E�� */
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				MATK_FIX( (5000 + 2500 * skill_lv + status_get_spl(bl) * 45) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (4250 + 1250 * skill_lv + status_get_spl(bl) * 35) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case AG_STORM_CANNON:		/* �X�g�[���L���m�� */
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				MATK_FIX( (5000 + 2500 * skill_lv + status_get_spl(bl) * 45) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (4250 + 1250 * skill_lv + status_get_spl(bl) * 35) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case AG_CRIMSON_ARROW:		/* �N�����]���A���[(�U��) */
			MATK_FIX( (100 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			break;
		case AG_CRIMSON_ARROW_ATK:		/* �N�����]���A���[(�U��) */
			MATK_FIX( (1500 + 500 * skill_lv + status_get_spl(bl) * 15) * status_get_lv(bl) / 100, 100 );
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				mgd.div_ += 1;
			}
			break;
		case AG_FROZEN_SLASH:		/* �t���[�Y���X���b�V�� */
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				MATK_FIX( (5000 + 2500 * skill_lv + status_get_spl(bl) * 45) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (4250 + 1250 * skill_lv + status_get_spl(bl) * 35) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case IG_JUDGEMENT_CROSS:	/* �W���b�W�����g�N���X */
			MATK_FIX( (7000 + 2000 * skill_lv + status_get_spl(bl) * 60) * status_get_lv(bl) / 100, 100 );
			break;
		case IG_CROSS_RAIN:		/* �N���X���C�� */
			if(sc && sc->data[SC_HOLY_S].timer != -1) {
				MATK_FIX( (150 * skill_lv + ((sd)? pc_checkskill(sd,IG_SPEAR_SWORD_M): 0) * (skill_lv * 15) + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (120 * skill_lv + ((sd)? pc_checkskill(sd,IG_SPEAR_SWORD_M): 0) * (skill_lv * 5) + status_get_spl(bl) * 5) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case CD_ARBITRIUM:	/* �A���r�g���E�� */
			MATK_FIX( (50 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * (skill_lv * 4) +  status_get_spl(bl) * 3) * status_get_lv(bl) / 100, 100 );
			break;
		case CD_ARBITRIUM_ATK:	/* �A���r�g���E��(�ǌ�) */
			MATK_FIX( (450 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * (skill_lv * 30) +  status_get_spl(bl) * 25) * status_get_lv(bl) / 100, 100 );
			break;
		case CD_PNEUMATICUS_PROCELLA:	/* �j���[�}�e�B�b�N�v���Z�� */
			if(t_race == RCT_UNDEAD || t_race == RCT_DEMON) {
				MATK_FIX( (6000 + 1500 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * 5 +  status_get_spl(bl) * 70) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (5500 + 1250 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * 3 +  status_get_spl(bl) * 60) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case CD_FRAMEN:	/* �t���[���� */
			if(t_race == RCT_UNDEAD || t_race == RCT_DEMON) {
				MATK_FIX( (900 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * (skill_lv * 60) +  status_get_spl(bl) * 50) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (600 * skill_lv + ((sd)? pc_checkskill(sd,CD_FIDUS_ANIMUS): 0) * (skill_lv * 30) +  status_get_spl(bl) * 30) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case ABC_FROM_THE_ABYSS_ATK:	/* �t�����W�A�r�X(�U��) */
			MATK_FIX( (1500 + 1500 * skill_lv + status_get_spl(bl) * 30) * status_get_lv(bl) / 100, 100 );
			break;
		case ABC_ABYSS_STRIKE:	/* �I���K�A�r�X�X�g���C�N */
			MATK_FIX( (7000 + 2000 * skill_lv + status_get_spl(bl) * 90) * status_get_lv(bl) / 100, 100 );
			break;
		case ABC_ABYSS_SQUARE:	/* �A�r�X�X�N�G�A */
			MATK_FIX( (150 * skill_lv + ((sd)? pc_checkskill(sd,ABC_MAGIC_SWORD_M): 0) * (skill_lv * 15) +  status_get_spl(bl) * 5) * status_get_lv(bl) / 100, 100 );
			if(flag) {
				mgd.div_ += 1;
			}
			break;
		case TR_ROSEBLOSSOM:	/* ���[�u���b�T�� */
			if(t_sc && t_sc->data[SC_SOUNDBLEND].timer != -1) {
				MATK_FIX( (1250 + 350 * skill_lv + status_get_con(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (750 + 150 * skill_lv + status_get_con(bl) * 5) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case TR_ROSEBLOSSOM_ATK:	/* ���[�u���b�T��(�U��) */
			if(t_sc && t_sc->data[SC_SOUNDBLEND].timer != -1) {
				MATK_FIX( (2500 + 700 * skill_lv + status_get_con(bl) * 20) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (1250 + 350 * skill_lv + status_get_con(bl) * 10) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case TR_METALIC_FURY:	/* ���^���b�N�t���[���[ */
			if(t_sc && t_sc->data[SC_SOUNDBLEND].timer != -1) {
				MATK_FIX( (4000 + 1000 * skill_lv + status_get_spl(bl) * 30) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (1250 + 350 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			}
			if(sd) {
				int e;
				if((e = status_get_attack_element_nw(&sd->bl)) != ELE_NEUTRAL)	// �����t�^
					ele = e;
				else if(sd->arrow_ele > ELE_NEUTRAL)	// ��̑���
					ele = sd->arrow_ele;
				else if((e = status_get_attack_element(&sd->bl)) != ELE_NEUTRAL) // ���푮��
					ele = e;
			}
			break;
		case TR_SOUNDBLEND:	/* �T�E���h�u�����h */
			MATK_FIX( (2000 + 500 * skill_lv + status_get_spl(bl) * 15) * status_get_lv(bl) / 100, 100 );
			if(sd) {
				int e;
				if((e = status_get_attack_element_nw(&sd->bl)) != ELE_NEUTRAL)	// �����t�^
					ele = e;
				else if(sd->arrow_ele > ELE_NEUTRAL)	// ��̑���
					ele = sd->arrow_ele;
				else if((e = status_get_attack_element(&sd->bl)) != ELE_NEUTRAL) // ���푮��
					ele = e;
			}
			break;
		case EM_DIAMOND_STORM:	/* �_�C�������h�X�g�[�� */
			if(t_sc && t_sc->data[SC_SUMMON_ELEMENTAL_DILUVIO].timer != -1) {
				MATK_FIX( (3000 + 1500 * skill_lv + 300 * skill_lv + status_get_spl(bl) * 45) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (3750 + 750 * skill_lv + status_get_spl(bl) * 25) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EM_LIGHTNING_LAND:	/* ���C�g�j���O�����h */
			if(t_sc && t_sc->data[SC_SUMMON_ELEMENTAL_PROCELLA].timer != -1) {
				MATK_FIX( (1000 + 400 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EM_VENOM_SWAMP:	/* �x�i���X�����v */
			if(t_sc && t_sc->data[SC_SUMMON_ELEMENTAL_SERPENS].timer != -1) {
				MATK_FIX( (1000 + 400 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EM_CONFLAGRATION:	/* �R���t���O���[�V���� */
			if(t_sc && t_sc->data[SC_SUMMON_ELEMENTAL_ARDOR].timer != -1) {
				MATK_FIX( (1000 + 400 * skill_lv + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (900 + 300 * skill_lv + status_get_spl(bl) * 8) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EM_TERRA_DRIVE:	/* �e���h���C�u */
			if(t_sc && t_sc->data[SC_SUMMON_ELEMENTAL_TERREMOTUS].timer != -1) {
				MATK_FIX( (3000 + 1500 * skill_lv + 300 * skill_lv + status_get_spl(bl) * 45) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (3750 + 750 * skill_lv + status_get_spl(bl) * 25) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EM_ELEMENTAL_BUSTER:			/* �G�������^���o�X�^�[ */
		case EM_ELEMENTAL_BUSTER_FIRE:		/* �G�������^���o�X�^�[(��) */
		case EM_ELEMENTAL_BUSTER_WATER:		/* �G�������^���o�X�^�[(��) */
		case EM_ELEMENTAL_BUSTER_WIND:		/* �G�������^���o�X�^�[(��) */
		case EM_ELEMENTAL_BUSTER_GROUND:	/* �G�������^���o�X�^�[(�n) */
		case EM_ELEMENTAL_BUSTER_POISON:	/* �G�������^���o�X�^�[(��) */
			MATK_FIX( (10500 + 3000 * skill_lv + status_get_spl(bl) * 135) * status_get_lv(bl) / 100, 100 );
			break;
		case NPC_BO_HELL_HOWLING:	/* �w���n�E�����O */
			MATK_FIX( 15000 * status_get_lv(bl) / 100, 100 );
			break;
		case NPC_BO_FAIRY_DUSTY:	/* �t�F�A���[�_�X�e�B */
			MATK_FIX( 12500 * status_get_lv(bl) / 100, 100 );
			break;
		case SOA_TALISMAN_OF_SOUL_STEALING:		/* �쓹�� */
			MATK_FIX( (2000 + skill_lv * 200 + status_get_spl(bl) * 3 + ((sd)? (pc_checkskill(sd,SOA_TALISMAN_MASTERY) + pc_checkskill(sd,SOA_SOUL_MASTERY)) * 7 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* ����� */
			if(t_sc && t_sc->data[SC_SOULCURSE].timer != -1) {
				MATK_FIX( (400 + skill_lv * 100 + status_get_spl(bl) + ((sd)? pc_checkskill(sd,SOA_SOUL_MASTERY) * 2: 0)) * ((sd)? sd->soulenergy.num: 1) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (400 + skill_lv * 50 + status_get_spl(bl) + ((sd)? pc_checkskill(sd,SOA_SOUL_MASTERY) * 2: 0)) * ((sd)? sd->soulenergy.num: 1) * status_get_lv(bl) / 100, 100 );
			}
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_TALISMAN_OF_BLUE_DRAGON:		/* ���� */
			if(sc && sc->data[SC_T_FIVETH_GOD].timer != -1) {
				MATK_FIX( (5500 + skill_lv * 1000 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (4250 + skill_lv * 750 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_TALISMAN_OF_WHITE_TIGER:		/* ���Օ� */
			if(sc && sc->data[SC_T_FIVETH_GOD].timer != -1) {
				MATK_FIX( (4250 + skill_lv * 500 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (3000 + skill_lv * 400 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_TALISMAN_OF_RED_PHOENIX:		/* �鐝�� */
			if(sc && sc->data[SC_T_FIVETH_GOD].timer != -1) {
				MATK_FIX( (5500 + skill_lv * 650 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (4250 + skill_lv * 500 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_TALISMAN_OF_BLACK_TORTOISE:	/* ������ */
			if(sc && sc->data[SC_T_FIVETH_GOD].timer != -1) {
				MATK_FIX( (4250 + skill_lv * 500 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (3000 + skill_lv * 400 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SOA_TALISMAN_OF_FOUR_BEARING_GOD:	/* �l���_�� */
			MATK_FIX( (500 + skill_lv * 50 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			if(sc) {
				if(sc->data[SC_T_FIRST_GOD].timer != -1) {
					mgd.div_ += 1;
				} else if(sc->data[SC_T_SECOND_GOD].timer != -1){
					mgd.div_ += 2;
				} else if(sc->data[SC_T_THIRD_GOD].timer != -1){
					mgd.div_ += 3;
				} else if(sc->data[SC_T_FOURTH_GOD].timer != -1){
					mgd.div_ += 4;
				} else if(sc->data[SC_T_FIVETH_GOD].timer != -1){
					mgd.div_ += 5;
				}
				if(sc->data[SC_SEVENWIND].timer != -1) {
					ele = sc->data[SC_SEVENWIND].val3;
				}
			}
			break;
		case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* �l���܍s�w */
			MATK_FIX( (2200 + skill_lv * 600 + status_get_spl(bl) * 5 + ((sd)? (pc_checkskill(sd,SOA_TALISMAN_MASTERY) + pc_checkskill(sd,SOA_SOUL_MASTERY)) * 15 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			if(sc && sc->data[SC_SEVENWIND].timer != -1) {
				ele = sc->data[SC_SEVENWIND].val3;
			}
			break;
		case SH_HYUN_ROKS_BREEZE:	/* �f�B�A�[�u���[�Y */
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_HYUN_ROK)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				MATK_FIX( (1600 + skill_lv * 200 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 40: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (800 + skill_lv * 100 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 20: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc) {
				if(sc->data[SC_COLORS_OF_HYUN_ROK_1].timer != -1)
					ele = ELE_WATER;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_2].timer != -1)
					ele = ELE_WIND;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_3].timer != -1)
					ele = ELE_EARTH;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_4].timer != -1)
					ele = ELE_FIRE;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_5].timer != -1)
					ele = ELE_DARK;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_6].timer != -1)
					ele = ELE_HOLY;
			}
			break;
		case SH_HYUN_ROK_CANNON:	/* �f�B�A�[�L���m�� */
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_HYUN_ROK)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				MATK_FIX( (5200 + skill_lv * 800 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 250: 0)) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (2400 + skill_lv * 300 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 125: 0)) * status_get_lv(bl) / 100, 100 );
			}
			if(sc) {
				if(sc->data[SC_COLORS_OF_HYUN_ROK_1].timer != -1)
					ele = ELE_WATER;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_2].timer != -1)
					ele = ELE_WIND;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_3].timer != -1)
					ele = ELE_EARTH;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_4].timer != -1)
					ele = ELE_FIRE;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_5].timer != -1)
					ele = ELE_DARK;
				else if(sc->data[SC_COLORS_OF_HYUN_ROK_6].timer != -1)
					ele = ELE_HOLY;
			}
			break;
		case HN_METEOR_STORM_BUSTER:	/* ���e�I�X�g�[���o�X�^�[ */
			{
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate;
				if(flag) {		// �����_���[�W
					rate = (1175 + skill_lv * 25 + ss_lv * 5 * skill_lv + status_get_spl(bl) * 3) * status_get_lv(bl) / 100;
					// �����͓Ɗw�̃_���[�W�␳�͊|����Ȃ�
					mgd.div_ = 1;
				} else {		// �����_���[�W
					static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
					rate = (1750 + skill_lv * 50 + ss_lv * 5 * skill_lv + status_get_spl(bl) * 3) * status_get_lv(bl) / 100;

					// �Ɗw�̃_���[�W�{���v�Z
					if(ss_lv > 10) ss_lv = 10;
					rate = rate * ss_rate[ss_lv] / 100;
				}
				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case HN_JUPITEL_THUNDER_STORM:	/* ���s�e���T���_�[�X�g�[�� */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate = (2700 + skill_lv * 150 + ss_lv * 3 * skill_lv + status_get_spl(bl) * 3) * status_get_lv(bl) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case HN_JACK_FROST_NOVA:	/* �W���b�N�t���X�g�m���@ */
			{
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate;

				if(flag) {		// �ݒu�_���[�W
					static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
					rate = (650 + skill_lv * 25 + ss_lv * 3 * skill_lv + status_get_spl(bl) * 4) * status_get_lv(bl) / 100;

					// �Ɗw�̃_���[�W�{���v�Z
					if(ss_lv > 10) ss_lv = 10;
					rate = rate * ss_rate[ss_lv] / 100;
				} else {		// �����_���[�W
					rate = (100 + skill_lv * 20 + ss_lv * 3 * skill_lv + status_get_spl(bl) * 2) * status_get_lv(bl) / 100;
					// �����͓Ɗw�̃_���[�W�␳�͊|����Ȃ�
					mgd.div_ = 1;
				}
				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case HN_HELLS_DRIVE:	/* �w���Y�h���C�u */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate = (2600 + skill_lv * 150 + ss_lv * 4 * skill_lv + status_get_spl(bl) * 3) * status_get_lv(bl) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case HN_GROUND_GRAVITATION:		/* �O���E���h�O���r�e�[�V���� */
			{
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate;

				if(flag&2) {	// �ݒu�_���[�W
					static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
					rate = (300 + skill_lv * 10 + ss_lv * 2 * skill_lv + status_get_spl(bl) * 2) * status_get_lv(bl) / 100;

					// �Ɗw�̃_���[�W�{���v�Z
					if(ss_lv > 10) ss_lv = 10;
					rate = rate * ss_rate[ss_lv] / 100;

					mgd.div_ = 1;
				} else {		// �����_���[�W
					rate = (600 + skill_lv * 50 + ss_lv * 4 * skill_lv + status_get_spl(bl) * 5) * status_get_lv(bl) / 100;
					// �����͓Ɗw�̃_���[�W�␳�͊|����Ȃ�
				}
				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case HN_NAPALM_VULCAN_STRIKE:	/* �i�p�[���o���J���X�g���C�N */
			{
				static const int ss_rate[11] = { 100, 101, 103, 105, 107, 109, 111, 113, 115, 120, 125 };
				int ss_lv = (sd)? pc_checkskill(sd,HN_SELFSTUDY_SOCERY): 0;
				int rate = (2600 + skill_lv * 150 + ss_lv * 4 * skill_lv + status_get_spl(bl) * 3) * status_get_lv(bl) / 100;

				// �Ɗw�̃_���[�W�{���v�Z
				if(ss_lv > 10) ss_lv = 10;
				rate = rate * ss_rate[ss_lv] / 100;

				// ���[���u���C�N
				if(sc && sc->data[SC_RULEBREAK].timer != -1)
					rate = rate * 300 / 100;

				MATK_FIX( rate, 100 );
			}
			break;
		case SS_TOKEDASU:		/* �e�n�� */
			MATK_FIX( (3200 + skill_lv * 500 + status_get_con(bl) * 5) * status_get_lv(bl) / 100, 100 );
			mgd.blewcount = 0;
			break;
		case SS_SEKIENHOU:		/* �ԉ��C */
			MATK_FIX( (4000 + skill_lv * 300 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SS_ANTENPOU) * 70 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			break;
		case SS_REIKETSUHOU:	/* �⌌�C */
			MATK_FIX( (4000 + skill_lv * 300 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SS_ANTENPOU) * 70 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			break;
		case SS_RAIDENPOU:		/* ���d�C */
			MATK_FIX( (4000 + skill_lv * 300 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SS_ANTENPOU) * 70 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			break;
		case SS_KINRYUUHOU:		/* �����C */
			MATK_FIX( (4000 + skill_lv * 300 + status_get_spl(bl) * 5 + ((sd)? pc_checkskill(sd,SS_ANTENPOU) * 70 * skill_lv: 0)) * status_get_lv(bl) / 100, 100 );
			break;
		case SS_ANTENPOU:		/* �Ó]�C */
			MATK_FIX( (5750 + skill_lv * 350 + status_get_spl(bl) * 5) * status_get_lv(bl) / 100, 100 );
			if(flag&2) {	// ���g�U��
				mgd.damage = mgd.damage * 30 / 100;
			}
			break;
		case SS_ANKOKURYUUAKUMU:	/* ���p -�Í���- */
			if(flag&2) {	// �ǉ��_���[�W
				ele = ELE_FIRE;
				MATK_FIX( (17000 + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			} else {
				MATK_FIX( (17000 + status_get_spl(bl) * 10) * status_get_lv(bl) / 100, 100 );
			}
			break;
		case EL_FIRE_MANTLE:	/* �t�@�C�A�[�}���g�� */
			if((t_ele == ELE_FIRE || battle_check_undead(t_race,t_ele)) && target->type != BL_PC)
				mgd.blewcount = 0;
			else
				mgd.blewcount |= SAB_REVERSEBLOW;
			MATK_FIX( 1000, 100 );
			break;
		case EL_FIRE_ARROW:		/* �t�@�C�A�[�A���[ */
			MATK_FIX( 300, 100 );
			break;
		case EL_FIRE_BOMB:		/* �t�@�C�A�[�{�� */
			MATK_FIX( 500, 100 );
			break;
		case EL_FIRE_WAVE:		/* �t�@�C�A�[�E�F�[�u */
			MATK_FIX( 1200, 100 );
			break;
		case EL_WATER_SCREW:	/* �E�H�[�^�[�X�N�����[ */
			MATK_FIX( 1000, 100 );
			break;
		case EL_HURRICANE_ATK:	/* �n���P�[�����C�W(�U��) */
			MATK_FIX( 500, 100 );
			break;
		case EL_TYPOON_MIS_ATK:	/* �^�C�t�[���~�T�C��(�U��) */
			MATK_FIX( 1200, 100 );
			break;
		case EL_ROCK_CRUSHER_ATK:	/* ���b�N�����`���[(�U��) */
			MATK_FIX( 300, 100 );
			break;
		case EM_EL_FLAMEROCK:	/* �t���C�����b�N */
			MATK_FIX( 25000 * status_get_lv(bl) / 100, 100 );
			mdef1 = 0;		// ����Mdef����
			break;
		case EM_EL_AGE_OF_ICE:	/* �G�C�W�I�u�A�C�X */
			MATK_FIX( 35000 * status_get_lv(bl) / 100, 100 );
			mdef1 = 0;		// ����Mdef����
			break;
		case EM_EL_STORM_WIND:	/* �X�g�[���E�C���h */
			MATK_FIX( 25000 * status_get_lv(bl) / 100, 100 );
			mdef1 = 0;		// ����Mdef����
			break;
		case EM_EL_AVALANCHE:	/* �A�o�����`�F */
			MATK_FIX( 5000 * status_get_lv(bl) / 100, 100 );
			mdef1 = 0;		// ����Mdef����
			break;
		case EM_EL_DEADLY_POISON:	/* �f�b�h���[�|�C�Y�� */
			MATK_FIX( 7000 * status_get_lv(bl) / 100, 100 );
			mdef1 = 0;		// ����Mdef����
			break;
	}

	/* �S�D��ʖ��@�_���[�W�v�Z */
	if(normalmagic_flag) {
		int rate = 100;

		// S.Matk�ɂ�閂�@�U���_���[�W����
		MATK_FIX( 100 + status_get_smatk(bl), 100 );

		if(sd) {
			rate = rate - sd->ignore_mdef_ele[t_ele] - sd->ignore_mdef_race[t_race] - sd->ignore_mdef_enemy[t_enemy];
			if(t_mode & MD_BOSS)
				rate -= sd->ignore_mdef_race[RCT_BOSS];
			else
				rate -= sd->ignore_mdef_race[RCT_NONBOSS];
		}
		if(rate > 0) {
			mdef1 = mdef1 * rate / 100;
			mdef2 = mdef2 * rate / 100;

#ifdef PRE_RENEWAL
			// ���l�����ׂ̈̃V���t�H�j�[
			if(t_sc && t_sc->data[SC_SYMPHONY_LOVE].timer != -1) {
				// ���ۂɂ͏��ZMDEF���������A�b��Ō��ZMDEF
				mdef2 += mdef2 * t_sc->data[SC_SYMPHONY_LOVE].val4 / 100;
			}
#else
			if(t_sc) {
				short reduce = 100;
				// �A�X���v�e�B�I
				if(t_sc->data[SC_ASSUMPTIO].timer != -1) {
					if(map[target->m].flag.pvp || map[target->m].flag.gvg)
						reduce += 35;	// �V�[�Y��35%
					else
						reduce += 100;	// ����ȊO��100%
				}
				// ���l�����ׂ̈̃V���t�H�j�[
				if(t_sc->data[SC_SYMPHONY_LOVE].timer != -1) {
					reduce += t_sc->data[SC_SYMPHONY_LOVE].val4;
				}
				// ���ZMDEF�ђʂ̓���v�Z����
				if(skill_num == MG_NAPALMBEAT || skill_num == WZ_FIREPILLAR || skill_num == HW_NAPALMVULCAN)
					mdef2 = (mdef1 + mdef2) * reduce / 100;
				else
					mdef1 = mdef1 * reduce / 100;
			}
#endif

			// Mres�ɂ�閂�@�_���[�W����
			if(mres > 0) {
				int mres_rate = 100;
				if(sc) {
					if(sc->data[SC_A_VITA].timer != -1) {		// �A���O�g�D�X���B�^
						mres_rate -= sc->data[SC_A_VITA].val2;
					}
				}

				if(mres_rate < 50) {
					mres_rate = 50;
				}
				if(mres_rate != 100) {
					mres = mres * mres_rate / 100;
				}
				mgd.damage = mgd.damage * (2000 + mres) / (2000 + mres * 5);
			}

			if(battle_config.magic_defense_type) {
				mgd.damage = mgd.damage - (mdef1 * battle_config.magic_defense_type) - mdef2;
			} else {
#ifdef PRE_RENEWAL
				mgd.damage = (mgd.damage*(100-mdef1))/100 - mdef2;
#else
				if(skill_num == RK_ENCHANTBLADE) {
					// �G���`�����g�u���C�h�͏��ZMDEF�����Z����������
					mgd.damage = mgd.damage - mdef1;
				} else if(skill_num != MG_NAPALMBEAT && skill_num != WZ_FIREPILLAR && skill_num != HW_NAPALMVULCAN){
					// �i�p�[���r�[�g,�i�p�[���o���J��,�t�@�C�A�[�s���[�͏��ZMDEF�ђ�
					mgd.damage = (mgd.damage*(1000+mdef1))/(1000+mdef1*10);
				}
#endif
			}
		}
		// �y�C���L���[
		if(t_sc && t_sc->data[SC_PAIN_KILLER].timer != -1)
			mgd.damage -= t_sc->data[SC_PAIN_KILLER].val4;
		if(mgd.damage < 1)	// �v���C���[�̖��@�X�L����1�_���[�W�ۏؖ���
			mgd.damage = (!battle_config.skill_min_damage && bl->type == BL_PC)? 0: 1;
	}

#ifdef PRE_RENEWAL
	/* �T�D�J�[�h�ɂ��_���[�W�ǉ����� */
	if(sd && mgd.damage > 0 && skill_num != NPC_EARTHQUAKE && skill_num != NPC_CANE_OF_EVIL_EYE) {
		cardfix = 100;
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

			// �J�[�h���ʂɂ�����X�L���̃_���[�W�����i���@�X�L���j
			if(sd->skill_dmgup.count > 0) {
				for(i=0; i<sd->skill_dmgup.count; i++) {
					if(skill_num == sd->skill_dmgup.id[i]) {
						rate += sd->skill_dmgup.rate[i];
						break;
					}
				}
			}
			// �J�[�h���ʂɂ����葮���X�L���̃_���[�W�����i���@�X�L���j
			rate += sd->skill_elemagic_dmgup[ele];
			cardfix = cardfix*rate/100;
		}
		mgd.damage = mgd.damage*cardfix/100;
	}
#endif

	/* �U�D�J�[�h�ɂ��_���[�W�������� */
	if(tsd && mgd.damage > 0 && skill_num != NPC_EARTHQUAKE && skill_num != NPC_CANE_OF_EVIL_EYE) {
		int s_class = status_get_class(bl);
		cardfix = 100;
		cardfix = cardfix*(100-tsd->subele[ele])/100;				// �����ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-tsd->def_eleenemy[status_get_elem_type(bl)])/100;				// �G�����ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-tsd->subenemy[status_get_enemy_type(bl)])/100;	// �G�^�C�v�ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-tsd->magic_subsize[status_get_size(bl)])/100;		// �T�C�Y�ɂ��_���[�W�ϐ�
		cardfix = cardfix*(100-tsd->magic_subrace[race])/100;
		cardfix = cardfix*(100-tsd->long_attack_def_rate)/100;	// �������ϐ��ɂ��_���[�W����
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
		if(mgd.damage < 1)	// �v���C���[�̖��@�X�L����1�_���[�W�ۏؖ���
			mgd.damage = (!battle_config.skill_min_damage && bl->type == BL_PC)? 0: 1;
	}
#endif

	if(mgd.damage < 0)
		mgd.damage = 0;

#ifndef PRE_RENEWAL
	if(t_sc && t_sc->data[SC_SPIDERWEB].timer != -1 && ele == ELE_FIRE && mgd.damage > 0 && normalmagic_flag) {	// �X�p�C�_�[�E�F�u
		mgd.damage <<= 1;
		status_change_end(bl, SC_SPIDERWEB, -1);
	}
#endif

	/* �V�D�����̓K�p */
	mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));

	/* �W�D�ΏۂɃX�e�[�^�X�ُ킪����ꍇ�̃_���[�W���Z���� */
	if( t_sc && mgd.damage > 0 && normalmagic_flag ) {
		cardfix = 100;

#ifndef PRE_RENEWAL
		// �{���P�[�m
		if(t_sc->data[SC_VOLCANO].timer != -1 && ele == ELE_FIRE)
			cardfix += t_sc->data[SC_VOLCANO].val4;
		// �o�C�I�����g�Q�C��
		if(t_sc->data[SC_VIOLENTGALE].timer != -1 && ele == ELE_WIND)
			cardfix += t_sc->data[SC_VIOLENTGALE].val4;
		// �f�����[�W
		if(t_sc->data[SC_DELUGE].timer != -1 && ele == ELE_FIRE)
			cardfix += t_sc->data[SC_DELUGE].val4;
#endif
		if(t_sc->data[SC_VENOMIMPRESS].timer != -1 && ele == ELE_POISON)		// �x�i���C���v���X
			cardfix += t_sc->data[SC_VENOMIMPRESS].val2;
		if(t_sc->data[SC_ORATIO].timer != -1 && ele == ELE_HOLY)		// �I���e�B�I
			cardfix += t_sc->data[SC_ORATIO].val1;
		if(t_sc->data[SC_SOULCURSE].timer != -1 && ele == ELE_DARK)		// ����߈�
			cardfix += t_sc->data[SC_SOULCURSE].val2;
		if(t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 && ele == ELE_EARTH)		// ����
			cardfix += t_sc->data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].val2;
		if(t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1 && ele == ELE_POISON)			// ����
			cardfix += t_sc->data[SC_HANDICAPSTATE_DEADLYPOISON].val2;
		if(t_sc->data[SC_CLIMAX_EARTH].timer != -1 && ele == ELE_EARTH)		// �N���C�}�b�N�X�N�G�C�N
			cardfix += t_sc->data[SC_CLIMAX_EARTH].val2;
		if(t_sc->data[SC_CLIMAX_BLOOM].timer != -1 && ele == ELE_FIRE)		// �N���C�}�b�N�X�u���[��
			cardfix += t_sc->data[SC_CLIMAX_BLOOM].val2;
		if(t_sc->data[SC_MISTYFROST].timer != -1 && ele == ELE_WATER)		// �W���b�N�t���X�g�m���@
			cardfix += t_sc->data[SC_MISTYFROST].val2;

		if(t_sc->data[SC_DEEP_SLEEP].timer != -1)		// �����̎q��S�i���Z�ł����̂��ȁH�j
			cardfix += 50;
		if(cardfix != 100) {
			mgd.damage = mgd.damage*cardfix/100;	// �X�e�[�^�X�ُ�␳�ɂ��_���[�W����
		}
	}

#ifndef PRE_RENEWAL
	if(sd && mgd.damage > 0 && normalmagic_flag) {
		cardfix = 100;
		// �iRE�j�J�[�h���ʂɂ�����X�L���̃_���[�W�����i���@�X�L���j
		if(sd->skill_dmgup.count > 0 && skill_num > 0) {
			for(i=0; i<sd->skill_dmgup.count; i++) {
				if(skill_num == sd->skill_dmgup.id[i]) {
					cardfix += sd->skill_dmgup.rate[i];
					break;
				}
			}
		}
		// �iRE�j�J�[�h���ʂɂ����葮���X�L���̃_���[�W�����i���@�X�L���j
		cardfix += sd->skill_elemagic_dmgup[ele];
		mgd.damage = mgd.damage*cardfix/100;
	}
#endif
#ifdef PRE_RENEWAL
	/* �X�D�X�L���C���P */
	if(skill_num == CR_GRANDCROSS || skill_num == NPC_GRANDDARKNESS) {	// �O�����h�N���X
		static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
		mgd.damage = (mgd.damage + wd.damage) * (100 + 40*skill_lv)/100;
		if(battle_config.gx_dupele)
			mgd.damage = battle_attr_fix(mgd.damage, ele, status_get_element(target));	// ����2�񂩂���
		if(bl == target) {
			if(bl->type & (BL_MOB | BL_HOM | BL_MERC | BL_ELEM))
				mgd.damage = 0;		// MOB,HOM,MERC,ELEM���g���ꍇ�͔�������
			else
				mgd.damage /= 2;	// �����͔���
		}
	}
#endif

	if(skill_num == NPC_RAYOFGENESIS && mgd.damage < 1)	// M���C�I�u�W�F�l�V�X
		mgd.damage = 1;

	if(skill_num == WZ_WATERBALL)
		mgd.div_ = 1;

	/* 10�D�ΏۂɃX�e�[�^�X�ُ킪����ꍇ */
	if(tsd && tsd->special_state.no_magic_damage)
		mgd.damage = 0;	// ����峃J�[�h�i���@�_���[�W�O)

	if(t_sc && t_sc->data[SC_HERMODE].timer != -1 && t_sc->data[SC_HERMODE].val1 == 1)	// �w�����[�h�Ȃ疂�@�_���[�W�Ȃ�
		mgd.damage = 0;

	if(skill_num == WL_SOULEXPANSION && t_sc && t_sc->data[SC_WHITEIMPRISON].timer != -1) {	// �\�E���G�N�X�p���V����
		status_change_end(target,SC_WHITEIMPRISON,-1);
		mgd.damage += mgd.damage;
	}

	/* 11�D�Œ�_���[�W */
	if(skill_num == HW_GRAVITATION) {	// �O���r�e�[�V�����t�B�[���h
#ifdef PRE_RENEWAL
		mgd.damage = 200+200*skill_lv;
#else
		mgd.damage = 500+100*skill_lv;
#endif
	}

	/* 12�D�q�b�g�񐔂ɂ��_���[�W�{�� */
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
			case NPC_RAYOFGENESIS:	/* M���C�I�u�W�F�l�V�X */
			case KO_KAIHOU:	/* �p�� -���- */
			case AG_SOUL_VC_STRIKE:		/* �\�E���o���J���X�g���C�N */
			case AG_CRYSTAL_IMPACT:		/* �N���X�^���C���p�N�g */
			case AG_CRIMSON_ARROW_ATK:		/* �N�����]���A���[(�U��) */
			case ABC_ABYSS_SQUARE:		/* �A�r�X�X�N�G�A */
			case EM_EL_AVALANCHE:		/* �A�o�����`�F */
			case EM_EL_DEADLY_POISON:	/* �f�b�h���[�|�C�Y�� */
			case SOA_TALISMAN_OF_FOUR_BEARING_GOD:	/* �l���_�� */
			case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* �l���܍s�w */
				if(t_mode&MD_PLANT) // ���E���̂���
					mgd.damage = mgd.div_;
				else
					mgd.damage *= mgd.div_;
				break;
			default:
				if(t_mode&MD_PLANT) {	 // ���E���̂���
					if(battle_config.skill_min_damage)
						mgd.damage = mgd.div_;
					else
						mgd.damage = 1;
				}
				break;
		}
	}

	/* 13�D�_���[�W�ŏI�v�Z */
	if(skill_num != ASC_BREAKER && skill_num != CR_ACIDDEMONSTRATION && skill_num != GN_FIRE_EXPANSION_ACID && skill_num != NPC_EARTHQUAKE)
		mgd.damage = battle_calc_damage(bl,target,mgd.damage,mgd.div_,skill_num,skill_lv,mgd.flag);

	/* 14�D���@�ł��I�[�g�X�y������(item_bonus) */
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

	/* 15�D���@�ł�HP/SP��(�������Ȃ�) */
	if(battle_config.magic_attack_drain && bl != target)
		battle_attack_drain(bl,mgd.damage,0,battle_config.magic_attack_drain_enable_type);

	/* 16�D�v�Z���ʂ̍ŏI�␳ */
	mgd.amotion = status_get_amotion(bl);
	mgd.dmotion = status_get_dmotion(target);
	mgd.damage2 = 0;
	mgd.type    = 0;

	return mgd;
}

/*==========================================
 * ���̑��_���[�W�v�Z
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

	// return�O�̏���������̂ŏ��o�͕��̂ݕύX
	if( bl == NULL || target == NULL || target->type == BL_PET ) {
		nullpo_info(NLP_MARK);
		return mid;
	}

	// �O���E���h�h���t�g�̂Ƃ���bl��ݒu�҂ɒu������
	if(bl->type == BL_SKILL) {
		unit = (struct skill_unit *)bl;
		if(unit && unit->group)
			bl = map_id2bl(unit->group->src_id);
	}

	sd  = BL_DOWNCAST( BL_PC, bl );
	tsd = BL_DOWNCAST( BL_PC, target );
	md  = BL_DOWNCAST( BL_MOB, bl );

	// �A�^�b�J�[
	int_ = status_get_int(bl);
	dex  = status_get_dex(bl);
	race = status_get_race(bl);
	ele  = skill_get_pl(skill_num);

	// �^�[�Q�b�g
	t_sc = status_get_sc(target);		// �Ώۂ̃X�e�[�^�X�ُ�

	if(sd) {
		sd->state.attack_type = BF_MISC;
		sd->state.arrow_atk = 0;
	}

	// �L���O�X�O���C�X
	if(skill_num != PA_PRESSURE && t_sc && t_sc->data[SC_KINGS_GRACE].timer != -1)
		return mid;

	/* �P�Dmid�\���̂̏����ݒ� */
	mid.div_      = skill_get_num(skill_num,skill_lv);
	mid.blewcount = skill_get_blewcount(skill_num,skill_lv);
	mid.flag      = BF_MISC|BF_SHORT|BF_SKILL;

	/* �Q�D��{�_���[�W�v�Z(�X�L�����Ƃɏ���) */
	switch(skill_num)
	{
#ifdef PRE_RENEWAL
	case HT_LANDMINE:	// �����h�}�C��
	case MA_LANDMINE:
		mid.damage = skill_lv*(dex+75)*(100+int_)/100;
		break;
	case HT_BLASTMINE:	// �u���X�g�}�C��
		mid.damage = skill_lv*(dex/2+50)*(100+int_)/100;
		break;
	case HT_CLAYMORETRAP:	// �N���C���A�g���b�v
		mid.damage = skill_lv*(dex/2+75)*(100+int_)/100;
		break;
#else
	case HT_LANDMINE:	// �����h�}�C��
	case MA_LANDMINE:
	case HT_BLASTMINE:	// �u���X�g�}�C��
	case HT_CLAYMORETRAP:	// �N���C���A�g���b�v
		mid.damage = (int)(dex * (3+status_get_lv(bl)/(float)100) * (1+int_/(float)35) * skill_lv);
		mid.damage = (mid.damage * 90 / 100) + (mid.damage * (atn_rand()%20 + 1) / 100);
		if(sd)
			mid.damage += 40 * pc_checkskill(sd,RA_RESEARCHTRAP);
		break;
#endif

	case HT_BLITZBEAT:	// �u���b�c�r�[�g
		if(sd == NULL || (skill = pc_checkskill(sd,HT_STEELCROW)) <= 0)
			skill = 0;
		mid.damage = (dex/10 + int_/2 + skill*3 + 40)*2;
		if(flag > 1)
			mid.damage /= flag;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;

	case TF_THROWSTONE:	// �Γ���
		mid.damage = 50;
		damagefix = 0;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;

	case BA_DISSONANCE:	// �s���a��
		mid.damage = skill_lv * 20;
		if(sd)
			mid.damage += pc_checkskill(sd,BA_MUSICALLESSON)*3;
		break;
	case NPC_SELFDESTRUCTION:	// ����
	case NPC_SELFDESTRUCTION2:	// ����2
		mid.damage = status_get_hp(bl)-((bl == target)? 1: 0);
		break;

	case NPC_DARKBREATH:
		{
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
	case NPC_MAXPAIN_ATK:		/* �}�b�N�X�y�C�� */
		{
			struct status_change *sc = status_get_sc(bl);
			if(sc && sc->data[SC_MAXPAIN].timer != -1)
				mid.damage = sc->data[SC_MAXPAIN].val2;
			else
				mid.damage = 0;
			damagefix = 0;
		}
		break;
	case NPC_MAGMA_ERUPTION_DOTDAMAGE:	/* M�}�O�}�C���v�V����(�ǌ�) */
		mid.damage = 1000 * skill_lv;
		damagefix = 0;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_SHORT|BF_WEAPON;
		break;
	case PA_PRESSURE:		// �v���b�V���[
		mid.damage = 500 + 300 * skill_lv;
		damagefix = 0;
		break;
	case NPC_KILLING_AURA:	// �L�����O�I�[��
		mid.damage = 100000;
		damagefix = 0;
		mid.damage = battle_attr_fix(mid.damage, ele, status_get_element(target));
		break;
	case SN_FALCONASSAULT:		// �t�@���R���A�T���g
		if(sd == NULL || (skill = pc_checkskill(sd,HT_STEELCROW)) <= 0)
			skill = 0;
		if (md && mobdb_search(md->class_)->mode_opt[MDOPT_STEELCROW])
			skill = mobdb_search(md->class_)->mode_opt[MDOPT_STEELCROW];
		mid.damage = ((dex/10+int_/2+skill*3+40)*2*(150+skill_lv*70)/100)*5;
		if(sd) {
			if(battle_config.allow_falconassault_elemet) {
				ele = sd->atk_ele;
			} else {
				// �ꎞ�I�Ƀt�@���R���A�T���g�̑�����t�^�����ɕύX����
				int e;
				if((e = status_get_attack_element_nw(&sd->bl)) != ELE_NEUTRAL)	// �����t�^
					ele = e;
				else if(sd->arrow_ele > ELE_NEUTRAL)	// ��̑���
					ele = sd->arrow_ele;
				else if((e = status_get_attack_element(&sd->bl)) != ELE_NEUTRAL) // ���푮��
					ele = e;
			}
		}
		flag &= ~(BF_WEAPONMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_LONG;
		break;
	case GS_GROUNDDRIFT:		// �O���E���h�h���t�g
		if(unit && unit->group)
		{
			ele = unit->group->val2;
			mid.damage = status_get_baseatk(bl);
		}
		break;
	case RA_CLUSTERBOMB:		// �N���X�^�[�{��
		{
			static struct Damage wd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			wd = battle_calc_weapon_attack(bl,target,skill_num,skill_lv,flag);
			mid.damage = wd.damage;
			mid.damage += ((dex * skill_lv + int_ * 5) * (150 + status_get_lv(bl)) / 100) * ((sd? pc_checkskill(sd,RA_RESEARCHTRAP): 5) * 20 / 50);
			mid.flag |= wd.flag;
			if(sd)
				mid.damage += 40 * pc_checkskill(sd,RA_RESEARCHTRAP);
		}
		break;
	case RA_FIRINGTRAP:			// �t�@�C�A�����O�g���b�v
	case RA_ICEBOUNDTRAP:		// �A�C�X�o�E���h�g���b�v
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
	case NC_MAGMA_ERUPTION_DOTDAMAGE:	/* �}�O�}�C���v�V����(�ǌ�) */
		mid.damage = 800 + 200 * skill_lv;
		damagefix = 0;
		flag &= ~(BF_SKILLMASK|BF_RANGEMASK|BF_WEAPONMASK);
		mid.flag = flag|(mid.flag&~BF_RANGEMASK)|BF_SHORT|BF_WEAPON;
		break;
	case GN_THORNS_TRAP:		// �\�[���g���b�v
		mid.damage = 100 + 200 * skill_lv + int_;
		damagefix = 0;
		break;
	case GN_BLOOD_SUCKER:		// �u���b�h�T�b�J�[
		mid.damage = 200 + 100 * skill_lv + int_;
		damagefix = 0;
		break;
	case GN_HELLS_PLANT_ATK:	// �w���Y�v�����g
		mid.damage = 10 * skill_lv * status_get_lv(target) + 7 * int_ / 2 * (18 + status_get_jlv(target) / 4) * 5 / (10 - ((sd)? pc_checkskill(sd,AM_CANNIBALIZE) : 5));
		mid.damage = battle_attr_fix(mid.damage, ELE_NEUTRAL, status_get_element(target));
		damagefix = 0;
		break;
	case RL_B_FLICKER_ATK:		// �o�C���h�g���b�v(����)
		mid.damage = status_get_dex(bl) * 10 + status_get_hp(target) * 3 * skill_lv / 100;
		break;
	case SP_SOULEXPLOSION:		// ���̕���
		mid.damage = status_get_hp(target)*80/100;
		damagefix = 0;
		break;
	case SU_SV_ROOTTWIST_ATK:	// �}�^�^�r�̍�����(�U��)
		mid.damage = 100;
		damagefix = 0;
		break;
	case HVAN_EXPLOSION:		// �o�C�I�G�N�X�v���[�W����
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

		/* �R�D�J�[�h�ɂ��_���[�W�������� */
		if(tsd && mid.damage > 0) {
			int cardfix = 100;
			cardfix = cardfix*(100-tsd->subele[ele])/100;	// �����ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-tsd->def_eleenemy[status_get_elem_type(bl)])/100;	// �G�����ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-tsd->subrace[race])/100;	// �푰�ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-tsd->subenemy[status_get_enemy_type(bl)])/100;	// �G�^�C�v�ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-tsd->subsize[status_get_size(bl)])/100;	// �T�C�Y�ɂ��_���[�W�ϐ�
			cardfix = cardfix*(100-tsd->misc_def_rate)/100;
			mid.damage = mid.damage*cardfix/100;
		}
		if(mid.damage < 0)
			mid.damage = 0;

		if(skill_num == SN_FALCONASSAULT) {
			if(sd && !battle_config.allow_falconassault_elemet) {
				// �t�@���R���A�T���g�̑��������ɖ߂�
				ele = skill_get_pl(skill_num);
			}
		}

		/* �S�D�����̓K�p */
		mid.damage = battle_attr_fix(mid.damage, ele, status_get_element(target));

		/* �T�D�X�L���C�� */
		if(skill_num == GS_GROUNDDRIFT) {	// �Œ�_���[�W�����Z���Ă���ɖ������Ƃ��đ����v�Z����
			mid.damage += skill_lv*50;
			mid.damage = battle_attr_fix(mid.damage, ELE_NEUTRAL, status_get_element(target));
		}

	}

	/* �U�D�q�b�g�񐔂ɂ��_���[�W�{�� */
	if(mid.div_ > 1)
		mid.damage *= mid.div_;
	if( mid.damage > 0 && (mid.damage < mid.div_ || (status_get_def(target) >= 1000000 && status_get_mdef(target) >= 1000000)) ) {
		mid.damage = mid.div_;
	}

	/* �V�D�Œ�_���[�W */
	if(status_get_mode(target)&MD_PLANT && mid.damage > 0)	// ���E���̂���
		mid.damage = 1;

	/* �W�D�J�[�h�ɂ��_���[�W�ǉ����� */
	if(sd && sd->skill_dmgup.count > 0 && skill_num > 0 && mid.damage > 0) {	// �J�[�h���ʂɂ�����X�L���̃_���[�W����
		int i;
		for(i=0; i<sd->skill_dmgup.count; i++) {
			if(skill_num == sd->skill_dmgup.id[i]) {
				mid.damage += mid.damage * sd->skill_dmgup.rate[i] / 100;
				break;
			}
		}
	}

	/* �X�D�_���[�W�ŏI�v�Z */
	mid.damage = battle_calc_damage(bl,target,mid.damage,mid.div_,skill_num,skill_lv,mid.flag);

	/* 10�Dmisc�ł��I�[�g�X�y������(bonus) */
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

	/* 11�Dmisc�ł�HP/SP��(�������Ȃ�) */
	if(bl != target)
	{
		// �t�@�C�A�����O�g���b�v�ƃA�C�X�o�E���h�g���b�v�͉񕜂���
		if(skill_num == RA_FIRINGTRAP || skill_num == RA_ICEBOUNDTRAP)
			battle_attack_drain(bl,mid.damage,0,3);
		// ���̑��͐ݒ莟��
		else if(battle_config.misc_attack_drain)
			battle_attack_drain(bl,mid.damage,0,battle_config.misc_attack_drain_enable_type);
	}

	/* 12�D�v�Z���ʂ̍ŏI�␳ */
	mid.amotion = status_get_amotion(bl);
	mid.dmotion = status_get_dmotion(target);
	mid.damage2 = 0;
	mid.type    = 0;

	return mid;
}

/*==========================================
 * �_���[�W�v�Z�ꊇ�����p
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
 * �ʏ�U�������܂Ƃ�
 *------------------------------------------
 */
int battle_weapon_attack( struct block_list *src,struct block_list *target,unsigned int tick,int flag)
{
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change *sc, *t_sc;
	atn_bignumber damage,rsdamage = 0,ridamage = 0;
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

	// �E�H�[�O���C�_�[��
	if(sd && pc_iswolfmount(sd)) {
		unit_stopattack(src);
		clif_msgstringtable(sd, 0x75d);	// �R�搶���ɋR�撆�́A�U�����ł��܂���B
		return 0;
	}

	// �����̏�Ԉُ�
	if(sc && (
		sc->data[SC_BLADESTOP].timer != -1 ||		// ���H���
		sc->data[SC_FORCEWALKING].timer != -1 ||	// �����ړ�
		(sc->data[SC_WINKCHARM].timer != -1 && sc->data[SC_WINKCHARM].val2 == target->id) ||	// ���f�̃E�B���N
		sc->data[SC__SHADOWFORM].timer != -1 ||		// �V���h�E�t�H�[��
		sc->data[SC__MANHOLE].timer != -1 ||		// �}���z�[��
		sc->data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// �����w(�g�p��)
		sc->data[SC_CURSEDCIRCLE].timer != -1 ||		// �����w
		(sc->data[SC_SIREN].timer != -1 && sc->data[SC_SIREN].val2 == target->id) ||		// �Z�C���[���̐�
		sc->data[SC_DEEP_SLEEP].timer != -1 ||		// ���炬�̎q��S
		sc->data[SC_DIAMONDDUST].timer != -1 ||		// �_�C�������h�_�X�g
		sc->data[SC_SUHIDE].timer != -1			// �������
	)) {
		unit_stopattack(src);
		return 0;
	}

	// ����̏�Ԉُ�
	if(t_sc && (
		t_sc->data[SC_FORCEWALKING].timer != -1 ||	// �����ړ�
		t_sc->data[SC__MANHOLE].timer != -1			// �}���z�[��
	)) {
		unit_stopattack(src);
		return 0;
	}

	if(battle_check_target(src,target,BCT_ENEMY) <= 0 && !battle_check_range(src,target,0))
		return 0;	// �U���ΏۊO

	// �^�[�Q�b�g��MOB GM�n�C�h���ŁA�R���t�B�O�Ńn�C�h���U���s�� GM���x�����w����傫���ꍇ
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

	// �O�i��
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
		if(t_sc && t_sc->data[SC_MAXPAIN].timer != -1) {
			t_sc->data[SC_MAXPAIN].val2 = BIGNUM2INT(damage * (t_sc->data[SC_MAXPAIN].val1 * 10) / 100);
			skill_castend_damage_id(target, target, NPC_MAXPAIN_ATK, t_sc->data[SC_MAXPAIN].val1, tick, 0);
			t_sc->data[SC_MAXPAIN].val2 = 0;
			wd.damage  = 0;
			wd.damage2 = 0;
		}
		else if(t_sc && t_sc->data[SC_REFLECTDAMAGE].timer != -1 && atn_rand()%100 < 30 + t_sc->data[SC_REFLECTDAMAGE].val1 * 10) {	// ���t���N�g�_���[�W����
			atn_bignumber maxdamage, rddamage;
			int ar = skill_get_area(LG_REFLECTDAMAGE,t_sc->data[SC_REFLECTDAMAGE].val1);
			maxdamage = (atn_bignumber)status_get_max_hp(target) * status_get_lv(target) / 100;
			rddamage = damage * t_sc->data[SC_REFLECTDAMAGE].val3 / 100;
			rddamage = (rddamage > maxdamage) ? maxdamage: rddamage;
			// ���ˑϐ��A�ʒu�͉��ł�
			// �U���҂̔��ˑϐ��Q�ƂŊg�U�_���[�W�����肷��H
			if(sd && sd->sub_return_damage && rddamage > 0)
				rddamage = rddamage * (100 - sd->sub_return_damage) / 100;

			map_foreachinarea(battle_damage_area,target->m,
				target->x-ar,target->y-ar,target->x+ar,target->y+ar,BL_CHAR,
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
			   (sd || t_sc->data[SC_DEVOTION].timer == -1))	// ��f�B�{�[�V�����҂Ȃ�PC����ȊO�͔������Ȃ�
			{
				rsdamage += damage * t_sc->data[SC_REFLECTSHIELD].val2 / 100;
#ifndef PRE_RENEWAL
				if(rsdamage > status_get_max_hp(target))
					rsdamage = status_get_max_hp(target);
#endif
				// ���ˑϐ�
				if(sd && sd->sub_return_damage && rsdamage > 0)
					rsdamage = rsdamage * (100 - sd->sub_return_damage) / 100;
			}
			// �f�X�o�E���h����
			if(t_sc && t_sc->data[SC_DEATHBOUND].timer != -1 && !(status_get_mode(src)&MD_BOSS) && path_check_dir(path_calc_dir(src,target->x,target->y),status_get_dir(target)))
			{
				rsdamage += (damage * t_sc->data[SC_DEATHBOUND].val2 * 7) / 1000;	// 7�����˃_���[�W
				wd.damage = (damage * t_sc->data[SC_DEATHBOUND].val2 * 3) / 1000;	// 3�����g���󂯂�
				clif_skill_damage(target, src, tick, wd.amotion, wd.dmotion, rsdamage, 0, RK_DEATHBOUND, t_sc->data[SC_DEATHBOUND].val1, 1);
				clif_skill_nodamage(target, target, RK_DEATHBOUND, t_sc->data[SC_DEATHBOUND].val1, 1);
				skill_blown(target, src, skill_get_blewcount(RK_DEATHBOUND, t_sc->data[SC_DEATHBOUND].val1) | SAB_NODAMAGE);
				status_change_end(target,SC_DEATHBOUND,-1);
			}
			// �V�[���h�X�y��(DEF)
			if(t_sc && t_sc->data[SC_SHIELDSPELL_DEF].timer != -1 && t_sc->data[SC_SHIELDSPELL_DEF].val2 == 1)
			{
				rsdamage += damage * t_sc->data[SC_SHIELDSPELL_DEF].val3 / 100;
			}
			// �C���X�s���[�V����
			if(sc && sc->data[SC_INSPIRATION].timer != -1)
			{
				rsdamage += damage / 100;
			}
			// �j�ꒌ����
			if(t_sc && t_sc->data[SC_CRESCENTELBOW].timer != -1 && !(status_get_mode(src)&MD_BOSS) && atn_rand()%100 < t_sc->data[SC_CRESCENTELBOW].val2)
			{
				static struct Damage tmpwd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				int lv = t_sc->data[SC_CRESCENTELBOW].val1;
				int dist = unit_distance(target,src);
				status_change_end(target,SC_CRESCENTELBOW,-1);
				rsdamage += damage + (damage * 20 * lv / 100);
				tmpwd = battle_calc_weapon_attack(target,src,SR_CRESCENTELBOW_AUTOSPELL,lv,flag);
				rsdamage += tmpwd.damage;
				wd.damage = rsdamage / 10;
				// ���ˑϐ�
				if(tsd && tsd->sub_return_damage && wd.damage > 0)
					wd.damage = wd.damage * (100 - tsd->sub_return_damage) / 100;
				skill_blown(target,src,skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,lv)|SAB_NODAMAGE);
				if(unit_distance(target,src) < skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,lv) + dist) {
					skill_addtimerskill(target,tick+200,src->id,0,0,SR_CRESCENTELBOW,lv,tick,(0x0f<<20)|0x0500);
				}
			}
			// ���B�S�[��
			if(sc && sc->data[SC_VIGOR].timer != -1 && wd.flag&BF_SHORT) {
				rsdamage += 100 * sc->data[SC_VIGOR].val1;
			}
		} else if(wd.flag&BF_LONG) {
			if(tsd && tsd->long_weapon_damage_return > 0) {
				ridamage += damage * tsd->long_weapon_damage_return / 100;
			}
		}
		// �A�C�e�����ʂɑ΂��锽�ˑϐ�
		if(sd && sd->sub_return_damage && ridamage > 0)
			ridamage = ridamage * (100 - sd->sub_return_damage) / 100;
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

	// �񓁗�����ƃJ�^�[���ǌ��̃~�X�\��(�������`)
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

	/* ��Ԉُ� */
	if(sc) {
		// �I�[�g�X�y��
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
				if(sc->data[SC_SAGE].timer != -1)	// �Z�[�W�̍�
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
					case 2:	/* �U���n */
						fail = skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
						break;
					case 1:	/* �x���n */
						if( (spellid == AL_HEAL || (spellid == ALL_RESURRECTION && target->type != BL_PC)) &&
						    battle_check_undead(status_get_race(target),status_get_elem_type(target)) )
							fail = skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
						else
							fail = skill_castend_nodamage_id(src,target,spellid,spelllv,tick,flag);
						break;
					}
				}
				if(sd && !fail)
					pc_heal(sd,0,-sp,0,0);
			}
		}

		// �f���v�����C�g
		if(sc->data[SC_DUPLELIGHT].timer != -1) {
			int skill;
			// �y�e�B�e�B�I
			if(sd && (skill = pc_checkskill(sd,CD_PETITIO)) > 0 && (sd->status.weapon == WT_MACE || sd->status.weapon == WT_BOOK)) {
				if(atn_rand()%100 < skill) {
					skill_castend_damage_id(src,target,CD_PETITIO,skill,tick,flag);
				}
			}
			if(atn_rand()%100 < sc->data[SC_DUPLELIGHT].val2) {
				skill_addtimerskill(src,tick+status_get_adelay(src) / 2,target->id,0,0,AB_DUPLELIGHT_MELEE,sc->data[SC_DUPLELIGHT].val1,tick,flag);
			}
			else if(atn_rand()%100 < sc->data[SC_DUPLELIGHT].val3) {
				skill_addtimerskill(src,tick+status_get_adelay(src) / 2,target->id,0,0,AB_DUPLELIGHT_MAGIC,sc->data[SC_DUPLELIGHT].val1,tick,flag);
			}
		}

		// �V���h�E�I�[�g�X�y��
		if(sc->data[SC__AUTOSHADOWSPELL].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%100 < sc->data[SC__AUTOSHADOWSPELL].val4) {
			int spellid = sc->data[SC__AUTOSHADOWSPELL].val2;
			int spelllv = sc->data[SC__AUTOSHADOWSPELL].val3;

			if(skill_get_inf(spellid) & INF_GROUND) {
				skill_castend_pos2(src,target->x,target->y,spellid,spelllv,tick,flag);
			} else {
				switch(skill_get_nk(spellid) & 3) {
				case 0:
				case 2:	/* �U���n */
					skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
					break;
				case 1:	/* �x���n */
					if( (spellid == AL_HEAL || (spellid == ALL_RESURRECTION && target->type != BL_PC)) &&
					    battle_check_undead(status_get_race(target),status_get_elem_type(target)) )
						skill_castend_damage_id(src,target,spellid,spelllv,tick,flag);
					else
						skill_castend_nodamage_id(src,target,spellid,spelllv,tick,flag);
					break;
				}
			}
		}

		// �f�b�h���[�C���t�F�N�g
		if(sc->data[SC__DEADLYINFECT].timer != -1 && (wd.damage > 0 || wd.damage2 > 0)) {
			status_change_copy(src,target);
		}

		// �_�� -��-
		if(sd && sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1 && atn_rand()%100 < sc->data[SC_GENTLETOUCH_ENERGYGAIN].val2 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? pc_checkskill(sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sc->data[SC_RAISINGDRAGON].timer != -1)
				max += sc->data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num < max)
				pc_addspiritball(sd,skill_get_time2(SR_GENTLETOUCH_ENERGYGAIN,sc->data[SC_GENTLETOUCH_ENERGYGAIN].val1),1);
		}

		// �g���s�b�N
		if(sc->data[SC_TROPIC].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_FIREBOLT,5,tick,flag);
		}

		// �N�[���G�A�[
		if(sc->data[SC_CHILLY_AIR].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_COLDBOLT,5,tick,flag);
		}

		// ���C���h�X�g�[��
		if(sc->data[SC_WILD_STORM].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,MG_LIGHTNINGBOLT,5,tick,flag);
		}

		// �A�b�v�w�C�o��
		if(sc->data[SC_UPHEAVAL].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			skill_castend_damage_id(src,target,WZ_EARTHSPIKE,5,tick,flag);
		}
		// ��������
		if (sc->data[SC_FALLINGSTAR].timer != -1 && (wd.flag&BF_WEAPON) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%100 < sc->data[SC_FALLINGSTAR].val2) {
			skill_castend_damage_id(src, target, SJ_FALLINGSTAR_ATK, sc->data[SC_FALLINGSTAR].val1, tick, flag);
		}
		// ���̎��n
		if(sd && sc->data[SC_SOULREAPER].timer != 1 && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%100 < sc->data[SC_SOULREAPER].val2) {
			pc_addsoulenergy(sd,600000,1);
		}
		// �T�[���@���g�E�F�|��
		if(sd && sc->data[SC_SERVANTWEAPON].timer != -1 && sd->ball.num > 0 && atn_rand()%100 < sc->data[SC_SERVANTWEAPON].val2) {
			skill_castend_damage_id(src,target,DK_SERVANTWEAPON_ATK,sc->data[SC_SERVANTWEAPON].val1,tick,flag);
			pc_delball(sd,1,0);
		}
		// �t�����W�A�r�X
		if(sd && sc->data[SC_ABYSSFORCEWEAPON].timer != -1) {
			int skill;
			if(sd->ball.num > 0 && atn_rand()%100 < sc->data[SC_ABYSSFORCEWEAPON].val2) {
				skill_castend_damage_id(src,target,ABC_FROM_THE_ABYSS_ATK,sc->data[SC_ABYSSFORCEWEAPON].val1,tick,flag);
				pc_delball(sd,1,0);
			}
			if((skill = pc_checkskill(sd,ABC_ABYSS_SQUARE)) > 0 && atn_rand()%100 < sc->data[SC_ABYSSFORCEWEAPON].val1) {
				skill_castend_pos2(src,target->x,target->y,ABC_ABYSS_SQUARE,skill,tick,flag);
			}
		}
		// �t���C���e�N�j�b�N
		if(sc->data[SC_FLAMETECHNIC].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			int skill;
			if(sd && ((skill = pc_checkskill(sd,MG_FIREBOLT)) > 0)) {
				skill_castend_damage_id(src,target,MG_FIREBOLT,skill,tick,flag);
			} else {
				skill_castend_damage_id(src,target,MG_FIREBOLT,1,tick,flag);
			}
		}
		// �R�[���h�t�H�[�X
		if(sc->data[SC_COLD_FORCE].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			int skill;
			if(sd && ((skill = pc_checkskill(sd,MG_COLDBOLT)) > 0)) {
				skill_castend_damage_id(src,target,MG_COLDBOLT,skill,tick,flag);
			} else {
				skill_castend_damage_id(src,target,MG_COLDBOLT,1,tick,flag);
			}
		}
		// �O���C�X�u���[�Y
		if(sc->data[SC_GRACE_BREEZE].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			int skill;
			if(sd && ((skill = pc_checkskill(sd,MG_LIGHTNINGBOLT)) > 0)) {
				skill_castend_damage_id(src,target,MG_LIGHTNINGBOLT,skill,tick,flag);
			} else {
				skill_castend_damage_id(src,target,MG_LIGHTNINGBOLT,1,tick,flag);
			}
		}
		// �A�[�X�P�A
		if(sc->data[SC_EARTH_CARE].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			int skill;
			if(sd && ((skill = pc_checkskill(sd,WZ_EARTHSPIKE)) > 0)) {
				skill_castend_damage_id(src,target,WZ_EARTHSPIKE,skill,tick,flag);
			} else {
				skill_castend_damage_id(src,target,WZ_EARTHSPIKE,1,tick,flag);
			}
		}
		// �f�B�[�v�|�C�Y�j���O
		if(sc->data[SC_DEEP_POISONING].timer != -1 && (wd.flag&BF_SHORT) && (wd.damage > 0 || wd.damage2 > 0) && atn_rand()%10000 < 2500) {
			int skill;
			if(sd && ((skill = pc_checkskill(sd,SO_POISON_BUSTER)) > 0)) {
				skill_castend_damage_id(src,target,SO_POISON_BUSTER,skill,tick,flag);
			} else {
				skill_castend_damage_id(src,target,SO_POISON_BUSTER,1,tick,flag);
			}
		}
		// �I�[�g�t�@�C�A�����O�����`���[
		if(sd && sc->data[SC_AUTO_FIRING_LAUNCHEREFST].timer != -1 && (wd.flag&BF_WEAPON) && (wd.damage > 0 || wd.damage2 > 0)) {
			int skill;
			if((skill = pc_checkskill(sd,NW_BASIC_GRENADE)) > 0 && atn_rand()%10000 < sc->data[SC_AUTO_FIRING_LAUNCHEREFST].val2) {
				skill_castend_damage_id(src,target,NW_BASIC_GRENADE,skill,tick,flag);
			} else if((skill = pc_checkskill(sd,NW_HASTY_FIRE_IN_THE_HOLE)) > 0 && atn_rand()%10000 < sc->data[SC_AUTO_FIRING_LAUNCHEREFST].val3) {
				skill_castend_pos2(src,target->x,target->y,NW_HASTY_FIRE_IN_THE_HOLE,skill,tick,flag);
			} else if((skill = pc_checkskill(sd,NW_GRENADES_DROPPING)) > 0 && atn_rand()%10000 < sc->data[SC_AUTO_FIRING_LAUNCHEREFST].val4) {
				skill_castend_pos2(src,target->x,target->y,NW_GRENADES_DROPPING,skill,tick,flag);
			}
		}
	}

	// �J�[�h�ɂ��I�[�g�X�y��
	if(sd && target != &sd->bl && (wd.damage > 0 || wd.damage2 > 0))
	{
		unsigned int asflag = EAS_ATTACK | EAS_NORMAL;
		unsigned int astick = gettick();

		if(wd.flag&BF_LONG)
			asflag += EAS_LONG;
		else
			asflag += EAS_SHORT;

		bonus_autospell_start(&sd->bl,target,asflag,astick,0);
		bonus_activeitem_start(sd,asflag,astick);
	}

	if(sd && target != &sd->bl && wd.flag&BF_WEAPON && (wd.damage > 0 || wd.damage2 > 0))
	{
		// SP����
		if(tsd && atn_rand()%100 < sd->sp_vanish.rate)
		{
			int sp = status_get_sp(target) * sd->sp_vanish.per/100;
			if(sp > 0)
				pc_heal(tsd, 0, -sp,0,0);
		}
	}

	if(sd && target != &sd->bl && wd.flag&BF_WEAPON && (wd.damage > 0 || wd.damage2 > 0)) {
		// ���z���A���z���Ƃ���
		battle_attack_drain(src, wd.damage, wd.damage2, 3);
	}

	if(rsdamage > 0) {
		battle_delay_damage(tick+wd.amotion,target,src,rsdamage,0,0,0);

		// �X�L���̔��˃_���[�W�̃I�[�g�X�y��
		if(battle_config.weapon_reflect_autospell && target->type == BL_PC && atn_rand()%2)
			bonus_autospell_start(target,src,EAS_ATTACK,tick,0);

		if(battle_config.weapon_reflect_drain && src != target)
			battle_attack_drain(target,rsdamage,0,battle_config.weapon_reflect_drain_enable_type);

		// �X�L���̔��˃_���[�W�̃A�N�e�B�u�A�C�e��
		if(battle_config.weapon_reflect_autospell && tsd)
			bonus_activeitem_start(tsd,EAS_ATTACK,tick);
	}
	if(ridamage > 0) {
		battle_delay_damage(tick+wd.amotion,target,src,ridamage,0,0,0);

		// �A�C�e���̔��˃_���[�W�̃I�[�g�X�y��
		if(battle_config.weapon_reflect_autospell && target->type == BL_PC && atn_rand()%2)
			bonus_autospell_start(target,src,EAS_ATTACK,tick,0);

		if(battle_config.weapon_reflect_drain && src != target)
			battle_attack_drain(target,ridamage,0,battle_config.weapon_reflect_drain_enable_type);

		// �A�C�e���̔��˃_���[�W�̃A�N�e�B�u�A�C�e��
		if(battle_config.weapon_reflect_autospell && tsd)
			bonus_activeitem_start(tsd,EAS_ATTACK,tick);
	}

	// �ΏۂɃX�e�[�^�X�ُ킪����ꍇ
	if(t_sc && t_sc->count > 0)
	{
		if(t_sc->data[SC_AUTOCOUNTER].timer != -1 && t_sc->data[SC_AUTOCOUNTER].val4 > 0) {
			if(t_sc->data[SC_AUTOCOUNTER].val3 == src->id)
				battle_weapon_attack(target,src,tick,0x8000|t_sc->data[SC_AUTOCOUNTER].val1);
			status_change_end(target,SC_AUTOCOUNTER,-1);
		}
		if(t_sc->data[SC_BLADESTOP_WAIT].timer != -1 &&
		   !(status_get_mode(src)&MD_BOSS) &&
		   (map[target->m].flag.pvp || unit_distance(src,target) <= 2)) {	// PvP�ȊO�ł̗L���˒���2�Z��
			int lv  = t_sc->data[SC_BLADESTOP_WAIT].val1;
			int sec = skill_get_time2(MO_BLADESTOP,lv);
			status_change_end(target,SC_BLADESTOP_WAIT,-1);
			status_change_start(src,SC_BLADESTOP,lv,1,src->id,target->id,sec,0);
			status_change_start(target,SC_BLADESTOP,lv,2,target->id,src->id,sec,0);
		}
		if(t_sc->data[SC_POISONREACT].timer != -1) {
			if( (src->type == BL_MOB && status_get_elem_type(src) == ELE_POISON) || status_get_attack_element(src) == ELE_POISON ) {
				// �ő���mob�܂��͓ő����ɂ��U���Ȃ�Δ���
				if( battle_check_range(target,src,status_get_range(target)+1) ) {
					t_sc->data[SC_POISONREACT].val2 = 0;
					battle_skill_attack(BF_WEAPON,target,target,src,AS_POISONREACT,t_sc->data[SC_POISONREACT].val1,tick,0);
				}
			} else {
				// ����ȊO�̒ʏ�U���ɑ΂���C���x�����i�ː��`�F�b�N�Ȃ��j
				--t_sc->data[SC_POISONREACT].val2;
				if(atn_rand()&1) {
					if( tsd == NULL || pc_checkskill(tsd,TF_POISON) >= 5 )
						battle_skill_attack(BF_WEAPON,target,target,src,TF_POISON,5,tick,flag);
				}
			}
			if(t_sc->data[SC_POISONREACT].val2 <= 0)
				status_change_end(target,SC_POISONREACT,-1);
		}
		if(t_sc->data[SC_STONEHARDSKIN].timer != -1 && wd.flag&BF_WEAPON) {	// �X�g�[���n�[�h�X�L��
			t_sc->data[SC_STONEHARDSKIN].val3 -= BIGNUM2INT(wd.damage + wd.damage2);
			if(t_sc->data[SC_STONEHARDSKIN].val3 <= 0)
				status_change_end(target,SC_STONEHARDSKIN,-1);
			if(sd && atn_rand() % 10000 < 500) {
				pc_break_equip(sd, LOC_RARM);
			} else {
				status_change_start(src,SC_STRIPWEAPON,1,0,0,0,10000,0);
			}
		}
		if(t_sc->data[SC__DEADLYINFECT].timer != -1 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {	// �f�b�h���[�C���t�F�N�g
			status_change_copy(target,src);
		}
		if(t_sc->data[SC_CIRCLE_OF_FIRE].timer != -1 && wd.flag&BF_SHORT && (wd.damage > 0 || wd.damage2 > 0)) {	// �T�[�N���I�u�t�@�C�A
			battle_skill_attack(BF_WEAPON,target,target,src,EL_CIRCLE_OF_FIRE,t_sc->data[SC_CIRCLE_OF_FIRE].val1,tick,(0x0f<<20)|0x0500);
		}
		if(t_sc->data[SC_WINDSIGN].timer != -1 && atn_rand()%100 < t_sc->data[SC_WINDSIGN].val2 && sd && sd->s_class.job == PC_JOB_WH && sd->status.weapon == WT_BOW && (wd.damage > 0 || wd.damage2 > 0)) {	// �E�B���h�T�C��
			pc_heal(sd,0,0,1,0);
		}
	}

	map_freeblock_unlock();
	return wd.dmg_lv;
}

/*=========================================================================
 * �X�L���U�����ʏ����܂Ƃ�
 * flag�̐����B16�i�}
 * 	0XYRTTff
 *  ff = battle_calc_attack�Ŋe��v�Z�ɗ��p
 *  TT = �p�P�b�g��type�����i0�Ńf�t�H���g�j
 *   R = �\��iskill_area_sub�Ŏg�p���ꂽBCT_*�j
 *   Y = �p�P�b�g�̃X�L��Lv�if�̂Ƃ���-1�ɕϊ��j
 *   X = �G�t�F�N�g�݂̂Ń_���[�W�Ȃ��t���O
 *-------------------------------------------------------------------------
 */
int battle_skill_attack(int attack_type,struct block_list* src,struct block_list *dsrc,
	struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct Damage dmg;
	struct map_session_data *sd = NULL, *tsd = NULL;
	struct status_change *sc;
	struct status_change *ssc;
	atn_bignumber damage, rdamage = 0;
	int type, lv;

	nullpo_retr(0, src);
	nullpo_retr(0, dsrc);
	nullpo_retr(0, bl);

	sc  = status_get_sc(bl);
	ssc = status_get_sc(src);

	sd  = BL_DOWNCAST( BL_PC, src );
	tsd = BL_DOWNCAST( BL_PC, bl );

	if(dsrc->m != bl->m)	// �Ώۂ������}�b�v�ɂ��Ȃ���Ή������Ȃ�
		return 0;
	if(src->prev == NULL || dsrc->prev == NULL || bl->prev == NULL)
		return 0;
	if(unit_isdead(src) || unit_isdead(dsrc) || unit_isdead(bl))	// ���łɎ���ł����牽�����Ȃ�
		return 0;

	if(ssc) {		// �����̏�Ԉُ�
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
		if(sc->data[SC_HIDING].timer != -1 && !(status_get_mode(src)&MD_BOSS) && skill_get_pl(skillid) != ELE_EARTH && skillid != HW_GRAVITATION)	// �n�C�f�B���O��Ԃ�BOSS�łȂ��X�L���̑������n�����łȂ��O���r�e�[�V�����t�B�[���h�łȂ��Ȃ牽�����Ȃ�
			return 0;
		if(sc->data[SC_CHASEWALK].timer != -1 && skillid == AL_RUWACH)	// �`�F�C�X�E�H�[�N��ԂŃ��A�t����
			return 0;
		if(sc->data[SC_TRICKDEAD].timer != -1) 				// ���񂾂ӂ蒆�͉������Ȃ�
			return 0;
		if(sc->data[SC_FORCEWALKING].timer != -1) 			// �����ړ����͉������Ȃ�
			return 0;
		// ������ԂŃX�g�[���K�X�g�A�t���X�g�m���@�A�X�՗��͖���
		if(sc->data[SC_FREEZE].timer != -1 && (skillid == WZ_STORMGUST || skillid == WZ_FROSTNOVA || skillid == NJ_HYOUSYOURAKU))
			return 0;
		if(sc->data[SC__MANHOLE].timer != -1) 			// �}���z�[�����͉������Ȃ�
			return 0;
	}
	if(sd && sd->chatID)	// ��������PC�Ń`���b�g���Ȃ牽�����Ȃ�
		return 0;

	type = (flag >> 8) & 0xff;
	if(skillid == 0)
		type = 5;

	/* ��̏��� */
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
				case RL_S_STORM:	/* �V���b�^�[�X�g�[�� */
				case RL_QD_SHOT:	/* �N�C�b�N�h���[�V���b�g */
				case RL_FIREDANCE:	/* �t�@�C�A�[�_���X */
				case RL_R_TRIP:		/* ���E���h�g���b�v */
				case KO_HAPPOKUNAI:
				case ABC_CHAIN_REACTION_SHOT:	/* �`�F�[�����A�N�V�����V���b�g */
				case ABC_CHAIN_REACTION_SHOT_ATK:	/* �`�F�[�����A�N�V�����V���b�g(�U��) */
				case WH_CALAMITYGALE:		/* �J���~�e�B�Q�C�� */
				case NW_THE_VIGILANTE_AT_NIGHT:		/* �r�W�����g�A�b�g�i�C�g */
				case NW_SPIRAL_SHOOTING:	/* �X�p�C�����V���[�e�B���O */
				case NW_WILD_FIRE:			/* ���C���h�t�@�C�A */
				case SS_KUNAIWAIKYOKU:		/* �ꖳ -�c��- */
				case SS_KUNAIKAITEN:		/* �ꖳ -��]- */
				// ���ɏ�����͊������Ă���̂ŏ��O
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

	/* �t���O�l�`�F�b�N */
	lv = (flag >> 20) & 0x0f;
	if(lv == 0)
		lv = skilllv;
	else if(lv == 0x0f)
		lv = -1;

	if(flag & 0x01000000) {	// �G�t�F�N�g�����o���ă_���[�W�Ȃ��ŏI��
		clif_skill_damage(dsrc, bl, tick, status_get_amotion(src), 0, -1, 1, skillid, lv, type);
		return -1;
	}

	/* �_���[�W�v�Z */
#ifdef PRE_RENEWAL
	dmg = battle_calc_attack(attack_type,(skillid == GS_GROUNDDRIFT)? dsrc: src,bl,skillid,skilllv,flag&0xff);
#else
	dmg = battle_calc_attack(attack_type,src,bl,skillid,skilllv,flag&0xff);
#endif

	/* �}�W�b�N���b�h */
	if(attack_type&BF_MAGIC && sc && sc->data[SC_MAGICROD].timer != -1 && src == dsrc) {
		dmg.damage = dmg.damage2 = 0;
		if(tsd) {	// �Ώۂ�PC�̏ꍇ
			int sp = skill_get_sp(skillid,skilllv);		// �g�p���ꂽ�X�L����SP���z��
			sp = sp * sc->data[SC_MAGICROD].val2 / 100;
			if(skillid == WZ_WATERBALL && skilllv > 1)
				sp = sp/((skilllv|1)*(skilllv|1));	// �E�H�[�^�[�{�[���͂���Ɍv�Z�H
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
		clif_skill_nodamage(bl,bl,SA_MAGICROD,sc->data[SC_MAGICROD].val1,1);	// �}�W�b�N���b�h�G�t�F�N�g��\��
	}

	damage = dmg.damage + dmg.damage2;

	if(damage <= 0 || damage < dmg.div_)	// ������΂�����
		dmg.blewcount = 0;

	if(skillid == CR_GRANDCROSS || skillid == NPC_GRANDDARKNESS) {	// �O�����h�N���X
		if(battle_config.gx_disptype)
			dsrc = src;	// �G�_���[�W�������\��
		if(src == bl)
			type = 4;	// �����̓_���[�W���[�V�����Ȃ�
	}

	// �_���[�W�v�Z��X�L�����Ƃ̕t�^����
	switch(skillid) {
	case KN_PIERCE:				// �s�A�[�X
	case LK_SPIRALPIERCE:		// �X�p�C�����s�A�[�X
	case RK_HUNDREDSPEAR:		// �n���h���b�h�X�s�A
	case DK_MADNESS_CRUSHER:	// �}�b�h�l�X�N���b�V���[
		if(ssc && ssc->data[SC_CHARGINGPIERCE].timer != -1) {		// �`���[�W���O�X�s�A
			if(ssc->data[SC_CHARGINGPIERCE_COUNT].timer == -1) {
				status_change_start(src,SC_CHARGINGPIERCE_COUNT,1,1,1,1,skill_get_time2(DK_CHARGINGPIERCE,1),0);
			} else if(ssc->data[SC_CHARGINGPIERCE_COUNT].val1 < 10) {
				status_change_start(src,SC_CHARGINGPIERCE_COUNT,ssc->data[SC_CHARGINGPIERCE_COUNT].val1+1,1,1,1,skill_get_time2(DK_CHARGINGPIERCE,1),0);
			} else {
				status_change_end(src,SC_CHARGINGPIERCE_COUNT,-1);
			}
		}
		break;
	case DK_SERVANT_W_DEMOL:	// �T�[���@���g�E�F�|���F�f�����b�V����
		if(sd)
			pc_addball(sd,600000,1);
		break;
	}

	/* �R���{ */
	if(sd) {
		int delay = 0;

		switch(skillid) {
		case MO_TRIPLEATTACK:	// �O�i��
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// �A�ŏ��A���Ռ��A�A�������擾����+300ms
				if((pc_checkskill(sd, MO_CHAINCOMBO) > 0) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��Ԃ̍Œ�ۏ�ǉ�
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
		case MO_CHAINCOMBO:	// �A�ŏ�
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// �җ����A���Ռ��A�A�������擾����+300ms
				if((pc_checkskill(sd, MO_COMBOFINISH) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��Ԃ̍Œ�ۏ�ǉ�
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
		case MO_COMBOFINISH:	// �җ���
			delay = 700 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ���C���e�����擾���C��4�ێ��������g����Ԏ���+300ms
				// ���Ռ��A�A�������擾����+300ms
				if((pc_checkskill(sd, MO_EXTREMITYFIST) > 0 && sd->spiritball.num >= 4 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) ||
				   (pc_checkskill(sd, CH_TIGERFIST) > 0 && sd->spiritball.num > 0) ||
				   (pc_checkskill(sd, CH_CHAINCRUSH) > 0 && sd->spiritball.num > 1))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��ԍŒ�ۏ�ǉ�
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
		case CH_TIGERFIST:	// ���Ռ�
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// �A�������擾����+300ms
				if(pc_checkskill(sd, CH_CHAINCRUSH) > 0) {
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��ԍŒ�ۏ�ǉ�
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
		case CH_CHAINCRUSH:	// �A������
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				// ���C���K�����C��1�ێ��������g�����f�B���C
				if(pc_checkskill(sd, MO_EXTREMITYFIST) > 0 && sd->spiritball.num >= 1 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
				{
					delay += (600+(skilllv/5)*200) * battle_config.combo_delay_rate /100;
					// �R���{���͎��ԍŒ�ۏ�ǉ�
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
			if(ranking_get_pc_rank(sd,RK_TAEKWON) > 0) {	// �e�R�������J�[�̓R���{���s
				delay = status_get_adelay(src);
				if(damage < status_get_hp(bl)) {
					delay += 2000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);	// eA����
					// TK�R���{���͎��ԍŒ�ۏ�ǉ�
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
		case SR_DRAGONCOMBO:	// �o���r
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl)) {
				 // �V���n�ԁA��㕕��x���K�����f�B���C
				if(pc_checkskill(sd, SR_SKYNETBLOW) > 0 || pc_checkskill(sd, SR_FALLENEMPIRE) > 0)
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��Ԃ̍Œ�ۏ�ǉ�
					if(delay < battle_config.combo_delay_lower_limits)
						delay = battle_config.combo_delay_lower_limits;
				}
				status_change_start(src,SC_COMBO,SR_DRAGONCOMBO,skilllv,0,0,delay,0);
			}
			if(delay > 0) {
				// �ŗL�f�B���C�ǉ�
				int nameid = skill_get_skilldb_id(SR_DRAGONCOMBO);
				if(nameid > 0) {
					sd->skillcooldown[nameid] = tick + delay;
					clif_skill_cooldown(sd, SR_DRAGONCOMBO, delay);
				}
				sd->ud.attacktarget = bl->id;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		case SR_FALLENEMPIRE:	// ��Z���x
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if(damage < status_get_hp(bl))
			{
				 // �j�C�擾���C��2�ێ����������g����ԁ@�܂��́@�����j�����擾���C��5�ێ�
				if( (pc_checkskill(sd, SR_TIGERCANNON) > 0 && sd->spiritball.num >= 2 && sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) ||
					(pc_checkskill(sd, SR_GATEOFHELL)  > 0 && sd->spiritball.num >= 5))
				{
					delay += 300 * battle_config.combo_delay_rate /100;
					// �R���{���͎��Ԃ̍Œ�ۏ�ǉ�
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
		case SJ_PROMINENCEKICK:	// �g���r
			delay = 1000 - 4 * status_get_agi(src) - 2 * status_get_dex(src);
			if( pc_checkskill(sd, SJ_SOLARBURST) )
			{
				delay += 300 * battle_config.combo_delay_rate /100;
				// �R���{���͎��Ԃ̍Œ�ۏ�ǉ�
				if(delay < battle_config.combo_delay_lower_limits)
					delay = battle_config.combo_delay_lower_limits;
			}
			status_change_start(src,SC_COMBO,skillid,skilllv,0,0,delay,0);
			if(delay > 0)
			{
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + delay;
				clif_combo_delay(src,delay);
			}
			break;
		}
	}
	if(src->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)src;

		if(hd) {
			switch(skillid) {
			case MH_SONIC_CRAW:			/* �\�j�b�N�N���[ */
			case MH_SILVERVEIN_RUSH:	/* �V���o�[�x�C�����b�V�� */
			case MH_TINDER_BREAKER:		/* �e�B���_�[�u���C�J�[ */
				if(hd->spiritball >= 1) {
					int delay = 1000;
					if(damage < status_get_hp(bl))
						status_change_start(src,SC_COMBO,skillid,skilllv,0,0,delay,0);
					clif_combo_delay(src,delay);
				}
				break;
			case MH_MIDNIGHT_FRENZY:	/* �~�b�h�i�C�g�t�����W */
			case MH_EQC:				/* E.Q.C */
				if(hd->spiritball >= 2) {
					int delay = 1000;
					if(damage < status_get_hp(bl))
						status_change_start(src,SC_COMBO,skillid,skilllv,0,0,delay,0);
					clif_combo_delay(src,delay);
				}
				break;
			}
		}
	}

	/* �_���[�W���� */
	if(sc && sc->data[SC_MAXPAIN].timer != -1 && damage > 0) {
		sc->data[SC_MAXPAIN].val2 = BIGNUM2INT(damage * (sc->data[SC_MAXPAIN].val1 * 10) / 100);
		skill_castend_damage_id(bl, bl, NPC_MAXPAIN_ATK, sc->data[SC_MAXPAIN].val1, tick, 0);
		sc->data[SC_MAXPAIN].val2 = 0;
		damage = 0;
		dmg.blewcount = 0;
	}
	if(attack_type&BF_WEAPON && damage > 0 && src != bl && (sc && sc->data[SC_KYOMU].timer == -1)) {	// ����X�L�����_���[�W���聕�g�p�҂ƑΏێ҂��Ⴄ�������̉e�ł͂Ȃ�
		if(src == dsrc || (dsrc->type == BL_SKILL && (skillid == SG_SUN_WARM || skillid == SG_MOON_WARM || skillid == SG_STAR_WARM || skillid == GS_DESPERADO))) {
			if(dmg.flag&BF_SHORT) {	// �ߋ����U����
				if(tsd) {	// �Ώۂ�PC�̎�
					if(tsd->short_weapon_damage_return > 0) {	// �ߋ����U�����˕Ԃ�
						rdamage += damage * tsd->short_weapon_damage_return / 100;
						if(rdamage < 1) rdamage = 1;
					}
				}

				// ���t���N�g�V�[���h��
				if(sc &&
				   sc->data[SC_REFLECTSHIELD].timer != -1 &&
				   (sd || sc->data[SC_DEVOTION].timer == -1) &&	// ��f�B�{�[�V�����҂Ȃ�PC����ȊO�͔������Ȃ�
				   skillid != WS_CARTTERMINATION &&
				   skillid != CR_ACIDDEMONSTRATION &&
				   skillid != GN_FIRE_EXPANSION_ACID)
				{
					rdamage += damage * sc->data[SC_REFLECTSHIELD].val2 / 100;	// ���˕Ԃ��v�Z
#ifndef PRE_RENEWAL
					if(rdamage > status_get_max_hp(bl))
						rdamage = status_get_max_hp(bl);
#endif
					if(rdamage < 1) rdamage = 1;
				}
				// ���ˑϐ�
				if(sd && sd->sub_return_damage && rdamage > 0) {
					rdamage = rdamage * (100 - sd->sub_return_damage) / 100;
					if(rdamage < 1) rdamage = 1;
				}
				// �f�X�o�E���h��
				if(sc && sc->data[SC_DEATHBOUND].timer != -1 && !(status_get_mode(src)&MD_BOSS) && path_check_dir(path_calc_dir(src,bl->x,bl->y),status_get_dir(bl)))
				{
					rdamage += (damage * sc->data[SC_DEATHBOUND].val2 * 7) / 1000;	// 7�����˃_���[�W
					damage = (damage * sc->data[SC_DEATHBOUND].val2 * 3) / 1000;	// 3�����g���󂯂�
					clif_skill_damage(bl, src, tick, dmg.amotion, dmg.dmotion, rdamage, 0, RK_DEATHBOUND, sc->data[SC_DEATHBOUND].val1, 1);
					clif_skill_nodamage(bl, dsrc, RK_DEATHBOUND, sc->data[SC_DEATHBOUND].val1, 1);
					skill_blown(bl, src, skill_get_blewcount(RK_DEATHBOUND, sc->data[SC_DEATHBOUND].val1) | SAB_NODAMAGE);
					status_change_end(bl,SC_DEATHBOUND,-1);
				}
				// �V�[���h�X�y��(DEF)
				if(sc && sc->data[SC_SHIELDSPELL_DEF].timer != -1 && sc->data[SC_SHIELDSPELL_DEF].val2 == 1)
				{
					rdamage += damage * sc->data[SC_SHIELDSPELL_DEF].val3 / 100;
				}
				// �C���X�s���[�V����
				if(ssc && ssc->data[SC_INSPIRATION].timer != -1)
				{
					rdamage += damage / 100;
				}
				// �j�ꒌ����
				if(sc && sc->data[SC_CRESCENTELBOW].timer != -1 && !(status_get_mode(src)&MD_BOSS) && atn_rand()%100 < sc->data[SC_CRESCENTELBOW].val2)
				{
					static struct Damage tmpwd = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
					int lv = sc->data[SC_CRESCENTELBOW].val1;
					int dist = unit_distance(bl,src);
					status_change_end(bl,SC_CRESCENTELBOW,-1);
					rdamage += damage + (damage * 20 * lv / 100);
					tmpwd = battle_calc_weapon_attack(bl,src,SR_CRESCENTELBOW_AUTOSPELL,lv,flag);
					rdamage += tmpwd.damage;
					damage = rdamage / 10;
					skill_blown(bl,src,skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,lv)|SAB_NODAMAGE);
					if(unit_distance(bl,src) < skill_get_blewcount(SR_CRESCENTELBOW_AUTOSPELL,lv) + dist) {
						skill_addtimerskill(bl,tick+200,src->id,0,0,SR_CRESCENTELBOW,lv,tick,(0x0f<<20)|0x0500);
					}
				}
			} else if(dmg.flag&BF_LONG) {	// �������U����
				if(tsd) {		// �Ώۂ�PC�̎�
					if(tsd->long_weapon_damage_return > 0) { // �������U�����˕Ԃ�
						rdamage += damage * tsd->long_weapon_damage_return / 100;
						if(rdamage < 1) rdamage = 1;
					}
				}
				// ���ˑϐ�
				if(sd && sd->sub_return_damage && rdamage > 0) {
					rdamage = rdamage * (100 - sd->sub_return_damage) / 100;
					if(rdamage < 1) rdamage = 1;
				}
			}
			if(rdamage > 0)
				clif_damage(src,src,tick, dmg.amotion,0,rdamage,1,4,0,0);
		}
	}
	if(attack_type&BF_MAGIC && damage > 0 && src != bl && (sc && sc->data[SC_KYOMU].timer == -1)) {	// ���@�X�L�����_���[�W���聕�g�p�҂ƑΏێ҂��Ⴄ�������̉e��Ԃł͂Ȃ�
		if(tsd && src == dsrc) {	// �Ώۂ�PC�̎�
			if(tsd->magic_damage_return > 0 && atn_rand()%100 < tsd->magic_damage_return) {	// ���@�U�����˕Ԃ��H��
				rdamage = damage;
				damage  = -1;	// �_���[�W0����miss���o���Ȃ�
			}
		}
		// �J�C�g
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
				damage = -1;	// �_���[�W0����miss���o���Ȃ�
			}
		}
		// �}�W�b�N�~���[
		if(damage > 0 && sc && sc->data[SC_MAGICMIRROR].timer != -1) {
			if(atn_rand()%100 < sc->data[SC_MAGICMIRROR].val1 * 20) {
				clif_misceffect2(bl,675);
				clif_skill_nodamage(bl,src,skillid,skilllv,1);
				rdamage += damage;
				damage = -1;	// �_���[�W0����miss���o���Ȃ�
			}
		}
		// ���ˑϐ�
		if(sd && sd->sub_return_damage && rdamage > 0) {
			rdamage = rdamage * (100 - sd->sub_return_damage) / 100;
			if(rdamage < 1) rdamage = 1;
		}
		// ���p -�O���z-
		if(damage > 0 && sc && sc->data[SC_GENSOU].timer != -1) {
			int odamage = BIGNUM2INT(damage * sc->data[SC_GENSOU].val2 / 100);
			int ar = skill_get_area(OB_OBOROGENSOU,sc->data[SC_GENSOU].val1);

			map_foreachinarea(battle_damage_area,bl->m,
				bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				bl,odamage,OB_OBOROGENSOU,sc->data[SC_GENSOU].val1,flag|BCT_ENEMY|1,tick);
		}
		if(rdamage > 0) {
			clif_skill_damage(src, src, tick, dmg.amotion, dmg.dmotion, rdamage, dmg.div_, skillid, ((src == dsrc)? lv: -1), type);
			if(dmg.blewcount > 0 && !map[src->m].flag.gvg) {
				int dir = path_calc_dir(src,bl->x,bl->y);
				if(dir == 0)
					dir = 8;
				skill_blown(src,src,dmg.blewcount|(dir<<20));	// �Ώۂɑ΂�������Ƌt�����ɔ�΂�
			}
			memset(&dmg,0,sizeof(dmg));
		}
	}
#ifndef PRE_RENEWAL
	if(sc && sc->data[SC_STEELBODY].timer != -1 && damage > 0) {
		damage = damage * 10 / 100;
	}
#endif

	/* �_���[�W�p�P�b�g���M */
	if(damage != -1) {
		switch(skillid) {
		case NPC_SELFDESTRUCTION:
		case NPC_SELFDESTRUCTION2:
			dmg.blewcount |= SAB_NODAMAGE;
			break;
		case WL_TETRAVORTEX_FIRE:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_WATER:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_WIND:	// �e�g���{���e�b�N�X(��)
		case WL_TETRAVORTEX_GROUND:	// �e�g���{���e�b�N�X(�n)
			clif_skill_damage(dsrc, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, WL_TETRAVORTEX, lv, type);
			break;
		case SU_LUNATICCARROTBEAT2:
		case SU_PICKYPECK_DOUBLE_ATK:
			clif_skill_damage(dsrc, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, skillid, -1, type);
			break;
		case RL_FIRE_RAIN:
		case HN_GROUND_GRAVITATION:
			clif_skill_damage(src, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, skillid, lv, type);
			break;
		default:
			clif_skill_damage(dsrc, bl, tick, dmg.amotion, dmg.dmotion, damage, dmg.div_, skillid, lv, type);
			break;
		}
	} else {	// �_���[�W�������̓p�P�b�g���M���Ȃ�
		damage = 0;
	}

	/* ������΂��␳ */
	if(skillid == WZ_STORMGUST) {
		// �A���f�b�h�ȊO�̒ʏ�MOB�̓X�g�[���K�X�g��3HIT�ڂŒe����Ȃ�(����̕z��)
		if(sc && sc->data[SC_FREEZE].val3 == 2 && !(status_get_mode(bl)&MD_BOSS) && !battle_check_undead(status_get_race(bl), status_get_elem_type(bl))) {
			dmg.blewcount = 0;
		}
	}

	/* ������΂������Ƃ��̃p�P�b�g */
	if(dmg.blewcount > 0 && !map[src->m].flag.gvg) {
		skill_blown(dsrc,bl,dmg.blewcount);
	}
	/* ������΂������Ƃ��̃p�P�b�g �J�[�h���� */
	if(dsrc->type == BL_PC && bl->type != BL_SKILL && !map[src->m].flag.gvg) {
		skill_add_blown(dsrc,bl,skillid,SAB_REVERSEBLOW);
	}

	map_freeblock_lock();

	/* ���v���f���[�X & �N���[���X�L�� */
	if(damage > 0 && dmg.flag&BF_SKILL && tsd && sc) {
		/* ���v���f���[�X���� */
		if(sc->data[SC__REPRODUCE].timer != -1 && pc_checkskill(tsd,SC_REPRODUCE)) {
			skill_reproduce(tsd,skillid,skilllv);
		}
		/* �N���[���X�L������ */
		else if(sc->data[SC_PRESERVE].timer == -1 && pc_checkskill(tsd,RG_PLAGIARISM)) {
			skill_clone(tsd,skillid,skilllv);
		}
	}

	/* ���ۂɃ_���[�W�������s�� */
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
				int ar = skill_get_area(skillid,skilllv);
				/* �Ώێ��ӂɂ����_���[�W */
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
		/* �C���e�B�~�f�C�g */
		if(damage > 0 && !(status_get_mode(bl)&MD_BOSS) && !map[src->m].flag.gvg) {
			int rate = 90 + status_get_lv(src) - status_get_lv(bl);
			if(atn_rand()%100 < rate)
				skill_addtimerskill(src,tick + status_get_amotion(src) + 500,bl->id,0,0,skillid,skilllv,0,flag);
		}
	} else if(skillid == NPC_EXPULSION) {
		/* �G�N�X�p���V�I�� */
		if(damage > 0 && !map[src->m].flag.gvg)
			skill_addtimerskill(src,tick + status_get_amotion(src) + 500,bl->id,0,0,skillid,skilllv,0,flag);
	}

	/* �_���[�W������Ȃ�ǉ����ʔ��� */
	if(bl->prev != NULL && !unit_isdead(bl)) {
		if((damage > 0 || skillid == SL_STUN || skillid == AG_DEADLY_PROJECTION
#ifndef PRE_RENEWAL
			|| dmg.dmg_lv == ATK_DEF
#endif
		) && skilllv >= 0) {
			// �O���E���h�h���t�g��dsrc�������Ƃ��ēn��
			if(skillid == GS_GROUNDDRIFT)
				skill_additional_effect(dsrc,bl,skillid,skilllv,attack_type,tick);
			else if(skillid != TK_TURNKICK)
				skill_additional_effect(src,bl,skillid,skilllv,attack_type,tick);

			if(tsd) {
				// �j�C��SP����
				if(skillid == SR_TIGERCANNON) {
					pc_heal(tsd,0,BIGNUM2INT(-(damage / 10)),0,0);
				}
			}
		}

		if(bl->type == BL_MOB && src != bl)	// �X�L���g�p������MOB�X�L��
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

	/* HP,SP�z�� */
	if(sd && dmg.flag&BF_WEAPON && src != bl && damage > 0) {
		if(src == dsrc || (dsrc->type == BL_SKILL && (skillid == SG_SUN_WARM || skillid == SG_MOON_WARM || skillid == SG_STAR_WARM || skillid == GS_DESPERADO || skillid == KO_HUUMARANKA))) {
			// ���z���A���z���Ƃ���
			battle_attack_drain(src, dmg.damage, dmg.damage2, 3);
		}
	}

	/* ���˃_���[�W�̎��ۂ̏��� */
	if((skillid || flag) && rdamage > 0) {
		unsigned int asflag = EAS_WEAPON | EAS_ATTACK | EAS_NORMAL;

		if(attack_type&BF_WEAPON) {
			battle_delay_damage(tick+dmg.amotion,src,src,rdamage,skillid,skilllv,0);
			if(sd) {
				// ���˃_���[�W�̃I�[�g�X�y��
				if(battle_config.weapon_reflect_autospell) {
					bonus_autospell_start(bl,src,asflag,tick,0);
				}
				if(battle_config.weapon_reflect_drain && src != bl)
					battle_attack_drain(bl,rdamage,0,battle_config.weapon_reflect_drain_enable_type);
			}
			if(tsd) {
				// ���˃_���[�W�̃A�N�e�B�u�A�C�e��
				if(battle_config.weapon_reflect_autospell)
					bonus_activeitem_start(tsd,asflag,tick);
			}
		} else {
			battle_damage(src,src,rdamage,skillid,skilllv,0);
			if(sd) {
				// ���˃_���[�W�̃I�[�g�X�y��
				if(battle_config.magic_reflect_autospell) {
					bonus_autospell_start(bl,src,asflag,tick,0);
				}
				if(battle_config.magic_reflect_drain && src != bl)
					battle_attack_drain(bl,rdamage,0,battle_config.magic_reflect_drain_enable_type);
			}
			if(tsd) {
				// ���˃_���[�W�̃A�N�e�B�u�A�C�e��
				if(battle_config.magic_reflect_autospell)
					bonus_activeitem_start(tsd,asflag,tick);
			}
		}
	}

	/* �I�[�g�J�E���^�[ */
	if(attack_type&BF_WEAPON && sc && sc->data[SC_AUTOCOUNTER].timer != -1 && sc->data[SC_AUTOCOUNTER].val4 > 0) {
		if(sc->data[SC_AUTOCOUNTER].val3 == dsrc->id)
			battle_weapon_attack(bl,dsrc,tick,0x8000|sc->data[SC_AUTOCOUNTER].val1);
		status_change_end(bl,SC_AUTOCOUNTER,-1);
	}
	/* �_�u���L���X�e�B���O */
	if ((skillid == MG_COLDBOLT || skillid == MG_FIREBOLT || skillid == MG_LIGHTNINGBOLT) &&
		ssc && ssc->data[SC_DOUBLECASTING].timer != -1 &&
		atn_rand() % 100 < 30+10*ssc->data[SC_DOUBLECASTING].val1) {
		if (!(flag & 1)) {
			//skill_castend_delay (src, bl, skillid, skilllv, tick + dmg.div_*dmg.amotion, flag|1);
			skill_castend_delay (src, bl, skillid, skilllv, tick + 100, flag|1);
		}
	}
	/* �u���b�h���X�g */
	if(src->type == BL_HOM && ssc && ssc->data[SC_BLOODLUST].timer != -1 && dmg.flag&BF_WEAPON && src != bl && src == dsrc && damage > 0)
	{
		struct homun_data *hd = (struct homun_data *)src;
		if(hd && atn_rand()%100 < ssc->data[SC_BLOODLUST].val1*9)
		{
			homun_heal(hd,BIGNUM2INT(damage/5),0);
		}
	}
	/* �X�g�[���n�[�h�X�L�� */
	if(attack_type&BF_WEAPON && sc && sc->data[SC_STONEHARDSKIN].timer != -1) {
		sc->data[SC_STONEHARDSKIN].val3 -= BIGNUM2INT(dmg.damage + dmg.damage2);
		if(sc->data[SC_STONEHARDSKIN].val3 <= 0)
			status_change_end(bl,SC_STONEHARDSKIN,-1);
		if(sd && atn_rand() % 10000 < 500) {
			pc_break_equip(sd, LOC_RARM);
		} else {
			status_change_start(src,SC_STRIPWEAPON,1,0,0,0,10000,0);
		}
	}
	/* �f�b�h���[�C���t�F�N�g */
	if(ssc && ssc->data[SC__DEADLYINFECT].timer != -1 && damage > 0) {
		status_change_copy(src,bl);
	}
	if(dmg.flag&BF_SHORT && sc && sc->data[SC__DEADLYINFECT].timer != -1 && damage > 0) {
		status_change_copy(bl,src);
	}
	/* �T�[�N���I�u�t�@�C�A */
	if(dmg.flag&BF_SHORT && sc && sc->data[SC_CIRCLE_OF_FIRE].timer != -1 && src != bl && damage > 0) {
		battle_skill_attack(BF_WEAPON,bl,bl,src,EL_CIRCLE_OF_FIRE,sc->data[SC_CIRCLE_OF_FIRE].val1,tick,(0x0f<<20)|0x0500);
	}
	// ���̎��n
	if(sd && ssc && ssc->data[SC_SOULREAPER].timer != 1 && damage > 0 && atn_rand()%100 < ssc->data[SC_SOULREAPER].val2) {
		pc_addsoulenergy(sd,600000,1);
	}

	map_freeblock_unlock();

	return BIGNUM2INT(dmg.damage+dmg.damage2);	/* �^�_����Ԃ� */
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
 * �s������
 *------------------------------------------
 */
int battle_check_undead(int race,int element)
{
	// element �ɑ����l�{lv(status_get_element �̖߂�l)���n�����~�X��
	// �Ή�����ׁAelement���瑮���^�C�v�����𔲂��o���B
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
 * �G��������(1=�m��, 0=�ے�, -1=�G���[)
 * flag&0xf0000
 *   0x00000 BCT_NOENEMY: �G����Ȃ�������iret:1���G�ł͂Ȃ��j
 *   0x10000 BCT_PARTY:   �p�[�e�B�[����iret:1=�p�[�e�B�[�����o)
 *   0x20000 BCT_ALL:     �S��(ret:1=�G��������)
 *   0x40000 BCT_ENEMY:   �G������(ret:1=�G)
 *   0x50000 BCT_NOPARTY: �p�[�e�B�[����Ȃ�������(ret:1=�p�[�e�B�łȂ�)
 *------------------------------------------
 */
int battle_check_target( struct block_list *src, struct block_list *target, int flag)
{
	int s_p, s_g, t_p, t_g;
	struct block_list *ss = src;

	nullpo_retr(-1, src);
	nullpo_retr(-1, target);

	if( flag & BCT_ENEMY ) {	// ���]�t���O
		int ret = battle_check_target(src, target, flag & (BCT_PARTY | BCT_ALL));
		if(ret != -1)
			return !ret;
		return -1;
	}

	if( flag & BCT_ALL ) {
		if( target->type == BL_MOB || (target->type == BL_PC && !pc_isinvisible((struct map_session_data *)target)) )
			return 1;
		if( target->type == BL_HOM && src->type != BL_SKILL )	// �z���̓X�L�����j�b�g�̉e�����󂯂Ȃ�
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
				return -1;	// �X�L�����j�b�g���m�Ȃ疳�����m��

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

	// �X�L�����j�b�g�̏ꍇ�A�e�����߂�
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

	// Mob��master_id��������special_mob_ai�Ȃ�A����������߂�
	if( src->type == BL_MOB ) {
		struct mob_data *md = (struct mob_data *)src;
		if(md) {
			if(md->master_id > 0) {
				if(md->master_id == target->id)	// ��Ȃ�m��
					return 1;
				if(md->state.special_mob_ai != MOB_AI_NONE) {
					if(target->type == BL_MOB) {	// special_mob_ai�őΏۂ�Mob
						struct mob_data *tmd = (struct mob_data *)target;
						if(tmd) {
							if(tmd->master_id != md->master_id)	// �����傪�ꏏ�łȂ���Δے�
								return 0;
							else if(md->state.special_mob_ai == MOB_AI_SPHERE2)	// �����傪�ꏏ�Ȃ̂ōm�肵�������ǎ����͔ے�
								return 0;
							else
								return 1;
						}
					} else if(target->type & (BL_HOM | BL_MERC | BL_ELEM)) {
						// special_mob_ai�őΏۂ��z���A�b���A����Ȃ�G���[�ŕԂ�
						return -1;
					}
				}
				if((ss = map_id2bl(md->master_id)) == NULL)
					return -1;
			}
			// �ʏ�AI�����X�^�[�ő��肪�����X�^�[
			if(md->state.special_mob_ai == MOB_AI_NONE && target->type == BL_MOB) {
				struct mob_data *tmd = (struct mob_data *)target;
				if(tmd && (tmd->state.special_mob_ai == MOB_AI_ABR || tmd->state.special_mob_ai == MOB_AI_BIONIC)) {
					// ���肪ABR�܂��̓o�C�I�j�b�NMOB�Ȃ�ے�
					return 0;
				}
			}
		}
	}

	if( src == target || ss == target )	// �����Ȃ�m��
		return 1;

	if(target->type == BL_PC && pc_isinvisible((struct map_session_data *)target))
		return -1;

	if( src->prev == NULL || unit_isdead(src) ) // ����ł�Ȃ�G���[
		return -1;

	// PC����MOB
	if(ss->type == BL_PC && target->type == BL_MOB) {
		int guardian = 0;
		struct mob_data *md         = (struct mob_data *)target;
		struct map_session_data *sd = (struct map_session_data *)ss;
		struct guild_castle *gc = NULL;

		// ���M�I�������X�^�[
		if(md->state.special_mob_ai == MOB_AI_LEGION) {
			if(sd->hd && sd->hd->bl.id == md->master_id)
				return 1;
		}

		// ABR/�o�C�I�j�b�N�����X�^�[
		if(md->state.special_mob_ai == MOB_AI_ABR || md->state.special_mob_ai == MOB_AI_BIONIC) {
			// ������߂�
			struct block_list *master = map_id2bl(md->master_id);
			if(master == NULL)
				return -1;
			// ��ɒu�������čĒT��
			return battle_check_target(src, master, flag);
		}

		// �Ԃ̃K�[�f�B�A�����ǂ���
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

		// GvG���ԊO
		if(!map[ss->m].flag.gvg) {
			// �K�[�f�B�A���ƔO�̂��߃G���y�͖���
			if(md->class_ == MOBID_EMPERIUM || guardian)
				return 1;
			// ����ȊO�͓G
			return 0;
		}

		/* �������� flag.gvg �����鏈�� */

		// �M���h����PC�͑S���G
		if(sd->status.guild_id <= 0)
			return 0;

		// �M���h����̕⊮
		if(md->guild_id <= 0)
			gc = guild_mapid2gc(md->bl.m);

		// �����̃M���h�������M���h��
		if(gc) {
			struct guild *g = guild_search(sd->status.guild_id);
			if(g == NULL)
				return 0;

			if(g->guild_id == gc->guild_id || guild_check_alliance(md->guild_id, sd->status.guild_id, 0)) {
				// �G���y�ƃK�[�f�B�A���͖���
				if(md->class_ == MOBID_EMPERIUM || guardian)
					return 1;
				// ����ȊO�̃o�C�I�v�����g�A�X�t�B�A�}�C���Ȃǂ͓G�i�U���\�j
				return 0;
			}
		}

		// ���l�̍ԁA�ԈȊO��GvG���[�h�Ȃ�S���G
		return 0;
	}
	if(ss->type == BL_MOB && target->type == BL_PC) {
		return 0;	// MOB��PC�Ȃ�G
	}

	if(ss->type == BL_PET && target->type == BL_MOB) {
		struct pet_data *pd = (struct pet_data*)ss;
		struct mob_data *md = (struct mob_data*)target;
		int mode = mobdb_search(pd->class_)->mode;
		int race = mobdb_search(pd->class_)->race;
		if(mobdb_search(pd->class_)->mexp <= 0 && !(mode&MD_BOSS) && (md->sc.option & (OPTION_HIDE | OPTION_CLOAKING) && race != RCT_INSECT && race != RCT_DEMON) ) {
			return 1; // ���s
		} else {
			return 0; // ����
		}
	}

	s_p = status_get_party_id(ss);
	s_g = status_get_guild_id(ss);

	t_p = status_get_party_id(target);
	t_g = status_get_guild_id(target);

	if(flag & BCT_PARTY) {
		if(s_p && t_p && s_p == t_p)
			return 1;	// �����p�[�e�B�Ȃ�m��i�����j
		else
			return 0;	// �p�[�e�B�����Ȃ瓯���p�[�e�B����Ȃ����_�Ŕے�
	}

	if(ss->type == BL_MOB && s_g > 0 && t_g > 0 && s_g == t_g )	// �����M���h/mob�N���X�Ȃ�m��i�����j
		return 1;

	if(ss->type == BL_PC && target->type == BL_PC) {	// ����PVP���[�h�Ȃ�ے�i�G�j
		struct skill_unit *su = NULL;
		if(src->type == BL_SKILL)
			su = (struct skill_unit *)src;
		// PK
		if(map[ss->m].flag.pk) {
			struct guild *g = NULL;
			struct map_session_data* ssd = (struct map_session_data*)ss;
			struct map_session_data* tsd = (struct map_session_data*)target;

			// battle_config.no_pk_level�ȉ��@1���͖����@�]���͑ʖ�
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
							return 0;	// �G�΃M���h�Ȃ疳�����ɓG
						else
							return 1;	// �����M���h�Ȃ疳�����ɖ���
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
							return 0;	// �G�΃M���h�Ȃ疳�����ɓG
						else
							return 1;	// �����M���h�Ȃ疳�����ɖ���
					}
				}
			}
			return 0;
		}
	}

	if(ss->type == BL_MOB && (target->type & (BL_HOM | BL_MERC | BL_ELEM)))
		return 0;	// MOB vs HOM, MERC, ELEM �Ȃ�G

	if((ss->type & (BL_HOM | BL_MERC | BL_ELEM)) && target->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)target;
		if(md && md->state.special_mob_ai == MOB_AI_LEGION && md->master_id > 0) {
			if(md->master_id == ss->id)	// ��Ȃ�m��
				return 1;
		}
		return 0;	// HOM, MERC, ELEM vs MOB �Ȃ�G
	}

	if(!(map[ss->m].flag.pvp || map[ss->m].flag.gvg)) {
		if(ss->type == BL_PC && (target->type & (BL_HOM | BL_MERC | BL_ELEM)))
			return 1;	// Pv�ł�Gv�ł��Ȃ��Ȃ�APC vs HOM, MERC, ELEM �͖���

		if((ss->type & (BL_HOM | BL_MERC | BL_ELEM)) && target->type == BL_PC)
			return 1;	// Pv�ł�Gv�ł��Ȃ��Ȃ�AHOM, MERC, ELEM vs PC �͖���
	}

	// ��PT�Ƃ�����Guild�Ƃ��͌�񂵁i����
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
	return 1;	// �Y�����Ȃ��̂Ŗ��֌W�l���i�܂��G����Ȃ��̂Ŗ����j
}

/*==========================================
 * �˒�����
 *------------------------------------------
 */
int battle_check_range(struct block_list *src,struct block_list *bl,int range)
{
	int arange;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	arange = path_distance(src->x,src->y,bl->x,bl->y);

	if(src->m != bl->m)	// �Ⴄ�}�b�v
		return 0;

	if(range > 0 && range < arange)	// ��������
		return 0;

	if(arange < 2)	// �����}�X���א�
		return 1;

	// ��Q������
	return path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y);
}

/*==========================================
 * ��̏���
 *------------------------------------------
 */
int battle_delarrow(struct map_session_data* sd,int num,int skillid)
{
	int mask = 0, idx = -1;

	nullpo_retr(0, sd);

	if(skillid == 0) {	// �ʏ�U��
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
	} else {		// �X�L���U��
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
 * �_���[�W�Ȃ��ŋ����ɎQ��
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
				// �_���[�W�Ȃ��Ő퓬�Q���ғ���
				linkdb_insert( &md->dmglog, INT2PTR(sd->status.char_id), INT2PTR(0) );
			}
		}
	}
	return;
}

/*==========================================
 * �ݒ�t�@�C���ǂݍ��ݗp�i�t���O�j
 *------------------------------------------
 */
static int battle_config_switch(const char *str)
{
	if(strcasecmp(str,"on") == 0 || strcasecmp(str,"yes") == 0)
		return 1;
	if(strcasecmp(str,"off") == 0 || strcasecmp(str,"no") == 0)
		return 0;
	return atoi(str);
}

/*==========================================
 * �ݒ�t�@�C����ǂݍ���
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
		{ "allow_se_univ_skill_limit",          &battle_config.allow_se_univ_skill_limit,          1        },
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
		{ "max_buyingstore_zeny",               &battle_config.max_buyingstore_zeny,               99990000 },
		{ "max_buyingstore_amount",             &battle_config.max_buyingstore_amount,             9999     },
		{ "allow_same_activeitem",              &battle_config.allow_same_activeitem,              0        },
		{ "disable_transform_when_gvg",         &battle_config.disable_transform_when_gvg,         1        },
		{ "esnv_status_max",                    &battle_config.esnv_status_max,                    120      },
		{ "esnv_baby_status_max",               &battle_config.esnv_baby_status_max,               108      },
		{ "esnv_max_aspd",                      &battle_config.esnv_max_aspd,                      140      },
		{ "ko_status_max",                      &battle_config.ko_status_max,                      120      },
		{ "ko_max_aspd",                        &battle_config.ko_max_aspd,                        140      },
		{ "rl_status_max",                      &battle_config.rl_status_max,                      120      },
		{ "rl_max_aspd",                        &battle_config.rl_max_aspd,                        140      },
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
		{ "ping_timer_interval",                &battle_config.ping_timer_interval,                30       },
		{ "enable_pet_autofeed",                &battle_config.enable_pet_autofeed,                1        },
		{ "enable_hom_autofeed",                &battle_config.enable_hom_autofeed,                1        },
		{ "homun_status_max",                   &battle_config.homun_status_max,                   150      },
		{ "skill_unit_interval_limit",          &battle_config.skill_unit_interval_limit,          1        },
		{ "max_skillpoint_nv",                  &battle_config.max_skillpoint_nv,                  9        },
		{ "max_skillpoint_1st",                 &battle_config.max_skillpoint_1st,                 58       },
		{ "max_skillpoint_n2nd",                &battle_config.max_skillpoint_n2nd,                107      },
		{ "max_skillpoint_n3rd",                &battle_config.max_skillpoint_n3rd,                176      },
		{ "max_skillpoint_2nd",                 &battle_config.max_skillpoint_2nd,                 127      },
		{ "max_skillpoint_3rd",                 &battle_config.max_skillpoint_3rd,                 196      },
		{ "max_skillpoint_tk2nd",               &battle_config.max_skillpoint_tk2nd,               107      },
		{ "max_skillpoint_tk3rd",               &battle_config.max_skillpoint_tk3rd,               176      },
		{ "max_skillpoint_ex1st",               &battle_config.max_skillpoint_ex1st,               78       },
		{ "max_skillpoint_ex2nd",               &battle_config.max_skillpoint_ex2nd,               147      },
		{ "max_skillpoint_snv",                 &battle_config.max_skillpoint_snv,                 107      },
		{ "max_skillpoint_esnv",                &battle_config.max_skillpoint_esnv,                176      },
		{ "max_skillpoint_doram",               &battle_config.max_skillpoint_doram,               59       },
		{ "pc_tstatus_max",                     &battle_config.pc_tstatus_max,                     100      },
		{ "mob_ai_area_size",                   &battle_config.mob_ai_area_size,                   36       },
		{ "mob_ai_sleeptime",                   &battle_config.mob_ai_sleeptime,                   60000    },
		{ "boss_ai_sleeptime",                  &battle_config.boss_ai_sleeptime,                  300000   },
		{ "fourth_jobchange_tstpoint",          &battle_config.fourth_jobchange_tstpoint,          7        },
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

		if(strcasecmp(w1,"import") == 0) {
			battle_config_read(w2);
		} else {
			for(i=0; data[i].val; i++) {
				if(strcasecmp(w1,data[i].str) == 0) {
					*data[i].val = battle_config_switch(w2);
					break;
				}
			}
			if(data[i].val == NULL)
				printf("unknown battle config : %s\a\n",w1);
		}
	}
	fclose(fp);

	// �t���O����
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
 * ������
 *------------------------------------------
 */
int do_init_battle(void)
{
	add_timer_func_list(battle_delay_damage_sub);

	return 0;
}

/*==========================================
 * �I��
 *------------------------------------------
 */
int do_final_battle(void)
{
	// nothing to do
	return 0;
}

