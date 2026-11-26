/*
 * Copyright (C) 2002-2026  Auriga
 *
 * Cash / expansion emotion packs (db/emotion_pack.lua).
 */

#ifndef _EMOTION_PACK_H_
#define _EMOTION_PACK_H_

#include "map.h"

#define EMOTION_PACK_MAX 64
#define EMOTION_PACK_ID_MAX 31
#define EMOTION_PACK_REG_MASK "#EMOTION_PACKS"

struct emotion_pack_data {
	short id;
	int price;			/* 0 = free */
	int item_id;			/* >0 item currency; 0 + price>0 = PC_SHOP_POINT */
	unsigned int start_date;	/* YYYYMMDD sale window */
	unsigned int end_date;
	unsigned int duration;		/* rental seconds; 0 = permanent */
};

const struct emotion_pack_data *emotion_pack_search(int id);
int emotion_pack_owned(struct map_session_data *sd, int pack_id);
/* expire unix time; 0 if permanent or not owned */
unsigned int emotion_pack_expire(struct map_session_data *sd, int pack_id);
int emotion_pack_unlock(struct map_session_data *sd, int pack_id);
int emotion_pack_buy(struct map_session_data *sd, int pack_id);
int emotion_pack_has_emotion(int pack_id, int emotion_id);
int emotion_pack_can_use(struct map_session_data *sd, int pack_id);

void emotion_pack_clear(void);
int emotion_pack_insert(int id, int price, int item_id,
	unsigned int start_date, unsigned int end_date, unsigned int duration);

int do_init_emotion_pack(void);
void do_final_emotion_pack(void);

#endif /* _EMOTION_PACK_H_ */
