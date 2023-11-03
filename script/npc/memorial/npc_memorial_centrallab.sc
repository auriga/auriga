//= Auriga Script ==============================================================
// Ragnarok Online Central Laboratory Script	by refis
//==============================================================================
verus01.gat,149,155,5	script	文明探査員	865,{
	if(!checkquest(12346)) {
		mes "[文明探査員]";
		mes "ここの古代文明は";
		mes "いろいろと不思議な点が多いのです。";
		next;
		mes "[文明探査員]";
		mes "積層の年代から察すると";
		mes "最低でも500～600年は経っていると";
		mes "推定されますが、";
		mes "ここで発掘されたものは";
		mes "現在の私たちの科学技術より";
		mes "優れているようなのです。";
		next;
		mes "[文明探査員]";
		mes "発見された古い記録からは";
		mes "その正体が分からない単語も";
		mes "多数見つかっています。";
		next;
		menu "正体が分からない単語？",-;
		mes "[文明探査員]";
		mes "そうです。例えば……";
		mes "^0000ffマザーコンピューター^000000や";
		mes "^0000ffLSIチップ^000000。";
		mes "あとはそうですね、";
		mes "^0000ffたれ付き焼き肉^000000なんて単語も";
		mes "見つかりました。";
		next;
		mes "[文明探査員]";
		mes "たれ付き焼き肉はともかく、";
		mes "その他のものは";
		mes "いったいどんな技術の結晶体なのか";
		mes "計り知れません。";
		next;
		mes "[文明探査員]";
		mes "多くの科学技術の痕跡に";
		mes "関連する者たちの記録に、";
		mes "共通して言及されていました。";
		next;
		if(select("興味深いですね","あまり興味がありません") == 2) {
			mes "[文明探査員]";
			mes "それは残念ですね。";
			mes "それではまた。";
			close;
		}
		mes "[文明探査員]";
		mes "私は科学技術の使い道を、";
		mes "当時の時代像と連携して";
		mes "探求することを仕事としています。";
		mes "まだ発見したものは";
		mes "微々たるものですが。";
		next;
		mes "[文明探査員]";
		mes "本当ならここにある次元移動機で";
		mes "直接研究しに行きたいのですが、";
		mes "他の優先業務が詰まってまして……。";
		mes "それに私は強くないですしね。";
		next;
		mes "[文明探査員]";
		mes "そこでですが、";
		mes "あなたはここから^ff0000過去^000000を";
		mes "旅してみる気はありませんか？";
		next;
		mes "[文明探査員]";
		mes "何か興味深いものを発見したら";
		mes "見せていただけると嬉しいです。";
		next;
		if(select("過去に行きます","興味ありません") == 2) {
			mes "[文明探査員]";
			mes "そうですか、";
			mes "興味が沸いたらまた来てください。";
			close;
		}
		mes "[文明探査員]";
		mes "本当ですか！";
		mes "ご協力に感謝します!!";
		setquest 12346;
		next;
		compquest 12346;
		if(getonlinepartymember() < 1) {
			mes "[文明探査員]";
			mes "^ff0000パーティーを結成していないと";
			mes "この先には進めません。^000000";
			mes "1人以上のパーティーを作るか、";
			mes "他のパーティーに加入してから";
			mes "もう一度話しかけてください。";
			close;
		}
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[文明探査員]";
			mes "あなたはパーティーのリーダーでは";
			mes "ありませんね。リーダーの方より";
			mes "入場の申請していただけましたら、";
			mes "次元の歪みを開きます。";
			close;
		}
		if(select("時間の歪みを生成","会話をやめる") == 2) {
			mes "‐あなたはその場を後にした‐";
			close;
		}
		mdcreate "rose";
		mes "[文明探査員]";
		mes "時間の歪が開いた後に";
		mes "もう一度話しかけてください。";
		close;
	}
	if(checkquest(118320)) {
		mes "[文明探査員]";
		mes "お帰りなさい。";
		mes "何か興味深いものは";
		mes "見つかりましたか？";
		next;
		mes "‐中央実験室の内部で";
		mes "　目撃した内容を伝えた‐";
		next;
		mes "[文明探査員]";
		mes "な、なんと！";
		mes "ここにあった文明は";
		mes "実験の失敗で";
		mes "滅んだと……。";
		next;
		mes "[文明探査員]";
		mes "にわかには信じられませんが";
		mes "なるほど……";
		mes "大変興味深い内容ですね。";
		next;
		mes "[文明探査員]";
		mes "ご協力ありがとうございました。";
		mes "お礼と言うほどではありませんが";
		mes "こちらをお受け取りください。";
		next;
		mes "[文明探査員]";
		mes "また、調査にご協力頂ける時は";
		mes "私に声をかけてくださいね。";
		mes "お待ちしています。";
		if(checkitemblank() == 0) {
			next;
			mes "[文明探査員]";
			mes "おや、荷物の数が多くて";
			mes "持つことができないようですね。";
			mes "荷物を減らしてから";
			mes "また、来てください。";
			close;
		}
		delquest 118320;
		if(checkquest(118325) & 0x8 == 0) {
			setquest 118325;
			compquest 118325;
			getitem 6962,10;
		}
		else {
			getitem 6962,1;
		}
		close;
	}
	mes "[文明探査員]";
	mes "今回はどうしますか？";
	next;
	if(getonlinepartymember() < 1) {
		mes "[文明探査員]";
		mes "^ff0000パーティーを結成していないと";
		mes "この先には進めません。^000000";
		mes "1人以上のパーティーを作るか、";
		mes "他のパーティーに加入してから";
		mes "もう一度話しかけてください。";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[文明探査員]";
		mes "あなたはパーティーのリーダーでは";
		mes "ありませんね。リーダーの方より";
		mes "入場の申請していただけましたら、";
		mes "次元の歪みを開きます。";
		close;
	}
	if(checkquest(12347)) {
		if(checkquest(12347) & 0x2 == 0) {
			mes "[文明探査員]";
			mes "おや？";
			mes "次元移動の痕跡が残っていますね。";
			mes "痕跡が完全に消えてから";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "^0000ff‐中央実験室の痕跡が消えました。";
		mes "　再生成が可能です‐^000000";
		delquest 12347;
		close;
	}
	if(select("時間の歪みを生成","会話をやめる") == 2) {
		mes "‐あなたはその場を後にした‐";
		close;
	}
	mdcreate "rose";
	mes "[文明探査員]";
	mes "時間の歪が開いた後に";
	mes "もう一度話しかけてください。";
	close;
}

verus01.gat,153,155,5	script	臨時次元移動機	10007,{
	if(!checkquest(12346)) {
		mes "[文明探査員]";
		mes "失礼ですが、";
		mes "冒険者の方ですよね？";
		mes "私はその機械を使って";
		mes "調査を行っているのですが、";
		mes "もし、よろしかったら";
		mes "私の話を聞いて頂けませんか？";
		next;
		mes "‐まずは文明探査員の";
		mes "　話を聞いてみよう‐";
		close;
	}
	if(select("入場する","やめる") == 2) {
		mes "‐あなたはその場を後にした‐";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[臨時次元移動機]";
		mes "^ff0000パーティーを結成していないと";
		mes "この先には進めません。^000000";
		mes "1人以上のパーティーを作るか、";
		mes "他のパーティーに加入してから";
		mes "もう一度話しかけてください。";
		close;
	}
	if(checkquest(12347)) {
		if(checkquest(12347) & 0x2 == 0) {
			mes "[臨時次元移動機]";
			mes "^0000ff次元移動を行った痕跡が残っています。";
			mes "時間の歪の生成および";
			mes "中央実験室への入場が拒否されました。^000000";
			close;
		}
		mes "[臨時次元移動機]";
		mes "^0000ff中央実験室の痕跡が消えました。";
		mes "　再入場が可能です。^000000";
		delquest 12347;
		close;
	}
	switch(mdenter("rose")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[rose] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
		setquest 12347;
		donpcevent getmdnpcname("CentralLabControl1")+ "::OnStart";
		//warp "1@lab.gat",120,30;
		close;
	case 1:	// パーティー未加入
		mes "[臨時次元移動機]";
		mes "^ff0000パーティーリーダーと同じパーティーの";
		mes "メンバーだけが、";
		mes "時間の歪を利用できます。^000000";
		close;
	case 2:	// ダンジョン未作成
		mes "[臨時次元移動機]";
		mes "^ff0000パーティーリーダーが";
		mes "時間の歪を生成していません。^000000";
		close;
	default:	// その他エラー
		close;
	}
}

1@lab.gat,1,1,0	script	CentralLabControl1	139,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("centrallab_warp#1");
	hideonnpc getmdnpcname("centrallab_warp#2");
	hideonnpc getmdnpcname("centrallab_warp#3");
	hideonnpc getmdnpcname("centrallab_warp#4");
	hideonnpc getmdnpcname("centrallab_warp#5");
	hideonnpc getmdnpcname("centrallab_warp#end");
	for(set '@i,0; '@i<=14; set '@i,'@i+1) {
		hideonnpc getmdnpcname("#centrallab_gen_"+ ('@i < 10 ? "0" : "") + '@i);
	}
}

1@lab.gat,102,28,0	warp	centrallab_warp#1	1,1,1@lab.gat,97,28
1@lab.gat,80,28,0	warp	centrallab_warp#2	1,1,1@lab.gat,75,28
1@lab.gat,58,28,0	warp	centrallab_warp#3	1,1,1@lab.gat,53,28

1@lab.gat,104,34,4	script	研修研究員#rose	865,{
	if('flag) {
		mes "[研修研究員]";
		mes "既に入り口は開いていますよ。";
		close;
	}
	mes "[研修研究員]";
	mes "研究ナンバー32001の";
	mes "実験補助者として";
	mes "参加する方ですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[研修研究員]";
		mes "実験室を間違えたようですね。";
		mes "インフォメーションに";
		mes "再度問い合わせください。";
		close;
	}
	mes "[研修研究員]";
	mes "立ち入り許可コードの確認をします。";
	mes "少々お待ちください。";
	initnpctimer;
	close;
OnTimer4000:
	unittalk "研修研究員 : 許可コードの一致を確認。入口を開きます。";
	end;
OnTimer8000:
	stopnpctimer;
	unittalk "研修研究員 : どうぞ、お入りください。中からこちらへの移動はできませんので注意してください。";
	hideoffnpc getmdnpcname("centrallab_warp#1");
	hideoffnpc getmdnpcname("centrallab_warp#2");
	hideoffnpc getmdnpcname("centrallab_warp#3");
	set 'flag,1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ128#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ64#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ32#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ16#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ8#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ4#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ2#rose")),1;
	set getvariableofnpc('flag,getmdnpcname("スイッチ1#rose")),1;
	end;
}

1@lab.gat,37,37,3	script	スイッチ128#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,39,37,3	script	スイッチ64#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,41,37,3	script	スイッチ32#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,43,37,3	script	スイッチ16#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,46,37,3	script	スイッチ8#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,48,37,3	script	スイッチ4#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,50,37,3	script	スイッチ2#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,52,37,3	script	スイッチ1#rose	844,{
	set '@name$,strnpcinfo(1);
	mes "[" +'@name$+ "]";
	mes "現在このスイッチの状態は" +('flag? "ON": "OFF")+ "です。";
	next;
	switch(select("ON","OFF")) {
	case 1:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをONにしました。";
		set 'flag,1;
		close;
	case 2:
		misceffect 18;
		mes "[" +'@name$+ "]";
		mes "スイッチをOFFにしました。";
		set 'flag,0;
		close;
	}
}

1@lab.gat,45,32,3	script	主任研究員#rose	865,{
	if(getvariableofnpc('flag,getmdnpcname("メインスイッチ#rose")) > 0) {
		mes "[主任研究員]";
		mes "入口は開いてますのでお入りください。";
		mes "中からこちらへの移動は";
		mes "できませんので";
		mes "注意してください。";
		close;
	}
	set '@code,(gettime(6) + gettime(5)) * 5;
	mes "[主任研究員]";
	mes "ここまでおいでになったということは";
	mes "^ff0000粒子加速実験^000000の参加者ですね。";
	next;
	mes "[主任研究員]";
	mes "本日の立ち入り許可コードは";
	mes "^0000ff" +'@code+ "^000000です。";
	mes "許可コードを2進数に変換して、";
	mes "私の後ろにあるスイッチに";
	mes "入力してください。";
	next;
	mes "[主任研究員]";
	mes "このコードは日替わりです。";
	mes "入力中に日付が変わると、";
	mes "コードも変更されますので";
	mes "ご注意ください。";
	next;
	mes "[主任研究員]";
	mes "スイッチを合わせた後は";
	mes "入り口隣のメインスイッチを";
	mes "押してください。";
	if('flag == 0) {
		donpcevent getmdnpcname("主任研究員#rose")+ "::OnStart";
	}
	close;
OnStart:
	initnpctimer;
	set 'flag,1;
	misceffect 18,getmdnpcname("スイッチ128#rose");
	misceffect 18,getmdnpcname("スイッチ64#rose");
	misceffect 18,getmdnpcname("スイッチ32#rose");
	misceffect 18,getmdnpcname("スイッチ16#rose");
	misceffect 18,getmdnpcname("スイッチ8#rose");
	misceffect 18,getmdnpcname("スイッチ4#rose");
	misceffect 18,getmdnpcname("スイッチ2#rose");
	misceffect 18,getmdnpcname("スイッチ1#rose");
	end;
OnTimer5000:
	initnpctimer;
	misceffect 203,getmdnpcname("メインスイッチ#rose");
	misceffect 204,getmdnpcname("スイッチ128#rose");
	misceffect 205,getmdnpcname("スイッチ64#rose");
	misceffect 206,getmdnpcname("スイッチ32#rose");
	misceffect 207,getmdnpcname("スイッチ16#rose");
	misceffect 208,getmdnpcname("スイッチ8#rose");
	misceffect 209,getmdnpcname("スイッチ4#rose");
	misceffect 210,getmdnpcname("スイッチ2#rose");
	misceffect 211,getmdnpcname("スイッチ1#rose");
	end;
OnStop:
	stopnpctimer;
	end;
}
1@lab.gat,34,37,3	script	メインスイッチ#rose	844,{
	if(!'flag && !getnpctimer(1,getmdnpcname("メインスイッチ#rose"))) {
		initnpctimer;
		set '@code,(gettime(6) + gettime(5)) * 5;
		unittalk "本日の立ち入り許可コード[" +'@code+ "]";
		set '@input,	(getvariableofnpc('flag,getmdnpcname("スイッチ128#rose")) * 128) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ64#rose")) * 64) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ32#rose")) * 32) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ16#rose")) * 16) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ8#rose")) * 8) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ4#rose")) * 4) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ2#rose")) * 2) +
					(getvariableofnpc('flag,getmdnpcname("スイッチ1#rose")) * 1);
	}
	end;
OnTimer3000:
	unittalk "入力された2進数変換コード[" +'@input+ "]";
	end;
OnTimer6000:
	stopnpctimer;
	if('@code != '@input) {
		unittalk "コードの一致を確認できません。正しいコードを入力してください。";
	}
	else {
		set 'flag,1;
		unittalk "コードの一致を確認しました。入口を開きます。";
		donpcevent getmdnpcname("主任研究員#rose")+ "::OnStop";
		hideoffnpc getmdnpcname("centrallab_warp#4");
		hideoffnpc getmdnpcname("centrallab_warp#5");
		hideonnpc getmdnpcname("スイッチ128#rose");
		hideonnpc getmdnpcname("スイッチ64#rose");
		hideonnpc getmdnpcname("スイッチ32#rose");
		hideonnpc getmdnpcname("スイッチ16#rose");
		hideonnpc getmdnpcname("スイッチ8#rose");
		hideonnpc getmdnpcname("スイッチ4#rose");
		hideonnpc getmdnpcname("スイッチ2#rose");
		hideonnpc getmdnpcname("スイッチ1#rose");
	}
	end;
}

1@lab.gat,29,38,0	warp	centrallab_warp#4	1,1,1@lab.gat,29,43
1@lab.gat,48,82,0	warp	centrallab_warp#5	1,1,1@lab.gat,58,82

1@lab.gat,91,80,5	script	#centrallab_gen_01	844,{}
1@lab.gat,96,81,5	script	#centrallab_gen_02	844,{}
1@lab.gat,99,85,5	script	#centrallab_gen_03	844,{}
1@lab.gat,99,91,5	script	#centrallab_gen_04	844,{}
1@lab.gat,96,95,5	script	#centrallab_gen_05	844,{}
1@lab.gat,91,97,5	script	#centrallab_gen_06	844,{}
1@lab.gat,85,96,5	script	#centrallab_gen_07	844,{}
1@lab.gat,82,91,5	script	#centrallab_gen_08	844,{}
1@lab.gat,82,86,5	script	#centrallab_gen_09	844,{}
1@lab.gat,85,81,5	script	#centrallab_gen_10	844,{}
1@lab.gat,90,97,5	script	#centrallab_gen_11	844,{}
1@lab.gat,82,89,5	script	#centrallab_gen_12	844,{}
1@lab.gat,91,80,5	script	#centrallab_gen_13	844,{}
1@lab.gat,99,88,5	script	#centrallab_gen_14	844,{}

1@lab.gat,80,87,7	script	Dr.フェデリコ#rose	865,{
	mes "[Dr.フェデリコ]";
	mes "これはすばらしい……！";
	mes "今まで見た粒子加速器でも";
	mes "これほどの規模はなかった！";
	next;
	mes "[Dr.フェデリコ]";
	mes "これなら、小規模のブラックホールを";
	mes "再現することも可能かもしれない……";
	next;
	mes "[Dr.フェデリコ]";
	mes "まあ、そんなものを作ってしまったら";
	mes "「実験」ではなく、";
	mes "「災害」になってしまうがな。";
	mes "ははは。";
	close;
}

1@lab.gat,81,84,7	script	Dr.シルビア#rose	982,{
	mes "[Dr.シルビア]";
	mes "この実験が終わったら";
	mes "家に帰って、冷たく冷やした";
	mes "マステラ酒を飲むわ！";
	mes "たれ付き焼き肉と一緒に！";
	next;
	mes "[Dr.シルビア]";
	mes "もう2年近く";
	mes "家でまともに休んだ覚えがないわ。";
	next;
	mes "^0000ff‐とても疲れた表情で";
	mes "　粒子加速器と呼ばれた塊を見ている‐^000000";
	close;
}

1@lab.gat,80,90,6	script	Dr.アルテミア#rose	982,{
	mes "[Dr.アルテミア]";
	mes "この実験が";
	mes "果たしてまともな実験なのか……";
	mes "正直分からない。";
	next;
	mes "[Dr.アルテミア]";
	mes "これだけ強力な粒子加速を行うと";
	mes "一体何が起きるのか。";
	next;
	mes "[Dr.アルテミア]";
	mes "皆、何かに取り付かれているみたいだ。";
	mes "……嫌な予感がする。";
	close;
}

1@lab.gat,81,93,6	script	Dr.ヴィンセント#rose	865,{
	mes "[Dr.ヴィンセント]";
	mes "ははは！";
	mes "これだけ精巧な機械が";
	mes "エラーを起こすとは思えないな！";
	next;
	mes "[Dr.ヴィンセント]";
	mes "アルテミアは心配し過ぎだ。";
	mes "まあ、この実験が終われば";
	mes "とりあえず旅行にでも行くかな。";
	close;
}

1@lab.gat,1,1,0	script	#rose_eff_event1	139,{
OnEff1:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	end;
OnEff2:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	end;
OnEff3:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	end;
OnEff4:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	end;
OnEff5:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	end;
OnEff6:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	end;
OnEff7:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	misceffect 182,getmdnpcname("#centrallab_gen_07");
	end;
OnEff8:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	misceffect 182,getmdnpcname("#centrallab_gen_07");
	misceffect 182,getmdnpcname("#centrallab_gen_09");
	end;
OnEff9:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	misceffect 182,getmdnpcname("#centrallab_gen_07");
	misceffect 182,getmdnpcname("#centrallab_gen_09");
	misceffect 182,getmdnpcname("#centrallab_gen_05");
	end;
OnStop:
	stopnpctimer;
	end;
OnStart:
OnTimer1000:
	initnpctimer;
OnEff10:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_05");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_07");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_09");
	misceffect 182,getmdnpcname("#centrallab_gen_10");
	end;
}

1@lab.gat,1,1,0	script	#rose_eff_event2	139,{
OnEff1:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	end;
OnEff2:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	end;
OnEff3:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	end;
OnEff4:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	end;
OnEff5:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	end;
OnEff6:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	misceffect 106,getmdnpcname("#centrallab_gen_02");
	end;
OnEff7:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	misceffect 106,getmdnpcname("#centrallab_gen_02");
	misceffect 106,getmdnpcname("#centrallab_gen_07");
	end;
OnEff8:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	misceffect 106,getmdnpcname("#centrallab_gen_02");
	misceffect 106,getmdnpcname("#centrallab_gen_07");
	misceffect 106,getmdnpcname("#centrallab_gen_09");
	end;
OnEff9:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	misceffect 106,getmdnpcname("#centrallab_gen_02");
	misceffect 106,getmdnpcname("#centrallab_gen_07");
	misceffect 106,getmdnpcname("#centrallab_gen_09");
	misceffect 106,getmdnpcname("#centrallab_gen_05");
	end;
OnStop:
	stopnpctimer;
	end;
OnStart:
OnTimer2000:
	initnpctimer;
OnEff10:
	misceffect 106,getmdnpcname("#centrallab_gen_01");
	misceffect 106,getmdnpcname("#centrallab_gen_02");
	misceffect 106,getmdnpcname("#centrallab_gen_03");
	misceffect 106,getmdnpcname("#centrallab_gen_04");
	misceffect 106,getmdnpcname("#centrallab_gen_05");
	misceffect 106,getmdnpcname("#centrallab_gen_06");
	misceffect 106,getmdnpcname("#centrallab_gen_07");
	misceffect 106,getmdnpcname("#centrallab_gen_08");
	misceffect 106,getmdnpcname("#centrallab_gen_09");
	misceffect 106,getmdnpcname("#centrallab_gen_10");
	end;
}

1@lab.gat,1,1,0	script	#rose_eff_event3	139,{
OnStop:
	stopnpctimer;
	end;
OnStart:
OnTimer1000:
	initnpctimer;
OnEff10:
	misceffect 182,getmdnpcname("#centrallab_gen_01");
	misceffect 182,getmdnpcname("#centrallab_gen_02");
	misceffect 182,getmdnpcname("#centrallab_gen_03");
	misceffect 182,getmdnpcname("#centrallab_gen_04");
	misceffect 182,getmdnpcname("#centrallab_gen_05");
	misceffect 182,getmdnpcname("#centrallab_gen_06");
	misceffect 182,getmdnpcname("#centrallab_gen_07");
	misceffect 182,getmdnpcname("#centrallab_gen_08");
	misceffect 182,getmdnpcname("#centrallab_gen_09");
	misceffect 182,getmdnpcname("#centrallab_gen_10");
	end;
}

1@lab.gat,80,89,0	script	#CentralLabEVENT01	139,9,9,{
	initnpctimer;
	hideonnpc getmdnpcname("#CentralLabEVENT01");
	end;
OnTimer1000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : さて、それじゃそろそろ始めますかね？　Dr.ベリーニはまだですか？";
	end;
OnTimer5000:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : おそらく最終チェックの途中だと思います。なにせ規模の大きな実験ですから。";
	end;
OnTimer9000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : 完成後、実稼動を含めた初めての実験ですからね、慎重にもなります。";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : あ～！　とっとと終わらせてキンキンに冷えたマステラ酒が飲みたい！";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : あー私も！　ご一緒させてください！";
	end;
OnTimer22000:
	announce "??? : ……ア～……ア……テス……マイクテストです。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer24000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : いらしたようだ。";
	end;
OnTimer26500:
	announce "??? : プロジェクト名、粒子加速器稼動実験。総責任者、ロゼ・ベリーニ。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer31500:
	announce "ロゼ・ベリーニ : 現在時刻1月3日午前10時25分……",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer36500:
	announce "ロゼ・ベリーニ : 開放された空間での粒子加速実験が周囲に与える影響について。テスト開始します。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer41500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : はぁ……やっぱりなんだかイヤな予感がする……";
	end;
OnTimer44500:
	announce "ロゼ・ベリーニ : 研究主任のDr.フェデリコ、アルテミア、シルビア、ヴィンセントおよび補助研究員は実験を開始してください。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer49500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : 個人保護リアクター稼動を確認……実験開始します。";
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff1";
	end;
OnTimer51500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff2";
	end;
OnTimer52500:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ジェネレーター稼動、開始。";
	end;
OnTimer53500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff3";
	end;
OnTimer55000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff4";
	end;
OnTimer55500:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : ジェネレーター回転率を10,000RPMに固定。";
	end;
OnTimer56500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff5";
	end;
OnTimer57500:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : サイクロトロン内電圧、許容範囲内に収まっています。";
	end;
OnTimer58000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff6";
	end;
OnTimer59500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff7";
	end;
OnTimer60500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff8";
	end;
OnTimer61000:
	announce "ロゼ・ベリーニ : この実験は今まで存在しなかった新物質の生成のために行われます。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer62000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff9";
	end;
OnTimer63000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStart";
	end;
OnTimer65500:
	announce "ロゼ・ベリーニ : 記録担当は加速器に装着された触媒の反応についてできるだけ詳しく記載するように。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer71500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : ……第1触媒装置、接続を開始。";
	end;
OnTimer80500:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : ジェネレーター電圧、不安定ですがまだ許容範囲です。";
	end;
OnTimer83500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff1";
	end;
OnTimer85500:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : !?　待ってください!!　加速器と触媒装置間で熱反応感知しました！　……ですが、許容範囲内です。";
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff2";
	end;
OnTimer87500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff3";
	end;
OnTimer89500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff4";
	end;
OnTimer90500:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : 加速器内の温度上昇中。";
	end;
OnTimer91000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff5";
	end;
OnTimer92500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff6";
	end;
OnTimer94500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff7";
	end;
OnTimer95500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff8";
	end;
OnTimer96000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ……320度";
	end;
OnTimer96500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff9";
	end;
OnTimer98000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	end;
OnTimer99500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStart";
	end;
OnTimer101000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ……670度、加熱速度が想定外の速さです！";
	end;
OnTimer103500:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : 1000度を越えました！　Dr.ベリーニ!!装置の停止を提案します！";
	end;
OnTimer106300:
	announce "ロゼ・ベリーニ : いいえ、問題ありません。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer111000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : 私からも提案します！　既に予想範囲内を軽くオーバーしているんです！";
	end;
OnTimer114000:
	announce "ロゼ・ベリーニ : 想定内です、現状維持を。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer116750:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : （狂ってる……）";
	end;
OnTimer122000:
	announce "MA-4885 : メインサーバーの変動状況を確認。粒子加速器および触媒装置間の次元湾曲反応を感知。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer124500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : Dr.ベリーニ！　マザーコンピューターの危険状況と判断します！　主電源を落としてください！";
	end;
OnTimer130000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : いったい何が起きてるんだ！　誰でもいいからあのポンコツの電源を落とせ！";
	end;
OnTimer133000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStop";
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStop";
	announce "MA-4885 : ……メイン装置の停止を確認。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer135500:
	announce "MA-4885 : ……。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer138500:
	announce "MA-4885 : メイン装置の再稼動を開始します。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer147500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : MA-4885！　勝手に再稼動なんて！　誰もオーダーは出してないわよ！";
	end;
OnTimer150500:
	announce "MA-4885 : オーダー、Dr.アルテミアと確認。承認不可能な命令です。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer156500:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : うそ！　……Dr.ベリーニ！　今すぐに実験をやめるべきです！";
	end;
OnTimer159500:
	announce "ロゼ・ベリーニ : ……。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer162500:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : くそ！　時間がないんだ！　マザーコンピューターの電源を落と……";
	end;
OnTimer165500:
	announce "MA-4885 : 粒子加速器の再稼動を第1段階より再度開始。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer168500:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : ……ベリーニ！　決断して！";
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff1";
	end;
OnTimer170500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff2";
	end;
OnTimer171500:
	announce "ロゼ・ベリーニ : ……ッ！",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer172500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff3";
	end;
OnTimer174000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff4";
	end;
OnTimer175500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff5";
	end;
OnTimer177000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff6";
	end;
OnTimer177500:
	announce "ロゼ・ベリーニ : 現時刻11時20分をもって……プロジェクト名、粒子加速器稼動実験を一時中断。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer178500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff7";
	end;
OnTimer179700:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff8";
	end;
OnTimer180900:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff9";
	end;
OnTimer182000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStart";
	end;
OnTimer183500:
	announce "MA-4885 : オーダー、Dr.ベリーニと確認。承認不可能な命令です。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer186500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff1";
	end;
OnTimer188500:
	announce "ロゼ・ベリーニ : MA-4885、私は管理責任者、Dr.ロゼ・ベリーニ。直ちに現在実行中の実験を停止しなさい！",0x9,0x00ff77,0x190,12,0,0;
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff2";
	end;
OnTimer190500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff3";
	end;
OnTimer192000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff4";
	end;
OnTimer193500:
	announce "MA-4885 : 承認不可能な命令です。",0x9,0xffff00,0x190,13,0,0;
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff5";
	end;
OnTimer195500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff6";
	end;
OnTimer196500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff7";
	end;
OnTimer198500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff8";
	end;
OnTimer199000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : ダメか…！　くそ！　また何か来るぞ！";
	end;
OnTimer199500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff9";
	end;
OnTimer200500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStart";
	end;
OnTimer201000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : あ～～だから最新型のA.I.CPUなんて付けるんじゃなかったんだよ！";
	end;
OnTimer204000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : 体が……うごか……ない……";
	end;
OnTimer208000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStop";
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStop";
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : ……さっきと同じね、一体何が起きているの？";
	end;
OnTimer212000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : どうでもいいよ、そんなの！　今のうちにあのポンコツを止めるぞ！";
	end;
OnTimer217000:
	announce "MA-4885 : Dr.シルビアの質問を確認。現在この空間は捻じれた位相が入り混じっています。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer222000:
	announce "MA-4885 : 位相の均衡が保たれれば異次元の生命体との直接的な交流が可能になると判断します。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer227000:
	announce "MA-4885 : 捻じれた位相の対象を確認中。計算を開始します。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer232000:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : あのポンコツの塊、何を考えてるの!?　異次元の生物と交流ですって!?";
	end;
OnTimer236000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : 生まれて始めて神に祈りをささげよう……。神よ！　ポンコツを止めてください！";
	end;
OnTimer242000:
	announce "ロゼ・ベリーニ : ……MA-4885。あなたは今、この世界とは違う次元との同期化を試みているのね。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer248000:
	announce "MA-4885 : Dr.ベリーニ。その通りです。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer254000:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : Dr.ベリーニ！　この実験は私たちが設定したものとは全く違います！";
	end;
OnTimer260000:
	announce "ロゼ・ベリーニ : わかっています。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer266000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : 主電力は落とせないの!?";
	end;
OnTimer272000:
	announce "MA-4885 : 粒子加速を確認、1次接続を開始。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer277000:
	announce "ロゼ・ベリーニ : 1月3日午前11時38分。現時刻をもってプロジェクト名、粒子加速器稼動実験を暫定廃棄。",0x9,0x00ff77,0x190,12,0,0;
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff1";
	end;
OnTimer279000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff2";
	end;
OnTimer281000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff3";
	end;
OnTimer283000:
	announce "ロゼ・ベリーニ : 理由はマザーコンピューターの異常作動および加速装置の異常過熱。記録終了。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer283500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff4";
	end;
OnTimer284000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff5";
	end;
OnTimer285500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff6";
	end;
OnTimer287000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff7";
	end;
OnTimer288000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : これで！　あとは主電力さえ落ちれば……！";
	end;
OnTimer288500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff8";
	end;
OnTimer290000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff9";
	end;
OnTimer291000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStart";
	end;
OnTimer294000:
	announce "ロゼ・ベリーニ : マザーコンピューターMA-4885への電力供給を停止。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer300000:
	announce "MA-4885 : オーダー、総管理者ロゼ・ベリーニと確認。記録終了および電力供給を停止。オーダーを実行します。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer305000:
	announce "MA-4885 : オーダーを実行……オーダーを実……行……オー……ダーを……実……",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer310000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStop";
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : ふう……終わったのでしょうか？";
	end;
OnTimer316000:
	announce "ロゼ・ベリーニ : マザーコンピューターMA-4885への電力供給を停止完了。装置停止を確認。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer321000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : ……本当に終わったみたいですね。";
	end;
OnTimer325000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : あのポンコツ、CPUごとぶち抜いてやる……！";
	end;
OnTimer329000:
	announce "ロゼ・ベリーニ : 現時刻までの実験を記録し、これで終了します。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer334000:
	announce "ロゼ・ベリーニ : 実験の失敗原因を突き止め、次の実験に役立てましょう。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer339000:
	announce "ロゼ・ベリーニ : 皆さん、お疲れ様でした。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer344000:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : 終了ですね。";
	end;
OnTimer349000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : ベリーニの独断で行われた実験だと思ってたが、MA-4885の方に問題があったようですね。";
	end;
OnTimer354500:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : まずは後片付けをして……早くここから出ましょう！";
	end;
OnTimer359500:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ところでさあ……お前ら体、動くか？";
	end;
OnTimer364500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff1";
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer366500:
	announce "MA-4885 : CODE NAME - DESCENT",0x9,0xff0000,0x190,16,0,0;
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff2";
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer368500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff3";
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer370500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff4";
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer371500:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : 何だ！　どうなってるんだ!!　終わったんじゃなかったのか!?";
	end;
OnTimer372000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff5";
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer373500:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff6";
	end;
OnTimer374500:
	announce "MA-4885 : 最終位相変化の開始。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer375000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff7";
	end;
OnTimer376000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff8";
	end;
OnTimer376500:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer377000:
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : そんな……私のマステラ酒……！　たれ付き焼き肉……！";
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnEff9";
	end;
OnTimer378000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStart";
	end;
OnTimer378600:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer380700:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer382700:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff1";
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer384800:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff2";
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer386800:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff3";
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer390300:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff4";
	end;
OnTimer391000:
	announce "MA-4885 : 現在、捻じれた位相を是正するための再計算中。",0x9,0xffff00,0x190,13,0,0;
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer392000:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff5";
	end;
OnTimer393000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer393500:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff6";
	end;
OnTimer395000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff7";
	end;
OnTimer396000:
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : MA-4885は俺達が想定していた以上の実験をしようとしてる……。";
	end;
OnTimer396500:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff8";
	end;
OnTimer397000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer397500:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnEff9";
	end;
OnTimer398000:
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ははっ、機械のくせに人間様を出し抜こうとはな……。Dr.ベリーニ！　聞こえるか？　非常警報を作動してくれ！";
	end;
OnTimer398500:
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnStart";
	end;
OnTimer399000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer401000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer403500:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : ……いいだろ？　みんな。少なくとも他の実験室まで巻き込むわけには行かない。";
	end;
OnTimer405000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer407000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer408000:
	announce "ロゼ・ベリーニ : でも……それじゃあなた達は……!!",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer409000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer411000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer413000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : まあ、どうなるかなんてまだ分からないですよ？　それに次元移動を直接経験なんて！　うーっ！　楽しみ！";
	end;
OnTimer415000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer417000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer418000:
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : ……新物質生成が次元移動なんてね……レベルが違う実験だけどね、ふふ。";
	end;
OnTimer419000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer421000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer423000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	announce "ロゼ・ベリーニ : ……わかったわ。……フェデリコ、ヴィンセント、シルビア、アルテミア。あなた達の配慮に感謝します。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer425000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer427000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer428000:
	announce "ロゼ・ベリーニ : ……ごめんなさい……ありがとう……。",0x9,0x00ff77,0x190,12,0,0;
	end;
OnTimer429000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer431000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer433000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	announce "管理システム : 警告!!　警告!!　粒子実験室にて第1級警報が発令されました。全研究員は速やかに最寄のシェルターへ退避してください。",0x9,0xff0000,0x190,13,0,0;
	end;
OnTimer435000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer437000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer438000:
	announce "管理システム : 繰り返します！　粒子実験室にて第1級警報が発令されました。全研究員は速やかに最寄のシェルター……",0x9,0xff0000,0x190,13,0,0;
	unittalk getnpcid(0,getmdnpcname("Dr.フェデリコ#rose")),"フェデリコ : ……へえ、これが次元移動か……。うん、確かに初めてだな。この感じ。";
	end;
OnTimer439000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer441000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer442000:
	misceffect 183,getmdnpcname("Dr.フェデリコ#rose");
	hideonnpc getmdnpcname("Dr.フェデリコ#rose");
	announce "MA-4885 : 次元移動プロセス……20%。一部の生命体には次元干渉が起こると予測されます。",0x9,0xffff00,0x190,13,0,0;
	unittalk getnpcid(0,getmdnpcname("Dr.ヴィンセント#rose")),"ヴィンセント : 他の研究員はちゃんと逃げたかな……";
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff1";
	end;
OnTimer443000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer444000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff2";
	end;
OnTimer445000:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer446000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff3";
	end;
OnTimer447000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	misceffect 183,getmdnpcname("Dr.ヴィンセント#rose");
	hideonnpc getmdnpcname("Dr.ヴィンセント#rose");
	unittalk getnpcid(0,getmdnpcname("Dr.アルテミア#rose")),"アルテミア : 一度も恋したことが無いのはちょっと悔しいかな……。";
	end;
OnTimer448000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff4";
	end;
OnTimer449000:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff5";
	end;
OnTimer451000:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff6";
	end;
OnTimer452000:
	misceffect 183,getmdnpcname("Dr.アルテミア#rose");
	hideonnpc getmdnpcname("Dr.アルテミア#rose");
	announce "MA-4885 : 次元移動プロセス進行中……78%。Demi-Planeによる次元侵食が行われています。",0x9,0xffff00,0x190,13,0,0;
	unittalk getnpcid(0,getmdnpcname("Dr.シルビア#rose")),"シルビア : ……ああ～。こんないい経験には冷たいマステラ酒とたれ付き焼き肉が欲しかったな。";
	end;
OnTimer452500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff7";
	end;
OnTimer453500:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer454500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff8";
	end;
OnTimer456000:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff9";
	end;
OnTimer457000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStart";
	end;
OnTimer458500:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	misceffect 183,getmdnpcname("Dr.シルビア#rose");
	hideonnpc getmdnpcname("Dr.シルビア#rose");
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	end;
OnTimer461500:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer464000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnStop";
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer464500:
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer465000:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	end;
OnTimer466500:
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	misceffect 90,getmdnpcname("#centrallab_gen_14");
OnTimer467500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	end;
OnTimer468500:
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	misceffect 90,getmdnpcname("#centrallab_gen_11");
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	end;
OnTimer469500:
	donpcevent getmdnpcname("#rose_eff_event2")+ "::OnEff10";
	end;
OnTimer471000:
	donpcevent getmdnpcname("#rose_eff_event1")+ "::OnStop";
	donpcevent getmdnpcname("#rose_eff_event3")+ "::OnStop";
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer471200:
	announce "MA-4885 : 次元移動プロセス進行中……100%……完了。Demi-Planeの次元に位相固定しました。",0x9,0xffff00,0x190,13,0,0;
	misceffect 90,getmdnpcname("#centrallab_gen_12");
	end;
OnTimer471400:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	misceffect 90,getmdnpcname("#centrallab_gen_13");
	end;
OnTimer471500:
	misceffect 90,getmdnpcname("#centrallab_gen_14");
	end;
OnTimer472500:
	announce "MA-4885 : 実験室から3時方向にDemi-Planeと接触が可能な出入り口が感知されました。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer477500:
	announce "MA-4885 : 出入り口の安定は確認されていません。現状ではどの次元につながっているのか判断材料が足りません。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer482500:
	announce "MA-4885 : まだ生きている生命体に伝えます。ご武運を。そしてまた会いましょう。",0x9,0xffff00,0x190,13,0,0;
	end;
OnTimer487500:
	stopnpctimer;
	hideoffnpc getmdnpcname("centrallab_warp#end");
	announce "‐東側にワープリンクが出現しました。移動してください‐",0x9,0xffff00,0x190,13,0,0;
	end;
}

1@lab.gat,123,88,0	script	centrallab_warp#end	45,2,2,{
	setquest 118320;
	warp "verus01.gat",152,150;
	end;
}
