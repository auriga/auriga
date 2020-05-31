//= Auriga Script ==============================================================
// Ragnarok Online Flame Valley Town Script　　by refis
//==============================================================================

//============================================================
// Shop
//------------------------------------------------------------
moro_vol.gat,95,96,6	shop	道具商人	553,717,611,504,525,610,645,656,657,601,602,1065

//============================================================
// 案内要員
//------------------------------------------------------------
moro_vol.gat,144,140,3	script	案内兵	469,{
	mes "[案内兵]";
	mes "魔王モロクを倒そうと、";
	mes "このフレイムヴァレーに";
	mes "人間、サファ族、ラフィネ族が";
	mes "次々と集結しています！";
	mes "おかげで連合軍の人数は";
	mes "すごい数に膨れ上がっています！";
	next;
	mes "[案内兵]";
	mes "ただ……その影響でどこに誰がいるのか";
	mes "わからず、迷ってしまう人が";
	mes "増えているんです。";
	mes "私はそんな人を見つけたら";
	mes "行先を案内するよう命じられました。";
	mes "誰か会いたい人はいますか？";
	next;
	switch(select("司令官アジフ","参謀アビダル","教官長イグリド","大臣ヘスランタ","ヒシエ","魔学者","守護者ニーズヘッグ","駐屯地調査官","特にいない")) {
	case 1:
		set '@name$,"司令官アジフ";
		set '@x,107;
		set '@y,85;
		break;
	case 2:
		set '@name$,"参謀アビダル";
		set '@x,107;
		set '@y,85;
		break;
	case 3:
		set '@name$,"教官長イグリド";
		set '@x,107;
		set '@y,85;
		break;
	case 4:
		set '@name$,"大臣ヘスランタ";
		set '@x,139;
		set '@y,80;
		break;
	case 5:
		set '@name$,"ヒシエ";
		set '@x,96;
		set '@y,105;
		break;
	case 6:
		set '@name$,"魔学者";
		set '@x,96;
		set '@y,105;
		break;
	case 7:
		set '@name$,"守護者ニーズヘッグ";
		set '@x,96;
		set '@y,105;
		break;
	case 8:
		set '@name$,"駐屯地調査官";
		set '@x,131;
		set '@y,100;
		break;
	case 9:
		mes "[案内兵]";
		mes "そうですか。";
		mes "案内が必要なときは";
		mes "遠慮なく声をかけてくださいね。";
		close;
	}
	mes "[案内兵]";
	mes "^ff0000" +'@name$+ "^000000の";
	mes "ところで良いですか？";
	next;
	if(select("はい","やっぱりやめる") == 2) {
		mes "[案内兵]";
		mes "そうですか。";
		mes "案内が必要なときは";
		mes "遠慮なく声をかけてくださいね。";
		close;
	}
	mes "[案内兵]";
	mes "では私に着いて来てください。";
	close2;
	warp "moro_vol.gat",'@x,'@y;
	end;
OnInit:
	waitingroom "フレイムヴァレー案内",0;
	end;
}

moro_vol.gat,91,105,1	script	次元移動機	10007,{
	mes "[ドフィ]";
	mes "それはエクラージュに";
	mes "繋がっている次元移動機です。";
	mes "この作戦が終われば破棄される";
	mes "ものですが、なかなか便利ですよ。";
	next;
	mes "‐次元移動機を使いますか？";
	mes "　エクラージュに移動します‐";
	next;
	if(select("エクラージュに移動","やめる") == 2) {
		mes "‐使用を中止します‐";
		close;
	}
	mes "‐エクラージュに移動します‐";
	close2;
	warp "ecl_in01.gat",38,96;
	end;
}

moro_vol.gat,88,107,5	script	魔学者ドフィ	440,{
	mes "[ドフィ]";
	mes "……ほう。";
	mes "人間ですか。";
	mes "ところでこんな疑問はどうでしょうか。";
	mes "あなたと私は今、";
	mes "普通に会話をしていますよね。";
	next;
	mes "[ドフィ]";
	mes "それは何故か？";
	mes "この次元の狭間という場所。";
	mes "魔王が潜んでいるところが……";
	mes "ビフロストの領域に";
	mes "含まれるということです。";
	next;
	mes "[ドフィ]";
	mes "そうですね。";
	mes "もっと簡単にいうと、";
	mes "コインの両面とも";
	mes "いえるでしょうか。";
	mes "それとも水面上と";
	mes "水面下というべきでしょうか。";
	next;
	mes "[ドフィ]";
	mes "もしくは私達は";
	mes "果て無き平行線を向かい合って";
	mes "走っているのではなく、";
	mes "同じ点を交差している";
	mes "違う空間の線上に";
	mes "立っているのでしょうか？";
	next;
	mes "[ドフィ]";
	mes "……。";
	mes "謎は深まるばかりです。";
	next;
	mes "[ドフィ]";
	mes "……しかし、重要なのはここです。";
	mes "人間の言葉でいうならば";
	mes "灯台下暗し、とも";
	mes "いうべきでしょうか。";
	mes "こいつらの本拠地が";
	mes "ビフロスト内の別の空間なら……";
	next;
	mes "[ドフィ]";
	mes "準備された結末は抹殺のみ!!";
	mes "そのために突っ走るだけ!!";
	mes "……簡単でしょう？";
	close;
}

moro_vol.gat,104,86,3	script	リョースン	748,{
	mes "[リョースン]";
	mes "き、緊……緊張してます。";
	mes "……事務官殿は何故";
	mes "私なんかに騎士団の方を……。";
	next;
	mes "[リョースン]";
	mes "見習い騎士でもない";
	mes "ロードナイトや";
	mes "ルーンナイトクラスを……！";
	mes "あああ……私のような";
	mes "末端公務員には荷が重過ぎます……。";
	next;
	mes "[リョースン]";
	mes "……とりあえずは命の保証は";
	mes "してもらえてるようですが";
	mes "何をすればいいのか……。";
	mes "大丈夫かな……。";
	close;
}

moro_vol.gat,101,87,5	script	ルーンミッドガッツ騎士	468,{
	switch(rand(4)) {
	case 0: unittalk "……。"; end;
	case 1: unittalk "ここは静かだな。"; end;
	case 2: unittalk "……襲撃もないし……。"; end;
	case 3: unittalk "……つまらん……。"; end;
	}
}

moro_vol.gat,101,85,5	script	ルーンミッドガッツ騎士	469,{
	switch(rand(5)) {
	case 0: unittalk "自分の任務はこちらの要人警備となります！"; end;
	case 1: unittalk "あまり怖がらないでください。その恐怖感は全体に広がります。"; end;
	case 2: unittalk "任務達成のため、がんばります！"; end;
	case 3: unittalk "……はあ……。"; end;
	case 4: unittalk "まだ何もありません。"; end;
	}
}

moro_vol.gat,103,83,1	script	ルーンミッドガッツ騎士	470,{
	switch(rand(5)) {
	case 0: unittalk "魔王と戦うのは騎士のロマン！　だが現実となると……。"; end;
	case 1: unittalk "戦場の緊張感は心地よい。"; end;
	case 2: unittalk "リョースン、気負いすぎだって。"; end;
	case 3: unittalk "……眠い……。"; end;
	case 4: unittalk "……ぐぉ……はっ！"; end;
	}
}

moro_vol.gat,110,83,3	script	ヒュー	868,{
	mes "[ヒュー]";
	mes "ついにはここまで";
	mes "辿りついてしまいましたね。";
	mes "まあ、正直な話、";
	mes "魔王が潜む場所とか、";
	mes "本拠地とか信じられませんが……。";
	next;
	mes "[ヒュー]";
	mes "このままだと出張期間だけ";
	mes "延びに延びて……";
	mes "本国帰還も遅くなり……はあ……。";
	next;
	mes "[ヒュー]";
	mes "こんなところは一日でも";
	mes "早く立ち去りたいものです。";
	mes "そのためにも魔王を";
	mes "早く見つけねばなりませんね。";
	next;
	mes "[ヒュー]";
	mes "負ける？";
	mes "まあ、頭の隅には";
	mes "浮かぶこともありますが、";
	mes "負けることを考えて臨むと";
	mes "勝てる戦いにも負けてしまいます。";
	next;
	mes "[ヒュー]";
	mes "我々シュバルツバルドは必ず勝ちます。";
	close;
}

moro_vol.gat,108,81,7	script	シュバルツバルド精鋭軍	852,{
	switch(rand(5)) {
	case 0: unittalk "アインブロックもここも、空気がいいとは、いえませんね。"; end;
	case 1: unittalk "……へーくしょい！　鼻がむずむずします……。"; end;
	case 2: unittalk "……マスクの1つでも持ってくれば良かった。"; end;
	case 3: unittalk "我々は必ず勝ちます！"; end;
	case 4: unittalk "シュバルツバルドの栄光のために！"; end;
	}
}

moro_vol.gat,111,80,1	script	シュバルツバルド精鋭軍	852,{
	switch(rand(5)) {
	case 0: unittalk "シュバルツバルド産おやつが食べたい……。"; end;
	case 1: unittalk "……寝ていない。瞑想していただけだ。"; end;
	case 2: unittalk "ミッドガルドのために！"; end;
	case 3: unittalk "我々に負けの文字はない！"; end;
	case 4: unittalk "シュバルツバルドの栄光のために！"; end;
	}
}

moro_vol.gat,113,81,3	script	シュバルツバルド精鋭軍	852,{
	switch(rand(5)) {
	case 0: unittalk "魔王との戦闘とアインブロックでマスクなしで警備48時間……どっちがきついですかね？"; end;
	case 1: unittalk "……勝ちます……勝ちに行きます。"; end;
	case 2: unittalk "こんなことならもう少し修練を積むべきだった……。"; end;
	case 3: unittalk "……涙が溢れそうです……目が痛くて。"; end;
	case 4: unittalk "……はあぁ……。"; end;
	}
}

moro_vol.gat,118,86,5	script	ヘンジヌ	931,{
	mes "[ヘンジヌ]";
	mes "予想を裏切られるどころか";
	mes "予想以上に素晴らしい！";
	mes "この体に悪そうな空気とか!";
	mes "気が滅入りそうな雰囲気とか!";
	mes "で……？";
	mes "肝心の魔王はどこです？";
	next;
	mes "[ヘンジヌ]";
	mes "隠れたか？　隠れたのか？";
	mes "ヒャハハハハハハ！";
	close;
}

moro_vol.gat,116,84,7	script	アルナベルツ聖徒団	935,{
	switch(rand(5)) {
	case 0: unittalk "ここには邪悪な者が群れ成していますね……。"; end;
	case 1: unittalk "……。"; end;
	case 2: unittalk "全ては女神の御心のままに……。"; end;
	case 3: unittalk "……異端の者と共にする必要があるとは……。"; end;
	case 4: unittalk "あなたに女神様のご加護があらんことを……。"; end;
	}
}

moro_vol.gat,118,83,7	script	アルナベルツ聖徒団	917,{
	switch(rand(5)) {
	case 0: unittalk "終わりなき戦いほど虚しいものはありません……。"; end;
	case 1: unittalk "ここの空気には馴染めそうにありません。"; end;
	case 2: unittalk "女神様、どうか我々にご加護を……。"; end;
	case 3: unittalk "……異端の者であれ、必要であれば……。"; end;
	case 4: unittalk "女神様のご加護が、あなたとともにありますように……。"; end;
	}
}

moro_vol.gat,121,84,1	script	アルナベルツ聖徒団	920,{
	switch(rand(5)) {
	case 0: unittalk "……今は祈ることしか出来ません。"; end;
	case 1: unittalk "女神様が見守っていてくれるはず……。"; end;
	case 2: unittalk "全ては女神の御心のままに……。"; end;
	case 3: unittalk "……異端者と今、争っている時ではございません……。"; end;
	case 4: unittalk "本当に何があるか、わからないものですね……。"; end;
	}
}

moro_vol.gat,119,106,3	script	教官ジャケン#h_sol01	405,3,3,{
	mes "[教官ジャケン]";
	mes "アッシュバキューム遠征に";
	mes "申し込んだとき、";
	mes "いつかこのような日が";
	mes "来ると予想していました。";
	next;
	mes "[教官ジャケン]";
	mes "もちろん覚悟はしていました。";
	mes "ミッドガルド大陸の平和のために、";
	mes "その元凶を断たねば……！";
	next;
	mes "[教官ジャケン]";
	mes "……やはり怖いですね。";
	mes "ですがこの不安を";
	mes "兵士が感じないように";
	mes "感情の統制をしなければ";
	mes "ならないのですが……。";
	close;
OnTouch:
	if(!getnpctimer(1))
		initnpctimer;
	end;
OnTimer3000:
	unittalk "ジャケン : 諸君！　我ら生まれ育った国は違えど、一つの志のもと！　ここに集まった！";
	end;
OnTimer6000:
	unittalk "ジャケン : その志を魔族にも見せつけようぞ！";
	end;
OnTimer8000:
	unittalk "ジャケン : 全軍！　前進せよ！";
	end;
OnTimer10000:
	donpcevent "ミッドガルド連合軍#so01::OnTalk1";
	donpcevent "ミッドガルド連合軍#so05::OnTalk1";
	donpcevent "ミッドガルド連合軍#so09::OnTalk1";
	end;
OnTimer13000:
	donpcevent "ミッドガルド連合軍#so02::OnTalk1";
	donpcevent "ミッドガルド連合軍#so06::OnTalk1";
	donpcevent "ミッドガルド連合軍#so10::OnTalk1";
	end;
OnTimer16000:
	donpcevent "ミッドガルド連合軍#so03::OnTalk1";
	donpcevent "ミッドガルド連合軍#so07::OnTalk1";
	donpcevent "ミッドガルド連合軍#so11::OnTalk1";
	end;
OnTimer19000:
	donpcevent "ミッドガルド連合軍#so04::OnTalk1";
	donpcevent "ミッドガルド連合軍#so08::OnTalk1";
	donpcevent "ミッドガルド連合軍#so12::OnTalk1";
	end;
OnTimer22000:
	donpcevent "ミッドガルド連合軍#so01::OnTalk2";
	donpcevent "ミッドガルド連合軍#so05::OnTalk2";
	donpcevent "ミッドガルド連合軍#so09::OnTalk2";
	end;
OnTimer25000:
	donpcevent "ミッドガルド連合軍#so02::OnTalk2";
	donpcevent "ミッドガルド連合軍#so06::OnTalk2";
	donpcevent "ミッドガルド連合軍#so10::OnTalk2";
	end;
OnTimer28000:
	donpcevent "ミッドガルド連合軍#so03::OnTalk2";
	donpcevent "ミッドガルド連合軍#so07::OnTalk2";
	donpcevent "ミッドガルド連合軍#so11::OnTalk2";
	end;
OnTimer31000:
	donpcevent "ミッドガルド連合軍#so04::OnTalk2";
	donpcevent "ミッドガルド連合軍#so08::OnTalk2";
	donpcevent "ミッドガルド連合軍#so12::OnTalk2";
	end;
OnTimer40000:
	stopnpctimer;
	end;
}

moro_vol.gat,117,104,1	script	ミッドガルド連合軍#so01	707,{
	end;
OnTalk1:
	unittalk "曙の太陽の中で～";
	end;
OnTalk2:
	unittalk "平和と幸せを～";
	end;
}

moro_vol.gat,117,102,1	script	ミッドガルド連合軍#so02	707,{
	end;
OnTalk1:
	unittalk "守るために～";
	end;
OnTalk2:
	unittalk "魔王の恐怖を";
	end;
}

moro_vol.gat,117,100,1	script	ミッドガルド連合軍#so03	707,{
	end;
OnTalk1:
	unittalk "両手に～";
	end;
OnTalk2:
	unittalk "魔王の恐怖を";
	end;
}

moro_vol.gat,117,98,1	script	ミッドガルド連合軍#so04	707,{
	end;
OnTalk1:
	unittalk "顔を上げ～";
	end;
OnTalk2:
	unittalk "わああああ!!";
	end;
}

moro_vol.gat,119,104,1	script	ミッドガルド連合軍#so05	852,{
	end;
OnTalk1:
	unittalk "夢に見た～";
	end;
OnTalk2:
	unittalk "おびやかす～";
	end;
}

moro_vol.gat,119,102,1	script	ミッドガルド連合軍#so06	852,{
	end;
OnTalk1:
	unittalk "兜の緒を締める～";
	end;
OnTalk2:
	unittalk "きっと払うために～";
	end;
}

moro_vol.gat,119,100,1	script	ミッドガルド連合軍#so07	868,{
	end;
OnTalk1:
	unittalk "構えし剣～";
	end;
OnTalk2:
	unittalk "払うために～";
	end;
}

moro_vol.gat,119,98,1	script	ミッドガルド連合軍#so08	868,{
	end;
OnTalk1:
	unittalk "目を開け～";
	end;
OnTalk2:
	unittalk "わああああ!!";
	end;
}

moro_vol.gat,121,104,1	script	ミッドガルド連合軍#so09	934,{
	end;
OnTalk1:
	unittalk "故郷を～";
	end;
OnTalk2:
	unittalk "魔族を倒すため～";
	end;
}

moro_vol.gat,121,102,1	script	ミッドガルド連合軍#so10	934,{
	end;
OnTalk1:
	unittalk "心も熱く～";
	end;
OnTalk2:
	unittalk "行進だ～";
	end;
}

moro_vol.gat,121,100,1	script	ミッドガルド連合軍#so11	939,{
	end;
OnTalk1:
	unittalk "進め前へ～";
	end;
OnTalk2:
	unittalk "行進だ～！";
	end;
}

moro_vol.gat,121,98,1	script	ミッドガルド連合軍#so12	939,{
	end;
OnTalk1:
	unittalk "まっすぐ前を見て～";
	end;
OnTalk2:
	unittalk "わああああ!!";
	end;
}

moro_vol.gat,105,97,3	script	遠征隊アサシン#ass01	884,{
	mes "[遠征隊アサシン]";
	mes "……間もなく";
	mes "新しい任務が下る予定だ……。";
	mes "我らの目的は魔王の";
	mes "正確な位置を割り出すこと……。";
	next;
	mes "[遠征隊アサシン]";
	mes "先行している仲間のために";
	mes "まずは情報の整理をしよう。";
	next;
	mes "[遠征隊アサシン]";
	mes "………。";
	mes "いくら遠征隊員と言っても";
	mes "聞き耳を立てるのは";
	mes "よろしくないな。";
	close;
}

moro_vol.gat,103,96,5	script	遠征隊アサシン#ass02	885,{
	mes "[遠征隊アサシン]";
	mes "……ここは……そうだな……。";
	mes "私のルートの追加しよう……。";
	next;
	mes "[遠征隊アサシン]";
	mes "……おい……。";
	mes "会議中だ……立ち去れ。";
	close;
}

moro_vol.gat,105,95,1	script	遠征隊アサシン#ass03	10002,{
	mes "[遠征隊アサシン]";
	mes "………。";
	mes "………いや俺は新入りだから。";
	mes "先輩の話を聞いているだけだよ。";
	mes "……。";
	close;
}

moro_vol.gat,87,104,5	script	魔学者コンパーナ#143vol	446,{
	mes "[コンパーナ]";
	mes "なんとか派遣員として";
	mes "ここまでは来ましたけど……";
	mes "想像以上ですね！";
	mes "緑がぜんぜん無いなんて……。";
	mes "びっくりですよ。";
	close;
}

moro_vol.gat,88,102,6	script	魔学者マキア#143vol03	444,{
	mes "[マキア]";
	mes "始めて見る生態系ですね。";
	mes "すごく熱そうに見えて意外と";
	mes "熱くもないし……";
	mes "不思議がいっぱいだな……。";
	close;
}

moro_vol.gat,104,109,0	script	戦士ラフィネ#sol01	447,{
	end;
OnTalk1:
	unittalk "我らは!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,106,109,0	script	戦士ラフィネ#sol02	447,{
	end;
OnTalk1:
	unittalk "我らは!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,108,109,0	script	戦士ラフィネ#sol03	447,{
	end;
OnTalk1:
	unittalk "我らは!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,104,107,0	script	戦士ラフィネ#sol04	447,{
	end;
OnTalk1:
	unittalk "誇り高き!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,106,107,0	script	戦士ラフィネ#sol05	447,{
	end;
OnTalk1:
	unittalk "誇り高き!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,108,107,0	script	戦士ラフィネ#sol06	447,{
	end;
OnTalk1:
	unittalk "誇り高き!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,104,105,0	script	戦士ラフィネ#sol07	447,{
	end;
OnTalk1:
	unittalk "ラフィネ族!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,106,105,0	script	戦士ラフィネ#sol08	447,{
	end;
OnTalk1:
	unittalk "ラフィネ族!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,108,105,0	script	戦士ラフィネ#sol09	447,{
	end;
OnTalk1:
	unittalk "ラフィネ族!!";
	end;
OnTalk2:
	unittalk "処断する!!";
	end;
}

moro_vol.gat,106,111,3	script	戦場指揮官#sol10	447,3,3,{
	mes "[ラフィネ指揮官]";
	mes "本格的な戦闘を前に";
	mes "部隊を整備中である。";
	mes "邪魔になるので立ち去るように。";
	close;
OnTouch:
	if(!getnpctimer(1))
		initnpctimer;
	end;
OnTimer3000:
	unittalk "指揮官 : 諸君！　ついに我らの訓練成果を見せるときだ！";
	end;
OnTimer6000:
	unittalk "指揮官 : 我らは!!";
	end;
OnTimer8000:
	donpcevent "戦士ラフィネ#sol01::OnTalk1";
	donpcevent "戦士ラフィネ#sol02::OnTalk1";
	donpcevent "戦士ラフィネ#sol03::OnTalk1";
	end;
OnTimer9500:
	donpcevent "戦士ラフィネ#sol04::OnTalk1";
	donpcevent "戦士ラフィネ#sol05::OnTalk1";
	donpcevent "戦士ラフィネ#sol06::OnTalk1";
	end;
OnTimer11000:
	donpcevent "戦士ラフィネ#sol07::OnTalk1";
	donpcevent "戦士ラフィネ#sol08::OnTalk1";
	donpcevent "戦士ラフィネ#sol09::OnTalk1";
	end;
OnTimer14000:
	unittalk "指揮官 : 悪を処断する!!";
	end;
OnTimer16000:
	donpcevent "戦士ラフィネ#sol01::OnTalk2";
	donpcevent "戦士ラフィネ#sol02::OnTalk2";
	donpcevent "戦士ラフィネ#sol03::OnTalk2";
	donpcevent "戦士ラフィネ#sol04::OnTalk2";
	donpcevent "戦士ラフィネ#sol05::OnTalk2";
	donpcevent "戦士ラフィネ#sol06::OnTalk2";
	donpcevent "戦士ラフィネ#sol07::OnTalk2";
	donpcevent "戦士ラフィネ#sol08::OnTalk2";
	donpcevent "戦士ラフィネ#sol09::OnTalk2";
	end;
OnTimer30000:
	stopnpctimer;
	end;
}

moro_vol.gat,101,102,0	script	ラフィネ魔道師#wsol01	611,{
	switch(rand(5)) {
	case 0: unittalk "守護者様が見ていらっしゃるんだわ……がんばる……。"; end;
	case 1: unittalk "……敵に、慈悲は無用……。"; end;
	case 2: unittalk "……エクラージュが恋しい。"; end;
	case 3: unittalk "……全部凍らせてやる……凍らせてやる……。"; end;
	case 4: unittalk "はぁ……はぁ……。"; end;
	}
}

moro_vol.gat,103,102,0	script	ラフィネ魔道師#wsol02	520,{
	switch(rand(5)) {
	case 0: unittalk "道具のお手入れ、ふんふふーん♪"; end;
	case 1: unittalk "……あれ、魔法書どこに置いたかな。"; end;
	case 2: unittalk "しっ……静かに……集中力が途切れる。"; end;
	case 3: unittalk "……あれをこうして、こうして……。"; end;
	case 4: unittalk "……おなか、ぺっこぺこだわあ。"; end;
	}
}

moro_vol.gat,105,102,0	script	ラフィネ魔道師#wsol03	446,{
	switch(rand(5)) {
	case 0: unittalk "……俺達はいつまで待機なんだ……。"; end;
	case 1: unittalk "…なんで俺はここに来たんだ……俺のヤイで眠りたい……。"; end;
	case 2: unittalk "……ハァ……。"; end;
	case 3: unittalk "……くっ！　羽根がうずく……。"; end;
	case 4: unittalk "背中側の人間……気に触る……。"; end;
	}
}

moro_vol.gat,107,102,0	script	ラフィネ魔道師#wsol04	440,{
	switch(rand(5)) {
	case 0: unittalk "一応、ハーブも持っていくかな。"; end;
	case 1: unittalk "うまくいくのかなあ、少し心配だわ。"; end;
	case 2: unittalk "……緊張するな……。"; end;
	case 3: unittalk "……敵を見つけたら……ファイア……。"; end;
	case 4: unittalk "サファ族は敵じゃない……サファ族は敵じゃない……いいい！　殴ってやりたい！"; end;
	}
}

moro_vol.gat,109,102,0	script	ラフィネ魔道師#wsol05	446,{
	switch(rand(5)) {
	case 0: unittalk "……緊張するな……。"; end;
	case 1: unittalk "こんな緊張感……悪くないな……ふふふ……。"; end;
	case 2: unittalk "……敵を見つけたら……あいつとダブルファイア……。"; end;
	case 3: unittalk "……火、実は苦手なんだけどな。"; end;
	case 4: unittalk "暗いの、もっと苦手なんだけどな。"; end;
	}
}

//============================================================
// 守護者
//------------------------------------------------------------
moro_vol.gat,86,167,7	script	前線基地・守護者#1	415,3,3,{
	mes "[前線基地・守護者]";
	set '@type,strnpcinfo(2);
	switch('@type%10) {
	case 0:
		mes "倒しても倒してもきりがないですね。";
		break;
	case 1:
		mes "ここは危険です。基地に戻って下さい！";
		break;
	case 2:
		mes "基地の中には絶対に";
		mes "入れません。";
		break;
	case 3:
		mes "ああ、いつまでこの仕事を";
		mes "やればいんだろう……。";
		break;
	case 4:
		mes "心配しないで下さい。";
		mes "ここは私がうまく守ります。";
		break;
	case 5:
		mes "今はあまり話をできる";
		mes "余裕がありません。";
		break;
	case 6:
		mes "退いて下さい。";
		mes "視界を防いでいます。";
		break;
	case 7:
		mes "雑談する余裕があるなら、";
		mes "少しでも多くの敵を";
		mes "倒したらどうですか？";
		break;
	case 8:
		mes "ああ……だんだん寒くなってきたし、";
		mes "お腹も空いてきたなあ。";
		mes "あ！　これは独り言です。";
		break;
	case 9:
		mes "ここは本当に魔物が多いです。";
		mes "少しでも気を抜くと";
		mes "酷い目に遭いそうです。";
		break;
	}
	close;
OnTouch:
	end;
OnTouchNPC:
	switch(rand(4)) {
	case 0: unittalk "前線基地・守護者 : そこまでだ！　ここから先には行かせない！"; break;
	case 1: unittalk "前線基地・守護者 : 基地には一歩も入れさせないぞ！"; break;
	case 2: unittalk "前線基地・守護者 : ここから離れろ！　ここから先は我々の領域だ！"; break;
	case 3: unittalk "前線基地・守護者 : 魔物め！　己のあるべき場所へ還れ！　私たちは戦うぞ！"; break;
	}
	switch(rand(4)) {
	case 0:
		misceffect 12;
		set '@dummy,sleep2(1000);
		misceffect 90;
		break;
	case 1:
		misceffect 12;
		set '@dummy,sleep2(1000);
		misceffect 89;
		break;
	case 2:
		misceffect 12;
		set '@dummy,sleep2(1000);
		misceffect 40;
		break;
	case 3:
		misceffect 12;
		set '@dummy,sleep2(1000);
		misceffect 183;
		break;
	}
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,93,166,7	duplicate(前線基地・守護者#1)	前線基地・守護者#2	414,3,3
moro_vol.gat,100,165,7	duplicate(前線基地・守護者#1)	前線基地・守護者#3	413,3,3
moro_vol.gat,107,164,7	duplicate(前線基地・守護者#1)	前線基地・守護者#4	419,3,3
moro_vol.gat,114,162,7	duplicate(前線基地・守護者#1)	前線基地・守護者#5	420,3,3
moro_vol.gat,121,160,7	duplicate(前線基地・守護者#1)	前線基地・守護者#6	418,3,3
moro_vol.gat,128,158,7	duplicate(前線基地・守護者#1)	前線基地・守護者#7	415,3,3
moro_vol.gat,135,155,7	duplicate(前線基地・守護者#1)	前線基地・守護者#8	414,3,3
moro_vol.gat,142,152,7	duplicate(前線基地・守護者#1)	前線基地・守護者#9	413,3,3
moro_vol.gat,149,148,7	duplicate(前線基地・守護者#1)	前線基地・守護者#10	419,3,3
moro_vol.gat,156,144,7	duplicate(前線基地・守護者#1)	前線基地・守護者#11	420,3,3
moro_vol.gat,162,137,6	duplicate(前線基地・守護者#1)	前線基地・守護者#12	418,3,3
moro_vol.gat,168,130,6	duplicate(前線基地・守護者#1)	前線基地・守護者#13	415,3,3
moro_vol.gat,174,123,6	duplicate(前線基地・守護者#1)	前線基地・守護者#14	414,3,3
moro_vol.gat,178,116,6	duplicate(前線基地・守護者#1)	前線基地・守護者#15	413,3,3
moro_vol.gat,182,109,6	duplicate(前線基地・守護者#1)	前線基地・守護者#16	419,3,3
moro_vol.gat,185,102,6	duplicate(前線基地・守護者#1)	前線基地・守護者#17	420,3,3
moro_vol.gat,187,95,6	duplicate(前線基地・守護者#1)	前線基地・守護者#18	418,3,3
moro_vol.gat,189,88,6	duplicate(前線基地・守護者#1)	前線基地・守護者#19	415,3,3
moro_vol.gat,191,81,6	duplicate(前線基地・守護者#1)	前線基地・守護者#20	414,3,3

moro_vol.gat,114,128,1	script	コンチネンタルガード::morovol_con01	997,3,3,{
	switch(rand(3)) {
	case 0: unittalk "異常ありません。"; end;
	case 1: unittalk "お気をつけて。"; end;
	case 2: unittalk "ここは危険です。お下がりください。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "ここは通さん!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,119,130,1	script	コンチネンタルガード::morovol_con02	998,{
	switch(rand(3)) {
	case 0: unittalk "はい、今のところ異常はありません。"; end;
	case 1: unittalk "お気をつけください。"; end;
	case 2: unittalk "あまりここに長居は不要かと……危険ですから。"; end;
	}
}

moro_vol.gat,122,130,7	script	コンチネンタルガード::morovol_con03	997,3,3,{
	switch(rand(3)) {
	case 0: unittalk "危険な場所です。あまり前に出ないでください。"; end;
	case 1: unittalk "お気をつけて。"; end;
	case 2: unittalk "異常ありません。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "ここは通さんぞ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,125,129,7	script	コンチネンタルガード::morovol_con04	997,{
	switch(rand(3)) {
	case 0: unittalk "何かあってからでは遅いので、下がってください。"; end;
	case 1: unittalk "どうぞお気をつけて。"; end;
	case 2: unittalk "異常……ありません。"; end;
	}
}

moro_vol.gat,127,127,7	script	コンチネンタルガード::morovol_con05	998,{
	switch(rand(3)) {
	case 0: unittalk "危険な場所ですから、気を抜かないようにしてください。"; end;
	case 1: unittalk "この場所は特に危険です。単独行動はなるべくお控えください"; end;
	case 2: unittalk "異常なし。"; end;
	}
}

moro_vol.gat,135,123,1	script	ミッドガルド連合軍::morovol_mid01	753,3,3,{
	switch(rand(3)) {
	case 0: unittalk "……アルナベルツの連中は前に出ないのか？"; end;
	case 1: unittalk "どんな奴だろうと倒してやる！"; end;
	case 2: unittalk "コンチネンタルガードって強いな。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "おっと!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,139,124,1	script	ミッドガルド連合軍::morovol_mid02	745,{
	switch(rand(3)) {
	case 0: unittalk "……フン。"; end;
	case 1: unittalk "きりが無いな……。"; end;
	case 2: unittalk "……お気をつけて。"; end;
	}
}

moro_vol.gat,143,124,1	script	ミッドガルド連合軍::morovol_mid03	735,{
	switch(rand(3)) {
	case 0: unittalk "ふう……。"; end;
	case 1: unittalk "……守護者達のおかげで戦いやすいな。"; end;
	case 2: unittalk "……下がっていなさい。"; end;
	}
}

moro_vol.gat,147,124,7	script	ミッドガルド連合軍::morovol_mid04	707,3,3,{
	switch(rand(3)) {
	case 0: unittalk "どんな相手だろうと、逃げませんよ。"; end;
	case 1: unittalk "……いつ、この戦いは終わるのだろうか。"; end;
	case 2: unittalk "体調ともに、いまのところ、異常も問題ありません。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵襲!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,150,121,7	script	ミッドガルド連合軍::morovol_mid05	707,{
	switch(rand(3)) {
	case 0: unittalk "なんでいつも前衛に配置されるんだろう……。"; end;
	case 1: unittalk "……く……来るな！　って、人だったか。"; end;
	case 2: unittalk "……こ……交代はいつだ……？"; end;
	}
}

moro_vol.gat,151,119,7	script	ミッドガルド連合軍::morovol_mid06	852,{
	switch(rand(3)) {
	case 0: unittalk "明日の朝には交代か……。"; end;
	case 1: unittalk "……おっと、ここから前には出ない方がいい。"; end;
	case 2: unittalk "……どこにいてもお守り係か……。"; end;
	}
}

moro_vol.gat,153,116,7	script	ミッドガルド連合軍::morovol_mid07	852,3,3,{
	switch(rand(3)) {
	case 0: unittalk "何もないのは良いが、精神的に疲れる……。"; end;
	case 1: unittalk "……モロク果実酒が飲みたい。"; end;
	case 2: unittalk "いったいどこから沸いてくるのか……。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "立ち去れ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,118,115,1	script	ミッドガルド連合軍::morovol_mid08	735,3,3,{
	switch(rand(3)) {
	case 0: unittalk "あの異端って話いつまで続けるんだ……。"; end;
	case 1: unittalk "……あれ？　並ぶ列間違えたか？"; end;
	case 2: unittalk "……なんでこんなところに……。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "あっちに行け!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,121,115,1	script	ミッドガルド連合軍::morovol_mid09	852,{
	switch(rand(3)) {
	case 0: unittalk "……前衛は非常に危険です。"; end;
	case 1: unittalk "……ここもうるさいな。"; end;
	case 2: unittalk "……ふう……正直、帰れるなら帰りたいです。"; end;
	}
}

moro_vol.gat,124,116,1	script	ミッドガルド連合軍::morovol_mid10	852,3,3,{
	switch(rand(3)) {
	case 0: unittalk "お互い、気をつけましょう。"; end;
	case 1: unittalk "異常ありません。"; end;
	case 2: unittalk "……ここは守り抜きます。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "魔族め！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,128,116,1	script	ミッドガルド連合軍::morovol_mid11	852,{
	switch(rand(3)) {
	case 0: unittalk "……へぇ、異常ないっす。"; end;
	case 1: unittalk "……異常ありやせん……ZZz……。"; end;
	case 2: unittalk "……ね……寝てやせん……！"; end;
	}
}

moro_vol.gat,131,115,7	script	ミッドガルド連合軍::morovol_mid12	934,{
	switch(rand(3)) {
	case 0: unittalk "異端者共と一緒になるとは……。"; end;
	case 1: unittalk "仕方がないとはいえ、やはり気分は良くないです。"; end;
	case 2: unittalk "女神よ、ご加護を……。"; end;
	}
}

moro_vol.gat,133,113,7	script	ミッドガルド連合軍::morovol_mid13	939,{
	switch(rand(3)) {
	case 0: unittalk "おいおい、あまりうろつくと危険だ。"; end;
	case 1: unittalk "疲れたな……。"; end;
	case 2: unittalk "……交代はいつだ？"; end;
	}
}

moro_vol.gat,136,111,7	script	ミッドガルド連合軍::morovol_mid14	934,3,3,{
	switch(rand(3)) {
	case 0: unittalk "防衛線には異常ありません。"; end;
	case 1: unittalk "お気をつけて。"; end;
	case 2: unittalk "お下がりください。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵襲！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,138,108,7	script	ミッドガルド連合軍::morovol_mid15	939,{
	switch(rand(3)) {
	case 0: unittalk "特に異常はありません。"; end;
	case 1: unittalk "前方監視中！　異常な～し！"; end;
	case 2: unittalk "……女神様のご加護がありますように……。"; end;
	}
}

moro_vol.gat,93,128,1	script	戦士ラフィネ#line01	461,3,3,{
	switch(rand(4)) {
	case 0: unittalk "気をつけてください！"; end;
	case 1: unittalk "危険なので後ろに下がってください！"; end;
	case 2: unittalk "異常なし！"; end;
	case 3: unittalk "はい～はい～。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵発見!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,96,130,1	script	戦士ラフィネ#line02	461,{
	switch(rand(4)) {
	case 0: unittalk "危険なほどに燃えるっすよ！"; end;
	case 1: unittalk "うっす、うっす！"; end;
	case 2: unittalk "異常は……ありませんっす！"; end;
	case 3: unittalk "気合い十分っす！"; end;
	}
}

moro_vol.gat,99,131,1	script	戦士ラフィネ#line03	461,3,3,{
	switch(rand(4)) {
	case 0: unittalk "元気があれば、ごはんがうまい。"; end;
	case 1: unittalk "……出番きちゃった!?"; end;
	case 2: unittalk "異常……なし……多分。"; end;
	case 3: unittalk "ふぁい……。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "く……くるな!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,102,132,7	script	戦士ラフィネ#line04	447,{
	switch(rand(4)) {
	case 0: unittalk "武器の手入れも万全です。"; end;
	case 1: unittalk "危ないので、ここはお任せください！"; end;
	case 2: unittalk "異常はありません。"; end;
	case 3: unittalk "ご苦労様です。"; end;
	}
}

moro_vol.gat,105,132,7	script	戦士ラフィネ#line05	462,3,3,{
	switch(rand(4)) {
	case 0: unittalk "どうかお下がりください。"; end;
	case 1: unittalk "緊張します……。"; end;
	case 2: unittalk "お互い、気をつけましょう。"; end;
	case 3: unittalk "ご苦労様です。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "ここは通さない！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,108,131,7	script	戦士ラフィネ#line06	461,{
	switch(rand(4)) {
	case 0: unittalk "命あってこそですから、気をつけてください。"; end;
	case 1: unittalk "ふーむ……。"; end;
	case 2: unittalk "ここは危険ですよ！"; end;
	case 3: unittalk "いつ襲撃がくるんだろうか……。"; end;
	}
}

moro_vol.gat,111,129,7	script	戦士ラフィネ#line07	447,3,3,{
	switch(rand(4)) {
	case 0: unittalk "異常はありません!!"; end;
	case 1: unittalk "どうぞ、ここは任せてください！"; end;
	case 2: unittalk "……皆、のんきだな。"; end;
	case 3: unittalk "ううーん……。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵だ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,85,117,1	script	戦士ラフィネ#line11	462,3,3,{
	switch(rand(4)) {
	case 0: unittalk "油断は禁物ですっ！"; end;
	case 1: unittalk "前衛に比べればマシなんでしょうけど……。"; end;
	case 2: unittalk "世界樹の加護がありますよーに……。"; end;
	case 3: unittalk "い、異常ありまっ……!!　ひた、かんじゃいまひた……。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "ここまで来るなんて！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,89,118,1	script	戦士ラフィネ#line12	447,{
	switch(rand(4)) {
	case 0: unittalk "逃げちゃだめだぞ！　逃げちゃ～……！"; end;
	case 1: unittalk "敵がこうきたら、こう動いて……。"; end;
	case 2: unittalk "前の方は大丈夫ですかね……。"; end;
	case 3: unittalk "異常……あ・り・ま・せん！"; end;
	}
}

moro_vol.gat,92,119,7	script	戦士ラフィネ#line13	447,3,3,{
	switch(rand(4)) {
	case 0: unittalk "些細なことでも、ご注意ください！"; end;
	case 1: unittalk "必ず、やり遂げます！"; end;
	case 2: unittalk "前方の皆が心配です……大丈夫でしょうけど。"; end;
	case 3: unittalk "異常、今のところありません！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵襲だぞ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,96,119,7	script	戦士ラフィネ#line14	461,{
	switch(rand(4)) {
	case 0: unittalk "緊張感を維持するのは、大変です……。"; end;
	case 1: unittalk "みんな無事に帰れたら良いな……。"; end;
	case 2: unittalk "何か気づいたら即、ご連絡しますね。"; end;
	case 3: unittalk "異常は、ありません。"; end;
	}
}

moro_vol.gat,100,117,7	script	戦士ラフィネ#line15	447,3,3,{
	switch(rand(4)) {
	case 0: unittalk "前衛の動向が見えないのが辛いですね……。"; end;
	case 1: unittalk "敵の動向が気になりますね……。"; end;
	case 2: unittalk "いつ何が起きるか……。"; end;
	case 3: unittalk "異常は今のところありません。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "倒してやる!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,103,118,1	script	戦士ラフィネ#line16	462,{
	switch(rand(4)) {
	case 0: unittalk "前方に友人がいるので、前方が気になります。"; end;
	case 1: unittalk "とりあえず今のところ、何もありません。"; end;
	case 2: unittalk "油断しないで行きましょう、敵陣ですし。"; end;
	case 3: unittalk "異常なしっ！"; end;
	}
}

moro_vol.gat,107,118,7	script	戦士ラフィネ#line17	462,3,3,{
	switch(rand(4)) {
	case 0: unittalk "いつ敵襲がきてもいいように、スマイルの練習♪"; end;
	case 1: unittalk "はふ～……。"; end;
	case 2: unittalk "油断大敵！　あれ……？　油断敵対でしたっけ？"; end;
	case 3: unittalk "異常、ありません♪"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "いきま～すっ♪";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,110,117,7	script	戦士ラフィネ#line18	461,{
	switch(rand(4)) {
	case 0: unittalk "木の橋を飛んで渡るくらい、慎重に行かねば……。"; end;
	case 1: unittalk "見えない前のメンバーにも注意しておこう。"; end;
	case 2: unittalk "どこに敵が潜んでいるか分からないしな……。"; end;
	case 3: unittalk "アレでも仲間だが、サファ族が裏切らない保証がない……。"; end;
	}
}

moro_vol.gat,114,114,7	script	戦士ラフィネ#line19	461,3,3,{
	switch(rand(4)) {
	case 0: unittalk "サファ族のやつらと一緒だと、多少不安っす……。"; end;
	case 1: unittalk "注意を怠らないようにがんばるっす！"; end;
	case 2: unittalk "大丈夫っす、問題ないっす。"; end;
	case 3: unittalk "異常、ないっす！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵っす！　敵っすよー！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,139,104,1	script	マヌク守護隊#line01	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "ふむ！"; end;
	case 1: unittalk "異常なし。"; end;
	case 2: unittalk "下がれ！　人間！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "小ざかしい！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,143,106,1	script	マヌク守護隊#line02	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "俺様の目が黒いうちは、何もさせん！"; end;
	case 1: unittalk "うむ！　今日も絶好調だ！"; end;
	case 2: unittalk "下がるんだな！　人間！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵だ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,147,108,1	script	マヌク守護隊#line03	492,{
	switch(rand(3)) {
	case 0: unittalk "……ふん。"; end;
	case 1: unittalk "異常はない。"; end;
	case 2: unittalk "どこかで虫の羽音が聞こえるな！　え～んとな！"; end;
	}
}

moro_vol.gat,152,109,1	script	マヌク守護隊#line04	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "異常なし。"; end;
	case 1: unittalk "ここは問題ないぞ！"; end;
	case 2: unittalk "下がっておれ！　人間！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "通さぬ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,156,110,1	script	マヌク守護隊#line05	492,{
	switch(rand(3)) {
	case 0: unittalk "……なぜラフィネ族なんかと……。"; end;
	case 1: unittalk "……羽根つきとは違うのだ、羽根つきとは。"; end;
	case 2: unittalk "お前は羽根なしのようだな。"; end;
	}
}

moro_vol.gat,160,110,7	script	マヌク守護隊#line06	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "異常なーし！"; end;
	case 1: unittalk "うぬうぬ！"; end;
	case 2: unittalk "そこにいると邪魔だ！　人間！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "笑わせるな！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,164,109,7	script	マヌク守護隊#line07	492,{
	switch(rand(3)) {
	case 0: unittalk "くっくっくっく！"; end;
	case 1: unittalk "異常？　ないぞ。"; end;
	case 2: unittalk "ラフィネ族なんぞに負けぬ。"; end;
	}
}

moro_vol.gat,167,107,7	script	マヌク守護隊#line08	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "ふんっ！　ふんっ！　ふーんっ！"; end;
	case 1: unittalk "やることがない時は、鍛錬に限るのだ！"; end;
	case 2: unittalk "ふん、わしの屈強な肉体に怖気づいたか。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵か！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,169,104,7	script	マヌク守護隊#line09	492,{
	switch(rand(3)) {
	case 0: unittalk "ううむ、手持ち無沙汰だ。"; end;
	case 1: unittalk "……なにか斬るものをくれ。"; end;
	case 2: unittalk "武器を振り回すと怒られるだろうしな……。"; end;
	}
}

moro_vol.gat,171,100,5	script	マヌク守護隊#line10	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "こう見えて、手先は器用なのだぞ。"; end;
	case 1: unittalk "扱うだけが武器じゃない。手入れも忘れずにな。"; end;
	case 2: unittalk "そんなひ弱な体で、よく動けるものだ。"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "なめるんじゃねーぞ!!";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,172,95,5	script	マヌク守護隊#line11	492,{
	switch(rand(3)) {
	case 0: unittalk "今日もハズレのようだな。"; end;
	case 1: unittalk "血沸き肉踊る戦いはいつ始まるんだ……。"; end;
	case 2: unittalk "勇敢なガルトンは退きはしない！"; end;
	}
}

moro_vol.gat,173,89,5	script	マヌク守護隊#line12	492,3,3,{
	switch(rand(3)) {
	case 0: unittalk "体が鈍るな……。"; end;
	case 1: unittalk "酒でも飲みたい気分だぜ……。"; end;
	case 2: unittalk "このような機会、滅多にないからな！"; end;
	}
OnTouch:
	end;
OnTouchNPC:
	unittalk "うおーっ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,100,183,1	script	駐屯地 番卒#bl0	417,3,3,{
	mes "[駐屯地 番卒]";
	mes "ここは危険地域です。";
	mes "勝手に歩き回っては";
	mes "困ります。";
	close;
OnTouch:
	end;
OnTouchNPC:
	unittalk "あっちへ行け！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,102,188,1	script	駐屯地 番卒#bl1	417,3,3,{
	mes "[駐屯地 番卒]";
	mes "ここは危険地域です。";
	mes "勝手に歩き回っては";
	mes "困ります。";
	close;
OnTouch:
	end;
OnTouchNPC:
	unittalk "敵襲だ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,104,193,1	script	駐屯地 番卒#bl2	417,3,3,{
	mes "[駐屯地 番卒]";
	mes "ここは危険地域です。";
	mes "勝手に歩き回っては";
	mes "困ります。";
	close;
OnTouch:
	end;
OnTouchNPC:
	unittalk "くらえ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,95,182,1	script	駐屯地 番卒#bl3	417,3,3,{
	mes "[駐屯地 番卒]";
	mes "ここは危険地域です。";
	mes "勝手に歩き回っては";
	mes "困ります。";
	close;
OnTouch:
	end;
OnTouchNPC:
	unittalk "魔物どもめ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

moro_vol.gat,90,181,7	script	駐屯地 番卒#bl4	417,3,3,{
	mes "[駐屯地 番卒]";
	mes "ここは危険地域です。";
	mes "勝手に歩き回っては";
	mes "困ります。";
	close;
OnTouch:
	end;
OnTouchNPC:
	unittalk "通さんぞ！";
	misceffect 92;
	set '@dummy,sleep2(2000);
	warp "Random",0,0;
	end;
}

//============================================================
// フレイムヴァレーへの道クエスト
//- Registry -------------------------------------------------
// FVOL_1QUE -> 0～18、100
//------------------------------------------------------------
morocc.gat,138,238,4	script	倒れている男性#ep14bs	849,{
	switch(FVOL_1QUE) {
	case 0:
		mes "‐人が倒れている。行き倒れだろうか‐";
		next;
		if(BaseLevel < 140) {
			mes "‐^0000FFフレイムヴァレーへの道^000000は";
			mes "　^FF0000BaseLv140以上^000000から";
			mes "　開始することができるクエストです‐";
			close;
		}
		if(select("声をかける","そのままにする") == 2) {
			mes "‐そのまま通り過ぎた‐";
			close;
		}
		mes "[？？？]";
		mes "うう……。";
		next;
		mes "‐声をかけると反応があった。";
		mes "　意識はあるようだ‐";
		next;
		if(select("揺らしてみる","そのままにしておく") == 2) {
			mes "‐あなたはその場を立ち去った‐";
			close;
		}
		mes "[？？？]";
		mes "う……う……";
		mes "た……食べ物を……";
		mes "^0000FF化け物のエサ^000000でもいいので……";
		mes "何か食べ物を……。";
		next;
		mes "‐力尽きたのか気絶してしまった。";
		mes "　^0000FF化け物のエサ^000000を手に入れて";
		mes "　食べさせてみよう‐";
		set FVOL_1QUE,1;
		setquest 11349;
		close;
	case 1:
		if(countitem(528) < 1) {
			mes "‐力尽きたのか気絶してしまった。";
			mes "　^0000FF化け物のエサ^000000を手に入れて";
			mes "　食べさせてみよう‐";
			close;
		}
		mes "[？？？]";
		mes "うう……。";
		next;
		if(select("化け物のエサを与える","そのままにしておく") == 2) {
			mes "[？？？]";
			mes "うう……助けて……。";
			close;
		}
		cutin "ep143_tadir",2;
		mes "[？？？]";
		mes "ううう……";
		mes "不味い！";
		delitem 528,1;
		set FVOL_1QUE,2;
		chgquest 11349,11350;
		next;
		mes "[？？？]";
		mes "モグモグ……。";
		mes "不味いよう……。";
		mes "モグモグ……。";
		next;
		mes "[？？？]";
		mes "……ふう……。";
		next;
	case 2:
		cutin "ep143_tadir",2;
		mes "[？？？]";
		mes "うっぷ……";
		mes "……あ、ありがとうございます。";
		mes "おかげ様でかなり良くなりました。";
		mes "うううっ……。";
		next;
		mes "[？？？]";
		mes "最近本当に不運続きで、";
		mes "私はどうしてこんなに";
		mes "運が悪いのかと嘆いていたところです。";
		next;
		mes "[？？？]";
		mes "このまま死ぬのかと思いましたが、";
		mes "幸運の女神はまだ私を";
		mes "見捨てていなかったようです。";
		next;
		mes "[？？？]";
		mes "地面にできていたひびに落ちて";
		mes "友達と離れ離れになったあげく、";
		mes "そのひびを抜けた先は";
		mes "炎が燻るような";
		mes "不思議な場所だったんです。";
		next;
		mes "[？？？]";
		mes "本当に……。こうやって";
		mes "人がいる場所に戻って来れただけでも";
		mes "奇跡と言うしか……。";
		next;
		mes "[？？？]";
		mes "運が良かったですよ。";
		mes "死ななかったんだから。";
		mes "ははは……。";
		next;
		mes "[？？？]";
		mes "そういえばさっきから";
		mes "自分の話ばかりで、";
		mes "ちゃんとしたお礼も";
		mes "まだしていなかったですね。";
		next;
		mes "[？？？]";
		mes "本当にありがとうございます。";
		mes "おかげで死なずにすみました。";
		mes "いただいた化け物のエサは";
		mes "死ぬほど不味かったですが。";
		next;
		mes "[？？？]";
		mes "こんな風に道端で死ぬのかなと";
		mes "思っていたのに、まだまだ世界も";
		mes "捨てたもんじゃないと思いました。";
		mes "本当に感動的です。";
		next;
		mes "[タマリン]";
		mes "私の名前は^0000FFタマリン^000000と言います。";
		mes "ご覧の通り冒険家……";
		mes "今はこんな姿ですが冒険家です。";
		next;
		menu "自己紹介を行う",-;
		mes "[タマリン]";
		mes strcharinfo(0)+ "様ですか。";
		mes "素敵な名前ですね。";
		next;
	case 3:
		if(FVOL_1QUE != 3) {
			mes "[タマリン]";
			mes "あ！";
			mes "こんな汚れた姿のまま";
			mes "お話をするのも失礼ですね。";
			next;
			mes "[タマリン]";
			mes "すみません、この近くに";
			mes "体を洗えそうな場所はありませんか？";
		}
		else {
			cutin "ep143_tadir",2;
			mes "[タマリン]";
			mes "やはりこんな汚れた姿で";
			mes "命の恩人とお話しするのは";
			mes "心苦しいです……。";
			next;
			mes "[タマリン]";
			mes "この近くに";
			mes "体を洗えそうな場所はありませんか？";
		}
		next;
		if(select("場所を教える","知らないと言う") == 2) {
			mes "[タマリン]";
			mes "やはり、砂漠都市なので";
			mes "水が貴重なのでしょうか？";
			set FVOL_1QUE,3;
			close2;
			cutin "ep143_tadir",255;
			end;
		}
	case 4:
		cutin "ep143_tadir",2;
		mes "[タマリン]";
		mes "ああ！";
		mes "^0000FF北西のピラミッド近くの水辺^000000";
		mes "のことですね？";
		mes "特別な水が湧いている場所が";
		mes "あると聞いたことがあります。";
		next;
		mes "[タマリン]";
		mes "そんな特別な場所で体を洗えるとは";
		mes "私はとても運が良いみたいですね！";
		mes "ではちょっと洗ってくるので";
		mes "待っててもらえますか？";
		next;
		mes "[タマリン]";
		mes "まだ体調は万全ではありませんが、";
		mes "1人で歩くことくらいはできます。";
		mes "動けるようになっただけでも十分です！";
		mes "ははは！";
		next;
		if(select("一緒に行く","見守る") == 2) {
			mes "[タマリン]";
			mes "よっ……はっ……ふうう!!";
			mes "……おっと！　ととっと！";
			mes "大丈夫です、立ち上がれます。";
			mes "ふんっ……！　あれ……？";
			next;
			mes "[タマリン]";
			mes "あれれれれ……。";
			set FVOL_1QUE,4;
			close2;
			cutin "ep143_tadir",255;
			end;
		}
	case 5:
		cutin "ep143_tadir",2;
		mes "[タマリン]";
		mes "い、いいんですか？";
		mes "見ず知らずの私に対して";
		mes "こんなに親切にしてくれる人が";
		mes "いるなんて……。";
		mes "いい世の中になりましたね。";
		next;
		mes "[タマリン]";
		mes "では";
		mes "^0000FF北西側にあるピラミッド近くの水辺^000000に";
		mes "一緒に行きましょう。";
		if(FVOL_1QUE != 5) {
			set FVOL_1QUE,5;
			chgquest 11350,11351;
		}
		close2;
		warp "moc_ruins.gat",106,135;
		end;
	default:
		mes "‐微かに寝息が聞こえる。";
		mes "　どうやら疲れて眠っているようだ。";
		mes "　そっとしておこう‐";
		close;
	}
OnInit:
	waitingroom "フレイムヴァレーへの道",0;
	end;
}

moc_ruins.gat,106,140,4	script	タマリン#ep14bs_ru	10027,{
	switch(FVOL_1QUE) {
	case 5:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "ぷはあ！";
		mes "冷たくて気持ちいい！";
		next;
		mes "[タマリン]";
		mes "こんな砂漠で体を洗えるなんて";
		mes "贅沢ではありませんか！";
		next;
		mes "[タマリン]";
		mes "死にかけていた私を助けてくれた";
		mes "だけでなく、水辺まで";
		mes "案内してくださるとは……";
		mes "本当にありがたい事です。";
		next;
		mes "[タマリン]";
		mes "そういえばあなたも冒険家の";
		mes "ようですね。";
		next;
		mes "[タマリン]";
		mes "助けていただいたお礼として、";
		mes "^0000FF真の冒険家なら興味を持つような話^000000を";
		mes "聞かせて差し上げます！";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "それは以前、私が行った";
		mes "不思議な場所の話です。";
		next;
		if(select("興味を見せる","興味ない") == 2) {
			cutin "ep143_tahuk",2;
			mes "[タマリン]";
			mes "興味ないですか？";
			mes "なかなか良い話だと";
			mes "思っているのですが……。";
			next;
			cutin "ep143_tasta",2;
			mes "[タマリン]";
			mes "では……";
			mes "私が受けた恩の代わりとして";
			mes "差し上げるものは……";
			mes "化け物のエサでも返しましょうか？";
			next;
			cutin "ep143_taang",2;
			mes "[タマリン]";
			mes "うえええ……。";
			close2;
			cutin "ep143_taang",255;
			end;
		}
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "やっぱり！";
		mes "不思議な場所と言われて";
		mes "興味を持たない冒険家は";
		mes "いませんからね！";
		next;
		mes "[タマリン]";
		mes "これから私が話す内容は";
		mes "最近の冒険家なら一度は行ってみたい";
		mes "場所^0000FF異世界^000000での旅行から";
		mes "始まります！";
		next;
		mes "[タマリン]";
		mes "冒険家タマリンは仲間たちと一緒に";
		mes "未知の領域！";
		mes "異世界に旅立ちました～。";
		next;
		mes "[タマリン]";
		mes "行く道は険しかったが～";
		mes "彼らは勇気を失わなかった～！";
		next;
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "ん？　どうして急に";
		mes "変なしゃべりになったかですって？";
		next;
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "実を言うと私、歌が得意で、";
		mes "バードになろうと修行中だったのですが";
		mes "友達に強く進められて、";
		mes "ハンターに転職したのです～！";
		next;
		mes "[タマリン]";
		mes "なので、折角ですし";
		mes "その頃を思い出して、";
		mes "得意な歌を歌いながら";
		mes "経緯をお話ししようかと～！";
		next;
		menu "普通にお願いします",-;
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "そうですか？";
		mes "普通にお話した方がいいですか？";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "では普通に……";
		mes "私はつい先日、仲間たちと";
		mes "異世界へ冒険に出ることにしたんです。";
		emotion 33,"";
		next;
		mes "[タマリン]";
		mes "異世界は初めてだったので、";
		mes "まずは次元の狭間を";
		mes "見て回っていたのですが、";
		mes "仲間の一人が興奮して暴れてしまって。";
		next;
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "暴れる仲間を止めようとした私は、";
		mes "次元の狭間にあるひびに気付かず、";
		mes "足を取られそこに落ちてしまいました。";
		next;
		mes "[タマリン]";
		mes "気がつくと仲間の姿は見えず、";
		mes "私は見たこともない場所で";
		mes "一人になっていました。";
		next;
		mes "[タマリン]";
		mes "^0000FF炎が燻るような赤い大地に";
		mes "奇妙な形をした";
		mes "見たことのない植物や昆虫。";
		mes "不気味な空気が漂う場所でした。^000000";
		next;
		mes "[タマリン]";
		mes "私は心細くなって、誰かいないかと";
		mes "叫んで歩き回りました。";
		mes "どのくらい時間が経っていたのかは";
		mes "わかりませんが、かなり長い間";
		mes "一人で彷徨っていたと思います。";
		next;
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "何日か過ぎてからはあまりにも";
		mes "お腹が空いて、いろいろ拾ったものを";
		mes "食べていたらお腹が痛くなり";
		mes "死ぬかと思いました。";
		next;
		mes "[タマリン]";
		mes "精神的にも体力的にも";
		mes "限界を迎えようとしていた時に、";
		mes "突如一人のアサシンが現れたのです。";
		mes "彼もまた酷く衰弱しており、";
		mes "うわ言の様に^0000FFモロクの痕跡をみつけた^000000と";
		mes "つぶやいていました。";
		next;
		mes "[タマリン]";
		mes "彼も私に気づき、";
		mes "いくらか気を持ち直したようで、";
		mes "自分は軍人だ、帰り道を知っているから";
		mes "ついて来いと言われ";
		mes "教えられた赤い大地のひびに";
		mes "体を押し込みました。";
		next;
		mes "[タマリン]";
		mes "軽い眩暈がして目を開けると、";
		mes "そこは仲間たちと一緒に訪れた";
		mes "次元の狭間だったんです。";
		mes "道を教えてくれたアサシンの男性は";
		mes "はぐれたのか、見当たりませんでした。";
		next;
		mes "[タマリン]";
		mes "そしてなんとか";
		mes "モロクに通じる次元移動機に入って、";
		mes "ここモロクに帰ってきたのです……。";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "はぐれた仲間たちが心配です……。";
		mes "今どこで何をしているんでしょう……。";
		next;
	case 6:
		if(FVOL_1QUE == 6)
			cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "みんなを探さないといけないし、";
		mes "私はある程度体が回復したら、";
		mes "もう一度あの場所へ行くつもりです。";
		next;
		if(select("一緒に行くと言う","励みの言葉を言う") == 2) {
			cutin "ep143_tasmi",2;
			mes "[タマリン]";
			mes "はい！";
			mes "助けていただいて、";
			mes "本当にありがとうございました。";
			next;
			mes "[タマリン]";
			mes "冒険というのは";
			mes "本当に素晴らしいことです。";
			mes "こんな素晴らしい人と";
			mes "出会うことができるのですから。";
			next;
			mes "[タマリン]";
			mes "当分の間、私はここでアルバイトでも";
			mes "しながら、もう一度旅の支度をする";
			mes "つもりです。";
			mes "モロクにいる間はまた会うことも";
			mes "あるでしょう。";
			set FVOL_1QUE,6;
			close2;
			cutin "ep143_tasmi",255;
			end;
		}
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "!!";
		next;
		mes "[タマリン]";
		mes "ほ、本当ですか？！";
		next;
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "ありがとうございます!!";
		mes "私は本当に運が良いです。";
		mes "本当は一人であの地へ行くのは";
		mes "心細かったので……。";
		next;
	case 7:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "では、少し休んでから";
		mes "必要な物を用意してくるので、";
		mes "^0000FF次元の狭間^000000でお会いしましょう。";
		next;
		mes "[タマリン]";
		mes "準備に時間がかかるかもしれないので、";
		mes "他に用があるなら済ましてきて下さい。";
		if(FVOL_1QUE != 7) {
			set FVOL_1QUE,7;
			chgquest 11351,11352;
		}
		close2;
		cutin "ep143_tasmi",255;
		end;
	default:
		cutin "ep143_tasmi",2;
		mes "[？？？]";
		mes "ぷはあ！";
		mes "冷たくて気持ちいい！";
		close2;
		cutin "ep143_tasmi",255;
		end;
	}
}

dali.gat,112,69,4	script	タマリン#ep14bs_cha	10027,{
	switch(FVOL_1QUE) {
	case 7:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes strcharinfo(0)+ "様、";
		mes "ここです、ここです！";
		mes "早かったですね！";
		mes "それでは早速……！";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "と言いたいところですが、";
		mes "あの時はあまりにもパニック状態";
		mes "だったので、はっきりとした";
		mes "入口の位置を覚えていないのです。";
		mes "^0000FFこの空間のどこかに";
		mes "あるはず^000000なのですが……。";
		next;
		mes "[タマリン]";
		mes "少し探してみてもらえますか？";
		mes "^0000FFその場所は小さなひびがあるので";
		mes "よく探せばわかるはずです。^000000";
		set FVOL_1QUE,8;
		chgquest 11352,11353;
		close2;
		cutin "ep143_tasta",255;
		end;
	case 8:
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "あの時はあまりにもパニック状態";
		mes "だったので、はっきりとした";
		mes "入口の位置を覚えていないのです。";
		mes "^0000FFこの空間のどこかに";
		mes "あるはず^000000なのですが……。";
		next;
		mes "[タマリン]";
		mes "少し探してみてもらえますか？";
		mes "^0000FFその場所は小さなひびがあるので";
		mes "よく探せばわかるはずです。^000000";
		close2;
		cutin "ep143_tasta",255;
		end;
	default:
		if(FVOL_1QUE < 7) {
			cutin "ep143_tasta",2;
			mes "[？？？]";
			mes "通路から足を踏み外さないように";
			mes "気を付けてくださいね。";
			close2;
			cutin "ep143_tasta",255;
			end;
		}
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes strcharinfo(0)+ "様、";
		mes "あのひびを通る際は";
		mes "とても狭くて暗いので、";
		mes "十分気を付けてくださいね。";
		next;
		mes "[タマリン]";
		mes "私も仲間を探すために何度か";
		mes "あのひびを通っているのですが、";
		mes "狭くておでこをぶつけてしまいます。";
		close2;
		cutin "ep143_tasta",255;
		end;
	}
}

dali.gat,64,98,0	script	ひび#ep14bs	550,{
	switch(FVOL_1QUE) {
	case 8:
		mes "‐この場所には似合わない";
		mes "　ひびがある‐";
		next;
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "ふう！";
		mes "無事見つかりましたね。";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "ではさっそく行きましょう。";
		mes "入口が少し狭いので気をつけて下さい。";
		next;
		if(select("入口に入る","やめる") == 2) {
			cutin "ep143_tahuk",2;
			mes "[タマリン]";
			mes "入らないんですか？";
			close2;
			cutin "ep143_tahuk",255;
			end;
		}
		mes "‐中は一人がやっと通れるくらいに狭く";
		mes "　暗かった‐";
		close2;
		cutin "ep143_tasta",255;
		set FVOL_1QUE,9;
		warp "moro_vol.gat",136,135;
		end;
	default:
		mes "‐この場所には似合わない";
		mes "　ひびがある‐";
		if(FVOL_1QUE < 8)
			close;
		next;
		if(select("入口に入る","やめる") == 2) {
			mes "‐入らないことにした‐";
			close;
		}
		mes "‐中は一人がやっと通れるくらいに狭く";
		mes "　暗かった‐";
		close2;
		warp "moro_vol.gat",136,135;
		end;
	}
}

moro_vol.gat,137,136,0	script	ひび	550,{
	mes "‐この場所には似合わない";
	mes "　ひびがある‐";
	next;
	if(select("次元の狭間に戻る","やめる") == 2) {
		mes "‐戻らないことにした‐";
		close;
	}
	mes "‐中は一人がやっと通れるくらいに狭く";
	mes "　暗かった‐";
	close2;
	warp "dali.gat",64,103;
	end;
OnInit:
	waitingroom "次元の狭間",0;
	end;
}

moro_vol.gat,132,140,4	script	タマリン#ep14bs_ju	10027,{
	viewpoint 2,1,1,1,0xFFFFFF;
	switch(FVOL_1QUE) {
	case 9:
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "うわー、いつの間にこんなに多くの人が";
		mes "集まったんでしょう。";
		mes "以前は全然人の気配がなかったのに。";
		next;
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "武装した人もいるし……。";
		mes "もしかして私を助けてくれた";
		mes "あのアサシンの男性が呼んだのかな？";
		mes "なんだか雰囲気が怪しいですね……。";
		next;
		mes "[タマリン]";
		mes "人の姿じゃない人（？）達も";
		mes "多く見られますね……。";
		mes "これはもしかすると、";
		mes "私が思っていたよりも";
		mes "凄い場所なのかもしれません!!";
		next;
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "それに、これだけ多くの人がいれば";
		mes "私の仲間を見かけた人が";
		mes "いるかもしれません！";
		next;
		if(checkquest(200875)) {	// 三ヶ国への報告書クエスト？
			cutin "ep13_captin_edq",2;
			mes "[司令官アジフ]";
			mes "お？";
			mes strcharinfo(0)+ "じゃないか！";
			mes "お前も来てくれたのか！";
			next;
			mes "[司令官アジフ]";
			mes "ここは先遣隊のひとりが発見した";
			mes "^0000FF魔王モロクが潜む地、";
			mes "フレイムヴァレー^000000だ。";
			mes "現在各所を調査中でな、";
			mes "少しずつだが";
			mes "わかってきたこともある。";
			next;
			mes "[司令官アジフ]";
			mes "早いとこ調査を進めて";
			mes "魔王とご対面、と行きたい所なんだが。";
			mes "まあ、焦りは禁物ってヤツだな。";
			next;
			mes "[司令官アジフ]";
			mes "ところでこの人の数を見てくれ！";
			mes "打倒モロクの旗印の下、";
			mes "サファ族もラフィネ族も";
			mes "種族間のわだかまりを超えて";
			mes "これだけの数が集まってくれたんだ！";
			next;
			mes "[司令官アジフ]";
			mes "これだけの規模の連合軍が";
			mes "結成されたんだ。";
			mes "いよいよ魔王モロクも";
			mes "年貢の納め時、ってとこだな！";
			next;
			mes "[司令官アジフ]";
			mes "俺はここから西の方角に";
			mes "本部を構えているから、";
			mes "何かあったら訪ねてくるといい。";
			mes "ここは危険な場所も多いから";
			mes "あまり無茶はするなよ。";
			next;
			cutin "ep13_captin_edq",255;
			mes "[バゼット]";
			mes "!?　そこのあなたたち!!";
			mes "何をしているんですか!!";
			next;
			cutin "ep13_captin_edq",2;
			mes "[司令官アジフ]";
			mes "おっと！";
			mes "怖い博士に見つかってしまった。";
			mes "俺は本部に戻る。";
			mes "くれぐれも無茶はするなよ！";
			next;
			cutin "ep13_captin_edq",255;
			mes "[バゼット]";
			mes "……今のはアジフ司令官？";
			mes "全く、油を売っている暇があるなら";
			mes "こちらを手伝ってほしいものですね！";
			mes "そして……そこのあなた達！";
			mes "あなた達は何をしているのですか！";
		}
		else {
			emotion 6,"バゼット#ep14bs";
			cutin "ep143_tahuk",255;
			mes "[バゼット]";
			mes "!?　そこのあなたたち!!";
			mes "何をしているんですか!!";
		}
		viewpoint 1,142,131,0,0xFF0000;
		set FVOL_1QUE,10;
		chgquest 11353,11354;
		close;
	case 10:
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "そういえば私を助けてくれた";
		mes "あのアサシンの男性が";
		mes "^0000FFモロクの痕跡をみつけた^000000と";
		mes "言っていました。";
		next;
		mes "[タマリン]";
		mes "ここは何か";
		mes "モロクと関係する地なのでしょうか。";
		next;
		cutin "ep143_tahuk",255;
		emotion 6,"バゼット#ep14bs";
		mes "[バゼット]";
		mes "そこのあなたたち!!";
		mes "ちょっとこちらにきなさい！";
		close;
	case 11:
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "こっそり来た事がばれると";
		mes "追い出されるかもしれません。";
		mes "まずは言う通りにした方が";
		mes "良さそうですね。";
		close2;
		cutin "ep143_taang",255;
		end;
	case 12:
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "植物標本を採集するだけなら、";
		mes "そこまで大変そうでもないので";
		mes "半分ずつ集めることにしましょう。";
		next;
		mes "[タマリン]";
		mes "^0000FFソニアの茎を1個集めたら、";
		mes "ここの中央にある大きな岩の前で";
		mes "待ち合わせて一緒に戻りましょう。^000000";
		viewpoint 1,198,179,2,0xFF0000;
		set FVOL_1QUE,13;
		chgquest 11356,11357;
		close2;
		cutin "ep143_tasta",255;
		end;
	case 13:
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "植物標本を採集するだけなら、";
		mes "そこまで大変そうでもないので";
		mes "半分ずつ集めることにしましょう。";
		next;
		mes "[タマリン]";
		mes "^0000FFソニアの茎を1個集めたら、";
		mes "ここの中央にある大きな岩の前で";
		mes "待ち合わせて一緒に戻りましょう。^000000";
		viewpoint 1,198,179,2,0xFF0000;
		close2;
		cutin "ep143_tasta",255;
		end;
	case 14:
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "まずはバゼットさんに報告しませんか？";
		close2;
		cutin "ep143_tahuk",255;
		end;
	case 15:
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "急いで^0000FFルーゲン教官^000000の所に";
		mes "向かいましょう！";
		mes "一刻を争います!!";
		close2;
		cutin "ep143_tahuk",255;
		end;
	case 16:
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "^0000FFソニアの茎を";
		mes "患者に食べさせてみましょう！^000000";
		close2;
		cutin "ep143_tahuk",255;
		end;
	case 17:
		cutin "ep143_tahuk",2;
		mes "[タマリン]";
		mes "ソニアの茎は患者の様態を";
		mes "落ち着かせる効果があるみたいですね。";
		mes "^0000FFルーゲン教官^000000に";
		mes "報告しましょう。";
		close2;
		cutin "ep143_tahuk",255;
		end;
	case 18:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "空腹のあまりに食べた";
		mes "植物がこんな形で役に立つとは！";
		mes "急いでバゼットさんに報告しましょう！";
		close2;
		cutin "ep143_tasmi",255;
		end;
	case 100:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "ここには人もたくさんいますし、";
		mes "ここからはもう一人でも大丈夫です。";
		mes "今まで本当にありがとうございました！";
		next;
		mes "[タマリン]";
		mes "もし中央の岩にあるという";
		mes "洞窟に入ることがあったら、";
		mes "私にひと声かけてくださいね。";
		close2;
		cutin "ep143_tasmi",255;
		end;
	}
}

moro_vol.gat,142,131,5	script	バゼット#ep14bs	883,{
	viewpoint 2,1,1,0,0xFFFFFF;
	switch(FVOL_1QUE) {
	case 10:
		mes "[バゼット]";
		mes "ああ、あなた達！";
		mes "そこを踏み荒らさないでください！";
		mes "せっかく集めておいたサンプルが";
		mes "メチャクチャになってしまったじゃ";
		mes "ありませんか！";
		next;
		mes "[バゼット]";
		mes "キャンプ側の調査もまだ完全に";
		mes "終えてないのに……。";
		mes "作業中の地域では気を付けて下さい！";
		mes "私の仕事を増やす気ですか!?";
		next;
		mes "[バゼット]";
		mes "こんなことになるとわかっていたら";
		mes "もっと助手を用意して欲しいと";
		mes "言うべきだった……。";
		mes "圧倒的に人手が足りなすぎる！";
		next;
		mes "[バゼット]";
		mes "ハッ……!!";
		mes "すみません、忙しさのあまり";
		mes "取り乱してしまいました……。";
		mes "私は軍の先遣隊が発見した";
		mes "ここ、フレイムヴァレーの調査を";
		mes "担当しているバゼットといいます。";
		next;
		mes "[バゼット]";
		mes "私たちの軍の先遣隊の多くは、";
		mes "次元移動機を通って、";
		mes "このフレイムヴァレーにきました。";
		next;
		mes "[バゼット]";
		mes "しかし……。";
		mes "一つの軍隊ほどの人数が調査に出たのに、";
		mes "戻ってきたのはたった数名で、";
		mes "しかも彼らはひどく弱っていました。";
		next;
		mes "[バゼット]";
		mes "先遣隊の調査結果で";
		mes "ここが魔王モロクに関係する地なのは";
		mes "間違いないとのことでしたが……。";
		mes "……この地は何かがおかしい。";
		next;
		mes "[バゼット]";
		mes "弱って帰ってきた先遣隊のように";
		mes "今ここにいる者たちを";
		mes "危険な目にあわすことのないよう";
		mes "急いで調査を進めているのです。";
		next;
		mes "[バゼット]";
		mes "そうだあなた達。見ない顔ですが、";
		mes "見るからに暇そうですね。";
		mes "サンプルを集める仕事を";
		mes "手伝って下さいよ！";
		next;
		mes "[バゼット]";
		mes "あなた達が研究用のサンプルを";
		mes "踏み荒らしたせいで、";
		mes "メチャクチャなってしまったので";
		mes "責任を取ってもらわないと！";
		mes "嫌とは言わせませんよ！";
		next;
		mes "[バゼット]";
		mes "まずは虫の標本を集めてください。";
		mes "この地域では変形している生物が";
		mes "たくさん見つかっていますが、";
		mes "その中から^0000FF完全に新しい種^000000が";
		mes "ひとつだけ見つかりました。";
		next;
		mes "[バゼット]";
		mes "^0000FF燃える虫のような姿をしているので、";
		mes "フレイムバグと呼んでいます。";
		mes "他の虫に比べちょっと変わっているのは";
		mes "フレイムピットと呼ばれる火の穴に";
		mes "住んでいる^000000という事です。";
		next;
		mes "[バゼット]";
		mes "時々外に出ている奴らもいますが、";
		mes "火の穴の外に出てしまうと";
		mes "すぐ死んでしまいます。";
		next;
		mes "[バゼット]";
		mes "そこで^0000FFフレイムピットを2個調査し、";
		mes "破壊した後、^000000";
		mes "フレイムバグを探し出して倒し、";
		mes "^0000FFフレイムバグの皮を1個";
		mes "採取して来て下さい。^000000";
		next;
		mes "[バゼット]";
		mes "熱いかもしれないので";
		mes "十分気を付けてくださいね。";
		set FVOL_1QUE,11;
		chgquest 11354,11355;
		close;
	case 11:
		if(checkquest(11355)&0x4 == 0 || countitem(6689) == 0) {
			mes "[バゼット]";
			mes "まずは虫の標本を集めてください。";
			mes "この地域では変形している生物が";
			mes "たくさん見つかっていますが、";
			mes "その中から^0000FF完全に新しい種^000000が";
			mes "ひとつだけ見つかりました。";
			next;
			mes "[バゼット]";
			mes "^0000FF燃える虫のような姿をしているので、";
			mes "フレイムバグと呼んでいます。";
			mes "他の虫に比べちょっと変わっているのは";
			mes "フレイムピットと呼ばれる火の穴に";
			mes "住んでいる^000000という事です。";
			next;
			mes "[バゼット]";
			mes "時々外に出ている奴らもいますが、";
			mes "火の穴の外に出てしまうと";
			mes "すぐ死んでしまいます。";
			next;
			mes "[バゼット]";
			mes "そこで^0000FFフレイムピットを2個調査し、";
			mes "破壊した後、^000000";
			mes "フレイムバグを探し出して倒し、";
			mes "^0000FFフレイムバグの皮を1個";
			mes "採取して来て下さい。^000000";
			next;
			mes "[バゼット]";
			mes "熱いかもしれないので";
			mes "十分気を付けてくださいね。";
			close;
		}
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[バゼット]";
		mes "お！　帰ってきましたね！";
		mes "ご苦労様でした！";
		mes "思っていたより";
		mes "早かったですね。";
		delitem 6689,1;
		set FVOL_1QUE,12;
		chgquest 11355,11356;
		next;
		mes "[バゼット]";
		mes "うわ！　あっちっち!!";
		mes "ふー！　ふー!!!!";
		mes "これは冷める前にうまく保存して";
		mes "実験室に送っといて……。";
		next;
		mes "[バゼット]";
		mes "次は植物標本を集めてください。";
		mes "採取しなければならない植物は、";
		mes "^FF0000ソニア^000000というとても原始的な姿を";
		mes "している植物です。";
		next;
		mes "[バゼット]";
		mes "パッと見た感じでは植物というよりは、";
		mes "プラスチックでつくったホースに";
		mes "見えますが、植物が備えておくべき";
		mes "一番基本的な構造をしています。";
		next;
		mes "[バゼット]";
		mes "ソニアを倒すと";
		mes "^0000FFソニアの茎^000000を落とします。";
		mes "その^0000FFソニアの茎を2個^000000";
		mes "持って来て下さい。";
		next;
		mes "[バゼット]";
		mes "ソニアの標本を採集すれば";
		mes "標本を集める仕事は終わりなので、";
		mes "もし作業中に^0000FF珍しい物でも発見^000000したら";
		mes "教えて下さい。";
		next;
		mes "[バゼット]";
		mes "危ないかもしれないので、本拠地から";
		mes "あまり遠くには行かないで下さい。";
		mes "気を付けて行ってきて下さいね。";
		mes "よろしくお願いします。";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "ふむ……";
		mes strcharinfo(0)+ "様、";
		mes "良い案を思いついたので";
		mes "ちょっと待って下さい！";
		viewpoint 1,132,140,1,0xFF0000;
		close2;
		cutin "ep143_tasta",255;
		end;
	case 12:
	case 13:
		mes "[バゼット]";
		mes "次は植物標本を集めてください。";
		mes "採取しなければならない植物は、";
		mes "^FF0000ソニア^000000というとても原始的な姿を";
		mes "している植物です。";
		next;
		mes "[バゼット]";
		mes "パッと見た感じでは植物というよりは、";
		mes "プラスチックでつくったホースに";
		mes "見えますが、植物が備えておくべき";
		mes "一番基本的な構造をしています。";
		next;
		mes "[バゼット]";
		mes "ソニアを倒すと";
		mes "^0000FFソニアの茎^000000を落とします。";
		mes "その^0000FFソニアの茎を2個^000000";
		mes "持って来て下さい。";
		next;
		mes "[バゼット]";
		mes "ソニアの標本を採集すれば";
		mes "標本を集める仕事は終わりなので、";
		mes "もし作業中に^0000FF珍しい物でも発見^000000したら";
		mes "教えて下さい。";
		next;
		mes "[バゼット]";
		mes "危ないかもしれないので、本拠地から";
		mes "あまり遠くには行かないで下さい。";
		mes "気を付けて行ってきて下さいね。";
		mes "よろしくお願いします。";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "ふむ……";
		mes strcharinfo(0)+ "様、";
		mes "良い案を思いついたので";
		mes "ちょっと待って下さい！";
		viewpoint 1,132,140,1,0xFF0000;
		close2;
		cutin "ep143_tasta",255;
		end;
	case 14:
		mes "[バゼット]";
		mes "おかえりなさい！";
		mes "無事に戻ったのですね！";
		mes "よかったです。あわてていて、";
		mes "^0000FF中央にある岩の近くに行ってはならない^000000";
		mes "と言うのを忘れていました。";
		next;
		mes "[バゼット]";
		mes "念のため救助隊を手配したのですが、";
		mes "無事に戻って来れて";
		mes "よかったです。";
		next;
		mes "[バゼット]";
		mes "危険な場所を伝え忘れて";
		mes "本当にすみません。";
		mes "殺人的な調査スケジュールに追われ、";
		mes "大事な事を失念してしまったばかりか、";
		mes "あなた方を危険に晒してしまいました。";
		next;
		mes "[バゼット]";
		mes "まだ処理しなければならない仕事も";
		mes "山のように積もっているし……";
		mes "ふう……。";
		next;
		menu "中央にある岩について話す",-;
		mes "[バゼット]";
		mes "なんですって!?";
		mes "あそこに行ったんですか？";
		mes "なんという事だ!!";
		mes "しかし、それが事実なら";
		mes "なぜあなた方は無事なのですか？";
		next;
		mes "[バゼット]";
		mes "あの場所を調査していた人は皆、";
		mes "^0000FF岩から出る毒ガスのせいで昏睡状態^000000に";
		mes "陥ったのに！";
		next;
		mes "[バゼット]";
		mes "どういう事だ……？";
		mes "……何か特別な事をしましたか？";
		mes "何か食べたとか、飲んだとか……";
		next;
		menu "ソニアの茎を食べた",-;
		mes "[バゼット]";
		mes "ソニアの茎を食べた？";
		mes "毒性がないのはわかっていたのですが、";
		mes "まだ調査が終わっていない植物の茎を";
		mes "食べて体に何か異常は起きていませんか？";
		next;
		menu "なんともない",-;
		mes "[バゼット]";
		mes "な、なんという事だ!!";
		mes "これは本当に素晴らしい発見だ!!";
		next;
		mes "[バゼット]";
		mes "早く研究を……";
		mes "いや、それより今は^0000FF体調が悪い患者が";
		mes "南の方に集まっているので、";
		mes "急いでソニアの茎を届けるのが先です！^000000";
		next;
		mes "[バゼット]";
		mes "もしかしたら患者の症状が";
		mes "治まるかもしれません。";
		next;
		mes "[バゼット]";
		mes "^0000FFルーゲン教官^000000が看病しているので";
		mes "あの方に茎を渡してください。";
		mes "この手紙に私が経緯を書いておくので";
		mes "これも一緒に渡してください。";
		next;
		mes "[バゼット]";
		mes "私はここで";
		mes "研究を始められるようにします！";
		mes "あと、今回は運よく無事でしたが、";
		mes "今後は何でも口に入れたりしないで";
		mes "下さいね！";
		viewpoint 1,105,71,3,0xFFFF0000;
		set FVOL_1QUE,15;
		chgquest 11358,11359;
		close;
	case 15:
		mes "[バゼット]";
		mes "早く研究を……";
		mes "いや、それより今は^0000FF体調が悪い患者が";
		mes "南の方に集まっているので、";
		mes "急いでソニアの茎を届けるのが先です！^000000";
		next;
		mes "[バゼット]";
		mes "もしかしたら患者の症状が";
		mes "治まるかもしれません。";
		next;
		mes "[バゼット]";
		mes "^0000FFルーゲン教官^000000が看病しているので";
		mes "あの方に茎を渡してください。";
		mes "この手紙に私が経緯を書いておくので";
		mes "これも一緒に渡してください。";
		next;
		mes "[バゼット]";
		mes "私はここで";
		mes "研究を始められるようにします！";
		mes "あと、今回は運よく無事でしたが、";
		mes "今後は何でも口に入れたりしないで";
		mes "下さいね！";
		viewpoint 1,105,71,3,0xFF0000;
		close;
	case 16:
	case 17:
		mes "[バゼット]";
		mes "ルーゲン教官の所には行って来ました？";
		close;
	case 18:
		mes "[バゼット]";
		mes "ふふふふふ!!!!";
		mes "どうでした?!";
		mes "やはり効果はありましたよね？";
		next;
		mes "[バゼット]";
		mes "研究の方もかなり良い結果が";
		mes "出ると思います！";
		mes "無謀な行動でしたが、";
		mes "おかげで多くの命を";
		mes "救うことができました!!";
		next;
		mes "[バゼット]";
		mes "これであの^0000FF怪しい洞窟^000000を";
		mes "隅から隅まで調査できそうです！";
		next;
		menu "洞窟？",-;
		mes "[バゼット]";
		mes "毒ガスが漏れている岩があるでしょう？";
		mes "あの岩には洞窟があるのです。";
		mes "^0000FFガスがあまりにも濃く出過ぎて";
		mes "入口がよく見えない程^000000ですが。";
		next;
		mes "[バゼット]";
		mes "しかしこのソニアの茎があれば";
		mes "毒ガスに臆することもなく、";
		mes "洞窟を調査することができます！";
		next;
		mes "[バゼット]";
		mes "お二人がいなければ、";
		mes "まだ頭を抱えていたことでしょう。";
		mes "本当にありがとうございました！";
		next;
		mes "[バゼット]";
		mes "調査に協力してもらったり";
		mes "ソニアの茎を届けてもらったり、";
		mes "いろいろあって疲れているでしょう。";
		mes "しばらくここで休んでいてください。";
		next;
		mes "[バゼット]";
		mes "私はその間にワクチンを作って";
		mes "みんなに配ってきます。";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "[バゼット]";
		mes "少しは休めましたか？";
		next;
		mes "[バゼット]";
		mes "お二人が休んでいる間に、";
		mes "ワクチンを投与した部隊が";
		mes "洞窟へと向かいました。";
		mes "問題が発生したという連絡も";
		mes "ありませんし、ワクチンの効果が";
		mes "効いているようですね。";
		next;
		mes "[バゼット]";
		mes "お二人は既に抗体ができていますから、";
		mes "ワクチンを接種しなくても";
		mes "あの洞窟に入れるでしょう。";
		mes "安心して調査してきてください。";
		next;
		mes "[バゼット]";
		mes "あと、ここから西に行った場所に";
		mes "我々の本部があります。";
		mes "何か困ったことがあったら";
		mes "行ってみてください。";
		next;
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes strcharinfo(0) + "様、";
		mes "一段落ついたようですし、";
		mes "私はこれから別れた仲間を";
		mes "探したいと思います。";
		next;
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "ここには人もたくさんいますし、";
		mes "ここからはもう一人でも大丈夫です。";
		mes "今まで本当にありがとうございました！";
		next;
		mes "[タマリン]";
		mes "その中央の岩にあるという";
		mes "洞窟付近を中心に探すつもりなので、";
		mes "洞窟に入ることがあったら";
		mes "ひと声かけてくださいね。";
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		set FVOL_1QUE,100;
		chgquest 11362,201705;
		close2;
		cutin "ep143_tasmi",255;
		end;
	case 100:
		mes "[バゼット]";
		mes "本当にお二人がいなければ、";
		mes "まだ頭を抱えていたことでしょう。";
		mes "本当にありがとうございました！";
		next;
		mes "[バゼット]";
		mes "ここから西に行った場所に";
		mes "我々の本部がありますから、";
		mes "何か困ったことがあったら";
		mes "行ってみてください。";
		close;
	default:
		mes "[バゼット]";
		mes "ああ……疲れた。";
		mes "いくら急ぎの仕事だとしても、";
		mes "働かせすぎじゃないか？";
		close;
	}
}

moro_vol.gat,198,179,4	script	タマリン#ep14bs_st	10027,{
	viewpoint 2,1,1,2,0xFFFFFF;
	switch(FVOL_1QUE) {
	case 13:
		if(countitem(6690)==0) {
			cutin "ep143_tasta",2;
			mes "[タマリン]";
			mes "^0000FFソニアの茎を1個集めたら、";
			mes "この大きな石の前で待ち合わせて";
			mes "一緒に戻りましょう^000000。";
			close2;
			cutin "ep143_tasta",255;
			end;
		}
		cutin "ep143_tasta",2;
		mes "[タマリン]";
		mes "そういえばこの前に来た時には、";
		mes "この石はここまで大きくなかったような";
		mes "気がするんだけど……。";
		mes "周りにいた変な生き物も";
		mes "やけに成長していますね。";
		mes "^0000FF怪しい煙^000000も出ていますし……。";
		next;
		mes "[タマリン]";
		mes "それに……";
		mes "^0000FFあの時は変わった生き物たちも";
		mes "こんなに多くなかったような……^000000";
		mes "ソニアだったかな、これもこんなに多く";
		mes "生えていませんでした。";
		next;
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "ここで食べた物の中では毒もなく、";
		mes "一番美味しかったのが";
		mes "このソニアだったのですが……";
		mes "その時はここまで多くなかったので、";
		mes "空腹を満たす事は難しかったんです。";
		next;
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes strcharinfo(0)+ "様も食べてみますか？";
		mes "少し多めに持って来たので……。";
		next;
		cutin "ep143_tasmi",255;
		mes "‐ソニアの味、";
		mes "　暖かくて弾力のある茎から、";
		mes "　恍惚な自然の味が広がり……";
		mes "　おいしい‐";
		next;
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "どうですか？";
		mes "なかなか美味しいでしょう！";
		next;
		mes "[タマリン]";
		mes "っと、うっかり渡す分まで";
		mes "食べちゃいそうなので、";
		mes "早くバゼットさんのところに";
		mes "戻りましょう。";
		cutin "ep143_tasmi",2;
		set FVOL_1QUE,14;
		chgquest 11357,11358;
		viewpoint 1,142,131,0,0xFF0000;
		close2;
		cutin "ep143_tasmi",255;
		end;
	case 14:
		mes "[タマリン]";
		mes "っと、うっかり渡す分まで";
		mes "食べちゃいそうなので、";
		mes "早くバゼットさんのところに";
		mes "戻りましょう。";
		cutin "ep143_tasmi",2;
		viewpoint 1,142,131,0,0xFF0000;
		close2;
		cutin "ep143_tasmi",255;
		end;
	case 100:
		cutin "ep143_tasmi",2;
		mes "[タマリン]";
		mes "あ、" +strcharinfo(0)+ "様、";
		mes "これだけ人が多いと";
		mes "逆に探すのが大変ですね！";
		mes "洞窟に入るなら案内しましょうか？";
		next;
		if(select("入る","入らない") == 2) {
			cutin "ep143_tasta",2;
			mes "[タマリン]";
			mes "そうですか。";
			mes "では私は仲間探しに戻りますね。";
			close2;
			cutin "ep143_tasmi",255;
			end;
		}
		mes "[タマリン]";
		mes "地面が良く見えないので";
		mes "足元に気を付けて下さいね！";
		close2;
		cutin "ep143_tasmi",255;
		warp "moro_cav.gat",59,14;
		end;
	default:
		cutin "ep143_taang",2;
		mes "[タマリン]";
		mes "うむ……";
		mes "今はこんな事をしている場合じゃ";
		mes "ありません！";
		close2;
		cutin "ep143_taang",255;
		end;
	}
}

moro_cav.gat,64,13,0	warp	#ep14_3洞窟出口	1,1,moro_vol.gat,198,176

moro_vol.gat,105,71,5	script	ルーゲン教官#ep14bs	405,{
	viewpoint 2,1,1,3,0xFFFFFF;
	switch(FVOL_1QUE) {
	case 15:
		mes "[ルーゲン教官]";
		mes "大丈夫か？";
		mes "気をしっかり持つんだ。";
		next;
		mes "[ルーゲン教官]";
		mes "バゼット博士が";
		mes "色々調べてくれているから、";
		mes "もう少しだけ、頑張ってくれ……。";
		next;
		if(select("話しかけてみる","深刻そうにみえるのでやめておく") == 2) {
			mes "[ルーゲン教官]";
			mes "もう少しだ、もう少しの辛抱だ。";
			mes "頑張ってくれ……。";
			close;
		}
		mes "[ルーゲン教官]";
		mes "どうしましたか？";
		mes "痛めている所があれば受付に";
		mes "症状を話して待っていて下さい。";
		if(countitem(6690)==0)
			close;
		next;
		menu "ソニアの茎と手紙を渡す",-;
		mes "[ルーゲン教官]";
		mes "!!　それは本当ですか？";
		mes "なになに、ふむふむ……";
		mes "手紙にも茎の事が書いてあります！";
		mes "さっそく患者たちに";
		mes "食べさせてみましょう！";
		delitem 6690,1;
		set FVOL_1QUE,16;
		chgquest 11359,11360;
		close;
	case 16:
		mes "[ルーゲン教官]";
		mes "!!　それは本当ですか？";
		mes "なになに、ふむふむ……";
		mes "手紙にも茎の事が書いてあります！";
		mes "さっそく患者たちに";
		mes "食べさせてみましょう！";
		close;
	case 17:
		mes "[ルーゲン教官]";
		mes "おお！";
		mes "オトゥ！";
		mes "どうだ？　大丈夫か!?";
		next;
		mes "[オトゥ]";
		mes "はぁ……あ……";
		mes "……ルーゲン……教官……";
		next;
		mes "[ルーゲン教官]";
		mes "ああ……意識が戻ったか！";
		mes "よかった、本当に良かった!!";
		next;
		mes "[ルーゲン教官]";
		mes "まだ完全に回復はしてないようですが、";
		mes "患者の状態が";
		mes "かなり良くなったようです。";
		mes "まずは症状の重い患者に茎を与え、";
		mes "残りはバゼット博士の研究結果が";
		mes "出るのを待った方が良さそうです。";
		next;
		mes "[ルーゲン教官]";
		mes "効果がとても良かったと";
		mes "手紙に書きましたので、";
		mes "^0000FFバゼット博士^000000に渡して下さい。";
		mes "本当に助かりました。";
		mes "ありがとうございます。";
		viewpoint 1,142,131,0,0xFF0000;
		set FVOL_1QUE,18;
		chgquest 11361,11362;
		close;
	case 18:
		mes "[ルーゲン教官]";
		mes "まだ完全に回復はしてないようですが、";
		mes "患者の状態が";
		mes "かなり良くなったようです。";
		mes "まずは症状の重い患者に茎を与え、";
		mes "残りはバゼット博士の研究結果が";
		mes "出るのを待った方が良さそうです。";
		next;
		mes "[ルーゲン教官]";
		mes "効果がとても良かったと";
		mes "手紙に書きましたので、";
		mes "^0000FFバゼット博士^000000に渡して下さい。";
		mes "本当に助かりました。";
		mes "ありがとうございます。";
		viewpoint 1,142,131,0,0xFFFF0000;
		close;
	case 100:
		mes "[ルーゲン教官]";
		mes "私の仲間たちもおかげ様で";
		mes "状態が良くなりました。";
		mes "ありがとうございます。";
		close;
	default:
		mes "[ルーゲン教官]";
		mes "大丈夫か？";
		mes "気をしっかり持つんだ。";
		next;
		mes "[ルーゲン教官]";
		mes "バゼット博士が";
		mes "色々調べてくれているから、";
		mes "もう少しだけ、頑張ってくれ……。";
		close;
	}
}

moro_vol.gat,104,70,4	script	中毒になった患者	887,{
	if(FVOL_1QUE > 16) {
		mes "[中毒になった患者]";
		mes "ふぅ……ふぅ……。";
		next;
		mes "‐今は落ち着いて眠っている‐";
		close;
	}
	mes "[中毒になった患者]";
	mes "う……うぅ……";
	if(FVOL_1QUE != 16)
		close;
	next;
	mes "‐中毒になった患者に";
	mes "　ソニアの茎を食べさせたら、";
	mes "　顔色がよくなった‐";
	set FVOL_1QUE,17;
	chgquest 11360,11361;
	close;
}

moro_vol.gat,101,72,4	script	患者	585,{
	mes "[患者]";
	mes "う……ううう……";
	close;
}

moro_vol.gat,101,74,4	script	患者	441,{
	mes "[患者]";
	mes "くううう……";
	close;
}

moro_vol.gat,103,71,6	script	患者	584,{
	mes "[患者]";
	mes "くう……うう……";
	close;
}

moro_vol.gat,106,69,4	script	患者	585,{
	mes "[患者]";
	mes "ああ……う……";
	close;
}

//============================================================
// 滅亡祝福教団クエスト
//- Registry -------------------------------------------------
// FVOL_2QUE -> 0～13
//------------------------------------------------------------
moro_vol.gat,131,103,3	script	駐屯地調査官#bl	419,{
	viewpoint 2,1,1,4,0xFFFFFF;
	switch(FVOL_2QUE) {
	case 0:
		mes "[駐屯地調査官]";
		mes "あなたも気付きましたか？";
		mes "そうです、この周辺に生息している";
		mes "モンスター達は何かがおかしい。";
		next;
		mes "[駐屯地調査官]";
		mes "ミッドガルドでも一部地域でしか";
		mes "見る事が出来ないモンスター達が、";
		mes "何らかの原因で変化した状態で";
		mes "この周辺を動き回っている。";
		next;
		mes "[駐屯地調査官]";
		mes "さらに問題なのは徐々にその数が";
		mes "増えていることなんです。";
		mes "やつらが物理的に危険な点以外にも、";
		mes "どのような害を与えるかを";
		mes "調査しなければならないのですが……。";
		next;
		mes "[駐屯地調査官]";
		mes "みんな忙しくて";
		mes "頼めそうな人がいません……。";
		mes "急ぎの調査なのに……。";
		if(BaseLevel < 140) {
			next;
			mes "‐^0000FF滅亡祝福教団^000000は";
			mes "　^FF0000BaseLv140以上^000000から";
			mes "　開始することができるクエストです‐";
			close;
		}
		next;
		switch(select("何が起きているんですか？","直接やったらどうですか？","お手伝いしましょうか？")) {
		case 1:
			mes "[駐屯地調査官]";
			mes "ここの環境が不安定で";
			mes "調査がなかなか進みません。";
			mes "ここは見たことがあるようで";
			mes "初めて訪れたような気もするし、";
			mes "消滅しそうな危うさもありながら";
			mes "いたる所に躍動感が感じられる。";
			next;
			mes "[駐屯地調査官]";
			mes "何なんだ……";
			mes "いったいここの正体は何だろう……。";
			close;
		case 2:
			mes "[駐屯地調査官]";
			mes "そうしたいけど、";
			mes "私は調査担当なのです。";
			mes "戦闘にも不向きなもので……。";
			mes "指示しかできません。";
			emotion 4,"";
			close;
		case 3:
			mes "[駐屯地調査官]";
			mes "本当ですか？　ありがたい!!";
			mes "ぜひお願いします！　それでは……";
			mes "モンスターの中でもとりわけ危険そうな";
			mes "^0000FFフレイムコンドル^000000の調査をしたいので";
			mes "お手伝いをお願いしたいです。";
			next;
			mes "[駐屯地調査官]";
			mes "フレイムコンドルは";
			mes "こちらから手を出さなければ";
			mes "おとなしいのですが、";
			mes "うっかり火が付いている尻尾に触れると";
			mes "全治三週間の大やけどです。";
			next;
			menu "ではそれを捕まえてきましょうか。",-;
			mes "[駐屯地調査官]";
			mes "いえ、捕まえてきたら";
			mes "処理が大変ですね……。";
			mes "調査が目的だから、";
			mes "^0000FFフレイムコンドル^000000の体に付いている";
			mes "^FF0000火のついた羽^000000を15個ほど";
			mes "持ってきてください。";
			next;
			if(select("私も忙しいです！","用意して来ます。") == 1) {
				mes "[駐屯地調査官]";
				mes "そうですか。";
				mes "残念です。";
				close;
			}
			mes "[駐屯地調査官]";
			mes "ありがとうございます！";
			mes "今も被害者が増えているので";
			mes "できる限り急いで下さい！";
			mes "お願いします!!";
			set FVOL_2QUE,1;
			setquest 1264;
			close;
		}
	case 1:
		if(countitem(6691) < 15) {
			mes "[駐屯地調査官]";
			mes "あなたが頑張って";
			mes "^0000FFフレイムコンドル^000000の";
			mes "^FF0000火のついた羽^000000を15個";
			mes "集めてきてくれると思ったから、";
			mes "調査隊員達を緊急招集して";
			mes "おきましたが……。";
			next;
			mes "[駐屯地調査官]";
			mes "まだ集まってないのですね……。";
			mes "ここでお待ちしていますので";
			mes "できる限り急いで下さい！";
			mes "お願いします!!";
			close;
		}
		mes "[駐屯地調査官]";
		mes "^FF0000火のついた羽^000000を";
		mes "15個集めてきたんですね？";
		mes "おかげで十分な調査が";
		mes "進められると思います。";
		next;
		mes "[駐屯地調査官]";
		mes "何よりも、火を点けることが";
		mes "出来るようになったことが嬉しいです。";
		emotion 21;
		next;
		mes "[駐屯地調査官]";
		mes "あなた……";
		mes "もしかして私の表情から、";
		mes "今私が抱えている悩みを";
		mes "読み取りましたね？";
		next;
		switch(select("何のことですか？","最初から気づいていました！")) {
		case 1:
			mes "[駐屯地調査官]";
			mes "……期待していた答えでは";
			mes "ありませんでしたが、";
			mes "めげずに準備しておいた話を";
			mes "続けます……！";
			next;
			mes "[駐屯地調査官]";
			mes "フレイムヴァレー一帯を偵察に行った";
			break;
		case 2:
			mes "[駐屯地調査官]";
			mes "素晴らしい……。";
			next;
			mes "[駐屯地調査官]";
			mes "実は、";
			mes "フレイムヴァレー一帯の偵察に行った";
			break;
		}
		mes "兵士が戻ってこないのです。";
		mes "何が起きているのか";
		mes "調べてきてもらえませんか？";
		next;
		if(select("忙しいです","分かりました") == 1) {
			mes "[駐屯地調査官]";
			mes "そうですか。";
			mes "残念です。";
			close;
		}
		mes "[駐屯地調査官]";
		mes "ありがとうございます！";
		mes "兵士は、北東の";
		mes "モンスターが密集している地域に";
		mes "向かったはずです。";
		mes "周りをよく調べながら偵察兵を";
		mes "見つけて下さい。";
		delitem 6691,15;
		set FVOL_2QUE,2;
		chgquest 1264,1265;
		viewpoint 1,234,301,5,0xFF0000;
		close;
	case 2:
	case 3:
		mes "[駐屯地調査官]";
		mes "偵察兵を探しに行ってもらったのに、";
		mes "どうして私の前を探しているんですか？";
		next;
		mes "[駐屯地調査官]";
		mes "早く偵察兵を探してきて下さい。";
		mes "彼は、北東の";
		mes "モンスターが密集している地域に";
		mes "向かったはずです。";
		mes "よろしくお願いしますね。";
		viewpoint 1,234,301,5,0xFF0000;
		close;
	case 4:
		mes "[駐屯地調査官]";
		mes "偵察兵が見つかりましたか！";
		mes "今は負傷して休んでいるが";
		mes "命に別状はなく、";
		mes "パトロール日誌を";
		mes "急いで作っていると？";
		next;
		mes "[駐屯地調査官]";
		mes "そうですか、ありがとうございます。";
		mes "これで不安の種が一つ減りましたよ。";
		mes "それにしても、負傷しているのに";
		mes "すぐに日誌をまとめているなんて……。";
		mes "なんて出来た部下なんだ……!!";
		emotion 21;
		emotion 4,"";
		next;
		mes "[駐屯地調査官]";
		mes "偵察兵の問題は解決したので、";
		mes "次の問題にもぜひ";
		mes "協力してほしいのですが……。";
		next;
		mes "[駐屯地調査官]";
		mes "ここフレイムヴァレーでは";
		mes "正体不明のモンスター達が";
		mes "増えている事は知っていますよね？";
		next;
		menu "知っている",-;
		mes "[駐屯地調査官]";
		mes "やつらが外の世界に出てしまい、";
		mes "外のモンスターと接触すると、";
		mes "狂暴化したり、";
		mes "致命的なウィルスを広めたりと、";
		mes "強力な突然変異を起こし、";
		mes "深刻な事態に陥る可能性があります。";
		next;
		mes "[駐屯地調査官]";
		mes "そこで取り急ぎあなたには";
		mes "やつらの個体数を";
		mes "減らしてほしいのです。";
		next;
		mes "[駐屯地調査官]";
		mes "^0000FFフレイムサンドマン^000000と";
		mes "^0000FFフレイムフリルドラ^000000をそれぞれ";
		mes "20匹ずつ退治して下さい。";
		next;
		if(select("直接やったらどうですか？","頑張って倒します！") == 1) {
			mes "[駐屯地調査官]";
			mes "この前も話したと思いますが、";
			mes "私は調査担当なのです。";
			mes "戦闘にも不向きなもので……。";
			mes "指示しかできないのです。";
			emotion 19,"";
			close;
		}
		mes "[駐屯地調査官]";
		mes "急いでください。";
		mes "こうしている間にも";
		mes "モンスター達は増えています。";
		set FVOL_2QUE,5;
		chgquest 1267,1268;
		setquest 1269;
		close;
	case 5:
		if(!(checkquest(1268) & 0x4) || !(checkquest(1269) & 0x4)) {
			mes "[駐屯地調査官]";
			mes "急いでください。";
			mes "こうしている間にも";
			mes "モンスター達は増えています。";
			next;
			mes "[駐屯地調査官]";
			mes "^0000FFフレイムサンドマン^000000と";
			mes "^0000FFフレイムフリルドラ^000000をそれぞれ";
			mes "20匹ずつ退治して下さい。";
			close;
		}
		mes "[駐屯地調査官]";
		mes "^0000FFフレイムサンドマン^000000と";
		mes "^0000FFフレイムフリルドラ^000000をそれぞれ";
		mes "20匹ずつ倒したようですね。";
		next;
		mes "[駐屯地調査官]";
		mes "ご苦労様でした。";
		mes "あなたが頑張ってくれたおかげで";
		mes "ある程度ここのモンスターへの";
		mes "対応方法がわかってきました。";
		next;
		mes "[駐屯地調査官]";
		mes "今後は私の部下たちが";
		mes "直接ここのモンスター達を";
		mes "討伐します。";
		mes "あなたは北西の方に集まっている";
		mes "怪しい集団の対応をお願いします。";
		next;
		mes "[駐屯地調査官]";
		mes "あの集団はいったいどこから";
		mes "集まって来たんだろう……？";
		mes "どうしてあんな集団まで";
		mes "私たちを苦しめるんでしょう。";
		emotion 28;
		set FVOL_2QUE,6;
		delquest 1268;
		delquest 1269;
		setquest 1297;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		viewpoint 1,91,197,6,0xFF0000;
		close;
	case 13:
		mes "[駐屯地調査官]";
		mes "あの怪しい連中が";
		mes "嘘のようにおとなしくなりました。";
		mes "いったい何をしたんですか？";
		mes "まあおかげで悩みの種が";
		mes "一つ減りました。";
		mes "ありがとうございました。";
		close;
	default:
		mes "[駐屯地調査官]";
		mes "モンスター討伐は私達に任せて下さい。";
		mes "あなたは北西の方に集まっている";
		mes "怪しい集団の対応をお願いします。";
		next;
		mes "[駐屯地調査官]";
		mes "あの集団はいったいどこから";
		mes "集まって来たんだろう……？";
		mes "どうしてあんな集団まで";
		mes "私たちを苦しめるんでしょう。";
		emotion 28;
		viewpoint 1,91,197,6,0xFF0000;
		close;
	}
OnInit:
	waitingroom "滅亡祝福教団",0;
	end;
}

moro_vol.gat,234,301,3	script	偵察兵#bl	413,{
	viewpoint 2,1,1,5,0xFFFFFF;
	switch(FVOL_2QUE) {
	case 2:
		mes "[偵察兵]";
		mes "良く来てくれました！";
		mes "ちょうど助けがほしいところでした。";
		next;
		mes "[偵察兵]";
		mes "私はここで危険を冒してまで";
		mes "偵察を行っていたのですが、";
		mes "モンスターの集団から攻撃を";
		mes "受けてしまい、しょうがなく";
		mes "ここで休んでいました。";
		next;
		if(select("一緒に戻りましょう","休みの続きをどうぞ！") == 2) {
			mes "[偵察兵]";
			mes "助けを求められるのが嫌で";
			mes "逃げましたね！";
			close;
		}
		mes "[偵察兵]";
		mes "戻りたいのはやまやまなのですが……。";
		mes "怪我は大したことないのですが、";
		mes "^0000FFフレイムサンドマン^000000が";
		mes "私の^FF0000パトロール日誌^000000を";
		mes "持って行ってしまいました。";
		next;
		mes "[偵察兵]";
		mes "^FF0000パトロール日誌^000000がないと";
		mes "駐屯地に戻っても怒られるし……。";
		next;
		mes "[偵察兵]";
		mes "どうですか？";
		mes "私に協力してあげたい気持ちが";
		mes "湧いてきたんじゃないですか？";
		next;
		if(select("協力したいです","別に……") == 2) {
			mes "[偵察兵]";
			mes "そうですか。";
			mes "ならそうなるまで";
			mes "私はもうちょっと休みます。";
			close;
		}
		mes "[偵察兵]";
		mes "そうでしょうそうでしょう。";
		mes "では^0000FFフレイムサンドマン^000000から";
		mes "^FF0000パトロール日誌^000000を取り戻してください。";
		next;
		mes "[偵察兵]";
		mes "日誌は噛みつかれてバラバラに";
		mes "なってしまったので、確認ができるように";
		mes "^FF0000パトロール日誌^00000020枚程度";
		mes "集めてきて下さい。";
		set FVOL_2QUE,3;
		chgquest 1265,1266;
		close;
	case 3:
		if(countitem(6692) < 20) {
			mes "[偵察兵]";
			mes "では^0000FFフレイムサンドマン^000000を倒して";
			mes "^FF0000パトロール日誌^00000020枚を";
			mes "取り戻してください。";
			close;
		}
		mes "[偵察兵]";
		mes "もう^FF0000パトロール日誌^00000020枚を";
		mes "全部集めて来たんですか？";
		mes "こんなに早く集まるなら";
		mes "100枚頼めばよかったかな。";
		next;
		mes "[偵察兵]";
		mes "何がともあれ、助かりました。";
		mes "ありがとうございます。しかし、";
		mes "戻ってから怒られるかもと考えると、";
		mes "ちょっと頭が痛くなってきますね。";
		next;
		mes "[偵察兵]";
		mes "パトロール日誌を整理してから";
		mes "行くので、調査官様には";
		mes "事情を伝えて下さい。";
		mes "あっ、日誌を取られた事は内緒ですよ！";
		delitem 6692,20;
		set FVOL_2QUE,4;
		chgquest 1266,1267;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		viewpoint 1,131,103,4,0xFF0000;
		close;
	case 4:
		mes "[偵察兵]";
		mes "パトロール日誌を整理してから";
		mes "行くので、調査官様には";
		mes "事情を伝えて下さい。";
		mes "あっ、日誌を取られた事は内緒ですよ！";
		viewpoint 1,131,103,4,0xFF0000;
		close;
	default:
		mes "[偵察兵]";
		mes "モンスターを調査中です。";
		mes "こんな危険な場所を私一人で";
		mes "調査しろだなんて、あんまりだ！";
		close;
	}
}

moro_vol.gat,91,197,3	script	滅亡祝福教団教主#bl	10021,{
	viewpoint 2,1,1,6,0xFFFFFF;
	switch(FVOL_2QUE) {
	case 6:
		mes "[滅亡祝福教団教主]";
		mes "いよいよ審判の日が到来した！";
		mes "滅亡！　祝福！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅！　亡！　祝！　福！";
		mes "滅！　亡！　祝！　福！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちをあの岩の中に案内しろ！";
		mes "私たちは神から選ばれた！";
		mes "滅亡が本格的に始まる日！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちだけが唯一！";
		mes "祝福を受ける！";
		mes "滅亡！　祝福！";
		next;
		switch(select("なんの神を信仰しているんですか？","あなた達は誰ですか？","早く安全な場所に移動して下さい！")) {
		case 1:
			mes "[滅亡祝福教団教主]";
			mes "私たちは滅亡の神に仕えている！";
			mes "星の滅亡どころかすべての宇宙を";
			mes "滅亡させる偉大な神である！";
			close;
		case 2:
			mes "[滅亡祝福教団教主]";
			mes "私たちは滅亡祝福教団だ！";
			mes "略してMSKと呼ぶ者もいる。";
			mes "滅亡の神に仕えていて、";
			mes "全世界の滅亡を祈っている。";
			next;
			mes "[滅亡祝福教団教主]";
			mes "すべてが滅亡し始めることで";
			mes "私たちは祝福を受けることができる！";
			next;
			mes "[滅亡祝福教団教主]";
			mes "あらゆる場所で発見された";
			mes "次元の狭間がすべてを語っている！";
			mes "二本足で立って話す猫や";
			mes "青い巨人……。";
			next;
			mes "[滅亡祝福教団教主]";
			mes "このすべてが滅亡を ";
			mes "予言している！";
			mes "おお、滅亡の時が来た！";
			mes "滅亡！　祝福！";
			close;
		case 3:
			break;
		}
		mes "[滅亡祝福教団教主]";
		mes "いきなり帰れと？";
		mes "ようやく滅亡の時が訪れるというのに！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちは帰らないぞ！";
		mes "早くあの岩の中に入れろ！";
		mes "私たちは滅亡の神に選ばれているから";
		mes "君たちと違って安全なんだよ！";
		next;
		menu "証明できますか？",-;
		mes "[滅亡祝福教団教主]";
		mes "私たちを疑うとは！";
		mes "いくらでも証明してみせてやる！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "この滅亡の大地に散らばっている";
		mes "^FF0000ブレスストーン^000000を40個集めて";
		mes "私たちに投げてみろ！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちの体に当たる瞬間、";
		mes "ポン！　と花びらに変わるだろう！";
		mes "滅亡！　祝福！";
		next;
		menu "滅亡の大地？",-;
		mes "[駐屯地 番卒]";
		mes "ここフレイムヴァレーをあの者たちは";
		mes "勝手に滅亡の大地と";
		mes "呼んでいます。";
		next;
		mes "[駐屯地 番卒]";
		mes "^FF0000ブレスストーン^000000というのは";
		mes "^0000FFフレイムゴーレム^000000の体に付着している";
		mes "普通の石です。";
		next;
		mes "[駐屯地 番卒]";
		mes "彼らを正気に戻すには、自分たちが";
		mes "間違っていることをわかってもらうしか";
		mes "ないようです。彼らの言うとおり、";
		mes "^0000FFフレイムゴーレム^000000を倒して";
		mes "^FF0000ブレスストーン^00000040個を集めてきますか？";
		next;
		if(select("係わらないことにする！","ブレスストーンを集めよう。") == 1) {
			mes "[滅亡祝福教団教主]";
			mes "このとてつもない光景を見て";
			mes "滅亡の神の存在を信じてしまうのが";
			mes "怖いのですね！　退いて下さい！";
			mes "滅亡！　祝福！";
			close;
		}
		mes "[滅亡祝福教団教主]";
		mes "そうか、では^FF0000ブレスストーン^000000を";
		mes "私たちに投げてみろ！";
		mes "花びらになり落ちるはずだ！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "奇跡を目の当たりにした君は";
		mes "泣いて許しを請いながら、";
		mes "滅亡祝福教団の信者になりたいと";
		mes "言うだろう！";
		set FVOL_2QUE,7;
		chgquest 1297,1270;
		close;
	case 7:
		if(countitem(6693) < 40) {
			mes "[滅亡祝福教団教主]";
			mes "ここ、滅亡の大地に散らばっている";
			mes "^FF0000ブレスストーン^000000を40個集めて";
			mes "私たちに投げてみろ！";
			next;
			mes "[滅亡祝福教団教主]";
			mes "私たちの体に当たる瞬間、";
			mes "ポン！　と花びらに変わるだろう！";
			mes "滅亡！　祝福！";
			next;
			mes "‐^0000FFフレイムゴーレム^000000を倒して";
			mes "　^FF0000ブレスストーン^00000040個を集めてこよう‐";
			close;
		}
		mes "[滅亡祝福教団教主]";
		mes "^FF0000ブレスストーン^00000040個を集めてきたのか！";
		mes "いいぞ、私たちは既に";
		mes "準備ができている。";
		mes "早くその石を投げてみろ！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "君たちには理解できない奇跡を";
		mes "目の当たりにすることになる！";
		mes "さあ、投げてみろ！";
		mes "思いきり投げてみろ！";
		mes "滅亡！　祝福！";
		next;
		mes "ヒューン！　ヒューン！　ヒューン！";
		mes "ヒューン！　ヒューン！　ヒューン！";
		next;
		mes "ヒューン！　ヒューン！　ヒューン！";
		mes "ヒューン！　ヒューン！　ヒューン！";
		mes "ヒューン！　ヒューン！　ヒューン！";
		mes "ヒューン！　ヒューン！　ヒューン！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "うわっ！";
		emotion 19,"滅亡祝福教団教主#bl";
		emotion 19,"滅亡祝福教団副教主#bl";
		emotion 28,"滅亡祝福教団信者#bl1";
		emotion 19,"滅亡祝福教団信者#bl2";
		emotion 19,"滅亡祝福教団信者#bl3";
		emotion 28,"滅亡祝福教団信者#bl4";
		next;
		mes "[滅亡祝福教団信者]";
		mes "うわっ！";
		mes "くわああ！";
		emotion 19,"滅亡祝福教団教主#bl";
		emotion 19,"滅亡祝福教団副教主#bl";
		emotion 28,"滅亡祝福教団信者#bl1";
		emotion 19,"滅亡祝福教団信者#bl3";
		emotion 28,"滅亡祝福教団信者#bl4";
		emotion 19,"滅亡祝福教団信者#bl6";
		emotion 28,"滅亡祝福教団信者#bl7";
		emotion 19,"滅亡祝福教団信者#bl9";
		emotion 28,"滅亡祝福教団信者#bl0";
		emotion 19,"滅亡祝福教団信者#bl12";
		next;
		mes "[滅亡祝福教団信者]";
		mes "うえええ！";
		mes "ヒイイ、ヒイホー！";
		emotion 19,"滅亡祝福教団教主#bl";
		emotion 19,"滅亡祝福教団副教主#bl";
		emotion 28,"滅亡祝福教団信者#bl1";
		emotion 4,"滅亡祝福教団信者#bl2";
		emotion 19,"滅亡祝福教団信者#bl3";
		emotion 28,"滅亡祝福教団信者#bl4";
		emotion 4,"滅亡祝福教団信者#bl5";
		emotion 19,"滅亡祝福教団信者#bl6";
		emotion 28,"滅亡祝福教団信者#bl7";
		emotion 19,"滅亡祝福教団信者#bl8";
		emotion 19,"滅亡祝福教団信者#bl9";
		emotion 28,"滅亡祝福教団信者#bl0";
		emotion 19,"滅亡祝福教団信者#bl11";
		emotion 19,"滅亡祝福教団信者#bl12";
		next;
		mes "[滅亡祝福教団教主]";
		mes "痛い！";
		mes "とても痛い！";
		mes "やめろ！";
		mes "私の顔に照準を合わせるんじゃない！";
		mes "今すぐにやめろ！";
		next;
		switch(select("全部投げる","やめる")) {
		case 1:
			mes "[滅亡祝福教団信者]";
			mes "わあ！";
			mes "私の額！";
			mes "あお、ふお！";
			emotion 19,"滅亡祝福教団教主#bl";
			emotion 19,"滅亡祝福教団副教主#bl";
			emotion 28,"滅亡祝福教団信者#bl1";
			emotion 19,"滅亡祝福教団信者#bl2";
			emotion 19,"滅亡祝福教団信者#bl3";
			emotion 28,"滅亡祝福教団信者#bl4";
			next;
			mes "[滅亡祝福教団信者]";
			mes "ほええ！";
			mes "私の鼻！";
			mes "きゃあ！　きゃあ！";
			emotion 19,"滅亡祝福教団教主#bl";
			emotion 19,"滅亡祝福教団副教主#bl";
			emotion 28,"滅亡祝福教団信者#bl1";
			emotion 4,"滅亡祝福教団信者#bl2";
			emotion 19,"滅亡祝福教団信者#bl3";
			emotion 28,"滅亡祝福教団信者#bl4";
			emotion 4,"滅亡祝福教団信者#bl5";
			emotion 19,"滅亡祝福教団信者#bl6";
			emotion 28,"滅亡祝福教団信者#bl7";
			emotion 19,"滅亡祝福教団信者#bl8";
			emotion 19,"滅亡祝福教団信者#bl9";
			emotion 28,"滅亡祝福教団信者#bl0";
			emotion 19,"滅亡祝福教団信者#bl11";
			emotion 19,"滅亡祝福教団信者#bl12";
			next;
			mes "[滅亡祝福教団教主]";
			mes "痛い！";
			mes "メチャクチャ痛い！";
			mes "まだ準備が出来ていないのに";
			mes "投げるんじゃない！";
			mes "待って！　やり直し！";
			close;
		case 2:
			mes "‐ポン！　と花びらに変わるどころか";
			mes "　うわっ！　という悲鳴だけが";
			mes "　辺りに鳴り響いた。";
			mes "　石投げをやめよう‐";
			delitem 6693,40;
			set FVOL_2QUE,8;
			chgquest 1270,1271;
			close;
		}
	case 8:
		mes "[滅亡祝福教団教主]";
		mes "兄弟たちよ、落ち着いてくれ！";
		mes "異端者が違う石を持ってきて";
		mes "我らを騙したんだ！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "やっぱり！";
		mes "そんなことだろうと思った！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "う～";
		mes "う～";
		emotion 32,"滅亡祝福教団教主#bl";
		emotion 32,"滅亡祝福教団副教主#bl";
		emotion 6,"滅亡祝福教団信者#bl1";
		emotion 6,"滅亡祝福教団信者#bl2";
		emotion 6,"滅亡祝福教団信者#bl3";
		emotion 6,"滅亡祝福教団信者#bl4";
		emotion 6,"滅亡祝福教団信者#bl5";
		emotion 6,"滅亡祝福教団信者#bl6";
		emotion 6,"滅亡祝福教団信者#bl7";
		emotion 6,"滅亡祝福教団信者#bl8";
		emotion 6,"滅亡祝福教団信者#bl9";
		emotion 6,"滅亡祝福教団信者#bl0";
		emotion 6,"滅亡祝福教団信者#bl11";
		emotion 6,"滅亡祝福教団信者#bl12";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "異端者よ、卑怯者よ！";
		mes "もう一度そなたに命じる！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "滅亡の大地を彷徨っている";
		mes "怪獣の血を持ってきなさい！";
		mes "私はそれを飲むことで";
		mes "空中浮遊が可能になる。";
		mes "そして君らを導いてやる！";
		next;
		mes "[駐屯地 番卒]";
		mes "うむ……ここフレイムヴァレーにいる";
		mes "^0000FFフレイムフリルドラ^000000と";
		mes "^0000FFフレイムサンドマン^000000から";
		mes "^FF0000怪獣の血^000000を集めてこい";
		mes "ということですね。";
		mes "30個ほどあれば十分でしょう。";
		next;
		if(select("係わらないようにする！","怪獣の血を集めよう") == 1) {
			mes "[滅亡祝福教団教主]";
			mes "そう来ると思ったよ！";
			mes "やっぱり滅亡の神の存在を";
			mes "信じてしまうことが恐ろしいんだな？";
			next;
			mes "[滅亡祝福教団教主]";
			mes "邪魔しないであっちに行ってくれ！";
			mes "滅亡！　祝福！";
			close;
		}
		mes "[滅亡祝福教団教主]";
		mes "怪獣の血を早く持ってきなさい！";
		mes "近づくだけで全身が震える恐ろしい";
		mes "^0000FFフレイムフリルドラ^000000と";
		mes "^0000FFフレイムサンドマン^000000を倒して";
		mes "^FF0000怪獣の血^000000を30個集めてくるんだ！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "とても危険な事なんだぞ！";
		mes "このまま逃げていれば";
		mes "適当にごまかせたかもしれないのに……";
		mes "こうなったらもう倒してくるしか";
		mes "なくなってしまったな！";
		mes "わはははは……。";
		set FVOL_2QUE,9;
		chgquest 1271,1272;
		close;
	case 9:
		if(countitem(6694) < 30) {
			mes "[滅亡祝福教団教主]";
			mes "怪獣の血を早く持ってきなさい！";
			mes "近づくだけで全身が震える恐ろしい";
			mes "^0000FFフレイムフリルドラ^000000と";
			mes "^0000FFフレイムサンドマン^000000を倒して";
			mes "^FF0000怪獣の血^000000を30個集めてくるんだ！";
			next;
			mes "[滅亡祝福教団教主]";
			mes "とても危険な事なんだぞ！";
			mes "このまま逃げていれば";
			mes "適当にごまかせたかもしれないのに……";
			mes "こうなったらもう倒してくるしか";
			mes "なくなってしまったな！";
			mes "わはははは……。";
			close;
		}
		mes "[滅亡祝福教団教主]";
		mes "とても暇な異端者よ！";
		mes "やっと^FF0000怪獣の血^000000を集めて来たのか！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "しっかりと見ておけ！";
		mes "私がお腹いっぱいに全部飲み干して";
		mes "空中浮遊で回答してやるぞ！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "ごくごく～";
		next;
		mes "[滅亡祝福教団教主]";
		mes "ごくごく～";
		mes "ごくごく～";
		next;
		mes "[滅亡祝福教団教主]";
		mes "ごくごく～";
		mes "ごくごく～";
		mes "ごくごく～";
		next;
		mes "[滅亡祝福教団教主]";
		mes "ごっくん……。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "ぶくぶく……。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "……";
		mes "うううっ……！";
		emotion 4,"滅亡祝福教団教主#bl";
		next;
		mes "‐滅亡祝福教団教主の顔色が";
		mes "　白くなって行き、彼から";
		mes "　酷い悪臭が漂ってきた……";
		mes "　教主が沈黙する‐";
		emotion 28,"滅亡祝福教団教主#bl";
		delitem 6694,30;
		set FVOL_2QUE,10;
		chgquest 1272,1273;
		close;
	case 10:
	case 11:
		mes "‐教主の体から悪臭がする。";
		mes "　教主は何も言わなくなった‐";
		next;
		mes "‐副教主が私に";
		mes "　指をさしている。";
		mes "　話かけてみよう‐";
		close;
	case 12:
		mes "[滅亡祝福教団教主]";
		mes "ふう……結局また滅亡は来なかった。";
		mes "早く家に戻って";
		mes "綺麗な服に着替えたい……。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "次の天災地変の時に、もう一度信者を";
		mes "集めて滅亡の神を必ず";
		mes "呼び出してやる！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "それはそうと、君が怪奇現象を";
		mes "起こしてくれたおかげで";
		mes "私の面目が立った。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "信者達が私のことを偽物だと言って";
		mes "疑って会費も払っていなかったんだ。";
		mes "君のおかげで助かった、お礼を言おう。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "次の集会が開かれる時には";
		mes "君も必ず参加して、";
		mes "今日のような怪奇現象を";
		mes "もう一度起こしてくれ。頼むぞ！";
		set FVOL_2QUE,13;
		chgquest 1275,201710;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		close;
	case 13:
		mes "[滅亡祝福教団教主]";
		mes "君が怪奇現象を";
		mes "起こしてくれたおかげで";
		mes "私の面目が立った。";
		next;
		mes "[滅亡祝福教団教主]";
		mes "次の集会が開かれる時には";
		mes "君も必ず参加して、";
		mes "今日のような気象異変を";
		mes "もう一度起こしてくれ。頼むぞ！";
		close;
	default:
		mes "[滅亡祝福教団教主]";
		mes "いよいよ審判の日が到来した！";
		mes "滅亡！　祝福！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちをあの岩の中に案内しろ！";
		mes "私たちは神から選ばれた！";
		mes "滅亡が本格的に始まる日！";
		next;
		mes "[滅亡祝福教団教主]";
		mes "私たちだけが唯一！";
		mes "祝福を受ける！";
		mes "滅亡！　祝福！";
		close;
	}
}

moro_vol.gat,95,195,3	script	滅亡祝福教団副教主#bl	10022,{
	switch(FVOL_2QUE) {
	case 10:
		mes "[滅亡祝福教団副教主]";
		mes "滅亡祝福教団信者達よ！";
		mes "動揺するな、落ち着け！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "どのみちもうすぐ審判が始まる。 ";
		mes "私たちは祝福を受けることが";
		mes "決まっている。";
		mes "今さら何が必要だと言うのだ！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "ともに祈り、";
		mes "この場所に祝福の扉を呼び出そう！";
		mes "滅！　亡！　滅亡滅亡！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅！　亡！　滅亡滅亡！";
		mes "滅！　亡！　滅亡滅亡！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "おお、光が見える！　私の両手に";
		mes "^FF0000フレイムゴーレムの岩の歯^000000と";
		mes "^FF0000フレイムフリルドラの襟巻^000000が";
		mes "それぞれ30個ずつ乗せられたなら！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "目の前に大きな祝福の扉が";
		mes "開くはずだ！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "おおお～！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "信者達よ！";
		mes "急いでここの危険なモンスターを";
		mes "素手で殴り倒してくるのです！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "^FF0000フレイムゴーレムの岩の歯^000000と";
		mes "^FF0000フレイムフリルドラの襟巻^000000を";
		mes "それぞれ30個ずつ私の前に";
		mes "持ってきなさい！";
		next;
		if(select("関わりたくない","私が集めてきます。") == 1) {
			mes "[滅亡祝福教団副教主]";
			mes "見なさい、信者達よ！";
			mes "あの冷血な異端者が";
			mes "関わりたくないといっている、";
			mes "これほど嬉しいことはない。";
			next;
			mes "[滅亡祝福教団副教主]";
			mes "急いでここに生息している恐ろしい";
			mes "モンスターたちを素手で倒して";
			mes "材料を集めてくるのです！";
			next;
			mes "[滅亡祝福教団副教主]";
			mes "怖い？　戦えない？";
			mes "扉を開くために犠牲はつきものです。";
			mes "恐れずに行きなさい！";
			emotion 19,"";
			close;
		}
		mes "[滅亡祝福教団副教主]";
		mes "聞け、信者達よ！";
		mes "この異端者にもう一度だけ";
		mes "祝福のチャンスを与えることにしよう！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "急いで";
		mes "^FF0000フレイムゴーレムの岩の歯^000000と";
		mes "^FF0000フレイムフリルドラの襟巻^000000を";
		mes "それぞれ30個ずつ私の前に";
		mes "持ってきなさい！";
		set FVOL_2QUE,11;
		chgquest 1273,1274;
		close;
	case 11:
		if(countitem(6695) < 30 || countitem(6696) < 30) {
			mes "[滅亡祝福教団副教主]";
			mes "急いで";
			mes "^FF0000フレイムゴーレムの岩の歯^000000と";
			mes "^FF0000フレイムフリルドラの襟巻^000000を";
			mes "それぞれ30個ずつ私の前まで持ってきなさい！";
			close;
		}
		mes "[滅亡祝福教団副教主]";
		mes "おお、滅亡祝福教団信者達よ！";
		mes "喜べ、材料がすべて集まったぞ！";
		mes "滅亡！　滅亡！　滅亡滅亡！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		next;
		mes "[滅亡祝福教団副教主]";
		mes "みんなで祈ろう！";
		mes "ここに祝福の扉を";
		mes "呼びだそうじゃないか！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "……";
		next;
		mes "[滅亡祝福教団信者]";
		mes "!!";
		next;
		mes "[滅亡祝福教団信者]";
		mes "きゃあああ！";
		mes "ひゃっほ、ひーほ！";
		misceffect 183,"滅亡祝福教団教主#bl";
		misceffect 183,"滅亡祝福教団副教主#bl";
		misceffect 183,"滅亡祝福教団信者#bl1";
		misceffect 183,"滅亡祝福教団信者#bl2";
		misceffect 183,"滅亡祝福教団信者#bl3";
		misceffect 183,"滅亡祝福教団信者#bl4";
		misceffect 183,"滅亡祝福教団信者#bl5";
		misceffect 183,"滅亡祝福教団信者#bl6";
		misceffect 183,"滅亡祝福教団信者#bl7";
		misceffect 183,"滅亡祝福教団信者#bl8";
		misceffect 183,"滅亡祝福教団信者#bl9";
		misceffect 183,"滅亡祝福教団信者#bl0";
		misceffect 183,"滅亡祝福教団信者#bl11";
		misceffect 183,"滅亡祝福教団信者#bl12";
		next;
		mes "[滅亡祝福教団信者]";
		mes "きゃあ！";
		mes "本当の滅亡だ！";
		mes "みんな死んでしまう！　きゃああ！";
		misceffect 183,"滅亡祝福教団教主#bl";
		misceffect 183,"滅亡祝福教団副教主#bl";
		misceffect 183,"滅亡祝福教団信者#bl1";
		misceffect 183,"滅亡祝福教団信者#bl2";
		misceffect 183,"滅亡祝福教団信者#bl3";
		misceffect 183,"滅亡祝福教団信者#bl4";
		misceffect 183,"滅亡祝福教団信者#bl5";
		misceffect 183,"滅亡祝福教団信者#bl6";
		misceffect 183,"滅亡祝福教団信者#bl7";
		misceffect 183,"滅亡祝福教団信者#bl8";
		misceffect 183,"滅亡祝福教団信者#bl9";
		misceffect 183,"滅亡祝福教団信者#bl0";
		misceffect 183,"滅亡祝福教団信者#bl11";
		misceffect 183,"滅亡祝福教団信者#bl12";
		next;
		mes "‐滅亡の神がいるかはわからないが、";
		mes "　彼らだけが選ばれて祝福を";
		mes "　受けたのではなさそうだ。";
		mes "　滅亡祝福教団教主と";
		mes "　もう一度話をしてみよう‐";
		delitem 6695,30;
		delitem 6696,30;
		set FVOL_2QUE,12;
		chgquest 1274,1275;
		close;
	case 12:
	case 13:
		mes "[滅亡祝福教団副教主]";
		mes "……ああ怖い……";
		mes "早く逃げたいけど";
		mes "みんなの目があるから困るな！";
		mes "怖いからまずは";
		mes "泣くようにしよう…";
		close;
	default:
		mes "[滅亡祝福教団副教主]";
		mes "滅亡祝福教団信者よ!";
		mes "もっと気持ちを込めて祈りましょう！";
		mes "絶！　望！　絶望絶望！";
		next;
		mes "[滅亡祝福教団信者]";
		mes "滅！　亡！　滅亡滅亡！";
		mes "滅！　亡！　滅亡滅亡！";
		close;
	}
}

moro_vol.gat,85,196,7	script	滅亡祝福教団信者#bl1	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "おお～怖い！";
	mes "家に帰りたい！";
	close;
}

moro_vol.gat,87,193,7	script	滅亡祝福教団信者#bl2	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "こんな恐ろしいことが起こるなんて！";
	mes "機を見てさっさと逃げなきゃ！";
	close;
}

moro_vol.gat,90,191,7	script	滅亡祝福教団信者#bl3	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "やっと祝福を受けられると思い";
	mes "全財産を教主に渡したのに！！";
	next;
	mes "[滅亡祝福教団信者]";
	mes "……";
	mes "私の信心が不足していたのかな……？";
	close;
}

moro_vol.gat,93,189,7	script	滅亡祝福教団信者#bl4	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "恐ろしい！";
	mes "なんてことだ！";
	close;
}

moro_vol.gat,83,193,7	script	滅亡祝福教団信者#bl5	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "うわああああ！";
	mes "うわっ、怖い！";
	close;
}

moro_vol.gat,86,190,7	script	滅亡祝福教団信者#bl6	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "おお～怖い！";
	mes "マジで家に帰りたい！";
	close;
}

moro_vol.gat,89,188,7	script	滅亡祝福教団信者#bl7	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "ううう、怖い！";
	mes "来るんじゃなかった！";
	close;
}

moro_vol.gat,93,185,7	script	滅亡祝福教団信者#bl8	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "おお～怖い！";
	mes "マジで家に帰りたい！";
	mes "教主のバカ！";
	close;
}

moro_vol.gat,81,197,7	script	滅亡祝福教団信者#bl9	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "もうこれ以上、";
	mes "教主を信じることができない!!";
	mes "私が教主になってやる！";
	close;
}

moro_vol.gat,84,201,5	script	滅亡祝福教団信者#bl0	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "滅亡！　祝福！";
		mes "滅亡！　祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "おお～怖い！";
	mes "マジで家に帰りたい！";
	close;
}

moro_vol.gat,97,187,5	script	滅亡祝福教団信者#bl11	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "亡！　亡！　滅亡滅亡！";
		mes "福！　福！　私だけ祝福！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "マジで怖いわ！";
	mes "信心が足りないからか？";
	mes "もっと献納をしないと！";
	close;
}

moro_vol.gat,82,189,7	script	滅亡祝福教団信者#bl12	10023,{
	if(FVOL_2QUE < 12) {
		mes "[滅亡祝福教団信者]";
		mes "おお、滅亡の神よ！";
		mes "早く、この私に滅亡を！";
		mes "この私だけに祝福を！";
		close;
	}
	mes "[滅亡祝福教団信者]";
	mes "マジで怖いわ！";
	mes "信心が足りないから？";
	mes "もっと献納をしないと！";
	close;
}

//============================================================
// デイリークエストNPC
//------------------------------------------------------------
moro_vol.gat,95,108,7	script	ヒシエ#143hisie01	623,{
	if(ECL_3QUE < 33) {	// エクラージュの王
		if(checkquest(201730)) {	// 魔神殿攻略済み？
			cutin "hisie01",2;
			mes "[ヒシエ]";
			mes "果してここで";
			mes "魔王の実体を探し出すことが";
			mes "できるのか？";
			mes "ここには見たことも無い";
			mes "生物が多すぎる……。";
			next;
			mes "[ヒシエ]";
			mes "まったく……";
			mes "見ていていい気分に";
			mes "なれるものではないな……。";
			close2;
			cutin "hisie01",255;
			end;
		}
		cutin "hisie01",2;
		mes "[ヒシエ]";
		mes "人間連合からの者か？";
		mes "特に連合に協力を";
		mes "要請するようなことは";
		mes "ないと思うが……。";
		next;
		mes "[ヒシエ]";
		mes "もし何かあれば";
		mes "そこにいる総司令官、";
		mes "アジフに知らせよう。";
		close2;
		cutin "hisie01",255;
		end;
	}
	switch(FVOL_3QUE) {
	case 0:
		cutin "hisie01",2;
		mes "[ヒシエ]";
		mes "全ての元凶がここに";
		mes "隠れているというのだな？";
		mes "……楽しみだ。";
		next;
		mes "[ヒシエ]";
		mes "ああ……。";
		mes "なぜ私がここにいるのか？";
		mes "って、顔だな。";
		mes "カルの代わりに来ているんだ。";
		next;
		mes "[ヒシエ]";
		mes "カルはオーブの魔力の代わりを";
		mes "務めているから、今は";
		mes "エクラージュを離れられない。";
		next;
		mes "[ヒシエ]";
		mes "そして我々にもっとも";
		mes "重要なのはイグドラシルと";
		mes "守護者の安寧だ。";
		mes "それに生まれたばかりの";
		mes "マヨルを失うわけにはいかない。";
		next;
		mes "[ヒシエ]";
		mes "他にも色々な事情があって、";
		mes "元老達を説得した上で";
		mes "私が戦場の指揮を執っているが……";
		mes "見ての通り、";
		mes "見掛け倒しの地位だ。";
		next;
		menu "エイヴァントはどうなった？",-;
		cutin "hisie02",2;
		mes "[ヒシエ]";
		mes "エイヴァントか……。";
		mes "今は、あいつの知識を";
		mes "利用させてもらっている。";
		mes "命を簡単に刈り取るのも";
		mes "いいことではないからね。";
		next;
		mes "[ヒシエ]";
		mes "それにある意味、あいつも";
		mes "シナイムに利用されただけとも";
		mes "言えなくはない。";
		mes "あいつは依頼された";
		mes "オーブの魔力について愚直に";
		mes "研究していただけだしな。";
		next;
		mes "[ヒシエ]";
		mes "それを踏まえて、元老会でも";
		mes "エイヴァントの能力を高く評価し、";
		mes "彼を積極的に活用する方向で";
		mes "決定を下している。";
		mes "それになにより……";
		next;
		mes "‐ヒシエは声のトーンを一段階落とし";
		mes "　周りに目を配りながらつぶやいた‐";
		next;
		mes "[ヒシエ]";
		mes "……オーブの魔力が";
		mes "奪われたことは誰にも";
		mes "知られていない……。";
		next;
		mes "[ヒシエ]";
		mes "彼らが知る";
		mes "エイヴァントの罪は";
		mes "私とカルの存在だけ";
		mes "だからね。";
		next;
		mes "[ヒシエ]";
		mes "しかしまさか、あいつの知識を";
		mes "このような形で利用することに";
		mes "なるなんてね……。";
		mes "まったく、皮肉なものだよ。";
		next;
		mes "[ヒシエ]";
		mes "もし、君があいつ……";
		mes "エイヴァントに用があるなら";
		mes "あいつは今も";
		mes "研究を続けているはずだ。";
		mes "聞きたいことがあれば";
		mes "直接聞くといい。";
		close2;
		cutin "hisie01",255;
		end;
	case 1:
		if(checkquest(7593) == 0) {
			cutin "hisie02",2;
			mes "[ヒシエ]";
			mes "オーブの魔力に関しては";
			mes "エイヴァントが良く知っている。";
			mes "……私とカルもいろいろ";
			mes "言いたいことや思うこともあるが";
			mes "エイヴァントの仕事に……";
			mes "……君も協力してほしい。";
			next;
			mes "[ヒシエ]";
			mes "オーブの魔力回収も問題だが、";
			mes "魔王の存在も無視できない。";
			mes "それにまだみんな";
			mes "オーブの中核魔力が";
			mes "奪取された事実を知らない。";
			next;
			mes "[ヒシエ]";
			mes "公けにすることが";
			mes "できない事項だからな……。";
			mes "君にしか頼むことができないんだ。";
			mes "私とカルの面子を立てるためにも";
			mes "助けてほしい。";
			close2;
			cutin "hisie01",255;
			end;
		}
		if(checkquest(7600)) {
			if(checkquest(7600)&0x2 == 0) {
				cutin "hisie01",2;
				mes "[ヒシエ]";
				mes "まだ回収されてない";
				mes "オーブの魔力が多い。";
				mes "まあ、最初の頃よりは";
				mes "マシになってきたが……";
				mes "できれば明日も手伝ってほしい。";
				close2;
				cutin "hisie01",255;
				end;
			}
			cutin "hisie01",2;
			delquest 7600;
			mes "[ヒシエ]";
			mes "もし魔神殿にまた挑戦するなら";
			mes "頼みたいことがある。";
			mes "……そうだ。";
			mes "前にもやったことだ。";
			mes "魔力を戻す仕事だよ。";
			next;
			mes "[ヒシエ]";
			mes "手伝う気があるなら";
			mes "また話しかけてほしい。";
			close2;
			cutin "hisie01",255;
			end;
		}
		if(checkquest(7595)) {
			if(checkquest(7595)&0x4 == 0) {
				cutin "hisie01",2;
				mes "[ヒシエ]";
				mes "魔神殿でうごめいている";
				mes "オーブの魔力を見つけたら、";
				mes "叩いて砕くだけの";
				mes "簡単な仕事だ。";
				mes "散らばった魔力は";
				mes "自然と世界樹に戻っていく。";
				next;
				mes "[ヒシエ]";
				mes "結晶化して移動できない魔力は";
				mes "吸収すればいい。";
				mes "そっと触れるだけでも";
				mes "吸収できるはずだ。";
				next;
				mes "[ヒシエ]";
				mes "吸収した魔力は";
				mes "君の助けになるかもしれない。";
				mes "魔族を相手にするときに";
				mes "有効に使ってほしい。";
				close2;
				cutin "hisie01",255;
				end;
			}
			cutin "hisie04",2;
			mes "[ヒシエ]";
			mes "すごいぞ！　よくやってくれた！";
			mes "君が魔力の結晶を壊してくれたおかげで";
			mes "魔力が徐々に戻ってくるのが";
			mes "感じられる。";
			mes "カルもきっと、喜ぶだろう！";
			next;
			cutin "hisie01",2;
			mes "[ヒシエ]";
			mes "大したものではないが";
			mes "受け取ってほしい。";
			mes "君の助けになるかもしれない";
			mes "あと……オーブの魔力は";
			mes "想像以上に大きいようだ。";
			next;
			mes "[ヒシエ]";
			mes "だからもしまた君が";
			mes "魔神殿に行くことになれば";
			mes "その時も頼みたい。";
			mes "まずはゆっくり休んでくれ。";
			setquest 7600;
			delquest 7595;
			getitem 607,1;
			close2;
			cutin "hisie01",255;
			end;
		}
		cutin "hisie01",2;
		mes "[ヒシエ]";
		mes "魔神殿か……。";
		mes "ついでで構わないのだが、";
		mes "マナと言うオーブの魔力を";
		mes "探してみて欲しい。";
		next;
		mes "[ヒシエ]";
		mes "そして、それを見つけたら";
		mes "叩いて砕いてほしい。";
		mes "それにより、魔力は拡散され";
		mes "散らばった魔力は";
		mes "自然と世界樹に戻っていく。";
		mes "頼まれてくれるか？";
		next;
		if(select("よろこんで","力になれない") == 2) {
			cutin "hisie02",2;
			mes "[ヒシエ]";
			mes "そうか、無理することはない。";
			mes "気にするな。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "すまない、助かる。";
		mes "今はオーブの魔力すらも";
		mes "惜しい状況なんだ。";
		next;
		mes "[ヒシエ]";
		mes "では……";
		mes "^0000FF「光輝のマナ」";
		mes "「生命のマナ」";
		mes "「大地のマナ」^000000";
		mes "それぞれ3つ、解放してほしい。";
		next;
		mes "[ヒシエ]";
		mes "とはいえ、無理はしなくていい。";
		mes "無事に帰ることを優先してくれ。";
		setquest 7595;
		close2;
		cutin "hisie01",255;
		end;
	}
OnInit:
	waitingroom "オーブの魔力回収",0;
	end;
}

moro_vol.gat,94,110,5	script	守護者ニーズヘッグ#143n	510,{
	if(checkquest(201730)) {	// 魔神殿攻略済み？
		mes "[守護者ニーズヘッグ]";
		mes "不思議です……。";
		mes "私は確かに彼の者を";
		mes "この世から消したかった……。";
		mes "そして、その願いは叶いました……。";
		mes "……ですが、なぜこんなにも";
		mes "気持ちが落ち着かないのでしょう？";
		cutin "ep14_nyd02",2;
		next;
		mes "[守護者ニーズヘッグ]";
		mes "分かりません……。";
		mes "守護者としての役割を一応は";
		mes "果たせたから……でしょうか。";
		mes "もしかしますとまだ、実感が";
		mes "沸かないからかもしれませんね……。";
		cutin "ep14_nyd01",2;
		next;
		mes "[守護者ニーズヘッグ]";
		mes "でも……。";
		mes "……きっといつか";
		mes strcharinfo(0)+ "様に";
		mes "助けていただいた";
		mes "この日のことを思い出して、";
		mes "笑える日がくると思っています。";
		cutin "ep14_nyd04",2;
		close2;
		cutin "ep14_nyd01",255;
		end;
	}
	cutin "ep14_nyd03",2;
	mes "[守護者ニーズヘッグ]";
	mes "もうすぐ決戦の日が";
	mes "やってきます。";
	mes "遅ればせながら";
	mes "守護者としての義務を";
	mes "遂行しましょう。";
	next;
	cutin "ep14_nyd04",2;
	mes "[守護者ニーズヘッグ]";
	mes "私はかつて過ちを犯してしまいました。";
	mes "その償いというわけではありませんが、";
	mes "出来る限りの力を尽くしましょう。";
	close2;
	cutin "ep14_nyd04",255;
	end;
}

moro_vol.gat,97,110,3	script	ロキ#1432loki01	512,{
	cutin "ep14_roki01",2;
	mes "[ロキ]";
	mes "これはまだ前哨戦だ。";
	mes "あいつの真の姿が現れた時。";
	mes "そこからが本当の始まりだ。";
	close2;
	cutin "ep14_roki01",255;
	end;
}

moro_vol.gat,98,107,3	script	魔学者#143avt01	618,{
	if(ECL_3QUE < 33) {	// エクラージュの王
		cutin "avant01",1;
		mes "[魔学者]";
		mes "……邪魔だ。";
		mes "私の実験材料になりたいのか？";
		mes "手伝う気が無いならここから去れ。";
		close2;
		cutin "avant01",255;
		end;
	}
	switch(FVOL_3QUE) {
	case 0:
		cutin "avant01",1;
		mes "[エイヴァント]";
		mes "ここには何の用だ？";
		mes "君も私をあざ笑いに来たのか？";
		next;
		menu "何故ここに？",-;
		mes "[エイヴァント]";
		mes "……愚問だな。";
		mes "これは私のプライドの問題だ。";
		mes "とはいえ一族を危機に";
		mes "さらしかけたことは";
		mes "認めよう。";
		next;
		cutin "avant02",1;
		mes "[エイヴァント]";
		mes "今回の協力は、";
		mes "それに対する贖罪ともいえるだろう。";
		mes "……いや。";
		mes "皆はそう思っているはずだ！";
		mes "ハハハハハハハハ！";
		next;
		mes "[エイヴァント]";
		mes "だがな！";
		mes "私の目的は違うのだよ！";
		mes "私を利用したシナイムと";
		mes "魔王モロクに仕返しをしたい";
		mes "だけなのだよ！";
		next;
		mes "[エイヴァント]";
		mes "最後に笑うのはシナイムでも……";
		mes "魔王モロクでもない！";
		mes "最後に笑うのは誰か……！";
		mes "期待するがいい！";
		mes "ハハハハハハハハ！";
		set FVOL_3QUE,1;
		close2;
		cutin "avant01",255;
		end;
	case 1:
		if(checkquest(7581) == 0) {	// 変異した現身退治受注
			cutin "avant01",1;
			mes "[エイヴァント]";
			mes "……ふん、極小の魔力でも";
			mes "あのような運用が可能とはな……。";
			mes "盗んだ魔力で強くなろうとは……";
			mes "汚らわしいやつらめ！";
			close2;
			cutin "avant01",255;
			end;
		}
		if(checkquest(7584)) {
			if(checkquest(7584)&0x2 == 0) {
				cutin "avant01",1;
				mes "[エイヴァント]";
				mes "……次の討伐の時も頼むぞ。";
				close2;
				cutin "avant01",255;
				end;
			}
			cutin "avant01",1;
			mes "[エイヴァント]";
			mes "もうすぐ人間連合から";
			mes "再度魔族討伐に出るはずだ。";
			mes "出発前にここに寄るがいい。";
			mes "^ff0000マナクリスタル^000000を集める";
			mes "必要があるからな。";
			delquest 7584;
			close2;
			cutin "avant01",255;
			end;
		}
		if(checkquest(7583)) {
			if(countitem(6708) < 3) {
				cutin "avant01",1;
				mes "[エイヴァント]";
				mes "お前があの強大な魔族を";
				mes "倒せば^ff0000マナクリスタル^000000が";
				mes "入手可能なはずだ。";
				mes "それを回収して来るんだ。";
				mes "最低3つ、分かったな？";
				mes "3つ以上だ。";
				close2;
				cutin "avant01",255;
				end;
			}
			cutin "avant01",1;
			mes "[エイヴァント]";
			mes "……フン、やるな。";
			mes "^ff0000マナクリスタル^000000はもらうぞ。";
			delitem 6708,3;
			chgquest 7583,7584;
			getexp 1000000,0,1;
			getexp 1000000,0,1;
			getexp 1000000,0,1;
			getexp 1000000,0,1;
			getexp 1000000,0,1;
			close2;
			cutin "avant01",255;
			end;
		}
		cutin "avant01",1;
		mes "[エイヴァント]";
		mes "おい、お前。";
		mes "そうだ、お前だ。";
		mes "向こうのやけに";
		mes "強そうなやつらが見えるか？";
		mes "見たところ、あやつらを";
		mes "倒しに行くようだが……。";
		next;
		mes "[エイヴァント]";
		mes "^ff0000歪んだモロクの現身";
		mes "炎火のモロクの現身";
		mes "冷気のモロクの現身^000000を";
		mes "倒せば^ff0000マナクリスタル^000000が";
		mes "手に入るはずだ。";
		next;
		mes "[エイヴァント]";
		mes "^ff0000マナクリスタル^000000はオーブから奪取された";
		mes "魔力の一部だ。";
		mes "魔族の分際であれほどまでに";
		mes "強くなったのは";
		mes "オーブの魔力のおかげ、";
		mes "というわけだ。";
		next;
		mes "[エイヴァント]";
		mes "……。";
		mes "何が言いたいのか分からないのか？";
		mes "あいつらを倒して";
		mes "^ff0000マナクリスタル^000000をもってこい。";
		mes "お前には到底扱えないものだからな、";
		mes "そのままもってくるのだ。";
		next;
		mes "[エイヴァント]";
		mes "全部で3匹、";
		mes "^ff0000マナクリスタル^000000も当然3つだ。";
		mes "……エクラージュ……ひいては";
		mes "カルデュイのためにもな……。";
		setquest 7583;
		close2;
		cutin "avant01",255;
		end;
	}
OnInit:
	waitingroom "マナクリスタル回収",0;
	end;
}

moro_vol.gat,108,88,5	script	司令官アジフ#14301	459,{
	cutin "ep13_captin_edq",2;
	if(checkquest(116545)) {
		mes "[司令官アジフ]";
		mes "どうした？";
		mes "魔王モロクはいたか？";
		mes "もし奴を倒すことができたのなら";
		mes "まず守護者のお嬢さんと";
		mes "話をしてみてくれ。";
		next;
		mes "[司令官アジフ]";
		mes "お嬢さんは魔神殿の入口の";
		mes "世界樹に似た樹の前にいるから";
		mes "送ってやろう。";
		close2;
		cutin "ep13_captin_edq",255;
		warp "moro_cav.gat",41,69;
		end;
	}
	if(checkquest(7593)) {
		mes "[司令官アジフ]";
		mes "魔神殿が発見されたのは";
		mes "中央にある丘の洞窟だ。";
		mes "内部に何故か、樹があるらしい。";
		next;
		mes "[司令官アジフ]";
		mes "守護者と呼ばれている";
		mes "お嬢さんも行くそうだ。";
		mes "そのお嬢さんを探せばいいだろう。";
		close2;
		cutin "ep13_captin_edq",255;
		end;
	}
	if(checkquest(7597)) {
		if(checkquest(201730)) {
			mes "[司令官アジフ]";
			mes "お、今日もお疲れさん。";
			mes "それで、魔神殿の方はどうだ？";
			mes "……どうやら";
			mes "おまえのその様子から";
			mes "特に進展はないみたいだな。";
			next;
			mes "[司令官アジフ]";
			mes "それでは、報酬だ。";
			mes "これを受け取ってくれ。";
			mes "また次回もよかったら、頼む。";
			delquest 7597;
			getitem 7444,2;
			close2;
			cutin "ep13_captin_edq.bmp", 255;
			end;
		}
		mes "[司令官アジフ]";
		mes "おお!!";
		mes "……英雄の帰還だ！";
		mes "はははははは!!";
		mes "ついにこの長かった";
		mes "遠征の終わりだ！";
		mes "ご苦労だった!!";
		next;
		mes "[司令官アジフ]";
		mes "全人類に代わりこの俺、";
		mes "ヒバ・アジフからおまえに";
		mes "感謝を言わせてくれ。";
		next;
		cutin "ep13_captin_edq",255;
		mes "[アビダル]";
		mes "本当に素晴らしい働きですよ。";
		mes "あなたはこの世界を救ったも";
		mes "同然の偉業を成し遂げたのですから。";
		mes "これで私の肩の荷も";
		mes "下りそうですね……。";
		next;
		cutin "ep13_captin_edq",2;
		mes "[司令官アジフ]";
		mes "アビダル!";
		mes "そこまでだ！";
		mes "それ以上しゃべると";
		mes "危険なフラグが";
		mes "立つらしいぞ！";
		next;
		mes "[司令官アジフ]";
		mes "さて、おまえも言葉だけでは";
		mes "物足りないだろう。";
		mes "おまえの功労を労って";
		mes "準備したものがある。";
		next;
		mes "[司令官アジフ]";
		mes "たいしたものじゃないが、";
		mes "良かったら受け取ってくれ。";
		mes "もっと良いものが用意できれば";
		mes "良かったんだがな……。";
		next;
		mes "[司令官アジフ]";
		mes "しかし……";
		mes "ふははははははっ！";
		mes "これでやっと酒瓶を枕にじゃなく";
		mes "普通にベッドの枕を高くして";
		mes "眠れそうだな！";
		mes "本当によくやってくれた！";
		next;
		mes "[司令官アジフ]";
		mes "だが、油断は禁物だ。";
		mes "しばらくは引き続き";
		mes "魔神殿の調査をしてくれないか？";
		mes "また魔王モロクが復活したら";
		mes "たまらんからな！";
		mes "よろしく頼んだぞ！";
		delquest 7597;
		setquest 7598;
		setquest 201730;
		getitem 7444,2;
		close2;
		cutin "ep13_captin_edq",255;
		end;
	}
	if(checkquest(7598)) {
		if(checkquest(7598)&0x2 == 0) {
			mes "[司令官アジフ]";
			mes "本体は片付けたんだ。";
			mes "ゆっくり慎重に進めるとしよう。";
			mes "その間、おまえは少し休んだ方がいい。";
			mes "残りはこっちにも任せてくれ。";
			next;
			mes "[司令官アジフ]";
			mes "そうだな……。";
			mes "入場してから1回目の";
			mes "^ff0000午前5時以降^000000に来てくれ。";
			mes "その時に何かあれば伝えよう。";
			next;
			mes "[司令官アジフ]";
			mes "まあ、最後の入場をしてから";
			mes "^ff00001時間30分^000000経過するまでは";
			mes "何もないだろうから";
			mes "安心して休んでくれ。";
			close2;
			cutin "ep13_captin_edq",255;
			end;
		}
		delquest 7598;
		mes "[司令官アジフ]";
		mes "へえ……つい先日、";
		mes "決戦に挑んだばかりだっていうのに";
		mes "なんとも無いみたいだな。";
		mes "さすが、鍛えてるだけあるな。";
		next;
		mes "[司令官アジフ]";
		mes "もしまた志願してくれるなら";
		mes "いつでも俺にいってくれ。";
		mes "モロクは確かに倒したはずなのに";
		mes "未だにあの魔神殿が";
		mes "そのままなのは気になる……。";
		next;
		mes "[司令官アジフ]";
		mes "これもまた次元の狭間の";
		mes "なせるわざというべき現象かも知れん。";
		mes "とはいえ、おまえが必ずしも";
		mes "調べに行く必要はない。";
		mes "俺たちも働かないとな！";
		close2;
		cutin "ep13_captin_edq",255;
		end;
	}
	if(checkquest(201730)) {
		mes "[司令官アジフ]";
		mes "しかし……どう考えても";
		mes "分からないな。";
		mes "「あれ」が神になると";
		mes "暴れ出した時点から、";
		mes "この場所の空気や雰囲気が";
		mes "一転したからな。";
		next;
		mes "[司令官アジフ]";
		mes "詳しくはわからないのだが";
		mes "どうやら一度ねじれてしまった";
		mes "次元の均衡は回復できないようだ。";
		mes "そこで相談だ！";
		mes "「魔神殿」にもう一度";
		mes "行ってみる気はないか？";
		next;
		if(select("行ってみる","行かない") == 2) {
			mes "[司令官アジフ]";
			mes "そうか。";
			mes "おまえはもう充分";
			mes "頑張ってくれたしな。";
			mes "うむ、仕方あるまい。";
			mes "他の人に頼むとしよう。";
			close2;
			cutin "ep13_captin_edq",255;
			end;
		}
		mes "[司令官アジフ]";
		mes "漠然と考えていたんだが、";
		mes "「魔神殿」は時間を";
		mes "繰り返す力があるのかも";
		mes "しれんな……。";
		mes "要するに、今まで観察された";
		mes "次元の狭間の状態と同じだ。";
		next;
		mes "[司令官アジフ]";
		mes "そう考えると、だ。";
		mes "この世界から抜け出そうと";
		mes "もがいても結局のところ、";
		mes "主神の掌の中なのではないかと";
		mes "思うのだが……。";
		next;
		mes "[司令官アジフ]";
		mes "すまない、無駄話が長くなった。";
		mes "探索を改めてお願いしたい。";
		mes "もし、過去を忘れたモロクに";
		mes "また会った場合だが……。";
		next;
		mes "[司令官アジフ]";
		mes "忘れた過去が";
		mes "思い出せるように";
		mes "再度、教育してやってくれ。";
		mes "ただし、相手は魔王だ。";
		mes "気を抜かずに、対応しろよ。";
		mes "では、健闘を祈る。";
		if(checkquest(7593) == 0)
			setquest 7593;
		close2;
		cutin "ep13_captin_edq",255;
		end;
	}
	if(checkquest(201720) && checkquest(201725)) {	// ビオスの島、モルスの洞窟クリア済み
		mes "[司令官アジフ]";
		mes "ちょうど良いところに来たな。";
		mes "あの暗い洞窟に道が";
		mes "できたらしい。";
		next;
		mes "[司令官アジフ]";
		mes "そして、その洞窟の道を進んだ先に";
		mes "新しい地域が発見された。";
		mes "その新しく発見された地域を";
		mes "今後は^FF0000魔神殿^000000と呼ぶことにした。";
		mes "探索で最初に見つけた者が";
		mes "そう呼んだそうだが……。";
		next;
		mes "[司令官アジフ]";
		mes "実際に確認したところ、";
		mes "なるほど、という感じだったからな。";
		mes "そのまま使うことにしたんだ。";
		mes "わかりやすいしな。";
		next;
		mes "[司令官アジフ]";
		mes "そして本題はここからだが……";
		mes "どうやらその魔神殿の奥深く、";
		mes "深層部と呼ばれる場所に";
		mes "魔王モロクが潜んでいるようなんだ。";
		next;
		mes "[司令官アジフ]";
		mes "俺たち連合軍も総攻撃をしかけようと";
		mes "勇み足で向かったのだが……";
		mes "魔王モロクに気付かれてしまってな。";
		mes "魔王モロクの潜む深層部に";
		mes "辿りつけなかったんだ。";
		next;
		mes "[司令官アジフ]";
		mes "色々と試してみたんだが";
		mes "どうしても大勢だと気付かれてしまう。";
		mes "守護者のお嬢さんとも相談したんだが、";
		mes "やはり、少人数で挑むしか";
		mes "方法はなさそうなんだ。";
		next;
		mes "[司令官アジフ]";
		mes "そこでおまえには";
		mes "魔神殿の内部にいるであろう";
		mes "魔王モロクの討伐を依頼したい。";
		next;
		mes "[司令官アジフ]";
		mes "黄色い種や赤い花での";
		mes "お前の活躍は聞いている。";
		mes "お前以上に腕の立つ者は";
		mes "連合軍には居ないだろう。";
		next;
		mes "[司令官アジフ]";
		mes "世界の命運を託せるのは";
		mes "お前しかいない。";
		mes "どうか、よろしく頼む。";
		next;
		mes "[司令官アジフ]";
		mes "だが、これは命令ではなく依頼だ。";
		mes "命がかかっている危険な仕事だしな。";
		mes "おまえが決めればいい。";
		mes "無論、断ったからといって、";
		mes "誰もおまえを責めたりはせん。";
		next;
		if(select("……やります！","……遠慮します") == 2) {
			mes "[司令官アジフ]";
			mes "それは仕方ない。";
			mes "命あっての物種だ。。";
			mes "ここまで協力してくれただけでも";
			mes "ありがたかったぜ。";
			close2;
			cutin "ep13_captin_edq",255;
			end;
		}
		mes "[司令官アジフ]";
		mes "……そう言ってくれると思ったぜ。";
		mes "やはりおまえは信頼に値するな。";
		mes "ロキとかいうやつの言葉によると、";
		mes "魔王はまだ封印が解けたときに受けた";
		mes "ダメージを完全には";
		mes "回復していないらしい。";
		next;
		mes "[司令官アジフ]";
		mes "未だに身を潜めているのも";
		mes "そのせいかも知れんな。";
		mes "とはいえ、俺たちにとっては";
		mes "その方が好都合な部分もある。";
		mes "……健闘を祈る。";
		setquest 7593;
		close2;
		cutin "ep13_captin_edq",255;
		end;
	}
	mes "[司令官アジフ]";
	mes "ここの景色は見る者を";
	mes "不安にさせたり、イラつかせる";
	mes "何かがあるな……。";
	mes "このどこかにモロクが";
	mes "潜んでいるということだが……。";
	next;
	mes "[司令官アジフ]";
	mes "確かに魔王が身を隠すのに";
	mes "適している……ようにも見えるな。";
	mes "ここでうろついているものは";
	mes "モロク砂漠から";
	mes "狭間の力に巻き込まれ……";
	mes "瘴気に汚染されたんだろうな。";
	next;
	mes "[司令官アジフ]";
	mes "ったく……。";
	mes "……次から次へと……。";
	mes "……。";
	next;
	mes "[司令官アジフ]";
	mes "……すまん。";
	mes "いや、愚痴るつもりは無かったんだが";
	mes "この土地の空気に";
	mes "毒されたのかもしれん。";
	next;
	mes "[司令官アジフ]";
	mes "おまえにはまた何か";
	mes "頼むかもしれないからな。";
	mes "それまで生き延びてくれよ。";
	close2;
	cutin "ep13_captin_edq",255;
	end;
OnInit:
	waitingroom "魔神殿",0;
	end;
}

moro_vol.gat,110,90,3	script	参謀アビダル#14302	755,{
	if(checkquest(7599)) {
		if(checkquest(7599)&0x2 == 0) {
			mes "[アビダル]";
			mes "ご苦労様でした。";
			mes "すこし休んでください。";
			next;
			mes "‐^ff0000魔神殿討伐報告は";
			mes "　最後に報告してから、";
			mes "　1回目の午前5時以降に、";
			mes "　再度、受注することが";
			mes "　できるようになります^000000‐";
			close;
		}
		delquest 7599;
		mes "[アビダル]";
		mes "ぐっすり休めましたか？";
		mes "顔色で判断するに";
		mes "よくなったようですね。";
		mes "ほっとしました。";
		mes "未だに閉じられずに佇む";
		mes "魔神殿に困っていたところです……。";
		next;
		mes "[アビダル]";
		mes "また魔神殿に住む魔物を討伐したら、";
		mes "私に報告してください。";
		mes "功績に応じた報酬を";
		mes "差し上げます。";
		close;
	}
	if(checkquest(96435)&4 || checkquest(96436)&4 || checkquest(96437)&4 || checkquest(96438)&4) {
		mes "[アビダル]";
		mes "魔神殿の魔物を倒してきたようですね！";
		mes "これだけの成果があれば十分です！";
		next;
		mes "[アビダル]";
		mes "少ないながら御礼を用意しております。";
		mes "では魔物を退治してきた報告書を";
		mes "作成していただけますか？";
		mes "また^ff0000報告は一日一回^000000に限られています。";
		next;
		mes "[アビダル]";
		mes "面倒かもしれませんが規則ですので";
		mes "ご理解をお願いします。";
		mes "報告書を作成しますか？";
		next;
		if(select("作成する","まだ作成しない") == 2) {
			mes "[アビダル]";
			mes "後にしますか？";
			mes "用意ができたら声をかけてください。";
			close;
		}
		mes "[アビダル]";
		mes "お疲れ様でした。";
		mes "こちらが報酬となります。";
		mes "ゆっくり体を休めてください。";
		setquest 7599;
		if(checkquest(96435)&4) {
			delquest 96435;
			set '@gain[0],1;
		}
		if(checkquest(96436)&4) {
			delquest 96436;
			set '@gain[2],'@gain[2]+1;
		}
		if(checkquest(96437)&4) {
			delquest 96437;
			set '@gain[1],'@gain[1]+1;
			set '@gain[2],'@gain[2]+1;
		}
		if(checkquest(96438)&4) {
			delquest 96438;
			set '@gain[2],'@gain[2]+1;
		}
		if('@gain[0]) {
			getitem 7228,'@gain[0];
			getitem 7229,'@gain[0];
		}
		if('@gain[1])
			getitem 22567,'@gain[1];
		if('@gain[2])
			getitem 7444,'@gain[2];
		close;
	}
	if(checkquest(7593)) {
		mes "[アビダル]";
		mes "魔神殿に向かうのですか？";
		mes "偵察兵によると、魔神殿の中には";
		mes "モロクの部下と思われる、";
		mes "今まで見たこともない魔物が";
		mes "存在していたとのことです。";
		next;
		mes "[アビダル]";
		mes "もしその魔物達を退治したら、";
		mes "私に報告してもらえますか。";
		mes "功績に応じた報酬を";
		mes "差し上げます。";
		next;
		mes "[アビダル]";
		mes "もちろん魔王モロクを";
		mes "討ち果たしたという吉報は";
		mes "私ではなく^ff0000アジフ司令官^000000に";
		mes "報告してくださいね。";
		close;
	}
	mes "[アビダル]";
	mes "あなたも魔王を退治するために";
	mes "志願してきた方ですか？";
	mes "ここの環境は変化が激しいので";
	mes "注意を怠らないでくださいね。";
	close;
OnInit:
	waitingroom "魔神殿討伐報告",0;
	end;
}

moro_vol.gat,111,87,1	script	教官長イグリド#14303	751,{
	if(checkquest(7582)) {
		if(checkquest(7582)&0x2 == 0) {
			mes "[イグリド]";
			mes strcharinfo(0)+ "か。";
			mes "あの強力な現身のことだが、";
			mes "おまえにだけ任せるわけには";
			mes "いかないからな、";
			mes "他の者にも指示をしたんだ。";
			next;
			mes "[イグリド]";
			mes "まずは体を休ませてくれ。";
			mes "狩りはまた明日からだ。";
			close;
		}
		mes "[イグリド]";
		mes "そろそろ魔族狩りの時間だ。";
		mes "期待に胸躍るな！　ははは！";
		delquest 7582;
		close;
	}
	if(checkquest(7581)) {
		if(checkquest(7581)&0x4 == 0) {
			mes "[イグリド]";
			mes "^4d4dff歪んだモロクの現身、";
			mes "炎火のモロクの現身、";
			mes "冷気のモロクの現身^000000を";
			mes "討伐してくれ。";
			mes "フレイムヴァレーを中心に";
			mes "それぞれの方位にいるはずだ。";
			close;
		}
		mes "[イグリド]";
		mes "期待と予想通りだな。";
		mes "力を持つ魔族を討伐したことで";
		mes "やつらの勢いも少しは";
		mes "弱まるはずだ。";
		mes "助かったよ。";
		next;
		mes "[イグリド]";
		mes "まずは体を休めて";
		mes "また討伐に参加して欲しい。";
		mes "帰るときにはみんな一緒に";
		mes "帰りたいからな。";
		chgquest 7581,7582;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		close;
	}
	mes "[イグリド]";
	mes "フレイムヴァレーに現われる";
	mes "魔族の中で、手をやいている";
	mes "相手がいる。";
	mes "そいつのおかげでかなり";
	mes "困難な状況に陥っているんだ。";
	next;
	mes "[イグリド]";
	mes "そいつはモロクの現身と";
	mes "見た目は同じなんだが、";
	mes "強力なオーラを纏っている。";
	mes "強さもケタ違いで、このままだと";
	mes "各隊の被害がさらに増えていくだろう。";
	next;
	mes "[イグリド]";
	mes "そこでおまえの腕を見込んで";
	mes "頼みがある。";
	mes "そいつを退治してきてくれないか？";
	mes "危険な相手だが、";
	mes "このままにしてはおけないんだ。";
	next;
	if(select("いやです","やります") == 1) {
		mes "[イグリド]";
		mes "……まさか断られるとは";
		mes "思わなかった。";
		mes "おまえもミッドガルドの平和のために";
		mes "ここに来たのではなかったのか？";
		next;
		mes "[イグリド]";
		mes "俺の目が間違っていたのかもしれん。";
		mes "討伐は他の者に任せるとしよう。";
		close;
	}
	mes "[イグリド]";
	mes "そうか！　やってくれるか！";
	mes "では説明しよう。";
	mes "フレイムヴァレーの中央には";
	mes "大きな岩がある。";
	mes "その岩を中心とした方位に";
	mes "強い力を持つ魔族が集まっている。";
	next;
	mes "[イグリド]";
	mes "外見だけならモロク近くでも";
	mes "見かけた魔王の下僕と同じなのだが……";
	mes "強さのケタが違うらしい。";
	mes "お陰でなかなかうまくいかず、";
	mes "怪我人も増えるばかりだ。";
	next;
	mes "[イグリド]";
	mes "そこでおまえにはその魔族、";
	mes "^4d4dff歪んだモロクの現身、";
	mes "炎火のモロクの現身、";
	mes "冷気のモロクの現身^000000を";
	mes "討伐してきてほしい。";
	mes "すまんが、頼む。";
	setquest 7581;
	close;
OnInit:
	waitingroom "変異した現身退治",0;
	end;
}

moro_vol.gat,136,84,3	script	大臣ヘスランタ#ep143	451,{
	switch(FVOL_4QUE) {
	case 0:
		if(DIC_2QUE < 23) {
			cutin "ep13_heslanta",2;
			mes "[ヘスランタ]";
			mes "サファ族代表として戦場の";
			mes "指揮を取るヘスランタと申します。";
			mes "これからあなた達人間と";
			mes "戦闘を共にしますので、";
			mes "お見知りおきを。";
			close2;
			cutin "ep13_heslanta",255;
			end;
		}
		cutin "ep13_heslanta",2;
		mes "[ヘスランタ]";
		mes "これはこれは、お久しぶりです。";
		mes "私を覚えていますか？";
		mes "ディエルにて会話を";
		mes "交わしたことを";
		mes "私は覚えていますよ。";
		next;
		menu "ここには何故？",-;
		mes "[ヘスランタ]";
		mes "私の主張を通して軍を率いてきました。";
		mes "あなたの推測どおり、";
		mes "アハト……彼は";
		mes "サファ族ではなかったのです。";
		next;
		mes "[ヘスランタ]";
		mes "……もちろん、この事実を";
		mes "知っているのは私一人です。";
		next;
		mes "[ヘスランタ]";
		mes "彼に対する果て無き疑問が";
		mes "結果的に私を守りました。";
		mes "アハトは驚くべき暗示能力を駆使し、";
		mes "その姿をくらませたのです。";
		next;
		mes "[ヘスランタ]";
		mes "その後、私は魔王が潜む地に";
		mes "我々も合流すべきだと主張しました。";
		mes "他のサファ族には種族の";
		mes "安寧のためには派兵すべきでないと";
		mes "猛反対されましたが……。";
		next;
		mes "[ヘスランタ]";
		mes "サファ族は同盟を結んだ仲間が";
		mes "危機に陥るのを黙って";
		mes "見過ごしたりはしません。";
		mes "ですから私が勇敢なガルトンを率いて";
		mes "ここに来ることになったのです。";
		next;
		mes "[ヘスランタ]";
		mes "話が長くなりましたね。";
		mes "もし、お時間があるようでしたら";
		mes "私の仕事を";
		mes "手伝っていただきたいのです。";
		next;
		mes "[ヘスランタ]";
		mes "チェシャーは知っていますね？";
		mes "チェシャーと関連する仕事なので";
		mes "他の人には任せられないのです。";
		mes "まだ仕事をする準備は";
		mes "整っていませんが……。";
		next;
		mes "[ヘスランタ]";
		mes "チェシャーに関する情報を集めた上で";
		mes "本格的に仕事を";
		mes "進めようと思います。";
		mes "それまではお気をつけて。";
		set FVOL_4QUE,1;
		close2;
		cutin "ep13_heslanta",255;
		end;
	case 1:
		cutin "ep13_heslanta",2;
		mes "[ヘスランタ]";
		mes "以前、チェシャーに関する話を";
		mes "したことを覚えていますか？";
		mes "事が事ですので……。";
		mes "他のサファ族にはどうしても";
		mes "話せませんでした。";
		mes "そこで相談ですが……";
		next;
		mes "[ヘスランタ]";
		mes "私の推測が合っているか";
		mes "確認をしたいのですが、";
		mes "手伝ってもらえますか？";
		next;
		menu "どんなことですか",-;
		mes "[ヘスランタ]";
		mes "ここ……フレイムヴァレーに";
		mes "とても似合わない……";
		mes "というのが、";
		mes "正しいかはわかりませんが……";
		mes "箱が飛んでいるのです。";
		next;
		mes "[ヘスランタ]";
		mes "瘴気に染まり自ら";
		mes "移動する暴虐の箱……です。";
		mes "ですがあれはまるで……";
		next;
		menu "まるで…？",-;
		mes "[ヘスランタ]";
		mes "エルディカスティスの";
		mes "ブラディウムの箱と";
		mes "非常に似ているんです。";
		mes "相談はここからです。";
		mes "その箱を退治して";
		mes "正体を調べたいのです。";
		next;
		mes "[ヘスランタ]";
		mes "あれはチェシャーが";
		mes "こっそり持ち出したという";
		mes "ブラディウムの箱だと";
		mes "私はにらんでいます。";
		next;
		mes "[ヘスランタ]";
		mes "もしそうなら、ここでブラディウムを";
		mes "回収して使うことで、";
		mes "補給の負担が少しは減ります。";
		next;
		mes "[ヘスランタ]";
		mes "今回の遠征は私の独断に";
		mes "近い形で行われたので";
		mes "補給が芳しくありません。";
		mes "まずは箱の正体を";
		mes "暴くことから始まります。";
		next;
		mes "[ヘスランタ]";
		mes "箱を退治し何が出てきたのか";
		mes "教えてください。";
		mes "お待ちしています。";
		set FVOL_4QUE,2;
		setquest 7578;
		close2;
		cutin "ep13_heslanta",255;
		end;
	case 2:
		if(checkquest(7578)&0x4 == 0 || countitem(6392) == 0) {
			cutin "ep13_heslanta",2;
			mes "[ヘスランタ]";
			mes "^4d4dff暴虐の箱^000000を退治して獲得したものを";
			mes "持ち帰ってきてください。";
			close2;
			cutin "ep13_heslanta",255;
			end;
		}
		cutin "ep13_heslanta",2;
		mes "[ヘスランタ]";
		mes "これは……予想通りではありますが……";
		mes "無機物である箱がどうやって";
		mes "動いたりしたのかは分かりません……。";
		mes "何かの魔力のせいでしょうか。";
		next;
		mes "[ヘスランタ]";
		mes "ですが、これで確信が持てました。";
		mes "フレイムヴァレーの箱は全て";
		mes "エルディカスティスの";
		mes "ブラディウムの箱ということが。";
		next;
		mes "[ヘスランタ]";
		mes "お手数をかけることになりますが、";
		mes "この仕事は継続的にお願いします。";
		mes "まだここには信じられる人が";
		mes "あまりいません。";
		next;
		mes "[ヘスランタ]";
		mes "ガルトンは勇敢ですが、";
		mes "ブラディウムの箱がこのような場所で";
		mes "見つかることに疑問を持つでしょう。";
		mes "その疑問が疑惑に変わる前に";
		mes "誤解を解くには話が";
		mes "長くなりすぎます。";
		next;
		menu "それでいつから始めれば？",-;
		mes "[ヘスランタ]";
		mes "そうですね、では早速お願いします。";
		mes "^4d4dff暴虐の箱^000000を退治し、";
		mes "^4d4dffブラディウムの箱を10個回収^000000してください。";
		delitem 6392,1;
		set FVOL_4QUE,3;
		chgquest 7578,7579;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		close2;
		cutin "ep13_heslanta",255;
		end;
	case 3:
		if(checkquest(7579)&0x4 == 0 || countitem(6392) < 10) {
			cutin "ep13_heslanta",2;
			mes "[ヘスランタ]";
			mes "暴虐の箱はそんなに";
			mes "危険ではないですが……";
			mes "場所が場所なので";
			mes "気をつけてください。";
			next;
			mes "[ヘスランタ]";
			mes "ではよろしくお願いします。";
			close2;
			cutin "ep13_heslanta",255;
			end;
		}
		cutin "ep13_heslanta",2;
		mes "[ヘスランタ]";
		mes "お疲れ様です。";
		mes "ありがとうございました。";
		mes "集めたブラディウムの箱は";
		mes "こちらで回収いたします。";
		next;
		mes "[ヘスランタ]";
		mes "おっと……周りの視線がありますね。";
		mes "ではまたお願いします。";
		delitem 6392,countitem(6392);
		set FVOL_4QUE,4;
		chgquest 7579,7580;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		getexp 1000000,0,1;
		close2;
		cutin "ep13_heslanta",255;
		end;
	case 4:
		if(checkquest(7579)) {
			if(checkquest(7579)&0x4 == 0 || countitem(6392) < 10) {
				cutin "ep13_heslanta",2;
				mes "[ヘスランタ]";
				mes "暴虐の箱はそんなに";
				mes "危険ではないですが……";
				mes "場所が場所なので";
				mes "気をつけてください。";
				next;
				mes "[ヘスランタ]";
				mes "ではよろしくお願いします。";
				close2;
				cutin "ep13_heslanta",255;
				end;
			}
			cutin "ep13_heslanta",2;
			mes "[ヘスランタ]";
			mes "お疲れ様です。";
			mes "ありがとうございました。";
			mes "集めたブラディウムの箱は";
			mes "こちらで回収いたします。";
			next;
			mes "[ヘスランタ]";
			mes "おっと……周りの視線がありますね。";
			mes "ではまたお願いします。";
			delitem 6392,countitem(6392);
			chgquest 7579,7580;
			getexp 1000000,0;
			getexp 1000000,0;
			getexp 1000000,0;
			getexp 1000000,0;
			getexp 1000000,0;
			close2;
			cutin "ep13_heslanta",255;
			end;
		}
		if(checkquest(7580)) {
			if(checkquest(7580)&0x2 == 0) {
				cutin "ep13_heslanta",2;
				mes "[ヘスランタ]";
				mes "ふふふ……まだまだ余裕がありますね。";
				mes "チェシャーは自分がかすめた";
				mes "ブラディウムが途中で";
				mes "回収されていることを";
				mes "知っているでしょうか？";
				next;
				mes "[ヘスランタ]";
				mes "あのかわいそうな猫には……";
				mes "後で何かエサを与えるとしましょう。";
				mes "ああ、また今度";
				mes "ブラディウムの箱の回収を";
				mes "お願いします。";
				close2;
				cutin "ep13_heslanta",255;
				end;
			}
			cutin "ep13_heslanta",2;
			mes "[ヘスランタ]";
			mes "そういえばもうこんな時間ですね。";
			mes "また箱の回収をお願いします。";
			delquest 7580;
			next;
			if(select("わかりました","また後で") == 2) {
				mes "[ヘスランタ]";
				mes "はい、急ぎではないので、";
				mes "時間が余ったときで構いません。";
				next;
				mes "[ヘスランタ]";
				mes "いつもありがとうございます。";
				mes "それではまた。";
				close2;
				cutin "ep13_heslanta",255;
				end;
			}
		}
		cutin "ep13_heslanta",2;
		mes "[ヘスランタ]";
		mes "おいでになりましたか。";
		mes "……では、今日もお願いしても？";
		next;
		if(select("やります","また後で") == 2) {
			mes "[ヘスランタ]";
			mes "はい、急ぎではないですから。";
			mes "時間が余ったときでいいので。";
			next;
			mes "[ヘスランタ]";
			mes "いつもありがとうございます。";
			mes "それではまた。";
			close2;
			cutin "ep13_heslanta",255;
			end;
		}
		mes "[ヘスランタ]";
		mes "それでは今日もよろしくお願いします。";
		mes "^4d4dff暴虐の箱^000000を退治し、";
		mes "^4d4dffブラディウムの箱を10個回収^000000してください。";
		setquest 7579;
		close2;
		cutin "ep13_heslanta",255;
		end;
	}
OnInit:
	waitingroom "暴虐の箱",0;
	end;
}

moro_vol.gat,134,83,5	script	ビハヌス#ep143	451,{
	mes "[ビハヌス]";
	mes "あなたもここに来ましたか。";
	mes "……そういえばここでは";
	mes "指輪の力が無くても";
	mes "言葉が通じますね？";
	next;
	mes "[ビハヌス]";
	mes "ビフロストの意思は";
	mes "どこにまで届くのでしょうか……。";
	mes "ぜひこの機会にラフィネ族とも";
	mes "ひざを交えて話したいものです。";
	next;
	mes "[ビハヌス]";
	mes "それはさておき、";
	mes "ヘスランタ様はすごいですな。";
	mes "ラフィネ族と不安定な同盟を";
	mes "結んだにも関わらず、";
	mes "戦場に自ら赴いているわけですから。";
	next;
	mes "[ビハヌス]";
	mes "ともあれラフィネ族と";
	mes "摩擦が無いことを願います。";
	close;
}

moro_vol.gat,138,84,3	script	補佐官ティエラ#ep143	453,{
	mes "[ティエラ]";
	mes "ディエルにいた多くの";
	mes "ゼルートとニットは、";
	mes "ヘスランタ様の主張を";
	mes "渋々、聞き入れました。";
	next;
	mes "[ティエラ]";
	mes "ですが、私はヘスランタ様の意見に";
	mes "全面的に同感しています。";
	mes "種族を分けて戦う以前に、";
	mes "魔王という共通の敵を倒すためには";
	mes "力を合わせるべきです。";
	next;
	mes "[ティエラ]";
	mes "関わらなくていい……ではなく、";
	mes "共に戦わないと今の平和な生活が";
	mes "塵と化すことになりかねませんから。";
	next;
	mes "[ティエラ]";
	mes "そういうことですので、";
	mes "人間の皆さんも、";
	mes "どうか頑張ってください。";
	close;
}

moro_vol.gat,134,87,1	script	先発隊長アバランチェ#ep	450,{
	mes "[アバランチェ]";
	mes "例え数は少なくとも";
	mes "我々ガルトン部隊は精鋭中の精鋭だ。";
	mes "人間の戦士よ。";
	mes "共に戦うこの日を私は待っていたのだ！";
	next;
	mes "[アバランチェ]";
	mes "我は我が命をかけて共に";
	mes "魔王を打ち倒すことを誓う！";
	close;
}

moro_vol.gat,131,86,1	script	ガルトン#gal01	492,{
	mes "[ガルトン]";
	mes "戦闘はいつだ！";
	mes "いつ始まるのか！";
	next;
	mes "[ガルトン]";
	mes "あの小さなラフィネ族と";
	mes "共闘せねばならぬとは……。";
	mes "私はまだ過ぎ去りし戦闘で";
	mes "散っていった戦友たちのことを";
	mes "忘れてなどいないというのに。";
	close;
}

moro_vol.gat,138,87,7	script	ガルトン#gal02	492,{
	mes "[ガルトン]";
	mes "我が任務は";
	mes "ゼルート・ヘスランタ様の護衛。";
	mes "ここから立ち去るがいい。";
	mes "敵とみなす前にな！";
	close;
}

moro_vol.gat,140,97,1	script	精鋭部隊#gal11	492,{}
moro_vol.gat,143,97,1	script	精鋭部隊#gal12	492,{}
moro_vol.gat,146,97,1	script	精鋭部隊#gal13	492,{}
moro_vol.gat,140,94,1	script	精鋭部隊#gal14	450,{}
moro_vol.gat,143,94,1	script	精鋭部隊#gal15	450,{}
moro_vol.gat,146,94,1	script	精鋭部隊#gal16	450,{}

moro_vol.gat,150,86,1	script	精鋭部隊#gal21	492,{}
moro_vol.gat,153,86,1	script	精鋭部隊#gal22	492,{}
moro_vol.gat,156,86,1	script	精鋭部隊#gal23	492,{}
moro_vol.gat,150,83,1	script	精鋭部隊#gal24	450,{}
moro_vol.gat,153,83,1	script	精鋭部隊#gal25	450,{}
moro_vol.gat,156,83,1	script	精鋭部隊#gal26	450,{}

moro_cav.gat,34,65,5	script	バンズ#morocav	49,{
	if(!(checkquest(116510) & 0x8)) {
		mes "[バンズ]";
		mes "君、もしかして、";
		mes "ここにいるという事は……";
		mes "モロク討伐へ向かう冒険者だな！";
		mes "私はモロク討伐へ向かう冒険者の";
		mes "支援をしているんだ。";
		next;
		mes "[バンズ]";
		mes "モロクは非常に強敵だ。";
		mes "力の無いものは";
		mes "近づくことさえ叶わない。";
		mes "残念ながら……";
		mes "私も近づけない者の1人だ。";
		next;
		mes "[バンズ]";
		mes "だから私はここでこうして";
		mes "^ff0000勇者の指輪^000000を";
		mes "モロク討伐へ向かう冒険者達に";
		mes "渡している。";
		mes "この指輪は一見、何の能力もない。";
		mes "しかし！";
		next;
		mes "[バンズ]";
		mes "私には特技があってね。";
		mes "私が力を施すことでこの指輪の";
		mes "四つの眠っている能力を引き出し";
		mes "大きな力を得る事ができる。";
		next;
		mes "[バンズ]";
		mes "勇者の指輪が持っている";
		mes "能力を引き出せば、";
		mes "モロク討伐の大きな助けに";
		mes "なるだろう。";
		mes "どうだ、受け取っていくか？";
		next;
		if(select("指輪を受け取る","指輪を受け取らない") == 2) {
			mes "[バンズ]";
			mes "そうか。";
			mes "欲しくなったら来てくれ。";
			close;
		}
		mes "[バンズ]";
		mes "ほら。これだ。";
		mes "この指輪の力が";
		mes "きっと君の役に立つはずだ。";
		setquest 116510;
		compquest 116510;
		getitem 2981,1;
		next;
		mes "[バンズ]";
		mes "もしも2つ目以降を欲しい場合は";
		mes "^ff0000勇者の証^000000を^0000ff30^000000個";
		mes "持ってきてくれ。";
		mes "交換しよう。";
		close;
	}
	mes "[バンズ]";
	mes "勇者の指輪の力を最大限に";
	mes "引き出すことができれば、";
	mes "今後の戦いで大いに役に立つだろう。";
	mes "今日は何の要件だ？";
	next;
	switch(select("指輪について聞く","指輪を交換する","エンチャントを行う","エンチャントを初期化する","何もしない")) {
	case 1:
		mes "[バンズ]";
		mes "この勇者の指輪は";
		mes "一見何の能力もない。";
		next;
		mes "[バンズ]";
		mes "しかし！";
		mes "私が力を施すことでこの指輪の";
		mes "四つの眠っている能力を引き出し";
		mes "大きな力を得る事ができる。";
		next;
		mes "[バンズ]";
		mes "勇者の指輪が持っている";
		mes "能力を引き出せば、";
		mes "モロク討伐の大きな助けに";
		mes "なるだろう。";
		close;
	case 2:
		mes "[バンズ]";
		mes "勇者の指輪は";
		mes "勇者の証30個で交換可能だ。";
		mes "交換するかい？";
		next;
		if(select("交換しない","交換する") == 1) {
			mes "[バンズ]";
			mes "そうか。";
			close;
		}
		if(countitem(6684) < 30) {
			mes "[バンズ]";
			mes "^006400勇者の証^00000030個を";
			mes "持っていないぞ？";
			mes "それじゃあ、交換することは";
			mes "できないな。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[バンズ]";
			mes "アイテムの種類数が多いぞ。";
			mes "少し荷物を減らしてこい。";
			close;
		}
		delitem 6684,30;
		getitem 2981,1;
		mes "[バンズ]";
		mes "^006400勇者の証^00000030個と";
		mes "^006400勇者の指輪^0000001個を";
		mes "交換したぜ。";
		close;
	case 3:
		if(checkitemblank() == 0) {
			mes "[バンズ]";
			mes "持ち物が多すぎるようだ。";
			mes "荷物に空きを作ってきてくれ。";
			close;
		}
		mes "[バンズ]";
		mes "エンチャントするには勇者の指輪を";
		mes "装備している必要がある。";
		mes "どっちに装備している指輪を";
		mes "エンチャントするんだ？";
		next;
		switch(select(
				(getequipid(7)!=0? "^nItemID^" +getequipid(7): "アクセサリー[1]‐装備していない"),
				(getequipid(8)!=0? "^nItemID^" +getequipid(8): "アクセサリー[2]‐装備していない"))
		) {
		case 1: set '@itemid,getequipid(7); set '@menu,7; break;
		case 2: set '@itemid,getequipid(8); set '@menu,8; break;
		}
		if('@itemid == 0) {
			mes "[バンズ]";
			mes "エンチャントをしたい場合は、";
			mes "勇者の指輪を装備しておいてくれよ。";
			close;
		}
		if('@itemid != 2981) {
			mes "[バンズ]";
			mes "勇者の指輪を装備してくれ。";
			mes "他のアクセサリーは扱えない。";
			close;
		}
		if(getequipcardid('@menu,0)) {
			mes "[バンズ]";
			mes "既にエンチャントされている";
			mes "勇者の指輪は、初期化をすれば";
			mes "再エンチャントが可能だ。";
			close;
		}
		setarray '@table1$,"Str","Agi","Vit","Int","Dex","Luk";
		setarray '@table2$,"Atk","Matk";
		setarray '@table3$,"MaxHP","MaxSP";
		setarray '@table4$,"Def","Mdef";
		mes "[バンズ]";
		mes "一番目のスロットには";
		mes "どんな能力を付与するんだ？";
		next;
		set '@socket1,select("Str","Agi","Vit","Int","Dex","Luk")-1;
		switch('@socket1) {
		case 0: setarray '@bonus1, 4700, 4701, 4702, 4703, 4704; break;
		case 1: setarray '@bonus1, 4730, 4731, 4732, 4733, 4734; break;
		case 2: setarray '@bonus1, 4740, 4741, 4742, 4743, 4744; break;
		case 3: setarray '@bonus1, 4710, 4711, 4712, 4713, 4714; break;
		case 4: setarray '@bonus1, 4720, 4721, 4722, 4723, 4724; break;
		case 5: setarray '@bonus1, 4750, 4751, 4752, 4753, 4754; break;
		}
		mes "[バンズ]";
		mes "二番目のスロットには";
		mes "どんな能力を付与するんだ？";
		next;
		set '@socket2,select("Atk","Matk")-1;
		switch('@socket2) {
		case 0: setarray '@bonus2, 4882, 4766, 4767, 4894, 4895; break;
		case 1: setarray '@bonus2, 4883, 4896, 4897, 4898, 4899; break;
		}
		mes "[バンズ]";
		mes "三番目のスロットには";
		mes "どんな能力を付与するんだ？";
		next;
		set '@socket3,select("MaxHP","MaxSP")-1;
		switch('@socket3) {
		case 0: setarray '@bonus3, 4861, 4862, 4867, 4868, 4900; break;
		case 1: setarray '@bonus3, 4800, 4870, 4871, 4801, 4802; break;
		}
		mes "[バンズ]";
		mes "四番目のスロットには";
		mes "どんな能力を付与するんだ？";
		next;
		set '@socket4,select("Def","Mdef")-1;
		switch('@socket4) {
		case 0: setarray '@bonus4, 4791, 4792, 4793, 4794, 4893; break;
		case 1: setarray '@bonus4, 4890, 4786, 4891, 4787, 4892; break;
		}
		mes "[バンズ]";
		mes "一番目のスロットは" +'@table1$['@socket1]+ "、";
		mes "二番目のスロットは" +'@table2$['@socket2]+ "、";
		mes "三番目のスロットは" +'@table3$['@socket3]+ "、";
		mes "四番目のスロットは" +'@table4$['@socket4]+ "、";
		mes "本当にいいんだな？";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[バンズ]";
			mes "ちゃんと決めてから";
			mes "もう一度話かけてくれ！";
			close;
		}
		mes "[バンズ]";
		mes "よし、エンチャントを始める！";
		mes "どんな結果が出るかは";
		mes "私にもわからない。幸運を祈ろう！";
		next;
		mes "[バンズ]";
		mes "ふうう……！";
		next;
		misceffect 182,"";
		misceffect 205,"";
		misceffect 102,"";
		misceffect 104,"";
		set '@card[0],'@bonus1[rand(getarraysize('@bonus1))];
		set '@card[1],'@bonus2[rand(getarraysize('@bonus2))];
		set '@card[2],'@bonus3[rand(getarraysize('@bonus3))];
		set '@card[3],'@bonus4[rand(getarraysize('@bonus4))];
		delequip '@menu;
		getitem2 2981,1,1,0,0,'@card[0],'@card[1],'@card[2],'@card[3];
		mes "[バンズ]";
		mes "エンチャントが完了したぞ！";
		close;
	case 4:
		mes "[バンズ]";
		mes "勇者の指輪に付与された";
		mes "エンチャントを初期化するには";
		mes "^FF0000勇者の証3個^000000が必要になる。";
		next;
		mes "[バンズ]";
		mes "だが、黄色い種、赤い花の";
		mes "調査を完了してきた奴には";
		mes "^ff0000無料^000000で初期化をしてやろう。";
		mes "両方の調査を完了すれば2回無料だ。";
		next;
		mes "^ff0000‐無料の初期化は繰り返し可能です。";
		mes "　但し回数のストックは出来ません。‐^000000";
		next;
		if(!checkquest(116513) && !checkquest(116514) && countitem(6684) < 3) {
			mes "[バンズ]";
			mes "残念だが君は勇者の証が";
			mes "足りないようだな。";
			close;
		}
		mes "[バンズ]";
		mes "初期化するには勇者の指輪を";
		mes "装備している必要がある。";
		mes "どっちに装備している指輪を";
		mes "初期化するんだ？";
		next;
		switch(select(
				(getequipid(7)!=0? "^nItemID^" +getequipid(7): "アクセサリー[1]‐装備していない"),
				(getequipid(8)!=0? "^nItemID^" +getequipid(8): "アクセサリー[2]‐装備していない"))
		) {
		case 1: set '@itemid,getequipid(7); set '@menu,7; set '@str$,"左"; break;
		case 2: set '@itemid,getequipid(8); set '@menu,8; set '@str$,"右"; break;
		}
		if('@itemid == 0) {
			mes "[バンズ]";
			mes "エンチャントをしたい場合は、";
			mes "勇者の指輪を装備しておいてくれよ。";
			close;
		}
		if('@itemid != 2981) {
			mes "[バンズ]";
			mes "勇者の指輪を装備してくれ。";
			mes "他のアクセサリーは扱えない。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[バンズ]";
			mes "持ち物が多すぎるようだ。";
			mes "荷物に空きを作ってきてくれ。";
			close;
		}
		set '@card1,getequipcardid('@menu,0);
		if('@card1 == 0) {
			mes "[バンズ]";
			mes "それはすでに初期化されている";
			mes "指輪じゃないか？";
			close;
		}
		mes "[バンズ]";
		mes '@str$+ "に装備した勇者の指輪だな。";
		mes "初期化をした場合、失われた能力を";
		mes "戻す事は不可能だぞ。";
		mes "^ff0000勇者の指輪を2つ装備している場合は";
		mes "特に気を付けてくれ。^000000";
		mes "それでもやるのか？";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[バンズ]";
			mes "そうか、まあ良く考えるんだな。";
			close;
		}
		if(checkquest(116513) || checkquest(116514)) {
			mes "[バンズ]";
			mes "おや、君は無料で初期化を";
			mes "することができるようだね。";
			while(1) {
				mes "どちらを使用して、";
				mes "初期化するんだい？";
				if(checkquest(116513))
					set '@str1$,"黄色い種完了";
				else
					set '@str1$,"黄色い種完了(未達成)";
				if(checkquest(116514))
					set '@str2$,"赤い花完了";
				else
					set '@str2$,"赤い花完了(未達成)";
				next;
				switch(select('@str1$,'@str2$)) {
				case 1:
					if(!checkquest(116513)) {
						mes "[バンズ]";
						mes "黄色い種の調査は";
						mes "完了していないようだぞ。";
						next;
						mes "[バンズ]";
						continue;
					}
					set '@type,116513;
					break;
				case 2:
					if(!checkquest(116514)) {
						mes "[バンズ]";
						mes "赤い花の調査は";
						mes "完了していないようだぞ。";
						next;
						mes "[バンズ]";
						continue;
					}
					set '@type,116514;
					break;
				}
				break;
			}
			mes "[バンズ]";
			mes "わかった、では今回は^ff0000無料^000000で";
			mes "初期化をしよう。";
			mes "少し待ってくれ。";
			next;
			setquest '@type;
			delquest '@type;
		}
		else {
			mes "[バンズ]";
			mes "わかった、君の決定を尊重しよう。";
			mes "それでは少し待ってくれ。";
			next;
			delitem 6684,3;
		}
		misceffect 182,"";
		misceffect 205,"";
		misceffect 338,"";
		delequip '@menu;
		getitem 2981,1;
		mes "[バンズ]";
		mes "初期化が完了した。";
		mes "エンチャントが必要なら";
		mes "また話かけてくれ。";
		close;
	case 5:
		mes "[バンズ]";
		mes "勇者の指輪を持ってきたら";
		mes "エンチャントをしてやるぞ。";
		close;
	}
OnInit:
	waitingroom "勇者の指輪",0;
	end;
}

moro_cav.gat,32,73,5	script	チェイコ#1	482,{
	mes "[チェイコ]";
	mes "^ff0000魔神エンチャント^000000って";
	mes "知ってる？";
	mes "武器、防具のどのカードスロットにも";
	mes "挿す事が可能な不思議なアイテムよ。";
	mes "私はそれに関する調査をしているの。";
	mes "何か用かしら？";
	next;
	switch(select("アップグレードを依頼する","説明を聞く","話をやめる")) {
	case 1:
		mes "[チェイコ]";
		mes "アップグレードの挑戦ね。";
		mes "わかったわ。";
		mes "挑戦は失敗する場合もあるわよ。";
		mes "^ff0000失敗した場合、利用したアイテムは";
		mes "全て無くなる^000000けどそれでもいい？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[チェイコ]";
			mes "挑戦したい時にまた来て。";
			close;
		}
		break;
	case 2:
		mes "[チェイコ]";
		mes "今のところ、魔神エンチャントには";
		mes "各能力6つの種類と、それぞれ";
		mes "3段階のグレードがある事が";
		mes "わかっているわ。";
		next;
		mes "[チェイコ]";
		mes "たとえば^ff0000魔神の腕力2^000000と言えば";
		mes "力(Str)に関するアイテムで";
		mes "グレードとしては2段階目という事ね。";
		next;
		mes "[チェイコ]";
		mes "ここからが大事な話よ。";
		mes "この魔神エンチャント、";
		mes "^ff0000同じグレードで同じ種類のアイテムを";
		mes "複数使ってアップグレードが出来るの。^000000";
		mes "研究の成果よ。　すごくない？";
		next;
		mes "[チェイコ]";
		mes "もちろん、失敗する場合もあるわ。";
		mes "失敗した場合、^ff0000利用したアイテムは";
		mes "全て消失してしまう。^000000";
		mes "だけど、第3段階の魔神エンチャントは";
		mes "凄く希少だし試す価値はあると思うわ。";
		next;
		mes "[チェイコ]";
		mes "ただ……アップグレードは";
		mes "同じ種類・段階のものでないと";
		mes "出来ないみたい。";
		mes "集めるアイテムの種類が違ったり、";
		mes "違う種類へのアップグレードは";
		mes "出来なかったわ。";
		next;
		mes "[チェイコ]";
		mes "説明はここまでよ。";
		mes "もしも挑戦したい場合は";
		mes "次の物を用意してここにきて。";
		mes "私の研究が少しでもモロク討伐の";
		mes "助けになれば幸いだわ。";
		next;
		mes "[アップグレード]";
		mes "第1段階　→　第2段階";
		mes "同じ種類の第1段階の魔神エンチャント";
		mes "^ff00003個^000000";
		next;
		mes "[アップグレード]";
		mes "第2段階　→　第3段階";
		mes "同じ種類の第2段階の魔神エンチャント";
		mes "^ff00005個^000000";
		close;
	case 3:
		mes "[チェイコ]";
		mes "魔神エンチャントに関する";
		mes "話があったらいつでも来て。";
		close;
	}
	while(1) {
		mes "[チェイコ]";
		mes "それじゃあアップグレードしたい";
		mes "アイテムの種類を教えてくれる？";
		next;
		set '@menu,select("魔神の腕力(Str)","魔神の迅速(Agi)","魔神の体力(Vit)","魔神の知力(Int)","魔神の集中(Dex)","魔神の幸運(Luk)","やめる")-1;
		switch('@menu) {
		case 0:
			set '@upstate$,"魔神の腕力";
			set '@need,4908;
			break;
		case 1:
			set '@upstate$,"魔神の迅速";
			set '@need,4914;
			break;
		case 2:
			set '@upstate$,"魔神の体力";
			set '@need,4917;
			break;
		case 3:
			set '@upstate$,"魔神の知力";
			set '@need,4911;
			break;
		case 4:
			set '@upstate$,"魔神の集中";
			set '@need,4920;
			break;
		case 5:
			set '@upstate$,"魔神の幸運";
			set '@need,4923;
			break;
		case 6:
			mes "[チェイコ]";
			mes "挑戦したい時にまた来て。";
			close;
		}
		mes "[チェイコ]";
		mes "どの段階のアップグレードに";
		mes "挑戦する？";
		next;
		switch(select("第1段階　→　第2段階","第2段階　→　第3段階","やめる")) {
		case 1:
			set '@upgrade$,"第1段階　→　第2段階";
			set '@amount,3;
			set '@rate,6500;
			break;
		case 2:
			set '@upgrade$,"第2段階　→　第3段階";
			set '@need,'@need+1;
			set '@amount,5;
			set '@rate,2500;
			break;
		case 3:
			mes "[チェイコ]";
			mes "挑戦したい時にまた来て。";
			close;
		}
		mes "[チェイコ]";
		mes "あなたが選んだのは……";
		mes '@upstate$;
		mes '@upgrade$;
		mes "……これでいいかしら？";
		next;
		switch(select("はい","もう一度選びなおす","やっぱりやめる")) {
		case 1:
			break;
		case 2:
			continue;
		case 3:
			mes "[チェイコ]";
			mes "挑戦したくなったら来て。";
			close;
		}
		break;
	}
	if(countitem('@need) < '@amount) {
		mes "[チェイコ]";
		mes getitemname('@need)+ "が足りないわ。";
		mes '@amount+ "個、必要よ。";
		close;
	}
	mes "[チェイコ]";
	mes "それじゃあ行くわ。";
	mes "うまくいくよう祈ってね。";
	next;
	mes "[チェイコ]";
	mes "ちぇい……チェイチェイ！";
	mes "　";
	mes "‐目を閉じて何か唱え始めた‐";
	misceffect 72;
	next;
	mes "[チェイコ]";
	mes "ちょいやー!!!";
	misceffect 8;
	next;
	if(rand(10000) < '@rate) {
		misceffect 182;
		mes "[チェイコ]";
		mes "や……やったー！　成功した！";
		mes "ね？　すごいでしょ。";
		mes "さぁ、これがアイテムよ。";
		mes "また挑戦したかったら来てね。";
		delitem '@need,'@amount;
		getitem '@need+1,1;
		close;
	}
	else {
		misceffect 183;
		mes "[チェイコ]";
		mes "くっ、悔しい……。";
		mes "失敗した……！";
		mes "ごめんなさい。";
		mes "次こそは成功させるから";
		mes "また持ってきてください……。";
		delitem '@need,'@amount;
		close;
	}
OnInit:
	waitingroom "魔神エンチャント",0;
	end;
}

moro_cav.gat,36,57,5	script	先遣隊兵士#moro	707,{
	if(BIOS_1QUE == 0 || MORS_1QUE == 0) {
		mes "[兵士]";
		mes "私はモロク討伐に向かう";
		mes "冒険者達から";
		mes "色々な情報を収集しています。";
		next;
		mes "[兵士]";
		mes "^ff0000黄色い種^000000と";
		mes "^ff0000赤い花^000000の";
		mes "調査をしてきてください。";
		mes "両方の調査結果を報告してくれたら";
		mes "お礼に経験値をお渡しします。";
		next;
		mes "[兵士]";
		mes "少しでも多くの情報が欲しいです。";
		mes "何度報告していただいても構いません。";
		mes "ご協力よろしくお願いします。";
		mes "　";
		mes "‐^ff0000繰り返し可能な依頼です。^000000‐";
		close;
	}
	set '@count,BIOS_1QUE + MORS_1QUE;
	mes "[兵士]";
	mes "おお、^ff0000黄色い種^000000と^ff0000赤い花^000000の";
	mes "調査が終わりましたか。";
	mes "延べ^ff0000" +'@count+ "人^000000で";
	mes "調査してくれたのですね。";
	mes "ありがとうございます。";
	mes "調査内容を報告してもらえますか？";
	next;
	if(select("報告する","まだ報告しない") == 2) {
		mes "[兵士]";
		mes "調査内容がまとまったら";
		mes "声をかけてください。";
		close;
	}
	mes "[兵士]";
	mes "なるほど、中ではそんなことが……。";
	mes "報告ありがとうございます。";
	next;
	mes "[兵士]";
	mes "まだ他に何かあるかもしれません。";
	mes "調査報告は引き続き受け付けますので、";
	mes "^ff0000黄色い種^000000と^ff0000赤い花^000000の";
	mes "調査を終えたら私に報告してください。";
	set '@base,1250000 * '@count;
	set '@job,500000 * '@count;
	set BIOS_1QUE,0;
	set MORS_1QUE,0;
	getexp '@base,0,1;
	getexp 0,'@job,0;
	close;
OnInit:
	waitingroom "ビオスの島・モルスの洞窟報酬",0;
	end;
}

moro_vol.gat,0,0,0	script	moro_vol_mon	-1,{
OnTimer10000:
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob1);
	if('@x < 292-15 || '@x > 292+15 || '@y < 201-15 || '@y > 201+15) {
		set 'mob1call,1;
		unittalk 'mob1,"あの方の命令だ。持ち場へ戻らなければ……。";
	}
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob2);
	if('@x < 277-15 || '@x > 277+15 || '@y < 238-15 || '@y > 238+15) {
		set 'mob2call,1;
		unittalk 'mob2,"あの方の命令だ。持ち場へ戻らなければ……。";
	}
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob3);
	if('@x < 216-15 || '@x > 216+15 || '@y < 245-15 || '@y > 245+15) {
		set 'mob3call,1;
		unittalk 'mob3,"あの方の命令だ。持ち場へ戻らなければ……。";
	}
	end;
OnTimer15000:
	if('mob1dead > 0) {
		set 'mob1dead,'mob1dead - 1;
		if('mob1dead <= 0) {
			set 'mob1,callmonster("moro_vol.gat",rand(288,296),rand(197,205),"炎火のモロクの現身",3039,"moro_vol_mon::OnKilled1");
		}
	}
	else if('mob1call > 0) {
		set 'mob1call,0;
		set '@mob1hp,getmobhp('mob1);
		set '@dummy,removemonster('mob1);
		set 'mob1,callmonster("moro_vol.gat",rand(288,296),rand(197,205),"炎火のモロクの現身",3039,"moro_vol_mon::OnKilled1");
		setmobhp 'mob1,'@mob1hp;
	}
	if('mob2dead > 0) {
		set 'mob2dead,'mob2dead - 1;
		if('mob2dead <= 0) {
			set 'mob2,callmonster("moro_vol.gat",rand(273,281),rand(234,242),"歪んだモロクの現身",3040,"moro_vol_mon::OnKilled2");
		}
	}
	else if('mob2call > 0) {
		set 'mob2call,0;
		set '@mob2hp,getmobhp('mob2);
		set '@dummy,removemonster('mob2);
		set 'mob2,callmonster("moro_vol.gat",rand(273,281),rand(234,242),"歪んだモロクの現身",3040,"moro_vol_mon::OnKilled2");
		setmobhp 'mob2,'@mob2hp;
	}
	if('mob3dead > 0) {
		set 'mob3dead,'mob3dead - 1;
		if('mob3dead <= 0) {
			set 'mob3,callmonster("moro_vol.gat",rand(212,220),rand(241,249),"冷気のモロクの現身",3041,"moro_vol_mon::OnKilled3");
		}
	}
	else if('mob3call > 0) {
		set 'mob3call,0;
		set '@mob3hp,getmobhp('mob3);
		set '@dummy,removemonster('mob3);
		set 'mob3,callmonster("moro_vol.gat",rand(212,220),rand(241,249),"冷気のモロクの現身",3041,"moro_vol_mon::OnKilled3");
		setmobhp 'mob3,'@mob3hp;
	}
	initnpctimer;
	end;
OnKilled1:
	set 'mob1call,0;
	set 'mob1dead,6;
	end;
OnKilled2:
	set 'mob2call,0;
	set 'mob2dead,6;
	end;
OnKilled3:
	set 'mob3call,0;
	set 'mob3dead,6;
	end;
OnInit:
	initnpctimer;
	set 'mob1,callmonster("moro_vol.gat",rand(288,296),rand(197,205),"炎火のモロクの現身",3039,"moro_vol_mon::OnKilled1");
	set 'mob2,callmonster("moro_vol.gat",rand(273,281),rand(234,242),"歪んだモロクの現身",3040,"moro_vol_mon::OnKilled2");
	set 'mob3,callmonster("moro_vol.gat",rand(212,220),rand(241,249),"冷気のモロクの現身",3041,"moro_vol_mon::OnKilled3");
	end;
}

//============================================================
// エクラージュ追加NPC
//------------------------------------------------------------
ecl_in01.gat,38,98,1	script	次元移動機#143_1	10007,{
	mes "[エクラージュガード]";
	mes "最近発見された魔王の隠れ家、";
	mes "^FF0000フレイムヴァレー^000000に";
	if(FVOL_1QUE < 9) {
		mes "移動できる次元移動機です。";
		mes "が、現在調整中ですので";
		mes "利用することができません。";
		next;
		mes "‐この次元移動機を利用するには";
		mes "　フレイムヴァレーへの道クエストを";
		mes "　途中まで進める必要があります‐";
		close;
	}
	mes "繋がっている次元移動機です。";
	mes "利用しますか？";
	next;
	if(select("フレイムヴァレーに移動","やめる") == 2) {
		mes "‐移動機を使うのをやめた‐";
		close;
	}
	mes "‐次元移動機を使って";
	mes "　フレイムヴァレーに移動します‐";
	close2;
	warp "moro_vol.gat",91,102;
	end;
}

ecl_in01.gat,35,89,6	script	魔学者アマンディー#143_	620,{
	mes "[アマンディー]";
	mes "次元の狭間というものが";
	mes "この世界に大きな打撃を";
	mes "与えなければいいのですが。";
	mes "それにしても流石エイヴァントですね。";
	next;
	mes "[レモニー]";
	mes "……私はあの者が嫌いだ。";
	next;
	mes "[アマンディー]";
	mes "それでも実力はずば抜けていると";
	mes "思いません？";
	next;
	mes "[レモニー]";
	mes "次元移動機なんてものを";
	mes "簡単に作ってしまうとはな。";
	mes "実力は認めるが……。";
	mes "ところで、あのエイヴァントが";
	mes "突然マヨルの力になるなんて、";
	mes "どういう風の吹き回しなんだ？";
	next;
	mes "[アマンディー]";
	mes "それとなく聞いてみたら";
	mes "罪滅ぼしとかなんとか……。";
	mes "マヨルの出生に関する";
	mes "問題ではないかと思いますが、";
	mes "詳しい事情はわかりませんね。";
	next;
	mes "[アマンディー]";
	mes "詳しく聞こうとしたら、";
	mes "俺のことをバカにして";
	mes "はぐらかされました。";
	mes "ああ……どうしてあんなのが";
	mes "魔学の天才なんだ……。";
	next;
	mes "[レモニー]";
	mes "……悔しいと思うなら勉強しろ。";
	mes "勉強は自分の為になる……。";
	close;
}

ecl_in01.gat,37,90,3	script	魔学者レモニー#143_3	611,{
	mes "[レモニー]";
	mes "今回の月刊心理の扉は読んだか？";
	mes "エイヴァントが新しく作った";
	mes "次元移動機の原理が載っていたらしい。";
	next;
	mes "[アマンディー]";
	mes "読みましたよ。";
	mes "基礎原理だけ掲載されていました。";
	mes "正直に言うと見ても";
	mes "イマイチ分からなかったです。";
	next;
	mes "[レモニー]";
	mes "ふむ……";
	mes "エイヴァントは今回の仕事をきっかけに";
	mes "大々的に研究活動を";
	mes "始めようとしているのかもしれないな。";
	next;
	mes "[レモニー]";
	mes "ん？　人間じゃないか？";
	mes "私達の話を盗み聞きしたのか？";
	mes "まあ、別に良いが……";
	next;
	mes "[レモニー]";
	mes "お前もあそこに行くのか？";
	mes "最近、次元の狭間を作った張本人である";
	mes "魔王の隠れ家を見つけたと";
	mes "みんな騒いでいるぞ。";
	next;
	mes "[レモニー]";
	mes "気になるならお前も";
	mes "あの移動機を使ってみるといい。";
	mes "中々よいものが見られるから。";
	mes "もちろん命まで保証はできないけどね。";
	mes "きゃはははは！";
	next;
	mes "[アマンディー]";
	mes "レモニー……";
	mes "君はその性格なんとかしないと。";
	mes "はああ……。";
	close;
}

ecl_in01.gat,44,99,1	script	ラフィネ兵士#143_4	461,{
	mes "[ラフィネ兵士]";
	mes "……緊張してきましたね。";
	close;
OnTalk1:
	unittalk "おー！";
	end;
OnTalk2:
	unittalk "……";
	end;
}

ecl_in01.gat,46,99,1	script	ラフィネ兵士#143_5	461,{
	mes "[ラフィネ兵士]";
	mes "無事に戻って来られるかな。";
	close;
OnTalk1:
	unittalk "おー！";
	end;
OnTalk2:
	unittalk "……あ……";
	end;
}

ecl_in01.gat,48,99,1	script	ラフィネ兵士#143_6	461,{
	mes "[ラフィネ兵士]";
	mes "ふむ……。";
	close;
OnTalk1:
	unittalk "おー！";
	end;
OnTalk2:
	unittalk "……";
	end;
}

ecl_in01.gat,44,97,1	script	ラフィネ兵士#143_7	462,{
	mes "[ラフィネ兵士]";
	mes "静かに。";
	close;
OnTalk1:
	unittalk "えっ！";
	end;
OnTalk2:
	unittalk "えいえいお～";
	end;
}

ecl_in01.gat,46,97,1	script	ラフィネ兵士#143_8	462,{
	mes "[ラフィネ兵士]";
	mes "やっと私が優れていることを";
	mes "お見せするチャンスが来たか。";
	close;
OnTalk1:
	unittalk "おー！";
	end;
OnTalk2:
	unittalk "……";
	end;
}

ecl_in01.gat,48,97,1	script	ラフィネ兵士#143_9	462,{
	mes "[ラフィネ兵士]";
	mes "私がどうして兵士に志願したか";
	mes "わかりますか？";
	mes "頭が悪いと体を使うしかないんです。";
	mes "心理の扉に入るのは";
	mes "どうしてあんなに難しいんだ……。";
	close;
OnTalk1:
	unittalk "おー！";
	end;
OnTalk2:
	unittalk "……";
	end;
}

ecl_in01.gat,46,102,6	script	指揮官ラフィネ#143_10	447,5,5,{
	mes "[指揮官ラフィネ]";
	mes "闇の種は発見したら";
	mes "消してしまったほうがいいです。";
	mes "たとえあなた達のミッドガルド大陸から";
	mes "飛んで来た異変だとしても……。";
	next;
	mes "[指揮官ラフィネ]";
	mes "この次元と世界樹に影響を与える";
	mes "悪として判断されれば、当たり前ですが";
	mes "私達ラフィネは悪の根絶の為に戦います。";
	close;
OnTouch:
	if(!getnpctimer(1))
		initnpctimer;
	end;
OnTimer3000:
	unittalk "指揮官 : 諸君！　いよいよ我々が訓練の成果を見せる時が来た！";
	end;
OnTimer5000:
	donpcevent "ラフィネ兵士#143_4::OnTalk1";
	donpcevent "ラフィネ兵士#143_5::OnTalk1";
	donpcevent "ラフィネ兵士#143_6::OnTalk1";
	donpcevent "ラフィネ兵士#143_7::OnTalk1";
	donpcevent "ラフィネ兵士#143_8::OnTalk1";
	donpcevent "ラフィネ兵士#143_9::OnTalk1";
	end;
OnTimer8000:
	unittalk "指揮官 : なんだ？　途中に変な声が混ざっていたぞ？";
	end;
OnTimer11000:
	unittalk "指揮官 : 前線基地スプレンディッドの戦友達に引けをとらない姿を見せなければならない。";
	end;
OnTimer14000:
	unittalk "指揮官 : 気をしっかり引き締めろ！　私たちは魔王に会いに行くんだ!!";
	end;
OnTimer16000:
	donpcevent "ラフィネ兵士#143_7::OnTalk2";
	end;
OnTimer18000:
	donpcevent "ラフィネ兵士#143_4::OnTalk2";
	donpcevent "ラフィネ兵士#143_5::OnTalk2";
	donpcevent "ラフィネ兵士#143_6::OnTalk2";
	donpcevent "ラフィネ兵士#143_8::OnTalk2";
	//donpcevent "ラフィネ兵士#143_9::OnTalk2";
	end;
OnTimer21000:
	unittalk "指揮官 : あれ……なぜだ？　どうして急におとなしくなってしまうんだ……？";
	end;
OnTimer24000:
	stopnpctimer;
	end;
}

ecl_in01.gat,40,96,3	script	エクラージュガード	447,{
	mes "[エクラージュガード]";
	mes "なんの用ですか？";
	next;
	switch(select("この移動機は何ですか？","どうして人たちが集まっているんですか？","魔王の隠れ家？","頑張って下さい")) {
	case 1:
		mes "[エクラージュガード]";
		mes "……魔王モロクが隠れていることが";
		mes "明らかになった地域に移動できる";
		mes "次元移動機です。";
		mes "次元の狭間と繋がっているんですが、";
		mes "研究の末に正確な場所まで";
		mes "行けるようになったのです。";
		next;
		mes "[エクラージュガード]";
		mes "既に多くの兵士たちが";
		mes "魔王の隠れ家に行きました。";
		mes "魔王が存在する空間は";
		mes "世界樹の脅威になるかも知れないので、";
		mes "私も遠征に参加する予定です。";
		close;
	case 2:
		mes "[エクラージュガード]";
		mes "ミッドガルド大陸から逃げた";
		mes "魔王モロクの隠れ家を";
		mes "探し出したからです。";
		mes "魔王を……";
		mes "ここから追い出さなければなりません。";
		mes "魔界から永遠に戻って来れないよう。";
		next;
		mes "[エクラージュガード]";
		mes "あなたも魔王を退治する為に";
		mes "遠征に参加するのであれば、";
		mes "ここにある次元移動機を利用して下さい。";
		mes "遠征団のいる場所に";
		mes "移動することができます。";
		close;
	case 3:
		mes "[エクラージュガード]";
		mes "次元の狭間は知っていますよね？";
		mes "最近、次元の狭間の内部が";
		mes "次元の通路になっていることが";
		mes "明らかになりました。";
		mes "それを利用して、次元の狭間内部を";
		mes "探検できるようになったのです。";
		next;
		mes "[エクラージュガード]";
		mes "もともと次元の狭間は";
		mes "魔王モロクが自身を隠すため";
		mes "逃げる際中に作ったものなので、";
		mes "狭間を調査していればいつかは";
		mes "魔王モロクを発見できるだろうと";
		mes "考えていました。";
		next;
		mes "[エクラージュガード]";
		mes "そしてついに魔王の隠れ家と";
		mes "推測される地域を見つけ、";
		mes "^FF0000フレイムヴァレー^000000と名付けました。";
		mes "……魔王の痕跡と……魔族たち……";
		mes "この中央にある巨大な坂を中心に";
		mes "現れています。";
		next;
		mes "[エクラージュガード]";
		mes "詳しい内容はたぶん現場の方が";
		mes "知っているでしょう。";
		mes "次元移動機を使い、移動してください。";
		close;
	case 4:
		mes "[エクラージュガード]";
		mes "あなたにも";
		mes "世界樹の加護がありますように。";
		close;
	}
}

ecl_in01.gat,47,106,6	script	カルデュイ#14301	624,{
	end;
OnHour01: OnHour03: OnHour05:
OnHour07: OnHour09: OnHour11:
OnHour13: OnHour15: OnHour17:
OnHour19: OnHour21: OnHour23:
	initnpctimer;
	hideoffnpc "カルデュイ#14301";
	announce "カルデュイ : エクラージュのすべての民よ。",0x9,0x00ff00;
	end;
OnTimer3000:
	announce "カルデュイ : 世界樹イグドラシルの守護者としてオーブの魔力を解放して力を捧げる。",0x9,0x00ff00;
	end;
OnTimer6000:
	hideoffnpc "#ecl_orb_buff";
	hideoffnpc "#ecl_buff_N";
	hideoffnpc "#ecl_buff_E";
	hideoffnpc "#ecl_buff_S";
	hideoffnpc "#ecl_buff_W";
	end;
OnTimer9000:
	announce "カルデュイ : イグドラシルの力で次元の狭間を乱している闇と戦ってください。",0x9,0x00ff00;
	hideonnpc "#ecl_buff_N";
	hideonnpc "#ecl_buff_E";
	hideonnpc "#ecl_buff_S";
	hideonnpc "#ecl_buff_W";
	end;
OnTimer12000:
	announce "カルデュイ : オーブの魔力はしばらく解放しておきます。",0x9,0x00ff00;
	end;
OnTimer15000:
	announce "カルデュイ : 真の平和を……",0x9,0x00ff00;
	end;
OnTimer600000:
	announce "カルデュイ : 解放していたオーブの魔力を封印します。",0x9,0x00ff00;
	end;
OnTimer603000:
	hideonnpc "#ecl_orb_buff";
	end;
OnTimer606000:
	announce "カルデュイ : 闇を追い払うまで……どうか良い夢が見れますように……。",0x9,0x00ff00;
	end;
OnTimer609000:
	stopnpctimer;
	misceffect 313,"カルデュイ#14301";
	hideonnpc "カルデュイ#14301";
	end;
}

ecl_in01.gat,48,67,0	script	#ecl_orb_buff	139,10,10,{
OnTouch:
	misceffect 313,"";
	sc_start SC_BLESSING,240000,10;
	sc_start SC_MSTR,5400000,6;
	sc_start SC_MAGI,5400000,6;
	sc_start SC_MVIT,5400000,6;
	sc_start SC_MINT,5400000,6;
	sc_start SC_MDEX,5400000,6;
	sc_start SC_MLUK,5400000,6;
	sc_start SC_ATKPOTION,5400000,24;
	sc_start SC_MATKPOTION,5400000,24;
	percentheal 100,100;
	misceffect 362,"";
	end;
}

ecl_in01.gat,48,67,0	script	オーブ#orb	844,{
	if(ECL_3QUE < 33 || FVOL_1QUE < 100) {
		mes "‐オーブの魔力が感じられる‐";
		close;
	}
	if(checkquest(116540) == 0) {
		mes "‐オーブに触れると頭の中に";
		mes "　カルデュイの声が響いてきた‐";
		next;
		mes "[カルデュイ]";
		mes strcharinfo(0)+"、";
		mes "私の声が聞こえるかい？";
		next;
		mes "[カルデュイ]";
		mes "このオーブには特別な魔力が";
		mes "込められているんだ。";
		mes "その魔力を受けた者は";
		mes "強力な力を得ることができる。";
		next;
		mes "[カルデュイ]";
		mes "本来は私が解放して";
		mes "皆に分け与えているものだが、";
		mes "このエクラージュのために";
		mes "力を尽くしてくれた君には、";
		mes "特別にこのオーブの魔力を";
		mes "自由に使えるようにしてあげよう。";
		next;
		mes "[カルデュイ]";
		mes "ただ、さすがに君一人に";
		mes "独占させるわけにはいかないからね。";
		mes "オーブの魔力を使うのは";
		mes "ほどほどにしておいてくれ。";
		next;
		mes "[カルデュイ]";
		mes "あと、たまには顔を見せて、";
		mes "私の話し相手になってくれよ。";
		mes "ふふ……";
		mes "イグドラシルの祝福が君のそばに……。";
		next;
		mes "‐オーブの魔力を受けることが";
		mes "　できるようになりました。";
		mes "　オーブの魔力は^ff000018時間に1回^000000";
		mes "　受けることができます‐";
		setquest 116540;
		compquest 116540;
		close;
	}
	if(checkquest(116541)) {
		if(checkquest(116541)&2 == 0) {
			mes "‐オーブの魔力は^ff000018時間に1回^000000";
			mes "　受けることができます‐";
			close;
		}
		delquest 116541;
	}
	mes "‐オーブの魔力は^ff000018時間に1回^000000";
	mes "　受けることができます。";
	mes "　オーブの魔力を受けますか？‐";
	next;
	if(select("受ける","受けない") == 2) {
		mes "‐あなたはオーブから離れた‐";
		close;
	}
	misceffect 313,"";
	sc_start SC_BLESSING,240000,10;
	sc_start SC_MSTR,5400000,6;
	sc_start SC_MAGI,5400000,6;
	sc_start SC_MVIT,5400000,6;
	sc_start SC_MINT,5400000,6;
	sc_start SC_MDEX,5400000,6;
	sc_start SC_MLUK,5400000,6;
	sc_start SC_ATKPOTION,5400000,24;
	sc_start SC_MATKPOTION,5400000,24;
	percentheal 100,100;
	misceffect 362,"";
	setquest 116541;
	close;
}

ecl_in01.gat,47,92,0	duplicate(#ecl_orb_buff)	#ecl_buff_N	139,10,10
ecl_in01.gat,71,67,0	duplicate(#ecl_orb_buff)	#ecl_buff_E	139,10,10
ecl_in01.gat,48,44,0	duplicate(#ecl_orb_buff)	#ecl_buff_S	139,10,10
ecl_in01.gat,23,68,0	duplicate(#ecl_orb_buff)	#ecl_buff_W	139,10,10

ecl_in01.gat,58,101,3	script	案内板	837,{
	mes "[カルデュイ様が";
	mes " お越しになられる時間]";
	mes "^FF0000  1:00 ,  3:00 ,  5:00";
	mes "  7:00 ,  9:00 , 11:00";
	mes "13:00 , 15:00 , 17:00";
	mes "19:00 , 21:00 , 23:00^000000";
	close;
}
