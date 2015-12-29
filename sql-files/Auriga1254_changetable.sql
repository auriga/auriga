# add `cart_inventory` table structure
ALTER TABLE `cart_inventory` ADD `opt0id` smallint(6) NOT NULL DEFAULT '0' AFTER `card3`;
ALTER TABLE `cart_inventory` ADD `opt0val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0id`;
ALTER TABLE `cart_inventory` ADD `opt1id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0val`;
ALTER TABLE `cart_inventory` ADD `opt1val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1id`;
ALTER TABLE `cart_inventory` ADD `opt2id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1val`;
ALTER TABLE `cart_inventory` ADD `opt2val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2id`;
ALTER TABLE `cart_inventory` ADD `opt3id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2val`;
ALTER TABLE `cart_inventory` ADD `opt3val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3id`;
ALTER TABLE `cart_inventory` ADD `opt4id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3val`;
ALTER TABLE `cart_inventory` ADD `opt4val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt4id`;

# add `guild_storage` table structure
ALTER TABLE `guild_storage` ADD `opt0id` smallint(6) NOT NULL DEFAULT '0' AFTER `card3`;
ALTER TABLE `guild_storage` ADD `opt0val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0id`;
ALTER TABLE `guild_storage` ADD `opt1id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0val`;
ALTER TABLE `guild_storage` ADD `opt1val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1id`;
ALTER TABLE `guild_storage` ADD `opt2id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1val`;
ALTER TABLE `guild_storage` ADD `opt2val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2id`;
ALTER TABLE `guild_storage` ADD `opt3id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2val`;
ALTER TABLE `guild_storage` ADD `opt3val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3id`;
ALTER TABLE `guild_storage` ADD `opt4id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3val`;
ALTER TABLE `guild_storage` ADD `opt4val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt4id`;

# add `inventory` table structure
ALTER TABLE `inventory` ADD `opt0id` smallint(6) NOT NULL DEFAULT '0' AFTER `card3`;
ALTER TABLE `inventory` ADD `opt0val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0id`;
ALTER TABLE `inventory` ADD `opt1id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0val`;
ALTER TABLE `inventory` ADD `opt1val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1id`;
ALTER TABLE `inventory` ADD `opt2id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1val`;
ALTER TABLE `inventory` ADD `opt2val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2id`;
ALTER TABLE `inventory` ADD `opt3id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2val`;
ALTER TABLE `inventory` ADD `opt3val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3id`;
ALTER TABLE `inventory` ADD `opt4id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3val`;
ALTER TABLE `inventory` ADD `opt4val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt4id`;

# add `storage` table structure
ALTER TABLE `storage` ADD `opt0id` smallint(6) NOT NULL DEFAULT '0' AFTER `card3`;
ALTER TABLE `storage` ADD `opt0val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0id`;
ALTER TABLE `storage` ADD `opt1id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt0val`;
ALTER TABLE `storage` ADD `opt1val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1id`;
ALTER TABLE `storage` ADD `opt2id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt1val`;
ALTER TABLE `storage` ADD `opt2val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2id`;
ALTER TABLE `storage` ADD `opt3id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt2val`;
ALTER TABLE `storage` ADD `opt3val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3id`;
ALTER TABLE `storage` ADD `opt4id` smallint(6) NOT NULL DEFAULT '0' AFTER `opt3val`;
ALTER TABLE `storage` ADD `opt4val` smallint(6) NOT NULL DEFAULT '0' AFTER `opt4id`;

# add `char_data` table structure
ALTER TABLE `char_data` ADD `style` smallint(6) NOT NULL DEFAULT '0' AFTER `font`;
