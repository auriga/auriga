# Database: Ragnarok
# Table: 'cart_inventory'
# 
CREATE TABLE `cart_inventory` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `char_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `char_id` (`char_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'char'
# 
CREATE TABLE `char` (
  `char_id` int(11) NOT NULL auto_increment,
  `account_id` int(11) NOT NULL default '0',
  `char_num` tinyint(4) NOT NULL default '0',
  `name` varchar(255) NOT NULL default '',
  `class` int(11) NOT NULL default '0',
  `base_level` bigint(20) unsigned NOT NULL default '1',
  `job_level` bigint(20) unsigned NOT NULL default '1',
  `base_exp` bigint(20) NOT NULL default '0',
  `job_exp` bigint(20) NOT NULL default '0',
  `zeny` int(11) NOT NULL default '500',
  `str` int(11) unsigned NOT NULL default '0',
  `agi` int(11) unsigned NOT NULL default '0',
  `vit` int(11) unsigned NOT NULL default '0',
  `int` int(11) unsigned NOT NULL default '0',
  `dex` int(11) unsigned NOT NULL default '0',
  `luk` int(11) unsigned NOT NULL default '0',
  `max_hp` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `max_sp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `status_point` int(11) NOT NULL default '0',
  `skill_point` int(11) NOT NULL default '0',
  `option` int(11) unsigned NOT NULL default '0',
  `karma` int(11) NOT NULL default '0',
  `manner` int(11) NOT NULL default '0',
  `die_counter` int(11) NOT NULL default '0',
  `party_id` int(11) NOT NULL default '0',
  `guild_id` int(11) NOT NULL default '0',
  `pet_id` int(11) NOT NULL default '0',
  `hair` tinyint(4) NOT NULL default '0',
  `hair_color` int(11) NOT NULL default '0',
  `clothes_color` tinyint(4) NOT NULL default '0',
  `weapon` int(11) NOT NULL default '1',
  `shield` int(11) NOT NULL default '0',
  `head_top` int(11) NOT NULL default '0',
  `head_mid` int(11) NOT NULL default '0',
  `head_bottom` int(11) NOT NULL default '0',
  `last_map` varchar(20) NOT NULL default 'new_5-1.gat',
  `last_x` int(4) NOT NULL default '53',
  `last_y` int(11) NOT NULL default '111',
  `save_map` varchar(20) NOT NULL default 'new_5-1.gat',
  `save_x` int(11) NOT NULL default '53',
  `save_y` int(11) NOT NULL default '111',
  `partner_id` int(11) NOT NULL default '0',
  `parent_id` int(11) NOT NULL default '0',
  `parent_id2` int(11) NOT NULL default '0',
  `baby_id` int(11) NOT NULL default '0',
  `online` tinyint(4) NOT NULL default '0',
  `homun_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY  (`char_id`),
  KEY `account_id` (`account_id`),
  KEY `party_id` (`party_id`),
  KEY `guild_id` (`guild_id`),
  KEY `name` (`name`)
) TYPE=MyISAM AUTO_INCREMENT=15000; 

# Database: Ragnarok
# Table: 'charlog'
# 
CREATE TABLE `charlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `log` TEXT NOT NULL
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'global_reg_value'
# 
CREATE TABLE `global_reg_value` (
  `char_id` int(11) NOT NULL default '0',
  `str` varchar(255) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  `type` int(11) NOT NULL default '3',
  `account_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`str`,`account_id`),
  KEY `account_id` (`account_id`),
  KEY `char_id` (`char_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild'
# 
CREATE TABLE `guild` (
  `guild_id` int(11) NOT NULL default '10000',
  `name` varchar(24) NOT NULL default '',
  `master` varchar(24) NOT NULL default '',
  `guild_lv` smallint(6) NOT NULL default '0',
  `connect_member` smallint(6) NOT NULL default '0',
  `max_member` smallint(6) NOT NULL default '0',
  `average_lv` smallint(6) NOT NULL default '0',
  `exp` int(11) NOT NULL default '0',
  `next_exp` int(11) NOT NULL default '0',
  `skill_point` int(11) NOT NULL default '0',
  `castle_id` int(11) NOT NULL default '-1',
  `mes1` varchar(60) NOT NULL default '',
  `mes2` varchar(120) NOT NULL default '',
  `emblem_len` int(11) NOT NULL default '0',
  `emblem_id` int(11) NOT NULL default '0',
  `emblem_data` blob NOT NULL,
  PRIMARY KEY  (`guild_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild_alliance'
# 
CREATE TABLE `guild_alliance` (
  `guild_id` int(11) NOT NULL default '0',
  `opposition` int(11) NOT NULL default '0',
  `alliance_id` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild_castle'
# 
CREATE TABLE `guild_castle` (
  `castle_id` int(11) NOT NULL default '0',
  `guild_id` int(11) NOT NULL default '0',
  `economy` int(11) NOT NULL default '0',
  `defense` int(11) NOT NULL default '0',
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
  PRIMARY KEY  (`castle_id`),
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('2','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('3','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('7','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('11','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('12','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('13','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('14','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('15','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('16','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('17','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('18','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
INSERT INTO `guild_castle` (`castle_id`,`guild_id`,`economy`,`defense`,`triggerE`,`triggerD`,`nextTime`,`payTime`,`createTime`,`visibleC`,`visibleG0`,`visibleG1`,`visibleG2`,`visibleG3`,`visibleG4`,`visibleG5`,`visibleG6`,`visibleG7`)
VALUES ('19','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');

# Database: Ragnarok
# Table: 'guild_expulsion'
# 
CREATE TABLE `guild_expulsion` (
  `guild_id` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mes` varchar(40) NOT NULL default '',
  `acc` varchar(40) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  `rsv1` int(11) NOT NULL default '0',
  `rsv2` int(11) NOT NULL default '0',
  `rsv3` int(11) NOT NULL default '0',
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

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
  `lv` smallint(6) NOT NULL default '0',
  `exp` bigint(20) NOT NULL default '0',
  `exp_payper` int(11) NOT NULL default '0',
  `online` tinyint(4) NOT NULL default '0',
  `position` smallint(6) NOT NULL default '0',
  `rsv1` int(11) NOT NULL default '0',
  `rsv2` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  KEY `guild_id` (`guild_id`),
  KEY `account_id` (`account_id`),
  KEY `char_id` (`char_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild_position'
# 
CREATE TABLE `guild_position` (
  `guild_id` int(11) NOT NULL default '0',
  `position` smallint(6) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mode` int(11) NOT NULL default '0',
  `exp_mode` int(11) NOT NULL default '0',
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild_skill'
# 
CREATE TABLE `guild_skill` (
  `guild_id` int(11) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` int(11) NOT NULL default '0',
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'guild_storage'
# 
CREATE TABLE `guild_storage` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `guild_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `guild_id` (`guild_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'interlog'
# 
CREATE TABLE `interlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `log` varchar(255) NOT NULL default ''
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'inventory'
# 
CREATE TABLE `inventory` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `char_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `char_id` (`char_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'ipbanlist'
# 
CREATE TABLE `ipbanlist` (
  `list` varchar(255) NOT NULL default '',
  `btime` datetime NOT NULL default '0000-00-00 00:00:00',
  `rtime` datetime NOT NULL default '0000-00-00 00:00:00',
  `reason` varchar(255) NOT NULL default ''
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'login'
# 
CREATE TABLE `login` (
  `account_id` int(11) NOT NULL AUTO_INCREMENT,
  `userid` varchar(255) NOT NULL default '',
  `user_pass` varchar(32) NOT NULL default '',
  `lastlogin` datetime NOT NULL default '0000-00-00 00:00:00',
  `sex` char(1) NOT NULL default 'M',
  `logincount` mediumint(9) NOT NULL default '0',
  `email` varchar(60) NOT NULL default '',
  `level` smallint(3) NOT NULL default '0',
  `last_ip` varchar(100) NOT NULL default '',
  `state` int(11) NOT NULL default '0',
  PRIMARY KEY  (`account_id`),
  KEY `name` (`userid`)
) TYPE=MyISAM AUTO_INCREMENT=2000000; 

# added standard accounts for servers, VERY INSECURE!!!
# inserted into the table called login which is above

INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('1', 's1', 'p1', 'S','athena@athena.com');
INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('2', 's2', 'p2', 'S','athena@athena.com');
INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('3', 's3', 'p3', 'S','athena@athena.com');
INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('4', 's4', 'p4', 'S','athena@athena.com');
INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('5', 's5', 'p5', 'S','athena@athena.com');

# Database: Ragnarok
# Table: 'loginlog'
# 
CREATE TABLE `loginlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `log` varchar(255) NOT NULL default ''
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'memo'
# 
CREATE TABLE `memo` (
  `memo_id` int(11) NOT NULL auto_increment,
  `char_id` int(11) NOT NULL default '0',
  `type` char(1) NOT NULL default '',
  `map` varchar(255) NOT NULL default '',
  `x` mediumint(9) NOT NULL default '-1',
  `y` mediumint(9) NOT NULL default '-1',
  PRIMARY KEY  (`memo_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'party'
# 
CREATE TABLE `party` (
  `party_id` int(11) NOT NULL default '100',
  `name` char(100) NOT NULL default '',
  `exp` int(11) NOT NULL default '0',
  `item` int(11) NOT NULL default '0',
  `leader_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`party_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'pet'
# 
CREATE TABLE `pet` (
  `pet_id` int(11) NOT NULL auto_increment,
  `class` mediumint(9) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `level` tinyint(4) NOT NULL default '0',
  `egg_id` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `intimate` mediumint(9) NOT NULL default '0',
  `hungry` mediumint(9) NOT NULL default '0',
  `rename_flag` tinyint(4) NOT NULL default '0',
  `incubate` int(11) NOT NULL default '0',
  PRIMARY KEY  (`pet_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'skill'
# 
CREATE TABLE `skill` (
  `char_id` int(11) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`id`),
  KEY `char_id` (`char_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'storage'
# 
CREATE TABLE `storage` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `account_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `account_id` (`account_id`)
) TYPE=MyISAM; 

# Database: Ragnarok
# Table: 'friend'
# 
CREATE TABLE friend (
  `char_id` int(11) NOT NULL default '0',
  `id1` int(11) NOT NULL default '0',
  `id2` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  KEY `char_id` (`char_id`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'homunculus'
# 
CREATE TABLE `homunculus` (
  `homun_id` int(11) NOT NULL auto_increment,
  `class` mediumint(9) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `base_level` tinyint(4) NOT NULL default '0',
  `base_exp` bigint(20) NOT NULL default '0',
  `max_hp` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `max_sp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `str` int(11) unsigned NOT NULL default '0',
  `agi` int(11) unsigned NOT NULL default '0',
  `vit` int(11) unsigned NOT NULL default '0',
  `int` int(11) unsigned NOT NULL default '0',
  `dex` int(11) unsigned NOT NULL default '0',
  `luk` int(11) unsigned NOT NULL default '0',
  `status_point` int(11) NOT NULL default '0',
  `skill_point` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `intimate` mediumint(9) NOT NULL default '0',
  `hungry` mediumint(9) NOT NULL default '0',
  `rename_flag` tinyint(4) NOT NULL default '0',
  `incubate` int(11) NOT NULL default '0',
  PRIMARY KEY  (`homun_id`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'homunculus_skill'
# 
CREATE TABLE `homunculus_skill` (
  `homun_id` int(11) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` int(11) NOT NULL default '0',
  KEY `homun_id` (`homun_id`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'status_change'
# 
CREATE TABLE `status_change` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `type` mediumint(9) NOT NULL default '0',
  `val1` int(11) NOT NULL default '0',
  `val2` int(11) NOT NULL default '0',
  `val3` int(11) NOT NULL default '0',
  `val4` int(11) NOT NULL default '0',
  `tick` int(11) NOT NULL default '0',
  KEY `char_id` (`char_id`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'mail'
#
CREATE TABLE `mail` (
  `char_id` int(11) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `rates` int(11) unsigned NOT NULL default '0',
  `store` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'mail_data'
#
CREATE TABLE `mail_data` (
  `char_id` int(11) NOT NULL default '0',
  `number` int(11) unsigned NOT NULL default '0',
  `read` int(11) NOT NULL default '0',
  `send_name` varchar(48) NOT NULL default '',
  `receive_name` varchar(48) NOT NULL default '',
  `title` varchar(80) NOT NULL default '',
  `times` int(11) unsigned NOT NULL default '0',
  `size` int(11) unsigned NOT NULL default '0',
  `body` blob NOT NULL,
  `zeny` int(11) NOT NULL default '0',
  `id` bigint(20) unsigned NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`,`number`),
  KEY `char_id` (`char_id`),
  KEY `number` (`number`)
) TYPE=MyISAM;

# Database: Ragnarok
# Table: 'mapreg'
#
CREATE TABLE `mapreg` (
  `server_tag` varchar(16) NOT NULL default '',
  `reg` varchar(255) NOT NULL default '',
  `index` smallint(6) NOT NULL default '0',
  `value` text NOT NULL,
  PRIMARY KEY (`server_tag`, `reg`, `index`),
  KEY `reg` (`reg`),
  KEY `index` (`index`)
) TYPE=MyISAM;
