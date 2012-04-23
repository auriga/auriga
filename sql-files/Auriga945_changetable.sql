# rename `mercenary` to `mercenary_employ`
ALTER TABLE `mercenary` RENAME TO `mercenary_employ`;

# fix `mercenary` table structure
CREATE TABLE `mercenary` (
  `merc_id` int(11) NOT NULL AUTO_INCREMENT,
  `class` smallint(6) NOT NULL default '0',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `hp` int(11) NOT NULL default '0',
  `sp` int(11) NOT NULL default '0',
  `kill_count` int(11) NOT NULL DEFAULT '0',
  `limit` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY (`merc_id`)
) ENGINE = InnoDB;
