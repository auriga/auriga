# fix type in party table
ALTER TABLE `party` MODIFY `exp` tinyint(4) unsigned NOT NULL default '0';
ALTER TABLE `party` MODIFY `item` tinyint(4) unsigned NOT NULL default '0';

# drop unused fields
ALTER TABLE `guild_member` DROP `rsv1`, DROP `rsv2`;
ALTER TABLE `guild_expulsion` DROP `acc`, DROP `rsv1`, DROP `rsv2`, DROP `rsv3`;
