# add memo type
ALTER TABLE `memo` ADD `type` char(1) NOT NULL DEFAULT '' AFTER `char_id` ;
ALTER TABLE `memo` CHANGE `x` `x` mediumint(9) NOT NULL default '-1' ;
ALTER TABLE `memo` CHANGE `y` `y` mediumint(9) NOT NULL default '-1' ;
