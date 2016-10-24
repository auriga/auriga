//----------------------------------------------------------------------
// スクリプト : Event_Ice v2
//----------------------------------------------------------------------
-	script	IceBuyer	85,{
	mes "[アイスクリーム商人]";
	if(strnpcinfo(2) == "moc") {
		mes "さぁ、モロクが大変な";
		mes "今だからこそ";
		mes "冷たいアイスクリーム！";
		mes "^3355FF100 Zeny^000000で";
		mes "身も心も爽やかにリフレッシュ！";
		mes "明日への活力にいかがですか！";
	}
	else if(strnpcinfo(2) == "moc_") {
		mes "さぁ、思わず食べたくなる";
		mes "冷たいアイスクリーム！";
		mes "^3355FF100 Zeny^000000で";
		mes "身も心も爽やかに！";
	}
	if(strnpcinfo(2) == "bra") {
		mes "さぁ、あつ～いブラジリスで";
		mes "つめた～いアイスクリームはいかが！";
		mes "冷たいアイスクリーム！";
		mes "^3355FF100 Zeny^000000で";
		mes "身も心も爽やかにリフレッシュ！";
		mes "おいしいよ！";
	}
	else {
		mes "冷たくて甘～い";
		mes "アイスクリーム！";
		mes "^3355FF100 Zeny^000000で";
		mes "身も心も爽やかに！";
	}
	next;
	switch(select("アイスクリームをください！","アイスクリームについて","取引をやめる")) {
	case 1:
		mes "[アイスクリーム商人]";
		if(strnpcinfo(2) == "moc") {
			mes "ありがとうございます!!";
			mes "このキャンプに移転したのを";
			mes "きっかけに製造数を増やしたので";
			mes "当店では一度に^0000FF100個^000000まで";
			mes "お買い求めいただけます！";
			set '@max,100;
		}
		else if(strnpcinfo(2) == "moc_") {
			mes "冷たくて甘いアイスクリームは";
			mes "こんな砂漠では本当に大事な";
			mes "補給源。一度に10個まで";
			mes "お買い求めいただけます。";
			set '@max,10;
		}
		else if(strnpcinfo(2) == "bra") {
			mes "ありがとうございます!!";
			mes "ここブラジリスでは";
			mes "最高のアイスクリーム製造機を";
			mes "導入しておりますので、当店では";
			mes "一度に^0000FF500個^000000まで";
			mes "お買い求めいただけます！";
			set '@max,500;
		}
		else {
			mes "アイスクリームは";
			mes "おやつにぴったり！";
			mes "一度に10個まで";
			mes "お買い求めいただけます。";
			set '@max,10;
		}
		while(1) {
			next;
			input '@num;
			if('@num > '@max) {
				mes "[アイスクリーム商人]";
				mes "え？";
				mes "ちょっと多すぎです。";
				mes "一度に販売できるのは";
				mes '@max+ "個までです。";
				mes "あまり食べ過ぎると";
				mes "お腹を壊しますよ～。";
				continue;
			}
			break;
		}
		if('@num <= 0) {
			mes "[アイスクリーム商人]";
			mes "あら？";
			mes "お腹の調子が良くないのですか？";
			close;
		}
		if(Zeny<'@num*100) {
			mes "[アイスクリーム商人]";
			mes "お客さん、お金が足りないです…";
			mes "一つ ^3355FF100 Zeny^000000ですよ！";
			close;
		}
		if(checkweight(536,'@num)==0) {
			mes "[アイスクリーム商人]";
			mes "お客さん、ちょっと荷物が";
			mes "多すぎますね。";
			mes "アイスクリームを落としてしまいます。";
			mes "持ち物を減らしてから来て下さい～。";
			close;
		}
		set Zeny,Zeny-'@num*100;
		getitem 536,'@num;
		mes "[アイスクリーム商人]";
		mes "はい、" +'@num+ "個ね。";
		mes "ありがとうございましたー。";
		close;
	case 2:
		mes "[アイスクリーム商人]";
		mes "「アイスクリーム」はですね…";
		mes "牛乳・乳製品の脂肪と";
		mes "無脂乳固形分を主原料に、";
		mes "砂糖・香料・安定剤・乳化剤";
		mes "色素などを加えて混合し、";
		next;
		mes "[アイスクリーム商人]";
		mes "泡立てて凍結させた食べ物です。";
		mes "細かく言うと、";
		mes "乳固形分15%以上";
		mes "うち乳脂肪8%以上";
		mes "のものですね。";
		next;
		mes "[アイスクリーム商人]";
		mes "エネルギーと栄養も豊富で";
		mes "とても美味しいんですが、";
		mes "だからと言って食べ過ぎると";
		mes "お腹を壊しますよ！";
		close;
	case 3:
		mes "[アイスクリーム商人]";
		mes "今この機会を逃すと";
		mes "もう味わうことが";
		mes "できなくなるかもしれませんよ？";
		mes "さぁ、さぁ、いかがですか～？";
		close;
	}
}

//morocc.gat,160,143,4	duplicate(IceBuyer)	アイスクリーム商人#moc	85
moc_ruins.gat,81,155,4	duplicate(IceBuyer)	アイスクリーム商人#moc	85
alberta.gat,107,73,4	duplicate(IceBuyer)	アイスクリーム商人#alb	85
moc_fild16.gat,88,304,4	duplicate(IceBuyer)	アイスクリーム商人#moc_	85
brasilis.gat,189,225,3	duplicate(IceBuyer)	アイスクリーム商人#bra	85
