#ifndef _ITEMDB_H_
#define _ITEMDB_H_

#include "map.h"

struct item_data {
	int nameid;
	char name[32];
	char jname[32];
	char cardillustname[64];
	int value_buy;
	int value_sell;
	int type;
	unsigned int class;
	int sex;
	int equip;
	int weight;
	int atk;
	int def;
	int range;
	int slot;
	int look;
	int elv;
	int wlv;
	int refine;
	struct script_code *use_script;	// 回復とかも全部この中でやろうかなと
	struct script_code *equip_script;	// 攻撃,防御の属性設定もこの中で可能かな?
	struct {
		unsigned available : 1;
		unsigned value_notdc : 1;
		unsigned value_notoc : 1;
		unsigned dropable : 1;
		unsigned storageable : 1;
		unsigned cartable : 1;
	} flag;
	int view_id;
	int group;
	int delay;
	int upper; 	//0:all(7に強制変換) 1:転生前 2:転生 4:養子
	int zone;	//0:制限無 1:normal 2:pvp 4:gvg 8:pk 16:turbo 32:noteleport 64:noreturn 128:nobranch
	int arrow_type;
};

struct random_item_data {
	int nameid;
	int per;
};

struct item_data* itemdb_searchname(const char *name);
struct item_data* itemdb_search(int nameid);
struct item_data* itemdb_exists(int nameid);
#define itemdb_type(n) itemdb_search(n)->type
#define itemdb_atk(n) itemdb_search(n)->atk
#define itemdb_def(n) itemdb_search(n)->def
#define itemdb_look(n) itemdb_search(n)->look
#define itemdb_weight(n) itemdb_search(n)->weight
#define itemdb_equip(n) itemdb_search(n)->equip
#define itemdb_usescript(n) itemdb_search(n)->use_script
#define itemdb_equipscript(n) itemdb_search(n)->equip_script
#define itemdb_wlv(n) itemdb_search(n)->wlv
#define itemdb_range(n) itemdb_search(n)->range
#define itemdb_slot(n) itemdb_search(n)->slot
#define	itemdb_available(n) (itemdb_exists(n) && itemdb_search(n)->flag.available)
#define	itemdb_viewid(n) (itemdb_search(n)->view_id)
#define	itemdb_group(n) (itemdb_search(n)->group)

int itemdb_searchrandomid(int flags);

#define itemdb_value_buy(n) itemdb_search(n)->value_buy
#define itemdb_value_sell(n) itemdb_search(n)->value_sell
#define itemdb_value_notdc(n) itemdb_search(n)->flag.value_notdc
#define itemdb_value_notoc(n) itemdb_search(n)->flag.value_notoc
int itemdb_isequip(int);
int itemdb_isequip2(struct item_data *);
int itemdb_isequip3(int);
int itemdb_iscartable(int nameid);
int itemdb_isstorageable(int nameid);
int itemdb_isdropable(int nameid);

// itemdb_equipマクロとitemdb_equippointとの違いは
// 前者が鯖側dbで定義された値そのものを返すのに対し
// 後者はsessiondataを考慮した鞍側での装備可能場所
// すべての組み合わせを返す

void itemdb_reload(void);
void do_final_itemdb(void);
int do_init_itemdb(void);

#endif
