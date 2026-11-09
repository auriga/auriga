# add `char_data` table structure to `inventory_slots` for Inventory Expansion
ALTER TABLE `char_data` ADD `inventory_slots` smallint(6) unsigned NOT NULL default '100' AFTER `title_id`;
