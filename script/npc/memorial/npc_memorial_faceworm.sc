//= Auriga Script ==============================================================
// Ragnarok Online Nest of Faceworm Script	by refis
//==============================================================================

//============================================================
// NPC
//------------------------------------------------------------
payon.gat,157,54,5	script	年配の女性	103,{
	if(checkquest(114655)) {
		mes "‐年配の女性が今日も";
		mes "　いつもの場所に一人";
		mes "　たたずんでいる……‐";
		next;
		if(countitem(6650) < 1) {
			mes "‐指輪を手に入れた女性の夫は";
			mes "　フェイスワームに襲われたのかも";
			mes "　しれない。";
			close;
		}
		if(select("声をかけない","声をかける") == 1) {
			mes "‐今はそっとしておこう‐";
			close;
		}
		mes "‐年配の女性に指輪を";
		mes "　そっと差し出した‐";
		next;
		mes "‐古ぼけてはいるものの";
		mes "　派手ではない控えめな装飾が";
		mes "　なにかに喜ぶように";
		mes "　小さく一瞬輝いた‐";
		next;
		if(checkquest(114655)&8) {
			mes "[年配の女性]";
			mes "あの人の指輪ね……。";
			mes "この指輪が戻るとまるで";
			mes "あの人がただいまって";
			mes "いってくれている気がするのよ。";
			mes "いつもありがとう。";
		}
		else {
			mes "^0000ff‐指輪には小さな文字が書かれている。";
			mes "[大切な君へ]‐^000000";
			next;
			mes "[年配の女性]";
			mes "これは……！";
			mes "あの人が私に贈ろうとしてくれた";
			mes "指輪……。";
			mes "名前は書いていないけれど";
			mes "私が好きだった宝石ばかり";
			mes "ちりばめられているわ。";
			next;
			mes "[年配の女性]";
			mes "あの人、いなくなる前に";
			mes "私の誕生石や私が好きな宝石をそりゃあ";
			mes "うんざりするほど聞いてきたの。";
			mes "だから、この指輪は";
			mes "あの人が私のためにと用意してくれた";
			mes "指輪に間違いないわ……。";
			next;
			mes "[年配の女性]";
			mes "でもよく見つかったわね……？";
			mes "ほぼ諦めかけていたくらいに";
			mes "月日は経過していたはずよ。";
			next;
			mes "‐あなたは黙って頷いた‐";
			next;
			mes "[年配の女性]";
			mes "あら……何か特別な";
			mes "事情があるのかしら。";
			mes "いいわ。";
			mes "あなたは指輪を持ってきてくれた。";
			mes "それだけで充分だわ。";
			mes "本当に、ありがとう。";
			next;
			mes "[年配の女性]";
			mes "これからは私……";
			mes "あの人との思い出を大切にして";
			mes "楽しく生きる事にするわ。";
			next;
			mes "‐^0000ffどこからか温かい気が感じられる^000000‐";
			misceffect 72;
		}
		next;
		mes "[年配の女性]";
		mes "あなたにもちゃんとした";
		mes "お礼をしたいのだけれど、";
		mes "今はこれしか無くて……。";
		mes "良かったら食べて頂戴。";
		delitem 6650,1;
		getitem RAND_FOOD,3;
		compquest 114655;
		close;
	}
	mes "[年配の女性]";
	mes "あなた、冒険者の方ね。";
	mes "少し私の昔話に付き合って";
	mes "いただいて、いいかしら。";
	next;
	mes "[年配の女性]";
	mes "私が幼い頃よ。";
	mes "14か15歳くらいだったかしら。";
	mes "その時私には";
	mes "心から好きだった男の子がいたの。";
	mes "でもね……。";
	next;
	mes "[年配の女性]";
	mes "その時は私の気持ちを";
	mes "どうやって表現すればいいのか";
	mes "分からなかったの。";
	next;
	mes "[年配の女性]";
	mes "暇さえあれば";
	mes "その人のペコペコにちょっかいを出して";
	mes "なんとか気を引こうとしたのだけど……";
	mes "上手くいかずに大喧嘩もしたわ。";
	next;
	mes "[年配の女性]";
	mes "ただ、お互い良く会っていたから";
	mes "気が合ったのかしらね。";
	mes "結局、いつからともなく";
	mes "付き合い始める事になったのよ。";
	mes "嬉しかったわ……。";
	mes "やだ。恥ずかしくなるわね。";
	next;
	mes "[年配の女性]";
	mes "ある程度の歳になって結婚もしたわ。";
	mes "まぁ、小さいころから";
	mes "ずーっと一緒だったし、";
	mes "お金も無かったから";
	mes "結婚式をしたわけではないけど。";
	next;
	mes "[年配の女性]";
	mes "それでね。";
	mes "年を取ってから主人はその事をすごく";
	mes "気にするようになっていたの。";
	mes "指輪ひとつ買ってあげられないままで";
	mes "本当に申し訳ない、って。";
	next;
	mes "[年配の女性]";
	mes "一緒にいるだけで充分だったのに。";
	mes "それに……結婚して何年も経ってから";
	mes "急に言わなくてもいいのに。ねぇ。";
	mes "ふふふ。";
	mes "笑っちゃうでしょ。";
	next;
	mes "[年配の女性]";
	mes "……。";
	next;
	mes "[年配の女性]";
	mes "……";
	mes "…………。";
	next;
	mes "[年配の女性]";
	mes "……";
	mes "…………";
	mes "………………。";
	next;
	mes "[年配の女性]";
	mes "もう随分前に突然、";
	mes "^0000ff指輪^000000を手にいれてくるって";
	mes "出て行ってしまったの。";
	next;
	mes "[年配の女性]";
	mes "いらないわよって";
	mes "何度も伝えたんだけど……。";
	next;
	mes "[年配の女性]";
	mes "それっきり、主人は帰って";
	mes "来なかったわ。";
	mes "冒険者の話じゃ主人によく似た男の人が";
	mes "大きな蛇に追われているのを";
	mes "見たんだとか……。";
	next;
	mes "[年配の女性]";
	mes "ああ、あの時止めていれば。";
	mes "あなた……。うぅ……。";
	next;
	menu "……",-;
	mes "[年配の女性]";
	mes "せめて指輪があれば、";
	mes "あの人も報われるのに……。";
	next;
	mes "‐もし指輪を拾ったら";
	mes "　この年配の女性の指輪か";
	mes "　確認してもらうために";
	mes "　話しかけよう‐";
	setquest 114655;
	close;
}

payon.gat,161,54,3	script	異国的な商人	99,{
	if(checkquest(114660)) {
		mes "‐家族の手がかりを探す";
		mes "　あの男性が今日も";
		mes "　この場所にいるのが見える‐";
		next;
		if(countitem(6652) < 1) {
			mes "‐フェイスワームの巣に";
			mes "　何か思い出の品が残っている";
			mes "　かもしれない‐";
			close;
		}
		if(select("声をかけない","声をかける") == 1) {
			mes "‐特に今は用がないので‐";
			mes "　声をかけるのをやめた‐";
			close;
		}
		if(checkquest(114660)&8) {
			mes "‐セルジオにまだ渡していない";
			mes "　新しく見つかったアルバムを";
			mes "　手渡した‐";
			next;
			mes "‐アルバムは少し色あせているが";
			mes "　そこに写っている人の笑顔は";
			mes "　色あせることなく写っている‐";
			next;
			mes "[セルジオ]";
			mes "あなたのお陰でまた";
			mes "親父との思い出を";
			mes "取り戻すことができました。";
			mes "ありがとうございます。";
			next;
			mes "‐優しい気があなたに力を";
			mes "　吹き込んでくれた‐";
		}
		else {
			mes "[セルジオ]";
			mes "このアルバムは……";
			mes "まさか親父の？";
			next;
			mes "[セルジオ]";
			mes "ああ、思い出しました。";
			mes "これは親父と一緒に";
			mes "仕事をしていた方です。";
			next;
			mes "[セルジオ]";
			mes "おお、他の人たちも見覚えがある。";
			mes "ありがとうございます。";
			mes "大事にさせていただきます……。";
			next;
			mes "[セルジオ]";
			mes "ですが……。";
			mes "親父は交流が広かったので";
			mes "ほかにもまだこのアルバムに";
			mes "載っていない人がいるかも";
			mes "しれません。";
			next;
			mes "[セルジオ]";
			mes "もしまたアルバムを拾ったら";
			mes "持ってきてくれませんか。";
			mes "親父のことです。";
			mes "他の人も撮影しているに";
			mes "違いないですし。";
			next;
			mes "‐^0000ffアルバムを眺めていたセルジオの顔に";
			mes "　寂しさと嬉しさが混ざった";
			mes "　微笑みが広がった^000000‐";
			next;
			mes "‐^0000ff優しい気を感じる^000000‐";
			misceffect 72;
		}
		next;
		mes "[セルジオ]";
		mes "本当にありがとうございました。";
		mes "アルバムのお礼にこれをどうぞ。";
		mes "気に入って頂けると良いのですが……。";
		delitem 6652,1;
		getitem RAND_FOOD,3;
		compquest 114660;
		close;
	}
	mes "[セルジオ]";
	mes "幼い頃、親父の仕事に";
	mes "ついて行った時の記憶が";
	mes "微かに残っているんです。";
	next;
	mes "[セルジオ]";
	mes "正確には分からないんですが、";
	mes "この近くを通っている途中に";
	mes "巨大な蛇のような生物に襲われて";
	mes "離れ離れになってしまいました。";
	next;
	mes "[セルジオ]";
	mes "その時、家族を失いました。";
	mes "今となっては家族との思い出も";
	mes "うまく思い出せない状態です。";
	next;
	mes "[セルジオ]";
	mes "今の私は商売もしているので";
	mes "生活に余裕が出来ました。";
	mes "ただ、相変わらずあの時の記憶が";
	mes "私を苦しめています。";
	next;
	mes "[セルジオ]";
	mes "この場所を訪れればもしかしたら";
	mes "私の家族に関する手がかりが";
	mes "見つけられるかなと思ったのですが";
	mes "なかなか難しいですね。";
	mes "やはり時間が経ち過ぎてたのか、";
	mes "何も見つかりませんでした。";
	next;
	mes "‐この男性の家族の";
	mes "　手がかりになりそうな";
	mes "　写真のようなものを拾ったら";
	mes "　再度また話しかけよう‐";
	setquest 114660;
	close;
}

payon.gat,161,50,1	script	強そうに見える男	88,{
	if(checkquest(114665)) {
		mes "‐大きな蛇を探す";
		mes "　強そうに見える男が";
		mes "　辺りを見回している‐";
		next;
		if(countitem(6653) < 1) {
			mes "‐届けられなかった薬は";
			mes "　フェイスワームの巣に";
			mes "　あるかもしれない。";
			mes "　探してみよう‐";
			close;
		}
		if(select("声をかけない","声をかける") == 1) {
			mes "‐声をかけるのをやめた‐";
			close;
		}
		if(checkquest(114665)&8) {
			mes "‐強そうに見える男に";
			mes "　新しく入手した薬袋を";
			mes "　手渡した‐";
			next;
			mes "[強そうに見える男]";
			mes "ありがとうございます。";
			mes "これであの蛇の数がまた";
			mes "減ったと思うと";
			mes "私の心も多少、救われます。";
			next;
			mes "[強そうに見える男]";
			mes "この薬はもう飲めませんが";
			mes "届けていただいた薬袋の存在は";
			mes "私にとって前に進むための";
			mes "特効薬になりそうです。";
		}
		else {
			mes "‐少し袋がくたびれた";
			mes "　薬袋を強そうに見える男に";
			mes "　錠剤がこぼれないように";
			mes "　気をつけながら渡した‐";
			next;
			mes "[強そうに見える男]";
			mes "これはまさか……!?";
			mes "間違いない。";
			mes "薬袋に見覚えのある字で";
			mes "メモが書かれている……。";
			mes "これをどうやって";
			mes "入手したのですか？";
			next;
			mes "‐あなたは事情を伝えた‐";
			next;
			mes "[強そうに見える男]";
			mes "この薬……この薬さえあったら……。";
			next;
			mes "‐^0000ff薬袋を握ったまま悲しんでいる。";
			mes "　主従の関係を超えた何かが";
			mes "　彼から感じ取られる^000000‐";
			next;
			mes "[強そうに見える男]";
			mes "もし、また薬袋を手に入れたら";
			mes "私の元に持ってきてください。";
			mes "薬袋が届けば、あの蛇の数が";
			mes "少しでも減った証になります。";
			next;
			mes "[強そうに見える男]";
			mes "死んだあの方はもう戻りません。";
			mes "ですが蛇が減れば、私と同じ";
			mes "気持ちの方が減るかもしれない。";
			mes "きっとそれがあの方への";
			mes "供養にもなると思うのです。";
			next;
			mes "[強そうに見える男]";
			mes "……そう考えたら少し";
			mes "気持ちが楽になりました。";
			mes "本当に、この薬袋をわざわざ";
			mes "届けていただき、";
			mes "ありがとうございました。";
			next;
			mes "‐^0000ff穏やかな気が感じられる^000000‐";
			misceffect 72;
		}
		next;
		mes "[強そうに見える男]";
		mes "それと……こんなものしかありませんが";
		mes "ぜひ、憎き蛇を倒す為に";
		mes "お役立てください。";
		delitem 6653,1;
		getitem RAND_FOOD,3;
		compquest 114665;
		close;
	}
	mes "[強そうに見える男]";
	mes "私には仕えている人がいました。";
	mes "その方は体が弱く常に咳をしていたので";
	mes "いつも薬を飲んでいたんです。";
	mes "その薬は毎月、決められた日に";
	mes "届けられていました。";
	next;
	mes "[強そうに見える男]";
	mes "ところがある日、到着する予定の薬が";
	mes "来なかったんです。";
	mes "聞いた話では薬を運んでいた人が";
	mes "大きな蛇に襲撃されたそうで……。";
	next;
	mes "[強そうに見える男]";
	mes "その結果、私が仕えている方は";
	mes "亡くなりました。";
	mes "……";
	mes "私はその蛇を見つけて殺すために";
	mes "何年も探し回っています。";
	next;
	menu "復讐でもするつもりですか？",-;
	mes "[強そうに見える男]";
	mes "そ、それは……。";
	next;
	mes "[強そうに見える男]";
	mes "そう、どうせあの蛇は";
	mes "私と関係がない。";
	mes "私はあの方のただの部下だ……。";
	next;
	mes "‐^0000ff彼の顔からは";
	mes "　複雑な思いが見られた^000000‐";
	next;
	mes "‐この男の気持ちを少しでも";
	mes "　救えるものの手がかりは";
	mes "　フェイスワームの巣にありそうだ‐";
	setquest 114665;
	close;
}

payon.gat,139,68,4	script	薄暗い男	795,{
	if(checkquest(114670)) {
		mes "‐腕輪を探し求めている";
		mes "　片言の幽霊の";
		mes "　キットンが今日もいる‐";
		next;
		if(countitem(6651) < 1) {
			mes "‐キットンは腕輪を探しているようだ。";
			mes "　フェイスワームの巣に";
			mes "　手がかりがありそうだ‐";
			close;
		}
		if(select("声をかけない","声をかける") == 1) {
			mes "‐幽霊でも一人でいたい時はあるはずだ‐";
			mes "‐　今はそっとしておこう‐";
			close;
		}
		if(checkquest(114670)&8) {
			mes "‐キットンに拾った";
			mes "　古ぼけた腕輪を";
			mes "　手渡した‐";
			next;
			mes "^999999[キットン]";
			mes "新しい腕輪。";
			mes "友達思い出す。";
			mes "友達増えた。気がする。";
			mes "嬉しい。^000000";
		}
		else {
			mes "‐小さなイニシャルが彫られた";
			mes "　少し古ぼけた腕輪を";
			mes "　キットンに見せてみた";
			next;
			mes "^999999[キットン]";
			mes "キットンの腕輪！^000000";
			next;
			mes "^999999[キットン]";
			mes "嬉しい。腕輪戻った！";
			mes "嬉しい!!^000000";
			next;
			mes "^999999[キットン]";
			mes "でも友達。昔言った。";
			mes "キットン好きな装飾。";
			mes "わからない。";
			mes "だからいっぱい作った。";
			mes "腕輪いっぱい。^000000";
			next;
			mes "^999999[キットン]";
			mes "だからもし。";
			mes "腕輪。新しいの。";
			mes "あなた見つけた。";
			mes "キットンに届ける。";
			mes "キットン腕輪増える。嬉しい。";
			mes "お願い。^000000";
			next;
			mes "^0000ff‐キットンの魂がまぶしく光る‐^000000";
			misceffect 247;
		}
		next;
		mes "^999999[キットン]";
		mes "キットン嬉しい。";
		mes "だからこれあげる。";
		mes "あなたも嬉しい？";
		mes "あなたが嬉しいと";
		mes "キットンもっと嬉しい。^000000";
		delitem 6651,1;
		compquest 114670;
		getitem RAND_FOOD,3;
		close;
	}
	mes "‐^0000ffすでに死んだ人の魂が、";
	mes "　何かを伝えようとしている^000000‐";
	next;
	mes "^999999[キットン]";
	mes "俺……キットン。";
	mes "話、うまくない。^000000";
	next;
	mes "^999999[キットン]";
	mes "キットン、昔死んだ。";
	mes "でも、恨みない。";
	mes "キットン悪い存在ではない。^000000";
	next;
	mes "^999999[キットン]";
	mes "キットン……腕輪が必要。";
	mes "とても。とても大事な物。";
	mes "友達がくれた大切な腕輪。^000000";
	next;
	mes "^999999[キットン]";
	mes "キットンその腕輪を探す。";
	mes "悪い蛇倒す。";
	mes "悪い蛇キットンを殺した。^000000";
	next;
	mes "‐この幽霊が安心できるよう";
	mes "　フェイスワームの巣で";
	mes "　腕輪を見つけたら";
	mes "　声をかけてみよう‐";
	setquest 114670;
	close;
}

//============================================================
// 生成NPC
//------------------------------------------------------------
dali.gat,83,67,5	script	古い立て札	857,{
	if($FacewormParty$ == "") {
		mes "‐長い間、新しい記録が出なかった為";
		mes "　掲示板が古くなりました‐";
		close;
	}
	mes "‐フェイスワームの巣　記録票‐";
	mes "■パーティー名";
	mes "^ff0044" +$FacewormParty$+ "^000000";
	mes "■攻略タイム";
	mes "^0000ff" + $FacewormTime/60 + "分 " + $FacewormTime%60 + "秒^000000";
	close;
}

dali.gat,80,60,4	script	魔法学者	755,{
	if(checkquest(12325)&2 && checkquest(118921)&2) {
		mes "‐^0000ff次元移動の痕跡が消えました。";
		mes "　次元移動機を再び利用することが";
		mes "　可能になりました。^000000‐";
		delquest 12325;
		delquest 118921;
		close;
	}
	mes "[魔法学者]";
	mes "こんにちは。";
	mes "何の用件でしょうか？";
	next;
	set '@party$,getpartyname(getcharid(1));
	set '@leader$,getpartyleader(getcharid(1));
	switch(select("次元移動をしたい","ここで何をしているか聞く","モンスターの巣について聞く","用件は無い")) {
	case 1:
		if(BaseLevel < 140) {
			mes "[魔法学者]";
			mes "ここに入場するのはまだ無理です。";
			mes "BaseLvが140以上になったら";
			mes "また来てください。";
			close;
		}
		if(checkquest(12325) || checkquest(118921)) {
			mes "[魔法学者]";
			mes "次元移動はどうでしたか。";
			mes "次元移動は体への負担も";
			mes "大きくかかるそうです。";
			next;
			mes "[魔法学者]";
			mes "もう一度次元移動をしたいのでしたら";
			mes "しばらく時間を空けてから";
			mes "来てください。";
			close;
		}
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[魔法学者]";
			mes "次元移動をご希望の場合は";
			mes "パーティーリーダーの方が";
			mes "手続きをしてください。";
			close;
		}
		mdcreate "Faceworm";
		mes "[魔法学者]";
		mes "パーティー名は";
		mes '@party$+ "で";
		mes "パーティーリーダーは";
		mes '@leader$;
		mes "ですね。";
		next;
		mes "[魔法学者]";
		mes "移動機を作動させました。";
		mes "準備が完了したら、";
		mes "奥の次元移動機から、";
		mes "移動してください。";
		close;
	case 2:
		mes "[魔法学者]";
		mes "私は次元の亀裂を研究しています。";
		mes "そこにある次元移動機から";
		mes "自由に過去に移動する事が";
		mes "出来るんですよ。";
		mes "すごいでしょう。";
		next;
		mes "[魔法学者]";
		mes "といっても……";
		mes "私の成果ではないんですけどね。";
		next;
		mes "[魔法学者]";
		mes "ここに自然発生した次元の亀裂を";
		mes "意図通りに操作できるまでには";
		mes "多くの試行錯誤がありました。";
		next;
		mes "[魔法学者]";
		mes "亀裂から発生する力を";
		mes "うまく制御する事ができず";
		mes "長い間、研究は停滞していたのです。";
		next;
		mes "[魔法学者]";
		mes "しかし最近になって、";
		mes "ある1人の研究者と";
		mes "ある1人の歴史学者の";
		mes "大きな貢献によって";
		mes "魔力で意図的に制御する事が";
		mes "可能になったのです。";
		next;
		mes "[魔法学者]";
		mes "ルーンミッドガッツから訪れた";
		mes "冒険者の方の力添えも";
		mes "かなりあったようです。";
		next;
		mes "[魔法学者]";
		mes "私が担当しているこの場所は";
		mes "近くもなく遠くもない過去と";
		mes "繋がっているようです。";
		mes "フェイヨン付近に生息する";
		mes "モンスターの巣だとか。";
		mes "ただ……";
		next;
		mes "[魔法学者]";
		mes "ここを通った冒険者に聞いても";
		mes "中で何があったのか";
		mes "教えてくれる人はいませんでした。";
		next;
		mes "[魔法学者]";
		mes "それに向こうに行って来た人たちは";
		mes "あっちにある立て札に";
		mes "何かの時間を記録していましたね。";
		mes "あれは何なのでしょう……。";
		next;
		mes "[魔法学者]";
		mes "おっと。すみません。";
		mes "一人で喋りすぎました。";
		mes "あなたも次元移動を希望ですか？";
		next;
		mes "[魔法学者]";
		mes "中にいるモンスターは強力なようです。";
		mes "腕に自信があってご希望のようなら";
		mes "私が次元移動機を作動させます。";
		mes "いつでも言って下さい。";
		mes "　";
		mes "‐^ff0000BaseLv140以上の冒険者のみ^000000‐";
		close;
	case 3:
		mes "[魔法学者]";
		mes "以前、フェイヨン付近で";
		mes "通行人がモンスターに襲われる";
		mes "被害が多発していました。";
		mes "この先はそのモンスターの巣に";
		mes "繋がっているようです。";
		next;
		mes "[魔法学者]";
		mes "そのモンスターの被害にあった人の";
		mes "関係者がフェイヨンにいます。";
		mes "もし巣の中で被害者に関係のある物を";
		mes "発見したら、彼らに渡してあげると";
		mes "良いでしょう。";
		next;
		mes "[魔法学者]";
		mes "良かったら彼らのいるフェイヨンまで";
		mes "送りましょうか？";
		next;
		if(select("お願いする","やめておく") == 2) {
			mes "[魔法学者]";
			mes "そうですか。";
			mes "まあ他人が首を突っ込むことでは";
			mes "ないのかもしれないですね。";
			close;
		}
		mes "[魔法学者]";
		mes "それではいきますよ。";
		close2;
		warp "payon.gat",150,58;
		end;
	case 4:
		mes "[魔法学者]";
		mes "そうですか。";
		mes "何か御用の際はお声かけください。";
		close;
	}
OnInit:
	waitingroom "フェイスワーム",0;
	end;
}

dali.gat,77,58,4	script	次元移動機	10007,{
	if(checkquest(12325)&2 && checkquest(118921)&2) {
		mes "‐^0000ff次元移動の痕跡が消えました。";
		mes "　次元移動機を再び利用することが";
		mes "　可能になりました。^000000‐";
		delquest 12325;
		delquest 118921;
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[次元移動機]";
		mes "次元移動機は、";
		mes "パーティーを組んだ状態で";
		mes "利用してください。";
		close;
	}
	mes "[次元移動機]";
	mes "確認中";
	mes "……";
	next;
	if(BaseLevel < 140) {
		mes "[次元移動機]";
		mes "次元移動不可能です。";
		mes "能力が不足しています。";
		mes "BaseLv140以上の能力が必要です。";
		close;
	}
	if(checkquest(12325) || checkquest(118921)) {
		mes "[次元移動機]";
		mes "移動不可、移動不可。";
		mes "次元移動の痕跡が残っています。";
		mes "時間を空けてから来てください。";
		close;
	}
	mes "‐次元移動機は正常に動作している‐";
	next;
	if(select("入る","やめておく") == 2) {
		mes "‐あなたは次元移動機から離れた‐";
		close;
	}
	switch(mdenter("Faceworm")) {
	case 0:
		announce "[" +strcharinfo(1)+ "]パーティーの[" +strcharinfo(0)+ "]が[Faceworm]に入場します。",0x9,0x00ff99;
		setquest 12325;
		setquest 118921;
		donpcevent getmdnpcname("#FacewarmManager")+ "::OnStart";
		//warp "1@face.gat",112,353;
		close;
	default:
		mes "[次元移動機]";
		mes "まだ、通路が活性化されていません。";
		mes "しばらくお待ちください。";
		close;
	}
}

//============================================================
// フェイスワームの巣
//------------------------------------------------------------
1@face.gat,110,348,6	script	#FacewarmManager	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("ケイオス#01");
	hideonnpc getmdnpcname("#虫1入口");
	hideonnpc getmdnpcname("#虫2入口");
	hideonnpc getmdnpcname("#虫3入口");
	hideonnpc getmdnpcname("#虫4入口");
	hideonnpc getmdnpcname("ケイオス#5");
	hideonnpc getmdnpcname("#ケイ_北");
	hideonnpc getmdnpcname("#ケイ_南");
	hideonnpc getmdnpcname("#ケイ_東");
	hideonnpc getmdnpcname("#ケイ_西");
	hideonnpc getmdnpcname("ケイオス#北");
	hideonnpc getmdnpcname("ケイオス#南");
	hideonnpc getmdnpcname("ケイオス#東");
	hideonnpc getmdnpcname("ケイオス#西");
	hideonnpc getmdnpcname("#ケイon3");
	hideonnpc getmdnpcname("ケイオス#6");
	hideonnpc getmdnpcname("アイリス#6");
	hideonnpc getmdnpcname("次元移動機#6");
	hideonnpc getmdnpcname("#虫1褒賞");
	hideonnpc getmdnpcname("#虫2褒賞");
	hideonnpc getmdnpcname("#虫3褒賞");
	hideonnpc getmdnpcname("#虫4褒賞");
	hideonnpc getmdnpcname("#虫5褒賞");
	hideonnpc getmdnpcname("大商人の箱#1");

	areamonster getmdmapname("1@face.gat"),0,0,0,0,"サベージ",1166,40;
	areamonster getmdmapname("1@face.gat"),0,0,0,0,"天下大将軍",1277,70;
	areamonster getmdmapname("1@face.gat"),0,0,0,0,"ビートル",1494,40;
	end;
}

1@face.gat,110,348,6	script	ケイオス#0	683,{
	cutin "H_CHAOS01.bmp", 2;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[ケイオス]";
		mes "今はお前らの代表者と";
		mes "話してる途中だから";
		mes "待っててくれるか？";
		close2;
		cutin "H_CHAOS01.bmp", 255;
		end;
	}
	mes "[ケイオス]";
	mes "ん？　他の懸賞金ハンターが";
	mes "ここに来るなんて話は";
	mes "聞いてないぞ？";
	unittalk "ケイオス : ん？　他の懸賞金ハンターがここに来るなんて話は聞いてないぞ？";
	next;
	menu "懸賞金ハンターではありません",-;
	mes "["+strcharinfo(0)+"]";
	mes "違います、";
	mes "私たちは懸賞金ハンターでは";
	mes "ありません。";
	unittalk getcharid(3),strcharinfo(0)+" : 違います、私たちは懸賞金ハンターではありません。";
	next;
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "違うならいいんだ。";
	mes "どうせフェイスワームは";
	mes "誰のモノでもないしな。";
	unittalk "ケイオス : 違うならいいんだ。どうせフェイスワームは誰のモノでもないしな。";
	next;
	if(select("詳しく聞く必要はない","フェイスワーム？") == 2) {
		mes "["+strcharinfo(0)+"]";
		mes "フェイスワームという名前は";
		mes "初めて聞きました。";
		unittalk getcharid(3),strcharinfo(0)+" : フェイスワームという名前は初めて聞きました。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "本当に知らないみたいだな。";
		mes "ま、下手に隠してケガでもされたら";
		mes "こっちも気分が悪いしな。";
		mes "簡単に説明してやるよ。";
		unittalk "ケイオス : 本当に知らないみたいだな。ま、下手に隠してケガでもされたらこっちも気分が悪いしな。簡単に説明してやるよ。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "フェイスワームってのは";
		mes "ここら辺に出没する、蟲みたいな";
		mes "モンスターの名前だ。";
		mes "フェイスワームは縄張り意識が";
		mes "かなり強く、侵入者には容赦しない。";
		unittalk "ケイオス : フェイスワームってのはここら辺に出没する、蟲みたいなモンスターの名前だ。フェイスワームは縄張り意識がかなり強く、侵入者には容赦しない。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "詳しい生態は分かっていないが";
		mes "女王と呼ばれる格段に強い";
		mes "フェイスワームがいる巣の";
		mes "存在が確認されている。";
		mes "女王のいる巣までの道のりは";
		mes "竹林を4つほど抜けた先らしい。";
		unittalk "ケイオス : 詳しい生態は分かっていないが女王と呼ばれる格段に強いフェイスワームがいる巣の存在が確認されている。女王のいる巣までの道のりは竹林を4つほど抜けた先らしい。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "あと、一つ重要なことを教えておく。";
		mes "あいつらはかなりの生存、繁殖能力を";
		mes "兼ね備えたモンスターだ。";
		mes "だから、討伐する際に重要なのは";
		mes "攻撃力と、素早さになる。";
		unittalk "ケイオス : あと、一つ重要なことを教えておく。あいつらはかなりの生存、繁殖能力を兼ね備えたモンスターだ。だから、討伐する際に重要なのは攻撃力と、素早さになる。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "そのためいつしかこの辺じゃ";
		mes "女王フェイスワームをどれだけ早く";
		mes "討伐できるかが、そいつの";
		mes "腕のよさの証明みたいな";
		mes "風潮になってるんだ。";
		unittalk "ケイオス : そのためいつしかこの辺じゃ女王フェイスワームをどれだけ早く討伐できるかが、そいつの腕のよさの証明みたいな風潮になってるんだ。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "あとはまあ、入手できる素材が";
		mes "手間と時間をかければかけるほど";
		mes "価値が下がる傾向でな。";
		mes "良質な素材がほしい商人どもが";
		mes "娯楽と素材目的でフェイスワーム";
		mes "討伐タイムアタックなんて企画を";
		unittalk "ケイオス : というのも、入手できる素材は手間と時間をかければかけるほど価値が下がる傾向でな。良質な素材がほしい商人どもが娯楽と素材目的でフェイスワーム討伐タイムアタックなんて企画を";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "この場所にやってきた参加者に";
		mes "強制的に参加させてるんだ。";
		mes "だからもし、この先に進むなら";
		mes "自分の意思に関わらず、";
		mes "タイムアタック参加とみなされるから";
		mes "憶えておくといいかもな。";
		unittalk "ケイオス : この場所にやってきた参加者に強制的に参加させてるんだ。だからもし、この先に進むなら自分の意思に関わらず、タイムアタック参加とみなされるから憶えておくといいかもな。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "ま、強制的に参加させられたからって";
		mes "早く討伐しなきゃいけないとか";
		mes "変に気にする必要はないぜ？";
		mes "早く討伐すれば素材や褒賞に";
		mes "多少の夢と希望がもてるって";
		mes "単純明快な話だからな。";
		unittalk "ケイオス : ま、強制的に参加させられたからって早く討伐しなきゃいけないとか変に気にする必要はないぜ？　早く討伐すれば素材や褒賞に多少の夢と希望がもてるって単純明快な話だからな。";
		next;
		cutin "H_CHAOS01.bmp", 2;
		mes "[ケイオス]";
		mes "とりあえず、もし進むなら";
		mes "慣れるまでアイリスのヤツに";
		mes "その時々の状況について、";
		mes "説明させるようにしておくぜ。";
		mes "うるさいと思うが、しばらく";
		mes "我慢してくれ。";
		unittalk "ケイオス : とりあえず、もし進むなら慣れるまでアイリスのヤツにその時々の状況について、説明させるようにしておくぜ。うるさいと思うが、しばらく我慢してくれ。";
	}
	close2;
	cutin "H_CHAOS01.bmp", 255;
	donpcevent getmdnpcname("ケイオス#0")+ "::OnStart";
	end;
OnStart:
	hideoffnpc getmdnpcname("ケイオス#01");
	hideonnpc getmdnpcname("ケイオス#0");
	initnpctimer;
	end;
OnTimer5000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk1";
	end;
OnTimer10000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk2";
	end;
OnTimer15000:
	donpcevent getmdnpcname("アイリス#0")+"::OnTalk1";
	end;
OnTimer20000:
	donpcevent getmdnpcname("アイリス#0")+"::OnTalk2";
	end;
OnTimer25000:
	donpcevent getmdnpcname("アイリス#0")+"::OnTalk3";
	end;
OnTimer30000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk3";
	end;
OnTimer35000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk4";
	end;
OnTimer40000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk5";
	end;
OnTimer45000:
	donpcevent getmdnpcname("アイリス#0")+"::OnTalk4";
	end;
OnTimer50000:
	donpcevent getmdnpcname("ケイオス#01")+"::OnTalk6";
	end;
OnTimer55000:
	hideonnpc getmdnpcname("ケイオス#01");
	hideonnpc getmdnpcname("アイリス#0");
	end;
OnTimer60000:
	stopnpctimer;
	donpcevent getmdnpcname("#虫0_mobdead")+"::OnStart";
	donpcevent getmdnpcname("#虫0_timer")+"::OnStart";
	announce "‐タイムアタック開始‐",0x9,0xffffff,0x190,36;
	end;
}

1@face.gat,110,348,6	script	ケイオス#01	683,{
	end;
OnTalk1:
	unittalk "ケイオス : しかしまさか、オレ達以外にも人がいるとはな……。";
	end;
OnTalk2:
	unittalk "ケイオス : まあ、いいか。邪魔さえしないなら、俺達からも迷惑はかけない。";
	end;
OnTalk3:
	unittalk "ケイオス : それもたぶん、今だけだ。";
	end;
OnTalk4:
	unittalk "ケイオス : 黒い風が吹き始めている。この風の感じは……。";
	end;
OnTalk5:
	unittalk "ケイオス : アイリス！　フェイスワームの気配を感じる。たぶん女王の巣はこの奥だ！";
	end;
OnTalk6:
	unittalk "ケイオス : そうだ、早く片付けて帰ろう。あと、そこのお前。進むつもりなら、フェイスワームたちが集まって来ているから気を付けろよ。";
	end;
}

1@face.gat,116,346,3	script	アイリス#0	666,{
	cutin "H_IRIS02.bmp", 2;
	mes "[アイリス]";
	mes "ごめんね～。";
	mes "今、風を感じている途中だから";
	mes "後にしてくれる？";
	close2;
	cutin "H_IRIS02.bmp", 255;
	end;
OnTalk1:
	unittalk "アイリス : あー気持ちのいい風ー♪";
	end;
OnTalk2:
	unittalk "アイリス : へへっ、この頃、天気がすごく良くてアイリスも大満足♪";
	end;
OnTalk3:
	unittalk "アイリス : どうかした？　ケイオス。すごく怖い顔してるけど。";
	end;
OnTalk4:
	unittalk "アイリス : いつも通りにやればいいんだよね？";
	end;
}

1@face.gat,1,1,0	script	#虫0_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@face.gat");
	set '@label$,getmdnpcname("#虫0_mobdead")+"::OnKilled";
	set '@user,getmapusers('@map$);
	areamonster '@map$,85,325,95,335,"フェイスワーム",2528,2+'@user,'@label$;
	areamonster '@map$,65,285,75,295,"フェイスワーム",2528,1+'@user,'@label$;
	areamonster '@map$,65,220,75,230,"フェイスワーム",2528,1+'@user,'@label$;
	areamonster '@map$,70,156,80,166,"フェイスワーム",2528,2+'@user,'@label$;
	areamonster '@map$,77,81,87,91,"フェイスワーム",2528,2+'@user*2,'@label$;
	areamonster '@map$,138,64,148,74,"フェイスワーム",2528,2+'@user*2,'@label$;
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@face.gat"),getmdnpcname("#虫0_mobdead")+"::OnKilled");
	if('@count <= 0) {
		donpcevent getmdnpcname("#ボス虫0")+"::OnStart";
		donpcevent getmdnpcname("#ボス虫0_bc")+"::OnStart";
	}
	else
		announce "‐あと" +'@count+ "匹‐",0x9,0xffffff,0x190,36;
	end;
}

1@face.gat,1,2,0	script	#虫0_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3600000:
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,1,3,0	script	#ボス虫0	139,{
OnStart:
	if('mob) end;
	announce "アイリス : フェイスワームが逃げ始めた！　って、なにか巨大な影がこっちに向かってきてるよ！", 0x9, 0x00ffff, 0x190, 20, 0, 0;
	set 'mob,callmonster(getmdmapname("1@face.gat"),145,74,"ダークフェイスワーム#1",2530,getmdnpcname("#ボス虫0")+"::OnKilled");
	setmobhp 'mob,2600000+getmapusers(getmdmapname("1@face.gat"))*200000;
	set 'mobmax,getmobhp('mob);
	end;
OnKilled:
	set 'mob,0;
	donpcevent getmdnpcname("#ボス虫0_bc")+"::OnStop";
	announce "アイリス : ダークフェイスワームが出てきた穴が見えるね。あの穴から次の場所に行けそうだよ。", 0x9, 0xffffff, 0x190, 18, 0, 0;
	hideoffnpc getmdnpcname("#虫1褒賞");
	hideoffnpc getmdnpcname("#虫1入口");
	end;
}

1@face.gat,1,4,0	script	#ボス虫0_bc	139,{
OnStart:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
OnTimer1000:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#ボス虫0"));
	set '@maxhp,getvariableofnpc('mobmax,getmdnpcname("#ボス虫0"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		set '@rate,getmobhp('@boss) / '@maxhp * 100;
		if('@rate > 80) {
			set 'mob[0],callmonster(getmdmapname("1@face.gat"),'@x-4,'@y,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
			set 'mob[1],callmonster(getmdmapname("1@face.gat"),'@x+4,'@y,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
		}
		else {
			set 'mob[0],callmonster(getmdmapname("1@face.gat"),'@x-4,'@y,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
			set 'mob[1],callmonster(getmdmapname("1@face.gat"),'@x+4,'@y,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
			set 'mob[2],callmonster(getmdmapname("1@face.gat"),'@x,'@y-4,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
			set 'mob[3],callmonster(getmdmapname("1@face.gat"),'@x,'@y+4,"フェイスワームの卵",2540,getmdnpcname("#ボス虫0_bc")+"::OnKilled");
		}
	}
	end;
OnTimer12000:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#ボス虫0"));
	if('@boss) {
		for(set '@i,0;'@i<3;set '@i,'@i+1) {
			if('mob['@i]) {
				set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob['@i]);
				if('@dummy == -1)
					break;
				monster '@map$,'@x,'@y,"フェイスワームの幼虫",2541,1;
				set '@num,'@num+1;
				set '@dummy,removemonster('mob['@i]);
				set 'mob['@i],0;
			}
		}
		if('@num > 0) {
			announce "アイリス : ダークフェイスワームが卵を" +'@num+ "個食べて、元気を取り戻したみたい……。やっかいね……。", 0x9, 0xff00ee, 0x190, 18, 0, 0;
			setmobhp '@boss,getmobhp('@boss)+50000*'@num;	// 未調査
		}
	}
	end;
OnTimer13000:
	initnpctimer;
	end;
OnKilled:
	end;
}

1@face.gat,149,92,0	script	#虫1入口	45,2,2,{
	if(BaseLevel < 160)
		getexp 10000000,0;
	else
		getexp 20000000,0;
	warp getmdmapname("1@face.gat"),127,95;
	end;
}

1@face.gat,120,97,6	script	ケイオス#1	683,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		// 未調査
		mes "[ケイオス]";
		mes "今はお前らの代表者と";
		mes "話してる途中だから";
		mes "待っててくれるか？";
		close2;
		cutin "H_CHAOS01.bmp", 255;
		end;
	}
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "もう追いついたのか。";
	mes "なかなかやるじゃないか。";
	unittalk "ケイオス : もう追いついたのか。なかなかやるじゃないか。";
	next;
	menu "さっきの……",-;
	mes "["+strcharinfo(0)+"]";
	mes "さっきのモンスターが";
	mes "ここの主なんですか？";
	unittalk getcharid(3),strcharinfo(0)+" : さっきのモンスターがここの主なんですか？";
	next;
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "いや、女王フェイスワームは";
	mes "あんなもんじゃない。";
	unittalk "ケイオス : いや、女王フェイスワームはあんなもんじゃない。";
	next;
	mes "[ケイオス]";
	mes "さっきの奴はフェイスワームの亜種だ。";
	mes "亜種とは言っても、そこまで";
	mes "恐ろしい奴じゃないけどな。";
	unittalk "ケイオス : さっきの奴はフェイスワームの亜種だ。亜種とは言っても、そこまで恐ろしい奴じゃないけどな。";
	next;
	mes "[ケイオス]";
	mes "そうだ。フェイスワームから";
	mes "手に入る皮なんだが、";
	mes "意外と使えるかもしれないぞ。";
	unittalk "ケイオス : そうだ。フェイスワームから手に入る皮なんだが、意外と使えるかもしれないぞ。";
	next;
	cutin "H_IRIS01.bmp", 2;
	mes "[アイリス]";
	mes "だけど戦闘が長びくと";
	mes "皮にキズが付くのよね～。";
	mes "一言でいえば使い物にならなく";
	mes "なっちゃうの。";
	donpcevent getmdnpcname("アイリス#1")+"::OnTalk1";
	next;
	cutin "H_IRIS02.bmp", 2;
	mes "[アイリス]";
	mes "手慣れたハンターたちは";
	mes "素早く正確に上等な皮を";
	mes "取る事ができるらしいよ。";
	donpcevent getmdnpcname("アイリス#1")+"::OnTalk2";
	next;
	mes "[アイリス]";
	mes "ケイオスも自信あるよね？";
	donpcevent getmdnpcname("アイリス#1")+"::OnTalk3";
	next;
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "無茶言うな！";
	mes "俺はマグナムブレイクしか";
	mes "使えないんだよ！";
	mes "全部燃えてなくなっちまうよ！";
	unittalk "ケイオス : 無茶言うな！　俺はマグナムブレイクしか使えないんだよ！　全部燃えてなくなっちまうよ！";
	next;
	cutin "H_IRIS01.bmp", 2;
	mes "[アイリス]";
	mes "まったく……！　使えないケイオス。";
	donpcevent getmdnpcname("アイリス#1")+"::OnTalk4";
	next;
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "とにかく俺たちが狙っている奴は";
	mes "ここにもいなかったようだ。";
	mes "俺たちは先に行くからお前も";
	mes "気をつけろよ。";
	unittalk "ケイオス : とにかく俺たちが狙っている奴はここにもいなかったようだ。俺たちは先に行くからお前も気をつけろよ。";
	next;
	hideonnpc getmdnpcname("ケイオス#1");
	cutin "H_IRIS01.bmp", 2;
	mes "[アイリス]";
	mes "ケイオス!?";
	mes "またそうやって一人で先走って……";
	mes "待ちなさい！";
	donpcevent getmdnpcname("アイリス#1")+"::OnTalk5";
	close2;
	cutin "H_IRIS02.bmp", 255;
	hideonnpc getmdnpcname("アイリス#1");
	initnpctimer;
	viewpoint 1, 116, 292, 1, 0xFF8000;
	viewpoint 1, 163, 239, 2, 0xFF8000;
	viewpoint 1, 203, 286, 3, 0xFF8000;
	viewpoint 1, 99, 206, 4, 0xFF8000;
	donpcevent getmdnpcname("#虫1_mobdead")+"::OnStart";
	donpcevent getmdnpcname("#虫1_timer")+"::OnStart";
	announce "アイリス : この辺りのフェイスワームは周りに幼虫がたくさんいるみたい。", 0x9, 0x00ffff, 0x190, 18, 0, 0;
	end;
OnTimer3000:
	announce "アイリス : くぼみごとに幼虫の数は違うみたいだけど……できるだけ近寄らないようにね！", 0x9, 0x00ffff, 0x190, 18, 0, 0;
	end;
}
1@face.gat,129,97,3	script	アイリス#1	666,{
	cutin "H_IRIS02.bmp", 2;
	mes "[アイリス]";
	mes "ケイオスは信じられる仲間よ。";
	mes "まあ、マグナムブレイクしか";
	mes "使えないんだけど……。";
	close2;
	cutin "H_IRIS02.bmp", 255;
	end;
OnTalk1:
	unittalk "アイリス : だけど戦闘が長びくと皮にキズが付くのよね～。一言でいえば使い物にならなくなっちゃうの。";
	end;
OnTalk2:
	unittalk "アイリス : 手慣れたハンターたちは素早く正確に上等な皮を取る事ができるらしいよ。";
	end;
OnTalk3:
	unittalk "アイリス : ケイオスも自信あるよね？";
	end;
OnTalk4:
	unittalk "アイリス : まったく……！　使えないケイオス。";
	end;
OnTalk5:
	unittalk "アイリス : ケイオス!?　またそうやって一人で先走って……待ちなさい！";
	end;
}

1@face.gat,1,1,0	script	#虫1_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@face.gat");
	set '@label$,getmdnpcname("#虫1_mobdead")+"::OnKilled";
	set '@user,getmapusers('@map$);
	areamonster '@map$,111,287,121,297,"フェイスワーム",2528,3+'@user,'@label$;
	areamonster '@map$,158,234,168,244,"フェイスワーム",2528,2+'@user*2,'@label$;
	areamonster '@map$,198,281,208,291,"フェイスワーム",2528,2+'@user*2,'@label$;
	areamonster '@map$,94,201,104,211,"フェイスワーム",2528,3+'@user,'@label$;
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@face.gat"),getmdnpcname("#虫1_mobdead")+"::OnKilled");
	if('@count <= 0) {
		donpcevent getmdnpcname("#ボス虫1")+"::OnStart";
	}
	else
		announce "‐あと" +'@count+ "匹‐",0x9,0xffffff,0x190,36;
	end;
}

1@face.gat,1,2,0	script	#虫1_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3600000:
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,1,3,0	script	#ボス虫1	139,{
OnStart:
	if('mob) end;
	announce "アイリス : フェイスワームが逃げ始めた！　って、なにか巨大な影がこっちに向かってきてるよ！", 0x9, 0x00ffff, 0x190, 20, 0, 0;
	set 'mob,callmonster(getmdmapname("1@face.gat"),165,270,"ダークフェイスワーム#2",2530,getmdnpcname("#ボス虫1")+"::OnKilled");
	setmobhp 'mob,2600000+getmapusers(getmdmapname("1@face.gat"))*200000;
	end;
OnKilled:
	set 'mob,0;
	announce "アイリス : 南の方から大きな音が聞こえたよ。南にいけば次の場所の手がかりがあるかも！", 0x9, 0xffffff, 0x190, 18, 0, 0;
	hideoffnpc getmdnpcname("#虫2褒賞");
	hideoffnpc getmdnpcname("#虫2入口");
	end;
}

1@face.gat,139,100,0	script	#虫2入口	45,2,2,{
	if(BaseLevel < 160)
		getexp 10000000,0;
	else
		getexp 20000000,0;
	warp getmdmapname("1@face.gat"),155,113;
	end;
}

1@face.gat,153,113,7	script	ケイオス#2	683,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		// 未調査
		mes "[ケイオス]";
		mes "今はお前らの代表者と";
		mes "話してる途中だから";
		mes "待っててくれるか？";
		close2;
		cutin "H_CHAOS01.bmp", 255;
		end;
	}
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "お前ら、随分と手慣れているな。";
	mes "だが、油断するなよ。";
	mes "この峡谷は、これまで以上に危険だ。";
	unittalk "ケイオス : お前ら、随分と手慣れているな。だが、油断するなよ。この峡谷は、これまで以上に危険だ。";
	next;
	cutin "H_IRIS01.bmp", 2;
	mes "[アイリス]";
	mes "ここ、何か嫌だな……。";
	mes "ねえ、早く行こうよケイオス。";
	donpcevent getmdnpcname("アイリス#2")+"::OnTalk1";
	next;
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "まあ、そういう事だから";
	mes "俺たちは先に行くぜ。";
	mes "ついてくるなら気をつけろよ。";
	unittalk "ケイオス : まあ、そういう事だから俺たちは先に行くぜ。ついてくるなら気をつけろよ。";
	close2;
	cutin "H_CHAOS01.bmp", 255;
	hideonnpc getmdnpcname("ケイオス#2");
	hideonnpc getmdnpcname("アイリス#2");
	viewpoint 1, 182, 127, 1, 0xFF8000;
	viewpoint 1, 166, 210, 2, 0xFF8000;
	viewpoint 1, 315, 335, 3, 0xFF8000;
	viewpoint 1, 221, 317, 4, 0xFF8000;
	donpcevent getmdnpcname("#虫2_mobdead")+"::OnStart";
	donpcevent getmdnpcname("#虫2_timer")+"::OnStart";
	donpcevent getmdnpcname("#猛毒泥_timer")+"::OnStart";
	end;
}
1@face.gat,160,113,1	script	アイリス#2	666,{
	end;
OnTalk1:
	unittalk "アイリス : ここ、何か嫌だな……。ねえ、早く行こうよケイオス。";
	end;
}

1@face.gat,1,1,0	script	#虫2_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@face.gat");
	set '@label$,getmdnpcname("#虫2_mobdead")+"::OnKilled";
	set '@user,getmapusers('@map$);
	areamonster '@map$,177,122,187,132,"フェイスワーム",2528,3+'@user,'@label$;
	areamonster '@map$,161,205,171,215,"フェイスワーム",2528,3+'@user,'@label$;
	areamonster '@map$,310,330,320,340,"フェイスワーム",2528,2+'@user*2,'@label$;
	areamonster '@map$,216,312,226,322,"フェイスワーム",2528,2+'@user*2,'@label$;
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@face.gat"),getmdnpcname("#虫2_mobdead")+"::OnKilled");
	if('@count <= 0) {
		donpcevent getmdnpcname("#ボス虫2")+"::OnStart";
		donpcevent getmdnpcname("#ボス虫2_bc")+"::OnStart";
	}
	else
		announce "‐あと" +'@count+ "匹‐",0x9,0xffffff,0x190,36;
	end;
}

1@face.gat,1,2,0	script	#虫2_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3600000:
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,1,3,0	script	#ボス虫2	139,{
OnStart:
	if('mob) end;
	announce "アイリス : フェイスワームが逃げ始めた！　って、なにか巨大な影がこっちに向かってきてるよ！", 0x9, 0x00ffff, 0x190, 20, 0, 0;
	set 'mob,callmonster(getmdmapname("1@face.gat"),277,305,"ダークフェイスワーム#3",2530,getmdnpcname("#ボス虫2")+"::OnKilled");
	setmobhp 'mob,2600000+getmapusers(getmdmapname("1@face.gat"))*200000;
	set 'mobmax,getmobhp('mob);
	end;
OnKilled:
	set 'mob,0;
	donpcevent getmdnpcname("#ボス虫2_bc")+"::OnStop";
	announce "アイリス : 南の方から石が崩れ落ちる音が聞こえた！　いってみよう！", 0x9, 0xffffff, 0x190, 18, 0, 0;
	hideoffnpc getmdnpcname("#虫3褒賞");
	hideoffnpc getmdnpcname("#虫3入口");
	end;
}

1@face.gat,1,4,0	script	#ボス虫2_bc	139,{
OnStart:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
OnTimer8000:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#ボス虫2"));
	set '@maxhp,getvariableofnpc('mobmax,getmdnpcname("#ボス虫2"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		set '@rate,getmobhp('@boss) / '@maxhp * 100;
		if('@rate > 80) {
			setarray '@xr,3,3,3,3,1,1,1,1,-1,-1,-1,-1,-3,-3,-3,-3;
			setarray '@yr,3,1,-1,-3,3,1,-1,-3,3,1,-1,-3,3,1,-1,-3;
			for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
				monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"猛毒袋",2531,1,getmdnpcname("#ボス虫2_bc")+"::OnKilled";
			}
		}
		else {
			setarray '@xr,5,5,5,5,5,5,3,3,3,3,3,3,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-3,-3,-3,-3,-3,-3,-5,-5,-5,-5,-5,-5;
			setarray '@yr,5,3,1,-1,-3,-5,5,3,1,-1,-3,-5,5,3,1,-1,-3,-5,5,3,1,-1,-3,-5,5,3,1,-1,-3,-5,5,3,1,-1,-3,-5;
			for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
				monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"猛毒袋",2531,1,getmdnpcname("#ボス虫2_bc")+"::OnKilled";
			}
		}
	}
	end;
OnTimer16000:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#ボス虫2"));
	if('@boss) {
		set '@count,getmapmobs(getmdmapname("1@face.gat"),getmdnpcname("#ボス虫2_bc")+"::OnKilled");
		if('@count > 0) {
			announce "アイリス : ちょ、ちょっと！　ダークフェイスワームが猛毒袋を自分にふりかけて体力回復したみたい!?", 0x9, 0x66ff00, 0x190, 18, 0, 0;
			setmobhp '@boss,getmobhp('@boss)+120000;
		}
	}
	initnpctimer;
	end;
OnKilled:
	end;
}

1@face.gat,248,185,0	script	#虫3入口	45,2,2,{
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	viewpoint 2, 1, 1, 4, 0xFFFFFF;
	viewpoint 2, 1, 1, 5, 0xFFFFFF;
	viewpoint 2, 1, 1, 6, 0xFFFFFF;
	if(BaseLevel < 160)
		getexp 10000000,0;
	else
		getexp 20000000,0;
	warp getmdmapname("1@face.gat"),261,170;
	end;
}

1@face.gat,261,169,0	script	#ケイon	139,3,3,{
OnTouch:
	hideonnpc;
	initnpctimer;
	donpcevent getmdnpcname("#虫3_timer")+"::OnStart";
	donpcevent getmdnpcname("#虫3_mobdead")+"::OnStart";
	donpcevent getmdnpcname("#虫3_猛毒地帯")+"::OnStart";
	viewpoint 1, 268, 126, 1, 0xFF8000;
	end;
OnTimer3000:
	announce "ケイオス : おい、この辺りは猛毒地帯だから気を付けて進め。毒に触れないようにしろよ。", 0x9, 0xffff00, 0x190, 18, 0, 0;
	end;
OnTimer6000:
	announce "ケイオス : 俺たちは他の巣を探しているからなんかの痕跡を見つけたら知らせてくれ。", 0x9, 0xffff00, 0x190, 18, 0, 0;
	end;
OnTimer9000:
	announce "ケイオス : これは……猛毒地帯の範囲が変化しているのか？", 0x9, 0xffff00, 0x190, 18, 0, 0;
	end;
OnTimer11000:
	stopnpctimer;
	announce "ケイオス : 気をつけろ！　猛毒地帯の影響を受けない場所を探して戦え！", 0x9, 0xffff00, 0x190, 18, 0, 0;
	end;
}

1@face.gat,1,1,0	script	#虫3_猛毒地帯	139,{
OnStart:
OnTimer30000:
	initnpctimer;
	killmonster getmdmapname("1@face.gat"),getmdnpcname("#虫3_猛毒地帯")+"::OnKilled";
	for(set '@i,0;'@i<40;set '@i,'@i+5) {
		for(set '@j,0;'@j<40;set '@j,'@j+5) {
			monster getmdmapname("1@face.gat"),249+'@i,106+'@j,"猛毒袋",2536,1,getmdnpcname("#虫3_猛毒地帯")+"::OnKilled";
		}
	}
	end;
OnStop:
	stopnpctimer;
	end;
OnKilled:
	end;
}

1@face.gat,1,1,0	script	#虫3_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@face.gat");
	set '@label$,getmdnpcname("#虫3_mobdead")+"::OnKilled";
	set '@user,getmapusers('@map$);
	areamonster '@map$,258,116,278,136,"フェイスワーム",2528,9+'@user,'@label$;
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	set '@count,getmapmobs(getmdmapname("1@face.gat"),getmdnpcname("#虫3_mobdead")+"::OnKilled");
	if('@count <= 0) {
		donpcevent getmdnpcname("#ボス虫3")+"::OnStart";
		donpcevent getmdnpcname("#ボス虫3_bc")+"::OnStart";
	}
	else
		announce "‐あと" +'@count+ "匹‐",0x9,0xffffff,0x190,36;
	end;
}

1@face.gat,1,2,0	script	#虫3_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3600000:
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,1,3,0	script	#ボス虫3	139,{
OnStart:
	if('mob) end;
	announce "アイリス : 西の方から何かの叫び声が聞こえる……。見に行ってみよう。", 0x9, 0xffffff, 0x190, 20, 0, 0;
	set 'mob,callmonster(getmdmapname("1@face.gat"),213,110,"ダークフェイスワーム#4",2530,getmdnpcname("#ボス虫3")+"::OnKilled");
	setmobhp 'mob,2600000+getmapusers(getmdmapname("1@face.gat"))*200000;
	set 'mobmax,getmobhp('mob);
	end;
OnKilled:
	set 'mob,0;
	donpcevent getmdnpcname("#ボス虫3_bc")+"::OnStop";
	announce "アイリス : 石が崩れ落ちる音が聞こえた……。他の通路がみつかったみたい。", 0x9, 0xffffff, 0x190, 18, 0, 0;
	hideoffnpc getmdnpcname("#虫4褒賞");
	hideoffnpc getmdnpcname("#虫4入口");
	end;
}

1@face.gat,1,4,0	script	#ボス虫3_bc	139,{
OnStart:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
OnTimer15000:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#ボス虫3"));
	set '@maxhp,getvariableofnpc('mobmax,getmdnpcname("#ボス虫3"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		set '@rate,getmobhp('@boss) / '@maxhp * 100;
		if('@rate > 80) {
			setarray '@xr,5,5,5,0,0,0,-5,-5,-5;
			setarray '@yr,5,0,-5,5,0,-5,5,0,-5;
			for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
				monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"#毒溜まり",2536,1,getmdnpcname("#ボス虫3_bc")+"::OnKilled";
			}
		}
		else {
			setarray '@xr,5,5,5,0,0,0,-5,-5,-5;
			setarray '@yr,5,0,-5,5,0,-5,5,0,-5;
			for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
				monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"#毒溜まり",2536,1,getmdnpcname("#ボス虫3_bc")+"::OnKilled";
			}
		}
	}
	initnpctimer;
	end;
OnKilled:
	end;
}

1@face.gat,204,122,0	script	#虫4入口	45,2,2,{
	if(BaseLevel < 160)
		getexp 10000000,0;
	else
		getexp 20000000,0;
	warp getmdmapname("1@face.gat"),210,145;
	end;
}

1@face.gat,213,147,0	script	#ケイon2	139,3,3,{
OnTouch:
	hideonnpc;
	initnpctimer;
	end;
OnTimer1000:
	donpcevent getmdnpcname("ケイオス#4")+"::OnTalk1";
	end;
OnTimer4000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk1";
	end;
OnTimer6000:
	donpcevent getmdnpcname("ケイオス#4")+"::OnTalk2";
	end;
OnTimer9000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk2";
	end;
OnTimer12000:
	donpcevent getmdnpcname("ケイオス#4")+"::OnTalk3";
	end;
OnTimer17000:
	hideonnpc getmdnpcname("ケイオス#4");
	end;
OnTimer20000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk3";
	end;
OnTimer27000:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk1";
	end;
OnTimer29000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk4";
	end;
OnTimer31000:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk2";
	end;
OnTimer31200:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk3";
	end;
OnTimer31400:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk4";
	end;
OnTimer31600:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk5";
	end;
OnTimer31800:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk6";
	end;
OnTimer32000:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk7";
	end;
OnTimer32200:
	donpcevent getmdnpcname("ケイオス#5")+"::OnTalk8";
	end;
OnTimer37000:
	hideoffnpc getmdnpcname("ケイオス#4");
	end;
OnTimer40000:
	donpcevent getmdnpcname("ケイオス#4")+"::OnTalk4";
	end;
OnTimer43000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk5";
	end;
OnTimer46000:
	donpcevent getmdnpcname("ケイオス#4")+"::OnTalk5";
	end;
OnTimer52000:
	hideonnpc getmdnpcname("ケイオス#4");
	end;
OnTimer53000:
	donpcevent getmdnpcname("アイリス#4")+"::OnTalk6";
	misceffect 1021, getmdnpcname("ケイオス#5");
	misceffect 247, getmdnpcname("ケイオス#5");
	end;
OnTimer58000:
	hideonnpc getmdnpcname("アイリス#4");
	end;
OnTimer67000:
	donpcevent getmdnpcname("#女王虫4")+"::OnStart";
	donpcevent getmdnpcname("#女王虫4_timer")+"::OnStart";
	donpcevent getmdnpcname("#虫3_猛毒地帯")+"::OnStop";
	end;
OnTimer77000:
	stopnpctimer;
	donpcevent getmdnpcname("#女王虫4_bc")+"::OnStart";
	end;
}

1@face.gat,213,153,6	script	ケイオス#5	683,{
	end;
OnTalk1:
	unittalk "ケイオス : うわああ！　何だこれ！";
	end;
OnTalk2:
	unittalk "ケイオス : う";
	end;
OnTalk3:
	unittalk "ケイオス : うあ";
	end;
OnTalk4:
	unittalk "ケイオス : うわあ";
	end;
OnTalk5:
	unittalk "ケイオス : うわああ";
	end;
OnTalk6:
	unittalk "ケイオス : うわあああ";
	end;
OnTalk7:
	unittalk "ケイオス : うわああああ";
	end;
OnTalk8:
	unittalk "ケイオス : うわあああああ!!";
	end;
}

1@face.gat,208,149,7	script	ケイオス#4	683,{
	cutin "H_CHAOS01.bmp", 2;
	mes "[ケイオス]";
	mes "こいつは本当に変な穴だな。";
	close2;
	cutin "H_CHAOS01.bmp", 255;
	end;
OnTalk1:
	unittalk "ケイオス : アイリス、この穴が何かわかるか？";
	end;
OnTalk2:
	unittalk "ケイオス : 仕方ない、俺が下まで降りてみる。";
	end;
OnTalk3:
	unittalk "ケイオス : 大丈夫、すぐに戻ってくる。";
	end;
OnTalk4:
	unittalk "ケイオス : あぶねぇ、もうちょっとでエサになるところだった。";
	end;
OnTalk5:
	unittalk "ケイオス : ああ、怒り狂っている女王フェイスワームが登って来てるんだ。かなり怒っているみたいだから一旦隠れよう。";
	end;
}

1@face.gat,220,149,1	script	アイリス#4	666,{
	cutin "H_IRIS01.bmp", 2;
	mes "[アイリス]";
	mes "怪しい気配がする……。";
	mes "ここは危ないよ！";
	close2;
	cutin "H_IRIS01.bmp", 255;
	end;
OnTalk1:
	unittalk "アイリス : う～ん、フェイスワームの巣としては大きすぎるし……。";
	end;
OnTalk2:
	unittalk "アイリス : ケイオス!?　危ないよ！";
	end;
OnTalk3:
	unittalk "アイリス : ああ、あのバカケイオス……。";
	end;
OnTalk4:
	unittalk "アイリス : ケイオス！　どうしたの!?";
	end;
OnTalk5:
	unittalk "アイリス : 何があったの!?";
	end;
OnTalk6:
	unittalk "アイリス : この……バカケイオス！";
	end;
}

1@face.gat,1,2,0	script	#女王虫4_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3600000:
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,1,3,0	script	#女王虫4	139,{
OnStart:
	if('mob) end;
	set 'users,getmapusers(getmdmapname("1@face.gat"));
	set 'mob,callmonster(getmdmapname("1@face.gat"),213,153,"女王フェイスワーム",2529,getmdnpcname("#女王虫4")+"::OnKilled");
	setmobhp 'mob,26000000+'users*2000000;
	set 'mobmax,getmobhp('mob);
	set 'oldhp,'mobmax;
	end;
OnSpawn:
	if('mob) {
		set 'hp,getmobhp('mob);
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		if('oldhp - 'hp > ('users + 7) * 400000) {
			announce "アイリス : 傷ついた女王フェイスワームが狂暴化した!!　さっき以上に攻撃力が増してるから気をつけて！", 0x9, 0xff3333, 0x190, 15, 0, 0;
			set '@mobid,2532;
		}
		else if( (('@x < 190) || ('@x > 230)) || (('@y < 135) || ('@y > 175)) ) {
			announce "アイリス : 巣から離れすぎだよ！　巣から離れすぎると、女王フェイスワームが落ち着くまでは凶暴になるから気をつけて！", 0x9, 0xff3333, 0x190, 15, 0, 0;
			set '@mobid,2532;
		}
		else {
			switch(rand(5)) {
			case 0:
				announce "アイリス : まっず……。女王フェイスワームが地属性に脱皮したみたい……。", 0x9, 0x55ff00, 0x190, 18, 0, 0;
				set '@mobid,2533;
				break;
			case 1:
				announce "アイリス : まっず……。女王フェイスワームが水属性に脱皮したみたい……。", 0x9, 0x9999ff, 0x190, 18, 0, 0;
				set '@mobid,2534;
				break;
			case 2:
				announce "アイリス : まっず……。女王フェイスワームが風属性に脱皮したみたい……。", 0x9, 0xffff00, 0x190, 18, 0, 0;
				set '@mobid,2535;
				break;
			case 3:
			default:
				announce "アイリス : 女王フェイスワームの姿が元に戻ったよ！", 0x9, 0xffffff, 0x190, 18, 0, 0;
				set '@mobid,2529;
				break;
			}
		}
		set 'oldhp,'hp;
		set '@dummy,removemonster(getvariableofnpc('mob,getmdnpcname("#女王虫4")));
		set 'mob,callmonster(getmdmapname("1@face.gat"),'@x,'@y,"女王フェイスワーム",'@mobid,getmdnpcname("#女王虫4")+"::OnKilled");
		setmobhp 'mob,'hp;
	}
	end;
OnDamage:
	if('mob) {
		set 'hp,getmobhp('mob);
		set '@users,getmapusers(getmdmapname("1@face.gat"));
		set '@damage,10000 * rand(20,('@users+7)*25);
		set '@facehp,'hp - '@damage;
		if('facehp < 5000000)
			set '@facehp,5000000;
		setmobhp 'mob,'@facehp;
		announce "アイリス : さすがケイオス！　攻撃は、女王フェイスワームに効いてるみたい！", 0x9, 0xffffff, 0x190, 18, 0, 0;
	}
	end;
OnKilled:
	set 'mob,0;
	stopnpctimer getmdnpcname("#ケイon2");
	donpcevent getmdnpcname("#女王虫4_bc")+"::OnStop";
	hideoffnpc getmdnpcname("#ケイon3");
	hideoffnpc getmdnpcname("ケイオス#6");
	hideoffnpc getmdnpcname("アイリス#6");
	hideoffnpc getmdnpcname("大商人の箱#1");
	end;
}

1@face.gat,1,4,0	script	#女王虫4_bc	139,{
OnStop:
	stopnpctimer;
	end;
OnStart:
	initnpctimer;
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	set '@maxhp,getvariableofnpc('mobmax,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		switch(rand(1,3)) {
		case 1:
			set '@rate,getmobhp('@boss) / '@maxhp * 100;
			if('@rate > 70) {
				setarray '@xr,-3,-3,3,3;
				setarray '@yr,-3,3,-3,3;
				for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
					monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"#毒溜まり",2536,1,getmdnpcname("#女王虫4_bc")+"::OnKilled";
				}
			}
			else {
				setarray '@xr,5,5,5,0,0,0,-5,-5,-5;
				setarray '@yr,5,0,-5,5,0,-5,5,0,-5;
				for(set '@i,0;'@i<getarraysize('@xr);set '@i,'@i+1) {
					monster getmdmapname("1@face.gat"),'@x+'@xr['@i],'@y+'@yr['@i],"#毒溜まり",2536,1,getmdnpcname("#女王虫4_bc")+"::OnKilled";
				}
			}
		case 2:
		case 3:
		}
	}
	end;
OnTimer5000:
	donpcevent getmdnpcname("#女王虫4")+"::OnSpawn";
	end;
OnTimer6000:
	set 'chaos,rand(6);
	switch('chaos) {
	case 0:
		announce "ケイオス : おい！　北の方に奴を誘え！　俺の一撃を見せてやる！", 0x9, 0xff44aa, 0x190, 18, 0, 0;
		donpcevent getmdnpcname("ケイオス#北")+"::OnStart";
		hideoffnpc getmdnpcname("#ケイ_北");
		hideoffnpc getmdnpcname("ケイオス#北");
		end;
	case 1:
		announce "ケイオス : おい！　南の方に奴を誘え！　俺の一撃を見せてやる！", 0x9, 0xff44aa, 0x190, 18, 0, 0;
		donpcevent getmdnpcname("ケイオス#南")+"::OnStart";
		hideoffnpc getmdnpcname("#ケイ_南");
		hideoffnpc getmdnpcname("ケイオス#南");
		end;
	case 2:
		announce "ケイオス : おい！　東の方に奴を誘え！　俺の一撃を見せてやる！", 0x9, 0xff44aa, 0x190, 18, 0, 0;
		donpcevent getmdnpcname("ケイオス#東")+"::OnStart";
		hideoffnpc getmdnpcname("#ケイ_東");
		hideoffnpc getmdnpcname("ケイオス#東");81
		end;
	case 3:
		announce "ケイオス : おい！　西の方に奴を誘え！　俺の一撃を見せてやる！", 0x9, 0xff44aa, 0x190, 18, 0, 0;
		donpcevent getmdnpcname("ケイオス#西")+"::OnStart";
		hideoffnpc getmdnpcname("#ケイ_西");
		hideoffnpc getmdnpcname("ケイオス#西");
		end;
	case 4: case 5:
		// dummy
	}
	end;
OnTimer21000:
	switch('chaos) {
	case 0:
		donpcevent getmdnpcname("ケイオス#北")+"::OnStop";
		hideonnpc getmdnpcname("#ケイ_北");
		hideonnpc getmdnpcname("ケイオス#北");
		end;
	case 1:
		donpcevent getmdnpcname("ケイオス#南")+"::OnStop";
		hideonnpc getmdnpcname("#ケイ_南");
		hideonnpc getmdnpcname("ケイオス#南");
		end;
	case 2:
		donpcevent getmdnpcname("ケイオス#東")+"::OnStop";
		hideonnpc getmdnpcname("#ケイ_東");
		hideonnpc getmdnpcname("ケイオス#東");
		end;
	case 3:
		donpcevent getmdnpcname("ケイオス#西")+"::OnStop";
		hideonnpc getmdnpcname("#ケイ_西");
		hideonnpc getmdnpcname("ケイオス#西");
		end;
	case 4: case 5:
		// dummy
	}
	end;
OnTimer23000:
	killmonster getmdmapname("1@face.gat"),getmdnpcname("#女王虫4_bc")+"::OnKilled";
	end;
OnTimer25000:
	donpcevent getmdnpcname("#女王虫4_bc")+"::OnStart";
	end;
OnKilled:
	// dummy
	end;
}

1@face.gat,214,172,0	script	#ケイ_北	139,2,2,{
OnTouch:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		if( (('@x > 205) && ('@x < 223)) && (('@y > 163) && ('@y < 181)) ) {
			misceffect 17,getmdnpcname("#ケイ_北");
			misceffect 90,getmdnpcname("#ケイ_北");
			donpcevent getmdnpcname("#女王虫4")+"::OnDamage";
		}
		else {
			// セリフ適当
			unittalk getnpcid(getmdnpcname("ケイオス#北")),"ケイオス : もっと近くまで女王フェイスワームを連れてくるんだ！";
		}
	}
	donpcevent getmdnpcname("ケイオス#北")+"::OnStop";
	hideonnpc getmdnpcname("#ケイ_北");
	hideonnpc getmdnpcname("ケイオス#北");
	end;
}

1@face.gat,214,143,0	script	#ケイ_南	139,2,2,{
OnTouch:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		if( (('@x > 205) && ('@x < 223)) && (('@y > 134) && ('@y < 152)) ) {
			misceffect 17,getmdnpcname("#ケイ_南");
			misceffect 90,getmdnpcname("#ケイ_南");
			donpcevent getmdnpcname("#女王虫4")+"::OnDamage";
		}
		else {
			// セリフ適当
			unittalk getnpcid(getmdnpcname("ケイオス#南")),"ケイオス : もっと近くまで女王フェイスワームを連れてくるんだ！";
		}
	}
	donpcevent getmdnpcname("ケイオス#南")+"::OnStop";
	hideonnpc getmdnpcname("#ケイ_南");
	hideonnpc getmdnpcname("ケイオス#南");
	end;
}

1@face.gat,226,158,0	script	#ケイ_東	139,2,2,{
OnTouch:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		if( (('@x > 217) && ('@x < 235)) && (('@y > 149) && ('@y < 167)) ) {
			misceffect 17,getmdnpcname("#ケイ_東");
			misceffect 90,getmdnpcname("#ケイ_東");
			donpcevent getmdnpcname("#女王虫4")+"::OnDamage";
		}
		else {
			// セリフ適当
			unittalk getnpcid(getmdnpcname("ケイオス#東")),"ケイオス : もっと近くまで女王フェイスワームを連れてくるんだ！";
		}
	}
	donpcevent getmdnpcname("ケイオス#東")+"::OnStop";
	hideonnpc getmdnpcname("#ケイ_東");
	hideonnpc getmdnpcname("ケイオス#東");
	end;
}

1@face.gat,200,158,0	script	#ケイ_西	139,{
OnTouch:
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'@boss);
		if( (('@x > 191) && ('@x < 209)) && (('@y > 149) && ('@y < 167)) ) {
			misceffect 17,getmdnpcname("#ケイ_西");
			misceffect 90,getmdnpcname("#ケイ_西");
			donpcevent getmdnpcname("#女王虫4")+"::OnDamage";
		}
		else {
			// セリフ適当
			unittalk getnpcid(getmdnpcname("ケイオス#西")),"ケイオス : もっと近くまで女王フェイスワームを連れてくるんだ！";
		}
	}
	donpcevent getmdnpcname("ケイオス#西")+"::OnStop";
	hideonnpc getmdnpcname("#ケイ_西");
	hideonnpc getmdnpcname("ケイオス#西");
	end;
}

1@face.gat,214,172,5	script	ケイオス#北	683,{
	end;
OnStart:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
OnTimer1000:
	initnpctimer;
	set '@boss,getvariableofnpc('mob,getmdnpcname("#女王虫4"));
	if('@boss) {
		set '@dummy,getmapxy('@map$,'@bx,'@by,3,'@boss);
		set '@dummy,getmapxy('@map$,'@nx,'@ny,1);
		if('@nx-10 < '@bx && '@nx+10 > '@bx && '@ny-10 < '@by && '@ny+10 > '@by) {
			emotion 27;
		}
	}
	end;
}
1@face.gat,214,143,8	duplicate(ケイオス#北)	ケイオス#南	683
1@face.gat,226,158,3	duplicate(ケイオス#北)	ケイオス#東	683
1@face.gat,200,158,6	duplicate(ケイオス#北)	ケイオス#西	683

1@face.gat,212,156,0	script	#ケイon3	139,5,5,{
	end;
OnTouch:
	initnpctimer;
	end;
OnTimer3000:
	donpcevent getmdnpcname("ケイオス#6")+"::OnTalk1";
	end;
OnTimer6000:
	donpcevent getmdnpcname("アイリス#6")+"::OnTalk1";
	end;
OnTimer9000:
	donpcevent getmdnpcname("ケイオス#6")+"::OnTalk2";
	end;
OnTimer12000:
	donpcevent getmdnpcname("アイリス#6")+"::OnTalk2";
	end;
OnTimer15000:
	donpcevent getmdnpcname("ケイオス#6")+"::OnTalk3";
	end;
OnTimer18000:
	donpcevent getmdnpcname("ケイオス#6")+"::OnTalk4";
	end;
OnTimer21000:
	donpcevent getmdnpcname("アイリス#6")+"::OnTalk3";
	end;
OnTimer24000:
	donpcevent getmdnpcname("ケイオス#6")+"::OnTalk5";
	end;
OnTimer26000:
	stopnpctimer;
	hideonnpc getmdnpcname("アイリス#6");
	hideonnpc getmdnpcname("ケイオス#6");
	hideoffnpc getmdnpcname("次元移動機#6");
	end;
}

1@face.gat,209,159,6	script	ケイオス#6	683,{
	end;
OnTalk1:
	unittalk "ケイオス : ふう……長い闘いだったな。";
	end;
OnTalk2:
	unittalk "ケイオス : しょうがない。今日はこの辺で撤収しよう。";
	end;
OnTalk3:
	unittalk "ケイオス : それにしても、お前らの実力は凄かったな。";
	end;
OnTalk4:
	unittalk "ケイオス : 今日の狩りが成功したのはお前達のお蔭だ。";
	end;
OnTalk5:
	unittalk "ケイオス : ああ、悪い悪い。戻るか。それじゃな！";
	end;
}

1@face.gat,220,159,4	script	アイリス#6	666,{
	end;
OnTalk1:
	unittalk "アイリス : だけど私達が探している奴じゃなかったみたい。";
	end;
OnTalk2:
	unittalk "アイリス : そうね、お目当てのフェイスワームに会えなかったのは残念だけど、みんな無事でよかった。";
	end;
OnTalk3:
	unittalk "アイリス : ケイオス、私疲れちゃったよ。そろそろ町に戻らない？";
	end;
}

1@face.gat,215,159,4	script	次元移動機#6	10007,{
	mes "[次元移動機]";
	mes "ここでの時間は終了になります。";
	mes "外に出るかもう少し見回る事が";
	mes "できますが";
	mes "どうしますか？";
	next;
	if(select("やめる","外に出る") == 1)
		close;
	if(BaseLevel < 160)
		getexp 20000000,0;
	else
		getexp 40000000,0;
	warp "dali.gat",85,62;
	end;
}

1@face.gat,155,82,3	script	#虫1褒賞	10005,15,15,{
	donpcevent getmdnpcname("#虫0_timer")+"::OnStop";
	set '@time,getnpctimer(0,getmdnpcname("#虫0_timer"))/1000;
	announce "今回の戦闘に所要された時間は" +'@time/60+ "分" +'@time%60+ "秒です。", 0x9, 0xffff33, 0x190, 12, 0, 0;
	misceffect 10;
	hideonnpc;
	setarray '@card,4700,4710,4720,4730,4740,4750,4701,4711,4721,4731,4741,4751,4702,4712,4722,4732,4742,4752,4703,4713,4723,4733,4743,4753,4704,4714,4724,4734,4744,4754;
	if('@time <= 121){
		if(rand(1,100) <= 70)
			dropitem2 getmdmapname("1@face.gat"),155+rand(-2,2),82+rand(-2,2),20717,1,0,0,rand(2,5),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
		else
			dropitem2 getmdmapname("1@face.gat"),155+rand(-2,2),82+rand(-2,2),rand(20717,20718),1,0,0,rand(4,6),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	else {
		if(rand(1,100) <= 70) dropitem2 getmdmapname("1@face.gat"),155+rand(-2,2),82+rand(-2,2),20717,1,0,0,rand(0,3),0,0,0,0,'@card[rand(getarraysize('@card))];
		else dropitem2 getmdmapname("1@face.gat"),155+rand(-2,2),82+rand(-2,2),rand(20717,20718),1,0,0,rand(2,4),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	end;
OnTouch:
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 1, 127, 95, 2, 0x32CD32;
	end;
}

1@face.gat,162,271,3	script	#虫2褒賞	10005,15,15,{
	set '@time,getnpctimer(0,getmdnpcname("#虫1_timer"))/1000;
	donpcevent getmdnpcname("#虫1_timer")+"::OnStop";
	announce "今回の戦闘に所要された時間は" +'@time/60+ "分" +'@time%60+ "秒です。", 0x9, 0xffff33, 0x190, 12, 0, 0;
	misceffect 10;
	hideonnpc;
	setarray '@card,4700,4710,4720,4730,4740,4750,4701,4711,4721,4731,4741,4751,4702,4712,4722,4732,4742,4752,4703,4713,4723,4733,4743,4753,4704,4714,4724,4734,4744,4754;
	if('@time <= 121){
		if(rand(1,100) <= 70)
			dropitem2 getmdmapname("1@face.gat"),162+rand(-2,2),271+rand(-2,2),20717,1,0,0,rand(2,5),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
		else
			dropitem2 getmdmapname("1@face.gat"),162+rand(-2,2),271+rand(-2,2),rand(20717,20718),1,0,0,rand(4,6),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	else {
		if(rand(1,100) <= 70) dropitem2 getmdmapname("1@face.gat"),162+rand(-2,2),271+rand(-2,2),20717,1,0,0,rand(0,3),0,0,0,0,'@card[rand(getarraysize('@card))];
		else dropitem2 getmdmapname("1@face.gat"),162+rand(-2,2),271+rand(-2,2),rand(20717,20718),1,0,0,rand(2,4),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	dropitem getmdmapname("1@face.gat"),162+rand(-2,2),271+rand(-2,2),7228,getmapusers(getmdmapname("1@face.gat")),0;
	end;
OnTouch:
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	viewpoint 2, 1, 1, 4, 0xFFFFFF;
	viewpoint 2, 1, 1, 5, 0xFFFFFF;
	viewpoint 1, 139, 100, 6, 0x32CD32;
	end;
}

1@face.gat,278,308,3	script	#虫3褒賞	10005,15,15,{
	donpcevent getmdnpcname("#虫2_timer")+"::OnStop";
	set '@time,getnpctimer(0,getmdnpcname("#虫2_timer"))/1000;
	announce "今回の戦闘に所要された時間は" +'@time/60+ "分" +'@time%60+ "秒です。", 0x9, 0xffff33, 0x190, 12, 0, 0;
	misceffect 10;
	hideonnpc;
	setarray '@card,4700,4710,4720,4730,4740,4750,4701,4711,4721,4731,4741,4751,4702,4712,4722,4732,4742,4752,4703,4713,4723,4733,4743,4753,4704,4714,4724,4734,4744,4754;
	if('@time <= 121){
		if(rand(1,100) <= 70)
			dropitem2 getmdmapname("1@face.gat"),278+rand(-2,2),308+rand(-2,2),20717,1,0,0,rand(2,5),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
		else
			dropitem2 getmdmapname("1@face.gat"),278+rand(-2,2),308+rand(-2,2),rand(20717,20718),1,0,0,rand(4,6),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	else {
		if(rand(1,100) <= 70) dropitem2 getmdmapname("1@face.gat"),278+rand(-2,2),308+rand(-2,2),20717,1,0,0,rand(0,3),0,0,0,0,'@card[rand(getarraysize('@card))];
		else dropitem2 getmdmapname("1@face.gat"),278+rand(-2,2),308+rand(-2,2),rand(20717,20718),1,0,0,rand(2,4),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	end;
OnTouch:
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	viewpoint 2, 1, 1, 4, 0xFFFFFF;
	viewpoint 2, 1, 1, 5, 0xFFFFFF;
	viewpoint 1, 248, 185, 6, 0x32CD32;
	end;
}

1@face.gat,214,108,3	script	#虫4褒賞	10005,{
	donpcevent getmdnpcname("#猛毒泥_timer")+"::OnStop";
	donpcevent getmdnpcname("#虫3_timer")+"::OnStop";
	set '@time,getnpctimer(0,getmdnpcname("#虫3_timer"))/1000;
	announce "今回の戦闘に所要された時間は" +'@time/60+ "分" +'@time%60+ "秒です。", 0x9, 0xffff33, 0x190, 12, 0, 0;
	misceffect 10;
	hideonnpc;
	setarray '@card,4700,4710,4720,4730,4740,4750,4701,4711,4721,4731,4741,4751,4702,4712,4722,4732,4742,4752,4703,4713,4723,4733,4743,4753,4704,4714,4724,4734,4744,4754;
	if('@time <= 111){
		if(rand(1,100) <= 70)
			dropitem2 getmdmapname("1@face.gat"),214+rand(-2,2),108+rand(-2,2),20717,1,0,0,rand(2,5),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
		else
			dropitem2 getmdmapname("1@face.gat"),214+rand(-2,2),108+rand(-2,2),rand(20717,20718),1,0,0,rand(4,6),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	else {
		if(rand(1,100) <= 70) dropitem2 getmdmapname("1@face.gat"),214+rand(-2,2),108+rand(-2,2),20717,1,0,0,rand(0,3),0,0,0,0,'@card[rand(getarraysize('@card))];
		else dropitem2 getmdmapname("1@face.gat"),214+rand(-2,2),108+rand(-2,2),rand(20717,20718),1,0,0,rand(2,4),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
	}
	dropitem getmdmapname("1@face.gat"),214+rand(-2,2),108+rand(-2,2),7444,getmapusers(getmdmapname("1@face.gat")),0;
	end;
OnTouch:
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 1, 204, 122, 3, 0x32CD32;
	end;
}

1@face.gat,61,132,5		script	柔らかいくぼみ#1	557,5,5,{
	set '@num,rand(1,3);
	set '@dummy,getmapxy('@map$,'@x,'@y,1);
	misceffect 124;
	hideonnpc;
	monster '@map$,'@x,'@y,"フェイスワームの幼虫",2541,'@num,getmdnpcname(strnpcinfo(0))+"::OnKilled";
	end;
}
1@face.gat,62,195,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#2	557,5,5
1@face.gat,66,94,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#3	557,5,5
1@face.gat,68,265,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#4	557,5,5
1@face.gat,68,108,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#5	557,5,5
1@face.gat,72,202,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#6	557,5,5
1@face.gat,75,73,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#7	557,5,5
1@face.gat,76,241,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#8	557,5,5
1@face.gat,79,274,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#9	557,5,5
1@face.gat,79,119,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#10	557,5,5
1@face.gat,97,59,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#11	557,5,5
1@face.gat,108,74,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#16	557,5,5
1@face.gat,171,62,5		duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#38	557,5,5

1@face.gat,114,282,5	script	柔らかいくぼみ#ex1	557,5,5,{
	set '@num,rand(3,9);
	set '@dummy,getmapxy('@map$,'@x,'@y,1);
	misceffect 124;
	hideonnpc;
	monster '@map$,'@x,'@y,"フェイスワームの幼虫",2541,'@num,getmdnpcname(strnpcinfo(0))+"::OnKilled";
	end;
}

1@face.gat,131,285,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex2	557,5,5
1@face.gat,107,264,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex3	557,5,5
1@face.gat,114,269,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex4	557,5,5
1@face.gat,146,245,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex5	557,5,5
1@face.gat,147,235,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex6	557,5,5
1@face.gat,150,227,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex7	557,5,5
1@face.gat,154,248,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex8	557,5,5
1@face.gat,161,248,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex9	557,5,5
1@face.gat,172,252,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex10	557,5,5
1@face.gat,179,255,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex11	557,5,5

1@face.gat,189,274,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex16	557,5,5
1@face.gat,189,276,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex17	557,5,5
1@face.gat,186,279,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex18	557,5,5
1@face.gat,190,282,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex19	557,5,5
1@face.gat,195,285,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex20	557,5,5

1@face.gat,206,275,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex26	557,5,5

1@face.gat,106,193,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex28	557,5,5
1@face.gat,110,200,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex29	557,5,5
1@face.gat,110,210,5	duplicate(柔らかいくぼみ#ex1)	柔らかいくぼみ#ex30	557,5,5
1@face.gat,158,138,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#33	557,5,5
1@face.gat,158,163,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#34	557,5,5
1@face.gat,171,149,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#39	557,5,5
1@face.gat,172,173,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#40	557,5,5
1@face.gat,168,194,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#36	557,5,5
1@face.gat,183,185,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#43	557,5,5
1@face.gat,194,192,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#45	557,5,5
1@face.gat,196,207,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#46	557,5,5
1@face.gat,229,200,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#50	557,5,5
1@face.gat,232,271,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#51	557,5,5
1@face.gat,250,223,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#52	557,5,5
1@face.gat,254,324,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#53	557,5,5
1@face.gat,255,263,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#54	557,5,5
1@face.gat,255,320,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#55	557,5,5
1@face.gat,250,326,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#56	557,5,5
1@face.gat,229,304,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#57	557,5,5
1@face.gat,172,127,3	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#58	557,5,5
1@face.gat,186,130,3	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#59	557,5,5
1@face.gat,232,340,5	duplicate(柔らかいくぼみ#1)	柔らかいくぼみ#60	557,5,5

1@face.gat,163,130,0	script	#猛毒泥1	139,7,7,{
	set '@map$,getmdmapname("1@face.gat");
	set '@event$,getmdnpcname(strnpcinfo(0))+ "::OnKilled";
	initnpctimer;
	misceffect 124;
	hideonnpc;
	killmonster '@map$,'@event$;
	set '@val,substr(strnpcinfo(2),6,1);
	switch('@val) {
	case 1: setarray '@xy[0],167,142,15; set '@num,25; break;
	case 2: setarray '@xy[0],163,161,15; set '@num,30; break;
	case 3: setarray '@xy[0],167,185,20; set '@num,50; break;
	case 4: setarray '@xy[0],197,203,15; set '@num,30; break;
	case 5: setarray '@xy[0],227,203,20; set '@num,50; break;
	case 6: setarray '@xy[0],244,232,15; set '@num,30; break;
	case 7: setarray '@xy[0],243,259,15; set '@num,40; break;
	case 8: setarray '@xy[0],292,277,50; set '@num,50; break;
	case 9: setarray '@xy[0],248,322,50; set '@num,50; break;
	}
	areamonster '@map$,'@xy[0]-'@xy[2],'@xy[1]-'@xy[2],'@xy[0]+'@xy[2],'@xy[1]+'@xy[2],"猛毒袋",2531,'@num,'@event$;
	end;
OnTimer15000:
	stopnpctimer;
	hideoffnpc;
	end;
OnKilled:
	end;
}
1@face.gat,165,147,0	duplicate(#猛毒泥1)	#猛毒泥2	139,7,7
1@face.gat,163,166,0	duplicate(#猛毒泥1)	#猛毒泥3	139,10,10
1@face.gat,183,197,0	duplicate(#猛毒泥1)	#猛毒泥4	139,10,10
1@face.gat,202,204,0	duplicate(#猛毒泥1)	#猛毒泥5	139,5,5
1@face.gat,237,220,0	duplicate(#猛毒泥1)	#猛毒泥6	139,5,5
1@face.gat,240,258,0	duplicate(#猛毒泥1)	#猛毒泥7	139,5,5
1@face.gat,292,277,0	duplicate(#猛毒泥1)	#猛毒泥8	139,5,5
1@face.gat,248,322,0	duplicate(#猛毒泥1)	#猛毒泥9	139,5,5

1@face.gat,158,120,0	script	#猛毒泥a	139,3,3,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	monster '@map$,152,113,"猛毒袋",2531,1;
	monster '@map$,154,113,"猛毒袋",2531,1;
	monster '@map$,156,113,"猛毒袋",2531,1;
	monster '@map$,158,113,"猛毒袋",2531,1;
	monster '@map$,160,113,"猛毒袋",2531,1;
	monster '@map$,162,113,"猛毒袋",2531,1;
	monster '@map$,152,115,"猛毒袋",2531,1;
	monster '@map$,154,115,"猛毒袋",2531,1;
	monster '@map$,156,115,"猛毒袋",2531,1;
	monster '@map$,158,115,"猛毒袋",2531,1;
	monster '@map$,160,115,"猛毒袋",2531,1;
	monster '@map$,162,115,"猛毒袋",2531,1;
	monster '@map$,152,117,"猛毒袋",2531,1;
	monster '@map$,154,117,"猛毒袋",2531,1;
	monster '@map$,156,117,"猛毒袋",2531,1;
	monster '@map$,158,117,"猛毒袋",2531,1;
	monster '@map$,160,117,"猛毒袋",2531,1;
	monster '@map$,162,117,"猛毒袋",2531,1;
	end;
OnTimer30000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,248,186,0	script	#猛毒泥b	139,10,10,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	monster '@map$,238,196,"猛毒袋",2531,1;
	monster '@map$,238,197,"猛毒袋",2531,1;
	monster '@map$,239,196,"猛毒袋",2531,1;
	monster '@map$,239,197,"猛毒袋",2531,1;
	monster '@map$,240,196,"猛毒袋",2531,1;
	monster '@map$,240,197,"猛毒袋",2531,1;
	monster '@map$,241,196,"猛毒袋",2531,1;
	monster '@map$,241,197,"猛毒袋",2531,1;

	monster '@map$,247,191,"猛毒袋",2531,1;
	monster '@map$,248,191,"猛毒袋",2531,1;
	monster '@map$,249,191,"猛毒袋",2531,1;
	monster '@map$,247,192,"猛毒袋",2531,1;
	monster '@map$,248,192,"猛毒袋",2531,1;
	monster '@map$,249,192,"猛毒袋",2531,1;
	end;
OnTimer15000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,277,343,0	script	#猛毒泥c	139,5,5,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	areamonster '@map$,263,330,291,357,"猛毒袋",2531,20;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,174,133,0	script	#猛毒泥d1	139,5,5,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	monster '@map$,174,131,"猛毒袋",2531,1;
	monster '@map$,174,132,"猛毒袋",2531,1;
	monster '@map$,175,131,"猛毒袋",2531,1;
	monster '@map$,175,132,"猛毒袋",2531,1;
	monster '@map$,176,131,"猛毒袋",2531,1;
	monster '@map$,176,132,"猛毒袋",2531,1;
	monster '@map$,184,137,"猛毒袋",2531,1;
	monster '@map$,184,138,"猛毒袋",2531,1;
	monster '@map$,185,137,"猛毒袋",2531,1;
	monster '@map$,185,138,"猛毒袋",2531,1;
	monster '@map$,186,137,"猛毒袋",2531,1;
	monster '@map$,186,138,"猛毒袋",2531,1;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,182,123,0	script	#猛毒泥d2	139,3,3,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	monster '@map$,177,121,"猛毒袋",2531,1;
	monster '@map$,177,122,"猛毒袋",2531,1;
	monster '@map$,178,121,"猛毒袋",2531,1;
	monster '@map$,178,122,"猛毒袋",2531,1;
	monster '@map$,179,121,"猛毒袋",2531,1;
	monster '@map$,179,122,"猛毒袋",2531,1;
	monster '@map$,184,121,"猛毒袋",2531,1;
	monster '@map$,184,122,"猛毒袋",2531,1;
	monster '@map$,185,121,"猛毒袋",2531,1;
	monster '@map$,185,122,"猛毒袋",2531,1;
	monster '@map$,186,121,"猛毒袋",2531,1;
	monster '@map$,186,122,"猛毒袋",2531,1;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,237,299,0	script	#猛毒泥e	139,5,5,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	areamonster '@map$,228,290,246,308,"猛毒袋",2531,25;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,245,230,0	script	#猛毒泥f	139,10,10,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	monster '@map$,236,236,"猛毒袋",2531,1;
	monster '@map$,238,236,"猛毒袋",2531,1;
	monster '@map$,240,236,"猛毒袋",2531,1;
	monster '@map$,242,236,"猛毒袋",2531,1;
	monster '@map$,244,236,"猛毒袋",2531,1;
	monster '@map$,246,236,"猛毒袋",2531,1;
	monster '@map$,248,236,"猛毒袋",2531,1;
	monster '@map$,250,236,"猛毒袋",2531,1;
	monster '@map$,236,239,"猛毒袋",2531,1;
	monster '@map$,238,239,"猛毒袋",2531,1;
	monster '@map$,240,239,"猛毒袋",2531,1;
	monster '@map$,242,239,"猛毒袋",2531,1;
	monster '@map$,244,239,"猛毒袋",2531,1;
	monster '@map$,246,239,"猛毒袋",2531,1;
	monster '@map$,248,239,"猛毒袋",2531,1;
	monster '@map$,250,239,"猛毒袋",2531,1;
	monster '@map$,236,242,"猛毒袋",2531,1;
	monster '@map$,238,242,"猛毒袋",2531,1;
	monster '@map$,240,242,"猛毒袋",2531,1;
	monster '@map$,242,242,"猛毒袋",2531,1;
	monster '@map$,244,242,"猛毒袋",2531,1;
	monster '@map$,246,242,"猛毒袋",2531,1;
	monster '@map$,248,242,"猛毒袋",2531,1;
	monster '@map$,250,242,"猛毒袋",2531,1;
	monster '@map$,236,245,"猛毒袋",2531,1;
	monster '@map$,238,245,"猛毒袋",2531,1;
	monster '@map$,240,245,"猛毒袋",2531,1;
	monster '@map$,242,245,"猛毒袋",2531,1;
	monster '@map$,244,245,"猛毒袋",2531,1;
	monster '@map$,246,245,"猛毒袋",2531,1;
	monster '@map$,248,245,"猛毒袋",2531,1;
	monster '@map$,250,245,"猛毒袋",2531,1;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,249,337,0	script	#猛毒泥g	139,10,10,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	areamonster '@map$,240,325,268,348,"猛毒袋",2531,20;
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,159,194,0	script	#猛毒泥h	139,5,5,{
	set '@map$,getmdmapname("1@face.gat");
	initnpctimer;
	misceffect 124;
	hideonnpc;
	areamonster '@map$,156,201,162,207,"猛毒袋",2531,16;
	end;
OnTimer30000:
	stopnpctimer;
	hideoffnpc;
	end;
}

1@face.gat,1,1,0	script	#猛毒泥_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	set '@map$,getmdmapname("1@face.gat");
	monster '@map$,238,196,"猛毒袋",2531,1;
	monster '@map$,238,197,"猛毒袋",2531,1;
	monster '@map$,239,196,"猛毒袋",2531,1;
	monster '@map$,239,197,"猛毒袋",2531,1;
	monster '@map$,240,196,"猛毒袋",2531,1;
	monster '@map$,240,197,"猛毒袋",2531,1;
	monster '@map$,241,196,"猛毒袋",2531,1;
	monster '@map$,241,197,"猛毒袋",2531,1;
	end;
OnTimer8000:
	set '@map$,getmdmapname("1@face.gat");
	monster '@map$,247,191,"猛毒袋",2531,1;
	monster '@map$,247,192,"猛毒袋",2531,1;
	monster '@map$,248,191,"猛毒袋",2531,1;
	monster '@map$,248,192,"猛毒袋",2531,1;
	monster '@map$,249,191,"猛毒袋",2531,1;
	monster '@map$,249,192,"猛毒袋",2531,1;
	end;
OnTimer18000:
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

1@face.gat,213,155,3	script	大商人の箱#1	10005,{
	initnpctimer;
	set 'flag,'flag+1;
	misceffect 10;
	hideonnpc;
	switch('flag) {
	case 1:
		donpcevent getmdnpcname("#女王虫4_timer")+"::OnStop";
		set '@time,getnpctimer(0,getmdnpcname("#女王虫4_timer"))/1000;
		set '@time,'@time + getnpctimer(0,getmdnpcname("#虫0_timer"))/1000;
		set '@time,'@time + getnpctimer(0,getmdnpcname("#虫1_timer"))/1000;
		set '@time,'@time + getnpctimer(0,getmdnpcname("#虫2_timer"))/1000;
		set '@time,'@time + getnpctimer(0,getmdnpcname("#虫3_timer"))/1000;
		if($FacewormTime == 0 || $FacewormTime > '@time) {
			set $FacewormParty$,getpartyname(getcharid(1));
			set $FacewormTime,'@time;
			announce "パーティー名" +getpartyname(getcharid(1))+ "がフェイスワームの巣の攻略最短記録を更新しました！(" +'@time/60+ "分" +'@time%60+ "秒)", 0;
		}
		else
			announce '@time/60+ "分" +'@time%60+ "秒を記録しましたが最短記録を更新する事はできませんでした。", 0x9, 0xffff33, 0x190, 12, 0, 0;
		setarray '@card,4700,4710,4720,4730,4740,4750,4701,4711,4721,4731,4741,4751,4702,4712,4722,4732,4742,4752,4703,4713,4723,4733,4743,4753,4704,4714,4724,4734,4744,4754,4705,4715,4725,4735,4745,4755,4706,4716,4726,4736,4746,4756;
		if('@time<271){
			if(rand(100)<10)
				set '@itemid,20718;
			else
				set '@itemid,20717;
			set '@rate,rand(1,100);
			set '@amount,rand(1,100)<=20?2:1;
			if('@rate <= 20){
				for(set '@i,0; '@i<'@amount; set '@i,'@i+1) dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(9,10),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
			} else if('@rate <= 50){
				for(set '@i,0; '@i<'@amount; set '@i,'@i+1) dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(5,9),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
			} else {
				for(set '@i,0; '@i<'@amount; set '@i,'@i+1) dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(3,7),0,0,0,0,'@card[rand(getarraysize('@card))];
			}
		} else {
			if(rand(100)<5)
				set '@itemid,20718;
			else
				set '@itemid,20717;
			set '@rate,rand(1,100);
			if('@rate <= 5)	dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(9,10),0,0,rand(4853,4858),'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
			 else if('@rate <= 25) dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(5,9),0,0,0,'@card[rand(getarraysize('@card))],'@card[rand(getarraysize('@card))];
			 else if('@rate <= 60) dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(3,7),0,0,0,0,'@card[rand(getarraysize('@card))];
			 else dropitem2 getmdmapname("1@face.gat"),213+rand(-2,2),155+rand(-2,2),'@itemid,1,0,0,rand(3,9),0,0,0,0,0;
		}
		break;
		end;
	case 2:
		// ガーネット、時をこえた指輪、フェイヨン移動スクロール
		setarray '@gain,718,718,718,718,718,718,6650,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 3:
		// アメジスト、時をこえた腕輪、フェイヨン移動スクロール
		setarray '@gain,719,719,719,719,719,719,6651,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 4:
		// アクアマリン、銀塊、時をこえたアルバム、フェイヨン移動スクロール
		setarray '@gain,720,720,720,720,720,720,7229,6652,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 5:
		// オパール、時をこえた錠剤、フェイヨン移動スクロール
		setarray '@gain,727,727,727,727,727,727,6653,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 6:
		// サードオニキス、銀塊、純金の王冠、フェイヨン移動スクロール
		setarray '@gain,725,725,725,725,725,725,7229,6648,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 7:
		// 真珠、プレゼントボックス、フェイヨン移動スクロール
		setarray '@gain,722,722,722,722,722,722,644,644,644,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	case 8:
		// エメラルド、銀塊、古く青い箱、フェイヨン移動スクロール
		setarray '@gain,721,721,721,721,721,721,7229,603,603,603,22507;
		setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
		for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
			set '@x,rand(208,218);
			set '@y,rand(150,160);
			if(rand(1000) < '@rate['@i])
				dropitem getmdmapname("1@face.gat"),'@x,'@y,'@gain['@i],1,0;
		}
		end;
	}
OnTimer2000:
	stopnpctimer;
	if('flag < 8 && rand(100) < 85)
		hideoffnpc;
	end;
}
