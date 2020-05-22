//= Auriga Script ==============================================================
// Ragnarok Online Morse Cave Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
moro_cav.gat,61,69,3	script	先任追跡隊員#a1	730,{
	if(checkquest(9319) || checkquest(118930)) {
		if(checkquest(9319)&0x2 == 0 || checkquest(118930)&0x2 == 0) {
			mes "[先任追跡隊員]";
			mes "力の回復の為に手段と方法を選ばない";
			mes "モロクのことを考えていたら、";
			mes "不安で夜も眠れません。";
			next;
			mes "[先任追跡隊員]";
			mes "そうですね……。";
			mes "入場してから1回目の";
			mes "^ff0000午前5時以降^000000にまた来てください。";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過しないと";
			mes "入場出来ないみたいです。";
			close;
		}
	}
	if(checkquest(201725)) {	// モルスクリア済み
		mes "[先任追跡隊員]";
		mes "もう一度戻って来ると思いました。";
		next;
		mes "[先任追跡隊員]";
		mes "モロクを相手する為には";
		mes "1人ではとても危険なので";
		mes "パーティー員と力を合わせて下さい。";
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "もし、赤い花に通じる道を利用するなら";
			mes "パーティーリーダーの方に";
			mes "私に話しかけるよう、伝えてください。";
			close;
		}
		mes "それでは";
		mes "赤い花に入ってみますか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[先任追跡隊員]";
			mes "気が変わったら";
			mes "また訪ねて来て下さい！";
			close;
		}
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[先任追跡隊員]";
			mes "まだ赤い花へ続く扉が";
			mes "開いていません。";
			mes "少し待って下さい。";
			close;
		}
		mdcreate "mors";
		mes "[先任追跡隊員]";
		mes "さあ、赤い花に";
		mes "通じる道を開けました。";
		mes "この道を開ける時間は";
		mes "制限されているので";
		mes "早く入って下さい。";
		close;
	}
	mes "[先任追跡隊員]";
	mes "ここはモロク復活を防ぐ連合軍の";
	mes "最前線です。";
	mes "私はモロクの足跡を追っています。";
	next;
	if(checkquest(201720) == 0) {	// ビオスの島未攻略
		mes "[先任追跡隊員]";
		mes "現在、この赤い花を調査中です。";
		mes "どうもその隣にある、";
		mes "黄色い種と深い関係が";
		mes "ありそうなのですが……。";
		next;
		mes "‐^ff0000黄色い種^000000を先に調査しよう‐";
		close;
	}
	mes "[先任追跡隊員]";
	mes "これまでの努力が実り、";
	mes "ついにモロクの潜伏先として";
	mes "有力な場所を発見しました。";
	next;
	mes "[先任追跡隊員]";
	mes "それがこの^ff0000赤い花^000000です。";
	next;
	mes "[先任追跡隊員]";
	mes "ただ、追跡を専門とする私の力では";
	mes "ここより先への侵入は";
	mes "危険であると判断しました。";
	next;
	mes "[先任追跡隊員]";
	mes "あなたもここを訪れたという事は";
	mes "同じ目的をもった実力者でしょう？";
	next;
	mes "[先任追跡隊員]";
	mes "どうでしょう。";
	mes "一つ中へ侵入してモロク追跡の";
	mes "先陣を切ってくれませんか？";
	next;
	mes "[先任追跡隊員]";
	mes "但し、弱っているとはいえ";
	mes "相手はモロクです。";
	mes "1人では危険なので";
	mes "必ず^ff0000パーティーを組んで^000000";
	mes "挑んでください。";
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		next;
		mes "[先任追跡隊員]";
		mes "赤い花へ通じる道は私が開いています。";
		mes "もし、先に進むようでしたら";
		mes "パーティーリーダーの方に";
		mes "私に話しかけるよう、伝えてください。";
		close;
	}
	mes "では赤い花に入ってみますか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[先任追跡隊員]";
		mes "気が変わったら";
		mes "また訪ねて来て下さい！";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[先任追跡隊員]";
		mes "まだ赤い花に";
		mes "入れる扉が";
		mes "開いていません。";
		mes "少し待って下さい。";
		close;
	}
	mdcreate "mors";
	mes "[先任追跡隊員]";
	mes "さあ、赤い花に";
	mes "通じる道を開けました。";
	mes "この道を開ける時間は";
	mes "制限されているので";
	mes "早く入って下さい。";
	close;
OnInit:
	waitingroom "モルスの洞窟生成",0;
	end;
}
moro_cav.gat,57,69,3	script	赤い花#a1	844,{
	if(checkquest(9319) || checkquest(118930)) {
		if(checkquest(9319)&0x2 == 0 || checkquest(118930)&0x2 == 0) {
			mes "‐赤い花が閉ざされている。";
			mes "　入る事ができなさそうだ‐";
			next;
			mes "‐入場してから1回目の";
			mes "　^ff0000午前5時以降^000000にまた来てみよう。";
			mes "　但し、最後の入場をしてから";
			mes "　^ff00001時間^000000経過しないと";
			mes "　入場出来ないようだ‐";
			close;
		}
	}
	if(checkquest(201720) == 0) {	// ビオスの島未攻略
		mes "[先任追跡隊員]";
		mes "ここはモロク復活を防ぐ連合軍の";
		mes "最前線です。";
		mes "私はモロクの足跡を追っています。";
		mes "　";
		mes "‐^ff0000ビオスの島未攻略のため";
		mes "　入場が出来ません^000000‐";
		close;
	}
	mes "‐赤い花がある‐";
	next;
	if(select("赤い花に入る","赤い花に入らない") == 2) {
		mes "‐その場を後にした‐";
		close;
	}
	switch(mdenter("mors")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[mors] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
		setquest 9319;
		setquest 9318;
		setquest 118930;
		donpcevent getmdnpcname("MorsControl")+ "::OnStart";
		close2;
		//warp "1@rev.gat",26,181;
		end;
	case 1:	// パーティー未加入
		mes "‐パーティー員のみ、";
		mes "　メモリアルダンジョンに";
		mes "　入場することができます‐";
		close;
	case 2:	// ダンジョン未作成
		mes "‐パーティーリーダーが";
		mes "　メモリアルダンジョンを";
		mes "　生成していない状態です‐";
		close;
	default:	// その他エラー
		close;
	}
OnTimer15000:
	initnpctimer;
	misceffect 239;
	end;
OnInit:
	initnpctimer;
	waitingroom "モルスの洞窟入場",0;
	end;
}

//============================================================
// モルスの洞窟
//------------------------------------------------------------
1@rev.gat,1,1,0	script	MorsControl	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("教官長イグリド#RZ1");
	hideonnpc getmdnpcname("キド#RZ1");
	hideonnpc getmdnpcname("ヒシエ#RZ1");
	hideonnpc getmdnpcname("教官長イグリド#RZ2");
	hideonnpc getmdnpcname("キド#RZ2");
	hideonnpc getmdnpcname("ヒシエ#RZ2");
	hideonnpc getmdnpcname("教官長イグリド#RZ3");
	hideonnpc getmdnpcname("キド#RZ3");
	hideonnpc getmdnpcname("ヒシエ#RZ3");
	hideonnpc getmdnpcname("教官長イグリド#RZ4");
	hideonnpc getmdnpcname("キド#RZ4");
	hideonnpc getmdnpcname("ヒシエ#RZ4");
	hideonnpc getmdnpcname("教官長イグリド#RZ5");
	hideonnpc getmdnpcname("キド#RZ5");
	hideonnpc getmdnpcname("ヒシエ#RZ5");

	hideonnpc getmdnpcname("死神アンク#RZイベント_2");
	hideonnpc getmdnpcname("死神アンク#RZイベント_3");
	hideonnpc getmdnpcname("死神アンク#RZイベント_5");
	hideonnpc getmdnpcname("死神アンク#RZイベント_6");
	hideonnpc getmdnpcname("モルス・魔導士#RZ1");
	hideonnpc getmdnpcname("#RZイベント_1");
	hideonnpc getmdnpcname("#RZイベント_1-2");

	hideonnpc getmdnpcname("#RZ移動_1");
	hideonnpc getmdnpcname("#RZ移動_2");
	hideonnpc getmdnpcname("#RZ移動_3");
	hideonnpc getmdnpcname("#RZ移動_4");
	hideonnpc getmdnpcname("#RZ移動_5");
	hideonnpc getmdnpcname("#RZ移動_6");
	hideonnpc getmdnpcname("#RZ移動_7");
	hideonnpc getmdnpcname("#RZ移動_8");
	hideonnpc getmdnpcname("#RZ移動_5a");
	hideonnpc getmdnpcname("#RZ移動_6a");
	hideonnpc getmdnpcname("#RZ移動_7a");
	hideonnpc getmdnpcname("#RZ移動_8a");

	hideonnpc getmdnpcname("#RZ移動_13a");
	hideonnpc getmdnpcname("#RZ移動_14a");
	hideonnpc getmdnpcname("#RZ移動_15a");
	hideonnpc getmdnpcname("#RZ移動_16a");
	hideonnpc getmdnpcname("#RZ移動_13");
	hideonnpc getmdnpcname("#RZ移動_14");
	hideonnpc getmdnpcname("#RZ移動_15");
	hideonnpc getmdnpcname("#RZ移動_16");

	hideonnpc getmdnpcname("#RZ移動_17a");

	hideonnpc getmdnpcname("#RZ移動_30");
	hideonnpc getmdnpcname("#RZ移動_31");
	hideonnpc getmdnpcname("#RZ移動_32");
}

1@rev.gat,27,181,0	script	#RZメモリアルスタート	139,1,1,{
OnTouch:
	if(getpartyleader(getcharid(1)) != strcharinfo(0))
		end;
	hideonnpc getmdnpcname("#RZメモリアルスタート");
	hideoffnpc getmdnpcname("#RZイベント_1");
	end;
}

1@rev.gat,34,120,0	script	#RZ_EFFECT01	139,{
OnStart:
	initnpctimer;
	misceffect 89;
	end;
OnTimer2000:
	initnpctimer;
	misceffect 196;
	end;
OnStop:
	stopnpctimer;
	end;
}

1@rev.gat,34,48,0	script	#RZ_EFFECT02	139,{
OnStart:
	initnpctimer;
	misceffect 89;
	misceffect 196;
	end;
OnTimer2000:
	initnpctimer;
	misceffect 196;
	end;
OnStop:
	stopnpctimer;
	end;
}

1@rev.gat,31,181,0	script	#RZイベント_1	139,5,5,{
OnTouch:
	if(getpartyleader(getcharid(1)) != strcharinfo(0))
		end;
	pcblockmove 1;
	set '@dummy,sleep2(3000);
	misceffect 1, getmdnpcname("#RZメモリアルスタート");
	announce "モロク : 誰だ？　私の休息の邪魔をするのは。", 0x9, 0x00ebff;
	set '@dummy,sleep2(2000);
	announce "‐どこからともなく声がする。どうやらここがモロクの潜伏先で間違いないようだ‐", 0x9, 0x00ebff;
	set '@dummy,sleep2(4000);
	announce "？？？ : 待ってくれ！", 0x9, 0x00ebff;
	set '@dummy,sleep2(2000);
	misceffect 60,""; //self
	pcblockmove 0;
	hideonnpc getmdnpcname("#RZイベント_1");
	hideoffnpc getmdnpcname("#RZイベント_1-2");
	end;
}

1@rev.gat,31,181,0	script	#RZイベント_1-2	139,5,5,{
OnTouch:
	if(getpartyleader(getcharid(1)) != strcharinfo(0))
		end;
	mes "‐後方から声が聞こえる？";
	mes "　誰か来たのだろうか‐";
	next;
	set 'menu,select(
		(ASH_6QUE == 14 || ASH_6QUE == 15? "イグリド": "？？？"),
		(ASH_5QUE >= 31? "キド": "？？？"),
		(ECL_3QUE >= 33? "ヒシエ": "？？？"),
		"誰もいない");
	hideonnpc getmdnpcname("#RZイベント_1-2");
	switch('menu) {
	case 1:
		if(ASH_6QUE < 14 || ASH_6QUE > 15) {
			mes "‐声が聞こえた気がしたが、";
			mes "　気のせいだったようだ‐";
			mes "‐^ff0000三ヶ国への報告書クエスト^000000を";
			mes "　クリアしていないため";
			mes "　仲間はかけつけませんでした‐";
			set 'menu,0;
			donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
			close;
		}
		hideoffnpc getmdnpcname("教官長イグリド#RZ1");
		donpcevent getmdnpcname("教官長イグリド#RZ1")+ "::OnStart";
		break;
	case 2:
		if(ASH_5QUE < 31) {
			mes "‐声が聞こえた気がしたが、";
			mes "　気のせいだったようだ‐";
			mes "‐^ff0000魔王モロク追跡クエスト^000000を";
			mes "　クリアしていないため";
			mes "　仲間はかけつけませんでした‐";
			set 'menu,0;
			donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
			close;
		}
		hideoffnpc getmdnpcname("キド#RZ1");
		donpcevent getmdnpcname("キド#RZ1")+ "::OnStart";
		break;
	case 3:
		if(ECL_3QUE < 33) {
			mes "‐声が聞こえた気がしたが、";
			mes "　気のせいだったようだ‐";
			mes "‐^ff0000エクラージュの王クエスト^000000を";
			mes "　クリアしていないため";
			mes "　仲間はかけつけませんでした‐";
			set 'menu,0;
			donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
			close;
		}
		hideoffnpc getmdnpcname("ヒシエ#RZ1");
		donpcevent getmdnpcname("ヒシエ#RZ1")+ "::OnStart";
		break;
	case 4:	//??
		mes "‐声が聞こえた気がしたが、";
		mes "　気のせいだったようだ‐";
		set 'menu,0;
		donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
		close;
	}
	mes "‐仲間がかけつけた-";
	close;
}

1@rev.gat,20,181,0	script	#モルス入口スタート	139,{
OnStart:
	set '@map$,getmdmapname("1@rev.gat");
	set '@label$,getmdnpcname("#モルス入口スタート")+ "::OnKilled";
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	monster '@map$,38,180,"モルス・グール",3001,1,'@label$;
	monster '@map$,38,181,"モルス・グール",3001,1,'@label$;
	monster '@map$,38,182,"モルス・グール",3001,1,'@label$;
	monster '@map$,54,180,"モルス・グール",3001,1,'@label$;
	monster '@map$,54,181,"モルス・グール",3001,1,'@label$;
	monster '@map$,54,182,"モルス・グール",3001,1,'@label$;
	monster '@map$,70,180,"モルス・グール",3001,1,'@label$;
	monster '@map$,70,181,"モルス・グール",3001,1,'@label$;
	monster '@map$,70,182,"モルス・グール",3001,1,'@label$;
	initnpctimer;
	end;
OnTimer2000:
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#モルス入口スタート")+ "::OnKilled");
	if('@count <= 0) {
		stopnpctimer;
		hideoffnpc getmdnpcname("死神アンク#RZイベント_2");
		if('menu == 1) {
			hideonnpc getmdnpcname("教官長イグリド#RZ1");
			hideoffnpc getmdnpcname("教官長イグリド#RZ2");
		} else if('menu == 2) {
			hideonnpc getmdnpcname("キド#RZ1");
			hideoffnpc getmdnpcname("キド#RZ2");
		} else if('menu == 3) {
			hideonnpc getmdnpcname("ヒシエ#RZ1");
			hideoffnpc getmdnpcname("ヒシエ#RZ2");
		}
		donpcevent getmdnpcname("死神アンク#RZイベント_2")+ "::OnStart";
	}
	end;
OnTimer4000:
	initnpctimer;
	end;
OnKilled:
	end;
}

1@rev.gat,25,183,5	script	教官長イグリド#RZ1	751,{
	mes "[イグリド]";
	mes "気を付けろ！";
	mes "敵が来ているぞ！";
	close;
OnStart:
	initnpctimer;
	unittalk "イグリド : ふぅ。間に合ったようだな。";
	end;
OnTimer3000:
	donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
	unittalk "イグリド : 兄……いや、司令官に許可はもらってきた。一緒に俺も行かせてくれ。";
	end;
OnTimer6000:
	stopnpctimer;
	unittalk "イグリド : 気を付けろ！　さっそく敵が来たようだぞ！";
	end;
}

1@rev.gat,25,183,5	script	キド#RZ1	884,{
	mes "[キド]";
	mes "敵が来るぞ！";
	close;
OnStart:
	initnpctimer;
	unittalk "キド : 間に合ったか。";
	end;
OnTimer3000:
	donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
	unittalk "キド : リーンには伝えてきた。決戦の時が近づいている。俺も一緒に行かせてくれ。";
	end;
OnTimer6000:
	stopnpctimer;
	unittalk "キド : さっそく敵さんのお出ましか。気を付けろ！";
	end;
}

1@rev.gat,25,183,5	script	ヒシエ#RZ1	623,{
	mes "[ヒシエ]";
	mes "敵が来ているぞ！";
	mes "注意しろ！";
	close;
OnStart:
	initnpctimer;
	unittalk "ヒシエ : 間に合ったか。";
	end;
OnTimer3000:
	donpcevent getmdnpcname("#モルス入口スタート")+ "::OnStart";
	unittalk "ヒシエ : そろそろカルの魔力が心配なんだ。急ぐ必要がある。俺も一緒に行かせてくれ。";
	end;
OnTimer6000:
	stopnpctimer;
	unittalk "ヒシエ : 敵が来ているな。油断するなよ！";
	end;
}

1@rev.gat,60,184,5	script	教官長イグリド#RZ2	751,{
	mes "[イグリド]";
	mes "死神みてえな顔しやがって！";
	close;
}

1@rev.gat,60,184,5	script	キド#RZ2	884,{
	mes "[キド]";
	mes "目の前の敵に集中しろ。";
	close;
}

1@rev.gat,60,184,5	script	ヒシエ#RZ2	623,{
	mes "[ヒシエ]";
	mes "得体のしれない奴だ。気を付けよう。";
	close;
}

1@rev.gat,64,181,4	script	死神アンク#RZイベント_2	3029,{
	end;
OnStart:
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	announce "死神アンク : また会いましたね。", 0x9, 0x00ebff;
	sleep 3000;
	if('menu == 1) {
		announce "イグリド : モロクはどこだ！", 0x9, 0x00ebff;
		sleep 3000;
	}
	else if('menu == 2) {
		announce "キド : モロクはどこにいる？", 0x9, 0x00ebff;
		sleep 3000;
	}
	else if('menu == 3) {
		announce "ヒシエ : モロクはどこだ？", 0x9, 0x00ebff;
		sleep 3000;
	}
	announce "死神アンク : そんなにモロク様に会いたいですか？　ククク。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : ここはモロク様がご自身の精神で支配されている空間。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : そう、すべてがモロク様の世界です。", 0x9, 0x00ebff;
	sleep 3000;
	if('menu == 1) {
		announce "イグリド : なんだと！", 0x9, 0x00ebff;
		sleep 3000;
	}
	else if('menu == 2) {
		announce "キド : ほう。", 0x9, 0x00ebff;
		sleep 3000;
	}
	else if('menu == 3) {
		announce "ヒシエ : ふむ。", 0x9, 0x00ebff;
		sleep 3000;
	}
	announce "死神アンク : あなた方の思い通りにはいかないでしょう。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : さぁモロク様がお待ちです。モロク様がいる場所まで案内しましょう。", 0x9, 0x00ebff;
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#RZイベント_2");
	sleep 3000;
	hideoffnpc getmdnpcname("#RZ移動_30");
	hideoffnpc getmdnpcname("#RZ移動_31");
	hideoffnpc getmdnpcname("#RZ移動_32");
	end;
}

1@rev.gat,34,126,4	script	死神アンク#RZイベント_3	3029,{
	end;
OnStart:
	hideoffnpc getmdnpcname("死神アンク#RZイベント_3");
	unittalk "死神アンク : ……こんなものですかあなた方の力は？";
	sleep 3000;
	unittalk "死神アンク : 失望しましたよ。モロク様の回復に必要なエネルギー源としては到底力不足ですね。";
	sleep 3000;
	unittalk "死神アンク : ここから立ち去りなさい!!　もうあなた方に興味は無い。";
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#RZイベント_3");
	sleep 5000;
	hideoffnpc getmdnpcname("#RZ移動_5a");
	hideoffnpc getmdnpcname("#RZ移動_6a");
	hideoffnpc getmdnpcname("#RZ移動_7a");
	hideoffnpc getmdnpcname("#RZ移動_8a");
	end;
}

1@rev.gat,34,55,4	script	死神アンク#RZイベント_5	3029,{
	end;
OnStart:
	hideoffnpc getmdnpcname("死神アンク#RZイベント_5");
	unittalk "死神アンク : ……こんなものですかあなた方の力は？";
	sleep 3000;
	unittalk "死神アンク : 失望しましたよ。モロク様の回復に必要なエネルギー源としては到底力不足ですね。";
	sleep 3000;
	unittalk "死神アンク : ここから立ち去りなさい!!　もうあなた方に興味は無い。";
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#RZイベント_5");
	sleep 5000;
	hideoffnpc getmdnpcname("#RZ移動_13a");
	hideoffnpc getmdnpcname("#RZ移動_14a");
	hideoffnpc getmdnpcname("#RZ移動_15a");
	hideoffnpc getmdnpcname("#RZ移動_16a");
	end;
}

1@rev.gat,112,48,4	script	死神アンク#RZイベント_6	3029,{}

1@rev.gat,63,181,0	warp	#RZ移動_30	10,8,1@rev.gat,103,177
1@rev.gat,47,181,0	warp	#RZ移動_31	10,8,1@rev.gat,103,177
1@rev.gat,31,181,0	warp	#RZ移動_32	10,8,1@rev.gat,103,177
1@rev.gat,104,176,0	script	#RZイベント_3	139,1,1,{
OnTouch:
	pcblockmove 1;
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	hideonnpc getmdnpcname("#RZイベント_3");
	if('menu==1)
		hideoffnpc getmdnpcname("教官長イグリド#RZ3");
	else if('menu==2)
		hideoffnpc getmdnpcname("キド#RZ3");
	else if('menu==3)
		hideoffnpc getmdnpcname("ヒシエ#RZ3");
	hideoffnpc getmdnpcname("モロク??#RZ1");
	unittalk getcharid(3),strcharinfo(0)+ " : モロク!?";
	switch('menu) {
	case 0:	set 'unit_id,getcharid(3); set 'unit_name$,strcharinfo(0); break;
	case 1:	set 'unit_id,getnpcid(0,getmdnpcname("教官長イグリド#RZ3"));	set 'unit_name$,"イグリド"; break;
	case 2:	set 'unit_id,getnpcid(0,getmdnpcname("キド#RZ3"));			set 'unit_name$,"キド"; break;
	case 3:	set 'unit_id,getnpcid(0,getmdnpcname("ヒシエ#RZ3"));		set 'unit_name$,"ヒシエ"; break;
	}
	set '@dummy,sleep2(2500);
	unittalk 'unit_id,'unit_name$+ " : おかしい……あれだけ慎重なモロクがこんなにあっさり見つかるとは。";
	set '@dummy,sleep2(3000);
	unittalk 'unit_id,'unit_name$+ " : ……本当にモロクか!?";
	misceffect 60,""; //self
	pcblockmove 0;
	donpcevent getmdnpcname("モロク??#RZ1")+ "::OnStart";
	end;
}

1@rev.gat,102,180,5	script	教官長イグリド#RZ3	751,{
	mes "[イグリド]";
	mes "気を付けろ！";
	mes "あのモロクがこんなにあっさり";
	mes "見つかるとは思えない。";
	close;
}

1@rev.gat,102,180,5	script	キド#RZ3	884,{
	mes "[キド]";
	mes "気を付けろ！";
	mes "あのモロクがこんなにあっさり";
	mes "見つかるとは思えない。";
	close;
}

1@rev.gat,102,180,5	script	ヒシエ#RZ3	623,{
	mes "[ヒシエ]";
	mes "気を付けろ！";
	mes "あのモロクがこんなにあっさり";
	mes "見つかるとは思えない。";
	close;
}

1@rev.gat,111,178,4	script	モロク??#RZ1	1916,{
	end;
OnStart:
	sleep 500;
	unittalk "モロク?? : 良くここまで来たな、人間よ。";
	sleep 3000;
	unittalk "モロク?? : だが、本当に私を阻止できると思っているのか？";
	sleep 3000;
	unittalk "モロク?? : いいだろう。褒美にここまで来た事を後悔させてやろう。";
	sleep 3000;
	unittalk "モロク?? : たとえ完全に力を回復していない私だとしても何の問題もない。";
	misceffect 169, getmdnpcname("モロク??#RZ1");
	sleep 3000;
	unittalk "モロク?? : 死の恐怖を与えてやる!!";
	misceffect 225, getmdnpcname("モロク??#RZ1");
	sleep 3000;
	initnpctimer;
	hideonnpc getmdnpcname("モロク??#RZ1");
	monster getmdmapname("1@rev.gat"),111,178,"モロク??",2998,1,getmdnpcname("モロク??#RZ1")+ "::OnKilled";
	end;
OnTimer2000:
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("モロク??#RZ1")+ "::OnKilled");
	if('@count <= 0) {
		stopnpctimer;
		donpcevent getmdnpcname("モロク??#RZ1")+ "::OnStart2";
	}
	end;
OnTimer4000:
	initnpctimer;
	end;
OnStart2:
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	hideoffnpc getmdnpcname("モロク??#RZ1");
	unittalk "モロク?? : ふむ。回復していない状態ではこの程度の力しか出せぬか。";
	sleep 3000;
	unittalk "モロク?? : まぁいいだろう。もう少し傷を癒すとしよう。";
	sleep 3000;
	unittalk "モロク?? : おい人間共、喜べ。お前らはモロク様を倒したんだ。";
	sleep 3000;
	unittalk "モロク?? : 戻って他の人間共と勝利の喜びでも分かち合ってきたらどうだ？　ククク。";
	hideonnpc getmdnpcname("モロク??#RZ1");
	sleep 3000;
	if('menu==0) {
		announce "逃げた！　追いかけよう!!", 0x9, 0x00ebff;
		sleep 3000;
	}
	else if('menu==1) {
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#RZ3")),"イグリド : あっ！　待て！　逃げやがったな！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#RZ3")),"イグリド : 急いで追いかけるぞ。俺が先に行こう。";
		sleep 3000;
		hideonnpc getmdnpcname("教官長イグリド#RZ3");
		sleep 3000;
		announce "イグリド : ぐ、ぐわぁぁ！　なんだこれは……。", 0x9, 0x00ebff;
		sleep 2000;
	}
	else if('menu==2) {
		unittalk getnpcid(0,getmdnpcname("キド#RZ3")),"キド : ちっ、逃げやがったか。しかし……腑に落ちんな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#RZ3")),"キド : 仕方ない、追いかけよう。先に行く。";
		sleep 3000;
		hideonnpc getmdnpcname("キド#RZ3");
		sleep 3000;
		announce "キド : なんだこれは!!　くっ……！", 0x9, 0x00ebff;
		sleep 2000;
	}
	else if('menu==3) {
		unittalk getnpcid(0,getmdnpcname("ヒシエ#RZ3")),"ヒシエ : 逃げたか……。……罠か？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#RZ3")),"ヒシエ : 追わないわけにもいかないか。よし、私が先に行こう。";
		sleep 3000;
		hideonnpc getmdnpcname("ヒシエ#RZ3");
		sleep 3000;
		announce "ヒシエ : ぐ、ぐわぁぁ！", 0x9, 0x00ebff;
		sleep 2000;
	}
	hideoffnpc getmdnpcname("#RZ移動_1");
	hideoffnpc getmdnpcname("#RZ移動_2");
	hideoffnpc getmdnpcname("#RZ移動_3");
	hideoffnpc getmdnpcname("#RZ移動_4");
	end;
OnKilled:
	end;
}

1@rev.gat,33,120,4	script	教官長イグリド#RZ4	751,{
	mes "[イグリド]";
	mes "くそっ。動けそうにないな……。";
	close;
}

1@rev.gat,33,120,4	script	キド#RZ4	884,{
	mes "[キド]";
	mes "くっ。なんだこれは。";
	mes "全く動けん。";
	close;
}

1@rev.gat,33,120,4	script	ヒシエ#RZ4	623,{
	mes "[ヒシエ]";
	mes "くぅっ。力が入らない……。";
	close;
}

1@rev.gat,33,120,0	script	#停止エフェクトRZ1	139,{
OnStart:
OnTimer10000:
	initnpctimer;
	misceffect 74;
	end;
OnStop:
	stopnpctimer;
	end;
}

/*
1@rev.gat,33,108,0	script	#2部屋目デバフ_1	139,{}
1@rev.gat,33,112,0	script	#2部屋目デバフ_2	139,{}
1@rev.gat,33,116,0	script	#2部屋目デバフ_3	139,{}
1@rev.gat,33,120,0	script	#2部屋目デバフ_4	139,{}
1@rev.gat,33,124,0	script	#2部屋目デバフ_5	139,{}
1@rev.gat,33,128,0	script	#2部屋目デバフ_6	139,{}
1@rev.gat,33,131,0	script	#2部屋目デバフ_7	139,{}
*/

1@rev.gat,34,120,0	script	#魂エフェクト用	139,{}

1@rev.gat,35,119,0	script	#戦闘_1RZ1	139,2,2,{
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	set 'cnt,0;
	hideonnpc getmdnpcname("#戦闘_1RZ1");
	hideonnpc getmdnpcname("#RZ移動_30");
	hideonnpc getmdnpcname("#RZ移動_31");
	hideonnpc getmdnpcname("#RZ移動_32");
	if('menu==0)
		set '@mobname$,strcharinfo(0)+ "の魂";
	else if('menu==1) {
		set '@mobname$,"イグリドの魂";
		set 'name$,getmdnpcname("教官長イグリド#RZ4");
	}
	else if('menu==2) {
		set '@mobname$,"キドの魂";
		set 'name$,getmdnpcname("キド#RZ4");
	}
	else if('menu==3) {
		set '@mobname$,"ヒシエの魂";
		set 'name$,getmdnpcname("ヒシエ#RZ4");
	}
	hideoffnpc 'name$;
	monster getmdmapname("1@rev.gat"),34,120,'@mobname$,3007,1,getmdnpcname("#戦闘_1RZ1")+ "::OnKilled1";
	donpcevent getmdnpcname("#戦闘_1RZ1_timer")+ "::OnStart";
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	initnpctimer;
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_1RZ1")+ "::OnKilled2");
	if('@count == 0) {
		switch('cnt) {
		case 1: setnpctimer 19900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 2: setnpctimer 34900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 3: setnpctimer 49900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 4: setnpctimer 64900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 5: setnpctimer 79900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 6: setnpctimer 94900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 7: setnpctimer 109900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 8: setnpctimer 134900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		case 9: setnpctimer 159900,getmdnpcname("#戦闘_1RZ1_timer"); break;
		}
	}
	end;
OnSpawn:
	set 'cnt,'cnt+1;
	set '@map$,getmdmapname("1@rev.gat");
	set '@label$,getmdnpcname("#戦闘_1RZ1")+ "::OnKilled2";
	monster '@map$,33,128,"モルス・グール",3001,1,'@label$;
	monster '@map$,42,120,"モルス・グール",3001,1,'@label$;
	monster '@map$,34,111,"モルス・グール",3001,1,'@label$;
	monster '@map$,25,119,"モルス・グール",3001,1,'@label$;
	if('cnt == 9)
		monster '@map$,33,111,"モルス・アーチャー",3003,1,'@label$;
	if('cnt == 10)
		monster '@map$,32,128,"モルス・アーチャー",3003,1,'@label$;
	misceffect 124, 'name$;
	misceffect 220, 'name$;
	misceffect 368, 'name$;
	misceffect 9, getmdnpcname("#魂エフェクト用");
	end;
OnKilled1:
OnKilled2:
	end;
}

1@rev.gat,35,119,0	script	#戦闘_1RZ1_timer	139,{
OnStart:
	//hideonnpc getmdnpcname("#戦闘_1RZ1");		//何故か2回hide
	donpcevent getmdnpcname("#RZ_EFFECT01")+ "::OnStart";
	announce "死神アンク : ククク。まんまと引っかかるとは愚かな人たちですね。どうですか魂が肉体と分離される気分は。", 0x9, 0x00ebff;
	sleep 2000;
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	if('menu >= 1)
		donpcevent getmdnpcname("#停止エフェクトRZ1")+ "::OnStart";
	sleep 3000;
	announce "死神アンク : 先ほどのモロク様は私が作り出した幻影です。本当のモロク様は現在休息をとっています。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : しかし……そうまでしてモロク様に会いたいとは。人間であるあなた方がモロク様までたどり着けるとは思いませんが……。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : いいでしょう。あなた方がモロク様に会う資格があるかどうか、私が試して差し上げます。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : あまり私を失望させないでくださいよ？　力不足と判断したらここから立ち去っていただきますので……。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : ここの最深部にたどりつけないような者など、モロク様に会う資格はありません。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : さあ、あなた方の力、見せていただきましょう！　ククク!!", 0x9, 0x00ebff;
	initnpctimer;
	end;
OnTimer4000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnStart";
	end;
OnTimer20000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer35000:
	announce "死神アンク : 私の部下達よ！　もっと恐怖と苦痛を与えるのです！", 0x9, 0x00ebff;
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer50000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer65000:
	announce "死神アンク : まだ足りない……！　もっと恐怖を！　苦痛を！　味わわせるのです!!", 0x9, 0x00ebff;
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer80000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer95000:
	announce "死神アンク : ククク……。いいですよ。もっと抵抗しなさい！", 0x9, 0x00ebff;
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer110000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer135000:
	announce "死神アンク : 私の見込んだ通り、力ある者のようですね。ククク……面白い！", 0x9, 0x00ebff;
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	end;
OnTimer160000:
	donpcevent getmdnpcname("#戦闘_1RZ1")+ "::OnSpawn";
	stopnpctimer getmdnpcname("#戦闘_1RZ1");
	end;
OnTimer175000:
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_1RZ1")+ "::OnKilled2");
	if('@count >= 20) {
		//fail
		stopnpctimer;
		donpcevent getmdnpcname("#RZ_EFFECT01")+ "::OnStop";
		donpcevent getmdnpcname("#停止エフェクトRZ1")+ "::OnStop";
		donpcevent getmdnpcname("死神アンク#RZイベント_3")+ "::OnStart";
	}
	else
		announce "死神アンク : ククク……なかなかしぶといですね！", 0x9, 0x00ebff;
	end;
OnTimer177000:
	announce "死神アンク : だが……いつまで続きますかね。ククク！", 0x9, 0x00ebff;
	end;
OnTimer183000:
	stopnpctimer;
	donpcevent getmdnpcname("#RZ_EFFECT01")+ "::OnStop";
	donpcevent getmdnpcname("#停止エフェクトRZ1")+ "::OnStop";
	hideonnpc getmdnpcname("#2部屋目デバフ_1");
	hideonnpc getmdnpcname("#2部屋目デバフ_2");
	hideonnpc getmdnpcname("#2部屋目デバフ_3");
	hideonnpc getmdnpcname("#2部屋目デバフ_4");
	hideonnpc getmdnpcname("#2部屋目デバフ_5");
	hideonnpc getmdnpcname("#2部屋目デバフ_6");
	hideonnpc getmdnpcname("#2部屋目デバフ_7");
	hideoffnpc getmdnpcname("#RZ移動_5");
	hideoffnpc getmdnpcname("#RZ移動_6");
	hideoffnpc getmdnpcname("#RZ移動_7");
	hideoffnpc getmdnpcname("#RZ移動_8");
	end;
}

1@rev.gat,34,47,0	script	#戦闘_2RZ1	139,10,10,{
	set 'cnt,0;
	hideonnpc getmdnpcname("#戦闘_2RZ1");
	donpcevent getmdnpcname("#戦闘_2RZ1_timer")+ "::OnStart";
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	initnpctimer;
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_2RZ1")+ "::OnKilled");
	if('@count == 0) {
		switch('cnt) {
		case 1: setnpctimer 29900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 2: setnpctimer 54900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 3: setnpctimer 79900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 4: setnpctimer 104900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 5: setnpctimer 129900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 6: setnpctimer 154900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		case 7: setnpctimer 169900,getmdnpcname("#戦闘_2RZ1_timer"); break;
		}
	}
	end;
OnSpawn:
	set 'cnt,'cnt+1;
	set '@map$,getmdmapname("1@rev.gat");
	set '@label$,getmdnpcname("#戦闘_2RZ1")+ "::OnKilled";
	monster '@map$,34,57,"モルス・グール",3001,1,'@label$;
	monster '@map$,43,48,"モルス・グール",3001,1,'@label$;
	monster '@map$,33,38,"モルス・グール",3001,1,'@label$;
	monster '@map$,24,48,"モルス・グール",3001,1,'@label$;
	if('cnt == 1 || 'cnt == 7) {
		monster '@map$,27,53,"モルス・アーチャー",3003,1,'@label$;
		monster '@map$,27,41,"モルス・アーチャー",3003,1,'@label$;
	}
	else {
		monster '@map$,40,41,"モルス・アーチャー",3003,1,'@label$;
		monster '@map$,40,54,"モルス・アーチャー",3003,1,'@label$;
	}
	if('cnt >= 3 && 'cnt < 7)
		monster '@map$,27,53,"モルス・ベリット",3005,1,'@label$;
	if('cnt == 7) {
		monster '@map$,40,41,"モルス・ベリット",3005,1,'@label$;
		monster '@map$,40,54,"モルス・ベリット",3005,1,'@label$;
	}
	if('cnt == 8) {
		monster '@map$,27,53,"モルス・ベリット",3005,1,'@label$;
		monster '@map$,27,41,"モルス・ベリット",3005,1,'@label$;
	}
	end;
OnKilled:
	end;
}

1@rev.gat,34,47,0	script	#戦闘_2RZ1_timer	139,{
OnStart:
	donpcevent getmdnpcname("#RZ_EFFECT02")+ "::OnStart";
	announce "死神アンク : 私の部下を倒して解放されたと思っているようですが、この空間はモロク様の意思により進化しています。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : 並大抵の実力では抜け出せませんよ？　ククク。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : しかし……お強い。やはりあなた方の魂はモロク様の回復に役立ちそうですね。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : その魂と苦痛を生贄にして差し上げましょう。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : あなた方の魂はモロク様の血となり肉となるのです。これは光栄な事ですよ！　ククク!!", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : さあ、行きなさい私の部下達よ!!　あの者たちの肉体と魂を引き裂き、モロク様に捧げるのです！", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : もちろん、先ほどと同様、力不足と判断したらここから立ち去っていただきますがね……。", 0x9, 0x00ebff;
	sleep 5000;
	announce "死神アンク : ククク……さぁ存分にその力を発揮してください！　モロク様のために!!", 0x9, 0x00ebff;
	initnpctimer;
	end;
OnTimer4000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnStart";
	end;
OnTimer30000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	announce "死神アンク : この心地よい感覚。……素晴らしい!!", 0x9, 0x00ebff;
	end;
OnTimer55000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	announce "死神アンク : モロク様に貢献出来る事、光栄に思いなさい！", 0x9, 0x00ebff;
	end;
OnTimer80000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	announce "死神アンク : もっとです！もっと力を!!", 0x9, 0x00ebff;
	end;
OnTimer105000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	announce "死神アンク : いいですよ。クック。もっと足掻きなさい……！", 0x9, 0x00ebff;
	end;
OnTimer130000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	end;
OnTimer155000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	announce "死神アンク : 死への恐怖や苦悩がモロク様の力になるのです！", 0x9, 0x00ebff;
	end;
OnTimer170000:
	donpcevent getmdnpcname("#戦闘_2RZ1")+ "::OnSpawn";
	stopnpctimer getmdnpcname("#戦闘_2RZ1");
	end;
OnTimer180000:
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_2RZ1")+ "::OnKilled");
	if('@count >= 20) {
		//fail
		stopnpctimer;
		donpcevent getmdnpcname("#RZ_EFFECT02")+ "::OnStop";
		donpcevent getmdnpcname("死神アンク#RZイベント_5")+ "::OnStart";
	}
	else
		announce "死神アンク : ほほう……ここまで耐えますか！　しかし、その生への執着、そして死への恐怖でエネルギーは充分蓄えられました！", 0x9, 0x00ebff;
	end;

OnTimer187000:
	announce "死神アンク : モロク様もお喜びになる！　素晴らしい……！", 0x9, 0x00ebff;
	end;
OnTimer190000:
	stopnpctimer;
	donpcevent getmdnpcname("#RZ_EFFECT02")+ "::OnStop";
	hideoffnpc getmdnpcname("#RZ移動_13");
	hideoffnpc getmdnpcname("#RZ移動_14");
	hideoffnpc getmdnpcname("#RZ移動_15");
	hideoffnpc getmdnpcname("#RZ移動_16");
	end;
}

1@rev.gat,112,48,4	script	モルス・魔導士#RZ1	10029,{
	end;
OnStart:
	sleep 3000;
	hideoffnpc getmdnpcname("死神アンク#RZイベント_6");
	unittalk getnpcid(0,getmdnpcname("死神アンク#RZイベント_6")),"死神アンク : これはこれは……。私が戻ってくる前に倒してしまうとは。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#RZイベント_6")),"死神アンク : まぁいいでしょう。あなた方のエネルギーはモロク様にきちんとお渡ししました。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#RZイベント_6")),"死神アンク : もうすぐモロク様が完全に回復されます！　そうなればあなた方の命もそこまでです！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#RZイベント_6")),"死神アンク : またお会いしましょう。その時あなた方は死体でしょうけどね。ククククク。";
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#RZイベント_6");
	hideoffnpc getmdnpcname("#RZ移動_17a");
	misceffect 30,getmdnpcname("モルス・魔導士#RZ1");
	sleep 1000;
	misceffect 90,getmdnpcname("モルス・魔導士#RZ1");
	end;
}

1@rev.gat,104,47,0	script	#戦闘_3RZ1	139,5,5,{
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	hideonnpc getmdnpcname("#戦闘_3RZ1");
	if('menu==0)
		set '@mobname$,strcharinfo(0)+ "の魂";
	else if('menu==1)
		set '@mobname$,"イグリドの魂";
	else if('menu==2)
		set '@mobname$,"キドの魂";
	else if('menu==3)
		set '@mobname$,"ヒシエの魂";
	hideoffnpc 'name$;
	monster getmdmapname("1@rev.gat"),112,48,'@mobname$,3007,1,getmdnpcname("#戦闘_3RZ1")+ "::OnKilled1";
	announce "死神アンク : 助かりましたよ皆さん。おかげでモロク様の回復に充分なエネルギーが溜まりました。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : 私はモロク様にこのエネルギーを献上して来るとしましょう。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : さて……後は片付けが必要ですね……ふむ。いいことを思いつきましたよ。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : この余ったエネルギーに私の力でも籠めるとしましょう。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : 皆さん、エネルギーを少しでも取り戻したければ全力で戦う事です。ククク。", 0x9, 0x00ebff;
	sleep 3000;
	announce "死神アンク : さぁ立ち上がれ魔導士よ！　この者達に本当の恐怖を教えてやりなさい！", 0x9, 0x00ebff;
	sleep 3000;
	hideoffnpc getmdnpcname("モルス・魔導士#RZ1");
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ1")+ "::OnKilled1";
	sleep 3000;
	misceffect 130,getmdnpcname("モルス・魔導士#RZ1");
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : 分かりました、アンク様!!";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : キキキ……お前らの魂に宿るエネルギーはモロク様の回復に利用されるのだ！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : しかもアンク様は、余ったエネルギーでこうして私まで生み出してくださった！　キキキ！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : 愚かな冒険者よ、もうお前らに用はない！　私がこの力で葬り去ってやろう!!";
	misceffect 54,getmdnpcname("モルス・魔導士#RZ1");
	sleep 3000;
	hideonnpc getmdnpcname("モルス・魔導士#RZ1");
	monster getmdmapname("1@rev.gat"),112,48,"モルス・魔導士",2999,1,getmdnpcname("#戦闘_3RZ1")+ "::OnKilled2";
	initnpctimer;
	end;
OnKilled1:
OnKilled2:
	end;
OnTimer2000:
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ1")+ "::OnKilled2");
	if('@count <= 0) {
		stopnpctimer;
		donpcevent getmdnpcname("#戦闘_3RZ2")+ "::OnStart";
	}
	end;
OnTimer4000:
	initnpctimer;
	end;
}

1@rev.gat,108,51,5	script	教官長イグリド#RZ5	751,{
	mes "[イグリド]";
	mes "はぁ……はぁ……";
	mes "モロクを……モロクはどこだ……。";
	close;
}

1@rev.gat,108,51,5	script	キド#RZ5	884,{
	mes "[キド]";
	mes "モロクを……";
	mes "くそっ……";
	mes "傷が深い。";
	close;
}

1@rev.gat,108,51,5	script	ヒシエ#RZ5	623,{
	mes "[ヒシエ]";
	mes "ふぅ……少し……";
	mes "傷が深いな……。";
	close;
}

1@rev.gat,106,60,0	script	#戦闘_3RZ2	139,{
OnStart:
	hideoffnpc getmdnpcname("モルス・魔導士#RZ1");
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : キキ。ちょっとはできるようだな。それでこそモロク様の生贄にふさわしい。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : しかしそろそろ終わりだ！　……私の本当の力をみせてやろう！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : お前らの命は、この私の手中にあるということを思い知るがいい!!";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : キキキ！";
	sleep 3000;
	set 'menu,getvariableofnpc('menu, getmdnpcname("#RZイベント_1-2"));
	if('menu >= 1) {
		announce "待て!!!", 0x9, 0x00ebff;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : なにっ!?";
		if('menu==1) {
			hideoffnpc getmdnpcname("教官長イグリド#RZ5");
			unittalk getnpcid(0,getmdnpcname("教官長イグリド#RZ5")),"イグリド : モロクはどこだっ!!!";
		}
		else if('menu==2) {
			hideoffnpc getmdnpcname("キド#RZ5");
			unittalk getnpcid(0,getmdnpcname("キド#RZ5")),"キド : モロクッ!!　モロクはどこだッ！";
		}
		else if('menu==3) {
			hideoffnpc getmdnpcname("ヒシエ#RZ5");
			unittalk getnpcid(0,getmdnpcname("ヒシエ#RZ5")),"ヒシエ : モロクはどこだっ！";
		}
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : ほう、まだ生きていたのか。しぶといな。キキキ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : 安心しろ。モロク様はお前らのおかげで順調に回復しているよ。キキキキキ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : 後はゆっくり私が相手してやるから安心して死ぬがよい！";
		sleep 3000;
		if('menu==1) {
			unittalk getnpcid(0,getmdnpcname("教官長イグリド#RZ5")),"イグリド : ふざけやがって!!　うぉぉぉぉぉ！";
			misceffect 12,getmdnpcname("教官長イグリド#RZ5");
			sleep 1500;
			misceffect 245,getmdnpcname("モルス・魔導士#RZ1");
			sleep 1500;
			unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : ぐっ！　ぐはっ！";
		}
		else if('menu==2) {
			unittalk getnpcid(0,getmdnpcname("キド#RZ5")),"キド : くっ！　ここまでか……。うぉぉぉぉぉぉ!!";
			misceffect 12,getmdnpcname("キド#RZ5");
			sleep 1500;
			misceffect 129,getmdnpcname("モルス・魔導士#RZ1");
			sleep 1500;
			unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : ぐはぁぁ！";
		}
		else if('menu==3) {
			unittalk getnpcid(0,getmdnpcname("ヒシエ#RZ5")),"ヒシエ : くっ……。せめて……!!　うおぉぉぉ!!";
			misceffect 12,getmdnpcname("ヒシエ#RZ5");
			sleep 1500;
			misceffect 30,getmdnpcname("モルス・魔導士#RZ1");
			sleep 1500;
			unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : ぐっはぁぁ！";
		}
		sleep 1500;
		announce "‐敵のHpが減少した‐", 0x9, 0x00ebff;
		sleep 3000;
		if('menu==1) {
			unittalk getnpcid(0,getmdnpcname("教官長イグリド#RZ5")),"イグリド : くぅっ……！　後は……頼む！";
			hideonnpc getmdnpcname("教官長イグリド#RZ5");
		}
		else if('menu==2) {
			unittalk getnpcid(0,getmdnpcname("キド#RZ5")),"キド : ぐはっ！　後は頼むぞ!!";
			hideonnpc getmdnpcname("キド#RZ5");
		}
		else if('menu==3) {
			unittalk getnpcid(0,getmdnpcname("ヒシエ#RZ5")),"ヒシエ : 後は……頼む……！";
			hideonnpc getmdnpcname("ヒシエ#RZ5");
		}
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : キキキ……！　力尽きて気を失ったか。愚かな奴め。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・魔導士 : お前らを始末したら、あいつもゆっくりいたぶって始末してやろう。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・ネクロマンサー : まずはお前らからだ……。さあ、私の真の姿を見て怯えろ！";
	}
	else {
		unittalk getnpcid(0,getmdnpcname("モルス・魔導士#RZ1")),"モルス・ネクロマンサー : さあ、私の真の姿を見て怯えろ！";
	}
	hideonnpc getmdnpcname("モルス・魔導士#RZ1");
	set 'mob_id,callmonster(getmdmapname("1@rev.gat"),112,48,"モルス・ネクロマンサー",3000,getmdnpcname("#戦闘_3RZ2")+ "::OnKilled");
	if('menu >= 1) {
		set '@mobhp,getmobhp('mob_id);
		set '@mobhp,'@mobhp - ('@mobhp * 20 / 100);
		setmobhp 'mob_id,'@mobhp;
	}
	donpcevent getmdnpcname("#戦闘_3RZ3")+ "::OnStart";
	initnpctimer;
	set 'cnt,0;
	end;
OnTimer1000:
	set 'cnt,'cnt+1;
	set '@count,getmapmobs(getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ2")+ "::OnKilled");
	if('@count <= 0) {
		stopnpctimer;
		set getvariableofnpc('users,getmdnpcname("#RZ移動_17a")),getmapusers(getmdmapname("1@rev.gat"));
		donpcevent getmdnpcname("#戦闘_3RZ3")+ "::OnStop";
		donpcevent getmdnpcname("モルス・魔導士#RZ1")+ "::OnStart";
		donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStop";
		donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStop";
		donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStop";
		donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStop";
		end;
	}
	else if('cnt == 150) {
		set getvariableofnpc('flag, getmdnpcname("#戦闘_3RZ3")),1;
		set 'cnt,0;
	}
	initnpctimer;
	end;
OnKilled:
	end;
}

1@rev.gat,120,60,0	script	#戦闘_3RZ3	139,{
OnStart:
	set 'flag,0;
	initnpctimer;
	end;
OnTimer7000:
	set '@map$,getmdmapname("1@rev.gat");
	set '@label$,getmdnpcname("#戦闘_3RZ3")+ "::OnKilled";
	donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStop";
	donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStop";
	donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStop";
	donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStop";
	set '@mob_id,getvariableofnpc('mob_id, getmdnpcname("#戦闘_3RZ2"));
	set '@count,getmapmobs('@map$,'@label$);
	if('flag) {
		unittalk '@mob_id,"モルス・ネクロマンサー : さあ、永遠の眠りにつくがいい!!";
	}
	else if('@count < 10) {
		set '@r,rand(1,100);
		if(('@r < 11) && ('@r > 0)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らはここで朽ちるのだ！";
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
		}
		else if(('@r < 21) && ('@r > 10)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : どんなに望んでも未来などないぞ！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStart";
		}
		else if(('@r < 31) && ('@r > 20)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らはここで朽ちるのだ！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
		}
		else if(('@r < 41) && ('@r > 30)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : そしてモロク様の望んだ世界の糧となれ！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
		}
		else if(('@r < 51) && ('@r > 40)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : そしてモロク様の望んだ世界の糧となれ！";
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
		}
		else if(('@r < 61) && ('@r > 50)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らはここで朽ちるのだ！";
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,40,"モルス・ベリット",3005,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
		}
		else if(('@r < 71) && ('@r > 60)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : どんなに望んでも未来などないぞ！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,40,"モルス・ベリット",3005,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStart";
		}
		else if(('@r < 81) && ('@r > 70)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : さあ苦しめ！　足掻け！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,119,40,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,104,40,"モルス・ベリット",3005,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
		}
		else if(('@r < 91) && ('@r > 80)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : さあ苦しめ！　足掻け！";
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
		}
		else if(('@r < 101) && ('@r > 90)) {
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らはここで朽ちるのだ！";
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
		}
		else {
			unittalk '@mob_id,"モルス・ネクロマンサー : さあ苦しめ！　足掻け！";
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
		}
	}
	else if('@count < 15) {
		set '@r,rand(1,60);
		if(('@r < 11) && ('@r > 0)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : モロク様の血肉となれることを光栄に思え！";
		}
		else if(('@r < 21) && ('@r > 10)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,119,40,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らはモロク様の忠実なしもべ！";
		}
		else if(('@r < 31) && ('@r > 20)) {
			monster '@map$,112,38,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・アーチャー",3003,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ4")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : モロク様のため、この者達に永遠の眠りを！";
		}
		else if(('@r < 41) && ('@r > 30)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らの力に恐怖するがいい！";
		}
		else if(('@r < 51) && ('@r > 40)) {
			monster '@map$,112,57,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,119,40,"モルス・アーチャー",3003,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ5")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らの力に恐怖するがいい！";
		}
		else if(('@r < 61) && ('@r > 50)) {
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・アーチャー",3003,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : モロク様のため、この者達に永遠の眠りを！";
		}
		else {
			monster '@map$,121,47,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,119,40,"モルス・ベリット",3005,1,'@label$;
			monster '@map$,104,40,"モルス・アーチャー",3003,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らの力に恐怖するがいい！";
		}
	}
	else if('@count < 20) {
		set '@r,rand(1,40);
		if(('@r < 11) && ('@r > 0)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,120,54,"モルス・ルード",3006,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ6")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : ここから生きて帰る事はできない！";
		}
		else if(('@r < 21) && ('@r > 10)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,119,40,"モルス・ルード",3006,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : ここから生きて帰る事はできない！";
		}
		else if(('@r < 31) && ('@r > 20)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,104,40,"モルス・ルード",3006,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			//cmdothernpc g_event_9 "talk_19"
		}
		else if(('@r < 41) && ('@r > 30)) {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,104,54,"モルス・ルード",3006,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らの力なぞ、我らの前では無意味だったということを思い知ったか！";
		}
		else {
			monster '@map$,102,48,"モルス・グール",3001,1,'@label$;
			monster '@map$,104,40,"モルス・ルード",3006,1,'@label$;
			donpcevent getmdnpcname("#戦闘_3RZ7")+ "::OnStart";
			unittalk '@mob_id,"モルス・ネクロマンサー : お前らの力なぞ、我らの前では無意味だったということを思い知ったか！";
		}
	}
	else if('@count < 40) {
		set '@r,rand(1,100);
		if(('@r < 11) && ('@r > 0)) {
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			//cmdothernpc g_event_9 "talk_21"
		}
		else if(('@r < 21) && ('@r > 10)) {
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			unittalk '@mob_id,"モルス・ネクロマンサー : ここまで耐えた事は褒めてやるぞ！";
		}
		else if(('@r < 31) && ('@r > 20)) {
			monster '@map$,120,54,"モルス・レイス",3004,1,'@label$;
			monster '@map$,119,40,"モルス・レイス",3004,1,'@label$;
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らにさえ対抗できない者が、モロク様に刃をむけるとは笑止！";
		}
		else if(('@r < 41) && ('@r > 30)) {
			monster '@map$,119,40,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			unittalk '@mob_id,"モルス・ネクロマンサー : しかしもうお前らも終わりだ。楽にしてやろう！";
		}
		else if(('@r < 61) && ('@r > 50)) {
			monster '@map$,119,40,"モルス・ルード",3006,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,54,"モルス・レイス",3004,1,'@label$;
			unittalk '@mob_id,"モルス・ネクロマンサー : 我らにさえ対抗できない者が、モロク様に刃をむけるとは笑止！";
		}
		else {
			monster '@map$,119,40,"モルス・ルード",3006,1,'@label$;
			monster '@map$,104,40,"モルス・レイス",3004,1,'@label$;
			monster '@map$,104,54,"モルス・レイス",3004,1,'@label$;
			unittalk '@mob_id,"モルス・ネクロマンサー : ここまで耐えた事は褒めてやるぞ！";
		}
	}
	else {
		unittalk '@mob_id,"モルス・ネクロマンサー : さあ、永遠の眠りにつくがいい!!";
	}
	end;
OnTimer25000:
	initnpctimer;
	end;
OnKilled:
	end;
OnStop:
	stopnpctimer;
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ3")+ "::OnKilled";
	end;
}

1@rev.gat,120,61,0	script	#戦闘_3RZ4	139,{
OnStart:
	set 'mob,callmonster(getmdmapname("1@rev.gat"),112,57,"モルス・オシリス#1",3002,getmdnpcname("#戦闘_3RZ4")+ "::OnKilled");
	initnpctimer;
	end;
OnTimer4500:
	if(getmobhp('mob) > 0) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		monster getmdmapname("1@rev.gat"),'@x,'@y,"モルス・プランクトン#1",3008,1,getmdnpcname("#戦闘_3RZ4")+ "::OnKilled";
	}
	initnpctimer;
	end;
OnKilled:
	end;
OnStop:
	stopnpctimer;
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ4")+ "::OnKilled";
	end;
}

1@rev.gat,120,62,0	script	#戦闘_3RZ5	139,{
OnStart:
	set 'mob,callmonster(getmdmapname("1@rev.gat"),121,47,"モルス・オシリス#2",3002,getmdnpcname("#戦闘_3RZ5")+ "::OnKilled");
	initnpctimer;
	end;
OnTimer4500:
	if(getmobhp('mob) > 0) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		monster getmdmapname("1@rev.gat"),'@x,'@y,"モルス・プランクトン#2",3008,1,getmdnpcname("#戦闘_3RZ5")+ "::OnKilled";
	}
	initnpctimer;
	end;
OnKilled:
	end;
OnStop:
	stopnpctimer;
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ5")+ "::OnKilled";
	end;
}

1@rev.gat,120,63,0	script	#戦闘_3RZ6	139,{
OnStart:
	set 'mob,callmonster(getmdmapname("1@rev.gat"),112,38,"モルス・オシリス#3",3002,getmdnpcname("#戦闘_3RZ6")+ "::OnKilled");
	initnpctimer;
	end;
OnTimer4500:
	if(getmobhp('mob) > 0) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		monster getmdmapname("1@rev.gat"),'@x,'@y,"モルス・プランクトン#3",3008,1,getmdnpcname("#戦闘_3RZ6")+ "::OnKilled";
	}
	initnpctimer;
	end;
OnKilled:
	end;
OnStop:
	stopnpctimer;
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ6")+ "::OnKilled";
	end;
}

1@rev.gat,120,58,0	script	#戦闘_3RZ7	139,{
OnStart:
	set 'mob,callmonster(getmdmapname("1@rev.gat"),102,48,"モルス・オシリス#4",3002,getmdnpcname("#戦闘_3RZ7")+ "::OnKilled");
	initnpctimer;
	end;
OnTimer4500:
	if(getmobhp('mob) > 0) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		monster getmdmapname("1@rev.gat"),'@x,'@y,"モルス・プランクトン#4",3008,1,getmdnpcname("#戦闘_3RZ7")+ "::OnKilled";
	}
	initnpctimer;
	end;
OnKilled:
	end;
OnStop:
	stopnpctimer;
	killmonster getmdmapname("1@rev.gat"),getmdnpcname("#戦闘_3RZ7")+ "::OnKilled";
	end;
}

1@rev.gat,106,183,0	warp	#RZ移動_1	10,10,1@rev.gat,33,117
1@rev.gat,106,172,0	warp	#RZ移動_2	10,10,1@rev.gat,33,117
1@rev.gat,117,172,0	warp	#RZ移動_3	10,10,1@rev.gat,33,117
1@rev.gat,117,183,0	warp	#RZ移動_4	10,10,1@rev.gat,33,117
1@rev.gat,28,125,0	warp	#RZ移動_5	10,10,1@rev.gat,31,50
1@rev.gat,28,114,0	warp	#RZ移動_6	10,10,1@rev.gat,31,50
1@rev.gat,39,114,0	warp	#RZ移動_7	10,10,1@rev.gat,31,50
1@rev.gat,39,125,0	warp	#RZ移動_8	10,10,1@rev.gat,31,50
1@rev.gat,28,125,0	warp	#RZ移動_5a	10,10,moro_cav.gat,59,63
1@rev.gat,28,114,0	warp	#RZ移動_6a	10,10,moro_cav.gat,59,63
1@rev.gat,39,114,0	warp	#RZ移動_7a	10,10,moro_cav.gat,59,63
1@rev.gat,39,125,0	warp	#RZ移動_8a	10,10,moro_cav.gat,59,63

1@rev.gat,28,53,0	warp	#RZ移動_13a	10,10,moro_cav.gat,59,63
1@rev.gat,28,42,0	warp	#RZ移動_14a	10,10,moro_cav.gat,59,63
1@rev.gat,39,42,0	warp	#RZ移動_15a	10,10,moro_cav.gat,59,63
1@rev.gat,39,53,0	warp	#RZ移動_16a	10,10,moro_cav.gat,59,63
1@rev.gat,28,53,0	warp	#RZ移動_13	10,10,1@rev.gat,104,48
1@rev.gat,28,42,0	warp	#RZ移動_14	10,10,1@rev.gat,104,48
1@rev.gat,39,42,0	warp	#RZ移動_15	10,10,1@rev.gat,104,48
1@rev.gat,39,53,0	warp	#RZ移動_16	10,10,1@rev.gat,104,48

1@rev.gat,112,56,3	script	#RZ移動_17a	723,{
	mes "‐^ff0000ここから退出する事で";
	mes "　報酬を受け取る事が出来ます。^000000";
	mes "　外に出ますか？‐";
	next;
	if(select("いいえ","はい") == 1) {
		mes "‐あなたはその場を離れた‐";
		close;
	}
	mes "‐あなたは外に出た‐";
	close2;
	if(checkitemblank() == 0) {
		mes "‐アイテムの種類数が多くて";
		mes "　持つことができない。";
		mes "　種類数を減らしてから受け取ろう‐";
		close;
	}
	if(checkquest(9318) & 0x4) {
		compquest 9318;
		if(BaseLevel < 160) {
			set '@base,9500000 + 500000 * 'users;
			if('users >= 12) set '@base,'@base + 500000;
		}
		else {
			set '@base,28000000 + 2000000 * 'users;
			if('users >= 12) set '@base,'@base + 2000000;
		}
		set '@job,3800000 + 200000 * 'users;
		if('users >= 12) set '@job,'@job + 200000;
		while('@base > 0) {
			if('@base >= 10000000) {
				getexp 10000000,0,1;
				set '@base,'@base - 10000000;
			}
			else {
				getexp '@base,0,1;
				set '@base,0;
			}
		}
		getexp 0,'@job,0;
	}
	if(checkquest(116514)==0) {
		setquest 116514;
		compquest 116514;
	}
	if(checkquest(9318) & 0x8)
		getitem 6684,1;
	if(checkquest(201725)==0)
		setquest 201725;
	if(MORS_1QUE==0)
		set MORS_1QUE,'users;
	warp "moro_cav.gat",59,63;
	end;
}
