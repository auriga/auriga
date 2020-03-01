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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

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
void mail_setitem(struct map_session_data *sd, int idx, int amount)
{
	nullpo_retv(sd);

	idx -= 2;
	if(idx == -2) {
		if(sd->status.zeny < amount)
			amount = sd->status.zeny;
		sd->mail_append.zeny = amount;
	} else {
		if(idx < 0 || idx >= MAX_INVENTORY)
			return;

		if( sd->status.inventory[idx].nameid > 0 &&
		    sd->status.inventory[idx].amount >= amount &&
		    itemdb_isdropable(sd->status.inventory[idx].nameid) ) {
			sd->mail_append.amount = amount;
			sd->mail_append.index  = idx;
		} else {
			// 添付不可
			clif_res_sendmail_setappend(sd->fd,idx,1);
			return;
		}
	}

	// 添付成功
	sd->state.mail_appending = 1;
	clif_res_sendmail_setappend(sd->fd,idx,0);

	return;
}

/*==========================================
 * 添付アイテムを初期化
 *------------------------------------------
 */
int mail_removeitem(struct map_session_data *sd, int flag)
{
	nullpo_retr(0, sd);

	if(!(flag&2) && sd->mail_append.index >= 0) {
		clif_additem(sd, sd->mail_append.index, sd->mail_append.amount, 0);	// アイテム返却
		sd->mail_append.index  = -1;
		sd->mail_append.amount = 0;
	}
	if(!(flag&1) && sd->mail_append.zeny > 0) {
		clif_updatestatus(sd, SP_ZENY);		// Zeny返却
		sd->mail_append.zeny = 0;
	}

	if(sd->mail_append.index == -1 && sd->mail_append.zeny == 0)
		sd->state.mail_appending = 0;

	return 0;
}

/*==========================================
 * 添付アイテムやZenyをチェックして減らす
 *------------------------------------------
 */
static int mail_checkappend(struct map_session_data *sd, struct mail_data *md)
{
	nullpo_retr(1, sd);
	nullpo_retr(1, md);

	if(sd->mail_append.zeny < 0 || sd->mail_append.zeny > sd->status.zeny)
		return 1;

	md->zeny = sd->mail_append.zeny;

	if(sd->mail_append.amount > 0) {
		int idx = sd->mail_append.index;
		if( idx < 0 ||
		    sd->status.inventory[idx].nameid <= 0 ||
		    sd->status.inventory[idx].amount < sd->mail_append.amount )
			return 1;

		memcpy(&md->item, &sd->status.inventory[idx], sizeof(struct item));
		md->item.amount = sd->mail_append.amount;
		pc_delitem(sd, idx, md->item.amount, 1, 0);
	}
	sd->status.zeny -= md->zeny;
	clif_updatestatus(sd,SP_ZENY);

	return 0;
}

/*==========================================
 * 送信前チェック
 *------------------------------------------
 */
int mail_checkmail(struct map_session_data *sd, const char *name, const char *title, const char *body, int len)
{
	struct map_session_data *rd = map_nick2sd(name);
	struct mail_data md;

	nullpo_retr(0, sd);

	// 本文の長さが不正、または送信相手が自分ならダメ
	if(len <= 0 || len > sizeof(md.body) || rd == sd) {
		clif_res_sendmail(sd->fd,1);
		mail_removeitem(sd,0);
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
int mail_sendmail(struct map_session_data *sd, struct mail_data *md)
{
	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	// 日付の保存
	md->times = (unsigned int)time(NULL);
	// アイテム・Zenyチェック
	if(mail_checkappend(sd,md) == 0)
		intif_sendmail(md);

	sd->mail_append.index    = -1;
	sd->mail_append.amount   = 0;
	sd->mail_append.zeny     = 0;
	sd->state.mail_appending = 0;

	return 0;
}

/*==========================================
 * 添付アイテムやZenyを取得
 *------------------------------------------
 */
void mail_getappend(int account_id, int zeny, int mail_num, struct item *item)
{
	bool result = true;
	struct map_session_data *sd;

	nullpo_retv(item);

	sd = map_id2sd(account_id);
	if(sd == NULL)
		return;

	// アイテムチェック
	if( item->nameid > 0 && item->amount > 0 )
	{
		switch(pc_checkadditem(sd,item->nameid,item->amount))
		{
			case ADDITEM_EXIST:
				clif_mail_getappend(sd->fd,0);
				break;
			case ADDITEM_OVERAMOUNT:
				clif_mail_getappend(sd->fd,2);
				result = false;
				break;
			default:
				clif_mail_getappend(sd->fd,1);
				result = false;
		}
	}

	// Zenyチェック
	if( zeny > 0 )
	{
		if( sd->status.zeny > MAX_ZENY - zeny )
			result = false;
	}

	// アイテムの取得に成功した場合、添付ファイルの削除をキャラ鯖に要求する
	if( result == true )
	{
		// アイテムの取得
		if( item->nameid > 0 && item->amount > 0 )
		{
			pc_additem(sd, item, item->amount);
		}

		// Zenyの取得
		if( zeny > 0 )
		{
			sd->status.zeny += zeny;
			clif_updatestatus(sd,SP_ZENY);
		}
		intif_mail_deleteappend(sd->status.char_id,mail_num);
	}

	return;
}
