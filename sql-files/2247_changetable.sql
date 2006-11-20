# create new table status_change
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
