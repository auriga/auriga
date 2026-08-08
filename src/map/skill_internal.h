/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * Internal declarations shared by skill*.c (not part of public skill.h API).
 * Introduced for Issue #56 file split.
 */

#ifndef _SKILL_INTERNAL_H_
#define _SKILL_INTERNAL_H_

#include <stdarg.h>

#include "skill.h"

typedef int (*SkillFunc)(struct block_list *,struct block_list *,int,int,unsigned int,int);

extern int skill_area_temp[8];

int skill_area_sub(struct block_list *bl, va_list ap);
int skill_area_sub_count(struct block_list *src, struct block_list *target, int skillid, int skilllv, unsigned int tick, int flag);
int skill_partner_count(struct block_list *src, struct block_list *target, int skillid, int skilllv, unsigned int tick, int flag);
int skill_4thpartner_count(struct block_list *src, struct block_list *target, int skillid, int skilllv, unsigned int tick, int flag);

void skill_brandishspear_dir(struct square *tc, int dir, int are);
void skill_brandishspear_first(struct square *tc, int dir, int x, int y);

int skill_abra_dataset(struct map_session_data *sd, int skilllv);
int skill_am_twilight(struct map_session_data *sd, int skillid);
int skill_get_spellslot(int skillid);
int skill_landprotector(struct block_list *bl, va_list ap);
int skill_greed(struct block_list *bl, va_list ap);
int skill_trample(struct block_list *bl, va_list ap);
int skill_flicker(struct block_list *bl, va_list ap);
int skill_count_unitgroup(struct unit_data *ud, int skillid);
int skill_castle_mob_changetarget(struct block_list *bl, va_list ap);

#endif /* _SKILL_INTERNAL_H_ */
