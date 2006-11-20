# rename field of incuvate to incubate in pet table
ALTER TABLE `pet` CHANGE `incuvate` `incubate` int(11) NOT NULL default '0';
