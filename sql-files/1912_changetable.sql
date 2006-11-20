ALTER TABLE `homunculus` DROP `base_exp`;
ALTER TABLE `homunculus` ADD `base_exp` BIGINT( 20 ) NOT NULL DEFAULT '0' AFTER `base_level` ;
