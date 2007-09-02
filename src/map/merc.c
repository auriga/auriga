
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

#include "clif.h"
#include "chrif.h"
#include "map.h"
#include "merc.h"
#include "mob.h"
#include "npc.h"
#include "pc.h"
#include "status.h"
#include "unit.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

struct merc_db merc_db[MAX_MERC_DB];

static int merc_data_init(struct map_session_data *sd);

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

	st.merc_id = 100;	// 本来IDはinter鯖から取得する

	sd->state.merc_creating = 1;
	//intif_create_merc(sd->status.account_id,sd->status.char_id,&st);
	merc_recv_mercdata(sd->status.account_id,sd->status.char_id, &st, 1);

	return 0;
}

//static int homun_natural_heal_hp(int tid,unsigned int tick,int id,int data);
//static int homun_natural_heal_sp(int tid,unsigned int tick,int id,int data);

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
	mcd->bl.x  = mcd->ud.to_x;
	mcd->bl.y  = mcd->ud.to_y;
	mcd->bl.id = npc_get_new_npc_id();
	mcd->dir   = sd->dir;
	mcd->speed = status_get_speed(&sd->bl);	// 歩行速度は、コール時の主人のspeedになる
	mcd->bl.subtype = MONS;
	mcd->bl.type    = BL_MERC;
	mcd->target_id  = 0;
	mcd->attackable = 1;	// これを0にすると、クライアントから攻撃パケットを出さなくなる
	mcd->msd        = sd;
	mcd->view_class = merc_db[class_].view_class;

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

	//merc_calc_status(mcd);			// ステータス計算
	// まだ未実装なので代わりにダミーデータを詰める
	mcd->atk      = 150;
	mcd->matk     = 30;
	mcd->hit      = 120;
	mcd->critical = 20;
	mcd->def      = 15;
	mcd->mdef     = 5;
	mcd->flee     = 42;
	mcd->aspd     = 170;

	unit_dataset(&mcd->bl);
	map_addiddb(&mcd->bl);

	//hd->natural_heal_hp    = add_timer(tick+NATURAL_HEAL_HP_INTERVAL,homun_natural_heal_hp,hd->bl.id,0);
	//hd->natural_heal_sp    = add_timer(tick+NATURAL_HEAL_SP_INTERVAL,homun_natural_heal_sp,hd->bl.id,0);

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
			//intif_delete_mercdata(account_id,char_id,p->merc_id);
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
			//mob_ai_hard_spawn( &sd->mcd->bl, 1 );
			clif_spawnmerc(sd->mcd);
			clif_send_mercdata(sd);
			clif_send_mercstatus(sd,1);
			clif_send_mercstatus(sd,0);
			clif_mercskillinfoblock(sd);
			//merc_save_data(sd);
			//skill_unit_move(&sd->mcd->bl,gettick(),1);
		}
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

	if(sd->status.homun_id > 0 && sd->mcd) {
		// 親密度保存
		//if(battle_config.save_homun_temporal_intimate)
		//	pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",2000);	// 初期値に
		unit_free(&sd->mcd->bl,0);
		//intif_delete_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);
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
			merc_delete_data(sd);
			break;
	}
	return 0;
}

/*==========================================
 * 傭兵のデータをセーブ
 *------------------------------------------
 */
int merc_save_data(struct map_session_data *sd)
{
/*
	struct homun_data *hd;

	nullpo_retr(0, sd);
	nullpo_retr(0, hd = sd->hd);

	if(battle_config.save_homun_temporal_intimate)
		pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
	memcpy(&sd->hom,&hd->status,sizeof(struct mmo_homunstatus));
	intif_save_homdata(sd->status.account_id,&sd->hd->status);
*/
	return 0;
}

/*==========================================
 * mcdにdamageのダメージ
 *------------------------------------------
 */
int merc_damage(struct block_list *src,struct merc_data *mcd,int damage)
{
/*
	struct map_session_data *sd = NULL;

	nullpo_retr(0, mcd);
	nullpo_retr(0, sd = mcd->msd);

	// 既に死んでいたら無効
	if(unit_isdead(&hd->bl))
		return 0;

	// 歩いていたら足を止める
	unit_stop_walking(&hd->bl,battle_config.pc_hit_stop_type);

	if(damage > 0)
		skill_stop_gravitation(&hd->bl);

	if(hd->bl.prev == NULL) {
		if(battle_config.error_log)
			printf("homun_damage : BlockError!!\n");
		return 0;
	}

	if(hd->status.hp > hd->max_hp)
		hd->status.hp = hd->max_hp;

	// over kill分は丸める
	if(damage > hd->status.hp)
		damage = hd->status.hp;

	hd->status.hp -= damage;

	// ハイド状態を解除
	status_change_hidden_end(&hd->bl);

	clif_send_homstatus(sd,0);

	// 死亡していた
	if(hd->status.hp <= 0) {
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
		// スキルユニットからの離脱
		hd->status.hp = 1;
		skill_unit_move(&hd->bl,gettick(),0);
		hd->status.hp = 0;

		hd->status.incubate = 0;
		unit_free(&hd->bl,1);
	}
*/
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
 * exp.txt 必要経験値
 * skill_tree.txt スキルツリー
 *------------------------------------------
 */
static int homun_readdb(void)
{
/*
	int i,j,k,class_=0;
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
		if(sscanf(line,"%d,%d,%d,%d,%d,%d",&b0,&b1,&b2,&b3,&b4,&b5) != 6)
			continue;
		homun_exp_table[0][i] = b0;
		homun_exp_table[1][i] = b1;
		homun_exp_table[2][i] = b2;
		homun_exp_table[3][i] = b3;
		homun_exp_table[4][i] = b4;
		homun_exp_table[5][i] = b5;
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
		int skillid;
		char *split[15];
		struct homun_skill_tree_entry *st;

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
		i = class_ - HOM_ID;
		if(i < 0 || i >= MAX_HOMUN_DB)
			continue;

		skillid = atoi(split[1]);
		st = homun_skill_tree[i];
		for(j=0; st[j].id && st[j].id != skillid; j++);

		if(j >= MAX_HOMSKILL_TREE - 1) {
			// 末尾はアンカーとして0にしておく必要がある
			printf("homun_readdb: skill (%d) is over max tree %d!!\n", skillid, MAX_HOMSKILL_TREE);
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
	printf("read db/homun_skill_tree.txt done\n");
*/
	return 0;
}

/*==========================================
 * 傭兵DBのリロード
 *------------------------------------------
 */
void merc_reload(void)
{
	read_mercdb();
	//homun_readdb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_merc(void)
{
	read_mercdb();
	//homun_readdb();

/*
	add_timer_func_list(homun_natural_heal_hp,"homun_natural_heal_hp");
	add_timer_func_list(homun_natural_heal_sp,"homun_natural_heal_sp");
*/
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
