# drop unused tables
DROP TABLE IF EXISTS `login_error`;
DROP TABLE IF EXISTS `ragsrvinfo`;
DROP TABLE IF EXISTS `sstatus`;


# create new table for RO mail system

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
