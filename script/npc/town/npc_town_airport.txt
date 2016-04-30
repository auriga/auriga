//= Athena Script ==============================================================
// Ragnarok Online Airport Script	by Blaze
//= Registry ===================================================================
// $TypingScore -> タイピングハイスコア
// $TypingName$ -> タイピング記録保持者のキャラ名
//==============================================================================

//============================================================
// ガイド職員
//------------------------------------------------------------
-	script	飛行船職員#guide	91,{
	mes "[飛行船職員]";
	mes "こんにちは。";
	mes "当船では、いつも";
	mes "お客様の快適な旅行のために";
	mes "最善を尽くしております。";
	next;
	mes "[飛行船職員]";
	mes "飛行船に乗りたい場合は、";
	mes "こちらの入り口からお入りください。";
	mes "空港を出たい場合は、";
	mes "あちらの階段をお降りください。";
	close;
}

//アインブロック
einbroch.gat,94,267,3	duplicate(飛行船職員#guide)	飛行船職員	91

//ジュノー
yuno.gat,88,263,3	duplicate(飛行船職員#guide)	飛行船職員	91
yuno.gat,14,262,5	duplicate(飛行船職員#guide)	飛行船職員	91

//============================================================
// 空港ゲート内職員
//------------------------------------------------------------
-	script	空港職員#AirportIn	90,{
	mes "[空港職員]";
	mes "こんにちは。";
	mes "我々は、お客様に快適な空の旅を";
	mes "提供できるよう、心掛けております。";
	mes "何をお手伝いいたしましょう？";
	next;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//map以外はダミー
	if('@map$ == "izlude.gat")
		set '@word$,"ジュノー/ラヘル行きの飛行船に乗る";
	else
		set '@word$,"空港に入る";

	if(select('@word$,"取り消し")==1) {
		mes "[空港職員]";
		mes "飛行船の利用料金は1200zenyです。";
		mes "飛行船無料利用券をお持ちの場合は";
		mes "無料でご利用できます。";
		if('@map$ == "izlude.gat")
			mes "飛行船に乗りますか？";
		else
			mes "空港に入りますか？";
		next;
		if(select("はい","いいえ")==1) {
			if(countitem(7311))
				delitem 7311,1;
			else if(Zeny<1200) {
				mes "[空港職員]";
				mes "飛行船の利用料金は";
				mes "1200zenyです。";
				close;
			}
			else {
				set Zeny,Zeny-1200;
			}
			if('@map$ == "izlude.gat")
				warp "airplane_01.gat",244,58;
			else
				warp '@map$,148,51;
			end;
		}
	}
	mes "[空港職員]";
	mes "またのご利用をお待ちしております。";
	close;
}

//アインブロック
airport.gat,126,43,5		duplicate(空港職員#AirportIn)	空港職員	90
airport.gat,143,43,5		duplicate(空港職員#AirportIn)	空港職員	90
airport.gat,158,43,5		duplicate(空港職員#AirportIn)	空港職員	90

//ジュノー
y_airport.gat,126,43,5		duplicate(空港職員#AirportIn)	空港職員	90
y_airport.gat,143,43,5		duplicate(空港職員#AirportIn)	空港職員	90
y_airport.gat,158,43,5		duplicate(空港職員#AirportIn)	空港職員	90

//リヒタルゼン
lhz_airport.gat,126,43,5	duplicate(空港職員#AirportIn)	空港職員	90
lhz_airport.gat,143,43,5	duplicate(空港職員#AirportIn)	空港職員	90
lhz_airport.gat,158,43,5	duplicate(空港職員#AirportIn)	空港職員	90

//イズルード
izlude.gat,206,55,2		duplicate(空港職員#AirportIn)	空港職員	90

//フィゲル
hugel.gat,178,142,0	script	hugelwarp	45,1,1,{
	mes "飛行船に乗るには、";
	mes "飛行船無料利用券か";
	mes "1200Zenyが必要となります。";
	mes "飛行船に乗りますか？";
	next;
	if(select("乗る","乗らない")==2) {
		mes "次回のご利用をお待ちしています。";
		close;
	}
	if(countitem(7311))
		delitem 7311,1;
	else if(Zeny<1200) {
		mes "所持金が足りません";
		mes "飛行船に乗るには";
		mes "1200Zeny必要です。";
		close;
	}
	else
		set Zeny,Zeny-1200;
	warp "airplane.gat",244,58;
	end;
}

//ラヘル
ra_fild12.gat,295,208,0	script	rachelwarp	45,1,1,{
	mes "飛行船に乗るには、";
	mes "飛行船無料利用券か";
	mes "1200Zenyが必要となります。";
	mes "飛行船に乗りますか？";
	next;
	if(select("乗る","乗らない")==2) {
		mes "次回のご利用をお待ちしています。";
		close;
	}
	if(countitem(7311))
		delitem 7311,1;
	else if(Zeny<1200) {
		mes "所持金が足りません";
		mes "飛行船に乗るには";
		mes "1200Zeny必要です。";
		close;
	}
	else
		set Zeny,Zeny-1200;
	warp "airplane_01.gat",245,60;
	end;
}

//============================================================
// 空港ゲート外職員
//------------------------------------------------------------
-	script	空港職員#AirportOut	90,{
	mes "[空港職員]";
	mes "こんにちは。";
	mes "我々は、お客様に快適な空の旅を";
	mes "提供できるよう、心掛けております。";
	mes "何をお手伝いいたしましょう？";
	next;
	if(select("空港から出る","取り消し")==1) {
		mes "[空港職員]";
		mes "一度出てしまうと、再入場の際は";
		mes "ご料金を頂くこととなります。";
		mes "出ますか？";
		next;
		if(select("はい","いいえ")==1) {
			set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//map以外はダミー
			warp '@map$,142,40;
			end;
		}
	}
	mes "[空港職員]";
	mes "またのご利用をお待ちしております。";
	close;
}

//アインブロック
airport.gat,126,51,3		duplicate(空港職員#AirportOut)	空港職員	90
airport.gat,143,49,3		duplicate(空港職員#AirportOut)	空港職員	90
airport.gat,158,50,3		duplicate(空港職員#AirportOut)	空港職員	90

//ジュノー
y_airport.gat,126,51,3		duplicate(空港職員#AirportOut)	空港職員	90
y_airport.gat,143,49,3		duplicate(空港職員#AirportOut)	空港職員	90
y_airport.gat,158,50,3		duplicate(空港職員#AirportOut)	空港職員	90

//リヒタルゼン
lhz_airport.gat,126,51,3	duplicate(空港職員#AirportOut)	空港職員	90
lhz_airport.gat,143,49,3	duplicate(空港職員#AirportOut)	空港職員	90
lhz_airport.gat,158,50,3	duplicate(空港職員#AirportOut)	空港職員	90

//============================================================
// アインブロック空港NPC
//------------------------------------------------------------
airport.gat,174,41,6	script	青年	99,{
	mes "[ルンアン]";
	mes "私は世界中から珍しい物を";
	mes "集めているんですが……";
	mes "最近の金持ちは、いわゆる";
	mes "珍品に対する目が肥えていて、";
	mes "もっともっと珍しい物を";
	mes "探してこいってうるさいんですよ……";
	next;
	mes "[ルンアン]";
	mes "昔は、ゼロピーですら珍しがられたのに";
	mes "今じゃありふれた物……";
	mes "はぁ～……ん？　あ、あなた！";
	mes "その身につけている派手な物は";
	mes "どこで手に入れたのですか？";
	close;
}

airport.gat,176,41,4	script	おじさん	88,{
	mes "[チンアン]";
	mes "ここら辺にいるモンスターから、";
	mes "花瓶の材料となる派手な光を出す鉱物が";
	mes "たくさん取れるという話を聞きました。";
	next;
	mes "[チンアン]";
	mes "けれど、それは本当に、";
	mes "花瓶にしか使えないのでしょうか？";
	next;
	mes "[チンアン]";
	mes "……私の友達に聞いた話なんですが、";
	mes "人形ってのは、手入れした動物の皮に";
	mes "羽毛を詰めて、目にサイファーや";
	mes "ジャルゴンを入れているそうです。";
	mes "そして、重心を整えるため、";
	mes "お尻の方にゼロピーを詰めるそうです！";
	next;
	mes "[チンアン]";
	mes "……気づきましたか？　つまり、物が";
	mes "多いのは悪いことではありません。";
	mes "結局、全て何かに使えるのですから。";
	mes "だから、私の様な収集品商人は、";
	mes "倉庫の規模が商売の規模を決める。";
	mes "そう思いませんか？";
	close;
}

//============================================================
// ジュノー空港路線変更職員
//------------------------------------------------------------
y_airport.gat,145,63,4	script	空港職員	91,{
	mes "[空港職員]";
	mes "シュバルツバルド共和国内の";
	mes "各地域を行き来する";
	mes "飛行船をご利用なさいますか？";
	next;
	if(select("はい","いいえ")==1) {
		warp "yuno.gat",59,244;
		end;
	}
	mes "[空港職員]";
	mes "快適な旅になりますように。";
	close;
}

y_airport.gat,140,63,4	script	空港職員	91,{
	mes "[空港職員]";
	mes "ジュノー・イズルード・ラヘル";
	mes "を運行する飛行船を";
	mes "ご利用なさいますか？";
	next;
	if(select("はい","いいえ")==1) {
		warp "yuno.gat",47,244;
		end;
	}
	mes "[空港職員]";
	mes "快適な旅になりますように。";
	close;
}

//============================================================
// シュバルツバルド国内線 飛行船NPC
//------------------------------------------------------------
airplane.gat,100,69,3	script	乗務員	852,{
	mes "[乗務員]";
	mes "飛行船をご利用の方は、";
	mes "そこの階段を上ってください。";
	mes "いつも飛行船を利用してくださり";
	mes "ありがとうございます。";
	close;
}

airplane.gat,250,58,2	script	飛行船案内員	67,{
	mes "[飛行船案内員]";
	mes "こんにちは。";
	mes "当船では、いつも";
	mes "お客様の快適な旅行のために";
	mes "最善を尽くしております。";
	mes "何をご案内いたしましょうか？";
	next;
	if(HU_7QUE == 3) {
		menu "ティオリという人を知らないか聞く",-;
		mes "[飛行船案内員]";
		mes "申し訳ありません。";
		mes "職員の中にそのような者は";
		mes "いないようです。";
		close;
	}
	switch(select("飛行船の利用方法","船長室の位置","内部施設","けっこうです")) {
	case 1:
		mes "[飛行船案内員]";
		mes "飛行船で目的地へ行かれる場合は、";
		mes "案内放送をよくお聞きください。";
		mes "そして、目的地の到着案内が";
		mes "ありましたら、甲板にある";
		mes "出口からお降りください。";
		next;
		mes "[飛行船案内員]";
		mes "万が一、降りるタイミングを";
		mes "逃してしまったとしても、大丈夫です。";
		mes "飛行船はずっと循環運行を";
		mes "しておりますので。";
		mes "少しお待ちになって、次の到着時に";
		mes "降りるようにしてください。";
		close;
	case 2:
		mes "[飛行船案内員]";
		mes "船長室は飛行船の一番前方にあります。";
		mes "その中には、飛行船を指揮する船長と";
		mes "舵をとっている操縦士がおります。";
		mes "船長は本当によいお方なので、";
		mes "是非、一度会ってみてください。";
		close;
	case 3:
		mes "[飛行船案内員]";
		mes "飛行船には、お客様がご旅行の間、";
		mes "退屈なさらないように";
		mes "ミニゲームをご用意しております。";
		mes "長旅に疲れた時、気分転換したい時、";
		mes "少し休みたい時にくつろげる場所なので";
		mes "遠慮なくご利用ください。";
		close;
	case 4:
		mes "[飛行船案内員]";
		mes "では、よい旅になりますように。";
		close;
	}
}

airplane.gat,221,158,2	script	操縦士	852,{
	if(HU_7QUE == 3) {
		mes "[操縦士]";
		mes "どこへ行っても、";
		mes "酒さえ飲めればいいです。";
		mes "酒は私の人生！　酒は私の力！";
		mes "酒がない人生は、";
		mes "小豆がないまんじゅうと一緒です！！";
		next;
		emotion 28;
		mes "[操縦士]";
		mes "でも、飲酒運転は絶対駄目！";
		mes "それが、この仕事の";
		mes "辛いところなんです～。";
		next;
		menu "ティオリという人を知らないか聞く",-;
		mes "[操縦士]";
		mes "ふう～。";
		mes "この制服だと、あっついなぁ～。";
		mes "船長室に人は来ないから、";
		mes "パンツ姿でいようかな……。";
		next;
		mes "[操縦士]";
		mes "…………。";
		next;
		emotion 23;
		mes "[操縦士]";
		mes "ハッ!!";
		mes "誰です?!";
		next;
		mes "-……全然聞いていなかった-";
		close;
	}
	switch(rand(4)) {
	case 0:
		mes "[操縦士]";
		mes "今日は天気が本当に良いですね。";
		mes "こんな日の操縦は、";
		mes "すごく気持ちいいです。";
		close;
	case 1:
		mes "[操縦士]";
		mes "私どもの船長は、";
		mes "よい人格と格式の両方を兼ね備えた";
		mes "素晴らしい方として、";
		mes "シュバルツバルド内でも有名です。";
		mes "もちろん、船員達は皆、";
		mes "船長を慕い、尊敬しています。";
		next;
		mes "[操縦士]";
		mes "それに引き換え、船長のお兄さんは";
		mes "少々気難しい方でして……";
		mes "でも、そんなお兄さんを船長は、";
		mes "大好きなんだそうです。";
		next;
		mes "[操縦士]";
		mes "ところで、そのお兄さんが船長に";
		mes "何か借りていたようですね。";
		mes "船長は、それが急に必要になった、";
		mes "とか言って探していたようですが……。";
		close;
	case 2:
		mes "[操縦士]";
		mes "どこへ行っても、";
		mes "酒さえ飲めればいいです。";
		mes "酒は私の人生！　酒は私の力！";
		mes "酒がない人生は、";
		mes "小豆がないまんじゅうと一緒です！！";
		next;
		emotion 28;
		mes "[操縦士]";
		mes "でも、飲酒運転は絶対駄目！";
		mes "それが、この仕事の";
		mes "辛いところなんです～。";
		close;
	case 3:
		mes "[操縦士]";
		mes "ふう～。";
		mes "この制服だと、あっついなぁ～。";
		mes "船長室に人は来ないから、";
		mes "パンツ姿でいようかな……。";
		next;
		mes "[操縦士]";
		mes "…………。";
		next;
		emotion 23;
		mes "[操縦士]";
		mes "ハッ!!";
		mes "誰です?!";
		close;
	}
}

airplane.gat,65,63,4	script	少女	714,{
	mes "[少女]";
	mes "この飛行船は、";
	mes "いつルティエに着くのかしら？";
	mes "いくら待っても、";
	mes "「ルティエに到着した」という";
	mes "放送がないのよね……";
	close;
}

airplane.gat,80,71,2	script	ゼルタ	834,{
	mes "[ゼルタ]";
	mes "私は、ある教えを広めるために";
	mes "巡業している者です。";
	mes "この教えにより、";
	mes "ルーンミッドガッツ王国全体を";
	mes "団結させることが、私の願いです。";
	close;
}

airplane.gat,72,34,6	script	アノース	702,{
	mes "[アノース]";
	mes "空から眺める景色は、";
	mes "本当に良いですね。";
	mes "鳥になって、自由に飛び回れたら";
	mes "どんなに良いだろうな。";
	close;
}

airplane.gat,71,91,6	script	ウンバラの男性	789,{
	if(UM_1QUE < 3) {
		mes "[お父さん]";
		mes "ウムババ、フムババ。";
		next;
		emotion 32;
		mes "[お父さん]";
		mes "ウムバ、ウバフムバ、ウムババ。";
		mes "ウババ、ウムババ、フムババ、";
		mes "ウムバ、フムバウムバ、ウムバ。";
		close;
	}
	mes "[お父さん]";
	mes "これが飛行船か。";
	next;
	emotion 32;
	mes "[お父さん]";
	mes "実は、飛行船の乗務員たちは、";
	mes "高所恐怖症を克服するのに、";
	mes "ウンバラで訓練するのです。";
	mes "中には、高所恐怖症を克服できず、";
	mes "死者の街へ行ってしまった人も";
	mes "いるとか、いないとか。";
	close;
}

airplane.gat,66,93,2	script	ウンバラの女性	783,{
	if(UM_1QUE < 3) {
		emotion 9;
		mes "[お母さん]";
		mes "ウムバウムバ……";
		mes "ウムウムバ、ウムバフムバ、ウムババ？";
		mes "ウムバ、ウムバババ。ウムバウムバ。";
		close;
	}
	emotion 9;
	mes "[お母さん]";
	mes "この子ったら……";
	mes "少しは静かにできないの？";
	mes "人がいる所で騒いだらダメでしょう。";
	close;
}

airplane.gat,64,94,0	script	ウンバラの子供	787,{
	if(UM_1QUE < 3) {
		emotion 19;
		mes "[子供]";
		mes "ウムバウムバ!!";
		mes "ウムババ、ウムバウムバ、";
		mes "フムバ!!!";
		close;
	}
	emotion 19;
	mes "[子供]";
	mes "ウワー、ママ、見て見て！";
	mes "空を飛んでるよー!!!!";
	close;
}

airplane.gat,0,0,0	script	airplane	-1,{
OnInit:
	disablenpc "airplanewarp#ein1";
	disablenpc "airplanewarp#ein2";
	disablenpc "airplanewarp#lhz1";
	disablenpc "airplanewarp#lhz2";
	disablenpc "airplanewarp#hu1";
	disablenpc "airplanewarp#hu2";
	initnpctimer;
	end;
OnTimer1000:
	disablenpc "airplanewarp#yuno1";
	disablenpc "airplanewarp#yuno2";
	announce "当船は離陸します。次の目的地はアインブロックです。",9,0x00FF00;
	end;
OnTimer16000:
	announce "当船は現在、アインブロックに向かっております。",9,0x00FF00;
	end;
OnTimer31000:
	announce "まもなく、アインブロックに着陸いたします。",9,0x00FF00;
	end;
OnTimer41000:
	enablenpc "airplanewarp#ein1";
	enablenpc "airplanewarp#ein2";
	announce "アインブロックに到着しました。またのご利用をお待ちしております。",9,0x00FF00;
	end;
OnTimer51000:
	announce "現在、アインブロックに停船中です。出発まで、しばらくお待ちください。",9,0x00FF00;
	end;
OnTimer61000:
	disablenpc "airplanewarp#ein1";
	disablenpc "airplanewarp#ein2";
	announce "飛行船、離陸します。次の目的地はリヒタルゼンです。",9,0x73DEDE;
	end;
OnTimer76000:
	announce "当船は現在、リヒタルゼンに向かっております。",9,0x73DEDE;
	end;
OnTimer91000:
	announce "まもなく、リヒタルゼンに着陸いたします。",9,0x73DEDE;
	end;
OnTimer101000:
	enablenpc "airplanewarp#lhz1";
	enablenpc "airplanewarp#lhz2";
	announce "リヒタルゼンに到着しました。またのご利用をお待ちしております。",9,0x73DEDE;
	end;
OnTimer111000:
	announce "現在、リヒタルゼンに停船中です。出発まで、しばらくお待ちください。",9,0x73DEDE;
	end;
OnTimer121000:
	disablenpc "airplanewarp#lhz1";
	disablenpc "airplanewarp#lhz2";
	announce "当船は離陸します。次の目的地はアインブロックです。",9,0x00FF00;
	end;
OnTimer136000:
	announce "当船は現在、アインブロックに向かっております。",9,0x00FF00;
	end;
OnTimer151000:
	announce "まもなく、アインブロックに着陸いたします。",9,0x00FF00;
	end;
OnTimer161000:
	enablenpc "airplanewarp#ein1";
	enablenpc "airplanewarp#ein2";
	announce "アインブロックに到着しました。またのご利用をお待ちしております。",9,0x00FF00;
	end;
OnTimer171000:
	announce "現在、アインブロックに停船中です。出発まで、しばらくお待ちください。",9,0x00FF00;
	end;
OnTimer181000:
	disablenpc "airplanewarp#ein1";
	disablenpc "airplanewarp#ein2";
	announce "当船は離陸します。次の目的地はジュノーです。",9,0xFF8400;
	end;
OnTimer196000:
	announce "当船は現在、ジュノーに向かっております。",9,0xFF8400;
	end;
OnTimer211000:
	announce "まもなく、ジュノーに着陸いたします。",9,0xFF8400;
	end;
OnTimer221000:
	enablenpc "airplanewarp#yuno1";
	enablenpc "airplanewarp#yuno2";
	announce "ジュノーに到着しました。またのご利用をお待ちしております。",9,0xFF8400;
	end;
OnTimer231000:
	announce "現在、ジュノーに停船中です。出発まで、しばらくお待ちください。",9,0xFF8400;
	end;
OnTimer241000:
	disablenpc "airplanewarp#yuno1";
	disablenpc "airplanewarp#yuno2";
	announce "飛行船、離陸します。次の目的地はフィゲルです。",9,0xCE4AF7;
	end;
OnTimer256000:
	announce "当船は現在、フィゲルに向かっております。",9,0xCE4AF7;
	end;
OnTimer271000:
	announce "まもなく、フィゲルに着陸いたします。",9,0xCE4AF7;
	end;
OnTimer281000:
	enablenpc "airplanewarp#hu1";
	enablenpc "airplanewarp#hu2";
	announce "フィゲルに到着しました。またのご利用をお待ちしております。",9,0xCE4AF7;
	end;
OnTimer291000:
	announce "現在、フィゲルに停船中です。出発まで、しばらくお待ちください。",9,0xCE4AF7;
	end;
OnTimer301000:
	disablenpc "airplanewarp#hu1";
	disablenpc "airplanewarp#hu2";
	announce "当船は離陸します。次の目的地はジュノーです。",9,0xFF8400;
	end;
OnTimer316000:
	announce "当船は現在、ジュノーに向かっております。",9,0xFF8400;
	end;
OnTimer331000:
	announce "まもなく、ジュノーに着陸いたします。",9,0xFF8400;
	end;
OnTimer341000:
	enablenpc "airplanewarp#yuno1";
	enablenpc "airplanewarp#yuno2";
	announce "ジュノーに到着しました。またのご利用をお待ちしております。",9,0xFF8400;
	end;
OnTimer351000:
	announce "現在、ジュノーに停船中です。出発まで、しばらくお待ちください。",9,0xFF8400;
	end;
OnTimer360000:
	initnpctimer;
	end;
}

airplane.gat,243,29	warp	airplanewarp#yuno1	1,1,yuno.gat,92,260
airplane.gat,243,73	warp	airplanewarp#yuno2	1,1,yuno.gat,92,260
airplane.gat,243,29	warp	airplanewarp#ein1	1,1,einbroch.gat,92,278
airplane.gat,243,73	warp	airplanewarp#ein2	1,1,einbroch.gat,92,278
airplane.gat,243,29	warp	airplanewarp#lhz1	1,1,lighthalzen.gat,302,75
airplane.gat,243,73	warp	airplanewarp#lhz2	1,1,lighthalzen.gat,302,75
airplane.gat,243,29	warp	airplanewarp#hu1	1,1,hugel.gat,181,146
airplane.gat,243,73	warp	airplanewarp#hu2	1,1,hugel.gat,181,146

airplane.gat,240,64,5	script	出口	857,{}
airplane.gat,247,64,5	script	出口	857,{}
airplane.gat,240,40,0	script	出口	857,{}
airplane.gat,247,40,0	script	出口	857,{}

//============================================================
// 国外線 飛行船NPC
//------------------------------------------------------------
airplane_01.gat,250,58,3	script	飛行船案内員#AirEvent	67,{
	mes "[飛行船案内員]";
	mes "こんにちは。";
	mes "当船では、いつも";
	mes "お客様の快適な旅行のために";
	mes "最善を尽くしております。";
	mes "何をご案内いたしましょうか？";
	next;
	switch(select("飛行船の利用方法","船長室の位置","内部施設","けっこうです")) {
	case 1:
		mes "[飛行船案内員]";
		mes "飛行船で目的地へ行かれる場合は、";
		mes "案内放送をよくお聞きください。";
		mes "そして、目的地の到着案内が";
		mes "ありましたら、甲板にある";
		mes "出口からお降りください。";
		next;
		mes "[飛行船案内員]";
		mes "万が一、降りるタイミングを";
		mes "逃してしまったとしても、大丈夫です。";
		mes "飛行船はずっと循環運行を";
		mes "しておりますので。";
		mes "少しお待ちなって、次の到着時に";
		mes "降りるようにしてください。";
		close;
	case 2:
		mes "[飛行船案内員]";
		mes "船長室は飛行船の一番前方にあります。";
		mes "その中には、飛行船を指揮する船長と";
		mes "舵をとっている操縦士がおります。";
		mes "船長は性格が少々……。";
		mes "まあ、お話する時は、";
		mes "気をつけてくださいね。";
		close;
	case 3:
		mes "[飛行船案内員]";
		mes "飛行船には、お客様がご旅行の間、";
		mes "退屈なさらないように";
		mes "ミニゲームをご用意しております。";
		mes "長旅に疲れた時、気分転換したい時、";
		mes "少し休みたい時にくつろげる場所なので";
		mes "遠慮なくご利用ください。";
		close;
	case 4:
		mes "[飛行船案内員]";
		mes "では、よい旅になりますように。";
		close;
	}
}

airplane_01.gat,221,158,2	script	操縦士	852,{
	switch(rand(4)) {
	case 0:
		mes "[操縦士]";
		mes "今日は雲が多いですね。";
		mes "こんな日は航路を見つけるのが";
		mes "大変なんです。";
		mes "はぁ～";
		close;
	case 1:
		mes "[操縦士]";
		mes "船長は、気難しい方です。";
		mes "何か問題を起こすと、";
		mes "その後始末は全部、";
		mes "私ども船員達がします。";
		mes "今日もまた、何のトラブルを";
		mes "起こすことやら……はぁ～。";
		next;
		mes "[^FF0000ペルロック^000000]";
		mes "^FF0000おい！　そこ!!";
		mes "無駄話してないで働け！^000000";
		next;
		mes "[操縦士]";
		mes "は、はい！";
		mes "了解です!!";
		close;
	case 2:
		mes "[操縦士]";
		mes "現在、α131、β52の上を航行中。";
		mes "異常なし！";
		close;
	case 3:
		mes "[操縦士]";
		mes "ふう～。";
		mes "この制服だと、あっついなぁ～。";
		mes "船長室に人は来ないから、";
		mes "パンツ姿でいようかな……。";
		next;
		mes "[操縦士]";
		mes "…………。";
		next;
		emotion 23;
		mes "[操縦士]";
		mes "ハッ!!";
		mes "誰です?!";
		close;
	}
}

airplane_01.gat,83,61,2	script	少女	72,2,2,{
	mes "[少女]";
	mes "うわ～ん!!";
	mes "お外ではしゃいでたら、";
	mes "鹿さん怒られた～。";
	mes "びっくりしたよ～。";
	close;
OnTouch:
	emotion 28;
	end;
}

airplane_01.gat,69,63,2	script	貴族の男性	55,{
	mes "[貴族の男性]";
	mes "やはり機内食は、私の口に合わないね。";
	mes "気品も、センスもない。";
	mes "専属料理人を連れて来ればよかった。";
	close;
}

airplane_01.gat,71,31,2	script	剣士	106,{
	mes "[剣士]";
	mes "……5年前の復讐……。";
	mes "……覚えてろ……。";
	mes "今度は絶対に逃がさんぞ!!";
	close;
}

airplane_01.gat,0,0,0	script	airplane_01	-1,{
OnInit:
	disablenpc "airplanewarp#iz1";
	disablenpc "airplanewarp#iz2";
	disablenpc "airplanewarp#yuno1_";
	disablenpc "airplanewarp#yuno2_";
	set 'count,12;
	initnpctimer;
	end;
OnTimer1000:
	disablenpc "airplanewarp#ra1";
	disablenpc "airplanewarp#ra2";
	announce "当船は離陸します。次の目的地はイズルードです。",9,0x00FF00;
	end;
OnTimer26000:
	announce "当船は現在、イズルードに向かっております。",9,0x00FF00;
	end;
OnTimer31000:
	if('count <= 0) {
		if(rand(3) == 0)
			callsub L_Attack;
		set 'count,12;
	}
	end;
OnTimer51000:
	announce "まもなく、イズルードに着陸いたします。",9,0x00FF00;
	end;
OnTimer61000:
	enablenpc "airplanewarp#iz1";
	enablenpc "airplanewarp#iz2";
	announce "イズルードに到着しました。またのご利用をお待ちしております。",9,0x00FF00;
	end;
OnTimer71000:
	announce "現在、イズルードに停船中です。出発まで、しばらくお待ちください。",9,0x00FF00;
	end;
OnTimer81000:
	disablenpc "airplanewarp#iz1";
	disablenpc "airplanewarp#iz2";
	announce "当船は離陸します。次の目的地はジュノーです。",9,0x73DEDE;
	end;
OnTimer106000:
	announce "当船は現在、ジュノーに向かっております。",9,0x73DEDE;
	end;
OnTimer131000:
	announce "まもなく、ジュノーに着陸いたします。",9,0x73DEDE;
	end;
OnTimer141000:
	enablenpc "airplanewarp#yuno1_";
	enablenpc "airplanewarp#yuno2_";
	announce "ジュノーに到着しました。またのご利用をお待ちしております。",9,0x73DEDE;
	end;
OnTimer151000:
	announce "現在、ジュノーに停船中です。出発まで、しばらくお待ちください。",9,0x73DEDE;
	end;
OnTimer161000:
	disablenpc "airplanewarp#yuno1_";
	disablenpc "airplanewarp#yuno2_";
	announce "当船は離陸します。次の目的地はラヘルです。",9,0xFF8400;
	end;
OnTimer176000:
	announce "当船は現在、ラヘルに向かっております。",9,0xFF8400;
	end;
OnTimer191000:
	announce "まもなく、ラヘルに着陸いたします。",9,0xFF8400;
	end;
OnTimer201000:
	enablenpc "airplanewarp#ra1";
	enablenpc "airplanewarp#ra2";
	announce "ラヘルに到着しました。またのご利用をお待ちしております。",9,0xFF8400;
	end;
OnTimer211000:
	announce "現在、ラヘルに停船中です。出発まで、しばらくお待ちください。",9,0xFF8400;
	end;
OnTimer220000:
	set 'count,'count-1;
	initnpctimer;
	end;
L_Attack:
	stopnpctimer;
	announce "観測兵：うん……うわ～っ!! 変なものが近づいてきてる?!",9,0x00FF00;
	sleep 4000;
	announce "案内放送：乗客の皆様、現在、正体不明のモンスター達が当船に向っております!!",9,0x00FF00;
	sleep 4000;
	announce "案内放送：甲板にいらっしゃる方々は、至急、中へ非難してください。",9,0x00FF00;
	hideonnpc "飛行船案内員#AirEvent";
	sleep 10000;
	monster "airplane_01.gat",245,57,"グレムリン",1632,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",247,59,"グレムリン",1632,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",249,52,"グレムリン",1632,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",243,62,"グレムリン",1632,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",239,52,"ビホルダー",1633,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",234,56,"ビホルダー",1633,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",227,49,"ビホルダー",1633,1,"Airplane#AirEvent1";
	monster "airplane_01.gat",233,41,"ビホルダー",1633,1,"Airplane#AirEvent1";
	setarray '@mobid,1111,1392,1005,1049,1042;
	monster "airplane_01.gat",251,47,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",245,53,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",234,46,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",233,58,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",243,60,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",228,54,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",232,41,"--ja--",'@mobid[rand(5)],1,"Airplane#AirEvent1";
	monster "airplane_01.gat",238,56,"グレムリン",1632,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",239,56,"グレムリン",1632,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",240,50,"グレムリン",1632,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",241,56,"グレムリン",1632,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",247,51,"グレムリン",1632,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",237,44,"ビホルダー",1633,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",233,54,"ビホルダー",1633,1,"Airplane#AirEvent2";
	monster "airplane_01.gat",237,62,"ビホルダー",1633,1,"Airplane#AirEvent2";
	sleep 5000;
	announce "乗務員：ペルロック船長、大変です！　グレムリンどもがプロペラに……!!",9,0x00FF00;
	sleep 5000;
	announce "ペルロック船長：何だと?!　奴らめ～、ただじゃおかねぇ～!!　この俺様が直接……！",9,0x73DEDE;
	sleep 5000;
	hideonnpc "飛行船船長#Air";
	hideoffnpc "飛行船船長#AirEvent";
	sleep 5000;
	emotion 7,"飛行船船長#AirEvent";
	announce "ペルロック船長：こいつらめ～!!　引きずり下ろすことができねぇーっ!!",9,0x73DEDE;
	sleep 5000;
	announce "-ギイギイーッ……グルルゥーッ、ギイギイギィーッ、グアァーッ!!-",9,0x00FF00;
	misceffect 183,"Effect#AirEvent6";
	sleep 500;
	misceffect 183,"Effect#AirEvent7";
	sleep 500;
	misceffect 183,"Effect#AirEvent8";
	sleep 500;
	misceffect 183,"Effect#AirEvent9";
	sleep 500;
	misceffect 183,"Effect#AirEvent10";
	sleep 500;
	misceffect 183,"Effect#AirEvent6";
	sleep 500;
	misceffect 183,"Effect#AirEvent7";
	sleep 500;
	misceffect 183,"Effect#AirEvent8";
	sleep 500;
	misceffect 183,"Effect#AirEvent9";
	sleep 500;
	misceffect 183,"Effect#AirEvent10";
	sleep 500;
	misceffect 183,"Effect#AirEvent6";
	announce "機関士：うわ～っ!!　1番の後方エンジンがっ……！",9,0x00FF00;
	sleep 1000;
	misceffect 183,"Effect#AirEvent7";
	sleep 1000;
	misceffect 183,"Effect#AirEvent8";
	sleep 1000;
	misceffect 183,"Effect#AirEvent9";
	sleep 1000;
	misceffect 183,"Effect#AirEvent10";
	sleep 1000;
	misceffect 183,"Effect#AirEvent6";
	sleep 1000;
	announce "操縦士：老人と女性、子供を先に安全な場所へ！　急げ!!",9,0x00FF00;
	sleep 1000;
	misceffect 183,"Effect#AirEvent6";
	sleep 1000;
	misceffect 183,"Effect#AirEvent7";
	sleep 1000;
	misceffect 183,"Effect#AirEvent8";
	sleep 1000;
	misceffect 183,"Effect#AirEvent7";
	sleep 1000;
	emotion 7,"飛行船船長#AirEvent";
	announce "ペルロック船長：ぬぅ～っ！　実力行使しかなさそうだな……。",9,0x73DEDE;
	sleep 5000;
	emotion 6,"飛行船船長#AirEvent";
	announce "ペルロック船長：俺様の船で暴れるとどうなるか、思い知らせてやるっ!!",9,0x73DEDE;
	sleep 5000;
	emotion 32,"飛行船船長#AirEvent";
	announce "ペルロック船長：特製のエクソダスジョーカーⅩⅢ、このとっておきのライフルでケリをつけてやるっ!!",9,0x73DEDE;
	sleep 5000;
	announce "シュッ!!　パンパン！　パンパン！　ズドンズドンズドンッ!!",9,0x00FF00;
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent1";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent2";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent3";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent4";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent5";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent0";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent1";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent2";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent3";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent4";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent5";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent0";
	killmonster "airplane_01.gat","Airplane#AirEvent2";
	sleep 5000;
	emotion 32,"飛行船船長#AirEvent";
	announce "ペルロック船長：グハハハッ！　これでどうだ?!",9,0x73DEDE;
	sleep 5000;
	announce "シュッ!!　パンパン！　パンパン！　ズドンズドンズドンッ!!",9,0x00FF00;
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent6";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent7";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent8";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent9";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent10";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent6";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent7";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent8";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent9";
	misceffect 5,"飛行船船長#AirEvent";
	sleep 500;
	misceffect 183,"Effect#AirEvent8";
	announce "ボン！　プスプス……ドカンドカン！",9,0x00FF00;
	sleep 1000;
	misceffect 183,"Effect#AirEvent9";
	sleep 1000;
	misceffect 183,"Effect#AirEvent10";
	sleep 1000;
	misceffect 183,"Effect#AirEvent6";
	sleep 1000;
	misceffect 183,"Effect#AirEvent7";
	sleep 1000;
	emotion 6,"飛行船船長#AirEvent";
	announce "ペルロック船長：なぬ?!　あいつら、またエンジンを壊しやがった?!",9,0x73DEDE;
	sleep 5000;
	announce "操縦士：あ、あの……エンジンが壊れたのは、船長のライフルのせいかと……。",9,0x00FF00;
	sleep 5000;
	emotion 4,"飛行船船長#AirEvent";
	announce "ペルロック船長：んあ？　それは……まあ～、誰しも間違いはあるだろ！　フハハハハッ！",9,0x73DEDE;
	sleep 5000;
	emotion 17,"飛行船船長#AirEvent";
	announce "ペルロック船長：とにかく、後のことはお前達に任せた……。ハハハハーッ！",9,0x73DEDE;
	sleep 5000;
	hideonnpc "飛行船船長#AirEvent";
	hideoffnpc "飛行船船長#Air";
	sleep 150000;
	killmonster "airplane_01.gat","Airplane#AirEvent1";
	sleep 5000;
	announce "案内放送：モンスター達は、全ていなくなったようです。では、再び通常運行に戻ります。",9,0x00FF00;
	hideoffnpc "飛行船案内員#AirEvent";
	setnpctimer 46000;
	startnpctimer;
	return;
}

airplane_01.gat,243,29	warp	airplanewarp#yuno1_	1,1,yuno.gat,12,261
airplane_01.gat,243,73	warp	airplanewarp#yuno2_	1,1,yuno.gat,12,261
airplane_01.gat,243,29	warp	airplanewarp#iz1	1,1,izlude.gat,200,56
airplane_01.gat,243,73	warp	airplanewarp#iz2	1,1,izlude.gat,200,56
airplane_01.gat,243,29	warp	airplanewarp#ra1	1,1,ra_fild12.gat,292,204
airplane_01.gat,243,73	warp	airplanewarp#ra2	1,1,ra_fild12.gat,292,204

airplane_01.gat,240,64,5	script	出口	857,{}
airplane_01.gat,247,64,5	script	出口	857,{}
airplane_01.gat,240,40,0	script	出口	857,{}
airplane_01.gat,247,40,0	script	出口	857,{}

airplane_01.gat,247,54,3	script	飛行船船長#AirEvent	873,{
	mes "[ペルロック]";
	mes "私が、この飛行船の船長ペルロックだ。";
	mes "今はグレムリン対応で忙しいから、";
	mes "後にしてくれないか！";
	close;
OnInit:
	hideonnpc;
	end;
}

airplane_01.gat,249,50,0	script	Effect#AirEvent0	139,{}
airplane_01.gat,239,62,0	script	Effect#AirEvent1	139,{}
airplane_01.gat,244,55,0	script	Effect#AirEvent2	139,{}
airplane_01.gat,239,50,0	script	Effect#AirEvent3	139,{}
airplane_01.gat,245,59,0	script	Effect#AirEvent4	139,{}
airplane_01.gat,245,48,0	script	Effect#AirEvent5	139,{}
airplane_01.gat,235,39,0	script	Effect#AirEvent6	139,{}
airplane_01.gat,252,41,0	script	Effect#AirEvent7	139,{}
airplane_01.gat,252,63,0	script	Effect#AirEvent8	139,{}
airplane_01.gat,234,65,0	script	Effect#AirEvent9	139,{}
airplane_01.gat,227,67,0	script	Effect#AirEvent10	139,{}

airplane_01.gat,0,0,0	script	Airplane#AirEvent1	-1,{}	//ダミーイベント
airplane_01.gat,0,0,0	script	Airplane#AirEvent2	-1,{}	//ダミーイベント

//============================================================
// 船内施設
//------------------------------------------------------------
-	script	AirApple	-1,{
	mes "[" +strnpcinfo(2)+ "]";
	mes "いらっしゃいませ～。";
	mes "美味しい～、甘～いリンゴは";
	mes "いかがですか～。";
	mes "リンゴジュースも作りますよ～。";
	next;
	if(strnpcinfo(2) == "フルツ")	//フルツの場合、選択肢増加
		set '@word$,"何故ここにリンゴ売りが？";
	switch(select("リンゴを買う","リンゴジュースを作る",'@word$,"取り消し")) {
	case 1:
		mes "[" +strnpcinfo(2)+ "]";
		mes "リンゴは1個、15zenyです。";
		mes "1度に500個まで買えます。";
		mes "やっぱりやめたって方は";
		mes "0を入力してくださいね。";
		mes "何個欲しいですか？";
		next;
		while(1) {
			input '@num;
			if('@num>500 || '@num<0) {
				mes "[" +strnpcinfo(2)+ "]";
				mes "一度に買えるのは、500個までですよ。";
				next;
				continue;
			}
			break;	//while文抜ける
		}
		if('@num==0)
			break;	//switch文抜ける
		set '@price,'@num*15;
		mes "[" +strnpcinfo(2)+ "]";
		mes "リンゴ^FF0000"+'@num+"個^000000で、";
		mes "金額は^FF0000"+'@price+"zeny^000000ですね。";
		mes "買いますか？";
		next;
		if(select("はい","いいえ")==2)
			break;	//「いいえ」ならswitch文抜ける
		if(Zeny<'@price) {
			mes "[" +strnpcinfo(2)+ "]";
			mes "あら、お金が足りないようですよ。";
			mes "お金をもうちょっと持ってくるか、";
			mes "購入するリンゴの数を";
			mes "減らしてくださいね～。";
			close;
		}
		if(checkweight(512,'@num)==0) {
			mes "[" +strnpcinfo(2)+ "]";
			mes "あらあら、それじゃあ荷物が多くて";
			mes "リンゴを買っても持てませんよ。";
			mes "荷物、減らしてきた方が";
			mes "いいと思いますよ。";
			close;
		}
		set Zeny,Zeny-'@price;
		getitem 512,'@num;
		mes "[" +strnpcinfo(2)+ "]";
		mes "毎度、ありがとうございました～！";
		mes "リンゴが必要になったら";
		mes "いつでも来てくださいね。";
		close;
	case 2:
		mes "[" +strnpcinfo(2)+ "]";
		mes "リンゴジュースは";
		mes "^FF0000リンゴ3個、空きビン1個^000000で";
		mes "作れます。";
		mes "リンゴジュースを作りますか？";
		next;
		if(select("はい","いいえ")==2)
			break;	//switch文抜ける
		if(countitem(512) < 3 || countitem(713) < 1) {
			mes "[" +strnpcinfo(2)+ "]";
			mes "あら、材料が足りないみたいですね。";
			mes "いいですか、^FF0000リンゴ3個、";
			mes "空きビン1個^000000ですよ。";
			mes "材料がそろったら、";
			mes "またいらしてくださいね。";
			close;
		}
		mes "[" +strnpcinfo(2)+ "]";
		mes "はい、ちょっと待っててくださいね。";
		next;
		mes "サク、サク、トントン……";
		mes "ギュオ～ン、グォングォン、";
		mes "ギュオ～～～ン!!";
		next;
		delitem 512,3;
		delitem 713,1;
		getitem 531,1;
		mes "[" +strnpcinfo(2)+ "]";
		mes "はい、新鮮なリンゴジュースです。";
		mes "毎度、ありがとうございました～！";
		mes "リンゴジュースが必要になったら";
		mes "いつでも来てくださいね。";
		close;
	case 3:
		mes "[フルツ]";
		mes "実は私、以前は日々の食べ物ですら";
		mes "人からもらって生活していました。";
		mes "そんなある日、木の下でぐっすり";
		mes "眠っていたら、私の頭に何かが";
		mes "ドンって落ちてきまして……";
		next;
		mes "[フルツ]";
		mes "びっくりして起きて、辺りを見回すと";
		mes "リンゴが転がっていました。";
		mes "私、リンゴの木の下で";
		mes "眠っていたんですね。";
		next;
		mes "[フルツ]";
		mes "ちょうどお腹が空いてたので、";
		mes "そのリンゴを食べることにしました。";
		mes "すると、飛行船のおじさんに";
		mes "助けてくれ～って";
		mes "急に呼ばれたんですよ。";
		next;
		mes "[フルツ]";
		mes "それで、しばらく飛行船で";
		mes "お手伝いをしました。";
		mes "その後に、リンゴを賭けて";
		mes "サイコロゲームをしている";
		mes "お姉さんに気がついたんです。";
		next;
		mes "[フルツ]";
		mes "退屈だったし、ちょうど";
		mes "リンゴを持っていたから、";
		mes "そのゲームで遊んでみました。";
		mes "そうしたら、運が良かったのか";
		mes "1個だったリンゴが2個、";
		mes "2個が4個になっていき……";
		next;
		mes "[フルツ]";
		mes "そうこうしているうちに、";
		mes "何と商売ができるくらいの";
		mes "リンゴが集まっちゃいました！";
		mes "信じられない出来事ですけど、";
		mes "リンゴ1個が私の人生を変えたんです！";
		next;
		mes "[フルツ]";
		mes "話が長くなっちゃいましたね。";
		mes "リンゴは健康にも美容にもいいですよ。";
		mes "お一つどうですか？";
		close;
	case 4:
		break;
	}
	mes "[" +strnpcinfo(2)+ "]";
	mes "よかったら次は買ってくださいね。";
	mes "では、お元気で～。";
	close;
}
airplane.gat,50,66,5	duplicate(AirApple)	リンゴ商人#フルツ	86
airplane_01.gat,50,66,5	duplicate(AirApple)	リンゴ商人#メルツ	86

-	script	AirDice	-1,{
	if(strnpcinfo(1) == "ケージ") {
		switch(HU_7QUE) {
		case 3:
			mes "[ケージ]";
			mes "こんにちは。";
			mes "私の名前はケージ。";
			mes "ちょっと退屈してるの。";
			mes "暇つぶしに、私とサクっと軽く";
			mes "サイコロゲームでもしない？";
			next;
			menu "ティオリという人を知らないか聞く",-;
			mes "[ケージ]";
			mes "ティオリ？";
			mes "どこかで聞いたような……";
			next;
			mes "[ケージ]";
			mes "……………………";
			mes "………………";
			mes "…………";
			mes "……";
			next;
			mes "[ケージ]";
			mes "アアッ！　ティオリ!!";
			next;
			mes "-急に思い出したように";
			mes "彼女は大きい声を出した-";
			mes "-おかげで私は食べていたりんごを";
			mes "落としてしまった-";
			next;
			mes "[ケージ]";
			mes "アハハッ。ごめんなさい。";
			mes "急に大声を出してしまって。";
			mes "あんまり懐かしい名前だったから";
			mes "なかなか思い出せなかったの。";
			next;
			mes "[ケージ]";
			mes "私が以前マウォング師匠に";
			mes "ゲームを教わっていた時、";
			mes "隣りに住んでいた青年だったわ。";
			mes "頭が良くて色んな研究を";
			mes "していたことを覚えてるわ。";
			next;
			mes "[ケージ]";
			mes "そういえば、マウォング師匠の下で";
			mes "一緒にゲームを学んだユスランと";
			mes "ティオリはラブラブだったわね。";
			mes "二人の関係はどうなったのかしら。";
			next;
			mes "-私は彼女にユスランとティオリは";
			mes "婚約していて、ティオリはユスランの";
			mes "病気を治すために飛行船に乗って";
			mes "どこかへ行ってしまった事を話した-";
			next;
			mes "[ケージ]";
			mes "え……そんな……";
			mes "あのユスランがそんな重い病気に……";
			mes "……あぁ…………";
			next;
			mes "-急な話に衝撃を受けたケージは";
			mes "焦点を失ったまま小声でぼそぼそと";
			mes "つぶやいていた-";
			mes "-しばらくすると、ハッと";
			mes "私に気づいて我に返った-";
			next;
			mes "[ケージ]";
			mes "ごめんなさい……";
			mes "私も役に立ちたいけど、";
			mes "最後に会ったのは数年前。";
			mes "どこに行ったのかわからないわ。";
			next;
			mes "[ケージ]";
			mes "何か方法は……";
			next;
			mes "[ケージ]";
			mes "……あ！";
			mes "船長なら知っているかも。";
			mes "搭乗者リストがあるはずよ。";
			next;
			mes "[ケージ]";
			mes "でも、搭乗者リストは";
			mes "一般人に公開しないのが原則……";
			next;
			mes "[ケージ]";
			mes "それでも事情を話せば";
			mes "船長はわかってくれるはず。";
			mes "船長に頼んでみて！";
			next;
			mes "[ケージ]";
			mes "あと、ユスランに会ったら、";
			mes "私はあなたの幸せを願ってる";
			mes "って伝えて欲しいの。";
			mes "お願い。";
			next;
			mes "-切実な彼女の願いを、";
			mes "必ず伝えると約束した-";
			set HU_7QUE,4;
			close;
		case 4:
			mes "[ケージ]";
			mes "ティオリがどこに行ったかは";
			mes "船長に聞いてみて。";
			mes "事情を話せばわかってくれるはずよ。";
			close;
		}
		switch(AIR_2QUE) {
		case 2:
			mes "[ケージ]";
			mes "こんにちは。";
			mes "私の名前はケージ。";
			mes "ちょっと退屈してるの。";
			mes "暇つぶしに、私とサクっと軽く";
			mes "サイコロゲームでもしない？";
			next;
			menu "ヘイルレンに頼まれた手紙を渡す。",-;
			mes "[ケージ]";
			mes "ん？　あ……";
			mes "ヘイルレンに頼まれたのね。";
			mes "あの子ったら……";
			mes "言われたことをちゃんと";
			mes "してればいいのに……";
			mes "お客様に迷惑をかけちゃったわね。";
			next;
			mes "[ケージ]";
			mes "あ、そうそう。";
			mes "これ、ありがとう。";
			mes "私はちょっと手紙を読んでるから、";
			mes "何かあったらいつでも言ってね。";
			set AIR_2QUE,3;
			close;
		case 3:
			mes "[ケージ]";
			mes "こんにちは。";
			mes "手紙、ありがとね。";
			mes "何か知りたいことがあったら";
			mes "遠慮なくどうぞ。";
			while('@tolk < 0x7) {
				next;
				switch(select("ヘイルレンと姉弟なのか聞く","手紙を送ったマウォングについて聞く","飛行船をどう思っているのか聞く")) {
				case 1:
					mes "[ケージ]";
					mes "ヘイルレンと？";
					mes "いいえ、姉弟じゃないわ。";
					mes "私の母方のおじの息子、";
					mes "私と従姉弟ってことかな。";
					next;
					mes "[ケージ]";
					mes "20年前、私のお父さんが";
					mes "アインベフで起きた";
					mes "鉱山爆発事故で死んで以来……";
					mes "一人になった私は";
					mes "ジュノーにある";
					mes "母方のおじの家で育ったの。";
					next;
					mes "[ケージ]";
					mes "そうするうちに偶然、";
					mes "サイコロゲームで";
					mes "人々を楽しませていたのを";
					mes "トロック船長に見込まれて";
					mes "この飛行船に乗る事になったの。";
					next;
					mes "[ケージ]";
					mes "小さい頃から何かを作るのが";
					mes "好きだったヘイルレンは";
					mes "私が飛行船で働くことになった";
					mes "と聞くと、何でもするから";
					mes "飛行船で一緒に働かせてって";
					mes "トロック船長にせがんだのよ。";
					next;
					mes "[ケージ]";
					mes "それで、結局あの子も";
					mes "一緒にきたんです。";
					mes "一度言い出すと聞かない子だから。";
					mes "フフッ。";
					next;
					set '@tolk,'@tolk|0x1;
					break;
				case 2:
					mes "[ケージ]";
					mes "あ、マウォング先生ね。";
					mes "マウォング先生は面白いゲームを";
					mes "たくさん作ることで有名な人よ。";
					mes "そして、私の恩師でもあるの。";
					next;
					mes "[ケージ]";
					mes "私が母方のおじの家にいた時、";
					mes "ある日、";
					mes "村にマウォング先生がきたわ。";
					next;
					mes "[ケージ]";
					mes "当時何一つまともにできなかったし、";
					mes "父さんの死で落ち込んでて……";
					mes "マウォング先生がきたことを聞いても";
					mes "全然関心がなかったわ。";
					next;
					mes "[ケージ]";
					mes "それなのに……";
					mes "偶然にだけど、先生に会ったの。";
					mes "先生は、あの時まで私が忘れていた";
					mes "笑いを取り戻してくれたわ。";
					next;
					mes "[ケージ]";
					mes "マウォング先生と出会って、";
					mes "私の人生にも笑いと幸せがあることが";
					mes "わかったのよ。";
					next;
					mes "[ケージ]";
					mes "その後……";
					mes "私は自分が得た笑いと幸せを";
					mes "以前の私のように落ち込んでいる";
					mes "人たちに伝えようと思って、";
					mes "先生の弟子になったの。";
					next;
					mes "[ケージ]";
					mes "先生には";
					mes "色々なゲームを教えてもらったわ……";
					mes "マウォング先生との縁は";
					mes "こんな風に始まったのよ。";
					next;
					set '@tolk,'@tolk|0x2;
					break;
				case 3:
					mes "[ケージ]";
					mes "大きくて……美しいわ。";
					mes "こんな大きな物体が";
					mes "空を飛び回れるのが";
					mes "本当に不思議で……";
					mes "神秘的に感じるわ。";
					next;
					mes "[ケージ]";
					mes "ここへ来る前から、";
					mes "高い所で世界を眺めながら";
					mes "好きなことをしたいって、";
					mes "いつも考えてたわ。";
					next;
					mes "[ケージ]";
					mes "そうしたらある日、";
					mes "私とサイコロゲームをした";
					mes "トロック船長が、飛行船で";
					mes "一緒に働こうと言ってくれたの。";
					mes "私はすぐに「はい」って答えたわ。";
					next;
					set '@tolk,'@tolk|0x4;
					break;
				}
				if('@tolk < 0x7) {
					mes "[ケージ]";
					mes "他に知りたい事があるならどうぞ。";
				}
			}
			mes "[ケージ]";
			mes "また、ヘイルレンが";
			mes "お客様に迷惑をかけるようだったら、";
			mes "はっきりと断ってね。";
			mes "あの子、すぐ甘えちゃうから。";
			mes "フフッ。";
			next;
			mes "[ケージ]";
			mes "そろそろまた仕事を";
			mes "始めなくちゃ。";
			mes "それじゃ、楽しい一日を！";
			set AIR_2QUE,4;
			close;
		case 8:
			mes "[ケージ]";
			mes "こんにちは。";
			mes strcharinfo(0)+ "さん。";
			mes "飛行船でよくお目にかかりますね。";
			mes "フフッ。";
			mes "何か聞きたいことでもあるの？";
			next;
			menu "酔っ払っている人が誰か聞く",-;
			mes "[ケージ]";
			mes "あぁ、あの人？";
			mes "どうもアインブロックにある";
			mes "研究所の所長さんみたいよ。";
			next;
			mes "[ケージ]";
			mes "いつもお酒を飲んでは";
			mes "私にリンゴが奪われるのが";
			mes "好きって言ってるけど、";
			mes "リンゴを取られると";
			mes "やっぱり落ち込んでるわね。";
			next;
			mes "[ケージ]";
			mes "この前、横にいるリンゴ商人さんから";
			mes "リンゴを沢山買って";
			mes "破産する一歩手前になってたわ。";
			next;
			mes "[ケージ]";
			mes "でも、そんなおじさんのおかげで";
			mes "この仕事が前より";
			mes "もっと好きになれた気がするわ。";
			mes "ありがたいお客さんかしらね。";
			next;
			mes "[ケージ]";
			mes "それにしても、";
			mes "いつも疲れているみたいね。";
			mes "所長さんだし、";
			mes "仕事が大変なのかしら？";
			mes "私が知ってるのはこれぐらいよ。";
			next;
			mes "（うーん……";
			mes "アインブロックの研究所か……";
			mes "一般人は入れない所だから";
			mes "どうも怪しいな……）";
			next;
			mes "（あの人が";
			mes "ユミルの心臓を知っているなら……";
			mes "その研究所に何かが……）";
			next;
			mes "（よし！";
			mes "アインブロックの研究所に";
			mes "行ってみよう。）";
			set AIR_2QUE,9;
			close;
		}
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "こんにちは。";
	mes "私の名前は" +strnpcinfo(1)+ "。";
	mes "ちょっと退屈してるの。";
	mes "暇つぶしに、私とサクっと軽く";
	mes "サイコロゲームでもしない？";
	next;
	switch (select("する","ルールを教えて","しない")) {
	case 1:
		mes "[" +strnpcinfo(1)+ "]";
		mes "サイコロゲームをするには、";
		mes "リンゴが必要よ。";
		mes "リンゴ、何個賭ける？";
		mes "最大50個まで賭けられるわ。";
		mes "止めるんだったら、0って入れてね。";
		while(1) {
			next;
			input '@apple;
			if('@apple<=0) {
				mes "[" +strnpcinfo(1)+ "]";
				mes "退屈だったら、後でまた来てね。";
				mes "じゃあね！";
				close;
			}
			if('@apple>50) {
				mes "[" +strnpcinfo(1)+ "]";
				mes "最大は50までよ。";
				mes "次は間違えないよう教えてね。";
				continue;
			}
			mes "[" +strnpcinfo(1)+ "]";
			mes "リンゴ^FF0000" +'@apple+ "個^000000で";
			mes "間違いない？";
			next;
			if(select("はい","いいえ")==2) {
				mes "[" +strnpcinfo(1)+ "]";
				mes "今度は間違いなく入力してね。";
				continue;
			}
			if(countitem(512) < '@apple) {
				mes "[" +strnpcinfo(1)+ "]";
				mes "リンゴが足りないみたいよ。";
				mes "何個賭ける？";
				continue;
			}
			break;	//while文を抜ける
		}
		delitem 512,'@apple;
		mes "[" +strnpcinfo(1)+ "]";
		mes "はーい。";
		mes "では、ゲームの始まり始まり。";
		mes "私が先に転がすわね。";
		next;
		mes "-コロ～ン、コロコロ-";
		next;
		//[0]:合計,[1]:1個目,[2]:2個目,[3]:3個目
		setarray '@enemy[1],rand(1,6),rand(1,6);
		setarray '@mine[1],rand(1,6),rand(1,6);
		set '@enemy[0],'@enemy[1]+'@enemy[2];
		set '@mine[0],'@mine[1]+'@mine[2];
		mes "[" +strnpcinfo(1)+ "]";
		mes "私の手は^0000FF" +'@enemy[1]+ "^000000と^0000FF" +'@enemy[2]+ "^000000。";
		mes "合計は^0000FF" +'@enemy+ "^000000ね。";
		mes "今度は^FF0000" +strcharinfo(0)+ "^000000さんの";
		mes "番よ。";
		next;
		menu "サイコロを転がす",-;
		mes "-コロ～ン、コロコロ-";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "^FF0000" +strcharinfo(0)+ "^000000さんの手は";
		mes "^FF0000" +'@mine[1]+ "^000000と^FF0000" +'@mine[2]+ "^000000ね。";
		mes "合計は^FF0000" +'@mine+ "^000000！";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "私が^0000FF" +'@enemy+ "^000000で、";
		mes "^FF0000" +strcharinfo(0)+ "^000000さんが^FF0000" +'@mine+ "^000000ね。";
		if('@mine < '@enemy)  {	//負けてる場合
			mes "私が一歩リード！";
			mes "どう、サイコロをもう1個転がす？";
		}
		if('@mine > '@enemy) {	//勝ってる場合
			mes "^FF0000" +strcharinfo(0)+ "^000000さんが";
			mes "一歩リード！";
			mes "どう、サイコロをもう1個転がす？";
		}
		if('@mine == '@enemy) {	//同点の場合
			mes "同点だけれど、どうする？";
			mes "サイコロをもう1個転がす？";
		}
		next;
		if(select("うん","ううん")==1) {
			mes "-コロロン、コロンコロン、トン！-";
			next;
			set '@mine[3],rand(1,6);
			set '@mine[0],'@mine[0]+'@mine[3];
			mes "[" +strnpcinfo(1)+ "]";
			mes "^FF0000" +strcharinfo(0)+ "^000000さんの手は";
			mes "^FF0000" +'@mine[3]+ "^000000だから";
			mes "合計は^FF0000" +'@mine+ "^000000ね。";
			if('@mine > 12) {	//12を超えた場合
				mes "合計が12を超えちゃったから";
				mes "そっちの負け～！";
				mes "残念だったね。";
				close;
			}
			if('@mine < '@enemy) {	//負けてる場合
				mes "私の手の方がまだ大きいわ。残念！";
				mes "そっちの負け～！";
				close;
			}
			if('@mine == '@enemy) {	//同点の場合
				mes "同点か……何か嫌な予感がするから";
				mes "今回は引き分けにしようか。";
				mes "はい、最初に賭けたリンゴを返すわね。";
				getitem 512,'@apple;
				next;
				mes "[" +strnpcinfo(1)+ "]";
				mes "次は負けないわよ～。";
				close;
			}
			if('@mine > '@enemy) {	//勝ってる場合
				mes "次は私の番よ。";
			}
		}
		else {
			mes "[" +strnpcinfo(1)+ "]";
			if('@mine < '@enemy) {	//負けてる場合
				mes "えー、諦めるの？";
				mes "転がすだけ転がしてみればいいのに。";
				mes "……なら、私の勝ちになるわね。";
				mes "また遊びにおいでね。";
				mes "じゃあね～。";
				close;
			}
			if('@mine > '@enemy) {	//勝ってる場合
				mes "勝ってるんだから、";
				mes "無理することないもんね。";
			}
			if('@mine == '@enemy) {	//同点の場合
				mes "あら、転がさないの？";
			}
			mes "じゃあ、私は転がすわね。";
		}
		next;
		mes "-コロン、コロロロン！-";
		next;
		set '@enemy[3],rand(1,6);
		set '@enemy[0],'@enemy[0]+'@enemy[3];
		mes "[" +strnpcinfo(1)+ "]";
		mes "私の手は^0000FF" +'@enemy[3]+ "^000000だから、合計は^0000FF" +'@enemy+ "^000000ね。";
		if('@enemy > 12) {	//12を超えた場合
			mes "合計が12を超えちゃったから";
			mes "私の負けだ～！";
			mes "はい、リンゴよ。";
			mes "よかったら、また勝負しようね。";
			getitem 512,'@apple*2;
			close;
		}
		if('@mine > '@enemy) {	//勝った場合
			mes "合計が^FF0000" +'@mine+ "^000000の";
			mes "^FF0000" +strcharinfo(0)+ "^000000さんの勝ち！";
			mes "はい、リンゴよ。";
			mes "よかったら、また勝負しようね。";
			getitem 512,'@apple*2;
			close;
		}
		if('@mine < '@enemy) {	//負けた場合
			mes "合計が^FF0000" +'@mine+ "^000000の";
			mes "^FF0000" +strcharinfo(0)+ "^000000さんの負け！";
			mes "残念だったね。";
			close;
		}
		if('@mine == '@enemy) {	//同点の場合
			mes "これは、引き分けね！";
			mes "^FF0000" +strcharinfo(0)+ "^000000さんが";
			mes "最初に賭けたリンゴを返すわ。";
			mes "よかったら、また勝負しようね。";
			getitem 512,'@apple;
			close;
		}
	case 2:
		mes "[" +strnpcinfo(1)+ "]";
		mes "じゃあ、サイコロゲームのルールを";
		mes "説明するわね。とても簡単よ。";
		mes "まず、賭ける分だけの";
		mes "リンゴを私に預けてね。";
		mes "リンゴは50個まで賭けられるわ。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "次に、サイコロを2個転がすの。";
		mes "それで、サイコロの目の";
		mes "合計が多い方が勝ち！";
		mes "でも、それじゃあ簡単すぎるよね。";
		mes "だから、サイコロをもう1個";
		mes "転がすチャンスがあるのよ。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "サイコロをもう1個、転がすかどうかは";
		mes "本人の自由。但し！";
		mes "この段階でサイコロの目の合計が";
		mes "12を超えちゃったら、負けよ。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "3個目のサイコロを転がした場合、";
		mes "合計が12を超えちゃったら、";
		mes "その時点で負け決定よ。いい？";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "ゲームで勝った方は、自分と相手の";
		mes "賭けたリンゴを全部もらえるの。";
		mes "ね、簡単でしょ。";
		close;
	case 3:
		mes "[" +strnpcinfo(1)+ "]";
		mes "やってみたくなったら";
		mes "いつでも声かけてね。";
		mes "じゃあね～。";
		close;
	}
}

airplane.gat,33,69,4	duplicate(AirDice)	ケージ#Air	73
airplane_01.gat,33,69,4	duplicate(AirDice)	クラリス#Air	74

//callfunc "Typing#Einbroch","Name";
//  呼び出し元のNPC名前が引数
function	script	Typing#Air	{
	set '@t,gettimetick(0);
	switch(rand(7)) {	//出題文を配列に格納する
	case 0:
		setarray '@term$,"^39BDBD","スモモも桃も桃のうち、","^39BDBD","桃もスモモも桃のうち","",
				"^39BDBD","さくら咲く桜の山の桜花、","咲く桜あり散る桜あり"; break;
	case 1:
		setarray '@term$,"^39BDBD","マヤパープルオーガトゥース","^39BDBD","キャットナインテイル","",
				"^840084","黄金蟲エドガ月夜花","ドッペルゲンガーミストレス"; break;
	case 2:
		setarray '@term$,"^39BDBD","空きビンカタシムリの皮","^39BDBD","でっかいゼロピーリンゴ","",
				"^FF1094","赤ポーション黄ポーション","白ポーション青ポーション"; break;
	case 3:
		setarray '@term$,"^39BDBD","はなのいろは","^39BDBD","うつりにけりな","いたづらに",
				"^39BDBD","わがみよにふる","ながめせしまに"; break;
	case 4:
		setarray '@term$,"^0000FF","abcdefghijklmnopqrstuvwxyz","^39BDBD","1234567890","",
				"^FF1094","LoadKnightAssassin","PriestProfessorSniper"; break;
	case 5:
		setarray '@term$,"^39BDBD","グラディウスクレイモア","^39BDBD","パルチザンバトルアックス","",
				"^FF1094","たれ猫ウサギのヘアバンド","ピエロの鼻大きなリボン"; break;
	case 6:
		setarray '@term$,"^39BDBD","人を知る者は、智なり。","^39BDBD","自ら知る者は、明なり。","",
				"^FF1094","人に勝つ者は、力あり。","自ら勝つ者は、強し。"; break;
	}
	mes "[" +getarg(0)+ "]";
	mes '@term$[0] + '@term$[1];
	mes '@term$[2] + '@term$[3];
	mes '@term$[4] + "^000000";
	next;
	//3分経過してたらcloseする
	if(getarg(0) == "セキュリティシステム" && (gettimetick(0)-'@t) >= 180000)
		close;
	input '@typing1$;
	mes "[" +getarg(0)+ "]";
	mes '@term$[5] + '@term$[6];
	mes '@term$[7] + "^000000";
	next;
	if(getarg(0) == "セキュリティシステム" && (gettimetick(0)-'@t) >= 180000)
		close;
	input '@typing2$;
	if('@typing1$ != '@term$[1]+'@term$[3]+'@term$[4] || '@typing2$ != '@term$[6]+'@term$[7]) {
		if(getarg(0) == "セキュリティシステム") {
			mes "[セキュリティシステム]";
			mes "認証に失敗しました。";
		}
		else {
			mes "[" +getarg(0)+ "]";
			mes "正確に入力してください。";
		}
		close;
	}
	//開始時間と終了時間の差からタイピング秒を計算（ms以下切捨て）
	return (gettimetick(0)-'@t)/1000;
}

-	script	AirTyping	-1,{
	mes "[" +strnpcinfo(1)+ "]";
	mes "こんにちは！";
	mes "^FF0000タイピングラグナロク^000000の";
	mes "進行、" +strnpcinfo(1)+ "です！";
	next;
	switch (select("^FF0000タイピングラグナロク^000000に挑戦する","^FF0000タイピングラグナロク^000000の説明を聞く","最高記録を見る","取り消す")) {
	case 1:
		mes "[" +strnpcinfo(1)+ "]";
		mes "^FF0000タイピングラグナロク^000000に";
		mes "挑戦するのですね！";
		mes "では、これから提示する文章を";
		mes "出来るだけ早く、正確に";
		mes "入力してください。";
		mes "それでは始めます！";
		next;
		set '@time,callfunc("Typing#Air",strnpcinfo(1));	//タイピングタイムを取得
		set '@score,(1450/'@time)*6;
		if('@time < 0 || '@score < 0)
			set '@score,0;
		mes "[" +strnpcinfo(1)+ "]";
		mes "^FF0000" +'@time+ "秒^000000で正確に入力完了！";
		mes "スコアは" +'@score+ "と出ました！";
		next;
		if('@score >= 1300) {
			mes "[" +strnpcinfo(1)+ "]";
			mes "しかし、人間が出せる速度では";
			mes "ありませんね。";
			mes "何かズルでもしましたか？";
			mes "次は正々堂々と挑んでください。";
			close;
		}
		if('@score >= $TypingScore) {	//メッセージ未取得
			mes "[" +strnpcinfo(1)+ "]";
			mes "前回の最高スコアは、";
			mes "^0000FF" +$TypingName$+ "様^000000の";
			mes "^0000FF" +$TypingScore+ "^000000でしたが、";
			mes "^0000FF" +strcharinfo(0)+ "様^000000の記録が";
			mes "最高記録を更新されました！";
			mes "おめでとうございます！";
			set $TypingScore,'@score;
			set $TypingName$,strcharinfo(0);
		}
		else {
			mes "[" +strnpcinfo(1)+ "]";
			mes "現在の最高スコアは、";
			mes "^0000FF" +$TypingName$+ "様^000000の";
			mes "^0000FF" +$TypingScore+ "^000000です。";
			mes "次は是非、最高記録更新に";
			mes "挑戦してください！";
		}
		close;
	case 2:
		mes "[" +strnpcinfo(1)+ "]";
		mes "^FF0000タイピングラグナロク^000000は";
		mes "私が提示する文章を素早く、";
		mes "正確に入力するゲームです。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "スコアが一番高い方の記録は、";
		mes "殿堂入りとなります。";
		mes "タイピングに自信のある方は";
		mes "是非挑戦してください！";
		close;
	case 3:
		mes "[" +strnpcinfo(1)+ "]";
		mes "現在の最高スコアは、";
		mes "^0000FF" +$TypingName$+ "様^000000の";
		mes "^0000FF" +$TypingScore+ "^000000です。";
		close;
	case 4:
		mes "[" +strnpcinfo(1)+ "]";
		mes "^FF0000タイピングラグナロク^000000に";
		mes "挑戦したくなったら、";
		mes "いつでも来てください！";
		close;
	}
}

airplane.gat,32,61,4	duplicate(AirTyping)	ジョン#Air	51
airplane_01.gat,32,61,4	duplicate(AirTyping)	ニルス#Air	49

//============================================================
// ルーン機関クエストNPC
//- Registry -------------------------------------------------
// AIR_1QUE -> 0～7
//------------------------------------------------------------
airplane_01.gat,238,154,2	script	飛行船船長#Air	873,{
	cutin "fly_felrock",2;
	mes "[ペルロック]";
	mes "私が、この飛行船の船長ペルロックだ。";
	mes "私に何か用事でもあるのかね？";
	mes "うん？";
	next;
	switch(AIR_1QUE) {
	default: set '@word$,"飛行船はどうやって動いてるのですか？"; break;
	case 4: set '@word$,"トロック船長の手紙を渡す"; break;
	case 5:
	case 6: set '@word$,"船長が手紙を読み終えたのか、確認してみる"; break;
	}
	switch(select("何故、トナカイが船長なの？",'@word$,"何もありません")) {
	case 1:
		mes "[ペルロック]";
		mes "な……トナカイだと?!";
		mes "これだから人間の若者は駄目だな。";
		mes "礼儀がなってない！　礼儀が！";
		mes "ふざけたこと言ってると、";
		mes "下に投げ落とすぞ!!";
		next;
		mes "[ペルロック]";
		mes "私の一族は、代々、";
		mes "貴い血を受け継ぐ貴族だ。";
		mes "君達人間どもとは、格が違う！";
		mes "この巨大な飛行船の船長を";
		mes "引き受けることだって、";
		mes "生易しいことじゃないんだ。";
		next;
		mes "[ペルロック]";
		mes "まあ～、私にとって、";
		mes "飛行船で全世界を旅することは、";
		mes "楽しみでもあり";
		mes "人生の目的でもあるがな。";
		close2;
		cutin "fly_felrock",255;
		end;
	case 2:
		break;
	case 3:
		mes "[ペルロック]";
		mes "ああっ?!";
		mes "私は忙しいんだ！";
		mes "用がないなら話かけないでくれ！";
		close2;
		cutin "fly_felrock",255;
		end;
	}
	switch(AIR_1QUE) {
	case 0:
		mes "[ペルロック]";
		mes "飛行船がどうやって動くかって？";
		mes "そんなの、説明したところで";
		mes "素人には理解はできんよ。";
		set AIR_1QUE,1;
		break;
	case 1:
		mes "[ペルロック]";
		mes "前に同じ質問してきた奴がいたが……。";
		if(BaseLevel < 60) {
			mes "君のような人間のひよっこに";
			mes "教えることなどない！";
			break;
		}
		mes "ん？　そうか……";
		mes "あれは君だったか！";
		mes "そんなに知りたいのかね？";
		next;
		if(select("いいえ、そうではありませんが……","はい、知りたいです")==1) {
			mes "[ペルロック]";
			mes "大して興味がないことを";
			mes "また質問して、";
			mes "私の貴重な時間を奪うとは！";
			mes "そんなに外に放り出されたいのか?!";
			break;
		}
		mes "[ペルロック]";
		mes "大して興味がないことを";
		mes "また質問して、";
		mes "私の貴重な時間を奪うとは！";
		mes "そんなに外に放り出されたいのか?!";
		next;
		mes "[ペルロック]";
		mes "そうか……";
		mes "これは本来、船長達だけに";
		mes "知らされている機密事項だが……。";
		mes "とは言っても、上司達が";
		mes "そう考えてるだけだし……。";
		mes "ちょうど頼みたいことがあるしな……。";
		next;
		mes "[ペルロック]";
		mes "そうだな、私の頼みをきいてくれたら、";
		mes "教えてやってもいいぞ。";
		next;
		mes "[ペルロック]";
		mes "どうだ……";
		mes "悪い取り引きではないだろう？";
		mes "私の頼みをきいてくれるかね？";
		next;
		if(select("遠慮します","引き受けます")==1) {
			mes "[ペルロック]";
			mes "まあ、無理強いはしないよ。";
			mes "もし、考えが変わったらまた来てくれ。";
			break;
		}
		mes "[ペルロック]";
		mes "それなら話は早い。";
		mes "では、頼むことにしよう。";
		next;
		mes "[ペルロック]";
		mes "私には、私のように飛行船に乗って";
		mes "旅をしている弟がいる。";
		mes "だが……それぞれ飛行船に";
		mes "乗って旅をしていると、";
		mes "なかなか会うことができなくてな……。";
		mes "連絡をとる方法もほとんどないんだよ。";
		next;
		mes "[ペルロック]";
		mes "そこでだ。";
		mes "私が書いたこの手紙を";
		mes "我が弟に届け、";
		mes "その返事をもらってきてくれないか？";
		next;
		mes "-ペルロックから手紙を受け取った-";
		next;
		mes "[ペルロック]";
		mes "それではよろしくな。";
		set AIR_1QUE,2;
		break;
	default:
		mes "[ペルロック]";
		mes "飛行船がどうやって動くかって？";
		mes "まだ、私の弟から返事を";
		mes "もらってきてないだろ？";
		mes "私の手紙を届けた上で、";
		mes "返事をもらってきたら教えてやる。";
		break;
	case 4:
		mes "[ペルロック]";
		mes "おお！";
		mes "本当に返事をもらってきてくれたのか！";
		mes "実は、あまり期待は";
		mes "していなかったんだが……。";
		mes "手紙を読むから、";
		mes "ちょっと待っててくれ。";
		set AIR_1QUE,5;
		break;
	case 5:
		mes "[ペルロック]";
		mes "ううむ……ハハハッ！";
		mes "あいつめ、恋人ができたようだな。";
		mes "だが、真の男の、真の無敵の道は、";
		mes "無敵のソロ軍団だ……。";
		mes "うん？　俺は何を言ってるんだ？";
		mes "ブツブツ……。";
		next;
		mes "-まだ読み途中のようなので、";
		mes "もう少し待とう-";
		set AIR_1QUE,6;
		break;
	case 6:
		mes "[ペルロック]";
		mes "手紙は全部読んだ。";
		mes "あいつに会ったのなら分かるだろうが、";
		mes "私とは全く違う性格だろ？";
		mes "だから、小さい頃はよくケンカした。";
		mes "でも、二人一緒なら";
		mes "怖いものなしだったがな……。";
		next;
		mes "[ペルロック]";
		mes "ああ、そんな昔話ではなく、";
		mes "君が知りたがってたことを";
		mes "教えてやろう。";
		next;
		mes "[ペルロック]";
		mes "飛行船が浮かぶ基本原理はな……";
		mes "大型ボイラーに火をつけ、";
		mes "湯を沸かした時にでる蒸気の圧力で";
		mes "ピストンと歯車、タービンを動かして、";
		mes "プロペラを回しているんだ。";
		mes "な？　これで分かっただろ？";
		next;
		menu "え？　それだけ?!　もっと何かあるでしょ？",-;
		mes "[ペルロック]";
		mes "ハハハッ！";
		mes "大雑把に説明して終わらそうと思ったが";
		mes "君にはそれで通用しなかったか。";
		mes "君の言うとおり、今話したのは、";
		mes "誰もが知る基本原理だ。";
		next;
		mes "[ペルロック]";
		mes "確かに蒸気だけでは、";
		mes "この重い腹を空に浮かべるのは無理だ。";
		mes "そこで^FF0000ルーン機関^000000という";
		mes "増幅器を使うんだよ。";
		next;
		menu "ルーン機関？　それは何ですか？",-;
		mes "[ペルロック]";
		mes "魔法の石を使った装置だ。";
		mes "それをどうするかまでは、";
		mes "覚えてないが……。";
		mes "話を聞き流したせいか、";
		mes "詳しい名前も忘れたが……。";
		next;
		mes "[ペルロック]";
		mes "ユミ……なんだったかな？";
		mes "それのイミテーションを";
		mes "蒸気機関みたいなものに装着すると、";
		mes "その石から流れ出るルーンで";
		mes "エネルギーが増幅されるんだ。";
		next;
		mes "[ペルロック]";
		mes "実は親指ほどの石ころ一つで";
		mes "このでっかい腹が浮いていると";
		mes "言っても過言ではない。";
		mes "それだけ強い力があるからな。";
		next;
		mes "[ペルロック]";
		mes "これで納得したかね？";
		mes "私は、少し休むよ。";
		mes "手紙の読み書きで";
		mes "ちょっと疲れたからな。";
		misceffect 231,"";
		set AIR_1QUE,7;
		if(checkre())
			getexp 20000,1000;
		else
			getexp 200000,10000;
		break;
	case 7:
		mes "[ペルロック]";
		mes "前に教えてやっただろ？";
		mes "そんな面倒なこと、";
		mes "何度も聞くんじゃない！";
		break;
	}
	close2;
	cutin "fly_felrock",255;
	end;
}

airplane.gat,236,163,2	script	飛行船船長	873,{
	cutin "fly_trock",2;
	switch(HU_7QUE) {
	case 3:
	case 4:
		mes "[トロック]";
		mes "我が飛行船へのご乗船を";
		mes "歓迎いたします。";
		mes "私はこの飛行船の船長";
		mes "トロックと申します。";
		mes "何かございますか？";
		next;
		menu "ティオリという人を知らないか聞く",-;
		mes "[トロック]";
		mes "うーん……";
		mes "そのような名前は初耳ですね。";
		mes "少なくともこの飛行船の";
		mes "乗務員ではありません。";
		next;
		menu "搭乗者名簿を見る事ができるのか聞く",-;
		mes "[トロック]";
		mes "搭乗者リストはありますが、";
		mes "一般人には公開することができません。";
		mes "申し訳ありません。";
		if(HU_7QUE == 3)
			close;
		next;
		menu "事情を説明する",-;
		mes "-なぜティオリを探しているのか";
		mes "事情を説明している間、";
		mes "トロック船長は何もしゃべらず";
		mes "うなずいてばかりいた-";
		next;
		mes "[トロック]";
		mes "事情は充分よくわかりましたが、";
		mes "搭乗者名簿を一般人に";
		mes "公開しないことは原則です。";
		next;
		mes "[トロック]";
		mes "……しかし事情が事情です。";
		mes "今回だけは見逃しましょう。";
		mes "少し待ってください。";
		next;
		mes "-トロック船長はどこからか";
		mes "大きな名簿を取り出して";
		mes "白紙の1ページ目に";
		mes "「ティオリ」と書いた-";
		mes "-すると、字がうっすらと消えて、";
		mes "名簿のページが勝手にめくれだした-";
		next;
		mes "-しばらくして本が止まったページには";
		mes "ティオリの搭乗記録があった-";
		next;
		mes "[トロック]";
		mes "ハハッ。驚きましたか？";
		mes "この名簿には魔法がかかっていて、";
		mes "名前さえ書けば簡単にわかります。";
		next;
		mes "[トロック]";
		mes "昔の友達にいただいた代物で……";
		mes "あぁ、話が脱線してしまいましたね。";
		next;
		mes "[トロック]";
		mes "ティオリですね……";
		mes "ふむ、一ヶ月程前に乗船しています。";
		mes "目的地はフィゲル。";
		mes "ちょうどこの飛行船にフィゲル路線が";
		mes "追加された日ですね。";
		next;
		mes "[トロック]";
		mes "あぁ、そういえば。";
		mes "その人は研究家でしたね。";
		mes "思い出しましたよ。";
		next;
		mes "[トロック]";
		mes "フィゲル路線が追加されたその日、";
		mes "いきなりドラゴンに襲われました。";
		mes "何も準備をしていなかった私たちは";
		mes "危機的な状況に陥りました。";
		next;
		mes "[トロック]";
		mes "考えて見ればフィゲルという所は";
		mes "人が寄りつかない理由として";
		mes "ドラゴンがいるという話でした。";
		mes "私はすっかりその事を忘れていました。";
		next;
		mes "[トロック]";
		mes "機体は故障し、もうだめだと思った時、";
		mes "その青年が機体の修理を";
		mes "手伝ってくれて、なんとか";
		mes "ドラゴンから逃げる事ができました。";
		mes "その青年の名前が";
		mes "ティオリだったのですね。";
		next;
		mes "[トロック]";
		mes "どこか悲しそうな顔を";
		mes "していたのは";
		mes "そんな事情があったからですね……";
		mes "彼がどこに行ったのか";
		mes "早く婚約者の方に";
		mes "教えてあげてください。";
		next;
		mes "[トロック]";
		mes "もし彼に出会ったら、";
		mes "あの時は本当にありがとう";
		mes "と伝えてください。";
		set HU_7QUE,5;
		close2;
		cutin "fly_trock",255;
		end;
	case 5:
		mes "[トロック]";
		mes "はやく婚約者の方に";
		mes "彼がフィゲルに行った事を";
		mes "教えてあげてください。";
		close2;
		cutin "fly_trock",255;
		end;
	}
	switch(AIR_2QUE) {
	case 11:
		mes "[トロック]";
		mes "あ……";
		mes "いらっしゃいましたね。";
		mes "どの話からすればいいか";
		mes "わかりませんが……まず、";
		mes "あなたに聞きたい事があります。";
		next;
		mes "[トロック]";
		mes "あなたが";
		mes "ユミルの心臓のイミテーションを";
		mes "調査しようとしたのは、";
		mes "単純な好奇心からですか？";
		mes "それとも……";
		mes "他の何かを感じたからでしょうか？";
		next;
		if(select("単純な好奇心","何かを感じたから")==1) {
			mes "[トロック]";
			mes "それなら……";
			mes "あなたの好奇心は";
			mes "ここで止めた方がいいです。";
			mes "これは忠告ではなく、警告です。";
			close2;
			cutin "fly_trock",255;
			end;
		}
		mes "[トロック]";
		mes "…………";
		mes "あなたが信用できるか";
		mes "まだわかりませんが……";
		mes "危険とわかっていながらも";
		mes "研究所に忍び込んだのを見ると、";
		mes "本当に何かを感じたのでしょう。";
		next;
		mes "[トロック]";
		mes "……わかりました。";
		mes "その何かが";
		mes "私と同じかわかりませんが、";
		mes "少なくともあなたと私は";
		mes "敵対関係ではないでしょう。";
		next;
		mes "[トロック]";
		mes "……一つ約束してください。";
		mes "今から私が話す事は、";
		mes "他の誰にも話さないと。";
		next;
		menu "絶対秘密にすると約束する",-;
		mes "[トロック]";
		mes "わかりました。";
		mes "それではお話しましょう。";
		next;
		mes "[トロック]";
		mes "ご存知でしょうが、";
		mes "飛行船の動力源は";
		mes "ルーン機関と呼ばれる";
		mes "ユミルの心臓のイミテーションです。";
		next;
		mes "[トロック]";
		mes "ルーン機関は、";
		mes "ユミルの心臓に比べ";
		mes "その力は落ちます。";
		next;
		mes "[トロック]";
		mes "ですが、どこでどうやって";
		mes "生まれたのかわからず、";
		mes "数も少ないユミルの心臓とは違い、";
		mes "人間の手で";
		mes "作り上げることができる動力源……";
		next;
		mes "[トロック]";
		mes "それこそがルーン機関なのです。";
		next;
		mes "[トロック]";
		mes "そして、その製造所が……";
		mes "アインブロックの研究所。";
		mes "あなたが忍び込んだ所です。";
		next;
		mes "[トロック]";
		mes "大まかにでもいいです。";
		mes "わかりますか？";
		next;
		menu "バルムントプロジェクトとは一体？",-;
		mes "[トロック]";
		mes "大賢者バルムントのことは";
		mes "知っていますね？";
		mes "彼の業績は有名ですが、";
		mes "世に知られないこともあります。";
		next;
		mes "[トロック]";
		mes "例えば……";
		mes "そう……ルーン機関です。";
		mes "ルーン機関を生み出した人物こそ、";
		mes "大賢者バルムントなのです。";
		next;
		mes "[トロック]";
		mes "幼い頃から天才的な頭脳で、";
		mes "ジュノー国立大学の教授にまで";
		mes "抜擢されたバルムント。";
		next;
		mes "[トロック]";
		mes "彼は語学養成より、";
		mes "古代遺跡の発掘と";
		mes "科学研究に力を向けたと聞きます。";
		next;
		mes "[トロック]";
		mes "しかし、";
		mes "貧しい農夫の息子に生まれた";
		mes "バルムントが、研究を続けるには";
		mes "経済的に問題がありました。";
		next;
		mes "[トロック]";
		mes "そんなバルムントが選んだ道は、";
		mes "「企業」と手を組むことでした。";
		mes "そして、彼が残したルーン機関は";
		mes "企業の力となったのです。";
		next;
		mes "[トロック]";
		mes "ルーン機関は";
		mes "飛行船の動力源に使われますが、";
		mes "ガーディアンの動力源にも";
		mes "使われています。";
		next;
		mes "[トロック]";
		mes "しかし、現在のルーン機関は";
		mes "ユミルの心臓と違い、";
		mes "不完全な状態です。";
		next;
		mes "[トロック]";
		mes "なぜなら、";
		mes "ユミルの心臓のように";
		mes "永久に力を生み出すことができず、";
		mes "突如として力尽き、それ以上";
		mes "使うことができなくなるからです。";
		next;
		mes "[トロック]";
		mes "私があの日、";
		mes "研究所へ行ったのは";
		mes "力尽きる直前のルーン機関を";
		mes "交換するためだったのです。";
		next;
		mes "[トロック]";
		mes "私が知っている";
		mes "バルムントプロジェクトは、";
		mes "ルーン機関の不完全な要素を";
		mes "補うためのプロジェクトです。";
		mes "これ以上詳しい事は、";
		mes "私にもわかりません。";
		next;
		mes "[トロック]";
		mes "フゥ……";
		mes "一息いれましょう。";
		set AIR_2QUE,12;
		close2;
		cutin "fly_trock",255;
		end;
	case 12:
		mes "[トロック]";
		mes "それでは続けます。";
		mes "私がこんな話を";
		mes strcharinfo(0)+ "さんに";
		mes "するのには理由があります。";
		next;
		mes "[トロック]";
		mes "ここ最近…………";
		mes "このルーン機関を取り囲むように、";
		mes "何かが起ころうとしているように";
		mes "感じたからです。";
		next;
		mes "[トロック]";
		mes "私は、兄さんの飛行船が";
		mes "グレムリンとビホルダーに";
		mes "襲われたのを見た事があります。";
		next;
		mes "[トロック]";
		mes "元々グレムリンは、";
		mes "おぞましい外見とは裏腹に、";
		mes "他の生命体に自分から";
		mes "手を出すような事はしない、";
		mes "比較的大人しいモンスターです。";
		next;
		mes "[トロック]";
		mes "しかし、機械や装置を壊す、";
		mes "いたずら好きなモンスターです。";
		mes "そのグレムリンにも羽はありますが、";
		mes "空を飛ぶことはできません。";
		next;
		mes "[トロック]";
		mes "その、空を飛べないモンスターが、";
		mes "高度8000メートル上空を飛び回る";
		mes "飛行船を襲うことができますか？";
		next;
		mes "[トロック]";
		mes "何かがモンスターを空に上げ、";
		mes "飛行船に落としたとしか";
		mes "考えられません。";
		next;
		mes "[トロック]";
		mes "しかし、そのグレムリンが";
		mes "どうして自分から";
		mes "飛行船を襲ったのか。";
		mes "疑問が残りますね？";
		next;
		mes "[トロック]";
		mes "それについて調査していたら、";
		mes "飛行船を襲ったグレムリンの体内に";
		mes "暗黒の意志が埋め込まれている";
		mes "ということがわかりました。";
		next;
		mes "[トロック]";
		mes "暗黒の意志とは、";
		mes "それが埋め込まれた生物の";
		mes "精神を支配する恐ろしい代物です。";
		next;
		mes "[トロック]";
		mes "つまり、誰かが故意に";
		mes "グレムリンの体内へ";
		mes "暗黒の意志を埋め込み、";
		mes "飛行船を襲わせているのです。";
		next;
		mes "[トロック]";
		mes "この推測を裏付ける";
		mes "根拠の一つが、";
		mes "ビホルダーというモンスターが";
		mes "グレムリンといつも";
		mes "一緒に出現する事です。";
		next;
		mes "[トロック]";
		mes "ビホルダーは別名、";
		mes "注視者と呼ばれるモンスターで、";
		mes "召還した者の";
		mes "目の役割をしてくれます。";
		next;
		mes "[トロック]";
		mes "誰かが、";
		mes "グレムリンや他のモンスターに";
		mes "襲わせながら、ビホルダーを通して";
		mes "監視しているという事です。";
		next;
		mes "[トロック]";
		mes "ここで二つの疑問が出ます。";
		mes "一つは「なぜ」襲うのか。";
		mes "もう一つは「誰が」襲うのか。";
		mes "この二つです。";
		next;
		mes "[トロック]";
		mes "一つ目の疑問は簡単です。";
		mes "それは飛行船の動力源である";
		mes "ルーン機関、つまり";
		mes "ユミルの心臓のイミテーションを";
		mes "手に入れるためです。";
		next;
		mes "[トロック]";
		mes "しかし、二つ目の疑問である";
		mes "それを誰が狙い、";
		mes "どうして狙うのかは";
		mes "未だにわかっていません。";
		next;
		mes "[トロック]";
		mes "飛行船を襲ったグレムリンと";
		mes "ビホルダーから出る";
		mes "暗黒の意志とトゲの実から";
		mes "相手を突き止めようとしましたが、";
		mes "これが思ったより難しくて……";
		next;
		mes "[トロック]";
		mes "この前、";
		mes "兄さんにこの事を話したら、";
		mes "俺が調べると言って";
		mes "暗黒の意志とトゲの実を";
		mes "持って行ったことがありました。";
		next;
		mes "[トロック]";
		mes "しかし、その事を";
		mes "すっかり忘れてしまった上、";
		mes "それらをどこに置いたのかすら";
		mes "忘れてたようで…………";
		next;
		mes "[トロック]";
		mes "シュバルツバルド内部の人を";
		mes "疑いもしましたが、";
		mes "シュバルツバルド内だけを";
		mes "運行する私の飛行船を";
		mes "襲わない所を見ると、";
		mes "外部の人の方が怪しいですね。";
		next;
		mes "[トロック]";
		mes "犯人がわかったら誰なのか、";
		mes strcharinfo(0)+ "さんに";
		mes "真っ先に教えますね。";
		next;
		mes "[トロック]";
		mes strcharinfo(0)+ "さんも、";
		mes "何か新しい情報が手に入ったら";
		mes "私に教えてください。";
		next;
		mes "[トロック]";
		mes "私の知っていることはこれだけです。";
		mes "もう一度言いますが、";
		mes "この話は絶対に、誰にも";
		mes "話さないでください。";
		mes "それでは、またご連絡します。";
		close2;
		cutin "fly_trock",255;
		set AIR_2QUE,13;
		if(checkre())
			getexp 70000,40000;
		else
			getexp 700000,400000;
		misceffect 253,"";
		close2;
		cutin "fly_trock",255;
		end;
	case 13:
		mes "[トロック]";
		mes "最近、仕事がとても忙しいので";
		mes "あまり調査はできません。";
		mes "ですので、私が新しい情報を";
		mes "得るのは難しいでしょう……";
		close2;
		cutin "fly_trock",255;
		end;
	}
	mes "[トロック]";
	mes "我が飛行船へのご乗船を";
	mes "歓迎いたします。";
	mes "私はこの飛行船の船長";
	mes "トロックと申します。";
	mes "何かございますか？";
	next;
	if(AIR_1QUE == 2) set '@word$,"ペルロック船長の手紙を渡す";
	else if(AIR_1QUE == 3) set '@word$,"船長に頼まれた物を渡す";
	switch(select("飛行船はどうやって動いてるのですか？",'@word$,"特にありません")) {
	case 1:
		mes "[トロック]";
		mes "申し訳ございません。";
		mes "それに関しては、";
		mes "船長達だけに知らされている";
		mes "機密事項となりますので……。";
		mes "一般の方々にお教えすることは";
		mes "できません。ご了承ください。";
		close2;
		cutin "fly_trock",255;
		end;
	case 2:
		break;
	case 3:
		mes "[トロック]";
		mes "それでは、よい旅になるといいですね。";
		close2;
		cutin "fly_trock",255;
		end;
	}
	switch(AIR_1QUE) {
	case 2:
		mes "-ペルロック船長の手紙を";
		mes "トロック船長に渡した-";
		next;
		mes "[トロック]";
		mes "おや……";
		mes "兄からの手紙ですか。";
		mes "お忙しい中、";
		mes "わざわざ届けていただいて";
		mes "ありがとうございます。";
		mes "少々お待ちください。";
		next;
		mes "-トロック船長は、手紙を読み始めた-";
		next;
		mes "[トロック]";
		mes "うーん……ハハッ……";
		mes "兄さんたら……。";
		mes "ううん……うーん……";
		mes "うん？……ハハハッ！";
		mes "……へぇ～、そんな事が……";
		mes "ううん……ブツブツ……。";
		next;
		mes "[トロック]";
		mes "はい、読みました。";
		mes "お待たせして申し訳ありません。";
		next;
		mes "[トロック]";
		mes "兄が私に手紙をよこすのは、";
		mes "安否を確認するためではありますが……";
		mes "今回は、この前、兄が私から借りた物を";
		mes "返すためでもありました。";
		next;
		mes "[トロック]";
		mes "私にとって必要な物です。";
		mes "ところが、兄はどうやらその品物を";
		mes "なくしてしまったようで……。";
		mes "手紙にはこう書いてありますね。";
		next;
		mes "[トロック]";
		mes "^FF0000「この手紙を持って来てくれた人が、";
		mes "その品物を渡してくれるだろう。";
		mes "だがもし、その人が品物を";
		mes "渡してくれなかったら、";
		mes "私に返事をよこさないでくれ。」^000000とね。";
		next;
		mes "[トロック]";
		mes "兄に何か弱点でも";
		mes "握られているんですか？";
		mes "ハッハッ！";
		mes "まあ、私には必要な物なので、";
		mes "持ってきていただければと思います。";
		next;
		mes "[トロック]";
		mes "お願いしたい品物は、";
		mes "^FF0000暗黒の意志2個^000000と";
		mes "^FF0000トゲの実2個^000000です。";
		next;
		mes "[トロック]";
		mes "あと、聞いた話によると、";
		mes "兄の飛行船をたまに";
		mes "襲う連中がいるそうです。";
		mes "詳しいことは分かりませんが……。";
		mes "それではお願いしますね。";
		set AIR_1QUE,3;
		break;
	case 3:
		if(countitem(7340) < 2 || countitem(576) < 2) {
			mes "[トロック]";
			mes "おや？";
			mes "まだ頼んだ品が";
			mes "揃っていないようですが……。";
			mes "念のため、もう一度";
			mes "申し上げましょうか。";
			next;
			mes "[トロック]";
			mes "^FF0000暗黒の意志2個^000000と";
			mes "^FF0000トゲの実2個^000000を";
			mes "集めてきてください。";
			mes "それではよろしくお願いします。";
			break;
		}
		delitem 7340,2;
		delitem 576,2;
		set AIR_1QUE,4;
		mes "[トロック]";
		mes "持ってきてくださいましたか！";
		mes "本当にありがとうございます。";
		mes "兄への手紙はこちらです。";
		next;
		mes "-船長から手紙を受けとった-";
		next;
		mes "[トロック]";
		mes "兄によろしくお伝えください。";
		mes "それではよい一日を。";
		break;
	}
	close2;
	cutin "fly_trock",255;
	end;
}

//============================================================
// ユミルの心臓クエストNPC
//- Registry -------------------------------------------------
// AIR_2QUE -> 0～13
//------------------------------------------------------------
airplane.gat,236,63,4	script	ヘイルレン	706,{
	if(HU_7QUE == 3) {
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "飛行船の仕事なら";
		mes "僕に任せな！";
		mes "ヘヘッ。";
		next;
		menu "ティオリという人を知らないか聞く",-;
		mes "[ヘイルレン]";
		mes "ティオリ？";
		mes "う～ん……知らないな～";
		mes "他の人にも聞いてみてよ。";
		mes "ケージ姉ちゃんなら知ってるかも。";
		close;
	}
	switch(AIR_2QUE) {
	case 0:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		if(BaseLevel < 60) {
			mes "[ヘイルレン]";
			mes "飛行船の仕事なら";
			mes "僕に任せな！";
			mes "ヘヘッ。";
			close;
		}
		mes "[ヘイルレン]";
		mes "ん？　乗客の人？";
		mes "こにちわぁ～";
		next;
		if(select("乗客じゃないよ？","ここで何してるの？")==1) {
			emotion 1;
			mes "[ヘイルレン]";
			mes "乗客じゃないって……乗務員？";
			mes "あれれ～？　見た事ない顔……";
			mes "まさか、僕がまだ" +(Sex? "兄": "姉")+ "ちゃんたちの";
			mes "顔を覚えられてない!?";
			next;
			mes "[ヘイルレン]";
			mes "…………!!";
			next;
			emotion 0;
			mes "[ヘイルレン]";
			mes "アッ！";
			mes "よく見たら服が";
			mes "全然違うじゃん！";
			mes "僕がまだ小さいからって";
			mes "バカにするなよッ！";
			next;
			mes "[ヘイルレン]";
			mes "びっくりしたなぁ。";
			mes "もぅ～";
		}
		else {
			mes "[ヘイルレン]";
			mes "見てわからない？";
			mes "甲板の掃除中に決まってるじゃん。";
			mes "僕が一番小っちゃいから、";
			mes "こういう仕事は";
			mes "押し付けられるんだよ。";
			next;
			mes "[ヘイルレン]";
			mes "さてと、";
		}
		mes "掃除をさっさと終わらせて、";
		mes "ケージ姉ちゃんとこに遊びに";
		mes "行こっと。";
		next;
		menu "ケージ……お姉さん？",-;
		mes "[ヘイルレン]";
		mes "ん……？";
		mes "飛行船の中でサイコロゲームを";
		mes "している人、知らない？";
		mes "退屈ならやってみたら？";
		next;
		mes "[ヘイルレン]";
		mes "サイコロを転がして、";
		mes "勝った方がリンゴを取るゲームだよ。";
		mes "あんまり勝ちすぎちゃったから、";
		mes "手に入れたリンゴで商売をする人が";
		mes "近くにいるぐらいだよ。";
		next;
		mes "[ヘイルレン]";
		mes "実はその話、ウソだと思って";
		mes "姉ちゃんに聞いてみたら……";
		mes "本当なんだってさ。";
		mes "すごいよね～";
		next;
		mes "[ヘイルレン]";
		mes "あ、この話は秘密だった！";
		mes "…………へへ、まいっか。";
		mes "それじゃ、僕はまだ仕事があるから。";
		mes "また今度ね、" +(Sex? "兄": "姉")+ "ちゃん。";
		set AIR_2QUE,1;
		close;
	case 1:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "オッ？";
		mes "前に会った" +(Sex? "兄": "姉")+ "ちゃんだね。";
		mes "こにちわぁ～っと。";
		mes "今日も熱心に掃除中だ！";
		next;
		emotion 0;
		mes "[ヘイルレン]";
		mes "あ！";
		mes "ちょっと";
		mes "お願いがあるんだけどいいかな？";
		mes "簡単だからさ、ね？";
		next;
		if(select("今忙しくて……ごめん","何？　簡単ならいいけど……")==1) {
			mes "[ヘイルレン]";
			mes "そっか……忙しいならいいよ。";
			mes "掃除を終わらせてから";
			mes "自分でするから……";
			mes "じゃ、僕は掃除を続けるから。";
			close;
		}
		mes "[ヘイルレン]";
		mes "ヘヘッ。サンキューサンキュー。";
		mes "そう難しい事じゃないよ。";
		next;
		mes "[ヘイルレン]";
		mes "定期的に乗務員のみんなに";
		mes "送られてる手紙を、";
		mes "ジュノー空港で僕が集めてるんだ。";
		mes "その中にケージ姉ちゃんへの";
		mes "手紙があってね。";
		next;
		mes "[ヘイルレン]";
		mes "今、掃除で忙しいから";
		mes "僕の代わりにこれを";
		mes "ケージ姉ちゃんに届けてよ。";
		mes "マウォングって人からの手紙だけど、";
		mes "姉ちゃんのお師匠様ということしか";
		mes "僕も知らないよ。";
		next;
		mes "-ヘイルレンから手紙を受けとった-";
		next;
		mes "[ヘイルレン]";
		mes "ケージ姉ちゃんは飛行船の中にいるよ。";
		mes "頼んだよ～";
		set AIR_2QUE,2;
		close;
	case 2:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "ふぅ……";
		mes "これ、いつ終わるんだ……";
		mes "サッサッサ…………";
		next;
		mes "[ヘイルレン]";
		mes "あ、" +(Sex? "兄": "姉")+ "ちゃん！";
		mes "ケージ姉ちゃんに手紙は渡した？";
		close;
	case 3:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "これ、いつ終わるんだ……";
		mes "サッサッサ…………";
		close;
	case 4:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "あ！　こにちわぁ～";
		mes "この前頼んだ手紙、ありがとね。";
		next;
		mes "[ヘイルレン]";
		mes "でも、ケージ姉ちゃんに";
		mes "乗客の方に面倒にかけるなって";
		mes "怒られちゃったよ……ちぇっ。";
		next;
		mes "[ヘイルレン]";
		mes "人間関係っていうのは";
		mes "忙しい時はお互いに";
		mes "助け合うことだとは思わない？";
		next;
		if(select("…………","そうだね。助け合わないといけない")==1) {
			mes "[ヘイルレン]";
			mes "どうして何も言わないのさ。";
			mes "もしかして、薄情者？";
			set AIR_2QUE,5;
			close;
		}
		mes "[ヘイルレン]";
		mes "おぉッ！";
		mes "やっぱり" +(Sex? "兄": "姉")+ "ちゃんは話がわかるね！";
		mes "そんな" +(Sex? "兄": "姉")+ "ちゃんには";
		mes "これをあげよう！";
		next;
		mes "[ヘイルレン]";
		mes "ヘヘッ。";
		mes "危ない時にでも使ってよ。";
		mes "それじゃ、僕は掃除をするから。";
		mes "またね～";
		set AIR_2QUE,5;
		getitem 501,1;
		close;
	case 5:
		mes "[ヘイルレン]";
		mes (Sex? "兄": "姉")+ "ちゃ～ん。";
		mes "こにちわぁ～";
		next;
		menu "今日は掃除をしないの？",-;
		mes "[ヘイルレン]";
		mes "僕がいっつも掃除だけ";
		mes "していると思った？";
		mes "僕だってたまには休むよ。";
		next;
		mes "[ヘイルレン]";
		mes "僕にも趣味があるんだ。";
		mes "ジュノーで暮らしている時、";
		mes "隣の家にイボって兄ちゃんがいて、";
		mes "兄ちゃんは本当に何でも作れる";
		mes "万能博士だったんだ。";
		next;
		mes "[ヘイルレン]";
		mes "その兄ちゃんが";
		mes "僕の理想なんだ。";
		mes "僕も不思議な物を";
		mes "いっぱい作って";
		mes "イボ兄ちゃんみたいになりたいんだ。";
		next;
		mes "[ヘイルレン]";
		mes "大賢者バルムント";
		mes "とまでは言わないけど、";
		mes "色んな物を作って、";
		mes "人々に喜ばれたいんだ。";
		mes "夢にしては大きすぎるかな？";
		mes "アハハッ。";
		next;
		menu "大賢者バルムント？",-;
		mes "[ヘイルレン]";
		mes "うん。え？　何？";
		mes "大賢者バルムントを知らない？";
		next;
		mes "[ヘイルレン]";
		mes "うーん……";
		mes "僕も聞いた話だから";
		mes "あまり詳しくは知らないけど……";
		next;
		mes "[ヘイルレン]";
		mes "300年ぐらい前に";
		mes "バルムントっていう人が、";
		mes "たくさんの業績を残したことで";
		mes "大賢者になったんだって。";
		next;
		mes "[ヘイルレン]";
		mes "僕たちが今、";
		mes "こんなに便利な生活していることも";
		mes "み～んなその人のおかげらしいよ。";
		next;
		mes "[ヘイルレン]";
		mes "だけど、その人はいきなり";
		mes "行方不明になっちゃったんだって。";
		mes "どこにいるのか誰にもわからなくて、";
		mes "やがて、人々の間では";
		mes "伝説のような人になったんだってさ。";
		next;
		mes "[ヘイルレン]";
		mes "こんなとこかな……";
		mes "そういえば、" +(Sex? "兄": "姉")+ "ちゃんは";
		mes "この飛行船の事、";
		mes "よく知ってる？";
		next;
		menu "どうして急に飛行船？",-;
		mes "[ヘイルレン]";
		mes "飛行船はすごく大きくて重いのに、";
		mes "こんなのがどうやって";
		mes "空に飛んでるのか知りたくない？";
		mes "さっきも言ったけど、";
		mes "僕はなんでも作りたいんだ。";
		next;
		mes "[ヘイルレン]";
		mes "だから、僕はこの飛行船について";
		mes "隅々まで知りたいんだ。";
		mes "でも、どうしてもこんな重いのが";
		mes "人を乗せて動けるのか";
		mes "全然わからなくて……うーん……";
		set AIR_2QUE,6;
		close;
	case 6:
		mes "[ヘイルレン]";
		mes (Sex? "兄": "姉")+ "ちゃんは飛行船が";
		mes "どうやって動いてるか";
		mes "知ってる？";
		next;
		if(AIR_1QUE < 7) {
			menu "うーん……私にもわからない",-;
			mes "[ヘイルレン]";
			mes "そっか……";
			mes "やっぱわかんないよね。";
			mes "トロック船長なら";
			mes "知ってるだろうけど";
			mes "聞いてみたら機密だからって";
			mes "教えてくれないんだよ。ちぇっ。";
			next;
			mes "[ヘイルレン]";
			mes (Sex? "兄": "姉")+ "ちゃんからもちょっと";
			mes "聞いてみてくれない？";
			mes "トロック船長が教えてくれないなら、";
			mes "他の船員でもいいからさ。";
			next;
			mes "[ヘイルレン]";
			mes "どうしても知りたいんだ。";
			mes "わかったら、また後で";
			mes "教えてよね！";
			mes "頼んだよ！";
			next;
			mes "-ヘイルレンは私が考える間もなく、";
			mes "話を切り上げて";
			mes "仕事に集中し始めた-";
			close;
		}
		menu "うん……知ってる",-;
		mes "[ヘイルレン]";
		mes "えッ？　本当!?";
		mes "本当に知ってるの!?";
		mes "教えて!!";
		mes "どうやって、こんな大きくて重い";
		mes "飛行船が浮いてるの!?";
		next;
		mes "-ペルロック船長に聞いた話を";
		mes "ユミルの心臓のイミテーションの";
		mes "部分を除いてヘイルレンに教えた-";
		next;
		mes "[ヘイルレン]";
		mes "うん、うん。";
		mes "簡単にいうと、水蒸気を利用して";
		mes "プロペラを回してるんだね。";
		next;
		mes "[ヘイルレン]";
		mes "……でも、この重い飛行船が";
		mes "そんな単純な機械で浮かぶの？";
		mes "もっと、違う何かがあるんじゃ……";
		next;
		mes "[ヘイルレン]";
		mes "本当に聞いたのはそれだけなの？";
		next;
		menu "ルーン機関について教える",-;
		mes "-子供になら事実を教えても";
		mes "問題はないだろうと思い、";
		mes "ルーン機関、つまり";
		mes "ユミルの心臓のイミテーション";
		mes "について話した-";
		next;
		mes "[ヘイルレン]";
		mes "えッ？　本当にそんな物があるの？";
		mes "わ！　ホント？　すごい！";
		mes "……あれ？";
		mes "なんだかユミルって言葉に";
		mes "聞き覚えが……";
		next;
		mes "[ヘイルレン]";
		mes "どっかで聞いたような……";
		mes "う～ん……";
		mes "ちょっと思い出してみる。";
		set AIR_2QUE,7;
		close;
	case 7:
		mes "[ヘイルレン]";
		mes "うーん……思い出せないや。";
		mes "どっかで聞いたことあるんだけど……";
		mes "どこだったかなぁ……";
		next;
		emotion 0;
		mes "[ヘイルレン]";
		mes "あッ！　思い出した!!";
		mes "それ、ケージ姉ちゃんの所で";
		mes "聞いたんだ！";
		next;
		menu "ケージお姉さんの所？",-;
		mes "[ヘイルレン]";
		mes "うん！";
		mes "姉ちゃんがサイコロゲームする所で";
		mes "いっつもお酒を飲んでいるおじさんが";
		mes "そんなこと言ってた！";
		next;
		if(EIN_3QUE == 11) {
			mes "（そういえばこの前、";
			mes "シドクスさんの頼みを";
			mes "聞いた時に";
			mes "そんな人に会ったことがあった）";
			next;
			mes "（あの人は確か";
			mes "ユミルの心臓の欠片がある";
			mes "アインブロックの";
			mes "研究所所長だった気が……）";
			next;
			mes "（ん？　それなら";
			mes "ユミルの心臓のイミテーションが";
			mes "アインブロック研究所にある";
			mes "ユミルの心臓の欠片に";
			mes "何か関係しているんじゃ？";
			mes "一度調べてみたほうがいいだろう）";
			next;
		}
		mes "[ヘイルレン]";
		mes "とにかく" +(Sex? "兄": "姉")+ "ちゃん。";
		mes "飛行船について教えてくれて";
		mes "ありがとね。";
		mes "安物だけど、これをあげるよ！";
		next;
		mes "[ヘイルレン]";
		mes "ヘヘッ。";
		mes "そう感動する物じゃないよね。";
		mes "それじゃ、僕は仕事があるから。";
		mes "今度またね。";
		mes "ばいば～い。";
		if(EIN_3QUE == 11)
			set AIR_2QUE,9;
		else
			set AIR_2QUE,8;
		getitem 501,1;
		close;
	case 8:
		mes "[ヘイルレン]";
		mes "ケージ姉ちゃんに";
		mes "その酔ったおじさんについて";
		mes "聞いてみてよ。";
		mes "いっつも来てるから、";
		mes "姉ちゃんなら何か知ってるかも。";
		close;
	default:
		mes "[ヘイルレン]";
		mes "サッサッサ～";
		mes "お掃除サッサ～";
		next;
		mes "[ヘイルレン]";
		mes "あ、この前はありがとね。";
		mes "ヘヘッ。";
		mes "僕もいつかはこんな、";
		mes "大きい飛行船を作ってやるんだッ！";
		close;
	}
}

ein_in01.gat,279,25,0	script	#研究所入口	139,1,1,{
	if(AIR_2QUE == 9) {
		mes "（研究所の中を探せば、";
		mes "何か出るかも知れない）";
		close;
	}
}

ein_in01.gat,264,17,0	script	#暗号チェック機	139,1,1,{
	if(AIR_2QUE == 9) {
		mes "（ん!?　これは……？";
		mes "暗号チェック機？";
		mes "……どうやら、";
		mes "暗号がどれだけ正しいか";
		mes "チェックしてくれる機械のようだ）";
		next;
		mes "-暗号チェック機を動かした-";
		set AIR_2QUE,10;
		close;
	}
}

ein_in01.gat,261,35,0	script	#暗号入力機	139,1,1,{
	if(AIR_2QUE == 9 || AIR_2QUE == 10) {
		mes "（ん!?　何かある）";
		next;
		mes "（……どうやら暗号が";
		mes "必要みたいだ）";
		next;
		mes "^FF0000[三桁の数字を合わせる。";
		mes "0を使わず、重複もしない。";
		mes "一回につき3分以内に";
		mes "入力しなければならない。";
		mes "10回間違えた場合、";
		mes "暗号は変更される。]^000000";
		next;
		if(AIR_2QUE == 9) {
			mes "（……と書いている。";
			mes "このまま暗号を合わせるのは";
			mes "とても難しいな……";
			mes "近くに何かないか探してみよう）";
			close;
		}
		mes "（……と書いてある。";
		mes "さっきの暗号チェック機を利用して";
		mes "数字を3個入力してみよう）";
		next;
		mes "[セキュリティシステム]";
		mes "暗号を入力してください。";
		mes "0を使わず重複もしない";
		mes "三個の数字を入力してください。";
		mes "入力範囲を超過する値を入力すると、";
		mes "認証が取り消されます。";
		next;
		set '@cnt,10;
		setarray '@num$[2],"二","三","四","五","六","七","八","九";
		setarray '@list,1,2,3,4,5,6,7,8,9;
		for(set '@i,0; '@i < 3; set '@i,'@i+1) {
			set '@r,rand(getarraysize('@list));
			set '@ans['@i],'@list['@r];
			deletearray '@list['@r],1;
		}
		while(1) {
			input '@temp;
			if('@temp < 100 || '@temp > 999) {
				mes "[セキュリティシステム]";
				mes "入力値の範囲を超過しました。";
				mes "認証は取り消されます。";
				close;
			}
			setarray '@num,'@temp/100,'@temp%100/10,'@temp%100%10;
			if('@num[0] == 0 || '@num[1] == 0 || '@num[2] == 0 || '@num[0] == '@num[1] || '@num[1] == '@num[2] || '@num[0] == '@num[2]) {
				mes "[セキュリティシステム]";
				mes "入力された値に";
				mes "0が入っているか、";
				mes "重複されています。";
				mes "再度入力してください。";
				next;
				continue;
			}
			mes "[セキュリティシステム]";
			mes "^FF0000" +strcharinfo(0)+ "^000000様が入力した数値は";
			mes "^0000FF" +'@num[0]+ "^000000, ^0000FF" +'@num[1]+ "^000000, ^0000FF" +'@num[2]+ "^000000 です。";
			mes "認証結果を表示します。";
			next;
			if('@num[0] == '@ans[0])
				set '@match,'@match+1;
			if('@num[0] == '@ans[1] || '@num[0] == '@ans[2])
				set '@shift,'@shift+1;
			if('@num[1] == '@ans[1])
				set '@match,'@match+1;
			if('@num[1] == '@ans[0] || '@num[1] == '@ans[2])
				set '@shift,'@shift+1;
			if('@num[2] == '@ans[2])
				set '@match,'@match+1;
			if('@num[2] == '@ans[0] || '@num[2] == '@ans[1])
				set '@shift,'@shift+1;
			if('@match == 3)
				break;
			mes "[セキュリティシステム]";
			mes "エラー！";
			mes "暗号が違います。";
			next;
			mes "[暗号チェック機]";
			mes "数字と桁数が合っているのは^FF0000" +'@match+ "^000000個";
			mes "数字だけ合っているのは^FF0000" +'@shift+ "^000000個です。";
			next;
			set '@match,0;
			set '@shift,0;
			set '@cnt,'@cnt-1;
			if('@cnt > 1)
				mes "（チャンスはあと" +'@num$['@cnt]+ "回だ。";
			else if('@cnt == 1)
				mes "（最後のチャンスだ。";
			else {
				mes "（正解は^FF0000" +'@ans[0]+ "^000000,^FF0000" +'@ans[1]+ "^000000,^FF0000" +'@ans[2]+ "^000000";
				mes "だったようだ。";
				mes "しかし、10回の失敗で";
				mes "暗号が変わってしまった。）";
				close;
			}
			mes "暗号チェック機の結果を元に";
			mes "暗号を考えよう。）";
			next;
			continue;
		}
		mes "[セキュリティシステム]";
		mes "認証が確認されました。";
		mes "文書の閲覧が可能となりました。";
		next;
		mes "（暗号を合わせると";
		mes "文書が入っているドアが開いた。";
		mes "いくつもの文書が入っていたが、";
		mes "その中でも特に目立つ書類がある）";
		next;
		mes "-バルムントプロジェクト　No.3-";
		mes "-保安レベル：1級　C-";
		next;
		mes "-注意：このプロジェクトは、完璧な";
		mes "ユミルの心臓のイミテーションを";
		mes "製作するためのプロジェクトである-";
		next;
		mes "-この文書は1級のCにあたる";
		mes "保安レベルにより、";
		mes "プロジェクト参加者を除いた者が";
		mes "この文書を扱うと、";
		mes "摘発時に懲戒を受けるので、";
		mes "注意してください-";
		next;
		mes "（やっぱり……";
		mes "ユミルの心臓のイミテーションは";
		mes "ここと関連があったな……";
		mes "どの書類から読んでみるか……）";
		next;
		mes "-トン、トン、トン-";
		next;
		mes "（アッ……誰か来た！）";
		next;
		mes "-いそいで書類を元通りにしたが、";
		mes "見つかってしまったようだ-";
		next;
		hideoffnpc "トロック#Air";
		initnpctimer "トロック#Air";
		mes "[トロック]";
		mes "失礼します。";
		mes "研究員の方でしょうか？";
		mes "ルーン機関の交換をしに……";
		next;
		mes "[トロック]";
		mes "……あれ!?";
		mes "見覚えがあるような……";
		mes "どこかでお会い……";
		next;
		emotion 23,"トロック#Air";
		mes "[トロック]";
		mes "アッ!!";
		mes "以前、兄さんの手紙を";
		mes "届けてくれた方ですね！";
		next;
		mes "[トロック]";
		mes "……そして、";
		mes "兄に飛行船がどうやって動くか";
		mes "聞いていましたよね……";
		mes "ここの研究員なら、";
		mes "そんな質問はしないはず……";
		next;
		mes "[トロック]";
		mes "そして、関係者以外入れない";
		mes "ここにいらっしゃるのは……";
		mes "大まかにですが見当がつきますね。……";
		next;
		mes "[トロック]";
		mes "あ、安心してください。";
		mes "警備を呼ぶつもりはありません。";
		mes "場所が場所なので、今は";
		mes "詳しいことも聞きません。";
		next;
		mes "[トロック]";
		mes "ここは時間ごとに警備が入って来て、";
		mes "研究員たちをチェックしています。";
		mes "早く外に出てください。";
		next;
		mes "[トロック]";
		mes "詳しい話は後で私のところで。";
		mes "さぁ……急いでください！";
		close2;
		set AIR_2QUE,11;
		stopnpctimer "トロック#Air";
		hideonnpc "トロック#Air";
		end;
	}
}

ein_in01.gat,263,35,2	script	トロック#Air	873,{
	end;
OnTimer120000:
	stopnpctimer;
OnInit:
	hideonnpc;
	end;
}
