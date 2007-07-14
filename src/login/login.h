#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "mmo.h"

#define MAX_SERVERS 30

#define LOGIN_CONF_NAME	"conf/login_auriga.conf"

#define PASSWORDENC		3	// 暗号化パスワードに対応させるとき定義する
							// passwordencryptのときは1、
							// passwordencrypt2のときは2にする。
							// 3にすると両方に対応

struct login_session_data {
	long account_id;
	long login_id1;
	long login_id2;
	long char_id;
	int  sex;
	int  passwdenc;
	int  md5keylen;
	char md5key[64];
	char userid[24],pass[24],lastlogin[24];
	char lastip[16];
};

struct mmo_char_server {
	char name[20];
	long ip;
	short port;
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

#endif /* _LOGIN_H_ */
