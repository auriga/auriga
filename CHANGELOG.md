----------------------------------------
//1524 [2023/03/30] by refis

・mapflag「damage_rate」追加
　（const.txt, script_ref.txt, map/battle.c, map.h, npc.c, script.c）

----------------------------------------
//1523 [2023/03/19] by refis

・grf内のファイル名が長すぎるとエラーになっていたので
　配列長を拡張

----------------------------------------
//1522 [2023/03/15] by refis

・item_dbの更新
	Thanks Heaven さん

----------------------------------------
//1521 [2022/11/08] by Cocoa

・経験値テーブルの更新  
	本鯖で2022年8月30日に適用された経験値テーブルです。

・Job補正の更新

----------------------------------------
//1520 [2022/11/08] by Cocoa

・経験値テーブルの更新  
	本鯖で2020年1月28日に適用された経験値テーブルです。  
	履歴として一旦残すためのコミットになります。

----------------------------------------
//1519 [2022/09/19] by refis

・レッケンベルの噂クエストの報酬を再受領できるよう修正
　（npc_town_lighthalzen.sc, npc_memorial_worsef.sc）

----------------------------------------
//1518 [2022/09/11] by refis

・ランダム系アイテムのリストを修正（item_random.txt）

----------------------------------------
//1517 [2022/09/11] by refis

・bonus系列でエラーが発生した際、アイテムIDを表示するようチェックを強化（bonus.c）

・ランダム系アイテムのリストをEP14相当に更新（item_random.txt, mob_random.txt）

・ランダム系アイテムの追加（const.txt, item_db.txt）

・スクリプト関数[getrandommob]追加（doc/script_ref.txt, script.c）

・ランダム系アイテムの最大登録数を拡張（itemdb.h）

----------------------------------------
//1516 [2022/05/22] by Cocoa

・特定条件下で取得経験値が1になる不具合を修正
	共闘ボーナス×与ダメージがint上限を超えた場合に発生

----------------------------------------
//1515 [2022/05/22] by Cocoa

・vc_make.batの対応コンパイラ整理
	サポート切れのコンパイラを削除とVS2022を追加
	合わせて不要になったコンパイラオプションなどを削除

----------------------------------------
//1514 [2022/05/22] by Cocoa

・ペットが孵化出来なくなる不具合の修正（sql-files/Auriga1514_changetable.sql, sql-files/main.sql）
	card0が0xff00(65280)の時にペットの卵と判定しているにも関わらず、DBがshort(上限32767)になっているために発生。
	inventory、cart_inventory、storage、guild_storage、mail_dataにあるペットの卵のcard0を32767から65280に変更することで既存ペットの卵は救済可能。

----------------------------------------
//1513 [2022/05/22] by refis

・[エビ三昧]の効果と持続時間計算を修正（skill.c, status.c）
	Thanks Heaven さん、sabun さん

・[ミャウミャウ]効果がレベルに対して正規的でないミスを修正（skill.c）
	Thanks Heaven さん

----------------------------------------
//1512 [2022/04/13] by refis

・サモナースキルでアイテム消費設定抜けがあったものを修正（skill_require_db.txt）
	Thanks Heaven さん

・PTL以外でサラの記憶に入場できなかった箇所を修正（npc_memorial_sara.sc）
	Thanks Heaven さん

・フェイスワームの巣の最終イベントのエラーを修正（npc_memorial_faceworm.sc）
	Thanks kuura さん

----------------------------------------
//1511 [2022/03/13] by refis

・魔人の塔メモリアルの再入場チェック、イベントを修正（npc_memorial_towermorocc.sc）

----------------------------------------
//1510 [2022/01/13] by refis

・アップグレード失敗時にも成功パケットを送っていたのを修正（clif.c, pc.*）

----------------------------------------
//1509 [2022/01/08] by refis

・クエストステータス変更が正常動作しない誤りを修正（clif.c）
	Thanks Dallen さん

・アイテムプレビューがitemid拡張に対応してなかったのを修正（clif.c）

----------------------------------------
//1508 [2022/01/08] by refis

・モロク復興関係NPCを更新（npc_town_morocc.sc, npc_job_thirdclass.sc）
	Thanks a lot Dallen さん!

----------------------------------------
//1507 [2022/01/07] by refis

・1505のitemidミスを修正（lapineupgrade_db.txt）
	Thanks Dallen さん

・対応item_db.txtの更新（item_db*.txt）

----------------------------------------
//1506 [2022/01/06] by refis

・オートスペル、オートアクティブ系アイテムボーナスでもスキル名称を利用できるよう追加拡張（script.c）
	Thanks Dallen さん

----------------------------------------
//1505 [2022/01/06] by refis

・ランダムオプションシステムの改修
	-> ID項をナンバリングとして扱えるように有効itemidチェックを削除する（script.c）
	-> optvalテーブルでカウントアップ値を指定できるようテーブル処理を拡張（itemdb.*, luascript.c）
	-> オプションが付かない項目があった場合、以降のオプションが非表示になるため
	   オプションを切り詰めるようにする（mob.c, script.c）
		Thanks エニ さん

・アイテムアップグレードシステムの追加（lapineupgrade_db.txt, packet_db.lua, script_ref.txt, clif.*, itemdb.*, pc.*, script.c）
	Thanks Dallen さん

・luaデータベースの更新（lua_auriga.conf, enumvar.lua, item_randopt_db.lua）

----------------------------------------
//1504 [2022/01/04] by refis

・オーバースキル「ツーハンドクイッケン」の増加量を50%から70%に修正（status.c）
	Thanks Dallen さん

----------------------------------------
//1503 [2022/01/04] by refis

・[魔神殿]の進行不具合と報酬ドロップの追加（npc_memorial_eom.sc）

----------------------------------------
//1502 [2022/01/03] by refis

・メモリアルダンジョン[魔神殿]実装（map_auriga.conf, npc_memorial_eom.sc）

・関連傭兵データの追加（merc_db.txt, mob_db.txt）

----------------------------------------
//1501 [2022/01/02] by refis

・職業定義テーブルのずれを修正（mmo.h）

・スキルユニット定義を追加（skill.h）
	Thanks Dallen さん

----------------------------------------
//1500 [2022/01/02] by refis

・PACKETVER[20190703]以降でコンパイルエラーが出ているのを修正（clif.c）

・2020-02-05aRagexeREをリスト追加（bcc32_make.bat, Makefile, vc_make.bat）

----------------------------------------
//1499 [2022/01/02] by refis

・文字コードが誤っていたので訂正（npc_memorial_heroair.sc）

----------------------------------------
//1498 [2021/12/19] by refis

・座る/立つ時に動作するスキルの判定式を修正（skill.c）
	Thanks Dallen さん

----------------------------------------
//1497 [2021/12/07] by refis

・古のグラストヘイムで会話中にスタックする箇所を修正（npc_memorial_glastheim.sc）

----------------------------------------
//1496 [2021/12/07] by refis

・覚醒ローブが複数回エンチャントできる箇所の修正（npc_memorial_fenrirsara.sc）
	Thanks Dallen さん

・管理コマンド[reloaditemdb]でメモリリークが発生していたのを修正（itemdb.c）
	Thanks Dallen さん

・メモリアルダンジョン生成破棄時にセル情報をリセットする（map.c）
	Thanks Dallen さん

----------------------------------------
//1495 [2021/11/07] by refis

・モンスタートーク修正（mob_talk_db.txt）

・デュプレライトの名称を修正（skill_db*.txt, battle.c, skill.c）

・ピアスエンチャントのtypo修正（npc_memorial_fenrirsara.sc）

----------------------------------------
//1494 [2021/10/10] by refis

・攻撃速度系エンチャントを加算タイプに修正（item_db.txt）

・サラのローブ覚醒、エンチャント関係を実装（npc_memorial_fenrirsara.sc）

----------------------------------------
//1493 [2021/09/09] by refis

・サモナースキルの有効射程を修正（skill_db.txt）

----------------------------------------
//1492 [2021/08/26] by refis

・サラの記憶の再入場制限条件式を修正（npc_memorial_sara.sc）
	Thanks rina さん

----------------------------------------
//1491 [2021/08/26] by refis

・ネジリアン帝国の陰謀クエスト実装（npc_quest_illusionteddybear.sc, quest_db.txt）

・ネジリアン帝国追加マップのmapflag更新 (mapflag.sc)

・ネジリアン帝国追加マップのmonster出現定義追加（npc_monster_eindun.sc）

・アイテム、モンスターデータを更新（item_db.txt, mob_db.txt, mob_skill_db.txt）

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1490 [2021/08/15] by refis

・ロックリッジメインクエストの報酬間違いを修正（npc_town_rockridge.sc）
	Thanks rina さん

・不必要な定義があったので削除（status.c）

----------------------------------------
//1489 [2021/08/15] by refis

・[サモンレギオン]スキルの挙動と不具合を修正（skill_db.txt, homun.*, mob.c, skill.c）
	Thanks rina さん

----------------------------------------
//1488 [2021/08/15] by refis

・ホムンクルススペリオールの経験値テーブルを修正（exp_homun.txt, homun_db.txt）
	Thanks rina さん

----------------------------------------
//1487 [2021/08/12] by refis

・ピンタドスフェスティバルが進行しないミス修正（npc_town_portmalaya.sc）
	Thanks rina さん

----------------------------------------
//1486 [2021/08/07] by refis

・フルスロットル習得クエスト実装
（quest_db.txt, skill_*.txt, npc_quest_skillget3.sc, mmo.h, skill.*, status.c）

----------------------------------------
//1485 [2021/07/20] by refis

・モンスターデータの更新（mob_db.txt, mob_skill_db.txt, mob_talk_db.txt）
	Thanks Dallen さん

----------------------------------------
//1484 [2021/07/20] by refis

・skill_require_dbに不正な項目があった点を修正（skill_require_db.txt）
	Thanks kuura さん

----------------------------------------
//1483 [2021/07/20] by refis

・skill_idリストの更新（skill.h）

----------------------------------------
//1482 [2021/07/16] by refis

・item_db.txtの添付洩れ（item_db.txt）

----------------------------------------
//1481 [2021/07/16] by refis

・スキルを指定するアイテムボーナスでもスキル名称を利用できるよう追加拡張
（item_db.txt, script.c）

----------------------------------------
//1480 [2021/07/12] by refis

・スクリプト命令「delmisceffect」追加（script_ref.txt, clif.*, script.c）
	Thanks Dallen さん

----------------------------------------
//1479 [2021/07/12] by refis

・1478で、存在しない定義名を指定した際クラッシュする可能性があったのを修正（skill.c）

・typo修正（skill.c）

----------------------------------------
//1478 [2021/07/12] by refis

・スクリプト命令「skill」、「itemskill」、スクリプト関数「getskilllv」で
　スキル名称を指定できるよう処理を拡張
　（item_db.txt, skill_db.txt, map.c, script.c, skill.*）

・リファレンス更新（script_ref.txt）

----------------------------------------
//1477 [2021/07/11] by refis

・スクリプト命令「unittalk」、クエスト討伐カウントの影響範囲を変更
	-> AREA_SIZE(14セル) -> WIDE_AREA_SIZE(18セル)
	（clif.*, map.h, mob.c, script.c）

----------------------------------------
//1476 [2021/07/11] by refis

・オートアクティブの複数装着時の仕様を変更
	-> カード等の同一アイテムのアクティブ化を許容する（conf/battle_auriga.conf）
	-> 同一アイテム装着時は確率のみ加算させる（bonus.c）
	-> 以下に対応するため新たに専用のitem_autoactive.txtを追加
	   アクティブ中、ステータス更新のたびにアクティブ時エフェクトが発生する
	   同一アイテムを複数装備時にアクティブ中効果が重複適用される
	   （item_autoactive.txt, bonus.c, itemdb.*, status.c）

・item_autoactive.txt追加に伴う一部item_dbの更新（item_db.txt）

----------------------------------------
//1475 [2021/07/10] by refis

・1471のfollow up（pc.c）

----------------------------------------
//1474 [2021/07/10] by refis

・luaシステムに関するドキュメントの整備（lua_ref.txt）

----------------------------------------
//1473 [2021/07/10] by refis

・1472に伴うドキュメントの更新（server_build.txt）

----------------------------------------
//1472 [2021/07/10] by refis

・packet_db.txtが残ったままだったので削除（db/packet_db.txt）

・上記に伴うdb_ref.txt内の記載を修正（db_ref.txt）

----------------------------------------
//1471 [2021/07/10] by refis

・プレイヤーのスキルツリーで前提スキルを6つまで設定できるよう書式を拡張
（skill_tree.txt, doc/db_ref.txt, pc.c）

----------------------------------------
//1470 [2021/06/27] by refis

・プロブルレムのエンチャントアイテムを更新（npc_quest_slotenchant.sc）
	Thanks a lot kuteloli さん!

----------------------------------------
//1469 [2021/06/27] by refis

・マップフラグ「nobranch」指定時、対象アイテム使用時に
　エラーメッセージを出力するよう修正（pc.c）

----------------------------------------
//1468 [2021/06/20] by refis

・ホムンクルス変異クエスト実装（map_auriga.conf, mapflag.sc, npc_quest_homun_s.sc）

・プロンテラのテイミング商人の販売リストを更新（item_db.txt, npc_town_prontera.sc）

・ホムンクルスSのステータスを修正（homun_db.txt）

・一部MAPを読み込みリストから除外（map_auriga.conf）

----------------------------------------
//1467 [2021/06/20] by refis

・[RE]クリティカル計算で敵Luk÷5を減算するよう修正（battle.c）

----------------------------------------
//1466 [2021/06/19] by refis

・PACKETVER[20200709]以降変更のパケット記述位置を訂正（packet_db.lua）

----------------------------------------
//1465 [2021/06/19] by refis

・conf/help.txtの更新（conf/help.txt）

----------------------------------------
//1464 [2021/06/17] by refis

・1462の戦闘設定「homun_max_aspd」の補正を差し戻し
　代わりにstatus.c側の処理を変更（battle_auriga.conf, status.c）

----------------------------------------
//1463 [2021/06/16] by refis

・NPCスキル[M呪縛陣]追加（skill_cast_db.txt, skill_db*.txt, skill.c）

・上記に合わせて使用スクリプトを修正（npc_quest_illusion*.sc）

----------------------------------------
//1462 [2021/06/13] by refis

・ホムンクルススペリオール実装準備（db/*, src/*）

・ホムンクルスの進化ボーナスを更新（homun_db2.txt）

・戦闘設定「homun_max_aspd」を暫定で100に補正してみる（battle_auriga.conf）

・戦闘設定「homun_status_max」を追加（battle_auriga.conf, battle.*, homun.c）
　デフォルト値は150です

・ヘルパワー中でもジークフリードの証が有効だったミスを修正（clif.c）

・警戒スキルの効果が正常に動いていなかったので修正（skill.c, status.c）

・packet_db.luaを更新（db/packet_db.lua, clif.c）

----------------------------------------
//1461 [2021/06/06] by refis

・実績レベルの必要ポイントを修正（achievement_level_db.lua）

・ラヘルのクエストの一部にクエストリストを適用（quest_db.txt, npc_town_rachel.sc）
	Thanks a lot Dallen さん

----------------------------------------
//1460 [2021/05/02] by refis

・サモナースキル「～の力」系列の習得スキル数ボーナス実装（battle.c, pc.*, skill.c, status.c）

・物理・魔法基礎ダメージ計算をRRに対応（battle.c, status.c）

----------------------------------------
//1459 [2021/05/01] by refis

・モーラの上位アーティファクト交換を実装（npc_town_mora.sc）

----------------------------------------
//1458 [2021/05/01] by refis

・アースクエイクのダメージ計算挙動を修正（battle.c）
	-> 自身への物理攻撃ダメージを魔法攻撃として分散させる
	Thanks Dallen さん

----------------------------------------
//1457 [2021/05/01] by refis

・item_bonusの説明文を少し修正（item_bonus.txt）

----------------------------------------
//1456 [2021/05/01] by refis

・mapflag「nocostume」を追加（const.txt, script_ref.txt, 
 atcommand.c, clif.c, map.h, npc.c, pc.*, script.c）

----------------------------------------
//1455 [2021/05/01] by refis

・battle_auriga.confを設定項目ごとに内容整理（battle_auriga.conf）
	-> 並び順の入れ替えのみで、設定変更や漏れはないはずですが
	   運用中のAurigaの場合はbattle_auriga.confをimport/battle_conf.txtへ
	   反映させる等してください

----------------------------------------
//1454 [2021/04/30] by refis

・script_erase_sleeptimerへ構造体で渡さないように修正（map.c, script.*）
	Thanks eni-ro さん

----------------------------------------
//1453 [2021/04/30] by refis

・エクラージュ猫の手職員のメニュー表示を修正（npc_town_eclage.sc）
	Thanks Dallen さん

----------------------------------------
//1452 [2021/04/25] by refis

・item_dbのmissing error修正（item_db.txt）

----------------------------------------
//1451 [2021/04/25] by refis

・性差メッセージを補完
（npc_quest_illusionturtleisland.sc, npc_quest_illusionvampire.sc）

----------------------------------------
//1450 [2021/04/25] by refis

・スクリプト命令「getmapxy」において、
モンスター対象時の非検索対象条件からHPチェックを撤去 (script.c)
	-> モンスター死亡時イベントで扱うことで死亡座標が取得できます

----------------------------------------
//1449 [2021/04/25] by refis

・スキル名称定義を更新 (skill_db.txt)

----------------------------------------
//1448 [2021/04/24] by refis

・ジョンダノービスの転送メニューを更新（npc_misc_dynamicnpc.sc）

----------------------------------------
//1447 [2021/04/24] by refis

・陽居村の幽霊少女クエストの開始可能レベルチェックがなかったのを修正
（npc_quest_illusionturtleisland.sc）

----------------------------------------
//1446 [2021/04/24] by refis

・イリュージョンダンジョンの特殊モンスターが固定位置で出現しないようにする
（npc_quest_illusionmoonlight.sc, npc_quest_illusionvampire.sc）

----------------------------------------
//1445 [2021/04/24] by refis

・陽居村の幽霊少女クエスト実装（npc_quest_illusionturtleisland.sc, quest_db.txt）

・陽居村の幽霊少女追加マップのmapflag更新 (mapflag.sc)

・陽居村の幽霊少女追加マップのmonster出現定義追加（npc_monster_turdun.sc）

・陽居村の幽霊少女追加マップのwarp更新 (npc_warp_dun.sc)

・アイテム、モンスターデータを更新（item_db.txt, mob_db.txt, mob_skill_db.txt）

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1444 [2021/04/24] by refis

・スクリプト関数「areacallmonster」を実装（doc/script_ref.txt, script.c）

・[Mハイネスヒール]のパケット処理を修正（skill.c）

・NPC専用スキル名称を更新 (skill_db.txt)

----------------------------------------
//1443 [2021/04/18] by refis

・rAthenaを参考にモンスターのターゲッティング範囲に
　Range2, Range3パラメータを利用するように修正（mob.c）

・クローキング状態NPCについて、プレーヤー毎に可視可能NPCをリスト化して保存するよう修正
（clif.c, map.h, pc.c, script.c, unit.c）

・クローキング状態NPCについて、OnTouchラベルを無効するよう修正（npc.c）

・PACKETVERによって発生する警告を抑制（clif.c）

・250ページクエスト実装（npc_quest_illusionvampire.sc, quest_db.txt）

・250ページ追加マップのmapflag更新 (mapflag.sc)

・250ページ追加マップのmonster出現定義追加（npc_monster_gefdun.sc）

・アイテム、モンスターデータを更新（item_db2.txt, mob_db.txt, mob_skill_db.txt）

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1442 [2021/04/17] by refis

・[Mハイネスヒール]実装（db/skill_db.txt, db/skill_db2.txt, skill.c）
	Thanks Dallen さん

・[アローストーム]、[Mアローストーム]の効果範囲が誤っていたのを修正（skill.c）

----------------------------------------
//1441 [2021/04/13] by refis

・フェイスワームの巣でタイマーイベントが停止していなかった個所を修正
（npc_memorial_faceworm.sc）
	Thanks Dallen さん

・武器修理パケットの処理誤りを修正（clif.c）
	Thanks Dallen さん

----------------------------------------
//1440 [2021/02/21] by refis

・フェイスワームの巣メモリアル実装（npc_memorial_faceworm.sc）

・item_dbの更新（item_db.txt）

・quest_dbの更新（quest_db.txt）

・mapflagの更新（mapflag_memorial.sc）

・map_auriga.confの更新（map_auriga.conf）

・フェンリルとサラの再入場チェックが不十分だった箇所を修正（npc_memorial_fenrirsara.sc）
	Thanks kuura さん

----------------------------------------
//1439 [2021/01/07] by refis

・マラン島クエストNPCを更新（npc_town_malangdo.sc, npc_warp_town.sc）
　->ニャンゲーマーズクエスト実装
　->鉄人料理長ニャスの伝説クエスト実装
	Thanks a lot teddy さん

・quest_dbの更新（quest_db.txt）
	Thanks a lot teddy さん

----------------------------------------
//1438 [2021/01/04] by refis

・ランダムオプションのドキュメントを整理（db_ref.txt）

・item_dbの更新（item_db.txt）
	Thanks Excella さん、teddy さん

----------------------------------------
//1437 [2021/01/03] by refis

・フェンリルとサラメモリアル実装（npc_memorial_fenrirsara.sc）

・mob_dbの更新（mob_db.txt, mob_skill_db.txt）

・quest_dbの更新（quest_db.txt）

・memorial_dbの更新（memorial_db.txt）

・mapflagの更新（mapflag_memorial.sc）

・map_auriga.confの更新（map_auriga.conf）

・market用パケット定義他の更新（packet_db.lua）

----------------------------------------
//1436 [2021/01/03] by refis

・NPC商店にmarket型を追加実装
　購入できる最大個数の指定が出来るshopです
（script_ref.txt, clif.*, map.h, npc.c, script.c）

・スクリプト命令「npcshopitem」追加（script_ref.txt, npc.*, script.c）
	Thanks Dallen さん

・ロックリッジの商店をnpcshopitemで実装（npc_town_rockridge.sc）

----------------------------------------
//1435 [2021/01/02] by refis

・アイテム作成系の送信パケット拡張漏れを修正（clif.c）
	Thanks Dallen さん

・PACKETVERでclif_show_partyshareitemのバッファが足りないミスを修正（clif.c）
	Thanks Dallen さん

----------------------------------------
//1434 [2021/01/01] by refis

・PACKETVER20180704以降、アイテム購入出来なかったのを修正
（buyingstore.c, clif.*, npc.*）

・獲得経験値量表示上限がint型上限に抑えられていたのを修正（clif.*, pc.c）

・アイテムID拡張関連のキャストエラー対応

----------------------------------------
//1433 [2021/01/01] by refis

・IDがshortの範囲を超えるアイテムのスクリプト処理を修正（mmo.h, script.c）

・定義関係の更新（mmo.h, skill.h, status.h）

----------------------------------------
//1432 [2020/12/31] by refis

・コンパイルエラーの修正（chardb_txt.c）

・通信量削減のため敵HPの更新処理に0xa36を利用するよう修正（clif.c, mob.c）

----------------------------------------
//1431 [2020/06/02] by refis

・hateffectの利用でサーバクラッシュする不具合を修正（clif.c）
	Thanks eni-ro さん

・MD削除時、NPC解放でsleepタイマーも削除させる（map.c, script.*）

----------------------------------------
//1430 [2020/05/31] by refis

・魔神殿メモリアル関連のクエストNPCデータ修正（npc_town_morovol.sc）

----------------------------------------
//1429 [2020/05/27] by refis

・スクリプト命令「mobuseskill」系列において、
　詠唱時間が0のときスキル使用条件を無視するようにしてみる（script.c）

・NPCスキル「獄炎」の状態異常付与を全体に与えるように修正（skill.c）

----------------------------------------
//1428 [2020/05/27] by refis

・魔神殿メモリアル関連データ修正
	-> item_dbの更新（item_db.txt）
	-> mob_dbの更新（mob_db.txt, mob_skill_db.txt）
	-> quest_dbの更新（quest_db.txt）
	-> map_auriga.confの更新（map_auriga.conf）
	-> memorial_dbの更新（memorial_db.txt）

・禁忌の研究所メモリアル内の敵出現エラー修正（npc_memorial_worsef.sc）
	Thanks Dallen さん

・時空ブーツエンチャントNPCで最終エンチャントを繰り返せるミス修正
（npc_quest_glastheim.sc）
	Thanks Heaven さん

----------------------------------------
//1427 [2020/05/22] by refis

・モンスタースキル使用条件「casttargeted」は
　自己対象スキルで動作しないよう変更（unit.c）
	-> 代わりに「afterskill」を利用してください

・ビオスの島メモリアル実装（npc_memorial_bios.sc）

・モルスの洞窟メモリアル実装（npc_memorial_mors.sc）

・mob_dbの更新（mob_db.txt, mob_skill_db.txt）

・quest_dbの更新（quest_db.txt）

・mapflagの更新（mapflag_memorial.sc）

・map_auriga.confの更新（map_auriga.conf）

----------------------------------------
//1426 [2020/05/15] by refis

・Patch1421以降のワープ型NPC接触時のエラーを修正（npc.c）

----------------------------------------
//1425 [2020/05/15] by refis

・フレイムヴァレーNPC実装（npc_town_morovol.sc, npc_monster_morovol.sc）
	-> フレイムヴァレーへの道クエスト実装
	-> 滅亡祝福教団クエスト実装
	-> フレイムヴァレーデイリークエスト実装

・item_dbの更新（item_cardtype.txt, item_db.txt）
	Thanks kuura さん、eni-ro さん

・mob_dbの更新（mob_db.txt, mob_skill_db.txt）

・quest_dbの更新（quest_db.txt）

・mapflagの更新（mapflag.sc）

・map_auriga.confの更新（map_auriga.conf）

----------------------------------------
//1424 [2020/05/14] by refis

・スクリプト命令「sit」「stand」追加（script.c）
	-> 座る/立つ

・スクリプト関数「mdopenstate」追加（memorial.*, script.c）
	-> 指定MDの生成が完了していれば1を、してなければ0以下を返します

----------------------------------------
//1423 [2020/05/14] by refis

・スクリプト命令[menu]でサーバークラッシュする不具合を修正（script.c）
	Thanks Dallen さん

----------------------------------------
//1422 [2020/05/14] by refis

・[RE] : デリュージのMHP増加効果がモンスターに適用されていなかったのを修正（status.c）

・NPCスキル[デスサモン]の挙動を修正（mob.c, skill.c）

----------------------------------------
//1421 [2020/05/14] by refis

・sleep2の復帰時、モンスターのアタッチが考慮されていないのを修正（script.c）

・プレイヤーが複数のOnTouchが起動できるよう拡張（clif.c, map.h, npc.c, unit.c）

・OnTouch拡張に伴うスクリプトの修正（npc_town_rockridge.sc）

----------------------------------------
//1420 [2020/05/02] by refis

・サモナーの一部スキル消費SP設定不正を修正（skill_require_db.txt）
	Thanks Dallen さん

----------------------------------------
//1419 [2020/05/02] by refis

・NPCタイマーが動作し続けるスクリプトの抑制（npc/*）

----------------------------------------
//1418 [2020/05/01] by refis

・エンドレスタワーの未調査メッセージを補完（npc_memorial_tower.sc）

----------------------------------------
//1417 [2020/05/01] by refis

・変数の直接代入が可能になるようにスクリプト構文の処理を調整（script.c）
　また、変数に対してインクリメントとデクリメントできるよう処理を追加
　　※インクリ/デクリメントはset命令と等価であるため、命令文や関数等と組み合わせて扱うことはできません。

　利用法
　'@val = 100;
　'@val++;		=> 101
　'@val -= 100;	=> 1

　以下は等価処理となります。
　for(set '@i,0; '@i<10; set '@i,'@i+1)
　for('@i=0; '@i<10; '@i++)

----------------------------------------
//1416 [2020/05/01] by refis

・通行不能セルにwarp型NPCを配置時、setcellで通行可能になっても動作しないため
　NPC配置時に通行不能でもNPC配置フラグを立てておくように変更（npc.c）

----------------------------------------
//1415 [2020/04/21] by refis

・フローズンメモリークエスト実装（npc_quest_illusionfrozen.sc, quest_db.txt）

・フローズンメモリー追加マップのmapflag更新 (mapflag.sc)

・フローズンメモリー追加マップのmonster出現定義追加（npc_monster_icedun.sc）

・月夜花の悪夢のモンスター出現処理を修正（npc_quest_illusionmoonlight.sc）

・月夜花の悪夢でデスペナルティが発生していた点を修正 (mapflag.sc)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1414 [2020/04/17] by refis

・キャッシュアイテム「ジョンダパス」のクールタイム修正（item_db2.txt）

・スクリプト命令「dynamicnpc」の使用失敗メッセージを追加（clif.*, script.c）

----------------------------------------
//1413 [2020/03/19] by refis

・スクリプト命令「dynamicnpc」追加（script_ref.txt, clif.*, map.h, npc.*, pc.c, script.c, unit.c）
	-> プレイヤーの視界内に指定の座標でNPCを出現させます。

・キャッシュアイテム「ジョンダパス」実装（item_db.txt, item_db2.txt, npc_misc_pointshop.sc）

・NPC「ジョンダノービス」実装（const.txt, scdata_db.txt, status.*, npc_misc_dynamicnpc.sc）

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1412 [2020/03/19] by refis

・Patch 0138の使用後ディレイ共有についてfollow up（mob.c, skill.c）
	-> 各スキル毎にディレイ判断していた箇所を修正し、
	   スキル使用時の各ディレイを同一スキルに対しても適用されるように処理変更する
	修正前
	-> ディレイ0のスキル使用後、ディレイ30秒の同一スキルを使用するまで30秒の待機が必要
	修正後
	-> 同条件時、スキル使用に待機が不要。ディレイ30秒の同一スキル使用後は再使用に30秒の待機が必要
		Thanks Dallen さん

----------------------------------------
//1411 [2020/03/19] by refis

・プラエファティオがオーバーフロウする可能性があったのを修正（skill.c, status.c）
	Issues Report #15 , Thanks eni-ro さん

----------------------------------------
//1410 [2020/03/07] by refis

・PACKETVER[20150513]以降のクエストリストパケット構造に不整合が発生してたミス修正（clif.c）
	Issues Report #14 , Thanks eni-ro さん

・0xb13のパケ長がおかしかったので調整（packet_db.lua）

・Patch1409 follow up（battle.c）

----------------------------------------
//1409 [2020/03/07] by refis

・NPCスキル[Mドラゴンブレス]実装（skill_cast_db.txt, skill_db*.txt, battle.c, skill.c）

・モンスターのデータ、使用スキルを更新（mob_db.txt, mob_skill_db.txt）

・mob_talk_db.txtの更新（mob_talk_db.txt）

----------------------------------------
//1408 [2020/03/07] by refis

・月夜花の悪夢クエスト実装（npc_quest_illusionmoonlight.sc, quest_db.txt）

・月夜花の悪夢追加マップのmapflag更新 (mapflag.sc)

・月夜花の悪夢追加マップのmonster出現定義追加（npc_monster_paydun.sc）

・モンスターのデータ、使用スキルを追加（mob_db.txt, mob_skill_db.txt）

・mob_talk_db.txtの更新（mob_talk_db.txt）

・map_auriga.conf更新 (map_auriga.conf)

・Patch1404のfollow up (mob.c)

・モンスタートークに改行コードが入り込んでいたのを修正 (clif.c, mob.c)

----------------------------------------
//1407 [2020/03/06] by refis

・ピラミッドダンジョン・スフィンクスダンジョンのモンスター出現情報を最新のものに更新
（npc_monster_insphinx.sc, npc_monster_mocpryd.sc）

・新規配置モンスターのデータ、使用スキルを追加（mob_db.txt, mob_skill_db.txt）

----------------------------------------
//1406 [2020/03/06] by refis

・定数Job_Starの表記にぶれがあったのを統一（const.txt, npc_misc_pointshop.sc, npc_custom_jobchange.sc）

・タナトスタワー3Fへの入場が一人で可能に変更されているので修正（npc_quest_noghalt.sc）

・タナトスタワー7Fへの入場条件に追加職が含まれてなかったのを修正（npc_warp_dun.sc）

・悪夢のグラストヘイムへの入場条件に追加職が含まれてなかったのを修正（npc_quest_glastheim.sc）

・悪夢のグラストヘイム古城北口の入場地点にワープポイントが重なっているミスを修正（npc_quest_glastheim.sc）

----------------------------------------
//1405 [2020/03/05] by refis

・ゲフェニアのモンスター出現情報を最新のものに更新（npc_monster_gefenia.sc）

----------------------------------------
//1404 [2020/03/04] by refis

・取り巻きモンスターの歩行に関する修正（map.h, mob.c, skill.c）
	-> 取り巻きは本来歩けないモンスターも歩けるように補正する
	-> ランダム歩行の有効無効フラグを追加
	   取り巻きはランダム歩行を無効にし、主に追従する
	   エモーションによるモードの変更がある場合はランダム歩行を有効に戻す
	   (ex.オシリス->イシス)

----------------------------------------
//1403 [2020/03/04] by refis

・[RE] : クリティカルスラッシュの無属性補正が抜けてたのを修正（battle.c）

----------------------------------------
//1402 [2020/03/04] by refis

・[RE] : クリティカルスラッシュのダメージ計算式を修正（battle.c）

・[RE] : ラッシュアタック、エスクをスキル倍率加算式に修正（battle.c, status.c）

・[RE] : ラッシュアタックのDEX3倍をFlee2倍に修正（status.c）

・追加NPCスキルを2種実装（skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_unit_db.txt, battle.c, skill.c, unit.c）

・上記修正のmob_db対応（mob_db.txt, mob_skill_db.txt）

----------------------------------------
//1401 [2020/03/03] by refis

・VSのプロジェクトに実績関連ファイルの追加忘れがあったのを修正
（char*.dsp, map*.dsp, char-server.vcxproj, map-server.vcxproj）

----------------------------------------
//1400 [2020/03/03] by refis

・ドラム族スキル修正（skill_db.txt, skill_unit_db.txt, battle.c, skill.c）
	-> イヌハッカシャワーのモーション・スキルが動作しない
	-> イヌハッカメテオが通常メテオのままだった
	-> 群れの力の状態異常確率が低かった
	Thanks a lot Dallen さん

----------------------------------------
//1399 [2020/03/03] by refis

・ロックリッジNPC実装（npc_town_rockridge.sc）
	-> ロックリッジクエスト実装
	-> ロックリッジウィークリークエスト実装
	※交換NPC等一部未実装があるので注意してください

・ロックリッジ関連NPC追加 (npc_misc_kafra.sc)

・ロックリッジ追加マップのwarp更新 (npc_warp_dun.sc, npc_warp_fild.sc, npc_warp_town.sc)

・ロックリッジ追加マップのmapflag更新 (mapflag.sc)

・ロックリッジ追加マップのmonster出現定義追加 (npc_monster_rockrdg.sc, npc_monster_harboro.sc, npc_monster_rockmine.sc)

・item_dbのランダム更新 (item_db.txt, item_db2.txt)
	Thanks a lot kuura さん

・mob_dbの更新 (mob_db.txt, mob_skill_db.txt)

・quest_dbの更新 (quest_db.txt)

・atcommand_go_dbの更新 (atcommand_go_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1398 [2020/03/03] by refis

・クエストDBのWW:DD:HH:MM形式処理が正常動作ではなかった (quest.c)

----------------------------------------
//1397 [2020/03/02] by refis

・BaseLevelが151以降に得られるステータスポイントが
　少なくなっている問題を修正 (atcommand.c, pc.c)
	Thanks Dallen さん

----------------------------------------
//1396 [2020/03/01] by refis

・mob_dbのデータを更新 (item_db.txt)

・コンパイルエラーを修正 (clif.c)

----------------------------------------
//1395 [2020/03/01] by refis

・item_dbのテーブルを更新 (item_db.txt)

・PACKETVER[20181017]以降にクエストリスト用パケットを追加 (clif.c)

・[SQL] : キャストエラー修正 (sqldbs.c)

----------------------------------------
//1394 [2020/03/01] by refis

・quest_db.txt内のアイテムドロップモンスターが非討伐カウント対象の場合
　アイテムドロップしない設定抜けがあったので修正 (quest.c)

・一部MAPにおいてmapflag未設定があったミスを修正 (mapflag.sc, mapflag_memorial.sc)

----------------------------------------
//1393 [2020/03/01] by refis

・クエストリストの制限時間で形式処理を拡張 (doc/db_ref.txt, quest.c)
	-> HH:MM形式の追加、00:HH:MMと同意
	-> WW:DD:HH:MM形式の追加、DD回目のWW曜日HH時MM分

----------------------------------------
//1392 [2020/03/01] by refis

・[RE] : モンスターのLvとIntが反映されていなかったMATK計算式を修正（status.c）

・スキルリストが表示されない場合があるので、
　暫定でPACKETVER20190101以降のスキルリストパケット処理順序を入れ替え (clif.c)

----------------------------------------
//1391 [2020/02/29] by refis

・実績、称号システム実装
(common/mmo.h, achieve.*, map.*, mob.c, clif.*, friend.c, pc.c, pet.c, quest.c, vending.c, 
　conf/lua_auriga.conf, doc/db_ref.txt, db/achievement_db.lua, db/achievement_level_db.lua)

・セーブデータ対象に実績、称号関連情報を追加 (inter_auriga.conf, map/intif.*, char/inter.c, char/chardb_*.c, char/int_achieve.*, char/achievedb_*.*)

・SQL：DBに実績、称号関連追加
 (common/sqldbs.h, sql-files/main.sql, sql-files/drop_table.sql, sql-files/db_maintenance.sql,
　sql-files/convert_engine_myisam.sql, sql-files/convert_engine_innodb.sql, sql-files/Auriga1391_changetable.sql)

・TXT：JOURNAL_IDENTIFIERを19->20に引き上げ (journal.c)

・スクリプト命令に以下を追加（script.c, doc/script_ref.txt）
	achievement  : ACH_ADVENTUREタイプの実績を達成させます
	achievement2 : 指定タイプの実績を達成させます
	※詳しくはscript_ref.txtを参照

・luascriptシステムの調整（map.c, itemdb.*, luascript.*, db/item_randopt_db.lua）
	-> 現時点でDB利用しかしていないのでガベージコレクトの頻度を下げる
	-> 読み込み処理を改善し、エラー発生メッセージをわかりやすくする
	-> 実績DB実装に合わせて関数系を整理
	-> ランダムオプションの処理において登録処理と初期化を分離

----------------------------------------
//1390 [2020/02/27] by refis

・リベリオン実装（battle_auriga.conf, const.txt, scdata_db.txt,
　skill_cast_db.txt, skill_db*.txt, skill_require_db*.txt, skill_tree.txt,
　skill_unit_db.txt, mmo.h, atcommand.c, battle.*, clif.*, map.h,
　pc.*, skill.*, status.*, unit.c）

・リベリオン転職試験実装（map_auriga.conf, quest_db.txt, npc_job_48rebellion.sc）

・装備変更時に解除される状態異常を更新（pc.c）

・カートブーストが保存されるよう変更（scdata_db.txt）

・一部NPCスキル、サモナースキルの設定修正（skill_db2.txt）

・キャロットビート追加効果のダメージが下落する場合があったミス修正（battle.c）

・ピッキ突き追加効果の判定式が正しく動いてなかったのを修正（skill.c）

・キャロットビート、ピッキ突きのモーション修正（battle.c）

・ニャングラス再修正（skill_unit_db.txt, skill.c, status.c）

----------------------------------------
//1389 [2020/02/24] by refis

・[SQL] : キャラ削除時、クエストデータの削除漏れを修正（chardb_sql.c）

・clif_weight_limitは外部で使用していないためstaticにして隠す（clif.*）

・Patch1370以降、モンスターのグループ設定が反映されないミスを修正（mob.c）
	Thanks Dallen さん

・ニューマの持続時間が長すぎる問題を修正（skill.c）
	Issues Report #11 , Thanks eni-ro さん

・タロウの傷状態になったときクラッシュする問題を修正（status.c）
	Issues Report #12 , Thanks eni-ro さん

・typo fix（quest.c）

----------------------------------------
//1388 [2020/02/20] by refis

・対象指定スキル使用開始・終了[0xb10][0xb11]追加
（packet_db.lua, clif.c, map.h, skill.c）

----------------------------------------
//1387 [2020/02/20] by refis

・魔神の塔メモリアル実装（map_auriga.conf, mob_db.txt, mob_skill_db.txt, quest_db.txt, npc_memorial_towermorocc.sc）

・カードリムーバーNPC[ツーニャ]実装（map_auriga.conf, npc_quest_cardremover.sc）

・[インビジブル]は再使用で効果が切れないはずなので修正（skill.c, status.c）

・[マインドブラスター]の再使用待機時間が反映されてなかったのを修正（skill.c）

----------------------------------------
//1386 [2020/02/19] by refis

・typo修正（npc_memorial_cursedknight.sc）

・[大トロ]の回復量が表記より低く計算されていたのを修正（skill.c）

----------------------------------------
//1385 [2020/02/19] by refis

・呪いの剣士メモリアル実装（map_auriga.conf, memorial_db.txt, mob_db.txt, mob_skill_db.txt, npc_memorial_cursedknight.sc）

・サラの記憶メモリアルのクールタイムを初回5時に変更し、文章を更新（quest_db.txt, npc_memorial_sara.sc）

----------------------------------------
//1384 [2020/02/18] by refis

・スキル対象の名称参照が飛んでくることがあるのでエラー対策する（clif.c）

・[永久霜]状態異常を追加（const.txt, scdata_db.txt, status.*）

・[エビ三昧][大トロ]のHP回復表示処理を修正（skill.c）

・追加NPCスキルを16種実装
（scdata_db.txt, skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_unit_db.txt, battle.c, skill.*, status.*）

・[ベナムフォグ][フレイムクロス][パルスストライクII]スキルの挙動、持続時間を修正
（scdata_db.txt, skill_cast_db.txt, skill_unit_db.txt, battle.c, skill.c, status.*）

----------------------------------------
//1383 [2020/02/17] by refis

・次元の狭間 時の通路内NPCの更新（npc_quest_herovestige.sc）

----------------------------------------
//1382 [2020/02/17] by refis

・飛行船襲撃メモリアル実装（map_auriga.conf, memorial_db.txt, mob_skill_db.txt, npc_memorial_heroair.sc）

・ランダムオプションデータ最大数登録時のチェック修正（itemdb.c）

・packet_db.luaは直接読み込みするように変更（lua_auriga.conf, clif.c, luascript.*, map.c）

・VC++ 2019 のパスを追加（vc_make.bat）
	Thanks rinaserver さん

----------------------------------------
//1381 [2020/02/16] by refis

・スクリプト命令「opendressroom」に引数を指定できるよう変更（script_ref.txt, script.c）

・スクリプト命令「getoptitem」を追加（script_ref.txt, script.c）

・スクリプト関数「getrandombox」を追加（script_ref.txt, script.c）

・ランダムオプションデータのアイテムIDが誤っていたのを修正（item_randopt_db.lua）

・ランダムオプションデータのMOB_IDキーに存在しないモンスターIDも使えるように変更（luascript.c）

----------------------------------------
//1380 [2020/02/15] by refis

・OTPログイン「0xacf」追加（login.c）

・PACKETVER「20190530」追加
	-> MAX_PACKET_DBの拡張（clif.c）
	-> itemidの拡張に対応（clif.c）
	-> システム対応のためclif_send_equipopenをclif_send_configに変更（clif.*）
	-> 新規・変更パケット対応（mmo.h, map.h, clif.*, pc.c, pet.c, storage.c）
	-> キャラクターデータに「allow_call」「autofeed」を追加、保存させる
（main.sql, Auriga1380_changetable.sql, chardb_*.c, mmo.h, clif.c）

・受信パケットのエラー対策としてダミー関数を用意する（clif.c）

・戦闘設定「ping_timer_interval」「enable_pet_autofeed」「enable_hom_autofeed」追加
（battle_auriga.conf, battle.*, homun.c, pet.c）

・2019-05-30aRagexeREのpacket_dbを追加（packet_db.lua, Makefile, bcc32_make.bat, vc_make.bat, vc_make_appveyor.bat）

----------------------------------------
//1379 [2020/02/15] by refis

・clif_item_repaireffectのパケット構造の誤りを修正（atcommand.c, clif.*, skill.c）
	Thanks Dallen さん

・PACKETVER「20081126」以前のclif_send_petstatusのパケット構造の誤りを修正（clif.c）

・デバッグコマンド「@statall」使用時、サモナー用設定が適用されないミスを修正（atcommand.c）

・見えないNPCに対する条件式が逆転していたミスを修正（clif.c）

・Warning修正（luascript.c）
	Thanks rinaserver さん

----------------------------------------
//1378 [2020/02/12] by refis

・アイテムボーナス「bAllStatus」がバッファオーバーランを起こしていた問題を修正（bonus.c）

・2018-04-18bRagexeREのpacket_db定義漏れを修正（packet_db.lua）
	Issues Report #10 , Thanks eni-ro さん

----------------------------------------
//1377 [2020/02/10] by refis

・アイテムボーナス「bSubSkillDamageRate」、「bNoGearFuel」追加
（db/const.txt, doc/item_bonus.txt, bonus.c, map.h, battle.c, skill.c, status.c）

・BCCコンパイル時にdouble値が読み取れない問題の再修正（utils.h）
	Report #9 , Thanks eni-ro さん

----------------------------------------
//1376 [2020/02/07] by refis

・packet_dbをluaで読み込み処理するように改修（lua_auriga.conf, packet_db.lua, clif.*, luascript.c）

・2018-04-18bRagexeREのpacket_dbを追加（packet_db.lua, Makefile, bcc32_make.bat, vc_make.bat）

・アイテムドロップエフェクト用にitem_db2にテーブルを追加（item_db2.txt, itemdb.*）

----------------------------------------
//1375 [2020/02/06] by refis

・PACKETVERによるクエストリストの表示不具合を修正（clif.*, intif.c, quest.c）

・スクリプト命令[chgquest]発行先クエストで日数指定制限時間が使えなかったのを修正（quest.c）

----------------------------------------
//1374 [2020/02/06] by refis

・[64BIT] GRFサイズがMAX_INTを超える場合でも読み込みできるよう修正（grfio.c）

----------------------------------------
//1373 [2020/02/05] by refis

・カプラ職員の転送サービスで料金が0zenyの場合、転送先が現れないことがあったのを修正
（npc_misc_kafra.sc）

----------------------------------------
//1372 [2020/02/02] by refis

・mob_avail使用時に配列外参照が発生するミスを修正（mob.c）
	Report #8 , Thanks eni-ro さん

・BCCコンパイル時にdouble値が正常に読み取れなかった問題を修正（utils.h, pc.c）
	Report #9 , Thanks eni-ro さん

・BCCコンパイル時のエラー抑制（skill.c）

----------------------------------------
//1371 [2020/01/31] by refis

・mobdb_data終了時に領域を解放する（mob.c）

・reloadmobdb使用時にskillデータが初期化されないミスを修正（mob.c）

----------------------------------------
//1370 [2020/01/31] by refis

・MobIDでshort型以上のIDを扱えるように改修（map.h）
	-> mob_db構造体をmobdb_dataに名称変更しDB管理させる（mob.*）
	-> データ参照はmobdb_exists関数とmobdb_search関数を通す
	（atcommand.c, battle.c, clif.c, itemdb.c, luascript.c,
	  npc.c, pc.c, pet.c, script.c, skill.c, status.c）

・ItemIDでshort型以上のIDを扱えるように改修（map.h, itemdb.c）

・2017-08-30bRagexeREのpacket_dbを追加（packet_db.txt, Makefile, bcc32_make.bat, vc_make.bat）

----------------------------------------
//1369 [2020/01/30] by refis

・キャラクターのEXP,JEXPをatn_bignumberに対応（char.c, chardb_*.c, mmo.h, clif.c, pc.*, skill.c）

・メール添付アイテムのランダムオプションが保存されないミスを修正（maildb_*.c）

・[TXT] 倉庫内アイテムのランダムオプションが保存されないミスを修正（storagedb_txt.c）

・[SQL] データ長拡張用にテーブルの更新（main.sql, Auriga1369_changetable.sql）

----------------------------------------
//1368 [2020/01/30] by refis

・PACKETVER[20141022]以降のキャラクター表示パケットの調整 (clif.c)

----------------------------------------
//1367 [2019/11/02] by refis

・PACKETVER[20161228]の定義抜けを修正 (packet_db.txt)
	Thanks Dallen さん

・clif_skill_setunitの定義更新漏れを修正 (clif.c)
	Thanks Dallen さん

----------------------------------------
//1366 [2019/10/03] by refis

・マスター・スヌスの職業チェック修正 (npc_quest_ac_entrance.sc)
	Thanks rinaserver さん

・スクリプト命令「unittalk」の排他チェック強化 (script.c)
	Thanks rinaserver さん、Dallen さん

----------------------------------------
//1365 [2019/10/03] by refis

・BCCコンパイル時に存在しないenumのエラーが発生していたのを修正 (clif.*)
	Thanks Spica さん

・BCCコンパイル時にluaコンパイルが通らなかったのを修正 (bcc32_make.bat)
	Thanks Spica さん

----------------------------------------
//1364 [2019/09/28] by refis

・PACKETVER「20170502」以降のパーティメンバのパケット構造の誤りを修正 (clif.c)
	Thanks えとりり さん

・パーティメンバ追加時のデータ格納エラー修正 (int_party.c)
	Thanks えとりり さん

----------------------------------------
//1363 [2019/09/08] by refis

・item_db.txtの更新 (item_db.txt)

・上記更新分のitem_cardtype.txt定義追加 (item_cardtype.txt)

----------------------------------------
//1362 [2019/09/05] by refis

・スクリプト関数「getnpcid」の安全性が低かった点を修正 (script.c)

----------------------------------------
//1361 [2019/08/25] by refis

・港町ラザーニャへの転送NPCを追加 (npc_town_lasagna.sc)

・アカデミーNPCのドラム族対応を追加 (npc_quest_ac_*.sc, npc_warp_academy.sc)

----------------------------------------
//1360 [2019/08/25] by refis

・quest_dbの更新 (quest_db.txt)

----------------------------------------
//1359 [2019/08/25] by refis

・サモナー用チュートリアルクエスト実装（npc_job_49summoner.sc）

・港町ラザーニャNPC実装（npc_town_lasagna.sc）

・ラザーニャ関連NPC追加 (npc_misc_kafra.sc, npc_misc_pointshop.sc, npc_misc_refine.sc, npc_quest_hairstylist.sc)

・ラザーニャ追加マップのwarp更新 (npc_warp_dun.sc, npc_warp_fild.sc, npc_warp_town.sc)

・ラザーニャ追加マップのmapflag更新 (mapflag.sc)

・ラザーニャ追加マップのmonster出現定義追加 (npc_monster_lasafild.sc, npc_monster_lasadun.sc)

・mob_dbの更新 (mob_db.txt, mob_skill_db.txt)

・quest_dbの更新 (quest_db.txt)

・atcommand_go_dbの更新 (atcommand_go_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

・ドラム族スタート地点を変更 (char_auriga.conf)

・婚礼品NPCの販売リスト修正 (npc_town_prontera.sc, npc_town_lighthalzen.sc)

----------------------------------------
//1358 [2019/08/21] by refis

・ピラミッドナイトメア2Fの隠しワープ起動時の発言処理を修正（npc_quest_pryd_nm.sc）

・スクリプト命令「mobuseskillpos」実装（script.c, script_ref.txt）

・スクリプト関数「getnpcid」実装（script.c, script_ref.txt）

・スクリプト命令「unittalk」で発言の可視対象を指定できるよう拡張（clif.*, script.c, script_ref.txt）

----------------------------------------
//1357 [2019/08/20] by refis

・サモナースキル[かくれる]使用中の挙動修正（clif.c）

・サーバー情報通知のパケット誤りを修正（clif.c）

・スクリプト命令「cloakonnpc」「cloakoffnpc」実装（clif.c, script.c, script_ref.txt）

----------------------------------------
//1356 [2019/08/19] by refis

・Patch 1355 follow up（npc_misc_pointshop.txt）

----------------------------------------
//1355 [2019/08/19] by refis

・ポイントショップ関連NPCのサモナー対応（npc_misc_pointshop.txt）

・ジェレミーの美容クーポン及び関連NPC実装（item_db.txt, npc_misc_pointshop.txt）

----------------------------------------
//1354 [2019/08/08] by refis

・名もなき島の配置情報を更新（mob_db.txt, mob_skill_db.txt, npc_monster_nameless.txt）

・修道院2Fのワープを追加（npc_warp_dun.txt）

----------------------------------------
//1353 [2019/08/05] by refis

・プロンテラへの帰還、タナトスタワーへの帰還スキルを実装
（skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_require_db.txt, skill.c）

・キャラクター削除時、非対象の削除予約キャラクターの表示がおかしくなるミスを修正（char.c）
	Thanks Dallen さん

----------------------------------------
//1352 [2019/08/05] by refis

・アカデミーNPCを更新
	-> マスター・スヌスを実装（npc_quest_ac_entrance.sc）
	-> [卒業証書]実装（npc_job_transmigration.sc）
	-> 関連NPCの処理調整（npc_job_thirdclass.sc）

・上記に合わせてセージキャッスル内のランダムワープを廃止（npc_warp_town.sc）

・item_db.txtの更新（item_db.txt, function_itemdb.sc）

・quest_db.txtの更新（quest_db.txt）

----------------------------------------
//1351 [2019/08/05] by refis

・戦闘設定[gm_all_skill]をデフォルトで0にする（battle_auriga.conf）
	-> GMアカウントでサモナーキャラクターを作成したときのエラー対策として

----------------------------------------
//1350 [2019/08/03] by refis

・スキル[イリュージョンドーピング]習得条件のミスを修正（skill_tree.txt）

・サモナーが応急手当を覚えられなかったのを修正（skill_tree.txt）

・サモナーのステータスとASPDの上限設定項目を追加（battle_auriga.conf, battle.*, pc.c, status.c）

----------------------------------------
//1349 [2019/07/25] by refis

・アイテムクールタイムが正常動作しない場合があったので修正（pc.c）
	Thanks Excella さん

・クエストDBの制限時間で日時指定できるように拡張（quest.*）

・quest_db.txtの説明がなかったので追加（db_ref.txt）

----------------------------------------
//1348 [2019/07/25] by refis

・アイテムクールタイムを実装（item_db2.txt, db_ref.txt, itemdb.*, map.h, pc.c）

----------------------------------------
//1347 [2019/07/25] by refis

・PACKETVER「20141022」以前でコンパイルエラーが起こる問題修正（clif.c）

----------------------------------------
//1346 [2019/07/25] by refis

・Hat_Effect表示「0xa3b」を追加（clif.*）
	-> スクリプト命令「hateffect」実装（map.h, pc.c, script.c, status.h, script_ref.txt, const.txt）
	Thanks Excella さん

・露店開設中に別の露店を開けないよう修正（clif.c）

----------------------------------------
//1345 [2019/07/20] by refis

・一部ドラム族スキルをno_magic_damage無効に修正（skill.c）

・ドラム族スキル「大トロ」の処理ミスを修正（skill.c）

----------------------------------------
//1344 [2019/07/20] by refis

・ピラミッドナイトメア実装
（map_auriga.conf, mob_db.txt, mob_skill_db.txt, mapflag.sc, npc_monster_mocpryd.sc, npc_quest_pryd_nm.sc）

・次元の狭間 時の通路01にtownフラグを追加（mapflag.sc）

----------------------------------------
//1343 [2019/07/16] by refis

・ワープポータルが使用できなくなっていたのを修正（skill_db2.txt）
	Thanks rinaserver さん

・発行済みcompquestが存在するとクエストリストがクラッシュするエラーを修正（clif.c）
	Thanks れる、Dallen さん

・マタタビランスが無属性固定のミスを修正（battle.c）
	Thanks Excella さん

----------------------------------------
//1342 [2019/07/11] by refis

・装備解除時に発行するスクリプトを設定できるようDBを拡張（itemdb.*, pc.c）
	-> 既存DBと互換性があるので不使用の場合は記載しなくても大丈夫です

----------------------------------------
//1341 [2019/07/07] by refis

・サラの記憶、古のグラストヘイムの会話パートスキップの選択肢を追加（npc_memorial_glastheim.sc, npc_memorial_sara.sc）

----------------------------------------
//1340 [2019/07/03] by refis

・PACKETVERが20160921以降の状態で露店を閲覧したときにクラッシュする可能性があったのを修正（clif.c）
	Thanks Dallen さん

----------------------------------------
//1339 [2019/07/03] by refis

・mob_avail.txtでプレイヤーキャラクター指定時にセカンドコスチュームを選べるよう拡張（mob_avail.txt, mob.*）

----------------------------------------
//1338 [2019/05/12] by refis

・サモナーと他職業の相互転職をできなくしておく（pc.c）

----------------------------------------
//1337 [2019/05/06] by refis

・リファレンスの更新漏れを訂正（db_ref.txt）

・2015-10-29aRagexeRE、2016-12-28aRagexeRE、2017-06-14bRagexeREのpacket_dbを追加（packet_db.txt）
	-> 構造体「party_member」に「class_」を格納するよう追加（mmo.h）
	-> パケット拡張、新規追加に対応（login.c, int_party.c, intif.c, party.*, clif.c）
	-> 内部パケットの拡張（int_party.c, inter.c, intif.c）
	-> 足りなくなるのでMAX_PACKET_DBの拡張（clif.c）

・新パケットのエラー対策でダミー関数を用意する（clif.c, packet_db.txt）

・PACKETVERを「20151029」に引き上げ（bcc32_make.bat Makefile vc_make.bat *.dsp）

----------------------------------------
//1336 [2019/05/06] by refis

・サモナー追加関連アイテムを追加（item_db.txt, item_db2.txt）

・MAX_ITEMGROUPを15に拡張（item_group_db.txt, map.h）

・3次職追加スキル、サモナースキルをskill_tree.txtに追記（skill_tree.txt）

----------------------------------------
//1335 [2019/05/05] by refis

・イヌハッカシャワー、イヌハッカメテオの効果がなかったのを修正（skill_unit_db.txt, skill.c, status.c）

----------------------------------------
//1334 [2019/05/04] by refis

・レッケンベル社の噂クエストの討伐判定ミスで進行できなかったのを修正（npc_memorial_worsef.sc）

・luascript終了処理のチェックを強化（luascript.c）

----------------------------------------
//1333 [2019/05/04] by refis

・ニャングラス、警戒の効果がなかったのを修正（skill_cast_db.txt, skill_unit_db.txt, skill.*, status.c）

・アクラウスダッシュの遠距離攻撃力増加判定を修正（battle.c）

・Patch 1332 follow up（battle.c）

----------------------------------------
//1332 [2019/05/01] by refis

・ログイン認証処理を調整（char.c）

・clif_addskill、clif_delskillを追加（clif.*）

・クールダウン計算をskill_cooldownfixとして分離させる（skill.*）

・status_get_jlvを追加して直接参照を避ける（battle.c, status.*）

・ドラム族DB修正（scdata_db.txt, skill_cast_db.txt, skill.txt）

・ドラム族SCRIPT準備（script/npc/*）

・ドラム族SKILL準備（src/common/mmo.h, src/map/*）

----------------------------------------
//1331 [2019/04/05] by refis

・非消費アイテムが消費されてしまっていたのを修正（item_db2.txt）

・NULL判定が正しくないのを修正（clif.c）

・DB上の定義ミスを修正（skill.txt, skill_require_db.txt）

・DB更新に合わせてドラム族DB準備（skill_cast_db.txt, skill.txt, skill_require_db.txt）

----------------------------------------
//1330 [2019/01/03] by refis

・1次転職時のアカデミー関係メッセージを表示させる（npc/job/*）

・typo修正（npc_quest_ac_agent.sc）

----------------------------------------
//1329 [2018/12/30] by refis

・コンパイルエラーの修正（pc.c）

・傭兵にロキのデータを追加（merc_db.txt, merc_skill_tree.txt）

----------------------------------------
//1328 [2018/12/29] by refis

・exp_tableが正常に読み込まれない不具合を修正（pc.c）
	#6 , Thanks niconicop さん

----------------------------------------
//1327 [2018/12/16] by refis

・memorial_db.txtの更新（memorial_db.txt, memorial.c）

・傭兵スキル「マインドブラスター」実装
（skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_require_db.txt, mmo.h, skill.c）

----------------------------------------
//1326 [2018/12/15] by refis

・クライアント対応、リベリオン、ドラム族準備
（char_auriga.conf, const.txt, job_*_db.txt, main.sql, Auriga1326_changetable.sql,
  char.*, chardb_*.*, journal.c, mmo.h, clif.c, pc.*）

・typo修正（script.c）

・clif_changeoption_singleの追加（clif.*）

・キングスグレイス状態の相手に攻撃するときはパケット段階で遮断させる（clif.c）

・バイタリティアクティベーションのSP回復量を修正（pc.c）

・各職のレベル限界、ステータス限界、必要経験値をRRに対応（battle_auriga.conf, exp.txt, pc.c）

・ジョブ補正値をRR対応（job_db*.txt）

----------------------------------------
//1325 [2018/12/14] by refis

・イリュージョンドーピングの射程、使用時エラー修正（skill_db.txt, skill.c, status.c）

・マグマエラプション盗作エラー修正（skill.c）

・ニューマのエフェクト問題解決のため処理を少し変えてみる（skill_unit_db.txt, skill.c）

----------------------------------------
//1324 [2018/12/13] by refis

・スキルをRR仕様に修正
（scdata_db.txt, skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_require_db.txt, skill_unit_db.txt, battle.c, skill.c, status.*, unit.c）

----------------------------------------
//1323 [2018/12/09] by refis

・転生時に騎乗生物のチェック抜けがあったので修正（npc_job_transmigration.sc）

・スキルのRR仕様へ修正の続き
（skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_require_db.txt, skill_unit_db.txt, battle.c, skill.*, status.c）

----------------------------------------
//1322 [2018/12/03] by refis

・モンスター使用スキルを修正（mob_skill_db.txt）

・アイテムグループを追加（item_group_db.txt, map.h）

・状態異常アイコンを更新（status.*）

・スキルのRR仕様へ修正の続き
（skill_cast_db.txt, skill_db.txt, skill_db2.txt, skill_require_db.txt, skill_require_db2.txt, battle.c, skill.*, status.*）

・NPCスキル[フレイムクロス]、[パルスストライクII]、[ダンシングブレード]、
　[ダークピアーシング]、[デスサモン]を実装
（skill_cast_db.txt, skill_db.txt, skill_unit_db.txt, battle.c, skill.c, status.c）

----------------------------------------
//1321 [2018/11/30] by refis

・キャラクター削除待機時間を10秒に修正（char_auriga.conf）

・セカンドコスチュームNPCを更新（npc_misc_pointshop.sc）
	Thanks magnus さん

・上位の次元ブーツにスロットエンチャントしたときの交換不具合を修正（npc_quest_glastheim.sc）
	Thanks rinaserver さん

----------------------------------------
//1320 [2018/11/07] by refis

・ホラーおもちゃ工場実装 (map_auriga.conf, npc_memorial_horroroftoy.sc)
	-> 関連アイテム交換NPC実装 (npc_town_lutie.sc)
	-> item_db, monster_dbの更新 (item_db.txt, item_random.txt, mob_db.txt, mob_skill_db.txt)
	-> const.txtの更新 (const.txt)
	-> mapflagの更新 (mapflag_memorial.sc)
	-> quest_dbの更新 (quest_db.txt)

----------------------------------------
//1319 [2018/11/04] by refis

・ヴェルキリーヘルム作成NPCを更新（npc_quest_hat5.sc）

・パイルバンカー作成NPCを追加（map_auriga.conf, npc_quest_pilebunker.sc）

----------------------------------------
//1318 [2018/11/03] by refis

・スクリプト関数「unequip」を拡張
	-> -2と-3指定で取り外し範囲を変えられるようにしました（doc/script_ref.txt, script.c）

・カプラ職員メニューに装備取り外し、倉庫設定変更を追加（quest_db.txt, npc_misc_kafra.sc）
	-> 倉庫メニューの表示形式も合わせて更新

・上記追加に合わせてfunction利用ファイルを更新

----------------------------------------
//1317 [2018/10/27] by refis

・スクリプト関数「getmercinfo」実装（doc/script_ref.txt, script.c）

・アイテムエクスチェンジNPC追加（npc_quest_exchange.sc）

----------------------------------------
//1316 [2018/04/11] by refis

・影狼、朧転職試験用モンスターが再出現しないミスを修正（npc_job_47kaboro.sc）

----------------------------------------
//1315 [2017/10/16] by refis

・トキシン、パイレクシア状態の挙動を修正（status.c）
	Thanks hikaru1112 さん

・阿修羅覇凰拳の挙動を修正（skill.c）
	Thanks ねぴぴ さん

----------------------------------------
//1314 [2017/10/16] by refis

・モンスタースキル使用条件[afterskill], [masterattacked]実装（doc/db_ref.txt, mob.*）

----------------------------------------
//1313 [2017/10/16] by refis

・アイテムボーナス「bAllStatus」追加（db/const.txt, doc/item_bonus.txt, bonus.c, map.h）

・アイテムボーナスの属性設定にEle_Allを追加（db/const.txt, doc/item_bonus.txt, bonus.c, map.h）
	-> 未実装のEle_Randomを削除

・ミンストレルのJob補正値の誤りを修正（db/job_db2.txt, db/job_db2-2.txt）
	Thanks mcrx さん

----------------------------------------
//1312 [2017/10/15] by refis

・ノンアクティブモンスターの多くが非反撃状態だったミスを修正（mob_db.txt）

----------------------------------------
//1311 [2017/10/15] by refis

・スキル[風魔手裏剣乱華]がドレイン効果を発揮しない不具合を修正（battle.c）
	Thanks ねぴぴ さん

・MobオプションAI[MDOPT_NOATTACK]の処理位置を調整（mob.c, unit.c）

----------------------------------------
//1310 [2017/10/15] by refis

・デフォルトで[PRE_RENEWAL]を外すよう変更（bcc32_make.bat, Makefile, vc_make.bat）

----------------------------------------
//1309 [2017/10/15] by refis

・アイテムボーナス「bMagicAddSize」追加（db/const.txt, doc/item_bonus.txt, battle.c, bonus.c, map.h, status.c）

・ランダムオプションボーナスをenumで整理（bonus.c, map.h）

----------------------------------------
//1308 [2017/10/15] by refis

・bonus4 bAutoSpellにEAS_CONDITIONを追加（db/const.txt, doc/item_bonus.txt, bonus.*）
	-> スキル使用条件をチェックさせる
	-> SP消費もチェックするため、通常はEAS_NOSPも指定してください

・オートスペルでハイネスヒールをアンデットに使用時にも回復させていた問題を修正（bonus.c）

----------------------------------------
//1307 [2017/10/15] by refis

・アイテムボーナスの種族設定にRct_Playerを追加（db/const.txt, doc/item_bonus.txt, battle.c, map.h）

・atcommand.cの型変換エラーを修正（atcommand.c）

----------------------------------------
//1306 [2017/10/06] by refis

・パーティ情報読み込み時にmemorial_idをチェックするように強化（memorial.*, party.c）

----------------------------------------
//1305 [2017/09/24] by refis

・item_randopt_db.luaにデータを追加できないミスを修正（item_randopt_db.lua）
	Thanks Alt さん

・ランダムオプションのコンパイルエラーを修正（bonus.c）
	Thanks wool さん、mcrx さん

----------------------------------------
//1304 [2017/09/24] by refis

・item_db.txt, item_db2.txt, item_cardtype.txtの更新
	Special Thanks mcrx さん!!

----------------------------------------
//1303 [2017/08/16] by refis

・mob_db.txt, item_db.txtの更新
	Special Thanks mcrx さん!!

----------------------------------------
//1302 [2017/07/23] by refis

・skill_db2.txtの更新（skill_db2.txt）
	Thanks sango さん

・IDリストの更新（skill.h, status.h）

----------------------------------------
//1301 [2017/07/23] by refis

・ランダムオプションシステムの実装
 (lua_auriga.conf, bonus.*, itemdb.*, luascript.c, map.h, mob.c, status.c, db/item_randopt_db.lua)

・db_ref.txtの更新（db_ref.txt）
	Thanks mcrx さん

・ビルド中のワーニングを修正（vc_make.bat, vc_make_appveyor.bat）
	Thanks mcrx さん

・item_db更新時に余分なスロットが変更されていた箇所を訂正（item_db.txt）

----------------------------------------
//1300 [2017/07/22] by refis

・luascriptシステムの実装準備 (Auriga-14.sln, vc_make.bat, vc_clean.bat, bcc32_make.bat, bcc32_clean.bat, map.c, luascript.*, lua_auriga.conf, common/lua)

----------------------------------------
//1299 [2017/07/22] by refis

・討伐系クエストでクラッシュしてしまう不具合を修正 (quest.*)
	Thanks rinaserver さん、dallen さん

----------------------------------------
//1298 [2017/07/22] by refis

・生体工学研究所出現モンスターのスペル誤りを訂正 (npc_monster_lhzdun.sc)

・mob_db.txt, mob_skill_db.txt, skill_db.txt, skill_db2.txtの更新
	Special Thanks mcrx さん!!

・新規アイテム群のIDのみ追加更新

----------------------------------------
//1297 [2017/06/02] by refis

・一部ダンジョンのモンスター出現情報のミスを修正 (monster/dungeon/*)

----------------------------------------
//1296 [2017/03/29] by refis

・一部フィールド・ダンジョンのモンスター出現情報を更新 (monster/dungeon/*, monster/field/*)

----------------------------------------
//1295 [2017/03/21] by refis

・2016/09/20配置変更、ステータス調整に対応
 (mob_db.txt, npc_monster_magdun.sc, npc_monster_paydun.sc, npc_monster_thor.sc)

・クラーケン関連の座標を調整 (npc_monster_izdun.sc)

----------------------------------------
//1294 [2017/03/21] by refis

・2015/10/13、2017/02/21配置変更、ステータス調整に対応
 (mob_db.txt, mob_skill_db.txt, npc_monster_gefdun.sc, npc_monster_izdun.sc, npc_monster_lhzdun.sc)
	Thanks ARIA さん

----------------------------------------
//1293 [2017/03/21] by refis

・冒険者アカデミーNPC実装 (quest/academy/*)
	-> 初心者修練場を撤去 (npc_job_00novice.sc, npc_warp_town.sc)
	Special Thanks Pneuma さん!!

・冒険者アカデミー追加マップのmapflag更新 (mapflag_academy.sc)

・冒険者アカデミー追加マップのwarp追加 (npc_warp_academy.sc)

・冒険者アカデミー追加マップのmonster出現定義追加 (npc_monster_academy.sc)

・map_auriga.conf更新 (map_auriga.conf)

・quest_db.txt更新 (quest_db.txt)

----------------------------------------
//1292 [2017/03/20] by refis

・経験値リセットNPC [闇魔術師]実装 (npc_misc_reset.sc, map_auriga.conf)

・セカンドコスチュームNPCを更新 (npc_misc_pointshop.sc)

----------------------------------------
//1291 [2017/03/20] by refis

・時計塔ナイトメアNPC実装 (npc_town_aldebaran.sc)

・時計塔ナイトメア追加マップのmapflag更新 (mapflag.sc)

・時計塔ナイトメア追加マップのmonster出現定義追加 (npc_monster_ctower.sc)

・mob_dbの更新 (mob_db.txt, mob_skill_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

・VS2012ソリューションファイル名を修正 (Auriga-11.sln)

----------------------------------------
//1290 [2017/03/12] by refis

・ミストレス出現マップの誤りを修正（npc_monster_mjolnir.sc）

・モンスター定義を更新（mob_db.txt, mob.h）

----------------------------------------
//1289 [2017/02/06] by refis

・[ルーンナイト]、[ギロチンクロス]スキルのダメージ倍率を修正（battle.c, skill.c）

----------------------------------------
//1288 [2017/01/30] by refis

・不要ファイルの削除（db/pre/refine_db.txt）

----------------------------------------
//1287 [2017/01/28] by refis

・メモリアルダンジョン削除時に他のメモリアルデータが壊れる可能性があったのを修正
（memorial.c）
	Thanks akayumi さん

----------------------------------------
//1286 [2017/01/28] by refis

・スクリプト命令「getmapxy」でMOBオブジェクトを指定できるように拡張（doc/script_ref.txt, script.c）

・スクリプト命令「dropitem2」実装（doc/script_ref.txt, script.c）

----------------------------------------
//1285 [2016/11/25] by refis

・サラの記憶NPC実装 (npc_memorial_sara.sc)
	-> レイヤン・ムーアクエスト実装 (npc_quest_herovestige.sc, npc_quest_ashvacuum.sc)

・サラの記憶追加マップのmapflag更新 (mapflag.sc, mapflag_memorial.sc)

・mob_dbの更新 (mob_db.txt)

・quest_dbの更新 (quest_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1284 [2016/11/23] by refis

・エクラージュNPC実装 (npc_town_eclage.sc, npc_memorial_hometree.sc)
	-> 冒険者達との出会いクエスト実装
	-> 夢見る作家クエスト実装
	-> エクラージュの王クエスト実装
	-> 美しさの代償クエスト実装
	-> 妖精たちの事件簿クエスト実装
	-> 悠久なる絆クエスト実装
	-> エクラージュの悪戯キッズクエスト実装
	-> ラフィネ流ガーデニングクエスト実装
	-> 塔に挑んだ冒険者達クエスト実装
	-> 塔の中の冒険者クエスト実装
	-> プロフェッサーワームの記憶クエスト実装

・エクラージュ関連NPC追加 (npc_job_thirdclass.sc)

・エクラージュ追加マップのwarp更新 (npc_warp_dun.sc, npc_warp_fild.sc, npc_warp_town.sc)

・エクラージュ追加マップのmapflag更新 (mapflag.sc, mapflag_memorial.sc)

・エクラージュ追加マップのmonster出現定義追加 (npc_monster_eclfild.sc, npc_monster_ecltdun.sc)

・item_dbの更新 (item_db.txt, item_db2.txt)

・quest_dbの更新 (quest_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

・Auriga-1283のACCESS_VIOLATION修正 (quest.c)

----------------------------------------
//1283 [2016/11/22] by refis

・quest_dbでのアイテムドロップの追加拡張 (quest_db.txt, quest.*)

・Auriga-1280追加アイテムのミスを修正（item_db.txt）

・Auriga-1276で使わなくなった変数の削除忘れを修正（skill.c）

----------------------------------------
//1282 [2016/11/12] by refis

・Auriga-1281のコンパイルエラーを修正 (npc.c)

----------------------------------------
//1281 [2016/11/12] by refis

・NPCの周囲で露店やチャットを開けなくするかどうかを戦闘設定に追加 (battle_auriga.conf, battle.*, clif.c, npc.*, skill.c)

・騎乗中はアイコンを表示するように修正 (status.c)

----------------------------------------
//1280 [2016/11/08] by refis

・グラストヘイムメモリアルアップデートに対応 (map_auriga.conf, npc_memorial_glastheim.sc, npc_quest_glastheim.sc)
	-> モンスター出現情報を追加変更 (npc_monster_glast.sc)
	-> item_db, monster_dbの更新 (item_db.txt, mob_db.txt, mob_skill_db.txt)
	-> mapflagの更新 (mapflag.sc, mapflag_memorial.sc)
	-> quest_dbの更新 (quest_db.txt)

・script_ref.txtの更新ミスを修正（script_ref.txt）

----------------------------------------
//1279 [2016/11/08] by refis

・item_db.txtに新規アイテム群のIDだけ追加しておく（item_db.txt）

・hideonnpcに関する仕様変更（npc.c, script_ref.txt）
	-> disablenpcと差別化のためhide中のNPCはイベント実行を受け付けるように変更
	-> ex. killイベント、doevent系

----------------------------------------
//1278 [2016/11/06] by refis

・changematerial_db.txtの更新（changematerial_db.txt）

----------------------------------------
//1277 [2016/10/26] by refis

・スキル関連DBをRR仕様に修正（skill_cast_db.txt, skill_db.txt, skill_require_db.txt）

----------------------------------------
//1276 [2016/10/25] by refis

・スキル[マナリチャージ]を装備効果と加算処理するよう修正（skill.c, status.c）
	Thanks ARIA さん

・スキル[転生一次職業の魂]の効果を修正（skill.c, status.c）
	Thanks SOLDIER_POPORING さん

・[RE]:スキル[ハイディング]のSP消費時間を修正（status.c）

----------------------------------------
//1275 [2016/10/25] by refis

・Lv100以下のプレイヤーのAspdをmax_aspdに補正するかどうかを戦闘設定に追加（conf/battle_auriga.conf, battle.*, status.c）
	Thanks rapis さん

----------------------------------------
//1274 [2016/10/25] by refis

・atcommand_go_db.txtの更新（atcommand_go_db.txt）

・changematerial_db.txtの更新（changematerial_db.txt）

・produce_db.txtの更新（produce_db.txt）

----------------------------------------
//1273 [2016/10/25] by refis

・モンスターが対象指定スキル詠唱完了時に距離チェックさせる（mob.c）

・msgstringtable表示「0x7e2」を追加（clif.*）

----------------------------------------
//1272 [2016/10/24] by refis

・scriptフォルダ以下のファイル拡張子を.scにリネームする（conf/map_auriga.conf, script/*）
	-> 中身はテキストのままですが、エディタの表示設定を反映させやすくするため変更

----------------------------------------
//1271 [2016/07/31] by refis

・パーティ情報受信時にmemorial_idが消失する問題を修正（party.c）
	Thanks yucco さん

----------------------------------------
//1270 [2016/03/10] by refis

・NPCスキル[リバース]状態で死亡した際のNPCSCRIPTが走る条件式を修正（mob.c）

----------------------------------------
//1269 [2016/03/09] by refis

・2015-05-13aRagexeのpacket_dbに定義抜けがあったのを修正（packet_db.txt）
	Thanks rinaserver さん、dallen さん

・itembonus「bMagicAddGroup」実装
（const.txt, doc/item_bonus.txt, battle.c, bonus.c, map.h, status.c）
	Thanks siong さん

----------------------------------------
//1268 [2016/02/28] by refis

・Auriga-1267のバグfix（npc.c）

----------------------------------------
//1267 [2016/02/28] by refis

・npc_misc_pointshop.txtの処理誤りを修正（npc_misc_pointshop.txt）
	Thanks mcrx さん

・NPC名長エラーが頻発するため、MDで複製されたNPCの命名規則を変更（npc.c）
	（旧）元のNPC名 + _(ハイフン) + 3桁整数
	（新）mdnpc_ + 3桁整数 + _(ハイフン) + 複製元NPCのobject_id

・上記変更に伴って getmdnpcname関数の戻り値を上記命名規則に沿ったものを返すようにする（script.c）

----------------------------------------
//1266 [2016/02/22] by refis

・[pre]:クァグマイアのステータス減少効果が割合になっていなかったのを修正（status.c）
	Thanks ねぴぴ さん

・デフォルトカラーチケット、エクストラカラーチケット用のNPCを実装（npc_misc_pointshop.txt）
	-> ついでに服色の保存をデフォルトで有効にする（battle_auriga.conf）

----------------------------------------
//1265 [2016/02/19] by refis

・[RE]:上限レベルに達している際の最大保有可能経験値を99,999,999にする（pc.c）

・トール火山ダンジョンの配置情報を更新修正（npc_monster_thor.txt）

----------------------------------------
//1264 [2016/01/25] by refis

・expテーブルデータが誤っているのを修正（db/exp.txt）
	Thanks Cocoa さん

・神器3次クエストの吟遊詩人と会話時のエラーを修正（npc_quest_artifacts.txt）
	Thanks rinaserver さん

----------------------------------------
//1263 [2016/01/18] by refis

・PACKETVERによって他キャラのセカンドコスチュームが見えなかったのを修正（clif.c）
	Thanks LunarPhantom さん

----------------------------------------
//1262 [2016/01/17] by refis

・Auriga-1257の同梱漏れを修正（pc.c）

・Auriga-1260で更新が巻き戻っていたのを修正（pc.c）

----------------------------------------
//1261 [2016/01/15] by refis

・Auriga-1259のモンスターデータを一部修正（mob_db.txt, mob_skill_db.txt）

----------------------------------------
//1260 [2016/01/14] by refis

・typo修正（skill_cast_db.txt, skill_db.txt, skill_require_db.txt, skill_require_db2.txt）
	Thanks siong さん

・森の中の秘密クエストが進行できない不具合を修正（npc_town_portmalaya.txt）
	Thanks rinaserver さん

・skill_require_dbの使用可能武器種別が上書きできない不具合を修正（skill.c）
	Thanks ねぴぴ さん

・モンスターID最大値の定数を3601に更新（mob.h）

----------------------------------------
//1259 [2016/01/14] by refis

・モンスターデータを暫定で更新（mob_db.txt, mob_skill_db.txt）

・一部地域のモンスター配置情報を更新（script/monster/*）

----------------------------------------
//1258 [2016/01/14] by refis

・経験値テーブル変更に対応（exp.txt, exp_guild.txt, exp_homun.txt）
	-> 経験値獲得アイテムデータ更新 (item_db.txt)
	-> クエスト獲得経験値を分割対応 (script/npc/*)

・一部職業の基礎攻撃速度変更に対応（job_db1.txt）

・一部テレポート不可MAPのmapflag更新（mapflag.txt）

・pet_dbの更新（pet_db.txt）

----------------------------------------
//1257 [2016/01/03] by refis

・新パケットのエラー抑制（clif.c, map.h, packet_db.txt）

・スペシャルアイテムNPC追加（npc_misc_pointshop.txt）

----------------------------------------
//1256 [2015/12/31] by refis

・ヴェルゼブブの羽、オルレアンのフルコース、コスチュームチェンジチケット実装
　（const.txt, item_db.txt, item_db2.txt, scdata_db.txt, script_ref.txt, script.c, status.*）

・スペシャルアイテム関連NPCの追加更新（npc_misc_pointshop.txt）

・キャラクターセレクト画面でセカンドコスチュームが表示されないミスを修正（char.c）

----------------------------------------
//1255 [2015/12/31] by refis

・PACKETVER「20150513」でのキャラクター作成、削除時パケットの修正（char.c）

----------------------------------------
//1254 [2015/12/30] by refis

・2015-05-13aRagexeのpacket_dbを追加（clif.*, packet_db.txt, bcc32_make.bat, vc_make.bat）

・セカンドコスチュームシステム実装（doc/script_ref.txt, mmo.h, chardb_sql.c, chardb_txt.c, clif.*, pc.*, Auriga1254_changetable.sql, main.sql）

・ランダムオプションシステムの実装準備（mmo.h, chardb_sql.c, chardb_txt.c, clif.*, Auriga1254_changetable.sql, main.sql）

・ドレスルーム表示「0xa02」を追加（clif.c）

・ワンクリック鑑定「0xa35」を追加（packet_db.txt, clif.c）

・新パケットのエラー対策でダミー関数を用意する（clif.c, packet_db.txt）

・ジャーナルの更新（journal.c）

----------------------------------------
//1253 [2015/12/29] by refis

・「0x22e」の上位互換「0x9f7」を追加（clif.c）

・「0x2b1」の上位互換「0x97a」を追加（clif.c, intif.c, quest.c）

----------------------------------------
//1252 [2015/12/28] by refis

・2014-10-22bRagexeのpacket_dbを追加（vc_make.bat, char.c, packet_db.txt）

・「0x13d」の上位互換「0xa27」を追加（clif.c）

----------------------------------------
//1251 [2015/12/28] by refis

・Auriga-1250のコンパイルエラーを修正 (script.c)

・mob_skill_dbについて、省略可能な値6を定義できるようにテーブルを拡張 (doc/db_ref.txt, mob.*)

・生体工学研究所モンスタースキルを修正 (mob_skill_db.txt)

・NPCスキル「ライフストリーム」の表示形式を修正（skill.c）

----------------------------------------
//1250 [2015/12/28] by refis

・mob_skill_dbのミスを修正 (mob_skill_db.txt)

・最大モンスタースキル数を49 -> 54へ拡張 (map.h)

・スクリプト関数「checkre」実装（doc/script_ref.txt, script.c）

----------------------------------------
//1249 [2015/12/28] by refis

・生体工学研究所拡張アップデートに対応
	-> 研究所進入クエスト、呪われた魂クエストをクエストリストに対応 (quest_db.txt, npc_town_lighthalzen.txt)
		※クエストフラグに若干の拡張があります
	-> レッケンベル社の噂クエスト関連NPCを追加 (quest_db.txt, npc_town_lighthalzen.txt)
	-> 禁忌の研究室NPC実装 (map_auriga.conf, npc_memorial_worsef.txt)
	-> モンスター出現情報を追加変更 (npc_monster_lhzdun.txt)
	-> item_db, monster_dbの更新 (item_db.txt, mob_db.txt, mob_skill_db.txt)

----------------------------------------
//1248 [2015/11/22] by refis

・モーラエンチャント関連NPCを追加 (npc_town_mora.txt)

・アーティファクト関連NPCを追加 (npc_town_mora.txt)
　※上位アーティファクト交換は未実装です

----------------------------------------
//1247 [2015/11/05] by refis

・ピンタドスフェスティバル関連NPCを追加 (npc_town_portmalaya.txt)
　※タトゥー交換NPCは未実装です

----------------------------------------
//1246 [2015/11/06] by Cocoa

・Auriga-1244で出ていたエラーの修正
	Thanks LunarPhantom さん

・VisualStudio2013/2015のビルド設定を試験的に追加 (vc_make.bat)

・開発者向けにVisualStudion2015のソリューションファイルを追加(Auriga.sln, vcproj-11/*)
	Thanks refis さん

----------------------------------------
//1245 [2015/11/04] by Cocoa

・homun_renameがyesでもリネーム出来ない不具合の修正（src/map/clif.c）
	-> homun_renameがnoの時にリネームしたホムンクルスが対象

----------------------------------------
//1244 [2015/11/03] by Cocoa

・MobオプションAIの初期化を行う（src/map/mob.c）

・MobオプションAIにクリティカル攻撃、完全回避、スチールクロウを追加（db/mob_mode_db.txt, src/map/battle.c, src/map/mob.h, src/map/status.h）
	-> 特定のMobだけクリティカル攻撃出来るようになる
	-> 特定のMobだけ完全回避出来るようになる
	-> ファルコンアサルトでスチールクロウを考慮した計算式になる

----------------------------------------
//1243 [2015/11/01] by Cocoa

・MobオプションAIを拡張とそれに伴う修正（src/map/battle.c, src/map/map.h, src/map/mob.*, src/map/status.h, src/map/unit.c）
	-> ダブルアタックのLvを指定できるようになる

・MobオプションAIに急所攻撃を追加（db/mob_mode_db.txt, src/map/status.h, src/map/skill.c）

・ランカーポーションボーナスを戦闘関係設定に追加（conf/battle_auriga.conf, src/map/battle.*, src/map/pc.c）

・ランカー武器ボーナスを戦闘関係設定に追加（conf/battle_auriga.conf, src/map/battle.*, src/map/status.c）

----------------------------------------
//1242 [2015/10/31] by Cocoa

・1241で追加したOnMDDeleteのエラーを修正（battle_auriga.conf）
	Thanks rapis さん

・同盟チャットの実装（conf/atcommand_auriga.conf, conf/battle_config.auriga, conf/msg_auriga.conf,
				src/map/atcommand.*, src/map/battle.*, src/map/guild.c, src/map/map.h, msrc/map/pc.c）

----------------------------------------
//1241 [2015/10/30] by Cocoa

・1239の同梱漏れ（src/map/skill.c）

・OnPCMapOutイベントの実装（conf/battle_auriga.conf, src/map/battle.*, src/map/pc.c）

・battle_auriga_confにOnMDDelete、OnPCMapIn、OnPCMapOutの設定項目に追加（conf/battle_auriga.conf, src/map/battle.*, src/map/clif.c, src/map/memorial.c）

・VC8以上 で指定できないオプションの回避処理にVCVER11を追加（vc_make.bat）

----------------------------------------
//1240 [2015/10/29] by Cocoa

・ステイシス、ハーモナイズ、安らぎの子守唄、フライデーナイトフィーバー、アルージョを通常マップでは使用できないようにする（skill_db2.txt）

----------------------------------------
//1239 [2015/10/29] by Cocoa

・戦闘関係設定に街中でグリードを使えるようにするかどうかの項目を追加（conf/battle_auriga.conf, src/map/battle.*）

----------------------------------------
//1238 [2015/10/28] by Cocoa

・1238のデグレ修正（script_ref.txt）

・ファイアリングトラップとアイスバウンドトラップは月光剣などで回復する（battle.c）

----------------------------------------
//1237 [2015/10/28] by Cocoa

・メモリアルダンジョン削除時にOnMDDeleteイベントを発生させる（memorial.c, script_ref.txt）

・OnPCMapInイベントの実装（clif.c, script_ref.txt）

・ウォーマーで冷凍、凍結、氷結状態を解除するようにする（skill.c）

----------------------------------------
//1236 [2015/10/12] by Cocoa

・MobオプションAI、MDOPT_DOUBLEの仮実装
	設定されたMobは通常攻撃時、Lv10ダブルアタックが発動します。

・MobオプションAI、MDOPT_NOATTACKの実装
	設定されたMobはスキル攻撃のみを行うようになり、通常攻撃を行わなくなります。

----------------------------------------
//1235 [2015/10/12] by Cocoa

・MobオプションAIの実装準備

----------------------------------------
//1234 [2015/10/08] by Cocoa

・1232の判定ミス修正 (script.c)

----------------------------------------
//1233 [2015/10/07] by Cocoa

・1232のデグレ修正 (script.c)

----------------------------------------
//1232 [2015/10/07] by Cocoa

・関数「getmapmobs」、「getareamobs」にてmobidを指定して抽出できるよう拡張 (script_ref.txt, script.c)

----------------------------------------
//1231 [2015/06/22] by refis

・ミンストレル、修羅のJob補正値の誤りを修正（job_db2.txt, job_db2-2.txt）
	Thanks SOLDIER_POPORING さん

・item_dbを少し更新（item_db.txt, item_db2.txt）

----------------------------------------
//1230 [2015/06/05] by refis

・ステータス割り振りコマンドのパケット仕様の変更に対応（clif.c, pc.*, script.c）

・Signクエスト[気難しそうな男]の配置と転送先を変更（npc_quest_thesign.txt）

・不要なセミコロンを削除（npc_quest_ashvacuum.txt）

----------------------------------------
//1229 [2015/06/01] by refis

・グロリアス武器交換NPCのアイテムチェック不具合を修正（npc_quest_glorias.txt）
	Thanks rusya7234 さん

・Auriga-1228のgccコンパイルエラーを修正（battle.c）
	Thanks LunarPhantom さん

・ギロチンクロス転職時に宝石箱がもらえるように修正（npc_job_thirdclass.txt）

----------------------------------------
//1228 [2015/05/30] by refis

・mob_avail.txtの説明文を更新（mob_avail.txt）
	Thanks ねぴぴ さん

・memorial_db.txtの定義抜けを修正（memorial_db.txt）

・ロイヤルガードスキル「リフレクトダメージ」を修正（battle.c）
	-> 反射時にオートスペル、ドレイン、オートアクティブが発揮されるよう修正
	-> 物理反射装備と重複して効果が発揮されるよう修正
		Thanks ねぴぴ さん

・[pre]メカニックスキル「アームズキャノン」にダメージ上昇効果が無かったのを修正（battle.c）
	Thanks ねぴぴ さん

・モンスター変身後にマップ移動等すると見た目が戻らなくなる不具合を修正（clif.c）
	Thanks nekoko さん

・シャドウチェイサースキル「オートシャドウスペル」の発動確率の誤りを修正（status.c）
	Thanks Yuki21 さん

・モンスターのMVPアイテムのIDが負の値の場合
　ランダム系アイテムのIDとして処理するように追加拡張（mob.c）
	Thanks dragon さん

----------------------------------------
//1227 [2015/03/12] by refis

・イズルード海底都市NPC追加（npc_misc_board.txt, npc_quest_deepsea.txt）
	-> バイラン島の案内板を更新
	-> 海底神殿調査団クエスト実装
	-> セドラを愛する者クエスト実装
	-> 呪われた人魚クエスト実装

・ブリーシンガメンの封印クエストが進行しない不具合を修正（npc_quest_artifacts.txt）
	Thanks rinaserver さん

・モンスターの通常ドロップアイテムのIDが負の値の場合
　ランダム系アイテムのIDとして処理するように拡張（mob.c）

----------------------------------------
//1226 [2014/12/07] by refis

・スクリプト命令「showdigit」「showmessage」実装（doc/script_ref.txt, clif.*, script.c）

・スクリプト命令「setmobhp」実装（doc/script_ref.txt, script.c）

・スクリプト関数「getmobhp」「sc_onparam」実装（doc/script_ref.txt, script.c）

・0x97b「サーバー情報通知」を実装（clif.*）

----------------------------------------
//1225 [2014/11/14] by refis

・アイテムスキル情報リセットの条件式をミスしていたのを修正（unit.c）

・@monster に表示名入力を省略したコマンド形式を追加（help.txt, atcommand.c）

----------------------------------------
//1224 [2014/11/14] by refis

・クエストリスト状態変更応答の誤りを修正（clif.c）

・Auriga-1108の活性化以外の状態のクエストは討伐更新しない変更を巻き戻し（quest.c）

・マップ離脱時にアイテムスキル情報をリセットするよう修正（unit.c）
	Thanks akayumi さん

・[RE]:bIgnoreDef、bDefRatioATKが二刀流時の追撃に乗らない問題を修正（battle.c）

----------------------------------------
//1223 [2014/10/27] by refis

・AUTH_FIFO_SIZEを越えてアクセスする可能性を排除する（char.c）

・PACKETVER「20130320」以降のキャラクター削除関係の不具合を修正（char.c）
	Thanks SOLDIER_POPORING さん

・[PRE]:クルセイダースキル「シールドブーメラン」の計算式を修正
	Thanks ねぴぴ さん

・クエストリストの討伐数表示不具合を修正（intif.c, quest.c）
	Thanks akayumi さん

・テコンランカーボーナスによるスキルリスト異常現象を修正（pc.c）
	Thanks akayumi さん

・利用期限付きアイテムが削除される際にデリートタイマーエラーが発生していたのを修正（pc.c）
	-> 事前に利用期限を削除して通常アイテムとして処理させる
		Thanks mayura さん

・カート、及び倉庫からアイテムの取り出しに失敗したときのパケット処理を修正（pc.c, storage.c）
	Thanks LunarPhantom さん

----------------------------------------
//1222 [2014/10/27] by refis

・キャラクターのオートセーブがマップ読み込み中のユーザーに対して行われないよう修正（pc.c）

・忍者スキル「影斬り」の射程修正、シーズ環境下の挙動を修正（skill.c）
	Thanks SOLDIER_POPORING さん

・クルセイダースキル「グランドクロス」は魔法無効時に発動しないよう修正（skill.c）
	Thanks SOLDIER_POPORING さん

・クルセイダースキル「グランドクロス」使用時、盾の着脱が出来ないよう修正（skill.c）
	Thanks SOLDIER_POPORING さん

----------------------------------------
//1221 [2014/09/13] by refis

・Auriga-1220のコンパイルエラーを修正（status.c）

・アルベルタ、ジュノーの道具商人販売リストを修正（npc_town_alberta.txt, npc_town_yuno.txt）

----------------------------------------
//1220 [2014/08/30] by refis

・古代精霊のお守りの効果実装（const.txt, item_db.txt, scdata_db.txt, battle.c, status.*）

・状態異常「SC_ATKPOTION」「SC_MATKPOTION」実装（const.txt, scdata_db.txt, status.*）

・ブワヤの巣NPC実装（conf/map_auriga.conf, mapflag_memorial.txt, npc_memorial_buwaya.txt）

----------------------------------------
//1219 [2014/08/30] by refis

・Auriga-1217以降、スクリプト命令「pcblockmove」が正常動作していなかったのを修正（clif.c）

・猫の手3段階エンチャントNPCを実装（npc_town_dicastes.txt）

----------------------------------------
//1218 [2014/08/29] by refis

・スクリプト命令「showevent」のデータが古いため更新拡張する（script_ref.txt, script.c）

・MaxHP,MaxSPを計算で利用する際、オーバーフロウ対策として
　一度atn_bignumberにキャストする（battle.c, mob.c, skill.c, status.c）
	Thanks akayumi さん、hyknt さん

----------------------------------------
//1217 [2014/08/29] by refis

・[RE]:エンペリウムのHPを修正、ダメージを1固定にする（mob_db.txt, battle.c）

・[RE]:エンペリウムはサンクチュアリ効果が無効になるよう修正（skill.c）

・設置用トラップを消費せずに罠を設置できたのを修正（skill.c）
	Thanks ほむ山 さん

・自爆、自害使用時も経験値やドロップがあったのを修正（skill.c）
	Thanks akayumi さん

・マップ離脱時にユニット効果を発現させないよう修正（clif.c, pc.*, unit.c）
	Thanks akayumi さん

----------------------------------------
//1216 [2014/08/29] by refis

・モーラNPC実装 (npc_town_mora.txt)
	-> ビフロストクエスト実装
	-> 紫色の竜クエスト実装
	-> ロペの捜索クエスト実装
	-> モーラの温泉調査クエスト実装
	-> チェシャーの依頼クエスト実装
	-> モーラ住人の依頼クエスト実装
	-> 地元騎士団クエスト実装

・モーラ追加マップのmonster出現定義追加 (npc_monster_biffild.txt)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1215 [2014/08/28] by refis

・スクリプト命令「setnpcdisplay」実装（script.c, doc/script_ref.txt）
	-> NPCの見た目を変更します

・スクリプト命令「pcblockmove」実装（clif.c, script.c, map.h, doc/script_ref.txt）
	-> プレイヤーの移動、攻撃などを制限します

----------------------------------------
//1214 [2014/06/16] by refis

・2014-01-15eRagexeのpacket_dbのミスを修正（packet_db.txt）
	Thanks SOLDIER_POPORING さん

・mob_skill_db.txtのミスを修正（mob_skill_db.txt）
	Thanks SOLDIER_POPORING さん

・NPCを有効化、無効化する際に接触範囲を超えてプレイヤーにアタッチしていたのを修正（npc.c）

・応急処置習得NPC、ポートマラヤNPC、闇のビョンウンゴ病院2階の会話メッセージを補完
　（npc_quest_skillget1.txt, npc_town_portmalaya.txt, npc_memorial_bangungot.txt）

----------------------------------------
//1213 [2014/06/09] by refis

・@rankingでクライアントがクラッシュする場合があるのを修正（msg_auriga.conf）

・0x97c,0x97d,0x97e「一括ランキング参照」を実装（packet_db.txt, clif.*, ranking.c）
	Thanks SOLDIER_POPORING さん、麓丸禄 さん

・「0x137」,「0x81b」の上位互換「0x9e5」,「0x9e6」を追加（buyingstore.c, clif.*, vending.c）

----------------------------------------
//1212 [2014/06/08] by refis

・ナイト転職NPCのメッセージを微修正（npc_job_07knight.txt）

・転生NPCのメッセージの修正、セーブポイントを変更しないよう修正（npc_job_transmigration.txt）
	Thanks pneuma さん

・1次転職NPC群の転職クエスト簡略化に対応（npc_job_01swordman.txt, npc_job_02magician.txt, npc_job_03archer.txt, npc_job_04acolyte.txt, npc_job_05merchant.txt, npc_job_06thief.txt）

・上記に伴う特殊1次職群の転職NPC修正（npc_job_23supernovice.txt, npc_job_24taekwonkid.txt, npc_job_28gunslinger.txt, npc_job_29ninja.txt）

・結婚NPCに養子で話しかけた時の会話を補完（npc_quest_marriage.txt）

・神器クエストを実装（npc_quest_artifacts.txt）

・Auriga-1211のマージ漏れを修正（npc.c）

----------------------------------------
//1211 [2014/06/06] by refis

・アサシン転職NPCにアコライト系で話したときの条件誤りを修正（npc_job_12assassin.txt）

・非ログイン対象に耳打ちするとMAPサーバーがクラッシュする問題を修正（intif.c）
	Thanks 麓丸禄 さん、dallen さん

・NPC有効化時の処理をwarp型とscript型で分ける（npc.c）
	Thanks keiko さん

・ハイディング状態かどうかの判定に「カモフラージュ」状態も含めるよう修正（pc.h）

・戦闘設定「natural_heal_weight_rate」を50、90以上に設定しても一部判定が固定されるのを修正（pc.c）
	Thanks kroe さん

----------------------------------------
//1210 [2014/05/07] by refis

・C-CadeをアカウントIDではなくキャラクターIDで送信するように修正（clif.c）

・「0x97」,「0x98」の上位互換「0x9de」,「0x9df」を追加（char/inter.c, map/clif.*, map/intif.c）

・耳打ち送信応答のパケットサイズの誤りを修正（clif.*）

----------------------------------------
//1209 [2014/05/04] by refis

・Auriga-1208の行動制御チェック強化において、
　NPC商店利用中の行動を不可とする処理をロールバックさせる（clif.c）
	-> 一部PACKETVERで商店利用後も行動不可が継続してしまうため
		Thanks rusya7234 さん

・MAP移動時にNPC商店の保持情報を開放させる（unit.c）
	Thanks rusya7234 さん

----------------------------------------
//1208 [2014/05/02] by refis

・結婚式進行NPCから国王陛下を降板させる（npc_quest_marriage.txt）

・プレイヤーの行動制御チェックを強化（clif.c）
	-> 取引進行中は装備着脱できない（clif.c）
	-> 倉庫利用中は取引要請できない（trade.c）

・モンク系スキル「気孔」、「練気孔」の処理順序を入れ替え（skill.c）

・モンクスキル「残影」の処理を修正（skill.c, unit.c）

・ディレイが0のスキルでもディレイパケットを送信していたのを修正（skill.c）

----------------------------------------
//1207 [2014/04/30] by refis

・Auriga-1206のミスを修正（npc_job_thirdclass.txt）
	Thanks さいこ さん、Gee さん

・[RE]:エンチャントデッドリーポイズン効果を修正（battle.c）
	Thanks keiko さん、ARIA さん、dallen さん

・戦闘設定「item_rate_details」が3のとき、ペットアクセサリードロップ率が非正常に適用される問題を修正（mob.c）
	Thanks dragon さん

・ジェムストーンを消費しない効果は
　アブラカタブラ以外のスキルの場合アイテムを消費しないよう修正（skill.c）
	-> アブラカタブラのみ現行のジェム消費-1のままです
		Thanks ねぴぴ さん

・オラティオ状態の持続時間は継ぎ足しできないよう修正（status.c）

----------------------------------------
//1206 [2014/04/23] by refis

・OnTouchラベルを指定していない範囲NPCの場合
　NPC有効化の際にOnTouchイベントが自動実行されない不具合を修正（npc.c）

・虚像のオーコルニルでブリュンヒルデが作成できないミスを修正（npc_quest_okolnir.txt）

・養子3次職への転職に対応（npc_job_thirdclass.txt）

・闇のビョンウンゴ病院2階実装（map_auriga.conf, mapflag_memorial.txt, npc_memorial_bangungot.txt）
	-> メモリアル生成NPCをポートマラヤファイルから移設（npc_town_portmalaya.txt）

----------------------------------------
//1205 [2014/04/21] by popori

・ログインサーバにおいて、コマンドライン引数を受け取っても初期値にセットしてしまうバグを修正 (src/login/login.c)

・VisualStudio2012のビルド設定を追加 (vc_make.bat)
	※WindowsKits8.0のインストールが必須です。
	　http://msdn.microsoft.com/ja-jp/windows/desktop/hh852363

・開発者向けにVisualStudion2012のソリューションファイルを追加(Auriga.sln, vcproj-11/*)
	※MySQL5.5、x64向けビルド前提です。
	　既存のdspファイルからコンバートが出来なくなったので追加。

----------------------------------------
//1204 [2014/04/10] by refis

・影狼・朧の転職試験の生存の試練で100LPを超過するミスを修正（npc_job_47kaboro.txt）
	Thanks SOLDIER_POPORING さん

・虚像のオーコルニルの一部初期配置モンスターが出現しないのを修正（npc_quest_okolnir.txt）

・ヴァルキリーの贈り物NPCのカラーコードの誤りを修正（npc_quest_godsefestival.txt）

----------------------------------------
//1203 [2014/04/10] by refis

・影狼・朧の転職試験のうち生存の試練で正常に進行しない箇所を修正（npc_job_47kaboro.txt）
	Thanks SOLDIER_POPORING さん

・無効化状態のNPCが有効化された際にOnTouchイベントが実行されなかったのを修正（npc.c）

・虚像のオーコルニル実装（map_auriga.conf, item_db2.txt, mapflag.txt, npc_quest_okolnir.txt）

・ヴァルキリーの贈り物召喚儀式実装（map_auriga.conf, npc_quest_godsefestival.txt）

----------------------------------------
//1202 [2014/04/07] by refis

・パケット難読化処理に対応（battle.*, clif.*, map.h）
	-> 戦闘設定に項目を追加（battle_auriga.conf）
	-> packet_db.txt に「#packet_key: key1,key2,key3」を追加。（db/packet_db.txt）
		Thanks Base on Hercules

・パケット長の誤っている箇所を修正（packet_db.txt）

----------------------------------------
//1201 [2014/04/04] by refis

・2014-03-05bRagexeまでのパケ長を追記（packet_db.txt）

・「0x99f」の上位互換「0x9ca」を追加（clif.c）

・銀行システムで出入金に失敗したとき、エラーメッセージが表示されるように修正（bank.c）

・タナトスタワークエストの一部処理を修正（npc_quest_thanatos.txt）

・スクリプト命令「clear」実装（clif.*, script.c, doc/script_ref.txt）
	-> メッセージウィンドウの文字列を消去します

example:
	prontera.gat,164,190,4	script	clear test	105,{
		mes "test";
		set '@dummy,sleep2(2000);
		clear;
		mes "huge";
		close;
	}

----------------------------------------
//1200 [2014/03/31] by refis

・タナトスタワークエスト実装（map_auriga.conf, npc_quest_thanatos.txt）

・タナトスタワー上層部の下りワープ定義を追加（npc_warp_dun.txt）

----------------------------------------
//1199 [2014/03/28] by refis

・2014-03-05bRagexeのpacket_dbを追加（packet_db.txt）

・2014-01-15eRagexeのpacket_dbのミスを修正（packet_db.txt）
	Thanks SOLDIER_POPORING さん

・client_packet.txtに少し追記（client_packet.txt）

・[RE]:左手のみ錐を持ったとき、右手にも効果が発揮されるよう修正（battle.c）
	Thanks ねぴぴ さん

・エリア情報パケットの設定ミスを修正（clif.c）
	Thanks muchey さん、dallen さん

・モンスターHPバー表示システムを更新（clif.c）

----------------------------------------
//1198 [2014/03/14] by refis

・マラン島関連のクエストログ更新漏れを修正（npc_town_malangdo.txt）
	Thanks ayu さん

・ポートマラヤ関連のクエストが進行しないミスを修正（npc_town_portmalaya.txt）
	Thanks さいこ さん

・SEアジトダンジョン関連NPC、モンスター実装（map_auriga.conf, npc_monster_glddunSE.txt, npc_gvg_arug*.txt, npc_gvg_schg*.txt, npc_gvg_global.txt）

----------------------------------------
//1197 [2014/03/02] by refis

・itembonus「bHPRatePenaltyTime」「bSPRatePenaltyTime」実装
（const.txt, doc/item_bonus.txt, bonus.c, map.h, pc.c, status.c）
	Thanks ARIA さん

・auth_fifoの領域をこえてアクセスする箇所を修正（login.c）
	Thanks ほむ山 さん

・[RE]:左手に錐を持ったときの条件式誤りを修正（battle.c）
	Thanks ねぴぴ さん

・「0x9cb」のバッファ拡張忘れを修正（clif.c）
	Thanks rapis さん

・スキル使用で発動するオートスペル,アクティブアイテムについて、
　スキル使用前ではなくスキル使用後に発動されるよう変更（skill.c）

----------------------------------------
//1196 [2014/03/01] by refis

・グローバル変数を削除する際、別の変数を同時に消してしまう場合があるのを修正（pc.c）
	Thanks ayu さん、mayura さん

・消えた住民とバコナワ関連のクエスト情報が足りていなかったのを修正（quest_db.txt）
	Thanks さいこ さん

・バコナワの伝説クエストで報酬が受け取れなかったのを修正（npc_town_portmalaya.txt）
	Thanks さいこ さん

・ヴァルキリーNPCによる転生条件を修正（npc_job_transmigration.txt）

----------------------------------------
//1195 [2014/02/28] by refis

・バコナワの棲み処NPCの不要なコメントが残っていたので消去（npc_memorial_bakonawa.txt）

----------------------------------------
//1194 [2014/02/28] by refis

・バコナワの棲み処NPC実装（conf/map_auriga.conf, mapflag_memorial.txt, npc_memorial_bakonawa.txt）

・バコナワの棲み処関連モンスターの修正（mob_db.txt, mob_skill_db.txt）

・memorial_db.txtの更新、及びDB最大登録数を20に拡張（memorial_db.txt, memorial.c）

・モンスターIDの最大値を2501から3001に拡張（mob.h）

----------------------------------------
//1193 [2014/02/28] by refis

・2014-01-15eRagexeのpacket_dbを追加（packet_db.txt）

・PACKETVER「20131223」を追加（bcc32_make.bat Makefile vc_make.bat *.dsp）

・「0x90f」「0x914」「0x915」の上位互換「0x9dc」「0x9db」「0x9dd」を追加（clif.c）

----------------------------------------
//1192 [2014/02/27] by refis

・2013-12-23cRagexeのpacket_dbを追加（packet_db.txt）

・PACKETVER「20130731」を追加（bcc32_make.bat Makefile vc_make.bat *.dsp）

・「0x11a」の上位互換「0x9cb」を追加（clif.c）

----------------------------------------
//1191 [2014/02/05] by Rayce

・2012-04-10aRagexeRE のPACKETVERをコンパイラの定義に追加（vc_make.bat, bcc32_make.bat, Makefile）
	reported by うに～く さん

・クライアントのタイムスタンプのパケット受信（0x044a）対応（clif.c, packet_db.txt）
  ※利用機会がないのでコメントアウトしている

・unknownパケットは全てダンプするように強化（char.c, login.c, chrif.c, clif.c）

・セッション番号のprintf出力メッセージを変更（socket.c, char.c, login.c, chrif.c, clif.c, intif.c）

----------------------------------------
//1190 [2014/02/03] by Rayce

・オートスペルとアクティブアイテムの関数名の命名規則を統一（bonus.*, battle.c, skill.c）
	bonus_autospell()      → bonus_autospell_start()
	bonus_skillautospell() → bonus_autospellskill_start()
	bonus_activeitem()     → bonus_add_activeitem()

・オートスペルとアクティブアイテムのビットマスクにconstを付与（bonus.c）

・キャラ作成処理の一部をTXTモードとSQLモードで共通の関数にまとめる（char.c, char_txt.c, char_sql.c）

・BL_XXX 系に対する演算を出来る限りビット演算に変更して高速化（battle.c, mob.c, skill.c, status.c）

・細かい最適化（char.c, inter.c, memorial.c）

・NPCスクリプトから不要な ; を削除
  （npc_quest_area.txt, npc_town_ayothaya.txt, npc_town_brasilis.txt, npc_town_comodo.txt）

----------------------------------------
//1189 [2014/02/02] by refis

・エルディカスティス関連クエストの一部が進行しないミスを修正（npc_town_dicastes.txt）
	Thanks ayu さん

・魔王モロク追跡クエストのクエストログ処理を修正（npc_quest_ashvacuum.txt）
	Thanks ayu さん

・ターボトラックコインの交換チェックを修正（npc_quest_turbo.txt）
	Thanks さいこ さん

----------------------------------------
//1188 [2014/01/23] by refis

・ターボトラックのロールバック修正（npc_quest_turbo.txt）

----------------------------------------
//1187 [2014/01/23] by refis

・ターボトラックの入場制限を修正（npc_quest_turbo.txt）
	Thanks さいこ さん

・カプラ倉庫、カプラカートレンタル時にカプラポイントが付与されないのを修正（npc_misc_kafra.txt, npc_job_23supernovice.txt）
	Thanks さいこ さん

・アルベルタの少年クエスト実装（npc_quest_yggdrasil.txt, npc_town_alberta.txt）

・quest_db.txtの更新（quest_db.txt）

----------------------------------------
//1186 [2014/01/22] by refis

・グロリアス武器交換時の誤りを修正（npc_quest_glorias.txt）

----------------------------------------
//1185 [2014/01/22] by refis

・グロリアス交換NPC実装（conf/map_auriga.conf, npc_quest_glorias.txt）

・グロリアス関連交換NPCを修正（npc_quest_arena.txt, npc_quest_turbo.txt, npc_town_aldebaran.txt）

・item_dbの更新（item_db.txt, item_db_pre.txt）

----------------------------------------
//1184 [2014/01/21] by Rayce

・Auriga-1176以降、RETCODEがまだ残っていた部分を修正（script.c）

・progressbar命令で60秒以上の時間を指定するとタイムアウトで強制的にcloseされる問題を修正（script.c）

・スクリプトのハッシュサイズを 1021 ⇒ 1571 に拡大（script.c）
  使用される変数が増えてきたためハッシュ値の分散性を最適化する

・変数のスコープの局在化（db.c, grfio.c）

----------------------------------------
//1183 [2014/01/20] by refis

・Auriga-1182のスペルミスを修正（bonus.c）
	Thanks LunarPhantom さん、rusya7234 さん

・NPCスキル「ベナムフォグ」はランドプロテクターの阻害効果を受けるよう修正（skill.c）

・NPCスキル「ベナムフォグ」は毒属性のプレイヤーにダメージを発生させないよう修正（skill.c）

・霧の森NPC実装（conf/map_auriga.conf, mapflag_memorial.txt, npc_memorial_mistwood.txt）

----------------------------------------
//1182 [2014/01/19] by Rayce

・Auriga-1181以降、packet_db.txt 読み込み時に解析エラーが発生したときメモリリークが発生する
  問題を修正（clif.c）

・packetdb_readdb_sub() から不要な変数を削除（clif.c）

・アイテム活性化中に再度活性化が発生するとき、タイマーが削除されてなかったのを修正（bonus.c）

・オートスペルとアクティブアイテムのビットマスク判定をまとめて処理を簡素化（bonus.c）

----------------------------------------
//1181 [2014/01/19] by Rayce

・コンパイルオプション PACKETVER の指定に合わせて packet_db.txt を自動的に読み取るように改善（clif.c）

  ※packet_db.txt に「#packet_ver: YYYYMMDD」を追加。
	PACKETVER を元に直近の日付を特定して上書きする仕組み。
    これにより、packet_db.txt からコメントアウトを外す作業が不要になる。

  ※同日のクライアント（2005-05-27gRagexe と 2005-05-27iRagexe 等）が複数ある場合は一番下に
    書かれた定義が有効になる。
    この場合、上に書かれた定義を有効にするには従来通り下の定義をコメントアウトすること。

  ※もし自動取得ではなく特定の日付を使用したい場合は、#packet_ver の値を PACKETVER と同じにして
    一番下に定義すること。
    PACKETVER と同一のときが最優先になるため。

・cppcheckを使った静的チェックのうち、変数の局所化を実施

----------------------------------------
//1180 [2014/01/18] by Rayce

・PACKETVER が 20120925 以上のとき、アイテムの追加処理に失敗したときのパケット位置が
  間違っているのを修正（clif.c）
	reported by LunarPhantomさん

・Auriga-1173以降、progressbar命令の指定時間がミリ秒単位になっているスクリプトを修正
  （npc_quest_ashvacuum.txt, npc_quest_yggdrasil.txt）
	reported by rusya7234さん

・ロック付きファイルの保存処理において、何かしらの原因で古いファイルの削除に失敗したときは
  リネームせずに保管しておくようにする（lock.c）

  ※TXTモードでsaveフォルダ内に .tmp ファイルが残っていた場合は、サーバ起動前に
    古いファイルを手動で削除して .tmp ファイルをリネームすることで最新のデータを
    復旧することが出来ます。

・コンパイルオプション NO_SCDATA_SAVING が有効のとき、コンパイルできない問題を修正
  （int_status.c, statusdb_txt.*, statusdb_sql.*）

・Auriga-1179の size_t に対する型変換のミスを修正（malloc.c）

----------------------------------------
//1179 [2014/01/18] by Rayce

・cppcheckを使った静的チェック修正の続き
	-> @callmerc のメッセージのNULL判定が間違っていたのを修正（atcommand.c）

	-> 精霊関連DBを再読み込みする @reloadelemdb を追加（atcommand.*）

	-> sscanf で文字列を読み込む場合は長さを指定するようにセキュリティの強化
	   （char.c, inter.c, grfio.c, login.c, httpd.c, socket.c）

	-> ファイルハンドラのクローズされておらずリソースリークが発生するのを修正（httpd.c）

	-> ファイルハンドラが2回クローズされる可能性を修正（grfio.c）

	-> SQLクエリ発行時の文字列長チェックが動作していなかった問題を修正（sqldbs.c）

	-> 意味のないコードをコメントアウト（guilddb_txt.c, clif.c）

	-> size_t型を printf() するときは %lu を使うように修正（malloc.c）

	-> unsigned型に対してマイナスチェックは不要なので変更（httpd.c, core.c, winservice.c）

	-> 未使用且つ不要な関数 do_final_chat() を削除（chat.*）

	-> 変数のスコープを局所化

・キャラ新規作成時の応答パケット処理を mmo_char_send006d() としてまとめる（char.c）

・キャラ新規作成に失敗したときのパケットスキップ位置が間違っているのを修正（char.c）

・@reloadmercdb を実行しても再読込が正常に動作していなかったのを修正（merc.c）

・elem_db_add.txt がデフォルトで用意されてなかったのでファイルを追加（db/addon/elem_db_add.txt）

・db_ref.txt にelem_db.txtの解説がなかったので追加（doc/db_ref.txt）

----------------------------------------
//1178 [2014/01/09] by Rayce

・callshop命令でPointShopからアイテムが取得できるように修正（script.c）
	reported by rusya7234さん

・[SQL] Auriga-1176以降、mysql_query() 実行後に結果セットの保存処理が無くなっていたバグを修正（sqldbs.c）
	reported by rusya7234さん

----------------------------------------
//1177 [2014/01/05] by Rayce

・Auriga-1176のファイル同梱漏れ（common/*.c）

・cppcheckを使った静的チェックを一部修正
  http://cppcheck.sourceforge.net
	-> /recall2, /remove2 コマンドが動作しなかったのを修正（clif.c）

	-> 子守唄状態でスキルユニットが見つからなかったときにサーバクラッシュする可能性を修正（status.c）

	-> フォントアイテムでないものの使用期限が切れたとき、フォントが初期化される問題を修正（pc.c）

	-> bAddRevEffの引数の最大値-最小値チェックの間違いを修正（bonus.c）

	-> 歩行パスの最大値 MAX_WALKPATH でループを打ち切る（path.c）

	-> sscanf で文字列を読み込む場合は長さを指定するようにセキュリティの強化
	   （atcommand.c, extra.c, map.c, msg.c, npc.c, script.c, mapreg_txt.c）

	-> unsigned型に対してマイナスチェックは不要なので削除（buyingstore.c, npc.c）

	-> 使用されない変数を削除（guild.c, homun.c, script.c, skill.c, unit.c）

	-> 意味のない初期化を削除（mob.c, skill.c）

	-> 冗長なNULLチェックを削除（skill.c, status.c）

	-> 括弧の囲みミスを修正（battle.c, clif.c）

	-> 変数のスコープを局所化

----------------------------------------
//1176 [2014/01/05] by Rayce

・改行コードの定義を RETCODE から NEWLINE に変更
  RETCODE は <sqlext.h> 等で既に定義されており重複する可能性があるため

・武器精錬可能アイテムリスト送信処理（0x221）に与える引数をrAthenaベースで補完（clif.c）

・gcc4.8.1での警告修正
	-> WindowsHandlerの初期値をNULLではなく 0 にする（winservice.c）
	   RegisterServiceCtrlHandlerEx() は失敗時に 0 を返すため、INVALID_HANDLE_VALUE は使えない

	-> chardb_txt_read() が常にtrueを返していたのを修正（chardb_txt.c）

	-> Mobの特殊AIでスキルを使用させるとき、定義されてない命令対象が指定されていた場合はその
	   命令を実行したMobのBlockIDが表示されるようにメッセージを変更（mob.c）

	-> db/attr_fix.txt 読み込み時、各テーブルのヘッダのLvと最大値が読み込めなかった場合は
	   そのテーブルの読み込みをスキップするように強化（pc.c）

	-> 未使用の変数を削除（atcommand.c, battle.c, clif.c, script.c, skill.c, unit.c）

・[SQL] SQLクエリ実行してエラーが発生した後、前回のSQLクエリの結果が参照できてしまうのを修正（sqldbs.c）

・[SQL] ROLLBACKを複数実行したときのトランザクションカウンタの補正漏れを修正（sqldbs.c）

----------------------------------------
//1175 [2014/01/05] by refis

・スクリプト関数「checkactiveitem」で前方一致したフラグ値しか得られないミスを修正（script.c）

・アルベルタ改修に伴う関連NPC座標の変更（script/npc/*）

----------------------------------------
//1174 [2014/01/04] by Rayce

・[SQL] 作成したプリペアドステートメントを保存するように改善（sqldbs.*）
        クエリ文字列で作成済みのstmtを検索したり、sqldbs_close() で
        メモリリークしないようにstmtのクローズが出来るようになります

・[SQL] ギルド城の定期同期セーブ処理をプリペアドステートメントに変更（guilddb_sql.c）
        毎回stmtを用意するのではなく、バインド済みの領域を使い回す

・[SQL] プリペアドステートメントの初期化に失敗したときはNULLを返すように強化
        （sqldbs.c, accregdb_sql.c, chardb_sql.c, account_sql.c）

・メール本文のデータ取得時の処理を最適化（maildb_txt.c, maildb_sql.c）

・hex_dump() の処理を最適化（utils.c）

----------------------------------------
//1173 [2014/01/04] by Rayce

・タイマーのキャッシュをデフォルトで無効にする（timer.c）
	-> OSのタイマー関数の呼び出しが負荷になることを考慮して、gettick() は256回まではキャッシュ
       された値を返す仕組みになっていました。
	   しかし、それにより経過時間を正しく取得できず、タイマー系の処理が動作しない等の弊害が
	   実は随所にありました。
	   今後はeA方式でキャッシュをデフォルトで無効にします。
	   もし負荷が大きいケースがある場合、コンパイラオプションの TIMER_CACHE を有効にしてください。
	   TIMER_CACHE=256 がこれまでと同様の動作です。
	   必要に応じて値を小さくしてもいいかもしれません。

	-> gettick() の呼び出し回数を抑えるように変更。
	   出来るだけ関数の最初で getick() を呼び出して変数に保存しておくことにより、実際の経過
	   時間を参照できるようにする。

	-> progressbar命令実行後に処理が続行できない場合がある問題を修正
		reported by mayuraさん

・progressbar命令の仕様変更（clif.*, script.c, doc/script_reg.txt）
	-> 引数に指定する時間はrAthenaと同じくミリ秒（ms）ではなく秒（sec）に変更
	   クライアントが秒でしか受け付けていないため

	-> 引数を1つ増やし、色が指定できるように拡張

	-> 処理機構をmenu系/sleep系と同じにする
	   STOPではなくRERUNLINEにし、経過時間の判定はclif.cではなくscript.cに留める

	-> スタック解放時にprogress情報を初期化する

	-> プレイヤーがアタッチされてないときに命令を呼び出したとき、
	   「fatal error ! player not attached!」が表示されるように変更

・sleep命令およびsleep2関数で、スクリプトが再開されるときにスタックからtickの値を
  取得していた無駄を改善（script.c）

・sleep2関数でアタッチに成功したとき、1以外の値が返る可能性を修正（script.c）

----------------------------------------
//1172 [2014/01/04] by Rayce

・座標および範囲指定を持つ定期沸きモンスターを出現させるときにスタック判定された場合、
  侵入可能セルの判定が mob_spawn() 時よりも小さくなっていたため侵入可能セルが見つからずに
  削除されてしまっていたバグを修正（npc.c）
	reported by rapisさん

・ポリンとエンペリウムのIDをenumとして定義（battle.c, clif.c, mob.c, skill.c, status.c, map.h）

・battle_check_target() の処理を少し最適化（battle.c）

----------------------------------------
//1171 [2014/01/03] by Rayce

・クエスト関係の処理見直し
	-> quest_search_index() をstaticにし、代わりに quest_get_data() を使う（clif.c, quest.*）

	-> 討伐データベースの最大数が MAX_QUEST_DB で制限されているのを撤廃
	   リストを動的に確保し、同一のMobIDが存在しないようにする（quest.*, map.c）

	-> 討伐データベースの検索でMobIDが0のときもヒットしていた問題を修正
	   独自のbinary searchではなく標準の bsearch() を使うように簡素化（quest.c）

	-> MAX_QUEST_DBの定義はquest.c内でしか参照されないので、mmo.hからquest.hに移動（mmo.h, quest.h）

・printfのフォーマット %z は処理系によって動作しないため、unsigned long型にキャストする（sqldbs.c, pc.c）

・サーバクラッシュ時に生成される crashdump.log にAurigaのバージョンを記録する（core.c）

・aMalloc, aCalloc, aReallocによって48KBを超えるデータがアロケートされ、その後メモリリークが
  発生した場合、ログに記載されるサイズが常に0になっていたのを修正（mallo.c）

・Auriga-1168で追加した winservice.c, winservice.h がdspに記載されてなかったので追記（*.dsp）

----------------------------------------
//1170 [2014/01/03] by Rayce

・map_auriga.confでextraシステムのチェック時間を設定できるように追加（map.*, extra.c, conf/map_auriga.conf）
  extraチェックのタイマーを作動させたくない場合は 0 を指定してください

・ログイン中のパーティメンバーを取得する処理を party_getvaliablesd() としてまとめる（party.*, memorial.c）

・マスターのsdを返す処理を map_bl2msd() としてまとめる（map.*, battle.c, mob.c, skill.c）

・BL_XXX の判定を出来るだけビット演算に変更するよう最適化（battle.c, mob.c, npc.c, skill.c, unit.c）

・使用頻度の低い変数からstaticを取り除く（socket.c）

----------------------------------------
//1169 [2014/01/02] by Rayce

・[SQL] Auriga-1163以降、sqlquery関数でSELECTしたときに結果が取得できないバグを修正（script.c）
          reported by LunarPhantomさん

・[TXT] マップ永続変数を保存する時間間隔を conf/script_auriga.conf で指定できるように拡張（script.c）
        これまでと同様デフォルトは300秒

----------------------------------------
//1168 [2014/01/01] by Rayce

・Athena-2265をベースにWindowsサービス化に対応（core.*, winservice.*）
	-> Windowsでのみ有効、Linuxの場合は何もしない。
	   コンパイルオプションは必要なし。

	-> サービスへの登録および削除はOS標準の sc.exe コマンドを使用。
	   詳細は doc/instasv.txt を参照。

	-> core.cの構造を変更。
	   起動パラメータ --service-name を直接起動とサービス起動の判定に利用。
	   大まかな処理の流れは以下。
	     * 直接起動時（これまでと同じ）
	         1. main() からエントリ
	         2. 起動パラメータを取得
	         3. --service_name が指定されてないことを確認
	         4. main_sub() を実行

	     * サービス起動時
	         1. main() からエントリ
	         2. 起動パラメータを取得
	         3. --service-name からサービス名を読み取る
	         4. 起動パラメータをコピーしてSCMに登録
	         5. SCMより winservice_main() が実行
	         6. SCMへ準備開始を通知後、main_sub() を実行

	-> 起動パラメータに --stdout, --stderr を追加。
	   標準出力および標準エラー出力をログファイルへリダイレクトできるように拡張。

・サーバ起動時およびサービス起動時にメッセージを出力するように拡張
  ログファイルから起動と終了を追跡できるようにする（core.c, winservice.c）

・出力のバッファリングを無効にする（core.c）
	Suggest by mapleさん、thanks a lot!!

・doc/account_making.txt にSQLモードでの直接編集方法を追記（doc/account_making.txt）

・サーバ起動時に指定可能な引数についての仕様を別ドキュメントとして分離
  （doc/commandline_parameter.txt, doc/distribute_servers.txt）

----------------------------------------
//1167 [2014/01/01] by Rayce

・[TXT] Auriga-1166の private_ 変数名の変更漏れ修正（chardb_txt.c）

・[TXT] セーブデータの読み込み/書き込みに失敗したときはエラーメッセージを出力するように強化

・各種dbファイルの読み込み失敗時のエラーメッセージを統一

・サーバ起動時の引数において、未定義のものがあっても exit(1) せずに続行するように変更
  （login.c, char.c, map.c, converter.c）

・malloc.cでエラーメッセージ出力が標準出力であった場合はハンドラをクローズしないように変更（malloc.c）

・utils.hが単体でリンクできるように stdio.h をincludeする（utils.h）

----------------------------------------
//1166 [2013/12/31] by Rayce

・VC++コンパイルオプション /TP 有効時のエラーおよび警告について一部修正
	-> item構造体の private 変数名を private_ に変更（mmo.h, chardb_*.c, char-converter.c, clif.c）

	-> clif_parse_QuestState(), mail_getappend() でint型の戻り値をbool型で受け取っていた問題を修正
	   （clif.c, mail.c）

	-> bool型変数へint値を設定していた問題を修正（login_httpd.c）

	-> sqldbs_num2datatype() の戻り値の型を enum enum_field_types に変更（sqldbs.c）

・[SQL] friend テーブルから name カラムを削除、キャラ名は char_data テーブルから参照する
        （chardb_sql.c, char-converter.c, main.sql）

----------------------------------------
//1165 [2013/12/31] by Rayce

・PRE_RENEWAL が定義されていないとき、コンパイル時に「warning: unused variable」の
  警告が発生するのを修正（battle.c）

・ジャーナル有効時、mapreg_txt_sync がstatic無しで再定義されているためにコンパイル
  エラーが発生する問題を修正（mapreg_txt.c）

・Auriga-1164以降、gccコンパイル時に「unknown conversion type character」の警告が
  発生するのを修正（pc.c）

・[SQL] gccコンパイル時に「unused variable」の警告が発生するのを修正（account_sql.c）

----------------------------------------
//1164 [2013/12/31] by Rayce

・グローバル変数は大文字/小文字を区別しないように変更（pc.c）

  ※これまでグローバル変数（prefixなし, #変数, ##変数）は大文字/小文字を区別して
    保存されていました。
    特にSQLモードの場合は「Duplicate entry」エラーが発生し、保存処理に失敗します。
    今後は他の変数と同様に大文字/小文字は区別せずに扱われます。

		set BUF, 1;
		set Buf, 2;
		debugmes BUF + ":" + Buf;	// 1:2が表示されていた、今後は 2:2 となる

・グローバル変数の読み取り/書き出し処理を共通化（pc.*）

・[SQL] ランキングデータを構築する際、LEFT JOINを使って処理を高速化（chardb_sql.c）

----------------------------------------
//1163 [2013/12/31] by Rayce

・[SQL] rAthenaをベースにsqldbs.cの構造を刷新
	-> MYSQL mysql_handle を直接使うのではなく、sqldbs_handle構造体を利用する
	   MYSQL_RES を内包しているので、MySQLハンドラと結果セットの紐付けが可能

	-> クエリ発行後は mysql_store_result() まで一括で実行されるため、すぐにフェッチを
       実行できるように簡略化されている

	-> sqldbs_fetch() は MYSQL_ROW ではなくtypedef元の char** を返す
	   これにより MYSQL_*** 系の型をsqldbs.c以外で記述しなくて済む

	-> 結果セット MYSQL_RES の有無は sqldbs_has_result() で判定する

	-> トランザクション開始・コミット・ロールバック処理をそれぞれ関数化
	   通常MySQLではトランザクションのネストが出来ないため、自前でネストに対応

	-> 安全のため sqldbs_query() および sqldbs_stmt_prepare() で可変長文字列の合成時の
	   文字列長チェックを追加

	-> MYSQL_STMT を直接使うのではなく、sqldbs_stmt構造体を利用する
	   MYSQL_BIND を内包しており動的にパラメータと結果カラムのバインドを内部で実行可能

	-> パラメータのバインド時は、登録されているステートメントを元にパラメータの数を
	   自動的に割り出す

	-> 結果カラムのバインド時は、登録されているステートメントを元にカラム数を
	   自動的に割り出す

	-> sqldbs_stmt_bind_result() を実行することで結果カラムに結果が格納される

	-> 1度バインドした sqldbs_stmt 構造体は使い回しが可能
	   sqldbs_execute() ⇒ sqldbs_stmt_bind_result() ⇒ sqldbs_stmt_fetch() を繰り返して
	   データを取得ことが可能になる

	-> エラー発生時は発行したクエリの全文を表示するように拡張
	   どのクエリで失敗したのか特定できるようになる

	-> Auriga-1158で追加したクローズ処理時のメッセージは、sqldbs_connect() 時に
	   設定するように変更

・[SQL] 少なくとも INSERT/UPDATE/DELETE が複数回実行される場合はトランザクション処理を行うよう改善
        トランザクションに失敗した場合はセーブデータのキャッシュへの保存は行わない

・[SQL] tmp_sql変数のexternを廃止

・[SQL] strecpy() 用のデフォルトのMYSQLハンドルを外部から設定できるように
        sqldbs_set_default_handle() を追加

・[SQL] セーブデータのキャッシュの削除処理を numdb_erase() だけで行うように高速化

・[SQL] INSERT/UPDATE/DELETE が実行される関数は戻り値をbool型に統一

・[SQL] chardb_sql_make() でMYSQL_BIND配列の数が小さく、バッファオーバーフローが
        発生していたのを修正

・[SQL] 倉庫のアイテム数が非常に多い場合（特にギルド倉庫で1000個近い場合）、chardb_sql_saveitem() で
        INSERT用のSQL文を組み立てるときにバッファオーバーフローが発生する問題を修正
        65536byteの更に2倍まで配列サイズを拡張

・全体的なリファクタリング
・全体的にnullpoチェックの強化

----------------------------------------
//1162 [2013/12/29] by Rayce

・BCCコンパイル時の警告修正（grfio.c）

・GMコマンド /recall2 がID指定の @recall として動作するように実装（clif.c）

・GMコマンド /remove2 がID指定の @jumpto として動作するように実装（clif.c）

・pc_unequip() を多重に呼び出す可能性がある場合、status_calc_pc_stop_begin() で
  保護ように改善（clif.c, pc.c, skill.c）

----------------------------------------
//1161 [2013/12/29] by Rayce

・[TXT] ジャーナル機能がONのとき、セーブデータが存在しない場合にデータの保存処理を
        行うと「journal not ready」のエラーが発生するのを修正
        セーブデータが無い場合でもロールフォワードを実行することが可能になる

・[TXT] mapreg_journal_convert() のデバッグ用コードを削除（mareg_txt.c）

----------------------------------------
//1160 [2013/12/29] by Rayce

・マップサーバのタグ名が他のマップサーバと重複していた場合に警報を発するように改善
  （char.*, map.c, chrif.c, mmo.h）
	-> チェックされるのは同一キャラサーバ配下のみ
	   他キャラサーバにあるマップサーバはチェックしない

・キャラサーバ内のメッセージで、マップサーバタグ名を表示するように拡張（char.c）

・サーバ間パケットドキュメント更新（doc/serverlink_packet.txt）

----------------------------------------
//1159 [2013/12/28] by Rayce

・@mannerpointの仕様をrAthena仕様に合わせる（clif.*, atcommand.c）
	-> msg_auriga.conf を使わずパケット 0x14a, 0x14b を利用する
	-> ポイントを0にすると SC_NOCHAT 状態を解除できる

・GMコマンド /rc が @mannerpoint として動作するように実装（clif.c）

・GMコマンド /remove は /shift と同じ動作として実装（clif.c）

・GMコマンド /check は clif_initialstatus() と同等の動作として実装（clif.c）

----------------------------------------
//1158 [2013/12/28] by Rayce

・[TXT] 永続マップ変数の保存のジャーナリング対応（mapreg_txt.*, journal.*）

・[SQL] 永続マップ変数の変更/削除があった場合、即座にMySQLサーバを更新するように変更（mapreg_sql.*）

  ※login系やchar系のセーブデータと同じ機構に合わせます。
	これにより自動セーブ待ち時点でサーバが落ちてもセーブデータが消失するような事故が無くなります。

・[SQL] スクリプト専用のMySQL接続が確立できていないときはクローズ処理も実施しないように修正（script.c）

・[SQL] SQLサーバとの接続をクローズするとき、どの接続のクローズなのか特定できるように拡張
        （sqldbs.*, account_sql.c, chardb_sql.c, mapreg_sql.c, script.c, converter.c）

・文字列型永続マップ変数をロードするとき、メモリリークが発生するバグを修正（mapreg_txt.c, mapreg_sql.c）

・文字列型変数で指定可能な値の最大バイト数の情報をドキュメント化（doc/script_ref.txt）

----------------------------------------
//1157 [2013/12/28] by Rayce

・mapreg_final() 時、解放済みの str_buf と str_data を参照してサーバクラッシュする
  問題を修正（script.c）
	reported by LunarPhantomさん

・userfunc_db を外部に公開せず、getter/setter を用意する（npc.c, script.*）

----------------------------------------
//1156 [2013/12/27] by Rayce

・Auriga-1155以降、config設定が読み込まれず mapreg_init() および mapreg_final() が
  呼び出されていない問題を修正（map.c, script.c）
	-> reported by LunarPhantomさん

・[SQL] MySQL接続時のcharsetのデフォルトを cp932 に変更

・[SQL] MySQLサーバ接続時にIP, Port, User, DB名の情報を表示するように変更（sqldbs.c）

----------------------------------------
//1155 [2013/12/26] by Rayce

・マップ変数のセーブ処理をTXTモードとSQLモードとでソースファイルを分離
  （map.c, script.*, mapreg_txt.*, mapreg_sql.*）

・conf/map_auriga.conf のうち、スクリプト専用のMySQLの設定項目を conf/script_auriga.conf に移動
  （map.*, script.c）

・MySQLへの接続は map.c ではなく mapreg_sql.c で行うように変更
  スクリプト専用のMySQLへの接続は script.c で行うように変更

・mapreg_txt.* および mapreg_sql.* をコンパイル対象に含める
  （Makefile, bcc32_make.bat, vc_make.bat, map.dsp, map_sql.dsp）

----------------------------------------
//1154 [2013/12/26] by Rayce

・コンパイルオプション /W4 有効時の警告修正
	-> warning C4189: 'xxx' : ローカル変数が初期化されましたが、参照されていません
	-> warning C4245: '=' : 'int' から 'unsigned int' に変換しました。signed/unsigned が一致しません。
	-> warning C4389: '!=' : signed と unsigned の数値を比較しようとしました。
	-> warning C4701: 初期化されていない可能性のあるローカル変数 'xxx' が使用されます
	-> warning C4702: 制御が渡らないコードです。

・イクシードブレイクの移動速度減少が、イクシードブレイクのスキルLvではなくフリーキャストのスキルLvを
  元に計算されていたのを修正（unit.c）

・ファイルのサイズを取得するとき、fseek, ftell を使わず stat を利用するように改善（httpd.c, grfio.c, map.c）

・map_mdmap_clean() のリファクタリング（map.c）

----------------------------------------
//1153 [2013/12/19] by refis

・ベナムフォグの回復処理のミスを修正（skill.c）

----------------------------------------
//1152 [2013/12/19] by refis

・NPCスキル「ベナムフォグ」実装（skill_cast_db.txt, skill_db2.txt, skill_db.txt, skill_unit_db.txt, skill.c）

・client_packet.txtの一部訂正（client_packet.txt）

・パケット0x8c7, 0x99fでウォーロックスキル「ラディウス」を参照していた箇所をユニット範囲に変更（clif.c）

----------------------------------------
//1151 [2013/12/07] by Rayce

・Auriga-1149で、clif_changelook() のパケット送出位置が間違っていたのを修正（clif.c）

・出来る限りWT系およびELE系定数を使用するように変更（battle.c, status.c）

----------------------------------------
//1150 [2013/12/07] by Rayce

・Auriga-0822以降、waitingroom命令の引数 job が正しく動作しなくなっていたのを修正（chat.c, pc.*, script.c）
	-> pc_check_useclass() を整理し、職業値のビットを返す関数 pc_get_job_bit() に変更。
	-> チャットの職業制限のビットは pc_get_job_bit() を参照するように変更。

・Auriga-0805以降、skill_require_db.txtの list_weapon 項目について、二刀流（93~98）の設定が
  無効になっていたのを修正（pc.c, skill.*, status.c）

・item_db.txtのSLOTの値が0~4以外の値の場合、バッファオーバー/アンダーフローが発生しないように
  読み込み時にチェックを入れる（itemdb.c）

・@optionの引数を16進数でも指定できるように拡張（atcommand.c）

・スクリプトにおいてクラスの番号指定をconst.txtの定数に変更（quest/npc_quest_arena.txt）

・helpおよびdb_refのメンテナンス（itemdb.c, conf/help.txt, doc/db_ref.txt）

・DBのヘッダ行のコメントの内容を正しく更新（db/size_fix.txt, db/skill_db2.txt）

----------------------------------------
//1149 [2013/12/07] by Rayce

・mob_talk() 実行するとき、最大値の判定を行うように強化（mob.c）

・pc_break_equip() の引数 where をunsinged short型からint型に拡張し、全てのLOC定数を受け入れることが
  可能にしておく（pc.*）

・map_session_data構造体の unbreakable_equip メンバをunsigned short型からunsinged int型に拡張し、
  全てのLOC定数でビット演算が可能にしておく（map.h）

・clif.cのリファクタリング、武器の見た目を取得する処理を clif_get_weapon_view() としてまとめる（clif.c）

・PACKETVERが3以下のとき、clif_changelook() でコンパイルエラーが発生する問題を修正（clif.c）

・装備箇所を示すLOC系定数をitemdb.hからmmo.hに移動し、char.cでも利用可能にする（mmo.h, itemdb.h）

・出来る限りenum型を使うように変更
  （chardb_txt.c, char.c, clif.c, extra.c, mob.c, pc.c, script.c, skill.c, status.c）

----------------------------------------
//1148 [2013/12/06] by Rayce

・関数名と意味を一致させるため pc_isquitable() の判定結果を反転（pc.c, clif.c）

・クライアントの切断パケット 0x18b を送る処理を clif_disconnect_ack() としてまとめる（clif.*）

・クライアントの終了判定で、エンジェラスの有無の判定方法をビット演算に変更（pc.c）

・INF系定数の名称を変更（battle.c, bonus.c, clif.c, mob.c, pet.c, script.c, skill.*, status.c, unit.c）

・INF2系定数を新たに設置（atcommand.c, battle.c, clif.c, pc.c, skill.*）

・LOOK系定数をmap.hからpc.hに移動（map.h, pc.h）

・出来る限りenum型を使うように変更（char.c, battle.c, mob.c, pc.c, status.c）

・status_change構造体で使用するopt1はビットフラグではないので、OPT1系のenum定数を16進数から
  10進数に変更する（status.h）

・clif_GMmessage() と clif_announce() のflag引数をunsigned int型に変更（clif.*）

----------------------------------------
//1147 [2013/12/06] by Rayce

・2進数対応の strtol, strtoul として strbtol, strbtoul を実装（utils.*）

・文字列を数値に変換するとき、2進数/8進数/16進数での変換をサポート（script.c, db/script_ref.txt）
	-> これまでは conv_num() が10進数固定だったのを基数を可変に変更。
	-> 例えば以下のような変換が可能。
		set '@val, "0b11" ⇒ 3
		set '@val, "077" ⇒ 63
		set '@val, "0xff" ⇒ 255

・@writevars や const.txt で2進数が扱えるように拡張（atcommand.c, script.c）

----------------------------------------
//1146 [2013/12/06] by Rayce

・べき乗演算子 ** を右結合に変更（script.c, doc/script_ref.txt）

  ※PerlやPythonと同じ仕様です。
    例えば、4 ** 3 ** 2 = 4096 ではなく 4 ** 3 ** 2 = 262144 となります。
    つまり、4 ** (3 ** 2) と等価になります。

・battle_configの etc_log と error_log について、スクリプトに関連する部分を
  script_configとして別途定義する（script.c）

  ※battle_config.etc_log   => script_config.debug_mode_log
    battle_config.error_log => script_config.error_log

・スクリプトのDEBUG用のメッセージを変更（script.c）

----------------------------------------
//1145 [2013/12/05] by refis

・装備ウィンドウの表示方法をデフォルトで誰でも利用可能にする（battle_auriga.conf）

・スクリプト関数「checkactiveitem」は活性状態を活性フラグで返すよう変更（script.c, doc/script_ref.txt）

・「審判のメイス」および「審判のメイスⅡ」スクリプトのアイテム活性効果を修正（db/item_db.txt）

----------------------------------------
//1144 [2013/12/05] by Rayce

・スクリプトにべき乗の演算子 ** を追加（script.c, doc/script_ref.txt）

  ※Perlライクな使い方になります。
    例] 2 ** 3 => 8 (2の3乗)

・const.txtに SC_SIGHT を定義し「クリムゾンオーブ」で使用する（db/const.txt, db/item_db.txt）

・「グロリアススピア」および「グロリアスランス」スクリプトの } 閉じ位置が
  間違っていたので修正（db/item_db.txt）

・「Kotakahuanaのガチャポン」の末尾にある不要な文字を削除（db/item_db.txt）

----------------------------------------
//1143 [2013/12/04] by Rayce

・出来る限りexternを止める
	-> ペット/傭兵/精霊のデータベースはインデックスではなくデータベースそのものを検索して
       返すように変更（atcommand.c, pet.*, merc.*, elem.*, npc.c, skill.c, status.c）

	-> quest_dbはそもそも公開していないのでexternを除去（quest.h）
	-> memorial_dataはそもそも公開していないのでexternを除去（memorial.h）

	-> スクリプトエラー判定用のコードをstaticに収める
       代わりに判定用の関数 script_is_error() を定義
       （elem.c, homun.c, itemdb.c, merc.c, npc.c, pet.c, script.*）

----------------------------------------
//1142 [2013/12/04] by Rayce

・gccでコンパイル時、msg.hでエラーが発生するのを修正（msg.h）

・gccでコンパイル時、「No sush file or directory」という警告が発生するのを修正（Makefile）

・status_get_race() で変数が未初期化の警告を修正（status.c）

・Linux環境で、SIGQUITを送る場合（CTRL+\）も終了処理できるように追加（core.c）

・[SQL] converterで配列のサイズが小さいためバッファオーバーフローが発生する問題を修正（char-converter.c）

----------------------------------------
//1141 [2013/12/04] by Rayce

・const.txt にサイズ系定数（Size_Small, Size_Medium, Size_Big）を追加（const.txt）

・item_db.txt のサイズ系ボーナスを定数に変更（db/item_db.txt, db/item_db_pre.txt）

・「グロリアススピア」のEquipScriptが動作していなかったのを修正（item_db.txt）
	reported by LunarPhantomさん

・item_db.txtの記述ミスを修正（item_db.txt）
	reported by LunarPhantomさん

・doc修正（item_bonus.txt, script_ref.txt）

----------------------------------------
//1140 [2013/12/04] by Rayce

・スクリプトの } 閉じの解析チェックを強化（script.*, elem.c, homun.c, itemdb.c, merc.c, npc.c, pet.c）
	-> npc_parse_script_line() を parse_script_line_curly() として script.c に共通化
	-> parse_script_line_curly() で curly_count が0になった時点でループを抜けるように改修
	-> parse_script() でも } で終わってない場合にエラー扱いにするように改修
	-> アイテム・ホム・傭兵・妖精のスクリプトの } 閉じチェックを共通化した
       parse_script_line_end() を新しく追加

・1行しかないスクリプトでエラーが発生したとき（missing right curlyなど）、表示されるエラー発生行が
  ズレる問題を修正（script.c）

・pet_db.txt および homun_db.txt の読込時、スクリプトエラーが発生すると読み込みカウントが増えない
  問題を修正（pet.c, homun.c）

・「missing right curly」が発生するアイテムスクリプトを修正（db/item_db.txt, db/item_db_pre.txt）

・スクリプト依存変数（'）を関数依存変数（'@）に変更（npc_town_hugel.txt）

----------------------------------------
//1139 [2013/12/03] by Rayce

・item 構造体と guild_member 構造体の並び順をpackに合わせて整理（mmo.h）
・mmo_status構造体の refuse_partyinvite と show_equip メンバをchar型に圧縮（mmo.h）

・merc_search_index() および elem_search_index() は -1 を返す可能性があるため、インデックスの
  値の判定を追加するように強化（status.c）

・0除算が発生する可能性を修正（bonus.c, pet.c, skill.c）

・pet_hungry() を pet_hungry_timer() にリネーム（pet.c）

----------------------------------------
//1138 [2013/12/03] by Rayce

・オートスペル、アクティブアイテム、bonus系命令の処理を pc.c から分離し、bonus.c に集約
  （bonus.*, battle.c, map.*, pc.*, script.c, skill.*）

・extraシステムを pc.c から分離し、extra.c に集約（extra.*, map.c, pc.c）

----------------------------------------
//1137 [2013/12/02] by Rayce

・Message Of The Day の処理を pc.c から msg.c に移管（atcommand.c, map.c, msg.*, pc.*）

----------------------------------------
//1136 [2013/12/02] by Rayce

・item_db.txtで使用するステータス異常の定数をconst.txtに追加（const.txt, db/item_db.txt）

・item_db.txtのスクリプトで関数が多重に呼び出されている部分を最適化
  （db/item_db.txt, db/pre/item_db_pre.txt）

----------------------------------------
//1135 [2013/12/02] by Rayce

・getbaseclass関数をscript.cからpc.cに移動（pc.*, script.c）

・以下のアイテムのオートスペル設定で、存在しない定数 EAS_ITEMNOCOST が記載されていたので削除
  （db/item_db.txt, db/pre/item_db_pre.txt）
	-> リングオブレゾナンス
	-> マグマフィスト
	-> アイシクルフィスト
	-> エレクトリックフィスト
	-> サイズミックフィスト
	-> 魔法のやかん

・以下のアイテムのボーナス設定で、存在しない定数 bAddFixCastRateAll が記載されていたので修正
  修正情報不明につきrAthenaから適当に移植（db/item_db.txt）
	-> おいしいロリポップR

・以下のアイテムのボーナス設定で、存在しない定数 bCritAtkRate が記載されていたので
  bAddCriticalDamage を使うように修正（db/item_db.txt）
	-> 虐殺のカタール(特攻)
	-> 戦慄のカタール

・以下のアイテムのボーナス設定で「Eff_Burning」のスペルミスを修正（db/item_db.txt）
	-> イグニスステイル
	-> バナスパティカード

・以下のアイテムのボーナス設定で「Eff_Silence」のスペルミスを修正（db/item_db.txt）
	-> カプラの猫耳ヘアバンド

・以下のアイテムのボーナス設定で「Rct_NonBoss」のスペルミスを修正（db/item_db.txt）
	-> サムライマスク

・以下のアイテムの状態異常設定で「SC_BLESSING」のスペルミスを修正（db/item_db.txt）
	-> 神妙な缶詰

・以下のアイテムで、非推奨の function_jobgroup.txt の関数を呼び出しているので修正
  修正情報不明につきrAthenaから適当に移植（db/item_db.txt）
	-> 3Dメガネ
	-> 3DメガネR

・以下のアイテムで、存在しない状態異常 SC_ELEMENTUNDEAD を SC_UndeadArmor に修正（db/item_db.txt）
	-> キュアーフリー

・以下のアイテムで不要な変数 n gが記載されていたので削除（db/item_db.txt, db/pre/item_db_pre.txt）
	-> ボーンヘッド

----------------------------------------
//1134 [2013/12/02] by Rayce

・pet_db.txt についても Auriga-1131 で const.txt に新しく定義した定数を使うように変更（db/pet_db.txt）

・アイテムボーナスの bRace のパラメータチェックの強化（pc.c, doc/item_bonus.txt）

・script_auriga.conf の refine_posword に余計な文字が混入していたのを修正（conf/script_auriga.conf）

・タイマーのtick変数には出来る限り unsigned を付与する（clif.*, map.h, pc.h, pet.c, skill.c）

----------------------------------------
//1133 [2013/12/02] by Rayce

・アイテムボーナス用の配列サイズのハードコーディングを避けるため定数を定義（map.h, pc.c）
	-> MAX_BONUS_CLASS: アイテムボーナスのクラスの容量
	-> MAX_BONUS_ADDDROP: アイテムボーナスのドロップの容量
	-> RCT_ALL: 全種族用

・bWeaponAtk と bWeaponAtkRate の配列は WT_MAX が最大なので、引数に指定できる数値を23までに制限する
  （doc/item_bonus.txt, battle.c, pc.c, status.c）

・item_db.txt について、Auriga-1131で const.txt に新しく定義した定数を使うように変更
  （db/item_db.txt, db/pre/item_db_pre.txt）

・item_db.txt の「サムライマスク」と「幸福の帽子」の bonus2命令の引数の使い方が間違っていたので修正（db/item_db.txt）

----------------------------------------
//1132 [2013/12/02] by Rayce

・Auriga-1130で更に size_t の型変換警告が出るのを修正（login.c, char.*, clif.c）
	reported by NP3228さん

----------------------------------------
//1131 [2013/12/02] by Rayce

・db/mob_group_db.txtのグループIDが MAX_MOBGROUP を越えるときは警告を表示し、スキップするように修正（mob.c）
	-> status_get_group() は補正せずに db/mob_group_db.txt のグループIDを返す。
       そのため敵グループ系のアイテムボーナス利用時に配列がバッファオーバーフローするため

・db/item_group_db.txtのグループIDが MAX_ITEMGROUP を越えるときは警告を表示し、スキップするように修正（itemdb.c）
	-> itemdb_group() は補正せずに db/item_group_db.txt のグループIDを返す。
       そのため bItemHealRate のアイテムボーナス利用時に配列がバッファオーバーフローするため

・装備関連のアイテムボーナス用の配列サイズが小さいので 11⇒EQUIP_INDEX_MAX まで拡張する（map.h）
	-> current_equip_item_index を使用するケースが該当する

・AddEff系アイテムボーナス用の配列サイズを MAX_SKILL_ADDEFF 定数で固定して整合性を取る（map.h, pc.c）

・MAX_SKILL_ADDEFF が状態異常の配列数なのか bAddEffSkill で登録できる容量なのか曖昧なので再定義（map.h, battle.c, pc.c, skill.c）
	-> MAX_EFF_TYPE: アイテムボーナスの状態異常の数
	-> MAX_SKILL_ADDEFF: bAddEffSkillで登録できる容量

・bBreakMyEquipWhenAttack と bBreakMyEquipWhenHit が bonus2 でも使えるように重複定義されていたので削除（pc.c）

・bLossEquipWhenHit の説明が無かったので追記（doc/item_bonus.txt）

・bonus系のパラメータチェックを強化（pc.c）

・db/const.txt に以下の定数を追加（db/const.txt）
	-> Rct系: 種族
	-> Ele系: 属性
	-> Emy系: 敵タイプ

----------------------------------------
//1130 [2013/12/01] by Rayce

・getequipname関数で引数に12以上で且つその部位の装備がない場合にバッファオーバーフローが
  発生するバグを修正（script.c, conf/script_auriga.conf）

・clif_disp_overhead() における型変換の警告を修正（clif.c）
	reported by NP3228さん

・メッセージ長を格納する変数は size_t型 に統一する
  （int_guild.c, int_party.c, inter.c, clif.*, guild.*, intif.*, party.*）

・1128のconst付与の抜け漏れ追加修正

----------------------------------------
//1129 [2013/12/01] by Rayce

・サーバースナップショット（version.h）

・0882で混入したwarpフォルダの削除

----------------------------------------
//1128 [2013/12/01] by Rayce

・スクリプトのunittalk命令でgccの警告が発生するのを修正（script.c）

・ファイル名の配列サイズを256まで拡張（malloc.c）

・堅牢性向上のためchar型ポインタの引数にconstを付与する

・DYNAMIC_SCDATAをデフォルトで有効にしてみる（vc_make.bat, bcc32_make.bat, Makefile, *.dsp）

----------------------------------------
//1127 [2013/11/27] by refis

・ポートマラヤNPCのマップサーバー変数構造を変更 (npc_town_portmalaya.txt)
	Thanks NP3228 さん

・メモリアル「封印された神殿」で、1Fパートが進行しないミスを修正 (npc_memorial_baphomet.txt)
	Thanks さいこ さん

・フラッグNPCにエンブレム情報が反映されない不具合を修正 (clif.c)

・clif_disp_overhead関数で型変換エラーが発生していたのを修正 (clif.c)
	Thanks NP3228 さん

・ロイヤルガードスキル「ムーンスラッシャー」を槍専用スキルに修正 (skill_require_db.txt)
	Thanks ねぴぴ さん

・リフレクトダメージ、フォースオブバンガード、バンディング、ストライキング状態においてSP自然回復するよう修正 (pc.c)
	Thanks ねぴぴ さん

・メカニックスキル「セルフディストラクション」に魔導ギアライセンス効果が乗るように魔導ギア解除タイミングを変更 (skill.c)

----------------------------------------
//1126 [2013/11/22] by refis

・ポートマラヤNPC実装 (npc_town_portmalaya.txt)
	-> 警戒する街クエスト実装
	-> 街の救済者クエスト実装
	-> 街を思う少女クエスト実装
	-> ペリー号のゴーストクエスト実装
	-> 新任看護師と病院クエスト実装
	-> 森の中の秘密クエスト実装
	-> バコナワの伝説クエスト実装
	-> 消えた住民とバコナワクエスト実装
	-> 鉄鍋クエスト実装
	-> ジェジェリンの落し物クエスト実装
	-> パンドイのシルバーブレイドクエスト実装
	-> 警備犬バンタイクエスト実装
	-> マリスの子供探しクエスト実装
	-> 旅人の友達カプレクエスト実装
		※メモリアルダンジョンは未実装です

・ポートマラヤ関連NPC追加 (npc_misc_guide.txt, npc_misc_kafra.txt)

・ポートマラヤ追加マップのwarp更新 (npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt)

・ポートマラヤ追加マップのmapflag更新 (mapflag.txt)

・ポートマラヤ追加マップのmonster出現定義追加 (npc_monster_mafild.txt, npc_monster_malaya.txt)

・mob_skill_db.txt更新 (db/mob_skill_db.txt)

・quest_db.txt更新 (db/quest_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

・影狼・朧関連交換NPCの文法誤りを修正 (npc_job_47kaboro.txt)
	Thanks Gee さん

----------------------------------------
//1125 [2013/11/19] by refis

・影狼・朧エンチャントが必ずキャンセルされるミスを修正 (npc_job_47kaboro.txt)

----------------------------------------
//1124 [2013/11/19] by refis

・スーパーノービス限界突破クエストのエラーを修正 (npc_job_46supernovice2.txt)
	Thanks NP3228 さん

・スクリプト命令「downrefitem」を実装 (doc/script_ref.txt, script.c)
	-> 指定箇所の装着済み装備品の精錬数値を下降させます

・影狼・朧転職実装
	-> 転職クエストを実装 (map_auriga.conf, quest_db.txt, npc_job_47kaboro.txt)
	-> 関連アイテム販売の追加 (npc_job_29ninja.txt)
	-> 関連アイテムのスロットエンチャント追加 (npc_quest_slotenchant.txt)

・影狼・朧のジョブ補正を修正 (job_db2.txt, job_db2-2.txt)
	Thanks SOLDIER_POPORING さん

・MAX_QUEST_DBを1000から1500に拡張 (common/mmo.h)

・item_db更新 (item_db.txt, item_db2.txt)
	Thanks luin さん、sango さん

----------------------------------------
//1123 [2013/11/17] by refis

・ニーズヘッグの巣が正常進行されない不具合を修正 (npc_memorial_nydhogg.txt)
	Thanks mayura さん

・リヒタルゼンガイドNPCが正常動作していなかったのを修正 (npc_misc_guide.txt)
	Thanks mayura さん

・攻城戦でエンペリウム破壊時のアナウンス情報を修正 (npc_gvg_global.txt)

・スーパーノービス限界突破クエスト実装 (map_auriga.conf, quest_db.txt, npc_job_46supernovice2.txt)

----------------------------------------
//1122 [2013/11/14] by refis

・イグドラシルNPC更新 (mapflag.txt, npc_quest_ashvacuum.txt, npc_quest_yggdrasil.txt)
	-> 守護者クエストを実装

・ニーズヘッグの巣NPC実装 (conf/map_auriga.conf, db/memorial_db.txt, mapflag_memorial.txt, npc_memorial_nydhogg.txt)

----------------------------------------
//1121 [2013/11/10] by Rayce

・Auriga-1120において、LOCALZLIBを有効にするとコンパイルエラーが発生するのを修正（grfio.c）
・不用意に exit(1) でサーバを停止しないように修正（itemdb.c, party.c）

・細かいリファクタリング（pc.c, status.c）

----------------------------------------
//1120 [2013/11/10] by Rayce

・「幻術 -朧幻想-」で0除算が発生する可能性を修正（skill.c）

・RFIFOQ, WFIFOQ, RBUFQ, WBUFQ は atn_bignumber型でキャストすると処理系によってはdouble型で
  扱われるため、uint64型でキャストするように変更（socket.h）

・読み込みに使用した zlib.dll のファイルパスを表示するように拡張（grfio.c）

・細かいリファクタリング（skill.c, itemdb.c, mob.c）

----------------------------------------
//1119 [2013/11/05] by refis

・エルディカスティスNPC実装 (npc_town_dicastes.txt, npc_warp_dun.txt, npc_warp_town.txt)
	-> エルディカスティスクエスト実装
	-> 猫耳と尻尾の男クエスト実装
	-> 友達のためにクエスト実装
	-> ディエルの依頼クエスト実装
	-> 文書クエスト実装

・エルディカスティス関連マップのmob追加 (npc_monster_dicdun.txt, npc_monster_dicfild.txt)

・エルディカスティス関連モンスターのskill追加 (db/mob_skill_db.txt)

・quest_db.txt更新 (db/quest_db.txt)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1118 [2013/11/03] by refis

・[RE]:ハンタースキル「ランドマイン」、「ブラストマイン」、「クレイモアトラップ」ダメージ計算式を修正 (battle.c)
	Thanks hikaru1112 さん

----------------------------------------
//1117 [2013/11/03] by refis

・修羅スキル「点穴 -反-」、朧スキル「幻術 -朧幻想-」でサーバークラッシュする問題を修正 (skill.c)
	Thanks hikaru1112 さん

----------------------------------------
//1116 [2013/11/02] by refis

・アッシュ・バキュームNPC更新 (npc_quest_ashvacuum.txt)
	-> 知恵の王の指輪クエスト関連メッセージの追加
	-> 駐屯地東側への転送NPC実装
	-> 不思議な岩の不具合を修正
		Thanks Akayumi さん

----------------------------------------
//1115 [2013/11/02] by refis

・quest_db.txt更新 (db/quest_db.txt)

・エピソードナンバリングの誤りを修正 (npc_monster_nyddun.txt)

----------------------------------------
//1114 [2013/11/02] by refis

・封印された神殿のマップフラグが追加されていなかったのを修正 (mapflag_memorial.txt)

・ユグドラシルNPC実装 (npc_quest_yggdrasil.txt, npc_town_manuk.txt, npc_town_splendide.txt)
	-> 知恵の王の指輪クエスト実装
	-> 二つの種族クエスト実装
	-> 異種族の調査クエスト実装
	-> リーンの依頼クエスト実装
	-> ドラコの卵クエスト実装
	-> ラフィネ族のヤイクエスト実装
	-> アールブヘイムの香水クエスト実装
	-> マヌクのモンスター討伐クエスト実装
	-> ブラディウムクエスト実装
	-> ミッドガルド大陸の鉱石クエスト実装
	-> 猫の手サービスクエスト追加NPC実装
　※アルベルタの少年クエスト、守護者クエストは未実装

・ユグドラシル関連マップのmob追加 (npc_monster_nyddun.txt)

・ユグドラシル関連マップのmapflag追加 (mapflag.txt)

・map_auriga.conf更新 (map_auriga.conf)

----------------------------------------
//1113 [2013/10/29] by refis

・海底都市モンスターの使用スキルを追加、ポートマラヤモンスターの使用スキルの誤りを修正 (mob_skill_db.txt)

・「守護者の記憶の破片」モンスターのセリフ順序の誤りを修正 (mob_talk_db.txt)

・1112での引数拡張が変数名とenumで重複していたので変数名を変更 (clif.*)

・影狼朧スキル「十六夜」、「土符：剛塊」、朧スキル「幻術 -残月-」の計算処理をPREとRENEWALで分ける (battle.c, pc.c, status.c)
	-> 「十六夜」、「幻術 -残月-」は本来ステータス窓に反映されませんが計算量の少なくなるstatus.c側で据え置き
	-> PRE環境において、「土符：剛塊」のAtk上昇効果が不明のため据え置き、Def上昇効果が大きすぎるため減算Def上昇に置き換え

----------------------------------------
//1112 [2013/10/26] by refis

・スクリプトからシャドウ装備を参照できるよう拡張 (doc/script_ref.txt, script.c)

・グローバルメッセージ関係の修正
	-> clif_GlobalMessage系でエリア指定ができるよう引数を拡張 (atcommand.c, clif.*, npc.c, skill.c)
		-> 関連enumをヘッダに移動しました
	-> clif_parse_GlobalMessageからメッセージ送信処理をclif_disp_overheadとして分離する (clif.*)
	-> モンスターメッセージの有効範囲をAREA_CHAT_WOCからAREAに変更 (mob.c)
	-> スクリプト命令「unittalk」を実装 (doc/script_ref.txt, script.c)
		-> マップ配置済みNPC、もしくは指定IDのユニットに発言させます
		-> globalmesとの違いは自動で発言者名が付加されないこと、前者に比べて有効範囲が広いことです

・スクリプト命令「delequip」を実装 (doc/script_ref.txt, script.c)
	-> 指定箇所の装着済み装備品を失います

----------------------------------------
//1111 [2013/10/19] by refis

・封印された神殿NPC実装 (conf/map_auriga.conf, npc_memorial_baphomet.txt)

・エンドレスタワー通常階での討伐処理を修正 (npc_memorial_tower.txt)

----------------------------------------
//1110 [2013/10/02] by Rayce

・scriptの sqlquery 関数において、LIKEで % を検索するとき % が消えてしまい部分検索が
  出来ない問題を修正（script.c）

	-> SQL文を一旦 vsprintf に流し込むため、% がフォーマット識別子として認識されているのが原因
		例）sqlquery("SELECT * FROM `db` WHERE `user` LIKE '%test%'");
				↓
		    sqlquery("SELECT * FROM `db` WHERE `user` LIKE 'test'")

    -> sqldbs_query() ではなく sqldbs_simplequery() を実行するように変更

・MySQL接続後、SET NAMES で文字コードを送るようにした（sqldbs.c）
	-> mysql_options(MYSQL_SET_CHARSET_NAME) は SET NAMES と組み合わせて使うもの
	   http://d.hatena.ne.jp/shibason/20090912/1252753970

・VCCのコンパイルパスにVC2008とVC2010のExpressEdition以外の情報を追加（vc_make.bat）

----------------------------------------
//1109 [2013/09/26] by refis

・王位継承クエストの一部イベントが進行しない不具合を修正 (npc_town_prontera.txt)

・買取露店に売却の際、買取個数を超過すると露店が終了する不具合を修正 (buyingstore.c)
	Thanks Akayumi さん

・プリーストスキル「ターンアンデット」の条件判定を修正 (skill.c)
	-> 不死以外のモンスターに使用時、ディレイを発生させないようにする

・モンスター移動完了時、次回動作判定までに必ず遅延が発生していたのを修正 (unit.c)

----------------------------------------
//1108 [2013/09/17] by refis

・クエストリストシステムを修正
	-> スクリプト命令「compquest」を追加 (clif.c, quest.*, script.c, doc/script_ref.txt)
		-> 受注済みクエストを達成済み状態にし、状態を閲覧できなくします
	-> スクリプト関数「checkquest」において達成済みになったクエストへ0x8の値を返すよう追加 (script.c, doc/script_ref.txt)
	-> 活性化以外の状態のクエストでは討伐更新されないよう変更 (quest.c)

・王位継承クエスト実装 (npc_town_prontera.txt)

・リボンのヘアバンドのリカラーNPCの交換処理実装 (npc_quest_hat6.txt)

・ソードマン転職関連NPCの名称を修正 (npc_job_01swordman.txt)
	Thanks Schwarzwald さん

----------------------------------------
//1107 [2013/09/13] by refis

・一部取り巻きモンスターのステータス・スキルを修正 (mob_db.txt, mob_skill_db.txt, mob_skill_db_pre.txt)

・item_db.txtの更新 (item_db.txt, item_db_pre.txt)
	-> バグfix
	-> スロットエンチャント装備の効果修正
		Thanks bunta さん、うに～く さん、Akayumi さん

・ゲフェンのテイミング商人エラーを修正 (npc_town_geffen.txt)
	Thanks Schwarzwald さん

----------------------------------------
//1106 [2013/09/05] by refis

・暴窟王の洞窟生成NPCの処理を更新 (npc_memorial_oct.txt)

・マラン島NPCを修正 (npc_town_malangdo.txt)
	-> マラン島転送NPCのチェック抜けを修正
	-> 投資相談ニャンコで猫の手サービス会員登録出来る選択肢を追加

----------------------------------------
//1105 [2013/08/18] by refis

・Auriga-1104の関数修正でNULLチェックがなかったのを修正 (script.c)
	Thanks うに～く さん

・エリア指定のモンスター出現の際、エリア指定が終点＜始点となる場合にエラーとなるのを修正 (mob.c)
	Thanks 716 さん

・イズルード海底都市NPCを実装 (map_auriga.conf, npc_quest_deepsea.txt)
	※クエストは未実装です

・イズルード海底都市関連マップのマップフラグ追加 (script/mapflag/mapflag.txt)

・イズルード海底神殿、イズルード海底都市のモンスター配置を修正 (npc_monster_izdun.txt)

・イズルード海底都市関連モンスターデータ修正 (mob_db.txt, mob_skill_db.txt)

----------------------------------------
//1104 [2013/08/17] by refis

・関数「getmapmobs」、「getareamobs」をキルイベント内で使用した際に倒した敵も数に含まれてしまうのを修正 (script.c)

・暴窟王の洞窟NPC実装 (conf/map_auriga.conf, db/quest_db.txt, script/npc/memorial/npc_memorial_oct.txt)

・暴窟王の洞窟関連マップのマップフラグ追加 (script/mapflag/mapflag_memorial.txt)

・メモリアルダンジョンデータ追加 (db/memorial_db.txt)

----------------------------------------
//1103 [2013/08/16] by refis

・状態異常「SC_ASSUMPTIO2」を実装 (db/const.txt, scdata.txt, map/battle.c, status.*)
	Thanks ARIA さん

・関数「getmapmobs」、「getareamobs」にて特定イベントのmobのみ抽出できるよう拡張 (script_ref.txt, script.c)
	-> エンドレスタワースクリプトを改修 (npc_memorial_tower.txt)
		Thanks Akayumi さん

・接続切断時の処理を修正
	-> 接続切断通知はセーブ時ではなく切断完了時に送信させる (char/char.c, map/clif.c)
	-> Auriga-1068以降不要だったセーブ後の切断処理を修正 (chrif.c)
		Thanks うに～く さん

----------------------------------------
//1102 [2013/08/16] by Blaze

・Auriga-1101の漏れを修正（clif.c）

・スキルツリーDB「db/pre/skill_tree.txt」を切り替え式ではなく、上書き式に変更（pc.c, db/pre/skill_tree_pre.txt）

・スキルツリーDBのアドオンDBを新規追加（pc.c, db/addon/skill_tree_add.txt）

・スキルツリーDBにclear指定ができるように変更（pc.c, doc/db_ref.txt）
	-> スキルIDに"clear"を定義することにより、それまで読み込んでいる職業のスキルツリーを破棄します。

・影狼朧の以下スキルのスキルツリー前提を修正。（db/skill_tree.txt）
　「風魔手裏剣 -乱華-」「幻術 -驚愕-」「幻術 -呪殺-」「幻術 -紅月-」「幻術 -朧幻想-」「幻術 -残月-」

----------------------------------------
//1101 [2013/08/15] by Blaze

・Auriga-1101のクールタイムが正常に動作しなかった不具合修正（clif.c）

----------------------------------------
//1100 [2013/08/15] by Blaze

・スキル使用のクールタイムを3次職スキル以外の全スキルに対応（map.h, pc.c, skill.c）

・朧スキル「幻術 -残月-」「幻術 -朧幻想-」を実装（skill.c, battle.c, status.c, db/scdata_db.txt）

・影狼朧スキル「幻術 -驚愕-」「幻術 -呪殺-」「幻術 -朧幻想-」「幻術 -紅月-」の使用不可時、
　失敗メッセージを出力するように修正（skill.c）

・影狼朧スキル「十六夜」の詠唱半減効果を忍者スキルのみから全てのスキルを対象に修正（battle.c）

・影狼朧の召喚符による忍術威力増加効果を修正（battle.c）

・土符：剛塊の効果が切れたとき、ATKとMATKの再計算がされてなかったのを修正（pc.c）

・影狼朧スキル「無茶投げ」の効果を修正（skill.c, db/skill_db.txt）
	-> 地面指定スキルに修正
	-> 消費金額はランダムでなく一定金額を消費するように修正

・影狼朧スキル「撒菱」の効果を修正（skill.c, db/skill_unit_db.txt）
	-> ユニット配置する数をランダムに修正
	-> ユニットの攻撃範囲を修正
	-> スタン確率を修正

・影狼朧スキル「爆裂苦無」で爆裂苦無を装備していなくても使用化に修正（db/skill_require_db.txt, db/skill_require_db2.txt）

・影狼朧スキル「黄泉返し」の効果が重複していた不具合修正（battle.c）

・影狼朧スキルの詠唱時間を修正（db/skill_cast_db.txt）

・影狼朧スキルの名称をFix（db/skill_db.txt, db/skill_db2.txt, db/skill_cast_db.txt, db/skill_require_db.txt, db/skill_unit_db.txt）

・影狼朧の基本HP、ASPDを修正（db/job_hp_db.txt, db/job_db1.txt, db/pre/job_db1_pre.txt）

・その他細かいFix（skill.c, status.c, battle.c）
----------------------------------------
//1099 [2013/08/14] by refis

・ログアウト時にクエストリスト討伐達成数を保存するよう修正 (unit.c)
	Thanks Akayumi さん

・物理攻撃スキルの距離判定順序を入れ替えてスキル毎の特殊処理を優先するよう修正 (battle.c)
	-> PRE_RENEWAL無効時、忍者スキル「畳返し」の距離判定処理が無効だったのを修正
	-> 修羅スキル「羅刹破凰撃」のLv5以上は遠距離判定になるよう修正
		Thanks hikaru1112 さん

----------------------------------------
//1098 [2013/07/31] by refis

・atn_bignumber用に新たに「RFIFOQ」、「WFIFOQ」、「RBUFQ」、「WBUFQ」を実装 (common/socket.h)

・2013-07-24eRagexeのpacket_dbを追加 (db/packet_db.txt)

・銀行システムを実装 (bank.*, clif.*, intif.c, map.h, map.dsp, map_sql.dsp, pc.c)
	-> 預金額情報の格納には「#PC_DEPOSIT」が扱われ、スクリプトから操作が可能です
	-> 上記実装のためconst.txt内で「#」文字が扱えるように拡張 (db/const.txt, script.c)

----------------------------------------
//1097 [2013/07/29] by refis

・PACKETVERによって、コスチューム装着時に装備ウィンドウ上に表示されないのを修正 (clif.c)

・座ったときに専用アイコンを表示するよう修正 (pc.*, status.h)

・doc/db_ref.txtのマージミスを修正 (doc/db_ref.txt)

----------------------------------------
//1096 [2013/07/28] by refis

・item_db2.txtにSellableフラグ、GuildStorageableフラグを追加
 (db/item_db2.txt, doc/db_ref.txt, itemdb.*, storage.c)

・売却不能フラグをDropableからSellableに変更 (npc.c)
　※従来のアイテム売値での制御も可能です

・スクリプト関数「getiteminfo」を新しいフラグが読み取れるように変更 (doc/script_ref.txt, script.c)

----------------------------------------
//1095 [2013/07/28] by refis

・script_ref.txtの一部訂正と巻き戻ってしまった箇所を修正 (doc/script_ref.txt)

----------------------------------------
//1094 [2013/07/28] by refis

・[RE]:アルケミストスキル「デモンストレーション」ダメージ計算式を修正 (battle.c)

・[RE]:「デモンストレーション」、「アシッドテラー」、「ソウルブレイカー」、
　「アシッドデモンストレーション」、「ファイアーエクスパンション(塩酸)」の魔法ダメージ部分は属性計算しないよう修正 (battle.c)

・「アスムプティオ」、「クレメンティア」、「カントキャンディダス」、「生死の境で」の
　各スキルを黄金蟲カード装着者へ使用時の挙動を修正 (skill.c)

・モンスターの再出現計算方式を変更 (doc/script_ref.txt, unit.c)
	-> 旧：spawndelay1とspawndelay2のうち、長い値を採用する方式
	-> 新：spawndelay1にspawndelay2までのランダム値を加算する方式

----------------------------------------
//1093 [2013/07/19] by refis

・NPC会話がタイムアウトした際に不必要なスクリプトスタック情報を破棄させるよう修正 (npc.c)

・UnknownPacketダンプのログ抑制のためにpacket_dbの更新 (db/packet_db.txt, clif.c)
	-> ついでにパケット長を追記

・client_packet.txtの更新 (doc/client_packet.txt)

・テーブル定義更新 (skill.h, status.h)

----------------------------------------
//1092 [2013/07/17] by Blaze

・「db/pre/skill_unit_db_pre.txt」の仕様を切り替え式ではなくaddon式に変更（skill.c, db/pre/skill_unit_db_pre.txt）
	-> 「PRE_RENEWAL」有効時に1086の「術式全開」ユニット修正が効かなかったのを修正

・「db/addon/skill_unit_db_add.txt」を新規追加。（skill.c, db/addon/skill_unit_db_add.txt）
	-> skill_unit_db.txt読み込み後に追加でオーバーライドします。

・影狼朧スキル全般の詠唱時間を修正 (db/skill_cast_db.txt)

・影狼朧スキル「十文字斬り」の効果を修正 (skill.c, battle.c)
	-> 使用者に状態異常が掛かっていたのを攻撃対象に付与するように修正
	-> 使用時、攻撃対象の隣のセルまで接近移動するように修正
	-> ダメージ計算を修正

・影狼朧スキル「召喚符」の効果を修正 (skill.c, status.c)
	-> 異なる属性の召喚符を使用時にこれまで召喚していた符をリセットするように修正
	-> 属性付与効果は召喚符の数が10個以上の場合だけに付与するよう修正（9個以下は属性付与しないように）

・影狼朧スキル「術式解放」使用時に召喚符を消費するように修正 (skill.c)

・影狼朧スキル「術式全開」を地面指定型に修正（skill.c, db/skill_db.txt）

・影狼朧スキル「霊魂絶断」「爆裂苦無」「風魔手裏剣乱華」「術式解放」のダメージ計算を修正（battle.c）

・影狼朧スキル「影武者」の効果を短剣以外でも発動するように修正（battle.c）

・影狼朧スキル「幻術‐残像」の分身召喚とバックステップ効果を実装（skill.c）
　※分身の身代わり効果は未実装です

----------------------------------------
//1091 [2013/07/15] by refis

・char-converterのsscanf関数フォーマットが一部誤っていたのを修正（char-converter.c）

・PACKETVER「20120925」以降の倉庫パケット情報が誤っていたのを修正（conf/msg_auriga.conf, clif.c）

・client_packet.txtを修正 (doc/client_packet.txt)

・2013-07-03aRagexeのpacket_dbを追加 (db/packet_db.txt)

----------------------------------------
//1090 [2013/07/12] by refis

・storage, gstorageにprivateテーブルは存在しないので削除（char-converter.c）

----------------------------------------
//1089 [2013/07/12] by refis

・txt-converterが動作するよう修正（char-converter.c, converter.c）
	Thanks hikaru1112 さん

----------------------------------------
//1088 [2013/07/11] by refis

・スクリプト関数「getclassjob」を実装（doc/script_ref.txt, pc.*, script.c）
　※1087にコードが混入したままコミットしてしまい申し訳ありません
	-> CLASS値をJOB値に変換して返します
	例：{ changebase getclassjob(getbaseclass(Class,2)),1; }

----------------------------------------
//1087 [2013/07/11] by refis

・NPCスキル「アースクエイク」使用時にサーバークラッシュする可能性を修正（battle.c）
	Thanks Blaze さん

・不死属性付与を受けたプレイヤーにブレッシング、速度増加を使用時
　固定1ダメージの攻撃が発生するよう修正（battle.c, skill.c）

・不死属性付与を受けた際、ブレッシング、速度増加状態が解除されるよう修正（status.c）

・自動ウォーグストライクの発生確率を修正（skill.c）

・ストリップアクセサリーの成功確率を修正（skill.c）
	Thanks Akayumi さん

・スキル名コメントをランダムfix（battle.c, skill.c）

----------------------------------------
//1086 [2013/07/10] by refis

・txt-converterのcharサーバーデータテーブルを更新（char-converter.c）
	Thanks hikaru1112 さん

・影狼、朧スキル「術式全開」のユニット配置を修正（skill_unit_db.txt）
	Thanks Akayumi さん

----------------------------------------
//1085 [2013/07/10] by refis

・メモリアルダンジョン複製NPCの命名規則を変更（npc.c, script.c）
	旧：表示名と識別子に付加されていた文字列「# + 3桁整数」を、
	新：識別子のみに文字列「_ + 3桁整数」を付加するように変更
		-> strnpcinfo関数の引数に「0」を渡すと複製元NPC名称が返るようになります。

・モーラ関連モンスターデータベースを修正（mob_skill_db.txt, mob_talk_db.txt）

・カート装着状態情報の取得処理をPACKETVERで切り替えるように変更（pc.*）
	Thanks ねぴぴ さん

・PACKETVER「20120307」以降の新規キャラクター作成時のパラメータ情報を訂正（chardb_sql.c, chardb_txt.c）

----------------------------------------
//1084 [2013/07/02] by refis

・エンドレスタワーでモンスター重複Popするbugfix（npc_memorial_tower.txt）
	Thanks うに～く さん

・魔導ギア搭乗時、サンクチュアリ効果が発揮されていなかったのを修正（skill.c）
	Thanks ねぴぴ さん

----------------------------------------
//1083 [2013/06/30] by refis

・mob_skill_db.txtのエモーション項で0未満の値を指定した場合
　反転した値のIDのメッセージを出すよう仕様を変更（doc/db_ref.txt mob.* skill.c）
　　例：エモーション項に「-1」を指定した場合、スキル使用時mob_talk_db.txtのID1番のメッセージを発言します

・mob_skill_db.txtの更新（db/mob_skill_db.txt）

・「サプライズアタック」状態の処理が抜けていた箇所を修正（status.c）

----------------------------------------
//1082 [2013/06/30] by refis

・「npcskillsupport」命令で発動元に存在しないNPCを指定しても実行NPCが指定される誤りを修正（script.c）
	Thanks Gee さん

・itembonus「bAddSkillHealRate」、「bAddSkillSubHealRate」の有効上限を7に修正（doc/item_bonus.txt map.h）

----------------------------------------
//1081 [2013/06/30] by refis

・2012-06-18aRagexeREのpacket_dbを一部修正 (db/packet_db.txt)
	Thanks Gee さん

・アサシンスキル「ベナムスプラッシャー」を分散スプラッシュ計算に修正（battle.c skill.c）
	Thanks Akayumi さん

・レンジャースキル「カモフラージュ」の挙動修正、Atk増加効果、Cri増加効果、Def減少効果を追加（battle.c skill.c status.c unit.c）
	Thanks Akayumi さん

・チャンピオンスキル「伏虎拳」、「連柱崩撃」のコンボ条件式を修正（skill.c）
	Thanks Akayumi さん

・エモーションが付帯しているMOBスキルが範囲攻撃の時、ターゲット分エモーションが実行されるのを修正（skill.c）

----------------------------------------
//1080 [2013/06/21] by refis

・[RE]:「EDP」状態中のスキル「ソウルブレイカー」ダメージ計算式を修正（battle.c）

・NPCスキル「セリフアナウンス」がmob_skillテーブル先頭にあると動作しない誤りを修正（skill.c）
	Thanks dallen さん

・モンクスキル「残影」の実処理と移動パケットの順序を入れ替える（skill.c）
	Thanks Akayumi さん、dallen さん

・ジェネティックスキル「スペシャルファーマシー」Lv1の作成数を1個に修正（skill.c）

----------------------------------------
//1079 [2013/06/18] by refis

・スロットエンチャント3rd, 4th用NPCを追加（npc_quest_slotenchant.txt）
	Thanks Gee さん

----------------------------------------
//1078 [2013/06/12] by refis

・スペル保存状態中でもSP自然回復するように変更（pc.c）

・演奏、踊り状態中でもレッスンスキルのSP自然回復が有効なように変更（pc.c）

・[RE]:アサシンクロススキル「ソウルブレイカー」を必中攻撃に修正（battle.c）

----------------------------------------
//1077 [2013/06/05] by refis

・パケット0x825「シングルサインオンログイン要求」を実装（login.c）

----------------------------------------
//1076 [2013/06/04] by refis

・1075がコンパイルエラーになるミスを修正（battle.c）

・[RE]:アコライトスキル「エンジェラス」の減算Def上昇効果を修正（status.c）

・[RE]:ウィザードスキル「ファイアーピラー」、「フロストノヴァ」の効果範囲を修正（skill.c）

・[RE]:イドゥンの林檎の回復効果を5秒毎発生させるように修正（skill.c）

・[RE]:子守唄の睡眠状態異常効果を4秒毎発生させるように修正（status.c）

----------------------------------------
//1075 [2013/06/03] by refis

・メカニックスキル「アームズキャノン」、影狼・朧スキル「八方苦無」で矢の消費量が誤っていたのを修正（battle.c, skill.c）
	Thanks Akayumi さん

・[RE]:スパイダーウェブ状態と属性補正の計算位置を修正（battle.c）

・[RE]:モンクスキル「阿修羅覇鳳拳」、忍者スキル「一閃」を以下のように修正（battle.c）
	-> 武器属性の影響を受け、属性適用及び属性補正の影響を受けない最終無属性攻撃

・[RE]:1071の「リフレクトシールド」スキル修正内容に欠落があったため補足修正（battle.c）

----------------------------------------
//1074 [2013/06/03] by refis

・[RE]:ストーンスキン、アンチマジックのpre仕様が一部残留していた箇所を修正（status.c）

・[RE]:状態異常リニューアルの実装（status.c）
	-> 状態異常の耐性計算にレベル偏差の実装
	-> 状態異常の耐性ステータスを変更
	-> 状態異常の耐性装備が状態異常持続時間に影響を及ぼすよう変更
		状態異常持続時間に対するレベル偏差は未実装です
		各状態異常の固定持続時間は暫定です

・アークビショプスキル「クリアランス」修正、ドキュメントの更新（db/scdata_db.txt, doc/db_ref.txt, skill.c）

----------------------------------------
//1073 [2013/06/02] by refis

・[RE]:1071のハンタートラップスキル修正をロールバック（battle.c, skill.c）
	Thanks rapis さん

・[RE]:1071以降、スーパーノービス以外でSP自然回復しなくなっていたのを修正（pc.c）
	Thanks user5577 さん

----------------------------------------
//1072 [2013/06/02] by refis

・高級武器の箱リストから未実装アイテムをコメントアウトしておく（db/item_random.txt）

・mob_random.txt更新（db/mob_random.txt）

・三ヶ国への報告書クエストの一部Limit値を修正（db/quest_db.txt）

・アークビショップスキル「エクスピアティオ」のアイコン情報の誤りを修正（status.h）

・ロイヤルガードスキル「シールドスペル」の範囲攻撃のダメージ倍率を修正（battle.c）

----------------------------------------
//1071 [2013/06/02] by refis

・アサシンスキル「ベナムスプラッシャー」をpreとREで分割（battle.c, skill.c）

・[RE]:ローグスキル「クローズコンファイン」の持続時間を修正（skill_cast_db.txt, pre/skill_cast_db_pre.txt）

・[RE]:ガンスリンガースキル「ダスト」、忍者スキル「畳返し」のノックバック距離を修正（skill_db.txt, pre/skill_db_pre.txt）

・[RE]:忍者スキル「雷撃砕」を地面対象スキルに修正（skill_db.txt, pre/skill_db_pre.txt）

・[RE]:忍者スキル「風魔手裏剣投げ」を詠唱妨害不可に修正（skill_db.txt）

・[RE]:ハンタースキル「ブラストマイン」、「クレイモアトラップ」を分散スプラッシュ攻撃に修正（battle.c, skill.c）

・[RE]:セージの属性場系列スキルの支援効果が一部適用されていなかったのを修正（battle.c, status.c）

・[RE]:クルセイダースキル「リフレクトシールド」を自身の最大HPまで反射可能なように修正（battle.c）

・[RE]:爆裂波動状態でも通常の50%の速度でSP自然回復するよう修正（pc.c）

----------------------------------------
//1070 [2013/05/31] by refis

・NPCスキル「ワイドサイト」修正（skill.c, status.c）
	効果範囲 11*11セル -> 29*29セル

・NPCスキル「クリティカルスラッシュ」のダメージ倍率をSkillLv*100%に変更（battle.c）

・[RE]:スピアクイッケン状態でのクリティカル上昇が一桁少なかったのを修正（status.c）

・[RE]:騎乗修練スキルの効果が反転していた不具合を修正（status.c）

----------------------------------------
//1069 [2013/05/29] by refis

・メモリアルダンジョン複製NPC削除時のタイマーイベント停止をスクリプト型NPCに限定させる（map.c）

----------------------------------------
//1068 [2013/05/28] by refis

・[RE]:グラビテーションフィールドのダメージ計算を修正（battle.c）

・データ不整合が起きる可能性があるので
　0966のクライアントのデストラクタ処理を巻き戻し（clif.c）
	Thanks Akayumi さん

・マップ読み込み時にデータが初期化されない場合があるので初期化を明示させておく（map.c）

・memorial_data構造体はexternさせて利用させるよう修正（memorial.*）

・メカニックスキル「マジックデコイ」の最大設置数制限が機能していなかったのを修正（skill.c）
	Thanks Akayumi さん

----------------------------------------
//1067 [2013/05/20] by refis

・マラン島NPC実装（npc_town_malangdo.txt）
	-> 猫達の定期集会クエスト実装
	-> ニャンキー団クエスト実装
		Thanks Pneuma さん

・マラン島関連マップのwarp追加（npc_warp_dun.txt, npc_warp_town.txt）

・マラン島関連マップのmob追加（npc_monster_malangdo.txt）

・mapflag.txtの更新（mapflag.txt）

・quest_db.txtの更新（quest_db.txt）

・map_auriga.confの更新（map_auriga.conf）

・モンスター「ブラディウムゴーレム」使用スキルの誤りを修正（mob_skill_db.txt）

----------------------------------------
//1066 [2013/05/20] by refis

・モンスター「ダンデリオンのメンバー」のステータス修正（mob_db.txt, pre/mob_db_pre.txt）

・アイテム「足鎖」のセット効果を修正（item_db.txt, mob_group_db.txt）

・item_db.txtの更新（const.txt, item_db.txt, item_random.txt）

・item_db2.txtの更新（item_db2.txt）

・mob_db.txtの更新（mob_db.txt）

・mob_skill_db.txtの更新（mob_skill_db.txt）

----------------------------------------
//1065 [2013/05/19] by refis

・[RE]:攻撃を回避出来なかった場合、追加状態異常判定するよう修正（battle.c）

・[RE]:全てのターゲット指定スキルに詠唱反応するよう修正（unit.c）

・一部3次職業スキルの使用時挙動を修正（skill.c）

----------------------------------------
//1064 [2013/05/18] by refis

・戦闘設定「npc_timeout_time」を追加（battle_auriga.conf battle.* map.h npc.* pc.c script.c）
	-> NPCの会話が自動で終了する入力待機猶予時間を設定します

----------------------------------------
//1063 [2013/05/18] by refis

・プレイヤー出現時に状態異常エフェクトが表示されないのを修正（clif.*）
	Thanks Akayumi さん

・NPCスキル「エモーション」で非アクティブ移行時、ターゲット解除されない場合があるのを修正（skill.c）

・[RE]:プロフェッサースキル「ソウルチェンジ」の仕様を相互SP折半に修正（skill.c）

----------------------------------------
//1062 [2013/05/14] by refis

・1061のファイル構造抜けを修正（pre/refine_db_pre.txt）

----------------------------------------
//1061 [2013/05/14] by refis

・refine_dbで各精錬毎にボーナス値を設定できるようDBテーブルを拡張（status.c）
	-> 「精錬成功率:総ボーナス値」の形式で各Lv毎に設定ができます。
	-> 省略した場合、精錬ボーナス値*精錬値の値が適用されます。

・refine_dbのR化前/後のDB対応の為、pre/refine_db_pre.txtを追加（status.c）
	-> 「PRE_RENEWAL」有効時、refine_db.txtの代わりにpre/refine_db_pre.txtを読み込みます。

・refine_db.txtをR化後データに合わせて修正（refine_db.txt）

----------------------------------------
//1060 [2013/05/14] by refis

・1059でskill_treeデータが読み込めないミスを修正（pc.c）
	Thanks rusya7234 さん

----------------------------------------
//1059 [2013/05/13] by refis

・attr_fix, skill_tree, skill_unit_dbのR化前/後のDB対応の為以下のDBを追加（pc.c, skill.c）
	-> 「PRE_RENEWAL」有効時、通常DBの代わりに以下のDBを読み込みます。
	　・attr_fix_pre.txt
	　・skill_tree_pre.txt
	　・skill_unit_db_pre.txt

・attr_fix.txt, skill_tree.txt, skill_unit_db.txtをR化後データに合わせて修正（attr_fix.txt, skill_tree.txt, skill_unit_db.txt）

----------------------------------------
//1058 [2013/05/12] by refis

・[RE]:アルケミストスキル「斧修練」が片手剣にも影響するよう修正 (battle.c)
	Thanks ARIA さん

・「pc_itemlimit_timer」が正常に削除されていなかったのを修正 (pc.c)
	Thanks mayura さん

----------------------------------------
//1057 [2013/05/12] by refis

・[RE]:ヒール系スキルのみにMATK分の回復量が加算されるよう修正 (skill.c)

・魔導ギア解除時にカート優先で解除される現象を修正 (pc.c)
	Thanks ねぴぴ さん

・魔導ギア装着中に死亡時、魔導ギアを解除するよう修正 (pc.c)

・3次新毒スキルが重複適用されないよう修正 (status.c)
	Thanks Akayumi さん

・シャドウチェイサースキル「デッドリーインフェクト」に伝染失敗確率を実装 (status.c)
	Thanks Akayumi さん

----------------------------------------
//1056 [2013/05/09] by refis

・0x99bの下位版、0x2e7を追加 (db/packet_db.txt, clif.*, map.*)

・マップフラグ「town」を追加 (const.txt, script_ref.txt, mapflag.txt, atcommand.c, map.h, npc.c, script.c, skill.c)
	-> マップフラグ「nopenalty」有効時のスキル使用不可処理を移譲
	-> 街MAPに「town」フラグを追加

・室内MAPにマップフラグ「noicewall」を追加 (mapflag.txt)

・一部クエストMAPにマップフラグ「noskill」を追加 (mapflag.txt)

----------------------------------------
//1055 [2013/05/08] by refis

・2012-06-18aRagexeREのpacket_dbを修正 (db/packet_db.txt)
	Thanks Akayumi さん

・[RE]:ロイヤルガードスキル「シールドスペル」Lv1の効果異常を修正 (skill.c)
	Thanks shisuka さん

・[RE]:ホムンクルスのステータス計算を修正 (homun.c, status.c)

・パケット0x99b「マッププロパティ通知」を実装 (db/packet_db.txt, clif.*)
	-> UnknownPacketダンプのログ抑制のためにpacket_db.txtの更新
	-> カートウィンドウ開閉のための暫定処理です

----------------------------------------
//1054 [2013/05/08] by refis

・パケット0x82dを実装（char.c）

・MOBAI「スキル無効」実装 (db/mob_db.txt doc/db_ref.txt battle.c skill.c status.h)

・状態異常「ジャイアントグロース」の発動確率と計算位置を修正 (battle.c)

----------------------------------------
//1053 [2013/05/07] by refis

・PACKETVER「20120404」を追加 (vc_make.bat bcc32_make.bat Makefile clif.* mob.c)
	-> パケット0x977「モンスターHPバー更新」を実装

・PACKETVER「20120618」を追加 (vc_make.bat bcc32_make.bat Makefile clif.c)
	-> 状態異常アイコン表示に0x8ffではなく0x983を利用するようにする

・アイテム情報の装着箇所情報を修正
 (common/mmo.h, char/sql/chardb_sql.c, char/sql/maildb_sql.c, char/txt/chardb_txt.c, char/txt/maildb_txt.c,
　char/txt/storagedb_txt.c, converter/char-converter.c, converter/inter-converter.c)

・TXT:AURIGA_JOURNALを17に引き上げ (common/journal.c.)

・SQL:インベントリテーブルの装着箇所情報を修正（sql-files/main.sql, sql-files/Auriga1053_changetable.sql）

・テーブル定義更新 (db/packet_db.txt clif.c skill.h status.h)

・client_packet.txtを少し追記と修正 (doc/client_packet.txt)

----------------------------------------
//1052 [2013/05/07] by refis

・map_sql.dspの誤り修正（map_sql.dsp）

----------------------------------------
//1051 [2013/05/07] by refis

・dspファイルにmsg.*が抜けているので修正（map.dsp, map_sql.dsp）

・2013-03-20eRagexeのpacket_dbを追加 (db/packet_db.txt)

・暫定的にPACKETVER「20120925」を追加 (vc_make.bat bcc32_make.bat Makefile *.dsp clif.c)
	-> 0xaa、0xac、0x2d4、0x8c7、0x900、0x901、0x902、0x903、0x904、0x905、0x906の上位版、
	   0x990、0x991、0x992、0x993、0x994、0x995、0x996、0x997、0x999、0x99a、0x99fを追加

・シャドウ装備用に処理を拡張 (doc/db_ref.txt clif.c itemdb.h map.h pc.c)

----------------------------------------
//1050 [2013/05/03] by refis

・頭装備作成NPCのミスを修正（map_auriga.conf npc_quest_hat6.txt）

・モンスターのATK, MATKを修正
	-> mob_db.txtのATK1, ATK2項目を暫定値で更新（db/mob_db.txt）
	-> 戦闘設定「monster_atk2_to_matk」を追加（battle_auriga.conf battle.* status.c）
		「PRE_RENEWAL」無効時にyesの場合、mob_db.txtのATK2項目をMATKとして扱い、RENEWAL用計算されます
		それ以外の場合、今まで同様の計算処理になります

----------------------------------------
//1049 [2013/05/01] by refis

・skill_cast_dbをリニューアルデータに更新（skill_cast_db.txt, skill_cast_db_pre.txt）

・1048で忍者関連NPCがduplicateエラーを起こしていたのを修正（npc_job_29ninja.txt）
	Thanks うに～く さん

----------------------------------------
//1048 [2013/04/29] by refis

・カプラ転送拡張、ウンバラ属性石分解NPC調整を取り込み（npc_town_umbala.txt npc_misc_kafra.txt）
	Thanks boitata さん

・MAP定義を更新（conf/map_auriga.conf）

・ガンスリンガー、忍者、メカニック関連NPCを追加（npc_job_28gunslinger.txt npc_job_29ninja.txt npc_job_thirdclass.txt）

・頭装備作成NPCを追加（db/quest_db.txt npc_quest_hat6.txt）

・次元の狭間01のワープポイント実装（npc_warp_fild.txt）

・次元の狭間01のコンチネンタルガードが接触反応するので修正（npc_town_morocc.txt）

----------------------------------------
//1047 [2013/04/25] by refis

・ELEM, HOM, MERC, PET呼び出し時、unit_datasetより先にunit_calc_posが呼ばれるため
　nullpoエラーが発生するのでunit_calc_posの第一引数をblock_listに変更して回避させる
（elem.c homun.c merc.c pet.c unit.*）

----------------------------------------
//1046 [2013/04/23] by refis

・太陽と月と星の融合、カイト、バードとダンサーの魂、
　ウィザードの魂、アサシンの魂状態をpreとREで分割（battle.c pc.c skill.c）

・warp定義を追加更新（npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt）

----------------------------------------
//1045 [2013/04/17] by refis

・Aspd向上効果の計算処理が誤っていたのを修正（status.c）
	Thanks nekoko さん

----------------------------------------
//1044 [2013/04/15] by refis

・ASPD計算式をpreとREで分割（db/job_db1_pre.txt db/pre/job_db1_pre.txt status.c）
	-> 盾装備時のASPDペナルティの対応
	-> DB対応の為、pre/job_db1_pre.txtを追加
		「PRE_RENEWAL」有効時、job_db1.txtの代わりにpre/job_db1_pre.txtを読み込みます。

・拡張スーパーノービスの経験値、JOB補正テーブルを修正（db/job_db2.txt db/job_db2-2.txt pc.c）

・typo修正（npc_memorial_tower.txt）

----------------------------------------
//1043 [2013/04/15] by refis

・状態異常「SC_EXEEDBREAK」のtypo修正（status.c）
	Thanks うに～く さん

・mob_db_pre.txtが正常に読み込まれない問題を修正（mob.c）
	Thanks ねぴぴ さん

----------------------------------------
//1042 [2013/04/07] by refis

・db_ref.txtの一部修正（doc/db_ref.txt）
	Thanks ねぴぴ さん

・金剛状態をpreとREで分割（battle.c status.c）

----------------------------------------
//1041 [2013/03/26] by refis

・spl_fild03にコルヌスではなくクブリンが出現するミスを修正（npc_quest_ashvacuum.txt）
	Thanks うに～く さん

・メモリアルダンジョンのNPCがタイマーイベントを発行中に削除された場合
	npc_timerevent errorが発生するのを修正（map.c）

----------------------------------------
//1040 [2013/03/25] by refis

・不要なmob_dbの更新箇所を巻き戻し（mob_db.txt）

----------------------------------------
//1039 [2013/03/25] by refis

・mob_db, mob_skill_dbをリニューアルデータに更新（mob_db.txt, mob_skill_db.txt, pre/mob_skill_db_pre.txt）
	ATK1, ATK2項目以外のステータス、ドロップ、使用スキルをR化データへ修正（非RRデータ）

・pre/mob_dbの異世界モンスターの一部にステータスが設定されていない箇所があったので修正（pre/mob_db_pre.txt）

----------------------------------------
//1038 [2013/03/25] by Rayce

・msg_auriga.conf の管理をatcommand.*から切り離し、msg.* を新設

  ※msg_txt() を使いたい場合、atcommand.h ではなく msg.h をincludeしてください。
    これにより atcommand.* との依存度を減らすことができます。

・ハードコーディングされているメッセージを msg_auriga.conf に移植（status.c）

----------------------------------------
//1037 [2013/03/25] by Rayce

・mob.h でexternしている manuk_mob 配列と splendide_mob 配列を battle_calc_damage関数内に
  移動し依存性を減らす（battle.c, mob.*）

・安全性のため、ranking_title 配列と ranking_reg 配列のサイズにMAX_RANKINGを明示する（ranking.c）

・一部の配列を可変にして柔軟性を上げる（atcommand.c, status.c）

・呼び出し回数が少ないconstからstaticを撤廃（skill.c）

----------------------------------------
//1036 [2013/03/24] by Rayce

・grfio.cで拡張子を検索するルーチンを汎用化（grfio.c）

・[SQL] utils系のSQLスクリプトに一部のテーブルが記載されてなかったので整理（sql-files/utils/*.sql）

----------------------------------------
//1035 [2013/03/24] by refis

・（RE）暖かい風の付与効果がステータスATKにも影響するよう修正（battle.c skill.c status.c）
	-> 識別のため暖かい風Lv7もSC_SEVENWINDで対応させる

・アイテムボーナスリファレンスを取り込み（doc/item_bonus.txt）
	Thanks alsion0609 さん

----------------------------------------
//1034 [2013/03/24] by Rayce

・スクリプトのmddelete命令で、引数にパーティIDを指定しても自分のPTが参照されていたのを修正（script.c）

・チャット参加時におけるバッファオーバーフロー対策（chat.c）

・char型の引数にconstを付与する（chat.*, clif.c）

・unit_distance を path.cに移動
  関数名も path_distance に改名し、unit_distance2 を unit_distance に改名する（unit.*, path.*）

----------------------------------------
//1033 [2013/03/24] by Rayce

・map.hに定義されているpath系の関数をpath.hに移動（map.h, path.h）

・map_check_dir と map_calc_dir をpath.cに移動
  関数名も path_check_dir および path_calc_dir に改名（map.*, path.*）

----------------------------------------
//1032 [2013/03/24] by Rayce

・gccでの警告修正（login_httpd.c, battle.c, clif.c）

・Linux環境で gettimeofday() の代わりに精度の高い clock_getime() を使えるように拡張（timer.c）

・タイマー削除時のエラーメッセージの内容を変更（timer.c）

・サーバ起動に失敗したときはメッセージを表示するように変更（login.c, char.c, converter.c）

・JOURNAL有効時、サーバ起動に失敗すると「delete_timer error : function dismatch」が発生する
  問題を修正（journal.c）

----------------------------------------
//1031 [2013/03/24] by Rayce

・gccでの警告修正（char.c, atcommand.c, clif.c, map.c, memorial.c, script.c, skill.c）

・@giveitem をALL指定で実行時、未認証のキャラクターにもアイテムが付与される可能性を修正（atcommand.c）

----------------------------------------
//1030 [2013/03/22] by refis

・手裏剣投げ、苦無投げ、風魔手裏剣投げ、銭投げ、畳返し、一閃、風刃のダメージ計算式をpreとREで分割（db/skill_db.txt pre/skill_db_pre.txt battle.c）

・マジカルバレット、ピアーシングショットのダメージ計算式をpreとREで分割（battle.c）

・口笛、ハミング状態をpreとREで分割（skill.c status.c）

・（RE）風魔手裏剣投げを対象指定から地面指定に修正（db/skill_db.txt pre/skill_db_pre.txt skill.c）

・（RE）インベナムの固定ダメージ加算位置を修正（battle.c）

・（RE）スプレッドアタック、霞斬り、影斬りの使用条件を修正（skill_require_db.txt, pre/skill_require_db_pre.txt）
	Thanks alsion0609 さん

・ヴェラチュールスピアのDEF計算位置を修正して処理をスリムにする（battle.c）

・点穴 -反-でMdefが減少するよう修正（skill.c status.c）

・ファイティングスピリットのAspd増加率を修正（skill.c status.c）

・シールドスペルのDEF増加にBaseLv補正を追加（skill.c）

・シールドスペルが装備Mdefの代わりにDefを利用していた箇所を修正（skill.c）

----------------------------------------
//1029 [2013/03/22] by refis

・モンク、アルケミスト系列職業スキルのダメージ計算式をpreとREで分割（db/skill_db2.txt battle.c skill.c）

・（RE）猛龍拳, 伏虎拳, 連柱崩撃は消費する気弾分のダメージも計上するように変更（battle.c skill.c）

・（RE）グランドクロス, グランドダークネスの物理部分に属性付与効果が計上されるように修正（battle.c）

・（RE）ソウルブレイカーの魔法ダメージに物理スキル倍率加算効果が乗っていたのを修正（battle.c）

・NPCスキル「不死属性変化」のデータ欠落を補完（db/skill_db2.txt）

----------------------------------------
//1028 [2013/03/22] by refis

・バード、ダンサー系列職業スキルのダメージ計算式をpreとREで分割（battle.c status.c）

・（RE）戦太鼓の響き、ニーベルングの指輪状態をpreとREで分割（battle.c status.c）

・（RE）オーバートラスト系のカートレボリューション除外チェックは無駄なので判定を減らす（battle.c）

・（RE）ソウルブレイカーの魔法ダメージに物理スキル倍率加算効果が乗っていたのを修正（battle.c）

・ヘスペルスリットに倍化処理が抜けていたのを修正（battle.c）

----------------------------------------
//1027 [2013/03/21] by refis

・ローグ系列職業スキルのダメージ計算式をpreとREで分割（battle.c skill.c）

・（RE）「SC_RAID」を実装（db/scdata_db.txt db/skill_cast_db.txt battle.c skill.c status.*）

・（RE）サプライズアタック、アローシャワーの効果範囲拡張に対応（skill.c）

・（RE）ストームガストの凍結処理変更に対応（skill.c）

・1026のDEF無視スキルの設定に抜けがあったので補完修正（battle.c）

・キリエエレイソン、セイフティウォール、ストーンスキン、アンチマジック状態をpreとREで分割（battle.c skill.c）

・（RE）戦闘設定「no_casting_int」を追加、詠唱計算式変更に対応（conf/battle_auriga.conf battle.* skill.c）
	-> 戦闘設定「no_casting_int」は戦闘設定「no_casting_dex」と併用して利用します
	-> 例：no_casting_dex150、no_casting_int115の場合、DEX+INT/2の合計が265以上で詠唱無しになります
	-> 例：no_casting_dex265、no_casting_int0の場合、DEXが265以上で詠唱無しになります

----------------------------------------
//1026 [2013/03/21] by refis

・クルセイダー系列職業スキルのダメージ計算式をpreとREで分割（battle.c）

・（RE）上記に伴ってスキル「ファイト」、「メランコリー」の計算位置を変更（battle.c）

・（RE）ファイアーピラー、スピアクイッケン、スパイラルピアースの使用条件を修正（skill_require_db.txt, pre/skill_require_db_pre.txt）

・（RE）ゴスペルATK2倍、スピアクイッケン、ファイティングスピリット、シールドスペル、プレスティージ、
　バンディング、インスピレーション、イクシードブレイク、オーディンの力状態をpreとREで分割（battle.c status.c）

・バルカンアーム、アックストルネード、ヘスペルスリットのHit数を修正（skill_db.txt）

・メカニックスキル「セルフディストラクション」はDEF減少効果の影響を受けないよう変更（battle.c）

・ストライキングのATK上昇がモンスターに対して2回かかっているのを修正（status.c）

・NPC爆裂波動（ラッシュアタック）とソウルリンカースキル「エスク」のATK倍率は加算するよう修正（status.c）
	Thanks かんなぎ さん

----------------------------------------
//1025 [2013/03/20] by refis

・アサシン系列職業スキルのダメージ計算式をpreとREで分割（battle.c）

・エイムドボルトにHit数倍化が抜けていた不具合を修正（battle.c）

・（RE）クリティカルダメージ向上効果がスキルに適用されない不具合を修正（battle.c）

・メモリアルダンジョンで中身の無いNPCをコピーするとサーバークラッシュする不具合を修正（npc.c）

・メモリアルダンジョン進行中にサーバーを落とすとメモリリークが発生する不具合を修正（map.c memorial.c）
	-> 通常のNPCとfree方法が異なるためdo_final_npc()より先にdo_final_memorial()を実行する
	-> do_final_memorial()内でmemorial_delete()を実行する

----------------------------------------
//1024 [2013/03/20] by Rayce

・名前からメモリアルダンジョンを探す際、存在しない名前を指定するとnullpoエラー
  扱いになるのを修正（memorial.c）

・意味のないNULLチェックを削除（memorial.c）

・party_searchname と guild_searchname の引数にconstを付ける（party.*, guild.*）

・ペット, ホム, 傭兵, 精霊の位置移動計算処理をunit.cに集約
  （pet.c, homun.c, merc.c, elem.c, unit.*）

----------------------------------------
//1023 [2013/03/19] by refis

・ハンター、ブラックスミス系列職業スキルのダメージ計算式をpreとREで分割（battle.c skill.c status.c）

・preコンパイルの際、「カートブースト」効果がなくなっていたミスを修正（battle.c）

----------------------------------------
//1022 [2013/03/19] by refis

・ウィザード、プリースト、セージ系列職業スキルのダメージ計算式をpreとREで分割（battle.c status.c）

・上記修正に伴い、処理位置が同一の「ベナムインプレス」「カートブースト」「フォースオブバンガード」
　「エコーの歌」「恋人たちの為のシンフォニー」のダメージ計算位置を修正（battle.c）

・（RE）物理攻撃計算に特定スキル増幅処理が抜けていたのを修正（battle.c）

・魔法攻撃計算に対象にステータス異常がある場合の補正処理を追加してナンバリングを調節（battle.c）

----------------------------------------
//1021 [2013/03/19] by refis

・一部スキルの近距離、遠距離判定を修正（skill_db2.txt）

・1019の起爆後ユニット残留時間の処理を見やすく直す（skill.c）

・スキル倍率に直接Hit数がかかっているスキルから倍化処理をDef計算以降に分離する（battle.c）

・モンスター情報のDEF、MDEF表示をpreとREで分割（clif.c）

・ナイト系列職業スキルのダメージ計算式をpreとREで分割（battle.c status.c）

・（RE）マグナムブレイクとEDPの属性ダメージ追加処理を分離（battle.c skill.c）

・（RE）呪いのAtk減少効果をスキル倍率から減算させるよう修正（battle.c）

----------------------------------------
//1020 [2013/03/19] by Blaze

・アッシュ・バキュームNPC追加（npc_quest_ashvacuum.txt）
	-> 魔王モロク追跡クエスト実装
	-> 三ヶ国への報告書クエスト実装
		Thanks to refis さん

・子供失踪クエストの旧NPCをnpc_quest_ashvacuum.txtへ移動のため削除（npc_town_morocc.txt）

・1019のビルドエラーを修正（battle.c）

----------------------------------------
//1019 [2013/03/18] by refis

・（RE）防御無視効果、錐効果の処理をpreとREで分割（battle.c）

・（RE）NPC_CRITICALSLASHは最大Atkで攻撃を行わせる（battle.c）

・（RE）矢のAtkがサイズ補正を受けないように処理順序を下げさせる（battle.c）

・（RE）修練系効果を種族耐性で軽減できるように処理順序を上げさせる（battle.c）

・ホバーリング状態でもマグネティックフィールドにかかってしまうのを修正（skill.c）
	Thanks Akayumi さん

・ファイアリングトラップとクラスターボムの起爆後ユニット残留時間を修正（skill.c）
	Thanks nekokoさん、Akayumi さん

・status_get_hit()の戻り値が1以下になる可能性があったのを修正（status.c）

----------------------------------------
//1018 [2013/03/18] by refis

・0995以降、TXT形式でキャラクターのロードが正常に行えなかったのを修正（char/txt/chardb_txt.c）

・（RE）クリティカルダメージ上昇効果が左手にかかるミスを修正（battle.c）

・（RE）NPC_CRITICALSLASHはクリティカルダメージ補正を行わない（battle.c）

・（RE）魔法ダメージ基礎計算の過剰精錬ボーナスのミスを修正（battle.c）

----------------------------------------
//1017 [2013/03/18] by Rayce

・1011以降、clif_GlobalMessage2() でメモリリークが発生していたのを修正（clif.c）
	reported by ChowZenkiさん, thx a lot!

・露店開設および買取露店開設の関数の汎用性を上げるために、タイトルの \0 補正を
  clif.cに移動する（clif.c, buyingstore.*, vending.*）

・GetSkillStatusChangeTable の呼び出しのまとめ（skill.c）

----------------------------------------
//1016 [2013/03/18] by refis

・物理、魔法ダメージの基礎計算をpreとREで分割（battle.c）

・通常物理攻撃、魔法攻撃の計算順序をpreとREで分割（battle.c status.c）

・ヒール計算式をpreとREで分割（battle.c skill.*）

----------------------------------------
//1015 [2013/03/17] by Rayce

・スクリプトのswitch構文の直後は } と case と default のみを許可するように強化（script.c）

  以下のコードは今後エラーになります。

	-	script	Tester	-1,{
	OnInit:
		switch (rand(3)) {
			debugmes "insert";
			case 0:
				debugmes "0";
				break;
			default:
				debugmes "etc";
				break;
		}
	}

----------------------------------------
//1014 [2013/03/17] by Rayce

・battle_calc_base_magic_damage でnullpo判定が正しく出来るように呼び出し順を修正（battle.c）

・battle_skill_attack 以下のスキルにおいて、評価順を入れ替えて処理速度を向上する（battle.c）
	-> リプロデュース
	-> クローンスキル
	-> サークルオブファイア

・以下のスキルにおいて、ステータスの再計算が多重に行われないように status_calc_pc_stop_begin,
  status_calc_pc_stop_end で保護するように修正（skill.c, status.c）
	-> デッドリーインフェクト
	-> アンチドート
	-> 点穴 -快-

・コード整理（battle.c, skill.c）

----------------------------------------
//1013 [2013/03/17] by refis

・リコグナイズドスペル使用時に最低MATKで固定されるミスを修正（battle.c）

・プレイヤーのAtk、Matk、Hit、Flee、Def、Mdef、CriticalをR前と後で分割（clif.c, status.c）
	RE環境において以下の変更があります
		「bMatk1」ボーナスは武器Matk上昇ボーナス扱いになります
		「bMatk2」ボーナスはステータスMatk上昇ボーナス扱いになります

・プレイヤー以外のHit、Flee、Def、MdefをR前と後で分割（status.c）

・上記に伴う命中率計算式の分割（battle.c）

・（RE）アイテムボーナス「bBaseAtk」, 「bMatk」をステータスに直接加算しないようにする
	（battle.c clif.c map.h pc.c status.c）
	RE環境において以下の変更があります
		「bBaseAtk」ボーナスはアンドレ型Atk扱いになります
		「bMatk」ボーナスは固定Matk上昇ボーナス扱いになります

----------------------------------------
//1012 [2013/03/17] by refis

・ダブルアタック未修得で二刀、カタール使用時に左手ダメージが1に補正されてしまう問題を修正（battle.c）

・呼び出しを容易にするため、battle_calc_magic_attackから基礎魔法ダメージ計算をbattle_calc_base_magic_damageとして分離させる（battle.*）

・ジェネティックスキル「ヘルズプラント」に無属性補正がなかったのを修正
	Thanks Akayumi さん

----------------------------------------
//1011 [2013/03/17] by Rayce

・脆弱性強化（clif.c, memorial.c, script.c）

・mob_talk() の引数をunsigned shortからintに変更（mob.*）

----------------------------------------
//1010 [2013/03/17] by Rayce

・getmdmapname関数およびgetmdnpcname関数をマップ未所属のNPCから実行すると
  サーバクラッシュする問題を修正（script.c）

・getmdnpcname関数の引数に長い文字を指定するとバッファオーバーフローが
  発生するのを修正（script.c）

・PCがアタッチされてない状態でmdenter関数を使用すると、リターン値がスクリプト
  スタックに戻らない問題を修正（script.c）

・メモリアルダンジョンのマップとNPCを複製する際、バッファオーバーフロー対策として
  元のマップ名やNPC名が長すぎる場合は失敗扱いにする（npc.c, map.c, memorial.c）

・MAPサーバ起動時、マップ情報が読み込めなくてもexitせずに続行するように変更
  grfファイル無しでもスクリプトのデバッグを可能にするため（map.c）

----------------------------------------
//1009 [2013/03/16] by refis

・一部スキルの近距離、遠距離判定を修正（skill_db2.txt）

・エルフの矢と狩人の矢が使用できないミスを修正（item_arrowtype.txt）

・メカニックスキル「魔導ギアライセンス」の修練加重値を修正（battle.c）

・メカニックスキル「斧修練」が鈍器にも影響を及ぼすよう修正（battle.c status.c）

・ナイトスキル「ブランディッシュスピア」のダメージ計算式の異常を修正（battle.c）

・ソードマンスキル「マグナムブレイク」のダメージ増加効果はスキル使用後に発現するよう修正（skill.c）

・ソーサラースキル「ヴェラチュールスピア」に物理ダメージが加算されるよう修正（battle.c）

・スクリプト関数「getequiprefinerycnt」で位置指定を省略した際の参照不具合を修正（script.c）

・item_dbを更新（item_db.txt）
	-> ヒール効果増加の統括function「ItemdbAlmightyHeal」の追加（item_db.txt, script/function/function_itemdb.txt）
	-> アイテムドロップ、オートスペル、オートアクティブのLv、確率を修正
	-> bAtk, bAtkRate, bAddShortWeaponDamageを使用しているアイテムの効果を適切なものに修正
	-> Matk関係がR化していない一部武器を修正

----------------------------------------
//1008 [2013/03/10] by refis

・1006,1007のコメントに誤りがあったのを修正（db/skill_unit_db.txt doc/script_ref.txt）

----------------------------------------
//1007 [2013/03/10] by refis

・モンスター操作用のスクリプト命令、関数を追加（doc/script_ref.txt map/mob.* map/script.c）
	-> callmonster 関数：モンスターを召喚し、オブジェクトIDを返します
	-> removemonster 関数：オブジェクトIDのモンスターの殺害を要求し、処理結果を返します
	-> mobuseskill 命令：オブジェクトIDのモンスターにスキルを使用させます
	-> areamobuseskill 命令：指定範囲のモンスターにスキルを使用させます

・スクリプト命令「setpartyinmap」を実装（doc/script_ref.txt script.c）

・スクリプト関数「getequipcardid」を実装（doc/script_ref.txt script.c）

----------------------------------------
//1006 [2013/03/10] by refis

・MAX_MOBSKILLを49に拡張（map/map.h）

・mob_talk_dbを追加（db/mob_talk_db.txt doc/db_ref.txt map/clif.* mob.*）

・以下のスキルを実装
	-> NPCスキル「セリフアナウンス」、「インビンシブル」、「インビンシブルオフ」
		（db/mob_skill_db.txt scdata_db.txt skill_cast_db.txt skill_db.txt skill_db2.txt src/battle.c skill.c status.*）
	-> NPCスキル「不死属性変化」、「不協和音」、「自分勝手なダンス」
		（db/skill_cast_db.txt skill_db.txt skill_db2.txt skill_unit_db.txt common/mmo.h map/battle.c skill.c status.c unit.c）
	-> 「スノーフリップ」、「ピオニーマミー」、「ぴしゃりハーブ」、「世界樹のほこり」、「エクラージュへの帰還」
		（db/skill_cast_db.txt skill_db.txt skill_db2.txt skill_require_db.txt common/mmo.h skill.c）

・無詠唱でも詠唱パケットを投げるよう修正（unit.c）
	-> ブレッシング等の無詠唱スキルがバトルチャットに表示されない問題のため

・スキル「エルディカスティスへの帰還」、「モーラへの帰還」をテレポート不可MAPでも使用できるよう修正（skill.c）

----------------------------------------
//1005 [2013/03/06] by refis

・httpdをデフォルトで無効にする補足 (login.dsp, login_sql.dsp)

・モンスターがunit_heal関数でHP0以下となっても死亡しないのを修正 (mob.c)

・addeff関連の処理を少し修正 (battle.c, skill.c, status.c)

----------------------------------------
//1004 [2013/03/04] by refis

・1001以降、通常カード効果が発揮されなかった不具合を修正 (status.c)
	Thanks うに～く さん

----------------------------------------
//1003 [2013/03/02] by refis

・MOBAI「ハイパーアクティブ」の修正 (mob.c)
	-> 最も近い敵をターゲットする処理を実装
	-> 攻撃を受けた後で待機状態に移行した場合、angry/followスイッチが復帰するよう修正

----------------------------------------
//1002 [2013/02/27] by refis

・typo修正（map/map.c script/npc/quest/npc_quest_hiddenenchant.txt）
	Thanks rapis さん

・闇販売員の修正、及びポイント商人の追加（script/npc/job/npc_job_thirdclass.txt）

----------------------------------------
//1001 [2013/02/26] by refis

・vc_make.batでコンパイラオプション「PRE_RENEWAL」が付加されない誤りを修正（vc_make.bat）

・ヒドゥンエンチャントシステムを実装
	-> カードの種類を設定するitem_cardtype.txtを追加（db/item_cardtype.txt doc/db_ref.txt map/itemdb.*）
	-> スロット外のカードも読み込むように処理を更新（pc.c script.c status.c）
	-> ヒドゥンエンチャントNPCを追加（conf/map_auriga.conf script/npc/quest/npc_quest_hiddenenchant.txt）
		Thanks Base on tomo さん

----------------------------------------
//1000 [2013/02/25] by Blaze

・コンパイラオプション「PRE_RENEWAL」を追加（Makefile, bcc32_make.bat, vc_make.bat）
	-> システムをR化前/後で切り替えます。
　	※R化システム実装完了までは"有効"推奨です。

・R化前/後のDB住み分け第1弾（itemdb.c, mob.c, skill.c）
	-> 「PRE_RENEWAL」有効時、通常DB読み込み後に以下のDBをアドオンします。
	　・item_db_pre.txt
	　・mob_db_pre.txt
	　・mob_skill_db_pre.txt
	　・skill_db_pre.txt
	　・skill_cast_db_pre.txt
	　・skill_require_db_pre.txt
	※Auriga-1000以降、db直下の各DBはR化後データをサポート、
	　R化前データは「db/pre」配下のDBでサポートとなります。

・item_db.txtのATK項でMATKを指定できるように拡張（itemdb.*, statuc.c, doc/db_ref.txt）
	-> 「DEF:MDEF」と同じ書式で「ATK:MATK」と記載することで、MATKを定義できます。

・item_db.txtをR化後データに合わせて修正（db/item_db.txt）

----------------------------------------
//0999 [2013/02/25] by refis

・0998のitem_db更新をフォローアップ（db/item_db.txt）
	-> 不要な改行が含まれていたミスを修正
	-> アクティブモンスター変身関連装備のミスを修正
	-> 英字定義名称を本家に合わせて修正
	-> その他追加修正

----------------------------------------
//0998 [2013/02/23] by refis

・0975以降タワー生成NPCから帰還できなくなっていたミスの修正と会話の補完（npc_memorial_tower.txt）

・スキル関連定義を更新（skill.h）

・スクリプト関数「getequiprefinerycnt」で位置指定を省略できるよう仕様変更（script.c doc/script_ref.txt）

・スクリプト関数「strstr」を実装（script.c doc/script_ref.txt）

・スクリプト命令「active_montransform」を実装
（db/scdata_db.txt doc/script_ref.txt clif.c pc.c script.c status.*）

・item_dbを更新（db/item_db.txt）
	-> アクティブモンスター変身関連のアイテム実装
	-> アイテムドロップ、オートスペル系装備の暫定確率であった一部装備を正しい値に修正

----------------------------------------
//0997 [2013/02/23] by Blaze

・メモリアルダンジョン複製NPCがタイマーイベントを発行するとき、delete_timer errorが出ていた不具合修正（map/npc.c）

----------------------------------------
//0996 [2013/02/23] by Blaze

・メモリアルダンジョン実装（map.*, memorial.*, clif.*, npc.*, pc.c, party.c, script.c, unit.c）
	-> MAP複製処理追加（map.*）
	-> NPC複製・消去処理追加（npc.*）
	-> 指定MAPのNPCイベント実行処理を追加（npc.*）
	-> メモリアルダンジョン情報通知パケット実装（clif.*）
	-> メモリアルダンジョン関連のスクリプト命令・関数実装（script.c, doc/script_ref.txt）

・パーティー情報構造体にメモリアルダンジョンID追加（common/mmo.h, char/int_party.c）

・メモリアルダンジョンDBの仕様変更（memorial.c, db/memorial_db.txt）
	-> 制限時間を分指定から秒指定に変更
	-> 分割MAP数を10から8に削減

・スクリプト命令「mddelete」のパラメータから、名称指定は不要に変更（script.c, doc/script_ref.txt）

・エンドレスタワーNPCの読み込み設定追加（conf/map_auriga.conf）

----------------------------------------
//0995 [2012/02/23] by Blaze

・アイテムウィンドウの個人タブ実装 (map/clif.*)

・アイテム情報に個人タブ有効フラグを追加 (common/mmo.h, char/sql/chardb_sql.c, char/txt/chardb_txt.c)

・TXT:AURIGA_JOURNALを16に引き上げ (common/journal.c.)

・SQL:インベントリテーブルに個人タブ情報を追加（sql-files/main.sql, sql-files/Auriga995_changetable.sql）

----------------------------------------
//0994 [2012/02/21] by refis

・ギルド倉庫デッドロックのチェック部分を修正 (char/int_storage.c)

・キャラクターセーブ応答の不具合を修正 (map/chrif.c)

----------------------------------------
//0993 [2012/02/20] by refis

・オートシャドウスペルのパケットを一部追加 (clif.c)

・状態異常「SC_KYOUGAKU」の値がおかしかったのを修正 (clif.c)
	Thanks Akayumi さん

・ポイントショップがオーバーフローを考慮していなかった点を修正（map/npc.c）
	Thanks おじさま さん

----------------------------------------
//0992 [2012/11/20] by refis

・モンスターの挙動を修正
	-> 戦闘設定に「slave_inherit_mode」を追加（conf/battle_auriga.conf map/battle.* map/mob.c）
	-> ハイディング中の通常攻撃とスキル使用を許可する（map/skill.c map/unit.c）
	-> ハイディング中に攻撃対象が射程外へ出るとターゲット解除させる（map/mob.c）
	-> ワープ時のターゲット解除は視界外消失判定に任せる（map/mob.c）

・特定距離攻撃時の状態異常付与が0983の拡張に対応してなかった不具合を修正（map/battle.c）

----------------------------------------
//0991 [2012/11/16] by refis

・0990でのコミット漏れを修正（map/pc.c）

・魔導ギア搭乗時に「魔導ギアライセンス」スキルが必要なように修正（map/pc.c）

----------------------------------------
//0990 [2012/11/16] by refis

・拡張スーパーノービスで無死亡ボーナスが得られないのを修正（map/status.c）
	Thanks alsion0609 さん

・拡張スーパーノービスで死亡カウンターリセット時エフェクトが出ないのを修正（map/status.c）
	Thanks alsion0609 さん

・カートと魔導ギアを併用した際の処理を修正（map/pc.c）
	Thanks Akayumi さん

----------------------------------------
//0989 [2012/10/14] by refis

・モンスターグループ「スカラバ」種のリストを修正（db/mob_group_db.txt）

・ルーンナイトスキル「ドラゴントレーニング」MaxLv習得時の「槍修練」ダメージを修正（map/battle.c）

・ジェネティックスキル「カート改造」取得時はカート情報を更新させる（map/pc.c）

・ウォーロックスキル「テトラボルテックス」の処理を修正（map/battle.c map/skill.c）
	Thanks pneuma さん

----------------------------------------
//0988 [2012/09/09] by refis

・アイテム使用時、及び装着時の制限レベルに関する不具合の修正（map/pc.c）

・アイテムボーナスコーマが非ボス属性に対して発動しない不具合の修正（map/battle.c）
	Thanks yucco さん

----------------------------------------
//0987 [2012/09/02] by Cocoa

・ウォーマーが敵も対象になっていない不具合の修正

----------------------------------------
//0986 [2012/09/02] by Cocoa

・スキル大纏崩捶使用後に発生するコンボ時間の条件が間違っているので修正（map/battle.c）

----------------------------------------
//0985 [2012/09/01] by Cocoa

・点穴 -球-が物理スキル攻撃で効果を発揮しない不具合の修正（map/battle.c）

----------------------------------------
//0984 [2012/09/01] by Cocoa

・エピクレシス前提条件からハイネスヒールは抜けていた不具合の修正（db/skill_tree.txt）

・ボディペインティングがアイテム消費なしで使用できる不具合の修正（db/skill_require_db.txt）

・魔力の書第1巻が未転生職でも装備できるように修正（db/item_db2.txt）

・ルーンプレートの制限を追記（db/item_db2.txt）

----------------------------------------
//0983 [2012/08/30] by refis

・状態異常関連アイテムボーナスに「恐怖」「発火」「深い睡眠」「氷結」「冷凍」「魅惑」を指定できるよう拡張
 (db/const.txt doc/item_bonus.txt common/mmo.h battle.c map.h pc.c skill.* status.*)
	Thanks Apache さん

・上記に伴うスキル定義を追加 (db/skill_cast_db.txt db/skill_db2.txt db/skill_db.txt)

----------------------------------------
//0982 [2012/08/28] by refis

・ギルド倉庫デッドロックチェックにlast_fdを利用しないよう変更 (char/int_storage.c)

----------------------------------------
//0981 [2012/08/26] by refis

・ログイン時にパーティ加入要請可否設定を出力するよう変更 (clif.*)
	Thanks NP3228 さん

・item_dbのずれの修正とついでに少し更新 (db/item_db.txt)
	Thanks dent さん

・状態異常「SC_BANDING」中のキャラが視界に入ったときにアイコン情報を送信させる (clif.c)

・状態異常「SC_JP_EVENT01」「SC_JP_EVENT02」「SC_JP_EVENT03」「SC_JP_EVENT04」を実装
 (db/const.txt db/item_db.txt db/scdata_db.txt battle.c pc.c status.*)
	Thanks alsion0609 さん

・アイテムボーナス「bonus2 bAddEleWeaponDamageRate」「bonus2 bAddEleMagicDamageRate」追加
 (db/const.txt db/item_db.txt doc/item_bonus.txt battle.c map.h pc.c skill.c status.c)
	Thanks unsyu さん
　bonus2 bAddEleWeaponDamageRate,n,x;
　n属性の物理スキルダメージをx%増加。
　ex)　bonus2 bAddEleWeaponDamageRate,3,10;	// 火属性物理スキルのダメージが10%増加

　bonus2 bAddEleMagicDamageRate,n,x;
　n属性の魔法スキルダメージをx%増加。
　ex)　bonus2 bAddEleMagicDamageRate,1,10;	// 水属性魔法スキルのダメージが10%増加

----------------------------------------
//0980 [2012/08/20] by refis

・itemの名称に半角スペースが混じっているミスを修正 (item_db.txt)

・スクリプト命令「getexp」の表示色を変えられるよう拡張 (doc/script_ref.txt script.c)

・アイテム使用時のレベル制限チェックでエラーメッセージを出力するよう変更 (pc.c)

・状態異常「SC_HAT_EFFECT」を実装 (const.txt item_db.txt scdata_db.txt clif.c status.*)

----------------------------------------
//0979 [2012/08/20] by refis

・別種同一名モンスターの名称変更の欠損分を補完 (npc_monster_abyss.txt)

・itemデータの更新 (item_db.txt item_db2.txt)

・mobデータの更新 (mob_db.txt mob_skill_db.txt)

----------------------------------------
//0978 [2012/08/11] by refis

・0977での関数のスペルミスを修正 (npc_misc_refine.txt)
	Thanks NP3228 さん、うに～く さん

----------------------------------------
//0977 [2012/08/09] by refis

・モンスターの詠唱時間は状態異常の影響を受けないよう修正 (src/map/mob.c)

・「checkitemblank」関数はインベントリの空き数を返すよう仕様変更 (doc/script_ref.txt src/map/script.c)

・精錬石関連NPCを修正 (npc_misc_refine.txt)
	-> 精錬石販売NPCにアイテム所持種チェックを追加
	-> 精錬石交換NPCを複数鉱石交換に対応

・ステータスが正常に表示されない場合がある不具合を修正 (src/map/status.c)
	Thanks テディ さん

・NPCスキル「ドラゴンフィアー」の呪いを混乱に修正 (src/map/skill.c)
	Thanks rapis さん

・別種同一名モンスターの名称を修正
	-> dungeonの修正 (npc_monster_juperos.txt npc_monster_magdun.txt npc_monster_odintem.txt npc_monster_thanatos.txt npc_monster_xmasdun.txt)
	-> fieldの修正 (npc_monster_geffild.txt npc_monster_hufild.txt npc_monster_mjolnir.txt npc_monster_mocfild.txt npc_monster_prtfild.txt npc_monster_yunofild.txt)
		Thanks pneuma さん

----------------------------------------
//0976 [2012/07/16] by refis

・0975のミスを修正 (npc_job_18alchemist.txt npc_job_28gunslinger.txt)

----------------------------------------
//0975 [2012/07/16] by refis

・幻想の花を利用したアルケミスト転職の会話を補完 (npc_job_18alchemist.txt)

・イズルードの街のNPC配置を更新 (npc_job_28gunslinger.txt npc_town_izlude.txt)

・0967の内容を少し修正 (doc/script_ref.txt mapflag_memorial.txt npc_memorial_tower.txt)

・PK設定のとき、マーダラーポイントが0でもボーナスが付与されるミスを修正 (src/map/pc.c)
	Thanks kroe さん

----------------------------------------
//0974 [2012/07/11] by refis

・タナトスタワーNPCの会話を補完 (npc_quest_noghalt.txt)

・ミルク交換NPCの会話を補完 (npc_quest_potion.txt)

・quest_dbを更新 (db/quest_db.txt)

----------------------------------------
//0973 [2012/07/10] by refis

・3次職関連NPCを追加
	-> 3次転職NPCと関連販売NPCを追加 (conf/map_auriga.conf npc_job_thirdclass.txt)
	-> アルケミスト材料商人を修正 (npc_town_aldebaran.txt)
	-> 影工房へのwarpを追加 (npc_warp_town.txt)

・item_dbを更新 (db/item_db.txt)

・2012-06-18aRagexeREのpacket_dbを一部修正 (db/packet_db.txt)
	Thanks Eco さん

・影狼、朧スキル「撒菱」の持続時間の誤りを修正 (db/skill_cast_db.txt)
	Thanks かんなぎ さん

・モンスターにはスキルディレイを適用しないよう修正 (src/map/skill.c)
　※mob_skill_db上のMOB専用スキルクールのみ影響する
	Thanks Apache さん

----------------------------------------
//0972 [2012/06/22] by popori

・0971のコミット漏れコードを追加 (src/map/clif.c)

----------------------------------------
//0971 [2012/06/22] by popori

・PACKETVER「20111102」を追加 (vc_make.bat bcc32_make.bat Makefile src/map/clif.c)
  → 0x43fの上位版0x8ffを追加

・暫定的にPACKETVER「20120328」を追加 (vc_make.bat bcc32_make.bat Makefile *.dsp src/map/clif.c)
  → 0x856、0x857、0x858の上位版0x90f、0x914、0x915を追加
  ※ モンスターのHP表示条件(PC・パーティーメンバ・ホム・傭兵・精霊がダメージを与える/受ける)に関しては未実装
     エンペリウム、BOSS、特定状態異常時以外は全て表示するようになっています

----------------------------------------
//0970 [2012/06/20] by popori

・2012-06-18aRagexeREのpacket_dbを追加 (db/packet_db.txt)

・docを少し修正 (doc/client_packet.txt doc/client_packet.txt)

----------------------------------------
//0969 [2012/06/20] by popori

・wis送信パケットをパケット仕様に合わせて変更 (src/char/inter.c src/map/clif.* src/map/inter.c doc/inter_server_packet.txt doc/client_packet.txt)

・少しリファクタ (src/common/mmo.h src/map/clif.c)

・新仕様のパーティーブッキングはパーティーリーダーでないと登録が出来ないよう修正 (src/map/booking.c)

・パケットの解析結果を記載と修正 (doc/client_packet.txt)

・キャラ作成時のパラメータの型を一部変更 (src/char/char.c src/char/txt/chardb_txt.* src/char/sql/chardb_sql.*)

・2012-06-18aRagexeREまでのパケット長の追記と一部クリーンアップと修正 (db/packet_db.txt)

----------------------------------------
//0968 [2012/06/19] by refis

・討伐クエストNPCのセリフとクエスト開始可能レベルを更新 (npc_quest_hunting.txt)

・エルディカスティスへの帰還、モーラへの帰還の処理を少し修正 (src/map/skill.c)

・マップサーバー間移動要求の不具合を修正 (src/char/char.c)
	Thanks うに～く さん

----------------------------------------
//0967 [2012/06/17] by Blaze

・メモリアルダンジョン実装準備
	-> メモリアルダンジョン用ソース追加（memorial.*, map.c, map.dsp, map_sql.dsp）
	-> スクリプト命令・関数のIFのみ追加（script.c, doc/script_ref.txt）
	　※処理内容は未実装です
		mdcreate命令:メモリアルダンジョンの生成を要求します
		mddelete命令:メモリアルダンジョンの削除を要求します
		mdenter関数:メモリアルダンジョンへの入場を要求し、処理結果を返します
		getmdmapname関数:複製されたMAP名称を返します
		getmdnpcname関数:複製されたNPC名称を返します
	-> メモリアルダンジョン用DB追加（db/memorial_db.txt, doc/db_ref.txt）

・エンドレスタワーNPC実装（script/npc/memorial/npc_memorial_tower.txt）
　※システム実装まではNPC読み込み対象外にしています。

・エンドレスタワー関連マップのマップフラグ追加（script/mapflag/mapflag.txt, script/mapflag/mapflag_memorial.txt, conf/map_auriga.conf）

・エンドレスタワー関連MOBのデータ一部修正（db/mob_db.txt, db/mob_skill_db.txt）

・パケット0x2c2「引数付きmsgstringtable表示」を実装（clif.*）

・announceが表示されない不具合対策で使用パケットを0x40cから0x1c3に暫定変更（clif.c）
	Thanks Akayumi さん

----------------------------------------
//0966 [2012/06/03] by refis

・キャラクターのデータセーブは応答を返すよう変更
	-> ログアウト時のデータ削除は応答を待ってから処理する (doc/serverlink_packet.txt src/char/char.c src/map/chrif.c src/map/clif.c)
	-> キャラクターセレクト、サーバ移動時はデータセーブの応答を待つ (src/map/chrif.c src/map/clif.c src/map/pc.c)

----------------------------------------
//0965 [2012/05/23] by refis

・一部のNPCの動作を修正
	-> 位置、判定文、台詞を修正(npc_job_11hunter.txt npc_job_14crusader.txt npc_misc_guide.txt npc_misc_kafra.txt npc_quest_potion.txt npc_quest_skillget3.txt npc_quest_smilegirl.txt)
	-> テイミング商人の品揃えを更新 (npc_town_geffen.txt npc_town_izlude.txt npc_town_lighthalzen.txt npc_town_morocc.txt npc_town_payon.txt npc_town_prontera.txt npc_town_yuno.txt)

・魔法書販売のクエストNPCを追加 (conf/map_auriga.conf npc_quest_magicbook.txt)

・状態異常「驚愕」にかかった相手が視界に入ったときの不具合を修正 (src/map/clif.c)

・スキル「マスカレード：グルーミー」のペットとホムに対する処理のチェックを強化 (src/map/skill.c)
	Thanks Akayumi さん

----------------------------------------
//0964 [2012/05/20] by refis

・clif_status_load、clif_status_change_idの処理を変更
	-> 既存のclif_status_loadをclif_status_load_idに名称変更し、新たに広範囲用のclif_status_loadを追加
　　　(src/map/atcommand.c src/map/clif.* src/map/pc.c src/map/status.c)
	-> 統一的にclif_status_change_idの第1引数にmap_session_dataを用いるよう変更 (src/map/clif.*)

・状態異常の解除にclif_status_loadを利用するように変更 (src/map/status.c)

・状態異常「深い睡眠」はステータスで耐性を得られないよう修正 (src/map/status.c)

・status_change_pretimerはスキルユニットに対しても呼ばれる可能性があるのでユニットチェックを変更 (src/map/status.c)

----------------------------------------
//0963 [2012/05/19] by Blaze

・精霊システム実装
	-> 攻撃モードによる自動攻撃AI実装（elem.c）
	-> 自動攻撃中にスキル使用するように（unit.c）
	-> 精霊の自動スキル使用確率を戦闘設定に追加（battle.*, conf/battle_auriga.conf）
	-> 精霊の移動処理を改善、ワープ処理を廃止（elem.*）
	-> 精霊ベントスの攻撃射程を修正（db/elem_db.txt）
	-> ソーサラースキル「サモン＊＊＊」の定義を追加（db/skill_db.txt）

・0898以降、ジェネティックスキル「チェンジマテリアル」が失敗する不具合修正（db/packet_db.txt）

・ソーサラースキル「エレメンタルアナライシス」実装（clif.*, skill.*）

----------------------------------------
//0962 [2012/05/17] by refis

・討伐クエストNPCを読み込むとエラーが出るので修正 (npc_quest_hunting.txt)

・カートの処理が上手く動いていないので修正 (src/map/clif.c src/map/pc.c src/map/status.c)

・AI「強敵に非アクティブ」の敵が非反撃になるミスを修正 (src/map/mob.c)
	Thanks rain さん

・討伐データベース登録時に0を除外するように修正 (src/map/quest.c)
	Thanks East さん、pneuma さん

----------------------------------------
//0961 [2012/05/12] by refis

・0960のミスを修正 (src/map/clif.c)

・本家にあわせて髪型最大値を拡張 (src/common/mmo.h)

・ついでにhelpを更新 (conf/help.txt)

----------------------------------------
//0960 [2012/05/12] by refis

・カートのアイテムリストは装着したときのみ送りつけるよう変更 (src/map/pc.c src/map/status.c)

・カートの処理を少し修正 (src/map/clif.c src/map/pc.h)

----------------------------------------
//0959 [2012/05/11] by refis

・PACKETVER「20111025」以降の所持品パケットを追加 (src/map/clif.c)

・ホムンクルスメニューパケットの区切りを一部修正 (db/packet_db.txt)
	Thanks shirasumi さん

・client_packet.txtを少し修正 (doc/client_packet.txt)

----------------------------------------
//0958 [2012/05/05] by Blaze

・0954以降、プレイヤー名に2バイト文字を含むとキャラ作成に失敗していた不具合を修正（char.c, chardb_txt.*, chardb_sql.*）

----------------------------------------
//0957 [2012/05/05] by Blaze

・精霊システム仮実装その２
	-> ソーサラースキル「エレメンタルコントロール」による精霊のモードチェンジ実装（elem.*, skill.c）
　　　※攻撃モードの自動攻撃AIは未実装です。
	-> 精霊がスキルを使用できるように（elem.*, skill.h, clif.c）
　　　※ソーサラースキル「エレメンタルコントロール」Lv2,3、「エレメンタルアクション」使用時に精霊がスキル発動します。
	-> 精霊スキルと状態異常を一部実装（db/skill_db.txt, db/skill_cast_db.txt, db/skill_unit_db.txt, db/scdata_db.txt, skill.*, status.*, battle.c, pc.c）
	-> 待機モード中のみ自然回復するように変更（elem.c）
※精霊の処理が安定化するまで、skill_dbから精霊召喚スキルの定義を無効にしています。

・ソーサラースキル「サモン＊＊＊」の精霊召喚時間が長かったのを修正（skill.c）

・ソーサラースキル「エレメンタルシンパシー」による精霊のMaxSP増加値が多かったのを修正（elem.c）

・ソーサラースキル「エレメンタルシンパシー」の効果を召喚直後にも反映するように修正（elem.c）

・ソーサラーのスキルツリーで「エレメンタルコントロール」のMaxLvを3→4に修正（db/skill_tree.txt）

・NPC終了処理にBL_ELEMに対する処理が漏れていたのを追加（npc.c）

・状態異常の最大登録数「MAX_STATUSCHANGE」を600→650に引き上げ（common/mmo.h）

----------------------------------------
//0956 [2012/05/01] by popori

・0955のパケット修正 (db/packet_db.txt src/map/booking.* src/map/clif.c)

・2012-03-28aRagexeRE用のパケットDB追加 (db/packet_db.txt)

・クライアントの解析結果を追記 (doc/client_packet.txt)

・状態異常「驚愕」にかかった際、画面外からの再表示するとモンスターの姿とならないのを修正 (src/map/clif.c)
　※表示の優先順位を以下にします
　　驚愕 > モンスター変身 > 搭乗システム

・以下のスキルを実装
 (db/skill_cast_db.txt db/skill_db.txt db/skill_unit_db.txt db/scdata_db.txt src/map/battle.c src/map/clif.* src/map/map.h src/map/pc.* src/map/skill.* src/map/status.* src/map/unit.c)
　
　KO_JYUMONJIKIRI
　KO_KAHU_ENTEN
　KO_HYOUHU_HUBUKI
　KO_KAZEHU_SEIRAN
　KO_DOHU_KOUKAI
　KO_KAIHOU
　KO_ZENKAI

----------------------------------------
//0955 [2012/04/29] by popori

・PACKETVER「20120222」の追加 (vc_make.bat Makefile bcc32_make.bat src/map/clif.* src/map/booking.* src/map/map.h db/packet_db.txt doc/client_packet.txt)
　->新仕様のパーティーブッキング対応

・2012-04-10aRagexeRE用のpacket_db.txtの追加 (db/packet_db.txt)

----------------------------------------
//0954 [2012/04/29] by popori

・PACKETVER「20120201」の追加 (vc_make.bat Makefile bcc32_make.bat src/map/clif.c src/map/pc.* src/map/skill.c src/map/status.* db/scdata_db.txt)
　->カートの処理方式を状態異常管理に変更
　->新規追加されたカート9種類に対応

・PACKETCER「20120307」の追加 (src/char/char.c src/char/txt/chardb_txt* src/char/sql/chardb_sql* *.dsp vc_make.bat Makefile bcc32_make.bat)
　->キャラ作成パケット0x970に対応

----------------------------------------
//0953 [2012/04/29] by refis

・0952で接触反応が動作しない不具合の修正とコメントの訂正 (src/map/mob.c)

・TXTモードでデータが一致しない不具合を修正（src/char/txt/chardb_txt.c）

----------------------------------------
//0952 [2012/04/29] by refis

・MOBAI「攻撃中ターゲットチェンジ許可」、「追跡中ターゲットチェンジ許可」を実装 (src/map/mob.c src/map/status.h)
	-> この実装により「アクティブAIの場合、25%確率で攻撃者にターゲットチェンジする」項目を廃止

・MOBAI「ハイパーアクティブ（通称火山AI）」を実装 (doc/db_ref.txt src/map/map.h src/map/mob.* src/map/skill.c src/map/status.h src/map/unit.c)
	-> 1度攻撃を受けるまでは、attackの代わりにangryのスキルが呼び出されます。
	-> 1度攻撃を受けるまでは、chaseの代わりにfollowのスキルが呼び出されます。
	-> 1度攻撃を受けるとその攻撃者をターゲットし、以降は通常アクティブと同じ挙動になります。
		※follow追跡中、最も近い敵をターゲットする効果は、ターゲットの再選定で仮実装しています。

・モンスターのAIを更新 (db/mob_db.txt)

・ハイパーアクティブAI用のスキルを追加更新 (db/mob_skill_db.txt)

・拡張スーパーノービスの「グロリア」スキルツリーの誤りを修正 (db/skill_tree.txt)
	Thanks shirasumi さん、rapis さん

----------------------------------------
//0951 [2012/04/28] by Blaze

・精霊システム仮実装
	-> 精霊の作成、削除、召喚者追従まで実装（map/elem.*, map/battle.c, map/mob.c, map/pc.c, map/skill.c, map/status.c, map/unit.c, map/map.dsp, map/map_sql.dsp）
	-> interサーバの精霊データ送受信処理を実装（map/intif.*, char/inter.c, char/int_elem.*, char/char.dsp, char/char_sql.dsp, doc/inter_server_packet.txt）
	-> charサーバの精霊データ保存処理を実装（char/char.c, char/sql/elemdb_sql.*, char/txt/elemdb_txt.*, char/char.dsp, char/char_sql.dsp）
	-> プレイヤーの精霊情報を保存するように変更（char/sql/chardb_sql.c, char/txt/chardb_txt.c, sql-files/main.sql, Auriga951_changetable.sql）
	-> SQL:新規テーブル「elemental」追加（common/sqldbs.h, sql-files/main.sql, Auriga951_changetable.sql）
	-> TXT:JOURNAL_IDENTIFIERを14->15に引き上げ (common/journal.c)
	-> 精霊保存データに"mode"と"limit"を追加 (common/mmo.h)
	-> 精霊データ定義にAIタイマー追加、不要な定義を削除（map/map.h）
	-> 精霊の初期化、破棄、block_list取得処理を追加（map/map.c）
	-> 戦闘設定に「elem_max_aspd」を追加（map/battle.*, conf/battle_auriga.conf）
※精霊の処理が安定化するまで、skill_dbからソーサラーの精霊スキル定義を無効にしています。

・TXT:Auriga-0888およびAuriga-0902にて、旧形式のデータとindexがずれているために一部データが破壊される不具合を修正（char/txt/chardb_txt.c）

----------------------------------------
//0950 [2012/04/28] by popori

・2012-4-24aRagexeREの解析結果を記載 (doc/client_packet.txt)

・2012-4-24aRagexeREまでのパケット長を記載 (db/packet_db.txt)
　※パケット長の追記を行っただけなので、2012-4-24aRagexeREまでのクライアントが使用出来るわけではありません

----------------------------------------
//0949 [2012/04/26] by refis

・PACKETVERによって、ログイン時に頭装備が装備ウィンドウ上に表示されないのを修正 (src/map/clif.c)

・買取露店関連の初期化処理の誤りを修正 (src/map/buyingstore.c)

・client_packet.txtの更新 (doc/client_packet.txt)

----------------------------------------
//0948 [2012/04/25] by refis

・0947がコンパイルエラーをなるミスを修正 (src/map/clif.c)

----------------------------------------
//0947 [2012/04/25] by refis

・搭乗システム、モンスター変身の無駄なパケットを抑制させる (src/map/clif.*)

・武器修理、装備閲覧のリストが正常に取得できない現象を修正 (src/map/clif.c)
	Thanks unsyu さん

・傭兵スキル「バーサーク」のミスを修正 (db/skill_cast_db.txt)

----------------------------------------
//0946 [2012/04/24] by Blaze

・ソーサラーの精霊スキル実装準備
	-> mmo.hに精霊の情報定義を追加（common/mmo.h）
	-> block_typeにBL_ELEMを新規追加（map.h）
	-> 精霊の基本情報構造体を新規追加（map.h）
	-> 精霊の表示系パケット（0x78,0x7b,0x7c,0x28,0x95）を新規追加（clif.*）
	-> 精霊のステータス更新パケット（0x81d,0x81e）を新規追加（clif.*）
	-> 精霊のスキル定義追加（skill.h, db/skill_db.txt, db/skill_db2.txt db/skill_require_db.txt）
	-> 精霊の基本情報DBとスキルDBを新規追加（db/elem_db.txt, db/elem_skill_tree.txt）


----------------------------------------
//0945 [2012/04/24] by Blaze

・傭兵データ構造の見直し（common/mmo.h, map.h, merc.*, clif.c, status.c, skill.c）
	-> BaseLvや各種ステータス、スキル情報などはsaveデータに保存しない様に変更。

・傭兵をSQLモードに対応 (char/sql/mercdb_sql.c, sql-files/main.sql, sql-files/Auriga945_changetable.sql)
	-> 既存のプレイヤーが持つ傭兵雇用情報は「mercenary」から「mercenary_employ」にテーブル名を変更
	-> 傭兵自身のデータを「mercenary」テーブルに保存するように。

・モンスター傭兵実装（common/mmo.h, merc.*, db/merc_db.txt, merc_skill_tree.txt）
	-> 傭兵IDを定められたID（6017～6046）しか登録できなかったのを任意のIDで登録できるように変更。

・傭兵DBの構造を変更（merc.*, db/merc_db.txt, db/addon/merc_db_add.txt, doc/db_ref.txt）
	-> 傭兵のクラスIDを任意に定義できる様にした為、ViewClassを廃止
	-> 傭兵の種類は内部で処理させるようにした為、ClassTypeを廃止

・傭兵のキルカウントボーナス実装（merc.c, status.*, db/scdata_db.txt）

・傭兵専用スキル「キリエエレイソン」「ブレッシング」「速度増加」を追加（skill.*, db/skill_db.txt, db/skill_db2.txt, db/skill_cast_db.txt, db/skill_require_db.txt）

・傭兵の自然回復が短かったのを修正（merc.h）
	-> HPの自然回復：2000ms → 8000ms、SPの自然回復：4000ms → 6000ms

・傭兵に処理させるスクリプトを追加（script.c, doc/script_ref.txt）
	-> mercheal命令：連れている傭兵のHP/SPを回復させます。
	-> mercsc_start命令：連れている傭兵を状態変化させます。

・傭兵関係のアイテム実装（db/item_db.txt）

----------------------------------------
//0944 [2012/04/21] by refis

・ギルド追放メンバリストのミスを修正 (src/map/clif.c)
	Thanks ryokucha さん

・clif_bodyrelocation()のnullチェック忘れを修正 (src/map/clif.c)

・NPCスキル「不死属性付与」は属性レベル2以上にならないよう修正 (src/map/skill.c)
	Thanks Akayumi さん

・3次職のBaseLv90～98迄のHP・SPデータを追加 (db/job_hp_db.txt db/job_sp_db.txt)

----------------------------------------
//0943 [2012/04/20] by refis

・モンスター変身でサーバーがクラッシュしてしまうミスを修正 (src/map/clif.c)

・モンクスキル「残影」のパケットをスイッチさせるように修正 (src/map/clif.* src/map/skill.c)

----------------------------------------
//0942 [2012/04/20] by refis

・搭乗システム、モンスター変身中キャラが画面に入ったとき、正常に表示されなかったのを修正 (src/map/clif.c src/map/status.c)
	-> 相互の干渉関係が不明なため、搭乗システムが優先される暫定処置です
		Thanks うに～く さん、ryokucha さん

・アサシンスキル「クローキング」で壁沿い移動時の無効な判定を修正 (src/map/status.c)
	Thanks Akayumi さん

・ハイプリーストスキル「バジリカ」の解除時はユニット判定しないよう修正 (src/map/skill.c)
	Thanks Akayumi さん

・ギルド追放関連のパケットを更新 (src/map/clif.c)
	Thanks Akayumi さん

・服色変更パケットは服色変更時のみ発行されるため、clif_send_clothcolor()は使用しないよう修正
 (src/map/atcommand.c src/map/clif.* src/map/pc.c src/map/script.c src/map/status.c)

----------------------------------------
//0941 [2012/04/19] by refis

・ジェネティックスキル「カート改造」、「剣修練」、「スリングアイテム」の最大Lvを修正 (db/skill_db.txt)
	Thanks rain さん、rapis さん

・アイテムボーナス「bMatkRate」が二重計算されていたのを修正 (src/map/battle.c)
	Thanks unsyu さん

----------------------------------------
//0940 [2012/04/17] by refis

・0939の内容が不足している部分を修正 (db/item_db.txt doc/script_ref.txt)
	-> item_db.txtのDEF項で「:」を使ってMDEFも指定できるよう拡張
		Thanks rapis さん

・MDEFのない装備品を装着時の不具合を修正 (src/map/itemdb.c)
	Thanks unsyu さん

----------------------------------------
//0939 [2012/04/16] by refis

・item_dbにMDEFを指定できるように拡張 (db/item_db.txt src/map/itemdb.* src/map/status.c)

・「シールドスペル」でMDEFの代わりに暫定でDEFを利用していた箇所を修正 (src/map/battle.c)

----------------------------------------
//0938 [2012/04/16] by refis

・「checkitemblank」関数を追加 (doc/script_ref.txt src/map/script.c)

・インベントリの不要なループを抑制させるよう処理を修正 (src/map/chrif.c src/map/clif.c src/map/map.h src/map/pc.c src/map/skill.c)

----------------------------------------
//0937 [2012/04/16] by Blaze

・スクリプト命令「progressbar」を実装（script.c, clif.*, pc.c, unit.c, map.h, db/packet_db.txt, doc/script_ref.txt）
　※移動による中断状態のキャンセルは未実装です

・アッシュ・バキュームNPC実装（npc_quest_ashvacuum.txt）
	-> 異世界クエスト実装
	-> 駐屯地の人々クエスト実装
	-> 会議のおともクエスト実装
	-> 生態研究クエスト実装
	-> 飼育場のお手伝いクエスト実装
	-> 小さな妖精クエスト実装
	-> 木の巨人クエスト実装
	-> 猫の手サービスクエスト実装
		Thanks to Xia
　※魔王モロク追跡クエストと三ヶ国への報告書クエストは未実装

・アッシュ・バキューム関連マップのwarp追加（npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt）

・アッシュ・バキューム関連マップのmob追加（npc_monster_manfild.txt, npc_monster_splfild.txt）

・アッシュ・バキューム関連マップのmapflag追加（mapflag.txt）

・map_auriga.conf更新（map_auriga.conf）

・0936の「callshop」の説明を微修正（doc/script_ref.txt）

----------------------------------------
//0936 [2012/04/15] by refis

・「callshop」関数を追加 (doc/script_ref.txt src/map/script.c)

・デワタの一部NPCにチャットバルーンを追加 (script/npc/town/npc_town_dewata.txt)

----------------------------------------
//0935 [2012/04/15] by Blaze

・「@go」コマンドの行き先を外部ファイルで設定できるように変更（atcommand.*, map.c）

・「@go」コマンドの行き先を設定するDBを追加（db/atcommand_go_db.txt, doc/db_ref.txt）

・戦闘設定「atcommand_go_significant_values」を廃止 (battle.*, conf/battle_auriga.conf)

----------------------------------------
//0934 [2012/04/14] by refis

・討伐データベースのソート処理を修正 (src/map/quest.c)
	Thanks 716 さん

・「ルーン製造」、「新毒製造」の材料リストを修正 (db/produce_db.txt)
	Thanks shisuka さん

----------------------------------------
//0933 [2012/04/07] by refis

・レンジャースキル「ウォーグダッシュ」使用時に移動不可セルを判定するよう修正 (src/map/skill.c)
	Thanks Akayumi さん

・ハイプリーストスキル「バジリカ」のユニット処理を修正 (db/skill_unit_db.txt src/map/skill.c)
	Thanks Akayumi さん、rapis さん

・クエストスキル「ベナムナイフ」習得NPCの台詞を修正 (script/npc/quest/npc_quest_skillget2.txt)

----------------------------------------
//0932 [2012/04/05] by refis

・MODEのマジックナンバーをenumで回避する
 (src/map/atcommand.c src/map/battle.c src/map/mob.c src/map/npc.c src/map/pc.c src/map/pet.c src/map/script.c src/map/skill.c src/map/status.* src/map/unit.c)

・接触反応AI、低レベルターゲッティングAIを実装 (doc/db_ref.txt src/map/mob.c)

・mob_db.txtを更新 (db/mob_db.txt)

----------------------------------------
//0931 [2012/04/05] by refis

・討伐データベースの初期化忘れを修正 (src/map/quest.c)

・MAX_PACKET_DBの拡張 (src/map/clif.c)

・grfの初期位置を本家にあわせて変更 (conf/grf-files.txt)

・@reproduce、@reproduce2を追加 (conf/atcommand_auriga.conf conf/help.txt src/map/atcommand.*)

・リプロデュースをスクリプトから操作できるよう定数を追加 (db/const.txt src/map/map.h src/map/pc.c)

----------------------------------------
//0930 [2012/04/05] by refis

・レンジャースキル「エイムドボルト」の矢消費量を修正 (db/skill_require_db2.txt src/map/battle.c src/map/skill.c)
	Thanks unsyu さん

・アイテムボーナス「bonus bMdef2」でMdefが上昇する不具合を修正 (src/map/pc.c)

・クエストシステムの討伐カウントがパーティーメンバーにも反映されるよう修正 (src/map/mob.c src/map/quest.*)

・敵が討伐対象かどうか事前に調べるよう変更 (src/map/mob.c src/map/quest.*)

----------------------------------------
//0929 [2012/04/01] by refis

・スーパーノービスの台詞コマンドが使えなくなっていたのを修正 (src/map/clif.c)
	Thanks unsyu さん

・シャドウチェイサースキル「オートシャドウスペル」の持続時間設定の誤りを修正 (src/map/skill.c)
	Thanks rain さん、unsyu さん

・packet_db.txtの更新 (db/packet_db.txt)

・client_packet.txtの更新 (doc/client_packet.txt)

----------------------------------------
//0928 [2012/03/28] by refis

・アイテムボーナス「bonus2 bFixCastrate」の判定式を修正 (src/map/pc.c)
	Thanks Akayumi さん

・ウォーロックスキル「ソウルエクスパンション」のダメージ計算式を修正 (src/map/battle.c)
	Thanks かんなぎ さん

・レンジャースキル「エイムドボルト」の拘束時のダメージ計算式を修正 (src/map/battle.c)
	Thanks velvet0001 さん

・命令文「npcskillsupport」で発動元と対象を指定できるように変更 (doc/script_ref.txt src/map/script.c)

----------------------------------------
//0927 [2012/03/14] by refis

・0926のミスを修正 (db/scdata.txt src/map/pc.c)

----------------------------------------
//0926 [2012/03/14] by refis

・騎乗システムを一部修正 (db/scdata.txt src/map/clif.c src/map/skill.c src/map/status.c)

・身代わりの護符を実装 (db/item.txt src/map/pc.c)

・Job教範の効果を実装 (db/const.txt db/scdata.txt src/map/pc.c src/map/status.*)

・戦闘教範の仕様を変更 (src/map/pc.c)

・関連アイテムのデータを修正 (db/item.txt)

・amotionの設定がずれているミスを修正 (db/job_db1.txt)
	Thanks kuroneko_daten さん、かんなぎ さん

----------------------------------------
//0925 [2012/03/04] by refis

・スキル「買取露店開設」が習得できなかった点を修正 (script/npc/quest/npc_quest_skillget3.txt)
	Thanks Akayumi さん

・ジェネティックスキル「カートブースト」の追加ダメージ計算の位置を修正 (script/npc/quest/npc_quest_skillget3.txt)

・スキル「点穴 -反-」、「ストライキング」の武器ATK上昇計算の位置を修正 (src/map/battle.c src/map/status.c)
 ※本来はサイズ補正前に計算

・スキル「フォースオブバンガード」、「点穴 -活-」、「エコーの歌」、「恋人たちの為のシンフォニー」のDEF/MDEF上昇計算の位置を修正
 (src/map/battle.c src/map/status.c)

・スキル「シールドプレス」、「大纏崩捶」、「號砲」、「羅刹破凰撃」を最終無属性に修正 (src/map/battle.c)

----------------------------------------
//0924 [2012/02/26] by refis

・mob_group_db拡張に伴うボーナス最大値の修正 (src/map/map.h)

・傭兵召喚時のエラーを修正 (src/map/merc.c)

・status_get_aspdは存在していないので消去 (src/map/status.h)

----------------------------------------
//0923 [2012/02/22] by refis

・変動詠唱と固定詠唱の計算式を修正 (src/map/skill.c)

・アイテムボーナス「bonus2 bFixCastrate」のリファクタリング (src/map/pc.c src/map/skill.c src/map/status.c)

・スキル「フロストミスティ」、「ジャックフロスト」、「コメット」に斜線チェックを追加 (src/map/skill.c)

・スキル「フロストミスティ」の状態異常付与はダメージと斜線チェックなしで判定させる (src/map/skill.c)

・アイテムデータの更新 (db/item_db.txt)
	Thanks lowl さん、rapis さん

・モンスターデータの更新 (db/mob_db.txt db/mob_group_db.txt db/mob_skill_db.txt)
　※一部R化後のデータは暫定です

----------------------------------------
//0922 [2012/02/20] by refis

・CLASS定義の補完と修正 (db/const.txt src/common/mmo.h)

・スキル「スーパーノービスの魂」の判定が誤っていた個所を修正 (src/map/skill.c)
	Thanks かんなぎ さん

----------------------------------------
//0921 [2012/02/13] by refis

・買取担当組合員をプロンテラ道具屋に追加とミスの修正 (script/npc/quest/npc_quest_skillget3.txt)

・スキル「イグニッションブレイク」、「キャノンスピア」のBaseLv補正を修正 (src/map/battle.c)
	Thanks velvet0001 さん

・スキル「アックスブーメラン」のダメージ計算式を修正 (src/map/battle.c)
	Thanks かんなぎ さん、ARIA さん

・MAP移動時にスキルメニューフラグを削除するよう仮修正 (src/map/unit.c)
	Thanks unsyu さん、かんなぎ さん

----------------------------------------
//0920 [2012/02/09] by refis

・スキル「オーディンの力」の効果時間が消えているミスを修正 (db/skill_cast_db.txt)

・買取担当組合員、闇商人の入力値判定のミスを修正 (script/npc/quest/npc_quest_skillget3.txt)

----------------------------------------
//0919 [2012/02/09] by refis

・0918のミスを修正 (script/npc/quest/npc_quest_skillget3.txt)

----------------------------------------
//0918 [2012/02/09] by refis

・買取露店開設関連を本家仕様に修正
 (db/item_db.txt db/item_db2.txt db/skill_db.txt db/skill_require_db.txt db/skill_tree.txt src/map/buyingstore.c src/map/clif.c src/map/skill.c)

・買取露店関連NPCを追加 (conf/map_auriga.conf script/npc/quest/npc_quest_skillget3.txt)

・ついでにMAP定義を追加 (conf/map_auriga.conf)

・スキル「ホーリーナイト」、「エルディカスティスへの帰還」、「モーラへの帰還」実装
 (db/skill_db.txt db/skill_db2.txt db/skill_cast_db.txt db/skill_require_db.txt src/map/skill.*)

・ALL_DREAM_SUMMERNIGHTの定義が異なっているのを修正 (src/map/skill.h)

----------------------------------------
//0917 [2012/02/06] by refis

・買取露店でアイテム販売時にZENYチェックを追加 (src/map/buyingstore.c)
	Thanks Akayumi さん

・メールシステムの不具合を修正 (src/map/mail.c)
	Thanks dragontail789 さん

・0916を若干修正 (src/map/map.h)

----------------------------------------
//0916 [2012/02/06] by refis

・スキル「オーディンの力」実装
 (db/scdata_db.txt db/skill_db.txt db/skill_db2.txt db/skill_cast_db.txt db/skill_require_db.txt src/common/mmo.h src/map/skill.* src/map/status.*)

・アイテムボーナス「bonus2 bAddSkillCastTime」「bonus2 bFixCastrate」「bonus2 bAddSkillSubHealRate」「bonus2 bAddSkillCoolDown」追加
 (db/const.txt doc/item_bonus.txt src/map/map.h src/map/skill.c src/map/pc.c src/map/status.c)
　bonus2 bAddSkillCastTime,n,x;
　指定スキルnの詠唱時間をxミリ秒増加させます。
　ex)　bonus2 bAddSkillCastTime,19,1000;	// スキルファイアーボルトの詠唱時間を1000ms(1秒)増加

　bonus2 bFixCastrate,n,x;
　固定詠唱時間をn%増加させます(xが0の場合、値の低い物が適用。xが0以外の場合、nは+される)
　ex)　bonus2 bFixCastrate,-20,0;	// これ以上値の低い効果を受けていない場合固定詠唱時間を20%減少
　ex)　bonus2 bFixCastrate,-5,1;	// 固定詠唱時間を5%減少(上記ボーナスと共に設定すると25%減少)

　bonus2 bAddSkillSubHealRate,n,x;
　指定スキルnを受けたときの回復量をx%増加させます。
　ex)　bonus2 bAddSkillSubHealRate,28,10;	// スキルヒールを受けたときの回復量を10%増加

　bonus2 bAddSkillCoolDown,n,x;
　指定スキルnのクールタイムをxミリ秒増加させます(3次職スキル以外は無視されます)
　ex)　bonus2 bAddSkillCoolDown,2051,-3000;	// スキルハイネスヒールのクールタイムを3000ms(3秒)減少

・mob_group_dbを更新 (db/mob_group_db.txt)

・NPC商店はNOTOCフラグとNOTDCフラグを確認してDUPE警告を表示するよう変更してみる (src/map/npc.c)

・ドキュメントファイルの細かい修正 (doc/db_ref.txt doc/item_bonus.txt)
	Thanks Akayumi さん、hyper_001 さん

----------------------------------------
//0915 [2012/02/05] by refis

・存在しないアイテムボーナスの説明の削除とその他細かい修正 (doc/item_bonus.txt)
	Thanks ARIA さん

・エンペリウムに状態異常を適用しないよう修正 (src/map/status.c)
	Thanks raisaba10 さん、pneuma さん

・影狼、朧スキル「十六夜」の詠唱時間計算を修正 (src/map/skill.c)

----------------------------------------
//0914 [2012/02/05] by refis

・ロイヤルガードスキル「トランプル」がハンターのトラップに効果が出ない不具合を修正 (db/skill_db.txt)
	Thanks Akayumi さん

・スキル倍率加算効果はスキル倍率計算後に使用しないよう修正 (src/map/battle.c)
	Thanks Akayumi さん

・アークビショップスキル「ハイネスヒール」はアコライトスキル「ヒール」Lv10を基準に算出させる (src/map/skill.c)
	Thanks めろでぃ さん

・スナイパースキル「ウインドウォーク」のFlee増加量を修正 (src/map/status.c)
	Thanks めろでぃ さん

----------------------------------------
//0913 [2012/02/03] by refis

・影狼、朧スキル「明鏡止水」のSP回復不具合を修正 (src/map/status.c)
	Thanks かんなぎ さん

・拡張スーパーノービス、影狼、朧の秒間最大攻撃回数が固定になる不具合を修正 (src/map/status.c)
	Thanks barusu2 さん、rapis さん

・二刀流時の右手・左手修練のダメージ計算式を修正 (src/map/battle.c)
	Thanks dragontail789 さん

・add_damage_class_count、add_damage_class_count_、add_magic_damage_class_countはintである必要がないのでshortに変更
 (src/map/map.h)

----------------------------------------
//0912 [2012/01/22] by popori

・スキル「明鏡止水」「幻術 - 驚愕」「幻術 - 呪殺」「幻術 - 幻惑」の実装
 (db/scdata_db.txt db/skill_db.txt db/skill_cast_db.txt src/map/battle.c src/map/clif.c src/map/skill.c src/map/status.* src/map/unit.c)

・スキル「フォースオブバンガード」の状態異常タイマーがおかしいのを修正 (src/map/status.c)
　rapisさんに感謝

・気付いた範囲でpacket_db.txtのcleanup (db/packet_db.txt)

----------------------------------------
//0911 [2012/01/22] by popori

・コスチュームシステムを本家仕様に修正 (src/map/clif.c src/map/pc.c)

・アイテムフラグを少し修正 (db/item_db2.txt)

・アルデバランのカプラ職員からスーパーノービスと拡張スーパーノービスがカートをレンタル出来なくなっていたのを修正
 (script/npc/job/npc_job_23supernovice.txt)
　716さんに感謝

----------------------------------------
//0910 [2012/01/22] by popori

・0886のバグ修正とマジックナンバー削減 (src/map/buyingstore.c src/map/clif.c src/map/pc.* src/map/vending.c)
　うに～くさん、Akayumiさんに感謝

----------------------------------------
//0909 [2012/01/22] by popori

・メールの最大保存数を超えるメールを受信しようとした場合は、一番古いメールを削除して受信するように変更 (src/char/int_mail.c)

・zeny、添付アイテムが存在するメールも削除可能なよう変更 (src/char/sql/maildb_sql.c src/char/txt/maildb_txt.c)

・メールの添付データの取得に失敗した時でも添付情報を削除していたので、添付データのロストが起こりうる可能性があったのを修正
 (src/char/inter.c src/char/int_main.c src/map/intif.* src/map/mail.* doc/inter_server_packet.txt)

・mail_dataテーブルを少し変更 (sql-files/main.sql sql-files/Auriga909_changetable.sql src/char/sql/maildb_sql.c)

----------------------------------------
//0908 [2012/01/12] by popori

・フォントアイテムの実装
 (db/item_db.txt db/item_db2.txt doc/script_ref.txt sql-files/Auriga908_changetable.sql sql-files/main.sql
　src/char/sql/chardb_sql.c src/char/txt/chardb_txt.c src/common/mmo.h src/map/clif.* src/map/pc.c src/map/script.c)

・clif.cの修正 (src/map/clif.c)
　かんなぎさんに感謝

----------------------------------------
//0907 [2012/01/12] by popori

・item_db2.txtのフラグ値修正 (db/item_db.txt)

・SC_ALL_RIDING中、攻撃とスキル使用は出来ないように変更 (src/map/clif.c)

・スキル「KO_BAKURETSU」の計算式を変更 (src/map/battle.c)

----------------------------------------
//0906 [2012/01/12] by popori

・矢の判定が誤っていた個所を修正 (src/map/battle.c)
　kuroneko_datenさんに感謝

・搭乗システムの実装
 (db/const.txt db/item_db.txt db/item_db2.txt db/scdata_db.txt doc/db_ref.txt src/map/itemdb.* src/map/pc.c src/map/status.*)

・item_db2.txtにNonconsumeフラグの追加
　詳細はdb_ref.txt参照のこと

----------------------------------------
//0905 [2012/01/11] by popori

・コスチュームシステムでグラフィクが反映されない場合のがあるのを修正 (src/map/clif.c src/map/pc.c)

----------------------------------------
//0904 [2012/01/11] by popori

・コスチューム装備のカード読み込みの修正 (src/map/status.c)

・battle_auriga.confのclif_fix_levelに拡張スーパーノービス、影狼、朧を対応 (src/map/clif.c)

・コスチューム装備の装備中viewidのセーブデータは保存しないよう変更する
 (src/char/txt/chardb_txt.c src/char/sql/chardb_sql/.c common/mmo.h src/map/pc.c sql-files/Auriga904_changetable.sql sql-files/main.sql)

・UnknownPacketダンプのログ抑制のためにpacket_db.txtの更新 (db/packet_db.txt)

・ついでにclient_packet.txtの更新 (doc/client_packet.txt)

----------------------------------------
//0903 [2012/01/10] by popori

・TXTのキャラデータ読み込み修正 (src/char/chardb_txt.c)
　lamunesさんに感謝

・SC_AKAITSUKIの判定式を修正 (src/map/skill.c)

・client_packet,txtの更新 (doc/client_packet.txt)

----------------------------------------
//0902 [2012/01/09] by popori

・コスチュームシステムの実装
 (db/item_db.txt sql-files/Auriga902_changetable.sql sql-files/main.sql src/char/sql/chardb_sql.c src/char/txt/chardb_txt.c
　src/common/mmo.h src/map/battle.c src/map/clif.c src/map/itemdb.* src/map/map.h src/map/pc.* src/map/script.c src/map/status.c
　doc/script_ref.txt doc/db_ref.txt)

・分かりづらいequip_indexのマジックナンバーをenumを使って回避する
 (src/map/battle.c src/map/clif.c src/map/itemdb.* src/map/map.h src/map/pc.* src/map/script.c src/map/status.c)

・battle_auriga.confの設定項目「disable_transform_when_gvg」が正常に動作しないのを修正 (src/map/pc.c)
　disable_transform_when_gvgを無効にしたい場合、item_db2.txtのzoneのフラグも修正すること

・battle_auriga.confに設定項目「disable_costume_when_gvg」を追加 (conf/battle_auriga.conf src/map/battle.* src/map/pc.c)
　GvGでコスチュームアイテムを無効にするか
　デフォルト有効
　disable_costume_when_gvgを無効にしたい場合、item_db2.txtのzoneのフラグも修正すること

----------------------------------------
//0901 [2012/01/08] by popori

・2012-01-04bRagexeの解析結果と、更新を行っていなかった解析済みのパケットをclient_packetへ追記 (doc/client_packet.txt)

・スキル「KG_KYOMU」に魔法反射無効も付けてみる (src/map/battle.c)

・battle_auriga.confに以下の設定項目を追加 (conf/battle_auriga.conf src/map/atcommand.c src/map/battle.* src/map/pc.c src/map/status.c)
　// 拡張スーパーノービスのステータス限界
　esnv_status_max: 120

　// 養子拡張スーパーノービスのステータス限界
　esnv_baby_status_max: 108

　// 拡張スーパーノービスの秒間最大攻撃回数を設定。
　// 単位はms(デフォルトは140で秒間7.1回の攻撃回数)
　esnv_max_aspd: 140

　// 影狼、朧のステータス限界
　ko_status_max: 120

　// 影狼、朧の秒間最大攻撃回数を設定。
　// 単位はms(デフォルトは140で秒間7.1回の攻撃回数)
　ko_max_aspd: 140

----------------------------------------
//0900 [2012/01/08] by popori

・スキル「KG_KYOMU」の反射無効の条件式を間違えていたので修正 (src/map/battle.c)

・vc_mae.batのMySQLのパスを5.5基準に書き換え (vc_make.bat)

----------------------------------------
//0899 [2012/01/08] by popori

・影狼、朧の実装
 (src/common/mmo.h src/char/char.c src/map/battle.c src/map/pc.* src/map/script.c src/map/skill.* src/map/status.*
　src/map/unit.c db/const.txt db/job_db*.txt script/sample/npc_custom_jobchange.txt db/skill_db.txt db/skill_db2.txt
　db/skill_cast_db.txt db/skill_require_db.txt db/skill_require_db2.txt db/skill_tree.txt db/scdata_db.txt db/item_arrowtype.txt
　db/item_db.txt db/skill_unit_db.txt)

　※JobボーナスとHP,SPは現行Aurigaの忍者と同一で暫定
　　基本ASPDはリニューアル後の忍者と同一で暫定

・packet_db.txtの修正 (db/packet_db.txt)
　うに～くさんに感謝

・mob_avail.txtの読み込み修正 (db/mob_avail.txt)
　うに～くさんに感謝

----------------------------------------
//0898 [2012/01/04] by popori

・char.cのPACKETVERの不整合を修正 (src/char/char.c)
　soldoutさんに感謝

・SQLモード時、キャラデータロードに不正が生じるのを修正 (src/char/sql/chardb_sql.c)
　soldoutさんに感謝

・packet_db.txtの更新 (db/packet_db.txt)

----------------------------------------
//0897 [2011/12/31] by popori

・0896変更点の「dropableフラグが真の時はNPCで売却を不可とするよう変更」の条件式が間違えていたので修正 (src/map/npc.c)
　soldoutさんに感謝

・モンスター変身アイテムのフラグ追記 (db/item_db2.txt)

----------------------------------------
//0896 [2011/12/29] by popori

・キャラ作成パラメータバインド時のタイプを修正 (src/char/sql/chardb_sql.c)
　soldoutさん、yooske61さんに感謝

・2011-12-28aRagexeREまでのパケット長追記 (db/packet_db.txt)

・dropableフラグが真の時はNPCで売却を不可とするよう変更 (src/map/npc.c)

・モンスター変身アイテムと2Dレイヤー装備に関するフラグを追加 (db/item_db2.txt)

・httpdをデフォルトで無効にする (Makefile bcc32_make.bat vc_make.bat src/login/login_httpd.c)

・GCC4以上の時は-fno-strict-aliasingを指定するように変更 (Makefile)

----------------------------------------
//0895 [2011/12/29] by popori

・モンスター変身アイテムの実装 (src/map/status.* src/map/battle.c db/scdata_db.txt db/item_db.txt db/const.txt)
　※ゴーレムは被弾時のインデュア発動確率が分からなかったので効果未実装

・battle_auriga.cofに「disable_transform_when_gvg」を追加 (conf/battle_auriga.conf src/map/battle.* src/map/pc.c)
　デフォルトはyes

・2Dレイヤー装備アイテムを追加 (db/item_db.txt)

----------------------------------------
//0894 [2011/12/29] by popori

・0x8b9の送信タイミングを0x6b前にするよう変更と追加 (src/char/char.c)

・PACKETVER20100615の追加 (vc_make.bat bcc32_make.bat Makefile src/login/login.c)

・UnknownPacketが出力されないようにとりあえず定義だけ追加 (db/packet_db.txt src/map/clif.c)

----------------------------------------
//0893 [2011/12/29] by popori

・gcc環境下でのwarning修正 (src/map/skill.c)

・SC_DEEP_SLEEPをpretimerで発動させるように変更 (src/map/skill.c)

・dspファイルの更新 (src/*/*.dsp)

・packet_db.txtの修正と追加 (db/packet_db.txt)

----------------------------------------
//0892 [2011/12/29] by popori

・拡張ノービスの実装
 (src/common/mmo.h src/char/char.c src/map/clif.c src/map/pc.* src/map/script.c src/map/skill.c src/map/status.c
　db/const.txt db/job_db1.txt db/job_db2.txt db/job2_2.txt db/job_hp_db.txt db/job_sp_db.txt db/skill_tree.txt
　script/npc/job/npc_job_23supernovice.txt script/warp/npc_warp_dun.txt script/sample/npc_custom_jobchange.txt)

----------------------------------------
//0891 [2011/12/29] by popori

・PACKETVER20100803からキャッシュショップの複数個購入に対応 (db/packet_db.txt src/map/clif.c src/map/npc.*)

・MAX_PACKET_DBを0x950まで拡張 (src/map/clif.c)

----------------------------------------
//0890 [2011/12/29] by popori

・PACKETVER20110111より0x2d7の上位パケット0x859に対応 (src/map/clif.c)

・LOC_***の定義更新 (src/map/itemdb.h)

・packet_db.txtの更新 (db/packet_db.txt)

・PACKETVER20110719の追加 (vc_make.bat bcc32_make.bat Makefile)

・0x1c9の上位パケット0x8c7の実装 (src/map/clif.c)

・0x2e1の上位パケット0x8c8の実装 (src/map/battle.c src/map/clif.* src/map/skill.c src/map/status.c src/map/unit.*)

----------------------------------------
//0889 [2011/12/29] by popori

・PACKETVER20110309の追加 (char.c)

・PACKETVER20110928の追加 (char.c)

・PACKETVER20111025の追加 (char.c vc_make.bat bcc32_make.bat Makefile src/*/*.dsp)

----------------------------------------
//0888 [2011/12/29] by popori

・ストレージエンジンをMyISAMからInnoDBに変更する (sql-files/main.sql sql-files/Auriga888_changetable.sql)
　そもそもMyISAMはAurigaに不向きかと

・肩装備、パーティー勧誘拒否フラグ、装備公開をセーブデータとして保存するように
 (sql-files/main.sql sql-files/Auriga888_changetable.sql src/common/mmo.h src/char/txt/chardb_txt.c src/char/sql/chardb_sql.c
　src/map/clif.c src/map/map.h src/map/party.c)

・0x9eの上位パケット0x84b用にPACKETVER20101020を追加 (vc_make.bat bcc32_make.bat Makefile src/map/clif.c)

・packet_dbに無駄な重複があったのでcleanup (db/packet_db.txt)

・2010-11-24aRagexeRE以降のpacket長追加 (db/packet_db.txt)

・PACKETVER20110111を追加 (vc_make.bat bcc32_make.bat Makefile src/*/*.dsp)

・PACKETVER20110111から肩装備の表示に対応させるため上位パケットを実装 (src/char/char.c src/map/map.h src/map/clif.c src/map/pc.c)

・上記の変更に伴いmob_avail.txtに肩装備を表示出来るように拡張 (db/mob_avail.txt src/map/mob.* src/map/clif.c)

----------------------------------------
//0887 [2011/12/29] by popori

・PACKETVERのリナンバリング based on eathena
 (vc_make.bat Makefile bcc32_make.bat src/char/char.c src/char/char.dsp src/char/char_sql.dsp src/common/mmo.h
　src/converter/converter.dsp src/login/login.dsp src/login/login_sql.dsp src/map/atcommand.c src/map/chrif.c
　src/map/clif.c src/map/map.dsp src/map/map_sql.dsp src/map/party.c src/map/pc.c src/map/script.c src/map/skill.c)
　分かりづらいPACKETVERの連番方式、PACKETERの途中挿入が非常に面倒なのでeAベースでYYYYMMDD形式に変更します。

・ビルドオプション「NEW_006b」を削除してPACKETVER20061023として定義し、「NEW_006b_RE」を「NEW_006b」として定義する
 (vc_make.bat Makefile bcc32_make.bat src/char/char.c src/char/char.dsp src/char/char_sql.dsp src/map/map.dsp src/map/map_sql.dsp
　src/converter/converter.dsp src/login/login.dsp src/login/login_sql.dsp)

・ついでにリファクタリング (src/char/char.c src/map/clif.c)

----------------------------------------
//0886 [2011/12/29] by popori

・露店と購買露店中の判定をリファクタリング
 (src/map/buyingstore.c src/map/chat.c src/map/clif.c src/map/map.h
　src/map/pc.c src/map/trade.c src/map/unit.c src/map/vending.c)

・VC2008以上でのマルチプロセスビルドのサポート (vc_make.bat)
　※マルチプロセッサ、マルチコアでVC2008環境下であればビルド速度が向上します。

----------------------------------------
//0885 [2011/10/29] by Blaze

・全ての3次職スキルの詠唱時間、射程距離、消費SPなどを本鯖仕様に更新 (db/skill_db.txt, db/skill_cast_db.txt, db/skill_require_db.txt)

・状態異常「冷凍」実装 (status.*, battle.c, pc.c, clif.c, unit.c, db/scdata_db.txt)

・状態異常「ファイティングスピリット」実装（status.c, skill.c）

・状態異常「リプロデュース」中、持続的にSPを消費するように修正（status.c, pc.c）

・ソーサラースキル「ファイアーウォーク」「エレクトリックウォーク」の持続時間を修正（skill.c, db/skill_cast_db.txt）

・ソーサラースキル「アースグレイヴ」に出血付与効果を実装（skill.c）

・ソーサラースキル「ポイズンバスター」の効果範囲を修正（skill.c）

・ウォーロックスキル「アースストレイン」のエフェクト開始位置を修正（skill.c）
	Thanks to dream さん、refis さん

・ウォーロックスキル「アースストレイン」の攻撃判定間隔を調整（db/skill_unit_db.txt）
	Thanks to Akayumi さん

・アークビショップスキル「ラウダアグヌス」「ラウダラムス」を確率で治癒成功判定をするように修正（skill.c）
	Thanks to ARIA さん

・状態異常「マスカレード ： エナーベーション」の攻撃力減少効果が武器の攻撃力のみ減少していたのを修正（status.c）
	Thanks to Akayumi さん

----------------------------------------
//0884 [2011/10/29] by Blaze

・討伐クエストNPC実装 (npc_quest_hunting.txt)

・confにスクリプト定義を追加 (conf/map_auriga.conf)
　※デフォルトは読み込み無効状態です。

・クエストDB更新（db/quest_db.txt）

・0883のファイル構成ミスを再アップ（npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt）
	Thanks to muchey さん

----------------------------------------
//0883 [2011/10/23] by Blaze

・デワタNPC実装 (npc_town_dewata.txt)
	-> ジャティ族の王冠クエスト実装
	-> 古の短剣クエスト実装
	-> デワタの伝統酒クエスト実装
		Thanks to Xia

・デワタ関連NPC追加 (npc_misc_guide.txt, npc_misc_kafra.txt)

・デワタ追加マップのwarp更新（npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt）

・デワタ追加マップのmapflag更新（mapflag.txt）

・デワタ追加マップのmonster出現定義追加（npc_monster_dewfild.txt, npc_monster_dewdun.txt）

・db更新（item_db.txt, item_db2.txt, mob_db.txt, mob_skill_db.txt）
　※Mobデータは暫定です

・conf更新 (map_auriga.conf)

----------------------------------------
//0882 [2011/10/15] by Blaze

・ブラジリスNPC実装 (npc_town_brasilis.txt)
	-> ガラナクエスト実装
	-> 幸運の睡蓮クエスト実装
	-> トイレのオバケクエスト実装
	-> イアラクエスト実装
	-> 変なヒドラクエスト実装
	-> ブラジリスの子犬クエスト実装
		Thanks to Xia

・ブラジリス関連NPC追加 (npc_misc_guide.txt, npc_misc_inn.txt, npc_misc_kafra.txt, npc_quest_ice.txt)

・ブラジリス追加マップのwarp更新（npc_warp_dun.txt, npc_warp_fild.txt, npc_warp_town.txt）

・ブラジリス追加マップのmapflag更新（mapflag.txt）

・ブラジリス追加マップのmonster出現定義追加（npc_monster_brasilis.txt, npc_monster_brafild.txt, npc_monster_bradun.txt）

・db更新（item_db.txt, mob_db.txt, mob_skill_db.txt, quest_db.txt）

・conf更新 (map_auriga.conf)

----------------------------------------
//0881 [2011/09/25] by popori

・ARIAさんのitem_db.txtの修正をマージ (db/item_db.txt)
  ARIAさんに感謝

・0878のマージ漏れを補完 (src/map/clif.c src/map/vending.c)

----------------------------------------
//0880 [2011/09/25] by popori

・battle_auriga.confに「allow_same_activeitem」を追加 (conf/battle_auriga.conf src/map/battle.* src/map/pc.c)
  同じカードのアクティブアイテムを許可するか切り替える
  デフォルトはno

・アクティブアイテム発動中に再度同アイテムの効果が発動しても発動時間が上書きされないのを修正 (src/map/pc.c)
  kroeさんに感謝

・クエストリストの追加、討伐数の更新が正常に適用されない問題を修正 (src/map/clif.c)
  716さんに感謝

----------------------------------------
//0879 [2011/09/25] by popori

・購買露店システムの実装 (conf/battle_auriga.conf db/packet_db.txt src/map/battle.* src/map/buyingstore.* src/map/chat.c
						  src/map/clif.* src/map/map.h src/map/pc.c src/map/trade.c src/map/unit.c src/map/vending.c
						  src/map/map.dsp src/map/map_sql.dsp)

・スキル「購買露店開設」の実装 (db/skill_db.txt db/skill_require_db.txt db/skill_tree.txt src/common/mmo.h src/map/skill.*)

・スクリプト命令「openbuyingstore」の追加 (doc/script_ref.txt db/item_db.txt src/map/script.c)

・item_db2.txtにフラグ「buyingable」を追加 (doc/db_ref.txt src/map/itemdb.* db/item_db2.txt)

----------------------------------------
//0878 [2011/09/25] by popori

・露店処理をパケット0x801を基に変更 (src/map/clif.c src/map/map.h src/map/vending.*)

・ついでに露店処理をリファクタリング (src/map/clif.c src/map/vending.*)

・露店開設中かどうかの判断をvender_idで確認するのではなく、state.vendingで確認するように処理を変更 (src/map/chat.c src/map/clif.c src/map/pc.c src/map/trade.c src/map/vending.c src/map/unit.c)

・パケット0x801の情報を変更 (doc/client_packet.txt)

・PC型MOBのoptが変更された際、恐らくshiftクリックでないと攻撃が出来なくなりそうな個所があったので修正 (src/map/clif.c)

----------------------------------------
//0877 [2011/08/30] by popori

・vc_make.batにVC++ 2010 64bitコンパイルを追加 (vc_make.bat)
　※Windows SDK最新版を基にパスを追記しています。適宜パスを修正して利用して下さい。

・char.cの0x65のリクエストが飛んできた時の判定文が間違っていたので修正 (src/char/char.c)

・0874の無駄を削除 (src/map/pc.c)

・モンク・チャンピオンの両手杖基本ASPDを修正 (db/job_db1.txt)

・3次職の基本ASPDを修正 (db/job_db1.txt)

・3次職のHP・SPを修正 (db/job_hp_db.txt db/job_sp_db.txt db/job_db1.txt)

・battle_auriga.confに「homun_max_aspd」「merc_max_aspd」を追加 (conf/battle_auriga.conf src/map/battle.* src/map/status.c)
　デフォルト値は共に200

----------------------------------------
//0876 [2011/06/24] by Blaze

・メカニックスキル「火と大地の研究」の効果を実装（battle.c）
	Thanks ARIA さん

・メカニックスキル「パワースイング」の以下の効果を実装（skill.c, db/skill_cast_db.txt）
	-> スキル「アックスブーメラン」の追撃発動を実装
	-> 状態異常スタン付与効果を実装
	Thanks ARIA さん

・ジェネティックスキル「剣修練」のHit上昇効果を実装（status.c）
	Thanks ARIA さん

・ロイヤルガードスキル「シールドプレス」のダメージ計算式を修正（battle.c）
	Thanks めろでぃ さん

・ロイヤルガードスキル「アースドライブ」を以下のように修正（battle.c, skill.c）
	-> ダメージ計算式を修正
	-> スキル使用時、一定確率で装備中の盾が壊れるように修正
	Thanks めろでぃ さん

・ソーサラースキル「スペルフィスト」のダメージ計算位置を変更（battle.c）
	Thanks めろでぃ さん

・シャドウチェイサースキル「インビジビリティ」の以下のように修正（skill.c, status.c）
	-> サイトやルアフなどの見破るスキルで解除されるように修正
	-> クリティカル上昇効果がなかったのを修正
	-> Aspd減少効果がなかったのを修正
	Thanks Akayumi さん

・状態異常「ウォーグバイト」中、ハイディング状態とクローキング状態を無効にするよう修正（status.c）
	Thanks Akayumi さん

・メカニックスキル「パワースイング」「アックスブーメラン」「アックストルネード」を
  片手斧と両手斧装備時にのみ使用できるように修正（db/skill_require_db.txt）

・メカニックスキル「アックスブーメラン」にノックバック効果を追加（db/skill_db.txt）

・メカニックスキル「アックストルネード」に以下の効果を追加（battle.c）
	-> 攻撃範囲の外周だと威力が下がるようにダメージ計算式を修正
	-> 風属性の武器を装備時、威力が上昇するようにダメージ計算式を修正

・ウォーロックスキル「ホワイトインプリズン」を使用者自身に使用できるように修正（skill.c, db/skill_db.txt）

・修羅スキル「大纏崩捶」「號砲」「羅刹破凰撃」の必中ダメージ計算位置を変更（battle.c）

・0874のpc_addspiritball()にて、変数の初期化後に定数を入れ直す必要はないため、巻き戻し（pc.c）

・0874のスペルフィスト解除前に状態異常情報のメンバ値を書き換えている箇所を削除（unit.c）


----------------------------------------
//0875 [2011/06/12] by Cocoa

・アイテムボーナス「bAddFixCastRate」「bAddCastRate」が名前と効果が矛盾してるので修正
	item_bonus.txt, skill.c

・それに伴いitem_db.txtの修正

----------------------------------------
//0874 [2011/06/08] by Cocoa

・点穴 -快-が睡眠以外の行動不能状態で使用できない不具合修正（skill.c, unit.c）

・スペルフィスト状態が通常攻撃で必中になっていない不具合修正（battle.c）

・スペルフィスト状態が他のスキルを使用しても解除されない不具合修正（unit.c）

・pc_addspiritball関数でモンク系職業以外もチェックするように修正（pc.c）

・天下大将軍カードの効果発動率上昇職業がアコライト系でなく、アーチャー系になってる不具合修正（item_db.txt）

・虹色のカードキーのDropable,Storageable,Cartableフラグを削除（item_db2.txt）

・WarlockのJobLv12のInt補正値が抜けている不具合修正（job_db2-2.txt）

・イグニッションブレイクが詠唱中断可能になっている不具合修正（skill_db.txt）

・ドラゴンブレスが詠唱中断可能になっている不具合修正（skill_db.txt）

・フルアドレナリンラッシュが一部の武器で使用できない不具合修正（skill_require_db.txt）

・デスペラードの攻撃範囲が広くなっている不具合修正（skill_unit_db.txt）

・エウカリスティカの最大取得レベルが5になっている不具合修正（skill_tree.txt）
	reported by shirasumiさん

----------------------------------------
//0873 [2011/06/02] by Cocoa

・ファントムスラストの使用者と対象が同セルの場合は
	対象を術者の北１セルに移動させるように修正（skill.c）

・バキュームエクストリームの吸い寄せ判定を修正（skill.c）
	BOSS属性は吸い寄せられないで移動先まで滑る
	設置セルとX座標かY座標が同じ場合は吸い寄せられない

・ウォーグダッシュの挙動を修正（skill.c）
	進行方向に敵がいない場合のみウォーグダッシュ発動

----------------------------------------
//0872 [2011/05/24] by Rayce

・気球およびコインタイマーセット時、バッファアンダーフローにより
  サーバクラッシュする問題を修正（pc.c）
		reported by Akayumiさん、pneumaさん

  ※発生条件としては、職業がモンク/チャンピオン/修羅で気功の習得レベルが
    0のとき、オートスペル経由で気球を作るとき等。

----------------------------------------
//0871 [2011/05/23] by Rayce

・床アイテムなどの一時objectのID管理方法を変更（map.c）
  常にIDの小さい方から使い回すのではなく、リングバッファでローテーションする
		based on eA, thx!!

	-> 「mob_ai_sub_hard target type error」が発生する可能性の対処。
	   恐らくMOBがルートアイテムと認識していたIDがすぐにSKILLとして
	   使い回していたのが原因。
			reported by Cocoaさん

	-> スキルユニット関連でサーバクラッシュする可能性の対処。
			reported by crisp.さん

・床アイテムなどの一時objectのIDが再利用されるまでの期間を
  延命するため、MAX_FLOORITEM を 1999999 まで引き上げ（mmo.h）
・IDの有効範囲を広げるため START_NPC_NUM を 5000001 に引き下げ（mmo.h）

----------------------------------------
//0870 [2011/05/22] by Rayce

・サーバースナップショット（version.h）

・*db_txt.c, *db_txt.h をそれぞれ login/txt, char/txt フォルダに分離
・*db_sql.c, *db_sql.h をそれぞれ login/sql, char/sql フォルダに分離

・移動や分離に伴って不要となった *.c, *.h ファイルを削除

・sql-filesフォルダの内、通常使用しないSQLスクリプトはutilsフォルダに
  まとめて置く
	-> convert_engine_innodb.sql
	-> convert_engine_myisam.sql
	-> db_maintenance.sql
	-> drop_table.sql

・sql-filesフォルダの内、パッチに付随するSQLスクリプトは使用される
  ことはないので削除

----------------------------------------
//0869 [2011/05/17] by Cocoa

・転生、1次、2次判定マクロの条件式が間違っている点を修正（pc.h）

----------------------------------------
//0868 [2011/05/15] by Rayce

・loginとcharの *db.h ファイルをTXTとSQL用に分離する
	-> login.h, char.h, inter.h および int_*.h の下に各種 *db_*.h 系を配備
	   各種エイリアスをinterfaceとして扱うことで、TXTとSQLを透過的に
	   includeして利用できる
	-> 元々の *db.h は競合しないように内容を全て削除
	-> TXTモードの場合は *db_txt.* のみ、SQLモードの場合は *db_sql.* のみ
	   コンパイル対象とする

----------------------------------------
//0867 [2011/05/15] by Rayce

・Makefileの依存関係行に指定するオブジェクトを ls コマンドで自動取得
  できるように変更

----------------------------------------
//0866 [2011/05/15] by Rayce

・chgquest命令で、<new_id>が既にクエストリストに存在していた場合に
  同じクエストが重複して存在できてしまう問題を修正
  特にSQLモードだと「Duplicate Entry ... for key 'PRIMARY'」が発生して
  追加処理に失敗していた（quest.c）
		reported by うに～くさん

・setquest命令やchgquest命令で、追加ではなく上書き更新したいのに
  MAX_QUESTLISTに達していると更新できない問題を修正（quest.c）

・quest_data構造体のmobメンバの配列数 3 を出来る限り
  ハードコーティングしないように改善（quest.c）

・TXT: クエストのセーブデータの保存先指定を追加
       （conf/inter_auriga.conf）

----------------------------------------
//0865 [2011/05/14] by Rayce

・TXT: ジャーナルが有効のとき、questdb_txt.cがコンパイルできなかった
       問題を修正（questdb_txt.c）
・TXT: クエスト関連のジャーナル設定がconfファイルになかったので追加
       （conf/inter_auriga.conf）

----------------------------------------
//0864 [2011/05/14] by Cocoa

・「太陽と月と星の融合」状態ではすべての攻撃が100%ヒットするように修正（battle.c）

----------------------------------------
//0863 [2011/05/12] by Cocoa

・ファイアーエクスパンション(催涙)の仕様を仮修正
　石化同様に最低でもHP1で死亡しないように修正
　※催涙の記事が探しても出てこないので仮修正とします。

----------------------------------------
//0862 [2011/05/10] by Rayce

・ドラゴンライティングのスキルLvが5以上のときにドラゴンブレスの計算式を
  スイッチするように0860を更に拡張（battle.c）

・auriga.dsp と auriga_sql.dsp で、それ自身がexeファイルを生成しようとして
  コンパイル時にエラーが発生していたのを修正
  構成の種類を "exe" から "ユーティリティ" に変更し、無駄なオプションを排除
  （auriga.dsp, auriga_sql.dsp）

・auriga_sql.dsp でSQLモードのコンパイルを行うと、sqldbs.* が参照できずに
  コンパイルに失敗する問題を修正
  （login_sql.dsp, char_sql.dsp, map_sql.dsp, converter.dsp）

----------------------------------------
//0861 [2011/05/09] by Rayce

・login鯖およびchar鯖起動時にconfファイルを読み込む際、キーワードが
  見つかった場合は以降のルーチンを省略するように高速化

・統一性を持たせるため、inter鯖のlogも interlog.h, interlog_sql.c,
  interlog_txt.c に分離（inter.*, int_guild.c）

----------------------------------------
//0860 [2011/05/09] by Cocoa

・ルーンナイトスキル「ドラゴンブレス」の計算式を修正（battle.c）
	thanks ばるす さん

----------------------------------------
//0859 [2011/05/09] by Cocoa

・bDefEleEnemyがbSubEleになっていたアイテム修正（db/item_db.txt）
	thanks Akayumi さん

・傭兵召喚書の剣と槍が入れ違いになっていた点を修正（db/item_db.txt）
	thanks gokunan さん

----------------------------------------
//0858 [2011/05/09] by Rayce

・db_search() と db_exists() の処理を db_search_dbn() で共通化（db.c）

・SQL: constの付いた構造体にmemcpyしているため、コンパイル時に警告が発生していたのを修正
       （questdb_sql.c）

・SQL: innoDBでは「INSERT DELAYED」が非サポートなため、login鯖の起動/停止時に
       「DELAYED option not supported for table 'loginlog'」が発生していたのを修正
       information_schemaからengine情報を取得し、DELAYEDがサポートされている
       エンジンの場合のみDELAYEDを付ける（account_sql.c）
         ※http://dev.mysql.com/doc/refman/5.1/en/insert-delayed.html

----------------------------------------
//0857 [2011/05/09] by Cocoa

・SpeedRateが変化している状態の時、ステータスの再計算が入る毎に「速度が増加しました」と出ていた不具合を修正（src/pc.c, src/status.c）

----------------------------------------
//0856 [2011/05/08] by Rayce

・script/function/function_jobgroup.txt は未使用なので、map_auriga.conf から削除

・db/addon以下のdbファイルを現在のdbファイルの定義と同期
  （merc_db_add.txt, skill_cast_db_add.txt）

----------------------------------------
//0855 [2011/05/08] by Cocoa

・呪い、石化状態でブレッシングを受けると状態異常解除のみ行うように修正（src/status.c）

・アークビショップのスキルツリーでオラティオの最大取得レベルが5だったのを修正（db/skill_tree.txt）

・アークビショップスキル「クリアランス」が自身に使用可能だったので修正（db/skill_db.txt）
	※GvGにおいて敵に使用は出来ないという仕様はまだ未適用です。

----------------------------------------
//0854 [2011/05/08] by Cocoa

・カートが外れた時にカートブースト状態が終了するように修正（src/pc.c）

----------------------------------------
//0853 [2011/04/15] by popori

・httpdのアカウント作成経由で性別が小文字だったのを修正 (src/login/login_httpd.c httpd/index.html)

・TXTで新規アカウント作成時渡されたbirth情報が保存されていなかったのを修正 (src/login/account_txt.c)

・不正対策の強化 (src/map/clif.c)

・いくつかのwarningを修正 (src/common/sqldbs.c src/char/char.c src/char/accregdb_sql.c src/char/chardb_sql.c src/char/guilddb_sql.c src/char/homundb_sql.c)
　Cocoaさんに感謝

・SQL:0851のquestテーブルのエンジン指定がTYPEになっているのでENGINEに変更 (sql-files/Auriga851_changetable.sql sql-files/main.sql)

----------------------------------------
//0852 [2011/04/13] by Blaze

・SQL：0851にてコンパイルエラーが発生するのを修正（char/questdb_sql.c）
	-> queryの戻り値をbool型に修正
	-> SQL文の文字列範囲がおかしかったのを修正

----------------------------------------
//0851 [2011/04/13] by Blaze

・クエストリスト実装 (map.*, quest.*, clif.*, pc.c, mob.c, common/mmo.h, db/quest_db.txt)

・セーブデータ対象にクエスト情報を追加 (char/inter.c, char/char.c, char/int_quest.*, char/questdb.*)

・SQL：DBにクエストテーブル追加 (common/sqldbs.h, sql-files/main.sql, sql-files/drop_table.sql, sql-files/db_maintenance.sql,
								 sql-files/convert_engine_myisam.sql, sql-files/convert_engine_innodb.sql, sql-files/Auriga851_changetable.sql)

・TXT：JOURNAL_IDENTIFIERを13->14に引き上げ (journal.c)

・パケットDBにクエストリスト関連のパケット定義を追加 (db/packet_db.txt)

・スクリプト命令・関数に以下を追加（script.c, doc/script_ref.txt）
	setquest : クエストを追加します
	chgquest : クエストを更新します
	delquest : クエストを削除します
	checkquest : クエストの情報を返します
	getquestlimit : クエストの制限時間を取得します
	getquestcount : クエストの討伐数を取得します
	getquestmaxcount : クエストの討伐最大数を取得します
	※詳しくはscript_ref.txtを参照

・クエストリストのメンテナンスNPC実装（npc_misc_questlist.txt, conf/map_auriga.conf）

・以下のクエストをクエストリストに対応化（script/*）
	ソードマン転職クエスト（npc_job_01swordman.txt）
	マジシャン転職クエスト（npc_job_02magician.txt）
	アーチャー転職クエスト（npc_job_03archer.txt）
	アコライト転職クエスト（npc_job_04acolyte.txt）
	マーチャント転職クエスト（npc_job_05merchant.txt）
	スーパーノービス転職クエスト（npc_job_23supernovice.txt）
	テコンキッド転職クエスト（npc_job_24taekwonkid.txt）
	ガンスリンガー転職クエスト（npc_job_28gunslinger.txt）
	忍者転職クエスト（npc_job_29ninja.txt）
	転生クエスト（npc_job_transmigration.txt）
	魔王モロク討伐クエスト（npc_town_morocc.txt）
	運命のカラスクエスト（npc_town_morocc.txt）

----------------------------------------
//0850 [2011/04/13] by popori

・auth_node形式を一旦auth_fifo形式にする (login.c char.c mmo.h)

・少しだけパケット情報を追記 (client_packet.txt)

----------------------------------------
//0849 [2011/04/12] by popori

・ノードの削除を忘れているケースがあったので修正 (login.c)

・いくつかJT_*****が更新されていたのでコメントアウトで定義だけ追加 (skill.h)

・ドキュメントを少し更新 (server_build.txt sqllogin.txt)

----------------------------------------
//0848 [2011/04/11] by Cocoa

・3次職の基本所持量を修正（db/job_db1.txt）

・Job補正値を各職Wikiを参考に修正（job_db2.txt, job_db2-2.txt, status.c）

----------------------------------------
//0847 [2011/04/11] by Rayce

・デッドリーインフェクトによる状態異常の複写ができるかどうかの定義を
  scdata_db.txt で行うように拡張（status.*）

・anti hacker強化（booking.c, skill.c）
・定数部分には出来る限りconstを付与する（mob.*, pc.c, skill.c）
・マクロの変数を括弧で括る（clif.c）

----------------------------------------
//0846 [2011/04/10] by Rayce

・booking_map_db.txt および booking_job_db.txt において、IDの昇順に
  並んでない場合にbinary searchが正常動作しなくなるので、読込時に
  補正を行うように修正（booking.c）

・booking_map_db.txtではID「0」は有効な値なので、memsetでの初期化は
  「-1」で詰めるように修正（booking.c）

・booking_idをunsigned int型に統一（booking.*, clif.*, map.h）

・混乱を避けるため、booking_search_mapid() と booking_search_jobid() の
  結果を反転させる（booking.c）

・パケット0x805の<more>に相当する部分において、変数flagの値が非常に大きい
  場合に桁溢れが発生する可能性があるので修正（clif.c）

・booking_map_db.txt の「ピラミッドダンジョン 2F」のMAPIDが恐らく
  間違っているので修正（db/booking_map_db.txt）

----------------------------------------
//0845 [2011/04/10] by Rayce

・計算式を一般式に展開し簡素化（battle.c, skill.c）
	-> ヘルズプラント
	-> 寒いジョーク
	-> スクリーム
	-> クラッカー

・インスピレーションでのロスト経験値の型はatn_bignumberである
  必要はないのでintに変更（skill.c）

・スリングアイテムとグラウンドドリフトにおける判定文が何か
  おかしいので修正（skill.c）

・細かいリファクタリング（battle.c, skill.c, status.c）

----------------------------------------
//0844 [2011/04/10] by popori

・httpd経由で正常にアカウントが作成出来なかったバグを修正 (login_httpd.c)

----------------------------------------
//0843 [2011/04/09] by popori

・ログインサーバーのソースを整理 (src/login/login.c)

・tool/phpでアカウントを作成出来るように対応 (tool/php/auriga.php tool/php/createaccount.php)

----------------------------------------
//0842 [2011/04/08] by Blaze

・0839でJOURNAL_IDENTIFIERを上げていないので12->13にアップ (journal.c)

・0837の修正にfloatが使用されているのを修正 (battle.c)

・0838でデバッグコマンド「@lvup」によるレベルアップ時、
　ステータスポイント取得設定が反映されていない不具合修正（atcommand.c）

・0838の判定文を微修正（pc.c）

・0822以降、養子縁組の判定文誤りにて養子の要請が出来なかった不具合を修正（pc.c）
	Thanks 黒猫 さん

----------------------------------------
//0841 [2011/04/08] by popori

・x64環境下でコンパイルするとワーニングが発生するのを修正 (login.c)
　Cocoaさんに感謝

----------------------------------------
//0840 [2011/04/08] by Cocoa

・0839でget_status_point_over_lv100ではなくpk_murderer_pointを参照していた不具合修正

----------------------------------------
//0839 [2011/04/08] by popori

・sqldbs.*に関する変更 (src/common/sqldbs.*)
 ->プリペアドステートメントに関するAPIを追加

 ->sqldbs_simplequery()を追加して単純な文字列を流す場合はこちらを使用するよう変更する

・ログインサーバーに関する変更 (src/login/* sql-files/Auriga837_changetable.sql sql-files/main.sql conf/login_auriga.conf)

 ->ログインサーバーの処理が全てlogin.cに集約しているので、各機能ごとに分割する
   今のところ大雑把にファイルを分割しただけです。
   少々強引ですが、1ファイルに全ての処理が集約しているのは形式として良くないと考えたためです。

 ->SQL: 該当のセーブデータを縮小しコーディングを簡略化する(0229の変更の補完)
   login table userid varchar(24) → login table userid varchar(23)
   login table user_pass varchar(24) → login table user_pass varchar(23)
   login table email varchar(40) → login table email varchar(39)
   worldreg table reg varchar(32) → worldreg table reg varchar(31)

 ->SQL: loginテーブルのsexをENUM型に変更する

 ->安全のためデフォルトでconf/login_auriga.confのristrict_admin_localオプションを有効に変更

 ->login_auriga.confのnew_accountをデフォルトで0に変更

 ->auth_fifo形式を廃止してauth_nodeを新たに追加する

 ->SQL: ログインサーバーのプリペアドステートメント、トランザクションに対応。一部のSQLインジェクション対策はプリペアドステートメントを使用するよう変更
        トランザクションに対応するにはMySQLのストレージエンジンをInnoDBに変更して下さい。
        今回のパッチからMySQL4.xをサポートを打ち切ります。
        各自5.xに移行して下さい。
        また、MyISAMの場合START TRANSACTIONを送っても無視されるだけなので、エンジンに関わらずSTART TRANSACTIONを送っています。

 ->その他細かい変更

・キャラクターサーバーに関する変更 (src/char/*)

 ->各機能ごとにソースファイルを分離
   現在はログインサーバーと同じくある程度大雑把に分割しただけです。
   interサーバーとしてのparse部分は従来通りint_****.*にして保存処理を別ファイルに置き換えました。
   同時にキャラクターサーバーとしての動作も1ファイルに集約しているので分割。
   やはり少々強引ですが、1ファイルに処理が集約しすぎていると考えたためです。
   現在暫定的にグローバルに設置しているオブジェクトがありますが、徐々に見直す予定。

 ->SQL: キャラサーバーの一部の処理をトランザクション・プリペアドステートメントに対応させる
        現在一部は未対応なので、追々全て対応させます。

 ->auth_fifo形式を廃止してauth_nodeを新たに追加する

 ->その他細かい変更

・上記の変更に伴いエンジンコンバート用スクリプトを追加 (sql-files/convert_engine_innodb.sql sql-files/convert_engine_myisam.sql)

・MySQLの簡易的なメンテナンス用にdb_maintenance.sqlを追加 (sql-files/db_maintenance.sql)
　ANALYZE TABLE、OPTIMIZE TABLEを実行するだけのものです。
　定期的に実行することによって、Aurigaで使用するテーブルのパフォーマンス低下を防げるかもしれません。

・AUTH_FIFO_SIZEをコードから削除 (src/common/mmo.h)

・MySQL5.2以降に対応(エンジンの指定をTYPEからENGINEに変更しただけです) (sql-files/main.sql)
　crisp.さんに感謝

・utils.hにbool型を追加(charのシノニム) (src/common/utils.h)

・上記の変更に伴い一部関数の仕様を変更 (src/common/sqldbs.* src/char/* src/map/map.c src/map/intif.c)

・性別の定義をenumで用意する (src/common/mmo.h src/login/login.* src/login/account_*.c src/map/atcommand.c src/map/clif.c src/map/itemdb.c src/map/pc.c src/map/script.c src/map/skill.c)

・管理者用パケットのサイズの一部の無駄を省く (src/login/login.c tool/ladmin doc/admin_packet.txt)
  今回の変更でtool/php以下のものは現在対応していません。
  後日tool/php以下も対応させます。

・2010-08-03aRagexeRE以降のクライアントの誕生日認証キャラ削除パケットに対応 (tool/ladmin src/char/char.c src/login/login.* src/common/mmo.h sql-files/main.sql sql-files/Auriga837_changetable.sql conf/char_auriga.conf doc/serverlink_packet.txt win32_start.bat)
  誕生日のデータは初期値は000000です。
  char_auriga.confのdelete_delay_timeはキャラを削除可能までの待機時間です、各自設定して下さい。デフォルトは24時間。
  今回の変更でtool/php以下のものは現在対応していません。
  後日tool/php以下も対応させます。

・上記の変更に伴いPACKETVERを31に引き上げ (vc_make.bat bcc32_make.bat Makefile *.dsp)

・ビルドオプションにAC_BIRTHDATEを追加 (vc_make.bat bcc32_make.bat Makefile src/login/login.c)
　誕生日認証でキャラを削除する場合はONにして下さい。
　2010-08-03aRagexeRE以降のクライアントのみ対応です。
　誕生日データはYYMMDDの形式で半角数値6バイト強制です。

・コスチュームシステム用にセーブデータだけ拡張しておく (src/common/mmo.h src/char/char.c src/map/itemdb.h sql-files/Auriga837_changetable.sql sql-files/main.sql)

・装備閲覧でMAPサーバーがクラッシュするバグを修正 (src/map/clif.c)
　Akayumiさんに感謝

・MAX_PACKET_DBとpacket_db構造体の定義をclif.hからclif.cに移動 (clif.*)

・本家の設定に合わせてペットの髪型情報の送信はAREA指定で送るよう変更 (src/map/clif.* src/map/pet.c)

・フリーキャストで移動速度が増加するバグを修正 (src/map/status.c src/map/unit.c)
　うに～くさんに感謝

・攻撃による状態異常付与の仕様を一部巻き戻す (src/map/battle.*)
 ->スキル「猛虎硬派山」のノックバック効果はダメージが発生しないとノックバックしないよう変更
 ->ダメージが1以上の場合のみ攻撃による状態異常を付与させるよう変更

・gcc4.3.4環境下でのコンパイルワーニングの修正 (src/map/battle.c src/map/skill.c src/map/status.c)

・最大所持金を本家仕様に合わせて拡大 (src/map/mmo.h)

・0x43fのパラメータをパケットの構造に合わせて拡張だけしておく (src/map/atcommand.c src/map/clif.* src/map/pc.c src/map/skill.c src/map/unit.c)
　基本的にval1,val2,val3に入る値は確率であったり、適用%だったりします。

・クラスIDの定義にJT_SANTA、JT_SUMMERが抜けているので追加 (src/common/mmo.h)

・職業のenum定義を使用していない箇所を使用するよう変更 (src/map/clif.c)

・battle_auriga.confのclif_fix_levelを少し拡張 (conf/battle_auriga.conf src/map/clif.c)
　3次職でレベルが150以上の場合でもオーラを表示出来るように

・0838を少し修正 (src/map/pc.c)

・スキルを一時的に覚えた状態でポイントを振るとポイントだけ消費されるのを修正 (src/map/pc.c)
　Cocoaさんに感謝

----------------------------------------
//0838 [2011/04/07] by Cocoa
・3次職の養子がbaby_status_max以上にステータスが振れなかった不具合修正（pc.c）

・BaseLevel100以上の時にレベルアップで取得するステータスポイントをjRO仕様に修正（pc.c）

・戦闘設定に「get_status_point_over_lv100」を追加（battle.*, pc.c, conf/battle_auriga.conf）
　-> BaseLevel100以上の時にレベルアップで取得できるステータスポイントの方式を選択できます。

----------------------------------------
//0837 [2011/04/04] by Cocoa

・ヘルズプラントのダメージ式を修正（battle.c）
	Thanks velvet0001 さん

----------------------------------------
//0836 [2011/03/06] by Blaze

・0738以降、Mobが状態異常などにより移動速度が変化した際、表示上の速度が変化しなかった不具合修正(clif.c)

・戦闘設定に「clif_fix_level」を追加(battle.*, clif.c, conf/battle_auriga.conf)
　-> PC,Mobなどがレベル100以上の場合、99に補正する（オーラを表示する）かどうかを設定できます（デフォルト：no）

・ウォーロックスキル「リーディングスペルブック」でテトラボルテックスの効果が発動しなかったのを修正(skill.c)
　-> PC以外のキャラでもテトラボルテックスが使用できるように修正

・シャドウチェイサースキル「リプロデュース」で一部スキルが習得できなかったのを修正(skill.c)
　-> 例）デュプレライト、シビアレインストーム、テトラボルテックスなど

・0835のスキル使用時、装備品の装備チェックを巻き戻し(skill.c)
　-> メカニックスキル「パイルバンカー」「ホバーリング」のみ装備チェックをするように変更
	Thanks ばるす さん

・ジェネティックスキル「スリングアイテム」のダメージ効果を相手が敵以外の場合は発生しないよう修正(skill.c)
	Thanks Akayumi さん

----------------------------------------
//0835 [2011/02/26] by Blaze

・状態異常「マジックマッシュルーム」のランダムスキル使用を実装(status.c)

・レンジャースキル「ウォーグダッシュ」の衝突ダメージ効果を実装(unit.c, skill.c, battle.c)

・ウォーグ騎乗時、一部トラップスキルが使用できるように修正(skill.c)

・ウォーグ騎乗中、ログイン時にエラーが表示される現象の回避策を適応(char.c)

・気功の仕様を変更、処理を最適化(pc.c, skill.c, battle.c, db/skill_cast_db.txt)
　-> 対象の職業がモンク・修羅以外は「気功」のスキルレベルを参照しないように変更
　-> 気功セット関数「pc_addspiritball()」を複数個セットできるように拡張
	Thanks Elisil さん

・シャドウチェイサースキル「メイルストーム」の仕様を変更(skill.c)
　-> 使用者がメイルストームの効果範囲内にいるときのみ、スキル吸収効果が発動するように
	Thanks unsyu さん

・0801のスキル使用時、水場セル判定の処理誤りを修正(skill.c)
	Thanks muchey さん

・スキル使用アイテム判定で、アイテムの種別が装備品の場合は装備中かどうかを判定するように修正(skill.c)
	Thanks olion22 さん

・ランダムスキルDB構造体とチェンジマテリアルDB構造体の宣言で、
　extern修飾子にも関わらず実体がstaticで隠蔽されていたのを修正(skill.c)
	Thanks takeshi さん

・ウォーロックスキル「コメット」を火属性から無属性攻撃に修正(db/skill_db.txt)
	Thanks unsyu さん

・状態異常「発火」「氷結」を対象がボス属性の場合は無効に修正(db/scdata_db.txt)
	Thanks olion22 さん

----------------------------------------
//0834 [2011/02/24] by Blaze

・スキルユニット設定処理「skill_unitsetting()」のflag値をスキル種別によって用途を変えるように変更(skill.c)
　-> グラウンドドリフト：装備している弾丸のIDを渡すように変更
　-> トラップ系スキル：使用した罠のIDを渡すように変更

・レンジャースキル「トラップ研究」の効果を追加(skill.c)
　-> 設置用トラップが必要なスキルにおいて、改良型設置用トラップで代用が可能になります

・ハンタースキル「リムーブトラップ」の処理を変更(skill.c)
　-> 設置用トラップを消費して使用した場合にのみ罠を返還するように修正
　-> ある条件下で罠アイテムを量産できていたのが修正されます

・トラップ系スキルの時間切れ時、罠を消費していた場合のみ罠を返還するように修正(skill.c)

・ガンスリンガースキル「グラウンドドリフト」使用時、弾丸が残り1のときに効果が不定になっていたのを修正(skill.c)

・0455の矢種別設定でスフィア系を個別に設定されていたのを廃止(db/item_arrowtype.txt, db/skill_require_db2.txt)

・レンジャースキル「鋭敏な嗅覚」のトラップ除去効果を実装(skill.c)

・シャドウチェイサースキル「メイルストーム」実装(skill.c)

・「メテオストーム」「ロードオブヴァーミリオン」のオーバーレベル条件を修正(skill.c)
　-> スキルレベルが11以上 -> 使用者がMOB & スキルレベルが戦闘設定「monster_skill_over」以上の場合

・NPCスキル「アースクエイク」をMdef無視攻撃に修正(battle.c)

----------------------------------------
//0833 [2011/02/20] by Blaze

・一部の3-1次職スキルの攻撃力・詠唱時間などを修正(skill.c, battle.c, db/skill_cast_db.txt)

・連続ヒットする魔法系スキルのダメージ計算で、一部のスキルのみヒット数で倍化するように変更(battle.c)
　-> 一部のスキルにおいて、草系のモンスターへヒット数分のダメージを与えていたのが修正されます

・メカニックスキル「FAW マジックデコイ」の召喚処理を実装(skill.*, clif.*)

・ポイズニングウェポン、リーディングスペルとオートシャドウスペルのスキル使用時、
　材料がなければリストを表示しないように修正(clif.c)

・NPCスキル「アースクエイク」の処理を最適化(skill.c, battle.c, db/skill_db.txt)
　-> 物理スキルから魔法スキルに変更
　-> 連続ヒットの見た目を修正
　-> 威力を本家仕様に修正

・モンクスキル「三段掌」の処理を最適化(skill.c, battle.c)

・チャンピオンスキル「伏虎拳」と「連柱崩撃」の使用条件で
　「三段掌」「連打掌」から繋げて使用できていなかったのを修正(skill.c)

・ジェネティックスキル「スリングアイテム」をアイテムを装備していない状態で使用すると
　サーバークラッシュが起きてしまう不具合を修正(skill.c)
	Thanks ChowZenki さん

・シャドウチェイサースキル「シャドウフォーム」をお互いにかけ合った状態で
　無限ループが発生してしまう不具合を修正(battle.c)
	Thanks Akayumi さん

・ルーンナイトがドラゴン騎乗中、ログイン時にエラーが表示される現象の回避策を適応(char.c)
	Thanks refis さん

----------------------------------------
//0832 [2011/02/16] by Blaze

・ウォーロックスキル修正(skill.c, status.c, battle.c, db/skill_db.txt, db/skill_cast_db.txt, db/skill_unit_db.txt)
　-> チェーンライトニング連鎖を実装
　-> ヘルインフェルノの闇属性攻撃を実装
　-> テトラボルテックスの使用条件をサモンボールの属性を問わないように修正
　-> テトラボルテックスの状態異常効果を実装
　-> クリムゾンロックの攻撃範囲が対象のノックバック先の位置から発生していたのを修正
　-> ドレインライフでプレイヤーのHP表記がおかしくなっていた不具合修正
　-> ホワイトインプリズンのダメージ効果を修正
　-> ジャックフロストを氷結状態でなくてもダメージを与えるように修正
　-> アースストレインの攻撃範囲を修正
　-> その他スキル威力計算式の見直し

----------------------------------------
//0831 [2011/02/14] by Blaze

・スキル使用失敗のメッセージを多様化(clif.*, skill.c, unit.c, homun.c, vending.c)
　-> 各スキル使用失敗時、アイテム不足や気弾が必要などの詳細メッセージが表示されます
　-> 0x110のパラメータを変更

・アークビショップスキル「アンシラ」が所持限界数を超えて生成できないように修正(skill.c)

・アイテムの各ルーンストーンとアンシラをドロップ不可、倉庫不可、取引不可に修正(db/item_db2.txt)

・0829のドラゴン騎乗時の所持量増加ボーナス誤りを修正(status.c)
	Thanks ARIA さん

・ソウルリンカースキル「転生一次職業の魂」でシーフハイが判定されない不具合修正(status.c)
	Thanks ARIA さん

・アークビショップスキル「シレンティウム」の最大レベルを修正(db/skill_db.txt)
	Thanks ARIA さん

----------------------------------------
//0830 [2011/02/13] by Blaze

・ルーンナイトスキル修正(skill.c, status.c, battle.c, db/skill_db.txt, db/skill_db2.txt, db/skill_cast.txt,)
　-> エンチャントブレイドを自分自身対象から相手指定に修正
　-> ソニックウェーブの射程距離を修正
	Thanks Sheep さん
　-> エンチャントブレイドの効果中、Matkに影響しないように修正
　-> エンチャントブレイドの計算式を相手Mdefに影響するように修正
　-> ファントムスラストを攻城戦中やボスモンスター相手には移動効果が発動しないように修正
　-> ハンドレッドスピアで追撃効果が発動する時にノックバック効果を追加
　-> その他スキル威力計算式の見直し

・転生ルーンナイトの「バーサーク」スキル習得条件からJobLvの規制を削除(db/skill_tree.txt)

・ルーンストーン製造の成功率を本鯖仕様化(skill.c, db/produce_db.txt)

・0829のスキル「武器精錬」の判定式誤りを修正(status.c)

----------------------------------------
//0829 [2011/02/13] by popori

・フリーキャストの計算式を修正 (unit.c status.c)

・ペコペコ・ドラゴン騎乗時に所持量増加ボーナスが消えていたので修正 (status.c)

・スキル「武器精錬」をメカニックが行う際は、JobLvに関係なくJovLv70として計算するよう変更 (status.c)

・スキル「オートシャドウスペル」で不正なパケットにより3次職スキルも使用出来る可能性があるので、チェックを強化 (skill.c)

・enum定義LOOK_MOBは本家に存在しないので削除する (map.h pc.c script.c)

・ペットの卵で名前変更済みでも、冠詞に「愛されている」が付かない場合があるのを修正 (clif.c)
　tomoさん、anteraさん、pneumaさんに感謝

・GM右クリックメニュー「全ての装備を解除」にて1分間全ての脱衣系の状態異常にかかるよう本家仕様に修正 (clif.c)

・スキル「ソウルドレイン」の処理位置を移動 (battle.c)

・PACKETVER7-13でのコンパイルエラーを修正 (clif.c)
　シロウさんに感謝

・スキル「メルトダウン」を本家仕様に変更 (scdata_db.txt)
　※ゴスペルによる、状態異常解除可否は分からなかったのでとりあえず有効にしています。
　ばるすさんに感謝

・pc_nextbaseexp() pc_nextjobexp()は順次参照で効率が悪い気がするので、ダイレクトジャンプさせるよう最適化 (pc.c)

・item_db.txtのIDが一部違うのを修正 (item_db.txt)
　シロウさんに感謝

・その他細かい変更 (packet_db.txt battle.c clif.c skill.c itemdb.h)

----------------------------------------
//0828 [2011/02/13] by Blaze

・ジェネティックスキル実装
	(skill.*, status.*, battle.c, clif.c, unit.c, pc.c,
	 db/skill_db.txt, db/skill_db2.txt,db/skill_cast_db.txt,
	 db/skill_require_db.txt, db/skill_require_db2.txt, db/skill_unit_db.txt,
	 db/skill_tree.txt, db/scdata_db.txt, db/produce_db.txt)

・3次職関連のアイテムDBを更新(item_db.txt, const.txt)
　※暫定処理中のため、3次職専用装備が2次職も装備可能で定義されています

・ジェネティックスキル「チェンジマテリアル」のDBを追加(db/changematerial_db.txt, db/packet_db.txt, doc/client_packet.txt)

・ブラックスミススキル「武器修理」や料理システム、各製造系スキルの処理を最適化(map.h, clif.c, skill.c, script.c)

・ロイヤルガードスキル「イクシードブレイク」使用時にサーバークラッシュする不具合を修正(status.c)
	Thanks rapis さん、unsyu さん、Azurite さん

・状態異常「アースドライブ」の効果でASPDが増加していた不具合を修正(status.c)
	Thanks rapis さん、unsyu さん

・ミンストレル・ワンダラースキル「地獄の歌」の判定誤りを修正(skill.c)
	Thanks rapis さん

・セージスキル「アドバンスドブック」の効果が異常だった不具合を修正(status.c)
	Thanks ねぎぽん さん

・シャドウチェイサースキル「シャドウフォーム」の仕様を変更(skill.c, db/skill_db.txt)
　-> 自分自身には使用できないように修正
　-> 一般MAPにはパーティメンバーに対してのみ発動するように修正
	Thanks ばるす さん、ARIA さん


----------------------------------------
//0827 [2011/02/06] by Blaze

・ロイヤルガードスキル実装
	(skill.*, status.c, battle.c, clif.c, unit.c, pc.c, common/mmo.h,
	 db/skill_db.txt, db/skill_db2.txt,db/skill_cast_db.txt, db/skill_require_db.txt, db/skill_unit_db.txt)
　-> バンディングの一部効果は未実装です
　-> シールドスペルのレベル2使用時、盾のMdefを参照する箇所を
　　 暫定でDefを参照するようにしています

・ハイウィザードスキル「ソウルドレイン」とNPCスキル「自爆」が動作しなかった不具合修正(battle.c)
	Thanks ばるす さん

・ガンスリンガースキル「シングルアクション」とセージスキル「アドバンスドブック」習得時、ASPDが遅くなる不具合修正(status.c)
	Thanks ARIA さん

・バードスキル「夕陽のアサシンクロス」とダンサースキル「私を忘れないで」で、演奏範囲外に出ると効果が継続しない不具合修正(status.c)
	Thanks ばるす さん

・バードとダンサーの合奏スキルの使用条件の職業判定誤りを修正(skill.c)
	Thanks Azurite さん、ばるす さん

・修羅のスキルツリーで「雷光弾」と「獅子吼」の前提スキルを修正(db/skill_tree.txt)
	Thanks bansyu さん

・シャドウチェイサースキル「ストリップアクセサリー」の最大レベルを3から5に修正(db/skill_db.txt)
	Thanks Azurite さん

・ファルコンレンタルNPCから該当職でもレンタルできない不具合修正(npc_job_11hunter.txt)
	Thanks ayu さん

・クルセイダー専用ペコペコレンタルNPCから該当職でもレンタルできない不具合修正(npc_job_14crusader.txt)
	Thanks ayu さん

・アイテム「毒薬の瓶」使用時、該当職でも効果が得られない不具合修正(db/item_db.txt)
	Thanks ayu さん

・修羅スキル「號砲」と「羅刹破凰撃」が味方にもダメージを与えることができた不具合修正(skill.c, db/skill_db.txt)

・状態異常「マジックマッシュルーム」と「リーチエンド」が死亡後にもダメージ効果が継続する不具合修正(status.c)

・スナイパースキル「シャープシューティング」等の斜線算出で、斜め方向の距離が半減していたのを修正(map.c)


----------------------------------------
//0826 [2011/02/03] by Blaze

・修羅スキル実装
	(skill.c, status.*, battle.*, clif.c, unit.c, pc.c, mob.c, map.h
	 db/skill_db.txt, db/skill_db2.txt,db/skill_cast_db.txt, db/skill_require_db.txt)


----------------------------------------
//0825 [2011/01/29] by Blaze

・ミンストレル・ワンダラースキル実装
	(skill.*, status.*, battle.c, clif.c, unit.c, db/skill_db.txt, db/skill_db2.txt,
	 db/skill_cast_db.txt, db/skill_require_db.txt, db/skill_require_db2.txt, db/skill_unit_db.txt)
　-> 合唱人数による効果上昇および消費SP減少は調整中のため未実装です

・戦闘設定に3次歌スキルが重複して効果を得られるか設定を追加(battle.*, conf/battle_auriga.conf)

・複数ヒットする魔法系スキルの威力の計算式修正(battle.c)

・ダンサースキル「魅惑のウィンク」の効果を修正(status.c, battle.c, skill.c, unit.c)
　-> 一律攻撃不可状態から使用者のみ攻撃不可になります

・ランダム発動スキルDBを追加(skill.*, db/skill_random.txt)
　-> 試作段階のため、現状ソース内の処理専用となります
　　（今後、スクリプトからのランダム発動を検討中）

・マジシャンスキル「フロストダイバー」の凍結効果がすぐに解除されてしまう不具合修正(skill.c)
	Thanks ばるす さん

・戦闘設定の新ステータス計算形式の設定が必要ポイント計算式に反映されない不具合修正(pc.c)
	Thanks kanashi さん

・カプラ職員とジョンダ職員からカートを正常にレンタルできない不具合修正(npc_misc_kafra.txt, npc_misc_zonda.txt)
	Thanks p-studio さん、NP3228 さん

・シャドウチェイサースキル「フェイタルメナス」使用時、
　相手が死亡後に対象の情報を参照していた不具合修正(skill.c)
	Thanks unsyu さん、refis さん

・シャドウチェイサースキル「オートシャドウスペル」の仕様を変更(battle.c, clif.c)
　-> 近距離攻撃でダメージを与えた場合に発動するように修正
　-> 3次職スキルは発動スキルメニューで選択できないように修正
	Thanks unsyu さん、refis さん


----------------------------------------
//0824 [2011/01/24] by Blaze

・ソーサラースキル実装
	(skill.*, status.*, battle.c, clif.c, unit.c, db/skill_db.txt, db/skill_db2.txt,
	 db/skill_cast_db.txt, db/skill_require_db.txt, db/skill_unit_db.txt)
　-> 精霊関係のスキルは未実装です

・サンプルの転職NPCの不具合を修正(npc_custom_jobchange.txt)

----------------------------------------
//0823 [2011/01/23] by Blaze

・シャドウチェイサースキル実装
	(skill.*, battle.c, map.*, clif.*, db/skill_db.txt, db/skill_db2.txt,
	 db/skill_cast_db.txt, db/skill_require_db.txt, db/skill_require_db2.txt, db/skill_unit_db.txt)
　-> メイルストームは動作不安定のため、未実装です

・シャドウチェイサー関連の状態異常実装(status.*, unit.c, mmo.h, pc.c, mob.c, pet.*, db/scdata_db.txt)

・スクリプト関数「checkwolf()」の仕様変更(script.c)
　-> パラメータ指定により、ウォーグ召喚またはウォーグ騎乗の両方がチェックできるようになります
　-> 「checkwolfmount()」は廃止されます

・0822以降、一部コンパイラにてエラーが出る不具合を修正 (script.c)
	Thanks eucalyptus さん

----------------------------------------
//0822 [2011/01/22] by Blaze

・3次職実装(mmo.h, char.c, map.h, pc.*, skill.c, status.c, clif.c, atcommand.c, mob.c)

・職業定義関連のDBを修正(db/exp.txt, db/job_db1.txt, db/job_db2.txt, db/job_db2-2.txt, db/job_hp_db.txt, db/job_sp_db.txt, db/skill_tree.txt)

・スクリプト定義値「Class」の仕様変更(db/const.txt, map.h, pc.*)
　-> Auriga内部定義の職業値からClass値を返すように変更
　（これにより、ガンスリンガーや忍者のClass値暫定処理が修正されます）
　-> 既存の職業値を取得する定義値「Job」を新規に追加

・スクリプト関数「getbaseclass()」追加(script.c, doc/script_ref.txt, conf/map_auriga.conf)
　-> 現在の職業Class値から前職のClass値を取得します
　-> function_jobgroup.txtでの職業グループ取得は非推奨となります

・Classを使用しているスクリプトやDBを修正 (db/item_db.txt, script/***.txt)

・3次職関連の戦闘設定を追加 (battle.*, battle_auriga.conf)
　-> new_statusup_calc : ステータス100以上のポイント計算式を変更できます
　-> third_status_max : 3次職のステータス限界値を設定できます
　-> third_baby_status_max : 養子3次職のステータス限界値を設定できます
　-> third_max_aspd : 3次職の攻撃速度の上限を設定できます

・DK/DC関連職業のキョンシーの定義追加 (mmo.h, pc.*, bcc32_make.bat, vc_make.bat, Makefile)

----------------------------------------
//0821 [2011/01/11] by popori

・歩行速度に関するバグを修正 (status.c pc.c)
　NP3228さんに感謝

・スキル「トマホーク投げ」はアイテムによる状態異常等の判定を行わないように変更 (skill.c)

・item_db.txtを少し修正 (item_db.txt)

----------------------------------------
//0820 [2011/01/10] by popori

・ホムンクルスのデータを本鯖仕様に修正 (homun_db.txt)

・カード補正効果無視のスキルはアイテムによる状態異常等の判定を行わないように変更 (skill.c)

・スキル「エンチャントデッドリーポイズン」「メルトダウン」「ポイズニングウェポン」の状態異常は物理攻撃スキルHIT時に判定を行うよう変更 (skill.c)

----------------------------------------
//0819 [2011/01/10] by popori

・オートカウンター、回避、完全回避以外はダメージが0の状況でもスキル、カード、武器による状態異常判定を行うように変更 (battle.*)
　※表記上x%の確率で回避と書いてあるスキルもダメージ回避が成功したとしても状態異常判定は行います。

・スキル「猛虎硬派山」のノックバック効果は回避判定が無い場合ダメージ0でも発動するように変更 (battle.c)

・スキル「メテオストーム」「ロードオブヴァーミリオン」「ストームガスト」以外のスキルのダメージディレイはamotion+500ではなくamotion分のみに変更 (battle.c)

・上記に伴ってスキルの状態異常ディレイをamotion分に変更 (skill.c)
　※どうやら、アイテムボーナスにのみamotion+500分のディレイが入るようです。

・移動速度、攻撃速度計算の部分を若干最適化 (status.c)

----------------------------------------
//0818 [2011/01/10] by popori

・スキル「メテオストーム」「ロードオブヴァーミリオン」「ストームガスト」以外にはamotion+500分のダメージディレイを入れるように変更 (battle.c)
　※大魔法以外にもダメージディレイがamotion分のみのスキルは存在するとは思いますが、後日。

・上記の変更に伴って3次職スキルにも状態異常ディレイを入れる (skill.c)

・pakcet_db.txtの更新 (packet_db.txt)

----------------------------------------
//0817 [2011/01/09] by popori

・一部のスキルの追加効果の際の状態異常にamotion+500のディレイを入れる (skill.c)
　※本家ではダメージを受けて表示から実際にHPが減るまでのディレイが発生するスキル全てに状態異常付与判定の際amotion+500のディレイが存在します。
　　逆にamotion+500のディレイが発生しないスキルは基本的に、ダメージ処理を行わないスキル・大魔法です。
　　また、通常攻撃にもHPが実際に減るまでのディレイにamotion+500の値を使っているので、同様にカードによる状態異常付与にもディレイを加えています。
　　今回の変更では、3次職スキルの扱いが分からないため変更していません。

・NULLを参照する可能性がある箇所を修正 (status.c)
　NP3228さんに感謝

・ホムの攻撃速度補正を少し修正 (homun.c)

・0816の条件式を少し修正 (battle.c)

・パケット情報の追記 (client_packet.txt)

----------------------------------------
//0816 [2011/01/08] by popori

・攻撃時に追加状態異常判定を行う際、ダメージが0になっても回避判定が無ければ状態異常判定を行うように変更 (battle.c)

・スキル「SM_SELFPROVOKE」を少し修正、ついでにitem_db.txtを少し修正 (skill.c item_db.txt)

・スキル「クァグマイア」BOSS無効の変更を有効に変更し、状態異常「SC_SPEEDUP1」のflagを調整 (scdata_db.txt)
　めろでぃさんに感謝

・0813のチェイスウォークの条件式を変更 (status.c)

----------------------------------------
//0815 [2011/01/08] by popori

・NPCスキル「速度強化」で使用する状態異常は本家で速度変化ポーションと同じなので、同様に変更する (skill.c status.c)

・上記の変更に沿って状態異常「SC_SPEEDUP1」の仕様を変更 (scdata_db.txt status.c)

・スキル「クァグマイア」はBOSS無効に変更 (scdata_db.txt)

・MOBの攻撃速度に関して少し修正 (status.c)

----------------------------------------
//0814 [2011/01/08] by popori

・battle_auriga.confのASPD関連の読み込み部分を修正 (battle.c)

・攻撃速度ポーションの挙動を少し修正 (status.c)

・移動速度増加アイテムの挙動を本鯖使用に修正 (scdata_db.txt)

・ItemID 662の馬牌の効果を変更し忘れたので修正 (item_db.txt)

----------------------------------------
//0813 [2011/01/07] by popori

・移動速度に関連する計算式を本家仕様に修正(リニューアル以前のもの)
　※この変更に伴って、item_db.txtの修正も若干行いました。
　　SpeedRateが使われている装備は全てvalを25に統一。
　　移動速度が変化するアイテムを追加。
　　速度変化ポーションの効果を実装。

　　ただし、各状態異常のセーブ可否等は分からないので適当に設定してあります。(scdata_db.txt)

　　3次職スキルの移動速度関連の挙動は分からなかったので、憶測で処理の箇所を変更しています。

----------------------------------------
//0812 [2011/01/06] by popori

・攻撃速度に関連する計算式を本家仕様に修正(リニューアル以前のもの)
　※攻撃速度関連に関連する計算式の処理を本家仕様に変更しました。
　　全てのユニットの攻撃速度の計算式が恐らく正しい物になっているかと思います。
　　この変更によって以下のbattle_auriga.confの仕様が変更されます。
　　monster_max_aspd
　　max_aspd
　　pk_max_aspd
　　gvg_max_aspd
　　pvp_max_aspd

　　従来の仕様はASPD上限を決めるだけのものでしたが、今回のパッチで以下の仕様に変更されます。
　　最大秒間攻撃速度
　　ms単位で決めることが出来ます。
　　デフォルトの状態は全て200です。
　　200/1000[ms] = 1/5となり、1秒間で攻撃出来る最大回数は5回=ASPD190となります。

　　また、一部の状態異常の削除を行いました。
　　SC_SPEEDPOTION3　SC_POISONPOTION
　　これらの状態異常は全てSC_SPEEDPOTION2に置き換わっています。

　　上記に伴って、item_db.txtの修正も若干行いました。
　　AspdRateが使われているものは全てAspdAddRateに変更。
　　FixAspdが使われていたものは全てbAspdAddRateに変更。
　　攻撃速度増加系のポーションの状態異常付与を若干変更。

　　3次職スキルの攻撃速度関連の挙動は分からなかったので、憶測で処理の箇所を変更しています。

----------------------------------------
//0811 [2010/12/18] by popori

・signedとunsignedの比較のwarningを修正 (booking.c map.h)
　NP3228さんに感謝

・ドキュメントの一部を更新 (client_packet.txt inter_server_packet.txt)

----------------------------------------
//0810 [2010/12/18] by popori

・パーティーブッキングシステムの実装
　※パーティーブッキングの検索機能ですが、検索の際の職業が明らかにおかしいIDをクライアント(使用したクライアントは2010-07-30)が送ってきています。
　　詳細は「それぞれ違う職業なのに、同じIDが送られてくる」
　　ex)ノービス=2 防御=2

　　とても仕様とは思えないので、クライアントのバグだと思います。
　　これに関してはサーバー側のバグではないので注意して下さい。

----------------------------------------
//0809 [2010/12/06] by popori

・スキル「インティミデイト」の計算式を修正 (battle.c)

・SC_SUMMER SC_SANTAをセーブするように変更 (scdata_db.txt)

・スキル「スティールコイン」の獲得Zenyの計算式を本家仕様に修正 (pc.c)

・スキル「*****ストリップ」の効果時間計算式を本家仕様に修正 (skill_cast_db.txt skill.c)

・スキル「武器精錬」の成功確率計算式を本家仕様に修正 (status.c skill.c)

・スキル「ストリップウェポン」「ストリップシールド」「ストリップアーマー」「ストリップヘルム」の成功率計算式を間違えていたので再度修正 (skill.c)

・アイテムボーナスによって歩行速度が変化する際、change_speedフラグをセットするように修正 (status.c)
　pneumaさんに感謝

----------------------------------------
//0808 [2010/12/06] by popori

・0806の状態異常に関する修正の続き (skill.c status.c)
　「石化」「凍結」「スタン」「沈黙」
  「毒」「出血」「睡眠」「暗黒」「呪い」
  「混乱」「猛毒」「誘惑」
   上記状態異常に関連するスキルごとの基本確率を本家仕様に修正
　※全てリニューアル以前のものです。
　　3次職スキルはノータッチ。

・スキル「レックスディビーナ」の沈黙付与基本時間を間違えていたので修正 (skill_cast_db.txt)

・SC_SANTA SC_SUMMER SC_WEDDING時のパケットのプロセスを本家仕様に修正 (status.c)

・スキル「ストリップウェポン」「ストリップシールド」「ストリップアーマー」「ストリップヘルム」の修正 (skill.c)
 ->使用者と対象者でDEX差がマイナスになった場合0に補正していた部分を削除
 　めろでぃさんに感謝
 ->成功確率計算式を本家仕様に修正

・スキル「フルストリップ」の成功確率計算式を本家仕様に修正 (skill.c)

・スキル「スティールコイン」の成功確率計算式を本家仕様に修正 (pc.c)

・スキル「タロットカード」の各効果の確率を本家仕様に修正 (skill.c)

----------------------------------------
//0807 [2010/12/04] by popori

・0806の状態異常に関する修正の続き (skill_cast_db.txt skill.c status.c)
 ->石化の持続時間計算式を修正
 ->凍結の持続時間計算式を修正
 ->スタンの持続時間計算式を修正
 ->沈黙の持続時間計算式を修正
 ->毒の持続時間計算式を修正
 ->出血の持続時間計算式を修正
 ->睡眠の持続時間計算式を修正
 ->暗黒の持続時間計算式を修正
 ->呪いの持続時間計算式を修正
 ->混乱の持続時間計算式を修正
 ->猛毒の持続時間計算式を修正
 ->各スキルごとの上記状態異常の基本時間を本家仕様に修正
 ※全てリニューアル以前のものです。
 　3次職スキルはノータッチ。

・0806の0x7e1に関する修正を再度修正 (clif.c client_packet.txt)
　ARIAさんに感謝

・0802のアイスウォールの修正を更に修正 (skill.c)
　めろでぃさんに感謝

----------------------------------------
//0806 [2010/12/01] by popori

・一部状態異常の計算式を本家仕様に変更 (status.c)
 ->石化の発生確率計算式を修正
 ->凍結の発生確率計算式を修正
 ->スタンの発生確率計算式を修正
 ->沈黙ンの発生確率計算式を修正
 ->毒の発生確率計算式を修正
 ->出血の発生確率計算式を修正
 ->睡眠の発生確率計算式を修正
 ->暗黒の発生確率計算式を修正
 ->呪いの発生確率計算式を修正
 ->混乱の発生確率計算式を修正
 ->猛毒の発生確率計算式を修正

 ※これらの状態異常持続時間も本家と処理が大分違うので、後日修正します。
 　なお、これらの計算式修正はリニューアル以前のものです。

・スキル「ストームガスト」の凍結確率を修正 (skill.c)

・一部定数の定義名が分かりづらかったので変更する (pc.* status.*)

・reloaditemdbを行った際read_petdb()を呼び出すように変更 (atcommand.c)
　cleaqさんに感謝

・スキルレベルを上げた際スキルがパッシブスキルに変わってしまうのを修正 (clif.c)
　NP3228さんに感謝

・一部のパケット区切りを修正 (clif.c client_packet.txt)

・clif_skillinfo()をstaticで隠蔽 (clif.*)

・スキル「ストリップヘルム」の対モンスター効果をINT40％減少に変更 (status.c)
　めろでぃさんに感謝

・エンジェラス時クライアントが終了出来ないのを修正 (pc.c)
　ARIAさんに感謝

・スキル「エンチャントデッドリーポイズン」の攻撃力上昇分を修正 (battle.c)
　めろでぃさんに感謝

・2010-11-30aRagexeREの解析結果を基にパケット情報の追記 (packet_db.txt client_packet.txt)
　※パケット長の追記を行っていますが、現状読み込ませる必要が無いと考え、MAX_PACKET_DBの拡張は行っていません。

----------------------------------------
//0805 [2010/11/23] by Blaze

・武器種の定義値を変更(map.h, pc.c, status.c, battle.c)
　-> ガトリングガンとショットガンの定義値を入れ替え
　-> 両手杖の武器種を新規追加

・上記の武器種変更によるDB修正(job_db1.txt, size_fix.txt, item_db.txt, skill_require_db.txt)

・DB仕様変更によるdoc修正 (db_ref.txt)

----------------------------------------
//0804 [2010/11/16] by Blaze

・モロクNPC追加 (npc_town_morocc.txt)
　-> 運命のカラスクエスト実装

・運命のカラスクエスト関連のNPC修正(npc_town_prontera.txt)

・運命のカラスクエスト関連のwarpを修正 (npc_warp_fild.txt)

----------------------------------------
//0803 [2010/11/16] by Blaze

・モスコビアNPC追加 (npc_town_moscovia.txt)
　-> 泣き虫のミハイル、ババヤガの魔術クエスト実装

・モスコビアクエスト関連のwarpを修正 (npc_warp_dun.txt)

----------------------------------------
//0802 [2010/11/12] by popori

・0801のコンパイル警告を修正 (map.h)
　NP3228さんに感謝

・アイスウォール設置上のセルに対してスキルユニットを設置出来ないように変更 (skill.c)
　めろでぃさんに感謝

・ガンバンテインの削除対象スキルを追加 (skill.c)

・0801の水場チェックにホムと傭兵が抜けていたので追加 (skill.c)

・2010-11-09aRagexeREの解析結果を追加 (packet_db.txt client_packet.txt)

----------------------------------------
//0801 [2010/11/12] by popori

・map_session_dataのメンバの一部を構造化する
　(atcommand.c battle.c clif.c guild.c map.h party.c pc.c script.c skill.c status.c trade.c unit.c vending.c)

・スキルポイント割り振り時に0x10fを送信するのはPACKETVERが12以下の時にのみにする。 (pc.c)
　※調査してみたところ、古い時期(少なくとも新スキルウインドウ実装以前)からスキルポイント割り振り時に0x10fを送信しない模様。
　　とりあえず暫定でPACKETVER12以下のみ送信するよう変更しました。(正確な日付の特定が難しい・・・)
　　多少の通信量削減にも繋がると思います。

・スキルユニットの使用IDを本家に合わせる (skill.* skill_unit_db.txt)

・SC_ANGELUSにOPT2_ANGELUSをセットするよう変更 (status.c)

・skill_db.txtのinfの項目をテーブルを用意し、そちらを使うように変更 (skill.* battle.c clif.c mob.c pet.c status.c unit.c)
　※inf2もやろうかと思いましたが、少しゴチャゴチャしていたので今回は変更無し

・スキル「フロストノヴァ」「雷撃砕」「氷柱落し」をスキルユニット設置型に変更する (skill.c skill_unit_db.txt)

・スキルユニット設置型のスキルの処理を変更 (skill.c skill_unit_db.txt)
　※layoutとrangeの変更が主です。ゴスペルのみflagを変更し、効果が重複しないようにしました。
　　3次職スキルは詳細不明なのでノータッチ。

・スキル「ランドプロテクター」の仕様を本家仕様に修正する (skill.c)
 ->水場セルにランドプロテクターのセルが重なっていた場合、そのセルは水場として機能させないように
 ->ランドプロテクターの効果適用外のスキルにトラップ(トーキーボックス、3次職トラップ除く)、イービルランド、ヘルモードの杖を追加
 ->ランドプロテクターの効果をスキルユニットの削除、スキルユニットの生成の妨害へ効果変更
 　めろでぃさんに感謝

・その他細かい修正 (clif.c skill.c)

----------------------------------------
//0800 [2010/11/02] by popori

・0799の続き (status.c)
 ->OPT2_BLOODINGをセットするのはSC_SIGNUMCRUCISではなくSC_BLEEDに変更
 ->SC_SANTA中はOPTION_SANTAをセットするように変更
 ->SC_SUMMER中はOPTION_SUMMERをセットするように変更
 ->SC_WEDDING中はview_classに22をセットするように変更

・キャノンボールのtypeを10→19へ変更 (item_db.txt)

・0798の処理を少し変更 (battle.c)

----------------------------------------
//0799 [2010/11/01] by popori

・オプション系列の整理と本家の仕様に近づける (atcommand.c battle.c clif.c homun.c merc.c mob.c npc.c pc.* pet.c skill.c status.* unit.c vending.c)
 ->opt1の数値を直接指定せず、enumを用いてセットするようにする OPT1_*****
 ->opt2の数値を直接指定せず、enumを用いてセットするようにする OPT2_*****
 ->opt3の数値を直接指定せず、enumを用いてセットするようにする OPT3_*****
 ->optionの数値を直接指定せず、enumを用いてセットするようにする OPTION_*****
 ->色違いドラゴン騎乗時アイコンが出ないのを修正
 ->clif_parse_ActionRequest()内の条件式で発火を除外する
 ->スキル「ホワイトインプリズン」で状態異常を付与する際OPT1_IMPRISONをセットするように変更し、一部判定はSC_WHITEIMPRISONからOPT1_IMPRISONで行うよう変更
 ->スキル「ウィンドカッター」で状態異常を付与する際OPT2_FEARをセットするように変更
 ->スキル「オーラブレイド」で状態異常を付与する際OPT3_AURABLADEをセットするように変更
 ->スキル「月明かりの下で」を演奏中OPT3_MOONをセットするように変更
 ->スキル「分身の術」で状態異常を付与する際OPT3_BUNSINをセットするように変更
 ->スキル「不死属性付与」で状態異常を付与する際OPT3_UNDEADをセットするように変更

----------------------------------------
//0798 [2010/10/30] by popori

・アイテムボーナス「bonus2 bDefEleEnemy」を使用するアイテムのscriptを追加 (item_db.txt)

・該当アイテムの効果を実装 (battle.c mob.* status.* scdata_db.txt item_db.txt)
　マヌクの豪気
　マヌクの意思
　ピンギキュラの果実ジャム
　ルシオラヴェスパのハチ蜜
　マヌクの信念
　コルヌスの涙

----------------------------------------
//0797 [2010/10/29] by popori

・課金濃縮エルニウム、オリデオコン専用精錬NPCの暫定実装 (npc_misc_refine.txt)
　pneumaさんに感謝

----------------------------------------
//0796 [2010/10/28] by popori

・script.cの装備箇所をenum化 (script.c)
　NP3228さんに感謝

・武器かどうかの判定はitemdb_isweapon()で判定するようにする (atcommand.c battle.c clif.c itemdb.* pc.c script.c skill.c status.c storage.c)
　NP3228さんに感謝

・防具かどうかの判定はitemdb_isarmor()で判定するようにする (atcommand.c battle.c clif.c itemdb.* pc.c script.c status.c storage.c)

----------------------------------------
//0795 [2010/10/27] by popori

・装備箇所のコードをenumにする (battle.c clif.c itemdb.h pc.c script.c skill.c)

・上記の変更に伴いEQP_****は廃止してLOC_****に統一する (map.h battle.c skill.c)

・clif_storageitemlist_sub()、clif_cart_itemlist()内で矢・弾丸・苦無・手裏剣・キャノンボールのチェックを行い該当した場合0x8000を送るように変更 (clif.c)

・頭装備のtypeをdb_ref.txtに従って変更する (item_db.txt)

・item_typeの9を風魔手裏剣→両手武器へ変更 (item_db.txt db_ref.txt)

・スキル「サイトブラスター」の修正 (status.c)
　めろでぃさんに感謝

・細かい修正 (clif.c itemdb.c)

・2010-10-27aRagexeREの解析結果を基にパケット長の追記 (packet_db.txt)

・スキル「石投げ」「砂まき」の最低ディレイにamotionを保証するよう変更 (skill_db2.txt)

----------------------------------------
//0794 [2010/10/26] by popori

・0792で追加したitem_typeのenumをmap.hからitemdb.hへ移動 (map.h itemdb.h)

・script.cのenumと衝突してしまうので、item_typeのenumをTYPE_****からITEMTYPE_*****へリネーム (atcommand.c battle.c clif.c itemdb.* map.h mob.c npc.c pc.c script.c skill.c status.c storage.c)
　Arocさんに感謝

・ペットの卵とペットアクセサリーの判定をtypeで行わずflagで判定するように変更する (atcommand.c clif.c item_db.* pet.c mob.c npc.c script.c)
　※従来のペットの卵とペットアクセサリーの判定方法はitem_db.txtのtype項に7、8を設定していましたが
　　今回からはpet_db.txtのEggID、AcceIDから自動で該当アイテムに対してフラグを設定するように変更しました。
　　サーバー独自のペット、ペットアクセサリーを定義している方は該当アイテムに対してitem_db.txtのtypeを7、8→4へ変更して下さい。
　　今後typeの7、typeの8はペットの卵、ペットアクセサリーとして使用しません。　

・ペットの卵とペットアクセサリーのtypeを4に変更する (item_db.txt db_ref.txt)

・item_typeの8を弓として使うように変更する (item_db.txt)

・0792以降itemdb_isequip3()が常に真を返すバグを修正 (itemdb.c)
　NP3228さん、mucheyさんに感謝

----------------------------------------
//0793 [2010/10/25] by popori

・item_typeの説明を追加 (db_ref.txt)

・item_db.txtの修正 (item_db.txt)

----------------------------------------
//0792 [2010/10/25] by popori

・client_packet.txtの更新 (client_packet.txt)

・item_typeを本家仕様に修正、ついでにitem_typeのenumを追加する (db_ref.txt item_db.txt atcommand.c battle.c clif.c itemdb.c map.h mob.c npc.c pc.c script.c skill.c status.c storage.c)
　※この変更で武器と防具のitem_typeが従来の仕様と逆になります。
　　旧)武器:4 防具:5
　　新)防具:4 武器:5
　　オリジナル装備品を実装しているサーバーは各自新しいitem_typeに沿って変更して下さい。
　　詳細はdb_ref.txtのitem_db.txtの項を参照のこと。

----------------------------------------
//0791 [2010/10/23] by Rayce

・battle.cを少しリファクタリング（battle.c）

・TXT: ジャーナルのロード時、バージョンとファイルサイズが不一致している場合は
       abort() するように0704以前の実装に巻き戻す（journal.c）
       バージョンが合わないときは、一旦古いバージョンでジャーナルデータをセーブ
       データに移してから新しいバージョンを使うこと

----------------------------------------
//0790 [2010/10/22] by popori

・0789のファルコンアサルトの変更を少し修正 (battle.c)

・スキル「S.B.R.44」の射程を無制限に変更 (skill_db.txt)
　tomoさんに感謝

・char.cのPACKETVERの分岐を少し変更 (char.c)

----------------------------------------
//0789 [2010/10/22] by popori

・client_packet.txtの更新 (client_packet.txt)

・2010-10-20aRagexeREの解析結果を基に新規追加パケット分の情報を追記 (client_packet.txt)
　※クライアントから見て受信するパケットのみ。
　　swtich tableに分岐は存在しているが0x845、0x847、0x849は処理が無いので多分未実装？
　　0x84bの処理は存在している

・packet_dbに2010-10-20aRagexeREまでのパケット長を追記 (packet_db.txt)

・ホムンクルスはシーズのダメージ補正を適用しないように変更 (battle.c)

・アイテムボーナス「bonus2 bAddCastRate」の詠唱時間削減を加算→乗算に変更 (skill.c)
　crisp.さんに感謝

・スキル「サイトブラスター」の範囲を3×3に変更 (status.c)
　めろでぃさんに感謝

・状態異常「発火」中アイテムの使用が制限されるのを修正 (clif.c)
　ばるすさんに感謝

・スキル「アースクエイク」に関する変更 (skill_db2.txt battle.c)
 ->レンジフラグを強制遠距離→遠距離に変更
 ->上記の変更に伴い、セイフティウォールを無条件で貫通するように変更

・ワープ時に無条件でディボーションを解除するよう変更 (pc.c)
　ばるすさんに感謝

・スキル「ライフストリーム」「フルリカバリー」のエフェクトをヒールと同じに変更 (skill.c)
　tomoさんに感謝

・スキル「ファルコンアサルト」使用時、付与属性に対しての減衰処理を行うよう変更 (battle.c)
　crisp.さんに感謝
　※付与属性に対してファルコンアサルトの属性が変わるわけではありません。
　　また、この変更よりallow_falconassault_elemet有効時の属性が優先されます。

----------------------------------------
//0788 [2010/10/20] by popori

・0785で追加したadelay/2分の値をディレイとして付与するオプションの削除 (battle.* battle_auriga.conf skill.c)
　※再度デフォルトでディレイ、詠唱が共に0以下のスキルは常にadelay/2分の値をディレイを付与する仕様に戻します。

・PACKETVER28以降装備ウィンドウシステムの表示がおかしくなっていたのを修正 (clif.c)

・client_packet.txtの修正 (client_packet.txt)

・Lyeseさんの情報を基に該当スキルのディレイに最低ディレイとしてamotionを付与する (skill_db2.txt)
　※該当スキル以外は最低ディレイにamotionの付与をさせないように変更しました。
　該当スキルは以下のもの
　バッシュ　ダブルストレイフィング　メマーナイト　ピアース
　メテオストーム　メテオアサルト　気功　発勁　指弾
　爆裂波動　残影　練気功　カートターミネーション
　Lyeseさんに感謝

・アイテムボーナス「bonus2 bAddSpCost」追加 (map.h skill.c pc.c status.c const.txt item_bonus.txt)
　NP3228さんに感謝
　指定スキルnの消費SPをx増加させます。
　ex)
　bonus2 bAddSpCost,5,10;	// スキルバッシュの消費SPを10増加
　bonus2 bAddSpCost,5,-10;	// スキルバッシュの消費SPを10減少

----------------------------------------
//0787 [2010/10/16] by popori

・スキル「ノピティギ」の斜め方向への移動セルを修正 (skill.c)
　ばるすさんに感謝

・VC++ 2010 Express Editionのパスを追加 (vc_make.bat)
　Cocoaさんに感謝

----------------------------------------
//0786 [2010/10/16] by popori

・0785で追加した「bonus2 bDefEleEnemy」の変数初期化し忘れでまずいことが起こっていたので修正 (status.c)

----------------------------------------
//0785 [2010/10/16] by popori

・ディレイに関する仕様変更
 ->ディレイ、詠唱が共に0以下のスキルに対してadelay/2分の値をディレイとして付与するオプションを追加 (battle.* skill.c)
　※従来の仕様ですとディレイ、詠唱が共に0以下のスキルは常にadelay/2分の値をディレイを付与していましたが、デフォルトでは無効にします。

 ->スキルディレイがamotionより小さい場合、amotionを最低値として保証していたのを、skill_db2.txtでスキルごとにスイッチさせるよう変更 (skill.* skill_db2.txt db_ref.txt)
　※0665以降は全てのスキルに対してスキルディレイがamotionより低いとamotionを最低値として設定していました。
　　これをskill_db2.txtで該当スキルのみスキルディレイがamotionより低いとamotionを最低値として保証するように変更します。
　　本来は無効化すべきスキルがあるはずなのですが、情報が集まらずほぼ全てのスキルに対して有効化しています。
　　詳しい情報をお持ちの方は情報提供お願いします。

・client_packet.txtの更新 (client_packet.txt)

・特定属性の敵からのダメージ軽減ボーナス「bonus2 bDefEleEnemy」の追加 (map.h pc.c battle.c const.txt item_bonus.txt)
　ばるすさんに感謝

・0x7faのtypeに合わせてアイテム消去時のtypeを合わせる (atcommand.c battle.c chrif.c clif.* guild.c homun.c mail.c npc.c pc.* pet.c script.c skill.c storage.c trade.c)

・スクリプト命令「announce」に機能不明の"tool"と"micc"を指定出来るように拡張 (clif.c intif.c script_ref.txt)
　※クライアントに定義されているものの、機能が不明。とりあえず指定出来るように拡張しました。

----------------------------------------
//0784 [2010/10/15] by popori

・clif_equipitemack()のPACKETVERの分岐を間違えていたので修正 (clif.c)

・凍結効果を付与する物理スキルが凍結を成功させても即座に割れてしまう問題を修正 (battle.c skill.c)
　ばるすさんに感謝

・スキル「フリージングトラップ」をBF_MISCからBF_WEAPONに変更 (skill.c skill_db.txt)

・client_packet.txtの更新 (client_packet.txt)

・現行最新のクライアントまでのパケット長を追記 (packet_db.txt)

・0769で追記したmerc_db.txtの定義はホムンクルスSの定義だったのでhomun_db.txtに移動させる (merc_db.txt homun_db.txt)

・アイテムボーナス「bDoubleAddRate」「bAddStealRate」の仕様を右手のみ適用から両手に適用に変更 (battle.c pc.c)
　kleinさんに感謝

----------------------------------------
//0783 [2010/10/11] by Rayce

・MAPサーバが複数ある場合、異なるMAPサーバに移動すると
  太陽と月と星の感情を上書き登録出来てしまうバグを修正（skill.c）
		reported by うに～くさん

・doc/client_packet.txtを一部修正
  それに伴い、一部のパケット区切りを変更（clif.c）

----------------------------------------
//0782 [2010/10/11] by Rayce

・ダメージが発生する状態異常の効果で死亡したとき、GvGマップやnorevive指定の
  マップの場合に状態異常が解除されないバグを修正（status.c）
		reported by dragontail789

	-> 死亡時に status_change_release() によって状態異常が一旦解除されると
	   sc_data[type].timer の値は-1になっているので、これを用いて既に状態異常が
	   解除済みかどうかを判定可能
	-> 対策を施したのは 出血, 猛毒, パイレックシア, ヘルインフェルノ の4つ

・アイテムボーナスの bAddCriticalDamage によってクリティカルダメージの
  増加率が100%のときに効果が適用できないバグを修正
  0485より前の計算方式に合わせる（battle.c）
		reported by ARIAさん

----------------------------------------
//0781 [2010/10/04] by Rayce

・ユーザ定義関数 callfunc 内のnextやselectにて待機中のプレイヤーに対し取引要請を
  行うと、取引終了後に再度NPCをクリックしたときに直接ユーザ定義関数が実行できて
  しまう致命的な問題を修正（clif.c, map.c, npc.c, script.c）
		reported by dragontail789さん

	-> NPCからデタッチ（npc_event_dequeue）された時点でプレイヤーが持っている
	   スタック情報を破棄する
	-> npc_pos や menu_or_input も同時に初期化することにより、一度デタッチされた
	   プレイヤーが不正にパケットを送りつけてスクリプトを再開するのを予防する

・sleep2待機中のキャラがデタッチされたにも関わらず、sleep2復帰後に再度アタッチ
  された状態で処理を継続できてしまう問題を修正（npc.c, map.h, script.＊）

	-> sleep情報をscript_state構造体から分離してscript_sleep構造体を追加　
	   charidメンバは使用しなくなったので削除
	-> map_session_data構造体に npc_sleep メンバを追加
	   sleep開始時に現在のscript_stateのsleep構造体のアドレスを保存しておく
	-> 取引要請、強制移動、ログアウト/ログインなどによって1度でもデタッチされた場合
	   npc_event_dequeue() で npc_sleep メンバをNULLで初期化しておく
	-> sleep復帰時に npc_sleep のアドレスと比較照合することで、デタッチされているか
	   どうかを判定できる
	   1度でもデタッチされていた場合、デタッチ状態のままsleep2処理は続行可能

・sleep復帰処理とawake復帰処理を run_script_awake() に集約（script.c）

・sleep2待機中にキャラがログアウトされたとき、sleep2の復帰後に st->rid を 0 に
  初期化してデタッチするように修正（script.c）
		based on eA, thx a lot!!

・sleep復帰後、RERUNLINEでない場合は即座にスクリプトを終了するように強化（script.c）
		based on eA, thx a lot!!

----------------------------------------
//0780 [2010/09/28] by Rayce

・メモリマネージャのブロックサイズを40KB→48KBに拡張（malloc.c）
	-> map_session_data構造体のsizeofが40KBを超過しており、メモリマネージャの
	   ブロックに収まりきらないという事象が発生していたため
	-> メモリの分布を簡単に計測してみると、2KB以下の小さなアロケートがほとんどで
	   比較的大きいアロケートはあまり実施されていない模様
	   実施されていたとしても、サーバ起動直後の初期化時であり、継続的な運用下では
	   頻繁にアロケートされないものと予測

----------------------------------------
//0779 [2010/09/23] by Rayce

・/common/zlib のバージョンを1.2.2から1.2.5にアップグレード

・Windows環境において、grfio_final() の後に再度 grfio_load_zlib() を
  呼び出したときに zlib.dll を再ロードできるように修正（grfio.c）

・Windows環境下において、zlibのバージョン番号は zlib.h からではなく
  zlib.dll内部で定義されている番号を zlibVersion() から取得するように修正（grfio.c）

・grfio_load_zlib() の初回呼び出し時に、現在ロードしているzlibの
  バージョンを表示するように追加（grfio.c）

----------------------------------------
//0778 [2010/09/20] by Rayce

・SQL: MySQLの wait_timeout による接続のタイムアウトを抑制するため、
       定期的に mysql_ping() を発行する仕組みを実装
		based on eA, thx a lot!!

	→ login_auriga.conf, char_auriga.conf, map_auriga.conf にそれぞれ
	   keepalive （単位は秒）の項目を追加。
	   この指定時間間隔でMySQLに対してpingを発行する。

	→ MySQL自体で設定されている wait_timeout よりも短い時間にすること。
	   デフォルトは「8時間から10分引いた」値で 28200 としている。

	→ keepalive を 0 にした場合は、定期的な mysql_ping() の発行は行わない

・SQL: NPCスクリプト関数 strescape が、Databaseの文字セットを考慮した上で
       文字列のエスケープ処理が出来るように改善（sqldbs.*, script.c）

----------------------------------------
//0777 [2010/09/20] by Rayce

・numdb_exists(), strdb_exists(), linkdb_exists() を追加（db.*）
	→ キーが含まれているかどうかだけを判定します。
	   内部処理は search と同じ。
       値にNULLが格納されている場合でも存在可否をチェックしたいときに利用します。

・db_search の代わりに db_exists を使うように変更
  （battle.c, chat.c, friend.c, mob.c, pc.c, script.c）

----------------------------------------
//0776 [2010/09/20] by Rayce

・LP64（64bit UNIX/Linux）正式対応
	→ long型は64bitになる可能性があるので、32bitのサイズが必要な場所ではlong型ではなく
	   int型を使うよう全面的に変更

	→ 8bit/16bit/32bitの明確な固定長の型が必要な場合は、int8/int16/int32型もしくは
	   uint8/uint16/uint32型を利用する

	→ "warning: cast to pointer from integer of different size" という警告が発生するので
	   数値をポインタにキャストする場合は INT2PTR マクロを利用する
	   unsignedな数値をポインタにキャストする場合は UINT2PTR マクロを利用する

	→ "warning: cast from pointer to integer of different size" という警告が発生するので
	   ポインタをint型にキャストする場合は PTR2INT マクロを利用する
	   ポインタをunsigned int型にキャストする場合は PTR2UINT マクロを利用する

----------------------------------------
//0775 [2010/09/20] by Rayce

・gccの警告 "may be used uninitialized in this function" を修正（int_party.c, battle.c）
・gccの警告 "unused variable" を修正（clif.c）

----------------------------------------
//0774 [2010/09/19] by Rayce

・NPCスクリプト実行過程で「run_func: not function and command!」が発生したとき、
  デバッグのためのヒントとして func_no と func_type を出力するように拡張（script.c）

・createaccount.php でユーザアカウントを作成するとき、入力したメールアドレスが
  無視される不具合を修正（tool/php/createaccount.php）

・TXT: アカウント情報 auth_dat をreallocで伸張するときは、memsetで初期化する（login.c）
		reported by 辻にゅまさん

----------------------------------------
//0773 [2010/09/19] by Rayce

・ポイズニングウェポンとリーディングスペルブックのアイテムIDを後々容易に
  拡張できるようにリファクタリング（clif.c, skill.c）

・clif_hpmeter() の内部処理を一括集約（clif.c）

・skill.cの全体的な細かい整形（skill.c）

・細かいリファクタリング
	battle_calc_damage()
	intif_GMmessage()
	status_change_hidden_end()

----------------------------------------
//0772 [2010/09/19] by Rayce

・clif_move() の歩行パケット送信部分を clif_move_sub() として分離して見通しを良くする（clif.c）
・clif.cの全体的な整形（clif.c）

----------------------------------------
//0771 [2010/09/19] by Rayce

・PC→MOBの敵味方判定処理の最適化（battle.c）
・アイテム関連のパケットを作成する際、ペットの卵かどうかを判定する処理を最適化（clif.c）

----------------------------------------
//0770 [2010/09/19] by Rayce

・魔法による反射ダメージのアクティブアイテムにおいて、battle_auriga.confの
  magic_reflect_autospell を参照するように修正（battle.c）

・フィアーブリーズの発動確率の計算式を一般式化（status.c）

・マーダラーボーナスの経験値倍加計算を0717以前の形に戻す（pc.c）

  ※わざわざ __BORLANDC__ で条件分岐する必要があり、しかも BIGNUMBER_DOUBLE が考慮されてないため
  ※コンパイラの最適化オプションが有効に作用していれば <<= も *= も同じアセンブラコードが
    生成されるようなので、ビットシフトに変更することによる高速化は期待できないため

----------------------------------------
//0769 [2010/09/15] by popori

・2010-09-08RagexeREの解析結果、eAからの情報を基にパケット情報の追記 (client_packet.txt)
　※未調査の物はパケットの区切りだけ解析した結果なので、何の機能のパケットなのか不明です。
　　調査出来る方は穴埋めお願い致します。

・2010-07-30aRagexeREまでのパケット長を追加 (packet_db.txt)

・クライアントに傭兵の定義が追加されていたので、merc_dbにコメントアウトで追加しておく (merc_db.txt)

・2010-07-30aRagexeREまでのクライアントに対応 (char.c bcc32_make.bat Makefile vc_make.bat *.dsp)
　※この更新に伴いPACKETVERの引き上げを行いました。
　　古いクライアントを使う際は使用するクライアントの日付に合わせてPACKETVER、packet_db.txtを編集して下さい。

・0766以降intif_GMmessage()でinterサーバーが落ちる問題を修正 (intif.c)
　ばるすさんに感謝

・eAを参考に不正対策の強化 (clif.c)

----------------------------------------
//0768 [2010/08/23] by popori

・gcc4.3.4環境下でのコンパイル警告を一部修正 (inter.c clif.* intif.* script.c)

・anti hackerのコードを更新 (clif.c)
 ->GMでないキャラが他人に赤エモを付与出来るexploitの修正

・docの修正と追加 (client_packet.txt script_ref.txt db_ref.txt)

・packet_db.txtの修正ついでにGM右クリックメニューの全ての装備を解除機能を実装 (packet_db.txt clif.c)

・item_db.txtのtypeを本家仕様に修正 (clif.c item_db.c)
　※追加されたtypeに合わせてソースを変更しただけなので、item_db.txtの変更はまだ未着手・・・。

・PCが死亡時にコインも削除するよう変更 (pc.c)

・スクリプト関数「checkwolf()」「checkwolfmount()」を追加 (script.c script_ref.txt)
　tomoさんに感謝

----------------------------------------
//0767 [2010/08/06] by popori

・0766の不要なコメントアウトが入ってしまったので削除 (clif.c)

----------------------------------------
//0766 [2010/08/05] by popori

・アナウンスパケットを本家仕様に修正 (inter.c atcommad.c clif.* intif.* script.c script_ref.txt)
　※この変更に伴いスクリプト命令「announce」「mapannounce」「areaannounce」の仕様が若干変わりましたので、script_ref.txtをお読みください。

・拳聖の融合状態のスキル攻撃によるオートスペル発動は温もりに限らず発動するよう変更 (battle.c)

・一定時間が経つと3次職スキルが使用不能になるバグを修正 (pc.c)

・item_typeの更新 (db_ref.txt)

・client_packet.txtの更新 (client_packet.txt)

----------------------------------------
//0765 [2010/07/30] by popori

・0762のpk_noshiftの仕様変更を少し修正 (clif.c)

・0764の多段HITスキルの挙動を一旦削除 (battle.c)

・clif_announce()を少し修正 (clif.c)

----------------------------------------
//0764 [2010/07/28] by popori

・HPをLongWordで送る場所はHPのチェックは不要なので削除する (char.c clif.c)

・多段HIT系スキルにHIT時、しばらくの間移動不能時間を付ける (battle.c)
　※以前eAと本家で調査をしたのですが体感数値なので、多少の誤差があると思います。

・0762のデスバウンドの反射の条件式を間違えていたので修正 (battle.c)

・デスバウンドの反射は対象者と向かい合っていなければ発動しないように修正 (battle.c)

・スクリプトでClassの参照にconst.txtの定数を用いていない箇所を修正 (npc_quest_skillget1.txt)

・Blazeさんの情報を元にリーディングスペルブックの最大スロット数を7に変更 (map.h)
　Blazeさんに感謝

----------------------------------------
//0763 [2010/07/28] by popori

・料理リストパケットの実装 (clif.* script.c packet_db.txt client_packet.txt)

・メール選択受信の未判明パケットの部分を穴埋め (clif.c)

・スキル「サイトブラスター」の効果範囲を5*5に変更 (status.c)

・死亡時には気孔を消すように変更 (pc.c)

・スキル「寸勁」の効果を修正 (skill.c)
 ->範囲を3*3から5*5に変更
 ->ノックバック距離を5に変更

----------------------------------------
//0762 [2010/07/28] by popori

・alucardさんの情報を元にシーズモードのダメージ補正を本家と同様に修正する。 (battle.* battle_auriga.conf)
　alucardさんに感謝
　※この変更により、一部battle_auriga.confの仕様が変更されます。

	gvg_short_attack_damage_rate
	gvg_long_attack_damage_rate
	-> これら2つは通常攻撃のみの倍率に適用されます。

	新規追加フラグ
	gvg_normal_attack_damage_rate
	-> このフラグはシーズモードMAPの物理攻撃スキルの倍率に適用されます。

・PKMAPも同様のシーズダメージ補正のようなので、上記の変更を加える。 (battle.* battle_auriga.conf)
　※上記と同様に、一部battle_auriga.confの仕様が変更されます。

	pk_short_attack_damage_rate
	pk_long_attack_damage_rate
	-> これら2つは通常攻撃のみの倍率に適用されます。

	新規追加フラグ
	pk_normal_attack_damage_rate
	-> このフラグはPKモードMAPの物理攻撃スキルの倍率に適用されます。

・リーディングスペルブックのスロット数計算式をマージ (map.h skill.c)
　pneumaさんに感謝

・トワイライトファーマシー３が使用不能なのを修正、フリップザコインも修正 (skill_require_db.txt)
　hanasakiさんに感謝

・0761のスパイラルピアースの移動不可効果が機能しないので、とりあえず削除 (skill.c)
　※騎士スレテンプレによると、SC_ANKLEの効果が短時間にかかってる模様？

・client_packet.txtの更新 (client_packet.txt)

・clif_initialstatus()の修正 (clif.c)

・clif_changeoption()のパケット仕様を本家に合わせる (clif.c)

・新歩行パケットは最後にintにキャストするのではなく、最初からintにキャストして受け取るように変更 (clif.c)

・battle_auriga.confのpk_noshiftの仕様を若干変更する。 (clif.c)
　※pk_noshiftが有効時はPKMAPにもPvPのランクが表示される仕様でしたが、本家の仕様と離れてしまうため変更を加えました。
　　今後はpk_noshift有効時でもPvPのランクは表示させない仕様に変更します。

・デスバウンドの反射はBOSS属性には無効に変更 (battle.c)

----------------------------------------
//0761 [2010/07/27] by Lyese

・スパイラルピアースに1秒間の移動不可能効果を追加

・ガンバンテインによるユニット削除の効果対象スキルを追加

・ソウルブレイカー、ベナムナイフに状態異常カードが乗らないように修正

----------------------------------------
//0760 [2010/07/09] by popori

・バーサーク中オートスペルが発動するように変更 (clif.c)
　ばるすさんに感謝
　※三段掌やスナッチャーを習得時にも効果が発動しますが、本家で装備品「ひよこちゃん」装備時バーサーク中でもDAが出ることから仕様ということで。

・毒薬の瓶の状態異常がディスペル、ゴスペルの全状態異常解除で解除されないので変更。ログアウト時の挙動が分からなかったので、とりあえずASPD増加系のPOTと同じように。 (scdata_db.txt)

・スキル「魔法力増幅」の効果を修正 (skill_db.txt skill_cast_db.txt status.c)
　->持続時間を30秒に変更
　->詠唱キャンセルされるように変更
　refisさんに感謝

・AutoActiveItemに関する変更 (battle.c)
　->weapon_reflect_autospell有効時、反射ダメージでも発動するように変更
　->物理スキル攻撃でも発動するように変更
　unsyuさんに感謝

・PACKETVER24以下の時のパーティーリーダー変更のメッセージをPTメンバー全員にメッセージを出すよう変更。
　パーティー情報窓を出すので、あなたがパーティーリーダーになりました。というメッセージは不要と考え削除。
　(msg_auriga.conf party.c clif.c)

----------------------------------------
//0759 [2010/07/03] by popori

・0755の修正 (clif.c)

----------------------------------------
//0758 [2010/06/26] by popori

・0757を少し修正 (clif.* party.c)

----------------------------------------
//0757 [2010/06/26] by popori

・パーティーリーダー変更の処理で各MAP鯖に通知を送っていなかった致命的な問題を修正 (int_party.c intif.c party.*)

----------------------------------------
//0756 [2010/06/22] by popori

・スティールの計算式をeAよりマージ (pc.c)

・新露天パケットの処理を少し変更 (packet_db.txt clif.c)

----------------------------------------
//0755 [2010/06/22] by popori

・判明している上位パケットで未実装な物を実装 (clif.c)

・client_packet.txtの修正 (client_packet.txt)

・スキル「ブランディッシュスピア」のディレイを修正 (ckill_cast_db.txt)
　ARIAさんに感謝

----------------------------------------
//0754 [2010/06/21] by popori

・PACKETVER23以上の歩行関連の上位パケットの仕様を出来るだけ本家に近づける (clif.c)
　※この変更は、Auriga-0119の0x86の使用する仕様を変更する形になるので、通信量が増えます。
　　しかし、0x86を使用するとMOB、PETのレベル差によるネームカラーが正常に動作しなくなるので、変更することにしました。
　　ただし、以下の状況ではレベル差によるネームカラーの違いが正常に動作しません。
【MOB、PETが一度も画面内で動かない状況】
　これは本家でも同様の仕様です。
　草や宝箱や卵に対してネームカラーの変更が効かないバグがある模様。
　一度でも画面内でMOB、PETが動けば、正常にネームカラーが変更されます。
　ただし、MOB、PETが動かない状況でも画面内でMOB、PETが沸いた場合はネームカラーが正常に変更されています。

・ペットのアクセサリーが表示されないバグを修正 (clif.c)
　tomoさんに感謝
　※他PCから見てアクセサリーを装備したペットが視界内に入った場合、そのペットが一度も動かないとアクセサリーが表示されません。
　　これは本家でも同様の現象を確認したので、仕様です。

・client_packet.txtの修正 (client_packet.txt)

----------------------------------------
//0753 [2010/06/15] by Cocoa

・txt-converterが正常にコンバート出来ない不具合を修正
	（char-converter.c inter-converter.c login-converter.c）
	※Auriga-0697SnapShotより古いAurigaでの動作は保障しません。

----------------------------------------
//0752 [2010/06/14] by popori

・0751を少し変更 (clif.c)

・client_packet.txtの更新 (client_packet.txt)

----------------------------------------
//0751 [2010/06/14] by popori

・上位歩行パケットを実装しているペットに対しては、髪型を0、髪色を7に、ホムに対しては髪型を0、髪色を8に送るように変更 (clif.c)

----------------------------------------
//0750 [2010/06/14] by popori

・0x7f7 0x7f8 0x7f9は常にレベルを送るように変更 (clif.c)

----------------------------------------
//0749 [2010/06/14] by popori

・PACKETVER23より獲得経験値表示パケットの実装 (clif.* pc.* homun.c merc.c mob.c npc.c party.c script.c skill.c)

・獲得経験値をデフォルトで有効に変更 (battle_auriga.conf battle.c)

・PETの発言やMOBの名前等が化けるのを修正 (clif.c)
　tomoさんに感謝

----------------------------------------
//0748 [2010/06/12] by popori

・装備破損時のメッセージを追加 (clif.* pc.c)

・client_packet.txtの更新 (client_packet.txt)

・既存のパケットで不明な部分を若干穴埋め (clif.c)

・PACKETVER12よりパーティーメンバーアイテム獲得メッセージパケットの実装 (clif.* party.c)

・パーティーメンバーのアイテム獲得メッセージをデフォルトで有効に変更 (battle_auriga.conf battle.c)

・太陽と月と星の奇跡は死亡時解除されないよう変更 (scdata_db.txt)
　ARIAさんに感謝

・ソースの整理 (clif.c party.*)

・PACKETVER25より、パーティーリーダー変更完了パケットの実装 (clif.* party.c)

----------------------------------------
//0747 [2010/06/11] by popori

・0744の修正以降ペットの移動速度が見かけ上異常になっていたのを修正(clif.c)
　tomoさんに感謝

----------------------------------------
//0746 [2010/06/10] by popori

・リネームしたペットの卵に対して「愛されている」と冠詞が付いていなかったのを修正 (clif.c)
　tomoさんに感謝

・ソースの整理 (clif.c)

----------------------------------------
//0745 [2010/06/09] by popori

・ホムのリネームに関する処理を本家仕様に変更 (clif.c)
　tomoさんに感謝

----------------------------------------
//0744 [2010/06/09] by popori

・PACKETVER23より他PCの武器が表示されないバグを修正 (clif.c)
　tomoさんに感謝

・0x7f7、x7f8、0x7f9をPC及びPC型MOB、ペットに限らず通常MOB、ペット、NPC、ホム、傭兵にも適用させる (clif.c)

・client_packet.txtの更新 (client_packet.txt)

・パーティー設定変更を微修正 (clif.c packet_db.txt)

・PACKETVER26よりHPメーター送信の上位パケットを実装 (clif.c)

・スキル「ボウリングバッシュ」「寸勁」のディレイを0に変更 (skill_cast_db.txt)

・PACKETVER20より、倉庫の武器と防具の項が入れ替わって表示されてしまうのを修正 (clif.c)
　※いつからタブ付き倉庫になったのか不明なので、とりあえずPACKETVER20からにしました。

----------------------------------------
//0743 [2010/06/08] by Cocoa

・カクテル・竜の吐息（大）とフベルゲルミルの酒（大）の効果が逆になっている不具合修正 (status.h)

----------------------------------------
//0742 [2010/06/07] by Cocoa

・ギルド未所属のプレイヤーが砦のガーディアンに攻撃するとサーバークラッシュする不具合修正 (battle.c)

----------------------------------------
//0741 [2010/05/30] by popori

・PACKETVERを23未満でコンパイルすると警告が発生するのを修正 (clif.c)

・client_packet.txtの更新 (client_packet.txt)

----------------------------------------
//0740 [2010/05/29] by popori

・現行最新のクライアントに対応に伴いPACKETVERの引き上げ (char.c *.dsp Makefile vc_make.bat bcc32_make.bat)

・0738の修正 (clif.c)

・vc_make.batのコンパイルメッセージを追加 (vc_make.bat)

----------------------------------------
//0739 [2010/05/28] by popori

・0738の変更漏れを修正 (atcommand.c clif.c)

・0733のtypoの修正 (atcommand.c clif.c)

----------------------------------------
//0738 [2010/05/28] by popori

・0x1c3の上位パケット0x40cに対応、0x10eの上位パケット0x7e1対応に伴いPACKETVERを更新 (mmo.h clif.c vending.c skill.c Makefile vc_make.bat bcc32_make.bat *.dsp)

・PACKETVER23より歩行関連の上位パケット(0x7f7 0x7f8 0x7f9)に対応 (clif.c)

・ダイヤモンド交換クエストのアイテムIDが間違っているのを修正 (npc_quest_diamond.txt)
　tomoさんに感謝

----------------------------------------
//0737 [2010/05/24] by popori

・0736以降コンパイルエラーが出ていたのを修正 (clif.c)
　Azuriteさんに感謝

・緑ポーションの効果を変更 (item_db.txt)
　Philip Morrisさんに感謝

・mob_db.txtの更新 (mob_db.txt)
　huge-cgiさん、編集者の方々に感謝

----------------------------------------
//0736 [2010/05/22] by popori

・スキル「ディボーション」献身元がディフェンダーを使用している際
　献身対象者のディフェンダーがレベル1で固定されているのを、献身元のディフェンダーのレベルと合わせるように変更 (status.c)
　tomoさんに感謝

・スキル「ソウルブレイカー」の物理ダメージが0の時、魔法ダメージが計算されないバグの修正をマージ (battle.c)
　ＡＥＧＩＳさん、Salvaさんに感謝

・スキル「鋭敏な嗅覚」で発生するサーバークラッシュの修正をマージ (skill.c)
　maruさんに感謝

・本家にて変更された、精錬費用改訂の部分の変更をマージ (npc_misc_refine.txt)
　tomoさんに感謝

・0x97のパケット構造更新に伴いPACKETVERを更新 (Makefile vc_make.bat bcc32_make.bat *.dsp clif.c vending.c)
　from OpenKoreProject

・スキル「イムポシティオマヌス」の最低攻撃力加算の式がおかしかったのを修正 (battle.c)

----------------------------------------
//0735 [2010/05/16] by Cocoa

・0732以降、砦以外のマップでシーズモードの時、通常モンスターに攻撃するとクラッシュする不具合を修正
	（battle.c）

----------------------------------------
//0734 [2010/05/13] by popori

・スクリプト命令「showevent」をNPCの名前を指定出来る様に拡張 (script.c script_ref.txt)

・PACKETVER21より、スクリプト命令「musiceffect」「areamusiceffect」を追加 (clif.* script.c script_ref.txt)
　※クライアントのBGMフォルダにあるmp3ファイルを演奏させます。
　　name(ファイル名)の指定には.mp3を省いたものを指定して下さい。
　　例) musiceffect "120"; // クライアントのBGMフォルダにある120.mp3を演奏させる

----------------------------------------
//0733 [2010/05/12] by popori

・2010-04-06日のクライアントまで対応 (clif.c vending.* *.dsp packet_db.txt vc_make.bat bcc32_make.bat Makefile client_packet.txt)
　PACKETVERを23まで引き上げましたので、使用する日付に合うPACKETVER、packet_db.txtに修正して下さい。
　※歩行関連の上位パケット実装は保留中です。
　　追々対応するので、もう少々お待ち下さい。

・0x804のパケットの仕様が現状不明なので、警告抑制のために関数のみ追加しておく (clif.c packet_db.txt)

・0721以降@コマンド「hotkeyset」が正常に動作しなかったのを修正 (atcommand.c clif.c)
　Cocoaさんに感謝

----------------------------------------
//0732 [2010/05/10] by Cocoa

・0731以降バイオプラントに攻撃できなかった不具合修正
	以下想定している動作です。
	・バイオプラント、スフィアーマインに関しては常に敵扱いで攻撃可能
	・エンペリウムとガーディアンはマップフラグ「gvg」があり、敵砦の場合のみ攻撃可能
		→　自分のギルド、同盟ギルドが所有する砦の場合攻撃不可能
		→　正規ギルド承認をとってない場合はギルドなしと同じ処理
		→　ギルドがなくてもガーディアンは攻撃可能、エンペはmiss処理
	※攻撃可能　：攻撃してダメージが出せる。
	　攻撃不可能：攻撃自体できない、スキル詠唱などは可能
	　miss　　　：攻撃できるがダメージはmiss

----------------------------------------
//0731 [2010/05/07] by Cocoa

・自砦のモンスター（エンペリウムなど）をダメージ0でも殴れてしまうのを修正（battle.c）

----------------------------------------
//0730 [2010/05/06] by Cocoa

・通常料理と課金料理の上昇ステータスが異なっていても、
　通常料理の効果が消去されていた不具合を修正（status.*, const.txt）

----------------------------------------
//0729 [2010/05/04] by Cocoa

・以下アイテムの効果「bAtk」を「bBaseAtk」に修正（item_db.txt）
	アトロスカード
	ダークナイトグローブ
	グロリアスタブレット

----------------------------------------
//0728 [2010/04/08] by Cocoa

・ガトリングフィーバーのATK補正を修正（status.c）

・ガトリングフィーバーの追加ダメージを削除（battle.c）

・達人の斧、盗賊の指輪の効果修正（item_db.txt）

----------------------------------------
//0727 [2010/04/08] by popori

・packet_db.txtの整理 (packet_db.txt)

・client_packet.txtの更新 (client_packet.txt)

・自砦及び同盟ギルドのガーディアン、守護石、バリケードにスキル攻撃が通ってしまうのを修正 (battle.c)
　ばるすさんに感謝

・SI_***の保管 (status.h)

・item_db.txtの更新 (item_db.txt)
　huge cgiさん、多くのDB編集者の方々に感謝

----------------------------------------
//0726 [2010/03/27] by Blaze

・0724の再修正
	-> 魔王モロククエストNPC最適化(npc_town_morocc.txt)
	-> フィアーブリーズ修正(battle.c, status.c)
	-> エピクレシス修正(skill.c)
	-> mob_skill_db修正(db/mob_skill_db.txt)

・スキル「ジュデックス」「ソウルエクスパンション」のスプラッシュ時ダメージ表示を変更(skill.c)

・スキル「フロントサイドスライド」「バックサイドスライド」のエフェクト表示を
　ノックバック後に表示させるように変更(skill.c)

・スキル「アースストレイン」を斜め方向に使用できないように変更(skill.c)

・「エピクレシス」「ラウダラムス」「ラウダアグヌス」の
　ステータス変化が機能しなかったのを修正(skill.c, status.c)

----------------------------------------
//0725 [2010/03/26] by popori

・mob_skill_db.txtの既存MOBに関する変更はBackoutし、新規MOBのみの定義を追加する (mob_skill_db.txt)

----------------------------------------
//0724 [2010/03/26] by popori

・0722の修正漏れを修正 (status.c)
　koyoriさんに感謝

・0721の修正 (char.c)
　dragontail789さんに感謝

・0712の温もりのHIT数変更をBackout (skill_unit_db.txt skill.c)
　※温もりのHIT数は秒間10HITに統一されます。
　Heavenさんに感謝

・0681のテコンランカーボーナスに関する修正 (pc.c)
　ARIAさん、unsyuさん、koyoriさんに感謝

・斧修練の効果が片手斧しか出ていないのを修正 (status.c)
　dragontail789さんに感謝

・スキル「エピクリシス」の効果を変更 (skill.c)
 ->設置時のみリザクレションの効果を発動するように変更
 ->バーサーク中、ギア搭乗中でも効果を発動するように変更
　unsyuさんに感謝

・魔王モロククエストの相違点の修正をマージ (npc_town_morocc.txt)
　mapleさん、tomoさんに感謝

・PACKETVER19よりスクリプト命令「showevent」をサポート (clif.* script.c script_ref.txt)

・client_packet.txtの更新 (client_packet.txt)

・0718以降BCCでコンパイル出来なかったのを修正 (pc.c)

・スキル「フィアーブリーズ」のHIT数は最大5回のようなので変更 (battle.c)

・vc_make.batの仕様を若干変更 (vc_make.bat)
 ->opt1からインクルードパスを分離させる。
 ->コンパイル時にVCVER、BITTYPE、CPU最適化スイッチ、コンパイルオプションを表示させるよう変更
 ->bcc32_make.batのようにコンパイル過程が表示されるように変更

・パーティー設定変更要求に関する修正 (clif.c)

・boitataさんのブラジリス関連の一部をマージ (item_db2.txt pet_db.txt)
　boitataさんに感謝

・DB類の更新 (item_db.txt mob_skill_db.txt mob_db.txt)
　huge cgiさん、多くのDB編集者の方々に感謝

----------------------------------------
//0723 [2010/03/15] by popori

・packet_db.txtの追加と微修正 (packet_db.txt)

・char.cの修正 (char.c)
　aris999さん、 dragontail789さんに感謝

・スキル「フィアーブリーズ」で0除算が発生する可能性を修正 (battle.c)
　うに～くさんに感謝

・MAX_PACKET_DBを0x850に拡張 (clif.h)

----------------------------------------
//0722 [2010/03/12] by Blaze

・0719で追加された状態異常のタイマー判定がおかしかったのを修正(status.c)
	Thanks うに～くさん

・スクリプト命令「setdragon」を拡張(script.c, pc.*, doc/script_ref.txt)
	->パラメータで色違いドラゴンに騎乗できるように(省略可)

----------------------------------------
//0721 [2010/03/09] by popori

・RagnarokRenewalのクライアントに対応 (*.dsp Makefile vc_make.bat bcc32_make.bat msg_auriga.conf packet_db.txt char.c int_party.c inter.c mmo.h clif.* intif.*)
　このパッチに伴い以下の点が変更されました。なお、現行最新のクライアントまでは対応していないので注意して下さい。
 ->packet_db.txtにRagnarokRE用の項目を追加。
 ->Makefile vc_make.bat bcc32_make.batにNEW_006b_REオプションを追加
 ->PACKETVERの引き上げ

　※従来のサクライクライアントを使用する場合は以下の点に注意して下さい。
　packet_db.txt：以下は RagnarokREより下の部分を全て削除し、使用するクライアントの日付に合わせてpacket_db.txtを編集して下さい。
　Makefile#line21：PACKETDEF = -DPACKETVER=20 -DNEW_006b -DNEW_006b_REの部分から-DNEW_006b_REを削除して下さい。
　bcc32_make.bat#line25：set __PACKETDEF__=-DPACKETVER=20 -DNEW_006b -DNEW_006b_REの部分から-DNEW_006b_REを削除して下さい。
　vc_make.bat#line34：set __PACKETDEF__=/D "PACKETVER=20" /D "NEW_006b" /D "NEW_006b_RE"の部分から/D "NEW_006b_RE"を削除して下さい。
　各Makefile：使用するクライアントの日付に合わせてPACKETVERを編集して下さい。

　※RagnarokRenewalのクライアントを使用する方
　コンパイルオプションNEW_006b_REを有効にし(デフォルトは有効)
　使用する日付に合わせてPACKETVER、packet_db.txtの編集を行って下さい。

・gcc環境下でのコンパイル警告を修正 (battle.c skill.c)

----------------------------------------
//0720 [2010/03/07] by Blaze

・ウルフライダー中、専用スキルが使えなかった不具合修正(skill.c)

・魔道ギア搭乗中、ヒールの効果を受けないように修正(skill.c)

----------------------------------------
//0719 [2010/03/06] by Blaze

・レンジャー、メカニックスキル実装 (skill.*, battle.c)

・新状態異常実装 (status.*, pc.*, unit.c, mob.c)

・ウォーロックスキル「リーディングスペルブック」実装 (map.h, skill.*, clif.*)

・下記DBファイル更新 (db/*)
	skill_db.txt
	skill_db2.txt
	skill_cast_db.txt
	skill_require_db.txt
	skill_require_db2.txt
	skill_unit_db.txt
	scdata_db.txt
	item_arrowtype.txt

・スクリプト命令にsetgear,checkgearを追加(script.c, doc/script_ref.txt)

----------------------------------------
//0718 [2010/02/25] by popori

・ギルド無所属のキャラクターがエンペリウムを攻撃出来るバグを修正 (script.c)
　bifuminさん、Salvaさん、辻にゅまさんに感謝

・エンペリウムに対して対象指定魔法を発動した場合Missとなるように、通常攻撃がMissとなる状況下でクリックしても攻撃出来ないのを修正 (clif.c battle.c)
　※ホム、傭兵に関しては本家の挙動が不明なので保留としておきます・・・。
　bifuminさんに感謝

・スクリプト関数getiteminfo()の返り値が一部おかしいのを修正 (script.c)
　testtesさんに感謝

・グラビテーションフィールドはハイドを貫通するように (battle.c)
　かんなぎさんに感謝

・左手武器装備にAtkが見かけ上加算されていないのを修正 (clif.c status.c)
　nyanoさんに感謝

・スキル「インビジブル」の効果が発動されない問題を修正 (status.c)
　olion22さんに感謝

・拳聖の祝福スキルはスキル取得者が止めを刺した場合に適用されるよう変更 (pc.c mob.c)
　unsyuさんに感謝

・マーダラーボーナスの経験値倍加はビットシフトに変更 (pc.c)

・バーンとバジン兄弟クエストの不具合修正をマージ (npc_town_yuno.txt)
　うに～くさんに感謝

・ホムンクルススキル「S.B.R.44」の計算式修正をマージ (battle.c)
　tomoさんに感謝

・0713で追加したモバイルペットの兼ね合いでbattle_auriga.confのpet_status_supportのデフォルト値をyesに変更 (battle_auriga.conf battle.c)

----------------------------------------
//0717 [2010/02/23] by Cocoa

・アイテム使用時、無敵時間が削除されないように修正（clif.c）

----------------------------------------
//0716 [2010/01/02] by popori

・0715以降MOBの魔法攻撃を受けるとMAPサーバーがクラッシュする致命的なバグを修正 (skill.c)
　 Azuriteさん、shinogiさん、 dragontail789さんに感謝

----------------------------------------
//0715 [2009/12/30] by popori

・本家では他の罠にトーキーを重ねることが出来るようなので、0713の修正を一部巻き戻しskill_unit_db.txtで変更することにする (skill.c skill_unit_db.txt)

・かんなぎさんの指摘によりハイド状態でアースクエイクは被弾しないようにする (battle.c)
　かんなぎさん、Lyeseさんに感謝

・AthenaProject Rev.384をマージ (skill_db.txt battle.c skill.c)
 ->ハンタースキル「フリージングトラップ」をMISC→物理攻撃へ変更
 ->ATK、FLEE依存(参考：弓手テンプレ)
　nanashiさんに感謝

・AthenaProject Rev.327をマージ (status.c)
 ->スキル「テンションリラックス」の仕様が転生スキル仕様変更前のままだったのを修正　（10秒毎に12SP消費 → 発動時のみSP消費）
　sakiさんに感謝

・docのrefの一部が更新されていないので、少し更新 (db_ref.txt)

・AthenaProject Rev.258をマージ (const.txt item_bonus.txt map.h pc. status.c skill.c)
 ->アイテムボーナス「bAddEffMagic」を追加
　ico776さんに感謝

・hymiwaさんの情報を元に一部のmapflagをAuroraを参考に変更 (mapflag_pvp.txt)
　Thanks to Aurora Dev Team!

----------------------------------------
//0714 [2009/12/28] by popori

・OpenKore、eAよりパケット情報を保管 (client_packet.txt)

・サンドマンは巻き込み倍加(巻き込み数分睡眠判定)するよう変更 (skill.c)

・weapon_reflect_drainをデフォルトで有効にするよう変更 (battle_auriga.conf battle.c)

・詠唱中はNPCをクリックしても反応しないように修正 (clif.c)

・0712、0713の整理 (skill.c)

・AthenaProject Rev.257をマージ (item_bonus.txt const.txt map.h pc.c status.c skill.c)
 ->アイテムボーナス「bAddCastRate」を追加
　ico776さんに感謝

・AthenaProject Rev.565を参考に以下を変更 (skill.c)
 ->スキル及びアイテムによるキャスティング/ディレイ削減効果を乗算から加算に変更(参考：ROratorio計算機)
　nanashiさんに感謝

・0713のReadmeの名前を間違えてしまったので変更

----------------------------------------
//0713 [2009/12/21] by popori

・battle_auriga.confのfirepillar_splash_onが無効時に巻き込み効果が無くなっていたのを修正 (skill.c)

・BOSSからの攻撃の場合ハイド中に関係なく全ての攻撃が当たるよう修正 (battle.c)

・EAS_USEMAXの判定が一部おかしいので修正 (skill.c)

・battle_auriga.confのweapon_attack_autospell無効時でも融合状態であれば、温もりにオートスペルが発動するように修正 (battle.c)

・属性場の効果が、攻撃対象が属性場にいる場合各ダメージ増加になっていたのを自身が属性場にいる場合各ダメージ増加に修正 (battle.c)
　dragontail789さんに感謝

・トーキーボックスに関する修正 (skill.c)
 ->トーキーボックスはbattle_auriga.confのplayer_skill_nofootsetに関係なく重ね置き出来るように修正
 ->HPを7万に変更
　Azuriteさんに感謝

・スキル「マグナムブレイク」「サイトラッシャー」で罠がノックバックするよう修正 (battle.c skill.c)

・eAを参考に新規ペットを追加(jROモバイルペット？含む)、同時にペット「餅」の餌を緑ハーブに変更 (pet_db.txt)
　※eAのpet_db.txtからほぼそのまま持ってきただけですので、細かい数値に目を通していません。
　　詳細な数値が分かる方いらっしゃいましたら、情報お願いします。
　Thanks to eA Dev Team!

・AthenaProjectを参考にスキル「イムポシティオマヌス」の効果を修正 (battle.c)

・AthenaProject Rev.361をマージ (skill.c)
 ->MOBの使うストリップ系スキルは、PCが該当箇所の装備をしていなくても発動し、脱衣状態になるように修正(アサWiki、殴り魔法職Wiki避難所)
　nanashiさんに感謝

・アサシン系の回避率増加による移動速度の増加は速度増加と重複しないよう修正 (status.c)
　dragontail789さんに感謝

・物理スキルでの攻撃時、HP/SP一定吸収、HP/SP%吸収両方乗るように変更 (battle.c)
　unsyuさんに感謝

・AthenaProject Rev.513のファイアーピラーに関する部分を一部マージ (battle.c skill.c)
 ->ダメージ1固定のMOBには不発するように修正
 ->設置制限5個、MB・AS・SiRでノックバック、HP3500に設定(ソース無し/暫定)

----------------------------------------
//0712 [2009/12/17] by popori

・0711の微修正 (battle.c unit.c)

・温もりのHIT数の修正 (skill_unit_db.txt skill.c)
 ->本家だとHIT間隔は秒間50のようなので変更
 ->BOSS属性には通常のHIT間隔の5倍にする(デフォルトは秒間10HIT)

・0708以降スキル「プロボック」がBOSS等にも効いてしまうので、戻し (skill.c)
　ばるすさんに感謝

・パケットの一部未判明部分をeAから保管 (client_packet.txt clif.c)
　Thanks to eA Dev Team!

・PETのASPDに関する修正 (status.c)
　kuroneko-Kさん、Toshiさん、easeさんに感謝

・ハイネスヒールが不死属性相手にも適用されてしまうのを修正 (skill.c)
　unsyuさんに感謝

----------------------------------------
//0711 [2009/12/15] by Lyese

・ガンバンテインが演奏スキルに効果を及ぼすように変更(skill.c)

・ギルドスキル詠唱時にフリーキャストで歩行できる問題を修正(unit.c)

・カートターミネーションに錐の効果が発動するように変更(battle_auriga.conf)

・シールドチェインの射程を5に修正(skill_db.txt)

----------------------------------------
//0710 [2009/11/23] by Blaze

・アイテムボーナスに以下を追加(map.h, pc.*, skill.*, db/const.txt, doc/item_bonus.txt, )
	bonus3 bAddEffSkill
	-> 指定したスキル使用時に状態異常付与効果を追加します

	bonus4 bSkillAutoSpell
	bonus4 bSkillAutoSpell2
	bonus4 bSkillAutoSelfSpell
	bonus4 bSkillAutoSelfSpell2
	-> 指定したスキル使用時、追加でオートスペルが発動します

	bonus4 bAutoActiveSkill
	-> 指定したスキル使用時、アイテムが活性化します

	※詳しくはdoc/item_bonus.txtを参照

・item_db.txtを更新(thx huge-cgiさん)
	-> EP13.1で追加された装備品の効果を実装
	-> アクティブアイテムの確率・効果を本鯖仕様に修正

----------------------------------------
//0709 [2009/11/23] by popori

・アイテムボーナスの一部の仕様を変更 (battle.c)
　Toshiさんに感謝
「bWeaponComaEle」「bWeaponComaEle2」「bWeaponComaRace」「bWeaponComaRace2」においての
　種族指定で0～9の種族を指定した際BOSSも適用される仕様でしたが
　この仕様を変更し0～9の種族を指定した場合はBOSSを適用外にする仕様にします。

・0706にて追加したキャッシュアイテム関連の微修正 (skill_cast_db.txt)

・気奪に関する修正 (skill.c)
 ->PKMAPでも発動するように変更
 ->MOB相手には詠唱妨害効果を付けるように変更
 ->BOSS属性には無効に変更

----------------------------------------
//0708 [2009/11/23] by Rayce

・0706のskill.cの修正を整理（skill.c）

・アサシン転職クエストの「転職試験用見本」を倒すMAPの穴に落ちると
  nullpoエラーが発生するのを修正（script/npc/job/npc_job_12assassin.txt）

----------------------------------------
//0707 [2009/11/17] by Salva

・アイテムボーナス「bAddSkillDamageRate」は他のダメージ増幅の効果がないスキルでも
　ダメージが増加するように修正 (battle.c)
	Ｓｃｈｗａｒｚｗａｌｄさん、easeさんに感謝

・反射ダメージはスキル「リフレクトシールド」などと「オークロードカード」などの
　反射効果のあるアイテムは別々にダメージ、オートスペルの判定をするように修正 (battle.c)

・反射ダメージの最低保障ダメージ1を無くすように修正 (battle.c)
　※デスバウンド反射については詳しい仕様が不明のため、
　リフレクトシールドと同じ変数を使用するようにだけ修正しています

・反射攻撃をしたときの攻撃によるアイテム オートスペル発動確率は半分に修正 (battle.c)

・スキル「プロボック」の詠唱妨害効果はプレイヤー使用時のみに修正(skill.c)

----------------------------------------
//0706 [2009/11/14] by popori

・遠距離攻撃耐性で魔法ダメージも減らすよう修正 (battle.c)
　Lyeseさんに感謝

・eA、その他の情報を参考に以下のスキルを実装 (skill.* skill_cast_db.txt skill_db2.txt skill_db.txt)
 ->キャッシュアイテム専用スキル「パーティーブレッシング」「パーティー速度増加」「パーティーアスムプティオ」
 ->アイテム用スキル？「セルフプロボック」
 ->定義のみ追加「GM_SANDMAN」「ALL_CATCRY」「ALL_PARTYFLEE」「ALL_ANGEL_PROTECT」「ALL_DREAM_SUMMERNIGHT」

　※SM_SELFPROVOKEはアロエベラに使用する模様
　　ALL_CATCRY ALL_PARTYFLEE ALL_ANGEL_PROTECT ALL_DREAM_SUMMERNIGHTはイベント専用スキルのようです。

・温もりのskill_typeをweaponに変更しておく (skill_db.txt)

・AthenaProject Rev.556をマージ (skill.c)
　nanashiさんに感謝
　->スキル「ブラギの詩」の効果を修正(参考：雷鳥テンプレ)

・アクティブアイテムに関連するバグ修正を取り込み (pc.c script.c map.h)
　dragontail789さんに感謝

----------------------------------------
//0705 [2009/11/09] by Rayce

・可変引数を使用する際、va_list型変数に対して複数回 va_arg() 実行する場合は
  処理系によっては挙動が不定になる致命的な不具合を修正
  （db.c, malloc.c, utils.h, clif.c, map.c, party.c）
	→ 可変引数「...」が直接関数の引数にある場合、va_start(), va_end() で開き直す
	→ va_list型変数を引数として持つ関数の場合、va_copy() でコピーして使用する
	→ va_copy() が定義されていない処理系（BCC, VC等）については、memcpyで代用する

----------------------------------------
//0704 [2009/11/08] by Rayce

・TXT: メールおよびペットのセーブデータのキャッシュが正しく生成出来ていなかった
       潜在的なバグを修正（int_mail.c, int_pet.c）

・TXT: ジャーナルに関する修正（journal.c）
	→ ファイルのチェックにおいて、バージョンの不一致かサイズの不一致かがわかるように判定を分離
	→ バージョンとサイズのチェックに失敗した場合、abort() せずに処理を続行する
	→ journal_header構造体の crc32 メンバーをunsigned long型に変更
	→ JOURNAL_IDENTIFIER を 11 から 12 にアップ

・不必要な nullpo_retr() を除去（mob.c, skill.c）

----------------------------------------
//0703 [2009/11/08] by Rayce

・0697において、auriga-start から砦情報の初期化部分を削除し忘れていたので修正
・0700の属性の優先順位の処理を最適化（battle.c）
・0702において、status_change_start(), status_change_end() の引数 bl には BL_SKILL が
  含まれる場合が考慮されていないため、unit_bl2ud() の戻り値でnullpo警告が発生する可能性を修正（status.c）
・0702の clif_move() に関する処理を最適化（clif.c）

----------------------------------------
//0702 [2009/11/08] by popori

・0701の処理を改善してみる (clif.c status.c map.h)

・クァグマイアをBOSSも有効にする (scdata_db.txt)
　shobonさんに感謝

----------------------------------------
//0701 [2009/11/08] by popori

・0119以降画面内のユニットの移動速度が変化した時に、見かけ上移動速度が更新されない問題を暫定修正 (clif.c)
　※本来なら、ユニットの移動速度が変化した場合のみ追加処理をさせたいのですが
　　移動速度に関する処理が散らばっているので、暫定形式で修正しました
　yumさん、Toshiさんに感謝

・クァグマイアの移動速度低下を1/3から2/3へ修正 (status.c homun.c merc.c)
　yumさんに感謝

----------------------------------------
//0700 [2009/11/07] by popori

・0699の攻撃時の属性の優先順位の修正にてif文が抜けてしまっていたのを修正 (battle.c)

・空蝉、影分身状態をディスペル、運命のタロットカードの女教皇で解除されるよう修正 (scdata_db.txt)

・scdata_db.txtのReleasable項目に速度減少を指定出来るよう拡張。またそれに伴い不要なコードを削除する (skill.c status.c db_ref.txt)

・カートブーストが速度減少で解除されるよう修正 (scdata_db.txt)

----------------------------------------
//0699 [2009/11/06] by popori

・ハイド状態でアースクエイクを回避出来ないよう修正 (battle.c)

・0698の修正でギルドスキル「治療」を考慮していなかった点を修正 (skill.c)

・battle_auriga.confのplayer_auto_counter_typeのデフォルトを0に (battle_auriga.conf battle.c)

・攻撃時の属性の優先順位を誤っていたのを修正 (battle.c)
　shobonさんに感謝

・グランドクロスの不要な処理を削除 (battle.c)
　shobonさんに感謝

----------------------------------------
//0698 [2009/11/05] by popori

・Arocさんの指摘により、0689のpc_healの仕様変更に伴い、結婚スキル「あなたに尽くします」で
　バーサーク中の相手にSPを与えられてしまうのを修正 (skill.c)

　※0689のpc_heal()の変更にてバーサーク中でもSP回復をするよう仕様を変更致しました。
　　それに伴いスクリプト命令healでバーサーク中のキャラにもSP回復するように変更しました。
　　また、本家ではバーサーク中のレベルアップ時や宿屋でもHPが回復するようなので、後々pc_heal()の
　　HP回復制限も撤廃する予定ですが、現状は未着手です。

----------------------------------------
//0697 [2009/11/03] by Rayce

・SQLモードの場合、SEで追加された砦の情報が guild_castle テーブルに
  保存できなかった問題を修正（int_guild.c）
		reported by ponyoさん

	→ サーバ起動時の初期化時に、商業値と防衛値をデフォルトの「1」に設定する
	→ あらかじめセーブデータに砦の情報を用意する必要がなくなったので、
	   win32_start.bat および main.sql から砦情報の初期化部分を削除
	→ SQLの場合、砦情報の保存を行うときは「ON DUPLICATE KEY UPDATE」を
	   利用する（OracleのMergeクエリに相当）

・SQL: guild_castleテーブルのeconomy, defenseのデフォルト値を '1' に変更
・SQL: datetime型のフィールドのデフォルト値を '2000-01-01 00:00:00' に変更

----------------------------------------
//0696 [2009/10/27] by Rayce

・0679以降、status_calc_pc() で指定する配列のサイズが MAX_PCSKILL ではなく
  MAX_SKILL のままであったため、バッファオーバーフローが発生する致命的な問題を修正（status.c）

・性転換時の雷鳥スキルリセットにおいて、2次職/3次職のスキルがリセットされない問題を修正（char.c）

・0695の行動不能状態異常の優先順位において、SC_SLEEPは実質何もしないので
  判定処理から除外するように改善（status.c）

・GetSkillStatusChangeTable() のバッファオーバーフロー/アンダーフロー対策（skill.c）

----------------------------------------
//0695 [2009/10/22] by Cocoa

・0694の修正抜けを適用
	-> 行動不能状態異常の優先順位を実装（status.c）

----------------------------------------
//0694 [2009/10/22] by Cocoa

・item_db.txtの更新
	リリースオブウィッシュの効果実装
	大空の帽子実装
	グランペコのヘアバンド実装
	ニューカウボーイハット実装

・歴史学者(ゲオルグの呪い/建国神話)クエストの進行が止まる不具合修正（npc_town_prontera.txt）

・JobLvに関係なくアコライトに転職できた不具合を修正（npc_job_04acolyte.txt）
	JobLvなどの判定箇所未調査の為、仮修正

・プロボックのDef減少値を修正（status.c）

・アサシンテンプレより行動不能状態異常の優先順位を実装（status.c）

----------------------------------------
//0693 [2009/10/18] by Rayce

・0687以降、motd.txtを未記入にするとバッファオーバーフローが発生する致命的な問題を修正（pc.c）
	reported by magnusさん

・0691の gm_can_drop_lv の処理を最適化（clif.c, storage.c）

----------------------------------------
//0692 [2009/10/18] by Rayce

・0689の修正
	→ Mob専用スキルを不発にしない判定をskill.cにハードコーディングするのではなく
	   db/skill_db2.txt のmisfireの設定値でのみ判定するように変更（skill_db2.txt, skill.c）

	→ 右手のOTダメージが左手のダメージに加算されている間違いを修正（battle.c）

	→ アクティブタイマーの永続問題の修正を巻き戻し（pc.c）
	   変数 current_equip_name_id を参照しても良いのはitembonus内で呼び出される場合のみです！
	   pc_unequipitem() は他の場所からも呼び出されるものなので、current_equip_name_id に
	   格納されている変数の一貫性は保証できません。

・skill_upperskill(), skill_mobskill() をstaticに変更（skill.*）
・使われていない関数 skill_abraskill(), skill_cloneable() を削除（skill.*）

----------------------------------------
//0691 [2009/10/17] by popori

・0689のgm_can_drop_lvの修正を再度修正 (clif.c storage.c)
　ponyoさんに感謝

----------------------------------------
//0690 [2009/10/16] by popori

・0689のイグニッションブレイクの修正が抜けていたので追加 (skill.c)

----------------------------------------
//0689 [2009/10/16] by popori

・アクティブタイマーが永続してしまうバグを修正 (pc.c)
　うに～くさんに感謝

・ヒールのディレイが消えているのを修正 (skill_cast_db.txt)
　Cocoaさんに感謝

・オーバートラストの攻撃力増加を使用者25%、パーティーメンバーを5%に修正 (battle.c status.c)
　dragontail789さんに感謝

・gm_can_drop_lvの取引禁止、倉庫出し入れが制限出来ていなかったので追加 (clif.c storage.c)
　ponyoさん、cornusさんに感謝

・バーサーク中、月光剣等でSP回復するよう修正 (pc.c)
　hancho3さん、dreamさんに感謝

・0686のdbを修正 (skill_cast_db.txt)
　LunarPhantomさんに感謝

・AthenaProject Rev.435をマージ (skill_db.txt skill_db2.txt skill_cast_db.txt abra_db.txt battle.c skill.c status.c)
 ->NPCスキル「ガイデッドアタック」を本鯖仕様に修正(参考：アサテンプレ)
 ->→一定時間DEX150%(効果時間が不明なので1Lvにつき5秒としました)
 ->同時にソース内名称も「ガイデッドアタック」で統一
　nanashiさんに感謝

・AthenaProject Rev.432をマージ (skill_cast_db.txt skill_tree.txt battle.c skill.c)
 ->スキル「ウォールオブフォグ」を本鯖仕様に修正(参考：sage wiki)
 ->同時に、ソース内名称を「ウォールオブフォグ」に統一
　nanashiさんに感謝

・サクラメントのキャスティング減少率を修正 (skill.c)
　dragontail789さんに感謝

・イグニッションブレイクの条件式がおかしかったので警告が出ていたのを修正 (skill.c)

----------------------------------------
//0688 [2009/10/15] by Rayce

・x64のWindows環境下において、コンパイル時に「'SOCKET' から 'int' への変換です」の
  警告が発生するのを修正（socket.c）
	reported by Toshiさん

・0687以降、x64でコンパイル時に「'size_t' から 'int' に変換しました。」の
  警告が発生するのを修正（script.c）
	reported by Toshiさん

----------------------------------------
//0687 [2009/10/15] by Rayce

・conf/motd.conf が32行までしか読み込めなかった制限を撤廃（pc.c）
		reported by dragontail789さん
	→ MOTD_LINE_SIZE を使用せず、記述された全ての内容を保存するようにメモリアロケートする
	→ MOTDの送信処理を pc_send_motd() として分離

・add_str() における変数について、x64を意識してsize_t型に変更（script.c）

----------------------------------------
//0686 [2009/10/13] by popori

・マーダラーボーナスに取得経験値2倍が無かったので追加 (pc.c)

・サンクチュアリは盗作不可に変更 (skill_db2.txt)

・エンチャントデッドリーポイズンの効果をリログで切れるように修正 (scdata_db.txt)

・ストームガストが1HITしかしなくなっていたのを修正 (skill_cast_db.txt)
　LunarPhantomさん、dragontail789さんに感謝

・フロストノヴァも同時に修正 (skill_cast_db.txt)
　LunarPhantomさんに感謝

・マジスレテンプレより、スタン中は凍結しないように修正 (status.c)

・キルハイルクエストが止まるのを修正 (npc_quest_kiel.txt)
　Cocoaさんに感謝

----------------------------------------
//0685 [2009/10/12] by Rayce

・foreach系の関数は、実行したサブルーチンの戻り値を加算してint型として返すように拡張
  （db.*, clif.*, map.*, party.*）
	based on eA, thanks a lot!!

・foreach系の関数で数をカウントする部分については、戻り値だけで取得するように改善

----------------------------------------
//0684 [2009/10/09] by Rayce

・skill_castend_id() および skill_castend_pos() において、PACKETVERが15以下の場合でも
  clif_skill_cooldown() を呼び出すように簡略化（skill.c）

・3次職スキルのクールタイム判定箇所をstatic timerの部分に移動（clif.c）
・status_change_start() で、常に icon_tick を初期化するように簡素化（status.c）
・status_get_max_sp() のデフォルト値を 1 → 0 に変更（status.c）

・全体的な細かい整形（battle.c, clif.c, pc.c, skill.c, status.c）

----------------------------------------
//0683 [2009/10/09] by Rayce

・0677のグランドクロスおよびグランドダークネスのDEF無視強制解除処理タイミングを変更（battle.c）
・0677のニューマ貫通処理のリファクタリング（battle.c）

・WL_EARTHSTRAIN の発動率計算式を、漸化式から一般式に改善（skill.c）
・WL_EARTHSTRAIN の初期位置指定は dirx[], diry[] を利用して簡素化（skill.c）
・RK_IGNITIONBREAK および WL_COMET において、unit_distance() が複数回呼ばれる無駄を改善（skill.c）

・配列のサイズが中途半端になるので、MOB_ID_MAX を 2500 → 2501 に変更（mob.h）

----------------------------------------
//0682 [2009/10/09] by Rayce

・MOBが影跳びを使用するとき、サーバクラッシュする可能性を修正（skill.c）
・GC_PHANTOMMENACE の範囲攻撃処理で、状態異常情報がNULLの場合にサーバクラッシュする可能性を修正（skill.c）

・WL_EARTHSTRAIN において、PCのインベントリの検索処理でバッファオーバーフローが
  発生していた問題を修正（skill.c）

・clif_mshield() で確保するバッファサイズが小さいため、バッファオーバーフローが
  発生していた問題を修正（clif.c）

・AB_CLEMENTIA, AB_CANTO, AB_CHEAL のcase文の誤りを修正（skill.c）
・pc_readdb() において、MAX_PCSKILL の不等号が間違っているので修正（pc.c）

・RK_DRAGONBREATH の計算式を暫定変更（battle.c）
	現行の計算式では、HPとSPが攻撃ダメージに及ぼす値が常に0であるため
	また、最大SPが0のとき（スキル使用者がMOBの場合等）に0除算のエラーが発生するため

----------------------------------------
//0681 [2009/10/08] by popori

・テコンランカーボーナスにテコン全スキルLvMAXで使用可能が抜けていたので追加 (pc.c)
　dragontail789さんに感謝

・ディバインプロテクションの計算式を修正 (battke.c)
　dragontail789さんに感謝

・カイゼルで復活した時にオシリスカードの効果が発動するよう修正 (pc.c)

----------------------------------------
//0680 [2009/10/07] by popori

・db系統の更新が全て巻き戻っているので、再度変更
(skill_db.txt skill_db2.txt skill_unit_db.txt skill_cast_db.txt )
　dragontail789さん、cornusさんに感謝

・ヘルジャッジメントの範囲をLv10の時のみ27×27にする (skill_unit_db.txt)
　Blazeさんに感謝

・ドキュメントの追記 (client_packet.txt)

・0679のコンパイル警告を修正 (skill.c)

・0679以降@allskill、/allskillが正常に動作しなくなっていたのを修正 (pc.c)
　NP3228さん、dragontail789さんに感謝

・影斬りの移動効果をGvGMAPでは発動しないよう修正 (skill.c)

----------------------------------------
//0679 [2009/10/06] by Blaze

・3-1次職スキル暫定実装（一部未実装）
	 (skill.*, battle.c, status.*, unit.c, pc.*, db/produce_db.txt,
	  db/skill_db.txt, db/skill_db2.txt, db/skill_cast_db.txt,
	  db/skill_require_db.txt, db/skill_unit_db.txt, db/scdata_db.txt）

・3次職関連アイテムを一部実装
	（db/item_db.txt, db/const.txt）

・スキルIDが肥大化してきたため、ID区分を3つに分割
	（mmo.h, char.c, char-converter.c, skill.*, pc.*）

・SkillStatusChangeTableを参照するとき、GetSkillStatusChangeTable()で参照させるように統一
	-> SkillStatusChangeTableのextern宣言を撤廃
	-> skill.c外部からステータス異常を参照するとき、Tableを使用しないように修正
	（skill.*, pc.c, battle.c, status.c）

・clif_status_change()を拡張
	-> 拡張定義のvalを指定できるように
	-> デバッグコマンド「@icon」に第4パラメータを指定できるように
	（clif.*, atcommand.c, conf/help.txt）

・status_change_start()からアイコン表示時、一部状態異常で
　tickが書き換えられてタイマーが表示されてしまうのを修正
	（status.c）

・スキルの固有ディレイ（クールタイム）を暫定実装（3次職スキルのみ対応）
	-> skill_cast_db.txtにクールタイムの設定項目を追加
	（skill.c, clif.c, db/skill_cast_db.txt, db/db_ref.txt）

・スクリプトにsetdragon命令とcheckdragon()を追加
	（script.c, db/script_ref.txt）

----------------------------------------
//0678 [2009/10/05] by popori

・0677のソウルチェンジの判定文がおかしかったのを修正 (skill.c)

----------------------------------------
//0677 [2009/10/05] by popori

・スパイラルピアースを強制遠距離に (skill_db2.txt)
　Y.Minadukiさんに感謝

・イービルランドの範囲を固定で11×11に変更 (skill_unit_db.txt)
　Toshiさんに感謝

・ベノムスプラッシャーの爆発までのインターバルを変更 (skill_cast_db.txt)
　Toshiさんに感謝

・バーサーク中の相手にソウルチェンジ出来ないように修正 (skill.c)

・スパイダーウェブに関する修正 (skill_db.txt skill_unit_db.txt skill_cast_db.txt)
 ->効果時間変更
 ->範囲を1×1に変更
 ->対象指定に変更

・AthenaProject Rev.350をマージ (battle.c)
 ->MOBの「アローシャワー」「シャープシューティング」はニューマを貫通するように修正
 ->また、遠距離攻撃耐性のアイテム効果を無視するように修正
　nanashiさんに感謝

・倉庫の最大預かり数をデフォルトで600に変更 (mmo.h)

・グランドクロス、グランドダークネスの攻撃力修正、DEF無視を強制解除するよう修正 (battle.c)
　shobonさんに感謝

・魔王モロクがタイムアウトでKillされないのを修正 (npc_town_morocc.txt)
　Toshiさん、Cocoaさんに感謝

・MOB_ID_MAXを2500に拡張しておく (mob.h)

・ヘルジャッジメントの効果がアイスウォールに及ばないよう修正 (skill.c)

・ヴァンパイアリタッチはBL_CHARを用いるように修正 (skill.c)

・アンクルで拘束中のMOBはテレポート出来ないように修正 (skill.c)

----------------------------------------
//0676 [2009/09/28] by popori

・一部のクライアントがサポート出来ていなかったのでPACKETVERを分ける (clif.* skill.c Makefile bcc32_make.bat vc_make.bat *.dsp)
 ->新スキルウインドウ対応をPACKETVER15に
 ->skillstatictimerのディレイ表示サポートをPACKETVER16に
　 ※ただし今のところこのパケットを使用するのは3次スキルのみ？らしいので、パケットの実装のみ。
 ->0x1a2の拡張をPACKETVER17に
 ->バフ時間表示、ディレイタイム表示をPACKETVER18に

・packet_db.txtの追記、修正 (packet_db.txt)

・ドキュメントの追記 (client_packet.txt)

・一部のbattle_auriga.confの初期値を本鯖仕様に変更 (battle_auriga.conf battle.c)

・Cocoaさんのランドマインの待機時間の修正を再度取り込み (skill_cast_db.txt)
　Cocoaさんに感謝

・影跳びはGvG中使用不可、失敗してもSPを消費するよう修正 (skill.c)

----------------------------------------
//0675 [2009/09/24] by Rayce

・即時発動スキル（skill_db.txtのinfが4）については、対象を自分自身に強制するように修正（clif.c）
	reported by Lyeseさん

	-> 即時発動スキルを他者に使用できてしまう問題が解決されます
	-> 阿修羅とティオアプチャギは状況に応じてinfが「即時発動」から「敵」に変更される場合があるため
	   別途判定を設けてます

・anti hackerコードの追加
	merged from eA, thanks a lot!!

	-> ホムや傭兵が居ない状態でもホムスキルや傭兵スキルを使えてしまうのを防ぐ
	-> ID指定スキルは、infが0（パッシブスキル）と2（地面スキル）の場合は使用できないようにする
	-> 地面指定スキルは、infが2（地面スキル）以外の場合は使用できないようにする

----------------------------------------
//0674 [2009/09/23] by Rayce

・gcc4でコンパイル時の警告を修正
	-> dereferencing type-punned pointer will break strict-aliasing rules（socket.c, httpd.c）
	-> implicit declaration of function（login.c）

・UNIX/Linuxにおいて、gccのバージョン表記が英語以外の場合を考慮して
  バージョン番号を検出する部分を修正（Makefile）

----------------------------------------
//0673 [2009/09/23] by Rayce

・キャスティングペナルティ「casting_penalty_type」を有効化している場合、ログイン時に装備が
  外れてしまう問題を修正（pc.c）
	reported by dragontail789さん

・上記のようにunit_dataの初期化が行われていないと様々な問題を引き起こす可能性があるため
  unit_dataset() の呼び出し優先度を上げるように修正（homun.c, merc.c, mob.c, pet.c）

・battle_auriga.conf の「hide_GM_session」の説明を修正（conf/battle_auriga.conf）
	reported by ponyoさん

・script_ref.txt のgetareadropitem関数の説明が間違っていたのを修正（doc/script_ref.txt）
	reported by crisp.さん

----------------------------------------
//0672 [2009/09/23] by Rayce

・msg_auriga.conf のimportが作動しなかった問題を修正（atcommand.c）
	reported by dragontail789さん、thanks to Blazeさん

・@giveitemコマンドで、「%sを%d個貰いました。」のメッセージはコマンド使用者ではなく
  アイテムを配布されたユーザに表示されるように修正（atcommand.c）
	thanks to dragontail789さん

・atcommand_auriga.conf のsynonymコマンドにGMレベルを個別設定できるように拡張（atcommand.c）

	例）reloaditemdb: 99
	    ri1= reloaditemdb
	    ri2= reloaditemdb: 50

	@reloaditemdb のGMレベルは99に設定される
	@ri1 は従来通りのsynonym書式なので、@reloaditemdb のGMレベルを引き継いで99に設定される
	@ri2 は個別設定書式なので、GMレベルは50に設定される（@reloaditemdb は99のまま）

----------------------------------------
//0671 [2009/09/23] by Rayce

・全体的な細かい整形（battle.c, merc.c, mob.c, pc.c, skill.c, status.*）

----------------------------------------
//0670 [2009/09/23] by Rayce

・0634以降、スキル使用失敗時に失敗メッセージが表示されなくなったスキルを修正（skill.c）
	-> フロストダイバー
	-> パンボイス
	-> 魅惑のウィンク

・0634以降、クラッカーの使用失敗時にnullpoエラーが発生するのを修正（skill.c）

・攻撃時の距離判定処理を最適化（battle.c）
  calc_flag の dist メンバは不要になったので削除
・battle_skill_attack() における追加効果判定文を最適化（battle.c）

----------------------------------------
//0669 [2009/09/23] by Rayce

・bDefRatioATK系とbIgnoreDefの戦闘ダメージ計算方法を最適化（battle.c）
	-> bIgnoreDef系の判定をstep15からstep14に移動して先に計算する
	-> bIgnoreDef系のrateが100ならbIgnoreDef系が無いものとみなし、bDefRatioATK系の計算を行う

----------------------------------------
//0668 [2009/09/23] by Rayce

・status_get_max_hp() MOBのギルド情報取得において、 guild_mapname2gc() の代わりに
  guild_mapid2gc() を使うように最適化（status.c）
・歩行停止処理 unit_stop_walking() を整理（unit.c）
・凍結の滑りに関する処理から SC_BLADESTOP の判定を分離する（mob.c）

・hex_dump() で、半角スペース（0x20）は「.」に置換せずに表示するように修正（utils.c）

----------------------------------------
//0667 [2009/09/23] by Rayce

・フリップザコインのコインタイマーに関する修正（pc.c, unit.c）
	-> ログイン時、コインタイマーが初期化されてなかったのを修正
	-> ログアウト時、コインタイマーが削除されてなかったのを修正

・ログイン時、AutoActiveタイマーを初期化するように修正（pc.c）
・bAutoActiveItem系において、効果時間が32768msまでしか指定できないので、
  activeitem構造体の tick メンバをshort型からint型に変更（map.h, pc.*）

----------------------------------------
//0666 [2009/09/23] by Rayce

・pc_activeitem() の引数の flag をunsigned long型に変更（pc.h）
・活性化発動タイミングを補正するため、pc_activeitem_start() の引数に tick を追加（battle.c, pc.*）
・map_session_data構造体の activeitem_timertick メンバは不要なので撤去（map.h, pc.c, script.c）

・アクティブアイテム関連処理のリファクタリング（pc.c, script.c）

----------------------------------------
//0665 [2009/09/23] by Rayce

・スキルディレイに関する処理は全て skill_delayfix() に集約する（battle.c, skill.*, unit.c）
	-> 引数を変更し、スキルIDとスキルLvのみを渡す
	-> unit.cでの個別処理をしないようにする

・スキルディレイがamotionより小さい場合、amotionを最低値として保証する（skill.c）
	merged from eA, thanks a lot!!

----------------------------------------
//0664 [2009/09/23] by Rayce

・武器研究の命中率計算が桁落ちしていた問題を修正（battle.c）
・武器研究の命中率計算のタイミングをstep3からstep2に移動（battle.c）

・ゴスペルの敵に対する呪い/暗黒/毒効果において、確率計算にはスキルユニットではなく
  ユニット所有者のベースレベルを渡すように修正（skill.c）

・skill_castend_pos() における SI_ACTIONDELAY の発生タイミングを
  skill_castend_pos2() の呼び出し前に移動（skill.c）

----------------------------------------
//0663 [2009/09/23] by Rayce

・0630以降、ジークフリードの装備耐性の効果が無かったのを修正（status.c）
・あまり意味がないので、battle_auriga.conf の「scdef_no_difflevel」は撤廃（battle.*, status.c）
・月の安楽状態に関する判定が間違っているような気がするので修正（status.c）

----------------------------------------
//0662 [2009/09/23] by Rayce

・スキル個別の仕様切り替え機能は蛇足なので、battle_auriga.conf の「whistle_perfect_flee」は撤廃
  口笛は完全回避上昇効果が無い仕様で固定化
  （battle.*, skill.c, status.c）

・PC以外の場合においても口笛に完全回避上昇を乗せないように修正する（status.c）
・SC_WHISTLE_ 状態における回避上昇計算が SC_WHISTLE を元に行われていた問題を修正（status.c）

----------------------------------------
//0661 [2009/09/23] by Rayce

・clif_status_change() を整理（clif.c）
・@icon に第3引数を追加（atcommand.c）
	アイコンのディレイ時間を指定、省略時は0と同じ

・conf/help.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0660 [2009/09/23] by Rayce

・0645以降、トルリョチャギの吹き飛ばし効果がMOBが使用したときのみしか発動しないのを修正（skill.c）

・阿修羅覇王拳をShiftクリックで発動したとき、SPを0にする処理は battle_skill_attack() 内
  ではなく、呼び出し元の skill_castend_damage_id() で行う（battle.c, skill.c）

・ブランディッシュスピアをShiftクリックで発動したときのエフェクト発生処理方法を最適化（skill.c）

----------------------------------------
//0659 [2009/09/23] by Rayce

・ストームガストの3HIT目で弾かない処理をリファクタリング（battle.c）

・スキル個別の仕様切り替え機能は蛇足なので、battle_auriga.conf の「sg_type」は撤廃（battle.*, skill.c）
  11x11のユニットを1個生成するのではなく、3x3のユニットを81個生成する仕様に固定する

・ストームガストのスキルユニットのrangeを1に合わせる（db/skill_unit_db.txt）

----------------------------------------
//0658 [2009/09/23] by Rayce

・アースクェイクの計算式を一般式に変更（battle.c）
・アースクェイクに関する条件判定順序を入れ替え（battle.c）

・アースクェイクにおけるPCとMOBの判定処理を最適化（skill.c）
  以下の2つの関数は不要なので削除
	-> skill_area_sub_count_mob()
	-> skill_area_sub_count_pc()

・0655において、pkmap_noteleportの記述を除去抜けがあり
  コンパイルできなかった問題を修正（skill.c）

----------------------------------------
//0657 [2009/09/23] by Rayce

・pointshopは <point> に負数を指定しても値の補正をしないように0623以前の仕様に戻す（npc.c）
・pointshopは価格設定の「:」を省略できないように強化（npc.c）
・ショップのアイテムIDと価格の書式が間違っている場合、エラーを出力するように強化（npc.c）

----------------------------------------
//0656 [2009/09/23] by Rayce

・MAX_MOBSKILLは 64 だと大きすぎるので 48 に引き下げ（map.h）
・MOBが待機時のスキル使用を失敗したとき、return で終了せずに歩行処理を続行する（mob.c）
・unit_data構造体に追加された idlecount メンバをmob_data構造体に変更（map.h, mob.c）

----------------------------------------
//0655 [2009/09/23] by Rayce

・battle_auriga.conf の「pkmap_noteleport」を撤廃
  代わりに map_auriga.conf の「map_pk_noteleport」で全てのPKマップに対して
  一括でMAPフラグ noteleport を設定するようにする（battle.*, map.c）

・battle_auriga.conf の初期値を変更（battle.c）
	monster_skill_over = 10
	NULL = 0

----------------------------------------
//0654 [2009/09/23] by Rayce

・出来る限り BL_CHAR マクロを利用するように置き換え（battle.c, mob.c, skill.c）
・battle_calc_damage() におけるGvG補正処理を最適化（battle.c）
・演算子の優先順序が間違っている可能性があるので修正（npc.c）

----------------------------------------
//0653 [2009/09/22] by Rayce

・GvGで城主が交代したとき、ワープ中でブロックリストから外れたPCが砦外に退去できない
  問題に関する対処（battle.*, script.c）
	based on eA, thanks a lot!!

	-> buildin_maprespawnguildid() を書き換え
	   PC用の検索ルーチン buildin_maprespawnguildid_sub_pc() と、
	   MOB用の検索ルーチン buildin_maprespawnguildid_sub_mob() の2つに分離
	-> battle_auriga.conf に「maprespawnguildid_all_players」を追加
	   デフォルトは本鯖と同じ「no」
	   「yes」にするとワープ中のPCも砦外に退去させる

----------------------------------------
//0652 [2009/09/22] by Rayce

・battle_auriga.conf の「pvp_send_guild_xy」の判定は、clif_guild_xy() 内ではなく
  呼び出し元の guild_send_xy_timer_sub() で行うように変更（clif.c, guild.c）

・guild_castlealldataload() のリファクタリング（guild.c）

----------------------------------------
//0651 [2009/09/22] by Rayce

・砦で MobId: 1285～1288 のモンスターを呼び出すと、常にギルド所属扱いになるのを撤廃（mob.c）

・NPCスクリプトの getguardianinfo 関数で、indexに1～8以外を指定すると
  バッファオーバーフロー/アンダーフローが発生するのを修正（script.c）

----------------------------------------
//0650 [2009/09/22] by Rayce

・各砦に設定可能なガーディアンの数は、MAX_GUILDGUARDIAN ではなく直接「8」で指定する
  （mmo.h, mob.c, script.c）

	※セーブデータはガーディアンの数を「8」であることを前提として処理を行っているため、
	  MAX_GUILDGUARDIAN を「8」以外の任意の数に変更してしまうとサーバクラッシュする。
	  可変に設定できないことを明示するために、配列の数を「8」で固定化する。

・砦情報を高速に取得するために guild_mapid2gc() を追加（mmo.h, guild.*）

	※guild_mapname2gc() はMAP名を文字列比較で検索するため低速です。
	  そのため、MAP番号を用いて高速に検索を行える guild_mapid2gc() を追加しました。
	  ただし、同一MAPサーバであることが確定している場合のみ使用可能です。
	  他のMAPサーバが管理しているMAPについては検索できないので注意してください。

・NPCスクリプトの callguardian 命令で、複数体のガーディアンを呼び出すと
  最後の1体しか砦所属にならない問題を修正（script.c）
・guild_mapname2gc の引数をconstにする（guild.*）

----------------------------------------
//0649 [2009/09/22] by Rayce

・sc_startおよびsc_starte命令において、完全耐性の場合でも状態異常に掛かる問題をを修正（script.c）
・getscrate命令は status_change_rate() の結果をそのまま返すように修正（script.c）
  引数の <percentage> と戻り値を百分率から万分率に変更

・doc/script_ref.txtを修正

----------------------------------------
//0648 [2009/09/22] by Rayce

・カプラのカートサービスにおいて、職業コードが数値指定に巻き戻っていたので修正
  （script/npc/misc/npc_misc_kafra.txt）

・細かい整形（db/packet_db.txt, db/scdata_db.txt）

----------------------------------------
//0647 [2009/09/22] by Rayce

・サーバースナップショット（version.h）

----------------------------------------
//0646 [2009/08/29] by Salva

・アイスウォール等のオブジェクトに状態異常の成功判定が発生したとき
	MAPサーバーが落ちていた問題を修正 (status.c)
　	　Thanks to dragontail789さん、Cocoaさん、Blazeさん、Lyeseさん

・フルアドレナリンラッシュの記述が消えていたのを修正 (skill_cast_db.txt)
　　Thanks to dragontail789さん、Blazeさん

・ストーンカースの成功確率が誤っていたのを修正 (skill.c)
　　Thanks to dragontail789さん

・Auriga-0645で検証用のprintfが残ったままになっていたのを削除 (battle.c)

----------------------------------------
//0645 [2009/08/11] by Salva

・修練系がbSplashRangeの追加攻撃範囲のみに乗っていた問題を修正 (battle.c)
	Thanks to creaさん、NP3228さん、Toshiさん

・エストンは当たらなくても状態異常付与できるよう修正 (battle.c)

・トルリョチャギはターゲットへは状態異常を付与しないよう修正 (battle.c)

・三段掌をクローンする際、攻撃側のプリザーブ状態を判定していた問題を修正 (battle.c)
	Thanks to memoさん

・Auriga-0634でのbHPPenaltyTime、bSPPenaltyTimeの修正が不完全だったのを修正 (pc.c)
	Thanks to mitaranさん、Toshiさん

・bHPPenaltyUnrigのHP0時の仕様を本鯖を再現(pc.c)

・ストーンカーストに関する修正 (skill.c)
	使用失敗時、相手が不死でなければ「スキル使用失敗」が出なかったのを修正
	スキルレベルが6以上の場合でも失敗してもアイテムを消費したことを修正

・ネリョチャギはステータスによるスタン耐性を無視するよう修正 (skill.c)

・トルリョチャギの吹き飛ばし効果はモンスターのみに修正 (skill.c)

・bNoGemStone、ウィザードの魂、深淵の中にの効果を
	ジェムストーンの消費を1つ減らすように修正 (skill.c)

・料理作成の計算式を修正 (skill.c)
	※経験補正に関しては詳細不明のため未実装のまま
	Thanks to Toshiさん

・各料理器具の成功補正値を修正 (item_db.txt)
	Thanks to Toshiさん

・ソードガーディアンカードとボウガーディアンカードの効果が逆になっていたのを修正 (item_db.txt)
	Thanks to creaさん

----------------------------------------
//0644 [2009/08/05] by popori

・0643でパケット定義が一部重複していたのを修正 (packet_db.txt)

・インベナムでnullpoエラーが出ないように修正 (skill.c)
　NP3228さん、Salvaさんに感謝

・CocoaさんのランドマインLv5の待機時間の修正を取り込み (skill_cast_db.txt)
　Cocoaさんに感謝

・セーフティウォールの距離判定を微修正 (battle.c)

・不要になった処理を一部削除 (battle.c)

・ソースの微修正 (skill.c)

・必中攻撃を強制遠距離に (skill_db2.txt)

----------------------------------------
//0643 [2009/08/04] by popori

・ティオアプチャギをシフトクリック使用出来るように (skill.c)

・アローシャワー、フリップザコインはディレイ短縮されないように修正 (unit.c)

・packet_db.txtのクリーンアップ (packet_db.txt)

・ドキュメントの追記 (server_build.txt)

----------------------------------------
//0642 [2009/07/30] by Blaze

・bonus命令に「AutoActiveItem」を実装（pc.*,map.h,status.c,battle.c,doc/item_bonus.txt）
　	※一定時間、装備アイテムを活性状態にして追加効果を発揮させます。

・アイテムの活性状態を取得する関数「checkactiveitem()」を追加（script.c,doc/script_ref.txt)

・autospellの登録処理を改善（status.*,pc.c）
	-> card_idの内容が装備箇所indexやアイテムIDなど、一貫性がなかったのをIDに統一

・定義値登録DBを更新（db/const.txt）
	-> bonusの定義値にAutoActiveItem関係を追加
	-> 攻城戦の設定関係を削除
	※攻城戦関係の設定はscript/npc/gvg/npc_gvg_global.txtで行ってください。

・ヴァンベルクカードなどのアイテム効果を実装（db/item_db.txt）

----------------------------------------
//0641 [2009/07/29] by popori

・0640の修正漏れ (skill_cast_db.txt)
　Yggdrasilさんに感謝

・Yggdrasilさんのskill_cast_db.txtを取り込み (skill_cast_db.txt)
　Yggdrasilさんに感謝

・デスペラード、温もりで攻撃時HP/SPドレインが有効で無いのを修正 (battle.c)
　hancho3さんに感謝

・スキル「一閃」を強制遠距離扱いにする (skill_db2.txt)

----------------------------------------
//0640 [2009/07/26] by popori

・0639の修正漏れ (battle.c)

・Yggdrasilさんのskill_cast_db.txtを取り込み (skill_cast_db.txt)
　Yggdrasilさんに感謝

・ダスト、グランドドリフトはディレイ短縮されないように修正 (unit.c)
　Yggdrasilさんに感謝

・noteleportの初期値を1に変更 (battle_auriga.conf battle.c)
　yumさん、Cocoaさん、Lyeseさんに感謝

・AthenaProject Rev.568をマージ (mob.c)
 ->アンクル・蜘蛛の巣による拘束時のみMOBが強制待機(タゲ外し)するよう修正
　nanashiさんに感謝

----------------------------------------
//0639 [2009/07/25] by popori

・AthenaProject Rev.482をマージ (skill.* battle.c skill_db2.txt)
 ->各攻撃スキルの遠・近距離設定をskill_db2.txtにて指定するように変更
　nanashiさんに感謝

・battle_auriga.confのsw_def_typeをデフォルトで2に変更、calc_dist_flagを1に変更 (battle_auriga.conf)

・AthenaProject Rev.491のbSplashRangeに関する修正をマージ (battle.c)
 ->修練・カタールの追撃・%UP・状態異常・カタール研究・EDPは乗らないように修正
　nanashiさんに感謝

・0631の修正漏れ (*.dsp)

・死んだふり中の相手に運命のタロットカードの効果が出てしまうのを修正 (skill.c)

----------------------------------------
//0638 [2009/07/23] by popori

・温もり、デスペラードのダメージが反射されない問題を修正 (battle.c)

・0637のコンパイル警告の修正 (skill.c)

----------------------------------------
//0637 [2009/07/21] by Salva

・状態異常発生率計算(status_change_rate())の引数type,rateに
	0未満、また以下を渡した場合0.01%の確率を返す問題を修正(status.c)
	 Thanks to Toshiさん

・Auriga-0628でAthenaProject Rev.444からマージした記述が
	一部抜けていた問題を修正(mob.c)
	 Thanks to nanashiさん、seikaiさん

・Auriga-0634の修正で不要になった
	status_change_start_sub(),status_change_pretimer_sub()を削除(status.c,status.h)

・battle_auriga.confに関する修正
	refinery_research_lv(武器研究の精錬成功率上昇効果を発動させるか)の追加
	 (battle_auriga.conf,status.c,battle.c,battle.h)
	boss_no_element_changeの初期値をyesに変更(battle_auriga.conf,battle.c)
	 Thanks to crispさん

・エレメンタルチェンジに関する修正(skill.c)
	ターゲットがプレイヤーの場合失敗するよう修正
	成否判定を追加
	 Thanks to crispさん

・武器研究の命中率 2% × Lv 増加を追加
	Thanks to Toshiさん

----------------------------------------
//0636 [2009/07/20] by popori

・AthenaProject Rev.480のサクリファイスに関する修正をマージ (battle.c)
 ->サクリファイス中はダブルアタック・範囲攻撃が発動しないように修正
　nanashiさんに感謝

・AthenaProject Rev.507のスパイダーウェブに関する修正を一部マージ (status.c)
 ->FLEEのペナルティを-50に変更
　nanashiさんに感謝

----------------------------------------
//0635 [2009/07/20] by popori

・新クライアント対応の続き (clif.* skill.c status.*)
 ->PACKETVERが15以上の時に新ステータスパケットをサポート
 ->PACKETVERが15以上の時にスキルディレイ表示をサポート
　Thanks to eA Dev Team

・0634のコンパイル警告の修正 (skill.c)

----------------------------------------
//0634 [2009/07/20] by Salva

・0630の微修正

・Auriga-0628で抜けていたmvpitem_weight_limitの処理を追加(mob.c)
	Thanks to NP3228さん

・mvpitem_weight_limitの仕様を修正(battle_auriga.conf,mob.c)
	設定値自体は以前のまま

・bHPPenaltyTime、bSPPenaltyTimeで回復時、HPが最大HP以上になる問題を修正(pc.c)
	Thanks to mitaranさん

・bHPPenaltyUnrig、bSPPenaltyUnrigでdeath_by_unrig_penaltyがnoのときHPの最低値が1になる問題を修正(pc.c)

・Auriga-0630で追加したstatus_change_judge()を削除し、状態異常発生率のみを関数で計算し、判定は各所で行うよう修正
	(skill.c,status.c,status.h,battle.c,script.c)
	 Thanks to Arocさん

・状態異常「暗黒」の持続時間計算式を修正(status.c)

----------------------------------------
//0633 [2009/07/19] by popori

・0632の微修正 (skill.c)

・AthenaProject Rev.478をマージ (skill.c status.c)
 ->スタン、睡眠、石化、凍結後にMOBがターゲットを失うように変更
 ->それに伴い、スキル「リカバリー」も修正
　nanashiさんに感謝

----------------------------------------
//0632 [2009/07/19] by popori

・packet_db.txtの修正 (packet_db.txt)
　mitaranさんに感謝

・ギルドスキルディレイの処理の一部を0265以前の処理に巻き戻す (status.* skill.c scdata.txt)

----------------------------------------
//0631 [2009/07/19] by popori

・新クライアントに対応(clif.* script.c chrif.c pc.c packet_db.txt Makefile vc_make.bat bcc32_make.bat)
 ->PACKETVERを15に引き上げ
 ->MAX_PACKET_DBを0x500に引き上げ
 ->PACKETVERが15以上の時に新スキルウインドウをサポート
 ->2009-02-25から2009-06-17までのサクライ蔵まで対応
　Thanks to eA Dev Team
　とりあえずログインと新スキルウインドウ対応まで

・db/const.txtにmf_nojumpが無いので追加 (const.txt)

・0630のバグ修正と未使用の変数をコメントアウト (mob.c skill.c status.c)

----------------------------------------
//0630 [2009/07/19] by Salva

・HITSTOPの発生条件式を修正(pc.c,mob.c,merc.c)
	shobonさんに感謝

・阿修羅覇王拳を味方に使用した場合にSPを0にするときにプレイヤーかチェックするよう修正(battle.c)
	Toshiさん、Cocoaさんに感謝

・Auriga-0629で修正したブランディッシュスピアをシフトクリック使用したときの条件文を若干修正(skill.c)
	poporiさんに感謝

・天体の怒りのダメージ倍率を修正(battle.c)
	shobonさんに感謝

・天体の安楽状態のとき、安楽の効果を発揮する条件を修正(status.c)
	shobonさんに感謝

・bHPPenaltyTime、bHPPenaltyUnrigで死亡する問題を修正(pc.c)
	 Toshiさんに感謝

・bDefRatioATK効果がボス属性に適用されていなかった問題を修正(battle.c)
	creaさんに感謝

・ジークフリートをステータス耐性ではなく装備耐性として計算するよう修正(status.c)

・速度減少の成否判定式修正(skill.c)

・battle_confに以下2つを追加
	mob_nohitstop_rate(モンスターが攻撃を受けた時にヒットストップしない確率)
	 (battle_auriga.conf,mob.c,unit.c,battle.c,battle.h)
		apacheさん、Toshiさん、mizukiさんに感謝
	scdef_no_difflevel(状態異常の耐性としてベースレベルの差を計算しない)
	 (status.c,battle.c,battle.h)

・状態異常に関する修正
   状態異常の耐性を一つの関数で行うように修正(skill.c,status.c,status.h,battle.c,script.c)
   状態異常耐性式、状態異常時間算出式を騎士スレテンプレ、CrusaderTemplateを参考に修正(status.c)

----------------------------------------
//0629 [2009/07/05] by Salva

・ファイヤピラー、クレイモアトラップ、ブラストマインを乗算計算するか設定できるように修正(battle_auriga.conf,battle.h,battle.c,skill.c)
	Thanks to Toshiさん

・左手にbDefRatioATK効果の武器を装備しているとき、ソウルブレイカーにbDefRatioATKの効果が乗っていなかった問題を修正(battle.c)
	Thanks to 大和さん

・bDefRatioATK効果のアイテムとbIgnoreDef効果のアイテムを同時に装備しているとき
	bDefRatioATKは発動しないよう修正(battle.c)

・ディスペル、阿修羅覇王拳をシフトクリック使用ができるように修正(skill.c,battle.c)

・ブランディッシュスピアをシフトクリック使用したとき
	攻撃可能な対象が範囲内にいないときにエフェクトが出なかった問題を修正(skill.c)

・プレイヤーが使う一部の地面スキルをプレイヤーやモンスターの足元に置くのを禁止するかどうか(player_skill_nofootset)の
	初期値をyesに修正(battle_auriga.conf,battle.c)

----------------------------------------
//0628 [2009/06/28] by Salva

・ストームガストの処理を以下のAthenaからMarge
	（skill.c , battle.c , mob.c）
	Athena 428,Athena 429,Athena 444,Athena 522,Athena 581
	nanashiさん、Toshiさん、かんなぎさんに感謝

・battle_auriga.confに以下を追加
	（battle.c , mob.c , clif.c , skill.c , battle.c）
	ストームガストの挙動(sg_type)
		nanashiさんに感謝
	PvPモードでギルドメンバーの位置情報の送信する(pvp_send_guild_xy)
		Lyeseさんに感謝
	MVPアイテムを所得時、落としてしまう所持重量率(mvpitem_weight_limit)
		Toshiさんに感謝
	ロキの中でアイテム オートスペルの発動を許可する(roki_item_autospell)

・デスペラードからキャスティング1秒を削除(skill_cast_db.txt)
	Toshiさんに感謝

・ジュピロスダンジョン最深部への通行クエストのNPC設置順番を入れ替え(npc_quest_juperos.txt)
	※クエスト進行上は問題ないが未だbTigereye使用時表示上の問題あり
	mitaranさんに感謝

・アースクエイクがプレイヤーとモンスターのみを攻撃対象にするよう修正(skill.c)

・0627のReadmeを若干修正

----------------------------------------
//0627 [2009/06/24] by Salva

・ロキ内にいるときアイテム オートスペルを発動しないように修正（skill.c）
	かんなぎさんに感謝

----------------------------------------
//0626 [2009/06/22] by Blaze

・0625を一部巻き戻し（npc.c,map.h,script.c,doc/script_ref.txt）
	-> 商品アイテム構造体の配列を動的確保に戻し
	-> スクリプト命令「setshopitem,addshopitem,delshopitem」の廃止

----------------------------------------
//0625 [2009/06/22] by Blaze

・ショップNPCの行解析を変更（npc.c,map.h）
	-> 商品アイテム構造体のメモリ動的確保を廃止し、定数指定分確保するように変更
	※メンバの追加が困難なため
	-> ショップNPCの宣言時、値段を省略できるように変更

・ショップNPCの書式を変更（script/npc/***.txt）

・スクリプト命令に以下のショップNPC操作命令を追加（script.c,doc/script_ref.txt）
	-> setshopitem : 指定したショップNPCの商品を再設定します
	-> addshopitem : 指定したショップNPCの商品を追加します
	-> delshopitem : 指定したショップNPCの指定した商品を削除します

・攻城戦の開始時間の判定不具合を修正（script/npc/gvg/npc_gvg_global.txt）
・0624のMob使用スキルDB変更で誤字があったのを修正（mob_skill_db.txt）
	（thx NP3228 さん）

----------------------------------------
//0624 [2009/06/20] by Blaze

・以下のスキルを実装（skill.*,battle.c,skill_db.txt,skill_db2.txt,skill_cast.txt）
	-> ヴァンパイアリックタッチ（ヴァンパイアギフト）
	-> マナバーン（ワイドソウルドレイン）
	-> 所持限界量増加R
	-> ヘルパワー
	-> ヘルディグニティ
	-> ライフストリーム

・以下のMobオーバースキル仕様を実装（skill.*,battle.c）
	-> 速度減少（AGI-50）
	-> マグナムブレイク（攻撃力1000%、命中補正1000%、攻撃範囲9x9セル）
	-> ユピテルサンダー（30HIT、14セルノックバック）
	※ダークサンダーはオーバースキル対象ではありません

・戦闘設定のオーバースキル判定の設定をLv11->Lv10に修正（battle_auriga.conf）
	※本家に合わせての修正です。通常のLv10効果を実現したい場合はLv11以上などに変更し、
	　mob_skill_db.txtを独自に書き換えてください

・状態異常ヘルパワーを実装（status.*,scdata_db.txt）

・Mob待機時スキルの使用判定間隔を調整（mob.c,map.h）

・カアヒの回復エフェクトを修正（battle.c）

・イービルランドのオブジェクト範囲・効果範囲を修正（skill_unit_db.txt）

・Mob使用スキルDBの最適化（mob_skill_db.txt）

・Mob使用スキルの最大登録数を40->64に引き上げ（map.h）

・mob_skill_db.txtのemotionが1桁指定の場合、正常に反映できなかった不具合を修正（mob.c）

----------------------------------------
//0623 [2009/06/20] by popori

・0620の変更を全て巻き戻し (battle.c)

----------------------------------------
//0622 [2009/06/19] by popori

・巻き戻しが不完全だったので修正 (skill.c)
　度々の連投パッチ誠に申し訳ございません

----------------------------------------
//0621 [2009/06/18] by popori

・演奏スキルのノックバック処理の修正を巻き戻し (skill.c)
　合奏スキルの挙動不明、合奏スキルのノックバックにバグがあるため
　誠に申し訳ございません

----------------------------------------
//0620 [2009/06/18] by popori

・バーサークに最終攻撃力2倍が無いのを修正 (battle.c)

・演奏スキル中ノックバックを受けると演奏スキルのみ元の座標に取り残されてしまうのを修正 (skill.c)
　Cocoaさんの報告に感謝

・0619のカイトの修正を巻き戻し (battle.c)

----------------------------------------
//0619 [2009/06/14] by popori

・ステータスポイントがmax_parameter以上になったら
　必要ステータスポイントが0に表示されるように修正 (pc.c)

・0611のバックステップのノックバック処理に関する修正を更に修正 (skill.*)

・バックステップの処理を本家仕様に修正 (skill.c)
　※モーションが出ないのは本家仕様です
　Toshiさんの報告に感謝

・カイトで魔法を反射時、自分はスキル名を叫ばないように修正 (battle.c)
　ARIAさんの報告に感謝

・ダメージ反射は絶対にお互いダメージをもらうように修正 (battle.c)

・白刃取りの構え中は動けないように修正 (unit.c)

・0611の修正で不要になった処理を削除 (battle.c)

・初期Zenyを0に変更 (char_auriga.conf)

・B4砦の執事の座標がおかしいのを修正 (npc_gvg_gefg04.txt)
　yumさんの報告に感謝

----------------------------------------
//0618 [2009/06/07] by Cocoa

・0617を若干修正

----------------------------------------
//0617 [2009/06/07] by Salva

・アースクエイク、ヘルジャッジメントに関する修正
	物理スキル扱いに(skill.c)
	ターゲットがselfでないものをselfに変更(mob_skill_db.txt)

・アースクエイクのスキル倍率と
	bonus bNoMagicDamageなど影響を受るなど、魔法のように処理されるように修正(battle.c)

・イフリートカードのオートスペルアースクエイクを自分に発動するよう修正
	(item_db.txt)

・0612のreadmeを微修正

----------------------------------------
//0616 [2009/06/07] by popori

・bInfiniteEndureに関する修正
	(pc.c、status.c)
	->bInfiniteEndureはGvGでは効果が出ないように修正
	->bInfiniteEndureの効果が付いた装備品を装備中、GvGではダメージモーションが出るように修正
	->Aegisでの検証により、bInfiniteEndureの効果が付いた装備品を装備中
	  SI_ENDUREが表示されるので、SI_ENDUREが表示されるように修正

・ヘルジャッジメントを魔法スキル扱いに
	(skill.c)

・payg_cas01の執事の座標がおかしいのを修正
	(npc_gvg_payg01.txt)

----------------------------------------
//0615 [2009/06/06] by Lyese

・HP回復力向上の計算式を修正（status.c）

	reported by mitaranさん

----------------------------------------
//0614 [2009/06/06] by popori

・アースクエイクを魔法スキル扱いに (skill.c)

・ステータスをリセットした際必要なステータスポイントが更新されない問題を修正 (pc.c)

・前回のreadmeを微修正

----------------------------------------
//0613 [2009/06/06] by popori

・0609のプロボックの成功判定修正がPC対PCしか考慮してないのでサーバークラッシュする問題を修正 (skill.c)
	hancho3 yumさんの報告に感謝

----------------------------------------
//0612 [2009/06/06] by Salva

・アイテムボーナスを1つ追加(const.txt、item_bounus.txt、map.h、pc.c、status.c)
	bMatk2Rate

・MATKの計算式を杖乗算補正とその他の乗算で別に計算するよう修正(status.c)
	Thanks to かんなぎさん

・MATK計算式の修正にともないMATKの乗算記述を修正
	MATK乗算効果のあるアイテムで乗算効果が15%以上のものを
	杖乗算補正(bMatk2Rate)とその他の乗算補正(bMatkRate)に分割
	(item_db.txt)

・アイテムボーナスbFixMatkが現状の処理を維持するように修正(status.c)

----------------------------------------
//0611 [2009/06/05] by popori

・ノックバックしない効果が付いた装備を装備中バックステップの効果が出ないのを修正 (skill.c)
	報告してくださったToshiさんに感謝

・ソニックブロー、アローバルカンはブラギの詩の効果を受けないように修正 (unit.c)

・温もりをデフォルトで新仕様の秒間10HITに修正する (skill_unit_db.txt)

・AthenaProjectを参考に温もりは、対人ではSPダメージのみに変更 (skill.c)
	ICOさんに感謝

・PKMAPではハエの羽、テレポートを使用出来ないように修正 (item_db2.txt、skill.c、battle.*、battle_auriga.conf)
	battle_auriga.confで切り替え可能
	ハエの羽はitem_db2.txtのZoneの値を36に変更すれば従来の仕様になります

----------------------------------------
//0610 [2009/06/05] by Lyese

・HP自動回復の計算式を修正（status.c）

・阿修羅覇凰拳、残影の射程を修正（skill_db.txt）

----------------------------------------
//0609 [2009/06/04] by Salva

・プロボックの効果を修正し、成功判定（skill.c、status.c）

・ヒルトバインディングのATK上昇をコメントアウト（status.c）

・口笛、イドゥンの林檎、夕陽のアサシンクロス、ハミング、私を忘れないで…
　サービスフォーユー、幸運のキスの計算式を修正（skill.c、status.c）

・口笛で完全回避が上昇しないように変更（battle.*、skill.c、status.c、battle_auriga.conf）
	battle_auriga.confで切り替え可能

・ランドプロテクター、ボルケーノ、デリュージ、バイオレントゲイルの効果時間を修正（skill_cast_db.txt）

----------------------------------------
//0608 [2009/06/02] by Blaze

・名も無き島クエストの追加・修正（npc_quest_nameless.txt）
	-> 大神官クエストの一部NPCの座標を修正
	-> Z団クエスト、隠された秘宝クエストNPC実装

・ローグ転職試験NPCで出現するモンスターを変更（npc_job_17rogue.txt）

・ローグ転職試験に関連するモンスターデータを更新（mob_db.txt）

・クエストアイテムの移動制御データを更新（item_db2.txt）

・mapflag修正（mapflag.txt）

----------------------------------------
//0607 [2009/05/25] by Cocoa

・VITによるダメージ減少量を0.8から1に修正（battle.c）

・スタン、石化、凍結、睡眠状態の時はスキルダメージが発生しないように修正（battle.c）
　eAとマジスレテンプレを参照していますが、睡眠に関しては仮です。
	reported by dreamさん

・落法状態が保存されないように修正（scdata_db.txt）
	reported by hancho3さん

----------------------------------------
//0606 [2009/05/25] by Cocoa

・ローグギルドではアイテムがドロップしないように修正
	mapflag.txt

・OnTouchイベントの不具合修正
	npc.c

----------------------------------------
//0605 [2009/05/25] by Cocoa

・0603より所有者のない砦のギルドフラッグにギルド未加入のプレイヤーが話しかけると
　砦内に移動できる不具合修正（npc_gvg_global.txt）

----------------------------------------
//0604 [2009/04/19] by Cocoa

・GXの反動ダメージ修正（battle.c）

・左手にのみ武器を持っている際、右手の計算もするように修正（battle.c）

・一次上位職業の魂の前提条件修正（skill_tree.txt）

・歴史学者クエストが進行しなくなる不具合修正（npc_town_prontera.txt）
	皮袋（ID:7432）を所持していてPRT_2QUEが36の場合は
	PRT_2QUEを13に書き直せばクエストを再度進行させることが出来ます。

・アンクルスネアがノックバックしないように変更（battle.*、skill.c、battle_auriga.conf）
	battle_auriga.confで切り替え可能

----------------------------------------
//0603 [2009/04/11] by Blaze

・攻城戦スクリプトの改正
	（npc_gvg_global.txt, npc_gvg_aldeg0*.txt, npc_gvg_gefg0*.txt,
		npc_gvg_payg0*.txt, npc_gvg_prtg0*.txt）
	※攻城戦の開始時間/終了時間の設定はdb/const.txtから
	　script/npc/gvg/npc_gvg_global.txtに変更しました
	-> マップ単位でファイルを区分
	-> ガーディアンのHP表示実装
	-> 執事メニューのアジト放棄は廃止
	-> マスタールームに入場制限を追加
	-> ギルドスキル「永久的な発展」の効果を実装
	-> 攻城戦開始と終了時にアナウンスを表示するように修正

・新攻城戦NPC実装
	（npc_gvg_schg0*.txt, npc_gvg_arug0*.txt）

・スクリプト命令/関数に以下を追加
	（script.c）
	-> setcell : 指定したセルの種類を変更します
	-> areasetcell : setcellの範囲版
	-> callguardian : 砦モンスター召喚
	-> getguardianinfo : ガーディアン情報の取得
	-> getmobname : Classからモンスター名を取得

・砦の固有名をDBで保持し、スクリプト関数「getcastle」で取得できるように変更
	（castle_db.txt, guild.c, script.c）

・「areamonster」など、範囲指定モンスター出現でランダム出現する条件を変更
	（mob.c）
	変更前 : 始点x,yが0のときにランダム出現
	変更後 : 始点x,yと終点x,yが全て0のときにランダム出現

・guild_castle構造体にガーディアンのIDを保持するように変更
	（int_guild.c, guild.c, mmo.h, char-converter.c）

・攻城戦モンスターの特別処理をclassで判別してるのをguild_idで判別するように修正
	（mob.c）

・砦の防衛値に比例してガーディアン/エンペリウムのMaxHPが上昇するように修正
	（status.c）

・mapflagにテコンキッドスキル「ノピティギ」を制限する「nojump」を追加
	（map.h, skill.c, script.c, npc.c）

・新攻城戦マップのmapflag定義を追加
	（mapflag_gvg.txt）

・新攻城戦マップのwarp定義を追加
	（npc_warp_vs.txt）

・map_auriga.confに定義追加
	（map_auriga.conf）

・カプラ職員NPCの転送サービス選択肢を追加
	（npc_misc_kafra.txt）

・mob_db.txt更新
	（mob_db.txt）

----------------------------------------
//0602 [2009/03/28] by Blaze

・モスコビアの「クジラ島をたずねて」クエストNPC実装
	（npc_town_moscovia.txt）

・モスコビアMobの使用スキルを修正
	（mob_skill_db.txt）

・map_auriga.confにモスコビア関連NPCの定義を追加
	（map_auriga.conf）

----------------------------------------
//0601 [2009/03/26] by Cocoa

・0599のエラーを修正

----------------------------------------
//0600 [2009/03/22] by Rayce

・名声値、召喚回数のセーブ方式の変更（char.c, sql-files/Auriga-600_changetable.sql）
	MAX_MERC_TYPE を変更してもデータが正しくセーブできることを保証します
		-> TXTは、ホットキーの後ろへ移動
		-> SQLは、mercenaryテーブルへ正規化

・傭兵のステータス通知用にenumを追加（clif.c, map.h, merc.c）
	-> SP_MERC_FLEE=165
	-> SP_MERC_KILLCOUNT=189
	-> SP_MERC_FAME=190

・傭兵の種類を自由にグループ化できるように、db/merc_db.txtに ClassType 項目を追加（merc.*）
	デフォルトでは以下のように設定されています
		0: 弓傭兵、1: 槍傭兵、2: 剣傭兵
	MAX_MERC_TYPE を増やしてmerc_db.txtのClassTypeを変更することで、別の種類の
	傭兵を作成することも可能です。

・0597で追加された関数の見直し（merc.*）
	-> merc_data 構造体自体に傭兵の種類を保存しておくようにしたので、merc_get_type() は不要
	-> merc_get_fame() は使用せずに直接参照するように変更
	-> merc_get_call() は使用せずに直接参照するように変更
	-> merc_set_fame() は引数を変更（データを保存しているPCを主体にする）
	-> merc_set_call() は引数を変更（データを保存しているPCを主体にする）

・mob_dead() を少し書き換え（mob.c）

・TXT: JOURNAL_IDENTIFIER を 11 に引き上げ（journal.c）

----------------------------------------
//0599 [2009/03/19] by Cocoa

・JobGroupを追加（function_jobgroup.txt、const.txt）
	系列の職業かどうかを返します。
	ソードマン系、シーフ系、マーチャント系という判定なら
		callfunc("JobGroup", Grp_Swordman, Grp_Thief, Grp_Merchant)
	という記述になります。

・item_db.txtをJobGroupを使用した記述に変更

----------------------------------------
//0598 [2009/03/13] by Cocoa

・タナトスタワー上層部07に拡張１次職が進入できる様に変更
	npc_warp_dun.txt

・スクリプト、item_dbでClassを数値で指定しているものをconstの定数に記述を統一

----------------------------------------
//0597 [2009/03/14] by Blaze

・傭兵関連の改正その２
	（merc.*, clif.*, status.c, pc.c, mob.c, skill.c）
	-> 傭兵のステータスを通知するパケット0x2a2に対応
	-> 傭兵ステータスの通知は0x29bではなく、なるべく0x2a2を使用するように修正
	-> キルカウント実装　※キルカウントボーナスは未実装
	-> 名声値、召喚回数の計測実装
	-> 傭兵関連メッセージをmsgstringtable.txtから読み込むように修正

・名声値、召喚回数をキャラセーブデータに保存するように修正
	（char.c, mmo.h, sql-files/main.sql, sql-files/Auriga597_changetable.sql）

・傭兵関連のDBを再読込みする「@reloadmercdb」を実装
	（atcommand.c, atcommand.h, conf/atcommand_auriga.conf, conf/msg_auriga.conf, conf/help.txt）

----------------------------------------
//0596 [2009/03/12] by Rayce

・TXT: 0594で、JOURNAL_IDENTIFIER を 10 に引き上げ忘れているので修正（journal.c）

・SQL: ホムンクルスのステータス端数値をセーブ保存するように（int_homun.c, sql-files/Auriga596_changetable.sql）
・SQL: ペット、ホム、傭兵の新規作成クエリの発行に失敗したとき、不正なポインタを
       aFreeしていた問題を修正（int_pet.c, int_homun.c, int_merc.c）

----------------------------------------
//0595 [2009/03/11] by Cocoa

・db/const.txtの修正
・それに伴う一部スクリプトの修正

----------------------------------------
//0594 [2009/03/10] by Blaze

・0592のホムンクルスのステータス端数値をセーブ保存するように修正
	（int_homun.c）

・ホムンクルスのステータスを再計算するとき、端数を初期化するように修正
	（homun.c）

----------------------------------------
//0593 [2009/03/07] by Rayce

・atcommand_homlevel() から使用しなくなった変数を削除（atcommand.c）
・db/homun_db2.txt 読み込み時にアクセスバイオレーションが発生するのを修正（homun.c）
・db/homun_db2.txt の最小値と最大値が同じ値の場合、乱数計算でサーバクラッシュが発生するのを修正（homun.c）

----------------------------------------
//0592 [2009/03/07] by Blaze

・ホムンクルスのレベルアップ時と進化時のステータス上昇処理を修正
	（mmo.h, homun.c, homun.h, atcommand.c）

・ホムンクルスの成長DBを追加
	（homun_db2.txt, db_ref.txt）


　※既存のホムンクルスと比べてステータスが大きく異なる場合があります
　　新方式に合わせる場合はrecalcで再計算してください


----------------------------------------
//0591 [2009/03/03] by Cocoa

・ポーションピッチャーにディレイがなかったので追加

----------------------------------------
//0590 [2009/03/01] by Rayce

・武器ダメージ計算において、ヒット回数計算はstep12ではなくstep7で行うように修正（battle.c）
  ピアース、指弾がミスのときにヒット回数が正しくなかったのが修正されます
	reported by mapleさん

----------------------------------------
//0589 [2009/02/25] by Cocoa

・mob_db.txt　/　mob_skill_db.txtの更新

----------------------------------------
//0588 [2009/02/15] by Rayce

・SQL: 0587で追加したUNIQUEキーにおいて、varcharの判定がcase insensitiveであるため
       キーの重複が発生していた問題を修正
       char, guild, login, party テーブルの該当フィールドに BINARY オプションを付与する
       （main.sql, sql-files/Auriga587-changetable.sql）
		reported by easeさん

・SQL: 上記変更に伴い大文字/小文字判定が不要になったので、処理を簡略化する
       （char.c, int_guild.c, int_party.c, login.c）

・SQL: 0587でサポートしなかったワープポータルのメモ情報の移行をやっぱり
       サポートできるように追加（sql-files/Auriga587-changetable.sql）

  ※今回はAuriga587-changetable.sqlを直接修正しています。
    既にクエリを流してしまっている人は、申し訳ありませんが手動での対応を
    お願いします。

  ※ワープポータルのメモ情報を移行できるのはMySQLのバージョンが4.1以上の
    場合のみです。
    4.0以下の方は該当箇所をコメントアウトしてください。
    また、メモの順番は保持されない可能性があります。
    順番まで厳密に移行する必要がある場合は、手動での対応をお願いします。

----------------------------------------
//0587 [2009/02/04] by Rayce

・ワープポータルのメモの順番が不定になる可能性を修正（char.c）
・不要なコメントを削除

・TXT: JOURNAL_IDENTIFIER を 09 に引き上げ（journal.c）
・SQL: memo テーブルに index フィールドを追加（sql-files/Auriga587-changetable.sql）

・SQL: テーブル定義の見直し（sql-files/main.sql）
	-> char テーブルを char_data に改名
	-> friend テーブルのカラム名を変更
	-> memo, feel_info テーブルから実質使われていない auto_increment を削除
	-> 重複する不要なINDEXの削除
	   複合インデックスの左端の部分はキーとして利用できる
	-> データの堅牢性向上のため、UNIQUEキーを張るように改善
	-> EXPLAIN の実行結果より、インデックスが利用できていないクエリに対して
	   INDEXを張るように改善
	-> global_reg_value テーブルの type はカーディナリティが低いので
	   worldreg, accountreg, globalreg テーブルにそれぞれ正規化する
	-> ipbanlist テーブルは参照されていないので削除

・SQL: 不要な ORDER BY を削除（int_guild.c）
・SQL: sql-files/drop_table.sql に IF EXISTS を付ける

  ※SQLモードについて、テーブル定義を変更しています。
    外部のアプリ等でDBを参照している方は、テーブル名・カラム名の変更に合わせて
    修正してください。
    また、INDEXはAuriga内部で使われる最低限のものだけにしています。
    DBを頻繁に参照する方は、各自適宜INDEXを張ってください。

  ※SQLモードについて、ワープポータルのメモの情報は移行されません。
    PRIMARY KEYを作り直す必要がある関係上、移行のスクリプトが極めて複雑になるため
    サポートしないことにしました。
    もしデータを移行したい方は、Auriga587-changetable.sql を実行する前に
    バックアップを取った上、手動でデータを入力し直して下さい。

  ※converter未対応です。

----------------------------------------
//0586 [2009/01/12] by Rayce

・太陽と月と星の怒りによるダメージボーナスは、基本武器ダメージ計算ではなく
  eAベースで修練ダメージ計算後に加算するようにしてみる（battle.c）
	reported by easeさん、Toshiさん

・スーパーノービスの魂状態のとき、装備可能な武器の判定を汎用的な方法に修正（pc.c）
	reported by shobonさん

----------------------------------------
//0585 [2009/01/12] by Rayce

・サーバ起動時、接続サーバのIPアドレスは1回だけ表示されるように変更
　（login.c, char.c, chrif.*, clif.*, map.c）
	-> IPアドレスに変換後の文字列ではなく、confに記述されたホスト名を
	   そのまま保持するように変更
	-> chrif_sethost(), clif_sethost() を追加

・gethostbyname() をラップした host2ip() を追加（socket.*）
・不要になった #include を削除

----------------------------------------
//0584 [2009/01/12] by Rayce

・0583以降、mapif_parse_GuildBasicInfoChange() で警告が発生していたので修正（int_guild.c）

・[SQL] 0583でコンパイルエラーが発生するのを修正（int_guild.c）
	reported by seionさん

----------------------------------------
//0583 [2009/01/10] by Rayce

・0541以降、取得不可能なギルドスキルも一覧に表示されていた問題を修正（int_guild.c）
	-> guild_calc_skilltree() を追加
	   guild_check_skill_require() を削除
	-> PCのスキルツリーと同様に、ギルドスキルについてもスキルツリーの計算を行います

・ギルドスキルのポイント割り振りに失敗したとき、以後ポイント割り振りが
  出来なくなる問題を修正（int_guild.c, clif.c, guild.*, intif.c）
	-> 失敗時にも0x10eのパケットを送りつける
	-> 0x383cのパケット長を14から15に拡張

・ギルドスキルポイントを上げるためのコマンド @guildskpoint を追加（atommand.*, int_guild.c）
	-> @guildlvup と同じくギルドマスターのみ使用可能
	-> mapif_parse_GuildBasicInfoChange() に GBI_SKILLPOINT に対する処理を追加

・clif_guild_skillinfo() のパケット定義を蔵の仕様に合わせる（clif.c）
・mapif_parse_GuildMemberInfoChange() の細かい修正（int_guild.c）
・mapif_parse_GuildAddMember() で mapif_guild_info() が2回呼び出される
　可能性を修正（int_guild.c）

----------------------------------------
//0582 [2009/01/09] by Cocoa

・ローグギルドでモンスターを出現させる際、フラグをチェックするように変更（npc_job_17rogue.txt）

----------------------------------------
//0581 [2009/01/06] by Cocoa

・ガンスリンガーのSPが一部以上だった不具合修正（job_sp_db.txt）
	reported by hancho3さん

・マーチャントクエストで判定するスキルが異なっている不具合修正（npc_quest_tutorial.txt）
	thanks to Toshiさん

・スクリプトエラーが発生する不具合修正（npc_event_newyeaar.txt）
	thanks to Toshiさん

・NPC_REBIRTHで復活したモンスターを倒してもイベントが発生しないように修正（mob.c）

----------------------------------------
//0580 [2009/01/04] by Rayce

・shopのアイテムの売り値が買い値を越える可能性がある場合、
　警告を表示するように拡張（map.c, npc.c, pc.c）

	※売り値および買い値は以下の4つの補正を受けますが、売り値の
	　最高値と買い値の最安値を計算した上で判定を行っています
		* ディスカウント
		* コンパルションディスカウント
		* オーバーチャージ
		* マーダラーボーナス

・DUPEの事故防止のため、shopの販売値は全て-1にする（script/npc/*）

	※-1の場合はitem_db.txtで設定したPriceを参照します
	　script/sample内のスクリプトについては、現状維持とします

----------------------------------------
//0579 [2009/01/04] by Rayce

・conf/login_auriga.conf の detect_multiple_login が0のとき、
  MAPサーバで二重loginを検出する際の条件判定が間違っていたのを修正（pc.c）

・areamonster命令で "this" 指定が作動していなかったのを修正
　それに伴い、monster命令の "this" 指定の仕様変更
　（atcommand.c, mob.*, script.c, skill.c）

	-> 今までは実行プレイヤーのMAPを参照していましたが、他のスクリプト命令/関数と同様に
	   NPCのMAPを優先して参照し、NPCが居ないときにプレイヤーのMAPを参照します。
	   monster命令で "this" 指定を使っている人は、挙動が変わっていないかどうか
	   確認してください。

----------------------------------------
//0578 [2008/12/19] by Cocoa

・MAX_ITEMGROUPを12に変更（map.h）
	おいしい魚や化け物のエサの回復量の異常が修正されます。

----------------------------------------
//0577 [2008/12/19] by Cocoa

・item_db2.txtを更新
	thanks to Toshiさん

・item_group_db.txt、item_db.txtを修正

・各砦内に設置されていたギルドフラッグを撤去

----------------------------------------
//0576 [2008/11/30] by Blaze

・monster出現情報のxs,ys範囲が半径指定ではなく直径になっていたのを修正
	（monster.c）

・上記修正に伴い、モンスター出現スクリプトの暫定処理を最適化
	（script/monster/***）

----------------------------------------
//0575 [2008/11/25] by Rayce

・timer.cを少し最適化（timer.c）

・0567以降、*.dspを用いてコンパイルが出来なかったのを修正
・doc/script_ref.txtを少し修正

----------------------------------------
//0574 [2008/11/23] by Blaze

・スクリプト命令「announce」に、攻城戦メッセージ機能を追加
　（clif.c, intif.c, doc/script_ref.txt）

・上記機能をGvGスクリプトに適用
　（npc_gvg_exe.txt, npc_gvg_steward.txt）

----------------------------------------
//0573 [2008/11/23] by Blaze

・プレイヤーを指定方向にノックバックさせる「pushpc」命令を追加
　（script.c, doc/script_ref.txt）

・名もなき島の「借金返済クエスト」NPC実装
　（npc_quest_nameless.txt）

----------------------------------------
//0572 [2008/11/22] by Rayce

・0570を少し修正（npc.c, script.c, unit,c）
・0571を少し修正（script.c）

----------------------------------------
//0571 [2008/11/21] by Cocoa

・プレイヤーが詠唱中かどうか判定する関数「checkcasting」を追加
	（script.c, script_ref.txt）

・定数を追加
	（const.txt）

・支援系スキルスクロールの修正
	（item_db.txt）

----------------------------------------
//0570 [2008/11/15] by Blaze

・AthenaProject Rev.499, Rev.518よりmerge
　（npc.*, map.h, unit.c, mob.c, doc/script_ref.txt）
	-> NPC接触判定にMob対応のOnTouchNPCラベルを追加
	-> モンスター出現時にOnTouchNPC判定をするように修正

・AthenaProject Rev.502, Rev.504よりmerge
　（script.c, npc_quest_kiel.txt）
	-> スクリプト命令「warp」をMob対象でも対応化
	-> 機械人形工場1FのクエストエリアにMob禁止NPCを実装

・AthenaProject Rev.500よりmerge
　（npc_town_rachel.txt）
	-> ラヘルクエストの一部NPCにOnTouchNPC実装

----------------------------------------
//0569 [2008/11/13] by Rayce

・サーバースナップショット（version.h）

・不要なファイルを削除
	db/random/*.txt
	db/mob_branch.txt
	db/mob_poring.txt
	db/mob_boss.txt

----------------------------------------
//0568 [2008/11/07] by Cocoa

・item_dbを更新（item_db.txt, item_group_db.txt）

----------------------------------------
//0567 [2008/11/04] by Rayce

・vc_make.batにVC++2008 64bitコンパイルの記述を追加
	64bitコンパイルを正式対応します
	現時点ではLLP64（Windows）のみ対応です
	LP64（UNIX/Linux）の対応は今しばらくお待ちください

・vc_make.batにVC++2008ExpressEditionの記述を追加
	thanks to poporiさん

・WindowsとUNIX/Linuxの判定は、「_WIN32」ではなく「WINDOWS」の
　#defineを参照するように統一
	-> bcc32_make.batにWINDOWSの定義を追加
	-> vc_make.batにWINDOWSの定義を追加

----------------------------------------
//0566 [2008/11/03] by Rayce

・Mobの死亡時スキル発動が正常に動作しない問題を修正（mob.c）
	reported by apacheさん

・NPC_REBIRTHの仕様を修正（map.h, mob.c, skill.c, status.*, unit.*）
	based on eA, thx a lot!!

	-> スキル発動直後にHPを回復させるのではなく、一旦 SC_REBIRTH 状態にする
	-> mob_dead() で死亡処理が完了した後、復活処理を行う（カイゼルと同じ手法）
	-> mob_rebirth() は unit_remove_map() と mob_spawn() の一部を集約
	-> リバース復活後は、再度リバースを使うことはできない
	-> リバース復活後はアイテムのドロップなし

----------------------------------------
//0565 [2008/11/03] by Rayce

・0564のランダム系モンスターの読み込みを最適化（mob.*）
	データ１件ずつに対して挿入ソートを行うのは非効率なため、一旦全てのデータを
	読み込んだ後、qsort() でMobのLvの低い順にソートするように変更

・mob_read_randommonster() で、MAX_RAND_MOB_AMOUNT であるべきはずの所が
　MAX_RAND_MOB_ENTRY になっていたのを修正（mob.c）

・ランダム系モンスターを１件しか読み込んでいないとき、mobdb_searchrandomid() で
　検索ができなかったのを修正（mob.c）

・引数の型を正しい型に修正（mob.*）
	-> mob_class_change_randam()
	-> mobdb_searchrandomid()

・guild_storage_deadlock_timer() がタイマーリストに登録されていなかったのを修正（int_storage.c）

----------------------------------------
//0564 [2008/11/03] by Blaze

・0562のランダムアイテムの処理をさらに修正（itemdb.*）
	-> ランダムアイテム構造体のメンバ名を分かりやすく変更
	-> item_random.txtの登録チェックを強化
	-> 登録最大数と乱数発生最大値の定義を追加
	-> 登録数が最大に達したとき、以降の登録が無視されていたのを修正

・ランダム系モンスターの登録と検索処理の改正（mob.*, skill.c）
	-> ランダム系モンスターを検索するmobdb_searchrandomid()関数を追加
	-> 検索失敗時にデフォルトIDを指定する定義を追加

・ランダム系モンスターを登録するdbを追加（db/mob_random.txt）
	※mob_branch.txt、mob_boss.txt、mob_poring.txtの設定は無効になります

・ランダム系モンスター種別の定義名を整理（db/const.txt）

・item_db.txtにランダム系モンスター種別の定義を反映（db/item_db.txt）

・db/addon配下のファイル読み込み時、出力結果に元ファイルの読込み数も加算されていたのを
　addonファイルだけの読込み数を出力するように修正（itemdb.c, pet.c, homun.c, merc.c）

----------------------------------------
//0563 [2008/11/01] by Blaze

・0451のemotion仕様変更によるスクリプトの修正内容がすべて誤っていたのを修正
	（script/npc/***.txt）

・0505で追加された「misceffect2」命令を廃止
	（script.c, script_ref.txt）

・emotionとmisceffect命令をプレイヤー以外でも対象できるように
　map_session_dataからblock_listで指定するように変更
	（script.c）

・誤認がないように「emotion」と「misceffect」の説明を修正
	（script_ref.txt）

・名もなき島の大神官クエストNPC実装
	（npc_quest_nameless.txt, npc_town_rachel.txt, npc_warp_town.txt）

----------------------------------------
//0562 [2008/10/29] by Rayce

・0561のランダムアイテムの処理をさらに修正（itemdb.c）
・unsignedのキャストが抜けている箇所を修正（script.c）
・script.cの細かい整形（script.c）

----------------------------------------
//0561 [2008/10/29] by Rayce

・SQL: 0473以降、敵対ギルドがある状態でギルド情報をセーブするとcharサーバが
       クラッシュする致命的なバグを修正（int_guild.c）
			reported by Toshiさん

・0577のランダムアイテムの処理を修正（itemdb.c）
	itemdb_searchrandomid()
	itemdb_read_randomitem()

----------------------------------------
//0560 [2008/10/27] by Cocoa

・0559でコンパイルが通らない不具合修正（status.c）

・ダブルストレイフィングの計算式修正（battle.c）
	reported by うに～くさん

・Def、Mdefが不の値になるように修正（status.c）

----------------------------------------
//0559 [2008/10/27] by Cocoa

・AthenaProject Rev.255を参考にプレイヤーの所持限界量の倍率を追加
	thanks to Blazeさん
	（battle_auriga.conf, battle.*, status.c）

・str1毎に追加される所持限界量の設定を追加
	（battle_auriga.conf, battle.*, status.c）

----------------------------------------
//0558 [2008/10/22] by Blaze

・指定アイテムの読書ウィンドウを表示させる「openbook」命令実装
	（script.c, clif.c, clif.h, doc/script_ref.txt）

・名も無き島クエストの読書ウィンドウ表示を実装
	（npc_quest_nameless.txt）

----------------------------------------
//0557 [2008/10/20] by Blaze

・0555の処理内容を修正（itemdb.c, itemdb.h）
	-> ランダムアイテム登録処理で初回登録時に
	   バッファオーバーフローが発生する可能性を修正
	-> ランダムアイテム検索ループの条件を修正
	-> rand関数仕様箇所をatn_rand関数に変更
	（thanks to Rayceさん）
	-> ランダムアイテム構造体のメンバを一対で保持するように修正

・getitemとgetitem2のスクリプト命令の仕様を変更（script.c）
	-> ランダム系で複数個取得を指定した際、
	   取得アイテムを毎回変更するように修正
	-> getitem2命令でランダム系を指定した際、
	   装備品のみ未鑑定状態を許可するように修正

・上記命令変更による、item_db.txtの該当箇所の最適化（db/item_db.txt）

----------------------------------------
//0556 [2008/10/18] by Cocoa

・ウンバラダンジョンのワープが機能していない不具合修正（npc_warp_dun.txt）

・デフォルトでシーズモードではアスムプティオが使用できないように変更（battle_auriga.conf）

・アルケミストクエストスキルが進行しない不具合修正（npc_quest_skillget2.txt）
	const.txtのJobClass部分が修正された場合また修正が必要になります。

・huge cgiよりmob_db.txtの1916～1925のデータ修正

・huge cgiよりmob_skill_db.txtに1916～1925のデータ追記

----------------------------------------
//0555 [2008/10/15] by Blaze

・ランダム系アイテムの登録と検索処理の改正（itemdb.c, itemdb.h）
	-> 直接確率を読み込んで判定していたのを
	   全体の登録数から判定するように
	-> ファイル毎でランダム系の種別をしていたのを
	   dbで登録されているIDで種別するように
	-> 仕様変更により、「MAX_RANDITEM」の値を変更
	(thanks to frozenさん)

・ランダム系アイテムを登録するdbを追加（db/item_random.txt）
	※これまでのdb/random直下のファイルは無効になります

・ランダム系アイテム種別の定義名を整理（db/const.txt）
	-> 「DIAMOND_*」など不要な定義の削除

・上記変更に伴い、item_db.txtの修正（db/item_db.txt）
	-> ランダム系アイテムの定義名変更
	-> ジュエルソード, ガイアソード, 呪文書の束, 菓子包み実装

・ダイヤモンドギャンブルNPCの修正（npc_quest_diamond.txt）
	-> 当選アイテム判定を内部で処理するように
	-> 得られるアイテムの種類と確率を本鯖仕様化

・スロットエンチャントNPCの一部NPC座標が
　正しく反映されなかったのを修正（npc_quest_slotenchant.txt）

・二次職クエストスキルNPCでソニックアクセラレーションの
　スキルIDが誤っていたのを修正（npc_quest_skillget2.txt）

・シャーマンクエストNPCの属性石分解数を増加（npc_town_umbala.txt）

----------------------------------------
//0554 [2008/10/15] by Rayce

・0552の傭兵に関する修正
	-> 見た目を自由に変更できるように、db/merc_db.txtにViewClass項目を復活（merc.*）
	-> 自然回復計算時、double型ではなくatn_bignumber型にキャストするように修正（merc.c）
	-> SQLモードでmakemerc命令を使用すると整合性が取れなくなるので、merc_callmerc() 内部で
	   SQLモードの処理をブロックするように修正（merc.c）
	-> @callmercで桁落ちが発生する可能性を修正（atcommand.c）
	-> makemerc命令を少し修正（script.c）
	-> rand() を atn_rand() に修正（clif.c）
	-> clif_send_mercstatus() で0除算が発生する可能性を修正（clif.c）

----------------------------------------
//0553 [2008/10/10] by Cocoa

・item_db更新
	ドロセラカードは「遠距離物理攻撃時」ではなく「遠距離武器装備時」になっています。

・item_bonusの説明文修正

・キリエエレイソンをかけた時のエフェクトが、対象ではなく術者に出ていた点を修正（skill.c）
	reported by Toshiさん

----------------------------------------
//0552 [2008/10/07] by Blaze

・傭兵関連の改正その１
　（merc.c, merc.h, map.h, clif.c, status.c, script.c）
	-> 傭兵ステータスの構造を改修
	-> 傭兵スキルデータの読み込みを改修
	-> 自然回復の計算式を修正
	-> 攻撃射程が無効になっていたのを修正、メンバattackable廃止
	-> 召喚時間を傭兵毎に設定していたのを、呼び出す時に指定するように変更

・傭兵データのフォーマット改修、データを本鯖仕様に修正（merc_db.txt）
	※0552以前のmerc_db.txtと互換性がなくなるので注意してください
・傭兵データのオーバーライドDBの追加（merc_db_add.txt）
・傭兵スキルツリーのフォーマット修正、データを本鯖仕様に修正（merc_db.txt）
・デバッグコマンド「@callmerc」の仕様を召喚時間を指定できるように変更（atcommand.c）
・スクリプト命令「makemerc」追加（script.c）
・傭兵召喚書アイテムの実装（item_db.txt）

----------------------------------------
//0551 [2008/10/05] by Rayce

・0365以降、一定条件下でMobの移動が完了した後動かなくなってしまうバグを修正（mob.*, unit.c）
	reported by alucardさん

・0550で発生したコンパイル警告を修正（script.c）

----------------------------------------
//0550 [2008/10/04] by Rayce

・AthenaProject Rev.288よりmerge、thanks to ico776さん
	-> guildskill命令でスキルレベルを0に指定した時、スキルが削除されなかったのを修正
	-> guildskill命令で指定するスキルレベルは加算ではなく、そのままの値を使うよう変更
	   （int_guild.c, inter.c, clif.c, guild.*, intif.*, script.c）

・0548で、getequipname関数で確保する文字列のサイズが大きすぎたを修正（script.c）
・intif_guild_alliance() のパケット長を修正（int_guild.c, inter.c, intif.c）
・一部の計算式の処理を最適化（battle.c）

----------------------------------------
//0549 [2008/10/03] by Cocoa

・0539以降、left_cardfix_to_rightがyesになっている時
　敵の防御力を無視していた不具合修正（battle.c）

----------------------------------------
//0548 [2008/10/02] by Rayce

・Athena形式のキャラセーブデータも読めるように拡張（char.c）
	reported by シスカさん

　※ただしホットキーの情報は捨てられます

・スクリプトのgetequipname関数で、アイテムを装備していたときの
　メッセージを修正（script.c）
	reported by NP3228さん

・sleepなどの待機中にdbのアイテム名を変更し、@reloaditemdbを行うと
　getitemname, getiteminfo関数で異なるデータが取得されてしまう問題を修正（script.c）

・0545のint_guild.cを少し修正（int_guild.c）

----------------------------------------
//0547 [2008/10/01] by Cocoa

・アルマイア=デュンゼカードが鎧に挿せた不具合修正（item_db.txt）
	reported by alucardさん

・スナイピングスーツが純Lukに応じてCriticalが増加しない不具合修正（item_db.txt）
	韓国ではLuk5毎にCri+1ですが、日本に合わせてLuk10毎にCri+1にしています。

----------------------------------------
//0546 [2008/09/30] by Cocoa

・ra_fild08、ra_fild09間の移動が出来なかった不具合修正（npc_warp_fild.txt）

・新スロットエンチャント用アイテムを適用（item_db.txt）

----------------------------------------
//0545 [2008/09/28] by Rayce

・SQL: charサーバ起動時にギルド城情報が初期化されてしまう致命的なバグを修正（int_guild.c）
・SQL: ROメールを開くとき、SELECTの構文エラーが発生する致命的なバグを修正（int_mail.c）
・SQL: mmo.hの MAX_CLOTH_COLOR を128以上にし、128番以上の服色を指定すると
       キャラクターデータのセーブ時にUPDATEエラーが発生する問題を修正
       （sql-files/Auriga545-changetable.sql）

・SQL: 全てのフィールドの型をAuriga内部の変数の型に合わせる（sql-files/main.sql）

----------------------------------------
//0544 [2008/09/28] by Rayce

・strftime() の部分を少し手直し（httpd.c, login.c）

・他人の装備ウィンドウを開いたとき、忍者とガンスリンガーの場合に
　表示されるキャラクターがノービスになっていたのを修正（clif.c）
	reported by Cocoaさん

----------------------------------------
//0543 [2008/09/25] by Cocoa

・スタッフオブピアーシングの効果が異なっている不具合修正（item_db.txt）

・huge cgiよりitem_db.txtの一部を追加

----------------------------------------
//0542 [2008/09/23] by Rayce

・0516以降、完全石化状態になったとき「status_change_timer %d != %d (type = %d)」の
　エラーが表示されるバグを修正（status.c）

・キャラ選択時のログに意味のない値が書き込まれていたのを修正（char.c）
・スタック時にマップ名が表示されるように（pc.c）
・Mobが攻撃対象以外をターゲットしたときに表示される情報を拡張（mob.c）

----------------------------------------
//0541 [2008/09/23] by Rayce

・AthenaProject Rev.288を参考に、タイミングによってはギルドスキルを
　レベル上限外まで取得できた問題を修正、thanks to ico776さん
　（int_guild.c, clif.c, guild.*, intif.c）

	サーバが過負荷のとき、もしくはマップサーバ分割時でタイミングに
	よって発生していました。
	MAPサーバでは各処理の同期を取るのが難しいので、スキル取得の
	整合性チェックをinterサーバで行うように変更します。

	従って、db/guild_skill_tree.txt の読み込みはinterサーバでのみ行います。
	MAPサーバでもギルドスキルLvの最大値の情報は必要なので、MAPサーバの
	初期化時にinterサーバから情報を受信し、guild_skill_max[] 配列に保存
	する仕組みにしています。

	上記変更により、ギルドスキルLvの最大値は db/guild_skill_tree.txt に
	記載された値が参照されます。
	db/skill_db.txt の値は使用されないので注意してください。

	-> guild_skill_tree 構造体をint_guild.cに移動
	-> guild_skill_max 配列追加
	-> guild_read_guildskill_tree_db() をint_guild.cに吸収
	-> guild_skill_get_max() は不要になったので削除
	-> guild_check_skill_require() をint_guild.cに移動
	-> guild_skillup() ではスキルツリーのチェックは行わないように変更
	-> guild_skillup() で、clif_guild_skillinfo() が多重に呼ばれるので削除
	-> clif_guild_skillinfo() でスキルツリーのチェックは行わないように変更
	-> mapif_parse_GuildSkillUp() の判定処理を guild_skillup() に合わせる
	-> mapif_guild_skillmax_load() 追加
	-> intif_parse_GuildSkillMaxLoad() 追加
	-> guild_skillmax_load() 追加
	-> doc/inter_server_packet.txt に0x3843を追記

----------------------------------------
//0540 [2008/09/23] by Rayce

・0519以降、auriga-start のstopとkillが動作しなくなっていたバグを修正（core.c）
	reported by シスカさん

----------------------------------------
//0539 [2008/09/22] by Rayce

・AthenaProject Rev.262よりmerge、thanks to ico776さん
	bIgnoreDef系およびbIgnoreMDef系の防御無視ボーナスで、
	効果の比率を設定できるように仕様を変更（battle.c, map.h, pc.c, status.c）

・AthenaProject Rev.264よりmerge、thanks to ico776さん
	アイテムボーナス「bBreakMyEquipWhenAttack」「bBreakMyEquipWhenHit」の
	解説を修正（doc/item_bonus.txt）

・db/item_db.txtを修正

----------------------------------------
//0538 [2008/09/21] by Rayce

・0374で、非暗号化ログインで且つクライアントからのアカウント作成を許可
  （login-auriga.confのnew_accountが1）しているとき、パスワードに @ を
  付けないとサーバクラッシュするバグを修正（login.c）

・Mobの死亡時スキルは、コマンドやスクリプトでの死亡でないときのみ
  発動するように修正（mob.c）
	merged from eA, thx a lot!!

・mobskill_use() で、MSS_DEADを優先するように修正（mob.c）
・numdb_cmp() における大小比較をintptr型からuintptr型に変更（db.c）

----------------------------------------
//0537 [2008/09/21] by Rayce

・メモリマネージャに関する修正（malloc.c）
	-> ポインタのアドレスを計算するときにはuintptr型を使うように修正
	-> _WIN64のときの制限を撤廃
	-> メモリリーク記録用のログファイル名の生成処理において、
	   バッファオーバーフローが発生する可能性を修正

・numdb_cmp() における大小比較は、ポインタのアドレスでも計算できるように
  intptr型で演算する（db.c）
・不要なキャストを削除（login.c, clif.c, map.h）
・db_init() で、不要な初期化を省略（db.c）

----------------------------------------
//0536 [2008/09/21] by Blaze

・スクリプト関数「getonlinepartymember」でパーティー未所属だった場合、
　返り値がおかしかったのを修正
	thanks to Rayceさん
	（script.c）

・ギルドの接続人数を返すスクリプト関数「getonlineguildmember」を追加
	（script.c, script_ref.txt）

・0534でwarp処理に関するスクリプトが巻き戻っていたのを修正
	thanks to Rayceさん
	（npc_misc_zonda.txt、npc_warp_town.txt）

・0534でmoc_fild16のモンスター出現情報が誤って無効になっていたのを修正
	（npc_monster_mocfild.txt）

・ayo_dun02のモンスター出現情報を修正
	（npc_monster_ayodun.txt）

・新スロットエンチャント実装、旧スロットエンチャントの成功確率を修正、
　拡張性を考慮し、処理の書式を全面的に変更
	（npc_quest_slotenchant.txt）

・以下の二次職クエストスキルの取得NPC実装
	ベナムナイフ、ソニックアクセラレーション、ファンタズミックアロー
	パンボイス、クローズコンファイン、レジストポーション
	（npc_quest_skillget2.txt）

・ベインスクエスト「スパイ疑惑」の一部NPCを魔王モロク変更に対応
	（npc_town_veins.txt）

・本鯖で変更された精錬NPCの手数料を適用
	（npc_misc_refine.txt）

----------------------------------------
//0535 [2008/09/20] by Rayce

・WBUFPOS, WBUFPOS2 を修正（clif.c）
	merged from eA, thx a lot!!

・念のため、マップ移動中には露店と取引の処理を行わないように強化（trade.c, vending.c）
・trade_check() の引数を変更（trade.c）

----------------------------------------
//0534 [2008/09/20] by Blaze

・パーティーの接続人数を返すスクリプト関数「getonlinepartymember」を追加
	（script.c, script_ref.txt）

・魔王モロクNPC追加・モロクNPCの変更
	（npc_town_morocc.txt）

・魔王モロクで変更されたNPCを対応
	（npc_misc_inn.txt, npc_misc_board.txt, npc_misc_refine.txt,
		npc_misc_zonda.txt, npc_quest_cooking.txt, npc_quest_ice.txt）

・魔王モロク追加マップの読み込み定義を追加
	（map_auriga.conf）

・魔王モロク追加マップのマップフラグ設定を追加
	（mapflag.txt）

・魔王モロク追加マップのモンスター出現情報を追加
	（npc_monster_mocfild.txt）

・魔王モロク追加マップのワープ定義を追加・修正
	（npc_warp_fild.txt, npc_warp_dun.txt, npc_warp_town.txt）

----------------------------------------
//0533 [2008/09/19] by Rayce

・0531のwarp命令に関する仕様を若干変更（script.c）
	suggested by apacheさん

	warp関連のスクリプト命令においてMAP名を指定する際、".gat" が不足していても
	内部的に自動補完し、動作できるようにします。
	ただし、AthenaProjectとの互換性を保持するために用意されています。
	".gat" を付けている場合に比べ処理速度は低下します。
	従って出来る限り ".gat" を記述することを推奨します。

・プレイヤーの最終ログインマップ名に ".gat" が不足していたとき
  バッファオーバーフローが発生する可能性を修正（char.c）

・0523以降、pc_setpos() でアクセスバイオレーションが発生していたのを修正（pc.c）

----------------------------------------
//0532 [2008/09/17] by Rayce

・0356以降、MAX_LEVELのときの基本SP値が0になるバグを修正（status.c）
	reported by 花咲香里さん

----------------------------------------
//0531 [2008/09/17] by Rayce

・0523以降、一部のスクリプトのwarp命令が動作しないバグを修正
	reported by apacheさん

	warp命令などのMAP名を指定するスクリプト命令/関数については
	常に ".gat" を付けるように統一します。
	".gat" が不足している場合は動作しない可能性が高いので注意してください。

----------------------------------------
//0530 [2008/09/16] by Rayce

・特定幅のint型を定義（utils.h）
	整数のサイズが固定で必要な場合に利用します
	uintptr, intptr はポインタのアドレス計算に使用します
	AthenaProjectではなくeAの指針がベースとなっているので注意してください

・atn_int64型はint64型に置換（utils.c）
・サーバ起動時に特定幅のサイズを確認する（core.c）

----------------------------------------
//0529 [2008/09/13] by Rayce

・MVP獲得者がホムで、主人がMVPアイテムを重量オーバーで所持できないとき、
　nullpoエラーが表示されるバグを修正（mob.c）
	merged from fix by ultramage on AthenaProject, thanks a lot!!

・ポインタへキャストする際のwarningを修正（unit.c）

・0515のdbやconfファイルの空行読み飛ばしにおいて、UNIX環境下で改行コードが
　CR/LFの場合を考慮してなかった問題を修正

----------------------------------------
//0528 [2008/09/13] by Rayce

・map_freeblock_lock() 中に同一のポインタが複数回 map_freeblock()
　されると、二重freeが発生する問題を修正（map.c）
	バッファを配列からtreedbに変更することで、同一のポインタが
	バッファに重複して登録されないようになります。
	従って map_freeblock() を重複して呼び出しても安全です。
	また BLOCK_FREE_MAX は撤廃されたので、バッファに蓄積できる
	量は無制限になります。

・0516をさらに強化して、スキルユニット設置時にサーバクラッシュが
　発生する可能性の対策（skill.c）

----------------------------------------
//0527 [2008/09/13] by Rayce

・malloc, calloc, realloc, strdup, free の #define 置換を廃止（malloc.*）
	aMalloc, aCalloc, aRealloc, aStrdup, aFree のマクロ群とは
	完全に分離されます。
	上記マクロを利用しない場合、メモリマネージャで管理されなくなります。
	40kBを越える巨大なメモリを確保する必要があって、確実にメモリリーク
	しないことが保証できる場合にのみ利用してください。

・treedbで使用するメモリプールは、callocでアロケートするように変更（db.c）
・check_ttl_wisdata() の処理を最適化（inter.c）

----------------------------------------
//0526 [2008/09/13] by Rayce

・スキルユニットグループに関連するキャスト問題バグ対策
　（map.*, pc.c, skill.c, status.c, unit.c）

	変更前
		status_change_start(bl,SC_ANKLE,sg->skill_lv,(int)sg,0,0,sec,0);
		    ↓
		struct skill_unit_group *sg = (struct skill_unit_group *)sc->data[SC_ANKLE].val2;
	変更後
		status_change_start(bl,SC_ANKLE,sg->skill_lv,sg->bl.id,0,0,sec,0);
		    ↓
		struct skill_unit_group *sg = map_id2sg(sc->data[SC_ANKLE].val2);

	スキルユニットグループについても、アドレスをintにキャストして保存する方法を廃止します。
	skill_unit_group型のデータを参照するときには、必ず map_id2sg() を経由してください。
	またスキルユニットグループをID管理する必要があるので、skill_unit_group構造体に
	block_list構造体を追加しています。
	BL_CHATと同じくブロックリストには繋がれません。

----------------------------------------
//0525 [2008/09/13] by Rayce

・マップ移動の最中は clif_parse_LoadEndAck 以外のパケットを
　受け付けないように修正（clif.c）
	reported by alucardさん

　※マップ移動後からマップロードまでの間に、不正なパケットを
　　受信することによってDupeが発生していたのが修正されます

・nullpoチェック強化（clif.c）

----------------------------------------
//0524 [2008/09/08] by Rayce

・battle_auriga.confの player_land_skill_limit がyesのときの地面スキルの
  設置個数の計算は skill_count_unitgroup() を使うように修正（skill.c）
・skill_initunitgroup() からダンスの処理を分離（skill.c）

----------------------------------------
//0523 [2008/09/07] by Rayce

・0516で、bEternalStatusChangeの発動判定が間違っていた致命的なバグを修正（status.c）
・map名に ".gat" が含まれているかどうかの判定は不要なので削除（char.c, pc.c）
・一部の関数の引数にconstを付与（char.c, chrif.*, map.*）

----------------------------------------
//0522 [2008/09/06] by Rayce

・AthenaProject Rev.548よりmerge、thanks to ico776さん
	スキルユニットの発動範囲読み込み処理を拡張し、
	発動範囲をスキルレベル毎に設定できるように修正（skill.*）

・0519で、core_ExceptionRoutine() の漏れを修正（core.c）
・不要なキャストを削除（db.c）
・ギルドデータ受信時、トリッキーなmemcpyを使わないように修正（guild.c）
・nullpoチェック追加（skill.c）

----------------------------------------
//0521 [2008/08/31] by Rayce

・0520で、script_free_stack() においてポインタを参照してなかったバグを修正（script.c）
・0520で、push_copy() におけるC_PTRの処理が間違っていたので修正（script.c）
・0520で、コンパイルオプション DEBUG_VARS の除去が不完全だったのを修正
  （bcc32_make.bat, vc_make.bat, doc/server_build.txt）

----------------------------------------
//0520 [2008/08/31] by Rayce

・使用された変数の一覧を出力するコンパイルオプション DEBUG_VARS を
  script_auriga.conf でスイッチするように変更（script.c）

・callfunc, callsub は、バイトコードと関数依存変数の情報を push_ptr() で
  pushするように修正（script.*）

・スタックを拡張する部分を expand_stack() として共通化（script.c）

----------------------------------------
//0519 [2008/08/31] by Rayce

・pid_create() を少し修正（core.c）
・core_ExceptionRoutine() を少し修正（core.c）
・不要なintのキャストを削除（graph.c）
・map_foreachinarea() のエラー時の出力を少し修正（map.c）

----------------------------------------
//0518 [2008/08/27] by Rayce

・Athena Rev.505より部分的にmerge、thanks to Blazeさん（grfio.c, map.c）
	-> 水場の高さをrswファイルから読むように
	-> conf/water_height.txtはrswの高さをオーバーライドする際に利用する
	   デフォルトでは未記入状態
	-> mapキャッシュ読み込み時、conf/water_height.txtに記述があるmapに
	   対してのみ水場が変更されていないかのチェックを行う

	※mapキャッシュを利用している方は、map.infoを削除して再度
	  作成し直して下さい
	※rswファイルが変更されてもmapキャッシュの自動再作成は行われないので、
	  その場合はmapキャッシュを削除してから再度作成し直して下さい

・conf/water_height.txtで、高さを省略した場合は全水場になるように修正（map.c）
	機能が中途半端で動作していなかったので有効化
	mapflagのrainを指定しなくても全てのセルを水場に設定できます

・conf/water_height.txtはmap_auriga.confの読み込みが終わった後に
  読み込みを行うように変更（map.c）

・map読み込み時、128MAP単位でメモリを拡張するように改善（map.c）
・map名の拡張子が .gat かどうかのチェックは map_readallmap() ではなく
  map_addmap() で行うように変更（map.c）

・BLOCK_FREE_MAXを超過したとき、blockがfreeされないのを修正（map.c）

----------------------------------------
//0517 [2008/08/23] by Rayce

・add_timer_real() のdataをint型からvoid型のポインタに変更
	ポインタをintにキャストすることなく、そのまま渡すことができます

・add_timer_real() のidはfreeできないように変更（timer.*）
	TIMER_FREE_ID, TIMER_FREE_DATA は廃止

----------------------------------------
//0516 [2008/08/23] by Rayce

・子守唄設置時にサーバクラッシュするバグを修正（status.c）
	reported by mccainさん

	SC_LULLABY で skill_additional_effect() 内で合奏の相方が睡眠状態になると
	合奏が停止してしまい、スキルユニットグループが不定になるのが原因。
	status_change_timer() を map_freeblock_lock() で保護するようにしました。

・skill_unitsetting() で、全てのユニットの設置が終わってから
  直上スキルを発動させるように修正（skill.c）

・地面設置スキルを使用時、ランドプロテクターなどによってスキルユニットの生成が
  妨害されると、MAP移動やログアウトをしない限りスキルユニットグループが解放
  されないメモリリークを修正（skill.c）

----------------------------------------
//0515 [2008/08/20] by Rayce

・OnGuildBreakラベルが作動しないバグを修正（guild.c）
	reported by Cocoaさん

・skill_unit_timer() で、map_freeblock_lock/unlockが二重に呼ばれるのを修正（skill.c）
・dbやconfファイル読み込み時、空行は読み飛ばすように改善

----------------------------------------
//0514 [2008/08/17] by Rayce

・size_tやポインタのアドレス計算部分に関する型を修正
	strlenの型など、出来る限りキャストしないようにする

・script.cでwarningが発生する可能性を修正（script.c）
・skill_unit_onplace() の細かい変更（skill.c）

----------------------------------------
//0513 [2008/08/09] by Rayce

・menu/select命令に関して（script.c）
	-> 選択肢の文字列が : で始まるとき、: のメニュー補正が機能しないバグを修正
	-> 第1引数が空文字のとき、パケット送信用の文字列に余計な : を付加しないように修正
	-> 引数が1つのときは、パケット送信用の文字列組み立てを省略するよう最適化
	-> 不要な変数の初期化を削除

・スクリプトにprintarray関数を追加（script.c）
	配列の要素を文字列に変換します
	デフォルトの区切り文字は ":" となっているので、そのままselect関数に
	渡すことができます

	例）setarray '@buf$,"aaa","bbb","ccc";
	    set '@n,select(printarray('@buf$));	// aaa bbb ccc のメニュー

	また任意の区切り文字も設定可能です。

	例）setarray '@buf$,"ddd","eee","fff";
	    mes printarray('@buf$, "\n");	// ddd eee fff が1行ずつ表示

・0512で発生するコンパイル時の警告修正（script.c）

----------------------------------------
//0512 [2008/08/08] by Rayce

・0510のskill.cのコーディングを巻き戻し（skill.c）
	db/skill_db.txtのinf2を 3072 にすることで、自分とPT/ギルドメンバーのみに
	使用可能になるので不要

・0511でareawarp命令の書式が巻き戻されているので書き直し（script.c）
・doc/script_ref.txtを少し修正

----------------------------------------
//0511 [2008/08/07] by Cocoa

・npc_morocc.txtで職業変数の定義が間違っていた不具合修正

・Athena Rev.497よりmerge、thanks to Blazeさん
	-> スクリプト命令「mapwarp」追加

----------------------------------------
//0510 [2008/08/07] by Cocoa

・Athena Rev.287よりmerge、thanks to ico776さん
	-> 攻撃属性付与スキルを、自身とパーティーメンバーに対してのみ使用できるように修正

----------------------------------------
//0509 [2008/08/04] by Cocoa

・0506でのstatus.cの記述が変だったので修正

・Athena Rev.510よりmerge、thanks to Blazeさん
	-> 魔王モロククエスト実装
	-> 関連マップのマップフラグ追加

・Athena Rev.512よりmerge、thanks to Blazeさん
	-> 名も無き島新規追加モンスターのスキル追加

----------------------------------------
//0508 [2008/08/01] by Cocoa

・Athena Rev.452よりmerge、thanks to nanashiさん
	-> GMキャラクターの全スキルリストにNPCスキルが紛れ込んでいたのを修正

・Athena Rev.455よりmerge、thanks to Blazeさん
	-> モスコビア関連マップのwarp追加

----------------------------------------
//0507 [2008/08/01] by Cocoa

・Athena Rev.412よりmerge、thanks to Blazeさん
	-> ラヘルとベインスのジョンダ職員に空間転送機能を追加

・Athena Rev.416よりmerge、thanks to Blazeさん
	-> モスコビア追加マップのmonster定義を追加

・Athena Rev.417より一部merge、thanks to Blazeさん
	-> モスコビアNPC実装

・Athena Rev.418よりmerge、thanks to Blazeさん
	-> モスコビアの案内要員とカプラ職員NPCを追加

----------------------------------------
//0506 [2008/08/01] by Cocoa

・Athena Rev.413よりmerge、thanks to Blazeさん
	-> 名も無き島関係マップのwarp定義を追加
	-> ベインスwarp名修正

・Athena Rev.414よりmerge、thanks to Blazeさん
	-> 名も無き島の秘密クエストNPC実装
	->プロンテラとラヘルの名も無き島関連NPCの修正
	-> map_auriga.confに名も無き島関連ファイルを定義追加

・Athena Rev.415よりmerge、thanks to Blazeさん
	-> モスコビアのwarp定義を追加

・Athena Rev.417より一部merge、thanks to Blazeさん
	-> map_auriga.confにモスコビア関連ファイルを定義追加

・Athena Rev.486よりmerge、thanks to nanashiさん
	-> アサテンプレ、ROratorioを参考に最大HP/SP計算式修正(status.c)

----------------------------------------
//0505 [2008/07/30] by Cocoa

・プレイヤーからエフェクトを発生させるmisceffect2命令を実装（script.c）
	-> script_ref.txtにmisceffet2命令の記述を追加
	-> npc_quest_skillget2.txtのgmcommandをmisceffect2に置き換え

・Athena Rev.419よりmerge、thanks to Blazeさん
	-> 名も無き島とモスコビア関連マップのmapflagを設定

・Athena Rev.437よりmerge、thanks to frankenさん
	-> カニカードのセット効果でおさしみではなく貝をドロップしていた不具合を修正

・Athena Rev.490よりmerge、thanks to yuyuyuさん
	-> チュンイーカードでCritical-5されていた部分を削除

----------------------------------------
//0504 [2008/07/30] by Cocoa

・Athena Rev.494よりmerge、thanks to yuyuyuさん
	-> サイコロゲームで勝ちと負け両方のメッセージが出ていたのを修正

・Athena Rev.501よりmerge、thanks to Blazeさん
	-> ゲフェンNPCに吟遊詩人クエストを実装

・Athena Rev.506よりmerge、thanks to frankenさん
	-> 名も無き島修道院のmapflagを設定

----------------------------------------
//0503 [2008/07/30] by Cocoa

・Athena Rev.515よりmerge、thanks to Blazeさん
	-> セージ転職クエストNPC実装

・Athena Rev.516よりmerge、thanks to Blazeさん
	-> 2次職クエストスキルNPC追加

・Athena Rev.517よりmerge、thanks to Blazeさん
	-> 1次職クエストNPC実装

----------------------------------------
//0502 [2008/07/29] by Cocoa

・0501でコンパイルが通らない不具合修正（skill.c）

----------------------------------------
//0501 [2008/07/28] by Cocoa

・Athena Rev.295よりmerge、thanks to Arc87さん
	-> 一セルに栽培可能な数を一つまでに限定（skill.c）

・Athena Rev.349よりmerge、thanks to nanashiさん
	-> skill_db.txt内の誤表記を訂正

----------------------------------------
//0500 [2008/07/28] by Cocoa

・Athena Rev.342よりmerge、thanks to Forestさん
	-> アーチャー試験でスナイパーが転職出来てしまうバグを修正

・Athena Rev.343よりmerge、thanks to Forestさん
	-> リヒタルゼン治安維持員の判定不備を修正

・Athena Rev.346よりmerge、thanks to ico776さん
	-> モンスターのアイテムルート範囲を8セルから10セルに修正（mob.c）

----------------------------------------
//0499 [2008/06/29] by Rayce

・ギルド倉庫に装備品が840個以上あると、蔵が強制終了する問題の対策（scoket.*, clif.c）
	蔵が１度に受け取れるパケットサイズは21820byteまでです。
	これを超過すると強制終了します。
	AthenaはRev.98でMAX_GUILD_STORAGEを1000から800に縮小していますが、
	縮小はせずにパケットを分割して送信する方法を採用しました。

	-> 最小限確保するパケットの空き容量を SOCKET_EMPTY_SIZE として定義
	-> SOCKET_EMPTY_SIZE を16KBから20kB（21820byte以下）に拡張する
	-> カプラ倉庫とギルド倉庫の処理をまとめる
		clif_storageitemlist_sub()
		clif_storageequiplist_sub()
	-> 倉庫パケットのサイズが SOCKET_EMPTY_SIZE を超過した場合は分割する

	※パケット分割しないといけないほど倉庫のアイテム数が多い場合、アイテムの
	  リストが表示されるまでかなりの時間が掛かります。

----------------------------------------
//0498 [2008/06/22] by Rayce

・IDが0のタイマーを delete_timer() で削除できないバグを修正（timer.c）
	merged from eA, thx a lot!!

・状態異常アイコン SI_*** の定義をAegisから補完（status.h）
	thanks to しゃずさん

----------------------------------------
//0497 [2008/06/21] by Rayce

・Athena Rev.330よりmerge、thanks to mizukiさん
	-> __WIN32は定義されていないため、ソケットハンドルがリークしていたのを修正（socket.c）

・includeを修正（journal.*, md5calc.c）
・clif_skillinfoblock() を蔵のパケット解析方法に合わせるように少し修正（clif.c）

----------------------------------------
//0496 [2008/06/01] by Rayce

・conf/char_auriga.confに check_status_polygon を追加（char.c）
	キャラ作成時のステータスポイントに制限を掛けることができます。

	0のとき：
		制限なしです。
		蔵の "Free-Form Stats Polygon" を有効にしていて、各ステータスを
		全て9にしたいとき設定します。
	1のとき：
		各ステータスの合計を30以下に制限します。
		0495以前と同じ形式です。
	2のとき：
		デフォルトです。
		STR+INT=10, AGI+LUK=10, VIT+DEX=10 に制限します。
		"Free-Form Stats Polygon" を有効にしていないの蔵で、
		意図しない不正なステータスが指定されるのを防止します。

・2008-05-28aSakexeに対応
	-> MAX_PACKET_DB を 0x400 に拡張（clif.h）
	-> ステータス異常アイコン SI_*** に追加分のコメントを記述（status.h）
	-> db/packet_db.txt更新
	-> doc/client_packet.txt更新

----------------------------------------
//0495 [2008/05/31] by Rayce

・0494でコンパイルできなかったのを修正（core.c）
	reported by seikaiさん

・キャラクタースロットを12まで拡張（char.*）
	conf/char_auriga.confの max_char_slot を12すれば、
	1アカウント当たり12キャラまで作成可能です。
	12よりも大きなキャラを扱いたい場合は、char.hの MAX_CHAR_SLOT の値を
	拡張する必要があります。

----------------------------------------
//0494 [2008/05/27] by Rayce

・srand() には gettick() ではなく現在時刻を渡すように修正（core.c）
・csvdb_open() を少しだけ最適化（db.c）
・0412で、１行当たり読み込める最大文字数の拡張が一部適用されてなかったのを修正（npc.c）

----------------------------------------
//0493 [2008/05/25] by Cocoa

・植物栽培でスキルレベルに関わらずきのこを生成していた不具合修正

----------------------------------------
//0492 [2008/05/09] by Cocoa

・AthenaProject Rev.237よりmerge、thanks to ico776さん
	-> アイテムボーナスHPPenaltyTimeで負数を設定した場合、nミリ秒でhpが回復するように修正（pc.c）

・AthenaProject Rev.238を参考に修正、thanks to ico776さん
	-> NPCスキル「自爆」のダメージが軽減できなかった不具合を修正（battle.c）
	-> NPCスキル「自爆」はシーズ補正を受けないように修正（battle.c）

・AthenaProject Rev.239よりmerge、thanks to ico776さん
	-> GMハイド状態のPCが全てのキャラクターを対象とするスキルの効果を受けていたのを修正（battle.c）

----------------------------------------
//0491 [2008/05/07] by Rayce

・ギルド倉庫のデッドロック検出を実装（char.c, int_storage.*, inter.c, intif.*, storage.*）
	誰もギルド倉庫を使ってないのに、倉庫が開けなくなる現象に対する暫定対策。
	1時間おきにギルド倉庫がデッドロックになっていないかチェックします。
	デッドロックになっていた場合は、自動的にロックが解除されます。

	通常、デッドロックは起こり得ないはずですが、もし
	「guild_storage_deadlock_timer: storage deadlocked!! (???)」が出力された
	場合には、速やかにご報告をお願いします。

----------------------------------------
//0490 [2008/05/06] by Rayce

・コンソールに表示するバージョン番号を、Readmeから参照するように（login.c, char.c, map.c）
	common/version.cを追加
	取得に失敗した場合は、AURIGA_REVISIONの値を使用する

・AURIGA_MOD_VERSION は意味がないので、代わりにReameのバージョンを参照する（login.c, clif.c）
	管理用パケット0x7531のパケット長を拡大
	tool/ladmin, tool/checkversion, tool/php/auriga.php を修正

・txt-converter.exeにもバージョン番号を表示するように（converter.c）
・MAPサーバのコンソールに、タグ名 map_server_tag を表示するように（map.c）
・サーバ起動時にPACKETVERを表示するように（core.c）
・warning修正（login.c, party.c）

----------------------------------------
//0489 [2008/05/06] by Rayce

・0327以降、ギルドスキルが発動しなくなっていた致命的なバグを修正（clif.c）
	reported by しゃずさん

・0488のルアフの部分をさらに修正（status.c）
・二項代入演算で桁落ちが発生していたのを修正（battle.c, status.c）

----------------------------------------
//0488 [2008/05/01] by Cocoa

・AthenaProject Rev.332よりmerge、thanks to nanashiさん
	-> 氷晶落（氷柱落とし）の範囲を自分中心7x7セルに修正

・AthenaProject Rev.328よりmerge、thanks to nanashiさん
	-> サイトブラスターでクローキング、ハイディングを解除できないように修正
	-> MATK倍率を等倍に変更

・AthenaProject Rev.326を参考に修正
	-> サイト、ワイドサイト、ルアフ、集中力向上、ディテクティングでインビジブルを解除できるように修正

----------------------------------------
//0487 [2008/05/01] by Cocoa

・AthenaProject Rev.291よりmerge、thanks to Blazeさん
	-> ベインスNPC修正・追加
	-> ベインスクエスト修正

----------------------------------------
//0486 [2008/04/19] by Cocoa

・AthenaProject Rev.306よりmerge、thanks to Blazeさん
	-> モンスターのステータスでASPDよりaMotionが高ければaMotionの値を攻撃速度に用いるように修正
	-> mob_dbの暫定数値の全修正と最新化（Thx huge cgi）

----------------------------------------
//0485 [2008/04/14] by Cocoa

・特定の条件でクリティカルダメージが増加しない不具合修正（battle.c）

・AthenaProject Rev.265よりmerge、thanks to Arc87さん
	-> 料理材料の再修正

・AthenaProject Rev.281よりmerge、thanks to miyajiさん
	-> 「十字架のヘアバンド」作成クエストの成功アイテムIDが小悪魔帽になっていたのを修正

・AthenaProject Rev.282よりmerge、thanks to Arc87さん
	-> 「ピアノの鍵盤クエスト」と「TheSignクエスト」で魔女の処理に不都合が出ていたのを修正

・AthenaProject Rev.284よりmerge、thanks to Blazeさん
	-> 名も無き島アップデート関連のモンスター出現情報を最新化

・細々した点を修正（npc.c）

----------------------------------------
//0484 [2008/04/07] by Rayce

・キャラ削除時はパーティIDとギルドIDの0初期化は不要なので、0483を修正（int_guild.c, int_party.c）
・SQL: キャラ削除時に `hotkey` テーブルからデータが削除されるように修正（char.c）

----------------------------------------
//0483 [2008/04/07] by Rayce

・ログインしていないキャラをパーティから除名すると、除名できなかったり
　「party: check_member ???[???] is not member」が出力されるバグを修正（char.h, int_party.c）

・int_party.cと同様の処理をギルドにも施す（int_guild.c）

----------------------------------------
//0482 [2008/04/06] by Rayce

・パーティメンバーの照合はキャラ名ではなくキャラIDで行うように改善
　（int_party.*, inter.c, mmo.h, intif.*, party.*）
	-> party_member構造体にchar_idメンバを追加
	-> inter, mapサーバ間のパケットを一部変更

・意味のない関数 party_check_conflict() の呼び出しをコメントアウト（party.c）
・TXT: JOURNAL_IDENTIFIER を 08 に引き上げ（journal.c）

・0481の pc_steal_item() をさらに修正（pc.c）

----------------------------------------
//0481 [2008/03/24] by Cocoa

・AthenaProject Rev.203より一部merge
	-> スタン確率の判定式を修正（skill.c）
	thanks to Blazeさん

・AthenaProject Rev.233よりmerge、thanks to ico776さん
	-> ステータス固定系ボーナスで、-の値を設定できないように修正（status.c）
	-> アイテムボーナスbFixCriticalの最大値を100から無制限に修正（status.c）

・AthenaProject Rev.234を参考に修正、thanks to ico776さん
	-> ドロップ率0%のアイテムがスティール可能だった不具合修正（pc.c）

----------------------------------------
//0480 [2008/03/24] by Rayce

・0447以降、PACKETVERが14以上のときにギルド倉庫が開けなかったバグを修正（clif.c）
	reported by Cocoaさん

----------------------------------------
//0479 [2008/03/24] by Rayce

・0470以降、csvreadarray命令で正しいデータが取得できないバグを修正（script.c）
	reported by Cocoaさん

----------------------------------------
//0478 [2008/03/23] by Cocoa

・AthenaProject Rev.191より一部merge
	-> ストーンカースの成功率修正
	thanks to Rohypnolさん

----------------------------------------
//0477 [2008/03/23] by Cocoa

・AthenaProject Rev.293を参考に矢作成データベースを修正
	thanks to Shimodaさん

----------------------------------------
//0476 [2008/03/22] by Rayce

・AthenaProject Rev.294より、CSV命令/関数を使用するとサーバクラッシュするバグを修正（db.c）
	thanks to soriaさん

・砦の宝箱のGM専用デバッグモードが作動しなくなっていたのを修正（npc_gvg_tbox.txt）

----------------------------------------
//0475 [2008/03/16] by Rayce

・0470以降、キャラ永続変数が正しく取得できないバグを修正（script.c）
	reported by Cocoaさん

----------------------------------------
//0474 [2008/03/13] by Rayce

・0470以降、db/const.txtの埋め込み変数が正しく取得できないバグを修正（script.c）
	reported by Cocoaさん

----------------------------------------
//0473 [2008/03/09] by Rayce

・SQL: MySQLのAPIをラップしたsqldbs.c, sqldbs.hを追加
・SQL: INSERT文で、VALUESに複数の値のリストを指定しないように変更
・SQL: SQLサーバ接続時に、MySQLのバージョンを表示するように拡張

・SQL: テーブル名をdefineに変更し、sqldbs.hに集約
・SQL: loginテーブルで利用するフィールド名は、変数に格納せずに直接クエリ文に書き込むように変更（login.c）
・SQL: char_sql_loaditem() および char_sql_saveitem() で使用するenumの変数名を変更
       （char.*, int_storage.c）

　※converterはまだ変更を加えてません。
　　正式対応されるまで使用を控えてください。

----------------------------------------
//0472 [2008/03/07] by Cocoa

・カタール装備時に、右手修練、左手修練が適用されていた不具合修正（battle.c）

----------------------------------------
//0471 [2008/03/05] by Rayce

・[SQL] configで設定したcharsetがMySQLサーバに正しく反映されてなかった問題を修正
	（login.c, char.c, map.c, converter.c）

	MySQLサーバ接続時にSET NAMESを送っていましたが、SET NAMESだとクライアントの
	文字セットの情報を送るだけで、mysql_real_escape_stirng() には影響しないという
	現象がありました。
	代わりに mysql_options() で MYSQL_SET_CHARSET_NAME を設定するように変更しました。

	これにより、sjis以外（cp932など）のcharsetを設定しているのも関わらず、「表」の
	ようにSJISで0x5c（バックスラッシュ \）を末尾に含む文字列がクエリ発行できない問題が
	解消されます。

・[SQL] 052で実装した TRIM_ESCAPE_AS_SJIS のdefineを撤廃（utils.c）
	上記修正により、strecpy() の強引な拡張は不要になったため

・[SQL] converterの終了時に、mysql_close() が呼ばれてなかったのを修正（converter.c）

----------------------------------------
//0470 [2008/03/02] by Rayce

・db/const.txtに文字列を定数として設定できるように拡張（script.c）
	文字列の場合はポストフィックス$を付ける必要があります。
	C_STRとして扱い、解析時に直接文字列をバイトコードに書き込みます。

	例）db/const.txt
		FUGA$	string
	    呼び出し
		debugmes FUGA$;	// "string" を表示

・変数読み取り時に、プレイヤーにアタッチできなかった場合は初期値を入れるように修正（script.c）
	文字列 → ""
	数値   → 0

・add_str() で一度にメモリ確保するサイズを拡張（script.c）
	str_data 128 → 512
	str_buf  256 → 4096

・一部の関数の引数にconstを付与（script.*）
・script.cの細かい整形（script.c）

----------------------------------------
//0469 [2008/02/26] by Rayce

・キャラ一時変数に文字列を追加するとき、ダングリングポインタが発生するバグを修正（script.c）
	pc_setregstr() の *str と sd->regstr[] が同一アドレスの場合、aRealloc() の時点で
	*str がfree済みの領域を指していました。
	DEBUG_MEMMGRのdefineをオンにし、以下のスクリプトを実行すると再現できます。

	set @data1$,"dummy";
	set @data2$,@data1$;
	debugmes @data2$;

・一部の文字列にconstを付与する（pc.*, script.c）
・以下の関数を整理（script.c）
	conv_str()
	op_add()
	buildin_return()

----------------------------------------
//0468 [2008/02/19] by Rayce

・0458の１MAPサーバ当たり1023マップまでしか利用できない制限の撤廃が char_erasemap()
　にも適用されてなかったのを修正（char.c）

・AthenaProject Rev.185よりmerge、thank to Rohypnolさん
	bonus2 bWeaponAtkRateが正常動作しない可能性を修正（battle.c）
	正常動作しなかったおかげで結果うまく動いていたクリティカルダメージ対応

----------------------------------------
//0467 [2008/02/17] by Rayce

・バーサーク終了後、自然回復が停止するように修正（pc.c, status.*）
	SC_NATURAL_HEAL_STOP 追加
	効果時間は db/skill_cast_db.txt のupkeep_time2を利用
	デフォルトでは5分

・conf/battle_auriga.conf の free_sc_data_dynamically がyesのとき、一部の状態異常が
　正常に解除されないバグを修正（status.c）

----------------------------------------
//0466 [2008/02/16] by Rayce

・取り巻きが取り巻き召還をする際、召還可能な世代数を規定できるように拡張（battle.*, skill.c）
	conf/battle_auriga.confに summonslave_generation を追加。
	例えば2にすると2世代（孫）まで召還可能となり、3世代目以降の召還は行われません。
	デフォルトは0の無制限。

・@summonで呼び出されたモンスターは、NPC_SUMMONMONSTERおよびNPC_SUMMONSLAVEを使用できない
　ように変更（skill.c）
	0461以降、上記2つのスキルを使用すると、その呼び出したモンスターを攻撃してしまう
	問題が発生していました。
	攻撃せずに味方として認識させるためにはかなりの修正が必要になるので、0460以前と
	同じく使用不可扱いにしています。

----------------------------------------
//0465 [2008/02/16] by Rayce

・function構文のfunction名を配列として記述した場合、解析時にエラーとなるように修正（script.c）
	以下の例は今後解析時エラーとなります。

	function Test {
		debugmes "bbb";
		return;
	}
	Test[0];	// getelementofarray(Test,0) として解釈されていた

・0379以降、スクリプトにおいてfunction構文を宣言したあとにfunction構文の実体がある場合、
　実行時に「unknown command ? @ ?」が出力され実行が停止してしまう致命的なバグを修正（script.c）
	set_label() で C_POS ではなく C_USERFUNC_POS を書き込んでいたのが原因。
	実行時の get_com() で C_USERFUNC_POS がコマンドとして存在しないため
	エラーとなっていました。

・上記修正により、0462のモンク転職の修正は無意味になったので巻き戻し（npc_job_monk15.txt）

----------------------------------------
//0464 [2008/02/16] by Cocoa

・ポーションピッチャーのSP回復量が少ない不具合修正

----------------------------------------
//0463 [2008/02/16] by Rayce

・add_timer_func_list() を最適化して引数を減らす（timer.*）
・コンパイルオプション NO_HTTPD_CGI がオンのときは、外部cgi処理/中断リストタイマを
　起動しないように最適化（httpd.c）

----------------------------------------
//0462 [2008/02/15] by Cocoa

・モンク転職でメッセージが出なくなる不具合修正。

・アシッドデモンストレーションが近距離扱いになっていたのを修正（battle.c）

----------------------------------------
//0461 [2008/02/15] by Cocoa

・古く青い箱と古い紫色の箱でデフォルトアイテムが出やすかった不具合を修正

・取り巻きが取り巻きを召喚しない不具合修正（skill.c）
	マスターIDのチェックを抜いただけなので、取り巻きを召喚するMobが
	自分と同じMobIDを召喚すると無限に召喚するので注意してください。
	デフォルトでそんなMobはいないと思うので大丈夫だと思いますが…。

・ウィザード転職NPCのセリフ修正

----------------------------------------
//0460 [2008/02/12] by Rayce

・0456以降、読み込んだNPCの数が表示されなくなっていた問題を修正（npc.c）
	reported by seikaiさん

・OnAgitBreak, OnAgitEliminate の処理を最適化（guild.c）

----------------------------------------
//0459 [2008/02/11] by Rayce

・スキルユニットの性質（Flag）をスキルLv毎に指定できるように拡張（skill.*, unit.c）
	skill_split_strtol() 追加
	skill_get_unit_flag() の引数拡張

・レベルオーバーのメテオは壁チェックなしで貫通して落下するように再実装（db/skill_unit_db.txt）
	Lv11以上はFlagにUF_PATHCHECK（オブジェクト発生時に射線チェック）を付けない

----------------------------------------
//0458 [2008/02/11] by Rayce

・１MAPサーバ当たり1023マップまでしか利用できなかった制限を取り払う（char.c）
・MAPサーバ有効化時の出力メッセージを少し変更（char.c）

・0456のメテオストームに関する修正は間違っていたので巻き戻し（skill.c）
・run_script() を少し最適化（script.c）
・battle.cの細かい整形（battle.c）

----------------------------------------
//0457 [2008/02/11] by Rayce

・AthenaProject Rev.152よりmerge、thanks to Rohypnolさん
	管理者パケットをローカルホストに限定するオプションを追加（login.c）

・AthenaProject Rev.153よりmerge、thanks to Rohypnolさん
	武器修理を同時にお互いに実行しあうと無限ループに陥るバグを修正（clif.c）

・パケット0x1fa, 0x2b0でログインするとき、アカウント名が表示されるように修正（login.c）

----------------------------------------
//0456 [2008/02/10] by Rayce

・レベルオーバーのメテオは壁チェックなしで貫通して落下する（skill.c）
	reported by seikaiさん

・スクリプトにgetiteminfo関数を追加（script.c）
	関数名はeAと同名ですが、引数が異なるので注意。
	アイテムの持つ全てのデータを取得することができます。
	getiteminfo(<itemid>,0) と getitemid(<name>) は等価です
	getiteminfo(<itemid>,2) と getitemname(<itemid>) は等価です

・NPCファイル解析の部分を npc_parse_srcfile() として分離（npc.c）

----------------------------------------
//0455 [2008/02/10] by Rayce

・矢/弾丸の消費処理の改善（battle.c, skill.c）
	skill.cでのハードコーディングを廃止。
	db/skill_require_db2.txtに記載してさえあれば矢/弾丸を消費するスキルとなります。
	ただし、一部を除いてダメージが発生するスキルのみが有効です。

・グラウンドドリフトの処理改善（skill.c, db/item_arrowtype.txt, db/skill_require_db2.txt）
	item_arrowtype.txtに新しく5項目追加。
	今までは設置されるスフィアの種類をアイテムID13203～13207で決め打ちしていましたが、
	item_arrowtype.txtの「arrow_type」で決めるように拡張します。
	アイテムID13203～13207以外のアイテムをグラウンドドリフト用の弾丸として指定可能です。

	例１）13200,Bullet,バレット,1148
		バレット装備で風のグラウンドドリフトを設置
	例２）13205,Poison_Sphere,ポイズンスフィア,2048
		毒のグラウンドドリフト専用弾、通常攻撃では使用不可

----------------------------------------
//0454 [2008/02/10] by Rayce

・0452, 0453のエスマの修正部分を最適化（battle.c）
・クラッカーによるスタン効果時間が0秒になっていたのを修正（skill.c）
・クラッカー使用時に弾丸が消費されるように修正（skill.c）
・フリップザコインを失敗しても「スキル使用失敗」のメッセージが出ないように修正（skill.c）

・暗号化ログインパケット0x1faをサポート（login.c）
	langtypeが5のときに利用される模様

----------------------------------------
//0453 [2008/02/06] by Cocoa

・0452のmergeミスを修正（battle.c）

・AthenaProject Rev.218よりmerge、thanks to Blazeさん
	-> アルケミストスキル「安息」の条件判定で、基本HPを参照していたのを増減分もチェックするように修正（skill.c）

・AthenaProject Rev.221よりmerge、thanks to Blazeさん
	-> ハンタースキル「ビーストストレイフィング」の条件に「ダブルストレイフィング使用後」の判定がされていなかったのを修正（skill.c）
	-> ビーストストレイフィングに矢消費判定、使用時消費するように（battle.txt）

・AthenaProject Rev.229よりmerge、thanks to Shimodaさん
	-> フライング・トリプルアクション・ブルズアイの弾丸消費を修正（skill_require_db2.txt, battle.c, skill.c）

----------------------------------------
//0452 [2008/02/05] by Cocoa

・0451のスクリプトミスを修正

・AthenaProject Rev.174よりmerge、thanks to ViViさん
	-> エスマでマップサーバーがダウンする不具合を修正（battle.c）

----------------------------------------
//0451 [2008/02/05] by Cocoa

・AthenaProject Rev.161よりmerge、thanks to ViViさん
	-> チェイスウォーク解除時は詠唱無しに修正（unit.c）

・AthenaProject Rev.170よりmerge、thanks to Blazeさん
	-> スクリプト「emotion」で指定NPCが見つからなかった場合はアタッチ中のプレイヤーに表示させるように修正（script.c）
	-> それにともないscript_ref.txtを修正
	-> 全スクリプトからgmcommand命令を撤廃

----------------------------------------
//0450 [2008/02/02] by Rayce

・PACKETVER 9以降の番号を１つズラし、2007-05-21aSakexeを挿入（clif.c, pc.c）
	最新のPACKETVERは 13 → 14 に変更されています

・2007-05-21aSakexe以降のクライアントで、map_auriga.confの packet_parse_time を
　1以上に設定しないとMAPサーバにログインできない問題を修正（clif.c）
	merged from eA, thx a lot!!

・キャラクター作成時の失敗メッセージを修正（char.c）
・doc/client_packet.txt更新

----------------------------------------
//0449 [2008/01/31] by Rayce

・戦場チャットの下準備（clif.c）
	/battlechatに対応。
	ただし発言の受信は戦場システムの詳細が判明するまでは未実装。

・battle_auriga.confに check_player_name_battle_msg を追加（battle.*）
	ただし現時点では効果無し

・db/packet_db.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0448 [2008/01/30] by Rayce

・PACKERVERが13以上のとき、パケット0x2ec, 0x2ed, 0x2efをサポート（clif.c）
	表示系パケットの上位版のようです。
	末端に付加された2Byteは用途不明。

----------------------------------------
//0447 [2008/01/29] by Rayce

・PACKERVERが13以上のとき、パケット0x2e8, 0x2e9, 0x2f0をサポート（clif.c）
	強化装備アイテムと同様に、消耗品/収集品にも使用期限が表示できるようになります。
	2008-01-02aSakexeよりも古いクライアントを使う場合は、PACKETVERを12以下に
	戻してください。

・カートおよび倉庫に使用期限付き消耗品/収集品を複数入れると、アイテムが１つにまとめられて
　個数だけ増えるバグを修正（pc.c, storage.c）

----------------------------------------
//0446 [2008/01/29] by Rayce

・PACKERVERが12以上のとき、通常攻撃ダメージパケットの上位版 0x2e1 をサポート（clif.c）
	PACKETVERを12に引き上げます。
	通常攻撃のダメージ表示の限界値が 32767 → 999999 に拡張されます。

----------------------------------------
//0445 [2008/01/29] by Rayce

・/huntingに対応する関数だけ実装（clif.c）
・db/packet_db.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0444 [2008/01/28] by Rayce

・装備ウィンドウシステム実装（clif.*, map.h, party.*）
	merged from eA Forum, thx a lot!!

	装備を公開している相手の装備を見ることができます
	装備の公開はALT+E画面の下にあるチェックボックスをオンにするか、/eqopenを使うこと
	PACKETVERが11以上の場合に有効です
	現在のところは装備ウィンドウを表示した時点での装備しか見れず、相手が装備を付けたり
	外したりしても更新されません

・battle_auriga.confに equip_window_type を追加（battle.*, party.c）
	デフォルトは1で、パーティメンバーのみに表示されます
	2にすれば装備を公開している相手全ての装備を見ることができます

・db/packet_db.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0443 [2008/01/28] by Rayce

・0442の太陽と月と星の融合に関するコードを少し最適化（battle.c）

・キャラ作成時の髪型/髪色の最大数は MAX_HAIR_STYLE, MAX_HAIR_COLOR を使うように修正（char.c）
・MAX_MOBSKILL を 64 → 40 に縮小（map.h）

----------------------------------------
//0442 [2008/01/27] by Cocoa

・AthenaProject Rev.240より一部merge、thx a lot!!
	-> mob_db.txtを080112時点での最新版に更新

・オシリスとドッペルゲンガーの召還する取り巻きが1匹になっていたのを修正（mob_skill_db.txt）

・太陽と月と星の融合状態でHPが20%未満の時、プレイヤー以外を攻撃しても即死するように修正（battle.c）

・battle_configのitemidentifyがyesでもスティールで取得する装備品は未鑑定だったのを修正（pc.c）

----------------------------------------
//0441 [2008/01/26] by Rayce

・AthenaProject Rev.141よりmerge、thanks to Blazeさん
	-> ダメージディレイ間のテレポートダメージキャンセル実装（battle.c）

・AthenaProject Rev.145を参考に修正、thanks to Blazeさん
	-> 幻覚状態時のダメージ表示式を修正、回避してもヒットストップするように（clif.c）
	-> battle_auriga.confの「錯覚スキルを無効にする」を「エフェクトを無効にする」に改名

----------------------------------------
//0440 [2008/01/22] by Cocoa

・AthenaProjectよりMob使用スキルをmerge、thanks to Blazeさん
	-> 初期～Ep5、Ep6～Ep10.2までのMob使用スキルを本鯖準拠に更新（Rev.99,120,228）
	Lv10のヒール、ファイアーボール、サイトラッシャー、ツーハンドクイッケンをLv11にしてあります。

・AthenaProject Rev.99より一部をmerge、thanks to Blazeさん
	-> Mobのスキル登録最大数を増加

・AthenaProject Rev.228より一部をmerge、thanks to Blazeさん
	->フェイヨン地下洞窟、ベインスフィールド、トール火山ダンジョンのモンスター出現情報を更新

----------------------------------------
//0439 [2008/01/21] by Cocoa

・AthenaProject Rev.204をmerge、thanks to Blazeさん
	-> 重量チェックの値がおかしかったのを修正
	-> ベインスクエスト「黒い石」のLv判定を追加
	-> ラヘルクエスト「ブルーの行方」の結末修正
	-> ニブルヘイムのカプラ職員の処理修正
	-> 初心者修練場のメッセージ微修正

・AthenaProject Rev.222をmerge、thanks to ViViさん
	-> ルティエ：サンタの家ワープポイントバグ修正

・AthenaProject Rev.223より一部merge、thanks to Blazeさん
	-> クリスマスイベントモンスターの出現情報を最新に更新

・AthenaProject Rev.224をmerge、thanks to Shimodaさん
	-> インクリージングアキュラシーのコイン消費枚数を修正

・AthenaProject Rev.225をmerge、thanks to Shimodaさん
	-> ベインスアップデートにより、NPCから購入できるようになった銃を追加

----------------------------------------
//0438 [2008/01/21] by Cocoa

・AthenaProject Rev.227をmerge、thanks to Blazeさん
	-> 2006クリスマスイベントNPC修正
	-> 2007クリスマスイベントNPC実装
	-> イベントNPC「アマツ迎春泉水祭」（2008新年イベント）実装
	-> ラヘルNPC追加

----------------------------------------
//0437 [2008/01/21] by Cocoa

・AthenaProject Rev.251をmerge、thanks to Blazeさん
	-> 飛行船NPCの襲撃イベントの発動条件を修正

・AthenaProject Rev.252をmerge、thanks to Blazeさん
	-> 初心者修練場NPCの職業適性の判定結果格納変数を修正

・AthenaProject Rev.253をmerge、thanks to Arc87さん
	-> 茹でサソリの材料修正

----------------------------------------
//0436 [2008/01/21] by Rayce

・PACKETVERを11に引き上げる（clif.c）
	2007-11-06aSakexe以降がPACKETVER 11になります。
	キャラクター表示関連パケット、傭兵ステータスの既存パケット変更に対応。
	2007-11-06aSakexeより古いクライアントを使う場合にはPACKETVERを10以下に戻す必要があります。

・db/packet_db.txtを2008-01-08aSakexeまで対応
・doc/client_packet.txt更新

----------------------------------------
//0435 [2008/01/19] by Rayce

・0327以降、ナパームビートおよびナパームバルカンで複数の敵に使用すると
　"battle_calc_magic_attack: NAPALM enemy count=0 !" が出て、分散ダメージが
　当たらないバグを修正（skill.c）
	reported by Cocoaさん

・ブランディッシュスピアでLv11以上を考慮するように修正（skill.c）

---------------------------------------
//0434 [2007/12/02] by Cocoa

・status_calc_pcの加算base_atk処理をまとめて行うように修正（status.c）
・ボルケーノ、戦太鼓の響きで増加するATKをwatkからbase_atkに変更（status.c）
・魔法ダメージの軽減処理でsubraceが適用されていた不具合修正（battle.c）
・魔法ダメージの軽減処理でmagic_subsizeではなくsubsizeが適用されていた不具合修正（battle.c）

----------------------------------------
//0433 [2007/11/29] by Cocoa

・モンスターからモンスターに攻撃した際、mode0x40（固定ダメージ1）を無視していた不具合を修正（battle.c）

・0430の巻き戻しが不完全だったのを修正（pc.c）

----------------------------------------
//0432 [2007/11/29] by Cocoa

・スフィアマインで召還したマリンスフィアの自爆をヒールなどで中止させ、
　再びダメージを与えて移動させる際、移動速度がリセットされていなかった点を修正（mob.c）

・スキンテンパリングの火属性耐性値を修正（status.c）

----------------------------------------
//0431 [2007/11/27] by Cocoa

・AthenaProject Rev.178, 183をmerge、thanks to allegroさん, Rohypnolさん
	-> battle_athenaでシーズモード時のチャージアタックの移動効果の有無を設定できるように修正
		（battle_athena.conf, battle.*, skill.c）
	-> 一閃やティオアプチャギの移動効果がなくなっていたのを修正（skill.c）

----------------------------------------
//0430 [2007/11/25] by Cocoa

・0429で太陽と月と星の知識の適用が不完全だったので巻き戻し（status.c, pc.c）

・0429のmob_once_spawnを微修正（mob.c）

・AthenaProject Rev.177をmerge、thanks to allegroさん（skill.c ）
	-> チャージアタックにシーズモードでも移動効果の乗っていたものを修正

----------------------------------------
//0429 [2007/11/24] by Cocoa

・太陽と月と星の知識を指定したマップを出てもサーバーを移動しない限り適用される様に修正（status.c, pc.c）

・mob_once_spawnで座標を(0,0)以下に指定した際、マップとクラスが表示されるように修正（mob.c）

----------------------------------------
//0428 [2007/11/24] by Cocoa

・AthenaProject Rev.171, Rev.172をmerge、thanks to Blazeさん
	-> イベントNPC「ハロウィーン2007」実装
	-> イベントNPC「WMサーカス団」実装
	-> スーパーノービス転職NPCのメッセージ修正
	-> 拳聖転職NPCの処理など修正
	-> プロンテラNPCに追加クエスト「ゲオルグの呪い」を実装

・status.cのゴミ（余計なセミコロン）削除

----------------------------------------
//0427 [2007/11/24] by Rayce

・AthenaProject Rev.132を参考に、テコン蹴り準備発動時にダメージ表記がなかったのを修正（battle.c, skill.c）
	thanks to Blazeさん

・0424で巻き戻した「太陽と月と星の友」の発動確率に関する修正を再実装（battle.c, skill.c）

----------------------------------------
//0426 [2007/11/23] by Rayce

・0422の「手裏剣投げ」「苦無投げ」のコードを書き直し（battle.c）
・0423のマインドブレイカー処理が中途半端だったので修正（status.c）
・0423のMobのランダム移動の射線チェックが間違っていたので修正（mob.c）

・AthenaProject Rev.142を参考に、Mobからターゲットされている間にテレポなどで見失った時も
　ターゲットを保持し、再度視界内に入ると即時追撃してしまうのを修正（mob.c）
	thanks to Blazeさん

----------------------------------------
//0425 [2007/11/23] by Rayce

・skill_sit_count() および skill_sit_in() を最適化（skill.c）
・「太陽と月と星の奇跡」の職業判定はs_classを参照するように修正（battle.c）

・/doridoriに関する修正（clif.c, map.h）
	-> doridori_counterをsn_doridoriに改名してstate構造体内に移動
	-> tk_doridori_counter_hp, tk_doridori_counter_spをそれぞれ
	   tk_doridori_hp, tk_doridori_spに改名してstate構造体内に移動
	-> /doridoriはスーパーノービス、テコン系のみに効果が発揮されるようにチェック強化
	-> packet_db.txtの sndoridori を doridori に改名

----------------------------------------
//0424 [2007/11/23] by Rayce

・0420における「太陽と月と星の友」の修正はmergeが中途半端なので巻き戻し（battle.c）
・0420における「太陽と月と星の天使」の修正を一時的に巻き戻し（pc.c）

・0421は実装が汚いので全面巻き戻し（battle.c, map.h, pc.*, skill.c）
・0423がコンパイルできなかったのを修正（mob.c）

----------------------------------------
//0423 [2007/11/22] by Cocoa

・AthenaProject Rev.140よりmerge、thanks to Rohypnolさん
	-> マインドブレイカーによるMDEF減少効果を除算MDEF対象から減算MDEF対象に修正（status.c）

・AthenaProject Rev.142より以下の項目をmerge、thanks to Blazeさん
	-> Mobのランダム移動判定に射線チェックを追加（mob.c）

・AthenaProject Rev.151より以下の項目をmerge、thanks to ViViさん
	-> チェイスウォークを詠唱妨害可能に修正（skill_db.txt）

----------------------------------------
//0422 [2007/11/22] by Cocoa

・AthenaProject Rev.138より以下の項目をmerge、thanks to Blazeさん（battle.c, skill_cast_db.txt, skill_db.txt）
	-> 忍者スキル「手裏剣投げ」「苦無投げ」のダメージ計算を修正、必中ダメージ実装
	-> 風魔手裏剣投げを詠唱妨害されるように修正
	-> 「苦無投げ」「風魔手裏剣投げ」「空蝉」「龍炎陣」「氷柱落とし」の使用後ディレイを本家同等に修正

----------------------------------------
//0421 [2007/11/22] by Cocoa

・AthenaProject Rev.133よりmerge、thanks to Blazeさん（battle.c, map.h, pc.*, skill.c）
	-> ソウルリンカースキル「カアヒ」本実装
	-> 敵の攻撃後にディレイ発動、スキル攻撃には無反応に、エフェクト正常化
	-> 違うレベルのカアヒをかけ直した時、レベルの高低に関わらずに新しいレベルで上書きするように修正

----------------------------------------
//0420 [2007/11/22] by Cocoa

・AthenaProject Rev.131よりmerge、thanks to Blazeさん
	-> 「太陽と月と星の奇跡」「太陽と月と星の天使」は職業が拳聖のときのみ発動するように修正（battle.c, pc.c）

・AthenaProject Rev.132より以下の項目をmerge、thanks to Blazeさん
	-> 拳聖スキル「太陽と月と星の友」の発動確率を修正（battle.c）

----------------------------------------
//0419 [2007/11/20] by Cocoa

・create_arrow_db.txtをID順にソート
	thanks to ぽぽりさん

・コンセントレイションの前提スキル修正（skill_tree.txt）

----------------------------------------
//0418 [2007/11/18] by Rayce

・AthenaProject Rev.127を参考に以下を実行、thanks to Blazeさん
	-> 拳聖スキル「温もり」の攻撃間隔を秒間50HITを再現（skill.c）
	-> 温もり状態時にテレポートをすると効果を削除するように修正（pc.c）

　　※skill_unit_db.txtにおける温もりユニットのintervalを20msに変更しています。
　　　通常intervalの最小値は100msですが、温もりのみ特殊で本鯖仕様の秒間50HITを再現します。
　　　従来の仕様に戻したい場合はintervalを200msに設定し直してください。
　　　AthenaProjectのようなbattle_configでの設定はありません。

----------------------------------------
//0417 [2007/11/18] by Cocoa

・ディフェンダー解除時、SPを消費するように修正（skill.c）
・シュリンク解除時、SPを消費しないように修正（skill.c）
・AthenaProject Rev.134よりmerge、thanks to Blazeさん
	-> 25地域のモンスター配置を最新版に微修正

----------------------------------------
//0416 [2007/11/17] by Cocoa

・0407以降、ID169以降のスキルが正常に動作しなかった不具合を修正（skill.c）

----------------------------------------
//0415 [2007/11/17] by Cocoa

・矢作成のサクライ新規材料追加（create_arrow_db.txt）

・セミコロン（;）が余計に付いてたので削除（status.c）

・dbフォルダ内のファイルで改行で終了していないものを修正
　（exp_guild.txt, exp_homun.txt, item_group_db.txt,
　　job_db2.txt, refine_db.txt, random/item_rjc2006.txt）

----------------------------------------
//0414 [2007/11/17] by Rayce

・AthenaProject Rev.125よりmerge、thanks to Blazeさん
　（battle.*, clif.c, pc.c）
	-> 「太陽と月と星の天使」実装
	-> battle_confに「太陽と月と星の天使」の発動確率を設定する項目を追加

・@resethateで太陽と月と星の憎悪をリセットしてもキャラ永続変数が削除されないため、再びログイン
　すると元に戻ってしまっていた問題を修正（atcommand.c）

----------------------------------------
//0413 [2007/11/16] by Rayce

・AthenaProject Rev.119より、暫定的にLv11以上のメテオストームの効果範囲を拡大する（skill.c）
	thanks to RINさん

・AthenaProject Rev.120より以下の項目をmerge、thanks to Blazeさん
　（battle.*, skill.c, status.c）

	-> heal_counter_stopを廃止
	   Mob独自オーバースキルの発動Lvを設定する「monster_skill_over」を追加
	-> 「ファイアーボール」「サイトラッシャー」「ツーハンドクイッケン」のオーバースキル効果を実装

　　※conf/battle_auriga.conf に追加された monster_skill_over のデフォルトは11です。
　　　AthenaProjectとは違いますので注意してください。
　　　AthenaProjectのようにデフォルトを10にしてしまうと、通常効果としてのスキルLv10を使用する
　　　ことができなくなってしまうためです。
　　　そのためAthenaProject Rev.120におけるdb/mob_skill_db.txtの更新はmerge対象から外しました。

----------------------------------------
//0412 [2007/11/16] by Rayce

・AthenaProject Rev.113より、初心者修練場の追加職説明の終了処理を修正（npc_job_00novice.txt）
	thanks to Blazeさん

・AthenaProject Rev.123よりmerge、thanks to Blazeさん（skill.c, skill_cast_db.txt）
	-> NPCスキル「アイスブレス」に凍結効果を付与
	-> NPCスキル「アシッドブレス」の毒付与判定式を追加

・各種NPCファイル、およびアイテム/ペット/ホム/傭兵データベースにおいて、１行当たり読み込める
　最大文字数を1019から4095文字に拡張（homun.c, itemdb.c, merc.c, npc.c, pet.c）

----------------------------------------
//0411 [2007/11/16] by Rayce

・0397以降、PC以外がポーションピッチャーを使うとnullpoエラーが出る致命的なバグを修正（skill.c）
・0292で致命傷状態を実装した際、skill_fix_heal() の仕様が間違っていた問題を修正
　（battle.c, skill.*）
	他人にヒールをかけるとき、相手ではなく自分が致命傷のときにHP回復低下が発生したり
	など、各種ヒール計算が根本的におかしくなってました

----------------------------------------
//0410 [2007/11/16] by Rayce

・AthenaProject Rev.112およびeAthenaを参考に以下を実行、thanks to Blazeさん
　（clif.c, map.h, pc.c, skill.*, status.*, unit.c）

	-> 「穏やかな休息」「楽しい休息」の効果を「周囲にテコン系列キャラクターが座っている状態」
	   のみ発動するように修正
	-> テコン休息とギャングスターパラダイスのコードを共有するために skill_gangsterparadise() を
	   skill_sit() に変更
	-> テコン休息中のdoridori追加効果値を修正
	-> 「楽しい状態」の実装
	   確率的にSP10消費する代わりにアーススパイクスクロールの消費が無しになる
	   ただし battle_auriga.conf の item_res がnoときは意味がない
	-> 暫定で205をSI_HAPPYとして使う

----------------------------------------
//0409 [2007/11/16] by Rayce

・AthenaProject Rev.105よりmerge、thanks to Forestさん
	-> MAP名のミスにより、タナトスタワー入り口のMAPでワープポータルメモが取れて
	   しまっていた不具合修正（mapflag.txt）

・AthenaProject Rev.108およびRev.109よりmerge、thanks to allegroさん
	-> 神器クエスト内、#Brysinggamenにてgmcommandが使われていた部分をemotionに変更
	-> 神器クエスト内、書類管理人内に余分な部分が有った物を削除

・PACKETVERが10以上のとき、ギルド倉庫の装備品リスト用のバッファサイズを修正（clif.c）
・0408を少し整形（battle.c, status.c）

----------------------------------------
//0408 [2007/11/16] by Cocoa

・AthenaProject Rev.99より一部merge、thanks to Blazeさん
	-> NPCスキル「インビジブル」の効果時間がskill_cast_dbの設定に関わらず、
	   5秒になっていたのを修正（status.c）

・AthenaProject Rev.106よりmerge、thanks to Forestさん
	-> 養子状態でアルケミスト試験を受け、転職を行うと
	   通常のキャラに再設定されてしまう不具合を修正（npc_job_18alchemist.txt）

・リフレクトシールドでアシッドデモンストレーションを反射できないように修正（battle.c）

・script_ref.txtの誤字修正

----------------------------------------
//0407 [2007/11/15] by Rayce

・AthenaProject Rev.95よりmerge、thanks to Blazeさん
	-> 初心者修練場に特殊一次職の説明を追加（npc_job_00novice.txt）
・AthenaProject Rev.96よりmerge、thanks to Blazeさん
	-> リヒタルゼンNPCに追加クエスト「レッケンベルのアルバイト」を実装（npc_town_lighthalzen.txt）
・AthenaProject Rev.97より部分的にmerge、thanks to Blazeさん
	-> NPCスキル「闇属性変化」と「念属性変化」のIDが入れ替わってたのを修正（skill.*）
	-> Ep10.3～Ep11.2までのMob使用スキルを本鯖準拠に更新

----------------------------------------
//0406 [2007/11/15] by Rayce

・AthenaProject Rev.94よりmerge、thanks to Blazeさん
	-> ID338～354の第二期NPCスキルの宣言名、IDを本鯖と同期
	   エフェクトを正常表示するように（skill.*）
	-> ID変更に伴い、「不死属性付与」「取り巻き呼び戻し」「後退」「インビジブル」の使用Mobの
	   スキルを修正（mob_skill_db.txt）
	-> NPCスキル判断定義に第三期NPCスキルを追加（skill.c）

・0405における最大攻撃速度のデフォルト値変更がbattle.cに反映されてなかったので修正（battle.c）

----------------------------------------
//0405 [2007/11/15] by Cocoa

・AthenaProject Rev.111よりmerge、thanks to Rohypnolさん
	ソウルバーン前提スキルをスペルブレイカーからディスペルに修正(skill_tree.txt)

・プレイヤーとモンスターの最大攻撃速度のデフォルト値を190に修正（battle_auriga.conf）

・植物栽培で生成された植物が5分で消滅するように修正（skill.c, skill_cast_db.txt）

----------------------------------------
//0404 [2007/11/15] by Rayce

・AthenaProject Rev.89を参考に、獲得経験値の上限設定の仕様を変更（battle.c, pc.c）
	thanks to Blazeさん

	conf/battle_auriga.conf の next_exp_limit の使い方を変更します。
	next_exp_limitの値が0以下の場合は本鯖仕様の制限が適用されます。
	（現Lvから次Lvへの総必要経験値分×2 - 現経験値 - 1）
	それ以外の値の場合は従来通り%表記で制限します。
	AthenaProjectとは仕様が異なるので注意してください。

・AthenaProject Rev.91を参考に、ホムにも獲得経験値の上限設定を適用するように修正（homun.c）
	thanks to Blazeさん

・スクリプトの "set BASEEXP,???;" や @コマンドの "@writevars BASEEXP ???" 等で多量の経験値を直接
　得る場合、現在Expが100%を越えてLvUpしなかったのを修正（pc.c）

----------------------------------------
//0403 [2007/11/15] by Rayce

・Webチャットのメッセージ履歴をリングバッファにし、memmoveしないように改善（clif.c）
・@mesと@meswebの効果を区別するように変更（atcommand.c, clif.*）
	@mesは全てのプレイヤーに対してメッセージを送信するだけで、Webサーバとはチャット
	しなくなります。
	@meswebが従来の@mesと同様になり、Webチャットに反映されます。
	Webチャットを使わずに全体発言だけ行いたい場合は@mesを使った方が処理が速いです。

----------------------------------------
//0402 [2007/11/14] by Rayce

・AthenaProject Rev.82よりmerge、thanks to Blazeさん
	-> ラヘル～ベインス追加マップの水位を設定（conf/water_height.txt）
	-> ベインス追加マップのマップフラグを設定（mapflag/mapflag.txt）

・AthenaProject Rev.83よりmerge、thanks to Blazeさん
	-> ベインス追加ワープリンクの追加（タウン、ダンジョン、フィールド）

・AthenaProject Rev.84よりmerge、thanks to Blazeさん
	-> ベインスクエスト関連アイテムの特殊フラグを設定

・AthenaProject Rev.85よりmerge、thanks to Blazeさん
	-> ベインスNPC実装
	-> ベインスクエスト4種実装
	-> ベインスにジョンダ職員NPC追加
	-> ベインスに案内要員NPC追加
	-> ベインスに宿屋NPC追加

・AthenaProject Rev.86よりmerge、thanks to Blazeさん
	-> ベインスモンスター配置変更点を修正
	-> ベインスフィールド、トール火山ダンジョンのモンスターを実装

・AthenaProject Rev.87よりmerge、thanks to Blazeさん
	-> map_athena.confをベインスに対応、最新情報に更新

----------------------------------------
//0401 [2007/11/14] by Rayce

・AthenaProject Rev.69を参考に@homtalkを実装（atcommand.*）
	thanks to Quaplaさん

・AthenaProject Rev.73を参考に日本語の誤字脱字を修正（doc/item_bonus.txt）
	thanks to izayoiさん

----------------------------------------
//0400 [2007/11/14] by Rayce

・AthenaProject Rev.67よりmerge、thanks to Blazeさん
	-> 「SPEARQUICKEN」と「SPEARSQUICKEN」で名称が一致していなかったのを修正（pc.c, skill.c, status.*）
	-> 状態異常「石化進行中」の持続時間をストーンカース以外は1000msに修正（skill.c, status.c）

・ホムや傭兵にはキリエエレイソンが適用されるように0398を修正（skill.c）

----------------------------------------
//0399 [2007/11/14] by Cocoa

・AthenaProject Rev.113よりmerge、thanks to Blazeさん
	-> TheSignNPCで入力が文字列で判定が数値型になっていたのを修正（npc_quest_thesign.txt）
	-> アルベルタのTheSign関係NPCが重複していたのを削除（npc_town_alberta.txt）
	-> コモド武器商人の販売商品を正常化（npc_town_comodo.txt）

・AthenaProject Rev.104よりmerge、thanks to Forestさん
	-> 龍之城 武器商人NPCが販売している「パイク」がS4だったものをS3に修正（npc_town_louyang.txt）

----------------------------------------
//0398 [2007/11/14] by Cocoa

・一部モンスターが召還する取り巻きの数が異なっていた点を修正（db/mob_skill_db.txt）
・モンスターにはキリエエレイソンが適用されないように修正（skill.c）

----------------------------------------
//0397 [2007/11/14] by Rayce

・AthenaProject Rev.65よりmerge、thanks to Blazeさん
	-> NPCスキル「アシッドブレス」の属性を毒に、毒付与効果を追加
	   （skill_cast_db.txt, skill_db.txt, skill.c）

・AthenaProject Rev.66を参考に修正、thanks to Blazeさん
	-> ストーンスキン、アンチマジックの効果時間をスキルLvに関わらず30秒に固定（skill_cast_db.txt）
	-> 新モンスタースキルについてskill_db.txtを修正
	-> モンスターがポーションピッチャーでHP回復する場合でも致命傷による回復低下が発生
	   するように修正（skill.c）

----------------------------------------
//0396 [2007/11/14] by Rayce

・AthenaProject Rev.58を参考に、一般的な配布形式に合わせるため
　LICENCE(_JA)をCOPYING(_JA)にリネーム
	thanks to mizukiさん

・AthenaProject Rev.75を参考に、各ソースにGPLのライセンス表記を追加
	thanks to mizukiさん

----------------------------------------
//0395 [2007/11/14] by Cocoa

・db/const.txtからSC_ItemDelayを削除
・0336以降、露店からアイテムを購入出来なくなっていたバグを修正（vending.c）

----------------------------------------
//0394 [2007/11/14] by Rayce

・サーバースナップショット（version.h）
・0393で移動したランダム系アイテムをdb/フォルダから削除

----------------------------------------
//0393 [2007/11/14] by Rayce

・db/mob_db.txtおよびdb/mob_skill_db.txtを最新まで更新、thanks to huge cgi
・ランダム系アイテムのデータベースをdb/random/内に移動する
	based on Freya

----------------------------------------
//0392 [2007/11/13] by Rayce

・AthenaProject2322より、battle_auriga.confに homun_rename を追加（battle.c, homun.c）
	thanks to Quaplaさん

・db/const.txtにSC_PROVOKEとSC_BLESSINGを追加
・db/item_db.txtを最新まで更新、thanks to huge cgi

----------------------------------------
//0391 [2007/11/13] by Rayce

・db/skill_require_db2.txtには設定項目があるスキルだけを列挙するように変更
・db/packet_db.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0390 [2007/11/13] by Rayce

・AthenaProject2321より以下をmerge、thanks to Blazeさん
	-> NPCスキル、モードチェンジ「NPC_EMOTION_ON」実装（skill.*, status.*, skill_db.txt）
	-> トムヤンクンクエストの一部不具合でクエストが進行しなかったのを修正
	   （npc_town_ayothaya.txt）

----------------------------------------
//0389 [2007/11/13] by Rayce

・AthenaProject2321より内部処理名称変更をmerge、thanks to Blazeさん
	SC_STAN → SC_STUN
	SC_HOLDWEB → SC_STOP
	SI_HOLDWEB → SI_STOP
	NPC_EXPLOSIONSPIRITS → NPC_POWERUP
	NPC_INCREASEFLEE → NPC_AGIUP
	NPC_ELEMENTUNDEAD → NPC_CHANGEUNDEAD
	NPC_DARKSOULSTRIKE → NPC_DARKSTRIKE
	NPC_RUNAWAY → NPC_RUN
	NPC_DARKGRANDCROSS → NPC_GRANDDARKNESS
	NPC_DARKJUPITEL → NPC_DARKTHUNDER

----------------------------------------
//0388 [2007/11/13] by Rayce

・inter_send_packet_length[] は使われていないので削除（inter.c）
・Lv11以上のカイゼルを使うと、復活時にHPが最大HPを越える可能性を修正（pc.c）
・map_readwater() を少し最適化（map.c）

----------------------------------------
//0387 [2007/11/11] by Rayce

・プレッシャーおよびグラビテーションフィールドがセーフティウォールやエナジーコート等あらゆる
　バリアを無視して固定ダメージを与えるように修正（battle.c）

・プレッシャーを武器スキル（BF_WEAPON）からその他スキル（BF_MISC）に変更してみる（battle.c, skill.c）
	based on eA, thx a lot!!

----------------------------------------
//0386 [2007/11/11] by Rayce

・0336以降、他人の露店を見ることができなくなっていたバグを修正（vending.c）
	reported by Cocoaさん

・VC8.0以上のときはstrdupの代わりに_strdupを使うように修正（malloc.h）
・battle_skill_attack() を少し最適化（battle.c）
　if-elseをswitchにすることでswitch tableの形成を促す

----------------------------------------
//0385 [2007/11/10] by Rayce

・0313以降、ソウルリンカーの転職できなくなっていたバグを修正（pc.c）
	reported by Cocoaさん
・スフィアーマインを強制的に水属性Lv2に修正（skill.c）
	reported by Cocoaさん
・カタール装備時、左手の追撃分が常にMissになるバグを修正（battle.c）
	reported by Cocoaさん

・左手にのみ武器を装備している状態で武器スキルを使う場合は右手のみを参照するように修正（battle.c）
	merged from eA, thx a lot!!

----------------------------------------
//0384 [2007/11/10] by Rayce

・BCCのとき、atn_bignumber型は__int64型ではなくdouble型を使うように戻す（utils.h）
	reported by Cocoaさん

	0153での変更を巻き戻します。
	__int64型の二項代入演算を行うと極稀に予期せぬ演算結果が返る特有のバグがある模様。
	BCCの__int64型は不安定要素が多いので使わないようにします。
	double型に戻したことにより演算速度と精度の低下が発生します。
	BCCを使う方はその点を留意しておいてください。

・mob_dead() を少し最適化（mob.c）

----------------------------------------
//0383 [2007/11/10] by Rayce

・レディムプティオを本鯖仕様に修正
	reported by Cocoaさん

	-> スキル発動時は死亡するのではなくHP1, SP0になる
	-> 効果範囲を15x15から29x29に修正
	-> オーラの場合、経験値がオーラレベルに必要な経験値の1%以下ならスキル失敗
	-> オーラの場合、発動時には取得経験値の1%を基準としてExpペナルティが発生する
	-> ペナルティは街中でも発生する

　　※以下変更箇所
	-> conf/battle_auriga.confの redemptio_penalty_type の仕様変更（battle.c）
	   デフォルトは1、誰も生き返らないときだけHP/SP/Expペナルティ無し設定
	-> skill_redemptio() を撤廃（skill.c）
	   party_foreachsamemap() は再帰的に skill_castend_nodamage_id() を呼ぶだけ
	-> SC_REDEMPTIOを撤廃（skill.c, status.*）
	-> pc_exp_penalty() の拡張（pc.*, skill.c）
	   レディムプティオのExpペナルティにも適用できるように

・buildin_repairitem() を少し修正（script.c）
	reported by Cocoaさん

・conf/battle_auriga.confの death_penalty_type のデフォルトを3に変更しておく（battle.c）

----------------------------------------
//0382 [2007/11/07] by Rayce

・ルート属性を持つMOBがルート属性を持たない取り巻きを召喚すると、取り巻きがアイテムを
　ターゲッティングしてしまうため "mob_ai_sub_hard target type error" となるバグを修正（mob.c）
	reported by Cocoaさん

・mob_spawn() 時に行うルートアイテムの初期化サイズが間違っていたので修正（mob.c）
・ソウルバーンが黄金蟲カードで無効化されるように修正（skill.c）
・サクリファイス中にエンペリウムを攻撃したときは攻撃回数が減少するように修正（battle.c）

----------------------------------------
//0381 [2007/11/06] by Rayce

・報告された項目について修正
	reported by Cocoaさん

　　-> プレイヤー以外が混乱状態になると歩行時にサーバクラッシュするバグを修正（unit.c）
　　-> カートターミネーションのダメージ倍率がカートの最大重量にのみ依存していたのを修正（battle.c）
　　-> アシッドデモンストレーションがエナジーコートを貫通するように修正（battle.c）
　　-> ボス属性はランドプロテクター上でもテレポートできるように修正（battle.*, skill.c）
　　   battle_auriga.confに boss_teleport_on_landprotector を追加
　　   デフォルトではyes、jRO 2007/10/30以前の旧仕様にしたい場合はnoに設定すること

----------------------------------------
//0380 [2007/10/27] by Rayce

・PT加入時に他のメンバーのHPバーが即座に更新されるように修正（party.c）

・コンパイルオプション -Wc++-compat で警告が出る部分を修正（login.c）
・コンパイルオプション -pedantic における警告の中で気になった箇所を修正（malloc.c, socket.c, db.h）

----------------------------------------
//0379 [2007/10/27] by Rayce

・スクリプトエンジンの若干の最適化（script.c）
	-> 条件分岐はif-elseではなく出来るだけswitchを使うように変更
	   コンパイラのオプティマイザによってswitch tableが形成されることが期待できるため
	-> バイトコードに直接命令を書き込む場合は add_str() ではなく search_str() を使う
	-> function構文の終わりに自動的に付加するreturn命令は parse_line() を経由せずに
	   バイトコードに直接書き込むように改善
	-> parse_syntax() での skip_word() は各case内で行うように改善
	-> doの閉じ判定時に skip_space() が一つ不要だったので削除
	-> push_val() および push_str() でスタックを拡張する際のmemsetを省略

----------------------------------------
//0378 [2007/10/26] by Rayce

・スクリプトエンジンの {} 閉じ関連について機能強化（script.c）

　　１．breakやcontinueの後でif, for, whileが閉じるとき、直後に命令が連結していると解析エラーと
　　　　なるバグを修正
　　　　以下の例文は今後正常なコードとして扱われます。
		while(1)
			break;next;	// スペースを入れずいきなり命令があるとアウトだった

　　２．if(); や do; を閉じるとき、続けてelseやwhileが置けなかったバグを修正
　　　　以下の例文は今後正常なコードとして扱われます。
		if(rand(2));		// if(); が正しく閉じられてなかった
		else
			mes "hoge";

　　３．function構文の関数宣言だけを行った場合、if, for, whileが閉じられないバグを修正
　　　　以下の例文は今後正常なコードとして扱われます。
		if(rand(2))
			function test;
		else
			mes "hoge";	// ifが終わってないのでelseが失敗していた

　　４．function構文の関数定義を閉じるとき、} の直後に命令が連結していると解析エラーと
　　　　なるバグを修正
　　　　以下の例文は今後正常なコードとして扱われます。
		function test {
			mes "hoge";
		}next;	// スペースを入れずいきなり命令があるとアウトだった

　　５．funciton構文で関数定義を行うとき、関数名のあとに { を付けることを強制するように変更
　　　　以下の例文は今後エラーとして扱われます。
		function test		// { がない定義
			mes getarg(0);
		test "hoge";

----------------------------------------
//0377 [2007/10/26] by Rayce

・0374以降、歩行経路計算が狂っていたバグを修正（path.c）
・gccコンパイル時の警告抑制（graph.c, atcommand.c）

----------------------------------------
//0376 [2007/10/24] by Rayce

・コンパイルオプション -Wshadow を参考に、変数indexをidxに改名
・Makefileでgccのversionの自動取得が正しく行われない場合があるので修正

・SQL: atoiのwarningを修正（int_mail.c）

----------------------------------------
//0375 [2007/10/22] by Rayce

・コンパイルオプション -Wredundant-decls を参考に、宣言が重複している以下の関数を削除
	guild_txt_delete()
	status_get_atk2()

・コンパイルオプション -Wold-style-definition で警告が出る部分を修正
　（inter.c, int_storage.c, pet.c, script.c）
・コンパイルオプション -Wunreachable-code を参考に、実行されないコードを部分的に修正
　（atcommand.c, script.c）
・コンパイルオプション -Wunused-macro を参考に、使われてないマクロを修正
　（int_guild.c, int_status.c）

----------------------------------------
//0374 [2007/10/22] by Rayce

・コンパイルオプション -Wshadow を参考に、変数のシャドーイングを出来る限り修正
・コンパイルオプション -Wwrite-strings を参考に、文字列リテラルに出来る限りconstを修飾する
・コンパイルオプション -Wmissing-declarations を参考に、一部の関数にstaticを修飾する

・conf/httpd.confで "target" の項目を指定してメモリ拡張が行われる際、拡張するべきサイズの
　計算が間違っていたバグを修正（httpd.c）
・マクロ sock() は紛らわしいので sockfd() に改名（socket.c）

----------------------------------------
//0373 [2007/10/22] by Rayce

・db/pet_db.txt, db/homun_db.txt, db/merc_db.txt のスクリプトを解析する際に
　バッファオーバーランが発生するバグを修正（pet.c, homun.c, merc.c）

・grfファイル検索用ハッシュテーブルのサイズをFILELIST_HASHとして定義、521に拡大（grfio.c）
・定数 FILELIST_ADDS を撤廃、grfio_add() は1つずつreallocするように変更（grfio.c）
・grfio.cの細かい整形

・char_make() の引数変更（char.c）
・定数 OPTION_MASK および CART_MASK をunsingedに修正（pc.h）
・存在しない関数 guild_read_db() の宣言を削除（guild.h）

----------------------------------------
//0372 [2007/10/21] by Rayce

・フォーマット付きメッセージ出力関数 msg_output() を追加（atcommand.c）
	出力用バッファを内包した clif_displaymessage() のラッパー関数。
	atcommand.c専用として使うのでstaticが付いてます。

・0371以降、@mapinfoの引数が省略できなくなっていたので修正（atcommand.c）

----------------------------------------
//0371 [2007/10/20] by Rayce

・@コマンドの各処理に渡されるmessageのNULLチェックを強化
・@コマンドの各処理におけるnullpoチェックを強化

・@item3でバッファオーバーランが生じる可能性を修正
・atcommand.cの全体的な細かい最適化および整形

----------------------------------------
//0370 [2007/10/20] by Rayce

・gccコンパイル時の警告修正（atcommand.c）
	atcommand_go()
	atcommand_param()

・0208以降、@ecoffが機能しなくなっていたバグを修正
・@mapflagでw4が不定になる可能性があるので空文字で初期化するように修正
・@produceで装備品以外のアイテムを指定した場合はメッセージが表示されるように改善
・@resetfeelおよび@resethateの配列サイズのチェックを修正

・@questskill, @charquestskill, @lostskill, @charlostskillでスキルIDの範囲チェックを省略
　範囲外だった場合は次の skill_get_inf2() の判定が偽になるので問題は無い
・@charquestskillおよび@charlostskillにおいて、クエストスキル以外のスキルIDを指定すると
　「そんな人は存在しません。」と表示されるバグを修正

----------------------------------------
//0369 [2007/10/19] by Rayce

・pc_authok() で位置の設定に失敗したときは未認証に戻して接続を切断するように修正（pc.c）
・clif_misceffect3() の引数を変更（battle.c, clif.*, script.c）
・@weatherを少し最適化（atcommand.c）

・@usersの書き直し（atcommand.c）
	-> users_dbを使用しない
	-> battle_auriga.confの hide_GM_session の設定を適用する
	-> 人数の割合は小数点第二位まで表示する

----------------------------------------
//0368 [2007/10/19] by Rayce

・バッファオーバーラン対策として、msg_txt() をフォーマットとして利用する場合は
　snprintfを使うように修正
　（atcommand.c, party.c, pc.c, ranking.c, skill.c, vending.c）

・細かい最適化（atcommand.c, chrif.c, pc.c）
	atcommand_add_hashtable()
	atcommand_mobsearch()
	atcommand_weather()
	atcommand_connectlimit()
	chrif_maintenanceack()
	pc_show_steal()

----------------------------------------
//0367 [2007/10/19] by Rayce

・ATCOMMAND_FUNC() の引数には文字列（const char）ではなくタイプ（AtCommandType）を渡すように変更
　これに合わせて以下のコマンドを修正
	@monster, @monstermap
	@kami, @kamib, @kamic
	@str, @agi, @vit, @int, @dex, @luk

・atcommand() を is_atcommand_sub() に統合
・atcommand_killmonster2() を atcommand_killmonster() に統合
・atcommand_raisemap() を atcommand_raise() に統合
・atcommand_doommap() を atcommand_doom() に統合

・@goにベインズを追加 merged from eA
・@goをマップ名の略式で指定できるように拡張
	gat名の頭文字から区別できる最小の文字数さえ合えば発動します。
	例えば以下の通り。
	　　@go pr    → プロンテラ
	　　@go i     → イズルード
	　　@go einbe → アインベフ
	これにより番号がわからなくてもマップ名さえ推測できていれば使えます。
	アインブログは南口にしか飛べませんが仕様とします。

----------------------------------------
//0366 [2007/10/19] by Rayce

・@コマンドのsynonymを高速化（atcommand.*）
　synonymを大量に作っても検索速度の極端な低下が起こらないよう改善されます
	-> synonym_tableの型をAtCommandInfoに変更
	-> synonymは実行時にコマンドを置換するのではなく登録時にコマンドをコピーしておく
	-> AtCommandInfo型のnextを配列のインデックスではなくポインタで扱う
	-> synonymのコマンドもハッシュテーブルに登録する
	   通常のコマンド同様 get_atcommandinfo_byname() が使えるので検索が速い
	-> @reloadatcommandの際、synonym tableだけをハッシュテーブルから削除するのは手間が
	   かかるのでハッシュテーブルを丸ごと初期化するように変更

・以下の関数について細かい最適化（atcommand.c）
	atcommand()
	is_atcommand_sub()

----------------------------------------
//0365 [2007/10/14] by Rayce

・Mobが自分より歩行速度の遅いPCを追跡する際、MOBがPCに対して１マス程度の間隔を開け続けて
　いつまでも追いつけない問題を暫定修正（mob.*, unit.c）
	reported by apacheさん

	歩行目的地に到着してもAIの実行時間になるまで次の行動が待機させられるため、
	その間にプレイヤーが移動しているとまた間隔が開いてしまうのが原因です。
	歩行目的地に到着した時点で直接AIを実行するように変更しましたが、場合によって
	はAIの実行頻度が高くなりすぎて処理上の負荷がかかる可能性が考えられます。
	もう少し良い方法が思い付き次第改善する予定です。

----------------------------------------
//0364 [2007/10/12] by Rayce

・ストリップ系スキルに関する修正
	reported by Cocoaさん

	-> ストリップシールド/アーマー/ヘルムはリログで解除されるように修正（scdata_db.txt）
	-> フルストリップの成功確率計算にDEX差が加味されてなかったのを修正（skill.c）
	-> 弓以外の両手武器はストリップシールドで外せないように修正（skill.c）
	-> ストリップシールドに掛かっていると両手武器が装備できなかったのを修正（pc.c）
	-> フルコート状態の対象にフルストリップを使った場合は失敗メッセージが出す（clif.h, skill.c）

----------------------------------------
//0363 [2007/10/12] by Rayce

・BLOCK_DATA_SIZE にunit_head構造体のサイズを加算するように変更（malloc.c）
	40948～40960byteのメモリをアロケートするとき、size2hash() では許容範囲内の
	ハッシュ値になるにも関わらずブロック長を超えるサイズとみなされてしまい、
	unit_head_large になる気持ち悪さを修正します。

・各ファイルにある memwatch.h のincludeを削除
　malloc.hに一括するので不要

----------------------------------------
//0362 [2007/10/12] by Rayce

・メモリマネージャにおいて、ユニットが全て埋まって空きが無いブロックに対してメモリリーク検出が
　行われない潜在的なバグを修正（malloc.c）
	unfill_prevがNULLのときは、「ブロックが空っぽ」「ブロックが満タン」の2つの状態の
	いずれかを意味します。
	したがってunfill_prevではブロックにまだユニットが残っているかどうかを判定すること
	はできません。
	代わりにunit_usedを見るように修正しています。

・timer.cの細かい整形（timer.c）
・一部の構造体のメンバを見直し（timer.h, battle.c, map.h, skill.*, status.*）

----------------------------------------
//0361 [2007/10/08] by Rayce

・PT未所属の状態でレディムプティオを使うと、周囲のPT未所属のプレイヤーを生き返らせることが
　出来たバグを修正（skill.c）
・レックスティビーナをShift押しで味方に使うと沈黙解除できるように修正（skill.c）
・pc_show_steal() を少し修正（pc.c）

----------------------------------------
//0360 [2007/10/08] by Rayce

・スーパーノービス関連の修正、thanks to Cocoaさん
　　-> レベルアップ時に受ける支援効果時間を全て120秒固定に修正（pc.c）

　　-> Lvが最大でも経験値がbattle_auriga.confの snovice_maxexp_border 以上であれば
　　   爆裂波動が発動するように修正（clif.c）

　　-> スーパーノービスの魂付与時に受ける無死亡ボーナスについて（status.c）
　　　　　　条件をBaseLevel90以上ではなくJobLevel70以上に修正
　　　　　　JobLevelが70未満でも死亡記録が削除されるように修正
　　　　　　JobLevelが70以上なら天使のエフェクトが出るように修正

　　-> スーパーノービスの妻が夫に「あなたに尽くします」を使用したとき、10%の確率で
　　   ステータス付与の効果が発現するように修正（skill.c, status.*）
　　　　　　状態異常 SC_WE_FEMALE を追加
　　　　　　アイコン SI_WE_FEMALE は暫定で102番を利用

・変数名の変更（battle.c）

----------------------------------------
//0359 [2007/10/07] by Rayce

・ペットがMAPから離脱するときに status_change_removemap_end() でnullpoエラーが
　発生するバグを修正（status.c）
	reported by Cocoaさん

・スーバーノービスの金剛について（battle.*, map.h, pc.c）
	thanks to Cocoaさん

	-> 経験値計算の過程でオーバーフローするため「Base経験値が99.0～99.9%」の判定が
	   失敗してしまうバグを修正
	-> Lvが最大でも経験値がbattle_auriga.confの snovice_maxexp_border 以上なら
	   何時でも金剛が発動するように修正
	   snovice_maxexp_border はいわゆるLv100状態に必要な経験値で、デフォルトは
	   99,999,999に設定されています
	-> スクリプトから set BASEEXP,100; のように経験値を獲得する場合、Lvが最大でも
	   経験値がセットされるように変更
	-> 金剛が発動するのはログイン後一度だけになるように修正

・BaseLevelが上がって最大になったとき、取得した経験値がそのまま加算されてしまうのを修正（pc.c）
・pc_checkbaselevelup() で status_calc_pc() が不必要に呼ばれないように修正（pc.c, status.*）

----------------------------------------
//0358 [2007/10/07] by Rayce

・傭兵が歩行するとサーバクラッシュする致命的なバグを修正（map.h）
・core_ExceptionRoutine() の細かい整形（core.c）

----------------------------------------
//0357 [2007/10/07] by Rayce

・パケット0x1c0の抑制（clif.c）
	langtypeが0だとログイン時に必ず送信されてくるようなので、ダンプ抑制のために
	clif_parse_GMcharge() を追加。
・eAの情報を元にパケット0x2b0をサポート（login.c）
	langtypeが0のときの非暗号化ログインパケットのようです。

・リジェクトソードの効果が死亡時に解除されないように修正（scdata_db.txt）
・クローキング中にアイテムを拾おうとすると、以後アイテムが拾えなくなるバグを修正（clif.c）
・チェイスウォーク中はアイテムを拾えるように修正（clif.c）
・白刃取りはPvP以外では2セル以上離れている場合は掴めないように修正（battle.c）

----------------------------------------
//0356 [2007/10/06] by Rayce

・ガンスリンガーと忍者の基本HP/SPを本鯖通りに合わせる（status.c）
	reported by Cocoaさん

	ガンスリンガーと忍者の基本HP/SPは個別に設定されているのか、JOB係数/倍率を用いて
	一意的に計算することができないようです。
	job_db1.txtのhpおよびspの項目を-1にするとjob_hp_db.txtおよびjob_sp_db.txtの値を
	基本HP/SPとして設定するように拡張しました。
	他の職業でも-1にしておくことでJOB係数/倍率に縛られることなく個別に基本HP/SPを
	設定することも可能です。

　　※ガンスリンガーと忍者について、Lv100以上の場合は以下のJOB係数/倍率を用いてLv255まで
　　　値を外挿してあります。
　　　　　ガンスリンガー：基本HP係数 85, 基本HP倍率 350, 基本SP係数 430
　　　　　忍者　　　　　：基本HP係数 75, 基本HP倍率 350, 基本SP係数 470

・0349以降に発生していたgccでのwarning修正（map.h）
・事故防止のためSQLモードでは@callmercが使えないように変更（atcommand.c）
	傭兵はまだ整備が完了してないため現状ではTXTモードのみ
	動作確認のために利用を許可しているに過ぎません

----------------------------------------
//0355 [2007/09/30] by Rayce

・aReallocのサイズ縮小対応（malloc.c）
　aReallocにサイズ0を指定した場合はaFreeと同様に機能するように修正

・aCallocをaMallocに修正（script.c）
・スクリプトの解析時に "missing right curly" エラーとなる場合は1を返すように修正（npc.c）

----------------------------------------
//0354 [2007/09/29] by Rayce

・スクリプトコンパイルエラー時の処理を変更（npc.c）
　以下のエラー時にはサーバ終了扱い（compile error）せずに警告扱い（warning）にして
　出来る限り解析を続行する

	-> map_auriga.confで指定したスクリプトが見つからない場合
	-> "Missing */ on ???" の警告が出る場合
	-> NPCスクリプトのヘッダがsyntax errorになった場合
	   その行以下の部分は全て捨てられるが、残りのファイルの解析は続行
	-> script構文の解析途中でエラーが発生した場合
	   その行以下の部分は全て捨てられるが、残りのファイルの解析は続行
	-> function構文で関数名の重複が起こった場合
	   そのスクリプトだけ無効になるが、残りのスクリプトの解析は続行される

　　※イベント名の重複が発生したときのみサーバ終了（compile error）となります。
　　　既にNPCが出現した後に発生するエラーであり、そのためイベントデータベースへの登録が中途半端な
　　　状態になってしまうためです。

　　※あくまでもサーバ終了されないだけで、警告時には部分的にデータの整合性が失われている可能性が
　　　あります。
　　　一度サーバを停止してからスクリプトを正常に修正することをお勧めします。

・npc_convertlabel_db() の改善（npc.c）

----------------------------------------
//0353 [2007/09/29] by Rayce

・script_code構造体を "struct hack" で利用するように変更してみる（script.*）
	script_bufがreallocで縮小されない分とcalloc用のヘッダの分だけメモリが削減されます
	全てのスクリプトを読み込ませて約1.5MB節約

・scriptlabel_dbはtree_dbにする意味があまりないのでlinkdbに変更（npc.c, script.*）
	npc_convertlabel_db() を変更
	アクセスが面倒なので script_get_label_db() を廃止して scriptlabel_db をexternする
	ラベルデータのコンバートが完了した時点で linkdb_final() してメモリ解放する

・0348以降、SC_SoulClearなどの特殊系ステータス異常が作動しなくなっていたので修正（status.c）
・mob_data構造体のメンバ recallmob_count をint型からshort型に変更（map.h）

----------------------------------------
//0352 [2007/09/28] by Rayce

・block_list構造体のsubtypeをnpc_data構造体に移動（map.h）
	subtypeはNPCにしか意味がないのでnpc_data構造体が持つだけで十分
	またblock_list構造体のサイズが傭兵実装以前に戻ったのでメモリの消費が抑えられます

・csvreload命令の処理を改善（script.c）
	file名のaStrdupではなくcsv_dataのfileをキーとする
	script_csvreload_sub() は不要になったので削除

・skill_condition型の変数名を改名し忘れ箇所を修正（skill.*, unit.c）

----------------------------------------
//0351 [2007/09/28] by Rayce

・切断待ちのプレイヤーは chrif_save() でセーブしないように修正
	切断待ちの間にセーブが行われると最終データが不正に上書きされるバグが修正されます。
	これはeAの finalsave による二重呼び出しのブロッキングと同じ手法です。

----------------------------------------
//0350 [2007/09/27] by Rayce

・battle_auriga.confに free_sc_data_dynamically を追加（battle.*, status.c）
	DYNAMIC_SC_DATAが有効のときに効果があります。
	yesにすればステータス異常の数が0になった時点でメモリを解放しますので、メモリの使用量を
	さらに減らすことができます。
	動的確保するメリットの薄かったプレイヤーに対しても効率良くメモリを利用できるようになる
	可能性があります。
	ただし頻繁にステータス異常にかかるような状況だと若干ですが負荷が増えるかもしれません。

・0349に変更によってhideonnpc/hideoffnpc命令が作動しなくなっていたので修正（clif.c）
・関数にstaticを付ける（chrif.c, intif.c）

----------------------------------------
//0349 [2007/09/27] by Rayce

・status_change構造体の変更 merged from eA, thanks
	ステータス異常の数やoption系を一つにまとめます。
	data部分はstatus_change_data構造体として再定義します。
	status_get_sc_count() や status_get_option() などが不要になるため、関数呼び出しの
	オーバーヘッドが減るなどの利点があります。

	PC, HOM, MERCのstatusにあるoptionとstatus_changeのoptionが重なりますが、MAPサーバでは
	全てstatus_changeのoptionを参照します。
	セーブの直前にstatusにコピーしてcharサーバに送ります（statusのoptionは通信用の受け皿）。

・プレイヤー、ホム、傭兵にもDYNAMIC_SC_DATAによるステータス異常の動的確保を適用する
	status_change構造体の変更に伴う副作用により、動的確保せざるを得なくなりました。
	特にプレイヤーは頻繁にステータス異常に掛かる可能性が高いため動的確保するメリットは
	薄いですが、デメリットもほとんどないため問題ないと考えました。

・status_calloc_sc_data() および status_free_sc_data() の引数をstatus_change型に変更
・status_get_sc_data() を status_get_sc() に改名（status.*）
・status_check_dummy_sc_data() はあまり意味がないので削除（status.*）
・npc_data構造体から使われていないメンバ opt1, opt2, opt3 を削除（map.h, npc.c）

----------------------------------------
//0348 [2007/09/26] by Rayce

・水遁のAGIペナルティ計算式を一般式化（skill.c）
・カイトの反射回数計算を一般式化（status.c）
・ボルケーノ、デリュージ、バイオレントゲイルでスキルLvが5より大きいとき、ボーナス値の計算を
　Lv5でキャップするように修正（status.c）

・status_change_timer_sub() にスキルLvを渡すように引数追加（skill.c, status.c）
・0346の @option と同じように @charoption も修正（atcommand.c）
・一部の紛らわしい変数名を改名（skill.c）

・ステータス異常呼び出し時にtypeがMAX_STATUSCHANGEを越えていないかチェックするように強化（status.c）
・ステータス異常が利用可能かどうかの判定はsc_dataがNULLかどうかで行うように変更（status.c）
・sc_dataのNULLチェックが不要な部分を省略

----------------------------------------
//0347 [2007/09/25] by Rayce

・mob_spawn() の呼び出しに関して（mob.c）
	MOBがMAP上に存在している状態でいきなり mob_spawn() を行ってはいけません！
	map_delblock() されないためブロックリストが異常になったり、ステータス異常が勝手に
	初期化されてステータス異常タイマーがエラーになったりするバグが発生してしまいます。

	-> MOBがAIが手抜きモードで同一MAPにPCが居るとき、時々沸き直していたのを廃止
	   本鯖には特にそのようなシステムはないはず
	-> mob_randomwalk() で移動可能場所の検索に失敗したとき、沸き直さずにPETと同じく
	   移動停止状態にするように修正

・dummy_sc_dataはDYMANIC_SC_DATAがオンのときだけコンパイルするように変更（status.*）
・int_status.hで定義しているstatus_change_data構造体をscdata構造体に改名
　（int_status.*, inter-converter.c）

----------------------------------------
//0346 [2007/09/25] by Rayce

・パケットに0x28a関する修正 from eA
　（atcommand.c, clif.*, merc.c, status.c）
	0x28aは傭兵出現パケットではなく、0x229では出来ないopt3の更新を行うためのパケットでした。
	clif_send_mercdata() を削除し、clif_changeoption2() に変更
	これにより @option を使ったときにopt3による見た目の変更が即座に反映されます。

・clif_mercskillinfoblock() を clif_send_mercstatus() 内にまとめる
　（clif.c, merc.c, skill.c, statuts.c）

----------------------------------------
//0345 [2007/09/24] by Rayce

・path.cの全体的な細かい整形、can_place() をマクロに変更（path.c）
・Makefileを少し修正

----------------------------------------
//0344 [2007/09/24] by Rayce

・0341で混入したホムと傭兵のスキルツリー計算の致命的なバグを修正（homun.c, merc.c）
・プレイヤー、ホム、傭兵のスキルツリー読み込み時にスキルIDの範囲チェックを行うように修正
　（pc.c, homun.c, merc.c）
・hacker対策として256文字以上のチャットメッセージは受け取らないように強化（clif.c）

・チェンジインストラクションの修正（homun.c）
	-> ステータスアップの計算を一般式化
	-> INT増加が間違っていたので以下のように修正
	     Lv1: +1, Lv2: +2, Lv3: +2, Lv4: +4, Lv5: +5

・メンタルチェンジの修正（battle.c, homun.c, skill.c, status.c, db/skill_require_db.txt）
	-> VITとINTがスキルLvに比例して加算されるように修正
	-> MAXHPとMAXSPの交換が行われないように修正
	-> ATKとMATKの交換が行われないように修正
	   マジッククラッシャーと同じくMATKで攻撃を行う
	-> 効果時間中は治療の手助けと緊急回避が使えないように修正
	-> 効果が切れたときHPとSPが10になるように修正
	   MAP移動などで効果が中断されたときはこのペナルティを受けない
	-> 消費SPを 1 → 100 に修正

・battle_auriga.confに homun_skilldelay_reset, homun_statuschange_reset を追加
　（battle.*, status.c, unit.c）
	マップ離脱時（テレポ、マップ移動など）にスキル使用後ディレイやホムスキル効果による
	ステータス異常をリセットするかどうかを設定できます。
	デフォルトでは共にyesでリセットされます。

　　※将来的に、マップ離脱時にステータス異常を解除するかどうかの制御はdb/scdata_db.txtで
　　　行えるように変更するかもしれません。
　　　そのときは homun_statuschange_reset は削除します。

----------------------------------------
//0343 [2007/09/23] by Rayce

・delay_item_dropおよびdelay_item_drop2構造体に保存するアイテムルート優先者の情報は、block_list型ではなく
　int型でIDだけを保存するように修正（map.*, mob.c, pc.c, pet.c, script.c, skill.c）
	partially merged from eA, thanks

	MOBを倒したときのドロップアイテムが出現するまでの間（約500ms）にルート優先者がMAPから
	消滅していると、既にfreeされた領域にアクセスしてしまう致命的なバグが修正されます。
	それに付随して map_addflooritem() の引数をint型に変更しています。

----------------------------------------
//0342 [2007/09/23] by Rayce

・マップ離脱時に解除すべきステータス異常を status_change_removemap_end() としてまとめる
　（clif.c, pc.c, status.*, unit.c）
・ホムスキルから発生するステータス異常はマップ離脱（テレポやMAP移動）で解除されるように修正（status.c）
・MAPロード時に行っていたシグナムクルシス状態のチェックは無くても問題ないので削除（clif.c）
・status_change_clear() でダンス状態とバジリカ状態の削除を考慮するように修正（status.c）

・表示をスムーズにするため hex_dump() を自前の完全バッファリングにする（utils.c）
・doc/client_packet.txt更新

----------------------------------------
//0341 [2007/09/23] by Rayce

・soundeffect命令、areasoundeffect命令で繰り返しサウンドを鳴らす場合、間隔をミリ秒で指定できる
　ように拡張（clif.*, script.c）
	clif_soundeffect() で不明だった部分は実は時間間隔を設定する機能があった模様。
	効果があるのは繰り返し鳴らす場合のみです。

・0336以降、チャットに入れない場合があるミスを修正（chat.c）
・hex_dump() 呼び出し時の余計なキャストを削除（char.c, login.c. clif.c）
・ホムと傭兵のスキルツリー計算をPCの処理方法に合わせる（homun.c, merc.c）
　battle_auriga.confのskillfreeをホムと傭兵にも適用する

----------------------------------------
//0340 [2007/09/21] by Rayce

・0339のitem_db.txtのType変更により、Rの箱系が使用できなくなっていたので修正（pc.c）
・pc_putitemtocart() および pc_getitemfromcart() から露店かどうかのチェックを外す（pc.c）
　チェック自体は既にclif.cで行っているので不要
・packet_dbのposのサイズを 20 → 8 に縮小（clif.h）
・packetdb_readdb() を少し修正（clif.c）

・ROメールに別のアイテムやZenyを添付しようとすると表示上戻ってこない問題を修正
　（clif.c, intif.c, mail.*, pc.c, trade.c, unit.c）
	0337で添付成功のパケットとして0x255を使うようにしたため、メールに貼り付けたアイテムを
	戻したりするときに clif_additem() を送り付けないといけなくなりました。
	インベントリのインデックスを保存する必要があるため、全体的な処理を取引と同じ方法に変更
	することにしました。
	アイテムを添付した時点で mail_appending フラグがオンになります。
	mail_appending中は取引と同じくアイテムに関連する行動が全て制限されます。

　　※本来はメールボックスを開いた時点でフラグを立てて行動制限するべきですが、メールを閉じたとき
　　　を判定する術がない（0x246は送信ボックスの開閉両方で飛んでくる）ため、添付アイテムがあるとき
　　　だけチェックを行う形をとっています。

----------------------------------------
//0339 [2007/09/20] by Rayce

・db/item_db.txtのTypeを本鯖仕様に修正（clif.*, itemdb.c, pc.c）
	矢は10、弾丸は16、苦無は17、Rの箱は18、で分類されます。
	これによりRの箱系を使用すると開封していいかどうかの確認ダイアログが出るようなります。

・上記変更に合わせて db/item_db.txtを修正、ついでに最新まで更新
	thanks to huge cgi

・0311以降、ファイアピラーなどでnullpoエラーが誤検出されるバグを修正（skill.c）
・ファイアピラー発動後に呼び出す battle_skill_attack_area() の引数が間違っていたので修正（skill.c）
・hex_dump() の改行コードを RETCODE に変更（utils.c）

----------------------------------------
//0338 [2007/09/20] by Rayce

・パケットのダンプ時に文字も表示するように改善 from eA（utils.*, login.c, char.c, clif.c）
	hex_dump() 追加
	特に@packetの出力フォーマットがより見やすい形になってるはず

----------------------------------------
//0337 [2007/09/19] by Rayce

・086以降、緊急回避とディフェンスのスキル使用後ディレイが無くなっていたのを修正（skill.c）
・clif_receive_mail() でバッファオーバーフローが発生する可能性を修正（clif.c）
・ROメールに添付されたアイテムに刺さっているカードが見えるように修正（clif.c）

・clif_res_sendmail_setappend() を mail_setitem() に統合する（clif.c, mail.*）
・clif_parse_RefleshMailBox() でも添付アイテム用のデータを削除するようにしてみる（clif.c）

・ROメールにアイテムを添付したときにメッセージが出ないように変更（clif.*, mail.c）
	解析した限りにおいて clif_res_sendmail_setappend() は0x245ではなく0x255のパケットを
	使うのが正しい仕様のようです。
	アイテムのインデックスが必要になるので引数を1つ追加。
	また添付不可能なアイテムを添付すると「このアイテムはメールに添付することができません」
	のメッセージが出るようになっています。

・ROメールに添付されたアイテムを受け取ったときにメッセージが出るように変更（clif.*, mail.c）
	clif_mail_getappend() 追加、0x245を使います。
	重量オーバーなどでアイテム取得できなかった時は「アイテムはメールにて保管されています」
	のメッセージが出るようになっています。

・mob_data構造体の並びを変更、8byteのメモリ節約（map.h）
・map_session_data構造体から不要なメンバ server_tick を削除（clif.c, map.h）
・map_session_data構造体の以下のメンバをstateに移動（map.h）
	deal_mode, deal_locked, party_sended, guild_sended, friend_sended, wis_all, joinchat

----------------------------------------
//0336 [2007/09/18] by Rayce

・hacker対策のためのチェック強化（clif.c, chat.c, friend.c, guild.c, vending.c）
	-> 太陽と月と星の感情によるMAPセーブ時に、スキルを取得しているかどうかをチェックする
	-> 死亡時にリスタートボタンを押した際にプレイヤーが死亡しているかどうかをチェックする
	-> チャット参加時に視界内に居るかどうかをチェックする
	-> 友達要請時に同一MAPか、視界内か、自分に対する要請でないかチェックする
	-> ギルドの役職変更時にidxの範囲チェックをする
	-> ギルド同盟/敵対要請時に同一MAPか、視界内か、同じギルドに対する要請でないか、要請者が
	   ギルドマスターかをチェックする
	-> 露店アイテムリスト要求時に同一MAPか、視界内かチェックする
	-> 露店アイテム購入時に同一MAPか、視界内かチェックする

・ギルドに関する修正（clif.c, guild.*）
	-> ギルドエンブレム変更時のマスターチェックはguild.cではなくclif.cで行うように変更
	-> guild_invite() で視界内に居るかどうかのチェックは　map_countnearpc() ではなく
	   unit_distance() を使うように変更
	-> guild_member_added() でサーバクラッシュする可能性を修正
	-> guild_send_xy_timer() で可変引数は不要なのでtickを削除
	-> guild_change_position() で guild_search() を実行しないように修正
	   ギルドの不正チェックは既にclif.cで行っているので不要

・以下の関数で出来る限り GETPACKETPOS() を利用するように修正（clif.c, db/packet_db.txt）
	clif_parse_GuildChangePositionInfo()
	clif_parse_GuildChangeMemberPosition()
	clif_parse_SendMail()

・0335に添付し忘れていたconf/battle_auriga.confを同梱

----------------------------------------
//0335 [2007/09/18] by Rayce

・clif_parse_HomMercActionRequest() を少し修正（clif.c）
	クライアントを調べた限り、プレイヤーとは違い once attack しかありませんでした。
	hacker対策として continueous attack の部分は削除します。

・PK MAPに入ったときに赤文字の注意勧告が表示されるように修正（clif.c）
・/acceptの存在を忘れていたので clif_parse_RefusePartyInvite() を修正（clif.c）
・clif_parse_func[] を packetdb_readdb() の中に収める（clif.c）
・clif.cの細かい整形（clif.c）

・battle_auriga.confに allow_guild_alliance_in_agit を追加（battle.*, guild.c）
	攻城戦中にギルドの同盟/敵対ができるかどうかを決めます
	デフォルトはnoなので、攻城戦中なら如何なるMAPにおいても同盟/敵対の要請は不可です。
・battle_auriga.confの allow_guild_invite_in_gvg と allow_guild_leave_in_gvg はGvG設定MAPで
　あっても攻城戦中でないならギルドメンバーの加入/脱退が出来るように変更（guild.c）

----------------------------------------
//0334 [2007/09/14] by Rayce

・PACKETVERを10に引き上げる
	2007-09-04aSakexe以降がPACKETVER 10になります。
	2007-09-04aSakexeより古いクライアントを使う場合にはPACKETVERを9以下に戻す必要があります。

・PACKETVERが10以上のとき、パケット0x2d0, 0x2d1, 0x2d2, 0x2d4をサポート（clif.c）
	末端に伸びた2byteはアイテムの永続装備？のためのもの。
	詳細不明なのでこれについては現在のところ未実装。

・PACKETVERが10以上のとき、パケット0x2c5, 0x2c6をサポート（clif.c）
	2007-09-04aSakexe以降はパーティ勧誘の応答に0xfdではなく0x2c5を使わないと時々メッセージが
	表示されない問題が発生するようです。

・/refuseをサポート（clif.c, map.h, party.c）
	パーティ勧誘の拒否/受諾を行うためのコマンド。
	map_session_data構造体のstate内に refuse_partyinvite 追加。

・パーティ勧誘に関する修正（clif.*, party.c）
	-> 2007-09-04aSakexe以降のクライアントにおいて、勧誘された人が基本スキルLvが4以下なら
	   「パーティ加入不可」メッセージを表示するように修正
	-> 相手が見つからない場合は「該当キャラがいない」メッセージを表示するように修正
	-> 要請者がリーダーかどうかをチェックするように強化
	-> clif_party_invite() の引数変更

----------------------------------------
//0333 [2007/09/13] by Rayce

・スタック位置にワープしたとき、ワープ先の検索は1000回で打ち切るように修正（pc.c）
・スクリプトのresetskill命令に可変引数を渡せるように拡張（atcommand.c, clif.c, pc.*, script.c）
・db/item_db2.txtのZoneに +256, +512 を追加（pc.c）
　mapflagにnopenaltyが設定されているかどうかでアイテムの使用可否を決定することができます

・script/functionを新設
	function_itemdb.txtにはdb/item_db.txtで利用するfunctionを集めます
	function_global.txtには各NPCファイルで共通で使うfucntionを集めます

・巨大なハエの羽、キラキラスティックの効果実装
	originally created by Cocoaさん、thx a lot!!

　　※キラキラスティックの相違点
　　　重量が0でないと使用できないはずだが使えてしまう。

----------------------------------------
//0332 [2007/09/13] by Rayce

・以下の傭兵専用スキルを実装（battle.c, skill.c）
	MER_QUICKEN, MER_CRASH, MER_REGAIN, MER_TENDER, MER_BENEDICTION, MER_RECUPERATE,
	MER_MENTALCURE, MER_COMPRESS, MER_SCAPEGOAT

　消費SPがわからなかったので他のスキルを適当に参照（db/skill_require_db.txt）
	MER_QUICKEN   → 2HQ
	MER_CRASH     → バッシュ
	MER_SCAPEGOAT → SP1
	その他        → キュア

・SC_WEAPONQUICKEN追加、ただし実装はかなり適当（merc.c, skill.c, status.*）
・MAX_HOMCSKILL_TREEを16に戻しておく、ついでにMAX_MERCSKILL_TREEを16に変更（homun.h, merc.h）

----------------------------------------
//0331 [2007/09/13] by Rayce

・以下の傭兵スキルを実装（battle.c, merc.c, skill.c, status.c, unit.c）
　ただしステータス異常は適当だったり未実装だったりします
	MS_BASH, MS_MAGNUM, MS_BOWLINGBASH, MS_PARRYING, MS_REFLECTSHIELD, MS_BERSERK,
	MA_DOUBLE, MA_SHOWER, MA_CHARGEARROW, MA_SHARPSHOOTING,
	MA_SKIDTRAP, MA_LANDMINE, MA_SANDMAN, MA_FREEZINGTRAP, MA_REMOVETRAP,
	ML_PIERCE, ML_BRANDISH, ML_SPIRALPIERCE, ML_DEFENDER, ML_AUTOGUARD,
	MER_MAGNIFICAT, MER_SIGHT, MER_PROVOKE, MER_AUTOBERSERK, MER_DECAGI,
	MER_LEXDIVINA, MER_ESTIMATION

・傭兵のスキル一覧が消えてしまう問題を暫定的に修正（clif.c, merc.c, skill.c, status.c）
	clif_send_mercstatus() を送信するとスキル一覧が消えるみたいなので、clif_send_mercstatus()
	の後には必ず clif_mercskillinfoblock() を送信するようにしています

・merc_calc_status() に適当に状態異常判定を追加（merc.c）
・pc_checkoverhp() および pc_checkoversp() をstaticに変更（pc.*）

----------------------------------------
//0330 [2007/09/12] by Rayce

・オートバーサークの処理方法がパッシブスキルだった頃のままだったので修正（clif.c, status.c）
	オートバーサークを使ってないのに勝手にプロボック状態になったり、
	オートバーサークをOFFにしてもプロボック状態が解除されないなどのバグが解消されます

・スキルツリーの計算処理を高速化（pc.c）
・battle_auriga.confの gm_allskill が設定されているときで且つ CLASS_DKDC が有効のとき、
　DK/DCスキルの一部が取得できなかった問題を修正（pc.c）
・doevent命令でプレイヤーがアタッチされてないときは警告を出すように修正（script.c）

・typo修正、MER_LEXDEVINA → MER_LEXDIVINA（skill.*）
・db/skill_unit_db.txtに傭兵の罠スキル4種追加
　ついでに細かい整形

----------------------------------------
//0329 [2007/09/11] by Rayce

・以下をeAよりmerge
	-> clif_clearflooritem() を少し修正（clif.c）
	-> ファイヤーウォールとアイスウォールを足元に出すときの向きをAegisに合わせて6にする（skill.c）
	-> 切断待ちの相手にパーティおよびギルドの勧誘をすると失敗するように修正（guild.c, party.c）
	-> パーティが定員オーバーのときはメッセージを表示するように修正（party.c）

・SkillStatusChangeTableの整理（skill.c）
・StatusChangeTable系およびStatusIconChangeTableにおいて、初期化の間違いをコンパイルエラーで
　検出できるように配列のサイズを指定するように修正（skill.*, status.c）

----------------------------------------
//0328 [2007/09/11] by Rayce

・ホムンクルスが攻撃してタゲをとったモンスターに殺されたあと、そのモンスターに攻撃しても
　反撃してこない時が発生するバグを修正（mob.c）
		reported by Cocoaさん
	Athena1046以降から発生して今まで残っていた隠れバグのようです。
	MOBと交戦中に攻撃主が消滅（PCならALT+F4による強制終了、HOMなら死亡）したとき、mob_data
	構造体のattacked_idが0に初期化されなかったのが原因です。
	mob_damage() でターゲットを獲得するためにはattacked_idが0になってる必要があります。

・新ギルドスキル？GD_ITEMEMEGENCYCALLが追加されていたので、MAX_GUILDSKILLを16にしておく（mmo.h）
　現在はアイコンが実装されてないらしくリソースエラーになるのでコメントアウト

・傭兵スキルをdbで有効化
	db/skill_cast_db.txt
	db/skill_db2.txt
	db/skill_require_db.txt
	db/skill_require_db2.txt

----------------------------------------
//0327 [2007/09/11] by Rayce

・傭兵がスキルを使えるように（clif.c, skill.c, unit.c）
・NPC_KEEPINGを使ってもキーピング状態にならなかったバグを修正（skill.c）
・緊急回避とディフェンスは主人だけでなくホム自身にも効果が発現するように修正（skill.c）

・スキルの仕様拡張（skill.c, unit.c）
	-> ストリップ系スキルがホムや傭兵にも効果が発現するように拡張
	-> ホムスキルも地面指定型スキルを扱えるように拡張
	-> ホムスキルについて、db/skill_require_db.txtのstateに sight, explosionspirits, cartboost
	   nen, water が指定できるように拡張
	-> 以下のスキルをホム以外が使ってもある程度効果が発現するように拡張
	   　　ブラッドラスト
	   　　フリートムーブ
	   　　オーバードスピード
	   　　メンタルチェンジ
	   　　バイオエクスプロージョン

・pet_target_check() を少し整形（pet.c）
・skill.cの全体的な整形（skill.c）

----------------------------------------
//0326 [2007/09/10] by Rayce

・傭兵スキルの実装準備
	-> 傭兵スキルの定義を追加（skill.h）
	-> skill_get_skilldb_id() を傭兵スキルに対応（skill.h）
	-> MercStatusChangeTable[] 追加（skill.*）
	-> db/merc_skill_tree.txt追加
	-> 傭兵召喚時にスキルツリーにあるスキルを全て取得する（merc.c）
	-> スキル一覧を表示できるように修正（clif.c, merc.c）
	   ホムと違い、傭兵メニューを開くタイミングでスキル一覧パケットを送信しないと
	   表示されないようです

　　※相変わらずdb/merc_skill_tree.txtは適当です。
　　　まだ仕様を固めてないのでフォーマットが変更される可能性があります。

----------------------------------------
//0325 [2007/09/10] by Rayce

・スキルIDの定義をmmo.hにまとめて整理する
　（int_homun.c, atcommand.c, map.h, pc.c, skill.*）
	-> skill.hにあった MAX_SKILL_DB, MAX_HOMSKILL_DB, MAX_GUILDSKILL_DB は混乱を招くので廃止
	-> MAX_SKILL_DB を skill_get_skilldb_id() 用IDの最大値として再定義

・skill_db構造体にidを追加、スキルIDを保存しておくようにする（skill.*）
　weaponをunsigned int型に修正
・ホムスキルやギルドスキルに対してもスキルユニット配置情報を作成できるように拡張（skill.c）

・pc_allskillup() を少し最適化（pc.c）

----------------------------------------
//0324 [2007/09/09] by Rayce

・パケット0x2c4, 0x2c7に対応（clif.c, party.*）
	2007-09-04aSakexeからパーティ勧誘パケットが変更されているので、それぞれ
	clif_parse_PartyInvite2(), clif_parse_ReplyPartyInvite2() を使います。

・battle_auriga.confに party_invite_range_check 追加（battle.*, party.c）
	主に2007-09-04aSakexe以降用です。
	PTウィンドウや /invite でパーティ要請する際に、遠くに離れている場合は要請不可に
	したい場合は yes にすると良いです。

・party_reply_invite() でパーティ勧誘中フラグが無い場合はinterサーバに追加要求せずにすぐに
　拒否するように修正（party.c）
・db/pet_db.txtをリロードすると現在出現しているペットの情報が狂う場合があるので、データベースの
　初期化はサーバ起動時にのみ行うように修正（pet.c）

・db/pet_db.txtおよびdoc/db_ref.txtを少しだけ修正
・db/packet_db.txt更新
・doc/client_packet.txt更新

----------------------------------------
//0323 [2007/09/08] by Rayce

・傭兵の雇用期限実装（map.h, merc.*, unit.c）
	db/merc_db.txtのlimitで指定した時間（デフォルトでは30分）経過したら、傭兵は消滅します
	現在の仕様ではログインしていなくても実時間で30分経つと期限切れとみなされます
	（課金アイテムである強化装備系の使用期限と同じ扱いです）

・ペットとホムの腹減りタイマーはmap_session_data構造体ではなく、pet_dataおよびhomun_data構造体が
　受け持つように変更（homun.*, map.h, pc.c, pet.*, unit.c）

----------------------------------------
//0322 [2007/09/08] by Rayce

・スクリプトにchecksit関数、checkdead関数を追加（script.c）
・太陽と月と星の憎しみでプレイヤーを指定した場合、職業名が表示されるように修正（clif.c）

・スキルツリーのバイナリサーチでidが0の場合を弾くように修正（homun.c, merc.c, pc.c）
・@makepetで存在しないモンスターを指定した場合は0を返すように変更（atcommand.c）
・既にホムを作成済みの場合において、homun_recv_homdata() でデータを取得した際にホムの呼び出しに
　成功したときのみホムスキル一覧パケットを送信するように修正（homun.c）
・merc_callmerc() が成功時には1、失敗時には0を返すように変更（merc.c）

----------------------------------------
//0321 [2007/09/07] by Rayce

・傭兵実装解禁
	-> @callmerc追加（atcommand.*）
	-> "@callmerc 傭兵ID" で指定した傭兵を召喚できます

・傭兵の雇い主が死亡したら傭兵が消滅するように修正（pc.c）
・傭兵が消滅する際に死亡/解雇/逃走のメッセージを表示するように（merc.c）
	msgstringtable.txtにはメッセージが用意されているが、調べた限りにおいてはこれらの
	メッセージを表示する手段が見つからないので暫定的にconf/msg_auriga.confを使います。

・strnlen() がコンパイラによって未定義になってたりして怪しいので削除（login.c, utils.*）
　memchr() を使って自前で判定するように変更
・コンパイル時の警告修正（clif.c）
・Makefileに int_merc.c, int_merc.h, merc.c, merc.h 追加
・*.dspファイル修正

　　※現時点での傭兵は移動して戦闘して経験値を取得できるだけです。
　　　とりあえず動かしてみたい人向け。
　　　傭兵特有のシステムや状態異常、スキルなどはまだ未実装。

----------------------------------------
//0320 [2007/09/07] by Rayce

・傭兵実装準備その７
	-> 経験値が取得できるように（mob.c, merc.c）
	   傭兵自体にレベルアップの概念が無いようなので、雇用主に経験値が渡されるだけで
	   傭兵自体が経験値を獲得するわけではありません
	-> battle_auriga.confに master_get_homun_base_exp, master_get_homun_job_exp を追加（battle.*）
	   ホムのと同じ使い方です

・傭兵に関する細かい修正（battle.c, map.c, npc.c）
・clif.hからstorage.hのincludeを外す
　（atcommand.c, clif.h, chrif.c, homun.c, merc.c, pet.c, unit.c）

----------------------------------------
//0319 [2007/09/07] by Rayce

・傭兵実装準備その６
	-> HPとSPが自然回復できるように（merc.*, unit.c）
	-> map_id2mcd() 追加（map.*）
	-> homun.hの NATURAL_HEAL_HP_INTERVAL, NATURAL_HEAL_SP_INTERVAL をそれぞれ
	   HOM_NATURAL_HEAL_HP_INTERVAL, HOM_NATURAL_HEAL_SP_INTERVAL に変更（homun.*）

・MOBが傭兵に攻撃できなかったバグを修正（mob.c）
・傭兵のaspd_kが間違っていたため攻撃モーションが出なかったバグを修正（merc.c）

・pc_itemlimit_timer をtimer関数リストに登録し忘れてたので追記（pc.c）
・pc_homisalive() を homun_isalive() に変更（pc.*, homun.*, skill.c）

----------------------------------------
//0318 [2007/09/07] by Rayce

・傭兵実装準備その５
	-> 戦闘ができるように（battle.c, skill.c, unit.c）
	   battle_check_target() は結構適当です、いずれ関数ごと見直して修正します
	-> clif_parse_HomActionRequest() を clif_parse_HomMercActionRequest() に変更（clif.c）
	   攻撃要求パケットもホムと傭兵で共通
	-> merc_damage() および merc_heal() 有効化（merc.*）

　　※何故か傭兵の攻撃射程が1で、しかも攻撃時にモーションが全く出ません。
　　　表示パケットが間違っているのか、それとも他の要因があるのか、今のところ不明。

----------------------------------------
//0317 [2007/09/07] by Rayce

・グラビテーションフィールドに関する修正
	-> skill_stop_gravitation() を削除（homun.c, pc.c, skill.*, status.c）
	   スキルユニット削除処理はゴスペルやグラフィティと同じく status_change_end() に
	   一括してまとめるように変更
	-> battle_auriga.confの player_gravitation_type が2以外のとき、グラビテーションフィールド
	   使用者が通常攻撃が可能になっていたバグを修正（clif.c）
	-> グラビテーションフィールド使用者はアイテム使用不可に修正（clif.c）
	-> グラビテーションフィールド発動後5秒間はリログ禁止に修正（skill.c）
	-> グラビテーションフィールド使用中にワープした場合は解除されるようにしてみる（unit.c）

・skill_unit_ondamaged() はtargetがNULLの場合があるのでチェックを入れるように修正（skill.c）
・0312でホムは skill_unit_move() を呼ばないようにしたが、今後の拡張を考えて巻き戻す（homun.c）

----------------------------------------
//0316 [2007/09/07] by Rayce

・battle_damage() をまとめ直し（battle.c）
・PC以外がシュリンクを使っている場合でも攻撃主を吹き飛ばせるように拡張（battle.c）
・ティオアプチャギによる対象のステータス異常解除がPCとMOB以外にも発動するように拡張（battle.c）
・unit_getdir() は status_get_dir() と同じなので削除（unit.*）
・MOBのrudeattackedが誤作動する可能性を修正（mob.c）
・PETとHOMも unit_remove_map() で skill_cleartimerskill() を実行するように修正（unit.c）

----------------------------------------
//0315 [2007/09/06] by Rayce

・傭兵実装準備その４
	-> ステータス再計算を暫定的に用意（merc.*, status.c）
	-> スキルツリーの準備（clif.*, merc.*）

・clif_homskillinfoblock() を少し整形（clif.c）
・MAX_HOMSKILL_TREEを5に縮小（homun.*）
	ホムの各クラスにおいて取得可能なスキルは最大で4個になります。
	さらに増やしたい方はdb/homun_skill_tree.txtにスキルを書き加えた上で
	MAX_HOMSKILL_TREE を適宜変更してください。

・AthenaProject2318よりmerge、thanks to ICOさん
	-> おいしい血の炭酸ソーダの材料を修正（db/produce_db.txt）

----------------------------------------
//0314 [2007/09/06] by Rayce

・ジークフリードの証の効果実装（clif.c）
	clif_parse_Revive() 追加。
	ジークフリードの証には専用のパケットは存在せず、単に所持しているだけで
	死亡時に復活ダイアログが出てくる仕組みのようです。
	何もないと寂しいので復活時にリザレクションのエフェクトを付けています。

・db/packet_db.txtに revive 追記
・doc/client_packet.txt更新

----------------------------------------
//0313 [2007/09/05] by Rayce

・ステータス異常 SC_SUMMER 追加（pc.c, script.c, status.*）
	サンタ服と同じ原理。
	2007-08-08aSakexeくらいから「涼しい夏衣装」が使えるはず。

・サンタ中と夏衣装中はスキルが使えないように修正（clif.c）
・db/const.txtに SC_Summer を登録

----------------------------------------
//0312 [2007/09/05] by Rayce

・0311で修正し忘れていたmob.cを添付（mob.c）
・ホムは出現時および消滅時に skill_unit_move() を呼ばないように修正（homun.c）
	ホムはスキルユニットの影響を受けないため、この関数を呼び出す必要がない

・ワープポータル発動時に skill_unit_effect() を呼ばないように修正（skill.c）
	ワープポータルは既にAthena1891で位置発動ユニットからタイマー発動ユニットに
	変更されているため不要

・skill_chastle_mob_changetarget() のtypo修正（skill.c）
・skill_hermode_wp_check() の引数変更（skill.*, unit.c）
・skill_hermode_wp_check() および skill_delunit_by_ganbantein() の位置を移動（skill.c）
・skill.cの全体的な整形

----------------------------------------
//0311 [2007/09/05] by Rayce

・map_foreach系の改善 merged from eA
　（atcommand.c, clif.c, map.*, mob.c, npc.c, pet.c, script.c, skill.c, status.c, unit.c）
	BL_CHARおよびBL_ALL追加。
	map_foreach*** を呼び出す際にBLの型を明示する。
	呼び出されたサブルーチンにおけるblock_listのprevチェックを省略。

----------------------------------------
//0310 [2007/09/04] by Rayce

・傭兵実装準備その３
	-> 歩行できるように（pc.c, unit.c）
	-> clif_parse_HomWalkMaster() および clif_parse_HomWalkToXY() をそれぞれ
	   clif_parse_HomMercWalkMaster() および clif_parse_HomMercWalkToXY() に変更（clif.c, merc.c）
	   移動系はホムと傭兵で共通のパケットを使うようです
	-> status_get_***系を一式用意（status.c）
	-> merc_data構造体に暫定でメンバ attackrange を追加（map.h）
	-> 傭兵もMOBのAIリンクリストに登録する（merc.c, mob.c, unit.c）

・battle_auriga.confに merc_speed_is_same_as_pc を追加（battle.*, status.c）

----------------------------------------
//0309 [2007/09/04] by Rayce

・キャラクターが召喚中の傭兵IDをセーブできるように（char.c）
	TXTならsave/auriga.txtのホムIDの次に保存されます。
	SQLなら `merc_id` フィールドに保存されます。

・TXT: JOURNAL_IDENTIFIERをバージョン07に変更しておく（journal.c）

・SQL: 「SELECT *」のようにワイルドカードを使うとカラムの並びに強く依存してしまうので、
       必要なフィールドを直接指定するように修正（char.c, int_guild.c, int_mail.c）
・SQL: `char` テーブルの `homun_id` フィールドのカラム位置を移動
・SQL: main.sql修正、Auriga-309_changetable.sql添付
・SQL: txt-converter対応（char-converter.c）

----------------------------------------
//0308 [2007/09/03] by Rayce

・傭兵実装準備その２
	-> int_merc.c, int_merc.h追加
	-> 傭兵の作成/情報送受信/セーブ送信/削除用interパケット一式追加（inter.c, intif.*）
	-> 暫定的に傭兵のデータをセーブできるように（char.c, int_merc.c）
	   TXTならsave/mercenary.txtにセーブされます、SQLは準備のみ
	   ただしフォーマットが変更される可能性が高いです
	-> inter_auriga.confに傭兵の項目追加（inter.c, int_merc.c）
	-> 既に傭兵を召喚済みの状態でログインすると傭兵が出現するように（clif.c, merc.c, pc.c）

----------------------------------------
//0307 [2007/09/03] by Rayce

・ホムデータの要求および削除をinterサーバに行う際、ホムIDがWORDで計算されていたのでDWORDに修正
　（inter.c, int_homun.c）
・intif_char_connect_limit() のパケット番号を 0x3070 → 0x3008 に変更（intif.c, inter.c）
・doc/inter_server_pacekt.txt修正

----------------------------------------
//0306 [2007/09/03] by Rayce

・傭兵実装準備
	-> merc.c, merc.h追加
	-> mmo_charstatus構造体にメンバ merc_id を追加（mmo.h）
	-> 暫定的にmmo_mercstatus構造体を追加（mmo.h）
	-> 暫定的にmerc_data構造体を追加（map.h）
	-> 傭兵の出現/表示/情報通知パケットを一式用意（clif.*）
	-> 傭兵メニュー要求パケット0x29f追加（clif.c）
	-> 傭兵データの解放処理（map.c, merc.c, pc.c, unit.c）
	-> 暫定的にdb/merc_db.txt追加

　　※とりあえず出現してメモリ解放するところまで。
　　　データのセーブとかはまだ先。
　　　基本的にはホムの流用です。
　　　穴ポコだらけですが少しずつ実装していきます。
　　　dbや構造体のメンバなどは今後の成り行きによって変更される可能性が高いのでご注意を。

----------------------------------------
//0305 [2007/09/03] by Rayce

・homun_callhom() を少し修正（homun.c）
・mmo.hに傭兵用の定数を定義（mmo.h）
・新規ブロックリストタイプとして BL_MERC を定義（map.h）
・doc/client_packet.txt更新

----------------------------------------
//0304 [2007/09/03] by Rayce

・hacker対策として、超短時間に連続してパーティ作成、ギルド作成、コールホムンクルスしても作成要求が
　二重に行われないように修正（atcommand.c, guild.c, homun.c, map.h, party.c）

・homun_data構造体から意味のないメンバ equip を削除、および整理（mmo.h, map.h, clif.c, homun.c）
・homun_db, mob_db, pet_db構造体の整理（homun.h, mob.h, pet.h）
・homun_data構造体の homskillstatictimer を skillstatictimer に改名（clif.c, homun.c, map.h, skill.c）
・db/homun_db.txtのNameをクライアント定義の名前に修正

----------------------------------------
//0303 [2007/09/02] by Rayce

・スキル系dbについて
	-> ID577以降の定義が間違っていたので修正
	-> DA系統および傭兵スキルを追加
	-> skill_cast_db.txtおよびskill_require_db.txtの整形

・battle_calc_misc_attack() の変数名を変更（battle.c）
・以下の関数の位置を移動（clif.c）
	clif_send_homdata()
	clif_send_homstatus()
	clif_hom_food()
	clif_homskillinfoblock()
	clif_homskillup()

----------------------------------------
//0302 [2007/09/02] by Rayce

・pet_data構造体およびhomun_data構造体から使われてないstateを削除（map.h, homun.c, pet.c）
・mob_data構造体の skillstate のビットフィールドを 8 → 4 に縮小（map.h）
・mob_readskilldb() を少しだけ修正（mob.c）
・MSS_***系定数の値を変更（mob.h）

----------------------------------------
//0301 [2007/09/01] by Rayce

・使用期限付きアイテムの生成を実装（atcommand.c, script.c）
	-> @item2
	   　引数を一つ追加、省略できないので10個の引数全て入力しないと発動しません。
	-> getitem2命令
	   　account_idの前に使用可能時間の設定を追加。
	   　引数の使い方が変更されているので、今までgetitem2命令でaccount_idを省略せずに
	   　指定していた場合は各自修正すること。
	-> getinventorylist命令、getcartlist命令
	   　@inventorylist_limitおよび@cartlist_limitに使用期限がUNIX時間で代入されます。
	   　使用期限は内部ではunsignedで計算されていますが、スクリプトで使う変数はsignedなので
	   　場合によっては負の値になっている可能性もあります。
	   　その点を考慮に入れた上で利用してください。
	-> dropitem命令
	   　省略可能な引数を一つ追加

・hacker対策として、db/item_db.txtでNPC売却不可設定にしているアイテムが絶対に売却できないように
　サーバ側でも判定を行うよう強化（npc.c）

・db/item_db.txtにバブルガム、凸面鏡、Rの箱系を正式実装
　ついでにhuge cgiより最新まで更新、thx a lot!!
・db/item_db2.txtに強化装備アイテムを追加
　ドロップ不可、倉庫移動不可、カート移動不可

----------------------------------------
//0300 [2007/09/01] by Rayce

・アイテムの使用期限のセーブに対応（char.c, int_mail.c, int_storage.c）
・TXT: JOURNAL_IDENTIFIERをバージョン06に変更しておく（journal.c）
・SQL: main.sql修正、Auriga-300_changetable.sql添付
・SQL: txt-converter対応（char-converter.c, inter-converter.c）

・パケット0x296が非対応になってたので修正（clif.c）
・battle_auriga.confのitem_checkをyesにした状態で、@giveitemを使って存在しないアイテムIDを指定すると
　サーバクラッシュするバグを修正（atcommand.c）

----------------------------------------
//0299 [2007/09/01] by Rayce

・アイテムに使用期限が設定できるように追加（mmo.h, clif.*, map.h, pc.*, unit.c）
　　課金アイテムである強化装備系再現のための下準備。
　　実行本体を実装しただけで、まだアイテムを生成する手段もないしセーブもされません。

	-> item構造体にメンバ limit 追加
	-> map_session_data構造体にメンバ inventory_timer 追加
	   使用期限付きアイテムのタイマーIDをリンクリストで保存しておく
	-> clif_delitem_timeout() 追加
	   ただしPACKETVERが9以上でないとこの関数は使えない
	-> アイテムに使用期限が設定されている場合はタイマーに登録します
	   期限が1時間を超える場合、タイマーは1時間でセットされ、1時間後に期限切れになっている
	   かどうかをチェックしてまだ時間になってない場合は再度1時間のタイマーをセットします
	   add_timer() に非常に長い時間をセットするとオーバーフローを起こしてタイマーが誤作動
	   する恐れがあるのでこのような仕様になってます
	-> pc_checkitem() でアイテムをソートする際、アイテムのインデックスが変化してしまうので
	   inventory_timerの再構築を行います
	   力技でやってるので処理がかなり煩雑です
	-> 本鯖準拠の課金アイテム以外でも使用期限を設定できるように実装されています
	-> 使用期限を設定したアイテムを捨てたり倉庫に預けたりしても問題ないように実装されています
	   タイマーが動くのはプレイヤーの所持品の中にある場合のみです
	   アイテムを削除したときには同時にタイマーも破棄されます
	   再びアイテムを取得したときに期限切れかどうかの判定が行われ、期限が切れていたらアイテムを
	   取得した直後に削除されます
	-> PACKETVERが9よりも古い場合でも問題なく作動します
	   しかしアイテムを右クリックしても期限時間が見えないので、PACKETVERを9以上にすることを
	   お勧めします

・マクロ itemdb_jname() を追加（itemdb.*, pc.c）
・conf/msg_auriga.confに187番を追加

----------------------------------------
//0298 [2007/08/30] by Rayce

・NPCイベントのブロードキャストを高速化（npc.c）
	OnInitやOnPCDieなどサーバから直接呼び出されるイベントや、"::OnKilled" のようにdonpcevent命令を
	ブロードキャストする場合の処理速度が大幅に改善されます。
	同じラベル名を持つイベント同士を単方向リンクリストに連結しておくことで、npc_event_doall()
	および npc_event_doall_id() においてstrdb_foreachで全巡回することなく効率的にイベントの
	呼び出しができます。

	ラベルデータをエクスポートする際、ラベルそのものをev_dbに登録しておきます。
	これはリンクリストの先頭を取得するためのダミーデータです。
	例えば "AA::OnInit" と "BB::OnInit" を順番に登録した場合、必ず "::OnInit" が最初に登録されます。

	　　"::OnInit" → "AA::OnInit" → "BB::OnInit"

	doallを呼び出す場合は "::OnInit" をキーにして ev_db を strdb_search() で検索し、順にリストを
	辿りながら run_script() を実行すればよいことになります。

	ただしOnTimer系ラベルはリンクリストを作りません。
	OnTimer系ラベルは量が多すぎること、またOnTimerをブロードキャストする場面はほとんどないと考え
	られるため。
	従って donpcevent "::OnTimer1000"; とかは今後作動しなくなりますのでご注意ください。

・OnTimer を予約ラベルにする（npc.c）
	今までは "OnTimer1000L" のように数値の後ろに文字が続く場合はタイマーラベルではなく単なる
	イベントラベルとして扱われていました。
	今後は OnTimer で始まるラベルは必ずタイマーイベントとしてみなされます。
	上記のように余計な文字が含まれる場合には「invalid OnTimer label」の警告が出力され
	サーバが落とされるようになります。

・ラベルデータが重複していて「dup event」になる場合はサーバを落とすように変更（npc.c）

----------------------------------------
//0297 [2007/08/29] by Rayce

・AthenaProject2277を参考にNPCタイマーを修正、thanks to Yasさん（npc.c）
	-> npc_event_do_clock() から続く npc_event_doall() 以下の関数内部でlocaltimeを使うと
	   時間が狂って時計イベントが発動しない場合が発生する問題を修正
	   localtimeで取得したデータを一旦バッファにコピーしてから参照する
	-> ev_tm_b を現在時刻で初期化するように変更

・OnDayラベルの仕様変更、OnMonthDayラベルの追加（npc.c）
	OnDayラベルは毎月指定日に発動するイベントに変更されます。
	これまでのOnDayラベルと同等の機能がOnMonthDayラベルとなります。
	OnDayラベルをスクリプトで利用していた方は各自修正してください。
	詳細はdoc/script_ref.txt参照。

・clif_send_homdata() と clif_spawnhom() のパケット区切りをクライアントの解析方法に合わせる
　（atcommand.c, battle.c, clif.*, homun.c, pc.c, skill.c）

----------------------------------------
//0296 [2007/08/27] by Rayce

・0291～0293で追加したNPCスキルのエフェクトが出ないので暫定的に修正（skill.c）
	何故か clif_skill_nodamage() ではなく clif_skill_damage() にエフェクトが含まれている模様。
	流石にエフェクトがないと寂しいので無理矢理修正しています。

・致命傷攻撃を強制無属性の遠距離攻撃にしてみる（battle.c）
・エクスパルシオンを必中の遠距離攻撃にしてみる（battle.c）
　処理方法はインティミデイトと同じにしてみる
・インティミデイトの処理で map_searchfreecell() を使うように最適化（skill.c）

----------------------------------------
//0295 [2007/08/27] by Rayce

・パケット0x124の上位版0x1c5追加（clif.c）
	カートにアイテムを入れるときにアイテムのtypeを付加することができるようです。
	恐らく本鯖はかなり昔に上位版に移行していたと考えられますので、PACKETVERが7以上のときに
	0x1c5をサポートするようにしています。

・PACKETVERが9以上のとき、パケット0x295, 0x296, 0x297, 0x29aをサポート（clif.c）
	末端に伸びた4byteは強化装備アイテムの効果が切れる時間を入れるためのもの。
	少なくとも2007年5月付近の蔵だとこれら上位パケットには無反応だったので、2007-07-11aSakexe
	より古い蔵はサポート対象外ということにしておきます。

・サーバ停止時に全てのMobを削除する際、念のため各MAPの持つボス情報をNULLクリアするように修正（npc.c）

・doc/client_packet.txt更新
・battle_auriga.confの mvp_announce の説明を補足

----------------------------------------
//0294 [2007/08/27] by Rayce

・バブルガムの効果実装（atcommand.c, mob.*, pc.c, status.*）
　　モンスターからのアイテムドロップ率を変化させます。
　　val1に百分率でドロップ確率を設定します。
	-> SC_ITEMDROPRATE および SI_ITEMDROPRATE 追加
	-> mob_drop_fix() に引数を一つ追加

　　例）12210,Unknown_Item,バブルガム,2,,,10,,,,,1000333311,2,,,,,,{ sc_start SC_ITEMDROPRATE,1800000,200; },{}

・凸面鏡の効果実装（clif.*, map.h, npc.c, pc.c, status.*, unit.c）
　　MVPボスがMAPに居ない場合はメッセージを表示して終了します。
　　居る場合は出現するまでの時間をアナウンスします。
　　既に出現している場合はミニMAPにボスの座標が表示されます。
　　ボスが倒されたら効果は削除されます。
　　また死亡時やMAP移動でも効果は削除されます。
　　対象となるのは再出現可能なMVPボスのみです。
　　従ってロードオブデスや生体工学研究所のボスには反応しませんが、これは公式通りの仕様です。
	-> SC_BOSSMAPINFO および SI_BOSSMAPINFO 追加
	-> clif_bossmapinfo() 追加
	-> map_data構造体にメンバ mvpboss を追加
	-> スクリプト解析時にMVPボスであれば mvpboss に登録しておく
	   同一MAPに複数のMVPボスが配置される場合は一番最後に記述されたもののみが登録対象となる
	-> Mobが死亡したとき、mob_data構造体の last_spawntime に再出現時間を保存するようにしておく
	   現在時間とlast_spawntimeの差を取れば次回に出現するまでの時間が算出できる

　　例）12214,Unknown_Item,凸面鏡,2,,,10,,,,,1000333311,2,,,,,,{ sc_start SC_BOSSMAPINFO,600000,0; },{}

----------------------------------------
//0293 [2007/08/26] by Rayce

・NPCスキル「ストーンスキン」「アンチマジック」を仮実装（skill.c, status.*）
・既に同じ状態異常になっている場合、タイマーを解除したあとdb/scdata_db.txtのDisableで無効化されると
　状態異常の後始末が中途半端になるので判定タイミングを変更する（status.c）

・各街にスペシャルアイテム販売NPCを設置（script/npc/misc/npc_misc_pointshop.txt）
	thanks to Cocoaさん

----------------------------------------
//0292 [2007/08/26] by Rayce

・以下のNPCスキルをeAをベースに仮実装（battle.c, skill.c, status.c）
	ワイドサイト
	エクスパルシオン
	マジックミラー

・以下のステータス異常を実装（pc.c, skill.c, status.*）
	スロウキャスト状態
	致命傷状態
	マジックミラー状態

・bAddSkillHealRateの効果はHPに対してのみかかるように変更してみる（skill.c）
・MAX_STATUSCHANGEを390に拡張（mmo.h）

----------------------------------------
//0291 [2007/08/25] by Rayce

・以下のNPCスキルをeAをベースに仮実装（skill.c, status.*）
	範囲沈黙攻撃
	範囲凍結攻撃
	範囲出血攻撃
	範囲石化攻撃
	範囲混乱攻撃
	範囲睡眠攻撃
	範囲呪い攻撃
	範囲スタン攻撃
	スロウキャスト
	致命傷攻撃

・skill_castend_id() と skill_castend_pos() を移動（skill.c）
・グラウンドドリフトから skill_additional_effect() が呼ばれると鯖落ちする可能性を修正（skill.c）

----------------------------------------
//0290 [2007/08/25] by Rayce

・eAを参考に以下について修正
	-> conf/motd.txtを起動時に読み込んで保存しておくように改善（pc.*）
	   読み込める行数は MOTD_LINE_SIZE で32までです
	-> @reloadmotdを追加（atcommand.*）
	   conf/motd.txtの内容を変更したあとはこのコマンドを使うことでサーバ内に反映されます
	-> clif_send_hotkey() を clif_parse_LoadEndAck() で呼ぶように修正（clif.c, pc.c）

----------------------------------------
//0289 [2007/08/25] by Rayce

・ギルドスキルやホムスキルを詠唱中の相手に対してスペルブレイカーを使うと鯖落ちするバグを修正（skill.*）
	skill_get_skill_type() 追加

・skill_castend_nodamage_id() の細かい整形（skill.c）
・緊急召集の詠唱をスペルブレイカーで妨害できるようにしてみる（db/skill_db.txt）

・PACKETVERを9に引き上げる（clif.c）
	2007-07-11aSakexeより古いクライアントが clif_send_hotkey() を受け取ると、それ以降に受信した
	パケットが時々破棄されてしまう現象が発生していました。
	仕方がないのでPACKETVERで処理を分岐することにしました。

　　※2007-07-11aSakexe以降がPACKETVER 9になります。
　　　2007-07-11aSakexeより古いクライアントを使う場合にはPACKETVERを8以下に戻す必要があります。

----------------------------------------
//0288 [2007/08/24] by Rayce

・skill_check_condition2_pc() を少しだけ整理（skill.c）
・処理効率を上げるために clif_takeitem() をマクロから関数に変更
　（clif.*, mob.c, pc.c, pet.c, skill.c）

・conf/script_auriga.confに error_marker_start, error_marker_end を追加（script.c）
	スクリプトの解析エラーが発生したとき、エラー箇所を特定しやすくするために好きな文字列を
	指定することができます（15文字まで）。
	script.c内部でのデフォルトは空文字になっているので、該当項目をコメントアウトすれば
	文字を表示しない設定にすることもできます。

・以下のスキルについて、skill_require_db.txtのstateの項目にfalconを設定しなかったときでもスキルが
　発動できるように拡張（skill.c）
	ブリッツビート
	ディテクティング
	スプリングトラップ
	ファルコンアサルト
・skill_require_db.txtのstateの項目に新しく以下の2つを追加（skill.*）
	cartboost: カートブースト状態
	nen: 念状態

・db/skill_require_db.txtを上記変更に従って修正
・doc/script_ref.txtにpet命令が記載されてなかったので修正

----------------------------------------
//0287 [2007/08/24] by Rayce

・TXT: 0140以降、サーバ起動中にアカウントやキャラを削除すると、他の特定のアカウントやキャラがログイン
       不可能になる致命的なバグを修正（login.c, char.c）
		reported by Cocoaさん、thanks a lot!!

	アカウントやキャラを削除するときにIDも0に初期化してしまうため、バイナリサーチが正常に機能
	しなくなるのがが原因でした。
	IDは維持したままの状態にして、他のメンバで削除されているかどうかを判定するようにします。
	loginの場合はmmo_account構造体のuseridが空文字ならauth_datから削除済み、
	charの場合はmmo_charstatus構造体のaccount_idが0ならchar_datから削除済み、とみなします。

・SQL: loginサーバで使うアカウントデータのキャッシュが有効利用されてなかったので修正（login.c）
・SQL: loginサーバ起動中にアカウントを削除するとそのアカウントがキャッシュから削除されずに
       残り続けるバグを修正（login.c）

・MAX_SERVERSを MAX_CHAR_SERVERS に改名（login.*）
　MAX_CHAR_SERVERS を 30 → 8 に縮小しておく
・MAX_MAP_SERVERS を 30 → 8 に縮小しておく（char.*）

　　※charサーバおよびmapサーバを8個よりもさらに設置したい場合はこれらの値を増やしてください

----------------------------------------
//0286 [2007/08/23] by Rayce

・AthenaProject2317より、エスマのLv10以外の倍率を修正（battle.c）
・Athena1468で抜け落ちたディバインプロテクションの効果を再実装（battle.c）
	from AthenaProject BTS, thanks
・聖体降福が対人エリアだと自身とPTメンバーにしか掛からなかったのを修正（skill.c）
　味方であっても不死や悪魔であればダメージが入るように修正
	from AthenaProject Forum, thanks

・セージスキルのテイミングモンスターの処理を少し最適化（skill.c）
・skill_am_twilight1(), skill_am_twilight2(), skill_am_twilight3() をまとめて
　skill_am_twilight() とする（skill.c）

----------------------------------------
//0285 [2007/08/22] by Rayce

・pointshopを2007-07-11aSakexe以降のクライアントに対応（clif.c）
	0x289のパケット長を見て処理分岐しています。
	0x288に付属してる末端の4byte分は謎なので無視。

・doc/client_packet.txt更新
・SQL: `hotkey` テーブルにKEYを張り忘れてたので追加（Auriga285_changetable.sql）

----------------------------------------
//0284 [2007/08/22] by Rayce

・スペシャルアイテム販売NPCの実装（clif.*, map.h, npc.*, pc.c）
	pointshopでNPCを定義します。
	shopと同じ形式ですが、<point>に負数を指定するとそのまま負数になるので注意。
	課金アイテムに限らずあらゆるアイテムをポイントで販売することができます。
	プレイヤーのショップポイントはキャラ永続変数 PC_SHOP_POINT に保存されます。
	埋め込み変数として実装されているので、db/const.txtにある通り変数の操作が可能です。
	例えばスクリプトから以下のような形でポイントを与えます。
		set PC_SHOP_POINT,100;

　※2007-07-11aSakexe以降のクライアントには対応していません。
　　修正されるまでpointshopは使わないで下さい。

・db/packet_db.txtに "npcpointshopbuy" を追加
・doc/script_ref.txt更新

----------------------------------------
//0283 [2007/08/21] by Rayce

・0x272eのパケット処理部分を少し修正（char.c）
・skill_check_condition2_pc() でSP消費なしの場合、すぐにreturnで返すと以降の処理が無視されてしまう
　ので、変数spを0にするだけに修正（skill.c）
・カートレボリューションの範囲攻撃の挙動が狂っていたバグを修正（skill.c）
	reported by Cocoaさん

・スクリプトの menu/select命令 の拡張 from eA（script.c）
	メニューに ":" (半角コロン) を含む文字列を渡した場合も正常に値が返るようになります。
	":" は蔵の仕様上デリミタとして扱われるので、メニュー選択後に補正します。

　　例１）select("AA:BB:CC") は select("AA","BB","CC") と同じ
　　　　　"AA" -> 1, "BB" -> 2, "CC" -> 3
　　例２）select("AA:BB::CC") は select("AA","BB","","CC") と同じ
　　　　　"AA" -> 1, "BB" -> 2, "CC" -> 4
　　例３）select("AA:","BB:CC") は select("AA","","BB","CC") と同じ
　　　　　"AA" -> 1, "BB" -> 3, "CC" -> 4

----------------------------------------
//0282 [2007/08/21] by Rayce

・サーバ側でのホットキー保存に対応（mmo.h, char.c, clif.*, pc.c）
	merged from AthenaProject, thanks a lot!!

　※TXTに関してですが、eAのようにsave/hotkeys.txtとして別ファイルに保存することも考えましたが
　　journalとかの兼ね合いで面倒になったのでAthenaProjectに沿ってsave/auriga.txtに保存しています。
　　ただし保存形式は異なるので注意。
　　本パッチ以降、Athenaからのセーブデータの流用が完全に不可能になります！
　　SQLに関してもAthenaと比較してフィールドが一つ増えてるので注意。

・db/packet_db.txtを2007-05-07と2007-07-11までサポート
・TXT: JOURNAL_IDENTIFIERをバージョン05に変更しておく（journal.c）
・SQL: main.sql修正、Auriga-0282_changetable.sql添付
・SQL: txt-converterをホットキーに対応（char-converter.c）

・@hotkeyset追加（atcommand.*, clif.c, map.h）
	ホットキーを27個以上登録/利用できるようにするための拡張システム。
	mmo.hのMAX_HOTKEYSをデフォルトの27よりも大きく設定している場合に意味があります。
	9x3ページ = 27個を1セットとして扱い、ホットキーセットを切り替えることで擬似的に
	ページを増やします。
	@hotkeysetを使ったあとF12でページをめくったりすると画面に更新されます。

　　例）MAX_HOTKEYSを54にしている場合
　　　　　　@hotkeyset 0 →  0 ～ 26まで
　　　　　　@hotkeyset 1 → 27 ～ 53まで

----------------------------------------
//0281 [2007/08/19] by Rayce

・ipに関する型をunsigned long型に統一
・portに関する型をunsigned short型に統一

・ファイルへの書き込みを fopen() ではなく lock_fopen() を使うように修正（core.c, db.c）
・lock_fopen() で10000回トライしても安全なファイル名が得られない場合はNULLを返すように修正（lock.c）
・gccでの警告潰し（skill.c）

----------------------------------------
//0280 [2007/08/19] by Rayce

・MAPサーバ分散している状態でギルド倉庫を利用すると、MAPサーバ間でアイテムデータの同期が取れないため
　預けたはずのアイテムが見えなくなったり容易にデュープが発生する致命的な問題を修正
　（mmo.h, int_storage.*, intif.c, script.c）
	-> guild_storage構造体にメンバ last_fd を追加
	-> ギルド倉庫のロック取得権をinter鯖に依頼したとき、最後にギルド倉庫を利用したMAP鯖と同じか
	   どうかを照合して、異なる場合はリロードフラグを返す
	-> MAP鯖が intif_parse_TrylockGuildStorageAck() でリロードフラグを受け取ったときは
	   ギルド倉庫のキャッシュを削除してinter鯖から倉庫データを再取得させるようにする
	-> MAP鯖分散してない場合はこれまでの処理とほぼ変化はない
	-> gstorage_save() に引数を1つ追加、SQL専用
	   easyの場合は storage_status や last_fd を書き換えるだけにして、アイテムデータのクエリを発行
	   しなくて済むように改善

----------------------------------------
//0279 [2007/08/18] by Rayce

・暖かい風に関する修正（pc.c, skill.c, status.c）
	-> SC_SEVENWIND追加
	-> 聖はアスペルシオと同じだが、他はSC_SEVENWIND状態となる
	-> SC_SEVENWINDは属性付与（フレイムランチャー等）とは重複しない
	   ただし既にエンチャントポイズンが掛かっている場合は、そのエンチャントポイズンは解除しない
	   毒属性は無くなるが毒付与の機能だけ残る
	-> 聖以外は武器を持ち替えても効果が消えない

　※実質的にAthena1380まで巻き戻した形となります。
　　従ってAthena1399で追加された SC_DARKELEMENT, SC_ATTENELEMENT は使われなくなりました。
　　今後はスクリプトのsc_start命令などからのみ発現可能です。

・db/scdata_db.txtの変更
	-> SC_DARKELEMENT がゴスペル使用時に解除されるようにしてみる
	-> SC_ATTENELEMENT, SC_UNDEADELEMENT がゴスペル使用時とディスペルで解除されるようにしてみる
	-> SC_SEVENWIND は死亡時に解除されない以外は他の属性付与と同じ性質にしてみる

・関数名のtypo修正（pc.c, status.*）
	status_encchant_eremental_end      → status_enchant_elemental_end
	status_enchant_armor_eremental_end → status_enchant_armor_elemental_end

----------------------------------------
//0278 [2007/08/18] by Rayce

・battle_configに関して（battle.*, pc.c）
	-> battle_configの初期化にデフォルト値の設定をまとめる based on eA
	-> デフォルト値がconf/battle_auriga.confの値と合っていない箇所を修正
	-> battle_auriga.confのItem_resをitem_resに改名

・chat_data構造体のメンバの型を最適化（map.h）
・chat.cの細かい整形（chat.c）

----------------------------------------
//0277 [2007/08/18] by Rayce

・charサーバがmapサーバから担当マップ名を受信する際（0x2afa）、1024MAP以上でバッファオーバーフローが
　発生するときはcharサーバではなくmapサーバを落とすように変更（char.c）
・0x2afcでの認証に失敗したときの警告文を少し変更（char.c）
・auth_fifoのメンバ tick をunsigned int型に修正（login.c, char.c）
・login.cおよびchar.cの細かい整形（login.c, char.c）

・skill_additional_effect() の整形（skill.c）
・battle_damage() および battle_delay_damage() に引数を2つ追加（battle.*, skill.c, unit.c）
　スキルIDとスキルLvを参照できるようになります
・以下のスキルはディボーションでダメージを肩代わりできないように修正（battle.c）
	プレッシャー
	コーマ
	NPCダークブレッシング
	グランドクロスの反動

----------------------------------------
//0276 [2007/08/17] by Rayce

・0019以降、Mobに先制攻撃されると経験値が全く入らなくなってしまうバグを修正（mob.c）
・0225以降、キャラを新規作成するとキャラ名の末尾にゴミ文字が付加するバグを多分修正（char.c）
	reported by Cocoaさん and ぽぽりさん

----------------------------------------
//0275 [2007/08/17] by Rayce

・ディボーションの修正（battle.c, skill.c, status.c, unit.c）
	-> 献身対象者から来るダメージによって術者の詠唱が妨害されるように修正
	-> 献身対象者がダメージを受けても献身対象者の凍結/石化/睡眠が解除されないように修正
	-> 献身対象者がダメージを食らった場合、術者に被弾共闘が入るように修正
	-> 献身対象者がダメージを食らったとき術者が位置ズレを起こすので、ダメージディレイ
	   （ヒットストップ）を入れるように修正してみる
	-> 術者がインデュア、オートガード、リフレクトシールド、ディフェンダーを使ったら
	   献身対象者にも同じ効果がかかるように修正
	   ただし被ディボーション者にかかるディフェンダーは強制的にLv1
	-> 術者がインデュア、オートガード、リフレクトシールド、ディフェンダーを解除したら
	   献身対象者も解除されるように修正
	-> ディボーションが終了したとき、献身対象者にかかっているインデュア、オートガード、
	   リフレクトシールド、ディフェンダーを全て解除するように修正
	-> 献身対象者にかかったリフレクトシールドはプレイヤーから攻撃されたときのみ効果が
	   発動するように修正
	-> 定員がいっぱいのときは詠唱できずにスキル使用失敗となるように修正
	-> 違うクルセから既にディボーションされている人にはスキルが使用できないように修正
	-> Mobに対してスキルを使用したとき詠唱反応Mobのタゲ取りができるように修正
	-> ディボーション解除時の処理方法を少し変更
	   skill_devotion_end() は skill_devotion() に取り込んだので削除
	-> skill_devotion3() で既に糸が切れているときはパケット送信しないように改善
	-> stauts_change_start() で不要なステータス再計算をしないように修正

　※インデュア、オートガード、リフレクトシールド、ディフェンダーに関連する部分は本鯖の挙動が
　　イマイチわからないのでeAのコードを参考にしています。

・オートガードのガード確率計算式を一般式化（status.c）
・紛らわしい変数名を変更（clif.c, skill.*）

----------------------------------------
//0274 [2007/08/16] by Rayce

・ステータス異常 SC_ITEM_DELAY と SC_ACTION_DELAY の撤廃（clif.c, map.h, pc.c, status.*）
	プレイヤーにしか必要がない上に、不正検出のための重要なシステムでありながらスクリプトの
	sc_start命令等で操作される可能性があるという極めて良くない実装でした。
	代わりにmap_session_data構造体にメンバ item_delay_tick, drop_delay_tick, drop_delay_count
	を用意してこれまでと同様の不正検出を行うことにします。

・map_session_data構造体のメンバemotion_lasttickをemotion_delay_tickに改名（clif.c, map.h, pc.c）
・map_session_data構造体のメンバinfinit_tigereyeをspecial_stateに変更（map.h, pc.c, status.c）

・dropitem命令を使ったスクリプトの引数指定方法が間違っていたので修正（npc_quest_kiel.txt）
	reported by Cocoaさん

----------------------------------------
//0273 [2007/08/15] by Rayce

・倉庫関連の関数を見直し（mmo.h, guild.c, intif.c, storage.*, unit.c）
	-> intif_parse_LoadStorage() の内容を storage_storageload() として分離
	-> intif_parse_LoadGuildStorage() の内容を storage_guild_storageload() として分離
	-> storage_storage_quit() および storage_guild_storage_quit() はそれぞれ
	   storage_storageclose() および storage_guild_storageclose() にまとめる
	-> ギルド解散時にギルドメンバーが倉庫を開いていた場合の処理を少し書き換え
	-> storage構造体およびguild_storage構造体にdirtyメンバを追加
	   倉庫内アイテムのデータが変更されたときのみセーブを行うように改善
	-> 細かい整形

・pc_takeitem_sub() でPT未所属でもPT共有設定とみなされていた問題を修正（pc.c）
・account_db_final() におけるキャストミスを修正（login.c）
	thanks to FPE in AthenaProject Forum

----------------------------------------
//0272 [2007/08/14] by Rayce

・死んだ状態から@loadや@goなどで pc_setpos() を実行すると、デスペナが無くなったり
　移動先ですぐに死んでしまう等の問題を修正（clif.c, pc.c）
・VC++で警告レベルを /W4 にした際に得られた結果の中で気になった箇所を修正
　（db.c, malloc.c, socket.c, char.c, int_guild.c, clif.c, map.h, pc.c, status.c, login-converter.c）

・converterの起動時にもコマンドライン引数をサポートする（converter.*）
　　以下のコマンドを使ってconfファイルへのパスを変更することができます。

　　converter
	--converter-config <filename>

----------------------------------------
//0271 [2007/08/13] by Rayce

・AthenaProject2314よりmerge、thanks to Paraさん
	-> clif_sitting() を少し変更して「立つ」処理もまとめる（clif.*, skill.c）
	-> スクリプトにgetcartlist命令を追加（script.c）

・カート内アイテム削除命令を一式追加（script.c）
　これらはプレイヤーがカートを持っていなくてもアイテムの削除を行います
　カートがあるときだけ削除したい場合はcheckcart関数でカートの有無をチェックする必要があります
	delcartitem命令
	delcartitem2命令
	clearcartitem命令

・delinventory命令をdelitem2命令に改名（script.c）
	カート用の命令と一律の名前にするため
	delinventory命令をスクリプトで利用している場合は各自delitem2命令に変更してください

----------------------------------------
//0270 [2007/08/13] by Rayce

・db/item_avail.txtを使ったアイテムをshop販売するとアイテム数超過扱いにされて
　アイテムが買えない問題を修正（npc.c）
	ただし販売品目の中でavail元のアイテムIDが重複している場合にアイテムを正しく
	買うことができませんが、これはクライアントの仕様に依ります。
	例えばdb/item_avail.txtに 600,512 を記述して600のIDを作ったとき
		prontera.gat,116,192,4	shop	shopper	112,512:10,600:10
	となっている場合は600のアイテムを買うことができません（恐らく512になる）
	この事例が発生し得るときはdb/item_avail.txtを使わないことをお勧めします。

・ELE_MAXを10より小さい値に設定している場合、モンスター情報を使うと「unknown attr type」
　のエラー文が出るバグを修正（clif.c）
・鉱石の製造確率でDEX依存部分の計算式が間違っていたのを修正（skill.c）
	reported by Cocoaさん

----------------------------------------
//0269 [2007/08/12] by Rayce

・スキル使用チェック時のアイテム消費処理を skill_item_consume() としてまとめる（skill.c）
	-> inf2で処理分岐せず、植物栽培も一つにまとめる
	-> アイテム消費なしにする場合はgotoを使わずitem_nocostフラグをオンにする
	-> 副作用としてホムがジェムの必要なスキルを使うとき、主人がミストレスカードを
	   装備していればジェム消費なしになる

----------------------------------------
//0268 [2007/08/10] by Rayce

・nextやselectで待機中に run_script() が再帰的に実行されると元のスクリプトが
　破棄されてスクリプトがそれ以降停止してしまうバグを修正（script.c）
・別MAPに移動すると地面に設置したスキルユニットが消滅するように修正（pc.c）
	reported by Cocoaさん

----------------------------------------
//0267 [2007/08/09] by Rayce

・クレイモアトラップが攻撃されても移動しないように修正（battle.c, skill.c）
・PTメンバーのHPが0x7fffを越えている場合、HPメーターが更新されない問題を修正（clif.c）
　MAXHPが0x7fffのときは0x7fffで規格化する
・party_send_xyhp_timer() を少し修正（party.c）
・gccでの警告修正（pc.c）

・以下のファイルの改行コードをCR/LFに変更
	script/npc/town/npc_town_hugel.txt
	src/common/zlib/
	src/map/status.c

----------------------------------------
//0266 [2007/08/01] by Rayce

・オートスペルでリムーブトラップが使えないバグを修正（battle.c, skill.c, unit.c）
	db/skill_db.txtのinfが32の罠の場合は、場所スキルとしてではなく対象指定スキルとして
	扱われなければなりません

・運命のタロットカード専用の状態異常 SC_THE_MAGICIAN, SC_STRENGTH, SC_THE_DEVIL, SC_THE_SUN の
　使い方が特殊だったので仕様変更（skill.c, status.*）
	-> 魔法師、力、悪魔、太陽の効果がそれぞれ重複するようにしてみる
	-> 不要になった SC_TAROTCARD を削除

・ディテクティング用の状態異常 SC_DETECTING の使い方が特殊だったので仕様変更（skill.c, status.*）
	-> サイトと同じ処理方法で周囲のPCおよびMOBを炙り出す
	-> ディテクティングでNPCインビジブルが見破れなくなるが当面の間仕様にしておく
	-> 不要になった SC_DETECTING を削除

----------------------------------------
//0265 [2007/08/01] by Rayce

・スキルのstatictimerをギルドスキルも一括して扱えるように変更（map.h）
・臨戦態勢、激励、治療、緊急召集のスキルディレイはstatictimerを使うように変更（clif.c, skill,c status.*）
　以下のステータス異常は不要になったので削除
	SC_BATTLEORDER_DELAY
	SC_REGENERATION_DELAY,
	SC_RESTORE_DELAY
	SC_EMERGENCYCALL_DELAY,
・スキルのstatictimerの初期化が二重に行われていた無駄を修正（pc.c）
	pc_setnewpc() ではなく pc_authok() だけで行えば良い

----------------------------------------
//0264 [2007/08/01] by Rayce

・オートスペル使用後にディレイが無かったのを修正（battle.*, skill.*）
	battle_auriga.confに skill_autospell_delay_enable と bonus_autospell_delay_enable を追加
	スキル由来かアイテムボーナス由来かで個別に設定できます
	デフォルトでは共にyesですが、noにすれば今まで通りディレイ無しになります

・skill_bonus_autospell() の引数tickがunsigned int型になっていなかったので修正（skill.*）

----------------------------------------
//0263 [2007/07/30] by Rayce

・サーバースナップショット（version.h）
・不要なファイルをフォルダごと削除
	./script/mosnter/etc

----------------------------------------
//0262 [2007/07/30] by Rayce

・スキルIDからスキルツリー情報を取得する際の処理を高速化（homun.*, pc.*）
	homun_search_skilltree(), pc_search_skilltree() 追加。
	バイナリサーチを使って検索します。
	db/homun_skill_tree.txtおよびdb/skill_tree.txtがそれぞれスキルIDの昇順に並んで記述されている
	ことを前提としています。
	並んでいなくてもデータベース読み込み時に自動的に補正されますが、読み込み速度が低下する可能性が
	あるので出来るだけソート済みの状態にしておいてください。
	デフォルトのdbは全てソート済みなので問題はありません。

	例）143が142よりも前に記述されているのは推奨されない
		0,0,143,1,0,0,0,0,0,0,0,0,0,0,0,0,0//NV_TRICKDEAD	#死んだふり#
		0,0,142,1,0,0,0,0,0,0,0,0,0,0,0,0,0//NV_FIRSTAID	#応急手当#

・AthenaProject2307に合わせてscript/monster/etcをscript/monster/eventに変更
・npc_monster_crystal.txtでエラーが出るので修正
・doc/client_packet.txt更新

----------------------------------------
//0261 [2007/07/29] by Rayce

・@コマンド処理を高速化（atcommand.*, map.c）
　　　オープンハッシュを用いてコマンド文字列からatcommand_infoを検索します。
　　　特に@autolootや@changemaptypeなど比較的新しく追加されたコマンドに対する検索速度が劇的に
　　　向上します。

	-> COMMAND_HASH_SIZEを定義、デフォルトは127
	-> AtCommandInfoにnextメンバを追加、外部ハッシュのリスト用
	-> atcommand_create_hashtable() 追加、ハッシュテーブルを作成する
	   サーバ起動時のみ呼ばれる、@reloadatcommandでは呼ばれない
	-> command2hash() 追加、アルゴリズムはscript.cの calc_hash() と同じ
	-> get_atcommandinfo_byname() をハッシュ検索に変更
	-> コマンド名からatcommand_infoを参照する場合には get_atcommandinfo_byname() を利用する
	-> synonym_table_構造体のcommandメンバをconst char型に変更し、aStrdupしないように改善

・0253のbattle_auriga.confの tkcombo_delay_lower_limits を入れ忘れていた箇所を修正（battle.c）
・path_blownpos() を少し最適化、MAX_BLOWNPOSを定義（path.c）

----------------------------------------
//0260 [2007/07/28] by Rayce

・装備中のアイテムは矢作成スキルで矢に変換できないように修正（clif.c, skill.c）
	AthenaProject BTS報告 Mopyaさん and Cocoaさん thank's

・is_atcommand() を名前解析部分とコマンド実行部分に分離する merged from eA（atcommand.*, clif.c, script.c）
	コマンド実行部分は is_atcommand_sub() とする。
	スクリプトのgmcommand命令のように名前解析が不要な場面においてはこちらを使うことで無駄な処理を省略する。
	ついでに is_atcommand() の引数gmlvlを削っておく。

・以下の@コマンドに対してsynonymous commandを作った場合、正常に機能しなかった問題を修正（atcommand.c）
	@kamib, @kamic
	@monstermap
	@str, @agi, @vit, @int, @dex, @luk

----------------------------------------
//0259 [2007/07/28] by Rayce

・マキシマイズパワー使用中にログアウトして再度ログインすると、SPの減少速度が速くなるバグを修正
　（from AthenaProject BTS  skill.c, status.c）
	save/scdata.txtからステータス異常を復帰する場合、status_change_start() のtickには
	必ず残り時間が入っています。
	従って一定時間ごとに status_change_tiemr() 呼び出す必要のあるステータス異常は、タイマーの
	インターバルをtickではなくval2～4のいずれかに入れるように統一します。
	tickは関数内部で書き換えるため、status_change_start() を呼び出すときのtickは0で構いません。

・上記の変更に合わせて以下のステータス異常を修正（skill.c, status.c）
	チェイスウォーク
	クローキング
	インビジブル
	属性場

・養子解体するとMAPサーバの接続が切断される致命的なバグを修正（char.c）
・養子の縁組および解体すると親の持っているカードスキルが消失してしまうバグが発生していたので、
　pc_calc_skill() を直接呼ぶのではなく status_calc_pc() を経由するように修正（chrif.c, pc.c）
・069以降、divorce関数で離婚成功しても常に0が返ってくるバグを修正（script.c）
・離婚および養子解体が成功したときはキャラデータをセーブするように強化（pc.c）

----------------------------------------
//0258 [2007/07/27] by Rayce

・AthenaProject2313よりmerge、thanks to Blazeさん
　　・以下のベインス追加NPCスキルを実装
	「アースクエイク」「ファイアブレス」「アイスブレス」「サンダーブレス」「アシッドブレス」
	「ダークネスブレス」「出血攻撃」「パルスストライク」「ヘルジャッジメント」「イビルランド」
　　・古く青い箱、古い紫色の箱、古いカード帖から得られるアイテムをラヘル時点に更新
	（item_bluebox.txt、item_violetbox.txt、item_cardalbum.txt）
　　・フィゲルのWarpを修正
	（npc_warp_town.txt）

・トルリョチャギの周囲へのスタン効果は skill_additional_effect() に記述するように修正（skill.c）
・skill_unit_onplace_timer() の一部を少し整形（skill.c）

----------------------------------------
//0257 [2007/07/27] by Rayce

・AthenaProject2312よりmerge、thanks to Blazeさん
　　・TheSignクエスト実装（npc_quest_thesign.txt）
　　・フィゲルクエスト2種実装、1種修正
	（npc_town_hugel.txt）
	（npc_town_airport.txt）
	（npc_town_lighthalzen.txt）
　　・ラヘルクエスト修正（npc_town_rachel.txt）
　　・ラヘル案内要員追加（npc_misc_guide.txt）
　　・ラヘルジョンダ職員のセーブ位置修正（npc_misc_zonda.txt）
　　・ラヘル新規追加頭装備作成NPC実装（一部未実装）（npc_quest_hat5.txt）
　　・ガンスリンガー武器作成クエスト5種実装（npc_job_28gunslinger.txt）
　　・初心者修練場で職業適性検査の結果と判定に相違が出ていたのを修正（npc_job_00novice.txt）
　　・キル・ハイルクエスト専用マップのwarpが2重化していたのを修正（npc_quest_kiel.txt）
　　・飛行船で新経路のラヘルの不具合修正（npc_town_airport.txt）
　　・ゲフェニアのテレポート不可を可に変更（mapflag.txt）

----------------------------------------
//0256 [2007/07/27] by Rayce

・db/job_db1.txtで読み込む武器のタイプがWT_MAXに対応してなかったのを修正（status.c）
・db/refine_db.txtの初期化時、MAX_WEAPON_LEVELに対応してなかったのを修正（status.c）

・conf/battle_auriga.confの pc_hit_stop_type をデフォルトで0に修正（battle.c）
　位置補正情報を送らないので所謂ヨーヨー現象が発生するようになります

----------------------------------------
//0255 [2007/07/26] by Rayce

・0244で保留にしていた bAddSkillHealRate の中身を実装（battle.c, skill.*）
　回復量補正は skill_fix_heal() で行う
　ついでにMAX_SKILL_HEAL_UPを10から5に縮小しておく
	merged from AthenaProject2311 thanks to ICOさん

　※指定可能なスキルは以下の通り
	ヒール
	治療の手助け
	応急手当
	ポーションピッチャー
	スリムポーションピッチャー
	君だけは護るよ
	あなたに尽くします
	カオティックベネディクション
	サンクチュアリ
	イドゥンの林檎
	カアヒ

・ランダムにセルを選択する機能はないので、map_searchrandfreecell() を
　map_searchfreecell() に改名（map.*, npc.c, skill.c）

・duplicate元のスクリプトと自身のMAPが異なる場合、duplicate元のスクリプトのMAPが読み込み対象外
　だとduplicateに失敗するので、duplicate元をMAP非配置型に修正しておく
	script/npc/quest/npc_quest_artifacts.txt
	script/npc/town/npc_town_airport.txt
	script/npc/town/npc_town_lighthalzen.txt

----------------------------------------
//0254 [2007/07/26] by Rayce

・AthenaProject2311よりmerge、thanks to ICOさん
　　・「カウプ」で魔法などが回避できなかった問題を修正（battle.c）
　　　　通常攻撃、およびプレッシャーを除く全てのスキル攻撃を1回だけ回避することができます
　　　　判定の優先順位は セイフティウォール > カウプ > ニューマ
　　・「カイト」で範囲魔法を反射できない不具合を修正（battle.c）
　　・「ソウルブレイカー」にカタール研究の効果が乗っている不具合を修正（battle.c）
　　・「喫煙」でダメージが発生する不具合を修正（battle.c, skill.c, db/skill_db.txt）
　　・@monster, @monstermap でMobがスタックすると召喚に失敗する問題を修正（atcommand.c）

----------------------------------------
//0253 [2007/07/26] by Rayce

・アイテムボーナスのステータス固定用の fix_status を構造体としてまとめる（map.h, pc.c, status.c）
・status_calc_pc() でステータス固定計算後にspeedとaspdの補正を行うように修正（status.c）
・@jumpで指定する座標を省略可能に拡張（atcommand.c）
　省略時は (0,0) と同義になりMAP内にランダムに飛ぶ

・battle_auriga.confに tkcombo_delay_lower_limits を追加（battle.*）
　	AGIとDEXが異常に大きい（350とか）場合、テコンの蹴り構えのモーションが短すぎて蹴りを発動
	できないバグが発生しているので、モンクのコンボと同様に最低入力保障時間を設けます

----------------------------------------
//0252 [2007/07/26] by Rayce

・ペットのルートアイテム検索について（pet.c）
	-> 最初にアイテムを見つけた時点で検索を中止していたバグを修正
	-> 検索範囲を 57x57 から 7x7 に縮小
	   ルートに行く射程距離は3なので7x7より広く検索する意味はない
	-> pet_ai_sub_hard_lootsearch() を少し修正

・map_readmap() で出力されるMAP番号を+1しておく（map.c）
・0251に添付し忘れていた conf/map_auriga.conf を追加
・MAP名に .gat が付いてなかった部分を修正（conf/map_auriga.conf）

----------------------------------------
//0251 [2007/07/26] by Rayce

・AthenaProject2310よりmerge、thanks to Blazeさん
　　・ラヘル実装
　　・ラヘルクエスト5種追加（npc_town_rachel.txt）
　　・飛行船に新経路追加（npc_town_airport.txt）
　　・ジョンダ職員追加（npc_misc_zonda.txt）
　　・宿屋NPC追加（npc_misc_inn.txt）
　　・各warp修正（npc_warp_town.txt、npc_warp_dun.txt）
　　・新規追加monsterの名称を修正
　　　（npc_monster_rafild.txt、npc_monster_rasan.txt、npc_monster_icedun.txt）
　　・mapflag修正（mapflag.txt）
　　・map_auriga.confをラヘル対応に更新、新マップ情報だけ追加

----------------------------------------
//0250 [2007/07/26] by Rayce

・AthenaProject2308よりmerge、thanks to Blazeさん
　　・アマツ通行手形クエスト修正（npc_town_amatsu.txt）
　　・バンジージャンプのHP計算を修正（npc_town_umbala.txt）
　　・ローグ転職クエストの一部箇所で進行不可になってしまうのを修正（npc_job_17rogue.txt）
　　・スロットエンチャントNPCを整形（npc_quest_slotenchant.txt）
　　・ノーグハルト追加ランダムアイテムをノーグハルト時点のデータで実装
　　　（item_petbox.txt、item_food.txt、item_mask.txt、item_jewel_box.txt）

----------------------------------------
//0249 [2007/07/26] by Rayce

・AthenaProject2306よりmergeの続き、thanks to ICOさん
　　・プレッシャーがエンペリウムに対してスキル使用失敗になるように修正（battle.c, skill.c）
　　・混乱状態の敵にパンボイスを使用した場合、相手の混乱状態を解除するように修正（skill.c）
　　・主人が死亡している時にもペットが支援攻撃した問題を修正（pet.c, pc.c）
　　・主人が9マスより遠くに離れるとペットが支援攻撃を止めるように仕様を変更（pet.c）
　　・見た目がPCではないMobが指弾を使うと一瞬姿が消えてしまう問題を修正（skill.c）

・PETのAIを少し最適化（pet.c）
	-> 親密度が0以下のときにルートアイテムの検索をしない
	-> 主人と距離が離れすぎているときにルートアイテムの検索をしない

----------------------------------------
//0248 [2007/07/25] by Rayce

・AthenaProject2306よりmerge、thanks to ICOさん
　　・運命のタロットカードの固定詠唱時間を通常詠唱時間に修正（db/skill_cast_db.txt）
　　・ソウルブレイカーの魔法ダメージ部分が対象のカード効果によって軽減されるように修正
　　　また属性軽減効果が二重に計算されていた問題を修正（battle.c）

　　・アイテムボーナスのHP/SPドレインの発動確率が合算で計算されていた不具合を修正
　　　（battle.c, map.h, pc.c, status.c）
　　　DrainRate系とDrainValue系はそれぞれ独立して発動確率を計算するようになります

　　・battle_auriga.confの「％吸収を有効にする」項目を「有効とする吸収タイプ」に変更（battle.*）
　　　デフォルトでは2で、DrainValue系による一定吸収のみが行われる
		magic_attack_drain_per_enable   → magic_attack_drain_enable_type
		misc_attack_drain_per_enable    → misc_attack_drain_enable_type
		weapon_reflect_drain_per_enable → weapon_reflect_drain_enable_type
		magic_reflect_drain_per_enable  → magic_reflect_drain_enable_type

　　・battle_weapon_attack() と battle_skill_attack() におけるHP/SP吸収処理を
　　　battle_attack_drain() にまとめる（battle.c）

　　・battle_auriga.confに mob_middle_boss_delay_rate, mob_mvp_boss_delay_rate を追加（battle.*, npc.c）
　　　通常MOB、中ボス、MVPボスそれぞれ別々に再出現までの時間の割合を設定できます

　　　※db/mob_db.txtのModeにBoss属性が設定されているかどうかだけで中ボスの判定を行います
　　　　Athenaのように出現時間には依存しないので注意してください

----------------------------------------
//0247 [2007/07/24] by Rayce

・AthenaProject2305よりmerge、thanks to number24さん
	-> MinGWのときは -lmysql を入れるように修正
	-> MySQLに関するリンカオプションの設定をトップのMakefileに集める
	-> doc/sqllogin.txtにMinGW環境下でコンパイルするときの注意点を追加

----------------------------------------
//0246 [2007/07/24] by Rayce

・AthenaProject2304よりmerge、thanks to Blazeさん
　以下Readmeより転載
　　・percenthealで-100以下のみ死亡判定を出すように修正
　　・テコン系列がレベルアップ時の支援効果を10分継続に修正（pc.c）
　　・NPCスキルの射程を修正（skill_db.txt）
　　・各スキルの消費SPを修正（skill_require_db.txt）

----------------------------------------
//0245 [2007/07/24] by Rayce

・AthenaProject2303より以下の項目についてmerge、thanks to ICOさん
	-> 死んだふり中に攻撃することができた不具合を修正（unit.c）
	-> 16bitおよび24bitカラーのギルドエンブレムをデフォルトで使用できるように
	   battle_auriga.confの guild_emblem_colors を3に変更しておく
	-> doc/db_ref.txtに召喚系スキルについての説明を追記

----------------------------------------
//0244 [2007/07/24] by Rayce

・AthenaProject2303より、以下のアイテムボーナス13種を追加、thanks to ICOさん
　スキルの固定詠唱時間の補正は skill_castfix() 内にまとめる
	bFixMaxHP
	bFixMaxSP
	bFixBaseAtk
	bFixMatk
	bFixDef
	bFixMdef
	bFixHit
	bFixCritical
	bFixFlee
	bFixAspd
	bFixSpeed
	bAddFixCastRate
	bAddSkillHealRate

　※bAddSkillHealRateについては準備をしただけで実際の効果は未実装にしています

----------------------------------------
//0243 [2007/07/23] by Rayce

・コマンドライン引数の仕様を変更 merged from eA
　　今までは例えばMAPサーバであれば、コマンドライン引数の第一引数がmap_auriga.confへのパス、
　　第二引数がbattle_auriga.confへのパス、というように一意的に決まっていましたが、非常に使い
　　勝手が悪いので仕様を変更します。
　　以下に示すコマンドを使って各confファイルへのパスを変更することができます。

　　login-server
　　　　--login-config <filename>

　　char-server
　　　　--char-config <filename>
　　　　--inter-config <filename>

　　map-server
　　　　--map-config <filename>
　　　　--battle-config <filename>
　　　　--atcommand-config <filename>
　　　　--script-config <filename>
　　　　--msg-config <filename>

　　これらは同一マシンで複数のキャラサーバやマップサーバを動かすときに有用です。
　　詳細は doc/distribute_servers.txt に記載してあるので参考に。

　　※eAにあるコマンド --help と --version は特に必要性を感じなかったためmergeしてません。

・auriga-startの修正
	-> 上記のコマンドライン引数仕様変更に対応
	-> 新規作成された ./save/account.txt に\tが一つ不足していたので修正
	-> saveファイルを新規作成する際、win32_start.batと同様に以下の3つのファイルも作成する
	   　./save/accreg.txt
	   　./save/g_storage.txt
	   　./save/scdata.txt

・grf-files.txtへのファイルパスはコマンドライン引数からではなくmap_auriga.confで設定するように変更
　conf/map_auriga.confに grf_path_txt キーを追加（map.c）
・マップキャッシュmap.infoはカレントディレクトリに作成するようにデフォルト設定を変更（map.c）
・pc_memo() を少し修正（pc.c）

・srand() および atn_srand() による種まきはmainでまとめて行うように変更（core.c, login.c, map.c）
・VCのときに使うランダム定義がRANDOMSTD2XになっていたのでRANDOM64に修正
　ついでに書き換えて簡素化（utils.h）

・doc/server_build.txtに少し加筆
・doc/distribute_servers.txtに情報加筆

----------------------------------------
//0242 [2007/07/23] by Rayce

・ROメールシステムの設計見直し（int_mail.*, clif.*, intif.c）
	-> mail_dataを取得するときにメモリをアロケートしないように改善
	   mail_free() は不要になったので撤廃
	-> 最大受信数30を越える場合、送信成功として扱われるがデータそのものは破棄するようにしておく
	   サクライの詳細な実装が不明なのでこれは当面の間これを仕様とする
	   添付アイテム、Zenyもろとも消えてしまうので注意すること
	-> mail構造体のstoreはメールデータの個数を保有する重要な変数なので、エラーが発生しないように
	   値が異常でないかどうかチェックする
	   異常時は「stored number mismatch!!」の警告が出ますが、内部で自動的に正しい値に補正されます

・キャラ名からキャラ情報を直接取得できるように char_nick2id() を char_nick2chardata() に変更（char.*, int_mail.c）
・ROメールを同一アカウントの他キャラクターに送信しようとすると添付アイテムが消失してしまうバグを修正（int_mail.c）

----------------------------------------
//0241 [2007/07/22] by Rayce

・0239以降、db_clear() と db_final() のtableがNULLだったときサーバクラッシュする問題を修正（db.c）
・mob_data構造体のメンバrecall_flagをビットフィールドに変更（map.h, mob.c, skill.c）
・calc_hash() の中に SCRIPT_HASH_SIZE の剰余計算を丸め込む（script.c）
・DEBUG_HASHの出力書式を整理（script.c）

----------------------------------------
//0240 [2007/07/21] by Rayce

・MAPサーバ停止時の終了処理の高速化（npc.c）
	do_final_npc() でMAPに出現中のMOBを削除する際は、一旦復活しないMOBに設定してから
	unit_remove_map() を呼び出します。
	これより不要な再出現タイマーの設定処理が省略されます。
	また map_id2bl() を2回呼ぶ必要がなくなります。
	PETとHOMがまだMAPに残っているはずはないのですが、念のため unit_free() で後始末します。

　※大変荒い実験な上に状況によってマチマチですが、処理速度が約2倍になっていることを確認しました

・monster定義で設定したMOBの座標が完全にスタック位置だった場合、警告を出力してMOBの出現を取り消す
　ように修正（npc.c, mob.c）
	範囲内の空きセルをランダムで50回検索しても空きセルが見つからなかった場合は1秒後に検索を
	やり直す仕様になっています。
	しかし指定座標の周囲に全く空きセルがない場合は検索失敗になるのは確実であり、そのために常に
	1秒毎に検索を行い続けるのは負荷にしかなりません。
	従って最初の mob_spawn() に失敗した場合は map_searchrandfreecell() で空きセルのチェックを
	行うようにします。
	チェックに引っ掛かったらデータは破棄します。
	このとき再検索用の1秒タイマーは動いたままになっているので、mob_spawn() のnullpoチェックは
	外すように変更しています。

・以下のスクリプトにおいて上記の変更により警告が出るのでコメントアウト
	monster/dungeon/npc_monster_ctower.txt
	monster/dungeon/npc_monster_gefdun.txt
	monster/dungeon/npc_monster_izdun.txt
	monster/dungeon/npc_monster_treasure.txt
	monster/field/npc_monster_cmdfild.txt
	monster/field/npc_monster_mjolnir.txt
	monster/field/npc_monster_prtfild.txt

----------------------------------------
//0239 [2007/07/21] by Rayce

・メモリ消費を若干節約するため、dbn構造体のメンバcolorとdeletedをint型からchar型に変更してみる（db.h）
・db_clear() 内部で db_erase() を使えるようにするため db_foreach() ではなく db_final() の処理方法を
　利用するように修正（db.c）
	db_final() の処理本体を db_clear_sub() として分離して共用化

・MAPサーバ停止時、キャラを全て切断した直後にcharサーバにパケットを送信するように修正（chrif.*, map.c）
	プレイヤーがまだ残ったままの状態でサーバ停止すると全キャラのデータをセーブすることになり
	ますが、mmo_charstatus構造体は比較的大きい（1人当たり約12kB）ため、パケットサイズがかなり
	大きくなります。
	従って切断が完了した時点で chrif_flush_fifo() を呼び出してパケットを送信しておきます。
	charサーバがこの大きなパケットを処理している間に do_final_battle() 以下の時間の掛かる処理を
	行うことにより、Auriga全体の終了処理の高速化が見込まれます。

----------------------------------------
//0238 [2007/07/21] by Rayce

・map_searchrandfreecell() をより汎用に使える関数に変更（map.*, skill.c）
　第1引数のcell_xy型をNULLにすると、空きセルのリストは返さず空きセルの数だけを取得できます

・以下の条件でペットの卵情報が削除されずセーブデータにゴミが残り続ける問題を修正（mob.c, unit.c）
	-> mobにペットの卵をルートさせたままの状態でサーバを停止する
	-> ペットの卵をルートしたmobを@killmonster2で消去する
	-> ペットの卵をルートしたmobをペットとして捕獲する

----------------------------------------
//0237 [2007/07/21] by Rayce

・0182の clif_parse_GuildRequestInfo() に関する変更を巻き戻す（clif.c, guild.c, map.h）
	各種ギルド情報が上手く更新されなかったりと色々問題が生じているようなので
	巻き戻すことにします。
	何が良い手が浮かんだら再度取り掛かるかもしれません。

・あまり意味のないlast_deadtimeをmob_data構造体から削除（map.h, unit.c）

----------------------------------------
//0236 [2007/07/18] by Rayce

・db_insert() および linkdb_replace() の返り値を変更（db.*）
	データを置換する前のdataをvoid*型で返すようにします
	データの新規追加の場合はNULLが返ってきます
・treedbおよびlinkdbに関して、searchが不要な部分を短縮して検索処理効率を上げるように改善
　（friend.c, guild.c, npc.c, script.c）

・TXT: 0227以降、ギルド告知や役職に#が連続で付加するバグが発生していたので修正
　（int_guild.c, char-converter.c）

----------------------------------------
//0235 [2007/07/17] by Rayce

・DEBUG_VARSの出力結果を元に修正（db/item_db.txt）
	bonus bUnbreakableArmor,n; → bonus bUnbreakableArmor,0;
・スクリプトの命令/関数/ラベル/変数のデータ量が増えてきたので、SCRIPT_HASH_SIZEを1021に引き上げ（script.c）
	外部ハッシュに繋がれるのがだいたい4～5個くらいに集約

・SQL: GCCのときにコンパイルエラーになっていたので修正（int_guild.c）

----------------------------------------
//0234 [2007/07/17] by Rayce

・アカウント名、キャラクター名、Emailの文字数制限を tool/ladmin, tool/cgi/, tool/php の各ファイルに
　対しても適用するように修正
	アカウント名   : 24 → 23文字
	キャラクター名 : 24 → 23文字
	Email          : 40 → 39文字

　※0200から行ってきたバッファオーバーラン対策はこれで完了です。
　　念のためセーブデータの整合性を再度確認しておくと良いです。

・db/packet_db.txtを0x2bcまで更新
・doc/client_packet.txtに情報追加

----------------------------------------
//0233 [2007/07/17] by Rayce

・SQL: converterの整理
	バッファオーバーフロー対策のための文字数制限を適用
	出来るだけlogin, char, interからコピペしたものに置換

----------------------------------------
//0232 [2007/07/17] by Rayce

・NPC定義のチェックを強化（npc.c）
　以下のように余計な文字が含まれる場合、"bad ??? declaration : ???" が表示されエラーとなります。
　警報が鳴るように強化されているので注意してください。
　またエラー箇所を特定しやすくするため、エラー行が出力されるように改善されています。

　　１）script定義に ,0 が余計に付いている
　　　　	prontera.gat,164,190,4,0	script	Test(1)	112,{}
　　２）duplicate定義の () の後ろにさらに ) が存在している
　　　　	prontera.gat,164,190,4	duplicate(Test(1))	Test2	113
　　３）warp定義の末尾に ,4 が余計に付いている
　　　　	prontera.gat,150,188	warp	000	1,1,izlude.gat,130,115,4
　　４）mob定義に ,0 が一つ多い
		prontera.gat,0,0,0,0,0	monster	--ja--	1002,1,1000,1000
　　５）mapflag定義に座標はない
　　　　	prontera.gat,0,0	mapflag	nomemo	dummy

　※BCC特有のsscanfバグにより、npc_parse_mapflag() だけは%n変換を使えません。
　　strlenで文字列長をチェックして余計な文字が残ってないかの判定を行っています。

・warp定義において、向き指定は省略可能であることを正式な仕様とする（npc.c）
　以下は今まで同様どちらも正常です。
	prontera.gat,148,188,0	warp 001	1,1,izlude.gat,132,115
	prontera.gat,148,186	warp 002	1,1,izlude.gat,132,115
　battle_auriga.confのwarp_point_debugがyesのときに向きを指定できるだけであり、基本的には不要です。
　詳細はdoc/script_ref.txtを参照。

・上記変更によりエラーとなるスクリプトの修正
	script/npc/town/geffen.txt
	script/npc/town/morocc.txt
	script/npc/town/niflheim.txt

----------------------------------------
//0231 [2007/07/17] by Rayce

・mapreg_setregstr() のコードを簡素化（script.c）
・文字列型のMAP永続変数において、1023文字まではデータの有効性を保証するように修正（script.c）
	文字列データのロードおよびセーブが正常に行われることを意味します。
	これよりも長い文字数を使った場合の挙動は未定義とします。

・doc/script_ref.txtに変数名として使える最大文字数に関する情報を追記
・SQL: MAP永続変数名として利用可能な最大文字数をTXTに合わせて255文字までに制限

・TXT: BCCのみsave/account.txtの%newid%行の読み込みに失敗するバグを修正（login.c）
・TXT: save/party.txtの読み込み時に%newid%行のチェックは不要なので省略する（int_party.c）
・TXT: save/guild.txtの読み込み時の空ギルドチェックを省略する（int_guild.c）
	この時点で guild_txt_delete() を呼び出すとギルド倉庫のデータが削除されずにゴミが残り続けたりするなど
	処理が中途半端になってしまうため。
	どちらにせよ mapif_parse_GuildInfo() で空ギルドチェックは行われるので問題はない。

----------------------------------------
//0230 [2007/07/16] by Rayce

・0225以降、##変数を保存するときにcharサーバがクラッシュする致命的なバグを修正（char.c）

・TXT: save/accreg.txtの読み込み時に、各データが半角スペースで区切られているかどうかのチェックを入れる（inter.c）
・TXT: ##変数が多量に登録されているとき、全ての##変数を読み込めない可能性のあるバグを修正（login.c）
・TXT: BCCのみ##変数の読み込みに失敗する可能性のあるバグを修正（login.c）
	save/accreg.txtと同じ処理方法に変更、詳細はAthena-Readme1593を参照

----------------------------------------
//0229 [2007/07/15] by Rayce

・バッファオーバーフロー対策の文字数制限、0225の続き（login.c）
	アカウントID 24 → 23
	アカウントパスワード 24 → 23
	アカウントメールアドレス 40 → 39
	##変数の名前 32 → 31

・login.cの全体的な修正および整形
　　　-> sex番号からsex文字への変換は sex2str[] を使うように
　　　-> mmo_auth() でアカウントが見つからなかった場合、パスワードの暗号化が有効なときはlog/login.logに
　　　   パスワードを出力しないように修正
　　　   暗号化されているパスワードを書かれても文字化けで意味がないため
　　　-> パケット0x277は暗号化されてないログイン要求らしいので修正
　　　-> コードを簡潔にするためTXTのときもlastipを保存するように変更してみる
　　　   ただしセーブデータとして書き出されるのは従来通りSQLのみ
　　　-> account_load_str() を呼び出す場合、引数となる文字列の末尾には必ず \0 を付けるように修正
　　　   SQLのときに関数内部でsprintfするため \0 がないとバッファオーバーランが発生する
　　　-> login_httpd_auth_func() のuseridの文字列長が信頼できないのでstrnlenでチェックする

・strnlenが使えない環境のために自作のstrnlenをeAから移植（unit.*）

----------------------------------------
//0228 [2007/07/14] by Rayce

・0222の時点でコンパイルエラーになっていたので修正（clif.c）
・int_homun.c, int_party.c, int_pet.c, int_storage.cの細かい整形
・バッファオーバーフロー対策のための文字数制限、0225の続き
	ホムの名前 24 → 23
	パーティ名 24 → 23
	パーティメンバー名 24 → 23
	ペットの名前 24 → 23

・SQL: 以下で利用されてないフィールドをSELECTしないように修正
	`homun_id` （int_homun.c）
	`party_id` （int_party.c）
	`pet_id`   （int_pet.c）
	`char_id`  （int_status.c）

----------------------------------------
//0227 [2007/07/14] by Rayce

・ギルド関連についてバッファオーバーフロー対策のための文字数制限、0225の続き（int_guild.c）
	ギルド名 24 → 23
	ギルドマスター名 24 → 23
	ギルドメンバー名 24 → 23
	ギルドの役職名 24 → 23
	ギルド追放時メッセージ 40 → 39

・int_guild.cの細かい修正と整形
	-> MAX_GUILDLEVELの値を増やしても50までしかギルドLvが上がらなかったバグを修正
	-> mapif_parse_GuildSkillUp() でスキルLvのチェックをしないように修正
	   既に判定はguild.cで行われているのでパケットの内容を信頼する
	-> SQL: guild_sql_load_num() で利用しない `guild_id` をSELECTしないように修正

・ギルド情報取得時に発生させるイベント名の末尾に \0 を強制するように修正（guild.c）
・guild_member_added() でメンバーの追加に失敗したとき、末尾に \0 を強制するために
　msg_txt() を一旦バッファにコピーしてから intif_guild_leave() を呼ぶように修正（guild.c）

----------------------------------------
//0226 [2007/07/14] by Rayce

・キャラ永続変数およびアカウント永続変数が31文字で制限されるように修正、0225の続き
　（inter.c, chrif.c, intif.c, pc.c）
・inter.*の細かい整形

・map_auriga.confのuserid, passwdを24→ 23文字に制限（chrif.c）
・wisの拒否リストに保存するキャラ名の末尾に \0 を強制するように修正（clif.c）

----------------------------------------
//0225 [2007/07/14] by Rayce

・char.cの細かい整形
・バッファオーバーフロー対策のため一部の文字列の末尾に '\0' を強制するように修正（char.c）
	キャラ名 24 → 23文字まで
	永続変数 32 → 31文字まで
	char_auriga.confのuserid 24 → 23文字まで
	char_auriga.confのpasswd 24 → 23文字まで

　※0200から少しずつ対策を施してきましたが、ここからはセーブデータに関与する部分について修正を行います。
　　利用可能な文字数が規定よりも1つ減らされます。
　　今まで長い文字列が使われていた場合は注意してください。
　　最大文字数を越えるものは自動的に安全な文字数まで切り詰められるので、キャラ名が変わってしまったり
　　セーブデータ自体が壊れてしまう可能性があります。
　　セーブデータのバックアップを取った上で十分検討してください。

----------------------------------------
//0224 [2007/07/14] by Rayce

・ROメールの削除を失敗したとき「削除できませんでした」のメッセージが出力されないバグを修正（clif.c, intif.c）

・int_mail.cの全体的な修正と整形
　　-> 送信者名、受信者名、タイトルの末尾に \0 を強制する
　　-> mail_dataのアイテムソート用idがunsigned intになってなかったのを修正、%d → %u
　　-> mapif_parse_OpenMailBox() でメールがロードできなかったときは念のためmail_dataを
　　　 NULLで埋め尽くすようにしておく
　　-> TXT: mail_data用のfilenameがバッファオーバランしないようにサイズを変更、1024 → 1056
　　-> TXT: mail_dataを保存する際は lock_fopen(), lock_fclose() を利用する
　　-> SQL: mail_sql_store_mail() でbody_dataにわざわざデータを変換する無駄を省略
　　-> SQL: mail_sql_load() で必要のない `char_id` をSELECTしないように改善

----------------------------------------
//0223 [2007/07/14] by Rayce

・pet_delete() を呼び出すとき、card[1]ではなくcard[2]を参照していたためにペットデータが削除されなかった
　バグを修正（char.c, int_storage.c）

・キャラクターを削除するとき、ROメールに添付されたペットの卵情報が削除されずセーブデータにゴミが残り
　続ける問題を修正（int_mail.c）
・アイテムやZenyが添付されたままのROメールを削除できないように修正（int_mail.c）
	通常はクライアント側で判定が行われ、以下のメッセージが出力されるだけで0x254のパケットは送信されません。
	「削除しようとしているメールに受け取っていないアイテムが存在します。」
	しかしhacker対策としてinterサーバでも添付アイテムの存在をチェックするように強化します。

・TXT: mail_txt_deletemail() のmemcpy部分を少し改善（int_mail.c）

----------------------------------------
//0222 [2007/07/13] by Rayce

・clif.cの細かい整形
	-> clif_parse_ChangeDir() のセキュリティ対策
	-> clif_parse_HomActionRequest() から2005-05-09dRagexeに対するデコード処理部分を抹消
	-> webchat_message() のsprintfをsnprintfに修正
・動作に影響しないレベルの細かい整形（src/common, src/map）

----------------------------------------
//0221 [2007/07/13] by Rayce

・path.cから経路探索ルーチン単体テスト関数を抹消（path.c）
・intif.cの細かい整形
	-> intif_GMmessage() を少し変更
	-> intif_parse_GuildMemberInfoChanged() から不要な代入を削除
・guild.cの細かい整形
	-> db/castle_db.txtで指定できるMap_Name, Castle_Name, Event_Nameを23文字までに制限
	-> guild_broken() でメモリをアロケートしなくて済むように改善

----------------------------------------
//0220 [2007/07/12] by Rayce

・バッファオーバーラン対策として文字列の末尾に \0 を強制するように修正（core.c, httpd.c, socket.c）
・windows環境で吐き出されるcrashdump.logの改行コードをCR/LFに修正（core.c）
・httpd.cの細かい整形
	-> httpd_strcasencmp() の代わりにstrcasecmpを使う
	-> httpd_pages() 用の関数ポインタを HttpdFunc型 としてtypedefする
	-> rand() を atn_rand() に変更

----------------------------------------
//0219 [2007/07/12] by Rayce

・ROメールにアイテムやZenyを添付するとき、idxが不正な値の場合は弾くようにチェック強化（mail.c）
・mail_checkappend() をstaticに変更（mail.*）
・clif_parse_GuildRequestInfo() で先にtypeの不正チェックを行うように修正（clif.c）

・SC_INCMSP2によるMAXSP増加の計算タイミングを少し変更（status.c）
・status.cの動作に影響しないレベルの細かい整形

----------------------------------------
//0218 [2007/07/11] by Rayce

・0202におけるgetpetinfo関数およびgethomuninfo関数の変更点を巻き戻し
　これまでの修正によりペットとホムの名前には \0 が入ることが保証されたのでaStrdupを使う（script.c）
・setmapflag命令でnosaveを指定する際、MAP名を15文字までに制限（script.c）

・map_session_data構造体のメンバwarp_waitingをビットフィールドに変更（map.h, skill.c, unit.c）
・ranking.c, unit.cの細かい整形

----------------------------------------
//0217 [2007/07/11] by Rayce

・ペットの名前を23文字までに制限（pet.c）
・動作に影響しないレベルの細かい整形（chat.c, mob.c, party.c, pet.*）

----------------------------------------
//0216 [2007/07/11] by Rayce

・battle_auriga.confのpet_loot_typeが0のとき、ペットが過剰にアイテムをルートする際に
　重量が変化しなかったバグを修正（pet.c）
・倉庫を開いているときだけ以下のタイミングで storage_storage_save() を呼び出すように修正（clif.c, homun.c, pet.c）
	ホムの削除時
	ペットの卵の孵化時
	ペットを卵に戻す時
	battle_auriga.confのpet_leaveがyesのときでペットが親密度0で消える時
	battle_auriga.confのsave_player_when_drop_itemがyesのときでアイテムを床に落とした時

・mapif_create_pet() でペットの新規作成に失敗した場合にはfreeするように修正（int_pet.c）
・GCCにおいて map_getcellp() で警告が出ていたので修正（map.c）

----------------------------------------
//0215 [2007/07/10] by Rayce

・アクセス違反が発生する可能性を修正
	-> pet_select_egg() で不正なindexが送信されてくるのを防ぐ（pet.c）
	-> guild_created() でエンペリウムが見つからないときのチェックを考慮する（guild.c）
	-> db/skill_db.txtのinf2に8192のフラグがセットされているスキルについて、
	   スキルLvが11以上の場合にはスキルLv10と同じ消費アイテムチェック処理にする（skill.c）

・homun_callhom() でエンブリオを検索する際に pc_search_inventory() を使うように修正（homun.c）
・removecards_sub() の > を >= に修正（script.c）
・skill_weapon_refine() で pc_search_inventory() を二重に呼ばないように改善（skill.c）
・battle_skill_attack() のカイトの部分で「水晶のかけら」を検索する際、不必要な個数チェックを省略（battle.c）
・ポーションピッチャーおよびスリムポーションピッチャーをスキルLv11以上で使う場合、
　スキルLv10と同じアイテムを使用するように変更（skill.c）

・csv_data構造体へのキャストを明示してなかった箇所を修正（script.c）
・script.cの細かい整形

----------------------------------------
//0214 [2007/07/10] by Rayce

・ユーザー定義関数として使える関数名を49文字までに制限（npc.c）
・npc_parse_script(), npc_parse_function() を少しだけ改善（npc.c）
・skill.cで使う WARP_CLASS はnpc.hから取得するように変更（skill.c）
・npc.cの細かい整形

----------------------------------------
//0213 [2007/07/09] by Rayce

・mob.cの細かい整形（mob.*）
	-> イベントを持っているMobを倒したときバッファアンダーフローが起こる可能性を修正
	-> mob_ai_sub_hard() で攻撃されたかの確認を行う際、チェックが二重に行われる無駄を修正
	-> db/mob_db.txtで指定可能なモンスター名の文字数を23文字までに制限する
	-> db/mob_skill_db.txtにMOB_ID_MAXを越える値をIDとして指定した場合にサーバクラッシュするバグを修正
	-> db/mob_skill_db.txtにMAX_MOBSKILLを越える数のスキルを登録しても「readdb: too many skill」の警告が
	   出力されなかったバグを修正

----------------------------------------
//0212 [2007/07/08] by Rayce

・mail.cの細かい整形（mail.c）
	-> nullpoチェックを入れる
	-> ROメールの受信者およびタイトルの末尾に \0 を付加する

・map.cの細かい整形（map.c）
	-> block_free_max を BLOCK_FREE_MAX に改名
	-> BL_LIST_MAX はblock_list構造体用のtypeと混同するので BLOCK_LIST_MAX に改名
	-> map_calc_dir() の最適化
	-> MAP名の末尾に \0 を付加する

・sleep_data構造体を無名構造体に変更（script.h）
・以下の入れ子になった構造体を外に分離する（db.h, map.c, map.h, script.h）
	db_free
	map_cache_head
	pet_skill_attack
	pet_skill_support
	script_stack

----------------------------------------
//0211 [2007/07/08] by Rayce

・ランダム系アイテムデータベースを読み込む際、存在しないアイテムのIDが指定されていた場合は
　読み込み対象外にするように修正（itemdb.c）
・db/item_db.txtで指定可能なアイテムの日本語名および英語名を47文字までに拡張（itemdb.c）
	現時点で idnum2itemdisplaynametable.txt に記載されている最長のアイテム名が37文字でした。
	これらをカバーするため文字数制限を32文字から47文字に引き上げます。
	バッファオーバーラン対策により末尾には \0 を強要するため、48文字ではなく47文字です。
・@idsearchの処理を最適化（atcommand.c, itemdb.*）
	itemdb_idsearch() を追加。
	numdb_foreach() を使うので効率良く検索が行われます。
	itemdb.cにあった変数 max_itemid および itemdb_getmaxid() は不要になったので削除。
・@idsearchでスロット数を表示するように機能拡張（atcommand.c, msg_auriga.conf）
・itemdb.cの細かい整形

----------------------------------------
//0210 [2007/07/07] by Rayce

・lock.cでバッファオーバーランが発生する可能性を修正（lock.c）
・0208においてatcommand.cで警告が出ていたので修正
	-> 抜け落ちていたreturnを補完（atcommand.c）
	-> pc_setpos() の引数にconstを付ける（pc.*）

----------------------------------------
//0209 [2007/07/07] by Rayce

・ホムが消えるとき、泣きエモタイマーが即座に削除されないバグを修正（unit.c）
・HPが0のホムを召喚してしまった場合は unit_free() で削除するように修正（homun.c）
・homun_get_create_homunid() を簡素化（homun.c）
・ホムの名前を23文字に制限する（homun.c）
	バッファオーバーラン対策のため、db/homun_db.txtおよびリネーム時で使える文字数が
	24 → 23に変更されます
・動作に影響しないレベルの細かい整形（homun.*）

----------------------------------------
//0208 [2007/07/06] by Rayce

・battle_addmastery() でデーモンベインのダメージ加算計算に浮動小数演算を使わないように変更（battle.c）
・atcommand.cの全体的な整形
	不要なmemsetを撤廃
	@iconの第二引数省略時はONになるように拡張

----------------------------------------
//0207 [2007/07/06] by Rayce

・ペットの卵を倉庫に入れたとき装備品目に置かれなかった問題を修正（clif.c）
・unit_walktodir() を pc_runtodir() と同様に修正（unit.c）
・取引時の距離チェックは unit_distance2() を利用するように変更（trade.c）

・skill.cの全体的な細かい整形
・skill_check_condition2_pc() の「ソウルリンカーで使えないスキル」の部分をまとめ直し（skill.c）
	battle_config.soul_linker_battle_modeの使い方がおかしかったので修正
	battle_config.soul_linker_battle_mode_kaが何故か使われてなかったので修正

----------------------------------------
//0206 [2007/07/06] by Rayce

・サーバースナップショット（version.h）
・不要なファイルをフォルダごと削除
	./bin
	./script/mob

----------------------------------------
//0205 [2007/07/06] by Rayce

・bin内のtoolフォルダをトップに移動してbinフォルダを削除する
	gccでMakefileを用いてコンパイルしたとき、生成されるexeファイルはbinではなく
	Aurigaのトップディレクトリに置かれるように変更されます。
	BCC, VCと同様の扱いになります。

----------------------------------------
//0204 [2007/07/05] by Rayce

・dbファイル群の更新 from huge cgi, thanks
・存在しないmapflag pvp_nopenaltyが混入していたので再度削除
・以下のスクリプトでエラーが発生していたので修正
	npc/misc/npc_misc_zonda.txt
	npc/quest/npc_quest_juperos.txt
	npc/quest/npc_quest_kiel.txt
	npc/quest/npc_quest_turbo.txt
	npc/town/amatsu.txt
	sample/npc_test_ev.txt

----------------------------------------
//0203 [2007/07/05] by Rayce

・@autoloot時にアイテムと同じMAPに居ない場合は取得できないように修正（mob.c）
・@autolootで取得したアイテムもPT分配の対象になるように修正（mob.c）
・グリードで取得したアイテムもPT分配の対象になるように修正（pc.*, skill.c）
　pc_takeitem() から処理本体を pc_takeitem_sub() として切り離してグリードと共通化

・conf/inter_auriga.confの guild_join_limit をデフォルトで「加入可能」の0に変更（int_guild.c）
・040以降、@recallでサーバクラッシュしていたバグを修正（inter.c, intif.c）

----------------------------------------
//0202 [2007/07/02] by Rayce

・getwaitingroomstate関数、getpetinfo関数、gethomuninfo関数から正しく文字列を取得できるように
　一部のaStrdupを使わないように修正（script.c）
・スクリプトで使えるOn系ラベルの最大文字数を24文字から23文字に縮小（npc.c, script.c）
	ev_dbは48文字でstrncmpするため合成されるイベント名は48文字以内に収まる必要があるためです。
	　(NPC識別子) + "::" + (Onラベル) = 23 + 2 + 23 = 48文字

・イベント型NPCスクリプトの名前が A::B::C のようになっているとサーバクラッシュするバグを修正（npc.c）
	今までは B::C が識別子になっていたため、ev_db_final() 内でaStrdupされてない名前をfreeしていました。
	今後は B が識別子になります。
	2回目以降に "::" が出現した場合はそれ以降の文字列は捨てられます。

・malloc.hから不要なincludeを外す（malloc.h, httpd.c, graph.c）
・malloc.cの整理

----------------------------------------
//0201 [2007/06/30] by Rayce

・コメントアウトしてあったBL_VALIDATEをコードから抹消（map.*）
・dspにデフォルトで /wd4819 を付ける

・MEMWATCHがオンの場合に、サーバを停止するときsocket.cがunfreedとして誤認される問題を修正（malloc.c）
・MEMWATCHがオンの場合はUSE_MEMMGR無しとして自動的に定義されるように修正（malloc.c）
	MEMWATCHを使うときはUSE_MEMMGRによるメモリマネージャは使えません。
	アライメントが異なるためサーバクラッシュを引き起こします。

・SQL: 0200のtypo修正、stncpy → strncpy（login.c）

----------------------------------------
//0200 [2007/06/29] by Rayce

・バッファオーバーランが起こる可能性があるので一部のmemcpyをstrncpyに修正
・sscanf時にバッファサイズを超えないように修正
・NPC名が24文字以上に長すぎた場合、strnpcinfo関数等で正しく文字列を取得できなかったバグを修正（npc.c）
・battle.cとpc.cの整形のやり残し

----------------------------------------
//0199 [2007/06/28] by Rayce

・party_foreachsamemap() の引数のtypeをrangeに変更して範囲を指定するように変更（skill.c, pc.c, party.c）
・ギルドスキルの有効チェックの一部を pc_check_guild_skill_effective_range_sub() としてまとめる（pc.c）
・pc_steal_item() と pc_steal_coin() の引数を変更（pc.*, skill.c）
・pc.cの全体的な整形（pc.c）

----------------------------------------
//0198 [2007/06/27] by Rayce

・gccで0197がコンパイルエラーになっていたので修正（battle.h）
・スクリプトにgetargcount関数追加（script.c）
	callfuncまたはcallsub内で呼び出し時の引数の個数を取得することができます

・アイテムボーナスオートスペルのEAS_LONGが正常に機能していなかったバグを修正（skill.c）
・autospell構造体のメンバflagをunsinged long型に変更した際の修正漏れを補完（pc.*, script.c, skill.c）
・コメント修正、所得 → 取得

----------------------------------------
//0197 [2007/06/27] by Rayce

・autospell構造体のメンバflagをlong型からunsigned long型に変更（battle.c, map.h, skill.*）
・map_session_data構造体の中で使用されていない以下のメンバを削除（map.h, status.c）
	autospell_id, autospell_lv, autospell_rate, autospell_flag

・battle_delay_damage_sub() が多重に add_timer_func_list() されないように
　do_init_battle(), do_final_battle() を追加（battle.*, map.c）
・battle.cの全体的な整形（battle.c）
・skill_get_inf() の返り値はビット演算で利用するように統一（battle.c, clif.c, skill.c, status.c, unit.c）

----------------------------------------
//0196 [2007/06/23] by Rayce

・battle_auriga.confの hallucianation_off がyesの時はエフェクトのみを無効化するように修正（skill.c, status.c）
	ダメージ表示の数値がばらつく効果だけは有効化されるようになります。
	/effect でエフェクトをオフにしているのと同じ状態になります。

・一部の距離計算で unit_distance() を使うように（battle.c, mob.c）
・clif_GMmessage() を少し改善（clif.c）
・pc_insert_card() を少し修正（pc.c）

----------------------------------------
//0195 [2007/06/11] by Rayce

・/pvpinfoに対するパケット処理追加 from eApp（clif.c）
　ただしPKポイントを表示するだけで、勝敗の部分は0で埋めています
・PC型MobおよびPetがアイテムをルートするとき、拾いモーションが出るように（mob.c, pet.c）
・DEBUG_RUNでスタックをダンプする際、RETINFOも識別するように修正（script.c）
・doc/client_packet.txt更新

----------------------------------------
//0194 [2007/06/06] by Rayce

・getmapxy関数の引数として渡す変数は数値型/文字列型どちらでも扱えるように修正
・「stack.sp(?) != default(?)」のエラー文が出力されるときに発生するメモリリークを修正
・script.cの細かい整形

----------------------------------------
//0193 [2007/06/01] by Rayce

・atcommand.cの細かい整形
・@changemaptype追加、/changemaptypeを有効化（atcommand.*, clif.c）
	/changemaptypeはクライアントの仕様によりセルタイプ0（移動可能）か1（壁）しか選べません。
	3（水場）や5（遠距離攻撃可能な壁）を設定したい場合は@changemaptypeを使ってください。
	またgatファイルでは壁として定義されているセルを移動可能セルに変更する場合、効果があるのは
	コマンド実行時に同一MAP内に居たプレイヤーのみです。
	セル変更パケット0x192を受け取っていないプレイヤーは依然壁として認識したままとなります。

----------------------------------------
//0192 [2007/05/29] by Rayce

・AthenaProject2301, 2302よりmerge、thanks to ルキさん、orz~さん
	-> mapflagにnocommandを追加（atcommand.c, map.h, npc.c, script.c）
	-> アシッドデモンストレーションがディフェンダーを貫通するように修正（battle.c）
	-> プレッシャーがダメージ1固定属性にも貫通していたのを修正（battle.c）
	-> アルケミストの魂状態でポーションピッチャーの効果が上がるよう修正（skill.c）
	-> 合奏開始判定から混乱状態不可削除（skill.c）

・gmcommand命令で使うダミーsdのfdを0に戻す（script.c）

----------------------------------------
//0191 [2007/05/28] by Rayce

・AthenaProject2300を参考に以下を修正、thanks to orz~さん
	-> MOBの攻撃対象がHOMの場合、HOMをターゲットした場合も動くように（mob.c）
	   判定部分を mob_can_lock() としてまとめる
	-> 合奏スキル発動時に相方が状態異常にかかっている場合は失敗するように修正（skill.c）
	-> 武器を外したときと沈黙時に演奏/ダンスが解除されるように修正（pc.c, status.c）

----------------------------------------
//0190 [2007/05/27] by Rayce

・0189でskill.cがコンパイルエラーになっていたので修正（skill.c）
・buildin_delinventory() を少しだけ最適化（script.c）

・AthenaProject2300より一部をmerge、thanks to orz~さん
	-> skill.cの丸付き数字を修正
	-> グランドクロスが物理DEF無視になっていたので修正（battle.c）
	-> カートターミネーションがオートガード、パリイング、リフレクトシールドを
	   貫通するように修正（battle.c）
	-> エスマを武器属性が乗らないように変更（battle.c, status.*）
	-> カートターミネーション、アシッドデモンストレーションに状態異常カードが
	   乗らないように修正（map/skill.c）
	-> メモライズ対象外スキルに激励と治療を追加（unit.c）

----------------------------------------
//0189 [2007/05/26] by Rayce

・AthenaProject2298より一部をmerge、thanks to Cocoaさん
	フリップザコインの成功率が異なっていた点を修正（skill.c）

・AthenaProject2299よりmerge、thanks to Blazeさん
	-> 取り巻きモンスターの挙動を修正（mob.c）
	-> NPCスキル「取り巻き呼び戻し」の範囲を修正（mob.c）
	-> NPCスキル「メタモルフォース」「トランスフォーメーション」のLv2以上実装（skill.c）

----------------------------------------
//0188 [2007/05/26] by Rayce

・AthenaProject2297よりmerge、thanks to Blazeさん
　　・monsterフォルダを細分化
　　　フィゲルまでの最新データ+ラヘル追加マップのデータ更新（script/monster）
　　・ニブルヘイム、生体工学研究所のMVPボススクリプトを本鯖仕様化
　　　（npc_monster_niflheim.txt、npc_monster_lhzdun.txt）
　　・warpにキル・ハイルクエスト関係などを追加（script/warp）
　　・mapflag細分化（script/mapflag）
　　　mapflag更新
　　・map_auriga.conf更新（conf/map_auriga.conf）
　　・キル・ハイルクエスト実装（npc_quest_kiel.txt）
　　・ターボトラック実装（npc_quest_turbo.txt）
　　・ジュピロス保安区域実装（npc_quest_juperos.txt）
　　・商圏投票実装（npc_misc_zonda.txt）
　　・アリーナPTモード実装（npc_quest_arena.txt）
　　　個人戦のモンスター位置や挙動を本鯖仕様化
　　・飛行船スクリプトが巻き戻っていたのを修正（npc_town_airport.txt）
　　　襲撃イベントの挙動・確率などを本鯖仕様化
　　　ミニゲームのタイピングを本鯖仕様化
　　・アインブロック工場クエスト修正
　　　汚染イベントの発生条件、モンスター発生箇所を本鯖仕様化（npc_town_einbroch.txt）
　　・リヒタルゼン、治安維持イベントのバグを修正、本鯖仕様化（npc_town_lighthalzen.txt）
　　・ウンバラ夫婦喧嘩クエスト実装（npc_town_umbala.txt）
　　　シャーマンがクエスト未進行でも進行される問題を修正
　　　バンジージャンプの各種確率、骸骨門に入れる確率、属性石の個数確率などを本鯖仕様化
　　・アマツ刺身包丁クエスト実装（npc_town_amatsu.txt）
　　　通行手形クエストを本鯖仕様化
　　・コンロンクエストを修正（npc_town_gonryun.txt）
　　　闘技場を本鯖仕様化
　　・龍之城クエスト修正（npc_town_louyang.txt）
　　　展望台修正
　　・コモドの一部NPCの挙動を修正（npc_town_comodo.txt）
　　・初心者修練場、レベルに関係なく経験値を得られてしまうのを修正（npc_job_00novice.txt）
　　　職業適性審査の判断箇所を本鯖仕様化
　　・忍者の手甲作成クエスト実装（npc_job_29ninja.txt）
　　・ほとんどのクエストで得られる報酬経験値を本鯖仕様化

----------------------------------------
//0187 [2007/05/26] by Rayce

・set_reg(), script_read_vars(), script_write_vars() の引数にconstを付けるように修正（script.*）
・delitem命令、delinventory命令に可変引数を追加
	ペットの卵の情報の削除をinterサーバに要請したくないときはフラグを入れます
・getinventorylist命令から取得できる情報に @inventorylist_index を追加
	インベントリのインデックスを正しく取得することができます
	今まではこれがなかったためdelinventory命令が正常に利用できない問題があったため

----------------------------------------
//0186 [2007/05/21] by Rayce

・同一MAPを複数のMAPサーバで読み込ませた場合に発生するメモリリークを修正（map.c）
	読み込んでいたが担当外になったMAPも map_eraseallipport_sub() で削除処理します。

・db_insert() 実行時にdb.cのメモリプールが満杯になったらサーバを落とすように修正（db.c）
	今まではdbnが512×4096個以上になったらバッファオーバーフローになっていました。
	配列のサイズを ROOT_BUCKET として定義して、満杯になった時点で
	「malloc_dbn: dbn memory over ??? !!」の警告を出すようにします。
	dbnが確保できないのは問題があるのでサーバを落とすようにしています。
	もしこの警告が出るほど大量にdbnが必要な場合は ROOT_BUCKET の値を上げてみてください。

・intif.cの細かい整形
・save/auriga.txtのデータコンバート処理を改善（char-converter.c）
	char_namedbをわざわざ用意する必要はないので削除
	バイナリサーチを使って友達リストの名前を補完します

----------------------------------------
//0185 [2007/05/20] by Rayce

・タイリギ移動中に敵を通常攻撃すると止まってしまう問題を解消するため、
　タイリギ移動中は通常攻撃不可に暫定的に変更（clif.c）
・タイリギ移動中はアイテムを拾えないようにanti hacker強化（clif.c）

・addtick_timer() をint型からunsigned int型に修正（timer.*）
・add_timer_sub() を add_timer_real() に改名（timer.*）
・status.c, unit.cの細かい整形

----------------------------------------
//0184 [2007/05/20] by Rayce

・@homlvでホムのLvが最大のときはステータスの再計算やエフェクトの表示をしないように修正（atcommand.c）
・バイオエクスプロージョンの範囲を5x5から11x11に修正（skill.c）
・バイオエクスプロージョンを使ってもダメージが発生しないバグを修正（battle.c, skill.c）
	BF_WEAPONだとbattle_delay_damage_sub() の時点で発動元のホムは消滅しているので
	その後のダメージ処理が行われない状況でした。
	武器スキルである必要はないのでBF_MISCに変更しています。

----------------------------------------
//0183 [2007/05/19] by Rayce

・0175で追加した myhpgtmaxrate, friendhpgtmaxrate が読み込めなかった問題を修正（mob.c）
・status_pretimer() でデータの整合性チェックを強化（status.c）
・pk_murderer_pointの設定が経験値取得と売り値補正に反映されてなかった問題を修正（pc.c）
・battle_calc_damage() を少し修正（battle.c）

・ハンマーフォールを素手では使用不可に修正（db/skill_require_db.txt）
・zlibにあるMakefileの改行コードをCR/LFに変更

---------------------------------------
//0182 [2007/05/11] by Rayce

・取得可能なギルドスキルの最大Lvをdb/skill_db.txtではなく、db/guild_skill_tree.txtの
　MaxLv設定に従うように変更（int_guild.c, map.c, guild.*）
	ギルドスキルツリーの設定をdb/guild_skill_tree.txtに一括します。
	ただしdb/skill_db.txtで設定したMaxLvを越えることはありません。
	また、行をコメントアウトするかMaxLvの値を0にすると取得不可スキルになります。

	-> guild_get_skilltree_max() 追加
	-> guild_check_skill_require() でスキルツリーのidとmaxをチェック
	-> guild_skillup() でスキルツリーを違反してスキルを振れないように不正チェック
	-> guild_read_guildskill_tree_db() で最大Lvをチェック
	-> guild_calcinfo() 修正

・clif_parse_GuildRequestInfo() が不必要に呼ばれないように改善（clif.c, map.h, guild.c）
	この関数はギルドウィンドのタブを切り替える度に呼ばれるので、その都度
	クライアントにパケットを送信していました。
	しかしギルド情報が変更されてないのに更新する必要はありません。
	MAPをロードしても一度受け取った情報は消えないようなので、各項目に
	ついて初回だけ呼び出せば良いことになります。

	-> map_session_data構造体のstateに guild_req_info メンバ追加
	-> clif_parse_GuildRequestInfo() で2回目以降の項目はブロックする
	-> ギルド作成時とギルド加入時に guild_req_info を0に初期化する

----------------------------------------
//0181 [2007/05/11] by Rayce

・AthenaProjectのBTS報告分について修正、thanks to TAKUROさん
	-> MOBにルートされた2個以上のアイテムが床にドロップされると
	   1個に変わってしまうバグを修正（mob.c）
	-> 非PTとガンスリンガーには気功転移を発動できないように修正（skill.c）
	-> マスターでないギルドメンバーがギルドスキル一覧を見るとき
	   未修得のものがグレーで表示されるように修正（clif.c）
	-> ストリップウェポン、速度減少、リバースオーキッシュがリログで
	   治るように修正（db/scdata_db.txt）

----------------------------------------
//0180 [2007/05/10] by Rayce

・NPCファイルの読み込みに使うファイル名のリストを双方向リストに変更して処理を単純化（npc.*）
・exit(1) で強制的にサーバ終了するときにメモリリークが発生するときがあるので修正（map.c, npc.c）
	do_final() 以下に続く処理で、水場リスト（waterlist）と
	NPCファイル名リスト（npc_src_list）がまだ残っていれば解放します

----------------------------------------
//0179 [2007/05/10] by Rayce

・エンペリウムに対して運命のタロットカードが発動しないように修正（skill.c）
・ディボーションの使用条件の一部を以下のように修正（skill.c）
	-> 自分および相手がPT未所属だと失敗
	-> 所属PTが異なる場合は失敗
	-> ギルドの所属は問わない

・倉庫に関する修正（intif.c, storage.*）
	-> 最初に開いたときにアイテムを出し入れすると正常にソートされないバグを修正
	-> interサーバからデータ受信したときの処理を修正
	-> ロスト対策として account2storage() および guild2storage() の利用はデータ受信時のみにする

----------------------------------------
//0178 [2007/05/10] by Rayce

・コンパイルオプションの AC_MAIL をSQLモードでも利用可能に拡張（login.c, char.c）
	処理を集約するために、AC_MAILが無効になっている場合でも必ずloginサーバに
	データを送信するように変更しています

・0176でgccのときにコンパイルエラーになっていたのを修正（mob.h）
・SQL: 0177のコンパイルエラーおよびwarning修正（int_guild.c）

----------------------------------------
//0177 [2007/05/10] by Rayce

・int_guild.cとguild.cを全体的に整形
・ギルド城データベース castle_db をツリーDBから配列に単純化（int_guild.c, guild.c）
・エンブレム変更処理部分をclif.cからguild.cに移動（clif.c, guild.*）

・0115以降、以下のスクリプト命令/関数において、assignされてないMAP名を入れたときに処理が
　実行されなくなっていたバグを修正（script.c）
	getcastlename
	getcastledata
	setcastledata

・guild構造体から使われてないメンバ castle_id を削除（mmo.h, int_guild.c, char-converter.c）
	セーブデータの形式が変更されているのでご注意を

・TXT: JOURNAL_IDENTIFIERをバージョン04に変更しておく（journal.c）
・SQL: main.sql修正、Auriga-0177_changetable.sql添付

----------------------------------------
//0176 [2007/05/09] by Rayce

・mob.cの全体的な整形
・以下の関数の処理を少し改善（mob.c）
	mob_can_reach()
	mobskill_anothertarget()
	mobskill_use()

・0175に引き続き一部の関数および引数にconstを付ける
・0150以降、ギルド城にカプラとガーディアンが設置できなくなっていた問題を修正
　（script/npc/gvg/npc_gvg_steward.txt）

----------------------------------------
//0175 [2007/05/08] by Rayce

・AthenaProject2296を参考に以下を実装、thanks to Sheepさん
	Mobスキルの使用条件に myhpgtmaxrate, friendhpgtmaxrate を追加（mob.c）

・Mobが反撃可能かどうかを判定を行う際、ダメージディレイが消える場合があったので修正（mob.c）
・Mobのスキル使用条件の一部でホムがターゲットとして認識されてなかったので修正（mob.c）
・mob_can_counterattack() の引数を増やしてターゲットを二重に検索しないように改善（mob.c）

・一部の関数および引数にconstを付ける
・skill_timerskill構造体をmap.hからskill.hへ移動
・status_pretimer構造体をmap.hからstatus.hへ移動
・skill.cとstatus.cを少し整理

----------------------------------------
//0174 [2007/04/29] by Rayce

・AthenaProject2295よりmerge、thanks to Blazeさん
　以下Readmeより転載
　　・スクリプトに指定場所にアイテムをドロップするdropitem命令を追加（script.c）
　　・スクリプトに経験値を取得するgetexp命令を追加（script.c）
　　・カードの出血耐性の効果が反映されなかったのを修正（status.c）
　　・ガトリングフィーバー状態の攻撃力・移動速度・Flee値を修正（status.c）
　　・空蝉の回避方向を相手の位置関係から見て後方になるように修正（battle.c）
　　・命令追加による各種スクリプトの修正
	（npc_job_00novice.txt）
	（npc_quest_arena.txt）
	（npc_town_airport.txt）
	（npc_town_ayothaya.txt）
	（npc_town_einbroch.txt）
	（npc_town_hugel.txt）
	（npc_town_lighthalzen.txt）
	（npc_town_louyang.txt）
　　・初心者修練場の職業適性審査修正
	（npc_job_00novice.txt）
　　・ニブルヘイムのロードオブデスを修正
	（npc_town_niflheim.txt）

　　※dropitemの仕様はAthenaProjectをベースに改変しているので注意

----------------------------------------
//0173 [2007/04/27] by Rayce

・PC型Mob/Petに関する処理方法の見直し（clif.c, mob.*, skill.c, status.c, unit.c）
	mob_db構造体のメンバ view_class には pc_calc_class_job() の計算結果を保存しておきます。
	transが不要になるので削除し、代わりに pcview_flag を追加しています。
	view_class の値を使ってPC型であるかどうかを判定することもできますが、煩雑になるので
	実行速度を重視してフラグをstaticに保存しておくようにしました。
	今後は mob_is_pcview() を使って判定してください。

・見かけ取得系の関数 mob_get_* はあまり意味がないので全てマクロに書き換え
・typo修正、buttom → bottom

----------------------------------------
//0172 [2007/04/27] by Rayce

・取得可能なスキルの最大Lvをdb/skill_db.txtではなく、db/skill_tree.txtおよびdb/homun_skill_tree.txtの
　MaxLv設定に従うように拡張
	各職業ごとにスキルの最大Lvを変更できるようになります。
	例えばMagicianはファイヤーウォールをLv5までしか覚えられないが、WizardはLv10まで取得可能など。
	ただしdb/skill_db.txtで設定したMaxLvを越えることはありません。

	-> pc_get_skilltree_max() 追加
	-> homun_get_skilltree_max() 追加
	-> do_init() で do_init_skill() を do_init_pc() よりも優先して実行するように変更
	-> skill_db.txtの読み込み時にMAX_SKILL_LEVELを越えてないかチェックするように強化

　　※ただし @allskill は例外です。
　　　プレイヤーがGMでbattle_auriga.confのgm_allskillが設定されている場合は、skill_tree.txtのMaxLvではなく
　　　skill_db.txtのMaxLvまでスキルを取得します。

・養子職のスキルツリーを独自に設定できるように拡張
	今までは養子のスキルツリーは通常職と同じものを使っており、db/skill_tree.txtのUpperを2にしても
	全く反映されていませんでした。
	battle_auriga.confに追加されたbaby_copy_skilltreeをnoにすると、養子職専用のスキルツリーを作る
	ことができるようになります。

　　※noにした場合はskill_tree.txtに養子用のツリーを追加してください。
　　　デフォルトのままだと一切のスキルが取得ができない状態になります。

・db/skill_tree.txtおよびdb/homun_skill_tree.txtで、同一のスキルIDがある場合は下に書いたもので上書き
　されるように修正
・skill_use_bonus_autospell() の処理を少し最適化
・homun.cおよびhomun.hの整理
・db/skill_tree.txtのMaxLvの値が間違っていた部分を修正
・doc/db_refにスキルツリーに関する説明を追加

----------------------------------------
//0171 [2007/04/25] by Rayce

・試験的に、攻撃開始時に歩行停止を実行するとき座標補正パケットを送信しないようにしてみる（clif.c）
	shift押しで他PCをクリックしたとき、目的地に到着する直前で後方に引き戻されるのを解消するための処置です。
	並んでいるPCに対してshiftクリックすることでPCに重なることができるようになります。
	動きが幾分滑らかになってるはずですが、座標補正しないので見かけ上位置ズレする問題があります。
	これは結果的にAthena mod1468で行われた修正の一部を巻き戻すことになっています。

　　※shiftクリックで移動させる場合、まず clif_parse_Walktoxy() が呼ばれて移動開始します。
　　　クライアント側が目的地の半歩手前に到着した時に clif_parse_ActionRequest() のパケットが飛んできます。
　　　この時点ではまだサーバ側は目的地の１歩手前なので、座標補正すると引き戻されるようです。
　　　クライアントとサーバの擦り合わせがまだまだ不十分なのでこれで当面は保留。

・Mobのワープやスキルユニットの移動において、ブロックを変更する必要がない場合は
　map_delblock(), map_addblock() を実行しないように最適化（map.h, mob.c, skill.c）
	マクロ map_block_is_differ() 追加

・Mobの移動途中において、一歩先にバジリカのセルが設置されているかどうかの判定は
　恐らく不要なので削除してみる（unit.c）
・Auriga0170で添付し忘れた doc/client_packet.txt を同梱

----------------------------------------
//0170 [2007/04/25] by Rayce

・聖体降福に関する修正（skill.c）
	-> 発動条件がアコ系キャラが「周囲1セル内に2人居たら」になっていたので、「X軸方向の両隣に2人居たら」
	   に修正、片側に重なっていても可とする
	-> skill_check_condition_use_sub() でモンクがアコ系に含まれていなかったのを修正
	-> mapforeachinareaの実行は対象となる2人が確定した時点で検索打ち切りにする
	-> アコ系キャラが3人以上居た場合、全員がSPを消費してしまうのを修正
	-> 補助者のSP消費が遅延する問題を修正
	-> 補助者の消費SPは10固定ではなく、術者のSPの半分になるように拡張

・バード/ダンサーの合奏スキルに関する修正（skill.c）
	-> 自分と相方が共にPT未所属でも合奏が発動した問題を修正
	-> 相方が楽器もしくは鞭を装備してないと発動しないように修正
	-> 相方が死亡していたら発動しないように修正
	-> 相方のSPが発動に必要なSPに満たない場合は発動しないように修正
	-> 発動時に相方もSPを消費するように修正

・gmcommand命令で使うダミーsdのfdを-1にするように修正（script.c）

----------------------------------------
//0169 [2007/04/25] by Rayce

・temperタブへのキラー情報表示実装
	自分が最後に殺した相手の名前（Kill）と自分を最後に殺した相手の名前（Killed）を
	temperタブで見ることができます。

	-> charid2nick構造体をmmo.hからmap.hへ移動
	-> map_session_data構造体にメンバ kill_charid, killed_charid を追加
	-> clif_update_temper() 追加

　　※battle_auriga.confの set_pckillerid を save_pckiller_type に改名しています。
　　　また値の使い方が変更されているので確認してください。
　　　デフォルトでは無効になっているので利用したい場合には設定してください。
　　　PvP, GvG, PKで仕分けが可能になっています。

　　※PC_KILLER_IDは廃止されます。
　　　代わりに PC_KILL_CHAR, PC_KILLED_CHAR が用意されます。
　　　今まではアカウントIDでしたが、本実装に伴いキャラクターIDに変更されています。
　　　スクリプトから呼び出す場合には十分注意してください（script/sample/npc_test_pcevent.txt参照）。

　　※PC_KILL_CHAR, PC_KILLED_CHAR は埋め込み変数として登録されています（db/const.txt参照）。
　　　スクリプトや@writevarsから値を書き換えると即座に対象キャラのtemperタブへ反映されます。

・map_reqchariddb() で返信付きキャラ名問い合わせを複数のプレイヤーが同時に行うと、最初の人にしか
　返信されない問題を修正
	charid2nick構造体のメンバ req_id を linkdb_node型の req に変更しています。
	既に名前問い合わせ要求済みでキャラサーバからの返信待ちの場合、返信すべきプレイヤーのアカウントIDを
	リンクリストに保存しておきます。
	map_addchariddb() が呼び出されたときにリストにあるプレイヤー全員に返信します。
	このときtypeに応じて clif_solved_charname() および clif_update_temper() を実行します。

・接続完了時にパートナーの名前をキャラサーバに要求するように変更（clif.c, pc.c）
	「あなたに逢いたい」を使用したとき、パートナーが一度もログインしてなくても
	即座に名前が呼ばれるようになります。
	スキル使用時にキャラ名の問い合わせを行うと map_reqchariddb() や map_addchariddb() がややこしく
	なるからというのが理由。

----------------------------------------
//0168 [2007/04/24] by Rayce

・元職業の算出について最適化
	pc_base_job構造体の宣言をmap.hに移動し、map_session_data構造体のメンバとして追加
	pc_authok() および pc_jobchange() のときだけ pc_calc_base_job() を実行して
	元職業の情報を保存しておきます
	各関数でわざわざ pc_calc_base_job() を呼び出さず直接値を取得できます

----------------------------------------
//0167 [2007/04/24] by Rayce

・pc_calc_base_job() でtypeの判定を行うとき、スパノビならtype=3にするように変更（pc.c）
　今のところtypeは利用されてませんが一応残しておきます
・map_session_data構造体から使われていないメンバ mob_view_class を削除（map.h, pc.c）

・party_member_added() でサーバクラッシュする可能性を修正（party.c）
・Mobが寒いジョークおよびスクリームを使うとき姿が消えないように修正（skill.c）
・clif_displaymessage() と clif_disp_onlyself() を同調させる（clif.*）
　引数の仕様を変更してメッセージにconstを付けるように修正

----------------------------------------
//0166 [2007/04/23] by Rayce

・以下の敵指定型の範囲攻撃スキルで他PCをshift+クリックしても発動するように修正（skill.c）
　例え範囲内に敵が存在していなくてもSPもアイテムも矢も消費します
	グリムトゥース
	ブランディッシュスピア
	シャープシューティング
	スプレッドアタック
	風魔手裏剣投げ
	龍炎陣
	朔風

　これらのスキルは敵関係チェックを skill_castend_id() ではなく skill_castend_damage_id() で行います。
　必要に応じて is_enemy フラグを利用してください。
　また battle_skill_attack() に渡すフラグ値の使用ビットを拡張しています。
　0x01000000を渡したときはスキルエフェクトのみを表示し、ダメージ処理は行いません。

　※今のところは暫定でskill.cに直接ハードコーディングしてますが、いずれはskill_db.txtのinf2
　　あたりを使ってある程度の設定ができるようにしたいとは思ってます

・ベナムスプラッシャーをボス無効に修正
・ベナムスプラッシャーの処理方法を最適化
・風魔手裏剣投げのダメージが分散スプラッシュするように修正
・風魔手裏剣投げの範囲攻撃部分が多段HIT表示されるように修正
・龍炎陣のスキル倍率を修正してみる
	Lv5のとき 900% x 3hit → 300% x 3hit

----------------------------------------
//0165 [2007/04/22] by Rayce

・高速化のため map_charid2sd() を手抜きマクロから関数に変更（map.*）
・map_quit() を少し整理（map.c）
・map_freeblock_timer() を呼び出す間隔を1分から10分にしてみる（map.c）
	エラー自体見たことないのでこの処理を丸ごと削除しても良さそうだが・・・

・pc.c, pc.hの整理
・motdの表示処理を少しだけ改善（pc.c）
・skill_tree構造体のneedメンバの配列が一つ多かったので修正（pc.c）

----------------------------------------
//0164 [2007/04/21] by Rayce

・倉庫に関して
	-> storage_flagがあるときは移動できないようにanti hackerチェック強化（clif.c）
	-> ギルドを解散したときにギルド倉庫のロック解除をinterサーバに要求しないように修正（storage.c）
	-> 倉庫データ受信時に既に倉庫を開いていないかチェックするように強化（intif.c）
	-> 倉庫データを切断待ちのクライアントが受信するとデッドロック状態になる可能性を修正（intif.c）
	-> アイテムをソートするタイミングが間違っていたので修正（storage.c）
	-> 倉庫を開いたままログアウトするとアイテムがソートされないバグを修正（storage.c）
	-> 紛らわしいので関数名の変更（guild.c, intif.c, storage.*）
		guild_storage_delete  → storage_guild_delete
		guild_storage_additem → storage_guild_additem
		guild_storage_delitem → storage_guild_delitem

	-> 試験的に、倉庫を開いている時のみデータをセーブするようにする（pc.c, unit.c）
	   自動セーブの時に個人倉庫のデータを不必要にセーブしなくて済むようになります
	   代わりにギルド倉庫と同様に倉庫を閉じるときや離脱するときにセーブするように変更しています

	-> 倉庫を閉じた瞬間にサーバクラッシュされるとアイテムのデュープが起こる問題の対策
	   battle_auriga.confに save_player_when_storage_closed を追加
	   デフォルトではnoですが負荷が掛かることよりもデータの安全性を優先したい場合はyesにしてください

----------------------------------------
//0163 [2007/04/21] by Rayce

・AthenaProject2294を参考にして以下を修正、thanks to Blazeさん
	-> フェオリチャギを多段HIT表示されるように修正（skill.c）
	-> ピアーシングショットをDEF無視攻撃に修正（battle.c）

・ROメールの添付アイテムを取得する部分を mail_getappend() として切り離す（intif.c, mail.*）
・mail_calctimes() はほとんど意味がないので削除（mail.*）
・unit_movepos() の返り値が間違っていた部分を修正（unit.c）

----------------------------------------
//0162 [2007/04/20] by Rayce

・AthenaProject2293よりmerge、thanks to 名無しさん
	-> 生命保険証のデスペナ軽減回数を設定可能に拡張（pc.c）
	   例えば「sc_start SC_LIFEINSURANCE,1800000,3;」で3回デスペナを軽減します
	-> 武器精錬で精錬不可のものがリストに出てしまうのを修正（clif.c, skill.c）
	   AthenaProject BTS報告Cocoaさん thank's
	-> オシリスカード装備時にリザレクションをするとSP表示が反映されなかったのを修正（skill.c）
	   AthenaProject BTS報告masterさん thank's

----------------------------------------
//0161 [2007/04/20] by Rayce

・ダメージが負のときの属性補正計算が間違っていたので修正（battle.c）
・弓でも三段掌が発動するように修正（battle.c）
・三段掌の判定順をダブルアタックよりも優先するように修正（battle.c）
・ゴスペルはボス属性に対しては無効にしてみる（skill.c）
・ガンバンテインはミストレスカードやウィザードの魂があってもジェムを消費するように修正（skill.c）
・ゴスペル、グラフィティ、温もりのスキルユニットグループが削除されるとき
　状態異常も解除するように修正（skill.c）
・skill.cのプロトタイプ宣言について細かい修正（skill.*）
・SC_GOSPELにReleaseable+4が入っていたのを修正（db/scdata_db.txt）

----------------------------------------
//0160 [2007/04/20] by Rayce

・map_searchrandfreecell() の更なる最適化（map.*）
	呼び出し元で配列変数を用意して、関数内部で空きセルの座標を順に格納します
	あとは呼び出し元で atn_rand() を使って任意のセルを抽出してください
	MAPの範囲チェックは map_getcell() でも行われるのでここでは省略しています
	これに伴い cell_xy 構造体を新しく追加

・緊急召集の修正（skill.c）
	-> 範囲はギルドマスターの周囲7x7セル
	-> battle_auriga.confの emergencycall_point_randam を emergencycall_point_type に改名
	-> emergencycall_point_type が1の場合、出現位置は完全なランダム
	   2の場合も同様にランダムだが「崖越えEMC」を禁止する
	   デフォルトでは本鯖に近いと思われる1に設定

・運命のタロットカードに関する修正（skill.c, status.*）
	-> 出るカードの種類の出現確率に偏りを持たせる
	   統計を取っていたサイトのデータを参考に適当に設定しました
	-> 運命の輪が連続で出続けると理論上無限ループが起こる可能性を修正
	-> 魔術師、力、悪魔、太陽の効果時間はskill_cast_db.txtのupkeep_time2を利用する

・PC以外にも混乱が発揮するように修正（unit.c）
・script_read_vars() でメモリをアロケートしなくて済むように修正（script.c）
・battle_auriga.confの no_emergency_call をデフォルトでnoに変更しておく

----------------------------------------
//0159 [2007/04/19] by Rayce

・path_search_real() に渡す walkpath_data 構造体はNULLでも使えるように改善および処理の最適化（path.c）
	based on eA, thx a lot!!

・0125以降、一部の歩行経路で壁を回り込んでの移動ができなくなっていたバグを修正（unit.c）
・rand() を atn_rand() に変更し忘れ箇所を修正（char.c, httpd.c, journal.c, login.c, path.c）
・unit.cの細かい修正および整形

----------------------------------------
//0158 [2007/04/18] by Rayce

・friend.cを少し修正

・SQL: 見栄えが良くないので、拳聖の感情のセーブデータを memo テーブルから切り離して
       feel_info テーブルに保存するように変更（char.c, char-converter.c）

	memo テーブルで使っていた type フィールドは廃止
	付属のAuriga158-changetable.sqlを実行すると自動的にデータが feel_info テーブル
	にコンバートされます

----------------------------------------
//0157 [2007/04/18] by Rayce

・script.cのbuildinで使われている変数の一部をshort型からint型に変更（script.c, unit.*）
・スクリプトで使える基数として2進数をサポート（script.c）
	0bを頭に付けて記述します。
	ビットフラグを明瞭に表現したいときなどに。

	0b1101 [2進数] = 13 [10進数] = 0xd [16進数] = 015 [8進数]

----------------------------------------
//0156 [2007/04/17] by Rayce

・AthenaProject2292の一部をmerge、thanks to Blazeさん
	-> デスペラードのダメージ発生インターバルを150ms → 100msに変更（skill.c）
	-> 実行範囲を持つNPCの範囲内でhideon→offをした時、スクリプトが再走しなかったのを修正（npc.c）

・クローズコンファインをボス属性無効に修正（skill.c）
・ストーンカースのLv6が以上のとき成功時にジェムが消費されないバグを修正（skill.c）
・skill_check_condition2() を少しだけ書き換え（skill.c）
・usediteminfo関数で製造者のIDを取得するとき、名前入りアイテムでない場合は0が返るように修正（pc.c）

----------------------------------------
//0155 [2007/04/17] by Rayce

・anti hacker、merged from eA（clif.c, map.h）
	-> MAPロード時に認証完了しているかどうかチェックする
	-> エモーション使用時に1秒以上インターバルがあるかどうかチェックする
	   clif_parse_Emotion() のパケットを短時間に連続で送信されると周囲のプレイヤーを
	   サーバキャンセルで落とすことができる穴を防ぎます

----------------------------------------
//0154 [2007/04/17] by Rayce

・アイコンパケットを送信するだけの状態異常を廃止
	以下の5つの状態異常はsc_dataとして実装する必要がありません。
	状況に応じてアイコンパケット0x196を送り付けるだけで良いからです。

	SC_RIDING   : pc_isriding() で状態の取得が可能
	SC_FALCON   : pc_isfalcon() で状態の取得が可能
	SC_WEIGHT50 : pc_50overweight() で状態の取得が可能
	SC_WEIGHT90 : pc_90overweight() で状態の取得が可能
	SC_DEVIL    : SG_DEVILを覚えているかどうかで判断可能

	-> 重量オーバーのアイコンを送信したかどうかの判定のためmap_session_data構造体にicon_weightメンバ追加
	-> pc_checkweighticon() 変更
	-> pc_setoption() 変更

・1プレイヤーにのみアイコンパケットを送りつける clif_status_load() 追加（clif.*）
	merged from eA, thx a lot!!
・カートを外すときにクライアント側で保存されているアイテムデータを消去するように修正（clif.*, pc.c）
	clif_cart_clear() 追加
・チェンジカートを使用したときサーバ側でベースレベルのチェックをするように強化（pc.c）
・clif_status_change() に SI_*** ではなく SC_*** を渡していた箇所を修正（skill.c, status.c）
・タイガーアイのパケット送信に clif_status_load() を使うように改善（pc.c, status.c）

----------------------------------------
//0153 [2007/04/16] by Rayce

・BCCのときも__int64型をatn_bignumber型として使うように変更（utils.h）
	32bitに強制変換されるバグが発生するのは恐らくunsignedのときだけだと思います
	atn_bignumber型はsignedなので問題はないはず
	不具合が起こる人は BIGNUMBER_DOUBLE をdefineしてコンパイルしてください

・eAを参考に clif_parse_LoadEndAck() の書き換え（clif.c）
	一部の処理の順番を変更しました
	またテレポやMAP移動などによる画面の切り替え時にクライアントに送られるパケットの量が削減されます

----------------------------------------
//0152 [2007/04/15] by Rayce

・温もり系の吹き飛び方向およびセル数がおかしくなっていた問題を修正（battle.c）
・skill_blown() の処理順を少し修正（skill.c）
・0136のゴスペルの修正が不完全だったので再度修正（status.c）
・skill.c, status.cの細かい整形

----------------------------------------
//0151 [2007/04/15] by Rayce

・battle_auriga.confの party_join_limit がnoのときに、パーティの機能が誤作動するバグを修正（party.c）
	refered from AthenaProject2291, thanks

----------------------------------------
//0150 [2007/04/15] by Rayce

・AthenaProject2291の一部をmerge、thanks to 暇人さん
　以下Readmeより転載
　　・料理(課金用)、戦闘教範50、生命保険証の効果を実装 (pc.c、status.c、status.h)
　　・上記の効果実装の為、関連dbを更新 (const.txt、item_db.txt、scdata_db.txt)

・Expペナルティ処理を修正してまとめた pc_exp_penalty() を追加（pc.c）
・レディムプティオ使用時、mapflagにnopenaltyが設定されていてもExpペナルティを受けるように修正（pc.c）

・064以降、「レディムプティオ」と「パパ、ママ、大好き」によるデスペナルティ回避効果が
　発動しなくなっていたのを修正（db/scdata_db.txt）
・battle_auriga.confの death_penalty_type を2に変更しておく
・db/const.txtからギルドスキル系の定数を削除
・db/const.txtのオートスペル系の定義を16進数に変更

----------------------------------------
//0149 [2007/04/14] by Rayce

・AthenaProject2290の一部をmerge、thanks to Blazeさん
　以下Readmeより転載
　　・NPCスキル「不死属性付与」効果時の挙動を修正（status.c、status.h)
　　・拳聖スキル「太陽と月と星の奇跡」を暫定実装（battle.c、battle.h)
　　・太陽と月と星の奇跡の発動確率を変更できるように修正（battle_athena.conf）

・SI_NIGHT が SI_MIRACLE に変更されたので@night, @dayのエフェクト表示部分をコメントアウト（atcommand.c）

----------------------------------------
//0148 [2007/04/14] by Rayce

・AthenaProject2289-fixよりmerge、thanks to 暇人さん
　以下Readmeより転載
　　・料理使用時のアイコン(STR～LUK、HIT、FLEE、CRITICAL)を表示するように修正 (status.c、status.h)
　　　AthenaProject BTS報告chaさん thank's
　　・料理使用時ログアウトしても効果が残るように修正 (scdata_db.txt)

----------------------------------------
//0147 [2007/04/14] by Rayce

・AthenaProject2288よりmerge、thanks to Blazeさん
　以下Readmeより転載
　　・NPCスキルの召喚系の仕様変更。種類 x Lv 匹 -> Lv 匹、召喚範囲の修正（mob.c)
　　・ソウルリンカースキル「エスク、エスウ、エスカ」の状態時、姿を維持しなかったのを修正（status.c)
　　・拳聖スキル「太陽と月と星の融合」状態のときは、移動速度が上がるように修正（status.c)
　　・拳聖スキル「太陽・月・星の温もり」のノックバック方向をMobの向きに依存するように修正（skill.c)
　　・MobスキルDBの召喚を変更に伴い修正（mob_skill_db.txt）

・skill_blown() で吹き飛ばしセル数が0のときは何も処理しないように修正（skill.c）
・mob_summonslave() の引数を一つ増やす（mob.*）

----------------------------------------
//0146 [2007/04/13] by Rayce

・高速化のため skill_get_skilldb_id() をマクロに変更（skill.h）
・db/skill_db.txtの読み込みの際、skill_get_skilldb_id() を使って
　スキルIDの範囲チェックを行うように最適化（skill.c）
・unit_skilluse_id() および unit_skilluse_pos() を最適化（unit.c）
・補正済み射程を返す skill_get_fixed_range() を追加（clif.c, mob.c, skill.*, unit.c）

・ギルドスキル使用時のNULLチェック追加（skill.c）
・skill_check_condition2() からギルドスキルに関するチェックを削除（skill.c）
	チェックが二重になるので skill_check_condition2_pc() だけで良い

----------------------------------------
//0145 [2007/04/13] by Rayce

・clif.cの全面的な修正や整形
	-> バッファオーバーフローする可能性を修正
		clif_GlobalMessage()
		clif_party_message()
	-> 引数の仕様を変更
		clif_clearflooritem()
		clif_dispchat()
		clif_clearchat()
		clif_showvendingboard()
		clif_closevendingboard()
	-> ホムの情報を参照すべきところがPCの情報を参照しているバグを修正
		clif_homskillinfoblock()
		clif_homskillup()
	-> clif_set009e() を clif_dropflooritem() に吸収
	-> clif_set01e1() の処理を変更
	-> パケット送信用のバッファをunsigned char型に修正
	-> nullpoチェックが抜けてる箇所を修正

----------------------------------------
//0144 [2007/04/13] by Rayce

・0143の温もりに関する修正（battle.c, pc.c, skill.c, status.c, unit.c）
	-> status_change_end() 内でスキルユニットを削除する
	-> skill_unit_group のアドレスの保存先をsc_dataのval3からval4に変更
	-> battle_calc_weapon_attack() の一部を修正

----------------------------------------
//0143 [2007/04/12] by Rayce

・AthenaProject2286-fixよりmerge、thanks to Blazeさん
　以下Readmeより転載
　　・拳聖スキル「太陽・月・星の温もり」実装（skill.c、battle.c、status.c、unit.c、pc.c)
　　・マップを移動した時、拳聖スキル「太陽・月・星の安楽」の効果を削除するように修正（pc.c)
　　・スキルユニットを設置後、ハエやマップ移動で消えてしまうのを修正（pc.c、unit.c)
　　・上記変更に伴うunit_remove_map関数の仕様変更
　　	（unit.c、unit.h、pc.c、mob.c、npc.c、pet.c、script.c、atcommand.c)
　　・テコン系列の各種スキルの使用SPや詠唱時間などが間違っていたのを修正
　　	（skill_require_db.txt、skill_cast_db.txt）
　　・テコン系列の蹴りスキルを3段HITするように修正（skill_db.txt）
　　・ガンスリンガースキル「グラウンドドリフト」の発動時エフェクトを修正（skill.c、skill_unit_db.txt）
　　・モンスターの最低沸き間隔時間を5秒から1秒（本鯖仕様）に修正（mob.c、unit.c）

----------------------------------------
//0142 [2007/04/11] by Rayce

・guild_member構造体から使われないメンバ rsv1, rsv2 を削除
・guild_explusion構造体から使われてないメンバ acc, rsv1, rsv2, rsv3 を削除
	セーブデータの形式が変更されているのでご注意を

・mapif_parse_GuildLeave() を少し修正（int_guild.c）
・一部のmemcpyをstrncpyに修正（chat.c, clif.c, npc.c）

・TXT: JOURNAL_IDENTIFIERをバージョン03に変更しておく（journal.c）
・SQL: main.sql修正、Auriga-0142_changetable.sql添付

----------------------------------------
//0141 [2007/04/10] by Rayce

・家族PTによるLv差を無視した経験値公平機能実装（int_party.c, intif.*, party.c）
　以下の条件が揃ったときに設定可能
	-> 親子の3人だけのPT
	-> 養子キャラがオンライン
	-> 両親のうちどちらかがオンラインで養子キャラと同一MAPに居る
	   （もう一人の親については特に制限しない）
	-> 両親のLvが70以上
　以下は仕様
	-> 誰かがMAP移動やログアウトした時点で公平は解除
	-> 誰かが加入・脱退した時点で公平は解除

・party構造体のメンバ exp, item をunsigned char型に変更（mmo.h, inter.c, party.*）
・doc/inter_server_packet.txt修正

----------------------------------------
//0140 [2007/04/10] by Rayce

・TXT: アカウントデータ（auth_dat）およびキャラデータ（char_dat）の検索を高速化（login.c, char.c）
	バイナリサーチのアルゴリズムを使って検索します
	もしセーブデータのIDが順番に並んでない場合は、ロード時に挿入ソートして補正します

	login_id2idx() 追加
	char_id2idx() 追加

----------------------------------------
//0139 [2007/04/09] by Rayce

・プレイヤーの base_level, job_level を保存する変数をunsigned short型に変更（mmo.h, mob.*, pc.c）
	map.hのMAX_LEVELを増やせば255以上にも対応可能になります

・isspace() に渡す引数をunsigned char型にキャストするように修正（atcommand.c）
・clif_packet_debug() の関数本体を削除し忘れ（clif.c）
・細かい修正や整形（int_homun.*, int_party.c, int_pet.c, homun.c）

・SQL: levelに関連するフィールドの型を変更（main.sql, Auriga139_changetable.sql）

----------------------------------------
//0138 [2007/04/04] by Rayce

・AthenaProject2284よりmergeおよび一部改変、thanks to Blazeさん
　以下Readmeより転載
　　・Mobスキル「エモーション」によるモードチェンジ実装（skill.c)
	　　mob_skill_db.txt、エモーションの値2にmodeを入れるとその値へモードチェンジします。
	　　例）アルギオペ追跡時にノンアクティブ化（移動1+攻撃128=129）
	　　1099,エモーション＠アルギオペ,chase,197,1,100,0,5000,no,self,always,0,19,129,,,,
　　・Mobの複数の同じスキルは使用後ディレイを共有するように修正（mob.c)

・不要なローカルプロトタイプ宣言を削除（mob.c）
・mobskill_use_id() および mobskill_use_pos() を移動（mob.c）
・使われてないプロトタイプ宣言を削除（mob.h）
	mobskill_use_id2()
	mobskill_use_pos2()
	mobskill_use_id_sub_command_to_slave()

----------------------------------------
//0137 [2007/04/04] by Rayce

・AthenaProject2281よりmerge, thanks to 暇人さん
　以下Readmeより転載
　　・スキル「マグヌスエクソシズム」のFlag値をエラーが出ない様に修正 (db/skill_uniti_db.txt)
　　・飛行船NPCの一部修正 (npc_town_airport.txt)

・AthenaProject2282よりmerge, thanks to Paraさん
　以下Readmeより転載
　　・追加された2種類のペット「クリスマスゴブリン」「餅」を実装（db/pet_db.txt）

----------------------------------------
//0136 [2007/04/03] by Rayce

・AthenaProject2280よりmerge, thanks to Blazeさん
　以下Readmeより転載
　　・スキル「火炎陣」のHIT数を修正 (db/skill_db.txt)
　　・アサシン転職クエストのJob50時の処理を修正 (npc_job_12assassin.txt)
　　・混乱発動時の挙動を修正 (src/map/status.c)
　　・ゴスペル効果「全状態異常耐性」を耐性計算している状態異常のみに対して発動するように (status.c)
　　・ジークフリードの状態異常耐性実装 (status.c)

----------------------------------------
//0135 [2007/04/03] by Rayce

・AthenaProject2279よりmerge, thanks to Blazeさん
　以下Readmeより転載
　　・スキル「火炎陣」の仕様を修正 (skill.c)
　　・スキル「一閃」の仕様を修正 (skill.c)
　　・ファイアーボールが多段HITしていたのを修正 (skill.c)
　　・スキル「投擲修練」の効果が風魔手裏剣などに適用されていたのを修正 (battle.c)
　　・スキル「影分身」が影宝珠を消費せずに使用できたのを修正 (db/skill_require_db.txt)
　　・忍者スキル・ガンスリンガースキルの攻撃力・詠唱時間などを修正
　　　(src/map/battle.c、db/skill_db.txt、db/skill_cast_db.txt)
　　・ガンスリンガーのスキルで装備制限の相違を修正 (db/skill_db.txt)
　　・忍者スキル・ガンスリンガースキルで装備制限の相違を修正 (db/skill_db.txt)

----------------------------------------
//0134 [2007/04/03] by Rayce

・太陽と月と星の融合を使ったときに拳聖の魂が解除されるように修正（skill.c）
・死亡している敵プレイヤーがサイトブラスターの効果範囲内に居るとサイトブラスターが
　解除されてしまうバグを修正（status.c）
・不要な関数 clif_parse_debug() を削除（clif.c）

・db/packet_db.txtの一部を修正
・パケット解析結果を doc/client_packet.txt に反映

----------------------------------------
//0133 [2007/03/27] by Rayce

・clif_homskillup() は0x10eではなく0x239のパケットを使うように修正（clif.c）
・ホムの腹減り値に使うパケット0x230のtypeを0x200に修正（homun.c）

・party_share_loot() を party_loot_share() に改名（party.*, pc.c）
・party_member構造体のメンバのサイズ変更（mmo.h, int_party.c, party.*）
	leader : unsigned char
	online : unsigned char
	lv     : unsigned short

----------------------------------------
//0132 [2007/03/25] by Rayce

・battle_auriga.confを少し整形
・typo修正 penaly → penalty（battle.*, status.c）
・スクリプトのsc_end命令でダンス状態とバジリカが正常に解除されるように修正（script.c）

・ゴスペルに関する修正（skill.c, status.c, unit.c）
	-> ゴスペル中にハエの羽などでテレポートすると動けなくなる問題を修正してみる（unit.c）
	-> status_change_end() 内でスキルユニットを削除する
	-> skill_unit_group のアドレスの保存先をsc_dataのval3からval4に変更
	   グラフィティに合わせるため

----------------------------------------
//0131 [2007/03/24] by Rayce

・サーバースナップショット（version.h）
・不要なファイルを削除
	bcc32_consqlmake.bat
・全てにおいて「Athena」の冠を撤去、「Auriga」に変更

----------------------------------------
//0130 [2007/03/24] by Rayce

・使われてない battle_config.unit_movement_type を削除（battle.*）
・char.dspの一部が間違っていたので修正
・db類の更新 thanks to huge cgi

----------------------------------------
//0129 [2007/03/23] by Rayce

・socket_athena.confの socket_ctrl_panel_url の読み込みを少し修正（socket.c）
・httpd_erase_pages() でメモリリークが発生する可能性を修正（httpd.c）

・関数名マクロ __func__ をVCでも使えるように修正（malloc.h, nullpo.h, utils.h）
	malloc.hとnullpo.hでの定義をutils.hにまとめる
	VC7.0以上であればgccと同様にnullpoエラーが出たとき関数名が出力されるようになります

----------------------------------------
//0128 [2007/03/22] by Rayce

・BCCとVCでSQLの設定が容易に出来るようにbatファイル修正（bcc32_clean.bat, bcc32_make.bat, vc_make.bat）
　BCCでのtxt-converter.exeの作成はbcc32_make.batに吸収
　bcc32_consqlmake.batは不要になったので削除予定

・doc/sqllogin.txtの内容を適切なものに編集
・doc/server_build.txtに少し加筆

・SQL: BCCでstrcmp系のエイリアスが重複定義エラーとなる場合があったので修正（utils.h）
・SQL: login-converter.cの read_gm_account() がおかしかったので修正（login-converter.c）

----------------------------------------
//0127 [2007/03/22] by Rayce

・httpd.cで警告が出ていたので修正（httpd.c）
・*.dspのビルドオプションに NO_HTTPD_CGI をデフォルトで入れておく

・SQL: converter.*のinclude関連修正
・SQL: athena.dswにmap_sql.dspを追記し忘れていたので更新

----------------------------------------
//0126 [2007/03/21] by Rayce

・0125の unit_walktoxy() の変更が不完全だったため、アクティブMobが常に2歩後退するように
　なっていたバグを修正（mob.c, pet.c）
・障害物およびバジリカ判定は目的地に到着してないときだけ行うように修正（unit.c）
・unit_movepos() で移動させたときパーティのHP情報通知検査が誤作動する可能性を修正（unit.c）

・アサシンの回避率上昇スキルによる移動速度増加効果が何かしらのステータス異常にかかっていないと
　発現しなかったバグを修正（status.c）
・クローキングの速度増加の計算方法を修正、壁チェックの処理を最適化（skill.c, status.c, unit.c）
・status_calc_pc() 内の速度に関する処理を少し最適化（status.c）

----------------------------------------
//0125 [2007/03/20] by Rayce

・バジリカの条件チェックは詠唱完了時には行わず詠唱開始時のみ行うように修正（skill.c）
・PCが移動要求したとき unit_can_move() が2回呼ばれていた無駄を修正（clif.c）
・歩行中に障害物に当たる際、障害物にめり込まないように変更（unit.c）
・unit_walktoxy() の返り値が間違っていたので修正（unit.c）
　移動出来たら1を、失敗なら0を返すように変更します

・歩行は半歩ずつではなく一歩ずつ行うようにしてみる（map.h, mob.c, path.c, pet.c, unit.c）
	マスの境界では今のところ何も処理しないため
	不要になったpath_halfをwalkpath_data構造体から削除

----------------------------------------
//0124 [2007/03/19] by Rayce

・nextやselectなどで入力待機中のプレイヤーをattachrid関数でアタッチしたとき、元のスタック情報が破棄
　されずスクリプトの誤作動やメモリリークが発生していたので修正（clif.c, script.c）
・npc_checknear() でチェックに引っ掛かったら警告を出力するように（npc.c）
・db/scdata_dbのReleasableの項目にSC_BASILICAを許可した場合、バジリカのセルが解除されるように修正（status.c）

----------------------------------------
//0123 [2007/03/18] by Rayce

・メモライズと緊急召集はメモライズで詠唱短縮できないように修正（unit.c）
・職業定義をmap.hからmmo.hに移動（char.c, clif.c, guild.c, mmo.h, map.h）
・guild_send_memberinfoshort() を少し修正（guild.c）
・db/scdata_dbのReleasableの項目にSC_DANCINGを許可した場合、演奏状態が正常に解除されるように修正（status.c）
　ただし死亡時だけは安全性維持のためdbの設定に関わらず必ず解除されます

・gccでLOCALZLIBを指定しないときはsrc/common/zlibをコンパイルしないように修正

----------------------------------------
//0122 [2007/03/17] by Rayce

・MinGWでのコンパイルに関する修正
	-> LOCALZLIB無しでコンパイル出来るように修正（grfio.c）
	   Win系と同じく動的にdllをロードするので -lz は付けない
	-> 今のところ利用してないが一応 MINGW をdefineしておく
	-> #pragma で警告が出るので -Wno-unknown-pragmas を付ける

・Makefileに関してeAよりmerge
	-> gcc4.X系で大量に出る警告の抑制
	   自動でgccのversionを取得して -Wno-unused-parameter と -Wno-pointer-sign を付ける
	-> -ffast-math をデフォルトで付けておく

・変数の初期化を忘れている箇所を修正（path.c, pc.c）
・0121の警告抑制が不完全だったので修正（core.c）
・パケット0x110と0x223についてeAの情報を追加（clif.c）
・doc/client_packet.txt更新

----------------------------------------
//0121 [2007/03/15] by Rayce

・AthenaProject2278からpacket_db.txtを更新、2007-02-12aSakexeに対応
・skill_unit_move_unit_group() を少し修正（skill.c）
・pid_create() の警告抑制（core.c）

----------------------------------------
//0120 [2007/03/14] by Rayce

・二重ログインをloginサーバで検出できるように修正（login.c, char.c）
　refered from Freya, thanks!!
	login_athena.confでスイッチできるようになっています。デフォルトは本鯖仕様で有効。
	無効にすると従来通りchar, mapサーバで検出を行いますが、同一アカウントで複数のワールドに
	ログイン可能なので##変数が正しく得られる保証がありません。
	有効のままにしておくことをお勧めします。

　※ID,Pass入力後、ワールド選択前にキャンセルして再度ID,Passを入力すると
　　「前の接続情報が残っています」と言われてログインが弾かれますが、これは本鯖に近い仕様です。

・二重ログインを完全に防ぐため、キャラ選択完了後にauth_fifoにある同一アカウントの未認証データを
　全て破棄しておくように修正（char.c）

----------------------------------------
//0119 [2007/03/14] by Rayce

・移動情報パケットに0x86を使う（clif.*, skill.c, unit.c）
　merged from eA, thanks a lot!!
	0x7bよりもサイズが遥かに小さく、また服色パケットを再送信しなくても服色を維持出来るようです。
	これにより通信量の大幅な削減が見込まれます。

	clif_movepc(), clif_movemob(), clif_movepet(), clif_movehom() 削除
	clif_move() 追加

・0111の@modelの修正が間違っていたので修正（atcommand.c）
・doc/client_packet.txt更新

----------------------------------------
//0118 [2007/03/14] by Rayce

・シャープシューティング、朔風の攻撃範囲を本鯖仕様に修正（map.*, skill.c）
	以下の問題点があったため map_foreachinpath() を完全に書き換えて map_foreachinshootpath() としました。
	　- 射線が考慮されておらず壁があっても攻撃が当たる
	　- 斜め方向に打つときの領域が本鯖よりも細くて長い、形が異なる
	　- 射線幅が1なので map_foreachinpath() を3回呼び出さなければならない

	直線方向は矩形になるので map_foreachinarea() に path_search_long() のチェックを入れるだけで済ませます。
	斜め方向の領域チェックは少々厄介ですが、ベクトル座標系に正規化して行います。
	判定に要する計算量が少なくて済む上に射線幅が広くなっても対処できます。

　※壁に対する挙動メモ
　　◎ = 攻撃主, ○ = 発動, × = 不発, ■ = 壁

　　　　　　　　　○○○○××　　　　　　　　　　　　　　○○■×××
　　　　　　　　　◎○○○■× →　　　　　　　　　　　 　◎○○○○○ →
　　　　　　　　　○○○○××　　　　　　　　　　　　　　○○○○○○

　　　射線上に壁があるとそのラインで止まる　　射線上になければ突き抜ける
　　　実質の射程距離が減少する　　　　　　　　壁の後ろ部分は path_search_long() で判定

----------------------------------------
//0117 [2007/03/11] by Rayce

・interサーバへホムの新規作成要求を行うとき、以下の条件でセーブデータが削除されずにゴミが
　残り続けたり他キャラのホムデータを受信するバグを修正（int_homun.c, homun.*, inter.c）
	- 返答が届く前にプレイヤーがログアウトしている
	- 返答が届く前に同じアカウントの別キャラにチェンジしていた
	- コールホムンクルス未取得なキャラが@makehomunを使った

・SQL: mapサーバのMakefileがSQL対応になっていなかったのを修正

----------------------------------------
//0116 [2007/03/11] by Rayce

・イベントデータの検索はcase-sensitiveで行うように修正
	基本的にイベントデータは Test::OnKilled のような形になっていますが、
	前半のNPC名はcase-sensitive、後半のラベル名はcase-insensitiveです。
	今まではラベル名を優先してcase-insensitiveで検索を行うようになっていましたが、
	NPC名にマルチバイト文字を使っている場合には他のNPCのイベントが呼ばれる不具合がありました。
		例）イ::OnEvent と ツ::OnEvent があった場合
		　　donpcevent "イ::OnEvent"; を実行すると ツ::OnEvent も呼ばれてしまう

	そこでNPC名を優先して今後は完全にcase-sensitiveで行います。
	上記の例では イ::OnEvent のみが呼ばれます。
	ただし イ::OnEVENT は別物として扱われるようになるので注意してください。
	また副次的効果として、strdb_search() がそのまま使えるので npc_event_do() の検索能が向上します。

・NPCイベントを呼び出す際、NPC名に : が含まれる場合を考慮するように修正
・npc_event() を少し修正
・「npc file syntax error」となるときの警告文を改良（npc.c）

----------------------------------------
//0115 [2007/03/10] by Rayce

・スクリプト命令/関数に関して全体的に修正（script.c）
　　-> 以下の命令/関数でアイテムが見つからなかったとき、リンゴのIDで補正しないように変更
　　　　　　countitem
　　　　　　countcartitem
　　　　　　checkweight
　　　　　　getitem
　　　　　　getitem2
　　　　　　delitem
　　　　　　getareadropitem
　-> 以下の命令/関数においてMAP名の "this" 指定に対応
　　　　　　getcastlename
　　　　　　getcastledata
　　　　　　setcastledata
　-> getequipid関数で何も装備してない場合は-1ではなく0を返すように修正
　-> getwaitingroomstate関数で文字列を取得する際、特定の状況でサーバクラッシュするバグを修正
　-> 細かい整形

----------------------------------------
//0114 [2007/03/10] by Rayce

・0113のmonster定義について修正（npc.c）
	イベント名が数字1文字だけの場合はイベント指定無しと同じ扱いにします。
	現状の npc_monster.txt にはダミーイベントとして0または1が書かれている
	ことを忘れていました・・・。

・トルリョチャギ使用時、敵の周囲3x3にいる他のMobを1セル吹き飛ばしながらスタンにかかるように修正（battle.c, skill.c）
	吹き飛ばし距離は skill_db.txt のblow_count、スタン時間は skill_cast_db.txt のupkeep_time2

----------------------------------------
//0113 [2007/03/09] by Rayce

・NPC定義でmonsterを指定する場合（定期沸き設定のもの）について変更（npc.c）
	-> イベントが23文字までしか指定できなかった問題を修正
	   今後はscriptのmosnter命令と同様に49文字まで指定できます
	-> イベント名が4文字以下の場合はイベントとして設定されなかった問題を修正
	-> ギルドIDを設定する際の引数の位置を変更
	   Athena1228から続く仕様を変更してギルドIDが最末尾になります！
	   詳細はdoc/script_ref.txtを参考にしてください
	-> 引数の個数チェックを強化

・スクリプトのmonster命令の仕様変更（script.c）
	上記のNPC定義monsterと同様にギルドIDを指定する引数の位置を変更します！

----------------------------------------
//0112 [2007/03/09] by Rayce

・scriptlabel_dbへの登録はOnで始まるイベントラベルに限定するように修正（script.c）
	通常のラベルはエクスポートされず最終的には全く利用されなくなるためです。
	function構文で使う関数名もエクスポート対象外になりますので、他スクリプトから
	完全に遮蔽されて安全性がさらに高まります。

・scriptlabel_dbへの登録前にラベル名をチェックするように強化（npc.c, script.c）
	npc_convertlabel_db() でラベル名を正しく取得するため、以下の条件をエラーとして扱います。
	ただしOnで始まるイベントラベルだけであり、通常のラベルには適用されません。
		- ラベル名に余計な文字が含まれている
		- ラベル名が24文字以上である

・NPC名に : が一文字だけ含まれているとき無限ループに陥るバグを修正 from eA（npc.c）
・npc.cおよびnpc.hの細かい整形
・gccでの警告潰し（int_guild.c, atcommand.c）
・0111で更新し忘れていたconf/help.txtを添付

----------------------------------------
//0111 [2007/03/09] by Rayce

・atcommand.cについて
	-> @kamib, @kamic, @monstermapが大文字で使えなかった問題を修正
	-> @modelで服色を変更するとき、テコン系職も服色未実装判定に加えるように修正
		ついでに引数に-1を指定できるように拡張, thanks to as on AthenaProject
		-1指定の箇所は変更しません
	-> @produceで製造できるアイテムが特定IDの範囲に縛られていた問題を修正
	-> @str, @agi, @vit, @int, @dex, @lukの最適化
	-> @night, @dayをeAライクに変更
		暗闇状態だと視野が狭すぎるのとログアウトできない問題があったので、アイコン番号160を
		SI_NIGHTとして定義して利用することにします
		パケットを送り付けるだけなのでeAのような高い機能はありません
	-> @giveitemも@itemと同様にIDを負の値にするとランダム系アイテムを取得できるように拡張
	-> @usersで利用するデータベースをstrdbからnumdbに変更
	-> MAX_SIZE_FIX, RCT_MAXがデフォルトよりも大きな値に設定していた場合、@mobinfoでサーバクラッシュ
	   する可能性を修正
	-> 細かい整形

----------------------------------------
//0110 [2007/03/08] by Rayce

・map.cについて
	-> map_foreachinmovearea() の処理を少し改善
	-> map_check_dir() を書き換え
	-> 細かい整形

----------------------------------------
//0109 [2007/03/06] by Rayce

・コンパイルオプションからNO_CSVDBを削除（db.*, script.c）
	db.cの関数そのものに問題があるわけではないので、スイッチを設けて機能抑制する意味はない
・Makefileから -Wno-sign-compare を削除

・SQL: スクリプト経由でのSQLクエリ発行はセーブデータのデータベースと別に出来るように修正（map.*, script.*）
	sqlquery関数の危険性を軽減するための処置です。
	map_athena.confにさらにスクリプト専用の設定項目を追加しています。
	デフォルトはセーブデータと同じですが、別途変更すれば異なるデータベースに保存することが可能です。
	セーブデータで使うIDとは別に専用のIDを用意して適切なアクセス権限を与えることで、sqlquery関数による
	操作を重要なセーブデータから隔離することができます。

・SQL: map_athena.confに sql_script_enable の項目を追加
	sqlquery関数を利用可能にするかどうかのスイッチです。
	デフォルトでは0（無効）にしておきます。

----------------------------------------
//0108 [2007/03/06] by Rayce

・スクリプトにおける構文もcase-insensitiveに変更
	大文字と小文字が区別なしになります。eA互換。
	ifとIF、switchとSWITCHはそれぞれ同等です。

・CSVアクセス命令でデータを書き込む際に指定するファイル名の規制緩和
	/（スラッシュ）_（アンダーバー）の使用を許可します。
	ディレクトリの指定ができるのでカレントディレクトリに置かなければならない縛りがなくなります。

・script_athena.confでimportすると最初に設定したデータが初期化されるバグを修正
・script_athena.confのcheck_gotocountを16384に上げておく（128*128）

----------------------------------------
//0107 [2007/03/05] by Rayce

・SQL: スクリプトにsqlquery関数、strescape関数追加 based on eA（script.c）
	CSVアクセス命令/関数と同等の動作を可能にします。
	ただしCSV系のような安全性やセキュリティ面のための利用規制は一切設けていません。
	危険な動作（セーブデータの破壊、インジェクション攻撃など）が容易に可能ですが、全て利用者の
	責任に委ねられますので注意してください。
	GRANTさえあれば如何なるSQL文も発行できます。

	CSV系とは異なりデータのキャッシュは作りません。
	データのやり取りを行う際は常にクエリがSQLサーバに飛んでいます。
	また一度に発行するクエリは64kB以内にしてください（長い場合は無視されます）。

　※利便性を高めるために一部eAとは異なる仕様にしています。
　　（SELECT以外の場合の返り値や、SELECTは二次元配列にデータ格納する点など）
　　詳細は doc/script_ref.txt や sample/npc_test_sqlquery.txt を参照。

----------------------------------------
//0106 [2007/03/04] by Rayce

・BCC, VCでstrncasecmpが使えるようにdefineを書き換え（utils.*）
　utils.cにあった自作のstrcasecmpは不要になったので削除
・@helpの一部のコードをstrncasecmpに最適化（atcommand.c）
・map_searchrandfreecell() の処理を最適化（map.c）

----------------------------------------
//0105 [2007/03/04] by Rayce

・MAPサーバが正常に終了するときのみOnFinalラベルを実行するように変更
　（core.*, login.c, char.c, converter.c, map.c）
	do_pre_final() 追加
・@mapexitの clif_GM_kick() は不要なのでいきなり exit(1) で落とすように修正（atcommand.c）

・スクリプトに関する追加機能（script.c）
	-> 制御コードをサポート
	   改行 "\n" は内部の処理で \r\n に置換されています
	-> 文字列の連結をサポート
		mes "aaa"
		    "bbb";　は mes "aaabbb"; と同等になります

----------------------------------------
//0104 [2007/03/04] by Rayce

・098のOnFinalラベル実装において致命的なバグがあったので修正（map.c, script.c）
	do_final_script() のあとに do_final_npc() が実行されるようになっていたので
	do_final_npc() 内で script_free_code() が呼ばれるときには既に str_buf, str_data が
	解放されているという最悪の状態になっていました。
	do_final_script() からOnFinalイベントの実行処理を切り離し、do_final_npc() の
	後に呼び出すように修正しました。

・map_addflooritem() のミスを修正（map.c）
・guild_recv_memberinfoshort() を少し修正（guild.c）

・SQL: char_set_online() と char_set_offline() の処理をまとめる（char.c）

----------------------------------------
//0103 [2007/03/03] by Rayce

・親密度が0になってペットが消えるとき intif_delete_petdata() が二重に呼ばれていたため
　「pet data delete failure」が出力されるバグを修正（pc.c, pet.c）

・ペットがアイテムをルートするときのAIを少し最適化（pet.c）
・battle_athena.confに pet_loot_type を追加（battle.*）
・MOB, PETがアイテム個数上限のときにルートを行う処理において、memcpyをmemmoveに最適化（mob.c, pet.c）

----------------------------------------
//0102 [2007/03/03] by Rayce

・ペットの卵のデータが削除されずセーブデータにゴミが残り続ける問題の修正、残り全て
	-> サーバ停止時に床アイテムを消すとき（map.c）
	-> map_addflooritem() でアイテム設置失敗したとき（map.c）
	-> サーバ停止する時点でMOBがペットの卵をルートしていたとき（npc.c）
	-> ペットが消える際にペットの卵をルートしていたとき（pet.*, unit.c）

・ペットがルートアイテムを所持する設定のとき、リスタートおよび他MAPサーバへの移動で
　ルートアイテムが消失してしまうバグを修正（clif.c, pc.c）

----------------------------------------
//0101 [2007/03/03] by Rayce

・ペットの卵のデータが削除されずセーブデータにゴミが残り続ける問題の修正、続き（map.*, mob.c, pet.c）
	MOBとPETのルートアイテムが地面に落ちるまでのディレイタイムの間にサーバが停止する場合について。
	do_final_timer() からは intif_delete_petdata() が実行できないので、delay_item_drop2構造体にnext
	メンバを追加しペットの卵をドロップするときはリンクリストのキューを作って管理することにしました。
	0100のタイマーヒープの変更はこのための布石です。
	登録した順にタイマーが実行されるのでキューの順番が狂うことはないはずです。

	map_push_delayitem_que()
	map_pop_delayitem_que()
	map_clear_delayitem_que() 追加

----------------------------------------
//0100 [2007/03/03] by Rayce

・タイマーヒープの優先順位を変更（timer.c）
	タイマーヒープへデータをpushする際の二分挿入ソートで、tickが等しい場合は大の方へ
	挿入されるように変更します。
	つまり先に登録されていた方が優先的にpopされることになります。

・上記の変更に伴う不具合を修正（char.c, chrif.c）
	charサーバがloginサーバへ、mapサーバがcharサーバへそれぞれ接続するとき認証が完了する前に
	send_users_tologin() を実行するようになっていました。
	check_connect_login_server() に対する実行順序の依存性を断ち切るために、セッションのauthがある
	かどうかを判定するように修正しています。

・タイマー関数リストに登録し忘れている関数をリストに追加（socket.c, pet.c, script.c）

・SQL: 099におけるinterサーバのペットデータの削除について、本来は成功として扱われるべき
　     ものが失敗として扱われるようになっていたので修正（int_pet.c）

----------------------------------------
//099 [2007/03/02] by Rayce

・@itemでアイテムIDに負の値を入れたとき、対応する番号のランダム系アイテム（青箱やカード帖など）
　を取得できるように拡張（atcommand.c）
・mob.cとpet.cにある delay_item_drop, delay_item_drop2構造体はほぼ同じなので
　まとめてmap.hで定義するように移動
・猛虎硬爬山のスキル発動タイミングを1sec遅らせるように修正 from eAthena（skill.c）

・SQL: interサーバでペット情報をdeleteする際、ペットIDが見つからなかった場合はTXTと同じように
       失敗flagを返すように修正（int_pet.c）

----------------------------------------
//098 [2007/02/28] by Rayce

・MAPサーバ終了時にchar,interサーバへデータを送信できるように修正
　　今まではキャラがMAPサーバ内に残っている状態でいきなりサーバを停止すると、キャラデータやギルドExpのキャッシュなどが
　　セーブされず巻き戻り等の不具合が発生するという仕様でした。
　　今回の修正によりMAPサーバ停止時に必要なデータをchar,interサーバに送信するようになったので、わざわざ@kickallで
　　キャラを全員kickしてからサーバを止めるといった一連の手間をかけることなく安全に停止出来ます。
　　map.c::do_final() で行う処理の順番が非常に重要になっていますので、今後何かしら修正を加えるときは注意してください。

	1. まず最初に do_final_script() を実行する
	   OnFinalイベント（詳細は後述）で実行されるスクリプトが如何なる制約も受けないようにするため、一番最初に
	   この関数を呼び出す必要があります

	2. ギルドExpのキャッシュをinterサーバにフラッシュする
	   guild_payexp_timer_sub() でギルドに関する情報を取得する必要があるため、必ずキャラ切断の前に実行する
	   必要があります

	3. chrif_disconnect_sub() で全キャラを切断します
	   今までは do_final_chrif() 内で行っていましたが、do_final_chrif() は char_fd を -1 にしてしまうので
	   char,interサーバのパケットバッファにデータを保存することができません
	   そこで切断処理だけを先に行うようにしています

	4. 残りの do_final関数群を実行します
	   これまでと同様に各ファイルで必要な後始末をします
	   ただし do_final_storage() は少し修正を加えて、numdb_final() したあとに倉庫dbをNULLにしています

	5. 床アイテムを消去します
	   必ず全キャラを切断したあとに処理を行う必要があります
	   キャラ切断時には map_quit() が呼ばれますが、ペットが居るときで且つペット自身がルートアイテムを保持する
	   設定になっていて、飼い主が重量オーバーでペットからアイテムを受け取れない状況であればアイテムは床に
	   ドロップされるからです
	   今まではこの事例が発生するとメモリリークになっていましたが修正されます

	6. 最後に do_final_chrif() を実行する
	   内部で flush_fifo() を呼び出します
	   do_final() は既に core.c のwhileループを抜けた後なのでパケットの送受信は行えません
	   そこでこの関数を明示的に呼び出すことで、do_final() 内で溜めたパケットデータをchar,interサーバへ送信する
	   ことが可能になります
	   続いて chrif_disconnect() が呼ばれますが、キャラのセッションは全て閉じた後なので chrif_disconnect_sub()
	   は実行されません
	   また倉庫のキャッシュを消す処理は専用の関数 storage_clear_cache() を用意しています
	   4. で倉庫dbはNULLにしてあるので実質何もしないことになります

	※ storage_clear_cache() はcharサーバだけが停止して socket.c のデストラクタから chrif_disconnect() が呼ばれた
	   ときに意味を持ちます
	   numdb_final() / numdb_init() を使わずに numdb_clear() だけで済むようになります
	   また上記の 6. で numdb_init() されると後始末処理をさらに入れる必要が出てくるから、という理由もあります

	-> flush_fifo() 追加、from eAthena（socket.*）
	-> chrif_disconnect() 修正（chrif.c）
	-> chrif_disconnect_sub() をグローバルに変更（chrif.h）
	-> guild_flush_expcache() 追加（guild.*）
	-> do_final() 修正（map.c）
	-> storage_clear_cache() 追加（storage.*）
	-> do_final_storage() 修正（storage.c）

・スクリプトにOnFinalラベルを追加
	MAPサーバ停止直前に実行されます。OnInitラベルなどと同様の使い方です。
	キャラのデータへアクセスしたり変数を書き換えたりなど、全ての処理が通常通り作動することを保証します。
	ただしsleepやNPCタイマーなどで遅延処理させることはできません。
	例えば以下のような使い方が想定されます。

	// 他の全MAPサーバへアナウンスする
	izlude.gat,130,115,4	script	Announcer	113,{
		end;
	OnFinal:
		announce "マップサーバ01が停止しました",0;
		end;
	}

----------------------------------------
//097 [2007/02/27] by Rayce

・atcommand.cを全体的に修正（atcommand.c）
・古いPACKETVERでもコンパイルできるように修正（clif.c）

・以下の項目でアイテムを削除するとき、ペットの卵のデータが削除されずセーブデータにゴミが残り続ける問題を修正
	@itemreset
	@charitemreset
	extra system
	clearitem命令
	pc_checkitem()

----------------------------------------
//096 [2007/02/26] by Rayce

・ギルド名およびパーティ名の検索をcase-sensitiveに修正（int_guild.c, int_party.c, guild.c, party.c）
	本鯖の仕様に従って半角英字は大文字/小文字が区別されるようになります。
	ついでに guild_searchname(), party_searchname() を最適化。

・SQL: アカウントIDの検索をcase-sensitiveに修正（login.c）
・SQL: キャラ名の検索をcase-sensitiveに修正（char.c）

----------------------------------------
//095 [2007/02/26] by Rayce

・ワープポータルがSP消費なしになっていたバグを修正、thanks to hugeさん（skill.c）
・ホールドウェブの効果が切れるときエフェクトが消滅するように修正（skill.c, status.*）
	パケットキャプチャにより SI_HOLDWEB が判明
	アスムなどと同じく clif_skill_nodamage() の前に0x196を送る必要があります

・ターゲット自動選択型のスキル（コンボ系スキルや飛び蹴り等）が距離を無視して発動できていたバグを修正（unit.c）
	ターゲットを補正するタイミングを変更しています。
	また unit_skilluse_id2() の処理内での処理の順番を少し修正しています。

----------------------------------------
//094 [2007/02/26] by Rayce

・新規作成キャラの##変数にデータがコピーされず、全ての##変数をクリアしてしまうバグを修正（char.c）
	get_account_reg2() 追加

----------------------------------------
//093 [2007/02/25] by Rayce

・パケット0xf4の上位版0x1c4を追加（clif.c）
	ペットの装備品やIDが13000以上のアイテムを倉庫に預けると、即座に装備欄に表示されなかった
	問題が修正されます。
	恐らく本鯖はかなり昔に上位版に移行していたと考えられますので、PACKETVERが7以上のときに
	0x1c4をサポートするようにしています。

・gccでコンパイル時にpc.cで警告が出るので修正（pc.c）
・doc/client_packet.txt更新

----------------------------------------
//092 [2007/02/25] by Rayce

・アイテムトグルが固定化されるように修正
	取得したアイテムはインベントリの最後尾に格納される必要がありますが、現在の仕様では配列内で空いている場所
	に格納されるようになっています。
	従って clif_parse_LoadEndAck() でアイテムリストを再送信したときに以前と並びが異なるアイテムリストが
	クライアントに渡されてしまい、トグルが固定化されない原因となっていました。
	そこでアイテムを取得した順に番号を付け、pc_checkitem() でこの番号順にソートするように変更しました。
	item構造体のidメンバがほとんど使われてなかったので、この番号を保存する変数として利用しています。
	pc_checkitem() で行っていたアイテムの空き詰め処理の代わりにqsortを行う形になっていますが、インベントリに
	関してはソート後にアイテムデータベースへのポインタを再設定しないといけないので、以前に比べて若干処理は
	増えていることになります。

	-> item構造体の id メンバを unsigned int型に変更
	-> map_session_data構造体内、state構造体に inventory_dirty, cart_dirty 追加
	   （qsortすべきかどうかを判定するフラグ）
	-> map_session_data構造体に inventory_sortkey, cart_sortkey 追加
	-> pc_setinventorydata() の処理を pc_checkitem() 内に吸収

・倉庫内アイテムの並び換えを修正および拡張
	上記のアイテムトグルと同様に倉庫内アイテムについても格納順に並ぶようにソートするように修正しました。
	battle_athena.confでソート方法を選択することができます。
	ただし今までの storagesort_by_itemid は削除されて personal_storage_sort, guild_storage_sort という項目に
	変更されているので注意してください。

	0のときはソートしません。速度重視。
	1のときはitem構造体のidを使って格納順にソートします。本鯖準拠。
	2のときはアイテムIDでソートします。091以前のバージョンの方法です。
	3のときは種類でソートします。まずtypeでソートし、次に武器・防具ならLoc（装備箇所）でソートし、
	最後にアイテムIDでソートします。これにより同じタイプのアイテムが近くに集まるようになります。

	-> storage構造体、guild_storage構造体に sortkey 追加
	-> storage_comp_item_by_key(), storage_comp_item_by_nameid(), storage_comp_item_by_type() 追加
	-> sortage_gsortitem() を削除し storage_sortitem() で一括処理できるように変更

・SQL: sql-filesにAuriga092_changetable.sql追加、main.sql更新
       `id` フィールドの使い方が変更されているので注意してください
・SQL: item構造体のidメンバが正しくコンバートされるように修正（char-converter.c）

----------------------------------------
//091 [2007/02/23] by Rayce

・login鯖で0x2712を受け取ったとき、auth_fifoに該当データが見つからなかった場合に
　バッファオーバーフローが生じるバグを修正
　ついでに見つからなかったときは "auth_fifo search error!" が出力されるように（login.c）

・サイズの種類を MAX_SIZE_FIX として定義（map.h, status.c）
	デフォルトでは3です。
	値を増やすことにより小/中/大以外のサイズを定義することが可能です。
	その場合はdb/size_fix.txtで新しく行を追記してください。

----------------------------------------
//090 [2007/02/21] by Rayce

・属性Lvの最大値を MAX_ELE_LEVEL として定義、デフォルトは4（map.h）
・attr_fix_tableの実体をbattle.cからpc.cへ移動（battle.*, pc.*）
・attr_fix_tableに ELE_MAX を使うように修正
	MAX_ELE_LEVEL を増やせば属性Lvが5以上を定義することができます。
	属性は20種類までしか指定できませんが、属性Lvは無制限です。
	属性を拡張する場合はdb/attr_fix_table.txtでテーブルを適切に設定してください。

・076以降ハンマーフォールでスタンが発生しなくなっていた問題を修正（db/skill_cast_db.txt）
・あまり意味がないので BASE_TICK, LIFETIME_FLOORITEM を削除（timer.h, map.h）
・088で混入したゴミコードを除去（skill.c）

----------------------------------------
//089 [2007/02/19] by Rayce

・死亡カウンタをキャラ永続変数ではなくmmo_charstatus構造体としてセーブするように変更 from Freya
　（char.c, mmo.h, map.h, pc.c, status.c）
	死亡カウンタは全職で利用される上、比較的頻繁に更新されるデータなので
	キャラデータの一つとしてまとめることにしました。
	キャラ永続変数は先頭から線形検索するため、PC_DIE_COUNTERが後方に登録されていた場合は
	速度的に不利になるという問題があったためです。

	PC_DIE_COUNTERはdb/const.txtから削除されています。
	死亡カウンタは今後は単なるパラメータとして扱われるので、スクリプトからはDieCounterという
	名前でアクセスしてください。

	セーブデータが変更されているので特にTXTの場合は注意してください。
	PC_DIE_COUNTERの値はセーブデータに変換されないので、各自で移行してください。
	TXTならmannerの次の項、SQLならcharテーブルに追加されたdie_counterです。
	移行完了したらPC_DIE_COUNTERは削除しておくと良いかもしれません。

　※以下のスクリプトを使って各プレイヤーにデータをコンバートさせることも可能です。
　　ただしbattle_athena.confでOnPCLoginラベルが利用できるように設定しておく必要があります。

	-	script	Conv_DieCounter	-1,{
	OnPCLogin:
		if(PC_DIE_COUNTER) {
			set DieCounter,PC_DIE_COUNTER;
			set PC_DIE_COUNTER,0;
		}
		end;
	}

・db/const.txtに記載されているパラメータの内、updatestatus出来ないものの値を変更しようとすると
　警告メッセージが出るのを抑制（pc.c）
	例えば「set Class,0;」を実行すると clif_updatestatus() でエラー扱いになっていました。
	今後はエラーが出なくなりますが、あくまで警告抑制であって実質何もしないコードになります。
・細かい修正（status.c）

・TXT: JOURNAL_IDENTIFIERをバージョン02に変更しておく（journal.c）
・SQL: main.sql更新、Auriga089_changetable.sql追加
・SQL: converter.exe対応、ただし089より古いバージョンは読み込み非対応なので
       必ず一度089以降のTXTモードでデータをセーブしてからコンバートしてください
・SQL: login-converter.cの細かい修正

----------------------------------------
//088 [2007/02/18] by Rayce

・@allskillの修正（atcommand.c, pc,*）
	-> battle_athena.confのplayer_skillup_limitがyesのとき全てのスキルが表示されなかった問題を解消
	-> 引数を一つ取れるように拡張
	   「@allskill 1」とするとbattle_athena.confのquest_skill_learnの設定に関わらず
	   クエストスキルも取得できるようになります

・クローンスキル関連の細かい修正（atcommand.c, skill.c）
・DEBUG_MEMMGRがオンのとき、メモリ消費削減のためタイムスタンプを最適化（malloc.c）

----------------------------------------
//087 [2007/02/17] by Rayce

・MakefileのPACKETVERが 8 になっていなかったのを修正
・script.cの DEBUG_VARS の定義をコンパイルオプションにする
	Makefile, bcc32_make.bat, vc_make.bat参照
・AthenaProjectからのmerge漏れを補完
	-> vc_make.batにCPU最適化スイッチ NOOPTIMIZE を追加
	-> doc/server_build.txt追加、内容を少し加筆および修正
・item_db.txtにtypoがあったので更新, thanks to huge cgi

----------------------------------------
//086 [2007/02/16] by Rayce

・ギルドメンバーの一覧でガンスリンガーと忍者が1_ETCと表示される問題を修正（clif.c）
・DYNAMIC_SC_DATAがオンのとき、ストームガストの凍結挙動がおかしかったバグを修正（skill.c, status.c）

・緊急回避とディフェンスの後にbreakが多分抜けていたので修正（skill.c）
・skill_castend_nodamage_id() を少し修正
・使われていない定数 CLASSCHANGE_BOSS_NUM を削除（mob.c）
・mobdb_searchname() でmemcmpしないように変更（mob.c）
・mob.cを少し整理
・doc/client_packet.txt更新

----------------------------------------
//085 [2007/02/16] by Rayce

・キャラ名を赤文字にするパケット0x220が見つかったので実装（battle.*, clif.*, status.c）
	-> clif_send_murderer() 追加
	-> battle_athena.confでマーダラーに必要なキラーポイントを設定できるように拡張
	   デフォルトは100で、この値以上になるとマーダラーとなり文字が赤くなります
	-> マーダラーシステム（ステータスボーナスなど）を無効にしたい場合には、
	   pk_murderer_pointの値を0に設定してください
	   また、PKモードを全く利用しない場合は0にしておくと良いかもしれません
	-> ステータスボーナスがAll+5になるのはキラーポイントがpk_murderer_pointの4倍以上のときです
	   個別設定できないので注意してください

・ログアウトするときはテレポートのようなエフェクト（clrtype=2）が出るように修正（clif.c, map.c）
・doc/client_packet.txt更新

----------------------------------------
//084 [2007/02/15] by Rayce

・サーバースナップショット（version.h）
・不要なファイルを削除
　　doc/
	mysql.txt
　　sql-files/
	****_changetable.sql
　　script/sample/
	npc_custom_extendshop.txt
	npc_debug_questskill2.txt
	npc_debug_sample.txt
	npc_test_arena.txt
	npc_test_bank.txt
	npc_test_skill.txt
・ファイルの改行コードをCR/LFに統一（29files）
　ただしUNIX環境用のものはLFにしています

----------------------------------------
//083 [2007/02/14] by Rayce

・treedbの全要素を削除する db_clear() を追加（db.*）
	今までは全要素を削除したい場合以下の2通りの方法がありましたが、いずれの方法も無駄な処理が発生します。
	　１．db_foreach() 内で 一つずつ db_erase()
	　２．db_final() したあと再度 db_init()
	db_clear() の利用法は基本的に db_final() とほぼ同じです。
	ただしfree_listとtableは解放しないので再利用が効率的に行えます。
	また巡回は db_foreach() の処理を用いているので db_final() よりも若干高速に作動します。

・以下の関数において numdb_clear() を使うように最適化
	guild_payexp_timer_sub()
	pc_read_gm_account()
	parse_script()

・script_csvreload_sub() でファイル名を検索する際、見つかったらそこで検索終了するように修正（script.c）
・doc/client_packet.txtにパケット0x12bの情報を追加 from eA
　ただし現状では無くても問題なさそうなので使っていません

----------------------------------------
//082 [2007/02/14] by Rayce

・AthenaProject2274よりmerge, thanks to Blazeさん
　以下Readmeより転載
	・飛行船クエスト第2部実装
	・スロットエンチャント実装
	・新春イベント2007年版実装
	・クリスマスイベント2006年版実装
	・2次職クエストスキル習得クエスト一部実装
	・アマツ属性石交換修正
	・アマツ通行手形クエスト修正
	・アマツモモタロ体験クエスト修正
	・ジュノー錬金術修正
	・リヒタルゼン友情クエスト修正
	・ナイト転職クエスト修正
	・ブラックスミス転職クエスト修正
	・ハンター転職クエスト修正
	・アルケミスト転職クエスト修正
	・衝突している変数名を一部変更
	・全ての街スクリプトの手直し
	・jawaiiのモンスターをnpc_monster.txtに移動

----------------------------------------
//081 [2007/02/14] by Rayce

・script/sample内のスクリプトの改修
　推奨される記述を浸透させるためサンプルも書き換えることに決めました
	npc_custom_branch.txt
	npc_custom_cardremover.txt
	npc_custom_gldcheck.txt
	npc_custom_jobchange.txt
	npc_custom_produce.txt
	npc_debug_arrow.txt
	npc_debug_convertvar.txt
	npc_debug_pota.txt
	npc_debug_questskill2.txt
	npc_debug_reset.txt
	npc_debug_revive.txt
	npc_test_bank.txt
	npc_test_chat.txt
	npc_test_chkoption.txt
	npc_test_func.txt
	npc_test_getequip.txt
	npc_test_gettime.txt
	npc_test_gstorage.txt
	npc_test_npctimer.txt

・以下のスクリプトは削除
	npc_custom_extendshop.txt（npc_debug_shop.txtと同じため）
	npc_test_arena.txt（イベントでタイマーを使う場合はNPCタイマーを推奨しているため）
	npc_test_skill.txt（npc_debug_questskill.txtと同じため）

・npc_test_bank.txtをnpc_custom_bank.txtに改名
・npc_debug_questskill2.txtをnpc_debug_questskill.txtに改名
・npc_debug_sample.txtは削除、一部の解説はdoc/script_ref.txtに補完

・getitem2命令を使っているスクリプトを少し修正
	npc_event_xmas.txt
	npc_quest_hat3.txt
	npc_quest_hat4.txt

----------------------------------------
//080 [2007/02/13] by Rayce

・itemdb.cの整理
	-> random_item_data構造体を変更
	-> 新しくMAX_RANDTYPEを定義、ランダム系アイテムの種類を示す
	-> ランダム系アイテムの読み込みおよび検索の処理を最適化
	-> デバッグコードを itemdb_debug_txt() に改名して整理し直し
	-> アイテム名でデータベースを検索する際、見つかった時点で検索終了にする
	   また余計な処理を省くためmemcmpは行わないようにする

　※新しくランダム系アイテムを増やしたい場合は、MAX_RANDTYPEの値を増やし
　　itemdb_read_randomitem() 内でfilenameを追加するだけでよくなりました

・MOBがランダム系アイテムをドロップする場合、該当アイテムIDが取得できなかったときに
　IDが0のアイテムをドロップしてしまう問題を修正（mob.c）

・successremovecards命令およびfailedremovecards命令の修正（script.c）
	-> エフェクトが出るように修正
	   clif_misceffect() だと「精錬成功/失敗しました」のメッセージが出力されてしまうので
	   clif_misceffect2() を使っています
	-> failedremovecards命令でfailtypeが3のときは失敗エフェクトを出すだけで何もしないように修正
	-> successremovecards命令は武具とカードを返却して成功エフェクトを出す必要があるので
	   removecards_sub() ではfailtype = 4として処理します

・ランダム系アイテムdbにおいて、デフォルト設定のアイテムの確率が間違っているものを修正
	db/item_bluebox.txt
	db/item_cardalbum.txt
	db/item_violetbox.txt
・鉱石発見dbのデフォルトアイテムのIDが間違っていたので修正
	db/item_findingore.txt

----------------------------------------
//079 [2007/02/12] by Rayce

・hugeさん作成のdebugパッチを部分的にmerge, thx a lot!!
	-> clif_parse_CloseKafra() を少し修正（clif.c）
	-> MobがドロップするアイテムIDが負のとき、箱系ランダムアイテムにならなかった問題を修正（mob.c）
	-> スティールの確率補正を少し修正（pc.c）
	-> 暖かい風の発動元の引数を少し変更（skill.c）
	-> 移動不可モードなMobをペットにした場合でも移動できるように改善（unit.c）

・一部の rand() を atn_rand() に変更（login.c, clif.c, party.c, pet.c）
・doc/packet_db.txtに解析できた範囲での情報を追記

----------------------------------------
//078 [2007/02/12] by Rayce

・map_athena.confにベインズ系のMAPを追加
・2007-02-05aSakexeを解析したパケット長を追加（db/packet_db.txt）
・db群の更新 thanks to huge cgi

----------------------------------------
//077 [2007/02/11] by Rayce

・AthenaProject2272, 2273とhugeさんの作成されたdebugパッチをベースにmerge
　thanks to KIAさん、Mizukiさん、hugeさん

　　・2006-10-23aSakexe以降のキャラセレパケットに対応（char.c）
　　　PACKERVERが8になっているので、これより古いクライアントの場合は7に変更してください
　　・2007-01-08aSakexeのパケットに対応（db/packet_db.txt）
　　・doc/client_packet.txt更新

----------------------------------------
//076 [2007/02/11] by Rayce

・AthenaProject2271よりmerge, thanks to 名無し＠さん

　　・スタン状態の時間が異常に長いスキルを修正(db/skill_cast_db.txt)
　　・スキルユニットを本鯖に合わせて修正(db/skill_unit_db.txt)
　　	マグヌスエクソシズムを重ね置き禁止
　　・以前追加した遠距離フラグの修正と本鯖に合わせた修正(src/map/battle.c)
　　・サプライズアタックのスタン時間だけ強制3秒になるように修正(src/map/skill.c)
　　	暗闇の時間だけをskill_cast_db.txtから読み込みます
　　・シールドチェインのヒット補正修正
　　・トリプルアクション、トラッキングのダメージ倍率修正
　　・トラッキングにヒット補正追加
　　・ブルズアイにカード補正が乗らないように修正

----------------------------------------
//075 [2007/02/11] by Rayce

・ギルドExpのキャッシュ guild_expcache_db をtreedbに戻す（guild.c）
・numdb_final() および strdb_final() を呼ぶ際、各ノードに対して実行すべき関数がない場合は
　引数にNULLを入れるだけにする
　（friend.c, map.c, npc.c, script.c）
・npc_buylist() および npc_selllist() で使っている itemdb_search() を itemdb_exists() に修正（npc.c）
・double型へキャストしている部分をatn_bignumber型に変更（script.c, status.c）
・script.cを少し整形

----------------------------------------
//074 [2007/02/11] by Rayce

・スクリプト命令のsetusescript, setequipscriptの廃止
	実行中のアイテムスクリプトから自身のスクリプトを変更するとサーバクラッシュしたり、
	sleepと相性が極めて悪いなどの不安定要素があるので思い切って削除することにします

・命令の後に引数が必要な場合、必ずスペースを入れることを強制する
	以下のようにスペースがないコードは今後エラーとして扱われます

	input(@val);
	mes@val;

----------------------------------------
//073 [2007/02/10] by Rayce

・PTのアイテム分配実装 from eA（int_party.c, clif.c, intif.*, party.*, pc.c）
	完全にランダムで取得者を選定します
・battle_athena.confにparty_item_share_type, party_item_share_showを追加（battle.*）
・パーティ設定を変更するコマンド@partyoption追加（atcommand.*）
	通常クライアントからは変更できないアイテム収集方式・分配に関する設定を
	変更するためのコマンドで、PTリーダーのみ効果があります

・あまり意味がないので MIN_ATTRIBUTE, MAX_ATTRIBUTE, ATTRIBUTE_NORMAL, MIN_STAR, MAX_STAR
　のdefineを削除（mmo.h, atcommand.c）

----------------------------------------
//072 [2007/02/09] by Rayce

・PC型Mobが死亡して消滅するときの挙動をbattle_athena.confで決定できるように追加（battle.*, clif.*, unit.c）
	デフォルトは1で、従来通りの方法です。
	しかし1の場合、消滅するまでの間に画面外に移動するとMobの残像が残り続けてしまいます。
	0に設定することでこの問題は解消されますが、ALL_SAMEMAPでパケットを送り付けるので
	関係の無い人にまでパケットを送られることになります。
	2は最も無駄がない設定ですが、Mobがすぐに消滅してしまいます。
	環境に合わせて好きな設定を選択してください。

・パーティメイン情報パケット0x1e9追加 from eA（clif.*, party.c）
	clif_party_option() にはアイテム分配に関する情報は含まれていませんでした。
	クライアントは経験値分配フラグをDWORDで読み取るようです。
	アイテム分配フラグは clif_party_main_info() が受け持ちます。

・課金アイテム販売リスト用のパケット0x287を用意（clif.*）
　ただし動作未確認
	clif_pointshop_list() 追加

・恐らくAthena2240以降、服色を0に変更すると見た目がノービスになる問題を修正（pc.c）
・重量50/90%オーバーは死亡時に解除されないようにdb/scdata_db.txtを修正
・doc/client_packet.txt更新

----------------------------------------
//071 [2007/02/07] by Rayce

・パーティのアイテム分配フラグをinterサーバに渡すための修正
　clif_parse_CreateParty2() でitem, item2の読み取りを有効化
　（int_party.c, inter.c, atcommand.c, intif.*, party.*）
・clif.cの細かい修正

・getelementofarray関数の一次元目の配列において、参照する要素が中途半端な相対位置になっていたので
　絶対位置を参照するように修正（script.c）

　※以下のコードは今までは4が返ってきましたが、2が返るようになります

	function Test {
		mes getelementofarray(getarg(0),1);
		return;
	}
	setarray '@data,1,2,3,4,5,6,7;
	Test '@data[2];
	close;

----------------------------------------
//070 [2007/02/01] by Rayce

・スクリプトの DEBUG_DISASM および DEBUG_RUN で出力される書式を少し修正（script.c）
・使われていない関数 mob_change_summon_monster_data() を削除（mob.*）
・VC++で警告レベルを /W4 にした際に得られた結果の中で気になった箇所を修正
　（char.c, int_guild.c, int_party.c, login.c, mob.c, npc.c）
・関数内で参照されない不要な引数を削除
	clif_quitsave()
	clif_refine()
	clif_devotion()
	clif_guild_explusion()
	clif_guild_message()
	clif_onlymessage()
	intif_announce()
	skill_devotion()

----------------------------------------
//069 [2007/01/30] by Rayce

・scriptに関して全体的な細かい修正（script.c）
	-> infinity loopになったとき、gotocountとcmdcountのどちらが原因かわかるように表示する
	-> 引数として変数が必要な命令/関数で、C_NAMEかどうか必ずチェックするように強化
	　 他の変数を参照したり最悪の場合サーバクラッシュするのを防ぐために、C_NAMEのチェック後に変数名を取得する
	-> 配列の上限128を越えてデータを格納しないようにチェック強化
	-> input命令、divorce関数は引数省略不可に変更
	-> deletearray命令の第二引数を省略不可に変更
	-> getcharname関数の省略可能な第二引数は意味がないので削除
	-> delitem命令でペットの卵を複数個削除すると、ペット情報が1個しか削除されずセーブデータに
	　 ゴミが残り続ける問題を修正
	-> delitem命令の処理を改善
	-> guildskill命令で第三引数を省略したときは、skill命令と同じく値に1を入れるように変更
	-> gettimestr関数でmaxlenの値が小さすぎた場合は警告文を出力するように強化
	-> getequipcardcnt関数、successremovecards命令、failedremovecards命令、checkequipedcard関数で
	　 名前入り装備品もカードとしてみなされる可能性を修正
	-> recovery命令を実行したときにPCにメッセージを表示しないように変更
	-> getpetinfo関数、gethomuninfo関数において名前を返すタイプのもので取得失敗したときは
	　 0ではなく "" （空文字）を返すように変更
	-> checkequipedcard関数がカート内のアイテムを検索しないように変更

・イベントタイマーの残り時間を返すgettimerdiff関数を追加（pc.*, script.c）
・文字列長を返すgetstrlen関数を追加
・strcutを廃止して、より柔軟に文字列を取得できるsubstr関数を追加

・strcut関数を利用していたNPCスクリプトを全てsubstr関数に書き換え
　特にnpc_test_library.txtは根本的に書き直し
	script/npc/event/npc_event_xmas.txt
	script/npc/misc/npc_misc_guide.txt
	script/sample/npc_test_library.txt
	script/sample/npc_test_pcevent.txt

----------------------------------------
//068 [2007/01/29] by Rayce

・return命令で文字列型の '@変数 を返すときダングリングポインタになるバグを修正（script.c）
	return命令が終わった時点で '@変数 は全て解放されてしまうため、文字列型の場合は
	get_val() を実行しただけでは完全な値渡しになりません。
	文字列のコピーを渡す必要があります。

・ステータス異常をセーブデータからロードする際、効果時間が0以下の場合は status_change_start() を
　実行しないように修正（intif.c）
・@npctalkやglobalmes命令でNPCに発言させるとき、NPC名に含まれる#以下の文字列は表示しないように修正（npc.c）

----------------------------------------
//067 [2007/01/26] by Rayce

・共闘をbl.idではなくchar_idで管理するように修正（battle.c, mob.c）
	PCの場合はキャラIDをそのまま使います。
	ホムの場合はブロックIDを負に反転させて使います。
	苦肉の策であることに変わりありませんが、一応PCとホムの区別は出来ています。

----------------------------------------
//066 [2007/01/25] by Rayce

・aStrdupをキャストするように修正（script.c）
・map.dspを少し修正、map_sql.dsp追加

・SQL: マップ永続変数のconvert対応（converter.*, map-converter.*）
	converter_athena.confに map_server_tag を設定する項目を追加しているので、
	複数のデータがある場合にはタグ名を変更して読み込ませてください。
・SQL: 049の最適化が不完全だった部分を修正および巻き戻し等（char.c, inter.c）

----------------------------------------
//065 [2007/01/25] by Rayce

・MAPサーバからSQLを発行できるように追加（map.c）
	map.cでSQLサーバの設定読み込み/connect/closeを行います。
	map_athena.confにMySQL用の設定項目を追加していますので、SQLユーザは自身の環境に合わせて適宜変更してください。

	do_init_map() 追加
	do_final_map() 追加
	map_config_read_sub() 追加

・マップ永続変数をSQLへセーブできるように追加（map.*, script.c）
	`mapreg` テーブルに保存されます。
	`server_tag` フィールドはMAPサーバのタグ名で、map_athena.confの map_server_tag で設定します。
	マップ永続変数は他のマップサーバと干渉しない独立な変数であるため、SQL内で一括管理するために
	このタグ名を使ってサーバを識別します。
	サーバ分割する場合はタグ名を全てのマップサーバで別々のものに設定してください。
	同一に設定することも可能ですが、変数の値が正しく得られる保証がないので推奨されません。
	詳細はdoc/conf_ref.txtおよびdoc/distribute_servers.txtを参照してください。

　※これでようやくsaveフォルダ内の全てのファイルをSQLに移行できました。
　　txt-converter.exeは次回対応予定です。

・マップ永続変数が変更されたときだけmapreg_dirtyを1にするように最適化（script.c）
	セーブの必要がないマップ一時変数が変更されたときもmapreg_dirtyが1になっていたため、
	自動セーブのタイミングで無駄にセーブ処理が行われていました。
	mapreg_setreg(), mapreg_setregstr() に引数を一つ増やし、マップ永続変数であるかどうかを判定しています。

・map.cから read_grf_files_txt が完全に削除されてなかったので修正（map.c）
・064のskill.cで警告が出ていたので修正（skill.c）

----------------------------------------
//064 [2007/01/24] by Rayce

・特定条件でステータス異常が解除可能かどうか、また特定条件下でステータス異常開始を無効にするか、を
　db/scdata_db.txtで設定できるように拡張（battle.c, pc.c, skill.c, status.*）
	詳細はdoc/db_ref.txtを参照。
	基本的には今までソースコードに記述されていた部分をtxtに追い出しただけです。
	設定はあくまでも適当暫定なので修正できる方に任せます。

　※死亡時は落法、PKペナルティ、赤エモだけ解除されません。
　　ディスペルは一部wikiを参考にして解除可否を修正しています。
　　ゴスペルの全状態異常解除はeAを参考に設定しました。

	scdata_db構造体にメンバ releasable, disable を追加
	status_is_disable() 追加
	status_change_release() 追加
	status_change_end_by_jumpkick() 削除
	status_support_magic_skill_end() 削除

・battle_athena.confの cancel_race は不要になったので削除（battle.*, skill.c）

----------------------------------------
//063 [2007/01/22] by Rayce

・ランキングの処理方法を修正
	各ランキングのデータはcharサーバで管理するように修正。
	これによりキャラがログインするまでランキングに登録されない問題や、サーバ分割をしている状況でサーバ移動
	するとランキングが変動する問題などが解決されます。

	追加
		char_build_ranking()
		char_set_ranking_send()
		char_ranking_update()
		char_ranking_delete()
		chrif_ranking_request()
		chrif_ranking_update()
		chrif_ranking_recv()
		ranking_set_data()
		パケット 0x2b2e, 0x2b2f, 0x2b30
	移動
		MAX_RANKING, MAX_RANKER の定義をmmo.hへ
		struct Ranking_Data の宣言をmmo.hへ
		compare_ranking_data() をchar.cへ
	削除
		ranking_sort()
		ranking_update_all()
		ranking_init_data()

　　※charサーバ起動時に char_build_ranking() を実行し、ランキングデータを作成します。
　　　TXTの場合はchar_datを全走査しながらキャラ永続変数を参照するので、かなり頭の悪い方法になっています。
　　　SQLの場合は ORDER BY でソートしたデータを取得できるので一見簡潔に見えますが、`value` には
　　　KEYが設定されていないため結局は Using filesort となりパフォーマンスが低下する可能性があります。

　　※mapサーバがcharサーバに接続完了した時点でcharサーバにランキングデータを要求します。
　　　そのため OnCharIfInit, OnInterIfInit でランキングに関するデータを操作することはできません。
　　　sleepなどを使ってウェイトを置く必要があります。

　　※mapサーバが持っているランキングデータはmapサーバ内の処理で直接変更されることはありません。
　　　データの参照や、データを更新する必要があるかどうかの判定に利用するだけです。
　　　元となるデータはcharサーバにあり、更新処理もcharサーバで行います。
　　　データが更新されたときにはそのデータを全サーバにフラッシュします。

　　※サーバ分割をしている場合、複数のmapサーバから同時にデータが更新される可能性がありますが、考慮した
　　　つもりなので問題ないと思います。

　　※キャラクター削除した場合、もしランカーであればデータの削除を行います。
　　　ただしデータの再構築はしないので、10位にUnknownというキャラ名が0ポイントでランクされる状態になります。
　　　これは仕様ということにしておきます。

　　※ランキングデータはMAX_RANKER（デフォルトは10）位までしか保持していません。
　　　従ってランカーのポイントが減少し11位以下になるような場合であっても10位のままです。
　　　PKランキングは減少する機会が有り得ますが、現状ではこれを仕様としておきます。

　　※ランキングデータへの登録は職業を考慮しません。
　　　例えば職業がBSであっても PC_ALCHEMIST_POINT さえ持っていればアルケミストランキングに掲載されます。
　　　これを回避したいのであれば、転職を行うスクリプトでランキング変数を0にする処理を入れてください。

　　※いくつかの問題点はFreya方式（mmo_charstatusにfame_pointを用意する）を採用すると改善される可能性があります。
　　　しかし一長一短なので、現状はこのままキャラ永続変数を利用する方式です。

・MAX_RANKERが10より小さいとき、ランキングを参照するとバッファオーバーフローが起こる問題を修正（ranking.c）
	ranking_clif_display() 修正

・SQL: `global_reg_value` テーブルの `value` フィールドが文字列型なっていたのでint型に修正
       sql-files/Auriga063_changetable.sql追加
・SQL: 054で不要なフィールドを削除した影響のため、account.txtデータのconvert時にサーバクラッシュした問題を修正
       login-converter.cから既に削除されたフィールドを参照しないように変更、およびクラッシュ対策

----------------------------------------
//062 [2007/01/20] by Rayce

・057でcase構文を変更して以後、const.txtに記載されている定数をcaseラベルに指定できなくなった問題を修正（script.c）
　以下の例は正常なコードとして扱われます。
	thanks for indication and fix, Skotlex in eAthena

	switch(Class) {
		case Job_Knight: ...
		case Job_Monk: ...
	}

----------------------------------------
//061 [2007/01/19] by Rayce

・種族を示す定数を RCT_*** として定義（map.h）
　種極に関連する値を気付いた範囲で置き換え
	eAと同じく RC_*** にしても良かったんですが、ユニークなものにし易いよう3文字（RaCeType）にしました。
	また人間は DEMIHUMAN ではなく単に HUMAN にしています。
・bWeaponAtk, bWeaponAtkRateに銃、手裏剣、両手武器が指定できるように拡張（map.h, pc.h）
　元々は指貫用として実装されてたみたいだけど使われてない？
　WT_*** のenumをpc.hからmap.hへ移動

・battle_calc_magic_attack() と battle_calc_misc_attack() を battle_calc_weapon_attack() と同様の書式に統一（battle.c）
	Damage構造体のポインタ *md は mob_data と混同しやすいので別の名前に変更しています

・doc/item_bonus.txtに bCriticalRaceRate の説明が欠けてたので追記
・ガンスリンガーと忍者のスキル名をjROの呼び名に統一

・HOM_SKILLID と HM_SKILLBASE は同じなので、全て HOM_SKILLID に統一して HM_SKILLBASE を削除（skill.c, skill.h）
・int_guild.cが GD_SKILLBASE を参照するために skill.h をincludeするという悲惨な状態だったので
　mmo.hに GUILD_SKILLID を定義、さらにギルドスキルのenumはmmo.hに移動
　（mmo.h, int_guild.c, clif.c, guild.c, skill.c, skill.h）
	guild_checkskill() でギルド拡張以外のギルドスキルも参照できる可能性を作るための処置です

----------------------------------------
//060 [2007/01/18] by Rayce

・mmo_auth() で認証OKだった場合は100ではなく-1を返すように変更（login.c）
	ログイン時のエラーメッセージ0x6aを詳細に調べた結果、100もエラー番号の一部として使われていました。
	混乱を避けるため、OKだった場合はeAやFreyaと同様に-1を返します。

・パケット0x1dd, 0x27c, 0x277のログインタイプの位置が間違っていたので修正（login.c）
　login_athena.confで "login_type" を指定していたのに正常にブロックできなかった不具合が解消されます
・doc/client_packet.txtに情報追記

----------------------------------------
//059 [2007/01/17] by Rayce

・マヤパープルカードの効果によるハイド見破りを本鯖仕様に修正（clif.c, pc.c, status.*）
　SI_TIGEREYE追加
	merged from eA, thanks to HelloKitty2

・status_check_attackable_by_tigereye() と status_check_tigereye() は本当に不要なので抹消

----------------------------------------
//058 [2007/01/16] by Rayce

・ギルド倉庫に関する処理の変更
　（int_storage.c, inter.c, atcommand.c, intif.*, map.h, script.c, storage.c）

　　ギルド倉庫はデュープの危険性を避けるために利用者は常に一人という制約があります。
　　しかしMAPサーバを分割している場合はこの制約が効かず、容易にデュープが可能となっていました。
　　そこでMAPサーバではなくInterサーバで排他制御を行うように変更しました。

　　1. inter_trylock_guild_storageを呼び出す
　　　　　　まず初めにInterサーバにロック権が取得できるか問い合わせます。
　　　　　　いきなりstorage_guild_storageopenを呼んではいけません！
　　2. sd->state.gstorage_lockreqに値を入れる
　　　　　　ロック要求中を示すフラグ。
　　　　　　1ならscriptのguildopenstorage経由、2ならatcommandの@gstorage経由。
　　3. mapif_parse_TrylockGuildStorageで処理する
　　　　　　誰も利用してなければロックをかけて成功フラグをMAPサーバに返す。
　　　　　　既にロック中ならば失敗フラグをMAPサーバに返す。
　　4. intif_parse_TrylockGuildStorageAckで確認
　　　　　　gstorage_lockreqの値で処理が異なります。
　　　　　　script経由なら成功/失敗フラグをnpc_menuに入れてスクリプトを再開します。
　　　　　　atcommand経由なら成功時のみ倉庫を開きます。

　　最初に必ずInterサーバに問い合わせる必要があるため、guildopenstorage関数の処理を変更しています。
　　この関数は呼び出されたらInterサーバにロック権の取得を要求し、一時停止します。
　　返答があったときにスクリプトは再開し、成功ならギルド倉庫が開かれます。
　　この一連の処理は自動的に行われるのでロックの取得/解放を明示する必要はありません。
　　（今まで通りの書き方で問題ないということです）

　　またギルド倉庫を閉じるときにinter_unlock_guild_storageを呼び出してロックの解放を行います。
　　lock/unlockが全て対応していると仮定しているのでデッドロックのチェック機構は今のところ実装されていません。

・カプラ倉庫を開くとき、既にカプラ倉庫を開いている状態なら開けないように修正（storage.c）
・057のスクリプトエンジンの修正に対して、case構文を少し最適化

----------------------------------------
//057 [2007/01/13] by Rayce

・スクリプトエンジンの構文関連についてチェック機能強化（script.c）

　　１．syntaxとして誤認されるバグを修正
　　　　strncmpだけで文字列のマッチングを行っていたのでユーザー定義関数が区別されない等の問題がありました。
　　　　以下の例文は今後正常なコードとして扱われます。
		function do_func {
			mes "string";
			return;
		}
		do_func;	// do構文として解釈しようとするのでエラーだった

　　２．default: の直後に命令が連結していると解析エラーとなるバグを修正
　　　　skip_word() が一つ多くdefaultの終了位置がおかしくなってました。
　　　　以下の例文は今後正常なコードとして扱われます。
		switch('@num) {
			default:mes "string";	// スペースを入れずいきなり命令があるとアウトだった
		}

　　３．break, continue の後は必ず ; を付けることを要求する
　　　　; のチェックが全くなかったので奇妙な記述が平然と許可されていました。
　　　　以下の例文は今後エラーとして扱われます。
		while('@num < 3) {
			if('@num == 1)
				continue%	// continueの後に何があってもOKだった
			set '@num,'@num+rand(4);
		}

　　４．caseラベルに指定できるのは数値型定数のみに規定
　　　　変数やラベルが指定出来るのは気持ち悪いのでC言語の形式に従います。
　　　　「'case' label not integer」の警告が出る場合はこのチェックに引っ掛かっています。
　　　　以下の例文は今後エラーとして扱われます。
		switch('@num) {
			case $@MapVal: mes "match"; break;	// 数値定数以外でも場合によってはOKだった
			default: mes "misimatch"; break;
		}

　　５．caseラベルに負の値を指定出来るように修正
　　　　'-' が skip_word() できないため上手く解釈できなかったのが原因でした。
　　　　以下の例文は今後正常なコードとして扱われます。
		switch(-rand(2)) {
			case  0: mes "zero"; break;
			case -1: mes "minus"; break;	// '-' の部分でエラーだった
		}

　　６．caseラベルが重複するときはエラーとなるように修正
　　　　syntax構造体内のcurly構造体に struct linkdb_node *case_label メンバを追加しました。
　　　　case構文がparseされたときはその値をリストに書き込み、同じ値があるかどうかチェックを行います。
　　　　switchが閉じたときにこのリストは解放されます。
	「dup 'case'」の警告が出る場合はこのチェックに引っ掛かっています。
　　　　以下の例文は今後エラーとして扱われます。
		switch('@num) {
			case 0: mes "first"; break;
			case 0: mes "second"; break;	// case 0 が重複していても警告されなかった
		}

・上記変更によってエラーが検出されるスクリプトの修正
	script/npc/job/npc_job_14crusader.txt

----------------------------------------
//056 [2007/01/11] by Rayce

・取引直後にサーバクラッシュすると稀にアイテムがデュープされる危険性を修正（trade.c）
	露店と同様に取引完了時には双方のプレイヤーのデータをセーブします

・AthenaProject2270-fixよりmerge, thanks to Cocoaさん
　以下Readmeをそのまま転載
	・ガンスリンガー、忍者のJob補正修正(db/job_db2.txt)
	・マグナムブレイクの表示ダメージが5分の1になっていたのを修正(skill_db.txt)
	・聖体降福の属性を聖属性に修正(skill_db.txt)
	・ハリネズミの針から岩石の矢が作成されなかったのを修正(create_arrow_db.txt)

----------------------------------------
//055 [2007/01/11] by Rayce

・ROメールシステムのバグ修正（int_mail.c, inter.c, clif.c, intif.*, mail.*）
　　-> clif_parse_SendMail() 内で送信処理が行われているのは良くないので、mail.cに移動
　　-> 本文に何も記入されてない状態で送信を試みると、それ以後メール送信が出来なくなる不具合を修正
　　　 　　失敗時には必ず返答パケット0x245を送らなければならないようです。
　　　 　　clif_res_sendmail() のflagに2を入れてやるとメッセージを出さずにこの問題を解決できる模様。

　　-> メール送信失敗時には必ず mail_removeitem() を呼ぶようにする
　　　 zenyもリセットされるように修正
　　　 　　アイテムを添付した状態で一度送信を試みて失敗し、次にアイテムは添付せずに正しく入力し直して
　　　 　　送信すると、失敗したときに置いたアイテムが勝手に添付される不具合が解消されます。

　　-> 受信者名の欄に存在しないキャラ名を指定してしまうと添付したアイテム/Zenyが消失する致命的なバグを修正
　　　 　　これはInter鯖から成功可否判定が返ってくる前にアイテム/Zenyを減らす処理を行っていたためでした。
　　　 　　安全性を確保するために処理の流れを変更しました。
　　　 　　キャラクターがそのMAP鯖に登録されてない場合は一旦Inter鯖にキャラクターの存在確認を要求し、
　　　 　　OKなら再度メールを送信する形式となります。
　　　 　　手抜きによりInter鯖から返ってきたキャラクター名はcharid_dbに登録されません！

　※変更後の処理の流れ
	1. clif_parse_SendMail
　　　  2. mail_checkmail (キャラが居れば7にジャンプ)
　　　  3. intif_mail_checkmail
　　　  4. mapif_parse_CheckMail
　　　  5. mapif_mail_checkok
　　　  6. intif_parse_MailCheckOK
　　　  7. mail_sendmail
　　　  8. mail_checkappend
　　　  9. intif_sendmail

・ROメール関連でInter鯖とMAP鯖間でやり取りするパケット番号を整理し直し（int_mail.c, intif.c）
　送信と受信がきちんと正しく対応するように変更、詳細は doc/inter_server_packet.txt
・mail_data構造体のメンバ receive_id は使われてないので削除（mmo.h）

・char鯖にキャラクター名の検索を要求したが見つからずに0x2b09が返ってくる場合、map_addchariddb() で
　charid_dbに登録しないように修正（map.c）

・SQL: char_sql_load() でキャラが見つからないときに「char - failed」が出力されないように修正（char.c）
　     例えば以下のようなスクリプトはエラーとして扱われるべきではないからです

		// ID 150000を持つキャラは既に削除されてると仮定
		set '@dummy$,getcharname(150000);
		if(sleep2(2000))
			mes getcharname(150000);	// Unknownが返る、このときfailedが出力されていた

----------------------------------------
//054 [2007/01/11] by Rayce

・オプション系の型をパケットの仕様に正しく合わせる
	option : short → unsigned int
	opt1   : short → unsigned short
	opt2   : short → unsigned short
	opt3   : short → unsigned int
・上記変更により浮遊とサンタ服が混ざる問題が解決したので、
　太陽と月と星の融合を使用時に浮遊するよう修正（status.c）
・オプション系についてhelp.txtに追記

・map_session_data構造体内のstate構造体のメンバ pass_through は使用されてないので削除（map.h）
・path_search_long_real() の引数がcell_t型になっていなかった部分を修正（mob.c）
・@charoptionも@optionと同様にopt3を指定できるように（atcommand.c）
・自動セーブ処理を少し最適化（pc.c）
・clif_changeoption() で使われていたループを展開（pc.c）
　clif_changelook() を少し修正

・SQL: charテーブルの `option` を unsigned int型に変更
・SQL: 使われていないフィールドを削除
・SQL: セキュリティ向上のため、標準で提供されるサーバアカウントを15個からTXTと同じ5個に変更
		Auriga054_changetable.sql追加、mail.sql更新

----------------------------------------
//053 [2007/01/10] by Rayce

・pc_makesavestatus() が二重に呼ばれていた無駄を修正（atcommand.c, homun.c, pc.c pet.c）
・ギルドメンバーの情報を参照しようとすると0x157のパケットが飛んで来るので、clif_parse_GuildMemberInfo()
　を追加、ただしパケットがダンプされるのを抑制するためだけであり、関数自体は何もしません（clif.c）

・map_athena.confに「autosave_gvg_rate」を追加（map.*, pc.c）
		merged from Freya, thx a lot!!
	GvG中に限り、自動セーブのインターバルを長く取ることでラグを緩和することを目的とします。
	デフォルトでは150（1.5倍）に設定されています。
	GvG中のラグが酷い場合には倍率を上げてみるといいかもしれません。
	尚、値は100以上しか設定できません（短くすることは不可）。

----------------------------------------
//052 [2007/01/09] by Rayce

・SQL: charasetにSJISを利用する環境下において、MySQL側のバグを回避できるようにスイッチを用意（utils.c）
	MySQLに付き纏う「文字コード問題」をAurigaサーバ側で補正するものです。
	SJISで0x5c（バックスラッシュ \）を含む2バイト文字があると、mysql_real_escape_string() によって
	\ が付加されますが、以下のような状況ではこの処理が災いしてクエリを発行できなくなります。

	例）'表'（0x955C）→　'表\'（0x955C5C）→ '?\'（0x955C）
		\\ が \ となり、続いて \' となるので、SQLの構文上 ' は文字列の一部として認識されます。
		そのため ' が閉じられてないと判定され、エラーとなります。

	これを強制的に解消するための暫定措置として、文字列の最後に「表・能・申」などの文字がある場合は
	mysql_real_escape_string() でサニタイズした後にさらに末端の余計なエスケープシーケンスを除去
	する機能を追加しました。

	utils.c の strecpy() にある #define TRIM_ESCAPE_AS_SJIS のコメントアウトを外してください。
	SJISの環境下において、上記の文字で終わるキャラクターやギルドが作成できなかったり、TXTセーブデータ
	からSQLへconvertできなかった問題を解決できるようになります。
	ただしMySQLがマルチバイト文字を正常に扱えるようになるまでの暫定処置です。
	（現在最新である 5.1.14 betaでも未解決でした・・・というか色々と迷走中？）
	また、あまり正しい方法ではないので何かしらの危険性を生み出す可能性を孕んでいます。
	SJIS以外の環境下ではこのスイッチを有効にしないで下さい。動作保証外です。

・SQL: save/account.txtからconvertする際、`loginlog` で警告が出るので修正（login-converter.c）
・doc/mysql.txtの内容をdoc/sqllogin.txtに吸収合併

----------------------------------------
//051 [2007/01/09] by Rayce

・converter_athena.conf, msg_athena.conf, script_athena.conf のimportをデフォルトでサポートする
　conf/importに対応するファイルを3つ追加

・TXT: ROメールのデータを読み込む際に、復帰コード \r が考慮されてなかったので修正（int_mail.c）
　     ついでにコメントを少し追加

・SQL: ROメールのセーブデータをTXTからSQLにconvert対応化（converter.*, inter-converter.c）
・SQL: save/castle.txtがconvert出来なかったので対応化（converter.*, char-converter.c）
・SQL: 048で同梱したsql-files/drop_table.sqlの書式が間違っていたので修正

----------------------------------------
//050 [2007/01/07] by Rayce

・utils.cを少し整理
・SQL: SQLで使う変数（mysql_handle, tmp_sql）と strecpy() を utils.c, utils.h にまとめる
       login鯖、char鯖、converterで必要となるので共通化しておくべきだと考えました

----------------------------------------
//049 [2007/01/06] by Rayce

・キャラ削除時に保存してあるROメールを削除するように修正（char.c, int_mail.*）
	mail_delete() 追加

・SQL: char_athena.confの start_weapon, start_armor が反映されてなかった問題を修正（char.c）
・SQL: status_sql_load() でステータス異常のデータをロードするとき、ゼロクリアやmysql_free_result()
       を呼び忘れてた箇所を修正（int_status.c）
・SQL: accreg_sql_save() において文字列エスケープ用のバッファサイズが小さかったので修正
       ついでに処理方法を少し改善（inter.c）
・SQL: converter_athena.confで account.txt と athena.txt を指定出来るように追加
       （char-converter.c, converter.*, login-converter.c）

・SQL: クエリ発行時にエラーが発生したとき、正しいテーブル名が出力されなかった問題を修正
・SQL: 「void*型から型変換する際にキャストを明示する」が抜けていた部分を修正

----------------------------------------
//048 [2007/01/05] by Rayce

・ROメールに関する変更および修正（mmo.h, inter.c, int_mail.c, clif.c, intif.c）
　　-> mail構造体のメンバ rates を unsigned int型に変更
　　-> mail_data構造体のメンバ mail_num を unsigned int型に変更
　　-> ROメールのデータ保存場所をinter_athena.confから設定出来るように追加
　　　 mail_txtにはメール全体のデータを保存するファイル名、mail_dirはメール本体のデータを格納する
　　　 ディレクトリを指定します
		mail_config_read_sub() 追加
　　-> メールの削除時にfreeし忘れる可能性を修正
		mail_txt_deletemail() 修正
　　-> メールを削除すると最後にあるデータが消去されずに残るバグを修正
		mail_txt_save_mail() 修正
　　-> 受信メールがBOXにある状態でキャラチェンジをすると、チェンジ後のキャラでもそのメールを閲覧
　　　 および添付アイテム/Zenyの取得が出来たバグを修正
		clif_send_mailbox()
		intif_parse_MailBoxLoad()

　※clif_send_mailbox() で mail_num に0を入れて送信すると画面がクリアできるようです
　　0だとエラーというコメントが気になりましたが、とりあえず問題なさそうなので0を許可しています

・ROメールの保存をSQLに対応（int_mail.*）
	`mail` にはメール全体の情報、`mail_data` には個人のメール本体の情報が格納されます
	残念ながら、文字化け対策のためメール本文（body）はTXTと同じくバイナリデータに変換されます

・mail_save_mail() の引数を一つ増やす
	この関数が呼ばれるのは、メール既読もしくは添付アイテム/Zenyの取得時にデータを書き換える時だけです
	SQLではTXTとは違い対象データをUPDATEするだけで済むので、mail_dataのindexを渡せるようにして
	無駄な処理を行わないようにしています
	TXTではこの引数は使われません

・SQL: sql-files/Auriga048_changetable.sqlを追加、main.sqlおよびdrop_table.sqlの更新
・SQL: 使われてないテーブル login_error, ragsrvinfo, sstatus を作成しないように削除（sql_files/mail.sql）

----------------------------------------
//047 [2007/01/02] by Rayce

・path_search_real(), path_search_long_real() で参照する引数の型をcell_t型に修正（map.h, path.c）
　path_search2() 用に CHK_NONE を追加
・細かい修正および整形
	battle_calc_damage()
	battle_calc_magic_attack()
	clif_skill_nodamage()
	clif_guild_message()
	pc_payzeny()
	pc_getzeny()
	pc_steal_item()

----------------------------------------
//046 [2007/01/01] by Rayce

・白羽取り中に連打掌を使うと鯖落ちするバグを修正（unit.c）
	reported by 16な人 in Athena Project

・bcc32_make.batで「zlib.dllをコンパイルする」を有効にしてもコンパイルされなかったのを修正
	有効にすればzlib.dllがなくても正常に起動するようになります
・vc_make.batにzlib.dllを読み込むかどうかのスイッチを追加
	BCCと同じくデフォルトでは無効にしておくのでコンパイルされません
	有効に変更しない限りはVCでもzlib.dllが必要になります
・BCCのとき、crc32.cとdeflate.cで「条件が常に真」と誤認されて警告が出るので強制的に抑制
	__warning__ に -w-8008 を追加

----------------------------------------
//045 [2006/12/30] by Rayce

・@mesでさらにオープンGM会話（黄色）が設定できるように拡張（clif.c, pc.*）
　ただしconf/GM_account.txtでGMを一人も設定していない場合は通常発言になります
・clif_onlymessage() でメモリリークが発生する可能性を修正（clif.c）

・スクリプトエンジンに関して、038をさらに改善
	merged from eA, thanks to FlavioJS
	-> add_str() で search_str() を呼ぶ必要はないので修正
	-> ハッシュのアルゴリズムを変更、SDBMを採用
	　 分散性が向上することが確認できたのでより高速に処理されるはず
	-> SCRIPT_HASH_SIZEを素数521に変更
	-> hash_dump.txtに吐き出す情報の追加、および整理

----------------------------------------
//044 [2006/12/28] by Rayce

・grfファイルの読み込みに関する大幅な変更と拡張（grfio.*, map.c）
　基本的にはeAを参考にしました、thx a lot!!

　　今まではgrfファイルを読み込む際に、grf内に格納されているファイル全てに対してデコード情報を保存していました。
　　しかしサーバ側はgatとtxtファイルしか必要としないので、他のファイルに関しては情報を保存しないように変更しました。
　　これによりメモリ使用量が約5MB近く削減されます（約40000 files × 132 = 5,280,000 byte）。

	GRF version: 0x0200. Number of files: 29977. Entered files: 462.
	               ↑                      ↑                    ↑
	      [grfファイルのversion]           ｜                    ｜
	                        [grf内に存在するファイルの総数]      ｜
	                                          [実際にエントリーされたgat,txtのファイル数]

　　conf/grf-files.txtの記述方式を変更し、10個までしか読み込めなかった制限を取り払います（上限127個）。
　　詳細はconf/grf-files.txtに直接記載しているので参考のこと。
　　またdataフォルダに置いてあるresnametable.txtを読み込んでduplicateするmapを指定できるように拡張しました。

	datadir:                   → data\resnametable.txt
		指定なしなのでgrfファイルを展開した後のファイルを自動で参照する
	datadir: C:\Program Files\ → C:\Program Files\data\resnametable.txt
		指定されたパスにあるresnametable.txtを読み込む

　　resnametable.txtをgrfファイルから抽出し、例えば
	dummy.gat#prontera.gat#
　　のように記述するとdummy.gatという名前のプロンテラを作ることができるのは周知の事実ですが、
　　これをdataフォルダに置いてパスを指定することで、grfファイルを作成することなく簡便にmapのduplicateを
　　行うことが可能になります。

　　今回の変更によりconf/grf-files.txtの機能性が向上したため、map_athena.confにある
　　read_grf_files_txt, data_grf, sdata_grf, adata_grfキーは廃止します。
　　今後はgrfファイルの読み込みはconf/grf-files.txtに一任されますので注意してください。

　　補足事項は以下の通り
	-> エントリテーブルを作成せずに直接 grfio_add() を呼び出して読み込み開始する
	-> MAX_GRF_FILES, data_file構造体を削除
	-> リソースチェックは全てのgrfファイルを解析し終えた後に行う
	　 grfio_resourcecheck() は対象ファイル名を引数に取るように変更
	-> filelist_adjust() は最後だけでよい
	-> grfio_setdatafile() は不要になったので削除

・上記のresnametable.txtの指定対応に伴い、012で実装したavailmapシステムは廃止（char.*, chrif.c, map.*, pc.c）
　　availmapは全てサーバ側で制御できるため、ユーザーにパッチを配布することなくmapのコピーを作成できるという利点
　　がありました。
　　しかし、例えば別のMAPへワープする際に現在のMAPとduplicateされたMAPの参照元が同じだった場合、ミニMAPに表示
　　されるPTメンバーのドットが消えずに残ったりするという気持ち悪さがありました。
　　もちろん修正することは可能でしたが、resnametable.txtを利用する方が遥かにスマート（/whereも正常に働くし）だと
　　判断したため、システムそのものを白紙に戻すことに決めました。
　　今後はresnametable.txtに必要な情報を追加し、ユーザーに配布する形式を取ってください。

----------------------------------------
//043 [2006/12/27] by Rayce

・042のキャストの明示が抜けている箇所を修正
・storage, guild_storage構造体のメンバ storage を store_item に名称変更（mmo.h）
・アイテムが製造武器、名前入り、ペット情報埋め込み済みかどうかを判定するマクロ itemdb_isspecial() を追加
	merged from eA

・せっかく作ったので、ハッシュの計算結果をダンプするコードを追加しておく（script.c）
	script.cにある DEBUG_HASH のコメントアウトを外すと、サーバ終了時にstr_dataに関する情報を
	hash_dump.txtに書き出すようになります。
	これは元々038で行ったスクリプトの解析速度の高速化を検証するために作ったデバッグ用のコード
	でしたが、もし利用者が自分の環境に合わせて速度を改善したい場合にはこれを用いて SCRIPT_HASH_SIZE
	の最適値を見積もることができます。
	特に独自に作ったスクリプトがかなり巨大で多くの変数/ラベルを使っている場合は、このサイズを
	大きくすることで読み込み速度が向上する可能性があります。

----------------------------------------
//042 [2006/12/27] by Rayce

・void*型から型変換する際はキャストを明示するように修正
・C++の予約語である classやnew キーワードを別の名称に変更
・login-converter.cで malloc.h のインクルードがなくてエラーを起こしていた問題を修正

----------------------------------------
//041 [2006/12/26] by Rayce

・各職に設定可能なスキルツリーのサイズを MAX_SKILL_TREE として定義、デフォルトは100（pc.h）
・ホムのスキルツリーのサイズを MAX_HOMSKILL_TREE として定義、デフォルトは16（homun.h）
・スキルツリー関連でバッファオーバーフローを起こす可能性を修正（homun.c, pc.c）

・属性を示す定数を ELE_*** として定義（map.h）
　属性に関連する値を気付いた範囲で置き換え
　現在は無(0)～不死(9)までしかありませんが、拡張要素でさらに種類を（19まで）増やしてもある程度
　正常に作動することを考慮して部分的に修正

・全体的に細かい修正
・doc/db_ref.txtのhomun_db.txtに関する記述が古いままだったので追記

----------------------------------------
//040 [2006/12/26] by Rayce

・malloc, calloc, realloc, strdup, free を全て aMalloc, aCalloc, aRealloc, aStrdup, aFree に置換
　#define による置き換えはそのままですが、出来る限りこれらのマクロを利用すること

・「unsigned と signed の比較」で警告が出る部分を修正
	BCC: -w-7035 を bcc32_make.batより削除
	VC : /wd4018 を vc_make.batより削除

----------------------------------------
//039 [2006/12/25] by Rayce

・gccでコンパイルする際、038においてscript.hで警告が出力されるので修正（atcommand.c, script.*）
	script_read_vars(), script_write_vars() の引数変更

・scriptのdo-while構文を少しだけ修正
・038でコメントアウトした aRealloc を有効に戻す（サイズ縮小される可能性を考慮して）

----------------------------------------
//038 [2006/12/25] by Rayce

・スクリプトの解析速度を高速化（script.c）
　　SCRIPT_HASH_SIZEを定義し、文字列のハッシュサイズを16から512に拡張
　　parse_script() の script_buf を aCalloc → aMalloc に置き換え
　　parse完了時の aRealloc をコメントアウト（サイズ縮小されないので意味がない）
　　search_str() と add_str() の改善
	-> 今までは小文字で検索し、見つからなかったらそのままの文字で検索し直すという手法だったため
	　 小文字で登録されてないものは検索時間が無駄に必要となる状態でした。
	　 そこで小文字としてハッシュ計算し、strcmpiで文字列の照合を行うようにしました。

　※デフォルトで付属のscript全てを読み込ませた場合、現時点でstr_dataは約3300くらいあります。
　　ハッシュサイズが16だとcollisionが多すぎなので拡張することにしました。
　　512だと外部ハッシュリストに繋がるのが多くても20程度なのでresonableな値だと判断しました。

　※今までは @Buf, @BUF のみがスクリプトに記述されていた場合（全部小文字の @buf は書かれていない時）、
　　@Bufと@BUFが別の変数として扱われるという奇妙な現象が起こっていました。
　　今後はスクリプトの仕様に完全に従う形で、全ての変数/定数/関数/ラベルを小文字として扱うようにします。

　※簡単で非常に荒い実験ですが、読み込み速度が40%近く高速化されていることを確認しました。
　　初期化時だけでなく add_str() を呼び出すスクリプト命令/関数においても高速化されていることが見込まれます。

・@readvars, @writevarsの修正（atcommand.c, script.*）
	-> データ取得と保存部分のみscript.cに記述し、文字列解析部分はatcommand.cに記述する
	-> 変数が登録されているかどうかのチェックは search_str() を利用するように高速化
	-> C_PARAMとC_INTは配列指定 [] があるときは参照できないように修正
	-> 書き込み時に定数を書き換えてしまう危険性を修正
	-> typeの書き換えを行わないように巻き戻し（C_NOPのままで問題ない）

　※atcommand_vars_sub(), script_check_variable(), script_read_vars(), script_write_vars() 追加
　※script_operate_vars() の削除

----------------------------------------
//037 [2006/12/24] by Rayce

・NPCファイルの読み込み時に、MAP名のチェックを強化する（npc.c）
・スクリプトエンジンの改善（script.c）
	-> スクリプトのparse時にエラーが発生した場合、エラー箇所を正しく出力するように修正
	-> check_script_buf() を expand_script_buf() に改名し、バッファサイズの拡張を行うだけの関数に変更
	-> 不要なコメントアウト部分を抹消
	-> getelementofarray関数の処理改善
	　 頻繁に使われる可能性の高い1次元の配列に関しては、多次元配列をサポートしたAthena2099より前の方法
	　 に近い形にして高速化を図っています
	-> getcharid関数で引数の値の範囲チェックが抜けていたので修正
	-> if, else-if, switch, while, do-whileの後には必ず () を付けることを強制する

　※以下のようなコードは今後エラーとして扱われます
	if Sex mes "true"; close;
　　C言語ライクなスクリプトを指向するため、必ず if(Sex) のように () を付けなければなりません

・上記変更に伴ってエラーが出るNPCスクリプトの修正
	script/npc/town/npc_lighthalzen.txt

・pvp_nopenaltyという存在しないmapflagを削除（script/mapflag/mapflag.txt）
	022でmapflag系の整理を行った際に存在しないmapflagを指定した場合には警告を出すように強化
	してましたが、mapflagファイル自体の修正が抜けてました
・kh_dun02.gatのmapflagからnoteleportが欠けてたので修正
・conf/map_athena.confに035で追加されたnpc_event_halloween.txtの記述が抜けてたので追記

----------------------------------------
//036 [2006/12/20] by Rayce

・定数の追加と精錬に関する拡張（map.h, pc.h）
	MAX_WEAPON_LEVEL : 武器Lvの最大値でデフォルトは4
	MAX_REFINE : 最大精錬値でデフォルトは10
	WT_MAX : 武器タイプの最大値、自動的に設定される

　※Lv5以上の武器を追加したい場合はMAX_WEAPON_LEVELの値を増やし、refine_dbの行を書き加えてください
　　+11以上の精錬を設定したい場合はMAX_REFINEの値を増やし、refine_dbのLv10の成功確率の次の列に確率を書き加えてください

・status.cでデータベースを読み込む変数の見通しをよくするための変更
	-> refine_db.txtに利用する変数（refinebonusとpercentrefinery）をまとめてrefine_db構造体とする
	-> job_db1.txt, job_db2.txt, job_db2-2.txtで利用する変数群をまとめてjob_db構造体とする
	-> status_getrefinebonus() を status_get_overrefine_bonus() に改名して、過剰精錬ボーナスを返す
	　 ためだけの関数に変更
	-> status_calc_pc() で最大HP,SPを計算する部分を少し整理

・+10装備に対してスクリプトのgetequippercentrefinery関数を実行すると、バッファオーバーフロー
　（最悪の場合サーバクラッシュ）が発生するバグを修正
・@reloadstatusdbを実行した際に、job_db1.txtのHP係数の値を変更しても最大HPが正しく再計算されない問題を
　修正するために、status_calc_sigma() を status_readdb() 内に取り込み
・スパノビの魂で装備可能になる武器LvをLv4以上に拡張（pc.c）

----------------------------------------
//035 [2006/12/19] by Rayce

・AthenaProject2266よりmerge, thanks to Blazeさん
　以下Readmeをそのまま転載
	・忍者・ガンスリンガーのJOBEXPテーブルLv49～更新（exp.txt）
	・テコン系列のHP・SP係数など修正（job_db1.txt）
	・item_fabox.txt、item_arrowtype.txt、mob_boss.txt更新
	・ハンター転職員の座標を修正（npc_job_11hunter.txt）
	・ジョンダ職員からカートを借りられない不具合を修正（npc_misc_zonda.txt）
	・コモドクエスト修正（npc_town_comodo.txt）
	・アインブロッククエスト修正と料理人クエスト追加（npc_town_einbroch.txt）
	・2006ハロウィンイベント新規追加（npc_event_halloween.txt）
	・神器、TheSign、タナトスクエスト関連マップのmapflagを追加（mapflag.txt）

・AthenaProject2267より部分的にmerge, thanks to Cocoaさん
　以下変更箇所のみそのまま転載
	・リザレクションホムンクルスの詠唱を中断可能に変更(skil_db.txt)
	・アシッドテラー、デモンストレーション、ケミカルチャージのディレイ追加(skill_cast_db.txt)

----------------------------------------
//034 [2006/12/19] by Rayce

・ホムがunit_free() されるときにも status_change_clear() を呼ぶように修正（unit.c）
・unit.cを少しだけ整理
・SI_BREAKARMOR, SI_BREAKWEAPON, SI_MAGNUM を追加（status.h）
・マグナムブレイク中ならSI_MAGNUMを送信するように修正（status.c）

・status_change_clear() の修正
	-> コメントアウト部分はもはや必要すらないので抹消
	-> type=0のときにのみSC_BABYとSC_REDEMPTIOのスキップ判定を行うように変更
	　 つまりtype=1（PC, HOMのunit_free）とtype=2（MOBのunit_remove_map）のときは全ステータス異常
	　 を強制的に解除するということになります
	-> sc_countを0にしないように修正

・Himmel氏発案のGMハイドの改造をmerge, thx a lot!!（atcommand.c, battle.*, clif.c）
	battle_athena.confにgm_perfect_hideを追加しました。デフォルトはno。
	yesにすると@hideが完全なインビジブルモードとなり、ツールによって姿が検出されなくなります。
	@hideでハイドした際は一旦キャラクターを消滅させ、解除時に再度出現パケットを送信しています。
	これによりハイドの瞬間に位置を悟られることを防止し、また出現の際に座標がズレるのを解消しています。

----------------------------------------
//033 [2006/12/17] by Rayce

・グラウンドドリフトをファイアスフィアで設置した場合、吹き飛ばすときにSAB_NODAMAGEを入れるように修正
	skill_additional_effect() が呼ばれるのはダメージ発生後なので、clif_blown() で飛ばすと位置ズレ
	を引き起こす可能性があるためです

・デスペラード修正
	5x5の範囲にランダムでオブジェクトが10回発生する、オブジェクトの攻撃範囲は3x3
	ウォーターボールとメテオストームのロジックを組み合わせてやってます

・アローシャワー、デスペラード、グラウンドドリフトは発動時に矢/弾を消費するように修正（battle.c, skill.c）
	敵が範囲内に居なくても消費されるようになります
	特にグラウンドドリフトは敵がヒットしたときに弾が減るという奇妙な現象が解消されます
	battle_skill_attack() ではなく自前で battle_delarrow() を呼び出すことで処理するように変更しています

----------------------------------------
//032 [2006/12/16] by Rayce

・status.cでコンパイル時に警告が出てたので修正（status.c）
・スキルユニットが罠かどうかを判定する skill_unit_istrap() を用意（skill.h）
・アンクルに敵が乗った状態で自動鷹が発動するとダメージが分散してしまう問題を修正（skill.c）
・battle_athena.confにtrap_is_invisibleを追加（battle.*, clif.c）
	yesにすると設置した罠が見えないようになります、merged from eA

----------------------------------------
//031 [2006/12/16] by Rayce

・凍結、石化、睡眠を解除する処理をまとめた status_change_attacked_end() を用意（battle.c, skill.c, status.*）
・ハイド状態を解除する処理をまとめた status_change_hidden_end() を用意（homun.c, mob.c, pc.c, status.*）
・スキルユニットのIDを定数 UNT_*** として定義する（skill.*）
	merged from eA

・グラウンドドリフトの暫定修正（battle.c, clif.c, skill.c）
	-> clif.cで弾薬の種類に応じて見かけを変えるのではなく、実際にスキルユニットIDを変えるように修正
	-> 足元置き、重ね置き可能にしてみる
	-> BF_WEAPONではくBF_MISCとして扱うようにしてみる
	　 スキルユニットからの攻撃を武器スキルとして扱うとダメージディレイが異常に遅れたり
	　 矢のATKが加算されたりするなど不可思議なことが起こり得るので罠と同じ扱いにしておきます
	-> battle_calc_attack() および skill_additional_effect() に引数を渡すとき、グラウンドドリフトだけは
	　 スキルユニットのIDが必要になるのでsrcの代わりにdsrcを渡すようにする
	-> 100%ダメージを属性込みで計算したあと、固定部分を加算してさらに無属性で属性補正するように修正
	-> ウィンドスフィアならスタン、ダークスフィアなら盲目、ポイズンスフィアなら毒、アイススフィアなら凍結
	　 の効果が追加されるように修正、確率は不明なので基本50%で設定
	-> ファイアスフィアなら必ず3セル吹き飛ぶように修正

---------------------------------------
//030 [2006/12/13] by Rayce

・@mesで従来のギルド会話、オープン会話に加えてパーティ会話が選択できるように拡張（clif.c）
・Athena1881以前の古い形式のキャラクターセーブデータは今後サポートしないようにする
・conf/char_athena.confで、キャラ作成時に持たせる武器と防具を任意に設定できるように拡張（merged from Freya）
	デフォルトではナイフとコットンシャツですが、start_weaponとstart_armorの値を変えることで
	違うものを持たせることが可能です
	また0にすることで初期装備を無しに設定できます。

・httpd.cでAURIGA_MOD_VERSIONではなくAURIGA_REVISIONを参照するように変更
・atn_bignumber型の定義とRETCODEをmmo.hからutils.hへ移動
・VCの警告関連
	pragma(disable : 4996) は削除、core.cのunlinkをremoveに置換
	エンコード問題があるので 4819 の警告をvc_make.batで抑制するように追加
	ついでに 4018 もvc_make.batで定義する

----------------------------------------
//029 [2006/12/13] by Rayce

・Athena Projectに投稿されたRohypnolさんのパッチから、独自修正項目についてmerge, thx a lot!!
	-> モンクの魂状態なら猛龍拳が5×5の範囲攻撃になるように修正
	-> ビーストストレイピングはダブルストレイピング使用後2sec以内でしか使えないように修正
	-> ビーストストレイピングが動物だけでなく昆虫種族にも使えるように修正
	-> 以下のスキル使用時に共闘ボーナスが付くように修正、battle_join_struggle() 追加
	　 （プロボック、気奪、マインドブレイカー、スティールコイン）

・カートレボリューションの吹き飛び方向を修正
　ターゲット以外の周囲の相手は、発動者ではなくターゲットとの位置関係で飛ぶ方向を決める

----------------------------------------
//028 [2006/12/12] by Rayce

・武器修理についてeAを参考して修正（clif.c, skill.*）
	-> メニュー選択後に射程内に対象が居ない場合は失敗するように修正
	-> 成功したときのみエフェクトを出すように修正
	-> clif.cでは判定を行わず、全てskill_repair_weapon() 内で処理するように変更
	-> skill_can_repair() は skill_repair_weapon() に吸収したので削除
	-> 処理方法の改善

・向き判定用の配列 dirx[], diry[] をmap.cに集める（homun.c, map.*, pc.c, pet.c, skill.c, unit.c）
・unit_skillcastcancel() に詠唱妨害可能かどうかの判定を取り込む
　引数に2を指定すれば、関数内部でフェンカードやGvGマップかなどを調べます

----------------------------------------
//027 [2006/12/11] by Rayce

・conf/grf-files.txtでdata, sdata, adataの制限を取り払うように拡張（grfio.*, map.c）
	-> MAX_GRF_FILES（デフォルトでは10個）まで読み込み可能
	-> : の前の名前は15文字以内で任意に指定することができます
	　 同じ名前がある場合は下に記述されたもので上書きされます
	-> 行頭に // を入れるとコメントアウトとして扱われます
	-> map_athena.confの方はdata, sdata, adata固定のままです
	　 grf-files.txtを利用することを推奨します

----------------------------------------
//026 [2006/12/11] by Rayce

・db/produce_db.txtの拡張をAthena Projectの投稿分からmerge, thanks to Rohypnolさん（skill.*）
	-> dbに新しくFixPerの項目を挿入
	　 基本成功確率にこの値を加算することで確率の補正を個別に設定します
	-> skill_produce_db構造体から使われてないメンバ trigger を削除し、perを追加
	-> skill.hに製造グループ定数 PRD_*** を追加
	　 製造の種別はスキルIDではなくこのグループ定数で分類する
	-> battle_athena.confの以下3項目が全く利用されてなかったので修正
		scroll_produce_rate, making_rate, scroll_item_name_input
	-> クリエイトコンバーターは100%成功にしておく
	　 db/produce_db.txtのFixPerを10000に設定しただけで、計算式自体はskill.cに残してます
	-> オリデオコン/エルニウム作成は本鯖にはない機能なので、ItemLvを1003に変更しておく
	-> 説明についてはdoc/db_ref.txtに記載

・012のMAPコピー機能の追加以後、担当MAPを決める処理が誤作動を起こしそうな気がしたので少し修正（map.h）
・login.cから使われてない変数 m_start, gm_last を削除（login.c）

----------------------------------------
//025 [2006/12/09] by Rayce

・製造系の修正をAthena2262-fix4よりmerge、thanks to T.Nさん（clif.c, skill.*）
	-> skill_produce_mix() から確率計算部分を切り離して skill_calc_produce_rate() とする
	-> 同様にファーマシー成功時のランキング計算部分を切り離して skill_am_ranking_point() とする
	-> skill_can_produce_mix() はnameidではなくインデックスを直接受け取るように変更し、検索の無駄を省く
	-> トワイライトファーマシーで成功個数/ランキングを一度に獲得するように修正
	-> トワイライトファーマシー成功後、重量オーバーになってしまう場合は地面に落ちずに消滅するように

----------------------------------------
//024 [2006/12/08] by Rayce

・pc_dead() でのデスペナルティ処理を最適化（pc.c）
・カオティックベネディクションのスキルLvが11以上のときサーバクラッシュする問題を修正（skill.c）
・battle_athena.confでresurrection_expを設定していたとき、JobExpの計算が間違っていたバグを修正（skill.c）
・レデムプティオで取得できる経験値の計算において、battle_athena.confのdeath_penalty_typeの設定が
　正しく反映されてなかったバグを修正（skill.c）
・経験値計算処理は出来るだけdouble型ではなくatn_bignumber型を利用するように修正
・skill_castend_nodamage_id() を少し整形

----------------------------------------
//023 [2006/12/08] by Rayce

・setmapflag命令の機能拡張
	const.txtに記載されているマップフラグ全てをこの命令で設定できます。
	mf_nosave, mf_baseexp_rate, mf_jobexp_rate, mf_pvp_nightmaredrop, mf_gvg_nightmaredrop, mf_pk_nightmaredrop
	については更に引数を指定することで必要な情報を設定します。
・setmapflag命令でナイトメアモード用の設定を行うために npc_set_mapflag_sub() を利用するので
　staticを外してnpc.hで宣言するように変更
・setmapflagnosave命令は不要になったので抹消

・removemapflag命令の機能拡張
	ナイトメアモード系を削除する場合には該当マップのドロップリストを削除し、
	空き詰め処理を行います。

・checkmapflag関数の追加
	指定マップに該当のmapflagが設定されているかどうかを調べます。
	mf_baseexp_rate, mf_jobexp_rateの場合には設定した経験値取得倍率が返ってきます。
	ナイトメアモード系のドロップリストに関する情報は取得できません。

・上記を実装するに当たり、処理を一括でまとめたかったので変数にビットフィールドを使わないように変更
	全てint型にして、script_conv_mapflag() でアドレスを取得できるようにしています。
	base_exp_rateとjob_exp_rateをflag構造体のメンバとして取り込み。

　※checkmapflag関数はgetpkflag関数の上位互換版です。
　　if(getpkflag("this")) は if(checkmapflag("this",mf_pvp) || checkmapflag("this",mf_gvg))
　　と等価ということになります。。
　　マップフラグに応じてスクリプトの挙動やアイテムの効果を変化させたいときなどに。

----------------------------------------
//022 [2006/12/07] by Rayce

・mapflag関連の最適化や機能追加
　（atcommand.c, map.*, mob.c, npc.*, pc.c, script.c, skill.c）
	-> mapflagを設定する処理をまとめて npc_set_mapflag() を用意
	　 スクリプトからの読み込みと@mapflagからの読み込みで共用します
	-> base_exp_rateとjob_exp_rateで負の値を設定しても取得経験値倍率が0にならなかった問題を修正
	-> MF_***系定数をscript.cからmap.hへ移動
	-> map_data構造体内のdrop_list構造体に drop_flag メンバを追加
	　 Pv, Gv, PK でドロップリストを共存させるためのものです
	-> ナイトメアモードの場合のアイテムドロップ処理をまとめて pc_nightmare_drop() を用意
	　 処理がゴチャゴチャしてたので書き直し
	-> MAX_DROP_PER_MAP の値が大きすぎるので、48 → 8 に縮める
	　 越えてしまった場合は「drop list is full」が出力されます
	　 ナイトメアモードで多くのアイテムIDを設定したい場合にはこの値を大きくしてください
	-> PKフィールドをナイトメアモードに一括変更するとき（map_athena.confのmap_pk_nightmaredrop有効時）
	　 drop_listに空きがない場合はモード設定しないように変更
	-> 存在しないマップフラグをスクリプトに書いていた場合は警報が鳴るように
	-> 利用価値が低いので map_check_normalmap() を削除
	-> 以下の4つのマップフラグをスクリプトから設定できるように
		fireworks, cloud1, cloud2, cloud3
	-> ついでなので新しく gvg_nightmaredrop を追加
	　 シーズモードで且つアイテムをドロップする特殊なMAPを作ることができます
	-> db/const.txtを変更
	-> doc/script_ref.txt更新

・pc_damage() から死亡処理を切り離して pc_dead() を用意（pc.c）
・ALT+Gをしたときギルドエンブレムが時々表示されないバグを多分修正（clif.c）
	merged from eAthena, thx a lot!!

----------------------------------------
//021 [2006/12/06] by Rayce

・キャラIDは出来るだけsd->char_idではなくsd->status.char_idを参照するように修正
　sd->char_idは認証用に使うだけに留める
・スクリプト解析エンジンについてeAthenaより一部merge（script.c）

・doc/script_ref.txt更新
・db群の更新
	thanks to huge cgi

----------------------------------------
//020 [2006/12/06] by Rayce

・ブロックIDの定義が各ファイルに散らばってて把握しずらいのでmmo.hに集める
	-> MIN_FLOORITEM を追加、MAX_FLOORITEM をmap.hから移動
	-> START_ACCOUNT_NUM, END_ACCOUNT_NUM をlogin.hから移動
	-> START_NPC_NUM, END_NPC_NUM をnpc.hから移動

・clif_parse_WantToConnection() における不正パケットのチェックを強化（chrif.c, clif.c）
	-> 送られてきたアカウントIDが不正な値でないかチェックする
	　 （例えばIDの値がMAX_FLOORITEM以内だと、存在しているのに map_id2sd() で検索されないキャラが出来る）
	-> Sexの不正チェックを chrif_authreq() から移動
	-> session_dataをcallocする前に判定は行う、不正だった場合はタイムアウトで落とす
	-> 「invalid Account ID !!」および「invalid Sex !!」が出力された場合は、
	　 不正なアクセスが行われたことを意味します

・一部の weapontype1, weapontype2 変数への代入について、0を WT_FIST に置換（pc.c）
・map.cを少しだけ整形

・scriptのchangebase命令で、職業IDが22（ウェディング）および26（拳聖2）のときは武器を外す処理が含まれていたが
　この部分をコメントアウト（script.c）
	装備を外すとHPやSPが減少する効果（bSPPenaltyUnrig等）を持つ装備品を装備している状態（三葉蟲カード等）で、
	EquipScriptに changebase 22; が記述された装備品（ウェディングドレス等）を装備すると
	HPとSPが共に0になり死亡してしまう現象を修正するための処置です。
	武器を外す処理を省いてもウェディング状態のときは clif_changelook() で武器の表示をしないように処置される
	ためクライアントエラーにはなりません。

　※詳細
	上記の例の場合、呼び出される主な関数は以下の通り。
	pc_equipitem() → status_calc_pc() → run_script() → buildin_changebase() → pc_unequip() → pc_heal()
	bSPPenaltyUnrigの効果により装備の解除時に pc_heal() が呼ばれますが、status_calc_pc() ではmax_hpの値は
	まだ計算されていない状態なので max_hp = 0 です。
	従って pc_heal() で最初に呼ばれる pc_checkoverhp() によってHPが0にされてしまいます。

----------------------------------------
//019 [2006/12/05] by Rayce

・mob_dead() の処理改善および整形
・ホムがMVPを取ったときのMVP経験値に対しても battle_athena.conf の master_get_homun_base_exp
　の倍率を適用するように修正（mob.c）

・一部のスキルの倍率計算において、double型ではなくatn_bignumber型を使うように変更（battle.c）
　少しオーバーフローしやすくなってる可能性はあります…
・battle_calc_weapon_attack() で利用するマクロ名が紛らわしいので
　ATK_FIX → DMG_FIX, ATK_ADD → DMG_ADD に変更、新たに DMG_SET 追加（ダメージ値の置換用）

・atn_bignumber型の変換指定子を統一して使えるようにマクロ BIGNUMCODE を用意（mmo.h）
　基本的にprintf用で10進数のみ対応です。
　用意しただけで実際のコードには今のところ出現してませんが、数値をダンプしたいとき等に利用してください。
	printf("i = %"BIGNUMCODE, i);

----------------------------------------
//018 [2006/12/04] by Rayce

・被弾共闘が入らないのを修正（pc.c）
　応急処置的にbl.idで管理するようにはしてますが、本来ならPCの場合はキャラIDを利用すべきなので
　いずれ修正する必要はあります
	merged from Athena-2262, thanks to T.Nさん

・doc/script_ref.txtにおいてmapflagの base_exp_rate, job_exp_rate に関して追記
・一閃を必中に修正（battle.c）
・mob_damage() から死亡処理の部分を切り離して mob_dead() を用意、および少し整理（mob.c）
・mob_damage() にあるテコンミッションのターゲット選定でも無限ループに陥る可能性があったので修正（mob.c）

・経験値取得系の関数において、引数をint型からatn_bignumber型に変更
　および無駄なキャストを排除して整理し直し
	guild_payexp(), homun_gainexp(), party_exp_share(), pc_gainexp()
・ホムの取得経験値がオーバーフローする可能性を修正（homun.c）
・ホムが取得した経験値を主人へ渡すときの倍率をbattle_athena.confで指定できるように変更/拡張（battle.c, homun.c）
	master_get_homun_base_exp はデフォルトで100（%）です
	master_get_homun_job_exp  はデフォルトで0（%）です

----------------------------------------
//017 [2006/12/01] by Rayce

・battle_calc_weapon_attack() の修繕その８
	-> 回避判定を先に行い、回避できなかったときだけ必要なダメージ計算を行うように改善
	　 基本ダメージ計算 battle_calc_base_damage() などの処理が省略されますので、回避時の計算は
	　 かなり改善されているものと期待します
	-> ヒット・属性・レンジの補正は回避判定の前に集める
	　 これら3つの要素は最終ダメージ計算 battle_calc_damage() に必要です
	　 battle_calc_damage() は回避出来たときにも呼び出されるので、回避判定前に補正しておかなければなりません

　※クリティカル時の処理をさらに改善する余地はありますが、長らく続いた修繕関連はこれでひとまず終了とします。

----------------------------------------
//016 [2006/11/29] by Rayce

・ヒールと治療の助けをカイトで反射した際にもエフェクトを付ける（skill.c）
・ローグの魂効果中はディスペル無効に修正（skill.c）

・battle_calc_weapon_attack() の修繕その７
	-> 「カードによるダメージ追加処理」「カードによる左手ダメージ追加処理」「カードによるダメージ減衰処理」
	　 「対象にステータス異常がある場合のダメージ減算処理」の4項目は、ダメージがあるときだけ計算する
	　 これらはダメージ倍率を計算する部分ですが、ダメージが0の場合は積を取っても結局0になるのは確定しているので
	　 計算を行う必要はありません
	-> スパイラルピアースのスキル倍率が間違っていたので修正、break抜け？
	-> 細かい整形

----------------------------------------
//015 [2006/11/21] by Rayce

・サーバースナップショット（version.h）
・不要なファイルを削除
　　conf/
	help1.txt, help2.txt, help3.txt, help4.txt
　　src/common/
	zconf_win32.h, zlib_win32.h

----------------------------------------
//014 [2006/11/28] by Rayce

・mmo.hに定義されていて実体がcore.cにある状況が気持ち悪いので、eAのようにutils.c, utils.hを追加
　共通で汎用的に使う関数をここに集めることにします
・各ファイルにおけるincludeの整理と整形

・version.hの ATHENA_*** を AURIGA_*** に改名しておく（httpd.c, version.h, login.c, char.c, clif.c, map.c）
・AurigaはModではないので、AURIGA_MOD_VERSION は未定義にする予定です
　パッチ番号はRevisionに合わせるつもりです
　つまり現在のversionは「Auriga-0.0.14」になります
　今のところAURIGA_MOD_VERSIONに関しては改名してmodを0にしただけであり、正式に修正されていません

・既に廃止されている zlib_win32.h, zconf_win32.h を削除するためにdspファイルの修正
・ジャーナルをオンにしてVCでコンパイルすると unlink() で警告が出るので remove() に変更しておく（journal.c）

----------------------------------------
//013 [2006/11/27] by Rayce

・battle_calc_weapon_attack() の修繕その６
	-> 「防御無視判定および錐効果ダメージ計算」の項目において、左手がある場合にのみ
	　 battle_athena.confのleft_cardfix_to_rightを適用するように修正
	-> 「対象の防御力によるダメージ減少」の項目において、左手用の防御無視フラグ calc_flag.idef_ が
	　 判定に全く関与していなかった問題を修正
	-> 「カードによる左手ダメージ追加処理」の項目は左手があるときだけ行うように改善

・clif_party_xy() と clif_party_hp() の引数 *p は未使用なので削除（clif.*, party.c, pc.c）
・cp_setpos() でOnPCMapMoveを実行するかどうかの判定処理を少し修正（pc.c）

----------------------------------------
//012 [2006/11/26] by Rayce

・マップのduplicateシステムとしてmap_athena.confのキーに availmap を追加（char.*, chrif.c, map.*, pc.c）
	例えばpronteraを常設のイベントMAPとして利用したいと考えた場合、元々のpronteraは使えなくなってしまいます。
	そのためgrf内のpronteraのMAPファイルをコピーし、別の名前に変更してユーザーにパッチとして配布する必要がありました。
	このシステムはパッチ配布という煩わしさを解消し、手軽にMAPのコピーを作成できるようにサーバ側で「すり替え」を行うためのものです。
	map_athena.confに例として以下のように記述。
		availmap: duplicate.gat,prontera.gat
	サーバ側ではduplicate.gatとして読み込みますが、クライアント側にはprontera.gatとして認識させます。
	要するにitem_avail.txtやmob_avail.txtのすり替えと同じもので、pronteraが擬似的にコピーされます。
	詳細はdoc/conf_ref.txtを参照のこと。

・@whereを少し仕様変更（atcommand.c）
　　@where [キャラ名] のようにキャラ名の部分は可変にします。
　　キャラ名が指定されない場合は自分自身のMAP情報が出力されます。
　　これは上記のコピーマップに対応するためのもので、自分が居る実際のMAP名を得ることができます。
　　（ /whereだとpronteraとして表示されてしまいますが、@whereだと正常にduplicateとして表示されます ）

・map_athena.confで指定したMAP名が不正な場合、mapデータベースから削除されなかった問題を修正（map.c）
　MAP名の判定は map_readallmap() ではなく map_addmap() で行うようにします
　参照元のMAP名は記述が間違っていても map_readmap() 内部で弾かれますが、コピーのMAP名はそれがないので厳密にMAP名のチェックを行います
　また不正な名前であった場合には "invalid map name!! (???)" が出力されます

・doc周りの更新
	conf/help.txt, doc/client_packet.txt, doc/conf_ref.txt

----------------------------------------
//011 [2006/11/25] by Rayce

・battle_calc_weapon_attack() の修繕その５
	-> 左手判定があるときだけwd.damage2を計算するようにする
	　 計算用のマクロ ATK_FIX, ATK_ADD を追加
	-> ブランディッシュスピアの攻撃力計算式がおかしかったので修正（Lv上昇に伴う倍率加算がなくなってた）
	-> 細かい整形
・010において警告が出るので修正（script.c）
・カイトで反射時にエフェクトを表示するように修正（battle.c）
	reported by rei in Athena Project Forum and refered to eAthena, thx

----------------------------------------
//010 [2006/11/24] by Rayce

・スクリプトのcsvアクセス命令/関数において、ファイル名のチェック処理をまとめた script_csvfilename_check() を追加
	merged from Athena-2262, thanks to T.Nさん
・doc/client_packet.txtを更新

・battle_calc_weapon_attack() の修繕その４
	-> battle_calc_base_damage() の引数を変更
	　 右手だけのときは左手の分の計算を行わないように改善
	　 また左手判定がある場合にはこの関数を2回呼び出してそれぞれ計算を行うことにします

　※右手だけのときは左手の計算をしないので高速化されますが、左手があるときは2回演算するので逆に遅くなります
　　しかし戦闘の大部分を占めるのは右手だけのときなので、全体的には高速化されているはずです
　※右手素手で左手武器の場合本来ならば右手の計算は不要ですが、左手のみという状況は限りなく少ないので
　　高速化のために右手は必ず計算します

----------------------------------------
//009 [2006/11/24] by Rayce

・battle_calc_weapon_attack() の修繕その３
	-> 各計算項目をナンバリングし、計算手順を明確化する
	-> ダメージ計算を始める前に左手武器があるかどうかを判定する
	　 スキル攻撃の場合は左手のダメージは反映されないので、左手武器が必要と判定されるのは通常攻撃だけ
	-> 既にDEF無視フラグが立っているときは「対象の防御力によるダメージの減少」の項目内の計算そのもの
	　 を行わないように処理改善
	-> 全体的に細かい整形

・battle_calc_damage() を少し修正し直し
・新ログインパケット？0x277をサポート（login.c）
	merged from Athena-debug2264, thanks to KADP

----------------------------------------
//008 [2006/11/24] by Rayce

・battle_calc_weapon_attack() の修繕その２
	-> クリティカル攻撃にならないと事前に確定しているものはクリティカル計算そのものを行わない
	-> テコンの蹴り構えを複数同時使用した状態のとき、アプチャオルリギの発動優先順位を最低にする
	-> 連撃判定部分の整形
・MAP鯖のコンソールにもversion表記を出力させる（map.c）
・bcc32_clean.batでmapファイルとtdsファイルも消去するように追加

----------------------------------------
//007 [2006/11/23] by Rayce

・battle_calc_weapon_attack() の修繕
	-> この関数内で全般的に参照する必要あるフラグ変数をまとめた calc_flag 構造体を用意
	　 変数名を変更しただけで基本的な構造は変えてません、rh, lhは準備だけ
	-> ソウルブレイカーのランダム追加ダメージの計算方法を修正

----------------------------------------
//006 [2006/11/23] by Rayce

・005でatcommand_athena.confの変更を忘れてたので同梱
・スタック破壊を修正（int_homun.c）
	merged from Athena-2262, thanks to T.Nさん

・スクリプト命令/関数のバグ修正（script.c）
	-> 以下のスクリプト関数のおいて、スタックに返り値がプッシュされずサーバクラッシュを引き起こすため修正
	　 またこのようなクラッシュを応急処置的に防止するために run_func() を少し修正
	　 　getarraysize, getequipid, getnpctimer, sc_ison, getguildcastle, getrepairableitemcount,
	　 　countitem, countcartitem, checkoption
	-> menu/selectでキャラクターがアタッチされてないときはキャンセル扱いにして終了させる
	-> sc_ison関数で状態異常のtypeが不正な値かどうかをチェックするよう強化

----------------------------------------
//005 [2006/11/22] by Rayce

・battle_skill_attack() で「何もしない」判定されたときは矢を消費しないようにしてみる
・battle_calc_weapon_attack() で最初にターゲットのクラスを得るように変更
・battle_calc_weapon_attack() で魅惑のウィンクや強制移動状態であるかどうかの判定を行わないように変更
	この関数はダメージ計算を行うだけに留め、状態によって判定するかどうかは呼び出し元で行うべきなので
	battle_weapon_attack() と battle_skill_attack() でそれぞれ判定をするようにしています

・@help系統の仕様変更（atcommand.*）
	conf/help1.txt（同様に2,3,4）に追記し忘れることが多いので、@help1,2,3,4は廃止
	代替方式として@helpを「@help [開始行] [終了行]」のように引数を可変にします
	行指定しない場合は全てのヘルプを表示します
	指定した場合は開始行～終了行のヘルプだけを表示します
	ただし0は指定なしを意味します
	また行頭に // を付けるとコメントアウトと見なされ、その行は表示されません
	　　例）@help 0 20  -> 最初の行～20行目まで表示
	　　　　@help 10 0  -> 10行目～最後の行まで表示
・conf/help.txtの整理

----------------------------------------
//004 [2006/11/22] by Rayce

・battle_attr_fix() を少し改善
・battle_calc_damage() の処理改善
　特にダメージが発生する場合で、アジトの情報が不要な場合でも情報を検索していた無駄が省かれます

・MAP名に "this" 指定可能なスクリプト命令/関数を考慮して、MAP番号を取得する処理をまとめた関数
　script_mapname2mapid() を用意（script.c）
・以下のスクリプト命令/関数においてMAP名の "this" 指定に対応
	mapannounce, areaannounce, getareadropitem, setmapflagnosave, setmapflag, removemapflag,
	pvpon, pvpoff, gvgon, gvgoff, maprespawnguildid
・MAP非配置型のNPCからmap_foreachinarea() を呼び出す命令/関数を実行されるとアクセス違反が生じる可能性があるので
　map_foreachinarea() でindexの値のチェックを入れるように修正（map.c）

----------------------------------------
//003 [2006/11/22] by Rayce

・battle_calc_weapon_attack() の構造変更によって、001の時点で矢のATKが計算されない
　可能性が生じていたので修正（battle.c）
・battle_calc_weapon_attack() を全体的に整形
・battle_delarrow() の引数を増やして battle_skill_attack() からでも使えるように共通化（battle.*）

・item_arrowtype.txtとitem_group_db.txtで存在しないアイテムIDだった場合は読み飛ばすように修正（itemdb.c）
・item_db.txtでアイテムIDが20000までしか使えない制限を取り払う（atcommand.c, itemdb.*）
	-> 読み込まれたデータの中で最大のID値をmax_itemidに保存しておくように変更
	-> itemdb_getmaxid() を追加
	-> 上記変更に伴って @idsearch を少し修正

・チェイサーのスキル名と混同するので、スキルの使用条件を示す ST_CLOAKING 等の名称を ST_*** → SST_*** に変更（skill.*）
　ST_CHASEWALKというstateは存在せず誤っているので、新しくSST_CHASEWALKINGを定義
　skill_require_db.txtのstateの項目にchasewalkingを追加

----------------------------------------
//002 [2006/11/21] by Rayce

・囲まれ判定用の定数 ATK_LUCKY, ATK_FLEE, ATK_DEF をmap.hからbattle.hに移動
・使われていない定数 MS_IDLE, MS_WALK, MS_ATTACK, MS_DEAD, MS_DELAY をmap.hから削除
　（mob.hの MSS_*** に変更されている）
・使われていない定数 SAB_NORMAL, SAB_SKIDTRAP をskill.hから削除
・ほとんど意味がないので AS_ATTACK, AS_REVENGE をskill.hとbattle.cから削除
・ほとんど意味がないので MAX_STATUS_TYPE をmmo.hとatcommand.cから削除

・pc.cとskill.cの distance() を削除し unit_distance() に置き換え
・一部のdouble型へのキャストをatn_bignumber型に置き換え
・homun_data構造体の変数名を atackable → attackable に変更（clif.c, homun.c, map.h）
・unit.cを少しだけ整理

----------------------------------------
//001 [2006/11/21] by Rayce

・Auriga始動
・サーバースナップショット
・ATHENA_MOD_VERSIONを1に変更（version.h）
・不要なファイルを削除
　　doc/sc_start.txt, bin/tool/convert.c

　※上記以外には変更を加えてないので、実質Athena-dev-2.1.1-mod2261までを集約したSSに相当します
　　このversionを以ってAurigaのスタートとします
　　細かい部分は「Athena」のままですが、今後変更していく予定です

----------------------------------------

    Athena Dev. v2.1.1       Released: Middle July, 2003
    (c) 2003 Athena Project.
     http://project-yare.de/

1. Athena(アテナ)について
2. このリリースについて
3. 必要な物
4. 使い方
5. 現在の仕様
6. 祝辞
7. 免責事項
8. 募集
9. English


1. アテナについて
    アテナとは2003年1月半ばにでた0052.lzhをベースとして作られているエミュレータの一つです。
    基本的なライセンスはオリジナルがGPLの下に配布されている為、
    これに従いGPLの下配布を許可します。
    /*
        改良版を配布する場合は必ずこのREADMEを書き換えてください。
        何処を改良したのか報告(athena@project-yare.deまで)して貰えると助かります。
        バイナリのみの配布はGPL違反ですので"必ず"ソースも添付してください。
     */
    動作の確認は以下の通りのみ行っています。
    // ただし完璧に動く事を保証するものでありません
    対象CPU: Intel Pentium系   // PentiumII以上で確認.
        FreeBSD 4.8R, 4.6.2R
        Linux RedHat 7.3
        cygwin + gcc 3.2 20020927 (prerelease)
    開発元URL: http://project-yare.de/


2. このリリースについて
    今回のリリースは前回(V2.1)同様開発版のリリースのみです。
    2.1に比べ下記の点が修正されています。
        mapのデフォルト設定が韓国data.grfのみ正常に動作するようになっていた点
        common/timer.cやmap/script.cの幾つかのバグ

    迅速にUpdateを強く推奨するものではありませんが各自の判断で行って下さい。


3. 必要な物
    data.grf      //sdata.grfは必要に応じて
    account.txt   //存在しない場合athena.shが自動生成します
    conf/*.cnf    //Map用とChar用の二種類あります
    conf/npc*.txt //npc設定用ファイルです。複数のファイルに分けることが可能です。
    db/*.txt      //アイテム、job情報など


4. 使い方
    > tar xvfz athena-d?.?.tar.gz
    > cd athena-d?.?.tar.gz
    > make
    > vi conf/char_athena.cnf       //IP(127.0.0.1)の部分を環境に合わせて変更してください
    > vi conf/map_athena.cnf        //同上、またmap設定などは、このファイルで行います。
    > ./athena.sh
    上記を行えば"たぶん"起動します。

    補足:
    conf/npc_sampleJ.txtにはスクリプトの書き方について色々な説明が記載されています。
    もし、独自のMap設定を行ってみたい人や、スクリプトを弄りたい方は参考にしてください。
    ただし、開発中のためスクリプトの仕様が変更される可能性が高いです。
    command.txtには実装済みの特殊コマンドについての説明を記載しています。


5. 現在の仕様
    本鯖と比べておかしい(例えばプバが歩く、ポリンがアイテムを拾わないなど)点は、
    全て現在開発中に因るものです。
    現状としてキャラクタ系及びモンスター系のバグ報告は無視される可能性が高いです。

    バグ報告について必ず発生条件をお書き下さい。
    下にある報告用テンプレートを使って報告して頂くと助かります。
    報告先はエミュ板の開発スレにでも。
    ---- Athena v 2.0 (stable or develop) ----
    【gcc ver】gcc -vを実行時に表示される内容
    【動作システム】FreeBSD, Linux(ディストリビュージョンも), cygwinなど
    【発生内容】mapが落ちてしまった時の表示されていたデバッグ情報など具体的に書いてください。
    【操作内容】具体的にどんな操作を行ったかを書いてください。
    ------------------ END -------------------
    理想はテンプレに加えてmap.coreなどcoreファイルをUploaderにアップして頂くことですが
    問題のMapだけの状態にしcoreの吐く容量に注意してください。
    /*
        確認した限りでは324個ほどmapデータを読み込ませると、
         40MB近いcoreファイルを吐き出します @FreeBSD
         cygwinの場合はstackdumpというファイルになるそうです。
        しかし、coreファイルなどをgzip圧縮などすれば大幅に小さくなります。
         大凡30MBのcoreファイルが2.9MBほどになるようです。
        ですので、もしアップロードする場合はgzip圧縮など各自行ってください。
     */

    今回のリリースだけでなくHISTORYを作成すると大量に記述が必要な為省略しています。
    // 多い日だと本当に結構ありますので‥‥。


6. 祝辞
    今回このAthena開発版を出すに当たって感謝したい方々(順番不同)
        Lemming氏 (Project YARE)
        0052氏 (Uploader)
        35氏 (エミュ開発スレ)
        Johan Lindh氏(Author of memwatch)
        YARE forumのNPC情報を作成した方々
        weiss研究会BBSの様々な情報ファイルを作成した方々
        最後に、.coreファイル達


7. 免責事項
    Athena Projectは一切Athenaの動作に関する保証等は行いません。
    つまり、Athenaは無保証です。
    athena@project-yare.deに動作・操作等に関する質問などを送られても一切お答えできません。
    又Athenaを用いたことにより生じた被害・問題等の責任は一切Athena Projectは負いません。


8. 募集
    athenaの開発に参加したい//興味があるという方ご連絡下さい。
    我々は貴方の参加をお待ちしています。
    // 最新版が欲しいだけで何ら協力して頂けないという方はお断りです;-)
    [募集要項: プログラマ(2-3人)]
        年齢: 不問
        性別: 不問
        言語: 日本語が理解可能
        内容: C言語もしくはC++による開発。(特にネットワークやDBの経験が有る方大募集!)
    [募集要項: 翻訳(?人)]
        年齢: 不問
        性別: 不問
        言語: 日本語、英語が理解可能
        内容: 仏蘭西語、独逸語、西班牙語、伊太利亜語、泰(タイ)語、朝鮮語、中国語へ文献、サイトなどの翻訳
    連絡先: athena@project-yare.de 雑務担当まで。


9. English
     This release is just fixed some bugs in timer.c, script.c and map_athena1.conf.


(c) 2003 Athena Project.
