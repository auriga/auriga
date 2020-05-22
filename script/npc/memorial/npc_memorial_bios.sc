//= Auriga Script ==============================================================
// Ragnarok Online Bios Island Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
moro_cav.gat,45,60,5	script	調査隊員	419,{
	if(!(checkquest(15006) & 0x8)) {	// 初回会話
		mes "[調査隊員]";
		mes "ここはモロク復活を防ぐ連合軍の";
		mes "最前線です。";
		mes "私は調査隊により発見された";
		mes "^ff0000黄色い種^000000の調査を行っています。";
		next;
		mes "[調査隊員]";
		mes "しかし、黄色い種の内部には";
		mes "強力なモンスターが生息しており";
		mes "調査隊も甚大な被害を";
		mes "受けてしまいました……。";
		next;
		mes "[調査隊員]";
		mes "調査は続行しなければなりませんが";
		mes "私一人の力では調査を行なえません。";
		next;
		mes "[調査隊員]";
		mes "そこで、腕の立つであろう";
		mes "冒険者の方々にお手伝いを";
		mes "お願いしているのです。";
		next;
		mes "[調査隊員]";
		mes "お願いします！";
		mes "黄色い種の内部の調査に";
		mes "協力してください！";
		next;
		menu "協力する",-;
		mes "[調査隊員]";
		mes "ありがとうございます！";
		mes "黄色い種の内部は非常に危険です。";
		mes "必ずパーティーを組んでから";
		mes "調査を行ってください。";
		mes "よろしくお願いします！";
		setquest 15006;
		compquest 15006;
		close;
	}
	mes "[調査隊員]";
	mes "黄色い種の内部は非常に危険です。";
	mes "必ずパーティーを組んでから";
	mes "調査を行ってください。";
	mes "よろしくお願いします！";
	close;
}
moro_cav.gat,50,63,5	script	黄色い種#bios	844,{
	if(!(checkquest(15006) & 0x8)) {	// 初回会話
		mes "[調査隊員]";
		mes "ここはモロク復活を防ぐ連合軍の";
		mes "最前線です。";
		mes "私は調査隊により発見された";
		mes "^ff0000黄色い種^000000の調査を行っています。";
		next;
		mes "[調査隊員]";
		mes "しかし、黄色い種の内部には";
		mes "強力なモンスターが生息しており";
		mes "調査隊も甚大な被害を";
		mes "受けてしまいました……。";
		next;
		mes "[調査隊員]";
		mes "調査は続行しなければなりませんが";
		mes "私一人の力では調査を行なえません。";
		next;
		mes "[調査隊員]";
		mes "そこで、腕の立つであろう";
		mes "冒険者の方々にお手伝いを";
		mes "お願いしているのです。";
		next;
		mes "[調査隊員]";
		mes "お願いします！";
		mes "黄色い種の内部の調査に";
		mes "協力してください！";
		next;
		menu "協力する",-;
		mes "[調査隊員]";
		mes "ありがとうございます！";
		mes "黄色い種の内部は非常に危険です。";
		mes "必ずパーティーを組んでから";
		mes "調査を行ってください。";
		mes "よろしくお願いします！";
		setquest 15006;
		compquest 15006;
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "^ff0000‐この先に進むにはパーティーに";
		mes "　加入している必要がある‐^000000";
		close;
	}
	if((checkquest(15005)&0x2 == 0 || checkquest(118927)&0x2 == 0) && checkquest(15007)&0x2) {
		mes "‐この先は入場してから1回目の";
		mes "　^ff0000午前5時以降^000000に進行可能です。";
		mes "　但し、最後の入場をしてから";
		mes "　^ff00001時間^000000経過するまでは";
		mes "　進行できませんのでご注意ください‐";
		close;
	}
	if(checkquest(15005) & 0x2) {
		delquest 15005;
		delquest 15007;
	}
	if(checkquest(118927) & 0x2)
		delquest 118927;
	set '@party$,getpartyname(getcharid(1));
	set '@leader$,getpartyleader(getcharid(1));
	mes "‐黄色い種がある‐";
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		set '@str1$,"黄色い種への道を開く";
		set '@str2$,"黄色い種に入る";
	}
	else {
		set '@str2$,"黄色い種に入る";
	}
	next;
	switch(select('@str1$,'@str2$,"キャンセル")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "パーティー名：" +'@party$;
			mes "パーティーリーダー：" +'@leader$;
			mes "^0000ffbios_island ^000000－予約失敗";
			close;
		}
		mdcreate "bios_island";
		mes "^ff0000‐メモリアルダンジョンが^000000";
		mes "^ff0000　生成されました。^000000";
		mes "^ff0000　再度クリックして^000000";
		mes "^ff0000　入場を押して下さい‐^000000";
		close;
	case 2:
		switch(mdenter("bios_island")) {
		case 0:	// エラーなし
			announce "メモリアルダンジョン[bios_island] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")", 0x1, 0x00ff99;
			setquest 96430;
			setquest 15005;
			setquest 15007;
			setquest 118927;
			donpcevent getmdnpcname("BiosControl")+ "::OnStart";
			close2;
			//warp "1@dth1.gat",17,93;
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
	case 3:
		mes "‐黄色い種から離れた‐";
		close;
	}
OnInit:
	waitingroom "ビオスの島",0;
	end;
}

//============================================================
// ビオスの島
//------------------------------------------------------------
1@dth1.gat,84,90,0	script	#BARRICADE_bios1_1	1905,{}
1@dth1.gat,84,91,0	script	#BARRICADE_bios1_2	1905,{}
1@dth1.gat,84,92,0	script	#BARRICADE_bios1_3	1905,{}
1@dth1.gat,84,93,0	script	#BARRICADE_bios1_4	1905,{}
1@dth1.gat,84,94,0	script	#BARRICADE_bios1_5	1905,{}
1@dth1.gat,84,95,0	script	#BARRICADE_bios1_6	1905,{}
1@dth1.gat,84,96,0	script	#BARRICADE_bios1_7	1905,{}
1@dth1.gat,84,97,0	script	#BARRICADE_bios1_8	1905,{}

1@dth1.gat,1,1,0	script	BiosControl	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("死神アンク#bios1");
	hideonnpc getmdnpcname("#会話用ダミー1");
	hideonnpc getmdnpcname("司令官アジフ#bios1");
	hideonnpc getmdnpcname("教官長イグリド#bios1");
	hideonnpc getmdnpcname("キド#bios1");
	hideonnpc getmdnpcname("リーン#bios1");
	hideonnpc getmdnpcname("連合軍事務官#bios1");
	hideonnpc getmdnpcname("リョースン#bios1");
	hideonnpc getmdnpcname("ヒュー#bios1");
	hideonnpc getmdnpcname("ヘンジヌ#bios1");
	hideonnpc getmdnpcname("ヒシエ#bios1");
	hideonnpc getmdnpcname("エイヴァント#bios1");
	hideonnpc getmdnpcname("大臣ヘスランタ#bios1");
	hideonnpc getmdnpcname("先発隊長アバランチェ#b1");

	hideonnpc getmdnpcname("warp1#bios2");
	hideonnpc getmdnpcname("死神アンク#bios3");

	hideonnpc getmdnpcname("司令官アジフ#bios3");
	hideonnpc getmdnpcname("教官長イグリド#bios3");
	hideonnpc getmdnpcname("キド#bios3");
	hideonnpc getmdnpcname("リーン#bios3");
	hideonnpc getmdnpcname("リョースン#bios3");
	hideonnpc getmdnpcname("ヒュー#bios3");
	hideonnpc getmdnpcname("ヘンジヌ#bios3");
	hideonnpc getmdnpcname("ヒシエ#bios3");
	hideonnpc getmdnpcname("エイヴァント#bios3");
	hideonnpc getmdnpcname("大臣ヘスランタ#bios3");
	hideonnpc getmdnpcname("先発隊長アバランチェ#b3");

	hideonnpc getmdnpcname("freeze#bios3");

	for(set '@i,1; '@i<=3; set '@i,'@i+1) {
		for(set '@j,1; '@j<=8; set '@j,'@j+1)
			hideonnpc getmdnpcname("死者のオークゾンビ#"+ '@i + '@j +"bi");
	}

	areasetcell getmdmapname("1@dth1.gat"),84,90,85,97,1;
	areasetcell getmdmapname("1@dth2.gat"),150,126,151,133,1;

	set '@map$,getmdmapname("1@dth1.gat");
	set '@label$,getmdnpcname("BiosControl")+ "::OnKilled";
	monster '@map$,90,94,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,90,94,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,101,125,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,101,125,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,108,156,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,108,156,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,119,59,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,119,144,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,121,69,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,124,164,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,131,101,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,131,101,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,135,50,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,135,152,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,138,132,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,138,132,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,141,143,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,143,49,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,144,164,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,145,107,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,145,107,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,153,76,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,153,76,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,156,46,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,165,84,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,165,130,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,170,67,"生者のマリンスフィアー",3012,2,'@label$;
	monster '@map$,184,130,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,192,145,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,194,116,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,203,131,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,203,151,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,203,162,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,203,162,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,204,112,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,205,98,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,206,169,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,210,62,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,211,88,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,212,75,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,213,151,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,214,53,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,215,109,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,217,129,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,221,166,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,223,72,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,224,62,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,225,103,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,225,54,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,225,89,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,225,152,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,227,150,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,227,150,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,227,150,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,228,124,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,232,87,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,232,69,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,233,57,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,237,80,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,240,140,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,243,106,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,244,119,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,246,71,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,246,126,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,248,81,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,249,144,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,249,155,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,252,105,"生者のオークベイビー",3010,1,'@label$;
	monster '@map$,274,104,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,297,103,"生者のマリンスフィアー",3012,1,'@label$;
	monster '@map$,306,103,"生者の子デザートウルフ",3011,1,'@label$;
	monster '@map$,316,103,"生者のオークベイビー",3010,1,'@label$;

	donpcevent getmdnpcname("#bios2_mobdead1") +"::OnStart";
	end;
OnKilled:
	end;
}
1@dth1.gat,71,97,3	script	ジェイス#bios1	467,{
	mes "[ジェイス]";
	mes "……ジェイスだ。";
	next;
	mes "[ジェイス]";
	mes "……。";
	close;
}
1@dth1.gat,74,94,3	script	死神アンク#bios1	3029,{
	end;
OnTalk1:
	unittalk "？？？？ : クックック。";
	end;
OnTalk2:
	unittalk "？？？？ : ようこそビオスの島へ。";
	end;
OnTalk3:
	unittalk "死神アンク : 私は死神アンク。ここは私が作り出した死と生の空間です。";
	end;
OnTalk4:
	unittalk "死神アンク : これはこれは、みなさん威勢がいいようですね。";
	end;
OnTalk5:
	unittalk "死神アンク : これからモロク様に捧げる生贄を調達しようとしていたのですが……。";
	end;
OnTalk6:
	unittalk "死神アンク : まさか生贄が自らやって来るとは……ククク。";
	end;
OnTalk7:
	unittalk "死神アンク : モロク様の力になれる事を光栄に思いなさい。";
	end;
OnTalk8:
	unittalk "死神アンク : クク、威勢が良くて結構です。ただ、急ぐ必要はありません。";
	end;
OnTalk9:
	unittalk "死神アンク : まずは私の世界でゆっくり……くつろぐことです。ククククク。";
	end;
}
1@dth1.gat,67,97,5	script	ブリド#bios1	468,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0) || 'flag) {
		mes "[ブリド]";
		mes "私はブリド。";
		mes "魔王モロクの復活を";
		mes "阻止しに来たんだ。";
		close;
	}
	if(checkquest(201720)) {
		if(select("先を急ぐ","会話をする") == 1) {
			mes "‐誰が来ている？‐";
			next;
			set '@menu,select(
				(ASH_6QUE == 14 || ASH_6QUE == 15? "アジフとイグリドだ": "？？？"),
				(ASH_5QUE >= 31? "キドとリーンだ": "？？？"),
				(ASH_3QUE >= 100? "セルザン達だ": "？？？"),
				(ECL_3QUE >= 33? "ヒシエとエイヴァントだ": "？？？"),
				(DIC_2QUE >= 23? "ヘスランタとアバランチェだ": "？？？"),
				"誰もいない");
			switch('@menu) {
			case 1:
				mes "‐アジフ、イグリドと合流した‐";
				set '@menu,3;
				break;
			case 2:
				mes "‐キド、リーンと合流した‐";
				set '@menu,4;
				break;
			case 3:
				mes "‐セルザン、リョースン、";
				mes "　ヒュー、ヘンジヌと合流した‐";
				set '@menu,5;
				break;
			case 4:
				mes "‐ヒシエ、";
				mes "　エイヴァントと合流した‐";
				set '@menu,6;
				break;
			case 5:
				mes "‐ヘスランタ、";
				mes "　アバランチェと合流した‐";
				set '@menu,7;
				break;
			default:
				mes "‐誰とも合流しなかった‐";
				set '@menu,2;
				break;
			}
			close2;
			set 'flag,'@menu;
			hideonnpc getmdnpcname("ブリド#bios1");
			hideonnpc getmdnpcname("ジェイス#bios1");
			donpcevent getmdnpcname("ブリド#bios1")+ "::OnStart";
			end;
		}
	}
	mes "‐見慣れない男性二人組が居る‐";
	close2;
	set 'flag,1;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ブリド : おや？　こんなところで冒険者に会うとは……";
	end;
OnTimer4000:
	unittalk "ブリド : 君も魔王モロクの復活を阻止しに来たのか？";
	end;
OnTimer7000:
	unittalk "ブリド : 私はプロンテラから来たブリド。こいつは……";
	end;
OnTimer10000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……ジェイスだ。";
	end;
OnTimer13000:
	unittalk "ブリド : すまんな。ジェイスは人見知りなんだ。";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……";
	end;
OnTimer19000:
	unittalk "ブリド : それより、後ろから誰か追いかけて来ているが、君の知り合いか？";
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc getmdnpcname("#会話用ダミー1");
	end;
OnStart:
	hideonnpc getmdnpcname("#BARRICADE_bios1_1");
	hideonnpc getmdnpcname("#BARRICADE_bios1_2");
	hideonnpc getmdnpcname("#BARRICADE_bios1_3");
	hideonnpc getmdnpcname("#BARRICADE_bios1_4");
	hideonnpc getmdnpcname("#BARRICADE_bios1_5");
	hideonnpc getmdnpcname("#BARRICADE_bios1_6");
	hideonnpc getmdnpcname("#BARRICADE_bios1_7");
	hideonnpc getmdnpcname("#BARRICADE_bios1_8");
	areasetcell getmdmapname("1@dth1.gat"),84,90,85,97,0;
	sleep 3000;
	announce "死神アンク : 死、それは生ある者のみに訪れる恐怖。すべてはここから始まるのです……", 0x9, 0xffff00;
	sleep 3000;
	announce "ブリド : 待てアンク！　くそっ、東に逃げたようだな。奴を追うぞ！", 0x9, 0xffff00;
	end;
}
1@dth1.gat,67,97,0	script	#会話用ダミー1	139,10,10,{
	mes "‐誰が来ている？‐";
	next;
	set '@menu,select(
		(ASH_6QUE == 14 || ASH_6QUE == 15? "アジフとイグリドだ": "？？？"),
		(ASH_5QUE >= 31? "キドとリーンだ": "？？？"),
		(ASH_3QUE >= 100? "セルザン達だ": "？？？"),
		(ECL_3QUE >= 33? "ヒシエとエイヴァントだ": "？？？"),
		(DIC_2QUE >= 23? "ヘスランタとアバランチェだ": "？？？"),
		"誰もいない");
	switch('@menu) {
	case 1:
		if(ASH_6QUE == 14 || ASH_6QUE == 15) {
			mes "‐振り向くと、アジフとイグリドが居た‐";
			close2;
			set 'flag,3;
			set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),3;
			hideonnpc getmdnpcname("#会話用ダミー1");
			hideoffnpc getmdnpcname("司令官アジフ#bios1");
			hideoffnpc getmdnpcname("教官長イグリド#bios1");
			donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
			end;
		}
		break;
	case 2:
		if(ASH_5QUE >= 31) {
			mes "‐振り向くと、キドとリーンが居た‐";
			close2;
			set 'flag,4;
			set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),4;
			hideonnpc getmdnpcname("#会話用ダミー1");
			hideoffnpc getmdnpcname("キド#bios1");
			hideoffnpc getmdnpcname("リーン#bios1");
			donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
			end;
		}
		break;
	case 3:
		if(ASH_3QUE >= 100) {
			mes "‐振り向くと、セルザン、リョースン、";
			mes "　ヒュー、ヘンジヌが居た‐";
			close2;
			set 'flag,5;
			set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),5;
			hideonnpc getmdnpcname("#会話用ダミー1");
			hideoffnpc getmdnpcname("リョースン#bios1");
			hideoffnpc getmdnpcname("ヒュー#bios1");
			hideoffnpc getmdnpcname("ヘンジヌ#bios1");
			hideoffnpc getmdnpcname("連合軍事務官#bios1");
			donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
			end;
		}
		break;
	case 4:
		if(ECL_3QUE >= 33) {
			mes "‐振り向くと、ヒシエと";
			mes "　エイヴァントが居た‐";
			close2;
			set 'flag,6;
			set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),6;
			hideonnpc getmdnpcname("#会話用ダミー1");
			hideoffnpc getmdnpcname("ヒシエ#bios1");
			hideoffnpc getmdnpcname("エイヴァント#bios1");
			donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
			end;
		}
		break;
	case 5:
		if(DIC_2QUE >= 23) {
			mes "‐振り向くと、ヘスランタと";
			mes "　アバランチェが居た‐";
			close2;
			set 'flag,7;
			set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),7;
			hideonnpc getmdnpcname("#会話用ダミー1");
			hideoffnpc getmdnpcname("大臣ヘスランタ#bios1");
			hideoffnpc getmdnpcname("先発隊長アバランチェ#b1");
			donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
			end;
		}
		break;
	default:
		mes "‐振り向くと、誰もいなかった。";
		mes "　ブリドの勘違いだろう‐";
		close2;
		set 'flag,2;
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),2;
		hideonnpc getmdnpcname("#会話用ダミー1");
		donpcevent getmdnpcname("#会話用ダミー1")+ "::OnStart";
		end;
	}
	mes "‐振り向くと、誰もいなかった。";
	mes "　ブリドの勘違いだろう‐";
	mes "　";
	mes "‐条件を満たしていないため";
	mes "　仲間を呼ぶことが出来ません‐";
	close;
OnStart:
	sleep 1000;
	if('flag == 2) {
		sleep 2000;
	}
	else if('flag == 3) {
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : みんな、無事か！　俺が来たからにはもう大丈夫だ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios1")),"イグリド : 兄貴！　司令官が前線に出るなんてどういうつもりだ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : うるさい！　あと、俺の事は司令官と呼べ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : あんたら……連合軍の司令官アジフと教官長イグリドか！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……どうしてこんなところに？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : こいつには借りがあってな。そいつを返しに来たんだ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios1")),"イグリド : そういうわけだから、悪いが俺たちも同行させて貰うぜ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : あんたらが居るなら心強い！　よろしく頼むぜ！";
		sleep 3000;
	}
	else if('flag == 4) {
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド : 久しぶりだな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("リーン#bios1")),"リーン : 久しぶりだね！　あの時はありがとう！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド : お前には世話になったからな。手伝ってやろう。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 君たちが誰かは知らないが、ここは危険だ！　帰った方が良い！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド :そう言うな、これでも腕に覚えはあるんだぜ？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("リーン#bios1")),"リーン : と、言うわけで私たちも一緒に行くよ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……ブリド、こいつら、口だけじゃなさそうだ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : そうか……だが、無理だけはしないでくれよ。";
		sleep 3000;
	}
	else if('flag == 5) {
		unittalk getnpcid(0,getmdnpcname("連合軍事務官#bios1")),"セルザン: みなさん、お久しぶりです！　僕たちにもお手伝いさせてください！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヘンジヌ#bios1")),"ヘンジヌ : 私がみんなに提案したんです。世話になった恩を返そうって。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒュー#bios1")),"ヒュー : まったく、何が提案だ……。これだからアルナベルツの人間は……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("リョースン#bios1")),"リョースン : 僕たちの意見も聞かずに勝手に決めてましたもんね……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒュー#bios1")),"ヒュー : リョースンだって私に無断で会議の日程を決めるけどな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヘンジヌ#bios1")),"ヘンジヌ : ヒューだって、ユーモアもセンスもなくて、堅苦しいですよ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("連合軍事務官#bios1")),"セルザン: 3人とも、こんな場所でケンカはやめてください！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : ……君たちはただの事務官だろう？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 悪い事は言わない。帰った方が良い。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……ブリド、こいつら聞いてないぞ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : ……。";
		sleep 3000;
	}
	else if('flag == 6) {
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : みんな、無事なようで良かった。私にも手伝わせてくれ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios1")),"エイヴァント : 勘違いするなよ。私はシナイムを追っているだけだ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : 私一人で行くと言ったのに、罪滅ぼしだと言ってついて来たんだ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ラフィネ族……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : ラフィネ族がどうしてここに？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : すまない、詳しい事は秘密なんだ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : そうだな、この人の仲間とでも思ってくれ。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : そうか、仲間が増えるのは心強い。よろしく頼む。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios1")),"エイヴァント : ふん、馴れ合いはそこまでだ。お出迎えが来たぞ。";
		sleep 3000;
	}
	else if('flag == 7) {
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b1")),"アバランチェ : こ、こちらにいらっしゃいましたか！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : アハトはあの後、行方をくらませてしまいました……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : アハトの行方を追う為にも同行させてください！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 君たちは……サファ族か？";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b1")),"アバランチェ : いかにも、先発隊長のアバランチェです。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : 大臣のヘスランタです。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 大臣……すまないが要人警護の経験はなくてね。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 自分の身は自分で守って貰うことになる。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : 心得ていますとも。みなさん、よろしくお願いします。";
		sleep 3000;
	}
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"？？？？ : クックック。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……!!!　誰だ!?";
	sleep 3000;
	hideoffnpc getmdnpcname("死神アンク#bios1");
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"？？？？ : ようこそビオスの島へ。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : 私は死神アンク。ここは私が作り出した死と生の空間です。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : なにっ!!";
	sleep 3000;
	if('flag == 3) {
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : へぇ、こいつが親玉か。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios1")),"イグリド : さすが……他とは桁違いの強さみたいだな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : 全員、気を抜くんじゃないぞ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これはこれは、みなさん威勢がいいようですね。";
		sleep 3000;
	}
	else if('flag == 4) {
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド : こいつ……強いな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("リーン#bios1")),"リーン : そうだね、死神っていうだけの事はあるかな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド : ああ……だが、全員でかかれば勝てない相手じゃない。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これはこれは、みなさん威勢がいいようですね。";
		sleep 3000;
	}
	else if('flag == 5) {
		unittalk getnpcid(0,getmdnpcname("リョースン#bios1")),"リョースン: し、死神!?";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒュー#bios1")),"ヒュー : す、凄く強そうじゃないですか！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヘンジヌ#bios1")),"ヘンジヌ : 死神って浮いてるんですね！　アハハハハ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("連合軍事務官#bios1")),"セルザン : みなさん、気を付けてください！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これはこれは、みなさん威勢がいいようですね。";
		sleep 3000;
	}
	else if('flag == 6) {
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : こいつ……強いぞ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios1")),"エイヴァント : ククク、大した魔力を持ってるようだな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios1")),"エイヴァント : 実験体として欲しいところだが……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : お前はまだそんな事を……！　みんな、気をつけろ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これはこれは、みなさん威勢がいいようですね。";
		sleep 3000;
	}
	else if('flag == 7) {
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b1")),"アバランチェ : みなさん、お気をつけください！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : これは、強敵のようですね……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios1")),"ヘスランタ : ですが、我々は退くわけにはいかないのです！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これはこれは、みなさん威勢がいいようですね。";
		sleep 3000;
	}
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : これからモロク様に捧げる生贄を調達しようとしていたのですが……。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : まさか生贄が自らやって来るとは……ククク。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : モロク様の力になれる事を光栄に思いなさい。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : はっ！　三下に用はない！";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 誰だか知らんが、まずはお前を倒してやるっ!!";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : クク、威勢が良くて結構です。ただ、急ぐ必要はありません。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios1")),"死神アンク : まずは私の世界でゆっくり……くつろぐことです。ククククク。";
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#bios1");
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : くそっ！　消えやがった!!";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : あいつが魔王モロクを復活させようとしているのか？";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios1")),"ブリド : 奴を追うぞ！　ジェイス急げ！";
	hideonnpc getmdnpcname("ブリド#bios1");
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios1")),"ジェイス : ……先行する。あとからついて来てくれ。";
	sleep 1000;
	hideonnpc getmdnpcname("ジェイス#bios1");
	sleep 3000;
	if('flag == 3) {
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios1")),"アジフ : イグリド！　俺たちも続くぞ！";
		sleep 3000;
		hideonnpc getmdnpcname("司令官アジフ#bios1");
		hideonnpc getmdnpcname("教官長イグリド#bios1");
	}
	else if('flag == 4) {
		unittalk getnpcid(0,getmdnpcname("キド#bios1")),"キド : よし！　俺たちも行くぞ！";
		sleep 3000;
		hideonnpc getmdnpcname("キド#bios1");
		hideonnpc getmdnpcname("リーン#bios1");
	}
	else if('flag == 5) {
		unittalk getnpcid(0,getmdnpcname("リョースン#bios1")),"リョースン : こ、怖いけど……みんな！　行きましょう！";
		sleep 3000;
		hideonnpc getmdnpcname("リョースン#bios1");
		hideonnpc getmdnpcname("ヒュー#bios1");
		hideonnpc getmdnpcname("ヘンジヌ#bios1");
		hideonnpc getmdnpcname("連合軍事務官#bios1");
	}
	else if('flag == 6) {
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios1")),"ヒシエ : 私も先に行く。みんなも後から来てくれ！";
		sleep 3000;
		hideonnpc getmdnpcname("ヒシエ#bios1");
		hideonnpc getmdnpcname("エイヴァント#bios1");
	}
	else if('flag == 7) {
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b1")),"アバランチェ : ヘスランタ様！　我々も参りましょう！";
		sleep 3000;
		hideonnpc getmdnpcname("大臣ヘスランタ#bios1");
		hideonnpc getmdnpcname("先発隊長アバランチェ#b1");
	}
	sleep 500;
	hideonnpc getmdnpcname("#BARRICADE_bios1_1");
	hideonnpc getmdnpcname("#BARRICADE_bios1_2");
	hideonnpc getmdnpcname("#BARRICADE_bios1_3");
	hideonnpc getmdnpcname("#BARRICADE_bios1_4");
	hideonnpc getmdnpcname("#BARRICADE_bios1_5");
	hideonnpc getmdnpcname("#BARRICADE_bios1_6");
	hideonnpc getmdnpcname("#BARRICADE_bios1_7");
	hideonnpc getmdnpcname("#BARRICADE_bios1_8");
	areasetcell getmdmapname("1@dth1.gat"),84,90,85,97,0;
	sleep 2500;
	announce "死神アンク : 死、それは生ある者のみに訪れる恐怖。すべてはここから始まるのです……", 0x9, 0xffff00;
	sleep 3000;
	announce "ブリド : 待てアンク！　くそっ、東に逃げたようだな。奴を追うぞ！", 0x9, 0xffff00;
	end;
}
1@dth1.gat,60,96,5	script	司令官アジフ#bios1	459,{
	cutin "ep13_captin_edq.bmp", 2;
	mes "[アジフ]";
	mes "久しぶりの前線だ。";
	mes "傭兵の血が騒ぐな。";
	mes strcharinfo(0)+"も";
	mes "よろしく頼むぜ。";
	close2;
	cutin "ep13_captin_edq.bmp", 255;
	end;
}
1@dth1.gat,60,93,5	script	教官長イグリド#bios1	751,{
	mes "[イグリド]";
	mes "まったく……。";
	mes "兄貴は何を考えてるんだ。";
	close;
}
1@dth1.gat,60,96,5	script	キド#bios1	884,{
	mes "[キド]";
	mes "ここから先は何があるかわからない。";
	mes "気を抜くんじゃないぞ。";
	close;
}
1@dth1.gat,60,93,5	script	リーン#bios1	885,{
	mes "[リーン]";
	mes "この島、何か嫌な感じがする。";
	mes "何が起こるかわからないから";
	mes "気を付けてね。";
	close;
}
1@dth1.gat,60,96,5	script	連合軍事務官#bios1	754,{
	mes "[セルザン]";
	mes "ほ、本当は怖いですけど";
	mes "私も何かお役にたちたいんです！";
	close;
}
1@dth1.gat,60,93,5	script	リョースン#bios1	748,{
	mes "[リョースン]";
	mes "どどど、どうしてこんなことに……。";
	mes "ああ、逃げ出したい……。";
	close;
}
1@dth1.gat,58,95,5	script	ヒュー#bios1	868,{
	mes "[ヒュー]";
	mes "は、はは、まさか最前線に来るとは";
	mes "予想外でしたよ。";
	close;
}
1@dth1.gat,58,92,5	script	ヘンジヌ#bios1	931,{
	mes "[ヘンジヌ]";
	mes "種に入ったら島に出るなんて";
	mes "こりゃあ、まいっ種";
	mes "なんてね";
	mes "アハハハハハ！";
	close;
}
1@dth1.gat,60,96,5	script	ヒシエ#bios1	623,{
	cutin "hisie01.bmp", 2;
	mes "[ヒシエ]";
	mes "こうしている間にもカルは……";
	mes "先を急ごう！";
	close2;
	cutin "hisie01.bmp", 255;
	end;
}
1@dth1.gat,60,93,5	script	エイヴァント#bios1	618,{
	cutin "avant01.bmp", 2;
	mes "[エイヴァント]";
	mes "ククク、私に何か用かな？";
	mes "実験体になりたいなら";
	mes "いつでも歓迎するぞ？";
	close2;
	cutin "avant01.bmp", 255;
	end;
}
1@dth1.gat,60,96,5	script	大臣ヘスランタ#bios1	451,{
	cutin "ep13_heslanta.bmp", 2;
	mes "[ヘスランタ]";
	mes "荒事に関しては";
	mes "あまり得意ではないのですが";
	mes "サファ族の代表として";
	mes "尽力致しましょう！";
	close2;
	cutin "ep13_heslanta.bmp", 255;
	end;
}
1@dth1.gat,60,93,5	script	先発隊長アバランチェ#b1	450,{
	mes "[アバランチェ]";
	mes "この先に待ち構えるのは";
	mes "並大抵の相手ではないでしょう。";
	mes "先発隊長の名にかけて";
	mes "ヘスランタ様は私が守ります。";
	close;
}

1@dth1.gat,326,103,0	script	warp1#bios1	45,1,1,{
	warp getmdmapname("1@dth2.gat"),17,93;
	end;
}

1@dth2.gat,150,126,0	script	#BARRICADE_bios2_1	1905,{}
1@dth2.gat,150,127,0	script	#BARRICADE_bios2_2	1905,{}
1@dth2.gat,150,128,0	script	#BARRICADE_bios2_3	1905,{}
1@dth2.gat,150,129,0	script	#BARRICADE_bios2_4	1905,{}
1@dth2.gat,150,130,0	script	#BARRICADE_bios2_5	1905,{}
1@dth2.gat,150,131,0	script	#BARRICADE_bios2_6	1905,{}
1@dth2.gat,150,132,0	script	#BARRICADE_bios2_7	1905,{}
1@dth2.gat,150,133,0	script	#BARRICADE_bios2_8	1905,{}

1@dth2.gat,1,1,0	script	#bios2_mobdead1	139,{
OnStart:
	monster getmdmapname("1@dth2.gat"),145,130,"生者のオークウォリアー",3013,5,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),144,130,"生者のデザートウルフ",3014,4,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),143,130,"生者のフェン",3015,4,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),103,124,"生者のオークウォリアー",3013,5,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),102,124,"生者のデザートウルフ",3014,3,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),101,124,"生者のフェン",3015,3,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),119,160,"生者のオークウォリアー",3013,5,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),118,160,"生者のデザートウルフ",3014,4,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),117,160,"生者のフェン",3015,4,getmdnpcname("#bios2_mobdead1")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer500:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@dth2.gat"),getmdnpcname("#bios2_mobdead1")+ "::OnKilled");
	if('@count == 10)
		announce "ブリド : まだ10匹のモンスターが残っているぞ！", 0x9, 0xffff00;
	else if('@count == 5)
		announce "ブリド : 残りのモンスターはあと5匹、もう少しだ！", 0x9, 0xffff00;
	else if('@count == 1)
		announce "ブリド : モンスターはあと1匹だ。最後まで気を抜くな！", 0x9, 0xffff00;
	else if('@count <= 0) {
		hideonnpc getmdnpcname("#BARRICADE_bios2_1");
		hideonnpc getmdnpcname("#BARRICADE_bios2_2");
		hideonnpc getmdnpcname("#BARRICADE_bios2_3");
		hideonnpc getmdnpcname("#BARRICADE_bios2_4");
		hideonnpc getmdnpcname("#BARRICADE_bios2_5");
		hideonnpc getmdnpcname("#BARRICADE_bios2_6");
		hideonnpc getmdnpcname("#BARRICADE_bios2_7");
		hideonnpc getmdnpcname("#BARRICADE_bios2_8");
		areasetcell getmdmapname("1@dth2.gat"),150,126,151,133,0;
		announce "ブリド : よし！　橋の封鎖がとけた！　奥に移動するぞ！", 0x9, 0xffff00;
		sleep 2500;
		donpcevent getmdnpcname("#bios2_mobdead2")+ "::OnStart";
	}
	end;
}
1@dth2.gat,1,1,0	script	#bios2_mobdead2	139,{
OnStart:
	announce "ブリド : くそっ！　奥もモンスターだらけだ。全て倒すしかないのか！", 0x9, 0xffff00;
	monster getmdmapname("1@dth2.gat"),203,132,"生者のオークウォリアー",3013,5,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),202,132,"生者のデザートウルフ",3014,3,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),201,132,"生者のフェン",3015,3,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),229,126,"生者のオークウォリアー",3013,5,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),228,126,"生者のデザートウルフ",3014,4,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),227,126,"生者のフェン",3015,4,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),267,104,"生者のオークウォリアー",3013,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),268,104,"生者のフェン",3015,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),269,104,"生者のオークウォリアー",3013,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),270,103,"生者のデザートウルフ",3014,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),270,104,"生者のフェン",3015,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),272,102,"生者のフェン",3015,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),273,102,"生者のデザートウルフ",3014,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),273,103,"生者のデザートウルフ",3014,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),274,102,"生者のオークウォリアー",3013,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),275,103,"生者のフェン",3015,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),276,103,"生者のデザートウルフ",3014,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),278,105,"生者のオークウォリアー",3013,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	monster getmdmapname("1@dth2.gat"),281,104,"生者のオークウォリアー",3013,1,getmdnpcname("#bios2_mobdead2")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer500:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@dth2.gat"),getmdnpcname("#bios2_mobdead2")+ "::OnKilled");
	if('@count == 10)
		announce "ブリド : まだ10匹のモンスターが残っているぞ！", 0x9, 0xffff00;
	else if('@count == 5)
		announce "ブリド : 残りのモンスターはあと5匹、もう少しだ！", 0x9, 0xffff00;
	else if('@count == 1)
		announce "ブリド : モンスターはあと1匹だ！", 0x9, 0xffff00;
	else if('@count <= 0) {
		announce "ブリド : よし、片付いたぞ！　島の東から先に進むぞ！", 0x9, 0xffff00;
		hideoffnpc getmdnpcname("warp1#bios2");
	}
	end;
}
1@dth2.gat,67,97,0	script	start1#bios2	139,5,5,{
	hideonnpc getmdnpcname("start1#bios2");
	donpcevent getmdnpcname("#bios2_mobdead")+ "::OnStart";
	switch(getvariableofnpc('flag,getmdnpcname("ブリド#bios1"))) {
	case 3:
		announce "アジフ : ふん、この程度の敵、俺の相手じゃねえな。", 0x9, 0xffff00;
		sleep 3000;
		announce "イグリド : こうして兄貴と背中合わせで戦ってると傭兵時代を思い出すよ。", 0x9, 0xffff00;
		break;
	case 4:
		announce "キド : リーン！　大丈夫か!?", 0x9, 0xffff00;
		sleep 3000;
		announce "リーン : 私は大丈夫。このまま進みましょう！", 0x9, 0xffff00;
		break;
	case 5:
		announce "ブリド : あの4人組の姿が見えないな……。", 0x9, 0xffff00;
		sleep 3000;
		announce "ブリド : やはり、この戦いには力不足だったか……。", 0x9, 0xffff00;
		break;
	case 6:
		announce "ヒシエ : 見た目によらず……こいつら結構強いな。", 0x9, 0xffff00;
		sleep 3000;
		announce "エイヴァント : ククク、何なら人体強化の実験体にでもしてやろうか？", 0x9, 0xffff00;
		break;
	case 7:
		announce "ヘスランタ : サファ族の意地にかけて、負けられないのです！", 0x9, 0xffff00;
		sleep 3000;
		announce "アバランチェ : ヘスランタ様！　ご無理なさらず！", 0x9, 0xffff00;
		break;
	}
	donpcevent getmdnpcname("BC用#bios2")+ "::OnStart";
	end;
}
1@dth2.gat,67,97,0	script	BC用#bios2	139,{
OnStart:
	sleep 3000;
	announce "死神アンク : ククク。怯えなさい人間。", 0x9, 0xffff00;
	sleep 3000;
	announce "死神アンク : 成長の終着点とは、すなわち深淵。", 0x9, 0xffff00;
	sleep 3000;
	announce "死神アンク : 死を迎え、冥府へと落ちてしまえば", 0x9, 0xffff00;
	sleep 3000;
	announce "死神アンク : 物語と違い、貴方の手を引く吟遊詩人は現れない。", 0x9, 0xffff00;
	sleep 3000;
	announce "死神アンク : さあ、死に怯えなさい。心を恐怖に染め上げるのです。", 0x9, 0xffff00;
	sleep 3000;
	announce "死神アンク : 恐怖は贄となり、モロク様は再び生まれ変わるでしょう。", 0x9, 0xffff00;
	sleep 3000;
	announce "ブリド : 待つんだアンク!!　くそっ。まずは邪魔なモンスター達を全て倒すぞ！", 0x9, 0xffff00;
	end;
}
1@dth2.gat,326,103,0	script	warp1#bios2	45,1,1,{
	warp getmdmapname("1@dth3.gat"),45,68;
	end;
}

1@dth3.gat,62,80,3	script	死者のオークゾンビ#11bi	3016,{}
1@dth3.gat,64,80,3	script	死者のオークゾンビ#12bi	3016,{}
1@dth3.gat,66,80,3	script	死者のオークゾンビ#13bi	3016,{}
1@dth3.gat,68,80,3	script	死者のオークゾンビ#14bi	3016,{}
1@dth3.gat,72,80,3	script	死者のオークゾンビ#15bi	3016,{}
1@dth3.gat,74,80,3	script	死者のオークゾンビ#16bi	3016,{}
1@dth3.gat,76,80,3	script	死者のオークゾンビ#17bi	3016,{}
1@dth3.gat,78,80,3	script	死者のオークゾンビ#18bi	3016,{}
1@dth3.gat,62,86,3	script	死者のオークゾンビ#21bi	3016,{}
1@dth3.gat,64,86,3	script	死者のオークゾンビ#22bi	3016,{}
1@dth3.gat,66,86,3	script	死者のオークゾンビ#23bi	3016,{}
1@dth3.gat,68,86,3	script	死者のオークゾンビ#24bi	3016,{}
1@dth3.gat,72,86,3	script	死者のオークゾンビ#25bi	3016,{}
1@dth3.gat,74,86,3	script	死者のオークゾンビ#26bi	3016,{}
1@dth3.gat,76,86,3	script	死者のオークゾンビ#27bi	3016,{}
1@dth3.gat,78,86,3	script	死者のオークゾンビ#28bi	3016,{}
1@dth3.gat,62,92,3	script	死者のオークゾンビ#31bi	3016,{}
1@dth3.gat,64,92,3	script	死者のオークゾンビ#32bi	3016,{}
1@dth3.gat,66,92,3	script	死者のオークゾンビ#33bi	3016,{}
1@dth3.gat,68,92,3	script	死者のオークゾンビ#34bi	3016,{}
1@dth3.gat,72,92,3	script	死者のオークゾンビ#35bi	3016,{}
1@dth3.gat,74,92,3	script	死者のオークゾンビ#36bi	3016,{}
1@dth3.gat,76,92,3	script	死者のオークゾンビ#37bi	3016,{}
1@dth3.gat,78,92,3	script	死者のオークゾンビ#38bi	3016,{}

1@dth3.gat,72,74,3	script	ジェイス#bios3	467,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 10) {
		mes "[ジェイス]";
		mes "……無事だったか。";
		mes "ここが最深部のようだ。";
		close;
	}
	if('@flag < 30) {
		mes "[ジェイス]";
		mes "くっ、体が……。";
		close;
	}
	mes "[ジェイス]";
	mes "……どうやら俺たちは、";
	mes "自分の力を過信していたようだ。";
	next;
	mes "[ジェイス]";
	mes "……おかげで命拾いをしたよ。";
	mes "ありがとう。";
	close;
}
1@dth3.gat,70,67,3	script	死神アンク#bios3	3029,{}
1@dth3.gat,64,74,5	script	ブリド#bios3	468,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 10) {
		if(getnpctimer(1)) {
			mes "[ブリド]";
			mes "無事でよかった。";
			mes "ここが最深部のようだが";
			mes "あの死神の姿が見えないな。";
			close;
		}
		if(checkquest(201720)) {
			if(select("先を急ぐ","会話をする") ==1) {
				donpcevent getmdnpcname("#bios3_talkshow")+ "::OnStart";
				close;
			}
		}
		initnpctimer;
		close;
	}
	if('@flag < 30) {
		mes "[ブリド]";
		mes "くっ、体が……！";
		mes "ここまで……なのか……！";
		close;
	}
	mes "[ブリド]";
	mes "すまないな、助かったよ。";
	mes "私が道中で拾ったこの";
	mes "^ff0000勇者の証^000000は";
	mes "君にこそ相応しいアイテムだ。";
	mes "是非受け取ってくれ。";
	next;
	mes "[ブリド]";
	mes "さぁ、早くこの気分の悪い場所から";
	mes "出ようぜ!!";
	close2;
	if(checkitemblank() == 0) {
		mes "‐アイテムの種類数が多くて";
		mes "　持つことができない。";
		mes "　種類数を減らしてから受け取ろう‐";
		close;
	}
	if(checkquest(96430) & 0x4) {
		compquest 96430;
		if(BaseLevel < 160) {
			set '@base,7500000 + 500000 * 'users;
			if('users >= 12) set '@base,'@base + 500000;
		}
		else {
			set '@base,20000000 + 2000000 * 'users;
			if('users >= 12) set '@base,'@base + 2000000;
		}
		set '@job,3000000 + 200000 * 'users;
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
	if(checkquest(116513)==0) {
		setquest 116513;
		compquest 116513;
	}
	if(checkquest(96430) & 0x8)
		getitem 6684, 1;
	if(checkquest(201720)==0)
		setquest 201720;
	if(BIOS_1QUE==0)
		set BIOS_1QUE,'users;
	warp "moro_cav.gat",45,63;
	end;
OnTimer1000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : おっ、君も着いたか。";
	end;
OnTimer4000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : 気になるな……。";
	end;
OnTimer7000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : ん？　どうしたジェイス？";
	end;
OnTimer10000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : モンスターが、少しずつ成長していた。それに、周りも既に暗くなってきている。";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : 時間の経過がおかしい。アンクが言っていた事と何か関係があるのか……。";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 確かに……！";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : 警戒が必要だ。";
	end;
OnTimer22000:
	hideoffnpc getmdnpcname("死神アンク#bios3");
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : クククク……。";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 出たな貴様ッ！　さっさとこっちへ来い！";
	end;
OnTimer28000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : そう、ここは死を祀る生の世界。";
	end;
OnTimer31000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : モロク様は死を迎え、魔神へと転生なさる為の贄を欲しているのです。";
	end;
OnTimer34000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : モロク様が欲する贄とは何か……気になりますか？";
	end;
OnTimer37000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク……出でよ！　私の部下達よ！";
	misceffect 35,getmdnpcname("死神アンク#bios3");
	end;
OnTimer40000:
	for(set '@i,1; '@i<=3; set '@i,'@i+1) {
		for(set '@j,1; '@j<=8; set '@j,'@j+1)
			hideoffnpc getmdnpcname("死者のオークゾンビ#"+ '@i + '@j +"bi");
	}
	end;
OnTimer43000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 御託はいい！　下っ端の相手などしていられるか！";
	end;
OnTimer46000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 私が直接お前を倒してやる！";
	end;
OnTimer49000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク。威勢が良いですね。しかし……残念ながらお別れの時間です。";
	end;
OnTimer52000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : その身に死が這い寄る恐怖を……とくと味わいなさい！";
	end;
OnTimer55000:
	misceffect 89,getmdnpcname("死神アンク#bios3");
	misceffect 134,getmdnpcname("ジェイス#bios3");
	misceffect 134,getmdnpcname("ブリド#bios3");
	misceffect 51,getmdnpcname("ジェイス#bios3");
	misceffect 51,getmdnpcname("ブリド#bios3");
	setnpcdisplay getmdnpcname("ブリド#bios3"),10036;
	setnpcdisplay getmdnpcname("ジェイス#bios3"),10035;
	hideoffnpc getmdnpcname("freeze#bios3");
	set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
	end;
OnTimer58000:
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : なっ、なんだ!?　体が……体が動かない?!";
	end;
OnTimer61000:
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : ……!!　体が……！";
	end;
OnTimer64000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : どうですか気分は。ククククク。";
	end;
OnTimer67000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ここまであなた達は私の部下達が急速に成長する姿を見たでしょう。";
	end;
OnTimer70000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ご覧なさい、今ここにいる部下達を。";
	end;
OnTimer73000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : 彼らは死を迎え、その魂はモロク様が転生する為の贄となるのです。";
	end;
OnTimer76000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : おやおや、私の術を解くとは……思ったよりやるようですね。";
	end;
OnTimer79000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : まあ、いいでしょう。次は……あなた達の番です。";
	end;
OnTimer82000:
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : それでは、愚かな冒険者様。冥府への旅路に憂い無きよう……。ククク。";
	hideonnpc getmdnpcname("freeze#bios3");
	end;
OnTimer85000:
	stopnpctimer;
	for(set '@i,1; '@i<=3; set '@i,'@i+1) {
		for(set '@j,1; '@j<=8; set '@j,'@j+1)
			hideonnpc getmdnpcname("死者のオークゾンビ#"+ '@i + '@j +"bi");
	}
	hideonnpc getmdnpcname("死神アンク#bios3");
	donpcevent getmdnpcname("#bios3_mobdead")+ "::OnStart";
	end;
}
1@dth3.gat,66,72,0	script	#bios3_mobdead	139,{
OnStart:
	set '@mdmap$,getmdmapname("1@dth3.gat");
	set '@mdnpc$,getmdnpcname("#bios3_mobdead")+ "::OnKilled1";
	for(set '@y,80;'@y<=92;set '@y,'@y+6) {
		for(set '@x,62;'@x<=78;set '@x,'@x+2) {
			if('@x != 70)
				monster '@mdmap$,'@x,'@y,"死者のオークゾンビ",3016,1,'@mdnpc$;
		}
	}
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("1@dth3.gat"),getmdnpcname("#bios3_mobdead")+ "::OnKilled1");
	if('@count > 0) end;
	sleep 500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 凄いな！　全部倒したのか？";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : まだだ……気を付けろ！";
	sleep 1000;
	set '@mdmap$,getmdmapname("1@dth3.gat");
	set '@mdnpc$,getmdnpcname("#bios3_mobdead")+ "::OnKilled2";
	for(set '@y,80;'@y<=92;set '@y,'@y+6) {
		for(set '@x,62;'@x<=78;set '@x,'@x+2) {
			if('@x != 70)
				monster '@mdmap$,'@x,'@y,"死者のベリット",3017,1,'@mdnpc$;
		}
	}
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("1@dth3.gat"),getmdnpcname("#bios3_mobdead")+ "::OnKilled2");
	if('@count > 0) end;
	sleep 500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 今度こそ全部倒したんだよな？";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : 残念ながらまだのようだ……！";
	sleep 1000;
	set '@mdmap$,getmdmapname("1@dth3.gat");
	set '@mdnpc$,getmdnpcname("#bios3_mobdead")+ "::OnKilled3";
	for(set '@y,80;'@y<=92;set '@y,'@y+6) {
		for(set '@x,62;'@x<=78;set '@x,'@x+2) {
			if('@x != 70)
				monster '@mdmap$,'@x,'@y,"死者のメガロドン",3018,1,'@mdnpc$;
		}
	}
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("1@dth3.gat"),getmdnpcname("#bios3_mobdead")+ "::OnKilled3");
	if('@count > 0) end;
	//hideonnpc "#bios3_mobdead";
	hideoffnpc getmdnpcname("死神アンク#bios3");
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag == 13) {
		hideoffnpc getmdnpcname("司令官アジフ#bios3");
		hideoffnpc getmdnpcname("教官長イグリド#bios3");
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios3")),"アジフ : ようやく追いついたぜ、お前ら無事か！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios3")),"イグリド : さっさと片付けようぜ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios3")),"アジフ : うおおおおおおお！";
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios3")),"イグリド : はあああああああ！";
		misceffect 12,getmdnpcname("司令官アジフ#bios3");
		misceffect 12,getmdnpcname("教官長イグリド#bios3");
		sleep 1500;
		misceffect 226,getmdnpcname("死神アンク#bios3");
		misceffect 245,getmdnpcname("死神アンク#bios3");
		sleep 3000;
		announce "‐死神アンクの体力が大きく減少した‐", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……まさか、この私に手傷を負わせるとは……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : そうですね……あなた方にはこういうのはいかがでしょう。";
		sleep 3000;
		misceffect 23,getmdnpcname("司令官アジフ#bios3");
		misceffect 23,getmdnpcname("教官長イグリド#bios3");
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("司令官アジフ#bios3")),"アジフ : 体が動かない!?　こ、声も……！";
		sleep 1000;
		unittalk getnpcid(0,getmdnpcname("教官長イグリド#bios3")),"イグリド : 体が……石に！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク、物言わぬ石となり、己の無力を永遠に嘆き続けなさい。";
		sleep 4000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : さて、そこの冒険者のあなた。";
	}
	else if('@flag == 14) {
		hideoffnpc getmdnpcname("キド#bios3");
		hideoffnpc getmdnpcname("リーン#bios3");
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios3")),"キド : 遅くなってすまない！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("リーン#bios3")),"リーン : キド、行くよ！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios3")),"キド : うおおおおおおお！";
		unittalk getnpcid(0,getmdnpcname("リーン#bios3")),"リーン : はあああああああ！";
		misceffect 12,getmdnpcname("キド#bios3");
		misceffect 12,getmdnpcname("リーン#bios3");
		sleep 3000;
		announce "‐死神アンクの体力が大きく減少した‐", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……まさか、この私に手傷を負わせるとは……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : そうですね……あなた方にはこういうのはいかがでしょう。";
		sleep 3000;
		misceffect 23,getmdnpcname("キド#bios3");
		misceffect 23,getmdnpcname("リーン#bios3");
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("キド#bios3")),"キド : か、体が石に……！　リーン！　大丈夫か!?";
		sleep 1000;
		unittalk getnpcid(0,getmdnpcname("リーン#bios3")),"リーン : くっ……声が……！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク、物言わぬ石となり、己の無力を永遠に嘆き続けなさい。";
		sleep 4000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : さて、そこの冒険者のあなた。";
	}
	else if('@flag == 15) {
		announce "セルザン : 食らええええええええ！", 0x9, 0xffff00;
		sleep 3000;
		misceffect 106,getmdnpcname("死神アンク#bios3");
		misceffect 107,getmdnpcname("死神アンク#bios3");
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
		sleep 3000;
		announce "‐死神アンクの体力が大きく減少した‐", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……一体何事ですか！";
		sleep 3000;
		announce "ヘンジヌ : き、効いた！", 0x9, 0xffff00;
		sleep 3000;
		announce "リョースン : さすがドランスさんに作ってもらった、新型爆薬！", 0x9, 0xffff00;
		sleep 3000;
		announce "ヒュー : ドランス式対大型モンスター擲弾だっけ？", 0x9, 0xffff00;
		sleep 3000;
		announce "セルザン : 早く！　今のうちに逃げますよ！", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : やってくれましたね……まぁいいでしょう。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : あの方たちは後でじっくり処分するとします。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : さて、そこの冒険者のあなた。";
	}
	else if('@flag == 16) {
		hideoffnpc getmdnpcname("ヒシエ#bios3");
		hideoffnpc getmdnpcname("エイヴァント#bios3");
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios3")),"ヒシエ : よし、どうにか間に合ったみたいだな。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios3")),"エイヴァント : まだ片付けてなかったのか。……まあいい、私の力を見せてやろう。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios3")),"ヒシエ : うおおおおおおお！";
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios3")),"エイヴァント : はあああああああ！";
		misceffect 12,getmdnpcname("ヒシエ#bios3");
		misceffect 12,getmdnpcname("エイヴァント#bios3");
		sleep 1500;
		misceffect 30,getmdnpcname("死神アンク#bios3");
		misceffect 89,getmdnpcname("死神アンク#bios3");
		sleep 3000;
		announce "‐死神アンクの体力が大きく減少した‐", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……まさか、この私に手傷を負わせるとは……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : そうですね……あなた方にはこういうのはいかがでしょう。";
		sleep 3000;
		misceffect 23,getmdnpcname("ヒシエ#bios3");
		misceffect 23,getmdnpcname("エイヴァント#bios3");
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("ヒシエ#bios3")),"ヒシエ : 体が動かない……!?　こ、声も……。";
		sleep 1000;
		unittalk getnpcid(0,getmdnpcname("エイヴァント#bios3")),"エイヴァント : くっ、石化か……小賢しい真似を……！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク、物言わぬ石となり、己の無力を永遠に嘆き続けなさい。";
		sleep 4000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : さて、そこの冒険者のあなた。";
	}
	else if('@flag == 17) {
		hideoffnpc getmdnpcname("大臣ヘスランタ#bios3");
		hideoffnpc getmdnpcname("先発隊長アバランチェ#b3");
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios3")),"ヘスランタ : みなさん、ご無事でしたか!?";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b3")),"アバランチェ : 先発隊長アバランチェ、参ります！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios3")),"ヘスランタ : はあああああああ！";
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b3")),"アバランチェ : ぬおおおおおおお！";
		misceffect 12,getmdnpcname("大臣ヘスランタ#bios3");
		misceffect 12,getmdnpcname("先発隊長アバランチェ#b3");
		sleep 1500;
		misceffect 17,getmdnpcname("死神アンク#bios3");
		misceffect 79,getmdnpcname("死神アンク#bios3");
		sleep 3000;
		announce "‐死神アンクの体力が大きく減少した‐", 0x9, 0xffff00;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……まさか、この私に手傷を負わせるとは……。";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : そうですね……あなた方にはこういうのはいかがでしょう。";
		sleep 1000;
		misceffect 23,getmdnpcname("大臣ヘスランタ#bios3");
		misceffect 23,getmdnpcname("先発隊長アバランチェ#b3");
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("大臣ヘスランタ#bios3")),"ヘスランタ : 体が石に……!?　声まで……！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("先発隊長アバランチェ#b3")),"アバランチェ : 病の進行……？　いや、違……！";
		sleep 3000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : ククク、物言わぬ石となり、己の無力を永遠に嘆き続けなさい。";
		sleep 4000;
		unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : さて、そこの冒険者のあなた。";
	}
	else
		set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : あなたは久しぶりに楽しめそうな方ですね。";
	sleep 3000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : 特別に、私が直接お相手しましょう!!";
	sleep 1500;
	hideonnpc getmdnpcname("死神アンク#bios3");
	set 'mob_id,callmonster(getmdmapname("1@dth3.gat"),70,67,"死神アンク",3029,getmdnpcname("#bios3_mobdead")+ "::OnBossKilled");
	if('@flag >= 13) {
		set '@mobhp,getmobhp('mob_id);
		set '@mobhp,'@mobhp - ('@mobhp * 20 / 100);
		setmobhp 'mob_id,'@mobhp;
	}
	donpcevent getmdnpcname("talkshow#bios3")+ "::OnStart";
	end;
OnBossKilled:
	stopnpctimer getmdnpcname("talkshow#bios3");
	sleep 1500;
	hideoffnpc getmdnpcname("死神アンク#bios3");
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : くっ……なるほど。人間には……強い者もいるのですね。";
	sleep 2000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : しかし……これで終わりだと思わない方がいいですよ。";
	sleep 1000;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : モロク様の復活は目の前まで来ているのです!!　ククク……!!";
	sleep 2000;
	hideonnpc getmdnpcname("死神アンク#bios3");
	misceffect 135, getmdnpcname("ブリド#bios3");
	misceffect 135, getmdnpcname("ジェイス#bios3");
	setnpcdisplay getmdnpcname("ブリド#bios3"),468;
	setnpcdisplay getmdnpcname("ジェイス#bios3"),467;
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : ……あっ!!　やっと体が！";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : くっ……。";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : ふぅ……あの死神の魔力は私とジェイスでは太刀打ちできないほど強力だった。";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 君がいなければ何もできないままやられていただろう。";
	sleep 2500;
	unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : 感謝の気持ちとして渡したい物がある。受け取る準備が出来たら話しかけてくれ。";
	set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),30;
	set getvariableofnpc('users,getmdnpcname("ブリド#bios3")),getmapusers(getmdmapname("1@dth3.gat"));
	end;
}
1@dth3.gat,66,72,0	script	#bios3_talkshow	139,{
OnStart:
	setnpcdisplay getmdnpcname("ジェイス#bios3"),10035;
	setnpcdisplay getmdnpcname("ブリド#bios3"),10036;
	hideoffnpc getmdnpcname("死神アンク#bios3");
	set getvariableofnpc('flag,getmdnpcname("ブリド#bios1")),getvariableofnpc('flag,getmdnpcname("ブリド#bios1")) + 10;
	sleep 1500;
	unittalk getnpcid(0,getmdnpcname("死神アンク#bios3")),"死神アンク : それでは、愚かな冒険者様。冥府への旅路に憂い無きよう……。ククク。";
	sleep 3000;
	hideonnpc getmdnpcname("死神アンク#bios3");
	donpcevent getmdnpcname("#bios3_mobdead")+ "::OnStart";
	end;
}
1@dth3.gat,66,72,5	script	司令官アジフ#bios3	459,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		cutin "ep13_captin_edq.bmp", 2;
		mes "[アジフ]";
		mes "イグリド！";
		mes "一気に勝負を決めるぞ！";
		close2;
		cutin "ep13_captin_edq.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐アジフは石化している‐";
		close;
	}
	cutin "ep13_captin_edq.bmp", 2;
	mes "[アジフ]";
	mes "司令官の仕事をしすぎて";
	mes "腕が鈍っちまったか……。";
	next;
	mes "[アジフ]";
	mes "悪いが俺はここまでみたいだ。";
	mes "司令官が長い間、拠点を留守に";
	mes "するわけにもいかないしな。";
	next;
	mes "[アジフ]";
	mes strcharinfo(0)+ "。";
	mes "あとは任せたぜ。";
	mes "しっかりケリつけてこい。";
	close2;
	cutin "ep13_captin_edq.bmp", 255;
	end;
}
1@dth3.gat,66,72,5	script	キド#bios3	884,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 10) {
		cutin "moc2_kid02.bmp", 2;
		mes "[キド]";
		mes "こんなところで";
		mes "立ち止まってられるか！";
		mes "俺の一撃を食らえ！";
		close2;
		cutin "moc2_kid05.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐キドは石化している‐";
		close;
	}
	cutin "moc2_kid03.bmp", 2;
	mes "[キド]";
	mes "すまない……。";
	mes "助けるつもりが";
	mes "逆に助けられてしまったな。";
	next;
	mes "[キド]";
	mes "リーンが怪我をしたみたいで";
	mes "これ以上の同行は難しいらしい……";
	mes "オレだけでも一緒にいけると";
	mes "いいんだけど……。";
	next;
	cutin "moc2_kid05.bmp", 2;
	mes "[キド]";
	mes "とにかく、今回は助かった。";
	mes "本当にありがとう。";
	close2;
	cutin "moc2_kid05.bmp", 255;
	end;
}
1@dth3.gat,66,72,5	script	ヒシエ#bios3	623,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		cutin "hisie01.bmp", 2;
		mes "[ヒシエ]";
		mes "私はカルの為にも";
		mes "先を急がなきゃならない！";
		mes "悪いが、一撃で終わらせる！";
		close2;
		cutin "hisie01.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐ヒシエは石化している‐";
		close2;
		cutin "hisie01.bmp", 255;
		end;
	}
	cutin "hisie01.bmp", 2;
	mes "[ヒシエ]";
	mes "ありがとう。";
	mes "助かったよ。";
	next;
	mes "[ヒシエ]";
	mes "さすが、敵の本拠地。";
	mes "手ごわい敵ばかりだ……。";
	next;
	mes "[ヒシエ]";
	mes "だが、こうしてる間にも";
	mes "カルは頑張っているんだ。";
	mes "弱気になっちゃダメだな。";
	next;
	mes "[ヒシエ]";
	mes "帰りを待つみんなの為にも";
	mes "先を急ごう。";
	close2;
	cutin "hisie01.bmp", 255;
	end;
}
1@dth3.gat,66,72,5	script	大臣ヘスランタ#bios3	451,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		cutin "ep13_heslanta.bmp", 2;
		mes "[ヘスランタ]";
		mes "サファの民のため、";
		mes "参ります！";
		close2;
		cutin "ep13_heslanta.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐ヘスランタは石化している‐";
		close;
	}
	cutin "ep13_heslanta.bmp", 2;
	mes "[ヘスランタ]";
	mes "くっ……。";
	mes "やはり私では力不足でしたか。";
	next;
	mes "[ヘスランタ]";
	mes "已むを得ません。";
	mes "私は戻る事にします。";
	mes "これ以上は、足手まといに";
	mes "なりかねませんから……。";
	next;
	mes "[ヘスランタ]";
	mes "これから先は、さらに激しい";
	mes "戦いとなるでしょう。";
	mes "どうか、お気をつけて。";
	close2;
	cutin "ep13_heslanta.bmp", 255;
	end;
}
1@dth3.gat,70,72,3	script	教官長イグリド#bios3	751,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		mes "[イグリド]";
		mes "伊達に傭兵はやってないぜ！";
		mes "俺の一撃、食らいな！";
		close;
	}
	if('@flag < 30) {
		mes "‐イグリドは石化している‐";
		close;
	}
	mes "[イグリド]";
	mes "どうやら兄貴は。";
	mes "拠点に戻るらしいな。";
	next;
	mes "[イグリド]";
	mes "俺か？";
	mes "俺はここから先も一緒に行くぜ。";
	mes "あの死神も放っておけないしな。";
	next;
	mes "[イグリド]";
	mes "兄貴の分もしっかり戦うから";
	mes "頼りにしてくれよな！";
	close;
}
1@dth3.gat,70,72,3	script	リーン#bios3	885,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		cutin "moc2_rin01.bmp", 2;
		mes "[リーン]";
		mes "私だって、戦えるのよ！";
		mes "キド、行くよ！";
		close2;
		cutin "moc2_rin03.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐リーンは石化している‐";
		close;
	}
	cutin "moc2_rin03.bmp", 2;
	mes "[リーン]";
	mes "痛っ。";
	mes "まさか、怪我をするなんて";
	mes "訓練が足りなかったかな。";
	next;
	mes "[リーン]";
	mes "私は一旦戻る事にするわ。";
	mes "一緒に行けなくてごめんね。";
	close2;
	cutin "moc2_rin03.bmp", 255;
	end;
}
1@dth3.gat,70,72,3	script	エイヴァント#bios3	618,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		cutin "avant01.bmp", 2;
		mes "[エイヴァント]";
		mes "貴様らの……";
		mes "貴様らのせいで私は！";
		close2;
		cutin "avant01.bmp", 255;
		end;
	}
	if('@flag < 30) {
		mes "‐エイヴァントは石化している‐";
		close2;
		cutin "avant01.bmp", 255;
		end;
	}
	cutin "avant01.bmp", 2;
	mes "[エイヴァント]";
	mes "荒事は苦手とはいえ";
	mes "ここまでコケにされるとはな……";
	mes "まったく、腹立たしい。";
	next;
	mes "[エイヴァント]";
	mes "私は一旦戻ることにしよう。";
	mes "これでも暇ではないのでね。";
	next;
	cutin "avant02.bmp", 2;
	mes "[エイヴァント]";
	mes "君も思う存分、戦ってくると良い。";
	mes "もし倒れてしまったとしても";
	mes "私の実験材料として";
	mes "役立つからな、ククク。";
	close2;
	cutin "avant01.bmp", 255;
	end;
}
1@dth3.gat,70,72,3	script	先発隊長アバランチェ#b3	450,{
	set '@flag,getvariableofnpc('flag,getmdnpcname("ブリド#bios1"));
	if('@flag < 20) {
		mes "[アバランチェ]";
		mes "ヘスランタ様には";
		mes "指一本触れさせんぞ！";
		close;
	}
	if('@flag < 30) {
		mes "‐アバランチェは石化している‐";
		close;
	}
	mes "[アバランチェ]";
	mes "私もヘスランタ様の護衛の為";
	mes "一度戻ります。";
	next;
	mes "[アバランチェ]";
	mes "最後まで助力できず";
	mes "申し訳ありません。";
	mes "どうか、ご武運を。";
	close;
}

1@dth3.gat,69,67,0	script	freeze#bios3	139,30,30,{
	sc_start SC_Freeze,17500,1;
	end;
}

1@dth3.gat,1,1,0	script	talkshow#bios3	139,{
OnStart:
	initnpctimer;
	set 'mob_id,getvariableofnpc('mob_id,getmdnpcname("#bios3_mobdead"));
	end;
OnTimer3000:
	initnpctimer;
	switch(rand(50)) {
	case 0:	unittalk 'mob_id,"死神アンク : 死の恐怖を感じるのです……。"; break;
	case 1: unittalk 'mob_id,"死神アンク : モロク様の復活もそう遠くありません。"; break;
	case 2: unittalk 'mob_id,"死神アンク : この程度のものですか？　人間の力というのは……。"; break;
	case 3: unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド : やばい……体が……。"; break;
	case 4: unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド :  うう……すまない……何の力にもなれない……。"; break;
	case 5: unittalk getnpcid(0,getmdnpcname("ブリド#bios3")),"ブリド :  俺たちの分まで頑張ってくれ！"; break;
	case 6: unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : くっ……私の力はこんなものか……。"; break;
	case 7: unittalk getnpcid(0,getmdnpcname("ジェイス#bios3")),"ジェイス : ……危険な感じがする。怪しい技を使い出したらその場から離れるんだ！"; break;
	}
	end;
}
