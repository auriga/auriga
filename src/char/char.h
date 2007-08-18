#ifndef _CHAR_H_
#define _CHAR_H_

#include "mmo.h"

#define MAX_MAP_SERVERS 30

#define DEFAULT_AUTOSAVE_INTERVAL_CS 300*1000

struct mmo_map_server {
	unsigned long ip;
	unsigned short port;
	int users;
	char *map;
	short map_num;
	short active;
};

struct mmo_chardata {
	struct mmo_charstatus st;
	struct registry reg;
};

struct char_session_data {
	int state;
	int account_id,login_id1,login_id2,sex;
	const struct mmo_chardata *found_char[9];
};

struct cram_session_data {
	int md5keylen;
	char md5key[128];
};

int mapif_sendall(unsigned char *buf,unsigned int len);
int mapif_sendallwos(int fd,unsigned char *buf,unsigned int len);
int mapif_send(int fd,unsigned char *buf,unsigned int len);
void mapif_parse_CharConnectLimit(int fd);

extern int autosave_interval;

struct char_online {
	int account_id;
	int char_id;
	unsigned long ip;
	unsigned short port;
	char name[24];
};

extern char char_conf_filename[];
extern char inter_conf_filename[];


#ifdef TXT_ONLY

const struct mmo_chardata* char_txt_load(int char_id);
const struct mmo_chardata* char_txt_nick2chardata(const char *char_name);

#ifndef _CHAR_C_
#define char_load char_txt_load
#define char_nick2chardata char_txt_nick2chardata
#endif /* _CHAR_C_ */

#else

const struct mmo_chardata* char_sql_load(int char_id);
const struct mmo_chardata* char_sql_nick2chardata(const char *char_name);

#ifndef _CHAR_C_
#define char_load char_sql_load
#define char_nick2chardata char_sql_nick2chardata
#endif /* _CHAR_C_ */

// for sql
enum {
	TABLE_INVENTORY,
	TABLE_CART,
	TABLE_STORAGE,
	TABLE_GUILD_STORAGE,
};
int char_sql_saveitem(struct item *item, int max, int id, int tableswitch);
int char_sql_loaditem(struct item *item, int max, int id, int tableswitch);

extern char char_db[256];
extern char reg_db[256];

#endif /* TXT_ONLY */

#endif /* _CHAR_H_ */
