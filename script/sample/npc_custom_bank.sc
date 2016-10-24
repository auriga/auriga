// カプラ銀行サービス	テストスクリプト
prontera.gat,162,188,4	script	銀行員カプラ	112,{
	cutin "kafra_06",2;
	mes "[銀行員カプラ]";
	mes "カプラ銀行サービスです。";
	mes "毎度ご利用ありがとうございます♪";
	mes "1000zからでのご利用になります。";
	next;
	switch(select("預ける","引き出す","やっぱやめる")) {
	case 1:
		mes "[銀行員カプラ]";
		mes "預ける金額を入力してください♪";
		mes "ちなみに、手数料として";
		mes "預かり金の1%頂きます。";
		next;
		input '@val;
		mes "[銀行員カプラ]";
		if('@val < 1000) {
			break;
		}
		set '@commission,'@val/100;
		if(Zeny < '@val + '@commission) {
			mes "持ち金が足りないようですね。";
			break;
		}
		set Zeny,Zeny - ('@val + '@commission);
		set #kafrabank,#kafrabank + '@val;
		mes "手数料^135445" + '@commission + "^000000Zeny";
		mes "頂きますね。";
		mes "無事に取り引きできました。";
		break;
	case 2:
		if(#kafrabank == 0) {
			mes "[銀行員カプラ]";
			mes "あなたからは、1zも";
			mes "お預かりしていないですよ？";
			break;
		}
		mes "[銀行員カプラ]";
		mes "現在あなたからお預かりしているのは";
		mes "^135445" + #kafrabank + "^000000Zenyです。";
		mes "引き出す金額を入力してください♪";
		next;
		input '@val;
		mes "[銀行員カプラ]";
		if('@val < 1)
			break;
		if(#kafrabank < '@val) {
			mes "そんなに預金はありませんよ？";
			break;
		}
		set #kafrabank,#kafrabank - '@val;
		set Zeny,Zeny + '@val;
		mes "無事に取り引きできました。";
		break;
	case 3:
		mes "[銀行員カプラ]";
		break;
	}
	mes "またのご利用をお待ちしています♪";
	close2;
	cutin "kafra_06",255;
	end;
}
