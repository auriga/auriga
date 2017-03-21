//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  昇級試験
//                                                  by Pneuma
//------------------------------------------------------------

// -----------------------------------------------------------
// 昇級試験関連
// -----------------------------------------------------------

ac_cl_area.gat,85,37,4	script	ガルド	122,{

	function	show_mission;

	if(!AC_RANKTEST) goto L_OTHER;
	switch(AC_RANK){
	case 0: goto L_TEST01;
	case 1: goto L_TEST02;
	case 2: goto L_TEST03;
	case 3: goto L_TEST04;
	case 4: goto L_TEST05;
	case 5: goto L_TEST06;
	case 6: goto L_TEST07;
	}
L_TEST01:
	switch(AC_RANKTEST){
	case 1:
		mes "[ガルド]";
		mes "よお！";
		mes "よく来たな！";
		mes "俺の名前はガルド";
		mes "君達の試験を担当させてもらっている。";
		mes "まずは君の名前を教えてくれ。";
		next;
		emotion 9;
		mes "[ガルド]";
		mes strcharinfo(0) + "……";
		mes "……" + strcharinfo(0) + "。";
		mes "どうやら第一試験を受ける資格が";
		mes "あるようだな。";
		next;
		mes "[ガルド]";
		mes "そうだ、一つ説明しておくが、試験";
		mes "という言葉で身構えなくてもいいぞ。";
		mes "今まで、君が請け負ってきた";
		mes "ルーンからの依頼と大差ないからな。";
		next;
		mes "[ガルド]";
		mes "早速試験の内容を説明させてもらおう。";
		mes "冒険者アカデミーには、";
		mes "当たり前だが";
		mes "俺以外にも教師がいる。";
		next;
		mes "[ガルド]";
		mes "だが、ほとんどの教師は";
		mes "学園外で、モンスターの生態研究";
		mes "などおこなっているんだ。";
		next;
		mes "[ガルド]";
		mes "そして、定期的に研究資料を";
		mes "提出してもらい、それを授業に";
		mes "役立てている感じなんだ。";
		next;
		mes "[ガルド]";
		mes "ということでだ、";
		mes "今回の試験の内容は、";
		mes "フェイヨン迷いの森03に設置されている";
		mes "ホルンの研究ボックスから";
		mes "研究報告書をとって来ることだ。";
		next;
		mes "[ガルド]";
		mes "あー、そういえば";
		mes "研究ボックスには鍵がかかっていて";
		mes "いくつかアイテムが";
		mes "必要だった気がするな。";
		next;
		emotion 21;
		mes "[ガルド]";
		mes "でも、全部フェイヨン迷いの森03に";
		mes "生息するモンスターから";
		mes "取得できるものだったはずだ。";
		mes "それじゃ、よろしくな！";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		goto L_REPEAT;
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "どうやら無事に研究報告書を";
		mes "持ってきたようだな。";
		next;
		mes "[ガルド]";
		mes "-ガルドに";
		mes "　ホルン先生の研究報告書を";
		mes "　渡した-";
		next;
	case 99:
		emotion 46;
		mes "[ガルド]";
		mes "第一試験突破おめでとう！";
		mes "後は、ルーンに報告するだけだ。";
		mes "お疲れ様！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐依頼を達成した！";
		mes "ルーンさんに報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_TEST02:
	switch(AC_RANKTEST){
	case 1:
		mes "[ガルド]";
		mes "よお！";
		mes strcharinfo(0);
		mes "そろそろ来る頃だと思っていたぜ。";
		mes "君なら、第二試験もラクラク";
		mes "クリアできるんじゃないかな？";
		next;
		mes "[ガルド]";
		mes "それじゃ、";
		mes "早速第二試験の内容について";
		mes "説明するぞ！";
		next;
		mes "[ガルド]";
		mes "今回も、前回同様に";
		mes "研究報告書を取ってきて";
		mes "ほしいんだ。";
		next;
		mes "[ガルド]";
		mes "本当は、他の内容にしようと";
		mes "思ったんだが、ポリン先生から";
		mes "いつまでたっても報告書が";
		mes "送られてこなくてな……";
		next;
		mes "[ガルド]";
		mes "ポリン先生は";
		mes "フェイヨン迷いの森04で";
		mes "研究をおこなっているはずなのだが";
		mes "何かあったんだろうか……";
		next;
		mes "[ガルド]";
		mes "というわけで、";
		mes "ポリン先生から研究報告書を";
		mes "とってきてくれ。";
		next;
		mes "[ガルド]";
		mes "あ！";
		mes "確か定期的に強いモンスターが";
		mes "現れる場所だった気がするから";
		mes "十分注意していけよ？";
		mes "それじゃ、頼んだぜ。";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		goto L_REPEAT;
	case 3: //ポリン先生にゼロピとべと液を要求される
	case 4: //空きビンを要求される
		goto L_MICHOUSA; //未調査
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "どうやら無事に研究報告書を";
		mes "持ってきたようだな。";
		next;
		mes "‐ガルドに";
		mes "　ポリン先生の研究報告書を";
		mes "　渡した‐";
		next;
	case 99:
		emotion 46;
		mes "[ガルド]";
		mes "第二試験突破おめでとう！";
		mes "後は、ルーンに報告するだけだ。";
		mes "お疲れ様！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "^FF0000ルーン^000000さんに";
		mes "報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_TEST03:
	switch(AC_RANKTEST){
	case 1:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "じゃないか！";
		mes "第三試験を受けに来たんだな。";
		next;
		emotion 5;
		mes "[ガルド]";
		mes "三回目の試験はっと……";
		mes "お、今回のも研究報告書を";
		mes "とってくるものだな。";
		next;
		mes "[ガルド]";
		mes "場所はフェイヨン迷いの森02だな。";
		mes "この場所は、ウルフ先生か！";
		next;
		mes "[ガルド]";
		mes "というわけで、";
		mes "フェイヨン迷いの森02にいる";
		mes "ウルフ先生から研究報告書を";
		mes "とってきてくれ。";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		goto L_REPEAT;
	case 3: //ウルフ先生に噛まれた
	case 4: //つぼを見つけた
		goto L_MICHOUSA; //未調査
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "どうやら無事に研究報告書を";
		mes "持ってきたようだな。";
		next;
		mes "‐ガルドに";
		mes "　ウルフ先生の研究報告書を";
		mes "　渡した‐";
		next;
	case 99:
		emotion 46;
		mes "[ガルド]";
		mes "第三試験突破おめでとう！";
		mes "後は、ルーンに報告するだけだ。";
		mes "お疲れ様！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "^FF0000ルーン^000000さんに";
		mes "報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_TEST04:
	switch(AC_RANKTEST){
	case 1:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "じゃないか！";
		mes "第三試験を受けに来たんだな。";
		next;
		mes "[ガルド]";
		mes "四回目の試験は、";
		mes "^0000FFプロンテラ^000000から、";
		mes "^0000FFゲフェン^000000まで歩いてもらう！";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		mes "[ガルド]";
		mes "ん、内容をもう一度聞きたいのか？";
		next;
		if(select("はい","いいえ")==2){
			mes "[ガルド]";
			mes "そうか、頑張れよ！";
			close;
		}
		mes "[ガルド]";
		mes "わかった。";
		mes "覚え切れなかったら";
		mes "メモをするんだ。";
		next;
		mes "[ガルド]";
		mes "四回目の試験は、";
		mes "^0000FFプロンテラ^000000から、";
		mes "^0000FFゲフェン^000000まで歩いてもらう！";
		next;
		show_mission;
		close;
	case 3: // プロ西口
	case 4: // プロ西左上WP手前
	case 5: // mjolnir_09 WP
	case 6: // ドラッブ先生にお弁当を渡す
	case 7: // prt_fild00 WP
		emotion 0;
		mes "[ガルド]";
		mes "!?";
		mes "試験途中で戻ってきてしまうとは……";
		mes "まあ、戻ってきてしまったものは";
		mes "仕方ない。";
		mes "もう一度はじめから試験を";
		mes "受けなおしてもらうぞ。";
		next;
		cutin "quest_route001.bmp",3;
		mes "[ガルド]";
		mes "いいか？";
		mes "試験は^0000FFプロンテラ^000000から、";
		mes "^0000FFゲフェン^000000まで歩くんだ。";
		next;
		show_mission;
		next;
		mes "[ガルド]";
		mes "ということだ。";
		mes "頑張れよ！";
		close2;
		set AC_RANKTEST,2;
		end;
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes "おお！";
		mes strcharinfo(0);
		mes "無事に戻ったな。";
		next;
		mes "[ガルド]";
		mes "ドラップ先生にも";
		mes "しっかりと";
		mes "お弁当を渡せたようだな。";
		next;
	case 99:
		emotion 46;
		mes "[ガルド]";
		mes "ということでだ、";
		mes strcharinfo(0);
		mes "第四試験合格おめでとう！";
		mes "後はルーンに報告すれば";
		mes "完了だ！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "^FF0000ルーン^000000さんに";
		mes "報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_TEST05:
	switch(AC_RANKTEST){
	case 1:
		mes "[ガルド]";
		mes "よお！";
		mes strcharinfo(0) + "！";
		mes "早いものでもう、第五試験だな。";
		mes "今回の試験の内容はっと……";
		mes "ふむ、今回も研究報告書を";
		mes "とってきてもらう試験のようだ。";
		next;
		mes "[ガルド]";
		mes "さて、詳細内容だが、";
		mes "ミョルニール山脈09に設置されている";
		mes "ホルンの研究ボックスから";
		mes "研究報告書をとってきてもらいたい。";
		next;
		mes "[ガルド]";
		mes "ホルン先生研究報告書が";/*のが抜けてるが本鯖どおり*/
		mes "入っているボックスにはいつも鍵がかかっている。";
		mes "確かこの場所のを空けるには";
		mes "暗号が必要だったはずだ……";
		next;
		mes "[ガルド]";
		mes "暗号は、ポストについているボタンを";
		mes "押すことでヒントを";
		mes "得られた気がするんだが、";
		mes "詳しくは忘れてしまった。";
		next;
		mes "[ガルド]";
		mes "まあ、とりあえず現地に";
		mes "向かってみてほしい。";
		mes "現地を調べれば";
		mes "わかるかもしれないしな。";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		goto L_REPEAT;
	case 3:
	case 4:
	case 5:
	case 6:
		goto L_MICHOUSA; //未調査
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "どうやら無事に研究報告書を";
		mes "持ってきたようだな。";
		next;
		mes "[ガルド]";
		mes "-ガルドに";
		mes "　ホルン先生の研究報告書を";
		mes "　渡した-";
		next;
	case 99:
		emotion 46;
		mes "[ガルド]";
		mes "第五試験突破おめでとう！";
		mes "後は、ルーンに報告するだけだ。";
		mes "お疲れ様！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "ルーンさんに報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_TEST06:
	switch(AC_RANKTEST){
	case 1:
		mes "[ガルド]";
		mes "来たな！";
		mes strcharinfo(0);
		mes "第六試験はなかなか難しい";
		mes "試験だぞ！";
		next;
		mes "[ガルド]";
		mes "今まで、何回か名前の出てきた";
		mes "ホルン先生を覚えているだろうか？";
		mes "彼は、好奇心と研究に対する";
		mes "真剣さが尋常ではないんだ。";
		next;
		mes "[ガルド]";
		mes "だから、";
		mes "自分の知らない土地であっても、";
		mes "危険だとわかっている場所であっても";
		mes "後先のことを考えずに";
		mes "何処にでも行ってしまう。";
		next;
		mes "[ガルド]";
		mes "そういうことで、彼は定期的に";
		mes "迷子になってしまうのだ！";
		mes "しかもだ、彼は無理して続けていることが";
		mes "多い為、発見した時には";
		mes "瀕死になっている事が多いのだ……";
		next;
		mes "[ガルド]";
		mes "正直なところ、";
		mes "一人前の冒険者でなければ";
		mes "彼を見つけるのは難しいだろう。";
		mes "しかし！";
		mes "逆に言えばだ！";
		next;
		mes "[ガルド]";
		mes "彼を見つけることができれば、";
		mes "一人前の冒険者といっても";
		mes "過言ではない。";
		next;
		mes "[ガルド]";
		mes "そういうことでだ！";
		mes "今回の試験はホルン先生を";
		mes "見つけ、ミルクを渡すことだ！";
		next;
		mes "[ガルド]";
		mes "ちなみに、ミルクを届けることも";
		mes "重要な任務になるからな？";
		mes "ミルクは学校の販売員から";
		mes "手に入れてくれ。";
		mes "頼まれたものを手に入れて、しっかりと";
		mes "届けるのも冒険者の基本だ。";
		next;
		mes "[ガルド]";
		mes "ということで、早速行ってくるんだ！";
		mes "と言いたい所だが、";
		mes "情報が少なすぎて、";
		mes "これでは探す場所の絞込みが";
		mes "できないだろう。";
		next;
		mes "[ガルド]";
		mes "一つヒントをあげよう。";
		mes "フェイヨン迷いの森08 で";
		mes "ホルン先生を見かけたという";
		mes "情報が入っている。";
		mes "もし、これで発見しミルクを渡せば";
		mes "第六試験合格になるわけだが";
		next;
		mes "[ガルド]";
		mes "この情報は若干古い情報でな";
		mes "今その場所にいるかどうかは";
		mes "実際に見に行って見ないと";
		mes "わからない。";
		next;
		mes "[ガルド]";
		mes "それじゃあ、気をつけて";
		mes "言って来るんだぞ。";
		next;
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		goto L_REPEAT;
	case 3:
		mes "[ガルド]";
		mes "なるほどな。";
		mes "ホロン先生に会ったのか。";
		mes "頑張ってホルン先生を";
		mes "見つけてミルクを渡すんだぞ？";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^FF0000ホルン先生^000000を見つけ、ミルクを渡す‐";
		mes "‐^0000FFミョルニール山脈06^000000付近で";
		mes "　ホルン先生の後姿を見かけたとの";
		mes "　情報あり。";
		mes "　^0000FFミョルニール山脈06^000000へは";
		mes "　^0000FFゲフェン^000000から向かうと近い‐";
		close;
	case 4:
		mes "[ガルド]";
		mes "ビートル先生に会ったのか。";
		mes "後姿はホルン先生と";
		mes "そっくりだからな。";
		mes "間違えても仕方ないだろう。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^FF0000ホルン先生^000000を見つけ、ミルクを渡す‐";
		mes "‐^FF0000ホルン先生^000000は";
		mes "　^0000FFソグラト砂漠 18^000000に向かった";
		mes "　との情報あり。";
		mes "　^0000FFソグラト砂漠 18^000000へは";
		mes "　^0000FFモロク^000000から向かうと近い‐";
		close;
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "お帰り！";
		mes "無事にホルン先生には";
		mes "会えたのかい？";
		next;
		mes "‐ガルドにホルン先生のメモを渡した‐";
		next;
		mes "[ガルド]";
		mes "なるほど、";
		mes strcharinfo(0) + "が";
		mes "ホルン先生の命を救ったのか。";
		mes "今回君が試験を受けていなかったら";
		mes "彼の命はなかったということだな……";
		next;
		mes "[ガルド]";
		mes "俺からもお礼を言わせてもらおう";
		mes "ありがとうな！";
		mes "勿論試験も文句なしの合格だ！";
		mes "次の試験もがんばってくれよ？";
		mes "それじゃあ、ルーンに報告";
		mes "しに行ってくれ！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐依頼を達成した！";
		mes "ルーンさんに";
		mes "報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	case 99: //【ミッション】と【依頼達成】の違いは？？？
		mes "[ガルド]";
		mes "俺からもお礼を言わせてもらおう";
		mes "ありがとうな！";
		mes "勿論試験も文句なしの合格だ！";
		mes "次の試験もがんばってくれよ？";
		mes "それじゃあ、ルーンに報告";
		mes "しに行ってくれ！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "ルーンさんに";
		mes "報告しに行こう‐";
		close;
	}
L_TEST07:
	switch(AC_RANKTEST){
	case 1:
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "ついに第七試験だな。";
		mes "これに合格すれば";
		mes "君は晴れて、冒険者アカデミー";
		mes "第一過程修了ということになる！";
		next;
		mes "[ガルド]";
		mes "最終試験にふさわしく";
		mes "今までの試験よりも";
		mes "大変だからな。";
		mes "心してかかるように。";
		next;
		mes "[ガルド]";
		mes "それでは、";
		mes "試験の内容について";
		mes "説明させてもらうぞ。";
		next;
		L_REP07:
		cutin "quest_route002.bmp",3;
		//モロク崩壊前はモロクからプロンテラ6マップ移動
		mes "[ガルド]";
		mes "今回の内容は、";
		mes "フェイヨンからプロンテラまで";
		mes "歩いて到達することだ。";
		next;
		mes "[ガルド]";
		mes "ただ、これだけでは簡単な試験に";
		mes "なってしまう。";
		mes "そこで、私が指定する場所を通り、";
		mes "写真やアイテムなども";
		mes "ついでにとってきてほしい。";
		next;
		mes "[ガルド]";
		mes "一つ目は、チュンリム湖の水を";
		mes "とって来ることだ。";
		mes "そして二つ目は、指定の場所を";
		mes "撮影してくること。";
		mes "三つ目は、草を採ってくることだ。";
		next;
		mes "[ガルド]";
		mes "ちなみに今頼んだものは";
		mes "全て、フェイヨンからプロンテラへ";
		mes "向かっている途中で";
		mes "手に入れることができる。";
		next;
		mes "[ガルド]";
		mes "一つずつ詳しく説明するぞ。";
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 2:
		mes "[ガルド]";
		mes "ん、内容をもう一度聞きたいのか？";
		next;
		if(select("はい","いいえ")==2){
			mes "[ガルド]";
			mes "そうか、頑張れよ！";
			close;
		}
		mes "[ガルド]";
		mes "わかった。";
		mes "覚え切れなかったら";
		mes "メモをするんだ。";
		next;
		goto L_REP07;
	case 3:  // ヤニクから水をもらう
	case 4:  // 盗賊に捕まる
	case 5:  // 荷物の場所を聞き出す
	case 6:  // 荷物を取り戻した
	case 7:  // WP前自動会話
	case 8:  // 廃墟の写真を撮る
	case 9:  // WP前自動会話
	case 10: // ミシュラン先生に話しかける
	case 11: // 草を採る
	case 12: // 茂みからポリンが出る(省略可能)
	case 13: // ミシュラン先生に魔法をかけてもらう
	case 14: // WP前自動会話
	case 15: // WP前自動会話
	case 16: // プロ西入り口自動会話
		emotion 18;
		mes "[ガルド]";
		mes "試験途中で戻ってきてしまうとは……";
		mes "まあ、戻ってきてしまったものは";
		mes "仕方ない。";
		mes "もう一度はじめから試験を";
		mes "受けなおしてもらうぞ。";
		next;
		mes "[ガルド]";
		mes "再度詳しく説明するぞ";
		show_mission;
		close2;
		set AC_RANKTEST,2;
		end;
	case 98:
		emotion 0;
		mes "[ガルド]";
		mes "おお！";
		mes strcharinfo(0) + "じゃないか！";
		mes "だいぶ時間がたっていたから";
		mes "心配していたんだが";
		mes "こうして無事に戻ってきてくれて";
		mes "うれしいよ。";
		next;
		mes "[ガルド]";
		mes "指定されたものは";
		mes "もってきてくれたのか？";
		next;
		mes "‐ガルドに";
		mes "　^006600浄水したチュンリム湖の水^000000と";
		mes "　^006600魔法のかかった草^000000を";
		mes "　渡した‐";
		next;
		mes "[ガルド]";
		mes "おお！確かに確認したぞ。";
		next;
	case 99:
		mes "[ガルド]";
		mes strcharinfo(0);
		mes "本当に成長したな。";
		mes "この試験を合格できた時点で";
		mes "君は一人前の冒険者だ！";
		next;
		mes "[ガルド]";
		mes "それじゃ、いつもどおり";
		mes "ルーンに報告してくれ。";
		mes "これからもがんばれよ！";
		next;
		mes "^FF0000【依頼達成】^000000";
		mes "‐依頼を達成した！";
		mes "ルーンさんに";
		mes "報告しに行こう‐";
		close2;
		set AC_RANKTEST,99;
		end;
	}
L_MICHOUSA: //未調査はここへ
L_REPEAT:
	mes "[ガルド]";
	mes "ん、内容をもう一度聞きたいのか？";
	next;
	if(select("はい","いいえ")==2){
		mes "[ガルド]";
		mes "そうか、頑張れよ！";
		close;
	}
	mes "[ガルド]";
	mes "わかった。";
	mes "覚え切れなかったら";
	mes "メモをするんだ。";
	next;
	show_mission;
	next;
	mes "[ガルド]";
	mes "ということだ。";
	mes "頑張れよ！";
	close;
L_OTHER:
	switch(AC_RANK){
	case 0:
		mes "[ガルド]";
		mes "俺の名前はガルド";
		mes "君達の試験を担当させてもらっている。";
		next;
		mes "[ガルド]";
		mes "試験を受けるためには、";
		mes "ルーンの依頼をいくつかこなして";
		mes "単位を稼ぐ必要があるからな。";
		mes "単位を稼ぎ、ルーンにて試験の";
		mes "手続きをしたら、";
		mes "もう一度俺のところに来てくれ！";
		next;
		mes "[ガルド]";
		mes "まってるぞ！";
		close;
	case 1:
		mes "[ガルド]";
		mes "第一試験合格おめでとう！";
		close;
	case 2: mes "[ガルド]";
		mes "第二試験合格おめでとう！";
		close;
	case 3: mes "[ガルド]";
		mes "第三試験合格おめでとう！";
		close;
	case 4:
		mes "[ガルド]";
		mes "第四試験合格おめでとう！";
		close;
	case 5:
		mes "[ガルド]";
		mes "第五試験合格おめでとう！";
		close;
	case 6:
		mes "[ガルド]";
		mes "第六試験合格おめでとう！";
		close;
	case 7: case 8:
		emotion 18;
		mes "[ガルド]";
		mes "よお！";
		mes strcharinfo(0);
		mes "君がひよっ子だった頃が";
		mes "懐かしいな。";
		close;
	}
	end;

OnInit:
	waitingroom "試験", 0;
	end;

	function	show_mission	{
		switch(AC_RANK){
		case 0:
			mes "^FF0000【ミッション】^000000";
			mes "^0000FFフェイヨン迷いの森03^000000にある";
			mes "^FF0000ホルンの研究ボックス^000000から";
			mes "^006600研究報告書^000000を取ってくる。";
			mes " ";
			mes "‐^0000FFフェイヨン迷いの森03^000000へは、";
			mes "　^0000FFアルベルタ^000000からいける‐";
			break;
		case 1: mes "^FF0000【ミッション】^000000";
			mes "‐^0000FFフェイヨン迷いの森04^000000にいる";
			mes "^FF0000ポリン先生^000000から";
			mes "^006600研究報告書^000000を預かってくる‐";
			mes " ";
			mes "‐^0000FFフェイヨン迷いの森04^000000へは、";
			mes "^0000FFプロンテラ^000000からいける‐";
			break;
		case 2: mes "^FF0000【ミッション】^000000";
			mes "‐^0000FFフェイヨン迷いの森02^000000にいる";
			mes "^FF0000ウルフ先生^000000から";
			mes "^006600研究報告書^000000を預かってくる‐";
			mes " ";
			mes "‐^0000FFフェイヨン迷いの森02^000000へは、";
			mes "^0000FFフェイヨン^000000からいける‐";
			break;
		case 3:
			mes "[ガルド]";
			mes "冒険者として足で世界を歩くのは";
			mes "すごく重要なことだ。";
			mes "だからここでそれを";
			mes "学んでもらうということだな。";
			next;
			cutin "quest_route001.bmp",3;
			mes "[ガルド]";
			mes "後、途中";
			mes "^0000FFプロンテラフィールド00 (163,244)^000000";
			mes "付近にいる^FF0000ドラップ先生^000000に、";
			mes "この、お弁当を渡して";
			mes "サインをもらってきてきてくれ。";
			next;
			mes "[ガルド]";
			mes "今説明したことを行い、";
			mes "ゲフェンに到達した時点で";
			mes "試験は合格となる！";
			mes "しかし、指定したアイテムを";
			mes "所持していなかったり、";
			mes "指定したルートを通ってこないと";
			next;
			mes "[ガルド]";
			mes "試験は失敗、全てやり直しとなる。";
			mes "後、全てを終わらせる前に";
			mes "私に話しかけた場合も同様に";
			mes "やり直しとなるからな。";
			mes "それじゃ頑張ってな！";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐指定された内容をクリアしながら";
			mes "指定されたルートを通り";
			mes "‐^0000FFプロンテラ^000000から^0000FFゲフェン^000000を目指す‐";
			break; 
		case 4:
			mes "^FF0000【ミッション】^000000";
			mes "‐^0000FFミョルニール山脈09^000000にある";
			mes "^006600ホルンの研究ボックス^000000から";
			mes "^FF0000研究報告書^000000を取ってくる。";
			mes " ";
			mes "‐^0000FFミョルニール山脈09^000000へは、";
			mes "^0000FFプロンテラ^000000からいける‐";
			break;
		case 5:
			mes "^FF0000【ミッション】^000000";
			mes "‐^FF0000ホルン先生^000000を見つけ、ミルクを渡す‐";
			mes "‐^0000FFフェイヨン迷いの森08^000000で";
			mes "　目撃したという情報があるらしい";
			mes "　まずは、この場所を調べてみよう";
			mes "　^0000FFフェイヨン迷いの森08^000000へは";
			mes "　^0000FFフェイヨン^000000から行くと近い‐";
			break;
		case 6: 
			mes "^0000FFチュンリム湖^000000の北東あたりに";
			mes "^FF0000行商人のヤニク^000000という男がいる。";
			mes "そいつに、俺から頼まれたといえば";
			mes "^006600浄水したチュンリム湖の水^000000を";
			mes "もらうことが出来るはずだ。";
			next;
			mes "[ガルド]";
			mes "二つ目の詳しい説明だが。";
			mes "^006600ソグラト砂漠01^000000の南側の";
			mes "丘にある石造りの廃墟を";
			mes "撮影してきてくれ。";
			next;
			mes "[ガルド]";
			mes "続いて三つ目の詳しい説明だ。";
			mes "^0000FFプロンテラフィールド09^000000の";
			mes "オアシス付近にいる";
			mes "^FF0000ミシュラン先生^000000に話しかけ";
			mes "^006600魔法のかかった草^000000をもらって来てほしい。";
			next;
			mes "[ガルド]";
			mes "今説明した全ての内容を行い";
			mes "プロンテラに^FF0000西側から^000000到達した時点で試験は合格となる！";
			mes "しかし、指定したアイテムを";
			mes "所持していなかったり、";
			mes "指定したルートを通ってこないと";
			next;
			mes "[ガルド]";
			mes "試験は失敗、全てやり直しとなる。";
			mes "後、全てを終わらせる前に";
			mes "私に話しかけた場合も同様に";
			mes "やり直しとなるからな。";
			mes "それじゃ頑張ってな！";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐指定された内容をクリアしながら";
			mes "指定されたルートを通り";
			mes "‐^0000FFフェイヨン^000000から^0000FFプロンテラ^000000を目指す‐";
			break;
		}
		return;
	}
}

//第１課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00

pay_fild03.gat,209,141,4	script	看板	835,{
	mes "‐北西= プロンテラ方面";
	mes "‐北= フェイヨン方面";
	mes "‐東= アルベルタ";
	mes "‐西= モロク方面";
	close;
}
pay_fild03.gat,209,143,4	script	ホルンの研究ボックス	888,{
	if(AC_RANK || AC_RANKTEST!=2){
		mes "‐冒険者アカデミー";
		mes "　ホルンの研究ボックス";
		mes "　「ゴミは入れないでね！";
		mes "　みんなのホルン先生より」";
		mes "　と書かれている‐";
		close;
	}
	if(AC_RANKTEST==98) goto L_FIN;
	mes "[ホルンの研究ボックス]";
	mes " ";
	mes "‐このボックスを開けるためには";
	mes "　クローバー1個 木の根1個が";
	mes "　必要です‐";
	next;
	if(countitem(705)>0 && countitem(902)>0){
		mes "[" + strcharinfo(0) + "]";
		mes "アイテムは、揃っているけど";
		mes "どうしよう。";
		next;
		if(select("ポストに放り込む","止めておく")==2) {
			mes "[" + strcharinfo(0) + "]";
			mes "止めておこう……";
			close;
		} else {
			mes "‐ガラガラ……";
			mes "　ドンドンドン……";
			mes "　中から分厚いノートらしきものが";
			mes "　出てきた‐";
			next;
			L_FIN:
			mes "[" + strcharinfo(0) + "]";
			mes "無事に手に入れることができたな。";
			mes "冒険者アカデミーに戻ろう。";
			next;
			mes "^FF0000【ミッション】^000000";
			mes "‐冒険者アカデミーにいる";
			mes "ガルドに、ホルンの研究書類を渡す‐";
			close2;
			set AC_RANKTEST,98;
			end;
		}
	} else {
		mes "[" + strcharinfo(0) + "]";
		mes "アイテムが足りないようだ。";
		close;
	}
}
//第２課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00

pay_fild04.gat,350,330,4	script	#AC_PORING	1002,{}
pay_fild04.gat,350,329,4	script	ポリン先生	111,{
	if(AC_RANK!=1 || AC_RANKTEST<2){
		mes "[ポリン先生]";
		mes "お腹がすいたなぁ……";
		close;
	}
	switch(AC_RANKTEST){
	case 2:goto L_TEST01;
	case 3:goto L_TEST02;
	case 4:goto L_TEST03;
	case 98:goto L_TEST04;
	}
L_TEST01:
	emotion 28,"#AC_PORING";
	mes "[ポリン先生]";
	mes "お腹がすいた……";
	mes "すいた！";
	mes "すいた～～～～～～～～～!!";
	next;
	set '@dummy,select("ポリン先生ですか？");
	emotion 1,"#AC_PORING";
	mes "[ポリン先生]";
	mes "ん？";
	mes "僕はいかにもポリン先生だけど？";
	mes "何か用？";
	mes "それにしてもお腹がすいて";
	mes "大変だよ。";
	next;
	set '@dummy,select("事情を説明する");
	mes "[ポリン先生]";
	mes "研究報告書だって!?";
	mes "僕はお腹がすいて";
	mes "生命の危機に直面しているんだ！";
	mes "報告書がほしければ";
	mes "食べ物を持ってきてくれ！";
	next;
	mes "[ポリン先生]";
	mes "話はそれからだよ！";
	mes "そうだなー。";
	mes "ゼロピー10個と";
	mes "べとべとする液体 5個ほど";
	mes "これでお腹いっぱいになるはず！";
	next;
	mes "[ポリン先生]";
	mes "この2つのは、そこら辺にいる";
	mes "ポリンやドロップスから";
	mes "手に入るからね。";
	next;
	set '@dummy,select("それって共食いじゃ……");
	mes "[ポリン先生]";
	mes "共食いだって!?";
	mes "ああ、共食いさ！";
	mes "でも僕は自分の命を優先するねっ！";
	mes "というわけでよろしく頼むよ。";
	next;
	L_TEST01_REP:
	mes "^FF0000【ミッション】^000000";
	mes "‐^006600ゼロピー^00000010個と";
	mes "^006600べとべとする液体^000000を5個集めて";
	mes "^FF0000ポリン先生に渡す^000000‐";
	mes " ";
	mes "‐この2つのアイテムは";
	mes "　ドロップスやポリンから得られる‐";
	close2;
	set AC_RANKTEST,3;
	end;
L_TEST02:
	emotion 0,"#AC_PORING";
	mes "[ポリン先生]";
	mes "あ！君！";
	mes "ゼロピー10個と";
	mes "べとべとする液体を5個集めて";
	mes "持って来てくれたの？";
	next;
	if(countitem(909)<10 || countitem(938)<5){
		mes "[ポリン先生]";
		mes "なんだ、もってないじゃないか！";
		mes "早く持ってきてよ！";
		next;
		goto L_TEST01_REP;
	}
	mes "[ポリン先生]";
	mes "あ、もってるじゃないか！";
	mes "早く頂戴！";
	next;
	if(select("はい","いいえ")==2){
		emotion 7,"#AC_PORING";
		mes "[ポリン先生]";
		mes "ケチケチケチケチケチ!!!";
		close;
	}
	emotion 15,"#AC_PORING";
	mes "[ポリン先生]";
	mes "わぁ！ ありがとう!!";
	mes "……";
	mes "…………";
	mes "ちょっと、君！";
	mes "足りないものがあるじゃないか！";
	next;
	mes "[ポリン先生]";
	mes "べとべとする液体";
	mes "このままでどうやって飲むんだよ！";
	mes "ちゃんと空きビンぐらい";
	mes "気を利かせてもってきて";
	mes "くれないと困るよ！";
	mes "まったく。";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐^006600空きビン^000000を1個手に入れて";
	mes "^FF0000ポリン先生に渡す^000000‐";
	mes " ";
	mes "‐このアイテムは";
	mes "　ドロップスやポリンから得られる‐";
	close2;
	set AC_RANKTEST,4;
	end;
L_TEST03:
	mes "[ポリン先生]";
	mes "空きビンは持って来て";
	mes "くれたんだろうね？";
	next;
	if(countitem(713)<1){
		mes "[ポリン先生]";
		mes "なんだ、もってないじゃないか！";
		mes "早く持ってきてよ！";
		close;
	}
	mes "[ポリン先生]";
	mes "あ、持ってるじゃないか！";
	mes "早く頂戴！";
	next;
	if(select("はい","いいえ")==2){
		emotion 7,"#AC_PORING";
		mes "[ポリン先生]";
		mes "ムッカーーッ！";
		mes "見せびらかすだけなんて";
		mes "なんて酷い人だーーっ！";
		close;
	}
	mes "[ポリン先生]";
	mes "君、実は結構良い奴じゃない？";
	mes "ありがとうね。";
	next;
	mes "‐パクパク、ムシャムシャ";
	mes "　モキュモキュ";
	mes "　ゴクゴク‐";
	next;
	mes "[ポリン先生]";
	mes "ふーっ。";
	mes "おいしかったー！";
	mes "君の事は忘れないよー。";
	mes "汚れちゃったけど空きビンは返すね。";
	mes "それじゃあね！";
	next;
	set '@dummy,select("あの、研究報告書を…");
	emotion 17,"#AC_PORING";
	mes "[ポリン先生]";
	mes "！";
	mes "ああ、ごめんごめん。";
	mes "すっかり忘れてた！";
	mes "しっかり届けてね。";
	next;
	L_TEST03_REP:
	mes "^FF0000【ミッション】^000000";
	mes "‐冒険者アカデミーにいる";
	mes "^FF0000ガルド^000000に、^006600研究報告書^000000を渡す‐";
	close2;
	set AC_RANKTEST,98;
	end;
L_TEST04:
	mes "[ポリン先生]";
	mes "おお！";
	mes "食べ物をありがとう！";
	mes "研究報告書を早く持ち帰った方が";
	mes "いいんじゃないかな？";
	next;
	goto L_TEST03_REP;
}
//第３課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00

pay_fild02.gat,105,242,4	script	#AC_WOLF	1107,{}
pay_fild02.gat,105,241,4	script	ウルフ先生	111,{
	if(AC_RANK!=2 || AC_RANKTEST<2){
		mes "[ウルフ先生]";
		mes "Zzzzz……";
		close;
	}
	switch(AC_RANKTEST){
	case 2:
		emotion 36,"#AC_WOLF";
		mes "[ウルフ先生]";
		mes "ウーーーーッ";
		mes "ワンワン！";
		mes "ガブッ";
		next;
		set '@dummy,select("いたっ");
		mes "‐ウルフ先生に噛まれてしまった‐";
		next;
		set '@dummy,select("何をするんですか！");
		emotion 0,"#AC_WOLF";
		mes "[ウルフ先生]";
		mes "!?";
		mes "あれ？";
		mes "ご、ごめんよ。";
		mes "てっきり奴らだと思って。";
		next;
		set '@dummy,select("奴らって？");
		mes "[ウルフ先生]";
		mes "ああ、この辺に住んでる";
		mes "ウルフ達さ。";
		mes "さっき喧嘩してしまってさ。";
		mes "あいつらがまた来たんじゃないかと";
		mes "思ったんだよ。";
		mes "ところで君は？";
		next;
		set '@dummy,select("事情を説明する");
		mes "[ウルフ先生]";
		mes "研究報告書か……";
		mes "すっかり忘れていたよ。";
		mes "この箱の中にしまったはず。";
		mes "取り出すからちょっとまってね。";
		next;
		mes "‐ウルフ先生が箱の上に手を当てて";
		mes "　何かを唱えている。";
		mes "　しかし何もおこらなかった‐";
		next;
		mes "[ウルフ先生]";
		mes "あれ？";
		mes "おっかしいなー。";
		mes "これで箱が空くはずなんだけど……";
		mes "……";
		mes "あ！";
		mes "わかった……";
		next;
		mes "[ウルフ先生]";
		mes "さっきの喧嘩で手を";
		mes "怪我してしまったからだ……";
		mes "傷が癒えるまでは";
		mes "悪いけどあけることができない。";
		next;
		set '@dummy,select("何とかなりませんか？");
		emotion 0,"#AC_WOLF";
		mes "[ウルフ先生]";
		mes "うーん……";
		mes "あ！ そうだ!!";
		mes "あの肉を食べればすぐ";
		mes "傷なんて治っちゃうはずだ！";
		mes "えと、こんなこともあろうかと";
		mes "特別なタレに漬けた肉があるんだ。";
		next;
		mes "[ウルフ先生]";
		mes "それさえ食べれば";
		mes "あけることが出来るはず。";
		mes "僕が今出歩くと、きっとまた";
		mes "喧嘩になっちゃうから。";
		mes "悪いんだけど君が";
		mes "とってきてくれないかな？";
		next;
		set '@dummy,select("わかりました");
		mes "[ウルフ先生]";
		mes "おお、助かるよー。";
		mes "確か、このマップの";
		mes "^0000FF（129,186）^000000付近だったと思う。";
		mes "念のため印を付けておくね。";
		next;
		L_REP:
		mes "^FF0000【ミッション】^000000";
		mes "‐^006600特製のタレに漬けた肉^000000を";
		mes "手に入れて、";
		mes "ウルフ先生に届ける‐";
		close2;
		viewpoint 1,129,186,20,0xFFFF00;
		set AC_RANKTEST,3;
		end;
	case 3:
	case 4:
		mes "[ウルフ先生]";
		mes "あ、おかえり";
		mes "肉は持って来てくれたかな？";
		next;
		if(AC_RANKTEST!=4){
			mes "[ウルフ先生]";
			mes "まだ、もってきてくれてないんだね。";
			mes "僕はここで待っているから";
			mes "頼むねー。";
			next;
			goto L_REP;
		}
		mes "[ウルフ先生]";
		mes "クンクン";
		mes "この匂いは！";
		mes "持って来てくれたんだねー。";
		mes "ありがとう！";
		next;
		set '@dummy,select("肉を渡す");
		mes "[ウルフ先生]";
		mes "‐バクバクバク、バクバクバク";
		mes "　ゲブッ‐";
		next;
		misceffect 77,"#AC_WOLF";
		emotion 54,"#AC_WOLF";
		mes "[ウルフ先生]";
		mes "おいしかったーーーー！";
		mes "おかげで力がわいてきたよ！";
		mes "これで箱が空くはず。";
		next;
		mes "‐ウルフ先生が箱の上に手を当てて";
		mes "　何かを唱えている。";
		mes "　パカッ‐";
		next;
		mes "[ウルフ先生]";
		mes "よしっ。";
		mes "今度は空いたよー";
		mes "これが研究報告書だ。";
		next;
		mes "[ウルフ先生]";
		mes "それじゃ、気をつけて帰ってね";
		L_REP2:
		mes "肉を持ってきてくれて";
		mes "ありがとう！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐冒険者アカデミーにいる";
		mes "^FF0000ガルド^000000に、^006600研究報告書^000000を渡す‐";
		close2;
		set AC_RANKTEST,98;
		end;
	case 98:
		mes "[ウルフ先生]";
		goto L_REP2;
	}
}
pay_fild02.gat,129,186,0	script	掘り返したような跡#ACTEST03		111,{
	mes "‐掘り返したような後がある‐"; //後で本鯖どおり
	if(AC_RANK!=2 || (AC_RANKTEST!=3 && AC_RANKTEST!=4)) close;
	next;
	if(AC_RANKTEST==4){
		mes "[" + strcharinfo(0) + "]";
		mes "肉はこれ以上必要ないな。";
		next;
		goto L_REP;
	}
	set '@dummy,select("掘ってみよう");
	mes "‐掘ってみると中からつぼがでてきた";
	mes "　つぼの中には肉が漬けてある‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "ウルフ先生の漬けた肉に";
	mes "間違いないな。";
	mes "一つ持っていこう。";
	next;
	mes "‐肉を一つ取り、";
	mes "　つぼを埋めなおした‐";
	next;
L_REP:
	mes "^FF0000【ミッション】^000000";
	mes "‐^FF0000ウルフ先生^000000に肉を届ける‐";
	close2;
	viewpoint 1,105,242,20,0xFFFF00;
	set AC_RANKTEST,4;
	end;
}
//第４課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00


// 徒歩クエストのルートタッチ

//prt_fild05.gat,367,205,0				script	AC_TEST04#ROUTE01	139,1,1,{ //プロ西でタッチ
//	if(AC_RANK!=3 || AC_RANKTEST!=2) end;
//	viewpoint 1,105,381,20,0xFFFF00;
//	mes "[" + strcharinfo(0) + "]";
//	mes "ガルドは^0000FFプロンテラ^000000から^0000FFゲフェン^000000へ";
//	mes "歩くことって言ってたっけ。";
//	mes "途中で^FF0000ドラップ先生^000000にお弁当を";
//	mes "渡さなくちゃ。";
//	mes "まずは^FF0000北西の方角へ^000000歩いていこう。";
//	close2;
//	set AC_RANKTEST,3; //フラグ更新
//	end;
//}
prt_fild05.gat,105,372,0				script	AC_TEST04#ROUTE02	139,5,4,{ //プロ西左上WP手前でタッチ
	if(AC_RANK!=3 || AC_RANKTEST!=3) end;
	mes "[" + strcharinfo(0) + "]";
	mes "まだまだ先は長い。";
	mes "がんばろう……";
	close2;
	set AC_RANKTEST,4; //フラグ更新
	end;
}
prt_fild05.gat,292,377,0				script	AC_TEST04#ROUTE03	139,5,5,{ //プロ西右上WP手前でタッチ
	if(AC_RANK!=3 || AC_RANKTEST!=3) end;
	viewpoint 1,105,381,20,0xFFFF00;
	mes "[" + strcharinfo(0) + "]";
	mes "あれ？";
	mes "行き先を間違ったかな？";
	mes " ";
	mes "‐ガルドから言われたルートだと、";
	mes "もっと^0000FF西の方から北に向かう^000000";
	mes "必要があるようだ‐";
	close2;
	end;
}
mjolnir_09.gat,37,244,0					script	AC_TEST04#ROUTE04	139,5,5,{ //プロ←↑の←ワープ手前でタッチ
	if(AC_RANK!=3 || AC_RANKTEST!=4) end;
	mes "[" + strcharinfo(0) + "]";
	mes "確か次の場所が";
	mes "ドラッブ先生がいる所";
	mes "のはずだ。";
	mes "先を急ごう。";
	close2;
	set AC_RANKTEST,5; //フラグ更新
	end;
}
prt_fild00.gat,152,250,0				script	ドラッブ先生	139,4,4,{
// ガルドがドラップというが、
// ドラッブが正しいらしい。（シークレットストーリーに出てきます）
// 修正されないため、ガルドが間違ってるだけだろう……

	if(AC_RANK!=3 || (AC_RANKTEST!=5 && AC_RANKTEST!=6)) end;
	if(AC_RANKTEST==5){
		mes "[ドラッブ先生]";
		mes "調査～、調査～。";
		mes "俺は今日も、穴の中で調査する～。";
		mes "そんな、俺に生徒達はうっとり～♪";
		mes "そして微笑む俺～、";
		mes "生徒達は失神～♪";
		next;
		set '@dummy,select("ガルド先生からこれを……");
		mes "[ドラッブ先生]";
		mes "お！ ガルドからかい！";
		mes "腹が減って死にそうだったんで";
		mes "グッドタイミングというやつだね。";
		mes "穴の中に弁当を放り投げてよ！";
		mes " ";
		mes "‐弁当を穴の中に放り投げた‐";
		next;
		set '@dummy,select("あの、サインを……");
		mes "[ドラッブ先生]";
		mes "サイン！おいおい、";
		mes "俺はそこまで有名人じゃないよ！？";
		mes "（へへっ、いつのまにか俺も人気者";
		mes "になってたのか）";
		next;
		mes "[ドラッブ先生]";
		mes "ま、まぁ、そこまで言うなら";
		mes "サインをあげよう。";
		mes "大事にしてくれよ。";
		mes " ";
		mes "‐ガルドからもらった紙に";
		mes "　サインを書いてもらった‐";
		next;
		mes "[ドラッブ先生]";
		mes "それでは、";
		mes "弁当を食べるとするかなあ。";
		next;
		L_REP:
		mes "[" + strcharinfo(0) + "]";
		mes "（ドラッブ先生からサインをもらった。";
		mes "^FF0000ゲフェン^000000へ向かおう！）";
		close2;
		viewpoint 1,18,129,20,0xFFFF00;
		set AC_RANKTEST,6; //フラグ更新
		end;
	} else {
		mes "[ドラッブ先生]";
		mes "弁当をありがとう！";
		mes "じゃあね!!";
		next;
		goto L_REP;
	}
}
prt_fild00.gat,28,124,0					script	AC_TEST04#ROUTE05	139,5,5,{
	if(AC_RANK!=3 || AC_RANKTEST<5 || AC_RANKTEST>6) end;
	//お弁当わたしたか確認
	if(AC_RANKTEST==5){
		//未調査 撮り忘れ。でもこんな感じだった
		mes "[" + strcharinfo(0) + "]";
		mes "ドラッブ先生にお弁当を渡さなきゃ。";
		close2;
		viewpoint 1,152,250,20,0xFFFF00;
		end;
	}
	mes "[" + strcharinfo(0) + "]";
	mes "あと少しでゲフェンだ！";
	close2;
	set AC_RANKTEST,7; //フラグ更新
	end;
}
geffen.gat,213,119,0					script	AC_TEST04#ROUTE06	139,1,1,{
	if(AC_RANK!=3 || AC_RANKTEST!=7) end;
	mes "無事にゲフェンに着いたぞ！";
	mes "ガルドさんに報告しよう！";
	close2;
	set AC_RANKTEST,98; //フラグ更新
	end;
}

//第５課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00

mjolnir_09.gat,100,365,4	script	ホルンの研究ボックス	888,{
	if(AC_RANK!=4 || AC_RANKTEST<2){
		mes "‐謎の言葉が書かれている‐";
		close;
	}
	switch(AC_RANKTEST){
	case 2:
		mes "[ホルンの研究ボックス]";
		mes " ";
		mes "‐一つ目の暗号を入力してください‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "ボタンを押すとヒントが表示される";
		mes "と書いてあったが。";
		mes "何処にボタンがあるのだろうか……";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "……";
		mes "おっ!?";
		mes "これが、ボタンのようだな。";
		mes "押してみよう……";
		next;
		mes "‐ガラガラガチャン";
		mes "　パサッ";
		mes "　一枚の紙がでてきたようだ‐";
		next;
		mes "‐アンゴウハゼンブデミッツ";
		mes " スベテニュウリョクスルコトデ、";
		mes " ケンキュウホウコクショヲ";
		mes " テニイレルコトガデキマス‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		L_REP: //繰り返し場所おかしいが本鯖どおり。
		mes "どうやら三つの暗号があるらしい。";
		mes "暗号の場所も書かれているな。";
		mes "とりあえず一つ目から暗号を";
		mes "見に行ってみよう。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "一つ目の暗号のありかは……";
		mes "このマップの座標";
		mes "（ 284,354）だな。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐一つ目の暗号を調べる‐";
		mes " ";
		mes "‐^0000FFミュルニール山脈09（284,345）^000000‐";
		close2;
		viewpoint 1,284,345,20,0xFFFF00;
		set AC_RANKTEST,3;
		end;
	case 3:
		mes " ";goto L_REP;
	case 4://未調査
		mes "[" + strcharinfo(0) + "]";
		mes "どうやら三つの暗号があるらしい。";
		mes "暗号の場所も書かれているな。";
		mes "一つ目の暗号は";
		mes "^006600ホルン先生は男前^000000";
		mes "だったな。";
		mes "二つ目を調べに行こう。";
		next;
	case 5:
		mes "[" + strcharinfo(0) + "]";
		mes "どうやら三つの暗号があるらしい。";
		mes "暗号の場所も書かれているな。";
		mes "二つ目の暗号は";
		mes "^006600ホルン先生はお金持ち^000000";
		mes "だったな。";
		mes "三つ目を調べに行こう。";
		next;
	case 6:
		mes "[ホルンの研究ボックス]";
		mes " ";
		mes "‐一つ目の暗号を入力してください‐";
		next;
		input '@dummy$;
		if('@dummy$!="ホルン先生は男前") goto L_INPERR;
		mes "[ホルンの研究ボックス]";
		mes " ";
		mes "‐ニつ目の暗号を入力してください‐";
		next;
		input '@dummy$;
		if('@dummy$!="ホルン先生はお金持ち") goto L_INPERR;
		mes "[ホルンの研究ボックス]";
		mes " ";
		mes "‐三つ目の暗号を入力してください‐";
		next;
		input '@dummy$;
		if('@dummy$!="ホルン先生は大天才") goto L_INPERR;
		mes "‐ガラガラ……";
		mes "　ドンドンドン……";
		mes "　中から分厚いノートらしきものが";
		mes "　出てきた‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "研究報告書だ。";
		mes "無事に手に入れることができたな。";
		mes "冒険者アカデミーに戻ろう。";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐冒険者アカデミーにいる";
		mes "ガルドに、ホルンの研究書類を渡す‐";
		close2;
		set AC_RANKTEST,98;
		end;
	}
L_INPERR:
	mes "[ホルンの研究ボックス]";
	mes " ";
	mes "‐暗号が違います‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "暗号入力を";
	mes "間違えてしまったようだ。";
	mes "再度確認して入力しよう。";
	close;
}
mjolnir_09.gat,284,345,4	script	看板#ACTEST501	858,{
	if(AC_RANK!=4 || (AC_RANKTEST!=3 && AC_RANKTEST!=4)){
		mes "‐看板には";
		mes "　謎の言葉が書かれている‐";
		close;
	}
	if(AC_RANKTEST==4) goto L_REP;
	mes "‐看板には";
	mes "　^006600ホルン先生は男前^000000";
	mes "　と書かれている‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "それ以外なにも書かれていない。";
	mes "どうやらこれが暗号のようだ……";
	next;
	L_REP:
	mes "[" + strcharinfo(0) + "]";
	mes "^006600ホルン先生は男前^000000か……";
	mes "とりあえず、他の場所も見てみよう。";
	mes "次の座標は……";
	mes "（309.282）だな。";
	next; //ピリオドであってます・・・
	mes "^FF0000【ミッション】^000000";
	mes "‐二つ目の暗号を調べる‐";
	close2;
	viewpoint 1,309,282,20,0xFFFF00;
	set AC_RANKTEST,4;
	end;
}
mjolnir_09.gat,309,282,4	script	看板#ACTEST502	858,{
	if(AC_RANK!=4 || (AC_RANKTEST!=4 && AC_RANKTEST!=5)){
		mes "‐看板には";
		mes "　謎の言葉が書かれている‐";
		close;
	}
	if(AC_RANKTEST==5) goto L_REP;
	mes "‐看板には";
	mes "　^006600ホルン先生はお金持ち^000000";
	mes "　と書かれている‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "……";
	mes "どうやらこれが暗号のようだな。";
	next;
	L_REP:
	mes "[" + strcharinfo(0) + "]";
	mes "^006600ホルン先生はお金持ち^000000……";
	mes "後一箇所見てみよう。";
	mes "次の座標は……";
	mes "（100,310）だな。";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐三つ目の暗号を調べる‐";
	close2;
	viewpoint 1,100,310,20,0xFFFF00;
	set AC_RANKTEST,5;
	end;
}
mjolnir_09.gat,100,310,4	script	看板#ACTEST503	858,{
	if(AC_RANK!=4 || (AC_RANKTEST!=5 && AC_RANKTEST!=6)){
		mes "‐看板には";
		mes "　謎の言葉が書かれている‐";
		close;
	}
	if(AC_RANKTEST==6) goto L_REP;
	mes "‐看板には";
	mes "　^006600ホルン先生は大天才^000000";
	mes "　と書かれている‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "……";
	mes "どうやらこれが暗号のようだな。";
	next;
	L_REP:
	//未調査 ここ以下の記録が消失・・・とりあえず想像でごまかしときます。
	mes "[" + strcharinfo(0) + "]";
	mes "一つ目が、^006600ホルン先生は男前^000000、";
	mes "二つ目が、^006600ホルン先生はお金持ち^000000、";
	mes "三つ目は、^006600ホルン先生は大天才^000000か。";
	mes "どうやら暗号は揃ったようだ。";
	mes "研究ボックスに入力しに行こう。";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐^FF0000ホルンの研究ボックス^000000に戻り、";
	mes "三つの暗号を入力する。‐";
	close2;
	viewpoint 1,100,365,20,0xFFFF00;
	set AC_RANKTEST,6;
	end;
}
//第６課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00


pay_fild08.gat,167,332,4		script	#AC_HORONG	1129,{}
pay_fild08.gat,167,331,4		script	ホロン先生	111,{
	if(AC_RANK==5 && AC_RANKTEST==3){ mes "[ホロン先生]";goto L_REP; }
	emotion 2,"#AC_HORONG";
	mes "[ホロン先生]";
	mes "ふんふん～♪";
	mes "う～ん研究は難しいわね。";
	mes "でも、上手くいかないところが";
	mes "いいのよねぇ。";
	if(AC_RANK!=5 || AC_RANKTEST!=2)close;
	next;
	set '@dummy,select("ホルン先生!!");
	emotion 0,"#AC_HORONG";
	mes "[ホロン先生]";
	mes "!!!!?";
	mes "びっくりしたわ～。";
	mes "私に何かしら？";
	next;
	set '@dummy,select("ミルクを渡しに来ました。");
	emotion 1,"#AC_HORONG";
	mes "[ホロン先生]";
	mes "????";
	mes "え？";
	mes "ミルクをくれるの？";
	mes "でも、わたしミルクは苦手なのよね";
	mes "だから気持ちだけいただいておくわ。";
	mes "ありがとうね。";
	next;
	set '@dummy,select("試験中で受け取ってもらう必要が");
	emotion 0,"#AC_HORONG";
	mes "[ホロン先生]";
	mes "試験……？";
	mes "……";
	mes "もしかして第六試験かしら？";
	next;
	set '@dummy,select("そうです！");
	emotion 23,"";
	mes "[ホロン先生]";
	mes "それ、私じゃないわよ？";
	mes "貴方が探してるのは";
	mes "ホルン先生よね？";
	mes "私は^FF0000ホロン先生^000000よ？";
	mes "よく間違えられるのよね…";
	next;
	set '@dummy,select("ああーっ！ ごめんなさい……");
	mes "[ホロン先生]";
	mes "いえいえ、気にしないでくださいね。";
	mes "それよりも、^FF0000ホルン先生^000000っぽい姿を";
	mes "ついこの前見かけたのよね。";
	mes "何処だったかしら……";
	mes "ゲフェンから";
	mes "近い場所だったんだけど……";
	next;
	emotion 0,"#AC_HORONG";
	mes "[ホロン先生]";
	mes "あ！ そうだわ！";
	mes "確か、^0000FFミョルニール山脈06^000000！";
	mes "間違いないわ。";
	next;
	set '@dummy,select("ありがとうございます！");
	mes "[ホロン先生]";
	mes "いえ～。";
	L_REP:
	mes "ホルン先生って確証はないからね。";
	mes "でも、あの後ろ姿はホルン先生";
	mes "だったと思うわ。";
	mes "それじゃあ、試験頑張ってね。";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐^FF0000ホルン先生^000000を見つけ、ミルクを渡す‐";
	mes "‐^0000FFミョルニール山脈06^000000付近で";
	mes "　ホルン先生の後姿を見かけたとの";
	mes "　情報あり。";
	mes "　^0000FFミョルニール山脈06^000000へは";
	mes "　^0000FFゲフェン^000000から向かうと近い‐";
	close2;
	set AC_RANKTEST,3;
}
mjolnir_06.gat,226,183,4		script	#AC_BEETLE	1494,{}
mjolnir_06.gat,226,182,4		script	ビートル先生	111,{
	if(AC_RANK==5 && AC_RANKTEST==4) goto L_REP;
	emotion 39,"#AC_BEETLE";
	mes "[ビートル先生]";
	mes "樹液は最高ですなぁ……";
	mes "この絶妙な甘みがなんとも……";
	if(AC_RANK!=5 || AC_RANKTEST!=3) close;
	next;
	set '@dummy,select("ホルン先生？");
	emotion 57,"";
	mes "[ビートル先生]";
	mes "ん？";
	mes "私のことを呼んでいるのかね？";
	mes "僕はビートル先生なんだけども？";
	mes "彼とは後姿が似ているから";
	mes "よく間違われるのだよ。";
	next;
	set '@dummy,select("はぁ……、またか……");
	emotion 2,"#AC_BEETLE";
	mes "[ビートル先生]";
	mes "おやおや、";
	mes "相当落ち込んでいるようだが……";
	mes "どうしたんだい？";
	next;
	set '@dummy,select("事情を説明する");
	mes "[ビートル先生]";
	mes "なるほどなぁ……";
	mes "それは気の毒に。";
	mes "しかし、色々な困難に";
	mes "立ち向かえないと";
	mes "冒険者として生きていくのは";
	mes "むずかしい。";
	next;
	mes "[ビートル先生]";
	mes "だから、最後まで";
	mes "諦めてはいけないよ？";
	next;
	set '@dummy,select("ありがとうございます。");
	emotion 11,"#AC_BEETLE";
	mes "[ビートル先生]";
	mes "少し、元気が出てきたみたいだね！";
	mes "よし、君にとっておきの情報だ！";
	mes "実はホルン先生とついこの前";
	mes "実際にあったんだよ。";
	next;
	set '@dummy,select("何ですって!?");
	mes "[ビートル先生]";
	mes "彼は、モロクの潮風が自分の";
	mes "体にどういう影響を与えるのか";
	mes "っていうのを調べるとかで";
	mes "モロク付近の海岸に";
	mes "行くって言ってたな。";
	next;
	mes "[ビートル先生]";
	mes "モロク付近の海岸といえば";
	mes "いくつかの場所があるが……";
	mes "危険なモンスターが";
	mes "生息している場所がほとんど……";
	mes "彼の実力を考えると……";
	next;
	L_REP:
	mes "[ビートル先生]";
	mes "ホルン先生はおそらく";
	mes "^0000FFソグラト砂漠18^000000辺りに";
	mes "いるのではないかと思う。";
	mes "行ってみるといいよ。";
	next;
	mes "^FF0000【ミッション】^000000";
	mes "‐^FF0000ホルン先生^000000を見つけ、ミルクを渡す‐";
	mes "‐^FF0000ホルン先生^000000は";
	mes "　^0000FFソグラト砂漠 18^000000に向かった";
	mes "　との情報あり。";
	mes "　^0000FFソグラト砂漠 18^000000へは";
	mes "　^0000FFモロク^000000から向かうと近い‐";
	close2;
	set AC_RANKTEST,4;
}
moc_fild18.gat,211,95,4		script	#AC_HORN	1128,{}
moc_fild18.gat,211,94,4		script	？？？	111,{
	if(AC_RANK==5 && AC_RANKTEST==98) {
		mes "[ホルン先生]";
		mes "それじゃ、ホルンは";
		mes "研究を続けるから";
		mes "君は気をつけて帰ってくれ。";
		next; //なぜか大先生がつかない
		mes "^FF0000【ミッション】^000000";
		mes "‐冒険者アカデミーにいる";
		mes "ガルドに、報告する‐";
		close; //こっちは「ガルド」が黒になってるが本鯖どおり。
	}
	if(AC_RANK!=5 || AC_RANKTEST!=4){
		mes "[？？？]";
		mes "潮風が厳しいな……";
		close;
	}
	mes "[ホルン先生]";
	mes "ウググググ……";
	mes "く、くるしぃ";
	mes "潮風は体に悪いようだ……";
	mes "も、う、だめ、だ……";
	mes "ミルク……";
	next;
	if(countitem(519)==0){
		//未調査 すっかり忘れてた＞＜
		mes "[" + strcharinfo(0) + "]";
		mes "しまった。ミルクを忘れてしまった。";
		mes "早くしないとホルン先生が危ない。";
		mes "急いでミルクを持ってこよう！";
		next;
		mes "^FF0000【ミッション】^000000";
		mes "‐^FF0000ホルン先生^000000に、ミルクを渡す‐";
		close;
	}
	set '@dummy,select("ホルン先生！ミルクを！");
	emotion 0,"#AC_HORN";
	mes "[ホルン先生]";
	mes "ミルク！";
	mes "このにおいは、ミルク！";
	mes "き、き、君！";
	mes "早く私にそのミルクをくれ……";
	mes " ";
	mes "‐ホルン先生にミルクを手渡した‐";
	next;
	misceffect 77,"#AC_HORN";
	mes "[ホルン先生]";
	mes "ゴキュッ、ゴキュッ、ゴキュッ";
	mes "プハーーーーッ";
	mes "生き返ったーーーー!!";
	mes "いやー、砂漠、そして潮風";
	mes "この劣悪な環境で飲む";
	mes "一杯のミルクすばらしい！";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "……";
	next;
	mes "[ホルン先生]";
	mes "君！";
	mes "名前は？";
	next;
	set '@dummy,select("名乗る");
	mes "[ホルン先生]";
	mes strcharinfo(0) + "君！";
	mes "君は今凄い瞬間に立ちあったんだよ？";
	mes "もうちょっと感動しても";
	mes "いいんじゃないかな？";
	mes "むしろ感動するべきだよ！";
	next;
	set '@dummy,select("は、はあ……");
	emotion 54,"";
	mes "[ホルン先生]";
	mes "ふむ……";
	mes "君は、研究しているわけじゃないから";
	mes "わからなくても当然か……";
	mes "まあ、いつかこの感動が";
	mes "わかるようになるさ。";
	next;
	mes "[ホルン先生]";
	mes "すまない、まず先に言うことを";
	mes "忘れていたね。";
	mes "助けてくれてありがとう。";
	mes "君が通りかからなかったら";
	mes "本当に危なかった……";
	next;
	set '@dummy,select("実は……");
	mes "[ホルン先生]";
	mes "そういうことだったのか、";
	mes "君はアカデミーの生徒だったのか。";
	mes "……";
	mes "もしかして、研究報告書を";
	mes "届けてくれた人かな？";
	mes "名前が似ている気がするんだけど。";
	next;
	set '@dummy,select("はい");
	mes "[ホルン先生]";
	mes "おお！ やっぱりそうか！";
	mes "君には色々とお世話になってしまってるね。";
	mes "本当にありがとう。";
	mes "きっと君はすばらしい冒険者に";
	mes "なるに違いない。";
	next;
	mes "[ホルン先生]";
	mes "あ、これをガルドに渡せば";
	mes "ホルン大先生と会った";
	mes "証拠になるからね。";
	mes "それじゃ、ホルン大先生は";
	mes "研究を続けるから";
	mes "君は気をつけて帰ってくれ。";
	next;
	L_REP:
	mes "^FF0000【ミッション】^000000";
	mes "‐冒険者アカデミーにいる";
	mes "^FF0000ガルド^000000に、報告する‐";
	close2;
	delitem 519,1;
	set AC_RANKTEST,98;
	end;
}
//第７課程   --------------------------------------------------------

// ミニマップに地点表示(ID:20～) 黄色 0xFFFF00

// 2:ガルドから請け負った
// 3:ヤニクから水をもらう
// 4:盗賊に捕まる
// 5:荷物の場所を聞き出す
// 6:荷物を取り戻した
// 7:WP前自動会話
// 8:廃墟の写真を撮る
// 9:WP前自動会話
//10:ミシュラン先生に話しかける
//11:草を採る
//12:茂みからポリンが出る(省略可能)
//13:ミシュラン先生に魔法をかけてもらう
//14:WP前自動会話
//15:WP前自動会話
//16:プロ西入り口自動会話
//98:プロ内西口自動会話
//99:ガルドに報告完了
pay_gld.gat,273,307,4		script	行商人ヤニク	89,{
	if(AC_RANK!=6 || (AC_RANKTEST!=2 && AC_RANKTEST!=3)) {
		mes "[" + strcharinfo(0) + "]";
		mes "(忙しそうだ、";
		mes "話しかけるのはやめておこう。)";
		close;
	}
	if(AC_RANKTEST==3){
		mes "[行商人ヤニク]";
		mes "よお、君か。";
		mes "早く行ったほうがいいぜ？";
		close2;
		viewpoint 1,16,276,20,0xFFFF00;
		end;
	}
	mes "[行商人ヤニク]";
	mes "こんにちは。";
	next;
	set '@dummy,select("ガルドさんから言われてきました");
	mes "[行商人ヤニク]";
	mes "おうおう、ガルドとは懐かしい。";
	mes "奴は元気かい？";
	next;
	set '@dummy,select("元気ですよ");
	mes "[行商人ヤニク]";
	mes "それは、良かった。";
	mes "ところで、";
	mes "奴に言われてきたということは";
	mes "俺に何か用事があるんじゃないのか？";
	mes "何のようだろうか？";
	next;
	set '@dummy,select("水をいただきたい");
	mes "[行商人ヤニク]";
	mes "おうおう、ちょうど蒸留した水が";
	mes "一つあったんだよ。";
	mes "これをもっていくといい。";
	next;
	mes "[行商人ヤニク]";
	mes "そうだ、ここから西に行けば";
	mes "砂漠になるが、砂漠での水は";
	mes "凄く貴重なものになるからな。";
	mes "盗賊などが襲ってくるかも";
	mes "しれない。";
	mes "十分気をつけてな。";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "水を手に入れることができたな。";
	mes "先を急ごう。";
	close2;
	viewpoint 1,16,276,20,0xFFFF00;
	set AC_RANKTEST,3;
}
// 盗賊 話しかけた場合基本
function	script	盗賊FUNC#AC_TST07	{
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6){
		mes "[盗賊男]";
		mes "なんだお前？";
		mes " ";
		mes "‐男はじろじろとこちらを見ている‐";
		close;
	}
	mes "[盗賊男]";
	mes "この野郎！";
	mes "逃げ出しやがったな！";
	close2;
	if(AC_RANKTEST>5) set AC_RANKTEST,5;
	warp "moc_fild02.gat",153,312;
	end;
}
// 盗賊 OnTouch専用
function	script	盗賊FUNC2#AC_TST07	{
	if(AC_RANK!=6 || (AC_RANKTEST<4 && AC_RANKTEST>6)) end;
	mes "[盗賊男]";
	mes "貴様っ！";
	mes "逃げ出しやがったな！";
	close2;
	if(AC_RANKTEST>5) set AC_RANKTEST,5;
	warp "moc_fild02.gat",153,312;
	end;
}

//東WP前とおせんぼ3人組
moc_fild02.gat,370,272,4	script	盗賊男#AC_TST07_03	930,10,10,{
	callfunc "盗賊FUNC#AC_TST07";
OnTouch:
	if(AC_RANK!=6 || AC_RANKTEST<3 || AC_RANKTEST>6) end;
	if(AC_RANKTEST==3){
		mes "[盗賊男]";
		mes "ヘッヘッヘ。";
		mes "一人で俺らの縄張りを";
		mes "うろつくとは馬鹿な奴だ。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "な、何をするんだ……";
		mes "‐後ろから何かで殴られたようだ";
		mes "　意識が遠のいていく‐";
		close2;
		warp "moc_fild02.gat",153,312;
		end;
	}
	mes "[盗賊男]";
	mes "てめぇっ！";
	mes "どこから逃げ出しやがった！";
	close2;
	if(AC_RANKTEST>5) set AC_RANKTEST,5;
	warp "moc_fild02.gat",153,312;
	end;
}
moc_fild02.gat,373,278,4	script	盗賊男#AC_TST07_01	931,{
	callfunc "盗賊FUNC#AC_TST07";
}
moc_fild02.gat,370,279,4	script	盗賊女#AC_TST07_02	919,{
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6){
		mes "[盗賊女]";
		mes "なによアンタ。";
		mes " ";
		mes "‐女はじろじろとこちらを見ている‐";
		close;
	}
	mes "[盗賊女]";
	mes "この野郎！";
	mes "逃がさないよ！";
	close2;
	if(AC_RANKTEST>5) set AC_RANKTEST,5;
	warp "moc_fild02.gat",153,312;
	end;
}
//中州とおせんぼ
moc_fild02.gat,270,268,4	script	盗賊男#AC_TST07_04	930,3,5,{
	callfunc "盗賊FUNC#AC_TST07";
OnTouch:
	callfunc "盗賊FUNC2#AC_TST07";
}
//南西ルートとおせんぼ
moc_fild02.gat,91,98,4	duplicate(盗賊男#AC_TST07_04)	盗賊男#AC_TST07_05	930,5,10
//荷物ルートとおせんぼ
moc_fild02.gat,203,290,4	duplicate(盗賊男#AC_TST07_04)	盗賊男#AC_TST07_06	934,10,5

//北西ルートとおせんぼ
moc_fild02.gat,78,210,4		script	盗賊男#AC_TST07_07	930,10,5,{
	if(AC_RANK==6 && AC_RANKTEST==6){
		mes "[盗賊男]";
		mes "むにゃむにゃ……";
		close;
	}
	callfunc "盗賊FUNC#AC_TST07";
OnTouch:
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>5) end;
	callfunc "盗賊FUNC2#AC_TST07";
}

//捕まったときの場所（自動会話用）
moc_fild02.gat,153,312,0	script	#AC_TST07_08	139,3,3,{
OnTouch:
	if(AC_RANK!=6) end;
	switch(AC_RANKTEST){
	case 3:
		mes "[" + strcharinfo(0) + "]";
		mes "……";
		mes "…………";
		mes "(ここは何処だ……？)";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "(盗賊の姿が見えるな……";
		mes "気を失って、この場所に";
		mes "つれてこられたらしい。)";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "(……どうやら水と荷物を";
		mes "盗られてしまったようだ。)";
		next;
		set AC_RANKTEST,4;
	case 4:
		viewpoint 1,160,302,20,0xFFFF00;
		mes "[" + strcharinfo(0) + "]";
		mes "（^FF0000盗賊に見つからないように";
		mes "移動して、荷物のありかを探そう！^000000）";
		close;
	case 5:
		viewpoint 1,234,314,20,0xFFFF00;
		mes "[" + strcharinfo(0) + "]";
		mes "（捕まってしまった……";
		mes "盗賊に見つからないように、";
		mes "^0000FFソグラト砂漠02(234,314)付近^000000";
		mes "に移動し、荷物をとりかえそう！）";
		close;
	}
	end;
}
//盗み聞き自動会話
moc_fild02.gat,147,302,0	script	#AC_TST07_09	139,5,5,{
OnTouch:
	if(AC_RANK!=6 || AC_RANKTEST!=4) end;
	viewpoint 1,160,302,20,0xFFFF00;
	mes "[" + strcharinfo(0) + "]";
	mes "（すぐ南東の方から声がする……";
	mes "南東の方にいってみよう。）";
	close;
}

//おかしらに話しかけてる人
moc_fild02.gat,163,294,7	script	盗賊男#AC_TST07_11	943,9,9,{
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6){
		mes "[" + strnpcinfo(1) + "]";
		mes "なんだお前？";
		mes " ";
		mes "‐男はじろじろとこちらを見ている‐";
		close;
	}
	mes "‐" + strnpcinfo(1) + "はよだれを垂らして、";
	mes "ぼけーっとしている‐";
	close;
OnTouch:
	if(AC_RANK!=6 || (AC_RANKTEST!=4 && AC_RANKTEST!=5)) end;
	switch(AC_RANKTEST){
	case 4:
		mes "[" + strcharinfo(0) + "]";
		mes "(盗賊の話し声がする、";
		mes "ここに隠れよう……)";
		mes " ";
		mes "‐" + strcharinfo(0) + "は";
		mes "木の裏に隠れた‐";
		next;
		mes "[盗賊男]";
		mes "おかしらぁー、馬鹿な冒険者が";
		mes "水をもっていやがりやして";
		mes "うばってやりやした。";
		next;
		mes "[おかしら]";
		mes "おうおう！";
		mes "水とはまた高価なものを";
		mes "もっていたじゃねーか。";
		mes "そんで、その水は何処にあるんだ？";
		next;
		mes "[盗賊男]";
		mes "へっへっへ。";
		mes "水なら^0000FFソグラト砂漠02(234,314)^000000";
		mes "付近に隠してありやす。";
		mes "もちろん見張りもつけて";
		mes "ありやすから安心ですぜ。";
		next;
		mes "[おかしら]";
		mes "そいつぁでかした！";
		mes "よし、今夜は皆で";
		mes "騒ごうじゃないか！";
		mes "へっへっへ……";
		mes " ";
		mes "‐おかしらはよだれを垂らしている‐";
		next;
		mes "[盗賊男]";
		mes "そうでやすね！";
		mes "へっへっへ……";
		mes " ";
		mes "‐盗賊男はよだれを垂らしている‐";
		close2;
		viewpoint 1,234,314,20,0xFFFF00;
		set AC_RANKTEST,5;
		end;
	case 5:
		mes "[おかしら]";
		mes "おっと、そういえば……";
		mes "えーっと……";
		mes "あれ？";
		mes "水は何処に隠してあるんだ？";
		next;
		mes "[盗賊男]";
		mes "やだなぁ、おかしら！";
		mes "隠し場所は、";
		mes "^0000FFソグラト砂漠02(234,314)^000000";
		mes "付近でありやす。";
		next;
		mes "[おかしら]";
		mes "そうか！";
		mes "早くうっぱらって金に";
		mes "しないとなぁ。";
		mes "へっへっへ……";
		mes " ";
		mes "‐おかしらはよだれを垂らしている‐";
		next;
		mes "[盗賊男]";
		mes "そうでやすね！";
		mes "へっへっへ……";
		mes " ";
		mes "‐盗賊男はよだれを垂らしている‐";
		close2;
		viewpoint 1,234,314,20,0xFFFF00;
		end;
	}
}
moc_fild02.gat,165,294,4	duplicate(盗賊男#AC_TST07_11)	おかしら#AC_TST07_12	939

function	script	盗賊FUNC3#AC_TST07	{
	mes "[盗賊男]";
	mes "何をしとるんじゃ！";
	mes "あの警備網をかいくぐるとは……";
	mes "なかなかやりおるわい。";
	mes "しかぁしっ！ わしの目が黒いうちは、";
	mes "荷物には指一本ふれさせん！";
	close2;
	if(AC_RANKTEST>5) set AC_RANKTEST,5;
	warp "moc_fild02.gat",153,312;
	end;
}

moc_fild02.gat,234,314,4	script	盗賊男#荷物番	945,5,5,{
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6) end; //メッセージなしで本鯖どおり
	if(getvariableofnpc('flag,"荷物#AC_TST07")<3){
		mes "[盗賊男]";
		mes "ムニャムニャ……";
		mes "Zzzzz";
		next;
		if(AC_RANKTEST==6){
			mes "[" + strcharinfo(0) + "]";
			mes "荷物は取り戻したな……";
			mes "盗賊に見つからないように、";
			mes "次の場所に向かおう……";
			close2;
			viewpoint 1,80,342,20,0xFFFF00;
			end;
		}
		mes "[" + strcharinfo(0) + "]";
		mes "眠っている";
		mes "今ならばれずに";
		mes "水と荷物を取り返せそうだ。";
		close;
	}
OnTouch:
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6 || getvariableofnpc('flag,"荷物#AC_TST07")<3) end;
	callfunc "盗賊FUNC3#AC_TST07";
}
moc_fild02.gat,234,313,4	script	荷物#AC_TST07	111,{
	if(AC_RANK!=6 || (AC_RANKTEST!=5 && AC_RANKTEST!=6)){
		mes "‐たくさんの荷物が置いてある……‐";
		close;
	}
	if(AC_RANKTEST==6){
		mes "[" + strcharinfo(0) + "]";
		mes "荷物は取り戻したな……";
		mes "盗賊に見つからないように、";
		mes "次の場所に向かおう……";
		close2;
		viewpoint 1,80,342,20,0xFFFF00;
		end;
	}
	if('flag<3){
		mes "‐奪われた荷物と水を発見した‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "よし、盗賊に見つからないよう";
		mes "次の場所に向かおう……";
		close2;
		viewpoint 1,80,342,20,0xFFFF00;
		set AC_RANKTEST,6;
		end;
	}
	callfunc "盗賊FUNC3#AC_TST07";
	end;
OnInit:
OnTimer3000:
	switch('flag){
		case 0: misceffect 197,"盗賊男#荷物番"; break;
		case 1: misceffect 197,"盗賊男#荷物番"; break;
		case 2: misceffect 197,"盗賊男#荷物番"; break;
		case 3: emotion 23,"盗賊男#荷物番"; break;
		case 4: emotion 20,"盗賊男#荷物番"; break;
		case 5: emotion  9,"盗賊男#荷物番"; break;
		case 6: emotion 45,"盗賊男#荷物番"; break;
	}
	set 'flag,('flag<6)*('flag+1);
	initnpctimer;
}
moc_fild02.gat,67,337,0		script	#AC_TST07_13	139,11,5,{
OnTouch:
	if(AC_RANK!=6 || AC_RANKTEST<4 || AC_RANKTEST>6) end;
	if(AC_RANKTEST==6){
		mes "[" + strcharinfo(0) + "]";
		mes "いろいろあったけど、";
		mes "ここまで来ることができた……";
		mes "先を急がなくては……";
		close2;
		set AC_RANKTEST,7;
		end;
	}
	mes "[" + strcharinfo(0) + "]";
	mes "戻って、荷物を取り返さないと……";
	close2;
	if(AC_RANKTEST==3 || AC_RANKTEST==4)
		viewpoint 1,163,294,20,0xFFFF00;
	else
		viewpoint 1,234,314,20,0xFFFF00;
	end;
}
moc_fild02.gat,92,337,0		duplicate(#AC_TST07_13)	#AC_TST07_14	139,11,5

moc_fild01.gat,190,38,0		script	#AC_TSTVP7_15	139,8,8,{
	if(AC_RANK!=6 || (AC_RANKTEST!=7 && AC_RANKTEST!=8)) end;
	if(AC_RANKTEST==8){
		mes "[" + strcharinfo(0) + "]";
		mes "既に撮影は終了したな。";
		mes "先を急ごう。";
		close2;
		viewpoint 1,22,242,20,0xFFFF00;
		end;
	}
	mes "[" + strcharinfo(0) + "]";
	mes "撮影するのはここで間違いなさそうだ。";
	next;
	mes "‐風景を撮影した‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "上手く撮れたようだな。";
	mes "先を急ごう。";
	close2;
	set AC_RANKTEST,8;
	viewpoint 1,22,242,20,0xFFFF00;
	end;
}
moc_fild01.gat,28,242,0		script	#AC_TSTVP7_16	139,5,2,{
	if(AC_RANK!=6 || (AC_RANKTEST!=7 && AC_RANKTEST!=8)) end;
	if(AC_RANKTEST==7){
		mes "[" + strcharinfo(0) + "]";
		mes "撮影をしなくちゃ。";
		close2;
		viewpoint 1,190,38,20,0xFFFF00;
		end;
	}
	mes "[" + strcharinfo(0) + "]";
	mes "また緑が見えてきた。";
	mes "ようやく砂漠を越えられるのだろうか？";
	close2;
	set AC_RANKTEST,9;
	end;
}
prt_fild09.gat,304,193,4	script	ミシュラン先生	101,{
	if(AC_RANK!=6 || AC_RANKTEST<9 || AC_RANKTEST>13) {
		mes "[ミシュラン先生]";
		mes "こんにちは。";
		close;
	}
	switch(AC_RANKTEST){
	case 9:
		emotion 1;
		mes "[ミシュラン先生]";
		mes "こんにちは。";
		mes "何か私に用かしら？";
		next;
		set '@dummy,select("事情を説明する");
	case 10:
		emotion 33;
		mes "[ミシュラン先生]";
		mes "魔法のかかった草が必要なのね。";
		mes "だったらこのマップに生えている";
		mes "^FF0000草^000000をとってきてくれる？";
		mes "そうしたらそれに魔法を";
		mes "かけてあげるから。";
		next;
		viewpoint 1,39,255,21,0xFFFF00;
		mes "[ミシュラン先生]";
		mes "詳しい場所なんだけどね、";
		mes "（39,255）付近だったかな？";
		mes "うん、このあたりに生えているはず。";
		mes "それじゃ行ってらっしゃいね。";
		close2;
		set AC_RANKTEST,10;
		end;
	case 11:
	case 12:
		misceffect 17;
		mes "[ミシュラン先生]";
		mes "お帰りなさい！";
		mes "無事に草をとってきたようね。";
		mes "それじゃ、早速魔法をかけるわ。";
		next;
		mes "[ミシュラン先生]";
		mes "うまくいったわ。";
		mes "それじゃ";
		mes "試験の続きがんばってねー。";
		next;
		mes "‐ミシュランから";
		mes "　魔法のかかった草を受け取った‐";
		next;
		mes "[ミシュラン先生]";
		mes "ゴールまでもう少しだけど、";
		mes "気をゆるめちゃだめだよ。";
		close2;
		set AC_RANKTEST,13;
		viewpoint 1,224,380,20,0xFFFF00;
		end;
	case 13:
		mes "[ミシュラン先生]";
		mes "試験の続きがんばってねー。";
		close2;
		viewpoint 1,224,380,20,0xFFFF00;
		end;
	}
}
prt_fild09.gat,39,255,0		script	#AC_TSTVP7_17	1080,{}
prt_fild09.gat,39,254,0		script	草#AC_TSTVP7_18	111,{
	mes "‐草が生えている‐";
	if(AC_RANK!=6 || AC_RANKTEST!=10) close;
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "この草で問題ないようだ。";
	mes "もっていこう。";
	next;
	mes "‐草を手に入れた‐";
	close2;
	viewpoint 1,304,193,20,0xFFFF00;
	set AC_RANKTEST,11;
	end;
}
prt_fild09.gat,227,368,0		script	#AC_TSTVP7_19	139,7,7,{
	if(AC_RANK!=6 || AC_RANKTEST<9 || AC_RANKTEST>13) end;
	if(AC_RANKTEST!=13){
		mes "[" + strcharinfo(0) + "]";
		mes "魔法のかかった草を";
		mes "手に入れないとな。";
		close2;
		if(AC_RANKTEST==9 || AC_RANKTEST>=11)
			viewpoint 1,304,193,20,0xFFFF00; //ミシュラン先生
		else
			viewpoint 1,39,255,21,0xFFFF00; //草
		end;
	}
	mes "[" + strcharinfo(0) + "]";
	mes "プロンテラまであと少しだ。";
	mes "がんばろう！";
	close2;
	set AC_RANKTEST,14;
	end;
}
prt_fild09.gat,50,260,0		script	#AC_TSTVP7_20	139,10,10,{
	if(AC_RANK!=6 || AC_RANKTEST!=11) end;
	mes "‐茂みから音が聞こえる……‐";
	next;
	mes "‐茂みからモンスターが現れた！‐";
	close2;
	set '@dummy, getmapxy('@dummy$,'@x,'@y,0);
	areamonster "prt_fild09.gat",'@x-3,'@y-3,'@x +3,'@y+3,"--ja--",1002,3;
	set AC_RANKTEST,12;
	end;
}
prt_fild07.gat,248,370,0	script	#AC_TSTVP7_21	139,5,5,{
	if(AC_RANK!=6 || AC_RANKTEST!=14) end;
	mes "[" + strcharinfo(0) + "]";
	mes "確かこの先がプロンテラの西側だった";
	mes "気がする。";
	mes "あと少しだ！";
	close2;
	set AC_RANKTEST,15;
	end;
}

// ミニマップ表示処理のところに移動。
//prt_fild05.gat,367,205,0	script	#AC_TSTVP7_22	139,5,5,{ //プロ西入り口手前
//	if(AC_RANK!=6 || AC_RANKTEST!=15) end;
//	mes "[" + strcharinfo(0) + "]";
//	mes "プロンテラが見える。";
//	mes "あと少しだ！";
//	close2;
//	set AC_RANKTEST,16;
//	end;
//}

// 未調査。 通ろうとすると追い返すらしい。
prt_fild05.gat,371,123,4	script	ガラの悪そうな男	943,{
	mes "[ガラの悪そうな男]";
	mes "ぐおー。";
	mes "ぐおー。";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "（男が寝ているようだ。）";
	close;
}

prontera.gat,26,203,0	script	#AC_TSTVP7_22	139,5,5,{ //プロ到着
	if(AC_RANK!=6 || AC_RANKTEST!=16) end;
	mes "[" + strcharinfo(0) + "]";
	mes "プロンテラに到着した！";
	mes "後は、ガルドさんに報告";
	mes "すれば試験完了だ！";
	close2;
	set AC_RANKTEST,98;
	end;
}
