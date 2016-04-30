//==============================================================================
//Ragnarok Online SmileGirl Script
//==============================================================================
-	script	SmileGirl	92,{
	mes "[スマイルガール]";
	mes "こんにちは～";
	mes "スマイルガールです。";
	mes "何をお手伝いしましょうか？";
	next;
	switch (select("^3355ffスマイルマスク^000000について","^3355ffスマイルマスク^000000を製作","会話を終了")) {
	case 1:
		mes "[スマイルガール]";
		mes "^3355ffトリスタン３世^000000国王陛下の命令により";
		mes "明るいミッドガッツ王国を作るため";
		mes "実施中のイベントです。";
		mes "^3355ff「国民に笑顔を！」^000000";
		mes "サービス担当の";
		mes "^3355ff「スマイルガール」^000000です。";
		next;
		mes "[スマイルガール]";
		mes "簡単な材料で";
		mes "皆様に^3355ff「スマイルマスク」^000000を";
		mes "作って差し上げます。";
		mes "必要な材料は以下の通りです。";
		next;
		mes "[スマイルガール]";
		mes "^3355ffゼロピー 10 個";
		mes "綿毛 10 個";
		mes "クローバー 10 個^000000";
		next;
		mes "[スマイルガール]";
		mes "このイベントをきっかけに、";
		mes "私だけでなく、みなさんが";
		mes "笑顔で生きていける";
		mes "世界を作りましょう。";
		close;
	case 2:
		if(countitem(909)<10 || countitem(914)<10 || countitem(705)<10) {
			mes "[スマイルガール]";
			mes "あ、残念ですが";
			mes "スマイルマスク製作に必要な";
			mes "アイテムが不足しています。";
			mes "^3355ffゼロピー 10 個";
			mes "綿毛 10 個";
			mes "クローバー 10 個^000000";
			mes "が必要です。";
			close;
		}
		mes "[スマイルガール]";
		mes "はい、出来上がりです！";
		mes "スマイルマスクをどうぞ～";
		delitem 909,10;
		delitem 914,10;
		delitem 705,10;
		getitem 2278,1;
		next;
		mes "[スマイルガール]";
		mes "トリスタン3世陛下は";
		mes "明るいミッドガッツ王国を作るため";
		mes "国が最善を尽くすことを";
		mes "約束してくださいました。";
		next;
		mes "[スマイルガール]";
		mes "以上";
		mes "ミッドガッツ広報からの";
		mes "お知らせでした。";
		close;
	case 3:
		mes "[スマイルガール]";
		mes "ご利用ありがとうございます。";
		mes "私達のルーンミッドガッツ王国は";
		mes "いつも明るい国を創り上げるため";
		mes "たゆまぬ努力をして参ります。";
		next;
		mes "[スマイルガール]";
		mes "国民の皆さんのご協力を";
		mes "お願い申し上げます。";
		mes "以上";
		mes "ミッドガッツ広報からでした！";
		close;
	}
}

prontera.gat,157,196,4	duplicate(SmileGirl)	スマイルマスク職員	92
aldebaran.gat,136,135,4	duplicate(SmileGirl)	スマイルマスク職員	92
geffen.gat,119,107,4	duplicate(SmileGirl)	スマイルマスク職員	92
alberta.gat,113,53,4	duplicate(SmileGirl)	スマイルマスク職員	92
payon.gat,186,104,5	duplicate(SmileGirl)	スマイルマスク職員	92
izlude.gat,129,118,4	duplicate(SmileGirl)	スマイルマスク職員	92
morocc.gat,158,97,4	duplicate(SmileGirl)	スマイルマスク職員	92
