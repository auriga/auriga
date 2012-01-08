# add `char_data` table structure
ALTER TABLE `char_data` ADD `costume_robe` smallint(6) NOT NULL DEFAULT '0' AFTER `costume_head_bottom`;
ALTER TABLE `char_data` ADD `costume_floor` smallint(6) NOT NULL DEFAULT '0' AFTER `costume_robe`;
