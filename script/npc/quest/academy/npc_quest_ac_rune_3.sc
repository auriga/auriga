//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  ルーンの依頼
//
//                                                 by Pneuma
//実験のお手伝い / ダンジョン救出  ---------------------------
//
//	AC_QUEST_LV_3
//	0 実験のお手伝い１
//	1 ダンジョン救出１
//	2 実験のお手伝い２
//	3 ダンジョン救出２
//	4 実験のお手伝い３
//	5 ダンジョン救出３
//	6 実験のお手伝い４
//	7 ダンジョン救出４
//	8 実験のお手伝い５

hu_in01.gat,309,27,4	script	タラシー博士	923,{
	set '@novice, callfunc("AC_GetNovice");
	if(!AC_QUEST_ST_3)goto L_OTHER;
	switch(AC_QUEST_LV_3){
	case 0:
		goto L_QUEST01;
	case 2:
		goto L_QUEST03;
	case 4:
		goto L_QUEST05;
	case 6:
		goto L_QUEST07;
	case 8:
		goto L_QUEST09;
	case 9:
		goto L_CLEAR;
	default:
		goto L_OTHER;
	}
L_QUEST01:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[タラシー博士]";
		mes "今度はうまくいきそうじゃ。";
		mes "これをまぜて……";
		next;
		menu "こんにちは",-;
		mes "[タラシー博士]";
		mes "研究が急がしいので後に";
		mes "してくれいー。";
		next;
		menu "依頼を受けてきたのですが。",-;
		emotion 0;
		mes "[タラシー博士]";
		mes "なんじゃと！";
		mes "おぬしが引き受けてくれるというのか！";
		mes "いやー、感心な若者じゃな！";
		next;
		mes "[タラシー博士]";
		mes "おぬしには研究に利用する材料を";
		mes "集めてきてもらいたい！";
		mes "詳しくは、超美人な助手のライラから";
		mes "聞くのじゃ！";
		next;
		menu "わかりました",-;
		mes "[タラシー博士]";
		mes "おぬし！";
		mes "ちょっと待つのじゃ！";
		next;
		if(Sex){
			menu "どうしましたか？",-;
			emotion 36;
			mes "[タラシー博士]";
			mes "いくら、助手のライラが";
			mes "美人だからって";
			mes "ハレンチなことをしたら";
			mes "ゆるさんぞい！";
			mes "わかったな？";
			next;
		}
		else {
			menu "どうかしましたか？",-;
			mes "[タラシー博士]";
			mes "おぬしも中々の美人だが";
			mes "ライラには敵わんな。";
			next;
		}
		menu "は、はぁ……",-;
		mes "[タラシー博士]";
		mes "それじゃ";
		mes "よろしく頼んだぞい！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[タラシー博士]";
		mes "ワシは急いでおるからな？";
		mes "早く助手のライラから";
		mes "詳細を聞くのじゃ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close;
	case 3:
		mes "[タラシー博士]";
		mes "若者よ！";
		mes "よろしく頼んだぞ！";
		close;
	case 4:
		emotion 0;
		mes "[タラシー博士]";
		mes "おお！";
		mes "それはまさしく、^FF0000ポムポム草^000000!!";
		mes "さあ、早くこちらへ。";
		next;
		menu "ポムポム草を渡す",-;
		mes "[タラシー博士]";
		mes "早速、実験じゃ！";
		mes "これで上手くいくと良いのじゃが……";
		next;
		misceffect 32,"#AC_BOM";
		mes "‐博士が液体に^0000FFポムポム草^000000を";
		mes "　入れた瞬間、";
		mes "　液体が泡立ち始めた";
		mes "　ボコボコボコ‐";
		next;
		misceffect 106,"#AC_BOM";
		percentheal -90,0;
		mes "[タラシー博士]";
		mes "い、イカン！";
		mes "爆発するぞーーー!!";
		next;
		mes "[タラシー博士]";
		mes "……";
		mes "君、生きておるか……？";
		next;
		menu "な、何とか……",-;
		mes "[タラシー博士]";
		mes "ふー……";
		mes "やってしまったわい……";
		mes "^FF0000ポムポム草^000000の成分なら";
		mes "いけると思ったんじゃがな。";
		mes "失敗じゃわい。";
		next;
		mes "[タラシー博士]";
		mes "とりあえず、依頼内容はこれで";
		mes "終わりじゃ……";
		if('@novice){
			mes "そういえば、おぬしは冒険者じゃったな";
			mes "これをやろう。";
			mes "昔ワシが使っていたやつなんだが";
			mes "役に立つかもしれん。";
			next;
			// 2220 ハット 1個
			if(!checkweight(2220,1)){
				mes "重量オーバー！";
				close;
			}
			getitem 2220,1;
		}
		else next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[タラシー博士]";
		mes "とりあえず、依頼内容はこれで";
		mes "終わりじゃ……";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	}
L_QUEST03:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[タラシー博士]";
		mes "こうするとこうなって……";
		mes "いやはや、難しい……";
		next;
		menu "こんにちは",-;
		mes "[タラシー博士]";
		mes "おお！";
		mes "おぬしは、この前手伝ってくれた！";
		mes "……";
		mes "なんじゃったけ？";
		next;
		menu "名乗る",-;
		emotion 0;
		mes "[タラシー博士]";
		mes "！";
		mes "そうじゃった";
		mes "そうじゃった！";
		mes "今回もおぬしが研究を";
		mes "手伝ってくれるということじゃな？";
		next;
		menu "ええ",-;
		mes "[タラシー博士]";
		mes "すばらしい！";
		mes "最近の若者にしては珍しい！";
		mes "早速依頼内容なんじゃが";
		mes "例によって^FF0000ライラ^000000から";
		mes "聞いてくれたまえ！";
		next;
		menu "わかりました",-;
		mes "[タラシー博士]";
		mes "それじゃ";
		mes "よろしく頼んだぞい！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "助手ライラさんに依頼の";
		mes "詳細内容を聞く。";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[タラシー博士]";
		mes strcharinfo(0)+"！";
		mes "すまないがワシは急いでおるのじゃ。";
		mes "ライラに内容をきいてくれい。";
		next;
		mes "^FF0000【ミッション】";
		mes "助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close;
	case 3:
		mes "‐研究に集中しているのか";
		mes "　こちらに気づかないようだ‐";
		close;
	case 4:
		mes "[タラシー博士]";
		mes strcharinfo(0);
		mes "じゃないか。";
		mes "ライラは本当に美人じゃ。";
		mes "おぬしもそうおもうじゃろ？";
		next;
		menu "そうですね",-;
		emotion 33;
		mes "[タラシー博士]";
		mes "そうじゃろ、そうじゃろ？";
		mes "私の自慢の助手なんじゃよ！";
		mes "それにしても、おぬしに何か";
		mes "頼んだ気がしたんじゃが……";
		mes "なんじゃったかな？";
		next;
		menu "ライライ草を……",-;
		mes "[タラシー博士]";
		mes "おお！";
		mes "そうじゃった!!!";
		mes "この液体に^FF0000ライライ草^000000を入れるのじゃ！";
		mes "さあ、おぬしが入れてよいぞ！";
		next;
		menu "え!? 私がですか……",-;
		misceffect 99,"#AC_BOM";
		sc_start3 SC_Blind,1,0,0,0,15000,0x8;
		mes "‐ライライ草を液体に投げ入れると";
		mes "　液体から凄まじい光が発せされた‐";
		next;
		mes "[タラシー博士]";
		mes "……";
		mes "…………";
		mes "まあ、こんなこともある！";
		mes "やはりポムポム草のほうが";
		mes "よかったのかの……";
		next;
		mes "[タラシー博士]";
		mes "仕方ない、";
		mes "また他の材料を探すとしよう。";
		mes "何かあったらまた頼むわい。";
		if('@novice){
			mes "あと、これをうけとれい。";
			next;
			// 1247 キンドリングダガー 1個
			if(!checkweight(1247,1)){
				mes "重量オーバー！";
				close;
			}
			getitem 1247,1;
		}
		else next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[タラシー博士]";
		mes "仕方ない、";
		mes "また他の材料を探すとしよう。";
		mes "何かあったらまた頼むわい。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST05:
	switch(AC_QUEST_ST_3) {
	case 1:
		emotion 7;
		mes "[タラシー博士]";
		mes "ライラへのプレゼントは";
		mes "どうしたらよいのじゃろうか。";
		mes "女心は本当にわからんからのぉ……";
		next;
		menu "なにがあったんですか？",-;
		emotion 0;
		mes "[タラシー博士]";
		mes "おお！";
		mes strcharinfo(0);
		mes "じゃないか！";
		mes "おぬしは気にしなくても良いのじゃ。";
		mes "それより、今回も研究の手伝いを";
		mes "してくれるんじゃろ？";
		next;
		menu "ええ",-;
		mes "[タラシー博士]";
		mes "この前の実験で";
		mes "わかったことが一つある！";
		mes "草は所詮草じゃった。";
		mes "時代はキノコなんじゃよ。";
		mes "キノコを混ぜれば研究は成功する";
		mes "ワシはこう考えておる！";
		next;
		menu "時代とか関係ないような……",-;
		mes "[タラシー博士]";
		mes "時代なんじゃよ時代。";
		mes "これは重要じゃよ？";
		mes "流行に乗り遅れてはイカン！";
		next;
		menu "は、はぁ",-;
		mes "[タラシー博士]";
		mes "それじゃ";
		mes "詳細をライラに聞いてくれ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[タラシー博士]";
		mes strcharinfo(0)+"！";
		mes "すまないがワシは急いでおるのじゃ。";
		mes "ライラに内容をきいてくれい。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close;
	case 3:
		mes "‐研究に集中しているのか";
		mes "　こちらに気づかないようだ‐";
		close;
	case 4:
		emotion 7;
		mes "[タラシー博士]";
		mes "おお！";
		mes "まっていたぞ！";
		mes "キノコならば成功するはずじゃ！";
		next;
		mes "[タラシー博士]";
		mes "もう少しで、薬を完成させられる！";
		mes "そうすれば、ワシも……";
		mes "ムフフフ";
		next;
		menu "どんな薬を作っているんですか？",-;
		mes "[タラシー博士]";
		mes "それは、企業秘密というやつじゃな！";
		mes "教えるわけにはいかん！";
		mes "それより早速、キノコを";
		mes "この液体に入れてみるぞい！";
		next;
		misceffect 109,"#AC_BOM";
		mes "‐黒い変なキノコを液体に";
		mes "　投げ入れた。";
		mes "　しかし何もおこらなかった‐";
		next;
		mes "[タラシー博士]";
		mes "……";
		mes "…………";
		mes "んー、どうやら失敗のようじゃ……";
		mes "しかし、成分が調和して";
		mes "違う効果の薬になっていることも";
		mes "十分に考えられる。";
		next;
		mes "[タラシー博士]";
		mes "というわけでじゃ！";
		mes "おぬし、ためしにのんでみい！";
		next;
		menu "遠慮しておきます……",-;
		mes "[タラシー博士]";
		mes "つべこべ言わんで";
		mes "早く飲まんかい！";
		next;
		misceffect 7,"";
		percentheal 100,100;
		mes "[タラシー博士]";
		mes "どうじゃ？";
		mes "何か起こったか？";
		next;
		menu "元気になったきがします",-;
		mes "[タラシー博士]";
		mes "そうじゃろ？";
		mes "ワシも薄々気づいとったんじゃよ。";
		mes "しかし、肝心の研究はまたも";
		mes "失敗とは……";
		mes "キノコの種類がわるかったんかも";
		mes "しれないが……";
		next;
		mes "[タラシー博士]";
		mes "とりあえずは、";
		mes "これで依頼はおわりじゃ。";
		mes "また何かあったらよろしく";
		mes "たのむぞい。";
		if('@novice){
			mes "あと、これをうけとれい。";
			next;
			// イグドラシルの葉 3個
			if(!checkweight(610,3)){
				mes "重量オーバー！";
				close;
			}
			getitem 610,3;
		}
		else next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[タラシー博士]";
		mes "とりあえずは、";
		mes "これで依頼はおわりじゃ。";
		mes "また何かあったらよろしく";
		mes "たのむぞい。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST07:
	switch(AC_QUEST_ST_3) {
	case 1:
		emotion 0;
		mes "[タラシー博士]";
		mes strcharinfo(0)+"！";
		mes "まっておったぞ！";
		mes "そいうじゃ、ワシの話を聞いてくれ！";
		mes "先日ワシの誕生日だったんじゃが、";
		mes "なんと、ライラがプレゼントを";
		mes "くれたんじゃよ！";
		next;
		menu "良かったですね",-;
		mes "[タラシー博士]";
		mes "じゃろ？";
		mes "きっとライラはワシのことが";
		mes "好きなんじゃよ。";
		mes "だからプレゼントをしてくれたに";
		mes "違いない。";
		mes "そう思わんか？";
		next;
		menu "どうでしょうか？",-;
		mes "[タラシー博士]";
		mes "いや、そうに決まっておる！";
		mes "しかしワシ、恥ずかしながら";
		mes "女性とお付き合いを";
		mes "したことがないからな。";
		mes "そのために研究を完成させる";
		mes "必要があるんじゃ！";
		next;
		mes "[タラシー博士]";
		mes "ということでじゃ！";
		mes "今回も、研究材料の収集を";
		mes "依頼したいのじゃ！";
		mes "詳しくはライラから聞くのじゃよ？";
		next;
		menu "わかりました",-;
		mes "[タラシー博士]";
		mes "それじゃ";
		mes "よろしく頼んだぞい！";
		mes "そうそう、さっき話したことを";
		mes "ライラに聞いたりしては";
		mes "いかんぞ？";
		mes "恥ずかしがらせてしまうからな。";
		next;
	L_REP4_1:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FF助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[タラシー博士]";
		mes strcharinfo(0)+"！";
		mes "すまないがワシは急いでおるのじゃ。";
		mes "ライラに内容をきいてくれい。";
		next;
		goto L_REP4_1;
	case 3:
		mes "‐研究に集中しているのか";
		mes "　こちらに気づかないようだ‐";
		close;
	case 4:
		mes "[タラシー博士]";
		mes "おお！";
		mes "ついについに完成じゃな。";
		mes "これで完成するに違いない。";
		mes "ささ、それをこっちによこすのじゃ。";
		next;
		menu "あやしいキノコを渡す",-;
		mes "[タラシー博士]";
		mes "さあ、世紀の一瞬じゃ！";
		next;
		misceffect 70,"#AC_BOM";
		mes "‐博士が液体にあやしいキノコを";
		mes "　放り込んだ。";
		mes "　すると液体があやしい色になり";
		mes "　泡立ち始めた‐";
		next;
		misceffect 106,"#AC_BOM";
		mes "[タラシー博士]";
		mes "爆発しおった!!!!!!!";
		mes "火事じゃーーーーー！";
		mes "早く消すのじゃ!!!!!";
		mes "アチチチチ";
		next;
		menu "どうやって……",-;
		mes "[ライラ]";
		mes "あら、大変！";
		mes "すぐに消さなくてはだめですね。";
		mes "2人ともちょっと下がっていて";
		mes "くださいね。";
		next;
		misceffect 89,"#AC_BOM";
		sc_start2 SC_Freeze,5000,1,10000;
		percentheal -99,0;
		mes "[ライラ]";
		mes "ストームガスト！";
		next;
		mes "[ライラ]";
		mes "……";
		mes "あら……ごめんなさい。";
		mes "少しやりすぎてしまったわ……";
		mes "博士、";
		mes strcharinfo(0) + "さん";
		mes "平気ですか？";
		next;
		menu "な、なんとか……",-;
		mes "[タラシー博士]";
		mes "平気じゃ平気じゃ！";
		mes "ライラの愛を感じたぞい！";
		mes strcharinfo(0) + "も";
		mes "心配ない。";
		mes "なんら問題ないぞい！";
		mes "若いんじゃからな！";
		next;
		mes "[タラシー博士]";
		mes "むむ、それにしても";
		mes "あのキノコでもダメというと";
		mes "他に何を試せばよいのか……";
		mes "やはり草のほうが良いのじゃろうが？";
		mes "ふむ……";
		next;
		menu "あの……",-;
		if('@novice){
			mes "[タラシー博士]";
			mes "すまん、すまん。";
			mes "忘れておったわい。";
			mes "今回の報酬はこれじゃ";
			mes "うけとれい。";
			next;
			// 579 おいしい魚 50個
			if(!checkweight(579,50)){
				mes "重量オーバー！";
				close;
			}
			getitem 579,50;
		}
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[タラシー博士]";
		mes "むむ、それにしても";
		mes "あのキノコでもダメというと";
		mes "他に何を試せばよいのか……";
		mes "やはり草のほうが良いのじゃろうか？";
		mes "ふむ……";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST09:
	switch(AC_QUEST_ST_3) {
	case 1:
		emotion 19;
		mes "[タラシー博士]";
		mes "ノーーーーッ";
		mes "色々とやばいぞい。";
		mes "どうすればよいんじゃ！";
		mes "よいんじゃーーーーーっ！";
		next;
		menu "どうしたんですか？",-;
		mes strcharinfo(0) + "!!!";
		mes "……";
		mes "おぬしになら話してもよいじゃろう……";
		mes "小さな声で言うから";
		mes "心して聞くんじゃぞ。";
		next;
		emotion 19;
		mes "[タラシー博士]";
		mes "なんと……";
		mes "昨日ライラと見知らぬ男が";
		mes "歩いているのを";
		mes "目撃してしまったのじゃ……";
		mes "どんな関係なんじゃろうか……";
		next;
		menu "本人に聞いてみればよいのでは？",-;
		emotion 36;
		mes "[タラシー博士]";
		mes "バカモン！";
		mes "そんなことを聞けるわけ無いじゃろ。";
		mes "うむー、しかしこのままでは……";
		mes "得体の知れない男に";
		mes "たぶらかされてしまう可能性もある。";
		mes "一刻も早く薬を完成させなくては。";
		next;
		mes "[タラシー博士]";
		mes "というわけで、急いで研究材料を";
		mes "採ってきてほしいのじゃ！";
		mes "今度はまちがいないぞい。";
		mes "絶対じゃ！";
		mes "色々調べた結果何が必要だか";
		mes "わかったんじゃよ！";
		next;
		mes "[タラシー博士]";
		mes "詳しくは^FF0000ライラ^000000から聞くのじゃ。";
		next;
		L_REP9_1:
		mes "^FF0000【ミッション】^000000";
		mes "^FF0000助手ライラ^000000さんに依頼の";
		mes "詳細内容を聞く。";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[タラシー博士]";
		mes strcharinfo(0) + " ！";
		mes "すまないがワシが急いでおるのじゃ。";
		mes "ライラに内容をきいてくれい。";
		next;
		goto L_REP9_1;
	case 3:
		mes "‐研究に集中しているのか";
		mes "　こちらに気づかないようだ‐";
		close;
	case 4:
		emotion 0;
		mes "[タラシー博士]";
		mes "おお！";
		mes "ついにじゃ！";
		mes "ついにこの時がきた。";
		mes "さあ、早くよこすのじゃ！";
		next;
		menu "ミンミン草を渡す",-;
		mes "[タラシー博士]";
		mes "よし、まずはミンミン草を入れるぞい。";
		next;
		misceffect 94,"#AC_BOM";
		mes "‐博士が液体に";
		mes "　ミンミン草を入れた瞬間、";
		mes "　液体が光はじめた‐";
		next;
		mes "[タラシー博士]";
		mes "よしっ！";
		mes "成功じゃ！";
		mes "成功じゃよ!!!!";
		next;
		mes "[ライラ]";
		mes "博士おめでとうございます！";
		next;
		mes "[タラシー博士]";
		mes "ライラありがとう。";
		mes "ここまで長かった……";
		next;
		mes "[ライラ]";
		mes "ところで、博士……";
		mes "この薬は、何の薬なのですか？";
		next;
		menu "私も気になっていました。",-;
		emotion 29;
		mes "[タラシー博士]";
		mes "フフフッ";
		mes "教えてやるワイ。";
		mes "これはのぉ……";
		mes "なんと、なぁぁぁんと！";
		mes "女性の心が読める薬なんじゃ！";
		next;
		menu "ええッ!?",-;
		emotion 23,"ライラ#AC";
		emotion 23,"";
		mes "[タラシー博士]";
		mes "そう、そしてこの髪をいれて";
		mes "飲めば！";
		mes "ライラの心が手に取るようにわかる";
		mes "はずなのじゃ！";
		next;
		mes "‐博士はすばやい動きで、";
		mes "　液体にライラの髪の毛をいれ";
		mes "　それを飲み干した‐";
		next;
		mes "[タラシー博士]";
		mes "フハハハハ。";
		mes "さあ、ライラ心をさらけ出すのじゃ！";
		mes "さらけ出すのじゃーーーー！";
		next;
		mes "[タラシー博士]";
		mes "……";
		mes "…………";
		next;
		mes "[タラシー博士]";
		mes "なっ、なんじゃと!?";
		mes "心が読めない!?";
		mes "どういうことなんじゃ。";
		mes "ワシの研究は完璧なはず……";
		next;
		mes "[タラシー博士]";
		mes "……";
		mes "…………";
		mes "実はですね……";
		mes "私、実は…………";
		next;
		mes "‐ライラは自分のカバンから";
		mes "　カプセルのようなものを取り出し";
		mes "　飲み込んだ‐";
		next;
		emotion 23;
		emotion 23,"";
		donpcevent "#AC_BOM::OnEvent";
		mes "[ライラ]";
		mes "男なんです……";
		mes "実は変身の薬というのを";
		mes "以前作りまして……";
		next;
		mes "[タラシー博士]";
		mes "ギャーーーーッ";
		mes "…………";
		next;
		mes "‐タラシー博士は";
		mes "　叫びながら叫んだ後";
		mes "　気絶してしまったようだ……‐";
		next;
		mes "[ライラ]";
		mes "あらら……";
		mes "気絶してしまいましたね……";
		next;
		mes "[ライラ]";
		mes "後は私が何とかしておきます。";
		mes "本当に色々ありがとうございました。";
		if('@novice){
			mes "これが今回の報酬になりますので";
			mes "うけとってくださいね。";
			next;
			switch(Job){
			//剣士    ：ヘルム[0] 1個
			case Job_Swordman:
				set '@item,2228;
				break;
			//シーフ  ：キャップ[0] 1個
			case Job_Thief:
			//商人    ：キャップ[0] 1個
			case Job_Merchant:
			//アチャ  ：キャップ[0] 1個
			case Job_Archer:
				set '@item,2226;
				break;
			//アコ    ：ビレタ[0] 1個
			case Job_Acolyte:
				set '@item,2216;
				break;
			//マジ    ：丸いぼうし[0] 1個
			case Job_Magician:
			//テコン  ：丸いぼうし[0] 1個
			case Job_TaeKwon:
			//忍者    ：丸いぼうし[0] 1個
			case Job_Ninja:
			//ガンスリ：丸いぼうし[0] 1個
			case Job_Gunslinger:
				set '@item,2222;
				break;
			//ノビ    ：スーパーノービス帽[0] 1個
			//スパノビ：スーパーノービス帽[0] 1個
			default:
				set '@item,5112;
				break;
			}
			if(!checkweight('@item,1)){
				mes "重量オーバー！";
				close;
			}
			getitem '@item,1;
		}
		else next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "‐タラシー博士は気を失っている‐";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_CLEAR:
	mes "[タラシー博士]";
	mes strcharinfo(0) + "じゃないか！";
	mes "色々手伝ってもらって";
	mes "凄くたすかったぞい。";
	mes "また何かあったらお願いしたい！";
	close;
L_OTHER:
	mes "[タラシー博士]";
	mes "こうするとこうなって……";
	mes "いやはや、難しい……";
	close;
}
hu_in01.gat,305,27,4	script	ライラ#AC	69,{
	set '@novice, callfunc("AC_GetNovice");
	switch(AC_QUEST_LV_3){
	case 0:
		goto L_QUEST01;
	case 2:
		goto L_QUEST03;
	case 4:
		goto L_QUEST05;
	case 6:
		goto L_QUEST07;
	case 8:
		goto L_QUEST09;
	case 9:
		goto L_CLEAR;
	default:
		goto L_OTHER;
	}
L_QUEST01:
	switch(AC_QUEST_ST_3) {
	case 2:
		mes "[ライラ]";
		mes "博士から話を伺っております。";
		mes "依頼の詳細内容ですね？";
		next;
		menu "よろしくお願いします",-;
		mes "[ライラ]";
		mes "いえ、こちらこそ";
		mes "お忙しいところ依頼を引き受けて";
		mes "下さってたすかりますわ。";
		next;
		mes "[ライラ]";
		mes "依頼内容なのですが、";
		mes "^0000FFゲフェンフィールド07(185 249)^000000";
		mes "に生えている";
		mes "^FF0000ポムポム草^000000を採ってきて";
		mes "いただきますか？";
		next;
		//本鯖どおり（いただき）
		menu "どんな草なんですか？",-;
		mes "[ライラ]";
		mes "あ、ごめんなさい。";
		mes "ポムポム草はですね……";
		next;
		mes "‐ライラからポムポム草の";
		mes "　説明を受けた‐";
		next;
		mes "[ライラ]";
		mes "それじゃあ";
		mes "よろしくお願いしますね。";
		next;
		menu "わかりました",-;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFゲフェンフィールド07(185 249)^000000";
		mes "に生えている";
		mes "^FF0000ポムポム草^000000を採ってきくる。";
		mes " ";
		mes "‐^0000FFゲフェンフィールド07^000000へは";
		mes "　ゲフェンから行くと近い‐";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ライラ]";
		mes "依頼内容を忘れてしまいましたか？";
		mes "念のためもう一度お話しますね。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFゲフェンフィールド07(185 249)^000000";
		mes "に生えている";
		mes "^FF0000ポムポム草^000000を採ってくる。";
		mes " ";
		mes "‐^0000FFゲフェンフィールド07^000000へは";
		mes "　ゲフェンから行くと近い‐";
		close;
	case 4:
		mes "[ライラ]";
		mes "あ！";
		mes "お帰りなさい。";
		mes "無事に^FF0000ポムポム草^000000を";
		mes "手に入れられたようですねー。";
		mes "^FF0000ポムポム草^000000は博士に渡して";
		mes "くださいね。";
		close;
	case 99:
		mes "[ライラ]";
		mes "どうやら研究は失敗のようですね。";
		mes "次は成功すると良いのですけど……";
		mes "依頼を受けていただいて";
		mes "ありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST03:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[ライラ]";
		mes "あら、";
		mes strcharinfo(0) + "さん";
		mes "こんにちは。";
		close;
	case 2:
		mes "[ライラ]";
		mes "今回も";
		mes strcharinfo(0) + "さんが";
		mes "手伝ってくれるのですね。";
		next;
		mes "[ライラ]";
		mes "依頼内容なのですが、";
		mes "^0000FFピラミッドダンジョン1F^000000に生えている";
		mes "^FF0000ライライ草^000000を採ってきて";
		mes "いただけますか？";
		mes "ライライ草は……";
		next;
		menu "わかりました",-;
		mes "‐ライラからライライ草の";
		mes "　説明を受けた‐";
		next;
		mes "[ライラ]";
		mes "ピラミッドダンジョンは";
		mes "モロクの近くにありますので";
		mes "街に行けばわかると思います。";
		mes "一応メモ書いておきますね。";
		mes "それでは、よろしくお願いします。";
		next;
	L_REP3_3:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFピラミッドダンジョン1F(193,193)^000000";
		mes "に生えている";
		mes "^FF0000ライライ草^000000を採ってくる。";
		mes " ";
		mes "‐^0000FFピラミッドダンジョン1F^000000へは";
		mes "　^0000FFモロク^000000から行くと近い‐";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ライラ]";
		mes "依頼内容を忘れてしまいましたか？";
		mes "念のためもう一度お話しますね。";
		next;
		mes "[ライラ]";
		mes "依頼内容なのですが、";
		mes "^0000FFピラミッドダンジョン1F^000000に生えている";
		mes "^FF0000ライライ草^000000を採ってきて";
		mes "いただけますか？";
		next;
		goto L_REP3_3;
	case 4:
		mes "[ライラ]";
		mes "さすが、";
		mes strcharinfo(0) + "さんですね。";
		mes "無事に^FF0000ライライ草^000000を手に入れましたか。";
		mes "それでは、博士に渡してくださいね。";
		close;
	case 99:
		mes "[ライラ]";
		mes "どうやら研究は失敗のようですね。";
		mes "次は成功すると良いのですけど……";
		mes "依頼を受けていただいて";
		mes "ありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST05:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[ライラ]";
		mes "あら、";
		mes strcharinfo(0) + "さん";
		mes "こんにちは。";
		close;
	case 2:
		mes "[ライラ]";
		mes strcharinfo(0)+"さん";
		mes "に手伝っていただいた研究で";
		mes "博士は何か新しい調合を";
		mes "思いついたみたいです。";
		mes "今度は成功するかもしれませんね！";
		next;
		mes "[ライラ]";
		mes "さっそく、";
		mes "依頼内容なのですが、";
		mes "^0000FFフェイヨンダンジョン1F^000000に生えている";
		mes "^FF0000黒い変なキノコ^000000を採ってきて";
		mes "いただけますか？";
		mes "^FF0000黒い変なキノコ^000000は……";
		next;
		menu "わかりました",-;
		mes "‐ライラから黒い変なキノコの";
		mes "説明を受けた‐";
		next;
		mes "[ライラ]";
		mes "フェイヨンダンジョンは";
		mes "フェイヨンの近くにありますので";
		mes "街に行けばわかると思います。";
		mes "一応メモを書いておきますね。";
		mes "それでは、よろしくお願いします。";
		next;
	L_REP4_2:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフェイヨンダンジョン1F^000000";
		mes "に生えている";
		mes "^FF0000黒い変なキノコ^000000を採ってくる。";
		mes " ";
		mes "‐^0000FFフェイヨンダンジョン1F^000000へは";
		mes "^0000FFフェイヨン^000000から行くと近い‐";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ライラ]";
		mes "依頼内容を忘れてしまいましたか？";
		mes "念のためもう一度お話しますね。";
		next;
		mes "[ライラ]";
		mes "依頼内容なのですが、";
		mes "^0000FFフェイヨンダンジョン1F^000000に生えている";
		mes "^FF0000黒い変なキノコ^000000を採ってきて";
		mes "いただけますか？";
		next;
		goto L_REP4_2;
	case 4:
		mes "[ライラ]";
		mes strcharinfo(0)+"さん";
		mes "おかえりなさい。";
		mes "無事に^FF0000黒い変なキノコ^000000を手に";
		mes "入れたようですね。";
		mes "それでは、博士に渡してくださいね。";
		close;
	case 99:
		mes "[ライラ]";
		mes "また、失敗してしまったようで……";
		mes "そういえば、助手の私にも";
		mes "今回の研究内容を";
		mes "教えてくれないのですが。";
		mes "何かご存知ですか？";
		next;
		menu "い、いえ……",-;
		mes "[ライラ]";
		mes "やはりですか……";
		mes "何を研究しているのか";
		mes "凄い気になります……";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST07:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[ライラ]";
		mes strcharinfo(0) + "さん";
		mes "こんにちは。";
		mes "いつもありがとうございます。";
		close;
	case 2:
		mes "[ライラ]";
		mes strcharinfo(0) + "さん";
		mes "こんにちは。";
		mes "もう、お得意様ですね。";
		mes "本当にいつもお世話になっています。";
		next;
		mes "[ライラ]";
		mes "早速今回お願いする";
		mes "収集品について説明いたしますね。";
		mes "えと……";
		mes "今回は、^0000FFフェイヨン迷いの森 02^000000に";
		mes "生えている、^FF0000あやしいキノコ^000000を";
		mes "採ってきてください。";
		next;
		mes "‐ライラからあやしいキノコの";
		mes "　説明を受けた‐";
		next;
		mes "[ライラ]";
		mes "それでは、";
		mes "今回もよろしくお願いしますね。";
		next;
	L_REP5_2:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFフェイヨン迷いの森 02(49,126)^000000";
		mes "に生えている、";
		mes "^FF0000あやしいキノコ^000000を採ってくる。";
		mes "‐^0000FFフェイヨン迷いの森 02^000000へは";
		mes "　フェイヨンから行くと近い‐";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ライラ]";
		mes "依頼内容を忘れてしまいましたか？";
		mes "念のためもう一度お話しますね。";
		next;
		mes "[ライラ]";
		mes "今回は、^0000FFフェイヨン迷いの森 02^000000に";
		mes "生えている、^FF0000あやしいキノコ^000000を";
		mes "採ってきてくださいね。";
		mes "^0000FFフェイヨン迷いの森 02^000000には";
		mes "^0000FFフェイヨン^000000から行くとよいですよ。";
		mes "それではよろしくお願いします。";
		next;
		goto L_REP5_2;
	case 4:
		mes "[ライラ]";
		mes "さすが、";
		mes strcharinfo(0) + "さんですね。";
		mes "無事に^FF0000あやしいキノコ^000000を";
		mes "手に入れましたか。";
		mes "それでは、博士に渡してくださいね。";
		close;
	case 99:
		mes "[ライラ]";
		mes strcharinfo(0) + "さん";
		mes "先ほどは本当に申し訳";
		mes "ありませんでした……";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "気にしないでください。";
		mes "それよりも博士にプレゼントを";
		mes "あげたとか？";
		next;
		mes "[ライラ]";
		mes "ええ、";
		mes "普段お世話になっていますから";
		mes "お誕生日プレゼントぐらいは";
		mes "差し上げないといけませんしね。";
		next;
		menu "なるほど！",-;
		mes "[ライラ]";
		mes "ふふふっ。";
		mes "それじゃ、また何かありましたら";
		mes "よろしくお願いしますね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST09:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[ライラ]";
		mes strcharinfo(0) + "さん";
		mes "こんにちは。";
		mes "何か博士が荒れているんです";
		mes "どうしたんでしょうか……";
		close;
	case 2:
		mes "[ライラ]";
		mes "相変わらず博士は荒れていますね……";
		mes "一体どうしたんでしょうか……";
		next;
		mes "[ライラ]";
		mes "でも、今回の材料は博士";
		mes "かなり自信があるみたいなんですよ。";
		mes "でも、成功するかもしれないというのに";
		mes "ちょっとおかしいんです。";
		mes "焦っているというか";
		mes "そんな感じですね……";
		next;
		mes "[ライラ]";
		mes "えと、収集していただく材料なのですが";
		mes "一つ目は、^0000FFプロンテラ地下水路3F^000000に";
		mes "生えている^FF0000ミンミン草^000000で、";
		mes "もう一つは……";
		mes "^FF0000私の髪の毛^000000!?";
		next;
		mes "[ライラ]";
		mes "んー、私の髪の毛が";
		mes "入っているのは何ででしょうか……";
		next;
		mes "[ライラ]";
		mes "とりあえず髪の毛は私が直接博士に";
		mes "渡しておきますので、";
		mes strcharinfo(0) + "さんは、";
		mes "もう一つの材料を採って来て";
		mes "くださいますか？";
		next;
		mes "[ライラ]";
		mes "えと、^0000FFプロンテラ地下水路3F^000000に";
		mes "生えている^FF0000ミンミン草^000000ですね。";
		mes "それではよろしくお願いします。";
		next;
	L_REP9_2:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFプロンテラ地下水路3F（184,17）";
		mes "に生えている^FF0000ミンミン草^000000を採ってくる。";
		mes " ";
		mes "‐^0000FFプロンテラ地下水路3F^000000へは";
		mes "　^0000FFプロンテラ^000000から行くと近い‐";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ライラ]";
		mes "依頼内容を忘れてしまいましたか？";
		mes "念のためにもう一度お話しますね。";
		next;
		mes "[ライラ]";
		mes "依頼内容なのですが、";
		mes "^0000FFプロンテラ地下水路3F^000000に";
		mes "生えている^FF0000ミンミン草^000000を";
		mes "採ってきてください。";
		next;
		goto L_REP9_2;
	case 4:
		mes "[ライラ]";
		mes strcharinfo(0) + "さん。";
		mes "お帰りなさい。";
		mes "髪の毛は私が先ほど渡しておきました。";
		mes "^FF0000ミンミン草^000000を博士に渡してくださいね。";
		close;
	case 99:
		mes "[ライラ]";
		mes "色々お手伝いいただいて";
		mes "本当にありがとうございました。";
		mes "博士が起きたら、";
		mes "事情を説明しておきますから";
		mes "安心してくださいね。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_CLEAR:
	mes "[ライラ]";
	mes strcharinfo(0) + "さん";
	mes "色々とありがとうございました！";
	next;
	mes "[ライラ]";
	mes "博士、私が変身していること";
	mes "覚えていないみたいです。";
	mes "ですので、このまま秘密にしておく";
	mes "ことにしますね。";
	close;
L_OTHER:
	mes "[ライラ]";
	mes "あら、こんにちは。";
	close;
}
hu_in01.gat,308,27,4	script	#AC_BOM	139,{
OnEvent:
	disablenpc "ライラ#AC";
	enablenpc "ライラ#AC2";
	misceffect 744,"ライラ#AC2";
	misceffect 30,"ライラ#AC2";
	misceffect 72,"ライラ#AC2";
	sleep 5000;
	disablenpc "ライラ#AC2";
	enablenpc "ライラ#AC";
}
hu_in01.gat,305,27,4	script	ライラ#AC2	740,{
OnInit:
	disablenpc;
}
gef_fild07.gat,179,242,4	script	#AC_POMPOM	1083,{
}
gef_fild07.gat,179,241,4	script	ポムポム草#AC	111,{
	if(AC_QUEST_LV_3!=0 || AC_QUEST_ST_3!=3) goto L_OTHER;
	mes "[" + strcharinfo(0) + "]";
	mes "この草で間違いなさそうだ。";
	next;
	mes "‐ポムポム草を一つ手に入れた‐";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ポムポム草^000000を";
	mes "届ける。";
	close2;
	set AC_QUEST_ST_3,4;
	end;
L_OTHER:
	mes "‐草が生えている‐";
	if(AC_QUEST_LV_3!=0 || AC_QUEST_ST_3!=4)close;
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ポムポム草^000000を";
	mes "届ける。";
	close;
}
moc_pryd01.gat,193,193,0	script	#AC_RAIRAI	1081,{
}
moc_pryd01.gat,193,192,0	script	ライライ草#AC	111,{
	if(AC_QUEST_LV_3!=2 || AC_QUEST_ST_3!=3) goto L_OTHER;
	mes "[" + strcharinfo(0) + "]";
	mes "この草で間違いなさそうだ。";
	next;
	mes "‐^FF0000ライライ草^000000を一つ手に入れた‐";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ライライ草^000000を";
	mes "届ける。";
	close2;
	set AC_QUEST_ST_3,4;
	end;
L_OTHER:
	mes "‐草が生えている‐";
	if(AC_QUEST_LV_3!=2 || AC_QUEST_ST_3!=4)close;
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ライライ草^000000を";
	mes "届ける。";
	close;
}
pay_dun00.gat,154,172,0	script	#AC_KINOKO1	1084,{
}
pay_dun00.gat,154,171,0	script	黒い変なキノコ#AC	111,{
	if(AC_QUEST_LV_3!=4 || AC_QUEST_ST_3!=3) goto L_OTHER;
	mes "[" + strcharinfo(0) + "]";
	mes "このキノコで間違いなさそうだ。";
	next;
	mes "‐^FF0000黒い変なキノコ^000000を一つ手に入れた‐";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000黒い変なキノコ^000000を";
	mes "届ける。";
	close2;
	set AC_QUEST_ST_3,4;
	end;
L_OTHER:
	mes "‐キノコが生えている‐";
	if(AC_QUEST_LV_3!=4 || AC_QUEST_ST_3!=4)close;
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000黒い変なキノコ^000000を";
	mes "届ける。";
	close;
}
pay_fild02.gat,52,125,0	script	#AC_KINOKO2	1085,{
}
pay_fild02.gat,52,124,0	script	あやしいキノコ#AC	111,{
	if(AC_QUEST_LV_3!=6 || AC_QUEST_ST_3!=3) goto L_OTHER;
	mes "[" + strcharinfo(0) + "]";
	mes "この草で間違いなさそうだ。";
	next;
	mes "‐^FF0000あやしいキノコ^000000を一つ手に入れた‐";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000あやしいキノコ^000000を";
	mes "届ける。";
	close2;
	set AC_QUEST_ST_3,4;
	end;
L_OTHER:
	mes "‐キノコが生えている‐";
	if(AC_QUEST_LV_3!=6 || AC_QUEST_ST_3!=4)close;
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000あやしいキノコ^000000を";
	mes "届ける。";
	close;
}
prt_sewb3.gat,184,17,0	script	#AC_MINMIN	1080,{
}
prt_sewb3.gat,184,16,0	script	ミンミン草#AC	111,{
	if(AC_QUEST_LV_3!=8 || AC_QUEST_ST_3!=3) goto L_OTHER;
	mes "[" + strcharinfo(0) + "]";
	mes "この草で間違いなさそうだ。";
	next;
	mes "‐^FF0000ミンミン草^000000を一つ手に入れた‐";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ミンミン草^000000を";
	mes "届ける。";
	close2;
	set AC_QUEST_ST_3,4;
	end;
L_OTHER:
	mes "‐草が生えている‐";
	if(AC_QUEST_LV_3!=8 || AC_QUEST_ST_3!=4)close;
	next;
	mes "^FF0000【ミッション】^000000";
	mes "^FF0000タラシー博士^000000に^FF0000ミンミン草^000000を";
	mes "届ける。";
	close;
}
hu_in01.gat,113,313,4	script	アムロン	47,{
	set '@novice, callfunc("AC_GetNovice");
	if(!AC_QUEST_ST_3) goto L_OTHER;
	switch(AC_QUEST_LV_3){
	case 1:
		goto L_QUEST02;
	case 3:
		goto L_QUEST04;
	case 5:
		goto L_QUEST06;
	case 7:
		goto L_QUEST08;
	case 9:
		goto L_CLEAR;
	default:
		goto L_OTHER;
	}
L_QUEST02:
	switch(AC_QUEST_ST_3) {
	case 1:
		emotion 0;
		mes "[アムロン]";
		mes "お！";
		mes "君ですか？";
		mes "依頼を引き受けてくれる冒険者は。";
		next;
		menu "えと、冒険者協会の？",-;
		mes "[アムロン]";
		mes "すまない。";
		mes "挨拶が遅れてしまいましたね。";
		mes "私は冒険者協会を統括している";
		mes "アムロンといいます。";
		mes "よろしくお願いしますね。";
		next;
		mes "[アムロン]";
		mes "まず、冒険者協会がどんなことを";
		mes "するところなのかを説明させて";
		mes "いただくね。";
		next;
		mes "[アムロン]";
		mes "冒険者協会は簡単に言うと";
		mes "何でも請け負うボランティアだよ。";
		mes "ただし、普通の人で解決するのが";
		mes "難しい案件のみ扱っている。";
		next;
		mes "[アムロン]";
		mes "ダンジョンの中に人が取り残されて";
		mes "しまったとか、";
		mes "冒険者じゃないと助けるのが";
		mes "困難な状態とか、そういうのを";
		mes "助けたりするんです。";
		next;
		mes "[アムロン]";
		mes "今回、冒険者アカデミーが全面的に";
		mes "バックアップしてくれるということで";
		mes "本当に助かっているよ。";
		mes "普通に雇ったらすごいお金が";
		mes "かかってしまうからね……";
		next;
		mes "[アムロン]";
		mes "ということでだ。";
		mes "早速、依頼内容を";
		mes "説明するね。";
		next;
		mes "[アムロン]";
		mes "むむっ";
		mes "これは、";
		mes "急がないとまずいかもしれないな。";
		mes "どうやら、子供がダンジョンに";
		mes "取り残されているらしい。";
		next;
		mes "[アムロン]";
		mes "名前は、^FF0000チスロー^000000。";
		mes "年齢10歳の男の子だそうです。";
		mes "^0000FFプロンテラ地下水路1F^000000に行ってくる";
		mes "とのメモを残して";
		mes "門限になっても帰ってこないそうだ。";
		next;
		mes "[アムロン]";
		mes "ことは一刻を争うとおもう。";
		mes "モンスターもいるからね。";
		mes "もし、^FF0000チスロー^000000を見つけたら";
		mes "この、^0000FF蝶の羽^000000を渡してほしい。";
		mes " ";
		mes "‐蝶の羽が入った袋を受け取った‐";
		next;
	L_REP2_1:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFプロンテラ地下水路1F（301,206）^000000に";
		mes "にいる^FF0000チスロー^000000に蝶の羽を渡す。";
		mes " ";
		mes "‐^0000FFプロンテラ地下水路1F^000000へは";
		mes "　^0000FFプロンテラ^000000から行くと近い‐";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[アムロン]";
		mes "急いでいってください。";
		mes "ことは一刻を争うからね。";
		next;
		goto L_REP2_1;
	case 3:
		mes "[アムロン]";
		mes "今さっき、依頼主から";
		mes "お礼の連絡があったよ。";
		mes strcharinfo(0)+"さん";
		mes "ご苦労様。";
		mes "本当に子供も、貴方も無事で";
		mes "良かった。";
		next;
		mes "[アムロン]";
		mes "それでは、また何かありましたら";
		mes "アカデミーの方に連絡しますので";
		mes "もし、手が開いていたら";
		mes "そのときはよろしくお願いします。";
		mes "ありがとうございました。";
		next;
	L_REP2_3:
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうございました。";
		next;
		goto L_REP2_3;
	default:
		goto L_OTHER;
	}
L_QUEST04:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "今回も貴方が引き受けて";
		mes "くれるのですか？";
		next;
		menu "ええ",-;
		mes "[アムロン]";
		mes "いやー、助かりますよ。";
		mes "それでは早速、";
		mes "今回の依頼内容について";
		mes "説明させてもらうよ。";
		next;
		mes "[アムロン]";
		mes "^0000FFイズルード海底洞窟1F^000000で";
		mes "かくれんぼをして遊んでいた";
		mes "女の子1人が5時間たっても、";
		mes "見つからないらしい。";
		next;
		mes "[アムロン]";
		mes "名前は、^FF0000ツイーフラ。^000000";
		mes "年齢11歳の女の子だそうだ。";
		next;
		mes "[アムロン]";
		mes "^FF0000ツイーフラ^000000を見つけたら";
		mes "前回同様に";
		mes "この、^0000FF蝶の羽^000000を渡してほしい。";
		mes " ";
		mes "‐蝶の羽が入った袋を受け取った‐";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFイズルード海底洞窟1F(351,45)^000000に";
		mes "いる^FF0000ツイーフラ^000000に蝶の羽を渡す。";
		mes " ";
		mes "^0000FF‐イズルード海底洞窟^000000には";
		mes "イズルードから船でいける";
		mes "バイラン島にある‐";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[アムロン]";
		mes "それにしても、普通ダンジョンで";
		mes "遊んだりしませんよね……";
		mes "親はどういう教育をしているん";
		mes "だろうか……";
		mes "とりあえず急いでいってください。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFイズルード海底洞窟1F(351,45)^000000に";
		mes "いる^FF0000ツイーフラ^000000に蝶の羽を渡す。";
		mes "‐^0000FFイズルード海底洞窟^000000には";
		mes "イズルードから船でいける";
		mes "バイラン島にある‐";
		close;
	case 3:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "お疲れ様でした。";
		mes "無事、ミッション達成ですね。";
		mes "丁度今、";
		mes "依頼主から連絡がありましたよ。";
		next;
		mes "[アムロン]";
		mes "それでは、また何かありましたら";
		mes "アカデミーの方に連絡しますので";
		mes "もし、手が開いていたら";
		mes "そのときはよろしくお願いします。";
		mes "ありがとうございました。";
		next;
	L_REP4_3:
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうございました。";
		next;
		goto L_REP4_3;
	default:
		goto L_OTHER;
	}
L_QUEST06:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[アムロン]";
		mes "お待ちしておりましたよ。";
		mes strcharinfo(0)+"さん";
		mes "今回の依頼内容は";
		mes "猫探しです！";
		next;
		menu "猫ですか!?",-;
		mes "[アムロン]";
		mes "ええ、どうやら数日前から";
		mes "依頼主の猫が見当たらない";
		mes "らしい。";
		mes "それで、猫の居場所を";
		mes "突き止めてほしいそうなんです。";
		next;
		mes "[アムロン]";
		mes "他の冒険者から、";
		mes "プロンテラ地下水路2Fに";
		mes "猫らしき姿を見たという情報を";
		mes "得ていますので、";
		mes "^FF0000プロンテラ地下水路2F^000000の";
		mes "捜索をお願いできますか？";
		next;
		mes "[アムロン]";
		mes "猫の名前は、^FF0000メルシー^000000ちゃん";
		mes "今年で2歳だそうです。";
		mes "凄く頭の良い猫らしく、";
		mes "^008800蝶の羽^000000を渡してあげれば";
		mes "自分で帰って来れるそうだ。";
		next;
		mes "[アムロン]";
		mes "なのでメルシーちゃんを";
		mes "見つけたら";
		mes "前回同様に蝶の羽を";
		mes "渡してくださいな。";
		mes " ";
		mes "‐蝶の羽が入った袋を受け取った‐";
		next;
	L_REP6_1:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFプロンテラ地下水路2F(159,182)^000000";
		mes "にいる^FF0000メルシー^000000ちゃんに";
		mes "蝶の羽を渡す。";
		mes " ";
		mes "^0000FF‐プロンテラ地下水路2F^000000へは";
		mes "　^0000FFプロンテラ^000000からいける‐";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[アムロン]";
		mes "それじゃお願いしますね。";
		next;
		goto L_REP6_1;
	case 3:
		emotion 4;
		emotion 23,"";
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "^FF0000メルシーちゃん^000000無事に";
		mes "戻ってきたそうですよ。";
		mes "でも……またすぐに行方不明に";
		mes "なったとか……";
		next;
		menu "そうですか……",-;
		mes "[アムロン]";
		mes "とりあえず依頼は終了です。";
		mes "それでは、また何かありましたら";
		mes "アカデミーの方に連絡しますので";
		mes "もし、手が空いていたら";
		mes "そのときはよろしくお願いします。";
		mes "ありがとうございました。";
		next;
	L_REP6_3:
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう‐";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_QUEST08:
	switch(AC_QUEST_ST_3) {
	case 1:
		mes "[アムロン]";
		mes "こんにちは、";
		mes strcharinfo(0) + "さん";
		mes "早速依頼内容を説明させて";
		mes "いただきますね。";
		next;
		mes "[アムロン]";
		mes "新米の冒険者がペアで";
		mes "冒険をしていたらしいのですが";
		mes "モンスターに囲まれてしまい";
		mes "一人が動けない状況に";
		mes "なってしまっているようです。";
		next;
		mes "[アムロン]";
		mes "ペアを組んでいた相方さんも";
		mes "怪我をしているらしく、";
		mes "すぐに助けに行くことができまい";
		mes "とのこと。";
		mes "ということで今回の依頼は";
		mes "この新米冒険者の救出となります。";
		next;
		mes "[アムロン]";
		mes "名前は^FF0000ザーパフ^000000。";
		mes "年齢は20歳の男性です。";
		mes "今回も同じく^008800蝶の羽^000000と";
		mes "この^008800傷薬^000000を渡してあげてください。";
		mes "‐蝶の羽と傷薬が";
		mes "　入った袋を受け取った‐";
		next;
	L_REP8_1:
		mes "^FF0000【ミッション】^000000";
		mes "^0000FFイズルード海底洞窟2F(129,79)^000000";
		mes "にいる^FF0000ザーパフ^000000に";
		mes "^008800蝶の羽^000000と^008800傷薬^000000を渡す。";
		mes " ";
		mes "‐^0000FFイズルード海底洞窟2F^000000へは";
		mes "　^0000FFイズルード^000000から船で行く‐";
		close2;
		set AC_QUEST_ST_3,2;
		end;
	case 2:
		mes "[アムロン]";
		mes "それじゃお願いしますね。";
		next;
		goto L_REP8_1;
	case 3:
		mes "[アムロン]";
		mes strcharinfo(0) + "さん";
		mes "いかがでしたか？";
		next;
		menu "事情を説明する",-;
		emotion 4;
		mes "[アムロン]";
		mes "なんと……";
		mes "ま、まあ、無事でよかったですよね！";
		mes "しかし、あんな場所で寝てるとは";
		mes "どれだけ、";
		mes "肝のすわっている人";
		mes "なんでしょうか……";
		next;
		mes "[アムロン]";
		mes "とりあえず、";
		mes "ミッション完了ということで……";
		mes strcharinfo(0) + "さん";
		mes "ありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close2;
		set AC_QUEST_ST_3,99;
		end;
	case 99:
		mes "[アムロン]";
		mes strcharinfo(0)+"さん";
		mes "ありがとうございました。";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "依頼を達成した！";
		mes "冒険者アカデミーに";
		mes "報告しに行こう。";
		close;
	default:
		goto L_OTHER;
	}
L_OTHER:
	mes "[アムロン]";
	mes "こんにちは。";
	close;
L_CLEAR:
	mes "[アムロン]";
	mes strcharinfo(0)+"さん";
	mes "貴方はほんとにすばらしい";
	mes "冒険者です。";
	mes "また、何かありましたら";
	mes "よろしくお願いしますね。";
	close;
}
prt_sewb1.gat,301,206,4	script	チスロー#AC	896,{
	if(AC_QUEST_LV_3!=1) goto L_OTHER;
	switch(AC_QUEST_ST_3) {
	case 2:
		mes "[チスロー]";
		mes "うわーん、うわーん。";
		mes "蝶の羽わすれて、";
		mes "帰れなくなっちゃったよー";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "チスロー君";
		mes "助けに来たよ。";
		next;
		emotion 0;
		mes "[チスロー]";
		mes "!?";
		mes "グスッ、グスッ";
		mes "ありがとう……";
		mes "これで家に帰れる。";
		next;
		emotion 15;
		mes "[チスロー]";
		mes "よーーし！";
		mes "蝶の羽があれば平気だし";
		mes "もうちょっと探検していこっと！";
		mes "ありがとうね！";
		next;
	L_REP01:
		mes "^FF0000【ミッション】^000000";
		mes "無事に蝶の羽を渡したことを";
		mes "^FF0000アムロン^000000に報告する。";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[チスロー]";
		mes "わざわざ来てくれてありがとうね。";
		mes "僕は少し探検したら";
		mes "帰るから安心して！";
		next;
		goto L_REP01;
	default:
		goto L_OTHER;
	}
L_OTHER:
	mes "[チスロー]";
	mes "探検探検たのしいなー。";
	close;
}
iz_dun00.gat,351,45,4	script	ツイーフラ#AC	96,{
	if(AC_QUEST_LV_3!=3) goto L_OTHER;
	switch(AC_QUEST_ST_3) {
	case 2:
		mes "[ツイーフラ]";
		mes "……";
		next;
		menu "ツイーフラちゃん？",-;
		mes "[ツイーフラ]";
		mes "シーッ";
		mes "いまかくれんぼしているんだから";
		mes "話しかけないでよね！";
		mes "鬼にばれちゃう！";
		next;
		menu "事情を説明する",-;
		mes "[ツイーフラ]";
		mes "私って凄い！";
		mes "そんなことになるほど";
		mes "わからなかったのねー。";
		mes "かくれんぼ名人？";
		mes "フフフッ";
		next;
		mes "[ツイーフラ]";
		mes "でも、わざわざきてくれてありがと。";
		mes "ちゃんと家に帰るようにする！";
		mes "それじゃあねー。";
		next;
	L_REP01:
		mes "^FF0000【ミッション】^000000";
		mes "無事に蝶の羽を渡したことを";
		mes "^FF0000アムロン^000000に報告する。";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ツイーフラ]";
		mes "ちゃんと後で帰るから";
		mes "心配しないで！";
		next;
		goto L_REP01;
	default:
		goto L_OTHER;
	}
L_OTHER:
	mes "[ツイーフラ]";
	mes "……";
	close;
}
prt_sewb2.gat,159,182,4	script	メルシーちゃん#AC	876,{
	if(AC_QUEST_LV_3!=5) goto L_OTHER;
	switch(AC_QUEST_ST_3) {
	case 2:
		mes "[メルシーちゃん]";
		mes "ニャーニャー";
		next;
		menu "メルシーちゃん？",-;
		mes "[メルシーちゃん]";
		mes "ニャーニャーニャー";
		next;
		menu "事情を説明する",-;
		mes "[" + strcharinfo(0) + "]";
		mes "（どうやらメルシーちゃんのようだ。";
		mes "　蝶の羽を渡そう。";
		mes "　本当にこれで平気なんだろうか";
		mes "　……）";
		next;
	L_REP01:
		mes "^FF0000【ミッション】^000000";
		mes "無事に蝶の羽を渡したことを";
		mes "^FF0000アムロン^000000に報告する。";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[メルシーちゃん]";
		mes "ニャー！";
		next;
		goto L_REP01;
	default:
		goto L_OTHER;
	}
L_OTHER:
	mes "[メルシーちゃん]";
	mes "ニャーニャー";
	close;
}
iz_dun01.gat,129,79,4	script	ザーパフ#AC	887,{
	if(AC_QUEST_LV_3!=7) goto L_OTHER;
	switch(AC_QUEST_ST_3) {
	case 2:
		mes "[ザーパフ]";
		mes "Zzzzz……";
		next;
		menu "ザーパフさん？",-;
		mes "[ザーパフ]";
		mes "んんっ？";
		mes "ムニャムニャ……";
		mes "もう食べられないよ……";
		next;
		menu "ザーパフさん！",-;
		emotion 23;
		mes "[ザーパフ]";
		mes "どわぁぁぁっ！";
		mes "なんだなんだ？";
		next;
		menu "事情を説明する",-;
		mes "[ザーパフ]";
		mes "なるほど、そういうことだったのか、";
		mes "でも平気だよ！";
		mes "俺寝てるだけだから。";
		mes "いやー、凄く眠くてさ";
		mes "ここ、冷たくて気持ちいいんだよね。";
		next;
		menu "……",-;
		mes "[ザーパフ]";
		mes "でも、ありがたく";
		mes "^008800傷薬^000000と^008800蝶の羽^000000はもらっておくよ。";
		mes "それじゃ！";
		next;
	L_REP01:
		mes "^FF0000【ミッション】^000000";
		mes "無事に蝶の羽を渡したことを";
		mes "^FF0000アムロン^000000に報告する。";
		close2;
		set AC_QUEST_ST_3,3;
		end;
	case 3:
		mes "[ザーパフ]";
		mes "Zzzzz……";
		next;
		goto L_REP01;
	default:
		goto L_OTHER;
	}
L_OTHER:
	mes "[ザーパフ]";
	mes "Zzzzz……";
	close;
}
