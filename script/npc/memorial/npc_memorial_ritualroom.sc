1@mir.gat,0,0,0		script	Mir_Contorl	-1,{
OnStart:
	hideonnpc getmdnpcname("パワフルアムダライス#03");
	hideonnpc getmdnpcname("#result");
	hideonnpc getmdnpcname("#effect01");
	hideonnpc getmdnpcname("ビジョウ#00");
	hideonnpc getmdnpcname("ビジョウ#02");
	hideonnpc getmdnpcname("ビジョウ#03");
	hideonnpc getmdnpcname("ビジョウ#04");
	hideonnpc getmdnpcname("ビジョウ#ex");
	hideonnpc getmdnpcname("サラ#04");
	hideonnpc getmdnpcname("#mir_bgm01");
	hideonnpc getmdnpcname("#mir_bgm02");
	areasetcell getmdmapname("1@mir.gat"),88,52,115,53,1;
	areasetcell getmdmapname("1@mir.gat"),78,83,125,84,1;
	set 'cell,1;
	initnpctimer;
	end;
OnTimer3000:
	areasetcell getmdmapname("1@mir.gat"),88,52,115,53,'cell;
	areasetcell getmdmapname("1@mir.gat"),78,83,125,84,'cell;
	initnpctimer;
	end;
}
1@mir.gat,0,1,0		script	Mir_Phase1	-1,{
OnStart:
	set 'mob,9;
	monster getmdmapname("1@mir.gat"),97,71,"パワフルAスケルトン",3445,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),107,72,"パワフルAスケルトン",3445,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),106,69,"パワフルAスケルトン",3445,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),99,77,"パワフルスケルトン",3446,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),104,77,"パワフルスケルトン",3446,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),107,75,"パワフルスケルトン",3446,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),97,76,"パワフルSスケルトン",3447,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),98,69,"パワフルSスケルトン",3447,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),102,69,"パワフルSスケルトン",3447,1,getmdnpcname("Mir_Phase1")+"::OnKilled";
	end;
OnKilled:
	set 'mob,'mob-1;
	if('mob <= 0)
		initnpctimer;
	end;
OnTimer5000:
	stopnpctimer;
	announce "ビジョウ : ふふふ……。", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	hideonnpc getmdnpcname("ビジョウ#00");
	hideoffnpc getmdnpcname("ビジョウ#02");
	end;
}

1@mir.gat,0,2,0		script	Mir_Phase2	-1,{
OnStart:
	monster getmdmapname("1@mir.gat"),101,75,"パワフルアムダライス",3448,1,getmdnpcname("Mir_Phase2")+"::OnKilled";
	end;
OnKilled:
	announce "ビジョウ : へえ……なかなかやるじゃないか。", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	hideonnpc getmdnpcname("ビジョウ#00");
	hideoffnpc getmdnpcname("ビジョウ#03");
	end;
}

1@mir.gat,0,3,0		script	#ビジョウ管理	-1,{
OnStart:
	set 'bijou,callmonster(getmdmapname("1@mir.gat"),101,79,"ビジョウ",3450,getmdnpcname("#ビジョウ管理")+"::OnKilled");
	initnpctimer;
	end;
OnTimer3000:
	set 'mobhp,getmobhp('bijou);
	if('mobhp < 7000000) {
		stopnpctimer;
		killmonster getmdmapname("1@mir.gat"),getmdnpcname("#ビジョウ管理")+"::OnKilled";
		initnpctimer getmdnpcname("#実験体アムダ");
		hideoffnpc getmdnpcname("ビジョウ#ex");
		end;
	}
	initnpctimer;
	end;
OnKilled:
	stopnpctimer;
	stopnpctimer getmdnpcname("#ビジョウ管理2");
	hideoffnpc getmdnpcname("ビジョウ#04");
	hideoffnpc getmdnpcname("#result");
	end;
}

1@mir.gat,0,4,0		script	#実験体アムダ	-1,{
OnTimer2000:
	announce "ビジョウ : なかなか頑張るな……ならばこれはどうだ？", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	end;
OnTimer4000:
	hideoffnpc getmdnpcname("#mir_bgm01");
	end;
OnTimer6000:
	monster getmdmapname("1@mir.gat"),101,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,69,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer10000:
	announce "ビジョウ : こいつらはアムダライスの失敗作さ。", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	monster getmdmapname("1@mir.gat"),102,81,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),102,73,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),102,63,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer12000:
	monster getmdmapname("1@mir.gat"),118,78,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,68,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,63,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer14000:
	announce "ビジョウ : このまま破棄されるなんて可哀想だろう？", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	monster getmdmapname("1@mir.gat"),101,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,69,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer15000:
	monster getmdmapname("1@mir.gat"),102,58,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,58,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),101,57,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer16000:
	monster getmdmapname("1@mir.gat"),102,68,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,63,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer18000:
	announce "ビジョウ : 思いっきり遊んでやっておくれよ。ははははは!!", 0x9, 0xff0000, 0x0190, 20, 0, 0;
	monster getmdmapname("1@mir.gat"),102,81,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),102,78,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),111,81,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer20000:
	monster getmdmapname("1@mir.gat"),118,78,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,73,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),102,58,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer22000:
	monster getmdmapname("1@mir.gat"),101,57,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),118,69,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),91,61,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer24000:
	monster getmdmapname("1@mir.gat"),90,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	monster getmdmapname("1@mir.gat"),101,80,"実験体アムダライス",3778,1,getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnTimer40000:
	stopnpctimer;
	killmonster getmdmapname("1@mir.gat"),getmdnpcname("#実験体アムダ")+"::OnKilled";
	end;
OnKilled:
	end;
}

1@mir.gat,0,5,0		script	#ビジョウ管理2	-1,{
OnStart:
	set 'bijou,callmonster(getmdmapname("1@mir.gat"),101,79,"ビジョウ",3450,getmdnpcname("#ビジョウ管理")+"::OnKilled");
	setmobhp 'bijou,getvariableofnpc('mobhp,getmdnpcname("#ビジョウ管理"));
	initnpctimer;
	end;
OnTimer16000:
	switch(rand(4)) {
	case 0: donpcevent getmdnpcname("#マントル")+"::OnStart"; break;
	case 1: donpcevent getmdnpcname("#フロストダイバー")+"::OnStart"; break;
	case 2: donpcevent getmdnpcname("#耐え難い苦痛")+"::OnStart"; break;
	case 3: donpcevent getmdnpcname("#アムダライス")+"::OnStart"; break;
	}
	initnpctimer;
	end;
}

1@mir.gat,1,0,0		script	#マントル	-1,{
OnStart:
	set '@mob_id,getvariableofnpc('bijou,getmdnpcname("#ビジョウ管理2"));
	unittalk '@mob_id,"ビジョウ : マントル・エクスプロージョン！";
	set 'mob1,callmonster(getmdmapname("1@mir.gat"),85,83,"ビジョウ#01",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob2,callmonster(getmdmapname("1@mir.gat"),85,78,"ビジョウ#02",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob3,callmonster(getmdmapname("1@mir.gat"),85,73,"ビジョウ#03",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob4,callmonster(getmdmapname("1@mir.gat"),85,68,"ビジョウ#04",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob5,callmonster(getmdmapname("1@mir.gat"),85,63,"ビジョウ#05",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob7,callmonster(getmdmapname("1@mir.gat"),102,83,"ビジョウ#07",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob8,callmonster(getmdmapname("1@mir.gat"),102,78,"ビジョウ#08",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob9,callmonster(getmdmapname("1@mir.gat"),102,73,"ビジョウ#09",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob10,callmonster(getmdmapname("1@mir.gat"),102,68,"ビジョウ#10",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob11,callmonster(getmdmapname("1@mir.gat"),102,63,"ビジョウ#11",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob13,callmonster(getmdmapname("1@mir.gat"),118,83,"ビジョウ#13",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob14,callmonster(getmdmapname("1@mir.gat"),118,78,"ビジョウ#14",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob15,callmonster(getmdmapname("1@mir.gat"),118,73,"ビジョウ#15",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob16,callmonster(getmdmapname("1@mir.gat"),118,68,"ビジョウ#16",3773,getmdnpcname("#マントル")+"::OnKilled");
	set 'mob17,callmonster(getmdmapname("1@mir.gat"),118,63,"ビジョウ#17",3773,getmdnpcname("#マントル")+"::OnKilled");
	sleep 2000;
	mobuseskill 'mob7,2216,5,0,0,0,-1,0;
	mobuseskill 'mob8,2216,5,0,0,0,-1,0;
	mobuseskill 'mob9,2216,5,0,0,0,-1,0;
	mobuseskill 'mob10,2216,5,0,0,0,-1,0;
	mobuseskill 'mob11,2216,5,0,0,0,-1,0;
	sleep 2000;
	mobuseskill 'mob1,2216,5,0,0,0,-1,0;
	mobuseskill 'mob2,2216,5,0,0,0,-1,0;
	mobuseskill 'mob3,2216,5,0,0,0,-1,0;
	mobuseskill 'mob4,2216,5,0,0,0,-1,0;
	mobuseskill 'mob5,2216,5,0,0,0,-1,0;
	mobuseskill 'mob13,2216,5,0,0,0,-1,0;
	mobuseskill 'mob14,2216,5,0,0,0,-1,0;
	mobuseskill 'mob15,2216,5,0,0,0,-1,0;
	mobuseskill 'mob16,2216,5,0,0,0,-1,0;
	mobuseskill 'mob17,2216,5,0,0,0,-1,0;
	sleep 1000;
	killmonster getmdmapname("1@mir.gat"),getmdnpcname("#マントル")+"::OnKilled";
	end;
OnKilled:
	end;
}
1@mir.gat,2,0,0		script	#フロストダイバー	-1,{
OnStart:
	set '@mob_id,getvariableofnpc('bijou,getmdnpcname("#ビジョウ管理2"));
	unittalk '@mob_id,"ビジョウ : 凍りつけ……";
	set 'mob1,callmonster(getmdmapname("1@mir.gat"),85,80,"ビジョウ#01",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	set 'mob2,callmonster(getmdmapname("1@mir.gat"),85,66,"ビジョウ#02",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	set 'mob4,callmonster(getmdmapname("1@mir.gat"),101,70,"ビジョウ#04",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	set 'mob5,callmonster(getmdmapname("1@mir.gat"),101,80,"ビジョウ#05",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	set 'mob6,callmonster(getmdmapname("1@mir.gat"),118,80,"ビジョウ#06",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	set 'mob7,callmonster(getmdmapname("1@mir.gat"),118,69,"ビジョウ#07",3773,getmdnpcname("#フロストダイバー")+"::OnKilled");
	sleep 2000;
	mobuseskill '@mob_id,720,5,0,0,0,-1,0;
	mobuseskill 'mob1,720,5,0,0,0,-1,0;
	mobuseskill 'mob4,720,5,0,0,0,-1,0;
	mobuseskill 'mob6,720,5,0,0,0,-1,0;
	unittalk '@mob_id,"ビジョウ : フロストダイバー！";
	sleep 1000;
	mobuseskill 'mob2,720,5,0,0,0,-1,0;
	mobuseskill 'mob5,720,5,0,0,0,-1,0;
	mobuseskill 'mob7,720,5,0,0,0,-1,0;
	sleep 1000;
	mobuseskill '@mob_id,720,5,0,0,0,-1,0;
	mobuseskill 'mob1,720,5,0,0,0,-1,0;
	mobuseskill 'mob4,720,5,0,0,0,-1,0;
	mobuseskill 'mob6,720,5,0,0,0,-1,0;
	sleep 1000;
	mobuseskill 'mob2,720,5,0,0,0,-1,0;
	mobuseskill 'mob5,720,5,0,0,0,-1,0;
	mobuseskill 'mob7,720,5,0,0,0,-1,0;
	sleep 1000;
	killmonster getmdmapname("1@mir.gat"),getmdnpcname("#フロストダイバー")+"::OnKilled";
	end;
OnKilled:
	end;
}
1@mir.gat,2,0,0		script	#耐え難い苦痛	-1,{
OnStart:
	set '@mob_id,getvariableofnpc('bijou,getmdnpcname("#ビジョウ管理2"));
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'@mob_id);
	mobuseskillpos '@mob_id,727,1,'@x,'@y,0,0;
	unittalk '@mob_id,"ビジョウ : 耐え難い苦痛を与えてやろう。";
	sleep 1000;
	mobuseskillpos '@mob_id,483,1,'@x-6,'@y-3,0,0;
	mobuseskillpos '@mob_id,483,1,'@x-6,'@y+3,0,0;
	mobuseskillpos '@mob_id,483,1,'@x-3,'@y-6,0,0;
	mobuseskillpos '@mob_id,483,1,'@x-3,'@y,0,0;
	mobuseskillpos '@mob_id,483,1,'@x-3,'@y+6,0,0;
	mobuseskillpos '@mob_id,483,1,'@x,'@y-3,0,0;
	mobuseskillpos '@mob_id,483,1,'@x,'@y+3,0,0;
	mobuseskillpos '@mob_id,483,1,'@x+3,'@y+6,0,0;
	mobuseskillpos '@mob_id,483,1,'@x+3,'@y,0,0;
	mobuseskillpos '@mob_id,483,1,'@x+3,'@y-6,0,0;
	mobuseskillpos '@mob_id,483,1,'@x+6,'@y-3,0,0;
	mobuseskillpos '@mob_id,483,1,'@x+6,'@y+3,0,0;
	sleep 1000;
	unittalk '@mob_id,"ビジョウ : 死ね！";
	mobuseskill '@mob_id,661,5,0,0,0,-1,0;
	end;
}

1@mir.gat,3,0,0		script	#アムダライス	-1,{
OnStart:
	set '@mob_id,getvariableofnpc('bijou,getmdnpcname("#ビジョウ管理2"));
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'@mob_id);
	unittalk '@mob_id,"ビジョウ : アムダライス！";
	areamonster getmdmapname("1@mir.gat"),80,59,90,80,"実験体アムダライス",3778,1,getmdnpcname("#アムダライス")+"::OnKilled";
	areamonster getmdmapname("1@mir.gat"),90,59,100,80,"実験体アムダライス",3778,1,getmdnpcname("#アムダライス")+"::OnKilled";
	areamonster getmdmapname("1@mir.gat"),100,59,110,80,"実験体アムダライス",3778,1,getmdnpcname("#アムダライス")+"::OnKilled";
	areamonster getmdmapname("1@mir.gat"),110,59,120,80,"実験体アムダライス",3778,1,getmdnpcname("#アムダライス")+"::OnKilled";
	initnpctimer;
	end;
OnTimer10000:
	killmonster getmdmapname("1@mir.gat"),getmdnpcname("#アムダライス")+"::OnKilled";
	end;
OnKilled:
	end;
}

1@mir.gat,101,75,3	script	パワフルアムダライス#03	3448,{}
1@mir.gat,101,75,0	script	#result	139,{}
1@mir.gat,101,79,0	script	#effect01	139,{}
1@mir.gat,101,81,3	script	ビジョウ#01	10143,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0))
		end;
	mes "‐祭壇の前に人影がある‐";
	next;
	mes "^ff0000‐注意‐";
	mes "　^ff0000「先に進む」を選んだ時点で";
	mes "　^ff0000このマップにいない";
	mes "　^ff0000パーティーメンバーは";
	mes "　^ff0000報酬を受け取ることができません。^000000";
	next;
	mes "^ff0000‐注意‐";
	mes "　^ff0000他にパーティーメンバーが";
	mes "　^ff0000いた場合、メンバーが揃ったのを";
	mes "　^ff0000確認してから先に進んでください。^000000";
	next;
	mes "‐先に進みますか？‐";
	next;
	if(select("少し待つ","先に進む")==1) {
		mes "‐あなたは様子を見ることにした‐";
		close;
	}
	cutin "bijou_01.bmp", 2;
	mes "[ビジョウ]";
	mes "人間か……";
	mes "結界を張ったから";
	mes "外からは入れないはずだが……";
	mes "どうやって中に入ってきた？";
	mes "貴様もユミルの心臓が目的か？";
	unittalk "ビジョウ : 人間か……結界を張ったから外からは入れないはずだが……どうやって中に入ってきた？　貴様もユミルの心臓が目的か？";
	next;
	mes "[ビジョウ]";
	mes "……まあいい。";
	mes "せっかくここまで来たんだ。";
	mes "少し遊んでいくがいい。";
	unittalk "ビジョウ : ……まあいい。せっかくここまで来たんだ。少し遊んでいくがいい。";
	next;
	mes "[ビジョウ]";
	mes "ヒメルメズ様の祝福を受けた";
	mes "この不死の軍団とな！";
	unittalk "ビジョウ : ヒメルメズ様の祝福を受けたこの不死の軍団とな！";
	close2;
	cutin "bijou_01.bmp", 255;
	if(!sleep2(1000)) end;
	hideonnpc getmdnpcname("ビジョウ#01");
	misceffect 90,getmdnpcname("#effect01");
	donpcevent getmdnpcname("Mir_Phase1")+ "::OnStart";
	end;
}

1@mir.gat,101,81,3	script	ビジョウ#02	10143,{
	cutin "bijou_01.bmp", 2;
	mes "[ビジョウ]";
	mes "ふふふ……";
	mes "人間のくせに頑張るじゃないか。";
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		close2;
		cutin "bijou_01.bmp", 255;
		end;
	}
	unittalk "ビジョウ : ふふふ……人間のくせに頑張るじゃないか。";
	next;
	cutin "bijou_02.bmp", 2;
	mes "[ビジョウ]";
	mes "じゃあこれはどうだ？";
	mes "さあ、立ち上がれ！　私のしもべよ！";
	unittalk "ビジョウ : じゃあこれはどうだ？　さあ、立ち上がれ！　私のしもべよ！";
	misceffect 8,getmdnpcname("パワフルアムダライス#03");
	if(!sleep2(2000)) end;
	misceffect 6,getmdnpcname("パワフルアムダライス#03");
	hideoffnpc getmdnpcname("パワフルアムダライス#03");
	if(!sleep2(1000)) end;
	misceffect 668,getmdnpcname("パワフルアムダライス#03");
	next;
	cutin "bijou_01.bmp", 2;
	mes "[ビジョウ]";
	mes "死ぬ前に教えてやろう。";
	mes "私の名前はビジョウ。";
	mes "12ヴァルキリー、ヒメルメズ様の";
	mes "副官を勤めている。";
	unittalk "ビジョウ : 死ぬ前に教えてやろう。私の名前はビジョウ。12ヴァルキリー、ヒメルメズ様の副官を勤めている。";
	next;
	mes "[ビジョウ]";
	mes "少し待っていろ。";
	mes "ユミルの心臓の封印が解けたら……";
	mes "私が自ら相手をしてやろう。";
	unittalk "ビジョウ : 少し待っていろ。ユミルの心臓の封印が解けたら……私が自ら相手をしてやろう。";
	next;
	mes "[ビジョウ]";
	mes "もっとも……";
	mes "お前がその時まで";
	mes "アムダライスを相手に";
	mes "生きていられたらの話だがな。";
	unittalk "ビジョウ : もっとも……お前がその時までアムダライスを相手に生きていられたらの話だがな。";
	close2;
	cutin "bijou_01.bmp", 255;
	hideonnpc getmdnpcname("パワフルアムダライス#03");
	hideonnpc getmdnpcname("ビジョウ#02");
	hideoffnpc getmdnpcname("ビジョウ#00");
	donpcevent getmdnpcname("Mir_Phase2")+ "::OnStart";
	end;
}
1@mir.gat,101,81,3	script	ビジョウ#03	10143,{
	cutin "bijou_01.bmp", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ビジョウ]";
		mes "ふふふ……";
		mes "そんなに簡単に殺しはしない。";
		mes "3年分の代価……";
		mes "支払ってもらうとしようか。";
		close2;
		cutin "bijou_01.bmp", 255;
		end;
	}
	mes "[ビジョウ]";
	mes "意外だったよ。";
	mes "ふふふ……";
	mes "まさか私が3年の月日をかけて";
	mes "完成させたアムダライスを";
	mes "倒すとは……";
	unittalk "ビジョウ : 意外だったよ。ふふふ……まさか私が3年の月日をかけて完成させたアムダライスを倒すとは……";
	next;
	mes "[ビジョウ]";
	mes "ふふふ……";
	mes "そんなに簡単に殺しはしない。";
	mes "3年分の代価……";
	mes "支払ってもらうとしようか。";
	unittalk "ビジョウ : ふふふ……そんなに簡単に殺しはしない。3年分の代価……支払ってもらうとしようか。";
	next;
	cutin "bijou_02.bmp", 2;
	mes "[ビジョウ]";
	mes "ゆっくりと……";
	mes "最大の苦痛でなぁ。";
	unittalk "ビジョウ : ゆっくりと……最大の苦痛でなぁ。";
	close2;
	cutin "bijou_02.bmp", 255;
	misceffect 383,getmdnpcname("ビジョウ#03");
	if(!sleep2(900)) end;
	misceffect 408,getmdnpcname("ビジョウ#03");
	if(!sleep2(1000)) end;
	misceffect 409,getmdnpcname("ビジョウ#03");
	hideonnpc getmdnpcname("ビジョウ#03");
	donpcevent getmdnpcname("#ビジョウ管理")+ "::OnStart";
	end;
}
1@mir.gat,101,81,3	script	ビジョウ#ex	10143,{
	cutin "bijou_01.bmp", 2;
	if(getnpctimer(1,getmdnpcname("#実験体アムダ"))) {
		mes "[ビジョウ]";
		mes "ふふふ……";
		mes "お喋りとは余裕だねぇ？";
		close2;
		cutin "bijou_01.bmp", 255;
		end;
	}
	mes "[ビジョウ]";
	mes "ふふふ……";
	mes "十分に楽しんで貰えたかな？";
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		close2;
		cutin "bijou_01.bmp", 255;
		end;
	}
	unittalk "ビジョウ : ふふふ……十分に楽しんで貰えたかな？";
	next;
	mes "[ビジョウ]";
	mes "それじゃ、";
	mes "そろそろ終わりにしようか。";
	unittalk "ビジョウ : それじゃ、そろそろ終わりにしようか。";
	close2;
	cutin "bijou_01.bmp", 255;
	hideonnpc getmdnpcname("ビジョウ#ex");
	hideonnpc getmdnpcname("#mir_bgm01");
	hideoffnpc getmdnpcname("#mir_bgm02");
	areawarp getmdmapname("1@mir.gat"),0,0,200,200,getmdmapname("1@mir.gat"),100+rand(3),75+rand(3);
	donpcevent getmdnpcname("#ビジョウ管理2")+ "::OnStart";
	end;
}

1@mir.gat,101,79,3	script	ビジョウ#04	10143,{
	cutin "bijou_03.bmp", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ビジョウ]";
		mes "バ、バカなっ！";
		mes "私がこんなやつに……！";
		close2;
		cutin "bijou_03.bmp", 255;
		end;
	}
	mes "[ビジョウ]";
	mes "ぐ……！";
	unittalk "ビジョウ : ぐ……！";
	next;
	mes "[ビジョウ]";
	mes "バ、バカなっ！";
	mes "私がこんなやつに……！";
	unittalk "ビジョウ : バ、バカなっ！　私がこんなやつに……！";
	hideoffnpc getmdnpcname("サラ#04");
	next;
	cutin "sarah_hero3.bmp", 2;
	mes "[サラ]";
	mes "こんなところで";
	mes "何をしているんだ？";
	mes "ビジョウ？";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : こんなところで何をしているんだ？　ビジョウ？";
	next;
	cutin "bijou_02.bmp", 2;
	mes "[ビジョウ]";
	mes "サ…ラ…様!?";
	unittalk "ビジョウ : サ…ラ…様!?";
	next;
	cutin "sarah_hero3.bmp", 2;
	mes "[サラ]";
	mes "何故お前はこんなところで";
	mes "油を売っている？";
	mes "ユミルの心臓はどうした？";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : 何故お前はこんなところで油を売っている？　ユミルの心臓はどうした？";
	next;
	cutin "bijou_02.bmp", 2;
	mes "[ビジョウ]";
	mes "そ……それが……。";
	unittalk "ビジョウ : そ……それが……。";
	next;
	mes "[ビジョウ]";
	mes "こ……ここはすぐに片付きます。";
	mes "わざわざサラ様がいらっしゃる";
	mes "必要など……。";
	unittalk "ビジョウ : こ……ここはすぐに片付きます。わざわざサラ様がいらっしゃる必要など……。";
	next;
	misceffect 565;
	if(!sleep2(1000)) end;
	cutin "bijou_03.bmp", 2;
	mes "[ビジョウ]";
	mes "サ……サラ様？";
	mes "……どうして!?";
	unittalk "ビジョウ : サ……サラ様？　……どうして!?";
	next;
	cutin "bijou_death.bmp", 4;
	mes "[サラ]";
	mes "安心しな。";
	mes "ヒメルメズには私から";
	mes "よく言っておくよ。";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : 安心しな。ヒメルメズには私からよく言っておくよ。";
	next;
	mes "[ビジョウ]";
	mes "く……";
	mes "ううっ!!";
	mes "そ……そんな……!!";
	unittalk "ビジョウ : く……ううっ!!　そ……そんな……!!";
	next;
	misceffect 567;
	if(!sleep2(1000)) end;
	hideonnpc;
	hideonnpc getmdnpcname("結界#00");
	hideonnpc getmdnpcname("結界#01");
	hideonnpc getmdnpcname("結界#02");
	hideonnpc getmdnpcname("結界#03");
	hideonnpc getmdnpcname("結界#04");
	hideonnpc getmdnpcname("結界#05");
	hideonnpc getmdnpcname("結界#06");
	hideonnpc getmdnpcname("結界#07");
	hideonnpc getmdnpcname("結界#08");
	hideonnpc getmdnpcname("結界#09");
	hideonnpc getmdnpcname("結界#10");
	set getvariableofnpc('cell,getmdnpcname("Mir_Contorl")), 0;
	areasetcell getmdmapname("1@mir.gat"),88,52,115,53,0;
	areasetcell getmdmapname("1@mir.gat"),78,83,125,84,0;
	cutin "sarah_hero3.bmp", 2;
	mes "[サラ]";
	mes "……お前の魂はもう自由だ。";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : ……お前の魂はもう自由だ。";
	next;
	mes "[サラ]";
	mes "……。";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : ……。";
	next;
	mes "[サラ]";
	mes "悪いがユミルの心臓は";
	mes "貰っていくぞ。";
	mes "邪魔をしなければ見逃してやる。";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : 悪いがユミルの心臓は貰っていくぞ。邪魔をしなければ見逃してやる。";
	next;
	mes "[サラ]";
	mes "はあああああっ！";
	unittalk getnpcid(0,getmdnpcname("サラ#04")),"サラ : はあああああっ！";
	next;
	misceffect 90;
	if(!sleep2(2000)) end;
	cutin "sarah_hero3.bmp", 255;
	hideonnpc getmdnpcname("サラ#04");
	mes "‐サラは天井を破壊して";
	mes "　ユミルの心臓を";
	mes "　持ち去ってしまった‐";
	unittalk getcharid(3),""+strcharinfo(0)+" : ‐サラは天井を破壊してユミルの心臓を持ち去ってしまった‐";
	next;
	misceffect 92;
	if(!sleep2(1000)) end;
	misceffect 92,getmdnpcname("サラ#04");
	mes "‐このままここに居ては危険だ。";
	mes "　結界が解けたこの部屋から";
	mes "　早く脱出しよう‐";
	unittalk getcharid(3),""+strcharinfo(0)+" : ‐このままここに居ては危険だ。結界が解けたこの部屋から早く脱出しよう‐";
	close;
}
1@mir.gat,101,81,3	script	サラ#04		10066,{}

1@mir.gat,101,81,0	script	#mir_bgm01	139,16,16,{
OnTouch:
	musiceffect "108";
	end;
}
1@mir.gat,101,81,0	script	#mir_bgm02	139,16,16,{
OnTouch:
	musiceffect "166";
	end;
}

1@mir.gat,101,88,3	script	ビジョウ#00	10143,{}

1@mir.gat,101,8,0	warp	#mir_exit_00	2,2,prt_lib_q.gat,88,83

1@mir.gat,78,83,3	script	結界#00	1914,{}
1@mir.gat,85,83,3	script	結界#01	1914,{}
1@mir.gat,93,83,3	script	結界#02	1914,{}
1@mir.gat,101,83,3	script	結界#03	1914,{}
1@mir.gat,110,83,3	script	結界#04	1914,{}
1@mir.gat,118,83,3	script	結界#05	1914,{}
1@mir.gat,96,53,3	script	結界#06	1914,{}
1@mir.gat,107,53,3	script	結界#07	1914,{}
1@mir.gat,125,83,3	script	結界#08	1914,{}
1@mir.gat,88,53,3	script	結界#09	1914,{}
1@mir.gat,115,53,3	script	結界#10	1914,{}