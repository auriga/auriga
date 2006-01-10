# fix field of option in char table
ALTER TABLE `char` CHANGE `option` `option` int(11) unsigned NOT NULL default '0';

# drop unused fields
ALTER TABLE `cart_inventory` DROP `broken`;
ALTER TABLE `guild_storage` DROP `broken`;
ALTER TABLE `inventory` DROP `broken`;
ALTER TABLE `storage` DROP `broken`;
ALTER TABLE `login` DROP `error_message`, DROP `connect_until`, DROP `memo`, DROP `ban_until`;
ALTER TABLE `loginlog` DROP `ip`, DROP `user`, DROP `rcode`;
