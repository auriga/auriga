//= Auriga Script ==============================================================
// Ragnarok Online Bakonawa Lake Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
ma_scene01.gat,174,179,4	script	タホー	541,{
	if(BaseLevel < 140) {
		mes "[タホー]";
		mes "ここはとても危険な場所です。";
		mes "街に戻って下さい！";
		next;
		mes "‐このクエストを進行するには";
		mes "　レベルが足りないようです。";
		mes "　^FF0000Baseレベル140以上^000000になったら";
		mes "　再度話しかけてください‐";
		close;
	}
	if(MALAYA_6QUE < 7 && MALAYA_7QUE < 15) {
		mes "[タホー]";
		mes "バコナワのせいで";
		mes "私たちはみんな死ぬかもしれません。";
		mes "誰か、バコナワを退治してくれる";
		mes "強い人が現れないだろうか……";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[タホー]";
		mes "この先は一人では危険です。";
		mes "パーティーを結成して来て下さい。";
		close;
	}
	if(checkquest(12279) & 0x4) {
		mes "[タホー]";
		mes "バコナワを退治した時に";
		mes "こんなものを拾いました。";
		mes "もしかしたら、あなたたちの";
		mes "役に立つかもしれませんね。";
		getitem 6499,5;
		if(checkre()) {
			getexp 500000,0;
			getexp 500000,0;
			getexp 500000,0;
			getexp 500000,0;
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,300000;
		}
		else {
			getexp 5000000,0;
			getexp 5000000,0;
			getexp 0,5000000;
		}
		delquest 12279;
		close;
	}
	if(checkquest(12278)) {
		if(!(checkquest(12278) & 0x2)) {
			mes "[タホー]";
			mes "バコナワ湖に下りるための";
			mes "命綱を使い切ってしまいました。";
			mes "用意に時間がかかるので、";
			mes "また今度来てください。";
			close;
		}
		mes "[タホー]";
		mes "命綱の用意ができました。";
		mes "これでバコナワ湖に";
		mes "行くことができます。";
		delquest 12278;
		close;
	}
	setquest 12279;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[タホー]";
		mes "バコナワ退治を任された人ですね？";
		mes "絶壁を下りるため";
		mes "しっかり準備をしてください。";
		set '@str1$,"命綱を巻いて下さい";
		set '@str2$,"今から下ります";
	}
	else {
		mes "[タホー]";
		mes "バコナワを退治するために";
		mes "来てくれたんですね。";
		mes "リーダーと私で、絶壁を下りるための";
		mes "命綱を巻きますね。";
		set '@str2$,"今から下ります";
	}
	next;
	switch(select('@str1$,'@str2$,"キャンセル")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[タホー]";
			mes "おや？";
			mes "いつの間にかリーダーでは";
			mes "なくなってしまっていますね。";
			mes "リーダーを連れてきてください。";
			close;
		}
		mdcreate "Bakonawa Lake";
		mes "[タホー]";
		mes "それでは、命綱を巻きます。";
		close;
	case 2:
		switch(mdenter("Bakonawa Lake")) {
		case 0:	// エラーなし
			announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Bakonawa Lake]に入場します",0x9,0x00FF99;
			setquest 12278;
			donpcevent getmdnpcname("BakonawaControl")+ "::OnStart";
			end;
		case 1:	// パーティー未加入
			mes "[タホー]";
			mes "君のパーティーに絶壁を下りる";
			mes "許可は出ていませんよ。";
			close;
		case 2:	// ダンジョン未作成
			mes "[タホー]";
			mes "まだ命綱を体に巻いていません。";
			mes "早まらないでください。";
			close;
		default:	// その他エラー
			close;
		}
	case 3:
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[タホー]";
			mes "準備がまだ終わっていないのですか？";
			mes "できるだけ早く準備を終わらせて、";
			mes "バコナワを退治してくださいね！";
		}
		close;
	}
}

//============================================================
// バコナワの棲み処
//------------------------------------------------------------
1@ma_b.gat,0,0,0	script	BakonawaControl	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("タホー#完了");
	hideonnpc getmdnpcname("タホー#失敗");
	end;
}

1@ma_b.gat,63,52,4	script	タホー#nf	541,{
	mes "[タホー]";
	mes "いよいよバコナワとの戦闘です。";
	mes "できることなら私も加勢したいのですが";
	mes "みなさんのように強くないので";
	mes "岩陰に隠れていますね。";
	next;
	mes "[タホー]";
	mes "バコナワは、時間が経つと";
	mes "湖の底に逃げてしまいます。";
	mes "また、攻撃が通じない状態になる";
	mes "場合もあります。";
	mes "私が岩陰からサポートしますので";
	mes "確認しながら戦ってください。";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[タホー]";
		mes "では、今からバコナワを";
		mes "湖の上に引きずり出して見せます。";
		mes "まずは10分以内に倒してください。";
		next;
		if(select("待って！　まだだ！","わかった、では始めよう！") == 1) {
			mes "[タホー]";
			mes "あ……危ないじゃないですか！";
			mes "あやうく呼び出す所でしたよ。";
			close;
		}
		mes "[タホー]";
		mes "では、特殊な薬を湖に";
		mes "一滴落としてみます。";
		next;
		mes "[タホー]";
		mes "湖への影響は短時間ですが、";
		mes "バコナワの奴は敏感に反応して";
		mes "水面に飛び出してくるでしょう。";
		donpcevent getmdnpcname("#バコナワn1")+"::OnStart";
		hideonnpc getmdnpcname("タホー#nf");
		close;
	}
	else {
		mes "[タホー]";
		mes "準備ができたら、リーダーから";
		mes "話しかけるよう伝えてください。";
		close;
	}
}

1@ma_b.gat,36,111,4	script	#バコナワn1	844,{
OnStart:
	announce "タホー：バコナワが現れました！　10分以内に倒してください！",0x9,0x00ffff,0x190,15;
	monster getmdmapname("1@ma_b.gat"),78,83,"バコナワ",2320,1,getmdnpcname("#バコナワn1")+"::OnKilled";
	initnpctimer;
	end;
OnKilled:
	donpcevent getmdnpcname("#バコナワ討伐n1")+"::OnStart";
	stopnpctimer;
	hideonnpc getmdnpcname("#バコナワn1");
	end;
OnTimer1000:	callsub OnAnnounce,"10分",15;
OnTimer60000:	callsub OnAnnounce,"9分",15;
OnTimer120000:	callsub OnAnnounce,"8分",15;
OnTimer180000:	callsub OnAnnounce,"7分",15;
OnTimer240000:	callsub OnAnnounce,"6分",15;
OnTimer300000:	callsub OnAnnounce,"5分",15;
OnTimer360000:	callsub OnAnnounce,"4分",15;
OnTimer420000:	callsub OnAnnounce,"3分",15;
OnTimer480000:	callsub OnAnnounce,"2分",15;
OnTimer540000:	callsub OnAnnounce,"1分",15;
OnTimer570000:	callsub OnAnnounce,"30秒",18;
OnTimer600000:
	announce "バコナワが湖の中に逃げて行きました。",0x9,0xffff00,0x190,20;
	donpcevent getmdnpcname("タホー#失敗")+"::OnStart";
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn1")+"::OnKilled";
	stopnpctimer;
	hideonnpc getmdnpcname("#バコナワn1");
	end;
OnAnnounce:
	announce "制限時間"+getarg(0),0x9,0xFF4400,0x190,getarg(1);
	donpcevent getmdnpcname("#手下召喚n1")+"::OnStart";
	end;
}

1@ma_b.gat,78,81,0	script	#手下召喚n1	139,4,5,{
OnStart:
	hideoffnpc getmdnpcname("#手下召喚n1");
	initnpctimer;
	end;
OnTouch:
	stopnpctimer;
	hideonnpc getmdnpcname("#手下召喚n1");
	end;
OnTimer5000:
	set '@map$,getmdmapname("1@ma_b.gat");
	setarray '@x,79,71,60,61,57,89,95,96,99;
	setarray '@y,71,72,80,90,99,73,82,90,99;
	for(set '@i,0; '@i<9; set '@i,'@i+1) {
		set '@rand,rand(1,10);
		if('@rand > 7)
			monster '@map$,'@x['@i],'@y['@i],"バコナワの意志",2337,1,getmdnpcname("#手下召喚n1")+"::OnKilled";
		else if('@rand < 4)
			monster '@map$,'@x['@i],'@y['@i],"バコナワの意志",2343,1,getmdnpcname("#手下召喚n1")+"::OnKilled";
	}
	hideonnpc getmdnpcname("#手下召喚n1");
	end;
OnTimer50000:
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#手下召喚n1")+"::OnKilled";
	stopnpctimer;
	end;
OnKilled:
	end;
}

1@ma_b.gat,1,5,4	script	#バコナワ討伐n1	844,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer100:
	announce "タホー：まだです！　伝説によると、バコナワは月を飲み込もうと再び姿を見せるはずです！",0x9,0x00ffff,0x190,15;
	end;
OnTimer5000:
	announce "タホー：奴が月に集中できないように、鍋と太鼓を壊れるくらい叩いて邪魔してください！",0x9,0x00ffff,0x190,15;
	end;
OnTimer10000:
	announce "タホー：奴が水の上に現れても無視してください。鍋と太鼓を叩くことに集中するんです！",0x9,0x00ffff,0x190,15;
	end;
OnTimer15000:
	announce "目標‐湖の左右にある鍋と太鼓を4個、壊れるまで攻撃する‐",0x9,0xff3300,0x190,15;
	donpcevent getmdnpcname("#バコナワn2")+"::OnStart";
	stopnpctimer;
	end;
}

1@ma_b.gat,36,111,4	script	#バコナワn2	844,{
	end;
OnStart:
	set '@label$, getmdnpcname("#バコナワn2")+"::OnKilled";
	set '@map$, getmdmapname("1@ma_b.gat");
	monster '@map$,95,98,"鍋",2328,1,'@label$;
	monster '@map$,60,98,"鍋",2328,1,'@label$;
	monster '@map$,97,104,"太鼓",2328,1,'@label$;
	monster '@map$,58,104,"太鼓",2328,1,'@label$;
	donpcevent getmdnpcname("#バコナワn2-1")+"::OnStart";
	initnpctimer;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn2")+"::OnKilled");
	if('@count < 1) {
		donpcevent getmdnpcname("#バコナワn2-1")+"::OnEnd";
		stopnpctimer;
	}
	else
		announce "タホー：いい感じです、あと"+'@count+"個です！",0x9,0x00ffff,0x190,15;
	end;
OnTimer1000:	callsub OnAnnounce,"5分",15,1;
OnTimer60000:	callsub OnAnnounce,"4分",15,1;
OnTimer120000:	callsub OnAnnounce,"3分",15,1;
OnTimer180000:	callsub OnAnnounce,"2分",15,1;
OnTimer240000:	callsub OnAnnounce,"1分",15,1;
OnTimer270000:	callsub OnAnnounce,"30秒",15,0;
OnTimer280000:	callsub OnAnnounce,"20秒",15,0;
OnTimer290000:	callsub OnAnnounce,"10秒",15,0;
OnTimer295000:	callsub OnAnnounce,"5秒",16,0;
OnTimer296000:	callsub OnAnnounce,"4秒",17,0;
OnTimer297000:	callsub OnAnnounce,"3秒",18,0;
OnTimer298000:	callsub OnAnnounce,"2秒",19,0;
OnTimer299000:	callsub OnAnnounce,"1秒",20,0;
OnTimer300000:
	announce "バコナワが湖の中に逃げて行きました。",0x9,0xffff00,0x190,20;
	donpcevent getmdnpcname("タホー#失敗")+"::OnStart";
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn2")+"::OnKilled";
	stopnpctimer;
	end;
OnAnnounce:
	announce "制限時間"+getarg(0),0x9,0xff4400,0x190,getarg(1);
	if(getarg(2)) donpcevent getmdnpcname("#手下召喚n1")+"::OnStart";
	end;
}

1@ma_b.gat,36,111,4	script	#バコナワn2-1	844,{
	end;
OnInstanceInit:
	disablenpc getmdnpcname("#バコナワn2-1");
	end;
OnStart:
	enablenpc getmdnpcname("#バコナワn2-1");
	monster getmdmapname("1@ma_b.gat"),78,93,"バコナワ",2321,1,getmdnpcname("#バコナワn2-1")+"::OnKilled";
	end;
OnEnd:
	enablenpc getmdnpcname("#バコナワn2-1");
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn2-1")+"::OnKilled";
	initnpctimer;
	end;
OnTimer1000:
	announce "タホー：バコナワが水の中に隠れてしまいましたね。これで終わったのかな？",0x9,0x00ffff,0x190,15;
	end;
OnTimer5000:
	announce "タホー：あっ、水の中で何かが動いています！　やつが来ます！",0x9,0x00ffff,0x190,15;
	end;
OnTimer10000:
	announce "目標‐さらに凶暴になったバコナワを倒すこと‐",0x9,0xff3300,0x190,15;
	donpcevent getmdnpcname("#バコナワn3")+"::OnStart";
	stopnpctimer;
	end;
OnKilled:
	end;
}

1@ma_b.gat,36,111,4	script	#バコナワn3	844,{
	end;
OnStart:
	initnpctimer;
	monster getmdmapname("1@ma_b.gat"),78,83,"Enraged Bakonawa",2322,1,getmdnpcname("#バコナワn3")+"::OnKilled";
	donpcevent getmdnpcname("#バコナワn3-1")+"::OnStart";
	end;
OnKilled:
	announce "タホー：バコナワを退治しました！　これでしばらくの間は平穏に暮らすことができます。",0x9,0x00ffff,0x190,15;
	donpcevent getmdnpcname("タホー#完了")+"::OnStart";
	donpcevent getmdnpcname("#バコナワn3-1")+"::OnEnd";
	stopnpctimer;
	end;
OnTimer1000:
	callsub OnAnnounce,"10分",15,1;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
	donpcevent getmdnpcname("#手下召喚n1")+"::OnStart";
	end;
OnTimer300000:	callsub OnAnnounce,"5分",15,1;
OnTimer360000:	callsub OnAnnounce,"4分",15,1;
OnTimer420000:	callsub OnAnnounce,"3分",15,1;
OnTimer480000:	callsub OnAnnounce,"2分",15,1;
OnTimer540000:	callsub OnAnnounce,"1分",15,1;
OnTimer570000:	callsub OnAnnounce,"30秒",15,0;
OnTimer580000:	callsub OnAnnounce,"20秒",15,0;
OnTimer590000:	callsub OnAnnounce,"10秒",15,0;
OnTimer595000:	callsub OnAnnounce,"5秒",16,0;
OnTimer596000:	callsub OnAnnounce,"4秒",17,0;
OnTimer597000:	callsub OnAnnounce,"3秒",18,0;
OnTimer598000:	callsub OnAnnounce,"2秒",19,0;
OnTimer599000:	callsub OnAnnounce,"1秒",20,0;
OnTimer600000:
	announce "バコナワが湖の中に逃げて行きました。",0x9,0xffff00,0x190,20;
	donpcevent getmdnpcname("タホー#失敗")+"::OnStart";
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn3")+"::OnKilled";
	stopnpctimer;
	end;
OnAnnounce:
	announce "制限時間"+getarg(0),0x9,0xff4400,0x190,getarg(1);
	if(getarg(2)) donpcevent getmdnpcname("#手下召喚n1")+"::OnStart";
	end;
}

1@ma_b.gat,36,111,4	script	#バコナワn3-1	844,{
	end;
OnStart:
	initnpctimer;
	end;
OnEnd:
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn3-1")+"::OnKilled";
	stopnpctimer;
	end;
OnTimer120000:	callsub OnMobSpawn,10;
OnTimer180000:	callsub OnMobSpawn,15;
OnTimer240000:	callsub OnMobSpawn,20;
//OnTimer300000:	callsub OnMobSpawn,25;
OnTimer300000:	callsub OnMobSpawn,30;
OnTimer360000:	callsub OnMobSpawn,35;
OnTimer420000:	callsub OnMobSpawn,40;
OnTimer480000:	callsub OnMobSpawn,45;
OnTimer540000:	callsub OnMobSpawn,50;
OnTimer600000:
	killmonster getmdmapname("1@ma_b.gat"),getmdnpcname("#バコナワn3-1")+"::OnKilled";
	stopnpctimer;
	end;
OnMobSpawn:
	set '@label$, getmdnpcname("#バコナワn3-1")+"::OnKilled";
	set '@map$, getmdmapname("1@ma_b.gat");
	killmonster '@map$,'@label$;
	areamonster '@map$,74,74,82,74,"バコナワの手下",2334,getarg(0),'@label$;
	end;
OnKilled:
	end;
}

1@ma_b.gat,66,64,0	script	タホー#完了	541,{
	mes "[タホー]";
	mes "すごい戦いでしたね！";
	mes "手下が残っていたら危険なので、";
	mes "上に戻りましょう。";
	next;
	mes "[タホー]";
	mes "あ！";
	mes "外で私に話しかけてくれたら、";
	mes "お礼を差し上げますね！";
	close2;
	warp "ma_scene01.gat",175,176;
	end;
OnStart:
	hideoffnpc getmdnpcname("タホー#完了");
	initnpctimer;
	end;
OnTimer1000:
	monster getmdmapname("1@ma_b.gat"),78,74,"バコナワの宝箱",2335,1;
	end;
OnTimer10000:
	announce "タホー：宝箱を開けたら、私の所に来てください。渡したい物があります。",0x9,0x00ffff,0x190,15;
	stopnpctimer;
	end;
}

1@ma_b.gat,61,52,4	script	タホー#失敗	541,{
	mes "[タホー]";
	mes "取り逃がしてしまいましたね。";
	mes "湖の底に潜ってしまうと、";
	mes "こちらから手出しできません。";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[タホー]";
		mes "もう一度挑戦しますか？";
		next;
		switch(select("ちょっと待って","もう一度呼び出してくれ","あきらめて帰る")) {
		case 1:
			mes "[タホー]";
			mes "あ……危ないじゃないですか！";
			mes "あやうく呼び出す所でしたよ。";
			close;
		case 2:
			mes "[タホー]";
			mes "では、あらためて";
			mes "特殊な薬を湖に落としてみます。";
			next;
			mes "[タホー]";
			mes "私は隠れます。";
			mes "まずは10分以内に";
			mes "バコナワを倒してください！";
			donpcevent getmdnpcname("#バコナワn1")+"::OnStart";
			hideonnpc getmdnpcname("タホー#失敗");
			close;
		case 3:
			mes "[タホー]";
			mes "無念です。";
			mes "腕を磨いて、次回は退治しましょう。";
			next;
			mes "[タホー]";
			mes "それでは、戻りましょう。";
			close2;
			warp "ma_scene01.gat",175,176;
			end;
		}
	}
	else {
		mes "[タホー]";
		mes "もう一度挑戦するか";
		mes "リーダーと相談してください。";
		next;
		if(select("もう一度呼び出してくれ","あきらめて帰る") == 1) {
			mes "[タホー]";
			mes "それでは、リーダーから";
			mes "話しかけるよう伝えてください。";
			close;
		}
		mes "[タホー]";
		mes "無念です。";
		mes "腕を磨いて、次回は退治しましょう。";
		next;
		mes "[タホー]";
		mes "それでは、戻りましょう。";
		close2;
		warp "ma_scene01.gat",175,176;
		end;
	}
OnStart:
	hideoffnpc getmdnpcname("タホー#失敗");
	end;
}

//1@ma_b.gat,62,51,0	warp	#バコナワ入口テレポ	2,2,ma_scene01.gat,175,176
