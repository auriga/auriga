# create new table quest

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
) TYPE=MyISAM;
