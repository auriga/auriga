# add `char_data` table structure
ALTER TABLE `char_data` ADD `allow_call` smallint(6) unsigned NOT NULL DEFAULT '0' AFTER `sex`;
ALTER TABLE `char_data` ADD `autofeed` smallint(6) unsigned NOT NULL DEFAULT '0' AFTER `allow_call`;
