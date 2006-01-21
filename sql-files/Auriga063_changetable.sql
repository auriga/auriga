#fix `value` to integer
ALTER TABLE `global_reg_value` CHANGE `value` `value` int(11) NOT NULL default '0';
