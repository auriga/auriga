# fix `cart_inventory` table structure
ALTER TABLE `cart_inventory` MODIFY `equip` int(11) unsigned NOT NULL default '0';

# fix `guild_storage` table structure
ALTER TABLE `guild_storage` MODIFY `equip` int(11) unsigned NOT NULL default '0';

# fix `inventory` table structure
ALTER TABLE `inventory` MODIFY `equip` int(11) unsigned NOT NULL default '0';

# fix `storage` table structure
ALTER TABLE `storage` MODIFY `equip` int(11) unsigned NOT NULL default '0';

# fix `mail_data` table structure
ALTER TABLE `mail_data` MODIFY `equip` int(11) unsigned NOT NULL default '0';
