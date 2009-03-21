# drop mercenary data field

ALTER TABLE `char_data` DROP `merc_fame1`;
ALTER TABLE `char_data` DROP `merc_call1`;
ALTER TABLE `char_data` DROP `merc_fame2`;
ALTER TABLE `char_data` DROP `merc_call2`;
ALTER TABLE `char_data` DROP `merc_fame3`;
ALTER TABLE `char_data` DROP `merc_call3`;

# create new table mercenary

CREATE TABLE `mercenary` (
  `char_id` int(11) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `fame` int(11) NOT NULL DEFAULT '0',
  `call` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`char_id`, `type`)
) TYPE = MyISAM;
