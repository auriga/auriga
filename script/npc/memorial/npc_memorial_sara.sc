//= Auriga Script ==============================================================
// Ragnarok Online Memory of Sara Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
dali.gat,130,107,5	script	探検家レーン#sara	945,{
	if((Job <= Job_Dancer && Upper != UPPER_HIGH) ||
		Job == Job_Taekwon || Job == Job_StarGladiator || Job == Job_SoulLinker || BaseLevel < 85
	) {
		mes "[探検家レーン]";
		mes "うむ……君はまだ未熟だから";
		mes "ここを探検するのは難しい。";
		mes "もう少し力を付けてから来てくれ！";
		next;
		mes "‐探検家レーンに力不足を";
		mes "　指摘された。";
		mes "　^ff0000特殊1次職、上位2次職、3次職、";
		mes "　限界突破したスーパーノービス、";
		mes "　影狼、朧、リベリオン、ドラム族の";
		mes "　BaseLv85以上^000000になったら";
		mes "　また来よう‐";
		close;
	}
	switch(checkquest(15003)) {
	case 0:
		if(SARA_1QUE == 0) {	// 初回
			mes "[探検家レーン]";
			mes "おお……私以外にも";
			mes "ここを訪ねて来る人がいるとは……";
			mes "驚いたよ！";
			next;
			mes "[探検家レーン]";
			mes "あ、失礼！";
			mes "私は探検家のレーンだ。";
			next;
			mes "[探検家レーン]";
			mes "ここは本当に……不思議な場所だ……";
			next;
			mes "[探検家レーン]";
			mes "探検をすればするほどさらに新しく、";
			mes "不思議な世界が広がる。";
			mes "例えば私の前にある";
			mes "次元の狭間のように。";
			next;
			mes "[探検家レーン]";
			mes "この次元の狭間は";
			mes "過去のフェイヨンと繋がっているようだ。";
			mes "私の力ではあまり調べられなかったが、";
			mes "この中には何かがあるという事が";
			mes "強く感じられる。";
			next;
			mes "[探検家レーン]";
			mes "何を根拠にかって？";
			mes "今まで数多くの場所を探検して来た";
			mes "私の勘がそう言っているのだよ！";
			next;
			mes "[探検家レーン]";
			mes "それで何だが……";
			mes "君にひとつお願いしたい事がある。";
			next;
			mes "[探検家レーン]";
			mes "私の代わりに次元の狭間を";
			mes "探検してきてくれ。";
			mes "何かが起きているに違いない！";
			next;
			mes "[探検家レーン]";
			mes "そこで聞いて、見た事を";
			mes "私に知らせてくれればいい。";
			mes "とても簡単な事じゃないか！";
			mes "早く行ってみなさい！";
			next;
			mes "[探検家レーン]";
			mes "ちなみにこの次元の狭間は";
			mes "とても不安定な状態だ。";
			mes "もし周辺が歪んでいるように見えたら";
			mes "すぐ外に出るんだ！";
			next;
			mes "[探検家レーン]";
			mes "よし、それじゃ準備はいいか？";
			mes "頼んだぞ！";
			next;
			mes "‐探検家レーンに無理やり頼まれて";
			mes "　しまった。まずはあの前にある";
			mes "　次元移動機を調べてみよう‐";
			setquest 15003;
			close;
		}
		mes "[探検家レーン]";
		mes "またフェイヨン次元の狭間を";
		mes "探検しに来たのか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[探検家レーン]";
			mes "そうか、また行きたくなったら";
			mes "声をかけてくれ。";
			close;
		}
		mes "[探検家レーン]";
		mes "何か発見があるかもしれない。";
		mes "帰ったら私に話を聞かせてくれ！";
		if(
			(checkquest(118900) && (!(checkquest(15002) & 0x2) || !(checkquest(118900) & 0x2)) ) ||
			(!checkquest(118900) && checkquest(15002) && !(checkquest(15002) & 0x2) )
		) {
			next;
			mes "[探検家レーン]";
			mes "次元の狭間の探検に失敗したのか？";
			mes "歪んだ次元が元に戻るまでは";
			mes "しばらくの時間が必要だ。";
			next;
			mes "[探検家レーン]";
			mes "もう一度探検をしたいのなら";
			mes "入場してから次の";
			mes "^ff0000午前5時以降^000000に来てくれ。";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過しないと";
			mes "チャレンジ出来ないぞ。";
			close;
		}
		delquest 15002;
		delquest 118900;
		setquest 15003;
		close;
	case 8:
		if(SARA_1QUE == 0) {	// 初回
			mes "[探検家レーン]";
			mes "次元の狭間の内部を探検して来たのか？";
			mes "それでそこはどうだったんだ？";
			mes "説明してくれ！　早く！";
			next;
			mes "‐次元の狭間の内部で経験した事を";
			mes "　レーンに話そうとしたが、";
			mes "　何があったのかまったく";
			mes "　思い出せなかった‐";
			next;
			mes "[探検家レーン]";
			mes "うむ……そうか……";
			mes "その様子を見ると";
			mes "何かあったのかもしれないな。";
			next;
			mes "[探検家レーン]";
			mes "なに、落ち込まなくていい。";
			mes "別の次元を探検しているんだ。";
			mes "記憶の混濁が起こったとしても";
			mes "何も不思議なことではない。";
			next;
			mes "[探検家レーン]";
			mes "君も疲れただろう。少し休んでいなさい。";
			mes "次元の狭間を再度探検してみたかったら、";
			mes "後でまた話しかけてくれればいい。";
			next;
			mes "[探検家レーン]";
			mes "ただし歪んだ次元が元に戻るまでは";
			mes "ある程度の時間がかかるのだ。";
			next;
			mes "[探検家レーン]";
			mes "もう一度探検をしたいのなら";
			mes "入場してから次の";
			mes "^ff0000午前5時以降^000000に来てくれ。";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過しないと";
			mes "チャレンジ出来ないぞ。";
		}
		else {
			mes "[探検家レーン]";
			mes "フェイヨン次元の狭間を";
			mes "探検して来たのか？";
			mes "どうだった？";
			mes "今度は何があったか覚えているか？";
			next;
			mes "‐今回も何も思い出せないと伝えた‐";
			next;
			mes "[探検家レーン]";
			mes "うむ……それは残念だ。";
			mes "ひょっとすると過去のフェイヨンには";
			mes "何かあるのかもしれないな。";
			next;
			mes "[探検家レーン]";
			mes "また行きたくなったら";
			mes "後で私に話しかけてくれ。";
			next;
			mes "[探検家レーン]";
			mes "ただし歪んだ次元が元に戻るまでは";
			mes "ある程度の時間がかかるのだ。";
			next;
			mes "[探検家レーン]";
			mes "もう一度探検をしたいのなら";
			mes "入場してから次の";
			mes "^ff0000午前5時以降^000000に来てくれ。";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過しないと";
			mes "チャレンジ出来ないぞ。";
			next;
			mes "[探検家レーン]";
			mes "さて……次元の狭間の探検で";
			mes "君も疲れただろう、";
			mes "少し休んでいなさい。";
		}
		delquest 15003;
		set SARA_1QUE,1;
		if(Job >= Job_RuneKnight && Job <= Job_Summoner) {
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,500000;
		}
		else {
			getexp 0,500000;
			getexp 0,500000;
			if(JobLevel >= 60) {
				getexp 0,500000;
				if(JobLevel >= 65)
					getexp 0,500000;
			}
		}
		close;
	default:
		if(checkquest(15002)) {
			if(
				(checkquest(118900) && (!(checkquest(15002) & 0x2) || !(checkquest(118900) & 0x2)) ) ||
				(!checkquest(118900) && !(checkquest(15002) & 0x2) )
			) {
				mes "[探検家レーン]";
				mes "次元の狭間の探検に失敗したのか？";
				mes "歪んだ次元が元に戻るまでは";
				mes "しばらくの時間が必要だ。";
				next;
				mes "[探検家レーン]";
				mes "もう一度探検をしたいのなら";
				mes "入場してから次の";
				mes "^ff0000午前5時以降^000000に来てくれ。";
				mes "但し、最後の入場をしてから";
				mes "^ff00001時間^000000経過しないと";
				mes "チャレンジ出来ないぞ。";
				close;
			}
			mes "[探検家レーン]";
			mes "またここの次元の狭間に";
			mes "入れるようになったようだぞ。";
			mes "早く行って、探検の結果を";
			mes "私に知らせてくれ！";
			delquest 15002;
			delquest 118900;
			close;
		}
		mes "[探検家レーン]";
		mes "まだ次元の狭間の探検が";
		mes "途中のようだね……";
		mes "諦めたくなったら言ってくれ。";
		next;
		if(select("いいえ","諦める") == 1) {
			mes "[探検家レーン]";
			mes "思ったより根性があるな。";
			mes "それでは頑張ってくれ。";
			mes "早く探検の結果を私に知らせてくれ！";
			close;
		}
		mes "[探検家レーン]";
		mes "無理に頼んでしまい悪いことをしたね。";
		mes "気が向いたらまた頼みを聞いてくれ。";
		delquest 15003;
		close;
	}
	end;
OnInit:
	waitingroom "サラの記憶",0;
	end;
}

//============================================================
// ダンジョン入場NPC
//------------------------------------------------------------
dali.gat,139,118,3	script	次元移動機#sara	10007,{
	if((Job <= Job_Dancer && Upper != UPPER_HIGH) ||
		Job == Job_Taekwon || Job == Job_StarGladiator || Job == Job_SoulLinker || BaseLevel < 85
	) {
		mes "‐このダンジョンは、";
		mes "　^ff0000特殊1次職、上位2次職、3次職、";
		mes "　限界突破したスーパーノービス、";
		mes "　影狼、朧のBaseLv85以上^000000のみ";
		mes "　入場できます‐";
		close;
	}
	if(!(checkquest(15003)&1)) {
		mes "^ff0000‐まずは探検家レーンに話しかけ、";
		mes "　探検することを伝えよう‐^000000";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "^ff0000‐次元の狭間に入場するためには";
		mes "　パーティーを結成してください‐^000000";
		close;
	}
	set '@party$,getpartyname(getcharid(1));
	set '@leader$,getpartyleader(getcharid(1));
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "‐次元移動機がある。";
		mes "　ここからフェイヨンの次元の狭間に";
		mes "　行けるようだ‐";
		set '@str1$,"次元の狭間の生成";
		set '@str2$,"サラの記憶に入場";
		next;
	}
	else {
		set '@str2$,"サラの記憶に入場";
	}
	switch(select('@str1$,'@str2$,"やめる")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "‐パーティー名";
			mes "　" +'@party$;
			mes "　パーティーリーダー";
			mes "　" +'@leader$;
			mes "^0000ffMemory of Sara^000000";
			mes "生成に失敗しました‐";
			close;
		}
		mdcreate "Memory of Sara";
		mes "^ff0000‐次元の狭間を生成します‐^000000";
		close;
	case 2:
		switch(mdenter("Memory of Sara")) {
		case 0:	// エラーなし
			announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Memory of Sara]に入場します",0x9,0x00FF99;
			setquest 15002;
			setquest 118900;
			donpcevent getmdnpcname("#hugin_sara1")+ "::OnStart";
			//warp "1@sara.gat",250,155;
			end;
		case 1:	// パーティー未加入
			mes "^ff0000‐あなたのパーティーでは";
			mes "　次元の狭間には入場できません‐^000000";
			close;
		case 2:	// ダンジョン未作成
			mes "^ff0000‐次元の狭間が生成されていません‐^000000";
			close;
		default:	// その他エラー
			close;
		}
	case 3:
		mes "‐次元移動機から離れた‐";
		close;
	}
}

//============================================================
// サラの記憶
//------------------------------------------------------------
1@sara.gat,246,159,3	script	#hugin_sara1	111,5,5,{
	end;
OnTouch:
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "sara_beholder",2;
		mes "[？？？？？]";
		mes "かつて……";
		unittalk "？？？？？ : かつて……";
		next;
		mes "‐どこからともなく響く声が";
		mes "　こちらに語りかけてくる……‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐どこからともなく響く声がこちらに語りかけてくる……‐";
		next;
		mes "[？？？？？]";
		mes "かつて存在したという";
		mes "強大な力を持つヴァルキリー、サラ。";
		mes "彼女が世界に与えた影響は、";
		mes "少なくありません。";
		unittalk "？？？？？ : かつて存在したという強大な力を持つヴァルキリー、サラ。彼女が世界に与えた影響は、少なくありません。";
		next;
		mes "[？？？？？]";
		mes "彼女は闇の道を進みました。";
		mes "ではなぜ、彼女は闇の道を";
		mes "選んだのか……。";
		unittalk "？？？？？ : 彼女は闇の道を進みました。ではなぜ、彼女は闇の道を選んだのか……。";
		next;
		mes "[？？？？？]";
		mes "サラの幼き頃、その身に起きた出来事を";
		mes "見てみましょう。";
		unittalk "？？？？？ : サラの幼き頃、その身に起きた出来事を見てみましょう。";
		close2;
		cutin "sara_beholder",255;
		hideonnpc getmdnpcname("#hugin_sara1");
	}
	end;
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("warp01#sara0");
	hideonnpc getmdnpcname("warp12#sara1");
	hideonnpc getmdnpcname("warp56#sara5");
	hideonnpc getmdnpcname("warp67#sara6");

	hideonnpc getmdnpcname("大長老アイリン#sara");
	hideonnpc getmdnpcname("サラ・アイリン#sa1a");
	hideonnpc getmdnpcname("サラ・アイリン#sa1b");
	hideonnpc getmdnpcname("サラ・アイリン#sa1c");
	hideonnpc getmdnpcname("サラ・アイリン#sa1d");
	hideonnpc getmdnpcname("サラ・アイリン#sa1e");
	hideonnpc getmdnpcname("サラ・アイリン#sa2b");
	hideonnpc getmdnpcname("サラ・アイリン#sa2c");
	hideonnpc getmdnpcname("サラ・アイリン#sa2d");
	hideonnpc getmdnpcname("サラ・アイリン#sa3b");
	hideonnpc getmdnpcname("サラ・アイリン#sa3c");
	hideonnpc getmdnpcname("サラ・アイリン#sa4b");
	hideonnpc getmdnpcname("サラ・アイリン#sa4c");
	hideonnpc getmdnpcname("サラ・アイリン#sa5");
	hideonnpc getmdnpcname("大長老アイリン#sa5a");
	hideonnpc getmdnpcname("大長老アイリン#sa5b");

	hideonnpc getmdnpcname("#oldman_a_sara1");
	hideonnpc getmdnpcname("#oldman_b_sara1");
	hideonnpc getmdnpcname("#papa_mama_sara1");
	hideonnpc getmdnpcname("#paydef_sara1");
	hideonnpc getmdnpcname("#hugin_sara2");
	hideonnpc getmdnpcname("#warp_end_sara6");
	hideonnpc getmdnpcname("bgmchg#sara0");
	hideonnpc getmdnpcname("bgmchg#sara1");
	hideonnpc getmdnpcname("navi#sara0");
	end;
}

1@sara.gat,240,145,0	warp	warp01#sara0	2,2,1@sara.gat,94,320
1@sara.gat,208,250,0	warp	warp12#sara1	2,2,1@sara.gat,230,316
1@sara.gat,226,190,0	warp	warp23#sara2	2,2,1@sara.gat,263,94
1@sara.gat,166,67,0		warp	warp34#sara3	2,2,1@sara.gat,164,81
1@sara.gat,155,180,0	script	warp45#sara4	45,2,2,{
	hideonnpc getmdnpcname("warp01#sara0");
	hideonnpc getmdnpcname("warp12#sara1");
	warp getmdmapname("1@sara.gat"),155,196;
	end;
}

1@sara.gat,250,155,0	script	bgmchg#sara0	139,1,1,{
	musiceffect "14";
	end;
}

1@sara.gat,107,326,0	script	bgmchg#sara1	139,10,10,{
	musiceffect "37";
	end;
OnStart:
	initnpctimer;
	hideoffnpc;
	end;
OnTimer3000:
	stopnpctimer;
OnInit:
	hideonnpc;
	end;
}

1@sara.gat,261,156,5	script	少女#sara0	668,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "‐花を抱えた少女がいる。";
		mes "　褐色がかった肌の色をした少女は、";
		mes "　少しすねたような表情をしている‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐花を抱えた少女がいる。褐色がかった肌の色をした少女は、少しすねたような表情をしている‐";
		next;
		if(SARA_1QUE > 0) {
			if(select("急ぐ","会話をする") == 1) {
				mes "‐サラの身に何か";
				mes "　悪いことが起きそうだ。";
				mes "　急いでサラを探そう‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐サラの身に何か悪いことが起きそうだ。急いでサラを探そう‐";
				hideonnpc getmdnpcname("少女#sara0");
				hideoffnpc getmdnpcname("warp01#sara0");
				hideoffnpc getmdnpcname("navi#sara0");
				close;
			}
		}
		mes "‐少女にここが何処なのかを訪ねると、";
		mes "　にっこりと、ひとなつっこい笑顔で";
		mes "　こちらを見た‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐少女にここが何処なのかを訪ねると、にっこりと、ひとなつっこい笑顔でこちらを見た‐";
		next;
		cutin "sara_9sara1",2;
		mes "[少女]";
		mes "ここはフェイヨンだよ！";
		mes ((Sex)? "お兄さん": "お姉さん")+ "はこの町の人では";
		mes "ないみたいだね？";
		unittalk "少女 : ここはフェイヨンだよ！　" +((Sex)? "お兄さん": "お姉さん")+ "はこの町の人ではないみたいだね？";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "君はこの町の人？";
		mes "肌の色が少し違うけど……";
		unittalk getcharid(3),strcharinfo(0)+" : 君はこの町の人？　肌の色が少し違うけど……";
		next;
		mes "[サラ]";
		mes "うん、そうだよ！";
		mes "私はフェイヨンで生まれたの。";
		mes "名前はサラ、サラ・アイリンなの！";
		unittalk "サラ : うん、そうだよ！　私はフェイヨンで生まれたの。名前はサラ、サラ・アイリンなの！";
		next;
		mes "[サラ]";
		mes "私の肌の色はね、えへへ！";
		mes "ママと同じなんだぁ！";
		unittalk "サラ : 私の肌の色はね、えへへ！　ママと同じなんだぁ！";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "そうなんだ。";
		mes "それで、ここで何をしていたの？";
		unittalk getcharid(3),strcharinfo(0)+" : そうなんだ。それで、ここで何をしていたの？";
		next;
		mes "[サラ]";
		mes "パパを待ってるの。";
		mes "パパはこの町の大長老なんだよ！";
		unittalk "サラ : パパを待ってるの。パパはこの町の大長老なんだよ！";
		next;
		mes "[サラ]";
		mes "パパ、遅いなぁ……";
		mes "すぐ来るって言っていたのに……";
		unittalk "サラ : パパ遅いなぁ……すぐ来るって言っていたのに……";
		next;
		hideoffnpc getmdnpcname("大長老アイリン#sara");
		mes "[大長老アイリン]";
		mes "サラ、待たせてしまったね。";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk1";
		next;
		mes "[サラ]";
		mes "パパ！";
		unittalk "サラ : パパ！";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "おやおや、私のお姫様、";
		mes "ずいぶんご機嫌だな。";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk2";
		next;
		cutin "sara_9sara1",0;
		mes "[サラ]";
		mes "も～！";
		mes "すぐ来るって言ったのに！";
		mes "パパの嘘つき！";
		unittalk "サラ : も～！　すぐ来るって言ったのに！　パパの嘘つき！";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "ああ、ごめんよ。";
		mes "長老たちとの会議が思ったより";
		mes "長引いてしまったんだ。";
		mes "パパを許しておくれ。";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk3";
		next;
		cutin "sara_9sara1",0;
		mes "[サラ]";
		mes "……私、あのお爺さん達キライ！";
		unittalk "サラ : ……私、あのお爺さん達キライ！";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "そんなことをいっちゃダメだぞ。";
		mes "ん？　この方は……";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk4";
		next;
		mes "‐大長老アイリンは";
		mes "　ジロリとこちらを観察した後、";
		mes "　目で挨拶してきた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐大長老アイリンはジロリとこちらを観察した後、目で挨拶してきた‐";
		next;
		cutin "sara_elder_irine2",2;
		mes "‐一瞬敵意が含まれているように";
		mes "　感じたのは、気のせいだろうか……‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐一瞬敵意が含まれているように感じたのは、気のせいだろうか……‐";
		next;
		mes "‐サラは満面の笑顔で、";
		mes "　手に持った花の束を";
		mes "　大長老アイリンに差し出した‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラは満面の笑顔で、手に持った花の束を大長老アイリンに差し出した‐";
		next;
		cutin "sara_9sara1",0;
		mes "[サラ]";
		mes "はい、これ！";
		unittalk "サラ : はい、これ！";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "これは……";
		mes "こんな綺麗な花をお父さんが";
		mes "貰ってもいいのかな？";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk5";
		next;
		cutin "sara_9sara1",0;
		mes "[サラ]";
		mes "うん、いいよ！";
		mes "えへへ……";
		mes "パパのために集めたんだぁ。";
		unittalk "サラ : いいよ！　えへへ……パパのために集めたんだぁ。";
		next;
		mes "‐サラから花を貰った大長老は";
		mes "　サラの体を持ち上げて";
		mes "　肩車に乗せた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラから花を貰った大長老は、サラの体を持ち上げて肩車に乗せた‐";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "さあ、私の小さなお姫様。";
		mes "今度はどこに行こうか？";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk6";
		next;
		cutin "sara_9sara1",2;
		mes "[サラ]";
		mes "あそこ！";
		mes "あそこの丘まで!!";
		unittalk "サラ : あそこ！　あそこの丘まで!!";
		next;
		cutin "sara_elder_irine1",2;
		mes "[大長老アイリン]";
		mes "よ～し！　では行くぞ～！";
		donpcevent getmdnpcname("大長老アイリン#sara")+"::OnTalk7";
		next;
		hideonnpc getmdnpcname("大長老アイリン#sara");
		hideonnpc getmdnpcname("少女#sara0");
		hideoffnpc getmdnpcname("warp01#sara0");
		hideoffnpc getmdnpcname("#oldman_a_sara1");
		hideoffnpc getmdnpcname("#oldman_b_sara1");
		cutin "sara_9sara1",255;
		mes "‐二人が丘の方に消えた頃、";
		mes "　近くから怪しい声が";
		mes "　聞こえてきた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐二人が丘の方に消えた頃、近くから怪しい声が聞こえてきた‐";
		next;
		mes "[怪しい老人A]";
		mes "サラの力が大きくなって行くのを";
		mes "感じる。";
		mes "これ以上、成長するのを";
		mes "見過ごす事はできない！";
		donpcevent getmdnpcname("#oldman_a_sara1")+"::OnTalk1";
		next;
		mes "[怪しい老人B]";
		mes "フェイヨンの正統な継承者でもない、";
		mes "異邦人の血筋……";
		mes "それも凶星の年に生まれた子だとは！";
		donpcevent getmdnpcname("#oldman_b_sara1")+"::OnTalk1";
		next;
		mes "[怪しい老人B]";
		mes "いつかこの町に血の嵐が";
		mes "吹き荒れるだろう。";
		donpcevent getmdnpcname("#oldman_b_sara1")+"::OnTalk2";
		next;
		mes "[怪しい老人A]";
		mes "四聖獣がサラを選択する前に、";
		mes "先に手を打たなければならない。";
		mes "あの者に頼んであるから、";
		mes "今晩やってくれるはずだ。";
		donpcevent getmdnpcname("#oldman_a_sara1")+"::OnTalk2";
		next;
		mes "[怪しい老人B]";
		mes "君がすでに手を打ってあると言うのなら";
		mes "信じて見守ることにしよう。";
		mes "……もうすぐ日が落ちる。";
		mes "よい報告を待っているぞ。";
		donpcevent getmdnpcname("#oldman_b_sara1")+"::OnTalk3";
		next;
		mes "‐対話を終えた二人の老人は";
		mes "　いつの間にかいなくなっていた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐対話を終えた二人の老人はいつの間にかいなくなっていた‐";
		next;
		mes "‐サラの身に何か";
		mes "　悪いことが起きそうだ。";
		mes "　急いでサラを探そう‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラの身に何か悪いことが起きそうだ。急いでサラを探そう‐";
		close2;
		hideonnpc getmdnpcname("#oldman_a_sara1");
		hideonnpc getmdnpcname("#oldman_b_sara1");
		hideoffnpc getmdnpcname("navi#sara0");
		end;
	}
	else {
		mes "[少女]";
		mes ((Sex)? "お兄さん": "お姉さん")+ "だぁれ？";
		next;
		mes "^ff0000‐イベントを進めるには";
		mes "　パーティーリーダーが";
		mes "　話しかけてください‐^000000";
		close;
	}
}

1@sara.gat,257,146,0	script	navi#sara0	139,10,10,{
OnTouch:
	viewpoint 1,240,145,1,0x00FF00;
	end;
}

1@sara.gat,268,158,3	script	大長老アイリン#sara	684,{
	cutin "sara_elder_irine1",2;
	mes "‐大長老アイリンは";
	mes "　優しい顔でサラをみつめており";
	mes "　こちらなど眼中に";
	mes "　入っていないようだ‐";
	close2;
	cutin "sara_elder_irine1",255;
	end;
OnTalk1:
	unittalk "大長老アイリン : サラ、待たせてしまったね。";
	end;
OnTalk2:
	unittalk "大長老アイリン : おやおや、私のお姫様、ずいぶんご機嫌だな。";
	end;
OnTalk3:
	unittalk "大長老アイリン : ああ、ごめんよ。長老たちとの会議が思ったより長引いてしまったんだ。パパを許しておくれ。";
	end;
OnTalk4:
	unittalk "大長老アイリン : そんなことを言っちゃダメだぞ。ん？　この方は……";
	end;
OnTalk5:
	unittalk "大長老アイリン : これは……こんな綺麗な花をお父さんが貰ってもいいのかな？";
	end;
OnTalk6:
	unittalk "大長老アイリン : さあ、私の小さなお姫様。今度はどこに行こうか？";
	end;
OnTalk7:
	unittalk "大長老アイリン : よ～し！　では行くぞ～！";
	end;
}

1@sara.gat,255,158,3	script	#oldman_a_sara1	111,{
	end;
OnTalk1:
	unittalk "怪しい老人A : サラの力が大きくなって行くのを感じる。これ以上、成長するのを見過ごす事はできない！";
	end;
OnTalk2:
	unittalk "怪しい老人A : 四聖獣がサラを選択する前に、先に手を打たなければならない。あの者に頼んであるから、今晩やってくれるはずだ。";
	end;
}

1@sara.gat,260,161,3	script	#oldman_b_sara1	111,{
	end;
OnTalk1:
	unittalk "怪しい老人B : フェイヨンの正統な継承者でもない、異邦人の血筋……それも凶星の年に生まれた子だとは！";
	end;
OnTalk2:
	unittalk "怪しい老人B : いつかこの町に血の嵐が吹き荒れるだろう。";
	end;
OnTalk3:
	unittalk "怪しい老人B : 君がすでに手を打ってあると言うのなら信じて見守ることにしよう。……もうすぐ日が落ちる。よい報告を待っているぞ。";
	end;
}

1@sara.gat,107,325,5	script	サラ・アイリン#sa1	668,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "sara_9sara1",2;
		mes "[サラ]";
		mes "あっ！";
		mes "さっきの" +((Sex)? "お兄さん": "お姉さん")+ "だぁ！";
		mes "なにかご用？";
		unittalk "サラ : あっ！　さっきの" +((Sex)? "お兄さん": "お姉さん")+ "だぁ！　なにかご用？";
		next;
		if(SARA_1QUE > 0) {
			if(select("急ぐ","会話をする") == 1) {
				cutin "sara_9sara1",255;
				mes "‐突然サラは叫びながら";
				mes "　駆け出した。";
				mes "　その間に警備兵がこちらを";
				mes "　取り囲む‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐突然サラは叫びながら駆け出した。その間に警備兵がこちらを取り囲む‐";
				hideonnpc getmdnpcname("サラ・アイリン#sa1");
				announce "南の方角に逃げたサラを追いかけよう！",0x9,0xffff00;
				donpcevent getmdnpcname("サラ・アイリン#sa1")+"::OnStart";
				hideoffnpc getmdnpcname("サラ・アイリン#sa1a");
				hideoffnpc getmdnpcname("warp12#sara1");
				close;
			}
		}
		mes "[サラ]";
		mes "あ、ちょっと待ってね、";
		mes "ママにお花を渡すの！";
		mes "うふふ、これはママの、";
		mes "これはパパの!!";
		unittalk "サラ : あ、ちょっと待ってね、ママにお花を渡すの！　うふふ、これはママの、これはパパの!!";
		next;
		mes "‐サラは両親の為に持って来た";
		mes "　花を一時でも早く渡そうとして";
		mes "　急いで家の扉を開けた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラは両親の為に持って来た花を一時でも早く渡そうとして、急いで家の扉を開けた‐";
		next;
		mes "[サラ]";
		mes "ママ、パパ！　これ見て！";
		mes "私がね……！";
		unittalk "サラ : ママ、パパ！　これ見て！　私がね……！";
		next;
		musiceffect "37";
		cutin "sara_momdie",4;
		mes "‐そこには刃物で刺されたのか、";
		mes "　血を流して倒しているサラの母親と、";
		mes "　刀を持ち、全身に血を浴びた";
		mes "　大長老アイリンがいた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐そこには刃物で刺されたのか、血を流して倒しているサラの母親と、刀を持ち、全身に血を浴びた大長老アイリンがいた‐";
		next;
		mes "[サラ]";
		mes "え…………";
		unittalk "サラ : え…………";
		next;
		mes "[サラの母親]";
		mes "……サラ…………";
		mes "こ……ここは……危ないわ……";
		mes "早く……逃げなさい……。";
		donpcevent getmdnpcname("#papa_mama_sara1")+"::OnTalk1";
		next;
		mes "[サラ]";
		mes "！！！！！！！！！！！";
		unittalk "サラ : ！！！！！！！！！！！";
		next;
		mes "‐サラの母親が握っていた玉が";
		mes "　サラの足元まで落ちて転がった。";
		mes "　サラは目の前で起きている光景を";
		mes "　理解できないまま、無意識で";
		mes "　玉を拾う‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラの母親が握っていた玉がサラの足元まで落ちて転がった。サラは目の前で起きている光景を理解できないまま、無意識で玉を拾う‐";
		next;
		mes "‐その瞬間、刀を握った";
		mes "　大長老アイリンが";
		mes "　サラの存在に気が付き、";
		mes "　振り返った‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐その瞬間、刀を握った大長老アイリンがサラの存在に気が付き、振り返った‐";
		next;
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "サラ……";
		mes "ちょうどお前を探していたんだ……。";
		donpcevent getmdnpcname("#papa_mama_sara1")+"::OnTalk2";
		next;
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "………";
		unittalk "サラ : ………";
		next;
		menu "サラを連れて脱出する",-;
		mes "‐危機を直感し、茫然と立っている";
		mes "　サラを連れてここから";
		mes "　出ようとした‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐危機を直感し、茫然と立っているサラを連れてここから出ようとした‐";
		next;
		cutin "sara_elder_irine3",2;
		mes "[大長老アイリン]";
		mes "警備兵!!";
		mes "ここに妻を殺害した奴がいる！";
		mes "こいつを捕まえろ！";
		donpcevent getmdnpcname("#papa_mama_sara1")+"::OnTalk3";
		next;
		mes "‐大長老が指示を出すと、";
		mes "　警備兵達が集まって来る音が";
		mes "　聞こえてきた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐大長老が指示を出すと、警備兵達が集まって来る音が聞こえてきた‐";
		next;
		cutin "sara_9sara3",2;
		mes "[サラ]";
		mes "うわあああ！！！！！";
		unittalk "サラ : うわあああ！！！！！";
		next;
		cutin "sara_9sara3",255;
		mes "‐突然サラは叫びながら";
		mes "　駆け出した。";
		mes "　その間に警備兵がこちらを";
		mes "　取り囲む‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐突然サラは叫びながら駆け出した。その間に警備兵がこちらを取り囲む‐";
		hideonnpc getmdnpcname("サラ・アイリン#sa1");
		hideonnpc getmdnpcname("#papa_mama_sara1");
		announce "南の方角に逃げたサラを追いかけよう！",0x9,0xffff00;
		donpcevent getmdnpcname("サラ・アイリン#sa1")+"::OnStart";
		hideoffnpc getmdnpcname("サラ・アイリン#sa1a");
		hideoffnpc getmdnpcname("warp12#sara1");
		close;
	}
	else {
		cutin "sara_9sara1",2;
		mes "[サラ]";
		mes ((Sex)? "お兄さん": "お姉さん")+ "だぁれ？";
		next;
		cutin "sara_9sara1",255;
		mes "^ff0000‐イベントを進めるには";
		mes "　パーティーリーダーが";
		mes "　話しかけてください‐^000000";
		close;
	}
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@mob1,callmonster('@mdmap$,99,323,"フェイヨン警備兵#23sr1",2543);
	set '@mob2,callmonster('@mdmap$,99,317,"フェイヨン警備兵#24sr1",2543);
	set '@mob3,callmonster('@mdmap$,99,311,"フェイヨン警備兵#25sr1",2543);
	set '@mob4,callmonster('@mdmap$,116,323,"フェイヨン警備兵#26sr1",2543);
	set '@mob5,callmonster('@mdmap$,116,317,"フェイヨン警備兵#27sr1",2543);
	set '@mob6,callmonster('@mdmap$,116,311,"フェイヨン警備兵#28sr1",2543);
	unittalk '@mob1,"フェイヨン警備兵 : 侵入者だ！";
	unittalk '@mob3,"フェイヨン警備兵 : あいつを捕まえろ！！";
	unittalk '@mob4,"フェイヨン警備兵 : もうすぐ休暇なのに……どうして……";
	unittalk '@mob6,"フェイヨン警備兵 : 止まれ！";
	hideoffnpc getmdnpcname("bgmchg#sara1");
	hideonnpc getmdnpcname("bgmchg#sara1");
	end;
}

1@sara.gat,109,327,3	script	#papa_mama_sara1	111,{
	end;
OnTalk1:
	unittalk "サラの母親 : ……サラ…………こ……ここは……危ないわ……早く……逃げなさい……。";
	end;
OnTalk2:
	unittalk "大長老アイリン : サラ……ちょうどお前を探していたんだ……。";
	end;
OnTalk3:
	unittalk "大長老アイリン : 警備兵!!　ここに妻を殺害した奴がいる！　こいつを捕まえろ！";
	end;
}

1@sara.gat,110,300,5	script	サラ・アイリン#sa1a	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : わあああ！！！！！！";
	hideonnpc getmdnpcname("サラ・アイリン#sa1a");
	hideoffnpc getmdnpcname("サラ・アイリン#sa1b");
	announce "サラは南の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,107,231,5	script	サラ・アイリン#sa1b	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : わあああっ！！！！！！";
	hideonnpc getmdnpcname("サラ・アイリン#sa1b");
	hideoffnpc getmdnpcname("サラ・アイリン#sa1c");
	announce "サラは東の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,142,229,5	script	サラ・アイリン#sa1c	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ぐすっ……ママ……ママぁ……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa1c");
	hideoffnpc getmdnpcname("サラ・アイリン#sa1d");
	announce "サラは東の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,171,228,5	script	サラ・アイリン#sa1d	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ママ……痛そうなママ……ぐすっ……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa1d");
	hideoffnpc getmdnpcname("サラ・アイリン#sa1e");
	announce "サラは北の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,185,249,5	script	サラ・アイリン#sa1e	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ママ……死んじゃやだあ……っ。";
	hideonnpc getmdnpcname("サラ・アイリン#sa1e");
	announce "サラはこの先に逃げていってしまった。",0x9,0xffff00;
	viewpoint 1,208,250,1,0x00FF00;
	end;
}

1@sara.gat,112,296,0	script	callmon_a#sara1	139,11,4,{
	hideonnpc getmdnpcname("callmon_a#sara1");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_a#sara1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,101,295,"フェイヨン警備兵#29sr1",2543,'@event$);
	set '@mob2,callmonster('@mdmap$,109,295,"フェイヨン警備兵#30sr1",2543,'@event$);
	set '@mob3,callmonster('@mdmap$,115,295,"フェイヨン警備兵#31sr1",2543,'@event$);
	set '@mob4,callmonster('@mdmap$,123,295,"フェイヨン警備兵#32sr1",2543,'@event$);
	unittalk '@mob2,"フェイヨン警備兵 : サラ様を守るぞ！";
	unittalk '@mob3,"フェイヨン警備兵 : あいつを捕まえろ！！";
	end;
OnKilled:
	end;
}

1@sara.gat,117,225,0	script	callmon_b#sara1	139,12,2,{
	hideonnpc getmdnpcname("callmon_b#sara1");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_b#sara1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,122,217,"フェイヨン警備兵#1sr1",2543,'@event$);
	set '@mob2,callmonster('@mdmap$,122,219,"フェイヨン警備兵#2sr1",2543,'@event$);
	set '@mob3,callmonster('@mdmap$,122,221,"フェイヨン警備兵#3sr1",2543,'@event$);
	set '@mob4,callmonster('@mdmap$,122,223,"フェイヨン警備兵#4sr1",2543,'@event$);
	set '@mob5,callmonster('@mdmap$,122,225,"フェイヨン警備兵#5sr1",2543,'@event$);
	set '@mob6,callmonster('@mdmap$,122,227,"フェイヨン警備兵#6sr1",2543,'@event$);
	set '@mob7,callmonster('@mdmap$,120,217,"大人しい警備犬#1sara1",2545,'@event$);
	set '@mob8,callmonster('@mdmap$,120,219,"大人しい警備犬#2sara1",2545,'@event$);
	set '@mob9,callmonster('@mdmap$,120,221,"大人しい警備犬#3sara1",2545,'@event$);
	set '@mob10,callmonster('@mdmap$,120,223,"大人しい警備犬#4sara1",2545,'@event$);
	set '@mob11,callmonster('@mdmap$,120,225,"大人しい警備犬#5sara1",2545,'@event$);
	set '@mob12,callmonster('@mdmap$,120,227,"大人しい警備犬#6sara1",2545,'@event$);
	unittalk '@mob2,"フェイヨン警備兵 : いたぞ！";
	unittalk '@mob4,"フェイヨン警備兵 : あいつを捕まえろ！！";
	unittalk '@mob4,"フェイヨン警備兵 : 逃がすな！！";
	unittalk '@mob8,"大人しい警備犬 : クゥゥン……";
	end;
OnKilled:
	end;
}

1@sara.gat,155,233,0	script	callmon_c#sara1	139,10,8,{
	hideonnpc getmdnpcname("callmon_c#sara1");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_c#sara1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,151,231,"フェイヨン警備兵#7sr1",2543,'@event$);
	set '@mob2,callmonster('@mdmap$,153,231,"フェイヨン警備兵#8sr1",2543,'@event$);
	set '@mob3,callmonster('@mdmap$,155,231,"フェイヨン警備兵#9sr1",2543,'@event$);
	set '@mob4,callmonster('@mdmap$,157,231,"フェイヨン警備兵#10sr1",2543,'@event$);
	set '@mob5,callmonster('@mdmap$,159,231,"フェイヨン警備兵#11sr1",2543,'@event$);
	set '@mob6,callmonster('@mdmap$,161,231,"フェイヨン警備兵#12sr1",2543,'@event$);
	unittalk '@mob2,"フェイヨン警備兵 : 怪しいヤツ！！";
	unittalk '@mob5,"フェイヨン警備兵 : 止まれ！";
	end;
OnKilled:
	end;
}

1@sara.gat,177,221,0	script	callmon_d#sara1	139,2,6,{
	hideonnpc getmdnpcname("callmon_d#sara1");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_d#sara1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,185,214,"フェイヨン警備兵#13sr1",2543,'@event$);
	set '@mob2,callmonster('@mdmap$,185,216,"フェイヨン警備兵#14sr1",2543,'@event$);
	set '@mob3,callmonster('@mdmap$,185,218,"フェイヨン警備兵#15sr1",2543,'@event$);
	set '@mob4,callmonster('@mdmap$,185,220,"フェイヨン警備兵#16sr1",2543,'@event$);
	set '@mob5,callmonster('@mdmap$,185,222,"フェイヨン警備兵#17sr1",2543,'@event$);
	set '@mob6,callmonster('@mdmap$,185,224,"フェイヨン警備兵#18sr1",2543,'@event$);
	set '@mob7,callmonster('@mdmap$,182,214,"大人しい警備犬#7sara1",2545,'@event$);
	set '@mob8,callmonster('@mdmap$,182,216,"大人しい警備犬#8sara1",2545,'@event$);
	set '@mob9,callmonster('@mdmap$,182,218,"大人しい警備犬#9sara1",2545,'@event$);
	set '@mob10,callmonster('@mdmap$,182,220,"大人しい警備犬#10sara1",2545,'@event$);
	set '@mob11,callmonster('@mdmap$,182,222,"大人しい警備犬#11sara1",2545,'@event$);
	set '@mob12,callmonster('@mdmap$,182,224,"大人しい警備犬#12sara1",2545,'@event$);
	unittalk '@mob2,"フェイヨン警備兵 : 来たぞ！";
	unittalk '@mob4,"フェイヨン警備兵 : 取り囲め！！";
	end;
OnKilled:
	end;
}

1@sara.gat,199,250,0	script	callmon_e#sara1	139,5,5,{
	hideonnpc getmdnpcname("callmon_e#sara1");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_e#sara1")+"::OnKilled";
	set '@mob1,callmonster('@mdmap$,190,258,"フェイヨン警備兵#19sr1",2543,'@event$);
	set '@mob2,callmonster('@mdmap$,192,258,"フェイヨン警備兵#20sr1",2543,'@event$);
	set '@mob3,callmonster('@mdmap$,194,258,"フェイヨン警備兵#21sr1",2543,'@event$);
	set '@mob4,callmonster('@mdmap$,196,258,"フェイヨン警備兵#22sr1",2543,'@event$);
	set '@mob5,callmonster('@mdmap$,198,258,"フェイヨン警備兵#33sr1",2543,'@event$);
	set '@mob6,callmonster('@mdmap$,200,258,"フェイヨン警備兵#34sr1",2543,'@event$);
	set '@mob7,callmonster('@mdmap$,205,246,"フェイヨン警備兵#35sr1",2543,'@event$);
	set '@mob8,callmonster('@mdmap$,205,256,"フェイヨン警備兵#36sr1",2543,'@event$);
	set '@mob9,callmonster('@mdmap$,205,254,"フェイヨン警備兵#37sr1",2543,'@event$);
	set '@mob10,callmonster('@mdmap$,205,252,"フェイヨン警備兵#38sr1",2543,'@event$);
	set '@mob11,callmonster('@mdmap$,205,250,"フェイヨン警備兵#39sr1",2543,'@event$);
	set '@mob12,callmonster('@mdmap$,205,248,"フェイヨン警備兵#40sr1",2543,'@event$);
	set '@mob13,callmonster('@mdmap$,205,246,"フェイヨン警備兵#41sr1",2543,'@event$);
	set '@mob14,callmonster('@mdmap$,196,256,"大人しい警備犬#13sara1",2545,'@event$);
	set '@mob15,callmonster('@mdmap$,196,254,"大人しい警備犬#14sara1",2545,'@event$);
	set '@mob16,callmonster('@mdmap$,196,252,"大人しい警備犬#15sara1",2545,'@event$);
	set '@mob17,callmonster('@mdmap$,196,250,"大人しい警備犬#16sara1",2545,'@event$);
	set '@mob18,callmonster('@mdmap$,196,248,"大人しい警備犬#17sara1",2545,'@event$);
	set '@mob19,callmonster('@mdmap$,196,246,"大人しい警備犬#18sara1",2545,'@event$);
	unittalk '@mob3,"フェイヨン警備兵 : 一斉にかかれ！";
	unittalk '@mob8,"フェイヨン警備兵 : 取り囲め！！";
	end;
OnKilled:
	end;
}

1@sara.gat,225,301,5	script	サラ・アイリン#sa2a	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ……はあ……はあ……。……えっう……ぐすっ……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa2a");
	hideoffnpc getmdnpcname("サラ・アイリン#sa2b");
	announce "サラは南の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,236,274,5	script	サラ・アイリン#sa2b	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : サラ、いい子にしてたのに……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa2b");
	hideoffnpc getmdnpcname("サラ・アイリン#sa2c");
	announce "サラは南の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,231,234,5	script	サラ・アイリン#sa2c	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ……どうして？　ママ、どうして痛そうな顔してたの？";
	hideonnpc getmdnpcname("サラ・アイリン#sa2c");
	hideoffnpc getmdnpcname("サラ・アイリン#sa2d");
	announce "サラは南の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,217,200,5	script	サラ・アイリン#sa2d	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : パパがママに悪いことしたの？　痛いことしたの？　……ひぐっ。";
	hideonnpc getmdnpcname("サラ・アイリン#sa2d");
	announce "サラはこの先に逃げていってしまった。",0x9,0xffff00;
	viewpoint 1,226,190,1,0x00FF00;
	end;
}

1@sara.gat,230,316,0	script	callmon_a#sara2	139,1,1,{
	set '@mdmap$,getmdmapname("1@sara.gat");
	monster '@mdmap$,228,312,"大人しい警備犬#1sara2",2545,1;
	monster '@mdmap$,227,312,"大人しい警備犬#2sara2",2545,1;
	monster '@mdmap$,229,319,"大人しい警備犬#3sara2",2545,1;
	monster '@mdmap$,221,197,"凶暴な警備犬#4sara2",2546,1;
	monster '@mdmap$,223,197,"凶暴な警備犬#5sara2",2546,1;
	monster '@mdmap$,248,290,"フェイヨン守護兵#1sara2",2544,1;
	monster '@mdmap$,247,290,"フェイヨン守護兵#2sara2",2544,1;
	monster '@mdmap$,249,290,"フェイヨン守護兵#3sara2",2544,1;
	monster '@mdmap$,221,248,"フェイヨン守護兵#4sara2",2544,1;
	monster '@mdmap$,224,248,"フェイヨン守護兵#5sara2",2544,1;
	monster '@mdmap$,227,248,"フェイヨン守護兵#6sara2",2544,1;
	monster '@mdmap$,230,248,"フェイヨン守護兵#7sara2",2544,1;
	monster '@mdmap$,218,223,"フェイヨン守護兵#8sara2",2544,1;
	monster '@mdmap$,222,223,"フェイヨン守護兵#9sara2",2544,1;
	monster '@mdmap$,226,223,"フェイヨン守護兵#10sara",2544,1;
	monster '@mdmap$,230,223,"フェイヨン守護兵#11sara",2544,1;
	hideonnpc getmdnpcname("callmon_a#sara2");
	end;
}

1@sara.gat,232,90,5	script	サラ・アイリン#sa3a	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : サラがあのお爺さんたちの悪口いった悪い子だから……？";
	hideonnpc getmdnpcname("サラ・アイリン#sa3a");
	hideoffnpc getmdnpcname("サラ・アイリン#sa3b");
	announce "サラは南西の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,211,76,5	script	サラ・アイリン#sa3b	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : パパはいい子じゃないサラ、いらないんだね……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa3b");
	hideoffnpc getmdnpcname("サラ・アイリン#sa3c");
	announce "サラは西の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,175,64,5	script	サラ・アイリン#sa3c	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : でも、ママを傷つけたパパは……？　あのパパは、悪いパパなの？";
	hideonnpc getmdnpcname("サラ・アイリン#sa3c");
	announce "サラはこの先に逃げていってしまった。",0x9,0xffff00;
	viewpoint 1,166,67,1,0x00FF00;
	end;
}

1@sara.gat,263,94,0	script	callmon_a#sara3	139,1,1,{
	set '@mdmap$,getmdmapname("1@sara.gat");
	monster '@mdmap$,90,67,"大人しい警備犬#1sara3",2545,1;
	monster '@mdmap$,93,67,"大人しい警備犬#2sara3",2545,1;
	monster '@mdmap$,90,63,"大人しい警備犬#3sara3",2545,1;
	monster '@mdmap$,93,63,"大人しい警備犬#4sara3",2545,1;
	monster '@mdmap$,90,59,"大人しい警備犬#5sara3",2545,1;
	monster '@mdmap$,93,59,"大人しい警備犬#6sara3",2545,1;
	monster '@mdmap$,90,55,"大人しい警備犬#7sara3",2545,1;
	monster '@mdmap$,93,55,"大人しい警備犬#8sara3",2545,1;
	monster '@mdmap$,255,91,"大人しい警備犬#9sara3",2545,1;
	monster '@mdmap$,253,91,"大人しい警備犬#10sara3",2545,1;
	monster '@mdmap$,255,93,"大人しい警備犬#11sara3",2545,1;
	monster '@mdmap$,253,93,"大人しい警備犬#12sara3",2545,1;
	monster '@mdmap$,255,95,"大人しい警備犬#13sara3",2545,1;
	monster '@mdmap$,253,95,"大人しい警備犬#14sara3",2545,1;
	monster '@mdmap$,255,97,"大人しい警備犬#15sara3",2545,1;
	monster '@mdmap$,253,97,"大人しい警備犬#16sara3",2545,1;
	monster '@mdmap$,193,56,"大人しい警備犬#17sara3",2545,1;
	monster '@mdmap$,195,56,"大人しい警備犬#18sara3",2545,1;
	monster '@mdmap$,197,56,"大人しい警備犬#19sara3",2545,1;
	monster '@mdmap$,193,60,"大人しい警備犬#20sara3",2545,1;
	monster '@mdmap$,195,60,"大人しい警備犬#21sara3",2545,1;
	monster '@mdmap$,197,60,"大人しい警備犬#22sara3",2545,1;
	monster '@mdmap$,193,63,"大人しい警備犬#23sara3",2545,1;
	monster '@mdmap$,195,63,"大人しい警備犬#24sara3",2545,1;
	monster '@mdmap$,197,63,"大人しい警備犬#25sara3",2545,1;
	monster '@mdmap$,87,67,"フェイヨン警備兵#1sara3",2543,1;
	monster '@mdmap$,87,63,"フェイヨン警備兵#2sara3",2543,1;
	monster '@mdmap$,87,59,"フェイヨン警備兵#3sara3",2543,1;
	monster '@mdmap$,87,55,"フェイヨン警備兵#4sara3",2543,1;
	monster '@mdmap$,121,39,"フェイヨン警備兵#5sara3",2543,1;
	monster '@mdmap$,120,39,"フェイヨン警備兵#6sara3",2543,1;
	monster '@mdmap$,122,39,"フェイヨン警備兵#7sara3",2543,1;
	monster '@mdmap$,228,59,"フェイヨン警備兵#8sara3",2543,1;
	monster '@mdmap$,228,61,"フェイヨン警備兵#9sara3",2543,1;
	monster '@mdmap$,228,63,"フェイヨン警備兵#10sara",2543,1;
	monster '@mdmap$,228,65,"フェイヨン警備兵#11sara",2543,1;
	monster '@mdmap$,81,67,"凶暴な警備犬#1sara3",2546,1;
	monster '@mdmap$,84,67,"凶暴な警備犬#2sara3",2546,1;
	monster '@mdmap$,81,63,"凶暴な警備犬#3sara3",2546,1;
	monster '@mdmap$,84,63,"凶暴な警備犬#4sara3",2546,1;
	monster '@mdmap$,81,59,"凶暴な警備犬#5sara3",2546,1;
	monster '@mdmap$,84,59,"凶暴な警備犬#6sara3",2546,1;
	monster '@mdmap$,81,55,"凶暴な警備犬#7sara3",2546,1;
	monster '@mdmap$,84,55,"凶暴な警備犬#8sara3",2546,1;
	hideonnpc getmdnpcname("callmon_a#sara3");
	end;
}

1@sara.gat,194,63,0	script	callmon_b#sara3	139,2,5,{
	hideonnpc getmdnpcname("callmon_b#sara3");
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@mob1,callmonster('@mdmap$,204,63,"凶暴な警備犬#ex1sara3",2546);
	set '@mob2,callmonster('@mdmap$,204,53,"凶暴な警備犬#ex2sara3",2546);
	unittalk '@mob1,"凶暴な警備犬 : ガルル……";
	end;
}

1@sara.gat,165,97,5	script	サラ・アイリン#sa4a	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : パパの顔、怖かった……ぐす……っ。あれはきっと悪いパパなんだ……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa4a");
	hideoffnpc getmdnpcname("サラ・アイリン#sa4b");
	announce "サラは北の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,172,126,5	script	サラ・アイリン#sa4b	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : 悪いパパ、きらい……悪いパパ、いらない……でも……サラは……サラは……うぅ……。";
	hideonnpc getmdnpcname("サラ・アイリン#sa4b");
	hideoffnpc getmdnpcname("サラ・アイリン#sa4c");
	announce "サラは北の方角に逃げていった。",0x9,0xffff00;
	end;
}

1@sara.gat,162,166,5	script	サラ・アイリン#sa4c	668,7,7,{
	end;
OnTouch:
	unittalk "サラ : ……ひっく。わかんないよぉ……。サラ、どうしたらいいの、ママ……ママ！";
	hideonnpc getmdnpcname("サラ・アイリン#sa4c");
	announce "サラはこの先に逃げていってしまった。",0x9,0xffff00;
	viewpoint 1,155,180,1,0x00FF00;
	end;
}

1@sara.gat,164,81,0	script	callmon_a#sara4	139,1,1,{
	hideonnpc getmdnpcname("callmon_a#sara4");
	set '@mdmap$,getmdmapname("1@sara.gat");
	killmonster '@mdmap$,getmdnpcname("callmon_a#sara1")+"::OnKilled";
	killmonster '@mdmap$,getmdnpcname("callmon_b#sara1")+"::OnKilled";
	killmonster '@mdmap$,getmdnpcname("callmon_c#sara1")+"::OnKilled";
	killmonster '@mdmap$,getmdnpcname("callmon_d#sara1")+"::OnKilled";
	killmonster '@mdmap$,getmdnpcname("callmon_e#sara1")+"::OnKilled";
	hideonnpc getmdnpcname("callmon_a#sara1");
	hideonnpc getmdnpcname("callmon_b#sara1");
	hideonnpc getmdnpcname("callmon_c#sara1");
	hideonnpc getmdnpcname("callmon_d#sara1");
	hideonnpc getmdnpcname("callmon_e#sara1");
	hideonnpc getmdnpcname("サラ・アイリン#sa1a");
	hideonnpc getmdnpcname("サラ・アイリン#sa1b");
	hideonnpc getmdnpcname("サラ・アイリン#sa1c");
	hideonnpc getmdnpcname("サラ・アイリン#sa1d");
	hideonnpc getmdnpcname("サラ・アイリン#sa1e");
	hideoffnpc getmdnpcname("サラ・アイリン#sa5");

	monster '@mdmap$,151,174,"フェイヨン警備兵#1sara4",2543,1;
	monster '@mdmap$,153,174,"フェイヨン警備兵#2sara4",2543,1;
	monster '@mdmap$,155,174,"フェイヨン警備兵#3sara4",2543,1;
	monster '@mdmap$,157,174,"フェイヨン警備兵#4sara4",2543,1;
	monster '@mdmap$,159,174,"フェイヨン警備兵#5sara4",2543,1;
	monster '@mdmap$,151,177,"フェイヨン警備兵#6sara4",2543,1;
	monster '@mdmap$,153,177,"フェイヨン警備兵#7sara4",2543,1;
	monster '@mdmap$,155,177,"フェイヨン警備兵#8sara4",2543,1;
	monster '@mdmap$,157,177,"フェイヨン警備兵#9sara4",2543,1;
	monster '@mdmap$,159,177,"フェイヨン警備兵#10sara",2543,1;
	monster '@mdmap$,173,137,"フェイヨン警備兵#11sara",2543,1;
	monster '@mdmap$,170,137,"フェイヨン警備兵#12sara",2543,1;
	monster '@mdmap$,167,137,"フェイヨン警備兵#13sara",2543,1;
	monster '@mdmap$,164,137,"フェイヨン警備兵#14sara",2543,1;
	monster '@mdmap$,173,139,"フェイヨン警備兵#16sara",2543,1;
	monster '@mdmap$,170,139,"フェイヨン警備兵#17sara",2543,1;
	monster '@mdmap$,167,139,"フェイヨン警備兵#18sara",2543,1;
	monster '@mdmap$,164,139,"フェイヨン警備兵#19sara",2543,1;
	monster '@mdmap$,153,96,"フェイヨン警備兵#20sara",2543,1;
	monster '@mdmap$,155,96,"フェイヨン警備兵#21sara",2543,1;
	monster '@mdmap$,157,96,"フェイヨン警備兵#22sara",2543,1;
	monster '@mdmap$,159,96,"フェイヨン警備兵#23sara",2543,1;
	monster '@mdmap$,151,180,"フェイヨン守護兵#1sara4",2544,1;
	monster '@mdmap$,153,180,"フェイヨン守護兵#2sara4",2544,1;
	monster '@mdmap$,155,180,"フェイヨン守護兵#3sara4",2544,1;
	monster '@mdmap$,157,180,"フェイヨン守護兵#4sara4",2544,1;
	monster '@mdmap$,159,180,"フェイヨン守護兵#5sara4",2544,1;
	monster '@mdmap$,223,144,"フェイヨン守護兵#6sara4",2544,1;
	monster '@mdmap$,221,144,"フェイヨン守護兵#7sara4",2544,1;
	monster '@mdmap$,223,148,"フェイヨン守護兵#8sara4",2544,1;
	monster '@mdmap$,221,148,"フェイヨン守護兵#9sara4",2544,1;
	monster '@mdmap$,223,152,"フェイヨン守護兵#10sara",2544,1;
	monster '@mdmap$,221,152,"フェイヨン守護兵#11sara",2544,1;
	monster '@mdmap$,213,113,"フェイヨン守護兵#12sara",2544,1;
	monster '@mdmap$,210,113,"フェイヨン守護兵#13sara",2544,1;
	monster '@mdmap$,207,113,"フェイヨン守護兵#14sara",2544,1;
	monster '@mdmap$,204,113,"フェイヨン守護兵#15sara",2544,1;
	monster '@mdmap$,201,113,"フェイヨン守護兵#16sara",2544,1;
	monster '@mdmap$,213,117,"フェイヨン守護兵#17sara",2544,1;
	monster '@mdmap$,210,117,"フェイヨン守護兵#18sara",2544,1;
	monster '@mdmap$,207,117,"フェイヨン守護兵#19sara",2544,1;
	monster '@mdmap$,204,117,"フェイヨン守護兵#20sara",2544,1;
	monster '@mdmap$,201,117,"フェイヨン守護兵#21sara",2544,1;
	end;
}

1@sara.gat,155,196,0	script	callmon_a#sara300	139,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	switch('flag) {
	case 0:
		donpcevent getmdnpcname("callmon_a#sara300")+"::OnSpawn1";
		set 'flag,1;
		break;
	case 1:
		announce "大長老アイリン : 私が直々に終わらせてやる！",0x9,0xffff00;
		sleep 2000;
		donpcevent getmdnpcname("callmon_a#sara300")+"::OnSpawn2";
		set 'flag,2;
		break;
	case 2:
		sleep 1000;
		hideoffnpc getmdnpcname("大長老アイリン#sa5b");
		break;
	}
	end;
OnSpawn1:
	set '@mdmap$,getmdmapname("1@sara.gat");
	set '@event$,getmdnpcname("callmon_a#sara300")+"::OnKilled";
	set '@mob[1],callmonster('@mdmap$,150,232,"フェイヨン守護兵#1sara5",2544,'@event$);
	set '@mob[2],callmonster('@mdmap$,150,227,"フェイヨン守護兵#2sara5",2544,'@event$);
	set '@mob[3],callmonster('@mdmap$,150,222,"フェイヨン守護兵#3sara5",2544,'@event$);
	set '@mob[4],callmonster('@mdmap$,150,217,"フェイヨン守護兵#4sara5",2544,'@event$);
	set '@mob[5],callmonster('@mdmap$,161,232,"フェイヨン守護兵#5sara5",2544,'@event$);
	set '@mob[6],callmonster('@mdmap$,161,227,"フェイヨン守護兵#6sara5",2544,'@event$);
	set '@mob[7],callmonster('@mdmap$,161,222,"フェイヨン守護兵#7sara5",2544,'@event$);
	set '@mob[8],callmonster('@mdmap$,161,217,"フェイヨン守護兵#8sara5",2544,'@event$);
	for(set '@i,1; '@i<=8; set '@i,'@i+1)
		unittalk '@mob['@i],"フェイヨン守護兵 : フェイヨンの為に!!";
	end;
OnSpawn2:
	set '@boss,callmonster(getmdmapname("1@sara.gat"),156,228,"大長老アイリン",2542,getmdnpcname("callmon_a#sara300")+"::OnKilled");
	unittalk '@boss,"大長老アイリン : 妻の仇をとってやる！";
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@sara.gat"),getmdnpcname("callmon_a#sara300")+ "::OnKilled");
	if('count <= 0) {
		initnpctimer;
	}
	end;
}

1@sara.gat,152,233,5	script	サラ・アイリン#sa5	668,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "……わからない……サラは……";
		mes "サラは……ひぐっ。";
		unittalk "サラ : ……わからない……サラは……サラは……ひぐっ。";
		next;
		if(SARA_1QUE > 0) {
			if(select("急ぐ","会話をする") == 1) {
				cutin "sara_9sara2",255;
				mes "‐サラは再び叫びながら、";
				mes "　南西の方角へ逃げていった。";
				mes "　大長老アイリンに話しかけよう‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐サラは再び叫びながら、南西の方角へ逃げていった‐";
				hideoffnpc getmdnpcname("大長老アイリン#sa5a");
				hideonnpc getmdnpcname("サラ・アイリン#sa5");
				close;
			}
		}
		hideoffnpc getmdnpcname("大長老アイリン#sa5a");
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "……サラ……";
		donpcevent getmdnpcname("大長老アイリン#sa5a")+"::OnTalk1";
		next;
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "……パパ。";
		unittalk "サラ : ……パパ。";
		next;
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "おまえを……探していたよ、サラ……";
		mes "ここはとても危険なんだ。";
		mes "早く……こっちにいらっしゃい……。";
		donpcevent getmdnpcname("大長老アイリン#sa5a")+"::OnTalk2";
		next;
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "血……ママの血……。";
		mes "悪いパパ、サラ……嫌い……。";
		mes "でもサラ……パパ……好き……。";
		mes "ママ……パパ……好き……。";
		mes "どうしたら……いい……の……。";
		mes "もう……もう、いやぁぁぁっ!!";
		unittalk "サラ : 血……ママの血……。悪いパパ、サラ……嫌い……。でもサラ……パパ……好き……。ママ……パパ……好き……。どうしたら……いい……の……。もう……もう、いやぁぁぁっ!!";
		next;
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "サラ!!";
		donpcevent getmdnpcname("大長老アイリン#sa5a")+"::OnTalk3";
		next;
		cutin "sara_9sara2",255;
		hideonnpc getmdnpcname("サラ・アイリン#sa5");
		mes "‐サラは再び叫びながら、";
		mes "　南西の方角へ逃げていった。";
		mes "　大長老アイリンに話しかけよう‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラは再び叫びながら、南西の方角へ逃げていった‐";
		close2;
		cutin "sara_elder_irine4",255;
		end;
	}
	else {
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "…………。";
		next;
		cutin "sara_9sara2",255;
		mes "^ff0000‐パーティーリーダーが";
		mes "　話しかけてみよう‐^000000";
		close;
	}
}

1@sara.gat,156,236,3	script	大長老アイリン#sa5a	684,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "sara_elder_irine3",2;
		mes "[大長老アイリン]";
		mes "貴様は……";
		mes "この殺人犯め！　まだ生きていたのか！";
		unittalk "大長老アイリン : 貴様は……この殺人犯め！　まだ生きていたのか！";
		while(1) {
			next;
			switch(select("どうするか考える","^0000ff自分は殺人犯ではないと説明する（戦闘なし）^000000","^ff0000大長老を力でねじ伏せる（戦闘あり）^000000")) {
			case 1:
				mes "[大長老アイリン]";
				mes "どうした！";
				mes "何か言ったらどうだ！";
				unittalk "大長老アイリン : どうした！　何か言ったらどうだ！";
				continue;
			case 2:
				cutin "sara_elder_irine3",255;
				mes "‐自分は殺人犯ではないことを";
				mes "　大長老アイリンに説明した‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐自分は殺人犯ではないことを大長老アイリンに説明した‐";
				next;
				cutin "sara_elder_irine3",2;
				mes "[大長老アイリン]";
				mes "……とぼけるつもりか？";
				unittalk "大長老アイリン : ……とぼけるつもりか？";
				next;
				cutin "sara_elder_irine3",255;
				hideoffnpc getmdnpcname("#paydef_sara1");
				mes "[フェイヨン守護兵]";
				mes "大長老様！";
				donpcevent getmdnpcname("#paydef_sara1")+"::OnTalk1";
				next;
				cutin "sara_elder_irine3",2;
				mes "[大長老アイリン]";
				mes "守護兵！";
				mes "殺人犯はここだ！";
				mes "あいつを包囲しろ!!";
				unittalk "大長老アイリン : 守護兵！　殺人犯はここだ！　あいつを包囲しろ!!";
				next;
				cutin "sara_elder_irine3",255;
				mes "[フェイヨン守護兵]";
				mes "大長老様、それが……";
				donpcevent getmdnpcname("#paydef_sara1")+"::OnTalk2";
				next;
				cutin "sara_elder_irine3",2;
				mes "[大長老アイリン]";
				mes "どうした？";
				mes "この緊急事態に！";
				unittalk "大長老アイリン : どうした？　この緊急事態に！";
				next;
				cutin "sara_elder_irine3",255;
				mes "‐大長老アイリンは、駆け付けた";
				mes "　フェイヨン守護兵と何やら";
				mes "　話し始めた。";
				mes "　もう一度、大長老アイリンに";
				mes "　話しかけてみよう‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐大長老アイリンは、駆け付けたフェイヨン守護兵と何やら話し始めた‐";
				close2;
				hideonnpc getmdnpcname("大長老アイリン#sa5a");
				hideonnpc getmdnpcname("#paydef_sara1");
				hideoffnpc getmdnpcname("大長老アイリン#sa5b");
				set getvariableofnpc('flag,getmdnpcname("大長老アイリン#sa5b")),1;
				end;
			case 3:
				cutin "sara_elder_irine3",255;
				mes "‐サラを追うのをはばむため、";
				mes "　大長老アイリンの前に";
				mes "　立ちはだかった‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐サラを追うのをはばむため、大長老アイリンの前に立ちはだかった‐";
				next;
				cutin "sara_elder_irine3",2;
				mes "[大長老アイリン]";
				mes "おい！";
				mes "あいつを包囲しろ!!";
				unittalk "大長老アイリン : おい！　あいつを包囲しろ!!";
				close2;
				cutin "sara_9sara2",255;
				hideonnpc getmdnpcname("大長老アイリン#sa5a");
				hideonnpc getmdnpcname("#paydef_sara1");
				set getvariableofnpc('flag,getmdnpcname("大長老アイリン#sa5b")),2;
				donpcevent getmdnpcname("callmon_a#sara300")+"::OnStart";
				end;
			}
		}
	}
	else {
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "…………。";
		next;
		cutin "sara_elder_irine4",255;
		mes "^ff0000‐パーティーリーダーが";
		mes "　話しかけてみよう‐^000000";
		close;
	}
OnTalk1:
	unittalk "大長老アイリン : ……サラ……";
	end;
OnTalk2:
	unittalk "大長老アイリン : おまえを……探していたよ、サラ……ここはとても危険なんだ。 早く……こっちにいらっしゃい……。";
	end;
OnTalk3:
	unittalk "大長老アイリン : サラ!!";
	end;
}

1@sara.gat,156,236,3	script	大長老アイリン#sa5b	684,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		if('flag == 1) {
			cutin "sara_elder_irine4",2;
			mes "[大長老アイリン]";
			mes "事件があった時、";
			mes "君を事件の現場とは離れた場所で";
			mes "見た兵がいるらしい……。";
			unittalk "大長老アイリン : 事件があった時、君を事件の現場とは離れた場所で見た兵がいるらしい……。";
		}
		else if('flag == 2) {
			cutin "sara_elder_irine4",2;
			mes "[大長老アイリン]";
			mes "くうう……";
			mes "これほど強いやつだったとは。";
			unittalk "大長老アイリン : くうう……これほど強いやつだったとは。";
			next;
			mes "[大長老アイリン]";
			mes "誰の指示を受けてこんな事を！";
			mes "妻だけでなく、サラまで狙うとは!!";
			unittalk "大長老アイリン : 誰の指示を受けてこんな事を！　妻だけでなく、サラまで狙うとは!!";
		}
		next;
		if(SARA_1QUE > 0) {
			if(select("急ぐ","会話をする") == 1) {
				mes "[大長老アイリン]";
				mes "総力を出してサラを探し出そう。";
				mes "君もサラを見つけたら私の所に";
				mes "連れて来てくれ。";
				mes "私からサラにすべてを説明する……。";
				unittalk "大長老アイリン : 総力を出してサラを探し出そう。君もサラを見つけたら私の所に連れて来てくれ。私からサラにすべてを説明する……。";
				announce strcharinfo(0) + " : サラが逃げて行った南西の方向に行ってみよう。",0x9,0xffff00;
				cutin "sara_elder_irine4",255;
				hideonnpc getmdnpcname("大長老アイリン#sa5b");
				hideoffnpc getmdnpcname("warp56#sara5");
				close;
			}
		}
		menu "殺人犯はあなたではないのか？",-;
		cutin "sara_elder_irine4",255;
		mes "[" + strcharinfo(0) + "]";
		mes "こちらからはあなたがサラの母親を";
		mes "殺したように見えました。";
		unittalk getcharid(3),strcharinfo(0)+" : こちらからはあなたがサラの母親を殺したように見えました。";
		next;
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "私が妻を殺しただと!?";
		unittalk "大長老アイリン : 私が妻を殺しただと!?";
		next;
		mes "[大長老アイリン]";
		mes "私が妻の部屋に入った時には、";
		mes "妻はすでに刺客たちによって……。";
		mes "サラが入ってきたのは、";
		mes "私がその刺客たちを倒した直後だ！";
		unittalk "大長老アイリン : 私が妻の部屋に入った時には、妻はすでに刺客たちによって……。サラが入ってきたのは、私がその刺客たちを倒した直後だ！";
		next;
		cutin "sara_momdie",4;
		mes "‐大長老アイリンの話を聞き、当時の";
		mes "　状況をもう一度思い出してみた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐大長老アイリンの話を聞き、当時の状況をもう一度思い出してみた‐";
		next;
		mes "‐確かに、大長老アイリンの周辺には";
		mes "　サラの母親のほかに、黒い服を着た";
		mes "　誰かが倒れていたような……‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐確かに、大長老アイリンの周辺にはサラの母親のほかに、黒い服を着た誰かが倒れていたような……‐";
		next;
		cutin "sara_elder_irine4",2;
		mes "[大長老アイリン]";
		mes "刺客ではないなら、君はいったい誰だ？";
		mes "どうしてサラと一緒にここまで来た？";
		unittalk "大長老アイリン : 刺客ではないなら、君はいったい誰だ？　どうしてサラと一緒にここまで来た？";
		next;
		mes "‐偶然怪しい老人の会話を聞き、";
		mes "　サラの身が心配になったため、";
		mes "　追いかけてきたことを伝えた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐偶然怪しい老人の会話を聞き、サラの身が心配になったため、追いかけてきたことを伝えた‐";
		next;
		mes "[大長老アイリン]";
		mes "怪しい老人……？";
		mes "君の話が本当なら、";
		mes "大きな間違いを犯してしまったようだ。";
		mes "私も、そして君も……";
		unittalk "大長老アイリン : 怪しい老人……？　君の話が本当なら、大きな間違いを犯してしまったようだ。私も、そして君も……";
		next;
		mes "[大長老アイリン]";
		mes "私は君が妻を殺した刺客の仲間だと";
		mes "誤解をし、君は私が妻を殺したと";
		mes "誤解をしていたのか。";
		unittalk "大長老アイリン : 私は君が妻を殺した刺客の仲間だと誤解をし、君は私が妻を殺したと誤解をしていたのか。";
		next;
		mes "[大長老アイリン]";
		mes "正体不明の老人たち……";
		mes "やはり長老たちの仕業なのか……。";
		unittalk "大長老アイリン : 正体不明の老人たち……やはり長老たちの仕業なのか……。";
		next;
		mes "[大長老アイリン]";
		mes "！";
		mes "まさかサラも、私が妻を";
		mes "殺したと考えているのか?!";
		unittalk "大長老アイリン : ！　まさかサラも、私が妻を殺したと考えているのか?!";
		next;
		mes "[大長老アイリン]";
		mes "それでサラは私を見て";
		mes "泣いていたのか？";
		mes "父が母を殺したと思って……";
		unittalk "大長老アイリン : それでサラは私を見て泣いていたのか？　父が母を殺したと思って……";
		next;
		mes "[大長老アイリン]";
		mes "おお、サラ！";
		mes "お前の絶望はどれほどだろう……。";
		unittalk "大長老アイリン : おお、サラ！　お前の絶望はどれほどだろう……。";
		next;
		mes "[大長老アイリン]";
		mes "総力を出してサラを探し出そう。";
		mes "君もサラを見つけたら私の所に";
		mes "連れて来てくれ。";
		mes "私からサラにすべてを説明する……。";
		unittalk "大長老アイリン : 総力を出してサラを探し出そう。君もサラを見つけたら私の所に連れて来てくれ。私からサラにすべてを説明する……。";
		close2;
		announce strcharinfo(0) + " : サラが逃げて行った南西の方向に行ってみよう。",0x9,0xffff00;
		cutin "sara_elder_irine4",255;
		hideonnpc getmdnpcname("大長老アイリン#sa5b");
		hideoffnpc getmdnpcname("warp56#sara5");
		end;
	}
	else {
		mes "^ff0000‐イベントの進行は";
		mes "　パーティーリーダーのみ可能です‐^000000";
		close;
	}
}

1@sara.gat,162,233,1	script	#paydef_sara1	2544,{
	end;
OnTalk1:
	unittalk "フェイヨン守護兵 : 大長老様！";
	end;
OnTalk2:
	unittalk "フェイヨン守護兵 : 大長老様、それが……";
	end;
}

1@sara.gat,88,188,0	warp	warp56#sara5	2,2,1@sara.gat,89,175

1@sara.gat,39,142,3	script	サラ・アイリン#sa6	668,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		hideoffnpc getmdnpcname("#hugin_sara2");
		if(SARA_1QUE > 0) {
			mes "‐サラを見つけた‐";
			next;
			if(select("急ぐ","会話をする") == 1) {
				mes "‐サラが消えたのと同時に周辺の";
				mes "　風景が歪み始めた。";
				mes "　探検家のレーンが話していたように、";
				mes "　狭間から出なければならないようだ‐";
				unittalk getcharid(3),strcharinfo(0)+" : ‐サラが消えたのと同時に周辺の風景が歪み始めた。探検家のレーンが話していたように、狭間から出なければならないようだ‐";
				close2;
				hideonnpc getmdnpcname("サラ・アイリン#sa6");
				hideoffnpc getmdnpcname("#warp_end_sara6");
				hideoffnpc getmdnpcname("warp67#sara6");
				end;
			}
		}
		mes "‐サラに声をかけようとした";
		mes "　瞬間、背後から強い襲撃を受け";
		mes "　崩れ落ちた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラに声をかけようとした瞬間、背後から強い襲撃を受け崩れ落ちた‐";
		next;
		cutin "sara_beholder",2;
		mes "[？？？？？]";
		mes "時間の旅人の干渉はここまでです。";
		mes "あなたは私達が彼女を迎え入れるために";
		mes "準備した歯車の中のひとつでしか";
		mes "ありません。";
		donpcevent getmdnpcname("#hugin_sara2")+"::OnTalk1";
		next;
		mes "[？？？？？]";
		mes "そろそろあなたが住んでいた時間に";
		mes "戻った方がいいでしょう。";
		donpcevent getmdnpcname("#hugin_sara2")+"::OnTalk2";
		next;
		mes "[？？？？？]";
		mes "それからあなたの記憶は消させてもらいます。";
		mes "元の時間に帰る頃にはここで起こったことは何も覚えていないでしょう。";
		donpcevent getmdnpcname("#hugin_sara2")+"::OnTalk3";
		misceffect 134,"";
		next;
		mes "‐正体不明の男女が倒れた私を";
		mes "　置いたままサラに近寄った‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐正体不明の男女が倒れた私を置いたままサラに近寄った‐";
		next;
		mes "[？？？？？]";
		mes "裏切りと絶望、";
		mes "憎悪に震えている少女よ……";
		mes "君がいるべき場所に導いてやる……。";
		donpcevent getmdnpcname("#hugin_sara2")+"::OnTalk4";
		next;
		cutin "sara_9sara2",2;
		mes "[サラ]";
		mes "…………。";
		unittalk "サラ : …………。";
		next;
		cutin "sara_beholder",2;
		mes "[？？？？？]";
		mes "サラ・アイリン、私について来なさい。";
		mes "あの方がお前が望む未来を与えてくれるだろう。";
		donpcevent getmdnpcname("#hugin_sara2")+"::OnTalk5";
		next;
		cutin "sara_beholder",255;
		mes "‐正体不明の男が自身のマントで";
		mes "　サラを覆い被せた瞬間、サラを含んだ";
		mes "　三人の姿が痕跡も残さずに";
		mes "　消えた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐正体不明の男が自身のマントでサラを覆い被せた瞬間、サラを含んだ三人の姿が痕跡も残さずに消えた‐";
		hideonnpc getmdnpcname("サラ・アイリン#sa6");
		next;
		mes "‐サラが消えたのと同時に周辺の";
		mes "　風景が歪み始めた。";
		mes "　探検家のレーンが話していたように、";
		mes "　狭間から出なければならないようだ‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐サラが消えたのと同時に周辺の風景が歪み始めた。探検家のレーンが話していたように、狭間から出なければならないようだ‐";
		close2;
		hideoffnpc getmdnpcname("#warp_end_sara6");
		hideoffnpc getmdnpcname("warp67#sara6");
		end;
	}
	else {
		mes "[サラ]";
		mes "誰……？";
		next;
		mes "^ff0000‐サラは怯えているようだ。";
		mes "　パーティーリーダーが";
		mes "　話しかけてみよう‐^000000";
		close;
	}
}

1@sara.gat,36,144,3	script	#hugin_sara2	111,{
	end;
OnTalk1:
	unittalk "？？？？？ : 時間の旅人の干渉はここまでです。あなたは私達が彼女を迎え入れるために準備した歯車の中のひとつでしかありません。";
	end;
OnTalk2:
	unittalk "？？？？？ : そろそろあなたが住んでいた時間に戻った方がいいでしょう。";
	end;
OnTalk3:
	unittalk "？？？？？ : それからあなたの記憶は消させてもらいます。元の時間に帰る頃にはここで起こったことは何も覚えていないでしょう。";
	end;
OnTalk4:
	unittalk "？？？？？ : 裏切りと絶望、憎悪に震えている少女よ……君がいるべき場所に導いてやる……。";
	end;
OnTalk5:
	unittalk "？？？？？ : サラ・アイリン、私について来なさい。あの方がお前が望む未来を与えてくれるだろう。";
	end;
}

1@sara.gat,36,144,0	script	#warp_end_sara6	139,30,5,{
OnTouch:
	compquest 15003;
	warp "dali.gat",134,111;
	end;
}

1@sara.gat,16,143,0	script	warp67#sara6	45,2,2,{
OnTouch:
	compquest 15003;
	warp "dali.gat",134,111;
	end;
}

1@sara.gat,107,252,0	script	sara_exmob1	139,3,3,{
OnTouch:
	if('flag > 0)
		end;
	set 'flag,1;
	monster getmdmapname("1@sara.gat"),106,255,"フェイヨン警備兵#ex1sar",2543,1;
	monster getmdmapname("1@sara.gat"),108,255,"フェイヨン警備兵#ex2sar",2543,1;
	monster getmdmapname("1@sara.gat"),106,246,"フェイヨン警備兵#ex3sar",2543,1;
	monster getmdmapname("1@sara.gat"),108,246,"フェイヨン警備兵#ex4sar",2543,1;
	end;
}

1@sara.gat,82,259,0	script	sara_exmob2	139,3,3,{
OnTouch:
	if('flag > 0)
		end;
	set 'flag,1;
	monster getmdmapname("1@sara.gat"),81,265,"フェイヨン警備兵#ex1sar",2543,1;
	monster getmdmapname("1@sara.gat"),82,265,"フェイヨン警備兵#ex2sar",2543,1;
	monster getmdmapname("1@sara.gat"),81,252,"フェイヨン警備兵#ex3sar",2543,1;
	monster getmdmapname("1@sara.gat"),82,252,"フェイヨン警備兵#ex4sar",2543,1;
	end;
}
