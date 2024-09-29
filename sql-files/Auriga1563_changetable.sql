# add `char_data` table structure
ALTER TABLE `char_data` ADD `pow` smallint(6) NOT NULL DEFAULT '0' AFTER `luk`;
ALTER TABLE `char_data` ADD `sta` smallint(6) NOT NULL DEFAULT '0' AFTER `pow`;
ALTER TABLE `char_data` ADD `wis` smallint(6) NOT NULL DEFAULT '0' AFTER `sta`;
ALTER TABLE `char_data` ADD `spl` smallint(6) NOT NULL DEFAULT '0' AFTER `wis`;
ALTER TABLE `char_data` ADD `con` smallint(6) NOT NULL DEFAULT '0' AFTER `spl`;
ALTER TABLE `char_data` ADD `crt` smallint(6) NOT NULL DEFAULT '0' AFTER `con`;
ALTER TABLE `char_data` ADD `max_ap` int(11) NOT NULL DEFAULT '0' AFTER `sp`;
ALTER TABLE `char_data` ADD `ap` int(11) NOT NULL DEFAULT '0' AFTER `max_ap`;
ALTER TABLE `char_data` ADD `tstatus_point` smallint(6) NOT NULL DEFAULT '0' AFTER `status_point`;
