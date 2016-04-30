//= Auriga Script ==============================================================
// Ragnarok Online Falicious Okolnir Script	by refis
//= Registry ===================================================================
// $GodSEActivete[] -> 各砦動作状況
//==============================================================================

function	script	GodSEAgitWarp	{
	set '@tag$,substr(getarg(0),0,1);
	set '@num,substr(getarg(0),1,1);
	if('@tag$ == "F") {
		switch('@num) {
		case 1: set '@map$,"arug_cas01.gat"; set '@x,157; set '@y,369; break;
		case 2: set '@map$,"arug_cas02.gat"; set '@x,349; set '@y,355; break;
		case 3: set '@map$,"arug_cas03.gat"; set '@x,321; set '@y,153; break;
		case 4: set '@map$,"arug_cas04.gat"; set '@x,321; set '@y,153; break;
		case 5: set '@map$,"arug_cas05.gat"; set '@x,321; set '@y,153; break;
		}
	}
	else if('@tag$ == "N") {
		switch('@num) {
		case 1: set '@map$,"schg_cas01.gat"; set '@x,369; set '@y,306; break;
		case 2: set '@map$,"schg_cas02.gat"; set '@x,177; set '@y,355; break;
		case 3: set '@map$,"schg_cas03.gat"; set '@x,81;  set '@y,95;  break;
		case 4: set '@map$,"schg_cas04.gat"; set '@x,369; set '@y,306; break;
		case 5: set '@map$,"schg_cas05.gat"; set '@x,369; set '@y,306; break;
		}
	}
	mapwarp "this",'@map$,'@x,'@y;
	return;
}

//============================================================
// 案内人
//------------------------------------------------------------
-	script	案内人#Okolnir	-1,{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	set '@GID, getcastledata('@map$,1);
	if(getcharid(2) != '@GID) {
		mes "[案内人]";
		mes "……見慣れない顔ですね。";
		mes "この砦の持ち主のギルドの方では";
		mes "ないようですね……";
		mes "外部の方ならば、今すぐ";
		mes "出て行かれたほうが良いですよ。";
		close;
	}
	set '@name$,substr('@map$,0,3) + substr('@map$,8,2);
	set '@map$,"que_q" +'@name$+ ".gat";
	if($GodSEActivete['castle] == 0) {
		mes "[案内人]";
		mes "この砦には隠された秘密が多いです。";
		mes "その中のひとつが、";
		mes "『^4D4DFFオーコルニル^000000』の存在です。";
		next;
		switch(select("オーコルニルについて聞く","オーコルニルに行きたい","興味無い")) {
		case 1:
			mes "[案内人]";
			mes "オーコルニルとは……正確には";
			mes "『^0000FF虚像のオーコルニル^000000』と";
			mes "呼ぶようなのですが、実のところどんな";
			mes "存在なのかよく解らないのです。";
			mes "あるヴァルキリーにより維持されている";
			mes "と言われています。";
			next;
			mes "[案内人]";
			mes "ヴァルキリーが戦士たちを試すために";
			mes "用意した場所なのではないかと";
			mes "なんとなく推測しているのですが……";
			mes "あ、でもオーコルニルに入るための";
			mes "条件ならば解っていますよ。";
			next;
			menu "条件？",-;
			mes "[案内人]";
			mes "そうです。";
			mes "ヴァルキリーは強い戦士を好みます。";
			mes "オーコルニルに行くこと然り、";
			mes "ヴァルハラに行くこと然り、";
			mes "ヴァルキリーに認められてこそと";
			mes "言えるでしょう。";
			next;
			mes "[案内人]";
			mes "虚像のオーコルニルが開放される";
			mes "タイミングは、多くの強き人々の";
			mes "力が集まった時なのです。";
			mes "その判断基準は、まさにこの砦に";
			mes "あるのです。";
			next;
			mes "[案内人]";
			mes "砦の^0000FF商業値が65以上、";
			mes "防衛値が30以上^000000の時、";
			mes "オーコルニルに行く事が出来ます。";
			mes "そして、オーコルニルで";
			mes "ヴァルキリーが下す試練に";
			mes "全て打ち勝つことができれば……!!";
			next;
			mes "[案内人]";
			mes "砦から産出される物から";
			mes "何か凄い物を作ってくれると";
			mes "言われています。";
			next;
			mes "[案内人]";
			mes "まあ、一度挑戦してみても";
			mes "良いのではないでしょうか？";
			mes "ふふふ……";
			close;
		case 2:
			mes "[案内人]";
			mes "オーコルニルに行きたいのですか？";
			mes "確認しますから少々お待ちを……";
			next;
			if((GetCastleData('@map$,3) >= 65) && (GetCastleData('@map$,2) >= 30)) {
				mes "[案内人]";
				mes "素晴らしいです！";
				mes "砦の商業値と防衛値が十分条件を";
				mes "満たしています。今ならオーコルニルに";
				mes "行くことができるでしょう。";
				mes "行きますか？";
				next;
				if(select("移動する","やめる") == 2) {
					mes "[案内人]";
					mes "オーコルニルへ行く機会は";
					mes "いつでもあります。";
					mes "あなた方がこの砦を";
					mes "守ることが出来ればの話……";
					mes "ですけどね。";
					close;
				}
				if(countitem(7839) > 0) {
					delitem 7839,countitem(7839);
				}
				mes "[案内人]";
				mes "貴方の願いが叶いますように……";
				close2;
				warp '@map$,346,32;
				end;
			}
			else {
				mes "[案内人]";
				mes "うーん……";
				mes "条件を満たしていないようですね。";
				mes "砦をもっと発展させなければ……";
				close;
			}
		case 3:
			mes "[案内人]";
			mes "そうですか……";
			mes "残念です。";
			close;
		}
	}
	else if($GodSEActivete['castle] == 1) {
		mes "[案内人]";
		mes "悠長に会話をしている";
		mes "余裕はありませんね。";
		mes "幸運をお祈りします。";
		next;
		if(select("移動する","移動しない") == 2) {
			mes "[案内人]";
			mes "そうですか？";
			mes "残念です。";
			close;
		}
		if(countitem(7839) > 0) {
			delitem 7839,countitem(7839);
		}
		mes "[案内人]";
		mes "貴方の願いが叶いますように……";
		close2;
		warp '@map$,346,32;
		end;
	}
	else if($GodSEActivete['castle] >= 2 && $GodSEActivete['castle] < 14) {
		mes "[案内人]";
		mes "オーコルニルが再構築されるまでには";
		mes "多くの時間を要すると言われています。";
		mes "例えそれが実在しない";
		mes "空間だとしても……です。";
		next;
		mes "[案内人]";
		mes "およそ12時間から13時間ほど";
		mes "かかると考えられています。";
		close;
	}
	else {
		// 未調査
		mes "[案内員]";
		mes "少々お待ちください。";
		close;
	}
OnInit:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if('@map$ == "-")					//duplicate元は何もしない
		end;
	set '@name$,substr(strnpcinfo(2),0,1);
	set '@num,substr(strnpcinfo(2),1,1);
	if('@name$ == "F")
		set 'castle,0;
	else if('@name$ == "N")
		set 'castle,5;
	if('@num > 0)
		set 'castle,'castle+'@num-1;
	if($GodSEActivete['castle] == 1)
		set $GodSEActivete['castle],0;
	end;
}
arug_cas01.gat,161,371,3	duplicate(案内人#Okolnir)	案内人#F1	899
arug_cas02.gat,349,347,3	duplicate(案内人#Okolnir)	案内人#F2	899
arug_cas03.gat,324,161,3	duplicate(案内人#Okolnir)	案内人#F3	899
arug_cas04.gat,324,161,3	duplicate(案内人#Okolnir)	案内人#F4	899
arug_cas05.gat,324,161,3	duplicate(案内人#Okolnir)	案内人#F5	899
schg_cas01.gat,376,307,3	duplicate(案内人#Okolnir)	案内人#N1	899
schg_cas02.gat,181,335,3	duplicate(案内人#Okolnir)	案内人#N2	899
schg_cas03.gat,84,101,3		duplicate(案内人#Okolnir)	案内人#N3	899
schg_cas04.gat,376,307,3	duplicate(案内人#Okolnir)	案内人#N4	899
schg_cas05.gat,376,307,3	duplicate(案内人#Okolnir)	案内人#N5	899

que_qaru01.gat,345,23,0	warp	ゲート02#F1	1,1,arug_cas01.gat,157,369
que_qaru02.gat,345,23,0	warp	ゲート02#F2	1,1,arug_cas02.gat,349,355
que_qaru03.gat,345,23,0	warp	ゲート02#F3	1,1,arug_cas03.gat,321,153
que_qaru04.gat,345,23,0	warp	ゲート02#F4	1,1,arug_cas04.gat,321,153
que_qaru05.gat,345,23,0	warp	ゲート02#F5	1,1,arug_cas05.gat,321,153
que_qsch01.gat,345,23,0	warp	ゲート02#N1	1,1,schg_cas01.gat,369,306
que_qsch02.gat,345,23,0	warp	ゲート02#N2	1,1,schg_cas02.gat,177,355
que_qsch03.gat,345,23,0	warp	ゲート02#N3	1,1,schg_cas03.gat,81,95
que_qsch04.gat,345,23,0	warp	ゲート02#N4	1,1,schg_cas04.gat,369,306
que_qsch05.gat,345,23,0	warp	ゲート02#N5	1,1,schg_cas05.gat,369,306

//============================================================
// クエスト開始NPC
//------------------------------------------------------------
-	script	ウィッシュメイデン#entr	-1,{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	set '@name$,substr('@map$,5,3);
	set '@num,substr('@map$,9,1);
	set '@GID,getcastledata('@name$+"g_cas0"+'@num+".gat",1);
	if(getcharid(2) != '@GID) {
		cutin "wish_maiden23",1;
		mes "[ウィッシュメイデン]";
		mes "……資格無き者は去れ。";
		close2;
		percentheal -100,0;
		cutin "wish_maiden32",255;
		end;
	}
	cutin "wish_maiden31",1;
	if(strcharinfo(0) != getguildmaster('@GID)) {
		cutin "wish_maiden31",1;
		mes "[ウィッシュメイデン]";
		mes "……我は……";
		mes "虚像のオーコルニルで夢を見る者……";
		mes "神々の領域を侵犯しようとする";
		mes "愚かな人間の前に立ち、";
		mes "彼らの声を聞き届ける者……";
		mes "ウィッシュメイデン……";
		next;
		mes "[ウィッシュメイデン]";
		mes "汝をここまで導いた者を";
		mes "連れてくるが良い。";
		mes "その者に我の意思を伝える。";
		close2;
		cutin "wish_maiden32",255;
		end;
	}
	mes "[ウィッシュメイデン]";
	mes "……我は……";
	mes "虚像のオーコルニルで夢を見る者……";
	mes "神々の領域を侵犯しようとする";
	mes "愚かな人間の前に立ち、";
	mes "彼らの声を聞き届ける者……";
	mes "ウィッシュメイデン……";
	next;
	if(
	  ('@name$ == "aru" && countitem(7835) && countitem(7836) && countitem(7837) &&
		countitem(7838) && countitem(2513) && countitem(7291) >= 10 && countitem(7293) >= 10 &&
		countitem(7063) >= 100 && countitem(757) >= 20) ||
	  ('@name$ == "sch" && countitem(7830) && countitem(7831) && countitem(7832) &&
		countitem(7833) && countitem(7834) && countitem(2357) && countitem(7510) >= 100 &&
		countitem(969) >= 10 && countitem(757) >= 20)
	) {
		cutin "wish_maiden11",1;
		mes "[ウィッシュメイデン]";
		mes "準備の整いし者よ。";
		mes ('@name$ == "aru"? "アスプリカ": "ブリュンヒルデ") +"の主たる資格を";
		mes "得んがための試練、";
		mes "受ける覚悟はできているか？";
		next;
		switch(select("どうすれば良いのですか？","後でします")) {
		case 1:
			cutin "wish_maiden12",1;
			mes "[ウィッシュメイデン]";
			mes ('@name$ == "aru"? "アスプリカ": "ブリュンヒルデ") +"の力を授かる資格が";
			mes "あるかどうか、";
			mes "この我が直接試すのだ。";
			mes "オーコルニルの数多の苦難を乗り越え、";
			mes "私を打ち倒せばよい。";
			mes "簡単であろう？";
			next;
			mes "[ウィッシュメイデン]";
			mes "だが、虚像のオーコルニルは";
			mes "文字通り虚像……";
			mes "僅かな過ちも受け入れることはない。";
			mes "^ff0000汝に与えられる時間は1時間だ。^000000";
			next;
			cutin "wish_maiden31",1;
			mes "[ウィッシュメイデン]";
			mes "時間を守ることが出来なければ";
			mes "オーコルニルは崩れ去り、";
			mes "深き眠りにつく……。";
			mes "そうなると汝らは長い間";
			mes "再生を待たねばならぬ。";
			next;
			mes "[ウィッシュメイデン]";
			mes "……さて、汝と共に行く者たちは";
			mes "集まったか？";
			mes "^4d4dff16～20人^000000程度が妥当だ。";
			next;
			cutin "wish_maiden11",1;
			mes "[ウィッシュメイデン]";
			mes "試練を受ける準備が整ったならば、";
			mes "オーコルニルへの門を開こう。";
			next;
			switch(select("全て整いました","もう少し時間が必要です")) {
			case 1:
				set '@saram,getmapusers("this");
				if('@saram > 15 && '@saram < 21) {
					cutin "wish_maiden12",1;
					mes "[ウィッシュメイデン]";
					mes "では、今ここでオーコルニルの";
					mes "門を開く。";
					mes "我はオーコルニルの最も高き場所にて";
					mes "汝らを待つ……";
					next;
					mes "[ウィッシュメイデン]";
					mes "見事試練を乗り越え、";
					mes "オーコルニルが崩れ去る前に";
					mes "我のもとに到達せよ！";
					close2;
					donpcevent "Gate_manager#"+substr(strnpcinfo(2),0,2)+"::OnStart";
					donpcevent "okolnir#"+substr(strnpcinfo(2),0,2)+"::OnStart";
					if('@name$ == "aru")
						set $GodSEActivete['@num-1],1;
					else if('@name$ == "sch")
						set $GodSEActivete[5+'@num-1],1;
					announce "["+ GetGuildName('@GID) +"]ギルドの["+ strcharinfo(0) +"]様により、虚像のオーコルニルが開放されました。",0;
					hideonnpc;
				}
				else {
					cutin "wish_maiden13",1;
					mes "[ウィッシュメイデン]";
					mes "オーコルニルの門を開くならば";
					mes "^FF000016人未満でも20人を越えても";
					mes "ならない。^000000";
					mes "共に行く仲間を整理した上で";
					mes "来るが良い。";
					close2;
				}
				break;
			case 2:
				cutin "wish_maiden13",1;
				mes "[ウィッシュメイデン]";
				mes "……躊躇うことなかれ。";
				mes "機会は目の前にある時に掴むもの。";
				mes "さあ、仲間を集めてくるが良い。";
				close2;
			}
			break;
		case 2:
			cutin "wish_maiden32",1;
			mes "[ウィッシュメイデン]";
			mes "……恐ろしいのか？";
			mes "汝の前に立ち塞がる試練のことが……";
			next;
			cutin "wish_maiden13",1;
			mes "[ウィッシュメイデン]";
			mes "愚かな者よ。";
			mes ('@name$ == "aru"? "アスプリカ": "ブリュンヒルデ") +"の力を";
			mes "簡単に譲るとでも思っていたのか？";
			mes "我、ウィッシュメイデンは";
			mes "汝と、汝と共にある者全てに失望した。";
			mes "退くがいい。";
			close2;
		}
	}
	else {
		// 未調査
		cutin "wish_maiden11",1;
		mes "[ウィッシュメイデン]";
		mes "汝は、中へ至ろうというのか？";
		mes "用意を済ませた者だけが中へと至れる。";
		mes "オーコルニルへ至るにはいくつかの";
		mes "アイテムが必要となるぞ。";
		next;
		if('@name$ == "aru") {
			mes "[ウィッシュメイデン]";
			mes "『黄昏の輝き』";
			mes "『黎明の精髄』";
			mes "『冷たい月明かり』";
			mes "『仄暗い星明かり』。";
			next;
			mes "[ウィッシュメイデン]";
			mes "この4つのアイテムに加え、";
			mes "めのう 10個";
			mes "薔薇水晶 10個";
			mes "エルニウム原石 20個";
			mes "天女の羽衣、および柔らかい羽毛を";
			mes "持ってきてほしい。";
		}
		else {
			mes "[ウィッシュメイデン]";
			mes "『女神の涙』";
			mes "『ヴァルキリーの彫刻』";
			mes "『ブリュンヒルデの鎧の欠片』";
			mes "『英雄の遺灰』";
			mes "『ヴァルキリーアーマー』";
			mes "『アンドヴァリの指輪』。";
			next;
			mes "[ウィッシュメイデン]";
			mes "この6つのアイテムに加え、";
			mes "黄金 10個";
			mes "エルニウム原石 20個を";
			mes "持ってきてほしい。";
			mes "捧げ物として多くの";
			mes "ヴァルハラの花も必要だ。";
		}
		next;
		mes "[ウィッシュメイデン]";
		mes "それら全てが集まれば、門は開く。";
		next;
		mes "[ウィッシュメイデン]";
		mes "…";
		mes "………神の光輝は汝に";
		mes "光を投げかけている。";
		mes "その光に値する強さを";
		mes "汝は持っていよう…";
		next;
		if('@name$ == "aru") {
			mes "[ウィッシュメイデン]";
			mes "柔らかい羽毛は多くの数が必要となる。";
			mes "よく覚えておくがいい…";
			mes "汝の夢が叶わんことを願うぞ…";
		}
		else {
			mes "[ウィッシュメイデン]";
			mes "ヴァルハラの花は";
			mes "多くの数が必要となる。";
			mes "よく覚えておくがいい…";
			mes "汝の夢が叶わんことを願うぞ…";
		}
		next;
		mes "[ウィッシュメイデン]";
		mes "品を持ち帰ることが出来れば";
		mes "我が望みの全てに応えよう。";
		close2;
	}
	cutin "wish_maiden11",255;
	end;
}
que_qaru01.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#F1_e	403
que_qaru02.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#F2_e	403
que_qaru03.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#F3_e	403
que_qaru04.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#F4_e	403
que_qaru05.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#F5_e	403
que_qsch01.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#N1_e	403
que_qsch02.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#N2_e	403
que_qsch03.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#N3_e	403
que_qsch04.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#N4_e	403
que_qsch05.gat,345,82,3	duplicate(ウィッシュメイデン#entr)	ウィッシュメイデン#N5_e	403

-	script	okolnir#Okolnir	-1,{
OnStart:
	set '@name$,strnpcinfo(2);
	donpcevent "ゲート01#"+'@name$+"::OnStart";
	donpcevent "Maze_Manager#"+'@name$+"::OnStart";
	hideoffnpc "event_start01#"+'@name$;
	donpcevent "gd_mobctrl#"+'@name$+"::OnEnable";
	hideoffnpc "影の番人#"+'@name$+"_01";
	hideoffnpc "影の番人#"+'@name$+"_02";
	hideoffnpc "影の番人#"+'@name$+"_03";
	hideoffnpc "影の番人#"+'@name$+"_04";
	hideoffnpc "血の狩人#"+'@name$+"_01";
	hideoffnpc "血の狩人#"+'@name$+"_02";
	hideoffnpc "血の狩人#"+'@name$+"_03";
	hideoffnpc "血の狩人#"+'@name$+"_04";
	hideoffnpc "神殿の守護者#"+'@name$+"_01";
	hideoffnpc "神殿の守護者#"+'@name$+"_02";
	hideonnpc "ウィッシュメイデン#"+'@name$+"_g";
	hideonnpc "to_agit_gate#"+'@name$;
	hideonnpc "jp_jingiwarp01#"+'@name$;
	hideonnpc "jp_jingiwarp02#"+'@name$;
	hideonnpc "jp_jingiwarp03#"+'@name$;
	hideonnpc "jp_jingiwarp04#"+'@name$;
	for(set '@i, 1; '@i <= 8; set '@i, '@i + 1)
		hideonnpc "getspell0"+'@i+"#"+'@name$;
	for(set '@i, 1; '@i <= 6; set '@i, '@i + 1)
		hideonnpc "#"+'@name$+"_cage0"+'@i;
	initnpctimer;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	hideonnpc "ウィッシュメイデン#"+'@name$+"_e";
	donpcevent "gq_miromob2#"+'@name$+"::OnReset";
	hideonnpc "ピアメット#"+'@name$;
	donpcevent "gdtimer01#"+'@name$+"::OnStop";
	donpcevent "gdtimer02#"+'@name$+"::OnStop";
	donpcevent "piamette_ev#"+'@name$+"::OnReset";
	donpcevent "ウィッシュメイデン#"+'@name$+"_b::OnDisable";
	donpcevent "ウィッシュメイデン#"+'@name$+"_g::OnDisable";
	donpcevent "gd_mobctrl#"+'@name$+"::OnReset";
	hideonnpc "ゲート01#"+'@name$;
	donpcevent "Maze_Manager#"+'@name$+"::OnDisable";
	stopnpctimer "event_start01#"+'@name$;
	donpcevent "nm_switch#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin01#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin02#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin03#"+'@name$+"::OnDisable";
	donpcevent "影の番人#"+'@name$+"_01::OnDisable";
	donpcevent "影の番人#"+'@name$+"_02::OnDisable";
	donpcevent "影の番人#"+'@name$+"_03::OnDisable";
	donpcevent "影の番人#"+'@name$+"_04::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_01::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_02::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_03::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_04::OnDisable";
	donpcevent "神殿の守護者#"+'@name$+"_01::OnDisable";
	donpcevent "神殿の守護者#"+'@name$+"_02::OnDisable";
	hideonnpc "to_agit_gate#"+'@name$;
	hideonnpc "#"+'@name$+"_cage01";
	hideonnpc "#"+'@name$+"_cage02";
	hideonnpc "#"+'@name$+"_cage03";
	hideonnpc "#"+'@name$+"_cage04";
	hideonnpc "#"+'@name$+"_cage05";
	hideonnpc "#"+'@name$+"_cage06";
	hideonnpc "windpath03#"+'@name$;
	hideonnpc "windpath04#"+'@name$;
	set getvariableofnpc('gqse_mobcount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_pccount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$),0;
	set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),0;
	stopnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
OnTimer1000:
	announce "ウィッシュメイデン : オーコルニルは1時間後には消滅する。全力を尽くすのだ！",0x9,0x00ff00;
	end;
OnTimer1800000:
	announce "虚像のオーコルニル【維持限界……残り30分】",0x9,0xff0000;
	end;
OnTimer2400000:
	announce "虚像のオーコルニル【維持限界……残り20分】",0x9,0xff0000;
	end;
OnTimer3000000:
	announce "虚像のオーコルニル【維持限界……残り10分】",0x9,0xff0000;
	end;
OnTimer3300000:
	announce "虚像のオーコルニル【維持限界……残り5分】",0x9,0xff0000;
	end;
OnTimer3360000:
	announce "虚像のオーコルニル【維持限界……残り4分】",0x9,0xff0000;
	end;
OnTimer3420000:
	announce "虚像のオーコルニル【維持限界……残り3分】",0x9,0xff0000;
	end;
OnTimer3480000:
	announce "虚像のオーコルニル【維持限界……残り2分】",0x9,0xff0000;
	end;
OnTimer3540000:
	announce "虚像のオーコルニル【維持限界……残り1分】",0x9,0xff0000;
	end;
OnTimer3600000:
	set '@name$,strnpcinfo(2);
	announce "虚像のオーコルニルの崩壊が始まりました。",0x9,0x4d4dff;
	hideonnpc "ウィッシュメイデン#"+'@name$+"_e";
	donpcevent "gq_miromob2#"+'@name$+"::OnReset";
	hideonnpc "ピアメット#"+'@name$;
	donpcevent "gdtimer01#"+'@name$+"::OnStop";
	donpcevent "gdtimer02#"+'@name$+"::OnStop";
	donpcevent "piamette_ev#"+'@name$+"::OnReset";
	donpcevent "ウィッシュメイデン#"+'@name$+"_b::OnDisable";
	donpcevent "ウィッシュメイデン#"+'@name$+"_g::OnDisable";
	donpcevent "gd_mobctrl#"+'@name$+"::OnReset";
	hideonnpc "ゲート01#"+'@name$;
	donpcevent "Maze_Manager#"+'@name$+"::OnDisable";
	stopnpctimer "event_start01#"+'@name$;
	donpcevent "nm_switch#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin01#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin02#"+'@name$+"::OnDisable";
	donpcevent "nmsom_jin03#"+'@name$+"::OnDisable";
	donpcevent "影の番人#"+'@name$+"_01::OnDisable";
	donpcevent "影の番人#"+'@name$+"_02::OnDisable";
	donpcevent "影の番人#"+'@name$+"_03::OnDisable";
	donpcevent "影の番人#"+'@name$+"_04::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_01::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_02::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_03::OnDisable";
	donpcevent "血の狩人#"+'@name$+"_04::OnDisable";
	donpcevent "神殿の守護者#"+'@name$+"_01::OnDisable";
	donpcevent "神殿の守護者#"+'@name$+"_02::OnDisable";
	hideonnpc "to_agit_gate#"+'@name$;
	hideonnpc "#"+'@name$+"_cage01";
	hideonnpc "#"+'@name$+"_cage02";
	hideonnpc "#"+'@name$+"_cage03";
	hideonnpc "#"+'@name$+"_cage04";
	hideonnpc "#"+'@name$+"_cage05";
	hideonnpc "#"+'@name$+"_cage06";
	hideonnpc "windpath03#"+'@name$;
	hideonnpc "windpath04#"+'@name$;
	end;
OnTimer3605000:
	announce "ウィッシュメイデン : ……実に残念だ。我はこれからオーコルニルと共に深き眠りにつく……",0x9,0x00ff00;
	end;
OnTimer3608000:
	announce "ウィッシュメイデン : 勇気を持った者たちよ……深き眠りの底で、再び出会う時を待つ……",0x9,0x00ff00;
	end;
OnTimer3610000:
	set '@name$,strnpcinfo(2);
	set getvariableofnpc('gqse_mobcount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_pccount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$),0;
	set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),0;
	callfunc "GodSEAgitWarp",strnpcinfo(2);
	end;
OnTimer3611000:
	donpcevent "okolnir_time01#"+strnpcinfo(2)+"::OnEnable";
	stopnpctimer;
	end;
}
que_qaru01.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#F1	139
que_qaru02.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#F2	139
que_qaru03.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#F3	139
que_qaru04.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#F4	139
que_qaru05.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#F5	139
que_qsch01.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#N1	139
que_qsch02.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#N2	139
que_qsch03.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#N3	139
que_qsch04.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#N4	139
que_qsch05.gat,1,1,0	duplicate(okolnir#Okolnir)	okolnir#N5	139

//============================================================
// ミスティックガーデンエリア
//------------------------------------------------------------
-	script	ゲート01#Okolnir	-1,{
OnTouch:
	set '@saram,getmapusers("this");
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@saram > 20) {
		// 未調査
		mes "人が多すぎるため入れません。";
		close;
	}
	set '@miro,getvariableofnpc('gqse_mobcount,"Gate_manager#"+strnpcinfo(2));
	if('@miro == getvariableofnpc('gqse_pccount,"Gate_manager#"+strnpcinfo(2))) {
		switch(rand(1,5)) {
		case 1: warp '@map$,72,271; break;
		case 2: warp '@map$,45,243; break;
		case 3: warp '@map$,102,248; break;
		case 4: warp '@map$,102,300; break;
		case 5: warp '@map$,46,300; break;
		}
		end;
	}
	switch('@miro) {
	case 0: setarray '@n, 77,271,72,271,1; break;
	case 1: setarray '@n, 63,278,63,282,2; break;
	case 2: setarray '@n, 63,294,59,294,3; break;
	case 3: setarray '@n, 50,300,46,300,4; break;
	case 4: setarray '@n, 51,280,51,285,5; break;
	case 5: setarray '@n, 51,258,51,262,6; break;
	case 6: setarray '@n, 49,243,45,243,7; break;
	case 7: setarray '@n, 86,249,82,249,8; break;
	case 8: setarray '@n, 102,243,102,248,9; break;
	case 9: setarray '@n, 90,256,90,260,10; break;
	case 10: setarray '@n, 90,283,90,280,11; break;
	case 11: setarray '@n, 102,295,102,300,12; break;
	case 12: setarray '@n, 96,285,96,290,13; break;
	case 13: setarray '@n, 63,278,63,282,14; break;
	case 14: setarray '@n, 65,243,61,243,15; break;
	case 15: setarray '@n, 73,249,70,249,16; break;
	case 16: setarray '@n, 102,275,102,282,17; break;
	case 17: setarray '@n, 70,300,66,300,18; break;
	case 18: setarray '@n, 57,255,57,258,19; break;
	case 19: setarray '@n, 84,277,84,280,20; break;
	}
	switch(getbaseclass(Class,1)) {
	case Job_Swordman: set '@mob,1652; break;
	case Job_Mage:     set '@mob,1663; break;
	case Job_Archer:   set '@mob,1662; break;
	case Job_Acolyte:  set '@mob,1661; break;
	case Job_Merchant: set '@mob,1660; break;
	case Job_Thief:    set '@mob,1659; break;
	default:           set '@mob,1652; break;
	}
	monster '@map$,'@n[0],'@n[1],strcharinfo(0),'@mob,1,"Gate_manager#"+strnpcinfo(2)+"::OnKilled";
	set getvariableofnpc('gqse_mobcount,"Gate_manager#"+strnpcinfo(2)),'@n[4];
	warp '@map$,'@n[2],'@n[3];
	end;

OnStart:
	hideoffnpc;
	areasetcell "this",58,302,63,302,1;
	end;
OnInit:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if('@map$ == "-")					//duplicate元は何もしない
		end;
	hideonnpc;
	end;
}
que_qaru01.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#F1	45,1,1
que_qaru02.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#F2	45,1,1
que_qaru03.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#F3	45,1,1
que_qaru04.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#F4	45,1,1
que_qaru05.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#F5	45,1,1
que_qsch01.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#N1	45,1,1
que_qsch02.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#N2	45,1,1
que_qsch03.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#N3	45,1,1
que_qsch04.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#N4	45,1,1
que_qsch05.gat,346,81,0	duplicate(ゲート01#Okolnir)	ゲート01#N5	45,1,1

-	script	Gate_manager#Okolnir	-1,{
OnStart:
	set 'gqse_mobcount,0;
	set 'gqse_pccount,getmapusers("this");
	end;
OnKilled:
	if('gqse_mobcount == 'gqse_pccount) {
		if(getmapmobs("this",strnpcinfo(0)+"::OnKilled") == 0) {
			donpcevent "gq_miromob2#"+strnpcinfo(2)+"::OnStart";
		}
	}
	end;
}
que_qaru01.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#F1	139
que_qaru02.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#F2	139
que_qaru03.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#F3	139
que_qaru04.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#F4	139
que_qaru05.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#F5	139
que_qsch01.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#N1	139
que_qsch02.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#N2	139
que_qsch03.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#N3	139
que_qsch04.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#N4	139
que_qsch05.gat,1,4,0	duplicate(Gate_manager#Okolnir)	Gate_manager#N5	139

-	script	gq_miromob2#Okolnir	-1,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	announce "ウィッシュメイデン : 汝らの過去の幻影を見てはどうかな？　まだ序の口だ……",0x9,0x00ff00;
	end;
OnTimer6000:
	announce "ウィッシュメイデン : 汝らが進もうとする道は見えるものが全てではない。虚像に騙されるな。",0x9,0x00ff00;
	monster "this",72,271,"セイレン=ウィンザー",1640,1,strnpcinfo(0)+"::OnKilled";
	monster "this",63,282,"カトリーヌ=ケイロン",1645,1,strnpcinfo(0)+"::OnKilled";
	monster "this",59,294,"セシル=ディモン",1644,1,strnpcinfo(0)+"::OnKilled";
	monster "this",46,300,"マーガレッタ=ソリン",1643,1,strnpcinfo(0)+"::OnKilled";
	monster "this",51,285,"エレメス=ガイル",1641,1,strnpcinfo(0)+"::OnKilled";
	monster "this",51,262,"ハワード=アルトアイゼン",1642,1,strnpcinfo(0)+"::OnKilled";

	monster "this",45,243,"セイレン=ウィンザー",1640,1,strnpcinfo(0)+"::OnKilled";
	monster "this",82,249,"カトリーヌ=ケイロン",1645,1,strnpcinfo(0)+"::OnKilled";
	monster "this",102,248,"セシル=ディモン",1644,1,strnpcinfo(0)+"::OnKilled";
	monster "this",90,260,"マーガレッタ=ソリン",1643,1,strnpcinfo(0)+"::OnKilled";
	monster "this",90,280,"エレメス=ガイル",1641,1,strnpcinfo(0)+"::OnKilled";
	monster "this",102,300,"ハワード=アルトアイゼン",1642,1,strnpcinfo(0)+"::OnKilled";

	monster "this",63,282,"セイレン=ウィンザー",1640,1,strnpcinfo(0)+"::OnKilled";
	monster "this",61,243,"カトリーヌ=ケイロン",1645,1,strnpcinfo(0)+"::OnKilled";
	monster "this",70,249,"セシル=ディモン",1644,1,strnpcinfo(0)+"::OnKilled";
	monster "this",102,282,"マーガレッタ=ソリン",1643,1,strnpcinfo(0)+"::OnKilled";
	monster "this",66,300,"エレメス=ガイル",1641,1,strnpcinfo(0)+"::OnKilled";
	monster "this",57,258,"ハワード=アルトアイゼン",1642,1,strnpcinfo(0)+"::OnKilled";
	stopnpctimer;
	end;
OnReset:
	killmonster "this",strnpcinfo(0)+"::OnKilled";
	stopnpctimer;
	end;
OnKilled:
	if(getmapmobs("this",strnpcinfo(0)+"::OnKilled") == 0) {
		announce "ミスティックガーデンの出口が開かれた。",0x9,0x00ff00;
		hideoffnpc "jp_jingiwarp01#"+strnpcinfo(2);
		hideoffnpc "jp_jingiwarp02#"+strnpcinfo(2);
		hideoffnpc "jp_jingiwarp03#"+strnpcinfo(2);
		hideoffnpc "jp_jingiwarp04#"+strnpcinfo(2);
		donpcevent "Maze_Manager#"+strnpcinfo(2)+"::OnDisable";
	}
	end;
}
que_qaru01.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#F1	139
que_qaru02.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#F2	139
que_qaru03.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#F3	139
que_qaru04.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#F4	139
que_qaru05.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#F5	139
que_qsch01.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#N1	139
que_qsch02.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#N2	139
que_qsch03.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#N3	139
que_qsch04.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#N4	139
que_qsch05.gat,1,4,0	duplicate(gq_miromob2#Okolnir)	gq_miromob2#N5	139

-	script	jp_jingiwarp#Okolnir	-1,{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	warp '@map$,60,311;
	end;
}
que_qaru01.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#F1	139,15,15
que_qaru01.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#F1	139,15,15
que_qaru01.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#F1	139,15,15
que_qaru01.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#F1	139,15,15
que_qaru02.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#F2	139,15,15
que_qaru02.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#F2	139,15,15
que_qaru02.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#F2	139,15,15
que_qaru02.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#F2	139,15,15
que_qaru03.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#F3	139,15,15
que_qaru03.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#F3	139,15,15
que_qaru03.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#F3	139,15,15
que_qaru03.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#F3	139,15,15
que_qaru04.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#F4	139,15,15
que_qaru04.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#F4	139,15,15
que_qaru04.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#F4	139,15,15
que_qaru04.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#F4	139,15,15
que_qaru05.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#F5	139,15,15
que_qaru05.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#F5	139,15,15
que_qaru05.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#F5	139,15,15
que_qaru05.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#F5	139,15,15
que_qsch01.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#N1	139,15,15
que_qsch01.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#N1	139,15,15
que_qsch01.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#N1	139,15,15
que_qsch01.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#N1	139,15,15
que_qsch02.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#N2	139,15,15
que_qsch02.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#N2	139,15,15
que_qsch02.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#N2	139,15,15
que_qsch02.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#N2	139,15,15
que_qsch03.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#N3	139,15,15
que_qsch03.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#N3	139,15,15
que_qsch03.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#N3	139,15,15
que_qsch03.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#N3	139,15,15
que_qsch04.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#N4	139,15,15
que_qsch04.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#N4	139,15,15
que_qsch04.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#N4	139,15,15
que_qsch04.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#N4	139,15,15
que_qsch05.gat,55,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp01#N5	139,15,15
que_qsch05.gat,87,285,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp02#N5	139,15,15
que_qsch05.gat,55,255,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp03#N5	139,15,15
que_qsch05.gat,87,258,0	duplicate(jp_jingiwarp#Okolnir)	jp_jingiwarp04#N5	139,15,15

-	script	Maze_Manager#Okolnir	-1,{
OnStart:
	initnpctimer;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	donpcevent "miro_bf#"+'@name$+"::OnDisable";
	donpcevent "miro_rf#"+'@name$+"::OnDisable";
	donpcevent "miro_yf#"+'@name$+"::OnDisable";
	stopnpctimer;
	end;
OnTimer1000:
	donpcevent "miro_rf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer2000:
	donpcevent "miro_yf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer3000:
	donpcevent "miro_bf#"+strnpcinfo(2)+"::OnEnable";
	end;
OnTimer120000:
	donpcevent "miro_bf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer121000:
	donpcevent "miro_yf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer123000:
	donpcevent "miro_rf#"+strnpcinfo(2)+"::OnEnable";
	end;
OnTimer240000:
	donpcevent "miro_bf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer241000:
	donpcevent "miro_rf#"+strnpcinfo(2)+"::OnDisable";
	end;
OnTimer242000:
	donpcevent "miro_yf#"+strnpcinfo(2)+"::OnEnable";
	end;
OnTimer360000:
	donpcevent "Maze_Manager#"+strnpcinfo(2)+"::OnStart";
	end;
}
que_qaru01.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#F1	139
que_qaru02.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#F2	139
que_qaru03.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#F3	139
que_qaru04.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#F4	139
que_qaru05.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#F5	139
que_qsch01.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#N1	139
que_qsch02.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#N2	139
que_qsch03.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#N3	139
que_qsch04.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#N4	139
que_qsch05.gat,1,2,0	duplicate(Maze_Manager#Okolnir)	Maze_Manager#N5	139

-	script	miro_bf#Okolnir	-1,{
	function	Cell;
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 44,270,46,270,50,287,52,287,50,265,52,265,56,279,58,279,64,301,64,298,62,272,64,272,58,245,58,243,72,289,72,287,68,257,68,255,73,263,73,261,75,251,75,249,79,283,79,281,82,271,84,271,89,295,89,293,88,276,90,276,88,266,90,266,94,256,96,256,64,301,64,299,100,251,102,251;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1]," ",1934,1,"miro_bf#"+'@name$+"::OnKilled";
	Cell '@name$,1;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","miro_bf#"+'@name$+"::OnKilled";
	Cell '@name$,0;
	end;
OnKilled:
	end;

	function	Cell	{
		setarray '@cell, 44,270,47,270,50,287,53,287,50,265,53,265,56,279,59,279,64,298,64,301,62,272,65,272,58,242,58,245,72,286,72,289,68,254,68,259,73,260,73,263,75,248,75,251,79,280,79,283,82,271,85,271,89,292,89,295,88,276,91,276,88,266,91,266,94,256,97,256,64,298,64,301,100,251,103,251;
		for (set '@i, 0; '@i < getarraysize('@cell); set '@i, '@i + 4) {
			areasetcell "this",'@cell['@i],'@cell['@i+1],'@cell['@i+2],'@cell['@i+3],getarg(1);
		}
	}
}
que_qaru01.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#F1	139
que_qaru02.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#F2	139
que_qaru03.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#F3	139
que_qaru04.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#F4	139
que_qaru05.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#F5	139
que_qsch01.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#N1	139
que_qsch02.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#N2	139
que_qsch03.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#N3	139
que_qsch04.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#N4	139
que_qsch05.gat,2,1,0	duplicate(miro_bf#Okolnir)	miro_bf#N5	139

-	script	miro_rf#Okolnir	-1,{
	function	Cell;
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 57,301,57,299,48,291,48,289,68,290,70,290,72,295,72,293,90,296,92,296,56,282,58,282,66,283,66,281,80,284,82,284,44,273,46,273,50,273,52,273,54,269,54,267,66,271,66,270,81,273,81,272,88,276,90,276,94,276,96,276,64,258,66,258,76,263,76,261,87,265,87,263,50,252,52,252,76,252,78,252,99,255,99,253,53,245,53,243;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1]," ",1935,1,"miro_rf#"+'@name$+"::OnKilled";
	Cell '@name$,1;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","miro_rf#"+'@name$+"::OnKilled";
	Cell '@name$,0;
	end;
OnKilled:
	end;

	function	Cell	{
		setarray '@cell, 57,298,57,301,48,288,48,291,68,290,71,290,72,292,72,295,90,296,93,296,56,282,59,282,66,280,66,283,80,284,83,284,44,273,47,273,50,273,53,273,54,266,54,269,66,270,66,271,81,272,81,273,88,276,91,276,94,276,97,276,64,258,67,258,76,260,76,263,87,262,87,265,50,252,53,252,76,252,79,252,99,252,99,255,53,242,53,245;
		for (set '@i, 0; '@i < getarraysize('@cell); set '@i, '@i + 4) {
			areasetcell "this",'@cell['@i],'@cell['@i+1],'@cell['@i+2],'@cell['@i+3],getarg(1);
		}
	}
}
que_qaru01.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#F1	139
que_qaru02.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#F2	139
que_qaru03.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#F3	139
que_qaru04.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#F4	139
que_qaru05.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#F5	139
que_qsch01.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#N1	139
que_qsch02.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#N2	139
que_qsch03.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#N3	139
que_qsch04.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#N4	139
que_qsch05.gat,2,2,0	duplicate(miro_rf#Okolnir)	miro_rf#N5	139

-	script	miro_yf#Okolnir	-1,{
	function	Cell;
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 44,292,46,292,67,295,67,293,94,301,94,299,79,289,79,287,56,282,58,282,71,283,71,281,100,281,102,281,44,261,46,261,50,265,52,265,56,270,58,270,72,278,73,278,82,266,84,266,88,266,90,266,94,271,96,271,60,257,60,255,73,263,73,261,75,257,75,255,87,257,87,255,58,251,58,249,80,251,80,249,53,245,53,243,75,245,75,243,100,251,102,251,100,256,102,256;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1]," ",1936,1,"miro_yf#"+'@name$+"::OnKilled";
	Cell '@name$,1;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","miro_yf#"+'@name$+"::OnKilled";
	Cell '@name$,0;
	end;
OnKilled:
	end;

	function	Cell	{
		setarray '@cell, 44,292,47,292,67,292,67,295,94,298,94,301,79,286,79,289,56,282,59,282,71,280,71,283,100,281,103,281,44,261,47,261,50,265,53,265,56,270,59,270,72,278,73,278,82,266,85,266,88,266,91,266,94,271,97,271,60,254,60,257,73,260,73,263,75,254,75,257,87,254,87,257,58,248,58,251,80,248,80,251,53,242,53,245,75,242,75,245,100,251,103,251,100,256,103,256;
		for (set '@i, 0; '@i < getarraysize('@cell); set '@i, '@i + 4) {
			areasetcell "this",'@cell['@i],'@cell['@i+1],'@cell['@i+2],'@cell['@i+3],getarg(1);
		}
	}
}
que_qaru01.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#F1	139
que_qaru02.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#F2	139
que_qaru03.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#F3	139
que_qaru04.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#F4	139
que_qaru05.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#F5	139
que_qsch01.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#N1	139
que_qsch02.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#N2	139
que_qsch03.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#N3	139
que_qsch04.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#N4	139
que_qsch05.gat,2,3,0	duplicate(miro_yf#Okolnir)	miro_yf#N5	139

//============================================================
// 少女の夢エリア
//------------------------------------------------------------
-	script	windpath01#Okolnir	-1,{
	if(countitem(7839) < 1) {
		// 未調査
		mes "‐ゲートを作動させるには";
		mes "　クリスタルの^0000FF鍵^000000が";
		mes "　必要です。‐";
		close;
	}
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	mes "‐^0000FFクリスタルの鍵^000000が";
	mes "　ゲートに反応した！‐";
	close2;
	delitem 7839,1;
	warp '@map$,114,158;
	end;
}
que_qaru01.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#F1	45,1,1
que_qaru02.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#F2	45,1,1
que_qaru03.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#F3	45,1,1
que_qaru04.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#F4	45,1,1
que_qaru05.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#F5	45,1,1
que_qsch01.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#N1	45,1,1
que_qsch02.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#N2	45,1,1
que_qsch03.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#N3	45,1,1
que_qsch04.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#N4	45,1,1
que_qsch05.gat,132,172,0	duplicate(windpath01#Okolnir)	windpath01#N5	45,1,1

que_qaru01.gat,113,165,0	warp	windpath02#F1	1,1,que_qaru01.gat,139,172
que_qaru02.gat,113,165,0	warp	windpath02#F2	1,1,que_qaru02.gat,139,172
que_qaru03.gat,113,165,0	warp	windpath02#F3	1,1,que_qaru03.gat,139,172
que_qaru04.gat,113,165,0	warp	windpath02#F4	1,1,que_qaru04.gat,139,172
que_qaru05.gat,113,165,0	warp	windpath02#F5	1,1,que_qaru05.gat,139,172
que_qsch01.gat,113,165,0	warp	windpath02#N1	1,1,que_qsch01.gat,139,172
que_qsch02.gat,113,165,0	warp	windpath02#N2	1,1,que_qsch02.gat,139,172
que_qsch03.gat,113,165,0	warp	windpath02#N3	1,1,que_qsch03.gat,139,172
que_qsch04.gat,113,165,0	warp	windpath02#N4	1,1,que_qsch04.gat,139,172
que_qsch05.gat,113,165,0	warp	windpath02#N5	1,1,que_qsch05.gat,139,172

que_qaru01.gat,131,136,3	script	ピアメット#F1	1930,{}
que_qaru02.gat,131,136,3	script	ピアメット#F2	1930,{}
que_qaru03.gat,131,136,3	script	ピアメット#F3	1930,{}
que_qaru04.gat,131,136,3	script	ピアメット#F4	1930,{}
que_qaru05.gat,131,136,3	script	ピアメット#F5	1930,{}
que_qsch01.gat,131,136,3	script	ピアメット#N1	1930,{}
que_qsch02.gat,131,136,3	script	ピアメット#N2	1930,{}
que_qsch03.gat,131,136,3	script	ピアメット#N3	1930,{}
que_qsch04.gat,131,136,3	script	ピアメット#N4	1930,{}
que_qsch05.gat,131,136,3	script	ピアメット#N5	1930,{}

-	script	event_start01#Okolnir	-1,{
OnTouch:
	initnpctimer;
	hideonnpc;
	end;
OnTimer2000:
	announce "ピアメットのつぶやき : テオ、あのね……？　小鳥さんが6羽いたの……でも、1羽は……",0x9,0xdb7093;
	end;
OnTimer6000:
	announce "ピアメットのつぶやき : あっ……テオ！　小鳥さんが帰ってきたの！　逃げたわたしの小鳥さんでしょう？　それとも……",0x9,0xdb7093;
	end;
OnTimer10000:
	announce "ピアメットのつぶやき : 旅人のふりをした破壊者かしら……フフッ……でもぉ、鳥籠の中に入れば、みんな小鳥さんだよねぇ～",0x9,0xdb7093;
	end;
OnTimer14000:
	announce "ピアメット : テオ、鳥を全て捕まえて！　わたしの鳥籠をいっぱいにするの！",0x9,0x00ff00;
	donpcevent "gdtimer01#"+strnpcinfo(2)+"::OnStart";
	stopnpctimer;
	end;
}
que_qaru01.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#F1	139,1,1
que_qaru02.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#F2	139,1,1
que_qaru03.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#F3	139,1,1
que_qaru04.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#F4	139,1,1
que_qaru05.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#F5	139,1,1
que_qsch01.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#N1	139,1,1
que_qsch02.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#N2	139,1,1
que_qsch03.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#N3	139,1,1
que_qsch04.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#N4	139,1,1
que_qsch05.gat,114,158,0	duplicate(event_start01#Okolnir)	event_start01#N5	139,1,1

-	script	gdtimer01#Okolnir	-1,{
OnStart:
	initnpctimer;
	end;
OnStop:
	set '@name$,strnpcinfo(2);
	for (set '@i, 1; '@i <= 8; set '@i, '@i + 1)
		donpcevent "getspell0"+'@i+"#"+'@name$+"::OnDisable";
	stopnpctimer;
	end;
OnTimer1000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell08#"+'@name$+"::OnDisable";
	donpcevent "getspell01#"+'@name$+"::OnEnable";
	end;
OnTimer10000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell01#"+'@name$+"::OnDisable";
	donpcevent "getspell02#"+'@name$+"::OnEnable";
	end;
OnTimer20000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell02#"+'@name$+"::OnDisable";
	donpcevent "getspell03#"+'@name$+"::OnEnable";
	end;
OnTimer30000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell03#"+'@name$+"::OnDisable";
	donpcevent "getspell04#"+'@name$+"::OnEnable";
	end;
OnTimer40000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell04#"+'@name$+"::OnDisable";
	donpcevent "getspell05#"+'@name$+"::OnEnable";
	end;
OnTimer50000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell05#"+'@name$+"::OnDisable";
	donpcevent "getspell06#"+'@name$+"::OnEnable";
	end;
OnTimer60000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell06#"+'@name$+"::OnDisable";
	donpcevent "getspell07#"+'@name$+"::OnEnable";
	end;
OnTimer70000:
	set '@name$,strnpcinfo(2);
	donpcevent "getspell07#"+'@name$+"::OnDisable";
	donpcevent "getspell08#"+'@name$+"::OnEnable";
	end;
OnTimer75000:
	set '@name$,strnpcinfo(2);
	if('gqse_cagecount < 6) {
		announce "ピアメット : この馬鹿鳥！　馬鹿テオ！　どうして一度で鳥籠をいっぱいにできないの!?",0x9,0x00ff00;
		for (set '@i, 1; '@i <= 6; set '@i, '@i + 1)
			hideoffnpc "#"+'@name$+"_cage0"+'@i;
		set 'gqse_cagecount,0;
	}
	end;
OnTimer76000:
	set '@name$,strnpcinfo(2);
	for (set '@i, 1; '@i <= 6; set '@i, '@i + 1)
		hideonnpc "#"+'@name$+"_cage0"+'@i;
	end;
OnTimer80000:
	initnpctimer;
	end;
}
que_qaru01.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#F1	139
que_qaru02.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#F2	139
que_qaru03.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#F3	139
que_qaru04.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#F4	139
que_qaru05.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#F5	139
que_qsch01.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#N1	139
que_qsch02.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#N2	139
que_qsch03.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#N3	139
que_qsch04.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#N4	139
que_qsch05.gat,2,2,0	duplicate(gdtimer01#Okolnir)	gdtimer01#N5	139

-	script	gdtimer02#Okolnir	-1,{
OnStart:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	killmonster "this","gdtimer02#"+strnpcinfo(2)+"::OnKilled";
	end;
OnTimer4000:
	announce "ピアメット : ぜんぶ……捕まえた！",0x9,0xdb7093;
	end;
OnTimer8000:
	announce "ピアメット : わたしの可愛い小鳥さんたちが逃げ出さないように、鍵を用意しましょう～",0x9,0xdb7093;
	end;
OnTimer12000:
	set '@name$,strnpcinfo(2);
	announce "ピアメット : フフフッ、鍵よ、わたしの鳥籠を守って！",0x9,0xdb7093;
	setarray '@xy, 108,151,109,135,115,116,158,106,163,133,150,154;
	for(set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"鍵",1905,1,"gdtimer02#"+'@name$+"::OnKilled";
	end;
OnTimer112000:
	set '@name$,strnpcinfo(2);
	announce "ピアメット : フフフッ、また遊びましょうよ！さあ逃げて御覧なさい、また捕まえてあげる！",0x9,0xdb7093;
	killmonster "this","gdtimer02#"+'@name$+"::OnKilled";
	for(set '@i, 1; '@i <= 6; set '@i, '@i + 1)
		hideoffnpc "#"+'@name$+"_cage0"+'@i;
	set getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$),0;
	end;
OnTimer113000:
	set '@name$,strnpcinfo(2);
	for(set '@i, 1; '@i <= 6; set '@i, '@i + 1)
		hideonnpc "#"+'@name$+"_cage0"+'@i;
	donpcevent "gdtimer01#"+'@name$+"::OnStart";
	stopnpctimer;
	end;
OnReset:
	killmonster "this","gdtimer02#"+strnpcinfo(2)+"::OnKilled";
	end;
OnKilled:
	set '@name$,strnpcinfo(2);
	if(getmapmobs("this","gdtimer02#"+'@name$+"::OnKilled") == 0) {
		for (set '@i, 1; '@i <= 6; set '@i, '@i + 1)
			hideoffnpc "#"+'@name$+"_cage0"+'@i;
		donpcevent "piamette_ev#"+'@name$+"::OnStart";
		stopnpctimer;
	}
	end;
}
que_qaru01.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#F1	139
que_qaru02.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#F2	139
que_qaru03.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#F3	139
que_qaru04.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#F4	139
que_qaru05.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#F5	139
que_qsch01.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#N1	139
que_qsch02.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#N2	139
que_qsch03.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#N3	139
que_qsch04.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#N4	139
que_qsch05.gat,2,3,0	duplicate(gdtimer02#Okolnir)	gdtimer02#N5	139

-	script	piamette_ev#Okolnir	-1,{
OnStart:
	initnpctimer;
	end;
OnReset:
	killmonster "this","piamette_ev#"+strnpcinfo(2)+"::OnKilled";
	stopnpctimer;
	end;
OnTimer1000:
	announce "ピアメット : 鍵がぜんぶ壊されちゃったの？　わたしの小鳥を逃がしたのはだれ？　ねえテオ、だれなの？",0x9,0xdb7093;
	end;
OnTimer5000:
	set '@name$,strnpcinfo(2);
	announce "ピアメット : わたし、怒っちゃうぞ!!",0x9,0xdb7093;
	hideonnpc "ピアメット#"+'@name$;
	monster "this",131,135,"怒ったピアメット",1930,1,"piamette_ev#"+'@name$+"::OnKilled";
	stopnpctimer;
	end;
OnKilled:
	set '@name$,strnpcinfo(2);
	announce "ピアメットの束縛が解け、南に向かうゲートが出現しました。",0x9,0x00ff00;
	hideoffnpc "windpath03#"+'@name$;
	hideoffnpc "windpath04#"+'@name$;
	hideoffnpc "nm_switch#"+'@name$;
	end;
}
que_qaru01.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#F1	139
que_qaru02.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#F2	139
que_qaru03.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#F3	139
que_qaru04.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#F4	139
que_qaru05.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#F5	139
que_qsch01.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#N1	139
que_qsch02.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#N2	139
que_qsch03.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#N3	139
que_qsch04.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#N4	139
que_qsch05.gat,1,4,0	duplicate(piamette_ev#Okolnir)	piamette_ev#N5	139

-	script	#getspells_main	-1,{
OnEnable:
	hideoffnpc;
	misceffect 60;
	end;
OnDisable:
	hideonnpc;
	end;
OnTouch:
	set '@name$,strnpcinfo(2);
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	sc_start SC_STONE,300000,0,10000;
	switch(getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$)) {
	case 0: setarray '@n$, "103","153","1","ピアメット : 新しい一羽は真っ白な羽が矢に貫かれ、地面にドサッと落ちたの。","0xdb7093"; break;
	case 1: setarray '@n$, "102","135","2","ピアメット : 新しい一羽は誰かが投げた罠にかかって、湖にバシャッと落ちたの。","0xdb7093"; break;
	case 2: setarray '@n$, "113","111","3","ピアメット : 新しい一羽は、ひとりぼっちで閉じ込められたまま放置されていたの。","0xdb7093"; break;
	case 3: setarray '@n$, "161","105","4","ピアメット : 新しい一羽は、甘ーい死の毒を食べてしまったの。","0xdb7093"; break;
	case 4: setarray '@n$, "168","135","5","ピアメット : 新しい一羽は、七日七晩歌を歌い続けて血を吐いてしまったの。","0xdb7093"; break;
	case 5:
		setarray '@n$, "150","159","6","ピアメット : 最後の一羽は、わたしの手の中でもがいて首が折れて投げ捨てられたの!!","0xff0000";
		donpcevent "gdtimer02#"+'@name$+"::OnStart";
		donpcevent "gdtimer01#"+'@name$+"::OnStop";
		break;
	}
	hideonnpc;
	warp '@map$,'@n$[0],'@n$[1];
	set getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$),'@n$[2];
	announce '@n$[3],0x9,'@n$[4];
	end;
}
que_qaru01.gat,113,135,0	duplicate(#getspells_main)	getspell01#F1	139,1,1
que_qaru02.gat,113,135,0	duplicate(#getspells_main)	getspell01#F2	139,1,1
que_qaru03.gat,113,135,0	duplicate(#getspells_main)	getspell01#F3	139,1,1
que_qaru04.gat,113,135,0	duplicate(#getspells_main)	getspell01#F4	139,1,1
que_qaru05.gat,113,135,0	duplicate(#getspells_main)	getspell01#F5	139,1,1
que_qsch01.gat,113,135,0	duplicate(#getspells_main)	getspell01#N1	139,1,1
que_qsch02.gat,113,135,0	duplicate(#getspells_main)	getspell01#N2	139,1,1
que_qsch03.gat,113,135,0	duplicate(#getspells_main)	getspell01#N3	139,1,1
que_qsch04.gat,113,135,0	duplicate(#getspells_main)	getspell01#N4	139,1,1
que_qsch05.gat,113,135,0	duplicate(#getspells_main)	getspell01#N5	139,1,1
que_qaru01.gat,146,150,0	duplicate(#getspells_main)	getspell02#F1	139,1,1
que_qaru02.gat,146,150,0	duplicate(#getspells_main)	getspell02#F2	139,1,1
que_qaru03.gat,146,150,0	duplicate(#getspells_main)	getspell02#F3	139,1,1
que_qaru04.gat,146,150,0	duplicate(#getspells_main)	getspell02#F4	139,1,1
que_qaru05.gat,146,150,0	duplicate(#getspells_main)	getspell02#F5	139,1,1
que_qsch01.gat,146,150,0	duplicate(#getspells_main)	getspell02#N1	139,1,1
que_qsch02.gat,146,150,0	duplicate(#getspells_main)	getspell02#N2	139,1,1
que_qsch03.gat,146,150,0	duplicate(#getspells_main)	getspell02#N3	139,1,1
que_qsch04.gat,146,150,0	duplicate(#getspells_main)	getspell02#N4	139,1,1
que_qsch05.gat,146,150,0	duplicate(#getspells_main)	getspell02#N5	139,1,1
que_qaru01.gat,131,117,0	duplicate(#getspells_main)	getspell03#F1	139,1,1
que_qaru02.gat,131,117,0	duplicate(#getspells_main)	getspell03#F2	139,1,1
que_qaru03.gat,131,117,0	duplicate(#getspells_main)	getspell03#F3	139,1,1
que_qaru04.gat,131,117,0	duplicate(#getspells_main)	getspell03#F4	139,1,1
que_qaru05.gat,131,117,0	duplicate(#getspells_main)	getspell03#F5	139,1,1
que_qsch01.gat,131,117,0	duplicate(#getspells_main)	getspell03#N1	139,1,1
que_qsch02.gat,131,117,0	duplicate(#getspells_main)	getspell03#N2	139,1,1
que_qsch03.gat,131,117,0	duplicate(#getspells_main)	getspell03#N3	139,1,1
que_qsch04.gat,131,117,0	duplicate(#getspells_main)	getspell03#N4	139,1,1
que_qsch05.gat,131,117,0	duplicate(#getspells_main)	getspell03#N5	139,1,1
que_qaru01.gat,117,150,0	duplicate(#getspells_main)	getspell04#F1	139,1,1
que_qaru02.gat,117,150,0	duplicate(#getspells_main)	getspell04#F2	139,1,1
que_qaru03.gat,117,150,0	duplicate(#getspells_main)	getspell04#F3	139,1,1
que_qaru04.gat,117,150,0	duplicate(#getspells_main)	getspell04#F4	139,1,1
que_qaru05.gat,117,150,0	duplicate(#getspells_main)	getspell04#F5	139,1,1
que_qsch01.gat,117,150,0	duplicate(#getspells_main)	getspell04#N1	139,1,1
que_qsch02.gat,117,150,0	duplicate(#getspells_main)	getspell04#N2	139,1,1
que_qsch03.gat,117,150,0	duplicate(#getspells_main)	getspell04#N3	139,1,1
que_qsch04.gat,117,150,0	duplicate(#getspells_main)	getspell04#N4	139,1,1
que_qsch05.gat,117,150,0	duplicate(#getspells_main)	getspell04#N5	139,1,1
que_qaru01.gat,150,135,0	duplicate(#getspells_main)	getspell05#F1	139,1,1
que_qaru02.gat,150,135,0	duplicate(#getspells_main)	getspell05#F2	139,1,1
que_qaru03.gat,150,135,0	duplicate(#getspells_main)	getspell05#F3	139,1,1
que_qaru04.gat,150,135,0	duplicate(#getspells_main)	getspell05#F4	139,1,1
que_qaru05.gat,150,135,0	duplicate(#getspells_main)	getspell05#F5	139,1,1
que_qsch01.gat,150,135,0	duplicate(#getspells_main)	getspell05#N1	139,1,1
que_qsch02.gat,150,135,0	duplicate(#getspells_main)	getspell05#N2	139,1,1
que_qsch03.gat,150,135,0	duplicate(#getspells_main)	getspell05#N3	139,1,1
que_qsch04.gat,150,135,0	duplicate(#getspells_main)	getspell05#N4	139,1,1
que_qsch05.gat,150,135,0	duplicate(#getspells_main)	getspell05#N5	139,1,1
que_qaru01.gat,117,121,0	duplicate(#getspells_main)	getspell06#F1	139,1,1
que_qaru02.gat,117,121,0	duplicate(#getspells_main)	getspell06#F2	139,1,1
que_qaru03.gat,117,121,0	duplicate(#getspells_main)	getspell06#F3	139,1,1
que_qaru04.gat,117,121,0	duplicate(#getspells_main)	getspell06#F4	139,1,1
que_qaru05.gat,117,121,0	duplicate(#getspells_main)	getspell06#F5	139,1,1
que_qsch01.gat,117,121,0	duplicate(#getspells_main)	getspell06#N1	139,1,1
que_qsch02.gat,117,121,0	duplicate(#getspells_main)	getspell06#N2	139,1,1
que_qsch03.gat,117,121,0	duplicate(#getspells_main)	getspell06#N3	139,1,1
que_qsch04.gat,117,121,0	duplicate(#getspells_main)	getspell06#N4	139,1,1
que_qsch05.gat,117,121,0	duplicate(#getspells_main)	getspell06#N5	139,1,1
que_qaru01.gat,131,154,0	duplicate(#getspells_main)	getspell07#F1	139,1,1
que_qaru02.gat,131,154,0	duplicate(#getspells_main)	getspell07#F2	139,1,1
que_qaru03.gat,131,154,0	duplicate(#getspells_main)	getspell07#F3	139,1,1
que_qaru04.gat,131,154,0	duplicate(#getspells_main)	getspell07#F4	139,1,1
que_qaru05.gat,131,154,0	duplicate(#getspells_main)	getspell07#F5	139,1,1
que_qsch01.gat,131,154,0	duplicate(#getspells_main)	getspell07#N1	139,1,1
que_qsch02.gat,131,154,0	duplicate(#getspells_main)	getspell07#N2	139,1,1
que_qsch03.gat,131,154,0	duplicate(#getspells_main)	getspell07#N3	139,1,1
que_qsch04.gat,131,154,0	duplicate(#getspells_main)	getspell07#N4	139,1,1
que_qsch05.gat,131,154,0	duplicate(#getspells_main)	getspell07#N5	139,1,1
que_qaru01.gat,146,121,0	duplicate(#getspells_main)	getspell08#F1	139,1,1
que_qaru02.gat,146,121,0	duplicate(#getspells_main)	getspell08#F2	139,1,1
que_qaru03.gat,146,121,0	duplicate(#getspells_main)	getspell08#F3	139,1,1
que_qaru04.gat,146,121,0	duplicate(#getspells_main)	getspell08#F4	139,1,1
que_qaru05.gat,146,121,0	duplicate(#getspells_main)	getspell08#F5	139,1,1
que_qsch01.gat,146,121,0	duplicate(#getspells_main)	getspell08#N1	139,1,1
que_qsch02.gat,146,121,0	duplicate(#getspells_main)	getspell08#N2	139,1,1
que_qsch03.gat,146,121,0	duplicate(#getspells_main)	getspell08#N3	139,1,1
que_qsch04.gat,146,121,0	duplicate(#getspells_main)	getspell08#N4	139,1,1
que_qsch05.gat,146,121,0	duplicate(#getspells_main)	getspell08#N5	139,1,1

-	script	#Okolnir_cages	-1,{
OnTouch:
	set '@name$,substr(strnpcinfo(2),0,2);
	set '@num,substr(strnpcinfo(2),8,1);
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	sc_end SC_STONE;
	setarray '@n, 108,151,106,135,113,115,158,106,163,133,150,154;
	warp '@map$,'@n['@num*2],'@n['@num*2+1];
	hideonnpc;
	end;
}
que_qaru01.gat,103,153,0	duplicate(#Okolnir_cages)	#F1_cage01	139,1,1
que_qaru02.gat,103,153,0	duplicate(#Okolnir_cages)	#F2_cage01	139,1,1
que_qaru03.gat,103,153,0	duplicate(#Okolnir_cages)	#F3_cage01	139,1,1
que_qaru04.gat,103,153,0	duplicate(#Okolnir_cages)	#F4_cage01	139,1,1
que_qaru05.gat,103,153,0	duplicate(#Okolnir_cages)	#F5_cage01	139,1,1
que_qsch01.gat,103,153,0	duplicate(#Okolnir_cages)	#N1_cage01	139,1,1
que_qsch02.gat,103,153,0	duplicate(#Okolnir_cages)	#N2_cage01	139,1,1
que_qsch03.gat,103,153,0	duplicate(#Okolnir_cages)	#N3_cage01	139,1,1
que_qsch04.gat,103,153,0	duplicate(#Okolnir_cages)	#N4_cage01	139,1,1
que_qsch05.gat,103,153,0	duplicate(#Okolnir_cages)	#N5_cage01	139,1,1
que_qaru01.gat,102,135,0	duplicate(#Okolnir_cages)	#F1_cage02	139,1,1
que_qaru02.gat,102,135,0	duplicate(#Okolnir_cages)	#F2_cage02	139,1,1
que_qaru03.gat,102,135,0	duplicate(#Okolnir_cages)	#F3_cage02	139,1,1
que_qaru04.gat,102,135,0	duplicate(#Okolnir_cages)	#F4_cage02	139,1,1
que_qaru05.gat,102,135,0	duplicate(#Okolnir_cages)	#F5_cage02	139,1,1
que_qsch01.gat,102,135,0	duplicate(#Okolnir_cages)	#N1_cage02	139,1,1
que_qsch02.gat,102,135,0	duplicate(#Okolnir_cages)	#N2_cage02	139,1,1
que_qsch03.gat,102,135,0	duplicate(#Okolnir_cages)	#N3_cage02	139,1,1
que_qsch04.gat,102,135,0	duplicate(#Okolnir_cages)	#N4_cage02	139,1,1
que_qsch05.gat,102,135,0	duplicate(#Okolnir_cages)	#N5_cage02	139,1,1
que_qaru01.gat,113,111,0	duplicate(#Okolnir_cages)	#F1_cage03	139,1,1
que_qaru02.gat,113,111,0	duplicate(#Okolnir_cages)	#F2_cage03	139,1,1
que_qaru03.gat,113,111,0	duplicate(#Okolnir_cages)	#F3_cage03	139,1,1
que_qaru04.gat,113,111,0	duplicate(#Okolnir_cages)	#F4_cage03	139,1,1
que_qaru05.gat,113,111,0	duplicate(#Okolnir_cages)	#F5_cage03	139,1,1
que_qsch01.gat,113,111,0	duplicate(#Okolnir_cages)	#N1_cage03	139,1,1
que_qsch02.gat,113,111,0	duplicate(#Okolnir_cages)	#N2_cage03	139,1,1
que_qsch03.gat,113,111,0	duplicate(#Okolnir_cages)	#N3_cage03	139,1,1
que_qsch04.gat,113,111,0	duplicate(#Okolnir_cages)	#N4_cage03	139,1,1
que_qsch05.gat,113,111,0	duplicate(#Okolnir_cages)	#N5_cage03	139,1,1
que_qaru01.gat,161,105,0	duplicate(#Okolnir_cages)	#F1_cage04	139,1,1
que_qaru02.gat,161,105,0	duplicate(#Okolnir_cages)	#F2_cage04	139,1,1
que_qaru03.gat,161,105,0	duplicate(#Okolnir_cages)	#F3_cage04	139,1,1
que_qaru04.gat,161,105,0	duplicate(#Okolnir_cages)	#F4_cage04	139,1,1
que_qaru05.gat,161,105,0	duplicate(#Okolnir_cages)	#F5_cage04	139,1,1
que_qsch01.gat,161,105,0	duplicate(#Okolnir_cages)	#N1_cage04	139,1,1
que_qsch02.gat,161,105,0	duplicate(#Okolnir_cages)	#N2_cage04	139,1,1
que_qsch03.gat,161,105,0	duplicate(#Okolnir_cages)	#N3_cage04	139,1,1
que_qsch04.gat,161,105,0	duplicate(#Okolnir_cages)	#N4_cage04	139,1,1
que_qsch05.gat,161,105,0	duplicate(#Okolnir_cages)	#N5_cage04	139,1,1
que_qaru01.gat,168,135,0	duplicate(#Okolnir_cages)	#F1_cage05	139,1,1
que_qaru02.gat,168,135,0	duplicate(#Okolnir_cages)	#F2_cage05	139,1,1
que_qaru03.gat,168,135,0	duplicate(#Okolnir_cages)	#F3_cage05	139,1,1
que_qaru04.gat,168,135,0	duplicate(#Okolnir_cages)	#F4_cage05	139,1,1
que_qaru05.gat,168,135,0	duplicate(#Okolnir_cages)	#F5_cage05	139,1,1
que_qsch01.gat,168,135,0	duplicate(#Okolnir_cages)	#N1_cage05	139,1,1
que_qsch02.gat,168,135,0	duplicate(#Okolnir_cages)	#N2_cage05	139,1,1
que_qsch03.gat,168,135,0	duplicate(#Okolnir_cages)	#N3_cage05	139,1,1
que_qsch04.gat,168,135,0	duplicate(#Okolnir_cages)	#N4_cage05	139,1,1
que_qsch05.gat,168,135,0	duplicate(#Okolnir_cages)	#N5_cage05	139,1,1
que_qaru01.gat,150,159,0	duplicate(#Okolnir_cages)	#F1_cage06	139,1,1
que_qaru02.gat,150,159,0	duplicate(#Okolnir_cages)	#F2_cage06	139,1,1
que_qaru03.gat,150,159,0	duplicate(#Okolnir_cages)	#F3_cage06	139,1,1
que_qaru04.gat,150,159,0	duplicate(#Okolnir_cages)	#F4_cage06	139,1,1
que_qaru05.gat,150,159,0	duplicate(#Okolnir_cages)	#F5_cage06	139,1,1
que_qsch01.gat,150,159,0	duplicate(#Okolnir_cages)	#N1_cage06	139,1,1
que_qsch02.gat,150,159,0	duplicate(#Okolnir_cages)	#N2_cage06	139,1,1
que_qsch03.gat,150,159,0	duplicate(#Okolnir_cages)	#N3_cage06	139,1,1
que_qsch04.gat,150,159,0	duplicate(#Okolnir_cages)	#N4_cage06	139,1,1
que_qsch05.gat,150,159,0	duplicate(#Okolnir_cages)	#N5_cage06	139,1,1

-	script	#gd_main_mobctrl	-1,{
OnEnable:
	setarray '@mob$[1][0], "ピアメットのおもちゃ","1738";
	setarray '@mobpos[1][0], 107,152,109,135,113,116,157,107,163,133,149,156,131,139,135,136,131,132,128,136,110,145,129,114,148,114,155,128,152,145,131,151,110,130;
	setarray '@mob$[2][0], "アリス","1275";
	setarray '@mobpos[2][0], 130,139,135,137,130,132,128,137,109,145,109,130,128,114,147,114,154,128,151,145,130,151;
	setarray '@mob$[3][0], "ヴァイオリー","1390";
	setarray '@mobpos[3][0], 132,139,135,135,132,132,128,135,111,145,111,130,130,114,149,114,156,128,153,145,132,151;
	setarray '@mob$[4][0], "ピアメットの宝箱","1699";
	setarray '@mobpos[4][0], 133,139,135,134,133,132,128,135,112,145,131,114,150,114,157,128,154,145,133,151,112,130;
	set '@name$,strnpcinfo(2);
	set '@c, 1;
	while ('@c <= 4) {
		for (set '@i, 0; '@i < getarraysize('@mobpos['@c][0]); set '@i, '@i + 2)
			monster "this",'@mobpos['@c]['@i],'@mobpos['@c]['@i+1],'@mob$['@c][0],'@mob$['@c][1],1,"gd_mobctrl#"+'@name$+"::OnKilled";
		set '@c, '@c + 1;
	}
	end;
OnReset:
	killmonster "this","gd_mobctrl#"+strnpcinfo(2)+"::OnKilled";
	end;
OnKilled:
	set '@name$,strnpcinfo(2);
	if(getmapmobs("this","gd_mobctrl#"+'@name$+"::OnKilled") < 7) {
		setarray '@n, 107,152,109,135,113,116,157,107,163,133,149,156;
		for(set '@i, 0; '@i < getarraysize('@n); set '@i, '@i + 2)
			monster "this",'@n['@i],'@n['@i+1],"ピアメットのおもちゃ",1738,1,"gd_mobctrl#"+'@name$+"::OnKilled";
	}
	end;
}
que_qaru01.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#F1	139
que_qaru02.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#F2	139
que_qaru03.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#F3	139
que_qaru04.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#F4	139
que_qaru05.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#F5	139
que_qsch01.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#N1	139
que_qsch02.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#N2	139
que_qsch03.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#N3	139
que_qsch04.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#N4	139
que_qsch05.gat,1,8,0	duplicate(#gd_main_mobctrl)	gd_mobctrl#N5	139

que_qaru01.gat,149,105,0	warp	windpath03#F1	1,1,que_qaru01.gat,119,103
que_qaru02.gat,149,105,0	warp	windpath03#F2	1,1,que_qaru02.gat,119,103
que_qaru03.gat,149,105,0	warp	windpath03#F3	1,1,que_qaru03.gat,119,103
que_qaru04.gat,149,105,0	warp	windpath03#F4	1,1,que_qaru04.gat,119,103
que_qaru05.gat,149,105,0	warp	windpath03#F5	1,1,que_qaru05.gat,119,103
que_qsch01.gat,149,105,0	warp	windpath03#N1	1,1,que_qsch01.gat,119,103
que_qsch02.gat,149,105,0	warp	windpath03#N2	1,1,que_qsch02.gat,119,103
que_qsch03.gat,149,105,0	warp	windpath03#N3	1,1,que_qsch03.gat,119,103
que_qsch04.gat,149,105,0	warp	windpath03#N4	1,1,que_qsch04.gat,119,103
que_qsch05.gat,149,105,0	warp	windpath03#N5	1,1,que_qsch05.gat,119,103

que_qaru01.gat,128,104,0	warp	windpath04#F1	1,1,que_qaru01.gat,146,109
que_qaru02.gat,128,104,0	warp	windpath04#F2	1,1,que_qaru02.gat,146,109
que_qaru03.gat,128,104,0	warp	windpath04#F3	1,1,que_qaru03.gat,146,109
que_qaru04.gat,128,104,0	warp	windpath04#F4	1,1,que_qaru04.gat,146,109
que_qaru05.gat,128,104,0	warp	windpath04#F5	1,1,que_qaru05.gat,146,109
que_qsch01.gat,128,104,0	warp	windpath04#N1	1,1,que_qsch01.gat,146,109
que_qsch02.gat,128,104,0	warp	windpath04#N2	1,1,que_qsch02.gat,146,109
que_qsch03.gat,128,104,0	warp	windpath04#N3	1,1,que_qsch03.gat,146,109
que_qsch04.gat,128,104,0	warp	windpath04#N4	1,1,que_qsch04.gat,146,109
que_qsch05.gat,128,104,0	warp	windpath04#N5	1,1,que_qsch05.gat,146,109

//============================================================
// ナイトメアキーパーエリア
//------------------------------------------------------------
-	script	#nm_switch_main	-1,{
OnTouch:
	hideonnpc;
	initnpctimer;
	end;
OnDisable:
	hideonnpc;
	stopnpctimer;
	end;
OnTimer1000:
	announce "ウィッシュメイデン : ピアメットとのお遊戯は楽しかったかね？", 0x9, 0x00ff00;
	end;
OnTimer4000:
	announce "ウィッシュメイデン : しかしまだ終わりではない。汝らの目前に古の神殿にて召喚されし者たちが現れる……", 0x9, 0x00ff00;
	end;
OnTimer9000:
	announce "ウィッシュメイデン : 我のところまで、無事辿り着いてみせよ。", 0x9, 0x00ff00;
	end;
OnTimer10000:
	donpcevent "nmsom_jin01#"+strnpcinfo(2)+"::OnEnable";
	end;
OnTimer190000:
	donpcevent "nmsom_jin02#"+strnpcinfo(2)+"::OnEnable";
	end;
OnTimer370000:
	donpcevent "nmsom_jin03#"+strnpcinfo(2)+"::OnEnable";
	stopnpctimer;
	end;
}
que_qaru01.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#F1	139,5,5
que_qaru02.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#F2	139,5,5
que_qaru03.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#F3	139,5,5
que_qaru04.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#F4	139,5,5
que_qaru05.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#F5	139,5,5
que_qsch01.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#N1	139,5,5
que_qsch02.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#N2	139,5,5
que_qsch03.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#N3	139,5,5
que_qsch04.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#N4	139,5,5
que_qsch05.gat,253,273,0	duplicate(#nm_switch_main)	nm_switch#N5	139,5,5

-	script	#nmsommain_jin01	-1,{
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 227,294,229,294,231,296,231,298,230,300,228,301,226,301,224,299,224,297,225,295;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"西側魔方陣の守護者",1752,1,"nmsom_jin01#"+'@name$+"::OnKilled1";
	initnpctimer;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","nmsom_jin01#"+'@name$+"::OnKilled1";
	killmonster "this","nmsom_jin01#"+'@name$+"::OnKilled2";
	stopnpctimer;
	end;
OnTimer5000:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 226,288,227,289,228,290,229,291,230,292,231,293,232,294,233,295,234,296,235,297,228,286,229,287,230,288,231,289,232,290,233,291,234,292,235,293,236,294,237,295,230,284,231,285,232,286,233,287,234,288,235,289,236,290,237,291,238,292,239,293;
	announce "西側の魔方陣が発動！　影の番人が召喚された！",0x9,0x4d4dff;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"影の番人",1752,1,"nmsom_jin01#"+'@name$+"::OnKilled2";
	end;
OnTimer25000:
OnTimer55000:
OnTimer85000:
OnTimer120000:
	set '@name$,strnpcinfo(2);
	setarray '@xy2, 226,294,227,294,228,294,229,294,230,295,231,296,231,297,231,298,231,299,230,300,229,301,228,301,227,301,226,301,225,300,224,299,224,298,224,297,224,296,225,295;
	for (set '@i, 0; '@i < getarraysize('@xy2); set '@i, '@i + 2)
		monster "this",'@xy2['@i],'@xy2['@i+1],"影の番人",1752,1,"nmsom_jin01#"+'@name$+"::OnKilled2";
	end;
OnTimer180000:
	stopnpctimer;
	end;
OnKilled1:
	set '@name$,strnpcinfo(2);
	if(getmapmobs("this","nmsom_jin01#"+'@name$+"::OnKilled1") == 0) {
		set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b")+1;
		donpcevent "nmsom_jin01#"+'@name$+"::OnDisable";
		if(getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b") == 3) {
			donpcevent "ウィッシュメイデン#"+'@name$+"_b::OnFight";
		}
	}
	end;
OnKilled2:
	end;
}
que_qaru01.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#F1	-1
que_qaru02.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#F2	-1
que_qaru03.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#F3	-1
que_qaru04.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#F4	-1
que_qaru05.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#F5	-1
que_qsch01.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#N1	-1
que_qsch02.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#N2	-1
que_qsch03.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#N3	-1
que_qsch04.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#N4	-1
que_qsch05.gat,229,297,0	duplicate(#nmsommain_jin01)	nmsom_jin01#N5	-1

-	script	#nmsommain_jin02	-1,{
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 275,301,277,301,279,299,279,297,278,295,276,294,274,294,272,296,272,298,273,300;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"東側魔方陣の守護者",1753,1,"nmsom_jin02#"+'@name$+"::OnKilled1";
	initnpctimer;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","nmsom_jin02#"+'@name$+"::OnKilled1";
	killmonster "this","nmsom_jin02#"+'@name$+"::OnKilled2";
	stopnpctimer;
	end;
OnTimer5000:
	set '@name$,strnpcinfo(2);
	announce "東側の魔方陣が発動！　血の狩人が召喚された！",0x9,0x4d4dff;
	setarray '@xy, 263,292,264,291,265,290,266,289,267,288,268,287,269,286,270,285,271,284,272,283,265,294,266,293,267,292,268,291,269,290,270,289,271,288,272,287,273,286,274,285,267,296,268,295,269,294,270,283,271,282,272,281,273,280,274,279,275,276,276,275;
	for(set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"血の狩人",1753,1,"nmsom_jin02#"+'@name$+"::OnKilled2";
	end;
OnTimer25000:
OnTimer55000:
OnTimer85000:
OnTimer120000:
	set '@name$,strnpcinfo(2);
	setarray '@xy2, 274,301,275,301,276,301,277,301,278,300,279,299,279,298,279,297,279,296,278,295,277,294,276,294,275,294,274,294,273,295,272,296,272,297,272,298,272,299,273,300;
	for(set '@i, 0; '@i < getarraysize('@xy2); set '@i, '@i + 2)
		monster "this",'@xy2['@i],'@xy2['@i+1],"血の狩人",1753,1,"nmsom_jin02#"+'@name$+"::OnKilled2";
	end;
OnTimer180000:
	stopnpctimer;
	end;
OnKilled1:
	set '@name$,strnpcinfo(2);
	if(getmapmobs("this","nmsom_jin02#"+'@name$+"::OnKilled1") == 0) {
		set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b")+1;
		donpcevent "nmsom_jin02#"+'@name$+"::OnDisable";
		if(getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b") == 3) {
			donpcevent "ウィッシュメイデン#"+'@name$+"_b::OnFight";
		}
	}
	end;
OnKilled2:
	end;
}
que_qaru01.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#F1	-1
que_qaru02.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#F2	-1
que_qaru03.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#F3	-1
que_qaru04.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#F4	-1
que_qaru05.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#F5	-1
que_qsch01.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#N1	-1
que_qsch02.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#N2	-1
que_qsch03.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#N3	-1
que_qsch04.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#N4	-1
que_qsch05.gat,275,299,0	duplicate(#nmsommain_jin02)	nmsom_jin02#N5	-1

-	script	#nmsommain_jin03	-1,{
OnEnable:
	set '@name$,strnpcinfo(2);
	setarray '@xy, 251,343,252,343,255,341,255,340,254,337,253,336,250,336,249,337,248,340,248,341;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"北側魔方陣の守護者",1933,1,"nmsom_jin03#"+'@name$+"::OnKilled1";
	initnpctimer;
	end;
OnDisable:
	set '@name$,strnpcinfo(2);
	killmonster "this","nmsom_jin03#"+'@name$+"::OnKilled1";
	killmonster "this","nmsom_jin03#"+'@name$+"::OnKilled2";
	stopnpctimer;
	end;
OnTimer5000:
	set '@name$,strnpcinfo(2);
	announce "北側の魔方陣が発動！　神殿の守護者が召喚された！", 0x9, 0x4d4dff;
	setarray '@xy, 247,329,249,329,251,329,253,329,255,329,243,339,245,337,247,335,247,333,254,333,256,335,258,337,260,339;
	for (set '@i, 0; '@i < getarraysize('@xy); set '@i, '@i + 2)
		monster "this",'@xy['@i],'@xy['@i+1],"神殿の守護者",1933,1,"nmsom_jin03#"+'@name$+"::OnKilled2";
	end;
OnTimer120000:
	set '@name$,strnpcinfo(2);
	setarray '@xy2, 251,343,252,343,255,341,255,340,254,337,253,336,250,336,249,337,248,340,248,341;
	for (set '@i, 0; '@i < getarraysize('@xy2); set '@i, '@i + 2)
		monster "this",'@xy2['@i],'@xy2['@i+1],"神殿の守護者",1933,1,"nmsom_jin03#"+'@name$+"::OnKilled2";
	end;
OnTimer240000:
	set '@name$,strnpcinfo(2);
	setarray '@xy3, 250,343,252,343,254,342,255,340,255,338,253,336,250,336,248,338,248,340,249,342;
	for (set '@i, 0; '@i < getarraysize('@xy3); set '@i, '@i + 2)
		monster "this",'@xy3['@i],'@xy3['@i+1],"神殿の守護者",1933,1,"nmsom_jin03#"+'@name$+"::OnKilled2";
	end;
OnTimer360000:
	set '@name$,strnpcinfo(2);
	setarray '@xy4, 250,343,252,343,254,342,255,340,255,338,253,336,251,336,249,337,248,339,248,341;
	for (set '@i, 0; '@i < getarraysize('@xy4); set '@i, '@i + 2)
		monster "this",'@xy4['@i],'@xy4['@i+1],"神殿の守護者",1933,1,"nmsom_jin03#"+'@name$+"::OnKilled2";
	stopnpctimer;
	end;
OnKilled1:
	set '@name$,strnpcinfo(2);
	if(getmapmobs("this","nmsom_jin03#"+'@name$+"::OnKilled1") == 0) {
		set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b")+1;
		donpcevent "nmsom_jin03#"+'@name$+"::OnDisable";
		if(getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b") == 3) {
			donpcevent "ウィッシュメイデン#"+'@name$+"_b::OnFight";
		}
	}
	end;
OnKilled2:
	end;
}
que_qaru01.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#F1	-1
que_qaru02.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#F2	-1
que_qaru03.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#F3	-1
que_qaru04.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#F4	-1
que_qaru05.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#F5	-1
que_qsch01.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#N1	-1
que_qsch02.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#N2	-1
que_qsch03.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#N3	-1
que_qsch04.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#N4	-1
que_qsch05.gat,251,340,0	duplicate(#nmsommain_jin03)	nmsom_jin03#N5	-1

-	script	影の番人#Okolnir	-1,{
	end;
OnTouch:
	set '@name$,strnpcinfo(2);
	set '@in,substr('@name$,4,1);
	hideonnpc;
	switch('@in) {
	case 1: setarray '@n, 234,284,235,285,236,286; break;
	case 2: setarray '@n, 223,289,224,290,225,291; break;
	case 3: setarray '@n, 235,295,236,296,237,297; break;
	case 4: setarray '@n, 224,302,225,303,226,304; break;
	}
	for (set '@i, 0; '@i < getarraysize('@n); set '@i, '@i + 2)
		monster "this",'@n['@i],'@n['@i+1],"影の番人",1752,1,"影の番人#"+'@name$+"::OnKilled";
	end;
OnDisable:
	killmonster "this","影の番人#"+strnpcinfo(2)+"::OnKilled";
	hideonnpc;
	end;
OnKilled:
	end;
}
que_qaru01.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#F1_01	1752,4,4
que_qaru01.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#F1_02	1752,4,4
que_qaru01.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#F1_03	1752,4,4
que_qaru01.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#F1_04	1752,4,4
que_qaru02.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#F2_01	1752,4,4
que_qaru02.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#F2_02	1752,4,4
que_qaru02.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#F2_03	1752,4,4
que_qaru02.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#F2_04	1752,4,4
que_qaru03.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#F3_01	1752,4,4
que_qaru03.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#F3_02	1752,4,4
que_qaru03.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#F3_03	1752,4,4
que_qaru03.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#F3_04	1752,4,4
que_qaru04.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#F4_01	1752,4,4
que_qaru04.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#F4_02	1752,4,4
que_qaru04.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#F4_03	1752,4,4
que_qaru04.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#F4_04	1752,4,4
que_qaru05.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#F5_01	1752,4,4
que_qaru05.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#F5_02	1752,4,4
que_qaru05.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#F5_03	1752,4,4
que_qaru05.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#F5_04	1752,4,4
que_qsch01.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#N1_01	1752,4,4
que_qsch01.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#N1_02	1752,4,4
que_qsch01.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#N1_03	1752,4,4
que_qsch01.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#N1_04	1752,4,4
que_qsch02.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#N2_01	1752,4,4
que_qsch02.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#N2_02	1752,4,4
que_qsch02.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#N2_03	1752,4,4
que_qsch02.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#N2_04	1752,4,4
que_qsch03.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#N3_01	1752,4,4
que_qsch03.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#N3_02	1752,4,4
que_qsch03.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#N3_03	1752,4,4
que_qsch03.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#N3_04	1752,4,4
que_qsch04.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#N4_01	1752,4,4
que_qsch04.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#N4_02	1752,4,4
que_qsch04.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#N4_03	1752,4,4
que_qsch04.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#N4_04	1752,4,4
que_qsch05.gat,235,285,5	duplicate(影の番人#Okolnir)	影の番人#N5_01	1752,4,4
que_qsch05.gat,224,290,5	duplicate(影の番人#Okolnir)	影の番人#N5_02	1752,4,4
que_qsch05.gat,236,296,5	duplicate(影の番人#Okolnir)	影の番人#N5_03	1752,4,4
que_qsch05.gat,225,303,5	duplicate(影の番人#Okolnir)	影の番人#N5_04	1752,4,4

-	script	血の狩人#Okolnir	-1,{
	end;
OnTouch:
	set '@name$,strnpcinfo(2);
	set '@in,substr('@name$,4,1);
	hideonnpc;
	switch('@in) {
	case 1: setarray '@n, 265,297,266,296,267,295; break;
	case 2: setarray '@n, 270,284,271,283,272,282; break;
	case 3: setarray '@n, 269,308,270,307,271,306; break;
	case 4: setarray '@n, 278,301,279,300,280,299; break;
	}
	for(set '@i, 0; '@i < getarraysize('@n); set '@i, '@i + 2)
		monster "this",'@n['@i],'@n['@i+1],"血の狩人",1753,1,"血の狩人#"+'@name$+"::OnKilled";
	end;
OnDisable:
	killmonster "this","血の狩人#"+strnpcinfo(2)+"::OnKilled";
	hideonnpc;
	end;
OnKilled:
	end;
}
que_qaru01.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#F1_01	1753,4,4
que_qaru01.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#F1_02	1753,4,4
que_qaru01.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#F1_03	1753,4,4
que_qaru01.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#F1_04	1753,4,4
que_qaru02.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#F2_01	1753,4,4
que_qaru02.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#F2_02	1753,4,4
que_qaru02.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#F2_03	1753,4,4
que_qaru02.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#F2_04	1753,4,4
que_qaru03.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#F3_01	1753,4,4
que_qaru03.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#F3_02	1753,4,4
que_qaru03.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#F3_03	1753,4,4
que_qaru03.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#F3_04	1753,4,4
que_qaru04.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#F4_01	1753,4,4
que_qaru04.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#F4_02	1753,4,4
que_qaru04.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#F4_03	1753,4,4
que_qaru04.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#F4_04	1753,4,4
que_qaru05.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#F5_01	1753,4,4
que_qaru05.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#F5_02	1753,4,4
que_qaru05.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#F5_03	1753,4,4
que_qaru05.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#F5_04	1753,4,4
que_qsch01.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#N1_01	1753,4,4
que_qsch01.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#N1_02	1753,4,4
que_qsch01.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#N1_03	1753,4,4
que_qsch01.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#N1_04	1753,4,4
que_qsch02.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#N2_01	1753,4,4
que_qsch02.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#N2_02	1753,4,4
que_qsch02.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#N2_03	1753,4,4
que_qsch02.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#N2_04	1753,4,4
que_qsch03.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#N3_01	1753,4,4
que_qsch03.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#N3_02	1753,4,4
que_qsch03.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#N3_03	1753,4,4
que_qsch03.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#N3_04	1753,4,4
que_qsch04.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#N4_01	1753,4,4
que_qsch04.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#N4_02	1753,4,4
que_qsch04.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#N4_03	1753,4,4
que_qsch04.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#N4_04	1753,4,4
que_qsch05.gat,266,296,3	duplicate(血の狩人#Okolnir)	血の狩人#N5_01	1753,4,4
que_qsch05.gat,271,283,3	duplicate(血の狩人#Okolnir)	血の狩人#N5_02	1753,4,4
que_qsch05.gat,270,307,3	duplicate(血の狩人#Okolnir)	血の狩人#N5_03	1753,4,4
que_qsch05.gat,279,300,3	duplicate(血の狩人#Okolnir)	血の狩人#N5_04	1753,4,4

-	script	神殿の守護者#Okolnir	-1,{
	end;
OnTouch:
	set '@name$,strnpcinfo(2);
	set '@in,substr('@name$,4,1);
	hideonnpc;
	switch ('@in) {
	case 1: setarray '@n, 246,330,247,330,248,330; break;
	case 2: setarray '@n, 254,330,255,330,256,330; break;
	}
	for(set '@i, 0; '@i < getarraysize('@n); set '@i, '@i + 2)
		monster "this",'@n['@i],'@n['@i+1],"神殿の守護者",1933,1,"神殿の守護者#"+'@name$+"::OnKilled";
	end;
OnDisable:
	killmonster "this","神殿の守護者#"+strnpcinfo(2)+"::OnKilled";
	hideonnpc;
	end;
OnKilled:
	end;
}
que_qaru01.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F1_01	1933,4,4
que_qaru01.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F1_02	1933,4,4
que_qaru02.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F2_01	1933,4,4
que_qaru02.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F2_02	1933,4,4
que_qaru03.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F3_01	1933,4,4
que_qaru03.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F3_02	1933,4,4
que_qaru04.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F4_01	1933,4,4
que_qaru04.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F4_02	1933,4,4
que_qaru05.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F5_01	1933,4,4
que_qaru05.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#F5_02	1933,4,4
que_qsch01.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N1_01	1933,4,4
que_qsch01.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N1_02	1933,4,4
que_qsch02.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N2_01	1933,4,4
que_qsch02.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N2_02	1933,4,4
que_qsch03.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N3_01	1933,4,4
que_qsch03.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N3_02	1933,4,4
que_qsch04.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N4_01	1933,4,4
que_qsch04.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N4_02	1933,4,4
que_qsch05.gat,247,330,5	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N5_01	1933,4,4
que_qsch05.gat,255,330,3	duplicate(神殿の守護者#Okolnir)	神殿の守護者#N5_02	1933,4,4

-	script	ウィッシュメイデン#boss	-1,{
OnDisable:
	killmonster "this","ウィッシュメイデン#"+strnpcinfo(2)+"::OnKilled";
	stopnpctimer;
	end;
OnFight:
	initnpctimer;
	end;
OnTimer1000:
	announce "ウィッシュメイデン : ここまで辿り着いたか……我の番人は全て倒されたと……",0x9,0x00ff00;
	end;
OnTimer4000:
	announce "ウィッシュメイデン : 我、ウィッシュメイデン！　全力で汝らを歓迎しよう!!",0x9,0x00ff00;
	end;
OnTimer5000:
	set '@name$,strnpcinfo(2);
	misceffect 72,"ウィッシュメイデン#"+'@name$+"_g";
	monster "this",252,340,"ウィッシュメイデン",1931,1,"ウィッシュメイデン#"+'@name$+"::OnKilled";
	stopnpctimer;
	end;
OnKilled:
	set '@name$,substr(strnpcinfo(2),0,2);
	if(!getmapmobs("this","ウィッシュメイデン#"+'@name$+"_b::OnKilled")) {
		donpcevent "okolnir#"+'@name$+"::OnStop";
		donpcevent "ウィッシュメイデン#"+'@name$+"_g::OnEnable";
		announce "ウィッシュメイデン : 見事だ……汝らに女神の光輝を受ける資格があることを認めよう……",0x9,0x00ff00;
	}
	end;
}
que_qaru01.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#F1_b	139
que_qaru02.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#F2_b	139
que_qaru03.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#F3_b	139
que_qaru04.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#F4_b	139
que_qaru05.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#F5_b	139
que_qsch01.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#N1_b	139
que_qsch02.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#N2_b	139
que_qsch03.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#N3_b	139
que_qsch04.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#N4_b	139
que_qsch05.gat,1,5,0	duplicate(ウィッシュメイデン#boss)	ウィッシュメイデン#N5_b	139

-	script	ウィッシュメイデン#gift	-1,{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	set '@name$,substr('@map$,5,3);
	set '@num,substr('@map$,9,1);
	set '@GID,getcastledata('@name$+"g_cas0"+'@num+".gat",1);
	if(getcharid(2) == '@GID) {
		if(strcharinfo(0) != getguildmaster('@GID)) {
			cutin "wish_maiden12",1;
			mes "[ウィッシュメイデン]";
			mes "皆、よくぞここまで努力してくれた。";
			mes "……人間の団結力は素晴らしいものだ。";
			mes "しかし、すぐ欲望に目が眩んでしまう。";
			next;
			mes "[ウィッシュメイデン]";
			mes "そんな不完全な存在だからこそ、";
			mes "神が見つめていらっしゃるのも";
			mes "頷ける話だ……";
			next;
			mes "[ウィッシュメイデン]";
			mes "だが……汝らは";
			mes "その日、その瞬間を";
			mes "堂々と生きるがいいだろう。";
			mes "自分の過去を悔いるようなことほど";
			mes "悲しいものはないからな。";
			close2;
			cutin "wish_maiden11",255;
			end;
		}
		if('@name$ == "aru") {
			setarray '@need,7835,7836,7837,7838,2513,7291,7293,7063,757;
			setarray '@amount,1,1,1,1,1,10,10,100,20;
			set '@gain, 2541; //アスプリカ
		}
		else if('@name$ == "sch") {
			setarray '@need,7830,7831,7832,7833,7834,2357,7510,969,757;
			setarray '@amount,1,1,1,1,1,1,100,10,20;
			set '@gain, 2383; //ブリュンヒルデ
		}
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1) {
			if(countitem('@need['@i]) >= '@amount['@i])
				set '@check, '@check + 1;
		}
		if('@check >= 9) {
			cutin "wish_maiden12",1;
			mes "[ウィッシュメイデン]";
			mes "試練を乗り越えここまで到達した";
			mes "汝らに、" +getitemname('@gain)+ "の力を与える。";
			mes "汝のもつそれらの品を";
			mes getitemname('@gain)+ "の力を持つ媒体で。";
			mes "鍛え上げるのだ……";
			next;
			mes "[ウィッシュメイデン]";
			mes "偉大なるヴァルキリーの";
			mes "能力が秘められている……";
			next;
			mes "[ウィッシュメイデン]";
			mes "後は、余興にひとつ、";
			mes "汝にちょっとしたものを贈ろう。";
			mes "楽しむが良い。";
			next;
			mes "[ウィッシュメイデン]";
			mes "ラヘルやジュノーで";
			mes "『ラビセフ』姉妹に会ってみると";
			mes "いいだろう。";
			next;
			cutin "wish_maiden32",1;
			mes "[ウィッシュメイデン]";
			mes "元の場所に戻るためのゲートを";
			mes "開いてやろう。";
			mes "オーコルニルは永遠ではないからな……";
			mes "フフフ……";
			for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1)
				delitem '@need['@i],'@amount['@i];
			getitem '@gain,1;
			getitem 7840,1;
			initnpctimer;
			hideonnpc;
			hideoffnpc "to_agit_gate#"+substr(strnpcinfo(2),0,2);
			announce "ギルド["+ GetGuildName('@GID) +"]のギルドマスター["+ strcharinfo(0) +"]によって、神器アイテム["+getitemname('@gain)+"]が誕生しました。",0;
			close2;
			cutin "wish_maiden11",255;
			end;
		}
		else {
			cutin "wish_maiden13",1;
			mes "[ウィッシュメイデン]";
			mes "試練を乗り越えここまで到達した";
			mes "汝らに、" +getitemname('@gain)+ "の";
			mes "力を与える……";
			mes "と言いたいところだが、";
			mes getitemname('@gain)+ "の力を授かる媒体……";
			mes "必要なアイテムが不足しているな。";
			next;
			mes "[ウィッシュメイデン]";
			mes "……何か忘れていないか？";
			close2;
		}
	}
	cutin "wish_maiden11",255;
	end;

OnEnable:
	hideoffnpc;
	initnpctimer;
	end;
OnDisable:
	hideonnpc;
	stopnpctimer;
	end;
OnTimer280000:
	announce "ウィッシュメイデン : オーコルニルは間もなく再び眠りにつく。汝らを元の場所に戻してやろう。",0x9,0x00ff00;
	end;
OnTimer290000:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	callfunc "GodSEAgitWarp",strnpcinfo(2);
	hideonnpc "to_agit_gate#"+substr(strnpcinfo(2),0,2);
	end;
OnTimer300000:
	set '@name$,substr(strnpcinfo(2),0,2);
	donpcevent "okolnir#"+'@name$+"::OnDisable";
	donpcevent "okolnir_time01#"+'@name$+"::OnEnable";
	set getvariableofnpc('gqse_mobcount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_pccount,"Gate_manager#"+ '@name$),0;
	set getvariableofnpc('gqse_cagecount,"gdtimer01#"+ '@name$),0;
	set getvariableofnpc('gqse_sealcount,"ウィッシュメイデン#"+ '@name$ +"_b"),0;
	stopnpctimer;
	end;
}
que_qaru01.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#F1_g	403
que_qaru02.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#F2_g	403
que_qaru03.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#F3_g	403
que_qaru04.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#F4_g	403
que_qaru05.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#F5_g	403
que_qsch01.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#N1_g	403
que_qsch02.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#N2_g	403
que_qsch03.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#N3_g	403
que_qsch04.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#N4_g	403
que_qsch05.gat,252,340,3	duplicate(ウィッシュメイデン#gift)	ウィッシュメイデン#N5_g	403

que_qaru01.gat,252,339,0	warp	to_agit_gate#F1	1,1,arug_cas01.gat,157,369
que_qaru02.gat,252,339,0	warp	to_agit_gate#F2	1,1,arug_cas02.gat,349,355
que_qaru03.gat,252,339,0	warp	to_agit_gate#F3	1,1,arug_cas03.gat,321,153
que_qaru04.gat,252,339,0	warp	to_agit_gate#F4	1,1,arug_cas04.gat,321,153
que_qaru05.gat,252,339,0	warp	to_agit_gate#F5	1,1,arug_cas05.gat,321,153
que_qsch01.gat,252,339,0	warp	to_agit_gate#N1	1,1,schg_cas01.gat,369,306
que_qsch02.gat,252,339,0	warp	to_agit_gate#N2	1,1,schg_cas02.gat,177,355
que_qsch03.gat,252,339,0	warp	to_agit_gate#N3	1,1,schg_cas03.gat,81,95
que_qsch04.gat,252,339,0	warp	to_agit_gate#N4	1,1,schg_cas04.gat,369,306
que_qsch05.gat,252,339,0	warp	to_agit_gate#N5	1,1,schg_cas05.gat,369,306

-	script	okolnir_timer#Okolnir	-1,{
OnEnable:
	initnpctimer;
	set $GodSEActivete['castle],2;
	end;
OnReset:
	set $GodSEActivete['castle],0;
	stopnpctimer;
	end;
OnTimer3600000:
	if($GodSEActivete['castle] < 14) {
		set $GodSEActivete['castle],$GodSEActivete['castle]+1;
		initnpctimer;
	}
	else if($GodSEActivete['castle] == 14) {
		set $GodSEActivete['castle],0;
		set '@name$,strnpcinfo(2);
		hideoffnpc "ウィッシュメイデン#"+'@name$+"_e";
		hideoffnpc "ピアメット#"+'@name$;
		hideoffnpc "ウィッシュメイデン#"+'@name$+"_b";
		stopnpctimer;
	}
	end;
OnInit:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if('@map$ == "-")					//duplicate元は何もしない
		end;
	set '@name$,substr(strnpcinfo(2),0,1);
	set '@num,substr(strnpcinfo(2),1,1);
	if('@name$ == "F")
		set 'castle,0;
	else if('@name$ == "N")
		set 'castle,5;
	if('@num > 0)
		set 'castle,'castle+'@num-1;
	if($GodSEActivete['castle] >= 2)
		initnpctimer;
	end;
}
que_qaru01.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#F1	139
que_qaru02.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#F2	139
que_qaru03.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#F3	139
que_qaru04.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#F4	139
que_qaru05.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#F5	139
que_qsch01.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#N1	139
que_qsch02.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#N2	139
que_qsch03.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#N3	139
que_qsch04.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#N4	139
que_qsch05.gat,1,6,0	duplicate(okolnir_timer#Okolnir)	okolnir_time01#N5	139

que_qaru01.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru01.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru01.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru01.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru02.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru02.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru02.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru03.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru03.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru03.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru04.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru04.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru04.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qaru05.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qaru05.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qaru05.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch01.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch01.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch01.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch02.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch02.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch02.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch03.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch03.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch03.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch04.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch04.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch04.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,116,313,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,120,285,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,117,236,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,103,223,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,85,204,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,79,186,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,73,167,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,68,150,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,71,128,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,69,118,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,117,78,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,110,79,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,141,80,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,158,84,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,193,104,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,119,269,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,155,77,0,0	monster	ガーデンキーパー	1932,1,180000,0,0
que_qsch05.gat,110,317,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,115,295,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,116,256,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,113,242,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,99,223,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,94,216,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,77,198,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,70,174,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,72,147,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,64,134,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,77,107,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,84,88,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,98,82,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,129,79,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,91,124,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,173,95,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,179,127,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,195,120,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,178,159,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,88,145,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,94,157,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,95,177,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,129,196,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,154,196,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,170,187,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,194,180,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
que_qsch05.gat,214,181,0,0	monster	ガーデンウォッチャー	1933,1,600000,0,0
que_qsch05.gat,243,199,0,0	monster	ガーデンウォッチャー	1933,1,1200000,0,0
