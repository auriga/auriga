# add birthdate
ALTER TABLE `login` ADD `birthdate` char(6) NOT NULL default '000000' AFTER `email`;

# change `login` table structure
ALTER TABLE `login` CHANGE `sex` `sex` ENUM( 'M', 'F', 'S' ) NOT NULL default 'M';

# fix some field length
ALTER TABLE `login` MODIFY `userid` varchar(23) BINARY NOT NULL default '';
ALTER TABLE `login` MODIFY `user_pass` varchar(23) NOT NULL default '';
ALTER TABLE `login` MODIFY `email` varchar(39) NOT NULL default '';
ALTER TABLE `worldreg` MODIFY `reg` varchar(31) NOT NULL default '';

# add `char_data` table structure
ALTER TABLE `char_data` ADD `costume_head_top` smallint(6) NOT NULL DEFAULT '0' AFTER `head_bottom`;
ALTER TABLE `char_data` ADD `costume_head_mid` smallint(6) NOT NULL DEFAULT '0' AFTER `costume_head_top`;
ALTER TABLE `char_data` ADD `costume_head_bottom` smallint(6) NOT NULL DEFAULT '0' AFTER `costume_head_mid`;
ALTER TABLE `char_data` ADD `delete_date` int(11) unsigned NOT NULL DEFAULT '0' AFTER `baby_id`;
