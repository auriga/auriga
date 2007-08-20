# create new table hotkey

CREATE TABLE `hotkey` (
  `char_id` int(11) NOT NULL default '0',
  `key` int(11) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `key`)
) TYPE=MyISAM;
