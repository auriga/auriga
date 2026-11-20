-- アカウント限定キャッシュショップの販売枠別購入履歴
CREATE TABLE IF NOT EXISTS `account_cashshop` (
  `account_id` int unsigned NOT NULL,
  `sale_id` int unsigned NOT NULL,
  `purchased` int unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`account_id`,`sale_id`)
) ENGINE=InnoDB;
