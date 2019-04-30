//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー              by Pneuma
//------------------------------------------------------------

//---------------------------------------------
// SHOP

-	shop	消耗品販売員::ac_shop1	-1,519,517,501,506,502,504,611,601,525,645,656,610
-	shop	道具販売員::ac_shop2	-1,1750,1770,1751,717
-	shop	ゼン::ac_shop3	-1,1351,1354,1116,1151,1154,1451,1454,1457
-	shop	エーイ::ac_shop4	-1,1204,1207,1210,1213,1216,1101,1104,1107,1110,1113,1122,1601,1604,1607,1501,1504,1507,1510,1519,1301,1401,1404,1407
-	shop	コウ::ac_shop5	-1,1701,1704,1707,1710,13150,13151,13102,13154,13155
-	shop	モーリ::ac_shop6	-1,2303,2305,2328,2323,2332,2307,2309,2312,2501,2503,2505,2101,2103,2401,2403,2405,2608,2627
-	shop	シャーレ::ac_shop7	-1,2211,2208,2220,2222,2232,2216,2226,2206,2228,2230,2212,2205,2203,2201,2239,2243,2242,2218,2241

ac_cl_hall.gat,155,35,4	script	消耗品販売員#ac	93,{/* 52611 */
	callshop "ac_shop1";
	end;
OnInit:
	waitingroom "消耗品 販売中", 0;
	end;
}
ac_cl_hall.gat,152,29,4	script	道具販売員#ac	82,{/* 52612 */
	callshop "ac_shop2";
	end;
OnInit:
	waitingroom "矢・ブルージェム 販売中", 0;
	end;
}
ac_cl_hall.gat,178,43,4	script	ゼン#ac	752,{/* 52615 */
	callshop "ac_shop3";
	end;
OnInit:
	waitingroom "両手武器 販売中", 0;
	end;
}
ac_cl_hall.gat,182,39,3	script	エーイ#ac	815,{/* 52616 */
	callshop "ac_shop4";
	end;
OnInit:
	waitingroom "片手武器 販売中", 0;
	end;
}
ac_cl_hall.gat,183,44,4	script	コウ#ac	732,{/* 52617 */
	callshop "ac_shop5";
	end;
OnInit:
	waitingroom "弓・銃 販売中", 0;
	end;
}
ac_cl_hall.gat,181,35,4	script	モーリ#ac	52,{/* 52618 */
	callshop "ac_shop6";
	end;
OnInit:
	waitingroom "防具 販売中", 0;
	end;
}
ac_cl_hall.gat,179,31,4	script	シャーレ#ac	731,{/* 52619 */
	callshop "ac_shop7";
	end;
OnInit:
	waitingroom "頭装備 販売中", 0;
	end;
}

//---------------------------------------------
// 冒険者アカデミー専用Lv判定
//  未転生1次職、BaseLevelが55未満 ならば真を返す。
function	script	AC_GetNovice	{
	return (BaseLevel<=55 && Upper!=1 && (Job<=6 || Job==Job_TaeKwon || Job==Job_Gunslinger || Job==Job_Ninja || Job==Job_SuperNovice));
}

//----------------------------------
// セーブ地点へワープ
// タールの転送と流用
function	script	AC_WarpTown	{
	switch(getarg(0)) {
	case 0: warp "prontera.gat",150,190; break;
	case 1: warp "izlude.gat",126,113; break;
	case 2: warp "morocc.gat",147,93; break;
	case 3: warp "alberta.gat",103,129; break;
	case 4: warp "geffen.gat",117,103; break;
	case 5: warp "payon.gat",155,203; break;
	case 6: warp "einbroch.gat",217,188; break;
	case 7: warp "amatsu.gat",148,134; break;
	case 8: warp "aldebaran.gat",138,110; break;
	}
	return;
}

//----------------------------------
// 初心者修練場からワープ後の表示
//
function	script	AC_NoviceInfo	{
	if(AC_AFLIER || AC_PASSPORT) end;
	set AC_AFLIER,1;
	if(BaseLevel>10 || Job!=0 || Upper!=0) {
		mes "[" + strcharinfo(0) + "]";
		mes "ん？";
		mes "‐チラシが落ちている‐";
		next;
		menu "チラシを見る",-;
		viewpoint 1, getarg(1), getarg(2), 100, 0xFF0000;
		mes "‐冒険者アカデミー生徒募集！‐";
		mes "‐新入生歓迎！‐";
		mes "‐受付場所はこちら！‐";
		mes "‐地図に^FF0000＋^000000で場所が記載してある‐";
		close;
	}
	mes "[インフォメーション]";
	mes "‐いよいよ壮大な冒険の始まりです！";
	mes "まずは冒険者が集まる";
	mes "冒険者アカデミーへ行ってみましょう‐";
	mes "‐新しい仲間がきっと見つかりますよ！";
	next;
	mes "[インフォメーション]";
	mes getarg(0);
	next;
	viewpoint 1, getarg(1), getarg(2), 100, 0xFF0000;
	mes "[インフォメーション]";
	mes "‐冒険者アカデミーは";
	mes "画面右上のミニマップに";
	mes "表示されている^FF0000＋^000000の場所へ";
	mes "行くと入学できますよ！‐";
	mes "‐ミニマップは^0000FFCtrl＋Tab^000000で";
	mes "表示の切り替えができます‐";
	close;
	return;
}

prontera.gat,146,51,0	script	#GT_07	139,5,5{
OnTouch:
	callfunc "AC_NoviceInfo","‐ここは首都^0000FFプロンテラ^000000‐",153,192;
}
geffen.gat,120,79,0	script	#GT_02	139,5,5{
OnTouch:
	callfunc "AC_NoviceInfo","‐ここは魔法都市^0000FFゲフェン^000000‐",116,109;
}
morocc.gat,156,94,0	script	#GT_03	139,5,5{
OnTouch:
	callfunc "AC_NoviceInfo","‐ここは砂漠の都市^0000FFモロク^000000‐",147,101;
}
payon.gat,166,67,0	script	#GT_04	139,5,5{
OnTouch:
	callfunc "AC_NoviceInfo","‐ここは山岳都市^0000FFフェイヨン^000000‐",159,205;
}
alberta.gat,114,58,0	script	#GT_05	139,5,5{
OnTouch:
	callfunc "AC_NoviceInfo","‐ここは港街^0000FFアルベルタ^000000‐",107,132;
}

//prontera.gat,279,356,0	script	#GT_01	139,{/* 52656 */}

//----------------------------------
// 教室棟ホール

ac_cl_hall.gat,159,31,4	script	忍者用具販売員#ac	49,{
	mes "[忍者用具販売員]";
	mes "やぁ、こんにちは。";
	mes "ここでは、忍者用品を";
	mes "販売しているよ。";
	if (BaseLevel<=55 && Job==Job_Ninja) {
		while(1) {
			next;
			mes "[忍者用具販売員]";
			mes "どの品物が欲しいんだい？";
			next;
			switch(select(  "手裏剣",
							"雨雲の手裏剣 <- Lv19以下 装備不可",
							"閃光の手裏剣 <- Lv39以下 装備不可",
							"氷閃石",
							"烈火石",
							"風鈴石",
							"影宝珠",
							"手甲 <- Lv19以下 装備不可",
							"購入をやめる")) {
			case 1: set '@itemid,13250; set '@price,4;  break;
			case 2: set '@itemid,13251; set '@price,10;  break;
			case 3: set '@itemid,13252; set '@price,20;  break;
			case 4: set '@itemid,7522; set '@price,150;  break;
			case 5: set '@itemid,7521; set '@price,150;  break;
			case 6: set '@itemid,7523; set '@price,150;  break;
			case 7: set '@itemid,7524; set '@price,300;  break;
			case 8:
				mes "[忍者用具販売員]";
				mes "手甲は1つ、10000Zenyだ。";
				mes "買うのかい？";
				next;
				if(select("買わない","買う")==1) {
					mes "[忍者用具販売員]";
					mes "おや？";
					mes "手甲は必要ないのかな？";
					continue;
				}
				if(Zeny < 10000) {
					mes "[忍者用具販売員]";
					mes "どうやら";
					mes "お金が足りないみたいだよ？";
					continue;
				}
				if(checkweight(2117,1)==0) {
					mes "[忍者用具販売員]";
					mes "どうやら";
					mes "そんなにもてないみたいだよ？";
					continue;
				}
				mes "[忍者用具販売員]";
				mes "はい、どうぞ。";
				mes "約束の商品だよ。";
				set Zeny,Zeny-10000;
				getitem 2117,1;
				continue;
			default:
				mes "[忍者用具販売員]";
				mes "そうか。";
				mes "また、何か必要になったら";
				mes "おいでよ。";
				close;
			}
			mes "[忍者用具販売員]";
			mes getitemname('@itemid)+ "は1つ、" +'@price+ "Zenyだ。";
			mes "どのくらい欲しいんだい？";
			mes "1～1000の間で、欲しい数を";
			mes "入力してくれ。";
			mes "0を入力すると";
			mes "購入をやめられるよ。";
			next;
			input '@num;
			if('@num < 0 || '@num > 1000) {
				mes "[忍者用具販売員]";
				mes "一度に購入出来るのは";
				mes "1000個までだよ。";
				continue;
			}
			if('@num == 0) {
				mes "[忍者用具販売員]";
				mes "おや？";
				mes getitemname('@itemid)+ "は必要ないのかな？";
				continue;
			}
			if(Zeny < '@price*'@num) {
				mes "[忍者用具販売員]";
				mes "どうやら";
				mes "お金が足りないみたいだよ？";
				continue;
			}
			if(checkweight('@itemid,'@num)==0) {
				mes "[忍者用具販売員]";
				mes "どうやら";
				mes "そんなにもてないみたいだよ？";
				continue;
			}
			mes "[忍者用具販売員]";
			mes "はい、どうぞ。";
			mes "約束の商品だよ。";
			set Zeny,Zeny-'@price*'@num;
			getitem '@itemid,'@num;
			continue;
		}
	} else {
		next;
		set '@novice, callfunc("AC_GetNovice");
		if ('@novice) {
			mes "[忍者用具販売員]";
			mes "申し訳ないけど、";
			mes "忍者以外には";
			mes "忍者用品を";
			mes "売ることは出来ないんだ。";
			mes "遠くから運んできていて、";
			mes "在庫が少ないんだよ。";
			close;
		} else {
			mes "[忍者用具販売員]";
			mes "申し訳ないけど、";
			mes "熟練の冒険者には";
			mes "忍者用品を";
			mes "売ることは出来ないんだ。";
			mes "駆け出しの冒険者に";
			mes "渡すものがないと困るからね。";
			close;
		}
	}
	end;
OnInit:
	waitingroom "忍者用具 販売中", 0;
	end;
}

ac_cl_hall.gat,158,34,4	script	銃弾販売員#ac	85,{
	mes "[銃弾販売員]";
	mes "やぁ、こんにちは。";
	mes "ここでは、銃用の弾丸を";
	mes "販売しているよ。";
	if (Job==Job_Gunslinger && BaseLevel<=55) {
		while(1){
			next;
			mes "[銃弾販売員]";
			mes "どの弾丸が欲しいんだい？";
			next;
			set '@sel, select("バレット","シルバーバレット","ブラッドバレット","購入をやめる");
			mes "[銃弾販売員]";
			switch('@sel){
			case 1:
				set '@itemid,13200;
				set '@price,1;
				mes "バレットは1つ、１Zenyだ。"; //全角文字で本家通り
				break;
			case 2:
				set '@itemid,13201;
				set '@price,15;
				mes "シルバーバレットは1つ、15Zenyだ。";
				break;
			case 3:
				set '@itemid,13202;
				set '@price,30;
				mes "ブラッドバレットは1つ、30Zenyだ。";
				break;
			default:
				mes "そうか。";
				mes "また、弾丸が必要になったら";
				mes "おいでよ。";
				close;
			}
			mes "どのくらい欲しいんだい？";
			mes "1～1000の間で、欲しい数を";
			mes "入力してくれ。";
			mes "0を入力すると";
			mes "購入をやめられるよ。";
			next;
			input '@num;
			if('@num < 0 || '@num > 1000) {
				mes "[銃弾販売員]";
				mes "一度に購入出来るのは";
				mes "1000個までだよ。";
				continue;
			}
			if('@num == 0) {
				mes "[銃弾販売員]";
				mes "おや？";
				mes getitemname('@itemid)+ "は必要ないのかな？";
				continue;
			}
			if(Zeny < '@price*'@num) {
				mes "[銃弾販売員]";
				mes "どうやら";
				mes "お金が足りないみたいだよ？";
				continue;
			}
			if(!checkweight('@itemid,'@num)) {
				mes "どうやら";
				mes "そんなにもてないみたいだよ？";
				continue;
			}
			mes "[銃弾販売員]";
			mes "はい、どうぞ。";
			mes "約束の商品だよ。";
			set Zeny,Zeny-'@price*'@num;
			getitem '@itemid,'@num;
		}
	} else {
		next;
		set '@novice, callfunc("AC_GetNovice");
		if ('@novice) {
			mes "[銃弾販売員]";
			mes "申し訳ないけど、";
			mes "ガンスリンガー以外には";
			mes "弾丸を売ることは出来ないんだ。";
			close;
		} else {
			mes "[銃弾販売員]";
			mes "申し訳ないけど、";
			mes "熟練の冒険者の方には";
			mes "弾丸を売ることは出来ないんだ。";
			mes "駆け出しの冒険者のために";
			mes "在庫を取っておく必要があるんだ。";
			close;
		}
	}
	end;
OnInit:
	waitingroom "銃弾 販売中", 0;
	end;
}

//------------------------------------------------------------------------------
// 教室棟 1F

//カプラサービスポスト
ac_cl_area.gat,41,145,4	script	カプラサービス	888,{
	mes "‐(株)カプラサービスは、";
	mes "いつも皆様のそばに‐";
	mes " ";
	mes "‐どのサービスを利用する？‐";
	next;
	switch(select("位置セーブサービス","倉庫サービス -> 0z","注意書きを読む","やめる")){
	case 1:
		savepoint "ac_cl_area.gat",48,128;
		mes "‐セーブしました‐";
		mes "‐ご利用ありがとうございます‐";
		mes " ";
		mes "‐(株)カプラサービスは、";
		mes "いつも皆様のそばに‐";
		close;
	case 2:
		if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
			mes "‐倉庫は基本スキルレベル6を";
			mes "習得してから利用可能となります‐";
			mes " ";
			mes "‐(株)カプラサービスは、";
			mes "いつも皆様のそばに‐";
			close;
		}
		openstorage;
		close;
	case 3:
		mes "‐アカデミーの倉庫は";
		mes "無料で利用できる倉庫です‐";
		mes "‐倉庫はきれいに使いましょう‐";
		close;
	default:
		mes "‐利用するのをやめた‐";
		close;
	}
	end;
OnInit:
	waitingroom "カプラサービス", 0;
	end;
}

//ミッド
ac_cl_area.gat,45,146,4	script	ミッド#ac_area	429,{
	set '@novice, callfunc("AC_GetNovice");
	cutin "jpn_mid01",2;
	if(AC_PASSPORT==2){
		mes "[ミッド]";
		mes "こんにちは！";
		mes "冒険者アカデミーへ";
		mes "入学おめでとう！";
		next;
		mes "[ミッド]";
		mes "冒険者アカデミーは";
		mes "世界中の冒険者のために";
		mes "設立された学校なんだ。";
		mes "わからない事があったら、";
		mes "先輩や先生達に聞いてみてね。";
		next;
		mes "[ミッド]";
		mes "入学祝にキミにプレゼントがあるよ。";
		next;
		set AC_PASSPORT,5;
		if(!checkweight(5406,1)){
			mes "[ミッド]";
			mes "あれ？";
			mes "荷物がいっぱいみたいだね。";
			mes "沢山の種類を持ちすぎている";
			mes "みたいだね。";
			mes "ちょっと種類数を減らしてきてね。";
			goto L_END;
		}
		getitem 5406,1;
		set AC_PASSPORT,3; // 新入生祝い完了
		mes "[ミッド]";
		mes ('@novice ?"これを装備して、頑張ってね！":"キミには必要ないかもしれないけど");
		mes "これで冒険者アカデミーの一員だ！";
		goto L_END;
	}
	if(AC_PASSPORT==5){
		mes "[ミッド]";
		mes "荷物は軽くしてきたかい？";
		mes "さあ、入学祝だよ！";
		next;
		mes "‐所持アイテムの種類数に2つ以上の";
		mes "空きがあることを確認してください‐";
		mes "‐空きがない状態で「はい」を";
		mes "選択した場合は、アイテムを";
		mes "ロストする可能性があります‐";
		next;
		mes "‐空きがない場合は、";
		mes "一旦「いいえ」を選択し、";
		mes "アイテムの種類数を2つ以上";
		mes "空けてから再度話しかけてください‐";
		mes "‐アイテムを受け取りますか？‐";
		next;
		if(select("いいえ","はい")==1){
			mes "[" + strcharinfo(0) + "]";
			mes "(アイテム数を確認してみよう。)";
			close;
		}
		if(!checkweight(5406,1)){
			mes "[ミッド]";
			mes "あれ？";
			mes "荷物がいっぱいみたいだね。";
			mes "沢山の種類を持ちすぎている";
			mes "みたいだね。";
			mes "ちょっと種類数を減らしてきてね。";
			goto L_END;
		}
		getitem 5406,1;
		set AC_PASSPORT,3; // 新入生祝い完了
		mes "[ミッド]";
		mes ('@novice ?"これを装備して、頑張ってね！":"キミには必要ないかもしれないけど");
		mes "これで冒険者アカデミーの一員だ！";
		goto L_END;
	}
	if(AC_RANK==7){ // 初心者以外未調査なのでとりあえず共通です。
		mes "[ミッド]";
		mes "一次課程修了試験合格おめでとう！";
		mes "一次課程修了のお祝いに";
		mes "君にはこれをあげよう！";
		next;
		if(!checkweight(2751,10)){
			mes "[ミッド]";
			mes "あれ？";
			mes "荷物がいっぱいみたいだね。";
			mes "沢山の種類を持ちすぎている";
			mes "みたいだね。";
			mes "ちょっと種類数を減らしてきてね。";
			goto L_END; 
		}
		getitem 2751,1;
		set AC_RANK,8;
		mes "[ミッド]";
		mes "このバッジは";
		mes "一次過程修了の証だよ！";
		mes "胸を張って、胸につけてね！";
		next;
		mes "[ミッド]";
		mes "一次過程は終了したけど、";
		mes "君の冒険はまだこれからだ！";
		mes "次は君が初心者の皆に";
		mes "教えていく番だね！";
		goto L_END;
	}
	if('@novice && AC_RANK<7){
		switch(AC_RANK){
		case 0:
			mes "[ミッド]";
			mes "こんにちは！";
			mes "冒険者アカデミーにようこそ！";
			next;
			if(AC_CREDIT>0){
				mes "[ミッド]";
				mes "君はまだ入って間もないようだね。";
				mes "まだわからないことばかりだろうけど、";
				mes "少しずつ覚えていこう！";
				mes "アカデミーのことについてなら、";
				mes "僕に何でも聞いてくれていいよ。";
				break;
			}
			// 2010/05/25 アカデミー改革 ポリン団参上！で追加。
			mes "[ミッド]";
			mes "君はまだ入って間もないようだね。";
			mes "まだ何も決めて無いなら、";
			mes "^FF0000ルーンの仕事^000000を";
			mes "手伝ったりするのもいいかも。";
			mes "いろんな依頼が来るから、";
			mes "世界中を巡れると思うよ。";
			next;
			mes "[ミッド]";
			mes "^FF0000ルーン^000000は僕のすぐ隣にいる";
			mes "ピンク色の髪をした女性だよ。";
			mes "詳しい話はルーンから";
			mes "聞いてみてね。";
			next;
			mes "[ミッド]";
			mes "すぐにモンスターと戦闘して、";
			mes "腕だめしをしたいなら、";
			mes "^FF0000実習室や特別室^000000に";
			mes "行くのがいいかな。";
			next;
			mes "[ミッド]";
			mes "戦いに行くときは";
			mes "受付や講習の時に渡された";
			mes "装備品や回復アイテムの";
			mes "準備を忘れずにね。";
			next;
			mes "[ミッド]";
			mes "^FF0000実習室や特別室^000000の入り口は";
			mes "ここから左上に行った所にあるよ。";
			mes "近くにポリン団と名乗っている";
			mes "^0000FFミスティ^000000がいるはずだ。";
			next;
			mes "[ミッド]";
			mes "まだわからないことばかりだろうけど、";
			mes "少しずつ覚えていこう！";
			mes "アカデミーのことについてなら、";
			mes "僕に何でも聞いてくれていいよ。";
			break;
		case 1:
			mes "[ミッド]";
			mes "やぁ、君かい。";
			mes "もうアカデミーには慣れたかな？";
			mes "何か僕に聞きたいことでも";
			mes "あるのかな？";
			break;
		case 2:case 3:case 4: //未調査かもしれない
			mes "[ミッド]";
			mes "やぁ、君かい。";
			mes "君もだいぶ、";
			mes "アカデミーに馴染んできたね。";
			mes "何か僕に聞きたいことでも";
			mes "あるのかな？";
			break;
		case 5:
			mes "[ミッド]";
			mes "やぁ、君かい。";
			mes "君、先生の中では成績優秀だって";
			mes "噂だよ。";
			mes "もうすぐ第一過程修了だね。";
			mes "頑張ってね！";
			mes "今日は何か僕にようかい？";
			break;
		case 6:
			mes "[ミッド]";
			mes "こんにちは！";
			mes "冒険者アカデミーにようこそ！";
			next;
			mes "[ミッド]";
			mes "このアカデミーのことなら、なんでも";
			mes "僕に聞いてくれ！";
			mes "……といっても、もう君に";
			mes "教えられることはないのかな？";
			mes "もうすぐ一次課程修了だね！";
			mes "今日は何か僕にようかい？";
			break;
		}
	} else {
		mes "[ミッド]";
		mes "やぁ、こんにちは！";
		mes "今日は僕に何のようだい？";
	}
	next;
	if('@novice){ menu "どうしたらいいのか聞く",L_TODO,"大事な話を聞きなおす",L_IMPORTANT,"冒険者アカデミーについて",L_ABOUT,"学校内について",L_SCHOOL,"世界地図をみせて",L_VIEWWORLD,"職業の書がほしい",L_GIVEBOOK,"雑談をする",L_TALK; }
	else { menu "冒険者アカデミーについて",L_ABOUT,"学校内について",L_SCHOOL,"世界地図をみせて",L_VIEWWORLD,"雑談をする",L_TALK; }
L_TODO:
	// 2010/05/25 アカデミー改革 ポリン団参上！で追加。
	//どうしたらいいのか聞く
	mes "[ミッド]";
	mes "えーと、そうだな。";
	L_REP_01:
	mes "まずは、試験を受けるために、";
	mes "単位を取得することが必要だね。";
	next;
	mes "[ミッド]";
	mes "単位を取得するには";
	mes "^0000FFルーン^000000の手伝いをするか、";
	mes "^000000ポリン団のミスティー^000000達の";
	mes "手助けをするといいね。";
	next;
	mes "[ミッド]";
	mes "単位が取得できたら、ルーンから";
	mes "^FF0000第一過程の試験^000000を受けるといい。";
	mes "試験はいくつもあるから、";
	mes "順番にクリアしていこう。";
	next;
	mes "[ミッド]";
	mes "そして、第一過程をすべて修了したら、";
	mes "記念に^FF0000アカデミーバッジ[0]^000000を";
	mes "君にプレゼントするよ！";
	next;
	mes "[インフォメーション]";
	mes "アカデミーバッジ[0]の";
	mes "効果を確認しますか？";
	next;
	if(select("はい","いいえ")==1){
		mes "[インフォメーション]";
		mes "‐アカデミーバッジ[0]‐";
		mes "第1過程修了でもらえる";
		mes "アカデミーのバッジ。";
		next;
		mes "[インフォメーション]";
		mes "‐アカデミーバッジ[0]‐";
		mes "バッジの形には";
		mes "一人前の冒険者が";
		mes "知識を蓄えたのち";
		mes "巣立っていけるようにと";
		mes "祈りが込められている。";
		next;
		mes "[インフォメーション]";
		mes "‐アカデミーバッジ[0]‐";
		mes "BaseLv79以下の時、";
		mes "MaxHP + 400";
		mes "MaxSP + 200";
		mes "系列 : ^777777アクセサリー^000000";
		mes "防御 : ^7777770^000000";
		next;
		mes "[インフォメーション]";
		mes "‐アカデミーバッジ[0]‐";
		mes "重量 : ^77777710^000000";
		mes "装備 : ^777777全ての職業^000000";
		mes "@next";
		mes "[インフォメーション]";
		mes "‐もう一度ミッドの話を";
		mes "聞きますか？‐";
		next;
		if(select("はい、もう一度聞く","いいえ、必要ない")==1){
			mes "[ミッド]";
			mes "よし、もう一度説明しよう。";
			goto L_REP_01;
		}
	}
	mes "[ミッド]";
	mes "それじゃ、がんばってね。";
	mes "わからないことがあったら、";
	mes "僕に何でも聞いてくれよ。";
	goto L_END;
L_IMPORTANT:
	//大事な話を聞きなおす(未調査)
	mes "[ミッド]";
	mes "あれ？";
	mes "今、君に説明してあげられる";
	mes "ことは無いみたいだよ。";
	next;
	menu "やめる";
	mes "[ミッド]";
	mes "他に聞きたいことがあったら、";
	mes "僕に聞いてね。";
	goto L_END;
L_ABOUT:
	mes "[ミッド]";
	mes "冒険者アカデミーは冒険者のために";
	mes "設立された学校だよ。";
	mes "わからない事があったら、";
	mes "先輩や先生に聞いて、";
	mes "いろいろと教わってみてね。";
	next;
	mes "[ミッド]";
	mes "冒険者アカデミーでは";
	mes "一人前の冒険者になるまで";
	mes "いろいろなサポートを";
	mes "行っているよ。";
	next;
	mes "[ミッド]";
	mes "冒険者アカデミーで";
	mes "一人前として認められるには";
	mes "条件があるんだ。";
	mes "1つ、Baselv56以上になった！";
	mes "2つ、2次職以上の職業についた！";
	mes "3つ、生まれ変わり！";
	next;
	if(!'@novice){
		mes "[ミッド]";
		mes "キミはもう一人前の冒険者だね！";
		mes "冒険者の先輩として、";
		mes "駆け出しの冒険者を";
		mes "助けてほしいな！";
		goto L_END;
	}
	mes "[ミッド]";
	mes "どれか一つでも条件に";
	mes "当てはまれば、一人前さ！";
	mes "一人前になるまでは、";
	mes "皆一緒の駆け出しの冒険者。";
	mes "ここで仲間を見つけて世界を";
	mes "いろいろ巡ってみるといいよ！";
	goto L_END;
L_SCHOOL:
	mes "[ミッド]";
	mes "どの場所について聞きたいんだい？";
	next;
	switch(select("1F 講習室","1F 自習室","1F 実習室","1F 販売","1F 図書室","2F 試験室","2F 資料室","もう聞くことは無い")) {
	case 1:
		mes "[ミッド]";
		mes "講習室だね。";
		mes "講習室では駆け出しの";
		mes "冒険者のための講義を";
		mes "行っているよ。";
		next;
		mes "[ミッド]";
		mes "プロン、アルディ、フェンから";
		mes "冒険に必要な基礎知識を";
		mes "学ぶことが出来るんだ。";
		next;
		mes "[ミッド]";
		mes "講習室はこの";
		mes "[教室棟1F]の隣にあるよ。";
		mes "この部屋にある看板を探してみてね。";
		next;
		goto L_SCHOOL;
	case 2:
		mes "[ミッド]";
		mes "自習室だね。";
		mes "自習室ではいろんなアドバイスを";
		mes "行っているんだ。";
		mes "困ったことがあったら、";
		mes "行ってみるといいよ。";
		next;
		mes "[ミッド]";
		mes "ルティーからは職業について、";
		mes "フィーからはクエストスキルに";
		mes "ついて、そして、ユタからは";
		mes "転職クエストについてのアドバイスが";
		mes "聞けるはずだよ。";
		next;
		mes "[ミッド]";
		mes "自習室はこの[教室棟1F]の";
		mes "隣にあるよ。";
		mes "この部屋にある看板を探してみてね。";
		next;
		goto L_SCHOOL;
	case 3:
		mes "[ミッド]";
		mes "実習室・特別室だね。";
		mes "実習室では様々なモンスターが";
		mes "棲息していて、調査や、";
		mes "モンスターとの戦闘実習を";
		mes "行うことが出来るんだ。";
		next;
		mes "[ミッド]";
		mes "実習室は、君たちの強さによって";
		mes "開放される場所が違うから、";
		mes "いける場所を覚えておいてね。";
		next;
		mes "[ミッド]";
		mes "リカバリープレートは";
		mes "冒険者アカデミー生全てが";
		mes "利用できる、多人数での調査を";
		mes "行う為の施設になるよ。";
		next;
		//mes "[ミッド]";
		//mes "大人数パーティで利用すると、";
		//mes "調査やモンスターとの戦闘実習が";
		//mes "楽になるから、利用してみてね。";
		//mes "もちろん、少人数パーティでも";
		//mes "利用できるけど、人数が少ないほど";
		//mes "効果が低くなるから気をつけてね。";
		//next;
		//mes "[ミッド]";
		//mes "lv1～lv25、lv20～lv35、lv30～lv45";
		//mes "用の実習室は";
		//mes "この[教室棟1F]の隣にあるよ。";
		//mes "この部屋にある看板を探してみてね。";
		//next;
		//mes "[ミッド]";
		//mes "他にも隠された実習室が";
		//mes "あるらしいけどね。";
		//next;
		//goto L_SCHOOL;
		//2010/04/13修正
		mes "[ミッド]";
		mes "上級者になればなるほど";
		mes "リカバリーを実行する時の";
		mes "^FF0000パワーが必要^000000になる。";
		mes "上級者は、パワーの充電に";
		mes "時間がかかるから、";
		mes "注意が必要だよ。";
		next;
		goto L_SCHOOL;
	case 4:
		mes "[ミッド]";
		mes "この[教室棟1F]の";
		mes "隣にある教室棟ホールには";
		mes "いろいろな装備を取り揃えている";
		mes "販売員がたっているよ。";
		next;
		mes "[ミッド]";
		mes "基本的なものは";
		mes "大体そろっているから、";
		mes "利用してみてね。";
		next;
		goto L_SCHOOL;
	case 5:
		mes "[ミッド]";
		mes "エントランスホールの隣にある";
		mes "図書室では、様々なことを";
		mes "調べることが出来るよ。";
		next;
		mes "[ミッド]";
		mes "基本的な操作方法だけじゃなくて、";
		mes "街中でよく見かける会話や";
		mes "スキルについての詳細など、";
		mes "解らないことがあれば";
		mes "すぐに調べられるんだ。";
		next;
		goto L_SCHOOL;
	case 6:
		mes "[ミッド]";
		mes "[教室棟2F]には";
		mes "試験室があるよ。";
		next;
		mes "[ミッド]";
		mes "ルーンから試験を受けるように";
		mes "言われたら、試験室にいる";
		mes "ガルドに話しかけて";
		mes "試験を受けてね。";
		next;
		goto L_SCHOOL;
	case 7:
		mes "[ミッド]";
		mes "[教室棟2F]には";
		mes "資料室があるよ。";
		next;
		mes "[ミッド]";
		mes "資料室にいるヨン爺さんは";
		mes "とっても物知りだから、";
		mes "いろいろな場所を知っているんだ。";
		next;
		goto L_SCHOOL;
	case 8:
		mes "[ミッド]";
		mes "また聞きたくなったら、おいでよ。";
		goto L_END;
	}
	goto L_END;
	
L_VIEWWORLD:
	cutin "jpn_mid01",255;
	cutin "world_map_001",3;
	mes "[ミッド]";
	mes "これがミッドガルド大陸がある";
	mes "世界地図だよ。";
	next;
	mes "[ミッド]";
	mes "世界中には多くの冒険者が";
	mes "旅をしている。";
	mes "多くの都市が存在し、";
	mes "様々な人々が暮らしているんだ。";
	next;
	mes "[ミッド]";
	mes "この地図に書かれているもの";
	mes "以外にも町はあるよ。";
	mes "新しい町を見つけたら、";
	mes "冒険の途中で立ち寄ってみても";
	mes "いいかもね。";
	close;
L_GIVEBOOK:
	//2010/04/13追加
	mes "[ミッド]";
	mes "職業の書がほしいのかい？";
	next;
	if(select("はい","いいえ")==2){
		mes "[ミッド]";
		mes "あれ？";
		mes "いらないのかい。";
		mes "失くしたりしたのだったら、";
		mes "僕が本を貰ってきてるから、";
		mes "あげるからね。";
		goto L_END;
	}
	if(checkweight(11055,1)) {
		switch(Job){
			case Job_Swordman:    getitem 11025,1; break; //ソードマンの書
			case Job_Thief:       getitem 11028,1; break; //シーフの書
			case Job_Archer:      getitem 11031,1; break; //アーチャーの書
			case Job_Acolyte:     getitem 11034,1; break; //アコライトの書
			case Job_Magician:    getitem 11037,1; break; //マジシャンの書
			case Job_Merchant:    getitem 11040,1; break; //マーチャントの書
			case Job_TaeKwon:     getitem 11043,1; break; //テコンキッドの書
			case Job_Ninja:       getitem 11046,1; break; //忍者の書
			case Job_Gunslinger:  getitem 11049,1; break; //ガンスリンガーの書
			case Job_SuperNovice: getitem 11052,1; break; //スーパーノービスの書
			default: getitem 11055,1;
		}
		mes "[ミッド]";
		mes "はい。";
		mes "それじゃ、がんばって。";
		mes " ";
		mes "‐ミッドが本を渡してくれた‐";
		goto L_END;
	}
	//未調査
	mes "[ミッド]";
	mes "君は持ち物を少し整理した";
	mes "ほうがいいね。";
	mes "大事な物はカプラサービスを";
	mes "利用して保管して、";
	mes "いらないものは商人に売るといいよ。";
	goto L_END;
L_TALK:
	switch(rand(12)){
	case 0:
		mes "[ミッド]";
		mes "冒険者アカデミーのマークは";
		mes "真の知恵、賢者の石を表す、";
		mes "六芒星からきているんだよ。";
		goto L_END;
	case 1:
		mes "[ミッド]";
		mes "この学校には今の図書室とは";
		mes "違う図書室があるらしいよ。";
		next;
		mes "[ミッド]";
		mes "僕も詳しいことは";
		mes "全くわからないんだけどね。";
		goto L_END;
	case 2:
		mes "[ミッド]";
		mes "することが無くて困っているのかい？";
		next;
		mes "[ミッド]";
		mes "それなら、ルーンに話を聞いてみてよ。";
		mes "冒険者アカデミーに";
		mes "よせられる依頼を";
		mes "詳しく説明してくれるよ。";
		goto L_END;
	case 3:
		mes "[ミッド]";
		mes "隠された実習室に";
		mes "ついて知っているかい？";
		next;
		mes "[ミッド]";
		mes "なんでも、教室棟ホールのどこかに";
		mes "昔は開放されていた実習室が";
		mes "あるらしいんだ。";
		next;
		mes "[ミッド]";
		mes "その実習室は、あぶないから";
		mes "何かで封印されたって噂だよ。";
		goto L_END;
	case 4:
		mes "[ミッド]";
		mes "今はこうやって先生をしているけど";
		mes "僕も昔は冒険者だったんだ。";
		mes "ルティエっていう街についた時は";
		mes "興奮したなぁ。";
		next;
		mes "[ミッド]";
		mes "生まれて初めて";
		mes "雪というものを見たんだ。";
		mes "ちょっと寒かったけど、";
		mes "楽しかったよ。";
		next;
		mes "[ミッド]";
		mes "僕の場合は";
		mes "アルデバランにいたサンタさんが";
		mes "転送してくれたんだけど。";
		mes "今もいるのかな？";
		goto L_END;
	case 5:
		mes "[ミッド]";
		mes "このアカデミーは";
		mes "皆の寄付によって成り立っているんだ。";
		next;
		mes "[ミッド]";
		mes "皆、君のようなすばらしい冒険者を";
		mes "心から待ちわびているんだよ。";
		goto L_END;
	case 6:
		mes "[ミッド]";
		mes "君は死者の世界を信じるかい？";
		mes "皆には信じてもらえないけど、";
		mes "僕は死者の世界に";
		mes "いったことがあるんだ。";
		next;
		mes "[ミッド]";
		mes "死者の世界は本当にあるんだよ。";
		mes "あれは確か、ウンバラで";
		mes "バンジージャンプに挑戦した時";
		mes "だったかな……";
		next;
		mes "[ミッド]";
		mes "詳しいことは";
		mes "もう覚えてないんだけど、";
		mes "あの体験は夢じゃなかったと";
		mes "信じているんだ。";
		goto L_END;
	case 7:
		mes "[ミッド]";
		mes "ルーンはとてもしっかりしている";
		mes "ように見えるだろう？";
		next;
		mes "[ミッド]";
		mes "でも、実はとっても";
		mes "甘い物に目が無いんだよ。";
		next;
		mes "[ミッド]";
		mes "昔はよく、アイスクリームを";
		mes "おごらされたなぁ……";
		goto L_END;
	case 8:
		mes "[ミッド]";
		mes "冒険者アカデミーでは";
		mes "沢山の冒険者を募っているんだ。";
		next;
		mes "[ミッド]";
		mes "君の知り合いで、まだ";
		mes "アカデミーに入っていない人がいたら、";
		mes "ぜひ、声をかけてみてよね。";
		goto L_END;
	case 9:
		mes "[ミッド]";
		mes "この学校にはとても有名な";
		mes "先生がいるんだ。";
		next;
		mes "[ミッド]";
		mes "モンスターの研究を";
		mes "している先生なんだけど、";
		mes "凄く……";
		mes "いやちょっとかわっててね！";
		next;
		mes "[ミッド]";
		mes "どう変わっているのかは、";
		mes "実際に会ってみれば";
		mes "すぐにわかるよ！";
		goto L_END;
	case 10:
		mes "[ミッド]";
		mes "そういえばこの前、校長が";
		mes "この施設を拡張したいって";
		mes "言ってたなぁ。";
		next;
		mes "[ミッド]";
		mes "しばらくは無理そうだけど、";
		mes "いつか、校舎が大きくなるかも";
		mes "しれないね。";
		goto L_END;
	case 11:
		mes "[ミッド]";
		mes "2階にいるヨン爺さんには";
		mes "もうあったかい？";
		next;
		mes "[ミッド]";
		mes "彼は、本が好きすぎて、";
		mes "ずっと資料室に入り浸っているんだ。";
		next;
		mes "[ミッド]";
		mes "……彼の仕事は一体なんなんだろう？";
		goto L_END;
	}
L_END:
	close2;
	cutin "jpn_mid01",255;
	end;
OnInit:
	waitingroom "初心者はこちらへ", 0;
	end;
}


//モッド
ac_cl_area.gat,61,166,4	script	モッド#AC	704,{
	set '@novice, callfunc("AC_GetNovice");
	if (!'@novice) {
		mes "[モッド]";
		mes "こんにちは。";
		mes strcharinfo(0)+ "さん";
		mes "私の力は必要ないみたいですね。";
		mes "これからはアカデミー内だけでなく、";
		mes "いろんなところを旅してみてください。";
		close;
	}
	mes "[モッド]";
	mes strcharinfo(0)+ "さん、";
	mes "私はここでカートの貸し出しを";
	mes "行っているんですよ。";
	next;
	mes "[モッド]";
	mes "カートを利用しますか？";
	mes "無料ですよ。";
	next;
	switch(select("カートを利用する","カートの利用について","やっぱりやめる")){
	case 1:
		if(Job!=Job_Merchant && Job!=Job_SuperNovice){
			mes "[モッド]";
			mes "あれ？";
			mes "カートは商人と";
			mes "その上位職、もしくは";
			mes "スーパーノービスでないと";
			mes "利用できませんよ。";
			close;
		}
		setcart;
		mes "[モッド]";
		mes "また必要になったら";
		mes "いらしてくださいね。";
		close;
	case 2:
		mes "[モッド]";
		mes "カートは商人とその上位職、";
		mes "それとスーパーノービスが";
		mes "利用できるんです。";
		mes "「プッシュカート」スキルを";
		mes "習得しないと利用することは";
		mes "できませんよ。";
		close;
	default:
		mes "[モッド]";
		mes "それじゃ、また。";
		close;
	}
OnInit:
	waitingroom "カートの貸し出し",0;
}

//タール
ac_cl_area.gat,57,173,2	script	タール#AC	931,{
	set '@novice, callfunc("AC_GetNovice");
	if ('@novice) {
		if(AC_RANK==0){
			mes "[タール]";
			mes "あ、";
			mes strcharinfo(0)+ "さん";
			mes "ですね。";
			mes "僕はここで転送のお手伝いを";
			mes "させてもらってるんです。";
		} else
		if(AC_RANK<3){
			mes "[タール]";
			mes strcharinfo(0)+ "さん";
			mes "じゃないですか。";
			mes "今日も調子いいみたいですね。";
		} else
		if(AC_RANK<=6){
			mes "[タール]";
			mes "大活躍してるみたいですね。";
			mes strcharinfo(0)+ "さん";
			mes "今度、旅の話でも聞かせてください。";
		} else
		if(AC_RANK>=7){
			mes "[タール]";
			mes "立派になりましたね。";
			mes strcharinfo(0)+ "さん";
			mes "なら、何でもできそうですね。";
		}
		next;
		if(Job==Job_Novice) goto L_NOVICE;
		mes "[タール]";
		mes "どこに行きますか？";
		mes "アカデミーの登録地点は";
		mes "無料ですよ。";
		next;
		if('mapprice==0) {
			setarray 'mapprice,  500,400,350,300,250,200
								,400,300,250,200,150,100
								,650,600,500,400,300,200
								,750,700,600,500,400,300
								,750,700,600,500,400,300
								,650,600,500,400,300,200;
		}
		set '@rank,(AC_RANK < 5 ? AC_RANK : 5);
		set '@num, select(
			"プロンテラ -> " +(AC_SAVE_MAP!=0 ? 'mapprice[    '@rank] : 0)+ "z",
			"イズルード -> " +(AC_SAVE_MAP!=1 ? 'mapprice[1*6+'@rank] : 0)+ "z",
			"モロク -> "     +(AC_SAVE_MAP!=2 ? 'mapprice[2*6+'@rank] : 0)+ "z",
			"アルベルタ -> " +(AC_SAVE_MAP!=3 ? 'mapprice[3*6+'@rank] : 0)+ "z",
			"ゲフェン -> "   +(AC_SAVE_MAP!=4 ? 'mapprice[4*6+'@rank] : 0)+ "z",
			"フェイヨン -> " +(AC_SAVE_MAP!=5 ? 'mapprice[5*6+'@rank] : 0)+ "z",
			"やっぱりやめる")-1;
		if ('@num==6) goto L_CANCEL;
		set '@price,(AC_SAVE_MAP!='@num ? 'mapprice['@num]['@rank] : 0);
		if(Zeny<'@price) {
			mes "[タール]";
			mes "おっと、お金が足りませんよ。";
			mes "また来てくださいね。";
			close;
		}
		mes "[タール]";
		mes "それじゃ、転送しますね。";
		close2;
		set Zeny,Zeny-'@price;
		callfunc "AC_WarpTown",'@num;
		end;

	} else {
		mes "[タール]";
		mes "こんにちは。";
		mes strcharinfo(0)+ "さん";
		mes "今日も元気そうですね。";
		next;
		mes "[タール]";
		mes "あなたには";
		mes "僕の力は必要ないみたいですね。";
		mes "アカデミーの先輩として、";
		mes "後輩を見てあげてください。";
		mes " ";
		mes "登録した街へ戻りますか？";
		next;
		menu "戻る",L_RETURN,"戻らない",-;
		mes "[タール]";
		mes "戻りたくなったら、";
		mes "いつでも言ってくださいね。";
		close;
	L_RETURN:
		mes "[タール]";
		mes "それじゃ、転送しますね。";
		close2;
		callfunc "AC_WarpTown",AC_SAVE_MAP;
		end;
	}
L_NOVICE:
	mes "[タール]";
	mes "あなたはノービスの方ですね。";
	mes "ノービスの方には";
	mes "転職のサポートを";
	mes "無料で行っていますよ。";
	mes " ";
	mes "どこに行きますか？";
	next;
	set '@num,select("プロンテラ -> 0z","イズルード -> 0z","モロク -> 0z","アルベルタ -> 0z","ゲフェン -> 0z","フェイヨン -> 0z","アインブロック -> 0z","アマツ -> 0z","アルデバラン -> 0z","やっぱりやめる")-1;
	if ('@num==9) goto L_CANCEL;
	mes "[タール]";
	mes "それじゃ、転送しますね。";
	close2;
	callfunc "AC_WarpTown",'@num;
	end;
L_CANCEL:
	mes "[タール]";
	mes "わかりました。";
	mes "また来てくださいね。";
	close;
OnInit:
	waitingroom "転送サービス",0;
}

// ----------------------------------------------
// ヘイム(ルーンの依頼の関連マップへの転送)
ac_cl_area.gat,57,168,4	script	ヘイム	798,{
	mes "[ヘイム]";
	mes "やぁ、こんにちは。";
	mes "僕はヘイムだよ。";
	next;
	set '@novice, callfunc("AC_GetNovice");
	if ('@novice)	goto L_NOVICE;
	else			goto L_EXPERT;
L_NOVICE:
	if(AC_QUEST_ST_0+AC_QUEST_ST_1+AC_QUEST_ST_2+AC_QUEST_ST_3+AC_QUEST_ST_4==0){
		mes "[ヘイム]";
		mes "ルーンに何か言われたら";
		mes "またおいで。";
		mes "少しくらいなら";
		mes "僕が手伝ってあげるからさ。";
		close;
	}
	mes "[ヘイム]";
	mes "ルーンから聞いたよ。";
	mes "僕が転送してあげよう。";
	mes "どこに行きたいんだい？";
	mes "^0000FF‐ルーン依頼・試験の進行中のため、";
	mes "転送後に画面右上のミニマップ内に";
	mes "行き先を示す『＋』が表示されます‐^000000";
	next;
	//クエスト状態取得

	set '@warplist,0; //マップ表示順が本鯖どおりになるように入れる
	//プロンテラ
	if( (AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==0)||	//気になるあの子１
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==1)||	//気になるあの子２
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==2)||	//気になるあの子３
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==3)||	//気になるあの子４
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==5)||	//気になるあの子６
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==6)||	//気になるあの子７
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==7)||	//気になるあの子８
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==1)||	//ダンジョン救出１
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==5)||	//ダンジョン救出３
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==8)||	//実験のお手伝い５
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==0)||	//冒険者になりたい１
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==1)||	//冒険者になりたい２
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==3)||	//冒険者になりたい４
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==5)||	//冒険者になりたい６
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==8)||	//冒険者になりたい９
		(AC_RANK==1 && AC_RANKTEST && AC_RANKTEST<98)||				//第2課程試験
		(AC_RANK==3 && AC_RANKTEST && AC_RANKTEST<98)||				//第4課程試験
		(AC_RANK==4 && AC_RANKTEST && AC_RANKTEST<98)){				//第5課程試験
		set '@warplist[getarraysize('@warplist)],1;
	}
	//モロク
	if( (AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==2)||	//気になるあの子３
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==4)||	//気になるあの子５
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==2)||	//実験のお手伝い２
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==2)||	//冒険者になりたい３
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99 && AC_QUEST_LV_4==4)||	//冒険者になりたい５
		(AC_RANK==5 && AC_RANKTEST && AC_RANKTEST<98)){				//第6課程試験
		set '@warplist[getarraysize('@warplist)],3;
	}
	//ゲフェン
	if( (AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==0)||	//実験のお手伝い１
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==3)||	//気になるあの子４
		(AC_QUEST_ST_4 && AC_QUEST_ST_4<99)||						//冒険者になりたい(全エピソード)
		(AC_RANK==5 && AC_RANKTEST && AC_RANKTEST<98)){				//第6課程試験
		set '@warplist[getarraysize('@warplist)],5;
	}
	//フェイヨン
	if( (AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==4)||	//気になるあの子５
		(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==1)||	//奇跡の箱２
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==8)||	//お詫びの品を届けたい２
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==4)||	//実験のお手伝い３
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==6)||	//実験のお手伝い４
		(AC_RANK==2 && AC_RANKTEST && AC_RANKTEST<98)||			//第3課程試験
		(AC_RANK==5 && AC_RANKTEST && AC_RANKTEST<98)||			//第6課程試験
		(AC_RANK==6 && AC_RANKTEST && AC_RANKTEST<98)){			//第7課程試験
		set '@warplist[getarraysize('@warplist)],6;
	}
	//アルベルタ
	if( (AC_QUEST_ST_1 && AC_QUEST_ST_1<99) ||						//奇跡の箱(全エピソード)
		(AC_RANK==0 && AC_RANKTEST && AC_RANKTEST<98)){				//第1課程試験
		set '@warplist[getarraysize('@warplist)],4;
	}
	//イズルード
	if( (AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==1)||	//気になるあの子２
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==7)||	//気になるあの子８
		(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==8)||	//気になるあの子９
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==5)||	//お菓子の材料集め４
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==6)||	//お菓子の材料集め５
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==3)||	//ダンジョン救出２
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99 && AC_QUEST_LV_3==7)){	//ダンジョン救出４
		set '@warplist[getarraysize('@warplist)],2;
	}
	//アルデバラン
	if( (AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==0)||	//お世話になったあの人に
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==1)||	//お詫びの品を届けたい１
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==7)||	//お菓子お届け
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==8)){	//お詫びの品を届けたい２
		set '@warplist[getarraysize('@warplist)],7;
	}
	//ジュノー
	if( (AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==1)||	//お詫びの品を届けたい１
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==2)||	//お菓子の材料集め１
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==3)||	//お菓子の材料集め２
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==4)||	//お菓子の材料集め３
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==5)||	//お菓子の材料集め４
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==6)||	//お菓子の材料集め５
		(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==7)){	//お菓子お届け
		set '@warplist[getarraysize('@warplist)],8;
	}
	//コモド
	if( (AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==5)||	//気になるあの子６
		(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==7)){	//奇跡の箱８
		set '@warplist[getarraysize('@warplist)],10;
	}
	//ラヘル
	if(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==8){		//気になるあの子９
		set '@warplist[getarraysize('@warplist)],12;
	}
	//ベインス
	if(AC_QUEST_ST_0 && AC_QUEST_ST_0<99 && AC_QUEST_LV_0==8){		//気になるあの子９
		set '@warplist[getarraysize('@warplist)],14;
	}
	//アインブロック
	if(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==3){		//お菓子の材料集め２
		set '@warplist[getarraysize('@warplist)],19;
	}
	//アインベフ
	if(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==4){		//お菓子の材料集め３
		set '@warplist[getarraysize('@warplist)],20;
	}
	//フィゲル
	if( (AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==8)||	//お詫びの品を届けたい２
		(AC_QUEST_ST_3 && AC_QUEST_ST_3<99)){						//実験のお手伝い(全エピソード)
		set '@warplist[getarraysize('@warplist)],11;
	}
	//リヒタルゼン
	if(AC_QUEST_ST_2 && AC_QUEST_ST_2<99 && AC_QUEST_LV_2==2){		//お菓子の材料集め１
		set '@warplist[getarraysize('@warplist)],13;
	}
	//アマツ
	if(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==2){		//奇跡の箱３
		set '@warplist[getarraysize('@warplist)],18;
	}
	//コンロン
	if(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==3){		//奇跡の箱４
		set '@warplist[getarraysize('@warplist)],15;
	}
	//龍之城
	if(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==4){		//奇跡の箱５
		set '@warplist[getarraysize('@warplist)],16;
	}
	//アユタヤ
	if(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==5){		//奇跡の箱６
		set '@warplist[getarraysize('@warplist)],17;
	}
	//ウンバラ
	if(AC_QUEST_ST_1 && AC_QUEST_ST_1<99 && AC_QUEST_LV_1==6){		//奇跡の箱７
		set '@warplist[getarraysize('@warplist)],9;
	}
	set '@mapselect$,"";
	for(set '@i,0; '@i<getarraysize('@warplist); set '@i,'@i+1){
		set '@mapselect$,'@mapselect$ + 'mapname$['@warplist['@i]-1] + ":";
	}
	set '@mapselect$,'@mapselect$ + "今は必要ない";
	set '@mapid, select('@mapselect$)-1;
	set '@num,'@warplist['@mapid]-1;
	if('mapname$['@num]=="") goto L_CANCEL;
	mes "[ヘイム]";
	mes "それじゃあ、転送するよ。";
	mes "　";
	mes "^0000FF‐ミニマップの拡大縮小は";
	mes "ミニマップ内右上の『＋－』を";
	mes "左クリックすることで行えます‐^000000";
	next;
	mes "[ヘイム]";
	mes "アカデミーに戻ってくるときは";
	mes "^0000FF『アカデミーの関係者』^000000が";
	mes "^FF0000街の中央付近^000000にいるから、";
	mes "迷ったら街の中央付近に";
	mes "行ってみてね。";
	close2;
	warp 'gatname$['@num],'map_xy['@num*2],'map_xy['@num*2+1];
	end;
L_EXPERT:
	mes "[ヘイム]";
	mes "きみくらい貫禄のある冒険者だと、";
	mes "僕の助けはいらないかも";
	mes "しれないな。";
	mes "僕はここで未熟な冒険者の";
	mes "手助けをしているんだ。";
	next;
	if(select("そうなのか","なんでここで手助けを？")==1) {
		mes "[ヘイム]";
		mes "学びたいことがあるなら、";
		mes "アカデミー内に図書室があるから、";
		mes "一度行ってみるといいよ。";
		close;
	}
	mes "[ヘイム]";
	mes "以前、ぼくは見知らぬ冒険者に";
	mes "助けられたことがあったんだ。";
	mes "そのときのことは今も鮮明に";
	mes "覚えているよ。";
	next;
	mes "[ヘイム]";
	mes "ぼくが今ここにいられるのも、";
	mes "あの人のおかげなんだ。";
	next;
	emotion 2;
	mes "[ヘイム]";
	mes "きみも駆け出しの";
	mes "冒険者だったころを";
	mes "思い出してごらんよ。";
	close;
L_CANCEL:
	mes "[ヘイム]";
	mes "そうかい？";
	mes "また必要になったら";
	mes "おいでよ！";
	close;
OnInit:
	setarray 'gatname$,"prontera.gat","izlude.gat","morocc.gat","alberta.gat","geffen.gat","payon.gat","aldebaran.gat","yuno.gat","umbala.gat","comodo.gat","hugel.gat","rachel.gat","lighthalzen.gat","veins.gat","gonryun.gat","louyang.gat","ayothaya.gat","amatsu.gat","einbroch.gat",  "einbech.gat";
	setarray 'mapname$,"プロンテラ",  "イズルード","モロク",    "アルベルタ", "ゲフェン", "フェイヨン","アルデバラン", "ジュノー","ウンバラ",  "コモド",    "フィゲル", "ラヘル",    "リヒタルゼン",   "ベインス", "コンロン",   "龍之城",     "アユタヤ",    "アマツ",    "アインブロック","アインベフ";
	setarray 'map_xy,   147,190,      121,115,     147,93,      103,129,      110,103,    155,197,     138,110,        150,174,   100,154,     209,143,     90,146,     129,138,     214,156,          200,123,    160,120,      217,114,      216,175,       117,151,     217,188,         168,131;
	waitingroom "お手伝い中",0;
	end;
}

//------------------------------------------------------------------------------
// 教室棟 2F

ac_cl_area.gat,63,81,0	script	3階WP	45,1,1,{
	mes "[3階]";
	mes "3階は一般学生の立ち入りを";
	mes "禁止しています。";
	close;
}

//資料室管理人
ac_cl_area.gat,41,38,4	script	資料室管理人	75,{
	mes "[資料室管理人]";
	mes "ここは資料室になります。";
	mes "いろんな資料をここに";
	mes "集めてるんですよ。";
	mes "今日はどのような用ですか？";
	next;
	if(select("ヨンお爺さんはいますか？","なんでもない")==2) {
		mes "[資料室管理人]";
		mes "そうですか。";
		mes "資料室が整ったら、";
		mes "また来てくださいね。";
	} else {
		mes "[資料室管理人]";
		mes "ヨンお爺さんは";
		mes "資料室の中にいると思いますよ。";
		mes "本が大好きなおじいさんですから。";
	}
	close;
}

//ヨンお爺さん
ac_cl_area.gat,39,23,4	script	ヨン#ac_cl_area	766,{
	set '@novice, callfunc("AC_GetNovice");
	if(AC_RANK>0) goto L_TENSOU;
	if (!'@novice) {
		mes "[ヨン]";
		mes "ふぉっふぉっふぉ。";
		mes "感心、感心。";
		mes "お主のような立派な冒険者が";
		mes "増えるといいのう。";
		next;
		mes "[ヨン]";
		mes "他の生徒達も皆、";
		mes "お主のようになれれば";
		mes "わしも安心して、";
		mes "引退できるんじゃがのう。";
		mes "ふぉっふぉっふぉ。";
		close;
	}
	mes "[ヨン]";
	mes "ふぉっふぉっふぉ。";
	mes "これは面白い本を";
	mes "見つけることができたわい。";
	mes "……ふーむ………";
	mes "この棚には何の資料を置こうかのう。";
	mes "……";
	next;
	mes "[ヨン]";
	mes "ん？";
	mes "お主も本に関心があるようじゃの。";
	mes "本が好きなのか？";
	next;
	if (select("好き","好きじゃない")==2) {
		mes "[ヨン]";
		mes "そうか。";
		mes "さみしいことじゃの～。";
		mes "本はいろんな世界を感じることが";
		mes "できる良いものじゃて。";
		mes "興味があることから、いろんな本を";
		mes "読んでみるといいぞ。";
		next;
		mes "[ヨン]";
		mes "アカデミーにも図書室があるでな。";
		mes "一度いってみてはどうじゃ。";
		mes "ここは散らかっていて、";
		mes "読める状態じゃないのでな。";
		mes "ふぉっふぉっふぉ。";
		close;
	}
	mes "[ヨン]";
	mes "ふぉっふぉっふぉ。";
	mes "関心関心。";
	mes "いろんな本を読むことは良いことじゃ。";
	mes "本はいろんな知識を授けてくれるしの。";
	mes " ";
	mes "‐ヨンじいさんはうれしいようだ‐";
	next;
	mes "[ヨン]";
	mes "折角じゃから、本で知った";
	mes "わしのお気に入りの場所を";
	mes "教えようかの。";
	mes " ";
	mes "いってみるか？";
	next;
	if(select("行く","行かない")==2) {
		mes "[ヨン]";
		mes "そうか。";
		mes "残念じゃの～。";
		mes "わしのお気に入りの場所なんじゃが。";
		mes "何時でも送る準備はしておるぞ。";
		close;
	}
	mes "[ヨン]";
	mes "それじゃ、送るぞい。";
	mes "のどかな場所じゃが、";
	mes "モンスターには";
	mes "気をつけるんじゃぞ～。";
	close2;
	warp "prt_fild07.gat",78,287;
	end;
L_TENSOU:
	mes "[ヨン]";
	mes strcharinfo(0) + "か。";
	mes "そろそろ来るころだと思っとったよ。";
	mes "順調に試験をこなしているようじゃの。";
	mes " ";
	mes "‐ヨンじいさんが地図を持ってきた‐";
	next;
	cutin "support_map001.bmp",3;
	//一次過程修了でもセリフ変わらず
	mes "[ヨン]";
	mes "お主に薦めようと思っとる場所は";
	mes "これだけある。";
	mes "ガルド殿の話を聞く限り、";
	mes "全部はむりじゃろ。";
	mes "お主ならこのくらいまでかの。";
	mes "どこに行きたいんじゃ？";
	next;
	set '@select$,"";
	for(set '@i,0; '@i<13; set '@i,'@i+1){
		set '@select$,'@select$ + (AC_RANK >= 'REQUIRE['@i] ? 'MAPNAME$['@i] : "^FF0000不可^000000") + ":";
	}
	set '@select$,'@select$ + "やっぱり行かない";
	set '@num,select('@select$);
	if(AC_RANK < 'REQUIRE['@num-1]){
		mes "[ヨン]";
		mes "残念じゃが";
		mes "今のお主には薦められんのじゃ。";
		mes "別の場所にしておくんじゃ。";
		close;
	}
	if('@num==10){
		mes "[ヨン]";
		mes "ううむ……ここはのう、";
		mes "前はソグラト砂漠 08という";
		mes "場所があったのじゃが……";
		mes "今はもう無くてのう、お主を";
		mes "ここに送ることは出来ぬのじゃ。";
		mes "別の場所にしておくんじゃ。";
		close;
	}
	if('@num==14){
		mes "[ヨン]";
		mes "そうか。";
		mes "行きたくなったら、";
		mes "いつでも言いなされ。";
		mes "まっとるでな。";
		close;
	}
	mes "[ヨン]";
	mes "転送先にアインがいるはずじゃから、";
	mes "戻る時はアインに言いなされ。";
	mes "モンスターには気をつけるんじゃぞ。";
	mes "それじゃ、送るぞい。";
	mes "ふぉっふぉっふぉ。";
	close2;
	switch('@num){
	case 1: warp "prt_sewb2.gat",70,100; end;
	case 2: warp "prt_fild07.gat",78,287; end;
	case 3: warp "pay_fild02.gat",135,172; end;
	case 4: warp "pay_dun00.gat",108,24; end;
	case 5: warp "pay_fild09.gat",218,289; end;
	case 6: warp "iz_dun00.gat",237,166; end;
	case 7: warp "gef_fild03.gat",32,55; end;
	case 8: warp "pay_dun01.gat",231,74; end;
	case 9: warp "gef_fild11.gat",369,294; end;
	case 11: warp "gef_fild12.gat",125,184; end;
	case 12: warp "mjolnir_05.gat",170,280; end;
	case 13: warp "gef_dun01.gat",247,231; end;
	}
	end;
OnInit:
	setarray 'MAPNAME$,"プロンテラ地下水路 B2F","プロンテラフィールド 07","フェイヨン迷いの森 02","フェイヨン地下洞窟 B1F","フェイヨン迷いの森 09","イズルード海底洞窟 1層","ゲフェンフィールド 03","フェイヨン地下洞窟 B2F","ゲフェンフィールド 11","^8C008C消滅^000000","ゲフェンフィールド 12","ミョルニール山脈 05","ゲフェン地下ダンジョン B2F";
	setarray 'REQUIRE,1,1,1,1,2,2,3,4,4,0,5,6,7;
}

//------------------------------------------------------------------------------
// アインの支援
// 補足：アンゼやマニピなどのPT支援系は、1人が行えばパーティ全員にかかる為、
//       処理が複雑になっています。

-	script	アインACFUNC	-1,{
	function	abs		{ return getarg(0)*(getarg(0)<0 ? -1 : 1); }
	set '@novice, callfunc("AC_GetNovice");
	if(AC_PASSPORT){
		if(!'@novice){
			mes "[アイン]";
			mes "もう、キミには私の力は";
			mes "必要ないだろう。";
			mes "キミは私の予想を遥かに超えて、";
			mes "立派に成長した。";
			mes "多くの人を助けてやってくれ。";
			close;
		}
		mes "[アイン]";
		mes "キミはアカデミーの生徒だな。";
		mes "あまり無茶はしないほうがいい。";
		mes "仲間と共に戦っていくことが、";
		mes "長生きのコツだ。";
		mes " ";
		mes "何か話したいことがあるのか？";
		next;
		menu "支援を受けたい",L_SHIEN,"冒険者アカデミーに戻りたい",L_WARP,"何をしているの？",L_WHAT,"なんでもない",L_CANCEL;
	} else {
		if(!'@novice){
			mes "[アイン]";
			mes "……";
			mes "旅の者か。";
			mes "私に何か用か？";
			next;
			if(select("何でもない","何をしているの？")==1){
				mes "[アイン]";
				mes "ここら辺にもモンスターが";
				mes "住み着いている。";
				mes "旅には気をつけることだ。";
				mes "良い旅を。";
				close;
			}
			mes "[アイン]";
			mes "私はここで冒険者アカデミーの";
			mes "生徒の面倒を見ている。";
			mes "駆け出しの冒険者の";
			mes "手伝いをしているんだ。";
			mes "キミも冒険者アカデミーに";
			mes "一度行ってみるといい。";
			close;
		}
		mes "[アイン]";
		mes "……";
		mes "キミは冒険者のようだな。";
		mes "私はこの場所で冒険者の手助けを";
		mes "行っている。";
		mes "一度冒険者アカデミーに";
		mes "行ってみるといい。";
		next;
		menu "冒険者アカデミー？",-;
		mes "[アイン]";
		mes "冒険者のための学校のようなものだ。";
		mes "入学の手続きはそちらで";
		mes "行うことができる。";
		mes "キミが望むなら、冒険者アカデミーへ";
		mes "送るが、どうする？";
		next;
		if(select("送ってもらう","断る")==2){
			mes "[アイン]";
			mes "そうか。";
			mes "冒険に困ったことがあったら、";
			mes "一度行って見るといい。";
			mes "街の中央辺りにもアカデミーの";
			mes "関係者がいるはずだから。";
			close;
		}
		mes "[アイン]";
		mes "わかった。";
		mes "それじゃ、転送するぞ。";
		close2;
		warp "ac_cl_room.gat",44,32;
		end;
	}
L_WARP:
	mes "[アイン]";
	mes "冒険者アカデミーに戻りたいのか？";
	next;
	if(select("はい","いいえ")==2){
		mes "[アイン]";
		mes "そうか。";
		mes "無理は禁物だぞ。";
		mes "危なくなったら、戻ってくるといい。";
		close;
	}
	mes "[アイン]";
	mes "いったん休憩だな。";
	mes "それじゃ、転送するぞ。";
	close2;
	warp "ac_cl_area.gat",67,155;
	end;
L_SHIEN:
	mes "[アイン]";
	mes "いくら推薦を受けたものであっても、";
	mes "無償というわけではない。";
	mes "Zenyは必要だぞ。";
	mes " ";
	mes "どの支援を受けたい？";
	next;
	switch(select(
				"^0000FF基本セット^000000 - 10Zeny",
				(AC_RANK>3 ? "^FF0000補助セットⅠ^000000" : "^777777？？？？？Ⅰ^000000") + " - 50Zeny",
				(AC_RANK>3 ? "^006600補助セットⅡ^000000" : "^777777？？？？？Ⅱ^000000") + " - 50Zeny",
				"セットの説明を聞く","やめる"))
	{
	case 1:
		if(Zeny<10) goto L_NOMONEY;
		mes "[アイン]";
		mes "よし。";
		mes "それじゃ、気をつけて戦うんだぞ。";
		close2;
		set Zeny,Zeny-10;
		npcskillsupport 34,0;
		sc_end 10;
		sc_start 10,'BLESS[AC_RANK],'BASIC_LV[AC_RANK];	//SC_BLESSING
		npcskillsupport 29,0;
		sc_end 12;
		sc_start 12,'BLESS[AC_RANK],'BASIC_LV[AC_RANK];	//SC_INCREASEAGI
		if(!getcharid(1)){
			npcskillsupport 33,0,"","";
			sc_end 9;
			sc_start 9,'ANGEL[AC_RANK],'BASIC_LV[AC_RANK];	//SC_ANGELUS
			if(AC_RANK>=7){
				npcskillsupport 74,0,"","";
				sc_end 20;
				sc_start 20,90000,5;	//SC_MAGNIFICAT
			}
		} else {
			set '@chid,getcharid(3);
			getpartymember getcharid(1);
			set '@dummy,getmapxy('@map$,'@x,'@y,0);
			for(set '@i,0; '@i<$@partymembercount; set '@i,'@i+1) {
				if(attachrid(getcharid(3,$@partymembername$['@i]))){
					set '@dummy, getmapxy('@pmmap$,'@pmx,'@pmy,0);
					if('@pmmap$ != '@map$) { detachrid; continue; }  //マップチェック
					if(abs('@x-'@pmx) > 14 || abs('@y-'@pmy)>14) { detachrid; continue; } //範囲チェック
					npcskillsupport 33,0,"","";
					sc_end 9;
					sc_start 9,'ANGEL[AC_RANK],'BASIC_LV[AC_RANK];	//SC_ANGELUS
					if(AC_RANK>=7){
						npcskillsupport 74,0,"","";
						sc_end 20;
						sc_start 20,90000,5;	//SC_MAGNIFICAT
					}
					detachrid;
				}
			}
			if(!attachrid('@chid)) end; //アタッチしなおす
		}
		npcskillsupport 73,0,"","";//キリエだけ上手く再現できないのはなんでだ・・・
		sc_end 110;
		sc_end 19;
		sc_start 19,120000,'BASIC_LV[AC_RANK];	//SC_KYRIE
		end;
	case 2:
		if(AC_RANK<4) goto L_FEWLANC;
		if(Zeny<50) goto L_NOMONEY;
		mes "[アイン]";
		mes "よし。";
		mes "それじゃ、気をつけて戦うんだぞ。";
		close2;
		set Zeny,Zeny-50;
		npcskillsupport 66,0;
		sc_end 15;
		sc_start 15,60000,'SUP1_LV[AC_RANK];	//SC_IMPOSITIO
		if(!getcharid(1)){
			npcskillsupport 383,0,"","";
			sc_end 116;
			sc_start 116,'WINDW[AC_RANK],'SUP2_LV[AC_RANK];	//SC_WINDWALK
		} else {
			set '@chid,getcharid(3);
			getpartymember getcharid(1);
			set '@dummy,getmapxy('@map$,'@x,'@y,0);
			for(set '@i,0; '@i<$@partymembercount; set '@i,'@i+1) {
				if(attachrid(getcharid(3,$@partymembername$['@i]))){
					set '@dummy, getmapxy('@pmmap$,'@pmx,'@pmy,0);
					if('@pmmap$ != '@map$) { detachrid; continue; }  //マップチェック
					if(abs('@x-'@pmx) > 14 || abs('@y-'@pmy)>14) { detachrid; continue; } //範囲チェック
					npcskillsupport 383,0,"","";
					sc_end 116;
					sc_start 116,'WINDW[AC_RANK],'SUP2_LV[AC_RANK];	//SC_WINDWALK
					detachrid;
				}
			}
		}
		end;
	case 3:
		if(AC_RANK<4) goto L_FEWLANC;
		if(Zeny<50) goto L_NOMONEY;
		mes "[アイン]";
		mes "よし。";
		mes "それじゃ、気をつけて戦うんだぞ。";
		close2;
		set Zeny,Zeny-50;
		if(!getcharid(1)){
			npcskillsupport 112,0,"","";
			sc_end 24;
			sc_start 24,'WEAPF[AC_RANK],'SUP1_LV[AC_RANK];	//SC_WEAPONPERFECTION
			npcskillsupport 113,0,"","";
			sc_end 25;
			sc_start 25,'OVERT[AC_RANK],'SUP1_LV[AC_RANK];	//SC_OVERTHRUST
		} else {
			set '@chid,getcharid(3);
			getpartymember getcharid(1);
			set '@dummy,getmapxy('@map$,'@x,'@y,0);
			for(set '@i,0; '@i<$@partymembercount; set '@i,'@i+1) {
				if(attachrid(getcharid(3,$@partymembername$['@i]))){
					set '@dummy, getmapxy('@pmmap$,'@pmx,'@pmy,0);
					if('@pmmap$ != '@map$) { detachrid; continue; }  //マップチェック
					if(abs('@x-'@pmx) > 14 || abs('@y-'@pmy)>14) { detachrid; continue; } //範囲チェック
					npcskillsupport 112,0,"","";
					sc_end 24;
					sc_start 24,'WEAPF[AC_RANK],'SUP1_LV[AC_RANK];	//SC_WEAPONPERFECTION
					npcskillsupport 113,0,"","";
					sc_end 25;
					sc_start 25,'OVERT[AC_RANK],'SUP1_LV[AC_RANK];	//SC_OVERTHRUST
					detachrid;
				}
			}
		}
		end;
	case 4:
		mes "[アイン]";
		if(AC_RANK<4){
			mes "今のキミには";
			mes "^0000FF基本セット^000000の支援ができる。";
		} else {
			mes "キミには3種類の支援ができる。";
			mes "まず^0000FF基本セット^000000だが、";
		}
		mes "ブレッシング、速度増加、";
		mes "エンジェラス、キリエエレイソンだ。";
		mes "キミが試験をこなすごとに";
		mes "支援スキルのレベルを上げるぞ。";
		next;
		mes "[アイン]";
		mes "最終的には基本セットで";
		mes "先ほどの4つのスキルを";
		mes "Lv10で提供するのに加え";
		mes "おまけでマグニフィカートLv5も";
		mes "つけてやろう。";
		if(AC_RANK<4){
			mes "説明は以上だ。";
			close;
		}
		next;
		mes "[アイン]";
		mes "そして^FF0000補助セットⅠ^000000では";
		mes "イムポシティオマヌスと";
		mes "ウィンドウォーク、";
		mes "^006600補助セットⅡ^000000では";
		mes "ウェポンパーフェクションと";
		mes "オーバートラストをかける。";
		next;
		mes "[アイン]";
		mes "同じくキミの成長に";
		mes "応じてレベルを高めよう。";
		mes "上手く利用して欲しい。";
		close;
	default:
		goto L_CANCEL;
	}
	close;
L_FEWLANC:
	mes "[アイン]";
	mes "残念だが";
	mes "今のキミにはこの支援を";
	mes "行うことは出来ない。";
	mes "もう少し試験をこなして";
	mes "修練を積むといい。";
	close;
L_NOMONEY:
	mes "[アイン]";
	mes "ん？";
	mes "お金が足りないぞ。";
	mes "そろそろ、冒険者アカデミーに";
	mes "戻ったほうがいいんじゃないか？";
	close;
L_WHAT:
	mes "[アイン]";
	mes "ミッドとルーンからキミの話を";
	mes "聞いている。";
	mes "キミが手を借りずに戦えるように";
	mes "なるまで、しばらくここで";
	mes "サポートしよう。";
	next;
	mes "[アイン]";
	mes "冒険者アカデミーで";
	mes "キミが成長を遂げれば";
	mes "遂げるほど、";
	mes "私も相応のサポートを行おう。";
	next;
	mes "[アイン]";
	mes "いつまでもというわけには";
	mes "いかないが、キミが立派に";
	mes "成長を遂げるまでは付き合おう。";
	close;
L_CANCEL:
	mes "[アイン]";
	mes "そうか。";
	mes "気をつけて行きなさい。";
	close;
OnInit:
	//スキルレベル
	setarray 'BASIC_LV,3,4,5,6,7,8,9,10;
	setarray 'SUP1_LV, 0,0,0,0,2,3,4,5;
	setarray 'SUP2_LV, 0,0,0,0,4,6,8,10; //ウインドウォーク用
	//スキル持続時間
	setarray 'BLESS,100000,120000,140000,160000,180000,200000,220000,240000;//IA共用
	setarray 'ANGEL,90000,120000,150000,180000,210000,240000,270000,300000;
	setarray 'WINDW,0,0,0,0,220000,280000,340000,400000;
	setarray 'WEAPF,0,0,0,0,20000,30000,40000,50000;
	setarray 'OVERT,0,0,0,0,40000,60000,80000,100000;
	//キリエ 120000 マニピ 90000 IMP 60000
}
prt_fild07.gat,78,290,4		duplicate(アインACFUNC)		アイン#PRTF07	747
prt_sewb2.gat,70,103,4		duplicate(アインACFUNC)		アイン#PRTSB2	747
pay_fild02.gat,135,175,4	duplicate(アインACFUNC)		アイン#PAYF02	747
pay_dun00.gat,108,26,4		duplicate(アインACFUNC)		アイン#PAYD00	747
pay_fild09.gat,218,292,4	duplicate(アインACFUNC)		アイン#PAYF09	747
iz_dun00.gat,237,169,4		duplicate(アインACFUNC)		アイン#IZLD00	747
gef_fild03.gat,32,58,4		duplicate(アインACFUNC)		アイン#GEFF03	747
pay_dun01.gat,231,77,4		duplicate(アインACFUNC)		アイン#PAYD01	747
gef_fild11.gat,369,297,4	duplicate(アインACFUNC)		アイン#GEFF11	747
gef_fild12.gat,125,187,4	duplicate(アインACFUNC)		アイン#GEFF12	747
mjolnir_05.gat,170,285,4	duplicate(アインACFUNC)		アイン#MJOL05	747
gef_dun01.gat,247,234,4		duplicate(アインACFUNC)		アイン#GEFD01	747

