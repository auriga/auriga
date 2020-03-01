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

#define _INT_MAIL_C_

#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

#include "char.h"
#include "int_mail.h"

//------------------------------------------------------------------------
int mapif_mail_res(const int fd,int account,int flag)
{
	WFIFOW(fd,0)=0x3848;
	WFIFOL(fd,2)=account;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);
	return 0;
}

int mapif_send_mailbox(int fd,const char *char_name,int store,struct mail_data md[MAIL_STORE_MAX])
{
	int i,size = sizeof(struct mail_data);

	if(md == NULL)
		return 0;

	WFIFOW(fd,0)=0x3849;
	WFIFOL(fd,4)=store;
	memcpy(WFIFOP(fd,8),char_name,24);
	for(i=0;i<store;i++)
		memcpy(WFIFOP(fd,32+i*size),&md[i],size);
	WFIFOW(fd,2)=32+i*size;
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_newmail(int fd,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	WFIFOW(fd,0)=0x384a;
	WFIFOW(fd,2)=4+size;
	memcpy(WFIFOP(fd,4),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_readmail(int fd,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	WFIFOW(fd,0)=0x384b;
	WFIFOW(fd,2)=4+size;
	memcpy(WFIFOP(fd,4),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_delmail(int fd,int account,unsigned int mail_num,int flag)
{
	WFIFOW(fd,0)=0x384c;
	WFIFOL(fd,2)=account;
	WFIFOL(fd,6)=mail_num;
	WFIFOB(fd,10)=flag;
	WFIFOSET(fd,11);
	return 0;
}

int mapif_mail_getappend(int fd, int account, struct mail_data *md)
{
	int size = sizeof(struct item);

	if(!md)
		return 1;
	if((md->item.nameid <= 0 || md->item.amount <= 0) && md->zeny <= 0)
		return 1;

	WFIFOW(fd,0)=0x384d;
	WFIFOW(fd,2)=16+size;
	WFIFOL(fd,4)=account;
	WFIFOL(fd,8)=(md->zeny <= 0)? 0: md->zeny;
	WFIFOL(fd,12)=md->mail_num;
	memcpy(WFIFOP(fd,16),&md->item,size);
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_mail_checkok(int fd,int account,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	if(!md)
		return 1;

	WFIFOW(fd,0) = 0x384e;
	WFIFOW(fd,2) = 8+size;
	WFIFOL(fd,4) = account;
	memcpy(WFIFOP(fd,8),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//--------------------------------------------------------
int mapif_parse_OpenMailBox(int fd)
{
	int char_id = RFIFOL(fd,2);
	const struct mmo_chardata *rd;
	const struct mail *m;
	struct mail_data md[MAIL_STORE_MAX];

	rd = chardb_load(char_id);

	if(rd == NULL)
		return 0;

	memset(md, 0, sizeof(md));

	m = maildb_load(char_id);
	if(m)
	{
		maildb_read_mail(char_id, m, md);
		mapif_send_mailbox(fd,rd->st.name,m->store,md);
	}
	else
	{
		mapif_send_mailbox(fd,rd->st.name,0,md);
	}
	return 0;
}

int mapif_parse_SendMail(int fd)
{
	const struct mmo_chardata *sd, *rd;
	const struct mail *m;
	struct mail_data md;

	if(!RFIFOP(fd,4))
		return 0;

	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));

	sd = chardb_nick2chardata(md.char_name);
	if(sd == NULL)
		return 0;

	rd = chardb_nick2chardata(md.receive_name);

	// 受け取る人が存在しません
	if(rd == NULL)
	{
		mapif_mail_res(fd,sd->st.account_id,1);
		return 0;
	}

	// 同じアカウントには送れない
	if(sd->st.account_id == rd->st.account_id)
	{
		mapif_mail_res(fd,sd->st.account_id,1);
		return 0;
	}

	// 保存だの何だの
	m = maildb_load(rd->st.char_id);
	if(m)
	{
		struct mail m2;
		if(m->store >= MAIL_STORE_MAX)
		{
			// 最大受信数を越える場合は一番古いメールを削除する
			struct mail_data md[MAIL_STORE_MAX];

			maildb_read_mail(rd->st.char_id, m, md);
			maildb_deletemail(rd->st.char_id,md[0].mail_num,m);
		}
		memcpy(&m2,m,sizeof(struct mail));
		m2.rates++;
		m2.store++;
		maildb_save(&m2);
		md.mail_num = m2.rates;
	}
	else
	{
		maildb_new(rd->st.account_id,rd->st.char_id);
		md.mail_num = 1;
	}

	maildb_store_mail(rd->st.char_id,&md);	// 保存
	mapif_mail_res(fd,sd->st.account_id,0);	// 送信成功
	mapif_mail_newmail(fd,&md);		// 新着メール通知

	return 0;
}

int mapif_parse_DeleteMail(int fd)
{
	const struct mail *m = maildb_load(RFIFOL(fd,2));
	int flag;

	if(!m)
		return 0;

	flag = maildb_deletemail(m->char_id,RFIFOL(fd,6),m);
	mapif_mail_delmail(fd,m->account_id,RFIFOL(fd,6),!flag);	// 結果送信

	return 0;
}

int mapif_parse_ReadMail(int fd)
{
	const struct mail *m;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);

	if((m = maildb_load(char_id)) == NULL)
		return 0;

	if(m->store > 0)
	{
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		maildb_read_mail(char_id, m, md);

		for( i = 0; i < m->store; i++ )
		{
			if(md[i].mail_num == mail_num)
			{
				mapif_mail_readmail(fd,&md[i]);
				if(!md[i].read)
				{
					md[i].read = 1;
					maildb_save_mail(char_id,i,m->store,md);
					mapif_send_mailbox(fd,md[i].char_name,m->store,md);
				}
				break;
			}
		}
	}

	return 0;
}

int mapif_parse_GetAppend(int fd)
{
	const struct mail *m;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);

	if((m = maildb_load(char_id)) == NULL)
		return 0;

	if(m->store > 0)
	{
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		maildb_read_mail(char_id, m, md);

		for( i = 0; i < m->store; i++ )
		{
			if(md[i].mail_num == mail_num)
			{
				if(!mapif_mail_getappend(fd,m->account_id,&md[i]))
					mapif_mail_readmail(fd,&md[i]);
				break;
			}
		}
	}

	return 0;
}

int mapif_parse_CheckMail(int fd)
{
	int send_id = RFIFOL(fd,4);
	struct mail_data *md = (struct mail_data *)RFIFOP(fd,8);
	const struct mmo_chardata *rd;

	if(md == NULL)
		return 0;

	rd = chardb_nick2chardata(md->receive_name);

	// 受け取る人が存在しません
	if(rd == NULL || rd->st.account_id == send_id)
		mapif_mail_res(fd,send_id,1);
	else
		mapif_mail_checkok(fd,send_id,md);

	return 0;
}

int mapif_parse_DeleteAppend(int fd)
{
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);
	const struct mail *m = maildb_load(char_id);

	if( !m )
		return 0;

	if(m->store > 0)
	{
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		maildb_read_mail(char_id, m, md);

		for( i = 0; i < m->store; i++ )
		{
			if( md[i].mail_num == mail_num )
			{
				// ここで添付アイテムとzenyを削除する
				memset(&md[i].item, 0, sizeof(struct item));
				md[i].zeny = 0;
				maildb_save_mail(char_id, i, m->store, md);
				break;
			}
		}
	}

	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_mail_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)) {
	case 0x3049: mapif_parse_OpenMailBox(fd);    break;
	case 0x304a: mapif_parse_SendMail(fd);       break;
	case 0x304b: mapif_parse_DeleteMail(fd);     break;
	case 0x304c: mapif_parse_ReadMail(fd);       break;
	case 0x304d: mapif_parse_GetAppend(fd);      break;
	case 0x304e: mapif_parse_CheckMail(fd);      break;
	case 0x304f: mapif_parse_DeleteAppend(fd);   break;
	default:
		return 0;
	}
	return 1;
}
