//= Athena Script ==============================================================
// Ragnarok Online MakeGlorias Script	by refis
//==============================================================================

//============================================================
// グロリアス
//------------------------------------------------------------
yuno.gat,335,38,2	script	グロリアス#yuno	813,{
	mes "[グロリアス]";
	mes "よく来たな。";
	mes "ワシは、グロリアス。";
	mes "特殊なアイテムを";
	mes "製造しておるブラックスミスじゃ。";
	next;
	mes "[グロリアス]";
	mes "最近、世の中に出回るようになった";
	mes "「GvGコイン」、「アリーナコイン」、";
	mes "「ターボトラックコイン」、";
	mes "「カプラコイン」、";
	mes "「エンドレスタワーコイン」を";
	mes "知っておるかね？";
	next;
	mes "[グロリアス]";
	mes "このコイン、";
	mes "実に不思議な力を秘めておってな。";
	mes "せっせと集めておるんじゃが、";
	mes "とにかく枚数が必要でな。";
	next;
	mes "[グロリアス]";
	mes "そこで、ワシの作った";
	mes "特殊なアイテムと";
	mes "5種類のコインと交換をして";
	mes "集めておるんじゃよ。";
	next;
	mes "[グロリアス]";
	mes "ちなみにワシのアイテムは、";
	mes "強力すぎるが故に";
	mes "幾つか制約を付けておる。";
	mes "他人に渡したり、カートに入れたり、";
	mes "カプラサービスに預けたり、";
	mes "地面に落としたりは、絶対にできん。";
	next;
	mes "[グロリアス]";
	mes "どうしても手放したいと思ったら、";
	mes "街の道具屋などに渡せばいい。";
	mes "ワシの手元に戻ってくるように";
	mes "話をつけてあるからのう。";
	next;
	mes "[グロリアス]";
	mes "ただし、厳しい制約の分だけ";
	mes "能力の高さは折り紙付きじゃ！";
	mes "望むのであれば、お主の持っている";
	mes "コインとワシの作ったアイテムを";
	mes "交換したいのじゃが、どうじゃろうか？";
	next;
	switch(select("武器と交換","防具と交換","やめる")) {
	case 1:
		mes "[グロリアス]";
		mes "フム……";
		mes "武器との交換を望むのか。";
		mes "どの武器がいいかね？";
		next;
		switch(select(
			"グロリアスダマスカス","グロリアスフランベルジェ","グロリアスレイピア",
			"グロリアスホーリーアヴェンジャー","グロリアスクレイモア","グロリアススピア",
			"グロリアスランス","グロリアスクリーヴァー","グロリアスツーハンドアックス",
			"グロリアスモーニングスター","グロリアスブラッディロア","グロリアスジャマダハル",
			"グロリアスタブレット","グロリアス黙示録","グロリアスハンターボウ",
			"グロリアスクロー","グロリアスフィスト","グロリアスアークワンド",
			"グロリアス治癒の杖","グロリアスウィザードスタッフ",
			"グロリアスギター","グロリアスラリエット",
			"グロリアスハンドガン","グロリアスライフル","グロリアスガトリングガン",
			"グロリアスショットガン","グロリアスグレネードガン","グロリアス風魔手裏剣"
			)) {
		case 1:		//グロリアスダマスカス
			set '@type$,"短剣";
			set '@gain,13042;
			break;
		case 2:		//グロリアスフランベルジェ
			set '@type$,"片手剣";
			set '@gain,13416;
			break;
		case 3:		//グロリアスレイピア
			set '@type$,"片手剣";
			set '@gain,13417;
			break;
		case 4:		//グロリアスホーリーアヴェンジャー
			set '@type$,"片手剣";
			set '@gain,13418;
			break;
		case 5:		//グロリアスクレイモア
			set '@type$,"両手剣";
			set '@gain,1187;
			break;
		case 6:		//グロリアススピア
			set '@type$,"片手槍";
			set '@gain,1426;
			break;
		case 7:		//グロリアスランス
			set '@type$,"両手槍";
			set '@gain,1486;
			break;
		case 8:		//グロリアスクリーヴァー
			set '@type$,"片手斧";
			set '@gain,1310;
			break;
		case 9:		//グロリアスツーハンドアックス
			set '@type$,"両手斧";
			set '@gain,1382;
			break;
		case 10:	//グロリアスモーニングスター
			set '@type$,"鈍器";
			set '@gain,1546;
			break;
		case 11:	//グロリアスブラッディロア
			set '@type$,"カタール";
			set '@gain,1281;
			break;
		case 12:	//グロリアスジャマダハル
			set '@type$,"カタール";
			set '@gain,1282;
			break;
		case 13:	//グロリアスタブレット
			set '@type$,"本";
			set '@gain,1576;
			break;
		case 14:	//グロリアス黙示録
			set '@type$,"本";
			set '@gain,1577;
			break;
		case 15:	//グロリアスハンターボウ
			set '@type$,"弓";
			set '@gain,1743;
			break;
		case 16:	//グロリアスクロー
			set '@type$,"爪";
			set '@gain,1826;
			break;
		case 17:	//グロリアスフィスト
			set '@type$,"爪";
			set '@gain,1827;
			break;
		case 18:	//グロリアスアークワンド
			set '@type$,"片手杖";
			set '@gain,1640;
			break;
		case 19:	//グロリアス治癒の杖
			set '@type$,"片手杖";
			set '@gain,1641;
			break;
		case 20:	//グロリアスウィザードスタッフ
			set '@type$,"両手杖";
			set '@gain,2002;
			break;
		case 21:	//グロリアスギター
			set '@type$,"楽器";
			set '@gain,1927;
			break;
		case 22:	//グロリアスラリエット
			set '@type$,"鞭";
			set '@gain,1981;
			break;
		case 23:	//グロリアスハンドガン
			set '@type$,"ハンドガン";
			set '@gain,13110;
			break;
		case 24:	//グロリアスライフル
			set '@type$,"ライフル";
			set '@gain,13176;
			break;
		case 25:	//グロリアスガトリングガン
			set '@type$,"ガトリングガン";
			set '@gain,13177;
			break;
		case 26:	//グロリアスショットガン
			set '@type$,"ショットガン";
			set '@gain,13178;
			break;
		case 27:	//グロリアスグレネードガン
			set '@type$,"グレネードガン";
			set '@gain,13179;
			break;
		case 28:	//グロリアス風魔手裏剣
			set '@type$,"風魔手裏剣";
			set '@gain,13307;
			break;
		}
		mes "[グロリアス]";
		mes '@type$+ "の";
		mes "「^FF0000" +getitemname('@gain)+ "^000000」と";
		mes "交換に必要なコインは、";
		mes "GvGコイン 100枚、";
		mes "アリーナコイン 200枚、";
		mes "ターボトラックコイン 200枚、";
		mes "カプラコイン 150枚、";
		mes "エンドレスタワーコイン 50枚じゃ。";
		next;
		mes "[グロリアス]";
		mes "今ならコインではなく";
		mes "「^FF0000グロリアス武器交換チケット^000000」";
		mes "1枚との交換も行っておるぞ。";
		next;
		mes "[グロリアス]";
		mes "「^FF0000" +getitemname('@gain)+ "^000000」と";
		mes "交換するかね？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[グロリアス]";
			mes "なんじゃ、止めるのか？";
			mes "まあ、好きにしたらええ。";
			close;
		}
		next;
		mes "[グロリアス]";
		mes "コインとチケットの";
		mes "どちらを使用するかね？";
		next;
		switch(select("コインで交換","チケットで交換","交換しない")) {
		case 1:
			if(countitem(6364) < 100 || countitem(6365) < 200 || countitem(6366) < 200 ||
				countitem(6367) < 150 || countitem(6368) < 50) {
				mes "[グロリアス]";
				mes "ん？";
				mes "必要なコインが足りないようだな。";
				mes "もう一度確認してから来なさい。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "‐所持アイテムの種類数が多い為";
				mes "　危険です。";
				mes "　所持アイテムを減らしてから、";
				mes "　再度話しかけてください‐";
				close;
			}
			delitem 6364,100;
			delitem 6365,200;
			delitem 6366,200;
			delitem 6367,150;
			delitem 6368,50;
			break;
		case 2:
			if(countitem(6798) < 1) {
				mes "[グロリアス]";
				mes "ん？";
				mes "チケットがないようだな。";
				mes "もう一度確認してから来なさい。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "‐所持アイテムの種類数が多い為";
				mes "　危険です。";
				mes "　所持アイテムを減らしてから、";
				mes "　再度話しかけてください‐";
				close;
			}
			delitem 6798,1;
			break;
		case 3:
			mes "[グロリアス]";
			mes "なんじゃ、止めるのか？";
			mes "まあ、好きにしたらええ。";
			close;
		}
		getitem '@gain,1;
		mes "[グロリアス]";
		mes "ワシの作った武器は、";
		mes "精錬するほどに";
		mes "特別な能力が増すのじゃ！";
		close;
	case 2:
		mes "[グロリアス]";
		mes "フム……";
		mes "防具との交換を望むのか。";
		mes "どの防具がいいかね？";
		next;
		switch(select(
			"グロリアスマフラー",
			"グロリアス普及用シューズ","グロリアス量産型シューズ","グロリアスシューズ",
			"グロリアス普及用スーツ","グロリアス量産型スーツ","グロリアススーツ",
			"グロリアス普及用リング","グロリアス量産型リング","グロリアスリング"
			)) {
		case 1:		//グロリアスマフラー
			set '@type$,"肩にかける物";
			set '@gain,2549;
			set '@ticket,6799;
			set '@gvg,200;
			set '@arena,400;
			set '@tarbo,400;
			set '@kafra,300;
			set '@endless,100;
			break;
		case 2:		//グロリアス普及用シューズ
			set '@type$,"靴";
			set '@gain,2446;
			set '@ticket,6799;
			set '@gvg,10;
			set '@arena,20;
			set '@tarbo,20;
			set '@kafra,50;
			set '@endless,5;
			break;
		case 3:		//グロリアス量産型シューズ
			set '@type$,"靴";
			set '@gain,2445;
			set '@ticket,6799;
			set '@gvg,30;
			set '@arena,50;
			set '@tarbo,50;
			set '@kafra,100;
			set '@endless,20;
			break;
		case 4:		//グロリアスシューズ
			set '@type$,"靴";
			set '@gain,2444;
			set '@ticket,6799;
			set '@gvg,200;
			set '@arena,400;
			set '@tarbo,400;
			set '@kafra,300;
			set '@endless,100;
			break;
		case 5:		//グロリアス普及用スーツ
			set '@type$,"鎧";
			set '@gain,2396;
			set '@ticket,6799;
			set '@gvg,10;
			set '@arena,20;
			set '@tarbo,20;
			set '@kafra,50;
			set '@endless,5;
			break;
		case 6:		//グロリアス量産型スーツ
			set '@type$,"鎧";
			set '@gain,2395;
			set '@ticket,6799;
			set '@gvg,30;
			set '@arena,50;
			set '@tarbo,50;
			set '@kafra,100;
			set '@endless,20;
			break;
		case 7:		//グロリアススーツ
			set '@type$,"鎧";
			set '@gain,2394;
			set '@ticket,6799;
			set '@gvg,200;
			set '@arena,400;
			set '@tarbo,400;
			set '@kafra,300;
			set '@endless,100;
			break;
		case 8:		//グロリアス普及用リング
			set '@type$,"アクセサリー";
			set '@gain,2774;
			set '@ticket,6800;
			set '@gvg,10;
			set '@arena,20;
			set '@tarbo,20;
			set '@kafra,50;
			set '@endless,5;
			break;
		case 9:		//グロリアス量産型リング
			set '@type$,"アクセサリー";
			set '@gain,2773;
			set '@ticket,6800;
			set '@gvg,100;
			set '@arena,200;
			set '@tarbo,200;
			set '@kafra,150;
			set '@endless,50;
			break;
		case 10:	//グロリアスリング
			set '@type$,"アクセサリー";
			set '@gain,2772;
			set '@ticket,6800;
			set '@gvg,1000;
			set '@arena,2000;
			set '@tarbo,2000;
			set '@kafra,1000;
			set '@endless,800;
			break;
		}
		mes "[グロリアス]";
		mes '@type$+ "の";
		mes "「^FF0000" +getitemname('@gain)+ "^000000」と";
		mes "交換に必要なコインは、";
		mes "GvGコイン " +'@gvg+ "枚、";
		mes "アリーナコイン " +'@arena+ "枚、";
		mes "ターボトラックコイン " +'@tarbo+ "枚、";
		mes "カプラコイン " +'@kafra+ "枚、";
		mes "エンドレスタワーコイン " +'@endless+ "枚じゃ。";
		next;
		mes "[グロリアス]";
		mes "今ならコインではなく";
		mes "「^FF0000" +getitemname('@ticket)+ "^000000」";
		mes "1枚との交換も行っておるぞ。";
		next;
		mes "[グロリアス]";
		mes "「^FF0000" +getitemname('@gain)+ "^000000」と";
		mes "交換するかね？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[グロリアス]";
			mes "なんじゃ、止めるのか？";
			mes "まあ、好きにしたらええ。";
			close;
		}
		next;
		mes "[グロリアス]";
		mes "コインとチケットの";
		mes "どちらを使用するかね？";
		next;
		switch(select("コインで交換","チケットで交換","交換しない")) {
		case 1:
			if(countitem(6364) < '@gvg || countitem(6365) < '@arena || countitem(6366) < '@tarbo ||
				countitem(6367) < '@kafra || countitem(6368) < '@endless) {
				mes "[グロリアス]";
				mes "ん？";
				mes "必要なコインが足りないようだな。";
				mes "もう一度確認してから来なさい。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "‐所持アイテムの種類数が多い為";
				mes "　危険です。";
				mes "　所持アイテムを減らしてから、";
				mes "　再度話しかけてください‐";
				close;
			}
			delitem 6364,'@gvg;
			delitem 6365,'@arena;
			delitem 6366,'@tarbo;
			delitem 6367,'@kafra;
			delitem 6368,'@endless;
			break;
		case 2:
			if(countitem('@ticket) < 1) {
				mes "[グロリアス]";
				mes "ん？";
				mes "チケットがないようだな。";
				mes "もう一度確認してから来なさい。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "‐所持アイテムの種類数が多い為";
				mes "　危険です。";
				mes "　所持アイテムを減らしてから、";
				mes "　再度話しかけてください‐";
				close;
			}
			delitem '@ticket,1;
			break;
		case 3:
			mes "[グロリアス]";
			mes "なんじゃ、止めるのか？";
			mes "まあ、好きにしたらええ。";
			close;
		}
		getitem '@gain,1;
		mes "[グロリアス]";
		mes "ワシの防具は、";
		mes "強力じゃぞ！";
		close;
	case 3:
		mes "[グロリアス]";
		mes "なんじゃ、止めるのか？";
		mes "まあ、好きにしたらええ。";
		close;
	}
}

//============================================================
// エンドレスタワーコイン交換NPC
//------------------------------------------------------------
alberta.gat,202,79,2	script	灰色の魔女	803,{
	mes "[灰色の魔女]";
	mes "私は、灰色の魔女。";
	mes "エンドレスタワーで手に入る";
	mes "闇の灰を研究する者さ。";
	next;
	mes "[灰色の魔女]";
	mes "あんた、エンドレスタワーに";
	mes "登った事があるかい？";
	mes "もし、闇の灰を持っているなら";
	mes "エンドレスタワーコインと";
	mes "交換しないかね？";
	next;
	switch(select("交換する","交換しない","闇の灰って？","何に使うの？")) {
	case 1:
		break;
	case 2:
		mes "[灰色の魔女]";
		mes "おや？";
		mes "交換しないのかい？";
		mes "まあ、私は構わないがね……";
		close;
	case 3:
		mes "[灰色の魔女]";
		mes "闇の灰を知らないって？";
		mes "それでもあんた冒険者かい？";
		next;
		mes "[灰色の魔女]";
		mes "闇の灰とは、エンドレスタワーで";
		mes "一定階層以上登ると手に入るアイテムで";
		mes "「はじまりの松明」という松明に使うと";
		mes "特定階層にワープさせてくれるという";
		mes "不思議な灰さ……";
		close;
	case 4:
		mes "[灰色の魔女]";
		mes "闇の灰を一体何に使うかだって？";
		mes "ヒッヒッヒ……";
		mes "世の中には知らない方が";
		mes "幸せな事もあるんだよ……";
		close;
	}
	mes "[灰色の魔女]";
	mes "そうかいそうかい。";
	mes "では、闇の灰 1個につき、";
	mes "一枚のエンドレスタワーコインと";
	mes "交換しようじゃないか。";
	next;
	mes "[灰色の魔女]";
	mes "もし気が変わったなら、";
	mes "0と言っておくれ。";
	mes "何枚欲しいんだい？";
	next;
	input '@num;
	if('@num == 0) {
		mes "[灰色の魔女]";
		mes "気が変わったのかい？";
		mes "では、またの機会にしようか。";
		close;
	}
	if('@num < 0 || '@num > 30000) {
		mes "[灰色の魔女]";
		mes "数が正しくないようだね。";
		close;
	}
	if(countitem(6000) < '@num) {
		mes "[灰色の魔女]";
		mes "闇の灰の数が足りないようだね。";
		mes "さっさとエンドレスタワーに";
		mes "登っておいで！";
		close;
	}
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　危険です。";
		mes "　所持アイテムを減らしてから、";
		mes "　再度話しかけてください‐";
		close;
	}
	delitem 6000,'@num;
	getitem 6368,'@num;
	mes "[灰色の魔女]";
	mes "ありがたい。";
	mes "これで更に研究が進むだろう。";
	mes "ヒッヒッヒ……";
	close;
}
