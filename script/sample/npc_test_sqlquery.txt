/*=========================================================================
 * SQLクエリ発行テスト
 *				created by Rayce (Auriga0107)
 *
 * ■ sqlquery関数はcsvアクセス命令/関数と同様の動作をSQLによって行う
 *    ための関数です。
 *    csvアクセス命令/関数よりも柔軟な操作が行える利点があります。
 *    ただしSQL文に関しては如何なる制限も設けていないので、便利である反面
 *    危険な動作も容易に実行できるという問題もあります。
 *    利用者の責任において十分注意して使ってください。
 *
 * ■ SQL文に文字列を含む場合には必ずstrescape関数を通してください。
 *-------------------------------------------------------------------------
 */
prontera.gat,155,195,4	script	じゃんけん	113,{
	mes "[じゃんけん]";
	mes "じゃんけんはどうですか？";
	next;
	switch(select("じゃんけんする","ランキングを見る","さようなら")) {
	case 1:
		mes "[じゃんけん]";
		mes "じゃ～んけ～ん・・・";
		next;
		set '@own,select("チョキ","グー","パー")-1;
		gmcommand "@emotion "+('@own+10);
		set '@enemy,rand(3);
		emotion '@enemy+10;
		mes "[じゃんけん]";
		mes "ポンッ！";
		next;
		if('@own == '@enemy) {
			mes "[じゃんけん]";
			mes "あいこです。";
			close;
		}
		if('@own != ('@enemy+1)%3) {
			mes "[じゃんけん]";
			mes "あなたの負けです。";
			close;
		}
		// 勝ったときはスコア記録
		set '@rid,getcharid(0);
		if(sqlquery("SELECT `score` FROM `janken` WHERE `char_id`=" + '@rid,'@score) > 0) {
			// 既にデータがある場合はスコア加算して更新
			set '@dummy,sqlquery("UPDATE `janken` SET `score`=" +('@score+1)+ " WHERE `char_id`=" + '@rid);
		}
		else {
			// スコア1点として新規登録
			// キャラ名は必ずstrescapeすること！
			set '@dummy,sqlquery("INSERT INTO `janken` (`char_id`, `name`, `score`) VALUES"
						"(" +'@rid+ ", '" +strescape(strcharinfo(0))+ "', 1)");
		}
		mes "[じゃんけん]";
		mes "あなたの勝ちです。";
		mes "現在のスコアは";
		mes "^FF0000" +('@score+1)+ "^000000 点です。";
		close;
	case 2:
		// 複数行のデータを配列変数に取得
		set '@max,sqlquery("SELECT `name`,`score` FROM `janken` ORDER BY `score` DESC",'@data$);
		if('@max > 0) {
			// '@maxの最大値は配列上限の128なので、表示可能なのは129位まで
			while(1) {
				mes "[じゃんけん]";
				for(set '@i,0; '@i < 6 && '@j < '@max; set '@i,'@i+1) {
					mes ('@j+1) + "位：" +'@data$['@j][0]+ " [^FF0000" +'@data$['@j][1]+ "^000000]";
					set '@j,'@j+1;
				}
				if('@j >= '@max) {
					break;
				}
				next;
			}
		}
		else {
			mes "[じゃんけん]";
			mes "ランキングはありません。";
		}
		close;
	case 3:
		mes "[じゃんけん]";
		mes "またどうぞ。";
		close;
	}

OnInit:
	// CREATEのGRANTがあるなら以下を有効にする
	// 無効であれば自前でテーブルを作成すること
	/*
	if(sqlquery(
		"CREATE TABLE IF NOT EXISTS `janken`"
		"(`char_id` int(11) NOT NULL DEFAULT '0',"
		"`name` varchar(255) NOT NULL DEFAULT '',"
		"`score` int(11) NOT NULL DEFAULT '0',"
		"PRIMARY KEY (`char_id`)) TYPE = MyISAM") < 0
	) {
		hideonnpc;
	}
	*/
	end;
}
