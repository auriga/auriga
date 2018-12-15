# add `char_data` table structure
ALTER TABLE `char_data` ADD `sex` tinyint(4) unsigned NOT NULL DEFAULT '99' AFTER `style`;
