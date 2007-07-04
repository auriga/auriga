#ifndef _PC_H_
#define _PC_H_

#include "utils.h"
#include "map.h"

#define OPTION_MASK 0xd7b8
#define CART_MASK 0x788

#define MAX_SKILL_TREE 100

#define pc_setdead(sd) ((sd)->state.dead_sit = 1)
#define pc_setsit(sd) ((sd)->state.dead_sit = 2)
#define pc_issit(sd) ((sd)->state.dead_sit == 2)
#define pc_setdir(sd,b,h) ((sd)->dir = (char)(b) ,(sd)->head_dir = (char)(h) )

#define pc_ishiding(sd) ((sd)->status.option&0x4006)
#define pc_iscloaking(sd)   (!((sd)->status.option&0x4000) && ((sd)->status.option&0x0004))
#define pc_ischasewalk(sd)  (((sd)->status.option&0x4000) && ((sd)->status.option&0x0004))

#define pc_iscarton(sd) ((sd)->status.option&CART_MASK)
#define pc_isfalcon(sd) ((sd)->status.option&0x0010)
#define pc_isriding(sd) ((sd)->status.option&0x0020)
#define pc_isinvisible(sd) ((sd)->status.option&0x0040)
#define pc_is50overweight(sd) ((sd)->weight*2 >= (sd)->max_weight)
#define pc_is90overweight(sd) ((sd)->weight*10 >= (sd)->max_weight*9)

extern int attr_fix_table[MAX_ELE_LEVEL][ELE_MAX][ELE_MAX];
extern int max_job_table[3][32];

int pc_get_skilltree_max(struct pc_base_job *bj,int id);

void pc_set_gm_account_fname(char *str);
int pc_isGM(struct map_session_data *sd);
int pc_numisGM(int account_id);
int pc_get_gm_account_dummy(void);
int pc_isquitable(struct map_session_data *sd);

int pc_setrestartvalue(struct map_session_data *sd,int type);
int pc_makesavestatus(struct map_session_data *);
void pc_setnewpc(struct map_session_data*,int,int,int,int,int);
int pc_authok(int,struct mmo_charstatus *st,struct registry *reg);
int pc_authfail(int);

int pc_equippoint(struct map_session_data *sd,int n);

int pc_checkskill(struct map_session_data *sd,int skill_id);
int pc_checkskill2(struct map_session_data *sd,int skill_id);
int pc_checkequip(struct map_session_data *sd,int pos);

int pc_checkoverhp(struct map_session_data*);
int pc_checkoversp(struct map_session_data*);

int pc_setpos(struct map_session_data*,char*,int,int,int);
int pc_setsavepoint(struct map_session_data*,char*,int,int);
int pc_randomwarp(struct map_session_data *sd,int type);
void pc_memo(struct map_session_data *sd, int i);

int pc_checkadditem(struct map_session_data*,int,int);
int pc_inventoryblank(struct map_session_data*);
int pc_search_inventory(struct map_session_data *sd,int item_id);
int pc_payzeny(struct map_session_data*,int);
int pc_additem(struct map_session_data*,struct item*,int);
int pc_getzeny(struct map_session_data*,int);
int pc_lossequipitem(struct map_session_data *sd,int pos,int type);
void pc_delitem(struct map_session_data*, int n, int amount, int type);
int pc_checkitem(struct map_session_data*);

int pc_cart_additem(struct map_session_data *sd,struct item *item_data,int amount);
int pc_cart_delitem(struct map_session_data *sd,int n,int amount,int type);
void pc_putitemtocart(struct map_session_data *sd, int idx, int amount);
void pc_getitemfromcart(struct map_session_data *sd, int idx, int amount);
int pc_cartitem_amount(struct map_session_data *sd,int idx,int amount);

void pc_takeitem(struct map_session_data*, struct flooritem_data*);
void pc_takeitem_sub(struct party *p, struct map_session_data *sd, struct flooritem_data *fitem);
int pc_dropitem(struct map_session_data*, int, int);

int pc_checkweighticon(struct map_session_data *sd);

int pc_bonus(struct map_session_data*,int,int);
int pc_bonus2(struct map_session_data *sd,int,int,int);
int pc_bonus3(struct map_session_data *sd,int,int,int,int);
int pc_bonus4(struct map_session_data *sd,int,int,int,int,unsigned long);
int pc_skill(struct map_session_data*,int,int,int);

void pc_insert_card(struct map_session_data *sd, int idx_card, int idx_equip);

void pc_item_identify(struct map_session_data *sd, int idx);
int pc_steal_item(struct map_session_data *sd,struct mob_data *md);
int pc_steal_coin(struct map_session_data *sd,struct mob_data *md);

int pc_modifybuyvalue(struct map_session_data*,int);
int pc_modifysellvalue(struct map_session_data*,int);

int pc_gainexp(struct map_session_data*,struct mob_data*,atn_bignumber,atn_bignumber);
int pc_nextbaseexp(struct map_session_data *);
int pc_nextjobexp(struct map_session_data *);
int pc_need_status_point(struct map_session_data *,int);
void pc_statusup(struct map_session_data *sd, unsigned short type);
int pc_statusup2(struct map_session_data*,int,int);
void pc_skillup(struct map_session_data *sd, int skill_num);
int pc_allskillup(struct map_session_data* sd,int flag);
void pc_resetstate(struct map_session_data* sd);
void pc_resetskill(struct map_session_data* sd);
void pc_equipitem(struct map_session_data*, int n, int pos);
void pc_unequipitem(struct map_session_data*, int n, int type);
int pc_equippeditem(struct map_session_data *sd,int id);
void pc_useitem(struct map_session_data*, int n);

int pc_damage(struct block_list *,struct map_session_data*,int);
int pc_heal(struct map_session_data *,int,int);
int pc_itemheal(struct map_session_data *sd,int hp,int sp);
int pc_percentheal(struct map_session_data *sd,int,int);
int pc_jobchange(struct map_session_data *,int, int);
void pc_setoption(struct map_session_data *sd, unsigned int type);
void pc_setcart(struct map_session_data *sd, unsigned short type);
int pc_setfalcon(struct map_session_data *sd);
int pc_setriding(struct map_session_data *sd);
int pc_changelook(struct map_session_data *,int,int);

int pc_readparam(struct map_session_data*,int);
int pc_setparam(struct map_session_data*,int,int);
int pc_readreg(struct map_session_data*,int);
int pc_setreg(struct map_session_data*,int,int);
char *pc_readregstr(struct map_session_data *sd,int reg);
int pc_setregstr(struct map_session_data *sd,int reg,char *str);
int pc_readglobalreg(struct map_session_data*,const char*);
int pc_setglobalreg(struct map_session_data*,const char*,int);
int pc_readaccountreg(struct map_session_data*,const char*);
int pc_setaccountreg(struct map_session_data*,const char*,int);
int pc_readaccountreg2(struct map_session_data*,const char*);
int pc_setaccountreg2(struct map_session_data*,const char*,int);

int pc_addeventtimer(struct map_session_data *sd,int tick,const char *name);
int pc_deleventtimer(struct map_session_data *sd,const char *name);
int pc_cleareventtimer(struct map_session_data *sd);
int pc_addeventtimercount(struct map_session_data *sd,const char *name,int tick);
int pc_geteventtimerdiff(struct map_session_data *sd,const char *name);

int pc_calc_pvprank(struct map_session_data *sd);
int pc_calc_pvprank_timer(int tid,unsigned int tick,int id,int data);

int pc_homisalive(struct map_session_data *sd);

int pc_ismarried(struct map_session_data *sd);
int pc_marriage(struct map_session_data *sd,struct map_session_data *dstsd);
int pc_divorce(struct map_session_data *sd);
struct map_session_data *pc_get_partner(struct map_session_data *sd);

int pc_adoption(struct map_session_data* sd,struct map_session_data *parent);
int pc_adoption_sub(struct map_session_data* sd,struct map_session_data *papa,struct map_session_data *mama);
int pc_check_adopt_condition(struct map_session_data *dstsd, struct map_session_data *sd, struct map_session_data *psd, short flag);
void pc_adopt_reply(struct map_session_data *sd,int src_id,int p_id,short flag);
int pc_break_adoption(struct map_session_data *sd);

int pc_break_equip(struct map_session_data *sd, unsigned short where);
int pc_break_equip2(struct map_session_data *sd, int where);

int pc_candrop(struct map_session_data *sd,int item_id);

void pc_setstand(struct map_session_data *sd);
int pc_calc_skilltree(struct map_session_data *sd);
int pc_check_guild_skill_effective_range(struct map_session_data *sd);

#define pc_isupper(sd) (((sd)->status.class_ >= PC_CLASS_NV2) && ((sd)->status.class_ < PC_CLASS_NV3))
#define pc_isbaby(sd) (((sd)->status.class_ >= PC_CLASS_NV3) && ((sd)->status.class_ <= PC_CLASS_SNV3))

struct pc_base_job pc_calc_base_job(int b_class);
int pc_calc_class_job(int job,int upper);

void pc_read_gm_account(void);
int pc_setinvincibletimer(struct map_session_data *sd,int);
int pc_delinvincibletimer(struct map_session_data *sd);
int pc_addspiritball(struct map_session_data *sd,int,int);
int pc_delspiritball(struct map_session_data *sd,int,int);
int pc_addcoin(struct map_session_data *sd,int,int);
int pc_delcoin(struct map_session_data *sd,int,int);

int pc_runtodir(struct map_session_data *sd);

// DB再読込用
int pc_readdb(void);

int do_final_pc(void);
int do_init_pc(void);

enum {ADDITEM_EXIST,ADDITEM_NEW,ADDITEM_OVERAMOUNT};

#endif
