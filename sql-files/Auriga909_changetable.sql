# fix mail_data structure
ALTER TABLE `mail_data` MODIFY `send_name` varchar(23) NOT NULL default '';
ALTER TABLE `mail_data` MODIFY `receive_name` varchar(23) NOT NULL default '';
ALTER TABLE `mail_data` MODIFY `title` varchar(39) NOT NULL default '';
