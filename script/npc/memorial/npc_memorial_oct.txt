//= Auriga Script ==============================================================
// Ragnarok Online Octpus Cave Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
mal_dun01.gat,151,235,5	script	ヒトデ	551,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ヒトデ]";
		mes "この先は立ち入り禁止だ。";
		mes "どうしても通りたいというのか？";
		mes "ならば、パーティーリーダーを";
		mes "連れて来るのだ！";
		close;
	}
	mes "[ヒトデ]";
	mes "私は忌々しい洞窟に続く道を";
	mes "監視しているヒトデだ。";
	mes "この先は立ち入り禁止だぞ！";
	while(1) {
		next;
		switch(select("話を聞く","洞窟に入りたい","引き返す")) {
		case 1:
			mes "[ヒトデ]";
			mes "なんで立ち入り禁止かって？";
			mes "それはな、私たちヒトデのアイドル";
			mes "ヒトデお嬢さんを拉致しようとした";
			mes "不届き者が洞窟に潜んでいるからだ！";
			next;
			mes "[ヒトデ]";
			mes "かわいそうに……";
			mes "ヒトデお嬢さんは";
			mes "ひどくおびえている……。";
			mes "無理もない。";
			mes "タコ足にグルグル巻きにされるなんて";
			mes "恐怖以外のなにものでもない！";
			next;
			mes "["+ strcharinfo(0) +"]";
			mes "ヒトデお嬢さんは大丈夫ですか？";
			next;
			mes "[ヒトデ]";
			mes "うむ、最近は落ち着いてきたが";
			mes "未だに他の種族と会うことを";
			mes "怖がっているようだ。";
			next;
			mes "[ヒトデ]";
			mes "だから、キミたち人間にも";
			mes "会わせるわけにはいかないのだ！";
			next;
			mes "[ヒトデ]";
			mes "ええい、憎い！";
			mes "憎いぞタコ!!";
			mes "ぶつぶつ独り言を喋りながら";
			mes "ヒトデお嬢さんに手を出しやがって！";
			mes "全くうるさいヤツだ。";
			next;
			mes "[ヒトデ]";
			mes "私たちヒトデは、ヤツを懲らしめて";
			mes "もう二度と、ヒトデお嬢さんに";
			mes "手を出さないと誓わせるまで";
			mes "この洞窟から逃がしはしないのだ！";
			next;
			mes "[ヒトデ]";
			mes "……もし、";
			mes "もしキミがタコのヤツを";
			mes "懲らしめてくれるというのなら";
			mes "洞窟に入ってもいいぞ。";
			next;
			mes "[ヒトデ]";
			mes "ただし、一人ではダメだ。";
			mes "必ず複数で";
			mes "パーティーを組んでくるんだ。";
			mes "一人では危険だからな。";
			next;
			mes "[ヒトデ]";
			mes "ちなみに私が洞窟の入り口を開けるには";
			mes "色々と準備が必要だ。";
			mes "^0000ffその為、入り口を開ける事は";
			mes "約１週間に一度しかできない。^000000";
			mes "ただし、制限中も仲間が開けた洞窟に";
			mes "入場する事は可能だぞ。";
			break;
		case 2:
			if(checkquest(71835)) {
				if(!(checkquest(71835)&0x2)) {
					mes "[ヒトデ]";
					mes "ここを通りたいのか？";
					mes "しかし、今は^0000ff暴窟王の洞窟^000000の入口を";
					mes "開けることができない。";
					mes "少し待ってくれ。";
					mes "もし、君か仲間が入口を開けているなら";
					mes "奥にある通路から通れるぞ。";
					close;
				}
				delquest 71835;
			}
			mes "[ヒトデ]";
			mes "そうか。洞窟に入りたいのか。";
			mes "私が洞窟の入り口を開けるには";
			mes "色々と準備が必要だ。";
			mes "^0000ffその為、入り口を開ける事は";
			mes "約１週間に一度しかできない。^000000";
			next;
			mes "[ヒトデ]";
			mes "一度開けると利用の有無や";
			mes "成功の可否に関わらず、制限されるから";
			mes "気を付けてくれ。";
			mes "では、入り口を開けても良いか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[ヒトデ]";
				mes "そうか。では都合の良い時に";
				mes "また、話しかけてくれ。";
				close;
			}
			mdcreate "Octopus Cave";
			setquest 71835;
			mes "[ヒトデ]";
			mes "パーティー名は";
			mes strcharinfo(1)+ "で";
			mes "パーティーリーダーは";
			mes strcharinfo(0);
			mes "だな。";
			next;
			mes "[ヒトデ]";
			mes "よし、^0000ff暴窟王の洞窟^000000の入口を開けるぞ。";
			mes "この奥にある通路から";
			mes "洞窟に入って";
			mes "中に潜むタコのヤツを";
			mes "懲らしめてくれ！";
			close;
		case 3:
			mes "[ヒトデ]";
			mes "悪く思わないでくれ。";
			mes "この先は危険なのだ。";
			close;
		}
	}
	end;
}

//============================================================
// ダンジョン入場NPC
//------------------------------------------------------------
mal_dun01.gat,153,237,5	script	不思議な通路	844,{
	mes "‐木の板でふさがれた";
	mes "　洞窟につながる道がある。";
	mes "　板の隙間をくぐれば";
	mes "　先に進めそうだ‐";
	next;
	if(select("先に進む","引き返す") == 2) {
		mes "‐あなたは、封鎖された通路に";
		mes "　背を向けた‐";
		close;
	}
	switch(mdenter("Octopus Cave")) {
	case 0:	// エラーなし
		announce strcharinfo(1)+ " パーティーの" +strcharinfo(0)+ "が暴窟王の洞窟に入場した！",0x9,0x00ff99;
		end;
	default:	// その他エラー
		mes "[ヒトデ]";
		mes "焦るんじゃない。";
		mes "パーティリーダーが";
		mes "まだ手続きを終えていないか";
		mes "入場の準備中だ。";
		mes "もう少しまつんだ。";
		close;
	}
}

//============================================================
// 暴窟王の洞窟
//------------------------------------------------------------
1@cash.gat,199,99,0	script	oct_enter	139,4,4,{
	hideonnpc;
	donpcevent getmdnpcname("oct_foot_4")+"::OnStart";
	donpcevent getmdnpcname("oct_mob_con")+"::OnStart";
	initnpctimer;
	end;
OnTimer1000:
	announce "頭領タコ : 誰だ！　恐れを知らず俺の縄張りに入って来るとは！",0x9,0x00ff99;
	end;
OnTimer4000:
	announce "頭領タコ : だが俺がいる洞窟の入り口は閉じてあるから、何をやっても無駄だ。",0x9,0x00ff99;
	end;
OnTimer7000:
	announce "頭領タコ : 俺の子分たちのおもちゃになりな、ワハハハハ!!",0x9,0x00ff99;
	stopnpctimer;
	end;
}

1@cash.gat,3,3,0		script	oct_foot_4	139,{
OnStart:
	hideonnpc getmdnpcname("oct_foot_exit1");
	hideonnpc getmdnpcname("oct_foot_exit2");
	hideonnpc getmdnpcname("oct_foot_exit3");
	hideonnpc getmdnpcname("oct_foot_exit4");
	hideonnpc getmdnpcname("oct_boss_warp");
	hideonnpc getmdnpcname("oct_exit2");
	donpcevent getmdnpcname("oct_foot1")+"::OnStart";
	donpcevent getmdnpcname("oct_foot2")+"::OnStart";
	donpcevent getmdnpcname("oct_foot3")+"::OnStart";
	donpcevent getmdnpcname("oct_foot4")+"::OnStart";

	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_foot_4")+"::OnKilled";
	monster '@mdmap$,20,114,"頭領タコの足",2193,1,'@event$;
	monster '@mdmap$,88,190,"頭領タコの足",2193,1,'@event$;
	monster '@mdmap$,307,215,"頭領タコの足",2193,1,'@event$;
	monster '@mdmap$,372,131,"頭領タコの足",2193,1,'@event$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@cash.gat"),getmdnpcname("oct_foot_4")+"::OnKilled");
	if('count > 0) {
		announce "頭領タコ : 痛たたたたた!!　おのれ～！　許さんぞ!!　俺の残りの足で必ずしとめるぞ！",0x9,0x00ff99;
		end;
	}
	initnpctimer;
	donpcevent getmdnpcname("oct_boss_con")+"::OnStart";
	announce "頭領タコ : おのれい、俺の足によくも!!　もう許さぬぞ!!",0x9,0x00ff99;
	hideoffnpc getmdnpcname("oct_boss_warp");
	mapwarp getmdmapname("1@cash.gat"),getmdmapname("1@cash.gat"),197,107;
	end;
OnTimer210000:
	set '@mdmap$,getmdmapname("1@cash.gat");
	if(getmapmobs('@mdmap$,getmdnpcname("oct_foot_4")+"::OnKilled1") <= 0)
		monster '@mdmap$,20,114,"頭領タコの足",2193,1,getmdnpcname("oct_foot_4")+"::OnKilled1";
	if(getmapmobs('@mdmap$,getmdnpcname("oct_foot_4")+"::OnKilled2") <= 0)
		monster '@mdmap$,88,190,"頭領タコの足",2193,1,getmdnpcname("oct_foot_4")+"::OnKilled2";
	if(getmapmobs('@mdmap$,getmdnpcname("oct_foot_4")+"::OnKilled3") <= 0)
		monster '@mdmap$,307,215,"頭領タコの足",2193,1,getmdnpcname("oct_foot_4")+"::OnKilled3";
	if(getmapmobs('@mdmap$,getmdnpcname("oct_foot_4")+"::OnKilled4") <= 0)
		monster '@mdmap$,372,131,"頭領タコの足",2193,1,getmdnpcname("oct_foot_4")+"::OnKilled4";
	initnpctimer;
	end;
OnKilled1:
OnKilled2:
OnKilled3:
OnKilled4:
	end;
}

1@cash.gat,20,114,0		script	oct_foot1	139,6,6,{
OnStart:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled1";
	areamonster '@mdmap$,31,93,41,103,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,38,89,42,93,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,36,74,42,80,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,38,57,42,61,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,47,35,59,47,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,65,29,75,39,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,82,25,86,29,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,106,27,110,31,"子分タコ",2192,1,'@event$;
	areamonster '@mdmap$,122,27,126,31,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,131,28,141,38,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,139,36,149,46,"子分タコ",2192,2,'@event$;
	end;
OnTouch:
	hideonnpc getmdnpcname("oct_foot1");
	announce "頭領タコ : 子分たちよ、やってしまえ!!",0x9,"0xffff00";
	initnpctimer;
	end;
OnTimer5000:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled1";
	announce "頭領タコ : あの生意気な奴らを懲らしめてやれ。",0x9,"0xffff00";
	areamonster '@mdmap$,15,109,25,119,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,15,109,25,119,"子分タコ",2192,3,'@event$;
	end;
OnTimer30000:
	stopnpctimer;
	//hideoffnpc getmdnpcname("oct_foot_exit1");
	end;
}

1@cash.gat,16,117,0		warp	oct_foot_exit1	2,2,1@cash.gat,198,99

1@cash.gat,88,190,0	script	oct_foot2	139,6,6,{
OnStart:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled2";
	areamonster '@mdmap$,136,110,146,120,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,133,102,139,108,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,120,90,130,100,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,112,89,116,93,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,102,88,106,92,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,88,89,92,93,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,72,102,78,108,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,72,118,78,124,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,81,129,89,137,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,90,140,96,146,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,96,157,102,163,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,91,177,101,187,"子分タコ",2192,5,'@event$;
	end;
OnTouch:
	hideonnpc getmdnpcname("oct_foot2");
	announce "頭領タコ : 子分たちよ、やってしまえ!!",0x9,"0xffff00";
	initnpctimer;
	end;
OnTimer5000:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled2";
	announce "頭領タコ : あの生意気な奴らを懲らしめてやれ。",0x9,"0xffff00";
	areamonster '@mdmap$,83,185,93,195,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,83,185,93,195,"子分タコ",2192,3,'@event$;
	end;
OnTimer30000:
	stopnpctimer;
	//hideoffnpc getmdnpcname("oct_foot_exit2");
	end;
}

1@cash.gat,77,193,0		warp	oct_foot_exit2	2,2,1@cash.gat,198,99

1@cash.gat,307,215,0	script	oct_foot3	139,6,6,{
OnStart:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled3";
	areamonster '@mdmap$,297,207,305,215,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,289,200,299,210,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,289,184,295,190,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,290,164,296,170,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,291,149,297,155,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,297,135,305,143,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,298,121,306,129,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,298,102,306,110,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,278,100,282,104,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,259,102,261,104,"子分タコ",2192,1,'@event$;
	end;
OnTouch:
	hideonnpc getmdnpcname("oct_foot3");
	announce "頭領タコ : 子分たちよ、やってしまえ!!",0x9,"0xffff00";
	initnpctimer;
	end;
OnTimer5000:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled3";
	announce "頭領タコ : あの生意気な奴らを懲らしめてやれ。",0x9,"0xffff00";
	areamonster '@mdmap$,302,210,312,220,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,302,210,312,220,"子分タコ",2192,3,'@event$;
	end;
OnTimer30000:
	stopnpctimer;
	//hideoffnpc getmdnpcname("oct_foot_exit3");
	end;
}

1@cash.gat,312,214,0	warp	oct_foot_exit3	2,2,1@cash.gat,198,99

1@cash.gat,372,131,0	script	oct_foot4	139,6,6,{
OnStart:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled4";
	areamonster '@mdmap$,361,121,369,129,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,361,105,371,115,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,361,91,369,99,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,362,70,368,76,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,362,59,368,62,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,353,42,361,50,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,344,34,352,42,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,316,25,328,37,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,304,26,308,30,"子分タコ",2192,2,'@event$;
	areamonster '@mdmap$,274,27,282,35,"子分タコ",2192,5,'@event$;
	areamonster '@mdmap$,255,34,265,44,"子分タコ",2192,2,'@event$;
	end;
OnTouch:
	hideonnpc getmdnpcname("oct_foot4");
	announce "頭領タコ : 子分たちよ、やってしまえ!!",0x9,"0xffff00";
	initnpctimer;
	end;
OnTimer5000:
	set '@mdmap$,getmdmapname("1@cash.gat");
	set '@event$,getmdnpcname("oct_mob_con")+"::OnKilled4";
	announce "頭領タコ : あの生意気な奴らを懲らしめてやれ。",0x9,"0xffff00";
	areamonster '@mdmap$,367,126,377,136,"子分タコ",2192,3,'@event$;
	areamonster '@mdmap$,367,126,377,136,"子分タコ",2192,3,'@event$;
	end;
OnTimer30000:
	stopnpctimer;
	//hideoffnpc getmdnpcname("oct_foot_exit4");
	end;
}

1@cash.gat,370,139,0	warp	oct_foot_exit4	2,2,1@cash.gat,198,99

1@cash.gat,15,15,0	script	oct_mob_con	139,{
OnStart:
	set '@mdmap$,getmdmapname("1@cash.gat");

	monster '@mdmap$,32,94,"ヒドラ",1068,1;
	monster '@mdmap$,41,101,"ヒドラ",1068,1;
	monster '@mdmap$,35,78,"ヒドラ",1068,1;
	monster '@mdmap$,35,62,"ヒドラ",1068,1;
	monster '@mdmap$,49,54,"ヒドラ",1068,1;
	monster '@mdmap$,70,28,"ヒドラ",1068,1;
	monster '@mdmap$,83,22,"ヒドラ",1068,1;
	monster '@mdmap$,99,23,"ヒドラ",1068,1;
	monster '@mdmap$,115,23,"ヒドラ",1068,1;
	monster '@mdmap$,132,25,"ヒドラ",1068,1;

	monster '@mdmap$,100,185,"ヒドラ",1068,1;
	monster '@mdmap$,92,178,"ヒドラ",1068,1;
	monster '@mdmap$,92,162,"ヒドラ",1068,1;
	monster '@mdmap$,70,121,"ヒドラ",1068,1;
	monster '@mdmap$,70,105,"ヒドラ",1068,1;
	monster '@mdmap$,105,85,"ヒドラ",1068,1;
	monster '@mdmap$,121,84,"ヒドラ",1068,1;

	monster '@mdmap$,292,209,"ヒドラ",1068,1;
	monster '@mdmap$,303,206,"ヒドラ",1068,1;
	monster '@mdmap$,290,163,"ヒドラ",1068,1;
	monster '@mdmap$,299,150,"ヒドラ",1068,1;
	monster '@mdmap$,308,141,"ヒドラ",1068,1;
	monster '@mdmap$,308,125,"ヒドラ",1068,1;
	monster '@mdmap$,295,97,"ヒドラ",1068,1;
	monster '@mdmap$,279,97,"ヒドラ",1068,1;

	monster '@mdmap$,370,111,"ヒドラ",1068,1;
	monster '@mdmap$,370,110,"ヒドラ",1068,1;
	monster '@mdmap$,371,96,"ヒドラ",1068,1;
	monster '@mdmap$,371,80,"ヒドラ",1068,1;
	monster '@mdmap$,367,55,"ヒドラ",1068,1;
	monster '@mdmap$,343,29,"ヒドラ",1068,1;
	monster '@mdmap$,327,24,"ヒドラ",1068,1;
	monster '@mdmap$,311,22,"ヒドラ",1068,1;
	monster '@mdmap$,295,22,"ヒドラ",1068,1;
	monster '@mdmap$,279,22,"ヒドラ",1068,1;

	areamonster '@mdmap$,20,57,60,97,"スタポ",1784,1;
	areamonster '@mdmap$,92,9,132,49,"スタポ",1784,1;
	areamonster '@mdmap$,79,128,119,168,"スタポ",1784,1;
	areamonster '@mdmap$,102,73,142,113,"スタポ",1784,1;
	areamonster '@mdmap$,273,158,313,198,"スタポ",1784,1;
	areamonster '@mdmap$,282,87,322,127,"スタポ",1784,1;
	areamonster '@mdmap$,345,54,385,94,"スタポ",1784,1;
	areamonster '@mdmap$,307,7,347,47,"スタポ",1784,1;
	end;
OnKilled1:
	set 'count,getmapmobs(getmdmapname("1@cash.gat"),getmdnpcname("oct_mob_con")+ "::OnKilled1");
	if('count <= 0) {
		announce "子分タコ : と、頭領すみません！やられました！",0x9,0x00ff99;
		stopnpctimer;
		hideoffnpc getmdnpcname("oct_foot_exit1");
		hideonnpc getmdnpcname("oct_foot1");
	}
	end;
OnKilled2:
	set 'count,getmapmobs(getmdmapname("1@cash.gat"),getmdnpcname("oct_mob_con")+ "::OnKilled2");
	if('count <= 0) {
		announce "子分タコ : と、頭領すみません！やられました！",0x9,0x00ff99;
		stopnpctimer;
		hideoffnpc getmdnpcname("oct_foot_exit2");
		hideonnpc getmdnpcname("oct_foot2");
	}
	end;
OnKilled3:
	set 'count,getmapmobs(getmdmapname("1@cash.gat"),getmdnpcname("oct_mob_con")+ "::OnKilled3");
	if('count <= 0) {
		announce "子分タコ : と、頭領すみません！やられました！",0x9,0x00ff99;
		stopnpctimer;
		hideoffnpc getmdnpcname("oct_foot_exit3");
		hideonnpc getmdnpcname("oct_foot3");
	}
	end;
OnKilled4:
	set 'count,getmapmobs(getmdmapname("1@cash.gat"),getmdnpcname("oct_mob_con")+ "::OnKilled4");
	if('count <= 0) {
		announce "子分タコ : と、頭領すみません！やられました！",0x9,0x00ff99;
		stopnpctimer;
		hideoffnpc getmdnpcname("oct_foot_exit4");
		hideonnpc getmdnpcname("oct_foot4");
	}
	end;
}

1@cash.gat,45,53,0	script	oct_backattack1	139,3,3,{
	set '@mdmap$,getmdmapname("1@cash.gat");
	monster '@mdmap$,39,59,"ヒドラ",1068,1;
	monster '@mdmap$,40,59,"ヒドラ",1068,1;
	monster '@mdmap$,41,59,"ヒドラ",1068,1;
	monster '@mdmap$,47,50,"ヒドラ",1068,1;
	monster '@mdmap$,48,50,"ヒドラ",1068,1;
	monster '@mdmap$,49,50,"ヒドラ",1068,1;
	monster '@mdmap$,41,53,"子分タコ",2192,1;
	announce "子分タコ : 突破させてなるものか！",0x9,0x00ff99;
	hideonnpc;
	end;
}

1@cash.gat,78,99,0	script	oct_backattack2	139,3,3,{
	initnpctimer;
	monster getmdmapname("1@cash.gat"),71,105,"子分タコ",2192,1;
	announce "子分タコ : 隙あり！　隙あり！",0x9,0x00ff99;
	hideonnpc;
	end;
OnTimer2000:
	monster getmdmapname("1@cash.gat"),71,105,"子分タコ",2192,1;
	announce "子分タコ : 行け！　体勢を整えられる前に叩け！",0x9,0x00ff99;
	end;
OnTimer4000:
	monster getmdmapname("1@cash.gat"),71,105,"子分タコ",2192,1;
	announce "子分タコ : 時間がない。急いでいくぞ！",0x9,0x00ff99;
	end;
OnTimer6000:
	monster getmdmapname("1@cash.gat"),71,105,"子分タコ",2192,3;
	announce "子分タコ : 全員で攻撃するぞ！",0x9,0x00ff99;
	end;
OnTimer8000:
	monster getmdmapname("1@cash.gat"),71,105,"子分タコ",2192,1;
	announce "子分タコ : いけー！遅れるな！",0x9,0x00ff99;
	stopnpctimer;
	end;
}

1@cash.gat,299,144,0	script	oct_backattack3	139,3,3,{
	set '@mdmap$,getmdmapname("1@cash.gat");
	monster '@mdmap$,293,153,"子分タコ",2192,1;
	monster '@mdmap$,294,152,"子分タコ",2192,1;
	monster '@mdmap$,292,153,"子分タコ",2192,1;
	monster '@mdmap$,293,151,"子分タコ",2192,1;
	monster '@mdmap$,293,152,"子分タコ?",2175,1;
	announce "子分タコ : 伏兵だ、驚いただろう！",0x9,0x00ff99;
	hideonnpc;
	end;
}

1@cash.gat,336,36,0	script	oct_backattack4	139,3,3,{
	set '@mdmap$,getmdmapname("1@cash.gat");
	monster '@mdmap$,332,37,"子分タコ",2192,1;
	monster '@mdmap$,332,36,"子分タコ",2192,1;
	monster '@mdmap$,332,35,"子分タコ",2192,1;
	monster '@mdmap$,332,34,"子分タコ",2192,1;
	monster '@mdmap$,341,37,"子分タコ",2192,1;
	monster '@mdmap$,341,36,"子分タコ",2192,1;
	monster '@mdmap$,341,35,"子分タコ",2192,1;
	monster '@mdmap$,341,34,"子分タコ",2192,1;

	monster '@mdmap$,260,40,"用心棒イカ",2175,1;
	monster '@mdmap$,260,41,"用心棒イカ",2175,1;
	monster '@mdmap$,260,39,"用心棒イカ",2175,1;
	monster '@mdmap$,259,40,"用心棒イカ",2175,1;
	monster '@mdmap$,261,40,"用心棒イカ",2175,1;
	announce "子分タコ : 頼むぞ用心棒！　一斉にいくぞー！",0x9,0x00ff99;
	initnpctimer;
	hideonnpc;
	end;
OnTimer5000:
	announce "用心棒イカ : ここは通さん！",0x9,0x00ff99;
	stopnpctimer;
	end;
}

1@cash.gat,2,2,0	script	oct_boss_con	139,{
OnStart:
	donpcevent getmdnpcname("oct_boss_foot")+"::OnStart";
	monster getmdmapname("1@cash.gat"),196,188,"頭領タコ",2194,1,getmdnpcname("oct_boss_con")+ "::OnKilled";
	initnpctimer;
	end;
OnTimer7000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : 俺に挑んだ事を後悔させてやろう！",0x9,0xffff00; break;
	case 1: announce "頭領タコ : 俺の足は何度でも蘇るぞ!!",0x9,0x00ff99; break;
	case 2: announce "頭領タコ : うおおおおお、頭領タコの本気見せてやる!!",0x9,0xffff00; break;
	}
	end;
OnTimer14000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : お前らもヒトデお嬢さんが好きなんだろう？",0x9,0xffff00; break;
	case 1: announce "頭領タコ : マラン島に住み着いた猫の話でもしよ……おい!今殴るなよ！",0x9,0xffff00; break;
	case 2: announce "頭領タコ : お前を諦めさせるには、痛い目を見てもらうしかないようだな。",0x9,0xffff00; break;
	}
	end;
OnTimer21000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : 顔を真っ赤にしてるんじゃない。元から赤いんだ！",0x9,0xffff00; break;
	case 1: announce "頭領タコ : ヒトデお嬢さんのプロポーションは美しすぎる。まさにスターだよ。",0x9,0xffff00; break;
	case 2: announce "頭領タコ : たとえここで倒れたとしても、必ずまた戻ってくるぞ！",0x9,0xffff00; break;
	}
	end;
OnTimer28000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : お前にも愛する人がいるだろう？",0x9,0xffff00; break;
	case 1: announce "頭領タコ : 俺が無礼なタコだと？　タコが恋しちゃいけないっていうのか。",0x9,0xffff00; break;
	case 2: announce "頭領タコ : ぐぬぬ……やめろお前ら！ やわらかいところを殴るのは汚いぞ！",0x9,0xffff00; break;
	}
	end;
OnTimer35000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : ファイナルオクトパスイリュージョンフェイント!! 効果は特に無い。",0x9,0xffff00; break;
	case 1: announce "頭領タコ : うう……今日は調子が悪い。今日だけ調子が悪い……いつもこんな事ないのに。",0x9,0xffff00; break;
	case 2: announce "頭領タコ : ヒトデお嬢さん、見ててください。俺こんなに頑張ってます!!",0x9,0xffff00; break;
	}
	end;
OnTimer42000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : タコの足が8本しかないと思うなよ。俺の足は無限だ！",0x9,0xffff00; break;
	case 1: announce "頭領タコ : 落ち着け、落ち着け、まず冷静に話し合おう。",0x9,0xffff00; break;
	case 2: announce "頭領タコ : 俺の足を倒したくらいで調子に乗るなよ！",0x9,0xffff00; break;
	}
	end;
OnTimer49000:
	switch(rand(3)) {
	case 0: announce "頭領タコ : くそっ力が出ない。だれか、墨汁をくれ！",0x9,0xffff00; break;
	case 1: announce "頭領タコ : ヒトデお嬢さんを好きなってなにが悪いんだ！",0x9,0xffff00; break;
	case 2: announce "頭領タコ : ヒトデお嬢さんは俺の物だ！",0x9,0xffff00; break;
	}
	initnpctimer;
	end;
OnKilled:
	announce "頭領タコ : ああっだめだ…！　今日はここまでにしてやる。次は覚えておけ!!",0x9,0x00ff99;
	hideoffnpc getmdnpcname("oct_exit2");
	stopnpctimer getmdnpcname("oct_boss_foot");
	stopnpctimer;
	hideonnpc;
	end;
}

1@cash.gat,4,4,0	script	oct_boss_foot	139,{
OnStart:
	initnpctimer;
	end;
OnTimer5000:
	announce "頭領タコ : 俺がいる部屋への入り口をあけてやったわ。",0x9,0x00ff99;
	end;
OnTimer10000:
	announce "頭領タコ : よし。お前たちも出て来て戦え！",0x9,0xffff00;
	areamonster getmdmapname("1@cash.gat"),184,173,214,203,"子分タコ",2192,5;
	stopnpctimer;
	end;
}

1@cash.gat,198,82,0	script	oct_exit	45,2,2,{
	mes "－暴窟王の洞窟の外に出ますか？－";
	next;
	if(select("外に出ない","外に出る") == 1) {
		close;
	}
	mes "‐外に出ました‐";
	close2;
	warp "mal_dun01.gat",153,233;
	end;
}

1@cash.gat,190,208,0	duplicate(oct_exit)	oct_exit2	45,1,1

1@cash.gat,193,84,0		warp	oct_door1	2,2,1@cash.gat,151,48
1@cash.gat,154,53,0		warp	oct_door2	2,2,1@cash.gat,197,87
1@cash.gat,187,99,0		warp	oct_door3	2,2,1@cash.gat,148,128
1@cash.gat,153,133,0	warp	oct_door4	2,2,1@cash.gat,197,99
1@cash.gat,209,100,0	warp	oct_door5	2,2,1@cash.gat,250,111
1@cash.gat,244,118,0	warp	oct_door6	2,2,1@cash.gat,199,100
1@cash.gat,209,83,0		warp	oct_door7	2,2,1@cash.gat,252,46
1@cash.gat,246,53,0		warp	oct_door8	2,2,1@cash.gat,203,83
1@cash.gat,198,116,0	warp	oct_boss_warp	2,2,1@cash.gat,210,172
1@cash.gat,206,168,0	warp	oct_boss_exit	2,2,1@cash.gat,197,107
