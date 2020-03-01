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

#include "map.h"
#include "ranking.h"
#include "nullpo.h"
#include "clif.h"
#include "pc.h"
#include "msg.h"
#include "chrif.h"

static struct Ranking_Data ranking_data[MAX_RANKING][MAX_RANKER];

static const char *ranking_title[MAX_RANKING] = {
	"BLACKSMITH",
	"ALCHEMIST",
	"TAEKWON",
	"PK",
	//"PVP",
};

static const char *ranking_reg[MAX_RANKING] = {
	"PC_BLACKSMITH_POINT",
	"PC_ALCHEMIST_POINT",
	"PC_TAEKWON_POINT",
	"PC_PK_POINT",
	//"PC_PVP_POINT",
};


/*==========================================
 * ランキングを返す
 * 0 : ランク外
 *------------------------------------------
 */
int ranking_get_pc_rank(struct map_session_data * sd,int ranking_id)
{
	int i;

	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	for(i=0; i<MAX_RANKER; i++) {
		if(sd->status.char_id == ranking_data[ranking_id][i].char_id)
			return i+1;
	}

	return 0;
}

/*==========================================
 * idからランキングを求める
 * 0 : ランク外
 *------------------------------------------
 */
int ranking_get_id2rank(int char_id,int ranking_id)
{
	int i;

	if(char_id <= 0)
		return 0;

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	for(i=0; i<MAX_RANKER; i++)
	{
		if(ranking_data[ranking_id][i].char_id == char_id)
			return i+1;
	}

	return 0;
}

/*==========================================
 * ランキングポイントを返す
 *------------------------------------------
 */
int ranking_get_point(struct map_session_data * sd,int ranking_id)
{
	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	return sd->ranking_point[ranking_id];
}

/*==========================================
 * ランキングポイントのセット
 *------------------------------------------
 */
int ranking_set_point(struct map_session_data * sd,int ranking_id,int point)
{
	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	sd->ranking_point[ranking_id] = point;

	return 1;
}

/*==========================================
 * ランキングポイントの獲得
 *------------------------------------------
 */
int ranking_gain_point(struct map_session_data * sd,int ranking_id,int point)
{
	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	sd->ranking_point[ranking_id] += point;

#if PACKETVER < 20130710
	switch(ranking_id){
	case RK_BLACKSMITH:
		clif_blacksmith_point(sd->fd,sd->ranking_point[ranking_id],point);
		break;
	case RK_ALCHEMIST:
		clif_alchemist_point(sd->fd,sd->ranking_point[ranking_id],point);
		break;
	case RK_TAEKWON:
		if(sd->ranking_point[ranking_id]%100 == 0)
			clif_taekwon_point(sd->fd,sd->ranking_point[ranking_id]/100,1);
		//	clif_taekwon_point(sd->fd,sd->ranking_point[ranking_id]/100,point);
		break;
	case RK_PK:
		clif_pk_point(sd->fd,sd->ranking_point[ranking_id],point);
		break;
	default:
		break;
	}
#else
	clif_updata_ranking_point(sd->fd,sd->ranking_point[ranking_id],point,ranking_id);
#endif

	return 1;
}

/*==========================================
 * キャラ永続変数へ書き込み
 *------------------------------------------
 */
int ranking_setglobalreg(struct map_session_data * sd,int ranking_id)
{
	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	pc_setglobalreg(sd, ranking_reg[ranking_id], sd->ranking_point[ranking_id]);

	return 1;
}

/*==========================================
 * キャラ永続変数へ全て書き込み
 *------------------------------------------
 */
int ranking_setglobalreg_all(struct map_session_data * sd)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_RANKING; i++)
		ranking_setglobalreg(sd,i);

	return 1;
}

/*==========================================
 * キャラ永続変数から読み込み
 *------------------------------------------
 */
int ranking_readreg(struct map_session_data * sd)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_RANKING; i++)
		sd->ranking_point[i] = pc_readglobalreg(sd, ranking_reg[i]);

	return 1;
}

/*==========================================
 * ランキング更新
 *------------------------------------------
 */
int ranking_update(struct map_session_data * sd,int ranking_id)
{
	int i,rank = -1;

	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	for(i=0; i<MAX_RANKER; i++) {
		//既にランカー
		if(sd->status.char_id == ranking_data[ranking_id][i].char_id) {
			rank = i;
			break;
		}
	}

	// 順位にはなかった
	if(i >= MAX_RANKER) {
		// 最下位より高得点ならランクイン
		if(ranking_data[ranking_id][MAX_RANKER-1].point < sd->ranking_point[ranking_id])
			rank = MAX_RANKER;	// MAX_RANKER+1 位としておく
	}

	if(rank >= 0) {
		struct Ranking_Data rd;
		memcpy(rd.name, sd->status.name, 24);
		rd.point   = sd->ranking_point[ranking_id];
		rd.char_id = sd->status.char_id;

		chrif_ranking_update(&rd,ranking_id,rank);
	}

	return 1;
}

/*==========================================
 * ランキングデータ受信
 *------------------------------------------
 */
int ranking_set_data(int ranking_id,struct Ranking_Data *rd)
{
	nullpo_retr(0, rd);

	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	memcpy(&ranking_data[ranking_id], rd, sizeof(ranking_data[0]));

	return 1;
}

/*==========================================
 * ランキングの表示（clif.c用）
 *------------------------------------------
 */
int ranking_clif_display(struct map_session_data * sd,int ranking_id)
{
	int i;
	const char *charname[10];
	int point[10];

	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;
	for(i=0; i<10 && i<MAX_RANKER; i++) {
		if(ranking_data[ranking_id][i].name[0] == 0)
			charname[i] = msg_txt(143);
		else
			charname[i] = ranking_data[ranking_id][i].name;

		if(ranking_id == RK_TAEKWON)
			point[i] = ranking_data[ranking_id][i].point/100;
		else
			point[i] = ranking_data[ranking_id][i].point;
	}
	for( ; i<10; i++) {	// MAX_RANKERが10より小さい場合
		charname[i] = "-";
		point[i] = 0;
	}

#if PACKETVER < 20130710
	switch(ranking_id) {
	case RK_BLACKSMITH:
		clif_blacksmith_ranking(sd->fd,charname,point);
		break;
	case RK_ALCHEMIST:
		clif_alchemist_ranking(sd->fd,charname,point);
		break;
	case RK_TAEKWON:
		clif_taekwon_ranking(sd->fd,charname,point);
		break;
	case RK_PK:
		clif_pk_ranking(sd->fd,charname,point);
		break;
	default:
		break;
	}
#else
	clif_rankinglist(sd->fd,charname,point,ranking_id,sd->ranking_point[ranking_id]);
#endif

	return 1;
}

/*==========================================
 * ランキングの直接表示
 *------------------------------------------
 */
int ranking_display(struct map_session_data * sd,int ranking_id,int begin,int end)
{
	int i;

	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	if(begin < 0)
		begin = 0;
	if(end >= MAX_RANKER)
		end = MAX_RANKER-1;

	msg_output(sd->fd, msg_txt(140), ranking_title[ranking_id]);

	for(i=begin; i<=end; i++)
	{
		const char *name = (ranking_data[ranking_id][i].name[0] == 0)? msg_txt(143): ranking_data[ranking_id][i].name;
		msg_output(sd->fd, msg_txt(141), i+1, name, ranking_data[ranking_id][i].point);
	}
	clif_displaymessage(sd->fd, msg_txt(142));
	msg_output(sd->fd, msg_txt(139), sd->status.name, ranking_title[ranking_id], sd->ranking_point[ranking_id]);

	return 1;
}

/*==========================================
 * ランキングポイントの表示
 *------------------------------------------
 */
int ranking_display_point(struct map_session_data * sd,int ranking_id)
{
	nullpo_retr(0, sd);

	// ランキング対象がない
	if(ranking_id < 0 || MAX_RANKING <= ranking_id)
		return 0;

	msg_output(sd->fd, msg_txt(139), sd->status.name, ranking_title[ranking_id], sd->ranking_point[ranking_id]);

	return 1;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_ranking(void)
{
	memset(&ranking_data, 0, sizeof(ranking_data));

	return 0;
}
