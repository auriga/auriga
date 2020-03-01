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

#ifndef _BATTLE_H_
#define _BATTLE_H_

// ダメージ
struct Damage {
	int damage,damage2;
	int type, div_;
	int amotion, dmotion;
	int blewcount;
	int flag;
	int dmg_lv;	//囲まれ減算計算用　0:スキル攻撃 ATK_LUCKY,ATK_FLEE,ATK_DEF
};

// 属性修正計算
int battle_attr_fix(int damage,int atk_elem,int def_elem);

// 最終計算のフラグ
enum {
	BF_WEAPON     = 0x0001,
	BF_MAGIC      = 0x0002,
	BF_MISC       = 0x0004,
	BF_SHORT      = 0x0010,
	BF_LONG       = 0x0040,
	BF_SKILL      = 0x0100,
	BF_NORMAL     = 0x0200,
	BF_WEAPONMASK = 0x000f,
	BF_RANGEMASK  = 0x00f0,
	BF_SKILLMASK  = 0x0f00,
};

// 囲まれペナルティ計算用
enum {
	ATK_LUCKY = 1,
	ATK_FLEE,
	ATK_DEF
};

struct map_session_data;
struct mob_data;
struct block_list;

// 実際にHPを増減
int battle_delay_damage(unsigned int tick,struct block_list *src,struct block_list *target,int damage,int skillid,int skilllv,int flag);
int battle_damage(struct block_list *bl,struct block_list *target,int damage,int skillid,int skilllv,int flag);
int battle_damage_area(struct block_list *bl,va_list ap);
int battle_heal(struct block_list *bl,struct block_list *target,int hp,int sp,int flag);

// 攻撃処理まとめ
int battle_weapon_attack( struct block_list *bl,struct block_list *target,
	unsigned int tick,int flag);
int battle_skill_attack(int attack_type,struct block_list* src,struct block_list *dsrc,
	struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag);
int battle_skill_attack_area(struct block_list *bl,va_list ap);
int battle_calc_base_magic_damage(struct block_list *src);

enum {
	BCT_NOENEMY = 0x00000,
	BCT_PARTY   = 0x10000,
	BCT_ALL     = 0x20000,
	BCT_ENEMY   = 0x40000,
	BCT_NOPARTY = 0x50000,
	BCT_NOONE   = 0x60000,
};

int battle_check_undead(int race,int element);
int battle_check_target(struct block_list *src, struct block_list *target,int flag);
int battle_check_range(struct block_list *src,struct block_list *bl,int range);
int battle_delarrow(struct map_session_data* sd,int num,int skillid);
void battle_join_struggle(struct mob_data *md,struct block_list *src);


// 設定
extern struct Battle_Config {
	int warp_point_debug;
	int enemy_critical;
	int enemy_critical_rate;
	int enemy_str;
	int enemy_perfect_flee;
	int cast_rate;
	int no_cast_dex;
	int delay_rate;
	int delay_dependon_dex,no_delay_dex;
	int sdelay_attack_enable;
	int left_cardfix_to_right;
	int pc_skill_add_range;
	int skill_out_range_consume;
	int mob_skill_add_range;
	int pc_damage_delay;
	int pc_damage_delay_rate;
	int defnotenemy;
	int random_monster_checklv;
	int attr_recover;
	int flooritem_lifetime;
	int item_auto_get;
	int item_first_get_time;
	int item_second_get_time;
	int item_third_get_time;
	int mvp_item_first_get_time;
	int mvp_item_second_get_time;
	int mvp_item_third_get_time;
	int item_rate,base_exp_rate,job_exp_rate;
	int drop_rate0item;
	int death_penalty_type;
	int death_penalty_base,death_penalty_job;
	int zeny_penalty;
	int zeny_penalty_percent;
	int zeny_penalty_by_lvl;
	int restart_hp_rate;
	int restart_sp_rate;
	int mvp_item_rate,mvp_exp_rate;
	int mvp_hp_rate;
	int monster_hp_rate;
	int monster_max_aspd;
	int homun_max_aspd;
	int merc_max_aspd;
	int elem_max_aspd;
	int atc_gmonly;
	int gm_allskill;
	int gm_allskill_addabra;
	int gm_allequip;
	int gm_skilluncond;
	int skillfree;
	int skillup_limit;
	int wp_rate;
	int pp_rate;
	int cdp_rate;
	int monster_active_enable;
	int monster_damage_delay_rate;
	int monster_loot_type;
	int mob_skill_use;
	int mob_count_rate;
	int mob_delay_rate;
	int mob_middle_boss_delay_rate;
	int mob_mvp_boss_delay_rate;
	int quest_skill_learn;
	int quest_skill_reset;
	int basic_skill_check;
	int guild_emperium_check;
	int guild_exp_limit;
	int guild_emblem_colors;
	int pc_invincible_time;
	int pet_catch_rate;
	int pet_rename;
	int pet_friendly_rate;
	int pet_hungry_delay_rate;
	int pet_hungry_friendly_decrease;
	int pet_str;
	int pet_status_support;
	int pet_attack_support;
	int pet_damage_support;
	int pet_support_rate;
	int pet_attack_exp_to_master;
	int pet_attack_exp_rate;
	int skill_min_damage;
	int finger_offensive_type;
	int heal_exp;
	int resurrection_exp;
	int shop_exp;
	int combo_delay_rate;
	int item_check;
	int wedding_modifydisplay;
	int natural_healhp_interval;
	int natural_healsp_interval;
	int natural_heal_skill_interval;
	int natural_heal_weight_rate;
	int natural_heal_weight_rate_icon;
	int item_name_override_grffile;
	int arrow_decrement;
	int allow_any_weapon_autoblitz;
	int max_aspd;
	int pvp_max_aspd;
	int gvg_max_aspd;
	int pk_max_aspd;
	int max_hp;
	int max_sp;
	int max_parameter;
	int max_cart_weight;
	int pc_skill_log;
	int mob_skill_log;
	int battle_log;
	int save_log;
	int error_log;
	int etc_log;
	int save_clothcolor;
	int undead_detect_type;
	int pc_auto_counter_type;
	int monster_auto_counter_type;
	int min_hitrate;
	int agi_penalty_type;
	int agi_penalty_count;
	int agi_penalty_num;
	int vit_penalty_type;
	int vit_penalty_count;
	int vit_penalty_num;
	int player_defense_type;
	int monster_defense_type;
	int pet_defense_type;
	int magic_defense_type;
	int pc_skill_reiteration;
	int monster_skill_reiteration;
	int pc_skill_nofootset;
	int monster_skill_nofootset;
	int pc_cloak_check_type;
	int monster_cloak_check_type;
	int gvg_short_damage_rate;
	int gvg_long_damage_rate;
	int gvg_normalskill_damage_rate;
	int gvg_magic_damage_rate;
	int gvg_misc_damage_rate;
	int gvg_eliminate_time;
	int mob_changetarget_byskill;
	int gvg_edp_down_rate;
	int pvp_edp_down_rate;
	int pk_edp_down_rate;
	int gvg_chargeattack_move;
	int pc_attack_direction_change;
	int monster_attack_direction_change;
	int pc_land_skill_limit;
	int monster_land_skill_limit;
	int party_skill_penalty;
	int monster_class_change_full_recover;
	int produce_item_name_input;
	int produce_potion_name_input;
	int making_arrow_name_input;
	int holywater_name_input;
	int display_delay_skill_fail;
	int display_snatcher_skill_fail;
	int chat_warpportal;
	int mob_warpportal;
	int dead_branch_active;
	int vending_max_value;
	int pet_lootitem;
	int pet_weight;
	int show_steal_in_same_party;
	int enable_upper_class;
	int pet_attack_attr_none;
	int mob_attack_attr_none;
	int pc_attack_attr_none;

	int agi_penalty_count_lv;
	int vit_penalty_count_lv;

	int gx_allhit;
	int gx_cardfix;
	int gx_dupele;
	int gx_disptype;
	int devotion_level_difference;
	int player_skill_partner_check;
	int sole_concert_type;
	int hide_GM_session;
	int invite_request_check;
	int gvg_trade_request_refused;
	int pvp_trade_request_refused;
	int skill_removetrap_type;
	int disp_experience;
	int castle_defense_rate;
	int riding_weight;
	int hp_rate;
	int sp_rate;
	int gm_can_drop_lv;
	int disp_hpmeter;
	int bone_drop;
	int bone_drop_itemid;
	int card_drop_rate;
	int equip_drop_rate;
	int consume_drop_rate;
	int refine_drop_rate;
	int etc_drop_rate;

	int potion_drop_rate;
	int arrow_drop_rate;
	int petequip_drop_rate;
	int weapon_drop_rate;
	int other_drop_rate;

	int item_res;
	int next_exp_limit;
	int monster_skill_over;
	int finding_ore_drop_rate;
	int joint_struggle_exp_bonus;
	int joint_struggle_limit;
	int pt_bonus_b;
	int pt_bonus_j;
	int equip_autospell_nocost;
	int mvp_announce;
	int petowneditem;
	int pet_loot_type;
	int buyer_name;
	int once_autospell;
	int allow_same_autospell;
	int combo_delay_lower_limits;
	int tkcombo_delay_lower_limits;
	int new_marrige_skill;
	int reveff_plus_addeff;
	int summonslave_no_drop;
	int summonslave_no_exp;
	int summonslave_no_mvp;
	int summonmonster_no_drop;
	int summonmonster_no_exp;
	int summonmonster_no_mvp;
	int cannibalize_no_drop;
	int cannibalize_no_exp;
	int cannibalize_no_mvp;
	int spheremine_no_drop;
	int spheremine_no_exp;
	int spheremine_no_mvp;
	int branch_mob_no_drop;
	int branch_mob_no_exp;
	int branch_mob_no_mvp;
	int branch_boss_no_drop;
	int branch_boss_no_exp;
	int branch_boss_no_mvp;
	int pc_hit_stop_type;
	int nomanner_mode;
	int death_by_unrig_penalty;
	int dance_and_play_duration;
	int soulcollect_max_fail;
	int gvg_flee_rate;
	int gvg_flee_penalty;
	int equip_sex;
	int weapon_attack_autospell;
	int magic_attack_autospell;
	int misc_attack_autospell;
	int magic_attack_drain;
	int magic_attack_drain_enable_type;
	int misc_attack_drain;
	int misc_attack_drain_enable_type;
	int hallucianation_off;
	int weapon_reflect_autospell;
	int magic_reflect_autospell;
	int weapon_reflect_drain;
	int weapon_reflect_drain_enable_type;
	int magic_reflect_drain;
	int magic_reflect_drain_enable_type;
	int max_parameter_str;
	int max_parameter_agi;
	int max_parameter_vit;
	int max_parameter_int;
	int max_parameter_dex;
	int max_parameter_luk;
	int cannibalize_nocost;
	int spheremine_nocost;
	int demonstration_nocost;
	int acidterror_nocost;
	int aciddemonstration_nocost;
	int chemical_nocost;
	int slimpitcher_nocost;
	int allow_assumptop_in_gvg;
	int allow_falconassault_elemet;
	int allow_guild_invite_in_gvg;
	int allow_guild_leave_in_gvg;
	int allow_guild_alliance_in_agit;
	int guild_skill_available;
	int guild_hunting_skill_available;
	int guild_skill_check_range;
	int allow_guild_skill_in_gvg_only;
	int allow_me_guild_skill;
	int emergencycall_point_type;
	int emergencycall_call_limit;
	int allow_guild_skill_in_gvgtime_only;
	int guild_skill_in_pvp_limit;
	int guild_exp_rate;
	int guild_skill_effective_range;
	int tarotcard_display_position;
	int job_soul_check;
	int repeal_die_counter_rate;
	int disp_job_soul_state_change;
	int check_knowlege_map;
	int tripleattack_rate_up_keeptime;
	int tk_counter_rate_up_keeptime;
	int allow_skill_without_day;
	int save_feel_map;
	int save_hate_mob;
	int twilight_party_check;
	int alchemist_point_type;
	int marionette_type;
	int max_marionette_str;
	int max_marionette_agi;
	int max_marionette_vit;
	int max_marionette_int;
	int max_marionette_dex;
	int max_marionette_luk;
	int max_marionette_pk_str;
	int max_marionette_pk_agi;
	int max_marionette_pk_vit;
	int max_marionette_pk_int;
	int max_marionette_pk_dex;
	int max_marionette_pk_luk;
	int max_marionette_pvp_str;
	int max_marionette_pvp_agi;
	int max_marionette_pvp_vit;
	int max_marionette_pvp_int;
	int max_marionette_pvp_dex;
	int max_marionette_pvp_luk;
	int max_marionette_gvg_str;
	int max_marionette_gvg_agi;
	int max_marionette_gvg_vit;
	int max_marionette_gvg_int;
	int max_marionette_gvg_dex;
	int max_marionette_gvg_luk;
	int baby_status_max;
	int baby_hp_rate;
	int baby_sp_rate;
	int upper_hp_rate;
	int upper_sp_rate;
	int normal_hp_rate;
	int normal_sp_rate;
	int baby_weight_rate;
	int upper_weight_rate;
	int normal_weight_rate;
	int no_emergency_call;
	int save_am_pharmacy_success;
	int save_all_ranking_point_when_logout;
	int soul_linker_battle_mode;
	int soul_linker_battle_mode_ka;
	int skillup_type;
	int allow_me_dance_effect;
	int allow_me_concert_effect;
	int allow_me_rokisweil;
	int pharmacy_get_point_type;
	int soulskill_can_be_used_for_myself;
	int hermode_gvg_only;
	int hermode_wp_check_range;
	int hermode_wp_check;
	int hermode_no_walking;
	int redemptio_penalty_type;
	int allow_weaponrearch_to_weaponrefine;
	int boss_no_knockbacking;
	int boss_no_element_change;
	int boss_teleport_on_landprotector;
	int scroll_produce_rate;
	int scroll_item_name_input;
	int pet_leave;
	int pk_short_damage_rate;
	int pk_long_damage_rate;
	int pk_normalskill_damage_rate;
	int pk_magic_damage_rate;
	int pk_misc_damage_rate;
	int cooking_rate;
	int making_rate;
	int extended_abracadabra;
	int no_pk_level;
	int allow_cloneskill_at_autospell;
	int pk_noshift;
	int pk_penalty_time;
	int clif_fixpos_type;
	int itemidentify;
	int casting_penalty_type;
	int casting_penalty_weapon;
	int casting_penalty_shield;
	int casting_penalty_armor;
	int casting_penalty_helm;
	int casting_penalty_robe;
	int casting_penalty_shoes;
	int casting_penalty_acce;
	int casting_penalty_arrow;
	int allow_homun_status_change;
	int save_homun_temporal_intimate;
	int homun_intimate_rate;
	int homun_temporal_intimate_resilience;
	int hvan_explosion_intimate;
	int homun_skill_intimate_type;
	int homun_speed_is_same_as_pc;
	int master_get_homun_base_exp;
	int master_get_homun_job_exp;

	int item_rate_details,item_rate_1,item_rate_10,item_rate_100,item_rate_1000;	//ドロップレート詳細
	int item_rate_1_min,item_rate_10_min,item_rate_100_min,item_rate_1000_min;	//ドロップレート詳細min
	int item_rate_1_max,item_rate_10_max,item_rate_100_max,item_rate_1000_max;	//ドロップレート詳細max
	int dropitem_itemrate_fix;

	int monster_damage_delay;

	int noportal_flag;
	int noexp_hiding;
	int noexp_trickdead;

	int gm_hide_attack_lv;
	int hide_attack;
	int gm_nomanner_lv;

	int serverside_friendlist;
	int pet0078_hair_id;

	int mes_send_type;

	int romail;

	int pc_die_script;
	int pc_kill_script;
	int pc_movemap_script;
	int pc_login_script;
	int pc_logout_script;
	int pc_mapin_script;
	int pc_mapout_script;
	int md_delete_script;
	int save_pckiller_type;

	int def_ratio_atk_to_shieldchain;
	int def_ratio_atk_to_carttermination;
	int player_gravitation_type;
	int enemy_gravitation_type;

	int mob_attack_fixwalkpos;
	int mob_ai_limiter;
	int mob_ai_cpu_usage;

	int show_always_party_name;

	// anti-hack
	int check_player_name_global_msg;
	int check_player_name_party_msg;
	int check_player_name_guild_msg;
	int check_player_name_battle_msg;
	int save_player_when_drop_item;
	int save_player_when_storage_closed;

	int extra_system_flag;
	int mob_take_over_sp;
	int party_join_limit;
	int check_skillpos_range;
	int pet_speed_is_same_as_pc;
	int tax_rate;
	int steal_rate;
	int sw_def_type;
	int calc_dist_flag;
	int allow_sw_dist;
	int personal_storage_sort;
	int guild_storage_sort;
	int allow_es_magic_all;
	int trap_is_invisible;
	int anklesnare_no_knockbacking;
	int gm_perfect_hide;
	int pcview_mob_clear_type;
	int party_item_share_type;
	int party_item_share_show;
	int pk_murderer_point;
	int sg_miracle_rate;
	int sg_angel_rate;
	int baby_copy_skilltree;
	int skill_autospell_delay_enable;
	int bonus_autospell_delay_enable;

	int merc_speed_is_same_as_pc;
	int master_get_merc_base_exp;
	int master_get_merc_job_exp;

	int party_invite_range_check;
	int homun_skilldelay_reset;
	int homun_statuschange_reset;
	int free_sc_data_dynamically;
	int snovice_maxexp_border;
	int homun_rename;
	int equip_window_type;
	int summonslave_generation;
	int str_weight;
	int pvp_send_guild_xy;
	int mvpitem_weight_limit;
	int roki_item_autospell;
	int trap_splash_on;
	int firepillar_splash_on;
	int mob_nohitstop_rate;
	int refinery_research_lv;
	int maprespawnguildid_all_players;
	int party_booking_lv;
	int new_statusup_calc;
	int third_status_max;
	int third_baby_status_max;
	int third_max_aspd;
	int third_song_overlap;
	int clif_fix_level;
	int get_status_point_over_lv100;
	int max_buyingstore_zeny;
	int max_buyingstore_amount;
	int allow_same_activeitem;
	int disable_transform_when_gvg;
	int esnv_status_max;
	int esnv_baby_status_max;
	int esnv_max_aspd;
	int ko_status_max;
	int ko_max_aspd;
	int rl_status_max;
	int rl_max_aspd;
	int sum_status_max;
	int sum_max_aspd;
	int disable_costume_when_gvg;
	int elem_attackskill_rate;
	int slave_inherit_mode;
	int no_cast_int;
	int monster_atk2_to_matk;
	int npc_timeout_time;
	int use_packet_obfuscation;
	int greed_use_town;
	int alliance_message;
	int ranker_potion_bonus;
	int ranker_potion_bonus_rogue;
	int ranker_weapon_bonus;
	int min_lv100_aspdfix;
	int min_npc_vendchat_distance;
	int ping_timer_interval;
	int enable_pet_autofeed;
	int enable_hom_autofeed;
} battle_config;

int battle_config_read(const char *cfgName);

int do_init_battle(void);
int do_final_battle(void);

#endif
