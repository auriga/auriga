//= Auriga Script ==============================================================
// Ragnarok Online Last Room Script	by refis
//==============================================================================
un_myst.gat,163,38,5	script	マークイシャ	616,{
	mes "[マークイシャ]";
	mes "この扉は今までと違って";
	mes "明らかにこちら側から";
	mes "塞いだ痕跡がありますね……。";
	cutin "bu_mark4",0;
	next;
	if(checkquest(11379) & 0x2) {
		delquest 11379;
		mes "[マークイシャ]";
		mes "しかし……";
		mes "また、ここに入るのか……。";
		mes "何だかこの中で過ごした時間の";
		mes "記憶があやふやで……。";
		mes "あまり何度も入りたい";
		mes "場所ではないですね……。";
		next;
	}
	cutin "bu_mark1",0;
	mes "[マークイシャ]";
	mes "どうしましょう。";
	mes "扉を開いて中に入りますか？";
	next;
	if(checkquest(11380) || checkquest(11379)) {
		mes "[マークイシャ]";
		mes "まだ疲れているようですね。";
		mes "ちゃんと休んで元気になったら";
		mes "中を調べにいきましょう。";
		cutin "bu_mark1.bmp", 0;
		next;
		mes "[マークイシャ]";
		mes "そういえばタマリンが";
		mes "誰かが掘って作ったと思われる";
		mes "出口を見つけました。";
		mes "ここを通れば外に出られそうですよ。";
		next;
		if(select("外に出たい","止めておく") == 2) {
			cutin "bu_mark2.bmp", 0;
			mes "[マークイシャ]";
			mes "そうですか。";
			mes "外に出たい時は";
			mes "いつでも声をかけて下さいね。";
			close2;
			cutin "bu_mark2.bmp", 255;
			end;
		}
		cutin "bu_mark2.bmp", 0;
		mes "[マークイシャ]";
		mes "かなり暗いので気をつけて";
		mes "進んでくださいね。";
		close2;
		cutin "bu_mark2.bmp", 255;
		warp "verus01.gat",115,190;
		end;
	}
	if(getonlinepartymember() < 1) {
		mes "[マークイシャ]";
		mes "パーティーを組んで";
		mes "いないようですね。";
		mes "……嫌な予感がしますから、";
		mes "必ずパーティーを組んでから";
		mes "中に入ってください。";
		close2;
		cutin "bu_mark1",255;
		end;
	}
	set '@party$,getpartyname(getcharid(1));
	set '@leader$,getpartyleader(getcharid(1));
	switch(select("扉を開ける","奥に入る","やめる","外に出たい")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "パーティー名：" +'@party$;
			mes "パーティーリーダー名：" +'@leader$;
			mes "^0000fflast_room ^000000-予約失敗";
			close2;
			cutin "bu_mark1",255;
			end;
		}
		mdcreate "last_room";
		mes "[マークイシャ]";
		mes "それでは扉を開きます。";
		mes "完全に開いたら";
		mes "中に入ってください。";
		close2;
		cutin "bu_mark1",255;
		end;
	case 2:
		switch(mdenter("last_room")) {
		case 0:	// エラーなし
			//setquest 11380;
			announce "メモリアルダンジョン[last_room] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
			setquest 11379;
			donpcevent getmdnpcname("LastRoomManager1")+ "::OnStart";
			cutin "bu_mark1",255;
			//warp "1@uns.gat",144,36;
			end;
		case 1:	// パーティー未加入
			mes "[マークイシャ]";
			mes "パーティーを組んで";
			mes "いないようですね。";
			mes "……嫌な予感がしますから、";
			mes "必ずパーティーを組んでから";
			mes "中に入ってください。";
			close2;
			cutin "bu_mark1",255;
			end;
		case 2:	// ダンジョン未作成
			mes "[マークイシャ]";
			mes "パーティーリーダーが";
			mes "扉を開いていないようですね。";
			mes "リーダーの方が先ず、";
			mes "扉を開いてください。";
			close2;
			cutin "bu_mark1",255;
			end;
		default:	// その他エラー
			close;
		}
	case 3:
		cutin "bu_mark4",0;
		mes "[マークイシャ]";
		mes "そうですね。";
		mes "何が起きるかわかりませんし";
		mes "妥当な選択だと思います。";
		mes "あいつもたまにはそんな風に、";
		mes "リーダーらしく物事を考えて";
		mes "発言して欲しいものです……。";
		close2;
		cutin "bu_mark4",255;
		end;
	case 4:
		cutin "bu_mark2",0;
		mes "[マークイシャ]";
		mes "そういえばタマリンが";
		mes "誰かが掘って作ったと思われる";
		mes "出口を見つけたんです。";
		mes "ここから外に出られると思いますが";
		mes "かなり暗いので気をつけて";
		mes "進んでくださいね。";
		close2;
		cutin "bu_mark2",255;
		warp "verus01.gat",115,190;
		end;
	}
}

1@uns.gat,1,1,0	script	LastRoomManager1	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("#lrdoor4");
	hideonnpc getmdnpcname("タマリン#room2");

	hideonnpc getmdnpcname("ベリティ#room4");
	hideonnpc getmdnpcname("タマリン#room4");
	hideonnpc getmdnpcname("テューリアン#room4");
	hideonnpc getmdnpcname("マークイシャ#room4");
	hideonnpc getmdnpcname("マギスティン#room4");
	hideonnpc getmdnpcname("アルプオカート#room4");

	hideonnpc getmdnpcname("システムメッセージ#batt");
	hideonnpc getmdnpcname("ベリティ#battle1");
	end;
}

1@uns.gat,143,36,3	script	ベリティ#room1	10078,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		close;
	}
	mes "[ベリティ]";
	mes "うっ……";
	mes "急に気持ちが悪く……。";
	cutin "EP15_2_brt_6.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : うっ……急に気持ちが悪く……。";
	next;
	mes "[ベリティ]";
	mes "頭が……";
	mes "割れる……くっ！";
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : 頭が……割れる……くっ！";
	next;
	mes "[ベリティ]";
	mes "ううっ……。";
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : ううっ……。";
	next;
	mes "[テューリアン]";
	mes "ちょっとお姉さん！";
	mes "大丈夫か!?";
	cutin "bu_du5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room1")),"テューリアン : ちょっとお姉さん！　大丈夫か!?";
	next;
	mes "[ベリティ]";
	mes "……カエ……らなきゃ。";
	cutin "EP15_2_brt_7.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : ……カエ……らなきゃ。";
	next;
	mes "[タマリン]";
	mes "ベリティさん！";
	mes "大丈夫ですか!?";
	cutin "ep143_tahuk.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("タマリン#room1")),"タマリン : ベリティさん！　大丈夫ですか!?";
	next;
	mes "[ベリティ]";
	mes "少し……休ませてくれる？";
	cutin "EP15_2_brt_6.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : 少し……休ませてくれる？";
	next;
	mes "[テューリアン]";
	mes "どうやらお姉さんは";
	mes "戻ったほうが良さそうだな。";
	cutin "bu_du1.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room1")),"テューリアン : どうやらお姉さんは戻ったほうが良さそうだな。";
	next;
	mes "[ベリティ]";
	mes "いえ……";
	mes "私もすぐに追いかけるわ。";
	mes "気にせず先に進んで頂戴。";
	cutin "EP15_2_brt_4.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room1")),"ベリティ : いえ……私もすぐに追いかけるわ。気にせず先に進んで頂戴。";
	next;
	mes "[タマリン]";
	mes "それでは私が付き添います。";
	mes "テューリアン達は気にせず";
	mes "先に進んでください。";
	cutin "ep143_taang.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("タマリン#room1")),"タマリン : それでは私が付き添います。テューリアン達は気にせず先に進んでください。";
	if('flag == 0) {
		set 'flag,1;
		donpcevent getmdnpcname("#lrdoor2")+"::OnStart";
	}
	close2;
	cutin "ep143_taang.bmp", 255;
	end;
}
1@uns.gat,142,38,5	script	テューリアン#room1	628,{
	mes "[テューリアン]";
	mes "しかし……";
	mes "なんだここは!?";
	mes "悪の秘密結社が使っていた";
	mes "地下のアジトなのか!?";
	cutin "bu_du5.bmp", 2;
	close2;
	cutin "bu_du5.bmp", 255;
	end;
}
1@uns.gat,145,37,3	script	タマリン#room1	10027,{
	mes "[タマリン]";
	mes "ベリティさん、大丈夫ですか？";
	mes "彼女は私が見ていますから、";
	mes "皆さんは、先に進んでください。";
	cutin "ep143_taang.bmp", 2;
	close2;
	cutin "ep143_taang.bmp", 255;
	end;
}
1@uns.gat,139,41,3	script	マークイシャ#room1	616,{
	mes "[マークイシャ]";
	mes "ここは……嫌な感じがする。";
	mes "みんな！　気を付けて進もう！";
	cutin "bu_mark4.bmp", 0;
	close2;
	cutin "bu_mark4.bmp", 255;
	end;
}
1@uns.gat,142,39,5	script	マギスティン#room1	612,{
	mes "[マギスティン]";
	mes "なぜでしょう……。";
	mes "何だかここにいると、";
	mes "自分がこの世界に独りのような";
	mes "気分になります……。";
	cutin "bu_maggi4.bmp", 2;
	close2;
	cutin "bu_maggi4.bmp", 255;
	end;
}
1@uns.gat,145,32,5	script	アルプオカート#room1	615,{
	mes "[アルプオカート]";
	mes "あちらこちらに怪しい痕跡がある。";
	mes "何か重い機械が通ったような……。";
	cutin "bu_alp1.bmp", 2;
	close2;
	cutin "bu_alp1.bmp", 255;
	end;
}
1@uns.gat,141,49,0	script	#lrdoor1	139,5,5,{
	misceffect 52,"";
	pushpc 0, 2;
	end;
}
1@uns.gat,140,45,0	script	#lrdoor2	139,{
OnStart:
	initnpctimer;
	announce "システムメッセージ : 警告、警告。", 0x9, 0xff0000;
	hideonnpc getmdnpcname("ベリティ#room1");
	hideonnpc getmdnpcname("テューリアン#room1");
	hideonnpc getmdnpcname("タマリン#room1");
	hideonnpc getmdnpcname("マークイシャ#room1");
	hideonnpc getmdnpcname("マギスティン#room1");
	hideonnpc getmdnpcname("アルプオカート#room1");
	//hideonnpc;
	end;
OnTimer2000:
	announce "システムメッセージ : 第1区域に侵入者を確認。直ちに退去してください。", 0x9, 0xff0000;
	end;
OnTimer4000:
	announce "システムメッセージ : 警告の無視を確認。侵入者は敵性存在と判断。", 0x9, 0xff0000;
	end;
OnTimer6000:
	announce "システムメッセージ : 自動防衛システム起動。", 0x9, 0xff0000;
	end;
OnTimer8000:
	announce "システムメッセージ : システム起動完了、オールグリーン。", 0x9, 0xff0000;
	end;
OnTimer10000:
	announce "システムメッセージ : 入口を閉鎖後、侵入者の排除を開始。", 0x9, 0xff0000;
	areamonster getmdmapname("1@uns.gat"),30,33,70,73,"システムメッセージ1",3253,1,getmdnpcname("#lrdoor2")+"::OnKilled";
	callsub L_MobCall;
	hideonnpc getmdnpcname("#lrdoor1");
	end;
OnTimer310000:
	announce "システムメッセージ : 侵入者を排除します。", 0x9, 0xff0000;
	callsub L_MobCall;
	end;
OnTimer610000:
	stopnpctimer;
	announce "システムメッセージ : 侵入者を排除します。", 0x9, 0xff0000;
	callsub L_MobCall;
	end;
L_MobCall:
	set '@map$,getmdmapname("1@uns.gat");
	set '@label$,getmdnpcname("#lrdoor2")+"::OnKilled";
	areamonster '@map$,125,44,145, 64,"機械部品",3251,3,'@label$;
	areamonster '@map$,117,50,137, 70,"機械部品",3251,3,'@label$;
	areamonster '@map$, 77,59, 97, 79,"機械部品",3251,3,'@label$;
	areamonster '@map$, 53,86, 73,106,"機械部品",3251,3,'@label$;
	areamonster '@map$,125,44,145, 64,"機械部品",3252,3,'@label$;
	areamonster '@map$,117,50,137, 70,"機械部品",3252,3,'@label$;
	areamonster '@map$, 77,59, 97, 79,"機械部品",3252,3,'@label$;
	areamonster '@map$, 53,86, 73,106,"機械部品",3252,3,'@label$;
	return;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@uns.gat"),getmdnpcname("#lrdoor2")+ "::OnKilled");
	if('@count <= 0) {
		stopnpctimer;
		announce "システムメッセージ : 自動防衛システムに障害発生。ホットスタンバイによる待機システムに処理を移行します。", 0x9, 0xff0000;
		hideoffnpc getmdnpcname("タマリン#room2");
	}
	end;
}
1@uns.gat,87,129,3	script	タマリン#room2	10027,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		close;
	}
	mes "[タマリン]";
	mes "はあ……はあ……。";
	mes "ベリティさんが……";
	mes "いきなり……";
	mes "立つことも出来なかった";
	mes "はずなのに……。";
	cutin "ep143_tahuk.bmp", 2;
	unittalk "タマリン : はあ……はあ……。ベリティさんが……いきなり……立つことも出来なかったはずなのに……。";
	next;
	mes "[タマリン]";
	mes "追いかけられないくらい……";
	mes "早くて……はあはあ……。";
	unittalk "タマリン : 追いかけられないくらい早くて……はあはあ……。";
	next;
	announce "システムメッセージ : 正体不明の物体が第1区域より第2区域に移動中。", 0x9, 0xff0000;
	mes "[タマリン]";
	mes "まさかベリティさんが";
	mes "もうあそこまで……。";
	unittalk "タマリン : まさかベリティさんがもうあそこまで……。";
	next;
	announce "システムメッセージ : 緊急プロトコルを実行します。", 0x9, 0xff0000;
	mes "[タマリン]";
	mes "早くベリティさんを";
	mes "探しに行かないと……！";
	unittalk "タマリン : 早くベリティさんを探しに行かないと……！";
	next;
	mes "[タマリン]";
	mes "道は一本道ですから";
	mes "早く行ってみましょう！";
	unittalk "タマリン : 道は一本道ですから早く行ってみましょう！";
	close2;
	if('flag == 0) {
		set 'flag,1;
		misceffect 35,getmdnpcname("#lrdoor4");
		hideoffnpc getmdnpcname("#lrdoor4");
	}
	cutin "ep143_tahuk.bmp", 255;
	end;
}
1@uns.gat,100,121,0	warp	#lrdoor4	3,3,1@uns.gat,145,107

1@uns.gat,157,94,0	script	#lrboom1	550,2,2,{
	end;
OnTouch:
	set '@num,substr(strnpcinfo(2),6);
	areamonster getmdmapname("1@uns.gat"),178,34,198,54,"機械部品",(3251 + (('@num-1) % 2)), 3;
	announce "システムメッセージ : 第2区域で侵入者を確認。排除します。", 0x9, 0xff0000;
	hideonnpc;
	end;
}
1@uns.gat,164,97,0	duplicate(#lrboom1)	#lrboom2	550,2,2
1@uns.gat,166,92,0	duplicate(#lrboom1)	#lrboom3	550,2,2
1@uns.gat,170,96,0	duplicate(#lrboom1)	#lrboom4	550,2,2
1@uns.gat,175,93,0	duplicate(#lrboom1)	#lrboom5	550,2,2
1@uns.gat,190,97,0	duplicate(#lrboom1)	#lrboom6	550,2,2
1@uns.gat,194,94,0	duplicate(#lrboom1)	#lrboom7	550,2,2
1@uns.gat,199,96,0	duplicate(#lrboom1)	#lrboom8	550,2,2
1@uns.gat,206,93,0	duplicate(#lrboom1)	#lrboom9	550,2,2
1@uns.gat,217,91,0	duplicate(#lrboom1)	#lrboom10	550,2,2
1@uns.gat,224,79,0	duplicate(#lrboom1)	#lrboom11	550,2,2
1@uns.gat,227,73,0	duplicate(#lrboom1)	#lrboom12	550,2,2
1@uns.gat,227,69,0	duplicate(#lrboom1)	#lrboom13	550,2,2
1@uns.gat,220,63,0	duplicate(#lrboom1)	#lrboom14	550,2,2
1@uns.gat,201,60,0	duplicate(#lrboom1)	#lrboom15	550,2,2

1@uns.gat,224,29,3	script	ベリティ#room2	10078,{
	mes "[ベリティ]";
	mes "う……ここは……";
	mes "なぜ……私がここに？";
	cutin "EP15_2_brt_6.bmp", 2;
	next;
	mes "[ベリティ]";
	mes "頭が……うっ……";
	mes "割れそうに……";
	mes "この扉の奥から……";
	mes "何か……音が……。";
	next;
	if(select("立ち去る","奥に進む") == 1) {
		mes "[ベリティ]";
		mes "カエ……カエらないと……。";
		cutin "EP15_2_brt_7.bmp", 2;
		close2;
		cutin "EP15_2_brt_7.bmp", 255;
		end;
	}
	mes "[ベリティ]";
	mes "早く……カエらないと……。";
	cutin "EP15_2_brt_7.bmp", 2;
	close2;
	cutin "EP15_2_brt_7.bmp", 255;
	warp getmdmapname("1@uns.gat"),240,255;
	end;
}

1@uns.gat,242,253,3	script	ベリティ#room3	10078,{
	mes "[ベリティ]";
	mes "やっと……帰ってきた……。";
	mes "本当にやっと……。";
	cutin "EP15_2_brt_7.bmp", 2;
	close2;
	if('flag == 0) {
		set 'flag,1;
		hideonnpc getmdnpcname("ベリティ#room3");
		donpcevent getmdnpcname("#bosslr_timer")+"::OnStart";
	}
	cutin "EP15_2_brt_7.bmp", 255;
	end;
}

1@uns.gat,1,1,0	script	#bosslr_timer	139,{
	end;
OnStart:
	sleep 2000;
	announce "システムメッセージ : マザールームで侵入者を確認。", 0x9, 0xff0000;
	sleep 2000;
	announce "システムメッセージ : 全システムのプライオリティを強制変更。", 0x9, 0xff0000;
	sleep 2000;
	announce "システムメッセージ : 侵入者の排除を最優先事項に設定。全システム戦闘モードに移行します。", 0x9, 0xff0000;
	hideoffnpc getmdnpcname("ベリティ#battle1");
	areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ2",3493,5,getmdnpcname("#bosslr_timer")+"::OnKilled";
	sleep 2000;
	announce "システムメッセージ : ……を守るためのプロセスを実行。非関係者は速やかに退避してください。", 0x9, 0xff0000;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+ "::OnKilled") + 1;
	if(rand('@count) == 0) {
		initnpctimer;
		killmonster getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+"::OnKilled";
		hideoffnpc getmdnpcname("システムメッセージ#batt");
	}
	end;
OnTimer1000:
	announce "システムメッセージ : 防衛システムにエラー発生。", 0x9, 0xff0000;
	unittalk getnpcid(0,getmdnpcname("システムメッセージ#batt")),"システムメッセージ : 防衛システムにエラー発生。";
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("ベリティ#battle1")),"ベリティ : ……。";
	end;
OnTimer8000:
	unittalk getnpcid(0,getmdnpcname("ベリティ#battle1")),"ベリティ : 排除……。制御……変更。";
	misceffect 432,getmdnpcname("ベリティ#battle1");
	end;
OnTimer9000:
	misceffect 452,getmdnpcname("ベリティ#battle1");
	end;
OnTimer10000:
	misceffect 257,getmdnpcname("ベリティ#battle1");
	end;
OnTimer10500:
	misceffect 30,getmdnpcname("ベリティ#battle1");
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ベリティ#battle1")),"ベリティ : ……制御……確認。";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("ベリティ#battle1")),"ベリティ : システムメッセージ1による補助システム構成……構築完了。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ベリティ#battle1")),"ベリティ : 主目的を出力補助に設定……起動確認。";
	end;
OnTimer28000:
	announce "システムメッセージ : T_W_O_002bによる制御を確認。侵入者の排除を再開。", 0x9, 0xff0000;
	misceffect 514,getmdnpcname("ベリティ#battle1");
	misceffect 94,getmdnpcname("ベリティ#battle1");
	end;
OnTimer31000:
	misceffect 8,getmdnpcname("ベリティ#battle1");
	misceffect 263,getmdnpcname("ベリティ#battle1");
	end;
OnTimer32000:
	misceffect 220,getmdnpcname("ベリティ#battle1");
	end;
OnTimer33000:
	hideonnpc getmdnpcname("ベリティ#battle1");
	hideonnpc getmdnpcname("システムメッセージ#batt");
	donpcevent getmdnpcname("#bosslr")+"::OnStart";
	areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#1",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
	areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#2",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
	areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#3",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
	areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#4",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
	end;
OnTimer35000:
	announce "テューリアン : 急にどうしちまったんだよお姉さん！　くそっ……凄い力だ！", 0x9, 0x00ff00;
	end;
OnTimer40000:
	announce "タマリン : あのシステムメッセージ1と呼んでいた物体……あれがエネルギーを供給しているようですね。", 0x9, 0x00ff00;
	end;
OnTimer45000:
	initnpctimer getmdnpcname("#bosslr");
	announce "タマリン : システムメッセージ1を倒せば、力を落とせるかも知れません！", 0x9, 0x00ff00;
	end;
OnTimer315000:
OnTimer590000:
OnTimer865000:
	set '@count,getmapmobs(getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+ "::OnKilled2");
	if('@count < 4) {
		announce "T_W_O : 補助システム再構築完了……再起動……完了。", 0x9, 0xff0000;
		killmonster getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+"::OnKilled2";
		areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#1",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
		areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#2",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
		areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#3",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
		areamonster getmdmapname("1@uns.gat"),225,250,265,280,"システムメッセージ1#4",3253,1,getmdnpcname("#bosslr_timer")+"::OnKilled2";
	}
	end;
OnKilled2:
	end;
}

1@uns.gat,2,2,0	script	#bosslr	139,{
OnStart:
	set 'mob_id,callmonster(getmdmapname("1@uns.gat"),245,265,"T_W_O#002b",3254,getmdnpcname("#bosslr")+"::OnKilled");
	end;
OnTimer10000:
	if(getmobhp('mob_id) <= 0) {
		stopnpctimer;
		end;
	}
	set 'count,getmapmobs(getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+ "::OnKilled2") + 1;
	unittalk 'mob_id,"T_W_O : 補助システムによる出力強化……攻撃開始。";
	end;
OnTimer11000:
	if(getmobhp('mob_id) <= 0) {
		stopnpctimer;
		end;
	}
	set 'r,rand(4);
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	setarray '@lv,1,2,4,6,8,10;
	switch('r) {
	case 0:	//サンダーストーム
		for(set '@i,0; '@i<'count; set '@i,'@i+1) {
			switch('@i%2) {
			case 0:	//十字
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y+5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y-5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y+10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y-10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y+15,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x,'@y-15,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+5,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-5,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+10,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-10,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+15,'@y,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-15,'@y,0,0;	// サンダーストーム
				break;
			case 1:	//Ｘ字
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+5,'@y+5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+5,'@y-5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-5,'@y+5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-5,'@y-5,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+10,'@y+10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+10,'@y-10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-10,'@y+10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-10,'@y-10,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+15,'@y+15,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x+15,'@y-15,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-15,'@y+15,0,0;	// サンダーストーム
				mobuseskillpos 'mob_id,21,'@lv['count],'@x-15,'@y-15,0,0;	// サンダーストーム
				break;
			}
			sleep 500;
		}
		break;
	case 1:	//サイトラッシャー
		for(set '@i,0; '@i<'count; set '@i,'@i+1) {
			mobuseskill 'mob_id,81,'@lv['count],0,0,-1,0,0;	// サイトラッシャー
			sleep 250;
		}
		mobuseskill 'mob_id,19,'@lv['count],0,0,-1,0,1;	// ファイアーボルト
		break;
	case 2:	//ユピテルサンダー
		for(set '@i,0; '@i<'count; set '@i,'@i+1) {
			mobuseskill 'mob_id,84,3,0,0,-1,0,1;	// ユピテルサンダー
			sleep 250;
		}
		break;
	case 3:	//ファイアーピラー
		mobuseskillpos 'mob_id,483,1,'@x-3,'@y,0,0;	// ガンバンテイン
		mobuseskillpos 'mob_id,483,1,'@x+3,'@y,0,0;	// ガンバンテイン
		mobuseskillpos 'mob_id,483,1,'@x,'@y-3,0,0;	// ガンバンテイン
		mobuseskillpos 'mob_id,483,1,'@x,'@y+3,0,0;	// ガンバンテイン
		mobuseskillpos 'mob_id,483,1,'@x-6,'@y,0,0;	// ガンバンテイン
		mobuseskillpos 'mob_id,483,1,'@x+6,'@y,0,0;	// ガンバンテイン
		sleep 500;
		mobuseskillpos 'mob_id,80,'@lv['count],'@x-5,'@y,0,0;	// ファイアーピラー
		mobuseskillpos 'mob_id,80,'@lv['count],'@x+5,'@y,0,0;	// ファイアーピラー
		mobuseskillpos 'mob_id,80,'@lv['count],'@x,'@y+5,0,0;	// ファイアーピラー
		mobuseskillpos 'mob_id,80,'@lv['count],'@x,'@y-5,0,0;	// ファイアーピラー
		if('count >= 2) {
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-4,'@y+1,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+4,'@y+1,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+4,'@y-1,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-4,'@y-1,0,0;	// ファイアーピラー
		}
		if('count >= 3) {
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-3,'@y+2,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+3,'@y+2,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+3,'@y-2,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-3,'@y-2,0,0;	// ファイアーピラー
		}
		if('count >= 4) {
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-2,'@y+3,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+2,'@y+3,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+2,'@y-3,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-2,'@y-3,0,0;	// ファイアーピラー
		}
		if('count >= 5) {
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-1,'@y+4,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+1,'@y+4,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x+1,'@y-4,0,0;	// ファイアーピラー
			mobuseskillpos 'mob_id,80,'@lv['count],'@x-1,'@y-4,0,0;	// ファイアーピラー
		}
		break;
	}
	initnpctimer;
	end;
OnKilled:
	stopnpctimer;
	stopnpctimer getmdnpcname("#bosslr_timer");
	set 'mob_id,0;
	killmonster getmdmapname("1@uns.gat"),getmdnpcname("#bosslr_timer")+"::OnKilled2";
	announce "システムメッセージ : 侵入者の排除に失敗。地域閉鎖を行います。", 0x9, 0xff0000;
	hideonnpc getmdnpcname("ベリティ#room2");
	hideoffnpc getmdnpcname("ベリティ#room4");
	hideoffnpc getmdnpcname("タマリン#room4");
	hideoffnpc getmdnpcname("テューリアン#room4");
	hideoffnpc getmdnpcname("マークイシャ#room4");
	hideoffnpc getmdnpcname("マギスティン#room4");
	hideoffnpc getmdnpcname("アルプオカート#room4");
	end;
}

1@uns.gat,246,266,3	script	システムメッセージ#batt	3253,{}
1@uns.gat,245,265,3	script	ベリティ#battle1	10078,{
	emotion 9;
	end;
}

1@uns.gat,242,253,3	script	ベリティ#room4	10078,{
	mes "[テューリアン]";
	mes "姉さん！";
	mes "急にどうしたんだ！";
	mes "大丈夫か!?";
	cutin "bu_du5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room4")),"テューリアン :  姉さん！　急にどうしたんだ！　大丈夫か!?";
	next;
	mes "[タマリン]";
	mes "ベリティさん！";
	mes "しっかりして下さい！";
	cutin "ep143_tahuk.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("タマリン#room4")),"タマリン : ベリティさん！　しっかりして下さい！";
	next;
	mes "[マークイシャ]";
	mes "みんなどいて！";
	mes "私がひとまずヒールを！";
	cutin "bu_mark4.bmp", 0;
	unittalk getnpcid(0,getmdnpcname("マークイシャ#room4")),"マークイシャ : みんなどいて！　私がひとまずヒールを！";
	next;
	mes "[ベリティ]";
	mes "わ、悪いわね……。";
	cutin "EP15_2_brt_4.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : わ、悪いわね……。";
	next;
	mes "[ベリティ]";
	mes "って……あら……";
	mes "あなた達、どうかしたの？";
	mes "深刻な顔をして。";
	cutin "EP15_2_brt_5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : って……あら……あなた達、どうかしたの？　深刻な顔をして。";
	next;
	mes "[テューリアン]";
	mes "なにいってるんだ、姉さん！";
	mes "どうしたんだ!?は、";
	mes "こっちの台詞だぞ!?";
	cutin "bu_du3.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room4")),"テューリアン : なにいってるんだ、姉さん！　どうしたんだ!?は、こっちの台詞だぞ!?";
	next;
	mes "[ベリティ]";
	mes "……どういうこと？";
	cutin "EP15_2_brt_5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : ……どういうこと？";
	next;
	mes "[ベリティ]";
	mes "そういえば……";
	mes "ここはどこなの？ ";
	cutin "EP15_2_brt_3.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : そういえば……ここはどこなの？";
	next;
	mes "[タマリン]";
	mes "ベリティさん、本当に何も";
	mes "覚えていませんか？";
	cutin "ep143_tahuk.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("タマリン#room4")),"タマリン : ベリティさん、本当に何も覚えていませんか？";
	next;
	mes "[ベリティ]";
	mes "そうね……。";
	mes "地下に降りてから";
	mes "頭が破裂しそうなくらい";
	mes "痛かったけど……。";
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : そうね……。地下に降りてから頭が破裂しそうなくらい痛かったけど……。";
	cutin "EP15_2_brt_3.bmp", 2;
	next;
	mes "[ベリティ]";
	mes "それ以降は覚えてないわね……。";
	unittalk getnpcid(0,getmdnpcname("ベリティ#room4")),"ベリティ : それ以降は覚えてないわね……。";
	cutin "EP15_2_brt_5.bmp", 2;
	next;
	mes "[テューリアン]";
	mes "それじゃあさっき";
	mes "俺たちを襲ってきたのは……？";
	cutin "bu_du5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room4")),"テューリアン : それじゃあさっき俺たちを襲ってきたのは……？";
	next;
	mes "[アルプオカート]";
	mes "おい、今は悠長に話をしている";
	mes "時間はなさそうだぞ。";
	cutin "bu_alp3.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("アルプオカート#room4")),"アルプオカート : おい、今は悠長に話をしている時間はなさそうだぞ。";
	next;
	mes "[テューリアン]";
	mes "しかしだな！";
	mes "さっきのは絶対……。";
	cutin "bu_du5.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("テューリアン#room4")),"テューリアン : しかしだな！　さっきのは絶対……。";
	next;
	mes "[アルプオカート]";
	mes "……この音が聞こえないか？";
	mes "何かがここに向かっている。";
	cutin "bu_alp1.bmp", 2;
	soundeffect "lava_golem_attack.wav", 0, 0;
	unittalk getnpcid(0,getmdnpcname("アルプオカート#room4")),"アルプオカート : ……この音が聞こえないか？　何かがここに向かっている。";
	next;
	mes "[タマリン]";
	mes "そういえば地面も少し";
	mes "揺れている感じがしませんか？";
	cutin "ep143_tahuk.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("タマリン#room4")),"タマリン : そういえば地面も少し揺れている感じがしませんか？";
	next;
	mes "[マギスティン]";
	mes "どんどん揺れが酷く";
	mes "なっています……！";
	misceffect 522,"";
	cutin "bu_maggi4.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("マギスティン#room4")),"マギスティン : どんどん揺れが酷くなっています……！";
	next;
	mes "[アルプオカート]";
	mes "ここは危険だ。";
	mes "すぐに脱出した方が良い。";
	mes "抜け道らしきものは見つけておいた。";
	cutin "bu_alp2.bmp", 2;
	unittalk getnpcid(0,getmdnpcname("アルプオカート#room4")),"アルプオカート : ここは危険だ。すぐに脱出した方が良い。抜け道らしきものは見つけておいた。";
	next;
	mes "[マークイシャ]";
	mes "わ、わかった！";
	mes "私達は後から行きますから、ベリティさんと";
	mes "先に一緒に脱出してください！";
	cutin "bu_mark4.bmp", 0;
	unittalk getnpcid(0,getmdnpcname("マークイシャ#room4")),"マークイシャ : わ、わかった！　私達は後から行きますから、ベリティさんと先に一緒に脱出してください！";
	next;
	menu "ここから出る",-;
	cutin "bu_mark4.bmp", 255;
	warp "verus01.gat",122,187;
	close;
}
1@uns.gat,236,258,1	script	アルプオカート#room4	615,{
	mes "[アルプオカート]";
	mes "安心するにはまだ早い……。";
	mes "俺は念のため、脱出口を調べておく。";
	cutin "bu_alp1.bmp", 2;
	close2;
	cutin "bu_alp1.bmp", 255;
	end;
}
1@uns.gat,244,257,3	script	タマリン#room4	10027,{
	mes "[タマリン]";
	mes "ベリティさん！";
	mes "しっかりして下さい！";
	cutin "ep143_tahuk.bmp", 2;
	close2;
	cutin "ep143_tahuk.bmp", 255;
	end;
}
1@uns.gat,245,254,3	script	マギスティン#room4	612,{
	mes "[マギスティン]";
	mes "ベリティさん……";
	mes "大丈夫ですか？";
	cutin "bu_maggi4.bmp", 2;
	close2;
	cutin "bu_maggi4.bmp", 255;
	end;
}
1@uns.gat,244,254,3	script	テューリアン#room4	628,{
	mes "[テューリアン]";
	mes "姉さん！";
	mes "急にどうしたんだ！";
	mes "大丈夫か!?";
	cutin "bu_du5.bmp", 2;
	close2;
	cutin "bu_du5.bmp", 255;
	end;
}
1@uns.gat,242,255,5	script	マークイシャ#room4	616,{
	mes "[マークイシャ]";
	mes "みんなどいて！";
	mes "私がひとまずヒールを！";
	cutin "bu_mark4.bmp", 0;
	close2;
	cutin "bu_mark4.bmp", 255;
	end;
}
