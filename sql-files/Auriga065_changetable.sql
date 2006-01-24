# create new table mapreg

CREATE TABLE `mapreg` (
  `server_tag` varchar(16) NOT NULL default '',
  `reg` varchar(255) NOT NULL default '',
  `index` smallint(6) NOT NULL default '0',
  `value` text NOT NULL,
  PRIMARY KEY (`server_tag`, `reg`, `index`),
  KEY `reg` (`reg`),
  KEY `index` (`index`)
) TYPE=MyISAM;
