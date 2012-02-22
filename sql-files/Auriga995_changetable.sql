# add `cart_inventory` table structure
ALTER TABLE `cart_inventory` ADD `private` tinyint(4) unsigned NOT NULL default '0' AFTER `limit`;

# add `guild_storage` table structure
ALTER TABLE `guild_storage` ADD `private` tinyint(4) unsigned NOT NULL default '0' AFTER `limit`;

# add `inventory` table structure
ALTER TABLE `inventory` ADD `private` tinyint(4) unsigned NOT NULL default '0' AFTER `limit`;

# add `storage` table structure
ALTER TABLE `storage` ADD `private` tinyint(4) unsigned NOT NULL default '0' AFTER `limit`;
