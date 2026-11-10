# Auriga-1628: RoDEXの添付アイテムと送信者ID
#
# 1) 添付アイテム用テーブルを作成する
# 2) 送信者のキャラクターIDを保存する
# 3) 既存メールの添付アイテムを新テーブルへ移行する
# 4) 移行済みの添付列をmail_dataから削除する
#

CREATE TABLE IF NOT EXISTS `mail_attachment` (
  `char_id` int(11) NOT NULL default '0',
  `number` int(11) unsigned NOT NULL default '0',
  `idx` tinyint(4) NOT NULL default '0',
  `id` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` smallint(6) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` tinyint(4) NOT NULL default '0',
  `refine` tinyint(4) NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` int(6) NOT NULL default '0',
  `card1` int(6) NOT NULL default '0',
  `card2` int(6) NOT NULL default '0',
  `card3` int(6) NOT NULL default '0',
  `opt0id` smallint(6) NOT NULL default '0',
  `opt0val` smallint(6) NOT NULL default '0',
  `opt1id` smallint(6) NOT NULL default '0',
  `opt1val` smallint(6) NOT NULL default '0',
  `opt2id` smallint(6) NOT NULL default '0',
  `opt2val` smallint(6) NOT NULL default '0',
  `opt3id` smallint(6) NOT NULL default '0',
  `opt3val` smallint(6) NOT NULL default '0',
  `opt4id` smallint(6) NOT NULL default '0',
  `opt4val` smallint(6) NOT NULL default '0',
  `limit` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY (`char_id`, `number`, `idx`)
) ENGINE = InnoDB;

# 返送先のキャラクターID。0の場合は送信者名から検索する。
# send_id列が既にある場合は次のALTERを実行しない。
ALTER TABLE `mail_data` ADD COLUMN `send_id` int(11) NOT NULL default '0' AFTER `read`;

# 既存の添付を移行する。移行済みの添付は重複して追加しない。
# 旧添付列を削除済みの場合、ここから最後のALTERまで実行しない。
INSERT INTO `mail_attachment` (
  `char_id`, `number`, `idx`,
  `id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`,
  `card0`, `card1`, `card2`, `card3`,
  `opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`,
  `opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`
)
SELECT
  d.`char_id`, d.`number`, 0,
  d.`id`, d.`nameid`, d.`amount`, d.`equip`, d.`identify`, d.`refine`, d.`attribute`,
  d.`card0`, d.`card1`, d.`card2`, d.`card3`,
  d.`opt0id`, d.`opt0val`, d.`opt1id`, d.`opt1val`, d.`opt2id`, d.`opt2val`,
  d.`opt3id`, d.`opt3val`, d.`opt4id`, d.`opt4val`, d.`limit`
FROM `mail_data` d
LEFT JOIN `mail_attachment` a
  ON a.`char_id` = d.`char_id` AND a.`number` = d.`number` AND a.`idx` = 0
WHERE d.`nameid` <> 0 AND a.`char_id` IS NULL;

ALTER TABLE `mail_data`
  DROP COLUMN `id`,
  DROP COLUMN `nameid`,
  DROP COLUMN `amount`,
  DROP COLUMN `equip`,
  DROP COLUMN `identify`,
  DROP COLUMN `refine`,
  DROP COLUMN `attribute`,
  DROP COLUMN `card0`,
  DROP COLUMN `card1`,
  DROP COLUMN `card2`,
  DROP COLUMN `card3`,
  DROP COLUMN `opt0id`,
  DROP COLUMN `opt0val`,
  DROP COLUMN `opt1id`,
  DROP COLUMN `opt1val`,
  DROP COLUMN `opt2id`,
  DROP COLUMN `opt2val`,
  DROP COLUMN `opt3id`,
  DROP COLUMN `opt3val`,
  DROP COLUMN `opt4id`,
  DROP COLUMN `opt4val`,
  DROP COLUMN `limit`;
