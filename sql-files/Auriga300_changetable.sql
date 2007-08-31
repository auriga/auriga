# add limit field
ALTER TABLE `cart_inventory` ADD `limit` int(11) unsigned NOT NULL default '0' AFTER `card3`;
ALTER TABLE `guild_storage` ADD `limit` int(11) unsigned NOT NULL default '0' AFTER `card3`;
ALTER TABLE `inventory` ADD `limit` int(11) unsigned NOT NULL default '0' AFTER `card3`;
ALTER TABLE `mail_data` ADD `limit` int(11) unsigned NOT NULL default '0' AFTER `card3`;
ALTER TABLE `storage` ADD `limit` int(11) unsigned NOT NULL default '0' AFTER `card3`;
