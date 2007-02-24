# first, delete auto increment and change type from bigint to int
ALTER TABLE `cart_inventory` MODIFY `id` int(11) unsigned NOT NULL default '0';
ALTER TABLE `guild_storage` MODIFY `id` int(11) unsigned NOT NULL default '0';
ALTER TABLE `inventory` MODIFY `id` int(11) unsigned NOT NULL default '0';
ALTER TABLE `storage` MODIFY `id` int(11) unsigned NOT NULL default '0';

# second, drop primary key
ALTER TABLE `cart_inventory` DROP PRIMARY KEY;
ALTER TABLE `guild_storage` DROP PRIMARY KEY;
ALTER TABLE `inventory` DROP PRIMARY KEY;
ALTER TABLE `storage` DROP PRIMARY KEY;

# third, set new primary key
ALTER TABLE `cart_inventory` ADD PRIMARY KEY (`id`, `char_id`);
ALTER TABLE `guild_storage` ADD PRIMARY KEY (`id`, `guild_id`);
ALTER TABLE `inventory` ADD PRIMARY KEY (`id`, `char_id`);
ALTER TABLE `storage` ADD PRIMARY KEY (`id`, `account_id`);
