//----------------------------------------------------------------------
// スクリプト : Event_Potion v1.1
//----------------------------------------------------------------------

prontera.gat,73,140,0	script	牛乳商人	86,{
	mes "[牛乳商人]";
	mes "空きビンを持ってきたら、";
	mes "たった 15Zenyでミルク1個と";
	mes "交換してあげますよー";
	next;
	switch(select("空きビンを全部交換する","やめる")) {
	case 1:
		if(countitem(713)<1) {
			mes "[牛乳商人]";
			mes "ささ、空きビンを。";
			mes "……ありませんか？";
			close;
		}
		set '@num,countitem(713);
		if(Zeny<'@num*15) {
			mes "[牛乳商人]";
			mes "あれ、お金が足りませんね。";
			mes ('@num*15)+ " Zeny足りません……";
			close;
		}
		if(checkweight(519,'@num)==0) {
			mes "[牛乳商人]";
			mes "ちょっと荷物が多いようですね……";
			mes "それではミルクをもちきれないですよ。";
			mes "荷物を減らすか、交換する空きビン";
			mes "の数を減らしてからおこしください。";
			close;
		}
		delitem 713,'@num;
		set Zeny,Zeny-'@num*15;
		getitem 519,'@num;
		close;
	case 2:
		mes "[牛乳商人]";
		mes "またどうぞー。";
		close;
	}
}

// ■ JUICE_EVE -> 0～13、13でジュース製作可能
//                    10までは肉をあげる度に1ずつ加算

prt_in.gat,49,172,3	script	マリエヌ	53,{
	switch(JUICE_EVE) {
	case 0:
		mes "[主婦マリエヌ]";
		mes "モリスン!!";
		mes "はやく果物食べなさい!!";
		mes "食べなさいってば～！";
		next;
		mes "ったく～!!";
		mes "どうして、あんなことだけ";
		mes "お父さんにそっくりなのかしら……";
		next;
		if(select("話をする","やめる")==2) {
			mes "[主婦マリエヌ]";
			mes "モリスン!!";
			mes "お母さんの言うこと聞かないと";
			mes "怒るわよ！";
			close;
		}
		mes "[主婦マリエヌ]";
		mes "ふ…この子は私の息子、モリスンです。";
		mes "この頃、この子が果物を食べようと";
		mes "しないんです。果物をぜんぜん";
		mes "食べないから顔色も悪くて……";
		next;
		mes "[主婦マリエヌ]";
		mes "ずっと肉ばかり食べようとして……";
		mes "ふう……なんとかして果物とか野菜も";
		mes "食べさせなきゃ……";
		close;
	case 1:
		mes "[主婦マリエヌ]";
		mes "モリスン!!";
		mes "はやく果物を食べなさい!!";
		mes "あなた、一体何歳になってまで";
		mes "そんなにワガママなの?!";
		mes "太った豚みたいになりたいの？";
		next;
		if(select("話をする","やめる")==2) {
			mes "[主婦マリエヌ]";
			mes "モリスン!!";
			mes "いい加減にしないと";
			mes "ママ本当に怒るわよ！";
			close;
		}
		mes "[主婦マリエヌ]";
		mes "あ、あなた！うちのモリスンに";
		mes "肉を食べさせた人ね?!";
		mes "ひょっとして、私が知らないと思って";
		mes "また来たんですか？";
		mes "ふん……図々しいわね。";
		mes "私が馬鹿だと思ってるわけ？";
		next;
		mes "[主婦マリエヌ]";
		mes "今すぐ出ていきなさい!!!";
		close;
	default:	//イベント消滅ルート
		mes "[主婦マリエヌ]";
		mes "あらっ!!";
		mes "な～んですか、これ!!";
		mes "うちの子にこんなもの食べさせないで";
		mes "ください！あふ～～図々しい!!";
		mes "早く出て行ってください！";
		close;
	case 12:
	case 13:
		mes "[主婦マリエヌ]";
		mes "ふう……肉じゃないと";
		mes "食べようともしないなんて……";
		mes "果物を食べやすくすれば、";
		mes "食べてくれるかしら……例えば……";
		mes "ジュースにしたりして……";
		next;
		mes "[主婦マリエヌ]";
		mes "あ！そういえば、ある村で果物を";
		mes "ジュースにしてくれると言ってたわ。";
		mes "……フェイヨンだったかしら？";
		mes "……モロクだったかしら……";
		if(JUICE_EVE == 12)
			set JUICE_EVE,13;
		close;
	}
}

prt_in.gat,47,173,3	script	モリスン	97,{
	switch(JUICE_EVE) {
	default:	//0～9のとき
		mes "[ちびモリスン]";
		mes "あ……アアァッ!!!";
		mes "た……食べないんだから！";
		mes "果物なんか、食べないんだから!!";
		next;
		if(countitem(517))
			set '@talk$,"肉を見せる";
		switch (select("話をする",'@talk$,"やめる")) {
			case 1:
				mes "[ちびモリスン]";
				mes "アアアッ!! 一回か二回だったら";
				mes "いいかも知れないけど!!";
				mes "もうこれ以上果物は食べられない！";
				next;
				mes "[ちびモリスン]";
				mes "僕は……果物みたいなもん……";
				mes "皮をむくのが面倒だし、";
				mes "水気が多くて気持ち悪いし";
				mes "それにすっぱくてヌルヌル……";
				mes "食べた後は物足りないし、";
				mes "アアアッ！肉が食べたい～！";
				close;
			case 2:
				mes "[ちびモリスン]";
				mes "アアッ！に……肉だっ";
				mes "……おおっ";
				mes "あ……お……お腹空いた……";
				mes "この肉の匂い……あの……";
				mes "一つもらえませんか？";
				next;
				if(select("肉をあげる","肉をあげない")==1) {
					delitem 517,1;
					set JUICE_EVE,JUICE_EVE+1;
					mes "[ちびモリスン]";
					mes "わあ～!!!肉だ、肉！美味しそう。";
					mes "ありがとう。もういけそうです。";
					mes "がりがり むしゃむしゃ……";
				}
				else {
					mes "[ちびモリスン]";
					mes "うう……そ……そう……";
					mes "もうわかったよ！";
					mes "大人なんてみんな同じだ！";
					set JUICE_EVE,12;
				}
				close;
			case 3:
				mes "[ちびモリスン]";
				mes "ああっ!!!何と言われても";
				mes "僕は野菜と果物は食べれないよ！";
				close;
		}
	case 10:
	case 11:
		mes "[ちびモリスン]";
		mes "あ……もうお腹いっぱいだ。";
		mes "もういいです。";
		mes "もう肉はいいです。";
		mes "これ以上食べたら";
		mes "お腹が破れてしまいそう。";
		if(JUICE_EVE == 10) {
			next;
			mes "[ちびモリスン]";
			mes "そして……これ、受け取って。";
			mes "僕が、この間もらったキャンディ。";
			mes "こっそり後で食べようと、";
			mes "隠してたんだけど、肉をくれたから";
			mes "代わりにあげるよ。";
			set JUICE_EVE,11;
			getitem 529,3;
			getitem 530,1;
		}
		close;
	case 12:
	case 13:
		mes "[ちびモリスン]";
		mes "ちぇっ……いいよ、もう……";
		mes "ずっと果物ばっかり食べて";
		mes "死んじゃうから。僕のこともう";
		mes "気にしないでちょうだい。";
		close;
	}
}

payon_in03.gat,188,146,4	script	マルクハンセン	86,{
	if(JUICE_EVE < 13) {
		mes "[商人マルクハンセン]";
		mes "いらっしゃい！";
		mes "なんのご用ですか？";
		next;
		if(select("話をする","やめる")==2) {
			mes "[商人マルクハンセン]";
			mes "人を訪ねてきたのなら、";
			mes "用件を話したらどうですか？";
			close;
		}
		callsub L_Routine;
		close;
	}
	mes "[商人マルクハンセン]";
	mes "いらっしゃい！";
	mes "あなたも果物を加工しに来ましたか？";
	next;
	switch (select("フルーツジュースをつくる","話をする","やめる")) {
	case 1:
		mes "[商人マルクハンセン]";
		mes "どんなフルーツジュースを作りますか？";
		next;
		switch (select("リンゴジュース","バナナジュース","ニンジンジュース","ブドウジュース","やめる")) {
			case 1:
				setarray '@need,512,713;
				set '@gain,531;
				break;
			case 2:
				setarray '@need,513,713;
				set '@gain,532;
				break;
			case 3:
				setarray '@need,515,713;
				set '@gain,534;
				break;
			case 4:
				setarray '@need,514,713;
				set '@gain,533;
				break;
			case 5:
				mes "[商人マルクハンセン]";
				mes "ふーむ、嫌ならしようがない……";
				close;
		}
		setarray '@amount,1,1;	//個数はどのジュースでも共通
		set '@max,callfunc("MathMax",'@need,'@amount,3);
		if('@max==0) {
			mes "[商人マルクハンセン]";
			mes "材料が足りないようですね。";
			mes getitemname('@gain)+ "を作るには";
			mes getitemname('@need[0])+ "1個と 空きビン1個";
			mes "が必要です。";
			mes "また手数料 3 zeny かかります。";
			mes "私がよ～く絞って、";
			mes "食べやすくしてあげましょう。";
			close;
		}
		mes "[商人 マルクハンセン]";
		mes "いくつほどほしいのでしょうか？";
		next;
		switch (select("できるだけ全部","数を決める","やめる")) {
			case 1:
				set '@num,'@max;
				break;
			case 2:
				mes "[商人マルクハンセン]";
				mes "100個以下で決めて下さい。";
				mes "いらないのなら0でお願いします。";
				mes "君が持っているアイテムでは";
				mes "最大 " +'@max+ " 個まで出来ますね。";
				while(1) {
					next;
					input '@num;
					if('@num>100 || '@num<0) {
						mes "[商人マルクハンセン]";
						mes "100個以上は無理です。";
						continue;
					}
					break;
				}
				if('@num==0) {
					mes "[商人マルクハンセン]";
					mes "じゃ、また……";
					close;
				}
				if('@num > '@max) {
					mes "[商人マルクハンセン]";
					mes "材料が足りないようですね。";
					mes "材料を早く集めてきてください……";
					close;
				}
				break;
			case 3:
				mes "[商人マルクハンセン]";
				mes "じゃまた……";
				close;
		}
		delitem '@need[0],'@num;
		delitem '@need[1],'@num;
		set Zeny,Zeny-'@num*3;
		getitem '@gain,'@num;
		mes "[商人マルクハンセン]";
		mes "さ！約束したジュースです。";
		mes "美味しそうでしょ。";
		mes "では、また是非来てください。";
		close;
	case 2:
		callsub L_Routine;
		next;
		mes "# フルーツジュース #";
		mes "りんごジュース";
		mes "^3355FFりんご1個、空きビン1個、3 zeny^000000";
		mes "バナナジュース";
		mes "^3355FFバナナ1個、空きビン1個、3 zeny^000000";
		next;
		mes "# フルーツジュース #";
		mes "ニンジンジュース";
		mes "^3355FFニンジン1個、空きビン1個、3 zeny^000000";
		mes "ブドウジュース";
		mes "^3355FFブドウ1個、空きビン1個、3 zeny^000000";
		close;
	case 3:
		mes "[商人マルクハンセン]";
		mes "人を訪ねてきたのなら、";
		mes "用件を話したらどうですか？";
		close;
	}
L_Routine:	//sub routine
	mes "[商人マルクハンセン]";
	mes "人間がまだ、今のように多くの知識を";
	mes "持つ前ですが、みんな果物をたくさん";
	mes "食べて生きていたと言います。";
	next;
	mes "[商人マルクハンセン]";
	mes "ひょっとしたら、果物は";
	mes "人間をこの世に存在できるようにした";
	mes "大自然の恵みではないのでしょうか。";
	next;
	mes "[商人マルクハンセン]";
	mes "しかし、生活が豊かになり";
	mes "この頃の若者は果物を食べないように";
	mes "なってしまったみたいです。";
	mes "そこで、果物を食べやすくする方法を";
	mes "考えてみました。";
	next;
	mes "[商人マルクハンセン]";
	mes "その結果、果物をよく絞って";
	mes "果汁にしたら、食べやすくなり、";
	mes "味ももっと良くなることが";
	mes "分かりました。";
	return;
}

alberta_in.gat,16,28,4	script	薬師おじいさん	61,{
	mes "[製薬師おじいさん]";
	mes "おぉ…お客さんか…？";
	mes "何の用かね？";
	next;
	switch (select("ポーションを作る","話を聞く","組み合わせを聞く","何でもありません")) {
	case 1:
		mes "[製薬師おじいさん]";
		mes "材料は用意して来たかね？";
		mes "どれが欲しいかね？";
		next;
		switch (select("赤ポーション","紅ポーション","黄ポーション","白ポーション","青ポーション","緑ポーション","やっぱりやめる")) {
			case 1:
				setarray '@need,507,713;
				setarray '@amount,2,1;
				set '@price,3;
				set '@gain,501;
				break;
			case 2:
				setarray '@need,507,508,713;
				setarray '@amount,1,1,1;
				set '@price,5;
				set '@gain,502;
				break;
			case 3:
				setarray '@need,508,713;
				setarray '@amount,2,1;
				set '@price,10;
				set '@gain,503;
				break;
			case 4:
				setarray '@need,509,713;
				setarray '@amount,2,1;
				set '@price,20;
				set '@gain,504;
				break;
			case 5:
				setarray '@need,510,713;
				setarray '@amount,2,1;
				set '@price,30;
				set '@gain,505;
				break;
			case 6:
				setarray '@need,511,713;
				setarray '@amount,2,1;
				set '@price,3;
				set '@gain,506;
				break;
			case 7:
				close;
		}
		if(Zeny<'@price) {	//1個も作れないくらい金がない場合
			mes "[製薬師おじいさん]";
			mes "この悪ガキ！";
			mes "金もないくせに作れとな？";
			mes "帰れ！帰れ！";
			close;
		}
		set '@max,callfunc("MathMax",'@need,'@amount,'@price);
		if('@max==0) {
			mes "[製薬師おじいさん]";
			mes "この悪ガキ！";
			mes "材料もないくせにに作れとな？";
			mes "帰れ！帰れ！";
			close;
		}
		mes "[製薬師おじいさん]";
		mes "どのくらい欲しい？";
		next;
		switch (select("出来る限り","数を決めます","やっぱりやめます")) {
			case 1:
				set '@num,'@max;
				break;
			case 2:
				mes "[製薬師おじいさん]";
				mes "ならば、100個以下にして";
				mes "くれるかな。やめるんだったら";
				mes "0にしてくれるかな。";
				mes "君が持っている材料では";
				mes '@max+" 個ぐらい作れそうだの。";
				while(1) {
					next;
					input '@num;
					if('@num>100 || '@num<0) {
						mes "[製薬師おじいさん]";
						mes "君、耳が悪いのかの？";
						mes "100個以下にしてくれと";
						mes "言っただろう！";
						continue;
					}
					break;
				}
				if('@num==0) {
					mes "[製薬師おじいさん]";
					mes "はっきり決めんかい！";
					close;
				}
				if('@num > '@max) {
					mes "[製薬師おじいさん]";
					mes "材料もないくせに作れとな？";
					close;
				}
				break;
			case 3:
				mes "[製薬師おじいさん]";
				mes "なに？用がないなら";
				mes "話しかけるでない！";
				close;
		}
		if('@gain==502) {	//紅だけは2種類のハーブが必要
			delitem 507,'@num;
			delitem 508,'@num;
		}
		else {
			delitem '@need[0],'@num*2;
		}
		delitem 713,'@num;
		set Zeny,Zeny-'@price*'@num;
		getitem '@gain,'@num;
		mes "[製薬師おじいさん]";
		mes "うむ、完成したぞ！";
		mes "ほれ、受け取ってくれるかな。";
		mes "気を付けろ！薬は使いすぎると";
		mes "体によくないからの！";
		close;
	case 2:
		mes "[製薬師おじいさん]";
		mes "薬は人間の回復能力を向上させて";
		mes "くれる。人間の回復能力をどこまでも";
		mes "引き出してくれる訳ではないがな……";
		next;
		mes "[製薬師おじいさん]";
		mes "とほほ……年を取ったからなのか、";
		mes "昔のことを良く思い出すな……";
		mes "とにかく、ポーションは薬であるだけ…";
		mes "…それ以上でもそれ以下でもない。";
		close;
	case 3:
		mes "[製薬師おじいさん]";
		mes "やれやれ……若いヤツはシツコイのぅ。";
		mes "よし、そこまで聞きたいのなら、";
		mes "詳しく説明してやるか。";
		next;
		mes "[製薬師おじいさん]";
		mes "ハーブはそのまま使っても効果あるが、";
		mes "わしの優れた知識と、ある秘法で";
		mes "水薬にすれば、その効果はもっと";
		mes "高くなる";
		next;
		mes "[製薬師おじいさん]";
		mes "欲しいというなら作ってあげよう。";
		mes "だが、ただと言うわけにはいかん……";
		mes "若干、手数料をいただくが、";
		mes "わしの小遣い程度だから";
		mes "そんなに高くはない。";
		next;
		mes "[製薬師おじいさん]";
		mes "赤ポーション";
		mes "^0098E5赤ハーブ 2個、空きビン 1個";
		mes "手数料 3 zeny^000000";
		mes "紅ポーション";
		mes "^0098E5赤ハーブ 1個、黄ハーブ 1個、空きビン";	//半角「、」じゃないとずれます。
		mes "1個";
		mes "手数料 5 zeny^000000";
		next;
		mes "[製薬師おじいさん]";
		mes "黄ポーション";
		mes "^0098E5黄ハーブ 2個、空きビン 1個";
		mes "手数料 10 zeny^000000";
		mes "白ポーション";
		mes "^0098E5白ハーブ 2個、空きビン 1個";
		mes "手数料 20 zeny^000000";
		next;
		mes "[製薬師おじいさん]";
		mes "青ポーション";
		mes "^0098E5靑ハーブ 2個、空きビン 1個";
		mes "手数料 30 zeny^000000";
		mes "録ポーション";
		mes "^0098E5録ハーブ 2個、空きビン 1個";
		mes "手数料 3 zeny^000000";
		close;
	case 4:
		mes "[製薬師おじいさん]";
		mes "何だね？";
		mes "言いたいことがあったら";
		mes "はっきり言ったらどうかね！";
		close;
	}
}
