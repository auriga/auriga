//====================================================================
//Ragnarok Online   Town Guide Script
//
//  ■ @compass -> ミニMAP表示のon/off
//		0x0001	プロンテラ
//		0x0002	イズルード
//		0x0004	ゲフェン
//		0x0008	フェイヨン
//		0x0010	フェイヨン弓手村
//		0x0020	アルベルタ
//		0x0040	モロク
//		0x0080	アインブログ
//		0x0100	アインベフ
//		0x0200	リヒタルゼン
//		0x0400	フィゲル
//		0x0800	ラヘル
//		0x1000	ベインス
//		0x2000	ブラジリス
//====================================================================

//[案内要員 - プロンテラ]
prontera.gat,154,196,4	script	案内要員#prontera	105,{
	cutin "prt_soldier",2;
	mes "[プロンテラ 案内要員]";
	mes "ようこそ、ルーンミッドガッツ王国の";
	mes "美しい首都プロンテラへ";
	mes "私達はここプロンテラにいらした";
	mes "旅人達の為に街の道案内をしています。";
	mes "分からない事があれば、いつでも私達";
	mes "案内要員に聞いてください。";
	next;
	mes "[プロンテラ 案内要員]";
	mes "私達の道案内を初めて聞く方は";
	mes "「告知事項」メニューを";
	mes "選んでください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[プロンテラ 案内要員]";
			mes "それではご案内いたしましょう。";
			if(@compass&0x001 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x001;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			next;
			mes "[プロンテラ 案内要員]";
			mes "案内を受けたい場所を選んでください。";
			while(1) {
				next;
				switch (select("剣士ギルド","^0000FF大聖堂^000000","騎士団","武器屋","道具屋","旅館",
							"精錬所","酒場","図書館","研究所","プロンテラ城","事務所","取り消し")) {
				case 1:
					mes "[プロンテラ 案内要員]";
					mes "剣士転職の業務を扱う";
					mes "「剣士ギルド」は";
					mes "衛星都市イズルードへ移って";
					mes "現在のプロンテラには";
					mes "空家が残っています。";
					if(@compass&0x001)
						viewpoint 1,237,41,1,0x00FF00;
					continue;
				case 2:
					mes "[プロンテラ 案内要員]";
					mes "アコライトへの転職業務を扱う";
					mes "「大聖堂」は街の北東";
					mes "外周街にあります。";
					mes "時計方向では2時の方向です。";
					if(@compass&0x001)
						viewpoint 1,236,316,2,0xFF0000;
					continue;
				case 3:
					mes "[プロンテラ 案内要員]";
					mes "ルーンミッドガッツ王国の";
					mes "首都プロンテラを守る";
					mes "「騎士団」の本部は街の北西";
					mes "外周街にあります。";
					mes "時計方向では10時の方向です。";
					if(@compass&0x001)
						viewpoint 1,46,345,3,0x00FF00;
					continue;
				case 4:
					mes "[プロンテラ 案内要員]";
					mes "「武器屋」は噴水広場の";
					mes "北東部にあります。";
					if(@compass&0x001)
						viewpoint 1,175,220,4,0xFF00FF;
					continue;
				case 5:
					mes "[プロンテラ 案内要員]";
					mes "「道具屋」は噴水広場の";
					mes "北西部にあります。";
					if(@compass&0x001)
						viewpoint 1,134,221,5,0xFF00FF;
					continue;
				case 6:
					mes "[プロンテラ 案内要員]";
					mes "「旅館」は噴水広場の";
					mes "東側と西側にあります。";
					if(@compass&0x001) {
						viewpoint 1,204,214,6,0xFF00FF;
						viewpoint 1,107,192,7,0xFF00FF;
					}
					continue;
				case 7:
					mes "[プロンテラ 案内要員]";
					mes "「精錬所」は噴水広場の";
					mes "南東部にあります。";
					if(@compass&0x001)
						viewpoint 1,179,184,8,0x00FF00;
					continue;
				case 8:
					mes "[プロンテラ 案内要員]";
					mes "「酒場」は噴水広場の";
					mes "南東部、精錬所の後側にあります。";
					if(@compass&0x001)
						viewpoint 1,208,154,9,0x00FF00;
					continue;
				case 9:
					mes "[プロンテラ 案内要員]";
					mes "「図書館」は噴水広場から";
					mes "北へ進む道の東側と西側にあります。";
					if(@compass&0x001) {
						viewpoint 1,120,267,10,0x00FF00;
						viewpoint 1,192,267,11,0x00FF00;
					}
					continue;
				case 10:
					mes "[プロンテラ 案内要員]";
					mes "「研究所」は噴水広場の";
					mes "南西部にあります。";
					if(@compass&0x001)
						viewpoint 1,133,183,12,0x00FF00;
					continue;
				case 11:
					mes "[プロンテラ 案内要員]";
					mes "「プロンテラ城」は街の北";
					mes "橋を渡ったところにあります。";
					mes "時計方向では12時の方向です。";
					mes "城の後門から外へ出ると";
					mes "北プロンテラ地方へ繋がっています。";
					if(@compass&0x001)
						viewpoint 1,156,360,13,0x00FF00;
					continue;
				case 12:
					mes "[プロンテラ 案内要員]";
					mes "「事務所」は街の南東";
					mes "外周街にあります。";
					mes "時計方向では7時の方向です。";
					if(@compass&0x001)
						viewpoint 1,75,91,14,0x00FF00;
					continue;
				case 13:
					mes "[プロンテラ 案内要員]";
					mes "位置標識を消したい時は";
					mes "「ミニMAP上の位置表示を消す」を";
					mes "選んでください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,237,41,1,0x00FF00;
			viewpoint 2,236,316,2,0xFF0000;
			viewpoint 2,46,345,3,0x00FF00;
			viewpoint 2,175,220,4,0xFF00FF;
			viewpoint 2,8,134,5,0xFF00FF;
			viewpoint 2,204,214,6,0xFF00FF;
			viewpoint 2,107,192,7,0xFF00FF;
			viewpoint 2,179,184,8,0x00FF00;
			viewpoint 2,208,154,9,0x00FF00;
			viewpoint 2,120,267,10,0x00FF00;
			viewpoint 2,192,267,11,0x00FF00;
			viewpoint 2,133,183,12,0x00FF00;
			viewpoint 2,156,360,13,0x00FF00;
			viewpoint 2,75,91,14,0x00FF00;
			set @compass,@compass&~0x001;
			set '@flag,0;
			continue;
		case 3:
			mes "[プロンテラ 案内要員]";
			mes "既存のアナログ案内方式から";
			mes "知りたい場所をミニMAPに";
			mes "表示してくれる、広域案内システムを";
			mes "利用した最先端デジタル案内方式に";
			mes "進化しました。";
			next;
			mes "[プロンテラ 案内要員]";
			mes "ルーンミッドガッツ王国の";
			mes "すばらしい魔法と、科学技術の";
			mes "組み合わせで作り出した";
			mes "この広域案内システムの性能を";
			mes "ぜひご覧下さい。";
			next;
			mes "[プロンテラ 案内要員]";
			mes "本案内をご利用いただく前に";
			mes "まずモニター右上にある";
			mes "ミニMAPをご覧下さい。";
			next;
			mes "[プロンテラ 案内要員]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウィンドウの";
			mes "「map」ボタンをクリックして下さい。";
			next;
			mes "[プロンテラ 案内要員]";
			mes "ミニMAPが表示されたら";
			mes "^3355FF -^000000ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定して下さい。";
			continue;
		case 4:
			mes "[プロンテラ 案内要員]";
			mes "それではよい旅を！";
			close2;
			cutin "prt_soldier",255;
			end;
		}
	}
}

prontera.gat,282,208,2	duplicate(案内要員#prontera)	東門-案内要員	105
prontera.gat,29,200,6	duplicate(案内要員#prontera)	西門-案内要員	105
prontera.gat,160,29,0	duplicate(案内要員#prontera)	南門-案内要員	105
prontera.gat,151,330,4	duplicate(案内要員#prontera)	北門-案内要員	105


//----------------------------------------------------------------------
//[案内要員 - イズルード]

izlude.gat,123,87,6	script	案内要員	105,{
	cutin "prt_soldier",2;
	mes "[イズルード案内要員]";
	mes "衛星都市イズルードにようこそ！";
	mes "私はこのイズルードの道案内を";
	mes "担当している公益公務員です。";
	mes "建物の位置について知りたいなら";
	mes "いつでも聞いてください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[イズルード案内要員]";
			mes "それでは案内します。";
			if(@compass&0x002 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x002;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000剣士ギルド^000000","剣士協会","アリーナ","船着場","武器屋","道具屋","取り消し")) {
				case 1:
					mes "[イズルード案内要員]";
					mes "剣士に転職したいのですか？";
					if(@compass&0x002)
						viewpoint 1,52,140,1,0xFF0000;
					continue;
				case 2:
					mes "[イズルード案内要員]";
					mes "剣士関連の仕事を処理する";
					mes "剣士協会は、東側にあります。";
					if(@compass&0x002)
						viewpoint 1,214,130,2,0x00FF00;
					continue;
				case 3:
					mes "[イズルード案内要員]";
					mes "イズルードの名物「アリーナ」は";
					mes "北にあります。12時方向です。";
					mes "私の兄貴がそこの関係者なんですけど";
					mes "アリーナはまだ未公開らしいです。";
					mes "今行っても無駄だと思います。";
					if(@compass&0x002)
						viewpoint 1,128,225,3,0x00FF00;
					continue;
				case 4:
					mes "[イズルード案内要員]";
					mes "「アルベルタ」や「バイラン島」に";
					mes "行くことができる船着場は北東に";
					mes "あります。MAPでは2時方向です。";
					if(@compass&0x002)
						viewpoint 1,200,180,4,0xFF0000;
					continue;
				case 5:
					mes "[イズルード案内要員]";
					mes "武器屋は北西にあります。";
					mes "近くですので、すぐ見つかるでしょう。";
					if(@compass&0x002)
						viewpoint 1,111,149,5,0xFF00FF;
					continue;
				case 6:
					mes "[イズルード案内要員]";
					mes "道具屋は北東にあります。";
					mes "近くですので、すぐ見つかるでしょう。";
					if(@compass&0x002)
						viewpoint 1,148,148,6,0xFF00FF;
					continue;
				case 7:
					mes "[イズルード 案内要員]";
					mes "表示位置を消したいなら";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,52,140,1,0xFF0000;
			viewpoint 2,214,130,2,0x00FF00;
			viewpoint 2,128,225,3,0x00FF00;
			viewpoint 2,200,180,4,0xFF0000;
			viewpoint 2,111,149,5,0xFF00FF;
			viewpoint 2,148,148,6,0xFF00FF;
			set @compass,@compass&~0x002;
			set '@flag,0;
			continue;
		case 3:
			mes "[イズルード案内要員]";
			mes "既存のアナログ案内方式から";
			mes "知りたい場所をミニMAPに";
			mes "表示してくれる、広域案内システムを";
			mes "利用した最先端デジタル案内方式に";
			mes "進化しました。";
			next;
			mes "[イズルード案内要員]";
			mes "ルーンミッドガッツ王国の";
			mes "すばらしい魔法と、科学技術の";
			mes "組み合わせで作り出した";
			mes "この広域案内システムの性能を";
			mes "ぜひご覧ください。";
			next;
			mes "[イズルード案内要員]";
			mes "本案内をご利用いただく前に";
			mes "まずモニター右上にある";
			mes "ミニMAPをご覧下さい。";
			next;
			mes "[イズルード案内要員]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウィンドウの";
			mes "「map」ボタンをクリックして下さい。";
			next;
			mes "[イズルード案内要員]";
			mes "ミニMAPが表示されたら";
			mes " -ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定して下さい。";
			continue;
		case 4:
			mes "[イズルード案内要員]";
			mes "聞きたい場所があったら";
			mes "いつでも言ってください。";
			close2;
			cutin "prt_soldier",255;
			end;
		}
	}
}

//----------------------------------------------------------------------
//[案内要員 - ゲフェン]

geffen.gat,203,116,0	script	案内要員#geffen	705,{
	cutin "gef_soldier",2;
	mes "[ゲフェン案内要員]";
	mes "魔法の都市ゲフェンに良くぞ参られた。";
	mes "我等はここ、ゲフェンに参った";
	mes "旅人のために街の案内をしておる。";
	mes "街のことなら何でも聞かれよ。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[ゲフェン案内要員]";
			mes "それでは案内いたそう。";
			if(@compass&0x004 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残すか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x004;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000魔法学校^000000","鍛冶屋","武器屋","道具屋","酒場","旅館","取り消し")) {
				case 1:
					mes "[ゲフェン案内要員]";
					mes "マジシャンの転職業務を";
					mes "処理する「魔法学校」である。";
					if(@compass&0x004)
						viewpoint 1,61,180,1,0xFF0000;
					continue;
				case 2:
					mes "[ゲフェン案内要員]";
					mes "「ブラックスミスギルド」は";
					mes "MAPの中心から南東方向に";
					mes "位置しておる。";
					if(@compass&0x004)
						viewpoint 1,182,59,2,0x00FF00;
					continue;
				case 3:
					mes "[ゲフェン案内要員]";
					mes "「武器屋」はMAPの中心から";
					mes "北西方向に位置しておる。";
					if(@compass&0x004)
						viewpoint 1,99,140,3,0xFF00FF;
					continue;
				case 4:
					mes "[ゲフェン案内要員]";
					mes "「道具屋」はMAPの中心から";
					mes "南西方向に位置しておる。";
					if(@compass&0x004)
						viewpoint 1,44,86,4,0xFF00FF;
					continue;
				case 5:
					mes "[ゲフェン案内要員]";
					mes "「酒場」はMAPの中心から";
					mes "北東方向に位置しておる。";
					if(@compass&0x004)
						viewpoint 1,138,138,5,0xFF00FF;
					continue;
				case 6:
					mes "[ゲフェン案内要員]";
					mes "「旅館」はMAPの中心から";
					mes "北東方向に位置しておる。";
					if(@compass&0x004)
						viewpoint 1,172,174,6,0xFF00FF;
					continue;
				case 7:
					mes "[ゲフェン案内要員]";
					mes "位置表示を消したい場合は";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択するが宜しい。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,61,180,1,0xFF0000;
			viewpoint 2,182,59,2,0x00FF00;
			viewpoint 2,99,140,3,0xFF00FF;
			viewpoint 2,44,86,4,0xFF00FF;
			viewpoint 2,138,138,5,0xFF00FF;
			viewpoint 2,172,174,6,0xFF00FF;
			set @compass,@compass&~0x004;
			set '@flag,0;
			continue;
		case 3:
			mes "[ゲフェン 案内要員]";
			mes "既存のアナログ案内方式を廃止し";
			mes "知りたい場所がミニMAPに表示される";
			mes "よう、広域検索システムを利用した";
			mes "最先端デジタル案内方式に";
			mes "変更されたのだ。";
			next;
			mes "[ゲフェン 案内要員]";
			mes "ルーンミッドガッツ王国に存在する";
			//mes "あるこの広組案内システムの性能を";	//本鯖仕様
			mes "すばらしい魔法と、科学技術の粋で";
			mes "あるこの広域案内システムの性能を";
			mes "しかとご覧になると宜しい。";
			next;
			mes "[ゲフェン 案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニMAPを確認して頂きたい。";
			mes "ミニMAPが見えない場合は";
			mes "「ctrl+tab」、または";
			mes "基本ウィンドウで「map」";
			mes "ボタンをクリックすれば良い。";
			next;
			mes "[ゲフェン 案内要員]";
			mes "ミニMAPが見えたら";
			mes "「-」ボタンを再度クリックし、";
			mes "街全体が見えるように設定するが";
			mes "良かろう。";
			continue;
		case 4:
			mes "[ゲフェン案内要員]";
			mes "良い旅を……";
			close2;
			cutin "gef_soldier",255;
			end;
		}
	}
}

geffen.gat,118,62,0	duplicate(案内要員#geffen)	案内要員	705


//----------------------------------------------------------------------
//[案内要員 - フェイヨン]

payon.gat,162,67,4	script	案内要員	708,{
	cutin "pay_soldier",2;
	mes "[フェイヨン案内要員]";
	mes "山岳都市フェイヨンにようこそ。";
	mes "私達はここフェイヨンにいらした";
	mes "旅人さん達のために、町の案内を";
	mes "しております。";
	while(1) {
		next;
		switch (select("町の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[フェイヨン案内要員]";
			mes "それではご案内します。";
			if(@compass&0x008 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x008;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000アーチャーギルド^000000","武器・防具屋","道具屋","酒場","中央宮",
									"宮殿の前庭","宮殿の別館","弓手の間","精錬所","取り消し")) {
				case 1:
					mes "[フェイヨン案内要員]";
					mes "アーチャー転職業務を処理する";
					mes "「アーチャーギルド」です。";
					mes "弓手村の北東方面にあります。";
					if(@compass&0x008)
						viewpoint 1,228,325,1,0xFF0000;
					continue;
				case 2:
					mes "[フェイヨン案内要員]";
					mes "「武器・防具屋」は";
					mes "この印の位置にあります。";
					if(@compass&0x008)
						viewpoint 1,138,158,2,0xFF00FF;
					continue;
				case 3:
					mes "[フェイヨン案内要員]";
					mes "「道具屋」はこの印の北にあります。";
					mes "また、この印の西側の建物の中にも";
					mes "あります。";
					if(@compass&0x008)
						viewpoint 1,149,87,3,0xFF00FF;
					continue;
				case 4:
					mes "[フェイヨン案内要員]";
					mes "「酒場」はこの印の東南の";
					mes "方向にあります。";
					if(@compass&0x008)
						viewpoint 1,220,117,4,0xFF00FF;
					continue;
				case 5:
					mes "[フェイヨン案内要員]";
					mes "「中央宮」はこの印の";
					mes "北側にあります。";
					if(@compass&0x008)
						viewpoint 1,156,243,5,0x00FF00;
					continue;
				case 6:
					mes "[フェイヨン案内要員]";
					mes "「宮殿の前庭」はこの印の";
					mes "北西の方向にあります。";
					if(@compass&0x008)
						viewpoint 1,107,320,6,0x00FF00;
					continue;
				case 7:
					mes "[フェイヨン案内要員]";
					mes "「宮殿の別館」はこの印の";
					mes "西側にあります。";
					if(@compass&0x008)
						viewpoint 1,135,194,7,0x00FF00;
					continue;
				case 8:
					mes "[フェイヨン案内要員]";
					mes "「弓手の間」はこの印の";
					mes "北側にあります。";
					if(@compass&0x008)
						viewpoint 1,155,324,8,0x00FF00;
					continue;
				case 9:
					mes "[フェイヨン案内要員]";
					mes "「精錬所」はこの印の位置にあります。";
					if(@compass&0x008)
						viewpoint 1,144,169,9,0x00FF00;
					continue;
				case 10:
					mes "[フェイヨン案内要員]";
					mes "位置表示を消したい場合は";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,228,325,1,0xFF0000;
			viewpoint 2,138,158,2,0xFF00FF;
			viewpoint 2,149,87,3,0xFF00FF;
			viewpoint 2,220,117,4,0xFF00FF;
			viewpoint 2,156,243,5,0x00FF00;
			viewpoint 2,107,320,6,0x00FF00;
			viewpoint 2,135,194,7,0x00FF00;
			viewpoint 2,155,324,8,0x00FF00;
			viewpoint 2,144,169,9,0x00FF00;
			set @compass,@compass&~0x008;
			set '@flag,0;
			continue;
		case 3:
			mes "[フェイヨン案内要員]";
			mes "既存のアナログ案内方式を廃止し、";
			mes "知りたい場所をミニMAPに表示して";
			mes "くれる、広域検索システムを利用した";
			mes "最先端デジタル案内方式に";
			mes "変わったんです。";
			next;
			mes "[フェイヨン案内要員]";
			mes "ルーンミッドガッツ王国に存在する";
			mes "すばらしい魔法と、科学技術の粋で";
			//mes "あるこの広組検索システムの性能を";	//本鯖仕様
			mes "あるこの広域検索システムの性能を";
			mes "直接その目で見てください。";
			next;
			mes "[フェイヨン案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニMAPを確認してください。";
			mes "ミニMAPが見えなかったら、";
			mes "「ctrl+tab」または";
			mes "基本ウインドウで「map」";
			mes "ボタンをクリックします。";
			next;
			mes "[フェイヨン案内要員]";
			mes "ミニMAPが見えたら";
			mes "「-」ボタンを再度クリックして、";
			mes "町全体が見えるように設定した方が";
			mes "良いでしょう。";
			continue;
		case 4:
			mes "[フェイヨン案内要員]";
			mes "良い旅になりますように。";
			close2;
			cutin "pay_soldier",255;
			end;
		}
	}
}

pay_arche.gat,85,30,2	script	案内要員	708,{
	cutin "pay_soldier",2;
	mes "[フェイヨン案内要員]";
	mes "山岳都市フェイヨンにようこそ。";
	mes "私はここフェイヨンにいらした";
	mes "旅人さん達のために、街の案内を";
	mes "しております。";
	while(1) {
		next;
		switch (select("町の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[フェイヨン案内要員]";
			mes "それではご案内します。";
			if(@compass&0x010 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x010;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000アーチャーギルド^000000","道具屋","フェイヨンダンジョン","取り消し")) {
				case 1:
					mes "[フェイヨン案内要員]";
					mes "アーチャー転職業務を処理する";
					mes "「アーチャーギルド」です。";
					mes "弓手村の北東方面にあります。";
					if(@compass&0x010)
						viewpoint 1,144,164,1,0xFF0000;
					continue;
				case 2:
					mes "[フェイヨン案内要員]";
					mes "「道具屋」はMAPの中心から";
					mes "北方向にあります。";
					if(@compass&0x010)
						viewpoint 1,71,156,2,0xFF00FF;
					continue;
				case 3:
					mes "[フェイヨン案内要員]";
					mes "「フェイヨンダンジョン」はMAPの";
					mes "中心から北西方面にあります。";
					if(@compass&0x010)
						viewpoint 1,34,132,3,0xFFFFFF;
					continue;
				case 4:
					mes "[フェイヨン案内要員]";
					mes "位置表示を消したい場合は";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,144,164,1,0xFF0000;
			viewpoint 2,71,156,2,0xFF00FF;
			viewpoint 2,34,132,3,0xFFFFFF;
			set @compass,@compass&~0x010;
			set '@flag,0;
			continue;
		case 3:
			mes "[フェイヨン案内要員]";
			mes "既存のアナログ案内方式を廃止し、";
			mes "知りたい場所をミニMAPに表示して";
			mes "くれる、広域検索システムを利用した";
			mes "最先端デジタル案内方式に";
			mes "変わったんです。";
			next;
			mes "[フェイヨン案内要員]";
			mes "ルーンミッドガッツ王国に存在する";
			mes "すばらしい魔法と、科学技術の粋で";
			mes "あるこの広域検索システムの性能を";
			mes "直接その目で見てください。";
			next;
			mes "[フェイヨン案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニMAPを確認してください。";
			mes "ミニMAPが見えなかったら、";
			mes "「ctrl+tab」または";
			mes "基本ウィンドウで「map」";
			mes "ボタンをクリックします。";
			next;
			mes "[フェイヨン案内要員]";
			mes "ミニMAPが見えたら";
			mes "「-」ボタンを再度クリックして、";
			mes "町全体が見えるように設定した方が";
			mes "良いでしょう。";
			continue;
		case 4:
			mes "[フェイヨン案内要員]";
			mes "良い旅になりますように。";
			close2;
			cutin "pay_soldier",255;
			end;
		}
	}
}

//----------------------------------------------------------------------
//[案内要員 - アルベルタ]

alberta.gat,23,238,4	script	案内要員#alberta	105,{
	cutin "prt_soldier",2;
	mes "[アルベルタ案内要員]";
	mes "港の都市アルベルタにようこそ。";
	mes "私達はここアルベルタに訪れた";
	mes "旅人達のために、街の案内をして";
	mes "おります。";
	mes "街の各所について知りたかったら";
	mes "いつでも聞いてください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[アルベルタ案内要員]";
			mes "知りたい場所を選んで下さい。";
			if(@compass&0x020 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x020;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000商人協会^000000","武器屋","道具屋","旅館","取り消し")) {
				case 1:
					mes "[アルベルタ案内要員]";
					mes "商人転職業務を処理する";
					mes "「商人組合」です。";
					if(@compass&0x020)
						viewpoint 1,33,41,1,0xFF0000;
					continue;
				case 2:
					mes "[アルベルタ案内要員]";
					mes "「武器屋」はMAPの南端に";
					mes "あります。";
					if(@compass&0x020)
						viewpoint 1,117,37,2,0xFF00FF;
					continue;
				case 3:
					mes "[アルベルタ案内要員]";
					mes "「道具屋」はMAPの中心付近に";
					mes "あります。";
					if(@compass&0x020)
						viewpoint 1,98,154,3,0xFF00FF;
					continue;
				case 4:
					mes "[アルベルタ案内要員]";
					//mes "「旅館」はMAPの北側にありあます。";	//本鯖仕様
					mes "「旅館」はMAPの北側にあります。";
					if(@compass&0x020)
						viewpoint 1,65,233,4,0xFF00FF;
					continue;
				case 5:
					mes "[アルベルタ案内要員]";
					mes "位置表示を消したい場合は";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,33,41,1,0xFF0000;
			viewpoint 2,117,37,2,0xFF00FF;
			viewpoint 2,98,154,3,0xFF00FF;
			viewpoint 2,65,233,4,0xFF00FF;
			set @compass,@compass&~0x020;
			set '@flag,0;
			continue;
		case 3:
			mes "[アルベルタ案内要員]";
			mes "既存のアナログ案内方式を廃止し、";
			mes "知りたい場所をミニMAPに表示して";
			mes "くれる、広域検索システムを利用した";
			mes "最先端デジタル案内方式に";
			mes "変わったんです。";
			next;
			mes "[アルベルタ案内要員]";
			mes "ルーンミッドガッツ王国に存在する";
			mes "すばらしい魔法と、科学技術の粋で";
			//mes "あるこの広組検索システムの性能を";	//本鯖仕様
			mes "あるこの広域検索システムの性能を";
			mes "直接その目で見てください。";
			next;
			mes "[アルベルタ案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニMAPを確認してください。";
			mes "ミニMAPが見えなかったら、";
			mes "「ctrl+tab」または";
			mes "基本ウィンドウで「map」";
			mes "ボタンをクリックします。";
			next;
			mes "[アルベルタ案内要員]";
			mes "ミニMAPが見えたら";
			mes "「-」ボタンを再度クリックして、";
			mes "街全体が見えるように設定した方が";
			mes "良いでしょう。";
			continue;
		case 4:
			mes "[アルベルタ案内要員]";
			mes "良い旅を。";
			close2;
			cutin "prt_soldier",255;
			end;
		}
	}
}

alberta.gat,120,60,3	duplicate(案内要員#alberta)	案内要員	105


//----------------------------------------------------------------------
//[案内要員 - モロク]

morocc.gat,153,286,6	script	案内要員#morocc	707,{
	cutin "moc_soldier",2;
	mes "[モロク案内要員]";
	mes "……ようこそ、辺境の地モロクへ。";
	mes "私はここモロクに来た旅人のために";
	mes "街の案内をしている者。";
	mes "聞きたい事があれば、どうぞ。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[モロク案内要員]";
			mes "……知りたい場所は？";
			if(@compass&0x040 == 0 && '@flag == 0) {
				mes "ミニMAPに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x040;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("^FF0000シーフギルド^000000","武器屋","旅館","酒場","傭兵ギルド","取り消し")) {
				case 1:
					mes "[モロク案内要員]";
					mes "シーフ転職業務を処理する";
					mes "「シーフギルド」は、ピラミッドの中に";
					mes "ある……";
					if(@compass&0x040)
						viewpoint 1,24,297,1,0xFF0000;
					continue;
				case 2:
					mes "[モロク案内要員]";
					mes "「武器屋」は街の南東にある。";
					if(@compass&0x040)
						viewpoint 1,253,56,2,0xFF00FF;
					continue;
				case 3:
					mes "[モロク案内要員]";
					mes "「旅館」は街の南と北東にある。";
					if(@compass&0x040)
						viewpoint 1,197,66,3,0xFF00FF;
					continue;
				case 4:
					mes "[モロク案内要員]";
					mes "「酒場」は街の北西にある。";
					if(@compass&0x040)
						viewpoint 1,52,259,4,0xFF00FF;
					continue;
				case 5:
					mes "[モロク案内要員]";
					mes "「傭兵ギルド」は街の東側にある。";
					if(@compass&0x040)
						viewpoint 1,284,171,5,0x00FF00;
					continue;
				case 6:
					mes "[モロク案内要員]";
					mes "位置表示を消したい場合は";
					mes "「ミニMAP上の位置表示を消す」";
					mes "を選択すればいい。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,24,297,1,0xFF0000;
			viewpoint 2,253,56,2,0xFF00FF;
			viewpoint 2,197,66,3,0xFF00FF;
			viewpoint 2,52,259,4,0xFF00FF;
			viewpoint 2,284,171,5,0x00FF00;
			set @compass,@compass&~0x040;
			set '@flag,0;
			continue;
		case 3:
			mes "[モロク案内要員]";
			mes "既存のアナログ案内方式を廃止し";
			mes "知りたい場所をミニMAPに表示する";
			mes "広域検索システムを利用した";
			mes "最先端デジタル案内方式に";
			mes "変更された。";
			next;
			mes "[モロク案内要員]";
			mes "ルーンミッドガッツ王国に存在する";
			mes "魔法と科学技術の粋である";
			mes "この広域検索システムの性能を";
			mes "直接その目で確かめてほしい。";
			next;
			mes "[モロク案内要員]";
			mes "まず、画面右上にある";
			mes "ミニMAPを確認してくれ。";
			mes "ミニMAPが見えない場合、";
			mes "「ctrl+tab」または";
			mes "基本ウィンドウで「map」";
			mes "ボタンをクリックすればいい。";
			next;
			mes "[モロク案内要員]";
			mes "ミニMAPが見えたら";
			mes "「-」ボタンを再度クリックし";
			mes "街全体が見えるように設定すれば";
			mes "良いだろう。";
			continue;
		case 4:
			mes "[モロク案内要員]";
			mes "良い、旅を……";
			close2;
			cutin "moc_soldier",255;
			end;
		}
	}
}

morocc.gat,54,97,6	duplicate(案内要員#morocc)	案内要員	707


//----------------------------------------------------------------------
//[案内要員 - アルデバラン]

aldebaran.gat,139,63,4	script	兵士	105,{
	cutin "prt_soldier",2;
	mes "[アルデバラン守備兵]";
	mes "私は、どこにでもいる平凡な";
	mes "守備兵ではありません。";
	mes "名前は「名無し」ですけど……";
	mes "とにかく、お望みとあれば";
	mes "街のご案内をしてさしあげ";
	mes "ますよ。";
	next;
	if(select("案内してもらう","やめる")==1) {
		viewpoint 1,57,222,1,0xFF6633;
		viewpoint 1,73,196,2,0x0000FF;
		viewpoint 1,224,224,3,0x00FFFF;
		viewpoint 1,233,106,4,0x515151;
		viewpoint 1,197,71,5,0x3355FF;
		viewpoint 1,60,60,6,0xFF5555;
		mes "^FF6633+^000000 -> カプラ本社";
		mes "^0000FF+^000000 -> 武器屋";
		mes "^00FFFF+^000000 -> ソーサラーギルド (Closed)";
		mes "^515151+^000000 -> 酒場";
		mes "^3355FF+^000000 -> 道具屋";
		mes "^FF5555+^000000 -> 錬金術師ギルド";
	}
	else {
		mes "[アルデバラン守備兵]";
		mes "アルデバランは";
		mes "私たちが守ります！";
	}
	close2;
	cutin "prt_soldier",255;
	end;
}

aldebaran.gat,241,136,2	script	兵士	105,{
	cutin "prt_soldier",2;
	mes "[アルデバラン守備兵]";
	mes "私は、どこにでもいる平凡な";
	mes "守備兵ではありません。";
	mes "名前は「名無し」ですけど……";
	mes "とにかく、お望みとあれば";
	mes "街のご案内をしてさしあげ";
	mes "ますよ。";
	next;
	switch (select("カプラ本社","武器屋","ソーサラーギルド","酒場","道具屋","錬金術師ギルド","やめる")) {
	case 1:
		viewpoint 1,57,222,1,0xFF6633;
		mes "^FF6633+^000000 -> カプラ本社";
		break;
	case 2:
		viewpoint 1,73,196,2,0x0000FF;
		mes "^0000FF+^000000 -> 武器屋";
		break;
	case 3:
		viewpoint 1,224,224,3,0x00FFFF;
		mes "^00FFFF+^000000 -> ソーサラーギルド (Closed)";
		break;
	case 4:
		viewpoint 1,233,106,4,0x515151;
		mes "^515151+^000000 -> 酒場";
		break;
	case 5:
		viewpoint 1,197,71,5,0x3355FF;
		mes "^3355FF+^000000 -> 道具屋";
		break;
	case 6:
		viewpoint 1,60,60,6,0xFF5555;
		mes "^FF5555+^000000 -> 錬金術師ギルド";
		break;
	case 7:
		mes "[アルデバラン守備兵]";
		mes "アルデバランは";
		mes "私たちが守ります！";
		break;
	}
	close2;
	cutin "prt_soldier",255;
	end;
}

//----------------------------------------------------------------------
//[案内要員 - コモド]
comodo.gat,322,178,4	script	コモドガイド#ココモ	700,{
	mes "[原住民"+strnpcinfo(2)+"]";	//#以降の文字列を参照
	mes "歓楽の夜が24時間続く";
	mes "夢と幻想の村コモドへようこそ！";
	mes "私がご案内してさしあげます。";
	mes "位置情報を知りたかったら";
	mes "いつでも聞いてくださいね。";
	next;
	switch (select("カジノ","フラダンスステージ ^3355FF(ダンサー転職所)^000000","武器店","道具店",
				"特産物品店","カプラサービス西部支部","村長の家","酒場 (PUB)","キャンプ村","会話をやめる")) {
	case 1:
		viewpoint 1,140,98,1,0xFF6633;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^FF6633+^000000 -> カジノ";
		mes "コモドをもっとコモドらしく！";
		mes "旅人たちの疲れを癒す安息所…";
		mes "しかしスリリングな勝負の場。";
		mes "それが「カジノ」！";
		break;
	case 2:
		viewpoint 1,188,168,2,0x0000FF;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^0000FF+^000000 -> フラダンスステージ";
		mes "フラフラ～ フラフラ～";
		mes "舞台に慣れたらダンサーへの転職も";
		mes "考えてみてはいかがでしょう。";
		mes "「フラダンスステージ」";
		mes "^3355FF(ダンサー転職所)^000000";
		break;
	case 3:
		viewpoint 1,266,70,3,0x00FFFF;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^00FFFF+^000000 -> 武器店";
		mes "コモドにはコモドだけの";
		mes "アイテムがあります。";
		mes "「コモド武器店」";
		break;
	case 4:
		viewpoint 1,86,128,4,0x515151;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^515151+^000000 -> 道具店";
		mes "コモドにはコモドだけの";
		mes "アイテムがあります。";
		mes "「コモド道具店」";
		break;
	case 5:
		viewpoint 1,298,124,5,0x3355FF;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^3355FF+^000000 -> 特産物品店";
		mes "コモドにはコモドだけの";
		mes "アイテムがあります";
		mes "「コモド特産物品店」";
		break;
	case 6:
		viewpoint 1,136,202,6,0xFF5555;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^FF5555+^000000 -> カプラサービス西部支部センター";
		mes "ミッドガルド大陸西部を担当する";
		mes "「カプラサービス西部支部センター」";
		mes "がコモドにあります。";
		break;
	case 7:
		viewpoint 1,114,294,7,0xFF5555;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^FF5555+^000000 -> 村長の家";
		mes "コモド村長様がいらっしゃる所です。";
		mes "もしあなたがコモドに深い興味を";
		mes "お持ちでしたら、是非村長様と";
		mes "お会いしてみてはいかがでしょう。";
		break;
	case 8:
		viewpoint 1,166,298,8,0xFF5555;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^FF5555+^000000 -> 酒場 (PUB)";
		mes "世界各地の旅人たちが情報と";
		mes "意見を交換する酒場です。";
		mes "コモドの民俗パブは、";
		mes "格別の雰囲気を醸し出していますよ。";
		break;
	case 9:
		viewpoint 1,210,308,9,0xFF5555;
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "^FF5555+^000000 -> キャンプ村";
		mes "時には家族同士…時には恋人同士…";
		mes "楽しいひとときを創り上げる";
		mes "バーベキューキャンプ村。";
		mes "コモド民俗料理「野生猪バーベキュー」";
		mes "を味わうことができる唯一の場所！";
		break;
	case 10:
		mes "[原住民"+strnpcinfo(2)+"]";
		mes "コモドは洞窟の中に存在していて";
		mes "日差しが入らないので、";
		mes "24時間、1日中暗いんです。";
		mes "コモドの住民たちはこのような特性を";
		mes "利用した観光商品で商売して";
		mes "生活しているんです。";
		break;
	}
	close;
}

comodo.gat,176,350,4	duplicate(コモドガイド#ココモ)	コモドガイド#ノッココ	700
comodo.gat,37,219,4	duplicate(コモドガイド#ココモ)	コモドガイド#パパヤ	700


//----------------------------------------------------------------------
//[案内要員 - ジュノー]

yuno.gat,153,47,4	script	"ジュノーガイド"	700,{
	mes "[ジュノーガイド]";
	mes "過去を知り……";
	mes "現在を見つめ……";
	mes "未来を予知する……";
	mes "ここは賢者たちの都市";
	mes "- ジュノー -";
	mes "ジュノーにようこそ";
	next;
	switch (select("武器防具店","道具店","セージキャッスル (セージ転職所)","書店通り","中央広場",
				"共和国図書館","シュバイチェル魔法アカデミー","モンスター博物館","会話をやめる")) {
	case 1:
		viewpoint 1,120,138,1,0xFF3355;
		mes "[ジュノーガイド]";
		mes "^FF3355+^000000 -> 武器防具店";
		break;
	case 2:
		viewpoint 1,193,142,2,0x3355FF;
		mes "[ジュノーガイド]";
		mes "^3355FF+^000000 -> 道具店";
		break;
	case 3:
		viewpoint 1,90,318,3,0x33FF55;
		mes "[ジュノーガイド]";
		mes "^33FF55+^000000 -> セージキャッスル";
		mes "(セージ転職所)";
		break;
	case 4:
		viewpoint 1,257,102,4,0xFF3355;
		mes "[ジュノーガイド]";
		mes "^FF3355+^000000 -> 書店通り";
		break;
	case 5:
		viewpoint 1,157,170,5,0x3355FF;
		mes "[ジュノーガイド]";
		mes "^3355FF+^000000 -> 中央広場";
		break;
	case 6:
		viewpoint 1,336,204,6,0x33FF55;
		mes "[ジュノーガイド]";
		mes "^33FF55+^000000 -> 共和国図書館";
		break;
	case 7:
		viewpoint 1,323,281,7,0xFF3355;
		mes "[ジュノーガイド]";
		mes "^FF3355+^000000 -> シュバイチェル魔法アカデミー";
		break;
	case 8:
		viewpoint 1,278,288,8,0x3355FF;
		mes "[ジュノーガイド]";
		mes "^3355FF+^000000 -> モンスター博物館";
		break;
	case 9:
		mes "[ジュノーガイド]";
		mes "賢者たちの大都市";
		mes "そして知識の宝庫";
		mes "ジュノーへようこそ！";
		close;
	}
	mes "になります。";
	mes "良い時をお過ごしください。";
	close;
}

//----------------------------------------------------------------------
//[案内要員 - アマツ]

amatsu.gat,207,91,4	script	ミス・アマツ::蛍ちゃん	758,{
	if(strnpcinfo(3) == "蛍ちゃん") {	//識別子を参照
		mes "[蛍ちゃん]";
		mes "私は、第13代ミス・アマツ";
		mes "「蛍」と申します。";
		mes "アマツ代表として";
		mes "村の案内を仰せつかっております。";
		mes "なにかご質問がありましたら";
		mes "なんなりとおっしゃってくださいませ。";
	}
	else {
		mes "[案内人]";
		mes "ようこそ。";
		mes "旅をするには良い季節ですね。";
		mes "私はこのアマツの";
		mes "案内を引き受けておる者です。";
		next;
		mes "[案内人]";
		mes "何をお探しですか？";
	}
	next;
	switch (select("城","道具店","武器店","居酒屋")) {
	case 1:
		viewpoint 1,85,235,0,0xFF3355;
		mes "["+strnpcinfo(3)+"]";
		mes "ミニマップの";
		mes "^FF3355+^000000部分が";
		mes "城でございます。";
		break;
	case 2:
		viewpoint 1,96,118,1,0xCE6300;
		mes "["+strnpcinfo(3)+"]";
		mes "ミニマップの";
		mes "^CE6300+^000000部分が";
		mes "道具店になります。";
		break;
	case 3:
		viewpoint 1,132,117,2,0x55FF33;
		mes "["+strnpcinfo(3)+"]";
		mes "ミニマップの";
		mes "^55FF33+^000000部分が";
		mes "武器店になります。";
		break;
	case 4:
		viewpoint 1,217,116,3,0x3355FF;
		mes "["+strnpcinfo(3)+"]";
		mes "ミニマップの";
		mes "^3355FF+^000000部分が";
		mes "居酒屋になります。";
		break;
	}
	mes "それでは、アマツで";
	mes "楽しい時間をお過ごし下さいませ。";
	close;
}

amatsu.gat,251,283,4	duplicate(蛍ちゃん)	案内人	767


//----------------------------------------------------------------------
//[案内要員 - コンロン]

gonryun.gat,163,60,4	script	コンロンガイド	780,{
	mes "[ハ ウォンチ]";
	mes "いつも活気に満ちて、熱気があふれ";
	mes "毎日人々が行き交っている";
	mes "コンロンにいらっしゃいませ!";
	next;
	mes "[ハ ウォンチ]";
	mes "商売がら、村の案内をして";
	mes "います。知りたいことがあれば";
	mes "何でも聞いてください。";
	next;
	switch (select("村長の家","道具商人","武器商人","防具商人","旅館")) {
	case 1:
		viewpoint 1,109,131,0,0xff3355;
		mes "[ハ ウォンチ]";
		mes "ミニマップの";
		mes "^ff3355+^000000の位置に";
		mes "村長の家があります。";
		break;
	case 2:
		viewpoint 1,147,84,1,0xce6300;
		mes "[ハ ウォンチ]";
		mes "ミニマップの";
		mes "^ce6300+^000000の位置に";
		mes "道具商人がいます。";
		break;
	case 3:
		viewpoint 1,174,101,2,0x55ff33;
		mes "[ハ ウォンチ]";
		mes "ミニマップの";
		mes "^55ff33+^000000の位置に";
		mes "武器商人がいます。";
		break;
	case 4:
		viewpoint 1,173,84,3,0x3355ff;
		mes "[ハ ウォンチ]";
		mes "ミニマップの";
		mes "^3355ff+^000000の位置に";
		mes "防具商人がいます。";
		break;
	case 5:
		viewpoint 1,215,114,4,0xffffff;
		mes "[ハ ウォンチ]";
		mes "ミニマップの";
		mes "^ffffff+^000000の位置に";
		mes "旅館があります。";
		break;
	}
	mes "私達の楽しいコンロンを";
	mes "思いっきり楽しんでください！";
	close;
}

//----------------------------------------------------------------------
//[案内要員 - ウンバラ]

umbala.gat,128,94,4	script	探険家	702,{
	mes "[探険家]";
	mes "ここはとても変な所です。";
	mes "未開拓のためなのか、";
	mes "道もとても複雑です。";
	next;
	mes "[探険家]";
	mes "しかし私は、ここで何ヶ月も探険を";
	mes "続けています。だから村の地理を良く";
	mes "知っていますので、どこに何があるか";
	mes "知りたいなら、遠慮なく聞いて下さい。";
	next;
	switch (select("村の案内を受ける","ミニマップの表示を全て消す","やめる")) {
	case 1:
		mes "[探険家]";
		mes "何を知りたいですか？";
		next;
		switch (select("酋長の家","シャーマンの家","武器屋","道具屋","バンジージャンプ台","取り消し")) {
			case 1:
				mes "[探険家]";
				mes "酋長様のお宅は、^FF3355+^000000の位置にあります。";
				mes "酋長様だけが、外部の言葉を話せます。";
				mes "なので、まず酋長様にお会いすると";
				mes "良いでしょう。";
				viewpoint 0,66,250,2,0xFF3355;
				break;
			case 2:
				mes "[探険家]";
				mes "シャーマンの力は神秘ですね。";
				mes "シャーマンの家は、^CE6300+^000000の位置にあります。";
				mes "彼女は、自然の属性の結合や分解が";
				mes "できるそうです。";
				viewpoint 0,217,186,3,0xCE6300;
				break;
			case 3:
				mes "[探険家]";
				mes "武器屋は、^55FF33+^000000の位置にあります。";
				mes "外部からの侵入が多いので、様々な";
				mes "武器が用意されているみたいです。";
				viewpoint 0,126,154,4,0x55FF33;
				break;
			case 4:
				mes "[探険家]";
				mes "道具屋は、^3355FF+^000000の位置にあります。";
				mes "旅行に必要な物を売っていますから、";
				mes "旅に出る前に立ち寄ってみてください。";
				viewpoint 0,136,127,5,0x3355FF;
				break;
			case 5:
				mes "[探険家]";
				mes "ウンバラには、他の所では見られない";
				mes "「バンジージャンプ台」というものが";
				mes "あります。バンジージャンプ台は、";
				mes "^00FF00+^000000の位置にあります。";
				mes "自分の勇気を試してみたければ、是非";
				mes "挑戦してみてください。";
				viewpoint 0,139,198,6,0x00FF00;
				break;
			case 6:
				mes "[探険家]";
				mes "位置表示を消したければ、";
				mes "「ミニマップの表示を全て消す」";
				mes "を選択してください。";
				break;
		}
		close;
	case 2:
		mes "[探険家]";
		mes "ミニマップの表示を全て消しました。";
		mes "ミニマップにまた表示したければ、";
		mes "いつでも言ってください。";
		viewpoint 2,66,250,2,0x00FF00;
		viewpoint 2,217,186,3,0x00FF00;
		viewpoint 2,126,154,4,0x00FF00;
		viewpoint 2,136,127,5,0x00FF00;
		viewpoint 2,139,198,6,0x00FF00;
		close;
	case 3:
		mes "[探険家]";
		mes "直接、歩き回りながら見るのも";
		mes "面白いですね。それではごきげんよう。";
		close;
	}
}

//----------------------------------------------------------------------
//[案内要員 - ニブルヘイム]

niflheim.gat,186,190,6	script	迷い人	798,{
	mes "[リカエル]";
	mes "こんなに恐ろしい街へ";
	mes "いらっしゃるなんて……";
	mes "あなたも道に迷われたのですね。";
	mes "僕は巨大な樹に導かれて、ここへ";
	mes "来ました。けれども長い間、";
	mes "脱出することができません。";
	next;
	mes "[リカエル]";
	mes "それでもずっと出口を捜していたので、";
	mes "街の地理だけはよく解っています。";
	mes "外へ出るのに役立つかもしれないので、";
	mes "遠慮なくお尋ねください。";
	next;
	switch (select("街の地理を尋ねる","ミニマップの表示を全て消す","話をやめる")) {
	case 1:
		mes "[リカエル]";
		mes "何を知りたいですか？";
		next;
		switch (select("魔女の城","道具屋","武器屋","酒屋","取り消し")) {
			case 1:
				mes "[リカエル]";
				mes "ニブルヘイムには恐ろしい魔女が";
				mes "います。 ^FF3355+^000000 の位置に、その魔女が";
				mes "住むお城があります。私は一度だけ";
				mes "行ったことがありますが、とても";
				mes "恐ろしかったので、すぐに逃げ出して";
				mes "きました。";
				viewpoint 0,253,191,2,0xFF3355;
				break;
			case 2:
				mes "[リカエル]";
				mes "道具屋は ^CE6300+^000000 の位置にあります。";
				mes "外の世界では売られていない";
				mes "珍しい物もありますので、是非一度、";
				mes "行ってみてください。";
				viewpoint 0,217,196,3,0xCE6300;
				break;
			case 3:
				mes "[リカエル]";
				mes "武器屋は ^55FF33+^000000 の位置にあります。";
				mes "他の所では見かけない物もありますので";
				mes "是非一度、行ってみてください。";
				viewpoint 0,216,171,4,0x55FF33;
				break;
			case 4:
				mes "[リカエル]";
				mes "酒屋は ^3355FF+^000000 の位置にあります。";
				mes "ここではたまに、死者達が集まって";
				mes "パーティーをしていますね。";
				viewpoint 0,189,207,5,0x3355FF;
				break;
			case 5:
				mes "[リカエル]";
				mes "位置表示を消したければ";
				mes "「ミニマップの表示を全て消す」";
				mes "を選択してください。";
				break;
		}
		close;
	case 2:
		mes "[リカエル]";
		mes "ミニマップの表示を全て消しました。";
		mes "またミニマップの表示を消したければ、";
		mes "いつでも声をかけてください。";
		viewpoint 2,253,191,2,0x00FF00;
		viewpoint 2,217,196,3,0x00FF00;
		viewpoint 2,216,171,4,0x00FF00;
		viewpoint 2,189,207,5,0x00FF00;
		close;
	case 3:
		mes "[リカエル]";
		mes "直接、歩いて見るのはとても";
		mes "危ないのに……気をつけて";
		mes "行ってらっしゃい。";
		close;
	}
}

//----------------------------------------------------------------------
//[案内要員 - 龍之城]
louyang.gat,224,104,4	script	広報大使#Lou	818,{
	mes "["+strnpcinfo(0)+"]";
	mes "龍之城へようこそ。";
	mes "この度、龍之城は外国との積極的な";
	mes "交流のため、新たに航路を開拓いたし";
	mes "ました。そのおかげで多くの国の方々が";
	mes "安心して訪れることが出来るように";
	mes "なったのです。";
	next;
	mes "["+strnpcinfo(0)+"]";
	mes "龍之城は長い歴史と共に在ります。";
	mes "ですので、見て回れる場所もたくさん";
	mes "御座います。";
	mes "わからない事がありましたら";
	mes "ご案内いたしましょう。";
	next;
	switch (select("村の案内をお願いする","ミニマップの表示を消す","やめる")) {
	case 1:
		mes "["+strnpcinfo(0)+"]";
		mes "どこを案内いたしましょう？";
		next;
		switch (select("城","病院","官庁","武器店","道具店","酒場","やめる")) {
			case 1:
				mes "["+strnpcinfo(0)+"]";
				mes "城は^ff0000+^000000にあります。";
				mes "城には城主様を含め、身分の高い方々が";
				mes "おられます。一度、城主様へご挨拶に";
				mes "伺われるのも、よろしいのではないで";
				mes "しょうか。";
				viewpoint 1,218,255,1,0xff0000;
				break;
			case 2:
				mes "["+strnpcinfo(0)+"]";
				mes "龍之城には有名な病院が";
				mes "^8a0000+^000000にございます。";
				mes "噂によると、彼等に治せない病気はない";
				mes "と言うことですが、それが真実なのか";
				mes "どうかはわかりません。";
				viewpoint 1,263,93,2,0x8a0000;
				break;
			case 3:
				mes "["+strnpcinfo(0)+"]";
				mes "龍之城には官庁がございます。";
				mes "^777777+^000000が官庁の場所となります。";
				mes "何か問題が発生した場合は";
				mes "官庁をお尋ね下さい。";
				viewpoint 1,309,80,3,0x00ff00;
				break;
			case 4:
				mes "["+strnpcinfo(0)+"]";
				mes "武器店は ^00ff00+^000000にあります。";
				mes "腕自慢の職人による立派な武器が";
				mes "並んでおります。";
				viewpoint 1,145,174,4,0x00ff00;
				break;
			case 5:
				mes "["+strnpcinfo(0)+"]";
				mes "道具店は ^0000ff+^000000にあります。";
				mes "準備を怠らなければ百戦百勝！";
				viewpoint 1,136,97,5,0x0000ff;
				break;
			case 6:
				mes "["+strnpcinfo(0)+"]";
				mes "疲れた時は酒場に立ち寄ってみては";
				mes "いかがでしょう。";
				mes "酒場は ^00ff00+^000000にあります。";
				mes "他にも大勢の旅行客がいらして";
				mes "らっしゃるようですよ。";
				viewpoint 1,280,167,6,0x00ff00;
				break;
			case 7:
				mes "["+strnpcinfo(0)+"]";
				mes "位置表示を消したければ";
				mes "『ミニマップの表示を消す』を";
				mes "選択してください。";
				break;
		}
		close;
	case 2:
		mes "["+strnpcinfo(0)+"]";
		mes "ミニマップの表示を全て消しました。";
		mes "また何か表示したければ";
		mes "いつでもご案内いたします。";
		viewpoint 2,218,255,1,0xff0000;
		viewpoint 2,263,93,2,0x8a0000;
		viewpoint 2,309,80,3,0x00ff00;
		viewpoint 2,145,174,4,0x00ff00;
		viewpoint 2,136,97,5,0x0000ff;
		viewpoint 2,280,167,6,0x00ff00;
		close;
	case 3:
		mes "["+strnpcinfo(0)+"]";
		mes "ご自分で歩き回るのも良いですね。";
		mes "では、御機嫌よう。";
		close;
	}
}

louyang.gat,160,175,4	duplicate(広報大使#Lou)	兵士	825
louyang.gat,213,213,4	duplicate(広報大使#Lou)	兵士	825


//----------------------------------------------------------------------
//[案内要員 - アユタヤ]

ayothaya.gat,203,169,4	script	ノイ	839,{
	mes "[ノイ]";
	mes "こんにちは。";
	mes "アユタヤへようこそ。";
	mes "ここアユタヤは、深き森に囲まれ";
	mes "川が流れる自然に恵まれた";
	mes "静かな村です。";
	next;
	mes "[ノイ]";
	mes "また海にも近いので、水産物市場も";
	mes "あります。他国ではお目にかかれない";
	mes "独特な建築物もたくさんあります。";
	mes "それではごゆっくりどうぞ。";
	next;
	switch (select("村の案内をしてもらう","ミニマップの表示を全て消す","会話をやめる")) {
	case 1:
		mes "[ノイ]";
		mes "どちらをご案内しましょうか？";
		next;
		switch (select("武器屋","道具屋","酒場","神殿","釣り場","取り消し")) {
			case 1:
				mes "[ノイ]";
				mes "武器屋は^55FF33+^000000の位置にあります。";
				mes "アユタヤの海の男たちは";
				mes "こちらで武具を揃えています。";
				viewpoint 1,182,59,2,0x00FF00;
				break;
			case 2:
				mes "[ノイ]";
				mes "道具屋は^3355FF+^000000の位置にあります。";
				mes "私共アユタヤの住民はどこかへ";
				mes "出かける際、必ず入念な準備をします。";
				mes "事前準備をしっかりすることは";
				mes "とても大事ですよね？";
				viewpoint 1,129,86,2,0x55FF33;
				break;
			case 3:
				mes "[ノイ]";
				mes "一度酒場に行ってみるとよいでしょう。";
				mes "酒場は^55FF33+^000000の位置にあります。";
				mes "冒険の基本は情報収集です。";
				mes "酒場は多くの旅行客が訪れる場所";
				mes "ですから、有用な情報を得ることが";
				mes "できるでしょう。";
				viewpoint 1,229,69,2,0x00FF00;
				break;
			case 4:
				mes "[ノイ]";
				mes "神様にお祈りをなさりたいのなら";
				mes "^55FF33+^000000の位置にある神殿に";
				mes "行ってみてください。";
				viewpoint 1,208,283,2,0x00FF00;
				break;
			case 5:
				mes "[ノイ]";
				mes "ここアユタヤは海岸が近いので";
				mes "海釣りを楽しむ人が多いです。";
				mes "^55FF33+^000000の位置にある釣り場は";
				mes "特に有名です。一度行ってみると";
				mes "よいでしょう。";
				viewpoint 1,253,99,2,0x00FF00;
				break;
			case 6:
				mes "[ノイ]";
				mes "位置表示を消したければ";
				mes "「ミニマップの表示を全て消す」";
				mes "を選択してください。";
				break;
		}
		close;
	case 2:
		mes "[ノイ]";
		mes "ミニマップの表示を全て消しました。";
		mes "再度表示したい場合は、いつでも";
		mes "お問い合わせください。";
		viewpoint 2,182,59,2,0x00FF00;
		viewpoint 2,129,86,2,0x55FF33;
		viewpoint 2,229,69,2,0x00FF00;
		viewpoint 2,208,283,2,0x00FF00;
		viewpoint 2,253,99,2,0x00FF00;
		close;
	case 3:
		mes "[ノイ]";
		mes "よいご旅行になりますように。";
		close;
	}
}

//----------------------------------------------------------------------
//[案内要員 - アインブロック]

einbroch.gat,72,202,4	script	案内要員#einbroch	852,{
	cutin "ein_soldier",2;
	mes "[アインブロック案内要員]";
	mes "鋼鉄の都市アインブロックへようこそ。";
	mes "私共は、アインブロックにいらした方に";
	mes "街の案内を行っています。";
	mes "私共の案内を初めて受ける方は、";
	mes "「告知事項を聞く」を選んでください。";
	next;
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[アインブロック案内要員]";
			mes "どこを案内しましょう？";
			if(@compass&0x080 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x080;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			next;
			while(1) {
				switch (select("^FF0000空港^000000","駅","工場","広場","ホテル","武器屋",
							"研究所","ブラックスミスギルド","記念タワー","取り消し")) {
				case 1:
					mes "[アインブロック案内要員]";
					mes "^FF0000空港^000000は、北西にあります。";
					mes "空港では、シュバルツバルドの";
					mes "誇りである飛行船を";
					mes "利用することができます。";
					mes "飛行船を利用する際は、";
					mes "切符が必要です。ご注意ください。";
					if(@compass&0x080)
						viewpoint 1,64,207,1,0xFF0000;
					continue;
				case 2:
					mes "[アインブロック案内要員]";
					mes "駅は街の北東にあります。";
					mes "アインベフ直通の汽車が";
					mes "運行しています。";
					if(@compass&0x080)
						viewpoint 1,232,272,2,0xFF00FF;
					continue;
				case 3:
					mes "[アインブロック案内要員]";
					mes "工場は街の重要施設で、";
					mes "アインブロックの中心とも言えます。";
					mes "街の南に位置し、その建物の中に";
					mes "研究所もあります。";
					if(@compass&0x080)
						viewpoint 1,140,79,3,0xFF00FF;
					continue;
				case 4:
					mes "[アインブロック案内要員]";
					mes "広場は、アインブロックの";
					mes "中央東にあり、商店街になっています。";
					mes "ホテルもありますので、";
					mes "行ってみるといいでしょう。";
					if(@compass&0x080)
						viewpoint 1,230,190,4,0xFF00FF;
					continue;
				case 5:
					mes "[アインブロック案内要員]";
					mes "ホテルは、広場の東にあります。";
					mes "最高級の設備で整えられていますので、";
					mes "快適に過ごせると思います。";
					if(@compass&0x080)
						viewpoint 1,257,199,5,0x00FF00;
					continue;
				case 6:
					mes "[アインブロック案内要員]";
					mes "武器屋は、広場より";
					mes "少し北側にあります。";
					if(@compass&0x080)
						viewpoint 1,216,214,6,0x00FF00;
					continue;
				case 7:
					mes "[アインブロック案内要員]";
					mes "研究所は工場の付属施設です。";
					mes "アインブロックの南西にあります。";
					if(@compass&0x080)
						viewpoint 1,51,52,7,0x00FF00;
					continue;
				case 8:
					mes "[アインブロック案内要員]";
					mes "ブラックスミスギルドは、";
					mes "アインブロックの南東にあります。";
					mes "精錬所も兼ねています。";
					if(@compass&0x080)
						viewpoint 1,255,107,8,0x00FF00;
					continue;
				case 9:
					mes "[アインブロック案内要員]";
					mes "記念タワーは、アインブロックの";
					mes "中心にあります。";
					mes "記念タワーから、アインブロックの";
					mes "全景を見下ろすことができます。";
					if(@compass&0x080)
						viewpoint 1,175,196,9,0x00FFFF;
					continue;
				case 10:
					mes "[アインブロック案内要員]";
					mes "位置表示を消したければ";
					mes "「ミニマップの表示を消す」を";
					mes "選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			mes "[アインブロック案内要員]";
			mes "ミニマップの表示を消しました。";
			mes "またのご利用をお待ちしております。";
			viewpoint 2,64,207,1,0xFF0000;
			viewpoint 2,232,272,2,0xFF00FF;
			viewpoint 2,140,79,3,0xFF00FF;
			viewpoint 2,230,190,4,0xFF00FF;
			viewpoint 2,257,199,5,0x00FF00;
			viewpoint 2,216,214,6,0x00FF00;
			viewpoint 2,51,52,7,0x00FF00;
			viewpoint 2,255,107,8,0x00FF00;
			viewpoint 2,175,196,9,0x00FFFF;
			set @compass,@compass&~0x080;
			set '@flag,0;
			continue;
		case 3:
			mes "[アインブロック案内要員]";
			mes "既存のアナログ案内方式から、";
			mes "知りたい場所をミニマップに表示する、";
			mes "広域検索システムを利用した";
			mes "最先端のデジタル案内方式に";
			mes "変わりました。";
			next;
			mes "[アインブロック案内要員]";
			mes "シュバルツバルド共和国で";
			mes "新たに開発された、魔法を完全排除した";
			mes "技術で作り出したこのシステムの";
			mes "性能を直接ご確認ください。";
			next;
			mes "[アインブロック案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニマップを確認してください。";
			next;
			mes "[アインブロック案内要員]";
			mes "もしミニマップが見えなければ、";
			mes "ショートカットキー";
			mes "「ctrl」+「tab」";
			mes "または基本ウィンドウの";
			mes "「map」ボタンをクリックしてください。";
			next;
			mes "[アインブロック案内要員]";
			mes "ミニマップ上の「-」ボタンを";
			mes "数回クリックすると、";
			mes "街の全景が見えるようになります。";
			continue;
		case 4:
			mes "[アインブロック案内要員]";
			mes "こちらでは、度々";
			mes "「大気汚染警報」が発令されますので";
			mes "お気をつけください。";
			close2;
			cutin "ein_soldier",255;
			end;
		}
	}
}

//大気汚染イベントでハイドされる
einbroch.gat,155,43,4	duplicate(案内要員#einbroch)	案内要員#einbrochdummy1	852
einbroch.gat,162,317,4	duplicate(案内要員#einbroch)	案内要員#einbrochdummy2	852

//----------------------------------------------------------------------
//[案内要員 - アインベフ]

einbech.gat,67,37,4	script	案内要員#einbech	852,{
	cutin "ein_soldier",2;
	mes "[アインベフ案内要員]";
	mes "採鉱の村アインベフへようこそ。";
	mes "私達は、アインベフにいらした方に";
	mes "村の案内をしています。";
	mes "案内を初めて受ける方は";
	mes "「告知事項を聞く」を選んでください。";
	next;
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[アインベフ案内要員]";
			mes "どこを案内しましょう？";
			if(@compass&0x0100 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x0100;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("駅","酒場","道具屋","ソードマンギルド","鉱山","取り消し")) {
				case 1:
					mes "[アインベフ案内要員]";
					mes "駅は、アインベフの";
					mes "北西と北東にあります。";
					mes "駅から、アインブロック直通の";
					mes "汽車が出ています。";
					if(@compass&0x0100)
						viewpoint 1,43,214,1,0xFF0000;
					continue;
				case 2:
					mes "[アインベフ案内要員]";
					mes "酒場は、アインベフの南側にあります。";
					mes "食事もできますし、";
					mes "仕事後の休息にもぴったりです。";
					if(@compass&0x0100)
						viewpoint 1,145,112,2,0xFF00FF;
					continue;
				case 3:
					mes "[アインベフ案内要員]";
					mes "道具屋は、アインベフの";
					mes "中心にあります。";
					if(@compass&0x0100)
						viewpoint 1,177,136,3,0xFF00FF;
					continue;
				case 4:
					mes "[アインベフ案内要員]";
					mes "ソードマンギルドは、";
					mes "アインベフの東にあります。";
					mes "現在、内部の工事中ですので、";
					mes "転職の申し込みは受け付けていません。";
					if(@compass&0x0100)
						viewpoint 1,257,109,4,0xFF00FF;
					continue;
				case 5:
					mes "[アインベフ案内要員]";
					mes "鉱山はアインベフの北にあり、現在も";
					mes "活発に発掘作業が行われています。";
					mes "これがアインベフの重要資源です。";
					mes "ただ、鉱物が産出される場所で";
					mes "時々、モンスターが出没し、";
					mes "作業が妨害されることがあります。";
					if(@compass&0x0100)
						viewpoint 1,138,252,5,0x00FF00;
					continue;
				case 6:
					mes "[アインベフ案内要員]";
					mes "位置表示を消したければ";
					mes "「ミニマップの表示を消す」を";
					mes "選択してください。";
				}
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			mes "[アインベフ案内要員]";
			mes "ミニマップの表示を消しました。";
			mes "またのご利用をお待ちしております。";
			viewpoint 2,43,214,1,0xFF0000;
			viewpoint 2,145,112,2,0xFF00FF;
			viewpoint 2,177,136,3,0xFF00FF;
			viewpoint 2,257,109,4,0xFF00FF;
			viewpoint 2,138,252,5,0x00FF00;
			set @compass,@compass&~0x0100;
			set '@flag,0;
			continue;
		case 3:
			mes "[アインベフ案内要員]";
			mes "既存のアナログ案内方式から、";
			mes "知りたい場所をミニマップに表示する、";
			mes "広域検索システムを利用した";
			mes "最先端のデジタル案内方式に";
			mes "変わりました。";
			next;
			mes "[アインベフ案内要員]";
			mes "シュバルツバルド共和国で";
			mes "新たに開発された、魔法を完全排除した";
			mes "技術で作り出したこのシステムの";
			mes "性能を直接ご確認ください。";
			next;
			mes "[アインベフ案内要員]";
			mes "案内の前に、画面右上にある";
			mes "ミニマップを確認してください。";
			next;
			mes "[アインベフ案内要員]";
			mes "もしミニマップが見えなければ、";
			mes "ショートカットキー";
			mes "「ctrl」+「tab」";
			mes "または基本ウィンドウの";
			mes "「map」ボタンをクリックしてください。";
			next;
			mes "[アインベフ案内要員]";
			mes "ミニマップ上の「-」ボタンを";
			mes "数回クリックすると、";
			mes "街の全景が見えるようになります。";
			continue;
		case 4:
			mes "[アインベフ案内要員]";
			mes "よい旅を。";
			close2;
			cutin "ein_soldier",255;
			end;
		}
	}
}

einbech.gat,48,214,4	duplicate(案内要員#einbech)	案内要員#einbechdummy	852

//----------------------------------------------------------------------
//[案内要員 - リヒタルゼン]

lighthalzen.gat,207,310,5	script	案内要員#West_Lhz1	852,{
	cutin "ein_soldier",2;
	mes "[リヒタルゼン案内要員]";
	mes "企業都市リヒタルゼンへようこそ！";
	mes "私はここリヒタルゼンに訪れた";
	mes "旅人の皆さまに、街の案内をして";
	mes "おります。";
	mes "街のことを色々と知りたかったら";
	mes "いつでもお聞きください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			set '@code$,substr(strnpcinfo(2),0,4);	//West or East
			mes "[リヒタルゼン案内要員]";
			if('@code$ == "West") {
				mes "私はリヒタルゼンの^FF0000西区域^000000の案内を";
				mes "担当しております。";
			}
			else if('@code$ == "East") {
				mes "私はリヒタルゼンの^FF0000東区域-貧民街^000000の";
				mes "案内を担当しております。";
			}
			if(@compass&0x0200 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x0200;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				if('@code$ == "West") {
					switch (select("^FF0000レッケンベル^000000","駅","警察署","銀行","ホテル","空港","商人組合","宝石店","武器屋","デパート","取り消し")) {
					case 1:
						mes "[リヒタルゼン案内要員]";
						mes "シュバルツバルド国内最大の企業";
						mes "「レッケンベル」は、街の西部に";
						mes "あります。";
						if(@compass&0x0200)
							viewpoint 1,101,248,1,0xFF0000;
						continue;
					case 2:
						mes "[リヒタルゼン案内要員]";
						mes "「駅」は、街の中央にあります。";
						mes "アインブロック行きの汽車が";
						mes "運行しています。";
						if(@compass&0x0200)
							viewpoint 1,228,163,2,0xFF00FF;
						continue;
					case 3:
						mes "[リヒタルゼン案内要員]";
						mes "街の中央から少し北側に、";
						mes "「警察署」があります。";
						mes "不審な者を見かけた時や、";
						mes "何か困ったことがあれば、";
						mes "相談してください。";
						if(@compass&0x0200)
							viewpoint 1,236,276,3,0x99FFFF;
						continue;
					case 4:
						mes "[リヒタルゼン案内要員]";
						mes "街の中央から少し北側に、";
						mes "「銀行」があります。";
						mes "各種金融関係を取り扱っています。";
						if(@compass&0x0200)
							viewpoint 1,198,257,4,0x0000FF;
						continue;
					case 5:
						mes "[リヒタルゼン案内要員]";
						mes "街の南側にある広場の中央に、";
						mes "「ホテル」があります。";
						mes "最高級の設備とサービスを提供しており";
						mes "著名人も頻繁に利用しています。";
						if(@compass&0x0200)
							viewpoint 1,159,33,5,0x00FF00;
						continue;
					case 6:
						mes "[リヒタルゼン案内要員]";
						mes "「空港」は、中央通りの突き当たり";
						mes "東側にあります。";
						mes "飛行船を利用して、快適な旅を";
						mes "楽しむことができます。";
						if(@compass&0x0200)
							viewpoint 1,267,75,6,0x00FF00;
						continue;
					case 7:
						mes "[リヒタルゼン案内要員]";
						mes "「商人組合」は、街の南西にあります。";
						if(@compass&0x0200)
							viewpoint 1,73,52,7,0xFF99FF;
						continue;
					case 8:
						mes "[リヒタルゼン案内要員]";
						mes "「宝石店」は、南側にある広場の";
						mes "西側にあります。";
						if(@compass&0x0200)
							viewpoint 1,93,110,8,0xFF9900;
						continue;
					case 9:
						mes "[リヒタルゼン案内要員]";
						mes "「武器屋」は、中央通りの";
						mes "突き当たりにあります。";
						mes "販売している武器の種類が豊富で、";
						mes "リヒタルゼンで最も規模が大きい";
						mes "武器屋です。";
						if(@compass&0x0200)
							viewpoint 1,196,46,9,0x330033;
						continue;
					case 10:
						mes "[リヒタルゼン案内要員]";
						mes "街の中央に、「デパート」があります。";
						mes "各種商店が密集しており、";
						mes "ショッピングにとても便利です。";
						if(@compass&0x0200)
							viewpoint 1,198,163,10,0xFF00;
						continue;
					case 11:
						break;
					}
				}
				if('@code$ == "East") {
					switch (select("道具屋","精錬所","酒場","取り消し")) {
					case 1:
						mes "[リヒタルゼン案内要員]";
						mes "「道具屋」は、貧民街の";
						mes "北側にあります。";
						mes "時計方向では11時の方向です。";
						if(@compass&0x0200)
							viewpoint 1,324,301,11,0xFF0000;
						continue;
					case 2:
						mes "[リヒタルゼン案内要員]";
						mes "「精錬所」は、貧民街の";
						mes "北側にあります。";
						mes "時計方向では1時の方向です。";
						if(@compass&0x0200)
							viewpoint 1,365,300,12,0xFF00FF;
						continue;
					case 3:
						mes "[リヒタルゼン案内要員]";
						mes "「酒場」は、貧民街の南側にあります。";
						if(@compass&0x0200)
							viewpoint 1,339,240,13,0x99FFFF;
						continue;
					case 4:
						break;
					}
				}
				mes "[リヒタルゼン案内要員]";
				mes "位置表示を消したい時は";
				mes "「ミニMAPの位置表示を消す」を";
				mes "選んでください。";
				break;	//2番目のwhileを抜ける
			}
			continue;	//1番目のwhileに戻る
		case 2:
			viewpoint 2,101,248,1,0xFF0000;
			viewpoint 2,228,163,2,0xFF00FF;
			viewpoint 2,236,276,3,0x99FFFF;
			viewpoint 2,198,257,4,0x0000FF;
			viewpoint 2,159,33,5,0x00FF00;
			viewpoint 2,267,75,6,0x00FF00;
			viewpoint 2,73,52,7,0xFF99FF;
			viewpoint 2,93,110,8,0xFF9900;
			viewpoint 2,196,46,9,0x330033;
			viewpoint 2,198,163,10,0xFF00;
			viewpoint 2,324,301,11,0xFF0000;
			viewpoint 2,365,300,12,0xFF00FF;
			viewpoint 2,339,240,13,0x99FFFF;
			set @compass,@compass&~0x0200;
			set '@flag,0;
			continue;
		case 3:
			mes "[リヒタルゼン案内要員]";
			mes "本案内をご利用いただく前に";
			mes "まずモニター右上にある";
			mes "ミニMAPをご覧下さい。";
			next;
			mes "[リヒタルゼン案内要員]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウィンドウの";
			mes "「map」ボタンをクリックして下さい。";
			next;
			mes "[リヒタルゼン案内要員]";
			mes "ミニMAPが表示されたら";
			mes " ^4A4AFF-^000000ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定して下さい。";
			continue;
		case 4:
			mes "[リヒタルゼン案内要員]";
			mes "リヒタルゼンは、街の中央に走る";
			mes "汽車線路を境として、";
			mes "二つの区域に分かれています。";
			mes "警備兵が常時巡察をしておりますが、";
			mes "何か困ったことがあれば";
			mes "いつでも私どもに相談してください。";
			next;
			mes "[リヒタルゼン案内要員]";
			mes "それではよい旅を！";
			close2;
			cutin "ein_soldier",255;
			end;
		}
	}
}

lighthalzen.gat,154,100,5	duplicate(案内要員#West_Lhz1)	案内要員#West_Lhz2	852
lighthalzen.gat,220,311,3	duplicate(案内要員#West_Lhz1)	案内要員#East_Lhz1	852
lighthalzen.gat,307,224,3	duplicate(案内要員#West_Lhz1)	案内要員#East_Lhz2	852

//----------------------------------------------------------------------
//[案内要員 - フィゲル]

hugel.gat,98,56,3	script	案内要員	863,{
	mes "[フィゲル案内要員]";
	mes "おや、若い人ね。こんにちわ。";
	mes "ここはシュバルツバルドの";
	mes "フィゲルという村よ。";
	mes "何か聞きたい事があるのかい？";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[フィゲル案内要員]";
			mes "フィゲルなら私がよーく知ってるよ。";
			if(@compass&0x0400 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残すかい？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x0400;
			}
			set '@flag,1;	//どちらを選んでもフラグオン。ミニMAP上の位置表示を消すを選ぶまで消えません。
			while(1) {
				next;
				switch (select("教会","旅館","酒店","飛行船","武器屋","道具屋","パーティ用品店",
						"^3131FFハンター転職所^000000","^3131FF神殿発掘団^000000","モンスターレース会場","ビンゴゲーム会場","取り消し")) {
				case 1:
					mes "[フィゲル案内要員]";
					mes "「教会」と言うよりは、";
					mes "豪華な老人ホームみたいな";
					mes "ものだけどねぇ。";
					if(@compass&0x0400)
						viewpoint 1,155,114,1,0xFF0000;
					continue;
				case 2:
					mes "[フィゲル案内要員]";
					mes "フィゲルの観光も良いけど、";
					mes "まずは泊まる所がないとねぇ。";
					mes "「旅館」はすぐ右手にあるよ。";
					if(@compass&0x0400)
						viewpoint 1,104,79,2,0xFF00FF;
					continue;
				case 3:
					mes "[フィゲル案内要員]";
					mes "やっぱり酒店で話に花を咲かせるのが";
					mes "旅の醍醐味よねぇ。";
					mes "「酒店」はすぐ右の方に行けばあるよ。";
					if(@compass&0x0400)
						viewpoint 1,129,66,3,0x99FFFF;
					continue;
				case 4:
					mes "[フィゲル案内要員]";
					mes "最近、初めて見る人が増えてきたわ。";
					mes "やっぱりあの大きなのが";
					mes "村に来るようになったからかねぇ。";
					mes "「飛行船」……だったっけ？";
					if(@compass&0x0400)
						viewpoint 1,178,142,4,0x0000FF;
					continue;
				case 5:
					mes "[フィゲル案内要員]";
					mes "「武器屋」は村中央にあるけど……";
					mes "こんな田舎じゃ何も無いよ。";
					if(@compass&0x0400)
						viewpoint 1,70,157,5,0x00FF00;
					continue;
				case 6:
					mes "[フィゲル案内要員]";
					mes "こんなおいぼれになったら";
					mes "もう赤ポーションすら";
					mes "どんな味かわからなくてねぇ……";
					mes "「道具屋」は村中央にあるよ。";
					if(@compass&0x0400)
						viewpoint 1,92,167,6,0x00FF00;
					continue;
				case 7:
					mes "[フィゲル案内要員]";
					mes "「パーティ用品店」は村の中央から";
					mes "少し離れた所にあるよ。";
					mes "パーティ用品でいたずらをすると";
					mes "大変な事になるから";
					mes "気をつけるんだよ。";
					if(@compass&0x0400)
						viewpoint 1,91,104,7,0xFF99FF;
					continue;
				case 8:
					mes "[フィゲル案内要員]";
					mes "「ハンター」に転職したいなら";
					mes "村の北東の方、";
					mes "海岸に沿って行けばいいよ。";
					if(@compass&0x0400)
						viewpoint 1,206,228,8,0xFF9900;
					continue;
				case 9:
					mes "[フィゲル案内要員]";
					mes "「神殿発掘団」っていうのが";
					mes "村の西の方にいるよ。";
					mes "人を募集しているようだけど、";
					mes "一体何をしているのやら。";
					if(@compass&0x0400)
						viewpoint 1,52,90,9,0xFFFFFF;
					continue;
				case 10:
					mes "[フィゲル案内要員]";
					mes "私もたまに「モンスターレース」で";
					mes "遊んでいるよ。";
					mes "一度楽しんでみたらどうだい？";
					if(@compass&0x0400)
						viewpoint 1,58,72,10,0xFF9900;
					continue;
				case 11:
					mes "[フィゲル案内要員]";
					mes "ビンゴゲームは好きかい？";
					mes "それなら、ユクランが司会をしている";
					mes "「ビンゴゲーム会場」に";
					mes "いってみるといいよ。";
					if(@compass&0x0400)
						viewpoint 1,55,208,11,0x66FFFF;
					continue;
				case 12:
					mes "[フィゲル案内要員]";
					mes "位置標識を消したい時は";
					mes "「ミニMAP上の位置表示を消す」を";
					mes "選ぶといいよ。";
				}
				break;
			}
			continue;
		case 2:
			viewpoint 2,155,114,1,0xFF0000;
			viewpoint 2,104,79,2,0xFF00FF;
			viewpoint 2,129,66,3,0x99FFFF;
			viewpoint 2,178,142,4,0x0000FF;
			viewpoint 2,70,157,5,0x00FF00;
			viewpoint 2,92,167,6,0x00FF00;
			viewpoint 2,91,104,7,0xFF99FF;
			viewpoint 2,206,228,8,0xFF9900;
			viewpoint 2,52,90,9,0xFFFFFF;
			viewpoint 2,52,90,10,0xFF9900;
			viewpoint 2,58,72,11,0x66FFFF;
			set @compass,@compass&~0x0400;
			set '@flag,0;
			mes "[フィゲル案内要員]";
			mes "位置標識を全部消したよ。";
			mes "知りたい事があるなら";
			mes "何でもいってごらん。";
			continue;
		case 3:
			mes "[フィゲル案内要員]";
			mes "村の案内を受ける前に";
			mes "まずモニター右上にある";
			mes "ミニMAPを見てごらん。";
			next;
			mes "[フィゲル案内要員]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウインドウの";
			mes "「map」ボタンをクリックするんだよ。";
			next;
			mes "[フィゲル案内要員]";
			mes "ミニMAPが表示されたら";
			mes " ^3152FF-^000000 ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定するといいよ。";
			continue;
		case 4:
			mes "[フィゲル案内要員]";
			mes "村の案内をするのも";
			mes "なかなか楽しいもんさ。";
			mes "ホッホッホッホッホ。";
			close;
		}
	}
}

//----------------------------------------------------------------------
//[案内要員 - ラヘル]

rachel.gat,138,146,5	script	ラヘル案内要員	934,{
	mes "[ラヘル案内要員]";
	mes "女神フレイヤ様の愛に包まれた";
	mes "アルナベルツの首都、ラヘルに";
	mes "ようこそいらっしゃいました。";
	next;
	mes "[ラヘル案内要員]";
	mes "初めて案内をお受けになられるなら、";
	mes "「告知事項」メニューを";
	mes "選択して見てください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[ラヘル案内要員]";
			mes "どこの場所を調べられますか？";
			if(@compass&0x0800 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x0800;
			}
			set '@flag,1;
			while(1) {
				next;
				switch (select("セスルムニル神殿","ホテル","武器屋","道具屋","飛行船","取り消し")) {
				case 1:
					mes "[ラヘル案内要員]";
					mes "セスルムニル神殿は";
					mes "女神フレイヤ様の化身である";
					mes "教皇様がいらっしゃる";
					mes "神聖な場所でございます。";
					next;
					mes "[ラヘル案内要員]";
					mes "道にそって北へ向かうと";
					mes "すぐに辿り着くでしょう。";
					if(@compass&0x0800)
						viewpoint 1,150,249,1,0xFF0000;
					continue;
				case 2:
					mes "[ラヘル案内要員]";
					mes "旅の疲れを癒すには、ホテルが";
					mes "一番でしょう。";
					mes "すぐ左にある建物がホテルです。";
					if(@compass&0x0800)
						viewpoint 1,115,149,2,0xFF00FF;
					continue;
				case 3:
					mes "[ラヘル案内要員]";
					mes "ラヘルで販売している";
					mes "丈夫な武器を御所望ですか？";
					mes "武器屋は西門のすぐ近くです。";
					if(@compass&0x0800)
						viewpoint 1,42,87,3,0x99FFFF;
					continue;
				case 4:
					mes "[ラヘル案内要員]";
					mes "上質の最高級ポーションだけを扱う、";
					mes "ラヘルの道具屋は";
					mes "西門の近くにあります。";
					if(@compass&0x0800)
						viewpoint 1,83,78,4,0x0000FF;
					continue;
				case 5:
					mes "[ラヘル案内要員]";
					mes "飛行船は、ラヘルの東門を出て";
					mes "東に行った所にあります。";
					if(@compass&0x0800)
						viewpoint 1,273,125,5,0x00FF00;
					continue;
				case 6:
					mes "[ラヘル案内要員]";
					mes "位置標識を消したい時は";
					mes "「ミニMAP上の位置表示を消す」を";
					mes "選択してください。";
				}
				break;
			}
			continue;
		case 2:
			viewpoint 2,150,249,1,0xFF0000;
			viewpoint 2,115,149,2,0xFF00FF;
			viewpoint 2,42,87,3,0x99FFFF;
			viewpoint 2,83,78,4,0x0000FF;
			viewpoint 2,273,125,5,0x00FF00;
			set @compass,@compass&~0x0800;
			set '@flag,0;
			mes "[ラヘル案内要員]";
			mes "ミニMAP上の位置表示を";
			mes "全部消しました。";
			mes "また、気になる事がありましたら";
			mes "いつでも、聞いてください。";
			continue;
		case 3:
			mes "[ラヘル案内要員]";
			mes "村の案内は、モニター右上にある";
			mes "ミニMAPを参考してください。";
			next;
			mes "[ラヘル案内要員]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウインドウの";
			mes "「map」ボタンを";
			mes "クリックしてください。";
			next;
			mes "[フィゲル案内要員]";
			mes "ミニMAPが表示されたら";
			mes " ^3152FF-^000000 ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定してください。";
			continue;
		case 4:
			mes "[ラヘル案内要員]";
			mes "では、良い旅を。";
			close;
		}
	}
}

//----------------------------------------------------------------------
//[案内要員 - ベインス]

veins.gat,210,345,5	script	ベインス案内兵士#ve	934,{
	mes "[ベインス案内兵士]";
	mes "砂嵐を通り抜けて来た皆様、";
	mes "ようこそ！";
	mes "ここは";
	mes "峡谷都市「ベインス」です。";
	next;
	mes "[ベインス案内兵士]";
	mes "初めて案内をお受けになられるなら、";
	mes "「告知事項」メニューを";
	mes "選択して見てください。";
	while(1) {
		next;
		switch (select("街の案内を受ける","ミニMAP上の位置表示を消す","告知事項","やめる")) {
		case 1:
			mes "[ベインス案内兵士]";
			mes "どの場所を調べられますか？";
			if(@compass&0x0800 == 0 && '@flag == 0) {
				mes "ミニマップに位置表示を残しますか？";
				next;
				if(select("はい","いいえ")==1)
					set @compass,@compass|0x1000;
			}
			set '@flag,1;
			while(1) {
				next;
				switch (select("セスルムニル神殿","ホテル","武器屋","道具屋","飛行船","酒場","地質学研究所","治安管理所","取り消し")) {
				case 1:
					mes "[ベインス案内兵士]";
					mes "神にお祈りをする参拝客で";
					mes "賑わうセスルムニル神殿は、";
					mes "ベインスの北側にあります。";
					if(@compass&0x1000)
						viewpoint 1,195,275,1,0xFF0000;
					continue;
				case 2:
					mes "[ベインス案内兵士]";
					mes "旅の疲れを癒してくれる";
					mes "ホテルは、";
					mes "ベインスの北西にあります。";
					if(@compass&0x1000)
						viewpoint 1,130,280,2,0xFF00FF;
					continue;
				case 3:
					mes "[ベインス案内兵士]";
					mes "自分の身を守るには";
					mes "武器が重要です。";
					mes "良質で安い武器を扱う";
					mes "武器屋は、";
					mes "ベインスの西にあります。";
					if(@compass&0x1000)
						viewpoint 1,148,185,3,0x99FFFF;
					continue;
				case 4:
					mes "[ベインス案内兵士]";
					mes "旅には色んな物が必要です。";
					mes "ベインスの中央にある";
					mes "道具屋で揃えてください。";
					if(@compass&0x1000)
						viewpoint 1,230,173,4,0x0000FF;
					continue;
				case 5:
					mes "[ベインス案内兵士]";
					mes "ベインスの飛行船は、";
					mes "貨物の運搬のみに";
					mes "使われております。";
					if(@compass&0x1000)
						viewpoint 1,271,292,5,0xCC99FF;
					continue;
				case 6:
					mes "[ベインス案内兵士]";
					mes "ベインスの地元の人と話したい時は、";
					mes "酒場に立ち寄ると良いです。";
					mes "酒場はベインスの西にあります。";
					if(@compass&0x1000)
						viewpoint 1,140,228,6,0xCCCC33;
					continue;
				case 7:
					mes "[ベインス案内兵士]";
					mes "地質学に興味をお持ちですか？";
					mes "では、武器屋の2階にある";
					mes "地質学研究所に行ってください。";
					if(@compass&0x1000)
						viewpoint 1,148,185,7,0xFF9900;
					continue;
				case 8:
					mes "[ベインス案内兵士]";
					mes "ベインスには治安を守る";
					mes "治安管理所があります。";
					mes "何か困った事がありましたら、";
					mes "そこに行ってください。";
					if(@compass&0x1000)
						viewpoint 1,87,170,8,0xFF9900;
					continue;
				case 9:
					mes "[ベインス案内兵士]";
					mes "位置標識を消したい時は";
					mes "「ミニMAP上の位置表示を消す」を";
					mes "選択してください。";
				}
				break;
			}
			continue;
		case 2:
			viewpoint 2,195,275,1,0xFF0000;
			viewpoint 2,130,280,2,0xFF00FF;
			viewpoint 2,148,185,3,0x99FFFF;
			viewpoint 2,230,173,4,0x0000FF;
			viewpoint 2,271,292,5,0xCC99FF;
			viewpoint 2,140,228,6,0xCCCC33;
			viewpoint 2,148,185,7,0xFF9900;
			viewpoint 2,87,170,8,0xFF9900;
			set @compass,@compass&~0x1000;
			set '@flag,0;
			mes "[ベインス案内兵士]";
			mes "ミニMAP上の位置表示を";
			mes "全部消しました。";
			mes "また、気になる事がありましたら";
			mes "いつでも、聞いてください。";
			continue;
		case 3:
			mes "[ベインス案内兵士]";
			mes "街の案内は、モニター右上にある";
			mes "ミニMAPを参考してください。";
			next;
			mes "[ベインス案内兵士]";
			mes "ミニMAPが表示されていない場合は";
			mes "ショートカットキー「Ctrl + Tab」";
			mes "または基本情報ウインドウの";
			mes "「map」ボタンを";
			mes "クリックしてください。";
			next;
			mes "[フィゲル案内要員]";
			mes "ミニMAPが表示されたら";
			mes " ^3333FF-^000000 ボタンをクリックして";
			mes "マップの全体が見えるように";
			mes "設定してください。";
			continue;
		case 4:
			mes "[ベインス案内兵士]";
			mes "では、良い旅を。";
			close;
		}
	}
}
veins.gat,189,101,5	duplicate(ベインス案内兵士#ve)	ベインス案内兵士	934

//----------------------------------------------------------------------
//[案内要員 - モスコビア]

moscovia.gat,161,76,4	script	モスコビアガイド	959,{
	mes "[モスコビアガイド]";
	mes "ようこそ。";
	mes "広い海の上に浮き上がる楽園。";
	mes "美しい海の音色と暖かい日差しが";
	mes "あなたを癒すモスコビアへ。";
	next;
	mes "[モスコビアガイド]";
	mes "私はモスコビア王宮から";
	mes "旅人の利便の為に、街の案内を";
	mes "する為に派遣されたガイドです。";
	mes "何か聞きたい事はありますか？";
	next;
	switch(select("街の案内を受ける","ミニMAP上の位置表示を消す","やめる")){
	case 1:
		mes "[モスコビアガイド]";
		mes "どちらをご案内しましょうか？";
		next;
		switch(select("王宮","礼拝堂","武器・防具屋","道具屋","旅館")) {
		case 1:
			mes "[モスコビアガイド]";
			mes "王宮は ^FF3355+^000000 です。";
			mes "モスコビアのチャール陛下と";
			mes "家臣達がいらっしゃる場所です。";
			viewpoint 1,255,140,1,0xFF3355;
			close;
		case 2:
			mes "[モスコビアガイド]";
			mes "礼拝堂は ^CC6600+^000000 です。";
			mes "モスコビアの平穏を祈る";
			mes "修道士達がいらっしゃいます。";
			viewpoint 1,265,163,2,0xCC6600;
			close;
		case 3:
			mes "[モスコビアガイド]";
			mes "武器・防具屋は ^AABBAA+^000000 です。";
			mes "モスコビア最高の職人達による";
			mes "傑作を見る事ができます。";
			viewpoint 1,186,190,3,0xAABBAA;
			close;
		case 4:
			mes "[モスコビアガイド]";
			mes "道具屋は ^55FF33+^000000 です。";
			mes "旅に出るためには様々な準備が";
			mes "必要ですよね。";
			viewpoint 1,222,175,4,0x55FF33;
			close;
		case 5:
			mes "[モスコビアガイド]";
			mes "旅館は ^3355FF+^000000 です。";
			mes "旅の疲れをここで癒してください。";
			viewpoint 1,229,208,5,0x3355FF;
			close;
		}
	case 2:
		viewpoint 2,255,140,1,0xFF3355;
		viewpoint 2,265,163,2,0xCC6600;
		viewpoint 2,186,190,3,0xAABBAA;
		viewpoint 2,222,175,4,0x55FF33;
		viewpoint 2,229,208,5,0x3355FF;
		mes "[モスコビアガイド]";
		mes "ミニMAPの表示を全て消しました。";
		close;
	case 3:
		mes "[モスコビアガイド]";
		mes "自分で一つずつ見つけ出すのも";
		mes "旅の楽しみですよね。";
		mes "では、良い旅を。";
		close;
	}
}

//----------------------------------------------------------------------
//[案内要員 - ブラジリス]

brasilis.gat,240,81,3	script	ブラジリスガイド	478,{
	mes "[ブラジリスガイド]";
	mes "真っ赤に輝く太陽に";
	mes "情熱的な国、ブラジリスに";
	mes "ようこそいらっしゃいました。";
	mes "何か解らないことがございましたら";
	mes "お聞きください！";
	next;
	while(1) {
		switch(select("街の案内を受ける","ミニMAP上の位置表示を消す","やめる")) {
		case 1:
			mes "[ブラジリスガイド]";
			mes "どちらをご案内いたしましょうか？";
			if(@compass&0x2000 == 0 && '@flag == 0) {
				mes " ";
				mes "-ミニマップに位置表示を";
				mes "　残しますか？-";
				next;
				if(select("はい","いいえ") == 1)
					set @compass,@compass|0x2000;
			}
			set '@flag,1;
			while(1) {
				next;
				switch(select("カプラ職員","ホテル","ジャングルケーブル","美術博物館","商店","バンデラス記念碑","やめる")) {
				case 1:
					mes "[ブラジリスガイド]";
					mes "カプラ職員さんは街の中心に";
					mes "いらっしゃいますよ。";
					mes "近くでアイスクリームも";
					mes "売ってます！";
					if(@compass&0x2000)
						viewpoint 1,197,221,1,0xFFFFFF;
					continue;
				case 2:
					mes "[ブラジリスガイド]";
					mes "ホテルはここからすぐ";
					mes "北北東にありますよ。";
					mes "内装が綺麗でおすすめです！";
					if(@compass&0x2000)
						viewpoint 1,274,151,2,0xFF3355;
					continue;
				case 3:
					mes "[ブラジリスガイド]";
					mes "木々の生い茂るジャングルを";
					mes "お散歩しますか？";
					mes "それではこちらに行ってみてください！";
					mes "ここから、フィールドに";
					mes "出ることができますよ。";
					if(@compass&0x2000)
						viewpoint 1,308,335,3,0xCE6300;
					continue;
				case 4:
					mes "[ブラジリスガイド]";
					mes "世界的規模の美術博物館は";
					mes "ブラジリスの誇りです！";
					mes "是非足を運んでみてください。";
					if(@compass&0x2000)
						viewpoint 1,137,167,4,0x00FF00;
					continue;
				case 5:
					mes "[ブラジリスガイド]";
					mes "お買い物はこちらでできますよ。";
					if(@compass&0x2000)
						viewpoint 1,254,248,5,0x55FF33;
					continue;
				case 6:
					mes "[ブラジリスガイド]";
					mes "ブラジリスの象徴といえる";
					mes "記念碑はこちらです。";
					if(@compass&0x2000)
						viewpoint 1,195,235,6,0x3355FF;
					continue;
				case 7:
					mes "[ブラジリスガイド]";
					mes "位置標識を消したい時は";
					mes "「ミニMAP上の位置表示を消す」を";
					mes "選択してくださいね。";
					break;
				}
				break;
			}
			continue;
		case 2:
			viewpoint 2,197,221,1,0xFFFFFF;
			viewpoint 2,274,151,2,0xFF3355;
			viewpoint 2,308,335,3,0x3355FF;
			viewpoint 2,137,167,4,0x00FF00;
			viewpoint 2,254,248,5,0x3355FF;
			viewpoint 2,195,235,6,0x3355FF;
			set @compass,@compass&~0x2000;
			set '@flag,0;
			mes "[ブラジリスガイド]";
			mes "ミニMAP上の位置表示を";
			mes "全て消しました。";
			mes "また、気になる事がありましたら";
			mes "いつでも聞いてくださいね。";
			close;
		case 3:
			mes "[ブラジリスガイド]";
			mes "直接街を見て回るのも";
			mes "楽しいですよ！";
			mes "それでは、ブラジリスでの旅を";
			mes "ごゆっくりお楽しみください！";
			close;
		}
	}
}


//----------------------------------------------------------------------
//[案内要員 - デワタ]

dewata.gat,226,82,4	script	デワタ案内要員#dew1	537,{
	mes "[デワタ案内要員]";
	mes "美しい波が心を穏やかにさせる、";
	mes "ここ、^884411デワタ^000000へようこそ。";
	mes "街のご案内をしましょうか？";
	while(1) {
		next;
		switch(select("カプラ職員","ホテル・ザ・グラント","食堂マスター","武器商人","防具商人","道具商人","果物商人","クラカト火山案内人","アルベルタ行船員","ミニMAP上の位置表示を消す","やめる")) {
		case 1:
			mes "[デワタ案内要員]";
			mes "カプラ職員は";
			mes ((strnpcinfo(2) == "dew2")? "すぐそちら": "街の中央")+ "にいます。";
			viewpoint 1,202,184,1,0xFF0000;
			break;
		case 2:
			mes "[デワタ案内要員]";
			mes "ホテル・ザ・グラントは";
			mes "街の北西にあります。";
			viewpoint 1,127,289,2,0x99FFFF;
			break;
		case 3:
			mes "[デワタ案内要員]";
			mes "食堂マスターは";
			mes "街の南西にいます。";
			viewpoint 1,146,109,3,0xFF00FF;
			break;
		case 4:
			mes "[デワタ案内要員]";
			mes "武器商人は";
			mes "街の中央のやや南東にいます。";
			viewpoint 1,218,164,4,0x0000FF;
			break;
		case 5:
			mes "[デワタ案内要員]";
			mes "防具商人は";
			mes "街の中央のやや西にいます。";
			viewpoint 1,158,182,5,0xCC99FF;
			break;
		case 6:
			mes "[デワタ案内要員]";
			mes "道具商人は";
			mes "街の中央のやや南西にいます。";
			viewpoint 1,182,164,6,0xCCCC33;
			break;
		case 7:
			mes "[デワタ案内要員]";
			mes "果物商人は";
			mes "街の中央の北西にいます。";
			viewpoint 1,145,267,7,0xFF9900;
			break;
		case 8:
			mes "[デワタ案内要員]";
			mes "クラカト火山案内人は";
			mes "街の南にいます。";
			viewpoint 1,235,56,8,0x00FF00;
			break;
		case 9:
			mes "[デワタ案内要員]";
			mes "アルベルタ行船員は";
			mes "街の南にいます。";
			viewpoint 1,229,49,9,0xFFFFFF;
			break;
		case 10:
			viewpoint 2,202,184,1,0xFF0000;
			viewpoint 2,127,289,2,0x99FFFF;
			viewpoint 2,146,109,3,0xFF00FF;
			viewpoint 2,218,164,4,0x0000FF;
			viewpoint 2,158,182,5,0xCC99FF;
			viewpoint 2,182,164,6,0xCCCC33;
			viewpoint 2,145,267,7,0xFF9900;
			viewpoint 2,235,56,8,0x00FF00;
			viewpoint 2,229,49,9,0xFFFFFF;
			mes "[デワタ案内要員]";
			mes "ミニMAP上の位置表示を";
			mes "全て消しました。";
			break;
		case 11:
			mes "[デワタ案内要員]";
			mes "それでは、よい観光を。";
			close;
		}
	}
}
dewata.gat,197,184,4	duplicate(デワタ案内要員#dew1)	デワタ案内要員#dew2	537

//----------------------------------------------------------------------
//[案内要員 - ポートマラヤ]

malaya.gat,71,72,4	script	ポートマラヤガイド#01	579,{
	mes "[ポートマラヤガイド]";
	mes "多様な文化と伝説が生きる町";
	mes "^8B4513ポートマラヤ^000000にようこそ。";
	mes "私は町案内をしているので";
	mes "知りたいことがあれば";
	mes "なんでも聞いて下さい。";
	while(1) {
		next;
		switch(select("カプラ職員","旅館","武器商人","道具商人","病院","公園","港","ミニマップ上の位置表示を消す","やめる")) {
		case 1:
			mes "[ポートマラヤガイド]";
			mes "^0000FFカプラ職員^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,71,79,0,0x0A82FF;
			viewpoint 1,234,204,1,0x0A82FF;
			continue;
		case 2:
			mes "[ポートマラヤガイド]";
			mes "^006400旅館^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,178,208,2,0xAAFF00;
			continue;
		case 3:
			mes "[ポートマラヤガイド]";
			mes "^008080武器商人^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,114,212,3,0x008080;
			continue;
		case 4:
			mes "[ポートマラヤガイド]";
			mes "^FF1493道具商人^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,297,167,4,0xFF1493;
			continue;
		case 5:
			mes "[ポートマラヤガイド]";
			mes "^FF4500病院^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,50,75,5,0xFF4500;
			continue;
		case 6:
			mes "[ポートマラヤガイド]";
			mes "^FF8C00公園^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,280,360,6,0xFF8C00;
			continue;
		case 7:
			mes "[ポートマラヤガイド]";
			mes "^8A2BE2港^000000の";
			mes "位置をミニマップに";
			mes "表示します。";
			mes "他に案内が必要ですか？";
			viewpoint 1,276,55,7,0x8A2BE2;
			continue;
		case 8:
			mes "[ポートマラヤガイド]";
			mes "ミニマップ上の位置表示を消去します。";
			mes "他に何か必要ですか？";
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			viewpoint 2,1,1,6,0xFFFFFF;
			viewpoint 2,1,1,7,0xFFFFFF;
			continue;
		case 9:
			mes "[ポートマラヤガイド]";
			mes "楽しんで行って下さいね。";
			close;
		}
	}
}
malaya.gat,250,83,6		duplicate(ポートマラヤガイド#01)	ポートマラヤガイド#02	579
malaya.gat,224,204,6	duplicate(ポートマラヤガイド#01)	ポートマラヤガイド#03	579
