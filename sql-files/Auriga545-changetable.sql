# fix some field type

ALTER TABLE `cart_inventory` MODIFY `nameid` smallint(6) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `amount` smallint(6) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `equip` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `identify` tinyint(4) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `refine` tinyint(4) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `card0` smallint(6) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `card1` smallint(6) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `card2` smallint(6) NOT NULL default '0';
ALTER TABLE `cart_inventory` MODIFY `card3` smallint(6) NOT NULL default '0';

ALTER TABLE `char` MODIFY `char_num` tinyint(4) unsigned NOT NULL default '0';
ALTER TABLE `char` MODIFY `name` varchar(24) NOT NULL default '';
ALTER TABLE `char` MODIFY `class` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `base_level` smallint(6) unsigned NOT NULL default '1';
ALTER TABLE `char` MODIFY `job_level` smallint(6) unsigned NOT NULL default '1';
ALTER TABLE `char` MODIFY `base_exp` int(11) NOT NULL default '0';
ALTER TABLE `char` MODIFY `job_exp` int(11) NOT NULL default '0';
ALTER TABLE `char` MODIFY `str` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `agi` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `vit` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `int` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `dex` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `luk` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `status_point` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `skill_point` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `karma` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `manner` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `hair` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `hair_color` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `clothes_color` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `weapon` smallint(6) NOT NULL default '1';
ALTER TABLE `char` MODIFY `shield` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `head_top` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `head_mid` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `head_bottom` smallint(6) NOT NULL default '0';
ALTER TABLE `char` MODIFY `last_map` varchar(24) NOT NULL default 'new_5-1.gat';
ALTER TABLE `char` MODIFY `last_x` smallint(6) NOT NULL default '53';
ALTER TABLE `char` MODIFY `last_y` smallint(6) NOT NULL default '111';
ALTER TABLE `char` MODIFY `save_map` varchar(24) NOT NULL default 'new_5-1.gat';
ALTER TABLE `char` MODIFY `save_x` smallint(6) NOT NULL default '53';
ALTER TABLE `char` MODIFY `save_y` smallint(6) NOT NULL default '111';

ALTER TABLE `global_reg_value` MODIFY `str` varchar(32) NOT NULL default '';
ALTER TABLE `global_reg_value` MODIFY `type` tinyint(4) NOT NULL default '3';

ALTER TABLE `guild_member` MODIFY `online` tinyint(4) unsigned NOT NULL default '0';

ALTER TABLE `guild_storage` MODIFY `nameid` smallint(6) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `amount` smallint(6) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `equip` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `identify` tinyint(4) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `refine` tinyint(4) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `card0` smallint(6) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `card1` smallint(6) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `card2` smallint(6) NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `card3` smallint(6) NOT NULL default '0';

ALTER TABLE `inventory` MODIFY `nameid` smallint(6) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `amount` smallint(6) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `equip` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `identify` tinyint(4) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `refine` tinyint(4) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `card0` smallint(6) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `card1` smallint(6) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `card2` smallint(6) NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `card3` smallint(6) NOT NULL default '0';

ALTER TABLE `login` MODIFY `userid` varchar(24) NOT NULL default '';
ALTER TABLE `login` MODIFY `user_pass` varchar(24) NOT NULL default '';
ALTER TABLE `login` MODIFY `logincount` int(11) NOT NULL default '0';
ALTER TABLE `login` MODIFY `email` varchar(40) NOT NULL default '';
ALTER TABLE `login` MODIFY `last_ip` varchar(16) NOT NULL default '';

ALTER TABLE `memo` MODIFY `x` smallint(6) NOT NULL default '0';
ALTER TABLE `memo` MODIFY `y` smallint(6) NOT NULL default '0';

ALTER TABLE `pet` MODIFY `class` smallint(6) NOT NULL default '0';
ALTER TABLE `pet` MODIFY `egg_id` smallint(6) NOT NULL default '0';
ALTER TABLE `pet` MODIFY `equip` smallint(6) NOT NULL default '0';
ALTER TABLE `pet` MODIFY `intimate` smallint(6) NOT NULL default '0';
ALTER TABLE `pet` MODIFY `hungry` smallint(6) NOT NULL default '0';
ALTER TABLE `pet` MODIFY `incubate` tinyint(4) NOT NULL default '0';

ALTER TABLE `skill` MODIFY `id` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `skill` MODIFY `lv` smallint(6) unsigned NOT NULL default '0';

ALTER TABLE `storage` MODIFY `nameid` smallint(6) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `amount` smallint(6) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `equip` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `storage` MODIFY `identify` tinyint(4) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `refine` tinyint(4) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `card0` smallint(6) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `card1` smallint(6) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `card2` smallint(6) NOT NULL default '0';
ALTER TABLE `storage` MODIFY `card3` smallint(6) NOT NULL default '0';

ALTER TABLE `homunculus` MODIFY `class` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `base_exp` int(11) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `str` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `agi` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `vit` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `int` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `dex` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `luk` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `status_point` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `skill_point` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `equip` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `intimate` int(11) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `hungry` smallint(6) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `incubate` tinyint(4) NOT NULL default '0';

ALTER TABLE `homunculus_skill` MODIFY `id` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `homunculus_skill` MODIFY `lv` smallint(6) unsigned NOT NULL default '0';

ALTER TABLE `status_change` MODIFY `type` smallint(6) NOT NULL default '0';

ALTER TABLE `mail_data` MODIFY `send_name` varchar(24) NOT NULL default '';
ALTER TABLE `mail_data` MODIFY `receive_name` varchar(24) NOT NULL default '';
ALTER TABLE `mail_data` MODIFY `title` varchar(40) NOT NULL default '';
ALTER TABLE `mail_data` MODIFY `id` int(11) unsigned NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `nameid` smallint(6) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `amount` smallint(6) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `equip` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `identify` tinyint(4) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `refine` tinyint(4) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `card0` smallint(6) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `card1` smallint(6) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `card2` smallint(6) NOT NULL default '0';
ALTER TABLE `mail_data` MODIFY `card3` smallint(6) NOT NULL default '0';

ALTER TABLE `feel_info` MODIFY `feel_id` bigint(20) unsigned NOT NULL auto_increment;
ALTER TABLE `feel_info` MODIFY `lv` smallint(6) NOT NULL default '-1';
