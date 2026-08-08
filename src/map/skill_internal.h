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

#define SKILLUNITTIMER_INVERVAL	50

typedef int (*SkillFunc)(struct block_list *,struct block_list *,int,int,unsigned int,int);

extern int skill_area_temp[8];
extern struct dbt *skillname_db;

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

int skill_area_trap_sub(struct block_list *bl, va_list ap);
int skill_count_water(struct block_list *src, int range);
int skill_tarot_card_of_fate(struct block_list *src, struct block_list *target, int skillid, int skilllv, unsigned int tick, int wheel);
int skill_balkyoung(struct block_list *bl, va_list ap);
int skill_delunit_by_ganbantein(struct block_list *bl, va_list ap);
int skill_shimiru(struct block_list *bl, va_list ap);
int skill_shinkirou(struct block_list *bl, va_list ap);
int skill_kunaikussetsu(struct block_list *bl, va_list ap);

int skill_clear_element_field(struct block_list *bl);
int skill_detonator(struct block_list *bl, va_list ap);
int skill_dominion_impulse(struct block_list *bl, va_list ap);
int skill_fire_expansion(struct block_list *bl, va_list ap);
int skill_fuumakouchiku(struct block_list *bl, va_list ap);

int skill_unit_onplace(struct skill_unit *src, struct block_list *bl, unsigned int tick);
int skill_unit_onplace_timer(struct skill_unit *src, struct block_list *bl, unsigned int tick);
int skill_count_target(struct block_list *bl, va_list ap);
int skill_trap_splash(struct block_list *bl, va_list ap);

int skill_item_consume(struct block_list *bl, struct skill_condition *cnd, int type, int *itemid, int *amount);
int skill_check_unit_id(struct block_list *bl, va_list ap);
int skill_check_condition_char_sub(struct block_list *bl, va_list ap);
int skill_check_condition_use_sub(struct block_list *bl, va_list ap);
int skill_check_condition_mob_master_sub(struct block_list *bl, va_list ap);
int skill_check_condition2_pc(struct map_session_data *sd, struct skill_condition *cnd, int type);

int skill_split_str(char *str, char **val, int num);
int skill_split_atoi(char *str, int *val, int num);
int skill_split_strtol(char *str, int *val, int num, int base);
void skill_init_unit_layout(void);
int skill_readdb(void);

#endif /* _SKILL_INTERNAL_H_ */
