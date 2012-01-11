# add `char_data` table structure
ALTER TABLE `char_data` ADD `font` smallint(6) NOT NULL DEFAULT '0' AFTER `show_equip`;
