#ifndef _MERC_H_
#define _MERC_H_

#include "map.h"

#define MAX_MERCSKILL_TREE 5

struct merc_db {
	short class_;
	unsigned short base_level;
	char name[24],jname[24];
	int hp,sp,hp_kmax,hp_kmin,sp_kmax,sp_kmin;
	int str,agi,vit,int_,dex,luk;
	int base;
	int str_k,agi_k,vit_k,int_k,dex_k,luk_k;
	short aspd_k;
	short view_class,size,race;
	int element;
	int range;
	unsigned int limit;
	struct script_code *script;
};
extern struct merc_db merc_db[MAX_MERC_DB];

int merc_get_skilltree_max(int class_,int skillid);

int merc_callmerc(struct map_session_data *sd, int class_);
int merc_recv_mercdata(int account_id,int char_id,struct mmo_mercstatus *p,int flag);
int merc_delete_data(struct map_session_data *sd);
int merc_menu(struct map_session_data *sd, int menunum);
int merc_return_master(struct map_session_data *sd);
int merc_save_data(struct map_session_data *sd);

int merc_calc_status(struct merc_data *mcd);
int merc_checkskill(struct merc_data *mcd,int skill_id);
int merc_calc_skilltree(struct merc_data *mcd);

int merc_damage(struct block_list *src,struct merc_data *mcd,int damage);
int merc_heal(struct merc_data *mcd,int hp,int sp);

int do_init_merc(void);
int do_final_merc(void);

#endif
