//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  ルーンの依頼
//
//                                                 by Pneuma
//冒険者になりたい   -----------------------------------------

geffen_in.gat,110,28,4	script		オネスト	62,{
	set '@novice, callfunc("AC_GetNovice");
	function show_mission;
	if(AC_QUEST_ST_4==0) goto L_OTHER;
	switch(AC_QUEST_LV_4){
	case 0:
		goto L_QUEST01;
	case 1:
		goto L_QUEST02;
	case 2:
		goto L_QUEST03;
	case 3:
		goto L_QUEST04;
	case 4:
		goto L_QUEST05;
	case 5:
		goto L_QUEST06;
	case 6:
		goto L_QUEST07;
	case 7:
		goto L_QUEST08;
	case 8:
		goto L_QUEST09;
	}
L_QUEST01:
	switch(AC_QUEST_ST_4){
	case 1:
		mes "[オネスト]";
		mes "やあ、君が僕の依頼を";
		mes "受けてくれる冒険者かい？";
		next;
		menu "そうです",-;
		emotion 5;
		mes "[オネスト]";
		mes "やっぱりね！";
		mes "そうだと思ったんだよ。";
		mes "僕は将来冒険者になりたいと";
		mes "思っているから。";
		mes "君の服装をみてピンと来たわけさ。";
		next;
		mes "[オネスト]";
		mes "でもさ、親がうるさくってさ。";
		mes "僕の歳でも色々冒険している人";
		mes "沢山いるのに、";
		mes "勉強しろ勉強しろってね。";
		next;
		mes "[オネスト]";
		mes "それで、冒険者になる為の";
		mes "勉強をしても怒られるし";
		mes "集めた資料だって一度";
		mes "全部捨てられちゃったんだ。";
		next;
		mes "[オネスト]";
		mes "だから、今資料を集めなおしている";
		mes "最中なんだよー。";
		mes "その資料集めの手伝いを";
		mes "君にお願いしたくてね。";
		next;
		mes "[オネスト]";
		mes "というわけでよろしく頼むよー。";
		mes "今回は、";
		mes "ボスモンスターの^FF0000エクリプス^000000が";
		mes "生息しているマップ";
		mes "^0000FFプロンテラフィールド02^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "^0000FFプロンテラフィールド02^000000へは";
		mes "プロンテラから向かうと近かったかな？";
		mes "後、撮影ポイントはメモしといたから";
		mes "その場所で頼むよ。";
		mes "あ、カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFプロンテラフィールド02(305,157)^000000";
		mes "　へ行き写真を撮ってくる‐";
		mes " ";
		mes "^0000FFプロンテラフィールド02^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		next;
		mes "[オネスト]";
		mes "^0000FFプロンテラフィールド02^000000へは";
		mes "プロンテラから向かうと近かったかな？";
		mes "後、撮影ポイントはメモしといたから";
		mes "その場所で頼むよ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFプロンテラフィールド02(305,157)^000000";
		mes "　へ行き写真を撮ってくる‐";
		mes " ";
		mes "^0000FFプロンテラフィールド02^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close;
	case 3:
		emotion 0;
		mes "[オネスト]";
		mes "おお、結構早かったね。";
		mes "ちゃんと写ってるか";
		mes "まだわからないけど、";
		mes "君を見る限りちゃんと";
		mes "撮影してきてくれてるっぽいから";
		mes "これで依頼は終了で良いや。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		mes "[オネスト]";
		if('@novice){
			mes "そうだ、たいした物じゃないけど";
			mes "これをあげるよ。";
			mes "マップを移動するのに楽な";
			mes "アイテムなんだ。";
		}
		mes "それじゃ、また何かあったら";
		mes "よろしくねー。";
		next;
		if('@novice){
			if(!checkweight(601,30)){
				mes "‐重量オーバー‐";
				close;
			}
			getitem 601,30;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "ありがとう！";
		mes "助かったわ。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST02:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 15;
		mes "[オネスト]";
		mes "やあやあ、この前はありがとう。";
		mes "今回もよろしく頼むよ！";
		mes "そういえば名前を";
		mes "聞いてなかったよね？";
		mes "なんていうの君？";
		next;
		menu "名乗る",-;
		mes "[オネスト]";
		mes strcharinfo(0) + "か！";
		mes "僕は、オネストよろしくね！";
		mes "それじゃ、早速内容なんだけど。";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000マスターリング^000000が";
		mes "生息しているマップ";
		mes "^0000FFフェイヨン迷いの森04^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "後、撮影ポイントはこの前と同じく";
		mes "メモしといたから";
		mes "その場所で頼むよ。";
		mes "あ、カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFフェイヨン迷いの森04(267.193)^000000";
		/*「.」で本鯖通り*/mes "に行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFフェイヨン迷いの森04^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000マスターリング^000000が";
		mes "生息しているマップ";
		mes "^0000FFフェイヨン迷いの森04^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFフェイヨン迷いの森04(267.193)^000000";
		/*「.」で本鯖通り*/mes "に行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFフェイヨン迷いの森04^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close;
	case 3:
		mes "[オネスト]";
		mes "さすが";
		mes strcharinfo(0) + "だね。";
		mes "この前の写真もしっかり取れていたし";
		mes "今回のも期待できそうだ。";
		mes "また何かあったらよろしくね。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		if('@novice){
			mes "[オネスト]";
			mes "あ！";
			mes "あと、これもし良かったら";
			mes "もって行ってよ！";
			next;
			switch(Job){
			case Job_Swordman:
			case Job_Thief:
			case Job_Archer:
			case Job_Merchant:
			case Job_TaeKwon:
			case Job_Gunslinger:
				set '@item,2405;
				break;
			// ブーツ[0]
				case Job_Magician:
			case Job_Acolyte:
			case Job_Ninja:
				set '@item,2403;
				break;
			// シューズ[0]
				case Job_SuperNovice:
			default:
				set '@item,2416;
				break;
				// ノービスシューズ[1]
			}
			if(!checkweight('@item,1)){
				mes "‐重量オーバー‐";
				close;
			}
			getitem '@item,1;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "ありがとう！";
		mes "助かったわ。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST03:
	switch(AC_QUEST_ST_4){
	case 1:
		mes "[オネスト]";
		mes "やあ" + strcharinfo(0);
		mes "今回もよろしく頼むよ！";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000ドラゴンフライ^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠18^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "後、撮影ポイントはこの前と同じく";
		mes "メモしといたから";
		mes "その場所で頼むよ。";
		mes "あ、カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠18(232,217)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠18^000000へは";
		mes "　^0000FFモロク^000000から行くのが";
		mes "　良いらしい‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000ドラゴンフライ^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠18^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠18(232,217)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠18^000000へは";
		mes "　^0000FFモロク^000000から行くのが";
		mes "　良いらしい‐";
		close;
	case 3:
		emotion 5;
		mes "[オネスト]";
		mes "ご苦労さまー。";
		mes "これでボスモンスター関連資料が";
		mes "3つになったよ。";
		mes "まだまだ必要になると思うから";
		mes "またよろしくね。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		emotion 5;
		mes "[オネスト]";
		mes "ご苦労さまー。";
		mes "これでボスモンスター関連資料が";
		mes "3つになったよ。";
		mes "まだまだ必要になると思うから";
		mes "またよろしくね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST04:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 0;
		mes "[オネスト]";
		mes strcharinfo(0);
		mes "今回も君が引き受けてくれるんだね。";
		mes "いやー、助かるよ。";
		mes "本当に。";
		mes "それじゃ、早速今回の依頼について";
		mes "説明するね。";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000トード^000000が";
		mes "生息しているマップ";
		mes "^0000FFゲフェンフィールド01^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "後、撮影ポイントはこの前と同じく";
		mes "メモしといたから";
		mes "その場所で頼むよ。";
		mes "あ、カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFゲフェンフィールド01(208,242)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFゲフェンフィールド01^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		next;
		mes "[オネスト]";
		mes "今回の撮影場所は、";
		mes "ボスモンスターの";
		mes "^FF0000トード^000000が";
		mes "生息しているマップ";
		mes "^0000FFゲフェンフィールド01^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFゲフェンフィールド01(208,242)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFゲフェンフィールド01^000000へは";
		mes "　^0000FFプロンテラ^000000から行くのが";
		mes "　良いらしい‐";
		close;
	case 3:
		mes "[オネスト]";
		mes "お疲れ様！";
		mes "いやー、すごいなー。";
		mes "僕も早く冒険者になって";
		mes "色々な場所へ冒険しに行きたい。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		if('@novice){
			emotion 0;
			mes "[オネスト]";
			mes "そうだ！これ！";
			mes "未鑑定のアイテムを鑑定できる";
			mes "拡大鏡なんだけど";
			mes "沢山あるからあげる！";
			mes "僕が持ってても使わないし。";
			next;
			if(!checkweight(611,20)){
				mes "‐重量オーバー‐";
				close;
			}
			getitem 611,20;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "ありがとう！";
		mes "助かったわ。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST05:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 0;
		mes "[オネスト]";
		mes "あ、" + strcharinfo(0);
		mes "君が来てくれるのを";
		mes "心待ちにしていたよ。";
		next;
		emotion 9;
		mes "[オネスト]";
		mes "実は次の撮影場所は";
		mes "凄い危ない場所なんだよね……";
		mes "だから、気をつけて行ってきて";
		mes "ほしいんだ。";
		mes "なんせ、MVPボスモンスターがいる";
		mes "場所だからね。";
		next;
		mes "[オネスト]";
		mes "ということで撮影場所なんだけど、";
		mes "MVPボスモンスターの";
		mes "^FF0000フリオニ^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠17^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "後、撮影ポイントはいつもと同じく";
		mes "メモしといたから";
		mes "その場所で頼むよ。";
		mes "カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠17(146,145)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠17^000000へは";
		mes "　^0000FFモロク^000000から行くのが";
		mes "　良いらしい‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		mes "今回の場所は";
		mes "危険だから気をつけてね。";
		next;
		mes "[オネスト]";
		mes "撮影場所なんだけど、";
		mes "MVPボスモンスターの";
		mes "^FF0000フリオニ^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠17^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠17(146,145)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠17^000000へは";
		mes "　^0000FFモロク^000000から行くのが";
		mes "　良いらしい‐";
		close;
	case 3:
		mes "[オネスト]";
		mes strcharinfo(0) + "！";
		mes "よかった、無事だったんだね。";
		mes "^FF0000フリオニ^000000にやられちゃったん";
		mes "じゃないかと心配していたんだよ。";
		mes "本当によかった。";
		next;
		emotion 20;
		mes "[オネスト]";
		mes "本当にすごいなぁ……";
		mes "僕も" + strcharinfo(0);
		mes "のような冒険者になれるように";
		mes "頑張って勉強しなきゃ。";
		mes "それじゃ、またよろしくね。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		emotion 20;
		mes "[オネスト]";
		mes "本当にすごいなぁ……";
		mes "僕も" + strcharinfo(0);
		mes "のような冒険者になれるように";
		mes "頑張って勉強しなきゃ。";
		mes "それじゃ、またよろしくね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST06:
	switch(AC_QUEST_ST_4){
	case 1:
		mes "[オネスト]";
		mes "こんにちは！";
		mes "今回も来てくれると思ったよ。";
		mes "君のおかげで僕も色々";
		mes "勉強できて、知識だけなら";
		mes "だいぶ付いてきたんじゃないかなと";
		mes "おもっているんだ。";
		next;
		mes "[オネスト]";
		mes "早速撮影場所なんだけど、";
		mes "今回は通常のボスモンスター";
		mes "^FF0000さすらい狼^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠03^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "撮影してほしいのは";
		mes "^0000FFプロンテラ^000000側から入った場所";
		mes "付近かな？";
		mes "だから、ちょっと遠くなっちゃうけど";
		mes "撮影には^0000FFプロンテラ^000000から";
		mes "行ってほしい。";
		next;
		mes "[オネスト]";
		mes "後、撮影ポイントはいつもと同じく";
		mes "メモしといたから";
		mes "その場所で頼むよ。";
		mes "カメラはこれを使ってね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠03(70,336)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠03^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		next;
		mes "[オネスト]";
		mes "早速撮影場所なんだけど、";
		mes "今回は通常のボスモンスター";
		mes "^FF0000さすらい狼^000000が";
		mes "生息しているマップ";
		mes "^0000FFソグラト砂漠03^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFソグラト砂漠03(70,336)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFソグラト砂漠03^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close;
	case 3:
		mes "[オネスト]";
		mes strcharinfo(0);
		mes "遠くまでご苦労様。";
		mes "無事に撮影できてるみたいだね。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		if('@novice){
			emotion 21;
			mes "[オネスト]";
			mes "あと、これスピードアップポーション";
			mes "っていうやつ。";
			mes "攻撃速度が上がるらしいよ。";
			mes strcharinfo(0) + "に";
			mes "あげるよ。";
			next;
			if(!checkweight(645,10)){
				mes "‐重量オーバー‐";
				close;
			}
			getitem 645,10;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "いつもありがとう！";
		mes "本当に助かるわ。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST07:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 0;
		mes "[オネスト]";
		mes strcharinfo(0) + "！";
		mes "いつもありがとう。";
		mes "おかげで沢山の資料を";
		mes "集めることができたよ。";
		next;
		mes "[オネスト]";
		mes "今回もよろしく頼むね！";
		next;
		mes "[オネスト]";
		mes "さて、撮影場所なんだけど、";
		mes "MVPボスモンスター";
		mes "^FF0000オークロード^000000が";
		mes "生息しているマップ";
		mes "^0000FFゲフェンフィールド10^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "凄く危険な場所だから";
		mes "気をつけてね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFゲフェンフィールド10(251,368)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFゲフェンフィールド10^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		mes "今回の場所は";
		mes "危険だから気をつけてね。";
		next;
		mes "[オネスト]";
		mes "撮影場所は";
		mes "MVPボスモンスター";
		mes "^FF0000オークロード^000000が";
		mes "生息しているマップ";
		mes "^0000FFゲフェンフィールド10^000000の";
		mes "写真を撮ってきてほしいんだ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFゲフェンフィールド10(251,368)^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFゲフェンフィールド10^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close;
	case 3:
		emotion 21;
		mes "[オネスト]";
		mes strcharinfo(0);
		mes "おかえり。";
		mes "思ったより早く帰ってきたねー。";
		mes "さすが" + strcharinfo(0);
		mes "だよ。";
		next;
		mes "[オネスト]";
		mes "えっとさ……";
		mes "親に一度、真剣に話してみようと";
		mes "思うんだ。";
		mes "コソコソ資料を集めてても";
		mes "多分そのうちばれてしまうだろうし。";
		next;
		mes "[オネスト]";
		mes strcharinfo(0) + "が";
		mes "撮ってきた写真を見せて";
		mes "真剣に話してみるよ。";
		next;
		menu "がんばってね",-;
		mes "‐オネストにカメラを返した‐";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "えっとさ……";
		mes "親に一度、真剣に話してみようと";
		mes "思うんだ。";
		mes "コソコソ資料を集めてても";
		mes "多分そのうちばれてしまうだろうし。";
		next;
		mes "[オネスト]";
		mes strcharinfo(0) + "が";
		mes "撮ってきた写真を見せて";
		mes "真剣に話してみるよ。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST08:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 0;
		mes "[オネスト]";
		mes "やあ、" + strcharinfo(0);
		mes "君のおかげでかなり";
		mes "資料が揃ってきて";
		mes "僕の知識もかなり付いてきた。";
		mes "最近、";
		mes "魔法の勉強もしだしたんだよ？";
		next;
		mes "[オネスト]";
		mes "やっぱり、魔法がいいよね！";
		mes "僕、マジシャンになって";
		mes "こう、ドカーンとモンスターを";
		mes "一掃してみたんだ。";//みたんだ？でいいのか……？本鯖通り
		next;
		mes "[オネスト]";
		mes "さて、撮影場所なんだけど、";
		mes "MVPボスモンスター";
		mes "^FF0000ストームナイト^000000が";
		mes "生息しているマップ";
		mes "^0000FFおもちゃ工場ダンジョン02^000000";
		mes "の写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "初めてダンジョン内の";
		mes "撮影をお願いするね。";
		mes "モンスターも強力なのが";
		mes "沢山いると思うから";
		mes "気をつけてね。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "[オネスト]";
		mes "^0000FFおもちゃ工場ダンジョン^000000へ行くには";
		mes "まず、^0000FFアルデバラン^000000にいる、";
		mes "^FF0000リンクサンタ^000000に話しかけて";
		mes "^0000FFルティエフィールド^000000に移動する";
		mes "必要があるよ。";
		next;
		mes "[オネスト]";
		mes "そして、^0000FFルティエフィールド^000000を";
		mes "北に行くと街があるんだけども";
		mes "その中にあるはず。";
		mes "それじゃよろしくね！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFおもちゃ工場ダンジョン02^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFおもちゃ工場ダンジョン02^000000へは";
		mes "　^0000FFアルデバラン^000000から向かう‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		mes "今回の場所は";
		mes "危険だから気をつけてね。";
		next;
		mes "[オネスト]";
		mes "^0000FFおもちゃ工場ダンジョン^000000へ行くには";
		mes "まず、^0000FFアルデバラン^000000にいる、";
		mes "^FF0000リンクサンタ^000000に話しかけて";
		mes "^0000FFルティエフィールド^000000に移動する";
		mes "必要があるよ。";
		next;
		mes "[オネスト]";
		mes "そして、^0000FFルティエフィールド^000000を";
		mes "北に行くと街があるんだけども";
		mes "その中にあるはず。";
		mes "それじゃよろしくね！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFおもちゃ工場ダンジョン02^000000";
		mes "へ行き、写真を撮影してくる‐";
		mes " ";
		mes "^0000FFおもちゃ工場ダンジョン02^000000へは";
		mes "　^0000FFアルデバラン^000000から向かう‐";
		close;
	case 3:
		mes "[オネスト]";
		mes strcharinfo(0);
		mes "お疲れ様！";
		mes "おもちゃ工場ダンジョンって";
		mes "聞いただけでワクワクするよね";
		mes "早く現像して写真が見たいよ。";
		next;
		emotion 21;
		mes "[オネスト]";
		mes "後一箇所でとりあえずは、";
		mes "資料が一通り揃うことになるよ。";
		mes "これも、" + strcharinfo(0) + "が";
		mes "頑張ってくれたおかげだよ。";
		mes "少ししたらまた依頼出しておくから";
		mes "よろしくね。";
		next;
		mes "‐オネストにカメラを返した‐";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		emotion 21;
		mes "[オネスト]";
		mes "後一箇所でとりあえずは、";
		mes "資料が一通り揃うことになるよ。";
		mes "これも、" + strcharinfo(0) + "が";
		mes "頑張ってくれたおかげだよ。";
		mes "少ししたらまた依頼出しておくから";
		mes "よろしくね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST09:
	switch(AC_QUEST_ST_4){
	case 1:
		emotion 0;
		mes "[オネスト]";
		mes "やあ、" + strcharinfo(0);
		mes "来てくれたね。";
		mes "それにしても、時がたつのは";
		mes "早いね。";
		mes "君と出会ってからだいぶ";
		mes "たつんじゃないかな？";
		next;
		mes "[オネスト]";
		mes "それじゃ、早速撮影場所なんだけど";
		mes "今回もダンジョンなんだよね。";
		mes "しかも奥深くまで行ってもらわないと";
		mes "いけない。";
		mes "凄く危険な撮影になると思う。";
		next;
		mes "[オネスト]";
		mes "撮影場所は、";
		mes "MVPボスモンスター";
		mes "^FF0000黄金蟲^000000が";
		mes "生息しているマップ";
		mes "^0000FFプロンテラ地下水路4F^000000";
		mes "の写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "アクティブなモンスターも";
		mes "沢山いるし";
		mes "本当に危険だから";
		mes "準備を整えてから向かってね。";
		mes "後、ハエの羽をもっていったほうが";
		mes "いいと思う。";
		next;
		mes "-オネストからカメラを受け取った-";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFプロンテラ地下水路4F^000000へ行き、";
		mes "写真を撮影してくる‐";
		mes " ";
		mes "^0000FFプロンテラ地下水路4F^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close2;
		set AC_QUEST_ST_4,2;
		end;
	case 2:
		mes "[オネスト]";
		mes "ん、もう一度";
		mes "説明したほうがいいのかな？";
		mes "今回の場所は";
		mes "危険だから気をつけてね。";
		next;
		mes "[オネスト]";
		mes "撮影場所は、";
		mes "MVPボスモンスター";
		mes "^FF0000黄金蟲^000000が";
		mes "生息しているマップ";
		mes "^0000FFプロンテラ地下水路4F^000000";
		mes "の写真を撮ってきてほしいんだ。";
		next;
		mes "[オネスト]";
		mes "アクティブなモンスターも";
		mes "沢山いるし";
		mes "本当に危険だから";
		mes "準備を整えてから向かってね。";
		mes "後、ハエの羽をもっていったほうが";
		mes "いいと思う。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "-^0000FFプロンテラ地下水路4F^000000へ行き、";
		mes "写真を撮影してくる‐";
		mes " ";
		mes "^0000FFプロンテラ地下水路4F^000000へは";
		mes "　^0000FFプロンテラ^000000から向かう‐";
		close;
	case 3:
		mes "[オネスト]";
		mes strcharinfo(0);
		mes "無事で戻ってきてくれて";
		mes "本当によかった。";
		mes "今回はさすがに";
		mes "大変だったんじゃない？";
		next;
		if(select("楽だったよ","大変だった")==1){
			emotion 23;
			mes "[オネスト]";
			mes "ええーーっ！";
			mes "実は" + strcharinfo(0) + "は";
			mes "凄い冒険者だったんだね！";
			mes "すごいなぁー。";
			mes "僕も絶対冒険者になって";
			mes "色々冒険するんだ。";
			next;
		}
		else {
			emotion 33;
			mes "[オネスト]";
			mes "そうだよねー。";
			mes "モンスターが沢山いる場所";
			mes "なんだもん。";
			mes "あー、早く僕も冒険者になりたい！";
			next;
		}
		emotion 0;
		mes "[オネスト]";
		mes "あ、そうだ！";
		mes "親が君の撮影してきた写真をみて";
		mes "僕が冒険者になることを";
		mes "認めてくれたんだ！";
		mes "親は僕が撮ってきたと勘違い";
		mes "していたけどもね。";
		next;
		mes "[オネスト]";
		mes strcharinfo(0) + "には";
		mes "凄く悪いんだけど、";
		mes "親には僕が撮影してきたってことに";
		mes "なっているから、";
		mes "それはごめんよ。";
		next;
		menu "気にしないで",-;
		mes "[オネスト]";
		mes "ありがとう……";
		mes "僕が冒険者になったら";
		mes "君とも一緒に冒険してみたいなー。";
		next;
		if('@novice){
			mes "‐オネストにカメラを返し、";
			mes "　アイテムを受け取った‐";
			next;
		}
		else {
			mes "‐オネストにカメラを返した‐";
			next;
		}
		emotion 21;
		mes "[オネスト]";
		mes "何度も手伝ってくれて";
		mes "本当にありがとうね。";
		mes "また、何かあったら";
		mes "冒険者アカデミーの方に";
		mes "依頼をかけさせてもらうから";
		mes "そのときは絶対よろしくね！";
		next;
		if('@novice){
			mes "[オネスト]";
			mes "あ！そうだこれ！";
			mes "イグドラシルの葉っていう";
			mes "アイテムなんだけど";
			mes "倒れている人を助けることが";
			mes "出来るものなんだ。";
			mes "冒険に役立ててよ。";
			next;
			if(!checkweight(610,10)){
				mes "‐重量オーバー‐";
				close;
			}
			getitem 610,10;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_4,99;
		end;
	case 99:
		mes "[オネスト]";
		mes "何度も手伝ってくれて";
		mes "本当にありがとうね。";
		mes "また、何かあったら";
		mes "冒険者アカデミーの方に";
		mes "依頼をかけさせてもらうから";
		mes "そのときは絶対よろしくね！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_OTHER:
	switch(AC_QUEST_LV_4){
	case 0:
		mes "[オネスト]";
		mes "後は、この資料とこの資料が";
		mes "必要かなぁ？";
		close;
	case 1:
	case 2:
		mes "[オネスト]";
		mes "ありがとう！";
		mes "助かったわ。";
		close;
	case 3:
		mes "[オネスト]";
		mes "これでボスモンスター関連資料が";
		mes "3つになったよ。";
		mes "まだまだ必要になると思うから";
		mes "またよろしくね。";
		close;
	case 4:
		mes "[オネスト]";
		mes "ありがとう！";
		mes "助かったわ。";
		close;
	case 5:
		mes "[オネスト]";
		mes "本当にすごいなぁ……";
		mes "僕も" + strcharinfo(0);
		mes "のような冒険者になれるように";
		mes "頑張って勉強しなきゃ。";
		mes "それじゃ、またよろしくね。";
		close;
	case 6:
		mes "[オネスト]";
		mes "いつもありがとう！";
		mes "本当に助かるわ。";
		close;
	case 7:
		mes "[オネスト]";
		mes "えっとさ……";
		mes "親に一度、真剣に話してみようと";
		mes "思うんだ。";
		mes "コソコソ資料を集めてても";
		mes "多分そのうちばれてしまうだろうし。";
		next;
		mes "[オネスト]";
		mes strcharinfo(0) + "が";
		mes "撮ってきた写真を見せて";
		mes "真剣に話してみるよ。";
		close;
	case 8:
		mes "[オネスト]";
		mes "後一箇所でとりあえずは、";
		mes "資料が一通り揃うことになるよ。";
		mes "これも、" + strcharinfo(0) + "が";
		mes "頑張ってくれたおかげだよ。";
		mes "少ししたらまた依頼出しておくから";
		mes "よろしくね。";
		close;
	case 9:
		mes "[オネスト]";
		mes "何度も手伝ってくれて";
		mes "本当にありがとうね。";
		mes "また、何かあったら";
		mes "冒険者アカデミーの方に";
		mes "依頼をかけさせてもらうから";
		mes "そのときは絶対よろしくね！";
		close;
	}
}
prt_fild02.gat,305,157,0		script	#撮影ポイントPRT02	139,5,5,{
	if(AC_QUEST_LV_4!=0) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
pay_fild04.gat,267,193,0		script	#撮影ポイントPAY04	139,5,5,{
	if(AC_QUEST_LV_4!=1) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
moc_fild18.gat,232,217,0		script	#撮影ポイントMOC18	139,5,5,{
	if(AC_QUEST_LV_4!=2) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいのかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
gef_fild01.gat,208,242,0		script	#撮影ポイントGEF01	139,5,5,{
	if(AC_QUEST_LV_4!=3) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
moc_fild17.gat,146,145,0		script	#撮影ポイントMOC17	139,5,5,{
	if(AC_QUEST_LV_4!=4) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
moc_fild03.gat,70,336,0		script	#撮影ポイントMOC03	139,5,5,{
	if(AC_QUEST_LV_4!=5) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
gef_fild09.gat,227,29,4		script	案内板	835,{
	mes "[オークの村]";
	mes "注意！";
	mes "この先はオークが出現します。";
	mes "オークウォリアーやオークレディ、";
	mes "ハイオークなどにご注意ください。";
	mes "また、オークヒーローやオークロード";
	mes "には特にご注意ください。";
	close;
}
gef_fild10.gat,251,368,0		script	#撮影ポイントGEF10	139,5,5,{
	if(AC_QUEST_LV_4!=6) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
xmas_dun02.gat,131,130,0		script	#撮影ポイントXMS02	139,5,5,{
	if(AC_QUEST_LV_4!=7) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
prt_sewb4.gat,100,92,0		script	#撮影ポイントSEW04	139,5,5,{
	if(AC_QUEST_LV_4!=8) end;
	switch(AC_QUEST_ST_4){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "ここで撮影すればいいかな。";
		next;
		mes "‐写真撮影完了‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close2;
		set AC_QUEST_ST_4,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "写真を撮影する必要は無いな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^0000FFゲフェンに戻って";
		mes "^FF0000オネスト^000000に報告しよう‐";
		close;
	}
}
