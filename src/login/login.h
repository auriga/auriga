#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "mmo.h"

#define MAX_CHAR_SERVERS 5

#define PASSWORDENC		3	// 暗号化パスワードに対応させるとき定義する
							// passwordencryptのときは1、
							// passwordencrypt2のときは2にする。
							// 3にすると両方に対応

struct login_session_data {
	int account_id;
	int login_id1;
	int login_id2;
	int char_id;
	int sex;
	int passwdenc;
	int md5keylen;
	char md5key[64];
	char userid[24],pass[24],lastlogin[24];
	char lastip[16];
};

struct mmo_char_server {
	char name[20];
	unsigned long ip;
	unsigned short port;
	int users;
	int maintenance;
	int new_;
};

struct mmo_account {
	int account_id,sex;
	char userid[24],pass[24],lastlogin[24],mail[40];
	int logincount;
	int state;
	int account_reg2_num;
	struct global_reg account_reg2[ACCOUNT_REG2_NUM];
	char lastip[16];
};

extern char login_conf_filename[];

#endif /* _LOGIN_H_ */
