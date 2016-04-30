//= Auriga Script ==============================================================
// Ragnarok Online Buwaya Cave Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
ma_fild02.gat,312,317,5	script	警備兵	570,{
	if(MALAYA_4QUE < 15) {
		mes "[警備兵]";
		mes "この洞窟の奥に何かが潜んでいる";
		mes "ようなのですが、現在は調査中です。";
		close;
	}
	if(BaseLevel < 130) {
		mes "[警備兵]";
		mes "この洞窟の奥には";
		mes "ブワヤの巣があります。";
		mes "あなたが挑むにはまだ危険です。";
		next;
		mes "‐^ff0000Baseレベルを130以上^000000にしてから";
		mes "　また来てみよう‐";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[警備兵]";
		mes "ブワヤ相手に一人では危険です。";
		mes "パーティーを組んでから";
		mes "また来てください。";
		close;
	}
	mes "[警備兵]";
	mes "ここはブワヤが潜む洞窟です。";
	mes "危険なので用がなければ";
	mes "近寄らないでください。";
	while(1) {
		next;
		switch(select("ブワヤについて聞きたい","ブワヤを倒しに来ました","ブワヤの巣に入る","引き返す")) {
		case 1:
			mes "[警備兵]";
			mes "最近町の人達が失踪した";
			mes "事件がありました。";
			mes "私たちはその痕跡を追跡した結果";
			mes "この洞窟の中に住んでいる";
			mes "巨大なモンスターブワヤの";
			mes "仕業だという事がわかりました。";
			next;
			mes "[警備兵]";
			mes "これまでブワヤを退治するために";
			mes "多くの兵士や傭兵たちが";
			mes "派遣されましたが、";
			mes "未だに退治できていません。";
			next;
			mes "[警備兵]";
			mes "ブワヤは今でも町の人たちを";
			mes "さらっていきます。";
			mes "誰かブワヤを退治してくれる";
			mes "人はいないだろうか……。";
			break;
		case 2:
			if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
				mes "[警備兵]";
				mes "パーティーの代表者とお話しします。";
				mes "代表者を呼んでください。";
				close;
			}
			if(checkquest(4229)) {
				if(!(checkquest(4229) & 0x2)) {
					mes "[警備兵]";
					mes "今はまだ準備ができていません。";
					mes "もう少し時間が経ってから";
					mes "また来てください。";
					close;
				}
				delquest 4229;
			}
			mdcreate "Buwaya Cave";
			mes "[警備兵]";
			mes "わかりました。入場を許可します。";
			mes "ブワヤの巣への通路を開けるので、";
			mes "準備ができたら私に話しかけてください。";
			close;
		case 3:
			if(checkquest(4229)) {
				if(!(checkquest(4229) & 0x2)) {
					mes "[警備兵]";
					mes "今はまだ準備ができていません。";
					mes "もう少し時間が経ってから";
					mes "また来てください。";
					close;
				}
				mes "[警備兵]";
				mes "また、ブワヤの巣に行くのですか？";
				next;
				delquest 4229;
				if(select("入場する","やめる") == 2) {
					mes "[警備兵]";
					mes "それが賢明です。";
					close;
				}
			}
			switch(mdenter("Buwaya Cave")) {
			case 0:	// エラーなし
				announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Buwaya Cave]に入場しました。",0x9,0x00ff99;
				setquest 4229;
				donpcevent getmdnpcname("BuwayaControl")+"::OnStart";
				end;
			case 1:	// パーティー未加入
				mes "[警備兵]";
				mes "入場を許可したパーティーに";
				mes "加入していません。";
				mes "ここを通すことはできません。";
				close;
			case 2:	// ダンジョン未作成
				mes "[警備兵]";
				mes "まだ通路は開いていません。";
				mes "もう少し待ってください。";
				close;
			default:	// その他エラー
				close;
			}
		case 4:
			mes "[警備兵]";
			mes "それが賢明です。";
			close;
		}
	}
}

//============================================================
// ブワヤの巣
//------------------------------------------------------------
1@ma_c.gat,0,0,0	script	BuwayaControl	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	donpcevent getmdnpcname("#buwaya_damage")+"::OnStart";
	donpcevent getmdnpcname("#buwaya_bunshin")+"::OnStart";
	donpcevent getmdnpcname("#buwaya_boss")+"::OnStart";
	donpcevent getmdnpcname("#buwaya_exit_mob")+"::OnStart";

	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("#buwaya_trap"+'@i);
	hideonnpc getmdnpcname("#buwaya_boxout");
	hideonnpc getmdnpcname("#buwaya_caveout");

	set '@map$, getmdmapname("1@ma_c.gat");
	areamonster '@map$,73,81,93,101,"水草",2331,9;
	areamonster '@map$,110,97,116,103,"水草",2331,4;
	areamonster '@map$,59,63,63,67,"水草",2331,4;
	areamonster '@map$,73,55,77,59,"水草",2331,2;
	areamonster '@map$,103,69,107,73,"水草",2331,2;
	areamonster '@map$,108,45,122,63,"水草",2331,7;
	areamonster '@map$,73,81,93,101,"ブワヤの卵",2329,5;
	areamonster '@map$,110,97,116,103,"ブワヤの卵",2329,4;
	areamonster '@map$,59,63,63,67,"ブワヤの卵",2329,2;
	areamonster '@map$,73,55,77,59,"ブワヤの卵",2329,1;
	areamonster '@map$,103,69,107,73,"ブワヤの卵",2329,1;
	areamonster '@map$,108,45,122,63,"ブワヤの卵",2329,7;
	areamonster '@map$,0,0,0,0,"水草",2331,5;
	areamonster '@map$,0,0,0,0,"働きブワヤ",2330,5;
	initnpctimer;
	end;
OnTimer30000:
	announce "ブワヤ : 箱の中で苦しみ続けるがいい！",0x9,0x00ff99;
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		misceffect 247,getmdnpcname("#buwaya_trap"+'@i);
	end;
OnTimer33000:
	hideonnpc getmdnpcname("#buwaya_boxout");
	donpcevent getmdnpcname("#buwaya_boxmob")+"::OnClose";
	end;
OnTimer34000:
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideoffnpc getmdnpcname("#buwaya_trap"+'@i);
	end;
OnTimer35000:
	initnpctimer;
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("#buwaya_trap"+'@i);
	end;
OnClose:
	stopnpctimer;
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("#buwaya_trap"+'@i);
	end;
}

1@ma_c.gat,33,112,0	script	#buwaya_damage	139,7,7,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	misceffect 53;
	end;
OnTimer2000:
	initnpctimer;
	end;
OnTouch:
	sc_start SC_Bleed,60000,0;
	sc_start SC_Poison,60000,0;
	end;
}

1@ma_c.gat,29,110,5	script	拉致された人たち#1	575,{
	mes "[拉致された人たち]";
	mes "ブワヤがいきなり暴れだしたと思ったら";
	mes "また捕まえられた人が来たんですね。";
	next;
	mes "[拉致された人たち]";
	mes "逃げようにも私達には力がありません。";
	mes "残念ですが、このまま最後の時を";
	mes "迎えるしかないようです。";
	next;
	menu "ここから出る方法は？",-;
	mes "[拉致された人たち]";
	mes "あの壁を見てください。";
	mes "他の部分と比べ少し変わっています。";
	mes "以前あそこを叩いたとき、";
	mes "ブワヤが暴れたんです。";
	mes "おそらくあそこが弱点でしょう。";
	donpcevent getmdnpcname("#buwaya_boxmob")+"::OnStart";
	next;
	mes "[拉致された人たち]";
	mes "私の力では無理でしたが、";
	mes "あなたの力ならなんとかなるかも";
	mes "しれません。";
	mes "あの壁を思いっきり";
	mes "叩いてみてください。";
	close;
}

1@ma_c.gat,36,110,5	script	拉致された人たち#2	574,{
	mes "[拉致された人たち]";
	mes "誰か非力なワシの代わりに";
	mes "ブワヤの弱点を攻撃してくれんか……。";
	next;
	switch(select("まかせてください","気にせず周りを調べる")) {
	case 1:
		mes "[拉致された人たち]";
		mes "君がやってくれるのか……。";
		mes "わかった。";
		mes "お礼に君の力を引き出してあげよう。";
		mes "頼んだぞ。";
		sc_start SC_ATKPOTION,60000,45;
		sc_start SC_MATKPOTION,60000,45;
		close;
	case 2:
		mes "[拉致された人たち]";
		mes "若者よ、";
		mes "今はみんなで協力するときだぞ。";
		next;
		mes "[拉致された人たち]";
		mes "このままではみんな揃って";
		mes "あの世行きじゃ。";
		close;
	}
}

1@ma_c.gat,3,3,0	script	#buwaya_boxmob	139,{
OnStart:
	if(getmapmobs(getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_boxmob")+"::OnKilled") < 1) {
		set '@label$, getmdnpcname("#buwaya_boxmob")+"::OnKilled";
		set '@map$, getmdmapname("1@ma_c.gat");
		monster '@map$,30,117,"箱のひび",2333,1,'@label$;
		monster '@map$,35,117,"箱のひび",2333,1,'@label$;
	}
	end;
OnClose:
	killmonster getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_boxmob")+"::OnKilled";
	end;
OnKilled:
	if(getmapmobs(getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_boxmob")+"::OnKilled") < 1) {
		hideonnpc getmdnpcname("#buwaya_damage");
		hideoffnpc getmdnpcname("#buwaya_boxout");
	}
	end;
}

1@ma_c.gat,34,118,0	script	#buwaya_boxout	45,7,7,{
OnTouch:
	set '@x,rand(1,20) + 97;
	set '@y,rand(1,20) + 74;
	warp getmdmapname("1@ma_c.gat"),'@x,'@y;
	end;
}

1@ma_c.gat,97,74,0	script	#buwaya_trap1	139,5,5,{
OnTouch:
	misceffect 191,"";
	warp getmdmapname("1@ma_c.gat"),33,112;
	end;
}
1@ma_c.gat,97,94,0	duplicate(#buwaya_trap1)	#buwaya_trap2	139,5,5
1@ma_c.gat,117,94,0	duplicate(#buwaya_trap1)	#buwaya_trap3	139,5,5
1@ma_c.gat,117,74,0	duplicate(#buwaya_trap1)	#buwaya_trap4	139,5,5
1@ma_c.gat,117,54,0	duplicate(#buwaya_trap1)	#buwaya_trap5	139,5,5
1@ma_c.gat,97,54,0	duplicate(#buwaya_trap1)	#buwaya_trap6	139,5,5
1@ma_c.gat,77,54,0	duplicate(#buwaya_trap1)	#buwaya_trap7	139,5,5
1@ma_c.gat,77,74,0	duplicate(#buwaya_trap1)	#buwaya_trap8	139,5,5
1@ma_c.gat,77,94,0	duplicate(#buwaya_trap1)	#buwaya_trap9	139,5,5

1@ma_c.gat,1,1,0	script	#buwaya_bunshin	139,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer58000:
	announce "ブワヤ : もう我慢の限界だ。私を怒らせた事を後悔させてやる。",0x9,0x00ff99;
	end;
OnTimer61000:
	announce "ブワヤ : 絶対に許さんぞ……。",0x9,0x00ff99;
	end;
OnTimer62000:
	announce "ブワヤ : これが……私の！",0x9,0x00ff99;
	end;
OnTimer63000:
	announce "ブワヤ : これが……私の……必殺の！",0x9,0x00ff99;
	end;
OnTimer64000:
	announce "ブワヤ : これが……私の……必殺の……分身攻撃！",0x9,0x00ff99;
	end;
OnTimer65000:
	set '@label$, getmdnpcname("#buwaya_bunshin")+"::OnKilled";
	set '@map$, getmdmapname("1@ma_c.gat");
	areamonster '@map$,112,89,122,99,"ブワヤ",2332,1,'@label$;
	areamonster '@map$,112,49,122,59,"ブワヤ",2332,1,'@label$;
	areamonster '@map$,72,49,82,59,"ブワヤ",2332,1,'@label$;
	areamonster '@map$,72,89,82,99,"ブワヤ",2332,1,'@label$;
	end;
OnTimer66000:
	announce "ブワヤ : どうした、怖いのか？　くくく！",0x9,0x00ff99;
	end;
OnTimer105000:
	killmonster getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_bunshin")+"::OnKilled";
	initnpctimer;
	end;
OnKilled:
	if(getmapmobs(getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_bunshin")+"::OnKilled") < 1) {
		initnpctimer;
	}
	end;
OnClose:
	stopnpctimer;
	killmonster getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_bunshin")+"::OnKilled";
	end;
}

1@ma_c.gat,2,2,0	script	#buwaya_boss	139,{
	end;
OnStart:
	areamonster getmdmapname("1@ma_c.gat"),90,67,104,81,"ブワヤ",2319,1,getmdnpcname("#buwaya_boss")+"::OnKilled";
	end;
OnKilled:
	set '@map$, getmdmapname("1@ma_c.gat");
	donpcevent getmdnpcname("BuwayaControl")+"::OnClose";
	donpcevent getmdnpcname("#buwaya_bunshin")+"::OnClose";
	donpcevent getmdnpcname("#buwaya_exit_mob")+"::OnClose";
	hideoffnpc getmdnpcname("#buwaya_caveout");
	announce "警備兵 : ご苦労様でした。入って来た場所から急いで脱出して下さい！",0x9,0x00ff99;
	end;
}

1@ma_c.gat,3,3,0	script	#buwaya_exit_mob	139,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer60000:
	set '@label$, getmdnpcname("#buwaya_exit_mob")+"::OnKilled";
	set '@map$, getmdmapname("1@ma_c.gat");
	if(getmapmobs('@map$,'@label$) < 30)
		set '@amount,5;
	else
		set '@amount,1;
	areamonster '@map$,43,58,47,60,"水草",2331,'@amount,'@label$;
	areamonster '@map$,43,58,47,60,"卵",2329,'@amount,'@label$;
	initnpctimer;
	end;
OnClose:
	stopnpctimer;
	killmonster getmdmapname("1@ma_c.gat"),getmdnpcname("#buwaya_exit_mob")+"::OnKilled";
	end;
}

1@ma_c.gat,28,57,0	script	#buwaya_caveout	45,2,2,{
OnTouch:
	mes "‐外に出ますか？‐";
	next;
	if(select("出る","出ない") == 2) {
		close;
	}
	mes "‐外に出ました‐";
	close2;
	warp "ma_fild02.gat",315,315;
	end;
}
