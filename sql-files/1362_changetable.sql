# drop old table
DROP TABLE IF EXISTS friends;

# create new table
CREATE TABLE friend (
  `char_id` int(11) NOT NULL default '0',
  `id1` int(11) NOT NULL default '0',
  `id2` int(11) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  KEY `char_id` (`char_id`)
) TYPE=MyISAM;
