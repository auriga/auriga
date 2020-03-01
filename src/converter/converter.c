/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "core.h"
#include "db.h"
#include "mmo.h"
#include "malloc.h"
#include "timer.h"
#include "version.h"
#include "sqldbs.h"

#include "converter.h"
#include "login-converter.h"
#include "char-converter.h"
#include "inter-converter.h"
#include "map-converter.h"

char converter_conf_filename[256] = "conf/converter_auriga.conf";

char db_server_ip[16] = "127.0.0.1";
unsigned short db_server_port = 3306;
char db_server_id[32] = "ragnarok";
char db_server_pw[32] = "ragnarok";
char db_server_logindb[32] = "ragnarok";
char db_server_charset[32] = "";
int  db_server_keepalive   = 0;

char login_db[1024]            = "login";
char login_db_account_id[1024] = "account_id";
char login_db_userid[1024]     = "userid";
char login_db_user_pass[1024]  = "user_pass";
char login_db_level[1024]      = "level";

char map_server_tag[16]        = "map01";

char account_filename[1024]    = "save/account.txt";
char char_txt[1024]            = "save/auriga.txt";
char GM_account_filename[1024] = "conf/GM_account.txt";
char pet_txt[1024]             = "save/pet.txt";
char storage_txt[1024]         = "save/storage.txt";
char party_txt[1024]           = "save/party.txt";
char guild_txt[1024]           = "save/guild.txt";
char guild_storage_txt[1024]   = "save/g_storage.txt";
char castle_txt[1024]          = "save/castle.txt";
char homun_txt[1024]           = "save/homun.txt";
char account_reg_txt[1024]     = "save/accreg.txt";
char scdata_txt[1024]          = "save/scdata.txt";
char mail_txt[1024]            = "save/mail.txt";
char mail_dir[1024]            = "save/mail_data/";
char mapreg_txt[1024]          = "save/mapreg.txt";


static int config_read(const char *cfgName)
{
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
		if(strcmpi(w1,"account_filename")==0){
			printf("set account_filename : %s\n",w2);
			strncpy(account_filename, w2, sizeof(account_filename));
		} else if(strcmpi(w1,"char_txt")==0){
			printf("set char_txt : %s\n",w2);
			strncpy(char_txt, w2, sizeof(char_txt));
		} else if(strcmpi(w1,"GM_account_filename")==0){
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
		} else if(strcmpi(w1,"castle_txt")==0){
			printf("set castle_txt : %s\n",w2);
			strncpy(castle_txt, w2, sizeof(castle_txt));
		} else if(strcmpi(w1,"homun_txt")==0){
			printf("set homun_txt : %s\n",w2);
			strncpy(homun_txt, w2, sizeof(homun_txt));
		} else if(strcmpi(w1,"account_reg_txt")==0){
			printf("set account_reg_txt : %s\n",w2);
			strncpy(account_reg_txt, w2, sizeof(account_reg_txt));
		} else if(strcmpi(w1,"scdata_txt")==0){
			printf("set scdata_txt : %s\n",w2);
			strncpy(scdata_txt, w2, sizeof(scdata_txt));
		} else if(strcmpi(w1,"mail_txt")==0){
			printf("set mail_txt : %s\n",w2);
			strncpy(mail_txt, w2, sizeof(mail_txt));
		} else if(strcmpi(w1,"mail_dir")==0){
			printf("set mail_dir : %s\n",w2);
			strncpy(mail_dir, w2, sizeof(mail_dir));
		} else if(strcmpi(w1,"mapreg_txt")==0){
			printf("set mapreg_txt : %s\n",w2);
			strncpy(mapreg_txt, w2, sizeof(mapreg_txt));
		}

		// add for DB connection
		else if(strcmpi(w1,"db_server_ip")==0){
			strncpy(db_server_ip, w2, sizeof(db_server_ip));
			printf("set db_server_ip : %s\n",w2);
		}
		else if(strcmpi(w1,"db_server_port")==0){
			db_server_port = (unsigned short)atoi(w2);
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
		else if(strcmpi(w1,"db_server_keepalive")==0){
			db_server_keepalive = atoi(w2);
			printf("set db_server_keepalive : %d\n",db_server_keepalive);
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
		}

		// Map Server Tag Name
		else if(strcmpi(w1,"map_server_tag")==0){
			strncpy(map_server_tag, w2, sizeof(map_server_tag));
			map_server_tag[sizeof(map_server_tag) - 1] = '\0';
			printf("set map_server_tag : %s\n",map_server_tag);
		}

		// support the import command, just like any other config
		else if(strcmpi(w1,"import")==0){
			config_read(w2);
		}

		// unknown option
		else {
			printf("Unknown option '%s' in file %s\n", w1, cfgName);
		}
	}
	fclose(fp);

	printf("Reading converter configuration: Done\n");

	return 0;
}

int do_init(int argc,char **argv)
{
	int i;
	bool rc;

	printf("Auriga Converter v%d.%d.%d version %04d\n",
		AURIGA_MAJOR_VERSION, AURIGA_MINOR_VERSION, AURIGA_REVISION,
		get_current_version()
	);

	for(i = 1; i < argc - 1; i += 2) {
		if(strcmp(argv[i], "--converter_config") == 0 || strcmp(argv[i], "--converter-config") == 0) {
			strncpy(converter_conf_filename, argv[i+1], sizeof(converter_conf_filename));
			converter_conf_filename[sizeof(converter_conf_filename)-1] = '\0';
		}
	}

	// read config
	config_read(converter_conf_filename);

	// DB connection initialized
	rc = sqldbs_connect(&mysql_handle,
		db_server_ip, db_server_id, db_server_pw, db_server_logindb, db_server_port, db_server_charset, db_server_keepalive, "CONVERTER"
	);
	if(rc == false) {
		printf("FATAL ERROR: sqldbs_connect() failed !!\n");
		exit(1);
	}

	printf("Warning : Make sure you backup your databases before continuing!\n");
	printf("Convert start...\n");

	login_convert();
	char_convert();
	inter_convert();
	map_convert();

	printf("\nEverything's been converted!\n");
	printf("Please Push Any Key...");
	getchar();

	exit(0);

	return 0;
}

void do_pre_final(void)
{
	// nothing to do
	return;
}

void do_final(void)
{
	sqldbs_close(&mysql_handle);

	exit_dbn();
	do_final_timer();
}
