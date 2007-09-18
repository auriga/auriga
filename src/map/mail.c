#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "nullpo.h"
#include "malloc.h"

#include "map.h"
#include "mail.h"
#include "clif.h"
#include "intif.h"
#include "itemdb.h"
#include "pc.h"

/*==========================================
 * アイテムやZenyを添付
 *------------------------------------------
 */
void mail_setitem(struct map_session_data *sd,int idx,int amount)
{
	nullpo_retv(sd);

	idx -= 2;
	if(idx == -2) {
		if(sd->status.zeny < amount)
			amount = sd->status.zeny;
		sd->mail_zeny = amount;
	} else {
		if(idx < 0 || idx >= MAX_INVENTORY)
			return;

		if(sd->mail_item.nameid > 0 && sd->mail_item.amount > amount) {
			sd->mail_item.amount -= amount;
		} else if(sd->status.inventory[idx].amount >= amount && itemdb_isdropable(sd->status.inventory[idx].nameid)) {
			memcpy(&sd->mail_item,&sd->status.inventory[idx],sizeof(struct item));
			sd->mail_amount = amount;
		} else {
			// 添付不可
			clif_res_sendmail_setappend(sd->fd,idx,1);
			return;
		}
	}

	// 添付成功
	clif_res_sendmail_setappend(sd->fd,idx,0);

	return;
}

/*==========================================
 * 添付アイテムを初期化
 *------------------------------------------
 */
int mail_removeitem(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	memset(&sd->mail_item,0,sizeof(struct item));
	sd->mail_amount = 0;
	sd->mail_zeny   = 0;

	return 0;
}

/*==========================================
 * 添付アイテムやZenyをチェックして減らす
 *------------------------------------------
 */
static int mail_checkappend(struct map_session_data *sd,struct mail_data *md)
{
	nullpo_retr(1, sd);
	nullpo_retr(1, md);

	if(sd->mail_zeny < 0 || sd->mail_zeny > sd->status.zeny)
		return 0;

	md->zeny = sd->mail_zeny;

	if(sd->mail_item.nameid > 0 && sd->mail_amount > 0) {
		int i,idx = -1;
		for(i=0; i<MAX_INVENTORY; i++) {
			if(memcmp(&sd->mail_item,&sd->status.inventory[i],sizeof(struct item)) == 0) {
				idx = i;
				break;
			}
		}
		if(idx < 0 || sd->status.inventory[idx].amount < sd->mail_amount)
			return 1;

		memcpy(&md->item,&sd->mail_item,sizeof(struct item));
		md->item.amount = sd->mail_amount;
		pc_delitem(sd,idx,md->item.amount,0);
	}
	sd->status.zeny -= md->zeny;
	clif_updatestatus(sd,SP_ZENY);

	return 0;
}

/*==========================================
 * 送信前チェック
 *------------------------------------------
 */
int mail_checkmail(struct map_session_data *sd,char *name,char *title,char *body,int len)
{
	struct map_session_data *rd;
	struct mail_data md;

	nullpo_retr(0, sd);

	// 短すぎまたは長すぎ、おかしい
	if(len <= 0 || len > sizeof(md.body)) {
		clif_res_sendmail(sd->fd,2);	// メッセージが出ないパケットを送る必要がある
		mail_removeitem(sd);
		return 0;
	}

	rd = map_nick2sd(name);
	if(rd == sd) {		// 自分はダメ
		clif_res_sendmail(sd->fd,1);
		mail_removeitem(sd);
		return 0;
	}

	memset(&md, 0, sizeof(md));

	strncpy(md.char_name, sd->status.name, 24);
	md.char_id = sd->status.char_id;

	memcpy(md.receive_name, name, 24);
	md.receive_name[23] = '\0';	// force \0 terminal
	strncpy(md.title, title, sizeof(md.title));
	md.title[sizeof(md.title)-1] = '\0';

	memcpy(md.body, body, len);
	md.body_size = len;

	if(rd)
		mail_sendmail(sd,&md);
	else
		intif_mail_checkmail(sd->status.account_id,&md);	// 受け取る人がいるかInterサーバに確認要求

	return 0;
}

/*==========================================
 * 送信→Interへ
 *------------------------------------------
 */
int mail_sendmail(struct map_session_data *sd,struct mail_data *md)
{
	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	// 日付の保存
	md->times = (unsigned int)time(NULL);
	// アイテム・Zenyチェック
	if(mail_checkappend(sd,md) == 0)
		intif_sendmail(md);

	mail_removeitem(sd);
	return 0;
}

/*==========================================
 * 添付アイテムやZenyを取得
 *------------------------------------------
 */
int mail_getappend(int account_id,int zeny,struct item *item)
{
	struct map_session_data *sd;

	nullpo_retr(0, item);

	sd = map_id2sd(account_id);
	if(sd) {
		if(zeny > 0) {
			sd->status.zeny += zeny;
			clif_updatestatus(sd,SP_ZENY);
		}
		if(item->nameid > 0 && item->amount > 0) {
			if(pc_additem(sd,item,item->amount))
				clif_mail_getappend(sd->fd,2);
			else
				clif_mail_getappend(sd->fd,0);
		}
	}
	return 0;
}
