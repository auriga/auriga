/* homun.c
	関数名：homun_*		*hom*
	ホムンクルス ID 6001-6016	※2006/03/14現在
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "intif.h"
#include "clif.h"
#include "chrif.h"
#include "homun.h"
#include "itemdb.h"
#include "battle.h"
#include "mob.h"
#include "npc.h"
#include "script.h"
#include "status.h"
#include "unit.h"
#include "skill.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

struct homun_db homun_db[MAX_HOMUN_DB];
struct random_homun_data embryo_data[MAX_HOMUN_DB];
int embryo_default=6001;

static int homun_exp_table[6][MAX_LEVEL];

static struct {
	int id;
	int max;
	struct {
		short id,lv;
	} need[6];
	short base_level;
	int   intimate;
} homun_skill_tree[MAX_HOMUN_DB][100];

static int homun_calc_pos(struct homun_data *hd,int tx,int ty,int dir)
{
	int x,y,dx,dy;
	int i,j=0,k;

	nullpo_retr(0, hd);

	hd->ud.to_x = tx;
	hd->ud.to_y = ty;

	if(dir >= 0 && dir < 8) {
		dx = -dirx[dir]*2;
		dy = -diry[dir]*2;
		x = tx + dx;
		y = ty + dy;
		if(!(j=unit_can_reach(&hd->bl,x,y))) {
			if(dx > 0) x--;
			else if(dx < 0) x++;
			if(dy > 0) y--;
			else if(dy < 0) y++;
			if(!(j=unit_can_reach(&hd->bl,x,y))) {
				for(i=0;i<12;i++) {
					k = atn_rand()%8;
					dx = -dirx[k]*2;
					dy = -diry[k]*2;
					x = tx + dx;
					y = ty + dy;
					if((j=unit_can_reach(&hd->bl,x,y)))
						break;
					else {
						if(dx > 0) x--;
						else if(dx < 0) x++;
						if(dy > 0) y--;
						else if(dy < 0) y++;
						if((j=unit_can_reach(&hd->bl,x,y)))
							break;
					}
				}
				if(!j) {
					x = tx;
					y = ty;
					if(!unit_can_reach(&hd->bl,x,y))
						return 1;
				}
			}
		}
	}
	else
		return 1;

	hd->ud.to_x = x;
	hd->ud.to_y = y;
	return 0;
}
/*==========================================
 * 腹減り
 *------------------------------------------
 */
static int homun_hungry_cry(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd;

	sd=map_id2sd(id);
	if(sd==NULL || sd->hd==NULL)
		return 1;

	if(sd->hd->hungry_cry_timer != tid){
		if(battle_config.error_log)
			printf("homun_hungry_cry_timer %d != %d\n",sd->hd->hungry_cry_timer,tid);
		return 0;
	}
	sd->hd->hungry_cry_timer = -1;
	clif_emotion(&sd->hd->bl,28);
	sd->hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,0);

	return 0;
}
static int homun_hungry(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd;
	int interval;

	sd=map_id2sd(id);
	if(sd==NULL)
		return 1;
	if(!sd->status.homun_id || !sd->hd)
		return 1;

	if(sd->homun_hungry_timer != tid){
		if(battle_config.error_log)
			printf("homun_hungry_timer %d != %d\n",sd->homun_hungry_timer,tid);
		return 0;
	}
	sd->homun_hungry_timer = -1;

	sd->hd->status.hungry--;

	if(sd->hd->status.hungry==0) {
		sd->hd->status.hungry=1;		// 0にはならない
	}
	if(sd->hd->status.hungry <= 10){	// 10以下で減り始める(泣きエモを20秒に1回出すようになる)
		int f=0;
		if(sd->hd->intimate == sd->hd->status.intimate)
			f=1;
		sd->hd->status.intimate -= 20*battle_config.homun_intimate_rate/100;
		clif_emotion(&sd->hd->bl,28);
		clif_send_homdata(sd,0x100,sd->hd->intimate/100);
		if(sd->hd->status.intimate <= 0)
			sd->hd->status.intimate = 0;
		if(f)
			sd->hd->intimate = sd->hd->status.intimate;
		if(sd->hd->hungry_cry_timer == -1)
			sd->hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,0);
	}else if(sd->hd->hungry_cry_timer != -1){
		delete_timer(sd->hd->hungry_cry_timer,homun_hungry_cry);
		sd->hd->hungry_cry_timer = -1;
	}

	clif_send_homdata(sd,2,sd->hd->status.hungry);
	// 本鯖ではここでステータスを送らないが、送らないと"ホムが腹ぺこです！"が出ない
	clif_send_homstatus(sd,0);

	interval = 60*1000;

	sd->homun_hungry_timer = add_timer(tick+interval,homun_hungry,sd->bl.id,0);

	return 0;
}
int homun_hungry_timer_delete(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->homun_hungry_timer != -1) {
		delete_timer(sd->homun_hungry_timer,homun_hungry);
		sd->homun_hungry_timer = -1;
	}
	if(sd->hd && sd->hd->hungry_cry_timer != -1) {
		delete_timer(sd->hd->hungry_cry_timer,homun_hungry_cry);
		sd->hd->hungry_cry_timer = -1;
	}

	return 0;
}
/*==========================================
 * オートステ振り(statuspoint方式)
 *------------------------------------------
 */
int homun_upstatus(struct mmo_homunstatus *hd)
{
	int total,class,ret=0;
	nullpo_retr(1, hd);

	class = hd->class-HOM_ID;

	total = homun_db[class].str_k+homun_db[class].agi_k+homun_db[class].vit_k+homun_db[class].int_k+homun_db[class].dex_k+homun_db[class].luk_k;
	if(total <= 0) return 0;
// STポイントが足りなかった場合、
//・次にレベルが上がるまでSTポイントを保存するか	return 0
//・振れるだけ振るか								continue
#define AUT_ST_RET return 0
//#define AUT_ST_RET continue
	while(hd->status_point && ret<64){
		int s = atn_rand()%total;
		int require;
		ret++;
		if((s-=homun_db[class].str_k) <0){
			require = (hd->str==0)?1:(hd->str-1)/10+2;
			if(require < hd->status_point){
				hd->str++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else if((s-=homun_db[class].agi_k) <0){
			require = (hd->agi==0)?1:(hd->agi-1)/10+2;
			if(require < hd->status_point){
				hd->agi++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else if((s-=homun_db[class].vit_k) <0){
			require = (hd->vit==0)?1:(hd->vit-1)/10+2;
			if(require < hd->status_point){
				hd->vit++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else if((s-=homun_db[class].int_k)<0){
			require = (hd->int_==0)?1:(hd->int_-1)/10+2;
			if(require < hd->status_point){
				hd->int_++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else if((s-=homun_db[class].dex_k) <0){
			require = (hd->dex==0)?1:(hd->dex-1)/10+2;
			if(require < hd->status_point){
				hd->dex++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else if((s-=homun_db[class].luk_k) <0){
			require = (hd->luk==0)?1:(hd->luk-1)/10+2;
			if(require < hd->status_point){
				hd->luk++;
				hd->status_point-=require;
			}else{
				AUT_ST_RET;
			}
		}else{
			AUT_ST_RET;
		}
	}
	return 0;
}
/*==========================================
 * 上昇ステ計算(非statuspoint方式)
 *------------------------------------------
 */
int homun_upstatus2(struct mmo_homunstatus *hd)
{
	int class;
	nullpo_retr(1, hd);
	class = hd->class-HOM_ID;
	// 各BasePointに1割くらいの追加でボーナス上昇？
	if(atn_rand()%100 < homun_db[class].str_k)
		hd->str += (atn_rand()%(homun_db[class].base*100-90))/100+1;
	if(atn_rand()%100 < homun_db[class].agi_k)
		hd->agi += (atn_rand()%(homun_db[class].base*100-90))/100+1;
	if(atn_rand()%100 < homun_db[class].vit_k)
		hd->vit += (atn_rand()%(homun_db[class].base*100-90))/100+1;
	if(atn_rand()%100 < homun_db[class].int_k)
		hd->int_+= (atn_rand()%(homun_db[class].base*100-90))/100+1;
	if(atn_rand()%100 < homun_db[class].dex_k)
		hd->dex += (atn_rand()%(homun_db[class].base*100-90))/100+1;
	if(atn_rand()%100 < homun_db[class].luk_k)
		hd->luk += (atn_rand()%(homun_db[class].base*100-90))/100+1;
	return 0;
}
/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int homun_calc_status(struct homun_data *hd)
{
	int dstr,bl,aspd_k,lv;
	int aspd_rate=100,speed_rate=100,atk_rate=100,matk_rate=100,hp_rate=100,sp_rate=100;
	int flee_rate=100,def_rate=100,mdef_rate=100,critical_rate=100,hit_rate=100;
	nullpo_retr(1, hd);
	hd->atk		= 0;
	hd->matk	= 0;
	hd->hit		= 0;
	hd->flee	= 0;
	hd->def		= 0;
	hd->mdef	= 0;
	hd->critical= 0;
	hd->max_hp = hd->status.max_hp;
	hd->max_sp = hd->status.max_sp;
	hd->str = hd->status.str;
	hd->agi = hd->status.agi;
	hd->vit = hd->status.vit;
	hd->dex = hd->status.dex;
	hd->int_= hd->status.int_;
	hd->luk = hd->status.luk;
	hd->speed = 150;
	hd->nhealhp=0;
	hd->nhealsp=0;
	hd->hprecov_rate=100;
	hd->sprecov_rate=100;
	//チェンジインストラクション
	if((lv = homun_checkskill(hd,HVAN_INSTRUCT))>0)
	{
		static int instruct_str[11]={0,1,1,3,4,4,6,7,7,9,10};//10まで拡張
		if(lv > 10)
			lv = 10;
		hd->str+= instruct_str[lv];
		hd->int_+= lv;
	}
	//脳手術
	if((lv = homun_checkskill(hd,HLIF_BRAIN))>0)
	{
		sp_rate += lv;
		hd->sprecov_rate+=lv*3;
	}
	//アダマンティウムスキン
	if((lv = homun_checkskill(hd,HAMI_SKIN))>0)
	{
		hp_rate += lv*2;
		hd->def += lv*4;
		hd->hprecov_rate+=lv*5;
	}
	// ステータス変化による基本パラメータ補正ホムスキル
	if(hd->sc_count && hd->sc_data)
	{
		//緊急回避
		if(hd->sc_data[SC_AVOID].timer!=-1)
			speed_rate -= hd->sc_data[SC_AVOID].val1*10;
		//
		if(hd->sc_data[SC_CHANGE].timer!=-1)
			hd->int_ += 60;
		//ブラッドラスト
		if(hd->sc_data[SC_BLOODLUST].timer!=-1)
			atk_rate += hd->sc_data[SC_BLOODLUST].val1*10+20;
		//フリットムーブ
		if(hd->sc_data[SC_FLEET].timer!=-1)
		{
			aspd_rate -= hd->sc_data[SC_FLEET].val1*3;
			atk_rate+=5+hd->sc_data[SC_FLEET].val1*5;
		}
	}
	// ステータス変化による基本パラメータ補正
	if(battle_config.allow_homun_status_change && hd->sc_count && hd->sc_data)
	{
		//ゴスペルALL+20
		if(hd->sc_data[SC_INCALLSTATUS].timer!=-1){
			hd->str+= hd->sc_data[SC_INCALLSTATUS].val1;
			hd->agi+= hd->sc_data[SC_INCALLSTATUS].val1;
			hd->vit+= hd->sc_data[SC_INCALLSTATUS].val1;
			hd->int_+= hd->sc_data[SC_INCALLSTATUS].val1;
			hd->dex+= hd->sc_data[SC_INCALLSTATUS].val1;
			hd->luk+= hd->sc_data[SC_INCALLSTATUS].val1;
		}

		if(hd->sc_data[SC_INCREASEAGI].timer!=-1)	// 速度増加
			hd->agi += 2+hd->sc_data[SC_INCREASEAGI].val1;

		if(hd->sc_data[SC_DECREASEAGI].timer!=-1)	// 速度減少(agiはbattle.cで)
			hd->agi-= 2+hd->sc_data[SC_DECREASEAGI].val1;

		if(hd->sc_data[SC_BLESSING].timer!=-1){	// ブレッシング
			hd->str+= hd->sc_data[SC_BLESSING].val1;
			hd->dex+= hd->sc_data[SC_BLESSING].val1;
			hd->int_+= hd->sc_data[SC_BLESSING].val1;
		}
		if(hd->sc_data[SC_SUITON].timer!=-1){	// 水遁
			if(hd->sc_data[SC_SUITON].val3)
				hd->agi+=hd->sc_data[SC_SUITON].val3;
			if(hd->sc_data[SC_SUITON].val4)
				hd->speed = hd->speed*2;
		}

		if(hd->sc_data[SC_GLORIA].timer!=-1)	// グロリア
			hd->luk+= 30;
			
		if(hd->sc_data[SC_QUAGMIRE].timer!=-1){	// クァグマイア
			short subagi = 0;
			short subdex = 0;
			subagi = (hd->status.agi/2 < hd->sc_data[SC_QUAGMIRE].val1*10) ? hd->status.agi/2 : hd->sc_data[SC_QUAGMIRE].val1*10;
			subdex = (hd->status.dex/2 < hd->sc_data[SC_QUAGMIRE].val1*10) ? hd->status.dex/2 : hd->sc_data[SC_QUAGMIRE].val1*10;
			if(map[hd->bl.m].flag.pvp || map[hd->bl.m].flag.gvg){
				subagi/= 2;
				subdex/= 2;
			}
			hd->speed = hd->speed*4/3;
			hd->agi-= subagi;
			hd->dex-= subdex;
		}
	}

	dstr		= hd->str / 10;
	bl			= hd->status.base_level;
	aspd_k		= homun_db[hd->status.class-HOM_ID].aspd_k;
	
	hd->atk		+= hd->str * 2 + bl + dstr * dstr;
	hd->matk	+= hd->int_+(hd->int_/ 5) * (hd->int_/ 5);
	hd->hit		+= hd->dex + bl;
	hd->flee	+= hd->agi + bl;
	hd->def		+= hd->vit + hd->vit / 5 + bl / 10;
	hd->mdef	+= hd->int_/ 5 + bl / 10;
	hd->critical+= hd->luk / 3 + 1;
	hd->aspd	= aspd_k - (aspd_k * hd->agi / 250 + aspd_k * hd->dex / 1000);
	hd->aspd	-= 200;
	
	//ディフェンス
	if(hd->sc_data[SC_DEFENCE].timer!=-1)
		hd->def += hd->sc_data[SC_DEFENCE].val1*2;
	//オーバードスピード
	if(hd->sc_data[SC_SPEED].timer!=-1)
		hd->flee = hd->flee + 10 + hd->sc_data[SC_SPEED].val1*10;
	//補正
	if(atk_rate!=100)
		hd->atk = hd->atk*atk_rate/100;
	if(matk_rate!=100)
		hd->matk = hd->matk*matk_rate/100;
	if(hit_rate!=100)
		hd->hit = hd->hit*hit_rate/100;
	if(flee_rate!=100)
		hd->flee = hd->flee*flee_rate/100;
	if(def_rate!=100)
		hd->def = hd->def*def_rate/100;
	if(mdef_rate!=100)
		hd->mdef = hd->mdef*mdef_rate/100;
	if(critical_rate!=100)
		hd->critical = hd->critical*critical_rate/100;
	if(hp_rate!=100)
		hd->max_hp = hd->max_hp*hp_rate/100;
	if(sp_rate!=100)
		hd->max_sp = hd->max_sp*sp_rate/100;
	if(aspd_rate!=100)
		hd->aspd = hd->aspd*aspd_rate/100;
	if(speed_rate!=100)
		hd->speed = hd->speed*speed_rate/100;
		
	//メンタルチェンジ
	if(hd->sc_data && hd->sc_data[SC_CHANGE].timer!=-1)
	{
		int atk_,hp_;
		//
		atk_= hd->atk;
		hd->atk = hd->matk;
		hd->matk = atk_;
		//
		hp_= hd->max_hp;
		hd->max_hp = hd->max_sp;
		hd->max_sp = hp_;
	}
	if(hd->max_hp<=0) hd->max_hp=1;	// mhp 0 だとクライアントエラー
	if(hd->max_sp<=0) hd->max_sp=1;
	//自然回復
	hd->nhealhp = hd->max_hp/100 + hd->vit/5 + 2;
	hd->nhealsp = (hd->int_/6)+(hd->max_sp/100)+1;
	if(hd->int_ >= 120)
		hd->nhealsp += ((hd->int_-120)>>1) + 4;
	if(hd->hprecov_rate!=100)
		hd->nhealhp = hd->nhealhp*hd->hprecov_rate/100;
	if(hd->sprecov_rate!=100)
		hd->nhealsp = hd->nhealsp*hd->sprecov_rate/100;
	
	homun_calc_skilltree(hd);
	return 0;
}
/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int homun_recalc_status(struct homun_data *hd)
{
	int lv,class,hp,sp;
	nullpo_retr(1, hd);
	class = hd->status.class-HOM_ID;
	hd->status.max_hp = hd->status.hp = homun_db[class].hp;
	hd->status.max_sp = hd->status.sp = homun_db[class].sp;
	hd->status.str = homun_db[class].str;
	hd->status.agi = homun_db[class].agi;
	hd->status.vit = homun_db[class].vit;
	hd->status.int_= homun_db[class].int_;
	hd->status.dex = homun_db[class].dex;
	hd->status.luk = homun_db[class].luk;
	for(lv=1;lv<hd->status.base_level;lv++)
	{
		// 実測値の、最大値〜最小値でランダム上昇
		hp = homun_db[hd->status.class-HOM_ID].hp_kmax-homun_db[hd->status.class-HOM_ID].hp_kmin;
		hd->status.max_hp += homun_db[hd->status.class-HOM_ID].hp_kmin + atn_rand()%hp;
		sp = homun_db[hd->status.class-HOM_ID].sp_kmax-homun_db[hd->status.class-HOM_ID].sp_kmin;
		hd->status.max_sp += homun_db[hd->status.class-HOM_ID].sp_kmin + atn_rand()%sp;
		//	homun_upstatus(&sd->hd->status);	// オートステ振り(statuspoint方式)
		homun_upstatus2(&hd->status);	// ステアップ計算
		homun_calc_status(hd);			// ステータス計算
	}
	return 0;
}

int homun_get_create_homunid()
{
	int i,j,tmp,nameid;
	int list[MAX_HOMUN_DB];

	// シャッフルされた配列を生成
	for(i=0; i<MAX_HOMUN_DB; i++)
		list[i] = i;
	for(i=0; i<MAX_HOMUN_DB; i++) {
		j = atn_rand()%MAX_HOMUN_DB;
		tmp = list[i];
		list[i] = list[j];
		list[j] = tmp;
	}

	for(i=0; i<MAX_HOMUN_DB; i++) {
		nameid = list[i];
		if(atn_rand()%1000000 < embryo_data[nameid].per)
			return embryo_data[nameid].homunid;
	}
	return embryo_default;
}

/*==========================================
 * ホムンクルス新規作成
 *------------------------------------------
 */
int homun_create_hom(struct map_session_data *sd,int homunid)
{
	// 作成初期値　新密度:2000/100000　満腹度:50/100
	struct mmo_homunstatus *hd;
	int class = homunid-HOM_ID;	// 作成されるホムの選定方法不明

	nullpo_retr(1, sd);
	hd = (struct mmo_homunstatus *)aCalloc(1,sizeof(struct mmo_homunstatus));

	hd->class = class+HOM_ID;
	hd->account_id = sd->status.account_id;
	hd->char_id = sd->status.char_id;
	memcpy(hd->name,homun_db[class].jname,24);
	hd->base_level = homun_db[class].base_level;
	hd->base_exp = 0;
	hd->max_hp = 1;
	hd->max_sp = 0;
	hd->status_point = 0;
	hd->skill_point = homun_db[class].skillpoint; //初期スキルポイント導入するかも…成長しないホム用

// 初期ステータスをDBから埋め込み
	hd->max_hp = hd->hp = homun_db[class].hp;
	hd->max_sp = hd->sp = homun_db[class].sp;

	hd->str = homun_db[class].str;
	hd->agi = homun_db[class].agi;
	hd->vit = homun_db[class].vit;
	hd->int_= homun_db[class].int_;
	hd->dex = homun_db[class].dex;
	hd->luk = homun_db[class].luk;

	hd->equip =  0;
	hd->intimate = 2000;
	hd->hungry = 50;
	hd->incubate = 0;
	hd->rename_flag = 0;
	
	if(battle_config.save_homun_temporal_intimate)
		pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);

	intif_create_hom(sd->status.account_id,sd->status.char_id,hd);
	aFree(hd);
	return 0;
}

static int homun_natural_heal_hp(int tid,unsigned int tick,int id,int data);
static int homun_natural_heal_sp(int tid,unsigned int tick,int id,int data);

/*==========================================
 * 
 *------------------------------------------
 */
int homun_data_init(struct map_session_data *sd)
{
	struct homun_data *hd;
	int i,class;
	unsigned long tick = gettick();

	nullpo_retr(1, sd);
	nullpo_retr(1, (hd=sd->hd));

	memcpy(&sd->hd->status,&sd->hom,sizeof(struct mmo_homunstatus));

	class = sd->hd->status.class-HOM_ID;

	hd->bl.m = sd->bl.m;
	hd->bl.prev = hd->bl.next = NULL;
	hd->bl.x = hd->ud.to_x = sd->bl.x;
	hd->bl.y = hd->ud.to_y = sd->bl.y;
	homun_calc_pos(hd,sd->bl.x,sd->bl.y,sd->dir);
	hd->bl.x = hd->ud.to_x;
	hd->bl.y = hd->ud.to_y;
	hd->bl.id = npc_get_new_npc_id();
	hd->equip = 0;
	hd->dir = sd->dir;
	hd->speed = status_get_speed(&sd->bl);	//歩行速度は、コール時の主人のspeedになる
	hd->bl.subtype = MONS;
	hd->bl.type = BL_HOM;
	memset(&hd->state,0,sizeof(hd->state));
	hd->target_id = 0;
	hd->attackable = 1;	// これを0にすると、クライアントから攻撃パケットを出さなくなる
	hd->limits_to_growth = 0;
	hd->msd = sd;
	hd->view_class = homun_db[class].view_class;

	for(i=0;i<MAX_HOMSKILL;i++)
		hd->homskillstatictimer[i] = tick;
	////親密度
	if(battle_config.save_homun_temporal_intimate)
	{
		hd->intimate = pc_readglobalreg(sd,"HOM_TEMP_INTIMATE");
		if(hd->intimate==0)//旧互換
			hd->intimate = hd->status.intimate;
	}
	else
	{
		hd->intimate = hd->status.intimate;
	}
	// ステータス異常の初期化
	for(i=0;i<MAX_STATUSCHANGE;i++) {
		hd->sc_data[i].timer=-1;
		hd->sc_data[i].val1 = hd->sc_data[i].val2 = hd->sc_data[i].val3 = hd->sc_data[i].val4 = 0;
	}
	hd->sc_count=0;
	hd->status.option&=OPTION_MASK;
	hd->opt1 = 0;
	hd->opt2 = 0;
	hd->opt3 = 0;

	homun_calc_status(hd);			// ステータス計算

//	printf("call homun id:%d class:%d lv:%d\nstatus str:%d agi:%d vit:%d int:%d dex:%d luk:%d\n",
//		hd->status.homun_id,hd->status.class,hd->status.base_level,
//		hd->status.str,hd->status.agi,hd->status.vit,hd->status.int_,hd->status.dex,hd->status.luk);
	unit_dataset(&hd->bl);

	map_addiddb(&hd->bl);

	if(sd->homun_hungry_timer != -1)
		homun_hungry_timer_delete(sd);

	hd->natural_heal_hp = add_timer(gettick()+NATURAL_HEAL_HP_INTERVAL,homun_natural_heal_hp,hd->bl.id,0);
	hd->natural_heal_sp = add_timer(gettick()+NATURAL_HEAL_SP_INTERVAL,homun_natural_heal_sp,hd->bl.id,0);
	sd->homun_hungry_timer = add_timer(gettick()+60*1000,homun_hungry,sd->bl.id,0);
	if(hd->status.hungry <10)
		hd->hungry_cry_timer = add_timer(gettick()+20*1000,homun_hungry_cry,sd->bl.id,0);
	else
		hd->hungry_cry_timer = -1;
	hd->view_size =  0;

	return 0;
}
/*==========================================
 * コールホムンクルス
 *------------------------------------------
 */
int homun_callhom(struct map_session_data *sd)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->status.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id){	// 作成済みなら、出す
		sd->hd = (struct homun_data *)aCalloc(1,sizeof(struct homun_data));
		homun_data_init(sd);
		if(sd->bl.prev != NULL)
		{
			if(sd->hd->status.hp <= 0){	// 死亡
				clif_skill_fail(sd,AM_CALLHOMUN,0,0);
				if(sd->hd->natural_heal_hp != -1 || sd->hd->natural_heal_sp != -1)
					homun_natural_heal_timer_delete(sd->hd);
				if(sd->homun_hungry_timer != -1)
					homun_hungry_timer_delete(sd);
				aFree(sd->hd);
				sd->hd = NULL;
				return 0;
			}
			map_addblock(&sd->hd->bl);
			mob_ai_hard_spawn( &sd->hd->bl, 1 );
			clif_spawnhom(sd->hd);
			clif_send_homdata(sd,0,0);
			clif_send_homstatus(sd,1);
			clif_send_homstatus(sd,0);
			clif_homskillinfoblock(sd);
			sd->hd->status.incubate = 1;
			homun_save_data(sd);
			skill_unit_move(&sd->hd->bl,gettick(),1);
		}
	}else{						// 初誕生なら、データ作成
		sd->status.homun_id = 0;
		for(i=0;i<MAX_INVENTORY;i++){
			if(sd->status.inventory[i].nameid==7142){	// エンブリオ所持を確認
				pc_delitem(sd,i,1,0);	// エンブリオ消去
			//if(atn_rand()%100<80)		// 成功率不明〜
				homun_create_hom(sd,homun_get_create_homunid());
				return 0;
			}
		}
		clif_skill_fail(sd,AM_CALLHOMUN,0,0);
	}

	return 0;
}
/*==========================================
 * interからホムのデータ受信
 *------------------------------------------
 */
int homun_recv_homdata(int account_id,struct mmo_homunstatus *p,int flag)
{
	struct map_session_data *sd;

	sd = map_id2sd(account_id);

	if(!p || sd == NULL)
		return 0;

	if( !pc_checkskill( sd, AM_CALLHOMUN ) && sd->status.homun_id == 0 ) {
		// コールホムンクルス未習得かつ未所持で無視(転生やリセットなど)
		return 0;
	}

	if(sd->status.homun_id > 0) {
		memcpy(&sd->hom,p,sizeof(struct mmo_homunstatus));
		//生命の倫理未習得時格納
		if(!pc_checkskill( sd, AM_BIOETHICS))
			sd->hom.incubate = 0;
		if(sd->hom.incubate && sd->hom.hp > 0)
		{
			homun_callhom(sd);
			clif_homskillinfoblock(sd);
		}
	} else if(sd->status.homun_id==0 && !sd->hd) {	// ホム新規作成
		memcpy(&sd->hom,p,sizeof(struct mmo_homunstatus));
		sd->status.homun_id = sd->hom.homun_id;
		homun_callhom(sd);
	}
	return 0;
}
/*==========================================
 * 安息	...エンブリオはインベントリには戻らない
 *------------------------------------------
 */
int homun_return_embryo(struct map_session_data *sd)
{
	struct homun_data *hd;
	nullpo_retr(0, sd);
	nullpo_retr(0,(hd=sd->hd));
	if(sd->status.homun_id > 0){
		//親密度保存
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
		hd->status.incubate = 0;
		homun_save_data(sd);
		unit_free(&hd->bl,0);
	}
	return 0;
}
/*==========================================
 * リザホム
 *------------------------------------------
 */
int homun_revive(struct map_session_data *sd,int skilllv)
{
	nullpo_retr(0, sd);

	if(sd->status.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id){
		if(sd->hom.hp > 0){
		clif_skill_fail(sd,AM_RESURRECTHOMUN,0,0);
		return 0;
		}
	} else {
		clif_skill_fail(sd,AM_RESURRECTHOMUN,0,0);
		return 0;
	}
// 蘇生時HP = 死亡時HP（≦0）+ MAXHP * (Skill Lv * 0.2)
	sd->hom.hp = sd->hom.hp + sd->hom.max_hp * skilllv / 5;
	if(sd->hom.max_hp<sd->hom.hp)
		sd->hom.hp=sd->hom.max_hp;
		homun_callhom(sd);
	return 0;
}
/*==========================================
 * エサをあげる
 *------------------------------------------
 */
int homun_food(struct map_session_data *sd)
{
	int i,t,food,class,emotion;

	nullpo_retr(1, sd);
	if(!sd->hd)
		return 1;

	if(sd->status.homun_id == 0)
		return 1;

	class = sd->hd->status.class-HOM_ID;
	food = homun_db[class].FoodID;

	i=pc_search_inventory(sd,food);
	if(i < 0) {
		clif_hom_food(sd,food,0);
		return 1;
	}
	pc_delitem(sd,i,1,0);
	t = sd->hd->status.hungry;
	if(t > 90){
		sd->hd->status.intimate -= 50*battle_config.homun_intimate_rate/100;
		sd->hd->intimate -= 50*battle_config.homun_intimate_rate/100;
		emotion = 16;
	}else if(t > 75){
		sd->hd->status.intimate -= 30*battle_config.homun_intimate_rate/100;
		sd->hd->intimate -= 30*battle_config.homun_intimate_rate/100;
		emotion = 19;
	}else if(t > 25){
		sd->hd->status.intimate += 80*battle_config.homun_intimate_rate/100;
		sd->hd->intimate += 80*battle_config.homun_intimate_rate/100;
		emotion = 2;
	}else if(t > 10){
		sd->hd->status.intimate +=100*battle_config.homun_intimate_rate/100;
		sd->hd->intimate +=100*battle_config.homun_intimate_rate/100;
		emotion = 2;
	}else{
		sd->hd->status.intimate += 50*battle_config.homun_intimate_rate/100;
		sd->hd->intimate += 50*battle_config.homun_intimate_rate/100;
		emotion = 2;
	}
	if(sd->hd->status.intimate <= 0)
		sd->hd->status.intimate = 0;
	if(sd->hd->status.intimate > 100000)
		sd->hd->status.intimate = 100000;
	if(sd->hd->intimate <= 0)
		sd->hd->intimate = 0;
	if(sd->hd->intimate > 100000)
		sd->hd->intimate = 100000;
	sd->hd->status.hungry += 10;
	if(sd->hd->status.hungry > 100)
		sd->hd->status.hungry = 100;

	if(sd->hd->hungry_cry_timer != -1){
		delete_timer(sd->hd->hungry_cry_timer,homun_hungry_cry);
		sd->hd->hungry_cry_timer = -1;
	}

	clif_emotion(&sd->hd->bl,emotion);
	clif_send_homdata(sd,2,sd->hd->status.hungry);
	clif_send_homdata(sd,0x100,sd->hd->intimate/100);
	clif_send_homstatus(sd,0);
	clif_hom_food(sd,food,1);

	return 0;
}
/*==========================================
 * ホム削除
 *------------------------------------------
 */
int homun_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);
	if(sd->status.homun_id > 0 && sd->hd){
		//親密度保存
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",2000);//初期値に
		unit_free(&sd->hd->bl,0);
		intif_delete_homdata(sd->status.account_id,sd->status.char_id,sd->status.homun_id);
		sd->status.homun_id = 0;
		memset(&sd->hom,0,sizeof(struct mmo_homunstatus));
		pc_makesavestatus(sd);
		chrif_save(sd);
		storage_storage_save(sd);
	}
	return 0;
}
/*==========================================
 * ホムのメニューの応答
 *------------------------------------------
 */
int homun_menu(struct map_session_data *sd,int menunum)
{
	nullpo_retr(0, sd);
	if(!sd->hd) return 0;

	switch(menunum) {
		case 0:
			clif_send_homstatus(sd,0);
			break;
		case 1:
			homun_food(sd);
			break;
		case 2:
			homun_delete_data(sd);
			break;
	}
	return 0;
}
/*==========================================
 * 待機命令などで、主人の下へ移動
 *------------------------------------------
 */
int homun_return_master(struct map_session_data *sd)
{
	struct homun_data *hd;
	nullpo_retr(0, sd);
	nullpo_retr(0,(hd=sd->hd));
	homun_calc_pos(hd,sd->bl.x,sd->bl.y,sd->dir);
	unit_walktoxy(&hd->bl,hd->ud.to_x,hd->ud.to_y);
	return 0;
}
/*==========================================
 * 名前の変更
 *------------------------------------------
 */
int homun_change_name(struct map_session_data *sd,char *name)
{
	int i;

	nullpo_retr(1, sd);

	for(i=0;i<24 && name[i];i++){
		if( !(name[i]&0xe0) || name[i]==0x7f )
			return 1;
	}
	if(!sd->hd)
		return 1;
	if(sd->hd->status.rename_flag == 1 && battle_config.pet_rename == 0)
		return 1;

	unit_stop_walking(&sd->hd->bl,1);
	memcpy(sd->hd->status.name,name,24);
	homun_save_data(sd);
	clif_clearchar_area(&sd->hd->bl,0);
	clif_spawnhom(sd->hd);
	clif_send_homstatus(sd,1);
	clif_send_homstatus(sd,0);
	sd->hd->status.rename_flag = 1;
//	clif_hom_equip(sd->hd,sd->hom.equip);
	clif_send_homstatus(sd,0);

	return 0;
}

/*==========================================
 * classを変更
 * class == -1 でホムを進化させる
 * class == 0 にすると、進化後のclassに変更（進化するわけではない==ステ上昇はなどはなし）
 *------------------------------------------
 */
int homun_change_class( struct map_session_data *sd, int class )
{
	int new_class = 0;

	nullpo_retr(1, sd);

	if( !sd->hd )
	{
		return 1;
	}

	// use evolved class
	if( class <= 0 )
	{
		int index = sd->hd->status.class - HOM_ID;
		new_class = homun_db[ index ].evo_class;
	}
	else
	{
		new_class = class;
	}

	// validation
	if( HOM_ID <= new_class && new_class < HOM_ID + MAX_HOMUN_DB );
	else
	{
		return 1;
	}

	// change class
	sd->hd->status.class = new_class;
	sd->hd->view_class = homun_db[ new_class - HOM_ID ].view_class;

	// evolution mode
	if( class == -1 )
	{
		// change intimate to 19
		sd->hd->intimate = 1900;

		// gain all statuses by 1 ~ 10
		sd->hd->status.str += 1 + atn_rand() % 10;
		sd->hd->status.vit += 1 + atn_rand() % 10;
		sd->hd->status.agi += 1 + atn_rand() % 10;
		sd->hd->status.int_+= 1 + atn_rand() % 10;
		sd->hd->status.dex += 1 + atn_rand() % 10;
		sd->hd->status.luk += 1 + atn_rand() % 10;
	}

	homun_return_embryo( sd );
	homun_callhom( sd );

	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int homun_checkskill(struct homun_data *hd,int skill_id)
{
	if(hd == NULL) return 0;
	if(skill_id >= HOM_SKILLID) skill_id -= HOM_SKILLID;
	if(skill_id >= MAX_HOMSKILL) return 0;
	if(hd->status.skill[skill_id].id == skill_id+HOM_SKILLID)
		return (hd->status.skill[skill_id].lv);

	return 0;
}
/*==========================================
 * スキルポイント割り振り
 *------------------------------------------
 */
void homun_skillup(struct map_session_data *sd, int skill_num)
{
	struct homun_data *hd;
	int skillid;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));

	skillid = skill_num - HOM_SKILLID;
	if(skillid < 0 || skillid >= HOM_SKILLID)
		return;

	if( hd->status.skill_point>0 &&
		hd->status.skill[skillid].id!=0 &&
		hd->status.skill[skillid].lv < skill_get_max(skill_num) )
	{
		hd->status.skill[skillid].lv++;
		hd->status.skill_point--;
		homun_calc_skilltree(hd);
		clif_homskillup(sd,skill_num);
		clif_send_homstatus(hd->msd,0);
		clif_homskillinfoblock(hd->msd);
	}

	return;
}
/*==========================================
 * 覚えられるスキルの計算
 *------------------------------------------
 */
int homun_calc_skilltree(struct homun_data *hd)
{
	int i,id=0;
	int c=0,flag;

	nullpo_retr(0, hd);
	c = hd->status.class-HOM_ID;

	for(i=0;i<MAX_HOMSKILL;i++)
		hd->status.skill[i].id=0;
	do{
		flag=0;
		for(i=0;(id=homun_skill_tree[c][i].id)>0;i++){
			int j,f=1;
			for(j=0;j<5;j++) {
				if( homun_skill_tree[c][i].need[j].id &&
					homun_checkskill(hd,homun_skill_tree[c][i].need[j].id) < homun_skill_tree[c][i].need[j].lv)
					f=0;
			}
			if(hd->status.base_level < homun_skill_tree[c][i].base_level)
				f=0;
			if(hd->status.intimate < homun_skill_tree[c][j].intimate)
				f = 0;
			id=id-HOM_SKILLID;
			if(f && hd->status.skill[id].id==0 && id>=0){
				hd->status.skill[id].id=id+HOM_SKILLID;
				flag=1;
			}
		}
	}while(flag);
	return 0;
}
/*==========================================
 * レベルアップ
 *------------------------------------------
 */
int homun_checkbaselevelup(struct homun_data *hd)
{
	int next = homun_nextbaseexp(hd);
	int hp,sp;

	nullpo_retr(0, hd);

	if(hd->status.base_exp >= next && next > 0){
		// base側レベルアップ処理
		hd->status.base_exp -= next;

		hd->status.base_level ++;
	//	hd->status.status_point += 15 + (hd->status.base_level+14)/3;	// 微調整してもうまくいかず・・・
		if(hd->status.base_level%3==0)	// 3レベル毎にSkillPoint加算
			hd->status.skill_point ++;

		// 実測値の、最大値〜最小値でランダム上昇
		hp = homun_db[hd->status.class-HOM_ID].hp_kmax-homun_db[hd->status.class-HOM_ID].hp_kmin;
		hd->status.max_hp += homun_db[hd->status.class-HOM_ID].hp_kmin + atn_rand()%hp;
		sp = homun_db[hd->status.class-HOM_ID].sp_kmax-homun_db[hd->status.class-HOM_ID].sp_kmin;
		hd->status.max_sp += homun_db[hd->status.class-HOM_ID].sp_kmin + atn_rand()%sp;

	//	homun_upstatus(&hd->status);	// オートステ振り(statuspoint方式)
		homun_upstatus2(&hd->status);	// ステアップ計算
		homun_calc_status(hd);			// ステータス計算
		homun_heal(hd,hd->max_hp,hd->max_sp);
		clif_misceffect2(&hd->bl,568);
		if(hd->msd){
			clif_send_homstatus(hd->msd,0);
			clif_homskillinfoblock(hd->msd);
		}
		return 1;
	}

	return 0;
}
/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int homun_gainexp(struct homun_data *hd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp)
{
	int per;
	atn_bignumber next;

	nullpo_retr(0, hd);

	if(hd->bl.prev == NULL || unit_isdead(&hd->bl))
		return 0;

	if(md && md->sc_data && md->sc_data[SC_RICHMANKIM].timer != -1) {
		base_exp = base_exp * (125 + md->sc_data[SC_RICHMANKIM].val1*11)/100;
		job_exp  = job_exp  * (125 + md->sc_data[SC_RICHMANKIM].val1*11)/100;
	}

	if(hd->msd) {	// 主人へ指定倍の経験値
		atn_bignumber mbexp=0, mjexp=0;
		if(battle_config.master_get_homun_base_exp)
			mbexp = base_exp * battle_config.master_get_homun_base_exp / 100;
		if(battle_config.master_get_homun_job_exp)
			mjexp = job_exp  * battle_config.master_get_homun_job_exp / 100;

		if(mbexp || mjexp)
			pc_gainexp(hd->msd,md,mbexp,mjexp);
	}

	per = battle_config.next_exp_limit;
	if(base_exp > 0) {
		if((next = homun_nextbaseexp(hd)) > 0) {
			while(base_exp + hd->status.base_exp >= next) {	// LvUP
				atn_bignumber temp_exp = next - hd->status.base_exp;
				int rate = (int)(100 - (atn_bignumber)hd->status.base_exp * 100 / next);
				if(per - rate < 0)
					break;
				per -= rate;
				hd->status.base_exp = (int)next;
				if(!homun_checkbaselevelup(hd) || (next = homun_nextbaseexp(hd)) <= 0)
					break;
				base_exp -= temp_exp;
			}
			if((next = homun_nextbaseexp(hd)) > 0 && (base_exp * 100 / next) > per)
				hd->status.base_exp = (int)(next * per / 100);
			else if(base_exp + hd->status.base_exp > 0x7fffffff)
				hd->status.base_exp = 0x7fffffff;
			else
				hd->status.base_exp += (int)base_exp;

			if(hd->status.base_exp < 0)
				hd->status.base_exp = 0;
			homun_checkbaselevelup(hd);
		} else {
			if(base_exp + hd->status.base_exp > 0x7fffffff)
				hd->status.base_exp = 0x7fffffff;
			else
				hd->status.base_exp += (int)base_exp;
		}
		if(hd->msd)
			clif_send_homstatus(hd->msd,0);
	}

	return 0;
}
/*==========================================
 * base level側必要経験値計算
 *------------------------------------------
 */
int homun_nextbaseexp(struct homun_data *hd)
{
	int i;
	nullpo_retr(0, hd);

	if(hd->status.base_level>=MAX_LEVEL || hd->status.base_level<=0)
		return 0;

	i = homun_db[hd->status.class-HOM_ID].exp_table;
	/*
	if(hd->status.class >= 6001 && hd->status.class < 6005) i=0;		// 第一期ホム（4種）
	else if(hd->status.class >= 6005 && hd->status.class < 6009) i=1;	// 第二期ホム（4種）
	else if(hd->status.class >= 6009 && hd->status.class < 6013) i=2;	// 第一期ホム進化（4種）
	else if(hd->status.class >= 6013 && hd->status.class < 6017) i=3;	// 第二期ホム進化（4種）
	else  i=0;		// その他？
	*/
	return homun_exp_table[i][hd->status.base_level-1];
}
/*==========================================
 * hdにdamageのダメージ
 *------------------------------------------
 */
int homun_damage(struct block_list *src,struct homun_data *hd,int damage)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, hd);
	nullpo_retr(0,(sd=hd->msd));

	// 既に死んでいたら無効
	if(unit_isdead(&hd->bl))
		return 0;

	// 歩いていたら足を止める
	unit_stop_walking(&hd->bl,battle_config.pc_hit_stop_type);

	if(damage>0)
		skill_stop_gravitation(&hd->bl);

	if(hd->bl.prev==NULL){
		if(battle_config.error_log)
			printf("homun_damage : BlockError!!\n");
		return 0;
	}

	if(hd->status.hp > hd->max_hp)
		hd->status.hp = hd->max_hp;

	// over kill分は丸める
	if(damage>hd->status.hp)
		damage=hd->status.hp;

	hd->status.hp-=damage;

	if (hd->status.option & 0x02)
		status_change_end(&hd->bl, SC_HIDING, -1);
	if ((hd->status.option & 0x4004) == 4)
		status_change_end(&hd->bl, SC_CLOAKING, -1);
	if ((hd->status.option & 0x4004) == 0x4004)
		status_change_end(&hd->bl, SC_CHASEWALK, -1);

	clif_send_homstatus(sd,0);

	// 死亡していた
	if(hd->status.hp<=0){
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
		// スキルユニットからの離脱
		hd->status.hp = 1;
		skill_unit_move(&hd->bl,gettick(),0);
		hd->status.hp = 0;

		hd->status.incubate = 0;
		unit_free(&hd->bl,1);
	}
	return 0;
}
/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int homun_heal(struct homun_data *hd,int hp,int sp)
{
//	if(battle_config.battle_log)
//		printf("heal %d %d\n",hp,sp);

	nullpo_retr(0, hd);

	// バーサーク中は回復させない
	if(hd->sc_data && hd->sc_data[SC_BERSERK].timer!=-1) {
		if (sp > 0)
			sp = 0;
		if (hp > 0)
			hp = 0;
	}

	if(hp+hd->status.hp > hd->max_hp)
		hp = hd->max_hp - hd->status.hp;
	if(sp+hd->status.sp > hd->max_sp)
		sp = hd->max_sp - hd->status.sp;
	hd->status.hp+=hp;
	if(hd->status.hp <= 0) {
		hd->status.hp = 0;
		homun_damage(NULL,hd,1);
		hp = 0;
	}
	hd->status.sp+=sp;
	if(hd->status.sp <= 0)
		hd->status.sp = 0;
	if((hp || sp) && hd->msd)
		clif_send_homstatus(hd->msd,0);

	return hp + sp;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static int homun_natural_heal_hp(int tid,unsigned int tick,int id,int data)
{
	struct homun_data *hd = map_id2hd(id);
	int bhp;

	nullpo_retr(0, hd);

	if(hd->natural_heal_hp != tid){
		if(battle_config.error_log)
			printf("homun_natural_heal_hp %d != %d\n",hd->natural_heal_hp,tid);
		return 0;
	}
	hd->natural_heal_hp = -1;

	bhp=hd->status.hp;

	if(hd->ud.walktimer == -1) {
		hd->status.hp += hd->nhealhp;
		if(hd->status.hp > hd->max_hp)
			hd->status.hp = hd->max_hp;
		if(bhp!=hd->status.hp && hd->msd)
			clif_send_homstatus(hd->msd,0);
	}
	hd->natural_heal_hp = add_timer(tick+NATURAL_HEAL_HP_INTERVAL,homun_natural_heal_hp,hd->bl.id,0);

	return 0;
}

static int homun_natural_heal_sp(int tid,unsigned int tick,int id,int data)
{
	struct homun_data *hd = map_id2hd(id);
	int bsp;

	nullpo_retr(0, hd);

	if(hd->natural_heal_sp != tid){
		if(battle_config.error_log)
			printf("homun_natural_heal_sp %d != %d\n",hd->natural_heal_sp,tid);
		return 0;
	}
	hd->natural_heal_sp = -1;

	bsp = hd->status.sp;

	if(hd->intimate < hd->status.intimate)
	{
		hd->intimate+=battle_config.homun_temporal_intimate_resilience;
		if(hd->status.intimate<hd->intimate)
			hd->intimate = hd->status.intimate;
		clif_send_homdata(hd->msd,0x100,hd->intimate/100);
	}

	if(hd->ud.walktimer == -1){
		hd->status.sp += hd->nhealsp;
		if(hd->status.sp > hd->max_sp)
			hd->status.sp = hd->max_sp;
		if(bsp != hd->status.sp && hd->msd)
			clif_send_homstatus(hd->msd,0);
	}
	hd->natural_heal_sp = add_timer(tick+NATURAL_HEAL_SP_INTERVAL,homun_natural_heal_sp,hd->bl.id,0);

	return 0;
}
int homun_natural_heal_timer_delete(struct homun_data *hd)
{
	nullpo_retr(0, hd);

	if(hd->natural_heal_hp != -1) {
		delete_timer(hd->natural_heal_hp,homun_natural_heal_hp);
		hd->natural_heal_hp = -1;
	}
	if(hd->natural_heal_sp != -1) {
		delete_timer(hd->natural_heal_sp,homun_natural_heal_sp);
		hd->natural_heal_sp = -1;
	}

	return 0;
}
/*==========================================
 * ホムのデータをセーブ
 *------------------------------------------
 */
int homun_save_data(struct map_session_data *sd)
{
	struct homun_data *hd;
	nullpo_retr(0, sd);
	nullpo_retr(0,(hd=sd->hd));

	if(battle_config.save_homun_temporal_intimate)
		pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
	memcpy(&sd->hom,&hd->status,sizeof(struct mmo_homunstatus));
	intif_save_homdata(sd->status.account_id,&sd->hd->status);

	return 0;
}
/*==========================================
 * ホムンクルス初期ステータスデータ読み込み
 *------------------------------------------
 */ 
int read_homundb(void)
{
	FILE *fp;
	char line[1024];
	int i;
	int j=0;
	int lines, count = 0;
	struct script_code *script = NULL;
	char *filename[]={"db/homun_db.txt","db/addon/homun_db_add.txt"};

	// DB情報の初期化
	for(i=0; i<MAX_HOMUN_DB; i++) {
		if(homun_db[i].script)
			script_free_code(homun_db[i].script);
	}
	memset(homun_db,0,sizeof(homun_db));

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

			nameid=atoi(str[0]);
			j = nameid-HOM_ID;

			if(j<0 || j>=MAX_HOMUN_DB)
				continue;

			homun_db[j].class = nameid;
			homun_db[j].view_class = atoi(str[1]);
			memcpy(homun_db[j].name,str[2],24);
			memcpy(homun_db[j].jname,str[3],24);
			homun_db[j].base_level=atoi(str[4]);
			homun_db[j].AcceID=atoi(str[5]);
			homun_db[j].FoodID=atoi(str[6]);
			homun_db[j].hp=atoi(str[7]);
			homun_db[j].sp=atoi(str[8]);
			homun_db[j].str=atoi(str[9]);
			homun_db[j].agi=atoi(str[10]);
			homun_db[j].vit=atoi(str[11]);
			homun_db[j].int_=atoi(str[12]);
			homun_db[j].dex=atoi(str[13]);
			homun_db[j].luk=atoi(str[14]);

			homun_db[j].base=atoi(str[15]);
			homun_db[j].hp_kmax=atoi(str[16]);
			homun_db[j].hp_kmin=atoi(str[17]);
			homun_db[j].sp_kmax=atoi(str[18]);
			homun_db[j].sp_kmin=atoi(str[19]);
			homun_db[j].str_k=atoi(str[20]);
			homun_db[j].agi_k=atoi(str[21]);
			homun_db[j].vit_k=atoi(str[22]);
			homun_db[j].int_k=atoi(str[23]);
			homun_db[j].dex_k=atoi(str[24]);
			homun_db[j].luk_k=atoi(str[25]);
			homun_db[j].aspd_k=atoi(str[26]);
			homun_db[j].size=atoi(str[27]);
			homun_db[j].race=atoi(str[28]);
			homun_db[j].element=atoi(str[29]);
			homun_db[j].evo_class=atoi(str[30]);
			homun_db[j].exp_table=atoi(str[31]);
			homun_db[j].skillpoint = homun_db[j].base_level/3; //予約 とりあえずベース/3
			
			if((np=strchr(p,'{'))==NULL)
				continue;

			if(homun_db[j].script)
				script_free_code(homun_db[j].script);
			script = parse_script(np,filename[i],lines);

			homun_db[j].script = (script != &error_code)? script: NULL;
			count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n",filename[i],count);
	}
	return 0;
}
//
// 初期化物
//
/*==========================================
 * 設定ファイル読み込む
 * exp.txt 必要経験値
 * skill_tree.txt スキルツリー
 *------------------------------------------
 */
int homun_readdb(void)
{
	int i,j,k,class=0;
	FILE *fp;
	char line[1024],*p;

	// 必要経験値読み込み
	memset(homun_exp_table, 0, sizeof(homun_exp_table));
	fp=fopen("db/exp_homun.txt","r");
	if(fp==NULL){
		printf("can't read db/exp_homun.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		int b0,b1,b2,b3,b4,b5;
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(sscanf(line,"%d,%d,%d,%d,%d,%d",&b0,&b1,&b2,&b3,&b4,&b5)!=6)
			continue;
		homun_exp_table[0][i]=b0;
		homun_exp_table[1][i]=b1;
		homun_exp_table[2][i]=b2;
		homun_exp_table[3][i]=b3;
		homun_exp_table[4][i]=b4;
		homun_exp_table[5][i]=b5;
		i++;
		if(i > MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read db/exp_homun.txt done\n");

	// スキルツリー
	memset(homun_skill_tree,0,sizeof(homun_skill_tree));
	fp=fopen("db/homun_skill_tree.txt","r");
	if(fp==NULL){
		printf("can't read db/homun_skill_tree.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)){
		char *split[50];
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<15 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j<15)
			continue;
		class=atoi(split[0]);
		i=class-HOM_ID;
		if(i<0 || i>=MAX_HOMUN_DB)
			continue;
		for(j=0;homun_skill_tree[i][j].id;j++);
		homun_skill_tree[i][j].id=atoi(split[1]);
		homun_skill_tree[i][j].max=atoi(split[2]);
		for(k=0;k<5;k++){
			homun_skill_tree[i][j].need[k].id=atoi(split[k*2+3]);
			homun_skill_tree[i][j].need[k].lv=atoi(split[k*2+4]);
		}
		homun_skill_tree[i][j].base_level=atoi(split[13]);
		homun_skill_tree[i][j].intimate=atoi(split[14]);
	}
	fclose(fp);
	printf("read db/homun_skill_tree.txt done\n");

	return 0;
}

/*==========================================
 * ランダムアイテム出現データの読み込み
 *------------------------------------------
 */
static int homun_read_embryodb(void)
{
	FILE *fp;
	char line[1024];
	int ln=0,count=0;
	int homunid,j;
	char *str[10],*p;

	// 読み込む度、初期化
 	embryo_default=6001;
	memset(embryo_data, 0, sizeof(embryo_data));

	if( (fp=fopen("db/embryo_db.txt","r"))==NULL ){
		puts("can't read db/embryo_db.txt");
		return 1;
	}

	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<3 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}

		if(str[0]==NULL)
			continue;

		homunid=atoi(str[0]);
		if(homunid == 0) {
			if(str[2])
				embryo_default = atoi(str[2]);
			continue;
		}
		ln = homunid - HOM_ID;
		if(ln < 0 || ln >= MAX_HOMUN_DB)
			continue;
		if(str[2]){
			embryo_data[ln].homunid = homunid;
			embryo_data[ln].per = atoi(str[2]);
			count++;
		}
	}
	fclose(fp);
	printf("read db/embryo_db.txt done (count=%d)\n",count);

	return 0;
}

/*==========================================
 * ホムDBのリロード
 *------------------------------------------
 */
void homun_reload(void)
{
	read_homundb();
	homun_readdb();
	homun_read_embryodb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_homun(void)
{
	memset(homun_db,0,sizeof(homun_db));
	read_homundb();
	homun_readdb();
	homun_read_embryodb();
	add_timer_func_list(homun_natural_heal_hp,"homun_natural_heal_hp");
	add_timer_func_list(homun_natural_heal_sp,"homun_natural_heal_sp");
	add_timer_func_list(homun_hungry,"homun_hungry");
	add_timer_func_list(homun_hungry_cry,"homun_hungry_cry");
	return 0;
}

int do_final_homun(void) {
	int i;
	for(i = 0;i < MAX_HOMUN_DB; i++) {
		if(homun_db[i].script) {
			script_free_code(homun_db[i].script);
		}
	}
	return 0;
}
