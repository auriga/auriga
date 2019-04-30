//= Athena Script ==============================================================
// Ragnarok Online Zonda Script	by Blaze
//= Registry ===================================================================
// $VoteTime -> 商圏投票タイマー
// $VoteResult -> 商圏投票期間区別
// $VoteNumber -> 商圏投票回数
// $VoteKafra -> 商圏投票カプラ票
// $VoteZonda -> 商圏投票ジョンダ票
// $VoteKafraP -> 商圏投票カプラ連続当選
// $VoteZondaP -> 商圏投票ジョンダ連続当選
//==============================================================================

//============================================================
// ジョンダ職員
//------------------------------------------------------------
-	script	ジョンダ職員#Zonda	874,{
	cutin "zonda_01",2;
	mes "[ジョンダ職員]";
	mes "いらっしゃいませ。";
	mes "（有）ジョンダイベントは、常に";
	mes "最高のサービスを提供しております。";
	mes "どのサービスをご利用いたしますか？";
	next;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "rachel.gat" || '@map$ == "veins.gat")
		set '@word$,"空間移動サービス";
	switch(select("位置セーブサービス","倉庫サービス",'@word$,"カートサービス","終了")) {
	case 1:
		if('@map$ == "lighthalzen.gat")
			savepoint "lighthalzen.gat",94,240;
		else if('@map$ == "hugel.gat")
			savepoint "hugel.gat",97,153;
		else if('@map$ == "rachel.gat")
			savepoint "rachel.gat",115,125;
		else if('@map$ == "veins.gat")
			savepoint "veins.gat",205,102;
		mes "[ジョンダ職員]";
		mes "セーブいたしました。";
		mes "ご利用頂きまして、";
		mes "誠にありがとうございます。";
		break;
	case 2:
		if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
			mes "[ジョンダ職員]";
			mes "誠に申し訳ございません、お客様。";
			mes "倉庫は、基本スキルレベル6を";
			mes "習得してから利用可能となります。";
			break;
		}
		if(Zeny < 40) {
			mes "[ジョンダ職員]";
			mes "お客様、倉庫利用料は";
			mes "40 Zenyとなっております。";
			mes "大変申し訳ございませんが、";
			mes "所持金をお確かめの上、";
			mes "再度話し掛けてください。";
			break;
		}
		set Zeny,Zeny-40;
		mes "[ジョンダ職員]";
		mes "ご利用頂きまして、";
		mes "誠にありがとうございます。";
		close2;
		openstorage;
		cutin "zonda_01",255;
		end;
	case 3:
		mes "[ジョンダ職員]";
		mes "目的地を選んでください。";
		next;
		if('@map$ == "rachel.gat")
			set '@word$,"ベインス";
		else if('@map$ == "veins.gat")
			set '@word$,"ラヘル";
		if(select('@word$+ " -> 2200 z","キャンセル")==2) {
			mes "[ジョンダ職員]";
			mes "またご利用くださいませ。";
			break;
		}
		if(Zeny < 2200) {
			mes "[ジョンダ職員]";
			mes "お客様、" +'@word$+ "までの";
			mes "空間移動サービスの料金は";
			mes "2200 Zenyとなっております。";
			mes "所持金をお確かめの上、";
			mes "再度ご利用ください。";
			break;
		}
		cutin "zonda_01",255;
		set Zeny,Zeny-2200;
		if('@map$ == "rachel.gat")
			warp "veins.gat",205,102;
		else if('@map$ == "veins.gat")
			warp "rachel.gat",115,125;
		end;
	case 4:
		if(getbaseclass(Class) != CLASS_MC) {
			mes "[ジョンダ職員]";
			mes "お客様、大変申し訳ございませんが、";
			mes "カートサービスは、商人とその上位職";
			mes "専用のサービスとなっております。";
			break;
		}
		if(checkcart()) {
			mes "[ジョンダ職員]";
			mes "大変申し訳ございませんが、";
			mes "お客様は現在カートを";
			mes "ご利用されております。";
			break;
		}
		mes "[ジョンダ職員]";
		mes "カート利用料金は 800 Zenyです。";
		mes "また、カートを利用するには";
		mes "「プッシュカート」スキルが必要です。";
		mes "そのスキルがないとカートを利用";
		mes "できずにお金だけ消えてしまいます。";
		mes "準備はよろしいですか？";
		next;
		if(select("利用する","取り消し")==2) {
			mes "[ジョンダ職員]";
			mes "ありがとうございました。";
			mes "またのご利用をお待ちしております。";
			break;
		}
		if(Zeny < 800) {
			mes "[ジョンダ職員]";
			mes "お客様、カート利用料金は";
			mes "800 Zenyです。";
			mes "大変申し訳ございませんが、";
			mes "所持金をお確かめの上、";
			mes "再度話し掛けてください。";
			break;
		}
		set Zeny,Zeny-800;
		setcart;
		break;
	case 5:
		mes "[ジョンダ職員]";
		mes "（有）ジョンダイベントは、お客様に";
		mes "常に最高のサービスを";
		mes "提供いたしております。";
		mes "ご意見・ご要望などございましたら、";
		mes "いつでもおっしゃってください。";
		next;
		mes "[ジョンダ職員]";
		mes "ご利用頂きまして、";
		mes "誠にありがとうございました。";
		break;
	}
	close2;
	cutin "zonda_01",255;
	end;
}

//============================================================
// リヒタルゼン-ジョンダ職員
//------------------------------------------------------------
lighthalzen.gat,94,248,4	duplicate(ジョンダ職員#Zonda)	ジョンダ職員	874

//============================================================
// フィゲル-ジョンダ職員
//------------------------------------------------------------
hugel.gat,88,168,4	duplicate(ジョンダ職員#Zonda)	ジョンダ職員	874

//============================================================
// ラヘル-ジョンダ職員
//------------------------------------------------------------
rachel.gat,109,138,5	duplicate(ジョンダ職員#Zonda)	ジョンダ職員	874

//============================================================
// ベインス-ジョンダ職員
//------------------------------------------------------------
veins.gat,208,128,5	duplicate(ジョンダ職員#Zonda)	ジョンダ職員	874

//==========================================
// 商圏投票
//------------------------------------------
-	script	VoteEvent	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer60000:
	set $VoteTime,$VoteTime+1;
	if($VoteResult == 0) {	//投票期間中
		if($VoteTime >= 1440) {
			if($VoteKafra < 20 && $VoteZonda < 20)	//どちらも20票に満たない場合はタイマー0
				set $VoteTime,0;
			else {
				if($VoteKafra >= $VoteZonda) {	//カプラサービス勝利
					if($VoteZondaP < 2)
						set $VoteZondaP,$VoteZondaP+1;
					set $VoteResult,1;
				}
				else {
					if($VoteKafraP < 2)
						set $VoteKafraP,$VoteKafraP+1;
					set $VoteResult,2;
				}
				announce "只今、実施していた商圏投票が終了いたしました。結果発表をお待ちください。",8;
				sleep 5000;
				announce "商圏投票の結果を発表いたします。",8;
				sleep 5000;
				announce "得票が多かったのは、"+(($VoteResult == 1)? "カプラサービス": "ジョンダイベント")+"です。"+(($VoteResult == 1)? "カプラサービス": "ジョンダイベント")+"が商圏を得ました。",8;
				sleep 5000;
				announce "今後もご利用、お願い申し上げます。",8;
				set $VoteTime,0;
				initnpctimer;
				end;
			}
		}
		if($VoteTime % 120 == 0)
			announce "現在、商圏投票を実施中です。皆様のご参加を、お待ちいたしております。",8;
	}
	else if($VoteTime >= 8640) {		//サービス期間終了
		if($VoteResult == 1 && $VoteKafraP > 0)
			set $VoteKafraP,$VoteKafraP-1;
		if($VoteResult == 2 && $VoteZondaP > 0)
			set $VoteZondaP,$VoteZondaP-1;
		set $VoteTime,0;
		set $VoteResult,0;
		set $VoteKafra,0;
		set $VoteZonda,0;
		set $VoteNumber,$VoteNumber+1;
		announce "現在、商圏投票を実施中です。皆様のご参加を、お待ちいたしております。",8;
	}
	initnpctimer;
	end;
}

-	script	カプラ投票広報職員#vt	116,{
	if(strnpcinfo(4) == "ジュノー" || strnpcinfo(4) == "リヒタルゼン")
		cutin "kafra_09",2;
	else
		cutin "kafra_02",2;
	mes "[カプラ投票広報職員]";
	mes "いらっしゃいませ。";
	mes "ジョンダイベントとカプラサービス";
	mes "の間に結ばれた協定^FF0000商圏投票^000000のため、";
	mes "カプラ本部から" +strnpcinfo(4)+ "に";
	mes "派遣された投票広報職員です。";
	mes "何をお手伝いいたしましょうか？";
	next;
	switch(select("商圏投票について","投票に参加","空間移動サービス","取り消し")) {
	case 1:
		mes "[カプラ投票広報職員]";
		mes "カプラサービスでは、";
		mes "現在サービス中の空間移動サービスを、";
		mes "その他の地域にも転送するサービスを";
		mes "企画しておりました。";
		next;
		mes "[カプラ投票広報職員]";
		mes "しかし、対象地域は異なるものの、";
		mes "ジョンダイベントでもそのサービスを";
		mes "企画していたようなのです。";
		next;
		mes "[カプラ投票広報職員]";
		mes "お互い似たようなサービスを";
		mes "企画していることを知り、";
		mes "ジョンダイベントとカプラサービスは";
		mes "対立することとなりました。";
		next;
		mes "[カプラ投票広報職員]";
		mes "両社で話し合いの結果考案されたのが";
		mes "この^FF0000商圏投票^000000です。";
		mes "すなわち、どちらの企業がサービスを";
		mes "実施するか、お客様の投票によって";
		mes "決めようというものです。";
		next;
		mes "[カプラ投票広報職員]";
		mes "お互い、どのようなサービスをするか";
		mes "お客様に公表し、お客様は";
		mes "希望に沿うサービスを行う企業に";
		mes "投票すれば良いということです。";
		next;
		mes "[カプラ投票広報職員]";
		mes "しかし、1回の投票で今後のサービスを";
		mes "永続的に決めてしまうと、";
		mes "両社間の摩擦が深まる恐れがあります。";
		mes "そのため、1回目の投票で権利を得た";
		mes "企業が一定期間先にサービスを行い、";
		mes "その後再投票することにいたしました。";
		next;
		mes "[カプラ投票広報職員]";
		mes "もちろん再投票をするとしても、";
		mes "一方の企業が毎回権利を得る";
		mes "可能性もあるので、両社にとっては";
		mes "メリットともデメリットとも";
		mes "言えることでしょう。";
		next;
		mes "[カプラ投票広報職員]";
		mes "我がカプラサービスでは、";
		mes "お客様が希望するサービスを行うため、";
		mes "最善を尽くすつもりです。";
		mes "これからも、";
		mes "ご声援をよろしくお願いいたします。";
		break;
	case 2:
		if(BaseLevel < 60) {
			mes "[カプラ投票広報職員]";
			mes "申し訳ございません。";
			mes "投票権がなければ、";
			mes "商圏投票には参加できません。";
			mes "投票権を得てから、";
			mes "投票にご参加ください。";
			next;
			mes "[カプラ投票広報職員]";
			mes "投票権に関しては、";
			mes "アルデバランにあるカプラ本社にて、";
			mes "案内いたしております。";
			break;
		}
		if($VoteResult) {
			mes "[カプラ投票広報職員]";
			mes "現在は投票期間ではございませんので、";
			mes "投票することができません。";
			mes "次回投票の際に、またお越しください。";
			mes "それでは、楽しい一日を。";
			break;
		}
		if(ZONDA_VOTE > $VoteNumber) {
			mes "[カプラ投票広報職員]";
			mes "申し訳ございませんが、";
			mes "お客様は既に投票済みです。";
			mes "次回投票の際に、またお越しください。";
			mes "それでは、楽しい一日を。";
			break;
		}
		mes "[カプラ投票広報職員]";
		mes "我がカプラサービスで企画中の";
		mes "転送地域は、次の地域です。";
		mes "-^FF0000おもちゃ分類所^000000-";
		if($VoteKafraP >= 1) mes "-^FF0000アルデバラン時計塔地下3F^000000-";
		if($VoteKafraP >= 2) mes "-^FF0000ノーグロード2層^000000-";
		next;
		mes "[カプラ投票広報職員]";
		mes "この地域への空間移動サービスを";
		mes "希望される場合は、カプラサービスに";
		mes "投票をお願いいたします。";
		mes "カプラサービスに貴重な一票を、";
		mes "よろしくお願いいたします。";
		next;
		if(select("いいえ","はい")==1) {
			mes "[カプラ投票広報職員]";
			mes "そうですか……残念ですが、";
			mes "投票はお客様の意思によって行う";
			mes "ものですので、仕方がないですね。";
			mes "もし、気が変わりましたら、";
			mes "私をお尋ねください。";
			next;
			mes "[カプラ投票広報職員]";
			mes "いつもカプラサービスは";
			mes "皆さんと一緒にいます。";
			mes "それでは、楽しい一日を。";
			break;
		}
		set ZONDA_VOTE,$VoteNumber+1;
		set $VoteKafra,$VoteKafra+1;
		mes "[カプラ投票広報職員]";
		mes "本当にありがとうございます。";
		mes "お客様の貴重な一票を忘れずに、";
		mes "今後もカプラサービスは";
		mes "努力してまいります。";
		mes "それでは、楽しい一日を。";
		break;
	case 3:
		if($VoteResult == 0) {
			mes "[カプラ投票広報職員]";
			mes "申し訳ございません。";
			mes "現在投票期間中のため、空間移動";
			mes "サービスを利用することができません。";
			mes "投票期間終了後、投票結果によって";
			mes "ご利用いただくことができます。";
			break;
		}
		if($VoteResult == 2) {
			mes "[カプラ投票広報職員]";
			mes "申し訳ございません、投票の結果、";
			mes "現在カプラサービスでは空間移動";
			mes "サービスをいたしておりません。";
			mes "次回投票の際には、カプラサービスへの";
			mes "一票をよろしくお願いいたします。";
			mes "それでは、楽しい一日を。";
			break;
		}
		mes "[カプラ投票広報職員]";
		mes "目的地をおっしゃってください。";
		mes "今回はお試し期間と";
		mes "なっておりますので、";
		mes "カプラポイントは発生しません。";
		next;
		if($VoteKafraP >= 1) set '@warp1$,"アルデバラン時計塔地下3F -> 4000z";
		if($VoteKafraP >= 2) set '@warp2$,"ノーグロード2層 -> 4000z";
		switch(select("おもちゃ分類所 -> 4000 z",'@warp1$,'@warp2$,"取り消し")) {
		case 1:	//おもちゃ分類所
			set '@mapname$,"xmas_dun02.gat";
			setarray '@warp,130,123;
			break;
		case 2:	//アルデバラン時計塔地下3F
			set '@mapname$,"alde_dun03.gat";
			setarray '@warp,265,22;
			break;
		case 3:	//ノーグロード2層
			set '@mapname$,"mag_dun02.gat";
			setarray '@warp,47,40;
			break;
		case 4: break;	//fall through
		}
		if('@mapname$ != "") {
			if(Zeny < 4000) {
				mes "[カプラ投票広報職員]";
				mes "お客様、お金が足りないようですが。";
				break;
			}
			set Zeny,Zeny-4000;
			warp '@mapname$,'@warp[0],'@warp[1];
			end;
		}
	case 4:
		mes "[カプラ投票広報職員]";
		mes "我々カプラサービスは、より完璧な";
		mes "サービスと管理業務を目指し";
		mes "お客様が安心してご利用いただけるよう";
		mes "いつも最善を尽くしています。";
		mes "（株）カプラサービスをご利用いただき";
		mes "ありがとうございました。";
		break;
	}
	close2;
	cutin "kafra_02",255;
	end;
}

-	script	ジョンダ投票広報職員#vt	874,{
	cutin "zonda_01",2;
	mes "[ジョンダ投票広報職員]";
	mes "いらっしゃいませ、お客様。";
	mes "私は、カプラサービスと";
	mes "ジョンダイベントの間に結ばれた協定";
	mes "^FF0000商圏投票^000000のために派遣された、";
	mes "投票広報職員です。";
	mes "ご用件をお伺いしましょう。";
	next;
	switch(select("商圏投票について","投票に参加","空間移動サービス","取り消し")) {
	case 1:
		mes "[ジョンダ投票広報職員]";
		mes "現在、ミッドガルドの空間移動";
		mes "サービスは、大部分を";
		mes "カプラサービスが行っております。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "そこでジョンダイベントでは";
		mes "カプラサービスとの差別化のため、";
		mes "カプラサービスでは提供していない";
		mes "ダンジョンなどに対して主にサービスを";
		mes "する企画をしていました。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "しかし、偶然にもカプラサービスも";
		mes "同様の企画を検討していたようです。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "我が社としては、既存商圏のほとんどを";
		mes "カプラサービスが掌握しているため、";
		mes "新規商圏は我が社で獲得したかった";
		mes "のですが、カプラサービス側も";
		mes "そうそう譲歩できることではなく、";
		mes "両社は対立することとなりました。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "両社で話し合いの結果考案されたのが";
		mes "この^FF0000商圏投票^000000です。";
		mes "すなわち、どちらの企業がサービスを";
		mes "実施するか、お客様の投票によって";
		mes "決めようというものです。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "しかし、1回の投票で今後のサービスを";
		mes "永続的に決めてしまうと、";
		mes "両社間の摩擦が深まる恐れがあります。";
		mes "そのため、1回目の投票で権利を得た";
		mes "企業が一定期間先にサービスを行い、";
		mes "その後再投票することにいたしました。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "もちろん再投票をするとしても、";
		mes "一方の企業が毎回権利を得る";
		mes "可能性もあるので、両社にとっては";
		mes "メリットともデメリットとも";
		mes "言えることでしょう。";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "ジョンダイベントは、カプラサービスと";
		mes "違った形でお客様に最高のサービスを";
		mes "提供してまいります。";
		mes "今後も我がジョンダイベントを、";
		mes "ご愛顧いただきますよう、";
		mes "よろしくお願い致します。";
		break;
	case 2:
		if(BaseLevel < 60) {
			mes "[ジョンダ投票広報職員]";
			mes "申し訳ございません。";
			mes "投票権がなければ、";
			mes "商圏投票には参加できません。";
			mes "投票権を得てから、";
			mes "投票にご参加ください。";
			next;
			mes "[ジョンダ投票広報職員]";
			mes "投票権に関しては、";
			mes "リヒタルゼンにあるジョンダ本社にて";
			mes "案内いたしております。";
			break;
		}
		if($VoteResult) {
			mes "[ジョンダ投票広報職員]";
			mes "現在は投票期間ではございませんので、";
			mes "投票することができません。";
			mes "次回投票の際に、またお越しください。";
			mes "それでは、良い一日を。";
			break;
		}
		if(ZONDA_VOTE > $VoteNumber) {
			mes "[ジョンダ投票広報職員]";
			mes "申し訳ございませんが、";
			mes "お客様は既に投票済みです。";
			mes "次回投票の際に、またお越しください。";
			mes "それでは、良い一日を。";
			break;
		}
		mes "[ジョンダ投票広報職員]";
		mes "我がジョンダイベントで企画中の";
		mes "転送地域は、次の地域です。";
		mes "-^FF0000イズルード海底洞窟3層^000000-";
		if($VoteZondaP >= 1) mes "-^FF0000アルデバラン時計塔地上3F^000000-";
		if($VoteZondaP >= 2) mes "-^FF0000グラストヘイム古城^000000-";
		next;
		mes "[ジョンダ投票広報職員]";
		mes "この地域への空間移動サービスを";
		mes "希望される場合は、ジョンダイベントに";
		mes "投票をお願いいたします。";
		mes "ジョンダイベントに貴重な一票を、";
		mes "よろしくお願いいたします。";
		next;
		if(select("いいえ","はい")==1) {
			mes "[ジョンダ投票広報職員]";
			mes "そうですか……残念ですが、";
			mes "投票はお客様の意思によって行う";
			mes "ものですので、仕方がないですね。";
			mes "もし、気が変わりましたら、";
			mes "私をお尋ねください。";
			next;
			mes "[ジョンダ投票広報職員]";
			mes "ジョンダイベントは、お客様に";
			mes "常に最高のサービスを";
			mes "提供いたしております。";
			mes "それでは、良い一日を。";
			break;
		}
		set ZONDA_VOTE,$VoteNumber+1;
		set $VoteZonda,$VoteZonda+1;
		mes "[ジョンダ投票広報職員]";
		mes "本当にありがとうございます。";
		mes "お客様の貴重な一票を忘れずに、";
		mes "今後もジョンダイベントは";
		mes "努力してまいります。";
		mes "それでは、良い一日を。";
		break;
	case 3:
		if($VoteResult == 0) {
			mes "[ジョンダ投票広報職員]";
			mes "申し訳ございません。";
			mes "現在投票期間中のため、空間移動";
			mes "サービスを利用することができません。";
			mes "投票期間終了後、投票結果によって";
			mes "ご利用いただくことができます。";
			break;
		}
		if($VoteResult == 1) {
			mes "[ジョンダ投票広報職員]";
			mes "申し訳ございません、投票の結果、";
			mes "現在ジョンダイベントでは空間移動";
			mes "サービスをいたしておりません。";
			mes "次回投票の際には、ジョンダイベントへ";
			mes "一票をよろしくお願いいたします。";
			mes "それでは、良い一日を。";
			break;
		}
		mes "[ジョンダ投票広報職員]";
		mes "目的地をおっしゃってください。";
		next;
		if($VoteZondaP >= 1) set '@warp1$,"アルデバラン時計塔地上3F -> 4000z";
		if($VoteZondaP >= 2) set '@warp2$,"グラストヘイム古城 -> 4000z";
		switch(select("イズルード海底洞窟3層 -> 4000 z",'@warp1$,'@warp2$,"取り消し")) {
		case 1:	//イズルード海底洞窟3層
			set '@mapname$,"iz_dun02.gat";
			setarray '@warp,234,206;
			break;
		case 2:	//アルデバラン時計塔地上3F
			set '@mapname$,"c_tower3.gat";
			setarray '@warp,64,143;
			break;
		case 3:	//グラストヘイム古城
			set '@mapname$,"glast_01.gat";
			setarray '@warp,368,303;
			break;
		case 4: break;	//fall through
		}
		if('@mapname$ != "") {
			if(Zeny < 4000) {
				mes "[ジョンダ投票広報職員]";
				mes "お客様、お金が足りないようですが。";
				break;
			}
			set Zeny,Zeny-4000;
			warp '@mapname$,'@warp[0],'@warp[1];
			end;
		}
	case 4:
		mes "[ジョンダ投票広報職員]";
		mes "ジョンダイベントは、お客様に";
		mes "常に最高のサービスを";
		mes "提供いたしております。";
		mes "それでは、良い一日を。";
		break;
	}
	close2;
	cutin "zonda_01",255;
	end;
}

yuno.gat,162,191,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::ジュノー		861
yuno.gat,153,191,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::ジュノー		874
prontera.gat,164,125,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::プロンテラ		116
prontera.gat,147,125,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::プロンテラ	874
//morocc.gat,164,114,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::モロク		116
//morocc.gat,155,114,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::モロク		874
moc_ruins.gat,104,133,3	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::モロク		116
moc_ruins.gat,97,133,5	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::モロク		874
geffen.gat,122,37,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::ゲフェン		116
geffen.gat,117,37,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::ゲフェン		874
payon.gat,158,182,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::フェイヨン		116
payon.gat,153,182,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::フェイヨン	874
alberta.gat,119,70,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::アルベルタ		116
alberta.gat,114,70,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::アルベルタ	874
aldebaran.gat,145,102,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::アルデバラン	116
aldebaran.gat,138,102,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::アルデラバン	874
lighthalzen.gat,163,60,4	duplicate(カプラ投票広報職員#vt)	カプラ投票広報職員::リヒタルゼン	861
lighthalzen.gat,154,60,6	duplicate(ジョンダ投票広報職員#vt)	ジョンダ投票広報職員::リヒタルゼン	874
