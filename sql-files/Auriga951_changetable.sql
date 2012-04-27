# add `char_data` table structure
ALTER TABLE `char_data` ADD `elem_id` int(11) NOT NULL DEFAULT '0' AFTER `merc_id`;

# create new table `elemental`
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
