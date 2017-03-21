//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  ルーンの依頼
//
//                                                 by Pneuma
//お世話になったあの人に   -----------------------------------
aldeba_in.gat,171,171,4	script	ミザリー#aldeba_in	68,{
	set '@novice, callfunc("AC_GetNovice");
	if(!AC_QUEST_ST_2)goto L_OTHER;
	switch(AC_QUEST_LV_2){
	case 0:
		goto L_QUEST01;
	case 1:
		goto L_QUEST02;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		goto L_QUEST08;
	case 8:
		goto L_QUEST09;
	}
L_QUEST01:
	switch(AC_QUEST_ST_2) {
	case 1:
		mes "[ミザリー]";
		mes "こんにちは～。";
		next;
		menu "こんにちは",-;
		emotion 5;
		mes "[ミザリー]";
		mes "あ、";
		mes "貴方が依頼を受けてくれる人なのね！";
		mes "助かるわー。";
		mes "えっと、これを";
		mes "^0000FFルティエ^000000にいる^FF0000トイーヒ^000000さんに";
		mes "届けてほしいのよ。";
		next;
		emotion 21,"";
		mes "[ミザリー]";
		mes "以前、^FF0000ルティエ^000000に行った時にね、";
		mes "モンスターにやられちゃって……";
		mes "それを助けてもらったんです。";
		mes "だから、お礼にこれを届けたいんです。";
		mes "でも、忙しくて届けることが";
		mes "できなかったの。";
		next;
		menu "しっかりと届けてきます",-;
		mes "^FF0000【ミッション】^000000";
		mes "^FF0000ルティエ^000000にいる^0000FFトイーヒ^000000さんに、";
		mes "お礼の品を届けたあと、";
		mes "ミザリーに報告する。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[ミザリー]";
		mes "あ、依頼の品を";
		mes "届けていただけましたか？";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "これから、行くところなんです。";
		next;
		emotion 21;
		mes "[ミザリー]";
		mes "そっかー、";
		mes "念のためもう一度届け先を";
		mes "教えておくね。";
		mes "^0000FFルティエ^000000にいる、^FF0000トイーヒ^000000さんに";
		mes "お礼の品を届けてね。";
		mes "よろしくね！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFルティエ^000000にいる^FF0000トイーヒ^000000さんに、";
		mes "お礼の品を届けたあと、";
		mes "ミザリーに報告する。";
		close;
	case 3:
		mes "[ミザリー]";
		mes "あ、依頼の品を";
		mes "届けていただけましたか？";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "ええ、とても喜んでいましたよ。";
		mes "それで、手紙を預かってきたんです。";
		next;
		emotion 21;
		mes "‐ミザリーに手紙を渡した‐";
		next;
		mes "[ミザリー]";
		mes "手紙をいただけるなんて、感激です。";
		mes strcharinfo(0)+"に";
		mes "請け負ってもらってよかったわ。";
		mes "また何かあったらよろしくね！";
		next;
		if('@novice){
			mes "[ミザリー]";
			mes "これ、大した物じゃないけど";
			mes "お礼にどうぞ！";
			next;
			// 602 蝶の羽 10個
			if(!checkweight(602,10)){
				mes "重量オーバー！";
				close;
			}
			getitem 602,10;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[ミザリー]";
		mes "ありがとうね。";
		mes "また何かあったらよろしく！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	}
L_QUEST02:
	switch(AC_QUEST_ST_2) {
	case 1:
		emotion 0;
		mes "[ミザリー]";
		mes "！";
		mes "もしかして、また";
		mes strcharinfo(0) + "さんが";
		mes "依頼を受けてくれるの!?";
		next;
		menu "はい",-;
		mes "[ミザリー]";
		mes "うわー、凄い助かるわー！";
		mes "一度お願いしてるし";
		mes "貴方なら信用できるわ。";
		next;
		emotion 5;
		mes "[ミザリー]";
		mes "早速依頼内容をお話するね。";
		mes "えっと、ジュノーに珍しいお菓子を作る";
		mes "職人さんがいるらしいの。";
		mes "その人に一つお菓子を";
		mes "作ってもらいたくて……";
		mes "代わりに頼んできてほしいのよ。";
		next;
		mes "[ミザリー]";
		mes "相変わらず忙しくって、";
		mes "私はここから動くことができないから";
		mes "お願いするわ。";
		mes "これ、注文書だからこれを渡して";
		mes "ちょうだい。";
		next;
		menu "まかせてください！",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000にいる、お菓子職人に";
		mes "お菓子作成の依頼を行い、";
		mes "ミザリーに報告する。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[ミザリー]";
		mes "あ、お菓子作成の依頼を";
		mes "していただけましたか？";
		next;
		menu "これから行くところです",-;
		emotion 11;
		mes "[ミザリー]";
		mes "そうだったのねー。";
		mes "念のためもう一度教えとくわね。";
		mes "^0000FFジュノー^000000にいる、お菓子職人に";
		mes "お菓子作成の依頼を行ってきてくれる？";
		next;
		mes "[ミザリー]";
		mes "依頼が終わったら";
		mes "私のところに戻ってきてね。";
		mes "それじゃよろしくー。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000にいる、お菓子職人に";
		mes "お菓子作成の依頼を行い、";
		mes "ミザリーに報告する。";
		close;
	case 3:
		mes "[ミザリー]";
		mes "あ、お菓子作成の依頼、";
		mes "どうですか？";
		next;
		menu "依頼できました！",-;
		emotion 33;
		mes "‐依頼したことと、";
		mes "　お菓子つくりに時間がかかること" /*「を」が抜けてるのは本鯖どおり*/;
		mes "　ミザリーに伝えた‐";
		next;
		mes "[ミザリー]";
		mes "ありがとうー、さすが";
		mes strcharinfo(0) + "ね！";
		mes "またお世話になっちゃった。";
		if('@novoce){
			mes "これ、お礼に受け取って！";
		}
		next;
		if('@novoce){
			if(!checkweight(2305,1)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 2305,1;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[ミザリー]";
		mes strcharinfo(0);
		mes "ありがとうね。";
		mes "また何かあったらよろしく！";
		close;
	}
L_QUEST08:
	switch(AC_QUEST_ST_2){
	case 1:
		goto L_OTHER;
	case 2:
		mes "[ミザリー]";
		mes "あ！";
		mes strcharinfo(0) + "さん";
		mes "こんにちはー。";
		next;
		menu "お菓子を持ってきました！",-;
		emotion 0;
		mes "[ミザリー]";
		mes "!?";
		mes "ついに完成したのね！";
		mes "ありがとうー。";
		next;
		menu "あと、お代を……",-;
		emotion 17;
		mes "[ミザリー]";
		mes "あ、お代だったわねー。";
		mes "すっかり忘れてたわ。";
		mes "ごめんなさいね！";
		mes "はい、これ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000にいる、^FF0000マッズイ^000000さんに";
		mes "お代を渡す。";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[ミザリー]";
		mes "うふふ、お菓子♪　お菓子♪";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000にいる、^FF0000マッズイ^000000さんに";
		mes "お代を渡す。";
		close;
	}
L_QUEST09:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[ミザリー]";
		mes "あ、やっぱり";
		mes strcharinfo(0) + "さん！";
		mes "きっと貴方が来てくると"/*来てくるで本鯖通り*/;
		mes "思ったわ！";
		next;
		menu "それでどんな依頼を？",-;
		mes "[ミザリー]";
		mes "えっとね、";
		mes "この前届けてもらったお菓子と手紙を、";
		mes "^FF0000ロックス^000000さんに届けてほしいの。";
		next;
		menu "何処にいるんですか？",-;
		mes "[ミザリー]";
		mes "あ、うん。";
		mes "えとね……";
		mes "実は彼、冒険者をしていてね";
		mes "世界中を旅しているから";
		mes "今何処にいるのかわからないのよね……";
		next;
		menu "何か少しでも情報はありませんか？",-;
		mes "[ミザリー]";
		mes "そうねぇ……";
		mes "仕事仲間の^FF0000ライアス^000000にも見つけたら";
		mes "教えてほしいと伝えてあるんだけど";
		mes "連絡こないし……";
		mes "うーん……";
		next;
		emotion 33;
		mes "[ミザリー]";
		mes "やみくもに探してもわからない";
		mes "だろうし、まずは^FF0000フェイヨン^000000にいる";
		mes "仕事仲間の^FF0000ライアス^000000に";
		mes "情報が無いか聞いてみてくれる？";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフェイヨン^000000にいる、";
		mes "仕事仲間の^FF0000ライアス^000000さんに";
		mes "情報が無いか確認する。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[ミザリー]";
		mes "あら、もう一度説明したほうが";
		mes "よいかしら？";
		next;
		mes "[ミザリー]";
		mes "やみくもに探してもわからない";
		mes "だろうし、まずは^FF0000フェイヨン^000000にいる";
		mes "仕事仲間の^FF0000ライアス^000000に";
		mes "情報が無いか聞いてみてくれる？";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフェイヨン^000000にいる、";
		mes "仕事仲間の^FF0000ライアス^000000さんに";
		mes "情報が無いか確認する。";
		close;
	case 3:
		//未調査
		mes "[ミザリー]";
		mes strcharinfo(0) + "さん！";
		mes "すぐに^FF0000フィゲル^000000へ";
		mes "行ってみてくれる？";
		mes "^FF0000ロックス^000000がいるらしいって";
		mes "ライアスから連絡が来たの！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフィゲル^000000へ行き";
		mes "^FF000000ロックス^000000さんを探す。";
		close;
	case 4:
		mes "[ミザリー]";
		mes strcharinfo(0) + "さん！";
		mes "^FF0000ロックス^000000は見つかりました？";
		next;
		menu "ええ",-;
		mes "[ミザリー]";
		mes "本当にありがとうございます！";
		mes "それで彼は元気でしたか？";
		next;
		menu "元気でした",-;
		mes "[ミザリー]";
		mes "良かったわ。";
		mes "手紙が後で来るのね。";
		mes "本当にありがとうー。";
		mes "色々お世話になっちゃった。";
		next;
		menu "冒険者だったことについて",-;
		mes "[ミザリー]";
		mes "あら、ロックスのやつ";
		mes "おしゃべりね……";
		mes "そうなのよ、";
		mes "私も冒険者だったの。";
		mes "でも商売のほうが楽しくなっちゃって。";
		next;
		mes "[ミザリー]";
		mes "以前は、";
		mes "彼とコンビを組んで色々な";
		mes "ダンジョンに行ったのよ？";
		mes "あの時は充実した毎日だったわ。";
		mes "でも、なんかさびしいのよね。";
		next;
		mes "[ミザリー]";
		mes "今度は商売で";
		mes "彼とコンビを組みたいんだけども……";
		mes "彼は冒険者を続けたいみたい。";
		next;
		emotion 23,"";
		emotion 29;
		mes "[ミザリー]";
		mes "貴方も気づいていると思うけど";
		mes "あのお菓子を食べたら";
		mes "冒険を続けられない体に";
		mes "なると思うから、";
		mes "結果的に私の目的は";
		mes "達成されると思うけどね。";
		next;
		mes "[ミザリー]";
		mes "あ、口が滑っちゃったわね……";
		mes "今の話は忘れて。";
		next;
		mes "[ミザリー]";
		if('@novice){
			mes "あと、これ私のお古だけど";
			mes "良かったら使って。";
		}
		mes "本当にありがとう。";
		next;
		if('@novoce){
			if(!checkweight(2340,1)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 2340,1;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[ミザリー]";
		mes strcharinfo(0) + "さん！";
		mes "ありがとう。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_CLEAR:
	switch(AC_QUEST_LV_2){
	case 1:
	case 2:
		mes "[ミザリー]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうね。";
		mes "また何かあったらよろしく！";
		close;
	//未調査
	case 3:
	case 4:
	case 5:
	case 6:
		mes "[ミザリー]";
		mes strcharinfo(0)+"さん";
		mes "お菓子のほうは順調にいってる？";
		close;
	//未調査
	case 7:
		mes "[ミザリー]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうね。";
		mes "また何かあったらよろしく！";
		close;
	//未調査
	case 8:
	case 9:
		mes "[ミザリー]";
		mes "あ、";
		mes strcharinfo(0)+"じゃない！";
		mes "色々お世話になっちゃったわね。";
		mes "本当にありがとう！";
		close;
	}
L_OTHER:
	mes "[ミザリー]";
	mes "こんにちは～。";
	close;
}
//-------------------------------------------------------
xmas_in.gat,173,171,4	script	トイーヒ#xmas_in	908,{
	if(AC_QUEST_LV_2==0) goto L_QUEST01;
	goto L_OTHER;
L_QUEST01:
	switch(AC_QUEST_ST_2) {
	case 2:
		mes "[トイーヒ]";
		mes "こんにちは。";
		next;
		menu "トイーヒさん？",-;
		mes "[トイーヒ]";
		mes "僕は確かにトイーヒだよ？";
		mes "何か用かな？";
		next;
		menu "経緯を説明する",-;
		emotion 33;
		mes "‐トイーヒに経緯を説明し、";
		mes "お礼の品を手渡した‐";
		next;
		emotion 19;
		mes "[トイーヒ]";
		mes "なんか、";
		mes "彼女には気を遣わせて";
		mes "しまったなー……";
		mes "でも、凄くうれしいよ。";
		next;
		emotion 5;
		mes "[トイーヒ]";
		mes "そうだ！";
		mes "ついでに一つ手紙を";
		mes "届けてくれないかな？";
		next;
		menu "いいですよ",-;
		emotion 0;
		mes "[トイーヒ]";
		mes "おお！";
		mes "ありがとう！";
		mes "それじゃ、";
		mes "手紙を書くからちょっと待ってね。";
		next;
		emotion 5;
		mes "[トイーヒ]";
		mes "……";
		mes "…………";
		mes "………………";
		next;
		mes "[トイーヒ]";
		mes "できたできた！";
		mes "それじゃ、これをよろしく頼むよー。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる、";
		mes "^FF0000ミザリー^000000に報告しよう！";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[トイーヒ]";
		mes "こんにちは。";
		mes strcharinfo(0)+"さん。";
		mes "手紙を届けてくれましたか？";
		next;
		menu "まだなんです。",-;
		mes "[トイーヒ]";
		mes "手紙、よろしく頼むよ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる、";
		mes "^FF0000ミザリー^000000に報告しよう！";
		close;
	}
L_OTHER:
	if(AC_QUEST_LV_2 || AC_QUEST_ST_2>3){
		mes "[トイーヒ]";
		mes "こんにちは。";
		mes strcharinfo(0)+"さん。";
		close;
	}
	else {
		mes "[トイーヒ]";
		mes "やあ、今日も寒いねー。";
		close;
	}
}
//------------------------------------------------------
payon.gat,165,99,4	script	ライアス	807,{
	if(AC_QUEST_LV_2!=8) goto L_OTHER;
	switch(AC_QUEST_ST_2) {
	case 2:
		mes "[ライアス]";
		mes "ん？";
		mes "冒険者か……";
		next;
		menu "ミザリーさんから言われてきました",-;
		mes "[ライアス]";
		mes "おお、ミザリーからか。";
		mes "んで、なんだろうか？";
		next;
		menu "事情を説明する",-;
		emotion 0;
		mes "[ライアス]";
		mes "！";
		mes "ああ、例の人の件か！";
		mes "ちょうどさっき情報がはいった";
		mes "所だったんだ。";
		mes "今、^FF0000フィゲル^000000にいるらしいぜ？";
		next;
		menu "本当ですか!?",-;
		mes "[ライアス]";
		mes "ああ、仕事仲間の情報だから";
		mes "間違いじゃないと思うぜ？";
		mes "一応この件について、";
		mes "ミザリーにも伝えておくよ。";
		next;
		menu "ありがとうございます",-;
		mes "["+strcharinfo(0)+"]";
		mes "早速、フィゲルに向かってみよう。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフィゲル^000000へ行き";
		mes "^FF0000ロックス^000000さんを探す。";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[ライアス]";
		mes "あ、君か。";
		mes "すぐに^FF0000フィゲル^000000へ";
		mes "向かったほうが良いぞ？";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフィゲル^000000へ行き";
		mes "^FF0000ロックス^000000さんを探す。";
		close;
	}
L_OTHER:
	mes "[ライアス]";
	mes "ん？";
	mes "冒険者か……";
	close;
}
hugel.gat,72,90,4	script	ロックス	884,{
	if(AC_QUEST_LV_2!=8 || AC_QUEST_ST_2<3 || AC_QUEST_ST_2>4) goto L_OTHER;
	switch(AC_QUEST_ST_2) {
	case 3:
		emotion 9;
		mes "[ロックス]";
		mes "……";
		next;
		menu "こんにちは",-;
		emotion 9;
		mes "[ロックス]";
		mes "……";
		next;
		menu "あの……ミザリーさんから頼まれて",-;
		emotion 0;
		mes "[ロックス]";
		mes "！";
		mes "ミザリー……";
		mes "懐かしい名前だな……";
		next;
		menu "手紙とお菓子を渡す",-;
		mes "‐ロックスは手紙を読んでいるようだ‐";
		next;
		emotion 4;
		mes "[ロックス]";
		mes "自分の誕生日なんて";
		mes "手紙を見るまですっかり忘れていた。";
		mes "それはそうと……";
		mes "冒険者なんて辞めろって";
		mes "よく言うよな……";
		next;
		mes "[ロックス]";
		mes "あいつも、つい最近まで";
		mes "冒険者だったんだぜ？";
		mes "ふー、勝手な奴だよ。";
		mes "まったく……";
		next;
		mes "[ロックス]";
		mes "そういえば君の名前を";
		mes "聞いていなかったな。";
		next;
		menu "名乗る",-;
		mes "[ロックス]";
		mes strcharinfo(0) + "か。";
		mes "色々迷惑をかけてしまったみたいで";
		mes "すまなかった。";
		mes "^FF0000ミザリー^000000には、後で手紙を送ると";
		mes "言っておいてくれ。";
		mes "ありがとう。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000に居る";
		mes "^FF0000ミザリー^000000に報告する。";
		close2;
		set AC_QUEST_ST_2,4;
		end;
	case 4:
	case 99:
		mes "[ロックス]";
		mes strcharinfo(0) + "か。";
		mes "ありがとうな。";
		close;
	}
L_OTHER:
	mes "[ロックス]";
	mes "……";
	close;
}
//------------------------------------------------------
yuno_in04.gat,39,126,4	script	マッズイ	886,{
	set '@novice, callfunc("AC_GetNovice");
	switch(AC_QUEST_LV_2){
	case 0:
		goto L_OTHER;
	case 1:
		goto L_QUEST02;
	case 2:
		goto L_QUEST03;
	case 3:
		goto L_QUEST04;
	case 4:
		goto L_QUEST05;
	case 5:
		goto L_QUEST06;
	case 6:
		goto L_QUEST07;
	case 7:
		goto L_QUEST08;
	case 8:
		goto L_OTHER;
	}
L_QUEST02:
	switch(AC_QUEST_ST_2){
	case 0:
	case 1:
	case 99:
		goto L_OTHER;
	case 2:
		mes "[マッズイ]";
		mes "ふんふんふふふん。";
		mes "おいしいお菓子を作る～";
		mes "おいしいおいしいおいしい。";
		mes "おいしいーーーーーーーーー！";
		next;
		menu "あの",-;
		mes "[マッズイ]";
		mes "おや、お客さんかな？";
		mes "いらっしゃい！";
		next;
		mes "‐ミザリーから預かった";
		mes "　注文書をマッズイに渡した‐";
		next;
		emotion 11;
		mes "[マッズイ]";
		mes "ふむふむ、誰かのお祝いに渡す";
		mes "食べ物を作ってほしいのか。";
		mes "しかも奇抜なお菓子とは、";
		mes "やりがいがありますね！";
		next;
		mes "[マッズイ]";
		mes "それにしても奇抜なお菓子というと";
		mes "特別な材料が必要になるから、";
		mes "まず材料集めですね！";
		mes "気合が入ってきましたよー。";
		next;
		mes "[マッズイ]";
		mes "おっと、失礼しました、";
		mes "ご注文は承りましたから";
		mes "依頼された方に";
		mes "作成に時間がかかることを";
		mes "お伝えください。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		menu "わかりました！",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる、";
		mes "^FF0000ミザリー^000000に報告しよう！";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[マッズイ]";
		mes "やあ、";
		mes strcharinfo(0) + "さん。";
		mes "^FF0000ミザリー^000000さんには伝えてくれたかな？";
		next;
		menu "まだなんです。",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる、";
		mes "^FF0000ミザリー^000000に報告しよう！";
		close;
	}
L_QUEST03:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes "ふんふんふふふん。";
		mes "おいしいお菓子を作る～";
		mes "おいしいおいしいおいしい。";
		mes "おいしいーーーーーーーーー！";
		next;
		menu "あの",-;
		mes "[マッズイ]";
		mes "おや、この前の方じゃないですか。";
		next;
		menu "依頼の件できたのですが",-;
		mes "[マッズイ]";
		mes "おお！";
		mes "貴方が請け負ってくれるとは、";
		mes "世の中狭いですねー。";
		mes "依頼内容なのですが、";
		mes "この前ミザリーさんから依頼された";
		mes "お菓子の材料集めなんですよ。";
		next;
		emotion 11;
		mes "[マッズイ]";
		mes "沢山の注文が入っていて、";
		mes "どうしても自分では、";
		mes "取りに行くことができなくてねー。";
		mes "本当は自分でとりに";
		mes "行きたかったんだけど……";
		mes "でも、君なら安心だ！";
		next;
		mes "[マッズイ]";
		mes "えと、^0000FFリヒタルゼン^000000に生えている木の葉";
		mes "これが必要なんだよね。";
		mes "これをお願いしたい。";
		mes "おっと、街のどの辺りかは、";
		mes "紙に記載しておくね。";
		mes "それじゃよろしくお願いします。";
		next;
		menu "まかせてください！",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFリヒタルゼン^000000に生えている木から";
		mes "葉っぱを取ってくる。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[マッズイ]";
		mes "お、早いですね。";
		mes "もうとってきてくれたんですか!?";
		next;
		menu "まだです",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFリヒタルゼン^000000に生えている木から";
		mes "葉っぱを取ってくる。";
		close;
	case 3:
		mes "[マッズイ]";
		mes "ふんふんふんー。";
		next;
		menu "マッズイさん？",-;
		mes "[マッズイ]";
		mes "おいしいお菓子を作る～";
		next;
		menu "葉っぱを取ってきましたよ!!!",-;
		emotion 23;
		mes "[マッズイ]";
		mes "!?!?!?!";
		mes "…………";
		next;
		mes "[マッズイ]";
		mes "あーびっくりした……";
		mes "まだ心臓がバクバクしてますよ。";
		next;
		mes "[マッズイ]";
		mes "っと、";
		mes "葉っぱを持って来てくれたんですね。";
		mes "ありがとうございます！";
		mes "確かに受け取りました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	}
L_QUEST04:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes "口に入れると、とろける";
		mes "うまさ～。";
		mes "ちょっと口がしびれるかも～。";
		mes "ふんふふん。";
		next;
		menu "こんにちは",-;
		mes "[マッズイ]";
		mes "おお！";
		mes strcharinfo(0) + "さん";
		mes "やはり" + strcharinfo(0) + "さんが";
		mes "来てくれましたか！";
		next;
		mes "[マッズイ]";
		mes "今回の依頼内容も";
		mes "材料集めなんですけども。";
		mes "いやー、この前の葉っぱだけではね";
		mes "完全なものは作れないことが";
		mes "わかりまして。";
		next;
		emotion 11;
		mes "[マッズイ]";
		mes "えと、次の材料は……";
		mes "^0000FFアインブロック^000000のドブの泥を";
		mes "とってきてほしいんだ！";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "え!?";
		mes "ドブの泥ですか……？";
		next;
		mes "[マッズイ]";
		mes "そうそう、ドブの泥ね。";
		mes "よろしくおねがいしますね！";
		mes "あ、これ入れ物です。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "まかせてください！";
		mes " ";
		mes "（でも、ドブの泥なんて何に";
		mes " 使うんだろう……）";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアインブロック^000000のドブにある";
		mes "泥を取ってくる。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[マッズイ]";
		mes "お、早いですね。";
		mes "もうとってきてくれたんですか!?";
		next;
		menu "まだです",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアインブロック^000000のドブにある";
		mes "泥を取ってくる。";
		close;
	case 3:
		mes "[マッズイ]";
		mes "食べる人によっては";
		mes "毒になるーかもしれないよ～";
		mes "うまうまうまうまい！";
		mes "おいしいよ～。";
		next;
		menu "ドブの泥を取ってきました。",-;
		mes "[マッズイ]";
		mes "お、ご苦労さま！";
		mes "これこれ、この色だよ。";
		next;
		menu "この泥は何に使うのですか？",-;
		mes "[マッズイ]";
		mes "ん？";
		mes "何って、お菓子の材料に";
		mes "きまってるじゃないですかー。";
		mes "使い方は秘密ですけどね。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "そ、そうですよね。";
		mes "失礼しました。";
		mes " ";
		mes "（このお菓子を食べた人はきっと";
		mes "　大変なことになるんだろうな……）";
		next;
		mes "[マッズイ]";
		mes "いやいや、";
		mes "今回もたすかりましたよ。";
		mes "また、何かあったらよろしく";
		mes "お願いしますね。";
		if('@novoce){
			mes "あと、これもっていって。";
			mes "お店では買えない品だから大切にね！";
		}
		next;
		if('@novoce){
			if(!checkweight(568,20)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 568,20;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";//ハイフンあり
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";//ハイフンなし
		close;
	}
L_QUEST05:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes "へいー！";
		mes "お菓子作りはたのしいなー。";
		mes "たのしいー。";
		next;
		menu "こんにちは",-;
		mes "[マッズイ]";
		mes strcharinfo(0) + "さん";
		mes "いつもありがとうございます！";
		mes "今回も材料集めなんです。";
		next;
		emotion 11;
		mes "[マッズイ]";
		mes "今回依頼したい材料は、";
		mes "^0000FFアインベフ^000000で取れる鉱石なんです。";
		mes "それをとってきていただきたいんです。";
		next;
		emotion 4,"";
		mes "[" + strcharinfo(0) + "]";
		mes "鉱石……";
		mes "（また変な材料だ……）";
		next;
		mes "[マッズイ]";
		mes "^0000FFアインベフ^000000に私の知り合いの";
		mes "^FF0000ドルドイ^000000という人がいるので、";
		mes "その人から鉱石を一つ";
		mes "もらってきてください。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "（オーブンに使ったり";
		mes "　するんだろうか……）";
		next;
		menu "わ、わかりました",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアインベフ^000000にいる";
		mes "^FF0000ドルドイ^000000から鉱石をもらってくる。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[マッズイ]";
		mes "お、早いですね。";
		mes "もうとってきてくれたんですか!?";
		next;
		menu "まだです",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアインベフ^000000にいる";
		mes "^FF0000ドルドイ^000000から鉱石をもらってくる。";
		close;
	case 3:
		mes "[マッズイ]";
		mes "ズンチャッチャー";
		mes "ズンズンチャッチャー";
		mes "生クリームを～泥と混ぜて～。";
		next;
		menu "鉱石をもってきました",-;
		mes "[マッズイ]";
		mes "さすが、";
		mes strcharinfo(0) + "さん";
		mes "仕事が本当に速いですね。";
		next;
		mes "[マッズイ]";
		mes "うーん、良い鉱石だよ。";
		mes "これでより一層おいしいお菓子が";
		mes "作れるはずです。";
		mes "ありがとう！また何かあったら";
		mes "よろしくお願いします！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	}
L_QUEST06:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes "お・か・し！";
		mes "お菓子ーーーー!!!";
		next;
		menu "あ、あの……",-;
		mes "[マッズイ]";
		mes "！";
		mes "おお、まってましたよー！";
		mes "今回はバイラン島まで";
		mes "海草をもらいに行ってほしいんだ。";
		next;
		emotion 11;
		mes "[マッズイ]";
		mes "バイラン島に";
		mes "ンライバって人がいるので";
		mes "その人から海草を";
		mes "分けてきてもらってほしい。";
		next;
		emotion 4,"";
		mes "[" + strcharinfo(0) + "]";
		mes "海草ですね。";
		mes "わかりました！";
		mes "（今度は少しまともな材料だ）";
		next;
		mes "[マッズイ]";
		mes "それじゃよろしく頼むよ！";
		next;
		menu "わ、わかりました",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFバイラン島^000000にいる";
		mes "^FF0000ンライバ^000000さんから海草をもらってくる。";
		mes " ";
		mes "‐バイラン島には^0000FFイズルード^000000";
		mes "から行ける‐";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
	case 3:
	//ンライバのクエ終わらせずに戻った時のセリフは未調査。
	case 4:
		mes "[マッズイ]";
		mes "お、早いですね。";
		mes "もうとってきてくれたんですか!?";
		next;
		menu "まだです",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFバイラン島^000000にいる";
		mes "^FF0000ンライバ^000000さんから海草をもらってくる。";
		mes " ";
		mes "‐バイラン島には^0000FFイズルード^000000";
		mes "から行ける‐";
		close;
	case 5:
		mes "[マッズイ]";
		mes "泥混ぜ生クリームと";
		mes "鉱石の相性は抜群だ～！";
		mes "まっぜまぜっ！";
		mes "おかし作りはたのしいな～";
		mes "ヘイ！";
		mes "そして海草を～～。";
		next;
		menu "海草をもってきましたよ",-;
		mes "[マッズイ]";
		mes "おお！";
		mes "海草！";
		mes "それを今丁度使いたいところ";
		mes "だったんですよー。";
		mes "まさにグッドタイミングですねー。";
		next;
		mes "[マッズイ]";
		mes "いい感じすよ。";
		mes "究極のお菓子が完成に";
		mes "近づいています！";
		mes strcharinfo(0) + "さん！";
		mes "今回もありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	}
L_QUEST07:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes "イヤッハー！";
		mes "お菓子を混ぜ混ぜ混ぜ";
		mes "海草とー。";
		next;
		menu "こんにちは！",-;
		mes "[マッズイ]";
		mes "おっと、";
		mes "今回も依頼を";
		mes "引き受けてくださるんですよね？";
		next;
		menu "そうなんですよ",-;
		emotion 11;
		mes "[マッズイ]";
		mes "今回は水です水！";
		mes "でも、ただの水じゃないんですよ。";
		mes "海洋深層水これがほしいんです。";
		mes "^0000FF沈没船付近の島^000000に^0000FFアイリン^000000という";
		mes "女の子がいますから";
		mes "その子からもらってきてください。";
		next;
		mes "[マッズイ]";
		mes "それじゃよろしく頼むよ！";
		next;
		menu "まかせてください！",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF沈没船付近の島^000000にいる";
		mes "^FF0000アイリン^000000さんから";
		mes "海洋深層水をもらってくる。";
		mes " ";
		mes "‐沈没船付近の島には、";
		mes "^0000FFアルベルタ^000000から行ける‐";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
	case 3:
		mes "[マッズイ]";
		mes "お、早いですね。";
		mes "もうとってきてくれたんですか!?";
		next;
		menu "まだです",-;
		mes "[マッズイ]";
		mes "そうでしたか。";
		mes "それじゃ、よろしくお願いしますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF沈没船付近の島^000000にいる";
		mes "^FF0000アイリン^000000さんから";
		mes "海洋深層水をもらってくる。";
		mes " ";
		mes "‐沈没船付近の島には、";
		mes "^0000FFアルベルタ^000000から行ける‐";
		close;
	case 4:
		mes "[マッズイ]";
		mes "海洋深層水";
		mes "持って来てくれたみたいですね！";
		mes "いやー本当にたすかります。";
		next;
		mes "[マッズイ]";
		mes "早速、これを作って";
		mes "お菓子作りを続けますね。";
		if('@novoce){
			mes "あ、これ余り物ですがどうぞ";
		}
		next;
		if('@novoce){
			if(!checkweight(579,50)){
				mes "‐重量オーバー！‐";
				close;
			}
			getitem 579,50;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_QUEST08:
	switch(AC_QUEST_ST_2){
	case 1:
		mes "[マッズイ]";
		mes strcharinfo(0) + "さん";
		mes "世紀の一瞬ですよ！";
		mes "まさにいま究極のお菓子が";
		mes "完成しようとしています！";
		next;
		set '@dummy,("おお！");
		misceffect 12;
		mes "[マッズイ]";
		mes "さあ、最後の仕上げです！";
		next;
		emotion 28;
		mes "[マッズイ]";
		mes "完成です！";
		mes "すばらしいお菓子が完成しました。";
		mes "さあ、これを^FF0000ミザリー^000000さんに";
		mes "届けてください！";
		mes "後、お代も忘れずに受け取ってきて";
		mes "くださいね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる";
		mes "^FF0000ミザリー^000000さんにお菓子を届ける。";
		close2;
		set AC_QUEST_ST_2,2;
		end;
	case 2:
		mes "[マッズイ]";
		mes strcharinfo(0) + "さん";
		mes "早く届けてください！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFアルデバラン^000000にいる";
		mes "^FF0000ミザリー^000000さんにお菓子を届ける。";
		close;
	case 3:
		mes "[マッズイ]";
		mes strcharinfo(0) + "さん";
		mes "お帰りなさい。";
		next;
		menu "お代を渡す",-;
		mes "[マッズイ]";
		mes "ありがとうございます。";
		mes strcharinfo(0) + "さん";
		mes "には色々とお世話になって";
		mes "しまいました。";
		mes "本当にありがとうございました！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_2,99;
		end;
	case 99:
		mes "[マッズイ]";
		mes "また、";
		mes "依頼する事があるかもしれないけど";
		mes "そのときはよろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close;
	}
L_OTHER:
	mes "[マッズイ]";
	mes "ふんふんふふふん。";
	mes "おいしいお菓子を作る～";
	mes "おいしいおいしいおいしい。";
	mes "おいしいーーーーーーーーー！";
	close;
}
//---------------------------------------------------------------
lighthalzen.gat,51,161,0	script		木#AC_QUE02	111,{
	mes "‐木に沢山の葉っぱが生えている‐";
	if(AC_QUEST_LV_2==2 && (AC_QUEST_ST_2==2 || AC_QUEST_ST_2==3)) next;
	else close;
	switch(AC_QUEST_ST_2){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "この葉っぱで良いのかな？";
		mes "とりあえず一枚とっていこう。";
		next;
		mes "‐木から一枚葉をとった‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "葉っぱを届ける。";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "葉っぱは入手してるし、";
		mes "早く^FF0000マッズイ^000000さんに届けよう。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "葉っぱを届ける。";
		close;
	}
}
einbroch.gat,111,261,0	script	ドブの泥#AC_QUE02	111,{
	mes "‐ドブの中にぎっしりと";
	mes "泥が詰まっている‐";
	if(AC_QUEST_LV_2==3 && (AC_QUEST_ST_2==2 || AC_QUEST_ST_2==3)) next;
	else close;
	switch(AC_QUEST_ST_2){
	case 2:
		mes "[" + strcharinfo(0) + "]";
		mes "これ、本当にお菓子の材料に";
		mes "なるんだろうか……";
		mes "それにしても凄い臭いだ……";
		next;
		mes "‐ドブの泥を容器に詰めた‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "泥を届ける。";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "泥は手に入れたし、";
		mes "早く^FF0000マッズイ^000000さんに届けよう、";
		next;
		//読点で本鯖通り
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "葉っぱを届ける。";
		close;
	}
}
einbech.gat,130,247,3	script	ドルドイ#AC_QUE02	848,{
	mes "[ドルドイ]";
	mes "悪いが仕事中なので、";
	mes "話しかけないでもらえるかい？";
	if(AC_QUEST_LV_2==4 && (AC_QUEST_ST_2==2 || AC_QUEST_ST_2==3)) next;
	else close;
	switch(AC_QUEST_ST_2){
	case 2:
		menu "マッズイさんからの依頼で……",-;
		mes "[ドルドイ]";
		mes "ああ、あいつの知り合いかー。";
		mes "それで、あいつは何だって？";
		next;
		menu "経緯を説明する",-;
		mes "[ドルドイ]";
		mes "なるほどな、鉱石が必要と……";
		mes "ホラよ、";
		mes "一つぐらいならやるさ。";
		next;
		mes "[ドルドイ]";
		mes "そういえば、前から気になってたんだけど";
		mes "あいつは、鉱石をお菓子作りの";
		mes "何につかっているんだろうか？";
		mes "あんたは知ってるかい？";
		mes "聞いてもおしえてくれなくってよ！";
		next;
		menu "いや……",-;
		mes "[ドルドイ]";
		mes "ふむー、やはりか……";
		mes "聞いても教えてくれないんだよな。";
		mes "まあ、いいや。";
		mes "それじゃ、俺は仕事に戻るわ。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "鉱石を届ける。";
		close2;
		set AC_QUEST_ST_2,3;
		end;
	case 3:
		mes "[ドルドイ]";
		mes "ん、あんたまだいたのか。";
		mes "早く届けなくていいのか？";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "鉱石を届ける。";
		close;
	}
}
izlu2dun.gat,136,50,4	script	ンライバ#AC_QUE02	88,{
	if(AC_QUEST_LV_2!=5 || AC_QUEST_ST_2<2 || AC_QUEST_ST_2>5) goto L_OTHER;
	switch(AC_QUEST_ST_2){
	case 2:
		mes "[ンライバ]";
		mes "うーん、困った困った。";
		next;
		menu "海草ください！",-;
		mes "[ンライバ]";
		mes "ん？";
		mes "すまないが";
		mes "それどころじゃないんだ……";
		mes "財布を落としてしまってね。";
		next;
		menu "経緯を説明する",-;
		mes "[ンライバ]";
		mes "そういうことなのか……";
		mes "よし！";
		mes "じゃあ、俺が海草を取っている間に";
		mes "君は僕の財布を捜してくれないか？";
		mes "財布が見つかる頃には";
		mes "海草が取れていると思うよ。";
		next;
		menu "わかりました！",-;
		mes "[ンライバ]";
		mes "サンキュー！";
		mes "えっと、多分北の方で落とした";
		mes "と思うんだよね……";
		mes "よろしく頼んだよ。";
		close2;
		set AC_QUEST_ST_2,3;
		viewpoint 1,58,165,32,0xFF9900;
		//ID別だったので適当に
		end;
	case 3:
		mes "[ンライバ]";
		mes "財布頼むぜ！";
		mes "俺は海草とってるからさ。";
		close2;
		viewpoint 1,58,165,32,0xFF9900;
		end;
	case 4:
		mes "[ンライバ]";
		mes "おお、それは！";
		mes "俺の財布じゃないか！";
		mes "見つけてくれたんだなー！";
		mes "サンキュー！";
		next;
		mes "[ンライバ]";
		mes "おっと、これが約束の";
		mes "海草だ！";
		mes "取れたばかりだから新鮮だぜ！";
		mes "すぐに届けてくれ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "海草を届ける。";
		close2;
		set AC_QUEST_ST_2,5;
		end;
	case 5:
		mes "[ンライバ]";
		mes "財布を見つけてくれて";
		mes "ありがとうな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "海草を届ける。";
		close;
	}
L_OTHER:
	mes "[" + strcharinfo(0) + "]";
	mes "忙しそうだ。";
	mes "話しかけるのは止めよう。";
	close;
}
izlu2dun.gat,58,165,0	script	落し物#AC_QUE02	111,{
	mes "‐財布らしきものが落ちている‐";
	if(AC_QUEST_LV_2==5 && (AC_QUEST_ST_2==3 || AC_QUEST_ST_2==4)) next;
	else close;
	switch(AC_QUEST_ST_2){
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "^FF0000ンライバ^000000さんが探していたのは";
		mes "これかな？";
		mes "とりあえず届けてみよう。";
		next;
	case 4:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF南東^000000にいる";
		mes "^FF0000ンライバ^000000さんに財布を届ける。";
		close2;
		set AC_QUEST_ST_2,4;
		viewpoint 1,136,50,12,0xFF9900;
		end;
	}
}
alb2trea.gat,105,95,4	script	アイリン#AC_QUE02	96,{
	if(AC_QUEST_LV_2!=6 || AC_QUEST_ST_2<2 || AC_QUEST_ST_2>4) goto L_OTHER;
	switch(AC_QUEST_ST_2){
	case 2:
		mes "[アイリン]";
		mes "こんにちはー。";
		mes "何かご用かしら？";
		next;
		menu "事情を説明する",-;
		mes "[アイリン]";
		mes "^FF0000マッズイ^000000さんからの依頼なんですね。";
		mes "差し上げても良いですよ。";
		mes "でも、一つ条件があるわ！";
		next;
		menu "条件とは？",-;
		mes "[アイリン]";
		mes "喉がからからなのよね。";
		mes "だから、^0000FFこの島にいる道具商人^000000から";
		mes "^FF0000赤ポーション^000000を1つ買って";
		mes "持って来てほしいの。";
		next;
		menu "わかりました！",-;
		mes "[アイリン]";
		mes "物分りがいいわね！";
		mes "私はここで待っているから";
		mes "なるべく早くねー、";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "道具商人から^FF0000赤ポーション^000000を";
		mes "1つ買ってきてアイリンに渡す。";
		close2;
		set AC_QUEST_ST_2,3;
		viewpoint 1,87,65,32,0xFF9900;
		end;
	case 3:
		if(countitem(501)==0){//未調査
			mes "[アイリン]";
			mes "喉がからからなのよね。";
			mes "私はここで待っているから";
			mes "なるべく早くねー、";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "道具商人から^FF0000赤ポーション^000000を";
			mes "1つ買ってきてアイリンに渡す。";
			close2;
			viewpoint 1,87,65,32,0xFF9900;
			end;
		}
		set AC_QUEST_ST_2,4;
		delitem 501,1;
		mes "[アイリン]";
		mes "ありがとう。";
		mes "持って来てくれたみたいね！";
		mes "早速いただくわ！";
		next;
		mes "‐ゴクッゴクッ";
		mes "　アイリンが赤ポーションを";
		mes "　飲み干した‐";
		next;
		mes "これ、約束の品ね！";
		mes "貴重なんだから、気をつけて";
		mes "持って帰ってよね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "海洋深層水を届ける。";
		close;
	case 4:
		mes "[アイリン]";
		mes "早く届けてあげてね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFジュノー^000000の^FF0000マッズイ^000000さんに";
		mes "海洋深層水を届ける。";
		close;
	}
L_OTHER:
	mes "[アイリン]";
	mes "……";
	close;
}
