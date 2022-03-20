//= Auriga Script ==============================================================
// Ragnarok Online Tower of Morocc Script	by refis
//==============================================================================

dali02.gat,134,119,5	script	歴史学者セフィト#tnm01	729,{
	mes "[歴史学者セフィト]";
	mes "こんばんは。";
	mes "私はこの先の塔で入手できる";
	mes "武器を研究しています！";
	mes "　";
	mes "‐^ff0000" +TNM_REFINE+ "回^000000、精錬可能‐";
	next;
	switch(select("精錬をする","話を聞く","会話をやめる")) {
	case 1:
		break;
	case 2:
		mes "[歴史学者セフィト]";
		mes "この先にある";
		mes "魔神の塔で入手できる武器は";
		mes "精錬されると";
		mes "その能力を増していくんです！";
		mes "素敵～～！";
		next;
		mes "[歴史学者セフィト]";
		mes "限界まで能力を引き出せば";
		mes "モロクなんてきっとイチコロです！";
		next;
		mes "[歴史学者セフィト]";
		mes "もしも武器を入手したら";
		mes "ぜひ私に精錬をさせてください！";
		mes "武器の持つ力を引き出す事に";
		mes "とても興味があります！";
		next;
		mes "‐^ff0000魔神の塔の頂上部まで";
		mes "　クリアする度に3回";
		mes "　ここで精錬をする事が可能です。";
		mes "　1000回分まで、貯める事が出来ます^000000‐";
		close;
	case 3:
		mes "[歴史学者セフィト]";
		mes "魔神の塔で武器を手に入れたら";
		mes "ぜひ私の所に来てください！";
		close;
	}
	mes "[歴史学者セフィト]";
	mes "精錬ですね！";
	mes "かしこまりました！";
	mes "何を精錬しますか？";
	next;
	switch(select(	(getequipid(3)!=0? "^nItemID^" +getequipid(3): "^999999左手-[装着していない]^000000"),
					(getequipid(4)!=0? "^nItemID^" +getequipid(4): "^999999右手-[装着していない]^000000"))) {
	case 1:
		set '@i,3;
		break;
	case 2:
		set '@i,4;
		break;
	}
	switch(getequipid('@i)) {
	case 2029:
	case 18131:
	case 21017:
	case 28009:
	case 28108:
	case 28707:
		break;
	case 0:
		mes "[歴史学者セフィト]";
		mes "あれ？　何も装備してないですよ。";
		mes "手を叩いて欲しいんですか？";
		close;
	default:
		mes "[歴史学者セフィト]";
		mes "あれっ。装備している武器が";
		mes "魔神の塔で入手できるものでは";
		mes "無いようですね。";
		mes "私が精錬出来るのは";
		mes "魔神の塔で入手可能な武器だけです！";
		mes "もう一度、確認してくださ～い。";
		close;
	}
	if(TNM_REFINE == 0) {
		mes "‐^ff0000精錬をする権利がありません。";
		mes "　魔神の塔の頂上部まで";
		mes "　クリアをする度に3回";
		mes "　ここで精錬をする事が可能です^000000‐";
		close;
	}
	set '@refine,getequiprefinerycnt('@i);
	if('@refine < 5 && TNM_REFINE >= 5 - '@refine) {	// 精錬値が4以下で+5までの精錬権があるとき
		mes "[歴史学者セフィト]";
		mes "おおっ！　この武器はまだ";
		mes "安全に精錬が可能ですね！";
		mes "もしよかったら";
		mes "^ff0000+5まで一気に精錬する^000000事も出来ますが";
		mes "どうしますか？";
		next;
		switch(select("1回だけ精錬","一気に精錬","やめる")) {
		case 1:
			break;
		case 2:
			set '@num,5 - '@refine;
			mes "[歴史学者セフィト]";
			mes "あなたの武器の精錬値は^ff0000+" +'@refine+ "^000000なので";
			mes "^ff0000" +'@num+ "回^000000、一気に精錬しちゃいますね！";
			mes "よろしいですか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[歴史学者セフィト]";
				mes "そうですか！";
				mes "わかりました～。";
				close;
			}
			for(set '@j,0;'@j<'@num;set '@j,'@j+1)
				successrefitem '@i;
			set TNM_REFINE,TNM_REFINE-'@num;
			mes "[歴史学者セフィト]";
			mes "そーれ！";
			mes "カン！ カン！ カン!!";
			mes "　";
			mes "はい！　出来上がりました！";
			mes "どうぞ～。";
			close;
		case 3:
			mes "[歴史学者セフィト]";
			mes "そうですか！";
			mes "わかりました～。";
			close;
		}
	}
	if('@refine >= 5) {
		mes "[歴史学者セフィト]";
		mes "おおっ！　この武器は既にかなり";
		mes "精錬をしてますね。";
		mes "これから先は";
		mes "武器が壊れるかもしれません。";
		mes "壊れると2度と使えなくなりますが";
		mes "それでも大丈夫ですか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[歴史学者セフィト]";
			mes "そうですか！";
			mes "わかりました～。";
			close;
		}
	}
	set TNM_REFINE,TNM_REFINE-1;
	mes "[歴史学者セフィト]";
	mes "そーれ！";
	mes "カン！ カン！ カン!!";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@i;
		next;
		emotion 21;
		mes "[歴史学者セフィト]";
		mes "さあ、できましたよ！";
		mes "良い物ができましたねっ！";
		close;
	}
	else {
		failedrefitem '@i;
		next;
		emotion 23;
		mes "[歴史学者セフィト]";
		mes "クホホッ……";
		mes "失敗してしまいました。";
		mes "　";
		mes "ご、ごめんなさい……。";
		mes "次は頑張ります！";
		close;
	}
OnInit:
	waitingroom "魔神武器【精錬】",0;
	end;
}

dali02.gat,141,120,3	script	魔神の塔 次元移動機	10007,{
	if(checkquest(7577)) {
		if(checkquest(7577) & 0x2 && checkquest(118909) & 0x2) {
			mes "‐再調査が可能になりました‐";
			delquest 7577;
			delquest 118909;
			close;
		}
		mes "‐この先は入場してから1回目の";
		mes "　^ff0000午前5時以降^000000に進行可能です。";
		mes "　但し、最後の入場をしてから";
		mes "　^ff00001時間^000000経過するまでは";
		mes "　進行できませんのでご注意ください‐";
		close;
	}
	mes "[魔学者アティ]";
	mes "それが次元移動機だ。";
	mes "出発するか？";
	next;
	if(select("入る","やめておく") == 2) {
		mes "[魔学者アティ]";
		mes "そうか。";
		mes "まあ、好きにするがいい。";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[魔学者アティ]";
		mes "魔神の塔の調査は";
		mes "パーティーでないと許可できない。";
		mes "まずは一緒に調査をする人を集めて";
		mes "パーティーを結成してくれ。";
		close;
	}
	switch(mdenter("Tower Of Morocc")) {
	case 0:	// エラーなし
		delquest 114800;
		delquest 114805;
		delquest 114810;
		set TNM1_QUE,0;
		setquest 7577;
		setquest 118909;
		announce "メモリアルダンジョン[Tower Of Morocc] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99;
		donpcevent getmdnpcname("TNMControl1")+ "::OnStart";
		//warp "1@tnm1.gat",50,104;
		end;
	case 1:	// パーティー未加入
	case 2:	// ダンジョン未作成
	default:	// その他エラー
		mes "[歴史学者セフィト]";
		mes "まだ次元移動機を";
		mes "作動させてないようですね。";
		next;
		mes "[歴史学者セフィト]";
		mes "調査隊リーダーが";
		mes "魔学者アティに話しかけて";
		mes "次元移動機を";
		mes "作動してもらってください。";
		close;
	}
}

dali02.gat,137,121,3	script	魔学者アティ#tnm02	620,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[魔学者アティ]";
		mes "調査隊か？";
		mes "魔神の塔は一人で行けるほど甘くない。";
		mes "まずはリーダーと話させてくれ。";
		close;
	}
	if(checkquest(7577)) {
		if(getonlinepartymember() < 1) {
			mes "[魔学者アティ]";
			mes "調査志願者か？";
			mes "それならまずはパーティーを";
			mes "結成してくれ。";
			close;
		}
		if(checkquest(7577) & 0x2 && checkquest(118909) & 0x2) {
			mes "‐再調査が可能になりました‐";
			delquest 7577;
			delquest 118909;
			close;
		}
		mes "‐この先は入場してから1回目の";
		mes "　^ff0000午前5時以降^000000に進行可能です。";
		mes "　但し、最後の入場をしてから";
		mes "　^ff00001時間^000000経過するまでは";
		mes "　進行できませんのでご注意ください‐";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[魔学者アティ]";
		mes "魔神の塔の調査は";
		mes "パーティーでないと許可できない。";
		mes "まずは一緒に調査をする人を集めて";
		mes "パーティーを結成してくれ。";
		close;
	}
	mes "[魔学者アティ]";
	mes "ここにある次元移動機は";
	mes "魔神の塔という所に繋がっている。";
	mes "我々はその魔神の塔を";
	mes "研究しているわけだが";
	mes "中にいるモンスターのせいで";
	mes "思うように調査ははかどっていない。";
	next;
	mes "[魔学者アティ]";
	mes "そこでこうして広く希望者を募って";
	mes "魔神の塔の様子を";
	mes "調べてきて貰っている。";
	mes "君ももし行くのであれば";
	mes "次元移動機を作動させるがいいかな？";
	next;
	if(select("調査に向かう","やめる") == 2) {
		mes "[魔学者アティ]";
		mes "そうか。";
		mes "まあ、好きにしな。";
		close;
	}
	mdcreate "Tower Of Morocc";
	mes "[魔学者アティ]";
	mes "次元移動機を起動したぞ。";
	mes "通路が開いたら";
	mes "次元移動機を調べてみろ。";
	close;
OnInit:
	waitingroom "魔神の塔",0;
	end;
}

1@tnm1.gat,0,0,0	script	TNMControl1	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	donpcevent getmdnpcname("副隊長ハイム#heim0")+ "::OnStart";
	hideonnpc getmdnpcname("副隊長ハイム#heim");
	hideonnpc getmdnpcname("衛生兵ペイマー#feima");
	for(set '@i,1;'@i<=7;set '@i,'@i+1)
		hideonnpc getmdnpcname("負傷兵#" +'@i);
	hideonnpc getmdnpcname("ルシル#tnm01");
	hideonnpc getmdnpcname("タナトス#tnm01");
	hideonnpc getmdnpcname("アサシン・ヒュー#tnm01");
	hideonnpc getmdnpcname("アサシン・リュー#tnm01");
	hideonnpc getmdnpcname("アサシン・デュー#tnm01");
	hideonnpc getmdnpcname("アサシン・ヒュー#hui02");
	hideonnpc getmdnpcname("箱#tnmtop");
	hideonnpc getmdnpcname("ルシル#tnm04");
	for(set '@i,1;'@i<=8;set '@i,'@i+1)
		hideonnpc getmdnpcname("#tnmバリケード" +'@i);
	areasetcell getmdmapname("1@tnm2.gat"),108,110,112,113,0;
	hideonnpc getmdnpcname("#tnm3gate01");
	hideonnpc getmdnpcname("領主の娘#tnm02");
	hideonnpc getmdnpcname("領主の娘#tnm03");
	hideonnpc getmdnpcname("#tnm3gate02");
	hideonnpc getmdnpcname("#tnm3gate03");
	hideonnpc getmdnpcname("箱#tnmbosang");
	hideonnpc getmdnpcname("領主の娘#tnm04");
	hideonnpc getmdnpcname("ロキ#tnmloki02");
	hideonnpc getmdnpcname("ロキの思念#hidden_loki");
	hideonnpc getmdnpcname("ロキ#tnmloki03");
	end;
}

1@tnm1.gat,57,112,5	script	副隊長ハイム#heim0	691,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[副隊長ハイム]";
		mes "君は？";
		mes "見たところ、私の隊の兵士では";
		mes "ないようだが……。";
		close;
	}
	stopnpctimer;
	mes "[副隊長ハイム]";
	mes "現在の戦況はどうなっている？";
	unittalk "副隊長ハイム : 現在の戦況はどうなっている？";
	next;
	mes "[偵察兵]";
	mes "次の階さえ突破すれば最上階ですが、";
	mes "多数の魔族がいます。";
	donpcevent getmdnpcname("偵察兵#tnm01")+ "::OnTalk1";
	next;
	mes "[偵察兵]";
	mes "この人員での突破は";
	mes "不可能だと思われます。";
	emotion 19,getmdnpcname("偵察兵#tnm01");
	donpcevent getmdnpcname("偵察兵#tnm01")+ "::OnTalk2";
	next;
	mes "[副隊長ハイム]";
	mes "現在残っている戦力は？";
	mes "援軍はいつになったら到着する！";
	unittalk "副隊長ハイム : 現在残っている戦力は？　援軍はいつになったら到着する！";
	emotion 9,getmdnpcname("副隊長ハイム#heim0");
	next;
	mes "[補佐官]";
	mes "……戦力とは言えない人数です。";
	emotion 9,getmdnpcname("補佐官#tnm02");
	donpcevent getmdnpcname("補佐官#tnm02")+ "::OnTalk1";
	next;
	mes "[補佐官]";
	mes "唯一の救いは、";
	mes "なぜか上の階にいる魔族たちが";
	mes "下に降りてこない";
	mes "ということです。";
	donpcevent getmdnpcname("補佐官#tnm02")+ "::OnTalk2";
	next;
	mes "[副隊長ハイム]";
	mes "このままここに";
	mes "いるわけにもいかないが、";
	mes "進撃することもできない……";
	mes "ということか。";
	mes "魔族たちは何故動かないのだ？";
	unittalk "副隊長ハイム : このままここにいるわけにもいかないが、進撃することもできない……ということか。魔族たちは何故動かないのだ？";
	next;
//	mes "[副隊長ハイム]";
	mes "[偵察兵]";
	mes "上の階で何かが";
	mes "起きているようですが……。";
	donpcevent getmdnpcname("偵察兵#tnm01")+ "::OnTalk3";
	close2;
	donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("副隊長ハイム#heim0");
	end;
}

1@tnm1.gat,56,110,3	script	副隊長ハイム#heim	691,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		if(TNM1_QUE == 0) {
			mes "[副隊長ハイム]";
			mes "援軍なのか？";
			mes "ならどうしてそこで突っ立っている！";
			close;
		}
		else if(TNM1_QUE < 8) {
			mes "[副隊長ハイム]";
			mes "負傷兵の応急処置が最優先だ。";
			mes "衛生兵に協力してやってくれ。";
			close;
		}
		else {
			mes "[副隊長ハイム]";
			mes "幸い、戦死者はいないようだ。";
			mes "これ以上部下たちが傷つくのは";
			mes "耐えられない。";
			close;
		}
	}
	if(TNM1_QUE == 0) {
		stopnpctimer;
		mes "[副隊長ハイム]";
		mes "援軍なのか？";
		mes "ならどうしてそこで突っ立っている！";
		unittalk "副隊長ハイム : 援軍なのか？　ならどうしてそこで突っ立っている！";
		next;
		hideoffnpc getmdnpcname("衛生兵ペイマー#feima");
		mes "[衛生兵ペイマー]";
		mes "うわ～ん！";
		mes "副隊長、助けてくださ～い!!";
		mes "私一人じゃ手が回りませ～ん！";
		donpcevent getmdnpcname("衛生兵ペイマー#feima")+ "::OnTalk1";
		next;
		mes "[副隊長ハイム]";
		mes "……あの声が聞こえただろう？";
		unittalk "副隊長ハイム : ……あの声が聞こえただろう？";
		next;
		mes "[副隊長ハイム]";
		mes "まずは負傷兵の治療を頼む。";
		mes "ペイマーから治療箱を受け取り、";
		mes "それを使ってくれ。";
		unittalk "副隊長ハイム : まずは負傷兵の治療を頼む。ペイマーから治療箱を受け取り、それを使ってくれ。";
		next;
		mes "[衛生兵ペイマー]";
		mes "お手伝いしてくれる方は、";
		mes "こちらに来て";
		mes "治療箱を受け取ってくださ～い！";
		donpcevent getmdnpcname("衛生兵ペイマー#feima")+ "::OnTalk2";
		setpartyinmap TNM1_QUE,1;
		close;
	}
	else if(TNM1_QUE < 8) {
		mes "[副隊長ハイム]";
		mes "負傷兵の応急処置が最優先だ。";
		mes "衛生兵に協力してやってくれ。";
		close;
	}
	else {
		mes "[副隊長ハイム]";
		mes "幸い、戦死者はいないようだ。";
		mes "これ以上部下たちが傷つくのは";
		mes "耐えられない。";
		close;
	}
OnStart:
	initnpctimer;
	unittalk "副隊長ハイム : そこにいるのは誰だ？";
	hideonnpc getmdnpcname("副隊長ハイム#heim0");
	hideoffnpc getmdnpcname("副隊長ハイム#heim");
	end;
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("副隊長ハイム#heim");
	end;
OnTalk1:
	unittalk "副隊長ハイム : アサシンギルドの支援か！　よく来てくれた!!";
	end;
OnTalk2:
	unittalk "副隊長ハイム : 貴様……私を挑発しているのか？";
	end;
OnTalk3:
	unittalk "副隊長ハイム : どうしてその事を……確かに魔族たちは進行を止め、何かを待っている様子だ。";
	end;
OnTalk4:
	unittalk "副隊長ハイム : な……何をするつもりだ！　そんな少人数で乗り込んでも無駄死にするだけだぞ！";
	end;
OnTalk5:
	unittalk "副隊長ハイム : 何を考えているんだ彼らは……。何にせよ厳しい状況だ。君も彼らを援護してくれ。";
	end;
OnTalk6:
	unittalk "副隊長ハイム : 魔族を迎撃するだけでも、大きな力になるはずだ。頼むぞ。";
	end;
}

1@tnm1.gat,61,113,3	script	偵察兵#tnm01	997,{
	mes "[偵察兵]";
	mes "援軍なのか？";
	mes "状況が悪化していたから助かったよ。";
	mes "ここまで来てくれてありがとな。";
	close;
OnTalk1:
	unittalk "偵察兵 : 次の階さえ突破すれば最上階ですが、多数の魔族がいます。";
	end;
OnTalk2:
	unittalk "偵察兵 : この人員での突破は不可能だと思われます。";
	end;
OnTalk3:
	unittalk "偵察兵 : 上の階で何かが起きているようですが……。";
	end;
}

1@tnm1.gat,61,110,3	script	補佐官#tnm02	998,{
	mes "[補佐官]";
	mes "何百年も前の災いが再び起ころうと";
	mes "しているわけじゃないよな？";
	mes "なぜ急に魔族が現れたのか……。";
	close;
OnTalk1:
	unittalk "補佐官 : ……戦力とは言えない人数です。";
	end;
OnTalk2:
	unittalk "補佐官 : 唯一の救いは、なぜか上の階にいる魔族たちが下に降りてこないということです。";
	end;
}

1@tnm1.gat,47,109,3	script	衛生兵ペイマー#feima	696,{
	if(TNM1_QUE == 1) {
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[衛生兵ペイマー]";
			mes "今あなた方のリーダーさんと";
			mes "お話をしていますので";
			mes "ちょっと待ってくださいね～。";
			close;
		}
		mes "[衛生兵ペイマー]";
		mes "お手伝いしていただけるんですか？";
		mes "助かります～。";
		mes "治療箱で負傷兵のみなさんを";
		mes "治療してほしいのです。";
		next;
		if(select("治療を手伝う","治療をスキップする") == 2) {
			mes "‐あなたは治療箱を受け取り、";
			mes "　負傷兵への治療を行った‐";
			next;
			mes "[衛生兵ペイマー]";
			mes "ふう……。";
			mes "これでひとまず";
			mes "落ち着いたみたいです。";
			mes "ありがとうございます！";
			mes "助かりました～！";
			set 'flag,1;
			setpartyinmap TNM1_QUE,8;
			for(set '@i,1;'@i<=7;set '@i,'@i+1) {
				misceffect 6,getmdnpcname("負傷兵#" +'@i+ "_1");
				hideonnpc getmdnpcname("負傷兵#" +'@i+ "_1");
				hideoffnpc getmdnpcname("負傷兵#" +'@i);
				misceffect 6,getmdnpcname("負傷兵#" +'@i);
			}
			donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
			close;
		}
		mes "[衛生兵ペイマー]";
		mes "治療に使う治療箱を";
		mes "用意しておきますので、";
		mes "そちらの準備ができたら";
		mes "もう一度声をかけてください～。";
		setpartyinmap TNM1_QUE,2;
		close;
	}
	else if(TNM1_QUE >= 2 && TNM1_QUE < 9) {
		if(countitem(7641)) {
			mes "[衛生兵ペイマー]";
			mes "ごめんなさい、補給の都合で";
			mes "治療箱は一度に1個だけ";
			mes "支給しているんです～。";
			mes "使い終わったらもう一度";
			mes "受け取りに来てもらえますか？";
			close;
		}
		mes "[衛生兵ペイマー]";
		mes "この治療箱で、";
		mes "負傷兵のみなさんを";
		mes "治療してください。";
		mes "そんなに難しくないですよ。";
		mes "マニュアル通りに";
		mes "治療すれば大丈夫です！";
		next;
		mes "[衛生兵ペイマー]";
		mes "それと、補給の都合で";
		mes "治療箱は一度に1個だけ";
		mes "支給しているんです～。";
		mes "使い終わったらもう一度";
		mes "受け取りに来てもらえますか？";
		getitem 7641,1;
		close;
	}
	else {
		mes "[衛生兵ペイマー]";
		mes "ふう……。";
		mes "これでひとまず";
		mes "落ち着いたみたいです。";
		mes "あっ、余った治療箱は";
		mes "こちらで回収しておきますね～！";
		if(countitem(7641))
			delitem 7641,1;
		next;
		if('flag) {
			mes "[衛生兵ペイマー]";
			mes "お手伝いしてくださって";
			mes "本当にありがとうございます！";
			mes "助かりました～！";
			close;
		}
		mes "[衛生兵ペイマー]";
		mes "お手伝いしてくださって";
		mes "本当にありがとうございます！";
		mes "助かりました～！";
		mes "あなたも無茶して怪我しないように、";
		mes "気をつけてくださいね～！";
		emotion 14,getmdnpcname("衛生兵ペイマー#feima");
		npcskillsupport 34,10;
		sc_end SC_BLESSING;
		sc_start SC_BLESSING,240000,10;
		npcskillsupport 29,10;
		sc_end SC_INCREASEAGI;
		sc_start SC_INCREASEAGI,240000,10;
		npcskillsupport 33,10;
		sc_end 9;
		sc_start 9,300000,10;	//SC_ANGELUS
		npcskillsupport 73,10;
		sc_end 19;
		sc_start 19,120000,10;	//SC_KYRIE
		close;
	}
OnTalk1:
	unittalk "衛生兵ペイマー : うわ～ん！　副隊長、助けてくださ～い。私一人じゃ手が回りませ～ん！";
	end;
OnTalk2:
	unittalk "衛生兵ペイマー : お手伝いしてくれる方は、こちらに来て治療箱を受け取ってくださ～い！";
	end;
OnTalk3:
	unittalk "衛生兵ペイマー : きゃあ！　ビックリしました！　急に現れないでくださいよ～！";
	end;
}

1@tnm1.gat,39,114,3	script	負傷兵#1	688,{
	mes "[負傷兵]";
	mes "助かりました。";
	mes "ありがとうございます。";
	close;
}
1@tnm1.gat,39,114,3	script	負傷兵#1_1	687,3,3,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#1_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#1_1");
	hideonnpc getmdnpcname("負傷兵#1_1");
	hideoffnpc getmdnpcname("負傷兵#1");
	misceffect 6,getmdnpcname("負傷兵#1");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00,0x190,12,0,0;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : ……ううう……。";
	end;
}

1@tnm1.gat,30,120,3	script	負傷兵#2	690,{
	mes "[負傷兵]";
	mes "うう……。";
	mes "あんなに痛い治療は";
	mes "二度とゴメンだぜ……。";
	close;
}
1@tnm1.gat,30,120,3	script	負傷兵#2_1	689,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#2_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#2_1");
	hideonnpc getmdnpcname("負傷兵#2_1");
	hideoffnpc getmdnpcname("負傷兵#2");
	misceffect 6,getmdnpcname("負傷兵#2");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : うう……。";
	end;
}

1@tnm1.gat,25,117,5	script	負傷兵#3	693,{
	mes "[負傷兵]";
	mes "助かった……。";
	mes "仲間たちは無事かな……。";
	close;
}
1@tnm1.gat,25,117,5	script	負傷兵#3_1	692,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#3_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#3_1");
	hideonnpc getmdnpcname("負傷兵#3_1");
	hideoffnpc getmdnpcname("負傷兵#3");
	misceffect 6,getmdnpcname("負傷兵#3");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : ……ぐぐぐ……ううう……。";
	end;
}

1@tnm1.gat,19,118,4	script	負傷兵#4	695,{
	mes "[負傷兵]";
	mes "もうだめかと思っていたのだが……";
	mes "私は助かったのだな……。";
	close;
}
1@tnm1.gat,19,118,4	script	負傷兵#4_1	694,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#4_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#4_1");
	hideonnpc getmdnpcname("負傷兵#4_1");
	hideoffnpc getmdnpcname("負傷兵#4");
	misceffect 6,getmdnpcname("負傷兵#4");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : ……くうう……。";
	end;
}

1@tnm1.gat,19,110,4	script	負傷兵#5	698,{
	mes "[負傷兵]";
	mes "オレ、この戦闘が終わったら";
	mes "故郷に戻り未来を約束した幼馴染に";
	mes "結婚を申し込むんだ……。";
	mes "きっと幸せになれるよな……。";
	close;
}
1@tnm1.gat,19,110,4	script	負傷兵#5_1	697,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#5_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#5_1");
	hideonnpc getmdnpcname("負傷兵#5_1");
	hideoffnpc getmdnpcname("負傷兵#5");
	misceffect 6,getmdnpcname("負傷兵#5");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : ……死ぬのは……いやだ。";
	end;
}

1@tnm1.gat,24,104,7	script	負傷兵#6	10001,{
	mes "[負傷兵]";
	mes "お蔭で以前より良くなったが……";
	mes "動くのにはまだ早いようだ。";
	mes "まあ、生きているだけマシか……。";
	close;
}
1@tnm1.gat,24,104,7	script	負傷兵#6_1	699,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#6_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#6_1");
	hideonnpc getmdnpcname("負傷兵#6_1");
	hideoffnpc getmdnpcname("負傷兵#6");
	misceffect 6,getmdnpcname("負傷兵#6");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : ……うううう……。";
	end;
}

1@tnm1.gat,31,110,3	script	負傷兵#7	690,{
	mes "[負傷兵]";
	mes "ありがとう！";
	mes "あんたは命の恩人だ。";
	close;
}
1@tnm1.gat,31,110,3	script	負傷兵#7_1	689,{
	if(countitem(7641) == 0) {
		mes "‐負傷兵を治療するには";
		mes "　治療箱が1個必要です‐";
		close;
	}
	mes "‐気を失ったままうなっている。";
	mes "　治療箱を使用して";
	mes "　応急治療を行いますか？‐";
	next;
	if(select("治療を行う","様子をみる") == 2) {
		mes "‐少し負傷兵の様子を";
		mes "　見ることにしました‐";
		close;
	}
	mes "‐治療箱に書かれてある方法で";
	mes "　治療を行います……";
	misceffect 72,getmdnpcname("負傷兵#7_1");
	progressbar 2;
	delitem 7641,1;
	misceffect 6,getmdnpcname("負傷兵#7_1");
	hideonnpc getmdnpcname("負傷兵#7_1");
	hideoffnpc getmdnpcname("負傷兵#7");
	misceffect 6,getmdnpcname("負傷兵#7");
	setpartyinmap TNM1_QUE,TNM1_QUE + 1;
	if(TNM1_QUE < 9) {
		announce "衛生兵ペイマー : 負傷兵はあと" +(9 - TNM1_QUE)+ "人です!!",0x9,0x00ff00;
	}
	else {
		announce "衛生兵ペイマー : 全ての負傷兵の治療が終わりました！",0x9,0xff0000;
		donpcevent getmdnpcname("ルシル#tnm01")+ "::OnStart";
	}
	mes "　治療に成功しました‐";
	close;
OnTouch:
	unittalk "負傷兵 : うう……。";
	end;
}

1@tnm1.gat,46,105,5	script	ルシル#tnm01	667,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		cutin "tnm_lucile01",2;
		mes "[ルシル]";
		mes "そちらの援軍のリーダーは";
		mes "どの方ですか？";
		close2;
		cutin "tnm_lucile01",255;
		end;
	}
	switch(TNM1_QUE) {
	case 9:
		stopnpctimer;
		cutin "tnm_lucile01",0;
		mes "[ルシル]";
		mes "アサシンギルドのルシルです。";
		mes "少し遠い所の任務でしたので、";
		mes "遅れました。";
		unittalk "ルシル : アサシンギルドのルシルです。少し遠い所の任務でしたので、遅れました。";
		next;
		cutin "tnm_loki",2;
		mes "[タナトス]";
		mes "タナトスだ……。";
		donpcevent getmdnpcname("タナトス#tnm01")+ "::OnTalk1";
		next;
		cutin "tnm_loki",255;
		mes "[副隊長ハイム]";
		mes "アサシンギルドの支援か！";
		mes "よく来てくれた!!";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk1";
		next;
		cutin "tnm_lucile01",0;
		mes "[ルシル]";
		mes "様子を見る限り、";
		mes "芳しくないようですね。";
		unittalk "ルシル : 様子を見る限り、芳しくないようですね。";
		next;
		mes "[ルシル]";
		mes "あの勇猛なプロンテラ騎士団は何処へ？";
		unittalk "ルシル : あの勇猛なプロンテラ騎士団は何処へ？";
		next;
		cutin "tnm_lucile01",255;
		mes "[副隊長ハイム]";
		mes "貴様……";
		mes "私を挑発しているのか？";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk2";
		next;
		cutin "tnm_lucile01",0;
		mes "[ルシル]";
		mes "まさか、誤解です。";
		mes "それより上の階で";
		mes "何か不穏な事が起きていませんか？";
		unittalk "ルシル : まさか、誤解です。それより上の階で何か不穏な事が起きていませんか？";
		next;
		cutin "tnm_lucile01",255;
		emotion 0,getmdnpcname("副隊長ハイム#heim");
		mes "[副隊長ハイム]";
		mes "どうしてその事を……";
		mes "確かに魔族たちは進行を止め、";
		mes "何かを待っている様子だ。";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk3";
		next;
		cutin "tnm_lucile01",0;
		emotion 5,getmdnpcname("ルシル#tnm01");
		mes "[ルシル]";
		mes "……ということらしいですよ。";
		mes "獲物は最上階みたいですが、";
		mes "どうします？";
		unittalk "ルシル : ……ということらしいですよ。獲物は最上階みたいですが、どうします？";
		next;
		cutin "tnm_loki",2;
		mes "[タナトス]";
		mes "そうか……";
		mes "それなら、俺は先に行く。";
		donpcevent getmdnpcname("タナトス#tnm01")+ "::OnTalk2";
		next;
		cutin "tnm_lucile01",0;
		mes "[ルシル]";
		mes "あら、相変わらず";
		mes "行動が早いのですね。";
		unittalk "ルシル : あら、相変わらず行動が早いのですね。";
		hideonnpc getmdnpcname("タナトス#tnm01");
		next;
		cutin "tnm_lucile01",255;
		mes "[副隊長ハイム]";
		mes "な……何をするつもりだ！";
		mes "そんな少人数で乗り込んでも";
		mes "無駄死にするだけだぞ！";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk4";
		next;
		cutin "tnm_lucile01",0;
		mes "[ルシル]";
		mes "少人数だなんて……";
		mes "ここに動ける兵士が";
		mes "いるじゃないですか。";
		unittalk "ルシル : 少人数だなんて……ここに動ける兵士がいるじゃないですか。";
		next;
		mes "[ルシル]";
		mes "それでは援護をお願いしますね。";
		mes "デュー！";
		mes "後のことは任せます。";
		unittalk "ルシル : それでは援護をお願いしますね。デュー！　後のことは任せます。";
		next;
		cutin "tnm_lucile01",255;
		mes "[アサシン・デュー]";
		mes "お任せください。";
		setpartyinmap TNM1_QUE,10;
		donpcevent getmdnpcname("アサシン・デュー#tnm01")+ "::OnStart";
		next;
		mes "[副隊長ハイム]";
		mes "何を考えているんだ彼らは……。";
		mes "何にせよ厳しい状況だ。";
		mes "君も彼らを援護してくれ。";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk5";
		hideonnpc getmdnpcname("ルシル#tnm01");
		hideonnpc getmdnpcname("アサシン・ヒュー#tnm01");
		hideonnpc getmdnpcname("アサシン・リュー#tnm01");
		next;
		mes "[副隊長ハイム]";
		mes "魔族を迎撃するだけでも、";
		mes "大きな力になるはずだ。頼むぞ。";
		donpcevent getmdnpcname("副隊長ハイム#heim")+ "::OnTalk6";
		close;
	}
OnStart:
	initnpctimer;
	hideoffnpc getmdnpcname("ルシル#tnm01");
	hideoffnpc getmdnpcname("タナトス#tnm01");
	hideoffnpc getmdnpcname("アサシン・ヒュー#tnm01");
	hideoffnpc getmdnpcname("アサシン・リュー#tnm01");
	donpcevent getmdnpcname("衛生兵ペイマー#feima")+ "::OnTalk3";
	end;
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("ルシル#tnm01");
	end;
}

1@tnm1.gat,52,104,3	script	タナトス#tnm01	494,{
	cutin "tnm_loki",2;
	mes "[タナトス]";
	mes "……。";
	close2;
	cutin "tnm_loki",255;
	end;
OnTalk1:
	unittalk "タナトス : タナトスだ……。";
	end;
OnTalk2:
	unittalk "タナトス : そうか……それなら、俺は先に行く。";
	end;
}

1@tnm1.gat,42,104,5	script	アサシン・ヒュー#tnm01	10002,{
	mes "[アサシン・ヒュー]";
	mes "任務中です。お静かに。";
	close;
}

1@tnm1.gat,44,101,5	script	アサシン・リュー#tnm01	884,{
	//mes "[アサシン・ヒュー]";
	mes "[アサシン・リュー]";
	mes "ルシル姉さんと共に行動しています。";
	close;
}

1@tnm1.gat,70,108,3	script	アサシン・デュー#tnm01	884,{
	mes "[アサシン・デュー]";
	mes "上の階まで行く道は";
	mes "私がご案内いたします。";
	next;
	if(select("移動する","移動しない") == 2) {
		mes "[アサシン・デュー]";
		mes "魔神との戦闘が";
		mes "起きる可能性もありますし";
		mes "準備は怠らない方が";
		mes "いいですからね。";
		mes "分かりました。";
		close;
	}
	mes "[アサシン・デュー]";
	mes "それでは、ご武運を。";
	close2;
	set TNM1_QUE,11;
	setquest 114815;
	compquest 114815;
	warp getmdmapname("1@tnm1.gat"),91,23;
	end;
OnStart:
	hideoffnpc getmdnpcname("アサシン・デュー#tnm01");
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("アサシン・デュー#tnm01");
	end;
}

1@tnm1.gat,91,23,0	script	#tnm1stepmob	139,1,1,{
OnTouch:
	initnpctimer;
	hideonnpc getmdnpcname("#tnm1stepmob");
	announce "誘惑の魔神の影 : 人間風情が……。貴様に葬られた多くの同胞の痛みを知るがいい！",0x9,0x00ff00;
	end;
OnTimer3000:
	announce "アサシン・ヒュー : 姉さん！　危ない！",0x9,0x00ff00;
	end;
OnTimer5000:
	announce "ルシル : え……？　きゃあああ！",0x9,0x00ff00;
	end;
OnTimer7000:
	announce "誘惑の魔神の影 : まだ人間が居るようだな……。くくく、こいつら同様、血祭にあげてやる……!!",0x9,0x00ff00;
	monster getmdmapname("1@tnm1.gat"),99,24,"誘惑の魔神の影",2939,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),113,21,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),113,26,"絶念の魔神の影",2941,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),122,27,"誘惑の魔神の影",2939,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),124,26,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),126,27,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),129,25,"絶念の魔神の影",2941,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),136,25,"誘惑の魔神の影",2939,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),136,26,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	monster getmdmapname("1@tnm1.gat"),137,25,"絶念の魔神の影",2941,1,getmdnpcname("#tnm1stepmob")+ "::OnKilled";
	stopnpctimer;
	end;
OnKilled:
	// dummy
	end;
}

1@tnm1.gat,158,24,0	warp	#newwarp_jp	2,2,1@tnm1.gat,124,86

1@tnm1.gat,138,96,3	script	ルシル#tnm02	667,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐何の反応もなく、動かない。";
		mes "　まるで機械人形のようだ‐";
		mes "　";
		mes "‐^ff0000パーティーリーダーのみ";
		mes "　進行が可能です^000000‐";
		close;
	}
	switch(TNM1_QUE) {
	case 11:
		cutin "tnm_lucile02",2;
		mes "[ルシル]";
		mes "くっ、魔族に不覚を取り、";
		mes "ダメージをうけてしまいました。";
		mes "……動くことができません。";
		unittalk "ルシル : くっ、魔族に不覚を取り、ダメージをうけてしまいました。……動くことができません。";
		next;
		mes "[ルシル]";
		mes "損傷が激しく、このままでは";
		mes "あと少しで会話もできなくなります。";
		unittalk "ルシル : 損傷が激しく、このままではあと少しで会話もできなくなります。";
		next;
		mes "[ルシル]";
		mes "……申し訳ないのですが、";
		mes "少し力を貸して頂けませんか？";
		unittalk "ルシル : ……申し訳ないのですが、少し力を貸して頂けませんか？";
		next;
		mes "[ルシル]";
		mes "私はちょっと特殊な体で、";
		mes "再起動を行うことで、";
		mes "体を修復する事が";
		mes "できるのですが……";
		unittalk "ルシル : 私はちょっと特殊な体で、再起動を行うことで体を修復する事ができるのですが……";
		next;
		mes "[ルシル]";
		mes "その間、私は";
		mes "完全に動くことができないので、";
		mes "周りからの攻撃で";
		mes "簡単に倒れてしまいます。";
		unittalk "ルシル : その間、私は完全に動くことができないので、周りからの攻撃で簡単に倒れてしまいます。";
		next;
		mes "[ルシル]";
		mes "ですので、少しの間だけ";
		mes "私の傍にいてください……。";
		unittalk "ルシル : ですので、少しの間だけ私の傍にいてください……。";
		next;
		cutin "tnm_lucile03",2;
		mes "[ルシル]";
		mes "お願い……します……。";
		mes "　";
		mes "‐^ff0000もう一度ルシルに話しかけ";
		mes "　ルシルの再起動を手伝おう^000000‐";
		unittalk "ルシル : お願い……します……。";
		close2;
		cutin "tnm_lucile03",255;
		setpartyinmap TNM1_QUE,12;
		hideoffnpc getmdnpcname("アサシン・ヒュー#hui02");
		donpcevent getmdnpcname("アサシン・ヒュー#hui02")+ "::OnTalk1";
		donpcevent getmdnpcname("アサシン・ヒュー#hui02")+ "::OnStart";
		end;
	case 12:
		mes "‐ルシルの様子を伺う。";
		mes "　彼女は人の姿をしているが、";
		mes "　まるで動力が切れた機械のように";
		mes "　無機質で全く動かない。";
		mes "　";
		mes "　^ff0000ルシルの再起動を手伝いますか？^000000‐";
		cutin "tnm_lucile03",2;
		next;
		if(select("手伝う","手伝わない") == 2){
			mes "‐あなたはその場を離れた‐";
			close2;
			cutin "tnm_lucile03",255;
			end;
		}
		cutin "tnm_lucile03",255;
		mes "‐ルシルの再起動を手伝うことにした。";
		mes "　彼女の体から、小さく";
		mes "　何かの駆動音が聞こえる……";
		misceffect 202,getmdnpcname("ルシル#tnm02");
		progressbar 30;
		mes "　^ff0000システムを再起動した。^000000";
		mes "　再起動したルシルに話しかけよう‐";
		setpartyinmap TNM1_QUE,13;
		killmonster getmdmapname("1@tnm1.gat"),getmdnpcname("#tnm1stepmob")+ "::OnKilled";
		close;
	case 13:
		cutin "tnm_lucile02",2;
		mes "[ルシル]";
		mes "ふう……";
		mes "予想より早く治ったようです。";
		mes "驚きましたか？";
		mes "普通の人間の体と違って毎回";
		mes "このように修理をしなければ";
		mes "ならないんです。";
		unittalk "ルシル : ふう……予想より早く治ったようです。驚きましたか？　普通の人間の体と違って毎回このように修理をしなければならないんです。";
		next;
		mes "[ルシル]";
		mes "天から授かった体ですから";
		mes "納得するしかありません。";
		mes "それはそうとして……";
		mes "中央の扉が見えますか？";
		unittalk "ルシル : 天から授かった体ですから納得するしかありません。それはそうとして……中央の扉が見えますか？";
		cutin "tnm_lucile01",2;
		next;
		mes "[ルシル]";
		mes "早くいかないと";
		mes "この世界が危険です。";
		unittalk "ルシル : 早くいかないとこの世界が危険です。";
		close2;
		cutin "tnm_lucile02",255;
		setpartyinmap TNM1_QUE,14;
		initnpctimer;
		unittalk "ルシル : それでは私はお先に失礼します。世界を救いたいのであれば、一緒に来て下さい。";
		hideonnpc getmdnpcname("ルシル#tnm02");
		end;
	}
OnTalk1:
	unittalk "ルシル : ……お待たせしました。私の再起動も完了したようです";
	end;
OnTimer1000:
	stopnpctimer;
	donpcevent getmdnpcname("アサシン・ヒュー#hui02")+ "::OnTalk2";
	end;
}

1@tnm1.gat,135,99,5	script	アサシン・ヒュー#hui02	10002,{
	if(TNM1_QUE != 14) {
		mes "[アサシン・ヒュー]";
		mes "姉さんが心配です……。";
		mes "^ff0000機械に近い体^000000なんです。";
		mes "万が一";
		mes "大きな負傷をすると危険なんです。";
		close;
	}
	mes "[アサシン・ヒュー]";
	mes "この上にタナトス様がいます！";
	mes "ルシル姉さんが今";
	mes "後を追っているはずです。";
	next;
	mes "[アサシン・ヒュー]";
	mes "協力していただけるのなら";
	mes "すぐに向かっていただけますか。";
	mes "私が案内します。";
	next;
	if(select("移動する","移動しない") == 2) {
		mes "[アサシン・ヒュー]";
		mes "……そうですか。";
		close;
	}
	mes "[アサシン・ヒュー]";
	mes "こちらです。";
	mes "気を付けて下さい。";
	close2;
	warp getmdmapname("1@tnm2.gat"),90,86;
	end;
OnStart:
	areamonster getmdmapname("1@tnm1.gat"),129,91,152,114,"誘惑の魔神の影",2939,5,getmdnpcname("アサシン・ヒュー#hui02")+ "::OnKilled";
	areamonster getmdmapname("1@tnm1.gat"),129,91,152,114,"猜疑の魔神の影",2940,7,getmdnpcname("アサシン・ヒュー#hui02")+ "::OnKilled";
	areamonster getmdmapname("1@tnm1.gat"),129,91,152,114,"絶念の魔神の影",2941,4,getmdnpcname("アサシン・ヒュー#hui02")+ "::OnKilled";
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@tnm1.gat"),getmdnpcname("アサシン・ヒュー#hui02")+ "::OnKilled");
	if('@count <= 0) {
		initnpctimer;
		setpartyinmap TNM1_QUE,13;
	}
	end;
OnTimer1000:
	unittalk "アサシン・ヒュー : 魔物の気配が消えました！　この辺にいる魔物たちは全て倒したようです！";
	end;
OnTimer3000:
	stopnpctimer;
	donpcevent getmdnpcname("ルシル#tnm02")+ "::OnTalk1";
	end;
OnTalk1:
	unittalk "アサシン・ヒュー : 姉さんっ、気を付けて下さい！　魔族どもが集まってきます！";
	end;
OnTalk2:
	unittalk "アサシン・ヒュー : ね……姉さん……。";
	end;
}

1@tnm2.gat,0,0,0	script	#tnm2topmob	128,{
OnStart:
	initnpctimer;
	set 'count,5;
	set 'stone,0;
	end;
OnTimer1000:
	announce "魔神の塔の5方向から魔神石が現れました。",0x9,0x00ff00;
	end;
OnTimer2000:
	monster getmdmapname("1@tnm2.gat"),68,167,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	monster getmdmapname("1@tnm2.gat"),90,86,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	monster getmdmapname("1@tnm2.gat"),190,86,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	monster getmdmapname("1@tnm2.gat"),206,162,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	monster getmdmapname("1@tnm2.gat"),142,214,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer4000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),68-3,167-3,68+3,167+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),90-3,86-3,90+3,86+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),190-3,86-3,190+3,86+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),206-3,162-3,206+3,162+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),142-3,214-3,142+3,214+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	}
	end;
OnTimer5000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),68-3,167-3,68+3,167+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),90-3,86-3,90+3,86+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),190-3,86-3,190+3,86+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),206-3,162-3,206+3,162+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),142-3,214-3,142+3,214+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	}
	end;
OnTimer6000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer21000:
	announce "ルシル : 魔神石が1回目の移動を始めました。",0x9,0x00ff00;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer22000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),78,165,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),183,94,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),140,205,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer26000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer31000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer32000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),96,95,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),197,162,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer34000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),78-3,165-3,78+3,165+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),96-3,95-3,96+3,95+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),183-3,94-3,183+3,94+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),197-3,162-3,197+3,162+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),140-3,205-3,140+3,205+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	}
	end;
OnTimer35000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),78-3,165-3,78+3,165+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),96-3,95-3,96+3,95+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),183-3,94-3,183+3,94+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),197-3,162-3,197+3,162+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),140-3,205-3,140+3,205+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	}
	end;
OnTimer46000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer51000:
	announce "ルシル : 魔神石が2回目の移動を始めました。",0x9,0x00ff00;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer52000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),88,163,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),174,103,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),140,195,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer61000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer62000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),103,104,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),188,161,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer64000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),88-3,163-3,88+3,163+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),103-3,104-3,103+3,104+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),174-3,103-3,174+3,103+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),188-3,161-3,188+3,161+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),140-3,195-3,140+3,195+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	}
	end;
OnTimer65000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),88-3,163-3,88+3,163+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),103-3,104-3,103+3,104+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),174-3,103-3,174+3,103+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),188-3,161-3,188+3,161+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),140-3,195-3,140+3,195+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	}
	end;
OnTimer66000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer81000:
	announce "ルシル : 魔神石が3回目の移動を始めました。",0x9,0x00ff00;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer82000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),98,160,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),165,112,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),140,185,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer86000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer91000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer92000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),110,110,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),179,158,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer94000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),98-3,160-3,98+3,160+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),110-3,110-3,110+3,110+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		//areamonster getmdmapname("1@tnm2.gat"),174-3,103-3,174+3,103+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),179-3,158-3,179+3,158+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
		areamonster getmdmapname("1@tnm2.gat"),140-3,185-3,140+3,185+3,"誘惑の魔神の影",2939,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2939";
	}
	end;
OnTimer95000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	if(!'first) {
		areamonster getmdmapname("1@tnm2.gat"),98-3,160-3,98+3,160+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),110-3,110-3,110+3,110+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		//areamonster getmdmapname("1@tnm2.gat"),174-3,103-3,174+3,103+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),179-3,158-3,179+3,158+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
		areamonster getmdmapname("1@tnm2.gat"),140-3,185-3,140+3,185+3,"猜疑の魔神の影",2940,2,getmdnpcname("#tnm2topmob")+ "::OnKilled2940";
	}
	end;
OnTimer106000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer111000:
	announce "ルシル : 魔神石が4回目の移動を始めました。",0x9,0x00ff00;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer112000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),108,156,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),157,120,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),140,173,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer121000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer122000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),116,116,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),170,155,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer126000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer141000:
	announce "ルシル : 魔神石が5回目の移動を始めました。　そろそろ危険です!!",0x9,0x00ff00;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer142000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),118,152,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),147,128,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),139,161,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer146000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer151000:
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer152000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),122,122,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),161,152,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer166000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnEventTalk";
	announce "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！",0x9,0xff0000;
	donpcevent getmdnpcname("#tnm2flamecross")+ "::OnStart";
	end;
OnTimer171000:
	announce "ルシル : かなり危険な状態です！　なんとか防いでください！",0x9,0xff0000;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer172000:
	if('stone & 0x1 == 0)
		monster getmdmapname("1@tnm2.gat"),126,148,"魔神石#01",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	if('stone & 0x4 == 0)
		monster getmdmapname("1@tnm2.gat"),143,131,"魔神石#03",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	if('stone & 0x10 == 0)
		monster getmdmapname("1@tnm2.gat"),138,150,"魔神石#05",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer176000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnFail1";
	announce "魔王モロク : くははははは、俺様の力の欠片たちよ！　ここに集え!!",0x9,0xff0000;
	end;
OnTimer178000:
	donpcevent getmdnpcname("タナトス#tnm02")+ "::OnFail1";
	announce "タナトス : これ以上、近寄らせるな！　ここで止めろ！",0x9,0x00ff00;
	end;
OnTimer181000:
	announce "ルシル : これ以上は限界です!!!",0x9,0xff0000;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer182000:
	if('stone & 0x2 == 0)
		monster getmdmapname("1@tnm2.gat"),129,130,"魔神石#02",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	if('stone & 0x8 == 0)
		monster getmdmapname("1@tnm2.gat"),144,148,"魔神石#04",2938,1,getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	end;
OnTimer183000:
	donpcevent getmdnpcname("タナトス#tnm02")+ "::OnFail2";
	announce "タナトス : 何をやっているんだ！　しっかり防げ!!",0x9,0x00ff00;
	end;
OnTimer184000:
	announce "‐封印に失敗しました‐",0x9,0x00ff00;
	end;
OnTimer185000:
	misceffect 17,getmdnpcname("タナトス#tnm02");
	misceffect 90,getmdnpcname("タナトス#tnm02");
	end;
OnTimer186000:
	donpcevent getmdnpcname("タナトス#tnm02")+ "::OnFail2";
	announce "タナトス : くっ……!!　もう一度だ！　何度でもお前を止めてやる!!　最後まで諦めるな！",0x9,0x00ff00;
	set 'first,1;
	set 'count,5;
	set 'stone,0;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled1";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled2";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled3";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled4";
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2topmob")+ "::OnKilled5";
	end;
OnTimer189000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnFail2";
	announce "魔王モロク : まだ懲りずに邪魔をするつもりか！　この虫けらどもが!!",0x9,0xff0000;
	end;
OnTimer191000:
	donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnFail3";
	announce "魔王モロク : 望み通りに最後までやってやる！　俺様の力の欠片たちよ！　出て来い!!",0x9,0xff0000;
	end;
OnTimer195000:
	initnpctimer;
	announce "‐再び魔神石が現れました。モロクへの接近を防ぎましょう!!‐",0x9,0x00ff00;
	end;
OnKilled1:
	set 'stone,'stone | 0x1;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStoneKilled";
	end;
OnKilled2:
	set 'stone,'stone | 0x2;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStoneKilled";
	end;
OnKilled3:
	set 'stone,'stone | 0x4;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStoneKilled";
	end;
OnKilled4:
	set 'stone,'stone | 0x8;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStoneKilled";
	end;
OnKilled5:
	set 'stone,'stone | 0x10;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStoneKilled";
	end;
OnStoneKilled:
	set 'count,'count-1;
	if('count == 0) {
		announce "ルシル : 魔神石を全て破壊したようです！　巨大な力がぶつかりあっています!!",0x9,0x00ff00;
		stopnpctimer;
		for(set '@i,1;'@i<=8;set '@i,'@i+1)
			hideoffnpc getmdnpcname("#tnmバリケード" +'@i);
		areasetcell getmdmapname("1@tnm2.gat"),108,110,112,113,5;
		mapwarp getmdmapname("1@tnm2.gat"),getmdmapname("1@tnm2.gat"),139,133;
		donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnStart";
	}
	else
		announce "ルシル : その調子です！　残りの魔神石はあと" +'count+ "個です!!",0x9,0x00ff00;
	end;
OnKilled2939:
OnKilled2940:
	// dummy
	end;
}

1@tnm2.gat,144,137,3	script	ルシル#tnm03	667,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ルシル]";
		mes "リーダーと話をしています。";
		mes "少し離れていてください。";
		cutin "tnm_lucile01",2;
		close2;
		cutin "tnm_lucile01",255;
		end;
	}
	if(TNM1_QUE == 14) {
		cutin "tnm_lucile01",2;
		mes "[ルシル]";
		mes "ちょうど良いタイミングですね。";
		mes "あちらを見て頂けますか？";
		unittalk "ルシル : ちょうど良いタイミングですね。あちらを見て頂けますか？";
		next;
		mes "[ルシル]";
		mes "やはりあのモロク、私達が止めなければ";
		mes "ならないようですね……。";
		mes "自信……ありますか？";
		unittalk "ルシル : やはりあのモロク、私達が止めなければならないようですね……。自信……ありますか？";
		next;
		cutin "tnm_lucile01",255;
		mes "[魔王モロク]";
		mes "愚かな人間め……!!";
		mes "このまま俺様を足止めできるとでも";
		mes "思っているのか!!";
		donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnTalk1";
		next;
		mes "[魔王モロク]";
		mes "出でよ！　我が影たちよ！";
		mes "闇の力に逆らう";
		mes "すべての物を切り刻め！";
		donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnTalk2";
		next;
		mes "[タナトス]";
		mes "ふっ、部下に助けを求めるとはな。";
		donpcevent getmdnpcname("タナトス#tnm02")+ "::OnTalk1";
		next;
		cutin "tnm_lucile01",2;
		mes "[ルシル]";
		mes "タナトス様、あながち虚勢という";
		mes "わけでもなさそうですよ？";
		unittalk "ルシル : タナトス様、あながち虚勢というわけでもなさそうですよ？";
		next;
		cutin "tnm_lucile01",255;
		mes "[魔王モロク]";
		mes "もうすぐ来る破滅の瞬間に";
		mes "恐怖するがよい!!";
		donpcevent getmdnpcname("魔王モロク#tnm01")+ "::OnTalk3";
		next;
		mes "[タナトス]";
		mes "うるさい！";
		mes "もういい加減に諦めたらどうだ！";
		mes "お前をここから一歩も出させん！";
		donpcevent getmdnpcname("タナトス#tnm02")+ "::OnTalk2";
		next;
		mes "[タナトス]";
		mes "ルシル！　後を頼んだぞ！";
		mes "俺がこいつを封印するまで！";
		donpcevent getmdnpcname("タナトス#tnm02")+ "::OnTalk3";
		next;
		cutin "tnm_lucile01",2;
		mes "[ルシル]";
		mes "了解しました。";
		unittalk "ルシル: 了解しました。";
		next;
		mes "[ルシル]";
		mes "さあ、みなさん。";
		mes "私達のやるべきことが決まりました。";
		mes "魔神石が入り込まないよう、";
		mes "ここを死守してください。";
		unittalk "ルシル : さあ、みなさん。私達のやるべきことが決まりました。魔神石が入り込まないよう、ここを死守してください。";
		setpartyinmap TNM1_QUE,15;
		setquest 7573;
		hideonnpc getmdnpcname("ルシル#tnm03");
		initnpctimer;
		close2;
		cutin "tnm_lucile01",255;
		end;
	}
	end;
OnTimer2000:
	announce "ルシル : 塔の5方向からモロクにエネルギーを与える為の魔神石が近づいてきています!!",0x9,0x00ff00,0x190,18,0,0;
	end;
OnTimer4000:
	stopnpctimer;
	donpcevent getmdnpcname("#tnm2topmob")+ "::OnStart";
	announce "ルシル : モロクのもとにたどりつく前に全て倒してください！",0x9,0x00ff00,0x190,18,0,0;
	end;
}

1@tnm2.gat,145,144,3	script	箱#tnmtop	10005,{
	setpartyinmap TNM1_QUE,17;
	misceffect 10,getmdnpcname("箱#tnmtop");
	hideonnpc getmdnpcname("箱#tnmtop");
	// 退魔神の杖、退魔神の弓、退魔神の両手剣、退魔神のカタール、退魔神のハンマー、退魔神の短剣
	// 魔神の腕力1、魔神の知力1、魔神の迅速1、魔神の体力1、魔神の集中1、魔神の幸運1
	setarray '@gain,2029,18131,21017,28009,28108,28707,4908,4911,4914,4917,4920,4923;
	setarray '@rate,8,8,10,8,10,8,1,1,1,1,1,1;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		for(set '@j,0; '@j<'@rate['@i]; set '@j,'@j+1) {
			set '@result['@k],'@gain['@i];
			set '@k,'@k+1;
		}
	}
	set '@x,145+rand(5)-2;
	set '@y,144+rand(5)-2;
	dropitem getmdmapname("1@tnm2.gat"),'@x,'@y,'@result[rand(getarraysize('@result))],1,0;
	set '@x,145+rand(5)-2;
	set '@y,144+rand(5)-2;
	dropitem getmdmapname("1@tnm2.gat"),'@x,'@y,'@result[rand(getarraysize('@result))],1,0;
	end;
}

1@tnm2.gat,144,137,3	script	ルシル#tnm04	667,{
	switch(TNM1_QUE) {
	case 15:
		if(checkquest(114805) & 0x8 == 0) {
			delquest 7573;
			mes "‐ルシルに話しかけようとしたその時";
			mes "　不思議な力に身を包まれた。";
			misceffect 35,"";
			setquest 114805;
			compquest 114805;
			misceffect 58,"";
			mes "　^0000ff魔神の塔入口で精錬可能な権利と";
			mes "　経験値を獲得！^000000‐";
			set TNM_REFINE,TNM_REFINE+3;
			if(TNM_REFINE > 1000)
				set TNM_REFINE,1000;
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,500000;
			next;
		}
		mes "[ルシル]";
		mes "どうやら封印の結界を";
		mes "壊そうとしていた魔神の力が";
		mes "タナトス様と衝突したようです。";
		mes "完全に成功とは";
		mes "いかなかったようですね。";
		cutin "tnm_lucile01",2;
		next;
		mes "‐箱を開封する事により、";
		mes "　ダンジョンの進行が可能となります‐";
		close2;
		cutin "tnm_lucile01",255;
		end;
	case 16:
	case 17:
		if(checkquest(114805) & 0x8 == 0) {
			delquest 7573;
			mes "‐ルシルに話しかけようとしたその時";
			mes "　不思議な力に身を包まれた。";
			misceffect 35,"";
			setquest 114805;
			compquest 114805;
			misceffect 58,"";
			mes "　^0000ff魔神の塔入口で精錬可能な権利と";
			mes "　経験値を獲得！^000000‐";
			set TNM_REFINE,TNM_REFINE+3;
			if(TNM_REFINE > 1000)
				set TNM_REFINE,1000;
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,500000;
			next;
		}
		mes "[ルシル]";
		mes "どうやら封印の結界を";
		mes "壊そうとしていた魔神の力が";
		mes "タナトス様と衝突したようです。";
		mes "完全に成功とは";
		mes "いかなかったようですね。";
		cutin "tnm_lucile01",2;
		next;
		mes "[ルシル]";
		mes "今の衝撃でモロクは、";
		mes "かなり……南の方に";
		mes "飛んで行きましたね。";
		mes "追いますか？";
		next;
		switch(select("追う","外に出る","やめる")) {
		case 1:
			mes "[ルシル]";
			mes "どうか魔神を無事に";
			mes "封印できますように……。";
			mes "ご武運を……。";
			next;
			mes "‐モロクを追う為、";
			mes "　南へ向かおうとしたが";
			mes "　突如、次元に乱れが生じた‐";
			misceffect 432,"";
			misceffect 174,"";
			misceffect 899,"";
			close2;
			cutin "tnm_lucile01",255;
			warp getmdmapname("1@tnm3.gat"),21,171;
			end;
		case 2:
			mes "[ルシル]";
			mes "本当に追跡を諦めてしまうのですか？";
			cutin "tnm_lucile02",2;
			next;
			if(select("はい","いいえ") == 2) {
				mes "[ルシル]";
				mes "わかりました。";
				mes "覚悟が決まりましたら";
				mes "教えてください。";
				close2;
				cutin "tnm_lucile01",255;
				end;
			}
			mes "[ルシル]";
			mes "そうですか……。";
			mes "ここが、あなたの";
			mes "限界のようですね。";
			close2;
			cutin "tnm_lucile01",255;
			warp "dali.gat",134,112;
			end;
		case 3:
			mes "[ルシル]";
			mes "わかりました。";
			mes "覚悟が決まりましたら";
			mes "教えてください。";
			close2;
			cutin "tnm_lucile01",255;
			end;
		}
	}
	end;
OnTalk1:
	unittalk "ルシル : 封印に成功……した……？";
	end;
}

1@tnm2.gat,136,139,5	script	魔王モロク#tnm01	1916,{
	end;
OnTalk1:
	unittalk "魔王モロク : 愚かな人間め……!!　このまま俺様を足止めできるとでも思っているのか!!";
	end;
OnTalk2:
	unittalk "魔王モロク : 出でよ！　我が影たちよ！　闇の力に逆らうすべての物を切り刻め！";
	end;
OnTalk3:
	unittalk "魔王モロク : もうすぐ来る破滅の瞬間に恐怖するがよい!!";
	end;
OnEventTalk:
	unittalk "魔王モロク : ふははは！　灼熱の炎に焼かれるがよい！";
	end;
OnFail1:
	unittalk "魔王モロク : くははははは、俺様の力の欠片たちよ！　ここに集え!!";
	end;
OnFail2:
	unittalk "魔王モロク : まだ懲りずに邪魔をするつもりか！　この虫けらどもが!!";
	end;
OnFail3:
	unittalk "魔王モロク : 望み通りに最後までやってやる！　俺様の力の欠片たちよ！　出て来い!!";
	end;
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	unittalk "魔王モロク : こ……こんなはずが！　いったい貴様は……貴様の正体はなんだ!!";
	end;
OnTimer6000:
	donpcevent getmdnpcname("タナトス#tnm02")+ "::OnTalk4";
	end;
OnTimer8000:
	misceffect 90,getmdnpcname("タナトス#tnm02");
	end;
OnTimer10000:
	stopnpctimer;
	hideonnpc getmdnpcname("タナトス#tnm02");
	hideonnpc getmdnpcname("魔王モロク#tnm01");
	hideoffnpc getmdnpcname("箱#tnmtop");
	hideoffnpc getmdnpcname("ルシル#tnm04");
	donpcevent getmdnpcname("ルシル#tnm04")+ "::OnTalk1";
	end;
}

1@tnm2.gat,142,139,3	script	タナトス#tnm02	10009,{
	if(TNM1_QUE == 14) {
		emotion 6,getmdnpcname("タナトス#tnm02");
		end;
	}
	if(TNM1_QUE == 15) {
		unittalk "タナトス : 悪いな……今は話してる余裕がないんだ。";
		end;
	}
	end;
OnTalk1:
	unittalk "タナトス : ふっ、部下に助けを求めるとはな。";
	end;
OnTalk2:
	unittalk "タナトス : うるさい！　もういい加減に諦めたらどうだ！　お前をここから一歩も出させん！";
	end;
OnTalk3:
	unittalk "タナトス : ルシル！　後を頼んだぞ！　俺がこいつを封印するまで！";
	end;
OnTalk4:
	unittalk "タナトス : 悪いがここまでだな!!　これで終わりだ!!! ";
	end;
OnFail1:
	unittalk "タナトス : これ以上、近寄らせるな！　ここで止めろ！";
	end;
OnFail2:
	unittalk "タナトス : 何をやっているんだ！　しっかり防げ!!";
	end;
OnFail3:
	unittalk "タナトス : くっ……!!　もう一度だ！　何度でもお前を止めてやる!!　最後まで諦めるな！";
	end;
}

1@tnm2.gat,0,0,0	script	#tnm2flamecross	139,{
OnStart:
	initnpctimer;
	end;
OnTimer300:
	monster getmdmapname("1@tnm2.gat"),126,149," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),128,130," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),145,130," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),146,149," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),138,151," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer600:
	monster getmdmapname("1@tnm2.gat"),122,151," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),125,127," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),148,126," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),150,151," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),138,160," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer900:
	monster getmdmapname("1@tnm2.gat"),118,153," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),122,124," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),151,122," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),155,152," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,165," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer1200:
	monster getmdmapname("1@tnm2.gat"),113,154," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),118,121," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),156,120," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),148,149," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,165," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer1500:
	monster getmdmapname("1@tnm2.gat"),107,156," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),115,118," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),160,117," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),162,153," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,170," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer1800:
	monster getmdmapname("1@tnm2.gat"),101,158," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),112,115," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),164,113," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),167,154," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,176," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer2100:
	monster getmdmapname("1@tnm2.gat"),96,160," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),109,110," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),168,109," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),173,156," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,181," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer2400:
	monster getmdmapname("1@tnm2.gat"),91,161," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),106,106," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),172,105," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),179,158," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,186," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer2600:
	monster getmdmapname("1@tnm2.gat"),86,162," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),102,102," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//2
	monster getmdmapname("1@tnm2.gat"),176,101," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),185,160," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,191," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer3000:
	monster getmdmapname("1@tnm2.gat"),81,163," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//1
	monster getmdmapname("1@tnm2.gat"),99,98," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";		//2
	monster getmdmapname("1@tnm2.gat"),180,97," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//3
	monster getmdmapname("1@tnm2.gat"),191,161," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//4
	monster getmdmapname("1@tnm2.gat"),140,196," ",2960,1,getmdnpcname("#tnm2flamecross")+ "::OnKilled";	//5
	end;
OnTimer8000:
	stopnpctimer;
	killmonster getmdmapname("1@tnm2.gat"),getmdnpcname("#tnm2flamecross")+ "::OnKilled";
	end;
}

1@tnm2.gat,109,113,0	script	#tnmバリケード1	1905,{}
1@tnm2.gat,110,112,0	script	#tnmバリケード2	1905,{}
1@tnm2.gat,111,111,0	script	#tnmバリケード3	1905,{}
1@tnm2.gat,112,110,0	script	#tnmバリケード4	1905,{}
1@tnm2.gat,108,113,0	script	#tnmバリケード5	1905,{}
1@tnm2.gat,109,112,0	script	#tnmバリケード6	1905,{}
1@tnm2.gat,110,111,0	script	#tnmバリケード7	1905,{}
1@tnm2.gat,111,110,0	script	#tnmバリケード8	1905,{}

1@tnm3.gat,21,171,0	script	#tnm3event01	139,1,1,{
	hideonnpc getmdnpcname("#tnm3event01");
	announce "女の子の叫び : きゃあああ！　魔族だわ!!　誰か助けて!!",0x9,0x00ff00;
	donpcevent getmdnpcname("女の子#tnm01")+ "::OnStart";
	end;
}

1@tnm3.gat,43,175,3	script	女の子#tnm01	941,{
	set '@count,getmapmobs(getmdmapname("1@tnm3.gat"),getmdnpcname("女の子#tnm01")+ "::OnKilled");
	if('@count > 0) {
		mes "[女の子]";
		mes "どうして城の中に魔族たちが……。";
		mes "助けて下さい!!";
		close;
	}
	if(TNM1_QUE == 17) {
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[女の子]";
			mes "……いきなり魔族が現れて";
			mes "本当に怖かったんです。";
			close;
		}
		mes "[女の子]";
		mes "いきなりどうして";
		mes "城に魔族が現れたんだろう……。";
		mes "警備兵のおじさんたちも";
		mes "いっぱい怪我をしちゃったし……。";
		unittalk "女の子 : いきなりどうして城に魔族が現れたんだろう……。警備兵のおじさんたちもいっぱい怪我をしちゃったし……。";
		next;
		menu "ここは何処なの？",-;
		unittalk getcharid(3),strcharinfo(0)+" : ここは何処なの？";
		mes "[女の子]";
		mes "？";
		mes "ここはモロクです。";
		mes "そしてこの城はモロク城ですよ。";
		unittalk "女の子 : ？　ここはモロクです。そしてこの城はモロク城ですよ。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "モロク城？";
		unittalk getcharid(3),strcharinfo(0)+" : モロク城？";
		next;
		mes "[女の子]";
		mes "そうですよ。";
		mes "私のパパはモロクの領主様なのです。";
		unittalk "女の子 : そうですよ。私のパパはモロクの領主様なのです。";
		next;
		mes "‐ルシルがいた時代から";
		mes "　だいぶ時間が経過しているようだ‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐ルシルがいた時代からだいぶ時間が経過しているようだ‐";
		next;
		mes "[領主の娘]";
		mes "どうも何かが";
		mes "起きているようなんです……。";
		mes "地下室から変な音が";
		mes "聞こえたって……。";
		unittalk "領主の娘 : どうも何かが起きているようなんです……。地下室から変な音が聞こえたって……。";
		next;
		mes "[領主の娘]";
		mes "黒い服を着たお兄さんたちも";
		mes "中に入ったけど、戻ってきません。";
		mes "この城で何が起きているんですか？";
		unittalk "領主の娘 : 黒い服を着たお兄さんたちも中に入ったけど、戻ってきません。この城で何が起きているんですか？";
		next;
		mes "[領主の娘]";
		mes "パパ……。";
		mes "パパは無事でいるのかな……。";
		unittalk "領主の娘 : パパ……。パパは無事でいるのかな……。";
		next;
		mes "[領主の娘]";
		mes "あそこに見える本棚の後ろにある";
		mes "通路からさらに下の方まで";
		mes "降りて行くことができます！";
		mes "私も連れて行って下さい！";
		mes "お願いします！";
		unittalk "領主の娘 : あそこに見える本棚の後ろにある通路からさらに下の方まで降りて行くことができます！　私も連れて行って下さい！　お願いします！";
		setpartyinmap TNM1_QUE,18;
		misceffect 35,getmdnpcname("#tnm3gate01");
		hideoffnpc getmdnpcname("#tnm3gate01");
		close;
	}
	mes "[領主の娘]";
	mes "あそこに見える本棚が";
	mes "秘密の通路と繋がっています。";
	mes "一緒に連れて行って下さい。";
	mes "お願いします……。";
	mes "パパが……心配なのです……。";
	close;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	monster getmdmapname("1@tnm3.gat"),37,175,"誘惑の魔神の影",2939,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),39,173,"誘惑の魔神の影",2939,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),41,171,"誘惑の魔神の影",2939,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	end;
OnTimer2000:
	monster getmdmapname("1@tnm3.gat"),32,176,"猜疑の魔神の影",2940,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),30,178,"猜疑の魔神の影",2940,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),32,180,"猜疑の魔神の影",2940,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	end;
OnTimer5000:
	monster getmdmapname("1@tnm3.gat"),30,173,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),32,175,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),34,173,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	end;
OnTimer6000:
	set 'flag,1;
	stopnpctimer;
	monster getmdmapname("1@tnm3.gat"),30,184,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),32,182,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),34,180,"絶念の魔神の影",2941,1,getmdnpcname("女の子#tnm01")+ "::OnKilled";
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@tnm3.gat"),getmdnpcname("女の子#tnm01")+ "::OnKilled");
	if('flag && '@count <= 0) {
		unittalk "女の子 : ありがとうございます……。だけどどうして魔族が……。";
	}
	end;
}

1@tnm3.gat,50,176,0	warp	#tnm3gate01	1,1,1@tnm3.gat,85,178

1@tnm3.gat,85,178,0	script	#tnm3event02ect	139,1,1,{
	hideonnpc getmdnpcname("#tnm3event02ect");
	hideoffnpc getmdnpcname("領主の娘#tnm02");
	donpcevent getmdnpcname("領主の娘#tnm02")+ "::OnStart";
	end;
}

1@tnm3.gat,89,179,4	script	領主の娘#tnm02	941,{
	mes "[領主の娘]";
	mes "どうして急にこんなに";
	mes "たくさんの魔族たちが……。";
	close;
OnStart:
	initnpctimer;
	unittalk "領主の娘 : あそこを見て下さい！　魔族が現れました！　これじゃ城の中が魔族だらけになりそうです！";
	monster getmdmapname("1@tnm3.gat"),97,173,"誘惑の魔神の影",2939,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),96,170,"誘惑の魔神の影",2939,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),94,164,"誘惑の魔神の影",2939,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	end;
OnTimer1000:
	monster getmdmapname("1@tnm3.gat"),100,170,"誘惑の魔神の影",2939,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),102,166,"誘惑の魔神の影",2939,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	end;
OnTimer3000:
	monster getmdmapname("1@tnm3.gat"),101,171,"猜疑の魔神の影",2940,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),102,172,"猜疑の魔神の影",2940,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),105,178,"猜疑の魔神の影",2940,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),104,177,"猜疑の魔神の影",2940,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),106,173,"猜疑の魔神の影",2940,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	end;
OnTimer5000:
	monster getmdmapname("1@tnm3.gat"),110,167,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),111,165,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),113,165,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),104,168,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	end;
OnTimer8000:
	set 'flag,1;
	stopnpctimer;
	monster getmdmapname("1@tnm3.gat"),121,170,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),122,171,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),123,170,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),125,173,"絶念の魔神の影",2941,1,getmdnpcname("領主の娘#tnm02")+ "::OnKilled";
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@tnm3.gat"),getmdnpcname("領主の娘#tnm02")+ "::OnKilled");
	if('flag && '@count <= 0) {
		stopnpctimer;	//custom
		unittalk "領主の娘 : この廊下を最後まで行くとさらに地下まで行く道があります！";
		announce "領主の娘 : この廊下を最後まで行くとさらに地下まで行く道があります！",0x9,0x00ff00;
		hideonnpc getmdnpcname("領主の娘#tnm02");
		hideoffnpc getmdnpcname("領主の娘#tnm03");
		hideoffnpc getmdnpcname("#tnm3gate02");
	}
	end;
}

1@tnm3.gat,128,164,3	script	領主の娘#tnm03	941,{
	mes "[領主の娘]";
	mes "ここからは私も詳しくありません。";
	mes "ずっと階段が続きますね……。";
	mes "これほどに魔族が多いのを見ると";
	mes "パパも危険なはずです！";
	mes "どうかパパを";
	mes "助けて下さい……。";
	close;
}

1@tnm3.gat,134,156,0	warp	#tnm3gate02	1,1,1@tnm3.gat,169,165

1@tnm3.gat,179,172,3	script	絶念の魔神の影#tnm3	2941,10,10,{
	end;
OnTouch:
	if(TNM1_QUE == 18) {
		initnpctimer;
		setpartyinmap TNM1_QUE,19;
	}
	end;
OnTimer3000:
	unittalk "絶念の魔神の影 : まさか、この城に忍び込む命知らずが居るとはな……。";
	end;
OnTimer6000:
	unittalk "絶念の魔神の影 : どうやって入って来たのかは知らないが、神聖な儀式は邪魔させんぞ。";
	end;
OnTimer9000:
	unittalk "絶念の魔神の影 : 出でよ！　我が兄弟たちよ!!";
	hideonnpc getmdnpcname("絶念の魔神の影#tnm3");
	monster getmdmapname("1@tnm3.gat"),179,172,"絶念の魔神の影",2941,1,getmdnpcname("#tnm3mobdead")+ "::OnKilled";
	end;
OnTimer10000:
	monster getmdmapname("1@tnm3.gat"),177,175,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm3mobdead")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),179,170,"猜疑の魔神の影",2940,1,getmdnpcname("#tnm3mobdead")+ "::OnKilled";
	end;
OnTimer11000:
	stopnpctimer;
	donpcevent getmdnpcname("#tnm3mobdead")+ "::OnStart";
	monster getmdmapname("1@tnm3.gat"),182,172,"誘惑の魔神の影",2939,1,getmdnpcname("#tnm3mobdead")+ "::OnKilled";
	monster getmdmapname("1@tnm3.gat"),182,170,"誘惑の魔神の影",2939,1,getmdnpcname("#tnm3mobdead")+ "::OnKilled";
	end;
}
1@tnm3.gat,1,1,0	script	#tnm3mobdead	139,{
	end;
OnStart:
	set 'flag,1;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@tnm3.gat"),getmdnpcname("#tnm3mobdead")+ "::OnKilled");
	if('flag && '@count <= 0) {
		misceffect 35,getmdnpcname("#tnm3gate03");
		hideoffnpc getmdnpcname("#tnm3gate03");
	}
	end;
}

1@tnm3.gat,183,177,0	warp	#tnm3gate03	1,1,1@tnm3.gat,97,6

1@tnm3.gat,97,18,3	script	誘惑の魔神の影#tnm3	2939,12,12,{
	end;
OnTouch:
	if(TNM1_QUE == 19) {
		initnpctimer;
		setpartyinmap TNM1_QUE,20;
	}
	end;
OnTimer1000:
	unittalk "誘惑の魔神の影 : お前たちがこの騒ぎの原因か？";
	end;
OnTimer4000:
	unittalk "誘惑の魔神の影 : まあ、何だっていい。お前たちはここで死ぬのだ。";
	end;
OnTimer7000:
	unittalk "誘惑の魔神の影 : お前たちの血を魔神に捧げる事にする!!";
	hideonnpc getmdnpcname("誘惑の魔神の影#tnm3");
	monster getmdmapname("1@tnm3.gat"),97,18,"誘惑の魔神の影",2939,1;
	end;
OnTimer8000:
	set '@map$,getmdmapname("1@tnm3.gat");
	monster '@map$,95+rand(5),16+rand(5),"猜疑の魔神の影",2940,1;
	monster '@map$,95+rand(5),16+rand(5),"猜疑の魔神の影",2940,1;
	monster '@map$,112,18,"誘惑の魔神の影",2939,1;
	monster '@map$,112,20,"猜疑の魔神の影",2940,1;
	monster '@map$,112,22,"絶念の魔神の影",2941,1;
	monster '@map$,113,23,"誘惑の魔神の影",2939,1;
	monster '@map$,114,13,"絶念の魔神の影",2941,1;
	monster '@map$,115,11,"猜疑の魔神の影",2940,1;
	monster '@map$,119,20,"猜疑の魔神の影",2940,1;
	monster '@map$,113,20,"猜疑の魔神の影",2940,1;
	monster '@map$,117,19,"誘惑の魔神の影",2939,1;
	monster '@map$,77,18,"猜疑の魔神の影",2940,1;
	monster '@map$,82,18,"誘惑の魔神の影",2939,1;
	monster '@map$,78,14,"絶念の魔神の影",2941,1;
	monster '@map$,71,18,"絶念の魔神の影",2941,1;
	monster '@map$,69,16,"誘惑の魔神の影",2939,1;
	monster '@map$,67,19,"猜疑の魔神の影",2940,1;
	monster '@map$,63,42,"猜疑の魔神の影",2940,1;
	monster '@map$,63,43,"誘惑の魔神の影",2939,1;
	monster '@map$,60,46,"猜疑の魔神の影",2940,1;
	monster '@map$,60,49,"猜疑の魔神の影",2940,1;
	monster '@map$,62,50,"誘惑の魔神の影",2939,1;
	monster '@map$,56,50,"絶念の魔神の影",2941,1;
	monster '@map$,75,67,"絶念の魔神の影",2941,1;
	monster '@map$,78,71,"猜疑の魔神の影",2940,1;
	monster '@map$,77,71,"猜疑の魔神の影",2940,1;
	monster '@map$,78,72,"誘惑の魔神の影",2939,1;
	monster '@map$,60,73,"猜疑の魔神の影",2940,1;
	monster '@map$,57,73,"絶念の魔神の影",2941,1;
	monster '@map$,62,73,"絶念の魔神の影",2941,1;
	monster '@map$,79,73,"誘惑の魔神の影",2939,1;
	monster '@map$,64,74,"猜疑の魔神の影",2940,1;
	monster '@map$,60,75,"誘惑の魔神の影",2939,1;
	monster '@map$,60,77,"誘惑の魔神の影",2939,1;
	monster '@map$,80,67,"絶念の魔神の影",2941,1;
	stopnpctimer;
	end;
}

1@tnm3.gat,93,52,4	script	モロクの領主#moclord01	106,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[モロクの領主]";
		mes "ネズミの正体はアサシンか？";
		mes "……他にもいるようだな。";
		mes "生贄になる為に来たのか？";
		close;
	}
	mes "[モロクの領主]";
	mes "ネズミの正体はアサシンか？";
	mes "……他にもいるようだな。";
	mes "生贄になる為に来たのか？";
	unittalk "モロクの領主 : ネズミの正体はアサシンか？……他にもいるようだな。生贄になる為に来たのか？";
	next;
	mes "[ロキ]";
	mes "時代遅れの腐った魔神なんかを";
	mes "呼び起こしてどうするつもりだ？";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk1";
	cutin "ep14_roki01",2;
	next;
	mes "[ロキ]";
	mes "おかげで俺がまた来るはめに";
	mes "なっちまったじゃねえか。";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk2";
	next;
	mes "[モロクの領主]";
	mes "どういうことだ……？";
	mes "アサシンギルドの君たちは、";
	mes "世界の力の均衡を維持する事が";
	mes "役目ではないのか？";
	unittalk "モロクの領主 : どういうことだ……？　アサシンギルドの君たちは、世界の力の均衡を維持する事が役目ではないのか？";
	cutin "ep14_roki01",255;
	next;
	mes "[モロクの領主]";
	mes "力の均衡を保つ為には";
	mes "魔神の復活が必要なのだ！、";
	mes "巨人までも神々のオモチャに";
	mes "なってしまったこの世界に……。";
	unittalk "モロクの領主 : 力の均衡を保つ為には魔神の復活が必要なのだ！　巨人までも神々のオモチャになってしまったこの世界に……。";
	next;
	mes "[モロクの領主]";
	mes "神は……";
	mes "私たちをどうするつもりなのか、";
	mes "知っているのか？";
	unittalk "モロクの領主 : 神は……私たちをどうするつもりなのか知っているのか？";
	next;
	mes "[モロクの領主]";
	mes "奴らは光、秩序、正義という名目の下に";
	mes "人間を……いや、この世界全体を……。";
	unittalk "モロクの領主 : 奴らは……光、秩序、正義という名目の下に人間を……いや、この世界全体を……。";
	next;
	mes "[ロキ]";
	mes "黙れ！";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk3";
	cutin "ep14_roki01",2;
	next;
	mes "[ロキ]";
	mes "神々がどうであれ、";
	mes "魔族がどうであれ……";
	mes "お前はここで死ぬ。";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk4";
	next;
	mes "[ロキ]";
	mes "それが俺の任務だからな。";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk5";
	next;
	mes "[モロクの領主]";
	mes "それで……そのくだらない任務を";
	mes "果たしてみせると？";
	unittalk "モロクの領主 : それで……そのくだらない任務を果たしてみせると？";
	cutin "ep14_roki01",255;
	next;
	mes "[ロキ]";
	mes "無論!!";
	cutin "ep14_roki01",2;
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk6";
	misceffect 55,getmdnpcname("ロキ#tnmloki01");
	next;
	mes "[ロキ]";
	mes "マインドブラスター!!";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk7";
	next;
	mes "[領主の娘]";
	mes "やめて下さい！";
	mes "パパを殺さないで!!";
	cutin "ep14_roki01",255;
	misceffect 135,getmdnpcname("領主の娘#tnm04");
	donpcevent getmdnpcname("領主の娘#tnm04")+ "::OnTalk1";
	hideoffnpc getmdnpcname("領主の娘#tnm04");
	next;
	mes "[ロキ]";
	mes "なっ……!?";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk8";
	cutin "ep14_roki01",2;
	next;
	mes "[モロクの領主]";
	mes "これはこれはフフフ……";
	mes "よく狙わないとねぇ～、";
	mes "アサシン先生。";
	unittalk "モロクの領主 : これはこれはフフフ……よく狙わないとねぇ～、アサシン先生。";
	cutin "ep14_roki01",255;
	next;
	mes "[領主の娘]";
	mes "何か……何かの……";
	mes "間違いだわ……。";
	donpcevent getmdnpcname("領主の娘#tnm04")+ "::OnTalk2";
	next;
	mes "[領主の娘]";
	mes "パパは……本当は……";
	mes "こんなことを……するような、";
	mes "人では……ない……の……。";
	donpcevent getmdnpcname("領主の娘#tnm04")+ "::OnTalk3";
	next;
	mes "[ロキ]";
	mes "なぜかばった!?";
	mes "人間は時折、理解不能な行動を起こす。";
	mes "これが心というものなのか？";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk9";
	cutin "ep14_roki01",2;
	next;
	mes "[モロクの領主]";
	mes "理解不能か……確かにそうだな。";
	mes "それを人間は犠牲と呼ぶ。";
	unittalk "モロクの領主 : 理解不能か……確かにそうだな。それを人間は犠牲と呼ぶ。";
	cutin "ep14_roki01",255;
	next;
	mes "[モロクの領主]";
	mes "しかし小娘！";
	mes "そんなものには何の意味も";
	mes "ないんだよぉ～！";
	mes "ウハハハハハッッ!!";
	unittalk "モロクの領主 : しかし小娘！　そんなものには何の意味もないんだよぉ～！　ウハハハハハッッ!!";
	next;
	mes "[モロクの領主]";
	mes "愚者どもめっ!!";
	mes "ここで朽ちるがいい!!";
	mes "魔神の復活は邪魔させんぞーーーっ!!";
	mes "クアアアアアッッ!!";
	unittalk "モロクの領主 : 愚者どもめっ!!　ここで朽ちるがいい!!　魔神の復活は邪魔させんぞーーーっ!!　クアアアアアッッ!!";
	misceffect 225,getmdnpcname("モロクの領主#moclord01");
	next;
	mes "[ロキ]";
	mes "……悪いがお断りだ。";
	donpcevent getmdnpcname("ロキ#tnmloki01")+ "::OnTalk10";
	cutin "ep14_roki01",2;
	close2;
	cutin "ep14_roki01",255;
	hideonnpc getmdnpcname("モロクの領主#moclord01");
	hideonnpc getmdnpcname("領主の娘#tnm04");
	hideonnpc getmdnpcname("ロキ#tnmloki01");
	hideoffnpc getmdnpcname("ロキ#tnmloki02");
	end;
}

1@tnm3.gat,95,50,4	script	領主の娘#tnm04	941,{
	end;
OnTalk1:
	unittalk "領主の娘 : やめて下さい！　パパを殺さないで!!";
	end;
OnTalk2:
	unittalk "領主の娘 : 何か……何かの……間違いだわ……。";
	end;
OnTalk3:
	unittalk "領主の娘 : パパは……本当は……こんなことを……するような、人では……ない……の……。";
	end;
}

1@tnm3.gat,98,47,3	script	ロキ#tnmloki01	512,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ロキ]";
		mes "本当に身勝手な奴だな。";
		cutin "ep14_roki01",2;
		close2;
		cutin "ep14_roki01",255;
		end;
	}
	end;
OnTalk1:
	unittalk "ロキ : 時代遅れの腐った魔神なんかを呼び起こしてどうするつもりだ？";
	end;
OnTalk2:
	unittalk "ロキ : おかげで俺がまた来るはめになっちまったじゃねえか。";
	end;
OnTalk3:
	unittalk "ロキ : 黙れ！";
	end;
OnTalk4:
	unittalk "ロキ : 神々がどうであれ、魔族がどうであれ……お前はここで死ぬ。";
	end;
OnTalk5:
	unittalk "ロキ : それが俺の任務だからな。";
	end;
OnTalk6:
	unittalk "ロキ : 無論!!";
	end;
OnTalk7:
	unittalk "ロキ : マインドブラスター!!";
	end;
OnTalk8:
	unittalk "ロキ : なっ……!?";
	end;
OnTalk9:
	unittalk "ロキ : なぜかばった!?　人間は時折、理解不能な行動を起こす。これが心というものなのか？";
	end;
OnTalk10:
	unittalk "ロキ : ……悪いがお断りだ。";
	end;
}

1@tnm3.gat,0,0,0	script	#tnm3finalmob	139,{
OnStart:
	set 'mob,callmonster(getmdmapname("1@tnm3.gat"),97,75,"魔神の巨影",2942,getmdnpcname("#tnm3finalmob")+"::OnKilled");
	end;
OnCrossEff:
	if('mob) {
		getmapxy '@map$,'@x,'@y,3,'mob;
		unittalk 'mob,"魔神の巨影 : どうだ！　地獄の炎は!!";
		for(set '@i,3;'@i<=12;set '@i,'@i+3) {
			set '@effmob['@j+0],callmonster(getmdmapname("1@tnm3.gat"),'@x+'@i,'@y+'@i," ",2960);
			set '@effmob['@j+1],callmonster(getmdmapname("1@tnm3.gat"),'@x+'@i,'@y-'@i," ",2960);
			set '@effmob['@j+2],callmonster(getmdmapname("1@tnm3.gat"),'@x-'@i,'@y+'@i," ",2960);
			set '@effmob['@j+3],callmonster(getmdmapname("1@tnm3.gat"),'@x-'@i,'@y-'@i," ",2960);
			set '@j,'@j+4;
			sleep 300;
		}
		sleep 5000;
		for(set '@i,0;'@i<='@j;set '@i,'@i+4) {
			if('@effmob['@i+0])
				set '@dummy,removemonster('@effmob['@i+0]);
			if('@effmob['@i+1])
				set '@dummy,removemonster('@effmob['@i+1]);
			if('@effmob['@i+2])
				set '@dummy,removemonster('@effmob['@i+2]);
			if('@effmob['@i+3])
				set '@dummy,removemonster('@effmob['@i+3]);
			sleep 300;
		}
	}
	end;
OnCircleEff:
	if('mob) {
		getmapxy '@map$,'@x,'@y,3,'mob;
		unittalk 'mob,"魔神の巨影 : うわははははは!!";
		setarray '@dx,-3,3,9,9,6, 0,-12,-12,-9,-3,6;
		setarray '@dy,3,6,0,-3,-9,-12,-3, 3,9,15,18;
		for(set '@i,0;'@i<getarraysize('@dx);set '@i,'@i+1) {
			set '@effmob['@i],callmonster(getmdmapname("1@tnm3.gat"),'@x+'@dx['@i],'@y+'@dy['@i]," ",2960);
			sleep 300;
		}
		sleep 5000;
		for(set '@i,0;'@i<getarraysize('@dx);set '@i,'@i+1) {
			if('@effmob['@i])
				set '@dummy,removemonster('@effmob['@i]);
			sleep 300;
		}
	}
	end;
OnKilled:
	set 'mob,0;
	announce "魔神の巨影 : こ……こんなことが……この力は……ま……まさか……あなたは……あの……。",0x9,0xff0000,0x190,12,0,0;
	viewpoint 0,98,47,0,0xFF0000;
	donpcevent getmdnpcname("#tnm3finaltimer")+ "::OnStop";
	hideonnpc getmdnpcname("ロキ#tnmloki02");
	hideonnpc getmdnpcname("ロキの思念#hidden_loki");
	hideoffnpc getmdnpcname("ロキ#tnmloki03");
	hideoffnpc getmdnpcname("箱#tnmbosang");
	end;
}

1@tnm3.gat,0,0,0	script	#tnm3finaltimer	139,{
OnStart:
	initnpctimer;
	donpcevent getmdnpcname("#tnm3finalmob")+ "::OnCrossEff";
	end;
OnTimer40000:
	donpcevent getmdnpcname("#tnm3finalmob")+ "::OnCircleEff";
	end;
OnTimer80000:
	initnpctimer;
	donpcevent getmdnpcname("#tnm3finalmob")+ "::OnCrossEff";
	end;
OnStop:
	stopnpctimer;
	end;
}

1@tnm3.gat,98,47,3	script	ロキ#tnmloki02	512,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ロキ]";
		mes "今はお前たちのリーダーと話している。";
		cutin "ep14_roki01",2;
		close2;
		cutin "ep14_roki01",255;
		end;
	}
	if(getmercinfo(0)) {
		mes "[ロキ]";
		mes "……参ったな。";
		mes "俺と共にアイツを倒したいなら";
		mes "現在^4d4dff雇用中である傭兵との契約を";
		mes "取り消してくれ。^000000";
		cutin "ep14_roki01",2;
		close2;
		cutin "ep14_roki01",255;
		end;
	}
	if(TNM1_QUE < 21) {
		mes "[ロキ]";
		mes "……";
		mes "お前たちはいったいどこから現れた？";
		mes "まぁいい。";
		mes "領主はすでに人間ではなくなっている。";
		mes "アイツを倒すのが俺の任務だ。";
		mes "手伝ってくれ！";
		cutin "ep14_roki01",2;
		if(getmercinfo(0)) {
			next;
			mes "[ロキ]";
			mes "……";
			close2;
			cutin "ep14_roki01",255;
			end;
		}
		hideonnpc getmdnpcname("ロキ#tnmloki02");
		setquest 114800;
		compquest 114800;
		setpartyinmap TNM1_QUE,21;
		makemerc 2937,900;
		donpcevent getmdnpcname("#tnm3finalmob")+ "::OnStart";
		donpcevent getmdnpcname("ロキ#tnmloki02")+ "::OnStart";
		hideoffnpc getmdnpcname("ロキの思念#hidden_loki");
		close2;
		cutin "ep14_roki01",255;
		end;
	}
	if(checkquest(114800) & 0x8) {
		mes "[ロキ]";
		mes "……。";
		mes "どうした、もうあきらめるのか？";
		cutin "ep14_roki01",2;
		next;
		mes "[ロキ]";
		mes "アイツは倒さねばならない敵だ。";
		mes "このまま放っておくわけにはいかない。";
		mes "さあもう一度だ。";
		mes "やつをあるべき場所へ還そう。";
		next;
		hideonnpc getmdnpcname("ロキ#tnmloki02");
		makemerc 2937,900;
		mes "^4d4dff‐アサシンギルドのギロチンクロス";
		mes "　ロキが仲間に合流しました。";
		mes "　ロキが使うスキル";
		mes "　「マインドブラスター」を使用すると";
		mes "　魔族に変貌したモロクの領主に";
		mes "　ダメージを与えることが";
		mes "　できるようになります‐^000000";
		cutin "ep14_roki01",255;
		close2;
		hideoffnpc getmdnpcname("ロキの思念#hidden_loki");
		end;
	}
	// 未調査
	mes "[ロキ]";
	mes "……。";
	cutin "ep14_roki01",2;
	close2;
	cutin "ep14_roki01",255;
	end;
OnStart:
	initnpctimer;
	announce "魔神の巨影 : 虫けらのような奴らめ！",0x9,0x00ff00;
	end;
OnTimer2000:
	announce "魔神の巨影 : この私がお前らを生贄にして魔神を呼び起こしてやる!!",0x9,0x00ff00;
	end;
OnTimer5000:
	announce "ロキ : 奴は今、モロクの加護で不死身だ。",0x9,0x00ff00,0x190,16,0,0;
	end;
OnTimer8000:
	announce "ロキ : 俺がそれをマインドブラスターで断ち切る!!",0x9,0x00ff00,0x190,16,0,0;
	end;
OnTimer11000:
	announce "ロキ : その隙に一気に攻撃するんだ！",0x9,0x00ff00,0x190,16,0,0;
	end;
OnTimer14000:
	announce "ロキの持つスキル「マインドブラスター」を使用すると魔神の巨影にダメージを与えることができるようになります。",0x9,0x00ffff,0x190,16,0,0;
	end;
OnTimer22000:
	stopnpctimer;
	donpcevent getmdnpcname("#tnm3finaltimer")+ "::OnStart";
	end;
}

1@tnm3.gat,98,47,3	script	ロキの思念#hidden_loki	10043,{
	if(checkquest(114800) & 0x8 == 0) {
		mes "‐^ff0000ロキと契約した";
		mes "　最初のパーティーリーダーのみ";
		mes "　ロキを再び呼び出す事が可能です^000000‐";
		close;
	}
	if(getmercinfo(0)) {
		mes "[インフォメーション]";
		mes "　ロキの残影を右クリックし、";
		mes "　「状態表示」を選択。";
		mes "　「SKILL」を押した際に表示される";
		mes "　スキル「マインドブラスター」を";
		mes "　魔神の巨影に向かって使用すると";
		mes "　ダメージを与えられるようになる。";
		next;
		mes "[インフォメーション]";
		mes "　また、ロキの残影が";
		mes "　いなくなった場合";
		mes "　最初にロキと契約を結んだ";
		mes "　パーティーリーダーであれば";
		mes "　再びここで";
		mes "　仲間にすることが可能。";
		close;
	}
	hideonnpc getmdnpcname("ロキの思念#hidden_loki");
	hideoffnpc getmdnpcname("ロキ#tnmloki02");
	end;
}

1@tnm3.gat,98,47,3	script	ロキ#tnmloki03	512,{
	if(checkquest(114810) & 0x8 == 0) {
		mes "‐ロキに話しかけようとしたその時";
		mes "　不思議な力に身を包まれた。";
		misceffect 35,"";
		setquest 114810;
		compquest 114810;
		misceffect 58,"";
		mes "　^0000ff経験値を獲得！^000000‐";
		getexp 500000,0;
		getexp 500000,0;
		getexp 0,500000;
		next;
	}
	mes "[ロキ]";
	mes "……小賢しい。";
	mes "魔神の復活儀式は失敗に終わった。";
	mes "これで当分は問題ないだろう。";
	cutin "ep14_roki01",2;
	next;
	mes "[ロキ]";
	mes "しかし……死んだ領主の娘。";
	mes "どうしてあんな事ができる？";
	mes "俺としては理解出来ない行動だ。";
	next;
	if(TNM1_QUE < 23) {
		mes "‐箱を開封する事により、";
		mes "　ダンジョンの進行が可能となります‐";
		close;
	}
	mes "‐考え込んでいるロキに、";
	mes "　自分たちのことを話し、";
	mes "　帰る方法を聞いてみた‐";
	cutin "ep14_roki01",255;
	next;
	mes "[ロキ]";
	mes "そうか。お前たちは";
	mes "この時代の人間じゃないのか。";
	mes "このままここに居続けるのか？";
	mes "元の時代に戻りたいなら送ってやるぞ。";
	cutin "ep14_roki01",2;
	next;
	if(select("ここから出る","もう少しいる") == 2) {
		mes "[ロキ]";
		mes "時間の流れがそれたここには";
		mes "長居しない方がいい。";
		close2;
		cutin "ep14_roki01",255;
		end;
	}
	mes "[ロキ]";
	mes "いつかまた会える日が";
	mes "来るかもしれないな。";
	if(getmercinfo(0)) {
		next;
		mes "[ロキ]";
		mes "俺の意識の一部は少しの間";
		mes "残しておくことにしよう。";
		mes "……心、感情というのを……";
		mes "感じられる機会かもしれないしな。";
		setquest 114800;
		compquest 114800;
	}
	close2;
	cutin "ep14_roki01",255;
	warp "dali02.gat",134,112;
	end;
}

1@tnm3.gat,92,47,3	script	箱#tnmbosang	10005,{
	setpartyinmap TNM1_QUE,23;
	misceffect 10,getmdnpcname("箱#tnmbosang");
	hideonnpc getmdnpcname("箱#tnmbosang");
	// 退魔神の杖、退魔神の弓、退魔神の両手剣、退魔神のカタール、退魔神のハンマー、退魔神の短剣
	// 魔神の腕力1、魔神の知力1、魔神の迅速1、魔神の体力1、魔神の集中1、魔神の幸運1、魔神の腕力2、魔神の知力2、魔神の迅速2、魔神の体力2、魔神の集中2、魔神の幸運2
	setarray '@gain,2029,18131,21017,28009,28108,28707,4908,4911,4914,4917,4920,4923,4909,4912,4915,4918,4921,4924;
	setarray '@rate,10,10,10,10,10,10,4,4,4,4,4,4,1,1,1,1,1,1;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		for(set '@j,0; '@j<'@rate['@i]; set '@j,'@j+1) {
			set '@result['@k],'@gain['@i];
			set '@k,'@k+1;
		}
	}
	set '@x,92+rand(5)-2;
	set '@y,47+rand(5)-2;
	dropitem getmdmapname("1@tnm3.gat"),'@x,'@y,'@result[rand(getarraysize('@result))],1,0;
	set '@x,92+rand(5)-2;
	set '@y,47+rand(5)-2;
	dropitem getmdmapname("1@tnm3.gat"),'@x,'@y,'@result[rand(getarraysize('@result))],1,0;
	end;
}
