//= Auriga Script ==============================================================
// Ragnarok Online Mora Town Script	by refis
//==============================================================================

//============================================================
// Shop
//------------------------------------------------------------
-	shop	mora_callshop1	-1,11519
mora.gat,138,110,3	script	シェフ#mora	518,{
	callshop "mora_callshop1";
	end;
OnInit:
	waitingroom "ビーフトースト",0;
	end;
}

-	shop	mora_callshop2	-1,11522,11523,11524,602,601,611,1773,1774
mora.gat,100,118,3	script	モーラ道具屋#mora	517,{
	callshop "mora_callshop2";
	end;
OnInit:
	waitingroom "道具屋",0;
	end;
}

//============================================================
// ビフロストフィールド01⇒ビフロストフィールド02転送NPC
//------------------------------------------------------------
bif_fild01.gat,38,374,0	script	不思議な花	844,{
	mes "‐巨大な花がある‐";
	next;
	if(countitem(12561) < 1) {
		mes "‐……";
		mes "　特に何もないので";
		mes "　あなたは立ち去った‐";
		close;
	}
	mes "‐……";
	mes "　花が大きく揺れ始めた。";
	mes "　不思議な種に";
	mes "　反応しているようだ‐";
	next;
	if(select("不思議な種を置く","何もしない") == 2) {
		mes "‐当然、何も起きなかった‐";
		close;
	}
	mes "‐不思議な種を置くと、";
	mes "　花は凄まじい勢いで";
	mes "　花びらを閉じた。";
	mes "　その影響で突風が発生し、";
	mes "　種とあなたは空高く";
	mes "　飛ばされてしまった!‐";
	close2;
	delitem 12561,1;
	warp "bif_fild02.gat",160,230;
	end;
}

//============================================================
// ビフロストフィールド02⇔モーラ転送NPC
//------------------------------------------------------------
bif_fild02.gat,285,332,0	script	不思議なトンネル#mora1	844,7,7,{
	mes "‐大きな花に囲まれるように";
	mes "　小さなトンネルがある。";
	mes "　この小さなトンネルの奥から";
	mes "　賑やかな声が聞こえる……‐";
	next;
	if(select("覗いてみる","立ち去る") == 2) {
		mes "‐あなたは立ち去った‐";
		close;
	}
	mes "‐不思議な力で";
	mes "　あなたはトンネルの中に";
	mes "　吸い込まれた‐";
	close2;
	warp "mora.gat",179,74;
	end;
OnTouch:
	misceffect 362;
	end;
}

bif_fild02.gat,95,310,0		duplicate(不思議なトンネル#mora1)	不思議なトンネル#mora2	844,7,7
bif_fild02.gat,173,162,0	duplicate(不思議なトンネル#mora1)	不思議なトンネル#mora3	844,7,7

mora.gat,182,74,0	script	出口#mora1	45,1,1,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "["+strcharinfo(0)+"]";
		mes "（なぜか外への道が";
		mes "遮断されていて、";
		mes "外に出ることが出来ない……）";
		next;
		mes "‐^FF0000異世界クエスト^000000をクリアしないと";
		mes "　モーラの外へ出ることができません‐";
		next;
		mes "[???]";
		mes "おい。";
		mes "　";
		mes "‐誰かが話しかけてきた。";
		mes "　振り向くと目つきが鋭い青年がいる‐";
		next;
		mes "[???]";
		mes "道に迷ったのか？";
		mes "俺がプロンテラに";
		mes "送ってやってもいいが。";
		next;
		if(select("お願いします！","けっこうです") == 2) {
			mes "[???]";
			mes "そうか。";
			mes "余計なお世話だったな。";
			close;
		}
		mes "[???]";
		mes "では送ってやろう。";
		close2;
		warp "prontera.gat",116,72;
		end;
	}
	if(strnpcinfo(2) == "mora1")
		warp "bif_fild02.gat",286,327;
	else if(strnpcinfo(2) == "mora2")
		warp "bif_fild02.gat",99,308;
	else if(strnpcinfo(2) == "mora3")
		warp "bif_fild02.gat",176,162;
	end;
}

mora.gat,20,159,0	duplicate(出口#mora1)	出口#mora2	45,1,1
mora.gat,56,25,0	duplicate(出口#mora1)	出口#mora3	45,1,1

//============================================================
// スプレンディッド転送NPC
//------------------------------------------------------------
mora.gat,135,81,4	script	猫の手職員#mora	421,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[猫の手職員]";
		mes "うにゃにゃー。";
		mes "モーラは居心地がいいから";
		mes "長居しちゃうにゃー。";
		next;
		mes "[猫の手職員]";
		mes "もうちょっと";
		mes "ゆっくりしていくにゃー。";
		close;
	}
	mes "[猫の手職員]";
	mes "うにゃにゃー。";
	mes "モーラは居心地がいいから";
	mes "長居しちゃったにゃー。";
	next;
	mes "[猫の手職員]";
	mes "そろそろ、スプレンディッドの";
	mes "方へ戻るかにゃー。";
	mes "ところで旅人、";
	mes "よろしければ";
	mes "ご一緒に戻りませんかにゃ？";
	next;
	mes "[猫の手職員]";
	mes "一人より二人の方が楽しいですにゃ。";
	mes "私はビフロスト南部への";
	mes "秘密の抜け道を知っているから";
	mes "安全に戻れるにゃーですよ。";
	next;
	switch(select("スプレンディッドの北側に行く","スプレンディッドの東側に行く","今はいいです")) {
	case 1:
		mes "[猫の手職員]";
		mes "いやあ、";
		mes "それでは楽しいお話をしながら";
		mes "行きましょうにゃー。";
		close2;
		warp "splendide.gat",270,378;
		end;
	case 2:
		mes "[猫の手職員]";
		mes "いやあ、";
		mes "それでは楽しいお話をしながら";
		mes "行きましょうにゃー。";
		close2;
		warp "splendide.gat",377,247;
		end;
	case 3:
		mes "[猫の手職員]";
		mes "そうですかにゃー。";
		mes "寂しいですにゃー。";
		close;
	}
OnInit:
	waitingroom "スプレンディッド転送",0;
	end;
}

//============================================================
// 案内員
//------------------------------------------------------------
mora.gat,167,76,3	script	レシア案内員#mora	522,5,5,{
	mes "[案内員ラプオ]";
	mes "ラオ～！";
	mes "レシア族の街モーラへようこそ！";
	mes "歓迎するお！";
	next;
	mes "[案内員ラプオ]";
	mes "君は最近現れるという";
	mes "人間という種族だね！";
	mes "ゆっくりしていくといいお♪";
	next;
	mes "[案内員ラプオ]";
	mes "それにしても、";
	mes "妖精のラフィネ族さん、";
	mes "猫の手職員さん、";
	mes "その他にもいろんな種族が";
	mes "この街を訪れるから";
	mes "賑やかで楽しいお！";
	next;
	mes "[案内員ラプオ]";
	mes "このビフロストは";
	mes "言葉が違っても話したことが";
	mes "互いに理解できる";
	mes "空間なんだお！";
	mes "だからこうやって話せるお！";
	next;
	mes "[案内員ラプオ]";
	mes "さてさて、";
	mes "行きたい場所があれば";
	mes "ラプオが案内するお！";
	next;
	switch(select("[旅館]","[居住地域]","[商店街]","[物流倉庫]","ミニMAP上の位置表示を消す","今はいいです")) {
	case 1:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "モーラ街に訪れた旅人が";
		mes "休める場所お。";
		mes "ゆっくり休めお！";
		viewpoint 1,44,134,0,0x0A82FF;
		close;
	case 2:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "おれたち、レシアの家があるお。";
		mes "寝てる仲間たちもいるから";
		mes "静かによろしくお。";
		viewpoint 1,119,170,1,0xAAFF00;
		close;
	case 3:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "旅の記念に買い物をするなら";
		mes "ここに行くお！";
		viewpoint 1,112,110,2,0xDA70D6;
		close;
	case 4:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "各種配達品と食料があるお。";
		mes "レシア族所有のものじゃないのも";
		mes "保管してるお！";
		viewpoint 1,182,161,3,0xFF1493;
		close;
	case 5:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "表示を消したお。";
		viewpoint 2,1,1,0,0xFFFFFF;
		viewpoint 2,1,1,1,0xFFFFFF;
		viewpoint 2,1,1,2,0xFFFFFF;
		viewpoint 2,1,1,3,0xFFFFFF;
		close;
	case 6:
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "君の故郷で流行してる競技はあるお？";
		mes "教えてくれお！";
		close;
	}
OnTouch:
	if(ASH_1QUE < 100) {
		end;
	}
	if(checkquest(71180)&0x8 == 0) {
		if(BIF_1QUE == 0)
			setquest 71182;
		if(BIF_2QUE == 0)
			setquest 71184;
		if(BIF_3QUE == 0)
			setquest 71186;
		if(BIF_4QUE == 0)
			setquest 71188;
		setquest 71190;
		setquest 71192;
		setquest 71194;
		if(BIF_5QUE == 0)
			setquest 71196;
		setquest 71180;
		compquest 71180;
		mes "[案内員ラプオ]";
		mes "ラオ～！";
		mes "レシア族の街モーラへようこそ！";
		mes "歓迎するお！";
		emotion 12;
		next;
		mes "[案内員ラプオ]";
		mes "さてさて、";
		mes "行きたい場所があれば";
		mes "ラプオが案内するお！";
		close;
	}
	end;
OnInit:
	waitingroom "街案内",0;
	end;
}

//============================================================
// 旅館
//------------------------------------------------------------
mora.gat,43,127,3	script	旅館の主#mora	522,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[旅館の主]";
		mes "おや、あなたは";
		mes "人間の集団の連合軍なんたらに";
		mes "所属していないようですね。";
		mes "所属したらまた来てください。";
		next;
		mes "‐サービスを受けるには";
		mes "　異世界クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	mes "[旅館の主]";
	mes "おや、いらっしゃいませ。";
	mes "私の旅館へようこそ。";
	next;
	switch(select("位置セーブを頼む","宿泊する","雑談する","倉庫について聞く")) {
	case 1:
		mes "[旅館の主]";
		mes "はい、セーブしました。";
		mes "これで何かあっても安心ですよ。";
		savepoint "mora.gat",57,142;
		close;
	case 2:
		mes "[旅館の主]";
		mes "宿泊ですね。";
		mes "5000zenyになりますが";
		mes "よろしいですか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[旅館の主]";
			mes "もし、お疲れでしたら";
			mes "街の中央にある温泉に";
			mes "行ってはいかがでしょう？";
			mes "疲れがとれるいいお湯ですよ。";
			close;
		}
		if(Zeny < 5000) {
			mes "[旅館の主]";
			mes "おや、料金が足らないようです。";
			mes "申し訳ありませんが";
			mes "宿泊できません。";
			close;
		}
		mes "[旅館の主]";
		mes "それでは、ごゆっくりどうぞ。";
		close2;
		set Zeny,Zeny-5000;
		warp "mora.gat",32,123;
		percentheal 100,100;
		end;
	case 3:
		mes "[旅館の主]";
		mes "異種族交流ですね。";
		mes "あなたはどちらから";
		mes "この街へいらっしゃったんですか？";
		next;
		input '@str$;
		mes "["+strcharinfo(0)+"]";
		mes "自分は";
		mes '@str$+ "から";
		mes "この街へきました。";
		next;
		mes "[旅館の主]";
		mes "ほお、そんな場所があるのですか！";
		next;
		mes "‐あなたは旅館の主と";
		mes "　心ゆくまで雑談した‐";
		close;
	case 4:
		mes "[旅館の主]";
		mes "倉庫ですね。";
		mes "それなら、私の右にある";
		mes "野菜模様の引き出しになります。";
		close;
	}
OnInit:
	waitingroom "旅館",0;
	end;
}

mora.gat,48,128,3	script	倉庫	844,{
	mes "‐野菜模様のひきだしに";
	mes "　小さな文字で、";
	mes "　^FF0000倉庫利用100Zeny^000000と";
	mes "　刻まれている‐";
	next;
	if(select("倉庫を利用する -> 100zeny","何もしない") == 2) {
		mes "‐今はやめておこう‐";
		close;
	}
	if(Zeny < 100) {
		mes "‐お金が足りない‐";
		close;
	}
	mes "‐ひきだしが開いた‐";
	close2;
	set Zeny,Zeny-100;
	openstorage;
	end;
}

//============================================================
// 矢筒作成
//------------------------------------------------------------
mora.gat,106,117,3	script	矢筒職人#mora	516,{
	if(checkitemblank() == 0) {
		mes "[矢筒職人]";
		mes "あれ？";
		mes "荷物の種類が多いみたいだね。";
		mes "それでは僕と取引できないよ。";
		close;
	}
	mes "[矢筒職人]";
	mes "モーラの街の人たちは";
	mes "矢筒などいらないと言うが";
	mes "それは世の中を知らないから";
	mes "言っているにすぎない。";
	next;
	mes "[矢筒職人]";
	mes "手を伸ばせばすぐそこに";
	mes "矢の材料があるモーラの街じゃ";
	mes "無理もないことだがな。";
	next;
	if(select("矢筒を作ってください","矢筒とは？") == 2) {
		mes "[矢筒職人]";
		mes "一本の矢は軽くてかさばらないが、";
		mes "その数が数百、数千になれば";
		mes "丸太を一本持ち歩いているのと";
		mes "同じだ。";
		next;
		mes "[矢筒職人]";
		mes "しかし、矢を収める矢筒があれば";
		mes "重さ的にもスペース的にも";
		mes "随分と変わってくるはずだ。";
		next;
		mes "[矢筒職人]";
		mes "興味があるなら、";
		mes "私が誠心誠意に作成してあげよう。";
		close;
	}
	mes "[矢筒職人]";
	mes "了解だとも！";
	mes "いやあ、矢筒の必要性を";
	mes "わかってる人は久しぶりだ。";
	mes "私は^FF0000狩人^000000と^FF0000エルフ^000000の矢筒を";
	mes "作れるよ。";
	mes "どっちの矢筒が必要だい？";
	next;
	switch(select("エルフの矢筒","狩人の矢筒","作らない")) {
	case 1:
		set '@item,1773;
		set '@gain,12575;
		break;
	case 2:
		set '@item,1774;
		set '@gain,12576;
		break;
	case 3:
		mes "[矢筒職人]";
		mes "矢は、隣にいる道具商人から";
		mes "購入できるぞ。";
		close;
	}
	if(countitem('@item) < 500) {
		mes "[矢筒職人]";
		mes getitemname('@item)+ "を500本以上";
		mes "持ってくれば、";
		mes "矢筒を作ってあげるよ。";
		close;
	}
	mes "[矢筒職人]";
	mes getitemname('@gain)+ "だね。";
	mes getitemname('@item)+ "500本と^FF3131500zeny^000000で";
	mes "作ってあげるよ。";
	next;
	switch(select("作成可能なだけ作る","1個分だけ作る","やっぱり止める")) {
	case 1:
		set '@num,countitem('@item) / 500;
		if(Zeny < 500*'@num)
			set '@num,Zeny / 500;
		mes "所持している矢の本数: ^3131FF" +countitem('@item)+ "本^000000";
		mes "作成可能な矢筒の数: ^3131FF" +'@num+ "個^000000";
		mes "必要金額: ^3131FF" +(500*'@num)+ " zeny^000000";
		next;
		if(select("作る","作らない") == 2) {
			mes "[矢筒職人]";
			mes "そうか、残念だ。";
			close;
		}
		break;
	case 2:
		set '@num,1;
		break;
	case 3:
		mes "[矢筒職人]";
		mes "そうか、残念だ。";
		close;
	}
	if(Zeny < (500*'@num)) {
		mes "[矢筒職人]";
		mes "おや、金額が足らないよ。";
		mes "それじゃあ作れない。";
		close;
	}
	mes "[矢筒職人]";
	mes "はい、できたよ。";
	mes "そうだ。^3131FF注意^000000してほしいんだが";
	mes "^FF0000重量が70%越えてしまうと";
	mes "矢筒は使用できなくなる^000000。";
	mes "忘れちゃだめだよ。";
	set Zeny,Zeny-(500*'@num);
	delitem '@item,500*'@num;
	getitem '@gain,'@num;
	close;
OnInit:
	waitingroom "矢筒作成",0;
	end;
}

//============================================================
// 住民
//------------------------------------------------------------
mora.gat,52,138,5	script	ムンムン	516,{
	mes "[ムンムン]";
	mes "あっ！";
	mes "私は旅館の主ではありませんよ。";
	mes "私に宿泊料金払われても";
	mes "困りますから！";
	close;
}

mora.gat,160,123,3	script	ネムネム	517,{
	mes "[ネムネム]";
	mes "ビフロストに亀裂ができてから";
	mes "多くの旅人が訪れて";
	mes "この街はとてもにぎやかになったよ。";
	mes "君もその旅人の一人なんだろう？";
	next;
	switch(select("もちろんです！","ちがいます！")) {
	case 1:
		mes "[ネムネム]";
		mes "ブラ～ボ！";
		mes "だろうと思ったよ。";
		mes "ぜひ、君の旅話を";
		mes "聞かせてくれないか！";
		emotion 38;
		close;
	case 2:
		mes "[ネムネム]";
		mes "違うのかい？";
		mes "もしそうなら、話を";
		mes "聞かせてもらおうと思ったんだ。";
		mes "残念。";
		emotion 19,"";
		close;
	}
}

mora.gat,105,104,3	script	語り人	514,{
	mes "‐一人、声を張り上げて";
	mes "　物語を話す者がいる‐";
	next;
	mes "[ラプレドル]";
	mes "それで？";
	mes "それでどうなったんだ!?";
	next;
	mes "[語り人]";
	mes "うむ。事はとても深刻だった。";
	mes "男は泣き疲れて";
	mes "眠ってしまったがな。";
	next;
	mes "[ラプレドル]";
	mes "うんうん！";
	next;
	mes "[語り人]";
	mes "男の物語は";
	mes "その夢の中でも続いていたんだ！";
	next;
	mes "[語り人]";
	mes "……ところでそこの旅人さん。";
	mes "　";
	mes "‐語り人は";
	mes "　" +strcharinfo(0)+ "に";
	mes "　目線を向けた‐";
	next;
	mes "[語り人]";
	mes "あなたも話を聞くなら";
	mes "料金をくれたまえ。";
	emotion 19,"";
	close;
}

mora.gat,101,99,1	script	ランラン	518,{
	mes "[ランラン]";
	mes "ああ～っ";
	mes "こんなに続きが気になる話は";
	mes "生まれて初めて聞いたよ！";
	close;
}

mora.gat,105,100,1	script	グルグル	516,{
	mes "[グルグル]";
	mes "泣き疲れて、寝て起きて";
	mes "それでもまだ終わらない！";
	mes "どうしてどうして!?";
	mes "どうしてそんなことに？";
	close;
}

mora.gat,99,100,7	script	ラプレドル	515,{
	mes "[ラプレドル]";
	mes "コインならいくらでも払うよ！";
	mes "早く続きを！";
	mes "続きを話してくれ！";
	close;
}

mora.gat,98,104,5	script	悲しんでいるレシア族	516,{
	mes "[悲しんでいるレシア族]";
	mes "悲しい、とても悲しい！";
	mes "男に幸せは訪れないの？";
	mes "どうして！";
	close;
}

mora.gat,102,107,5	script	話を聞いているレシア族	517,{
	mes "[話を聞いているレシア族]";
	mes "ああ……興味がつきない。";
	mes "私がそんな目にあったら";
	mes "……どうすれば終わるの!?";
	close;
}

mora.gat,101,107,5	script	効果音を出すレシア族	518,{
	mes "[効果音を出すレシア族]";
	mes "ここで出すのは";
	mes "この音！";
	mes "おお～！";
	mes "おお～っ";
	mes "おおお～!!";
	close;
}

mora.gat,103,100,5	script	感激しているレシア族	518,{
	mes "[感激しているレシア族]";
	mes "おおお……";
	mes "まさかこんな素晴らしい物語を";
	mes "ここで聞けるなんて！";
	mes "感激だ……！";
	close;
}

mora.gat,123,94,7	script	旅行客	515,{
	mes "[旅行客]";
	mes "いきなり現れた亀裂のせいで";
	mes "この街から";
	mes "出られなくなってしまいました。";
	mes "はぁぁぁ……";
	close;
}

mora.gat,155,72,3	script	旅行客	513,{
	mes "[旅行客]";
	mes "モーラの街の雰囲気は";
	mes "とても素敵でしょう？";
	mes "このままこの街に";
	mes "定着してしまおうか悩んでしまいます。";
	close;
}

mora.gat,184,169,5	script	働き手	516,{
	mes "[働き手]";
	mes "霧の森を抜けて";
	mes "この街に訪れている人がいるそうよ。";
	mes "いったい誰かしら。";
	mes "会ってみたいわ。";
	close;
}

mora.gat,179,155,1	script	若輩者の働き手	516,{
	mes "[若輩者の働き手]";
	mes "オレはいつか";
	mes "霧の森を制覇して";
	mes "英雄になるんだ！";
	next;
	mes "[口の悪い働き手]";
	mes "すでにその森を通って";
	mes "旅人がこのモーラの街に";
	mes "来たじゃないか。";
	next;
	mes "[若輩者の働き手]";
	mes "……むむむ、";
	mes "それならその旅人こそ";
	mes "オレだと言ってやる！";
	next;
	mes "[口の悪い働き手]";
	mes "止めろ、";
	mes "お前はここで生まれて";
	mes "育ったじゃないか。";
	mes "街の者はみんな知ってるぞ。";
	next;
	mes "[若輩者の働き手]";
	mes "それもそうかあ……";
	close;
}

mora.gat,177,157,5	script	口の悪い働き手	518,{
	mes "[若輩者の働き手]";
	mes "オレはいつか";
	mes "霧の森を制覇して";
	mes "英雄になるんだ！";
	next;
	mes "[口の悪い働き手]";
	mes "すでにその森を通って";
	mes "旅人がこのモーラの街に";
	mes "来たじゃないか。";
	next;
	mes "[若輩者の働き手]";
	mes "……むむむ、";
	mes "それならその旅人こそ";
	mes "オレだと言ってやる！";
	next;
	mes "[口の悪い働き手]";
	mes "止めろ、";
	mes "お前はここで生まれて";
	mes "育ったじゃないか。";
	mes "街の者はみんな知ってるぞ。";
	next;
	mes "[若輩者の働き手]";
	mes "それもそうかあ……";
	close;
}

mora.gat,108,182,5	script	働き手	516,{
	mes "[働き手]";
	mes "霧の森には気をつけろよ。";
	mes "好奇心から向かった旅人たちが";
	mes "たくさん行方不明に";
	mes "なってるんだからさ。";
	close;
}

mora.gat,122,97,6	script	休んでいるレシア族	517,{
	mes "[休んでいるレシア族]";
	mes "街の中央にある温泉は";
	mes "モーラの街の象徴なんだ。";
	next;
	mes "[休んでいるレシア族]";
	mes "たまにただの水溜りだという";
	mes "馬鹿もいるけどね。";
	mes "その温泉は、傷を癒す";
	mes "すご～い効能がある。";
	next;
	mes "[休んでいるレシア族]";
	mes "君も行ってみな。";
	mes "傷の治りが早くなるからさ。";
	close;
}

mora.gat,174,171,0	script	倉庫職員ショップレ	518,{
	mes "[ショップレ]";
	mes "ちょっとお、誰だよ";
	mes "このハシゴ持ってきたの。";
	mes "これだと僕の足じゃ";
	mes "届かないじゃないか！";
	emotion 28;
	close;
}

mora.gat,113,185,4	script	読書中のレシア族	516,{
	mes "‐読書に没頭しているようだ‐";
	next;
	if(select("何の本かのぞき見る","邪魔をしては悪い") == 2) {
		mes "‐あなたは読書の邪魔に";
		mes "　ならないよう、静かに";
		mes "　その場を離れた‐";
		close;
	}
	mes "‐あなたはレシア族が持つ";
	mes "　本を背後からのぞき見た‐";
	next;
	mes "‐レシア族の小さな";
	mes "　朗読の声が聞こえてくる‐";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFセイレンはエレメスの家に";
	mes "遊びに行く途中だった。";
	mes "借りた本を返しに行くのも";
	mes "目的であったけれど。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFついで、エレメスの姉であるソリンに";
	mes "会えるかもという期待があった。";
	mes "セイレンは逸る気持ちを抑え、";
	mes "礼儀正しくエレメスの家の";
	mes "ドアを叩いた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFドン！　ドン！　ドン！";
	mes "セイレンです。エレメスはいますか？";
	mes "　";
	mes "ドン！　ドン！　ドン！^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF……";
	mes "　";
	mes "何の音も返ってこない。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF（あれ、留守かな？）";
	mes "セイレンは何気なく";
	mes "ドアノブに手をかけた。";
	mes "　";
	mes "軽い音を立てて、ドアが動いた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF（カギがかかっていない……";
	mes "それなのに、誰もいないのか？）";
	mes "セイレンは友の無用心さに";
	mes "不安を抱いた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF家の中からは";
	mes "何の音も聞こえてこない。";
	mes "（どうしよう……";
	mes "外で待ってみてもいいけど、";
	mes "ドアを開けてしまったし……）^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFセイレンは、悩んだ末に";
	mes "エレメスが帰って来るまで";
	mes "家の中で待たせてもらうことにした。";
	mes "空が雷雨の訪れを";
	mes "予告していたからだ。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF（あとで勝手に入ったことは謝ろう）";
	mes "セイレンは家に足を踏み入れた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF家の中は暗かった。";
	mes "その時初めて、セイレンは";
	mes "背後で聞こえてくるゴロゴロという";
	mes "空の不吉な音とは別に";
	mes "水の音がしていることに気づいた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF「……エレメスか？」";
	mes "セイレンは水の音がしてくる方へ";
	mes "足を向けた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF水音の出所はシャワー室だった。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFセイレンがシャワー室に";
	mes "到着したと同時に、";
	mes "そのドアが開いた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FF真っ白な湯気が周囲に広がり、";
	mes "その中心に人影がひとつ。";
	mes "セイレンは突然の遭遇に";
	mes "その場で凍り付いてしまっていた。^000000";
	next;
	mes "[読書中のレシア族]";
	mes "^0000FFタオルを掴んだその誰かの手は";
	mes "シャワーを終えたばかりだとわかる";
	mes "みずみずしさを^000000";
	next;
	mes "[読書中のレシア族]";
	mes "ぎゃあああ!!";
	emotion 23;
	next;
	mes "[読書中のレシア族]";
	mes "き、きき、君！　誰だ!!";
	mes "いつからここに!!";
	mes "人の読書を邪魔するなんて";
	mes "失礼だろう！";
	next;
	mes "‐レシア族は挙動不審に";
	mes "　読んでいた本を閉じた‐";
	close;
}

mora.gat,99,65,6	script	バナナ好きなレシア族	516,{
	mes "[バナナ好きなレシア族]";
	mes "ね、君";
	mes "バナナ好き？";
	next;
	switch(select("好き","嫌い")) {
	case 1:
		mes "[バナナ好きなレシア族]";
		mes "ほんと？";
		mes "わーい。バナナおいしいよねバナナ。";
		emotion 33;
		close;
	case 2:
		mes "[バナナ好きなレシア族]";
		mes "……こんなにおいしいのに。";
		emotion 32;
		close;
	}
}

mora.gat,30,128,4	script	休憩中の旅人	514,{
	mes "[旅人]";
	mes "モーラの街の旅館は、";
	mes "ここでも独特な内装で";
	mes "有名なんだ。";
	mes "きのこクローゼットに";
	mes "リンゴ衣装タンス、";
	mes "画期的と思うだろ？";
	next;
	if(select("思う","思わない") == 2) {
		mes "[旅人]";
		mes "ごめん、";
		mes "そう思っていたのは";
		mes "私だけのようだね。";
		close;
	}
	mes "[旅人]";
	mes "それを見るために";
	mes "来る価値があるよな。";
	close;
}

mora.gat,130,96,4	script	休憩中の旅人	513,{
	mes "[旅人]";
	mes "ここモーラの街のレシア族は";
	mes "みんな似た姿をしていて";
	mes "見分けるのが大変だ。";
	next;
	mes "[旅人]";
	mes "けれど、よく見れば";
	mes "彼らが素敵な個性を";
	mes "持っていることがわかるはずだよ。";
	mes "その個性を見つけるのも";
	mes "この街での楽しみ方の一つだ。";
	close;
}

mora.gat,43,113,4	script	負傷したレシア族	517,{
	mes "[負傷したレシア族]";
	mes "うううう……";
	mes "温泉にいたあれは";
	mes "一体なんだったんだろう……";
	mes "うう……いきなり攻撃してきた。";
	next;
	mes "[負傷したレシア族]";
	mes "凶暴な奴だ。";
	mes "君も温泉に行くなら";
	mes "気をつけろよ……";
	close;
}

mora.gat,168,161,4	script	倉庫職員ライブリ	513,{
	mes "[ライブリ]";
	mes "あっちにある旅館～";
	mes "あの旅館が私の物だったら～";
	next;
	mes "[ライブリ]";
	mes "あっちにある商店～";
	mes "あの商店も私の物だったら～";
	next;
	mes "[ライブリ]";
	mes "ここにある倉庫～";
	mes "その中にある物も全部～";
	mes "私の物だったら～";
	mes "私の物だったら～";
	next;
	mes "[ライブリ]";
	mes "あ～あ～";
	mes "お金がない……";
	emotion 28;
	close;
}

mora.gat,175,161,6	script	倉庫職員クオリタ	518,{
	mes "[クオリタ]";
	mes "ながーくのびた赤いクチバシ♪";
	mes "すーぐはずかし、赤いほお～";
	mes "まっすぐ飛んでく黒いはね～♪";
	emotion 40;
	next;
	mes "[クオリタ]";
	mes "……そんなアヒルが";
	mes "すごくほしいんだよね～";
	emotion 37;
	close;
}

mora.gat,140,186,3	script	レシア族の哲学者	517,{
	mes "[レシア族の哲学者]";
	mes "人によって、一つの言葉の解釈も";
	mes "まったく異なってしまう。";
	mes "それが異文化にあるもの同士なら";
	mes "なおさら。";
	next;
	mes "[レシア族の哲学者]";
	mes "しかし、それは";
	mes "理解を諦める理由には";
	mes "ならない。";
	close;
}

mora.gat,140,72,4	script	ちょっかいをかける旅人	513,{
	mes "[ちょっかいをかける旅人]";
	mes "やあ、そこの君。";
	mes "見ない姿かたちをしてるけど";
	mes "どこから来たんだい？";
	close;
}

mora.gat,138,72,6	script	問いかける旅人	513,{
	mes "[問いかける旅人]";
	mes "なあ、ちょっとちょっと";
	mes "私は今、答えを出せないでいるんだが";
	mes "君の意見を聞かせてくれないか。";
	next;
	if(select("話を聞く","話を聞かない") == 2) {
		mes "[問いかける旅人]";
		mes "あ、ちょ、";
		mes "ちょっと！";
		mes "　";
		mes "‐あなたは呼び止める声を無視して";
		mes "　その場を去った‐";
		close;
	}
	mes "[問いかける旅人]";
	mes "バラの母は息子が10人いる。";
	mes "長男はイチバラ、次男はニバラ、";
	mes "三男はサンバラ……";
	mes "九男はキュウバラ。";
	mes "こんな感じの名の息子たちが。";
	next;
	mes "[問いかける旅人]";
	mes "そこで聞きたい。";
	mes "十番目の息子は";
	mes "なんという名前だろう？";
	mes "私にはわからなくて。";
	next;
	switch(select("ジュウバラ","バラ","わからない")) {
	case 1:
		mes "[問いかける旅人]";
		mes "そうだよな。";
		mes "一番、二番、三番……";
		mes "ときてるんだから";
		mes "答えはジュウバラだよな！";
		next;
		mes "[問いかける旅人]";
		mes "……しかし、となると";
		mes "バラは誰だろう。";
		next;
		mes "[問いかける旅人]";
		mes "うーん……";
		close;
	case 2:
		mes "[問いかける旅人]";
		mes "……そうか！";
		mes "最初にバラの母とあって、";
		mes "長男から九男の名前が判明していたら";
		mes "残りはバラだよな！";
		next;
		mes "[問いかける旅人]";
		mes "あーすっきりした！";
		mes "答えてくれてありがとうな。";
		close;
	case 3:
		mes "[問いかける旅人]";
		mes "そうか、君もわからないか。";
		next;
		mes "[問いかける旅人]";
		mes "うーん……";
		mes "十番目の息子の名前は";
		mes "一体なんだろうか。";
		close;
	}
}

mora.gat,139,73,4	script	悩んでる旅人	513,{
	mes "[悩んでる旅人]";
	mes "うーん……";
	next;
	mes "[悩んでる旅人]";
	mes "遊びでつくった簡単な問題を";
	mes "どうして誰も答えられないんだ？";
	next;
	mes "[悩んでる旅人]";
	mes "問題に答えが出ているのに。";
	close;
}

mora.gat,139,179,5	script	モーラの街の住民	518,{
	mes "[モーラの街の住民]";
	mes "ぷう……ぷう……";
	mes "　";
	mes "‐かわいらしい寝息を立てている‐";
	close;
}

mora.gat,137,181,5	script	モーラの街の住民	524,{
	mes "[モーラの街の住民]";
	mes "グガー、グガー・・・・・・";
	mes "　";
	mes "‐大口を開けて寝ている‐";
	close;
}

mora.gat,136,183,3	script	モーラの街の住民	525,{
	mes "[モーラの街の住民]";
	mes "ウェイ……";
	mes "　";
	mes "君にたなびたいことがある……";
	mes "グーグー";
	mes "　";
	mes "‐寝言を言っているようだ‐";
	close;
}

mora.gat,134,180,5	script	モーラの街の住民	522,{
	mes "[モーラの街の住民]";
	mes "お菓子……";
	mes "オイラもだーい好きでゲス……";
	mes "むにゃむにゃ……";
	mes "　";
	mes "‐食べ物の夢を見ているようだ‐";
	close;
}

mora.gat,134,184,1	script	モーラの街の住民	516,{
	mes "[モーラの街の住民]";
	mes "パーティー……";
	mes "盛大にやろうぜ！……";
	mes "ムニャムニャ";
	mes "　";
	mes "‐いい夢を見ているようだ‐";
	close;
}

mora.gat,133,178,7	script	モーラの街の住民	524,{
	mes "[モーラの街の住民]";
	mes "……すすす";
	mes "　";
	mes "‐鼻が何かを求めて";
	mes "　動いている。";
	mes "　夢の中で何を探しているのだろう‐";
	close;
}

mora.gat,133,183,7	script	モーラの街の住民	518,{
	mes "[モーラの街の住民]";
	mes "むにゃむにゃ";
	mes "……お、応援、ありがとー!!";
	mes "むにゃ……";
	mes "　";
	mes "‐いい夢を見ているようだ‐";
	close;
}

mora.gat,131,181,1	script	モーラの街の住民	522,{
	mes "[モーラの街の住民]";
	mes "いやあ、哲学とは";
	mes "よく眠れる学問ですなあ。";
	mes "哲学者の話を聞いていると";
	mes "よく眠れるのです。";
	close;
}

//============================================================
// ビフロストクエスト
//- Registry -------------------------------------------------
// BIF_1QUE -> 0～181,182,183
// BIF_1QUE_POS -> 調査した茂みの位置
//------------------------------------------------------------
mid_camp.gat,148,222,4	script	テオレ#mora	865,3,3,{
	if(BaseLevel < 100) {
		mes "[テオレ]";
		mes "うあああああ!!!!";
		mes "終わりだ！";
		mes "私はもう終わりだ!!";
		next;
		mes "‐白いガウンを着た男が";
		mes "　自分の髪の毛を";
		mes "　かきむしっている‐";
		next;
		mes "[テオレ]";
		mes "もう救世主が来ない限り";
		mes "現状を打破することはできない……";
		next;
		mes "[テオレ]";
		mes "……遠くから私を見ている冒険者では";
		mes "助力を請おうにも、力量が足りない！";
		mes "ああっどこかにいないものか！";
		mes "私を助けてくれる勇者様あっ!!";
		next;
		mes "‐このクエストを進行するには";
		mes "　レベルが満たないようです。";
		mes "　^FF0000レベル100^000000になったら";
		mes "　再度話しかけてください‐";
		close;
	}
	if(YGG_1QUE < 100) {	//知恵の王の指輪クエスト未クリア
		mes "[テオレ]";
		mes "うあああああ!!!!";
		mes "終わりだ！";
		mes "私はもう終わりだ!!";
		next;
		mes "‐白いガウンを着た男が";
		mes "　自分の髪の毛を";
		mes "　かきむしっている‐";
		next;
		mes "[テオレ]";
		mes "誰か妖精の言葉を理解できる";
		mes "人はいないのか――!?";
		next;
		mes "‐知恵の王の指輪クエストを";
		mes "　クリアしたら、";
		mes "　テオレに話しかけよう‐";
		close;
	}
	switch(BIF_1QUE) {
	case 0:
		mes "[テオレ]";
		mes "うあああああ!!!!";
		mes "終わりだ！";
		mes "私はもう終わりだ!!";
		next;
		mes "‐白いガウンを着た男が";
		mes "　自分の髪の毛を";
		mes "　かきむしっている‐";
		next;
		mes "[テオレ]";
		mes "そこらの三歳児が書いたような報告書を";
		mes "どうして提出できるというんだ！";
		mes "うあああああ!!!!";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（叫んでいる男がいる。";
		mes "話しかけてみよう）";
		set BIF_1QUE,1;
		setquest 11182;
		delquest 71182;
		close;
	case 1:
		mes "[テオレ]";
		mes "うあああああ!!!!";
		mes "終わりだ！";
		mes "私はもう終わりだ!!";
		next;
		mes "‐白いガウンを着た男が";
		mes "　自分の髪の毛を";
		mes "　かきむしっている‐";
		next;
		if(select("話しかけてみる","うるさい") == 2) {
			mes "[テオレ]";
			mes "あっはいすみません！";
			mes "ごめんなさい！";
			mes "静かにします。";
			next;
			mes "‐白いガウンを着た男は";
			mes "　汗をかき、何度も頭をさげた‐";
			close;
		}
		mes "["+strcharinfo(0)+"]";
		mes "あの……";
		mes "そんなに髪をかきむしるのは";
		mes "よくないと思いますよ。";
		mes "落ち着いてください。";
		next;
		mes "[テオレ]";
		mes "ハッ!!";
		next;
		mes "[テオレ]";
		mes "……";
		next;
		mes "[テオレ]";
		mes "あああっ！";
		mes "　";
		mes "‐男はあなたを見て";
		mes "　突然、おおげさに天を仰いだ‐";
		next;
		mes "[テオレ]";
		mes "オーディン様フレイヤ様ヘル様！";
		mes "とりあえず神様!!";
		mes "ありがとうございますっ";
		mes "私を見捨てたりしては";
		mes "おられなかったのですね!!";
		next;
		mes "[テオレ]";
		mes "頑張って生きる人を";
		mes "天は捨てないんですね！";
		mes "このテオレ、";
		mes "希望を失わずに";
		mes "一生懸命生きていきます!!";
		next;
		mes "‐テオレは首を動かし、";
		mes "　あなたを見つめる‐";
		next;
		mes "[テオレ]";
		mes "冒険者様！";
		mes "いいえ、勇者様英雄様！";
		mes "今、お忙しいですか!?";
		mes "ぜひ私の話を聞いてください！";
		next;
		if(select("忙しい","話を聞く") == 1) {
			mes "[テオレ]";
			mes "……";
			mes "　";
			mes "‐テオレのテンションが";
			mes "　一瞬で下降した‐";
			next;
			mes "[テオレ]";
			mes "……それなら、仕方ないですよね。";
			mes "わたしは、";
			mes "少し旅に出ます。";
			mes "こんな冷たい世の中にはいられません。";
			next;
			mes "[テオレ]";
			mes "大丈夫。";
			mes "あなたを恨んだりなど";
			mes "していませんから。";
			close;
		}
		mes "[テオレ]";
		mes "ありがとうございます！";
		mes "ありがとうございます!!";
		next;
		mes "[テオレ]";
		mes "あっ申し遅れました！";
		mes "私はテオレ。";
		mes "バゼットティーブラック異文化研究所で";
		mes "働いています。";
		next;
		mes "[テオレ]";
		mes "今は、スプレンディッドに住む";
		mes "ラフィネ族の調査を";
		mes "一任されたのですが……";
		next;
		mes "[テオレ]";
		mes "ちょっとはりきり過ぎたのか";
		mes "ラフィネ族に避けられるように";
		mes "なってしまいまして……";
		next;
		mes "[テオレ]";
		mes "……";
		next;
		mes "[テオレ]";
		mes "報告書の提出期日は";
		mes "どんどん近づいてきているのに、";
		mes "必要な資料がそろっていないので";
		mes "教授ががっかりされる出来のものしか";
		mes "書けそうにないんです。";
		next;
		mes "[テオレ]";
		mes "ああっ！";
		mes "教授は私を信じて";
		mes "任せてくれたというのに!!";
		mes "テオレの恩知らず!!";
		next;
		mes "‐テオレは再び";
		mes "　おのれの髪を力いっぱい";
		mes "　むしってしまった‐";
		next;
		mes "[テオレ]";
		mes "はあはあ……";
		mes "……ふう。";
		mes "私の事情は以上です。";
		next;
		mes "[テオレ]";
		mes "私を助けてくださいませんか!?";
		mes "勇者様！";
		mes "もちろんお礼は用意しますから!!";
		next;
		if(select("助ける","助けない") == 2) {
			mes "[テオレ]";
			mes "ああああ……";
			mes "　";
			mes "‐テオレは力なく";
			mes "　地面に崩れ落ちた‐";
			next;
			mes "[テオレ]";
			mes "あなたは悪い人。";
			mes "私の心を揺るがして……";
			mes "……";
			close;
		}
		mes "[テオレ]";
		mes "勇者様最高!!";
		mes "この恩は絶対に忘れません！";
		mes "今日の日記にも書いて！";
		mes "報告書にももちろん書いて！";
		mes "故郷の母上への手紙にも書いて！";
		next;
		mes "[テオレ]";
		mes "研究所の同僚にも話して！";
		mes "ルーゲン様にも報告して!!";
		mes "そしてまた!!!!";
		mes "　";
		mes "‐テオレはテンション高く";
		mes "　叫んでいる‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（落ち着く頃合を見て";
		mes "また話しかけてみよう）";
		set BIF_1QUE,2;
		close;
	case 2:
		mes "‐どうやらテオレは落ち着きを";
		mes "　とり戻したようだ‐";
		next;
		mes "[テオレ]";
		mes "すみません。";
		mes "少し興奮してしまいました。";
		mes "反省します……";
		next;
		mes "[テオレ]";
		mes "あっ、でもいつもは";
		mes "こんなではないんですよ！";
		mes "今日は地獄から天国へ一度に";
		mes "行って来たような心持だったので!!";
		next;
		mes "[テオレ]";
		mes "……本題に戻りましょうか。";
		next;
		mes "[テオレ]";
		mes "最初に言っておきますけど、";
		mes "私が勇者様にお願いすることは";
		mes "まあ、それほど難しくないと";
		mes "思います。";
		next;
		mes "[テオレ]";
		mes "最近西の地域で、";
		mes "^FF0000武装もしないで何かを必死に探す";
		mes "非武装のラフィネ族^000000が";
		mes "出没しているとの噂もあります。";
		next;
		mes "[テオレ]";
		mes "今まではラフィネ族は";
		mes "そんな行動をとっていませんでした。";
		mes "^FF0000私は非武装のラフィネ族が";
		mes "何のために、何を探しているのかを";
		mes "調査したいんです^000000。";
		mes "きっと大きな理由があるはずです。";
		next;
		mes "[テオレ]";
		mes "実際、私もその";
		mes "非武装のラフィネ族に遭遇しました。";
		mes "すぐに逃げられてしまったので";
		mes "話すことはできませんでしたけど。";
		mes "茂みや水辺で必死に何かを";
		mes "探しているようでした。";
		next;
		mes "[テオレ]";
		mes "そのラフィネ族は、";
		mes "スプレンディッドに";
		mes "戻っていることでしょう。";
		next;
		menu "あとを追っていないのですか？",-;
		mes "[テオレ]";
		mes "あ……はあ……";
		next;
		mes "[テオレ]";
		mes "私はどうも仕事熱心な";
		mes "ところがあるみたいで……";
		next;
		mes "[テオレ]";
		mes "どうも熱くなりすぎちゃうんです。";
		mes "調査のためラフィネ族に";
		mes "取材をしすぎちゃって……";
		mes "それで、ちょっとラフィネ族に";
		mes "嫌がられちゃったみたいで……";
		next;
		mes "[テオレ]";
		mes "スプレンディッドへの立ち入りを";
		mes "禁止されたんです。実は。";
		mes "　";
		mes "……ははは！";
		next;
		mes "[テオレ]";
		mes "ラフィネ族は";
		mes "かわいらしい見た目に反して";
		mes "戦闘種族ですし……";
		mes "侵入する勇気は私にはありません。";
		next;
		mes "[テオレ]";
		mes "なので、勇者様。";
		mes "代わりに非武装のラフィネ族を";
		mes "調べてきてください。";
		next;
		mes "[テオレ]";
		mes "遭遇した途端、";
		mes "逃げられる可能性もあるので";
		mes "^0000FF出会った時にそのラフィネ族の特徴を";
		mes "しっかりと覚えれば^000000";
		mes "その後見つけられると思います。";
		next;
		mes "[テオレ]";
		mes "よろしくお願いします勇者様!!";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（スプレンディッドフィールド02に";
		mes "出没する、非武装のラフィネ族を";
		mes "探そう）";
		set BIF_1QUE,3;
		chgquest 11182,11183;
		close;
	case 3:
	case 4:
		mes "[テオレ]";
		mes "スプレンディッドの外に出没する";
		mes "非武装のラフィネ族を";
		mes "調べてきてください。";
		next;
		mes "[テオレ]";
		mes "遭遇した途端、";
		mes "逃げられる可能性もあるので";
		mes "^0000FF出会った時にそのラフィネ族の特徴を";
		mes "しっかりと覚えれば^000000";
		mes "その後見つけられると思います。";
		next;
		mes "[テオレ]";
		mes "嵐の前夜は静かという言葉がありますが";
		mes "今まさしくそんな気配を";
		mes "感じているのです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（スプレンディッドフィールド02に";
		mes "出没する、非武装のラフィネ族を";
		mes "探そう）";
		close;
	case 51:
	case 52:
	case 53:
		mes "[テオレ]";
		mes "非武装のラフィネ族がいた場所に";
		mes "小さな袋がですか？";
		next;
		mes "[テオレ]";
		mes "ふむ……";
		mes "やわらかい皮の素材、";
		mes "乾かした木に";
		mes "油をしみこませて作られた紐、";
		mes "人間、そしてサファ族が使用するには";
		mes "小さすぎるサイズ……";
		next;
		mes "[テオレ]";
		mes "確かにこれは";
		mes "ラフィネ族が使用するもので";
		mes "間違いないでしょう。";
		next;
		mes "[テオレ]";
		mes "それにしてもロマンですねえ。";
		mes "妖精の持つ袋。";
		mes "一体何が入っているのでしょうか。";
		next;
		mes "[テオレ]";
		mes "はっ！";
		mes "も、もしかして!!";
		mes "これはあれじゃないですかね!!";
		next;
		mes "[テオレ]";
		mes "ラフィネ族は、この小さな袋に";
		mes "空を飛ぶための粉と";
		mes "体を小さくする妖精の粉を";
		mes "一緒に入れているんじゃないですか！";
		mes "きっとそうだ！";
		next;
		mes "[テオレ]";
		mes "これは貴重な物ですね！";
		mes "これを使えば私も飛べるかも！";
		mes "やっほほ～い！";
		mes "これはすごい！";
		next;
		mes "[テオレ]";
		mes "そうだとすると、";
		mes "こんな貴重な物を落とした";
		mes "ラフィネ族の妖精は";
		mes "すごく困っているでしょうね。";
		next;
		mes "[テオレ]";
		mes "勇者様が届けてあげたら";
		mes "代わりにいろんな情報を";
		mes "教えてもらえるかも！";
		next;
		mes "[テオレ]";
		mes "……その前に！";
		next;
		mes "[テオレ]";
		mes "少しくらい中身を";
		mes "覗いてもいいですよね！";
		next;
		mes "[テオレ]";
		mes "ふふふっ";
		mes "子どもの頃はおとぎ話の妖精が";
		mes "窓から入ってきて、";
		mes "私に空を飛べる粉をふりかけてくれる！";
		mes "そんな妄想をしたものですよ！";
		next;
		mes "[テオレ]";
		mes "テテーン!!";
		mes "いでよ!!";
		mes "妖精の粉！";
		mes "　";
		mes "‐テオレは小さな袋を";
		mes "　開けて中を覗きこんだ‐";
		next;
		mes "[テオレ]";
		mes "……";
		mes "は、はふ……？";
		next;
		mes "[テオレ]";
		mes "袋の中身は……";
		mes "木の実……";
		mes "　";
		mes "と、葉っぱ!?";
		next;
		mes "[テオレ]";
		mes "……空を飛ぶ粉は？";
		mes "うああああ！";
		mes "私の童心に謝れ!!!!";
		next;
		mes "‐テオレは再び、";
		mes "　髪をむしりはじめた‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（スプレンディッドに行って";
		mes "小さな袋の持ち主を";
		mes "探してみよう）";
		if(BIF_1QUE == 51)
			set BIF_1QUE,61;
		else if(BIF_1QUE == 52)
			set BIF_1QUE,62;
		else if(BIF_1QUE == 53)
			set BIF_1QUE,63;
		chgquest 11185,11186;
		close;
	case 61:
	case 62:
	case 63:
		mes "[テオレ]";
		mes "すっすみません！";
		mes "今はちょっ……";
		mes "　";
		mes "うああっ";
		mes "あれがそろってない!!";
		next;
		mes "‐テオレは多忙のようだ‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（……^FF0000スプレンディッド^000000に";
		mes "^0000FF小さい袋^000000の持ち主を";
		mes "探しに行こう）";
		close;
	case 171:
	case 172:
	case 173:
		mes "[テオレ]";
		mes "勇者様!!";
		mes "やっと戻られたんですね！";
		mes "調査はどうでしたか!?";
		next;
		mes "‐あなたは";
		mes "　テオレに調査結果を報告した‐";
		next;
		mes "[テオレ]";
		mes "おおっ！";
		mes "うおぉぉ!!";
		mes "うわああああ!!";
		next;
		mes "[テオレ]";
		mes "さいっこう！";
		mes "これなら完璧な報告書を";
		mes "書けると思います!!";
		mes "ビフロストに現れた亀裂ですか!!";
		next;
		mes "[テオレ]";
		mes "これも全部勇者様のおかげ！";
		mes "この恩は一生！";
		mes "いいえ!!";
		mes "代々に渡って子孫に語り継ごうと";
		mes "思います!!!!";
		next;
		mes "[テオレ]";
		mes "……";
		mes "しかし、ラフィネ族は";
		mes "大変そうですね。";
		mes "食糧とか大丈夫でしょうかね？";
		mes "ちょっと、報告書と一緒に";
		mes "上に相談してみようかな。";
		next;
		mes "[テオレ]";
		mes "今回は本当に";
		mes "ありがとうございました。";
		mes "これ、お礼です！";
		if(checkitemblank() == 0) {
			next;
			mes "‐所持アイテムの種類数が多い為";
			mes "　報酬を受け取ることができません。";
			mes "　アイテムを整理してから、";
			mes "　再度調べてください‐";
			close;
		}
		if(checkre())
			getexp 500000,250000;
		else
			getexp 5000000,2500000;
		getitem 6380,5;
		if(BIF_1QUE == 171)
			set BIF_1QUE,181;
		else if(BIF_1QUE == 172)
			set BIF_1QUE,182;
		else if(BIF_1QUE == 173)
			set BIF_1QUE,183;
		setquest 201352;
		delquest 71146;
		next;
		mes "[テオレ]";
		mes "では、早速報告書をまとめます！";
		mes "うおおおおおお!!!!";
		mes "　";
		mes "‐テオレはものすごい速さで";
		mes "　ペンを走らせている‐";
		close;
	case 181:
	case 182:
	case 183:
		mes "[テオレ]";
		mes "どこまでも限界に挑戦！";
		mes "勇者様の調査結果で";
		mes "報告書はパーフェクトに";
		mes "仕上げますよっ!!";
		next;
		mes "[テオレ]";
		mes "うおおおお!!!!";
		mes "　";
		mes "‐テオレはものすごい速さで";
		mes "　ペンを走らせている‐";
		close;
	default:
		mes "[テオレ]";
		mes "すっすみません！";
		mes "今はちょっ……";
		mes "　";
		mes "うああっ";
		mes "あれがそろってない!!";
		next;
		mes "‐テオレは多忙のようだ‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（今は引き受けた依頼を";
		mes "解決するのが先だ）";
		close;
	}
OnTouch:
	if(BIF_1QUE == 0 && BaseLevel >= 100 && YGG_1QUE == 100) {
		mes "[テオレ]";
		mes "うあああああ!!!!";
		mes "終わりだ！";
		mes "私はもう終わりだ!!";
		next;
		mes "‐白いガウンを着た男が";
		mes "　自分の髪の毛を";
		mes "　かきむしっている‐";
		next;
		mes "[テオレ]";
		mes "そこらの三歳児が書いたような報告書を";
		mes "どうして提出できるというんだ！";
		mes "うあああああ!!!!";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（叫んでいる男がいる。";
		mes "話しかけてみよう）";
		set BIF_1QUE,1;
		setquest 11182;
		delquest 71182;
		close;
	}
	end;
}

spl_fild02.gat,0,0,0	script	茂み#mora	844,{
	switch(BIF_1QUE) {
	case 3:
		if(rand(6)) {
			mes "‐ガサゴソッ……";
			mes "　";
			mes "　何かの気配を感じる。";
			mes "　^FF0000もう一度調べよう^000000‐";
			close;
		}
		switch(rand(3)) {
		case 0:
			set '@type,1;
			break;
		case 1:
			set '@type,2;
			break;
		case 2:
			set '@type,3;
			break;
		}
		mes "[非武装のラフィネ族]";
		mes "きゃあぁぁぁぁぁ!!!!!!";
		set BIF_1QUE,40+'@type;
		set '@name$,strnpcinfo(2);
		if('@name$ == "mora1")
			set BIF_1QUE_POS,1;
		else if('@name$ == "mora2")
			set BIF_1QUE_POS,2;
		else if('@name$ == "mora3")
			set BIF_1QUE_POS,3;
		else if('@name$ == "mora4")
			set BIF_1QUE_POS,4;
		else if('@name$ == "mora5")
			set BIF_1QUE_POS,5;
		else if('@name$ == "mora6")
			set BIF_1QUE_POS,6;
		chgquest 11183,71100;
		donpcevent "妖精#mora" +BIF_1QUE_POS+ "-" +'@type+ "::OnStart";
		next;
		mes "‐茂みの中にいた";
		switch(BIF_1QUE) {
		case 41:
			mes "　^ff8000金色の髪の毛^000000、^ffa020白い肌色^000000";
			mes "　^400040紫の服^000000で^404000二枚羽根^000000のラフィネ族は";
			break;
		case 42:
			mes "　^008000緑色の髪の毛^000000、^c05800濃い肌色^000000";
			mes "　^ffa020白い服^000000で^808000丸い羽根^000000のラフィネ族は";
			break;
		case 43:
			mes "　^0000ff水色の髪の毛^000000、^c05800濃い肌色^000000";
			mes "　^008000緑の服^000000で^e00000個性ある羽根^000000のラフィネ族は";
			break;
		}
		mes "　あなたを見るなり、";
		mes "　悲鳴をあげて飛び去ってしまった‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（茂みで何をしていたのだろう？";
		mes "^FF0000もう一度茂みを調べてみよう^000000）";
		close;
	case 41:
	case 42:
	case 43:
		if("mora" +BIF_1QUE_POS != strnpcinfo(2)) {
			mes "‐茂みがある‐";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐所持アイテムの種類数が多い為";
			mes "　報酬を受け取ることができません。";
			mes "　アイテムを整理してから、";
			mes "　再度調べてください‐";
			close;
		}
		mes "‐あなたは";
		mes "　ラフィネ族のいた茂みの中を";
		mes "　調べてみた‐";
		next;
		mes "‐……‐";
		next;
		if(rand(6)) {
			mes "‐何も見つからなかった。";
			mes "　^FF0000もう一度調べよう^000000‐";
			close;
		}
		mes "‐^FF0000小さな袋^000000を見つけた。";
		mes "　さきほどのラフィネ族が";
		mes "　落としたものだろうか‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（テオレに報告しよう）";
		if(BIF_1QUE == 41)
			set BIF_1QUE,51;
		else if(BIF_1QUE == 42)
			set BIF_1QUE,52;
		else if(BIF_1QUE == 43)
			set BIF_1QUE,53;
		chgquest 71100,11185;
		getitem 6390,1;
		close;
	case 51:
	case 52:
	case 53:
	case 61:
	case 62:
	case 63:
		if("mora" +BIF_1QUE_POS != strnpcinfo(2)) {
			mes "‐茂みがある‐";
			close;
		}
		mes "["+strcharinfo(0)+"]";
		mes "（テオレに報告しよう）";
		close;
	default:
		mes "‐茂みがある‐";
		close;
	}
}

spl_fild02.gat,0,0,0	script	妖精#mora	844,{
	end;
OnStart:
	initnpctimer;
	hideoffnpc strnpcinfo(0);
	end;
OnTimer5000:
	stopnpctimer;
OnInit:
	hideonnpc strnpcinfo(0);
	end;
}

spl_fild02.gat,79,104,0		duplicate(茂み#mora)	茂み#mora1		111
spl_fild02.gat,79,104,6		duplicate(妖精#mora)	妖精#mora1-1	440
spl_fild02.gat,79,104,6		duplicate(妖精#mora)	妖精#mora1-2	445
spl_fild02.gat,79,104,6		duplicate(妖精#mora)	妖精#mora1-3	439

spl_fild02.gat,103,344,0	duplicate(茂み#mora)	茂み#mora2		111
spl_fild02.gat,103,344,6	duplicate(妖精#mora)	妖精#mora2-1	440
spl_fild02.gat,103,344,6	duplicate(妖精#mora)	妖精#mora2-2	445
spl_fild02.gat,103,344,6	duplicate(妖精#mora)	妖精#mora2-3	439

spl_fild02.gat,261,323,0	duplicate(茂み#mora)	茂み#mora3		111
spl_fild02.gat,261,323,6	duplicate(妖精#mora)	妖精#mora3-1	440
spl_fild02.gat,261,323,6	duplicate(妖精#mora)	妖精#mora3-2	445
spl_fild02.gat,261,323,6	duplicate(妖精#mora)	妖精#mora3-3	439

spl_fild02.gat,137,305,0	duplicate(茂み#mora)	茂み#mora4		111
spl_fild02.gat,137,305,6	duplicate(妖精#mora)	妖精#mora4-1	440
spl_fild02.gat,137,305,6	duplicate(妖精#mora)	妖精#mora4-2	445
spl_fild02.gat,137,305,6	duplicate(妖精#mora)	妖精#mora4-3	439

spl_fild02.gat,23,196,0		duplicate(茂み#mora)	茂み#mora5		111
spl_fild02.gat,23,196,6		duplicate(妖精#mora)	妖精#mora5-1	440
spl_fild02.gat,23,196,6		duplicate(妖精#mora)	妖精#mora5-2	445
spl_fild02.gat,23,196,6		duplicate(妖精#mora)	妖精#mora5-3	439

spl_fild02.gat,186,260,0	duplicate(茂み#mora)	茂み#mora6		111
spl_fild02.gat,186,260,6	duplicate(妖精#mora)	妖精#mora6-1	440
spl_fild02.gat,186,260,6	duplicate(妖精#mora)	妖精#mora6-2	445
spl_fild02.gat,186,260,6	duplicate(妖精#mora)	妖精#mora6-3	439

splendide.gat,183,117,4	script	疲れ気味の妖精	438,{
	if(!equippeditem(2782)) {
		mes "[疲れ気味の妖精]";
		mes "VeOsaRiveh No ModAsh";
		mes "　";
		mes "‐言葉が通じない。";
		mes "　通訳をしてくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 61:
	case 62:
	case 63:
		mes "[疲れ気味の妖精]";
		mes "対応が面倒だから";
		mes "話しかけないでくれる？";
		mes "疲れてくたくたなの私。";
		next;
		menu "小さな袋を見せてみる",-;
		mes "[疲れ気味の妖精]";
		mes "……あっ!!";
		mes "　";
		mes "ちょっとちょっと";
		mes "それを何処で手に入れたの!?";
		next;
		menu "拾いました",-;
		mes "[疲れ気味の妖精]";
		mes "拾っただって!?";
		mes "まったく……";
		mes "誰が落としたの。";
		mes "大事ってわかってるはずなのに！";
		next;
		mes "[疲れ気味の妖精]";
		mes "……あ、";
		mes "えっとその袋さ。";
		mes "君には大した物に見えないと思うけど";
		mes "私たちには、かなり大事な物なのね。";
		next;
		mes "[疲れ気味の妖精]";
		mes "だからできたら";
		mes "落とし主に届けるべきなの。";
		next;
		mes "[疲れ気味の妖精]";
		mes "でも、その袋だけじゃ";
		mes "持ち主を特定できないのね。";
		if(BIF_1QUE == 61)
			set BIF_1QUE,71;
		else if(BIF_1QUE == 62)
			set BIF_1QUE,72;
		else if(BIF_1QUE == 63)
			set BIF_1QUE,73;
		set BIF_1QUE_POS,0;
		//setquest 11187;
		//delquest 11187;
		next;
		mes "[疲れ気味の妖精]";
		mes "う～ん、どうしたものかしらね。";
		next;
	case 71:
	case 72:
	case 73:
		mes "[疲れ気味の妖精]";
		mes "せめて持ち主の特徴が";
		mes "わかればいいんだけど。";
		next;
		switch(select("持ち主らしき者は見ている","考えてみます","持ち主の特徴を思い出す")) {
		case 1:
			mes "[疲れ気味の妖精]";
			mes "あら、そうなの。";
			mes "どんな容姿だったか覚えてる？";
			next;
			setarray '@sel1$[1],"^ff8000金色の髪の毛^000000","^008000緑色の髪の毛^000000","^803000茶色の髪の毛^000000","^0000ff水色の髪の毛^000000";
			setarray '@sel2$[1],"^c05800濃い肌色^000000","^ffa020白い肌色^000000";
			setarray '@sel3$[1],"^ffa020白い服^000000","^400040紫の服^000000","^0000ff水色の服^000000","^008000緑の服^000000";
			setarray '@sel4$[1],"^808000丸い羽根^000000","^404000二枚羽根^000000","^e00000個性ある羽根^000000";

			set '@sec1,select('@sel1$[1],'@sel1$[2],'@sel1$[3],'@sel1$[4]);
			set '@sec2,select('@sel2$[1],'@sel2$[2]);
			set '@sec3,select('@sel3$[1],'@sel3$[2],'@sel3$[3],'@sel3$[4]);
			set '@sec4,select('@sel4$[1],'@sel4$[2],'@sel4$[3]);
			mes "[疲れ気味の妖精]";
			mes '@sel1$['@sec1]+ "で" +'@sel2$['@sec2];
			mes '@sel3$['@sec3]+ "に" +'@sel4$['@sec4]+ "といえば……";
			set '@total,'@total + '@sec1 * 1000;
			set '@total,'@total + '@sec2 * 100;
			set '@total,'@total + '@sec3 * 10;
			set '@total,'@total + '@sec4 * 1;
			switch('@total) {
			case 1222:
				if(BIF_1QUE != 71) {
					mes "クスミのことかな。";
					next;
					mes "[疲れ気味の妖精]";
					mes "でも、クスミはちゃんと";
					mes "袋を持っていたわ！";
					mes "だから、クスミじゃない。";
					mes "見間違いじゃないの？";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "（容姿を間違えて伝えたようだ。";
					mes "あの妖精の容姿を思い出そう）";
					close;
				}
				mes "^FF0000クスミ^000000のことかな。";
				next;
				mes "[疲れ気味の妖精]";
				mes "クスミだったら";
				mes "街の^FF0000南西^000000にいるはず。";
				mes "袋を落としたのか";
				mes "聞いてみなよ。";
				set BIF_1QUE,81;
				delquest 11186;
				setquest 71130;
				close;
			case 2111:
				if(BIF_1QUE != 72) {
					mes "テオドのことかな。";
					next;
					mes "[疲れ気味の妖精]";
					mes "でも、テオドはちゃんと";
					mes "袋を持っていたわ！";
					mes "だから、テオドじゃない。";
					mes "見間違いじゃないの？";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "（容姿を間違えて伝えたようだ。";
					mes "あの妖精の容姿を思い出そう）";
					close;
				}
				mes "^FF0000テオド^000000のことかな。";
				next;
				mes "[疲れ気味の妖精]";
				mes "テオドだったら";
				mes "街の^FF0000北東^000000にいるはず。";
				mes "袋を落としたのか";
				mes "聞いてみなよ。";
				set BIF_1QUE,82;
				delquest 11186;
				setquest 71135;
				close;
			case 4143:
				if(BIF_1QUE != 73) {
					mes "ポションのことかな。";
					next;
					mes "[疲れ気味の妖精]";
					mes "でも、ポションはちゃんと";
					mes "袋を持っていたわ！";
					mes "だから、ポションじゃない。";
					mes "見間違いじゃないの？";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "（容姿を間違えて伝えたようだ。";
					mes "あの妖精の容姿を思い出そう）";
					close;
				}
				mes "^FF0000ポション^000000のことかな。";
				next;
				mes "[疲れ気味の妖精]";
				mes "ポションだったら";
				mes "街の^FF0000北^000000にいるはず。";
				mes "袋を落としたのか";
				mes "聞いてみなよ。";
				set BIF_1QUE,83;
				delquest 11186;
				setquest 71140;
				close;
			default:
				next;
				mes "[疲れ気味の妖精]";
				mes "ん……";
				mes "そんなやついたかな。";
				mes "見間違いじゃないの？";
				mes "もう一度、考えてみて。";
				close;
			}
		case 2:
			mes "[疲れ気味の妖精]";
			mes "じゃ、なにか思い出したら";
			mes "私に話してちょうだい。";
			close;
		case 3:
			mes "["+strcharinfo(0)+"]";
			mes "（思い出してみせる……!!）";
			next;
			mes "…";
			next;
			mes "……";
			next;
			mes "………";
			next;
			switch(BIF_1QUE) {
			case 71:
				setarray '@replay$,"^ff8000金色の髪の毛^000000","^ffa020白い肌色^000000","^400040紫の服^000000","^404000二枚羽根^000000";
				break;
			case 72:
				setarray '@replay$,"^008000緑色の髪の毛^000000","^c05800濃い肌色^000000","^ffa020白い服^000000","^808000丸い羽根^000000";
				break;
			case 73:
				setarray '@replay$,"^0000ff水色の髪の毛^000000","^c05800濃い肌色^000000","^008000緑の服^000000","^e00000個性ある羽根^000000";
				break;
			}
			mes "["+strcharinfo(0)+"]";
			mes "そうだ！";
			mes "あのラフィネ族は";
			mes '@replay$[rand(4)]+ "だった!!";
			emotion 5,"";
			close;
		}
	case 81:
		mes "[疲れ気味の妖精]";
		mes "^ff8000金色の髪の毛^000000で^ffa020白い肌色^000000";
		mes "^400040紫の服^000000に^404000二枚羽根^000000といえば……";
		mes "^FF0000クスミ^000000のことかな。";
		next;
		mes "[疲れ気味の妖精]";
		mes "クスミだったら";
		mes "街の^FF0000南西^000000にいるはず。";
		mes "袋を落としたのか";
		mes "聞いてみなよ。";
		close;
	case 82:
		mes "[疲れ気味の妖精]";
		mes "^008000緑色の髪の毛^000000で^c05800濃い肌色^000000";
		mes "^ffa020白い服^000000に^808000丸い羽根^000000といえば……";
		mes "^FF0000テオド^000000のことかな。";
		next;
		mes "[疲れ気味の妖精]";
		mes "テオドだったら";
		mes "街の^FF0000北東^000000にいるはず。";
		mes "袋を落としたのか";
		mes "聞いてみなよ。";
		close;
	case 83:
		mes "[疲れ気味の妖精]";
		mes "^0000ff水色の髪の毛^000000で^c05800濃い肌色^000000";
		mes "^008000緑の服^000000に^e00000個性ある羽根^000000といえば……";
		mes "^FF0000ポション^000000のことかな。";
		next;
		mes "[疲れ気味の妖精]";
		mes "ポションだったら";
		mes "街の^FF0000北^000000にいるはず。";
		mes "袋を落としたのか";
		mes "聞いてみなよ。";
		close;
	default:
		mes "[疲れ気味の妖精]";
		mes "対応が面倒だから";
		mes "話しかけないでくれる？";
		close;
	}
}

splendide.gat,119,138,4	script	クスミ	440,{
	if(!equippeditem(2782)) {
		mes "[クスミ]";
		mes "DimFusTal Mu Lars";
		mes "ModAnduLo";
		mes "Mod";
		mes "DorDuMe U NohLarsFulo Mu Fus";
		next;
		mes "‐言葉が通じない。";
		mes "　通訳してくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 61:
	case 62:
	case 63:
	case 71:
	case 72:
	case 73:
	case 82:
	case 83:
		mes "[クスミ]";
		mes "どなた？";
		mes "私になにか？";
		next;
		menu "小さな袋を見せる",-;
		mes "[クスミ]";
		mes "なんですかそれは！";
		mes "誰だか知らないけど、";
		mes "そんな大事なものを人間の手に";
		mes "渡すなんて！";
		next;
		mes "[クスミ]";
		mes "えっ私のもの？";
		mes "そんなはずありません！";
		mes "自分のはちゃんと持ってますねん！";
		close;
	case 81:
		mes "[クスミ]";
		mes "どなた？";
		mes "私になにか？";
		next;
		menu "小さな袋を見せる",-;
		mes "[クスミ]";
		mes "あっそれ私の袋!!";
		next;
		mes "[クスミ]";
		mes "ずっと探してたのですねん。";
		mes "あなたが";
		mes "見つけてくれてたのですね！";
		mes "ありがとうございます!!";
		next;
		mes "[クスミ]";
		mes "あれ、";
		mes "でもこれを落としたのって……";
		next;
		mes "[クスミ]";
		mes "……もしかして、";
		mes "あの場所で遭遇したのは";
		mes "あなた、でした？";
		next;
		menu "はい",-;
		mes "‐あなたはうなずき、";
		mes "　クスミにあの場所を";
		mes "　武装もせずに出歩いていた理由を";
		mes "　たずねた‐";
		next;
		mes "[クスミ]";
		mes "あ、あー";
		mes "それはまた困った質問を";
		mes "されてしまいましたねん。";
		next;
		mes "[クスミ]";
		mes "でも、あなたは";
		mes "わざわざ私に落とし物を";
		mes "届けてくれたし……";
		next;
		mes "[クスミ]";
		mes "……ううう。";
		next;
		mes "[クスミ]";
		mes "わ、わかりました答えましょう！";
		mes "ですが、この話は";
		mes "内密にお願いしますねん。";
		next;
		mes "[クスミ]";
		mes "その約束を守れるなら";
		mes "もう一度、話しかけてくださいねん。";
		delitem 6390, 1;
		set BIF_1QUE,91;
		delquest 71130;
		setquest 11188;
		close;
	case 91:
		mes "[クスミ]";
		mes "約束を守ってくれるんですねん？";
		mes "それなら話しましょう。";
		next;
		mes "[クスミ]";
		mes "実は最近……";
		mes "本国から補給物資が";
		mes "届いてないんですねん！";
		next;
		mes "[クスミ]";
		mes "まだ飢えるまでは";
		mes "行ってないんですけどねん。";
		mes "備蓄がなくなる前に";
		mes "食料を見つけようと";
		mes "私は外に出てたのです。";
		next;
		mes "[クスミ]";
		mes "もともとこの周辺は凍った地。";
		mes "食料が少ないのですねん。";
		next;
		mes "[クスミ]";
		mes "私たちの技術で、";
		mes "緑を増やしてはいますが、それだって";
		mes "現状を維持するのがやっと。";
		mes "食料を生産まで行くと、";
		mes "あまりにも非効率なんですよん。";
		next;
		mes "[クスミ]";
		mes "未だに上の人たちが";
		mes "動く気配をみせないですけど、";
		mes "戦争中に、この状況は";
		mes "まずいですよねえ。";
		next;
		mes "[クスミ]";
		mes "私だけでなく、";
		mes "仲間たちも不安なんですよ～";
		next;
		mes "[クスミ]";
		mes "納得いただけました？";
		mes "では、約束は守ってくださいね。";
		mes "協力者でもないのに、";
		mes "こんな事情を教えても";
		mes "私たちには何の利もありませんから。";
		next;
		mes "‐本国からスプレンディッドに";
		mes "　補給物資が届かなくなった……";
		mes "　これはとても重大な";
		mes "　案件ではないだろうか‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（もう少し詳しい事情を";
		mes "聞いてみよう……）";
		set BIF_1QUE,101;
		chgquest 11188,11189;
		close;
	case 101:
		mes "[クスミ]";
		mes "おや？";
		mes "まだ私にご用事でも？";
		next;
		menu "詳しい事情を聞く",-;
		mes "‐あなたは";
		mes "　本国から補給が届かない件の";
		mes "　詳しい話を聞かせてくれるよう";
		mes "　クスミに頼んだ‐";
		next;
		mes "[クスミ]";
		mes "い、いや、";
		mes "それは……";
		next;
		mes "[クスミ]";
		mes "私は話してもいいですけど、";
		mes "そこまで詳しい事情を知るからには";
		mes "あなたに協力してもらわないと";
		mes "いけなくなりますねん。";
		next;
		mes "[クスミ]";
		mes "それでも知りたいと";
		mes "いうんですか？";
		next;
		if(select("話を聞く","やめる") == 2) {
			mes "[クスミ]";
			mes "それが賢明ですよん。";
			mes "……まー";
			mes "手伝ってくれたら";
			mes "私たちは大助かりですが。";
			close;
		}
		mes "[クスミ]";
		mes "あらら。";
		mes "好奇心は身を滅ぼしますよん。";
		mes "まあ、お話しましょう。";
		next;
		mes "[クスミ]";
		mes "私たちの周りでは、";
		mes "補給が届かないのは";
		mes "本国から通じている通路に";
		mes "異変があったからと";
		mes "言われていますねん。";
		next;
		mes "[クスミ]";
		mes "補給路は一ルートしか";
		mes "ありませんから、";
		mes "そこがつぶれてしまったら";
		mes "まあ行き来できなくなって";
		mes "しまうでしょうね。";
		next;
		mes "[クスミ]";
		mes "さあ、話しましたよ。";
		mes "あなたには、補給路に";
		mes "何があったのか調べるのを";
		mes "協力してほしいですねん。";
		next;
		mes "[クスミ]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいったんです。";
		mes "そろそろ戻ってくるはずですねん。";
		next;
		mes "[クスミ]";
		mes "彼を捜して調査結果を";
		mes "聞いてほしいですねん。";
		next;
		mes "[クスミ]";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道がありますので";
		mes "そこに行ってください。";
		mes "兵士が戻ってくるはずですねん。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		set BIF_1QUE,111;
		setquest 11190;
		delquest 11189;
		close;
	case 111:
		mes "[クスミ]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいったんです。";
		mes "そろそろ戻ってくるはずですねん。";
		next;
		mes "[クスミ]";
		mes "彼を捜して調査結果を";
		mes "聞いてほしいですねん。";
		next;
		mes "[クスミ]";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道がありますので";
		mes "そこに行ってください。";
		mes "兵士が戻ってくるはずですねん。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		close;
	case 121:
		mes "[クスミ]";
		mes "なんと！";
		mes "補給路に亀裂ができていると!?";
		next;
		mes "[クスミ]";
		mes "なるほど。";
		mes "だから、本国との連絡が";
		mes "とれなくなってしまったですねん。";
		next;
		mes "‐あなたは霧の森を通るルートが";
		mes "　存在することを";
		mes "　クスミに伝えた‐";
		next;
		mes "[クスミ]";
		mes "ええっ!!";
		mes "霧の森ですか!?";
		mes "確かにそこを通ればいけるでしょうが、";
		mes "でも、あそこは……";
		next;
		mes "[クスミ]";
		mes "……";
		next;
		mes "[クスミ]";
		mes "まあ……";
		mes "いっか。";
		next;
		mes "[クスミ]";
		mes "あなたが";
		mes "霧の森を通って、";
		mes "ビフロストの状況を";
		mes "見てきてもよいかもしれません。";
		next;
		mes "[クスミ]";
		mes "ビフロストは";
		mes "不思議な力が働いている地域で、";
		mes "言葉が違う種族同士でも";
		mes "何故か^0000FF意志疎通^000000できますねん。";
		mes "言葉が通じるんですねん。";
		next;
		mes "[クスミ]";
		mes "そしてビフロストには^FF0000モーラ^000000という";
		mes "街がありまして、";
		mes "本国からの物資はみな";
		mes "その街を経由してやってきますねん。";
		next;
		mes "[クスミ]";
		mes "^0000FF霧の森^000000に入るためには";
		mes "スプレンディッドの";
		mes "北の地域ビフロストにいる";
		mes "^0000FF霧の森の監視兵^000000に話せば";
		mes "通してくれるはずですねん。";
		next;
		mes "[クスミ]";
		mes "でも大変危険な森だから";
		mes "気をつけてください。";
		mes "しかも巨大な竜が現れたって";
		mes "噂もありますし……";
		next;
		mes "[クスミ]";
		mes "……";
		mes "こんなことを頼むのも";
		mes "ずうずうしいのですが、";
		mes "もし、モーラに行くのであれば";
		mes "お願いがありますねん。";
		next;
		mes "[クスミ]";
		mes "モーラの物流倉庫に行って";
		mes "^0000FF物流倉庫の管理人^000000を";
		mes "助けてあげてほしいですねん。";
		next;
		mes "[クスミ]";
		mes "物流倉庫の管理人、";
		mes "きっと困ってますねん。";
		mes "こんなこと頼んで申し訳ないですけど、";
		mes "よろしくお願いしますねん。";
		set BIF_1QUE,131;
		delquest 11191;
		setquest 71145;
		close;
	case 131:
		mes "[クスミ]";
		mes "……";
		mes "こんなことを頼むのも";
		mes "ずうずうしいのですが、";
		mes "もし、モーラに行くのであれば";
		mes "お願いがありますねん。";
		next;
		mes "[クスミ]";
		mes "モーラの物流倉庫に行って";
		mes "^0000FF物流倉庫の管理人^000000を";
		mes "助けてあげてほしいですねん。";
		next;
		mes "[クスミ]";
		mes "物流倉庫の管理人、";
		mes "きっと困ってますねん。";
		mes "こんなこと頼んで申し訳ないですけど、";
		mes "よろしくお願いしますねん。";
		close;
	case 141:
	case 151:
	case 161:
	case 171:
	case 181:
		mes "[クスミ]";
		mes "いろいろと力を貸してくれて";
		mes "本当にありがとうですねん。";
		close;
	default:
		mes "[クスミ]";
		mes "はーあ。";
		mes "いくらこの地を整備しようとも";
		mes "まだまだ住みにくいです！";
		mes "楽園のような私の故郷とは";
		mes "ほんと、程遠いこと！";
		close;
	}
}

splendide.gat,304,295,4	script	テオド	445,{
	if(!equippeditem(2782)) {
		mes "[テオド]";
		mes "DimFusTal Mu Lars";
		mes "ModAnduLo";
		mes "Mod";
		mes "DorDuMe U NohLarsFulo Mu Fus";
		next;
		mes "‐言葉が通じない。";
		mes "　通訳してくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 61:
	case 62:
	case 63:
	case 71:
	case 72:
	case 73:
	case 81:
	case 83:
		mes "[テオド]";
		mes "誰だお前！";
		mes "俺に何の用だ！";
		next;
		menu "小さな袋を見せる",-;
		mes "[テオド]";
		mes "なんだその汚い袋は！";
		mes "そんなもの、俺";
		mes "持ってないぞ！";
		close;
	case 82:
		mes "[テオド]";
		mes "誰だお前！";
		mes "俺に何の用だ！";
		next;
		menu "小さな袋を見せる",-;
		mes "[テオド]";
		mes "あっそれは！";
		mes "俺のじゃないか!!";
		next;
		mes "[テオド]";
		mes "お、お前が見つけてくれたのか？";
		mes "あんなに探しても";
		mes "見つかんなかったのに。";
		next;
		mes "[テオド]";
		mes "……ん？";
		mes "いや、待て。";
		mes "お前、あの場所で";
		mes "俺を驚かせたやつだな!?";
		next;
		menu "はい",-;
		mes "‐あなたはうなずき、";
		mes "　テオドにあの場所を";
		mes "　武装もせずに出歩いていた理由を";
		mes "　たずねた‐";
		next;
		mes "[テオド]";
		mes "ん！";
		mes "的を射た質問だ！";
		next;
		mes "[テオド]";
		mes "だが、その質問に対する答えは";
		mes "スプレンディッドにいるラフィネ族に";
		mes "影響してしまう。";
		mes "俺にも決断の時間が必要だ。";
		next;
		mes "[テオド]";
		mes "お前が他の誰にも";
		mes "教えないって約束してくれるなら";
		mes "もう一度、俺に話しかけてくれ。";
		delitem 6390,1;
		set BIF_1QUE,92;
		delquest 71135;
		setquest 11194;
		close;
	case 92:
		mes "[テオド]";
		mes "他言は無用だぞ！";
		mes "では、話そう。";
		mes "俺が単身、スプレンディッドを";
		mes "出ていた理由を。";
		next;
		mes "[テオド]";
		mes "スプレンディッドでは";
		mes "大きな問題が発生している。";
		mes "本国からの連絡が";
		mes "途絶えたのだ。";
		next;
		mes "[テオド]";
		mes "それだけじゃない。";
		mes "食料、衣服、";
		mes "生きていくのに必要な";
		mes "物資の補給までもが";
		mes "届かなくなった！";
		next;
		mes "[テオド]";
		mes "この険しい地では、";
		mes "食料を手に入れることは";
		mes "とても難しい。";
		mes "俺も外に出て探したが";
		mes "成果は得られなかった。";
		next;
		mes "[テオド]";
		mes "……今の俺たちは、周辺の緑を";
		mes "維持するのがせいいっぱいなんだ。";
		mes "戦争も終わっていない。";
		next;
		mes "[テオド]";
		mes "この状況で、";
		mes "補給の話を周りに知られては";
		mes "まずいんだ。";
		next;
		mes "[テオド]";
		mes "だから、本当に他言無用で";
		mes "頼むぞ。";
		mes "お前は俺を助けてくれたから";
		mes "教えてやったんだからな！";
		next;
		mes "‐本国からスプレンディッドに";
		mes "　補給物資が届かなくなった……";
		mes "　これはとても重大な";
		mes "　案件ではないだろうか‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（もう少し詳しい事情を";
		mes "聞いてみよう……）";
		set BIF_1QUE,102;
		chgquest 11194,11195;
		close;
	case 102:
		mes "[テオド]";
		mes "なんだ。";
		mes "さっきの話じゃ";
		mes "お礼にならないとでも？";
		next;
		menu "詳しい事情を聞く",-;
		mes "[テオド]";
		mes "……お前を思って";
		mes "忠告してやるが、";
		mes "これ以上を聞くというなら";
		mes "面倒なことになるぞ。";
		next;
		mes "[テオド]";
		mes "それでも知りたいのか？";
		next;
		if(select("話を聞く","やめる") == 2) {
			mes "[テオド]";
			mes "まあ、誰も面倒ごとは";
			mes "ごめんだよな。";
			next;
			mes "[テオド]";
			mes "何度も言うけど、";
			mes "袋を見つけてくれてありがとよ。";
			close;
		}
		mes "[テオド]";
		mes "やれやれ。";
		mes "それじゃあ、この話を聞いたら";
		mes "お前にはいろいろ";
		mes "手伝ってもらうからな。";
		next;
		mes "[テオド]";
		mes "本国からの連絡、補給が";
		mes "途絶えたのは、";
		mes "補給路として使ってる道が";
		mes "つぶれたからって聞いてる。";
		next;
		mes "[テオド]";
		mes "誰に聞いたって？";
		next;
		mes "[テオド]";
		mes "仲間内ではこの噂で";
		mes "もちきりなのさ。";
		next;
		mes "[テオド]";
		mes "本国との補給路は、";
		mes "ビフロストが中継地点と";
		mes "なっている。";
		mes "ここに前線基地を作ったのも";
		mes "その補給路があったからだ。";
		next;
		mes "[テオド]";
		mes "その道は、かなり昔から";
		mes "各大陸をつなぐ橋として";
		mes "知られてるんだぜ。";
		next;
		mes "[テオド]";
		mes "……という訳で、";
		mes "お前にはその補給路が";
		mes "本当につぶれてしまったのか";
		mes "確認してほしい。";
		next;
		mes "[テオド]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいっているんだ。";
		mes "そろそろ戻ってくるはず。";
		next;
		mes "[テオド]";
		mes "その兵士から調査結果を";
		mes "聞いて来てほしい。";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道があるから";
		mes "そこに行ってくれ。";
		mes "兵士が戻ってくるはずだ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		set BIF_1QUE,112;
		chgquest 11195,11196;
		close;
	case 112:
		mes "[テオド]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいっているんだ。";
		mes "そろそろ戻ってくるはず。";
		next;
		mes "[テオド]";
		mes "その兵士から調査結果を";
		mes "聞いて来てほしい。";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道があるから";
		mes "そこに行ってくれ。";
		mes "兵士が戻ってくるはずだ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		close;
	case 122:
		mes "[テオド]";
		mes "補給路に亀裂だって？";
		mes "そりゃ、本国からの連絡も補給も";
		mes "なくなるはずだ！";
		next;
		mes "‐あなたは霧の森を通るルートが";
		mes "　存在することを";
		mes "　テオドに伝えた‐";
		next;
		mes "[テオド]";
		mes "霧の森に？";
		mes "でも、あそこは……";
		next;
		mes "[テオド]";
		mes "……まあ、お前なら";
		mes "大丈夫かな。";
		mes "大変だと思うけど。";
		next;
		mes "[テオド]";
		mes "本国からの物流は、";
		mes "ビフロストの中間にある";
		mes "^FF0000モーラ^000000という街を";
		mes "経由してるから";
		mes "そこにいけば状況がわかるはずだぜ。";
		next;
		mes "[テオド]";
		mes "一番正確な情報を得られるのは";
		mes "モーラで";
		mes "^0000FF物流倉庫を管理してる奴^000000だな。";
		mes "話を聞いてみるといい。";
		mes "モーラに行くためには、";
		mes "霧の森を通るといいだろう。";
		next;
		mes "[テオド]";
		mes "^0000FF霧の森^000000に入るためには";
		mes "スプレンディッドの";
		mes "北の地域ビフロストにいる";
		mes "^0000FF霧の森の監視兵^000000に話せば";
		mes "通してくれるはずだ。";
		next;
		mes "[テオド]";
		mes "ただ、最近、";
		mes "霧の森に紫色の竜が";
		mes "迷い込んだという噂を聞いた。";
		mes "気をつけた方がいいかもな。";
		next;
		mes "[テオド]";
		mes "そうそう、説明しておくが、";
		mes "ビフロストは";
		mes "不思議な力が働いている地域でな。";
		mes "言葉が違う種族同士でも";
		mes "何故か^0000FF意志疎通^000000ができるんだ。";
		next;
		mes "[テオド]";
		mes "だからモーラでも";
		mes "言葉が違うのに互いの話す言葉は";
		mes "理解できる。";
		mes "どういう原理かはわからないがな。";
		set BIF_1QUE,132;
		delquest 11197;
		setquest 71145;
		close;
	case 132:
		mes "[テオド]";
		mes "本国からの物流は、";
		mes "ビフロストの中間にある";
		mes "^FF0000モーラ^000000という街を";
		mes "経由してるから";
		mes "そこにいけば状況がわかるはずだぜ。";
		next;
		mes "[テオド]";
		mes "一番正確な情報を得られるのは";
		mes "モーラで";
		mes "^0000FF物流倉庫を管理してる奴^000000だな。";
		mes "話を聞いてみるといい。";
		mes "モーラに行くためには、";
		mes "霧の森を通るといいだろう。";
		close;
	case 142:
	case 152:
	case 162:
	case 172:
	case 182:
		mes "[テオド]";
		mes "ラフィネ族のために";
		mes "いろいろとしてくれて";
		mes "ありがとな。";
		mes "人間は優しい一族だな。";
		close;
	default:
		mes "[テオド]";
		mes "今日は風が気持ちいいな。";
		close;
	}
}

splendide.gat,168,301,4	script	ポション	439,{
	if(!equippeditem(2782)) {
		mes "[ポション]";
		mes "DimFusTal Mu Lars";
		mes "ModAnduLo";
		mes "Mod";
		mes "DorDuMe U NohLarsFulo Mu Fus";
		next;
		mes "‐言葉が通じない。";
		mes "　通訳してくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 61:
	case 62:
	case 63:
	case 71:
	case 72:
	case 73:
	case 81:
	case 82:
		mes "[ポション]";
		mes "あの……僕になにか？";
		next;
		menu "袋を見せる",-;
		mes "[ポション]";
		mes "あの……それは";
		mes "僕のじゃありません。";
		mes "僕、ちゃんと持ってます。";
		next;
		mes "[ポション]";
		mes "それにしてもそんな大事なものを";
		mes "落とすなんて。";
		mes "持ち主は、怒られた方が";
		mes "よさそうですね。";
		close;
	case 83:
		mes "[ポション]";
		mes "あの……僕になにか？";
		next;
		menu "袋を見せる",-;
		mes "[ポション]";
		mes "あっそれ僕のです。";
		mes "見つからなくて";
		mes "途方にくれてたんです！";
		next;
		mes "[ポション]";
		mes "わざわざ届けにまで";
		mes "きてくれて……";
		mes "本当にありがとうございます。";
		next;
		mes "[ポション]";
		mes "お恥ずかしい話ですが、";
		mes "街の外に出て";
		mes "なにかと遭遇した時に";
		mes "驚いて放り投げちゃったんです……";
		next;
		mes "[ポション]";
		mes "あれ、待って。";
		mes "その後に袋を持ってきたってことは……";
		next;
		mes "[ポション]";
		mes "あの。もしかして、";
		mes "あの場所で遭遇したのは";
		mes "あなた、でした？";
		next;
		menu "はい",-;
		mes "‐あなたはうなずき、";
		mes "　ポションにあの場所を";
		mes "　武装もせずに出歩いていた理由を";
		mes "　たずねた‐";
		next;
		mes "[ポション]";
		mes "あ、えっと……";
		mes "それに答えるのは";
		mes "ちょっと……";
		next;
		mes "[ポション]";
		mes "でも、あなたは";
		mes "僕にこの袋をわざわざ";
		mes "届けてくれたし……";
		next;
		mes "[ポション]";
		mes "……ううう。";
		next;
		mes "[ポション]";
		mes "わ、わかりました答えましょう！";
		mes "ですが、この話は";
		mes "どうか内密にしてください。";
		mes "その約束を守れるなら";
		mes "答えましょう。";
		delitem 6390,1;
		set BIF_1QUE,93;
		delquest 71140;
		setquest 11200;
		close;
	case 93:
		mes "[ポション]";
		mes "約束を守ってくれますね？";
		mes "……わかりました。";
		next;
		mes "[ポション]";
		mes "今から話すのは";
		mes "僕たちの間でも口にすることが";
		mes "はばかられているものです。";
		next;
		mes "[ポション]";
		mes "それもそのはず……";
		mes "だって、本国からの補給が";
		mes "突然途切れたという";
		mes "ものなんですから！";
		next;
		mes "[ポション]";
		mes "……ふう。";
		mes "は、話してしまいました。";
		mes "これで僕がなぜ内密にと";
		mes "頼んだのかわかったでしょう？";
		next;
		mes "[ポション]";
		mes "本国からの補給がなくなる、";
		mes "それは僕たちの困窮を";
		mes "意味します……";
		next;
		mes "[ポション]";
		mes "こうしてる今も、";
		mes "上が調査しているようですが";
		mes "……ただ待機しているなんて";
		mes "できません。";
		next;
		mes "[ポション]";
		mes "せめて食料を確保しようと";
		mes "僕は、外に出ていたのです。";
		mes "……収穫はなかったですけど。";
		next;
		mes "[ポション]";
		mes "話は以上です。";
		mes "約束どおり、";
		mes "内緒にしていてくださいね。";
		next;
		mes "‐本国からスプレンディッドに";
		mes "　補給物資が届かなくなった……";
		mes "　これはとても重大な";
		mes "　案件ではないだろうか‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（もう少し詳しい事情を";
		mes "聞いてみよう……）";
		set BIF_1QUE,103;
		chgquest 11200,11201;
		close;
	case 103:
		mes "[ポション]";
		mes "あの……まだなにか？";
		next;
		menu "詳しい事情を聞く",-;
		mes "[ポション]";
		mes "えっ";
		mes "　";
		mes "で、でも……";
		mes "これ以上詳しいことは……";
		next;
		mes "[ポション]";
		mes "あの、これを話したら";
		mes "僕に見返りはありますか？";
		next;
		mes "[ポション]";
		mes "たとえば、その……";
		mes "僕を助けてくれる、とか……";
		mes "お願いを聞いてくれるとか。";
		next;
		mes "[ポション]";
		mes "でしたら、話します。";
		next;
		if(select("話を聞く","やめる") == 2) {
			mes "[ポション]";
			mes "そ、そうですよね！";
			mes "僕が欲張りすぎました……";
			mes "でも、それでは";
			mes "お話できません。";
			close;
		}
		mes "[ポション]";
		mes "あなたは補給路を";
		mes "ご存知ですか？";
		mes "街の^FF0000北^000000にあるんですけど……";
		next;
		mes "[ポション]";
		mes "本国からの補給や連絡は";
		mes "すべて一本の補給路を通じて";
		mes "ここにやってくるんです。";
		next;
		mes "[ポション]";
		mes "それが途絶えたというなら";
		mes "補給路になにかあったに";
		mes "違いありません。";
		next;
		mes "[ポション]";
		mes "その道は歴史が深く";
		mes "ずっと昔から使われていたものですから";
		mes "……";
		next;
		mes "[ポション]";
		mes "あの……それでお願いなんです。";
		mes "あなたにその補給路が";
		mes "どうなっているか";
		mes "確認してほしいんです。";
		next;
		mes "[ポション]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいったんです。";
		mes "そろそろ戻ってくるはずです。";
		next;
		mes "[ポション]";
		mes "彼を捜して調査結果を";
		mes "聞いてほしいのです。";
		next;
		mes "[ポション]";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道がありますので";
		mes "そこに行ってください。";
		mes "兵士が戻ってくるはずです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		set BIF_1QUE,113;
		chgquest 11201,11202;
		close;
	case 113:
		mes "[ポション]";
		mes "兵士の一人が補給路に";
		mes "何があったかビフロストへ";
		mes "調査しにいったんです。";
		mes "そろそろ戻ってくるはずです。";
		next;
		mes "[ポション]";
		mes "彼を捜して調査結果を";
		mes "聞いてほしいのです。";
		next;
		mes "[ポション]";
		mes "スプレンディッドの北に";
		mes "ビフロストへの道がありますので";
		mes "そこに行ってください。";
		mes "兵士が戻ってくるはずです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（補給路のあるビフロストへ";
		mes "調査に行った兵士を捜そう。";
		mes "スプレンディッドの街の北の";
		mes "方から戻ってくるらしい）";
		close;
	case 123:
		mes "[ポション]";
		mes "補給路を調べてきて";
		mes "くれたんですね……って";
		mes "亀裂ですか!?";
		next;
		mes "[ポション]";
		mes "最近、あちこちで亀裂が";
		mes "発生してるとは聞いてましたけど";
		mes "まさか補給路にまで……";
		mes "それじゃあ、本国からの";
		mes "補給が途絶えるはずです。";
		next;
		mes "‐あなたは霧の森を通るルートが";
		mes "　存在することを";
		mes "　ポションに伝えた‐";
		next;
		mes "[ポション]";
		mes "あ……霧の森ですか。";
		mes "確かに霧の森を通れば";
		mes "その先にあるビフロストに";
		mes "行けますけど……";
		mes "でも、あそこは……";
		next;
		mes "[ポション]";
		mes "……";
		next;
		mes "[ポション]";
		mes "あなた、そこに行くんですか？";
		next;
		mes "[ポション]";
		mes "……ビフロストには";
		mes "^FF0000モーラ^000000という街が";
		mes "あります。";
		mes "本国からの物資はみな";
		mes "その街を経由してやってくるんです。";
		next;
		mes "[ポション]";
		mes "^0000FF霧の森^000000に入るためには";
		mes "スプレンディッドの";
		mes "北の地域ビフロストにいる";
		mes "^0000FF霧の森の監視兵^000000に話せば";
		mes "通してくれるはずです。";
		next;
		mes "[ポション]";
		mes "でも大変危険な森だから";
		mes "気をつけてください。";
		mes "しかも巨大な竜が現れたって";
		mes "噂もありますし……";
		next;
		mes "[ポション]";
		mes "霧の森をぬけて";
		mes "モーラの街の^FF0000物流倉庫に行けば";
		mes "管理者から話を聞ける^000000はずですよ。";
		next;
		mes "[ポション]";
		mes "あと、ビフロストは";
		mes "不思議な力が働いているんです。";
		mes "言葉が違う種族同士でも";
		mes "何故か^0000FF意志疎通^000000ができます。";
		mes "原理はよく分からないんですけど。";
		set BIF_1QUE,133;
		delquest 11203;
		setquest 71145;
		close;
	case 133:
		mes "[ポション]";
		mes "モーラの街の^FF0000物流倉庫に行けば";
		mes "管理者から話を聞ける^000000はずですよ。";
		close;
	case 143:
	case 153:
	case 163:
	case 173:
	case 183:
		mes "[ポション]";
		mes "いろいろとありがとうございました。";
		mes "いやあ、それにしても";
		mes "これからどうしたものですかなあ。";
		close;
	default:
		mes "[ポション]";
		mes "ああ……おなかすきました。";
		mes "本国に戻ったら";
		mes "本当におなかいっぱい";
		mes "食べたいです。";
		close;
	}
}

splendide.gat,262,376,4	script	ラフィネ族の兵士	447,{
	if(!equippeditem(2782)) {
		mes "[ラフィネ族の兵士]";
		mes "DielFarmar Di RiniIyazser";
		mes "Ha mahAgolAsh UU";
		mes "TurNohnar Di DurNeiFar";
		mes "Ra AnuVerNoth Ha";
		mes "AshRivehDor Ha BurWehLars";
		mes "Ur RinimanMod";
		next;
		mes "‐言葉が通じない。";
		mes "　通訳してくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 111:
	case 112:
	case 113:
		mes "[ラフィネ族の兵士]";
		mes "なんてことだ、";
		mes "まさかビフロストに";
		mes "あんな異変がおきてるなんて……";
		mes "物資が届かない訳だ……";
		next;
		menu "異変？",-;
		mes "[ラフィネ族の兵士]";
		mes "ビフロストに";
		mes "^0000FF巨大な青く光る球体^000000が";
		mes "発生していました。";
		mes "あなた方、人間の駐屯地にある";
		mes "あの亀裂と同様のものと思われます。";
		next;
		mes "[ラフィネ族の兵士]";
		mes "この先にあるビフロストを通って";
		mes "本国アルフヘイムから物資が届きます。";
		mes "きっと、あの亀裂で通行ができなくなり";
		mes "物資が届かないのでしょう。";
		next;
		mes "[ラフィネ族の兵士]";
		mes "もしかしたら、物資を運ぶ部隊自体が";
		mes "あの亀裂に飲み込まれてしまったかも";
		mes "しれません……";
		next;
		mes "[ラフィネ族の兵士]";
		mes "しかし、困った……";
		mes "急いで新しい補給路を";
		mes "見つけなくてはいけません。";
		next;
		mes "[ラフィネ族の兵士]";
		mes "もう一つ通行できるルートは";
		mes "あるにはあるのですが、";
		mes "危険な^0000FF霧の森^000000を通らなくては";
		mes "いけないのです……";
		mes "う～む、司令官に報告しなくては。";
		next;
		if(BIF_1QUE == 111) {
			set BIF_1QUE,121;
			chgquest 11190,11191;
			mes "["+strcharinfo(0)+"]";
			mes "（クスミに報告しよう）";
			close;
		} else if(BIF_1QUE == 112) {
			set BIF_1QUE,122;
			chgquest 11196,11197;
			mes "["+strcharinfo(0)+"]";
			mes "（テオドに報告しよう）";
			close;
		} else if(BIF_1QUE == 113) {
			set BIF_1QUE,123;
			chgquest 11202,11203;
			mes "["+strcharinfo(0)+"]";
			mes "（ポションに報告しよう）";
			close;
		}
	case 121:
	case 122:
	case 123:
		mes "[ラフィネ族の兵士]";
		mes "もしかしたら、物資を運ぶ部隊自体が";
		mes "あの亀裂に飲み込まれてしまったかも";
		mes "しれません……";
		next;
		mes "[ラフィネ族の兵士]";
		mes "しかし、困った……";
		mes "急いで新しい補給路を";
		mes "見つけなくてはいけません。";
		next;
		mes "[ラフィネ族の兵士]";
		mes "もう一つ通行できるルートは";
		mes "あるにはあるのですが、";
		mes "危険な^0000FF霧の森^000000を通らなくては";
		mes "いけないのです……";
		next;
		if(BIF_1QUE == 121) {
			mes "["+strcharinfo(0)+"]";
			mes "（クスミに報告しよう）";
			close;
		} else if(BIF_1QUE == 122) {
			mes "["+strcharinfo(0)+"]";
			mes "（テオドに報告しよう）";
			close;
		} else if(BIF_1QUE == 123) {
			mes "["+strcharinfo(0)+"]";
			mes "（ポションに報告しよう）";
			close;
		}
	default:
		mes "[ラフィネ族の兵士]";
		mes "この先はアルフヘイムに繋がる";
		mes "ビフロストがあります。";
		mes "現在は、原因不明の亀裂によって";
		mes "通行が不可能になっていますので";
		mes "ご注意を。";
		close;
	}
}

splendide.gat,118,261,4	script	ダプレル	435,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(!equippeditem(2782)) {
		mes "[ダプレル]";
		mes "DRHSfhsdfGSDH";
		mes "Fgkkmvoifk DFG";
		mes "DFHshfeksmn fgg";
		mes "FDbbd fjnnvk n skncki";
		mes "dfgd F FHdfkdfjkmv";
		next;
		mes "‐言葉が通じない。";
		mes "　通訳をしてくれる何かが必要だ‐";
		close;
	}
	switch(BIF_1QUE) {
	case 161:
	case 162:
	case 163:
		mes "[ダプレル]";
		mes "もしかして、それは";
		mes "モーラの街からの荷ですか!?";
		mes "あああ、待ってました!!";
		next;
		mes "[ダプレル]";
		mes "薬など病の者や怪我をした者に";
		mes "必要な物資が入っているのです！";
		mes "非常に助かりました！";
		next;
		mes "[ダプレル]";
		mes "これはお礼です。";
		mes "是非、受け取ってください。";
		mes "本当にありがとうございました！";
		delitem 6391,1;
		if(BIF_1QUE == 161)
			set BIF_1QUE,171;
		else if(BIF_1QUE == 162)
			set BIF_1QUE,172;
		else if(BIF_1QUE == 163)
			set BIF_1QUE,173;
		setquest 71146;
		delquest 11208;
		if(checkre())
			getexp 500000,250000;
		else
			getexp 5000000,2500000;
		getitem 6380,5;
		next;
		mes "[ダプレル]";
		mes "しかし、あの亀裂を";
		mes "何とかしないと、";
		mes "我々は困窮してしまいます。";
		mes "困りました……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ラフィネ族の現状が";
		mes "よくわかった。";
		mes "テオレに報告しておこう）";
		close;
	case 171:
	case 172:
	case 173:
		mes "[ダプレル]";
		mes "あなたの協力に感謝しています。";
		mes "ありがとうございました。";
		next;
		mes "[ダプレル]";
		mes "しかし、あの亀裂を";
		mes "何とかしないと、";
		mes "我々は困窮してしまいます。";
		mes "困りました……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ラフィネ族の現状が";
		mes "よくわかった。";
		mes "テオレに報告しておこう）";
		close;
	case 181:
	case 182:
	case 183:
		mes "[ダプレル]";
		mes "あなたの協力に感謝しています。";
		mes "ありがとうございました。";
		close;
	default:
		mes "[ダプレル]";
		mes "いやあ、やはりヤイは";
		mes "居心地がいいですね。";
		close;
	}
}

mora.gat,185,163,2	script	物流倉庫の管理人	516,{
	switch(BIF_1QUE) {
	case 131:
	case 132:
	case 133:
		mes "[物流倉庫の管理人]";
		mes "あの、お客さん！";
		mes "ここに勝手に入らないで！";
		next;
		mes "‐あなたは、";
		mes "　物資が届かないことを心配し、";
		mes "　スプレンディッドから";
		mes "　様子を見に来たことを伝えた‐";
		next;
		mes "[物流倉庫の管理人]";
		mes "え？";
		mes "あの、あなた、";
		mes "スプレンディッドから";
		mes "いらしたんですか!?";
		mes "霧の森を通って来たんですか！";
		mes "すごい……";
		next;
		mes "[物流倉庫の管理人]";
		mes "いやあ、謎の亀裂ができたおかげで";
		mes "物資を輸送できないのですよ！";
		mes "まったく困ったものです。";
		mes "薬や食料もあるので一大事ですよ。";
		next;
		mes "[物流倉庫の管理人]";
		mes "あっちからあそこまで";
		mes "積み上げられてるのが全部";
		mes "スプレンディッドに";
		mes "送らなければいけない物資です。";
		next;
		mes "[物流倉庫の管理人]";
		mes "どんどん積もっていく荷を見るのが";
		mes "悲しいですね。";
		emotion 28;
		next;
		menu "手伝いましょうか？",-;
		mes "[物流倉庫の管理人]";
		mes "本当ですか!?";
		mes "それは助かります！";
		next;
		mes "[物流倉庫の管理人]";
		mes "それでは";
		mes "^FF0000旅館^000000にいる^FF0000ヨネス^000000さんに";
		mes "会ってあげてください。";
		mes "急ぎの配達があるんですよ！";
		mes "よろしくお願いします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（旅館にいるヨネスさんを";
		mes "たずねてみよう）";
		if(BIF_1QUE == 131)
			set BIF_1QUE,141;
		else if(BIF_1QUE == 132)
			set BIF_1QUE,142;
		else if(BIF_1QUE == 133)
			set BIF_1QUE,143;
		delquest 71145;
		setquest 11206;
		close;
	case 141:
	case 142:
	case 143:
		mes "[物流倉庫の管理人]";
		mes "それでは";
		mes "^FF0000旅館^000000にいる^FF0000ヨネス^000000さんに";
		mes "会ってあげてください。";
		mes "急ぎの配達があるんですよ！";
		mes "よろしくお願いします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（旅館にいるヨネスさんを";
		mes "たずねてみよう）";
		close;
	default:
		if(BIF_1QUE >= 151) {
			mes "[物流倉庫の管理人]";
			mes "ビフロストに亀裂が出来てから";
			mes "配送が不可能になり、";
			mes "どんどん積もっていく荷を見るのが";
			mes "悲しいですね。";
			next;
			mes "[物流倉庫の管理人]";
			mes "旅人も足止めされて";
			mes "この街にはそんな人で";
			mes "いっぱいですし……";
			close;
		}
		mes "[物流倉庫の管理人]";
		mes "あの、お客さん！";
		mes "ここに勝手に入らないで！";
		mes "必要なものがあれば";
		mes "外にいる職員に";
		mes "声をかけてください。";
		close;
	}
}

mora.gat,35,119,4	script	ロンド	513,{
	mes "[ロンド]";
	mes "この街は本当に不思議な場所。";
	mes "どんな言語でもすべて";
	mes "聞き取れます。";
	next;
	mes "[ロンド]";
	mes "もちろん、街を離れると";
	mes "あなたの言葉は";
	mes "聞き取れなくなってしまうけど。";
	close;
}

mora.gat,98,66,4	script	リリシア	518,{
	mes "[リリシア]";
	mes "寒いの、本当に嫌い！";
	mes "わたしの大事な葉が";
	mes "枯れちゃうんだもの！";
	next;
	mes "[リリシア]";
	mes "その点、この街は";
	mes "本当に住みやすいわ！";
	mes "いつも緑だし、";
	mes "誰とでも気軽にお話できるし！";
	close;
}

mora.gat,139,102,2	script	ホミン	515,{
	mes "[ホミン]";
	mes "ヨトゥンヘイムに";
	mes "ミッドガルドへ行ける";
	mes "亀裂ができたと聞いて";
	mes "行ってみようと思ったのですが、";
	mes "ここで足止めになっちゃいました。";
	next;
	mes "[ホミン]";
	mes "あなたは、ミッドガルドに";
	mes "行ったことあります？";
	mes "一体どんなところなんでしょう。";
	mes "ポリンという生物を";
	mes "一目でいいから見てみたいんです。";
	close;
}

mora.gat,55,124,2	script	ヨネス	495,{
	switch(BIF_1QUE) {
	case 141:
	case 142:
	case 143:
		mes "[ヨネス]";
		mes "おや、ひょっとして君。";
		mes "君がスプレンディッドから";
		mes "霧の森を抜けて";
		mes "モーラの街へ来た旅人なのかい？";
		next;
		mes "[ヨネス]";
		mes "もし君がその旅人で、";
		mes "これからスプレンディッドに戻るなら";
		mes "この荷を配達してくれないかな。";
		next;
		mes "[ヨネス]";
		mes "スプレンディッドのお偉いさんから";
		mes "急ぎの注文を受けたのに";
		mes "ここで足止めをくって";
		mes "届けられないんだよ。";
		mes "お願いだ、力を貸しておくれ！";
		next;
		if(select("依頼を受ける","依頼を受けない") == 2) {
			mes "[ヨネス]";
			mes "そうか……";
			mes "まあ初対面で頼むようなことじゃ";
			mes "ないよな。";
			mes "はは……";
			close;
		}
		mes "[ヨネス]";
		mes "ああ！　助かるよ！";
		mes "今、用意するから";
		mes "もう一度話しかけてくれ。";
		if(BIF_1QUE == 141)
			set BIF_1QUE,151;
		else if(BIF_1QUE == 142)
			set BIF_1QUE,152;
		else if(BIF_1QUE == 143)
			set BIF_1QUE,153;
		setquest 11207;
		delquest 11206;
		close;
	case 151:
	case 152:
	case 153:
		if(checkweight(6391,1) == 0) {
			mes "[ヨネス]";
			mes "あれ？";
			mes "荷物の空きを作ってくれと";
			mes "言ったじゃないか。";
			mes "そんな状態じゃ頼めないよ。";
			close;
		}
		mes "[ヨネス]";
		mes "はい、確かに頼んだよ。";
		mes "届け先は^FF0000スプレンディッド^000000に";
		mes "いらっしゃる";
		mes "^FF0000ダプレル^000000様だ。";
		mes "間違えないように！";
		getitem 6391,1;
		if(BIF_1QUE == 151)
			set BIF_1QUE,161;
		else if(BIF_1QUE == 152)
			set BIF_1QUE,162;
		else if(BIF_1QUE == 153)
			set BIF_1QUE,163;
		setquest 11208;
		delquest 11207;
		next;
		mes "[ヨネス]";
		mes "医療道具とか";
		mes "命にかかわる大事な物が";
		mes "入っているらしいから";
		mes "急いで届けてくれ。";
		close;
	case 161:
	case 162:
	case 163:
		mes "[ヨネス]";
		mes "はい、確かに頼んだよ。";
		mes "届け先は^FF0000スプレンディッド^000000に";
		mes "いらっしゃる^FF0000ダプレル^000000様だ。";
		mes "間違えないように！";
		close;
	case 171:
	case 172:
	case 173:
		mes "[ヨネス]";
		mes "君のおかげで仕事は";
		mes "完了したよ、ありがとう。";
		mes "ところで君は、";
		mes "この仕事に就く気はないかな？";
		close;
	default:
		mes "[ヨネス]";
		mes "ああ……";
		mes "このままモーラの街から";
		mes "出られなくなってしまったら";
		mes "今まで頑張ってつみあげてきた";
		mes "信用が崩れ落ちてしまうよ。";
		close;
	}
}

//============================================================
// 紫色の竜クエスト
//- Registry -------------------------------------------------
// BIF_2QUE -> 0～
//------------------------------------------------------------
1@mist.gat,1,1,0	script	#mistwood_mon	844,{
OnStart:
	switch(rand(1,6)) {
	case 1: set '@x,77;  set '@y,240; break;
	case 2: set '@x,147; set '@y,261; break;
	case 3: set '@x,182; set '@y,263; break;
	case 4: set '@x,194; set '@y,350; break;
	case 5: set '@x,268; set '@y,183; break;
	case 6: set '@x,65;  set '@y,278; break;
	}
	monster getmdmapname("1@mist.gat"),'@x,'@y,"彷徨う紫色の竜",2131,1,getmdnpcname("#mistwood_mon")+"::OnKilled";
	end;
OnKilled:
	announce "竜の叫び : これが……守護者の道を捨てた……私……罰……なのか……",0x9,0xFFFF00;
	hideoffnpc getmdnpcname("ロキ#mist");
	hideoffnpc getmdnpcname("倒れている女性#mist");
	end;
}

1@mist.gat,97,30,3	script	謎の青年#mist	512,{
	if(BaseLevel < 98) {
		mes "[謎の青年]";
		mes "ここを通るつもりなのか？";
		mes "……";
		mes "君の実力では";
		mes "俺に協力するのは無理なようだな。";
		next;
		mes "‐^FF0000Baseレベルが98以上なければ";
		mes "　いけないようだ^000000。";
		mes "　98以上になったらまた来よう‐";
		close;
	}
	switch(BIF_2QUE) {
	case 0:
		if(DIC_2QUE == 24 || DIC_2QUE == 26) {
			mes "[謎の青年]";
			mes "君は……";
			mes "連合軍駐屯地で一度あったな。";
			mes "エルディカスティスの大臣アハトに";
			mes "関する情報は有用だった。";
			mes "礼を言っておく。";
			next;
		}
		mes "[謎の青年]";
		mes "ここを通過するつもりなのか？";
		mes "この森は人を惑わす。";
		mes "好奇心だけで挑戦するのであれば";
		mes "やめておけ。";
		next;
		menu "あなたは誰ですか？",-;
		mes "[ロキ]";
		mes "アサシンギルドの…^FF0000ロキ^000000。";
		mes "それが俺の名前だ。";
		mes "君の名前は？";
		next;
		menu "名乗る",-;
		mes "[ロキ]";
		mes strcharinfo(0)+ "か。";
		mes "忠告しておくが、";
		mes "この森は人を迷わす上、";
		mes "^800080凶暴な竜^000000が迷い込んでいる。";
		mes "命が大切ならば、この森から";
		mes "すぐに立ち去った方がいい。";
		next;
		if(select("あなたこそ何をしているのですか？","立ち去ります") == 2) {
			mes "[ロキ]";
			mes "それがいい。";
			mes "気をつけて戻るがいい。";
			set BIF_2QUE,1;
			close;
		}
		break;
	case 1:
		mes "[ロキ]";
		mes "まだいたのか？";
		mes "命を粗末にするな。";
		next;
		if(select("さよなら","あなたは何をしているのですか？") == 1) {
			mes "[ロキ]";
			mes "気をつけるがいい。";
			close;
		}
		mes "[ロキ]";
		mes "……";
		mes "君も物好きだな。";
		mes "まあいい、話してやろう。";
		next;
		break;
	case 2:
		if(getmapmobs(getmdmapname("1@mist.gat"),getmdnpcname("#mistwood_mon")+ "::OnKilled")) {
			mes "[ロキ]";
			mes "この森のどこかで";
			mes "竜が目を覚ましたようだ。";
			mes "戦ってくるがいい。";
			close;
		}
		if(getnpctimer(1)) {
			mes "‐竜の咆哮が聞こえる。";
			mes "　^800080彷徨う紫色の竜^000000が";
			mes "　歌に反応しているのかもしれない‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（歌い終わるまで待とう。";
			mes "約30秒間経過したら";
			mes "ロキに話しかけよう)";
			close;
		}
		if('flag) {
			mes "[ロキ]";
			mes "竜に変化があったようだな。";
			mes "……";
			mes "君達の歌のおかげ、という訳か。";
			mes "どうやら、";
			mes "君達はイグドラシルに関わる者達と";
			mes "関係があるようだな。";
			next;
			mes "[ロキ]";
			mes "俺は竜に会うために";
			mes "森の奥へ行く。";
			mes "……この先はモンスターも多い。";
			mes "ついて来るか？";
			next;
			if(select("いや、けっこうです","ついて行きます") == 1) {
				mes "[ロキ]";
				mes "そうか。";
				mes "好きにするがいい。";
				close;
			}
			mes "[ロキ]";
			mes "では行こう。";
			close2;
			warp getmdmapname("1@mist.gat"),334,178;
			end;
		}
		mes "[ロキ]";
		mes "この森に迷い込んだ竜は";
		mes "今、一時の眠りについているが、";
		mes "再び目を覚ましそうだ。";
		mes "目を覚ませば、";
		mes "問答無用で襲ってくるぞ。";
		next;
		if(BIF_2QUE_SUB == 2 || BIF_2QUE_SUB == 3) {
			switch(select("何でもありません","^FF0000ノローキアの歌を歌う^000000")) {
			case 1:
				mes "[ロキ]";
				mes "早く森を出た方がいい。";
				close;
			case 2:
				if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
					mes "‐ノローキアの歌を歌うためには";
					mes "　パーティーリーダーで";
					mes "　なくてはいけません‐";
					close;
				}
				break;
			}
			mes "‐ノローキアの歌を";
			mes "　歌いますか？‐";
			next;
			if(select("いいえ","はい") == 1) {
				mes "[ロキ]";
				mes "……";
				mes "何をしているのだ？";
				close;
			}
			mes "‐あなたの歌声にあわせて";
			mes "　ノローキアの歌声も聞こえる‐";
			initnpctimer;
			set BIF_2QUE_SUB,3;
			misceffect 91,"";
			next;
			mes "‐竜の咆哮が聞こえる。";
			mes "　^800080彷徨う紫色の竜^000000が";
			mes "　歌に反応しているのかもしれない‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（歌い終わるまで待とう。";
			mes "約30秒間経過したら";
			mes "ロキに話しかけよう)";
			close;
		}
		else {
			switch(select("何でもありません","^FF0000竜と戦います^000000","^0000FF助言をください[竜を倒さないルート]^000000")) {
			case 1:
				mes "[ロキ]";
				mes "早く森を出た方がいい。";
				close;
			case 2:
				if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
					mes "[ロキ]";
					mes "本気か……？";
					mes "いや、君なら";
					mes "倒せるかもしれないな。";
					next;
					mes "[ロキ]";
					mes "わかった。";
					mes "竜の残影と戦うのであれば";
					mes "パーティーリーダーに";
					mes "俺に話しかけてもらってくれ。";
					close;
				}
				mes "[ロキ]";
				mes "本気か……？";
				mes "いや、君ならもしかしたら";
				mes "倒せるかもしれないな。";
				mes "本当に竜と戦うのか？";
				next;
				if(select("やっぱり戦いません","戦います") == 1) {
					mes "[ロキ]";
					mes "……";
					mes "ならば早く立ち去るがいい。";
					close;
				}
				mes "[ロキ]";
				mes "意志は固いようだな。";
				mes "ならば、";
				mes "ここでしばらく待つといい。";
				mes "　";
				mes "‐数分後‐";
				next;
				mes "‐竜の咆哮が聞こえる。";
				mes "　^800080彷徨う紫色の竜^000000が";
				mes "　目覚めたようだ‐";
				donpcevent getmdnpcname("#mistwood_mon") + "::OnStart";
				next;
				mes "[ロキ]";
				mes "この森のどこかで";
				mes "竜が目を覚ましたようだ。";
				mes "戦ってくるがいい。";
				close;
			case 3:
				mes "[ロキ]";
				mes "……";
				mes "この森に迷い込んだ竜は";
				mes "非常に強く、";
				mes "さらに厄介なことに";
				mes "この霧の森にいるモンスターも";
				mes "桁外れに強い。";
				next;
				mes "[ロキ]";
				mes "竜を倒すことも、";
				mes "霧の森の通過もままならないならば、";
				mes "この森の竜に詳しい者に話を聞けば、";
				mes "何かわかるかもしれない。";
				next;
				mes "[ロキ]";
				mes "……";
				mes "そもそも、詳しい者が";
				mes "いるかどうかもわからないが、";
				mes "何もしないよりはマシだ。";
				mes "捜してみたらどうだ？";
				next;
				mes "‐前線基地 スプレンディッドの";
				mes "　基地内(272,338)に";
				mes "　彷徨う紫色の竜に関係する者";
				mes "　がいるようです‐";
				next;
				mes "‐「紫色の竜」クエスト進行において、";
				mes "　紫色の竜を倒せない、";
				mes "　霧の森を通過できない冒険者は";
				mes "　スプレンディッドの基地内";
				mes "　(272,338)にいる「何かの気配」に";
				mes "　話しかけてください‐";
				close;
			}
		}
	case 3:
	case 4:
		mes "[ロキ]";
		mes "また会ったな。";
		mes "モーラの旅館に来てくれないか。";
		mes "渡すものがある。";
		next;
		mes "[ロキ]";
		mes "俺はこれから";
		mes "森の奥へ行く。";
		mes "……この先はモンスターも多い。";
		mes "ついて来るか？";
		next;
		if(select("いや、けっこうです","ついて行きます") == 1) {
			mes "[ロキ]";
			mes "そうか。";
			mes "好きにするがいい。";
			close;
		}
		mes "[ロキ]";
		mes "では行こう。";
		close2;
		warp getmdmapname("1@mist.gat"),334,178;
		end;
	case 99:
	case 100:
		mes "[ロキ]";
		mes "また会ったな。";
		mes "ここは危険な地域。";
		mes "気をつけるがいい。";
		next;
		if(getmapmobs(getmdmapname("1@mist.gat"),getmdnpcname("#mistwood_mon")+ "::OnKilled")) {
			mes "[ロキ]";
			mes "この森のどこかで";
			mes "竜の残影が目を覚ましたようだ。";
			mes "戦ってくるがいい。";
			close;
		}
		mes "[ロキ]";
		mes "それと、君に話がある。";
		mes "この霧の森から紫色の竜は";
		mes "いなくなった。";
		next;
		mes "[ロキ]";
		mes "しかし、どうやら";
		mes "紫色の竜の力がこの霧の森に";
		mes "宿ってしまい、";
		mes "紫色の竜の残影が出てしまうのだ。";
		mes "恐ろしいことに強さは、";
		mes "あの強さのままだ。";
		next;
		if(select("怖いので立ち去ります","^FF0000竜と戦います^000000") == 1) {
			mes "[ロキ]";
			mes "ああ、";
			mes "早く森を出た方がいい。";
			close;
		}
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[ロキ]";
			mes "本気か……？";
			mes "いや、君なら";
			mes "倒せるかもしれないな。";
			next;
			mes "[ロキ]";
			mes "わかった。";
			mes "竜の残影と戦うのであれば";
			mes "パーティーリーダーに";
			mes "俺に話しかけてもらってくれ。";
			close;
		}
		mes "[ロキ]";
		mes "本気か……？";
		mes "本当に戦うのか？";
		next;
		if(select("やっぱり戦いません","戦います") == 1) {
			mes "[ロキ]";
			mes "……";
			mes "ならば早く立ち去るがいい。";
			close;
		}
		mes "[ロキ]";
		mes "意志は固いようだな。";
		mes "ならば、";
		mes "ここでしばらく待つといい。";
		mes "　";
		mes "‐数分後‐";
		next;
		mes "‐竜の咆哮が聞こえる。";
		mes "　^800080彷徨う紫色の竜^000000が";
		mes "　目覚めたようだ‐";
		donpcevent getmdnpcname("#mistwood_mon") + "::OnStart";
		next;
		mes "[ロキ]";
		mes "この森のどこかで";
		mes "竜の残影が目を覚ましたようだ。";
		mes "戦ってくるがいい。";
		close;
	}
	mes "[ロキ]";
	mes "……";
	mes "守護……いや、";
	mes "^800080紫色の髪をした女^000000を探している。";
	next;
	menu "紫色の髪をした女？",-;
	mes "[ロキ]";
	mes "そうだ、彼女は";
	mes "必要とされている。";
	mes "彼女を元の場所に";
	mes "連れて行かなくてはならない。";
	next;
	mes "[ロキ]";
	mes "……";
	mes strcharinfo(0)+ "、";
	mes "俺と話していないで";
	mes "ここから早く立ち去った方がいい。";
	next;
	menu "どうしました？",-;
	mes "[ロキ]";
	mes "この森に迷い込んだ竜は";
	mes "今、一時の眠りについているが、";
	mes "再び目を覚ましそうだ。";
	mes "目を覚ませば、";
	mes "問答無用で襲ってくるぞ。";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "（迷い込んだ竜……）";
	next;
	set BIF_2QUE,2;
	setquest 7212;
	delquest 71184;
	if(BIF_2QUE_SUB == 2) {
		mes "["+strcharinfo(0)+"]";
		mes "（迷い込んだ竜……";
		mes "ノローキアの言っていた";
		mes "竜のことだろう）";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（パーティーリーダーで";
		mes "ロキに話しかけよう）";
		next;
		mes "‐パーティーリーダーが";
		mes "　あなた、もしくはあなたと同じく";
		mes "　ノローキアの歌を覚えている者";
		mes "　であれば、ロキに話しかければ";
		mes "　ノローキアの歌を";
		mes "　歌うことができます‐";
		close;
	}
	mes "["+strcharinfo(0)+"]";
	mes "（迷い込んだ竜……";
	mes "戦ってみるのもいいかもしれない。";
	mes "竜と戦いたい場合は";
	mes "パーティーリーダーが";
	mes "ロキに話しかけよう）";
	close;
OnTimer5000:
	announce "竜の叫び : …………………う…た……？………",0x9,0xFFFF00;
	misceffect 91,getmdnpcname("ensyutu_1");
	misceffect 91,getmdnpcname("ensyutu_2");
	misceffect 91,getmdnpcname("ensyutu_3");
	end;
OnTimer10000:
	misceffect 91,getmdnpcname("ensyutu_4");
	misceffect 91,getmdnpcname("ensyutu_5");
	misceffect 91,getmdnpcname("ensyutu_6");
	end;
OnTimer15000:
	announce "竜の叫び : …………………どこかで…………………なつかしい……",0x9,0xFFFF00;
	misceffect 91,getmdnpcname("ensyutu_1");
	misceffect 91,getmdnpcname("ensyutu_2");
	misceffect 91,getmdnpcname("ensyutu_3");
	end;
OnTimer20000:
	misceffect 91,getmdnpcname("ensyutu_1");
	misceffect 91,getmdnpcname("ensyutu_2");
	misceffect 91,getmdnpcname("ensyutu_3");
	end;
OnTimer25000:
	misceffect 91,getmdnpcname("ensyutu_4");
	misceffect 91,getmdnpcname("ensyutu_5");
	misceffect 91,getmdnpcname("ensyutu_6");
	end;
OnTimer30000:
	set 'flag,1;
	donpcevent getmdnpcname("ロキ#mist")+ "::OnStart";
	stopnpctimer;
	announce "竜の叫び : この歌は……あ、頭が……割れる……そ、そうだ……私は、守護者……",0x9,0xFFFF00;
	end;
}

1@mist.gat,334,182,3	script	ロキ#mist	512,{
	switch(BIF_2QUE) {
	case 2:
		if(BIF_2QUE_SUB == 2 || BIF_2QUE_SUB == 3) {		// 回避ルート
			mes "‐紫色の髪の女性が倒れている‐";
			next;
			menu "この女性は……？",-;
			mes "[ロキ]";
			mes "この女は、俺が探していた";
			mes "イグドラシルの守護者、";
			mes "ニーズヘッグ。";
		}
		else {
			if('flag == 1) {
				mes "[ロキ]";
				mes "また会ったな。";
				mes "ここは危険な地域。";
				mes "気をつけるがいい。";
				close;
			}
			mes "‐ロキの横に";
			mes "　紫色の髪の女性が倒れている‐";
			next;
			if(select("この女性は……？","何かあったのですか？","あなたは何てことを……") != 1) {
				mes "[ロキ]";
				mes "あの紫色の竜を倒したのは";
				mes "君なのか？";
				mes "ならば感謝しなくてはいけないな。";
				next;
			}
			mes "[ロキ]";
			mes "この女は、俺が探していた";
			mes "イグドラシルの守護者、";
			mes "ニーズヘッグ。";
			mes "君がさきほど倒した紫色の竜だ。";
		}
		next;
		menu "ええ!?",-,"ニーズヘッグ!?",-;
		mes "[ロキ]";
		mes "彼女は";
		mes "過去の自分の行為への罪悪感から、";
		mes "この森の中で自我を失い、";
		mes "迷い続けていたのだ。";
		next;
		mes "[ロキ]";
		mes "……";
		mes "そして、君のあの歌で";
		mes "自らの意識を取り戻したのだろう。";
		mes "……";
		mes "君のおかげだな。";
		next;
		mes "[ロキ]";
		mes "俺はニーズヘッグを連れて";
		mes "この森を抜けた先にある";
		mes "レシア族の街モーラに向かう。";
		mes "君も来るがいい。";
		set BIF_2QUE,3;
		chgquest 7212,7213;
		close2;
		warp "bif_fild02.gat",286,327;
		end;
	case 3:
	case 4:
		mes "[ロキ]";
		mes "俺はニーズヘッグを連れて";
		mes "この森を抜けた先にある";
		mes "レシア族の街モーラに向かう。";
		mes "君も来るがいい。";
		close2;
		warp "bif_fild02.gat",286,327;
		end;
	default:
		mes "[ロキ]";
		mes "また会ったな。";
		mes "ここは危険な地域。";
		mes "気をつけるがいい。";
		close;
	}
OnStart:
	set 'flag,1;
	end;
}

1@mist.gat,333,179,3	script	倒れている女性#mist	511,{
	mes "‐^800080紫色の髪^000000をした女性が";
	mes "　倒れている。";
	mes "　近づくと、";
	mes "　とてもよい花の香りがした‐";
	close;
}

mora.gat,46,152,5	script	紫色の髪の女性#ep14_1	510,{
	switch(BIF_2QUE) {
	case 3:
		mes "[紫色の髪の女性]";
		mes "あなたをお待ちしていました。";
		mes "未だ混乱していますが、";
		mes "私の罪は私が一番よく";
		mes "わかっています。";
		next;
		mes "[紫色の髪の女性]";
		mes "あなたがいなかったら";
		mes "きっと私は今も深淵の闇を";
		mes "彷徨っていたでしょう……";
		next;
		menu "あなたは本当にニーズヘッグ？",-;
		mes "[紫色の髪の女性]";
		mes "……はい。";
		mes "私はイグドラシルの守護者";
		mes "ニーズヘッグです。";
		emotion 0,"";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "……";
		mes "私は心の弱さにつけこまれ";
		mes "闇に落とされた竜。";
		mes "もう守護者としての";
		mes "資格はありません……";
		next;
		mes "[ロキ]";
		mes "ニーズヘッグ。";
		next;
		mes "[ロキ]";
		mes "おまえが守護者であること、";
		mes "それがイグドラシルの意思だ。";
		mes "自己嫌悪している場合ではない。";
		mes "自分の役目を忘れるな。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "イグドラシルの意思……？";
		mes "……";
		mes "そうなのですね……";
		mes "もう見捨てられたと";
		mes "思っていたのに……";
		next;
		mes "‐ニーズヘッグは視線を外し、";
		mes "　何か考えはじめた。";
		mes "　きっとこれから何を為すべきか";
		mes "　考えているのだろう‐";
		set BIF_2QUE,4;
		close;
	case 4:
		mes "‐ニーズヘッグは";
		mes "　考え込んでいるようだ‐";
		close;
	case 99:
	case 100:
		mes "[守護者ニーズヘッグ]";
		mes "私の力はまだ完全に";
		mes "戻ってはいません。";
		mes "……";
		mes "今の私に魔王モロクに";
		mes "対抗するすべはないのです。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "しかし私は守護者。";
		mes "必ず力を取り戻し、";
		mes "忌まわしき魔王モロクから";
		mes "イグドラシルを守りましょう。";
		close;
	default:
		mes "[紫色の髪の女性]";
		mes "……";
		mes "私に話しかけないでください。";
		mes "ごめんなさい……";
		close;
	}
}

mora.gat,48,152,3	script	鋭い目つきの青年#ep14_1	512,{
	switch(BIF_2QUE) {
	case 3:
		mes "[ロキ]";
		mes "待っていた。";
		mes "ニーズヘッグが";
		mes "君に話があるそうだ。";
		close;
	case 4:
		if(checkitemblank() < 2) {
			mes "‐所持アイテムの種類数が多い為";
			mes "　新しくアイテムを受け取ることが";
			mes "　できません。";
			mes "　アイテムを整理してください‐";
			close;
		}
		if(checkweight(2568,1) == 0) {
			mes "‐所持アイテムの重量が重い為";
			mes "　新しくアイテムを受け取ることが";
			mes "　できません。";
			mes "　アイテムを整理してください‐";
			close;
		}
		mes "[ロキ]";
		mes "ニーズヘッグは元々";
		mes "世界樹の守護者の一柱だった。";
		mes "しかし、魔王モロクにそそのかされ";
		mes "守護者の役目を放棄してしまった。";
		next;
		mes "[ロキ]";
		mes "……その魔王モロクは";
		mes "君の知るミッドガルド大陸に";
		mes "封印されていたな。";
		next;
		mes "[ロキ]";
		mes "魔王モロクの支配を受けた";
		mes "愚か者たちが、魔王を開放すべく";
		mes "儀式を行ったことがあった。";
		next;
		mes "[ロキ]";
		mes "儀式は不完全だったが";
		mes "それによって、魔王モロクの封印は";
		mes "酷く弱くなってしまった……";
		mes "その最後の一線を維持していたのは";
		mes "世界樹イグドラシルの意思。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "……そうです。";
		mes "世界樹イグドラシルの意思と力は";
		mes "すべての世界と繋がっていますから。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "しかし、私が守護者の役目を";
		mes "放棄してしまったために、";
		mes "世界樹イグドラシルは";
		mes "不安定になってしまいました。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "イグドラシルで異変が起こったのも";
		mes "全て、そのせいなのです。";
		next;
		mes "[ロキ]";
		mes "そして、魔王モロクは";
		mes "自ら封印を破り、復活した。";
		mes "もっとも、その時に";
		mes "力の大半を使い、";
		mes "弱っているようだがな。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "全て私の責任です。";
		mes "私は魔王モロクの誘惑に";
		mes "耐えることができませんでした。";
		mes "とても……とても長い間……";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "私は孤独だったのです。";
		mes "ひとり、守護者の役割を担う日々……";
		mes "その数千年、寂しかったのです。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "私はその寂しさに負け、";
		mes "自分自身を制御できなくなり、";
		mes "暴走したのです。";
		mes "私のもう一つの意志は影となり";
		mes "暴君となってしまいました。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "しかし、そうして世に出た私は";
		mes "思い知ったのです。";
		mes "魔王モロクは私を利用し、";
		mes "私は私の手で、世界樹イグドラシルを";
		mes "裏切ってしまったことに。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "……それまで耐えてきた";
		mes "数千年の寂しささえかなわぬほどの";
		mes "喪失感が私を襲いました。";
		next;
		mes "[ロキ]";
		mes "まだ遅くない、ニーズヘッグ。";
		mes "君はまだ世界樹イグドラシルの守護者。";
		mes "まだ、やるべきことがある。";
		next;
		switch(select("あなたはひとりではありません","大変な義務ですね","もういい加減にして")) {
		case 1:
			mes "[守護者ニーズヘッグ]";
			mes "……ええ、そうですね。";
			mes "私はそれを知るために、";
			mes "今ここにいるのですね。";
			mes "やさしい人よ。";
			next;
			mes "[守護者ニーズヘッグ]";
			mes "今からでも間に合うのなら、";
			mes "私は守護者の義務を果たしましょう。";
			break;
		case 2:
			mes "[守護者ニーズヘッグ]";
			mes "……ああ、そうですね。";
			mes "ですが、これが";
			mes "私の償いになるのでしょう。";
			mes "今からでも、守護者として";
			mes "義務を果たさねばなりません。";
			break;
		case 3:
			mes "[守護者ニーズヘッグ]";
			mes "……";
			mes "あなたの怒りはもっともです。";
			mes "今からでも、守護者として";
			mes "義務を果たさねばなりません。";
			mes "そして償わなければいけません。";
			break;
		}
		next;
		mes "[守護者ニーズヘッグ]";
		mes "ひとの子。";
		mes "私の懺悔を聞いてくれてありがとう。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "私の力はまだ完全に";
		mes "戻ってはいません。";
		mes "……";
		mes "今の私に魔王モロクに";
		mes "対抗するすべはないのです。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "しかし私は守護者。";
		mes "必ず力を取り戻し、";
		mes "忌まわしき魔王モロクから";
		mes "イグドラシルを守りましょう。";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "あなたにこれをさし上げます。";
		mes "いつか、きっと";
		mes "あなたを守ってくれる時がくるはず。";
		next;
		mes "[ロキ]";
		mes "そういうことなら……";
		mes "俺もこれを渡そう。";
		mes "　";
		mes "‐ロキは首に巻いていたマフラーを";
		mes "　あなたにさし出した‐";
		next;
		mes "[守護者ニーズヘッグ]";
		mes "母なるイグドラシルが";
		mes "あなたを見守ってくださいますように。";
		delquest 7213;
		getitem 2568,1;
		getitem 2858,1;
		set BIF_2QUE,99;
		if(BIF_2QUE_SUB == 3) {
			setquest 201410;
			set BIF_2QUE_SUB,4;
			if(checkre()) {
				for(set '@i,0;'@i<3;set '@i,'@i+1)
					getexp 500000,0;
				for(set '@i,0;'@i<3;set '@i,'@i+1)
					getexp 0,250000;
			}
			else {
				for(set '@i,0;'@i<3;set '@i,'@i+1)
					getexp 5000000,0;
				for(set '@i,0;'@i<3;set '@i,'@i+1)
					getexp 0,2500000;
			}
		} else {
			setquest 201370;
			if(checkre()) {
				for(set '@i,0;'@i<6;set '@i,'@i+1)
					getexp 500000,0;
				for(set '@i,0;'@i<6;set '@i,'@i+1)
					getexp 0,250000;
			}
			else {
				for(set '@i,0;'@i<6;set '@i,'@i+1)
					getexp 5000000,0;
				for(set '@i,0;'@i<6;set '@i,'@i+1)
					getexp 0,2500000;
			}
		}
		close;
	case 99:
	case 100:
		mes "[ロキ]";
		mes "俺は当分この街にとどまる。";
		mes "魔王モロクについて";
		mes "調査するためにな。";
		mes "必ず俺の手で";
		mes "息の根を止めてやる。";
		close;
	default:
		mes "‐鋭い目つきの青年がいる‐";
		close;
	}
}

splendide.gat,272,338,4	script	何かの気配#14_1	437,{
	switch(BIF_2QUE_SUB) {
	case 0:
		if(BaseLevel < 98 || ASH_1QUE < 100) {	//異世界クエスト未クリア
			mes "‐何かの気配を感じる……";
			mes "　気のせいだろうか？‐";
			close;
		}
		if(BIF_2QUE == 100) {
			mes "‐ノローキアはもういない‐";
			close;
		}
		mes "‐うっすらと女性の姿が見える‐";
		emotion 1,"";
		next;
		if(select("気にしない","話しかける") == 1) {
			mes "‐あなたは立ち去った‐";
			close;
		}
		mes "[？]";
		mes "えっ……！";
		mes "あなたは私が見えるのですか？";
		next;
		menu "はい",-;
		mes "[？]";
		mes "……";
		mes "あなたが初めてです……";
		mes "私の存在に気付いてくれた人は。";
		mes "私はノローキア……";
		next;
		menu "あなたは何者ですか？",-;
		mes "[ノローキア]";
		mes "……";
		mes "わからないのです……";
		mes "もう、私にはほとんど";
		mes "記憶がのこっていません。";
		mes "ただ、意識だけの状態で";
		mes "この場所にとらわれています。";
		next;
		mes "[ノローキア]";
		mes "唯一覚えているのは、";
		mes "^FF0000あの方^000000のこと。";
		mes "　";
		mes "^FF0000あの方^000000をお救いしなくては……";
		next;
		menu "あの方？",-;
		mes "[ノローキア]";
		mes "……はい。";
		mes "あの方は";
		mes "ここから北にある霧の森で、";
		mes "自らが生み出した";
		mes "迷いに囚われているのです。";
		mes "心をとりもどしてほしいんです……";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "お願いです。";
		mes "あなたの力を貸してください。";
		mes "あの方を救ってください……";
		next;
		if(select("わかりました","忙しいのでまた今度") == 2) {
			mes "[ノローキア]";
			mes "……そんな！";
			next;
			mes "‐あなたは立ち去った‐";
			close;
		}
		mes "[ノローキア]";
		mes "ああっ、";
		mes "ありがとうございます……";
		next;
		menu "どうすればいいですか？",-;
		mes "[ノローキア]";
		mes "あの方、そう";
		mes "霧の森にいる紫色の竜を";
		mes "迷いから解き放ってください。";
		next;
		mes "[ノローキア]";
		mes "あの方を倒すことができれば、";
		mes "あの方を囚えている迷いも消え去り、";
		mes "心をとりもどすことができるでしょう。";
		next;
		mes "[ノローキア]";
		mes "ただし、あの方の力は強大です……";
		mes "倒すのは困難を極めるでしょう。";
		next;
		mes "[ノローキア]";
		mes "……^FF0000他にも方法はあります^000000。";
		mes "霧の森で、";
		mes "この^FF0000歌を歌ってください^000000。";
		next;
		mes "‐ノローキアはそういうと、";
		mes "　歌い始めた。";
		mes "　心に響く、とても暖かい歌だった‐";
		misceffect 91,"";
		next;
		mes "[ノローキア]";
		mes "生命の象徴イグドラシルを尊び、";
		mes "全ての生命を守ろうという歌です。";
		mes "あの方はいつも優しい顔で";
		mes "この歌を歌ってくださいました。";
		next;
		mes "[ノローキア]";
		mes "この歌は、まさにあの方の";
		mes "心、気持ちを表していました。";
		mes "しかし、あの方はいつ頃からか";
		mes "この歌を歌わなくなりました……";
		next;
		mes "[ノローキア]";
		mes "この歌を聞けば、";
		mes "時間がかかるかもしれませんが";
		mes "きっと、";
		mes "心を取り戻してくれると思います。";
		next;
		mes "[ノローキア]";
		mes "……でも、";
		mes "問題があります。";
		next;
		menu "問題？",-;
		mes "[ノローキア]";
		mes "この歌は、あなた一人では";
		mes "あの方の心に届かない……";
		mes "長い間、あの方の側にいて、";
		mes "ともに歌った私の力も必要でしょう。";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "しかし、私は肉体を失った制限からか、";
		mes "この場所を";
		mes "離れることはできません……";
		next;
		mes "[ノローキア]";
		mes "だから、あなたに私の力を託し、";
		mes "歌ってほしいのですが……";
		mes "今の私には";
		mes "あなたに力を託す力もないのです。";
		next;
		menu "どうすれば？",-;
		mes "[ノローキア]";
		mes "……";
		mes "ラフィネ族の力が欲しいのです。";
		mes "そう、ラフィネの力を";
		mes "宿した物があれば、";
		mes "その力を利用して";
		mes "あなたに私の力を宿せます。";
		next;
		mes "[ノローキア]";
		mes "……コイン。";
		mes "ラフィネの技術と魔力で";
		mes "製造されたコインがあれば、";
		mes "その力を利用することができます。";
		next;
		mes "[ノローキア]";
		mes "お願いです。";
		mes "スプレンディッドコイン50枚";
		mes "を持って来てください。";
		next;
		mes "‐^FF0000スプレンディッドコインを";
		mes "　ノローキアに渡すこと^000000で、";
		mes "　「紫色の竜」クエストを";
		mes "　^FF0000彷徨う紫色の竜^000000を倒さなくても";
		mes "　進行できるようになります‐";
		next;
		mes "‐しかし、^FF0000「紫色の竜」クエストの";
		mes "　報酬経験値が半分^000000になります。";
		mes "　（報酬アイテムは";
		mes "　通常通り入手できます）‐";
		next;
		mes "‐また、スプレンディッドコインを";
		mes "　ノローキアに渡した後、";
		mes "　^FF0000彷徨う紫色の竜を倒して";
		mes "　クエストを進行した場合も、";
		mes "　「紫色の竜」クエストの";
		mes "　報酬経験値は半分^000000になりますので";
		mes "　ご注意ください‐";
		next;
		mes "[ノローキア]";
		mes "お願いします。";
		mes "あなただけが頼りなのです。";
		set BIF_2QUE_SUB,1;
		close;
	case 1:
		mes "[ノローキア]";
		mes "スプレンディッドコイン50枚";
		mes "を持って来てくださいましたか？";
		next;
		if(select("まだです","持ってきました") == 1) {
			mes "[ノローキア]";
			mes "お願いします。";
			mes "あなただけが頼りなのです。";
			close;
		}
		if(countitem(6081) < 50) {
			mes "[ノローキア]";
			mes "……";
			mes "スプレンディッドコインを";
			mes "50枚持っていないようですが……";
			close;
		}
		mes "[ノローキア]";
		mes "スプレンディッドコインを";
		mes "持って来てくれたのですね！";
		mes "ありがとうございます!!";
		next;
		mes "‐^FF0000スプレンディッドコインを";
		mes "　ノローキアに渡すこと^000000で、";
		mes "　「紫色の竜」クエストを";
		mes "　^FF0000彷徨う紫色の竜^000000を倒さなくても";
		mes "　進行できるようになります‐";
		next;
		mes "‐しかし、^FF0000「紫色の竜」クエストの";
		mes "　報酬経験値が半分^000000になります。";
		mes "　（報酬アイテムは";
		mes "　通常通り入手できます）‐";
		next;
		mes "‐また、スプレンディッドコインを";
		mes "　ノローキアに渡した後、";
		mes "　^FF0000彷徨う紫色の竜を倒して";
		mes "　クエストを進行した場合も、";
		mes "　「紫色の竜」クエストの";
		mes "　報酬経験値は半分^000000になりますので";
		mes "　ご注意ください‐";
		next;
		mes "‐ノローキアに";
		mes "　スプレンディッドコイン50枚を";
		mes "　渡しますか？‐";
		next;
		if(select("また後で来ます","渡す") == 1) {
			mes "[ノローキア]";
			mes "そうですか……";
			mes "お待ちしてます。";
			close;
		}
		mes "[ノローキア]";
		mes "ありがとうございます！";
		mes "それでは今からあなたに";
		mes "私の力を託します。";
		next;
		delitem 6081,50;
		set BIF_2QUE_SUB,2;
		misceffect 91,"";
		mes "‐ノローキアが呪文を唱えると、";
		mes "　スプレンディッドコインが";
		mes "　共鳴し、薄い光を放ち、";
		mes "　ノローキアとあなたを照らした。";
		mes "　そして、頭の中に直接ノローキアの";
		mes "　歌が聞こえ、響き渡った‐";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "今、あなたに私の力を託しました。";
		mes "霧の森で歌えば、私の力も宿り、";
		mes "霧の森中に歌声が響き、";
		mes "あの方の心にも届くと思います。";
		next;
		mes "‐「紫色の竜」クエストにおいて、";
		mes "　あなたが^FF0000パーティーリーダー^000000になり、";
		mes "　メモリアルダンジョン「霧の森」";
		mes "　にいる「謎の青年」に話しかけ、";
		mes "　「ノローキアの歌を歌う」を";
		mes "　選択することで、‐";
		next;
		mes "‐彷徨う紫色の竜を倒さなくても";
		mes "　クエストを進行できるように";
		mes "　なりました‐";
		next;
		mes "‐なお、彷徨う紫色の竜を倒さなくても";
		mes "　「紫色の竜」クエストが";
		mes "　進行できるのは、";
		mes "　ノローキアにコインを渡した";
		mes "　冒険者のみとなります‐";
		close;
	case 2:
		mes "[ノローキア]";
		mes "あの方をお救いください。";
		next;
		mes "‐「紫色の竜」クエストにおいて、";
		mes "　あなたが^FF0000パーティーリーダー^000000になり、";
		mes "　メモリアルダンジョン「霧の森」";
		mes "　にいる「謎の青年」に話しかけ、";
		mes "　「ノローキアの歌を歌う」を";
		mes "　選択することで、‐";
		next;
		mes "‐彷徨う紫色の竜を倒さなくても";
		mes "　クエストを進行できるように";
		mes "　なりました‐";
		next;
		mes "‐なお、彷徨う紫色の竜を倒さなくても";
		mes "　「紫色の竜」クエストが";
		mes "　進行できるのは、";
		mes "　ノローキアにコインを渡した";
		mes "　冒険者のみとなります‐";
		close;
	case 3:
		mes "[ノローキア]";
		mes "あの方をお救いください。";
		close;
	case 4:
		mes "[ノローキア]";
		mes "あの方を、守護者を";
		mes "お救いくださったのですね！";
		next;
		mes "[ノローキア]";
		mes "ありがとうございました。";
		mes "あなたにはいくら感謝しても";
		mes "感謝しきれません。";
		next;
		mes "[ノローキア]";
		mes "……";
		next;
		mes "[ノローキア]";
		mes "これで私もここから";
		mes "離れることができます。";
		next;
		mes "[ノローキア]";
		mes "あなたが守護者を";
		mes "救ってくれたおかげか";
		mes "少しだけ私の記憶が戻りました。";
		next;
		mes "[ノローキア]";
		mes "私は守護者の侍従。";
		mes "ずっと守護者のお側に";
		mes "仕えていました。";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "守護者がイグドラシルから";
		mes "いなくなった後、";
		mes "私は、邪悪な竜により";
		mes "生命を奪われました。";
		next;
		mes "[ノローキア]";
		mes "生命を失ったこのような状態でも、";
		mes "守護者をお救いしたくて";
		mes "この世界にとどまっていたのです。";
		next;
		mes "[ノローキア]";
		mes "あなたのおかげで";
		mes "守護者が救われて、";
		mes "私の願いもかないました。";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "どうやら、私はもうここから";
		mes "離れなくてはいけないようです。";
		mes "あなたには心から感謝しています。";
		next;
		mes "[ノローキア]";
		mes "……";
		mes "最初に、なぜ、あなただけに";
		mes "私の声が届くのかと";
		mes "不思議に思いました。";
		next;
		mes "[ノローキア]";
		mes "でも今はわかります。";
		mes "私の願い、守護者を救うことができる";
		mes "力を持つ者だから";
		mes "あなたに声が届いたのでしょう。";
		next;
		mes "[ノローキア]";
		mes "それでは私はそろそろ離れます。";
		mes "この世界からいなくなるわけでは";
		mes "ありませんよ。";
		mes "イグドラシルの元へ戻るだけです。";
		mes "そして、あなたの冒険を";
		mes "見守りましょう。";
		next;
		mes "‐ノローキアが微笑むと、";
		mes "　だんだんと姿は消えて行き、";
		mes "　やがて何も見えなくなった‐";
		set BIF_2QUE,100;
		set BIF_2QUE_SUB,0;
		close;
	}
}

1@mist.gat,94,24,0	script	mora_ensyutu_1	139,{}
1@mist.gat,84,33,0	script	mora_ensyutu_2	139,{}
1@mist.gat,94,27,0	script	mora_ensyutu_3	139,{}
1@mist.gat,76,41,0	script	mora_ensyutu_4	139,{}
1@mist.gat,76,32,0	script	mora_ensyutu_5	139,{}
1@mist.gat,81,23,0	script	mora_ensyutu_6	139,{}

//============================================================
// ロペの捜索クエスト
//- Registry -------------------------------------------------
// BIF_3QUE -> 0～
//------------------------------------------------------------
mora.gat,117,66,3	script	ユリディ#mora	521,{
	if(ASH_1QUE < 100 || BaseLevel < 100) {	//異世界クエスト未クリア
		mes "[ユリディ]";
		mes "ねえ、ちょっと。";
		mes "私のロペを……";
		mes "　";
		mes "あら。";
		next;
		mes "[ユリディ]";
		mes "ごめんなさい。";
		mes "なんでもないわ。";
		next;
		mes "[ユリディ]";
		mes "……人を探してるの。";
		mes "でも、あなたじゃ";
		mes "聞いても無駄そう。";
		mes "だから、ごめんなさい。";
		next;
		if(ASH_1QUE < 100) {	//異世界クエスト未クリア
			mes "‐クエストを受けるには";
			mes "　異世界クエストをクリアする";
			mes "　必要があるようだ‐";
			close;
		}
		else {
			mes "‐このクエストを進行するには";
			mes "　レベルが満たないようです。";
			mes "　^FF0000Baseレベル100^000000になったら";
			mes "　再度話しかけてください‐";
			close;
		}
	}
	switch(BIF_3QUE) {
	case 0:
		mes "[ユリディ]";
		mes "ねえ、ちょっと。";
		mes "もしかして、あなたが";
		mes "霧の森を通ってきた人？";
		next;
		mes "[ユリディ]";
		mes "霧の森を通ってきたなら、";
		mes "ロペを見ませんでしたか？";
		mes "私の婚約者なんです。";
		next;
		if(select("見た","見てない") == 1) {
			mes "[ユリディ]";
			mes "えっ本当!?";
			mes "どこで見ました？";
			mes "彼は元気でしたか？";
			next;
			mes "‐ユリディは";
			mes "　あなたの両肩をつかみ";
			mes "　何度も揺さぶってきた！‐";
			next;
			mes "‐揺れる視界から";
			mes "　開放されたくなったあなたは";
			mes "　ロペという人物を";
			mes "　本当は見ていないことを";
			mes "　ユリディに告げた‐";
			next;
			mes "[ユリディ]";
			mes "はあ!?";
			mes "ウソなんですか？";
			mes "ウソなんですか！";
			emotion 36;
			next;
			mes "[ユリディ]";
			mes "そういうのやめてください。";
			mes "私、真剣なんです!!";
			close;
		}
		mes "[ユリディ]";
		mes "そうですか";
		mes "見てませんか……";
		next;
		mes "[ユリディ]";
		mes "ああ、ロペ。";
		mes "どこにいるの……";
		mes "ずっと探しているのに。";
		next;
		mes "[ユリディ]";
		mes "彼になにかあったら";
		mes "私……";
		next;
		mes "[ユリディの友達]";
		mes "ユリディ……";
		mes "しっかりして。";
		next;
		mes "[ユリディ]";
		mes "あ……そう、そうね。";
		mes "ロペはきっと帰ってくるもの。";
		mes "私、あきらめない。";
		next;
		mes "[ユリディ]";
		mes "あ、あの！";
		mes "　";
		mes "‐ユリディはあなたの手をとり、";
		mes "　真剣な眼差しを向けてきた‐";
		next;
		mes "[ユリディ]";
		mes "ロペを、彼を探してください！";
		next;
		mes "[ユリディ]";
		mes "あなたは霧の森を";
		mes "通ってきたんでしょう？";
		mes "これも縁と思って……";
		mes "お願いします！";
		next;
		mes "[ユリディの友達]";
		mes "わたしからもお願い！";
		mes "ユリディは、ロペが心配で";
		mes "単身、モーラに来たの。";
		mes "それほど心配してるの！";
		next;
		if(select("忙しいので断る","手伝います！") == 1) {
			mes "[ユリディ]";
			mes "そんな……！";
			next;
			mes "[ユリディの友達]";
			mes "ひどい!!";
			emotion 6,"ユリディの友達#mora";
			next;
			mes "[ユリディの友達]";
			mes "手伝ってくれたっていいじゃない！";
			mes "ああ、ユリディ……";
			mes "大丈夫。わたしたちだけででも";
			mes "ロペを探そう。";
			next;
			mes "[ユリディ]";
			mes "……";
			close;
		}
		mes "[ユリディ]";
		mes "ああ、ありがとう……！";
		mes "心から感謝するわ！";
		next;
		mes "‐ユリディは";
		mes "　ロペの容姿などの特徴を";
		mes "　ひとつひとつ、あなたに伝えた‐";
		next;
		mes "[ユリディ]";
		mes "ロペは旅人たちにガイドとして雇われ";
		mes "霧の森へ行ってしまったと";
		mes "聞きました。";
		next;
		mes "[ユリディ]";
		mes "でも、ロペと一緒に";
		mes "行ったはずの方が一人、";
		mes "旅館にいるんです。";
		next;
		mes "[ユリディ]";
		mes "なのに、";
		mes "ロペはいない……";
		mes "私が探していると知ったら";
		mes "すぐに姿を見せてくれるに";
		mes "違いないのに！";
		next;
		mes "[ユリディの友達]";
		mes "わたしたち、";
		mes "旅館にいる旅人にも";
		mes "会いに行ったわ！";
		next;
		mes "[ユリディ]";
		mes "ロペを知らないか";
		mes "聞きに行きました。";
		mes "でも、その旅人……";
		mes "^FF0000ピット^000000というそうですけど、";
		mes "面会を拒否されてしまって……";
		next;
		mes "[ユリディの友達]";
		mes "あの態度は絶対、";
		mes "なにか知ってるはずです!!";
		next;
		mes "[ユリディ]";
		mes "わたしたちじゃ、";
		mes "警戒されちゃってダメだけど";
		mes "あなたになら話してくれるかも";
		mes "しれません。";
		next;
		mes "[ユリディ]";
		mes "ピットを訪ねてもらえますか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ユリディの恋人ロペを";
		mes "見つけるため、";
		mes "旅館にいる^FF0000ピット^000000に";
		mes "話を聞いてみよう）";
		set BIF_3QUE,1;
		setquest 1109;
		delquest 71186;
		close;
	case 1:
		mes "[ユリディ]";
		mes "ピットの居場所を";
		mes "忘れてしまいましたか？";
		mes "彼は^FF0000旅館^000000にいます。";
		mes "部屋に閉じこもってるんです。";
		close;
	case 2:
		mes "[ユリディ]";
		mes "ピットに会ったんですね！";
		mes "ロペのこと、";
		mes "何か言ってましたか!?";
		next;
		mes "‐あなたは、ピットから聞いた話を";
		mes "　ユリディに伝えた‐";
		next;
		mes "[ユリディ]";
		mes "そんな！";
		mes "ロペが人を見捨てて逃げるなんて";
		mes "ありえない話です!!";
		next;
		mes "[ユリディの友達]";
		mes "そうですよ！";
		mes "ロペは一度引き受けたことは";
		mes "絶対に投げ出さない人だもの。";
		mes "ガイドの仕事だって";
		mes "ちゃんとやるに決まってる！";
		next;
		mes "[ユリディ]";
		mes "わ、私、信じません。";
		mes "ピットはきっと";
		mes "嘘をついてます！";
		next;
		mes "[ユリディ]";
		mes "……ただ、";
		mes "ピットが一度は霧の森に";
		mes "行ったことが本当なら";
		mes "ロペも同行したに違いありません。";
		next;
		mes "[ユリディ]";
		mes "もしかしたら、";
		mes "なにか痕跡が残ってるかも……";
		next;
		mes "[ユリディ]";
		mes "霧の森に行って";
		mes "^FF0000ロペの手掛かり^000000がないか";
		mes "探してきてくれませんか？";
		mes "お願いします！";
		next;
		mes "[ユリディ]";
		mes "それを証拠として";
		mes "ピットにつきつければ";
		mes "今度こそ本当のことを";
		mes "話してくれるかもしれません。";
		set BIF_3QUE,3;
		chgquest 1110,1111;
		close;
	case 3:
		mes "[ユリディ]";
		mes "霧の森に行って";
		mes "^FF0000ロペの手掛かり^000000がないか";
		mes "探してきてくれませんか？";
		next;
		mes "[ユリディ]";
		mes "それを証拠として";
		mes "ピットにつきつければ";
		mes "今度こそ本当のことを";
		mes "話してくれるかもしれません。";
		next;
		mes "[ユリディ]";
		mes "ロペの無実を";
		mes "証明するんです。";
		mes "お願いします！";
		if(countitem(6383) >= 30) {
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（ロペの手掛かりを30個集めた。";
			mes "宿にいるピットに見せに行こう）";
		}
		close;
	case 4:
		mes "[ユリディ]";
		mes "ピットは本当のことを";
		mes "話してくれましたか？";
		next;
		mes "‐あなたは、ピットから聞いた話を";
		mes "　ユリディに伝えた‐";
		next;
		mes "[ユリディ]";
		mes "……理解できません。";
		mes "どうして、ピットはそこまで……";
		next;
		mes "[ユリディの友達]";
		mes "こんなにたくさん、";
		mes "証拠をつきつけてるのに";
		mes "白状しないなんて……";
		mes "　";
		mes "あら？";
		next;
		mes "[ユリディの友達]";
		mes "ねえ、";
		mes "ちょっとその手掛かり";
		mes "見せてくれない？";
		next;
		mes "[ユリディ]";
		mes "どうしたの？";
		next;
		mes "[ユリディの友達]";
		mes "うん……";
		mes "これパズルみたいにパーツが";
		mes "ぴったり合うの。";
		mes "もしかしたら……";
		next;
		mes "‐ユリディの友達は";
		mes "　ロペの手掛かりを一つ一つ";
		mes "　並べて、組み合わせた‐";
		next;
		mes "[ユリディ]";
		mes "……あ、これっ！";
		next;
		mes "[ロペの手紙]";
		mes "^0000FFもう何日も、霧の森をさまよっている。";
		mes "依頼人たちを守るどころか、";
		mes "オレが猛毒にやられて";
		mes "足手まといになってしまった。^000000";
		next;
		mes "[ロペの手紙]";
		mes "^0000FFなさけねぇ……";
		mes "こんなだから、";
		mes "スプレンディッドの遠征隊を";
		mes "はずされるんだよな。^000000";
		next;
		mes "[ロペの手紙]";
		mes "^0000FFでも、依頼人の一人だけは";
		mes "無事に守りきった。";
		mes "きっと彼がこの手紙と指輪を";
		mes "あなたに渡してくれるだろう。^000000";
		next;
		mes "[ロペの手紙]";
		mes "^0000FF……本当なら、";
		mes "遠征隊の一員になった時に";
		mes "立派にプロポーズをしたかった。^000000";
		next;
		mes "[ロペの手紙]";
		mes "^0000FFごめん、ユリディ。";
		mes "すぐ、会いに行くから。^000000";
		next;
		mes "[ユリディ]";
		mes "そんな……";
		next;
		mes "[ユリディ]";
		mes "ちがう……";
		mes "ロペは無事よ。";
		mes "きっと戻ってくるわ……";
		next;
		mes "‐ロペの手紙を読んだユリディは";
		mes "　まるで魂を抜かれたかのように";
		mes "　立ちつくしている‐";
		next;
		mes "[ユリディの友達]";
		mes "ユリディ……";
		next;
		mes "[ユリディの友達]";
		mes "……でも、これが";
		mes "霧の森に散らばっていたって";
		mes "どういうこと？";
		next;
		mes "[ユリディの友達]";
		mes "彼が手紙と指輪を";
		mes "渡してくれるだろうってあるけど";
		mes "この彼って";
		mes "……ピットのこと？";
		next;
		mes "[ユリディの友達]";
		mes "だったらどうして、";
		mes "本当のことを言ってくれないの!?";
		mes "ユリディはロペに";
		mes "会いたがっていたのに!!";
		next;
		mes "‐ユリディの友達が";
		mes "　怖い目つきで、";
		mes "　あなたを見た‐";
		next;
		mes "[ユリディの友達]";
		mes "お願いがあります。";
		next;
		mes "[ユリディの友達]";
		mes "この復元した手紙を";
		mes "ピットの奴に";
		mes "叩きつけてやってください!!";
		mes "そして、今度こそ";
		mes "本当のことを白状させて！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（旅館にいる^FF0000ピット^000000に";
		mes "話を聞いてこよう）";
		set BIF_3QUE,5;
		chgquest 1112,1113;
		delitem 6383,30;
		close;
	case 5:
		mes "[ユリディ]";
		mes "ちがう……";
		mes "ロペは無事よ。";
		mes "きっと戻ってくるわ……";
		next;
		mes "[ユリディの友達]";
		mes "ユリディ……";
		next;
		mes "[ユリディの友達]";
		mes "この復元した手紙を";
		mes "ピットの奴に";
		mes "叩きつけてやってください!!";
		close;
	case 6:
		mes "‐" +strcharinfo(0)+ "は";
		mes "　ロペの指輪を手に";
		mes "　ユリディを訪ねた‐";
		next;
		mes "‐ユリディはうつむき、";
		mes "　小さい声で歌っている‐";
		next;
		mes "[ユリディの友達]";
		mes "……ユリディは今、";
		mes "大きな悲しみで不安定になった心を";
		mes "なぐさめるため、";
		mes "治癒の歌を歌っています。";
		next;
		mes "[ユリディの友達]";
		mes "それにしても";
		mes "ロペが……";
		mes "ユリディ、かわいそうに……";
		next;
		mes "[ユリディの友達]";
		mes "……あ。";
		mes "　";
		mes "‐ユリディの友達が不意に";
		mes "　声をあげた‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（どうしたんだろう……";
		mes "ユリディの友達に話を";
		mes "聞いてみよう）";
		close;
	case 7:
	case 8:
		mes "‐ユリディはうつむき、";
		mes "　小さい声で歌っている。";
		mes "　歌詞は";
		mes "　聞き取ることができない‐";
		close;
	case 9:
		mes "‐ユリディはうつむき、";
		mes "　小さい声で歌っている‐";
		next;
		mes "[ユリディ]";
		mes "ロペ……";
		mes "どこにいるの？";
		next;
		if(select("見つからなかったと言う","ロペの死を伝える") == 1) {
			mes "[ユリディ]";
			mes "うそよ……";
			mes "うそうそ！";
			mes "ロペは言ったわ！";
			mes "帰るって言った！";
			close;
		}
		mes "[ユリディ]";
		mes "うそよ……";
		mes "だって、ロペは";
		mes "すぐ戻るって……";
		mes "そんな、そんなこと……";
		next;
		mes "‐あなたはピットから取り戻した";
		mes "　ロペの指輪を彼女に渡した‐";
		next;
		mes "[ユリディ]";
		mes "これは……";
		next;
		mes "[ユリディ]";
		mes "……";
		mes "　";
		mes "彼にはもう会えないの？";
		next;
		mes "‐ユリディはロペの指輪を";
		mes "　握りしめ、涙をこぼした‐";
		set BIF_3QUE,10;
		chgquest 1116,1117;
		delitem 6384,1;
		close;
	case 10:
		// 未調査
	case 11:
		mes "‐ユリディはロペの指輪をはめ、";
		mes "　涙を流しながら";
		mes "　歌っている‐";
		close;
	}
OnInit:
	waitingroom "ロぺの捜索",0;
	end;
}

mora.gat,115,68,3	script	ユリディの友達#mora	520,{
	switch(BIF_3QUE) {
	case 2:
		mes "[ユリディの友達]";
		mes "ロペにガイドを頼んだっていう";
		mes "ピットが何か知ってるに";
		mes "決まってます！";
		mes "問い詰めてください！";
		close;
	case 3:
		mes "[ユリディの友達]";
		mes "ロペったら、ユリディを";
		mes "こんなに心配させて！";
		mes "見つかったら";
		mes "説教しちゃうんだから！";
		next;
		mes "[ユリディの友達]";
		mes "ピットの奴も";
		mes "早く口を割ればいいのに！";
		close;
	case 4:
		mes "[ユリディの友達]";
		mes "ピットの奴、";
		mes "白状しましたか？";
		mes "えっ、まだ？";
		next;
		mes "[ユリディの友達]";
		mes "……もうっ";
		mes "ユリディがいなかったら";
		mes "わたしが直接脅しを";
		mes "かけてやるのに！";
		mes "サイテーっ";
		close;
	case 5:
		mes "[ユリディの友達]";
		mes "ユリディ……";
		next;
		mes "[ユリディの友達]";
		mes "この復元した手紙を";
		mes "ピットの奴に";
		mes "叩きつけてやってください!!";
		close;
	case 6:
		mes "‐" +strcharinfo(0)+ "は";
		mes "　ロペの指輪を手に";
		mes "　ユリディを訪ねた‐";
		next;
		mes "‐ユリディはうつむき、";
		mes "　小さい声で歌っている。";
		mes "　" +strcharinfo(0)+ "が";
		mes "　いることにも気づいていないようだ‐";
		next;
		mes "[ユリディの友達]";
		mes "……ユリディは今、";
		mes "大きな悲しみで不安定になった心を";
		mes "なぐさめるため、";
		mes "治癒の歌を歌っています。";
		next;
		mes "[ユリディの友達]";
		mes "それにしても";
		mes "ロペが……";
		mes "ユリディ、かわいそうに……";
		next;
		mes "[ユリディの友達]";
		mes "……";
		next;
		mes "[ユリディの友達]";
		mes "……あ。";
		mes "でも、そうだ。";
		mes "最近、街に来た人から聞いたんですが";
		mes "霧の森の入り口で";
		mes "不審な人物を見たんですって。";
		next;
		mes "[ユリディの友達]";
		mes "その不審者を見るようになったのが";
		mes "ロペの失踪した時期と";
		mes "重なってるんです。";
		mes "もしかしたら……";
		next;
		mes "[ユリディの友達]";
		mes "これが最後の望みです。";
		mes "その不審な人物を";
		mes "調べてくれませんか。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（霧の森入り口に出没する";
		mes "不審者を調べよう）";
		set BIF_3QUE,7;
		chgquest 1114,1115;
		close;
	case 7:
		mes "[ユリディの友達]";
		mes "霧の森の入り口で不審者を";
		mes "見るようになったのが";
		mes "ロペの失踪した時期と";
		mes "重なってるんです。";
		mes "もしかしたら……";
		next;
		mes "[ユリディの友達]";
		mes "これが最後の望みです。";
		mes "その不審な人物を";
		mes "調べてくれませんか。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（霧の森入り口に出没する";
		mes "不審者を調べよう）";
		close;
	case 8:
	case 9:
		mes "[ユリディの友達]";
		mes "顔色が悪いですね。";
		mes "……よくない知らせですか？";
		close;
	case 10:
		mes "‐あなたはユリディの友達に";
		mes "　不審者の正体を";
		mes "　報告した‐";
		next;
		mes "[ユリディの友達]";
		mes "……!!";
		emotion 0;
		next;
		mes "[ユリディの友達]";
		mes "そうでしたか……";
		next;
		mes "[ユリディの友達]";
		mes "……このことは";
		mes "ユリディには知らせないほうが";
		mes "いいでしょうね。";
		next;
		mes "[ユリディの友達]";
		mes "知らせたら……";
		mes "ユリディはロペに会いに";
		mes "行ってしまうでしょうから。";
		next;
		mes "[ユリディの友達]";
		mes "そうなったら、";
		mes "ユリディは…ロペは…";
		next;
		mes "[ユリディの友達]";
		mes "……";
		next;
		mes "[ユリディの友達]";
		mes "……ロペを探すのを";
		mes "手伝ってくださって";
		mes "ありがとうございました。";
		mes "これ、お礼です。";
		delquest 1117;
		setquest 201365;
		set BIF_3QUE,11;
		if(checkre()) {
			getexp 500000,250000;
			getexp 500000,250000;
		}
		else {
			getexp 5000000,2500000;
			getexp 5000000,2500000;
		}
		getitem 6380,10;
		next;
		mes "[ユリディの友達]";
		mes "……わたし、";
		mes "ユリディが元気になるまで";
		mes "そばについてます。";
		next;
		mes "[ユリディの友達]";
		mes "ユリディが元気になったら、";
		mes "私、ロペが元に戻る方法を";
		mes "さがしてみます。";
		mes "正直、自信ないですけど。";
		next;
		mes "[ユリディの友達]";
		mes "でも、初めから諦めていても";
		mes "仕方ないですよね。";
		mes "わたし、ユリディの笑顔が";
		mes "見たいんです。";
		close;
	case 11:
		mes "[ユリディの友達]";
		mes "ロペを探すのを";
		mes "手伝ってくださって";
		mes "ありがとうございました。";
		next;
		mes "[ユリディの友達]";
		mes "……わたし、";
		mes "ユリディが元気になるまで";
		mes "そばについてます。";
		next;
		mes "[ユリディの友達]";
		mes "ユリディが元気になったら、";
		mes "私、ロペが元に戻る方法を";
		mes "さがしてみます。";
		mes "正直、自信ないですけど。";
		next;
		mes "[ユリディの友達]";
		mes "でも、初めから諦めていても";
		mes "仕方ないですよね。";
		mes "わたし、ユリディの笑顔が";
		mes "見たいんです。";
		close;
	default:
		mes "[ユリディの友達]";
		mes "どうかユリディを";
		mes "助けてあげてください。";
		mes "彼女は失踪した恋人を探すために";
		mes "ここまで来たんです。";
		close;
	}
}

mora.gat,65,145,3	script	ピット	519,{
	switch(BIF_3QUE) {
	case 1:
		mes "[ピット]";
		mes "……おい。";
		mes "なんだ、アンタ。";
		next;
		mes "[ピット]";
		mes "俺は今、具合が悪いんだ。";
		mes "またユリディとかいう女の";
		mes "差し金じゃねえだろうな？";
		next;
		mes "‐あなたはロペのことを";
		mes "　たずねた‐";
		next;
		mes "[ピット]";
		mes "……ほんっとしつけえな！";
		mes "わかったよ話してやるよ!!";
		next;
		mes "[ピット]";
		mes "ロペの野郎はな、";
		mes "あの霧の森で";
		mes "めちゃくちゃなガイドをした挙句、";
		mes "モンスターに囲まれた時";
		mes "俺たちを見捨てて";
		mes "とんずらしやがったんだ!!";
		next;
		mes "[ピット]";
		mes "そこから俺一人だけが";
		mes "命からがら";
		mes "モーラに戻ってこれた。";
		mes "アイツのその後なんて";
		mes "しらねえ。しりたくもない！";
		next;
		mes "[ピット]";
		mes "……ほら、話してやったぞ。";
		mes "あの女に一字一句正確に";
		mes "伝えろよな！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ピットの話を";
		mes "ユリディに伝えよう）";
		set BIF_3QUE,2;
		chgquest 1109,1110;
		close;
	case 2:
		mes "[ピット]";
		mes "ロペの野郎はな、";
		mes "あの霧の森で";
		mes "めちゃくちゃなガイドをした挙句、";
		mes "モンスターに囲まれた時";
		mes "俺たちを見捨てて";
		mes "とんずらしやがったんだ!!";
		next;
		mes "[ピット]";
		mes "そこから俺一人だけが";
		mes "命からがら";
		mes "モーラに戻ってこれた。";
		next;
		mes "[ピット]";
		mes "わかったか。";
		mes "わかったなら、さっさと去れ！";
		mes "俺は今、具合が悪いんだ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ピットの話を";
		mes "ユリディに伝えよう）";
		close;
	case 3:
		if(countitem(6383) < 30) {
			mes "[ピット]";
			mes "わかったか。";
			mes "わかったなら、さっさと去れ！";
			mes "俺は今、具合が悪いんだ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（霧の森に行って";
			mes "^FF0000ロペの手掛かり^000000を探し、";
			mes "ピットに見せよう。";
			mes "ロペの手掛かりなる物は";
			mes "30個ほどあればよいだろう）";
			close;
		}
		mes "[ピット]";
		mes "……なんだそりゃ。";
		mes "紙切れの束なんぞ";
		mes "持ってきやがって。";
		next;
		mes "‐あなたはピットに";
		mes "　ロペのことを聞いた‐";
		next;
		mes "[ピット]";
		mes "だから！";
		mes "しるかよ!!";
		next;
		mes "[ピット]";
		mes "俺は被害者なんだぞ。";
		mes "ユリディとかいう女のせいで";
		mes "怪我だってなおりゃしねえ！";
		next;
		mes "[ピット]";
		mes "俺はさっさと傷を治して";
		mes "この街を出たいんだ。";
		mes "ゆっくり休ませろよ！";
		next;
		mes "‐ピットはどうあっても";
		mes "　ロペのことを話してくれそうにない‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（とりあえず、このことを";
		mes "ユリディに報告しよう）";
		set BIF_3QUE,4;
		chgquest 1111,1112;
		close;
	case 4:
		mes "[ピット]";
		mes "俺はさっさと傷を治して";
		mes "この街を出たいんだ。";
		mes "ゆっくり休ませろよ！";
		next;
		mes "‐ピットはどうあっても";
		mes "　ロペのことを話してくれそうにない‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（とりあえず、このことを";
		mes "ユリディに報告しよう）";
		close;
	case 5:
		if(checkitemblank() == 0) {
			mes "‐所持アイテムの種類数が多い為";
			mes "　報酬を受け取ることができません。";
			mes "　アイテムを整理してから、";
			mes "　再度報告してください‐";
			close;
		}
		mes "‐あなたはピットに";
		mes "　ロペの手紙をつきつけた‐";
		next;
		mes "[ピット]";
		mes "いきなりなんだよ！";
		next;
		mes "[ピット]";
		mes "……";
		next;
		mes "‐それがロペの手紙だと気づいたのか";
		mes "　ピットの顔色が一気に悪くなった‐";
		next;
		mes "[ピット]";
		mes "……チッ、";
		mes "バラバラにして捨てたのに、";
		mes "まさかそれを探して";
		mes "復元させるなんてな。";
		next;
		mes "[ピット]";
		mes "……";
		next;
		mes "[ピット]";
		mes "ロペとは";
		mes "霧の森の出口まで";
		mes "一緒にいたんだよ。";
		mes "けど、そこで倒れた。";
		next;
		mes "[ピット]";
		mes "俺は奴を街まで連れていくべきか";
		mes "悩んだ。";
		next;
		mes "[ピット]";
		mes "そしたら、ロペは";
		mes "俺に……";
		mes "アンタが今持ってる手紙と、";
		mes "指輪を渡してきたんだ。";
		next;
		mes "[ピット]";
		mes "ラフィネ族ではない者には";
		mes "決して手に入れられない";
		mes "ラフィネ族の指輪を。";
		next;
		mes "[ピット]";
		mes "ラフィネ族じゃない俺には";
		mes "素晴らしい宝だ！";
		mes "それが俺の手の中にある。";
		mes "手放すなんてできるか!?";
		next;
		mes "[ピット]";
		mes "……本当はすぐこの街を";
		mes "離れるつもりだった。";
		mes "けど、俺も猛毒にやられてて、";
		mes "休んでたら、あの女につきまとわれ、";
		mes "ついにはバレちまった！";
		next;
		mes "[ピット]";
		mes "悪いことはできないってことか。";
		mes "女の執念に負けたってことか。";
		next;
		mes "‐ピットは";
		mes "　指輪をあなたにむかって";
		mes "　投げた‐";
		next;
		mes "[ピット]";
		mes "それがロペの指輪だよ。";
		mes "これでいいんだろ。";
		mes "もう俺につきまとうな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……ロペはどこに？";
		next;
		mes "[ピット]";
		mes "……霧の森の出口で";
		mes "死んだって言ったろ。";
		mes "その辺にいるんだろう。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（……ロペの指輪を";
		mes "ユリディに届けてあげよう）";
		set BIF_3QUE,6;
		chgquest 1113,1114;
		getitem 6384,1;
		close;
	case 6:
		mes "[ピット]";
		mes "ロペなら霧の森で死んだ。";
		mes "指輪も返したんだから";
		mes "もう俺につきまとうなよ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（……ロペの指輪を";
		mes "ユリディに届けてあげよう）";
		close;
	case 7:
	case 8:
		mes "[ピット]";
		mes "なんだよ。";
		mes "まだなんかあるのかよ。";
		mes "……ゆっくり休みたいんだ。";
		mes "帰ってくれ！";
		close;
	case 9:
	case 10:
	case 11:
		mes "‐ピットは眠っている。";
		mes "　深い眠りにあるようで、";
		mes "　あなたの存在に";
		mes "　気づいた様子はない‐";
		close;
	default:
		mes "[ピット]";
		mes "霧の森を無事に通過するなんて";
		mes "アンタ、いい腕持ってんだな。";
		mes "俺もアンタに案内を";
		mes "頼むんだったぜ……ふう。";
		next;
		mes "[ピット]";
		mes "……おい。";
		mes "いつまでここにいんだ。";
		next;
		mes "[ピット]";
		mes "俺は今、具合が悪いんだ。";
		mes "アンタの武勇伝を";
		mes "聞いてやる余裕はねえぞ。";
		close;
	}
}

bif_fild01.gat,132,338,3	script	ロペ#mora	461,2,2,{
	if(BIF_3QUE != 8) {
		mes "‐うつろな目をした";
		mes "　怪しい男がいる‐";
		close;
	}
	if(BIF_3QUE == 9) {
		mes "‐ロぺは森の奥に消えて行った‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（……ユリディの元に行こう）";
		close;
	}
	if(BIF_3QUE >= 10) {
		mes "‐ロぺは森の奥に消えて行った‐";
		close;
	}
	mes "‐男は目を押さえ、";
	mes "　うめき声をあげている‐";
	setnpcdisplay "ロペ#mora",999;
	next;
	mes "[怪しい男]";
	mes "クウウウウウウアアッ";
	mes "目が、目が!!";
	mes "生命の輝きが痛い!!!!";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "あなたはロペですか？";
	next;
	mes "[ロペ]";
	mes "誰だお前！";
	mes "何故オレの名を!!";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "ユリディがあなたを探しています。";
	next;
	mes "[ロペ]";
	mes "ユ……!?";
	mes "ウワアアアアッ!!!!";
	next;
	mes "[ロペ]";
	mes "亡霊よ、残酷な亡霊！";
	mes "この身に呪いを抱える代わりに";
	mes "ユリディの名をオレの中から";
	mes "消してくれと頼んだではないか!!";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "どうしてそんなことを!?";
	next;
	mes "[ロペ]";
	mes "……人を守りたいという思いが";
	mes "オレを死へと追いやった!!";
	next;
	mes "[ロペ]";
	mes "死にたくないと思う心が";
	mes "オレを魔物へと導いた！";
	mes "反故にされた約束が";
	mes "オレを怒りに狂わせた!!";
	next;
	mes "[ロペ]";
	mes "魔物になってしまった……";
	mes "オレはもう、生命の側には";
	mes "いられない。";
	next;
	mes "[ロペ]";
	mes "この身が死体から";
	mes "完全な魔物へと変わったら";
	mes "オレは霧の森の魔物として";
	mes "お前達に牙を向けるだろう！";
	next;
	mes "[ロペ]";
	mes "去れ!!";
	mes "オレはユリディを";
	mes "忘れなければ……!!";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "ロペの思いは届いています。";
	next;
	mes "‐あなたは、ユリディと";
	mes "　ユリディの友達が復元した手紙を";
	mes "　ロペに渡した‐";
	next;
	mes "[ロペ]";
	mes "……これは！";
	mes "ユリディの温もりを……";
	mes "感じる。";
	next;
	mes "[ロペ]";
	mes "オレの思いは、";
	mes "ユリディに届いたのか？";
	next;
	mes "[ロペ]";
	mes "……";
	next;
	mes "[ロペ]";
	mes "……そうか。";
	next;
	mes "[ロペ]";
	mes "しかし、オレはもう";
	mes "魔物となってしまった。";
	mes "彼女の元へ帰ることはできない。";
	next;
	mes "[ロペ]";
	mes "ユリディには、";
	mes "オレは霧の森の肥やしになったと";
	mes "伝えてくれ。";
	next;
	mes "[ロペ]";
	mes "彼女は悲しんでくれるだろう。";
	mes "しかし、時がいつか";
	mes "彼女をなぐさめる。";
	next;
	mes "[ロペ]";
	mes "……オレは遠くから";
	mes "彼女を思い、";
	mes "魔物として生きていくから。";
	next;
	mes "‐ロペだった魔物が、";
	mes "　霧の森からモーラの街を";
	mes "　見つめた‐";
	next;
	mes "‐その左手の指には";
	mes "　恋人にあげたものと";
	mes "　おそろいの指輪が";
	mes "　控えめに光っていた‐";
	next;
	mes "‐そして、";
	mes "　ロぺは森の奥に消えて行った‐";
	next;
	mes "["+strcharinfo(0)+"]";
	mes "（……ユリディの元に行こう）";
	set BIF_3QUE,9;
	chgquest 1115,1116;
	hideonnpc;
	initnpctimer;
	close;
OnTouch:
	if(BIF_3QUE == 7) {
		mes "‐うつろな目をした男がいる‐";
		next;
		mes "‐ユリディの友達が言っていた";
		mes "　怪しい男だろうか‐";
		next;
		if(select("無視する","声をかけてみる") == 1) {
			mes "‐あなたは怪しい男に";
			mes "　声をかけず、立ち去った‐";
			hideonnpc;
			initnpctimer;
			close;
		}
		mes "[怪しい男]";
		mes "……";
		hideonnpc;
		initnpctimer;
		next;
		mes "‐男のうつろな目が";
		mes "　ゆっくりとあなたに向いた‐";
		next;
		mes "[怪しい男]";
		mes "……ク";
		next;
		mes "[怪しい男]";
		mes "クウウウウウウアアッ!!!!!!";
		next;
		mes "‐男は目を押さえ、";
		mes "　うめき声をあげた‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（怪しい男に話しかけよう）";
		set BIF_3QUE,8;
		close;
	}
	end;
OnTimer1000:
	setnpcdisplay "ロペ#mora",461;
	hideoffnpc;
	stopnpctimer;
	end;
}

//============================================================
// モーラの温泉調査クエスト
//- Registry -------------------------------------------------
// BIF_4QUE -> 0～22
// BIF_4QUE_SUB -> オッシーの懲らしめ数
//------------------------------------------------------------
mora.gat,31,138,6	script	レシア研究員#mora	522,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[レシア研究員]";
		mes "ああ、どうしよう……";
		mes "大事な大事な、私の実験道具が";
		mes "……しかし、あそこに戻るのも";
		mes "ううむむ……";
		next;
		mes "[レシア研究員]";
		mes "誰か手伝ってくれる人は";
		mes "いないものか……";
		next;
		mes "‐クエストを受けるには";
		mes "　異世界クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	switch(BIF_4QUE) {
	case 0:
		mes "[レシア研究員]";
		mes "ああ、どうしよう……";
		mes "大事な大事な、私の実験道具が";
		mes "……しかし、あそこに戻るのも";
		mes "ううむむ……";
		next;
		mes "‐頭を悩ませている";
		mes "　学者らしき者がいる‐";
		emotion 28;
		next;
		menu "どうかしましたか？",-,"何を悩んでいるんですか？",-;
		mes "‐学者はあなたに気づいた‐";
		emotion 1;
		next;
		if(BaseLevel < 100) {
			mes "[レシア研究員]";
			mes "あ……いや、";
			mes "確かに私は困ってるんだが";
			mes "……こういうことは言いたくないが";
			mes "君では力不足だ。";
			next;
			mes "[レシア研究員]";
			mes "まあ、";
			mes "気にかけてくれてありがとう。";
			next;
			mes "‐このクエストを進行するには";
			mes "　レベルが満たないようです。";
			mes "　^FF0000Baseレベル100^000000になったら";
			mes "　再度話しかけてください‐";
			close;
		}
		mes "[レシア研究員]";
		mes "……おや？";
		mes "君、見ない顔だね。";
		mes "もしかして別の世界から";
		mes "来たのかい？";
		next;
		mes "[レシア研究員]";
		mes "あの亀裂を越えて";
		mes "ここまで到達するとは";
		mes "なかなか……";
		next;
		mes "[レシア研究員]";
		mes "……";
		next;
		mes "[レシア研究員]";
		mes "君、ちょっとこっちにおいで。";
		mes "なに、簡単な実験だからね。";
		mes "怖くないよ。";
		mes "　";
		mes "‐学者はあやしい笑みを浮かべた‐";
		emotion 29;
		next;
		if(select("逃げる","逃げない") == 1) {
			mes "‐あなたは逃げた‐";
			next;
			mes "[レシア研究員]";
			mes "なんだ、逃げるのか。";
			mes "亀裂を越えてきたというから";
			mes "期待したのに、";
			mes "根性のない奴だな。";
			emotion 32;
			close;
		}
		mes "[レシア研究員]";
		mes "……";
		emotion 9;
		next;
		mes "[レシア研究員]";
		mes "ふむ、君は";
		mes "肝が据わっているようだね。";
		mes "私が試していたということにも";
		mes "気づいているのかな？";
		next;
		mes "[レシア研究員]";
		mes "まあ、実験とも言うかな。";
		mes "……他にも実験してみようか？";
		next;
		menu "そ、それはちょっと……",-;
		mes "[レシア研究員]";
		mes "ははは！";
		mes "冗談、冗談だよ。";
		mes "私は研究者だが、";
		mes "研究対象は人間ではないからね。";
		next;
		menu "よかったです",-;
		mes "[レシア研究員]";
		mes "納得してくれたかね。";
		mes "……ところで、君";
		mes "忙しいのかな？";
		mes "私を手伝ってほしいんだが……";
		next;
		if(select("手伝う","手伝わない") == 2) {
			mes "[レシア研究員]";
			mes "…そうか、残念だ。";
			mes "気が変わったら";
			mes "また話しかけておくれ。";
			close;
		}
		mes "[レシア研究員]";
		mes "ありがとう！";
		mes "さすが、私が見こんだ者だ。";
		emotion 21;
		next;
		mes "[レシア研究員]";
		mes "手伝ってもらいたいことと";
		mes "いうのはだね。";
		mes "そのまま研究の手伝いなのだ。";
		next;
		mes "[レシア研究員]";
		mes "ここ、モーラの街にある旅館には";
		mes "入ると傷を治癒する温泉があってね、";
		mes "私はそれをテーマにした";
		mes "研究をしているのだ。";
		next;
		mes "[レシア研究員]";
		mes "それでこの間、サンプル採取に";
		mes "温泉に入ったのだが、";
		mes "そこで^FF0000未確認生命体^000000に襲われてね、";
		mes "大事な研究道具を";
		mes "奪われてしまったのだよ！";
		next;
		menu "未確認生命体？",-;
		mes "[レシア研究員]";
		mes "そうなんだ！";
		mes "温泉に現れた謎の生命体！";
		mes "最近、やつが温泉の入浴者を";
		mes "襲う事件が多発しているのだよ。";
		next;
		mes "[レシア研究員]";
		mes "私はやつを、";
		mes "温泉に住む魔物、^FF0000オッシー^000000";
		mes "と呼んでいる！";
		next;
		menu "オッシー！",-;
		mes "[レシア研究員]";
		mes "オッシーのせいで";
		mes "私は研究をすることができない。";
		mes "研究を再開するには、";
		mes "まず道具がないと駄目だからね。";
		next;
		mes "[レシア研究員]";
		mes "そこでお願いだ！";
		mes "旅館の温泉に行って、";
		mes "私の研究道具を";
		mes "取り返してきてくれたまえ。";
		set BIF_4QUE,1;
		setquest 5016;
		delquest 71188;
		emotion 12;
		close;
	case 1:
		if(countitem(6385) < 1) {
			mes "[レシア研究員]";
			mes "おかえり。";
			mes "それで、私の研究道具は";
			mes "取り戻せたのかね？";
			emotion 1;
			next;
			mes "[レシア研究員]";
			mes "……そうか。まだか。";
			mes "あれがないと、私は非常に";
			mes "困るんだ。";
			mes "早く、見つけてきておくれ。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[レシア研究員]";
			mes "君、やたらと荷物が多いね。";
			mes "それじゃあ、いろいろと困るだろう。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		mes "[レシア研究員]";
		mes "おおっ！";
		mes "研究道具を取り返してくれたんだね！";
		next;
		mes "[レシア研究員]";
		mes "本当にありがとう。";
		mes "これで、研究を再開できるぞ。";
		next;
		menu "よかったですね",-;
		mes "[レシア研究員]";
		mes "うむ。";
		mes "君に助手を頼んで本当によかった。";
		mes "最近の若い者は、";
		mes "使える者が少なくてね。";
		mes "助手を探すのも毎回、一苦労なのさ。";
		next;
		mes "[レシア研究員]";
		mes "……おっと、";
		mes "愚痴はいけないね。";
		next;
		mes "[レシア研究員]";
		mes "では、私はこれから";
		mes "道具に損傷がないか確認するからね。";
		mes "君は少し休むといい。";
		mes "休憩が終わったら、";
		mes "また私に話しかけてほしい。";
		mes "そうしたら次のお願いをするよ。";
		delitem 6385,1;
		getitem 6380,1;
		set BIF_4QUE,2;
		delquest 5016;
		setquest 71300;
		close;
	case 2:
		mes "[レシア研究員]";
		mes "休憩は終わったのかい？";
		next;
		mes "[レシア研究員]";
		mes "では、次のお願いをしようかな。";
		mes "君には再び温泉に行って";
		mes "オッシーを懲らしめてもらいたい。";
		next;
		mes "[レシア研究員]";
		mes "研究を再開するにあたって、";
		mes "温泉でのサンプル採取から";
		mes "確認やらが必要だからね。";
		mes "その時に、またあいつに襲われたら";
		mes "困るんだよ。";
		next;
		mes "[レシア研究員]";
		mes "なに、息の根を止めてこいとまでは";
		mes "言わない。";
		mes "おとなしくさせるだけでいいんだ。";
		mes "そうだな……^FF00003回^000000ほど";
		mes "しつけてやれば、いいんじゃないかな。";
		next;
		mes "[レシア研究員]";
		mes "では頼んだよ。";
		mes "研究ができるようにするのは、";
		mes "助手の大事な役目だ。";
		delquest 71300;
		setquest 5017;
		set BIF_4QUE,3;
		close;
	case 3:
		mes "[レシア研究員]";
		mes "オッシーを";
		mes "しつけられたかい？";
		mes "まだなの？";
		next;
		menu "はい",-;
		mes "[レシア研究員]";
		mes "いけないな。";
		mes "助手は行動が早くなければ。";
		mes "研究には迅速さが必要なんだよ。";
		next;
		mes "[レシア研究員]";
		mes "温泉に行って、";
		mes "オッシーを^FF00003回^000000ほど";
		mes "こらしめておいで。";
		emotion 29;
		close;
	case 4:
		mes "[レシア研究員]";
		mes "ご苦労様。";
		mes "オッシーに";
		mes "脅しは十分に効果あったようだね。";
		mes "襲撃被害は、";
		mes "なりをひそめたようだ。";
		emotion 18;
		next;
		mes "[レシア研究員]";
		mes "さて。では、今のうちに";
		mes "研究を進めようか。";
		next;
		mes "[レシア研究員]";
		mes "君には、この^FF0000空の試験管^000000に";
		mes "温泉の水を";
		mes "採取してきてもらいたい。";
		next;
		mes "[レシア研究員]";
		mes "あ、とってくるサンプルは";
		mes "^FF000010個^000000ほど必要だよ。";
		mes "温泉に行って、その水のサンプルを";
		mes "10個だ。";
		next;
		mes "[レシア研究員]";
		mes "私はここで研究の準備をして";
		mes "待っているからね。";
		mes "よろしく頼むよ。";
		if(checkitemblank() == 0) {
			next;
			mes "[レシア研究員]";
			mes "……おや、君、荷物が多いよ。";
			mes "それじゃあ、手伝いを頼めない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		if(checkweight(1092,10) == 0) {
			next;
			mes "[レシア研究員]";
			mes "……といきたいが、荷物が多いね。";
			mes "それじゃあ、手伝いを頼めない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		getitem 1092,10;
		set BIF_4QUE,5;
		chgquest 5018,5019;
		close;
	case 5:
		if(countitem(6386) < 10) {
			mes "[レシア研究員]";
			mes "温泉のサンプルは";
			mes "まだなのか？";
			mes "なるべく早く採取してくれたまえ。";
			mes "私は待っているからな。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[レシア研究員]";
			mes "君、やたらと荷物が多いね。";
			mes "それじゃあ、いろいろと困るだろう。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		mes "[レシア研究員]";
		mes "温泉のサンプルだね。";
		mes "ご苦労様。";
		next;
		mes "[レシア研究員]";
		mes "では、さっそく分析に入るよ。";
		mes "そうだな……";
		mes "^FF000024時間^000000ほどかかるから";
		mes "君は休憩していてくれたまえ。";
		delitem 6386,10;
		getitem 6380,1;
		set BIF_4QUE,6;
		chgquest 5019,5020;
		close;
	case 6:
		if(!(checkquest(5020) & 2)) {
			mes "[レシア研究員]";
			mes "なんだ？";
			mes "まだ検査は終わっていないぞ。";
			mes "成分分析の結果というものは";
			mes "そんなすぐに出るものじゃないんだ。";
			close;
		}
		mes "[レシア研究員]";
		mes "よく来たね。";
		mes "ちょうど分析が終わったところだ。";
		next;
		mes "[レシア研究員]";
		mes "やはり、温泉の不思議な効果は";
		mes "水にも現れていたよ！";
		emotion 2;
		next;
		mes "[レシア研究員]";
		mes "そして、水の中に別の成分が";
		mes "混ざっていることも確認した。";
		mes "調べたところ、どうやら";
		mes "我々が遭遇した";
		mes "未確認生物のもののようなんだ。";
		next;
		mes "[レシア研究員]";
		mes "この考えを立証する必要がある。";
		mes "そこで、今回の君の仕事だ。";
		next;
		mes "[レシア研究員]";
		mes "温泉に行って、";
		mes "オッシーの^FF0000鱗^000000を";
		mes "^FF000010枚^000000ほど";
		mes "入手してきてくれたまえ。";
		mes "頼んだぞ。";
		set BIF_4QUE,7;
		chgquest 5020,5022;
		close;
	case 7:
		if(checkquest(5021)) {
			if(countitem(6387) < 10) {
				mes "[レシア研究員]";
				mes "君に頼んだ仕事は";
				mes "まだ終わらないのかい？";
				mes "オッシーの^FF0000歯^000000を";
				mes "^FF000010個^000000だよ。";
				mes "早く研究を進めたいんだ。";
				mes "急いでくれたまえ。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[レシア研究員]";
				mes "君、やたらと荷物が多いね。";
				mes "それじゃあ、いろいろと困るだろう。";
				mes "待っててあげるから";
				mes "荷物を整理しておいでよ。";
				close;
			}
			mes "[レシア研究員]";
			mes "確かに、オッシーの歯だね。";
			mes "ご苦労様。";
			next;
			mes "[レシア研究員]";
			mes "では、さっそく分析に入るよ。";
			mes "そうだな……";
			mes "^FF00006時間^000000ほどかかるから";
			mes "君は休憩していてくれたまえ。";
			delitem 6387,10;
			getitem 6380,1;
			chgquest 5021,5023;
			close;
		}
		if(checkquest(5022)) {
			if(countitem(6388) < 10) {
				mes "[レシア研究員]";
				mes "君に頼んだ仕事は";
				mes "まだ終わらないのかい？";
				mes "オッシーの^FF0000鱗^000000を";
				mes "^FF000010枚^000000だよ。";
				mes "早く研究を進めたいんだ。";
				mes "急いでくれたまえ。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[レシア研究員]";
				mes "君、やたらと荷物が多いね。";
				mes "それじゃあ、いろいろと困るだろう。";
				mes "待っててあげるから";
				mes "荷物を整理しておいでよ。";
				close;
			}
			mes "[レシア研究員]";
			mes "確かに、オッシーの鱗だね。";
			mes "ご苦労様。";
			next;
			mes "[レシア研究員]";
			mes "では、さっそく分析に入るよ。";
			mes "そうだな……";
			mes "^FF00006時間^000000ほどかかるから";
			mes "君は休憩していてくれたまえ。";
			delitem 6388,10;
			getitem 6380,1;
			chgquest 5022,5023;
			close;
		}
		if(checkquest(5023)) {
			if(!(checkquest(5023) & 2)) {
				mes "[レシア研究員]";
				mes "なんだ？";
				mes "まだ検査は終わっていないぞ。";
				mes "分析の結果というものは";
				mes "そんなすぐに出るものじゃないんだ。";
				mes "そうだな、6時間ほどかかる。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[レシア研究員]";
				mes "君、やたらと荷物が多いね。";
				mes "それじゃあ、いろいろと困るだろう。";
				mes "待っててあげるから";
				mes "荷物を整理しておいでよ。";
				close;
			}
			if(checkweight(1092,1) == 0) {
				mes "[レシア研究員]";
				mes "……といきたいが、荷物が多いね。";
				mes "それじゃあ、手伝いを頼めない。";
				mes "待っててあげるから";
				mes "荷物を整理しておいでよ。";
				close;
			}
			set '@rand,rand(5);
			if('@rand < 2) {
				chgquest 5023,5021;
				mes "[レシア研究員]";
				mes "これは……";
				mes "いや、君が持ってきたのは";
				mes "既に巷にあふれている生物のものだ。";
				emotion 19;
				next;
				mes "[レシア研究員]";
				mes "あの場所には多くの生物が";
				mes "集まるから無理もないが。";
				next;
				mes "[レシア研究員]";
				mes "悪いがもう一度行ってくれたまえ。";
				mes "オッシーの……そうだな。";
				mes "^FF0000歯^000000を^FF000010個^000000ほど";
				mes "集めてくるんだ。";
				mes "頼んだぞ。";
				close;
			} else if('@rand < 4) {
				chgquest 5023,5022;
				mes "[レシア研究員]";
				mes "これは……";
				mes "いや、君が持ってきたのは";
				mes "既に巷にあふれている生物のものだ。";
				emotion 19;
				next;
				mes "[レシア研究員]";
				mes "あの場所には多くの生物が";
				mes "集まるから無理もないが。";
				next;
				mes "[レシア研究員]";
				mes "悪いがもう一度行ってくれたまえ。";
				mes "オッシーの……そうだな。";
				mes "^FF0000鱗^000000を^FF000010枚^000000ほど";
				mes "集めてくるんだ。";
				mes "頼んだぞ。";
				close;
			} else {
				getitem 1092,1;
				set BIF_4QUE,8;
				chgquest 5023,5024;
				mes "[レシア研究員]";
				mes "よく来たね。";
				mes "ちょうど分析が終わったところだ。";
				mes "とりあえず、";
				mes "これを受け取ってくれ。";
				mes "後でこれを使って";
				mes "また仕事を頼むから。";
				next;
				mes "[レシア研究員]";
				mes "ではオッシーの分析結果を話すぞ。";
				mes "オッシーは";
				mes "一般的な魚から70％ほど変化した";
				mes "生き物のようだな。";
				next;
				mes "[レシア研究員]";
				mes "一体、この魚は";
				mes "どこから来て、";
				mes "どのくらいあそこにいるのか……";
				mes "温泉の温かい水の中で";
				mes "どうして生息できるのか……";
				mes "うん、気になるなあ。";
				next;
				mes "[レシア研究員]";
				mes "……";
				emotion 9;
				next;
				mes "[レシア研究員]";
				mes "これは、街のお年寄りから";
				mes "聞いた話なんだが、";
				mes "温泉の水源は、街周辺の水溜りに";
				mes "あるらしいんだ。";
				next;
				mes "[レシア研究員]";
				mes "では、君に仕事を頼もうか。";
				next;
				mes "[レシア研究員]";
				mes "街の2時方向……^FF0000東の水溜り^000000の";
				mes "水のサンプルを";
				mes "採取してきてくれたまえ。";
				mes "よろしく頼むよ。";
				close;
			}
		}
		close;
	case 8:
		if(countitem(6389) < 1) {
			mes "[レシア研究員]";
			mes "東の水溜りのサンプルは";
			mes "まだなのか？";
			mes "なるべく早く採取してくれたまえ。";
			mes "次もあるんだぞ。";
			close;
		}
		mes "[レシア研究員]";
		mes "東の水溜りのサンプルを";
		mes "持ってきてくれたんだね。";
		mes "ありがとう。";
		next;
		mes "[レシア研究員]";
		mes "では、次の仕事だ。";
		next;
		mes "[レシア研究員]";
		mes "街の7時方向……^FF0000西の水溜り^000000の";
		mes "水のサンプルを";
		mes "採取してきてくれたまえ。";
		next;
		mes "[レシア研究員]";
		mes "万が一にも破損には";
		mes "気をつけてくれよ。";
		mes "頼んだぞ。";
		if(checkweight(1092,1) == 0) {
			next;
			mes "[レシア研究員]";
			mes "……といきたいが、荷物が多いね。";
			mes "それじゃあ、手伝いを頼めない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		delitem 6389,1;
		getitem 1092,1;
		set BIF_4QUE,9;
		setquest 5025;
		delquest 5024;
		close;
	case 9:
		if(countitem(6389) < 1) {
			mes "[レシア研究員]";
			mes "西の水溜りのサンプルは";
			mes "まだなのか？";
			mes "なるべく早く採取してくれたまえ。";
			mes "次もあるんだぞ。";
			close;
		}
		mes "[レシア研究員]";
		mes "西の水溜りのサンプルを";
		mes "持ってきてくれたんだね。";
		mes "ありがとう。";
		next;
		mes "[レシア研究員]";
		mes "では、次の仕事だ。";
		next;
		mes "[レシア研究員]";
		mes "街の6時方向……^FF0000南の水溜り^000000の";
		mes "水のサンプルを";
		mes "採取してきてくれたまえ。";
		next;
		mes "[レシア研究員]";
		mes "万が一にも破損には";
		mes "気をつけてくれよ。";
		mes "頼んだぞ。";
		if(checkweight(1092,1) == 0) {
			next;
			mes "[レシア研究員]";
			mes "……といきたいが、荷物が多いね。";
			mes "それじゃあ、手伝いを頼めない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		delitem 6389,1;
		getitem 1092,1;
		set BIF_4QUE,10;
		setquest 5026;
		delquest 5025;
		close;
	case 10:
		if(countitem(6389) < 1) {
			mes "[レシア研究員]";
			mes "南の水溜りのサンプルは";
			mes "まだなのか？";
			mes "なるべく早く採取してくれたまえ。";
			mes "次もあるんだぞ。";
			close;
		}
		mes "[レシア研究員]";
		mes "南の水溜りのサンプルを";
		mes "持ってきてくれたんだね。";
		mes "ありがとう。";
		next;
		mes "[レシア研究員]";
		mes "では、次の仕事だ。";
		mes "これで最後だぞ。";
		next;
		mes "[レシア研究員]";
		mes "街の11時方向……^FF0000北の水溜り^000000の";
		mes "水のサンプルを";
		mes "採取してきてくれたまえ。";
		next;
		mes "[レシア研究員]";
		mes "万が一にも破損には";
		mes "気をつけてくれよ。";
		mes "頼んだぞ。";
		if(checkweight(1092,1) == 0) {
			next;
			mes "[レシア研究員]";
			mes "……といきたいが、荷物が多いね。";
			mes "それじゃあ、手伝いを頼めない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		delitem 6389,1;
		getitem 1092,1;
		set BIF_4QUE,11;
		setquest 5027;
		delquest 5026;
		close;
	case 11:
		if(countitem(6389) < 1) {
			mes "[レシア研究員]";
			mes "北の水溜りのサンプルは";
			mes "まだなのか？";
			mes "なるべく早く採取してくれたまえ。";
			mes "これが最後なんだ。";
			close;
		}
		mes "[レシア研究員]";
		mes "北の水溜りのサンプルを";
		mes "持ってきてくれたんだね。";
		next;
		mes "[レシア研究員]";
		mes "君が手伝ってくれたおかげで";
		mes "研究をまとめられそうだ。";
		mes "本当にありがとう。";
		next;
		mes "[レシア研究員]";
		mes "では、さっそく分析に入るよ。";
		mes "そうだな……";
		mes "^FF000012時間^000000ほどかかるんだが";
		mes "その後でまた君に";
		mes "渡したいものがあるんだ。";
		mes "また顔を出してくれたまえ。";
		if(checkitemblank() == 0) {
			next;
			mes "[レシア研究員]";
			mes "……おや、君、荷物が多いよ。";
			mes "それじゃあ、お礼を渡せない。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		delitem 6389,1;
		getitem 6380,4;
		set BIF_4QUE,12;
		chgquest 5027,5028;
		close;
	case 12:
		if(!(checkquest(5028) & 2)) {
			mes "[レシア研究員]";
			mes "なんだ？";
			mes "まだ研究は終わっていないぞ。";
			mes "そうだな……";
			mes "12時間ほど必要なんだ。";
			mes "そのあとに来てくれ。";
			close;
		}
		mes "[レシア研究員]";
		mes "おお、待っていたぞ！";
		mes "こちらも研究を終えられたところだ。";
		mes "どうだ？";
		mes "結果を見るか？";
		next;
		switch(select("研究結果を見ない","研究結果を見る")) {
		case 1:
			mes "[レシア研究員]";
			mes "……そうか、残念だが";
			mes "知識のない者では";
			mes "中身を見てもわからないもの";
			mes "なのだろうな。";
			next;
			mes "[レシア研究員]";
			mes "では、改めて";
			mes "手伝ってくれた礼をしようか。";
			break;
		case 2:
			mes "[レシア研究員]";
			mes "本当か！";
			mes "そうかそうか、では見てくれたまえ。";
			next;
			mes "[研究報告書]";
			mes "■研究員‐インフレ";
			mes "■助手‐";
			mes "　　　　　　"+ strcharinfo(0);
			mes "　";
			mes "<研究対象>";
			mes "■モーラの街　旅館温泉";
			next;
			mes "<研究目的>";
			mes "温泉水の効能を知り";
			mes "さらなる新しい活用の道を";
			mes "模索する。";
			mes "また調査の途中、遭遇した";
			mes "オッシーの正体を探る。";
			next;
			mes "<研究本文1/3>";
			mes "1.温泉水の分析";
			mes "　";
			mes "2.「1」で摘出された";
			mes "　オッシーの細胞分析";
			next;
			mes "<研究本文2/3>";
			mes "調査の結果、オッシーは";
			mes "ソードフィッシュから70％以上";
			mes "変化した生物の模様。";
			next;
			mes "<研究本文3/3>";
			mes "3.街外にある源泉水の分析";
			mes "街の東西南北にある4箇所の源泉が";
			mes "均一に混ざり合うことで";
			mes "研究対象である温泉の効能が";
			mes "現れていると結論。";
			next;
			mes "‐その後に、成分分析の結果が";
			mes "　書き連ねられている‐";
			next;
			mes "[レシア研究員]";
			mes "今回の研究で出した結論だけでは、";
			mes "説明しきれない何かが";
			mes "あの温泉にはある。";
			next;
			mes "[レシア研究員]";
			mes "オッシーと呼んでいた魚が";
			mes "生息していることもそうだが、";
			mes "この付近には火山もないし、";
			mes "また存在したという記録もないのに";
			mes "温泉がある……";
			mes "そのことも不思議だ。";
			next;
			mes "[レシア研究員]";
			mes "まだまだ研究は必要ということだな。";
			next;
			mes "[レシア研究員]";
			mes "……まあ、それはともかく";
			mes "改めて君にこれまでの";
			mes "礼をしないといけない。";
			mes "手を出したまえ。";
			break;
		}
		next;
		if(checkitemblank() == 0) {
			mes "[レシア研究員]";
			mes "君、やたらと荷物が多いね。";
			mes "それじゃあ、いろいろと困るだろう。";
			mes "待っててあげるから";
			mes "荷物を整理しておいでよ。";
			close;
		}
		chgquest 5028,201360;
		if(checkre()) {
			getexp 500000,250000;
			getexp 500000,250000;
		}
		else {
			getexp 5000000,2500000;
			getexp 5000000,2500000;
		}
		getitem 6380,30;
		set BIF_4QUE,13;
		setquest 71305;
		mes "[レシア研究員]";
		mes "研究を終わらせられたのは";
		mes "君が助手をしてくれたおかげだ。";
		mes "君はこれまでのどの助手より";
		mes "一番素晴らしいよ！";
		mes "最後まで助けてくれてありがとう。";
		next;
		mes "[レシア研究員]";
		mes "今度機会があればまた";
		mes "一緒に研究をしよう。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（研究は終わったけど、";
		mes "オッシーの正体が気になる……）";
		close;
	default:
		mes "[レシア研究員]";
		mes "ん、どうした？";
		mes "また研究を手伝ってくれるのか？";
		next;
		if(select("報告書を見る","あいさつに来た") == 2) {
			mes "[レシア研究員]";
			mes "ほう、挨拶に来てくれたのか。";
			mes "そうか。";
			next;
			mes "[レシア研究員]";
			mes "私はずいぶん、素晴らしい助手を";
			mes "手に入れたものだよ。";
			mes "また遊びに来たまえ。";
			mes "君ならいつでも歓迎しよう。";
			close;
		}
		mes "[レシア研究員]";
		mes "……";
		emotion 9;
		next;
		mes "[レシア研究員]";
		mes "そうか！";
		mes "そんなにも見たいと！";
		mes "私はうれしいぞ。";
		next;
		mes "[レシア研究員]";
		mes "さあ、ぜひ読んでくれ。";
		while(1) {
			next;
			mes "[研究報告書]";
			mes "■研究員‐インフレ";
			mes "■助手‐";
			mes "　　　　　　" +strcharinfo(0);
			mes "　";
			mes "<研究対象>";
			mes "■モーラの街　旅館温泉";
			next;
			mes "<研究目的>";
			mes "温泉水の効能を知り";
			mes "さらなる新しい活用の道を";
			mes "模索する。";
			mes "また調査の途中、遭遇した";
			mes "オッシーの正体を探る。";
			next;
			mes "<研究本文1/3>";
			mes "1.温泉水の分析";
			mes "　";
			mes "2.「1」で摘出された";
			mes "　オッシーの細胞分析";
			next;
			mes "<研究本文2/3>";
			mes "調査の結果、オッシーは";
			mes "ソードフィッシュから70％以上";
			mes "変化した生物の模様。";
			next;
			mes "<研究本文3/3>";
			mes "3.街外にある源泉水の分析";
			mes "街の東西南北にある4箇所の源泉が";
			mes "均一に混ざり合うことで";
			mes "研究対象である温泉の効能が";
			mes "現れていると結論。";
			next;
			mes "‐その後に、成分分析の結果が";
			mes "　書き連ねられている‐";
			next;
			mes "[レシア研究員]";
			mes "研究報告書はここまでだ、";
			mes "もう一度見るかい？";
			emotion 1;
			next;
			if(select("もう一度見る","もう見ない") == 2) {
				mes "[レシア研究員]";
				mes "研究結果を見たくなったら";
				mes "いつでも来たまえ。";
				mes "君が手伝ってくれた研究だ。";
				mes "遠慮はいらないからね。";
				close;
			}
			mes "[レシア研究員]";
			mes "ああ！";
			mes "何度でも見せてやるとも！";
			continue;
		}
	}
OnInit:
	waitingroom "温泉の研究",0;
	end;
}

mora.gat,114,79,0	script	黒い影#mora	844,{
	if(BaseLevel < 100) {
		mes "‐見たことのない形の影が";
		mes "　あなたをあざ笑い、";
		mes "　水中に姿を消した‐";
		next;
		mes "‐このクエストを進行するには";
		mes "　レベルが満たないようです。";
		mes "　^FF0000レベル100^000000になったら";
		mes "　再度挑戦してください‐";
		close;
	}
	if(checkquest(5029)) {
		if(!(checkquest(5029)&0x2)) {
			mes "‐見たことのない形の影が";
			mes "　捕まえる間もなく、";
			mes "　穴の中に逃げて行った‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（もう少し時間が経過したら";
			mes "また来よう）";
			close;
		}
		delquest 5029;
	}
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いです。";
		mes "　種類数を減らしてから";
		mes "　また調べてください‐";
		close;
	}
	switch(BIF_4QUE) {
	case 1:
	case 2:
	case 3:
		break;
	case 13:
		if(BIF_4QUE_SUB >= 30) {
			mes "[オッシー]";
			mes "うあぁぁぁ！";
			mes "もうやめて、やめて！";
			mes "おれ、コウゲキしない！";
			mes "コウサン!!";
			next;
			if(select("攻撃を続ける","手をおろす") == 1) {
				mes "‐オッシーは、泣き声をあげて";
				mes "　温泉の中を逃げ惑う‐";
				emotion 28;
				close;
			}
			mes "[オッシー]";
			mes "あ、アリガト。";
			mes "ごめんなさい。";
			mes "おれ、ハンセイ。";
			mes "ぜんぶはなす。";
			next;
			mes "[オッシー]";
			mes "……みんな、おれみて";
			mes "ヒメイあげてなぐってきた。";
			mes "カイブツいわれて";
			mes "こわくて、おれテイコウした。";
			next;
			mes "[オッシー]";
			mes "でも、テイコウばかりしても";
			mes "ダメ、わかった。";
			next;
			mes "[オッシー]";
			mes "おれ、コギ。";
			mes "おとうさん、つけたナマエ。";
			next;
			mes "[オッシー改めコギ]";
			mes "コギ、もうあばれない。";
			mes "これからは、なぐられてもにげる。";
			mes "だから、ハナシきいて。";
			mes "おれ、たすけて。";
			next;
			if(select("助けない","助ける") == 1) {
				mes "[コギ]";
				mes "おまえひどい！";
				mes "もうはなさない！";
				close;
			}
			mes "[コギ]";
			mes "おまえやさしい、やさしい！";
			next;
			mes "[コギ]";
			mes "おれ、ここすんでなかった。";
			mes "おれ、みずたまりすんでた。";
			mes "みずたまりすんでた！";
			next;
			mes "[コギ]";
			mes "おれ、ねくせワルイ。";
			mes "あるひ、おきた。";
			mes "ここでおきた。";
			next;
			mes "[コギ]";
			mes "かえるみち、わからない。";
			mes "おれ、ここにすんだ。";
			mes "カラダおおきくなった。";
			mes "あな、ちいさい。";
			mes "おれ、とおれない。";
			next;
			mes "[コギ]";
			mes "カゾクあいたい。あいたい。";
			mes "おまえ、カゾクつたえる。";
			mes "おれのこと、いう。";
			next;
			menu "家族はどこに？",-;
			set '@rand,rand(4);
			set BIF_4QUE,14+'@rand;
			set BIF_4QUE_SUB,0;
			setarray '@str$,"ヒガシ","ニシ","ミナミ","キタ";
			mes "[コギ]";
			mes "かぞく、" +'@str$['@rand]+ "。";
			mes '@str$['@rand]+ "のみずたまりすんでる。";
			mes "おれ、さかな。あたまワルイ。";
			mes "でも、かぞく、";
			mes "おれのナマエわかる。";
			next;
			mes "[コギ]";
			mes "つたえて。";
			mes "おれのこと。";
			setquest 5032;
			delquest 71305;
			close;
		}
		break;
	case 14:
	case 15:
	case 16:
	case 17:
		mes "[コギ]";
		mes "かぞくつたえた？";
		mes "おれ、ここにいる。";
		next;
		if(select("もう一度名前を教えて","伝えてくるよ") == 1) {
			mes "[コギ]";
			mes "おれ、コギ！";
			mes "あたまわるくても";
			mes "つけたおとうさん、わかる。";
			mes "つたえて。";
			mes "おれのこと。";
			close;
		}
		mes "[コギ]";
		mes "つたえて。";
		mes "おれのこと。";
		close;
	case 18:
	case 19:
	case 20:
	case 21:
		if(checkweight(5792,1) == 0) {
			// 未調査
			close;
		}
		mes "[コギ]";
		mes "かぞく、おれのことわかった？";
		next;
		menu "家族が迎えにくるって",-;
		mes "[コギ]";
		mes "ほんとうか！";
		mes "ありがと、ありがとう！";
		mes "おれ、おんわすれないサカナ。";
		mes "おれい、する！";
		delquest 5034;
		getitem 5792,1;
		set BIF_4QUE,22;
		setquest 201362;
		next;
		mes "[コギ]";
		mes "かんしゃかんしゃ！";
		mes "ありがとう！";
		close;
	case 22:
		mes "[コギ]";
		mes "おれ、もうあばれない。";
		mes "いじめられたら、にげる。";
		mes "かぞくのおむかえ、まつ！";
		close;
	default:
		mes "["+strcharinfo(0)+"]";
		mes "（今は用はない）";
		close;
	}
	mes "‐^FF0000オッシー^000000が現れた！";
	mes "　あなたに敵意を向けてきている‐";
	emotion 0,"";
	next;
	mes "【温泉バトル!!^000000】";
	mes "^FF0000" +strcharinfo(0)+ "^000000";
	mes "体力　100ポイント";
	mes "　　　　VS";
	mes "^0000FF温泉に現る未確認生命体";
	mes "オッシー^000000";
	mes "体力　100ポイント";
	musiceffect "130";
	next;
	mes "【オッシー撃破数】";
	mes "現在まで^FF0000" +BIF_4QUE_SUB+ "^000000回";
	mes "オッシーを撃破！";
	set '@p_hp,100;
	set '@n_hp,100;
	while(1) {
		next;
		set '@p_atk,select("素手で攻撃","物で攻撃","かむ","逃亡を図る");
		set '@p_atk2,rand(1,5);
		set '@n_def,rand(1,3);
		if('@p_atk == 4) {
			mes "‐あなたはその場から";
			mes "　逃亡を図った！‐";
			next;
			if(rand(100) < 60) {
				mes "‐オッシーは追ってこない。";
				mes "　あなたは逃亡に成功した‐";
				close2;
				musiceffect "139";
				end;
			}
			mes "‐しかし、オッシーに";
			mes "　まわりこまれてしまった‐";
			next;
			mes "‐オッシーの攻撃。";
			mes "　あなたに^FF000010^000000のダメージ！‐";
			set '@p_hp,'@p_hp-10;
		} else if(rand(100) < 25*'@p_atk) {
			switch('@p_atk) {
			case 1:
				mes "‐あなたは";
				mes "　オッシーを叩いた。";
				mes "　しかし、あなたの攻撃は";
				mes "　避けられてしまった‐";
				break;
			case 2:
				switch('@p_atk2) {
				case 1:
					mes "‐あなたは";
					mes "　^0000FF履いていたシューズ^000000を";
					break;
				case 2:
					mes "‐あなたは";
					mes "　^0000FF足元にあった石^000000を";
					break;
				case 3:
					mes "‐あなたは";
					mes "　^0000FF温泉に浮いていた木の枝^000000を";
					break;
				case 5:
					mes "‐あなたは";
					mes "　^0000FF近くに落ちていた木の棒^000000を";
					break;
				}
				mes "　使用し、オッシーを攻撃した。";
				mes "　しかし、あなたの攻撃は";
				mes "　避けられてしまった‐";
				break;
			case 3:
				mes "‐あなたはオッシーに";
				mes "　噛み付こうとしたが、";
				mes "　避けられてしまった‐";
				break;
			}
		} else {
			switch('@p_atk) {
			case 1:
				mes "‐あなたは";
				mes "　オッシーを叩いた。";
				mes "　オッシーに";
				mes "　^FF000010^000000の";
				mes "　ダメージを与えた‐";
				misceffect 0;
				set '@n_hp,'@n_hp-10;
				break;
			case 2:
				switch('@p_atk2) {
				case 1:
					if(rand(100) < 30) {
						mes "‐あなたは";
						mes "　^0000FF履いていたシューズ^000000の";
						mes "　使用に失敗した‐";
						break;
					}
					mes "‐あなたは";
					mes "　^0000FF履いていたシューズ^000000を";
					break;
				case 2:
					if(rand(100) < 30) {
						mes "‐あなたは";
						mes "　^0000FF足元にあった石^000000の";
						mes "　使用に失敗した‐";
						break;
					}
					misceffect 16;
					mes "‐あなたは";
					mes "　^0000FF足元にあった石^000000を";
					break;
				case 3:
					misceffect 16;
					mes "‐あなたは";
					mes "　^0000FF温泉に浮いていた木の枝^000000を";
					break;
				case 4:
					if(rand(100) < 30) {
						mes "‐あなたは";
						mes "　^0000FF足元に落ちてたヘアピン^000000の";
						mes "　使用に失敗した‐";
						break;
					}
					misceffect 16;
					mes "‐あなたは";
					mes "　^0000FF足元に落ちてたヘアピン^000000を";
					break;
				case 5:
					misceffect 16;
					mes "‐あなたは";
					mes "　^0000FF近くに落ちていた木の棒^000000を";
					break;
				}
				mes "　使用し、オッシーを攻撃した。";
				mes "　オッシーに";
				mes "　^FF000020^000000の";
				mes "　ダメージを与えた‐";
				set '@n_hp,'@n_hp-20;
				break;
			case 3:
				misceffect 0;
				mes "‐あなたはオッシーに";
				mes "　噛み付いた！";
				mes "　オッシーに";
				mes "　^FF000050^000000の";
				mes "　ダメージを与えた‐";
				set '@n_hp,'@n_hp-50;
				break;
			}
		}
		if('@n_hp <= 0 || '@p_hp <= 0)
			break;
		next;
		mes "[戦況]";
		mes "あなたの体力＝" +'@p_hp;
		mes "オッシーの体力＝" +'@n_hp;
		next;
		set '@attack,rand(3);
		switch('@attack) {
		case 0:
			mes "‐オッシーの攻撃！";
			mes "　オッシーの口から発射された";
			mes "　水鉄砲があなたを襲う‐";
			set '@damage,10;
			break;
		case 1:
			mes "‐オッシーの攻撃！";
			mes "　オッシーの頭突きが";
			mes "　あなたを襲う‐";
			set '@damage,20;
			break;
		case 2:
			mes "‐オッシーの攻撃！";
			mes "　オッシーの鋭い歯が";
			mes "　あなたを襲う‐";
			set '@damage,50;
			break;
		}
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（どうする!?）";
		next;
		switch(select("何もしない","避ける","防ぐ","逃亡を図る")) {
		case 1:
			switch('@attack) {
			case 0:
				misceffect 26,"";
				mes "‐オッシーの発射した水が";
				mes "　直撃した。";
				mes "　^FF000010^000000のダメージ‐";
				set '@p_hp,'@p_hp-10;
				break;
			case 1:
				misceffect 16,"";
				mes "‐オッシーの頭が";
				mes "　直撃した。";
				mes "　^FF000020^000000のダメージ‐";
				set '@p_hp,'@p_hp-20;
				break;
			case 2:
				misceffect 0,"";
				mes "‐オッシーの歯が";
				mes "　あなたの皮膚を貫いた。";
				mes "　^FF000050^000000のダメージ‐";
				set '@p_hp,'@p_hp-50;
				break;
			}
			break;
		case 2:
			if(rand(100) < 40) {
				switch('@attack) {
				case 0:
					misceffect 26,"";
					break;
				case 1:
					misceffect 16,"";
					break;
				case 2:
					misceffect 0,"";
					break;
				}
				mes "‐あなたは攻撃を避けることに";
				mes "　成功した‐";
			} else {
				switch('@attack) {
				case 0:
					misceffect 26,"";
					break;
				case 1:
					misceffect 16,"";
					break;
				case 2:
					misceffect 0,"";
					break;
				}
				mes "‐あなたは攻撃を避けることに";
				mes "　失敗した。";
				mes "　^FF0000" +'@damage+ "^000000のダメージ‐";
				set '@p_hp,'@p_hp-'@damage;
			}
			break;
		case 3:
			if(rand(100) < 40) {
				misceffect 336,"";
				mes "‐あなたは受けるダメージを";
				mes "　軽減することに成功。";
				set '@damage,'@damage/2;
			} else {
				misceffect 26,"";
				mes "‐あなたは攻撃を防ぎきれない！";
			}
			mes "　^FF0000" +'@damage+ "^000000のダメージを受けた‐";
			set '@p_hp,'@p_hp-'@damage;
			break;
		case 4:
			mes "‐あなたはその場から";
			mes "　逃亡を図った！‐";
			next;
			if(rand(100) < 60) {
				mes "‐オッシーは追ってこない。";
				mes "　あなたは逃亡に成功した‐";
				close2;
				musiceffect "139";
				end;
			}
			mes "‐しかし、オッシーに";
			mes "　まわりこまれてしまった‐";
			next;
			mes "‐オッシーの攻撃。";
			mes "　あなたに^FF000010^000000のダメージ！‐";
			set '@p_hp,'@p_hp-10;
			break;
		}
		if('@n_hp <= 0 || '@p_hp <= 0)
			break;
	}
	next;
	if('@p_hp < '@n_hp) {
		mes "‐あなたはオッシーとの";
		mes "　戦闘に敗北した‐";
		next;
		mes "‐気絶したあなたは何者かの手によって";
		mes "　温泉から追い出された‐";
		close2;
		musiceffect "139";
		warp "mora.gat",31,132;
		percentheal -99,0;
		end;
	}
	set BIF_4QUE_SUB,BIF_4QUE_SUB+1;
	mes "‐オッシーの体力が底をついた。";
	mes "　あなたは勝利した！‐";
	if(BIF_4QUE == 3) {
		next;
		mes "‐レシア研究員に頼まれた";
		mes "　こらしめを実行することにした‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（何をしよう……）";
		next;
		input '@str$;
		mes "‐あなたは";
		mes "　オッシーに";
		mes "　^0000FF" +'@str$+ "^000000した‐";
		next;
		set '@count,BIF_4QUE_SUB-1;
		if('@count<=1) {
			mes "‐オッシーは";
			mes "　まだこちらを威嚇してくる‐";
		} else if('@count<=2) {
			mes "‐オッシーは";
			mes "　および腰ながら";
			mes "　まだこちらを威嚇してくる‐";
		} else if('@count<=3) {
			mes "‐オッシーは";
			mes "　怯えた目でこちらに";
			mes "　腹を見せている‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（どうやら降参したみたいだ）";
			set BIF_4QUE,4;
			setquest 5029;
			setquest 5018;
			delquest 5017;
			close2;
			musiceffect "139";
			end;
		}
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（まだ降参する様子はないみたいだ）";
		setquest 5029;
		musiceffect "139";
		close;
	}
	if(BIF_4QUE == 13) {
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（どうしよう……）";
		next;
		if(select("オッシーの体を調べる","その場を離れる") == 1) {
			mes "‐直後、覚醒したオッシーが";
			mes "　一目散に逃げて行った‐";
		} else {
			mes "‐あなたは、オッシーを";
			mes "　そのままに";
			mes "　立ち去った‐";
		}
		musiceffect "139";
		close;
	}
	if(countitem(6385) < 1) {
		next;
		mes "‐オッシーは気絶している‐";
		next;
		menu "奪われた研究道具を探す",-;
		mes "‐オッシーが出現した穴の中で";
		mes "　^0000FF研究道具^000000を見つけた‐";
		getitem 6385,1;
		setquest 5029;
		next;
		mes "‐直後、覚醒したオッシーが";
		mes "　一目散に逃げて行った‐";
	}
	musiceffect "139";
	close;
}

mora.gat,108,86,0	script	源泉#mora1	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_4QUE == 7) {
		if(checkquest(5022)) {
			mes "‐水中で何かが光っている。";
			mes "　オッシーの鱗のようだ‐";
			next;
			if(select("調べる","何もしない") == 2) {
				mes "‐あなたはその場を離れた‐";
				close;
			}
			if(countitem(6388) >= 10) {
				mes "‐サンプルはもう十分だろう。";
				mes "　あなたはその場を離れた‐";
			}
			else if(rand(5) == 0) {
				mes "‐オッシーのものと推測できる";
				mes "　鱗を入手した‐";
				getitem 6388,1;
			}
			else {
				mes "‐光っているのは、水の反射だった‐";
			}
			close2;
			initnpctimer;
			end;
		}
		if(checkquest(5021)) {
			mes "‐水中で何かが光っている。";
			mes "　オッシーの歯のようだ‐";
			next;
			if(select("調べる","何もしない") == 2) {
				mes "‐あなたはその場を離れた‐";
				close;
			}
			if(countitem(6387) >= 10) {
				mes "‐サンプルはもう十分だろう。";
				mes "　あなたはその場を離れた‐";
				close;
			}
			if(rand(3) == 0) {
				mes "‐オッシーのものと推測できる";
				mes "　歯を入手した‐";
				getitem 6387,1;
			} else {
				mes "‐光っているのは、水の反射だった‐";
			}
			close2;
			initnpctimer;
			end;
		}
	}
	if(BIF_4QUE != 5) {
		mes "‐水面がきらきらと光っている‐";
		close;
	}
	mes "‐温泉の水のサンプルを";
	mes "　採取しますか？‐";
	next;
	if(select("サンプルを採取する","何もしない") == 2) {
		mes "‐あなたはその場を離れた‐";
		close;
	}
	if(countitem(6386) >= 10) {
		mes "‐これ以上、サンプルを";
		mes "　採取する必要はないだろう‐";
		close;
	}
	if(countitem(1092) < 1) {
		mes "‐サンプルを採取するには";
		mes "　^FF0000空の試験管^000000が1本必要です‐";
		close;
	}
	mes "‐あなたはサンプルを";
	mes "　採取することにした‐";
	if(rand(3) == 0) {
		delitem 1092,1;
		getitem 6386,1;
	} else {
		mes "‐サンプルの採取に失敗した‐";
	}
	close2;
	initnpctimer;
	end;
OnTimer1000:
	hideonnpc strnpcinfo(0);
	end;
OnTimer5000:
	stopnpctimer;
	hideoffnpc strnpcinfo(0);
	end;
}

mora.gat,107,82,0	duplicate(源泉#mora1)	源泉#mora2	844
mora.gat,113,84,0	duplicate(源泉#mora1)	源泉#mora3	844
mora.gat,116,81,0	duplicate(源泉#mora1)	源泉#mora4	844
mora.gat,118,86,0	duplicate(源泉#mora1)	源泉#mora5	844

bif_fild02.gat,315,285,0	script	水溜り#mora1	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_4QUE == 8) {
		mes "‐東の水溜りに到着した。";
		mes "　サンプルを採取しますか？‐";
		next;
		if(select("サンプルを採取する","何もしない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		if(countitem(6389) > 0) {
			mes "‐あなたはすでに";
			mes "　サンプルを採取している‐";
			close;
		}
		if(countitem(1092) < 1) {
			mes "‐サンプルを採取するには";
			mes "　^FF0000空の試験管^000000が1本必要です‐";
			close;
		}
		mes "‐東の水溜りのサンプルを採取した‐";
		delitem 1092,1;
		getitem 6389,1;
		close;
	}
	if(BIF_4QUE == 9) {
		mes "‐ここは西の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 10) {
		mes "‐ここは南の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 11) {
		mes "‐ここは北の水溜りではない‐";
		close;
	}
	if(BIF_4QUE >= 14 && BIF_4QUE <= 17) {
		mes "‐東の水溜りに到着した。";
		mes "　あなたはコギの家族を探した‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "お魚さん、お魚さん、";
		mes "いらっしゃいますか？";
		next;
		if(BIF_4QUE != 14) {
			mes "‐水面は動かない。";
			mes "　この水溜りには住んでいないようだ‐";
			close;
		}
		mes "‐あなたが呼びかけていると";
		mes "　水底から、声が聞こえてくる‐";
		next;
		mes "[？？？]";
		mes "だれ？";
		mes "釣り人？";
		next;
		menu "ある家族を探しています",-;
		mes "[？？？]";
		mes "家族？";
		mes "だれの家族？";
		next;
		input '@str$;
		if('@str$ != "コギ") {
			mes "[？？？]";
			mes "私の家族に";
			mes '@str$+ "はいない。";
			mes "お前、去る。";
			mes "私、去る。";
			next;
			mes "‐水面は再び静かになった‐";
			close;
		}
		mes "[？？？]";
		mes "コギ？";
		next;
		mes "[？？？]";
		mes "それ、息子！";
		mes "私の息子！";
		next;
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　次々に水面に現れた‐";
		next;
		mes "‐興奮した魚たちは";
		mes "　おのおのに騒ぎ立てている。";
		mes "　しばらくして、一匹の魚が";
		mes "　あなたに近づいていった‐";
		next;
		mes "[コギの父]";
		mes "お前、息子の無事";
		mes "しってる？";
		mes "息子、夜中、釣り人に";
		mes "つかまったか、思った。";
		next;
		mes "‐あなたは彼らに";
		mes "　これまでの事情を話した‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		set BIF_4QUE,18;
		delquest 5032;
		setquest 5034;
		close;
	}
	if(BIF_4QUE == 18) {
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　水面からあなたを見あげている‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		close;
	}
	mes "‐穏やかな水面が広がっている‐";
	close;
}

bif_fild02.gat,65,109,0	script	水溜り#mora2	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_4QUE == 8) {
		mes "‐ここは東の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 9) {
		mes "‐西の水溜りに到着した。";
		mes "　サンプルを採取しますか？‐";
		next;
		if(select("サンプルを採取する","何もしない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		if(countitem(6389) > 0) {
			mes "‐あなたはすでに";
			mes "　サンプルを採取している‐";
			close;
		}
		if(countitem(1092) < 1) {
			mes "‐サンプルを採取するには";
			mes "　^FF0000空の試験管^000000が1本必要です‐";
			close;
		}
		mes "‐西の水溜りのサンプルを採取した‐";
		delitem 1092,1;
		getitem 6389,1;
		close;
	}
	if(BIF_4QUE == 10) {
		mes "‐ここは南の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 11) {
		mes "‐ここは北の水溜りではない‐";
		close;
	}
	if(BIF_4QUE >= 14 && BIF_4QUE <= 17) {
		mes "‐西の水溜りに到着した。";
		mes "　あなたはコギの家族を探した‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "お魚さん、お魚さん、";
		mes "いらっしゃいますか？";
		next;
		if(BIF_4QUE != 15) {
			mes "‐水面は動かない。";
			mes "　この水溜りには住んでいないようだ‐";
			close;
		}
		mes "‐あなたが呼びかけていると";
		mes "　水底から、声が聞こえてくる‐";
		next;
		mes "[？？？]";
		mes "だれ？";
		mes "釣り人？";
		next;
		menu "ある家族を探しています",-;
		mes "[？？？]";
		mes "家族？";
		mes "だれの家族？";
		next;
		input '@str$;
		if('@str$ != "コギ") {
			mes "[？？？]";
			mes "私の家族に";
			mes '@str$+ "はいない。";
			mes "お前、去る。";
			mes "私、去る。";
			next;
			mes "‐水面は再び静かになった‐";
			close;
		}
		mes "[？？？]";
		mes "コギ？";
		next;
		mes "[？？？]";
		mes "それ、息子！";
		mes "私の息子！";
		next;
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　次々に水面に現れた‐";
		next;
		mes "‐興奮した魚たちは";
		mes "　おのおのに騒ぎ立てている。";
		mes "　しばらくして、一匹の魚が";
		mes "　あなたに近づいていった‐";
		next;
		mes "[コギの父]";
		mes "お前、息子の無事";
		mes "しってる？";
		mes "息子、夜中、釣り人に";
		mes "つかまったか、思った。";
		next;
		mes "‐あなたは彼らに";
		mes "　これまでの事情を話した‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		set BIF_4QUE,19;
		delquest 5032;
		setquest 5034;
		close;
	}
	if(BIF_4QUE == 19) {
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　水面からあなたを見あげている‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		close;
	}
	mes "‐穏やかな水面が広がっている‐";
	close;
}

bif_fild02.gat,223,71,0	script	水溜り#mora3	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_4QUE == 8) {
		mes "‐ここは東の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 9) {
		mes "‐ここは西の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 10) {
		mes "‐南の水溜りに到着した。";
		mes "　サンプルを採取しますか？‐";
		next;
		if(select("サンプルを採取する","何もしない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		if(countitem(6389) > 0) {
			mes "‐あなたはすでに";
			mes "　サンプルを採取している‐";
			close;
		}
		if(countitem(1092) < 1) {
			mes "‐サンプルを採取するには";
			mes "　^FF0000空の試験管^000000が1本必要です‐";
			close;
		}
		mes "‐南の水溜りのサンプルを採取した‐";
		delitem 1092,1;
		getitem 6389,1;
		close;
	}
	if(BIF_4QUE == 11) {
		mes "‐ここは北の水溜りではない‐";
		close;
	}
	if(BIF_4QUE >= 14 && BIF_4QUE <= 17) {
		mes "‐南の水溜りに到着した。";
		mes "　あなたはコギの家族を探した‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "お魚さん、お魚さん、";
		mes "いらっしゃいますか？";
		next;
		if(BIF_4QUE != 16) {
			mes "‐水面は動かない。";
			mes "　この水溜りには住んでいないようだ‐";
			close;
		}
		mes "‐あなたが呼びかけていると";
		mes "　水底から、声が聞こえてくる‐";
		next;
		mes "[？？？]";
		mes "だれ？";
		mes "釣り人？";
		next;
		menu "ある家族を探しています",-;
		mes "[？？？]";
		mes "家族？";
		mes "だれの家族？";
		next;
		input '@str$;
		if('@str$ != "コギ") {
			mes "[？？？]";
			mes "私の家族に";
			mes '@str$+ "はいない。";
			mes "お前、去る。";
			mes "私、去る。";
			next;
			mes "‐水面は再び静かになった‐";
			close;
		}
		mes "[？？？]";
		mes "コギ？";
		next;
		mes "[？？？]";
		mes "それ、息子！";
		mes "私の息子！";
		next;
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　次々に水面に現れた‐";
		next;
		mes "‐興奮した魚たちは";
		mes "　おのおのに騒ぎ立てている。";
		mes "　しばらくして、一匹の魚が";
		mes "　あなたに近づいていった‐";
		next;
		mes "[コギの父]";
		mes "お前、息子の無事";
		mes "しってる？";
		mes "息子、夜中、釣り人に";
		mes "つかまったか、思った。";
		next;
		mes "‐あなたは彼らに";
		mes "　これまでの事情を話した‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		set BIF_4QUE,20;
		delquest 5032;
		setquest 5034;
		close;
	}
	if(BIF_4QUE == 20) {
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　水面からあなたを見あげている‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		close;
	}
	mes "‐穏やかな水面が広がっている‐";
	close;
}

bif_fild02.gat,113,340,0	script	水溜り#mora4	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_4QUE == 8) {
		mes "‐ここは東の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 9) {
		mes "‐ここは西の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 10) {
		mes "‐ここは南の水溜りではない‐";
		close;
	}
	if(BIF_4QUE == 11) {
		mes "‐北の水溜りに到着した。";
		mes "　サンプルを採取しますか？‐";
		next;
		if(select("サンプルを採取する","何もしない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		if(countitem(6389) > 0) {
			mes "‐あなたはすでに";
			mes "　サンプルを採取している‐";
			close;
		}
		if(countitem(1092) < 1) {
			mes "‐サンプルを採取するには";
			mes "　^FF0000空の試験管^000000が1本必要です‐";
			close;
		}
		mes "‐北の水溜りのサンプルを採取した‐";
		delitem 1092,1;
		getitem 6389,1;
		close;
	}
	if(BIF_4QUE >= 14 && BIF_4QUE <= 17) {
		mes "‐北の水溜りに到着した。";
		mes "　あなたはコギの家族を探した‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "お魚さん、お魚さん、";
		mes "いらっしゃいますか？";
		next;
		if(BIF_4QUE != 17) {
			mes "‐水面は動かない。";
			mes "　この水溜りには住んでいないようだ‐";
			close;
		}
		mes "‐あなたが呼びかけていると";
		mes "　水底から、声が聞こえてくる‐";
		next;
		mes "[？？？]";
		mes "だれ？";
		mes "釣り人？";
		next;
		menu "ある家族を探しています",-;
		mes "[？？？]";
		mes "家族？";
		mes "だれの家族？";
		next;
		input '@str$;
		if('@str$ != "コギ") {
			mes "[？？？]";
			mes "私の家族に";
			mes '@str$+ "はいない。";
			mes "お前、去る。";
			mes "私、去る。";
			next;
			mes "‐水面は再び静かになった‐";
			close;
		}
		mes "[？？？]";
		mes "コギ？";
		next;
		mes "[？？？]";
		mes "それ、息子！";
		mes "私の息子！";
		next;
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　次々に水面に現れた‐";
		next;
		mes "‐興奮した魚たちは";
		mes "　おのおのに騒ぎ立てている。";
		mes "　しばらくして、一匹の魚が";
		mes "　あなたに近づいていった‐";
		next;
		mes "[コギの父]";
		mes "お前、息子の無事";
		mes "しってる？";
		mes "息子、夜中、釣り人に";
		mes "つかまったか、思った。";
		next;
		mes "‐あなたは彼らに";
		mes "　これまでの事情を話した‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		set BIF_4QUE,21;
		delquest 5032;
		setquest 5034;
		close;
	}
	if(BIF_4QUE == 21) {
		mes "‐温泉にいるコギとよく似た姿が";
		mes "　水面からあなたを見あげている‐";
		next;
		mes "[コギの母]";
		mes "コギ、生きてた。";
		mes "よかった、よかった。";
		next;
		mes "[コギの父]";
		mes "お前、おしえてくれた。";
		mes "ありがとう。感謝。";
		mes "息子、迎えに行く。";
		mes "お前、伝えて。";
		close;
	}
	mes "‐穏やかな水面が広がっている‐";
	close;
}

mora.gat,105,91,4	script	温泉の管理人#mora	522,{
	if(BIF_4QUE == 22) {
		mes "[温泉の管理人]";
		mes "コギ君から話は聞きましたよ。";
		mes "これでみんなが安心して入浴できます。";
		mes "本当にありがとうございました。";
		next;
		mes "[温泉の管理人]";
		mes "お礼にあなたに特別サービスを";
		mes "させていただきましょう。";
		next;
		switch(select("位置セーブを頼む","温泉に入る -> 4,000zeny","倉庫を使う -> 100zeny","今はいいです")) {
		case 1:
			mes "[温泉の管理人]";
			mes "はい、セーブしました。";
			mes "これで何かあっても安心ですよ。";
			savepoint "mora.gat",55,144;
			close;
		case 2:
			if(Zeny < 4000) {
				mes "[温泉の管理人]";
				mes "おや、料金が足らないようです。";
				close;
			}
			mes "[温泉の管理人]";
			mes "それでは、ごゆっくりどうぞ。";
			close2;
			set Zeny,Zeny-4000;
			warp "mora.gat",111,84;
			percentheal 100,100;
			end;
		case 3:
			if(Zeny < 100) {
				mes "[温泉の管理人]";
				mes "おや、料金が足らないようです。";
				close;
			}
			mes "[温泉の管理人]";
			mes "倉庫を開きます。";
			close2;
			set Zeny,Zeny-100;
			openstorage;
			end;
		case 4:
			mes "[温泉の管理人]";
			mes "そうですか。";
			mes "またお待ちしております。";
			close;
		}
	}
	mes "[温泉の管理人]";
	mes "モーラの温泉～、";
	mes "とってもいいユゥ～♪";
	mes "モーラを訪れたなら～";
	mes "せっかくだから、せっかくだから～";
	mes "一度は入ろうよぉ～♪";
	emotion 21;
	next;
	mes "[温泉の管理人]";
	mes "身も心もあったまる";
	mes "モーラの温泉へ入っていきませんか？";
	mes "疲れなんかふっとんでいきますよ。";
	mes "金額は5000zenyになります。";
	next;
	if(select("温泉に入る(HP/SP全回復)","入らない") == 2) {
		mes "[温泉の管理人]";
		mes "そうですか。";
		mes "温泉に入りたくなったら";
		mes "いつでも来てください。";
		close;
	}
	if(Zeny < 5000) {
		mes "[温泉の管理人]";
		mes "おや、料金が足らないようです。";
		close;
	}
	mes "[温泉の管理人]";
	mes "それでは、ごゆっくりどうぞ。";
	close2;
	set Zeny,Zeny-5000;
	warp "mora.gat",111,84;
	percentheal 100,100;
	end;
OnInit:
	waitingroom "温泉サービス",0;
	end;
}

//============================================================
// チェシャーの依頼クエスト
//- Registry -------------------------------------------------
// BIF_5QUE -> 0～4
//------------------------------------------------------------
dic_in01.gat,262,191,0	script	#ep14_1_xq02	139,3,3,{
	if(DIC_2QUE >= 23 && BIF_5QUE == 0) {
		donpcevent "チェシャー#ep14_1::OnStart";
		cutin "ep13_cheshire_h",1;
		mes "[チェシャー]";
		mes "おい、お前";
		mes "ちょっと待て！";
		mes "　";
		mes "‐アハトの執務室を出たあなたを";
		mes "　チェシャーが追いかけてきた‐";
		next;
		mes "[チェシャー]";
		mes "今日はもう一つ、";
		mes "お前に指示があったんだ。";
		next;
		mes "‐チェシャーは息を整えつつ、";
		mes "　近くにいる警備兵をちらっと見た後";
		mes "　あなたの耳元に顔を寄せる‐";
		next;
		mes "[チェシャー]";
		mes "^4d4dffカミダルトンネル^000000、";
		mes "^4d4dffスカラバホール入口の西^000000に";
		mes "猫の手の奴らが荷物をまとめてる";
		mes "場所がある。";
		next;
		mes "[チェシャー]";
		mes "そこには唯一、";
		mes "^4d4dffラベルの貼られた箱^000000があるはずだ。";
		next;
		mes "[チェシャー]";
		mes "お前は、今からそこに出向き";
		mes "その^4d4dffラベルの貼られた箱^000000を";
		mes "指示された場所に運べ。";
		next;
		mes "[チェシャー]";
		mes "わかってるだろうが、";
		mes "この仕事も内密に動くんだぞ。";
		mes "失敗するなよ！";
		mes "いいか、任せたからな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（スカラバホール入口の西にある";
		mes "^4d4dffラベルの貼られた箱^000000を";
		mes "運搬する仕事を任された）";
		set BIF_5QUE,1;
		setquest 7206;
		delquest 71196;
		hideonnpc "チェシャー#ep14_1";
		cutin "ep13_cheshire_h",255;
		close;
	}
	end;
}

dic_in01.gat,260,194,4	script	チェシャー#ep14_1	498,{
	end;
OnStart:
	initnpctimer;
	hideoffnpc "チェシャー#ep14_1";
	end;
OnTimer30000:
	stopnpctimer;
OnInit:
	hideonnpc "チェシャー#ep14_1";
	end;
}

dic_dun01.gat,274,114,0	script	積み上げられた箱	844,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　新しくアイテムを受け取ることが";
		mes "　できません。";
		mes "　アイテムを整理してください‐";
		close;
	}
	if((MaxWeight - Weight) < 100) {
		mes "‐所持アイテムの重量が重い為";
		mes "　新しくアイテムを受け取ることが";
		mes "　できません。";
		mes "　アイテムを整理してください‐";
		close;
	}
	switch(BIF_5QUE) {
	case 1:
		mes "‐箱が積み上げられている‐";
		next;
		mes "‐その中に、チェシャーの言っていた";
		mes "　ラベルの貼られた箱を発見した‐";
		next;
		mes "‐ラベルには";
		mes "　^FF0000「ビフロストの亀裂近くに運べ」^000000と";
		mes "　書かれている‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ビフロストの亀裂に箱を";
		mes "持って行こう）";
		set BIF_5QUE,2;
		chgquest 7206,7207;
		getitem 6392,1;
		close;
	case 2:
		mes "‐チェシャーの言っていた";
		mes "　箱のラベルには";
		mes "　^FF0000「ビフロストの亀裂近くに運べ」^000000と";
		mes "　書かれている‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ビフロストの亀裂に箱を";
		mes "持って行こう）";
		close;
	case 3:
		if(checkquest(7208) & 0x2) {
			mes "‐箱が積み上げられている‐";
			next;
			mes "‐その中に、チェシャーの言っていた";
			mes "　ラベルの貼られた箱を発見した‐";
			next;
			if(select("箱を運ぶ","何もしない") == 2) {
				mes "‐あなたは、";
				mes "　ラベルの貼られた箱をとらず、";
				mes "　その場を離れた‐";
				close;
			}
			mes "‐ラベルには";
			mes "　^FF0000ビフロストの亀裂近く^000000で";
			mes "　^FF0000チェシャー^000000に渡すように。と";
			mes "　書かれている‐";
			set BIF_5QUE,4;
			chgquest 7208,7210;
			getitem 6392,1;
			close;
		}
		mes "‐箱が積み上げられている‐";
		next;
		mes "‐しかし、チェシャーの言っていた";
		mes "　ラベルの貼られた箱は見当たらない。";
		mes "　まだ到着していないようだ‐";
		close;
	case 4:
		mes "‐ラベルには";
		mes "　^FF0000ビフロストの亀裂近く^000000で";
		mes "　^FF0000チェシャー^000000に渡すように。と";
		mes "　書かれている‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（ビフロストの亀裂に箱を";
		mes "持って行こう）";
		close;
	default:
		mes "‐箱が積み上げられている‐";
		close;
	}
}

bif_fild01.gat,335,168,3	script	チェシャー	497,{
	cutin "ep13_cheshire",1;
	if(DIC_2QUE < 16) {	//猫耳と尻尾の男クエスト
		cutin "ep13_cheshire",255;
		mes "‐男がイライラした";
		mes "　様子で立っている‐";
		next;
		menu "どうしたんですか？",-;
		cutin "ep13_cheshire",1;
		mes "[男]";
		mes "！";
		mes "お、お前には関係ないことだ。";
		mes "かまうな。あっちにいけよ！";
		next;
		mes "‐あなたは追い払われてしまった‐";
		close2;
		cutin "ep13_cheshire",255;
		end;
	}
	if(DIC_2QUE < 23) {	//猫耳と尻尾の男クエスト
		mes "[チェシャー]";
		mes "なんだ、お前";
		mes "こんなところまで来てるのか。";
		next;
		mes "[チェシャー]";
		mes "……別にいいけど、";
		mes "アハト様に泥を塗るような真似は";
		mes "するんじゃないぞ。";
		mes "そのことは絶対に";
		mes "忘れるなよな。";
		close2;
		cutin "ep13_cheshire",255;
		end;
	}
	if(checkquest(7209)) {
		if(countitem(6090) < 20) {
			mes "[チェシャー]";
			mes "持ってくるのは";
			mes "精製されたブラディウムを20個。";
			mes "お前がなくした箱の代わり!!";
			mes "こんどはちゃんとやってくれよ。";
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		mes "[チェシャー]";
		mes "……こんどはちゃんと持ってきたな。";
		mes "よし。";
		next;
		mes "‐チェシャーは";
		mes "　精製されたブラディウムを受け取ると";
		mes "　すべて、亀裂の中に投げ込んだ‐";
		next;
		mes "[チェシャー]";
		mes "いつもより、量が少ないけど";
		mes "……まあ、いいだろ。";
		mes "明日はちゃんと箱を";
		mes "持って来てくれよ。";
		mes "今日みたいになくしたりするな。";
		if(checkitemblank() == 0) {
			next;
			mes "[チェシャー]";
			mes "……荷物多いんだな、お前。";
			mes "荷物の種類数を減らしてよ。";
			mes "減らしたら";
			mes "また話しかけてくれ。";
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		delitem 6090,20;
		set BIF_5QUE,3;
		delquest 7209;
		setquest 7208;
		getitem 6304,1;
		close2;
		cutin "ep13_cheshire",255;
		end;
	}
	switch(BIF_5QUE) {
	case 0:
		mes "[チェシャー]";
		mes "あれ、お前";
		mes "こんなところまで来てるのか。";
		mes "　";
		mes "‐アハトの補佐官チェシャーにあった。";
		mes "　いつもは深く被っている頭巾はとれ、";
		mes "　猫の耳が晒されていた‐";
		next;
		menu "あれ、チェシャー？",-;
		mes "[チェシャー]";
		mes "な、なんだよ。";
		mes "オレがここにいて悪いことでもある？";
		next;
		menu "頭巾が……",-;
		mes "[チェシャー]";
		mes "ああ……";
		mes "これのことか。";
		mes "　";
		mes "‐チェシャーの言葉にあわせて";
		mes "　猫耳が動く‐";
		next;
		mes "[チェシャー]";
		mes "さすがにずっと頭巾で隠してるのは";
		mes "窮屈なんだよね。";
		mes "……ここはディエルじゃないし。";
		next;
		mes "[チェシャー]";
		mes "そうだ。ちょうどよかった。";
		mes "お前に仕事があるんだ。";
		mes "もちろん、";
		mes "アハト様のためのものだぞ。";
		mes "やるよな？";
		next;
		switch(select("はい","いいえ")) {
		case 1:
			mes "[チェシャー]";
			mes "うん。当然だよな。";
			mes "アハト様のためだもの。";
			break;
		case 2:
			mes "[チェシャー]";
			mes "……何、言ってんの？";
			mes "ここは拒否しちゃだめだろ。";
			mes "お前はアハト様に忠誠を";
			mes "誓ったんじゃないのか？";
			break;
		}
		next;
		mes "[チェシャー]";
		mes "^4d4dffカミダルトンネル^000000、";
		mes "^4d4dffスカラバホール入口の西^000000に";
		mes "猫の手の奴らが荷物をまとめてる";
		mes "場所がある。";
		next;
		mes "[チェシャー]";
		mes "そこには唯一、";
		mes "^4d4dffラベルの貼られた箱^000000があるはずだ。";
		next;
		mes "[チェシャー]";
		mes "お前は、今からそこに出向き";
		mes "その^4d4dffラベルの貼られた箱^000000を";
		mes "ここに持ってこい。";
		next;
		mes "[チェシャー]";
		mes "わかってるだろうが、";
		mes "この仕事も内密に動くんだぞ。";
		mes "失敗するなよ！";
		mes "いいか、任せたからな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（スカラバホール入口の西にある";
		mes "^4d4dffラベルの貼られた箱^000000を";
		mes "運搬する仕事を任された）";
		setquest 7206;
		delquest 71196;
		set BIF_5QUE,1;
		close2;
		cutin "ep13_cheshire",255;
		end;
	case 1:
		mes "[チェシャー]";
		mes "今からお前は、";
		mes "スカラバホール入口近くにある";
		mes "ラベルのついた箱を持って来るんだ。";
		mes "誰にも見つからないようにな。";
		mes "さあ、早く急げ！";
		close2;
		cutin "ep13_cheshire",255;
		end;
	case 2:
		if(countitem(6392) == 0) {
			mes "[チェシャー]";
			mes "やっと来たな。";
			mes "……ん、お前";
			mes "箱はどうした？";
			next;
			if(select("すぐ持ってきます","失くしました") == 1) {
				mes "[チェシャー]";
				mes "それなら、とっとと";
				mes "持ってこい！";
				mes "忘れたならもう一度";
				mes "説明してやる。";
				next;
				mes "[チェシャー]";
				mes "^4d4dffカミダルトンネル^000000、";
				mes "^4d4dffスカラバホール入口の西^000000に";
				mes "猫の手の奴らが荷物をまとめてる";
				mes "場所がある。";
				next;
				mes "[チェシャー]";
				mes "そこには唯一、";
				mes "^4d4dffラベルの貼られた箱^000000があるはずだ。";
				next;
				mes "[チェシャー]";
				mes "お前は、今からそこに出向き";
				mes "その^4d4dffラベルの貼られた箱^000000を";
				mes "ここに持ってこい。";
				next;
				mes "[チェシャー]";
				mes "わかってるだろうが、";
				mes "この仕事も内密に動くんだぞ。";
				mes "失敗するなよ！";
				mes "いいか、任せたからな。";
				close2;
				cutin "ep13_cheshire",255;
				end;
			}
			mes "[チェシャー]";
			mes "なくしただとぉ!?";
			mes "何をやってるんだ、お前は!!";
			next;
			mes "[チェシャー]";
			mes "信じらんねえ……";
			mes "このことはアハト様に";
			mes "報告するからな。";
			next;
			mes "[チェシャー]";
			mes "……とりあえず、";
			mes "お前は、箱の代わりに";
			mes "^4d4dff精製されたブラディウム^000000を^4d4dff20個^000000";
			mes "集めてこい。";
			next;
			mes "[チェシャー]";
			mes "こんどはちゃんとやってくれよ。";
			delquest 7210;
			setquest 7209;
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		mes "[チェシャー]";
		mes "持ってきたな、ご苦労さま。";
		mes "お前はなかなか有能で助かるよ。";
		mes "アハト様もお喜びになるぞ。";
		next;
		mes "[チェシャー]";
		mes "この箱は毎日、";
		mes "他の荷にまぎれて、";
		mes "カミダルトンネルに運ばれてくる。";
		next;
		mes "[チェシャー]";
		mes "時間になったら、";
		mes "ラベルのついた箱をそこから";
		mes "オレのところに持ってくるように。";
		mes "わかったな。";
		next;
		menu "チェシャーの仕事じゃないの？",-;
		mes "[チェシャー]";
		mes "なんだよ。";
		mes "お前、アハト様のために";
		mes "働きたくないの？";
		next;
		mes "[チェシャー]";
		mes "……確かに、これまでは";
		mes "オレの仕事だったけど";
		mes "オレはアハト様の補佐官なんだぞ。";
		next;
		mes "[チェシャー]";
		mes "ここはラフィネ族の領域。";
		mes "サファ族のアハト様の補佐官が";
		mes "うろちょろしていい場所じゃないだろ。";
		next;
		mes "[チェシャー]";
		mes "今までは、オレの耳と尻尾で";
		mes "うまくごまかせてたけど、";
		mes "これからもそうとは限らないし。";
		next;
		mes "[チェシャー]";
		mes "お前が一番、適役なんだよ。";
		next;
		mes "[チェシャー]";
		mes "もう質問はないな。";
		mes "それじゃあ、箱を渡して。";
		next;
		mes "‐あなたはチェシャーに";
		mes "　箱を渡した‐";
		next;
		mes "‐チェシャーは箱を開け、";
		mes "　中に入っていたものを取り出すと";
		mes "　すべて亀裂に投げ込む。";
		mes "　それは、";
		mes "　精製されたブラディウムだった‐";
		next;
		mes "[チェシャー]";
		mes "これで、よしっと。";
		mes "……お前は知らないだろ。";
		mes "あの亀裂の向こうには";
		mes "お前の知らない道が";
		mes "たくさんあるんだぞ。";
		next;
		mes "[チェシャー]";
		mes "はい、それじゃあ報酬な。";
		mes "受け取ったら、";
		mes "ラフィネ族に怪しまれないうちに";
		mes "ここを離れろ。";
		if(checkitemblank() == 0) {
			next;
			mes "[チェシャー]";
			mes "……荷物多いんだな、お前。";
			mes "荷物の種類数を減らしてよ。";
			mes "減らしたら";
			mes "また話しかけてくれ。";
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		delitem 6392,1;
		set BIF_5QUE,3;
		chgquest 7207,7208;
		getitem 6304,1;
		if(checkre())
			getexp 5000,4000;
		else
			getexp 50000,40000;
		close2;
		cutin "ep13_cheshire",255;
		end;
	case 3:
		if(checkquest(7208) & 0x2) {
			mes "[チェシャー]";
			mes "……そろそろ時間だな。";
			mes "ラベルのついた箱を取ってこい。";
			mes "回収場所はカミダルトンネルの";
			mes "スカラバホール入口近く。";
			mes "わかってるよな。";
			mes "誰にも見つからないように遂行しろよ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（スカラバホール入口の西にある";
			mes "^4d4dffラベルの貼られた箱^000000を";
			mes "運搬する仕事を任された）";
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		mes "[チェシャー]";
		mes "あの箱は毎日、";
		mes "他の荷にまぎれて、";
		mes "カミダルトンネルに運ばれてくる。";
		next;
		mes "[チェシャー]";
		mes "時間になったら、";
		mes "ラベルのついた箱をそこから";
		mes "オレのところに持ってくるんだぞ。";
		mes "それがこれから新しく";
		mes "お前に与えられた仕事だ。";
		mes "わかったな。";
		close2;
		cutin "ep13_cheshire",255;
		end;
	case 4:
		if(countitem(6392) == 0) {
			mes "[チェシャー]";
			mes "やっと来たな。";
			mes "……ん、お前";
			mes "箱はどうした？";
			next;
			if(select("すぐ持ってきます","失くしました") == 1) {
				mes "[チェシャー]";
				mes "それなら、とっとと";
				mes "持ってこい！";
				mes "忘れたならもう一度";
				mes "説明してやる。";
				next;
				mes "[チェシャー]";
				mes "^4d4dffカミダルトンネル^000000、";
				mes "^4d4dffスカラバホール入口の西^000000に";
				mes "猫の手の奴らが荷物をまとめてる";
				mes "場所がある。";
				next;
				mes "[チェシャー]";
				mes "そこには唯一、";
				mes "^4d4dffラベルの貼られた箱^000000があるはずだ。";
				next;
				mes "[チェシャー]";
				mes "お前は、今からそこに出向き";
				mes "その^4d4dffラベルの貼られた箱^000000を";
				mes "ここに持ってこい。";
				next;
				mes "[チェシャー]";
				mes "わかってるだろうが、";
				mes "この仕事も内密に動くんだぞ。";
				mes "失敗するなよ！";
				mes "いいか、任せたからな。";
				close2;
				cutin "ep13_cheshire",255;
				end;
			}
			mes "[チェシャー]";
			mes "なくしただとぉ!?";
			mes "何をやってるんだ、お前は!!";
			next;
			mes "[チェシャー]";
			mes "信じらんねえ……";
			mes "このことはアハト様に";
			mes "報告するからな。";
			next;
			mes "[チェシャー]";
			mes "……とりあえず、";
			mes "お前は、箱の代わりに";
			mes "^4d4dff精製されたブラディウム^000000を^4d4dff20個^000000";
			mes "集めてこい。";
			next;
			mes "[チェシャー]";
			mes "こんどはちゃんとやってくれよ。";
			delquest 7210;
			setquest 7209;
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		mes "[チェシャー]";
		mes "持ってきたな、ご苦労さま。";
		mes "明日も頼むぞ。";
		mes "わかったら、ラフィネ族のやつらに";
		mes "怪しまれないうちにここを離れるんだ。";
		if(checkitemblank() == 0) {
			next;
			mes "[チェシャー]";
			mes "……荷物多いんだな、お前。";
			mes "荷物の種類数を減らしてよ。";
			mes "減らしたら";
			mes "また話しかけてくれ。";
			close2;
			cutin "ep13_cheshire",255;
			end;
		}
		set BIF_5QUE,3;
		chgquest 7210,7208;
		delitem 6392,1;
		getitem 6304,1;
		if(checkre())
			getexp 5000,4000;
		else
			getexp 50000,40000;
		close2;
		cutin "ep13_cheshire",255;
		end;
	}
}

dicastes02.gat,125,192,0	script	#call_cheshir_ep14	139,3,3,{
	if(DIC_2QUE == 23 || DIC_2QUE == 24) {
		emotion 1,"";
		mes "‐あなたは不意に";
		mes "　展望台の下に誰かの気配を感じた‐";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（誰だろう？）";
		//setquest 71150;
		//compquest 71150;
		if(DIC_2QUE == 23)
			set DIC_2QUE,25;
		else
			set DIC_2QUE,26;
		donpcevent "チェシャー#cheshir_ep14::OnStart";
		close;
	} else if(DIC_2QUE >= 25) {
		emotion 1,"";
		donpcevent "チェシャー#cheshir_ep14::OnStart";
		end;
	}
	end;
}

dicastes02.gat,120,192,3	script	チェシャー#cheshir_ep14	497,{
	if(DIC_2QUE < 23) {
		mes "‐男がいる‐";
		close;
	}
	cutin "ep13_cheshire",1;
	mes "‐大臣アハトの補佐官、";
	mes "　チェシャーを見つけた‐";
	next;
	mes "[チェシャー]";
	mes "あれ？";
	mes "……驚いた。";
	mes "ここで会うなんてな。";
	next;
	switch(select("どうしてここに？","頭にあるのって……")) {
	case 1:
		mes "[チェシャー]";
		mes "アハト様と散策してたんだ。";
		mes "まあ、アハト様はお忙しいから";
		mes "すぐ戻られたけどね。";
		next;
		mes "[チェシャー]";
		mes "……";
		next;
		menu "……",-,"す、すごい木だよね",-;
		mes "[チェシャー]";
		mes "……知ってる？";
		mes "ここにある、真っ白で透明に光る木、";
		mes "みーんなサファ族の亡骸なんだ。";
		next;
		mes "[チェシャー]";
		mes "サファ族は体が石のように";
		mes "かたくなってく。";
		mes "最後には、この石の木になる。";
		next;
		mes "[チェシャー]";
		mes "今、オレたちがいる森は";
		mes "いわば墓場なのさ。";
		mes "よく見ると、足と腕があるのが";
		mes "わかるだろ？";
		next;
		mes "[チェシャー]";
		mes "……";
		next;
		mes "[チェシャー]";
		mes "ふふ……";
		mes "じゃあ、オレは帰るよ。";
		mes "アハト様の補佐をしなきゃな。";
		next;
		mes "‐チェシャーは頭巾を目深にかぶると";
		mes "　そのまま去って行った‐";
		break;
	case 2:
		mes "[チェシャー]";
		mes "うん？";
		mes "……ああ、しまった。";
		mes "この場所じゃ、頭巾を";
		mes "ぬいじゃまずかったな。";
		next;
		menu "報告書を盗んだ犯人？",-;
		mes "[チェシャー]";
		mes "な、何のことだ！";
		mes "報告書なんて、";
		mes "オレはそんなの知らない！";
		mes "変なことを言うな!!";
		next;
		mes "‐チェシャーは走り去ってしまった‐";
		break;
	}
	hideonnpc "チェシャー#cheshir_ep14";
	cutin "ep13_cheshire",255;
	close;
OnStart:
	initnpctimer;
	hideoffnpc "チェシャー#cheshir_ep14";
	end;
OnTimer600000:
	stopnpctimer;
OnInit:
	hideonnpc "チェシャー#cheshir_ep14";
	end;
}

//============================================================
// モーラ住人の依頼クエスト
//------------------------------------------------------------
mora.gat,108,98,4	script	ルルララ#mora	517,{
	mes "[ルルララ]";
	mes "人間の冒険者殿。";
	mes "あなたもよろしければ";
	mes "力を貸してください。";
	next;
	mes "[ルルララ]";
	mes "このモーラ村は";
	mes "冒険者や旅行者に憩いを";
	mes "提供しております。";
	next;
	mes "[ルルララ]";
	mes "そのため、多くの方々が";
	mes "このモーラを訪れてくれるように";
	mes "なりました。";
	next;
	mes "[ルルララ]";
	mes "しかし困ったことに";
	mes "訪れる者が多くなるにつれ";
	mes "モンスターに襲われる者、";
	mes "霧の森で迷ってしまう者なども";
	mes "増えてきました。";
	next;
	mes "[ルルララ]";
	mes "そんな中、この地を訪れた";
	mes "旅人たちがモーラを助けるために";
	mes "救援隊を組織してくれたのです。";
	mes "なんとありがたいことか……";
	next;
	mes "[ルルララ]";
	mes "よろしければ、";
	mes "レシア族を助けるために";
	mes "私の東側にいる救援隊の";
	mes "ゾウリン、ワンワォーン達に";
	mes "話しかけて依頼を";
	mes "受けてください。";
	next;
	mes "[ルルララ]";
	mes "さらに東側の方に";
	mes "魂の救済をしているという";
	mes "レシア族がいます。";
	mes "彼の話も聞いてくださると";
	mes "助かります。";
	if(BIF_2QUE < 99) {
		next;
		mes "[ルルララ]";
		mes "ただ困った事に、";
		mes "現在霧の森あたりで凶暴な竜が";
		mes "出現しているそうです。";
		mes "非常に危険な状態なので、";
		mes "警戒体制をとって、一時的に";
		mes "依頼をするのをやめているのです。";
		next;
		mes "[ルルララ]";
		mes "・・・・・・";
		mes "本当に困りました。";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	delquest 71194;
	close;
OnInit:
	waitingroom "モーラ各種依頼",0;
	end;
}

mora.gat,112,100,8	script	ゾウリン	509,{
	if(BaseLevel < 110) {
		mes "[ゾウリン]";
		mes "ここには、モーラの街の住民が";
		mes "日々のこまごまとした用件への";
		mes "助力を依頼してきます。";
		mes "それらを腕に覚えのある方に";
		mes "解決してもらっているのです。";
		next;
		mes "[ゾウリン]";
		mes "しかし、あなたではまだ荷が重そうだ。";
		mes "もう少し強くなられたその時に";
		mes "ご助力願います。";
		mes "　";
		mes "‐クエストを受けるには";
		mes "　^FF0000BaseLv110以上^000000必要です‐";
		close;
	}
	if(checkquest(12225)) {
		set '@quest,12225;
	} else if(checkquest(12226)) {
		set '@quest,12226;
	} else if(checkquest(12227)) {
		set '@quest,12227;
	} else if(checkquest(12228)) {
		set '@quest,12228;
	} else if(checkquest(12229)) {
		set '@quest,12229;
	}
	if(checkquest('@quest)) {
		if(checkquest('@quest) & 0x2) {
			mes "[ゾウリン]";
			mes "どうやら時間内に討伐を";
			mes "完了できなかったようですね。";
			mes "残念です。";
			mes "依頼は未達成とみなします。";
			next;
			mes "[ゾウリン]";
			mes "しかし、あなたにはまだまだ";
			mes "依頼をお願いしたいところ。";
			mes "また依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest '@quest;
			delquest 12230;
			close;
		}
		mes "[ゾウリン]";
		mes "モンスター討伐を";
		mes "よろしくお願いします。";
		mes "討伐が終わったら、";
		mes "私の横にいるハッチャに";
		mes "報告をお願いします。";
		close;
	}
	if(checkquest(12230)) {
		if(checkquest(12230) & 0x2) {
			mes "[ゾウリン]";
			mes "またあなたに";
			mes "依頼をお願いしたいです。";
			mes "依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest 12230;
			close;
		}
		mes "[ゾウリン]";
		mes "現在、あなたにお願いできる";
		mes "依頼はありません。";
		mes "時間が経過したら";
		mes "またお越しください。";
		close;
	}
	mes "[ゾウリン]";
	mes "ようこそ。";
	mes "あなたは冒険者ですね。";
	mes "モーラを脅かすモンスターを";
	mes "退治していただきたいのです。";
	mes "ぜひとも依頼を受けてください。";
	next;
	mes "[ゾウリン]";
	mes "なお、依頼は23時間に1回のみ";
	mes "うける事ができます。";
	next;
	mes "[ゾウリン]";
	mes "また、23時間以内に依頼を";
	mes "達成できない場合、もしくは";
	mes "モンスターを討伐しても";
	mes "報告しなかった場合は、";
	mes "未達成とみなして";
	mes "キャンセルとなります。";
	next;
	if(select("依頼を断る","依頼をうける") == 1) {
		mes "[ゾウリン]";
		mes "そうですか……";
		mes "残念です。";
		mes "気が変わったら";
		mes "また声をおかけください。";
		close;
	}
	mes "[ゾウリン]";
	mes "かしこまりました。";
	mes "こちらですな。";
	next;
	switch(rand(1,5)) {
	case 1:
		setquest 12225;
		setquest 12230;
		mes "[ゾウリン]";
		mes "この地域には果物を担いだ";
		mes "昆虫型モンスターが生息しています。";
		mes "そのモンスターは凶暴なため";
		mes "住民への被害があとを絶ちません。";
		next;
		mes "[ゾウリン]";
		mes "あなたにはその昆虫";
		mes "^FF0000ポムスパイダー^000000を^0000FF3体^000000";
		mes "駆除して欲しいのです。";
		mes "報告先はハッチャです。";
		mes "よろしくお願いいたします。";
		close;
	case 2:
		setquest 12226;
		setquest 12230;
		mes "[ゾウリン]";
		mes "最近、花に擬態して他の生物を";
		mes "襲撃する昆虫の被害が";
		mes "報告されています。";
		next;
		mes "[ゾウリン]";
		mes "^FF0000アングラマンティス^000000を^0000FF4体^000000";
		mes "駆除してください。";
		mes "報告先はハッチャです。";
		mes "よろしくお願いいたします。";
		close;
	case 3:
		setquest 12227;
		setquest 12230;
		mes "[ゾウリン]";
		mes "ビフロスト周辺で";
		mes "採集を行っていた冒険者が";
		mes "小さな鳥たちの襲撃を受けました。";
		next;
		mes "[ゾウリン]";
		mes "その冒険者からの依頼です。";
		mes "^FF0000パルス^000000^0000FF5体^000000の";
		mes "駆除をお願いします。";
		mes "報告先はハッチャです。";
		mes "よろしくお願いいたします。";
		close;
	case 4:
		setquest 12228;
		setquest 12230;
		mes "[ゾウリン]";
		mes "忌々しい妖精を退治してくれとの";
		mes "要請が入りました。";
		next;
		mes "[ゾウリン]";
		mes "^FF0000リトルファートゥム^000000を^0000FF6体^000000";
		mes "駆除してください。";
		mes "報告先はハッチャです。";
		mes "よろしくお願いいたします。";
		close;
	case 5:
		setquest 12229;
		setquest 12230;
		mes "[ゾウリン]";
		mes "金色の髪の束に見える";
		mes "モンスターが存在すると";
		mes "あなたは信じますか？";
		next;
		mes "[ゾウリン]";
		mes "^FF0000ミミン^000000を^0000FF7体^000000";
		mes "駆除してください。";
		mes "報告先はハッチャです。";
		mes "よろしくお願いいたします。";
		close;
	}
}

mora.gat,115,98,8	script	ハッチャ	509,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_2QUE < 99) {
		mes "[ハッチャ]";
		mes "あなたに仕事を依頼したいです。";
		mes "しかし、現在";
		mes "霧の森周辺で凶暴な竜が";
		mes "出現しているそうです。";
		mes "そのため、仕事の依頼を";
		mes "することはできないのです。";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(BaseLevel < 110) {
		mes "[ハッチャ]";
		mes "ここには、モーラの街の住民が";
		mes "日々のこまごまへの助力を";
		mes "依頼してきます。";
		mes "それらを腕に覚えのある方に";
		mes "解決してもらっているのです。";
		next;
		mes "[ハッチャ]";
		mes "しかし、あなたではまだ荷が重そうだ。";
		mes "もう少し強くなられたその時に";
		mes "ご助力願います。";
		mes "　";
		mes "‐クエストを受けるには";
		mes "　^FF0000BaseLv110以上^000000必要です‐";
		close;
	}
	if(checkquest(12225)) {
		set '@quest,12225;
	} else if(checkquest(12226)) {
		set '@quest,12226;
	} else if(checkquest(12227)) {
		set '@quest,12227;
	} else if(checkquest(12228)) {
		set '@quest,12228;
	} else if(checkquest(12229)) {
		set '@quest,12229;
	} else if(!checkquest(12230)) {
		mes "[ハッチャ]";
		mes "モンスター討伐の";
		mes "依頼を受けてくれるなら、";
		mes "横にいるゾウリンさんに";
		mes "話しかけてください。";
		close;
	}
	if(checkquest('@quest) & 0x2) {
		mes "[ハッチャ]";
		mes "時間内に討伐が";
		mes "完了できなかったようですね。";
		mes "申し訳ありませんが、";
		mes "依頼は未達成です。";
		mes "もう一度依頼を受けて頂けるなら";
		mes "ゾウリンに話しかけてください。";
		delquest '@quest;
		delquest 12230;
		close;
	}
	if(checkquest(12230) & 0x2) {
		mes "[ハッチャ]";
		mes "またあなたに";
		mes "モンスター討伐の依頼があります。";
		mes "受けて頂けるなら";
		mes "ゾウリンに話しかけてください。";
		delquest 12230;
		close;
	}
	mes "[ハッチャ]";
	mes "いらっしゃいませ。";
	mes "ご用件をお伺いします。";
	next;
	if(select("依頼を完了しました","なんでもありません") == 2) {
		mes "[ハッチャ]";
		mes "またのご利用を";
		mes "お待ちしております。";
		close;
	}
	mes "[ハッチャ]";
	mes "了解しました。";
	mes "少々お待ちください。";
	mes "依頼内容を確認いたします。";
	next;
	if(!'@quest) {
		mes "[ハッチャ]";
		mes "あの……";
		mes "あなたはこちらの依頼を";
		mes "受けていないようですよ。";
		close;
	}
	if(!(checkquest('@quest) & 0x4)) {
		mes "[ハッチャ]";
		mes "まだモンスターを";
		mes "討伐し終わっていないようですね。";
		mes "引き続き、討伐をお願いします。";
		close;
	}
	mes "[ハッチャ]";
	mes "依頼の完遂を確認しました。";
	mes "見事な働き、ありがとうございます。";
	mes "　";
	mes "またの助力をお待ちしております。";
	delquest '@quest;
	misceffect 18,"";
	if(BaseLevel < 100) {
		getexp 0,1*JobLevel*JobLevel;
	} else {
		getexp 0,5*JobLevel*JobLevel;
	}
	getitem 6380,3;
	close;
}

mora.gat,119,103,4	script	ワンワォーン	513,{
	if(BIF_2QUE < 99) {
		mes "[ワンワォーン]";
		mes "仕事を依頼したいのですが、";
		mes "霧の森周辺で紫の竜が現れた";
		mes "という情報が入っているのです。";
		mes "そのため、仕事の依頼を";
		mes "することはできないのです。";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(checkquest(12231)) {
		set '@quest,12231;
	} else if(checkquest(12232)) {
		set '@quest,12232;
	} else if(checkquest(12233)) {
		set '@quest,12233;
	} else if(checkquest(12234)) {
		set '@quest,12234;
	} else if(checkquest(12235)) {
		set '@quest,12235;
	}
	if(checkquest('@quest)) {
		if(checkquest('@quest) & 0x2) {
			mes "[ワンワォーン]";
			mes "どうやら時間内に材料を";
			mes "収集できなかったようですね。";
			mes "残念です。";
			mes "依頼は未達成とみなします。";
			next;
			mes "[ワンワォーン]";
			mes "しかし、あなたにはまだまだ";
			mes "依頼をお願いしたいところ。";
			mes "また依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest '@quest;
			delquest 12241;
			close;
		}
		mes "[ワンワォーン]";
		mes "依頼の件、";
		mes "よろしくお願いします。";
		mes "依頼を達成したら、";
		mes "私の横にいる雑貨業者に";
		mes "報告をお願いします。";
		close;
	}
	if(checkquest(12241)) {
		if(checkquest(12241) & 0x2) {
			mes "[ワンワォーン]";
			mes "またあなたに";
			mes "依頼をお願いしたいです。";
			mes "依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest 12241;
			close;
		}
		mes "[ワンワォーン]";
		mes "現在、あなたにお願いできる";
		mes "依頼はありません。";
		mes "時間が経過したら";
		mes "またお越しください。";
		close;
	}
	mes "[ワンワォーン]";
	mes "モーラでの生活に";
	mes "必要な物資を集めております。";
	mes "是非、依頼をうけてください。";
	next;
	mes "[ワンワォーン]";
	mes "なお、依頼は23時間に1回のみ";
	mes "うける事ができます。";
	mes "また、23時間以内に依頼を";
	mes "達成できない場合は未達成とみなして";
	mes "キャンセルとなります。";
	next;
	if(select("依頼を断る","依頼をうける") == 1) {
		mes "[ワンワォーン]";
		mes "残念です……";
		mes "気が変わったら";
		mes "また声をおかけください。";
		close;
	}
	mes "[ワンワォーン]";
	mes "はい。";
	mes "本日あなたにお願いするのは……";
	next;
	switch(rand(1,5)) {
	case 1:
		setquest 12231;
		setquest 12241;
		mes "[ワンワォーン]";
		mes "旅人に持たせる";
		mes "非常食料の防腐剤には";
		mes "虫の觸角がかかせません。";
		next;
		mes "[ワンワォーン]";
		mes "^FF0000虫の觸角^000000を^0000FF4本^000000";
		mes "持ってきてください。";
		mes "届け先は雑貨業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 2:
		setquest 12232;
		setquest 12241;
		mes "[ワンワォーン]";
		mes "最近、旅人の間で";
		mes "止まらない心臓を象徴した";
		mes "お守りが人気ということです。";
		next;
		mes "[ワンワォーン]";
		mes "^FF0000止まらない心臓^000000を^0000FF5個^000000";
		mes "持ってきてください。";
		mes "届け先は雑貨業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 3:
		setquest 12233;
		setquest 12241;
		mes "[ワンワォーン]";
		mes "街で備蓄している包帯を";
		mes "新しく補充することになりました。";
		mes "その材料を取ってきてください。";
		next;
		mes "[ワンワォーン]";
		mes "^FF0000くさった包帯^000000を^0000FF1本^000000";
		mes "持ってきてください。";
		mes "届け先は雑貨業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 4:
		setquest 12234;
		setquest 12241;
		mes "[ワンワォーン]";
		mes "強い戦士の証は、";
		mes "厳しい旅路を前にした者を";
		mes "勇気付けてくれることで";
		mes "お守りとして人気があります。";
		next;
		mes "[ワンワォーン]";
		mes "^FF0000オーク戦士の証^000000を^0000FF3つ^000000";
		mes "持ってきてください。";
		mes "届け先は雑貨業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 5:
		setquest 12235;
		setquest 12241;
		mes "[ワンワォーン]";
		mes "飲めば、スタミナがつくと人気の";
		mes "ドリンクがあります。";
		mes "その材料を集める依頼です。";
		next;
		mes "[ワンワォーン]";
		mes "^FF0000スケルボーン^000000を^0000FF3本^000000";
		mes "持ってきてください。";
		mes "届け先は雑貨業者です。";
		mes "よろしくお願いいたします。";
		close;
	}
}

mora.gat,116,105,4	script	雑貨業者	516,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_2QUE < 99) {
		mes "[雑貨業者]";
		mes "霧の森周辺で紫の竜が現れた";
		mes "という情報が入っています！";
		mes "これでは仕事ができません・・・・・・";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	mes "[雑貨業者]";
	mes "いらっしゃいませ。";
	mes "ご用件をお伺いします。";
	next;
	if(select("依頼を完了しました","なんでもありません") == 2) {
		mes "[雑貨業者]";
		mes "またのご利用を";
		mes "お待ちしております。";
		close;
	}
	mes "[雑貨業者]";
	mes "了解しました。";
	mes "少々お待ちください。";
	mes "依頼内容を確認いたします。";
	next;
	if(checkquest(12231)) {
		set '@quest,12231;
		set '@itemid,928;
		set '@num,4;
	} else if(checkquest(12232)) {
		set '@quest,12232;
		set '@itemid,929;
		set '@num,5;
	} else if(checkquest(12233)) {
		set '@quest,12233;
		set '@itemid,930;
		set '@num,1;
	} else if(checkquest(12234)) {
		set '@quest,12234;
		set '@itemid,931;
		set '@num,3;
	} else if(checkquest(12235)) {
		set '@quest,12235;
		set '@itemid,932;
		set '@num,3;
	} else {
		mes "[雑貨業者]";
		mes "あの……";
		mes "あなたはこちらの依頼を";
		mes "受けていないようですよ。";
		close;
	}
	if(countitem('@itemid) < '@num) {
		mes "[雑貨業者]";
		mes "おや、条件を満たしてませんよ。";
		mes "あなたはまだ依頼を";
		mes "達成していません。";
		close;
	}
	mes "[雑貨業者]";
	mes "依頼の完遂を確認しました。";
	mes "見事な働き、ありがとうございます。";
	mes "　";
	mes "またの助力をお待ちしております。";
	delitem '@itemid,'@num;
	delquest '@quest;
	misceffect 18,"";
	if(BaseLevel < 100) {
		getexp 0,1*JobLevel*JobLevel;
	} else {
		getexp 0,5*JobLevel*JobLevel;
	}
	getitem 6380,1;
	close;
}

mora.gat,109,93,4	script	キャングルル	514,{
	if(BIF_2QUE < 99) {
		mes "[キャングルル]";
		mes "霧の森あたりで危険な竜が";
		mes "出現したそうです。";
		mes "危険な状態なので";
		mes "今は仕事の依頼を中断しております。";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(checkquest(12236)) {
		set '@quest,12236;
	} else if(checkquest(12237)) {
		set '@quest,12237;
	} else if(checkquest(12238)) {
		set '@quest,12238;
	} else if(checkquest(12239)) {
		set '@quest,12239;
	} else if(checkquest(12240)) {
		set '@quest,12240;
	}
	if(checkquest('@quest)) {
		if(checkquest('@quest) & 0x2) {
			mes "[キャングルル]";
			mes "どうやら時間内に材料集めを";
			mes "完了できなかったようですね。";
			mes "残念です。";
			mes "依頼は未達成とみなします。";
			next;
			mes "[キャングルル]";
			mes "しかし、あなたにはまだまだ";
			mes "依頼をお願いしたいところ。";
			mes "また依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest '@quest;
			delquest 12242;
			close;
		}
		mes "[キャングルル]";
		mes "材料集めを";
		mes "よろしくお願いします。";
		mes "材料集めが終わったら、";
		mes "私の横にいる生活用品業者に";
		mes "報告をお願いします。";
		close;
	}
	if(checkquest(12242)) {
		if(checkquest(12242) & 0x2) {
			mes "[キャングルル]";
			mes "またあなたに";
			mes "依頼をお願いしたいです。";
			mes "依頼を受けてくれるならば、";
			mes "私に話しかけてください。";
			delquest 12242;
			close;
		}
		mes "[キャングルル]";
		mes "現在、あなたにお願いできる";
		mes "依頼はありません。";
		mes "時間が経過したら";
		mes "またお越しください。";
		close;
	}
	mes "[キャングルル]";
	mes "モーラを訪れる冒険者や旅行者";
	mes "のために、物資を集めています。";
	mes "依頼をうけてくれると嬉しいです。";
	next;
	mes "[キャングルル]";
	mes "なお、依頼は23時間に1回のみ";
	mes "うける事ができます。";
	mes "また、23時間以内に依頼を";
	mes "達成できない場合は未達成とみなして";
	mes "キャンセルとなります。";
	next;
	if(select("依頼を断る","依頼をうける") == 1) {
		mes "[キャングルル]";
		mes "残念です……";
		close;
	}
	mes "[キャングルル]";
	mes "はい。";
	mes "本日あなたにお願いするのは……";
	next;
	switch(rand(1,5)) {
	case 1:
		setquest 12236;
		setquest 12242;
		mes "[キャングルル]";
		mes "お守りをそのまま身につけるのも";
		mes "良いですが、ケースにいれて";
		mes "保管するのも良い方法ですね。";
		mes "それには死者の遺品が";
		mes "最適だそうですよ。";
		next;
		mes "[キャングルル]";
		mes "^FF0000死者の遺品^000000を^0000FF2個^000000";
		mes "持ってきてください。";
		mes "届け先は生活用品業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 2:
		setquest 12237;
		setquest 12242;
		mes "[キャングルル]";
		mes "こまごました備品を保管するのに";
		mes "かたい皮を使った入れ物は";
		mes "最適なんですよ。";
		mes "その業者からの依頼です。";
		next;
		mes "[キャングルル]";
		mes "^FF0000かたい皮^000000を^0000FF3枚^000000";
		mes "持ってきてください。";
		mes "届け先は生活用品業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 3:
		setquest 12238;
		setquest 12242;
		mes "[キャングルル]";
		mes "ひざを守るガードを作る材料が";
		mes "足らないそうです。";
		next;
		mes "[キャングルル]";
		mes "^FF0000鱗のかけら^000000を^0000FF3個^000000";
		mes "持ってきてください。";
		mes "届け先は生活用品業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 4:
		setquest 12239;
		setquest 12242;
		mes "[キャングルル]";
		mes "新作の毒虫対処薬の効果を";
		mes "実験するために";
		mes "毒成分があるものを";
		mes "集めてほしいとのことです。";
		next;
		mes "[キャングルル]";
		mes "^FF0000毒の牙^000000を^0000FF2個^000000";
		mes "持ってきてください。";
		mes "届け先は生活用品業者です。";
		mes "よろしくお願いいたします。";
		close;
	case 5:
		setquest 12240;
		setquest 12242;
		mes "[キャングルル]";
		mes "靴に使用する滑り止めを";
		mes "作る材料が足らないそうです。";
		next;
		mes "[キャングルル]";
		mes "^FF0000べとべとする液体^000000を^0000FF5個^000000";
		mes "持ってきてください。";
		mes "届け先は生活用品業者です。";
		mes "よろしくお願いいたします。";
		close;
	}
}

mora.gat,114,92,4	script	生活用品業者	518,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(BIF_2QUE < 99) {
		mes "[生活用品業者]";
		mes "霧の森あたりで危険な竜が";
		mes "出現したそうですよ。";
		mes "危険な状態なのですよ。";
		mes "だから、";
		mes "仕事の依頼を中断しております。";
		next;
		mes "‐クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	mes "[生活用品業者]";
	mes "いらっしゃいませ。";
	mes "ご用件をお伺いします。";
	next;
	if(select("依頼を完了しました","なんでもありません") == 2) {
		mes "[生活用品業者]";
		mes "またのご利用を";
		mes "お待ちしております。";
		close;
	}
	mes "[生活用品業者]";
	mes "了解しました。";
	mes "少々お待ちください。";
	mes "依頼内容を確認いたします。";
	next;
	if(checkquest(12236)) {
		set '@quest,12236;
		set '@itemid,934;
		set '@num,2;
	} else if(checkquest(12237)) {
		set '@quest,12237;
		set '@itemid,935;
		set '@num,3;
	} else if(checkquest(12238)) {
		set '@quest,12238;
		set '@itemid,936;
		set '@num,3;
	} else if(checkquest(12239)) {
		set '@quest,12239;
		set '@itemid,937;
		set '@num,2;
	} else if(checkquest(12240)) {
		set '@quest,12240;
		set '@itemid,938;
		set '@num,5;
	} else {
		mes "[生活用品業者]";
		mes "あの……";
		mes "あなたはこちらの依頼を";
		mes "受けていないようですよ。";
		close;
	}
	if(countitem('@itemid) < '@num) {
		mes "[生活用品業者]";
		mes "おや、条件を満たしてませんよ。";
		mes "あなたはまだ依頼を";
		mes "達成していません。";
		close;
	}
	mes "[生活用品業者]";
	mes "依頼の完遂を確認しました。";
	mes "見事な働き、ありがとうございます。";
	mes "　";
	mes "またの助力をお待ちしております。";
	delitem '@itemid,'@num;
	delquest '@quest;
	misceffect 18,"";
	if(BaseLevel < 100) {
		getexp 0,1*JobLevel*JobLevel;
	} else {
		getexp 0,5*JobLevel*JobLevel;
	}
	getitem 6380,1;
	close;
}

mora.gat,170,101,4	script	魂の引導者#mora	517,{
	if(BIF_2QUE < 99) {
		mes "[魂の引導者ニューリ]";
		mes "あなたはまだ霧の森で迷える竜を";
		mes "導いていないようだ。";
		mes "あれを導けるのはあなただけだ。";
		mes "もし、導くことができたら";
		mes "私の仕事を手伝ってほしい。";
		next;
		mes "‐魂の引導者から";
		mes "　クエストを受けるには";
		mes "　紫色の竜クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(checkquest(12253)) {
		if(checkquest(12243))
			set '@quest,12243;
		if(checkquest(12244))
			set '@quest,12244;
		if(checkquest(12245))
			set '@quest,12245;
		if(checkquest(12246))
			set '@quest,12246;
		if(checkquest(12247))
			set '@quest,12247;
		if(checkquest(12248))
			set '@quest,12248;
		if(checkquest(12249))
			set '@quest,12249;
		if(checkquest(12250))
			set '@quest,12250;
		if(checkquest(12251))
			set '@quest,12251;
		if(checkquest(12252))
			set '@quest,12252;
		if('@quest) {
			if(checkquest(12253) & 0x2) {
				mes "[魂の引導者ニューリ]";
				mes "・・・・・・時間が経過しすぎた。";
				mes "どうした、もう諦めるか？";
				next;
				if(select("諦めない","諦める") == 1) {
					mes "[魂の引導者ニューリ]";
					mes "そうか、では頼んだぞ。";
					close;
				}
				mes "[魂の引導者ニューリ]";
				mes "そうか、";
				mes "ではあなたへお願いしたことは";
				mes "とり下げよう。";
				mes "　";
				mes "‐クエストがキャンセルされました‐";
				delquest '@quest;
				delquest 12253;
				close;
			}
			mes "[魂の引導者ニューリ]";
			mes "頼んだぞ。";
			mes "霧の森の竜を導いたあなたなら";
			mes "この仕事はできるはずだ。";
			close;
		}
		if(!'@quest) {
			if(checkquest(12253) & 0x2) {
				mes "[魂の引導者ニューリ]";
				mes "迷える者の気配を感じる……";
				mes "またあなたに仕事を頼みたい。";
				mes "引き受けてくれるなら";
				mes "もう一度話しかけてくれ。";
				delquest 12253;
				close;
			}
			mes "[魂の引導者ニューリ]";
			mes "無事、迷える者を導いたな。";
			mes "礼をいうぞ。";
			mes "次の仕事だが、";
			mes "今はまだ導く時ではないようだ。";
			mes "時が来るまで待とう。";
			next;
			mes "‐前回の依頼を受けてから";
			mes "　23時間経過したら";
			mes "　また話しかけよう‐";
			close;
		}
	}
	mes "[魂の引導者ニューリ]";
	mes "竜を導いたものよ。";
	mes "あなたなら私の仕事ができる。";
	mes "このモーラの他の者から";
	mes "受けられる依頼とは違う性質の";
	mes "仕事だが頼まれてくれるかね？";
	next;
	switch(select("説明を聞く","依頼を受ける","断る")) {
	case 1:
		mes "[魂の引導者ニューリ]";
		mes "私の仕事は霧の森に";
		mes "取り残されたものを導くことだ。";
		mes "霧の森は迷いの森。";
		mes "繋がるはずだったものが";
		mes "迷いのために繋がらない。";
		mes "私はそれを導いているのだ。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "あなたは霧の森で";
		mes "私に頼まれた物を探し、";
		mes "触れるだけでいい。";
		mes "それであなたの仕事は完了だ。";
		next;
		if(select("断る","依頼を受ける") == 1) {
			mes "[魂の引導者ニューリ]";
			mes "そうか。";
			mes "だかあなたは必ず";
			mes "私の仕事を受けるだろう。";
			mes "また来るといい。";
			close;
		}
	case 2:
		break;
	case 3:
		mes "[魂の引導者ニューリ]";
		mes "そうか。";
		mes "だが、あなたは必ず";
		mes "私の仕事を受けるだろう。";
		mes "また来るといい。";
		close;
	}
	mes "[魂の引導者ニューリ]";
	mes "では……";
	mes "霧の森から届く魂の声を";
	mes "届けよう。";
	next;
	switch(rand(10)) {
	case 0:
		setquest 12243;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "過去にタザルという男が";
		mes "霧の森に、モーラの街中の花を";
		mes "植えたようだ。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "長い時間を経て、";
		mes "植えられた花は";
		mes "街への帰還を望んでいる。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標13x,10xに行き、";
		mes "花に触れてやってくれ。";
		break;
	case 1:
		setquest 12244;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "霧の森で力尽きた男がいる。";
		mes "母親への想いが";
		mes "その男の持っていたペンダントに";
		mes "宿り、悲しく音を刻んでいる。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標10x,24xに行き、";
		mes "ペンダントに";
		mes "触れてやってくれ。";
		break;
	case 2:
		setquest 12245;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "メシルという女が";
		mes "恋人との逢瀬に";
		mes "使用していた場所がある。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "別離のあと、残してきた指輪に";
		mes "悲しい思いがこもっているようだ。";
		mes "終わらせてやろう。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標14x,24xに行き、";
		mes "メシルの指輪を見つけてくれ。";
		break;
	case 3:
		setquest 12246;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "ヌワルイという男が";
		mes "長い戦士生活の終わりに";
		mes "霧の森に剣を残してきた。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "長い時間を経て、";
		mes "ヌワルイの剣は";
		mes "主への帰還を望んでいる。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標19x,27xに行き、";
		mes "剣を解放してくれ。";
		break;
	case 4:
		setquest 12247;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "パザマという男が";
		mes "己の夢を示すため";
		mes "霧の森に剣を残してきた。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "長い時間を経て、";
		mes "パザマの夢は叶ったようだ。";
		mes "剣は主への帰還を望んでいる。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標30x,32xに行き、";
		mes "剣を見つけてくれ。";
		break;
	case 5:
		setquest 12248;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "メンデルという女が";
		mes "過去、霧の森で";
		mes "薬物の研究をしていた。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "その際に植えられていた薬草が";
		mes "メンデルの命を救う唯一の薬。";
		mes "だがそれももう必要ない。";
		mes "せめて悲しみから";
		mes "解放してあげよう。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標33x,28xに行き、";
		mes "薬草を回収してくれたまえ。";
		break;
	case 6:
		setquest 12249;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "マイルビットという男が";
		mes "嘘をついたのは生涯ただ一度。";
		mes "その嘘は霧の森に掘った穴に";
		mes "閉じ込められている。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "男はすでに生涯を終えた。";
		mes "その嘘を開放してやろう。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標33x,17xに行き、";
		mes "マイルビットの嘘を";
		mes "回収してくれたまえ。";
		break;
	case 7:
		setquest 12250;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "クーンムンは幼い頃親をなくした。";
		mes "その親が残した遺産が";
		mes "霧の森にある。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "クーンムンは今、";
		mes "愛する者のために";
		mes "お金が必要だ。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標28x,8xに行き、";
		mes "クーンムンの親の遺産を";
		mes "見つけてくれ。";
		break;
	case 8:
		setquest 12251;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "チャイホキンは幾人もの女性と";
		mes "遊んで暮らした。";
		mes "しかし、心から愛した女はただ一人。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "チャイホキンよりも先に";
		mes "亡くなった女の魂は霧の森に";
		mes "迷い込んだ。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "チャイホキンも人生の終わりを";
		mes "迎えたようだ。";
		mes "二人を一緒にさせてやろう。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標17x,5xに行き、";
		mes "女の身につけていたものを";
		mes "見つけてくれ。";
		break;
	case 9:
		setquest 12252;
		setquest 12253;
		mes "[魂の引導者ニューリ]";
		mes "トゥーアルは霧の森で";
		mes "多くの友と子ども時代を過ごした。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "病に倒れた彼を、";
		mes "霧の森の友たちは心配している。";
		mes "その思いを代わりに届けてやろう。";
		next;
		mes "[魂の引導者ニューリ]";
		mes "霧の森座標11x,4xに行き、";
		mes "友の見舞い品を";
		mes "見つけてくれ。";
		break;
	}
	next;
	mes "[魂の引導者ニューリ]";
	mes "今あなたにまじないをかけよう。";
	next;
	misceffect 18,"";
	mes "[魂の引導者ニューリ]";
	mes "これであなたは";
	mes "迷える者を正しい方向に導ける。";
	mes "それでは頼むぞ。";
	close;
OnInit:
	waitingroom "霧の森捜索",0;
	end;
}

function	script	Mora_Remain	{
	if(checkitemblank() < 2) {
		mes "‐荷物の種類数が多いようだ。";
		mes "　種類数を減らしてから";
		mes "　もう一度調べよう‐";
		close;
	}
	if((MaxWeight - Weight) < 1000) {
		mes "‐荷物の重量が重すぎるようだ。";
		mes "　重量を減らしてから";
		mes "　もう一度調べよう‐";
		close;
	}
	if(checkquest(getarg(0))) {
		delquest getarg(0);
		if(getarg(3) > 0)
			getitem getarg(3),rand(getarg(4),getarg(5));
		mes "‐" +getarg(1)+ "を";
		mes "　手に取ると";
		mes "　一瞬光があたりを包み、";
		mes "　光の球体は空に向かって行った。";
		mes "　ふと、足元を見ると";
		mes "　何か落ちていた‐";
		misceffect 18,"";
		getitem 6380,getarg(2);
		close;
	}
	mes "‐特に変わったものはない‐";
	close;
}

1@mist.gat,132,100,0	script	タザルの痕跡		844,{ callfunc "Mora_Remain",12243,"タザルの花",6,526,1,3; }
1@mist.gat,102,242,0	script	ナイザの痕跡		844,{ callfunc "Mora_Remain",12244,"ナイザのペンダント",5,942,2,17; }
1@mist.gat,145,245,0	script	メシルの痕跡		844,{ callfunc "Mora_Remain",12245,"メシルの指輪",5,943,2,4; }
1@mist.gat,196,276,0	script	ヌワルイの痕跡		844,{ callfunc "Mora_Remain",12246,"ヌワルイの剣",6,549,1,3; }
1@mist.gat,304,327,0	script	パザマの痕跡		844,{ callfunc "Mora_Remain",12247,"パザマの剣",5,945,8,18; }
1@mist.gat,334,287,0	script	メンデルの痕跡		844,{ callfunc "Mora_Remain",12248,"メンデルの薬草",7,946,2,31; }
1@mist.gat,330,177,0	script	マイルビットの痕跡	844,{ callfunc "Mora_Remain",12249,"マイルビットの嘘",5,7008,6,17; }
1@mist.gat,284,84,0		script	クーンムンの痕跡	844,{ callfunc "Mora_Remain",12250,"クーンムンの親の遺産",4,0,0,0; }
1@mist.gat,170,54,0		script	チャイホキンの痕跡	844,{ callfunc "Mora_Remain",12251,"チャイホキンの想い人の遺品",2,929,1,5; }
1@mist.gat,118,43,0		script	トゥーアルの痕跡	844,{ callfunc "Mora_Remain",12252,"トゥーアルの友の見舞い品",3,0,0,0; }

mora.gat,131,165,7	script	モーラの街住民	520,{
	mes "[モーラの街住民]";
	mes "ここでは、冒険者が";
	mes "モーラの街でできる仕事を";
	mes "請けおうことができます。";
	next;
	mes "[モーラの街住民]";
	mes "人手はいくつあっても";
	mes "足りません。";
	mes "よかったら、助けてください。";
	close;
}

mora.gat,125,174,2	script	モーラの街住民	520,{
	mes "[モーラの街住民]";
	mes "ああ……";
	mes "私の出した依頼、";
	mes "無事に優秀な人の手に";
	mes "渡ったかなぁ……？";
	next;
	mes "[モーラの街住民]";
	mes "おかしな人が";
	mes "私の依頼を受けなきゃ";
	mes "いいんだけど……";
	close;
}

mora.gat,104,172,7	script	モーラの街住民	520,{
	mes "[モーラの街住民]";
	mes "モーラの街の住民は、";
	mes "困ったことがあったら";
	mes "すぐにここに依頼しに来るんだ。";
	next;
	mes "[モーラの街住民]";
	mes "そして、それを君のような";
	mes "旅人や冒険者が";
	mes "賃金目当てに助けてくれるってわけ。";
	mes "ははっ、需要と供給ってやつだね。";
	close;
}

//============================================================
// 地元騎士団クエスト
//------------------------------------------------------------
mora.gat,118,166,5	script	地元騎士団のボス	525,{
	mes "[地元騎士団のボス]";
	mes "我々は5分前に結成された";
	mes "伝説の地元騎士団である！";
	next;
	mes "[地元騎士団のボス]";
	mes "我々の目下の悩みは";
	mes "ボス、親分、団長に隊長と来て";
	mes "部下の兵卒がいないことだ。";
	next;
	mes "[地元騎士団のボス]";
	mes "……君、やってみない？";
	close;
}

mora.gat,116,165,5	script	地元騎士団の親分#mora	524,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(checkquest(1119)) {
		if(checkquest(1119) & 0x2) {
			mes "[地元騎士団の親分]";
			mes "モーラコインを手に入れたよ！";
			mes "だから、また君に不思議な種を";
			mes "集めて来てほしいんだ。";
			delquest 1119;
			close;
		}
		mes "[地元騎士団の親分]";
		mes "君に渡すモーラコインが";
		mes "なくなってしまったよ。";
		mes "これじゃあ、頼みごとはできないね。";
		mes "明日、また来てよ。";
		close;
	}
	if(checkquest(71250)) {
		if(countitem(12561) < 200) {
			mes "[地元騎士団の親分]";
			mes "霧の森にて";
			mes "^FF0000不思議な種^000000を";
			mes "200個集めてくるように！";
			mes "任せたぞ！";
			next;
			if(select("はい、親分！","嫌です、親分！") == 2) {
				mes "[地元騎士団の親分]";
				mes "なんとっ!!";
				close;
			}
			mes "[地元騎士団の親分]";
			mes "いい答えだ!!";
			mes "無事に帰ってきたら";
			mes "君に報酬を約束しよう！";
			close;
		}
		mes "[地元騎士団の親分]";
		mes "おお！";
		mes "それはまさしく";
		mes "^FF0000不思議な種^000000！";
		mes "しかも200個ある！";
		mes "それをよこすのだ！";
		mes "褒美にモーラコインをあげよう。";
		next;
		if(select("譲らない","譲る") == 1) {
			mes "[地元騎士団の親分]";
			mes "なんと！";
			mes "譲ってくれないのか！";
			mes "……";
			mes "反抗期か？";
			close;
		}
		mes "[地元騎士団の親分]";
		mes "うむ！";
		mes "約束どおり、褒美を渡そう。";
		mes "あ、地元騎士団の活動だと";
		mes "ちゃんと広告してくれたよな？";
		mes "頼むよ、兵卒。";
		chgquest 71250,1119;
		delitem 12561,200;
		getitem 6380,1;
		if(checkre())
			getexp 5000,4000;
		else
			getexp 50000,40000;
		close;
	}
	mes "[地元騎士団の親分]";
	mes "見知らぬ地！";
	mes "見知らぬ者たちとの出会いを恐れず";
	mes "やってきた君を見込んで";
	mes "地元騎士団の親分が仕事を与える！";
	next;
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[地元騎士団の親分]";
		mes "おや、君は正式にこの地には";
		mes "来ていないようだね。";
		mes "それでは仕事は与えられない！";
		next;
		mes "‐クエストを受けるには";
		mes "　異世界クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	mes "[地元騎士団の親分]";
	mes "霧の森にて";
	mes "^FF0000不思議な種^000000を";
	mes "200個集めてくるように！";
	next;
	if(select("はい、親分！","嫌です、親分！") == 2) {
		mes "[地元騎士団の親分]";
		mes "なんとっ!!";
		close;
	}
	mes "[地元騎士団の親分]";
	mes "いい答えだ!!";
	mes "無事に帰ってきたら";
	mes "君に報酬を約束しよう！";
	setquest 71250;
	delquest 71192;
	close;
OnInit:
	waitingroom "地元騎士団！",0;
	end;
}

mora.gat,114,163,5	script	地元騎士団の団長	522,{
	if(BIF_3QUE < 11) {
		mes "[地元騎士団の団長]";
		mes "霧の森でロペというラフィネ族が";
		mes "失踪したそうだよ！";
		mes "団長、地元騎士団の団長だから";
		mes "ぱぱっと解決するよ！";
		next;
		mes "[地元騎士団の団長]";
		mes "団長は、君に";
		mes "ロペの捜索を命じるよ！";
		mes "団長の代わりにがんばって。";
		mes "団長はこれからお掃除だよ！";
		next;
		mes "‐地元騎士団の団長から";
		mes "　クエストを受けるには";
		mes "　ロペ捜索クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(checkquest(201355)) {
		mes "[地元騎士団の団長]";
		mes "団長は騎士団活動に飽きてきたよ！";
		mes "団長だから、";
		mes "次はサーカス団にしようと思うよ。";
		mes "綱渡り、やってみる？";
		next;
		switch(select("他のものなら……","本当にサーカスを？")) {
		case 1:
			mes "[地元騎士団の団長]";
			mes "サーカス好き？";
			mes "団長は火のショーが好きだよ！";
			mes "飛び火こわいから";
			mes "やらないけどね！";
			close;
		case 2:
			mes "[地元騎士団の団長]";
			mes "……という、";
			mes "活動飽きてきたごっこだよ！";
			mes "だまされた？";
			mes "だまされた？";
			close;
		}
	}
	if(checkquest(1118)) {
		if(countitem(6383) < 30) {
			mes "[地元騎士団の団長]";
			mes "^FF0000ロペの手掛かり^000000はまだなの？";
			mes "団長は命じたよ！";
			mes "30枚持って来てって！";
			close;
		}
		mes "[地元騎士団の団長]";
		mes "まさしく^FF0000ロペの手掛かり^000000だね！";
		mes "それじゃあ、団長";
		mes "組み立てて、補修するよ！";
		next;
		mes "[地元騎士団の団長]";
		mes "くみくみ……";
		next;
		mes "[地元騎士団の団長]";
		mes "できたよ！";
		mes "団長、読んであげる！";
		next;
		mes "[ロペの手紙]";
		mes "……旅人……しゅうげき……";
		mes "偽装したまま……もうどく……";
		mes "まち……危険……";
		next;
		mes "[地元騎士団の団長]";
		mes "なぁに？";
		mes "なにこれ？";
		mes "団長、よくわからないよ！";
		mes "でも、持ってきてくれたから";
		mes "団長は兵卒に褒美をあげるよ！";
		chgquest 1118,201355;
		delitem 6383,30;
		getitem 6380,2;
		if(checkre())
			getexp 200000,100000;
		else
			getexp 2000000,1000000;
		close;
	}
	mes "[地元騎士団の団長]";
	mes "失踪したロペは";
	mes "結局間に合わなかったらしいね。";
	mes "団長、残念だよ！";
	next;
	mes "[地元騎士団の団長]";
	mes "ロペは駄目だったけど";
	mes "霧の森に散らばった";
	mes "^FF0000ロペの手掛かり^000000はまだ";
	mes "全部集まってないみたい。";
	next;
	mes "[地元騎士団の団長]";
	mes "団長は君に、それの回収を命じるよ！";
	mes "30枚くらい持ってきてよ！";
	next;
	if(select("いやです","はい、団長！") == 1) {
		mes "[地元騎士団の団長]";
		mes "だ、団長に";
		mes "さ、逆らう気……？";
		mes "団長に逆らうのはよくないもん。";
		close;
	}
	mes "[地元騎士団の団長]";
	mes "よろしくね。";
	mes "団長は命じたよ！";
	setquest 1118;
	delquest 71190;
	close;
}

mora.gat,112,161,5	script	地元騎士団の隊長	523,{
	mes "[地元騎士団の隊長]";
	mes "私は地元騎士団の隊長だ！";
	mes "どうした、事件か!?";
	mes "隊長の私に話してみなさい。";
	next;
	mes "[地元騎士団のボス]";
	mes "いや、相談事は";
	mes "地元騎士団のボスである私に";
	mes "話してくれないと困るぞ!!";
	mes "ボスが一番偉いんだから。";
	next;
	mes "[地元騎士団の隊長]";
	mes "何を言う！";
	mes "隊長が一番偉いんだ。";
	mes "ボスではなく、隊長に相談しなさい!!";
	mes "　";
	mes "‐ボスと隊長の間に火花が散る‐";
	emotion 19,"";
	close;
}

//============================================================
// モーラエンチャント関連NPC
//------------------------------------------------------------
function	script	MoraEnchants	{
	if(rand(100) < 10) {
		switch(rand(1,8)) {
		case 1: set getarg(0),4742; set getarg(1),4742; set getarg(2),4742; break;
		case 2: set getarg(0),4767; set getarg(1),4702; set getarg(2),4702; break;
		case 3: set getarg(0),4761; set getarg(1),4712; set getarg(2),4712; break;
		case 4: set getarg(0),4761; set getarg(1),4722; set getarg(2),4722; break;
		case 5: set getarg(0),4765; set getarg(1),4732; set getarg(2),4732; break;
		case 6: set getarg(0),4763; set getarg(1),4732; set getarg(2),4732; break;
		case 7: set getarg(0),4763; set getarg(1),4722; set getarg(2),4722; break;
		case 8: set getarg(0),4763; set getarg(1),4752; set getarg(2),4753; break;
		}
	} else {
		switch(rand(1,4)) {
		case 1: set getarg(0),4760; break;
		case 2: set getarg(0),4762; break;
		case 3: set getarg(0),4764; break;
		case 4: set getarg(0),4766; break;
		}
		if(rand(1,3) == 2) {
			set getarg(0),getarg(0) + 1;
		}
		switch(rand(1,3)) {
		case 1: set getarg(1),4710; break;
		case 2: set getarg(1),4720; break;
		case 3: set getarg(1),4750; break;
		}
		if(rand(1,3) == 2) {
			set getarg(1),getarg(1) + 1;
		}
		switch(rand(1,3)) {
		case 1: set getarg(2),4700; break;
		case 2: set getarg(2),4730; break;
		case 3: set getarg(2),4740; break;
		}
		if(rand(1,3) == 2) {
			set getarg(2),getarg(2) + 1;
		}
	}
	return;
}

mora.gat,105,176,4	script	モーラの服縫製家	509,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	mes "[モーラの服縫製家]";
	mes "私はモーラ街特産の衣服";
	mes "モーラの服を縫製している";
	mes "ケイと申します。";
	next;
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[モーラの服縫製家]";
		mes "……おや、";
		mes "あなたは正規にここに";
		mes "派遣された";
		mes "人間ではないようですね。";
		mes "残念ながらモーラの服に関わる";
		mes "サービスはできません。";
		next;
		mes "‐クエストを受けるには";
		mes "　異世界クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	mes "[モーラの服縫製家]";
	mes "よろしければ、私が製作した";
	mes "モーラの服を";
	mes "譲ってさしあげましょう。";
	mes "1着、モーラコイン1枚です。";
	next;
	mes "[モーラの服縫製家]";
	mes "さらに^FF0000モーラコイン5枚^000000と";
	mes "^FF0000モーラの服1着^000000";
	mes "持ってきてくだされば";
	mes "私の手でもっとすばらしく";
	mes "仕立ててさしあげますよ！";
	next;
	switch(select("モーラの服をください","^FF0000エンチャントの注意事項を聞く^000000","モーラの服をエンチャントしてください","今はいいです")) {
	case 1:
		mes "[モーラの服縫製家]";
		mes "モーラの服を";
		mes "譲ってさしあげましょう。";
		mes "1着、モーラコイン1枚です。";
		next;
		if(select("今回はやめときます","買います") == 1) {
			mes "[モーラの服縫製家]";
			mes "そうですか。";
			mes "モーラの服は";
			mes "持っていて損はありませんよ。";
			close;
		}
		if(countitem(6380) < 1) {
			mes "[モーラの服縫製家]";
			mes "おや。";
			mes "モーラコインを1枚も";
			mes "持っていないようですね。";
			mes "それではお譲りできません。";
			close;
		}
		delitem 6380,1;
		getitem 15024,1;
		mes "[モーラの服縫製家]";
		mes "さあ、どうぞ。";
		mes "ふかふかしているでしょう？";
		close;
	case 2:
		mes "[モーラの服縫製家]";
		mes "それでは";
		mes "エンチャントについて";
		mes "ご説明しましょう。";
		next;
		mes "[モーラの服縫製家]";
		mes "一般に流通しているモーラの服も";
		mes "なかなか素晴らしいですが、";
		mes "私の技術でエンチャントしますと";
		mes "3つのスロットに";
		mes "様々な効果が追加され";
		mes "すばらしいものになります。";
		next;
		mes "[モーラの服縫製家]";
		mes "^FF0000モーラコイン5枚^000000と";
		mes "^FF0000モーラの服1着^000000が";
		mes "あればエンチャントしてあげます。";
		mes "是非芸術作品を生み出しましょう！";
		mes "それはあなたの意思一つで";
		mes "決まりますよ。";
		next;
		mes "[モーラの服縫製家]";
		mes "なお、エンチャントする場合は";
		mes "モーラの服を一着だけ";
		mes "所持してください。";
		next;
		mes "[モーラの服縫製家]";
		mes "複数持っている場合、";
		mes "どのモーラの服に";
		mes "エンチャントするかわかりません。";
		mes "^FF0000必ずエンチャントしたい";
		mes "モーラの服だけ所持して";
		mes "エンチャントしてください^000000。";
		next;
		mes "[モーラの服縫製家]";
		mes "あと、精錬値がある場合";
		mes "精錬値はなくなります。";
		mes "既にエンチャントされている場合、";
		mes "効果は上書きされますので、";
		mes "その点ご注意ください。";
		next;
		mes "[モーラの服縫製家]";
		mes "そして、もう一つ。";
		mes "この私でもエンチャントに";
		mes "失敗してしまうことがあります。";
		mes "^FF0000失敗した時、そのモーラの服は";
		mes "なくなってしまいます^000000。";
		mes "その点、ご了承ください。";
		close;
	case 3:
		mes "[モーラの服縫製家]";
		mes "エンチャントですね。";
		mes "^FF0000モーラコイン5枚^000000と";
		mes "^FF0000モーラの服1着^000000が";
		mes "必要ですがよろしいですか？";
		next;
		mes "[モーラの服縫製家]";
		mes "モーラの服を2着以上お持ちだと";
		mes "どちらにエンチャントされるか";
		mes "わかりませんので";
		mes "必ず1着だけお持ちになるように";
		mes "してください。";
		next;
		if(select("やっぱり止める","エンチャントする") == 1) {
			mes "[モーラの服縫製家]";
			mes "わかりました。";
			mes "私の腕を見せたかったのですが";
			mes "仕方ありません。";
			close;
		}
		if(countitem(6380) < 5 || countitem(15024) < 1) {
			mes "[モーラの服縫製家]";
			mes "私の腕を見せたいのですが、";
			mes "残念ながら……";
			mes "^FF0000モーラコイン5枚^000000と";
			mes "^FF0000モーラの服1着^000000がなければ";
			mes "何もできませんよ。";
			close;
		}
		misceffect 101,"";
		delitem 6380,5;
		delitem 15024,1;
		set '@rand,rand(100);
		if('@rand < 5) {
			// 未調査
			getitem 15024,1;
			mes "[モーラの服縫製家]";
			mes "……あ。失敗しました。";
			next;
			mes "[ペンダント細工師]";
			mes "申し訳ありません。";
			mes "モーラの服に";
			mes "能力は宿りませんでした。";
			close;
		}
		else {
			callfunc "MoraEnchants",'@enchant_card1,'@enchant_card2,'@enchant_card3;
			getitem2 15024,1,1,0,0,0,'@enchant_card1,'@enchant_card2,'@enchant_card3;
			mes "[モーラの服縫製家]";
			mes "うん！";
			mes "上出来です。";
			mes "大事にしてくださいね。";
			close;
		}
	case 4:
		mes "[モーラの服縫製家]";
		mes "わかりました。";
		mes "私の腕を見せたかったのですが";
		mes "仕方ありません。";
		close;
	}
OnInit:
	waitingroom "モーラの服",0;
	end;
}

mora.gat,123,177,6	script	ペンダント細工師	509,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(countitem(2858) < 1) {
		mes "[ペンダント細工師]";
		mes "私はペンダントに";
		mes "はめ込まれている宝石を";
		mes "より美しく加工し、";
		mes "特別な力をつける技術を";
		mes "持っています。";
		next;
		if(ASH_1QUE < 100) {	//異世界クエスト未クリア
			mes "[ペンダント細工師]";
			mes "……おや、";
			mes "あなたは正規にここに";
			mes "派遣された";
			mes "人間ではないようですね。";
			mes "残念ながらサービスを";
			mes "することはできません。";
			next;
			mes "‐クエストを受けるには";
			mes "　異世界クエストをクリアする";
			mes "　必要があるようだ‐";
			close;
		}
		mes "[ペンダント細工師]";
		mes "しかし、全てのペンダントに";
		mes "それを行える訳ではありません。";
		mes "ごく一部の特殊なペンダントにしか";
		mes "行えません。";
		mes "ここ最近そのようなペンダントと";
		mes "出会っておりません。";
		next;
		mes "[ペンダント細工師]";
		mes "……";
		mes "^FF0000古大樹を守るという";
		mes "紫色の竜が持つペンダント。";
		mes "私はその伝説のペンダントを";
		mes "加工してみたいのです！^000000";
		close;
	}
	if(countitem(6380) < 5) {
		mes "[ペンダント細工師]";
		mes "守護者のペンダントを";
		mes "お持ちのようですね。";
		mes "モーラコイン5枚で";
		mes "加工してあげましょう。";
		next;
		mes "[ペンダント細工師]";
		mes "……しかし";
		mes "あなたはコインをお持ちで";
		mes "ないようですね。";
		close;
	}
	mes "[ペンダント細工師]";
	mes "あなたは素晴らしいペンダントを";
	mes "持っていますね。";
	mes "守護者のペンダント、";
	mes "それは本当に素晴らしい物です。";
	next;
	mes "[ペンダント細工師]";
	mes "私はペンダントに";
	mes "はめ込まれている宝石を";
	mes "より美しく加工し、";
	mes "特別な力をつける技術を";
	mes "持っています。";
	next;
	mes "[ペンダント細工師]";
	mes "エンチャントを行いますか？";
	next;
	if(select("^FF0000注意事項を聞く^000000","エンチャントする") == 1) {
		mes "[ペンダント細工師]";
		mes "守護者のペンダントを";
		mes "私の技術でより美しく";
		mes "エンチャントしますと";
		mes "3つのスロットに";
		mes "様々な効果が追加され";
		mes "すばらしいものになります。";
		next;
		mes "[ペンダント細工師]";
		mes "ただし、";
		mes "すでにエンチャントをしている場合、";
		mes "さらにエンチャントすると、";
		mes "以前の効果は消えて、";
		mes "新しい効果に上書きされます。";
		next;
		mes "[ペンダント細工師]";
		mes "必要な物としては";
		mes "^FF0000モーラコイン5枚^000000と";
		mes "^FF0000守護者のペンダント1個^000000が";
		mes "あればエンチャントできます。";
		next;
		mes "[ペンダント細工師]";
		mes "なお、エンチャントする場合は";
		mes "守護者のペンダントを一つだけ";
		mes "所持してください。";
		next;
		mes "[ペンダント細工師]";
		mes "複数持っている場合、";
		mes "どの守護者のペンダントに";
		mes "エンチャントするかわかりません。";
		mes "^FF0000必ずエンチャントしたい";
		mes "守護者のペンダントだけ所持して";
		mes "エンチャントしてください^000000。";
		next;
		mes "[ペンダント細工師]";
		mes "なお、エンチャントが失敗して";
		mes "守護者のペンダントが";
		mes "壊れることはないので";
		mes "ご安心ください。";
		mes "ただ、何の効果もつかないことは";
		mes "ありますが……";
		close;
	}
	mes "[ペンダント細工師]";
	mes "エンチャントですね。";
	mes "^FF0000モーラコイン5枚^000000が";
	mes "必要ですがよろしいですか？";
	next;
	if(select("エンチャントを止める","エンチャントする") == 1) {
		mes "[ペンダント細工師]";
		mes "わかりました。";
		mes "私の腕を見せたかったのですが";
		mes "仕方ありません。";
		close;
	}
	misceffect 101,"";
	delitem 6380,5;
	delitem 2858,1;
	set '@rand,rand(100);
	if('@rand < 5) {
		getitem 2858,1;
		mes "[ペンダント細工師]";
		mes "……あ。失敗しました。";
		next;
		mes "[ペンダント細工師]";
		mes "申し訳ありません。";
		mes "守護者のペンダントに";
		mes "能力は宿りませんでした。";
		close;
	}
	else {
		callfunc "MoraEnchants",'@enchant_card1,'@enchant_card2,'@enchant_card3;
		getitem2 2858,1,1,0,0,0,'@enchant_card1,'@enchant_card2,'@enchant_card3;
		mes "[ペンダント細工師]";
		mes "うん！";
		mes "上出来です。";
		mes "大事にしてくださいね。";
		close;
	}
OnInit:
	waitingroom "守護者のペンダント",0;
	end;
}

mora.gat,134,166,4	script	バルバリウェストフード	509,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　報酬を受け取ることができません。";
		mes "　アイテムを整理してから、";
		mes "　再度報告してください‐";
		close;
	}
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[バルバリウェストフード]";
		mes "私、フードとマフラーを扱う";
		mes "バルバリウェストフードと申します。";
		next;
		mes "[バルバリウェストフード]";
		mes "……おや、";
		mes "あなたは正規にここに";
		mes "派遣された";
		mes "人間ではないようですね。";
		mes "残念ながらサービスを";
		mes "することはできません。";
		next;
		mes "‐クエストを受けるには";
		mes "　異世界クエストをクリアする";
		mes "　必要があるようだ‐";
		close;
	}
	if(countitem(2568) < 1) {
		mes "[バルバリウェストフード]";
		mes "私、フードとマフラーを扱う";
		mes "バルバリウェストフードと申します。";
		next;
		mes "[バルバリウェストフード]";
		mes "さきほどあなたの種族の青年が";
		mes "とても素敵なマフラーを";
		mes "して歩いていました。";
		mes "^FF0000鋭い目つきの青年^000000でした。";
		next;
		mes "[バルバリウェストフード]";
		mes "ああ、あのマフラーを";
		mes "私の手でより素敵にしたい！";
		mes "もしあのマフラーを";
		mes "持ってきてくれたら";
		mes "モーラコイン5枚で";
		mes "さらに素敵に仕立ててあげますよ。";
		close;
	}
	if(countitem(6380) < 5) {
		mes "[バルバリウェストフード]";
		mes "私、フードとマフラーを扱う";
		mes "バルバリウェストフードと申します。";
		next;
		mes "[バルバリウェストフード]";
		mes "おや、あなたのそのお持ちのマフラーは";
		mes "あの鋭い目つきの青年のマフラー";
		mes "ではありませんか。";
		next;
		mes "[バルバリウェストフード]";
		mes "そのマフラーは";
		mes "ロキのマフラーというのですね。";
		mes "そのマフラーをモーラコイン5枚で";
		mes "さらに素敵に仕立ててあげますよ。";
		next;
		mes "[バルバリウェストフード]";
		mes "おや、";
		mes "モーラコイン5枚を";
		mes "持っていないようですね。";
		mes "もしモーラコインを";
		mes "手に入れたらまた来てください。";
		close;
	}
	mes "[バルバリウェストフード]";
	mes "ブランドフードのプライドを守る";
	mes "バルバリウェストフードと申します。";
	next;
	mes "[バルバリウェストフード]";
	mes "あなたのそのお持ちのマフラーは";
	mes "あの鋭い目つきの青年のマフラー、";
	mes "ロキのマフラー";
	mes "ではありませんか。";
	next;
	mes "[バルバリウェストフード]";
	mes "そのロキのマフラーを";
	mes "^FF0000モーラコイン5枚^000000で";
	mes "さらに素敵なマフラーに";
	mes "エンチャントしますが";
	mes "いかがなさいますか？";
	next;
	if(select("^FF0000注意事項を聞く^000000","エンチャントする") == 1) {
		mes "[バルバリウェストフード]";
		mes "ロキのマフラーを";
		mes "私が仕立ててエンチャントしますと";
		mes "3つのスロットに";
		mes "様々な効果が追加され";
		mes "さらに素敵なマフラーになります。";
		next;
		mes "[バルバリウェストフード]";
		mes "^FF0000モーラコイン5枚^000000と";
		mes "^FF0000ロキのマフラー1つ^000000が";
		mes "あればエンチャントしてあげます。";
		next;
		mes "[バルバリウェストフード]";
		mes "なお、エンチャントする場合は";
		mes "ロキのマフラーを1つだけ";
		mes "所持してください。";
		next;
		mes "[バルバリウェストフード]";
		mes "複数持っている場合、";
		mes "どのロキのマフラーを仕立てて";
		mes "エンチャントするかわかりません。";
		mes "^FF0000必ずエンチャントしたい";
		mes "ロキのマフラーだけ所持して";
		mes "エンチャントしてください^000000。";
		next;
		mes "[バルバリウェストフード]";
		mes "なお、エンチャントが失敗して";
		mes "ロキのマフラーが";
		mes "壊れることはないので";
		mes "ご安心ください。";
		mes "ただ、何の効果もつかないことは";
		mes "ありますのでご了承ください。";
		close;
	}
	mes "[バルバリウェストフード]";
	mes "その前に話しておきますが、";
	mes "以前にエンチャントを行っていた場合、";
	mes "その能力は失われます。";
	next;
	mes "[バルバリウェストフード]";
	mes "ひどい時は何の能力もない状態に";
	mes "戻ってしまいます。";
	mes "……救いといえば";
	mes "ロキのマフラーが壊れることは";
	mes "ないということでしょうか。";
	mes "さすがブランドもの！";
	next;
	mes "[バルバリウェストフード]";
	mes "では改めてお聞きします。";
	mes "エンチャントを行いますか？";
	next;
	if(select("エンチャントを止める","エンチャントする") == 1) {
		mes "[バルバリウェストフード]";
		mes "わかりました。";
		mes "私の腕を見せたかったのですが";
		mes "仕方ありません。";
		close;
	}
	misceffect 101,"";
	delitem 6380,5;
	delitem 2568,1;
	set '@rand,rand(100);
	if('@rand < 5) {
		// 未調査
		getitem 2568,1;
		mes "[バルバリウェストフード]";
		mes "……あ。失敗しました。";
		next;
		mes "[バルバリウェストフード]";
		mes "申し訳ありません。";
		mes "ロキのマフラーに";
		mes "能力は宿りませんでした。";
		close;
	}
	else {
		callfunc "MoraEnchants",'@enchant_card1,'@enchant_card2,'@enchant_card3;
		getitem2 2568,1,1,0,0,0,'@enchant_card1,'@enchant_card2,'@enchant_card3;
		mes "[バルバリウェストフード]";
		mes "さらにさらに最高のブランドに";
		mes "仕上がりましたよ！";
		mes "皆に見せびらかすと";
		mes "よいでしょう。";
		close;
	}
OnInit:
	waitingroom "ロキのマフラー",0;
	end;
}

//============================================================
// アーティファクト関連NPC
//------------------------------------------------------------
function	script	ArtifactEnchants	{
	set '@c,getarg(0);	// カテゴリー
	set '@s,getarg(1);	// 段階
	switch('@c) {
	case 1:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4792,4786,4787,4800,4795; break;
		case 2: setarray '@tbl_enchant,4791,4792,4793,4786,4787,4788,4800,4795,4796; break;
		case 3: setarray '@tbl_enchant,4792,4793,4794,4787,4788,4789,4800,4801,4796; break;
		}
		break;
	case 2:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4795,4700,4720,4811; break;
		case 2: setarray '@tbl_enchant,4791,4786,4795,4700,4701,4720,4721,4811,4810; break;
		case 3: setarray '@tbl_enchant,4700,4701,4702,4720,4721,4722,4811,4810,4809; break;
		}
		break;
	case 3:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4700,4701,4720,4721,4811,4810; break;
		case 2: setarray '@tbl_enchant,4700,4701,4702,4720,4721,4722,4811,4810,4809; break;
		case 3: setarray '@tbl_enchant,4701,4702,4703,4721,4722,4723,4812,4811,4810; break;
		}
		break;
	case 4:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4792,4786,4795,4796,4740; break;
		case 2: setarray '@tbl_enchant,4791,4792,4793,4786,4795,4796,4797,4740,4741; break;
		case 3: setarray '@tbl_enchant,4792,4793,4794,4740,4741,4742,4796,4797,4798; break;
		}
		break;
	case 5:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4792,4793,4740,4741,4796,4797; break;
		case 2: setarray '@tbl_enchant,4792,4793,4740,4741,4742,4796,4797,4798,4861; break;
		case 3: setarray '@tbl_enchant,4793,4741,4742,4743,4797,4798,4862; break;
		}
		break;
	case 6:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4795,4750,4730,4859; break;
		case 2: setarray '@tbl_enchant,4791,4786,4795,4750,4751,4730,4731,4859,4860; break;
		case 3: setarray '@tbl_enchant,4750,4751,4752,4730,4731,4732,4859,4860,4762; break;
		}
		break;
	case 7:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4750,4751,4730,4731,4860,4762; break;
		case 2: setarray '@tbl_enchant,4750,4751,4752,4730,4731,4732,4860,4762,4763; break;
		case 3: setarray '@tbl_enchant,4751,4752,4753,4731,4732,4733,4762,4763,4854; break;
		}
		break;
	case 8:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4786,4750,4730,4764; break;
		case 2: setarray '@tbl_enchant,4791,4786,4786,4750,4751,4730,4731,4764,4765; break;
		case 3: setarray '@tbl_enchant,4750,4751,4752,4730,4731,4732,4764,4765,4807; break;
		}
		break;
	case 9:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4750,4751,4730,4731,4764,4765; break;
		case 2: setarray '@tbl_enchant,4750,4751,4752,4730,4731,4732,4764,4765; break;
		case 3: setarray '@tbl_enchant,4751,4752,4753,4731,4732,4733,4765,4807; break;
		}
		break;
	case 10:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4800,4710,4720,4801; break;
		case 2: setarray '@tbl_enchant,4791,4786,4800,4801,4710,4711,4720,4721,4815; break;
		case 3: setarray '@tbl_enchant,4710,4711,4712,4720,4721,4722,4801,4815,4814; break;
		}
		break;
	case 11:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4710,4711,4720,4721,4801,4815; break;
		case 2: setarray '@tbl_enchant,4710,4711,4712,4720,4721,4722,4801,4815,4814; break;
		case 3: setarray '@tbl_enchant,4711,4712,4713,4721,4722,4723,4815,4814,4813; break;
		}
		break;
	case 12:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4815,4814,4711,4712,4721,4722; break;
		case 2: setarray '@tbl_enchant,4815,4814,4813,4711,4712,4713,4721,4722,4760; break;
		case 3: setarray '@tbl_enchant,4712,4713,4714,4722,4814,4813,4812,4760,4761; break;
		}
		break;
	case 13:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4800,4710,4750,4720; break;
		case 2: setarray '@tbl_enchant,4791,4786,4800,4710,4711,4750,4751,4720,4721; break;
		case 3: setarray '@tbl_enchant,4710,4711,4712,4750,4751,4752,4720,4721,4722; break;
		}
		break;
	case 14:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4710,4711,4750,4751,4720,4721; break;
		case 2: setarray '@tbl_enchant,4710,4711,4712,4750,4751,4720,4721,4722,4832; break;
		case 3: setarray '@tbl_enchant,4711,4712,4713,4751,4721,4722,4723,4832,4833; break;
		}
		break;
	case 15:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4791,4786,4795,4750,4700,4764; break;
		case 2: setarray '@tbl_enchant,4791,4786,4795,4750,4751,4700,4701,4764,4765; break;
		case 3: setarray '@tbl_enchant,4750,4751,4752,4700,4701,4702,4764,4765,4818; break;
		}
		break;
	case 16:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4750,4751,4700,4701,4764,4765; break;
		case 2: setarray '@tbl_enchant,4750,4751,4752,4700,4701,4702,4764,4765,4818; break;
		case 3: setarray '@tbl_enchant,4751,4752,4753,4701,4702,4703,4765,4818,4817; break;
		}
		break;
	case 17:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4795,4800,4786,4710,4720,4740; break;
		case 2: setarray '@tbl_enchant,4795,4800,4786,4710,4711,4720,4721,4740,4741; break;
		case 3: setarray '@tbl_enchant,4710,4711,4712,4720,4721,4740,4741,4742,4805; break;
		}
		break;
	case 18:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4710,4711,4720,4721,4740,4741; break;
		case 2: setarray '@tbl_enchant,4710,4711,4712,4720,4721,4740,4741,4742,4805; break;
		case 3: setarray '@tbl_enchant,4711,4712,4713,4721,4741,4742,4743,4805,4850; break;
		}
		break;
	case 19:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4795,4800,4786,4710,4700,4720; break;
		case 2: setarray '@tbl_enchant,4795,4800,4786,4710,4711,4700,4701,4720,4721; break;
		case 3: setarray '@tbl_enchant,4710,4711,4712,4700,4701,4702,4720,4721,4722; break;
		}
		break;
	case 20:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4710,4711,4700,4701,4720,4721; break;
		case 2: setarray '@tbl_enchant,4710,4711,4712,4700,4701,4702,4720,4721,4722; break;
		case 3: setarray '@tbl_enchant,4711,4712,4701,4702,4721,4722,4767,4861,4760; break;
		}
		break;
	case 21:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4795,4800,4786,4710,4720,4740; break;
		case 2: setarray '@tbl_enchant,4795,4800,4786,4710,4711,4720,4721,4740,4741; break;
		case 3: setarray '@tbl_enchant,4710,4711,4720,4721,4722,4740,4741,4861,4803; break;
		}
		break;
	case 22:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4795,4800,4786,4710,4720,4740; break;
		case 2: setarray '@tbl_enchant,4795,4800,4786,4710,4711,4720,4721,4740,4741; break;
		case 3: setarray '@tbl_enchant,4710,4711,4720,4721,4722,4740,4741,4861,4805; break;
		}
		break;
	case 23:
		switch('@s) {
		case 1: setarray '@tbl_enchant,4795,4800,4786,4710,4720,4740; break;
		case 2: setarray '@tbl_enchant,4795,4800,4786,4710,4711,4720,4721,4740,4741; break;
		case 3: setarray '@tbl_enchant,4710,4711,4720,4721,4722,4740,4741,4861,4804; break;
		}
		break;
	}
	set '@len,getarraysize('@tbl_enchant);
	set '@enchant,'@tbl_enchant[rand('@len)];
	return '@enchant;
}

mora.gat,152,97,5	script	アーティファクト管理人	515,{
	mes "[管理人]";
	mes "こんにちは、人間の冒険者。";
	mes "私はこのモーラの村の周辺で";
	mes "発見された古の装備、";
	mes "アーティファクトを管理してます。";
	mes "アーティファクトに興味はありますか？";
	next;
	switch(select("今は特にないです","^FF0000アーティファクトについて聞く^000000","^0000FFアーティファクトをください^000000")) {
	case 1:
		mes "[管理人]";
		mes "そうですか。";
		mes "興味がわいたら";
		mes "またいらしてください。";
		mes "それでは、モーラで";
		mes "ゆっくりしていってください。";
		close;
	case 2:
		break;
	case 3:
		mes "[管理人]";
		mes "どの職業のアーティファクトが";
		mes "必要ですか？";
		next;
		switch(select("やっぱり止めます","ルーンナイト","ギロチンクロス","レンジャー","ウォーロック","アークビショップ","武器を上位交換")) {
		case 1:
			mes "[管理人]";
			mes "そうですか、必要になったら";
			mes "またいらしてください。";
			close;
		case 2:
			mes "[管理人]";
			mes "ルーンナイトの";
			mes "アーティファクトで";
			mes "どちらが必要ですか？";
			next;
			switch(select("やっぱり止めます","ウルズグリーブ[1](靴) -> 20枚","ペオースグリーブ[1](靴) -> 20枚","ウルズマント[0](肩にかける物) -> 20枚","ペオースマント[0](肩にかける物) -> 20枚")) {
			case 1: break;
			case 2: set '@gain,2475; set '@coin,20; break;
			case 3: set '@gain,2476; set '@coin,20; break;
			case 4: set '@gain,2574; set '@coin,20; break;
			case 5: set '@gain,2575; set '@coin,20; break;
			}
			break;
		case 3:
			mes "[管理人]";
			mes "ギロチンクロスの";
			mes "アーティファクトで";
			mes "どちらが必要ですか？";
			next;
			switch(select("やっぱり止めます","サバフのシューズ[1](靴) -> 20枚","ナブのシューズ[1](靴) -> 20枚","サバフのフード[0](肩にかける物) -> 20枚","ナブのフード[0](肩にかける物) -> 20枚")) {
			case 1: break;
			case 2: set '@gain,2477; set '@coin,20; break;
			case 3: set '@gain,2478; set '@coin,20; break;
			case 4: set '@gain,2577; set '@coin,20; break;
			case 5: set '@gain,2578; set '@coin,20; break;
			}
			break;
		case 4:
			mes "[管理人]";
			mes "レンジャーの";
			mes "アーティファクトで";
			mes "どちらが必要ですか？";
			next;
			switch(select("やっぱり止めます","白羽のブーツ[1](靴) -> 20枚","黒羽のブーツ[1](靴) -> 20枚","白羽のマント[0](肩にかける物) -> 20枚","黒羽のマント[0](肩にかける物) -> 20枚")) {
			case 1: break;
			case 2: set '@gain,2479; set '@coin,20; break;
			case 3: set '@gain,2480; set '@coin,20; break;
			case 4: set '@gain,2580; set '@coin,20; break;
			case 5: set '@gain,2581; set '@coin,20; break;
			}
			break;
		case 5:
			mes "[管理人]";
			mes "ウォーロックの";
			mes "アーティファクトで";
			mes "どちらが必要ですか？";
			next;
			switch(select("やっぱり止めます","ゴールデンロッドスタッフ[2](両手杖) -> 50枚","アクアスタッフ[2](両手杖) -> 50枚","クリムゾンスタッフ[2](両手杖) -> 50枚","フォレストスタッフ[2](両手杖) -> 50枚","ゴールデンロッドシューズ[0](靴) -> 20枚","アクアシューズ[0](靴) -> 20枚","クリムゾンシューズ[0](靴) -> 20枚","フォレストシューズ[0](靴) -> 20枚","ゴールデンロッドローブ[0](鎧) -> 20枚","アクアローブ[0](鎧) -> 20枚","クリムゾンローブ[0](鎧) -> 20枚","フォレストローブ[0](鎧) -> 20枚")) {
			case 1: break;
			case 2: set '@gain,2007; set '@coin,50; break;
			case 3: set '@gain,2008; set '@coin,50; break;
			case 4: set '@gain,2009; set '@coin,50; break;
			case 5: set '@gain,2010; set '@coin,50; break;
			case 6: set '@gain,2467; set '@coin,20; break;
			case 7: set '@gain,2468; set '@coin,20; break;
			case 8: set '@gain,2469; set '@coin,20; break;
			case 9: set '@gain,2470; set '@coin,20; break;
			case 10:set '@gain,15025;set '@coin,20; break;
			case 11:set '@gain,15026;set '@coin,20; break;
			case 12:set '@gain,15027;set '@coin,20; break;
			case 13:set '@gain,15028;set '@coin,20; break;
			}
			break;
		case 6:
			mes "[管理人]";
			mes "アークビショップの";
			mes "アーティファクトで";
			mes "どちらが必要ですか？";
			next;
			if(select("武器","防具") == 1) {
				switch(select("やっぱり止めます","慈愛の杖[2](片手杖) -> 50枚","審判のメイス[2](鈍器) -> 50枚")) {
				case 1: break;
				case 2: set '@gain,1657; set '@coin,50; break;
				case 3: set '@gain,16013;set '@coin,50; break;
				}
			} else {
				switch(select("やっぱり止めます","慈愛の靴[0](靴) -> 20枚","審判の靴[0](靴) -> 20枚","慈愛のショール[0](肩にかける物) -> 20枚","審判のショール[0](肩にかける物) -> 20枚","慈愛のローブ[0](鎧) -> 20枚","審判のローブ[0](鎧) -> 20枚")) {
				case 1: break;
				case 2: set '@gain,2471; set '@coin,20; break;
				case 3: set '@gain,2472; set '@coin,20; break;
				case 4: set '@gain,2569; set '@coin,20; break;
				case 5: set '@gain,2570; set '@coin,20; break;
				case 6: set '@gain,15029;set '@coin,20; break;
				case 7: set '@gain,15030;set '@coin,20; break;
				}
			}
			break;
		case 7:
			mes "[管理人]";
			mes "ウォーロック、";
			mes "アークビショップの";
			mes "武器アーティファクトを";
			mes "より強い上位のアーティファクトと";
			mes "交換します。";
			next;
			mes "[管理人]";
			mes "これからあなたの持つ武器が";
			mes "交換するに値するか確認します。";
			mes "そのためにはあなたが";
			mes "武器のアーティファクトを";
			mes "装備している必要があります。";
			mes "交換対象の武器を装備していますか？";
			next;
			if(select("装備しています","装備してません") == 2) {
				mes "[管理人]";
				mes "そうですか。";
				mes "武器を装備してから";
				mes "私に話しかけてください。";
				close;
			}
			set '@itemid,getequipid(4);
			setarray '@artifact,2007,2008,2009,2010,1657,16013;
			for(set '@i,0; '@i < getarraysize('@artifact); set '@i,'@i+1) {
				if('@itemid == '@artifact['@i])
					break;
			}
			if('@i == '@len) {
				mes "[管理人]";
				mes "ウォーロック、";
				mes "またはアークビショップの";
				mes "武器のアーティファクトを";
				mes "装備していませんね。";
				mes "装備してから話しかけてください。";
				close;
			}
			set '@refine,getequiprefinerycnt('@menu);
			if('@refine < 7) {
				mes "[管理人]";
				mes "そのアーティファクトは";
				mes "精錬値が7未満ですね。";
				mes "7以上でないと、";
				mes "上位の武器と交換することは";
				mes "できません。";
				close;
			}
			// 未調査
			mes "[未調査]";
			close;
		}
		if('@gain == 0) {
			mes "[管理人]";
			mes "そうですか、必要になったら";
			mes "またいらしてください。";
			close;
		}
		mes "[管理人]";
		mes getitemname('@gain);
		mes "ですね。";
		mes "モーラコイン" +'@coin+ "枚との";
		mes "交換になります。";
		mes "本当によろしいですか？";
		next;
		if(select("やっぱりやめます","はい") == 1) {
			mes "[管理人]";
			mes "そうですか、必要になったら";
			mes "またいらしてください。";
			close;
		}
		if(countitem(6380) < '@coin) {
			mes "[管理人]";
			mes "申し訳ありません。";
			mes "モーラコインが足りません。";
			mes "それでは交換できません。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[管理人]";
			mes "荷物を持ちすぎのようですね。";
			mes "荷物の種類数を減らしてから";
			mes "また話しかけてください。";
			close;
		}
		if(MaxWeight - Weight < 5000) {
			mes "[管理人]";
			mes "荷物を持ちすぎのようですね。";
			mes "荷物の重量を減らしてから";
			mes "また話しかけてください。";
			close;
		}
		delitem 6380,'@coin;
		getitem '@gain,1;
		mes "[管理人]";
		mes "お受け取りください。";
		close;
	}
	mes "[管理人]";
	mes "アーティファクトとは";
	mes "このモーラの周辺で発見された";
	mes "非常に強力な装備です。";
	next;
	mes "[管理人]";
	mes "なぜ、この周辺で発見されるかは";
	mes "まだわかってませんが、";
	mes "どうやら古代の冒険者が使っていた";
	mes "物のようです。";
	next;
	mes "[管理人]";
	mes "私どもはレシア族の許可をとり、";
	mes "このアーティファクトを探しだし、";
	mes "冒険者たちに譲っているのです。";
	mes "アーティファクトは";
	mes "必ず冒険の助けになるでしょう。";
	next;
	mes "[管理人]";
	mes "現在、発見されている";
	mes "アーティファクトは、";
	mes "ルーンナイト、ギロチンクロス、";
	mes "レンジャー、ウォーロック、";
	mes "アークビショップの5職業の";
	mes "アーティファクトです。";
	next;
	mes "[管理人]";
	mes "ウォーロックと";
	mes "アークビショップのみ、";
	mes "防具だけではなく、";
	mes "武器も発見されています。";
	next;
	mes "[管理人]";
	mes "これらのアーティファクトは、";
	mes "モーラコインと交換でき、";
	mes "武器はモーラコイン^FF000050^000000枚、";
	mes "防具はモーラコイン^FF000020^000000枚で";
	mes "交換しています。";
	next;
	mes "[管理人]";
	mes "なお、武器に関しては、";
	mes "^FF0000精錬値が7以上^000000であり、";
	mes "さらに^FF0000特殊なエンチャントが";
	mes "付与されている場合^000000、";
	mes "上位の武器と交換することが";
	mes "できます。";
	next;
	mes "[管理人]";
	mes "実際のアーティファクトの";
	mes "性能については数が多い為、";
	mes "この資料に纏めました。";
	mes "性能を見たい職業はありますか？";
	while(1) {
		next;
		switch(select("ルーンナイト","ギロチンクロス","レンジャー","ウォーロック","アークビショップ","上位の武器との交換","もういいです")) {
		case 1:
			mes "[管理人]";
			mes "どの性能を見ますか？";
			while(1) {
				next;
				switch(select("^0000FFセット効果を見る^000000","ウルズグリーブ[1](靴)","ペオースグリーブ[1](靴)","ウルズマント[0](肩にかける物)","ペオースマント[0](肩にかける物)","他職業のアーティファクトを知りたい","もういいです")) {
				case 1:
					mes "[管理人]";
					mes "ルーンナイトのアーティファクトの";
					mes "どのセット効果を見ますか？";
					while(1) {
						next;
						switch(select("ウルズシリーズ装備","ペオースシリーズ装備","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
						case 1:
							mes "【セット効果】";
							mes "[ウルズプレート]";
							mes "[ウルズマント]";
							mes "[ウルズグリーブ]";
							mes "[ウルズブローチ]を共に装備時、";
							mes "MaxHP + 10%、";
							mes "無属性攻撃に対する耐性 + 5%、";
							mes "[ハンドレッドスピア]で";
							mes "与えるダメージ + 50%、";
							mes "スキル使用時の消費SP + 10%。";
							mes "　";
							mes "[ウルズプレート]";
							mes "[ウルズマント]";
							mes "[ウルズグリーブ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "MaxHP + 5%、";
							mes "無属性攻撃に対する耐性 + 5%、";
							mes "[ハンドレッドスピア]で";
							mes "与えるダメージ + 50%。";
							continue;
						case 2:
							mes "【セット効果】";
							mes "[ペオースプレート]";
							mes "[ペオースマント]";
							mes "[ペオースグリーブ]";
							mes "[ペオースブローチ]を共に装備時、";
							mes "物理攻撃で与えるダメージ + 10%、";
							mes "[コンセントレイション]";
							mes "使用時に5秒間Aspd + 2、";
							mes "[ソニックウェーブ]、";
							mes "[ウィンドカッター]で";
							mes "与えるダメージ + 100%。";
							mes "　";
							mes "[ペオースプレート]";
							mes "[ペオースマント]";
							mes "[ペオースグリーブ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "物理攻撃で与えるダメージ + 5%、";
							mes "[コンセントレイション]使用時に";
							mes "10秒間Aspd + 2(5秒間から";
							mes "10秒間に延長)。";
							continue;
						case 3:
							mes "[管理人]";
							mes "どのアーティファクトの";
							mes "性能を見ますか？";
							break;
						case 4:
							mes "[管理人]";
							mes "どの職業のアーティファクトを";
							mes "知りたいですか？";
							set '@job,1;
							break;
						case 5:
							mes "[管理人]";
							mes "わかりました。";
							mes "またいつでも来てください。";
							close;
						}
						break;
					}	// while end
					break;
				case 2:
					mes "【ウルズグリーブ[1]】";
					mes "―――――――――――――";
					mes "MaxSP + 40";
					mes "―――――――――――――";
					mes "精錬値が8以上の時、";
					mes "精錬値が 1 上がる毎に";
					mes "MaxHP + 1%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777732^000000";
					mes "重量 : ^77777790^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ルーンナイト^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 3:
					mes "【ペオースグリーブ[1]】";
					mes "―――――――――――――";
					mes "MaxSP + 40";
					mes "―――――――――――――";
					mes "精錬値が8以上の時、";
					mes "精錬値が 1 上がる毎に";
					mes "Agi + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777732^000000";
					mes "重量 : ^77777790^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ルーンナイト^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 4:
					mes "【ウルズマント[0]】";
					mes "―――――――――――――";
					mes "MaxHP + 2%";
					mes "―――――――――――――";
					mes "無属性攻撃に対する";
					mes "耐性 + 10%";
					mes "―――――――――――――";
					mes "精錬値が 1 上がる毎に";
					mes "MaxHP + 1%";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777720^000000";
					mes "重量 : ^77777760^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ルーンナイト^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 5:
					mes "【ペオースマント[0]】";
					mes "ペオースルーンストーンで";
					mes "作成されたマント。";
					mes "―――――――――――――";
					mes "Flee + 10 , Cri + 10";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777716^000000";
					mes "重量 : ^77777760^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ルーンナイト^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 6:
					mes "[管理人]";
					mes "どの職業のアーティファクトを";
					mes "知りたいですか？";
					set '@job,1;
					break;
				case 7:
					mes "[管理人]";
					mes "わかりました。";
					mes "またいつでも来てください。";
					close;
				}
				if('@job) {	// もう一つ抜ける
					set '@job,0;
					break;
				}
			}	// while end
			continue;
		case 2:
			mes "[管理人]";
			mes "どの性能を見ますか？";
			while(1) {
				next;
				switch(select("^0000FFセット効果を見る^000000","サバフのシューズ[1](靴)","ナブのシューズ[1](靴)","サバフのフード[0](肩にかける物)","ナブのフード[0](肩にかける物)","他職業のアーティファクトを知りたい","もういいです")) {
				case 1:
					mes "[管理人]";
					mes "ギロチンクロスのアーティファクトの";
					mes "どのセット効果を見ますか？";
					while(1) {
						next;
						switch(select("サバフシリーズ装備","ナブシリーズ装備","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
						case 1:
							mes "【セット効果】";
							mes "[サバフのクロース]";
							mes "[サバフのフード]";
							mes "[サバフのシューズ]";
							mes "[サバフのリング]を共に装備時、";
							mes "スキル使用時の消費SP + 10%、";
							mes "Cri + 7、";
							mes "クリティカル攻撃で";
							mes "与えるダメージ + 15%、";
							mes "Flee + 10、";
							mes "[クロスインパクト]で";
							mes "与えるダメージ + 20%。";
							mes "　";
							mes "[サバフのクロース]";
							mes "[サバフのフード]";
							mes "[サバフのシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "Cri + 8、";
							mes "クリティカル攻撃で";
							mes "与えるダメージ + 15%。";
							continue;
						case 2:
							mes "【セット効果】";
							mes "[ナブのクロース]";
							mes "[ナブのフード]";
							mes "[ナブのシューズ]";
							mes "[ナブのリング]を共に装備時、";
							mes "物理攻撃で与えるダメージ + 5%、";
							mes "Matk + 5%、";
							mes "Cri - 20、";
							mes "純粋なStrが120の時、Atk + 30、";
							mes "物理攻撃時、一定確率で";
							mes "[ソウルブレイカー]Lv1発動、";
							mes "[ソウルブレイカー]Lv2以上を";
							mes "習得している場合、習得レベルで発動。";
							mes "　";
							mes "[ナブのクロース]";
							mes "[ナブのフード]";
							mes "[ナブのシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "物理攻撃で与えるダメージ + 5%、";
							mes "Matk + 5%。";
							continue;
						case 3:
							mes "[管理人]";
							mes "どのアーティファクトの";
							mes "性能を見ますか？";
							break;
						case 4:
							mes "[管理人]";
							mes "どの職業のアーティファクトを";
							mes "知りたいですか？";
							set '@job,1;
							break;
						case 5:
							mes "[管理人]";
							mes "わかりました。";
							mes "またいつでも来てください。";
							close;
						}
						break;
					}	// while end
					break;
				case 2:
					mes "【サバフのシューズ[1]】";
					mes "―――――――――――――";
					mes "MaxSP + 30";
					mes "―――――――――――――";
					mes "Luk + 3";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777718^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ギロチンクロス^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 3:
					mes "【ナブのシューズ[1]】";
					mes "―――――――――――――";
					mes "Int + 2 , Flee + 3";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777718^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ギロチンクロス^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 4:
					mes "【サバフのフード[0]】";
					mes "―――――――――――――";
					mes "Flee + 12";
					mes "―――――――――――――";
					mes "精錬値が 1 上がる毎に";
					mes "クリティカル攻撃";
					mes "で与えるダメージ + 1%";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777713^000000";
					mes "重量 : ^77777710^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ギロチンクロス^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 5:
					mes "【ナブのフード[0]】";
					mes "―――――――――――――";
					mes "精錬値が 1 上がる毎に";
					mes "Atk + 2 , Flee + 2";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777713^000000";
					mes "重量 : ^77777710^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ギロチンクロス^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 6:
					mes "[管理人]";
					mes "どの職業のアーティファクトを";
					mes "知りたいですか？";
					set '@job,1;
					break;
				case 7:
					mes "[管理人]";
					mes "わかりました。";
					mes "またいつでも来てください。";
					close;
				}
				if('@job) {	// もう一つ抜ける
					set '@job,0;
					break;
				}
			}	// while end
			continue;
		case 3:
			mes "[管理人]";
			mes "どの性能を見ますか？";
			while(1) {
				next;
				switch(select("^0000FFセット効果を見る^000000","白羽のブーツ[1](靴)","黒羽のブーツ[1](靴)","白羽のマント[0](肩にかける物)","黒羽のマント[0](肩にかける物)","他職業のアーティファクトを知りたい","もういいです")) {
				case 1:
					mes "[管理人]";
					mes "レンジャーのアーティファクトの";
					mes "どのセット効果を見ますか？";
					while(1) {
						next;
						switch(select("白羽シリーズ装備","黒羽シリーズ装備","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
						case 1:
							mes "【セット効果】";
							mes "[白羽のスーツ]";
							mes "[白羽のマント]";
							mes "[白羽のブーツ]";
							mes "[白羽のブローチ]を共に装備時、";
							mes "Aspd + 1、";
							mes "遠距離物理攻撃で";
							mes "与えるダメージ + 15%、";
							mes "[アローストーム]で";
							mes "与えるダメージ + 10%、";
							mes "遠距離物理攻撃時、一定確率で";
							mes "[ダブルストレイフィング]";
							mes "Lv3発動、";
							mes "[ダブルストレイフィング]";
							mes "Lv4以上を習得している場合、";
							mes "習得レベルで発動。";
							mes "　";
							mes "[白羽のスーツ]";
							mes "[白羽のマント]";
							mes "[白羽のブーツ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "Aspd + 1、";
							mes "遠距離物理攻撃で";
							mes "与えるダメージ + 15%、";
							mes "[アローストーム]で";
							mes "与えるダメージ + 10%。";
							continue;
						case 2:
							mes "【セット効果】";
							mes "[黒羽のスーツ]";
							mes "[黒羽のマント]";
							mes "[黒羽のブーツ]";
							mes "[黒羽のブローチ]を共に装備時、";
							mes "MaxHP + 10%、";
							mes "完全回避 + 5、";
							mes "[クラスターボム]で";
							mes "与えるダメージ + 20%、";
							mes "遠距離物理攻撃で";
							mes "与えるダメージ - 20%、";
							mes "Aspd - 7。";
							mes "　";
							mes "[黒羽のスーツ]";
							mes "[黒羽のマント]";
							mes "[黒羽のブーツ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "MaxHP + 5%、";
							mes "完全回避 + 5、";
							mes "[クラスターボム]で";
							mes "与えるダメージ + 10%、";
							mes "遠距離物理攻撃で";
							mes "与えるダメージ - 10%。";
							continue;
						case 3:
							mes "[管理人]";
							mes "どのアーティファクトの";
							mes "性能を見ますか？";
							break;
						case 4:
							mes "[管理人]";
							mes "どの職業のアーティファクトを";
							mes "知りたいですか？";
							set '@job,1;
							break;
						case 5:
							mes "[管理人]";
							mes "わかりました。";
							mes "またいつでも来てください。";
							close;
						}
						break;
					}	// while end
					break;
				case 2:
					mes "【白羽のブーツ[1]】";
					mes "―――――――――――――";
					mes "Agi + 2";
					mes "―――――――――――――";
					mes "[エイムドボルト]を";
					mes "使用した時の消費SP - 10";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777718^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777レンジャー^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 3:
					mes "【黒羽のブーツ[1]】";
					mes "―――――――――――――";
					mes "MaxSP + 5%";
					mes "―――――――――――――";
					mes "Int + 2";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777718^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777レンジャー^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 4:
					mes "【白羽のマント[0]】";
					mes "―――――――――――――";
					mes "Agi + 2 , Flee + 10";
					mes "―――――――――――――";
					mes "物理攻撃時、";
					mes "一定確率で7秒間 Flee + 20";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777715^000000";
					mes "重量 : ^77777720^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777レンジャー^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 5:
					mes "【黒羽のマント[0]】";
					mes "―――――――――――――";
					mes "Int + 2";
					mes "―――――――――――――";
					mes "精錬値が7以上の時、";
					mes "精錬値が 1 上がる毎に";
					mes "完全回避 + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777715^000000";
					mes "重量 : ^77777720^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777レンジャー^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 6:
					mes "[管理人]";
					mes "どの職業のアーティファクトを";
					mes "知りたいですか？";
					set '@job,1;
					break;
				case 7:
					mes "[管理人]";
					mes "わかりました。";
					mes "またいつでも来てください。";
					close;
				}
				if('@job) {	// もう一つ抜ける
					set '@job,0;
					break;
				}
			}	// while end
			continue;
		case 4:
			mes "[管理人]";
			mes "どの性能を見ますか？";
			while(1) {
				next;
				switch(select("^0000FFセット効果を見る^000000","ゴールデンロッドスタッフ[2](両手杖)","アクアスタッフ[2](両手杖)","クリムゾンスタッフ[2](両手杖)","フォレストスタッフ[2](両手杖)","ゴールデンロッドシューズ[0](靴)","アクアシューズ[0](靴)","クリムゾンシューズ[0](靴)","フォレストシューズ[0](靴)","ゴールデンロッドローブ[0](鎧)","アクアローブ[0](鎧)","クリムゾンローブ[0](鎧)","フォレストローブ[0](鎧)","他職業のアーティファクトを知りたい","もういいです")) {
				case 1:
					mes "[管理人]";
					mes "ウォーロックのアーティファクトの";
					mes "どのセット効果を見ますか？";
					while(1) {
						next;
						switch(select("ゴールデンロッドシリーズ装備","アクアシリーズ装備","クリムゾンシリーズ装備","フォレストシリーズ装備","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
						case 1:
							mes "【セット効果】";
							mes "[ゴールデンロッドスタッフ]";
							mes "[ゴールデンロッドローブ]";
							mes "[ゴールデンロッドシューズ]";
							mes "[ゴールデンロッドオーブ]";
							mes "を共に装備時、";
							mes "風属性魔法攻撃で";
							mes "与えるダメージ + 20%、";
							mes "地属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "地属性攻撃に対する耐性 - 25%、";
							mes "風属性攻撃に対する耐性 + 15%。";
							mes "　";
							mes "[ゴールデンロッドスタッフ]";
							mes "[ゴールデンロッドローブ]";
							mes "[ゴールデンロッドシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "風属性魔法攻撃で";
							mes "与えるダメージ + 10%、";
							mes "地属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "地属性攻撃に対する耐性 - 25%。";
							continue;
						case 2:
							mes "【セット効果】";
							mes "[アクアスタッフ]";
							mes "[アクアローブ]";
							mes "[アクアシューズ]";
							mes "[アクアオーブ]";
							mes "を共に装備時、";
							mes "水属性魔法攻撃で";
							mes "与えるダメージ + 20%、";
							mes "風属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "風属性攻撃に対する耐性 - 25%、";
							mes "水属性攻撃に対する耐性 + 15%。";
							mes "　";
							mes "[アクアスタッフ]";
							mes "[アクアローブ]";
							mes "[アクアシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "水属性魔法攻撃で";
							mes "与えるダメージ + 10%、";
							mes "風属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "風属性攻撃に対する耐性 - 25%。";
							continue;
						case 3:
							mes "【セット効果】";
							mes "[クリムゾンスタッフ]";
							mes "[クリムゾンローブ]";
							mes "[クリムゾンシューズ]";
							mes "[クリムゾンオーブ]を共に装備時、";
							mes "火属性魔法攻撃で";
							mes "与えるダメージ + 20%、";
							mes "水属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "水属性攻撃に対する耐性 - 25%、";
							mes "火属性攻撃に対する耐性 + 15%。";
							mes "　";
							mes "[クリムゾンスタッフ]";
							mes "[クリムゾンローブ]";
							mes "[クリムゾンシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "火属性魔法攻撃で";
							mes "与えるダメージ + 10%、";
							mes "水属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "水属性攻撃に対する耐性 - 25%。";
							continue;
						case 4:
							mes "【セット効果】";
							mes "[フォレストスタッフ]";
							mes "[フォレストローブ]";
							mes "[フォレストシューズ]";
							mes "[フォレストオーブ]を共に装備時、";
							mes "地属性魔法攻撃で";
							mes "与えるダメージ + 20%、";
							mes "火属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "火属性攻撃に対する耐性 - 25%、";
							mes "地属性攻撃に対する耐性 + 15%。";
							mes "　";
							mes "[フォレストスタッフ]";
							mes "[フォレストローブ]";
							mes "[フォレストシューズ]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "地属性魔法攻撃で";
							mes "与えるダメージ + 10%、";
							mes "火属性魔法攻撃で";
							mes "与えるダメージ - 15%、";
							mes "火属性攻撃に対する耐性 - 25%。";
							continue;
						case 5:
							mes "[管理人]";
							mes "どのアーティファクトの";
							mes "性能を見ますか？";
							break;
						case 6:
							mes "[管理人]";
							mes "どの職業のアーティファクトを";
							mes "知りたいですか？";
							set '@job,1;
							break;
						case 7:
							mes "[管理人]";
							mes "わかりました。";
							mes "またいつでも来てください。";
							close;
						}
						break;
					}	// while end
					break;
				case 2:
					mes "【ゴールデンロッドスタッフ[2]】";
					mes "―――――――――――――";
					mes "Matk + 230";
					mes "―――――――――――――";
					mes "Int + 3";
					mes "―――――――――――――";
					mes "[ユピテルサンダー]で";
					mes "与えるダメージ + 12%";
					mes "―――――――――――――";
					mes "系列 : ^777777両手杖^000000";
					mes "攻撃 : ^77777730^000000";
					mes "重量 : ^77777790^000000";
					mes "属性 : ^777777風^000000";
					mes "武器レベル : ^7777774^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 3:
					mes "【アクアスタッフ[2]】";
					mes "―――――――――――――";
					mes "Matk + 230";
					mes "―――――――――――――";
					mes "Int + 3";
					mes "―――――――――――――";
					mes "[コールドボルト]";
					mes "[フロストダイバー]";
					mes "で与えるダメージ + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777両手杖^000000";
					mes "攻撃 : ^77777730^000000";
					mes "重量 : ^77777790^000000";
					mes "属性 : ^777777水^000000";
					mes "武器レベル : ^7777774^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 4:
					mes "【クリムゾンスタッフ[2]】";
					mes "―――――――――――――";
					mes "Matk + 230";
					mes "―――――――――――――";
					mes "Int + 3";
					mes "―――――――――――――";
					mes "[ファイアーボルト]、";
					mes "[ファイアーボール]";
					mes "で与えるダメージ + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777両手杖^000000";
					mes "攻撃 : ^77777730^000000";
					mes "重量 : ^77777790^000000";
					mes "属性 : ^777777火^000000";
					mes "武器レベル : ^7777774^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 5:
					mes "【フォレストスタッフ[2]】";
					mes "―――――――――――――";
					mes "Matk + 230";
					mes "―――――――――――――";
					mes "Int + 3";
					mes "―――――――――――――";
					mes "[アーススパイク]、";
					mes "[ヘヴンズドライブ]";
					mes "で与えるダメージ + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777両手杖^000000";
					mes "攻撃 : ^77777730^000000";
					mes "重量 : ^77777790^000000";
					mes "属性 : ^777777地^000000";
					mes "武器レベル : ^7777774^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 6:
					mes "【ゴールデンロッドシューズ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 2";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "風属性攻撃に";
					mes "対する耐性 + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777750^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 7:
					mes "【アクアシューズ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 2";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "水属性攻撃に";
					mes "対する耐性 + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777750^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 8:
					mes "【クリムゾンシューズ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 2";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "火属性攻撃に";
					mes "対する耐性 + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777750^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 9:
					mes "【フォレストシューズ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 2";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "地属性攻撃に";
					mes "対する耐性 + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777750^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 10:
					mes "【ゴールデンロッドローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Int + 1";
					mes "―――――――――――――";
					mes "[ロードオブヴァーミリオン]";
					mes "の詠唱時間 - 3秒";
					mes "―――――――――――――";
					mes "純粋なIntが 120の時、";
					mes "追加でInt + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777740^000000";
					mes "重量 : ^77777750^000000";
					mes "属性 : ^777777風^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 11:
					mes "【アクアローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Int + 1";
					mes "―――――――――――――";
					mes "[ストームガスト]の";
					mes "詠唱時間 - 3秒";
					mes "―――――――――――――";
					mes "純粋なIntが 120の時、";
					mes "追加でInt + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777740^000000";
					mes "重量 : ^77777750^000000";
					mes "属性 : ^777777水^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 12:
					mes "【クリムゾンローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Int + 1";
					mes "―――――――――――――";
					mes "[メテオストーム]の";
					mes "詠唱時間 - 3秒";
					mes "―――――――――――――";
					mes "純粋なIntが 120の時、";
					mes "追加でInt + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777740^000000";
					mes "重量 : ^77777750^000000";
					mes "属性 : ^777777火^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 13:
					mes "【フォレストローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Int + 1";
					mes "―――――――――――――";
					mes "[ヘヴンズドライブ]の";
					mes "詠唱時間 - 3秒";
					mes "―――――――――――――";
					mes "純粋なIntが 120の時、";
					mes "追加でInt + 1";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777740^000000";
					mes "重量 : ^77777750^000000";
					mes "属性 : ^777777地^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777ウォーロック^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 14:
					mes "[管理人]";
					mes "どの職業のアーティファクトを";
					mes "知りたいですか？";
					set '@job,1;
					break;
				case 15:
					mes "[管理人]";
					mes "わかりました。";
					mes "またいつでも来てください。";
					close;
				}
				if('@job) {	// もう一つ抜ける
					set '@job,0;
					break;
				}
			}	// while end
			continue;
		case 5:
			mes "[管理人]";
			mes "どの性能を見ますか？";
			while(1) {
				next;
				switch(select("^0000FFセット効果を見る^000000","慈愛の杖[2](片手杖)","審判のメイス[2](鈍器)","慈愛の靴[0](靴)","審判の靴[0](靴)","慈愛のショール[0](肩にかける物)","審判のショール[0](肩にかける物)","慈愛のローブ[0](鎧)","審判のローブ[0](鎧)","他職業のアーティファクトを知りたい","もういいです")) {
				case 1:
					mes "[管理人]";
					mes "アークビショップのアーティファクトの";
					mes "どのセット効果を見ますか？";
					while(1) {
						next;
						switch(select("慈愛シリーズ装備","審判シリーズ装備","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
						case 1:
							mes "【セット効果】";
							mes "[慈愛の杖]";
							mes "[慈愛のローブ]";
							mes "[慈愛の靴]";
							mes "[慈愛のショール]を共に装備時、";
							mes "[ヒール]を使用した時の";
							mes "SP消費量 + 20、";
							mes "[ヒール]";
							mes "[サンクチュアリ]";
							mes "[ポーションピッチャー]";
							mes "[ハイネスヒール]";
							mes "[コルセオヒール]";
							mes "を使用した時の回復量 + 20%、";
							mes "[クリアランス]";
							mes "[ラウダアグヌス]";
							mes "[ラウダラムス]の";
							mes "再使用待機時間 - 2秒。";
							mes "　";
							mes "[慈愛の杖]";
							mes "[慈愛のローブ]";
							mes "[慈愛の靴]";
							mes "[慈愛のショール]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "[ヒール]を使用した時の";
							mes "SP消費量 + 10、";
							mes "[ヒール]";
							mes "[サンクチュアリ]";
							mes "[ポーションピッチャー]";
							mes "[ハイネスヒール]";
							mes "[コルセオヒール]";
							mes "を使用した時の回復量 + 10%。";
							continue;
						case 2:
							mes "【セット効果】";
							mes "[審判のメイス]";
							mes "[審判のローブ]";
							mes "[審判の靴]";
							mes "[審判のショール]";
							mes "を共に装備時、";
							mes "不死属性モンスターへの";
							mes "物理攻撃・魔法攻撃で";
							mes "与えるダメージ + 10%、";
							mes "[アドラムス]で";
							mes "与えるダメージ + 50%、";
							mes "[アドラムス]を";
							mes "使用した時のSP消費量 + 30。";
							mes "　";
							mes "[審判のメイス]";
							mes "[審判のローブ]";
							mes "[審判の靴]";
							mes "[審判のショール]";
							mes "の精錬値が全て7以上の場合、";
							mes "追加で、";
							mes "不死属性モンスターへの";
							mes "物理攻撃・魔法攻撃で";
							mes "与えるダメージ + 5%、";
							mes "[アドラムス]で";
							mes "与えるダメージ + 100%。";
							continue;
						case 3:
							mes "[管理人]";
							mes "どのアーティファクトの";
							mes "性能を見ますか？";
							break;
						case 4:
							mes "[管理人]";
							mes "どの職業のアーティファクトを";
							mes "知りたいですか？";
							set '@job,1;
							break;
						case 5:
							mes "[管理人]";
							mes "わかりました。";
							mes "またいつでも来てください。";
							close;
						}
						break;
					}	// while end
					break;
				case 2:
					mes "【慈愛の杖[2]】";
					mes "―――――――――――――";
					mes "Matk + 160";
					mes "―――――――――――――";
					mes "Int + 2";
					mes "―――――――――――――";
					mes "[ヒール]、";
					mes "[サンクチュアリ]、";
					mes "[ポーションピッチャー]、";
					mes "[ハイネスヒール]、";
					mes "[コルセオヒール]";
					mes "を使用した時の回復量 + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777片手杖^000000";
					mes "攻撃 : ^77777730^000000";
					mes "重量 : ^77777750^000000";
					mes "属性 : ^777777聖^000000";
					mes "武器レベル : ^7777773^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 3:
					mes "【審判のメイス[2]】";
					mes "―――――――――――――";
					mes "Matk + 180";
					mes "―――――――――――――";
					mes "Str + 1 , Int + 1";
					mes "―――――――――――――";
					mes "物理攻撃時、一定確率";
					mes "で7秒間、悪魔形モンスターに";
					mes "与える物理ダメージ + 20%";
					mes "―――――――――――――";
					mes "魔法攻撃時、一定確率";
					mes "で7秒間、悪魔形モンスターに";
					mes "与える魔法ダメージ + 20%";
					mes "―――――――――――――";
					mes "系列 : ^777777鈍器^000000";
					mes "攻撃 : ^777777140^000000";
					mes "重量 : ^777777120^000000";
					mes "属性 : ^777777聖^000000";
					mes "武器レベル : ^7777773^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 4:
					mes "【慈愛の靴[0]】";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "人間形モンスターから";
					mes "受けるダメージ - 10%";
					mes "―――――――――――――";
					mes "人間形を除くモンスターから";
					mes "受けるダメージ + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777730^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 5:
					mes "【審判の靴[0]】";
					mes "―――――――――――――";
					mes "MaxSP + 150";
					mes "―――――――――――――";
					mes "「ジュデックス」で";
					mes "与えるダメージ + 30%";
					mes "―――――――――――――";
					mes "「ジュデックス」を";
					mes "使用した時のSP消費量 + 40";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777730^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 6:
					mes "【慈愛のショール[0]】";
					mes "―――――――――――――";
					mes "完全回避 + 5";
					mes "―――――――――――――";
					mes "物理・魔法攻撃を受けた時、";
					mes "一定確率で";
					mes "[レノヴァティオ]Lv 1発動";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 7:
					mes "【審判のショール[0]】";
					mes "―――――――――――――";
					mes "Flee + 5";
					mes "―――――――――――――";
					mes "物理・魔法攻撃を受けた時、";
					mes "一定確率で";
					mes "[オラティオ]Lv 2発動";
					mes "[オラティオ]Lv 3以上を";
					mes "習得している場合、";
					mes "習得レベルで発動";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^77777712^000000";
					mes "重量 : ^77777740^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 8:
					mes "【慈愛のローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Int + 1";
					mes "―――――――――――――";
					mes "[クレメンティア]を";
					mes "使用した時のSP消費量 - 50";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777722^000000";
					mes "重量 : ^77777730^000000";
					mes "属性 : ^777777聖^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 9:
					mes "【審判のローブ[0]】";
					mes "―――――――――――――";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "Str + 1 , Int + 1";
					mes "―――――――――――――";
					mes "悪魔形モンスターから";
					mes "受けるダメージ - 10%";
					mes "―――――――――――――";
					mes "不死形モンスターから";
					mes "受けるダメージ - 10%";
					mes "―――――――――――――";
					mes "悪魔形・不死形を除く";
					mes "モンスターから受ける";
					mes "ダメージ + 10%";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^77777722^000000";
					mes "重量 : ^77777730^000000";
					mes "属性 : ^777777闇^000000";
					mes "要求レベル : ^777777100^000000";
					mes "装備 : ^777777アークビショップ^000000";
					mes "^FF0000※セット効果もあります。";
					mes "　「セット効果を見る」を選択すれば";
					mes "　セット効果を確認できます。^000000";
					next;
					mes "[管理人]";
					mes "他のアーティファクトの性能も";
					mes "見ますか？";
					continue;
				case 10:
					mes "[管理人]";
					mes "どの職業のアーティファクトを";
					mes "知りたいですか？";
					set '@job,1;
					break;
				case 11:
					mes "[管理人]";
					mes "わかりました。";
					mes "またいつでも来てください。";
					close;
				}
				if('@job) {	// もう一つ抜ける
					set '@job,0;
					break;
				}
			}	// while end
			continue;
		case 6:
			mes "[管理人]";
			mes "どの職業の上位の武器を";
			mes "知りたいのですか？";
			next;
			switch(select("アークビショップ","ウォーロック")) {
			case 1:
				while(1) {
					switch(select("上位武器の交換方法について","^0000FFセット効果を見る^000000","慈愛の杖Ⅱ[1](片手杖)","審判のメイスⅡ[1](鈍器)","他職業のアーティファクトを知りたい","もういいです")) {
					case 1:
						mes "[管理人]";
						mes "アークビショップと";
						mes "ウォーロックの武器において、";
						mes "さらに強力な、";
						mes "上位の武器アーティファクトが";
						mes "発見されています。";
						next;
						mes "[管理人]";
						mes "この武器は非常に貴重で、";
						mes "持つにふさわしい方にしか";
						mes "お譲りできません。";
						mes "すなわちモーラコインとは";
						mes "交換していません。";
						next;
						mes "[管理人]";
						mes "お譲りできるのは、";
						mes "アークビショップとウォーロックの";
						mes "武器アーティファクトの能力を";
						mes "ひきだすことに";
						mes "成功している方のみです。";
						next;
						mes "[管理人]";
						mes "その能力をひきだした";
						mes "武器アーティファクトと交換に";
						mes "上位の武器アーティファクトを";
						mes "お譲りします。";
						next;
						mes "[管理人]";
						mes "武器アーティファクトが";
						mes "^0000FF精錬値7以上^000000であり、";
						mes "^0000FF特定の性能がエンチャント";
						mes "されている場合^000000、";
						mes "その上位の武器と交換しています。";
						next;
						mes "[管理人]";
						mes "その特定の性能のエンチャントは";
						mes "アーティファクトによって";
						mes "違います。";
						mes "特定の性能とは以下の通りです。";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "ゴールデンロッドスタッフ[2]";
						mes "クリムゾンスタッフ[2]";
						mes "アクアスタッフ[2]";
						mes "フォレストスタッフ[2]";
						mes "の4つについては";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "それぞれのⅡの装備と交換できます。";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Dex+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Dex+2 ";
						mes "-------------------------------";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "慈愛の杖[2]については";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "Ⅱの装備と交換できます。";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Dex+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Vit+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Dex+2 ";
						mes "-------------------------------";
						mes "1段階目：Vit+1、2段階目：Int+2 ";
						mes "-------------------------------";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "審判のメイス[2]については";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "Ⅱの装備と交換できます。";
						mes "--------------------------------";
						mes "1段階目：Int+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						mes "1段階目：Str+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						mes "1段階目：Dex+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						next;
						mes "[管理人]";
						mes "エンチャントは、私の横にいます";
						mes "「アーティファクト研究者」が";
						mes "行います。";
						mes "なお、エンチャントする場合には";
						mes "モーラコインが必要なので";
						mes "コインをご用意くださいね。";
						next;
						mes "[管理人]";
						mes "説明は以上になります。";
						mes "他に知りたいことはありますか？";
						next;
						continue;
					case 2:
						mes "[管理人]";
						mes "アークビショップのアーティファクトの";
						mes "どのセット効果を見ますか？";
						while(1) {
							next;
							switch(select("慈愛の杖Ⅱのセット効果","審判のメイスⅡのセット効果","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
							case 1:
								mes "【セット効果】";
								mes "[慈愛の杖Ⅱ]";
								mes "[慈愛のローブ]";
								mes "[慈愛の靴]";
								mes "[慈愛のショール]を共に装備時、";
								mes "[ヒール]を使用した時の";
								mes "SP消費量 + 40、";
								mes "[ヒール]";
								mes "[サンクチュアリ]";
								mes "[ポーションピッチャー]";
								mes "[ハイネスヒール]";
								mes "[コルセオヒール]";
								mes "を使用した時の回復量 + 40%、";
								mes "近接物理攻撃を受けた時、";
								mes "一定確率で";
								mes "[シレンティウム]Lv1発動、";
								mes "[クリアランス]";
								mes "[ラウダアグヌス][ラウダラムス]";
								mes "の再使用待機時間 - 3秒。";
								mes "　";
								mes "[慈愛の杖Ⅱ]";
								mes "[慈愛のローブ]";
								mes "[慈愛の靴]";
								mes "[慈愛のショール]";
								mes "の精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "[ヒール]を使用した時の";
								mes "SP消費量 + 10、";
								mes "[ヒール]";
								mes "[サンクチュアリ]";
								mes "[ポーションピッチャー]";
								mes "[ハイネスヒール]";
								mes "[コルセオヒール]を";
								mes "使用した時の回復量 + 10%。";
								continue;
							case 2:
								mes "【セット効果】";
								mes "[審判のメイスⅡ]";
								mes "[審判のローブ]";
								mes "[審判の靴]";
								mes "[審判のショール]を共に装備時、";
								mes "不死属性モンスターへの";
								mes "物理攻撃・魔法攻撃で";
								mes "与えるダメージ + 15%、";
								mes "[アドラムス]で";
								mes "与えるダメージ + 150%、";
								mes "[アドラムス]を";
								mes "使用した時のSP消費量 + 30、";
								mes "[ホーリーライト]";
								mes "[ターンアンデッド]";
								mes "[マグヌスエクソシズム]";
								mes "[ジュデックス]";
								mes "[アドラムス]の詠唱時間 - 50%。";
								mes "　";
								mes "[審判のメイスⅡ]";
								mes "[審判のローブ]";
								mes "[審判の靴]";
								mes "[審判のショール]の";
								mes "精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "不死属性モンスターへの";
								mes "物理攻撃・魔法攻撃で";
								mes "与えるダメージ + 15%、";
								mes "[アドラムス]で";
								mes "与えるダメージ + 50%。";
								continue;
							case 3:
								mes "[管理人]";
								mes "どのアーティファクトの";
								mes "性能を見ますか？";
								next;
								break;
							case 4:
								mes "[管理人]";
								mes "どの職業のアーティファクトを";
								mes "知りたいですか？";
								set '@job,1;
								break;
							case 5:
								mes "[管理人]";
								mes "わかりました。";
								mes "またいつでも来てください。";
								close;
							}
							break;
						}	// while end
						break;
					case 3:
						mes "【慈愛の杖Ⅱ[1]】";
						mes "―――――――――――――";
						mes "Matk + 180";
						mes "―――――――――――――";
						mes "Int + 4";
						mes "―――――――――――――";
						mes "[ヒール]、";
						mes "[サンクチュアリ]、";
						mes "[ポーションピッチャー]、";
						mes "[ハイネスヒール]、";
						mes "[コルセオヒール]";
						mes "を使用した時の回復量 + 20%";
						mes "―――――――――――――";
						mes "系列 : ^777777片手杖^000000";
						mes "攻撃 : ^77777730^000000";
						mes "重量 : ^77777750^000000";
						mes "属性 : ^777777聖^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777アークビショップ^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 4:
						mes "【審判のメイスⅡ[1]】";
						mes "―――――――――――――";
						mes "Matk + 180";
						mes "―――――――――――――";
						mes "Str + 2 , Int + 2";
						mes "―――――――――――――";
						mes "物理攻撃時、一定確率";
						mes "で7秒間、悪魔形モンスターに";
						mes "与える物理ダメージ + 40%";
						mes "―――――――――――――";
						mes "魔法攻撃時、一定確率";
						mes "で7秒間、悪魔形モンスターに";
						mes "与える魔法ダメージ + 40%";
						mes "―――――――――――――";
						mes "系列 : ^777777鈍器^000000";
						mes "攻撃 : ^777777170^000000";
						mes "重量 : ^777777120^000000";
						mes "属性 : ^777777聖^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777アークビショップ^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 5:
						mes "[管理人]";
						mes "どの職業のアーティファクトを";
						mes "知りたいですか？";
						set '@job,1;
						break;
					case 6:
						mes "[管理人]";
						mes "わかりました。";
						mes "またいつでも来てください。";
						close;
					}
					if('@job) {	// もう一つ抜ける
						set '@job,0;
						break;
					}
				}	// while end
				break;
			case 2:
				while(1) {
					switch(select("上位武器の交換方法について","^0000FFセット効果を見る^000000","ゴールデンロッドスタッフⅡ[1](両手杖)","アクアスタッフⅡ[1](両手杖)","クリムゾンスタッフⅡ[1](両手杖)","フォレストスタッフⅡ[1](両手杖)","他職業のアーティファクトを知りたい","もういいです")) {
					case 1:
						mes "[管理人]";
						mes "アークビショップと";
						mes "ウォーロックの武器において、";
						mes "さらに強力な、";
						mes "上位の武器アーティファクトが";
						mes "発見されています。";
						next;
						mes "[管理人]";
						mes "この武器は非常に貴重で、";
						mes "持つにふさわしい方にしか";
						mes "お譲りできません。";
						mes "すなわちモーラコインとは";
						mes "交換していません。";
						next;
						mes "[管理人]";
						mes "お譲りできるのは、";
						mes "アークビショップとウォーロックの";
						mes "武器アーティファクトの能力を";
						mes "ひきだすことに";
						mes "成功している方のみです。";
						next;
						mes "[管理人]";
						mes "その能力をひきだした";
						mes "武器アーティファクトと交換に";
						mes "上位の武器アーティファクトを";
						mes "お譲りします。";
						next;
						mes "[管理人]";
						mes "武器アーティファクトが";
						mes "^0000FF精錬値7以上^000000であり、";
						mes "^0000FF特定の性能がエンチャント";
						mes "されている場合^000000、";
						mes "その上位の武器と交換しています。";
						next;
						mes "[管理人]";
						mes "その特定の性能のエンチャントは";
						mes "アーティファクトによって";
						mes "違います。";
						mes "特定の性能とは以下の通りです。";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "ゴールデンロッドスタッフ[2]";
						mes "クリムゾンスタッフ[2]";
						mes "アクアスタッフ[2]";
						mes "フォレストスタッフ[2]";
						mes "の4つについては";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "それぞれのⅡの装備と交換できます。";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Dex+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Dex+2 ";
						mes "-------------------------------";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "慈愛の杖[2]については";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "Ⅱの装備と交換できます。";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Dex+2";
						mes "-------------------------------";
						mes "1段階目：Int+1、2段階目：Vit+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Int+2";
						mes "-------------------------------";
						mes "1段階目：Dex+1、2段階目：Dex+2 ";
						mes "-------------------------------";
						mes "1段階目：Vit+1、2段階目：Int+2 ";
						mes "-------------------------------";
						next;
						mes "^0000FF<Ⅱと交換可能な特定の性能>^000000";
						mes "審判のメイス[2]については";
						mes "^0000FF下記エンチャントの組み合わせの";
						mes "いずれか^000000であれば、";
						mes "Ⅱの装備と交換できます。";
						mes "--------------------------------";
						mes "1段階目：Int+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						mes "1段階目：Str+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						mes "1段階目：Dex+1";
						mes "2段階目：Int+2、Str+2、Dex+2の";
						mes "　　　　 いずれか";
						mes "--------------------------------";
						next;
						mes "[管理人]";
						mes "エンチャントは、私の横にいます";
						mes "「アーティファクト研究者」が";
						mes "行います。";
						mes "なお、エンチャントする場合には";
						mes "モーラコインが必要なので";
						mes "コインをご用意くださいね。";
						next;
						mes "[管理人]";
						mes "説明は以上になります。";
						mes "他に知りたいことはありますか？";
						next;
						continue;
					case 2:
						mes "[管理人]";
						mes "ウォーロックのアーティファクトの";
						mes "どのセット効果を見ますか？";
						while(1) {
							next;
							switch(select("ゴールデンロッドスタッフⅡのセット効果","アクアスタッフⅡのセット効果","クリムゾンスタッフⅡのセット効果","フォレストスタッフⅡのセット効果","他のアーティファクトの性能を知りたい","他職業のアーティファクトを知りたい","もういいです")) {
							case 1:
								mes "【セット効果】";
								mes "[ゴールデンロッドスタッフⅡ]";
								mes "[ゴールデンロッドローブ]";
								mes "[ゴールデンロッドシューズ]";
								mes "[ゴールデンロッドオーブ]";
								mes "を共に装備時、";
								mes "風属性魔法攻撃で";
								mes "与えるダメージ + 40%、";
								mes "地属性魔法攻撃で";
								mes "与えるダメージ - 40%、";
								mes "地属性攻撃に対する耐性 - 30%、";
								mes "風属性攻撃に対する耐性 + 15%。";
								mes "　";
								mes "[ゴールデンロッドスタッフⅡ]";
								mes "[ゴールデンロッドローブ]";
								mes "[ゴールデンロッドシューズ]";
								mes "の精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "風属性魔法攻撃で";
								mes "与えるダメージ + 10%、";
								mes "地属性魔法攻撃で";
								mes "与えるダメージ - 20%、";
								mes "地属性攻撃に対する耐性 - 20%。";
								continue;
							case 2:
								mes "【セット効果】";
								mes "[アクアスタッフⅡ]";
								mes "[アクアローブ]";
								mes "[アクアシューズ]";
								mes "[アクアオーブ]を共に装備時、";
								mes "水属性魔法攻撃で";
								mes "与えるダメージ + 40%、";
								mes "風属性魔法攻撃で";
								mes "与えるダメージ - 40%、";
								mes "風属性攻撃に対する耐性 - 30%、";
								mes "水属性攻撃に対する耐性 + 15%。";
								mes "　";
								mes "[アクアスタッフⅡ]";
								mes "[アクアローブ]";
								mes "[アクアシューズ]";
								mes "の精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "水属性魔法攻撃で";
								mes "与えるダメージ + 10%、";
								mes "風属性魔法攻撃で";
								mes "与えるダメージ - 20%、";
								mes "風属性攻撃に対する耐性 - 20%。";
								continue;
							case 3:
								mes "【セット効果】";
								mes "[クリムゾンスタッフⅡ]";
								mes "[クリムゾンローブ]";
								mes "[クリムゾンシューズ]";
								mes "[クリムゾンオーブ]を共に装備時、";
								mes "火属性魔法攻撃で";
								mes "与えるダメージ + 40%、";
								mes "水属性魔法攻撃で";
								mes "与えるダメージ - 40%、";
								mes "水属性攻撃に対する耐性 - 30%、";
								mes "火属性攻撃に対する耐性 + 15%。";
								mes "　";
								mes "[クリムゾンスタッフⅡ]";
								mes "[クリムゾンローブ]";
								mes "[クリムゾンシューズ]";
								mes "の精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "火属性魔法攻撃で";
								mes "与えるダメージ + 10%、";
								mes "水属性魔法攻撃で";
								mes "与えるダメージ - 20%、";
								mes "水属性攻撃に対する耐性 - 20%。";
								continue;
							case 4:
								mes "【セット効果】";
								mes "[フォレストスタッフⅡ]";
								mes "[フォレストローブ]";
								mes "[フォレストシューズ]";
								mes "[フォレストオーブ]を共に装備時、";
								mes "地属性魔法攻撃で";
								mes "与えるダメージ + 40%、";
								mes "火属性魔法攻撃で";
								mes "与えるダメージ - 40%、";
								mes "火属性攻撃に対する耐性 - 30%、";
								mes "地属性攻撃に対する耐性 + 15%。";
								mes "　";
								mes "[フォレストスタッフⅡ]";
								mes "[フォレストローブ]";
								mes "[フォレストシューズ]";
								mes "の精錬値が全て7以上の場合、";
								mes "追加で、";
								mes "地属性魔法攻撃で";
								mes "与えるダメージ + 10%、";
								mes "火属性魔法攻撃で";
								mes "与えるダメージ - 20%、";
								mes "火属性攻撃に対する耐性 - 20%。";
								continue;
							case 5:
								mes "[管理人]";
								mes "どのアーティファクトの";
								mes "性能を見ますか？";
								next;
								break;
							case 6:
								mes "[管理人]";
								mes "どの職業のアーティファクトを";
								mes "知りたいですか？";
								set '@job,1;
								break;
							case 7:
								mes "[管理人]";
								mes "わかりました。";
								mes "またいつでも来てください。";
								close;
							}
							break;
						}	// while end
						break;
					case 3:
						mes "【ゴールデンロッドスタッフⅡ[1]】";
						mes "―――――――――――――";
						mes "Matk + 270";
						mes "―――――――――――――";
						mes "Int + 5";
						mes "―――――――――――――";
						mes "[ユピテルサンダー]で";
						mes "与えるダメージ + 30%";
						mes "―――――――――――――";
						mes "系列 : ^777777両手杖^000000";
						mes "攻撃 : ^77777730^000000";
						mes "重量 : ^77777790^000000";
						mes "属性 : ^777777風^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777ウォーロック^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 4:
						mes "【アクアスタッフⅡ[1]】";
						mes "―――――――――――――";
						mes "Matk + 270";
						mes "―――――――――――――";
						mes "Int + 5";
						mes "―――――――――――――";
						mes "[コールドボルト]";
						mes "[フロストダイバー]";
						mes "で与えるダメージ + 30%";
						mes "―――――――――――――";
						mes "系列 : ^777777両手杖^000000";
						mes "攻撃 : ^77777730^000000";
						mes "重量 : ^77777790^000000";
						mes "属性 : ^777777水^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777ウォーロック^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 5:
						mes "【クリムゾンスタッフⅡ[1]】";
						mes "―――――――――――――";
						mes "Matk + 270";
						mes "―――――――――――――";
						mes "Int + 5";
						mes "―――――――――――――";
						mes "[ファイアーボルト]";
						mes "[ファイアーボール]";
						mes "で与えるダメージ + 30%";
						mes "―――――――――――――";
						mes "系列 : ^777777両手杖^000000";
						mes "攻撃 : ^77777730^000000";
						mes "重量 : ^77777790^000000";
						mes "属性 : ^777777火^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777ウォーロック^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 6:
						mes "【フォレストスタッフⅡ[1]】";
						mes "―――――――――――――";
						mes "Matk + 270";
						mes "―――――――――――――";
						mes "Int + 5";
						mes "―――――――――――――";
						mes "[アーススパイク]";
						mes "[ヘヴンズドライブ]";
						mes "で与えるダメージ + 30%";
						mes "―――――――――――――";
						mes "系列 : ^777777両手杖^000000";
						mes "攻撃 : ^77777730^000000";
						mes "重量 : ^77777790^000000";
						mes "重量 : ^777777地^000000";
						mes "武器レベル : ^7777774^000000";
						mes "要求レベル : ^777777130^000000";
						mes "装備 : ^777777ウォーロック^000000";
						mes "^FF0000※セット効果もあります。";
						mes "　「セット効果を見る」を選択すれば";
						mes "　セット効果を確認できます。^000000";
						next;
						mes "[管理人]";
						mes "他のアーティファクトの性能も";
						mes "見ますか？";
						next;
						continue;
					case 7:
						mes "[管理人]";
						mes "どの職業のアーティファクトを";
						mes "知りたいですか？";
						set '@job,1;
						break;
					case 8:
						mes "[管理人]";
						mes "わかりました。";
						mes "またいつでも来てください。";
						close;
					}
					if('@job) {	// もう一つ抜ける
						set '@job,0;
						break;
					}
				}	// while end
				break;
			}
			continue;
		case 7:
			mes "[管理人]";
			mes "わかりました。";
			mes "またいつでも来てください。";
			close;
		}
	}	// while end
OnInit:
	waitingroom "アーティファクト交換",0;
	end;
}

mora.gat,147,98,3	script	アーティファクト研究者	521,{
	mes "[アーティファクトの研究者]";
	mes "私はアーティファクトを";
	mes "研究しています。";
	mes "研究の結果、アーティファクトに";
	mes "エンチャントすることが";
	mes "できるようになりました。";
	next;
	mes "[アーティファクトの研究者]";
	mes "もしアーティファクトを";
	mes "お持ちであれば";
	mes "エンチャントしてあげましょう。";
	mes "ただし、費用として";
	mes "モーラコインと10万Zenyを";
	mes "いただきますよ。";
	next;
	switch(select("今はいいです","説明を聞く","エンチャントを行う","エンチャントの初期化を行う")) {
	case 1:
		mes "[アーティファクトの研究者]";
		mes "そうですか。";
		mes "必要になったらまた来てください。";
		mes "お待ちしています。";
		close;
	case 2:
		mes "[アーティファクトの研究者]";
		mes "それでは説明しますね。";
		mes "アーティファクトに";
		mes "エンチャントを^FF00003段階^000000まで";
		mes "行うことができます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "ただしゴールデンロッドスタッフ[2]、";
		mes "アクアスタッフ[2]、クリムゾン";
		mes "スタッフ[2]、フォレストスタッフ[2]、";
		mes "慈愛の杖[2]、審判のメイス[2]の";
		mes "6装備は、^FF00002段階^000000までの";
		mes "エンチャントとなっています。";
		next;
		mes "[アーティファクトの研究者]";
		mes "1度に3段階エンチャント";
		mes "するのではなく、";
		mes "1段階ずつエンチャントしていきます。";
		mes "^FF00001段階ごとにモーラコイン1枚と";
		mes "10万Zenyが必要になります。^000000";
		next;
		mes "[アーティファクトの研究者]";
		mes "なお、エンチャントは、";
		mes "アーティファクトを";
		mes "装備した状態で行いますので、";
		mes "装備してから話しかけてくださいね。";
		next;
		mes "[アーティファクトの研究者]";
		mes "エンチャントの効果は";
		mes "初期化することもできます。";
		mes "やはり初期化もモーラコイン1枚と";
		mes "10万Zenyが必要になります。";
		mes "カード効果と精錬値については";
		mes "初期化されないのでご安心ください。";
		next;
		mes "[アーティファクトの研究者]";
		mes "次に注意事項について説明します。";
		next;
		mes "[アーティファクトの研究者]";
		mes "1段階目は何の危険もなく";
		mes "エンチャントできますが、";
		mes "2段階目ではエンチャントに失敗し";
		mes "エンチャント効果を";
		mes "初期化してしまう可能性があります。";
		next;
		mes "[アーティファクトの研究者]";
		mes "3段階目についても失敗して";
		mes "初期化してしまう可能性があり、";
		mes "さらに^FF0000破壊してしまう可能性^000000";
		mes "があります。";
		next;
		mes "[アーティファクトの研究者]";
		mes "破壊されてしまった場合、";
		mes "当然そのアーティファクトは";
		mes "失われてしまいます。";
		mes "2段階目以降のエンチャントは";
		mes "大変難しく、必ず成功する";
		mes "わけではないんです。";
		next;
		mes "[アーティファクトの研究者]";
		mes "しかし、悪いことばかりでは";
		mes "ありませんよ。";
		mes "アーティファクトエンチャントでは、";
		mes "エンチャントしても";
		mes "^FF0000精錬値とカード効果は失われず、";
		mes "維持することができるんです。^000000";
		next;
		mes "[アーティファクトの研究者]";
		mes "精錬値7でエンチャントしても";
		mes "精錬値7が残りますし、";
		mes "カードを挿していても";
		mes "その挿したカードは";
		mes "そのまま残ります。";
		mes "これは大きなメリットだと思います。";
		next;
		mes "[アーティファクトの研究者]";
		mes "そして次にエンチャントの";
		mes "効果について説明します。";
		mes "エンチャントされる効果は";
		mes "アーティファクトごとに違います。";
		mes "様々なカテゴリに分かれるのです。";
		next;
		mes "[アーティファクトの研究者]";
		mes "たとえば、慈愛シリーズエンチャントは";
		mes "「慈愛1」という名前の";
		mes "支援職向けのカテゴリになります。";
		mes "「慈愛1」は、主にInt、Dex、";
		mes "ヒール系の回復量増加といった";
		mes "効果がエンチャントされます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "サバフシリーズは、";
		mes "「クリティカル系1」という";
		mes "カテゴリになり、";
		mes "主にCriやLukが増加する効果が";
		mes "エンチャントされます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "通常、カテゴリは";
		mes "アーティファクトごとに固定であり、";
		mes "選択することはできません。";
		next;
		mes "[アーティファクトの研究者]";
		mes "しかし、アーティファクトの";
		mes "^FF0000精錬値が9以上の場合、^000000";
		mes "その強力な力により、";
		mes "カテゴリが2つに増え、";
		mes "選択することが出来ます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "慈愛シリーズでいうと、";
		mes "「慈愛1」と「慈愛2」から";
		mes "どちらの効果をエンチャントするか";
		mes "選択できるようになります。";
		mes "「慈愛2」の方が";
		mes "強い効果がエンチャントされます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "何のカテゴリが増えるかは";
		mes "アーティファクトごとに違います。";
		next;
		mes "[アーティファクトの研究者]";
		mes "慈愛シリーズのように、より強い";
		mes "カテゴリが増えるものもあれば、";
		mes "タイプが全く違う、";
		mes "カテゴリが増える場合もあります。";
		next;
		mes "[アーティファクトの研究者]";
		mes "なお、アークビショップと";
		mes "ウォーロックのアーティファクトである";
		mes "^FF0000杖、鈍器のⅡシリーズ^000000は";
		mes "元々非常に強力な力を持っているので、";
		mes "^FF0000精錬値が7以上^000000で";
		mes "カテゴリが2つに増えます。";
		next;
		mes "[アーティファクトの研究者]";
		mes "説明は以上です。";
		mes "是非アーティファクトを手に入れて";
		mes "エンチャントをしてくださいね。";
		close;
	case 3:
		if(countitem(6380) < 1 || Zeny < 100000) {
			mes "[アーティファクトの研究者]";
			mes "エンチャントをするためには、";
			mes "モーラコイン1枚と";
			mes "10万Zenyが必要です。";
			mes "残念ですがあなたは、";
			mes "お持ちではないようです。";
			close;
		}
		mes "[アーティファクトの研究者]";
		mes "^0000FFエンチャント^000000にはモーラコイン1枚と";
		mes "10万Zenyが必要です。";
		mes "また、対象のアーティファクトを";
		mes "装備している必要があります。";
		mes "どの部位のアーティファクトを";
		mes "エンチャントしますか？";
		next;
		set '@menu,select(
				"装備しなおします",
				(getequipid(4)!=0? "^nItemID^" +getequipid(4): "(右手)‐[装着していない]"),
				(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴‐[装着していない]"),
				(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装着していない]"),
				(getequipid(2)!=0? "^nItemID^" +getequipid(2): "鎧‐[装着していない]"),
				(getequipid(7)!=0? "^nItemID^" +getequipid(7): "アクセサリー1‐[装着していない]"),
				(getequipid(8)!=0? "^nItemID^" +getequipid(8): "アクセサリー2‐[装着していない]"),
				(getequipid(3)!=0? "^nItemID^" +getequipid(3): "(左手)‐[装着していない]"));
		switch('@menu) {
		case 1:
			mes "[アーティファクトの研究者]";
			mes "わかりました。";
			mes "エンチャントしたい";
			mes "アーティファクトを装備したら";
			mes "また話しかけてください。";
			close;
		case 2: set '@itemid,getequipid(4); set '@menu,4; break;
		case 3: set '@itemid,getequipid(6); set '@menu,6; break;
		case 4: set '@itemid,getequipid(5); set '@menu,5; break;
		case 5: set '@itemid,getequipid(2); set '@menu,2; break;
		case 6: set '@itemid,getequipid(7); set '@menu,7; break;
		case 7: set '@itemid,getequipid(8); set '@menu,8; break;
		case 8: set '@itemid,getequipid(3); set '@menu,3; break;
		}
		if('@itemid == 0) {
			mes "[アーティファクトの研究者]";
			mes "おや、";
			mes "装備していませんよ。";
			mes "アーティファクトを";
			mes "装備してから";
			mes "話しかけてください。";
			close;
		}
		switch(Job) {
		case Job_RuneKnight:
			setarray '@artifact,2475,2476,2574,2575,2883,2884,15036,15037;
			break;
		case Job_Warlock:
			setarray '@artifact,2007,2008,2009,2010,2011,2012,2013,2014,2467,2468,2469,2470,2859,2860,2861,2862,15025,15026,15027,15028;
			break;
		case Job_Ranger:
			setarray '@artifact,2479,2480,2580,2581,2890,2891,15042,15043;
			break;
		case Job_ArchBishop:
			setarray '@artifact,1657,1660,16013,16018,2156,2471,2472,2569,2570,2864,2865,2866,15029,15030;
			break;
		case Job_Guillotine:
			setarray '@artifact,2477,2478,2577,2578,2886,2887,15038,15039;
			break;
		}
		set '@len,getarraysize('@artifact);
		for(set '@i,0; '@i < '@len; set '@i,'@i+1) {
			if('@itemid == '@artifact['@i])
				break;
		}
		if('@i == '@len) {
			mes "[アーティファクトの研究者]";
			mes "^990099^nItemID^" +'@itemid+ "^000000？";
			mes "アーティファクトではないですよ。";
			mes "アーティファクトを装備して";
			mes "話しかけてください。";
			close;
		}
		set '@refine,getequiprefinerycnt('@menu);
		setarray '@categoryname$,
			"Nothing",
			"防御力系",
			"攻撃力系1","攻撃力系2",
			"体力系1","体力系2",
			"回避系1","回避系2",
			"攻撃速度系1","攻撃速度系2",
			"魔法系1","魔法系2","魔法系3",
			"遠距離物理系1","遠距離物理系2",
			"クリティカル系1","クリティカル系2",
			"慈愛1","慈愛2",
			"審判1","審判2",
			"治癒","大司教","大聖堂";
		switch('@itemid) {
		// RuneKnight
		case 2475: setarray '@category,1,('@refine>=9? 4: 0); set '@flag,0; break;
		case 2476: setarray '@category,1,('@refine>=9? 8: 0); set '@flag,0; break;
		case 2574: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2575: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2883: setarray '@category,1; set '@flag,0; break;
		case 2884: setarray '@category,1; set '@flag,0; break;
		case 15036:setarray '@category,4,('@refine>=9? 5: 0); set '@flag,0; break;
		case 15037:setarray '@category,8,('@refine>=9? 9: 0); set '@flag,0; break;
		// Warlock
		case 2007: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,1; break;
		case 2008: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,1; break;
		case 2009: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,1; break;
		case 2010: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,1; break;
		case 2011: setarray '@category,10,('@refine>=7? 12: 0); set '@flag,0; break;
		case 2012: setarray '@category,10,('@refine>=7? 12: 0); set '@flag,0; break;
		case 2013: setarray '@category,10,('@refine>=7? 12: 0); set '@flag,0; break;
		case 2014: setarray '@category,10,('@refine>=7? 12: 0); set '@flag,0; break;
		case 2467: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 2468: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 2469: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 2470: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 2859: setarray '@category,1; set '@flag,0; break;
		case 2860: setarray '@category,1; set '@flag,0; break;
		case 2861: setarray '@category,1; set '@flag,0; break;
		case 2862: setarray '@category,1; set '@flag,0; break;
		case 15025:setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 15026:setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 15027:setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 15028:setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		// Ranger
		case 2479: setarray '@category,1,('@refine>=9? 15: 0); set '@flag,0; break;
		case 2480: setarray '@category,1,('@refine>=9? 13: 0); set '@flag,0; break;
		case 2580: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2581: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2890: setarray '@category,1; set '@flag,0; break;
		case 2891: setarray '@category,1; set '@flag,0; break;
		case 15042: setarray '@category,15,('@refine>=9? 16: 0); set '@flag,0; break;
		case 15043: setarray '@category,13,('@refine>=9? 14: 0); set '@flag,0; break;
		// ArchBishop
		case 1657: setarray '@category,17,('@refine>=9? 18: 0); set '@flag,1; break;
		case 1660: setarray '@category,17,('@refine>=7? 18: 0); set '@flag,0; break;
		case 16013:setarray '@category,19,('@refine>=9? 20: 0); set '@flag,1; break;
		case 16018:setarray '@category,19,('@refine>=7? 20: 0); set '@flag,0; break;
		case 2156: setarray '@category,10,('@refine>=9? 11: 0); set '@flag,0; break;
		case 2471: setarray '@category,17,('@refine>=9? 18: 0); set '@flag,0; break;
		case 2472: setarray '@category,19,('@refine>=9? 20: 0); set '@flag,0; break;
		case 2569: setarray '@category,17,('@refine>=9? 18: 0); set '@flag,0; break;
		case 2570: setarray '@category,19,('@refine>=9? 20: 0); set '@flag,0; break;
		case 2864: setarray '@category,21; set '@flag,0; break;
		case 2865: setarray '@category,23; set '@flag,0; break;
		case 2866: setarray '@category,22; set '@flag,0; break;
		case 15029:setarray '@category,17,('@refine>=9? 18: 0); set '@flag,0; break;
		case 15030:setarray '@category,19,('@refine>=9? 20: 0); set '@flag,0; break;
		// Guillotine
		case 2477: setarray '@category,1,('@refine>=9? 15: 0); set '@flag,0; break;
		case 2478: setarray '@category,1,('@refine>=9?  2: 0); set '@flag,0; break;
		case 2577: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2578: setarray '@category,6,('@refine>=9? 7: 0); set '@flag,0; break;
		case 2886: setarray '@category,1; set '@flag,0; break;
		case 2887: setarray '@category,1; set '@flag,0; break;
		case 15038:setarray '@category,15,('@refine>=9? 16: 0); set '@flag,0; break;
		case 15039:setarray '@category, 2,('@refine>=9?  3: 0); set '@flag,0; break;
		}
		if('@category[1]) {
			// 未調査
			mes "[アーティファクトの研究者]";
			mes getitemname('@itemid)+ "ですね。";
			mes "このアーティファクトには";
			mes "^FF0000" +'@categoryname$['@category[0]]+ "^000000";
			mes "^FF0000" +'@categoryname$['@category[1]]+ "^000000";
			mes "という種類の効果を";
			mes "エンチャントできます。";
			next;
			mes "[アーティファクトの研究者]";
			mes "どちらのエンチャントを";
			mes "行いますか？";
			next;
			if(select('@categoryname$['@category[0]],'@categoryname$['@category[0]]+ "^FF0000(精錬値9以上)^000000") == 2)
				set '@category[0],'@category[1];
		} else {
			mes "[アーティファクトの研究者]";
			mes getitemname('@itemid)+ "ですね。";
			mes "このアーティファクトには";
			mes "^FF0000" +'@categoryname$['@category[0]]+ "^000000";
			mes "という種類の効果を";
			mes "エンチャントできます。";
			next;
		}
		set '@card1,getequipcardid('@menu,0);
		set '@card[0],'@card1;
		set '@card2,getequipcardid('@menu,1);
		set '@card[1],'@card2;
		set '@card3,getequipcardid('@menu,2);
		set '@card[2],'@card3;
		set '@card4,getequipcardid('@menu,3);
		set '@card[3],'@card4;
		if('@card2 != 0) {
			mes "[アーティファクトの研究者]";
			mes "おや、このアーティファクトは";
			mes "エンチャントによる性能が";
			mes "限界までひきだされていますね。";
			mes "これ以上はエンチャントできません。";
			close;
		} else if('@card3 != 0) {
			if('@flag) {
				// 未調査
				mes "[アーティファクトの研究者]";
				mes "おや、このアーティファクトは";
				mes "エンチャントによる性能が";
				mes "限界までひきだされていますね。";
				mes "これ以上はエンチャントできません。";
				close;
			}
			mes "[アーティファクトの研究者]";
			mes "このアーティファクトには";
			mes "第2段階のエンチャントが";
			mes "されていますので、今回";
			mes "^FF0000第3段階^000000のエンチャントを行えます。";
			mes "行いましょうか？";
			set '@soket,3;
			set '@slot,1;
			set '@str$,"^9900002番目のスロット^000000";
		} else if('@card4 != 0) {
			mes "[アーティファクトの研究者]";
			mes "このアーティファクトには";
			mes "第1段階のエンチャントが";
			mes "されていますので、今回";
			mes "^FF0000第2段階^000000のエンチャントを行えます。";
			mes "行いましょうか？";
			set '@soket,2;
			set '@slot,2;
			set '@str$,"^9900003番目のスロット^000000";
		} else {
			mes "[アーティファクトの研究者]";
			mes "このアーティファクトには";
			mes "エンチャントの効果は";
			mes "何もありませんので";
			mes "^FF0000第1段階^000000のエンチャントを行えます。";
			mes "行いましょうか？";
			set '@soket,1;
			set '@slot,3;
			set '@str$,"^9900004番目のスロット^000000";
		}
		next;
		if(select("やめます","エンチャントを行う") == 1) {
			mes "[アーティファクトの研究者]";
			mes "そうですか。";
			mes "必要になったらまた来てください。";
			mes "お待ちしています。";
			close;
		}
		set '@rand,rand(100);
		if('@soket >= 3 && '@rand < 5) {
			misceffect 183,"";
			mes "[アーティファクトの研究者]";
			mes "ああっ！";
			mes "アーティファクトが";
			mes "壊れてしまいました……";
			mes "非常に残念です……";
			delitem 6380,1;
			set Zeny,Zeny-100000;
			delequip '@menu;
			close;
		} else if('@soket >= 2 && '@rand < 15) {
			misceffect 246,"";
			mes "[アーティファクトの研究者]";
			mes "アーティファクトの能力が";
			mes "全てなくなってしまいました。";
			mes "非常に残念です……";
			delitem 6380,1;
			set Zeny,Zeny-100000;
			delequip '@menu;
			getitem2 '@itemid,1,1,'@refine,0,'@card[0],0,0,0;
			close;
		} else {
			misceffect 101,"";
			mes "[アーティファクトの研究者]";
			mes '@str$+ "に";
			mes "効果を付与することができました。";
			mes "お受け取りください。";
			delitem 6380,1;
			set Zeny,Zeny-100000;
			delequip '@menu;
			set '@card['@slot],callfunc("ArtifactEnchants",'@category[0],'@soket);
			getitem2 '@itemid,1,1,'@refine,0,'@card[0],'@card[1],'@card[2],'@card[3];
			close;
		}
	case 4:
		if(countitem(6380) < 1 || Zeny < 100000) {
			mes "[アーティファクトの研究者]";
			mes "初期化するためには、";
			mes "モーラコイン1枚と";
			mes "10万Zenyが必要です。";
			mes "残念ですがあなたは、";
			mes "お持ちではないようです。";
			close;
		}
		mes "[アーティファクトの研究者]";
		mes "^0000FF初期化^000000にはモーラコイン1枚と";
		mes "10万Zenyが必要です。";
		mes "また、対象のアーティファクトを";
		mes "装備している必要があります。";
		mes "どの部位のアーティファクトを";
		mes "初期化しますか？";
		next;
		switch(
				select("装備しなおします",
				(getequipid(4)!=0? "^nItemID^" +getequipid(4): "(右手)‐[装着していない]"),
				(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴‐[装着していない]"),
				(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装着していない]"),
				(getequipid(2)!=0? "^nItemID^" +getequipid(2): "鎧‐[装着していない]"),
				(getequipid(7)!=0? "^nItemID^" +getequipid(7): "アクセサリー1‐[装着していない]"),
				(getequipid(8)!=0? "^nItemID^" +getequipid(8): "アクセサリー2‐[装着していない]"),
				(getequipid(3)!=0? "^nItemID^" +getequipid(3): "(左手)‐[装着していない]"))
		) {
		case 1:
			mes "[アーティファクトの研究者]";
			mes "わかりました。";
			mes "エンチャントしたい";
			mes "アーティファクトを装備したら";
			mes "また話しかけてください。";
			close;
		case 2: set '@itemid,getequipid(4); set '@menu,4; break;
		case 3: set '@itemid,getequipid(6); set '@menu,6; break;
		case 4: set '@itemid,getequipid(5); set '@menu,5; break;
		case 5: set '@itemid,getequipid(2); set '@menu,2; break;
		case 6: set '@itemid,getequipid(7); set '@menu,7; break;
		case 7: set '@itemid,getequipid(8); set '@menu,8; break;
		case 8: set '@itemid,getequipid(3); set '@menu,3; break;
		}
		if('@itemid == 0) {
			mes "[アーティファクトの研究者]";
			mes "おや、";
			mes "装備していませんよ。";
			mes "アーティファクトを";
			mes "装備してから";
			mes "話しかけてください。";
			close;
		}
		switch(Job) {
		case Job_RuneKnight:
			setarray '@artifact,2475,2476,2574,2575,2883,2884,15036,15037;
			break;
		case Job_Warlock:
			setarray '@artifact,2007,2008,2009,2010,2011,2012,2013,2014,2467,2468,2469,2470,2859,2860,2861,2862,15025,15026,15027,15028;
			break;
		case Job_Ranger:
			setarray '@artifact,2479,2480,2580,2581,2890,2891,15042,15043;
			break;
		case Job_ArchBishop:
			setarray '@artifact,1657,1660,16013,16018,2156,2471,2472,2569,2570,2864,2865,2866,15029,15030;
			break;
		case Job_Guillotine:
			setarray '@artifact,2477,2478,2577,2578,2886,2887,15038,15039;
			break;
		}
		set '@len,getarraysize('@artifact);
		for(set '@i,0; '@i < '@len; set '@i,'@i+1) {
			if('@itemid == '@artifact['@i])
				break;
		}
		if('@i == '@len) {
			mes "[アーティファクトの研究者]";
			mes "^990099^nItemID^" +'@itemid+ "^000000？";
			mes "アーティファクトではないですよ。";
			mes "アーティファクトを装備して";
			mes "話しかけてください。";
			close;
		}
		mes "[アーティファクトの研究者]";
		mes getitemname('@itemid)+ "を";
		mes "初期化します。";
		mes "エンチャント効果が全て消えますが、";
		mes "本当によろしいですか？";
		next;
		if(select("やっぱりやめます","初期化します") == 1) {
			mes "[アーティファクトの研究者]";
			mes "わかりました。";
			mes "必要になったら";
			mes "いつでも来てください。";
			close;
		}
		set '@refine,getequiprefinerycnt('@menu);
		set '@card1,getequipcardid('@menu,0);
		set '@card2,getequipcardid('@menu,1);
		set '@card3,getequipcardid('@menu,2);
		set '@card4,getequipcardid('@menu,3);
		misceffect 101,"";
		mes "[アーティファクトの研究者]";
		mes "それではエンチャントの効果を";
		mes "すべて消しましょう。";
		delitem 6380,1;
		set Zeny,Zeny-100000;
		delequip '@menu;
		getitem2 '@itemid,1,1,'@refine,0,'@card1,0,0,0;
		close;
	}
OnInit:
	waitingroom "アーティファクトエンチャント",0;
	end;
}
