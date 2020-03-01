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

#include "friend.h"
#include "map.h"
#include "path.h"
#include "clif.h"
#include "chrif.h"
#include "pc.h"
#include "db.h"
#include "battle.h"
#include "nullpo.h"
#include "msg.h"
#include "achieve.h"

static struct dbt * online_db = NULL;

/*==========================================
 * 友達リスト追加要請
 *------------------------------------------
 */
int friend_add_request( struct map_session_data *sd, const char* name )
{
	struct map_session_data *tsd = map_nick2sd( name );

	nullpo_retr(0, sd);

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	if( tsd==NULL )
	{
		// 失敗
		clif_friend_add_ack( sd->fd, 0, 0, msg_txt(175), 1 ); // log off
		return 0;
	}

	if( sd->friend_invite > 0 || tsd->friend_invite > 0 )
		return 0;

	if(sd->bl.m != tsd->bl.m)
		return 0;
	if(path_distance(sd->bl.x,sd->bl.y,tsd->bl.x,tsd->bl.y) > AREA_SIZE)
		return 0;
	if(sd->status.char_id == tsd->status.char_id)
		return 0;

	sd->friend_invite      = tsd->bl.id;
	sd->friend_invite_char = tsd->status.char_id;
	memcpy( sd->friend_invite_name, tsd->status.name, 24 );

	tsd->friend_invite      = sd->bl.id;
	tsd->friend_invite_char = sd->status.char_id;
	memcpy( tsd->friend_invite_name, sd->status.name, 24 );

	// 要求を出す
	clif_friend_add_request( tsd->fd, sd );
	return 1;
}

/*==========================================
 * 友達リスト追加要請返答
 *------------------------------------------
 */
int friend_add_reply( struct map_session_data *sd, int account_id, int char_id, int flag )
{
	struct map_session_data *tsd = map_id2sd( account_id );

	nullpo_retr(0, sd);

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	// 変じゃないか1
	if( sd->friend_invite != account_id || sd->friend_invite_char != char_id ||  tsd==NULL )
	{
		clif_friend_add_ack( sd->fd, sd->friend_invite, sd->friend_invite_char, sd->friend_invite_name, 1 );
		return 0;
	}
	sd->friend_invite = 0;

	// 変じゃないか2
	if( tsd->friend_invite != sd->bl.id || char_id != tsd->status.char_id )
	{
		clif_friend_add_ack( sd->fd, sd->friend_invite, sd->friend_invite_char, sd->friend_invite_name, 1 );
		return 0;
	}
	tsd->friend_invite = 0;

	// 追加拒否
	if( flag==0 )
	{
		clif_friend_add_ack( tsd->fd, sd->bl.id, sd->status.char_id, sd->status.name, 1 );
		return 0;
	}

	// 追加処理
	if( sd->status.friend_num==MAX_FRIEND || tsd->status.friend_num==MAX_FRIEND )
	{
		// 人数オーバー
		clif_friend_add_ack( sd->fd, tsd->bl.id, tsd->status.char_id, tsd->status.name, (sd->status.friend_num==MAX_FRIEND)? 2:3 );
		clif_friend_add_ack( tsd->fd, sd->bl.id, sd->status.char_id, sd->status.name, (tsd->status.friend_num==MAX_FRIEND)? 2:3 );
		return 0;
	}
	sd->status.friend_data[sd->status.friend_num].account_id = tsd->bl.id;
	sd->status.friend_data[sd->status.friend_num].char_id = tsd->status.char_id;
	memcpy( sd->status.friend_data[sd->status.friend_num].name, tsd->status.name, 24 );
	sd->status.friend_num++;
	sd->state.friend_sended = 0;

	tsd->status.friend_data[tsd->status.friend_num].account_id = sd->bl.id;
	tsd->status.friend_data[tsd->status.friend_num].char_id = sd->status.char_id;
	memcpy( tsd->status.friend_data[tsd->status.friend_num].name, sd->status.name, 24 );
	tsd->status.friend_num++;
	tsd->state.friend_sended = 0;

	// 追加通知
	clif_friend_add_ack( sd->fd, tsd->bl.id, tsd->status.char_id, tsd->status.name, 0 );
	clif_friend_add_ack( tsd->fd, sd->bl.id, sd->status.char_id, sd->status.name, 0 );

	achieve_update_content(sd, ACH_ADD_FRIEND, 1, sd->status.friend_num);
	achieve_update_content(tsd, ACH_ADD_FRIEND, 1, tsd->status.friend_num);

	return 1;
}

/*==========================================
 * 友達リスト削除用ヘルパ
 *------------------------------------------
 */
static int friend_delete( struct map_session_data *sd, int account_id, int char_id )
{
	int i;

	nullpo_retr(0, sd);

	for( i=0; i< sd->status.friend_num; i++ )
	{
		struct friend_data * frd = &sd->status.friend_data[i];
		if(frd && frd->account_id == account_id && frd->char_id == char_id )
		{
			sd->status.friend_num--;
			sd->state.friend_sended = 0;
			memmove( frd, frd+1, sizeof(struct friend_data)* ( sd->status.friend_num - i ) );
			clif_friend_del_ack( sd->fd, account_id, char_id );	// 通知
			return 1;
		}
	}
	return 0;
}

/*==========================================
 * 友達リスト削除
 *------------------------------------------
 */
int friend_del_request( struct map_session_data *sd, int account_id, int char_id )
{
	struct map_session_data *tsd = map_id2sd( account_id );

	nullpo_retr(0, sd);

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	if( tsd!=NULL && tsd->status.char_id == char_id )
	{
		friend_delete( tsd, sd->bl.id, sd->status.char_id );
	}
	else
	{
		chrif_friend_delete( sd, account_id, char_id );
	}
	friend_delete( sd, account_id, char_id );
	return 0;
}

/*==========================================
 * 別サーバーの友達リスト削除
 *------------------------------------------
 */
int friend_del_from_otherserver( int account_id, int char_id, int account_id2, int char_id2 )
{
	struct map_session_data *tsd = map_id2sd( account_id );

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	if( tsd!=NULL && tsd->status.char_id == char_id )
		friend_delete( tsd, account_id2, char_id2 );

	return 0;
}

/*==========================================
 * ロード直後の情報送信
 *------------------------------------------
 */
int friend_send_info( struct map_session_data *sd )
{
	int i;

	nullpo_retr(0, sd);

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	if(sd->state.friend_sended != 0)	// ログインのときにすでに送信済み
		return 0;

	// リスト送信
	clif_friend_send_info( sd );

	// 全員のオンライン情報を送信
	for( i=0; i<sd->status.friend_num; i++ )
	{
		if( numdb_exists( online_db, sd->status.friend_data[i].char_id ) )
		{
			clif_friend_send_online( sd->fd, sd->status.friend_data[i].account_id, sd->status.friend_data[i].char_id, 0 );
		}
	}

	return 0;
}

/*==========================================
 * オンライン情報送信
 *------------------------------------------
 */
int friend_send_online( struct map_session_data *sd, int flag )
{
	int i;

	nullpo_retr(0, sd);

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	if(flag==0 && sd->state.friend_sended != 0)	// ログインのときにすでに送信済み
		return 0;

	// オンライン情報を保存
	if( flag==0 ) {
		numdb_insert( online_db, sd->status.char_id, INT2PTR(1) );
	} else {
		numdb_erase( online_db, sd->status.char_id );
	}

	// 全員に通知
	for( i=0; i<sd->status.friend_num; i++ )
	{
		struct map_session_data *sd2 = map_id2sd( sd->status.friend_data[i].account_id );
		if( sd2!=NULL && sd->status.friend_data[i].char_id == sd2->status.char_id )
		{
			clif_friend_send_online( sd2->fd, sd->bl.id, sd->status.char_id, flag );
		}
	}

	// char 鯖へ通知
	chrif_friend_online( sd, flag );
	sd->state.friend_sended = 1;

	return 0;
}

/*==========================================
 * 別マップサーバーの友人のオンライン情報送信
 *------------------------------------------
 */
int friend_send_online_from_otherserver( int account_id, int char_id, int flag, int num, int* list )
{
	int i;

	// サーバー側管理かどうか
	if( !battle_config.serverside_friendlist )
		return 0;

	// オンライン情報を保存
	if( flag==0 ) {
		numdb_insert( online_db, char_id, INT2PTR(1) );
	} else {
		numdb_erase( online_db, char_id );
	}

	// 全員に通知
	for( i=0; i<num; i++ )
	{
		struct map_session_data *sd2 = map_id2sd( list[i*2] );
		if( sd2!=NULL && list[i*2+1] == sd2->status.char_id )
		{
			clif_friend_send_online( sd2->fd, account_id, char_id, flag );
		}
	}
	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
void do_init_friend(void)
{
	online_db = numdb_init();
}

/*==========================================
 * 終了
 *------------------------------------------
 */
void do_final_friend(void)
{
	if(online_db)
		numdb_final(online_db,NULL);
}
