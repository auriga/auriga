# Auriga SQL Table Drop Sprict
# 2005/12/02 yoran
# まれにテーブル構築失敗するので、その時は下記スプリクトを実行してから
# 再度、main.sqlを実行してください。

DROP TABLE IF EXISTS `cart_inventory`;
DROP TABLE IF EXISTS `char_data`;
DROP TABLE IF EXISTS `charlog`;
DROP TABLE IF EXISTS `worldreg`;
DROP TABLE IF EXISTS `accountreg`;
DROP TABLE IF EXISTS `globalreg`;
DROP TABLE IF EXISTS `guild`;
DROP TABLE IF EXISTS `guild_alliance`;
DROP TABLE IF EXISTS `guild_castle`;
DROP TABLE IF EXISTS `guild_expulsion`;
DROP TABLE IF EXISTS `guild_member`;
DROP TABLE IF EXISTS `guild_position`;
DROP TABLE IF EXISTS `guild_skill`;
DROP TABLE IF EXISTS `guild_storage`;
DROP TABLE IF EXISTS `interlog`;
DROP TABLE IF EXISTS `inventory`;
DROP TABLE IF EXISTS `login`;
DROP TABLE IF EXISTS `loginlog`;
DROP TABLE IF EXISTS `memo`;
DROP TABLE IF EXISTS `party`;
DROP TABLE IF EXISTS `pet`;
DROP TABLE IF EXISTS `skill`;
DROP TABLE IF EXISTS `storage`;
DROP TABLE IF EXISTS `friend`;
DROP TABLE IF EXISTS `homunculus`;
DROP TABLE IF EXISTS `homunculus_skill`;
DROP TABLE IF EXISTS `status_change`;
DROP TABLE IF EXISTS `mail`;
DROP TABLE IF EXISTS `mail_data`;
DROP TABLE IF EXISTS `mapreg`;
DROP TABLE IF EXISTS `feel_info`;
DROP TABLE IF EXISTS `hotkey`;
DROP TABLE IF EXISTS `mercenary`;
DROP TABLE IF EXISTS `mercenary_employ`;
DROP TABLE IF EXISTS `quest`;
DROP TABLE IF EXISTS `elemental`;
DROP TABLE IF EXISTS `achieve`;
