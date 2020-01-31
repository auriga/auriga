# fix `cart_inventory` table structure
ALTER TABLE `cart_inventory` MODIFY `nameid` int(11) NOT NULL default '0';

# fix `char_data` table structure
ALTER TABLE `char_data` MODIFY `base_exp` bigint(20) NOT NULL default '0';

# fix `char_data` table structure
ALTER TABLE `char_data` MODIFY `job_exp` bigint(20) NOT NULL default '0';

# fix `guild_storage` table structure
ALTER TABLE `guild_storage` MODIFY `nameid` int(11) NOT NULL default '0';

# fix `inventory` table structure
ALTER TABLE `inventory` MODIFY `nameid` int(11) NOT NULL default '0';

# fix `pet` table structure
ALTER TABLE `pet` MODIFY `class` int(11) NOT NULL default '0';

# fix `storage` table structure
ALTER TABLE `storage` MODIFY `nameid` int(11) NOT NULL default '0';

# fix `mail_data` table structure
ALTER TABLE `mail_data` MODIFY `nameid` int(11) NOT NULL default '0';

# add `mail_data` table structure
ALTER TABLE `mail_data` ADD `opt0id` smallint(6) NOT NULL DEFAULT '0' AFTER `card3`;
ALTER TABLE `mail_data` ADD `opt0val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0id`;
ALTER TABLE `mail_data` ADD `opt1id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0val`;
ALTER TABLE `mail_data` ADD `opt1val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1id`;
ALTER TABLE `mail_data` ADD `opt2id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1val`;
ALTER TABLE `mail_data` ADD `opt2val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2id`;
ALTER TABLE `mail_data` ADD `opt3id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2val`;
ALTER TABLE `mail_data` ADD `opt3val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3id`;
ALTER TABLE `mail_data` ADD `opt4id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3val`;
ALTER TABLE `mail_data` ADD `opt4val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt4id`;
