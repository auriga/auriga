//= Auriga Script ==============================================================
// Ragnarok Online Orc's Memory Script	by Blaze
//- Registry -------------------------------------------------------------------
// ORCS_1QUE -> 0～3
//==============================================================================

//============================================================
// クエストNPC
//------------------------------------------------------------
gef_fild10.gat,238,202,6	script	謎の研究者	865,{
	if(Job == Job_Summoner || Job == Job_SpiritHandler) {
		mes "[謎の研究者]";
		mes "お前、^ff0000ドラム^000000だな。";
		mes "人間以外が触ると";
		mes "妙な現象が発生しかねん。";
		mes "あっちへ行け！";
		close;
	}
	switch(ORCS_1QUE) {
	case 0:
		mes "[謎の研究者]";
		mes "クック……！";
		mes "ハァーッハッハ!!";
		mes "オークどもめ、私に指一本";
		mes "触れられないようだな……！";
		mes "やはり^0000ff狭間の石^000000の力は素晴らしい……！";
		next;
		if(select("オークが触れられない？","（なんだこの人……）") == 2) {
			mes "[謎の研究者]";
			mes "なんだ、お前は？";
			mes "そんな目で私を見るな！";
			mes "あっち行け！";
			mes "シッシッ!!";
			close;
		}
		mes "[謎の研究者]";
		mes "んんんんんー？";
		mes "なんだ、興味があるのか？";
		next;
		mes "[謎の研究者]";
		mes "ククク……信じがたい事実だが……";
		mes "私がモロクの調査をしていた時、";
		mes "次元の狭間でとある鉱石が見つかった。";
		mes "そしてこの鉱石には";
		mes "凄まじい力が秘められていることが";
		mes "わかったのだ！";
		next;
		menu "次元の狭間で……？",-;
		mes "[謎の研究者]";
		mes "そう、次元の狭間で見つかった鉱石";
		mes "時や空間を超越した場所に";
		mes "影響を与える……？";
		mes "もしくは影響を受けたのか……？";
		mes "詳しくはわからんが、とにかく";
		mes "この石の力は次元を超えるのだ！";
		next;
		mes "[謎の研究者]";
		mes "私はついさっき、それで";
		mes "時間旅行じみたことを経験した。";
		mes "そこにある石像がわかるか？";
		mes "こいつには現代科学の髄と";
		mes "次元の狭間の鉱石が持つ力を";
		mes "高レベルで融合させてある……";
		next;
		mes "[謎の研究者]";
		mes "どうだ、お前も";
		mes "時間旅行をしてみないか？";
		next;
		menu "これって不正な実験ですよね？",-;
		mes "[謎の研究者]";
		mes "もちろん不正だ！";
		next;
		mes "[謎の研究者]";
		mes "だがそれが何だ？";
		mes "これほどまでに研究者という生き物を";
		mes "奮い立たせる素材が目の前にある！";
		mes "それを！　本能的に！";
		mes "研究することは間違っていない！";
		next;
		mes "[謎の研究者]";
		mes "クックック、 まあやってみろ！";
		mes "面白いぞ！";
		mes "オークどもと話が出来るぞ、ハハハ！";
		next;
		if(BaseLevel < 30) {
			mes "[謎の研究者]";
			mes "……と思ったが……";
			mes "お前、^ff0000レベルが30未満^000000だな。";
			mes "そんなんじゃ次元を超える力に";
			mes "耐えられん。";
			mes "いくら私でも失敗することが";
			mes "わかっていることを薦める暇はない！";
			close;
		}
		if(BaseLevel > 80) {
			mes "[謎の研究者]";
			mes "……と思ったが……";
			mes "お前、^ff0000レベルが81以上^000000だな。";
			mes "あんまりお前の力が強すぎると";
			mes "妙な現象が発生しかねん。";
			mes "さすがにそいつはまずいからな。";
			mes "あきらめろ！";
			close;
		}
		if(select("じゃあ、してみます","……こういうのは苦手です") == 2) {
			mes "[謎の研究者]";
			mes "つまらん！";
			mes "お前は本当につまらん！";
			close;
		}
		mes "[謎の研究者]";
		mes "物分りがいいじゃないか！";
		mes "さあ、そこの石像に触れるがいい。";
		mes "オークどもの過去の劇を";
		mes "堪能するがいい！";
		mes "ククク！";
		set ORCS_1QUE, 1;
		close;
	case 1:
		mes "[謎の研究者]";
		mes "ん？　なんだ？";
		mes "時間旅行をしてみたければ";
		mes "そこの石像に触れるがいい。";
		mes "オークどもの過去の劇を";
		mes "堪能できるぞ！";
		mes "ククク！";
		next;
		if (select("わかりました","もう一度説明してください") == 1) {
			mes "[謎の研究者]";
			mes "物分りがいいじゃないか！";
			mes "ククク！";
			close;
		}
		mes "[謎の研究者]";
		mes "はああああー？";
		mes "めんどくさい奴だな！";
		next;
		mes "[謎の研究者]";
		mes "いいか……信じがたい事実だが……";
		mes "私がモロクの調査をしていた時、";
		mes "次元の狭間でとある鉱石が見つかった。";
		mes "そしてこの鉱石には";
		mes "凄まじい力が秘められていることが";
		mes "わかったのだ！";
		next;
		mes "[謎の研究者]";
		mes "次元の狭間で見つかった鉱石……";
		mes "時や空間を超越した場所に";
		mes "影響を与える……？";
		mes "もしくは影響を受けたのか……？";
		mes "詳しくはわからんが、とにかく";
		mes "この石の力は次元を超えるのだ！";
		next;
		mes "[謎の研究者]";
		mes "私はついさっき、それで";
		mes "時間旅行じみたことを経験した。";
		mes "そこにある石像がわかるか？";
		mes "こいつには現代科学の髄と";
		mes "次元の狭間の鉱石が持つ力を";
		mes "高レベルで融合させてある……";
		next;
		mes "[謎の研究者]";
		mes "そいつを使えばお前も";
		mes "時間旅行が出来るというわけだ。";
		next;
		mes "[謎の研究者]";
		mes "ただし！";
		mes "時間旅行が出来るのは";
		mes "レベル30～80までの人間に限る！";
		mes "弱すぎたら次元を超える力に";
		mes "耐えられないし、";
		mes "強すぎても変な現象が起きかねん。";
		next;
		mes "[謎の研究者]";
		mes "それだけ繊細ってことだ";
		mes "説明は以上だ！";
		mes "満足したか？";
		close;
	case 2:
		mes "[謎の研究者]";
		mes "おお、どうだった？";
		mes "時間旅行は楽しかったか？";
		mes "同じ時間にしか行けないからな、";
		mes "私が見てきたものと同じ展開を";
		mes "見てきたんだろう。";
		mes "オークどもの妙な演劇をな。";
		next;
		menu "……過去にいったい何が？",-;
		mes "[謎の研究者]";
		mes "さあな、それは私に聞かれても困る。";
		mes "少なくとも……";
		mes "過去にオークの巫女とかいうのとの";
		mes "大規模な戦闘があった……";
		mes "ということだな。";
		next;
		mes "[謎の研究者]";
		mes "勝手に突っ込んでいって";
		mes "倒れたオークの娘が巫女……？";
		mes "まあ経緯はわからんが。";
		mes "研究の価値はありそうだな……";
		mes "ククク……！";
		next;
		menu "……………",-;
		mes "[謎の研究者]";
		mes "何度でも見に行けるぞ。";
		mes "過去に起きたことだからな。";
		mes "ありがちな戦争劇……";
		mes "何度も見る価値があるかは";
		mes "知らないがね……ククク。";
		close;
	case 3:
		mes "[謎の研究者]";
		mes "おお、どうだった？";
		mes "時間旅行は楽しかったか？";
		mes "同じ時間にしか行けないからな、";
		mes "私が見てきたものと同じ展開を";
		mes "見てきたんだろう。";
		mes "オークどもの妙な演劇をな。";
		next;
		menu "……若干反応が変わりましたよ",-;
		mes "[謎の研究者]";
		mes "ほう？　まあ多少は変わるだろうな。";
		mes "だが、結果は変わらないだろう。";
		mes "少なくとも……";
		mes "過去にオークの巫女とかいうのとの";
		mes "大規模な戦闘があった……";
		mes "という結果は。";
		next;
		mes "[謎の研究者]";
		mes "何でそんなことになったのかは";
		mes "よく分からんが。";
		mes "研究の価値はありそうだな……";
		mes "ククク……！";
		next;
		menu "……………",-;
		mes "[謎の研究者]";
		mes "何度でも見に行けるぞ。";
		mes "過去に起きたことだからな。";
		mes "ありがちな戦争劇……";
		mes "何度も見る価値があるかは";
		mes "知らないがね……ククク。";
		close;
	case 4:
		mes "[謎の研究者]";
		mes "おお、どうだった？";
		mes "時間旅行は楽しかったか？";
		mes "同じ時間にしか行けないからな、";
		mes "私が見てきたものと同じ展開を";
		mes "見てきたんだろう。";
		mes "オークどもの妙な演劇をな。";
		next;
		menu "クルガーが無事だった！",-;
		mes "[謎の研究者]";
		mes "クルガー？";
		mes "ああ、あの巫女に突っ込んで";
		mes "倒れたオークか。";
		mes "あいつが無事だったって？";
		mes "ふむ……そこまで歴史の一部が";
		mes "変わることもあるのか……";
		next;
		mes "[謎の研究者]";
		mes "だがな、今のこのオークどもの";
		mes "村の様子を見ろ。";
		mes "何か変わっているか……？";
		mes "おそらく、クルガーは";
		mes "結果的には倒れる。";
		mes "何も出来ずに、だ。";
		next;
		menu "……………",-;
		mes "[謎の研究者]";
		mes "過去に何かあったって";
		mes "今の現在に至るように";
		mes "歴史は軸を修正しようとするもんだ。";
		mes "たまたま倒れるタイミングが";
		mes "変わったくらいだろう。";
		next;
		mes "[謎の研究者]";
		mes "だが、研究としては非常に";
		mes "面白い……！";
		mes "過去にオークに何かあったのか……？";
		mes "おそらく、これ以上は";
		mes "あの時間に移動するだけでは";
		mes "わからないだろうが……";
		next;
		mes "[謎の研究者]";
		mes "ククク、研究者の血が騒ぐな……";
		close;
	}
}

//============================================================
// 説明NPC
//------------------------------------------------------------
gef_fild10.gat,238,205,4	script	研究メモ	857,{
	mes "[研究メモ]";
	mes "‐過去のオーク地下洞窟の";
	mes "　研究メモ‐";
	next;
	switch(select("^dc143c時間^000000について","^dc143c制限^000000について","^dc143c注意点^000000について")) {
	case 1:
		mes "[研究メモ]";
		mes "過去に時間移動するための";
		mes "鍵を作成し、時間移動すると、";
		mes "その移動先は";
		mes "他のパーティーと干渉しない";
		mes "空間のようである。";
		next;
		mes "[研究メモ]";
		mes "時間移動を行うと";
		mes "^ff0000時間移動の影響^000000を受ける。";
		mes "また、時間移動していられる";
		mes "限界の時間は";
		mes "^0000ff1時間^000000である。";
		next;
		mes "[研究メモ]";
		mes "一度現在に戻るか、1時間経過して";
		mes "現在に戻った後、再度";
		mes "鍵を作成したり、移動するには";
		mes "^ff0000入場してから1回目の午前5時以降^000000";
		mes "且つ、^ff0000最後の入場から1時間経過後^000000";
		mes "になる。";
		close;
	case 2:
		mes "[研究メモ]";
		mes "過去の地下洞窟は";
		mes "例の巫女の呪術だろうか、";
		mes "謎の力が張り巡らされているようだ。";
		mes "そのため一部スキルやアイテムが";
		mes "効果を発揮しない。";
		next;
		mes "[研究メモ]";
		mes "スキルでは、";
		mes "テレポート、アイスウォール、";
		mes "スパイダーウェブ、インティミデイト、";
		mes "アブラカタブラが使えない。";
		next;
		mes "[研究メモ]";
		mes "アイテムでは、";
		mes "ハイローゾイストカード、";
		mes "アゾートといった";
		mes "モンスターを変換する効果が";
		mes "無効化される。";
		next;
		mes "[研究メモ]";
		mes "テレポートと同じ効果の";
		mes "ハエの羽なども";
		mes "使うことができない。";
		close;
	case 3:
		mes "[研究メモ]";
		mes "^ff0000決してモンスターを^000000";
		mes "テイミングしてはならない。";
		mes "もししてしまった場合は、";
		mes "先に進めなくなる可能性がある。";
		mes "そうなったら、現実に";
		mes "戻るほかない。";
		close;
	}
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
gef_fild10.gat,242,202,0	script	狭間の石	406,{
	if (ORCS_1QUE == 0) {
		mes "‐妙な雰囲気の石がある……‐";
		close;
	}
	if(BaseLevel < 30 || BaseLevel > 80 || Job == Job_Summoner) {
		mes "【狭間の石】";
		mes "この空間は";
		mes "^0000ffレベル30～80の人間の冒険者のみ^000000";
		mes "入ることができる。";
		mes "該当しないレベルの冒険者や";
		mes "ドラム族は入ることはできない。";
		close;
	}
	if(getonlinepartymember() == 0) {
		mes "【狭間の石】";
		mes "1人以上のパーティーを組んでから";
		mes "再試行せよ。";
		close;
	}
	if(checkquest(12059) || checkquest(120410)) {
		if(checkquest(12059)&2 == 0 || checkquest(120410)&2 == 0) {
			mes "【狭間の石】";
			mes "ここに足を踏み入れたため、";
			mes "^ff0000時間移動の影響^000000を受けている状態。";
			mes "^ff0000入場してから1回目の午前5時以降^000000";
			mes "且つ、^ff0000最後の入場から1時間経過後^000000";
			mes "に再度、鍵の作成、入場が";
			mes "おこなえる。";
			close;
		}
		delquest 12059;
		delquest 120410;
		mes "【狭間の石】";
		mes "^ff0000時間移動の影響^000000が消えた。";
		mes "ここの鍵の作成、及び入場が";
		mes "可能になった。";
		close;
	}
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "【狭間の石】";
		mes "資格ある代表の者よ。";
		mes "ここに入る鍵を作るか？";
		set '@str$,"Orc's Memoryの鍵の作成";
	}
	else {
		mes "【狭間の石】";
		mes "資格ある者よ。";
		mes "ここに入るか？";
		set '@str$,"";
	}
	next;
	switch(select('@str$,"Orc's Memoryに入る","キャンセル")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "【狭間の石】";
			mes "代表権が無くなっている。";
			mes "再試行せよ。";
			close;
		}
		mdcreate "Orc's Memory";
		mes "【狭間の石】";
		mes "■パーティー名";
		mes "^0000ff"+getpartyname(getcharid(1))+"^000000";
		mes "■パーティーリーダー";
		mes "^0000ff"+getpartyleader(getcharid(1))+"^000000";
		mes " ";
		mes "^006400Orc's Memory^000000の鍵の作成試行中。";
		next;
		mes "【狭間の石】";
		mes "作成に成功した場合は";
		mes "再び石に話しかけ、";
		mes "『Orc's Memoryに入る』を";
		mes "選択することで入場が可能。";
		close;
	case 2:
		switch(mdenter("Orc's Memory")) {
		case 0:	// エラーなし
			announce "メモリアルダンジョン[Orc's Memory] に入場しました　：　"+strcharinfo(1)+" ("+strcharinfo(0)+")",0x9,0x00FF99;
			setquest 12059;
			setquest 120410;
			donpcevent getmdnpcname("クルガー#Orcs1-1")+"::OnStart";
			end;
		case 1:		// パーティー未加入
			mes "【狭間の石】";
			mes "Orc's Memory に入る資格がない。";
			mes "パーティーに加入していない状態。";
			close;
		case 2:		// ダンジョン未作成
			mes "【狭間の石】";
			mes "Orc's Memory の鍵が";
			mes "存在しない。";
			mes "パーティーリーダーが鍵を";
			mes "作成していない状態。";
			close;
		default:	// その他エラー
			mes "【狭間の石】";
			mes "不明なエラーが発生。";
			close;
		}
	case 3:
		close;
	}
}

//============================================================
// オーク地下洞窟 01（過去）
//------------------------------------------------------------
1@orcs.gat,180,29,4	script	クルガー#Orcs1-1	433,{
	donpcevent getmdnpcname("クルガー#Orcs1-2")+"::OnStart";
	hideonnpc;
	end;
OnStart:
	if('flag == 0) {
		set 'flag,1;
		areasetcell "this",164,27,180,27,1;
		monster "this",164,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",165,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",166,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",167,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",168,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",169,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",170,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",171,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",172,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",173,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",174,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",175,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",176,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",177,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",178,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",179,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
		monster "this",180,28,"",1080,1,getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
	}
	end;
OnKilled:
	end;
}

1@orcs.gat,180,29,4	script	クルガー#Orcs1-2	433,{
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer10:
	announce "クルガー : 何故こんなに遅れた!!　言い訳を聞く要素はひとつも無いぞ!?　今が一番大変だというのに!!",0x9,0xFFFF00;
	end;
OnTimer5710:
	announce "クルガー : 計画通りに進んでいれば我々の仲間が門を開けていたはずだ！　だがお前達が遅れたせいで巫女にバレてやりづらくなった！",0x9,0xFFFF00;
	end;
OnTimer14610:
	announce "オーク守護大将 : 新しい勢力が入った気配がするな……巡回兵！　入口近辺を警護しろ！",0x9,0xFF4444;
	end;
OnTimer20210:
	announce "クルガー : まずいな……奴らがすぐにでも群がってくるだろう。いいか、今から言うことをよく聞け。",0x9,0xFFFF00;
	end;
OnTimer24910:
	announce "クルガー : 我々に気付いた巫女はこの階層を四つの区域に分けて封印魔術を施した。そして区域ごとに一人の守護兵が封印を管理している……",0x9,0xFFFF00;
	end;
OnTimer34310:
	announce "クルガー : もう理解したろ？　奴らを片付けて封印を解くんだ！　そうすれば次の階層に移動できる！",0x9,0xFFFF00;
	end;
OnTimer39710:
	announce "クルガー : ただしひとつ注意しろ！　封印の守護兵以外には手を出すな！　奴ら、仲間がやられる度に兵力を強化してきやがる！",0x9,0xFFFF00;
	end;
OnTimer49210:
	announce "クルガー : 最悪の場合は次の階層に行くどころじゃなくなる可能性がある。なるべく全面対決を避けて進むんだ！",0x9,0xFFFF00;
	end;
OnTimer56310:
	announce "[任務] 【オーク封印守護兵】を倒せ！　守護兵以外のオーク兵との戦闘を極力避けろ！",0x9,0x44FFFF;
	donpcevent getmdnpcname("OrcsControl1")+"::OnStart";
	hideonnpc;
	killmonster "this",getmdnpcname("クルガー#Orcs1-1")+"::OnKilled";
	areasetcell "this",164,27,180,27,0;
	end;
OnInit:
	hideonnpc;
	end;
}

1@orcs.gat,0,0,0	script	OrcsControl1	-1,{
OnStart:
	areamonster "this",0,0,0,0,"オーク兵",1217,30,getmdnpcname("OrcsControl1")+"::OnKilled1";
	areamonster "this",0,0,0,0,"訓練された狼",1432,15,getmdnpcname("OrcsControl1")+"::OnKilled2";
	areamonster "this",0,0,0,0,"オーク弓兵",1473,15,getmdnpcname("OrcsControl1")+"::OnKilled3";
	areamonster "this",0,0,0,0,"",2569,10,getmdnpcname("OrcsControl1")+"::OnKilled4";
	areamonster "this",137,83,143,89,"オーク封印守護兵",1217,1,getmdnpcname("OrcsControl1")+"::OnKilled5";
	end;
OnKilled1:
	set '@num,30 - getmapmobs(getmdmapname("1@orcs.gat"),getmdnpcname("OrcsControl1")+"::OnKilled1");
	if('@num > 0) {
		set '@rand,rand(30);
		if('@rand < 1) {
			areamonster "this",0,0,0,0,"オーク兵",1217,'@num,getmdnpcname("OrcsControl1")+"::OnKilled1";
		} else if('@rand < 2) {
			areamonster "this",0,0,0,0,"オーク突撃兵",1439,'@num,getmdnpcname("OrcsControl1")+"::OnKilled1";
			if(rand(10) == 0) {
				announce "オーク守護大将 : 防御が不足しているぞ！　もう少しまともな兵はいないのか!?",0x9,0xFF4444;
			}
		} else if('@rand < 4) {
			areamonster "this",41,81,51,91,"オーク突撃兵",1439,'@num,getmdnpcname("OrcsControl1")+"::OnKilled1";
			if(rand(10) == 0) {
				announce "オーク守護大将 : 突撃兵たちはいるか!?　敵勢力を抑えろ!!",0x9,0xFF4444;
			}
		} else {
			areamonster "this",17,177,27,187,"オーク突撃兵",1439,'@num,getmdnpcname("OrcsControl1")+"::OnKilled1";
			if(rand(5) == 0) {
				announce "[警告] 第四区域に一部兵力が集結を開始！",0x9,0x77FF77;
			}
			if(rand(100) == 0) {
				initnpctimer;
			}
		}
	}
	end;
OnTimer10:
	announce "オーク守護大将 : 埒が明かないな！　スタラクタイトゴーレムを召喚しろ!!",0x9,0xFF4444;
	end;
OnTimer4010:
	announce "[警告] スタラクタイトゴーレムが地下の泥土より出現！",0x9,0x77FF77;
	areamonster "this",17,177,27,187,"スタラクタイトゴーレム",1223,20,getmdnpcname("OrcsControl1")+"::OnKilled1";
	stopnpctimer;
	end;
OnKilled2:
	if(rand(2)) {
		areamonster "this",0,0,0,0,"訓練された狼",1432,1,getmdnpcname("OrcsControl1")+"::OnKilled2";
	} else {
		areamonster "this",17,177,27,187,"訓練された狼",1432,1,getmdnpcname("OrcsControl1")+"::OnKilled2";
	}
	end;
OnKilled3:
	set '@rand,rand(30);
	if('@rand < 1) {
		areamonster "this",0,0,0,0,"オーク弓兵",1473,1,getmdnpcname("OrcsControl1")+"::OnKilled3";
	} else if('@rand < 4) {
		areamonster "this",43,155,47,159,"オーク弓兵",1473,1,getmdnpcname("OrcsControl1")+"::OnKilled3";
		if(rand(3) == 0) {
			announce "オーク守護大将 : 後衛を狙え！　敵の支援を断つのだ!!",0x9,0xFF4444;
		}
	} else {
		areamonster "this",17,177,27,187,"オーク弓兵",1473,1,getmdnpcname("OrcsControl1")+"::OnKilled3";
	}
	end;
OnKilled4:
	areamonster "this",0,0,0,0,"",2569,1,getmdnpcname("OrcsControl1")+"::OnKilled4";
	end;
OnKilled5:
	enablenpc getmdnpcname("#OrcsWarp1-1");
	initnpctimer getmdnpcname("#OrcsWarp1-1");
	areamonster "this",103,105,109,111,"オーク封印守護兵",1217,1,getmdnpcname("OrcsControl1")+"::OnKilled6";
	announce "[情報] 【オーク封印守護兵】1体撃破！　次の区画へ移動可能！",0x9,0x44FFFF;
	end;
OnKilled6:
	enablenpc getmdnpcname("#OrcsWarp1-2");
	initnpctimer getmdnpcname("#OrcsWarp1-2");
	areamonster "this",32,40,38,46,"オーク封印守護兵",1217,1,getmdnpcname("OrcsControl1")+"::OnKilled7";
	announce "[情報] 【オーク封印守護兵】2体撃破！　次の区画へ移動可能！",0x9,0x44FFFF;
	end;
OnKilled7:
	enablenpc getmdnpcname("#OrcsWarp1-3");
	areamonster "this",19,177,25,183,"オーク封印守護兵",1217,1,getmdnpcname("OrcsControl1")+"::OnKilled8";
	announce "[情報] 【オーク封印守護兵】3体撃破！　次の区画へ移動可能！",0x9,0x44FFFF;
	end;
OnKilled8:
	enablenpc getmdnpcname("#OrcsWarp1-4");
	initnpctimer getmdnpcname("#OrcsWarp1-4");
	killmonster "this",getmdnpcname("OrcsControl1")+"::OnKilled1";
	killmonster "this",getmdnpcname("OrcsControl1")+"::OnKilled2";
	killmonster "this",getmdnpcname("OrcsControl1")+"::OnKilled3";
	killmonster "this",getmdnpcname("OrcsControl1")+"::OnKilled4";
	announce "[情報] 【オーク封印守護兵】全て撃破！　次の階層へ移動可能！",0x9,0x44FFFF;
	end;
}

1@orcs.gat,168,125,0	script	#OrcsWarp1-1	45,3,3,{
OnTouch:
	warp getmdmapname("1@orcs.gat"),168,130;
	end;
OnTimer10300:
	announce "クルガーの囁き : ここのオークたちはちょっと前まで俺の仲間だった……だが巫女の精神支配を受けて自らの意思を失ってしまった。",0x9,0xFF4499;
	end;
OnTimer18700:
	announce "クルガーの囁き : だが今はどうすることも出来ん。残っている仲間を助ける為にも巫女は倒さねばならないのだ。",0x9,0xFF4499;
	stopnpctimer;
	end;
OnInit:
	disablenpc;
	end;
}

1@orcs.gat,89,94,0	script	#OrcsWarp1-2	45,3,3,{
OnTouch:
	warp getmdmapname("1@orcs.gat"),85,85;
	end;
OnTimer10300:
	announce "クルガーの囁き : ここまでの道に仲間たちの骸があった……巫女は何も知らないオークたちを自分の儀式に使った。",0x9,0xFF4499;
	end;
OnTimer18700:
	announce "クルガーの囁き : だが、それは全て俺のためだったんだ……自分が撒いた種は自分でなんとかしなくてはな……",0x9,0xFF4499;
	stopnpctimer;
	end;
OnInit:
	disablenpc;
	end;
}

1@orcs.gat,38,105,0	script	#OrcsWarp1-3	45,3,3,{
OnTouch:
	warp getmdmapname("1@orcs.gat"),38,110;
	end;
OnInit:
	disablenpc;
	end;
}

1@orcs.gat,21,189,0	script	#OrcsWarp1-4	45,3,3,{
OnTouch:
	warp getmdmapname("2@orcs.gat"),32,171;
	donpcevent getmdnpcname("クルガー#Orcs2-1")+"::OnStart";
	end;
OnTimer2300:
	announce "クルガーの囁き : あと少しだ……",0x9,0xFF4499;
	end;
OnTimer5700:
	announce "クルガーの囁き : ここを抜ければ次の階層に移動できる。気を抜くなよ。",0x9,0xFF4499;
	stopnpctimer;
	end;
OnInit:
	disablenpc;
	end;
}

//============================================================
// オーク地下洞窟 02（過去）
//------------------------------------------------------------
2@orcs.gat,35,169,4	script	クルガー#Orcs2-1	433,{
	donpcevent getmdnpcname("クルガー#Orcs2-2")+"::OnStart";
	hideonnpc;
	end;
OnStart:
	if('flag == 0) {
		set 'flag,1;
		areasetcell "this",28,165,37,165,1;
		monster "this",28,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",29,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",30,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",31,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",32,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",33,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",34,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",35,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",36,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
		monster "this",37,164,"",1080,1,getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
	}
	end;
OnKilled:
	end;
}

2@orcs.gat,35,169,4	script	クルガー#Orcs2-2	433,{
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer10:
	announce "クルガー : よし、来たな。今のうちに巫女のところに行く方法を教える。",0x9,0xFFFF00;
	end;
OnTimer3510:
	announce "クルガー : 巫女があちこちに立てた松明が見えるか？　あれに魔力を込めることで次の区域への封印が解かれるはずだ。",0x9,0xFFFF00;
	end;
OnTimer10710:
	announce "クルガー : 無論簡単に触れられないように敵は動くだろう。小規模な戦いは避けられないか……",0x9,0xFFFF00;
	end;
OnTimer16310:
	announce "クルガー : だがなるべく巫女直属の兵士が防衛することがないように静かに行動したほうがいいだろうな。",0x9,0xFFFF00;
	end;
OnTimer21910:
	announce "クルガー : よし、先に進んでくれ。俺は俺で行動する……",0x9,0xFFFF00;
	end;
OnTimer23910:
	announce "[任務] 最大限戦闘を避けつつ松明に魔力を込め、封印を解け！　なお、魔力を込められる松明は一定の順番で決まる！",0x9,0x44FFFF;
	donpcevent getmdnpcname("OrcsControl2")+"::OnStart";
	hideoffnpc getmdnpcname("松明#Orcs1-1");
	hideonnpc;
	killmonster "this",getmdnpcname("クルガー#Orcs2-1")+"::OnKilled";
	areasetcell "this",28,165,37,165,0;
	end;
OnTimer29310:
	announce "クルガー : そうだ、言い忘れていた。松明には一人で触れろ！　あんまり複数人で同時に触れると痛い目にあうぞ！",0x9,0xFFFF00;
	end;
OnInit:
	hideonnpc;
	end;
}

2@orcs.gat,0,0,0	script	OrcsControl2	-1,{
OnStart:
	areamonster "this",0,0,0,0,"オーク怨霊",1462,30,getmdnpcname("OrcsControl2")+"::OnKilled1";
	areamonster "this",0,0,0,0,"腐ったオーク兵",1463,15,getmdnpcname("OrcsControl2")+"::OnKilled2";
	areamonster "this",0,0,0,0,"",2569,10,getmdnpcname("OrcsControl2")+"::OnKilled3";
	end;
OnKilled1:
	set '@num,30 - getmapmobs(getmdmapname("2@orcs.gat"),getmdnpcname("OrcsControl2")+"::OnKilled1");
	if('@num > 0) {
		set '@rand,rand(30);
		if('@rand < 1) {
			areamonster "this",0,0,0,0,"オーク怨霊",1462,1,getmdnpcname("OrcsControl2")+"::OnKilled1";
		} else if('@rand < 2) {
			areamonster "this",0,0,0,0,"オーク突撃兵",1439,1,getmdnpcname("OrcsControl2")+"::OnKilled1";
		} else if('@rand < 4) {
			areamonster "this",157,112,167,122,"オーク突撃兵",1439,1,getmdnpcname("OrcsControl2")+"::OnKilled1";
			if(rand(5) == 0) {
				announce "[警告] オーク突撃兵たちが第三区域に集結を開始！",0x9,0xFF4444;
			}
		} else {
			areamonster "this",173,13,183,23,"オーク突撃兵",1439,1,getmdnpcname("OrcsControl2")+"::OnKilled1";
			if(rand(5) == 0) {
				announce "[警告] 巫女のテリトリーに多数の兵が集結を開始！",0x9,0x77FF77;
			}
			if(rand(70) == 0) {
				initnpctimer;
			}
		}
	}
	end;
OnTimer10:
	announce "謎の声 : しつこい奴らよ。この程度でこちらが崩れると思ったかえ？",0x9,0xFF4444;
	end;
OnTimer4010:
	announce "[警告] 降霊儀式により、古代の呪われた魂が甦る！",0x9,0x77FF77;
	areamonster "this",167,25,177,35,"邪悪なる古の魂",1475,30,getmdnpcname("OrcsControl2")+"::OnKilled1";
	stopnpctimer;
	end;
OnKilled2:
	set '@rand,rand(30);
	if('@rand < 1) {
		areamonster "this",0,0,0,0,"オーク弓兵",1473,1,getmdnpcname("OrcsControl2")+"::OnKilled2";
	} else if('@rand < 24) {
		areamonster "this",168,10,184,26,"オーク弓兵",1473,1,getmdnpcname("OrcsControl2")+"::OnKilled2";
	} else {
		areamonster "this",168,21,184,21,"オーク弓兵",1473,1,getmdnpcname("OrcsControl2")+"::OnKilled2";
		if(rand(3) == 0) {
			announce "[警告] 巫女のテリトリーに多数の兵が集結を開始！",0x9,0x77FF77;
		}
		if(rand(70) == 0) {
			initnpctimer;
		}
	}
	end;
OnKilled3:
	areamonster "this",0,0,0,0,"",2569,1,getmdnpcname("OrcsControl2")+"::OnKilled3";
	end;
OnBossSpawn1:
	monster "this",109,156,"オーク守護大将",1981,1,getmdnpcname("OrcsControl2")+"::OnBossKilled1";
	announce "オーク守護大将 : このネズミ野郎どもめ!!　勇気があるならば俺と闘え!!",0x9,0xFF8888;
	end;
OnBossKilled1:
	enablenpc getmdnpcname("#OrcsWarp2-1");
	hideoffnpc getmdnpcname("松明#Orcs2-1");
	announce "[情報] オーク守護大将を撃破！　次の区域へ移動可能！",0x9,0x44FFFF;
	end;
OnBossSpawn2:
	monster "this",67,64,"オーク狙撃兵",1982,1,getmdnpcname("OrcsControl2")+"::OnBossKilled2";
	announce "オーク狙撃兵 : ふん、よくここまで来たな！　だが残念！　お前たちの冒険はここで終わりだ!!",0x9,0xFF8888;
	end;
OnBossKilled2:
	enablenpc getmdnpcname("#OrcsWarp2-2");
	hideoffnpc getmdnpcname("松明#Orcs3-1");
	announce "[情報] オーク狙撃兵を撃破！　次の区域へ移動可能！",0x9,0x44FFFF;
	end;
OnBossSpawn3:
	monster "this",152,147,"堕ちたオークの怨念",1983,1,getmdnpcname("OrcsControl2")+"::OnBossKilled3";
	announce "堕ちたオークの怨念 : 肉ダ！　肉をヨこセ！　腹ガ減っタ！　人間、食ウ！",0x9,0xFF8888;
	end;
OnBossKilled3:
	enablenpc getmdnpcname("#OrcsWarp2-3");
	donpcevent getmdnpcname("OrcsBossControl")+"::OnStart";
	end;
}

2@orcs.gat,26,164,0	script	松明#Orcs1-1	844,{
	progressbar 5;
	if(getnpctimer(1) == 0) {
		initnpctimer;
		set '@num1,substr(strnpcinfo(2),4,1);
		set '@num2,substr(strnpcinfo(2),6,1);
		hideoffnpc getmdnpcname("松明#Orcs"+'@num1+"-"+('@num2+1));
		announce "[情報] "+('@num2 == 1? "一": '@num2 == 2? "二": "三")+"つ目の松明に魔力注入完了！　次に魔力を込められる松明を探して触れろ！",0x9,0x44FFFF;
		hideonnpc;
	}
	end;
OnTimer100:
	misceffect 96;
	end;
OnTimer2000:
	misceffect 97;
	end;
OnInit:
	hideonnpc;
	end;
}
2@orcs.gat,55,155,0		duplicate(松明#Orcs1-1)	松明#Orcs1-2	844
2@orcs.gat,108,146,0	duplicate(松明#Orcs1-1)	松明#Orcs1-3	844

2@orcs.gat,98,171,0		script	松明#Orcs1-4	844,{
	progressbar 10;
	if(getnpctimer(1) == 0) {
		initnpctimer;
		donpcevent getmdnpcname("OrcsControl2")+"::OnBossSpawn"+substr(strnpcinfo(2),4,1);
		hideonnpc;
	}
	end;
OnTimer100:
	misceffect 96;
	end;
OnTimer2000:
	misceffect 97;
	end;
OnInit:
	hideonnpc;
	end;
}

2@orcs.gat,48,100,0	script	#OrcsWarp2-1	45,3,3,{
OnTouch:
	warp getmdmapname("2@orcs.gat"),47,93;
	end;
OnInit:
	disablenpc;
	end;
}

2@orcs.gat,35,92,0	duplicate(松明#Orcs1-1)	松明#Orcs2-1	844
2@orcs.gat,32,70,0	duplicate(松明#Orcs1-1)	松明#Orcs2-2	844
2@orcs.gat,70,31,0	duplicate(松明#Orcs1-1)	松明#Orcs2-3	844
2@orcs.gat,84,51,0	duplicate(松明#Orcs1-4)	松明#Orcs2-4	844

2@orcs.gat,101,55,0	script	#OrcsWarp2-2	45,3,3,{
OnTouch:
	warp getmdmapname("2@orcs.gat"),107,55;
	end;
OnInit:
	disablenpc;
	end;
}

2@orcs.gat,142,145,0	duplicate(松明#Orcs1-1)	松明#Orcs3-1	844
2@orcs.gat,162,134,0	duplicate(松明#Orcs1-1)	松明#Orcs3-2	844
2@orcs.gat,144,117,0	duplicate(松明#Orcs1-1)	松明#Orcs3-3	844
2@orcs.gat,136,98,0		duplicate(松明#Orcs1-4)	松明#Orcs3-4	844

2@orcs.gat,167,104,0	script	#OrcsWarp2-3	45,3,3,{
OnTouch:
	warp getmdmapname("2@orcs.gat"),167,95;
	end;
OnInit:
	disablenpc;
	end;
}

2@orcs.gat,0,0,0	script	OrcsBossControl	-1,{
OnStart:
	monster "this",179,15,"堕ちたオークヒーロー",1850,1,getmdnpcname("OrcsBossControl")+"::OnKilled1";
	monster "this",185,8,"巫女カルガルラスィ",1984,1,getmdnpcname("OrcsBossControl")+"::OnKilled2";
	announce "巫女カルガルラスィ : ホッホホ！　結局ここまで来たのかえ。貴様らの送り込んだ刺客は無謀であった。その阿呆なオークはわらわの足元で転がっておるわ。",0x9,0xFFFF00;
	initnpctimer;
	end;
OnTimer6810:
	announce "巫女カルガルラスィ : わらわの忠実なる下僕よ、侵入者どもを殲滅してまいれ。",0x9,0xFFFF00;
	end;
OnTimer10310:
	announce "堕ちたオークヒーロー : 御意………………",0x9,0xFF8888;
	end;
OnTimer13110:
	announce "[警告] 巫女に発見された！　別行動していたクルガーの作戦は失敗した模様！　巫女を倒せ！",0x9,"0x8888FF";
	stopnpctimer;
	end;
OnKilled1:
	announce "堕ちたオークヒーロー : 無念………………",0x9,0xFF8888;
	sleep 6810;
	announce "巫女カルガルラスィ : ……なんという役立たずじゃ。反吐が出るわ。",0x9,0xFFFF00;
	end;
OnKilled2:
	switch(rand(4)) {
	case 0:
		announce "巫女カルガルラスィ : この強さ……人間とは思えぬ……!!",0x9,0xFFFF00;
		break;
	case 1:
		announce "巫女カルガルラスィ : こ……こんなはずでは……この虫けらども……!!",0x9,0xFFFF00;
		break;
	case 2:
		announce "巫女カルガルラスィ : まだ……死ぬわけには行かぬ……!!",0x9,0xFFFF00;
		break;
	case 3:
		announce "巫女カルガルラスィ : 話にならぬ……このようなことがあってたまるかぁぁ!!",0x9,0xFFFF00;
		break;
	}
	hideoffnpc getmdnpcname("クルガー#Orcs2-3");
	enablenpc getmdnpcname("#OrcsWarp2-4");
	killmonster "this",getmdnpcname("OrcsControl2")+"::OnKilled1";
	killmonster "this",getmdnpcname("OrcsControl2")+"::OnKilled2";
	killmonster "this",getmdnpcname("OrcsControl2")+"::OnKilled3";
	killmonster "this",getmdnpcname("OrcsBossControl")+"::OnKilled1";
	end;
}

2@orcs.gat,172,13,0	script	クルガー#Orcs2-3	434,{
	switch(ORCS_1QUE) {
	default:
		mes "[クルガー]";
		mes "…………";
		mes strcharinfo(0)+"、";
		mes "お前か……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……！";
		mes "傷が酷い！　動かないほうが……";
		next;
		mes "[クルガー]";
		mes "いいんだ……";
		mes "俺は失敗したんだからな……";
		mes "巫女は……？";
		mes "巫女はどうなった……？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "巫女は倒しましたよ。";
		mes "ところで、結局あの巫女の";
		mes "正体は何なんです？";
		next;
		mes "‐クルガーは安堵の表情を見せた後、";
		mes "　少し苦しそうな顔をした……‐";
		next;
		mes "[クルガー]";
		mes "……結局……";
		mes "俺は自分の手で娘を止めることは";
		mes "出来なかっただろう……";
		mes "だがもう、もうその娘も、";
		mes "自分を苦しめた悪夢も……";
		mes "終わったこと……だ……";
		next;
		mes "‐切実な表情で何か言おうと";
		mes "　していたクルガーだったが、";
		mes "　そのまま最後の息を吐くと";
		mes "　やがて冷たくなっていった……";
		mes "　と同時に、目の前に光が溢れた‐";
		close2;
		set ORCS_1QUE,2;
		break;
	case 2:
		mes "[クルガー]";
		mes "…………";
		mes strcharinfo(0)+"、";
		mes "お前か……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……！";
		mes "傷が酷い！　動かないほうが……";
		next;
		mes "[クルガー]";
		mes "いいんだ……";
		mes "俺は失敗したんだからな……";
		mes "巫女は……？";
		mes "巫女はどうなった……？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "巫女は倒しましたよ。";
		mes "ところで、結局あの巫女の";
		mes "正体は……";
		next;
		if(select("あなたの娘なのですか？","何なんですか？") == 1) {
			mes "[クルガー]";
			mes "…………!!";
			mes "お前……何故それを……!?";
			mes "ふ……まあ、今となっては";
			mes "もう終わったことだ……";
			next;
			mes "[クルガー]";
			mes "俺の娘の巫女は……";
			mes "ある野望を持って仲間のオークたちの";
			mes "精神支配をした……";
			mes "お前も知っていると思うが";
			mes "昔はオークと人間は不可侵条約のような";
			mes "物を結んでいた……";
			next;
			mes "[クルガー]";
			mes "ところがその精神支配のせいで";
			mes "我々は敵対するようになってしまった。";
			mes "俺をはじめとする精神支配から";
			mes "逃れたオークは、お前たち";
			mes "人間に巫女を倒す協力を求めた……";
			next;
			mes "[クルガー]";
			mes "そして……";
			mes "見事、お前たち人間のおかげで";
			mes "巫女が倒せたわけだ……";
			mes "だが精神支配の影響は残るだろう……";
			mes "今後もオークと人間の敵対関係は";
			mes "続いてしまうだろうな……";
			next;
			mes "[クルガー]";
			mes "だが……それも";
			mes "仕方あるまい……ぐぅっ……!!";
			mes "ありがとうよ、 勇士よ……";
			mes "俺は…………";
			mes "……";
			next;
			mes "‐切実な表情で何か言おうと";
			mes "　していたクルガーだったが、";
			mes "　そのまま最後の息を吐くと";
			mes "　やがて冷たくなっていった……";
			mes "　と同時に、目の前に光が溢れた‐";
			close2;
			set ORCS_1QUE,3;
		}
		else {
			mes "‐クルガーは安堵の表情を見せた後、";
			mes "　少し苦しそうな顔をした……‐";
			next;
			mes "[クルガー]";
			mes "……結局……";
			mes "俺は自分の手で娘を止めることは";
			mes "出来なかっただろう……";
			mes "だがもう、もうその娘も、";
			mes "自分を苦しめた悪夢も……";
			mes "終わったこと……だ……";
			next;
			mes "‐切実な表情で何か言おうと";
			mes "　していたクルガーだったが、";
			mes "　そのまま最後の息を吐くと";
			mes "　やがて冷たくなっていった……";
			mes "　と同時に、目の前に光が溢れた‐";
			close2;
		}
		break;
	case 3:
	case 4:
		mes "[クルガー]";
		mes "…………";
		mes strcharinfo(0)+"、";
		mes "お前か……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "クルガー……！";
		mes "大丈夫!?";
		next;
		mes "[クルガー]";
		mes "ああ……運が良かったのか";
		mes "足の骨折くらいで済んだ。";
		mes "……まあこの通り立つことは";
		mes "難しいんだがな……恥ずかしい話だ。";
		mes "それで、巫女は……？";
		mes "巫女はどうなった……？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "巫女は倒しましたよ。";
		mes "ところで、結局あの巫女の";
		mes "正体はあなたの娘なんですよね？";
		next;
		mes "[クルガー]";
		mes "…………!!";
		mes "お前……何故それを……!?";
		mes "ふ……まあ、今となっては";
		mes "もう終わったことだ……";
		next;
		mes "[クルガー]";
		mes "俺の娘の巫女は……";
		mes "ある野望を持って仲間のオークたちの";
		mes "精神支配をした……";
		mes "お前も知っていると思うが";
		mes "昔はオークと人間は不可侵条約のような";
		mes "物を結んでいた……";
		next;
		mes "[クルガー]";
		mes "ところがその精神支配のせいで";
		mes "我々は敵対するようになってしまった。";
		mes "俺をはじめとする精神支配から";
		mes "逃れたオークは、お前たち";
		mes "人間に巫女を倒す協力を求めた……";
		next;
		mes "[クルガー]";
		mes "そして……";
		mes "見事、お前たち人間のおかげで";
		mes "巫女が倒せたわけだ……";
		mes "だが精神支配の影響は残るだろう……";
		mes "今後もオークと人間の敵対関係は";
		mes "続いてしまうだろうな……";
		next;
		mes "[クルガー]";
		mes "だが……それも";
		mes "仕方あるまい……";
		mes "ありがとうよ、勇士よ……";
		mes "とりあえずの脅威は去った……";
		mes "俺はあとは見守るだけだ。";
		next;
		mes "‐クルガーは優しく微笑んだ。";
		mes "　と同時に、目の前に光が溢れた‐";
		close2;
		if(ORCS_1QUE == 3)
			set ORCS_1QUE,4;
		break;
	}
	warp "gef_fild10.gat", 240, 197;
	end;

OnInit:
	hideonnpc;
	end;
}

2@orcs.gat,182,8,0	script	#OrcsWarp2-4	45,3,3,{
OnTouch:
	mes "‐眼の前が輝いている。";
	mes "　元の場所に戻れるのだろうか？‐";
	next;
	if(select("先に進んでみる","何もしない") == 2) {
		mes "‐何もしないでおこう……‐";
		close;
		close;
	}
	mes "‐光がさらに溢れてくる……！‐";
	close2;
	warp "gef_fild10.gat",240,197;
	end;
OnInit:
	disablenpc;
	end;
}
