# chnage default value

ALTER TABLE `guild_castle` MODIFY `economy` int(11) NOT NULL default '1';
ALTER TABLE `guild_castle` MODIFY `defense` int(11) NOT NULL default '1';

ALTER TABLE `charlog` MODIFY `time` datetime NOT NULL default '2000-01-01 00:00:00';
ALTER TABLE `interlog` MODIFY `time` datetime NOT NULL default '2000-01-01 00:00:00';
ALTER TABLE `login` MODIFY `lastlogin` datetime NOT NULL default '2000-01-01 00:00:00';
ALTER TABLE `loginlog` MODIFY `time` datetime NOT NULL default '2000-01-01 00:00:00';
