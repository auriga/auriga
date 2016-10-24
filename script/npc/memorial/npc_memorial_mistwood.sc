//= Auriga Script ==============================================================
// Ragnarok Online Mistwood Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
bif_fild01.gat,158,340,5	script	霧の森の監視兵	447,{
	mes "[霧の森の監視兵]";
	mes "この先は、入る者を惑わす";
	mes "^0000FF霧の森^000000。";
	mes "非常に危険な場所です。";
	mes "私はスプレンディッドの住民が";
	mes "ここに迷いこまないよう";
	mes "見張っています。";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[霧の森の監視兵]";
		mes "パーティーのリーダーは";
		mes "いらっしゃいますか？";
		mes "リーダーが手続きをしないと";
		mes "森に入ることを許可できません。";
		if(checkquest(7211) & 0x2) {
			next;
			mes "[霧の森の監視兵]";
			mes "そういえば、あなたは以前";
			mes "霧の森に入りましたね。";
			next;
			mes "[霧の森の監視兵]";
			mes "……";
			mes "どうやら霧の森が";
			mes "静まったようです。";
			mes "これであなたは再び森に";
			mes "入れるようになりました。";
			delquest 7211;
		}
		close;
	}
	if(checkquest(7211)) {
		if(checkquest(7211) & 0x2) {
			mes "[霧の森の監視兵]";
			mes "この先は、入る者を惑わす";
			mes "^0000FF霧の森^000000。";
			mes "非常に危険な場所です。";
			mes "私はスプレンディッドの住民が";
			mes "ここに迷いこまないよう";
			mes "見張っています。";
			next;
			mes "[霧の森の監視兵]";
			mes "……";
			mes "どうやら霧の森が";
			mes "静まったようです。";
			mes "これであなたは再び森に";
			mes "入れるようになりました。";
			delquest 7211;
			close;
		}
		mes "[霧の森の監視兵]";
		mes "霧の森が騒いでいます。";
		mes "まだあなたを拒否しているようですね。";
		mes "もう少し時間をおかないと";
		mes "森に入れないでしょう。";
		close;
	}
	mes "[霧の森の監視兵]";
	mes "あなたは人間の冒険者ですね。";
	mes "もし森に入りたいのであれば";
	mes "止めはしません。";
	mes "私が守るのはラフィネ族のみで";
	mes "人間を守る義務はありませんから。";
	next;
	if(!getcharid(1)) {
		mes "[霧の森の監視兵]";
		mes "この森に入るなら、";
		mes "森の幻惑を避けるため";
		mes "^FF0000パーティー^000000を組んでください。";
		mes "そうしないと入ることを";
		mes "許可できません。";
		next;
		mes "[霧の森の監視兵]";
		mes "パーティーを組みましたら、";
		mes "必ずパーティーのリーダーが";
		mes "私と入場手続きをするように";
		mes "してください。";
		mes "誰が入ったか管理したいのです。";
		close;
	}
	mes "[霧の森の監視兵]";
	mes "この森に入るためには、";
	mes "パーティーを組む必要がありますが、";
	mes "あなたは既にパーティーを";
	mes "組んでいますね。";
	mes "森に入る許可をあたえましょう。";
	next;
	if(select("^0000FF霧の森（mistwood）^000000に入りたい","今はやめておく") == 2) {
		mes "[霧の森の監視兵]";
		mes "それがいいでしょう。";
		mes "あえて危険をおかす";
		mes "必要はないですからね。";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[霧の森の監視兵]";
		mes "あなたは私と話している間に";
		mes "パーティーリーダーで";
		mes "なくなってしまったのですか？";
		mes "リーダーでなくては";
		mes "手続きをすることはできません。";
		close;
	}
	mdcreate "mistwood";
	mes "[霧の森の監視兵]";
	mes "この森に入りたいのですね。";
	mes "わかりました。";
	mes "では確認しましょう。";
	next;
	mes "[霧の森の監視兵]";
	mes "パーティ名が";
	mes getpartyname(getcharid(1))+ "。";
	mes "リーダーの名前が";
	mes getpartyleader(getcharid(1))+ "。";
	next;
	mes "[霧の森の監視兵]";
	mes "森もあなたを拒んでいない";
	mes "ようですし、問題はないですね。";
	mes "森に入る許可をあげましょう。";
	next;
	mes "[霧の森の監視兵]";
	mes "この先に大きな丸太の";
	mes "トンネルがあります。";
	mes "そこが森への入り口です。";
	mes "それでは";
	mes "気をつけて行ってください。";
	close;
}

//============================================================
// 転送NPC
//------------------------------------------------------------
bif_fild01.gat,161,355,0	script	丸太のトンネル	844,{
	mes "‐丸太のトンネルを覗くと";
	mes "　奥にうっすらと霧がかかった";
	mes "　森が見える‐";
	next;
	if(select("先に進む","今はやめておく") == 2) {
		mes "‐今はやめておこう‐";
		close;
	}
	mes "‐あなたは先に進むことにした‐";
	close2;
	switch(mdenter("mistwood")) {
	case 0:	// エラーなし
		setquest 7211;
		announce strcharinfo(1)+ "パーティーの" +strcharinfo(0)+ "が霧の森に入場します。",0x9,0x00ff99;
		end;
	case 1:	// パーティー未加入
		mes "[霧の森の監視兵]";
		mes "霧の森に入れるのは";
		mes "パーティーメンバーのみです。";
		close;
	case 2:	// ダンジョン未作成
		mes "[霧の森の監視兵]";
		mes "パーティーリーダーが";
		mes "まだ手続きを終えてないか、";
		mes "霧の森への進入準備中ですので、";
		mes "今はまだ霧の森に入れません。";
		mes "もう少しお待ちください。";
		close;
	default:	// その他エラー
		close;
	}
}

//============================================================
// 霧の森NPC
//------------------------------------------------------------
1@mist.gat,0,0,0	script	MistwoodControl	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;

//	hideonnpc getmdnpcname("ロキ#mist");
//	hideonnpc getmdnpcname("倒れている女性#mist");
	hideonnpc getmdnpcname("a25_a18-1");
	hideonnpc getmdnpcname("a27-2_af1-2");
	hideonnpc getmdnpcname("a15-2_a4-1");
	hideonnpc getmdnpcname("a4-2_a11");
	hideonnpc getmdnpcname("b4-2_b2");
	hideonnpc getmdnpcname("b7_bf1-2");
	hideonnpc getmdnpcname("b31_b16");
	hideonnpc getmdnpcname("b27-3_bN-1");
	hideonnpc getmdnpcname("b6-1_b33");
	hideonnpc getmdnpcname("b5_b14");
	hideonnpc getmdnpcname("c1_c13-1");
	hideonnpc getmdnpcname("c13-3_c4");
	hideonnpc getmdnpcname("c19_c4");
	hideonnpc getmdnpcname("to_bif02");

	set '@map$,getmdmapname("1@mist.gat");
	areamonster '@map$,0,0,0,0,"ミミン",2137,15,getmdnpcname("MistwoodControl")+ "::OnKilled1";
	areamonster '@map$,0,0,0,0,"ポムスパイダー",2132,25,getmdnpcname("MistwoodControl")+ "::OnKilled2";
	areamonster '@map$,0,0,0,0,"アングラマンティス",2133,25,getmdnpcname("MistwoodControl")+ "::OnKilled3";
	areamonster '@map$,0,0,0,0,"パルス",2134,15,getmdnpcname("MistwoodControl")+ "::OnKilled4";
	areamonster '@map$,0,0,0,0,"リトルファートゥム",2136,15,getmdnpcname("MistwoodControl")+ "::OnKilled5";
	areamonster '@map$,0,0,0,0,"守護者の記憶の破片",2138,5;
	areamonster '@map$,0,0,0,0,"守護者の記憶の破片",2140,5;
	areamonster '@map$,0,0,0,0,"守護者の記憶の破片",2142,5;

	monster '@map$,249,120,"ちびっこトーム",2136,1,getmdnpcname("GardenTree#1")+ "::OnKilled";
	monster '@map$,200,64,"木登りトームバー",2136,1,getmdnpcname("GardenTree#2")+ "::OnKilled";
	monster '@map$,154,184,"お疲れレミ",2137,1,getmdnpcname("GardenTree#3")+"::OnKilled";
	monster '@map$,101,107,"うたた寝レム",2136,1,getmdnpcname("GardenTree#4")+"::OnKilled";
	monster '@map$,227,178,"怖がりロン",2134,1,getmdnpcname("GardenTree#5")+"::OnKilled";
	monster '@map$,304,237,"杞憂のローバー",2134,1,getmdnpcname("GardenTree#6")+"::OnKilled";
	monster '@map$,239,253,"幸せなナモ",2133,1,getmdnpcname("GardenTree#7")+"::OnKilled";
	monster '@map$,89,173,"勇敢なナモン",2134,1,getmdnpcname("GardenTree#8")+"::OnKilled";
	monster '@map$,143,265,"憂鬱なニョロン",2137,1,getmdnpcname("GardenTree#9")+"::OnKilled";
	monster '@map$,209,200,"優越ゲミ",2132,1,getmdnpcname("GardenTree#10")+"::OnKilled";
	monster '@map$,264,291,"暴虐のティト",2133,1,getmdnpcname("GardenTree#11")+"::OnKilled";
	monster '@map$,309,165,"働き者プムバー",2134,1,getmdnpcname("GardenTree#12")+"::OnKilled";
	monster '@map$,277,343,"卓越したテテ",2136,1,getmdnpcname("GardenTree#13")+"::OnKilled";

	monster '@map$,318,137,"ちびっこトーム",2136,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,321,137,"木登りトームバー",2136,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,324,137,"お疲れレミ",2137,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,319,135,"うたた寝レム",2136,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,323,135,"怖がりロン",2134,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,320,133,"杞憂のローバー",2134,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,323,133,"幸せなナモ",2133,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,317,132,"勇敢なナモン",2134,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,326,132,"憂鬱なニョロン",2137,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,317,129,"優越ゲミ",2132,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,320,129,"暴虐のティト",2133,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,324,129,"働き者プムバー",2134,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	monster '@map$,327,129,"卓越したテテ",2136,1,getmdnpcname("GardenTree#14")+"::OnKilled";
	end;
OnKilled1:
	areamonster getmdmapname("1@mist.gat"),0,0,0,0,"ミミン",2137,1,getmdnpcname("MistwoodControl")+ "::OnKilled1";
	end;
OnKilled2:
	areamonster getmdmapname("1@mist.gat"),0,0,0,0,"ポムスパイダー",2132,1,getmdnpcname("MistwoodControl")+ "::OnKilled2";
	end;
OnKilled3:
	areamonster getmdmapname("1@mist.gat"),0,0,0,0,"アングラマンティス",2133,1,getmdnpcname("MistwoodControl")+ "::OnKilled3";
	end;
OnKilled4:
	areamonster getmdmapname("1@mist.gat"),0,0,0,0,"パルス",2134,1,getmdnpcname("MistwoodControl")+ "::OnKilled4";
	end;
OnKilled5:
	areamonster getmdmapname("1@mist.gat"),0,0,0,0,"リトルファートゥム",2136,1,getmdnpcname("MistwoodControl")+ "::OnKilled5";
	end;
}

1@mist.gat,251,121,3	script	ちびっこトームの庭園::Mistwood#1	858,{}
1@mist.gat,247,123,0	script	ちびっこトームの庭木::GardenTree#1	527,{
	if('flag <= 0) {
		announce "ちびっこトーム : ん？私の庭木に嫌がらせをするつもり!?",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　ちびっこトームの力で";
		mes "　護られているようだ。";
		mes "　^FF0000ちびっこトームを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐ちびっこトームを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : ちびっこトームのかんぬきが外れた！トームバー、気をつけて！トームバー、気をつけて！",0x9,0xccffcc;
	donpcevent getmdnpcname("a25_a18-1")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#1");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : ちびっこトームが倒された……「ちびっこトームの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,226,95,3	script	木登りトームバーの庭::Mistwood#2	858,{}
1@mist.gat,225,98,0	script	木登りトームバーの庭木::GardenTree#2	527,{
	if('flag <= 0) {
		announce "木登りトームバー : 私の庭木に手を出すな！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　木登りトームバーの力で";
		mes "　護られているようだ。";
		mes "　^FF0000木登りトームバーを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐木登りトームバーを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : トームバーの庭木、トームバーと消えた！レミ気をつけて、レミ！",0x9,0xccffcc;
	donpcevent getmdnpcname("a27-2_af1-2")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#2");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 木登りトームバーが倒された……「木登りトームバーの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,157,183,3	script	お疲れレミの庭園::Mistwood#3	858,{}
1@mist.gat,159,184,0	script	お疲れレミの庭木::GardenTree#3	527,{
	if('flag <= 0) {
		announce "お疲れレミ : 私の庭木に近づかないで！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　お疲れレミの力で";
		mes "　護られているようだ。";
		mes "　^FF0000お疲れレミを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐お疲れレミを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : レミ、レミの庭木も倒れたの？次はレムの番？かわいそうなレム！",0x9,0xccffcc;
	donpcevent getmdnpcname("a15-2_a4-1")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#3");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : お疲れレミが倒された……「お疲れレミの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,58,39,3	script	うたた寝レムの庭::Mistwood#4	858,{}
1@mist.gat,61,39,0	script	うたた寝レムの庭木::GardenTree#4	527,{
	if('flag <= 0) {
		announce "うたた寝レム : ああっ！僕の庭木に触らないでよ!!",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　うたた寝レムの力で";
		mes "　護られているようだ。";
		mes "　^FF0000うたた寝レムを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐うたた寝レムを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "うたた寝レム : あ～あ……レムは寝る。もう寝る。永遠に寝るわ！",0x9,0xccffcc;
	donpcevent getmdnpcname("a4-2_a11")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#4");
	initnpctimer;
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : うたた寝レムが倒された……「うたた寝レムの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
OnTimer10000:
	announce "森の囁き : トーム、トームバー、レミ、レムの庭木が全て倒れちゃったの？",0x9,0xccffcc;
	end;
OnTimer15000:
	announce "森の囁き : 大変だ、大変だ、それは大変だ！",0x9,0xccffcc;
	end;
OnTimer20000:
	announce "森の囁き : 誰かは二番目の深い森まで来てしまったよ！深い森の庭師達はしっかりしてね！",0x9,0xccffcc;
	stopnpctimer;
	end;
}

1@mist.gat,227,179,3	script	怖がりロンの庭園::Mistwood#5	858,{}
1@mist.gat,230,179,0	script	怖がりロンの庭木::GardenTree#5	527,{
	if('flag <= 0) {
		announce "怖がりロン : これ以上、先には行かせないよ！君は僕の庭木を壊せない！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　怖がりロンの力で";
		mes "　護られているようだ。";
		mes "　^FF0000怖がりロンを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐怖がりロンを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "怖がりロン : 僕はいない！二番目の森の怖がりロンをもう探さないで!!",0x9,0xccffcc;
	donpcevent getmdnpcname("b4-2_b2")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#5");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 怖がりロンが倒された……「怖がりロンの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,288,226,3	script	杞憂のローバーの庭園::Mistwood#6	858,{}
1@mist.gat,285,225,0	script	杞憂のローバーの庭木::GardenTree#6	527,{
	if('flag <= 0) {
		announce "杞憂のローバー : ロンを倒すなんて信じられない！僕も倒すの!?",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　杞憂のローバーの力で";
		mes "　護られているようだ。";
		mes "　^FF0000怖がりロンを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐杞憂のローバーを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : ロン、杞憂のローバーの庭園も突破されちゃった！無理やり森を暴くのは誰？誰？",0x9,0xccffcc;
	donpcevent getmdnpcname("b7_bf1-2")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#6");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 杞憂のローバーが倒された……「杞憂のローバーの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,159,318,3	script	幸せなナモの庭園::Mistwood#7	858,{}
1@mist.gat,161,316,0	script	幸せなナモの庭木::GardenTree#7	527,{
	if('flag <= 0) {
		announce "幸せなナモ : 私の大事な庭木に手を出そうとしてるのは誰!?",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　幸せなナモの力で";
		mes "　護られているようだ。";
		mes "　^FF0000幸せなナモを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐幸せなナモを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : ナモの庭木も倒れた！ナモも倒れてしまった！ナモン、ナモンは勇敢だから大丈夫だよね？",0x9,0xccffcc;
	donpcevent getmdnpcname("b31_b16")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#7");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 幸せなナモが倒された……「幸せなナモの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,205,300,3	script	勇敢なナモンの庭園::Mistwood#8	858,{}
1@mist.gat,204,299,0	script	勇敢なナモンの庭木::GardenTree#8	527,{
	if('flag <= 0) {
		announce "勇敢なナモン : 俺の庭木に手出しさせないぜ！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　勇敢なナモンの力で";
		mes "　護られているようだ。";
		mes "　^FF0000勇敢なナモンを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐勇敢なナモンを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : 勇敢なナモンが勇敢ではない最後を！さあ、誰が仇討ちする!?",0x9,0xccffcc;
	donpcevent getmdnpcname("b27-3_bN-1")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#8");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 勇敢なナモンが倒された……「勇敢なナモンの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,219,232,3	script	憂鬱なニョロンの庭園::Mistwood#9	858,{}
1@mist.gat,221,236,0	script	憂鬱なニョロンの庭木::GardenTree#9	527,{
	if('flag <= 0) {
		announce "憂鬱なニョロン : ゆううつだぁ……ゆううつだなぁ……ぼくの庭に来ないでよ……",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　憂鬱なニョロンの力で";
		mes "　護られているようだ。";
		mes "　^FF0000憂鬱なニョロンを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐憂鬱なニョロンを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : ニョロンが倒れた、ゆううつに！どうする？どうしよう！",0x9,0xccffcc;
	donpcevent getmdnpcname("b6-1_b33")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#9");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 憂鬱なニョロンが倒された……「憂鬱なニョロンの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,206,202,3	script	優越ゲミの庭園::Mistwood#10	858,{}
1@mist.gat,206,200,0	script	優越ゲミの庭木::GardenTree#10	527,{
	if('flag <= 0) {
		announce "優越ゲミ : 私の大切な庭から出て行きなさい！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　優越ゲミの力で";
		mes "　護られているようだ。";
		mes "　^FF0000優越ゲミを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐優越ゲミを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : これで二番目の深い森も終わり。庭師が次々に倒れていくよ！",0x9,0xccffcc;
	donpcevent getmdnpcname("b5_b14")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#10");
	initnpctimer;
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 優越ゲミが倒された……「優越ゲミの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
OnTimer5000:
	announce "森の囁き : 道がつながろうとしてる、道が、かたく閉ざされていた森が開かれちゃった！",0x9,0xccffcc;
	end;
OnTimer9000:
	announce "森の囁き : 誰かは次の森まで暴こうとしてる、暴虐のティト、プンバー！誰かが向かってる！",0x9,0xccffcc;
	end;
OnTimer13000:
	announce "森の囁き : くるくる回って到着する場所に、くるくる回って会ってたみんなが",0x9,0xccffcc;
	end;
OnTimer17000:
	announce "森の囁き : 全ての庭師が光るハサミを持って、誰かを待っている～！",0x9,0xccffcc;
	stopnpctimer;
	end;
}

1@mist.gat,96,288,3	script	暴虐のティトの庭園::Mistwood#11	858,{}
1@mist.gat,95,287,0	script	暴虐のティトの庭木::GardenTree#11	527,{
	if('flag <= 0) {
		announce "暴虐のティト : 私の庭にまで来るなんて！なんて奴！なんて奴だ！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　暴虐のティトの力で";
		mes "　護られているようだ。";
		mes "　^FF0000暴虐のティトを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐暴虐のティトを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : う……うわぁぁ!!暴虐のティト！暴虐のティトはもう終わりだ！もう終わっちゃったよ！うあぁぁ!!",0x9,0xccffcc;
	donpcevent getmdnpcname("c1_c13-1")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#11");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 暴虐のティトが倒された……「暴虐のティトの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,326,325,3	script	働き者プムバーの庭園::Mistwood#12	858,{}
1@mist.gat,324,325,0	script	働き者プムバーの庭木::GardenTree#12	527,{
	if('flag <= 0) {
		announce "働き者プムバー : 僕が毎日毎日大切に育ててる庭に近づくな！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　働き者プムバーの力で";
		mes "　護られているようだ。";
		mes "　^FF0000働き者プムバーを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐働き者プムバーを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : 働き者プムバーがやられた！テテは遊ばないで仕事して！テテは仕事しなさい！",0x9,0xccffcc;
	donpcevent getmdnpcname("c13-3_c4")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#12");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 働き者プムバーが倒された……「働き者プムバーの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,278,345,3	script	卓越したテテの庭園::Mistwood#13	858,{}
1@mist.gat,280,344,0	script	卓越したテテの庭木::GardenTree#13	527,{
	if('flag <= 0) {
		announce "卓越したテテ : ここまで来たら、ちゃんと仕事しなきゃね！君はここで終わりだよ！",0x9,0xccffcc;
		mes "‐この庭木を倒せば先に進めそうだが、";
		mes "　卓越したテテの力で";
		mes "　護られているようだ。";
		mes "　^FF0000卓越したテテを倒して、";
		mes "　この庭木を破壊しよう^000000‐";
		close;
	}
	mes "‐卓越したテテを倒したので";
	mes "　庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : 彼らは強い、強いよ。これからどうしよう？残っている庭師はいないのかな？いないのかな？",0x9,0xccffcc;
	donpcevent getmdnpcname("c19_c4")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#13");
	close;
OnKilled:
	set 'flag,1;
	announce "森の囁き : 卓越したテテが倒された……「卓越したテテの庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,345,186,0	script	全ての庭師の庭木::GardenTree#14	527,{
	if('flag < 13) {
		announce "庭師たち : 君を倒すため、再び13人の庭師が大集合！みんなの力で君を倒す！僕たちのいる場所までおいで！",0x9,0xccffcc;
		mes "‐これが最後の庭木のようだ。";
		mes "　13人の庭師の力で護られている。";
		mes "　どうやら、あなたを倒すために";
		mes "　庭師たちが再び現れ、";
		mes "　結集したようだ‐";
		next;
		mes "‐^FF000013人の庭師全てを倒して、";
		mes "　この庭木を破壊しよう。^000000";
		mes "　";
		mes "　残りの庭師：^FF0000" +(13 - 'flag)+ "人^000000‐";
		close;
	}
	mes "‐庭木を護る者はいない。";
	mes "　この庭木を破壊すれば、";
	mes "　先に進めそうだ‐";
	next;
	if(select("庭木を破壊する","やめる") == 2) {
		mes "‐庭木を破壊するのをやめた‐";
		close;
	}
	mes "‐迷宮の道をふさいでいた";
	mes "　庭木を破壊した。";
	mes "　これで先に進むことができる‐";
	announce "森の囁き : 森は君を忘れない！全ての庭師のハサミと庭を壊した君を忘れないよ！",0x9,0xccffcc;
	donpcevent getmdnpcname("to_bif02")+"::OnStart";
	hideonnpc getmdnpcname("GardenTree#14");
	close;
OnKilled:
	set 'flag,'flag + 1;
	if('flag >= 13)
		announce "森の囁き : 全ての庭師が倒された……「全ての庭師の庭木」を護る者がいない……壊されちゃう……",0x9,0xFFFF00;
	end;
}

1@mist.gat,73,290,0		script	不思議な花#1	844,{
	hideonnpc;
	getitem 12561,1;
	end;
}

1@mist.gat,69,295,0		duplicate(不思議な花#1)	不思議な花#2	844
1@mist.gat,62,291,0		duplicate(不思議な花#1)	不思議な花#3	844
1@mist.gat,54,293,0		duplicate(不思議な花#1)	不思議な花#4	844
1@mist.gat,48,286,0		duplicate(不思議な花#1)	不思議な花#5	844
1@mist.gat,54,277,0		duplicate(不思議な花#1)	不思議な花#6	844
1@mist.gat,52,270,0		duplicate(不思議な花#1)	不思議な花#7	844
1@mist.gat,62,268,0		duplicate(不思議な花#1)	不思議な花#8	844
1@mist.gat,72,271,0		duplicate(不思議な花#1)	不思議な花#9	844
1@mist.gat,72,276,0		duplicate(不思議な花#1)	不思議な花#10	844
1@mist.gat,118,194,0	duplicate(不思議な花#1)	不思議な花#11	844
1@mist.gat,122,204,0	duplicate(不思議な花#1)	不思議な花#12	844
1@mist.gat,137,209,0	duplicate(不思議な花#1)	不思議な花#13	844
1@mist.gat,144,203,0	duplicate(不思議な花#1)	不思議な花#14	844
1@mist.gat,146,186,0	duplicate(不思議な花#1)	不思議な花#15	844
1@mist.gat,142,182,0	duplicate(不思議な花#1)	不思議な花#16	844
1@mist.gat,132,179,0	duplicate(不思議な花#1)	不思議な花#17	844
1@mist.gat,123,184,0	duplicate(不思議な花#1)	不思議な花#18	844
1@mist.gat,194,118,0	duplicate(不思議な花#1)	不思議な花#19	844
1@mist.gat,188,109,0	duplicate(不思議な花#1)	不思議な花#20	844
1@mist.gat,193,94,0		duplicate(不思議な花#1)	不思議な花#21	844
1@mist.gat,205,92,0		duplicate(不思議な花#1)	不思議な花#22	844
1@mist.gat,213,96,0		duplicate(不思議な花#1)	不思議な花#23	844
1@mist.gat,216,103,0	duplicate(不思議な花#1)	不思議な花#24	844
1@mist.gat,212,116,0	duplicate(不思議な花#1)	不思議な花#25	844
1@mist.gat,207,120,0	duplicate(不思議な花#1)	不思議な花#26	844
1@mist.gat,169,310,0	duplicate(不思議な花#1)	不思議な花#27	844
1@mist.gat,172,296,0	duplicate(不思議な花#1)	不思議な花#28	844
1@mist.gat,191,301,0	duplicate(不思議な花#1)	不思議な花#30	844
1@mist.gat,195,301,0	duplicate(不思議な花#1)	不思議な花#31	844
1@mist.gat,192,316,0	duplicate(不思議な花#1)	不思議な花#32	844
1@mist.gat,187,320,0	duplicate(不思議な花#1)	不思議な花#33	844
1@mist.gat,174,318,0	duplicate(不思議な花#1)	不思議な花#34	844
1@mist.gat,308,136,0	duplicate(不思議な花#1)	不思議な花#35	844
1@mist.gat,314,122,0	duplicate(不思議な花#1)	不思議な花#36	844
1@mist.gat,321,118,0	duplicate(不思議な花#1)	不思議な花#37	844
1@mist.gat,331,123,0	duplicate(不思議な花#1)	不思議な花#38	844
1@mist.gat,335,126,0	duplicate(不思議な花#1)	不思議な花#39	844
1@mist.gat,332,141,0	duplicate(不思議な花#1)	不思議な花#40	844
1@mist.gat,328,144,0	duplicate(不思議な花#1)	不思議な花#41	844
1@mist.gat,314,144,0	duplicate(不思議な花#1)	不思議な花#42	844
1@mist.gat,238,224,0	duplicate(不思議な花#1)	不思議な花#43	844
1@mist.gat,244,231,0	duplicate(不思議な花#1)	不思議な花#44	844
1@mist.gat,257,232,0	duplicate(不思議な花#1)	不思議な花#45	844
1@mist.gat,262,229,0	duplicate(不思議な花#1)	不思議な花#46	844
1@mist.gat,265,216,0	duplicate(不思議な花#1)	不思議な花#47	844
1@mist.gat,260,214,0	duplicate(不思議な花#1)	不思議な花#48	844
1@mist.gat,252,206,0	duplicate(不思議な花#1)	不思議な花#49	844
1@mist.gat,244,211,0	duplicate(不思議な花#1)	不思議な花#50	844

1@mist.gat,89,29,0	script	囁き#mist	844,1,1,{
	hideonnpc;
	initnpctimer;
	end;
OnTimer7000:
	announce "森の囁き : 誰？誰？森に誰か入ってきた！トーム、トームバー、レム、レミ！みんな起きて！",0x9,0xccffcc,0x190,12,0,0;
	end;
OnTimer15000:
	announce "森の囁き : トーム、トームバー、かんぬきをしっかりかけて！逃がさないで！",0x9,0xccffcc,0x190,12,0,0;
	end;
OnTimer60000:
	announce "森の囁き : 森の番人達は何をしているの？庭師達は何をしているの？みんなでお出迎えしよう！",0x9,0xccffcc,0x190,12,0,0;
	end;
OnTimer120000:
	announce "森の囁き : ず～っと私達と遊ぼうよ！この森に永遠にいてね！ずっと一緒！",0x9,0xccffcc,0x190,12,0,0;
	end;
OnTimer180000:
	stopnpctimer;
	announce "森の囁き : アハハ！森から出たければ、私達を倒してごらんよ。そうすれば道が開かれるかも！アハハ！",0x9,0xccffcc,0x190,12,0,0;
	end;
}

1@mist.gat,104,23,0	script	to_bif01	45,1,1,{
	mes "‐ここから外に出られそうだ。";
	mes "　";
	mes "　霧の森から出て、";
	mes "　5分以上誰もいない状態が続くと";
	mes "　この霧の森は消滅します。";
	mes "　5分より早く";
	mes "　再入場すれば消滅しません‐";
	next;
	if(select("外に出ない","外に出る") == 1) {
		mes "‐霧の森に残った‐";
		close;
	}
	mes "‐霧の森をあとにした‐";
	close2;
	warp "bif_fild01.gat",163,331;
	end;
}

1@mist.gat,109,70,0		script	a1_a2	45,1,1,{
	if('flag <= 0) {
		mes "‐この先から";
		mes "　モンスターの気配を感じる。";
		mes "　先に進むとモンスターが現れそうだ‐";
		next;
		if(select("進まない","進む") == 1) {
			mes "‐進むのをやめた‐";
			close;
		}
		mes "‐進むことにした‐";
		close2;
		if('flag <= 0)
			donpcevent getmdnpcname("MistwoodControl")+"::OnStart";
		set 'flag,1;
	}
	warp getmdmapname("1@mist.gat"),116,40;
	end;
}

1@mist.gat,113,40,0		warp	a2_a7		1,1,1@mist.gat,90,81
1@mist.gat,93,81,0		warp	a7_a14		1,1,1@mist.gat,108,152
1@mist.gat,111,154,0	warp	a14_a24		1,1,1@mist.gat,236,108
1@mist.gat,236,110,0	warp	a24_a1		1,1,1@mist.gat,106,69
1@mist.gat,161,67,0		warp	a18-1_a22	1,1,1@mist.gat,159,85
1@mist.gat,180,116,0	warp	a23_a18-1	1,1,1@mist.gat,164,66
1@mist.gat,180,63,0		warp	a18-2_a9	1,1,1@mist.gat,140,90
1@mist.gat,116,84,0		warp	a8_a26		1,1,1@mist.gat,222,133
1@mist.gat,220,133,0	warp	a26_a27-1	1,1,1@mist.gat,200,64
1@mist.gat,197,64,0		warp	a27-1_a23	1,1,1@mist.gat,177,116
1@mist.gat,146,194,0	warp	af1-2_a27-2	1,1,1@mist.gat,225,96
1@mist.gat,133,195,0	warp	af1-1_af2-1	1,1,1@mist.gat,202,110
1@mist.gat,202,107,0	warp	af2-1_af1-1	1,1,1@mist.gat,134,189
1@mist.gat,217,110,0	warp	af2-2_a20-1	1,1,1@mist.gat,240,56
1@mist.gat,240,54,0		warp	a20-1_af2-2	1,1,1@mist.gat,214,110
1@mist.gat,234,67,0		warp	a20-2_a21	1,1,1@mist.gat,239,80
1@mist.gat,242,77,0		warp	a21_a15-1	1,1,1@mist.gat,153,137
1@mist.gat,156,139,0	warp	a15-1_a3	1,1,1@mist.gat,123,55
1@mist.gat,124,51,0		warp	a3_a20-1	1,1,1@mist.gat,240,56
1@mist.gat,48,41,0		warp	a4-1_a17	1,1,1@mist.gat,174,165
1@mist.gat,171,165,0	warp	a17_a16		1,1,1@mist.gat,168,143
1@mist.gat,169,141,0	warp	a16_a10		1,1,1@mist.gat,101,107
1@mist.gat,99,107,0		warp	a10_a4-2	1,1,1@mist.gat,57,38
1@mist.gat,65,113,0		warp	a11_a28		1,1,1@mist.gat,218,151
1@mist.gat,221,151,0	warp	a28_a13		1,1,1@mist.gat,117,126
1@mist.gat,114,126,0	warp	a13_a5		1,1,1@mist.gat,36,62
1@mist.gat,61,88,0		warp	a6_a19		1,1,1@mist.gat,189,139
1@mist.gat,186,140,0	warp	a19_a12		1,1,1@mist.gat,98,126
1@mist.gat,101,126,0	warp	a12_a29-1	1,1,1@mist.gat,238,151
1@mist.gat,235,152,0	warp	a29-1_af1-2	1,1,1@mist.gat,144,194
1@mist.gat,254,151,0	warp	a29-2E_b1	1,1,1@mist.gat,271,164
1@mist.gat,275,211,0	warp	b1_b13		1,1,1@mist.gat,277,112
1@mist.gat,301,141,0	warp	b14_b24		1,1,1@mist.gat,99,232
1@mist.gat,99,230,0		warp	b24_b25		1,1,1@mist.gat,103,255
1@mist.gat,102,253,0	warp	b25_b4-1	1,1,1@mist.gat,215,177
1@mist.gat,212,177,0	warp	b4-1_b1		1,1,1@mist.gat,276,208
1@mist.gat,289,167,0	warp	b2_b19		1,1,1@mist.gat,152,219
1@mist.gat,149,219,0	warp	b19_b20		1,1,1@mist.gat,119,227
1@mist.gat,115,227,0	warp	b20_b23		1,1,1@mist.gat,230,353
1@mist.gat,233,353,0	warp	b23_b7		1,1,1@mist.gat,289,225
1@mist.gat,76,273,0		warp	bf1-2_b7	1,1,1@mist.gat,289,225
1@mist.gat,61,282,0		warp	bf1-1_bf2-1	1,1,1@mist.gat,256,220
1@mist.gat,252,220,0	warp	bf2-1_bf1-1	1,1,1@mist.gat,65,282
1@mist.gat,267,213,0	warp	bf2-2_b28	1,1,1@mist.gat,214,268
1@mist.gat,212,265,0	warp	b28_b12		1,1,1@mist.gat,288,266
1@mist.gat,285,266,0	warp	b12_b21		1,1,1@mist.gat,143,234
1@mist.gat,143,231,0	warp	b21_b29		1,1,1@mist.gat,222,281
1@mist.gat,223,279,0	warp	b29_b31		1,1,1@mist.gat,158,317
1@mist.gat,134,287,0	warp	b30_b3		1,1,1@mist.gat,293,195
1@mist.gat,295,197,0	warp	b3_b10		1,1,1@mist.gat,239,253
1@mist.gat,236,253,0	warp	b10_b12		1,1,1@mist.gat,288,266
1@mist.gat,111,203,0	warp	b16_b34		1,1,1@mist.gat,202,333
1@mist.gat,199,333,0	warp	b34_b27-1	1,1,1@mist.gat,203,251
1@mist.gat,206,249,0	warp	b27-1_b22	1,1,1@mist.gat,168,239
1@mist.gat,165,239,0	warp	b22_b15		1,1,1@mist.gat,89,173
1@mist.gat,177,265,0	warp	b27-2_a14	1,1,1@mist.gat,108,152
1@mist.gat,166,314,0	warp	bN-1_b27-3	1,1,1@mist.gat,206,297
1@mist.gat,197,299,0	warp	bN-2_b17	1,1,1@mist.gat,167,200
1@mist.gat,165,200,0	warp	b17_bN-2	1,1,1@mist.gat,193,299
1@mist.gat,86,173,0		warp	b15_b32		1,1,1@mist.gat,218,313
1@mist.gat,215,313,0	warp	b32_b28		1,1,1@mist.gat,214,268
1@mist.gat,230,324,0	warp	b33_b6-1	1,1,1@mist.gat,221,233
1@mist.gat,230,230,0	warp	b6-2_b11	1,1,1@mist.gat,263,261
1@mist.gat,263,258,0	warp	b11_b9		1,1,1@mist.gat,272,246
1@mist.gat,269,246,0	warp	b9_b26		1,1,1@mist.gat,143,265
1@mist.gat,140,265,0	warp	b26_b5		1,1,1@mist.gat,209,200
1@mist.gat,195,206,0	warp	b18_b35		1,1,1@mist.gat,169,341
1@mist.gat,166,341,0	warp	b35_b36		1,1,1@mist.gat,198,354
1@mist.gat,201,354,0	warp	b36_b37-1	1,1,1@mist.gat,83,224
1@mist.gat,87,224,0		warp	b37-1_b35	1,1,1@mist.gat,169,341
1@mist.gat,84,273,0		warp	b37-2_c1	1,1,1@mist.gat,98,287
1@mist.gat,111,298,0	warp	c2_c3		1,1,1@mist.gat,82,307
1@mist.gat,79,307,0		warp	c3_c7		1,1,1@mist.gat,284,89
1@mist.gat,281,89,0		warp	c7_c12		1,1,1@mist.gat,264,291
1@mist.gat,261,291,0	warp	c12_c2		1,1,1@mist.gat,115,298
1@mist.gat,326,275,0	warp	c13-1_b13	1,1,1@mist.gat,277,112
1@mist.gat,294,293,0	warp	c13-2_c5	1,1,1@mist.gat,78,330
1@mist.gat,81,330,0		warp	c5_c17		1,1,1@mist.gat,308,330
1@mist.gat,308,327,0	warp	c17_c10		1,1,1@mist.gat,309,165
1@mist.gat,306,165,0	warp	c10_c13-2	1,1,1@mist.gat,298,293
1@mist.gat,46,316,0		warp	c4_c6		1,1,1@mist.gat,113,328
1@mist.gat,95,328,0		warp	c6_c9		1,1,1@mist.gat,342,157
1@mist.gat,339,157,0	warp	c9_c16		1,1,1@mist.gat,343,328
1@mist.gat,343,325,0	warp	c16_c8-2	1,1,1@mist.gat,346,120
1@mist.gat,344,123,0	warp	c8-2_c19	1,1,1@mist.gat,277,343
1@mist.gat,256,313,0	warp	c18_c15		1,1,1@mist.gat,343,307
1@mist.gat,342,305,0	warp	c15_cKEY	1,1,1@mist.gat,332,121
1@mist.gat,335,120,0	warp	cKEY_c18	1,1,1@mist.gat,259,313
1@mist.gat,317,89,0		warp	c8-1_c14	1,1,1@mist.gat,339,284
1@mist.gat,339,281,0	warp	c14_c11-1	1,1,1@mist.gat,332,172
1@mist.gat,329,171,0	warp	c11-1_c8-2	1,1,1@mist.gat,346,120
1@mist.gat,301,237,0	warp	b8_b2		1,1,1@mist.gat,289,170

1@mist.gat,247,123,0	script	a25_a18-1	45,1,1,{
	warp getmdmapname("1@mist.gat"),164,66;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,225,98,0		script	a27-2_af1-2	45,1,1,{
	warp getmdmapname("1@mist.gat"),144,194;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,159,184,0	script	a15-2_a4-1	45,1,1,{
	warp getmdmapname("1@mist.gat"),49,37;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,61,39,0		script	a4-2_a11	45,1,1,{
	warp getmdmapname("1@mist.gat"),68,113;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,230,179,0	script	b4-2_b2		45,1,1,{
	warp getmdmapname("1@mist.gat"),289,170;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,285,225,0	script	b7_bf1-2	45,1,1,{
	warp getmdmapname("1@mist.gat"),72,274;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,161,316,0	script	b31_b16		45,1,1,{
	warp getmdmapname("1@mist.gat"),108,203;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,204,299,0	script	b27-3_bN-1	45,1,1,{
	warp getmdmapname("1@mist.gat"),169,314;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,221,236,0	script	b6-1_b33	45,1,1,{
	warp getmdmapname("1@mist.gat"),233,324;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,206,200,0	script	b5_b14		45,1,1,{
	warp getmdmapname("1@mist.gat"),298,142;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,95,287,0		script	c1_c13-1	45,1,1,{
	warp getmdmapname("1@mist.gat"),323,276;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,324,325,0	script	c13-3_c4	45,1,1,{
	warp getmdmapname("1@mist.gat"),49,316;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,280,344,0	script	c19_c4		45,1,1,{
	warp getmdmapname("1@mist.gat"),49,316;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}

1@mist.gat,345,186,0	script	to_bif02	45,1,1,{
	warp "bif_fild02.gat",151,121;
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	misceffect 6;
	initnpctimer;
	end;
}
