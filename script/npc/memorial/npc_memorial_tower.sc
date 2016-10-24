//= Auriga Script ==============================================================
// Ragnarok Online Endless Tower Script	by Blaze
//- Registry -------------------------------------------------------------------
// TOWER_1QUE -> 0～4
//==============================================================================

//============================================================
// 転送NPC
//------------------------------------------------------------
alberta.gat,214,77,6	script	艦長ヤンセン	709,{
	if(BaseLevel < 50) {
		mes "[艦長ヤンセン]";
		mes "ああ……";
		mes "わしは再び海に出られるだろうか……";
		next;
		mes "[艦長ヤンセン]";
		mes "うん？";
		mes "君は……冒険者か？";
		mes "……しかし、^FF0000レベル50未満^000000と見える。";
		mes "まだまだ青いな……";
		mes "ふう……";
		close;
	}
	switch(TOWER_1QUE) {
	case 0:
		mes "[艦長ヤンセン]";
		mes "ん、君は……";
		mes "冒険者だね？";
		mes "しかもなかなかの実力がありそうだ。";
		next;
		mes "[艦長ヤンセン]";
		mes "初対面で失礼だとは思うが、";
		mes "君を見込んで";
		mes "どうしても頼みたいことがある……";
		next;
		mes "[艦長ヤンセン]";
		mes "^0000FF10,000^000000 Zenyを";
		mes "わしに寄付してくれないか？";
		next;
		if(select("当然断る","^0000FF10,000Zeny寄付する^000000") == 1) {
			mes "[艦長ヤンセン]";
			mes "……そうか、当然だろうな。";
			mes "すまない。";
			mes "失礼したな、若者よ。";
			close;
		}
		mes "[艦長ヤンセン]";
		mes "!!";
		mes "ほ、本当か!?";
		mes "わしに寄付してくれると言うのか!?";
		mes "なんと親切な方だ……！";
		next;
		if(Zeny < 10000) {
			mes "[艦長ヤンセン]";
			mes "しかし……気持ちはうれしいが、";
			mes "君が持っているZenyでは";
			mes "足りないようだ……";
			mes "すまない、ありがとう若者よ。";
			close;
		}
		mes "-10,000 Zenyを";
		mes "　船乗りに寄付した-";
		next;
		mes "[艦長ヤンセン]";
		mes "本当にありがとう!!";
		mes "まだこの世に君のような";
		mes "若者がいるとは……";
		mes "この恩は一生忘れない。";
		mes "これで船の資材が用意できる！";
		set Zeny,Zeny-10000;
		set TOWER_1QUE,1;
		next;
		mes "-船の資材？";
		mes "　一体何をするんだろう……";
		mes "　もう少し話を聞いてみよう-";
		close;
	case 1:
		mes "-船乗りは笑顔で近くの";
		mes "　航海用品売り場に行き、";
		mes "　色々な品を注文しているようだ。";
		mes "　せっかくなので";
		mes "　事情を聞いてみることにしよう-";
		next;
		mes "-買い物を終えた船乗りが";
		mes "　こちらに気付き、近寄ってきた-";
		next;
		mes "[艦長ヤンセン]";
		mes "ふむ、初対面にも関わらず";
		mes "わしの話を聞いてくれるとは、";
		mes "今時珍しい冒険者だ。";
		mes "申し遅れた、わしはヤンセンという。";
		next;
		mes "[艦長ヤンセン]";
		mes "ところで君は";
		mes "遠い海に出ることに興味はあるかね？";
		next;
		switch(select("航海経験がある","興味ある","興味ない")) {
		case 1:
			mes "[艦長ヤンセン]";
			mes "ほお～、ならば";
			mes "基本はできているようだな。";
			break;
		case 2:
			mes "[艦長ヤンセン]";
			mes "そうかそうか、";
			mes "ならば話を聞いてくれ。";
			break;
		case 3:
			mes "[艦長ヤンセン]";
			mes "何？　夢のないやつだな。";
			mes "まあいい、とにかく";
			mes "話を聞いてくれ。";
			break;
		}
		mes "こう見えてもわしは昔、";
		mes "大船団を率いる艦長だった。";
		mes "今は一隻だけになったがね。";
		next;
		mes "[艦長ヤンセン]";
		mes "あの大陸の彼方にある海は";
		mes "まだまだ未知の世界同然だ。";
		mes "わしはその世界に破れたのだが。";
		next;
		mes "-ヤンセンは自分の";
		mes "　昔話を話しはじめた。";
		mes "　暇だったのでその昔話に付き合った-";
		next;
		mes "-本当かどうか分からない内容が";
		mes "　ほとんどだったが……";
		mes "　中には興味深い話もあった。";
		mes "　それは雲をも突き抜けているという";
		mes "　^0000FF巨大な塔^000000の話だった-";
		set TOWER_1QUE,2;
		close;
	case 2:
		mes "[艦長ヤンセン]";
		mes "……ん、どこまで話したかな。";
		mes "ああ、そうそう！";
		mes "それで難破したわしの船は";
		mes "止むを得ずその巨大な塔の所で";
		mes "暫く留まるしかなかった。";
		next;
		mes "[艦長ヤンセン]";
		mes "食料も底をつき、このままでは全員";
		mes "餓死してしまうという状況の中、";
		mes "船員の何人かが食料を求め、";
		mes "塔の中に入ったが……";
		mes "誰一人戻ってこなかった。";
		next;
		mes "[艦長ヤンセン]";
		mes "生き残るために不要な物を全て捨て、";
		mes "島で手に入れた少量の水と食用植物で";
		mes "再び海に出た……";
		next;
		mes "[艦長ヤンセン]";
		mes "それから何日経ったかわからないが、";
		mes "ある日、陸地に";
		mes "たどり着くことができた。";
		mes "だが……";
		mes "結局生き残りはわし一人だけだった。";
		next;
		mes "[艦長ヤンセン]";
		mes "それから、";
		mes "わしは決心したのだ。";
		mes "塔に入って戻ってこれなかった、";
		mes "仲間たちを探すとな。";
		mes "わしの命が続く限りの使命だ。";
		next;
		mes "[艦長ヤンセン]";
		mes "そして、君のような心優しい";
		mes "冒険者のおかげで";
		mes "塔まで航海するための資金ができた。";
		mes "これで使命を果たすことができる。";
		mes "本当にありがとう。";
		next;
		menu "一人で行くつもりですか？",-;
		mes "[艦長ヤンセン]";
		mes "ああ、その通りだ。";
		mes "……とても危険な場所だ。";
		mes "自分も行ってみようなどと";
		mes "考えているのか？";
		next;
		mes "[艦長ヤンセン]";
		mes "君のような若者がそこで";
		mes "命を落とすようなことが";
		mes "あってはいかん。";
		next;
		menu "行ってみたいです",-;
		mes "[艦長ヤンセン]";
		mes "………………";
		mes "そうか、そこまで言うなら";
		mes "わしも止めはしない。しかし";
		mes "準備とかもあるだろうから";
		mes "全ての準備ができたらわしに";
		mes "話しかけてくれ。";
		next;
		mes "[艦長ヤンセン]";
		mes "あ……それと！";
		mes "君を心より歓迎するよ。";
		mes "勇敢な航海士さんよ！";
		set TOWER_1QUE,3;
		close;
	case 3:
		mes "[艦長ヤンセン]";
		mes "準備ができたか？";
		mes "では、そろそろ行くとするか？";
		next;
		if(select("^0000FF行きましょう！^000000","まだ準備が……") == 2) {
			mes "[艦長ヤンセン]";
			mes "そうか。";
			mes "では準備ができたら";
			mes "声をかけてくれ。";
			close;
		}
		mes "[艦長ヤンセン]";
		mes "よし！";
		mes "では出航だ!!";
		close2;
		set TOWER_1QUE,4;
		warp "e_tower.gat",70,114;
		end;
	case 4:
		mes "[艦長ヤンセン]";
		mes "君か。";
		mes "再び出航するには";
		mes "若干の資材が必要だ。";
		mes "^0000FF10,000^000000Zenyあれば出航のための";
		mes "全ての準備ができる。";
		next;
		if(select("またにします","^0000FFすぐ行きましょう！^000000") == 1) {
			mes "[" +strcharinfo(0)+ "]";
			mes "今は余裕がありません。";
			mes "残念ですが、今度にします。";
			next;
			mes "[艦長ヤンセン]";
			mes "そうか……";
			mes "では行きたくなったら";
			mes "いつでもわしのところに";
			mes "来てくれ。";
			close;
		}
		if(Zeny < 10000) {
			mes "[艦長ヤンセン]";
			mes "残念だが、そのZenyじゃ";
			mes "全ての資材は買えないな。";
			close;
		}
		mes "[艦長ヤンセン]";
		mes "…………よし！";
		mes "これで全ての準備が整った。";
		mes "では早速出航だ！";
		close2;
		set Zeny,Zeny-10000;
		warp "e_tower.gat",70,114;
		end;
	}
}

//============================================================
// 説明NPC
//------------------------------------------------------------
e_tower.gat,80,108,3	script	書置き	857,{
	mes "[書置き]";
	mes "……この場所に挑む";
	mes "後続の冒険者たちのために";
	mes "これを記す。";
	mes "初めてここに挑む冒険者は";
	mes "特に参考にして欲しい。";
	next;
	switch(select("^FF0000時間^000000について","^FF0000制限^000000について","^FF0000はじまりの松明^000000について","^FF0000注意点^000000について")) {
	case 1:
		mes "[書置き]";
		mes "この塔に入るための鍵を作成すると、";
		mes "何故かわからないが";
		mes "他のパーティーと干渉しない";
		mes "塔の空間が生成される。";
		next;
		mes "[書置き]";
		mes "そして塔の中に一度でも";
		mes "立ち入った瞬間、";
		mes "^FF0000刻の呪い^000000を受ける。";
		mes "一度生成された空間が";
		mes "維持される時間は";
		mes "^0000FF4時間^000000のようだ。";
		next;
		mes "[書置き]";
		mes "一度外に出たり、4時間経過して";
		mes "空間が消滅した後、再度";
		mes "鍵を作成したり、中に入るには";
		mes "一度立ち入った時から";
		mes "^0000FF約1週間^000000の時間を要する。";
		next;
		mes "[書置き]";
		mes "何度も気軽に挑戦できるものではない。";
		mes "準備は入念に行ったほうがいいだろう。";
		break;
	case 2:
		mes "[書置き]";
		mes "塔の内部は特殊な呪術のような";
		mes "力が張り巡らされているようだ。";
		mes "そのため一部スキルやアイテムが";
		mes "効果を発揮しないようだ。";
		next;
		mes "[書置き]";
		mes "スキルでは、";
		mes "^0000FFテレポート、アイスウォール、";
		mes "スパイダーウェブ、インティミデイト、";
		mes "アブラカタブラ^000000が使えない。";
		mes "また^0000FF太陽と月と星の感情^000000による";
		mes "登録も不可能だ。";
		next;
		mes "[書置き]";
		mes "アイテムでは、";
		mes "^0000FFハイローゾイストカード";
		mes "アゾート^000000といった";
		mes "モンスターを変換する効果が";
		mes "無効化されるようだ。";
		next;
		mes "[書置き]";
		mes "当然、テレポートと同じ効果の";
		mes "^0000FFハエの羽^000000なども";
		mes "使うことができない。";
		mes "以上を踏まえて準備をするといい。";
		break;
	case 3:
		mes "[書置き]";
		mes "塔に入った直後、";
		mes "ふたつの松明が見えるはずだ。";
		mes "そのうちの北側のものは";
		mes "^0000FFはじまりの松明^000000と呼ばれている。";
		next;
		mes "[書置き]";
		mes "このはじまりの松明は、";
		mes "塔に入った直後は一切反応がないが、";
		mes "しばらく時間が経てば";
		mes "文字が浮かび上がり";
		mes "調べられるようになっているはずだ。";
		next;
		mes "[書置き]";
		mes "このはじまりの松明に、";
		mes "^0000FF闇の灰^000000というものを撒くと";
		mes "闇夜の覇王に近づくことが";
		mes "出来るらしい。";
		next;
		mes "[書置き]";
		mes "詳しいことはわからないが、";
		mes "何らかの手段で^0000FF闇の灰^000000を入手し、";
		mes "撒くことによって";
		mes "上層の階に移動することが";
		mes "可能なようだ。";
		next;
		mes "[書置き]";
		mes "しかし安易に考えてはならない。";
		mes "この塔は、1階から順に";
		mes "モンスターどもを全滅することで";
		mes "上の階へと移動することが出来る。";
		next;
		mes "[書置き]";
		mes "上層に行くに従って";
		mes "より強力なモンスターが出現する。";
		mes "移動した瞬間にやられてしまっては";
		mes "元も子もない。";
		mes "十分注意したほうがいいだろう。";
		break;
	case 4:
		mes "[書置き]";
		mes "この塔では、";
		mes "その階に出現するモンスターを";
		mes "全滅させることで上の階への門が開く。";
		mes "その際、この塔の管理者は";
		mes "「戦って全滅させたか」を";
		mes "監視しているようだ……";
		next;
		mes "[書置き]";
		mes "私は一度、つい出来心で";
		mes "出てきたモンスターを";
		mes "^FF0000テイミング^000000してしまった。";
		mes "しかしテイミング成功で消滅した";
		mes "モンスターは、倒した数として";
		mes "認められず……";
		next;
		mes "[書置き]";
		mes "挑戦を諦めざるを得なかった。";
		mes "^FF0000決してモンスターを";
		mes "テイミングしてはならない。^000000";
		mes "もししてしまった場合は、";
		mes "生成されたダンジョンを";
		mes "破棄するほかない。注意してくれ。";
		break;
	}
	next;
	mes "[書置き]";
	mes "諸君の健闘と無事を祈る。";
	mes " ";
	mes "^0000FF文責 : 名も無き冒険者たち一同^000000";
	close;
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
e_tower.gat,81,105,0	script	塔の守護石	406,{
	if(getonlinepartymember() < 1) {
		mes "【塔の守護石】";
		mes "1人以上のパーティーを組んでから";
		mes "再試行せよ。";
		close;
	}
	if(checkquest(12058)) {
		if(checkquest(12058)&2) {
			delquest 12058;
			mes "【塔の守護石】";
			mes "塔の^FF0000刻の呪い^000000が解けた。";
			mes "塔の鍵の作成、及び塔への";
			mes "入場が可能になった。";
			close;
		}
		mes "【塔の守護石】";
		mes "塔に足を踏み入れたため、";
		mes "^FF0000刻の呪い^000000を受けている状態。";
		mes "呪いが解けるまで";
		mes "鍵の作成、入場を行う資格はない。";
		next;
		switch(select("アルベルタに帰還","キャンセル")){
		case 1:
			mes "【塔の守護石】";
			mes "元の場所への帰還術を";
			mes "発動……";
			close2;
			warp "alberta.gat",223,36;
			end;
		case 2:
			mes "【塔の守護石】";
			mes "元の場所への帰還術の";
			mes "発動を中止……";
			close;
		}
	}
	else {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "【塔の守護石】";
			mes "資格ある代表の者よ。";
			mes "塔に入る鍵を作るか？";
			set '@str1$,"Endless Towerの鍵の作成";
			set '@str2$,"Endless Towerに入る";
		}
		else {
			mes "【塔の守護石】";
			mes "資格ある者よ。";
			mes "塔に入るか？";
			set '@str2$,"Endless Towerに入る";
		}
	}
	next;
	switch(select('@str1$,'@str2$,"アルベルタに帰還","キャンセル")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "【塔の守護石】";
			mes "代表権が無くなっている。";
			mes "再試行せよ。";
			close;
		}
		mdcreate "Endless Tower";
		mes "【塔の守護石】";
		mes "■パーティー名";
		mes "^0000FF" +getpartyname(getcharid(1))+ "^000000";
		mes "■パーティーリーダー";
		mes "^0000FF" +getpartyleader(getcharid(1))+ "^000000";
		mes " ";
		mes "^006400Endless Tower^000000の鍵の作成試行中。";
		next;
		mes "【塔の守護石】";
		mes "作成に成功した場合は";
		mes "再び守護石に話しかけ、";
		mes "『Endless Towerに入る』を";
		mes "選択することで入場が可能。";
		close;
	case 2:
		switch(mdenter("Endless Tower")) {
		case 0:	// エラーなし
			announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Endless Tower]に入場します",0x9,0x00FF99;
			setquest 12058;
			donpcevent getmdnpcname("TowerControl1")+ "::OnStart";
			end;
		case 1:	// パーティー未加入
			mes "【塔の守護石】";
			mes "Endless Tower に入る資格がない。";
			mes "パーティーに加入していない状態。";
			close;
		case 2:	// ダンジョン未作成
			mes "【塔の守護石】";
			mes "Endless Tower の鍵が";
			mes "存在しない。";
			mes "パーティーリーダーが鍵を";
			mes "作成していない状態。";
			close;
		default:	// その他エラー
			mes "【塔の守護石】";
			mes "不明なエラーが発生。";
			close;
		}
	case 3:
		mes "【塔の守護石】";
		mes "元の場所への帰還術を";
		mes "発動……";
		close2;
		warp "alberta.gat",223,36;
		end;
	case 4:
		close;
	}
}

//============================================================
// エンドレスタワー1F～25F
//------------------------------------------------------------
1@tower.gat,50,360,0	script	はじまりの松明	111,{
	mes "-松明に浮かんだ文-";
	mes " ";
	mes "^006600ここに^0000FF闇の灰^006600を撒いた者は、";
	mes "闇夜の覇王に近づくだろう……^000000";
	next;
	set @menu,select("^0000FF26階^000000","^00660051階^000000","^FF000076階^000000");
	if(countitem(6000) < @menu) {
		mes "-^FF0000警告^000000-";
		mes (@menu*25+1)+ "階に移動するためには";
		mes "^0000FF闇の灰^000000が^FF0000" +@menu+ "個^000000必要である。";
		close;
	}
	delitem 6000,@menu;
	announce "[" +strcharinfo(0)+ "]が " +(@menu*25+1)+ "階 へ移動します",0x9,0x00FF99;
	donpcevent getmdnpcname("TowerControl" +(@menu+1))+ "::OnStart";
	warp getmdmapname((@menu+1)+ "@tower.gat"),52,354;
	end;
}

1@tower.gat,0,0,0	script	TowerControl1	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,1;
	setarray 'mob[0][0],	// 1F
		1613,15,	// メタリン
		1242,5,		// マーリン
		1031,5,		// ポポリン
		1113,5,		// ドロップス
		1090,1,		// マスターリング
		1002,5,		// ポリン
	;
	setarray 'mob[1][0],	// 2F
		1106,20,	// デザートウルフ
		1092,1,		// さすらい狼
		1107,10,	// 子デザートウルフ
	;
	setarray 'mob[2][0],	// 3F
		1016,5,		// アーチャースケルトン
		1169,5,		// スケルワーカー
		1028,5,		// ソルジャースケルトン
		1152,5,		// オークスケルトン
		1071,5,		// パイレーツスケル
		1076,5,		// スケルトン
	;
	setarray 'mob[3][0],	// 4F
		1099,15,	// アルギオペ
		1139,5,		// マンティス
		1100,5,		// アルゴス
		1088,1,		// ボーカル
		1052,5,		// ロッカー
		1004,5,		// ホーネット
	;
	setarray 'mob[4][0],	// 5F
		//1086,1,	// 黄金蟲
		//1054,15,	// 雄盗蟲
		//1053,15,	// 雌盗蟲
		//1051,15,	// 盗蟲
		//1048,5,	// 盗蟲の卵
		// jRO配置
		1115,1,		// エドガ
		1243,20,	// サスカッチ
		1306,5,		// レイブオルマイ
		1517,5,		// 虎人
	;
	setarray 'mob[5][0],	// 6F
		1721,5,		// ドラゴンの卵
		1048,5,		// 盗蟲の卵
		1097,5,		// 蟻の卵
		1008,5,		// プパ
	;
	setarray 'mob[6][0],	// 7F
		1383,15,	// エクスプロージョン
		1111,15,	// ドレインリアー
		1627,15,	// ウィレス
		1005,15,	// ファミリアー
	;
	setarray 'mob[7][0],	// 8F
		1403,15,	// 銃奇兵
		1248,15,	// クルーザー
	;
	setarray 'mob[8][0],	// 9F
		1615,15,	// オブシディアン
		1040,15,	// ゴーレム
		1784,10,	// スタポ
	;
	setarray 'mob[9][0],	// 10F
		1059,1,		// ミストレス
		1303,25,	// ジャイアントホーネット
		1004,20,	// ホーネット
	;
	setarray 'mob[10][0],	// 11F
		1493,15,	// ドリアード
		1500,15,	// フェアリーフ
		1413,15,	// 老人参
		1162,5,		// ラフレシア
	;
	setarray 'mob[11][0],	// 12F
		1378,25,	// デーモンパンク
		1199,25,	// パンク
	;
	setarray 'mob[12][0],	// 13F
		1512,15,	// ヒェグン
		1188,15,	// ボンゴン
		1026,10,	// ムナック
	;
	setarray 'mob[13][0],	// 14F
		1213,15,	// ハイオーク
		1189,10,	// オークアーチャー
		1273,10,	// オークレディ
		1023,5,		// オークウォリアー
		1686,5,		// オークベイビー
	;
	setarray 'mob[14][0],	// 15F
		//1147,1,	// マヤー
		//1059,1,	// フリオニ
		//1105,15,	// デニーロ
		//1160,15,	// ピエール
		//1095,15,	// アンドレ
		//1097,5,	// 蟻の卵
		// jRO配置
		1147,1,		// マヤー
		1289,1,		// マヤパープル
		1105,15,	// デニーロ
		1160,15,	// ピエール
		1095,15,	// アンドレ
		1097,5,		// 蟻の卵
	;
	setarray 'mob[15][0],	// 16F
		1276,10,	// レイドリックアーチャー
		1189,10,	// オークアーチャー
		1253,10,	// ガーゴイル
		1016,10,	// アーチャースケルトン
	;
	setarray 'mob[16][0],	// 17F
		1264,10,	// 半漁人
		1101,10,	// バフォメット.Jr
		1065,15,	// ストラウフ
		1629,5,		// ヒルウィンド(槍)
	;
	setarray 'mob[17][0],	// 18F
		1209,25,	// クランプ
		1175,15,	// タロウ
	;
	setarray 'mob[18][0],	// 19F
		1108,10,	// デビアス
		1064,10,	// メガロドン
		1069,10,	// ソードフィッシュ
		1158,10,	// フェン
	;
	setarray 'mob[19][0],	// 20F
		1112,1,		// ドレイク
		1071,50,	// パイレーツスケル
	;
	setarray 'mob[20][0],	// 21F
		1693,10,	// プラズマ(黄)
		1696,10,	// プラズマ(紫)
		1695,5,		// プラズマ(緑)
		1697,5,		// プラズマ(青)
		1694,5,		// プラズマ(赤)
	;
	setarray 'mob[21][0],	// 22F
		1780,15,	// マスキプラー
		1781,15,	// ドロセラ
		1118,15,	// フローラ
		1068,15,	// ヒドラ
		1020,10,	// マンドラゴラ
		1162,10,	// ラフレシア
	;
	setarray 'mob[22][0],	// 23F
		1216,15,	// ペノメナ
		1044,10,	// オボンヌ
		1144,10,	// マルス
		1069,10,	// ソードフィッシュ
		1068,5,		// ヒドラ
	;
	setarray 'mob[23][0],	// 24F
		1131,15,	// ジョーカー
		1267,15,	// ジェスター
		1130,10,	// ジャック
	;
	setarray 'mob[24][0],	// 25F
		1307,15,	// キャットナインテイル
		1150,1,		// 月夜花
		1180,15,	// 九尾狐
	;
	setarray 'x,  9, 93,181,267,352;
	setarray 'y,351,267,180, 96,  9;
L_MobCall:
	disablenpc getmdnpcname("TowerGate" +'lv);
	set '@idx,'lv-1;
	set '@max,getarraysize('mob['@idx][0])/2;
	for(set '@i,0; '@i < '@max; set '@i,'@i+1)
		areamonster getmdmapname("1@tower.gat"),'x['@idx%5],'y['@idx/5],'x['@idx%5]+10,'y['@idx/5]+36,"--ja--",'mob['@idx]['@i*2],'mob['@idx]['@i*2+1],getmdnpcname("TowerControl1")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set 'count,getmapmobs(getmdmapname("1@tower.gat"),getmdnpcname("TowerControl1")+ "::OnKilled");
	if('count <= 0) {
		announce 'lv+ "階のすべてのモンスターを倒しました",0x9,0xFFFF00;
		enablenpc getmdnpcname("TowerGate"+'lv);
		if('lv%25 == 0)
			initnpctimer getmdnpcname("TowerGate"+'lv);
		else {
			set 'lv,'lv+1;
			callsub L_MobCall;
		}
	}
	else
		announce 'lv+ "階に残ったモンスター [" +'count+ "]体",0x9,0x00FF99;
	end;
}

1@tower.gat,12,393,0	warp	TowerGate1	2,2,1@tower.gat,136,354
1@tower.gat,96,393,0	warp	TowerGate2	2,2,1@tower.gat,224,354
1@tower.gat,184,393,0	warp	TowerGate3	2,2,1@tower.gat,310,354
1@tower.gat,270,393,0	warp	TowerGate4	2,2,1@tower.gat,395,354
1@tower.gat,355,393,0	warp	TowerGate5	2,2,1@tower.gat,52,270
1@tower.gat,12,309,0	warp	TowerGate6	2,2,1@tower.gat,136,270
1@tower.gat,96,309,0	warp	TowerGate7	2,2,1@tower.gat,224,270
1@tower.gat,184,309,0	warp	TowerGate8	2,2,1@tower.gat,310,270
1@tower.gat,270,309,0	warp	TowerGate9	2,2,1@tower.gat,395,270
1@tower.gat,355,309,0	warp	TowerGate10	2,2,1@tower.gat,52,183
1@tower.gat,12,222,0	warp	TowerGate11	2,2,1@tower.gat,136,183
1@tower.gat,96,222,0	warp	TowerGate12	2,2,1@tower.gat,224,183
1@tower.gat,184,222,0	warp	TowerGate13	2,2,1@tower.gat,310,183
1@tower.gat,270,222,0	warp	TowerGate14	2,2,1@tower.gat,395,183
1@tower.gat,355,222,0	warp	TowerGate15	2,2,1@tower.gat,52,99
1@tower.gat,12,138,0	warp	TowerGate16	2,2,1@tower.gat,136,99
1@tower.gat,96,138,0	warp	TowerGate17	2,2,1@tower.gat,224,99
1@tower.gat,184,138,0	warp	TowerGate18	2,2,1@tower.gat,310,99
1@tower.gat,270,138,0	warp	TowerGate19	2,2,1@tower.gat,395,99
1@tower.gat,355,138,0	warp	TowerGate20	2,2,1@tower.gat,52,12
1@tower.gat,12,51,0		warp	TowerGate21	2,2,1@tower.gat,136,12
1@tower.gat,96,51,0		warp	TowerGate22	2,2,1@tower.gat,224,12
1@tower.gat,184,51,0	warp	TowerGate23	2,2,1@tower.gat,310,12
1@tower.gat,270,51,0	warp	TowerGate24	2,2,1@tower.gat,395,12
1@tower.gat,355,51,0	script	TowerGate25	45,2,2,{
	if(getnpctimer(1))
		getitem 6000,1;
	donpcevent getmdnpcname("TowerControl2")+ "::OnStart";
	warp getmdmapname("2@tower.gat"),52,354;
	end;
OnTimer120000:
	stopnpctimer;
	end;
}

//============================================================
// エンドレスタワー26F～50F
//------------------------------------------------------------
2@tower.gat,0,0,0	script	TowerControl2	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,26;
	setarray 'mob[0][0],	// 26F
		1503,10,	// ジビット
		1410,10,	// 人面桃樹
		1497,10,	// ウドゥンゴーレム
		1495,10,	// フレイムシューター
		1033,5,		// エルダーウィロー
	;
	setarray 'mob[1][0],	// 27F
		1258,10,	// ゴブリンアーチャー
		1122,10,	// ゴブリン長男
		1123,5,		// ゴブリン次男
		1124,5,		// ゴブリン三男
		1125,5,		// ゴブリン四男
		1126,5,		// ゴブリン五男
	;
	setarray 'mob[2][0],	// 28F
		1194,30,	// アクラウス
		1255,15,	// ネレイド
		1256,15,	// ペスト
		1070,10,	// ククレ
	;
	setarray 'mob[3][0],	// 29F
		1260,10,	// ダークフレーム
		1375,10,	// 一反木綿
		1510,10,	// ハイローゾイスト
		1508,5,		// キューブ
		1509,5,		// ルード
		1179,10,	// ウィスパー
	;
	setarray 'mob[4][0],	// 30F
		//1630,1,	// ペクソジン
		//1416,30,	// 天仙娘々
		// jRO配置
		1159,1,		// フリオニ
		1166,20,	// サベージ
		1311,10,	// グリンブルスティ
	;
	setarray 'mob[5][0],	// 31F
		1387,20,	// ギグ
		1212,15,	// アイアンフィスト
		1099,10,	// アルギオペ
		1001,5,		// スコーピオン
	;
	setarray 'mob[6][0],	// 32F
		1299,1,		// ゴブリンリーダー
		1258,10,	// ゴブリンアーチャー
		1122,10,	// ゴブリン長男
		1123,5,		// ゴブリン次男
		1124,5,		// ゴブリン三男
		1125,5,		// ゴブリン四男
		1126,5,		// ゴブリン五男
	;
	setarray 'mob[7][0],	// 33F
		1296,1,		// コボルドリーダー
		1133,15,	// コボルド(斧)
		1282,15,	// コボルドアーチャー
		1134,10,	// コボルド(槌)
		1135,5,		// コボルド(毬)
	;
	setarray 'mob[8][0],	// 34F
		1869,20,	// フレームスカル
		1179,10,	// ウィスパー
		1186,10,	// 巨大ウィスパー
	;
	setarray 'mob[9][0],	// 35F
		1312,1,		// タートルジェネラル
		1319,10,	// フリーズタートル
		1316,10,	// ソリッドタートル
		1318,10,	// ヒートタートル
		1314,10,	// パーメットタートル
	;
	setarray 'mob[10][0],	// 36F
		1206,30,	// アノリアン
		1687,10,	// グリーンイグアナ
		1271,10,	// アリゲーター
	;
	setarray 'mob[11][0],	// 37F
		1270,5,		// 時計塔管理者
		1269,10,	// クロック
		1193,30,	// アラーム
	;
	setarray 'mob[12][0],	// 38F
		1698,25,	// デスワード
		1195,25,	// ライドワード
	;
	setarray 'mob[13][0],	// 39F
		1416,10,	// 天仙娘々
		1513,10,	// ミョグェ
		1412,10,	// 天邪仙人
		1514,10,	// 小龍舞
		1517,5,		// 虎人
	;
	setarray 'mob[14][0],	// 40F
		//1492,1,	// 怨霊武士
		//1401,10,	// カブキ忍者
		//1405,10,	// 酒天狗
		//1403,5,	// 銃奇兵
		//1404,10,	// 雅人形
		//1400,5,	// カラ傘
		// jRO配置
		1251,1,		// ストームナイト
		1252,1,		// ハティー
		1515,35,	// ハティーベベ
		1775,15,	// スノウアー
		1777,15,	// アイスタイタン
	;
	setarray 'mob[15][0],	// 41F
		1587,50,	// クラベン
	;
	setarray 'mob[16][0],	// 42F
		1386,20,	// スリーパー
		1207,10,	// スティング
		1516,10,	// 土精
		1165,5,		// サンドマン
		1127,5,		// ホード
	;
	setarray 'mob[17][0],	// 43F
		1148,10,	// メデューサ
		1037,40,	// サイドワインダー
		1030,5,		// アナコンダク
		1025,5,		// スネイク
	;
	setarray 'mob[18][0],	// 44F
		1515,20,	// ハティーベベ
		1101,20,	// バフォメット.Jr
		1686,1,		// オークベイビー
		1107,10,	// 子デザートウルフ
		1167,10,	// サベージベベ
	;
	setarray 'mob[19][0],	// 45F
		1038,1,		// オシリス
		1297,15,	// エンシェントマミー
		1032,15,	// ベリット
		1041,20,	// マミー
	;
	setarray 'mob[20][0],	// 46F
		1774,20,	// シーカー
		1633,20,	// ビホルダー
	;
	setarray 'mob[21][0],	// 47F
		1384,20,	// デリーター(空)
		1385,10,	// デリーター(地)
		1156,10,	// プティット(空)
		1155,10,	// プティット(地)
	;
	setarray 'mob[22][0],	// 48F
		1305,10,	// エンシェントワーム
		1297,10,	// エンシェントマミー
		1699,10,	// エンシェントミミック
	;
	setarray 'mob[23][0],	// 49F
		1381,20,	// グリズリー
		1306,7,		// レイブオルマイ
		1417,5,		// チャッキー
		1243,5,		// サスカッチ
		1060,5,		// ビッグフット
	;
	setarray 'mob[24][0],	// 50F
		1157,1,		// ファラオ
		1511,1,		// アモンラー
		1098,10,	// アヌビス
		1140,10,	// マルドゥーク
		1146,10,	// マーター
	;
	setarray 'x,  9, 93,181,267,352;
	setarray 'y,351,267,180, 96,  9;
L_MobCall:
	disablenpc getmdnpcname("TowerGate" +'lv);
	set '@idx,'lv-26;
	set '@max,getarraysize('mob['@idx][0])/2;
	for(set '@i,0; '@i < '@max; set '@i,'@i+1)
		areamonster getmdmapname("2@tower.gat"),'x['@idx%5],'y['@idx/5],'x['@idx%5]+10,'y['@idx/5]+36,"--ja--",'mob['@idx]['@i*2],'mob['@idx]['@i*2+1],getmdnpcname("TowerControl2")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set 'count,getmapmobs(getmdmapname("2@tower.gat"),getmdnpcname("TowerControl2")+ "::OnKilled");
	if('count <= 0) {
		announce 'lv+ "階のすべてのモンスターを倒しました",0x9,0xFFFF00;
		enablenpc getmdnpcname("TowerGate"+'lv);
		if('lv%25 == 0)
			initnpctimer getmdnpcname("TowerGate"+'lv);
		else {
			set 'lv,'lv+1;
			callsub L_MobCall;
		}
	}
	else
		announce 'lv+ "階に残ったモンスター [" +'count+ "]体",0x9,0x00FF99;
	end;
}

2@tower.gat,12,393,0	warp	TowerGate26	2,2,2@tower.gat,136,354
2@tower.gat,96,393,0	warp	TowerGate27	2,2,2@tower.gat,224,354
2@tower.gat,184,393,0	warp	TowerGate28	2,2,2@tower.gat,310,354
2@tower.gat,270,393,0	warp	TowerGate29	2,2,2@tower.gat,395,354
2@tower.gat,355,393,0	warp	TowerGate30	2,2,2@tower.gat,52,270
2@tower.gat,12,309,0	warp	TowerGate31	2,2,2@tower.gat,136,270
2@tower.gat,96,309,0	warp	TowerGate32	2,2,2@tower.gat,224,270
2@tower.gat,184,309,0	warp	TowerGate33	2,2,2@tower.gat,310,270
2@tower.gat,270,309,0	warp	TowerGate34	2,2,2@tower.gat,395,270
2@tower.gat,355,309,0	warp	TowerGate35	2,2,2@tower.gat,52,183
2@tower.gat,12,222,0	warp	TowerGate36	2,2,2@tower.gat,136,183
2@tower.gat,96,222,0	warp	TowerGate37	2,2,2@tower.gat,224,183
2@tower.gat,184,222,0	warp	TowerGate38	2,2,2@tower.gat,310,183
2@tower.gat,270,222,0	warp	TowerGate39	2,2,2@tower.gat,395,183
2@tower.gat,355,222,0	warp	TowerGate40	2,2,2@tower.gat,52,99
2@tower.gat,12,138,0	warp	TowerGate41	2,2,2@tower.gat,136,99
2@tower.gat,96,138,0	warp	TowerGate42	2,2,2@tower.gat,224,99
2@tower.gat,184,138,0	warp	TowerGate43	2,2,2@tower.gat,310,99
2@tower.gat,270,138,0	warp	TowerGate44	2,2,2@tower.gat,395,99
2@tower.gat,355,138,0	warp	TowerGate45	2,2,2@tower.gat,52,12
2@tower.gat,12,51,0		warp	TowerGate46	2,2,2@tower.gat,136,12
2@tower.gat,96,51,0		warp	TowerGate47	2,2,2@tower.gat,224,12
2@tower.gat,184,51,0	warp	TowerGate48	2,2,2@tower.gat,310,12
2@tower.gat,270,51,0	warp	TowerGate49	2,2,2@tower.gat,395,12
2@tower.gat,355,51,0	script	TowerGate50	45,2,2,{
	if(getnpctimer(1))
		getitem 6000,1;
	donpcevent getmdnpcname("TowerControl3")+ "::OnStart";
	warp getmdmapname("3@tower.gat"),52,354;
	end;
OnTimer120000:
	stopnpctimer;
	end;
}

//============================================================
// エンドレスタワー51F～75F
//------------------------------------------------------------
3@tower.gat,0,0,0	script	TowerControl3	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,51;
	setarray 'mob[0][0],	// 51F
		1292,20,	// ミニデモ
		1382,20,	// ディアボリック
		1109,10,	// デビルチ
	;
	setarray 'mob[1][0],	// 52F
		1376,20,	// ハーピー
		1369,10,	// グランペコ
		1408,10,	// パピヨン
		1253,10,	// ガーゴイル
		1680,5,		// ヒルウィンド(羽)
		1629,5,		// ヒルウィンド(槍)
	;
	setarray 'mob[2][0],	// 53F
		1315,25,	// アサルトタートル
		1401,30,	// カブキ忍者
	;
	setarray 'mob[3][0],	// 54F
		1250,10,	// チェペット
		1143,10,	// マリオネット
		1404,10,	// 雅人形
	;
	setarray 'mob[4][0],	// 55F
		1148,25,	// メデューサ
		1418,1,		// 黒蛇王
		1029,15,	// イシス
		1037,15,	// サイドワインダー
	;
	setarray 'mob[5][0],	// 56F
		1319,10,	// フリーズタートル
		1515,10,	// ハティーベベ
		1777,15,	// アイスタイタン
		1775,10,	// スノウアー
		1778,10,	// ゲイズティ
	;
	setarray 'mob[6][0],	// 57F
		1388,1,		// アークエンジェリング
		1582,1,		// デビルリング
		1096,1,		// エンジェリング
		1120,1,		// ゴーストリング
		1090,1,		// マスターリング
		1613,25,	// メタリン
		1242,5,		// マーリン
		1031,5,		// ポポリン
		1113,5,		// ドロップス
	;
	setarray 'mob[7][0],	// 58F
		1202,20,	// フェンダーク
		1201,10,	// リビオ
		1197,10,	// ゾンビプリズナー
		1196,5,		// スケルプリズナー
		1257,5,		// インジャスティス
	;
	setarray 'mob[8][0],	// 59F
		1699,30,	// エンシェントミミック
		1191,20,	// ミミック
		1249,10,	// ミストケース
	;
	setarray 'mob[9][0],	// 60F
		1658,1,		// イグニゼム=セニア(MVP)
		1046,1,		// ドッペルゲンガー
		1654,10,	// アルマイア=デュンゼ
		1653,10,	// ヒュッケバイン=トリス
		1657,10,	// ラウレル=ヴィンダー
		1656,10,	// カヴァク=イカルス
		1655,10,	// イレンド=エベシ
		1652,10,	// イグニゼム=セニア
	;
	setarray 'mob[10][0],	// 61F
		1769,10,	// アガヴ
		1770,10,	// エキオ
		1772,5,		// アイシラ
		1313,10,	// チンピラ
		1154,10,	// パサナ
		1771,5,		// ヴァンベルク
	;
	setarray 'mob[11][0],	// 62F
		1208,35,	// 彷徨う者
	;
	setarray 'mob[12][0],	// 63F
		1865,20,	// ラギッドゾンビ
		1298,10,	// ゾンビマスター
		1197,5,		// ゾンビプリズナー
		1153,5,		// オークゾンビ
		1015,5,		// ゾンビ
	;
	setarray 'mob[13][0],	// 64F
		1618,30,	// ウンゴリアント
		1305,2,		// エンシェントワーム
		1300,2,		// キャタピラー
		1293,2,		// クリーミーフィアー
		1294,2,		// キラーマンティス
		1303,2,		// ジャイアントホーネット
	;
	setarray 'mob[14][0],	// 65F
		1785,1,		// アトロス
		1783,20,	// ガリオン
	;
	setarray 'mob[15][0],	// 66F
		1374,20,	// インキュバス
		1736,20,	// エリオット
		1257,10,	// インジャスティス
	;
	setarray 'mob[16][0],	// 67F
		1716,10,	// オシドス(青)
		1713,10,	// オシドス(金)
		1384,5,		// デリーター(空)
		1262,10,	// ミュータントドラゴン
		1156,5,		// プティット(空)
	;
	setarray 'mob[17][0],	// 68F
		1366,10,	// ラーヴァゴーレム
		1278,10,	// スタラクタイトゴーレム
		1777,10,	// アイスタイタン
		1497,5,		// ウドゥンゴーレム
		1040,5,		// ゴーレム
	;
	setarray 'mob[18][0],	// 69F
		1700,20,	// 監視する者
		1701,10,	// 保護する者
		1702,10,	// 執行する者
		1703,10,	// 慰める者
		1371,10,	// フェイクエンジェル
	;
	setarray 'mob[19][0],	// 70F
		//1087,1,	// オークヒーロー
		//1190,1,	// オークロード
		//1686,20,	// オークベイビー
		// jRO配置
		1623,1,		// RSX-0806
		1685,1,		// ヴェスパー
		1617,10,	// ジャンクポット
		1622,5,		// ベアドール
		1668,5,		// アークダム
		1670,15,	// ディミック(風)
		1671,15,	// ディミック(水)
		1672,5,		// ディミック(地)
		1673,10,	// ディミック(火)
	;
	setarray 'mob[20][0],	// 71F
		1370,20,	// サキュバス
		1379,20,	// ナイトメアテラー
		1374,20,	// インキュバス
		1061,5,		// ナイトメア
	;
	setarray 'mob[21][0],	// 72F
		1637,10,	// マーガレッタ=ソリン
		1314,10,	// パーメットタートル
		1655,10,	// イレンド=エベシ
		1410,10,	// 人面桃樹
	;
	setarray 'mob[22][0],	// 73F
		1370,10,	// サキュバス
		1505,20,	// ロリルリ
		1737,10,	// エリザ
		1200,5,		// ジルタス
		1275,5,		// アリス
		1631,10,	// チュンイー
	;
	setarray 'mob[23][0],	// 74F
		1671,6,		// ディミック(水)
		1673,6,		// ディミック(火)
		1672,6,		// ディミック(地)
		1677,6,		// ヴェナート(風)
		1670,6,		// ディミック(風)
		1668,6,		// アークダム
		1678,6,		// ヴェナート(地)
		1679,6,		// ヴェナート(水)
		1676,6,		// ヴェナート(無)
	;
	setarray 'mob[24][0],	// 75F
		1039,1,		// バフォメット
		1272,1,		// ダークロード
		1101,20,	// バフォメット.Jr
		1302,10,	// ダークイリュージョン
	;
	setarray 'x,  9, 93,181,267,352;
	setarray 'y,351,267,180, 96,  9;
L_MobCall:
	disablenpc getmdnpcname("TowerGate" +'lv);
	set '@idx,'lv-51;
	set '@max,getarraysize('mob['@idx][0])/2;
	for(set '@i,0; '@i < '@max; set '@i,'@i+1)
		areamonster getmdmapname("3@tower.gat"),'x['@idx%5],'y['@idx/5],'x['@idx%5]+10,'y['@idx/5]+36,"--ja--",'mob['@idx]['@i*2],'mob['@idx]['@i*2+1],getmdnpcname("TowerControl3")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set 'count,getmapmobs(getmdmapname("3@tower.gat"),getmdnpcname("TowerControl3")+ "::OnKilled");
	if('count <= 0) {
		announce 'lv+ "階のすべてのモンスターを倒しました",0x9,0xFFFF00;
		enablenpc getmdnpcname("TowerGate"+'lv);
		if('lv%25 == 0)
			initnpctimer getmdnpcname("TowerGate"+'lv);
		else {
			set 'lv,'lv+1;
			callsub L_MobCall;
		}
	}
	else
		announce 'lv+ "階に残ったモンスター [" +'count+ "]体",0x9,0x00FF99;
	end;
}

3@tower.gat,12,393,0	warp	TowerGate51	2,2,3@tower.gat,136,354
3@tower.gat,96,393,0	warp	TowerGate52	2,2,3@tower.gat,224,354
3@tower.gat,184,393,0	warp	TowerGate53	2,2,3@tower.gat,310,354
3@tower.gat,270,393,0	warp	TowerGate54	2,2,3@tower.gat,395,354
3@tower.gat,355,393,0	warp	TowerGate55	2,2,3@tower.gat,52,270
3@tower.gat,12,309,0	warp	TowerGate56	2,2,3@tower.gat,136,270
3@tower.gat,96,309,0	warp	TowerGate57	2,2,3@tower.gat,224,270
3@tower.gat,184,309,0	warp	TowerGate58	2,2,3@tower.gat,310,270
3@tower.gat,270,309,0	warp	TowerGate59	2,2,3@tower.gat,395,270
3@tower.gat,355,309,0	warp	TowerGate60	2,2,3@tower.gat,52,183
3@tower.gat,12,222,0	warp	TowerGate61	2,2,3@tower.gat,136,183
3@tower.gat,96,222,0	warp	TowerGate62	2,2,3@tower.gat,224,183
3@tower.gat,184,222,0	warp	TowerGate63	2,2,3@tower.gat,310,183
3@tower.gat,270,222,0	warp	TowerGate64	2,2,3@tower.gat,395,183
3@tower.gat,355,222,0	warp	TowerGate65	2,2,3@tower.gat,52,99
3@tower.gat,12,138,0	warp	TowerGate66	2,2,3@tower.gat,136,99
3@tower.gat,96,138,0	warp	TowerGate67	2,2,3@tower.gat,224,99
3@tower.gat,184,138,0	warp	TowerGate68	2,2,3@tower.gat,310,99
3@tower.gat,270,138,0	warp	TowerGate69	2,2,3@tower.gat,395,99
3@tower.gat,355,138,0	warp	TowerGate70	2,2,3@tower.gat,52,12
3@tower.gat,12,51,0		warp	TowerGate71	2,2,3@tower.gat,136,12
3@tower.gat,96,51,0		warp	TowerGate72	2,2,3@tower.gat,224,12
3@tower.gat,184,51,0	warp	TowerGate73	2,2,3@tower.gat,310,12
3@tower.gat,270,51,0	warp	TowerGate74	2,2,3@tower.gat,395,12
3@tower.gat,355,51,0	script	TowerGate75	45,2,2,{
	if(getnpctimer(1))
		getitem 6000,1;
	donpcevent getmdnpcname("TowerControl4")+ "::OnStart";
	warp getmdmapname("4@tower.gat"),52,354;
	end;
OnTimer120000:
	stopnpctimer;
	end;
}

//============================================================
// エンドレスタワー76F～99F
//------------------------------------------------------------
4@tower.gat,0,0,0	script	TowerControl4	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,76;
	setarray 'mob[0][0],	// 76F
		1219,30,	// 深淵の騎士
		1379,20,	// ナイトメアテラー
		1061,10,	// ナイトメア
	;
	setarray 'mob[1][0],	// 77F
		1867,30,	// バンシー
		1291,10,	// デッドリーレイス
		1117,10,	// イビルドルイド
		1192,10,	// レイス
		1263,10,	// ウィンドゴースト
	;
	setarray 'mob[2][0],	// 78F
		1829,5,		// ソードガーディアン
		1268,10,	// ブラッディナイト
		1219,5,		// 深淵の騎士
		1504,10,	// デュラハン
		1163,20,	// レイドリック
	;
	setarray 'mob[3][0],	// 79F
		1720,10,	// ハイドラランサー
		1714,10,	// ペロス(赤)
		1717,10,	// ペロス(緑)
		1385,10,	// デリーター(地)
		1155,10,	// プティット(地)
	;
	setarray 'mob[4][0],	// 80F
		1871,1,		// 堕ちた大神官ヒバム
		1870,15,	// ネクロマンサー
	;
	setarray 'mob[5][0],	// 81F
		1203,20,	// ミステルテイン
		1204,20,	// オーガトゥース
		1205,20,	// エクスキューショナー
	;
	setarray 'mob[6][0],	// 82F
		1268,10,	// ブラッディナイト
		1769,10,	// アガヴ
		1507,10,	// ブラッディマーダー
		1752,10,	// スコグル
		1257,10,	// インジャスティス
	;
	setarray 'mob[7][0],	// 83F
		1754,10,	// スケゴルト
		1302,10,	// ダークイリュージョン
		1259,10,	// グリフォン
		1283,10,	// キメラ
	;
	setarray 'mob[8][0],	// 84F
		1370,10,	// サキュバス
		1302,20,	// ダークイリュージョン
		1320,10,	// オウルデューク
		1295,10,	// オウルバロン
		1374,10,	// インキュバス
	;
	setarray 'mob[9][0],	// 85F
		1832,1,		// イフリート
	;
	setarray 'mob[10][0],	// 86F
		1720,10,	// ハイドラランサー
		1259,10,	// グリフォン
		1283,10,	// キメラ
		1310,10,	// ごっついミノタウロス
	;
	setarray 'mob[11][0],	// 87F
		1831,15,	// サラマンダー
		1833,20,	// カーサ
		1366,15,	// ラーヴァゴーレム
		1309,10,	// ガジョマート
	;
	setarray 'mob[12][0],	// 88F
		1870,15,	// ネクロマンサー
		1098,15,	// アヌビス
		1291,10,	// デッドリーレイス
		1297,10,	// エンシェントマミー
		1132,10,	// カーリッツバーグ
	;
	setarray 'mob[13][0],	// 89F
		1704,6,		// タナトスの憎悪
		1705,6,		// タナトスの絶望
		1707,6,		// タナトスの苦悩
		1706,6,		// タナトスの悲しみ
	;
	setarray 'mob[14][0],	// 90F
		1751,1,		// ランドグリス
		1702,10,	// 執行する者
		1703,10,	// 慰める者
		1371,10,	// フェイクエンジェル
	;
	setarray 'mob[15][0],	// 91F
		1638,10,	// セシル=ディモン
		1830,10,	// ボウガーディアン
		1656,30,	// カヴァク=イカルス
	;
	setarray 'mob[16][0],	// 92F
		1639,15,	// カトリーヌ=ケイロン
		1377,10,	// エルダー
		1657,10,	// ラウレル=ヴィンダー
		1263,10,	// ウィンドゴースト
		1140,10,	// マルドゥーク
	;
	setarray 'mob[17][0],	// 93F
		1634,15,	// セイレン=ウィンザー
		1268,10,	// ブラッディナイト
		1219,10,	// 深淵の騎士
		1208,10,	// 彷徨う者
	;
	setarray 'mob[18][0],	// 94F
		1829,15,	// ソードガーディアン
		1830,15,	// ボウガーディアン
	;
	setarray 'mob[19][0],	// 95F
		1873,1,		// ヴェルゼブブ
		1035,30,	// ハンターフライ
		1042,5,		// スチールチョンチョン
		1091,5,		// ドラゴンフライ
		1011,5,		// チョンチョン
	;
	setarray 'mob[20][0],	// 96F
		1765,5,		// ランドグリスゴースト
		1755,10,	// スケゴルト(青)
		1754,10,	// スケゴルト(茶)
	;
	setarray 'mob[21][0],	// 97F
		1918,5,		// モロクの現身(天使型)
		1919,5,		// モロクの現身(物質型)
		1920,5,		// モロクの現身(人間型)
		1921,5,		// モロクの現身(精霊型)
	;
	setarray 'mob[22][0],	// 98F
		1639,2,		// カトリーヌ=ケイロン
		1634,2,		// セイレン=ウィンザー
		1637,2,		// マーガレッタ=ソリン
		1635,2,		// エレメス=ガイル
		1636,2,		// ハワード=アルトアイゼン
		1638,2,		// セシル=ディモン
	;
	setarray 'mob[23][0],	// 99F
		1639,2,		// カトリーヌ=ケイロン
		1634,2,		// セイレン=ウィンザー
		1637,2,		// マーガレッタ=ソリン
		1635,2,		// エレメス=ガイル
		1636,2,		// ハワード=アルトアイゼン
		1638,2,		// セシル=ディモン
		1918,5,		// モロクの現身(天使型)
		1919,5,		// モロクの現身(物質型)
		1920,5,		// モロクの現身(人間型)
		1921,5,		// モロクの現身(精霊型)
		1765,5,		// ランドグリスゴースト
		1755,10,	// スケゴルト(青)
		1754,10,	// スケゴルト(茶)
		1634,15,	// セイレン=ウィンザー
		1268,10,	// ブラッディナイト
		1219,10,	// 深淵の騎士
		1208,10,	// 彷徨う者
		1829,15,	// ソードガーディアン
		1830,15,	// ボウガーディアン
		1639,15,	// カトリーヌ=ケイロン
		1377,10,	// エルダー
		1657,10,	// ラウレル=ヴィンダー
		1263,10,	// ウィンドゴースト
		1140,10,	// マルドゥーク
		1638,10,	// セシル=ディモン
		1830,10,	// ボウガーディアン
		1656,30,	// カヴァク=イカルス
		1702,10,	// 執行する者
		1703,10,	// 慰める者
		1371,10,	// フェイクエンジェル
	;
	setarray 'x,  9, 93,181,267,352;
	setarray 'y,351,267,180, 96,  9;
L_MobCall:
	disablenpc getmdnpcname("TowerGate" +'lv);
	set '@idx,'lv-76;
	set '@max,getarraysize('mob['@idx][0])/2;
	if('lv == 99) {
		for(set '@i,0; '@i < 7; set '@i,'@i+1) {
			set '@r,rand('@max);
			areamonster getmdmapname("4@tower.gat"),'x['@idx%5],'y['@idx/5],'x['@idx%5]+10,'y['@idx/5]+36,"--ja--",'mob['@idx]['@r*2],'mob['@idx]['@r*2+1],getmdnpcname("TowerControl4")+ "::OnKilled";
		}
	}
	else {
		for(set '@i,0; '@i < '@max; set '@i,'@i+1)
			areamonster getmdmapname("4@tower.gat"),'x['@idx%5],'y['@idx/5],'x['@idx%5]+10,'y['@idx/5]+36,"--ja--",'mob['@idx]['@i*2],'mob['@idx]['@i*2+1],getmdnpcname("TowerControl4")+ "::OnKilled";
	}
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set 'count,getmapmobs(getmdmapname("4@tower.gat"),getmdnpcname("TowerControl4")+ "::OnKilled");
	if('count <= 0) {
		announce 'lv+ "階のすべてのモンスターを倒しました",0x9,0xFFFF00;
		enablenpc getmdnpcname("TowerGate"+'lv);
		if('lv == 99)
			initnpctimer "TowerGate" +'lv;
		else {
			set 'lv,'lv+1;
			callsub L_MobCall;
		}
	}
	else
		announce 'lv+ "階に残ったモンスター [" +'count+ "]体",0x9,0x00FF99;
	end;
}

4@tower.gat,12,393,0	warp	TowerGate76	2,2,4@tower.gat,136,354
4@tower.gat,96,393,0	warp	TowerGate77	2,2,4@tower.gat,224,354
4@tower.gat,184,393,0	warp	TowerGate78	2,2,4@tower.gat,310,354
4@tower.gat,270,393,0	warp	TowerGate79	2,2,4@tower.gat,395,354
4@tower.gat,355,393,0	warp	TowerGate80	2,2,4@tower.gat,52,270
4@tower.gat,12,309,0	warp	TowerGate81	2,2,4@tower.gat,136,270
4@tower.gat,96,309,0	warp	TowerGate82	2,2,4@tower.gat,224,270
4@tower.gat,184,309,0	warp	TowerGate83	2,2,4@tower.gat,310,270
4@tower.gat,270,309,0	warp	TowerGate84	2,2,4@tower.gat,395,270
4@tower.gat,355,309,0	warp	TowerGate85	2,2,4@tower.gat,52,183
4@tower.gat,12,222,0	warp	TowerGate86	2,2,4@tower.gat,136,183
4@tower.gat,96,222,0	warp	TowerGate87	2,2,4@tower.gat,224,183
4@tower.gat,184,222,0	warp	TowerGate88	2,2,4@tower.gat,310,183
4@tower.gat,270,222,0	warp	TowerGate89	2,2,4@tower.gat,395,183
4@tower.gat,355,222,0	warp	TowerGate90	2,2,4@tower.gat,52,99
4@tower.gat,12,138,0	warp	TowerGate91	2,2,4@tower.gat,136,99
4@tower.gat,96,138,0	warp	TowerGate92	2,2,4@tower.gat,224,99
4@tower.gat,184,138,0	warp	TowerGate93	2,2,4@tower.gat,310,99
4@tower.gat,270,138,0	warp	TowerGate94	2,2,4@tower.gat,395,99
4@tower.gat,355,138,0	warp	TowerGate95	2,2,4@tower.gat,52,12
4@tower.gat,12,51,0		warp	TowerGate96	2,2,4@tower.gat,136,12
4@tower.gat,96,51,0		warp	TowerGate97	2,2,4@tower.gat,224,12
4@tower.gat,184,51,0	warp	TowerGate98	2,2,4@tower.gat,310,12
4@tower.gat,270,51,0	script	TowerGate99	45,2,2,{
	if(getnpctimer(1))
		getitem 6000,1;
	donpcevent getmdnpcname("TowerControl5")+ "::OnStart";
	warp getmdmapname("5@tower.gat"),101,72;
	end;
OnTimer120000:
	stopnpctimer;
	end;
}

//============================================================
// エンドレスタワー100F
//------------------------------------------------------------
5@tower.gat,0,0,0	script	TowerControl5	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,100;
	set '@mdmap$,getmdmapname("5@tower.gat");
	set '@mdnpc$,getmdnpcname("TowerControl5");
	monster '@mdmap$,83,85,"エントヴァイエン",1957,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,72,93,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,70,87,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,68,83,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,70,80,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,74,81,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,78,72,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,81,70,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,78,84,"治癒の茨",1959,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,85,72,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,91,74,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,79,77,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,82,80,"治癒の茨",1959,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,87,83,"治癒の茨",1959,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,80,92,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,81,89,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,85,93,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,86,90,"治癒の茨",1959,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,88,88,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,91,87,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,95,94,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,91,96,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,90,82,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,96,98,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,83,76,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	monster '@mdmap$,74,85,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2";
	switch(rand(3)) {
		case 0: monster '@mdmap$,82,85,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2"; break;
		case 1: monster '@mdmap$,82,85,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2"; break;
		case 2: monster '@mdmap$,82,85,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2"; break;
	}
	switch(rand(3)) {
		case 0: monster '@mdmap$,84,85,"狙撃の茨",1958,1,'@mdnpc$ +"::OnKilled2"; break;
		case 1: monster '@mdmap$,84,85,"魔法の茨",1960,1,'@mdnpc$ +"::OnKilled2"; break;
		case 2: monster '@mdmap$,84,85,"浄化の茨",1961,1,'@mdnpc$ +"::OnKilled2"; break;
	}
	end;
OnKilled:
	killmonster getmdmapname("5@tower.gat"),getmdnpcname("TowerControl5") +"::OnKilled2";
	announce "正体不明の声 : 誰だ？　勝手に私のテリトリーに入った者は……",0x9,0xFFFF00;
	hideoffnpc getmdnpcname("水晶#Tower");
	end;
OnKilled2:
	end;
}

5@tower.gat,106,109,0	script	水晶#Tower	111,{
	mes "-強い光を放つ水晶から";
	mes "　奇妙な感覚を感じる。";
	mes "　まるでこちらを歓迎しているかの";
	mes "　ようだ……-";
	next;
	mes "[正体不明の声]";
	mes "^FF0000フフフ……";
	mes "血と汗の臭い、そして";
	mes "荒い息を感じるぞ……";
	mes "人間どもの無謀さには";
	mes "いつになっても興味が尽きぬ……^000000";
	next;
	mes "[正体不明の声]";
	mes "^FF0000……私の所まで来ることを";
	mes "許可してやろう。";
	mes "この闇夜の覇王の所までな……^000000";
	close2;
	warp getmdmapname("6@tower.gat"),32,12;
	end;
OnInit:
	hideonnpc;
	end;
}

//============================================================
// エンドレスタワー101F～102F
//------------------------------------------------------------
6@tower.gat,45,89,0	script	命の泉#Tower	111,{
	misceffect 14,"";
	mes "^0066FF-幻想的で美しい水を飲むと、";
	mes "　体中に活力が戻ってくるのが";
	mes "　わかった-^000000";
	percentheal 100,100;
	close;
OnInit:
OnTimer2000:
	misceffect 109;
	initnpctimer;
	end;
}

6@tower.gat,32,100,0	script	TowerGate101	45,2,2,{
	donpcevent getmdnpcname("TowerControl6")+ "::OnStart";
	warp getmdmapname("6@tower.gat"),155,64;
	end;
}

6@tower.gat,0,0,0	script	TowerControl6	-1,{
OnStart:
	if('lv > 0)
		end;
	set 'lv,102;
	areamonster getmdmapname("6@tower.gat"),154,73,156,75,"監視者ウィレス",1627,10,getmdnpcname("TowerControl6")+ "::OnKilled";
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("6@tower.gat"),getmdnpcname("TowerControl6")+ "::OnKilled");
	if('count > 0)
		end;
	sleep 500;
	announce "正体不明の声 : 来たか……ここがどんな場所かも知らずに……",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : お前ら冒険者どもはいつもそうだ。だが、その勇気だけは褒めてやろう。",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : ここに足を踏み入れたからには、存分に楽しませて貰うぞ。",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : 私は虫けらどもが必死になって右往左往する様を見るのが好きだ。",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : さあ、この私をどこまで楽しませてくれるかな？",0x9,0x00FFCC;
	areamonster getmdmapname("6@tower.gat"),152,66,152,106,"骨の守護兵",1152,50,getmdnpcname("TowerControl6")+ "::OnKilled2";
	areamonster getmdmapname("6@tower.gat"),159,66,159,106,"骨の守護兵",1152,50,getmdnpcname("TowerControl6")+ "::OnKilled2";
	end;
OnKilled2:
	set 'count,getmapmobs(getmdmapname("6@tower.gat"),getmdnpcname("TowerControl6")+ "::OnKilled2");
	if('count > 0) {
		announce "残り[" +'count+ "]匹",0x9,0x00FF99;
		end;
	}
	sleep 500;
	announce "正体不明の声 : ……ふむ。まあ、手始めとしては少々物足りなかったか？",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : では、少し刺激を増やしてやろう。",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : さあ、次はどうかな？",0x9,0x00FFCC;
	areamonster getmdmapname("6@tower.gat"),152,66,152,106,"風の守護兵",1263,30,getmdnpcname("TowerControl6")+ "::OnKilled3";
	areamonster getmdmapname("6@tower.gat"),159,66,159,106,"風の守護兵",1263,30,getmdnpcname("TowerControl6")+ "::OnKilled3";
	end;
OnKilled3:
	set 'count,getmapmobs(getmdmapname("6@tower.gat"),getmdnpcname("TowerControl6")+ "::OnKilled3");
	if('count > 0) {
		announce "残り[" +'count+ "]匹",0x9,0x00FF99;
		end;
	}
	sleep 500;
	announce "正体不明の声 : フフ、少しはやるようだな！",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : 流石にここまで来ただけはある。覚えてやろう、お前らの名前を。",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : ……せっかくだ、残りの守護兵でも楽しんでくれ。",0x9,0x00FFCC;
	areamonster getmdmapname("6@tower.gat"),152,66,152,106,"刃の守護兵",1132,20,getmdnpcname("TowerControl6")+ "::OnKilled4";
	areamonster getmdmapname("6@tower.gat"),159,66,159,106,"刃の守護兵",1132,20,getmdnpcname("TowerControl6")+ "::OnKilled4";
	end;
OnKilled4:
	set 'count,getmapmobs(getmdmapname("6@tower.gat"),getmdnpcname("TowerControl6")+ "::OnKilled4");
	if('count > 0) {
		announce "残り[" +'count+ "]匹",0x9,0x00FF99;
		end;
	}
	sleep 500;
	announce "正体不明の声 : ……よかろう！　今度は私が相手だ！",0x9,0x00FFCC;
	sleep 5000;
	announce "正体不明の声 : 私が何者か、気になるのかね？　……私は闇夜の覇王、ナハトズィーガー！",0x9,0x00FFCC;
	sleep 5000;
	announce "ナハトズィーガー : ……だが、名前を聞いたからには死んでもらう！　行くぞ!!",0x9,0x00FFCC;
	monster getmdmapname("6@tower.gat"),156,147,"ナハトズィーガー",1956,1,getmdnpcname("TowerControl6")+ "::OnKilled5";
	end;
OnKilled5:
	hideoffnpc getmdnpcname("彷徨う魂#Tower");
	initnpctimer getmdnpcname("彷徨う魂#Tower");
	sleep 500;
	announce "ナハトズィーガー : ば、馬鹿な……!!　この私が……敗れるだと……!?",0x9,0xFFFF00;
	sleep 5000;
	announce "ナハトズィーガー : ぐぉぉ!!　わ、私の体がっ……!!",0x9,0xFFFF00;
	sleep 5000;
	announce "ナハトズィーガーは黒い灰になり、空中に飛散していった……",0x9,0x00FFCC;
	end;
}

6@tower.gat,169,127,2	script	彷徨う魂#Tower	796,{
	if((MaxWeight - Weight) < 1000) {
		mes "-所持アイテムの種類数が多い為";
		mes "　危険です。";
		mes "　所持アイテムを減らしてから、";
		mes "　再度話しかけてください-";
		close;
	}
	mes "[彷徨う魂]";
	mes "^FF0000あなたでしたか……";
	mes "邪悪なナハトズィーガーから";
	mes "私たちを解放してくれた人は。^000000";
	next;
	mes "[彷徨う魂]";
	mes "^FF0000これでやっと暗くて湿っぽい";
	mes "ここから出られます。^000000";
	next;
	if(countitem(13412) && countitem(13413)) {
		mes "[彷徨う魂]";
		mes "^FF0000ん？";
		mes "あなたは";
		mes "ナハトズィーガーの剣を";
		mes "両方持っていますね。^000000";
		next;
		mes "[彷徨う魂]";
		mes "^FF0000それらは片手剣ですが、";
		mes "あなたさえ良ければ";
		mes "それらを合成して1本の両手剣に";
		mes "変えてあげますよ？";
		mes "これが私からできる唯一の";
		mes "恩返しです……^000000";
		next;
		if(select("両手剣にして","このままでいい") == 1) {
			mes "[彷徨う魂]";
			mes "^FF0000分かりました。";
			mes "では二つの剣を合わせて";
			mes "両手剣にしてあげましょう。^000000";
			next;
			delitem 13412,1;
			delitem 13413,1;
			getitem 1185,1;
		}
		else {
			// 未調査
			mes "[彷徨う魂]";
			mes "^FF0000分かりました。";
			mes "二つの剣はそのままの状態に";
			mes "しておきましょう。^000000";
			next;
		}
		mes "[彷徨う魂]";
		mes "^FF0000もっと話がしたいですが、";
		mes "私が現世にいられるのも";
		mes "あともうごく僅か……^000000";
		next;
	}
	mes "[彷徨う魂]";
	mes "^FF0000では、お別れの時間です。";
	mes "お達者で、ありがとう。^000000";
	close2;
	warp "alberta.gat",223,36;
	end;
OnInit:
	hideonnpc;
	end;
OnTimer1000:
	misceffect 71;
	initnpctimer;
	end;
}
