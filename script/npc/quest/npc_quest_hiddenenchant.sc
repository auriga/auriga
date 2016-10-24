//==============================================================================
// Ragnarok Online HSE & HSEEX Script ver.2.1 2010/07/12	by tomo
//==============================================================================
function	script	HseSub	{
	set '@name$,getarg(0);
	set '@itemid,getarg(2);
	set '@price,getarg(3);
	if('@itemid == 0) {
		mes "[細工職人・" +'@name$+ "]";
		mes "わかりました。";
		mes "もし興味がわきましたら";
		mes "お越しください。";
		close;
	}
	if(countitem('@itemid) != 1) {
		mes "[細工職人・" +'@name$+ "]";
		mes "あら……";
		mes "先ほどもご説明しました通り";
		mes "^0000FF対象の鎧を1つだけ持った状態^000000で";
		mes "お願いします。";
		mes "持っていないのは論外ですが";
		mes "2つ以上持たないでください。";
		close;
	}
	mes "[細工職人・" +'@name$+ "]";
	mes "^0000FF" +getitemname('@itemid)+ "[" +getiteminfo('@itemid,10)+ "]^000000ですね。";
	mes "では、ご確認します。";
	mes "まず、手数料として";
	mes "^0000FF" +getarg(1)+ "Zeny^000000をいただきます。";
	next;
	mes "[細工職人・" +'@name$+ "]";
	mes "そして、エンチャントは";
	mes "必ずしも成功するとは限りません。";
	mes "^FF0000失敗すると、鎧は消えてしまいます^000000。";
	mes "また、成功すると、いままでの";
	mes "^FF0000精錬値及び挿していたカードが";
	mes "消えてしまいます^000000。";
	next;
	mes "[細工職人・" +'@name$+ "]";
	mes "エンチャントを行いますか？";
	next;
	if(select("^FF0000今回はやめておく^000000","^0000FFおねがいします^000000") == 1) {
		mes "[細工職人・" +'@name$+ "]";
		mes "わかりました。";
		mes "またいつでもお待ちしています。";
		close;
	}
	mes "[細工職人・" +'@name$+ "]";
	mes "わかりました。";
	mes "では、始めますよ。";
	next;
	if(Zeny < '@price) {
		mes "[細工職人・" +'@name$+ "]";
		mes "……あら、Zenyが";
		mes "足りなくなっていますよ。";
		close;
	}
	delitem '@itemid,1;
	set Zeny,Zeny-'@price;
	switch(getarg(4)) {
	case 0:	set '@rate,50;	break;
	case 1:	set '@rate,55;	break;
	case 2:	set '@rate,60;	break;
	}
	set '@succsess,rand(1,'@rate);
	if((6 + 12 + 18) >= '@succsess) {
		//成功
		switch(rand(6)) {
		case 0:	set '@cardid,4700;	break;
		case 1:	set '@cardid,4710;	break;
		case 2:	set '@cardid,4720;	break;
		case 3:	set '@cardid,4730;	break;
		case 4:	set '@cardid,4740;	break;
		case 5:	set '@cardid,4750;	break;
		}
		if('@succsess <= 6)
			set '@cardid, '@cardid+2;
		else if('@succsess <= 18)
			set '@cardid, '@cardid+1;
		getitem2 '@itemid,1,1,0,0,0,0,0,'@cardid;
		misceffect 305;
		mes "[細工職人・" +'@name$+ "]";
		mes "……ふう、成功しました！";
		mes "是非、大切に使ってください。";
		close;
	}
	misceffect 306;
	mes "[細工職人・" +'@name$+ "]";
	mes "ああ……";
	mes "エンチャントに失敗しました。";
	mes "切ないです……";
	close;
}

prontera.gat,91,116,6	script	細工職人・長女	815,{
	mes "[細工職人・長女]";
	mes "こんにちは。";
	mes "私は鎧を再構成し、その能力を";
	mes "極限まで引き出す研究を";
	mes "長年行っている者です。";
	mes "そこにある^FF0000細工案内板^000000の内容を";
	mes "ご確認いただけましたか？";
	next;
	if(select("していません","^0000FFしました^000000") == 1) {
		mes "[細工職人・長女]";
		mes "もし技術の施行をお望みでしたら、";
		mes "必ず^FF0000細工案内板^000000を";
		mes "ご確認ください。";
		mes "よろしくお願いいたします。";
		close;
	}
	mes "[細工職人・長女]";
	mes "かしこまりました。";
	mes "この技術、私が担当する鎧では";
	mes "1回^0000FF1,000,000Zeny^000000で、";
	mes "お試しいただけます。";
	next;
	mes "[細工職人・長女]";
	mes "では、エンチャント可能な鎧の";
	mes "一覧から、希望をお選びください。";
	next;
	setarray '@list,2365,2390,2388,2387,2375,2374,2389,2364,2391,0;
	set '@itemid, '@list[select(
		"オルレアンの制服[1]","改良型タイツ[1]","カンドゥラ[1]","スプリントメイル[1]",
		"ディアボロスアーマー[1]","ディアボロスローブ[1]","ナーガの鱗鎧[1]",
		"メテオプレート[1]","ライフリンク[1]","やめる")-1];
	callfunc "HseSub","長女","1,000,000",'@itemid,1000000,2;
}

prontera.gat,89,114,6	script	細工職人・次女	816,{
	mes "[細工職人・次女]";
	mes "こんにちは。";
	mes "私は鎧を再構成し、その能力を";
	mes "極限まで引き出す研究を";
	mes "長年行っている者です。";
	mes "そこにある^FF0000細工案内板^000000の内容を";
	mes "ご確認いただけましたか？";
	next;
	if(select("していません","^0000FFしました^000000") == 1) {
		mes "[細工職人・次女]";
		mes "もし技術の施行をお望みでしたら、";
		mes "必ず^FF0000細工案内板^000000を";
		mes "ご確認ください。";
		mes "よろしくお願いいたします。";
		close;
	}
	mes "[細工職人・次女]";
	mes "かしこまりました。";
	mes "この技術、私が担当する鎧では";
	mes "1回^0000FF500,000Zeny^000000で、";
	mes "お試しいただけます。";
	next;
	mes "[細工職人・次女]";
	mes "では、エンチャント可能な鎧の";
	mes "一覧から、希望をお選びください。";
	next;
	setarray '@list,2349,2319,2351,2336,2347,2322,2333,2324,2326,2331,2320,2342,2317,2311,2315,2308,2345,2318,2310,0;
	set '@itemid, '@list[select(
		"エベシ嵐のうねり[1]","グリッタングクロース[1]","クレイトス大地の裂け目[1]",
		"シーフクロース[1]","シャピニハ海の叫び[1]","シルクローブ[1]","シルバーローブ[1]",
		"スケーピューラー[1]","セイントローブ[1]","タイツ[1]","フォーマルスーツ[1]",
		"フルプレート[1]","プレート[1]","ミンクのコート[1]","メイル[1]","メントル[1]",
		"ルシウス火山の激しさ[1]","ロードクロース[1]","ロングコート[1]","やめる")-1];
	callfunc "HseSub","次女","500,000",'@itemid,500000,1;
}

prontera.gat,87,112,6	script	細工職人・三女	817,{
	mes "[細工職人・三女]";
	mes "こんにちは。";
	mes "私は鎧を再構成し、その能力を";
	mes "極限まで引き出す研究を";
	mes "長年行っている者です。";
	mes "そこにある^FF0000細工案内板^000000の内容を";
	mes "ご確認いただけましたか？";
	next;
	if(select("していません","^0000FFしました^000000") == 1) {
		mes "[細工職人・三女]";
		mes "もし技術の施行をお望みでしたら、";
		mes "必ず^FF0000細工案内板^000000を";
		mes "ご確認ください。";
		mes "よろしくお願いいたします。";
		close;
	}
	mes "[細工職人・三女]";
	mes "かしこまりました。";
	mes "この技術、私が担当する鎧では";
	mes "1回^0000FF300,000Zeny^000000で、";
	mes "お試しいただけます。";
	next;
	mes "[細工職人・三女]";
	mes "では、エンチャント可能な鎧の";
	mes "一覧から、希望をお選びください。";
	next;
	setarray '@list,2348,2386,2350,2335,2346,2321,2332,2325,2330,2337,2341,2316,2327,2334,2314,2307,2344,2309,0;
	set '@itemid, '@list[select(
		"エベシ嵐のうねり[0]","カメレオンアーマー[0]","クレイトス大地の裂け目[0]",
		"シーフクロース[0]","シャピニハ海の叫び[0]","シルクローブ[0]","シルバーローブ[0]",
		"セイントローブ[0]","タイツ[0]","忍者スーツ[0]","フルプレート[0]","プレート[0]",
		"ホーリーローブ[0]","マジックコート[0]","メイル[0]","メントル[0]",
		"ルシウス火山の激しさ[0]","ロングコート[0]","やめる")-1];
	callfunc "HseSub","三女","300,000",'@itemid,300000,0;
}

//==============================================================================
prontera.gat,83,108,6	script	細工職人・師範	814,{
	mes "[細工職人・師範]";
	mes "……私は兜を再構成し、";
	mes "その能力を極限まで引き出す研究を";
	mes "最近開始した者だ。";
	mes "そこにある^FF0000細工案内板^000000の内容は";
	mes "把握しているかな？";
	next;
	if(select("していません","^0000FFしました^000000") == 1) {
		mes "[細工職人・師範]";
		mes "……もし私の技術の施行を望みなら、";
		mes "必ず^FF0000細工案内板^000000を";
		mes "確認して欲しい。";
		close;
	}
	mes "[細工職人・師範]";
	mes "ふむ、良いだろう。";
	mes "私が提供する技術は、";
	mes "そこの三姉妹が行っている";
	mes "鎧の物とは違い、";
	mes "兜に対して行う。";
	mes "今のところ私一人しか出来ない技術だ。";
	next;
	mes "[細工職人・師範]";
	mes "三姉妹と同じように、";
	mes "その難易度によって3つのカテゴリーに";
	mes "分けさせてもらっている。";
	mes "^006400B級^000000⇒1回^9932CC　300,000Zeny^000000、";
	mes "^0000FFA級^000000⇒1回^9932CC　500,000Zeny^000000、";
	mes "^FF0000S級^000000⇒1回^9932CC1,000,000Zeny^000000だ。";
	next;
	mes "[細工職人・師範]";
	mes "では、カテゴリーと、";
	mes "エンチャント可能な兜の";
	mes "一覧から、希望を選んで欲しい。";
	next;
	switch(select("^006400B級^000000","^0000FFA級^000000","^FF0000S級^000000","やめる")) {
	case 1:
		set '@rank,0;
		set '@zeny$,"300,000";
		set '@price,300000;
		switch(select("^006400B級その①^000000","^006400B級その②^000000","やめる")) {
		case 1:
			switch(select(
				"赤いリボン[0]","ウサギのヘアバンド[0]","大きな金の鈴[0]","オールドスターロマンス[0]","おしゃれな帽子[0]",
				"海賊の頭巾[1]","カウボーイハット[0]","笠[0]","^0000FFかつらシリーズ^000000[⇒選択]","仮初めの恋[0]",
				"くま帽子[0]","黒い猫耳[0]","子犬のヘアバンド[0]","工事帽[0]","サークレット[1]"	,"やめる")) {

			case 1:	// 赤いリボン
				set '@enchantid,5083;
				break;
			case 2:	// ウサギのヘアバンド
				set '@enchantid,2214;
				break;
			case 3:	// 大きな金の鈴
				set '@enchantid,5091;
				break;
			case 4:	// オールドスターロマンス
				set '@enchantid,2247;
				break;
			case 5:	// おしゃれな帽子
				set '@enchantid,5032;
				break;
			case 6:	// S海賊の頭巾
				set '@enchantid,5350;
				break;
			case 7:	// カウボーイハット
				set '@enchantid,5075;
				break;
			case 8:	// 笠
				set '@enchantid,2280;
				break;
			case 9:	// かつらシリーズ（入れ子）
				switch(select( //長いのでかつらだけ3区切り
					"アフロかつら[1]","シャイニーアフロかつら[1]","ハッピーアフロかつら[1]",
					"ファンタスティックアフロかつら[1]","マーヴェラスアフロかつら[1]"
					)) {
					case 1:	// アフロかつら
						set '@enchantid,5258;
						break;
					case 2:	// シャイニーアフロかつら
						set '@enchantid,5274;
						break;
					case 3:	// ハッピーアフロかつら
						set '@enchantid,5273;
						break;
					case 4:	// ファンタスティックアフロかつら
						set '@enchantid,5276;
						break;
					case 5:	// マーヴェラスアフロかつら
						set '@enchantid,5275;
						break;
					}
				break;

			case 10:	// 仮初めの恋
				set '@enchantid,5008;
				break;
			case 11:	// くま帽子
				set '@enchantid,5059;
				break;
			case 12:	// 黒い猫耳
				set '@enchantid,5057;
				break;
			case 13:	// 子犬のヘアバンド
				set '@enchantid,5118;
				break;
			case 14:	// 工事帽
				set '@enchantid,5009;
				break;
			case 15:	// Sサークレット
				set '@enchantid,2233;
				break;
			case 16:	// やめる
				mes "[細工職人・師範]";
				mes "必要であれば、";
				mes "いつでも来て欲しい。";
				close;
			}
			break;

		case 2:
			switch(select(
				"シニョンキャップ[0]","スイートジェントル[0]","装飾用花[0]","装飾用ひまわり[1]","たぬき帽[0]",
				"^0000FFたれ猫シリーズ^000000[⇒選択]","花のヘアバンド[0]","パンダ帽[0]","ピエロの帽子[0]","ビレタ[1]",
				"ファッション防寒帽[0]","プロンテラ軍帽[0]","ポリン帽[0]","三日月のヘアピン[0]","野球帽[1]",
				"ラッコ帽[0]","やめる")) {

			case 1:	// シニョンキャップ
				set '@enchantid,5042;
				break;
			case 2:	// スイートジェントル
				set '@enchantid,2245;
				break;
			case 3:	// 装飾用花
				set '@enchantid,2207;
				break;
			case 4:	// S装飾用ひまわり
				set '@enchantid,5351;
				break;
			case 5:	// たぬき帽
				set '@enchantid,5033;
				break;
			case 6:	// たれ猫シリーズ（入れ子）
				switch(select(
					"たれ猫[0]","たれ猫（青）[0]","たれ猫（黄）[0]","たれ猫（白）[0]","たれ猫（灰）[0]",
					"たれ猫（桃）[0]"
					)) {

					case 1:	// たれ猫
						set '@enchantid,5058;
						break;
					case 2:	// たれ猫（青）
						set '@enchantid,5233;
						break;
					case 3:	// たれ猫（黄）
						set '@enchantid,5234;
						break;
					case 4:	// たれ猫（白）
						set '@enchantid,5230;
						break;
					case 5:	// たれ猫（灰）
						set '@enchantid,5231;
						break;
					case 6:	// たれ猫（桃）
						set '@enchantid,5232;
						break;
					}
				break;
			case 7:	// 花のヘアバンド
				set '@enchantid,2215;
				break;
			case 8:	// パンダ帽
				set '@enchantid,5030;
				break;
			case 9:	// ピエロの帽子
				set '@enchantid,5003;
				break;
			case 10:	// Sビレタ
				set '@enchantid,2217;
				break;
			case 11:	// ファッション防寒帽
				set '@enchantid,5115;
				break;
			case 12:	// プロンテラ軍帽
				set '@enchantid,2261;
				break;
			case 13:	// ポリン帽
				set '@enchantid,5035;
				break;
			case 14:	// 三日月のヘアピン
				set '@enchantid,5048;
				break;
			case 15:	// 野球帽
				set '@enchantid,5147;
				break;
			case 16:	// ラッコ帽
				set '@enchantid,5078;
				break;
			case 17:	// やめる
				mes "[細工職人・師範]";
				mes "必要であれば、";
				mes "いつでも来て欲しい。";
				close;
			}
			break;
		case 3:	// やめる
			mes "[細工職人・師範]";
			mes "必要であれば、";
			mes "いつでも来て欲しい。";
			close;
		}
		break;

	case 2:	// A級
		set '@rank,1;
		set '@zeny$,"500,000";
		set '@price,500000;
		switch(select("^0000FFA級その①^000000","^0000FFA級その②^000000","やめる")) {
		case 1:	// A級その①
			switch(select(
				"悪魔のヘアバンド[0]","インキュバスの角[0]","オーク族のヘルム[1]","お金を失った者の心[0]","学生帽[1]","看護帽[0]",
				"狐のお面[0]","^0000FF子悪魔シリーズ^000000[⇒選択]","ゴーグル[1]","コルセア[1]",
				"サキュバスの角[0]","サテライトヘアバンド[1]","やめる")) {

			case 1:	// 悪魔のヘアバンド
				set '@enchantid,2255;
				break;
			case 2:	// インキュバスの角
				set '@enchantid,5072;
				break;
			case 3:	// Sオーク族のヘルム
				set '@enchantid,5157;
				break;
			case 4:	// お金を失った者の心
				set '@enchantid,5021;
				break;
			case 5:	// S学生帽
				set '@enchantid,5349;
				break;
			case 6:	// 看護帽
				set '@enchantid,2277;
				break;
			case 7:	// 狐のお面
				set '@enchantid,5069;
				break;
			case 8:	// 子悪魔シリーズ（入れ子）
				switch(select("子悪魔帽[0]","子悪魔帽（赤）[0]","子悪魔帽（白）[0]","子悪魔帽（灰）[0]")) {
				case 1:	// 子悪魔帽
					set '@enchantid,5038;
					break;
				case 2:	// 子悪魔帽（赤）
					set '@enchantid,5227;
					break;
				case 3:	// 子悪魔帽（白）
					set '@enchantid,5228;
					break;
				case 4:	// 子悪魔帽（灰）
					set '@enchantid,5229;
					break;
				}
				break;
			case 9:	// Sゴーグル
				set '@enchantid,2225;
				break;
			case 10:	// Sコルセア
				set '@enchantid,5163;
				break;
			case 11:	// サキュバスの角
				set '@enchantid,5066;
				break;
			case 12:	// サテライトヘアバンド
				set '@enchantid,5212;
				break;
			case 13:	// やめる
				mes "[細工職人・師範]";
				mes "必要であれば、";
				mes "いつでも来て欲しい。";
				close;
			}
			break;
		case 2:	// A級その②
			switch(select(
				"シャープヘッドギア[1]","スーパーノービス帽[1]","聖職者の帽子[1]","天使のヘアバンド[0]","熱血鉢巻き[0]",
				"ブルーリボン[1]","ヘルム[1]","ボーンヘルム[0]","マジェスティックゴート[0]","丸いぼうし[1]",
				"ミストレスの王冠[0]","やめる")) {

			case 1:	// Sシャープヘッドギア
				set '@enchantid,5161;
				break;
			case 2:	// Sスーパーノービス帽
				set '@enchantid,5119;
				break;
			case 3:	// S聖職者の帽子
				set '@enchantid,5158;
				break;
			case 4:	// 天使のヘアバンド
				set '@enchantid,2254;
				break;
			case 5:	// 熱血鉢巻き
				set '@enchantid,5070;
				break;
			case 6:	// Sブルーリボン
				set '@enchantid,5404;
				break;
			case 7:	// Sヘルム
				set '@enchantid,2229;
				break;
			case 8:	// ボーンヘルム
				set '@enchantid,5017;
				break;
			case 9:	// マジェスティックゴート
				set '@enchantid,2256;
				break;
			case 10:	// S丸いぼうし
				set '@enchantid,2223;
				break;
			case 11:	// ミストレスの王冠
				set '@enchantid,5081;
				break;
			case 12:	// やめる
				mes "[細工職人・師範]";
				mes "必要であれば、";
				mes "いつでも来て欲しい。";
				close;
			}
			break;
		case 3:	// やめる
			mes "[細工職人・師範]";
			mes "必要であれば、";
			mes "いつでも来て欲しい。";
			close;
		}
		break;
	case 3:	// S級
		set '@rank,2;
		set '@zeny$,"1,000,000";
		set '@price,1000000;
		switch(select(
			"かわいいリボン[1]","ドレスハット[1]","ハイビスカス[0]","パレード帽[1]","マジェスティックゴート[1]",
			"マジックアイズ[0]","やめる")) {

		case 1:	// かわいいリボン
			set '@enchantid,5140;
			break;
		case 2:	// ドレスハット
			set '@enchantid,5211;
			break;
		case 3:	// ハイビスカス
			set '@enchantid,5139;
			break;
		case 4:	// パレード帽
			set '@enchantid,5468;
			break;
		case 5:	// Sマジェスティックゴート
			set '@enchantid,5160;
			break;
		case 6:	// マジックアイズ
			set '@enchantid,5138;
			break;
		case 7:	// やめる
			mes "[細工職人・師範]";
			mes "必要であれば、";
			mes "いつでも来て欲しい。";
			close;
		}
		break;
	case 4:	// やめる
		mes "[細工職人・師範]";
		mes "必要であれば、";
		mes "いつでも来て欲しい。";
		close;
	}
	if(countitem('@enchantid) != 1) {
		mes "[細工職人・師範]";
		mes "……案内にもある通り";
		mes "^0000FF対象の兜を1つだけ持った状態^000000で";
		mes "お願いする。";
		mes "持っていないのは論外だが";
		mes "2つ以上持たないで欲しい。";
		close;
	}
	mes "[細工職人・師範]";
	mes "^0000FF" +getitemname('@enchantid)+ "[" +getiteminfo('@enchantid,10)+ "]^000000でいいのだな。";
	mes "では、最終確認だ。";
	mes "まず、手数料として";
	mes "^0000FF"+'@zeny$+ "Zeny^000000をいただく。";
	next;
	mes "[細工職人・師範]";
	mes "そして、エンチャントは";
	mes "必ずしも成功するとは限らない。";
	mes "^FF0000失敗すると、兜は消えてしまう^000000。";
	mes "また、成功すると、いままでの";
	mes "^FF0000精錬値及び挿していたカードが";
	mes "消えてしまう^000000。";
	next;
	mes "[細工職人・師範]";
	mes "さあ、エンチャントを行うか？";
	next;
	if(select("^FF0000今回はやめておく^000000","^0000FFお願いします^000000") == 1) {
		mes "[細工職人・師範]";
		mes "必要であれば、";
		mes "いつでも来て欲しい。";
		close;
	}
	mes "[細工職人・師範]";
	mes "わかった。";
	mes "では、始めようか。";
	next;
	if(Zeny < '@price) {
		mes "[細工職人・師範]";
		mes "……おや、Zenyが";
		mes "足りなくなっているようだぞ。";
		close;
	}
	delitem '@enchantid,1;
	set Zeny,Zeny-'@price;
	switch('@rank) {	// 確率不明なので暫定で鎧HSEと同一
	case 0:	set '@rate,50;	break;
	case 1:	set '@rate,55;	break;
	case 2:	set '@rate,60;	break;
	}
	set '@succsess,rand(1,'@rate);
	if((6 + 12 + 18) >= '@succsess) {
		//成功
		switch(rand(6)) {
		case 0:	set '@cardid,4768;	break;
		case 1:	set '@cardid,4771;	break;
		case 2:	set '@cardid,4774;	break;
		case 3:	set '@cardid,4777;	break;
		case 4:	set '@cardid,4780;	break;
		case 5:	set '@cardid,4783;	break;
		}
		if('@succsess <= 6)
			set '@cardid, '@cardid+2;
		else if('@succsess <= 18)
			set '@cardid, '@cardid+1;
		getitem2 '@enchantid,1,1,0,0,0,0,0,'@cardid;
		mes "[細工職人・師範]";
		mes "……ふう、成功だ！";
		mes "大切に使って欲しい。";
		close;
	}
	mes "[細工職人・師範]";
	mes "うっ……!!";
	mes "エンチャントに失敗したか……";
	mes "すまなかったな……";
	close;
}

prontera.gat,85,110,6	script	細工案内板	857,{
	mes "【^9932CCHSE・HSEEXのご案内^000000】";
	mes "我々は、^0000FFHSE^000000こと";
	mes "^0000FFヒドゥンスロットエンチャント^000000の";
	mes "技術を提供している、職人集団です。";
	mes "もし、まだご利用した経験がなく、";
	mes "ご興味のある方は、";
	mes "必ずご一読くださいませ。";
	next;
	switch(select("^0000FFHSE^000000とは？","^006400HSEEX^000000とは？","やめる")) {
	case 1:
		mes "【^0000FFHSEとは^000000】";
		mes "^0000FFヒドゥンスロットエンチャント^000000";
		mes "（以下HSE）とは、";
		mes "^FF0000鎧^000000の隠されたスロットに";
		mes "神秘的な力を吹き込む技術のことです。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "現在の技術では、";
		mes "Str、Agi、Vit、Dex、Int、Lukの";
		mes "どれかが、+1～+3のどれかの値で";
		mes "付与されることになります。";
		mes "パターンは計18種となります。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "注意すべき点として、";
		mes "この技術の施行は難易度が高く、";
		mes "^FF0000必ずしも成功しません^000000。";
		mes "失敗してしまっても、";
		mes "我々は責任を負うことはできません。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "次に、エンチャントすると、";
		mes "^FF0000それまでの精錬値や";
		mes "挿していたカードは消えます^000000。";
		mes "全く新しい鎧に生まれ変わるのです。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "最後に、";
		mes "エンチャントしようとした際、";
		mes "^FF0000同じ対象鎧を複数お持ちの場合、";
		mes "所持している順に";
		mes "エンチャントされます^000000。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "例えば精錬済みのメイルと、";
		mes "未精錬のメイルを持っており、";
		mes "メイルをエンチャントした場合……";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "未精錬のメイルをエンチャント";
		mes "したかったとしても、";
		mes "精錬済みのメイルが";
		mes "エンチャントされる可能性があります。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "望んでいない方の鎧が";
		mes "エンチャントされてしまうことを";
		mes "避ける為にも、";
		mes "エンチャントしたい鎧は";
		mes "^0000FF1個だけ^000000持っているように";
		mes "してください。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "もし、同じアイテムを";
		mes "複数持った状態で、何が起きても";
		mes "我々は責任を負えません。";
		mes "ご了承ください。";
		next;
		mes "【^0000FFHSEとは^000000】";
		mes "なお、技術提供料金は、";
		mes "難易度により異なります。";
		mes "詳細は、それぞれの担当員に";
		mes "お尋ねください。";
		close;
	case 2:
		mes "【^006400HSEEX^000000とは？】";
		mes "^006400HSEEX^000000とは、最近";
		mes "新たに研究が進んだ技術で、便宜上";
		mes "ヒドゥンスロットエンチャントEXと";
		mes "命名したものであり、";
		mes "^FF0000兜^000000の隠されたスロットに";
		mes "新たな力を吹き込む技術のことです。";
		next;
		mes "【^006400HSEEX^000000とは？】";
		mes "付与される能力や、";
		mes "実施の際の注意点は、通常の";
		mes "^0000FFHSE^000000と変わりません。";
		mes "^0000FFHSE^000000の項目を";
		mes "あわせてご確認ください。";
		close;
	case 3:
		mes "【^9932CCHSE・HSEEXのご案内^000000】";
		mes "またのご利用を";
		mes "お待ちしております。";
		close;
	}
}
