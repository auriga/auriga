//= Auriga Script ==============================================================
// Ragnarok Online Temple of Demon God Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
moro_cav.gat,41,73,4	script	守護者ニーズヘッグ#epeo	510,{
	if(!checkquest(201720) || !checkquest(201725)) {	// ビオスの島、モルスの洞窟未クリア
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "あの黄色い種と赤い花、";
		mes "それにこの樹……。";
		mes "モロクは何を考えているのでしょう。";
		next;
		mes "‐^ff0000魔神殿に入るには";
		mes "　ビオスの島、モルスの洞窟を";
		mes "　クリアする必要があります^000000‐";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(checkquest(116545)) {
		mes "[ニーズヘッグ]";
		mes "ついにモロクを倒しましたね。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "彼は欲張り過ぎました。";
		mes "生まれ変わって得た強大な力。";
		mes "この世界を飲み込み、";
		mes "新しい自身の世界を創るという野望。";
		mes "彼は何もかも自分の思い通りに";
		mes "したかったのでしょう。";
		cutin "ep14_nyd02", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "しかし、皆さんのおかげで";
		mes "彼の野望を打ち砕く事ができました。";
		mes "私達は種族を超えて協力することで、";
		mes "強大な絶望を退ける事ができたのです。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "司令官に報告できるように、";
		mes "私がモロク討伐の事実を";
		mes "伝えておきましょう。";
		mes "ご苦労様でした。";
		next;
		cutin "ep14_nyd04", 255;
		mes "‐^ff0000これ以降、魔神殿に入ることは";
		mes "　できなくなります。";
		mes "　司令官アジフに報告してから、";
		mes "　1回目の午前5時以降に、";
		mes "　再度魔神殿に入ることが";
		mes "　できるようになります^000000‐";
		if(checkquest(7593)) {
			setquest 7597;
			delquest 7593;
		}
		if(checkquest(116545)) {
			setquest 116545;
			delquest 116545;
		}
		close;
	}
	if(checkquest(7597)) {	// 討伐後未報告
		mes "[ニーズヘッグ]";
		mes "本当にお疲れ様でした。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "司令官に報告できるように、";
		mes "私がモロク討伐の事実を";
		mes "伝えておきましたので、";
		mes "報告に向かってください。";
		close2;
		cutin "ep14_nyd04", 255;
		end;
	}
	if(checkquest(7605)&0x4)	// 守護者との契約時間制限
		delquest 7605;
	if(checkquest(7593) == 0) {
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "申し訳ありませんが、";
		mes "司令官の許可なしには";
		mes "出入を許可することができません。";
		mes "魔神討伐を依頼された方のみ";
		mes "入場を許可しています。";
		next;
		mes "[ニーズヘッグ]";
		mes "司令官ヒバ・アジフ様に会って、";
		mes "依頼を受けてきて下さい。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(getonlinepartymember() < 1) {
		mes "[ニーズヘッグ]";
		mes "この先は一人では危険です。";
		mes "パーティーを結成してから来て下さい。";
		cutin "ep14_nyd01", 2;
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "皆さんの安全を守るため、";
		mes "魔神殿に入る申請は";
		mes "パーティーリーダーだけができます。";
		mes "あなたのパーティーのリーダーから";
		mes "私に話しかけるよう伝えてください。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	mes "[ニーズヘッグ]";
	mes "お待ちしていました。";
	mes "モロクがいる深層部まで案内します。";
	cutin "ep14_nyd04", 2;
	next;
	mes "[ニーズヘッグ]";
	mes "この樹は世界樹と似ていますね。";
	mes "モロクの目的が私の予想とは";
	mes "異なると良いのですが……。";
	cutin "ep14_nyd03", 2;
	next;
	mes "[ニーズヘッグ]";
	mes "ここから流れ出る魔力は";
	mes "一定間隔で息をしているかのような";
	mes "動きがあります。";
	mes "私はこの空間から";
	mes "深層部への道を開きます。";
	mes "深層部へ行く準備はできましたか？";
	cutin "ep14_nyd04", 2;
	next;
	if(select("準備ができた","行かない") == 2) {
		mes "[ニーズヘッグ]";
		mes "わかりました。";
		mes "出発するまで十分に準備する";
		mes "時間が必要でしょう。";
		mes "ゆっくり準備して来て下さい。";
		mes "私はここで待っています。";
		cutin "ep14_nyd04", 2;
		close2;
		cutin "ep14_nyd04", 255;
		end;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ニーズヘッグ]";
		mes "待ってください、これは……!?";
		mes "魔力の流れが変わりました。";
		mes "私たちの動きに気が付いたようです。";
		mes "もう少し様子を見てみましょう。";
		mes "私たちは招かれざる客ですから。";
		cutin "ep14_nyd01", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "勿論、私も今すぐ深層部へ行って";
		mes "モロクを戒めたいのですが、";
		mes "彼らに気付かれていると危険です。";
		mes "しばらく待ちましょう。";
		cutin "ep14_nyd02", 2;
		close2;
		cutin "ep14_nyd02", 255;
		end;
	}
	mdcreate "end_of_morocc";
	if(checkquest(7596))
		delquest 7596;
	mes "[ニーズヘッグ]";
	mes "……もう少しで入口が開きます。";
	mes "樹を通じて侵入してください。";
	mes "怖がらないで下さい。";
	mes "私も共に行きます。";
	cutin "ep14_nyd04", 2;
	close2;
	cutin "ep14_nyd04", 255;
	end;
OnInit:
	waitingroom "魔神殿生成", 0;
	end;
}

//============================================================
// 入場NPC
//------------------------------------------------------------
moro_cav.gat,45,75,0	script	世界樹に似た樹#eom_gate	844,{
	if(!checkquest(201720) || !checkquest(201725)) {	// ビオスの島、モルスの洞窟未クリア
		mes "[ニーズヘッグ]";
		mes "あの黄色い種と赤い花、";
		mes "それにこの樹……。";
		mes "モロクは何を考えているのでしょう。";
		cutin "ep14_nyd01", 2;
		next;
		mes "‐^ff0000魔神殿に入るには";
		mes "　ビオスの島、モルスの洞窟を";
		mes "　クリアする必要があります^000000‐";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(checkquest(7597)) {	// 討伐後未報告
		mes "[ニーズヘッグ]";
		mes "本当にお疲れ様でした。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "司令官に報告できるように、";
		mes "私がモロク討伐の事実を";
		mes "伝えておきましたので、";
		mes "報告に向かってください。";
		close2;
		cutin "ep14_nyd04", 255;
		end;
	}
	if(checkquest(116545)) {
		mes "[ニーズヘッグ]";
		mes "ついにモロクを倒しましたね。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "彼は欲張り過ぎました。";
		mes "生まれ変わって得た強大な力。";
		mes "この世界を飲み込み、";
		mes "新しい自身の世界を創るという野望。";
		mes "彼は何もかも自分の思い通りに";
		mes "したかったのでしょう。";
		cutin "ep14_nyd02", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "しかし、皆さんのおかげで";
		mes "彼の野望を打ち砕く事ができました。";
		mes "私達は種族を超えて協力することで、";
		mes "強大な絶望を退ける事ができたのです。";
		cutin "ep14_nyd04", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "司令官に報告できるように、";
		mes "私がモロク討伐の事実を";
		mes "伝えておきましょう。";
		mes "ご苦労様でした。";
		next;
		cutin "ep14_nyd04", 255;
		mes "‐^ff0000これ以降、魔神殿に入ることは";
		mes "　できなくなります。";
		mes "　司令官アジフに報告してから、";
		mes "　1回目の午前5時以降に、";
		mes "　再度魔神殿に入ることが";
		mes "　できるようになります^000000‐";
		setquest 7597;
		delquest 7593;
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(checkquest(7593) == 0) {
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "申し訳ありませんが、";
		mes "司令官の許可なしには";
		mes "出入を許可することができません。";
		mes "魔神討伐を依頼された方のみ";
		mes "入場を許可しています。";
		next;
		mes "[ニーズヘッグ]";
		mes "司令官ヒバ・アジフ様に会って、";
		mes "依頼を受けてきて下さい。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	mes "‐樹に手を当てると、";
	mes "　魔力の流れが感じられる。";
	mes "　この流れに身を任せれば";
	mes "　深層部に侵入できるのだろうか‐";
	next;
	if(select("入る","入らない") == 2) {
		cutin "ep14_nyd04", 2;
		mes "[ニーズヘッグ]";
		mes "わかりました。";
		mes "出発するまで十分に準備する";
		mes "時間が必要でしょう。";
		mes "ゆっくり準備して来て下さい。";
		mes "私はここで待っています。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(getonlinepartymember() < 1) {
		mes "[ニーズヘッグ]";
		mes "この先は一人では危険です。";
		mes "パーティーを結成してから来て下さい。";
		cutin "ep14_nyd01", 2;
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	switch(mdenter("end_of_morocc")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[end_of_morocc] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")", 0x9, 0x00ff99, 0x190, 12, 0, 0;
		if(!checkquest(96435))
			setquest 96435;
		//warp "1@eom.gat",101,16;
		//warp "1@eom_jp.gat",45,66;
		end;
	case 1:	// パーティー未加入
	case 2:	// ダンジョン未作成
		mes "[ニーズヘッグ]";
		mes "あなたのパーティーで入場許可が";
		mes "申請されていません。";
		mes "パーティーリーダーから正式に";
		mes "要請していただければ、私が";
		mes "魔神殿に通じる入口を開けましょう。";
		cutin "ep14_nyd01", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "皆さんの安全のため、";
		mes "ご協力をお願いします。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	default:	// その他エラー
		close;
	}
OnInit:
	waitingroom "魔神殿入場", 0;
	end;
}

1@eom_jp.gat,45,75,0	script	世界樹に似た樹#eom_jp	844,{
	if(checkquest(7598)) {
		if(checkquest(7598)&2 == 0 && checkquest(73730)&2) {
			mes "^ff0000[インフォメーション]";
			mes "再入場時間を過ぎているため";
			mes "進むことが出来ません‐^000000";
			close2;
			warp "moro_cav.gat",45,66;
			end;
		}
		if(checkquest(7598)&2) {
			delquest 7598;
			delquest 73730;
			setquest 7598;
			setquest 73730;
		}
	}
	else {
		setquest 7598;
		setquest 73730;
	}
	donpcevent getmdnpcname("EoMControl")+ "::OnStart";
	warp getmdmapname("1@eom.gat"),101,16;
	end;
OnInit:
	waitingroom "魔神殿入場",0;
	end;
}

//============================================================
// Floor 1
//------------------------------------------------------------
1@eom.gat,1,1,0	script	EoMControl	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;

	hideonnpc getmdnpcname("空になっている魂の器#sh");
	hideonnpc getmdnpcname("空になっている魂の器#ah");
	hideonnpc getmdnpcname("魔神の使徒・アハト#ah02");
	hideonnpc getmdnpcname("魂が満ちている器#shnaim");
	hideonnpc getmdnpcname("魂が満ちている器#ahat02");
	hideonnpc getmdnpcname("#gate_to_center");
	hideonnpc getmdnpcname("ロキ#eomloki01");
	hideonnpc getmdnpcname("ニーズヘッグ#eomnyd01");
	hideonnpc getmdnpcname("#eom_gate_to_ice");
	hideonnpc getmdnpcname("#eom_ice_to_center");
	hideonnpc getmdnpcname("モロク#mockid03");
	hideonnpc getmdnpcname("#eom_gate_to_last");
	hideonnpc getmdnpcname("固まった溶岩#01");
	hideonnpc getmdnpcname("固まった溶岩#02");
	hideonnpc getmdnpcname("#eom_fire_to_center");
	hideonnpc getmdnpcname("ロキ#op");
	hideonnpc getmdnpcname("ニーズヘッグ#op");
	hideonnpc getmdnpcname("#eom_bgm_change2");
	hideonnpc getmdnpcname("#eom_bgm_change3");
	hideonnpc getmdnpcname("#eom_bgm_change4");
	hideonnpc getmdnpcname("#morocc_god");
	hideonnpc getmdnpcname("#eom_quest");
	hideonnpc getmdnpcname("絶望の神モロク#04");
	hideonnpc getmdnpcname("ロキ#eomnyd04");
	hideonnpc getmdnpcname("ニーズヘッグ#eomnyd04");
	hideonnpc getmdnpcname("ニーズヘッグ#eomnyd02");
	end;
}

1@eom.gat,1,1,0	script	callmon#eom1	139,{
OnStart:
	initnpctimer;
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@event$,getmdnpcname("callmon#eom1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,102,30,"魔神の使徒・アハト",3105,'@event$);
	set '@mob2,callmonster('@mdmap$,98, 30,"魔神の破片",1918,'@event$);
	set '@mob3,callmonster('@mdmap$,100, 30,"魔神の破片",1918,'@event$);
	set '@mob4,callmonster('@mdmap$,104, 30,"魔神の破片",1918,'@event$);
	set '@mob5,callmonster('@mdmap$,106, 30,"魔神の破片",1918,'@event$);
	set '@mob6,callmonster('@mdmap$,102,40,"魔神の使徒・シナイム",3106,'@event$);
	set '@mob7,callmonster('@mdmap$,98, 40,"魔神の破片",1921,'@event$);
	set '@mob8,callmonster('@mdmap$,100, 40,"魔神の破片",1921,'@event$);
	set '@mob9,callmonster('@mdmap$,104, 40,"魔神の破片",1921,'@event$);
	set '@mob0,callmonster('@mdmap$,106, 40,"魔神の破片",1921,'@event$);
	if(getmapusers('@mdmap$) <= 2) {
		setmobhp '@mob1,5000000;
		setmobhp '@mob6,5000000;
	}
	end;
OnTimer3000:
	announce "アハト : この門の先に進むには、私とシナイムを倒しその魂を捧げる必要があります。", 0x9, 0x00ff00;
	end;
OnTimer6000:
	stopnpctimer;
	announce "アハト : さあ、我が主と会うに相応しい力を持っているか、私に見せてください！", 0x9, 0x00ff00;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom1")+ "::OnKilled");
	if('@count <= 0) {
		hideoffnpc getmdnpcname("空になっている魂の器#sh");
		hideoffnpc getmdnpcname("空になっている魂の器#ah");
		hideoffnpc getmdnpcname("魔神の使徒・アハト#ah02");
	}
	end;
}

1@eom.gat,101,43,3	script	魔神の使徒・アハト#ahat	493,{
	if(Sex)
		cutin "ep13_ahat_f", 2;
	else
		cutin "ep13_ahat_m", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[アハト]";
		mes "魔神殿へようこそ。";
		mes "あなたのお相手を務めることができ";
		mes "光栄です。";
		close2;
		cutin "ep13_ahat_f", 255;
		end;
	}
	if(DIC_2QUE < 16) {		// 猫耳と尻尾の男クエスト
		mes "[アハト]";
		mes "初めてお目にかかりますね。";
		mes "魔神の最初のしもべ、";
		mes "アハトと申します。";
		unittalk "アハト : 初めてお目にかかりますね。魔神の最初のしもべ、アハトと申します。";
	}
	else {
		mes "[アハト]";
		mes "結局ここまで来てしまいましたか。";
		mes "あなたという人は";
		mes "本当にしつこいですね。";
		unittalk "アハト : 結局ここまで来てしまいましたか。あなたという人は本当にしつこいですね。";
		next;
		mes "[アハト]";
		mes "フフフ……";
		mes "私がここにいることに";
		mes "驚いているようですね。";
		mes "しかし少しは予想していたのでは";
		mes "ないですか？";
		unittalk "アハト : フフフ……私がここにいることに驚いているようですね。しかし少しは予想していたのではないですか？";
		next;
		mes "[アハト]";
		mes "改めてご挨拶いたしましょう。";
		mes "魔神の最初のしもべ、";
		mes "アハトと申します。";
		unittalk "アハト : 改めてご挨拶いたしましょう。魔神の最初のしもべ、アハトと申します。";
	}
	next;
	mes "[アハト]";
	mes "我が主から";
	mes "あなたに客人としての資格があるか、";
	mes "私とシナイムで試すようにと";
	mes "命じられました。";
	unittalk "アハト : 我が主からあなたに客人としての資格があるか、私とシナイムで試すようにと命じられました。";
	next;
	mes "[アハト]";
	mes "あなたは自らの力で";
	mes "ここに来たと思っているようですが、";
	mes "それは大きな間違いです。";
	unittalk "アハト : あなたは自らの力でここに来たと思っているようですが、それは大きな間違いです。";
	next;
	mes "[アハト]";
	mes "すべては我が主の意思。";
	mes "まずはこの門を開くことができるか";
	mes "試してみましょう。";
	unittalk "アハト : すべては我が主の意思。まずはこの門を開くことができるか試してみましょう。";
	close2;
	setquest 7596;
	cutin "ep13_ahat_f", 255;
	mapwarp getmdmapname("1@eom.gat"),getmdmapname("1@eom.gat"),103,16;
	donpcevent getmdnpcname("callmon#eom1")+"::OnStart";
	hideonnpc;
	end;
}

1@eom.gat,101,55,3	script	魔神の使徒・アハト#ah02	493,{
	if(Sex)
		cutin "ep13_ahat_f", 2;
	else
		cutin "ep13_ahat_m", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[アハト]";
		mes "さすがですね。";
		mes "我が主の客人として";
		mes "相応しい実力です。";
		close2;
		cutin "ep13_ahat_f", 255;
		end;
	}
	mes "[アハト]";
	mes "クッ……ハハ……アハハハッ！";
	mes "さ、流石……我が主が一目おく";
	mes "相手ですね……これほどまでとは……。";
	unittalk "アハト : クッ……ハハ……アハハハッ！　さ、流石……我が主が一目おく相手ですね……これほどまでとは……。";
	next;
	mes "[アハト]";
	mes "どうやら……";
	mes "我々の役目はここまでのようです……。";
	unittalk "アハト : どうやら……我々の役目はここまでのようです……。";
	next;
	mes "[アハト]";
	mes "さあ、そこにある器に我々の魂を捧げ、";
	mes "先に進んでください。";
	mes "我が主に会う資格が充分、";
	mes "貴方達にあることは";
	mes "証明されたのですから……。";
	unittalk "アハト : さあ、そこにある器に我々の魂を捧げ先に進んでください。我が主に会う資格が充分、貴方達にあることは証明されたのですから……。";
	misceffect 231, getmdnpcname("空になっている魂の器#sh");
	misceffect 231, getmdnpcname("空になっている魂の器#ah");
	getitem 6713,1;
	getitem 6714,1;
	hideonnpc getmdnpcname("魔神の使徒・アハト#ah02");
	close2;
	cutin "ep13_ahat_f", 255;
	end;
}

1@eom.gat,98,56,0	script	空になっている魂の器#sh	844,{
	if(countitem(6714) < 1) {
		mes "‐扉を開くにはシナイムの魂で";
		mes "　この器を満たす必要がある‐";
		close;
	}
	mes "‐空になっている魂の器に";
	mes "　シナイムの魂を注入します‐";
	next;
	misceffect 72, getmdnpcname("空になっている魂の器#sh");
	progressbar 5;
	delitem 6714, 1;
	misceffect 6, getmdnpcname("空になっている魂の器#sh");
	hideonnpc getmdnpcname("空になっている魂の器#sh");
	hideoffnpc getmdnpcname("魂が満ちている器#shnaim");
	misceffect 6, getmdnpcname("魂が満ちている器#shnaim");
	misceffect 202, getmdnpcname("魂が満ちている器#shnaim");
	donpcevent getmdnpcname("#gate_to_center")+ "::OnStart";
	mes "‐器がシナイムの魂で満たされました‐";
	close;
}
1@eom.gat,98,56,0	script	魂が満ちている器#shnaim	844,{}

1@eom.gat,104,56,0	script	空になっている魂の器#ah	844,{
	if(countitem(6713) < 1) {
		mes "‐扉を開くにはアハトの魂で";
		mes "　この器を満たす必要がある‐";
		close;
	}
	mes "‐空になっている魂の器に";
	mes "　アハトの魂を注入します‐";
	next;
	misceffect 72, getmdnpcname("空になっている魂の器#ah");
	progressbar 5;
	delitem 6713, 1;
	misceffect 6, getmdnpcname("空になっている魂の器#ah");
	hideonnpc getmdnpcname("空になっている魂の器#ah");
	hideoffnpc getmdnpcname("魂が満ちている器#ahat02");
	misceffect 6, getmdnpcname("魂が満ちている器#ahat02");
	misceffect 202, getmdnpcname("魂が満ちている器#ahat02");
	donpcevent getmdnpcname("#gate_to_center")+ "::OnStart";
	mes "‐器がアハトの魂で満たされました‐";
	close;
}
1@eom.gat,104,56,0	script	魂が満ちている器#ahat02	844,{}

1@eom.gat,101,58,0	script	#gate_to_center	45,2,2,{
OnTouch:
	if(checkquest(7596))
		delquest 7596;
	warp getmdmapname("1@eom.gat"),98,115;
	end;
OnStart:
	if(!'flag) {
		set 'flag,1;
		end;
	}
	misceffect 231, getmdnpcname("#gate_to_center");
	misceffect 202, getmdnpcname("#gate_to_center");
	hideoffnpc getmdnpcname("#gate_to_center");
	end;
}

//============================================================
// Center Room
//------------------------------------------------------------
1@eom.gat,100,122,3	script	見慣れない少年#mockid01	10038,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		cutin "morocc_kid.bmp", 2;
		mes "[少年]";
		mes "僕は今とっても";
		mes "気分がいいんだ。";
		mes "だからここで攻撃したり、";
		mes "無粋なことはしないよ。";
		close2;
		cutin "morocc_kid.bmp", 255;
		end;
	}
	if(checkquest(201730)) {
		if(select("急ぐ","会話をする") == 1) {
			if('flag)
				close;
			hideonnpc getmdnpcname("見慣れない少年#mockid01");
			hideoffnpc getmdnpcname("ニーズヘッグ#eomnyd01");
			hideoffnpc getmdnpcname("#eom_gate_to_ice");
			misceffect 135, getmdnpcname("#eom_gate_to_ice");
			set 'dummy,sleep2(1000);
			misceffect 231, getmdnpcname("#eom_gate_to_ice");
			close;
		}
	}
	else {
		menu "会話をする",-;
	}
	if('flag)
		close;
	set 'flag,1;
	cutin "morocc_kid", 2;
	mes "[少年]";
	mes "ようこそ。";
	mes "どうかな？　この部屋は。";
	mes "僕はわりと気に入っているんだけど。";
	announce "少年 : ようこそ。どうかな？　この部屋は。僕はわりと気に入っているんだけど。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "["+strcharinfo(0)+"]";
	mes "君は？";
	unittalk getcharid(3),strcharinfo(0)+" : 君は？";
	next;
	mes "[少年]";
	mes "あれ？　分からないの？";
	announce "少年 : あれ？　分からないの？", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[少年]";
	mes "あはは、そっか！";
	mes "君たちは昔の僕しか";
	mes "知らないんだよね。";
	announce "少年 : あはは、そっか！　君たちは昔の僕しか知らないんだよね。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[少年]";
	mes "ごめんごめん。";
	mes "困らせるつもりはないんだ。";
	mes "僕は君たちが";
	mes "ここまで追いかけてきた目的だよ。";
	announce "少年 : ごめんごめん。困らせるつもりはないんだ。僕は君たちがここまで追いかけてきた目的だよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "……そう、僕がモロク。";
	mes "以後、お見知りおきを。";
	announce "モロク : ……そう、僕がモロク。以後、お見知りおきを。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "まさか、あの2人を倒すなんてね、";
	mes "あの2人は信頼していたのにな……。";
	announce "モロク : まさか、あの2人を倒すなんてね、あの2人は信頼していたのにな……。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "ねえ、どうしてそこまで";
	mes "実力がありながら冒険者なんて";
	mes "続けているの？";
	mes "もっと他に、相応しい生き方が";
	mes "あると、僕は思うよ。";
	announce "モロク : ねえ、どうしてそこまで実力がありながら冒険者なんて続けているの？　もっと他に、相応しい生き方があると、僕は思うよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	close2;
	cutin "morocc_kid", 255;
	donpcevent getmdnpcname("見慣れない少年#mockid01")+ "::OnStart";
	end;
OnStart:
	initnpctimer;
	hideoffnpc getmdnpcname("ロキ#eomloki01");
	hideoffnpc getmdnpcname("ニーズヘッグ#eomnyd01");
	end;
OnTimer1000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : フン。その相応しい場所をお前が用意するとでも言うのか？";
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : 笑わせるな。こいつらは自分達でその場所を、見つけることが出来る。";
	end;
OnTimer11000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : もっと分かりやすく言ってやろう。";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : お前が用意した場所など、こいつらには必要ない。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : そして、お前がこの世界に存在できる場所もな。";
	end;
OnTimer26000:
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd01")),"ニーズヘッグ : そうです、あなたは必要のない存在……。いいえ、存在してはいけないのです。";
	end;
OnTimer31000:
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd01")),"ニーズヘッグ : その証拠に、世界樹もあなたの存在を否定しています。";
	end;
OnTimer36000:
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd01")),"ニーズヘッグ : 世界樹イグドラシルの守護者たる、ニーズヘッグが命じます。……この世界から消えなさい!!";
	end;
OnTimer41000:
	announce "モロク : そんなに邪険にしないでほしいなあ。僕と君の仲じゃないか、ニーズヘッグ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer46000:
	announce "モロク : もしかしてもう忘れちゃったの？　僕の言葉にあんなに熱心に耳を傾けてくれたのに。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer51000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : ふざけるな！";
	misceffect 17, getmdnpcname("見慣れない少年#mockid01");
	end;
OnTimer56000:
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : ……チッ。流石に実体ではなかったか。";
	end;
OnTimer62000:
	announce "モロク : あれ、言ってなかったかな？　これは僕の幻。だから傷つけられないよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer68000:
	announce "モロク : せっかくお客様が来てくれたんだ。それなりのおもてなしをしないとね。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer74000:
	announce "モロク : そうだ！　アハトとシナイムには、もう一度チャンスをあげよう。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer80000:
	announce "モロク : 神となった僕の力で作り出した2匹の獣がいるんだけど……。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer86000:
	announce "モロク : そこにアハトとシナイムの魂を移植するのさ！　どうだい、面白そうだろう？", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer91000:
	announce "モロク : ちょっとした余興さ。僕の力で生まれ変わった2人の力を見せてあげるよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	end;
OnTimer94000:
	misceffect 6, getmdnpcname("見慣れない少年#mockid01");
	hideonnpc getmdnpcname("見慣れない少年#mockid01");
	unittalk getnpcid(0,getmdnpcname("ロキ#eomloki01")),"ロキ : 逃げるのか！";
	set getvariableofnpc('flag,getmdnpcname("ニーズヘッグ#eomnyd01")),1;
	end;
OnTimer96000:
	hideonnpc getmdnpcname("ロキ#eomloki01");
	hideoffnpc getmdnpcname("#eom_gate_to_ice");
	misceffect 135, getmdnpcname("#eom_gate_to_ice");
	end;
OnTimer97000:
	stopnpctimer;
	misceffect 231, getmdnpcname("#eom_gate_to_ice");
	end;
}

1@eom.gat,95,122,5	script	ロキ#eomloki01	512,{
	cutin "ep14_roki01", 2;
	mes "[ロキ]";
	mes "……フン。";
	mes "こんな茶番、早く終わらせて";
	mes "とっとと帰るぞ。";
	close2;
	cutin "ep14_roki01", 255;
	end;
}

1@eom.gat,94,120,5	script	ニーズヘッグ#eomnyd01	510,2,2,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		cutin "ep14_nyd01.bmp", 2;
		mes "[ニーズヘッグ]";
		mes "今回の決戦には私も協力します。";
		mes "私の分身を同行させたいのですが";
		mes "代表者の方とお話させて";
		mes "頂けませんか？";
		close2;
		cutin "ep14_nyd01.bmp", 255;
		end;
	}
	if('flag == 0) {
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "ご無事でしたか……。";
		mes "ここからは微力ながら、";
		mes "私たちもお手伝いします。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	if(getmercinfo(0)) {
		cutin "ep14_nyd01", 2;
		mes "[ニーズヘッグ]";
		mes "すでに傭兵がいますね……。";
		mes "現在契約中である傭兵との契約を切り、";
		mes "私を連れて行ってはくださいませんか？";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
	cutin "ep14_nyd01", 2;
	mes "[ニーズヘッグ]";
	mes "今回の決戦には私も協力します。";
	mes "あなたが望むならば";
	mes "私の分身を同行させましょう。";
	unittalk "ニーズヘッグ : 今回の決戦には私も協力します。あなたが望むならば私の分身を同行させましょう。";
	next;
	switch(select("一緒に行く","今はまだいい","^ff0000操作方法を確認する^000000")) {
	case 1:
		mes "[ニーズヘッグ]";
		mes "今こそ守護者の務めを";
		mes "果たしましょう。";
		unittalk "ニーズヘッグ : 今こそ守護者の務めを果たしましょう。";
		misceffect 72, getmdnpcname("ニーズヘッグ#eomnyd01");
		setnpcdisplay getmdnpcname("ニーズヘッグ#eomnyd01"),2131;
		setnpcdisplay getmdnpcname("ニーズヘッグ#eomnyd01"),510;
		hideonnpc getmdnpcname("ニーズヘッグ#eomnyd01");
		cutin "ep14_nyd01", 255;
		mes "‐^4d4dff守護者ニーズヘッグの分身が";
		mes "　仲間として参戦しました^000000‐";
		setquest 7605;
		makemerc 3087,1800;
		close;
	case 2:
		mes "[ニーズヘッグ]";
		mes "そうですか……。";
		mes "私の力が必要になったら";
		mes "いつでも言ってください。";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	case 3:
		mes "‐守護者の分身は";
		mes "　プレイヤーと共に戦ってくれる";
		mes "　NPCです。";
		mes "　30分経過するか、HPが0になると";
		mes "　いなくなってしまいます‐";
		next;
		mes "[操作方法]";
		mes "‐^ff0000[Alt]^000000キー+モンスターを左クリックで";
		mes "　クリックしたモンスターを";
		mes "　攻撃します。";
		mes "　^ff0000[Alt]^000000キー+地面を左クリックで";
		mes "　クリックした場所に移動します‐";
		next;
		mes "[ステータス]";
		mes "‐守護者の分身を右クリックすると";
		mes "　^0000ff[状態表示]^000000と^0000ff[待機]^000000が表示されます。";
		mes "　^0000ff[状態表示]^000000を選ぶと";
		mes "　ステータスウィンドウが";
		mes "　表示されます‐";
		next;
		mes "‐ステータスウィンドウ内の";
		mes "　^0000ff[解雇]^000000を選ぶと守護者の分身が";
		mes "　消滅します。";
		mes "　^0000ff[スキル]^000000は所持していないため、";
		mes "　なにも選ぶことができません‐";
		next;
		mes "‐^0000ff[待機]^000000を選ぶと攻撃をやめて";
		mes "　プレイヤーを追尾する";
		mes "　待機状態になります。";
		mes "　もう一度^0000ff[待機]^000000を選択すると";
		mes "　待機状態が解除されます‐";
		next;
		mes "‐一度守護者の分身を仲間にすると、";
		mes "　^ff00003時間経過するまで";
		mes "　再度仲間にすることができません^000000‐";
		close2;
		cutin "ep14_nyd01", 255;
		end;
	}
OnTouch:
	if('flag > 0)
		unittalk "ニーズヘッグ : 待って下さい！";
	end;
}

1@eom.gat,91,120,0	script	#eom_gate_to_ice	45,2,2,{
	if(!checkquest(96436))
		setquest 96436;
	warp getmdmapname("1@eom.gat"),56,88;
	end;
}

1@eom.gat,100,122,3	script	モロク#mockid03	10038,{
	cutin "morocc_kid", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[モロク]";
		mes "あはは！";
		mes "まだ生きてたんだね。驚いたよ。";
		close2;
		cutin "morocc_kid", 255;
		end;
	}
	mes "[モロク]";
	mes "あはは！　まだ生きてたんだね。";
	mes "驚いたよ。";
	announce "モロク : あはは！　まだ生きてたんだね。驚いたよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "正直、あの2匹に勝てるとは";
	mes "思ってなかったんだけど……。";
	announce "モロク : 正直、あの2匹に勝てるとは思ってなかったんだけど……。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "まあ、僕が直々に君たちを排除して、";
	mes "この世界を全て飲み込めばいいや。";
	announce "モロク : まあ、僕が直々に君たちを排除して、この世界を全て飲み込めばいいや。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	next;
	mes "[モロク]";
	mes "……さて、そろそろ始めようか。";
	mes "奥の部屋で待ってるよ。";
	announce "モロク : ……さて、そろそろ始めようか。奥の部屋で待ってるよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	close2;
	cutin "morocc_kid", 255;
	misceffect 57, getmdnpcname("モロク#mockid03");
	sleep 2000;
	misceffect 6, getmdnpcname("モロク#mockid03");
	hideonnpc getmdnpcname("モロク#mockid03");
	hideoffnpc getmdnpcname("#eom_gate_to_last");
	sleep 1000;
	misceffect 316, getmdnpcname("#eom_gate_to_last");
	donpcevent getmdnpcname("モロク#eom_master")+ "::OnStart";
	end;
}

1@eom.gat,98,127,0	script	#eom_gate_to_last	45,2,2,{
	if(!checkquest(96438))
		setquest 96438;
	warp getmdmapname("1@eom.gat"),102,178;
	end;
}

//============================================================
// Floor 2
//------------------------------------------------------------
1@eom.gat,56,88,0	script	#icemob01	139,1,1,{
OnTouch:
	hideonnpc;
	set '@mdmap$,getmdmapname("1@eom.gat");
	areamonster '@mdmap$,35,90,49,100,"フロストスパイダー",3088,5;
	end;
}

1@eom.gat,22,116,3	script	#icemob02	844,2,2,{
	end;
OnTouch:
	hideonnpc;
	set '@mdmap$,getmdmapname("1@eom.gat");
	areamonster '@mdmap$,22,113,26,117,"フロストスパイダー",3088,5;
	end;
}

1@eom.gat,53,134,5	script	#icemob03	844,2,2,{
	end;
OnTouch:
	hideonnpc;
	set '@mdmap$,getmdmapname("1@eom.gat");
	areamonster '@mdmap$,48,132,53,136,"フロストスパイダー",3088,5;
	end;
}

1@eom.gat,38,129,3	script	ブリナラネア#brinpc01	3091,10,10,{
	end;
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	announce "ブリナラネア : お待ちしていました。……私ですよ、シナイムです。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ブリナラネア : モロク様より頂いた新たな体……実に素晴らしい力を持っています。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ブリナラネア : ふふふ……気分はいかがですか？　あなたの命運もここまでです。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ブリナラネア : さあ、もう一度お相手しましょう。それではさようなら！", 0x9, 0xff0000, 0x190, 14, 0, 0;
	misceffect 236, getmdnpcname("ブリナラネア#brinpc01");
	hideonnpc getmdnpcname("ブリナラネア#brinpc01");
	donpcevent getmdnpcname("callmon#eom2")+ "::OnStart";
	initnpctimer;
	end;
OnTimer3000:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@event$,getmdnpcname("ブリナラネア#brinpc01")+"::OnKilled";
	set '@mob_id,getvariableofnpc('mob_id,getmdnpcname("callmon#eom2"));
	set '@mobhp,getmobhp('@mob_id);
	if('@mobhp < 25000000)
		set 'type,4;
	else if('@mobhp > 20000000 && '@mobhp < 30000000)
		set 'type,3;
	else if('@mobhp > 30000000 && '@mobhp < 40000000)
		set 'type,2;
	else if('@mobhp > 40000000 && '@mobhp < 50000000)
		set 'type,1;
	else
		set 'type,0;
	if('type == 0)
		initnpctimer;
	else if('type == 4)
		stopnpctimer;
	else {
		if('type == 1)
			unittalk '@mob_id,"ブリナラネア : ふふふ……私の眷属をお見せしましょう。";
		else if('type == 2)
			unittalk '@mob_id,"ブリナラネア : 眷属よ、敵を食らい尽くしなさい！";
		else if('type == 3)
			unittalk '@mob_id,"ブリナラネア : ふふふ……私の眷属はお腹を空かせているようです。";
		sleep 500;
		donpcevent getmdnpcname("callmon#eom2")+"::OnReSpawn";
		set '@mob_id,getvariableofnpc('mob_id,getmdnpcname("callmon#eom2"));
		mobuseskill '@mob_id,664,5,0,0,0,0;	// ワイドフリーズ
		sleep 1000;
		set '@count,getmapmobs('@mdmap$,'@event$ +'type);
		if('@count <= 0) {
			set '@dummy,getmapxy('@mdmap$,'@x,'@y,3,'@mob_id);
			areamonster '@mdmap$,'@x-5,'@y-5,'@x+5,'@y+5," ",3088,5,'@event$ +'type;
		}
		//sleep 15000;
		initnpctimer;
	}
	end;
OnKilled1:
OnKilled2:
OnKilled3:
	end;
}

1@eom.gat,1,1,0	script	callmon#eom2	139,{
OnStart:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@event$,getmdnpcname("callmon#eom2")+"::OnIceSpider";
	set 'mob_id,callmonster('@mdmap$,38,123,"ブリナラネア#brimob01",3091,'@event$);
	sleep 3000;
	announce "ブリナラネア : 先ほどまでの私と同じと思わないでください！ ", 0x9, 0xff0000, 0x190, 14, 0, 0;
	initnpctimer;
	end;
OnTimer10000:
	switch(rand(4)) {
	case 0:	donpcevent getmdnpcname("callmon#eom2")+ "::OnHeal";	break;
	case 1:	donpcevent getmdnpcname("callmon#eom2")+ "::OnJupitel";	break;
	case 2:	donpcevent getmdnpcname("callmon#eom2")+ "::OnThunder1";	break;
	case 3:	donpcevent getmdnpcname("callmon#eom2")+ "::OnThunder2";	break;
	}
	initnpctimer;
	end;
OnReSpawn:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@event$,getmdnpcname("callmon#eom2")+"::OnIceSpider";
	set '@mobhp,getmobhp('mob_id);
	set '@dummy,removemonster('mob_id);
	set 'mob_id,callmonster('@mdmap$,38,123,"ブリナラネア#brimob01",3091,'@event$);
	setmobhp 'mob_id,'@mobhp;
	end;
OnHeal:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"ブリナラネア : ふふふ……！";
	sleep 1000;
	mobuseskill 'mob_id,28,10,0,0,0,0;	// ヒール
	sleep 1000;
	mobuseskill 'mob_id,28,10,0,0,0,0;	// ヒール
	sleep 1000;
	mobuseskill 'mob_id,28,10,0,0,0,0;	// ヒール
	end;
OnJupitel:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"ブリナラネア : こういうのはいかがですか？";
	sleep 2000;
	mobuseskill 'mob_id,664,5,0,0,0,0;	// ワイドフリーズ
	sleep 2000;
	mobuseskill 'mob_id,84,28,0,0,0,1;	// ユピテルサンダー
	end;
OnThunder1:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"ブリナラネア : これが生まれ変わった私の力です！";
	sleep 1000;
	mobuseskill 'mob_id,664,5,0,0,0,0;	// ワイドフリーズ
	sleep 1500;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,21,20,'@x-3,'@y+3,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x+3,'@y+3,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x+3,'@y-3,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-3,'@y-3,0,0;	// サンダーストーム
	end;
OnThunder2:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"ブリナラネア : この素晴らしい魔力、身をもって味わいなさい！";
	sleep 1000;
	mobuseskill 'mob_id,664,5,0,0,0,0;	// ワイドフリーズ
	sleep 1500;
	mobuseskill 'mob_id,85,5,0,0,0,0;	// ロードオブヴァーミリオン
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,21,20,'@x-3,'@y+3,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+3,'@y+3,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+3,'@y-3,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-3,'@y-3,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y-4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y-4,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-5,'@y+5,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+5,'@y+5,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+5,'@y-5,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-5,'@y-5,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-6,'@y+6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+6,'@y+6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+6,'@y-6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-6,'@y-6,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-7,'@y+7,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+7,'@y+7,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+7,'@y-7,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-7,'@y-7,0,0;	// サンダーストーム
	end;
OnIceSpider:
	stopnpctimer;
	stopnpctimer getmdnpcname("ブリナラネア#brinpc01");
	announce "ニーズヘッグ : ブリナラネアが倒れ、出口が開いたようです！", 0x9, 0x00ff00, 0x190, 12, 0, 0;
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("ブリナラネア#brinpc01")+"::OnKilled1";
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("ブリナラネア#brinpc01")+"::OnKilled2";
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("ブリナラネア#brinpc01")+"::OnKilled3";
	hideonnpc getmdnpcname("#icemob02");
	hideonnpc getmdnpcname("#icemob03");
	hideoffnpc getmdnpcname("#eom_ice_to_center");
	hideoffnpc getmdnpcname("ニーズヘッグ#eomnyd02");
	donpcevent getmdnpcname("流れる溶岩#lavapond01")+ "::OnStart";
	donpcevent getmdnpcname("流れる溶岩#lavapond02")+ "::OnStart";
	end;
}

1@eom.gat,59,147,3	script	ニーズヘッグ#eomnyd02	510,{
	mes "[ニーズヘッグ]";
	mes "この先は灼熱の溶岩地帯が";
	mes "広がっているようです。";
	mes "この場所に自生する^ff0000永久霜^000000を";
	mes "いくつか採取してお持ちください。";
	mes "きっと役に立つでしょう。";
	next;
	mes "[ニーズヘッグ]";
	mes "なにはともあれ、";
	mes "大変な戦いでしたね……。";
	mes "私から出来ることは多くありませんが、";
	mes "守護者として貴方に、";
	mes "イグドラシルの加護を……。";
	misceffect 313,"";
	percentheal 100,100;
	close;
}

1@eom.gat,67,149,0	script	#eom_ice_to_center	45,2,2,{
	if(!checkquest(96437))
		setquest 96437;
	warp getmdmapname("1@eom.gat"),136,93;
	end;
}

//============================================================
// Floor 3
//------------------------------------------------------------
1@eom.gat,148,100,3	script	ロキ#flamewolf	512,5,5,{
	mes "[ロキ]";
	mes "あの溶岩……。";
	mes "永久霜の強力な冷気なら";
	mes "止められるかもしれないな。";
	close;
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	sleep 1000;
	announce "ロキ : くっ、何て熱気だ！　体力が奪われていく……！", 0x9, 0x00ff00;
	sleep 3000;
	announce "ロキ : あの溶岩を何とかしなければ不味いな……。", 0x9, 0x00ff00;
	sleep 3000;
	announce "ロキ : おい、溶岩に永久霜を使ってみてくれ。あれなら溶岩を止められるかもしれない。", 0x9, 0x00ff00;
	sleep 2000;
	hideonnpc getmdnpcname("ロキ#flamewolf");
	end;
}

1@eom.gat,168,133,3	script	ムスペルスコール#npc	3092,10,10,{
	end;
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	announce "ムスペルスコール : ……先ほどぶりですね。アハトです。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ムスペルスコール : 一度滅びた身にも関わらず、このような姿になり、またあなたと相対するとは……。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ムスペルスコール : しかし、我が主の望みとあらば、再びこの身が果てるまで尽くしましょう。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	sleep 3000;
	announce "ムスペルスコール : さあ、参りましょう。私たちの運命に終止符を打つのです！", 0x9, 0xff0000, 0x190, 14, 0, 0;
	misceffect 225;
	hideonnpc;
	donpcevent getmdnpcname("callmon#eom3")+ "::OnStart";
	sleep 1000;
	initnpctimer;
	end;
OnTimer10000:
	initnpctimer;
	switch(rand(4)) {
	case 0:	donpcevent getmdnpcname("callmon#eom3")+ "::OnHellBurning1"; break;
	case 1:	donpcevent getmdnpcname("callmon#eom3")+ "::OnHellBurning2"; break;
	case 2:	donpcevent getmdnpcname("callmon#eom3")+ "::OnHellBurning3"; break;
	}
}

1@eom.gat,1,1,0	script	callmon#eom3	139,{
OnStart:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@event1$,getmdnpcname("callmon#eom3")+"::OnFlameWolf";
	set '@event2$,getmdnpcname("callmon#eom3")+"::OnKilled1";
	set '@mob2,callmonster('@mdmap$,162,130,"狂気のカーサ",3089,'@event2$);
	set '@mob3,callmonster('@mdmap$,165,130,"狂気のカーサ",3089,'@event2$);
	set '@mob4,callmonster('@mdmap$,168,130,"狂気のカーサ",3089,'@event2$);
	set '@mob5,callmonster('@mdmap$,171,130,"狂気のカーサ",3089,'@event2$);
	set '@mob6,callmonster('@mdmap$,174,130,"狂気のカーサ",3089,'@event2$);
	set '@mob7,callmonster('@mdmap$,162,133,"狂気のカーサ",3089,'@event2$);
	set '@mob8,callmonster('@mdmap$,165,133,"狂気のカーサ",3089,'@event2$);
	set '@mob9,callmonster('@mdmap$,168,133,"狂気のカーサ",3089,'@event2$);
	set '@mob10,callmonster('@mdmap$,171,133,"狂気のカーサ",3089,'@event2$);
	set '@mob11,callmonster('@mdmap$,174,133,"狂気のカーサ",3089,'@event2$);
	announce "ムスペルスコール : 灼熱の炎よ、全てを燃やし尽くしなさい！", 0x9, 0xff0000, 0x190, 14, 0, 0;
	set 'mob1,callmonster('@mdmap$,167,133,"ムスペルスコール#01",3092,'@event1$);
	mobuseskill 'mob1,81,10,0,0,0,0;	// サイトラッシャー
	sleep 1000;
	unittalk 'mob1,"ムスペルスコール : 全ては我が主の意のままに！";
	initnpctimer;
	sleep 2000;
	mobuseskill 'mob1,724,1,0,0,0,0;	// ファイアストーム
	end;
OnTimer7000:
	unittalk 'mob1,"ムスペルスコール : 我が主の作りだした灼熱の炎を甘く見ないことです！";
	callsub L_LavaHeal,1,156,117;
	sleep 2000;
	mobuseskill 'mob1,724,1,0,0,0,0;	// ファイアストーム
	if(getmapmobs(getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom3")+"::OnKilled1") < 6)
		areamonster getmdmapname("1@eom.gat"),156-3,117-3,156+3,117+3,"狂気のカーサ",3089,3,getmdnpcname("callmon#eom3")+"::OnKilled1";
	end;
OnTimer10000:
	callsub L_LavaHeal,2,180,129;
	sleep 2000;
	mobuseskill 'mob1,721,1,0,0,0,0;	// ワイドウェブ
	mobuseskill 'mob1,724,1,0,0,0,0;	// ファイアストーム
	if(getmapmobs(getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom3")+"::OnKilled1") < 6)
		areamonster getmdmapname("1@eom.gat"),180-3,129-3,180+3,129+3,"狂気のカーサ",3089,3,getmdnpcname("callmon#eom3")+"::OnKilled1";
	end;
OnTimer13000:
	donpcevent getmdnpcname("callmon#eom3")+"::OnWarpReturn";
	if(getmobhp('mob1) > 22500000 && rand(2))
		initnpctimer;
	end;
OnTimer27000:
	stopnpctimer;
	if(getmobhp('mob1) > 22500000)
		initnpctimer;
	end;
L_Move:
	set 'hp,getmobhp('mob1);
	set '@dummy,removemonster('mob1);
	set 'mob1,callmonster(getmdmapname("1@eom.gat"),getarg(0),getarg(1),"ムスペルスコール#01",3092,getmdnpcname("callmon#eom3")+"::OnFlameWolf");
	setmobhp 'mob1,'hp;
	set getvariableofnpc('mob_id,getmdnpcname("ムスペルスコール#npc")),'mob1;
	return;
L_LavaHeal:
	if(getmobhp('mob1) < 1) end;
	callsub L_Move,getarg(1),getarg(2);
	if(getvariableofnpc('flag,getmdnpcname("固まった溶岩#0")+getarg(0)) != 1) {
		announce "ロキ : ムスペルスコールが溶岩を利用して回復をしようとしているぞ！", 0x9, 0x00ff00;
		for(set '@i,0; '@i<=8; set '@i,'@i+1) {
			mobuseskill 'mob1,28,10,0,0,0,0;	// ヒール
			sleep 100;
		}
	}
	return;
OnWarpReturn:
	if(getmobhp('mob1) < 1) end;
	unittalk 'mob1,"ムスペルスコール : さすが、一度は私を倒しただけのことはありますね。ですが、まだです!!";
	set 'hp,getmobhp('mob1);
	set '@dummy,removemonster('mob1);
	set 'mob1,callmonster(getmdmapname("1@eom.gat"),168,121,"ムスペルスコール#01",3092,getmdnpcname("callmon#eom3")+"::OnFlameWolf");
	setmobhp 'mob1,'hp;
	set getvariableofnpc('mob_id,getmdnpcname("ムスペルスコール#npc")),'mob1;
	mobuseskill 'mob1,252,1,0,0,0,0;	// リフレクトシールド
	end;
OnHellBurning1:
	if(getmobhp('mob1) < 1) end;
	unittalk 'mob1,"ムスペルスコール : 灼熱の海に飲まれなさい！";
	sleep 1000;
	mobuseskill 'mob1,724,3,0,0,0,0;	// ファイアストーム
	sleep 2000;
	mobuseskill 'mob1,81,10,0,0,0,0;	// サイトラッシャー
	end;
OnHellBurning2:
	if(getmobhp('mob1) < 1) end;
	mobuseskill 'mob1,724,3,0,0,0,0;	// ファイアストーム
	unittalk 'mob1,"ムスペルスコール : 灼熱の炎に抱かれなさい！";
	sleep 2000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob1);
	mobuseskillpos 'mob1,80,10,'@x-2,'@y+2,0,0;	// ファイアーピラー
	sleep 2000;
	mobuseskillpos 'mob1,80,10,'@x+2,'@y+2,0,0;	// ファイアーピラー
	sleep 2000;
	mobuseskillpos 'mob1,80,10,'@x-2,'@y-2,0,0;	// ファイアーピラー
	sleep 2000;
	mobuseskillpos 'mob1,80,10,'@x+2,'@y-2,0,0;	// ファイアーピラー
	end;
OnHellBurning3:
	if(getmobhp('mob1) < 1) end;
	unittalk 'mob1,"ムスペルスコール : 灼熱の隕石で朽ち果てなさい!!";
	sleep 1000;
	mobuseskill 'mob1,724,3,0,0,0,0;	// ファイアストーム
	set '@mdmap$,getmdmapname("1@eom.gat");
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob1);
	monster '@mdmap$,'@x+3,'@y+3," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-3,'@y-3," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x+3,'@y-3," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-3,'@y+3," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	sleep 200;
	monster '@mdmap$,'@x+6,'@y+6," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-6,'@y-6," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x+6,'@y-6," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-6,'@y+6," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	sleep 200;
	monster '@mdmap$,'@x+9,'@y+9," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-9,'@y-9," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x+9,'@y-9," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-9,'@y+9," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	sleep 200;
	monster '@mdmap$,'@x+13,'@y-13," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-13,'@y+13," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x+13,'@y-13," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	monster '@mdmap$,'@x-13,'@y+13," ",2960,1,getmdnpcname("callmon#eom3")+"::OnKilled2";
	sleep 4400;
	mobuseskillpos 'mob1,83,5,'@x,'@y+5,0,0;	// メテオストーム
	sleep 1000;
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom3")+"::OnKilled2";
	sleep 1000;
	mobuseskillpos 'mob1,83,5,'@x,'@y-5,0,0;	// メテオストーム
	sleep 2000;
	mobuseskillpos 'mob1,83,5,'@x,'@y+10,0,0;	// メテオストーム
	sleep 2000;
	mobuseskillpos 'mob1,83,5,'@x,'@y+10,0,0;	// メテオストーム
	end;
OnFlameWolf:
	stopnpctimer;
	stopnpctimer getmdnpcname("ムスペルスコール#npc");
	announce "ロキ : ムスペルスコールが倒れ、出口が開いたようだ。", 0x9, 0x00ff00;
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom3")+"::OnKilled1";
	hideonnpc getmdnpcname("流れる溶岩#lavapond01");
	hideonnpc getmdnpcname("固まった溶岩#01");
	hideonnpc getmdnpcname("流れる溶岩#lavapond02");
	hideonnpc getmdnpcname("固まった溶岩#02");
	stopnpctimer getmdnpcname("流れる溶岩#lavapond01");
	stopnpctimer getmdnpcname("固まった溶岩#01");
	stopnpctimer getmdnpcname("流れる溶岩#lavapond02");
	stopnpctimer getmdnpcname("固まった溶岩#02");
	hideoffnpc getmdnpcname("ロキ#flameend");
	hideoffnpc getmdnpcname("#eom_fire_to_center");
	hideonnpc getmdnpcname("#eom_gate_to_ice");
	hideoffnpc getmdnpcname("モロク#mockid03");
	end;
OnKilled1:
OnKilled2:
	end;
}

1@eom.gat,154,119,0	script	流れる溶岩#lavapond01	844,{
	if(countitem(22566) == 0) {
		mes "‐溶岩が流れ出している。";
		mes "　普通の氷で止めるのは難しそうだ‐";
		close;
	}
	mes "‐永久霜で流れ出す溶岩を";
	mes "　止めることができます‐";
	next;
	if(select("霜を使用する","使用しない") == 2) {
		mes "‐永久霜を使うのをやめた‐";
		close;
	}
	delitem 22566,1;
	stopnpctimer;
	donpcevent getmdnpcname("固まった溶岩#01")+ "::OnStart";
	close;
OnStart:
OnTimer1000:
	initnpctimer;
	misceffect 97;
	end;
}

1@eom.gat,154,119,0	script	固まった溶岩#01	844,{
	end;
OnStart:
	set 'flag,1;
	initnpctimer;
	hideonnpc getmdnpcname("流れる溶岩#lavapond01");
	hideoffnpc getmdnpcname("固まった溶岩#01");
	hideonnpc getmdnpcname("#lavazone11");
	hideonnpc getmdnpcname("#lavazone12");
	hideonnpc getmdnpcname("ロキ#flamewolf");
	end;
OnTimer180000:
	set 'flag,0;
	stopnpctimer;
	announce "ロキ : 霜の効果が切れたか……。また溶岩が流れ始めたぞ！", 0x9, 0x00ff00, 0x190, 12, 0, 0;
	hideonnpc getmdnpcname("固まった溶岩#01");
	hideoffnpc getmdnpcname("流れる溶岩#lavapond01");
	hideoffnpc getmdnpcname("#lavazone11");
	hideoffnpc getmdnpcname("#lavazone12");
	end;
}

1@eom.gat,161,122,0	script	#lavazone11	139,10,10,{
	percentheal -3,0;
	misceffect 310,"";
	end;
}

1@eom.gat,161,102,0	script	#lavazone12	139,10,10,{
	percentheal -3,0;
	misceffect 310,"";
	end;
}

1@eom.gat,182,129,0	script	流れる溶岩#lavapond02	844,{
	if(countitem(22566) == 0) {
		mes "‐溶岩が流れ出している。";
		mes "　普通の氷で止めるのは難しそうだ‐";
		close;
	}
	mes "‐永久霜で流れ出す溶岩を";
	mes "　止めることができます‐";
	next;
	if(select("霜を使用する","使用しない") == 2) {
		mes "‐永久霜を使うのをやめた‐";
		close;
	}
	delitem 22566,1;
	stopnpctimer;
	donpcevent getmdnpcname("固まった溶岩#02")+ "::OnStart";
	close;
OnStart:
OnTimer1000:
	initnpctimer;
	misceffect 97;
	end;
}

1@eom.gat,182,129,0	script	固まった溶岩#02	844,{
	end;
OnStart:
	set 'flag,1;
	initnpctimer;
	hideonnpc getmdnpcname("流れる溶岩#lavapond02");
	hideoffnpc getmdnpcname("固まった溶岩#02");
	hideonnpc getmdnpcname("#lavazone21");
	hideonnpc getmdnpcname("#lavazone22");
	hideonnpc getmdnpcname("ロキ#flamewolf");
	end;
OnTimer180000:
	set 'flag,0;
	stopnpctimer;
	announce "ロキ : 霜の効果が切れたか……。また溶岩が流れ始めたぞ！", 0x9, 0x00ff00, 0x190, 12, 0, 0;
	hideonnpc getmdnpcname("固まった溶岩#02");
	hideoffnpc getmdnpcname("流れる溶岩#lavapond02");
	hideoffnpc getmdnpcname("#lavazone21");
	hideoffnpc getmdnpcname("#lavazone22");
	end;
}

1@eom.gat,163,150,0	script	#lavazone21	139,10,10,{
	percentheal -3,0;
	misceffect 310,"";
	end;
}

1@eom.gat,163,150,0	script	#lavazone22	139,10,10,{
	percentheal -3,0;
	misceffect 310,"";
	end;
}

1@eom.gat,151,155,3	script	ロキ#flameend	512,{
	mes "[ロキ]";
	mes "……侮っていたな。";
	mes "あいつがこれ程まで";
	mes "強力なモンスターを";
	mes "生み出すことが出来るとはな。";
	next;
	mes "[ロキ]";
	mes "今回も大変な戦いだったな。";
	mes "だがこれからが本当の闘いだ。";
	mes "その前に傷を癒してやる。";
	misceffect 313,"";
	percentheal 100,100;
	close;
}

1@eom.gat,147,156,0	warp	#eom_fire_to_center	2,2,1@eom.gat,98,115

//============================================================
// Floor 4
//------------------------------------------------------------
1@eom.gat,101,178,0	script	#eom_bgm_change1	139,2,2,{
	musiceffect "997";
	end;
}

1@eom.gat,101,194,0	script	#eom_bgm_change2	139,20,20,{
	musiceffect "158";
	end;
}

1@eom.gat,101,194,0	script	#eom_bgm_change3	139,20,20,{
	musiceffect "997";
	end;
}

1@eom.gat,101,194,0	script	#eom_bgm_change4	139,20,20,{
	musiceffect "103";
	end;
}

1@eom.gat,98,182,0	script	#eom_fire_left1	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,105,182,0	script	#eom_fire_right1	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,98,188,0	script	#eom_fire_left2	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,105,188,0	script	#eom_fire_right2	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,98,194,0	script	#eom_fire_left3	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,105,194,0	script	#eom_fire_right3	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,98,200,0	script	#eom_fire_left4	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,105,200,0	script	#eom_fire_right4	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,98,206,0	script	#eom_fire_left5	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,105,206,0	script	#eom_fire_right5	139,10,0,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	misceffect 47;
	end;
}

1@eom.gat,104,204,1	script	ロキ#op	512,{
	// 未調査
}

1@eom.gat,99,204,7	script	ニーズヘッグ#op	510,{
	// 未調査
}

1@eom.gat,102,209,0	script	#event_eom_talk	139,3,3,{
OnTouch:
	if('flag)
		end;
	set 'flag,1;
	initnpctimer;
OnTimer2000:
	misceffect 47,getmdnpcname("#eom_fire_left1");
	misceffect 47,getmdnpcname("#eom_fire_left2");
	misceffect 47,getmdnpcname("#eom_fire_left3");
	misceffect 47,getmdnpcname("#eom_fire_left4");
	misceffect 47,getmdnpcname("#eom_fire_left5");
	misceffect 47,getmdnpcname("#eom_fire_right1");
	misceffect 47,getmdnpcname("#eom_fire_right2");
	misceffect 47,getmdnpcname("#eom_fire_right3");
	misceffect 47,getmdnpcname("#eom_fire_right4");
	misceffect 47,getmdnpcname("#eom_fire_right5");
	initnpctimer;
	end;
OnStart:
	announce "モロク : よく来たね。人間如きがここまで来れるなんて驚いたよ。", 0x9, 0xff0000, 0x190, 14, 0, 0;
	hideonnpc getmdnpcname("#eom_bgm_change1");
	hideoffnpc getmdnpcname("#eom_bgm_change2");
	sleep 3000;
	announce "モロク : ふふっ、僕の目的が気になるのかい？　それはね、世界の創造さ。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : かつてユミルがしたように僕も世界を作りかえるんだよ！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : その為の力はすべて揃った。僕は今からこの世界を滅ぼし、新たな世界を創造して神として君臨するのさ！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	misceffect 90,getmdnpcname("モロク#eom_master");
	sleep 2000;
	announce "モロク : あははは！　無駄だよ無駄。君は僕に触れる事すら出来ない。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : この障壁が見えるだろう？　これがある限り、君たちは僕に触れられない。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 残念だったね。そこで世界の終焉と再誕を見届けるがいい！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : まずは手始めにフレイムヴァレーに居るゴミ共を掃除をしようか。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 君はそこで仲間の死にゆく様を指をくわえて見ていると良い！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 僕が！　僕こそが新世界の神！　魔神モロクだ！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 2000;
	misceffect 59,getmdnpcname("モロク#eom_master");
	stopnpctimer getmdnpcname("モロク#eom_master");
	stopnpctimer getmdnpcname("#event_eom_talk");
	sleep 3000;
	misceffect 90,getmdnpcname("モロク#eom_master");
	sleep 5000;
	misceffect 135,getmdnpcname("モロク#eom_master");
	sleep 1000;
	announce "モロク : これは……障壁が壊れた？", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : ああ、僕としたことが、君たちの事を失念していたよ。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	hideoffnpc getmdnpcname("ロキ#op");
	hideoffnpc getmdnpcname("ニーズヘッグ#op");
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : 全てが思い通りになると思うなよ、モロク！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#op")),"ニーズヘッグ : 障壁は破壊しました。あとはあなたを倒すだけです！";
	sleep 3000;
	announce "モロク : 僕を倒す？　神であるこの僕を？", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 調子に乗るな！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	misceffect 30,getmdnpcname("ロキ#op");
	misceffect 30,getmdnpcname("ニーズヘッグ#op");
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : くっ……。";
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#op")),"ニーズヘッグ : うぅ……。";
	sleep 3000;
	announce "モロク : おやおや、たった一撃で満身創痍じゃないか。それで僕を倒せるのかい？", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : ふっ……くくく。";
	sleep 3000;
	announce "モロク : ……何がおかしいんだい？", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : 慢心していると、また負けるぞ、モロク。";
	sleep 3000;
	announce "モロク : ……面白い冗談だね、この死に損ない！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 君が戦えない今、誰が僕に敵うと言うんだい？", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : 確かに俺たちにはもう戦う力は残っていない。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ロキ#op")),"ロキ : だが、お前を倒す奴はここにいる！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#op")),"ニーズヘッグ : この世界の未来を……あなたに託します！";
	sleep 1000;
	hideonnpc getmdnpcname("ロキ#op");
	hideonnpc getmdnpcname("ニーズヘッグ#op");
	sleep 2000;
	announce "モロク : さて、君がどれほどの力を持っているのか見せて貰うよ。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : 君たち人間との戦いも、これで閉幕だ。", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 3000;
	announce "モロク : さあ、神に仇なす脆弱なる者よ！　世界再誕の最初の贄となるがいい！", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 2000;
	hideonnpc getmdnpcname("モロク#eom_master");
	donpcevent getmdnpcname("callmon#eom4")+ "::OnStart";
	end;
}

1@eom.gat,102,209,3	script	モロク#eom_master	10038,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		cutin "morocc_kid.bmp", 2;
		mes "[モロク]";
		mes "ここまで来たからには";
		mes "僕が直接相手をしてあげるよ。";
		mes "君たちは神の手によって";
		mes "滅ぼされるんだ、光栄だろう？";
		next;
		mes "[モロク]";
		mes "覚悟が出来たらリーダーを通じて";
		mes "僕に教えてね。";
		mes "それまでは待っててあげるよ。";
		mes "僕は優しいからね。";
		mes "僅かな余生を満喫するといいよ。";
		close2;
		cutin "morocc_kid.bmp", 255;
		end;
	}
	if('flag == 0) {
		if(checkquest(201730)) {
			if(select("急ぐ","会話をする") == 1) {
				stopnpctimer getmdnpcname("モロク#eom_master");
				stopnpctimer getmdnpcname("#event_eom_talk");
				hideonnpc getmdnpcname("#eom_bgm_change1");
				hideoffnpc getmdnpcname("#eom_bgm_change2");
				hideonnpc getmdnpcname("モロク#eom_master");
				donpcevent getmdnpcname("callmon#eom4")+ "::OnStart";
				close;
			}
			set 'flag,1;
			donpcevent getmdnpcname("#event_eom_talk")+ "::OnStart";
			close;
		}
		menu "会話をする",-;
		set 'flag,1;
		donpcevent getmdnpcname("#event_eom_talk")+ "::OnStart";
		close;
	}
	end;
OnStart:
OnTimer1000:
	initnpctimer;
	misceffect 252;
	end;
}

1@eom.gat,1,1,0	script	callmon#eom4	139,{
OnStart:
	initnpctimer;
	set 'mob_id,callmonster(getmdmapname("1@eom.gat"),102,209,"再生の半魔神#mk01",3096,getmdnpcname("callmon#eom4")+"::OnKilled");
	mobuseskill 'mob_id,83,10,0,0,0,0;	// メテオストーム
	mobuseskill 'mob_id,83,10,0,0,0,0;	// メテオストーム
	end;
OnTimer3000:
OnTimer6000:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@mobhp,getmobhp('mob_id);
	if('@mobhp < 1) {
		stopnpctimer;
		end;
	}
	if('@mobhp < 18000000 && 'flag == 2) {
		set '@count,getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled4");
		if('@count < 3) {
			set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
			monster '@mdmap$,'@x-1,'@y,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster '@mdmap$,'@x,'@y-1,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster '@mdmap$,'@x+1,'@y,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster '@mdmap$,'@x,'@y+1,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
		}
	}
	end;
OnTimer10000:
	set '@mdmap$,getmdmapname("1@eom.gat");
	set '@mobhp,getmobhp('mob_id);
	set '@count,getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled2") + getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled3");
	if('@mobhp < 1) {
		stopnpctimer;
		end;
	}
	if('@count > 0) {
		initnpctimer;
		end;
	}
	else if('@mobhp < 30000000 && 'flag == 0) {
		set 'flag,1;
		//stopnpctimer;
		unittalk 'mob_id,"再生の半魔神 : このまま終わらせはしないよ！";
		set '@dummy,removemonster('mob_id);
		set 'mob_id,callmonster(getmdmapname("1@eom.gat"),102,209,"再生の半魔神#mk01",3096,getmdnpcname("callmon#eom4")+"::OnKilled");
		setmobhp 'mob_id,'@mobhp;
		set 'mob_id2,callmonster(getmdmapname("1@eom.gat"),114,198,"太古のモロク#origin",3098,getmdnpcname("callmon#eom4")+"::OnKilled2");
		set 'mob_id3,callmonster(getmdmapname("1@eom.gat"),86,199,"安息のモロク#rest",3099,getmdnpcname("callmon#eom4")+"::OnKilled3");
		mobuseskill 'mob_id2,675,4,0,0,0,0;	// ストーンスキン
		mobuseskill 'mob_id3,676,4,0,0,0,0;	// アンチマジック
		donpcevent getmdnpcname("callmon#eom4_timer")+"::OnStart";
		end;
	}
	else if('@mobhp < 18000000 && 'flag == 2) {
		switch(rand(3)) {
		case 0: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidMS";	break;
		case 1: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidTS";	break;
		case 2: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidLoV";	break;
		}
		set '@count,getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled4");
		if('@count < 1) {
			set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
			monster getmdmapname("1@eom.gat"),'@x-1,'@y,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster getmdmapname("1@eom.gat"),'@x,'@y-1,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster getmdmapname("1@eom.gat"),'@x+1,'@y,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
			monster getmdmapname("1@eom.gat"),'@x,'@y+1,"狂気のカーサ",3089,1,getmdnpcname("callmon#eom4")+"::OnKilled4";
		}
	}
	else {
		switch(rand(3)) {
		case 0: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidMS";	break;
		case 1: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidTS";	break;
		case 2: donpcevent getmdnpcname("callmon#eom4")+"::OnMoroccKidLoV";	break;
		}
	}
	end;
OnMoroccKidMS:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"再生の半魔神 : 脆弱な魂たちの為にフィナーレを！";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,724,3,0,0,0,0;	// ファイアストーム
	sleep 2000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,83,5,'@x-5,'@y,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,5,'@x+5,'@y,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,5,'@x,'@y+5,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,5,'@x,'@y-5,0,0;	// メテオストーム
	sleep 4000;
	unittalk 'mob_id,"再生の半魔神 : ふふふ……！　もっと楽しもうよ！";
	sleep 2000;
	mobuseskill 'mob_id,85,10,0,0,0,1;	// ロードオブヴァーミリオン
	sleep 2000;
	initnpctimer;
	end;
OnMoroccKidTS:
	if(getmobhp('mob_id) < 1) end;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	unittalk 'mob_id,"再生の半魔神 : 脆弱な魂たちの為にレクイエムを！";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+2,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-2,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y-4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y-4,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y-8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y-8,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y-12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y-12,0,0;	// サンダーストーム
	sleep 1000;
	initnpctimer;
	end;
OnMoroccKidLoV:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"再生の半魔神 : ふふふ!!　耐えられるものなら耐えてみるんだね!!";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,724,3,0,0,0,0;	// ファイアストーム
	sleep 2000;
	mobuseskill 'mob_id,85,10,0,0,0,1;	// ロードオブヴァーミリオン
	sleep 2000;
	mobuseskill 'mob_id,252,1,0,0,0,0;	// リフレクトシールド
	initnpctimer;
	end;
OnHeal1:
	mobuseskill 'mob_id,28,10,0,0,0,0;	// ヒール
	end;
OnHeal2:
	mobuseskill 'mob_id,675,5,0,0,0,0;	// ストーンスキン
	mobuseskill 'mob_id,671,5,0,0,0,0;	// マジックミラー
	end;
OnReStart:
	set 'flag,2;
	set '@mobhp,getmobhp('mob_id);
	set '@dummy,removemonster('mob_id);
	set 'mob_id,callmonster(getmdmapname("1@eom.gat"),102,209,"再生の半魔神#mk01",3096,getmdnpcname("callmon#eom4")+"::OnKilled");
	setmobhp 'mob_id,'@mobhp;
	unittalk 'mob_id,"再生の半魔神 : ふふふ……！　まだあきらめないの？";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,724,3,0,0,0,0;	// ファイアストーム
	sleep 1000;
	mobuseskill 'mob_id,17,10,0,0,0,1;	// ファイアーボール
	initnpctimer;
	end;
OnKilled:
	stopnpctimer;
	donpcevent getmdnpcname("#morocc_god")+ "::OnStart";
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom4")+"::OnKilled4";
	end;
OnKilled2:
	unittalk 'mob_id3,"安息のモロク : すべての生者に安息を与えてやる!!　それが私からの慈悲だ!!";
	mobuseskill 'mob_id3,83,9,800,0,0,0;	// メテオストーム
	end;
OnKilled3:
	unittalk 'mob_id2,"太古のモロク : ガアアアアアアァァッ!!";
	end;
OnKilled4:
	end;
}

1@eom.gat,1,1,0	script	callmon#eom4_timer	139,{
OnStart:
	initnpctimer;
	set 'cnt,0;
	donpcevent getmdnpcname("callmon#eom4")+"::OnHeal2";
	end;
OnTimer200:
	initnpctimer;
	set '@mdmap$,getmdmapname("1@eom.gat");
	set 'cnt,'cnt+1;
	if('cnt > 10) {
		set 'cnt,0;
		set '@count,getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled2") + getmapmobs('@mdmap$,getmdnpcname("callmon#eom4")+"::OnKilled3");
		if('@count <= 0) {
			stopnpctimer;
			donpcevent getmdnpcname("callmon#eom4")+"::OnReStart";
			end;
		}
		donpcevent getmdnpcname("callmon#eom4")+"::OnHeal2";
	}
	donpcevent getmdnpcname("callmon#eom4")+"::OnHeal1";
	end;
}

1@eom.gat,101,194,3	script	#morocc_god	3097,{
OnStart:
	hideonnpc getmdnpcname("#eom_bgm_change2");
	hideoffnpc getmdnpcname("#eom_bgm_change3");
	sleep 4000;
	announce "モロク : 面白くなってきたじゃないか。ククククク……。", 0x9, 0xff0000, 0x0190, 16, 0, 0;
	sleep 4000;
	announce "モロク : おいおい、まさかこれで終わりだと思ってはいないよな？", 0x9, 0xff0000, 0x0190, 16, 0, 0;
	sleep 4000;
	misceffect 897,getmdnpcname("#morocc_god");
	announce "モロク : 神となった私の姿を見よ！", 0x9, 0xff0000, 0x0190, 16, 0, 0;
	sleep 3000;
	misceffect 897,getmdnpcname("#morocc_god");
	sleep 2000;
	hideonnpc getmdnpcname("#eom_bgm_change3");
	hideoffnpc getmdnpcname("#eom_bgm_change4");
	sleep 1000;
	misceffect 432,getmdnpcname("#morocc_god");
	sleep 2000;
	misceffect 432,getmdnpcname("#morocc_god");
	misceffect 488,getmdnpcname("#morocc_god");
	sleep 1000;
	announce "モロク : ククク……神の力に恐れ慄くがいい!!", 0x9, 0xff0000, 0x0190, 16, 0, 0;
	misceffect 796,getmdnpcname("#morocc_god");
	sleep 2000;
	misceffect 30,getmdnpcname("#morocc_god");
	misceffect 587,getmdnpcname("#morocc_god");
	donpcevent getmdnpcname("callmon#eom5")+"::OnStart";
	hideonnpc getmdnpcname("#eom_bgm_change4");
	end;
}

1@eom.gat,1,1,0	script	callmon#eom5	139,{
OnStart:
	set 'mob_id,callmonster(getmdmapname("1@eom.gat"),101,194,"絶望の神モロク#ma01",3097,getmdnpcname("callmon#eom5")+"::OnKilled");
	mobuseskill 'mob_id,653,1,0,0,0,0;	// アースクエイク
	sleep 1000;
	unittalk 'mob_id,"絶望の神モロク : さあ、悲痛の叫びを聞かせてくれ！";
	initnpctimer;
	end;
OnTimer10000:
	set '@mobhp,getmobhp('mob_id);
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom5")+"::OnKilled2";
	if('flag == 0) {
		if('@mobhp < 45000000) {
			set 'flag,1;
			donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtChange";
			end;
		}
		switch(rand(5)) {
		case 0: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtTS";	break;
		case 1: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtLoV";	break;
		case 2: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtFP";	break;
		case 3:	donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtMS";	break;
		case 4:	donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtFC";	break;
		}
		end;
	}
	else if('flag == 1) {
		if('@mobhp < 30000000) {
			set 'flag,2;
			donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtChange";
			end;
		}
		switch(rand(4)) {
		case 0: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtTS2";	break;
		case 1: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtEstr";	break;
		case 2: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtJF";	break;
		case 3: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtFW";	break;
		}
		end;
	}
	else if('flag == 2) {
		switch(rand(4)) {
		case 0: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtPSHJ";	break;
		case 1: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtComet";	break;
		case 2: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtAllMagic";	break;
		case 3: donpcevent getmdnpcname("callmon#eom5")+"::OnMoroccAdtCall";	break;
		}
		end;
	}
	initnpctimer;
	end;
OnMoroccAdtTS:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 弱者の魂よ、雷に打たれ朽ちるがいい！";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,21,20,'@x-2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+2,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-2,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y-4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y-4,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y-8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y-8,0,0;	// サンダーストーム
	sleep 1000;
	mobuseskillpos 'mob_id,21,20,'@x-16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y-12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y-12,0,0;	// サンダーストーム
	sleep 1000;
	initnpctimer;
	end;
OnMoroccAdtLoV:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 圧倒的な死の落雷を見せてやろう!!";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 2000;
	mobuseskill 'mob_id,664,5,0,0,0,0;	// ワイドフリーズ
	sleep 2000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,85,5,'@x-7,'@y,0,0;	// ロードオブヴァーミリオン
	sleep 500;
	mobuseskillpos 'mob_id,85,5,'@x+7,'@y,0,0;	// ロードオブヴァーミリオン
	sleep 500;
	mobuseskillpos 'mob_id,85,5,'@x,'@y+7,0,0;	// ロードオブヴァーミリオン
	sleep 500;
	mobuseskillpos 'mob_id,85,5,'@x,'@y-7,0,0;	// ロードオブヴァーミリオン
	sleep 2500;
	unittalk 'mob_id,"絶望の神モロク : ……ククク……魂が引き裂かれる痛みに耐えれるか？";
	sleep 2000;
	mobuseskill 'mob_id,85,10,0,0,0,1;	// ロードオブヴァーミリオン
	sleep 2000;
	initnpctimer;
	end;
OnMoroccAdtFP:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : ククク……全てを滅してやろう！";
	sleep 2000;
	mobuseskill 'mob_id,724,3,0,0,0,0;	// ファイアストーム
	sleep 2000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,80,10,'@x-1,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+1,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y+1,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y-1,0,0;	// ファイアーピラー
	sleep 500;
	mobuseskillpos 'mob_id,80,10,'@x-5,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+5,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y+5,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y-5,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-3,'@y+3,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-3,'@y-3,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+3,'@y+3,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+3,'@y-3,0,0;	// ファイアーピラー
	sleep 500;
	mobuseskillpos 'mob_id,80,10,'@x-9,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+9,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y+9,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y-9,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-7,'@y+7,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-7,'@y-7,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+7,'@y+7,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+7,'@y-7,0,0;	// ファイアーピラー
	sleep 500;
	mobuseskillpos 'mob_id,80,10,'@x-15,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+15,'@y,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y+15,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x,'@y-15,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-11,'@y+11,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x-11,'@y-11,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+11,'@y+11,0,0;	// ファイアーピラー
	mobuseskillpos 'mob_id,80,10,'@x+11,'@y-11,0,0;	// ファイアーピラー
	sleep 2000;
	initnpctimer;
	end;
OnMoroccAdtMS:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 業火に焼かれる苦痛を味わえ!!";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,724,3,0,0,0,0;	// ファイアストーム
	sleep 2000;
	mobuseskill 'mob_id,83,10,0,0,0,0;	// メテオストーム
	initnpctimer;
	end;
OnMoroccAdtFC:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : その命、貰い受けるぞ!!";
	sleep 2000;
	mobuseskill 'mob_id,711,1,0,0,0,0;	// フレイムクロス
	sleep 1000;
	mobuseskill 'mob_id,81,10,0,0,0,0;	// サイトラッシャー
	sleep 1000;
	initnpctimer;
	end;
OnMoroccAdtChange:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : フフフ……こういうのはどうだ？";
	sleep 1000;
	mobuseskill 'mob_id,85,10,0,0,0,0;	// ロードオブヴァーミリオン
	sleep 1000;
	mobuseskill 'mob_id,289,5,0,0,0,1;	// ディスペル
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	monster getmdmapname("1@eom.gat"),'@x+1,'@y," ",20131,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
	monster getmdmapname("1@eom.gat"),'@x-1,'@y," ",20132,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
	monster getmdmapname("1@eom.gat"),'@x,'@y-1," ",20129,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
	monster getmdmapname("1@eom.gat"),'@x,'@y+1," ",20130,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
	sleep 10000;
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom5")+"::OnKilled2";
	initnpctimer;
	end;
OnMoroccAdtEstr:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 堅固なるツルギに貫かれ、醜態を晒すがいい。";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,2216,5,0,0,0,1;	// アースストレイン
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,91,5,'@x-2,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+2,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y+2,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y-2,0,0;	// ヘヴンズドライブ
	sleep 500;
	mobuseskillpos 'mob_id,91,5,'@x-6,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+6,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y+6,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y-6,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x-4,'@y+4,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x-4,'@y-4,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+4,'@y+4,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+4,'@y-4,0,0;	// ヘヴンズドライブ
	sleep 500;
	mobuseskillpos 'mob_id,91,5,'@x-10,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+10,'@y,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y+10,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x,'@y-10,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x-8,'@y+8,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x-8,'@y-8,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+8,'@y+8,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,91,5,'@x+8,'@y-8,0,0;	// ヘヴンズドライブ
	initnpctimer;
	end;
OnMoroccAdtJF:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 太古より続く冷たき棺に抱かれ、逝くがよい!!";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,720,5,0,0,0,0;	// Mジャックフロスト
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,89,10,'@x-2,'@y,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x+2,'@y,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x,'@y+2,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x,'@y-2,0,0;	// ストームガスト
	sleep 1000;
	mobuseskillpos 'mob_id,89,10,'@x-10,'@y,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x+10,'@y,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x,'@y+10,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x,'@y-10,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x-8,'@y+8,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x-8,'@y-8,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x+8,'@y+8,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,89,10,'@x+8,'@y-8,0,0;	// ストームガスト
	initnpctimer;
	end;
OnMoroccAdtFW:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 痛みを感じる間もなく、燃やしつくしてやろう!!";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,18,10,'@x-2,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+2,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y+2,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y-2,0,0;	// ファイアーウォール
	sleep 500;
	mobuseskillpos 'mob_id,18,10,'@x-6,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+6,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y+6,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y-6,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-4,'@y+4,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-4,'@y-4,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+4,'@y+4,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+4,'@y-4,0,0;	// ファイアーウォール
	sleep 500;
	mobuseskillpos 'mob_id,18,10,'@x-10,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+10,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y+10,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y-10,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-8,'@y+8,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-8,'@y-8,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+8,'@y+8,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+8,'@y-8,0,0;	// ファイアーウォール
	sleep 500;
	mobuseskillpos 'mob_id,18,10,'@x-16,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+16,'@y,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y+16,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x,'@y-16,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-12,'@y+12,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x-12,'@y-12,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+12,'@y+12,0,0;	// ファイアーウォール
	mobuseskillpos 'mob_id,18,10,'@x+12,'@y-12,0,0;	// ファイアーウォール
	sleep 500;
	mobuseskillpos 'mob_id,83,10,'@x-12,'@y+12,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,10,'@x-12,'@y-12,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,10,'@x+12,'@y+12,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,10,'@x+12,'@y-12,0,0;	// メテオストーム
	sleep 1000;
	initnpctimer;
	end;
OnMoroccAdtTS2:
	unittalk 'mob_id,"絶望の神モロク : 裁きの雷にその身を焦がすがいい……！";
	sleep 2000;
	mobuseskill 'mob_id,721,1,0,0,0,0;	// ワイドウェブ
	sleep 1000;
	mobuseskill 'mob_id,84,28,0,0,0,1;	// ユピテルサンダー
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	mobuseskillpos 'mob_id,21,20,'@x-2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+2,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+2,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-2,0,0;	// サンダーストーム
	sleep 500;
	mobuseskillpos 'mob_id,21,20,'@x-6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+6,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-6,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-4,'@y-4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y+4,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+4,'@y-4,0,0;	// サンダーストーム
	sleep 500;
	mobuseskillpos 'mob_id,21,20,'@x-10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+10,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-10,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-8,'@y-8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y+8,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+8,'@y-8,0,0;	// サンダーストーム
	sleep 500;
	mobuseskillpos 'mob_id,21,20,'@x-16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+16,'@y,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y+16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x,'@y-16,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x-12,'@y-12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y+12,0,0;	// サンダーストーム
	mobuseskillpos 'mob_id,21,20,'@x+12,'@y-12,0,0;	// サンダーストーム
	sleep 500;
	initnpctimer;
	end;
OnMoroccAdtPSHJ:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 虫けらが……もがき苦しむがいい!!";
	sleep 1000;
	mobuseskill 'mob_id,289,5,0,0,0,1;	// ディスペル
	sleep 2000;
	unittalk 'mob_id,"絶望の神モロク : 闇の底に沈めぇぇぇ!!";
	sleep 1000;
	mobuseskill 'mob_id,661,3,0,0,0,0;	// パルスストライク
	sleep 1000;
	mobuseskill 'mob_id,662,5,0,0,0,0;	// ヘルジャッジメント
	sleep 1000;
	initnpctimer;
	end;
OnMoroccAdtComet:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : クッ……!!　人間ごときがあぁぁッ!!";
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	sleep 2000;
	mobuseskillpos 'mob_id,483,5,'@x-6,'@y,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x+6,'@y,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x,'@y+6,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x,'@y-6,0,0;	// ガンバンテイン
	sleep 1000;
	unittalk 'mob_id,"絶望の神モロク : 地獄を味わえ！　これでフィナーレだ！";
	sleep 2000;
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	mobuseskill 'mob_id,708,5,0,0,0,0;	// Mコメット
	initnpctimer;
	end;
OnMoroccAdtAllMagic:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : 貴様ら……いい気になるなよ!!";
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	sleep 2000;
	mobuseskillpos 'mob_id,483,5,'@x-3,'@y,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x+3,'@y,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x,'@y-3,0,0;	// ガンバンテイン
	mobuseskillpos 'mob_id,483,5,'@x,'@y+3,0,0;	// ガンバンテイン
	sleep 1000;
	mobuseskillpos 'mob_id,85,10,'@x+2,'@y,0,0;	// ロードオブヴァーミリオン
	mobuseskillpos 'mob_id,89,10,'@x,'@y+2,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,91,5,'@x,'@y-2,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,83,10,'@x-2,'@y,0,0;	// メテオストーム
	sleep 500;
	mobuseskillpos 'mob_id,85,10,'@x+10,'@y,0,0;	// ロードオブヴァーミリオン
	mobuseskillpos 'mob_id,89,10,'@x,'@y+10,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,91,5,'@x,'@y-10,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,83,10,'@x-10,'@y,0,0;	// メテオストーム
	sleep 500;
	mobuseskillpos 'mob_id,85,10,'@x-8,'@y-8,0,0;	// ロードオブヴァーミリオン
	mobuseskillpos 'mob_id,89,10,'@x+8,'@y+8,0,0;	// ストームガスト
	mobuseskillpos 'mob_id,91,5,'@x+8,'@y-8,0,0;	// ヘヴンズドライブ
	mobuseskillpos 'mob_id,83,10,'@x-8,'@y+8,0,0;	// メテオストーム
	sleep 1000;
	unittalk 'mob_id,"絶望の神モロク : ……これで終わりだッ!!!!";
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	sleep 1000;
	mobuseskillpos 'mob_id,83,10,'@x,'@y,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,10,'@x,'@y,0,0;	// メテオストーム
	mobuseskillpos 'mob_id,83,10,'@x,'@y,0,0;	// メテオストーム
	initnpctimer;
	end;
OnMoroccAdtCall:
	if(getmobhp('mob_id) < 1) end;
	unittalk 'mob_id,"絶望の神モロク : この神に逆らう愚か者どもめ!!";
	sleep 2000;
	mobuseskill 'mob_id,85,10,0,0,0,0;	// ロードオブヴァーミリオン
	sleep 1000;
	mobuseskill 'mob_id,289,5,0,0,0,1;	// ディスペル
	sleep 1000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	switch(rand(3)) {
	case 0:
		monster getmdmapname("1@eom.gat"),'@x+1,'@y," ",20131,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		monster getmdmapname("1@eom.gat"),'@x-1,'@y," ",20132,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		break;
	case 1:
		monster getmdmapname("1@eom.gat"),'@x+1,'@y," ",20129,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		monster getmdmapname("1@eom.gat"),'@x-1,'@y," ",20130,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		break;
	case 2:
		monster getmdmapname("1@eom.gat"),'@x+1,'@y," ",3096,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		monster getmdmapname("1@eom.gat"),'@x-1,'@y," ",3096,1,getmdnpcname("callmon#eom5")+"::OnKilled2";
		break;
	}
	sleep 10000;
	killmonster getmdmapname("1@eom.gat"),getmdnpcname("callmon#eom5")+"::OnKilled2";
	initnpctimer;
	end;
OnKilled:
	announce "モロク : ……私は神だぞ……!?　たかが人間風情にこの私が……私が……ッ!!", 0x9, 0xff0000, 0x0190, 14, 0, 0;
	sleep 1000;
	hideoffnpc getmdnpcname("#eom_quest");
	sleep 3000;
	hideonnpc getmdnpcname("#eom_quest");
	hideoffnpc getmdnpcname("絶望の神モロク#04");
	hideoffnpc getmdnpcname("ロキ#eomnyd04");
	hideoffnpc getmdnpcname("ニーズヘッグ#eomnyd04");
	hideonnpc getmdnpcname("#eom_bgm_change3");
	end;
OnKilled2:
	end;
}

1@eom.gat,101,194,0	script	#eom_quest	139,20,20,{
	setquest 116545;
	compquest 116545;
	end;
}

1@eom.gat,102,197,3	script	絶望の神モロク#04	3097,{
	end;
OnStart:
	sleep 2000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : くっ……私が、神が敗れるのか……！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 次元を裂き、大地を創造し、生命の刻を操る私の力……。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 何故だ！　何故、世界創造の力が貴様如きに敗れる！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : ……愚かだな、モロク。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : 神は万物を創造した。しかし創造されしものは時の流れを生きる。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : この世界は、この世界に住む全ての生物の意志や行動によって支えられているんだ。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 馬鹿な！　万物を創造する神の力とは万物を支配し、破壊できる力だ！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : そう、人間を支配できる力だ！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : 人間を支配？　笑わせてくれますね。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : あなたは「神」を見ていない。結局見ているのは「人間」。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : あなたは神の姿をしているのではない。人間の姿をしているのです。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 戯言を……！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : しかし、いくら姿形を真似ようと無意味です。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ヒトは全にして個、個にして全。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ご覧なさい、フレイムヴァレーにいる者達を！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ミッドガルド、アールヴヘイム、ヨトゥンヘイム……。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : 微細の違いあれど多くのヒトが大きな個となれば、あなたの創ろうとする張りぼての世界など薄氷のように脆いのです！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : ありえぬ！　脆弱なヒトなど神の前では羽虫も同然……。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : モロク、貴様はヒトに神の姿を重ね、憧れていただけだ。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : 貴様はヒトに憧れ、ヒトになれず、そして、ヒトに滅ぼされる。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 黙れ黙れ！　神である私に説教だと？　ふざけるな！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : あなたは気付いていないだけです！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ヒトに憧れた！　世界を羨んだ！　その思いはあなたの生み出したものからも感じます！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 馬鹿な！　私は……！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ……眠りなさい。夢を見なさい。そこにあなたを拒絶する世界はありません。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 私は消えぬ！　例え私の残した傷痕が世界から消えようともな！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 貴様らの記憶に私が居る限り、私は何度でも貴様らの前に立ちはだかろう！";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("絶望の神モロク#04")),"モロク : 貴様らが私を消すことなど、出来ぬのだ！";
	sleep 3000;
	misceffect 183,getmdnpcname("絶望の神モロク#04");
	misceffect 62,getmdnpcname("絶望の神モロク#04");
	misceffect 266,getmdnpcname("絶望の神モロク#04");
	sleep 500;
	misceffect 183,getmdnpcname("絶望の神モロク#04");
	misceffect 62,getmdnpcname("絶望の神モロク#04");
	misceffect 266,getmdnpcname("絶望の神モロク#04");
	hideonnpc getmdnpcname("絶望の神モロク#04");
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : 確かに私たちの記憶から完全に消えない限り、魔王モロクは残り続けるでしょう……。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : 魔王モロクは、滅んだことによって、我々の意識の中で永遠の魔王となりました。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ロキ#eomnyd04")),"ロキ : ……奴には最高の皮肉かもしれないな。";
	sleep 5000;
	unittalk getnpcid(0,getmdnpcname("ニーズヘッグ#eomnyd04")),"ニーズヘッグ : ……さあ、帰りましょう。外に出るときは私に話しかけて下さい。";
	set getvariableofnpc('flag,getmdnpcname("ニーズヘッグ#eomnyd04")),2;
	end;
}

1@eom.gat,104,194,1	script	ロキ#eomnyd04	512,{
	mes "[ロキ]";
	mes "魔王モロクの最期か。";
	mes "長かった因縁もこれまでだ。";
	cutin "ep14_roki01", 2;
	close2;
	cutin "ep14_roki01", 255;
	end;
}

1@eom.gat,99,194,7	script	ニーズヘッグ#eomnyd04	510,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0) && 'flag == 0) {
		if(checkquest(201730)) {
			if(select("急ぐ","会話をする") == 1) {
				misceffect 172,getmdnpcname("絶望の神モロク#04");
				set '@dummy,sleep2(2000);
				misceffect 183,getmdnpcname("絶望の神モロク#04");
				misceffect 62,getmdnpcname("絶望の神モロク#04");
				misceffect 266,getmdnpcname("絶望の神モロク#04");
				set '@dummy,sleep2(500);
				misceffect 183,getmdnpcname("絶望の神モロク#04");
				misceffect 62,getmdnpcname("絶望の神モロク#04");
				misceffect 266,getmdnpcname("絶望の神モロク#04");
				hideonnpc getmdnpcname("絶望の神モロク#04");
				set 'flag,2;
				close;
			}
			set 'flag,1;
			donpcevent getmdnpcname("絶望の神モロク#04")+"::OnStart";
			close;
		}
		menu "会話をする",-;
		set 'flag,1;
		donpcevent getmdnpcname("絶望の神モロク#04")+"::OnStart";
		close;
	}
	if('flag <= 1) {
		mes "[ニーズヘッグ]";
		mes "魔王モロク……。";
		mes "神になろうとしていたようですが";
		mes "その実、ヒトへの憧れが";
		mes "あったのでしょう。";
		cutin "ep14_nyd03", 2;
		close2;
		cutin "ep14_nyd03", 255;
		end;
	}
	if(checkquest(7597)) {
		mes "[ニーズヘッグ]";
		mes "……これが最後ではない気がします。";
		mes "ここはモロクの精神世界です。";
		mes "恐らく、この場所で彼は";
		mes "終わりなき野望を繰り返すはずです。";
		cutin "ep14_nyd03", 2;
		next;
		menu "外に出る",-;
		mes "[ニーズヘッグ]";
		mes "遠征隊員がいる場所までお送りします。";
		cutin "ep14_nyd04", 2;
		close2;
		cutin "ep14_nyd04", 255;
		warp "moro_vol.gat",91,87;
		end;
	}
	if(checkquest(7593)&0x4) {
		mes "[ニーズヘッグ]";
		mes "……これでやっと";
		mes "魔王モロクの企みを";
		mes "本当の意味で止めることが";
		mes "出来ました。";
		mes "ありがとうございます。";
		cutin "ep14_nyd03", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "ここは彼の作りだした精神世界。";
		mes "彼は身体を失ってもなお";
		mes "この空間を永遠に彷徨い、";
		mes "あがき続けるでしょう。";
		cutin "ep14_nyd02", 2;
		next;
		mes "[ニーズヘッグ]";
		mes "そしてまた、ここに来る全ての人が";
		mes "今日のような出来事を繰り返します。";
		next;
		mes "[ニーズヘッグ]";
		mes "今日の絶望を明日も。";
		mes "そしてその明日もまた明日も……。";
		mes "幾度となく続けるでしょう。";
		next;
		mes "[ニーズヘッグ]";
		mes "私たちはそれを知っていても、";
		mes "その同じ道をまた歩くでしょう。";
		mes "その度に私は、";
		mes "守護者としてあなたの側に……。";
		cutin "ep14_nyd03", 2;
		next;
		cutin "ep14_nyd04", 2;
		mes "[ニーズヘッグ]";
		mes "話が長くなりました。";
		mes "司令官が待っていますよね？";
		mes "今回の件の報告をお願いします。";
		mes "本当にありがとうございました。";
		next;
		mes "‐^ff0000これ以降、魔神殿に入ることは";
		mes "　できなくなります。";
		mes "　司令官アジフに報告してから、";
		mes "　1回目の午前5時以降に、";
		mes "　再度魔神殿に入ることが";
		mes "　できるようになります^000000‐";
		setquest 7597;
		delquest 7593;
		setquest 116545;
		delquest 116545;
		next;
	}
	menu "外に出る",-;
	mes "[ニーズヘッグ]";
	mes "遠征隊員がいる場所までお送りします。";
	cutin "ep14_nyd04", 2;
	close2;
	cutin "ep14_nyd04", 255;
	warp "moro_vol.gat",91,87;
	end;
}

1@eom.gat,48,88,0	script	冷たい魔力の結晶#eom01	10043,{
	misceffect 362;
	hideonnpc;
	getitem 22566,1;
	end;
}
1@eom.gat,51,103,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom02	10043
1@eom.gat,24,109,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom03	10043
1@eom.gat,26,128,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom04	10043
1@eom.gat,40,140,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom05	10043
1@eom.gat,38,139,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom06	10043
1@eom.gat,51,149,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom07	10043
1@eom.gat,49,148,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom08	10043
1@eom.gat,27,100,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom09	10043
1@eom.gat,32,94,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom10	10043
1@eom.gat,60,140,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom11	10043
1@eom.gat,54,97,0	duplicate(冷たい魔力の結晶#eom01)	冷たい魔力の結晶#eom12	10043
