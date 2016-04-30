//= Auriga Script ==============================================================
// Ragnarok Online Bangungot Hospital 2F Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
ma_dun01.gat,147,10,5	script	看護師	569,{
	switch(MALAYA_4QUE) {
	case 19:
	case 20:
		cutin "malaya_nurseB",2;
		mes "[看護師]";
		mes "…………。";
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 21:
		cutin "malaya_nurseB",2;
		mes "‐病院の扉は";
		mes "　閉まっていたはずなのに";
		mes "　この看護師はいつ";
		mes "　入って来たのだろう？";
		mes "　後ろから呼んでみたが";
		mes "　反応しない‐";
		next;
		mes "‐いったん、病院の入り口まで戻って";
		mes "　看護師ラズに階段の様子を";
		mes "　伝えよう‐";
		delquest 11302;
		setquest 11303;
		set MALAYA_4QUE,22;
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 22:
		cutin "malaya_nurseB",2;
		mes "‐病院の扉は";
		mes "　閉まっていたはずなのに";
		mes "　この看護師はいつ";
		mes "　入って来たのだろう？";
		mes "　後ろから呼んでみたが";
		mes "　反応しない‐";
		next;
		mes "‐いったん、病院の入り口まで戻って";
		mes "　看護師ラズに階段の様子を";
		mes "　伝えよう‐";
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 23:
	case 24:
	case 25:
		//未調査
		cutin "malaya_nurseB",2;
		mes "‐病院の扉は";
		mes "　閉まっていたはずなのに";
		mes "　この看護師はいつ";
		mes "　入って来たのだろう？";
		mes "　後ろから呼んでみたが";
		mes "　反応しない‐";
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 26:
		cutin "malaya_nurseB",2;
		mes "[看護師]";
		mes "いい調子だわ。";
		mes "もうすぐね……";
		next;
		mes "‐何かに集中しているようだ‐";
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 27:
		cutin "malaya_nurseB",2;
		mes "[看護師]";
		mes "ここは私に任せて";
		mes "あなたは病院の外に逃げなさい。";
		mes "さあ、早く！";
		close2;
		cutin "malaya_nurseB",255;
		warp "malaya.gat",58,76;
		end;
	case 28:
	case 29:
		if(checkquest(11309) & 0x4) {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "お疲れ様。";
			mes "まさか本当にビョンウンゴを";
			mes "倒してしまうなんて……。";
			mes "なかなかやるわね。";
			next;
			mes "[看護師マエン]";
			mes "これでビョンウンゴが";
			mes "いなくなるほど甘くはないでしょうね。";
			mes "また力を借りるかもしれないから、";
			mes "時々、ここに来てくれると助かるわ。";
			delquest 9224;
			setquest 9223;
			delquest 11309;
			set MALAYA_3QUE,29;
			getitem 6499,5;
			next;
			mes "[看護師マエン]";
			mes "病院から出たいなら、";
			mes "入り口のところまで来てね。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if(checkquest(9222) & 0x4) {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "お疲れ様。";
			mes "まさか本当にビョンウンゴを";
			mes "倒してしまうなんて……。";
			mes "なかなかやるわね。";
			next;
			mes "[看護師マエン]";
			mes "これでビョンウンゴが";
			mes "いなくなるほど甘くはないでしょうね。";
			mes "また力を借りるかもしれないから、";
			mes "時々、ここに来てくれると助かるわ。";
			delquest 9222;
			delquest 9224;
			setquest 9223;
			getitem 6499,5;
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if(checkquest(9224) & 0x2) {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "また来たのね。";
			mes "……よし、こちらの準備は大丈夫よ。";
			mes "ビョンウンゴの部屋に行きたいなら";
			mes "もう一度話しかけてね。";
			delquest 9224;
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if(checkquest(9223)) {
			if(!(checkquest(9223) & 0x2)) {
				cutin "malaya_nurseB",2;
				mes "[看護師マエン]";
				mes "これでビョンウンゴが";
				mes "いなくなるほど甘くはないでしょうね。";
				mes "また力を借りるかもしれないから、";
				mes "時々、ここに来てくれると助かるわ。";
				close2;
				cutin "malaya_nurseB",255;
				end;
			}
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "久しぶりね。";
			mes "ビョンウンゴが";
			mes "また現れたみたいなの。";
			mes "手を貸してくれないかしら？";
			mes "準備ができたらもう一度話しかけて。";
			delquest 9223;
			setquest 9222;
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if(getonlinepartymember() < 1) {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "ビョンウンゴを倒しに来たのね？";
			mes "この先は危険だから";
			mes "1人で行かせることはできないわ。";
			mes "パーティーに加入してから";
			mes "もう一度来てちょうだい。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if(getpartyleader(getcharid(1)) == strcharinfo(0) && !checkquest(9224)) {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "ビョンウンゴを倒しに来たのね？";
			mes "準備ができているなら";
			mes "彼女をおびき寄せるわよ。";
			set '@str$,"ビョンウンゴをおびき寄せる";
		}
		else {
			cutin "malaya_nurseB",2;
			mes "[看護師マエン]";
			mes "もしかして、";
			mes "ビョンウンゴの部屋に";
			mes "行きたいのかしら？";
		}
		next;
		switch(select('@str$,"ビョンウンゴの部屋に入る","やっぱりやめる")) {
		case 1:
			if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
				mes "[看護師マエン]";
				mes "あら……出てこない？";
				mes "おかしいわね。";
				mes "少し時間を空けて、";
				mes "もう一度話しかけてね。";
				close2;
				cutin "malaya_nurseB",255;
				end;
			}
			mdcreate "Bangungot 2F";
			mes "[看護師マエン]";
			mes "ビョンウンゴをおびき寄せるわね。";
			mes "準備が整ったら";
			mes "もう一度話しかけてね。";
			setquest 9224;
			close2;
			cutin "malaya_nurseB",255;
			end;
		case 2:
			switch(mdenter("Bangungot 2F")) {
			case 0:	// エラーなし
				announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Bangungot 2F]に入場します",0x9,0x00FF99;
				cutin "malaya_nurseB",255;
				donpcevent getmdnpcname("BangungotControl1-1")+ "::OnStart";
				//warp "1@ma_h.gat",40,157;
				end;
			case 1:	// パーティー未加入
				mes "[看護師マエン]";
				mes "あら？";
				mes "パーティーを抜けてしまったの？";
				mes "それじゃ、通すわけにはいかないわ。";
				close2;
				cutin "malaya_nurseB",255;
				end;
			case 2:	// ダンジョン未作成
				if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
					mes "[看護師マエン]";
					mes "まだビョンウンゴが出て来てないわ。";
					mes "焦らないでね。";
				}
				else {
					mes "[看護師マエン]";
					mes "まだビョンウンゴが出て来てないわ。";
					mes "まず、リーダーと";
					mes "話をさせてもらえるかしら？";
				}
				close2;
				cutin "malaya_nurseB",255;
				end;
			default:	// その他エラー
				close;
			}
		case 3:
			mes "[看護師マエン]";
			mes "わかったわ。";
			mes "もし考えが変わったら";
			mes "また来てね。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
	default:
		cutin "malaya_nurseB",2;
		mes "‐病院の扉は";
		mes "　閉まっていたはずなのに";
		mes "　この看護師はいつ";
		mes "　入って来たのだろう？";
		mes "　後ろから呼んでみたが";
		mes "　反応しない‐";
		close2;
		cutin "malaya_nurseB",255;
		end;
	}
}

//============================================================
// 闇のビョンウンゴ病院2階
//------------------------------------------------------------
1@ma_h.gat,43,157,0	script	BangungotControl1-1	139,2,2,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("BangungotControl8-3");
	hideonnpc getmdnpcname("BangungotExit");
	hideonnpc getmdnpcname("BangungotGate1");
	hideonnpc getmdnpcname("BangungotGate2");
	for(set '@i,2; '@i<=8; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	for(set '@i,34; '@i<=38; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	for(set '@i,41; '@i<=49; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTouch:
	initnpctimer;
	announce "ビョンウンゴ：愚かな " +strcharinfo(0)+ "……。死ぬ前にここから出ていけ……。",0x9,0xff82ff;
	donpcevent getmdnpcname("BangungotControl1-2")+ "::OnStart";
	hideonnpc getmdnpcname("BangungotControl1-1");
	end;
OnTimer5000:
	announce "ビョンウンゴ：もう私を止める事はできないぞ……。",0x9,0xff82ff;
	end;
OnTimer10000:
	stopnpctimer;
	announce "ビョンウンゴ：ふふふふふ!!",0x9,0xff82ff;
	end;
}

1@ma_h.gat,43,157,0	script	BangungotControl1-2	139,{
OnStart:
	monster getmdmapname("1@ma_h.gat"),45,157,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl1-2")+ "::OnKilled";
	misceffect 360,getmdnpcname("BangungotControl1-1");
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	announce "ビョンウンゴ：それが返答か……いいだろう、恐ろしい悪夢を見せてやる。",0x9,0xff82ff;
	end;
OnTimer2000:
	announce "看護師マエン：聞こえる？　ビョンウンゴが居る部屋の入口は閉じているわ。",0x9,0xff8200;
	end;
OnTimer4000:
	stopnpctimer;
	announce "看護師マエン：まずは病室を順番にまわってビョンウンゴの部下を退治して。",0x9,0xff8200;
	misceffect 360,getmdnpcname("BangungotControl2");
	donpcevent getmdnpcname("BangungotControl2")+ "::OnStart";
	end;
}

1@ma_h.gat,46,165,0	script	BangungotControl2	139,{
OnStart:
	monster getmdmapname("1@ma_h.gat"),50,173,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl2")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),53,172,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl2")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl2")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl3")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,57,147,0	script	BangungotControl3	139,{
OnStart:
	misceffect 360,getmdnpcname("BangungotControl2");
	announce "ビョンウンゴ：本当の痛みと苦しみを教えてやろう……。",0x9,0xff82ff;
	misceffect 360,getmdnpcname("BangungotControl3");
	monster getmdmapname("1@ma_h.gat"),54,141,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl3")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),45,140,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl3")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl3")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl4")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,67,165,0	script	BangungotControl4	139,{
OnStart:
	misceffect 360,getmdnpcname("BangungotControl3");
	announce "ビョンウンゴ：お前たちの苦しみは私の力となる……。",0x9,0xff82ff;
	misceffect 360,getmdnpcname("BangungotControl4");
	monster getmdmapname("1@ma_h.gat"),71,172,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl4")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),73,172,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl4")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),74,172,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl4")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl4")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl5")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,79,147,0	script	BangungotControl5	139,{
OnStart:
	misceffect 360,getmdnpcname("BangungotControl4");
	announce "ビョンウンゴ：私に聞かせてみろ……お前の苦しみを!!",0x9,0xff82ff;
	misceffect 360,getmdnpcname("BangungotControl5");
	monster getmdmapname("1@ma_h.gat"),73,140,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl5")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),75,140,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl5")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),76,140,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl5")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl5")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl6")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,90,165,0	script	BangungotControl6	139,{
OnStart:
	misceffect 360,getmdnpcname("BangungotControl5");
	announce "ビョンウンゴ：もっと……もっと苦しむがいい……。",0x9,0xff82ff;
	misceffect 360,getmdnpcname("BangungotControl6");
	monster getmdmapname("1@ma_h.gat"),94,174,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl6")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),95,174,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl6")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),98,174,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl6")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),95,176,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl6")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl6")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl7")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,101,147,0	script	BangungotControl7	139,{
OnStart:
	misceffect 360,getmdnpcname("BangungotControl6");
	announce "ビョンウンゴ：もっと怯えろ……怖がれ……。",0x9,0xff82ff;
	misceffect 360,getmdnpcname("BangungotControl7");
	monster getmdmapname("1@ma_h.gat"),94,137,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl7")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),96,139,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl7")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),99,138,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl7")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),94,140,"悪夢のマンククーラム",2339,1,getmdnpcname("BangungotControl7")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),95,141,"悪夢のマナナンガル",2338,1,getmdnpcname("BangungotControl7")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl7")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotBoss")+ "::OnStart";
	}
	end;
}

1@ma_h.gat,110,177,0	script	BangungotBoss	139,{
OnStart:
	announce "ビョンウンゴ：愚かな……生きて帰ることはできないぞ……。",0x9,0xff82ff;
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnStart";
	donpcevent getmdnpcname("BangungotEvent")+ "::OnStart";
	monster getmdmapname("1@ma_h.gat"),143,158,"ビョンウンゴ",2317,1,getmdnpcname("BangungotBoss")+ "::OnKilled";
	monster getmdmapname("1@ma_h.gat"),131,62,"憤怒のビョンウンゴ",2318,1;
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	announce "ビョンウンゴ：こ……これで終わりだと思うなよ。",0x9,0xff82ff;
	donpcevent getmdnpcname("BangungotControl9-1")+ "::OnStart";
	end;
}

1@ma_h.gat,147,143,0	script	BangungotControl8-1	139,10,10,{
OnStart:
	hideoffnpc getmdnpcname("BangungotControl8-1");
	hideoffnpc getmdnpcname("BangungotGate1");
	hideoffnpc getmdnpcname("BangungotGate2");
	end;
OnTouch:
	misceffect 360,getmdnpcname("BangungotControl7");
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnDisable";
	donpcevent getmdnpcname("BangungotControl8-2")+ "::OnStart";
	end;
OnSpawn:
	areamonster getmdmapname("1@ma_h.gat"),123,152,137,166,"悪夢のマナナンガル",2338,1,getmdnpcname("BangungotControl8-1")+"::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl8-1")+"::OnKilled");
	if('@count < 1) {
		announce "ビョンウンゴ：ふふふ……その程度の力では無駄だ、私には勝てないぞ……。",0x9,0xff82ff;
	}
	end;
OnEnable:
	hideoffnpc getmdnpcname("BangungotControl8-1");
	hideoffnpc getmdnpcname("BangungotWarp_a");
	hideoffnpc getmdnpcname("BangungotWarp_b");
	hideoffnpc getmdnpcname("BangungotWarp_c");
	hideoffnpc getmdnpcname("BangungotWarp_d");
	hideoffnpc getmdnpcname("BangungotWarp_e");
	hideoffnpc getmdnpcname("BangungotWarp_f");
	hideoffnpc getmdnpcname("BangungotWarp_g");
	hideoffnpc getmdnpcname("BangungotWarp_h");
	end;
OnDisable:
	hideonnpc getmdnpcname("BangungotControl8-1");
	hideonnpc getmdnpcname("BangungotWarp_a");
	hideonnpc getmdnpcname("BangungotWarp_b");
	hideonnpc getmdnpcname("BangungotWarp_c");
	hideonnpc getmdnpcname("BangungotWarp_d");
	hideonnpc getmdnpcname("BangungotWarp_e");
	hideonnpc getmdnpcname("BangungotWarp_f");
	hideonnpc getmdnpcname("BangungotWarp_g");
	hideonnpc getmdnpcname("BangungotWarp_h");
	end;
}

1@ma_h.gat,147,143,0	script	BangungotControl8-2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer5000:
	announce "ビョンウンゴ：哀れな者よ……本当の苦しみを教えてやろう……。",0x9,0xff82ff;
	end;
OnTimer30000:
	announce "ビョンウンゴ：呼吸もできぬほど痛く、苦しい病が ",0x9,0xff82ff;
	for(set '@i,10; '@i<=22; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer40000:
	announce "ビョンウンゴ：どのようなものか……知っているか？",0x9,0xff82ff;
	for(set '@i,25; '@i<=33; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer50000:
	announce "ビョンウンゴ：病に苦しむ者たちの悲鳴を聞いたことがあるか？",0x9,0xff82ff;
	end;
OnTimer60000:
	announce "ビョンウンゴ：聞いたことがないなら私が聞かせてやる！",0x9,0xff82ff;
	hideoffnpc getmdnpcname("BangungotControl8-4");
	killmonster "this",getmdnpcname("BangungotControl8-5")+ "::OnKilled";
	end;
OnTimer65000:
	for(set '@i,2; '@i<=8; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	for(set '@i,34; '@i<=38; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer65500:
	for(set '@i,41; '@i<=49; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer95000:
	announce "ビョンウンゴ：患者の苦しみが私の力となっていく……。",0x9,0xff82ff;
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnSpawn";
	end;
OnTimer115000:
	announce "ビョンウンゴ：もっと苦しめろ……呪われし病よ！",0x9,0xff82ff;
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnSpawn";
	end;
OnTimer130000:
	announce "ビョンウンゴ：もうそろそろ私と遊んでみるか……？",0x9,0xff82ff;
	end;
OnTimer133000:
	for(set '@i,2; '@i<=8; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	for(set '@i,34; '@i<=38; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer133500:
	for(set '@i,41; '@i<=49; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer134000:
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnEnable";
	end;
OnTimer134500:
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnSpawn";
	for(set '@i,10; '@i<=22; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer135000:
	for(set '@i,25; '@i<=33; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	stopnpctimer;
	end;
OnStopTimer:
	stopnpctimer;
	end;
}

1@ma_h.gat,111,177,0	script	BangungotControl8-3	139,{
OnStart:
	announce "ビョンウンゴ：なかなかやるようだな……。",0x9,0xff82ff;
	initnpctimer;
	end;
OnTimer3000:
	announce "ビョンウンゴ：だが、続けてこの私を……",0x9,0xff82ff;
	end;
OnTimer6000:
	announce "ビョンウンゴ：相手にすることができるかな……？",0x9,0xff82ff;
	end;
OnTimer9000:
	for(set '@i,2; '@i<=8; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	for(set '@i,34; '@i<=38; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer9500:
	for(set '@i,41; '@i<=49; set '@i,'@i+1)
		hideonnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer10000:
	announce "ビョンウンゴ：愚かな者よ……。",0x9,0xff82ff;
	for(set '@i,10; '@i<=22; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	end;
OnTimer10500:
	for(set '@i,25; '@i<=33; set '@i,'@i+1)
		hideoffnpc getmdnpcname("BangungotWarp" +'@i);
	stopnpctimer;
	end;
}

1@ma_h.gat,118,63,0	script	BangungotControl8-4	139,4,4,{
OnTouch:
	donpcevent getmdnpcname("BangungotControl8-5")+ "::OnStart";
	misceffect 196,getmdnpcname("BangungotControl8-4");
	hideonnpc getmdnpcname("BangungotControl8-4");
	end;
OnSummon1:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,47,77,49,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,49,77,51,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,51,77,53,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,47,79,49,81,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,49,79,51,81,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,47,81,49,83,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,49,81,51,83,"悪夢のチャナック",2340,1,'@label$;
	end;
OnSummon2:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,51,45,53,47,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,53,45,55,47,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,49,47,51,49,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,53,47,55,49,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,49,49,51,51,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,51,49,53,51,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,53,49,55,51,"悪夢のチャナック",2340,1,'@label$;
	end;
OnSummon3:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,69,75,71,77,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,71,75,73,77,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,73,75,75,77,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,69,77,71,79,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,71,77,73,79,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,69,79,71,81,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,71,79,73,81,"悪夢のチャナック",2340,1,'@label$;
	end;
OnSummon4:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,73,45,75,47,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,75,45,77,47,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,71,47,73,49,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,75,47,77,49,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,71,49,73,51,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,73,49,75,51,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,75,49,77,51,"悪夢のチャナック",2340,1,'@label$;
	end;
OnSummon5:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,93,77,95,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,95,77,97,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,97,77,99,79,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,93,79,95,81,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,95,79,97,81,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,93,81,95,83,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,95,81,97,83,"悪夢のチャナック",2340,1,'@label$;
	end;
OnSummon6:
	set '@map$, getmdmapname("1@ma_h.gat");
	set '@label$, getmdnpcname("BangungotControl8-5")+"::OnKilled";
	areamonster '@map$,93,43,95,45,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,95,43,97,45,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,91,45,93,47,"悪夢のマンククーラム",2339,1,'@label$;
	areamonster '@map$,95,45,97,47,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,91,47,93,49,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,93,47,95,49,"悪夢のチャナック",2340,1,'@label$;
	areamonster '@map$,95,47,97,49,"悪夢のチャナック",2340,1,'@label$;
	end;
}

1@ma_h.gat,118,64,0	script	BangungotControl8-5	139,{
OnStart:
	initnpctimer;
	end;
OnTimer4000:
	set '@flag,rand(1,12);
	switch('@flag) {
	case 1:	//唸っている患者
		donpcevent getmdnpcname("BangungotPatient01")+ "::OnStart";
		break;
	case 2:	//絶叫する患者
		donpcevent getmdnpcname("BangungotPatient02")+ "::OnStart";
		break;
	case 3:	//苦しんでいる患者
		donpcevent getmdnpcname("BangungotPatient03")+ "::OnStart";
		break;
	case 4:	//気絶した患者
		donpcevent getmdnpcname("BangungotPatient04")+ "::OnStart";
		break;
	case 5:	//悪夢を見る患者
		donpcevent getmdnpcname("BangungotPatient05")+ "::OnStart";
		break;
	case 6:	//痛そうに見える患者
		donpcevent getmdnpcname("BangungotPatient06")+ "::OnStart";
		break;
	case 7:	//恐怖に怯えている患者
		donpcevent getmdnpcname("BangungotPatient07")+ "::OnStart";
		break;
	case 8:	//悲しんでいる患者
		donpcevent getmdnpcname("BangungotPatient08")+ "::OnStart";
		break;
	case 9:	//顔を歪める患者
		donpcevent getmdnpcname("BangungotPatient09")+ "::OnStart";
		break;
	case 10:	//身悶える患者
		donpcevent getmdnpcname("BangungotPatient10")+ "::OnStart";
		break;
	case 11:	//冷汗をかく患者
		donpcevent getmdnpcname("BangungotPatient11")+ "::OnStart";
		break;
	case 12:	//叫んでいる患者
		donpcevent getmdnpcname("BangungotPatient12")+ "::OnStart";
		break;
	}
	donpcevent getmdnpcname("BangungotControl8-4")+ "::OnSummon" +(('@flag+1)/2);
	end;
OnTimer8000:
	announce "ビョンウンゴ：呪いにかかった奴らに憑りついてやろう……。",0x9,0xff82ff;
	end;
OnTimer11000:
	announce "ビョンウンゴ：部下たちよ！　行け！　病室の患者たちを苦しめろ!!",0x9,0xff82ff;
	end;
OnTimer13000:
	announce "看護師マエン：まさか……患者の苦しみから力を蓄えるつもり!?",0x9,0xff8200;
	end;
OnTimer15000:
	stopnpctimer;
	announce "看護師マエン：ビョンウンゴが力を蓄える前に病室の部下たちを退治して！",0x9,0xff8200;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@ma_h.gat"),getmdnpcname("BangungotControl8-5")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("BangungotControl8-3")+"::OnStart";
		donpcevent getmdnpcname("BangungotControl8-1")+"::OnEnable";
		donpcevent getmdnpcname("BangungotControl8-2")+"::OnStopTimer";
	}
	stopnpctimer;
	end;
}

1@ma_h.gat,112,177,0	script	BangungotControl9-1	139,{
OnStart:
	donpcevent getmdnpcname("BangungotControl8-2")+"::OnStopTimer";
	donpcevent getmdnpcname("BangungotControl9-2")+ "::OnStart";
	monster getmdmapname("1@ma_h.gat"),131,157,"忌み木のビョンウンゴ",2327,1,getmdnpcname("BangungotControl9-1")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	killmonster "this","All";
	donpcevent getmdnpcname("BangungotControl9-2")+"::OnStopTimer";
	hideoffnpc getmdnpcname("BangungotExit");
	announce "ビョンウンゴ：くっ……これで終わりだと思うな!!　私は必ず戻ってくる!!",0x9,0xff4500;
	end;
OnTimer3000:
	stopnpctimer;
	announce "看護師マエン：お疲れ様！　外に出て報告を聞かせてね。",0x9,0xff8200;
	end;
}

1@ma_h.gat,112,178,0	script	BangungotControl9-2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	announce "看護師マエン：ビョンウンゴの力がどんどん回復しているわ！",0x9,0xff8200;
	misceffect 247,getmdnpcname("BangungotWarp45");
	end;
OnTimer4000:
	announce "看護師マエン：復活してしまう前に早く倒すのよ!!",0x9,0xff8200;
	misceffect 247,getmdnpcname("BangungotWarp45");
	end;
OnTimer7000:
	announce "ビョンウンゴ：私は不死身だ!!",0x9,0xff82ff;
	misceffect 247,getmdnpcname("BangungotWarp45");
	end;
OnTimer14000:
	announce "ビョンウンゴ：殺せるものなら殺してみろ!!　すぐに復活してやる!!",0x9,0xff82ff;
	misceffect 247,getmdnpcname("BangungotWarp45");
	end;
OnTimer21000:
	announce "ビョンウンゴ：このまま勝てるなどと思わないことだな!!",0x9,0xff82ff;
	misceffect 247,getmdnpcname("BangungotWarp45");
	end;
OnTimer31000:
	announce "ビョンウンゴ：ははははは!!　柱の中で力を回復して戻ってきたぞ!!",0x9,0xff82ff;
	killmonster "this",getmdnpcname("BangungotControl9-1")+ "::OnKilled";
	end;
OnTimer36000:
	stopnpctimer;
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnEnable";
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnStart";
	monster getmdmapname("1@ma_h.gat"),143,158,"ビョンウンゴ",2317,1,getmdnpcname("BangungotBoss")+ "::OnKilled";
	end;
OnStopTimer:
	stopnpctimer;
	end;
}

1@ma_h.gat,35,156,0		warp	BangungotExit	1,1,ma_dun01.gat,150,8
1@ma_h.gat,105,157,0	warp	BangungotGate1	1,1,1@ma_h.gat,116,157
1@ma_h.gat,112,157,0	warp	BangungotGate2	1,1,1@ma_h.gat,100,157
1@ma_h.gat,104,63,0		warp	BangungotGate3	1,1,1@ma_h.gat,117,63
1@ma_h.gat,112,63,0		warp	BangungotGate4	1,1,1@ma_h.gat,100,63

1@ma_h.gat,53,157,0		script	BangungotWarp2	139,7,7,{
	warp getmdmapname("1@ma_h.gat"),117,63;
	end;
}

1@ma_h.gat,57,157,0		duplicate(BangungotWarp2)	BangungotWarp3	139,7,7
1@ma_h.gat,67,157,0		duplicate(BangungotWarp2)	BangungotWarp4	139,7,7
1@ma_h.gat,79,157,0		duplicate(BangungotWarp2)	BangungotWarp5	139,7,7
1@ma_h.gat,89,157,0		duplicate(BangungotWarp2)	BangungotWarp6	139,7,7
1@ma_h.gat,100,157,0	duplicate(BangungotWarp2)	BangungotWarp7	139,7,7
1@ma_h.gat,51,173,0		duplicate(BangungotWarp2)	BangungotWarp8	139,10,10
1@ma_h.gat,52,140,0		duplicate(BangungotWarp2)	BangungotWarp34	139,10,10
1@ma_h.gat,73,173,0		duplicate(BangungotWarp2)	BangungotWarp35	139,10,10
1@ma_h.gat,73,140,0		duplicate(BangungotWarp2)	BangungotWarp36	139,10,10
1@ma_h.gat,95,173,0		duplicate(BangungotWarp2)	BangungotWarp37	139,10,10
1@ma_h.gat,95,140,0		duplicate(BangungotWarp2)	BangungotWarp38	139,10,10
1@ma_h.gat,117,171,0	duplicate(BangungotWarp2)	BangungotWarp41	139,10,10
1@ma_h.gat,131,171,0	duplicate(BangungotWarp2)	BangungotWarp42	139,10,10
1@ma_h.gat,146,171,0	duplicate(BangungotWarp2)	BangungotWarp43	139,10,10
1@ma_h.gat,117,157,0	duplicate(BangungotWarp2)	BangungotWarp44	139,10,10
1@ma_h.gat,131,157,0	duplicate(BangungotWarp2)	BangungotWarp45	139,10,10
1@ma_h.gat,146,157,0	duplicate(BangungotWarp2)	BangungotWarp46	139,10,10
1@ma_h.gat,117,143,0	duplicate(BangungotWarp2)	BangungotWarp47	139,10,10
1@ma_h.gat,131,143,0	duplicate(BangungotWarp2)	BangungotWarp48	139,10,10
1@ma_h.gat,146,143,0	duplicate(BangungotWarp2)	BangungotWarp49	139,10,10

1@ma_h.gat,36,63,0		script	BangungotWarp10	139,7,7,{
	warp getmdmapname("1@ma_h.gat"),116,157;
	end;
}

1@ma_h.gat,46,63,0		duplicate(BangungotWarp10)	BangungotWarp11	139,7,7
1@ma_h.gat,56,63,0		duplicate(BangungotWarp10)	BangungotWarp12	139,7,7
1@ma_h.gat,67,63,0		duplicate(BangungotWarp10)	BangungotWarp13	139,7,7
1@ma_h.gat,78,63,0		duplicate(BangungotWarp10)	BangungotWarp14	139,7,7
1@ma_h.gat,89,63,0		duplicate(BangungotWarp10)	BangungotWarp15	139,7,7
1@ma_h.gat,100,63,0		duplicate(BangungotWarp10)	BangungotWarp16	139,7,7
1@ma_h.gat,51,79,0		duplicate(BangungotWarp10)	BangungotWarp17	139,10,10
1@ma_h.gat,51,46,0		duplicate(BangungotWarp10)	BangungotWarp18	139,10,10
1@ma_h.gat,73,80,0		duplicate(BangungotWarp10)	BangungotWarp19	139,10,10
1@ma_h.gat,73,46,0		duplicate(BangungotWarp10)	BangungotWarp20	139,10,10
1@ma_h.gat,95,79,0		duplicate(BangungotWarp10)	BangungotWarp21	139,10,10
1@ma_h.gat,95,46,0		duplicate(BangungotWarp10)	BangungotWarp22	139,10,10
1@ma_h.gat,117,77,0		duplicate(BangungotWarp10)	BangungotWarp25	139,10,10
1@ma_h.gat,131,77,0		duplicate(BangungotWarp10)	BangungotWarp26	139,10,10
1@ma_h.gat,146,77,0		duplicate(BangungotWarp10)	BangungotWarp27	139,10,10
1@ma_h.gat,117,63,0		duplicate(BangungotWarp10)	BangungotWarp28	139,10,10
1@ma_h.gat,131,63,0		duplicate(BangungotWarp10)	BangungotWarp29	139,10,10
1@ma_h.gat,146,63,0		duplicate(BangungotWarp10)	BangungotWarp30	139,10,10
1@ma_h.gat,117,49,0		duplicate(BangungotWarp10)	BangungotWarp31	139,10,10
1@ma_h.gat,131,49,0		duplicate(BangungotWarp10)	BangungotWarp32	139,10,10
1@ma_h.gat,146,49,0		duplicate(BangungotWarp10)	BangungotWarp33	139,10,10

1@ma_h.gat,118,171,0	script	BangungotWarp_a	139,10,10,{
	misceffect 358,strnpcinfo(0);
	donpcevent getmdnpcname("BangungotControl8-1")+ "::OnDisable";
	donpcevent getmdnpcname("BangungotControl8-2")+ "::OnStart";
	end;
}

1@ma_h.gat,132,171,0	duplicate(BangungotWarp_a)	BangungotWarp_b	139,10,10
1@ma_h.gat,147,171,0	duplicate(BangungotWarp_a)	BangungotWarp_c	139,10,10
1@ma_h.gat,118,157,0	duplicate(BangungotWarp_a)	BangungotWarp_d	139,10,10
1@ma_h.gat,132,157,0	duplicate(BangungotWarp_a)	BangungotWarp_e	139,10,10
1@ma_h.gat,147,157,0	duplicate(BangungotWarp_a)	BangungotWarp_f	139,10,10
1@ma_h.gat,118,143,0	duplicate(BangungotWarp_a)	BangungotWarp_g	139,10,10
1@ma_h.gat,132,143,0	duplicate(BangungotWarp_a)	BangungotWarp_h	139,10,10

1@ma_h.gat,131,62,0	script	BangungotEvent	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	misceffect 63;
	initnpctimer;
	end;
}

1@ma_h.gat,43,86,4	script	唸っている患者::BangungotPatient01	584,{
	end;
OnStart:
	initnpctimer;
	announce "唸っている患者：うう……うっ……く……!!",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,60,87,4	script	絶叫する患者::BangungotPatient02	585,{
	end;
OnStart:
	initnpctimer;
	announce "絶叫する患者: うわあああああああああああ!! ",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,60,39,7	script	苦しんでいる患者::BangungotPatient03	584,{
	end;
OnStart:
	initnpctimer;
	announce "苦しんでいる患者：痛い……痛い……!!",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,43,39,7	script	気絶した患者::BangungotPatient04	585,{
	end;
OnStart:
	initnpctimer;
	announce "気絶した患者:う、うう……!! ",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,77,86,4	script	悪夢を見る患者::BangungotPatient05	584,{
	end;
OnStart:
	initnpctimer;
	announce "悪夢を見る患者：助けて!!　誰か助けて!!　ああ……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,69,87,4	script	痛そうに見える患者::BangungotPatient06	585,{
	end;
OnStart:
	initnpctimer;
	announce "痛そうに見える患者：はああ……う……ううう……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,73,39,7	script	恐怖に怯えてる患者::BangungotPatient07	584,{
	end;
OnStart:
	initnpctimer;
	announce "恐怖に怯えている患者：あっちに行って!!　お願い……来ないで……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,65,51,7	script	悲しんでいる患者::BangungotPatient08	585,{
	end;
OnStart:
	initnpctimer;
	announce "悲しんでいる患者：うう……どうして……こんな……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,87,86,4	script	顔を歪める患者::BangungotPatient09	584,{
	end;
OnStart:
	initnpctimer;
	announce "顔を歪める患者：もうやめて……お願い……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,104,86,4	script	身悶える患者::BangungotPatient10	585,{
	end;
OnStart:
	initnpctimer;
	announce "身悶える患者：くわああ……う……くっ……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,99,39,7	script	冷汗をかく患者::BangungotPatient11	584,{
	end;
OnStart:
	initnpctimer;
	announce "冷汗をかく患者：はああ……た、助けて……。",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,87,39,7	script	叫んでいる患者::BangungotPatient12	585,{
	end;
OnStart:
	initnpctimer;
	announce "叫んでいる患者：く、来るなあああああああああああ!!",0x9,0xff0000;
OnTimer5000:
OnTimer8000:
OnTimer11000:
OnTimer14000:
OnTimer17000:
OnTimer20000:
OnTimer23000:
OnTimer26000:
	misceffect 220;
	misceffect 196;
	end;
OnTimer30000:
	stopnpctimer;
	misceffect 220;
	misceffect 196;
	end;
}

1@ma_h.gat,43,181,4	script	唸っている患者	584,{}
1@ma_h.gat,60,182,4	script	絶叫する患者	585,{}
1@ma_h.gat,60,132,7	script	苦しんでいる患者	584,{}
1@ma_h.gat,43,132,7	script	気絶した患者	585,{}
1@ma_h.gat,77,182,4	script	悪夢を見る患者	584,{}
1@ma_h.gat,69,182,4	script	痛そうに見える患者	585,{}
1@ma_h.gat,73,132,7	script	恐怖に怯えてる患者	584,{}
1@ma_h.gat,65,144,7	script	悲しんでいる患者	585,{}
1@ma_h.gat,87,181,4	script	顔を歪める患者	584,{}
1@ma_h.gat,104,181,4	script	身悶える患者	585,{}
1@ma_h.gat,99,132,7	script	冷汗をかく患者	584,{}
1@ma_h.gat,87,132,7	script	叫んでいる患者	585,{}
