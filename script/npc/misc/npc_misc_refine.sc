//=====================================================================
//武具精錬NPCセリフパターン1
//	（プロンテラ・アルベルタ・アインブロック）
//  callfunc "Refine1","NPCName",SuccessEmotion,FalureEmotion;
//--------------------------------------------------------------------

function	script	Refine1	{
	mes "["+getarg(0)+"]";
	mes "俺は武器と防具を精錬する鍛冶屋だ。";
	mes "君が装備しているアイテムの中で";
	mes "好きなものを精錬できるのだ。";
	mes "どの装備アイテムを";
	mes "精錬したいのかい？";
	next;
	set '@i,select(getequipname(1),getequipname(2),getequipname(3),getequipname(4),getequipname(5),
				getequipname(6),getequipname(7),getequipname(8),getequipname(9),getequipname(10));
	mes "["+getarg(0)+"]";
	if(getequipisequiped('@i)==0) {
		switch('@i) {
		case 1:
			mes "君の足りない脳みそを";
			mes "精錬してあげようか？";
			break;
		case 2:
			mes "俺の熱い体で君の体を";
			mes "精錬してあげるわ！";
			break;
		case 3:
			mes "君の左手をロケットパンチに";
			mes "する腕はないな。";
			break;
		case 4:
			mes "現代科学技術でも君の右手を";
			mes "ドリルにすることは";
			mes "できないね。";
			break;
		case 5:
			mes "ローブを持ってないじゃないか！";
			break;
		case 6:
			mes "君の足の臭いすごいぜ！";
			break;
		case 7:
		case 8:
			mes "どこにアクセサリーがあるのかい？";
			break;
		case 9:
		case 10:
			mes "何を精錬しろと言うんだ？";
			mes "他のアイテムの事かい？";
			break;
		}
		return;
	}
	if(getequipisenableref('@i)==0) {
		mes "このアイテムは精錬不可能だ。";
		return;
	}
	if(getequipisidentify('@i)==0) {
		mes "これは未鑑定だから精錬できない。";
		return;
	}
	if(getequiprefinerycnt('@i)>=10) {
		mes "これ以上は精錬できないぞ。";
		return;
	}
	//初回呼び出し時のみ料金とアイテムIDをそれぞれ格納
	if('price[0]==0) {
		setarray 'price,5000,100,500,5000,10000;
		setarray 'itemid,985,1010,1011,984,984;
	}
	set '@wlv,getequipweaponlv('@i);
	switch('@wlv) {
	case 0:
		mes "君が選んだ装備を精錬するには";
		mes "^ff9999エルニウム^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "続けるかい？";
		break;
	case 1:
		mes "レベル1の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999プラコン^000000と";
		mes "手数料100Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 2:
		mes "レベル2の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999エンベルタコン^000000と";
		mes "手数料500Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 3:
		mes "レベル3の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 4:
		mes "レベル4の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料10000Zenyが必要だな。";
		mes "続けるのか？";
		break;
	}
	next;
	if(select("はい","いいえ")==2) {
		mes "["+getarg(0)+"]";
		mes "君が嫌なら仕方がないだろう…";
		return;
	}
	if(getequippercentrefinery('@i) < 100) {
		mes "["+getarg(0)+"]";
		if('@wlv==0) {	//防具のとき
			mes "おおっと！この防具はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら防具が壊れるかも";
			mes "しれないぞ。防具が壊れたら";
		}
		else {		//武器のとき
			mes "おおっと！この武器はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら武器が壊れるかも";
			mes "しれないぞ。武器が壊れたら";
		}
		mes "2度と使えなくなる…それでも";
		mes "精錬をする気なのかい？";
		next;
		if(select("はい","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "良い選択だな。";
			mes "俺も無理して他人の武器を壊したら";
			mes "気分が悪くなるからさ…";
			return;
		}
	}
	if(countitem('itemid['@wlv])<1 || Zeny<'price['@wlv]) {
		mes "["+getarg(0)+"]";
		mes "それが君が持ってる全部かい？";
		mes "残念だが、材料が足りないんじゃ";
		mes "仕方がないな。";
		mes "俺はただでやってやるほど";
		mes "心が広くないからな。";
		return;
	}
	delitem 'itemid['@wlv],1;
	set Zeny,Zeny-'price['@wlv];
	mes "["+getarg(0)+"]";
	mes "カン！ カン！ カン!!";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@i;
		next;
		emotion getarg(1);
		mes "["+getarg(0)+"]";
		mes "さあ、出来上ったよ！";
		mes "久々に良い物ができた。";
		mes "武具が強くなって君も嬉しいだろ？";
	}
	else {
		failedrefitem '@i;
		next;
		emotion getarg(2);
		mes "["+getarg(0)+"]";
		mes "クホホホホ…";
		next;
		mes "["+getarg(0)+"]";
		mes "すまん！";
		mes "精錬中に武具が壊れてしまったな…";
		mes "ほ、ほら、俺がやめろって";
		mes "最初に言っただろう？";
	}
	return;
	//closeで終了
}

//=====================================================================
//武具精錬NPCセリフパターン2
//	（フェイヨン・ジュノー）
//  callfunc "Refine2","NPCName",SuccessEmotion,FalureEmotion;
//--------------------------------------------------------------------

function	script	Refine2	{
	mes "["+getarg(0)+"]";
	mes "来たか。まあとにかく";
	mes "精錬したい装備を出せ。";
	next;
	set '@i,select(getequipname(1),getequipname(2),getequipname(3),getequipname(4),getequipname(5),
				getequipname(6),getequipname(7),getequipname(8),getequipname(9),getequipname(10));
	mes "["+getarg(0)+"]";
	if(getequipisequiped('@i)==0) {
		switch('@i) {
		case 1:
			mes "俺は忙しい！お前の冗談に";
			mes "付き合っている時間など無いんだ。";
			mes "頭を突っ込んでどうするつもりだ？";
			break;
		case 2:
			mes "俺は忙しいと言っているだろう！";
			break;
		case 3:
			mes "くだらない冗談はやめてくれ！";
			break;
		case 4:
			mes "お前、精錬する気あるのか？";
			break;
		case 5:
			mes "かえれ！";
			break;
		case 6:
			mes "くだらない悪戯に付き合う";
			mes "暇は無いんだ！";
			break;
		case 7:
			mes "精錬しないのなら用は無いだろ？";
			break;
		case 8:
			mes "俺は忙しい！";
			break;
		case 9:
			mes "どこを精錬するって？";
			break;
		case 10:
			mes "帰ってくれないか？";
			break;
		}
		return;
	}
	if(getequipisenableref('@i)==0) {
		mes "これは精錬できない。";
		mes "他を当たってくれ。";
		return;
	}
	if(getequipisidentify('@i)==0) {
		mes "わけのわからない物を";
		mes "精錬する趣味は無い…";
		return;
	}
	if(getequiprefinerycnt('@i)>=10) {
		mes "これ以上手を加えるところが";
		mes "無いぞ！";
		return;
	}
	//初回呼び出し時のみ料金とアイテムIDをそれぞれ格納
	if('price[0]==0 || 'itemid[0]==0) {
		setarray 'price,5000,100,500,5000,10000;
		setarray 'itemid,985,1010,1011,984,984;
	}
	set '@wlv,getequipweaponlv('@i);
	switch('@wlv) {
	case 0:
		mes "お前が選んだ装備を精錬するには";
		mes "^ff9999エルニウム^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "ビタ1Zeny負けられない。";
		break;
	case 1:
		mes "レベル1の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999プラコン^000000と";
		mes "手数料100Zenyが必要だな。";
		mes "ビタ1Zeny負けられない。";
		break;
	case 2:
		mes "レベル2の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999エンベルタコン^000000と";
		mes "手数料500Zenyが必要だな。";
		mes "ビタ1Zeny負けられない。";
		break;
	case 3:
		mes "レベル3の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "久しぶりに俺の実力を見せてやるか。";
		break;
	case 4:
		mes "レベル4の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料10000Zenyが必要だな。";
		mes "レベル4の武器か…興奮するぜ！";
		break;
	}
	next;
	if(select("はい","いいえ")==2) {
		mes "["+getarg(0)+"]";
		mes "遊びじゃないんだよ！";
		return;
	}
	if(getequippercentrefinery('@i) < 100) {
		mes "["+getarg(0)+"]";
		mes "く…どこからこんな厄介な物を";
		mes "持ってきたんだ…。";
		mes "これ以上の精錬は危険だ。";
		mes "それを承知でやるというのか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "つまらん…";
			mes "俺は忙しい、帰ってくれ。";
			return;
		}
	}
	if(countitem('itemid['@wlv])<1 || Zeny<'price['@wlv]) {
		mes "["+getarg(0)+"]";
		mes "1Zenyも負けられないから";
		mes "精錬したければお金を持ってきな。";
		return;
	}
	delitem 'itemid['@wlv],1;
	set Zeny,Zeny-'price['@wlv];
	mes "["+getarg(0)+"]";
	mes "カン！ カン！ カン!!";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@i;
		next;
		emotion getarg(1);
		mes "["+getarg(0)+"]";
		mes "バッチリだ！";
		mes "また来てくれ。";
	}
	else {
		failedrefitem '@i;
		next;
		emotion getarg(2);
		mes "["+getarg(0)+"]";
		mes "ふ…";
		next;
		mes "["+getarg(0)+"]";
		mes "残念だ…";
		mes "まあ人生こういうこともある。";
		mes "落ち込むなよ…";
	}
	return;
	//closeで終了
}

//=====================================================================
//武具精錬NPCセリフパターン3
//	（モロク）
//  callfunc "Refine3","NPCName",SuccessEmotion,FalureEmotion;
//--------------------------------------------------------------------

function	script	Refine3	{
	mes "["+getarg(0)+"]";
	mes "私は武器と防具を精錬する鍛冶屋。";
	mes "汝が装備しているアイテムの中で";
	mes "好きなものを精錬できる。";
	mes "どの装備アイテムを";
	mes "精錬したいのか？";
	next;
	set '@i,select(getequipname(1),getequipname(2),getequipname(3),getequipname(4),getequipname(5),
				getequipname(6),getequipname(7),getequipname(8),getequipname(9),getequipname(10));
	mes "["+getarg(0)+"]";
	if(getequipisequiped('@i)==0) {
		switch('@i) {
		case 1:
			mes "汝の足りない脳みそを";
			mes "精錬してさしあげようか？";
			break;
		case 2:
			mes "私の熱い体で汝の体を";
			mes "精錬してあげるわ！";
			break;
		case 3:
			mes "汝の左手を改造する技術は無い。";
			break;
		case 4:
			mes "汝の右手をマシンガンに";
			mes "するのは無理だ。";
			break;
		case 5:
			mes "ローブを持っていないな。";
			break;
		case 6:
			mes "臭い…";
			break;
		case 7:
		case 8:
			mes "どのアクセサリーか？";
			break;
		case 9:
		case 10:
			mes "何を精錬せよと言う？";
			mes "他のアイテムの事か？";
			break;
		}
		return;
	}
	if(getequipisenableref('@i)==0) {
		mes "このアイテムは精錬不可能。";
		return;
	}
	if(getequipisidentify('@i)==0) {
		mes "これは未鑑定だから精錬できない。";
		return;
	}
	if(getequiprefinerycnt('@i)>=10) {
		mes "これ以上は精錬できない。";
		return;
	}
	//初回呼び出し時のみ料金とアイテムIDをそれぞれ格納
	if('price[0]==0 || 'itemid[0]==0) {
		setarray 'price,5000,100,500,5000,10000;
		setarray 'itemid,985,1010,1011,984,984;
	}
	set '@wlv,getequipweaponlv('@i);
	switch('@wlv) {
	case 0:
		mes "汝が選んだ装備を精錬するには";
		mes "^ff9999エルニウム^000000と ";
		mes "手数料5000Zenyが必要だ。";
		mes "続けるか？";
		break;
	case 1:
		mes "レベル1の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999プラコン^000000と";
		mes "手数料100Zenyが必要だ。";
		mes "続けるか？";
		break;
	case 2:
		mes "レベル2の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999エンベルタコン^000000と";
		mes "手数料500Zenyが必要だ。";
		mes "続けるか？";
		break;
	case 3:
		mes "レベル3の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料5000Zenyが必要だ。";
		mes "続けるか？";
		break;
	case 4:
		mes "レベル4の武器を精錬したいのか？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料10000Zenyが必要だ。";
		mes "続けるか？";
		break;
	}
	next;
	if(select("はい","いいえ")==2) {
		mes "["+getarg(0)+"]";
		mes "汝がやめるなら仕方がない…";
		return;
	}
	if(getequippercentrefinery('@i) < 100) {
		mes "["+getarg(0)+"]";
		if('@wlv==0) {	//防具のとき
			mes "ふむ…この防具はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら防具が壊れるかも";
			mes "しれない。防具が壊れたら";
		}
		else {		//武器のとき
			mes "ふむ…この武器はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら武器が壊れるかも";
			mes "しれない。武器が壊れたら";
		}
		mes "2度と使えなくなる…それでも";
		mes "精錬をする気なのか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "良い選択だ。";
			mes "私も無理して他人の武器を壊したら";
			mes "気分が悪くなるから…";
			return;
		}
	}
	if(countitem('itemid['@wlv])<1 || Zeny<'price['@wlv]) {
		mes "["+getarg(0)+"]";
		mes "それが汝が持ってる全部か？";
		mes "残念だが、材料が足りないならば";
		mes "仕方がない。";
		mes "私はただでやってさしあげるほど";
		mes "心が広くない。";
		return;
	}
	delitem 'itemid['@wlv],1;
	set Zeny,Zeny-'price['@wlv];
	mes "["+getarg(0)+"]";
	mes "カン！ カン！ カン!!";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@i;
		next;
		emotion getarg(1);
		mes "["+getarg(0)+"]";
		mes "さあ、出来た！";
		mes "久々に良い物ができたな。";
		mes "武具が強くなって汝も嬉しかろう？";
	}
	else {
		failedrefitem '@i;
		next;
		emotion getarg(2);
		mes "["+getarg(0)+"]";
		mes "………";
		next;
		mes "["+getarg(0)+"]";
		mes "すまない…";
		mes "精錬中に武具が壊れてしまった…";
		mes "しかし、最初に忠告はしたぞ？";
	}
	return;
	//closeで終了
}

//=====================================================================
//武具精錬NPCセリフパターン4
//	（プロンテラ）
//  callfunc "Refine4","NPCName",SuccessEmotion,FalureEmotion;
//--------------------------------------------------------------------

function	script	Refine4	{
	mes "["+getarg(0)+"]";
	mes "俺は武器と防具を精錬する鍛冶屋だ！";
	mes "お前が装備しているアイテムを";
	mes "精錬できるってわけだ。";
	mes "ただし、濃縮オリデオコンか";
	mes "濃縮エルニウムが必要だぞ。";
	mes "どの装備アイテムを精錬したい？";
	next;
	set '@i,select(getequipname(1),getequipname(2),getequipname(3),getequipname(4),getequipname(5),
				getequipname(6),getequipname(7),getequipname(8),getequipname(9),getequipname(10));
	mes "["+getarg(0)+"]";
	if(getequipisequiped('@i)==0) {
		switch('@i) {
		case 1:
			mes "お前の悪い頭を精錬してあげようか？";
			break;
		case 2:
			mes "俺の熱い体でお前の体を";
			mes "精錬してあげるぜ。";
			break;
		case 3:
			mes "残念ながら、お前の左手を";
			mes "ロケットパンチにする能力はないね。";
			break;
		case 4:
			mes "現代科学技術でもお前の右手を";
			mes "ロケットパンチにする事はできないぜ。";
			break;
		case 5:
			mes "持っているローブがないじゃないか？";
			break;
		case 6:
			mes "お前、足のにおいがすごいね。";
			break;
		case 7:
		case 8:
			mes "どのアクセサリーを言ってるんだろ？";
			break;
		case 9:
			mes "何を精錬してほしいんだ？";
			mes "もしかして、頭の他の所？";
			break;
		case 10:
			mes "お前の頭蓋骨を精錬してやろうか？";
			break;
		}
		return;
	}
	if(getequipisenableref('@i)==0) {
		mes "ふむ、これは精錬できる";
		mes "アイテムじゃないんだぜ……";
		return;
	}
	if(getequipisidentify('@i)==0) {
		mes "未鑑定だから精錬できないな。";
		return;
	}
	if(getequiprefinerycnt('@i)>=10) {
		mes "これ以上は精錬できないな。";
		return;
	}
	//初回呼び出し時のみ料金とアイテムIDをそれぞれ格納
	if('price[0]==0) {
		setarray 'price,5000,100,500,5000,10000;
		setarray 'itemid,7619,7620,7620,7620,7620;
	}
	set '@wlv,getequipweaponlv('@i);
	switch('@wlv) {
	case 0:
		mes "お前が選んだ装備を";
		mes "精錬するためには";
		mes "^FF9C9C濃縮エルニウム^000000と";
		mes "手数料5000Zenyが必要だぜ？";
		mes "精錬するか？";
		break;
	case 1:
		mes "レベル1の武器を";
		mes "精錬しようとしてるんだね。";
		mes "精錬のためには";
		mes "^FF9C9C濃縮オリデオコン^000000と";
		mes "手数料100Zenyが必要だぜ？";
		mes "精錬するか？";
		break;
	case 2:
		mes "レベル2の武器を";
		mes "精錬しようとしてるんだね。";
		mes "精錬のためには";
		mes "^FF9C9C濃縮オリデオコン^000000と";
		mes "手数料500Zenyが必要だぜ？";
		mes "精錬するか？";
		break;
	case 3:
		mes "レベル3の武器を";
		mes "精錬しようとしてるんだね。";
		mes "精錬のためには";
		mes "^FF9C9C濃縮オリデオコン^000000と";
		mes "手数料5000Zenyが必要だぜ？";
		mes "精錬するか？";
		break;
	case 4:
		mes "レベル4の武器を";
		mes "精錬しようとしてるんだね。";
		mes "精錬のためには";
		mes "^FF9C9C濃縮オリデオコン^000000と";
		mes "手数料10000Zenyが必要だぜ？";
		mes "精錬するか？";
		break;
	}
	next;
	if(select("はい","いいえ")==2) {
		mes "["+getarg(0)+"]";
		mes "お前がいやだったら仕方ないしな。";
		return;
	}
	// 濃縮課金アイテム精錬テーブル
	switch('@wlv) {
	case 0: setarray '@parcent,100,100,100,100, 90, 60, 60, 30, 30, 10; break;
	case 1: setarray '@parcent,100,100,100,100,100,100,100, 90, 60, 20; break;
	case 2: setarray '@parcent,100,100,100,100,100,100, 90, 60, 30, 20; break;
	case 3: setarray '@parcent,100,100,100,100,100, 90, 75, 30, 30, 20; break;
	case 4: setarray '@parcent,100,100,100,100, 90, 60, 60, 30, 30, 10; break;
	}
	if('@parcent[getequiprefinerycnt('@i)] < 100) {
		mes "["+getarg(0)+"]";
		if('@wlv==0) {	//防具のとき
			mes "あらら！";
			mes "この防具はもう";
			mes "何回も精錬されちゃったね。";
			mes "これ以上精錬すると";
			mes "防具が壊れちゃう";
			mes "恐れがある……";
			next;
			mes "["+getarg(0)+"]";
			mes "防具が壊れちゃうと";
			mes "二度と使えないんだぜ?!";
			mes "中に打ち込まれたカードも特性も";
			mes "^FF0000すべてが消えちゃう^000000んだからね。";
			mes "^FF0000防具自体が消えちゃう^000000ってわけだ。";
			mes "それでも精錬するつもりか？";
		} else {		//武器のとき
			mes "あらら！";
			mes "この武器はもう";
			mes "何回も精錬されちゃったね。";
			mes "これ以上精錬すると";
			mes "武器が壊れちゃう";
			mes "恐れがある……";
			next;
			mes "["+getarg(0)+"]";
			mes "武器が壊れちゃうと";
			mes "二度と使えないんだぜ?!";
			mes "中に打ち込まれたカードも特性も";
			mes "^FF0000すべてが消えちゃう^000000んだからね。";
			mes "^FF0000武器自体が消えちゃう^000000ってわけだ。";
			mes "それでも精錬するつもりか？";
		}
		next;
		if(select("はい","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "そうだな、物は大切に扱うべきだからな。";
			return;
		}
	}
	if(countitem('itemid['@wlv])<1 || Zeny<'price['@wlv]) {
		mes "["+getarg(0)+"]";
		mes "これがお前が持ってるすべてか？";
		mes "残念だけど、材料が足りないと";
		mes "精錬してあげられないぜ。";
		mes "俺も仕事をした代価くらい";
		mes "貰わないとな……。";
		return;
	}
	delitem 'itemid['@wlv],1;
	set Zeny,Zeny-'price['@wlv];
	mes "["+getarg(0)+"]";
	mes "カン！ カン！ カン！";
	if('@parcent[getequiprefinerycnt('@i)] > rand(100)) {
		successrefitem '@i;
		next;
		emotion getarg(1);
		mes "["+getarg(0)+"]";
		mes "さ！ 無事に精錬が終わったぜ。";
		mes "俺の腕はまだ使えるぜ！";
		mes "自分で言うのもなんだが、";
		mes "なかなか良い出来じゃないか！";
	}
	else {
		failedrefitem '@i;
		next;
		emotion getarg(2);
		mes "["+getarg(0)+"]";
		mes "ウアアアアアアアアアアッ!!!!";
		next;
		mes "["+getarg(0)+"]";
		mes "あ、あら……";
		mes "失敗しちゃった。ご、ごめん……";
		mes "装備が壊れちゃったな……";
		mes "だ、だからさ……";
		mes "危ないって言ったじゃないか……";
		mes "俺を恨まないでくれ……";
	}
	return;
	//closeで終了
}

// ----- アルベルタ -----
alberta_in.gat,28,58,4	script	フレドリック	85,{
	callfunc "Refine1","フレドリックヘルマンソン",18,4;
	close;
}
// ----- プロンテラ -----
prt_in.gat,63,60,0	script	ホルグレン	85,{
	callfunc "Refine1","ホルグレン",21,23;
	close;
}
// ----- モロク -----
morocc_in.gat,73,38,4	script	アラガム	99,{
	callfunc "Refine3","アラガムサレー",30,16;
	close;
}
// ----- フェイヨン -----
payon.gat,144,173,5	script	アントニオ	88,{
	callfunc "Refine2","アントニオ",0,32;
	close;
}
// ----- ジュノー -----
yuno_in01.gat,171,21,4	script	ディスターブ	85,{
	callfunc "Refine2","ディスターブ",9,0;
	close;
}
// ----- アインブロック -----
ein_in01.gat,24,87,5	script	マンダスマン	826,{
	callfunc "Refine1","マンダスマン",18,4;
	close;
}
// ----- プロンテラ -----
prontera.gat,123,65,1	script	フランツ	85,{
	callfunc "Refine4","フランツ",21,23;
	close;
}

//====================================================================
//精錬石販売NPC
//--------------------------------------------------------------------

-	script	BuyStone	-1,{
	if(checkitemblank()==0) {
		mes "- 所持アイテムの種類数が -";
		mes "- 多いため、アイテムを受けとる -";
		mes "- ことができません。 -";
		mes "- 所持アイテムを減らしてから -";
		mes "- 再度話しかけてください。 -";
		close;
	}
	mes "["+strnpcinfo(0)+"]";
	mes "鉄や鋼鉄の武器を精錬する時に";
	mes "使える金属を売っています。";
	mes "1レベルの武器精錬に使える";
	mes "^007777プラコン^000000と";
	mes "2レベルの武器精錬に使える";
	mes "^007777エンベルタコン^000000があります。";
	next;
	mes "["+strnpcinfo(0)+"]";
	mes "プラコンは1個200Zeny、";
	mes "エンベルタコンは";
	mes "1個1000Zenyです。";
	next;
	switch (select("プラコン購入","エンベルタコン購入","他の金属はないか聞いてみる")) {
	case 1:
		set '@price,200;
		set '@itemid,1010;
		break;
	case 2:
		set '@price,1000;
		set '@itemid,1011;
		break;
	case 3:
		mes "["+strnpcinfo(0)+"]";
		mes "1レベルと2レベルの武器より";
		mes "レベルが高い武器を精錬するための";
		mes "金属ですね。";
		mes "もうご存知かもしれませんが、";
		mes "オリデオコンとエルニウムは";
		mes "手に入れるのがすごく難しくてね…";
		close;
	}
	mes "["+strnpcinfo(0)+"]";
	mes "いくつ購入しますか？";
	mes "取り引きを中止したければ";
	mes "「0」でお願いします。";
	while(1) {
		next;
		input '@num;
		if('@num<=0) {
			mes "["+strnpcinfo(0)+"]";
			mes "取引中止ですね。";
			close;
		}
		if('@num>500) {
			mes "["+strnpcinfo(0)+"]";
			mes "500個以下で決めてください。";
			continue;
		}
		break;	//while文抜ける
	}
	if(Zeny<'@price*'@num) {
		mes "["+strnpcinfo(0)+"]";
		mes "あれ？お客さん…";
		mes "お金が足りませんね。";
		mes "すみませんが、うちも商売だから";
		mes "損するわけにはいかないんですよ。";
		close;
	}
	if(checkweight('@itemid,'@num)==0) {
		mes "["+strnpcinfo(0)+"]";
		mes "荷物が多いですね。";
		mes "持ち物を整理してから";
		mes "またおこしください。";
		close;
	}
	set Zeny,Zeny-'@price*'@num;
	getitem '@itemid,'@num;
	mes "["+strnpcinfo(0)+"]";
	mes "ご購入、ありがとうございました。";
	close;
}

alberta_in.gat,13,71,4	duplicate(BuyStone)	カラマンリス	86
prt_in.gat,56,68,4	duplicate(BuyStone)	ブルウェル	86
morocc_in.gat,63,32,0	duplicate(BuyStone)	サド		99
payon.gat,145,178,4	duplicate(BuyStone)	ベグナド	88
yuno_in01.gat,171,27,4	duplicate(BuyStone)	ティルレマ	86
ein_in01.gat,15,87,4	duplicate(BuyStone)	ティルイハース	86


//====================================================================
//精錬石交換NPC
//--------------------------------------------------------------------

-	script	ChangeStone	-1,{
	if(checkitemblank()==0) {
		mes "- 所持アイテムの種類数が -";
		mes "- 多いため、アイテムを受けとる -";
		mes "- ことができません。 -";
		mes "- 所持アイテムを減らしてから -";
		mes "- 再度話しかけてください。 -";
		close;
	}
	mes "["+strnpcinfo(3)+"]";	//識別子を参照
	mes "オリデオコンやエルニウムの原石を";
	mes "僕に持ってきたら、すぐに";
	mes "オリデオコンとエルニウムにしてあげる。";
	mes "但し、原石は各5つ以上持ってくるように。";
	next;
	switch (select("オリデオコンを作る","エルニウムを作る","属性石について聞く")) {
	case 1:
		set '@itemid,756;
		set '@gain,984;
		break;
	case 2:
		set '@itemid,757;
		set '@gain,985;
		break;
	case 3:
		mes "["+strnpcinfo(3)+"]";
		mes "属性石ねえ…";
		mes "私の金属精錬人生20年で";
		mes "話はよく聞いたけど実際には";
		mes "見たことはないな。";
		mes "聞くところによると、金属が";
		mes "火、水、地、風の属性を持つらしい。";
		next;
		mes "["+strnpcinfo(3)+"]";
		mes "その属性石を武器を作る時に";
		mes "混入すれば、属性を持つ武器を";
		mes "作れるという…";
		mes "はは…そんなことができるのは";
		mes "相当な精錬職人だろうね。";
		close;
	}
	if(countitem('@itemid)<5) {
		mes "["+strnpcinfo(3)+"]";
		mes "え？冗談でしょ？";
		mes getitemname('@itemid)+ "が5つ以上無いと";
		mes getitemname('@gain)+ "が作れないと言ったじゃないか。";
		close;
	}
	mes "["+strnpcinfo(3)+"]";
	mes getitemname('@gain)+ "を作る量はどうする？";
	next;
	if(select("1個分だけ作る","作れるだけ作る")==1) {
		if(checkweight('@gain,1)==0) {
			mes "‐所持アイテムの重量が重い為";
			mes "　危険です。";
			mes "　所持アイテムを減らしてから、";
			mes "　再度話しかけてください‐";
			close;
		}
		delitem '@itemid,5;
		getitem '@gain,1;
		mes "["+strnpcinfo(3)+"]";
		mes "ほら、約束の" +getitemname('@gain)+ "だ。";
		mes "いつでもまた来てくれ。";
		close;
	}
	set '@num,countitem('@itemid)/5;
	mes "["+strnpcinfo(3)+"]";
	mes getitemname('@itemid)+ "^FF0000" +('@num*5)+ "^000000個で";
	mes getitemname('@gain)+ "^FF0000" +'@num+ "^000000個作ればいい？";
	next;
	if(select("やっぱりやめます","お願いします")==1) {
		mes "["+strnpcinfo(3)+"]";
		mes "いつでもまた来てくれ。";
		close;
	}
	if(checkweight('@gain,1)==0) {
		mes "‐所持アイテムの重量が重い為";
		mes "　危険です。";
		mes "　所持アイテムを減らしてから、";
		mes "　再度話しかけてください‐";
		close;
	}
	delitem '@itemid,'@num*5;
	getitem '@gain,'@num;
	mes "["+strnpcinfo(3)+"]";
	mes "ほら、約束の" +getitemname('@gain)+ "だ。";
	mes "いつでもまた来てくれ。";
	close;
}

alberta_in.gat,21,63,5	duplicate(ChangeStone)	ゼノフォン::ゼノフォン ゾロタス	84
prt_in.gat,63,69,4	duplicate(ChangeStone)	ディートリヒ		84
morocc_in.gat,72,32,0	duplicate(ChangeStone)	アブドゥル		99
payon.gat,137,178,5	duplicate(ChangeStone)	ハキム			88
yuno_in01.gat,164,27,4	duplicate(ChangeStone)	ティルレイ		84
ein_in01.gat,18,82,5	duplicate(ChangeStone)	マティシュタイン	84


//====================================================================
//武具修理NPC
//--------------------------------------------------------------------

-	script	Repairer	-1,{
	mes "[修理工]";
	mes "そこの旅人、";
	mes "修理したいアイテムはあるか？";
	mes "アイテムの修理は俺に任せてくれ！";
	next;
	if(select("実は修理して欲しいアイテムが……","今は特に無いです")==2) {
		mes "[修理工]";
		mes "ふむ……";
		mes "なら俺に用は無いな。";
		close;
	}
	set '@num,getrepairableitemcount();
	if('@num==0) {
		mes "[修理工]";
		mes "おいおい……";
		mes "修理する必要のあるものなんて";
		mes "一つも持っていないじゃないか。";
		mes "はぁ……";
		mes "お前のようなヤツが増えると";
		mes "俺の商売もあがったりだよ……";
		close;
	}
	set '@price,'@num*5000;
	mes "[修理工]";
	mes "ふむ……";
	mes "お前が持っているアイテムで";
	mes "損傷しているアイテムは";
	mes '@num+ "だな。";
	next;
	mes "[修理工]";
	mes "一つ修理するのに 5000 Zenyだから";
	mes "全て直すと" +'@price+ "Zenyとなる。";
	mes "修理するか？";
	next;
	if(select("お願いします","いいえ")==2) {
		mes "[修理工]";
		mes "俺は、アイテムが傷ついたまま";
		mes "放って置かれるのが";
		mes "たまらなく嫌いなんだ。";
		mes "損傷したアイテムはすぐ直そうぜ。";
		close;
	}
	if(Zeny<'@price) {
		mes "[修理工]";
		mes "お金が足りないようだ";
		close;
	}
	set Zeny,Zeny-'@price;
	repairitem;
	mes "[修理工]";
	mes "OK！";
	mes "直ったな。";
	mes "アイテムにも寿命があるってことを";
	mes "覚えておくんだな。";
	close;
}

alberta_in.gat,31,65,4	duplicate(Repairer)	修理工	84
prt_in.gat,63,54,2	duplicate(Repairer)	修理工	86
//morocc_in.gat,71,41,4	duplicate(Repairer)	修理工	99
moc_ruins.gat,107,94,4	duplicate(Repairer)	修理工	99
payon.gat,143,165,7	duplicate(Repairer)	修理工	88
geffen_in.gat,34,166,2	duplicate(Repairer)	修理工	86
aldeba_in.gat,38,60,2	duplicate(Repairer)	修理工	86
yuno_in01.gat,175,28,2	duplicate(Repairer)	修理工	86


//=====================================================================
//鍛冶職人NPC
//  callfunc "BlackSmith","NPCName",SuccessEmotion,FalureEmotion;
//--------------------------------------------------------------------

function	script	BlackSmith	{
	mes "["+getarg(0)+"]";
	mes "俺は武器と防具を精錬する鍛冶屋だ。";
	mes "今日はどうしたんだ？";
	next;
	switch(select("精錬する","精錬用品を買う","アイテムを修理する","話をやめる")) {
	case 1:
		break;
	case 2:
		if(checkitemblank()==0) {
			mes "- 所持アイテムの種類数が -";
			mes "- 多いため、アイテムを受けとる -";
			mes "- ことができません。 -";
			mes "- 所持アイテムを減らしてから -";
			mes "- 再度話しかけてください。 -";
			return;
		}
		mes "["+getarg(0)+"]";
		mes "鉄や鋼鉄の武器を精錬する時に";
		mes "使える金属が必要か？";
		mes "1レベルの武器精錬に使える";
		mes "^007777プラコン^000000 と";
		mes "2レベルの武器精錬に使える";
		mes "^007777エンベルタコン^000000 があるぞ。";
		next;
		mes "["+getarg(0)+"]";
		mes "プラコンは1個200Zeny、";
		mes "エンベルタコンは";
		mes "1個1000Zenyだ。";
		next;
		switch(select("プラコン購入","エンベルタコン購入","他の金属はないか聞いてみる")) {
		case 1:
			set '@price,200;
			set '@itemid,1010;
			break;
		case 2:
			set '@price,1000;
			set '@itemid,1011;
			break;
		case 3:
			mes "["+getarg(0)+"]";
			mes "1レベルと2レベルの武器より";
			mes "レベルが高い武器を精錬するための";
			mes "金属だな。";
			mes "もう知っているかもしれないが､ ";
			mes "オリデオコンとエルニウムは";
			mes "手に入れるのがすごく難しくてな…。";
			return;
		}
		mes "["+getarg(0)+"]";
		mes "いくつ購入するんだ？";
		mes "取り引きを中止したければ";
		mes "「0」で頼む。";
		while(1) {
			next;
			input '@num;
			if('@num<=0) {
				mes "["+getarg(0)+"]";
				mes "取引中止だな。";
				return;
			}
			if('@num>500) {
				mes "["+getarg(0)+"]";
				mes "500個以下で決めてくれ。";
				continue;
			}
			break;	//while文抜ける
		}
		if(Zeny<'@price*'@num) {
			mes "["+getarg(0)+"]";
			mes "あれ？　お客さん……";
			mes "お金が足りないね。";
			mes "すまないが、うちも商売だから";
			mes "損するわけにはいかないんだよ。";
			return;
		}
		if(checkweight('@itemid,'@num)==0) {
			mes "["+getarg(0)+"]";
			mes "荷物が多いな。";
			mes "持ち物を整理してから";
			mes "また来てもらえるか？。";
			return;
		}
		set Zeny,Zeny-'@price*'@num;
		getitem '@itemid,'@num;
		mes "["+getarg(0)+"]";
		mes "確かに受け取ったぜ。";
		mes "また来てくれよな。";
		return;
	case 3:
		set '@num,getrepairableitemcount();
		if('@num==0) {
			mes "["+getarg(0)+"]";
			mes "おいおい……";
			mes "修理する必要のあるものなんて";
			mes "一つも持っていないじゃないか。";
			mes "はぁ……";
			mes "お前のようなヤツが増えると";
			mes "俺の商売もあがったりだよ……";
			return;
		}
		set '@price,'@num*5000;
		mes "["+getarg(0)+"]";
		mes "ふむ……";
		mes "お前が持っているアイテムで";
		mes "損傷しているアイテムは";
		mes '@num+ "だな。";
		next;
		mes "["+getarg(0)+"]";
		mes "一つ修理するのに 5000 Zenyだから";
		mes "全て直すと" +'@price+ "Zenyとなる。";
		mes "修理するか？";
		next;
		if(select("お願いします","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "俺は、アイテムが傷ついたまま";
			mes "放って置かれるのが";
			mes "たまらなく嫌いなんだ。";
			mes "損傷したアイテムはすぐ直そうぜ。";
			return;
		}
		if(Zeny<'@price) {
			mes "["+getarg(0)+"]";
			mes "お金が足りないようだ";
			return;
		}
		set Zeny,Zeny-'@price;
		repairitem;
		mes "["+getarg(0)+"]";
		mes "OK！";
		mes "直ったな。";
		mes "アイテムにも寿命があるってことを";
		mes "覚えておくんだな。";
		return;
	case 4:
		mes "["+getarg(0)+"]";
		mes "そうかい。残念だな。";
		mes "いつでも来てくれよな。";
		return;
	}
	// 以下武具精練
	mes "["+getarg(0)+"]";
	mes "俺は武器と防具を精錬する鍛冶屋だ。";
	mes "君が装備しているアイテムの中で";
	mes "好きなものを精錬できるのだ。";
	mes "どの装備アイテムを";
	mes "精錬したいのかい？";
	next;
	set '@i,select(
			getequipisequiped(1)? "^nItemID^"+getequipid(1): "",
			getequipisequiped(2)? "^nItemID^"+getequipid(2): "",
			getequipisequiped(3)? "^nItemID^"+getequipid(3): "",
			getequipisequiped(4)? "^nItemID^"+getequipid(4): "",
			getequipisequiped(5)? "^nItemID^"+getequipid(5): "",
			getequipisequiped(6)? "^nItemID^"+getequipid(6): "",
			"やっぱりやめる");
	if('@i == 7) {
		mes "[鍛冶職人]";
		mes "また来るんだな。";
		return;
	}
	mes "["+getarg(0)+"]";
	if(getequipisenableref('@i)==0) {
		mes "このアイテムは精錬不可能だ。";
		return;
	}
	if(getequipisidentify('@i)==0) {
		mes "これは未鑑定だから精錬できない。";
		return;
	}
	if(getequiprefinerycnt('@i)>=10) {
		mes "これ以上は精錬できないぞ。";
		return;
	}
	//初回呼び出し時のみ料金とアイテムID、連続精練上限をそれぞれ格納
	if('price[0]==0) {
		setarray 'price,5000,100,500,5000,10000;
		setarray 'itemid,985,1010,1011,984,984;
		setarray 'max,4,7,6,5,4;
	}
	set '@wlv,getequipweaponlv('@i);
	if(getequiprefinerycnt('@i)<'max) {
		mes "この装備をどうするんだ？";
		mes "安全圏内は一気に精錬出来るぜ。";
		mes "一気に精錬するなら";
		mes "安全圏分の素材とZenyが必要だ。";
		next;
		switch(select("精錬する","一気に精錬する","やめる")) {
		case 1:
			mes "["+getarg(0)+"]";
			break;
		case 2:
			set '@num,'max - getequiprefinerycnt('@i);
			mes "["+getarg(0)+"]";
			mes "君が選んだ装備を精錬するには";
			mes "^0000FF" +getitemname('itemid['@wlv])+ " " +'@num+ "個^000000と";
			mes "^0000FF手数料 " +('price['@wlv]*'@num)+ "Zeny^000000が必要だ。";
			mes "精錬を続けるかい？";
			next;
			if(select("はい","やっぱりやめる") == 2) {
				mes "["+getarg(0)+"]";
				mes "また来るんだな。";
				return;
			}
			if(countitem('itemid['@wlv])<'@num || Zeny<'price['@wlv]*'@num) {
				mes "["+getarg(0)+"]";
				mes "それが君が持ってる全部かい？";
				mes "残念だが、材料が足りないんじゃ";
				mes "仕方がないな。";
				mes "俺はただでやってやるほど";
				mes "心が広くないからな。";
				return;
			}
			for(set '@j,0; '@j<'@num; set '@j,'@j+1) {
				if(getequippercentrefinery('@i) < 100) {
					mes "["+getarg(0)+"]";
					mes "何かがおかしいぞ？";
					return;
				}
				delitem 'itemid['@wlv],1;
				set Zeny,Zeny-'price['@wlv];
				successrefitem '@i;
			}
			mes "["+getarg(0)+"]";
			mes "さぁ出来たぞ。";
			mes "持って行くと良い。";
			return;
			//closeで終了
		case 3:
			mes "[鍛冶職人]";
			mes "また来るんだな。";
			return;
		}
	}
	switch('@wlv) {
	case 0:
		mes "君が選んだ装備を精錬するには";
		mes "^ff9999エルニウム^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "続けるかい？";
		break;
	case 1:
		mes "レベル1の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999プラコン^000000と";
		mes "手数料100Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 2:
		mes "レベル2の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999エンベルタコン^000000と";
		mes "手数料500Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 3:
		mes "レベル3の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料5000Zenyが必要だな。";
		mes "続けるのか？";
		break;
	case 4:
		mes "レベル4の武器を精錬したいのかい？";
		mes "精錬するため、 ^ff9999オリデオコン^000000と";
		mes "手数料10000Zenyが必要だな。";
		mes "続けるのか？";
		break;
	}
	next;
	if(select("はい","いいえ")==2) {
		mes "["+getarg(0)+"]";
		mes "君が嫌なら仕方がないだろう…";
		return;
	}
	if(getequippercentrefinery('@i) < 100) {
		mes "["+getarg(0)+"]";
		if('@wlv==0) {	//防具のとき
			mes "おおっと！この防具はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら防具が壊れるかも";
			mes "しれないぞ。防具が壊れたら";
		}
		else {		//武器のとき
			mes "おおっと！この武器はもうたくさんの";
			mes "精錬をしてきたみたいだな…これ以上";
			mes "精錬したら武器が壊れるかも";
			mes "しれないぞ。武器が壊れたら";
		}
		mes "2度と使えなくなる…それでも";
		mes "精錬をする気なのかい？";
		next;
		if(select("はい","いいえ")==2) {
			mes "["+getarg(0)+"]";
			mes "良い選択だな。";
			mes "俺も無理して他人の武器を壊したら";
			mes "気分が悪くなるからさ…";
			return;
		}
	}
	if(countitem('itemid['@wlv])<1 || Zeny<'price['@wlv]) {
		mes "["+getarg(0)+"]";
		mes "それが君が持ってる全部かい？";
		mes "残念だが、材料が足りないんじゃ";
		mes "仕方がないな。";
		mes "俺はただでやってやるほど";
		mes "心が広くないからな。";
		return;
	}
	delitem 'itemid['@wlv],1;
	set Zeny,Zeny-'price['@wlv];
	mes "["+getarg(0)+"]";
	mes "カン！ カン！ カン!!";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@i;
		next;
		emotion getarg(1);
		mes "["+getarg(0)+"]";
		mes "さあ、出来上ったよ！";
		mes "久々に良い物ができた。";
		mes "武具が強くなって君も嬉しいだろ？";
	}
	else {
		failedrefitem '@i;
		next;
		emotion getarg(2);
		mes "["+getarg(0)+"]";
		mes "クホホホホ…";
		next;
		mes "["+getarg(0)+"]";
		mes "すまん！";
		mes "精錬中に武具が壊れてしまったな…";
		mes "ほ、ほら、俺がやめろって";
		mes "最初に言っただろう？";
	}
	return;
	//closeで終了
}
