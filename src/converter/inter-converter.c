#include <stdio.h>
#include <stdlib.h>

#include "../common/mmo.h"
#include "../common/utils.h"
#include "converter.h"


struct accreg {
	int account_id;
	int reg_num;
	struct global_reg reg[ACCOUNT_REG_NUM];
};

struct status_change_data {
	int account_id;
	int char_id;
	short count;
	struct {
		short type;
		int val1,val2,val3,val4,tick;
	} data[MAX_STATUSCHANGE];
};

// アカウント変数を文字列から変換
static int int_accreg_fromstr(const char *str,struct accreg *reg)
{
	int j,n,val;
	char buf[128];
	const char *p = str;

	if(sscanf(p,"%d\t%n", &reg->account_id, &n) != 1 || reg->account_id <= 0)
		return 1;

	for(j=0, p+=n; j<ACCOUNT_REG_NUM; j++, p+=n) {
		if(sscanf(p, "%[^,],%d%n", buf, &val, &n) != 2)
			break;
		strncpy(reg->reg[j].str, buf, 32);
		reg->reg[j].value = val;
		n++;
	}
	reg->reg_num = j;

	return 0;
}

// アカウント変数を書き込み
static void int_accreg_tosql(struct accreg *reg) {
	int j;
	char buf[128];

	//`global_reg_value` (`type`, `account_id`, `char_id`, `str`, `value`)
	sprintf(tmp_sql, "DELETE FROM `global_reg_value` WHERE `type`=2 AND `account_id`='%d'", reg->account_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `global_reg_value`)- %s\n", mysql_error(&mysql_handle) );
	}

	for(j=0; j<reg->reg_num; j++) {
		if(reg->reg[j].str[0]) {
			sprintf(tmp_sql, "INSERT INTO `global_reg_value` (`type`, `account_id`, `str`, `value`) VALUES (2,'%d', '%s','%d')",
				reg->account_id, strecpy(buf,reg->reg[j].str), reg->reg[j].value);
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `global_reg_value`)- %s\n", mysql_error(&mysql_handle) );
			}
		}
	}

	return;
}

// ステータス異常データを文字列から変換
static int int_status_fromstr(char *str, struct status_change_data *sc)
{
	int i,next,set,len;
	int tmp_int[6];

	if(sscanf(str,"%d,%d%n",&sc->char_id,&sc->account_id,&next) != 2)
		return 1;

	if(sc->account_id <= 0 || sc->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i=0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str+next,"%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&len);
		if(set != 6)
			return 1;
		if(i < MAX_STATUSCHANGE && tmp_int[0] >= 0 && tmp_int[0] < MAX_STATUSCHANGE) {
			sc->data[i].type = (short)tmp_int[0];
			sc->data[i].val1 = tmp_int[1];
			sc->data[i].val2 = tmp_int[2];
			sc->data[i].val3 = tmp_int[3];
			sc->data[i].val4 = tmp_int[4];
			sc->data[i].tick = tmp_int[5];
		}
		next+=len;
		if(str[next] == ' ')
			next++;
	}
	sc->count = (i < MAX_STATUSCHANGE)? i: MAX_STATUSCHANGE;

	return 0;
}

// ステータス異常データを書き込み
static void int_status_tosql(struct status_change_data *sc)
{
	int i;

	sprintf(tmp_sql,"DELETE FROM `status_change` WHERE `char_id`='%d'",sc->char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `status_change`)- %s\n", mysql_error(&mysql_handle));
	}

	for(i=0; i<sc->count; i++) {
		sprintf(
			tmp_sql,
			"INSERT INTO `status_change` (`char_id`, `account_id`, `type`, `val1`, `val2`, `val3`, `val4`, `tick`) "
			"VALUES ('%d','%d','%d','%d','%d','%d','%d','%d')",
			sc->char_id, sc->account_id, sc->data[i].type,
			sc->data[i].val1, sc->data[i].val2, sc->data[i].val3, sc->data[i].val4, sc->data[i].tick
		);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (insert `status_change`)- %s\n", mysql_error(&mysql_handle));
		}
	}

	return;
}

int inter_convert(void)
{
	char input, line[65536];
	int c = 0;
	FILE *fp;

	printf("\nDo you wish to convert your Account Registered Variables to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct accreg reg;
		printf("\nConverting Account Registered Variables...\n");
		if( (fp = fopen(account_reg_txt,"r")) == NULL )
			return 0;
		while(fgets(line, sizeof(line), fp)) {
			c++;
			memset(&reg, 0, sizeof(reg));
			if(int_accreg_fromstr(line, &reg) == 0 && reg.account_id > 0) {
				int_accreg_tosql(&reg);
			} else {
				printf("int_accreg: broken data [%s] line %d\n", account_reg_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	printf("\nDo you wish to convert your Status Change Data to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct status_change_data sc;
		printf("\nConverting Status Change Data...\n");
		if( (fp = fopen(scdata_txt,"r")) == NULL )
			return 0;
		while(fgets(line, sizeof(line), fp)) {
			c++;
			memset(&sc, 0, sizeof(sc));
			if(int_status_fromstr(line, &sc) == 0) {
				int_status_tosql(&sc);
			} else {
				printf("int_status: broken data [%s] line %d\n", scdata_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	return 0;
}
