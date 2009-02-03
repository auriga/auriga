# rename
ALTER TABLE `char` RENAME TO `char_data`;
ALTER TABLE `friend` CHANGE `id1` `friend_account` int(11) NOT NULL default '0';
ALTER TABLE `friend` CHANGE `id2` `friend_id` int(11) NOT NULL default '0';

# change `memo` table structure
ALTER TABLE `memo` ADD `index` int(11) NOT NULL default '0' AFTER `char_id`;
UPDATE `memo` SET `index` = `memo_id`;

ALTER TABLE `memo` ADD KEY `memo_id` (`memo_id`);
ALTER TABLE `memo` DROP PRIMARY KEY;
ALTER TABLE `memo` DROP `memo_id`;
ALTER TABLE `memo` ADD PRIMARY KEY (`char_id`, `index`);

# change `feel_info` table structure
ALTER TABLE `feel_info` ADD KEY `feel_id` (`feel_id`);
ALTER TABLE `feel_info` DROP PRIMARY KEY;
ALTER TABLE `feel_info` DROP `feel_id`;
ALTER TABLE `feel_info` ADD PRIMARY KEY (`char_id`, `lv`);

# drop unused index
ALTER TABLE `cart_inventory` DROP KEY `char_id`;
ALTER TABLE `guild_castle` DROP KEY `guild_id`;
ALTER TABLE `guild_member` DROP KEY `account_id`;
ALTER TABLE `guild_member` DROP KEY `char_id`;
ALTER TABLE `guild_storage` DROP KEY `guild_id`;
ALTER TABLE `inventory` DROP KEY `char_id`;
ALTER TABLE `skill` DROP KEY `char_id`;
ALTER TABLE `storage` DROP KEY `account_id`;
ALTER TABLE `mail_data` DROP KEY `char_id`;
ALTER TABLE `mail_data` DROP KEY `number`;
ALTER TABLE `mapreg` DROP KEY `reg`;
ALTER TABLE `mapreg` DROP KEY `index`;
ALTER TABLE `hotkey` DROP KEY `char_id`;

# change primery key
ALTER TABLE `cart_inventory` DROP PRIMARY KEY;
ALTER TABLE `guild_storage` DROP PRIMARY KEY;
ALTER TABLE `inventory` DROP PRIMARY KEY;
ALTER TABLE `storage` DROP PRIMARY KEY;

ALTER TABLE `cart_inventory` ADD PRIMARY KEY (`char_id`, `id`);
ALTER TABLE `guild_storage` ADD PRIMARY KEY (`guild_id`, `id`);
ALTER TABLE `inventory` ADD PRIMARY KEY (`char_id`, `id`);
ALTER TABLE `storage` ADD PRIMARY KEY (`account_id`, `id`);

# apply unique key
ALTER TABLE `char_data` DROP KEY `account_id`;
ALTER TABLE `char_data` ADD UNIQUE `account_slot` (`account_id`, `char_num`);
ALTER TABLE `char_data` DROP KEY `name`;
ALTER TABLE `char_data` ADD UNIQUE `name` (`name`);
ALTER TABLE `guild` ADD UNIQUE `name` (`name`);
ALTER TABLE `guild_alliance` DROP KEY `guild_id`;
ALTER TABLE `guild_alliance` ADD PRIMARY KEY (`guild_id`, `alliance_id`);
ALTER TABLE `guild_member` DROP KEY `guild_id`;
ALTER TABLE `guild_member` ADD PRIMARY KEY (`guild_id`, `char_id`);
ALTER TABLE `guild_position` DROP KEY `guild_id`;
ALTER TABLE `guild_position` ADD PRIMARY KEY (`guild_id`, `position`);
ALTER TABLE `guild_skill` DROP KEY `guild_id`;
ALTER TABLE `guild_skill` ADD PRIMARY KEY (`guild_id`, `id`);
ALTER TABLE `login` DROP KEY `name`;
ALTER TABLE `login` ADD UNIQUE `name` (`userid`);
ALTER TABLE `party` ADD UNIQUE `name` (`name`);
ALTER TABLE `friend` DROP KEY `char_id`;
ALTER TABLE `friend` ADD PRIMARY KEY (`char_id`, `friend_id`);
ALTER TABLE `homunculus_skill` DROP KEY `homun_id`;
ALTER TABLE `homunculus_skill` ADD PRIMARY KEY (`homun_id`, `id`);
ALTER TABLE `status_change` DROP KEY `char_id`;
ALTER TABLE `status_change` ADD PRIMARY KEY (`char_id`, `type`);

# normalize global_reg_value
CREATE TABLE `worldreg` (
  `account_id` int(11) NOT NULL default '0',
  `reg` varchar(32) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`, `reg`)
) TYPE = MyISAM;

CREATE TABLE `accountreg` (
  `account_id` int(11) NOT NULL default '0',
  `reg` varchar(32) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`, `reg`)
) TYPE = MyISAM;

CREATE TABLE `globalreg` (
  `char_id` int(11) NOT NULL default '0',
  `reg` varchar(32) NOT NULL default '',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`, `reg`)
) TYPE = MyISAM;

INSERT INTO `worldreg` (`account_id`, `reg`, `value`)
  SELECT `account_id`, `str`, `value` FROM `global_reg_value` WHERE `type` = '1';

INSERT INTO `accountreg` (`account_id`, `reg`, `value`)
  SELECT `account_id`, `str`, `value` FROM `global_reg_value` WHERE `type` = '2';

INSERT INTO `globalreg` (`char_id`, `reg`, `value`)
  SELECT `char_id`, `str`, `value` FROM `global_reg_value` WHERE `type` = '3';

DROP TABLE `global_reg_value`;

# drop unused tables
DROP TABLE IF EXISTS `ipbanlist`;
