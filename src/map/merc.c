
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "mmo.h"

#include "atcommand.h"
#include "battle.h"
#include "clif.h"
#include "chrif.h"
#include "intif.h"
#include "map.h"
#include "merc.h"
#include "mob.h"
#include "npc.h"
#include "pc.h"
#include "skill.h"
#include "status.h"
#include "storage.h"
#include "unit.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

struct merc_db merc_db[MAX_MERC_DB];

static struct merc_skill_tree_entry {
	int id;
	int max;
	struct {
		short id,lv;
	} need[5];
	unsigned short base_level;
	int intimate;
} merc_skill_tree[MAX_MERC_DB][MAX_MERCSKILL_TREE];

/*==========================================
 * スキルツリー情報の検索
 *------------------------------------------
 */
static struct merc_skill_tree_entry* merc_search_skilltree(int class_, int skillid)
{
	int min = -1;
	int max = MAX_MERCSKILL_TREE;
	struct merc_skill_tree_entry *st;

	st = merc_skill_tree[class_ - MERC_ID];

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(st[mid].id == skillid)
			return &st[mid];

		// 0のときは大とみなす
		if(st[mid].id == 0 || st[mid].id > skillid)
			max = mid;
		else
			min = mid;
	}
	return NULL;
}

/*==========================================
 * スキルのMaxLvを返す
 *------------------------------------------
 */
int merc_get_skilltree_max(int class_,int skillid)
{
	struct merc_skill_tree_entry *st;

	st = merc_search_skilltree(class_, skillid);
	if(st == NULL)
		return 0;

	return st->max;
}

/*==========================================
 *
 *------------------------------------------
 */
static int merc_calc_pos(struct merc_data *mcd,int tx,int ty,int dir)
{
	int x,y,dx,dy;
	int i,j=0,k;

	nullpo_retr(0, mcd);

	mcd->ud.to_x = tx;
	mcd->ud.to_y = ty;

	if(dir >= 0 && dir < 8) {
		dx = -dirx[dir]*2;
		dy = -diry[dir]*2;
		x = tx + dx;
		y = ty + dy;
		if(!(j=unit_can_reach(&mcd->bl,x,y))) {
			if(dx > 0) x--;
			else if(dx < 0) x++;
			if(dy > 0) y--;
			else if(dy < 0) y++;
			if(!(j=unit_can_reach(&mcd->bl,x,y))) {
				for(i=0;i<12;i++) {
					k = atn_rand()%8;
					dx = -dirx[k]*2;
					dy = -diry[k]*2;
					x = tx + dx;
					y = ty + dy;
					if((j=unit_can_reach(&mcd->bl,x,y)))
						break;
					else {
						if(dx > 0) x--;
						else if(dx < 0) x++;
						if(dy > 0) y--;
						else if(dy < 0) y++;
						if((j=unit_can_reach(&mcd->bl,x,y)))
							break;
					}
				}
				if(!j) {
					x = tx;
					y = ty;
					if(!unit_can_reach(&mcd->bl,x,y))
						return 1;
				}
			}
		}
	}
	else
		return 1;

	mcd->ud.to_x = x;
	mcd->ud.to_y = y;
	return 0;
}

/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int merc_calc_status(struct merc_data *mcd)
{
	int dstr,blv,aspd_k;
	int aspd_rate=100,speed_rate=100,atk_rate=100,matk_rate=100,hp_rate=100,sp_rate=100;
	int flee_rate=100,def_rate=100,mdef_rate=100,critical_rate=100,hit_rate=100;

	nullpo_retr(1, mcd);

	mcd->atk      = 0;
	mcd->matk     = 0;
	mcd->hit      = 0;
	mcd->flee     = 0;
	mcd->def      = 0;
	mcd->mdef     = 0;
	mcd->critical = 0;
	mcd->max_hp   = mcd->status.max_hp;
	mcd->max_sp   = mcd->status.max_sp;
	mcd->str      = mcd->status.str;
	mcd->agi      = mcd->status.agi;
	mcd->vit      = mcd->status.vit;
	mcd->dex      = mcd->status.dex;
	mcd->int_     = mcd->status.int_;
	mcd->luk      = mcd->status.luk;
	mcd->speed    = DEFAULT_WALK_SPEED;
	mcd->nhealhp  = 0;
	mcd->nhealsp  = 0;
	mcd->hprecov_rate = 100;
	mcd->sprecov_rate = 100;

/*
	// ステータス変化による基本パラメータ補正ホムスキル
	if(mcd->sc_count > 0)
	{
		// 緊急回避
		if(mcd->sc_data[SC_AVOID].timer != -1)
			speed_rate -= mcd->sc_data[SC_AVOID].val1*10;
		// メンタルチェンジ
		if(mcd->sc_data[SC_CHANGE].timer != -1)
			mcd->int_ += 60;
		// ブラッドラスト
		if(mcd->sc_data[SC_BLOODLUST].timer != -1)
			atk_rate += mcd->sc_data[SC_BLOODLUST].val1*10+20;
		// フリットムーブ
		if(mcd->sc_data[SC_FLEET].timer != -1) {
			aspd_rate -= mcd->sc_data[SC_FLEET].val1*3;
			atk_rate  += 5+mcd->sc_data[SC_FLEET].val1*5;
		}

		// ステータス変化による基本パラメータ補正
		if(battle_config.allow_homun_status_change)
		{
			// ゴスペルALL+20
			if(mcd->sc_data[SC_INCALLSTATUS].timer != -1) {
				mcd->str  += mcd->sc_data[SC_INCALLSTATUS].val1;
				mcd->agi  += mcd->sc_data[SC_INCALLSTATUS].val1;
				mcd->vit  += mcd->sc_data[SC_INCALLSTATUS].val1;
				mcd->int_ += mcd->sc_data[SC_INCALLSTATUS].val1;
				mcd->dex  += mcd->sc_data[SC_INCALLSTATUS].val1;
				mcd->luk  += mcd->sc_data[SC_INCALLSTATUS].val1;
			}

			if(mcd->sc_data[SC_INCREASEAGI].timer != -1)	// 速度増加
				mcd->agi += 2+mcd->sc_data[SC_INCREASEAGI].val1;

			if(mcd->sc_data[SC_DECREASEAGI].timer != -1)	// 速度減少(agiはbattle.cで)
				mcd->agi -= 2+mcd->sc_data[SC_DECREASEAGI].val1;

			if(mcd->sc_data[SC_BLESSING].timer != -1) {	// ブレッシング
				mcd->str  += mcd->sc_data[SC_BLESSING].val1;
				mcd->dex  += mcd->sc_data[SC_BLESSING].val1;
				mcd->int_ += mcd->sc_data[SC_BLESSING].val1;
			}
			if(mcd->sc_data[SC_SUITON].timer != -1) {	// 水遁
				if(mcd->sc_data[SC_SUITON].val3)
					mcd->agi += mcd->sc_data[SC_SUITON].val3;
				if(mcd->sc_data[SC_SUITON].val4)
					mcd->speed = mcd->speed*2;
			}

			if(mcd->sc_data[SC_GLORIA].timer != -1)	// グロリア
				mcd->luk += 30;

			if(mcd->sc_data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
				short subagi = 0;
				short subdex = 0;
				subagi = (mcd->status.agi/2 < mcd->sc_data[SC_QUAGMIRE].val1*10) ? mcd->status.agi/2 : mcd->sc_data[SC_QUAGMIRE].val1*10;
				subdex = (mcd->status.dex/2 < mcd->sc_data[SC_QUAGMIRE].val1*10) ? mcd->status.dex/2 : mcd->sc_data[SC_QUAGMIRE].val1*10;
				if(map[mcd->bl.m].flag.pvp || map[mcd->bl.m].flag.gvg) {
					subagi /= 2;
					subdex /= 2;
				}
				mcd->speed = mcd->speed*4/3;
				mcd->agi -= subagi;
				mcd->dex -= subdex;
			}
		}
	}
*/

	dstr   = mcd->str / 10;
	blv    = mcd->status.base_level;
	aspd_k = merc_db[mcd->status.class_-MERC_ID].aspd_k;

	mcd->atk      += mcd->str * 2 + blv + dstr * dstr;
	mcd->matk     += mcd->int_+(mcd->int_/ 5) * (mcd->int_/ 5);
	mcd->hit      += mcd->dex + blv;
	mcd->flee     += mcd->agi + blv;
	mcd->def      += mcd->vit + mcd->vit / 5 + blv / 10;
	mcd->mdef     += mcd->int_/ 5 + blv / 10;
	mcd->critical += mcd->luk / 3 + 1;

	mcd->aspd = aspd_k - (aspd_k * mcd->agi / 250 + aspd_k * mcd->dex / 1000) - 200;

	// 補正
	if(atk_rate != 100)
		mcd->atk = mcd->atk*atk_rate/100;
	if(matk_rate != 100)
		mcd->matk = mcd->matk*matk_rate/100;
	if(hit_rate != 100)
		mcd->hit = mcd->hit*hit_rate/100;
	if(flee_rate != 100)
		mcd->flee = mcd->flee*flee_rate/100;
	if(def_rate != 100)
		mcd->def = mcd->def*def_rate/100;
	if(mdef_rate != 100)
		mcd->mdef = mcd->mdef*mdef_rate/100;
	if(critical_rate != 100)
		mcd->critical = mcd->critical*critical_rate/100;
	if(hp_rate != 100)
		mcd->max_hp = mcd->max_hp*hp_rate/100;
	if(sp_rate != 100)
		mcd->max_sp = mcd->max_sp*sp_rate/100;
	if(aspd_rate != 100)
		mcd->aspd = mcd->aspd*aspd_rate/100;
	if(speed_rate != 100)
		mcd->speed = mcd->speed*speed_rate/100;

	if(mcd->max_hp <= 0)
		mcd->max_hp = 1;
	if(mcd->max_sp <= 0)
		mcd->max_sp = 1;

	// 自然回復
	mcd->nhealhp = mcd->max_hp/100 + mcd->vit/5 + 2;
	mcd->nhealsp = (mcd->int_/6)+(mcd->max_sp/100)+1;
	if(mcd->int_ >= 120)
		mcd->nhealsp += ((mcd->int_-120)>>1) + 4;
	if(mcd->hprecov_rate != 100)
		mcd->nhealhp = mcd->nhealhp*mcd->hprecov_rate/100;
	if(mcd->sprecov_rate != 100)
		mcd->nhealsp = mcd->nhealsp*mcd->sprecov_rate/100;

	merc_calc_skilltree(mcd);

	return 0;
}

/*==========================================
 * 傭兵召喚
 *------------------------------------------
 */
int merc_callmerc(struct map_session_data *sd,int class_)
{
	struct mmo_mercstatus st;

	nullpo_retr(1, sd);

	if(sd->status.merc_id > 0 || sd->mcd)	// 既に召喚中
		return 1;
	if(sd->state.merc_creating)
		return 1;

	class_ -= MERC_ID;
	if(class_ < 0 || class_ >= MAX_MERC_DB)
		return 1;

	memset(&st, 0, sizeof(st));

	memcpy(st.name, merc_db[class_].jname , 24);
	st.class_     = class_ + MERC_ID;
	st.account_id = sd->status.account_id;
	st.char_id    = sd->status.char_id;
	st.base_level = merc_db[class_].base_level;
	st.max_hp     = 1;
	st.max_sp     = 0;

	// 初期ステータスをDBから埋め込み
	st.max_hp = merc_db[class_].hp;
	st.max_sp = merc_db[class_].sp;
	st.str    = merc_db[class_].str;
	st.agi    = merc_db[class_].agi;
	st.vit    = merc_db[class_].vit;
	st.int_   = merc_db[class_].int_;
	st.dex    = merc_db[class_].dex;
	st.luk    = merc_db[class_].luk;
	st.limit  = merc_db[class_].limit + (unsigned int)time(NULL);

	st.hp = st.max_hp;
	st.sp = st.max_sp;

	sd->state.merc_creating = 1;
	intif_create_merc(sd->status.account_id,sd->status.char_id,&st);

	return 0;
}

static int merc_natural_heal_hp(int tid,unsigned int tick,int id,int data);
static int merc_natural_heal_sp(int tid,unsigned int tick,int id,int data);

/*==========================================
 *
 *------------------------------------------
 */
static int merc_data_init(struct map_session_data *sd)
{
	struct merc_data *mcd;
	int i,class_;
	unsigned int tick = gettick();

	nullpo_retr(1, sd);
	nullpo_retr(1, mcd = sd->mcd);

	class_ = sd->mcd->status.class_ - MERC_ID;

	mcd->bl.m    = sd->bl.m;
	mcd->bl.prev = mcd->bl.next = NULL;
	mcd->bl.x    = mcd->ud.to_x = sd->bl.x;
	mcd->bl.y    = mcd->ud.to_y = sd->bl.y;
	merc_calc_pos(mcd,sd->bl.x,sd->bl.y,sd->dir);
	mcd->bl.x        = mcd->ud.to_x;
	mcd->bl.y        = mcd->ud.to_y;
	mcd->bl.id       = npc_get_new_npc_id();
	mcd->dir         = sd->dir;
	mcd->speed       = status_get_speed(&sd->bl);	// 歩行速度は、コール時の主人のspeedになる
	mcd->bl.subtype  = MONS;
	mcd->bl.type     = BL_MERC;
	mcd->target_id   = 0;
	mcd->attackable  = 1;	// これを0にすると、クライアントから攻撃パケットを出さなくなる
	mcd->msd         = sd;
	mcd->view_class  = merc_db[class_].view_class;
	mcd->attackrange = merc_db[class_].range;

	for(i=0; i<MAX_MERCSKILL; i++)
		mcd->skillstatictimer[i] = tick;

	// ステータス異常の初期化
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		mcd->sc_data[i].timer = -1;
		mcd->sc_data[i].val1 = mcd->sc_data[i].val2 = mcd->sc_data[i].val3 = mcd->sc_data[i].val4 = 0;
	}
	mcd->sc_count = 0;
	mcd->status.option &= OPTION_MASK;
	mcd->opt1 = 0;
	mcd->opt2 = 0;
	mcd->opt3 = 0;

	merc_calc_status(mcd);			// ステータス計算
	unit_dataset(&mcd->bl);
	map_addiddb(&mcd->bl);

	mcd->natural_heal_hp = add_timer(tick+MERC_NATURAL_HEAL_HP_INTERVAL,merc_natural_heal_hp,mcd->bl.id,0);
	mcd->natural_heal_sp = add_timer(tick+MERC_NATURAL_HEAL_SP_INTERVAL,merc_natural_heal_sp,mcd->bl.id,0);

	mcd->view_size = 0;

	return 0;
}

/*==========================================
 * interから傭兵のデータ受信
 *------------------------------------------
 */
int merc_recv_mercdata(int account_id,int char_id,struct mmo_mercstatus *p,int flag)
{
	struct map_session_data *sd;

	nullpo_retr(0, p);

	sd = map_id2sd(account_id);

	if(sd == NULL || sd->status.char_id != char_id || (sd->status.merc_id && sd->status.merc_id != p->merc_id))
	{
		if(flag) {
			// 新規作成時なら傭兵データを削除する
			intif_delete_mercdata(account_id,char_id,p->merc_id);
		}
		if(sd)
			sd->state.merc_creating = 0;
		return 0;
	}

	if(sd->mcd == NULL) {
		sd->mcd = (struct merc_data *)aCalloc(1,sizeof(struct merc_data));
		memcpy(&sd->mcd->status, p, sizeof(struct mmo_mercstatus));

		if(sd->status.merc_id <= 0)
			sd->status.merc_id = p->merc_id;

		if(!merc_data_init(sd) && sd->bl.prev != NULL)
		{
			if(sd->mcd->status.hp <= 0) {	// 死亡
				merc_delete_data(sd);
				sd->state.merc_creating = 0;
				return 0;
			}
			map_addblock(&sd->mcd->bl);
			mob_ai_hard_spawn( &sd->mcd->bl, 1 );
			clif_spawnmerc(sd->mcd);
			clif_send_mercdata(sd);
			clif_send_mercstatus(sd,1);
			clif_send_mercstatus(sd,0);
			merc_save_data(sd);
			skill_unit_move(&sd->mcd->bl,gettick(),1);
		}
		clif_mercskillinfoblock(sd);
	}
	sd->state.merc_creating = 0;

	return 0;
}

/*==========================================
 * 傭兵削除
 *------------------------------------------
 */
int merc_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.merc_id > 0 && sd->mcd) {
		// 親密度保存
		//if(battle_config.save_homun_temporal_intimate)
		//	pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",2000);	// 初期値に
		unit_free(&sd->mcd->bl,0);
		intif_delete_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);
		sd->status.merc_id = 0;
		chrif_save(sd);
		if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
	}

	return 0;
}

/*==========================================
 * 傭兵メニューの応答
 *------------------------------------------
 */
int merc_menu(struct map_session_data *sd, int menunum)
{
	nullpo_retr(0, sd);

	if(!sd->mcd)
		return 0;

	switch(menunum) {
		case 1:
			clif_send_mercstatus(sd,0);
			break;
		case 2:
			clif_disp_onlyself(sd->fd, msg_txt(190));	// 傭兵を解雇しました。
			merc_delete_data(sd);
			break;
	}
	return 0;
}

/*==========================================
 * 待機命令などで、主人の下へ移動
 *------------------------------------------
 */
int merc_return_master(struct map_session_data *sd)
{
	struct merc_data *mcd;

	nullpo_retr(0, sd);
	nullpo_retr(0, mcd = sd->mcd);

	merc_calc_pos(mcd,sd->bl.x,sd->bl.y,sd->dir);
	unit_walktoxy(&mcd->bl,mcd->ud.to_x,mcd->ud.to_y);
	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int merc_checkskill(struct merc_data *mcd,int skill_id)
{
	if(mcd == NULL)
		return 0;
	if(skill_id >= MERC_SKILLID)
		skill_id -= MERC_SKILLID;

	if(skill_id >= MAX_MERCSKILL)
		return 0;
	if(mcd->status.skill[skill_id].id == skill_id + MERC_SKILLID)
		return mcd->status.skill[skill_id].lv;

	return 0;
}

/*==========================================
 * 覚えられるスキルの計算
 *------------------------------------------
 */
int merc_calc_skilltree(struct merc_data *mcd)
{
	int i, id, c, flag;

	nullpo_retr(0, mcd);

	c = mcd->status.class_ - MERC_ID;

	for(i=0; i<MAX_MERCSKILL; i++)
		mcd->status.skill[i].id = 0;
	do {
		flag = 0;
		for(i=0; (id = merc_skill_tree[c][i].id) > 0; i++) {
			int j, f = 1;
			for(j=0; j<5; j++) {
				if( merc_skill_tree[c][i].need[j].id &&
				    merc_checkskill(mcd,merc_skill_tree[c][i].need[j].id) < merc_skill_tree[c][i].need[j].lv )
					f = 0;
			}
			if(mcd->status.base_level < merc_skill_tree[c][i].base_level)
				f = 0;
			id -= MERC_SKILLID;
			if(f && mcd->status.skill[id].id == 0 && id >= 0) {
				mcd->status.skill[id].id = id + MERC_SKILLID;
				flag = 1;
			}
		}
	} while(flag);

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int merc_gainexp(struct merc_data *mcd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp)
{
	nullpo_retr(0, mcd);

	if(mcd->bl.prev == NULL || unit_isdead(&mcd->bl))
		return 0;

	if(md && md->sc_data && md->sc_data[SC_RICHMANKIM].timer != -1) {
		base_exp = base_exp * (125 + md->sc_data[SC_RICHMANKIM].val1*11)/100;
		job_exp  = job_exp  * (125 + md->sc_data[SC_RICHMANKIM].val1*11)/100;
	}

	if(mcd->msd) {	// 主人へ指定倍の経験値
		atn_bignumber mbexp = 0, mjexp = 0;
		if(battle_config.master_get_merc_base_exp)
			mbexp = base_exp * battle_config.master_get_merc_base_exp / 100;
		if(battle_config.master_get_merc_job_exp)
			mjexp = job_exp  * battle_config.master_get_merc_job_exp / 100;

		if(mbexp || mjexp)
			pc_gainexp(mcd->msd,md,mbexp,mjexp);
	}

	return 0;
}

/*==========================================
 * mcdにdamageのダメージ
 *------------------------------------------
 */
int merc_damage(struct block_list *src,struct merc_data *mcd,int damage)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, mcd);
	nullpo_retr(0, sd = mcd->msd);

	// 既に死んでいたら無効
	if(unit_isdead(&mcd->bl))
		return 0;

	// 歩いていたら足を止める
	unit_stop_walking(&mcd->bl,battle_config.pc_hit_stop_type);

	if(damage > 0 && mcd->sc_data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&mcd->bl, SC_GRAVITATION_USER, -1);

	if(mcd->bl.prev == NULL) {
		if(battle_config.error_log)
			printf("merc_damage : BlockError!!\n");
		return 0;
	}

	if(mcd->status.hp > mcd->max_hp)
		mcd->status.hp = mcd->max_hp;

	// over kill分は丸める
	if(damage > mcd->status.hp)
		damage = mcd->status.hp;

	mcd->status.hp -= damage;

	// ハイド状態を解除
	status_change_hidden_end(&mcd->bl);

	clif_send_mercstatus(sd,0);

	// 死亡していた
	if(mcd->status.hp <= 0) {
		//if(battle_config.save_homun_temporal_intimate)
		//	pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);

		// スキルユニットからの離脱
		mcd->status.hp = 1;
		skill_unit_move(&mcd->bl,gettick(),0);
		mcd->status.hp = 0;

		clif_disp_onlyself(sd->fd, msg_txt(189));	// 傭兵が死亡しました。
		merc_delete_data(sd);
	}

	return 0;
}

/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int merc_heal(struct merc_data *mcd,int hp,int sp)
{
	nullpo_retr(0, mcd);

	// バーサーク中は回復させない
	if(mcd->sc_data[SC_BERSERK].timer != -1) {
		if(sp > 0)
			sp = 0;
		if(hp > 0)
			hp = 0;
	}

	if(hp + mcd->status.hp > mcd->max_hp)
		hp = mcd->max_hp - mcd->status.hp;
	if(sp + mcd->status.sp > mcd->max_sp)
		sp = mcd->max_sp - mcd->status.sp;
	mcd->status.hp += hp;
	if(mcd->status.hp <= 0) {
		mcd->status.hp = 0;
		merc_damage(NULL,mcd,1);
		hp = 0;
	}
	mcd->status.sp += sp;
	if(mcd->status.sp <= 0)
		mcd->status.sp = 0;
	if((hp || sp) && mcd->msd)
		clif_send_mercstatus(mcd->msd,0);

	return hp + sp;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static int merc_natural_heal_hp(int tid,unsigned int tick,int id,int data)
{
	struct merc_data *mcd = map_id2mcd(id);
	int bhp;

	nullpo_retr(0, mcd);

	if(mcd->natural_heal_hp != tid) {
		if(battle_config.error_log)
			printf("merc_natural_heal_hp %d != %d\n",mcd->natural_heal_hp,tid);
		return 0;
	}
	mcd->natural_heal_hp = -1;

	bhp = mcd->status.hp;

	if(mcd->ud.walktimer == -1) {
		mcd->status.hp += mcd->nhealhp;
		if(mcd->status.hp > mcd->max_hp)
			mcd->status.hp = mcd->max_hp;
		if(bhp != mcd->status.hp && mcd->msd)
			clif_send_mercstatus(mcd->msd,0);
	}
	mcd->natural_heal_hp = add_timer(tick+MERC_NATURAL_HEAL_HP_INTERVAL,merc_natural_heal_hp,mcd->bl.id,0);

	return 0;
}

static int merc_natural_heal_sp(int tid,unsigned int tick,int id,int data)
{
	struct merc_data *mcd = map_id2mcd(id);
	int bsp;

	nullpo_retr(0, mcd);

	if(mcd->natural_heal_sp != tid) {
		if(battle_config.error_log)
			printf("merc_natural_heal_sp %d != %d\n",mcd->natural_heal_sp,tid);
		return 0;
	}
	mcd->natural_heal_sp = -1;

	bsp = mcd->status.sp;

	if(mcd->ud.walktimer == -1) {
		mcd->status.sp += mcd->nhealsp;
		if(mcd->status.sp > mcd->max_sp)
			mcd->status.sp = mcd->max_sp;
		if(bsp != mcd->status.sp && mcd->msd)
			clif_send_mercstatus(mcd->msd,0);
	}
	mcd->natural_heal_sp = add_timer(tick+MERC_NATURAL_HEAL_SP_INTERVAL,merc_natural_heal_sp,mcd->bl.id,0);

	return 0;
}

int merc_natural_heal_timer_delete(struct merc_data *mcd)
{
	nullpo_retr(0, mcd);

	if(mcd->natural_heal_hp != -1) {
		delete_timer(mcd->natural_heal_hp,merc_natural_heal_hp);
		mcd->natural_heal_hp = -1;
	}
	if(mcd->natural_heal_sp != -1) {
		delete_timer(mcd->natural_heal_sp,merc_natural_heal_sp);
		mcd->natural_heal_sp = -1;
	}

	return 0;
}

/*==========================================
 * 傭兵のデータをセーブ
 *------------------------------------------
 */
int merc_save_data(struct map_session_data *sd)
{
	struct merc_data *mcd;

	nullpo_retr(0, sd);
	nullpo_retr(0, mcd = sd->mcd);

	//if(battle_config.save_homun_temporal_intimate)
	//	pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",mcd->intimate);

	intif_save_mercdata(sd->status.account_id,&sd->mcd->status);

	return 0;
}

//
// 初期化物
//
/*==========================================
 * 傭兵初期ステータスデータ読み込み
 *------------------------------------------
 */
static int read_mercdb(void)
{
	FILE *fp;
	char line[1024];
	int i;
	int j=0;
	int lines, count = 0;
	struct script_code *script = NULL;
	char *filename[] = { "db/merc_db.txt", "db/addon/merc_db_add.txt" };

	// DB情報の初期化
	for(i=0; i<MAX_MERC_DB; i++) {
		if(merc_db[i].script)
			script_free_code(merc_db[i].script);
	}
	memset(merc_db,0,sizeof(merc_db));

	for(i=0;i<2;i++){
		fp=fopen(filename[i],"r");
		if(fp==NULL){
			if(i>0)
				continue;
			printf("can't read %s\n",filename[i]);
			return -1;
		}
		lines=0;
		while(fgets(line,1020,fp)){
			int nameid,i;
			char *str[50],*p,*np;
			lines++;

			if(line[0] == '/' && line[1] == '/')
				continue;

			for(i=0,p=line;i<32;i++){
				if((np=strchr(p,','))!=NULL){
					str[i]=p;
					*np=0;
					p=np+1;
				} else {
					str[i]=p;
					p+=strlen(p);
				}
			}

			nameid = atoi(str[0]);
			j = nameid - MERC_ID;

			if(j < 0 || j >= MAX_MERC_DB)
				continue;

			merc_db[j].class_     = nameid;
			merc_db[j].view_class = atoi(str[1]);
			strncpy(merc_db[j].name,str[2],24);
			strncpy(merc_db[j].jname,str[3],24);
			merc_db[j].base_level = atoi(str[4]);
			merc_db[j].hp         = atoi(str[5]);
			merc_db[j].sp         = atoi(str[6]);
			merc_db[j].str        = atoi(str[7]);
			merc_db[j].agi        = atoi(str[8]);
			merc_db[j].vit        = atoi(str[9]);
			merc_db[j].int_       = atoi(str[10]);
			merc_db[j].dex        = atoi(str[11]);
			merc_db[j].luk        = atoi(str[12]);

			merc_db[j].base       = atoi(str[13]);
			merc_db[j].hp_kmax    = atoi(str[14]);
			merc_db[j].hp_kmin    = atoi(str[15]);
			merc_db[j].sp_kmax    = atoi(str[16]);
			merc_db[j].sp_kmin    = atoi(str[17]);
			merc_db[j].str_k      = atoi(str[18]);
			merc_db[j].agi_k      = atoi(str[19]);
			merc_db[j].vit_k      = atoi(str[20]);
			merc_db[j].int_k      = atoi(str[21]);
			merc_db[j].dex_k      = atoi(str[22]);
			merc_db[j].luk_k      = atoi(str[23]);
			merc_db[j].aspd_k     = atoi(str[24]);
			merc_db[j].size       = atoi(str[25]);
			merc_db[j].race       = atoi(str[26]);
			merc_db[j].element    = atoi(str[27]);
			merc_db[j].range      = atoi(str[28]);
			merc_db[j].limit      = (unsigned int)atoi(str[29]);

			// force \0 terminal
			merc_db[i].name[23]  = '\0';
			merc_db[i].jname[23] = '\0';

			if((np = strchr(p,'{')) == NULL)
				continue;

			if(merc_db[j].script)
				script_free_code(merc_db[j].script);
			script = parse_script(np,filename[i],lines);

			merc_db[j].script = (script != &error_code)? script: NULL;
			count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n",filename[i],count);
	}
	return 0;
}

/*==========================================
 * 設定ファイル読み込む
 * merc_skill_tree.txt スキルツリー
 *------------------------------------------
 */
static int merc_readdb(void)
{
	int i,j,k,class_=0;
	FILE *fp;
	char line[1024],*p;

	// スキルツリー
	memset(merc_skill_tree,0,sizeof(merc_skill_tree));
	fp=fopen("db/merc_skill_tree.txt","r");
	if(fp==NULL){
		//printf("can't read db/merc_skill_tree.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)){
		int skillid;
		char *split[15];
		struct merc_skill_tree_entry *st;

		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<15 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 15)
			continue;
		class_ = atoi(split[0]);
		i = class_ - MERC_ID;
		if(i < 0 || i >= MAX_MERC_DB)
			continue;

		skillid = atoi(split[1]);
		st = merc_skill_tree[i];
		for(j=0; st[j].id && st[j].id != skillid; j++);

		if(j >= MAX_MERCSKILL_TREE - 1) {
			// 末尾はアンカーとして0にしておく必要がある
			printf("merc_readdb: skill (%d) is over max tree %d!!\n", skillid, MAX_MERCSKILL_TREE);
			continue;
		}
		if(j > 0 && skillid < st[j-1].id) {
			// スキルIDの昇順に並んでない場合
			int max = j;
			while(j > 0 && skillid < st[j-1].id) {
				j--;
			}
			memmove(&st[j+1], &st[j], (max-j)*sizeof(st[0]));
		}

		st[j].id  = skillid;
		st[j].max = atoi(split[2]);

		if(st[j].max > skill_get_max(skillid))
			st[j].max = skill_get_max(skillid);

		for(k=0; k<5; k++) {
			st[j].need[k].id = atoi(split[k*2+3]);
			st[j].need[k].lv = atoi(split[k*2+4]);
		}
		st[j].base_level = atoi(split[13]);
		st[j].intimate   = atoi(split[14]);
	}
	fclose(fp);
	printf("read db/merc_skill_tree.txt done\n");

	return 0;
}

/*==========================================
 * 傭兵DBのリロード
 *------------------------------------------
 */
void merc_reload(void)
{
	read_mercdb();
	merc_readdb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_merc(void)
{
	read_mercdb();
	merc_readdb();

	add_timer_func_list(merc_natural_heal_hp,"merc_natural_heal_hp");
	add_timer_func_list(merc_natural_heal_sp,"merc_natural_heal_sp");

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_merc(void)
{
	int i;

	for(i = 0; i < MAX_MERC_DB; i++) {
		if(merc_db[i].script) {
			script_free_code(merc_db[i].script);
		}
	}
	return 0;
}
