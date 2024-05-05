# Database: Ragnarok
# Table: 'achieve'
# 
CREATE TABLE `achieve` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `count1` int(11) NOT NULL default '0',
  `count2` int(11) NOT NULL default '0',
  `count3` int(11) NOT NULL default '0',
  `count4` int(11) NOT NULL default '0',
  `count5` int(11) NOT NULL default '0',
  `count6` int(11) NOT NULL default '0',
  `count7` int(11) NOT NULL default '0',
  `count8` int(11) NOT NULL default '0',
  `count9` int(11) NOT NULL default '0',
  `count10` int(11) NOT NULL default '0',
  `comp_date` int(11) unsigned NOT NULL default '0',
  `reward` tinyint(4) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `nameid`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'cart_inventory'
# 
CREATE TABLE `cart_inventory` (
  `id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  `private` tinyint(4) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'char_data'
# 
CREATE TABLE `char_data` (
  `char_id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NOT NULL default '0',
  `char_num` tinyint(4) unsigned NOT NULL default '0',
  `name` varchar(24) BINARY NOT NULL default '',
  `class` smallint(6) NOT NULL default '0',
  `base_level` smallint(6) unsigned NOT NULL default '1',
  `job_level` smallint(6) unsigned NOT NULL default '1',
  `base_exp` bigint(20) NOT NULL default '0',
  `job_exp` bigint(20) NOT NULL default '0',
  `zeny` int(11) NOT NULL default '500',
  `str` smallint(6) NOT NULL default '0',
  `agi` smallint(6) NOT NULL default '0',
  `vit` smallint(6) NOT NULL default '0',
  `int` smallint(6) NOT NULL default '0',
  `dex` smallint(6) NOT NULL default '0',
  `luk` smallint(6) NOT NULL default '0',
  `max_hp` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `max_sp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `status_point` smallint(6) NOT NULL default '0',
  `skill_point` smallint(6) NOT NULL default '0',
  `option` int(11) unsigned NOT NULL default '0',
  `karma` smallint(6) NOT NULL default '0',
  `manner` smallint(6) NOT NULL default '0',
  `die_counter` int(11) NOT NULL default '0',
  `party_id` int(11) NOT NULL default '0',
  `guild_id` int(11) NOT NULL default '0',
  `pet_id` int(11) NOT NULL default '0',
  `homun_id` int(11) NOT NULL DEFAULT '0',
  `merc_id` int(11) NOT NULL DEFAULT '0',
  `elem_id` int(11) NOT NULL DEFAULT '0',
  `hair` smallint(6) NOT NULL default '0',
  `hair_color` smallint(6) NOT NULL default '0',
  `clothes_color` smallint(6) NOT NULL default '0',
  `weapon` smallint(6) NOT NULL default '1',
  `shield` smallint(6) NOT NULL default '0',
  `robe` smallint(6) NOT NULL default '0',
  `head_top` smallint(6) NOT NULL default '0',
  `head_mid` smallint(6) NOT NULL default '0',
  `head_bottom` smallint(6) NOT NULL default '0',
  `last_map` varchar(24) NOT NULL default 'new_5-1.gat',
  `last_x` smallint(6) NOT NULL default '53',
  `last_y` smallint(6) NOT NULL default '111',
  `save_map` varchar(24) NOT NULL default 'new_5-1.gat',
  `save_x` smallint(6) NOT NULL default '53',
  `save_y` smallint(6) NOT NULL default '111',
  `partner_id` int(11) NOT NULL default '0',
  `parent_id` int(11) NOT NULL default '0',
  `parent_id2` int(11) NOT NULL default '0',
  `baby_id` int(11) NOT NULL default '0',
  `delete_date` int(11) unsigned NOT NULL default '0',
  `refuse_partyinvite` smallint(6) NOT NULL default '0',
  `show_equip` smallint(6) NOT NULL default '0',
  `font` smallint(6) NOT NULL default '0',
  `style` smallint(6) NOT NULL default '0',
  `sex` tinyint(4) unsigned NOT NULL default '99',
  `allow_call` smallint(6) unsigned NOT NULL default '0',
  `autofeed` smallint(6) unsigned NOT NULL default '0',
  `title_id` int(11) NOT NULL default '0',
  `online` tinyint(4) NOT NULL default '0',
  PRIMARY KEY (`char_id`),
  UNIQUE `account_slot` (`account_id`, `char_num`),
  KEY `party_id` (`party_id`),
  UNIQUE `name` (`name`)
) ENGINE = InnoDB AUTO_INCREMENT=15000;

# Database: Ragnarok
# Table: 'charlog'
# 
CREATE TABLE `charlog` (
  `time` datetime NOT NULL default '2000-01-01 00:00:00',
  `log` TEXT NOT NULL
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'worldreg'
# 
CREATE TABLE `worldreg` (
  `account_id` int(11) NOT NULL default '0',
  `reg` varchar(31) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`, `reg`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'accountreg'
#
CREATE TABLE `accountreg` (
  `account_id` int(11) NOT NULL default '0',
  `reg` varchar(32) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`, `reg`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'globalreg'
#
CREATE TABLE `globalreg` (
  `char_id` int(11) NOT NULL default '0',
  `reg` varchar(32) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `reg`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild'
# 
CREATE TABLE `guild` (
  `guild_id` int(11) NOT NULL default '10000',
  `name` varchar(24) BINARY NOT NULL default '',
  `master` varchar(24) NOT NULL default '',
  `guild_lv` smallint(6) NOT NULL default '0',
  `connect_member` smallint(6) NOT NULL default '0',
  `max_member` smallint(6) NOT NULL default '0',
  `average_lv` smallint(6) unsigned NOT NULL default '0',
  `exp` int(11) NOT NULL default '0',
  `next_exp` int(11) NOT NULL default '0',
  `skill_point` int(11) NOT NULL default '0',
  `mes1` varchar(60) NOT NULL default '',
  `mes2` varchar(120) NOT NULL default '',
  `emblem_len` int(11) NOT NULL default '0',
  `emblem_id` int(11) NOT NULL default '0',
  `emblem_data` blob NOT NULL,
  PRIMARY KEY (`guild_id`),
  UNIQUE `name` (`name`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_alliance'
# 
CREATE TABLE `guild_alliance` (
  `guild_id` int(11) NOT NULL default '0',
  `opposition` int(11) NOT NULL default '0',
  `alliance_id` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  PRIMARY KEY (`guild_id`, `alliance_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_castle'
# 
CREATE TABLE `guild_castle` (
  `castle_id` int(11) NOT NULL default '0',
  `guild_id` int(11) NOT NULL default '0',
  `economy` int(11) NOT NULL default '1',
  `defense` int(11) NOT NULL default '1',
  `triggerE` int(11) NOT NULL default '0',
  `triggerD` int(11) NOT NULL default '0',
  `nextTime` int(11) NOT NULL default '0',
  `payTime` int(11) NOT NULL default '0',
  `createTime` int(11) NOT NULL default '0',
  `visibleC` int(11) NOT NULL default '0',
  `visibleG0` int(11) NOT NULL default '0',
  `visibleG1` int(11) NOT NULL default '0',
  `visibleG2` int(11) NOT NULL default '0',
  `visibleG3` int(11) NOT NULL default '0',
  `visibleG4` int(11) NOT NULL default '0',
  `visibleG5` int(11) NOT NULL default '0',
  `visibleG6` int(11) NOT NULL default '0',
  `visibleG7` int(11) NOT NULL default '0',
  `gHP0` int(11) NOT NULL default '0',
  `ghP1` int(11) NOT NULL default '0',
  `gHP2` int(11) NOT NULL default '0',
  `gHP3` int(11) NOT NULL default '0',
  `gHP4` int(11) NOT NULL default '0',
  `gHP5` int(11) NOT NULL default '0',
  `gHP6` int(11) NOT NULL default '0',
  `gHP7` int(11) NOT NULL default '0',
  PRIMARY KEY (`castle_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_expulsion'
# 
CREATE TABLE `guild_expulsion` (
  `guild_id` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mes` varchar(40) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  KEY `guild_id` (`guild_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_member'
# 
CREATE TABLE `guild_member` (
  `guild_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `hair` smallint(6) NOT NULL default '0',
  `hair_color` smallint(6) NOT NULL default '0',
  `gender` smallint(6) NOT NULL default '0',
  `class` smallint(6) NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  `exp` bigint(20) NOT NULL default '0',
  `exp_payper` int(11) NOT NULL default '0',
  `online` tinyint(4) unsigned NOT NULL default '0',
  `position` smallint(6) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  PRIMARY KEY (`guild_id`, `char_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_position'
# 
CREATE TABLE `guild_position` (
  `guild_id` int(11) NOT NULL default '0',
  `position` smallint(6) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mode` int(11) NOT NULL default '0',
  `exp_mode` int(11) NOT NULL default '0',
  PRIMARY KEY (`guild_id`, `position`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_skill'
# 
CREATE TABLE `guild_skill` (
  `guild_id` int(11) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` int(11) NOT NULL default '0',
  PRIMARY KEY (`guild_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'guild_storage'
# 
CREATE TABLE `guild_storage` (
  `id` int(11) unsigned NOT NULL default '0',
  `guild_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  `private` tinyint(4) unsigned NOT NULL default '0',
  PRIMARY KEY (`guild_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'interlog'
# 
CREATE TABLE `interlog` (
  `time` datetime NOT NULL default '2000-01-01 00:00:00',
  `log` varchar(255) NOT NULL default ''
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'inventory'
# 
CREATE TABLE `inventory` (
  `id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  `private` tinyint(4) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'login'
# 
CREATE TABLE `login` (
  `account_id` int(11) NOT NULL AUTO_INCREMENT,
  `userid` varchar(23) BINARY NOT NULL default '',
  `user_pass` varchar(23) NOT NULL default '',
  `lastlogin` datetime NOT NULL default '2000-01-01 00:00:00',
  `sex` ENUM('M', 'F', 'S') NOT NULL default 'M',
  `logincount` int(11) NOT NULL default '0',
  `email` varchar(39) NOT NULL default '',
  `birthdate` char(6) NOT NULL default '000000',
  `level` smallint(3) NOT NULL default '0',
  `last_ip` varchar(16) NOT NULL default '',
  `state` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`),
  UNIQUE `name` (`userid`)
) ENGINE = InnoDB AUTO_INCREMENT=2000000;

# added standard accounts for servers, VERY INSECURE!!!
# inserted into the table called login which is above

INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`)
VALUES
  ('1', 's1', 'p1', 'S', 'auriga@auriga.com'),
  ('2', 's2', 'p2', 'S', 'auriga@auriga.com'),
  ('3', 's3', 'p3', 'S', 'auriga@auriga.com'),
  ('4', 's4', 'p4', 'S', 'auriga@auriga.com'),
  ('5', 's5', 'p5', 'S', 'auriga@auriga.com');

# Database: Ragnarok
# Table: 'loginlog'
# 
CREATE TABLE `loginlog` (
  `time` datetime NOT NULL default '2000-01-01 00:00:00',
  `log` varchar(255) NOT NULL default ''
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'memo'
# 
CREATE TABLE `memo` (
  `char_id` int(11) NOT NULL default '0',
  `index` int(11) NOT NULL default '0',
  `map` varchar(24) NOT NULL default '',
  `x` smallint(6) NOT NULL default '0',
  `y` smallint(6) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `index`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'party'
# 
CREATE TABLE `party` (
  `party_id` int(11) NOT NULL default '100',
  `name` varchar(24) BINARY NOT NULL default '',
  `exp` tinyint(4) unsigned NOT NULL default '0',
  `item` tinyint(4) unsigned NOT NULL default '0',
  `leader_id` int(11) NOT NULL default '0',
  PRIMARY KEY (`party_id`),
  UNIQUE `name` (`name`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'pet'
# 
CREATE TABLE `pet` (
  `pet_id` int(11) NOT NULL AUTO_INCREMENT,
  `class` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `level` smallint(6) unsigned NOT NULL default '0',
  `egg_id` smallint(6) NOT NULL default '0',
  `equip` smallint(6) NOT NULL default '0',
  `intimate` smallint(6) NOT NULL default '0',
  `hungry` smallint(6) NOT NULL default '0',
  `rename_flag` tinyint(4) NOT NULL default '0',
  `incubate` tinyint(4) NOT NULL default '0',
  PRIMARY KEY (`pet_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'skill'
# 
CREATE TABLE `skill` (
  `char_id` int(11) NOT NULL default '0',
  `id` smallint(6) unsigned NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`,`id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'storage'
# 
CREATE TABLE `storage` (
  `id` int(11) unsigned NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  `private` tinyint(4) unsigned NOT NULL default '0',
  PRIMARY KEY (`account_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'friend'
# 
CREATE TABLE `friend` (
  `char_id` int(11) NOT NULL default '0',
  `friend_account` int(11) NOT NULL default '0',
  `friend_id` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `friend_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'homunculus'
# 
CREATE TABLE `homunculus` (
  `homun_id` int(11) NOT NULL AUTO_INCREMENT,
  `class` smallint(6) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `base_level` smallint(6) unsigned NOT NULL default '1',
  `base_exp` int(11) NOT NULL default '0',
  `max_hp` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `max_sp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `str` smallint(6) NOT NULL default '0',
  `agi` smallint(6) NOT NULL default '0',
  `vit` smallint(6) NOT NULL default '0',
  `int` smallint(6) NOT NULL default '0',
  `dex` smallint(6) NOT NULL default '0',
  `luk` smallint(6) NOT NULL default '0',
  `f_str` smallint(6) NOT NULL default '0',
  `f_agi` smallint(6) NOT NULL default '0',
  `f_vit` smallint(6) NOT NULL default '0',
  `f_int` smallint(6) NOT NULL default '0',
  `f_dex` smallint(6) NOT NULL default '0',
  `f_luk` smallint(6) NOT NULL default '0',
  `status_point` smallint(6) NOT NULL default '0',
  `skill_point` smallint(6) NOT NULL default '0',
  `equip` smallint(6) NOT NULL default '0',
  `intimate` int(11) NOT NULL default '0',
  `hungry` smallint(6) NOT NULL default '0',
  `rename_flag` tinyint(4) NOT NULL default '0',
  `incubate` tinyint(4) NOT NULL default '0',
  PRIMARY KEY (`homun_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'homunculus_skill'
# 
CREATE TABLE `homunculus_skill` (
  `homun_id` int(11) NOT NULL default '0',
  `id` smallint(6) unsigned NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  PRIMARY KEY (`homun_id`, `id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'status_change'
# 
CREATE TABLE `status_change` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `type` smallint(6) NOT NULL default '0',
  `val1` int(11) NOT NULL default '0',
  `val2` int(11) NOT NULL default '0',
  `val3` int(11) NOT NULL default '0',
  `val4` int(11) NOT NULL default '0',
  `tick` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `type`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'mail'
#
CREATE TABLE `mail` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `rates` int(11) unsigned NOT NULL default '0',
  `store` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'mail_data'
#
CREATE TABLE `mail_data` (
  `char_id` int(11) NOT NULL default '0',
  `number` int(11) unsigned NOT NULL default '0',
  `read` int(11) NOT NULL default '0',
  `send_name` varchar(23) NOT NULL default '',
  `receive_name` varchar(23) NOT NULL default '',
  `title` varchar(39) NOT NULL default '',
  `times` int(11) unsigned NOT NULL default '0',
  `size` int(11) unsigned NOT NULL default '0',
  `body` blob NOT NULL,
  `zeny` int(11) NOT NULL default '0',
  `id` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `number`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'mapreg'
#
CREATE TABLE `mapreg` (
  `server_tag` varchar(16) NOT NULL default '',
  `reg` varchar(255) NOT NULL default '',
  `index` smallint(6) NOT NULL default '0',
  `value` text NOT NULL,
  PRIMARY KEY (`server_tag`, `reg`, `index`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'feel_info'
#
CREATE TABLE `feel_info` (
  `char_id` int(11) NOT NULL default '0',
  `map` varchar(24) NOT NULL default '',
  `lv` smallint(6) NOT NULL default '-1',
  PRIMARY KEY (`char_id`, `lv`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'hotkey'
#
CREATE TABLE `hotkey` (
  `char_id` int(11) NOT NULL default '0',
  `key` int(11) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `key`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'mercenary'
#
CREATE TABLE `mercenary` (
  `merc_id` int(11) NOT NULL AUTO_INCREMENT,
  `class` smallint(6) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `kill_count` int(11) NOT NULL DEFAULT '0',
  `limit` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY (`merc_id`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'mercenary_employ'
#
CREATE TABLE `mercenary_employ` (
  `char_id` int(11) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `fame` int(11) NOT NULL DEFAULT '0',
  `call` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`char_id`, `type`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'quest'
#
CREATE TABLE `quest` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `state` tinyint(4) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  `mobid1` smallint(6) NOT NULL default '0',
  `mobmax1` smallint(6) NOT NULL default '0',
  `mobcnt1` smallint(6) NOT NULL default '0',
  `mobid2` smallint(6) NOT NULL default '0',
  `mobmax2` smallint(6) NOT NULL default '0',
  `mobcnt2` smallint(6) NOT NULL default '0',
  `mobid3` smallint(6) NOT NULL default '0',
  `mobmax3` smallint(6) NOT NULL default '0',
  `mobcnt3` smallint(6) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `nameid`)
) ENGINE = InnoDB;

# Database: Ragnarok
# Table: 'elemental'
#
CREATE TABLE `elemental` (
  `elem_id` int(11) NOT NULL AUTO_INCREMENT,
  `class` smallint(6) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `mode` smallint(6) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY (`elem_id`)
) ENGINE = InnoDB;
