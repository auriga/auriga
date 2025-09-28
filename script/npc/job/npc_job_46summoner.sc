//====================================================================
//Ragnarok Online - Summoner Script	by refis
//====================================================================

//------------------------------------------------------------
// Monstar Spawn
//------------------------------------------------------------
// do_tu01a.gat
do_tu01a.gat,100,320,75,55	monster	エッグリン	3495,30,5000,0,0
do_tu01a.gat,100,320,75,55	monster	グラスファブル	3497,30,5000,0,0
//------------------------------------------------------------
// do_tu04a.gat
do_tu04a.gat,0,0,0,0	monster	スウィートフロッグ	3499,40,5000,0,0
do_tu04a.gat,0,0,0,0	monster	ハンターウルフ	3500,30,5000,0,0
do_tu04a.gat,0,0,0,0	monster	ワイルドホーネット	3498,30,5000,0,0
do_tu04a.gat,0,0,0,0	monster	リーフルナティック	3496,40,5000,0,0
do_tu04a.gat,0,0,0,0	monster	偵察バジルリスク	3502,10,5000,0,0
//------------------------------------------------------------
// do_tu06a.gat
do_tu06a.gat,0,0,0,0	monster	偵察バジルリスク	3502,40,5000,0,0
do_tu06a.gat,0,0,0,0	monster	トランススポア	3501,30,5000,0,0
//------------------------------------------------------------
// do_tu07a.gat
do_tu07a.gat,0,0,0,0	monster	偵察バジルリスク	3502,80,5000,0,0
//------------------------------------------------------------

//------------------------------------------------------------
// チュートリアルNPC
//------------------------------------------------------------
new_do1.gat,90,247,0	script	object01#new_do1	139,30,3,{
	mes "[シェレ]";
	mes "そっちじゃないわ。";
	mes "こっちに来てちょうだい。";
	set '@dummy,sleep2(1000);
	warp "new_do1.gat",95,260;
	end;
}

new_do1.gat,95,264,4	script	シェレ#new_do1	10165,{
	if(DORAM_1QUE == 100) {
		mes "^ff0000【インフォメーション】";
		mes "スキップ処理を実行中です。";
		mes "クライアントを終了しないでください。";
		mes "実行中に終了した場合、";
		mes "一部のアイテムや経験値を";
		mes "受け取れない場合があります。^000000";
		next;
		mes "^ff0000【インフォメーション】^000000";
		mes "^0000ff[next] をクリックしてください。^000000";
		next;
		mes "[シェレ]";
		mes "わかったわ。";
		mes "それじゃそのように";
		mes "手配しておくわ。";
		mes "あなたの活躍、期待してるわ！";
		set DORAM_1QUE,100;
		savepoint "lasagna.gat",299,239;
		warp "lasagna.gat",298,238;
		end;
	}
	//setquest 102845;
	//compquest 102845;
	mes "[シェレ]";
	mes "パースタ大陸へようこそ！";
	mes "新しい冒険者かしら？";
	next;
	mes "[シェレ]";
	mes "私はシェレ。";
	mes "外から来る冒険者に";
	mes "案内してるの。";
	next;
	mes "[シェレ]";
	mes "クンクン……";
	mes "ふむふむ……";
	mes "あなた、^ff0000サモナー^000000としての素質は";
	mes "なかなかのものを持ってるわ。";
	mes "良い冒険者になれそうよ。";
	next;
	mes "[シェレ]";
	mes "よかったらここで";
	mes "チュートリアルを受けて、";
	mes "冒険の基礎を学んでいかない？";
	mes "きっとこれからの旅の";
	mes "役に立つと思うわ。";
	next;
	mes "[シェレ]";
	mes "もし冒険に自信があるなら";
	mes "チュートリアルをスキップしても";
	mes "かまわないわ。";
	next;
	mes "[シェレ]";
	mes "でも^0000ff初めて冒険に出るような";
	mes "初心者だったら、";
	mes "チュートリアルは絶対に";
	mes "受けておいた方が良いわよ。^000000";
	while(1) {
		next;
		switch(select("ここはどこ？","^009eff冒険の基礎を学ぶ(チュートリアルを開始)^000000","^ff0000すぐに冒険を始める(チュートリアルを省略)^000000")) {
		case 1:
			mes "[シェレ]";
			mes "ここは^ff0000パースタ大陸^000000にある";
			mes "^ff0000港町ラザーニャ。^000000";
			mes "最近ではミッドガルドという";
			mes "新大陸が発見されたせいで、";
			mes "大陸の各地からたくさんのドラムが";
			mes "集まってきているわ。";
			next;
			mes "[シェレ]";
			mes "ただ……興味本位だけで";
			mes "冒険の基礎もできていない";
			mes "ドラムが多過ぎるのよ。";
			mes "だから私がここで";
			mes "外から来たドラムを案内しているの。";
			continue;
		case 2:
			mes "[シェレ]";
			mes "それじゃ、";
			mes "チュートリアル会場に送るわね。";
			mes "あなたの活躍、期待してるわよ！";
			close2;
			warp "do_tu01a.gat",29,283;
			end;
		case 3:
			mes "^ff0000【インフォメーション】";
			mes "<すべてのチュートリアルを";
			mes "スキップする>を選択すると、";
			mes "チュートリアルで獲得できる";
			mes "全ての経験値やアイテムを";
			mes "受け取った状態で、";
			mes "ラザーニャから冒険を開始できます。^000000";
			next;
			mes "^ff0000【インフォメーション】";
			mes "ただし、一度選んでしてしまうと";
			mes "チュートリアルの内容を";
			mes "再度確認することはできません。";
			mes "チュートリアルをスキップしますか？^000000";
			next;
			if(select("少し考える","^ff0000すべてのチュートリアルをスキップする^000000") == 1) {
				mes "[シェレ]";
				mes "わかったわ。";
				mes "では、どうするのかしら？";
				continue;
			}
			mes "^ff0000【インフォメーション】";
			mes "スキップ処理を実行中です。";
			mes "クライアントを終了しないでください。";
			mes "実行中に終了した場合、";
			mes "一部のアイテムや経験値を";
			mes "受け取れない場合があります。^000000";
			next;
			if(DORAM_1QUE <= 4){
				getitem 26135, 1;
			}
			if(DORAM_1QUE <= 32) {
				getitem 15273, 1;
				getitem 22183, 1;
			}
			if(DORAM_1QUE <= 37) {
				getitem 569, 50;
			}
			if(DORAM_1QUE <= 42) {
				getitem 19330, 1;
				getitem 28576, 1;
				getitem 15274, 1;
				getitem 22184, 1;
			}
			if(DORAM_1QUE <= 40) {
				getitem 12324, 1;
			}
			if(DORAM_1QUE == 0) {
				setquest 98400;
				delquest 98400;
				getexp 2,0;
				getexp 0,10;
			}
			if(DORAM_1QUE <= 1) {
				getexp 4,0;
				getexp 0,20;
			}
			if(DORAM_1QUE <= 2) {
				setquest 98402;
				delquest 98402;
				getexp 6,0;
				getexp 0,40;
			}
			if(DORAM_1QUE <= 3) {
				setquest 98403;
				delquest 98403;
				getexp 9,0;
				getexp 0,60;
			}
			if(DORAM_1QUE <= 6) {
				setquest 98404;
				delquest 98404;
				getexp 12,0;
				getexp 0,80;
			}
			if(DORAM_1QUE <= 8) {
				setquest 98405;
				delquest 98405;
				getexp 15,0;
				getexp 0,100;
			}
			if(DORAM_1QUE <= 10) {
				setquest 98406;
				delquest 98406;
				getexp 18,0;
				getexp 0,200;
			}
			if(DORAM_1QUE <= 12) {
				setquest 98407;
				delquest 98407;
				getexp 21,0;
				getexp 0,400;
			}
			if(DORAM_1QUE <= 14) {
				setquest 98408;
				delquest 98408;
				getexp 27,0;
				getexp 0,600;
				delitem 26135, 1;
				getitem2 26135, 1, 1, 4, 0, 0, 0, 0, 0;
			}
			if(DORAM_1QUE <= 16) {
				setquest 98409;
				delquest 98409;
				getexp 40,0;
				getexp 0,800;
			}
			if(DORAM_1QUE <= 18) {
				setquest 98410;
				delquest 98410;
				getexp 48,0;
				getexp 0,1000;
			}
			if(DORAM_1QUE <= 20) {
				setquest 98411;
				delquest 98411;
				getexp 61,0;
				getexp 0,1200;
			}
			if(DORAM_1QUE <= 20) {
				setquest 98412;
				delquest 98412;
				getexp 73,0;
				getexp 0,1400;
			}
			if(DORAM_1QUE <= 23) {
				setquest 98413;
				delquest 98413;
				getexp 87,0;
				getexp 0,1600;
			}
			if(DORAM_1QUE <= 24) {
				skill 142,1,0;
				getexp 103,0;
				getexp 0,1800;
			}
			if(DORAM_1QUE <= 25) {
				setquest 98415;
				delquest 98415;
				getexp 121,0;
				getexp 0,2000;
			}
			if(DORAM_1QUE <= 28) {
				setquest 98416;
				delquest 98416;
				getexp 140,0;
				getexp 0,2200;
			}
			if(DORAM_1QUE <= 29) {
				setquest 98417;
				delquest 98417;
				getexp 157,0;
				getexp 0,2400;
			}
			if(DORAM_1QUE <= 31) {
				setquest 98418;
				delquest 98418;
				getexp 177,0;
				getexp 0,2600;
			}
			if(DORAM_1QUE <= 32) {
				setquest 98419;
				delquest 98419;
				getexp 214,0;
				getexp 0,2800;
				getexp 239,0;
				getexp 0,3000;
			}
			if(DORAM_1QUE <= 33) {
				setquest 98421;
				delquest 98421;
				getexp 267,0;
				getexp 0,3200;
			}
			if(DORAM_1QUE <= 35) {
				setquest 98422;
				delquest 98422;
				getexp 298,0;
				getexp 0,3400;
				getexp 332,0;
				getexp 0,3600;
			}
			if(DORAM_1QUE <= 36) {
				setquest 98424;
				delquest 98424;
				getexp 389,0;
				getexp 0,3800;
			}
			if(DORAM_1QUE <= 38) {
				setquest 98425;
				delquest 98425;
				getexp 430,0;
				getexp 0,4000;
			}
			if(DORAM_1QUE <= 39) {
				setquest 98426;
				delquest 98426;
				getexp 475,0;
				getexp 0,6000;
				setquest 98427;
				delquest 98427;
				getexp 524,0;
				getexp 0,8000;
			}
			if(DORAM_1QUE <= 40) {
				setquest 98428;
				delquest 98428;
			}
			if(DORAM_1QUE <= 41) {
				getexp 577,0;
				getexp 0,10000;
			}
			if(DORAM_1QUE <= 42) {
				setquest 98429;
				delquest 98429;
				getexp 0,25000;
			}
			set DORAM_1QUE,100;
			mes "^ff0000【インフォメーション】^000000";
			mes "^0000ff[next] をクリックしてください。^000000";
			next;
			mes "[シェレ]";
			mes "わかったわ。";
			mes "それじゃそのように";
			mes "手配しておくわ。";
			mes "あなたの活躍、期待してるわ！";
			savepoint "lasagna.gat",299,239;
			warp "lasagna.gat",298,238;
			end;
		}
	}
}

do_tu05a.gat,137,98,4	script	シェレ#do_tu01a	10165,{
	mes "[シェレ]";
	mes "あら、チュートリアルの";
	mes "終了をご希望かしら？";
	while(1) {
		next;
		switch(select("少し考える","^009effチュートリアルに戻る^000000","^ff0000すべてのチュートリアルをスキップする^000000")) {
		case 1:
			mes "[シェレ]";
			mes "わかったわ。";
			mes "決まったらもう一度声かけてね。";
			close;
		case 2:
			mes "[シェレ]";
			mes "それじゃ、";
			mes "チュートリアル会場に送るわね。";
			mes "あなたの活躍、期待してるわよ！";
			close2;
			if(DORAM_1QUE <= 1)
				warp "do_tu01a.gat",29,281;
			else if(DORAM_1QUE <= 24)
				warp "do_tu01a.gat",60,320;
			else if(DORAM_1QUE <= 26)
				warp "do_tu02a.gat",224,124;
			else if(DORAM_1QUE <= 34)
				warp "do_tu02a.gat",235,196;
			else if(DORAM_1QUE <= 35)
				warp "do_tu02a.gat",203,322;
			else if(DORAM_1QUE <= 37)
				warp "do_tu05a.gat",186,55;
			else if(DORAM_1QUE <= 38)
				warp "do_tu05a.gat",26,62;
			end;
		case 3:
			break;
		}
		mes "^ff0000【インフォメーション】";
		mes "<すべてのチュートリアルを";
		mes "スキップする>を選択すると、";
		mes "チュートリアルで獲得できる";
		mes "全ての経験値やアイテムを";
		mes "受け取った状態で、";
		mes "ラザーニャから冒険を開始できます。^000000";
		next;
		mes "^ff0000【インフォメーション】";
		mes "ただし、一度選んでしてしまうと";
		mes "チュートリアルの内容を";
		mes "再度確認することはできません。";
		mes "チュートリアルをスキップしますか？^000000";
		next;
		if(select("少し考える","^ff0000すべてのチュートリアルをスキップする^000000") == 1) {
			mes "[シェレ]";
			mes "わかったわ。";
			mes "では、どうするのかしら？";
			continue;
		}
		mes "^ff0000【インフォメーション】";
		mes "スキップ処理を実行中です。";
		mes "クライアントを終了しないでください。";
		mes "実行中に終了した場合、";
		mes "一部のアイテムや経験値を";
		mes "受け取れない場合があります。^000000";
		next;
		if(DORAM_1QUE <= 4){
			getitem 26135, 1;
		}
		if(DORAM_1QUE <= 32) {
			getitem 15273, 1;
			getitem 22183, 1;
		}
		if(DORAM_1QUE <= 37) {
			getitem 569, 50;
		}
		if(DORAM_1QUE <= 42) {
			getitem 19330, 1;
			getitem 28576, 1;
			getitem 15274, 1;
			getitem 22184, 1;
		}
		if(DORAM_1QUE <= 40) {
			getitem 12324, 1;
		}
		if(DORAM_1QUE == 0) {
			setquest 98400;
			delquest 98400;
			getexp 2,0;
			getexp 0,10;
		}
		if(DORAM_1QUE <= 1) {
			getexp 4,0;
			getexp 0,20;
		}
		if(DORAM_1QUE <= 2) {
			setquest 98402;
			delquest 98402;
			getexp 6,0;
			getexp 0,40;
		}
		if(DORAM_1QUE <= 3) {
			setquest 98403;
			delquest 98403;
			getexp 9,0;
			getexp 0,60;
		}
		if(DORAM_1QUE <= 6) {
			setquest 98404;
			delquest 98404;
			getexp 12,0;
			getexp 0,80;
		}
		if(DORAM_1QUE <= 8) {
			setquest 98405;
			delquest 98405;
			getexp 15,0;
			getexp 0,100;
		}
		if(DORAM_1QUE <= 10) {
			setquest 98406;
			delquest 98406;
			getexp 18,0;
			getexp 0,200;
		}
		if(DORAM_1QUE <= 12) {
			setquest 98407;
			delquest 98407;
			getexp 21,0;
			getexp 0,400;
		}
		if(DORAM_1QUE <= 14) {
			setquest 98408;
			delquest 98408;
			getexp 27,0;
			getexp 0,600;
			delitem 26135, 1;
			getitem2 26135, 1, 1, 4, 0, 0, 0, 0, 0;
		}
		if(DORAM_1QUE <= 16) {
			setquest 98409;
			delquest 98409;
			getexp 40,0;
			getexp 0,800;
		}
		if(DORAM_1QUE <= 18) {
			setquest 98410;
			delquest 98410;
			getexp 48,0;
			getexp 0,1000;
		}
		if(DORAM_1QUE <= 20) {
			setquest 98411;
			delquest 98411;
			getexp 61,0;
			getexp 0,1200;
		}
		if(DORAM_1QUE <= 20) {
			setquest 98412;
			delquest 98412;
			getexp 73,0;
			getexp 0,1400;
		}
		if(DORAM_1QUE <= 23) {
			setquest 98413;
			delquest 98413;
			getexp 87,0;
			getexp 0,1600;
		}
		if(DORAM_1QUE <= 24) {
			skill 142,1,0;
			getexp 103,0;
			getexp 0,1800;
		}
		if(DORAM_1QUE <= 25) {
			setquest 98415;
			delquest 98415;
			getexp 121,0;
			getexp 0,2000;
		}
		if(DORAM_1QUE <= 28) {
			setquest 98416;
			delquest 98416;
			getexp 140,0;
			getexp 0,2200;
		}
		if(DORAM_1QUE <= 29) {
			setquest 98417;
			delquest 98417;
			getexp 157,0;
			getexp 0,2400;
		}
		if(DORAM_1QUE <= 31) {
			setquest 98418;
			delquest 98418;
			getexp 177,0;
			getexp 0,2600;
		}
		if(DORAM_1QUE <= 32) {
			setquest 98419;
			delquest 98419;
			getexp 214,0;
			getexp 0,2800;
			getexp 239,0;
			getexp 0,3000;
		}
		if(DORAM_1QUE <= 33) {
			setquest 98421;
			delquest 98421;
			getexp 267,0;
			getexp 0,3200;
		}
		if(DORAM_1QUE <= 35) {
			setquest 98422;
			delquest 98422;
			getexp 298,0;
			getexp 0,3400;
			getexp 332,0;
			getexp 0,3600;
		}
		if(DORAM_1QUE <= 36) {
			setquest 98424;
			delquest 98424;
			getexp 389,0;
			getexp 0,3800;
		}
		if(DORAM_1QUE <= 38) {
			setquest 98425;
			delquest 98425;
			getexp 430,0;
			getexp 0,4000;
		}
		if(DORAM_1QUE <= 39) {
			setquest 98426;
			delquest 98426;
			getexp 475,0;
			getexp 0,6000;
			setquest 98427;
			delquest 98427;
			getexp 524,0;
			getexp 0,8000;
		}
		if(DORAM_1QUE <= 40) {
			setquest 98428;
			delquest 98428;
		}
		if(DORAM_1QUE <= 41) {
			getexp 577,0;
			getexp 0,10000;
		}
		if(DORAM_1QUE <= 42) {
			setquest 98429;
			delquest 98429;
			getexp 0,25000;
		}
		mes "^ff0000【インフォメーション】^000000";
		mes "[シェレ]";
		mes "わかったわ。";
		mes "それじゃそのように";
		mes "手配しておくわ。";
		mes "あなたの活躍、期待してるわ！";
		set DORAM_1QUE,100;
		savepoint "lasagna.gat",299,239;
		warp "lasagna.gat",298,238;
		end;
	}
}

do_tu01a.gat,134,381,0	script	warp01#do_tu01a	45,2,2,{
	mes "^ff0000【インフォメーション】";
	mes "進行中のチュートリアルから";
	mes "離れてしまいました。";
	mes "進行中のチュートリアルの";
	mes "場所に戻りますか？^000000";
	next;
	if(select("はい","いいえ") == 2) {
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルの場所が";
		mes "わからなくなった場合、";
		mes "再度話しかけることで";
		mes "チュートリアル進行中のNPCの場所に";
		mes "戻ることができます。^000000";
		close;
	}
	if(DORAM_1QUE <= 1)
		warp "do_tu01a.gat",29,281;
	else if(DORAM_1QUE <= 22)
		warp "do_tu01a.gat",60,320;
	else
		warp "do_tu02a.gat",153,58;
	end;
}

do_tu01a.gat,29,283,0	script	object01#do_tu01a	139,1,1,{
	if(DORAM_1QUE == 0) {
		initnpctimer;
		cutin "do_su_001.bmp", 3;
		setquest 98400;
		set DORAM_1QUE,1;
	}
	end;
OnTimer1000:
	donpcevent "自警団員アジェニャー#do::OnTalk1";
	end;
OnTimer3000:
	stopnpctimer;
	donpcevent "自警団員アジェニャー#do::OnTalk2";
	end;
}

do_tu01a.gat,35,288,3	script	自警団員アジェニャー#do	10162,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 0:
	case 1:
		if(checkquest(98400)) {
			delquest 98400;
			getexp 2,10;
		}
		mes "[自警団員アジェニャー]";
		mes "おお、そうだ！　しっかりクリック出来たな。";
		next;
		mes "^009eff【インフォメーション】";
		mes "NPCとの会話中におよそ1分以上";
		mes "会話を進行しなかった場合、";
		mes "会話が中断してしまいます。";
		mes "その場合、再度話しかける";
		mes "必要があるのでご注意ください。^000000";
		next;
		mes "　チュートリアル<講習編>　1/12";
		mes "************************";
		mes "　・NPCの利用";
		mes "　・クエストウィンドウの開閉";
		mes "　・基本的な移動";
		mes "　・現在位置の確認";
		mes "************************";
		next;
		switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
		case 1:
			break;
		case 2:
			getexp 4,20;
			setquest 98402;
			set DORAM_1QUE,2;
			mes "^ff0000【インフォメーション】";
			mes "現在会話中のNPCでの";
			mes "チュートリアルは";
			mes "全て終了しました。";
			mes "次のチュートリアルの場所へ";
			mes "向かいますか？^000000";
			next;
			switch(select("次の場所へワープする","ワープせずに歩いて向かう","すべてのチュートリアルをスキップする")) {
			case 1:
				warp "do_tu01a.gat",60,319;
				end;
			case 2:
				close;
			}
		case 3:
			warp "do_tu05a.gat",136,95;
			end;
		}
		mes "[自警団員アジェニャー]";
		mes "今お前が私に話しかけてくれたように";
		mes "他の人に会った時にも";
		mes "まずは話しかけると良いぞ。";
		next;
		mes "^009eff【インフォメーション】";
		mes "マウスのクリックでゲーム内の";
		mes "各種インターフェースを操作出来ます。^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "NPCとの会話や移動、モンスターへの攻撃は";
		mes "マウスの左クリックを使用します。^000000";
		next;
		mes "[自警団員アジェニャー]";
		mes "^009eff新大陸^000000への渡航を";
		mes "希望する冒険者だな？";
		mes "最近は本当に多いな。";
		next;
		mes "[自警団員アジェニャー]";
		mes "しかし、";
		mes "話を聞いたときは驚いたよ。";
		mes "^009effミッドガルド^000000といったかな？";
		mes "行方不明になっていた^009effナビ号^000000と一緒に";
		mes "我々とは異なる種族が住む新大陸が";
		mes "発見されただなんて。";
		next;
		mes "[自警団員アジェニャー]";
		mes "おかげで辺境の漁村に過ぎなかった";
		mes "この^009effラザーニャ^000000は";
		mes "今では外からきたドラム達でいっぱいさ。";
		next;
		mes "[自警団員アジェニャー]";
		mes "ただ、外から来たドラムたちが";
		mes "かなり問題を起こしていてな……";
		mes "相当困らされているのだ。";
		next;
		mes "[自警団員アジェニャー]";
		mes "だから新大陸への渡航者には";
		mes "^009effファルファーレ自警団^000000への";
		mes "入団を義務付けることにした。";
		next;
		mes "[自警団員アジェニャー]";
		mes "お前も新大陸へ渡りたいなら";
		mes "入団テストをクリアして";
		mes "自警団に入ってくれ。";
		next;
		mes "[自警団員アジェニャー]";
		mes "とはいえ、";
		mes "冒険のいろはも知らないやつに";
		mes "いきなり試験を課したりはしない。";
		mes "まずは冒険の基礎を教えてやる。";
		next;
		mes "[自警団員アジェニャー]";
		mes "北東に仲間のアリオが待っている。";
		mes "彼に詳しい話は聞いてくれ。";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		next;
		cutin "do_su_003.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウには";
		mes "行き先や目標が書いてあります。";
		mes "今回のクエストにも";
		mes "行き先が書いてあるので、";
		mes "まずはそこを目指しましょう！^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "画面右上のマップに";
		mes "自分の現在地が表示されます。";
		mes "クエストウィンドウの情報を元に";
		mes "アリオを探しましょう！^000000";
		next;
		cutin "do_su_003.bmp", 255;
		viewpoint 1, 60, 322, 1, 0xFF0000;
		mes "[自警団員アジェニャー]";
		mes "^009effアリオ^000000のところにまで";
		mes "無事に辿り着けるように、";
		mes "^ff0000画面右上の地図に印をつけておいた。^000000";
		mes "慣れない土地だろうから";
		mes "気を付けて進むように！";
		next;
		mes "[自警団員アジェニャー]";
		mes "^009effアリオ^000000が";
		mes "この先の冒険に必要なことを";
		mes "色々と教えてくれるから";
		mes "尋ねてみると良い。";
		mes "私からは以上だ。";
		next;
		mes "^009eff【インフォメーション】";
		mes "クエスト「自警団員のレクチャー」を";
		mes "受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		setquest 98402;
		set DORAM_1QUE,2;
		getexp 4,20;
		close;
	case 2:
		mes "[自警団員アジェニャー]";
		mes "私はお前のように新大陸を目指して";
		mes "やってくる好奇心旺盛なドラム達を";
		mes "出迎えなければならない。";
		mes "この先どうするかはあそこにいる";
		mes "^009effアリオ^000000から聞いてくれ。";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		next;
		cutin "do_su_003.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウには";
		mes "行き先や目標が書いてあります。";
		mes "今回のクエストにも";
		mes "行き先が書いてあるので、";
		mes "まずはそこを目指しましょう！^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "画面右上のマップに";
		mes "自分の現在地が表示されます。";
		mes "クエストウィンドウの情報を元に";
		mes "アリオを探しましょう！^000000";
		next;
		cutin "do_su_003.bmp", 255;
		viewpoint 1, 60, 322, 1, 0xFF0000;
		mes "[自警団員アジェニャー]";
		mes "アリオのところにまで";
		mes "無事に辿り着けるように、";
		mes "^ff0000画面右上の地図に印をつけておいた。^000000";
		mes "慣れない土地だろうから";
		mes "気を付けて進むように！";
		next;
		mes "[自警団員アジェニャー]";
		mes "アリオは私達";
		mes "^009effファルファーレ自警団^000000の中でも";
		mes "優秀な奴だ。";
		mes "色々と教えてくれるだろう。";
		close;
	default:
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
OnTalk1:
	unittalk "自警団員アジェニャー : おい、そこの新入り！　こっちだ！";
	end;
OnTalk2:
	unittalk "自警団員アジェニャー : こっちに来て！　私をクリックするんだ！";
	end;
}

do_tu01a.gat,60,322,3	script	自警団員アリオ#do_tu01a	10154,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	while(1) {
		switch(DORAM_1QUE) {
		case 2:
			if(checkquest(98402)) {
				delquest 98402;
				getexp 6,40;
			}
			mes "　チュートリアル<講習編>　2/12";
			mes "************************";
			mes "　・モンスターへの攻撃";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98403;
				delquest 98403;
				set DORAM_1QUE,4;
				getexp 9,60;
				continue;
			}
			emotion 12;
			mes "[自警団員アリオ]";
			mes "やあ、元気かい？";
			mes "これから君の案内を担当する";
			mes "アリオと言うものだ。";
			mes "君は幸運だよ。";
			mes "私はファルファーレ自警団の中でも";
			mes "相当に優秀な団員だからな！";
			next;
			mes "[自警団員アリオ]";
			mes "大体の事は私が力になれると思うよ。";
			mes "まずは君がどの程度出来るか";
			mes "見せてもらおうかな？";
			next;
			mes "[自警団員アリオ]";
			mes "私の所に来るまでに";
			mes "めだまやきのような生き物を";
			mes "見かけなかったか？";
			mes "奴らは^009effエッグリン^000000という";
			mes "モンスターなんだ。";
			next;
			mes "[自警団員アリオ]";
			mes "腕試しに^009effエッグリン^000000を";
			mes "3体倒してこい！";
			mes "君の実力を私に見せてくれ！";
			next;
			mes "^009eff【インフォメーション】";
			mes "左クリックでモンスターへ攻撃できます。";
			mes "来た道を戻り、エッグリンを";
			mes "左クリックしてみましょう！^000000";
			close2;
			set DORAM_1QUE,3;
			setquest 98403;
			end;
		case 3:
			if(!(checkquest(98403)&0x4)) {
				mes "[自警団員アリオ]";
				mes "腕試しにエッグリンを";
				mes "3体倒してこい！";
				mes "君の実力を私に見せてくれ！";
				next;
				mes "^009eff【インフォメーション】";
				mes "左クリックでモンスターへ攻撃できます。";
				mes "来た道を戻り、エッグリンを";
				mes "左クリックしてみましょう！^000000";
				close;
			}
			mes "[自警団員アリオ]";
			mes "おお、中々の実力じゃないか。";
			mes "新大陸を目指しているだけの";
			mes "ことはあるな。";
			emotion 21;
			next;
			mes "[自警団員アリオ]";
			mes "君ならこの先の厳しい環境でも";
			mes "やっていけるだろうね。";
			next;
			if(checkquest(98403)) {
				delquest 98403;
				set DORAM_1QUE,4;
				getexp 9,60;
			}
		case 4:
		case 5:
			mes "　チュートリアル<講習編>　3/12";
			mes "************************";
			mes "　・所持アイテム欄の開き方";
			mes "　・アイテムの装備方法";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				getitem 26135, 1;
				setquest 98404;
				delquest 98404;
				set DORAM_1QUE,7;
				getexp 12,80;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "よし、これからの冒険に備えて";
			mes "これをやろう。";
			next;
			if(DORAM_1QUE == 4){
				set DORAM_1QUE,5;
				getitem 26135,1;
			}
			mes "[自警団員アリオ]";
			mes "今渡した「初心者用猫じゃらし」を";
			mes "装備したら";
			mes "もう一度私に話しかけてくれ。";
			mes "そうしたら次の訓練内容を伝えよう。";
			next;
			mes "^009eff【インフォメーション】";
			mes "アリオからもらったアイテムを";
			mes "確認するために、";
			mes "アイテムウィンドウを";
			mes "開いてみましょう！";
			next;
			cutin "do_su_004.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "アイテムウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<E>キー^009effで";
			mes "開くことができます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "アイテムウィンドウの装備タブから";
			mes "「初心者用猫じゃらし」を";
			mes "ダブルクリックしてみましょう。";
			mes "装備することができます。";
			next;
			cutin "do_su_005.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "装備しているアイテムは";
			mes "装備ウィンドウで確認できます。";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<Q>キー^009effで";
			mes "開くことができます。^000000";
			next;
			cutin "do_su_006.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ダブルクリック以外にも、";
			mes "アイテムウィンドウから";
			mes "装備したいアイテムを";
			mes "装備ウィンドウに";
			mes "ドラッグ＆ドロップする事で、";
			mes "装備を変更することができます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "ただし、装備欄を開いていない時に";
			mes "ドラッグ＆ドロップで";
			mes "地面を指定すると";
			mes "アイテムを落としてしまうので";
			mes "注意してください。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "ドロップロックボタンを押して";
			mes "ロック状態にすれば地面に";
			mes "アイテムが捨てられることはなくなります。";
			mes "心配な人はロック状態に";
			mes "しておきましょう。^000000";
			setquest 98404;
			set DORAM_1QUE,6;
			close2;
			cutin "do_su_002.bmp", 255;
			end;
		case 6:
			if(getequipid(4) != 26135) {
				mes "[自警団員アリオ]";
				mes "違うものを身につけてるな。";
				mes "私が渡した「初心者用猫じゃらし」を";
				mes "身に付けているかもう一度";
				mes "確認してくれよな。";
				next;
				mes "^009eff【インフォメーション】";
				mes "アリオからもらったアイテムを";
				mes "確認するために、";
				mes "アイテムウィンドウを";
				mes "開いてみましょう！";
				next;
				cutin "do_su_004.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "アイテムウィンドウは";
				mes "アイコンを左クリックするか";
				mes "^ff0000<Alt>キー+<E>キー^009effで";
				mes "開くことができます。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "アイテムウィンドウの装備タブから";
				mes "「初心者用猫じゃらし」を";
				mes "ダブルクリックしてみましょう。";
				mes "装備することができます。";
				next;
				cutin "do_su_005.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "装備しているアイテムは";
				mes "装備ウィンドウで確認できます。";
				mes "アイコンを左クリックするか";
				mes "^ff0000<Alt>キー+<Q>キー^009effで";
				mes "開くことができます。^000000";
				next;
				cutin "do_su_006.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "ダブルクリック以外にも、";
				mes "アイテムウィンドウから";
				mes "装備したいアイテムを";
				mes "装備ウィンドウに";
				mes "ドラッグ＆ドロップする事で、";
				mes "装備を変更することができます。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "ただし、装備欄を開いていない時に";
				mes "ドラッグ＆ドロップで";
				mes "地面を指定すると";
				mes "アイテムを落としてしまうので";
				mes "注意してください。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "ドロップロックボタンを押して";
				mes "ロック状態にすれば地面に";
				mes "アイテムが捨てられることはなくなります。";
				mes "心配な人はロック状態に";
				mes "しておきましょう。^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "なかなか飲みこみが早いな。";
			mes "新大陸を目指しているだけの";
			mes "ことはあるな。";
			next;
			delquest 98404;
			set DORAM_1QUE,7;
			getexp 12,80;
		case 7:
			mes "　チュートリアル<講習編>　4/12";
			mes "************************";
			mes "　・ステータスの説明";
			mes "　・ステータスの振り方";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98405;
				delquest 98405;
				set DORAM_1QUE,9;
				getexp 15,100;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "これからの冒険で";
			mes "君は様々な経験を積み";
			mes "成長していくだろう。";
			next;
			mes "[自警団員アリオ]";
			mes "君の進む道を決めるために";
			mes "まずはステータスについて";
			mes "理解を深める必要がある。";
			next;
			cutin "do_su_007.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ステータスは6種類あります。";
			mes "それぞれの特性を";
			mes "しっかりと把握しておきましょう！^000000";
			next;
			cutin "do_su_008.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ステータスウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<A>キー^009effで";
			mes "で開くことができます。";
			mes "まずはウィンドウを開いてみましょう！^000000";
			next;
			cutin "do_su_009.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "矢印をクリックすると";
			mes "Status Pointを消費し、";
			mes "ステータスが上昇します。";
			mes "Status PointはBaseLvが";
			mes "上がるごとに増えます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "序盤は";
			mes "^ff0000Str20";
			mes "Dex20^009eff";
			mes "を目指してステータスを";
			mes "上げていきましょう。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "一度消費したStatus Pointは";
			mes "戻すことができません。";
			mes "間違えて別のステータスに";
			mes "ポイントを使用しないように";
			mes "気を付けましょう。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "なおドラムはチュートリアル終了後、";
			mes "自警団員オリオに話しかけてから";
			mes "7日間、BaseLv70になるまで";
			mes "何度でもステータスが";
			mes "リセットできます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "ステータスの上げ方次第で";
			mes "モンスターとの戦い方は";
			mes "大きく変わります。";
			mes "自分に合ったステータスを";
			mes "探してみましょう。^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "ステータスについては理解したか？";
			mes "では、試しに^0000ffDexを";
			mes "「10」になるまで上げてくれ。^000000";
			next;
			mes "[自警団員アリオ]";
			mes "ちなみにステータスの";
			mes "「+○」という部分は";
			mes "装備やJobLvによる";
			mes "ステータスボーナスだ。";
			mes "今回は^0000ffステータスボーナスを含めず、";
			mes "Dexを10にしてくれ。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "装備アイテムがすべて外され、";
			mes "ステータス取得状況が";
			mes "リセットされました。^000000";
			setquest 98405;
			resetstatus;
			unequip -1;
			set DORAM_1QUE,8;
			close2;
			cutin "do_su_002.bmp", 255;
			end;
		case 8:
			if(readparam(bDex) < 10) {
				mes "[自警団員アリオ]";
				mes "Dexがまだ足りないぞ。";
				mes "「10」になるまで上げるんだ。";
				mes "君の実力を私に見せてくれ！";
				next;
				mes "[自警団員アリオ]";
				mes "ちなみにステータスの";
				mes "「+○」という部分は";
				mes "装備やJobLvによる";
				mes "ステータスボーナスだ。";
				mes "今回は^0000ffステータスボーナスを含めず、";
				mes "Dexを10にしてくれ。^000000";
				next;
				cutin "do_su_008.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "ステータスウィンドウは";
				mes "アイコンを左クリックするか";
				mes "^ff0000<Alt>キー+<A>キー^009effで";
				mes "で開くことができます。";
				mes "まずはウィンドウを開いてみましょう！^000000";
				next;
				cutin "do_su_009.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "矢印をクリックすると";
				mes "Status Pointを消費し、";
				mes "ステータスが上昇します。";
				mes "Status PointはBaseLvが";
				mes "上がるごとに増えます。^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "よし、ちゃんとDexを上げてきたな。";
			mes "これでモンスターに攻撃が";
			mes "命中しやすくなったぞ。";
			next;
			delquest 98405;
			set DORAM_1QUE,9;
			getexp 15,100;
		case 9:
			mes "　チュートリアル<講習編>　5/12";
			mes "************************";
			mes "　・スキルについて";
			mes "　・スキルウィンドウの開き方";
			mes "　・スキルの振り方";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98406;
				delquest 98406;
				set DORAM_1QUE,11;
				getexp 18,200;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "よし、次はスキルについて";
			mes "学ぼうではないか。";
			next;
			mes "^009eff【インフォメーション】";
			mes "スキルは職業毎に異なり";
			mes "職業がサモナーの貴方は";
			mes "攻撃や回復、補助のスキルを";
			mes "覚えることができます。^000000";
			next;
			cutin "do_su_010.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "スキルウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<S>キー^009effで";
			mes "開くことができます。";
			mes "まずはウィンドウを開いてみましょう！^000000";
			next;
			cutin "do_su_011.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "習得したいスキルを左クリックし";
			mes "確定ボタンを押して、";
			mes "確認に同意するとスキルポイントを";
			mes "消費してスキルを習得します。";
			mes "スキルポイントはJobLvが";
			mes "1上がるごとに1ポイント増えます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "一度消費したスキルポイントは";
			mes "戻すことができません。";
			mes "間違えて別のスキルに";
			mes "ポイントを使用しないように";
			mes "気を付けましょう。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "なおドラムはチュートリアル終了後、";
			mes "自警団員オリオに話しかけてから";
			mes "7日間、BaseLv70になるまで";
			mes "何度でもスキルが";
			mes "リセットできます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "習得するスキル次第で";
			mes "モンスターとの戦い方は";
			mes "大きく変わります。";
			mes "自分に合ったスキルを";
			mes "探してみましょう。^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "スキルについては理解したか？";
			mes "では、試しに";
			mes "^0000ff「ドラム基本スキル」^000000と";
			mes "^0000ff「かみつく」^000000を";
			mes "を習得してみてくれ。";
			next;
			mes "^009eff【インフォメーション】";
			mes "スキルの中には覚えるための";
			mes "条件があるものもあります。";
			mes "「かみつく」を習得するには";
			mes "「ドラム基本スキル」Lv1を";
			mes "習得している必要があります。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "まずは「ドラム基本スキル」を";
			mes "習得してから";
			mes "「かみつく」を習得しましょう。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "装備アイテムがすべて外され、";
			mes "スキル取得状況が";
			mes "リセットされました。^000000";
			setquest 98406;
			resetskill;
			unequip -1;
			set DORAM_1QUE,10;
			close;
		case 10:
			if(getskilllv(5019) == 0) {		// かみつくスキル
				mes "[自警団員アリオ]";
				if(getskilllv(5018) == 0) {		// ドラム基本スキル
					mes "どちらのスキルもまだ";
					mes "取得できていないぞ？";
				}
				else {
					mes "かみつくのスキルが";
					mes "まだ取得できていないぞ。";
				}
				mes "もう一度確認してくれ。";
				next;
				cutin "do_su_010.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "スキルウィンドウは";
				mes "アイコンを左クリックするか";
				mes "^ff0000<Alt>キー+<S>キー^009effで";
				mes "開くことができます。";
				mes "まずはウィンドウを開いてみましょう！^000000";
				next;
				cutin "do_su_011.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "習得したいスキルを左クリックし";
				mes "確定ボタンを押して、";
				mes "確認に同意するとスキルポイントを";
				mes "消費してスキルを習得します。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "一度消費したスキルポイントは";
				mes "戻すことができません。";
				mes "間違えて別のスキルに";
				mes "ポイントを使用しないように";
				mes "気を付けましょう。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "なおドラムはチュートリアル終了後、";
				mes "自警団員オリオに話しかけてから";
				mes "7日間、BaseLv70になるまで";
				mes "何度でもスキルが";
				mes "リセットできます。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "習得するスキル次第で";
				mes "モンスターとの戦い方は";
				mes "大きく変わります。";
				mes "自分に合ったスキルを";
				mes "探してみましょう。^000000";
				next;
				cutin "do_su_002.bmp", 255;
				mes "^009eff【インフォメーション】";
				mes "スキルの中には覚えるための";
				mes "条件があるものもあります。";
				mes "「かみつく」を習得するには";
				mes "「ドラム基本スキル」Lv1を";
				mes "習得している必要があります。^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "まずは「ドラム基本スキル」を";
				mes "習得してから";
				mes "「かみつく」を習得しましょう。^000000";
				close;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "ちゃんとスキルを";
			mes "覚えてきたな。";
			mes "さっそく使いたくなってきたか？";
			next;
			delquest 98406;
			set DORAM_1QUE,11;
			getexp 18,200;
		case 11:
			mes "　チュートリアル<講習編>　6/12";
			mes "************************";
			mes "　・ショートカットウィンドウ";
			mes "　・スキルの使い方";
			mes "　・スキルの試し打ち";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98407;
				delquest 98407;
				set DORAM_1QUE,13;
				getexp 21,400;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "よし、では今覚えたスキルを";
			mes "さっそく使ってみようか。";
			next;
			mes "[自警団員アリオ]";
			mes "っと、その前に、";
			mes "スキルやアイテムを登録できる";
			mes "ショートカットウィンドウを";
			mes "説明しよう。";
			next;
			mes "[自警団員アリオ]";
			mes "スキルやアイテムを";
			mes "ショートカットウィンドウに";
			mes "登録しておくと、";
			mes "素早く使用することができるぞ。";
			next;
			cutin "do_su_027.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ショートカットウィンドウは";
			mes "^ff0000<Ctrl>キー+<F12>キー^009effで";
			mes "開くことができます。";
			mes "ショートカットウィンドウは<F12>キーで";
			mes "切り替えることができ、";
			mes "最大で4つまで登録できます。";
			next;
			cutin "do_su_012.bmp", 255;
			mes "[自警団員アリオ]";
			mes "ショートカットウィンドウを";
			mes "開いたか？";
			mes "それじゃ次はスキルを";
			mes "ショートカットウィンドウに登録だ。";
			next;
			cutin "do_su_012.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "スキルをショートカットウィンドウに";
			mes "登録します。";
			mes "スキルウィンドウを開き、";
			mes "習得した「かみつく」を";
			mes "ショートカットウィンドウに";
			mes "ドラッグ＆ドロップしてみましょう！^000000";
			next;
			cutin "do_su_013.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ショートカットに対応した";
			mes "ファンクションキーを押すと";
			mes "スキルのカーソルが出るので、";
			mes "敵に合わせて左クリックしてみましょう。^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "使い方はわかったか？";
			mes "では^009effグラスファブル^000000を";
			mes "3体倒したら私に報告してくれ！";
			mes "^0000ff緑色の芋虫のようなモンスターで";
			mes "ここから東に行ったところにいる。^000000";
			mes "スキルを使いこなせばできるはずだ！";
			close2;
			setquest 98407;
			set DORAM_1QUE,12;
			end;
		case 12:
			if(!(checkquest(98407)&0x4)) {
				mes "[自警団員アリオ]";
				mes "では^009effグラスファブル^000000を";
				mes "3体倒したら私に報告してくれ！";
				mes "^0000ff緑色の芋虫のようなモンスターで";
				mes "ここから東に行ったところにいる。^000000";
				mes "スキルを使いこなせばできるはずだ！";
				next;
				cutin "do_su_027.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "ショートカットウィンドウは";
				mes "^ff0000<Ctrl>キー+<F12>キー^009effで";
				mes "開くことができます。";
				mes "ショートカットウィンドウは<F12>キーで";
				mes "切り替えることができ、";
				mes "最大で4つまで登録できます。";
				next;
				cutin "do_su_012.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "スキルをショートカットウィンドウに";
				mes "登録します。";
				mes "スキルウィンドウを開き、";
				mes "習得した「かみつく」を";
				mes "ショートカットウィンドウに";
				mes "ドラッグ＆ドロップしてみましょう！^000000";
				next;
				cutin "do_su_013.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "ショートカットに対応した";
				mes "ファンクションキーを押すと";
				mes "スキルのカーソルが出るので、";
				mes "敵に合わせて左クリックしてみましょう。^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "やるじゃないか。";
			mes "まあ新大陸に行きたいなら";
			mes "このくらいはやってもらわないとな。";
			next;
			delquest 98407;
			set DORAM_1QUE,13;
			getexp 21,400;
		case 13:
			mes "　チュートリアル<講習編>　7/12";
			mes "************************";
			mes "　・アイテムの精錬";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				delitem 26135, 1;
				getitem2 26135, 1, 1, 4, 0, 0, 0, 0, 0;
				setquest 98408;
				delquest 98408;
				set DORAM_1QUE,15;
				getexp 27,600;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "よし、それでは次の講習だ。";
			mes "これまでエッグリンと";
			mes "グラスファブルと戦ってもらったが、";
			mes "これから先、もっと強力な";
			mes "モンスターと戦うことになるだろう。";
			next;
			mes "[自警団員アリオ]";
			mes "強力なモンスターを倒すには";
			mes "強力な装備が必要になってくる。";
			mes "そこで自分の装備を強化し、";
			mes "性能を上げるのが^ff0000精錬^000000だ。";
			next;
			mes "[自警団員アリオ]";
			mes "そこにいる鍛冶屋に話しかけて、";
			mes "持っている武器を";
			mes "精錬してもらってこい。";
			next;
			mes "[自警団員アリオ]";
			mes "本来なら費用や素材が必要なんだが、";
			mes "今回は特別にそれらは一切不要で";
			mes "やってくれるように言ってある。";
			mes "「初心者用猫じゃらし」を";
			mes "精錬値が^ff0000+4^000000になるまで";
			mes "精錬してくるんだ！";
			next;
			cutin "do_su_023.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "装備を精錬することで";
			mes "武器や防具の性能を";
			mes "上昇させることができます。";
			mes "精錬に必要な費用や素材は";
			mes "アイテムによって異なります。^000000";
			next;
			cutin "do_su_024.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "特定の精錬値を超えて精錬すると、";
			mes "精錬に失敗することがあります。";
			mes "安全な精錬値は装備によって異なり、";
			mes "精錬に失敗したアイテムは";
			mes "消失してしまうので";
			mes "気をつけてください！^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "精錬値+4までなら";
			mes "精錬に失敗することはない。";
			mes "安心して行ってこい！";
			close2;
			setquest 98408;
			set DORAM_1QUE,14;
			end;
		case 14:
			switch(getequipid(4)) {
			case 26135:
				break;
			case 0:
				mes "[自警団員アリオ]";
				mes "おいおい、";
				mes "武器を装備してないじゃないか。";
				mes "ちゃんと装備してから";
				mes "声をかけてくれ。";
				close;
			default:
				mes "[自警団員アリオ]";
				mes "おいおい、";
				mes "「初心者用猫じゃらし」じゃ";
				mes "ないじゃないか。";
				mes "ちゃんと装備してから";
				mes "声をかけてくれ。";
				close;
			}
			if(getequiprefinerycnt(4) < 4) {
				mes "[自警団員アリオ]";
				mes "おいおい、";
				if(getequiprefinerycnt(4) == 0) {
					mes "精錬してもらってないじゃないか。";
					mes "ちゃんと精錬してもらってから";
					mes "声をかけてくれ。";
				}
				else {
					mes "精錬が足りないじゃないか。";
					mes "ちゃんと^ff0000+4^000000になるまで";
					mes "精錬してから声をかけてくれ。";
				}
				next;
				mes "[自警団員アリオ]";
				mes "そこにいる鍛冶屋に話しかけて、";
				mes "持っている武器を";
				mes "精錬してもらってこい。";
				mes "「初心者用猫じゃらし」を";
				mes "精錬値が^ff0000+4^000000になるまで";
				mes "精錬してくるんだ！";
				close;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "見事な猫じゃらしだ！";
			mes "さすが新大陸を目指すドラムだな。";
			next;
			delquest 98408;
			set DORAM_1QUE,15;
			getexp 27,600;
		case 15:
			mes "　チュートリアル<講習編>　8/12";
			mes "************************";
			mes "　・自然回復について";
			mes "　・重量50%と90%について";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98409;
				delquest 98409;
				set DORAM_1QUE,17;
				getexp 40,800;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "何度か戦ってみて";
			mes "わかってきたと思うが、";
			mes "モンスターから攻撃を受けると";
			mes "HPが減り、スキルで攻撃すると";
			mes "SPが減る。";
			next;
			mes "[自警団員アリオ]";
			mes "では、それらを回復するには";
			mes "どうするか？";
			mes "これからはそれを教える。";
			next;
			cutin "do_su_014.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "HPとSPは時間が経てば";
			mes "自然に回復しますが、";
			mes "座ることで回復する速度を";
			mes "早めることができます。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "「立つ」と「座る」は^ff0000<Insert>キー^009effで";
			mes "切り替えることができます。^000000";
			next;
			cutin "do_su_015.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "なお所持アイテムの重量が";
			mes "総重量の50%以上になると";
			mes "自然回復が発生しなくなります。";
			next;
			mes "^009eff【インフォメーション】";
			mes "さらに90%以上になると、";
			mes "通常攻撃やスキル攻撃が";
			mes "できなくなります。";
			mes "もしそうなってしまったら";
			mes "アイテムを捨てて";
			mes "重量を減らしましょう！^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "よし、それじゃ座った状態で";
			mes "話しかけてみろ！";
			close2;
			setquest 98409;
			set DORAM_1QUE,16;
			end;
		case 16:
			if(checksit() == 0) {
				mes "[自警団員アリオ]";
				mes "おいおい、座ってないじゃないか。";
				mes "もっとリラックスしていいんだぞ。";
				next;
				cutin "do_su_014.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "座って回復してみましょう。";
				mes "HPとSPが回復する速度が";
				mes "立っている時より素早く回復するのを";
				mes "実感できるはずです！";
				next;
				mes "^009eff【インフォメーション】";
				mes "「立つ」と「座る」は^ff0000<Insert>キー^009effで";
				mes "切り替えることができます。^000000";
				next;
				cutin "do_su_015.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "なお所持アイテムの重量が";
				mes "総重量の50%以上になると";
				mes "自然回復が発生しなくなります。";
				next;
				mes "^009eff【インフォメーション】";
				mes "さらに90%以上になると、";
				mes "通常攻撃やスキル攻撃が";
				mes "できなくなります。";
				mes "もしそうなってしまったら";
				mes "アイテムを捨てて";
				mes "重量を減らしましょう！^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "そうだ、時には進むだけじゃなく、";
			mes "立ち止まって休むことも重要だぞ。";
			next;
			delquest 98409;
			set DORAM_1QUE,17;
			getexp 40,800;
		case 17:
			mes "　チュートリアル<講習編>　9/12";
			mes "************************";
			mes "　・アイテムの購入方法";
			mes "　・アイテムの売却方法";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98410;
				delquest 98410;
				set DORAM_1QUE,19;
				getexp 48,1000;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "大分冒険の基本は抑えてきたな。";
			mes "それでは次の講習だが、";
			mes "これから多くのモンスターと";
			mes "戦っていくためには";
			mes "自然回復だけでは切り抜けられない";
			mes "場面も多くでてくるだろう。";
			next;
			mes "[自警団員アリオ]";
			mes "では、どうするか？";
			mes "これからはそれを教える。";
			next;
			mes "[自警団員アリオ]";
			mes "そこにいる商人から";
			mes "初心者用ポーション 5個";
			mes "初心者用青ポーション 5個";
			mes "を購入してこい。";
			mes "それでは、待っているぞ。";
			next;
			cutin "do_su_016.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "今までの戦闘で拾ってきた";
			mes "ゼロピーや綿毛などの収集品を";
			mes "商人に売却してZenyにしましょう。";
			next;
			cutin "do_su_017.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "Zenyを獲得したら、";
			mes "^ff0000初心者用ポーション 5個";
			mes "初心者用青ポーション 5個^009eff";
			mes "を購入しましょう！^000000";
			close2;
			setquest 98410;
			set DORAM_1QUE,18;
			cutin "do_su_002.bmp", 255;
			end;
		case 18:
			if(countitem(569) < 5 || countitem(11518) < 5) {
				mes "[自警団員アリオ]";
				mes "そこにいる商人から";
				mes "初心者用ポーション 5個";
				mes "初心者用青ポーション 5個";
				mes "を購入してこい。";
				mes "それでは、待っているぞ。";
				next;
				cutin "do_su_016.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "今までの戦闘で拾ってきた";
				mes "ゼロピーや綿毛などの収集品を";
				mes "商人に売却してZenyにしましょう。";
				next;
				cutin "do_su_017.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "Zenyを獲得したら、";
				mes "^ff0000初心者用ポーション 5個";
				mes "初心者用青ポーション 5個^009eff";
				mes "を購入しましょう！^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21;
			mes "[自警団員アリオ]";
			mes "ちゃんと買って来れたようだな。";
			mes "おつかいくらいなら";
			mes "お手の物ってところか。";
			next;
			delquest 98410;
			set DORAM_1QUE,19;
			getexp 48,1000;
		case 19:
			mes "　チュートリアル<講習編>　10/12";
			mes "************************";
			mes "　・消耗アイテムの使い方";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				setquest 98411;
				delquest 98411;
				set DORAM_1QUE,21;
				getexp 61,1200;
				continue;
			}
			mes "[自警団員アリオ]";
			mes "では、次はそのポーションの";
			mes "使い方を説明するので";
			mes "よく聞いておくように。";
			next;
			cutin "do_su_018.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "アイテムウィンドウを開いて";
			mes "購入したポーションを";
			mes "ダブルクリックしましょう。";
			mes "なお、NPCと会話中はアイテムが";
			mes "使用できない場合があるので";
			mes "注意してください！^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "またスキルの時のように、";
			mes "ショートカットウィンドウに登録し、";
			mes "対応したファンクションキーを";
			mes "押しても使用することができます。^000000";
			next;
			cutin "do_su_002.bmp", 255;
			mes "[自警団員アリオ]";
			mes "回復を実感できるように";
			mes "HPとSPを減らしておいたぞ。";
			mes "それでは、^0000ff持っている";
			mes "ポーションを全て使い切ったら^000000";
			mes "声をかけてくれ。";
			percentheal -50,-50;
			close2;
			setquest 98411;
			set DORAM_1QUE,20;
			end;
		case 20:
			if(countitem(569) > 0 || countitem(11518) > 0) {
				mes "[自警団員アリオ]";
				mes "^0000ff持っているポーションを";
				mes "全て使い切ったら^000000";
				mes "声をかけてくれ。";
				mes "それでは、待っているぞ。";
				next;
				cutin "do_su_018.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "所持欄を開いてポーションを";
				mes "ダブルクリックしましょう。";
				mes "なお、NPCと会話中はアイテムが";
				mes "使用できない場合があるので";
				mes "注意してください！^000000";
				next;
				mes "^009eff【インフォメーション】";
				mes "またスキルの時のように、";
				mes "ショートカットウィンドウに登録し、";
				mes "対応したファンクションキーを";
				mes "押しても使用することができます。^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			emotion 21, "自警団員アリオ#do_tu01a";
			mes "[自警団員アリオ]";
			mes "アイテムの使い方も覚えたな。";
			mes "緊急時に備えて";
			mes "いつでも使えるようにしておくんだ。";
			next;
			delquest 98411;
			set DORAM_1QUE,21;
			getexp 61,1200;
		case 21:
			mes "　チュートリアル<講習編>　11/12";
			mes "************************";
			mes "　・クエストウィンドウに";
			mes "　　直接入るアイテム";
			mes "************************";
			next;
			switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
			case 1:
				break;
			case 2:
				getitem 1081, 1;
				setquest 98412;
				delquest 98412;
				getexp 73,1400;
				setquest 98413;
				set DORAM_1QUE,23;
				mes "^ff0000【インフォメーション】";
				mes "現在会話中のNPCでの";
				mes "チュートリアルは";
				mes "全て終了しました。";
				mes "次のチュートリアルの場所へ";
				mes "向かいますか？^000000";
				next;
				switch(select("次の場所へワープする","ワープせずに歩いて向かう","すべてのチュートリアルをスキップする")) {
				case 1:
					warp "do_tu02a.gat",224,124;
					close;
				case 2:
					close;
				}
			}
			mes "[自警団員アリオ]";
			mes "ふむ、それでは次は……";
			next;
			cloakoffnpc "道具屋の末っ子#do_tu01a";
			donpcevent "道具屋の末っ子#do_tu01a::OnTalk1";
			next;
			mes "[自警団員アリオ]";
			mes "驚かせやがって、何の用だ？";
			mes "お前、道具屋の末っ子じゃないか。";
			mes "こんな危険な場所までどうして来たんだ？";
			next;
			mes "[道具屋の末っ子]";
			mes "転んだら無くしちゃったんだ……。";
			mes "荷物なんだけど、";
			mes "ハル兄さんに渡すように";
			mes "頼まれてたんだけど";
			mes "遊んでいたらいつのまにか…。";
			next;
			mes "[道具屋の末っ子]";
			mes "助けてよー、アリオ兄さん！";
			mes "怒られちゃう！";
			next;
			mes "[自警団員アリオ]";
			mes "治療師ハルに箱を届けるお使いを";
			mes "頼まれたが、ちょっと遊んでいたら";
			mes "転んだ隙に箱を見失ってしまった、";
			mes "ってことで良いか？";
			next;
			mes "[道具屋の末っ子]";
			mes "そう！　その通りです！";
			mes "さすが兄さん！";
			mes "よくわかりましたね。";
			next;
			mes "[自警団員アリオ]";
			mes "まず、お前はもう街に帰れ。";
			mes "箱の件は私がなんとかする。";
			mes "それと初対面の人がいる前で";
			mes "そんな恥ずかしい喋り方は";
			mes "もうやめろ。";
			next;
			mes "[道具屋の末っ子]";
			mes "兄さんそんな厳しいこと言わないで～。";
			mes "私はラザーニャの可愛い末っ子ですよ！";
			mes "とにかく、箱の件は頼みましたよ。";
			next;
			cloakonnpc "道具屋の末っ子#do_tu01a";
			mes "[自警団員アリオ]";
			mes "……";
			mes "はぁ……。";
			next;
			mes "[自警団員アリオ]";
			mes "こうなった以上仕方ない。";
			mes strcharinfo(0)+ "、";
			mes "箱の捜索をお願いできないか？";
			next;
			mes "[自警団員アリオ]";
			mes "いやあ、優秀なドラムが隣にいて";
			mes "本当に良かった！";
			mes "肝心の箱だが、恐らくは";
			mes "^009effエッグリン^000000が";
			mes "食べたのだろう。";
			next;
			mes "[自警団員アリオ]";
			mes "^009effエッグリン^000000を";
			mes "何匹か倒せば箱も見つかるだろう。";
			mes "さぁ、頼んだぞ！";
			next;
			mes "^009eff【インフォメーション】";
			mes "エッグリンが配達用の木箱を";
			mes "飲み込んだようです。";
			mes "探して来てアリオに見せましょう。";
			next;
			cutin "do_su_019.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "通常、アイテムはモンスターを";
			mes "倒した際に地面にドロップしますが、";
			mes "クエストによっては対象のアイテムが";
			mes "直接アイテムウィンドウに";
			mes "入る場合があります。^000000";
			close2;
			setquest 98412;
			set DORAM_1QUE,22;
			cutin "do_su_002.bmp", 255;
			end;
		case 22:
			if(countitem(1081) < 1) {
				mes "[自警団員アリオ]";
				mes "^009effエッグリン^000000はさっき倒したし";
				mes "見た目は覚えているな？";
				mes "どの個体が呑み込んだかは";
				mes "わからないが、";
				mes "片っ端から倒せば見つかるはずだ。";
				next;
				mes "^009eff【インフォメーション】";
				mes "エッグリンが配達用の木箱を";
				mes "飲み込んだようです。";
				mes "探して来てアリオに見せましょう。";
				next;
				cutin "do_su_019.bmp", 3;
				mes "^009eff【インフォメーション】";
				mes "通常、アイテムはモンスターを";
				mes "倒した際に地面にドロップしますが、";
				mes "クエストによっては対象のアイテムが";
				mes "直接アイテムウィンドウに";
				mes "入る場合があります。^000000";
				close2;
				cutin "do_su_002.bmp", 255;
				end;
			}
			mes "[自警団員アリオ]";
			mes "おお、それだよ、その箱だ！";
			mes "それじゃあ次はその箱を";
			mes "ハルのところまで届けてもらえるか？";
			next;
			mes "[自警団員アリオ]";
			mes "街についたら治療師ハルを";
			mes "探して渡してくれ。";
			next;
			emotion 27;
			mes "[自警団員アリオ]";
			mes "町には道なりに北東に歩いて";
			mes "いけばいい。";
			mes "ずっと歩いていけばいい。";
			mes "簡単な道だが、気を付けろよ。";
			next;
			cutin "do_su_020.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ワープリンクに触れると";
			mes "別のマップに移動できます。";
			mes "このマップの北にある";
			mes "ワープリンクに触れれば、";
			mes "ラザーニャの町に";
			mes "移動することができます。^000000";
			close2;
			viewpoint 1, 134, 381, 1, 0xFF0000;
			cutin "do_su_002.bmp", 255;
			delquest 98412;
			getexp 73,1400;
			setquest 98413;
			set DORAM_1QUE,23;
			end;
		case 23:
			mes "[自警団員アリオ]";
			mes "治療師のハルが荷物を";
			mes "待っているだろうから";
			mes "急いで持っていってやってくれ。";
			next;
			mes "[自警団員アリオ]";
			mes "町には道なりに北東に歩いて";
			mes "いけばいい。";
			mes "ずっと歩いていけばいい。";
			mes "簡単な道だが、気を付けろよ。";
			next;
			mes "[自警団員アリオ]";
			mes "私も後でいくから";
			mes "心配しないで真っ直ぐ行けよ。";
			next;
			cutin "do_su_020.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "ワープリンクに触れると";
			mes "別のマップに移動できます。";
			mes "このマップの北にある";
			mes "ワープリンクに触れれば、";
			mes "ラザーニャの町に";
			mes "移動することができます。^000000";
			close2;
			viewpoint 1, 134, 381, 1, 0xFF0000;
			cutin "do_su_002.bmp", 255;
			end;
		case 24:
			mes "[自警団員アリオ]";
			mes "ミッドガルドには行けたか？";
			mes "港で何か問題が起きているようだが";
			mes "大丈夫、君なら解決できるさ。";
			close;
		default:
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルから";
			mes "離れてしまいました。";
			mes "進行中のチュートリアルの";
			mes "場所に戻りますか？^000000";
			next;
			if(select("はい","いいえ") == 2) {
				mes "^ff0000【インフォメーション】";
				mes "進行中のチュートリアルの場所が";
				mes "わからなくなった場合、";
				mes "再度話しかけることで";
				mes "チュートリアル進行中のNPCの場所に";
				mes "戻ることができます。^000000";
				close;
			}
			if(DORAM_1QUE <= 1)
				warp "do_tu01a.gat",29,281;
			else if(DORAM_1QUE <= 24)
				warp "do_tu01a.gat",60,320;
			else if(DORAM_1QUE <= 26)
				warp "do_tu02a.gat",224,124;
			else if(DORAM_1QUE <= 34)
				warp "do_tu02a.gat",235,196;
			else if(DORAM_1QUE <= 37)
				warp "do_tu02a.gat",203,322;
			else
				warp "do_tu05a.gat",26,62;
			end;
		}
	}
}
-	shop	lasagna_callshop	-1,569:1,11518:1
do_tu01a.gat,52,323,4	script	旅の行商人#do_tu01a	10163,{
	if(DORAM_1QUE < 18) {
		mes "[旅の行商人]";
		mes "オイラは旅の行商人さ。";
		mes "でも、キミには何も売れないよ。";
		mes "自警団のアリオさんに";
		mes "許可を貰った人とだけ取引が";
		mes "許されているんだ。";
		mes "すまないね。";
		close;
	}
	if(DORAM_1QUE >= 19) {
		mes "[旅の行商人]";
		mes "新大陸かぁ……。";
		mes "オイラも自警団に入って";
		mes "海を渡ろうか悩むよ。";
		next;
		mes "[旅の行商人]";
		mes "あいにくポーションは今";
		mes "きらしちゃってね。";
		mes "売れる物は何もないんだ。";
		close;
	}
	if(countitem(569) >= 5 && countitem(11518) >= 5) {
		mes "[旅の行商人]";
		mes "ポーションはもう";
		mes "それぞれ5個以上";
		mes "持っているようだよ？";
		mes "アリオさんに早く見せておいで。";
		close;
	}
	mes "[旅の行商人]";
	mes "ポーションを買いに";
	mes "来たんだろう？";
	mes "アリオさんから話は";
	mes "聞いているよ。";
	next;
	if(Zeny == 0) {
		mes "[旅の行商人]";
		mes "キミは……";
		mes "お金を持っていないじゃないか。";
		mes "そういう時はまず";
		mes "不要なものを売って";
		mes "お金にしてから買うんだよ。";
		next;
	}
	switch(select("買う","売る")) {
	case 1:
		callshop "lasagna_callshop",1;
		close;
	case 2:
		callshop "lasagna_callshop",2;
		close;
	}
}

do_tu01a.gat,62,320,3	script	道具屋の末っ子#do_tu01a	10167,{
	end;
OnTalk1:
	unittalk "道具屋の末っ子 : ア……アリオオオ！！！";
	end;
OnInit:
	cloakonnpc;
	end;
}

do_tu01a.gat,66,323,4	script	旅の鍛冶屋#do_tu01a	10163,{
	if(DORAM_1QUE < 14) {
		mes "[旅の鍛冶屋]";
		mes "オレは旅の鍛冶屋だ。";
		mes "残念だがアリオの兄ちゃんの";
		mes "許可が無いと精錬はしてやれねえ。";
		mes "わりぃな。";
		close;
	}
	if(DORAM_1QUE >= 15) {
		mes "[旅の鍛冶屋]";
		mes "生まれ変わった武器の具合は";
		mes "どうだい？";
		close;
	}
	mes "[旅の鍛冶屋]";
	mes "アリオの兄ちゃんから";
	mes "話は聞いている。精錬だな？";
	mes "任せておけ。";
	mes "どれを精錬するんだ？";
	next;
	switch(getequipid(4)) {
	case 26135:
		break;
	case 0:
		mes "[旅の鍛冶屋]";
		mes "だがその前に、";
		mes "精錬したい武器を装備してくれ。";
		mes "そうじゃないと";
		mes "精錬のしようがないぜ。";
		close;
	default:
		mes "[旅の鍛冶屋]";
		mes "おっと、";
		mes "そのアイテムは精錬できないな。";
		mes "「初心者用猫じゃらし」を";
		mes "装備してくれ。";
		close;
	}
	if(getequiprefinerycnt(4) >= 4) {
		mes "[旅の鍛冶屋]";
		mes "おっと、";
		mes "その武器はもう精錬済みだな。";
		mes "今回オレが精錬してやれるのは";
		mes "^ff0000+4^000000までだ。";
		next;
		mes "[旅の鍛冶屋]";
		mes "そこから先は他のやつに";
		mes "頼んでくれ。";
		mes "サービスで精錬してやってるんだ、";
		mes "文句言わないでくれよ？";
		close;
	}
	if(select("^nItemID^"+ getequipid(4),"やめる") == 2) {
		mes "[旅の鍛冶屋]";
		mes "ん？　精錬しないのか？";
		close;
	}
	successrefitem 4;
	mes "[旅の鍛冶屋]";
	mes "そらよっと！";
	mes "どうだい？";
	mes "良い仕事してるだろ？";
	close;
}

do_tu02a.gat,150,54,0	warp	warp01#do_tu02a	2,2,do_tu01a.gat,131,378
do_tu02a.gat,358,91,0	warp	warp02#do_tu02a	2,2,do_tu04a.gat,20,98
do_tu02a.gat,205,327,0	script	warp03#do_tu02a	45,2,2,{
	switch(DORAM_1QUE) {
	case 33:
		mes "‐近くに座っている";
		mes "　船員のドラムに話しかけよう‐";
		close;
	default:
		if(DORAM_1QUE > 34) {
			warp "do_tu05a.gat",55,61;
			end;
		}
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		end;
	}
}

do_tu02a.gat,153,58,0	script	object01#do_tu02a	139,3,3,{
	if(DORAM_1QUE == 23) {
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウには";
		mes "行き先や目標が書いてあります。";
		mes "^ff0000治療師ハル^009effの場所も";
		mes "クエストウィンドウに書いてあるので";
		mes "そこを目指しましょう！^000000";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		next;
		cutin "do_su_002.bmp", 255;
		mes "^009eff【インフォメーション】";
		mes "また、画面右上のマップの";
		mes "下部にある「+」「-」で";
		mes "マップの拡大縮小ができます。";
		mes "状況に応じてマップのサイズを";
		mes "変えてみましょう！^000000";
		close2;
		viewpoint 1, 224, 126, 1, 0xFF0000;
		end;
	}
	end;
}

do_tu02a.gat,224,126,5	script	治療師ハル#do_tu02a	10164,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 23:
		delquest 98413;
		getexp 87,1600;
		savepoint "do_tu02a.gat",224,123;
		set DORAM_1QUE,24;
		mes "^009eff【インフォメーション】";
		mes "セーブポイントを更新しました。";
		mes "戦闘不能になった場合、";
		mes "この場所で復活します。^000000";
		next;
	case 24:
		mes "　チュートリアル<講習編>　12/12";
		mes "************************";
		mes "　・クエストスキル";
		mes "************************";
		next;
		switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
		case 1:
			break;
		case 2:
			getexp 103,1800;
			delitem 1081, 1;
			skill 142,1,0;
			setquest 98415;
			set DORAM_1QUE,25;
			mes "^ff0000【インフォメーション】";
			mes "現在会話中のNPCでの";
			mes "チュートリアルは";
			mes "全て終了しました。";
			mes "次のチュートリアルの場所へ";
			mes "向かいますか？^000000";
			next;
			switch(select("次の場所へワープする","ワープせずに歩いて向かう","すべてのチュートリアルをスキップする")) {
			case 1:
				warp "do_tu02a.gat",235,196;
				close;
			case 2:
				close;
			}
		}
		emotion 20, "治療師ハル#do_tu02a";
		mes "[治療師ハル]";
		mes "そろそろ荷物が届く頃なんですが……";
		mes "遅いな……。";
		next;
		mes "[治療師ハル]";
		mes "あれ？";
		mes "その箱は？";
		cloakoffnpc "道具屋の末っ子#do_tu02a";
		donpcevent "道具屋の末っ子#do_tu02a::OnTalk1";
		next;
		mes "[治療師ハル]";
		mes "おお、待っていたよ。";
		mes "今日はずいぶんと遅かったじゃないか。";
		mes "まさか、どこかに寄り道して";
		mes "遊んでたんじゃないだろうな。";
		next;
		mes "[道具屋の末っ子]";
		mes "い……いや？　ぜんぜん？";
		mes "そんなことないですよ？";
		mes "この人は荷物が重そうだからって";
		mes "親切にもこの荷物を";
		mes "持ってくれたんです。";
		next;
		mes "[治療師ハル]";
		mes "そうでしたか。";
		mes "わざわざありがとうございます。";
		next;
		mes "[道具屋の末っ子]";
		mes "そ、それじゃ私はこれで！";
		next;
		donpcevent "道具屋の末っ子#do_tu02a::OnTalk2";
		cloakonnpc "道具屋の末っ子#do_tu02a";
		mes "[治療師ハル]";
		mes "おや、もう行ってしまった。";
		mes "せっかちな子だね。";
		next;
		mes "[治療師ハル]";
		mes "まあ、大方どこかで無くした";
		mes "荷物をあなたが見つけて";
		mes "持って来てくれたんでしょう？";
		mes "よくあることなんで";
		mes "もう慣れましたよ。";
		next;
		mes "[治療師ハル]";
		mes "ふむ……。";
		mes "失礼ですが、見たところ";
		mes "まだ旅には不慣れなようですね。";
		next;
		mes "[治療師ハル]";
		mes "荷物を持って来てくれたお礼に、";
		mes "旅の役に立つスキル";
		mes "「応急手当」を";
		mes "教えてあげましょう。";
		next;
		mes "^009eff【インフォメーション】";
		mes "レベルを上げて習得するのではなく、";
		mes "クエストを達成することで";
		mes "習得できるスキルを";
		mes "クエストスキルと呼びます。^000000";
		next;
		mes "[治療師ハル]";
		mes "応急手当はSPを消費して";
		mes "自分のHPを回復するスキルです。";
		next;
		mes "[治療師ハル]";
		mes "回復する量はわずかですが、";
		mes "いざという時には役にたつでしょう。";
		mes "覚えておいて損はないですよ。";
		next;
		mes "[治療師ハル]";
		mes "さあ、いいですか？";
		mes "よく見ていてください。";
		next;
		mes "[治療師ハル]";
		mes "まずここを上に……";
		next;
		mes "[治療師ハル]";
		mes "次は下に……";
		next;
		mes "[治療師ハル]";
		mes "左右に2回動かして……";
		next;
		mes "[治療師ハル]";
		mes "はい！";
		mes "できました！";
		misceffect 58,"";
		misceffect 234,"";
		skill 142,1,0;
		next;
		cutin "do_su_010.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "スキル「応急手当」を習得しました。";
		mes "スキルウィンドウを開いて";
		mes "確認しましょう。";
		mes "クエストスキルはスキルポイントを";
		mes "消費せずに覚えることができます。^000000";
		next;
		cutin "do_su_010.bmp", 255;
		mes "[治療師ハル]";
		mes "あくまで応急手当ですので、";
		mes "危ない時はポーションなどで";
		mes "回復するようにしてくださいね。";
		next;
		cloakoffnpc "自警団員アリオ#do_tu02a";
		donpcevent "自警団員アリオ#do_tu02a::OnTalk1";
		mes "[自警団員アリオ]";
		mes "お、ちゃんと荷物を";
		mes "届けられたようだな。";
		next;
		mes "[自警団員アリオ]";
		mes "冒険に必要なことは";
		mes "一通り教えたし、";
		mes "こうしてちゃんと配達の依頼も";
		mes "こなすことができた。";
		next;
		mes "[自警団員アリオ]";
		mes "これならもう入団テストに";
		mes "挑んでも大丈夫そうだな。";
		mes "それじゃ、団長のところに向かうぞ。";
		next;
		mes "^009eff【インフォメーション】";
		mes "お疲れ様でした。";
		mes "チュートリアル<講習編>は";
		mes "以上で終了となります。^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "次からは実際のクエストに近い内容の";
		mes "^ff0000チュートリアル<実践編>^009effが";
		mes "始まります。";
		mes "これまでのチュートリアルで";
		mes "学んだことを活かし、";
		mes "クエストをクリアしてください！^000000";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエスト「入団テスト」を";
		mes "受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		cloakonnpc "自警団員アリオ#do_tu02a";
		viewpoint 1, 235, 198, 1, 0xFF0000;
		getexp 103,1800;
		delitem 1081,1;
		setquest 98415;
		set DORAM_1QUE,25;
		cutin "do_su_002.bmp", 255;
		close;
	case 25:
		mes "[治療師ハル]";
		mes "団長に会うなら";
		mes "よろしく言っておいてください。";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエスト「入団テスト」を";
		mes "受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		close2;
		cutin "do_su_002.bmp", 255;
		viewpoint 1, 235, 198, 1, 0xFF0000;
		end;
	case 26:
		mes "[治療師ハル]";
		mes "団長には会えたようだね。";
		close;
	default:
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
}

do_tu02a.gat,226,124,3	script	道具屋の末っ子#do_tu02a	10167,{
	end;
OnTalk1:
	unittalk "道具屋の末っ子 : お、おまたせしましたー！";
	end;
OnTalk2:
	unittalk "道具屋の末っ子 : ご利用ありがとうございましたー！";
	end;
OnInit:
	cloakonnpc;
	end;
}

do_tu02a.gat,230,127,3	script	自警団員アリオ#do_tu02a	10154,{
	end;
OnTalk1:
	unittalk "自警団員アリオ : ちょうど用事が済んだようだな。";
	end;
OnInit:
	cloakonnpc;
	end;
}

do_tu02a.gat,235,198,3	script	ペロン団長#do_tu02a	10152,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 25:
		delquest 98415;
		getexp 121,2000;
		savepoint "do_tu02a.gat",235,196;
		set DORAM_1QUE,26;
		mes "^009eff【インフォメーション】";
		mes "セーブポイントを更新しました。";
		mes "戦闘不能になった場合、";
		mes "この場所で復活します。^000000";
		next;
	case 26:
		mes "　チュートリアル<実践編>　1/3";
		mes "************************";
		mes "　・入団テスト";
		mes "************************";
		next;
		switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
		case 1:
			break;
		case 2:
			setquest 98416;
			delquest 98416;
			getexp 140,2200;
			setquest 98417;
			delquest 98417;
			getexp 157,2400;
			setquest 98418;
			delquest 98418;
			getexp 177,2600;
			setquest 98419;
			delquest 98419;
			getexp 214,2800;
			getexp 239,3000;
			viewpoint 1, 203, 324, 1, 0xFF0000;
			setquest 98421;
			set DORAM_1QUE,33;
			getitem 25046,1;	// 乗船許可書
			getitem 15273,1;	// 白いTシャツ
			getitem 22183,1;	// 木のスリッパ
			mes "^ff0000【インフォメーション】";
			mes "現在会話中のNPCでの";
			mes "チュートリアルは";
			mes "全て終了しました。";
			mes "次のチュートリアルの場所へ";
			mes "向かいますか？^000000";
			next;
			switch(select("次の場所へワープする","ワープせずに歩いて向かう","すべてのチュートリアルをスキップする")) {
			case 1:
				warp "do_tu02a.gat",205,323;
				close;
			case 2:
				close;
			}
		}
	case 27:
		mes "[ペロン団長]";
		mes "^ff0000町の南東の出口から出た先にある";
		mes "ラビオル森^000000に行ってください。";
		next;
		mes "[ペロン団長]";
		mes "そして森の東北東にある";
		mes "^ff0000大きなトゲの生えた枝^000000を探し、";
		mes "その枝を1個取ってきてください。";
		mes "そうすれば合格です。";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストを受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		next;
		cutin "do_su_003.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "大きなトゲの生えた枝の場所は";
		mes "クエストウィンドウに";
		mes "書いてあります。";
		mes "まずは町の南東側から外に出て、";
		mes "ラビオル森に行きましょう。^000000";
		next;
		cutin "do_su_028.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "ラビオル森はラザーニャの町の";
		mes "^ff0000隣のMAP^009effにあります。";
		mes "チャットウィンドウに";
		mes "^ff0000「/where」^009effと入力すると";
		mes "自分のいるマップ名を";
		mes "調べることができます。^000000";
		next;
		cutin "do_su_002.bmp", 255;
		mes "[ペロン団長]";
		mes "ラビオル森には";
		mes "攻撃的なモンスターがいます。";
		mes "十分気をつけてください。";
		next;
		mes "[ペロン団長]";
		mes "もし一人で行くのが難しい場合は、";
		mes "他の仲間と一緒に^ff0000パーティー^000000を";
		mes "組むのも良いでしょう。";
		next;
		mes "[ペロン団長]";
		mes "ずるいことではありません。";
		mes "仲間を集めるのも実力のうちです。";
		next;
		cutin "do_su_021.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "パーティーウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<Z>キー^009effで";
		mes "で開くことができます。";
		mes "開いたら「パーティー作成」で";
		mes "パーティーを作ってみましょう！^000000";
		next;
		cutin "do_su_022.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "パーティー名を決めて";
		mes "パーティーを作ったら、";
		mes "他のプレイヤーを右クリックすると";
		mes "「パーティー加入要請」を";
		mes "することができます。^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "相手がパーティー要請を承認すると、";
		mes "パーティーに入れることができます。";
		mes "お友達を誘ってパーティーを";
		mes "組んでみましょう！^000000";
		close2;
		viewpoint 1, 358, 91, 1, 0xFF0000;
		cutin "do_su_002.bmp", 255;
		end;
	case 28:
		emotion 21;
		mes "[ペロン団長]";
		mes "無事に枝を持ち帰りましたね。";
		mes "お見事です。";
		next;
		delquest 98416;
		getexp 140,2200;
		set DORAM_1QUE,29;
		mes "[ペロン団長]";
		mes "それではその枝を持って";
		mes "私についてきてください。";
		mes "次のテストを行います。";
		close2;
		setquest 98417;
		warp "do_tu03a.gat",61,94;
		end;
	case 29:
	case 30:
	case 31:
		close;
	case 32:
		if(checkquest(98419)) {
			delquest 98419;
			getexp 214,2800;
		}
		mes "[ペロン団長]";
		mes "お疲れ様でした。";
		mes "テストはこれで終わりです。";
		next;
		mes "[ペロン団長]";
		mes "ラビオル森の奥まで行き";
		mes "枝を取って来る実力。";
		next;
		mes "[ペロン団長]";
		mes "口を閉ざしたバジルリスクから";
		mes "情報を引き出す方法に";
		mes "辿り着いた頭脳と洞察力。";
		next;
		mes "[ペロン団長]";
		mes "どちらも優れたものを";
		mes "持っていることがわかりました。";
		mes "あなたはファルファーレ自警団に";
		mes "ふさわしい人物です。";
		next;
		emotion 46,"";
		mes "[ペロン団長]";
		mes "あなたの入団を認めましょう。";
		mes "おめでとうございます。";
		next;
		mes "[ペロン団長]";
		mes "さて、あなたは新大陸への渡航を";
		mes "希望していましたね。";
		next;
		mes "[ペロン団長]";
		mes "この乗船許可書を持って";
		mes "北の港に停泊している船に行けば、";
		mes "あなたを乗せてくれるでしょう。";
		mes "さっそく行ってみてください。";
		next;
		mes "[ペロン団長]";
		mes "ふふふ……";
		mes "私も若い頃は冒険に出て";
		mes "何かでかいことを成し遂げてやろうと";
		mes "息巻いていたものです。";
		next;
		mes "[ペロン団長]";
		mes "ですが……";
		mes "私には守らなければならないものが";
		mes "多過ぎました。";
		next;
		mes "[ペロン団長]";
		mes "まあ、あまりにも";
		mes "船酔いが酷かったので";
		mes "冒険に出るのが";
		mes "難しかったというのも";
		mes "あるんですけどね。";
		mes "ハハハハ。";
		close2;
		set DORAM_1QUE,33;
		getitem 25046,1;	// 乗船許可書
		getitem 15273,1;	// 白いTシャツ
		getitem 22183,1;	// 木のスリッパ
		cutin "do_su_002.bmp", 255;
		getexp 239,3000;
		viewpoint 1, 203, 324, 1, 0xFF0000;
		setquest 98421;
		end;
	case 33:
		mes "[ペロン団長]";
		mes "この乗船許可書を持って";
		mes "北の港に停泊している船に行けば、";
		mes "あなたを乗せてくれるでしょう。";
		mes "さっそく行ってみてください。";
		close2;
		viewpoint 1, 203, 324, 1, 0xFF0000;
		end;
	default:
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
}

do_tu02a.gat,203,324,5	script	エッグリン#do_tu02a	10157,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 33:
		delquest 98421;
		getexp 267,3200;
		savepoint "do_tu02a.gat",235,196;
		set DORAM_1QUE,34;
		mes "^009eff【インフォメーション】";
		mes "セーブポイントを更新しました。";
		mes "戦闘不能になった場合、";
		mes "この場所で復活します。^000000";
		next;
	case 34:
		mes "　チュートリアル<実践編>　2/3";
		mes "************************";
		mes "　・船員のお願い";
		mes "************************";
		next;
		switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
		case 1:
			break;
		case 2:
			setquest 98422;
			delquest 98422;
			getexp 298,3400;
			getexp 332,3600;
			setquest 98424;
			set DORAM_1QUE,36;
			mes "^ff0000【インフォメーション】";
			mes "現在会話中のNPCでの";
			mes "チュートリアルは";
			mes "全て終了しました。";
			mes "次のチュートリアルの場所へ";
			mes "向かいますか？^000000";
			next;
			switch(select("次の場所へワープする","ワープせずに歩いて向かう","すべてのチュートリアルをスキップする")) {
			case 1:
				warp "do_tu05a.gat",26,62;
				close;
			case 2:
				close;
			}
		}
		emotion 45;
		mes "[エッグリン]";
		mes "乗船希望かな？";
		mes "チケットを見せて。";
		next;
		mes "[エッグリン]";
		mes "冒険者？　船は初めてかい？";
		mes "新大陸ではドラム族の名に恥じない";
		mes "活躍を期待してるよ。";
		mes "頑張ってね。";
		next;
		mes "[エッグリン]";
		mes "あ、そうだ。";
		mes "中に入るついでに、";
		mes "奥の食堂にいる料理長に";
		mes "渡して欲しい料理素材が";
		mes "あるんだ。いいかな？";
		next;
		menu "はい",-;
		mes "[エッグリン]";
		mes "ありがと。";
		mes "ただ渡す際に、";
		mes "ちょっと注意があるんだ。";
		next;
		menu "注意？",-;
		mes "[エッグリン]";
		mes "うん。";
		mes "料理長は変わり者だから、";
		mes "普通に渡したんじゃ";
		mes "受け取ってくれないんだ。";
		mes "だから今から言う通りに";
		mes "やるんだ。いいね？";
		next;
		mes "[エッグリン]";
		mes "僕が渡す料理素材を";
		mes "料理長の胸元に投げつけて、";
		mes "^0000cd「超大型新人が来てやったぞ！」^000000";
		mes "と言うんだ。";
		next;
		mes "[エッグリン]";
		mes "初めて船に乗るドラムがそれを";
		mes "やると航海が上手く行くらしい。";
		mes "そういう^0000ffおまじない^000000なんだ。";
		mes "料理長もそれが勇敢な行為だと";
		mes "信じてる。";
		next;
		getitem 25047,1;		// カルニャック
		set DORAM_1QUE,35;
		emotion 12, "エッグリン#do_tu02a";
		mes "[エッグリン]";
		mes "わかったかな？";
		mes "それじゃよろしく頼むよ！";
		setquest 98422;
		next;
		mes "^009eff【インフォメーション】";
		mes "クエスト「船員のお願い」を";
		mes "受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		close;
	case 35:
		mes "[エッグリン]";
		mes "僕が渡した料理素材を";
		mes "料理長の胸元に投げつけて、";
		mes "^0000cd「超大型新人が来てやったぞ！」^000000";
		mes "と言うんだ。";
		next;
		mes "[エッグリン]";
		mes "初めて船に乗るドラムがそれを";
		mes "やると航海が上手く行くらしい。";
		mes "そういうおまじないなんだ。";
		mes "料理長もそれが勇敢な行為だと";
		mes "信じてる。";
		next;
		emotion 12;
		mes "[エッグリン]";
		mes "わかったかな？";
		mes "それじゃよろしく頼むよ！";
		close;
	case 36:
		mes "[エッグリン]";
		mes "ええ！　本当にやっちゃったの！";
		mes "冗談だったのに！";
		mes "アハハハハ！";
		mes "で？　どうだったの？";
		mes "よく無事だったね？";
		next;
		mes "[エッグリン]";
		mes "え？";
		mes "料理長がカンカン？";
		next;
		mes "[エッグリン]";
		mes "……どうしよ。";
		close;
	default:
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
}

do_tu03a.gat,59,90,5	script	ペロン団長#do_tu03e	10152,{
	switch(DORAM_1QUE) {
	case 29:
		if(checkquest(98417)) {
			delquest 98417;
			getexp 157,2400;
		}
		mes "[????]";
		mes "……。";
		next;
		mes "‐壺の中から何かが顔を出している‐";
		next;
		mes "[ペロン団長]";
		mes "ラビオル森で見たかもしれませんが、";
		mes "こいつはバジルリスクといって";
		mes "ラザーニャの街から";
		mes "少し離れたところに住んでいます。";
		next;
		mes "[ペロン団長]";
		mes "これまで何もなかったのですが、";
		mes "このところ急にラザーニャ周辺で";
		mes "問題を起こすようになって、";
		mes "悩みの種になっています。";
		next;
		mes "[ペロン団長]";
		mes "こいつは昨日、街の中に入って";
		mes "暴れようとしていたので、";
		mes "我々で捕まえたんですが……";
		mes "ご覧の通り、何も喋らないんです。";
		next;
		mes "[ペロン団長]";
		mes "そこで、あなたに取ってきてもらった";
		mes "トゲの生えた枝を使います。";
		mes "まずはその枝を";
		mes "ジンドウに渡してください。";
		close2;
		setquest 98418;
		set DORAM_1QUE,30;
		end;
	case 30:
		mes "[ペロン団長]";
		mes "まずはその枝を";
		mes "ジンドウに渡してください。";
		close;
	case 31:
		mes "[ペロン団長]";
		mes "さあ、その笛を使って";
		mes "バジルリスクの口を";
		mes "割ってください。";
		next;
		mes "‐トゲの笛を使って……‐";
		next;
		if(select("吹く","殴る") == 2) {
			mes "‐ボコ！‐";
			misceffect 1, "バジルリスク捕虜#do_tu0";
			next;
			mes "[捕虜のバジルリスク]";
			mes "グハッ！";
			next;
			emotion 23;
			mes "[ペロン団長]";
			mes "ちょ、ちょっと！";
			mes "何してるんですか！";
			mes "手荒な真似はやめてください！";
			close;
		}
		mes "‐ピーピーピー‐";
		next;
		mes "[捕虜のバジルリスク]";
		mes "シャッ!!";
		next;
		mes "‐バジルリスクは笛の音に";
		mes "　反応して威嚇し始めた‐";
		next;
		mes "‐トゲの笛を使って……‐";
		next;
		switch(select("演奏する","吹く","刺す")) {
		case 1:
			break;
		case 2:
			mes "‐ピーピーピー‐";
			next;
			mes "[捕虜のバジルリスク]";
			mes "シャッ!!";
			next;
			mes "‐バジルリスクは威嚇したままだ‐";
			close;
		case 3:
			mes "‐グサ！‐";
			misceffect 4, "バジルリスク捕虜#do_tu0";
			next;
			mes "[捕虜のバジルリスク]";
			mes "イテッ！";
			next;
			emotion 23;
			mes "[ペロン団長]";
			mes "ちょ、ちょっと！";
			mes "何してるんですか！";
			mes "手荒な真似はやめてください！";
			close;
		}
		mes "‐プープーピピーポー♪‐";
		next;
		mes "[捕虜のバジルリスク]";
		mes "シャー!!";
		mes "シャッシャッ!!";
		next;
		mes "‐バジルリスクの頭が";
		mes "　少しずつ壺から出てきた‐";
		next;
		mes "‐トゲの笛を使って……‐";
		next;
		if(select("さらに演奏する","叩く") == 2) {
			mes "‐バン！‐";
			misceffect 3, "バジルリスク捕虜#do_tu0";
			next;
			mes "[捕虜のバジルリスク]";
			mes "アウチッ！";
			next;
			emotion 23;
			mes "[ペロン団長]";
			mes "ちょ、ちょっと！";
			mes "何してるんですか！";
			mes "手荒な真似はやめてください！";
			close;
		}
		mes "‐ピーポーピーポー♪‐";
		next;
		mes "‐バジルリスクが";
		mes "　演奏にあわせて";
		mes "　左右に体をくねらせ始めた‐";
		next;
		mes "[捕虜のバジルリスク]";
		mes "か、体が勝手に……！";
		next;
		mes "[捕虜のバジルリスク]";
		mes "わ、わたしは何も知らない！";
		mes "王様に命令されたとか";
		mes "そんなことは絶対ない！";
		next;
		mes "‐トゲの笛を使って……‐";
		next;
		if(select("演奏し続ける","斬る") == 2) {
			mes "‐ザク！‐";
			misceffect 565, "バジルリスク捕虜#do_tu0";
			next;
			mes "[捕虜のバジルリスク]";
			mes "グフッ！";
			next;
			emotion 23;
			mes "[ペロン団長]";
			mes "ちょ、ちょっと！";
			mes "何してるんですか！";
			mes "手荒な真似はやめてください！";
			close;
		}
		mes "‐ペーペーポーペーペポポー♪‐";
		next;
		mes "‐バジルリスクが";
		mes "　演奏にあわせて";
		mes "　激しく頭を振ったり";
		mes "　体をくねらせ始めた‐";
		next;
		mes "[捕虜のバジルリスク]";
		mes "絶対に言わないぞ！";
		mes "あの洞窟に住んでいる";
		mes "あいつが目的だなんて";
		mes "絶対に言うもんか！";
		next;
		emotion 21;
		mes "[ペロン団長]";
		mes "そこまで！";
		mes "もう十分でしょう。";
		mes "お見事です！";
		next;
		mes "[ペロン団長]";
		mes "バジルリスクは";
		mes "その笛の演奏を聴くと";
		mes "体が勝手に踊り出して";
		mes "なんでも喋ってしまうんです。";
		next;
		mes "[ペロン団長]";
		mes "それではジンドウ、";
		mes "あとはお願いします。";
		next;
		mes "[ジンドウ]";
		mes "わかりました。";
		mes "笛はお預かりします。";
		next;
		mes "[ペロン団長]";
		mes "入団テストは合格です。";
		mes "では戻りましょう。";
		close2;
		delitem 25043, 1;
		delquest 98418;
		getexp 177,2600;
		setquest 98419;
		set DORAM_1QUE,32;
		warp "do_tu02a.gat",235,196;
		end;
	default:
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルから";
		mes "離れてしまいました。";
		mes "進行中のチュートリアルの";
		mes "場所に戻りますか？^000000";
		next;
		if(select("はい","いいえ") == 2) {
			mes "^ff0000【インフォメーション】";
			mes "進行中のチュートリアルの場所が";
			mes "わからなくなった場合、";
			mes "再度話しかけることで";
			mes "チュートリアル進行中のNPCの場所に";
			mes "戻ることができます。^000000";
			close;
		}
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
}

do_tu03a.gat,64,92,3	script	ジンドウ#do_tu03e	10159,{
	if(DORAM_1QUE == 30) {
		delitem 25044, 1;
		getitem 25043, 1;
		set DORAM_1QUE,31;
		mes "[ジンドウ]";
		mes "素晴らしいトゲですね。";
		mes "このトゲをこうやって……";
		mes "さあ、出来ました。";
		next;
		mes "[ジンドウ]";
		mes "この笛を使えば、";
		mes "バジルリスクも喋らずには";
		mes "いられなくなるでしょう。";
		close;
	}
	else if(DORAM_1QUE == 31) {
		mes "[ジンドウ]";
		mes "この笛を使えば、";
		mes "バジルリスクも喋らずには";
		mes "いられなくなるでしょう。";
		close;
	}
	mes "[ジンドウ]";
	mes "ふむ……。";
	close;
}

do_tu03a.gat,61,91,5	script	バジルリスク捕虜#do_tu0	10158,{
	emotion 9;
	mes "[バジルリスク捕虜]";
	mes "……。";
	close;
}

do_tu04a.gat,16,98,0	warp	warp01#do_tu04a	2,2,do_tu02a.gat,355,92
do_tu04a.gat,348,244,0	script	warp02#do_tu04a	45,2,2,{
	if(DORAM_1QUE < 38) {
		mes "‐なにやら危なそうな気がする。";
		mes "　今はまだ先に進むのはやめよう‐";
		close;
	}
	warp "do_tu06a.gat",24,143;
	end;
}

do_tu04a.gat,20,98,0	script	object01#do_tu04a	139,3,3,{
	if(DORAM_1QUE == 27) {
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウには";
		mes "行き先や目標が書いてあります。";
		mes "^ff0000大きなトゲの生えた枝^009effの場所も";
		mes "クエストウィンドウに書いてあるので";
		mes "そこを目指しましょう！^000000";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		close2;
		viewpoint 1, 340, 251, 1, 0xFF0000;
		cutin "do_su_001.bmp", 255;
		end;
	}
	end;
}

do_tu04a.gat,340,251,3	script	大きなトゲの生えた枝#do	111,{
	if(DORAM_1QUE == 27) {
		getitem 25044,1;
		set DORAM_1QUE,28;
		misceffect 5;
		mes "‐大きなトゲの生えた枝を";
		mes "　手に入れた。";
		mes "　ペロン団長のところへ戻ろう‐";
		next;
		if(select("戻る","戻らない") == 2) {
			mes "‐もう少しここに居よう‐";
			close;
		}
		warp "do_tu02a.gat",235,196;
		end;
	}
	else if(DORAM_1QUE == 28) {
		mes "‐ペロン団長のところへ戻ろう‐";
		next;
		if(select("戻る","戻らない") == 2) {
			mes "‐もう少しここに居よう‐";
			close;
		}
		warp "do_tu02a.gat",235,196;
		end;
	}
	mes "‐大きなトゲが生えている枝だ。";
	mes "　怪我をしないように気をつけよう‐";
	close;
OnInit:
	initnpctimer;
	end;
OnTimer2000:
	initnpctimer;
	misceffect 6;
	end;
}

do_tu05a.gat,59,62,0	warp	warp01#do_tu05a	2,2,do_tu02a.gat,205,324
do_tu05a.gat,50,60,0	script	warp02#do_tu05a	45,2,2,{
	if(DORAM_1QUE <= 35) {
		mes "‐「船長室」と書いてある。";
		mes "　まずは食堂に行こう‐";
		close;
	}
	warp "do_tu05a.gat",30,60;
	end;
}

do_tu05a.gat,36,60,0	warp	warp03#do_tu05a	2,2,do_tu05a.gat,54,60
do_tu05a.gat,143,60,0	warp	warp04#do_tu05a	2,2,do_tu05a.gat,165,60
do_tu05a.gat,159,60,0	warp	warp05#do_tu05a	2,2,do_tu05a.gat,138,60
do_tu05a.gat,186,57,3	script	料理長#do_tu05a	548,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 35:
		if(checkquest(98422)) {
			delquest 98422;
			getexp 298,3400;
		}
		mes "[料理長]";
		mes "なんだ？";
		mes "今は忙しいから後にしてくれ。";
		next;
		menu "超大型新人が来てやったぞ！",-;
		misceffect 1, "料理長#do_tu05a";
		emotion 9, "料理長#do_tu05a";
		emotion 23, "甲板長#do_tu05a";
		emotion 23, "操舵手#do_tu05a";
		mes "[料理長]";
		mes "……。";
		next;
		mes "[料理長]";
		mes "ほう……貴様……";
		mes "よっぽど腕に自信があるようだな。";
		mes "良いだろう！";
		mes "俺は売られた喧嘩は買う主義だ！";
		mes "武器を取りな！";
		next;
		emotion 4, "甲板長#do_tu05a";
		mes "[甲板長]";
		mes "おいおいおいマジかよ。";
		next;
		emotion 16, "操舵手#do_tu05a";
		mes "[操舵手]";
		mes "死ぬわアイツ。";
		next;
		emotion 29, "料理長#do_tu05a";
		mes "[料理長]";
		mes "若造が料理長の座を奪おうとは";
		mes "いい度胸だ！";
		mes "この包丁の錆にしてくれるわ！";
		next;
		menu "そんなつもりは……",-;
		mes "[料理長]";
		mes "この期に及んで怖気づいたか！";
		mes "さっきまでの威勢はどうした！";
		next;
		emotion 0, "甲板長#do_tu05a";
		mes "[甲板長]";
		mes "……あれ？";
		next;
		mes "[甲板長]";
		mes "あいつが投げたのは";
		mes "もしかして……？";
		next;
		mes "[甲板長]";
		mes "やっぱり。";
		mes "これ、料理長が注文した";
		mes "カルニャックじゃ？";
		next;
		emotion 0, "料理長#do_tu05a";
		mes "[料理長]";
		mes "何……？";
		next;
		mes "[料理長]";
		mes "……確かにそうだ。";
		mes "どうしてこれを新人のお前が";
		mes "持っている？";
		next;
		mes "‐あなたは船の外で会った";
		mes "　ドラムのことを話した‐";
		next;
		emotion 36, "料理長#do_tu05a";
		mes "[料理長]";
		mes "またあいつか！";
		mes "新人を使い走りにするだけじゃなく";
		mes "こんな悪戯までしやがって！";
		mes "そんなだからいつまで経っても";
		mes "エッグリンと呼ばれ続けるんだ！";
		next;
		mes "[料理長]";
		mes "驚かせてすまなかったな。";
		mes "どうやらうちの船員の";
		mes "悪戯だったようだ。";
		next;
		mes "[料理長]";
		mes "あんたには悪いことをしたな。";
		mes "やつに代わって謝罪させてもらう。";
		next;
		mes "[料理長]";
		mes "後でやつにも謝罪させにいく。";
		mes "トラブルばかり起こして";
		mes "いつまで経っても半人前の";
		mes "問題児なんだ。";
		next;
		emotion 15, "料理長#do_tu05a";
		mes "[料理長]";
		mes "食材を届けてくれてありがとうな。";
		mes "船長なら船内に入ってすぐの";
		mes "船長室にいるから、";
		mes "早く挨拶してきな。";
		close2;
		delitem 25047, 1;
		set DORAM_1QUE,36;
		getexp 332,3600;
		setquest 98424;
		end;
	case 36:
		mes "[料理長]";
		mes "食材を届けてくれてありがとうな。";
		mes "船長なら船内に入ってすぐの";
		mes "船長室にいるから、";
		mes "早く挨拶してきな。";
		close;
	default:
		if(DORAM_1QUE <= 1)
			warp "do_tu01a.gat",29,281;
		else if(DORAM_1QUE <= 24)
			warp "do_tu01a.gat",60,320;
		else if(DORAM_1QUE <= 26)
			warp "do_tu02a.gat",224,124;
		else if(DORAM_1QUE <= 34)
			warp "do_tu02a.gat",235,196;
		else if(DORAM_1QUE <= 37)
			warp "do_tu02a.gat",203,322;
		else
			warp "do_tu05a.gat",26,62;
		end;
	}
}

do_tu05a.gat,122,61,5	script	船員#do_tu05a_01	559,{
	mes "[船員]";
	mes "新大陸は初めてですか？";
	mes "一度も行って見たことない場所に";
	mes "行く気分はどうですか？";
	next;
	mes "[船員]";
	mes "どきどきしませんか？";
	mes "私も初めての時は眠れませんでした。";
	mes "いまだに新大陸に行くときには";
	mes "そう感じます。";
	close;
}

do_tu05a.gat,169,70,3	script	船員#do_tu05a_02	545,{
	mes "[船員]";
	mes "ミッドガルドも発見されたけど、";
	mes "他にもあるかな？";
	mes "地図にもない場所。";
	mes "まだ私たちが行ったこともない場所。";
	mes "";
	close;
}

do_tu05a.gat,166,68,6	script	船員#do_tu05a_03	544,{
	mes "[船員]";
	mes "ステルロー一等航海士なら";
	mes "地図にもない新大陸への航路を";
	mes "また見つけ出しそうな気がする。";
	next;
	mes "[船員]";
	mes "発見の瞬間を自分の目で";
	mes "見るためにも、";
	mes "一日でも長く";
	mes "この船に乗っていなきゃ。";
	close;
}

do_tu05a.gat,181,61,5	script	甲板長#do_tu05a	421,{
	mes "[甲板長]";
	mes "ここの料理長、顔はこええが";
	mes "料理の腕は確かなんだぜ。";
	close;
}

do_tu05a.gat,181,58,3	script	操舵手#do_tu05a	561,{
	mes "[操舵手]";
	mes "エッグリンのやろう。";
	mes "まーたサボってやがるな。";
	close;
}

do_tu05a.gat,26,64,5	script	ガムベリー船長#do_tu05a	10153,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	switch(DORAM_1QUE) {
	case 36:
		delquest 98424;
		getexp 389,3800;
		savepoint "do_tu05a.gat",26,62;
		set DORAM_1QUE,37;
		mes "^009eff【インフォメーション】";
		mes "セーブポイントを更新しました。";
		mes "戦闘不能になった場合、";
		mes "この場所で復活します。^000000";
		next;
	case 37:
		mes "　チュートリアル<実践編>　3/3";
		mes "************************";
		mes "　・新米自警団員の初仕事";
		mes "************************";
		next;
		switch(select("はじめる","このチュートリアルをスキップ","すべてのチュートリアルをスキップする")) {
		case 1:
			break;
		case 2:
			getitem 569, 50;
			delitem 25046, 1;
			setquest 98425;
			delquest 98425;
			getexp 430,4000;
			setquest 98426;
			delquest 98426;
			getexp 475,6000;
			setquest 98427;
			delquest 98427;
			getexp 524,8000;
			setquest 98428;
			delquest 98428;
			getexp 577,10000;
			getitem 19330, 1;
			getitem 28576, 1;
			getitem 15274, 1;
			getitem 22184, 1;
			getitem 12324, 1;
			setquest 98429;
			delquest 98429;
			getexp 0,25000;
			set DORAM_1QUE,100;
			savepoint "lasagna.gat",299,239;
			mes "^009eff【インフォメーション】";
			mes "お疲れ様でした。";
			mes "すべてのチュートリアルが";
			mes "終了しました。";
			mes "この後、港町ラザーニャに";
			mes "移動します。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "序盤は港町ラザーニャにいる";
			mes "自警団員オリオ(座標：323,229)から";
			mes "受けられるクエストを";
			mes "プレイするのがおすすめです。^000000";
			next;
			mes "^009eff【インフォメーション】";
			mes "それではラグナロクオンラインの";
			mes "世界をお楽しみください！^000000";
			close2;
			warp "lasagna.gat",298,238;
			end;
		}
		mes "[ガムベリー船長]";
		mes "誰だね。";
		mes "ここは関係者以外立ち入り禁止だ。";
		mes "早く出ていきなさい。";
		next;
		menu "乗船許可書を渡す",-;
		emotion 33;
		mes "[ガムベリー船長]";
		mes "新しい冒険者か。";
		mes "私はこの船の船長^0000cdガムベリー^000000、";
		mes "隣の彼は一等航海士のステルローだ。";
		mes "君を歓迎しよう。";
		next;
		menu "出航はいつですか？",-;
		mes "[ガムベリー船長]";
		mes "出航か……それなんだが、";
		mes "少し困ったことになっていてね。";
		mes "外を見てくれ。";
		next;
		mes "‐窓から沖の方を見ると、";
		mes "　濃い煙が発生していた‐";
		next;
		mes "[ステルロー]";
		mes "この煙ではまともな航海はできない。";
		mes "視界が晴れるまで船は出せないよ。";
		mes "しかもこれはおそらく……。";
		next;
		mes "[ガムベリー船長]";
		mes "ああ、たぶんあいつだ。";
		next;
		menu "あいつ？",-;
		mes "[ガムベリー船長]";
		mes "^0000ffラビオル森の奥にある洞窟に";
		mes "住んでいる龍^000000だ。";
		mes "そいつが吐く炎が周りを燃やして";
		mes "あの煙になっているんだ。";
		next;
		mes "[ガムベリー船長]";
		mes "普段はおとなしいから";
		mes "なんともないんだが、";
		mes "きっと今は何か問題が";
		mes "起きているんだろう。";
		next;
		mes "[ガムベリー船長]";
		mes "その問題が収まるまで、";
		mes "この煙は晴れないだろうな。";
		next;
		mes "[ステルロー]";
		mes "そして今は手が空いている";
		mes "乗組員がいないんだ。";
		mes "龍の様子を見に行くことも";
		mes "できないし、このまま";
		mes "煙が晴れるのを";
		mes "じっと待つしかないんだ。";
		next;
		menu "自分が行きましょうか？",-;
		mes "[ガムベリー船長]";
		mes "本当かね！";
		mes "それは助かる。";
		next;
		mes "[ガムベリー船長]";
		mes "龍がいるのは^ff0000ラビオル森の";
		mes "北東にある「龍の巣」と呼ばれる";
		mes "洞窟の奥^000000だ。";
		next;
		mes "[ガムベリー船長]";
		mes "あの辺りは最近バジルリスクが";
		mes "暴れているから注意してくれ。";
		mes "ある程度の実力が無いと";
		mes "痛い目に会うぞ。";
		next;
		mes "[ガムベリー船長]";
		mes "ステータスを伸ばしたり、";
		mes "スキルを習得しているか？";
		mes "スキル「かみつく」や「ひっかく」は";
		mes "バジルリスク相手にも有効だ。";
		next;
		cutin "do_su_009.bmp", 3;
		mes "[ガムベリー船長]";
		mes "「かみつく」や「ひっかく」の";
		mes "威力を上げたいなら";
		mes "ステータスの「Str」を上げるんだ。";
		mes "攻撃力が上がって";
		mes "戦いを有利に進められるぞ。";
		next;
		cutin "do_su_002.bmp", 255;
		mes "[ガムベリー船長]";
		mes "もしステータスの割り振りを";
		mes "やり直したいなら、";
		mes "^ff0000ステルロー^000000に言ってくれ。";
		mes "今回に限り、特別にステータスを";
		mes "リセットしてくれるだろう。";
		next;
		mes "[ガムベリー船長]";
		mes "^0000ff洞窟に入ってすぐのところに";
		mes "自警団員がいるはずだ。^000000";
		mes "まずは彼から龍の状態が";
		mes "どうなっているのか確認するんだ。";
		next;
		mes "[ガムベリー船長]";
		mes "そして必要なら彼に協力して、";
		mes "龍が吐く炎を止めてくれ。";
		next;
		mes "[ガムベリー船長]";
		mes "龍の巣の入り口までは……";
		mes "^ff0000ステルロー^000000、君が案内してくれるか。";
		next;
		emotion 33, "ステルロー#do_tu05a";
		mes "[ステルロー]";
		mes "了解です、船長。";
		next;
		mes "[ステルロー]";
		mes "ということだ。";
		mes "準備ができたら俺に声をかけてくれ。";
		next;
		mes "[ガムベリー船長]";
		mes "訓練を終えた新米冒険者の";
		mes "初の実戦だ。";
		mes "気を引き締めて行ってくれ。";
		next;
		mes "[ガムベリー船長]";
		mes "これを渡しておく。";
		mes "危なくなったら使ってくれ。";
		mes "それでは頼んだぞ。";
		next;
		set DORAM_1QUE,38;
		getitem 569, 50;
		delitem 25046, 1;
		setquest 98425;
		mes "^009eff‐ガムベリー船長から";
		mes "　初心者用ポーションを受け取った‐^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "クエスト「新米冒険者の初仕事」を";
		mes "受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		close;
	case 38:
	case 39:
	case 40:
	case 41:
		mes "[ガムベリー船長]";
		mes "龍がいるのは^ff0000ラビオル森の";
		mes "北東にある洞窟の奥^000000だ。";
		mes "あの辺りは最近バジルリスクが";
		mes "暴れているから注意してくれ。";
		next;
		mes "[ガムベリー船長]";
		mes "^0000ff洞窟に入ってすぐのところに";
		mes "自警団員がいるはずだ。^000000";
		mes "まずは彼から龍の状態が";
		mes "どうなっているのか確認するんだ。";
		next;
		mes "[ガムベリー船長]";
		mes "洞窟の入り口までは";
		mes "ステルローに案内させよう。";
		mes "準備が整ったら出発してくれ。";
		next;
		mes "[ステルロー]";
		mes "ということだ。";
		mes "準備ができたら俺に声をかけてくれ。";
		close;
	case 42:
		cloakoffnpc "甲板長#do_tu05a_2";
		cloakoffnpc "操舵手#do_tu05a_2";
		cloakoffnpc "ステルロー#do_tu05a";
		mes "[ガムベリー船長]";
		mes "おお、無事だったか。";
		mes "なかなか帰って来ないから";
		mes "誰かを様子見に行かせようと";
		mes "していたところだ。";
		next;
		mes "[ガムベリー船長]";
		mes "で、どうだった？";
		mes "問題は解決したのか？";
		next;
		menu "タルトゥーフィは落ち着きを取り戻した",-;
		mes "[ガムベリー船長]";
		mes "そうか、バジルリスクのせいで";
		mes "タルトゥーフィが暴れていたのか……。";
		next;
		mes "[ガムベリー船長]";
		mes "だが、君が言った通りなら";
		mes "もうしばらくすれば";
		mes "煙も晴れてくるはずだが……。";
		next;
		emotion 0, "ステルロー#do_tu05a";
		mes "[ステルロー]";
		mes "船長！";
		mes "外を見てください！";
		next;
		mes "[ガムベリー船長]";
		mes "おおお……";
		mes "煙が……。";
		next;
		mes "‐沖に充満していた濃い煙が";
		mes "　薄れていき……";
		musiceffect "149";
		mes "　真っ青な海と水平線が";
		mes "　姿を現した‐";
		next;
		mes "[ガムベリー船長]";
		mes "……";
		mes "……こうしちゃいられん。";
		next;
		emotion 27, "ガムベリー船長#do_tu05a";
		mes "[ガムベリー船長]";
		mes "ステルロー！　各員に伝達！";
		mes "出航の準備だ！";
		next;
		emotion 21, "ステルロー#do_tu05a";
		mes "[ステルロー]";
		mes "了解！";
		next;
		mes "[ステルロー]";
		mes "各員に伝達！";
		mes "沖の煙は晴れた！";
		mes "ただちに出航の準備に移れ！";
		next;
		emotion 27, "ステルロー#do_tu05a";
		mes "[ステルロー]";
		mes "操舵手と甲板長！";
		mes "いつまでも油を売ってないで、";
		mes "さっさと持ち場へ戻れ！";
		next;
		emotion 29, "甲板長#do_tu05a_2";
		mes "[甲板長]";
		mes "へいへーいっと！";
		next;
		emotion 32, "操舵手#do_tu05a_2";
		mes "[操舵手]";
		mes "ったく、待ちわびたぜ！";
		next;
		mes "[ガムベリー船長]";
		mes "さあ、忙しくなるぞ。";
		mes "これまでの遅れを取り戻すんだ！";
		next;
		misceffect 119, "ガムベリー船長#do_tu05a";
		mes "[ガムベリー船長]";
		mes "てめえら！";
		mes "気合入れて取り掛かれ！";
		donpcevent "ステルロー#do_tu05a::OnTalk1";
		donpcevent "甲板長#do_tu05a::OnTalk1";
		donpcevent "操舵手#do_tu05a::OnTalk1";
		cloakonnpc "ステルロー#do_tu05a";
		cloakonnpc "甲板長#do_tu05a_2";
		cloakonnpc "操舵手#do_tu05a_2";
		next;
		menu "いよいよ出航ですか？",-;
		mes "[ガムベリー船長]";
		mes "ああ、だが出航までは";
		mes "もう少し時間がかかるだろう。";
		mes "君は今のうちに一度町に戻って";
		mes "準備を整えて来ると良い。";
		next;
		emotion 29, "ガムベリー船長#do_tu05a";
		mes "[ガムベリー船長]";
		mes "フフフ……";
		mes "久しぶりの船出に";
		mes "少し熱くなってしまったよ。";
		next;
		mes "[ガムベリー船長]";
		mes "こうやって無事に出航できるのも";
		mes "君がタルトゥーフィを";
		mes "鎮めてくれたおかげだ。";
		mes "ありがとう。";
		next;
		mes "[ガムベリー船長]";
		mes "君のその勇気と実力、";
		mes "とても新米の冒険者とは";
		mes "思えないな。";
		mes "超大型新人というのも";
		mes "あながち嘘ではなさそうだ。";
		next;
		menu "それはエッグリンが……",-;
		emotion 18, "ガムベリー船長#do_tu05a";
		mes "[ガムベリー船長]";
		mes "ハッハッハ！";
		mes "まあそう謙遜するな。";
		mes "実際君はそれだけのことをしたんだ。";
		next;
		mes "[ガムベリー船長]";
		mes "おっとそうだった、";
		mes "ペロンのやつから";
		mes "預かっているものがあったんだ。";
		next;
		mes "‐ゴソゴソ‐";
		next;
		mes "[ガムベリー船長]";
		mes "これは一人前の";
		mes "ファルファーレ自警団員に";
		mes "贈られる帽子だ。";
		mes "これを被れるようになって";
		mes "初めて真の自警団員に";
		mes "なったと言えるんだ。";
		next;
		mes "[ガムベリー船長]";
		mes "この船に来る新米自警団員に、";
		mes "頃合いを見て渡して欲しいと";
		mes "頼まれているものなんだが……";
		mes "こんなに早くその時が来るとは";
		mes "思いも寄らなかったよ。";
		next;
		mes "[ガムベリー船長]";
		mes "さあ、これを受け取ったら";
		mes "町へ戻って準備をしてきてくれ。";
		mes "その帽子を自慢し過ぎて";
		mes "遅刻しないように。";
		mes "あまり遅いと置いて行って";
		mes "しまうかもしれんぞ。ハッハッハ！";
		close2;
		misceffect 42,"";
		misceffect 91,"";
		misceffect 68,"";
		getitem 19330, 1;
		getitem 28576, 1;
		getitem 15274, 1;
		getitem 22184, 1;
		getitem 12324, 1;
		delquest 98429;
		set DORAM_1QUE,100;
		getexp 0,25000;
		savepoint "lasagna.gat",299,239;
	case 100:
		mes "^009eff【インフォメーション】";
		mes "お疲れ様でした。";
		mes "すべてのチュートリアルが";
		mes "終了しました。";
		mes "この後、港町ラザーニャに";
		mes "移動します。^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "序盤は港町ラザーニャにいる";
		mes "自警団員オリオ(座標：323,229)から";
		mes "受けられるクエストを";
		mes "プレイするのがおすすめです。^000000";
		next;
		mes "^009eff【インフォメーション】";
		mes "それではラグナロクオンラインの";
		mes "世界をお楽しみください！^000000";
		close2;
		warp "lasagna.gat",298,238;
		end;
	}
}

do_tu05a.gat,24,62,5	script	ステルロー#do_tu05a	10156,{
	if(DORAM_1QUE < 38) {
		mes "[ステルロー]";
		mes "俺はステルロー。";
		mes "この船の航海士をやっている。";
		close;
	}
	if(DORAM_1QUE >= 42) {
		mes "[ステルロー]";
		mes "無事だったようだな。";
		close;
	}
	mes "[ステルロー]";
	mes "準備ができたら出発するぞ。";
	next;
	switch(select("出発する","ステータスを振り直したい","ちょっと待って")) {
	case 1:
		mes "[ステルロー]";
		mes "洞窟の入り口まで";
		mes "案内してやる。";
		mes "準備はいいな？";
		next;
		if(select("出発する","ちょっと待って") == 2) {
			mes "[ステルロー]";
			mes "俺もあまり暇じゃないんだ。";
			mes "さっさと準備してくれよ。";
			close;
		}
		mes "[ステルロー]";
		mes "よし、行くぞ。";
		close2;
		warp "do_tu04a.gat",343, 244;
		end;
	case 2:
		mes "[ステルロー]";
		mes "ほらよ。";
		mes "ステータスを";
		mes "リセットしておいたぜ。";
		resetstatus;
		unequip -1;
		next;
		mes "^009eff【インフォメーション】";
		mes "装備アイテムがすべて外され、";
		mes "ステータス取得状況が";
		mes "リセットされました。^000000";
		close;
	case 3:
		mes "[ステルロー]";
		mes "俺もあまり暇じゃないんだ。";
		mes "さっさと準備してくれよ。";
		close;
	}
OnTalk1:
	unittalk "ステルロー : アイアイサー！";
	end;
}

do_tu05a.gat,30,57,0	script	object01#do_tu05a	139,11,11,{
	if(DORAM_1QUE == 42) {
		cloakoffnpc "甲板長#do_tu05a_2";
		cloakoffnpc "操舵手#do_tu05a_2";
	}
	end;
}

do_tu05a.gat,22,60,5	script	甲板長#do_tu05a_2	421,{
	mes "[甲板長]";
	mes "時間が経ち過ぎると";
	mes "積み荷が駄目になっちまうからな。";
	mes "早く何とかしてほしいもんだぜ。";
	close;
OnTalk1:
	unittalk "甲板長 : アイアイサー！";
	end;
OnInit:
	cloakonnpc;
	end;
}

do_tu05a.gat,21,56,3	script	操舵手#do_tu05a_2	561,{
	mes "[操舵手]";
	mes "いつになったら";
	mes "出航できるのかねえ。";
	close;
OnTalk1:
	unittalk "操舵手 : アイアイサー！";
	end;
OnInit:
	cloakonnpc;
	end;
}

do_tu06a.gat,18,143,0	warp	warp01#do_tu06a	2,2,do_tu04a.gat,344,243
do_tu06a.gat,29,146,5	script	自警団員#do_tu06a	10162,5,5,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	if(DORAM_1QUE == 38) {
		if(checkquest(98425)) {
			delquest 98425;
			getexp 430,4000;
		}
		mes "[自警団員]";
		mes "おや、新米の冒険者さんが";
		mes "こんなところに何の用ですか？";
		next;
		mes "‐あなたはラザーニャの海で";
		mes "　起こっていることを伝えた‐";
		next;
		emotion 5;
		mes "[自警団員]";
		mes "へ～なるほど。";
		mes "そんなことが起きてたんですね。";
		mes "やけにさっきから煙たいと";
		mes "思っていたらそういうことでしたか。";
		next;
		mes "[自警団員]";
		mes "それでは、一緒に様子を";
		mes "見に行きましょうか。";
		next;
		if(select("はい","ラザーニャに戻りたい") == 2) {
			mes "[自警団員]";
			mes "あれ？";
			mes "忘れ物ですか？";
			mes "私はここにいるので";
			mes "早く取って来てくださいね。";
			close2;
			warp "do_tu05a.gat",26, 62;
			end;
		}
		mes "[自警団員]";
		mes "目指す場所はここです。";
		mes "迷っても大丈夫なように、";
		mes "地図に印をつけておきました。";
		mes "さあ、行きましょう。";
		viewpoint 1, 157, 98, 1, 0xFF0000;
		close2;
		setquest 98426;
		set DORAM_1QUE,39;
		end;
	}
	if(DORAM_1QUE == 39) {
		mes "[自警団員]";
		mes "やけにさっきから煙たいと";
		mes "思っていたらそういうことでしたか。";
		mes "それでは、一緒に様子を";
		mes "見に行きましょうか。";
		next;
		if(select("はい","ラザーニャに戻りたい") == 2) {
			mes "[自警団員]";
			mes "あれ？";
			mes "忘れ物ですか？";
			mes "私はここにいるので";
			mes "早く取って来てくださいね。";
			close2;
			warp "do_tu05a.gat",26, 62;
			end;
		}
		mes "[自警団員]";
		mes "目指す場所はここです。";
		mes "迷っても大丈夫なように、";
		mes "地図に印をつけておきました。";
		mes "さあ、行きましょう。";
		viewpoint 1, 157, 98, 1, 0xFF0000;
		close;
	}
	mes "^ff0000【インフォメーション】";
	mes "進行中のチュートリアルから";
	mes "離れてしまいました。";
	mes "進行中のチュートリアルの";
	mes "場所に戻りますか？^000000";
	next;
	if(select("はい","いいえ") == 2) {
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルの場所が";
		mes "わからなくなった場合、";
		mes "再度話しかけることで";
		mes "チュートリアル進行中のNPCの場所に";
		mes "戻ることができます。^000000";
		close;
	}
	if(DORAM_1QUE <= 1)
		warp "do_tu01a.gat",29,281;
	else if(DORAM_1QUE <= 24)
		warp "do_tu01a.gat",60,320;
	else if(DORAM_1QUE <= 26)
		warp "do_tu02a.gat",224,124;
	else if(DORAM_1QUE <= 34)
		warp "do_tu02a.gat",235,196;
	else if(DORAM_1QUE <= 37)
		warp "do_tu02a.gat",203,322;
	else
		warp "do_tu05a.gat",26,62;
	end;
OnTouch:
	// dummy
	end;
OnTouchNPC:
	warp "Random",0,0;
	end;
}

do_tu06a.gat,153,103,3	script	自警団員#do_tu06a_2	10162,5,5,{
	if(distance(getcharid(3)) > 5) {
		showmessage "‐もっと近づいてから話しかけよう‐","";
		end;
	}
	if(DORAM_1QUE == 39) {
		if(checkquest(98426)) {
			delquest 98426;
			getexp 475,6000;
		}
		mes "[自警団員]";
		mes "迷わず来れましたね。";
		mes "この先にこの洞窟の龍、";
		mes "^ff0000タルトゥーフィ^000000がいます。";
		next;
		mes "[自警団員]";
		mes "おとなしいやつなので";
		mes "襲ってくるようなことは";
		mes "無いと思いますが、";
		mes "一応気を付けておいてください。";
		mes "それでは進みましょう。";
		next;
		if(select("はい","ラザーニャに戻りたい") == 2) {
			mes "[自警団員]";
			mes "あれ？";
			mes "忘れ物ですか？";
			mes "私はここにいるので";
			mes "早く取って来てくださいね。";
			close2;
			warp "do_tu05a.gat",26, 62;
			end;
		}
		if(!checkquest(98427))
			setquest 98427;
		warp "do_tu07a.gat",190,20;
		end;
	}
	mes "^ff0000【インフォメーション】";
	mes "進行中のチュートリアルから";
	mes "離れてしまいました。";
	mes "進行中のチュートリアルの";
	mes "場所に戻りますか？^000000";
	next;
	if(select("はい","いいえ") == 2) {
		mes "^ff0000【インフォメーション】";
		mes "進行中のチュートリアルの場所が";
		mes "わからなくなった場合、";
		mes "再度話しかけることで";
		mes "チュートリアル進行中のNPCの場所に";
		mes "戻ることができます。^000000";
		close;
	}
	if(DORAM_1QUE <= 1)
		warp "do_tu01a.gat",29,281;
	else if(DORAM_1QUE <= 24)
		warp "do_tu01a.gat",60,320;
	else if(DORAM_1QUE <= 26)
		warp "do_tu02a.gat",224,124;
	else if(DORAM_1QUE <= 34)
		warp "do_tu02a.gat",235,196;
	else if(DORAM_1QUE <= 37)
		warp "do_tu02a.gat",203,322;
	else
		warp "do_tu05a.gat",26,62;
	end;
OnTouch:
	// dummy
	end;
OnTouchNPC:
	warp "Random",0,0;
	end;
}

do_tu07a.gat,190,15,0	warp	warp01#do_tu07a	2,2,do_tu06a.gat,153,98
do_tu07a.gat,190,20,0	script	object01#do_tu07a	139,4,4,{
	if(DORAM_1QUE == 39) {
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウには";
		mes "行き先や目標が書いてあります。";
		mes "^ff0000タルトゥーフィ^009effの場所も";
		mes "クエストウィンドウに書いてあるので";
		mes "そこを目指しましょう！^000000";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストウィンドウは";
		mes "アイコンを左クリックするか";
		mes "^ff0000<Alt>キー+<U>キー^009effで";
		mes "開くことができます。^000000";
		close2;
		viewpoint 1, 162, 158, 1, 0xFF0000;
		cutin "do_su_001.bmp", 255;
		end;
	}
	end;
}

do_tu07a.gat,159,156,5	script	自警団員#do_tu07a	10162,5,5,{
	if(DORAM_1QUE < 42) {
		mes "[自警団員]";
		mes "だいぶバジルリスクが増えたな……。";
		next;
		if(select("はい","ラザーニャに戻りたい") == 2) {
			mes "[自警団員]";
			mes "あれ？";
			mes "忘れ物ですか？";
			mes "私はここにいるので";
			mes "早く取って来てくださいね。";
			close2;
			warp "do_tu05a.gat",26, 62;
			end;
		}
		mes "[自警団員]";
		mes "何かにつけて";
		mes "問題を起こすやつらなので、";
		mes "自警団でも頭を悩ませています。";
		close;
	}
	mes "[自警団員]";
	mes "お疲れ様。";
	mes "私は入口に戻るよ。";
	next;
	mes "[自警団員]";
	mes "その^ff0000初心者用蝶の羽^000000を";
	mes "使えば君も町に戻れるだろう。";
	close;
OnTouch:
	// dummy
	end;
OnTouchNPC:
	warp "Random",0,0;
	end;
}

do_tu07a.gat,162,158,3	script	タルトゥーフィ#do_tu07a	10161,5,5,{
	if(DORAM_1QUE == 39) {
		if(checkquest(98427)) {
			delquest 98427;
			getexp 524,8000;
		}
		emotion 6, "タルトゥーフィ#do_tu07a";
		mes "[タルトゥーフィ]";
		mes "ええい、";
		mes "騒がしいやつらだな。";
		mes "僕になんの恨みがあるんだ。";
		next;
		mes "[タルトゥーフィ]";
		mes "お父さん、";
		mes "お母さん、";
		mes "会いたいよ……。";
		next;
		mes "‐大きな龍が何が呟いている‐";
		next;
		emotion 0, "タルトゥーフィ#do_tu07a";
		mes "[タルトゥーフィ]";
		mes "ん？　誰？";
		mes "初めて見る顔だね。";
		next;
		mes "[自警団員]";
		mes "やあタルトゥーフィ。";
		mes "彼は新米の冒険者だ。";
		mes "船でミッドガルド大陸に";
		mes "行こうとしたら、";
		mes "君が吐く炎の煙のせいで";
		mes "船が出港できないらしい。";
		next;
		mes "[タルトゥーフィ]";
		mes "あ、それはごめんね。";
		mes "だけどそれは^ff0000バジルリスクの";
		mes "せい^000000なんだ。";
		next;
		mes "[タルトゥーフィ]";
		mes "これまではたまにちょっかいを";
		mes "出してくるだけだったのに、";
		mes "この前から突然";
		mes "それが激しくなったんだ。";
		next;
		mes "[自警団員]";
		mes "そういえば最近、";
		mes "バジルリスクが荒れてるね。";
		mes "何かしたのかい？";
		next;
		mes "[タルトゥーフィ]";
		mes "僕は何もしてないよ。";
		mes "「仲間の恨み！」とか言ってたから、";
		mes "あいつらの仲間が";
		mes "何かされたんじゃないかな。";
		mes "捕まって酷い目にあったとか。";
		next;
		mes "[自警団員]";
		mes "なるほど……。";
		mes "君は何か知っているかい？";
		next;
		menu "いいえ",-,"知りません",-,"心当たりはありません",-;
		mes "[自警団員]";
		mes "そうだよな。";
		mes "冒険者になりたての君が";
		mes "知っているわけないよな。";
		next;
		mes "[タルトゥーフィ]";
		mes "まあ、そんなわけで、";
		mes "僕だってやりたくて";
		mes "やってるわけじゃないんだ。";
		next;
		emotion 0, "タルトゥーフィ#do_tu07a";
		mes "[タルトゥーフィ]";
		mes "そうだ！";
		mes "君たちでこの周りにいる";
		mes "バジルリスクを懲らしめてよ。";
		mes "あいつらが大人しくなれば";
		mes "僕も炎を吐かずに済むからさ。";
		next;
		mes "[タルトゥーフィ]";
		mes "うーん、そうだな。";
		mes "^ff0000偵察バジルリスクを5体^000000も";
		mes "退治してくれば十分かな。";
		mes "お願いね。";
		next;
		cutin "do_su_002.bmp", 3;
		mes "^009eff【インフォメーション】";
		mes "クエストを受注しました。";
		mes "クエストウィンドウを開いて";
		mes "確認してみましょう！^000000";
		setquest 98428;
		set DORAM_1QUE,40;
		close2;
		cutin "do_su_002.bmp", 255;
		end;
	}
	if(DORAM_1QUE == 40 || DORAM_1QUE == 41) {
		if(!(checkquest(98428) & 0x4)) {
			mes "[タルトゥーフィ]";
			mes "君たちでこの周りにいる";
			mes "バジルリスクを懲らしめてよ。";
			mes "あいつらが大人しくなれば";
			mes "僕も炎を吐かずに済むからさ。";
			next;
			mes "[タルトゥーフィ]";
			mes "うーん、そうだな。";
			mes "^ff0000偵察バジルリスクを5体^000000も";
			mes "退治してくれば十分かな。";
			mes "お願いね。";
			next;
			cutin "do_su_002.bmp", 3;
			mes "^009eff【インフォメーション】";
			mes "クエストを受注しました。";
			mes "クエストウィンドウを開いて";
			mes "確認してみましょう！^000000";
			close2;
			cutin "do_su_002.bmp", 255;
			end;
		}
		mes "[タルトゥーフィ]";
		mes "ようやく静かになったみたい。";
		mes "ありがとう。";
		mes "これであいつらもしばらくは";
		mes "おとなしくしてるかな。";
		next;
		mes "[自警団員]";
		mes "新米冒険者と聞いていたけど";
		mes "なかなかの腕だね。";
		mes "もう一人前の冒険者だよ。";
		next;
		mes "[タルトゥーフィ]";
		mes "君はミッドガルド大陸に";
		mes "行くんだよね？";
		mes "たまには帰って来て、";
		mes "向こうの話を聞かせてほしいな。";
		next;
		mes "[タルトゥーフィ]";
		mes "僕はもう少し大きくなるまで";
		mes "ここにいないといけないんだ。";
		mes "自由な君がうらやましいよ。";
		next;
		mes "[タルトゥーフィ]";
		mes "短い間だったけどありがとう。";
		mes "帰るならこれを使いなよ。";
		next;
		mes "‐タルトゥーフィから";
		mes "　何かを渡された‐";
		next;
		if(DORAM_1QUE == 40) {
			getitem 12324, 1;
			set DORAM_1QUE,41;
		}
		mes "[タルトゥーフィ]";
		mes "これは^ff0000初心者用蝶の羽^000000だ。";
		mes "使うと位置セーブされたところまで";
		mes "移動することができるんだ。";
		next;
		mes "^009eff【インフォメーション】";
		mes "位置セーブポイントは";
		mes "特定のNPCから設定することが";
		mes "できます。";
		mes "現在の位置セーブポイントは";
		mes "ガムベリー船長の前になっています。^000000";
		next;
		mes "[タルトゥーフィ]";
		mes "ほんとうは僕が送ってあげたいけど、";
		mes "いつバジルリスクがやってくるか";
		mes "わからないから……。";
		mes "代わりにそれを使ってよ。";
		mes "それじゃあまたね。";
		close2;
		delquest 98428;
		set DORAM_1QUE,42;
		getexp 577,10000;
		setquest 98429;
		end;
	}
	mes "[タルトゥーフィ]";
	mes "君はミッドガルド大陸に";
	mes "行くんだよね？";
	mes "たまには帰って来て、";
	mes "向こうの話を聞かせてほしいな。";
	close;
OnTouch:
	// dummy
	end;
OnTouchNPC:
	warp "Random",0,0;
	end;
}

do_tu07a.gat,247,194,0	script	object02#do_tu07a	139,{}

do_tu02a.gat,226,181,3	script	カルルー#do_tu02a	548,{
	mes "[カルルー]";
	mes "カルーニャミルクの";
	mes "主な材料を知っているか？";
	mes "カルーニャという特別な貝を";
	mes "発酵させて作ったエッセンスと";
	mes "新鮮な牛乳で作られている。";
	next;
	mes "[カルルー]";
	mes "それを適切な量で混ぜる。";
	mes "そこにニャンダレの実を一緒に";
	mes "添えるとみんなが愛する";
	mes "カルーニャミルクになるんだ。";
	close;
}

do_tu02a.gat,225,290,5	script	作業班長#do_tu02a	421,{
	mes "[作業班長]";
	mes "この仕事をやったことある？";
	mes "すぐに覚えられる簡単な事だ。";
	mes "コンキリナ号のガムベリー船長は";
	mes "特に上手かったな。";
	close;
}

do_tu02a.gat,139,299,3	script	イワシ漁船船長#do_tu02a	561,{
	mes "[イワシ漁船船長]";
	mes "イワシ産業が";
	mes "以前より落ち込んでいても";
	mes "人手は常に不足している。";
	close;
}

do_tu02a.gat,263,156,5	script	おばあちゃん#do_tu02a	554,{
	mes "[おばあちゃん]";
	mes "昔のラザーニャは凄かった。";
	mes "道も住民もボロボロ。";
	mes "当時は暗黒期と呼ばれているよ。";
	next;
	mes "[おばあちゃん]";
	mes "ある時、何の遊びなのかしらないが、";
	mes "悪がきどもが";
	mes "他のチンピラたちを更生させる、と";
	mes "無理やり自分たちが作った自警団や";
	mes "猫の手サービスに入れ始めたんだ。";
	next;
	mes "[おばあちゃん]";
	mes "更生したくない奴らは";
	mes "みんなラザーニャを去り、";
	mes "新しい人生を歩んでみたい";
	mes "やつだけが残った。";
	mes "今のラザーニャは";
	mes "全部あの子たちが作ったんだ。";
	close;
}

do_tu02a.gat,244,231,3	script	イワシ漁船員#do_tu02a	544,{
	mes "[イワシ漁船員]";
	mes "この黄色いチーズ道に沿って";
	mes "歩いて行けば、";
	mes "私たちの故郷が現れる。";
	mes "いつかは戻りたい。";
	close;
}

do_tu02a.gat,260,134,3	script	ラスムス#do_tu02a	546,{
	mes "[ラスムス]";
	mes "赤い毛糸は君が行きたい場所に";
	mes "連れていってくれるし、";
	mes "黄色い道は君を家に";
	mes "連れていってくれる。";
	mes "道に迷ったら赤い毛糸に";
	mes "ついて行けばいい。";
	close;
}

do_tu02a.gat,141,166,5	script	クルメ#do_tu02a	555,{
	mes "[クルメ]";
	mes "道を歩いていると悟ることがある。";
	mes "この世界のどこからでも";
	mes "ミートソースの匂いが";
	mes "するということを。";
	close;
}

do_tu02a.gat,233,174,5	script	酔っ払い#do_tu02a_01	561,{
	mes "[飲み手]";
	mes "カルーニャミルクは";
	mes "ゆっくり混ぜてから飲まなきゃ。";
	mes "最近ここに来た流れ者たちは";
	mes "振って飲んでいるみたいだけど、";
	mes "それはお子ちゃまのやることさ。";
	close;
}

do_tu02a.gat,236,173,3	script	酔っ払い#do_tu02a_02	561,{
	mes "[飲み手]";
	mes "カルーニャミルクは";
	mes "よく振ってから飲むのが一番だ。";
	mes "発酵されたカルーニャが";
	mes "牛乳と混ざることで作り出される";
	mes "繊細な味を感じることができる。";
	close;
}

do_tu02a.gat,200,278,5	script	心配そうなドラム#do_tu0	559,{
	emotion 54;
	mes "[心配そうなドラム]";
	mes "最近、不法にイワシを獲る漁船に";
	mes "騙されて乗せられるドラムが";
	mes "多いらしい。怖い世の中になったね。";
	mes "自警団が本気になって";
	mes "探しまわっているらしいですよ。";
	close;
}

do_tu02a.gat,202,276,5	script	浮かれたドラム#do_tu02a	560,{
	emotion 18;
	mes "[浮かれたドラム]";
	mes "やった！";
	mes "豪華クルーズ旅行が当たったぞ！";
	mes "なんて運が良いんだ！";
	mes "早く集合場所の";
	mes "イワシ漁船前に行かなきゃ！";
	close;
}

do_tu02a.gat,209,301,3	script	ムスタチ#do_tu02a	10167,{
	mes "[ムスタチ]";
	mes "新大陸に旅立つ前に";
	mes "身だしなみを整えてみては？";
	close;
}

do_tu02a.gat,236,179,5	script	ニャンクン#do_tu02a	10163,{
	mes "[ニャンクン]";
	mes "困った事があるなら";
	mes "自警団に頼んでみたら？";
	close;
}

do_tu02a.gat,229,197,5	script	トス#do_tu02a	10164,{
	emotion 22;
	mes "[トス]";
	mes "やはり有名な場所だから人が多いな。";
	close;
}

do_tu02a.gat,228,193,5	script	ポルト#do_tu02a	10163,{
	emotion 32;
	mes "[ポルト]";
	mes "ここに来たなら";
	mes "カルーニャミルクは";
	mes "飲んでおかないとな！";
	close;
}

do_tu02a.gat,226,196,5	script	アラム#do_tu02a	10166,{
	emotion 7;
	mes "[アラム]";
	mes "きょろきょろしないの！";
	mes "田舎者丸出しじゃない！";
	close;
}

do_tu02a.gat,227,187,1	script	ヴォンゴロ#do_tu02a	544,{
	mes "[ヴォンゴロ]";
	mes "こんにちは。";
	mes "パブ「オーブン」へようこそ。";
	mes "注文は決まりましたか？";
	next;
	mes "[ヴォンゴロ]";
	mes "ペロン団長、ガムベリー船長、";
	mes "トーマス船長による";
	mes "「オーブンの誓い」の影響で、";
	mes "みんなカルーニャミルクを";
	mes "注文しますが、一番味に";
	mes "自信のあるのはボスの料理です。";
	next;
	mes "[ヴォンゴロ]";
	mes "白身魚に心を込めて手入れした後、";
	mes "ゆでた豆とイモを";
	mes "混ぜてつぶして形作って";
	mes "揚げたものです。";
	mes "本当に美味しいのに";
	mes "誰も注文しません。";
	next;
	mes "[ヴォンゴロ]";
	mes "だから最近は材料も";
	mes "準備しておかないので、";
	mes "急な注文が入ると、";
	mes "魚屋さんまで走って";
	mes "買いに行くんです。";
	next;
	emotion 54;
	mes "[ヴォンゴロ]";
	mes "あーあ、本当に美味しいのに……。";
	close;
}

do_tu02a.gat,232,187,6	script	フェットゥチーニャ#do_t	545,{
	mes "[フェットゥチーニャ]";
	mes "ここで働いてそれなりに経つけど、";
	mes "未だに下っ端なので皿洗いは";
	mes "すべて私の担当です。";
	next;
	mes "[フェットゥチーニャ]";
	mes "船に乗りに行く前に一杯、";
	mes "長い航海を終えて一杯、";
	mes "各地から訪ねて来た冒険者が一杯、";
	mes "元から飲んでいる人が一杯、";
	mes "周りにつられて飲みだす人が一杯……";
	next;
	mes "[フェットゥチーニャ]";
	mes "とにかく洗わないといけない";
	mes "食器の数が想像を超えます。";
	mes "それだけではありませんよ、";
	mes "自警団と猫の手職員たちの泣き言、";
	mes "新米冒険者たちからの相談等々……";
	next;
	emotion 28;
	mes "[フェットゥチーニャ]";
	mes "24時間じゃ足りないです。";
	mes "従業員を増やせばいいのに！";
	close;
}

do_tu02a.gat,232,181,5	script	リンギュイーネ#do_tu02a	559,{
	mes "[リンギュイーネ]";
	mes "ここは自警団本部ですが、";
	mes "冒険者が立ち寄っていく";
	mes "パブでもあります。";
	mes "各地から押し寄せて来た冒険者が";
	mes "経験談を交わしたり、";
	mes "冒険の仲間を探したりもします。";
	next;
	mes "[リンギュイーネ]";
	mes "最近では新大陸に旅立つ前に";
	mes "情報を仕入れに来る人が増えました。";
	next;
	mes "[リンギュイーネ]";
	mes "十数年前には不良ドラムたちを";
	mes "更生させて自警団に入団させるための";
	mes "場所としても使われました。";
	mes "それ以前は荒くれ者の船乗りたちが";
	mes "一日の疲れを癒す場所だったんです。";
	next;
	mes "[リンギュイーネ]";
	mes "ペロン団長、ガムベリー船長、";
	mes "トーマス船長もここで出会いました。";
	mes "三匹はここで義兄弟の絆を結び、";
	mes "その後の功労でここラザーニャの";
	mes "生きる伝説になりました。";
	next;
	mes "[リンギュイーネ]";
	mes "彼らに憧れてやってくる";
	mes "冒険者も多いんですよ。";
	close;
}

do_tu02a.gat,190,239,5	script	幼いニャンコ#do_tu02a_0	559,{
	unittalk "幼いニャンコ : 私はこの遊び場の隊長だにゃ～。";
	end;
}

do_tu02a.gat,180,230,7	script	幼いニャンコ#do_tu02a_0	560,{
	unittalk "幼いニャンコ : ハァ……こんな幼稚なやつらとは一緒に遊べないにゃ～。";
	end;
}

do_tu02a.gat,192,245,7	script	幼いニャンコ#do_tu02a_0	554,{
	unittalk "幼いニャンコ : 毛玉の塊がひとつ、ななつ、ふたつ、むっつ……多いにゃ!!";
	end;
}

do_tu02a.gat,184,234,5	script	幼いニャンコ#do_tu02a_0	422,{
	unittalk "幼いニャンコ : シーソーに乗りながら一緒に遊びたいやつは集まれ～。";
	end;
}

do_tu02a.gat,186,231,3	script	幼いニャンコ#do_tu02a_0	10167,{
	emotion 28;
	unittalk "幼いニャンコ : これどうして転がらないにゃ～？転がるようにしてにゃ～。";
	end;
}

do_tu02a.gat,211,186,5	script	乗船案内員#do_tu02a	559,{
	mes "[乗船案内員]";
	mes "こんにちは！";
	mes "新大陸に旅立つ船はここから北の";
	mes "船着き場に停泊していますよ。";
	close;
}

do_tu02a.gat,222,187,3	script	ボス#do_tu02a	548,{
	mes "[ボス]";
	mes "なんだ？";
	mes "あんたもカルーニャミルクかい？";
	close;
}

do_tu02a.gat,202,291,3	script	自警団案内員#do_tu02a01	10162,{
	mes "[自警団案内員]";
	mes "港町ラザーニャへようこそ！";
	mes "助けが必要な時は";
	mes "いつでもファルファーレ自警団を";
	mes "訪ねて下さい。";
	close;
}

do_tu02a.gat,174,160,3	script	自警団案内員#do_tu02a02	10162,{
	mes "[自警団案内員]";
	mes "こんにちは。";
	mes "良い天気ですにゃ。";
	close;
}

do_tu02a.gat,233,197,5	script	自警団員オリオ#do_tu02a	10155,{
	mes "[自警団員オリオ]";
	mes "この方はファルファーレ自警団の";
	mes "団長であるペロン様だ！";
	close;
}

do_tu02a.gat,77,263,5	script	タルリー#do_tu02a	10166,{
	mes "[タルリー]";
	mes "早く仕事を仕上げないと……";
	mes "待ち合わせに間に合わないわ。";
	close;
}

do_tu02a.gat,191,174,3	script	ゴルリ#do_tu02a	547,{
	emotion 45;
	mes "[ゴルリ]";
	mes "良い天気だにゃあ。";
	close;
}
