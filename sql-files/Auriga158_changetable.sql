# separate feel_info from memo table

# Database: Ragnarok
# Table: 'feel_info'
#
CREATE TABLE `feel_info` (
  `feel_id` int(11) NOT NULL auto_increment,
  `char_id` int(11) NOT NULL default '0',
  `map` varchar(24) NOT NULL default '',
  `lv` mediumint(9) NOT NULL default '-1',
  PRIMARY KEY (`feel_id`)
) TYPE=MyISAM;

# convert data
INSERT INTO `feel_info` (`char_id`,`map`,`lv`) SELECT `char_id`,`map`,`x` FROM `memo` WHERE `type` = 'F';
DELETE FROM `memo` WHERE `type` = 'F';

# change memo table
ALTER TABLE `memo` DROP `type`;
ALTER TABLE `memo` MODIFY `x` mediumint(9) NOT NULL default '0';
ALTER TABLE `memo` MODIFY `y` mediumint(9) NOT NULL default '0';
