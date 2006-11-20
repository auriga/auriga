#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mmo.h"
#include "converter.h"
#include "login-converter.h"
#include "char-converter.h"
#include "inter-converter.h"
#include "../common/db.h"
#include "../common/timer.h"

MYSQL mysql_handle;

char db_server_ip[16] = "127.0.0.1";
int  db_server_port   = 3306;
char db_server_id[32] = "ragnarok";
char db_server_pw[32] = "ragnarok";
char db_server_logindb[32] = "ragnarok";
char db_server_charset[32] = "";

char login_db[1024]            = "login";
char login_db_account_id[1024] = "account_id";
char login_db_userid[1024]     = "userid";
char login_db_user_pass[1024]  = "user_pass";
char login_db_level[1024]      = "level";

char GM_account_filename[1024] = "conf/GM_account.txt";
char pet_txt[1024]             = "save/pet.txt";
char storage_txt[1024]         = "save/storage.txt";
char party_txt[1024]           = "save/party.txt";
char guild_txt[1024]           = "save/guild.txt";
char guild_storage_txt[1024]   = "save/g_storage.txt";
char homun_txt[1024]           = "save/homun.txt";
char account_reg_txt[1024]     = "save/accreg.txt";
char scdata_txt[1024]          = "save/scdata.txt";

char tmp_sql[65535];

#ifdef _MSC_VER
#pragma comment(lib,"libmysql.lib")
#endif

char* strecpy (char* pt,const char* spt) {
	//copy from here
	mysql_real_escape_string(&mysql_handle,pt,spt,strlen(spt));
	return pt;
}

int config_read(const char *cfgName) {
	int i;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	printf("Start reading converter configuration: %s\n",cfgName);

	fp=fopen(cfgName,"r");
	if(fp==NULL){
		printf("File not found: %s\n", cfgName);
		return 1;
	}
	while(fgets(line, sizeof(line)-1, fp)){
		i=sscanf(line,"%[^:]:%s", w1, w2);
		if(i!=2)
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;

		// TXT files
		if(strcmpi(w1,"GM_account_filename")==0){
			printf("set GM_account_filename : %s\n",w2);
			strncpy(GM_account_filename, w2, sizeof(GM_account_filename));
		} else if(strcmpi(w1,"pet_txt")==0){
			printf("set pet_txt : %s\n",w2);
			strncpy(pet_txt, w2, sizeof(pet_txt));
		} else if(strcmpi(w1,"storage_txt")==0){
			printf("set storage_txt : %s\n",w2);
			strncpy(storage_txt, w2, sizeof(storage_txt));
		} else if(strcmpi(w1,"party_txt")==0){
			printf("set party_txt : %s\n",w2);
			strncpy(party_txt, w2, sizeof(party_txt));
		} else if(strcmpi(w1,"guild_txt")==0){
			printf("set guild_txt : %s\n",w2);
			strncpy(guild_txt, w2, sizeof(guild_txt));
		} else if(strcmpi(w1,"guild_storage_txt")==0){
			printf("set guild_storage_txt : %s\n",w2);
			strncpy(guild_storage_txt, w2, sizeof(guild_storage_txt));
		} else if(strcmpi(w1,"homun_txt")==0){
			printf("set homun_txt : %s\n",w2);
			strncpy(homun_txt, w2, sizeof(homun_txt));
		} else if(strcmpi(w1,"account_reg_txt")==0){
			printf("set account_reg_txt : %s\n",w2);
			strncpy(account_reg_txt, w2, sizeof(account_reg_txt));
		} else if(strcmpi(w1,"scdata_txt")==0){
			printf("set scdata_txt : %s\n",w2);
			strncpy(scdata_txt, w2, sizeof(scdata_txt));
		}

		// add for DB connection
		else if(strcmpi(w1,"db_server_ip")==0){
			strncpy(db_server_ip, w2, sizeof(db_server_ip));
			printf("set db_server_ip : %s\n",w2);
		}
		else if(strcmpi(w1,"db_server_port")==0){
			db_server_port = atoi(w2);
			printf("set db_server_port : %d\n",db_server_port);
		}
		else if(strcmpi(w1,"db_server_id")==0){
			strncpy(db_server_id, w2, sizeof(db_server_id));
			printf("set db_server_id : %s\n",w2);
		}
		else if(strcmpi(w1,"db_server_pw")==0){
			strncpy(db_server_pw, w2, sizeof(db_server_pw));
			printf("set db_server_pw : %s\n",w2);
		}
		else if(strcmpi(w1,"db_server_logindb")==0){
			strncpy(db_server_logindb, w2, sizeof(db_server_logindb));
			printf("set db_server_logindb : %s\n",w2);
		}
		else if(strcmpi(w1,"db_server_charset")==0){
			strncpy(db_server_charset, w2, sizeof(db_server_charset));
			printf("set db_server_charset : %s\n",w2);
		}

		// login SQL DB configuration
		else if(strcmpi(w1,"login_db")==0){
			strncpy(login_db, w2, sizeof(login_db));
			printf("set login_db : %s\n",w2);
		} else if(strcmpi(w1,"login_db_account_id")==0){
			strncpy(login_db_account_id, w2, sizeof(login_db_account_id));
			printf("set login_db_account_id : %s\n",w2);
		} else if(strcmpi(w1,"login_db_userid")==0){
			strncpy(login_db_userid, w2, sizeof(login_db_userid));
			printf("set login_db_userid : %s\n",w2);
		} else if(strcmpi(w1,"login_db_user_pass")==0){
			strncpy(login_db_user_pass, w2, sizeof(login_db_user_pass));
			printf("set login_db_user_pass : %s\n",w2);
		} else if(strcmpi(w1,"login_db_level")==0){
			strncpy(login_db_level, w2, sizeof(login_db_level));
			printf("set login_db_level : %s\n",w2);

		// support the import command, just like any other config
		} else if(strcmpi(w1,"import")==0){
			config_read(w2);

		// unknown option
		} else {
			printf("Unknown option '%s' in file %s\n", w1, cfgName);
		}
	}
	fclose(fp);

	printf("Reading converter configuration: Done\n");

	return 0;
}

int do_init(int argc,char **argv) {
	// read config
	config_read("conf/converter_athena.conf");

	// DB connection initialized
	mysql_init(&mysql_handle);
	printf("Connect DB server");
	if(db_server_charset[0]) {
		printf(" (charset: %s)",db_server_charset);
	}
	printf("...\n");
	if(!mysql_real_connect(&mysql_handle, db_server_ip, db_server_id, db_server_pw,
		db_server_logindb ,db_server_port, (char *)NULL, 0)) {
		//pointer check
		printf("%s\n",mysql_error(&mysql_handle));
		exit(1);
	}
	else {
		printf ("connect success! (inter server)\n");
	}
	if(db_server_charset[0]) {
		sprintf(tmp_sql,"SET NAMES %s",db_server_charset);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (charset)- %s\n", mysql_error(&mysql_handle));
		}
	}

	printf("Warning : Make sure you backup your databases before continuing!\n");
	printf("Convert start...\n");

	login_convert();
	char_convert();
	inter_convert();

	printf ("\nEverything's been converted!\n");
	printf ("Please Push Any Key...");
	getchar();

	exit(0);

	return 0;
}

void do_final(void)
{
	exit_dbn();
	do_final_timer();
}