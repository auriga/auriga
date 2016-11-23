//= Auriga Script ==============================================================
// Ragnarok Online Eclage Home Tree Script	by refis
//==============================================================================

ecl_hub01.gat,132,12,3	script	軍参謀#tl01	435,{
	if(getonlinepartymember() != 1) {
		mes "-! 注意 !-";
		mes "該当のクエストは^ff00001人用の";
		mes "メモリアルダンジョン^000000での";
		mes "進行になります。";
		mes "パーティーを生成し、リーダー以外の";
		mes "パーティーメンバーはパーティーから";
		mes "脱退してください。";
		close;
	}
	mes "[シナイム]";
	mes "ここがオーブを照らすための";
	mes "照明が設置された場所です。";
	mes "準備はよろしいですか？";
	next;
	if(select("門を開けてもらう","やめておく") == 2) {
		mes "[シナイム]";
		mes "準備が整ったら";
		mes "また話しかけてください。";
		close;
	}
	if(getonlinepartymember() != 1) {
		mes "[シナイム]";
		mes "門が開くには時間がかかりますので";
		mes "しばらくお待ちください。";
		mes "また、今は警備が強化されています。";
		mes "万が一の場合に備え";
		mes "あらかじめ同意をお願いします。";
		close;
	}
	mdcreate "home_tree";
	mes "[シナイム]";
	mes "中に居る兵士達は";
	mes "警戒心が強くなっています。";
	mes "あまり刺激しないようにしてください。";
	close;
}

ecl_hub01.gat,130,15,0	script	固く閉ざされた門	844,{
	mes "‐広場の天井裏へ繋がる門だ。";
	mes "　オーブを美しく見せるための";
	mes "　照明が設置された場所でもある‐";
	next;
	if(select("入ってみる","やめておく") == 2) {
		mes "‐門の中に入るのは";
		mes "　やめておくことにした‐";
		close;
	}
	if(getonlinepartymember() != 1) {
		mes "-! 注意 !-";
		mes "該当のクエストは^ff00001人用の";
		mes "メモリアルダンジョン^000000での";
		mes "進行になります。";
		mes "パーティーを生成し、リーダー以外の";
		mes "パーティーメンバーはパーティーから";
		mes "脱退してください。";
		close;
	}
	switch(mdenter("home_tree")) {
	case 0:	// エラーなし
		announce strcharinfo(1)+ "パーティーのリーダー" +strcharinfo(0)+ "様がhome_treeに入場します。",0x9,0x00FF99;
		donpcevent getmdnpcname("#HomeTreeEvent") +"::OnStart";
		//warp "1@ecl.gat",60,50;
		end;
	default:	// その他エラー
		mes "[シナイム]";
		mes "門を開くには少し";
		mes "時間がかかりそうです。";
		mes "魔法的処置がいくつも施されていて……";
		mes "無理に入ろうとしないでください。";
		close;
	}
}

1@ecl.gat,51,64,1	script	怪しい存在#HomeTree1	2375,{}
1@ecl.gat,43,67,7	script	怪しい存在#HomeTree2	2375,{}
1@ecl.gat,55,80,3	script	怪しい存在#HomeTree3	2375,{}
1@ecl.gat,60,75,3	script	怪しい存在#HomeTree4	2375,{}

1@ecl.gat,57,65,0	script	#HomeTreeEvent	139,5,5,{
	mes "‐殺風景な広い部屋。";
	mes "　中央にある円形の装置からは";
	mes "　光が漏れている‐";
	next;
	mes "[怪しい存在]";
	mes "グルルルルル……";
	next;
	mes "‐正体不明の連中が";
	mes "　威圧的に迫ってくる。";
	mes "　彼らは一瞬慌てたように見えたが";
	mes "　ビフロストの意志が通じるにも";
	mes "　かかわらず意思の疎通ができない‐";
	next;
	mes "[怪しい存在]";
	mes "グルル……グルァ!!";
	next;
	mes "‐今にも襲ってきそうな様子だ。";
	mes "　彼らとの戦いは避けられない‐";
	close2;
	hideonnpc getmdnpcname("怪しい存在#HomeTree1");
	hideonnpc getmdnpcname("怪しい存在#HomeTree2");
	hideonnpc getmdnpcname("怪しい存在#HomeTree3");
	hideonnpc getmdnpcname("怪しい存在#HomeTree4");
	monster getmdmapname("1@ecl.gat"),51,64,"怪しい存在",2375,1,"#HomeTreeEvent::OnKilled";
	monster getmdmapname("1@ecl.gat"),43,67,"怪しい存在",2375,1,"#HomeTreeEvent::OnKilled";
	monster getmdmapname("1@ecl.gat"),55,80,"怪しい存在",2375,1,"#HomeTreeEvent::OnKilled";
	monster getmdmapname("1@ecl.gat"),60,75,"怪しい存在",2375,1,"#HomeTreeEvent::OnKilled";
	hideonnpc getmdnpcname("#HomeTreeEvent");
	end;
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("シナイム#HomeTree");
	hideonnpc getmdnpcname("怪しい存在#HomeTree5");
	hideonnpc getmdnpcname("怪しい存在#HomeTree6");
	hideonnpc getmdnpcname("怪しい存在#HomeTree7");
	hideonnpc getmdnpcname("怪しい存在#HomeTree8");
	hideonnpc getmdnpcname("#HomeTreeSNDMaster");
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@ecl.gat"),getmdnpcname("#HomeTreeEvent") +"::OnKilled");
	if('@count <= 0) {
		hideoffnpc getmdnpcname("怪しい存在#HomeTree5");
		hideoffnpc getmdnpcname("怪しい存在#HomeTree6");
		hideoffnpc getmdnpcname("怪しい存在#HomeTree7");
		hideoffnpc getmdnpcname("怪しい存在#HomeTree8");
		hideoffnpc getmdnpcname("#HomeTreeSNDMaster");
		donpcevent getmdnpcname("#HomeTreeSND_bc") +"::OnStart";
	}
	end;
}

1@ecl.gat,53,83,0	script	#HomeTreeSNDMaster	139,10,10,{
	mes "‐再び奇妙な存在が現れたが";
	mes "　やはり言葉が通じない。";
	mes "　その中の一匹は周辺を見回し";
	mes "　倒れている仲間をみて";
	mes "　激しく怒っている‐";
	next;
	mes "‐その姿はまるで";
	mes "　モロクの現身のようだ。";
	mes "　オーブを狙っているのは";
	mes "　魔王モロクなのだろうか";
	mes "　それとも偶然の一致なのか‐";
	next;
	mes "[魔王の手下]";
	mes "グルルル……";
	mes "グルァ!";
	next;
	mes "‐戦闘を避けることができない！";
	mes "　奴らは私を殺すつもりのようだ‐";
	close2;
	hideonnpc getmdnpcname("怪しい存在#HomeTree5");
	hideonnpc getmdnpcname("怪しい存在#HomeTree6");
	hideonnpc getmdnpcname("怪しい存在#HomeTree7");
	hideonnpc getmdnpcname("怪しい存在#HomeTree8");
	monster getmdmapname("1@ecl.gat"),42,80,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),48,86,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),59,82,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),56,88,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),39,72,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),42,69,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),47,64,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	monster getmdmapname("1@ecl.gat"),50,60,"魔王の手下",2375,1,getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled";
	hideonnpc getmdnpcname("#HomeTreeSNDMaster");
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@ecl.gat"),getmdnpcname("#HomeTreeSNDMaster") +"::OnKilled");
	if('@count <= 0) {
		announce "シナイム : まるで、私達を待ち伏せていたみたいですね。",0x9,0xffff00;
		hideoffnpc getmdnpcname("シナイム#HomeTree");
	}
	end;
}

1@ecl.gat,53,84,0	script	#HomeTreeSND_bc	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	announce "警告 : 照明室に異常発生、異常発生。",0x9,0xffff00;
	end;
OnTimer4000:
	stopnpctimer;
	announce "怪しい存在 : グルルルル……グルァ!!",0x9,0xffff00;
	end;
}

1@ecl.gat,42,80,5	script	怪しい存在#HomeTree5	2376,{}
1@ecl.gat,48,86,5	script	怪しい存在#HomeTree6	2376,{}
1@ecl.gat,58,82,3	script	怪しい存在#HomeTree7	2376,{}
1@ecl.gat,56,88,3	script	怪しい存在#HomeTree8	2376,{}

1@ecl.gat,58,69,3	script	シナイム#HomeTree	435,{
	mes "[シナイム]";
	mes "これは何ということでしょう！";
	mes "マヨル・ジュンの送った増援の兵士まで";
	mes "一人残らず倒してしまうなんて……。";
	next;
	menu "何……？",-,"私が戦ったのは怪物だ！",-;
	mes "[シナイム]";
	mes "ふふふ……";
	mes "気分はいかがですか？";
	mes "あなたの役目はここまでです。";
	next;
	mes "[シナイム]";
	mes "あなたは兵士を襲った裏切り者として";
	mes "罪に問われるでしょう。";
	mes "それではさようなら！";
	misceffect 55;
	next;
	mes "["+strcharinfo(0)+"]";
	mes "そんな……！";
	percentheal -99,0;
	misceffect 90,"";
	sc_start3 SC_BLIND,0,0,0,0,60000,10;
	close2;
	warp getmdmapname("1@ecl.gat"),146,95;
	end;
}

1@ecl.gat,148,97,3	script	エイヴァント	618,{
	cutin "avant01",1;
	mes "[エイヴァント]";
	mes "おや、どなたかな……？";
	mes "　";
	mes "君は息子の友人ではないか！";
	mes "こんなところで会うなんて";
	mes "面白い縁もあるものだな。";
	sc_end SC_BLIND;
	next;
	mes "[エイヴァント]";
	mes "何があった。";
	mes "先ほど微かな魔力の響きがあったが";
	mes "その直後、君がここへ放り込まれた。";
	next;
	if(select("すべてあなたのせいだ！","シナイムが……") == 1) {
		mes "[エイヴァント]";
		mes "落ち着きなさい。";
		mes "何を言いたいのかわからない。";
		mes "六何の原則、起承転結という言葉を";
		mes "知っているか？";
		next;
	}
	mes "[エイヴァント]";
	mes "ほう……。";
	mes "シナイムがオーブを狙った。";
	mes "これは……？";
	next;
	mes "[エイヴァント]";
	mes "ふふふふ……ははははあははは";
	mes "これはこれは、私がやられた？";
	mes "この私、エイヴァントが？";
	mes "ははは！";
	cutin "avant02",1;
	next;
	menu "どういうこと？",-;
	mes "[エイヴァント]";
	mes "オーブの魔力についての研究は";
	mes "もちろん自発的に行っていた。";
	mes "しかし、シナイムは本当に粘り強く";
	mes "彼女の望む道へと";
	mes "私を導いていったよ。";
	cutin "avant01",1;
	next;
	mes "[エイヴァント]";
	mes "最初はオーブが美しいからと";
	mes "軽く研究を始めた。";
	next;
	mes "[エイヴァント]";
	mes "魔力はどれだけ集まっているのか。";
	mes "私たちが魔力の恵みを受けるのは";
	mes "どんな原理だろう？";
	mes "知りたくないか？";
	mes "と言いながら……。";
	next;
	mes "[エイヴァント]";
	mes "ラフィネならまるで";
	mes "空気や水と同じように";
	mes "当たり前に享受している";
	mes "オーブからの魔力を";
	mes "根源から考える者は";
	mes "その者が初めてだったよ。";
	next;
	mes "[エイヴァント]";
	mes "そう……シナイム。";
	mes "彼女は私の好奇心を刺激させた。";
	next;
	mes "[エイヴァント]";
	mes "空気と水を意識しなかった者に";
	mes "刺激を与え続けて認識させる。";
	mes "そして探求させる！";
	mes "面白いとは思わないかね？";
	cutin "avant02",1;
	next;
	mes "[エイヴァント]";
	mes "は……ははは……";
	mes "……奴に利用されたことを";
	mes "悟ったことも悔しいが";
	mes "一族に大きな罪を作ってしまった。";
	mes "とんだ傀儡だよ私は。";
	mes "実に腹立たしい！";
	next;
	menu "あなたに良心があったの？",-;
	mes "[エイヴァント]";
	mes "君は私のことを何だと思っているんだ？";
	mes "まあ、息子から私の話を聞いているなら";
	mes "無理もない話か。";
	cutin "avant01",1;
	next;
	mes "[エイヴァント]";
	mes "……ふん。";
	mes "面白くない。";
	mes "君に持っていた興味も消えた。";
	next;
	mes "[エイヴァント]";
	mes "……";
	mes "客が来たようだな。";
	next;
	cutin "minuel01",4;
	mes "[ミニュエル]";
	mes strcharinfo(0)+ "様。";
	mes "照明室で行われた暴動の犯人と目され";
	mes "ここで留置されていましたが、";
	mes "あなたの無罪を証明する人々が";
	mes "現れました。";
	next;
	mes "[ミニュエル]";
	mes "どうなるかはわかりませんが";
	mes "私もあなたが潔白だと信じています。";
	mes "一応、傷がまだひどいようですので";
	mes "治療室に移しますね。";
	next;
	mes "[ミニュエル]";
	mes "大したことはないはずです。";
	mes "……たぶん。";
	mes "行きましょう。ご案内いたします。";
	close2;
	cutin "minuel01",255;
	warp getmdmapname("1@ecl.gat"),146,24;
	end;
}

1@ecl.gat,148,29,3	script	ロキ	512,{
	mes "[ロキ]";
	mes "隣にいる彼が君に言いたいことが";
	mes "あるようだ。";
	mes "まず、彼に説明してくれないか。";
	close;
}

1@ecl.gat,147,30,3	script	ニーズヘッグ	510,{
	mes "[ニーズヘッグ]";
	mes "まずはヒシエさんと話すのが";
	mes "先ではありませんか？";
	close;
}

1@ecl.gat,144,27,5	script	ヒシエ	623,{
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "傷は大丈夫か？";
	mes "あの時、何があったのか";
	mes "説明できるか？";
	next;
	menu "モンスターと戦った",-;
	cutin "hisie03",0;
	npcskillsupport 28,1672;
	heal 1672,0;
	mes "[ヒシエ]";
	mes "モンスター？　モロクの手下？";
	mes "お前が戦ったのは";
	mes "ラフィネの兵士だ！";
	mes "一体何があったんだ？";
	next;
	cutin "hisie01",255;
	mes "[ロキ]";
	mes strcharinfo(0)+ "は";
	mes "正常な状態ではなかったんだろう。";
	mes "これが天井裏に落ちていた。";
	mes "おそらくシナイムの仕業だ。";
	next;
	mes "‐ロキの手のひらの上には";
	mes "　非常に小さい細長い棘が";
	mes "　干からびていた‐";
	next;
	cutin "hisie03",0;
	npcskillsupport 28,1672;
	heal 1672,0;
	mes "[ヒシエ]";
	mes "軍参謀のシナイム？";
	mes "この棘とシナイムに何の関係が";
	mes "あるんですか？";
	next;
	menu "そういえば……",-;
	cutin "hisie01",255;
	mes "["+strcharinfo(0)+"]";
	mes "ここに来る前、シナイムが出す手を";
	mes "握ったときに何か刺さった感じがした。";
	mes "気のせいだと思っていたけど";
	mes "まさか、その時に？";
	next;
	mes "[ニーズヘッグ]";
	mes "たぶん、そうでしょう。";
	mes "この棘があなたの理性を";
	mes "曇らせていたはずです。";
	mes "そしてあなたはラフィネの兵士を";
	mes "モンスターと錯覚させられた……";
	mes "奸悪な策略を張る人ですね。";
	next;
	cutin "hisie03",0;
	npcskillsupport 28,1672;
	heal 1672,0;
	mes "[ヒシエ]";
	mes "つまり、"+strcharinfo(0)+"は";
	mes "シナイムに謀られていたってことか？";
	mes "シナイムは古参のラフィネだ！";
	mes "そんなことするわけが……。";
	next;
	cutin "hisie01",255;
	mes "[ロキ]";
	mes "シナイムはモロクの手下の一人だ。";
	mes "本人も気づかないうちに";
	mes "支配されていたんだろう。";
	next;
	mes "[ロキ]";
	mes "奴は自分の身体の一部を利用して";
	mes "相手の肉体を直接操作したり";
	mes "精神に干渉する能力を持っている。";
	mes "今回はそれを利用したのだろう。";
	next;
	if(checkquest(201370)) {	// 紫竜クエストメイン
		mes "[ロキ]";
		mes "とにかくこの事件の犯人は";
		mes "こいつではない。";
		mes "俺が保証する。";
		next;
		mes "[ニーズヘッグ]";
		mes "そうですね。";
		mes strcharinfo(0)+ "様からは";
		mes "悪意を感じません。";
		mes "以前、私を救って下さった方と";
		mes "同じ雰囲気をまとっています。";
		next;
		mes "[ニーズヘッグ]";
		mes "私もイグドラシルの守護者の";
		mes "名にかけて保証します。";
		mes strcharinfo(0)+ "様は";
		mes "決してそのような方ではありません。";
	}
	else if(checkquest(201410)) {	// ノローキアルート
		mes "[ロキ]";
		mes "とにかくこの事件の犯人は";
		mes "こいつではない。";
		mes "俺が保証する。";
		next;
		mes "[ニーズヘッグ]";
		mes "私もイグドラシルの守護者の";
		mes "名にかけて保証します。";
		mes strcharinfo(0)+ "様は";
		mes "決してそのような方ではありません。";
	}
	else {	// 未クリア?
		mes "[ロキ]";
		mes "こいつはシナイムの";
		mes "罠に嵌められていただけで、";
		mes "自分の意志で事件を";
		mes "起こしたんじゃない。";
		next;
		mes "[ニーズヘッグ]";
		mes "そうですね。";
		mes strcharinfo(0)+ "様からは";
		mes "悪意を感じません。";
		mes "以前、私を救って下さった方と";
		mes "同じ雰囲気をまとっています。";
		next;
		mes "[ニーズヘッグ]";
		mes "イグドラシルの守護者の";
		mes "名にかけて保証します。";
		mes strcharinfo(0)+ "様は";
		mes "そのような方ではありません。";
	}
	next;
	cutin "hisie02",0;
	mes "[ヒシエ]";
	mes "はぁ……";
	mes "しかし、話がずいぶんと";
	mes "大きくなってしまったな。";
	mes "こんなことになるなんて。";
	next;
	menu "オーブは？",-;
	npcskillsupport 28,1672;
	heal 1672,0;
	mes "[ヒシエ]";
	mes "内核が奪われた。";
	mes "だが、オーブの内核が奪われた事は";
	mes "まだ誰も知らないんだ。";
	mes "この場にカルが居ないのも";
	mes "そのためだ……。";
	next;
	mes "[ヒシエ]";
	mes "オーブもオーブだが";
	mes "君のところには大勢の兵士が";
	mes "送られた。";
	mes "幸い死亡者はいないが";
	mes "多くの兵士が重症を負っている。";
	mes "あまり好ましい状況ではないな。";
	next;
	cutin "hisie01",255;
	mes "[ロキ]";
	mes "誰かが責任を負う事になるだろう。";
	mes "そしておそらくそれは";
	mes strcharinfo(0);
	mes "君になるだろう。";
	next;
	cutin "hisie02",0;
	npcskillsupport 28,1672;
	heal 1672,0;
	mes "[ヒシエ]";
	mes "……オーブに対する疑いは";
	mes "二人が解決してくれたが";
	mes "カルもあなたも責任を免れは";
	mes "しないだろう。";
	mes "そして、シナイムを";
	mes "捕まえなければならない。";
	next;
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "適度に回復したら移動するぞ。";
	mes "カルが待っているからな。";
	mes "二人はどうする？";
	next;
	cutin "hisie01",255;
	mes "[ロキ]";
	mes "俺達に気を使うな。";
	mes "俺達の目的は魔王モロクだ。";
	mes "こちらで手がかりを見つけただけでも";
	mes "十分だ。";
	next;
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "助けてくれてありがとう。";
	mes "それでは先に行ってみるよ。";
	mes "さあ、行こう。";
	mes strcharinfo(0)+ "。";
	set ECL_3QUE,30;
	chgquest 7450,7451;
	close2;
	cutin "hisie01",255;
	warp "ecl_in03.gat",57,76;
	end;
}
