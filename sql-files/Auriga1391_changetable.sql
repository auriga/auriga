# add `char_data` table structure
ALTER TABLE `char_data` ADD `title_id` int(11) NOT NULL DEFAULT '0' AFTER `autofeed`;

# create new table `achieve`
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
