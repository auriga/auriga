#ifndef _PET_H_
#define _PET_H_

#define MAX_PET_DB	100

struct pet_db {
	short class;
	char name[24],jname[24];
	short itemID;
	short EggID;
	short AcceID;
	short FoodID;
	int fullness;
	int hungry_delay;
	int r_hungry;
	int r_full;
	short intimate;
	int die;
	int capture;
	int speed;
	char s_perfor;
	int talk_convert_class;
	int attack_rate;
	int defence_attack_rate;
	int change_target_rate;
	struct script_code *script;
};
extern struct pet_db pet_db[MAX_PET_DB];

enum { PET_CLASS,PET_CATCH,PET_EGG,PET_EQUIP,PET_FOOD };

int pet_hungry_val(struct map_session_data *sd);
int pet_target_check(struct map_session_data *sd,struct block_list *bl,int type);
int search_petDB_index(int key,int type);
int pet_hungry_timer_delete(struct map_session_data *sd);
int pet_data_init(struct map_session_data *sd);
int pet_birth_process(struct map_session_data *sd);
int pet_recv_petdata(int account_id,struct s_pet *p,int flag);
int pet_select_egg(struct map_session_data *sd,short egg_index);
int pet_catch_process1(struct map_session_data *sd,int target_class);
int pet_catch_process2(struct map_session_data *sd,int target_id);
int pet_get_egg(int account_id,int pet_id,int flag);
int pet_menu(struct map_session_data *sd,int menunum);
int pet_change_name(struct map_session_data *sd,char *name);
void pet_equipitem(struct map_session_data *sd, int idx);
int pet_unequipitem(struct map_session_data *sd);
int pet_food(struct map_session_data *sd);
int pet_lootitem_drop(struct pet_data *pd,struct map_session_data *sd);
int pet_delay_item_drop2(int tid,unsigned int tick,int id,int data);
int pet_skill_support_timer(int tid,unsigned int tick,int id,int data);
int do_init_pet(void);
int do_final_pet(void);

int read_petdb(void);

#endif

