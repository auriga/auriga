
ALTER TABLE `char` ADD INDEX ( `account_id` )
ALTER TABLE `char` ADD INDEX ( `name` )

# Database: Ragnarok
# Table: 'homunculus_skill'
# 

CREATE TABLE `homunculus_skill` (
  `homun_id` int(11) NOT NULL default '0',
  `id` int(11) NOT NULL default '0',
  `lv` int(11) NOT NULL default '0',
  KEY `homun_id` (`homun_id`)
) TYPE=MyISAM; 

