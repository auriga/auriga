#ifndef _HOMUN_H_
#define _HOMUN_H_

#include "map.h"
#include "mob.h"

#define NATURAL_HEAL_HP_INTERVAL 2*1000
#define NATURAL_HEAL_SP_INTERVAL 4*1000

#define MAX_HOMSKILL_TREE 16

struct homun_db {
	short class;
	char name[24],jname[24];
	int base_level;
	int hp,sp,hp_kmax,hp_kmin,sp_kmax,sp_kmin;
	int str,agi,vit,int_,dex,luk;
	int base;
	int str_k,agi_k,vit_k,int_k,dex_k,luk_k;
	short AcceID;
	short FoodID;
	short aspd_k;
	int maxskill;
	int view_class,size,race,element,evo_class;
	int exp_table;
	int skillpoint;
	struct script_code *script;
};
extern struct homun_db homun_db[MAX_HOMUN_DB];

struct random_homun_data {
	int homunid;
	int per;
};
int homun_data_init(struct map_session_data *sd);
int homun_hungry_timer_delete(struct map_session_data *sd);

int homun_menu(struct map_session_data *sd,int menunum);
int homun_change_name(struct map_session_data *sd,char *name);
int homun_return_master(struct map_session_data *sd);

int homun_callhom(struct map_session_data *sd);
int homun_recv_homdata(int account_id,struct mmo_homunstatus *p,int flag);
int homun_return_embryo(struct map_session_data *sd);
int homun_revive(struct map_session_data *sd,int skilllv);
int homun_change_class( struct map_session_data *sd, int class );

int homun_checkskill(struct homun_data *hd,int skill_id);
void homun_skillup(struct map_session_data *sd, int skill_num);
int homun_calc_skilltree(struct homun_data *hd);
int homun_checkbaselevelup(struct homun_data *hd);
int homun_gainexp(struct homun_data *hd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp);
int homun_nextbaseexp(struct homun_data *hd);
int homun_calc_status(struct homun_data *hd);
int homun_upstatus2(struct mmo_homunstatus *hd);

int homun_damage(struct block_list *src,struct homun_data *hd,int damage);

int homun_heal(struct homun_data *hd,int hp,int sp);
int homun_natural_heal_timer_delete(struct homun_data *hd);
int homun_get_create_homunid(void);
int homun_create_hom(struct map_session_data *sd,int homunid);
int homun_recalc_status(struct homun_data *hd);
int homun_delete_data(struct map_session_data *sd);

int homun_save_data(struct map_session_data *sd);

int do_init_homun(void);
int do_final_homun(void);

int read_homundb(void);
void homun_reload(void);

#endif
