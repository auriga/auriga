//====================================================================
//Ragnarok Online - MagicBook Quest Script	by refis
//====================================================================

geffen_in.gat,176,105,4	script	魔法書管理者ベルロポス	64,{
	if(Job != Job_Warlock) {
		mes "[魔法書管理者ベルロポス]";
		mes "ほぅ……";
		mes "どうやら君も何かに対する";
		mes "渇望を抱いているようだな。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "だが……";
		mes "君は私の進む道とは";
		mes "違う道を歩んでいるようだな。";
		mes "残念だ。";
		close;
	}
	if(getskilllv(2230)==0) {
		mes "[魔法書管理者ベルロポス]";
		mes "ふむ……";
		mes "素質はあるが、";
		mes "あと一つ足りないようだな。";
		mes "そう、リリースがな……";
		close;
	}
	mes "[魔法書管理者ベルロポス]";
	mes "リーディングスペルブック、";
	mes "フリージングスペル、";
	mes "そして魔法書……";
	next;
	mes "[魔法書管理者ベルロポス]";
	mes "リリースを習得した君なら";
	mes "興味があるだろう？";
	next;
	switch(select("特に興味は無い","リーディングスペルブックについて","フリージングスペルについて","魔法書が欲しい")) {
	case 1:
		mes "[魔法書管理者ベルロポス]";
		mes "……そうか。";
		close;
	case 2:
		mes "[魔法書管理者ベルロポス]";
		mes "リーディングスペルブック。";
		mes "魔法書を読む、そのままの意味だ。";
		mes "魔法書のことは知っているか？";
		next;
		if(select("はい","いいえ……")==1) {
			mes "[魔法書管理者ベルロポス]";
			mes "なら、これ以上私から";
			mes "言うことはないな。";
			close;
		}
		mes "[魔法書管理者ベルロポス]";
		mes "魔法書はスクロールの一種だが、";
		mes "スクロールとは大きく異なる。";
		mes "スクロールに保存された魔法は";
		mes "一度使用すると無くなるが、";
		mes "魔法書はそうではない。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "そう、魔法書は何度でも";
		mes "魔法を保存することができる。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "そして、魔法書を利用すれば、";
		mes "君はすでに習得している魔法を";
		mes "使用することができる。";
		mes "もちろん、魔法書がその魔法に";
		mes "対応していないとならないが。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "さて、なぜ君が習得している魔法を";
		mes "わざわざ魔法書を利用して";
		mes "使用しなければならないのか？";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "先ほどもいったように、";
		mes "魔法書はスクロールの一種。";
		mes "魔法書を利用すれば";
		mes "スクロールのように";
		mes "詠唱せずに魔法を扱える。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "だが、もちろん制限はある。";
		mes "まず、魔法書には魔法を";
		mes "保存する必要がある。";
		mes "いわば事前準備だな。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "そして、魔法書に魔法を";
		mes "保存している間、";
		mes "魔法書は君のSPを吸い続ける。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "なお、君が習得していない魔法を";
		mes "無理やり魔法書に";
		mes "保存しようとすると……";
		mes "いや、流石にそこまで愚かではないか。";
		close;
	case 3:
		mes "[魔法書管理者ベルロポス]";
		mes "魔法書に魔法を保存するために";
		mes "必要となる基礎だ。";
		mes "熟知すればより多くの魔法を";
		mes "保存できるようになる。";
		mes "また、強力な魔法も";
		mes "保存できるようになるだろう。";
		close;
	case 4:
		mes "[魔法書管理者ベルロポス]";
		mes "悪いが、魔法書は";
		mes "無料で配っているような";
		mes "ものではない。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "魔法書を作成するには";
		mes "いくつかの材料が必要だ。";
		mes "だが、材料さえ持ってくれば";
		mes "すでに作っておいた魔法書と";
		mes "交換しよう。";
		next;
		mes "[魔法書管理者ベルロポス]";
		mes "詳しい材料については、";
		mes "すぐそこにいるリアに聞いてくれ。";
		mes "あと、魔法書と材料の交換も";
		mes "リアが行っている。";
		if(WL_MAGICBOOK < 1)
			set WL_MAGICBOOK, 1;
		close;
	}
}

geffen_in.gat,175,112,4	script	リア	123,{
	if(checkitemblank()==0) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　危険です。";
		mes "　所持アイテムを減らしてから、";
		mes "　再度試行してください‐";
		close;
	}
	if(MaxWeight - Weight < 100) {
		mes "‐所持アイテムの重量が重い為";
		mes "　危険です。";
		mes "　所持アイテムを減らしてから、";
		mes "　再度試行してください‐";
		close;
	}
	if(WL_MAGICBOOK < 1 || Job != Job_Warlock) {
		mes "[リア]";
		mes "私は、ベルロポス様に";
		mes "認められた方々に";
		mes "魔法書をお渡ししております。";
		close;
	}
	mes "[リア]";
	mes "何かご用ですか？";
	next;
	menu "ベルロポスから魔法書について聞いた",-;
	mes "[リア]";
	mes "なるほど。";
	mes "では、魔法書の作成ですね。";
	mes "どの魔法書にしますか？";
	next;
	switch(select("作成をやめる","初級の魔法書","中級の魔法書","上級の魔法書")) {
	case 1:
		mes "[リア]";
		mes "わかりました。";
		mes "魔法書が必要になりましたら";
		mes "またいらしてください。";
		close;
	case 2:
		mes "[リア]";
		mes "初級の魔法書ですね。";
		mes "そちらの魔法書作成には";
		mes "10,000 Zeny必要になります。";
		mes "なお、古い魔法書2個、";
		mes "または古い本のページ50個でも";
		mes "作成できます。";
		next;
		switch(select("作成をやめる","10,000Zenyで作成する","古い魔法書2個で作成する","古い本のページ50個で作成する")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@value,10000;
			set '@str$,"10,000Zeny";
			break;
		case 3:
			set '@need,1006;
			set '@amount,2;
			set '@str$,"古い魔法書2個";
			break;
		case 4:
			set '@need,1097;
			set '@amount,50;
			set '@str$,"古い本のページ50個";
			break;
		}
		mes "[リア]";
		mes "それでは、";
		mes "魔法書の種類を選んで下さい。";
		next;
		switch(select("作成をやめる","魔法書(ファイアーボルト)","魔法書(コールドボルト)","魔法書(ライトニングボルト)")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@gain,6189;
			break;
		case 3:
			set '@gain,6190;
			break;
		case 4:
			set '@gain,6191;
			break;
		}
		mes "[リア]";
		mes getitemname('@gain) +"を";
		mes '@str$ +"で作成。";
		mes "間違いありませんか？";
		next;
		if(select("作成をやめる","間違いない")==1) {
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		}
		if('@need > 0) {
			if(countitem('@need) < '@amount){
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			delitem '@need,'@amount;
		} else if('@value > 0) {
			if(Zeny < '@value){
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			set Zeny,Zeny -'@value;
		}
		getitem '@gain,1;
		mes "[リア]";
		mes "それでは魔法書をどうぞ。";
		mes "くれぐれも無くさないよう";
		mes "気をつけてください。";
		close;
	case 3:
		mes "[リア]";
		mes "中級の魔法書ですね。";
		mes "そちらの魔法書作成には";
		mes "50,000 Zeny必要になります。";
		mes "なお、古く青い箱2個、";
		mes "またはエルニウム9個でも";
		mes "作成できます。";
		next;
		switch(select("作成をやめる","50,000Zenyで作成する","古く青い箱2個で作成する","エルニウム9個で作成する")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@value,50000;
			set '@str$,"50,000Zeny";
			break;
		case 3:
			set '@need,603;
			set '@amount,2;
			set '@str$,"古く青い箱2個";
			break;
		case 4:
			set '@need,985;
			set '@amount,9;
			set '@str$,"エルニウム9個";
			break;
		}
		mes "[リア]";
		mes "それでは、";
		mes "魔法書の種類を選んで下さい。";
		next;
		switch(select("作成をやめる","魔法書(ストームガスト)","魔法書(ロードオブヴァーミリオン)","魔法書(メテオストーム)","魔法書(サンダーストーム)","魔法書(ユピテルサンダー)","魔法書(ウォーターボール)","魔法書(ヘヴンズドライブ)","魔法書(アーススパイク)")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@gain,6192;
			break;
		case 3:
			set '@gain,6193;
			break;
		case 4:
			set '@gain,6194;
			break;
		case 5:
			set '@gain,6197;
			break;
		case 6:
			set '@gain,6198;
			break;
		case 7:
			set '@gain,6199;
			break;
		case 8:
			set '@gain,6200;
			break;
		case 9:
			set '@gain,6201;
			break;
		}
		mes "[リア]";
		mes getitemname('@gain) +"を";
		mes '@str$ +"で作成。";
		mes "間違いありませんか？";
		next;
		if(select("作成をやめる","間違いない")==1) {
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		}
		if('@need > 0) {
			if(countitem('@need) < '@amount) {
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			delitem '@need,'@amount;
		} else if('@value > 0) {
			if(Zeny < '@value) {
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			set Zeny,Zeny -'@value;
		}
		getitem '@gain,1;
		mes "[リア]";
		mes "それでは魔法書をどうぞ。";
		mes "くれぐれも無くさないよう";
		mes "気をつけてください。";
		close;
	case 4:
		mes "[リア]";
		mes "上級の魔法書ですね。";
		mes "そちらの魔法書作成には";
		mes "まず100,000Zeny。";
		mes "それと未知の欠片12個か";
		mes "オリデオコン7個か";
		mes "古い紫色の箱1個が必要です。";
		next;
		mes "[リア]";
		mes "もちろん材料を集めるのも";
		mes "大変ですよね。";
		mes "よろしければ200,000Zenyでも";
		mes "作成は可能ですよ。";
		next;
		switch(select("作成をやめる","100,000Zenyと未知の欠片12個で作成する","100,000Zenyとオリデオコン7個で作成する","100,000Zenyと古い紫色の箱1個で作成する","200,000Zenyで作成する")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@value,100000;
			set '@need,7094;
			set '@amount,12;
			set '@str$,"未知の欠片12個";
			break;
		case 3:
			set '@value,100000;
			set '@need,984;
			set '@amount,7;
			set '@str$,"オリデオコン7個";
			break;
		case 4:
			set '@value,100000;
			set '@need,617;
			set '@amount,1;
			set '@str$,"古い紫色の箱1個";
			break;
		case 5:
			set '@value,200000;
			set '@str$,"200,000Zeny";
			break;
		}
		mes "[リア]";
		mes "それでは、";
		mes "魔法書の種類を選んで下さい。";
		next;
		switch(select("作成をやめる","魔法書(アースストレイン)","魔法書(チェーンライトニング)","魔法書(クリムゾンロック)","魔法書(ドレインライフ)")) {
		case 1:
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		case 2:
			set '@gain,6202;
			break;
		case 3:
			set '@gain,6203;
			break;
		case 4:
			set '@gain,6204;
			break;
		case 5:
			set '@gain,6205;
			break;
		}
		mes "[リア]";
		mes getitemname('@gain) +"を";
		if('@need > 0)
			mes "100,000Zenyと";
		mes '@str$ +"で作成。";
		mes "間違いありませんか？";
		next;
		if(select("作成をやめる","間違いない")==1) {
			mes "[リア]";
			mes "わかりました。";
			mes "魔法書が必要になりましたら";
			mes "またいらしてください。";
			close;
		}
		if('@need > 0) {
			if(countitem('@need) < '@amount || Zeny < '@value) {
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			delitem '@need,'@amount;
			set Zeny,Zeny -'@value;
		} else if('@value > 0) {
			if(Zeny < '@value) {
				mes "[リア]";
				mes "あら？";
				mes "材料が足りないみたいですね。";
				mes "手荷物をもう一度確認してください。";
				close;
			}
			set Zeny,Zeny -'@value;
		}
		getitem '@gain,1;
		mes "[リア]";
		mes "それでは魔法書をどうぞ。";
		mes "くれぐれも無くさないよう";
		mes "気をつけてください。";
		close;
	}
}