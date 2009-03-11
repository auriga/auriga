# add grown status field
ALTER TABLE `homunculus` ADD `f_str` smallint(6) NOT NULL default '0' AFTER `luk`;
ALTER TABLE `homunculus` ADD `f_agi` smallint(6) NOT NULL default '0' AFTER `f_str`;
ALTER TABLE `homunculus` ADD `f_vit` smallint(6) NOT NULL default '0' AFTER `f_agi`;
ALTER TABLE `homunculus` ADD `f_int` smallint(6) NOT NULL default '0' AFTER `f_vit`;
ALTER TABLE `homunculus` ADD `f_dex` smallint(6) NOT NULL default '0' AFTER `f_int`;
ALTER TABLE `homunculus` ADD `f_luk` smallint(6) NOT NULL default '0' AFTER `f_dex`;
