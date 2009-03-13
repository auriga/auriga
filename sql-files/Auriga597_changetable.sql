# add mercenary data field
ALTER TABLE `char_data` ADD `merc_fame1` int(11) NOT NULL default '0' AFTER `merc_id`;
ALTER TABLE `char_data` ADD `merc_call1` int(11) NOT NULL default '0' AFTER `merc_fame1`;
ALTER TABLE `char_data` ADD `merc_fame2` int(11) NOT NULL default '0' AFTER `merc_call1`;
ALTER TABLE `char_data` ADD `merc_call2` int(11) NOT NULL default '0' AFTER `merc_fame2`;
ALTER TABLE `char_data` ADD `merc_fame3` int(11) NOT NULL default '0' AFTER `merc_call2`;
ALTER TABLE `char_data` ADD `merc_call3` int(11) NOT NULL default '0' AFTER `merc_fame3`;
