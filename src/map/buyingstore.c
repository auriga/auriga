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

#include "nullpo.h"
#include "utils.h"
#include "mmo.h"

#include "battle.h"
#include "buyingstore.h"
#include "chat.h"
#include "chrif.h"
#include "clif.h"
#include "itemdb.h"
#include "map.h"
#include "path.h"
#include "npc.h"
#include "pc.h"
#include "trade.h"
#include "unit.h"

// 買取露店ID
static unsigned int buyingstore_id = 0;

// 買取露店開設失敗定義
enum e_open_failstore
{
	FAILED_OPEN_INVALIDDATA	= 1,
	FAILED_OPEN_WEIGHT		= 2,
	FAILED_OPEN_NODATA		= 8,
};

// 買取露店閉鎖定義
enum e_close_store
{
	CLOSE_ZENY		= 3,
	CLOSE_NOITEM	= 4,
};

// 買取露店買い取り失敗定義
enum e_trade_failstore
{
	FAILED_TRADE_INVALIDDATA	= 5,
	FAILED_TRADE_COUNT			= 6,
	FAILED_TRADE_ZENY			= 7,
};

/*==========================================
 * 買取露店ウインドウ表示処理
 *
 * @param sd 買取露店開設要求者
 * @param count 買取露店最大登録アイテム数
 * @return falseならウインドウ表示不可状態
 *------------------------------------------
 */
bool buyingstore_openstorewindow(struct map_session_data *sd, unsigned char count)
{
	nullpo_retr(false, sd);

	// 買取露店ウインドウが開ける状態かチェック
	if( sd->state.store || sd->state.deal_mode )
	{
		return false;
	}

	// countの範囲チェック
	if( count == 0 || count > MAX_BUYINGSTORE_COUNT )
	{
		return false;
	}

	sd->buyingstore.count = count;
	clif_openwindow_buyingstore(sd);

	return true;
}

/*==========================================
 * 買取露店開設処理
 *
 * @param sd 買取露店開設要求者
 * @param limit_zeny 最大買収金額
 * @param result trueなら開設する
 * @param store_name 買取露店名
 * @param data アイテムデータ
 * @param count アイテムデータ個数
 *------------------------------------------
 */
void buyingstore_openstore(struct map_session_data *sd, int limit_zeny, bool result, const char *store_name, const unsigned char *data, int count)
{
	int i, weight;
	struct item_data *id;

	nullpo_retv(sd);

	// 買取露店キャンセル
	if( result == false )
		return;

	// 金額の範囲チェック
	if( limit_zeny <= 0 || limit_zeny > sd->status.zeny )
	{
		sd->buyingstore.count = 0;
		clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
		return;
	}

	// countの範囲チェック
	if( count <= 0 || count > sd->buyingstore.count )
	{
		sd->buyingstore.count = 0;
		clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
		return;
	}

	// 露店開設中は開設不可
	if( sd->state.store )
	{
		sd->buyingstore.count = 0;
		clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
		return;
	}

	// 取引中は開設不可
	if( sd->state.deal_mode )
	{
		sd->buyingstore.count = 0;
		clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
		return;
	}

	// 先頭がnull文字かチェック
	if( store_name[0] == '\0' )
	{
		sd->buyingstore.count = 0;
		clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
		return;
	}

	// デタッチさせる
	if( sd->npc_id )
		npc_event_dequeue(sd);
	if( sd->trade.partner )
		trade_tradecancel(sd);
	if( sd->chatID )
		chat_leavechat(sd, 0);

	// プレイヤーの重量取得
	weight = sd->weight;

	// 買取露店データ初期化
	memset(&sd->buyingstore, 0, sizeof(struct buyingstore));

	// アイテムリストのチェック
	for( i = 0; i < count; i++ )
	{
		short nameid = *(short *)(data + 8*i + 0);
		short amount = *(short *)(data + 8*i + 2);
		int value    = *(int *)(data + 8*i + 4);
		int idx;

		// 自分が所持しているアイテムでないと買取出来ない
		if( (idx = pc_search_inventory(sd, nameid)) == -1 )
		{
			memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
			clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
			return;
		}

		// 個数のチェック
		if( amount <= 0 || sd->status.inventory[idx].amount+amount > battle_config.max_buyingstore_amount )
		{
			memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
			clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
			return;
		}

		// アイテムIDの存在チェック
		if( (id = itemdb_exists(nameid)) == NULL )
		{
			memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
			clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
			return;
		}

		// 金額チェック
		if( value <= 0 || value > battle_config.max_buyingstore_zeny )
		{
			memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
			clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
			return;
		}

		// 買取露店で買い取り可能なアイテムかチェック
		if( itemdb_isbuyingable(nameid) != 1 )
		{
			memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
			clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
			return;
		}

		// 重複するアイテムIDがないかチェック
		if( i )
		{
			int j;
			for( j = 0; j < i; j++ )
			{
				if( sd->buyingstore.item[j].nameid == nameid )
				{
					memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
					clif_failed_openbuyingstore(sd, FAILED_OPEN_INVALIDDATA, 0);
					return;
				}
			}
		}

		// 買取露店データにセット
		weight += id->weight * amount;
		sd->buyingstore.item[i].nameid = nameid;
		sd->buyingstore.item[i].amount = amount;
		sd->buyingstore.item[i].value  = value;
	}

	// 重量チェック
	if( (sd->max_weight*90) / 100 < weight )
	{
		memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
		clif_failed_openbuyingstore(sd, FAILED_OPEN_WEIGHT, 0);
		return;
	}

	// 移動と攻撃を止める
	unit_stop_walking(&sd->bl, 1);
	unit_stopattack(&sd->bl);

	// 買取露店オープン
	sd->state.store = STORE_TYPE_BUYINGSTORE;
	sd->buyer_id = ++buyingstore_id;
	sd->buyingstore.limit_zeny = limit_zeny;
	sd->buyingstore.count = i;
	strncpy(sd->message, store_name, 80);
	sd->message[79] = '\0';

	clif_showmylist_buyingstore(sd);
	clif_show_buyingstore(&sd->bl, sd->message, -1);

	return;
}

/*==========================================
 * 買取露店閉鎖処理
 *
 * @param sd 買取露店閉鎖要求者
 *------------------------------------------
 */
void buyingstore_close(struct map_session_data *sd)
{
	nullpo_retv(sd);

	if( sd->state.store == STORE_TYPE_BUYINGSTORE )
	{
		sd->state.store = STORE_TYPE_NONE;
		memset(&sd->buyingstore, 0, sizeof(struct buyingstore));
		clif_close_buyingstore(&sd->bl, -1);
	}

	return;
}

/*==========================================
 * 買取露店アイテムリスト表示
 *
 * @param sd 買取露店アイテムリスト回覧要求者
 * @param account_id 買取露店開設者アカウントID
 *------------------------------------------
 */
void buyingstore_itemlist(struct map_session_data* sd, int account_id)
{
	struct map_session_data *ssd;

	nullpo_retv(sd);

	// 対象が存在するかチェック
	if( (ssd = map_id2sd(account_id)) == NULL )
		return;

	// 対象がblock_listから抜けていないかチェック
	if( ssd->bl.prev == NULL )
		return;

	// 対象と自身が同じかチェック
	if( ssd->bl.id == sd->bl.id )
		return;

	// 自身が露店開設中かチェック
	if( sd->state.store )
		return;

	// 対象が買取露店を閉鎖中
	if( ssd->state.store != STORE_TYPE_BUYINGSTORE )
		return;

	// 対象が取引中もしくは自身が取引中かチェック
	if( ssd->state.deal_mode != 0 || sd->state.deal_mode != 0 )
		return;

	// 対象と自身が同じMAPかチェック
	if( sd->bl.m != ssd->bl.m )
		return;

	// 対象と自身がAREA_SIZE内に居るかチェック
	if( path_distance(sd->bl.x,sd->bl.y,ssd->bl.x,ssd->bl.y) > AREA_SIZE )
		return;

	// アイテムリストを送る
	clif_itemlist_buyingstore(sd,ssd);

	return;
}

/*==========================================
 * 買取露店アイテム売却処理
 *
 * @param sd 売却者
 * @param account_id 買取露店開設者アカウントID
 * @param buyer_id 買取露店開設者ストアID
 * @param data アイテムデータ
 * @param count アイテムデータ個数
 *------------------------------------------
 */
void buyingstore_sell(struct map_session_data *sd, int account_id, unsigned int buyer_id, const unsigned char *data, int count)
{
	double zeny = 0.;
	int new_ = 0;
	int blank;
	int i, weight, listidx;
	struct map_session_data *ssd;

	nullpo_retv(sd);

	// 対象が存在するかチェック
	if( (ssd = map_id2sd(account_id)) == NULL )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 対象がblock_listから抜けていないかチェック
	if( ssd->bl.prev == NULL )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 対象と自身が同じかチェック
	if( ssd->bl.id == sd->bl.id )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 対象と自身が同一MAPかチェック
	if( ssd->bl.m != sd->bl.m )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 対象と自身がAREA_SIZE内かチェック
	if( path_distance(sd->bl.x,sd->bl.y,ssd->bl.x,ssd->bl.y) > AREA_SIZE )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 対象が露店開設中かチェック
	if( ssd->state.store != STORE_TYPE_BUYINGSTORE )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// buyer_idが違えば不可
	if( ssd->buyer_id != buyer_id )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// countの範囲チェック
	if( count <= 0 || count > ssd->buyingstore.count )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 露店開設中は売却不可
	if( sd->state.store )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 取引中は売却不可
	if( sd->state.deal_mode )
	{
		clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
		return;
	}

	// 買取露店開設者の重量取得
	weight = ssd->weight;

	// 買取露店開設者の空きアイテム欄の個数取得
	blank = pc_inventoryblank(ssd);

	// アイテムデータ確認処理
	for( i = 0; i < count; i++ )
	{
		short idx    = *(short *)(data + 6*i + 0) - 2;
		short nameid = *(short *)(data + 6*i + 2);
		short amount = *(short *)(data + 6*i + 4);

		// indexの重複チェック
		if( i )
		{
			int j;
			for( j = 0; j < i; j++ )
			{
				short idx_tmp = *(short *)(data + 6*j + 0) - 2;
				if( idx == idx_tmp )
				{
					clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
					return;
				}
			}
		}

		// indexの範囲チェック
		if( idx < 0 || idx >= MAX_INVENTORY )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
			return;
		}

		// indexにアイテムは存在するかチェック
		if( sd->inventory_data[idx] == NULL )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
			return;
		}

		// アイテムIDのチェック
		if( sd->status.inventory[idx].nameid != nameid )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
			return;
		}

		// 個数のチェック
		if( amount <= 0 || sd->status.inventory[idx].amount < amount )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_COUNT, 0);
			return;
		}

		// 買い取り終了チェック
		for( listidx = 0; listidx < ssd->buyingstore.count; listidx++ )
		{
			if( ssd->buyingstore.item[listidx].nameid == nameid )
			{
				if( listidx >= ssd->buyingstore.count || ssd->buyingstore.item[listidx].amount <= 0 )
				{
					clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
					return;
				}
				break;
			}
		}

		// 個数チェック
		if( ssd->buyingstore.item[listidx].amount < amount )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_COUNT, 0);
			return;
		}

		// 重量計算
		weight += itemdb_weight(sd->inventory_data[idx]->nameid) * amount;

		// 重量チェック
		if( weight > ssd->max_weight )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_INVALIDDATA, 0);
			return;
		}

		// Zeny計算
		zeny += amount * ssd->buyingstore.item[listidx].value;

		// Zenyチェック
		if( sd->status.zeny > MAX_ZENY - zeny )
		{
			// 買取対象アイテムの合計金額が、キャラクターが所持可能な最大金額(2,147,483,647 Zeny)を超過しています。
			clif_msgstringtable(sd, 0x74e);
			return;
		}

		// 買い取り限度チェック
		if( zeny > ssd->buyingstore.limit_zeny )
		{
			clif_failed_tradebuyingstore(sd, FAILED_TRADE_ZENY, 0);
			return;
		}

		// インベントリ空きチェック
		switch(pc_checkadditem(ssd, sd->inventory_data[idx]->nameid, amount))
		{
			case ADDITEM_EXIST:
				break;
			case ADDITEM_NEW:
				new_++;
				if (new_ > blank)
					return;
				break;
			case ADDITEM_OVERAMOUNT:
				return;
		}
	}

	// 買い取り処理
	for( i = 0; i < count; i++ )
	{
		short idx    = *(short *)(data + 6*i + 0) - 2;
		short nameid = *(short *)(data + 6*i + 2);
		short amount = *(short *)(data + 6*i + 4);

		// 買い取り商品のZeny計算
		for( listidx = 0; listidx < ssd->buyingstore.count; listidx++ )
		{
			if( ssd->buyingstore.item[listidx].nameid == nameid )
			{
				zeny = amount * ssd->buyingstore.item[listidx].value;
				break;
			}
		}

		// アイテムの移動
		pc_additem(ssd, &sd->status.inventory[idx], amount);
		pc_delitem(sd, idx, amount, 1, 0);
		ssd->buyingstore.item[listidx].amount -= amount;

		// Zenyの支払い
		pc_payzeny(ssd, (int)zeny);
		pc_getzeny(sd, (int)zeny);
		ssd->buyingstore.limit_zeny -= (int)zeny;

		// クライアントへ送信
		clif_delete_buyingstore(sd, idx, amount, ssd->buyingstore.item[listidx].value);
		clif_update_buyingstore(ssd, nameid, amount, ssd->buyingstore.item[listidx].value * amount, sd->bl.id, sd->char_id);
	}

	// 買い取り品数チェック
	for( i = 0; (i < ssd->buyingstore.count) && (ssd->buyingstore.item[i].amount <= 0); i++ );
	if( i == ssd->buyingstore.count )
	{
		clif_failed_trybuyingstore(ssd, CLOSE_NOITEM);
		buyingstore_close(ssd);
	}

	// limit_zenyのチェック
	if( ssd->buyingstore.limit_zeny <= 0 )
	{
		clif_failed_trybuyingstore(ssd, CLOSE_ZENY);
		buyingstore_close(ssd);
	}

	// データをセーブ
	chrif_save(sd,0);
	chrif_save(ssd,0);

	return;
}
