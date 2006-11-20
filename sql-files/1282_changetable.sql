#
ALTER TABLE `charlog` DROP `char_msg` ,
DROP `account_id` ,
DROP `char_num` ,
DROP `name` ,
DROP `str` ,
DROP `agi` ,
DROP `vit` ,
DROP `int` ,
DROP `dex` ,
DROP `luk` ,
DROP `hair` ,
DROP `hair_color` ;

#
ALTER TABLE `charlog` ADD `log` TEXT NOT NULL AFTER `time` ;
