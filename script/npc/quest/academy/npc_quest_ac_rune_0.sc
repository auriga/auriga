//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  ルーンの依頼
//
//                                                 by Pneuma
//気になるあの子   -------------------------------------------
prontera.gat,146,232,4	script	ハルバード#AC_QUE00H01	48,{
	set '@novice, callfunc("AC_GetNovice");
	if(!AC_QUEST_ST_0) goto L_OTHER;
	switch(AC_QUEST_LV_0){
	case 0:
		goto L_QUEST01;
	case 1:
		goto L_QUEST02;
	case 2:
		goto L_QUEST03;
	case 3:
		goto L_QUEST04;
	case 4:
		goto L_OTHER;
	case 5:
		goto L_QUEST06;
	case 6:
		goto L_QUEST07;
	case 7:
		goto L_QUEST08;
	case 8:
		goto L_OTHER;
	}
	goto L_OTHER;
L_QUEST01:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "‐この人が依頼主のようだ‐";
		next;
		emotion 1;
		mes "[ハルバード]";
		mes "ん、君は？";
		next;
		select "名乗る";
		mes "[ハルバード]";
		mes "君が、僕の依頼を受けてくれた";
		mes strcharinfo(0) +"か！";
		mes "ずっと待っていたよ！";
		next;
		menu "今回の依頼内容は？",-;
		mes "[ハルバード]";
		mes "かなり重要な事だよ。";
		mes "真剣に取り組んで欲しいんだ。";
		mes "そう、今回の依頼内容は！";
		next;
		mes "[ハルバード]";
		mes "僕の恋愛の悩みを";
		mes "聞いて欲しいんだ！";
		next;
		mes "[ハルバード]";
		mes "僕には幼馴染の女の子がいるんだ。";
		mes "彼女の名前はスザンヌ。";
		mes "^FF0000彼女はイズルードに住んでいる。^000000";
		mes "僕と彼女は、誕生月も7月と同じで、";
		mes "食べ物の好みも同じ、学校も同じ。";
		mes "ずっと、仲良しにしてきたんだ。";
		next;
		emotion 40;
		mes "[ハルバード]";
		mes "でもね、最近、スザンヌが";
		mes "妙に大人っぽくなってきたんだ……";
		mes "ずっと幼馴染としてしか";
		mes "見てこなかったんだけど、";
		mes "最近、彼女を見ると、";
		mes "胸が熱くなって、苦しくなるんだ。";
		next;
		mes "[ハルバード]";
		mes "そう、僕はスザンヌを";
		mes "愛してしまったんだ！";
		mes "意識してしまって、最近スザンヌと";
		mes "話すことも出来ないんだ……";
		mes "彼女が他の男子と話しているだけで";
		mes "やきもちをやいてしまう……";
		next;
		mes "[ハルバード]";
		mes "もう、この気持ちが抑えられない！";
		mes "だから、彼女にこの気持ちを伝えようと";
		mes "思うんだ！告白しようと思うんだ！";
		mes "君は、この事についてどう思う？";
		next;
		menu "それでいいと思う",-;
		emotion 4;
		mes "[ハルバード]";
		mes "でも、告白することで";
		mes "今までの関係が壊れるんじゃないか、";
		mes "嫌われてしまうんではないか、";
		mes "と思うと、急に尻込みしちゃうんだ……";
		next;
		mes "[ハルバード]";
		mes "ううっ、";
		mes "胃が痛くなってきた……";
		mes "あいたた……";
		next;
		emotion 23;
		mes "[ハルバード]";
		mes "ぐわぁぁぁぁぁっ！";
		mes "本当に痛い！";
		mes "いてててててて！";
		next;
		menu "大丈夫？",-;
		mes "[ハルバード]";
		mes "ううっ、悪いけど……";
		mes "ミルクを持ってきてくれない？";
		mes "痛くて動けない……";
		mes "胃に優しいミルクが欲しいっ！";
		next;
	L_M_01_2_REP:
		mes "[ハルバード]";
		mes "ミルクは、";
		mes "このプロンテラの都市で";
		mes "^FF0000牛乳商人^000000が売っている！";
		mes "場所は、^FF0000南西^000000らへんだよ！";
		mes "こ、これで買ってきて～"; // 修練場撤去と同時に追加？
		mes "うはぁぁっ！";
		next;
		mes "‐ハルバードが^0000FF50zeny^000000を渡してくる‐"; //追加
		mes "　";
		mes "^FF0000【ミッション】^000000";
		mes "‐牛乳商人からミルクを買って、";
		mes "ハルバードに渡す‐";
		close2;
		viewpoint 1,74,134,1,0x0000FF;
		if(2147483647 - Zeny > 50) set Zeny, Zeny + 50;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		if(countitem(519)==0){
			emotion 23;
			mes "[ハルバード]";
			mes "ぐぁぁぁっっ…";
			mes "お願いだぁ！";
			mes "ミルクを…";
			mes "ミルクを持ってきて！";
			next;
			goto L_M_01_2_REP;
		}
		mes "[ハルバード]";
		mes "そ、それはミルクっ！";
		mes "お願い！";
		mes "それを僕にっ！";
		mes " ";
		mes "‐ミルクをハルバードに渡した‐";
		next;
		mes "[ハルバード]";
		mes "あ、ありがとう！";
		mes "では、早速！";
		next;
		mes "[ハルバード]";
		mes "ゴクゴク……";
		mes "ゴクゴク……";
		mes "ゴクゴクゴクゴクゴクゴク……";
		next;
		emotion 21;
		mes "[ハルバード]";
		mes "～～～～～～っあああ！";
		mes "うめ～～～っ！";
		mes "生き返った～！";
		next;
		mes "[ハルバード]";
		mes "本当にありがとう！";
		mes "痛みが治まったよ！";
		next;
		mes "[ハルバード]";
		mes "でも、我ながら情けない……";
		mes "ここまで、悩んでしまうとは……";
		next;
		menu "頑張れ",-;
		mes "[ハルバード]";
		mes strcharinfo(0) +"……";
		mes "ありがとう。";
		mes "少し勇気が出てきたよ。";
		next;
		mes "[ハルバード]";
		mes "何もしないで後悔するぐらいなら、";
		mes "行動をおこして、";
		mes "後悔する方がいいよね。";
		mes " ";
		mes "でももう少しだけ、彼女に告白するのに";
		mes "時間が欲しい……";
		next;
		mes "[ハルバード]";
		mes "今回は相談にのってくれて";
		mes "本当にありがとう。";
		mes "何かあったら";
		mes "また君に相談するよ！";
		next;
		delitem 519,1;
		if('@novice){
			//初心者にはイグ葉3枚
			if(!checkweight(610,3)){
				mes "重量オーバー！";
				close;
			}
			getitem 610,3;
		}
		set AC_QUEST_ST_0,99;
	L_M_01_3_REP:
		mes "^FF0000【任務達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	case 99:
		mes "[ハルバード]";
		mes "本当にありがとう！";
		mes "君は本当にいい人だね。";
		mes "また君に相談するよ！";
		next;
		goto L_M_01_3_REP;
	}
	goto L_OTHER;
L_QUEST02:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "[ハルバード]";
		mes strcharinfo(0) + "！";
		mes "待っていたよ！";
		mes "どうしても、";
		mes "君に相談したくてさ！";
		next;
		menu "どうしたの？",-;
		emotion 52;
		mes "[ハルバード]";
		mes "僕は決めたんだ。";
		mes "スザンヌに告白するよっ!";
		mes "どんな結果でも後悔しない。";
		next;
		mes "[ハルバード]";
		mes "それで、";
		mes "彼女に告白する前に";
		mes "彼女が喜ぶプレゼントを";
		mes "渡したいんだ。";
		next;
		mes "[ハルバード]";
		mes "そこで、お願いなんだ。";
		mes "彼女が欲しいものを調べて欲しいんだ。";
		mes "直接僕から聞くと、";
		mes "いかにもプレゼントを考えています、";
		mes "って感じだからさ。";
		mes "";
		next;
		menu "スザンヌに直接聞けばいい？",-;
		mes "[ハルバード]";
		mes strcharinfo(0) + "でも";
		mes "直接スザンヌに聞いてしまうと、";
		mes "怪しまれちゃうかもね。";
		mes "う～ん。";
		next;
		emotion 52;
		mes "[ハルバード]";
		mes "そうだ！そういえば、";
		mes "最近、スザンヌはイズルードの";
		mes "道具屋に通っているって聞いたぞ、";
		mes "そこの道具屋の店員なら";
		mes "彼女の好みを";
		mes "把握しているかもしれない！";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "^FF0000イズルードの道具屋^000000に";
		mes "行ってみてくれないかい？";
		next;
		menu "わかった！",-;
		mes "[ハルバード]";
		mes "ありがとう！";
		mes "頼んだよ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐イズルードの道具屋の店員に";
		mes "話しかける‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		mes "[ハルバード]";
		mes strcharinfo(0) + "！";
		mes "頼んだよ！";
		mes "^FF0000イズルードの道具屋^000000";
		mes "でスザンヌのことを聞いてみて！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐イズルードの道具屋の店員に";
		mes "話しかける‐";
		close;
	case 3:
		mes "[ハルバード]";
		mes strcharinfo(0) + "！";
		mes "どうだった？";
		mes "彼女の欲しい物って";
		mes "何かわかった？";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "どうしたの？";
		mes "暗い顔して……";
		next;
		emotion 52;
		mes "[ハルバード]";
		mes "ははぁ、わかったぞ！";
		next;
		mes "[ハルバード]";
		mes "スザンヌの欲しい物が";
		mes "高かったんでしょ？";
		mes "大丈夫、心配しないでくれよ！";
		mes "この日のために、";
		mes "お金は貯めていたんだからさ。";
		next;
		misceffect 28;
		mes "‐気の毒だが、ハルバードに";
		mes "イズルードの道具屋での話を報告した。";
		mes "ハルバードが凍っていくのがわかる‐";
		next;
		mes "[ハルバード]";
		mes "な、";
		next;
		emotion 23;
		mes "[ハルバード]";
		mes "なんだって～！";
		mes "スザンヌには、もう好きな人が";
		mes "いるっていうのかあ!!";
		mes "しかも、モロクの宝石とか、";
		mes "そんな高価なものを！";
		next;
		mes "[ハルバード]";
		mes "ひ、ひどすぎる～～っ！";
		mes "ぐはぁぁぁぁ！";
		next;
		mes "[ハルバード]";
		mes "……";
		mes strcharinfo(0) + "、";
		mes "と、とりあえず、";
		mes "調べてくれてありがとう……";
		if('@novice){
			mes "これはお礼だよ。";
		}
		mes "ちょっと、一人にさせてくれ…";
		next;
		if('@novice){
			if(!checkweight(1210,1)) {
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 1210,1;
			//ダーク
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "ごめん、";
		mes "ちょっと、一人にさせてくれ…";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
	goto L_OTHER;
L_QUEST03:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "久しぶりだね。";
		mes " ";
		mes "ゴホッ…… ゴホッ！";
		next;
		mes "[ハルバード]";
		mes "ご、ごめん。";
		mes "体調が悪くてさ…";
		mes "さっき、薬を飲んだから、";
		mes "すぐよくなるよ～";
		mes "僕は、どうも体が弱くてね。";
		next;
		mes "[ハルバード]";
		mes "本題を言うと、今回、";
		mes strcharinfo(0) + "に";
		mes "スザンヌの好きな人が";
		mes "どういう人か調べて欲しいんだ。";
		next;
		menu "何故？",-;
		mes "[ハルバード]";
		mes "彼女の幼馴染として、";
		mes "その男が、";
		mes "スザンヌに相応しい人かどうか";
		mes "知りたいんだよ。";
		next;
		mes "[ハルバード]";
		mes "ブツブツ……";
		mes "（もし、彼女を傷つけるような奴なら、";
		mes "いっそ、僕がこの手で……）";
		next;
		menu "え、何か言った？",-;
		mes "[ハルバード]";
		mes "いや、何も言ってないよ。";
		next;
		menu "本当はまだスザンヌのことを……",-;
		mes "[ハルバード]";
		mes "……";
		mes "本当は、僕は彼女のことは";
		mes "まだ愛しているよ。";
		mes "できるのであれば、";
		mes "この気持ちを伝えたい……";
		next;
		menu "伝えた方がいいよ",-;
		mes "[ハルバード]";
		mes "いや、それはできないって！";
		mes "彼女を困惑させたくないんだ。";
		next;
		mes "[ハルバード]";
		mes "と、とりあえず、スザンヌに";
		mes "スザンヌの好きな人の事を";
		mes "聞いてみてくれないかな。";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "前、スザンヌは、";
		mes "モロクに宝石を探しに行くって";
		mes "言ってたよね？";
		next;
		mes "[ハルバード]";
		mes "それで、今日、スザンヌは、";
		mes "モロクの宝石商に";
		mes "頼んでいた宝石を";
		mes "受け取りに行くらしいんだ。";
		next;
		mes "[ハルバード]";
		mes "そこで、相手はどんな人か";
		mes "聞いてみてくれないかい？";
		mes "（その相手の弱点とか……）";
		next;
		menu "何故、彼女が行くって知っているの？",-;
		mes "[ハルバード]";
		mes "それは、僕が";
		mes "モロクの宝石商の所に先回りして";
		mes "聞きだし……";
		mes "ゴホッゴホッ、";
		mes "まあ、何で知っているかは";
		mes "いいじゃないか！";
		next;
		mes "[ハルバード]";
		mes "モロクにいる宝石商のところだよ。";
		mes "あっ！ 今はピラミッド周辺の";
		mes "キャンプに避難しているんだった。";
		mes "モロクの北西だよ。";
		mes "わかったね？ 頼んだよ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐モロクのピラミッド周辺の";
		mes "宝石商の場所に行き、";
		mes "スザンヌに話しかける‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		//未調査
		mes "[ハルバード]";
		mes "モロクにいる宝石商のところだよ。";
		mes "あっ！ 今はピラミッド周辺の";
		mes "キャンプに避難しているんだった。";
		mes "モロクの北西だよ。";
		mes "わかったね？ 頼んだよ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐モロクのピラミッド周辺の";
		mes "宝石商の場所に行き、";
		mes "スザンヌに話しかける‐";
		close;
	case 3:
		mes "[ハルバード]";
		mes strcharinfo(0) + "！";
		mes "どうだった？";
		mes "スザンヌの好きな人のこと";
		mes "わかった？";
		next;
		mes "‐スザンヌと話した内容を報告した‐";
		next;
		mes "[ハルバード]";
		mes "名前はわからなかったか～、残念。";
		mes "でも、その男は、とても優しい人で、";
		mes "体が弱いのに、いつも";
		mes "スザンヌを守ろうとする、か。";
		next;
		mes "[ハルバード]";
		mes "まあ、優しいって言っても、";
		mes "人間なかなか本性は";
		mes "わからないからね。";
		mes "その男もどうだかね。";
		next;
		mes "[ハルバード]";
		mes "そして、体が弱いか……";
		mes "ふん、体の弱さなら";
		mes "僕だって負けてないぞ。";
		mes "それに僕だってスザンヌを守ろうと";
		mes "してきたし……";
		next;
		emotion 28;
		mes "[ハルバード]";
		mes "ううっ、それなのになぜ……";
		mes "あ、あんまりだ……";
		mes "ううっ……";
		next;
		mes "[ハルバード]";
		mes "ねぇ、";
		mes strcharinfo(0) + "、";
		mes "ところで、その男はさ、";
		mes "夜はどの道を通って帰っているとか";
		mes "聞いてないかな？";
		next;
		mes "[ハルバード]";
		mes "そ、そんな眼で見ないでよ。";
		mes "別に深い意味はないよ、";
		mes " ";
		mes "……";
		mes "ゴホッ、ゴホゴホッ！";
		next;
		mes "[ハルバード]";
		mes "ゴホッ、ゴホゴホッ！";
		mes "ご、ごめん、";
		mes "また具合が悪くなってきたみたい。";
		next;
		mes "[ハルバード]";
		mes "ゴホッ、ゴホゴホッ！";
		mes "薬を飲むからちょっと待ってね。";
		mes " ";
		mes "あ、薬がなくなりそうだな。";
		mes "また貰いに行かなくちゃ……";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "今回も色々、";
		mes "調べてくれてありがとうね。";
		if('@novice){
			mes "これはお礼だよ";
		}
		mes "また、何かお願いがあったら、";
		mes "よろしくね！";
		next;
		if('@novice){
			if(!checkweight(1010,7)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 1010,7;
			//プラコンx7
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[ハルバード]";
		mes "ゴホッ、ゴホゴホッ！";
		mes "薬がなくなりそうだな。";
		mes "また貰いに行かなくちゃ……";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "今回も色々、";
		mes "調べてくれてありがとうね。";
		mes "また、何かお願いがあったら、";
		mes "よろしくね！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
	goto L_OTHER;
L_QUEST04:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "ゴホッ、ゴホッ……";
		mes "久しぶりだね……";
		next;
		mes "[ハルバード]";
		mes "体調がこの通り悪くてさ。";
		mes "薬がきれてしまって……";
		mes "とりに行きたくても、";
		mes "体がいうことを聞かなくて、";
		mes "とりにいけないんだ。";
		mes "ゴホッ、ゴホッ……";
		next;
		mes "[ハルバード]";
		mes "申し訳ないけど、";
		mes "僕の主治医のところに";
		mes "薬を貰いにいってくれないかな？";
		next;
		menu "わかった！",-;
		emotion 15;
		mes "[ハルバード]";
		mes "ゴホッ、ゴホッ……";
		mes "ありがとう。";
		mes "僕の主治医は、^FF0000ゲフェン^000000にいるんだ。";
		mes "頼んだよ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ゲフェンにいる医者に話しかける‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		mes "[ハルバード]";
		mes "ゴホッ、ゴホッ……";
		mes "僕の主治医は、^FF0000ゲフェン^000000にいるんだ。";
		mes "ゴホッ、ゴホッ……";
		mes "薬を頼んだよ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ゲフェンにいる医者に話しかける‐";
		close;
	case 3:
		emotion 15;
		mes "[ハルバード]";
		mes "あ、" + strcharinfo(0) + "。";
		mes "薬を貰ってきてくれたんだね！";
		mes "ありがとう！";
		next;
		mes "‐ハルバードの体調がよさそうだ。";
		mes "バリー先生からもらった";
		mes "薬をハルバードに渡した‐";
		next;
		mes "[ハルバード]";
		mes "実は、さっき、スザンヌが";
		mes "薬を持ってきてくれたんだ！";
		mes "それを飲んだから、";
		mes "大分、体調が良くなったんだ～。";
		next;
		emotion 2;
		mes "[ハルバード]";
		mes "やっぱり、スザンヌは優しいなあ。";
		mes "可愛かった……";
		mes "まるで天使のようだったなあ。";
		next;
		mes "[ハルバード]";
		mes "昔、よくバリー先生のところに";
		mes "スザンヌに";
		mes "付き添ってもらってたしなあ。";
		mes "あの頃から変わらず優しいんだなあ。";
		mes "懐かしい…";
		next;
		mes "[ハルバード]";
		mes "実は最近、";
		mes "スザンヌと話をするのがつらくて、";
		mes "話しかけられても冷たくしていたんだ。";
		mes "それなのに……";
		next;
		emotion 28;
		mes "[ハルバード]";
		mes "それなのに、";
		mes "僕が、体調悪いのに気付いて……";
		mes "しかも薬まで持ってきてくれるなんて。";
		mes "ううっ、スザンヌ……";
		next;
		mes "[ハルバード]";
		mes "はぁぁぁぁ……";
		mes "今は、この幸せな気持ちを";
		mes "味わいつくそう。";
		next;
		menu "スザンヌに感謝しないとね",-;
		mes "[ハルバード]";
		mes "ああっ、スザンヌ！";
		mes "冷たくした僕の愚かさを";
		mes "許しておくれっ!!";
		next;
		emotion 9,"";
		mes "[ハルバード]";
		mes "ああっ、スザンヌ！";
		mes "好きだ！";
		mes "大好きだっ！";
		next;
		menu "……",-;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[ハルバード]";
		mes "はぁぁぁぁ……";
		mes "今は、この幸せな気持ちを";
		mes "味わいつくそう。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
	goto L_OTHER;
L_QUEST06:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "久しぶりだね。";
		mes "この前は薬を届けてくれて";
		mes "ありがとう！";
		next;
		mes "[ハルバード]";
		mes "実は、";
		mes strcharinfo(0) + "に";
		mes "またお願いがあるんだ……";
		next;
		menu "スザンヌのこと？",-;
		mes "[ハルバード]";
		mes "そう、";
		mes "スザンヌのことなんだけど…";
		next;
		mes "[ハルバード]";
		mes "スザンヌがコモドに行ったんだ。";
		mes "間違いなく、ノエリアに会うため";
		mes "だと思う。";
		next;
		menu "ノエリア？",-;
		mes "[ハルバード]";
		mes "ノエリアは、";
		mes "僕とスザンヌの親友でね、";
		mes "昔はいつも3人で遊んでいたんだ。";
		next;
		mes "[ハルバード]";
		mes "そのノエリアは、";
		mes "少し前に、ダンサーになりたい！";
		mes "って言いだして、";
		mes "コモドに急に行ったんだよ。";
		next;
		menu "ノエリアに会いに行くのに何か問題が？",-;
		mes "[ハルバード]";
		mes "ノエリアに会いに行くのが";
		mes "問題なんじゃないんだよ。";
		mes "1人で会いに行ったことが";
		mes "問題なんだ。";
		next;
		mes "[ハルバード]";
		mes "僕達は3人とも親友なんだ。";
		mes "以前、コモドにノエリアに会いに";
		mes "行った時は、僕とスザンヌで";
		mes "2人で行ったんだよ。";
		next;
		mes "[ハルバード]";
		mes "でも、今回はスザンヌは1人で行った…";
		mes "これから言うことは";
		mes "僕の思い込みかもしれないけど、";
		mes "たぶん、スザンヌが好きな人に";
		mes "関係しているような気がする……";
		next;
		emotion 54;
		mes "[ハルバード]";
		mes "だって、そうだろ？";
		mes "僕をおいていくってことはさぁ。";
		mes "なんかすごく寂しいよ。";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "お願いだから、^FF0000コモド^000000に行って";
		mes "様子を見てきてくれないかい？";
		mes "何から何まで頼んで";
		mes "申し訳ないけど、お願いだよ。";
		next;
		menu "わかったよ",-;
		mes "[ハルバード]";
		mes "ありがとう！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐コモドにいる";
		mes "スザンヌとノエリアの様子を見る‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		mes "[ハルバード]";
		mes "^FF0000コモド^000000に行って、スザンヌの";
		mes "様子を見てきてくれないかい？";
		mes "何から何まで頼んで";
		mes "申し訳ないけど、お願いだよ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐コモドにいる";
		mes "スザンヌとノエリアの様子を見る‐";
		close;
	case 3:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "どうだった？";
		next;
		mes "‐ハルバードに、コモドでのことを";
		mes "報告した‐";
		next;
		mes "[ハルバード]";
		mes "そうか、";
		mes "スザンヌがノエリアに";
		mes "相談していたんだね。";
		mes "そして、その相談は恋の相談";
		mes "のようであったと。";
		next;
		emotion 54;
		mes "[ハルバード]";
		mes "はぁぁぁぁっ。";
		mes "恋の相談かぁ。";
		mes "やはり、ショックだなあ。";
		next;
		mes "[ハルバード]";
		mes "でも正直、僕をおいてけぼりにして、";
		mes "スザンヌ、ノエリア、";
		mes "コモドで楽しく遊んでいることまで";
		mes "考えていたから、";
		next;
		mes "[ハルバード]";
		mes "少しだけ、安心したよ。";
		mes "しかも、まだ、スザンヌは";
		mes "告白していないんだね。";
		next;
		menu "このままでいいの？",-;
		mes "[ハルバード]";
		mes "……";
		next;
		menu "スザンヌは君のことが好きだと思う",-;
		mes "[ハルバード]";
		mes "……";
		mes "そう言ってくれてありがとう。";
		mes "僕に勇気をくれようとして。";
		mes "でも、そんなわけはないよ。";
		next;
		mes "[ハルバード]";
		mes "でも、決めたよ。";
		mes "いつも君ばかりに頼って、";
		mes "僕は何もしていない……";
		mes "気持ちを伝えることすらしていない！";
		next;
		mes "[ハルバード]";
		mes "君は、僕のために";
		mes "いろいろな都市を";
		mes "巡ってくれているのに……";
		mes "僕は今まで一体、";
		mes "何をしていたんだろう……";
		next;
		mes "[ハルバード]";
		mes "……ありがとう。";
		mes "君の姿を見て、気付いたよ。";
		next;
		mes "[ハルバード]";
		mes "僕、スザンヌに告白するよ！";
		mes "絶対にっ！";
		mes "スザンヌに好きな人がいても";
		mes "かまわないっ！";
		next;
		mes "[ハルバード]";
		mes "僕の気持ちを伝えるよ!!";
		mes " ";
		mes strcharinfo(0) + "、";
		mes "ありがとう！";
		if('@novice){
			mes "これは、君へのお礼だよ。";
		}
		next;
		if('@novice){
			if(!checkweight(1216,1)) {
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 1216,1;
			//スチレ
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[ハルバード]";
		mes "僕、スザンヌに告白するよ！";
		mes "絶対にっ！";
		mes "スザンヌに好きな人がいても";
		mes "かまわないっ！";
		next;
		//未調査
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
	goto L_OTHER;
L_QUEST07:
	switch(AC_QUEST_ST_0) {
	case 1:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "よく来てくれたね。";
		next;
		mes "[ハルバード]";
		mes "実は、スザンヌに呼び出しを";
		mes "受けたんだ。";
		mes "場所は、";
		mes "^FF0000聖カピトーリナ修道院。^000000";
		next;
		mes "[ハルバード]";
		mes "たぶんスザンナは";
		mes "そこで、僕に、好きな人の相談を";
		mes "しようとしているんだろうね。";
		next;
		mes "[ハルバード]";
		mes "でも、僕はその場所で、スザンヌに";
		mes "告白しようと思う。";
		next;
		mes "[ハルバード]";
		mes "もう、この気持ちを抑えることは";
		mes "できないんだっ！";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "には";
		mes "随分、協力してもらったよね。";
		mes "だから、";
		mes "僕の告白を見届けて欲しいんだ。";
		next;
		menu "いいよ",-;
		mes "[ハルバード]";
		mes "ありがとう！";
		mes "^FF0000聖カピトーリナ修道院^000000";
		mes "で待ち合わせよう。";
		mes "僕は、先に行っているからね。";
		next;
		mes "[ハルバード]";
		mes "聖カピトーリナ修道院へは、";
		mes "^0000FFこのプロンテラの街から";
		mes "まず東へ1マップ行って、";
		mes "北へ1マップ、そして東へ1マップ";
		mes "移動すれば行けるよ。^000000";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐聖カピトーリナ修道院に行き、";
		mes "ハルバードに話しかける‐";
		close2;
		set AC_QUEST_ST_0,2;
		viewpoint 1,289,203,11,0x0000FF;
		end;
	case 2:
		mes "[ハルバード]";
		mes "現地で待ち合わせよう。";
		mes "聖カピトーリナ修道院へは、";
		mes "^0000FFこのプロンテラの街から";
		mes "まず東へ1マップ行って、";
		mes "北へ1マップ、そして東へ1マップ";
		mes "移動すれば行けるよ。^000000";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐聖カピトーリナ修道院に行き、";
		mes "ハルバードに話しかける‐";
		close2;
		viewpoint 1,289,203,11,0x0000FF;
		end;
	}
	goto L_OTHER;
L_QUEST08:
	switch(AC_QUEST_ST_0) {
	case 2:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "ごめん、僕はすぐに";
		mes "出かけなくちゃいけないんだ。";
		next;
		mes "‐スザンヌが心配していたことを";
		mes "伝えた‐";
		next;
		mes "[ハルバード]";
		mes "僕さ、あれからずっと、";
		mes "あのルビーと同じくらいのルビーを";
		mes "探しているんだ。";
		mes "モロクの宝石商に聞いたら、";
		mes "今は、あのルビーほどの宝石は";
		mes "おいていないんだって。";
		next;
		mes "[ハルバード]";
		mes "あれは、アルナベルツ教国で";
		mes "採掘された宝石らしくてさ。";
		mes "アルナベルツ教国の方に";
		mes "通っているんだ。";
		next;
		mes "[ハルバード]";
		mes "ゴホッ、ゴホッ！";
		mes "ごめん、ちょっと疲れていてね。";
		mes "スザンヌとお揃いの";
		mes "ルビーのペアリングが欲しいもんね。";
		mes "だから、頑張るよ。";
		next;
		mes "[ハルバード]";
		mes "ルビーを見つけて、";
		mes "それでリングを作ったら……";
		mes "その時、スザンヌにプロポーズ";
		mes "しようと思うんだ。";
		next;
		mes "[ハルバード]";
		mes "ごめん、そろそろ行くね。";
		mes "スザンヌには、";
		mes "もう少しだけ待っててね、";
		mes "と伝えておいて欲しい。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "(スザンヌに報告しよう。)";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐イズルードにいるスザンヌに";
		mes "報告しよう‐";
		close2;
		set AC_QUEST_ST_0,3;
		end;
	case 3:
		mes "[ハルバード]";
		mes "ごめん、そろそろ行くね。";
		mes "スザンヌには、";
		mes "もう少しだけ待っててね、";
		mes "と伝えておいて欲しい。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐イズルードにいるスザンヌに";
		mes "報告しよう‐";
		close;
	}
	goto L_OTHER;
L_QUEST09:
L_OTHER:
	switch(AC_QUEST_LV_0){
	case 1:
		mes "[ハルバード]";
		mes "本当にありがとう！";
		mes "君は本当にいい人だね。";
		mes "また君に相談するよ！";
		close;
	case 2:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "ごめん、";
		mes "ちょっと、一人にさせてくれ…";
		close;
	case 3:
		mes "[ハルバード]";
		mes "ゴホッ、ゴホゴホッ！";
		mes "薬がなくなりそうだな。";
		mes "また貰いに行かなくちゃ……";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "今回も色々、";
		mes "調べてくれてありがとうね。";
		mes "また、何かお願いがあったら、";
		mes "よろしくね！";
		close;
	case 4:
	case 5:
		mes "[ハルバード]";
		mes "はぁぁぁぁ……";
		mes "今は、この幸せな気持ちを";
		mes "味わいつくそう。";
		close;
	case 6:
	case 7:
	case 0:
		mes "[ハルバード]";
		mes "ああ、スザンヌ……";
		mes "彼女のことを想うと";
		mes "胸が張り裂けそうだ……";
		close;
	case 8:
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "ごめん、僕はすぐに";
		mes "出かけなくちゃいけないんだ。";
		close;
	case 9:
		/*名前なしで本鯖どおり*/
		mes strcharinfo(0) + "、";
		mes "本当にありがとう！";
		close;
	}
}
izlude_in.gat,108,55,4		script	店員#AC_QUE02	951,{
	mes "[マリアン]";
	mes "いらっしゃいませ！";
	if(AC_QUEST_LV_0>1 && AC_QUEST_ST_0!=2) goto L_OTHER;
	if(AC_QUEST_LV_0!=1 && AC_QUEST_ST_0!=2) close;
	next;
	menu "お聞きしたいことが…",-;
	emotion 1;
	mes "[マリアン]";
	mes "はい、何でしょう？";
	next;
	menu "スザンヌという女性を知っていますか？",-;
	mes "[マリアン]";
	mes "あら、";
	mes "スザンヌのお友達？";
	mes "スザンヌは";
	mes "よくこのお店に来るわよ。";
	next;
	menu "何の品物を見ていましたか？",-;
	mes "[マリアン]";
	mes "彼女、ここでリングを";
	mes "買っていたわよ。";
	mes "ウフフ、あの子、";
	mes "好きな人にあげるとかって";
	mes "言っていたわ。";
	mes "あ～、若いっていいわね～。";
	next;
	mes "[マリアン]";
	mes "そのリングにつける宝石を";
	mes "モロクに探しに行くって";
	mes "嬉しそうに話していたわ。";
	next;
	mes "[マリアン]";
	mes "それをもらえる彼氏は";
	mes "女の私から見てもうらやましいわね。";
	mes "あんな可愛い子、滅多にいないもの。";
	next;
	menu "相手の名前ってわかりますか？",-;
	mes "[マリアン]";
	mes "ごめんなさい。";
	mes "名前までは聞いていないのよ。";
	mes "まだつきあっているわけじゃなくて、";
	mes "スザンヌの片思いらしいわ。";
	mes "うまくいくといいわね！";
	next;
	mes "‐ハルバードに報告しよう。";
	mes "ハルバードは耐えられるだろうか？‐";
	next;
L_REP:
	mes "^FF0000【ミッション】^000000";
	mes "‐プロンテラにいる";
	mes "ハルバードに報告する‐";
	close2;
	set AC_QUEST_ST_0,3;
	end;
L_OTHER:
	mes "[マリアン]";
	mes "スザンヌ、うまくいくといいわね。";
	if(AC_QUEST_LV_0==1 || AC_QUEST_ST_0==3) goto L_REP;
	close;
}
function	script	宝石商FUNC#AC_QUE00	{
	if(AC_QUEST_ST_0==3){
		mes "[リューク]";
		mes "お気に入り頂けましたか？";
		next;
		if(strnpcinfo(1)=="スザンヌ"){
			emotion 33,"スザンヌ#AC_QUE00SZ01";
			//スザンヌに話しかけたときにしか出ない
		}
		mes "[スザンヌ]";
		mes "はい、とっても！";
		mes "このルビー、";
		mes "きっと彼も気に入ってくれるわ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐プロンテラにいる";
		mes "ハルバードに報告する‐";
		close;
	}
	mes "[リューク]";
	mes "スザンヌさん。";
	mes "お待ちしておりました。";
	mes "お約束の品、出来ていますよ。";
	next;
	mes "‐宝石商らしき男が、";
	mes "客らしい女性と話をしている‐";
	next;
	mes "[リューク]";
	mes "スザンヌさん。";
	mes "こちらになります。";
	next;
	mes "‐宝石商の男が、";
	mes "２つの宝石をスザンヌに渡した‐";
	next;
	//全角数字で本鯖どおり
	emotion 2,"スザンヌ#AC_QUE00SZ01";
	mes "[スザンヌ]";
	mes "わぁ……";
	next;
	mes "[リューク]";
	mes "お気に入り頂けましたか？";
	next;
	emotion 33,"スザンヌ#AC_QUE00SZ01";
	mes "[スザンヌ]";
	mes "はい、とっても！";
	mes "このルビー、";
	mes "きっと彼も気に入ってくれるわ！";
	next;
	mes "‐スザンヌに誰にプレゼントするか";
	mes "聞いてみよう‐";
	next;
	menu "ステキな宝石ですね。",-;
	mes "[スザンヌ]";
	mes "え、ありがとう。";
	next;
	menu "プレゼント？",-;
	mes "[スザンヌ]";
	mes "え、うん……";
	mes "ずっと好きだった人に";
	mes "プレゼントしようと思って……";
	next;
	mes "[スザンヌ]";
	mes "私と彼は、同じ誕生月で、";
	mes "誕生石は、ルビー。";
	mes " ";
	mes "おそろいのルビーのペアリングを";
	mes "作ろうと思うの。";
	next;
	menu "その人の名前は？",-;
	mes "[スザンヌ]";
	mes "え、名前？";
	mes "ちょっと、それは言えないわ。";
	mes "ごめんなさい。";
	next;
	mes "[スザンヌ]";
	mes "でも、とても優しい人なの。";
	mes "体が弱いのに、いつも";
	mes "私を守ろうとしてくれて……";
	next;
	menu "…… うまくいくといいね。",-;
	emotion 15,"スザンヌ#AC_QUE00SZ01";
	mes "[スザンヌ]";
	mes "ありがとう！";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "(ハルバードに報告しよう。)";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐プロンテラにいる";
	mes "ハルバードに報告する‐";
	close2;
	set AC_QUEST_ST_0,3;
	end;
}
moc_ruins.gat,114,100,4		script	スザンヌ#AC_QUE00SZ01	90,{
	if(AC_QUEST_LV_0==2 && (AC_QUEST_ST_0==2 || AC_QUEST_ST_0==3)) callfunc "宝石商FUNC#AC_QUE00";
	if(AC_QUEST_LV_0==4){
		switch(AC_QUEST_ST_0){
		case 2:
			mes "[スザンヌ]";
			mes "あ、あなたは……";
			next;
			menu "はい、どうぞ。",-;
			mes "‐預かっていた指輪が入っている箱を";
			mes "2つ、スザンヌに渡した‐";
			next;
			mes "[スザンヌ]";
			mes "あなたが指輪を持ってきてくれたのね、";
			mes "ありがとう。";
			next;
			emotion 40;
			mes "‐スザンヌは、ゆっくりと箱をあけた。";
			mes "そして中を見て、ため息をついた‐";
			next;
			mes "[スザンヌ]";
			mes "わぁ、綺麗……";
			mes "本当に綺麗な指輪……";
			next;
			mes "[リューク]";
			mes "見事な指輪ですね。";
			mes "さすが、ジェラルドさん。";
			mes "あの方の仕事ぶりには、";
			mes "いつも驚かされます。";
			next;
			emotion 40;
		case 3:
			mes "[スザンヌ]";
			mes "本当に綺麗な指輪……";
			mes "あの人、喜んでくれるかな……";
			next;
			mes "‐スザンヌは、指輪を見て、";
			mes "微笑んでいる‐";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐フェイヨンの指輪職人ジェラルドに";
			mes "報告する‐";
			close2;
			set AC_QUEST_ST_0,3;
			end;
		}
	}
	mes "[スザンヌ]";
	mes "リュークさんの扱う宝石は";
	mes "とても綺麗なの。";
	close;
}
moc_ruins.gat,116,100,4		script	宝石商#AC_QUE00	47,{
	if(AC_QUEST_LV_0==2 && (AC_QUEST_ST_0==2 || AC_QUEST_ST_0==3)) callfunc "宝石商FUNC#AC_QUE00";
	mes "[リューク]";
	mes "私、宝石商を営んでいる";
	mes "リュークと申します。";
	mes "以後、御見知りおきを。";
	close;
}
geffen_in.gat,113,104,4		script	スザンヌ#AC_QUE00SZ02	90,{
	if(AC_QUEST_LV_0==3){
		switch(AC_QUEST_ST_0){
		case 2:
			mes "‐スザンヌが医者らしき";
			mes "男に話しかけている‐";
			close;
		case 3:
			emotion 19;
			mes "[スザンヌ]";
			mes "あなたは、モロクで会った……";
			mes "あ、ごめんね。";
			mes "急いで、このお薬を";
			mes "届けなくちゃいけないの！";
			close;
		}
	}
	mes "[スザンヌ]";
	mes "こんにちは。";
	mes "私は、バリー先生のところに、";
	mes "お薬をもらいにきたの。";
	close;
}
geffen_in.gat,113,101,4		script	医者#AC_QUE00	121,{
	if(AC_QUEST_LV_0==3){
		switch(AC_QUEST_ST_0){
		case 2:
			mes "‐スザンヌが医者に話しかけている‐";
			next;
			emotion 19,"スザンヌ#AC_QUE00SZ02";
			mes "[スザンヌ]";
			mes "先生、";
			mes "彼、また体調が";
			mes "悪いみたいなんです！";
			mes "薬も切れてしまったみたいで……";
			next;
			mes "[スザンヌ]";
			mes "だから、彼のかわりに";
			mes "薬を貰いにきたんです。";
			next;
			mes "[バリー]";
			mes "そうか、では";
			mes "すぐに薬を処方しよう。";
			next;
			mes "‐医者は、スザンヌに薬を渡した‐";
			next;
			mes "[スザンヌ]";
			mes "先生、ありがとうございます！";
			mes "急いで、彼に渡してきます！";
			next;
			mes "[バリー]";
			mes "うむ、急いで飲ませてあげなさい。";
			next;
			mes "‐医者は、スザンヌの対応が終わって";
			mes "こちらを見た‐";
			next;
			mes "[バリー]";
			mes "うむ、次の方……";
			next;
			mes "‐ハルバードの件について話した‐";
			next;
			mes "[バリー]";
			mes "ハルバードの薬をとりに来た？";
			mes "ハルバードは";
			mes "いい友達がいっぱいいるようじゃな。";
			next;
			menu "？",-;
			mes "[バリー]";
			mes "薬を多く持っていても";
			mes "困ることもないだろう。";
			mes " ";
			mes "ほれ、薬だ。";
			next;
			mes "‐薬を受けとった‐";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐プロンテラにいる";
			mes "ハルバードに薬を渡す‐";
			close2;
			set AC_QUEST_ST_0,3;
			end;
		case 3:
			mes "[バリー]";
			mes "薬がなくなったら、";
			mes "いつでも来なさい。";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐プロンテラにいる";
			mes "ハルバードに薬を渡す‐";
			close;
		}
	}
	mes "[バリー]";
	mes "わしの名は、バリー。";
	mes "医者である。";
	mes "健康には気をつけるのだぞ。";
	close;
}
payon_in01.gat,6,55,4		script	指輪職人#AC_QUE00	901,{
	if(AC_QUEST_LV_0==4){
		switch(AC_QUEST_ST_0){
		case 1:
			mes "[ジェラルド]";
			mes "お、よく来てくれたな！";
			mes "わしが、今回依頼した";
			mes "ジェラルドじゃ！";
			next;
			mes "[ジェラルド]";
			mes "指輪を作って40年！";
			mes "わしは、指輪職人をしているっ！";
			next;
			mes "[ジェラルド]";
			mes "ほう、おまえさん、";
			mes "なかなかいい指をしているのう。";
			mes "この仕事に向いていそうじゃな。";
			next;
			mes "[ジェラルド]";
			mes "う～む、次は指輪つくりの";
			mes "手伝いを依頼しようかのう。";
			next;
			menu "今回の依頼内容は？",-;
			mes "[ジェラルド]";
			mes "今回お願いしたいのは、";
			mes "わしの作った指輪を、";
			mes "至急、依頼主に届けて欲しいのじゃ。";
			mes "ほれ、これじゃ。";
			next;
			mes "[ジェラルド]";
			mes "どうじゃ？";
			mes "いい出来じゃろ。";
			mes "このリングの装飾といい、";
			mes "わしの渾身の作品じゃよ。";
			next;
			mes "[ジェラルド]";
			mes "このルビーの指輪を";
			mes "2つ届けてくれ。";
			mes "場所は、モロクピラミッド周辺の";
			mes "宝石商のところじゃ。";
			mes "そこに、この指輪の依頼主が";
			mes "来ているはずじゃ。";
			next;
			emotion 0,"";
			mes "[ジェラルド]";
			mes "依頼主の名前は、^FF0000スザンヌ^000000じゃ。";
			mes "よろしく頼むぞ。";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐モロクのピラミッド周辺の";
			mes "宝石商の場所にいる";
			mes "スザンヌに会って、";
			mes "ルビーの指輪を渡す‐";
			close2;
			set AC_QUEST_ST_0,2;
			end;
		case 2:
			mes "[ジェラルド]";
			mes "場所は、^FF0000モロクの";
			mes "ピラミッド周辺の宝石商^000000のところじゃ。";
			mes "そこに、この指輪の依頼主が";
			mes "来ているはずじゃ。";
			mes "依頼主の名前は、^FF0000スザンヌ^000000じゃ。";
			mes "よろしく頼むぞ。";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐モロクのピラミッド周辺の";
			mes "宝石商の場所にいる";
			mes "スザンヌに会って、";
			mes "ルビーの指輪を渡す‐";
			close;
		case 3:
			mes "[ジェラルド]";
			mes "おお、届けてくれたか！";
			mes "ありがとう！";
			mes "おまえさん、仕事が早いのう。";
			next;
		case 99:
			mes "[ジェラルド]";
			mes "また、何か頼む事があるかもしれん。";
			mes "その際は、よろしく頼むぞ。";
			next;
			mes "^FF0000【依頼達成】^000000";
			mes "‐依頼を達成した！";
			mes "冒険者アカデミーに";
			mes "報告しに行こう‐";
			close2;
			set AC_QUEST_ST_0,99;
			end;
		}
	}
	mes "[ハルバード]";
	/*本鯖通り*/mes "わしの名はジェラルドじゃ。";
	mes "指輪を作って40年！";
	mes "わしは、指輪職人をしているっ！";
	close;
}
function	script	ノエリアFUNC#AC_QUE00	{
	mes "‐スザンヌがいる。";
	mes "スザンヌが女の人と話をしている。";
	mes "聞き耳をたててみる‐";
	next;
	mes "[スザンヌ]";
	mes "……そうなっても";
	mes "私たちの仲は今まで通りだよね。";
	next;
	mes "[ノエリア]";
	mes "そりゃ、そうよ！";
	mes "当たり前じゃない！";
	mes "心配しないで大丈夫だよ。";
	next;
	mes "[スザンヌ]";
	mes "よかった……";
	next;
	emotion 18,"ノエリア#AC_QUE00";
	mes "[ノエリア]";
	mes "あんた、そんなこと";
	mes "わざわざあたしに";
	mes "確認しに来るなんて";
	mes "本当に、律儀ね～！";
	next;
	mes "[スザンヌ]";
	mes "だって、私たち親友じゃない。";
	mes "だから……";
	next;
	emotion 18,"ノエリア#AC_QUE00";
	mes "[ノエリア]";
	mes "心配しない、心配しない！";
	mes "あたしはいつまでたっても親友よ！";
	mes "それにしても、";
	mes "あいつのことを好……";
	next;
	emotion 0,"ノエリア#AC_QUE00";
	//微妙な時間差再現できるかな？
	mes "‐その時、話に熱中していた2人が、";
	mes strcharinfo(0) + "が";
	mes "横にいることに気付いた‐";
	emotion 0,"スザンヌ#AC_QUE00SZ03";
	next;
	emotion 23,"スザンヌ#AC_QUE00SZ03";
	mes "[スザンヌ]";
	mes "～～～～～～～～っ!!!!";
	mes strcharinfo(0) + "！";
	next;
	mes "[スザンヌ]";
	mes "い、今の話、";
	mes "全部っ、聞いていたの？";
	next;
	menu "聞いてないよ",-;
	emotion 54,"スザンヌ#AC_QUE00SZ03";
	mes "[スザンヌ]";
	mes "はぁ……";
	mes "よかった……";
	next;
	emotion 29,"ノエリア#AC_QUE00";
	mes "[ノエリア]";
	mes "あれ、聞いてなかったの？";
	mes "じゃあ、あたしが全部話してあげるね。";
	mes "この子ね……";
	next;
	emotion 23,"スザンヌ#AC_QUE00SZ03";
	mes "[スザンヌ]";
	mes "ちょっと、ノエリアっ！";
	mes "本当にやめて～～～～!!";
	next;
	mes "‐スザンヌがノエリアの口を";
	mes "必死にふさいでいる‐";
	next;
	emotion 23,"ノエリア#AC_QUE00";
	mes "[ノエリア]";
	mes "ヴ～～～っ！";
	mes "モゴモゴ～～～～ッ!!";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "(ハルバードに報告しよう。)";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐プロンテラにいる";
	mes "ハルバードに報告する‐";
	close2;
	set AC_QUEST_ST_0,3;
	end;
}
comodo.gat,165,163,4		script	スザンヌ#AC_QUE00SZ03	90,{
	if(AC_QUEST_LV_0==9) goto L_CLEAR;
	if(AC_QUEST_LV_0==5 && AC_QUEST_ST_0==2) callfunc "ノエリアFUNC#AC_QUE00";
	if(AC_QUEST_LV_0==5 && AC_QUEST_ST_0==3) {
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "本当に聞いてなかったんだよね……";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐プロンテラにいる";
		mes "ハルバードに報告する‐";
		close;
	}
L_OTHER:
	mes "[スザンヌ]";
	mes "ノエリアに会いに";
	mes "プロンテラから来たんだ。";
	close;
L_CLEAR:
	mes "[スザンヌ]";
	mes strcharinfo(0) + "。";
	mes "あなたには";
	mes "感謝しているわ！";
	close;
}
comodo.gat,168,163,4		script	ノエリア#AC_QUE00	724,{
	if(AC_QUEST_LV_0==9) goto L_CLEAR;
	if(AC_QUEST_LV_0==5 && AC_QUEST_ST_0==2) callfunc "ノエリアFUNC#AC_QUE00";
	if(AC_QUEST_LV_0==5 && AC_QUEST_ST_0==3) {
		mes "[ノエリア]";
		mes "スザンヌって可愛いから";
		mes "からかいたくなっちゃうのよね～。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐プロンテラにいる";
		mes "ハルバードに報告する‐";
		close;
	}
L_OTHER:
	mes "[ノエリア]";
	mes "ああ、コモドっていいわね～。";
	mes "私は、ダンサーになりたくて";
	mes "プロンテラから来たんだ。";
	mes "来てよかったわ～。";
	close;
L_CLEAR:
	mes "[ノエリア]";
	mes "ハルバードとスザンヌがうまくいったのね。";
	mes "よかったわ～";
	close;
}
prt_monk.gat,138,168,4		script	ハルバード#AC_QUE00H02	48,{
	set '@novice, callfunc("AC_GetNovice");
	if(AC_QUEST_LV_0!=6) goto L_OTHER;
	switch(AC_QUEST_ST_0){
	case 2:
		mes "[ハルバード]";
		mes "やぁ、";
		mes strcharinfo(0) + "！";
		mes "待っていたよ！";
		next;
		mes "[ハルバード]";
		mes "スザンヌは、";
		mes "南の方にいるらしいんだ。";
		mes "ふぅ～、緊張するなあ。";
		next;
		emotion 1;
		mes "[ハルバード]";
		mes "……";
		mes "ん？";
		mes "あれ、何か落ちているね。";
		next;
		mes "‐小さな箱が落ちている。";
		mes "覚えがあるような……";
		mes "ハルバードが、その箱を拾った‐";
		next;
		mes "[ハルバード]";
		mes "なんだろうな？";
		mes "あっ、指輪が入っている。";
		mes "すごく綺麗な指輪だ……";
		next;
		mes "^FF0000‐スザンヌの指輪だ！‐^000000";
		next;
		mes "[ハルバード]";
		mes "落とした人は困っているだろうなぁ。";
		mes "スザンヌの待ち合わせ時間には、";
		mes "まだ少し時間があるから、";
		mes "ちょっと持ち主を探してみようかな……";
		next;
		mes "‐スザンヌに急いで";
		mes "聞いてみた方がいいな。";
		mes "スザンヌは、南の方にいるらしい‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐スザンヌに指輪のことを聞いてみる。";
		mes "スザンヌは、聖カピトーリナ修道院の";
		mes "南の方角にいる‐";
		close2;
		set AC_QUEST_ST_0,3;
		viewpoint 1,232,86,11,0x0000FF;
		end;
	case 3:
		mes "[ハルバード]";
		mes "それにしてもかっこいい指輪だなぁ。";
		mes "落とし主が現れなかったら、";
		mes "貰ってしまいたいね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐スザンヌに指輪のことを聞いてみる。";
		mes "スザンヌは、聖カピトーリナ修道院の";
		mes "南の方角にいる‐";
		close;
	case 4:
		mes "[ハルバード]";
		mes "それにしてもかっこいい指輪だなぁ。";
		mes "落とし主が現れなかったら、";
		mes "貰ってしまいたいね。";
		next;
		menu "持ち主が見つかったよ",-;
		mes "[ハルバード]";
		mes "えっ、本当に？";
		mes "じゃあ、僕が返しに行くよ。";
		mes "持ち主の人はどこにいるんだい？";
		next;
		menu "自分が返しに行くよ",-;
		emotion 9;
		mes "[ハルバード]";
		mes strcharinfo(0) + "が";
		mes "返しに行くからいいって？";
		mes "いや、大丈夫だよ。";
		mes "僕が拾ったから、僕が届けるよ。";
		next;
		menu "……",-;
		emotion 1;
		mes "[ハルバード]";
		mes "持ち主の人はどこにいるんだい？";
		mes "ねぇ、何で教えてくれないの？";
		next;
		mes "‐しばらくの間、";
		mes strcharinfo(0) + "は";
		mes "ハルバードに指輪を渡すように";
		mes "言ったが、";
		mes "ハルバードは指輪を返さなかった‐";
		next;
		mes "‐仕方ないので、";
		mes "その指輪は、スザンヌの物であること";
		mes "を話した‐";
		next;
		emotion 0;
		mes "[ハルバード]";
		mes "！";
		mes "なるほどね。";
		next;
		mes "[ハルバード]";
		mes "おそらく、この指輪が、";
		mes "スザンヌの好きな人に渡そうとしている";
		mes "指輪なんだろうね……";
		next;
		mes "[ハルバード]";
		mes strcharinfo(0) + "、";
		mes "僕は今、1つの感情で支配されそうだ。";
		mes "こんなこと初めてだ……";
		next;
		emotion 7;
		mes "[ハルバード]";
		mes "それはスザンヌを愛する、";
		mes "という感情。";
		mes "すなわち、スザンヌを";
		mes "他の男に渡したくない。という";
		mes "感情！";
		next;
		emotion 36;
		mes "[ハルバード]";
		mes "ええい！";
		mes "こんなものっ！";
		next;
		mes "‐ハルバードが指輪を";
		mes "地面に叩きつけ、";
		mes "さらに落ちている石を拾い、";
		mes "その石を指輪に叩きつけた！‐";
		next;
		mes "^0000FF‐そして、ハルバードは、";
		mes "指輪を海に投げてしまった！‐";
		next;
		menu "なんて事をっ！",-;
		mes "‐" + strcharinfo(0) + "は";
		mes "ハルバードを平手打ちした‐";
		next;
		mes "[ハルバード]";
		mes "ブベッ！";
		mes "……";
		mes "感情を抑えられなかった……";
		mes "ごめん。";
		next;
		mes "[ハルバード]";
		mes "僕は、スザンヌのことが……";
		mes "どうしようもなく、好きなんだ……";
		next;
		mes "‐仕方ない……";
		mes "指輪のことをスザンヌに報告しよう‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐スザンヌに指輪のことを報告する‐";
		close2;
		viewpoint 1,232,86,11,0x0000FF;
		set AC_QUEST_ST_0,5;
		end;
	case 5:
		mes "[ハルバード]";
		mes "スザンヌのことが……";
		mes "どうしようもなく、好きなんだ……";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐スザンヌに指輪のことを報告する‐";
		close2;
		viewpoint 1,232,86,11,0x0000FF;
		end;
	case 6:
		emotion 23;
		mes "[ハルバード]";
		mes "あぁぁぁぁぁぁっっ!!";
		mes "僕はっ！";
		mes "なんて事をしてしまったんだぁぁっ！";
		next;
		mes "[ハルバード]";
		mes "僕は、なんて、";
		mes "なんて愚かなんだっ!!";
		next;
		emotion 23;
		mes "[ハルバード]";
		mes "スザンヌに会わせる顔がない……";
		mes "うぁぁぁっ！";
		next;
		mes "[ハルバード]";
		mes "……";
		mes strcharinfo(0) + "、";
		mes "ご、ごめん……";
		mes "一人で考えたいんだ…";
		mes "色々と、ありがとう。";
		if('@novice){
			mes "これはお礼だよ……";
		}
		next;
		if('@novice){
			if(!checkweight(1011,6)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 1011,6;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[ハルバード]";
		mes "……";
		mes strcharinfo(0) + "、";
		mes "ご、ごめん……";
		mes "一人で考えたいんだ…";
		mes "色々と、ありがとう。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_OTHER:
	mes "[ハルバード]";
	mes "こんにちは。";
	close;
}
prt_monk.gat,232,86,4		script	スザンヌ#AC_QUE00SZ03	90,{
	if(AC_QUEST_LV_0!=6) goto L_OTHER;
	switch(AC_QUEST_ST_0){
	case 3:
		emotion 28;
		mes "[スザンヌ]";
		mes "どうしよう、指輪がない……";
		mes "落としちゃったのかな……";
		mes "これじゃ、告白できないよ……";
		next;
		mes "‐スザンヌにルビーの指輪が";
		mes "落ちていたこと、";
		mes "ハルバードが拾ったことを話した‐";
		next;
		emotion 0;
		mes "[スザンヌ]";
		mes "ええっ";
		mes "ハルバードが拾ってしまったのっ！";
		mes "そ、そんなぁ。";
		next;
		mes "[スザンヌ]";
		mes "よりによって、ハルバード";
		mes "に拾われてしまうなんて……";
		mes "あれは、";
		mes "私からハルバードに渡す";
		mes "ルビーの指輪だったのに……";
		next;
		mes "[スザンヌ]";
		mes "……";
		mes "実はね、今日、ハルバードに";
		mes "告白しようと思っているの。";
		mes "それで、彼をここへ呼び出したんだ。";
		next;
		mes "[スザンヌ]";
		mes "私たち、同じ誕生月だから、";
		mes "誕生石のルビーの";
		mes "おそろいのペアリングを用意したの。";
		next;
		mes "[スザンヌ]";
		mes "それを渡して、告白したかったのに。";
		mes "それが、こんなことに";
		mes "なってしまうなんて……";
		next;
		menu "とりあえず、指輪を返してもらってくるよ",-;
		mes "[スザンヌ]";
		mes "……うん、";
		mes "お願い……";
		mes "私からハルバードに渡したいの……";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ハルバードに話しかけ、";
		mes "指輪を返してもらおう‐";
		close2;
		set AC_QUEST_ST_0,4;
		viewpoint 1,138,168,11,0x0000FF;
		end;
	case 4:
		emotion 54;
		mes "[スザンヌ]";
		mes "ああ、私は";
		mes "なんてドジなんだろう……";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ハルバードに話しかけ、";
		mes "指輪を返してもらおう‐";
		close;
	case 5:
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "どうだった？";
		next;
		mes "‐ハルバードが指輪を";
		mes "破壊してしまったことを話した‐";
		next;
		mes "‐そしてハルバードが";
		mes "スザンヌのことを好きであること、";
		mes "指輪は、他の男にあげるものだと";
		mes "勘違いして壊してしまったことを";
		mes "話した‐";
		next;
		emotion 1;
		mes "[スザンヌ]";
		mes "ハルバードが私のことを好き？";
		mes "そ、そんな……";
		next;
		mes "[スザンヌ]";
		mes "だって、ハルバード、";
		mes "最近ずっと私に会ってくれないし、";
		mes "話しかけても、冷たくされて……";
		mes " ";
		mes "それが、すごく寂しくて……";
		next;
		mes "[スザンヌ]";
		mes "だから、ルビーの指輪を……";
		mes "ルビーは私と彼の生まれ月の７月の";
		mes "誕生石なの。";
		mes "石言葉も「純愛」だし、";
		mes "ルビーの指輪で";
		mes "告白したいなって思ってて……";
		next;
		mes "‐その時！‐";
		next;
		mes "[？]";
		mes "クッ!!";
		next;
		mes "‐物陰から声が聞こえた。";
		mes "^0000FFハルバードだ！^000000";
		mes "今の会話を聞いていたようだ‐";
		next;
		mes "‐ハルバードは^0000FF悲痛な顔^000000をして";
		mes "走り去った！‐";
		next;
		emotion 0;
		mes "[スザンヌ]";
		mes "ハルバードっ!!";
		mes " ";
		mes "‐スザンヌはハルバードを";
		mes "追おうとする‐";
		next;
		if(select("スザンヌを止める","見守る")==1){
			mes "‐スザンヌが追おうとしたが、";
			mes strcharinfo(0) + "は";
			mes "それを止めた‐";
			next;
			mes "[スザンヌ]";
			mes strcharinfo(0) + "、";
			mes "何で止めるのっ！";
			next;
			menu "自分が行く",-;
			mes "[スザンヌ]";
			mes "……";
			mes "わかったわ……";
			mes "お願いね。";
			next;
			mes "[スザンヌ]";
			mes "……";
			mes "私がルビーの指輪さえ";
			mes "おとさなければ……";
			next;
		}
		else {
			mes "‐スザンヌがハルバードを追う。";
			mes strcharinfo(0) + "は";
			mes "それを見守る‐";
			next;
			mes "[スザンヌ]";
			mes "あっ！";
			mes " ";
			mes "‐スザンヌがつまずいた。";
			mes "その間にハルバードの姿は";
			mes "見えなくなってしまった‐";
			next;
			mes "[スザンヌ]";
			mes "ああ、ハルバード……";
			mes "行かないで……";
			next;
			menu "自分が探しに行くよ",-;
			mes "[スザンヌ]";
			mes "……";
			mes "うん、お願い……";
			next;
		}
		mes "^FF0000【ミッション】^000000";
		mes "‐ハルバードに話しかける‐";
		close2;
		set AC_QUEST_ST_0,6;
		viewpoint 1,138,168,11,0x0000FF;
		end;
	case 6:
		mes "[スザンヌ]";
		mes "……";
		mes "私がルビーの指輪さえ";
		mes "おとさなければ……";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ハルバードに話しかける‐";
		close2;
		viewpoint 1,138,168,11,0x0000FF;
		end;
	case 99:
		mes "[スザンヌ]";
		mes "……";
		mes "私がルビーの指輪さえ";
		mes "おとさなければ……";
		next;
		//未調査
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_OTHER:
	mes "[スザンヌ]";
	mes "こんにちは。";
	mes "私、この場所が好きなんだ。";
	close;
}
izlude.gat,137,156,4		script	スザンヌ#AC_QUE00SZ04	90,{
	switch(AC_QUEST_LV_0){
	case 7:
		goto L_QUEST08;
	case 8:
		goto L_QUEST09;
	case 9:
		goto L_CLEAR;
	default:
		goto L_OTHER;
	}
L_QUEST08:
	switch(AC_QUEST_ST_0){
	case 1:
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "お願いがあるの。";
		next;
		mes "[スザンヌ]";
		mes "あれから、ハルバードの行方が";
		mes "わからないの。";
		mes "たまに、プロンテラに戻ってきている";
		mes "みたいなんだけど、";
		mes "すぐにいなくなってしまうの。";
		next;
		mes "[スザンヌ]";
		mes "私、すごく心配で……";
		mes "だから、ハルバードがどこにいるか、";
		mes "何をしているか調べて欲しいの。";
		next;
		menu "わかった",-;
		mes "[スザンヌ]";
		mes "ありがとう！";
		next;
		mes "‐プロンテラのハルバードが";
		mes "いた居場所に行ってみよう‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐プロンテラのハルバードが";
		mes "いた居場所に行って、情報を探す‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		mes "[スザンヌ]";
		mes "ハルバードがどこにいるか、";
		mes "何をしているか調べて欲しいの。";
		next;
		mes "‐プロンテラのハルバードが";
		mes "いた居場所に行ってみよう‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐プロンテラのハルバードが";
		mes "いた居場所に行って、情報を探す‐";
		close;
	case 3:
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "何かわかった？";
		next;
		mes "‐プロンテラで";
		mes "ハルバードに会ったこと、";
		mes "ハルバードは代わりのルビーを";
		mes "アルナベルツ教国に";
		mes "探しにいっていることを話した‐";
		next;
		mes "[スザンヌ]";
		mes "えっ、そんな……";
		mes "ハルバード、体が弱いのに、";
		mes "そんな遠くまで……";
		next;
		mes "[スザンヌ]";
		mes "私、ハルバードと";
		mes "いれるだけでいいのに……";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_0,99;
		end;
	case 99:
		mes "[スザンヌ]";
		mes "ハルバード、体が弱いのに……";
		mes "心配……";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
	goto L_OTHER;
L_QUEST09:
	switch(AC_QUEST_ST_0){
	case 1:
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "大変なのっ！";
		next;
		menu "どうしたの？",-;
		mes "[スザンヌ]";
		mes "ハルバードがアルナベルツ教国に行ってから";
		mes "1週間戻ってこないの！";
		mes "彼、体が弱いのよ！";
		mes "薬が必要なのっ！";
		next;
		emotion 0,"";
		mes "[スザンヌ]";
		mes "ゲフェンにいる";
		mes "ハルバードの主治医の先生に";
		mes "確認したら、1週間前に";
		mes "3日分だけもらっただけらしいの。";
		next;
		menu "!!",-;
		mes "[スザンヌ]";
		mes "今頃、薬がきれて";
		mes "大変なことになっていると思うの、";
		mes "私と一緒に、薬を届けに";
		mes "アルナベルツ教国に行きましょう！";
		next;
		menu "もちろんさ！",-;
		mes "[スザンヌ]";
		mes "まず、ラヘルに探しに行こう！";
		next;
		mes "[スザンヌ]";
		mes "ラヘルの中央の道を北に行くと";
		mes "フレイヤ神殿への階段があるの。";
		mes "その前で、落ち合いましょう！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ラヘルへ行き、";
		mes "情報を集めているスザンヌに";
		mes "フレイヤ神殿への階段前で会う‐";
		close2;
		set AC_QUEST_ST_0,2;
		end;
	case 2:
		mes "[スザンヌ]";
		mes "まず、ラヘルに行きましょう！";
		next;
		mes "[スザンヌ]";
		mes "ラヘルの中央の道を北に行くと";
		mes "フレイヤ神殿への階段があるの。";
		mes "その前で、落ち合いましょう！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ラヘルへ行き、";
		mes "情報を集めているスザンヌに";
		mes "フレイヤ神殿への階段前で会う‐";
		close;
	}
L_OTHER:
	mes "[スザンヌ]";
	mes "こんにちは。";
	close;
L_CLEAR:
	mes "[スザンヌ]";
	mes strcharinfo(0) + "。";
	mes "あなたには";
	mes "感謝しているわ！";
	close;
}
rachel.gat,148,190,4		script	スザンヌ#AC_QUE00SZ05	90,{
	if(AC_QUEST_LV_0==9) goto L_CLEAR;
	if(AC_QUEST_LV_0!=8) goto L_OTHER;
	switch(AC_QUEST_ST_0){
	case 2:
		mes "[スザンヌ]";
		mes strcharinfo(0) + "！";
		mes "ハルバード、";
		mes "2日前までラヘルの";
		mes "ホテルに泊まっていたわ！";
		next;
		mes "[スザンヌ]";
		mes "ホテルの人に";
		mes "これから、ベインスに行くって";
		mes "言っていたらしいわ。";
		next;
		mes "[スザンヌ]";
		mes "特に、具合が悪そうでも";
		mes "なかったみたいだから、";
		mes "ちょっと安心した……";
		next;
		mes "[スザンヌ]";
		mes "でも、急がなくちゃ。";
		mes "次はベインスに行きましょう。";
		mes "ハルバード……";
		mes "待ってて！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ベインスに行き、";
		mes "ハルバードを探す‐";
		close2;
		set AC_QUEST_ST_0,3;
		end;
	case 3:
		mes "[スザンヌ]";
		mes "次はベインスに行きましょう。";
		mes "ハルバード……";
		mes "待ってて！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐ベインスに行き、";
		mes "ハルバードを探す‐";
		close;
	}
L_OTHER:
	mes "[スザンヌ]";
	mes "こんにちは。";
	close;
L_CLEAR:
	mes "[スザンヌ]";
	mes strcharinfo(0) + "。";
	mes "あなたには";
	mes "感謝しているわ！";
	close;
}
veins.gat,151,330,4			script	スザンヌ#AC_QUE00SZ06	90,{
	set '@novice, callfunc("AC_GetNovice");
	if(AC_QUEST_LV_0!=8) goto L_OTHER;
	switch(AC_QUEST_ST_0) {
	case 3:
		mes "[スザンヌ]";
		mes "ハルバード！";
		next;
		emotion 0,"ハルバード#AC_QUE00H03";
		mes "[ハルバード]";
		mes "スザンヌっ！";
		mes "どうしてここにいるんだい？";
		next;
		mes "[スザンヌ]";
		mes "心配してきたんじゃない！";
		mes "体は大丈夫？";
		mes "薬を持ってきたの！";
		mes "さぁ、早く飲んでっ！";
		next;
		mes "‐スザンヌが薬を";
		mes "ハルバードの口の中に押し込んだ‐";
		next;
		emotion 16,"ハルバード#AC_QUE00H03";
		mes "[ハルバード]";
		mes "ちょっと!!";
		mes "ゲホッゲホッ……";
		mes "苦しいっ！";
		next;
		mes "[ハルバード]";
		mes "く、薬は、さっき飲んだから";
		mes "大丈夫だよ。";
		next;
		emotion 1,"スザンヌ#AC_QUE00SZ06";
		mes "[スザンヌ]";
		mes "なんでっ！？";
		mes "薬がなくて、大変だったでしょ！";
		next;
		mes "[ハルバード]";
		mes "以前、";
		mes strcharinfo(0) + "が";
		mes "持ってきてくれた薬があったから";
		mes "それを飲んだから大丈夫さ。";
		next;
		mes "[スザンヌ]";
		mes "本当？";
		mes "よかった……";
		mes "心配してたんだよ……";
		next;
		emotion 33,"スザンヌ#AC_QUE00SZ06";
		mes "[スザンヌ]";
		mes "じゃあ、私と一緒に、";
		mes "もう戻りましょう。";
		mes " ";
		mes "ね？";
		next;
		mes "[ハルバード]";
		mes "だめだよっ！";
		mes "まだ戻れない！";
		next;
		emotion 1,"スザンヌ#AC_QUE00SZ06";
		mes "[スザンヌ]";
		mes "どうして？";
		mes "どうして戻れないの？";
		next;
		mes "[ハルバード]";
		mes "……";
		mes "君とおそろいの";
		mes "ペアリングを作るためだよ……";
		mes "そのために";
		mes "ルビーを探さなきゃいけないんだ。";
		next;
		emotion 0,"スザンヌ#AC_QUE00SZ06";
		mes "[スザンヌ]";
		mes "もうペアリングはいらない！";
		mes "だから";
		mes "一緒に戻ろうよ。";
		next;
		mes "[ハルバード]";
		mes "だめだよ。";
		mes "これは僕の試練なんだ。";
		mes "僕は今まで、人に頼りすぎていた。";
		next;
		mes "[ハルバード]";
		mes "スザンヌ、僕は君のことが好きだ、";
		mes "でも、僕は君にふられるのが怖くて、";
		mes "告白することから逃げて";
		mes strcharinfo(0) + "に";
		mes "ばかり頼っていた。";
		next;
		mes "[ハルバード]";
		mes "そんな僕は君にふさわしくないよ。";
		mes "おそろいのペアリングを";
		mes "自分の力で手にいれて初めて";
		mes "君にふさわしい男になれるんだ。";
		next;
		mes "[スザンヌ]";
		mes "そんなことないよっ！";
		mes "私のために、自分の体を顧みずに";
		mes "一人でこんなところまで来て……";
		mes "その気持ちだけで十分だよ。";
		next;
		mes "‐ハルバードは首を横に振った‐";
		next;
		mes "‐スザンヌは、一瞬考え込んだ。";
		mes "そして、ルビーの指輪を取り出した‐";
		next;
		mes "[ハルバード]";
		mes "君の分の指輪だね。";
		mes "必ず、僕の分も作って、";
		mes "おそろいになるよ……";
		next;
		mes "‐スザンヌは、いきなり";
		mes "そのルビーの指輪を";
		mes "山の方へ思い切り投げた！‐";
		next;
		mes "[ハルバード]";
		mes "あっ！";
		mes "何やっているの！？";
		next;
		mes "[スザンヌ]";
		mes "これで私たちおそろいだね。";
		next;
		mes "[スザンヌ]";
		mes "ハルバードがルビーの指輪を";
		mes "作っちゃうと、";
		mes "私たち、";
		mes "おそろいじゃなくなっちゃうよ。";
		next;
		emotion 9,"ハルバード#AC_QUE00H03";
		mes "[ハルバード]";
		mes "……";
		next;
		emotion 20,"ハルバード#AC_QUE00H03";
		mes "[ハルバード]";
		mes "フフフ";
		mes "スザンヌ、一緒に戻ろう。";
		mes "こんな僕だけど、";
		mes "君を絶対に幸せにするよ！";
		next;
		emotion 33,"スザンヌ#AC_QUE00SZ06";
		mes "[スザンヌ]";
		mes "うん！";
		next;
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "本当にありがとう。";
		if('@novice){
			mes "これ、私からの気持ちよ。";
		}
		next;
		if('@novice){
			if(!checkweight(1146,1)) {
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 1146,1;
		}
		set AC_QUEST_ST_0,99;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	case 99:
		mes "[スザンヌ]";
		mes "ハルバード……";
		mes "ずっと一緒よ。";
		mes "これからは、何でも私に相談してね。";
		next;
		mes "[ハルバード]";
		mes "うん……";
		next;
		mes "[スザンヌ]";
		mes strcharinfo(0) + "、";
		mes "本当にありがとう。";
		next;
		mes "[ハルバード]";
		mes "僕たちがうまくいったのは";
		mes strcharinfo(0) + "の";
		mes "おかげだよ。";
		mes "ありがとう！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_OTHER:
	mes "[" + strcharinfo(0) + "]";
	mes "(2人が楽しそうに会話している。";
	mes "そっとしておこう。)";
	close;
}
veins.gat,148,329,4		duplicate(スザンヌ#AC_QUE00SZ06)	ハルバード#AC_QUE00H03	48

