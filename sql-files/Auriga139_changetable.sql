# fix some field type
ALTER TABLE `char` MODIFY `base_level` int(11) unsigned NOT NULL default '1';
ALTER TABLE `char` MODIFY `job_level` int(11) unsigned NOT NULL default '1';
ALTER TABLE `char` MODIFY `last_x` int(11) NOT NULL default '53';
ALTER TABLE `guild` MODIFY `average_lv` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `guild_member` MODIFY `lv` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `memo` MODIFY `map` varchar(24) NOT NULL default '';
ALTER TABLE `party` MODIFY `name` varchar(24) NOT NULL default '';
ALTER TABLE `pet` MODIFY `level` smallint(6) unsigned NOT NULL default '0';
ALTER TABLE `skill` MODIFY `lv` int(11) NOT NULL default '0';
ALTER TABLE `homunculus` MODIFY `base_level` smallint(6) unsigned NOT NULL default '1';
