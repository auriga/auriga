//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Labyrinth Quest Script	by refis
//= Registry ===================================================================
// IL_MAZE_QUE -> 0～8
//==============================================================================

prt_maze01.gat,91,22,4	script	怪しい小道#ILU_001	10042,{
	mes "‐怪しい雰囲気の漂う小道がある‐";
	mes "　微かに赤く光っている‐";
	next;
	if(select("小道へ入る","無視する") == 2) {
		mes "‐その場を去った‐";
		close;
	}
	if(BaseLevel < 170) {
		mes "^ff0000【インフォメーション】";
		mes "クエスト「新人アコライトの幽霊」は";
		mes "BaseLv170以上で進行可能です。^000000";
		close;
	}
	mes "‐怪しい雰囲気の漂う小道を進んだ‐";
	if(IL_MAZE_QUE == 0) {
		setquest 12481;
		set IL_MAZE_QUE,1;
	}
	close2;
	if(IL_MAZE_QUE == 8)
		warp "prt_mz01_i.gat",102,21;
	else
		warp "prt_mz01_q.gat",102,21;
	end;
}

prt_mz01_q.gat,103,22,0	script	#ilmaze000	139,10,10,{
	switch(IL_MAZE_QUE) {
	case 1:
	case 2:
		cloakoffnpc "歪んだ裂け目#1";
		misceffect 513,"歪んだ裂け目#1";
		misceffect 74,"歪んだ裂け目#1";
		cloakoffnpc "イレーネ#1";
		cloakonnpc "エスメラルダ#1";
		cloakonnpc "アンドレア#1";
		cloakonnpc "アネス#1";
		cloakonnpc "シルバノ#1";
		cloakonnpc "セリシア#1";
		end;
	case 3:
		cloakoffnpc "歪んだ裂け目#1";
		misceffect 513,"歪んだ裂け目#1";
		misceffect 74,"歪んだ裂け目#1";
		cloakoffnpc "イレーネ#1";
		cloakoffnpc "エスメラルダ#1";
		cloakonnpc "アンドレア#1";
		cloakonnpc "アネス#1";
		cloakonnpc "シルバノ#1";
		cloakonnpc "セリシア#1";
		end;
	case 4:
	case 5:
		cloakoffnpc "歪んだ裂け目#1";
		misceffect 513,"歪んだ裂け目#1";
		misceffect 74,"歪んだ裂け目#1";
		cloakonnpc "イレーネ#1";
		cloakoffnpc "エスメラルダ#1";
		cloakonnpc "アンドレア#1";
		cloakonnpc "アネス#1";
		cloakonnpc "シルバノ#1";
		cloakonnpc "セリシア#1";
		end;
	case 6:
	case 7:
		cloakoffnpc "歪んだ裂け目#1";
		misceffect 513,"歪んだ裂け目#1";
		misceffect 74,"歪んだ裂け目#1";
		cloakonnpc "イレーネ#1";
		cloakonnpc "エスメラルダ#1";
		cloakoffnpc "アンドレア#1";
		cloakoffnpc "アネス#1";
		cloakoffnpc "シルバノ#1";
		cloakoffnpc "セリシア#1";
		end;
	}
}

prt_mz01_q.gat,108,22,5	script	歪んだ裂け目#1	844,{
	switch(IL_MAZE_QUE) {
	case 3:
	case 5:
		mes "-エスメラルダに話しかけよう-";
		close;
	case 4:
		mes "‐歪んだ裂け目の向こうに、";
		mes "　見慣れているようで";
		mes "　馴染みの無い迷宮の姿が広がっている‐";
		next;
		if(select("裂け目の向こうへ行く","見なかったことにする") == 2) {
			mes "^0000ff‐好奇心は猫をも殺すという。";
			mes "　静かに引き返そう‐^000000";
			close;
		}
		mes "-裂け目の向こうへ進んだ-";
		close2;
		warp "prt_mz03_q.gat",107,102;
		end;
	case 6:
		mes "‐アンドレアに話しかけよう‐";
		close;
	case 7:
		mes "‐迷宮の外でエスメラルダを探そう‐";
		close;
	}
	mes "‐歪んだ裂け目の向こうに、";
	mes "　見慣れているようで";
	mes "　馴染みの無い迷宮の姿が広がっている‐";
	close;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,99,24,5	script	イレーネ#1	10337,10,10,{
	switch(IL_MAZE_QUE) {
	case 1:
		mes "[イレーネ]";
		mes "きゃあ！";
		mes "すみません。わたくし幽霊じゃありません。";
		mes "モンスターでもないです!!";
		mes "驚かせるつもりじゃなかったんです！";
		next;
		mes "[イレーネ]";
		mes "どうかその武器を収めて、";
		mes "話を聞いてください。お願いします！";
		next;
		menu "わかりました。",-;
		mes "[イレーネ]";
		mes "ありがとうございます。";
		mes "わたくしはプロンテラの";
		mes "司祭ギルドに所属している";
		mes "イレーネと申します。";
		mes "あ……今のこの姿には";
		mes "ちょっと事情がありまして……。";
		next;
		menu "事情？",-;
		mes "[イレーネ]";
		mes "はい……。";
		mes "実は狩りの途中で";
		mes "やられてしまいまして……。";
		next;
		mes "[イレーネ]";
		mes "4人の新人のギルド員と一緒に";
		mes "修行する場所を探している途中、";
		mes "そこの怪しい裂け目を発見したのですが、";
		mes "新人たちが勢いのまま入ってしまい、";
		mes "それを追って行ったら全員……。";
		next;
		mes "[イレーネ]";
		mes "お願いします。";
		mes "このことをギルド長に伝えてください。";
		mes "プロンテラ大聖堂の近くで";
		mes "ギルド員の募集活動を";
		mes "している^ff0000エスメラルダ^000000という女性です。";
		next;
		mes "[イレーネ]";
		mes "わたくしはここで";
		mes "新人の誰かが運よく生き残って";
		mes "戻って来ないか、";
		mes "待たなければいけませんので……。";
		next;
		if(select("わかりました","断る") == 2) {
			mes "[イレーネ]";
			mes "やはり、無理なお願いだったのですね……。";
			close;
		}
		mes "[イレーネ]";
		mes "ありがとうございます！";
		mes "ギルド長の位置のメモはお渡します！";
		mes "どうかお願いします！";
		next;
		if(select("プロンテラへ向かう","とどまる") == 2) {
			mes "‐プロンテラに戻る前に";
			mes "　もう少し辺りを確認しよう‐";
			chgquest 12481,12482;
			set IL_MAZE_QUE,2;
			close;
		}
		mes "‐あなたはプロンテラに向かった‐";
		chgquest 12481,12482;
		set IL_MAZE_QUE,2;
		close2;
		warp "prontera.gat",212,318;
		end;
	case 2:
		mes "[イレーネ]";
		mes "お願いします。";
		mes "このことをギルド長に伝えてください。";
		mes "プロンテラ大聖堂の近くで";
		mes "ギルド員の募集活動を";
		mes "している^ff0000エスメラルダ^000000という女性です。";
		next;
		if(select("プロンテラへ向かう","とどまる") == 2) {
			mes "‐プロンテラに戻る前に";
			mes "　もう少し辺りを確認しよう‐";
			close;
		}
		mes "‐あなたはプロンテラに向かった‐";
		close2;
		warp "prontera.gat",212,318;
		end;
	case 3:
		mes "[イレーネ]";
		mes "うう、わたくしの亡骸は";
		mes "もう痕跡も残っていないみたいです……。";
		next;
		mes "[エスメラルダ]";
		mes "まあ、幸い守護聖物はギルドに";
		mes "保管してあるから、";
		mes "復活はなんとかなるでしょう。";
		mes "ちょっとお金はかかるけどね。";
		next;
		mes "[イレーネ]";
		mes "ごめんなさいぃぃ……。";
		close;
	case 4:
		mes "[イレーネ]";
		mes "わたくしはそろそろギルドへ戻りますね。";
		mes "幽霊のままでかなり恥ずかしいですが……。";
		close2;
		cloakonnpc "イレーネ#1";
		end;
	}
	end;
OnTouch:
	if(IL_MAZE_QUE == 1)
		unittalk "イレーネ : きゃあ！　すみません。わたくし幽霊じゃありません。モンスターでもないです!!";
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,105,24,3	script	エスメラルダ#1	677,{
	switch(IL_MAZE_QUE) {
	case 3:
		mes "[エスメラルダ]";
		mes "イレーネ！";
		mes "泣いてばかりいないで、";
		mes "しっかりしなさい！";
		next;
		mes "[エスメラルダ]";
		mes "幸い守護聖物はギルドに";
		mes "保管してあるから、";
		mes "復活はなんとかなるでしょう。";
		mes "ちょっとお金はかかるけどね。";
		next;
		mes "[イレーネ]";
		mes "ごめんなさいぃぃ……。";
		next;
		mes "[エスメラルダ]";
		mes "この問題児は";
		mes "急いで復活させる必要があるので、";
		mes "一旦ギルドへ帰らせます。";
		next;
		mes "[エスメラルダ]";
		mes "本当に感謝いたします。";
		mes "厚かましいとは思いますが、";
		mes "もう一つお願いをしても";
		mes "よろしいでしょうか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[エスメラルダ]";
			mes "あ、そうですよね……。";
			mes "申し訳ありませんでした……。";
			mes "後は私たちでどうにかします。";
			close;
		}
		mes "[エスメラルダ]";
		mes "ありがとうございます。";
		next;
		mes "[エスメラルダ]";
		mes "イレーネは昔、";
		mes "守護聖物と魂の契約をしたので、";
		mes "復活に問題はなさそうですが、";
		mes "行方不明の新人4人は";
		mes "そうではありません。";
		next;
		mes "[エスメラルダ]";
		mes "彼らはまだ守護聖物との契約を";
		mes "していなかったので、";
		mes "幽霊の姿にもなれないのです。";
		mes "はぁ……困りましたね……。";
		next;
		menu "守護聖物との契約？",-;
		mes "[エスメラルダ]";
		mes "守護聖物との契約とは";
		mes "保険のようなものです。";
		mes "契約の儀式を行うと、";
		mes "死亡しても魂と肉体が完全に";
		mes "復活することができるのです。";
		next;
		mes "[エスメラルダ]";
		mes "私たちのギルドは";
		mes "聖職者のみで構成されたギルドなので、";
		mes "死亡事故が少ないと思われるでしょうが、";
		mes "意外にも頻繁に起きています。";
		next;
		mes "[エスメラルダ]";
		mes "契約の儀式はギルド入団と同時に";
		mes "行うようにしていたのですが、";
		mes "今回の4人はその契約がまだだったので、";
		mes "このままでは復活できません。";
		next;
		mes "[エスメラルダ]";
		mes "小さな一部だけでいいので、";
		mes "遺体が必要なのです。";
		mes "まるごとあれば費用は安くなりますが、";
		mes "今は復活させるのが優先ですから。";
		next;
		mes "[エスメラルダ]";
		mes "4人はこの歪んだ裂け目の";
		mes "向こう側にいるはずです。";
		mes "これは4人の情報をまとめたものです。";
		mes "遺体の一部や痕跡を見つけたら、";
		mes "この情報と照合してください。";
		close2;
		delquest 12483;
		setquest 12479;
		setquest 12484;
		setquest 12485;
		setquest 12486;
		setquest 12487;
		set IL_MAZE_QUE,4;
		end;
	case 4:
		mes "[エスメラルダ]";
		mes "4人はこの歪んだ裂け目の";
		mes "向こう側にいるはずです。";
		mes "これは4人の情報をまとめたものです。";
		mes "遺体の一部や痕跡を見つけたら、";
		mes "この情報と照合してください。";
		close;
	case 5:
		mes "[エスメラルダ]";
		mes "ああ……";
		mes "諦めかけていたのに、";
		mes "本当に全員を見つけて来て";
		mes "くださいましたね。";
		mes "本当にありがとうございます。";
		next;
		mes "[エスメラルダ]";
		mes "一旦、彼らの魂を呼び出してみます。";
		mes "魂だけの復活ですから、プロンテラよりも";
		mes "ここで魂を呼び出した方が";
		mes "良いでしょう。";
		mes "町中に幽霊が現れたりしたら、";
		mes "混乱しそうですからね。";
		next;
		mes "[エスメラルダ]";
		mes "それから、申し訳ありません。";
		mes "魂の復活はギルド員以外には";
		mes "お見せできないのです。";
		mes "しばらくの間、外でお待ちいただけますか？";
		next;
		menu "はい",-;
		mes "[エスメラルダ]";
		mes "ご配慮ありがとうございます。";
		mes "少ししたら、";
		mes "またこちらにいらしてください。";
		mes "では外までお送りいたします。";
		chgquest 12488,12489;
		set IL_MAZE_QUE,6;
		close2;
		warp "prt_fild01.gat",136,365;
		end;
	case 6:
		mes "[エスメラルダ]";
		mes "ご配慮ありがとうございます。";
		mes "少ししたら、";
		mes "またこちらにいらしてください。";
		mes "では外までお送りいたします。";
		close2;
		warp "prt_fild01.gat",136,365;
		end;
	}
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,111,20,1	script	セリシア#1	10316,{
	if(IL_MAZE_QUE == 7) {
		mes "[セリシア]";
		mes "私にできることはありますか？";
		next;
		if(select("特にない","外へ送ってもらう") == 1) {
			mes "[セリシア]";
			mes "お力になれず、申し訳ありません。";
			close;
		}
		mes "[セリシア]";
		mes "わかりました。";
		close2;
		warp "prt_fild01.gat",136,365;
		end;
	}
	mes "[セリシア]";
	mes "私たちはみんな ";
	mes strcharinfo(0)+"様に";
	mes "感謝しております。";
	mes "またギルド長が";
	mes "^0000ffアンドレア^000000に";
	mes "伝言を残しています。";
	close;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,105,24,5	script	アンドレア#1	10310,{
	if(IL_MAZE_QUE < 6)
		end;
	if(IL_MAZE_QUE == 7) {
		mes "[アンドレア]";
		mes "ギルド長が戻ってきたようですね。";
		mes "迷宮の入り口を見て来てもらえますか？";
		next;
		mes "‐迷宮の入り口に向かおう‐";
		close2;
		warp "prt_fild01.gat",141,365;
		end;
	}
	mes "[アンドレア]";
	mes "ギルド長のエスメラルダから";
	mes "話は伺いました。";
	mes "僕たちを救ってくださった方ですよね。";
	next;
	menu "大袈裟です。",-;
	mes "[アンドレア]";
	mes "またまた、そんなご謙遜を。";
	mes strcharinfo(0)+"様が";
	mes "助けてくださらなければ、";
	mes "あのまま帰ってこれないところでした。";
	mes "本当にありがとうございます。";
	next;
	menu "エスメラルダさんはどこに？",-;
	mes "[アンドレア]";
	mes "あ、ギルド長は、";
	mes "いくつか準備するものがあって、";
	mes "一旦ギルド駐屯地に戻りました。";
	mes "またここの迷宮の入口に";
	mes "すぐに戻るらしいです。";
	next;
	mes "[アンドレア]";
	mes "そして"+strcharinfo(0)+"様が";
	mes "僕たちのギルドの客員として";
	mes "ご活動していただけないか、";
	mes "うかがえと言われています。";
	next;
	mes "[アンドレア]";
	mes "実際に活動する立場の僕たちが、";
	mes "こんな有り様で、";
	mes "復活のための資金を用意する人手が";
	mes "足りない状況なのです。";
	next;
	mes "[アンドレア]";
	mes "新しく発見されたこの歪んだ迷宮を";
	mes "攻略できれば、僕たちのギルドを";
	mes "建て直すきっかけになるでしょう。";
	mes "そしてそれを信じて頼める冒険者は";
	mes strcharinfo(0)+"様だけです。";
	next;
	mes "[アンドレア]";
	mes "僕たちは魂の状態ではあるものの、";
	mes "この歪んだ迷宮の中を彷徨いながら";
	mes "様々な体験をしています。";
	next;
	mes "[アンドレア]";
	mes "僕たちはこの迷宮のモンスターの";
	mes "情報を提供します。";
	mes strcharinfo(0)+"様には";
	mes "その^ff0000モンスター達を";
	mes "退治して来て欲しい^000000のです。";
	next;
	mes "[アンドレア]";
	mes strcharinfo(0)+"様、";
	mes "どうか僕たちのギルドの客員として";
	mes "力を貸していただけませんか？";
	next;
	if(select("力を貸す","やめる") == 2) {
		mes "[アンドレア]";
		mes "確かに……そうですね。";
		mes "ちょっと無理なお願いだったようです。";
		close;
	}
	mes "[アンドレア]";
	mes "本当ですか！";
	mes "ありがとうございます。";
	mes "僕がギルドを代表して、";
	mes strcharinfo(0)+"様に";
	mes "この歪んだ迷宮に関する";
	mes "依頼を出します。";
	next;
	mes "[アンドレア]";
	mes "報告と報酬に関しては、";
	mes "^0000FFシルバノ^000000が担当いたします。";
	mes "依頼が完了したら、";
	mes "彼に報告してください。";
	next;
	mes "[アンドレア]";
	mes "ん？　どうやら";
	mes "ギルド長が戻ってきたようですね。";
	mes "迷宮の入り口を見て来てもらえますか？";
	next;
	mes "‐迷宮の入り口に向かおう‐";
	delquest 12489;
	setquest 12492;
	set IL_MAZE_QUE,7;
	close2;
	warp "prt_fild01.gat",141,365;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,105,20,7	script	アネス#1	10312,{
	mes "[アネス]";
	mes "あたしたちはみんな";
	mes strcharinfo(0)+"様に";
	mes "感謝しています。";
	if(IL_MAZE_QUE == 6) {
		mes "そしてギルド長が";
		mes "^0000ffアンドレア^000000に";
		mes "伝言を残しています。";
	}
	close;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_q.gat,111,24,3	script	シルバノ#1	10314,{
	mes "[シルバノ]";
	mes "俺たちはみんな";
	mes strcharinfo(0)+"様に";
	mes "感謝しています。";
	if(IL_MAZE_QUE == 6) {
		mes "そしてギルド長が";
		mes "^0000ffアンドレア^000000に伝言を残しています。";
		mes "詳しくは彼から聞いてください。";
	}
	close;
OnInit:
	cloakonnpc;
	end;
}

prontera.gat,212,320,0	script	#ilmaze002	139,10,10,{
	if(IL_MAZE_QUE == 2) {
		cloakoffnpc "エスメラルダ#2";
		end;
	}
	cloakonnpc "エスメラルダ#2";
	end;
}

prontera.gat,212,320,3	script	エスメラルダ#2	677,6,6,{
	switch(IL_MAZE_QUE) {
	case 2:
		mes "[エスメラルダ]";
		mes "うん？";
		mes "どうかなさいましたか？";
		mes "私たちのギルドに興味があるのですか？";
		next;
		menu "イレーネのことを伝える",-;
		mes "[エスメラルダ]";
		mes "新人たちが行方不明ですか？";
		mes "はぁ……";
		mes "ギルドの伝統なのでしょうか……。";
		mes "毎年恒例の事件ですね。";
		next;
		mes "[エスメラルダ]";
		mes "教えてくださり、ありがとうございます。";
		mes "私はこれから彼らを助けに行きます。";
		mes "あなたに神のご加護があらんことを。";
		next;
		mes "‐エスメラルダの後を追いますか？‐";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			chgquest 12482,12483;
			set IL_MAZE_QUE,3;
			close;
		}
		mes "‐エスメラルダの後を追った‐";
		chgquest 12482,12483;
		set IL_MAZE_QUE,3;
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	case 3:
		mes "‐エスメラルダの後を追いますか？‐";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			close;
		}
		mes "‐エスメラルダの後を追った‐";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	end;
OnTouch:
	if(IL_MAZE_QUE == 2)
		unittalk "エスメラルダ : 光の導きを受ける、私たちプロンテラ司祭ギルドは、新しいギルド員を募集中です。";
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz03_q.gat,107,104,0	script	#ilmazed01	139,15,15,{
	if(IL_MAZE_QUE == 4) {
		cloakoffnpc "アンドレアの痕跡#D";
		misceffect 561,"アンドレアの痕跡#D";
		end;
	}
	cloakonnpc "アンドレアの痕跡#D";
	end;
}

prt_mz03_q.gat,107,104,3	script	アンドレアの痕跡#D	10311,{
	if(checkquest(12484) == 0) {
		mes "-他の痕跡を探しに向かいますか？-";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			close;
		}
		mes "-他の痕跡を探しに向かった-";
		close2;
		warp "prt_mz03_q.gat",10,16;
		end;
	}
	mes "^0000ff‐アンドレアの痕跡を見つけました。";
	mes "　痕跡を回収しますか？‐^000000";
	next;
	if(select("回収する","やめる") == 2) {
		mes "‐^0000ff回収作業を中断した^000000‐";
		close;
	}
	progressbar 5;
	misceffect 568,"アンドレアの痕跡#D";
	delquest 12484;
	if(checkquest(12484) == 0 && checkquest(12485) == 0 && checkquest(12486) == 0 && checkquest(12487) == 0) {
		delquest 12479;
		setquest 12488;
		set IL_MAZE_QUE,5;
		cloakonnpc "アンドレアの痕跡#D";
		cloakonnpc "アネスの痕跡#D";
		cloakonnpc "シルバノの痕跡#D";
		cloakonnpc "セリシアの痕跡#D";
		mes "^0000ff‐司祭ギルドの新人の痕跡を";
		mes "　すべて見つけたあなたは";
		mes "　エスメラルダの元へ向かった‐^000000";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	mes "-他の痕跡を探しに向かった-";
	close2;
	warp "prt_mz03_q.gat",10,16;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz03_q.gat,10,18,0	script	#ilmazed02	139,15,15,{
	if(IL_MAZE_QUE == 4) {
		cloakoffnpc "アネスの痕跡#D";
		misceffect 561,"アネスの痕跡#D";
		end;
	}
	cloakonnpc "アネスの痕跡#D";
	end;
}

prt_mz03_q.gat,10,18,3	script	アネスの痕跡#D	10313,{
	if(checkquest(12485) == 0) {
		mes "-他の痕跡を探しに向かいますか？-";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			close;
		}
		mes "-他の痕跡を探しに向かった-";
		close2;
		warp "prt_mz03_q.gat",135,66;
		end;
	}
	mes "^0000ff‐アネスの痕跡を見つけました。";
	mes "　痕跡を回収しますか？‐^000000";
	next;
	if(select("回収する","やめる") == 2) {
		mes "‐^0000ff回収作業を中断した^000000‐";
		close;
	}
	progressbar 5;
	misceffect 568,"アネスの痕跡#D";
	delquest 12485;
	if(checkquest(12484) == 0 && checkquest(12485) == 0 && checkquest(12486) == 0 && checkquest(12487) == 0) {
		delquest 12479;
		setquest 12488;
		set IL_MAZE_QUE,5;
		cloakonnpc "アンドレアの痕跡#D";
		cloakonnpc "アネスの痕跡#D";
		cloakonnpc "シルバノの痕跡#D";
		cloakonnpc "セリシアの痕跡#D";
		mes "^0000ff‐司祭ギルドの新人の痕跡を";
		mes "　すべて見つけたあなたは";
		mes "　エスメラルダの元へ向かった‐^000000";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	mes "-他の痕跡を探しに向かった-";
	close2;
	warp "prt_mz03_q.gat",135,66;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz03_q.gat,135,68,0	script	#ilmazed03	139,15,15,{
	if(IL_MAZE_QUE == 4) {
		cloakoffnpc "シルバノの痕跡#D";
		misceffect 561,"シルバノの痕跡#D";
		end;
	}
	cloakonnpc "シルバノの痕跡#D";
	end;
}

prt_mz03_q.gat,135,68,3	script	シルバノの痕跡#D	10315,{
	if(checkquest(12486) == 0) {
		mes "-他の痕跡を探しに向かいますか？-";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			close;
		}
		mes "-他の痕跡を探しに向かった-";
		close2;
		warp "prt_mz03_q.gat",183,24;
		end;
	}
	mes "^0000ff‐シルバノの痕跡を見つけました。";
	mes "　痕跡を回収しますか？‐^000000";
	next;
	if(select("回収する","やめる") == 2) {
		mes "‐^0000ff回収作業を中断した^000000‐";
		close;
	}
	progressbar 5;
	misceffect 568,"シルバノの痕跡#D";
	delquest 12486;
	if(checkquest(12484) == 0 && checkquest(12485) == 0 && checkquest(12486) == 0 && checkquest(12487) == 0) {
		delquest 12479;
		setquest 12488;
		set IL_MAZE_QUE,5;
		cloakonnpc "アンドレアの痕跡#D";
		cloakonnpc "アネスの痕跡#D";
		cloakonnpc "シルバノの痕跡#D";
		cloakonnpc "セリシアの痕跡#D";
		mes "^0000ff‐司祭ギルドの新人の痕跡を";
		mes "　すべて見つけたあなたは";
		mes "　エスメラルダの元へ向かった‐^000000";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	mes "-他の痕跡を探しに向かった-";
	close2;
	warp "prt_mz03_q.gat",183,24;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz03_q.gat,183,26,0	script	#ilmazed04	139,15,15,{
	if(IL_MAZE_QUE == 4) {
		cloakoffnpc "セリシアの痕跡#D";
		misceffect 561,"セリシアの痕跡#D";
		end;
	}
	cloakonnpc "セリシアの痕跡#D";
	end;
}

prt_mz03_q.gat,183,26,3	script	セリシアの痕跡#D	10317,{
	if(checkquest(12487) == 0) {
		mes "-他の痕跡を探しに向かいますか？-";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐その場にとどまった‐";
			close;
		}
		mes "-他の痕跡を探しに向かった-";
		close2;
		warp "prt_mz03_q.gat",107,102;
		end;
	}
	mes "^0000ff‐セリシアの痕跡を見つけました。";
	mes "　痕跡を回収しますか？‐^000000";
	next;
	if(select("回収する","やめる") == 2) {
		mes "‐^0000ff回収作業を中断した^000000‐";
		close;
	}
	progressbar 5;
	misceffect 568,"セリシアの痕跡#D";
	delquest 12487;
	if(checkquest(12484) == 0 && checkquest(12485) == 0 && checkquest(12486) == 0 && checkquest(12487) == 0) {
		delquest 12479;
		setquest 12488;
		set IL_MAZE_QUE,5;
		cloakonnpc "アンドレアの痕跡#D";
		cloakonnpc "アネスの痕跡#D";
		cloakonnpc "シルバノの痕跡#D";
		cloakonnpc "セリシアの痕跡#D";
		mes "^0000ff‐司祭ギルドの新人の痕跡を";
		mes "　すべて見つけたあなたは";
		mes "　エスメラルダの元へ向かった‐^000000";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	mes "-他の痕跡を探しに向かった-";
	close2;
	warp "prt_mz03_q.gat",107,102;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_fild01.gat,137,365,0	script	#ilmaze005	139,10,10,{
	if(IL_MAZE_QUE == 6) {
		cloakonnpc "エスメラルダ#5";
		mes "……";
		next;
		mes "‐そろそろ儀式が終わっただろうか？";
		mes "　もう一度迷宮の中へ入ろう‐";
		close2;
		warp "prt_mz01_q.gat",102,21;
		end;
	}
	if(IL_MAZE_QUE >= 7) {
		cloakoffnpc "エスメラルダ#5";
		end;
	}
	cloakonnpc "エスメラルダ#5";
	end;
}

prt_fild01.gat,141,367,3	script	エスメラルダ#5	677,5,5,{
	if(IL_MAZE_QUE == 8) {
		mes "[エスメラルダ]";
		mes "いつもありがとうございます。";
		mes "よろしければ、";
		mes "プロンテラまでお送りしましょうか？";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[エスメラルダ]";
			mes "そうですか。";
			mes "神のご加護がありますように。";
			close;
		}
		mes "[エスメラルダ]";
		mes "それでは、神のご加護がありますように。";
		close2;
		warp "prontera.gat",118,80;
		end;
	}
	if(IL_MAZE_QUE == 7) {
		mes "[エスメラルダ]";
		mes "ああ……";
		mes "挨拶もできないまま";
		mes "お別れかと思いきや、";
		mes "客員として活動してくださるそうですね。";
		next;
		mes "[エスメラルダ]";
		mes "なんと素晴らしい心を";
		mes "お持ちなのでしょうか。";
		mes "本当にありがとうございます。";
		mes "神のお導きがあるに違いありません。";
		next;
		menu "なぜギルド員たちを町に戻さないのですか？",-;
		mes "[エスメラルダ]";
		mes "それには訳があるのです。";
		mes "あの子たちは、";
		mes "守護聖物と契約をしておらず、";
		mes "何の保険もない状態なのです。";
		mes "町で見つかり間違って祓いでもされたら、";
		mes "完全消滅してしまいます。";
		next;
		mes "[エスメラルダ]";
		mes "だからしばらくはここに留まった方が";
		mes "安全と判断しました。";
		mes "普段は姿を隠しておいて";
		mes "あなたの前にのみ現れるように";
		mes "指示しておきました。";
		next;
		mes "[エスメラルダ]";
		mes "現在、ギルドの資金が尽きてしまっており、";
		mes "肉体を含めた完全な復活までは";
		mes "しばらく時間がかかりそうです。";
		mes "なので、しばらくギルドの活動を縮小し、";
		mes "ここでダンジョンを訪れる";
		mes "冒険者の支援をして資金を稼ぐつもりです。";
		next;
		mes "[エスメラルダ]";
		mes "この迷宮には高価な幻想の石を求めて";
		mes "探索に通う高レベルの冒険者が";
		mes "何人もいるそうですから、";
		mes "それなりの期間で";
		mes "ギルド員たちの復活資金は集まるはずです。";
		next;
		mes "[エスメラルダ]";
		mes "それが、今できる最善だと思います。";
		mes "もちろん、ギルドのお手伝いをしていただく";
		mes strcharinfo(0)+"様には、";
		mes "移動を無料で支援させていただきます。";
		next;
		mes "[エスメラルダ]";
		mes "そういうわけで、";
		mes "これからもどうかお手伝いを";
		mes "よろしくお願いします。";
		next;
		delquest 12492;
		setquest 202155;
		getitem 25271,10;
		set IL_MAZE_QUE,8;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		mes "[エスメラルダ]";
		mes "さて、ギルドの依頼については、";
		mes "アンドレアがまとめていますので、";
		mes "一度アンドレアの元へ送りますね。";
		close2;
		warp "prt_mz01_i.gat",102,21;
		end;
	}
OnTouch:
	if(IL_MAZE_QUE == 7)
		unittalk "エスメラルダ : あの子たちを完全に復活させるのはいつになることやら……。";
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_i.gat,103,22,0	script	#ilmaze001	139,10,10,{
	if(IL_MAZE_QUE == 8) {
		cloakoffnpc "歪んだ裂け目#2";
		misceffect 513,"歪んだ裂け目#2";
		misceffect 74,"歪んだ裂け目#2";
		cloakoffnpc "アンドレア#2";
		cloakoffnpc "アネス#2";
		cloakoffnpc "シルバノ#2";
		cloakoffnpc "セリシア#2";
	}
	end;
}

prt_mz01_i.gat,108,22,5	script	歪んだ裂け目#2	844,{
	mes "‐歪んだ裂け目の向こうに、";
	mes "　見慣れているようで";
	mes "　馴染みの無い迷宮の姿が広がっている。";
	mes "　一度入ったら、";
	mes "　二度と抜け出せなくなる";
	mes "　かもしれない‐";
	next;
	if(select("裂け目の向こうへ行く","見なかったことにする") == 2) {
		mes "^0000ff‐好奇心は猫をも殺すという。";
		mes "　静かに引き返そう‐^000000";
		close;
	}
	mes "-裂け目の向こうへ進んだ-";
	close2;
	warp "prt_mz03_i.gat",102,21;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_i.gat,111,20,1	script	セリシア#2	10316,{
	mes "[セリシア]";
	mes "私たちはみんな ";
	mes strcharinfo(0)+"様に";
	mes "感謝しております。";
	mes "私にもできることはありますか？";
	next;
	if(select("特にない","外へ送ってもらう") == 1) {
		mes "[セリシア]";
		mes "お力になれず、申し訳ありません。";
		close;
	}
	mes "[セリシア]";
	mes "わかりました。";
	close2;
	warp "prt_fild01.gat",136,365;
	end;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_i.gat,105,24,5	script	アンドレア#2	10310,{
	if(checkquest(12490)) {
		if(checkquest(12490)&0x2 == 0) {
			mes "[アンドレア]";
			mes "本日の依頼はすでに完了済みです。";
			mes "次の午前5時以降にいらしてください。";
			close;
		}
		delquest 12490;
		mes "[アンドレア]";
		mes "先日はありがとうございました。";
		mes strcharinfo(0)+"様のおかげで、";
		mes "少しずつギルドが復興できていますが、";
		mes "先は長そうでして……。";
		next;
	}
	if(checkquest(12478)) {
		mes "[アンドレア]";
		mes "現在の依頼の進行状況はこちらです。";
		next;
		mes "【進行状況】";
		mes "混沌のバフォメット.Jrの討伐　" + (checkquest(12470)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のハンターフライの討伐　" + (checkquest(12472)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のキラーマンティスの討伐　" + (checkquest(12473)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のマンティスの討伐　" + (checkquest(12474)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のポポリンの討伐　" + (checkquest(12475)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のサイドワインダーの討伐　" + (checkquest(12476)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		mes "混沌のステムワームの討伐　" + (checkquest(12477)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000");
		next;
		mes "[アンドレア]";
		mes "報告と報酬に関しては、";
		mes "^0000FFシルバノ^000000が担当いたします。";
		mes "依頼がすべて完了したら、";
		mes "^0000FFシルバノ^000000に報告してください。";
		close;
	}
	mes "[アンドレア]";
	mes "改めまして、"+strcharinfo(0)+"様に";
	mes "お願いしたい依頼がたくさんあります。";
	mes "受けていただけますか？";
	next;
	if(select("受ける","受けない") == 2) {
		mes "[アンドレア]";
		mes "依頼を受ける準備が出来たら、";
		mes "またいらしてください。";
		close;
	}
	setquest 12470;
	setquest 12472;
	setquest 12473;
	setquest 12474;
	setquest 12475;
	setquest 12476;
	setquest 12477;
	setquest 12478;
	mes "[アンドレア]";
	mes "いつもありがとうございます。";
	mes "今日もよろしくお願いいたします。";
	close;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_i.gat,105,20,7	script	アネス#2	10312,{
	mes "[アネス]";
	mes strcharinfo(0)+"様、";
	mes "歪んだ裂け目の中で、";
	mes "あたしたちの姿をした者に出会ったら、";
	mes "敵だと思ってください。";
	next;
	mes "[アネス]";
	mes "それらは、";
	mes "本来のあたしたちとは全くの別物です。";
	mes "幽霊の姿で復活する過程で";
	mes "負の感情が漏れ出し、";
	mes "凝縮されて誕生した邪念の塊です。";
	close;
OnInit:
	cloakonnpc;
	end;
}

prt_mz01_i.gat,111,24,3	script	シルバノ#2	10314,{
	if(checkquest(12490)) {
		if(checkquest(12490)&0x2) {
			mes "[シルバノ]";
			mes "いつもありがとうございます。";
			mes "アンドレアから";
			mes "新しい依頼を受注してください。";
			close;
		}
		mes "[シルバノ]";
		mes "本日の依頼の達成ありがとうございました。";
		mes "すべての依頼は完了しております。";
		mes "次の午前5時以降に、アンドレアから";
		mes "新しい依頼を受注してください。";
		close;
	}
	mes "[シルバノ]";
	mes "いつもありがとうございます。";
	mes "すべての依頼が完了したら、";
	mes "報酬をお渡しします。";
	mes "今すぐ受け取りますか？";
	next;
	if(select("ちょっと待って","報酬を受け取る") == 1) {
		mes "[シルバノ]";
		mes "いくらでもお待ちいたしますよ！";
		close;
	}
	mes "【進行状況】";
	mes "混沌のバフォメット.Jrの討伐　" + (checkquest(12470)==0? "^999999未受注^000000": (checkquest(12470)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のハンターフライの討伐　" + (checkquest(12472)==0? "^999999未受注^000000": (checkquest(12472)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のキラーマンティスの討伐　" + (checkquest(12473)==0? "^999999未受注^000000": (checkquest(12473)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のマンティスの討伐　" + (checkquest(12474)==0? "^999999未受注^000000": (checkquest(12474)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のポポリンの討伐　" + (checkquest(12475)==0? "^999999未受注^000000": (checkquest(12475)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のサイドワインダーの討伐　" + (checkquest(12476)==0? "^999999未受注^000000": (checkquest(12476)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	mes "混沌のステムワームの討伐　" + (checkquest(12477)==0? "^999999未受注^000000": (checkquest(12477)&0x4? "^FF0000完了^000000": "^0000FF討伐中^000000"));
	next;
	if(checkquest(12470)&0x4 && checkquest(12472)&0x4 && checkquest(12473)&0x4 && checkquest(12474)&0x4 && checkquest(12475)&0x4 && checkquest(12476)&0x4 && checkquest(12477)&0x4) {
		setquest 12490;
		delquest 12470;
		delquest 12472;
		delquest 12473;
		delquest 12474;
		delquest 12475;
		delquest 12476;
		delquest 12477;
		delquest 12478;
		getitem 25271,2;
		getexp 100000000,0,1;
		getexp 0,20000000,0;
		mes "[シルバノ]";
		mes "すべての依頼が完了されていますね。";
		mes "報酬をお受け取りください。";
		mes "ありがとうございました。";
		close;
	}
	mes "[シルバノ]";
	mes "完了していない依頼があります。";
	mes "すべての依頼を完了してから";
	mes "また来てください。";
	close;
OnInit:
	cloakonnpc;
	end;
}

// Quest Floor No.01 -------------------------------------------------------------
prt_mz03_q.gat,5,186,0		warp	ilmazewarp5001		1,1,prt_mz03_q.gat,151,134	/*To No.3-9*/
prt_mz03_q.gat,22,194,0		warp	ilmazewarp5002		1,1,prt_mz03_q.gat,175,48	/*To No.3-20*/
// Quest Floor No.02
prt_mz03_q.gat,58,194,0		script	#ilmazewarp5003		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_q.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_q.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_q.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_q.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Quest Floor No.03
prt_mz03_q.gat,85,174,0		warp	ilmazewarp5004		1,1,prt_mz03_q.gat,14,48	/*To No.3-16*/
prt_mz03_q.gat,102,165,0	warp	ilmazewarp5005		1,1,prt_mz03_q.gat,137,71	/*To No.3-19*/
// Quest Floor No.04
prt_mz03_q.gat,125,171,0	warp	ilmazewarp5006		1,1,prt_mz03_q.gat,105,111	/*To No.3-13*/
prt_mz03_q.gat,154,181,0	warp	ilmazewarp5007		1,1,prt_mz03_q.gat,139,48	/*To No.3-19*/
// Quest Floor No.05
prt_mz03_q.gat,175,165,0	warp	ilmazewarp5008		1,1,prt_mz03_q.gat,71,12	/*To No.3-22*/
prt_mz03_q.gat,194,175,0	warp	ilmazewarp5009		1,1,prt_mz03_q.gat,191,139	/*To No.3-10*/
// Quest Floor No.06
prt_mz03_q.gat,5,140,0		warp	ilmazewarp5010		1,1,prt_mz03_q.gat,111,56	/*To No.3-18*/
prt_mz03_q.gat,18,154,0		warp	ilmazewarp5011		1,1,prt_mz03_q.gat,48,21	/*To No.3-22*/
prt_mz03_q.gat,23,125,0		warp	ilmazewarp5012		1,1,prt_mz03_q.gat,177,71	/*To No.3-20*/
// Quest Floor No.07
prt_mz03_q.gat,54,154,0		warp	ilmazewarp5013		1,1,prt_mz03_q.gat,142,111	/*To No.3-14*/
prt_mz03_q.gat,63,125,0		warp	ilmazewarp5014		1,1,prt_mz03_q.gat,88,97	/*To No.3-13*/
// Quest Floor No.08
prt_mz03_q.gat,85,146,0		warp	ilmazewarp5015		1,1,prt_mz03_q.gat,22,88	/*To No.3-11*/
prt_mz03_q.gat,98,154,0		warp	ilmazewarp5016		1,1,prt_mz03_q.gat,99,31	/*To No.3-23*/
prt_mz03_q.gat,114,145,0	warp	ilmazewarp5017		1,1,prt_mz03_q.gat,168,22	/*To No.3-25*/
// Quest Floor No.09
prt_mz03_q.gat,137,125,0	warp	ilmazewarp5018		1,1,prt_mz03_q.gat,71,71	/*To No.3-17*/
prt_mz03_q.gat,154,134,0	warp	ilmazewarp5019		1,1,prt_mz03_q.gat,8,186	/*To No.3-1*/
// Quest Floor No.10
prt_mz03_q.gat,166,139,0	warp	ilmazewarp5020		1,1,prt_mz03_q.gat,63,88	/*To No.3-12*/
prt_mz03_q.gat,194,139,0	warp	ilmazewarp5021		1,1,prt_mz03_q.gat,191,175	/*To No.3-5*/
// Quest Floor No.11
prt_mz03_q.gat,17,114,0		warp	ilmazewarp5022		1,1,prt_mz03_q.gat,128,102	/*To No.3-14*/
prt_mz03_q.gat,22,85,0		warp	ilmazewarp5023		1,1,prt_mz03_q.gat,88,146	/*To No.3-8*/
// Quest Floor No.12
prt_mz03_q.gat,45,104,0		warp	ilmazewarp5024		1,1,prt_mz03_q.gat,96,48	/*To No.3-18*/
prt_mz03_q.gat,63,114,0		warp	ilmazewarp5025		1,1,prt_mz03_q.gat,14,71	/*To No.3-16*/
prt_mz03_q.gat,74,97,0		warp	ilmazewarp5026		1,1,prt_mz03_q.gat,57,8		/*To No.3-22*/
prt_mz03_q.gat,63,85,0		warp	ilmazewarp5027		1,1,prt_mz03_q.gat,169,139	/*To No.3-10*/
// Quest Floor No.13
prt_mz03_q.gat,85,97,0		warp	ilmazewarp5028		1,1,prt_mz03_q.gat,63,128	/*To No.3-7*/
prt_mz03_q.gat,105,114,0	warp	ilmazewarp5029		1,1,prt_mz03_q.gat,128,174	/*To No.3-4*/
prt_mz03_q.gat,114,95,0		warp	ilmazewarp5030		1,1,prt_mz03_q.gat,176,8	/*To No.3-25*/
// Quest Floor No.14
prt_mz03_q.gat,125,105,0	warp	ilmazewarp5031		1,1,prt_mz03_q.gat,58,191	/*To No.3-2*/
prt_mz03_q.gat,142,114,0	warp	ilmazewarp5032		1,1,prt_mz03_q.gat,54,151	/*To No.3-7*/
// Quest Floor No.15
prt_mz03_q.gat,168,94,0		warp	ilmazewarp5033		1,1,prt_mz03_q.gat,191,54	/*To No.3-20*/
prt_mz03_q.gat,182,85,0		warp	ilmazewarp5034		1,1,prt_mz01_q.gat,99,30
prt_mz03_q.gat,194,94,0		warp	ilmazewarp5035		1,1,prt_mz03_q.gat,151,22	/*To No.3-24*/
// Quest Floor No.16
prt_mz03_q.gat,5,58,0		warp	ilmazewarp5036		1,1,prt_mz03_q.gat,191,15	/*To No.3-25*/
prt_mz03_q.gat,14,74,0		warp	ilmazewarp5037		1,1,prt_mz03_q.gat,63,111	/*To No.3-12*/
prt_mz03_q.gat,14,45,0		warp	ilmazewarp5038		1,1,prt_mz03_q.gat,88,174	/*To No.3-3*/
// Quest Floor No.17
prt_mz03_q.gat,52,45,0		warp	ilmazewarp5039		1,1,prt_mz03_q.gat,16,31	/*To No.3-21*/
prt_mz03_q.gat,74,74,0		script	#ilmazewarp5040		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_q.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_q.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_q.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_q.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Quest Floor No.18
prt_mz03_q.gat,85,56,0		warp	ilmazewarp5041		1,1,prt_mz03_q.gat,176,31	/*To No.3-25*/
prt_mz03_q.gat,104,74,0		warp	ilmazewarp5042		1,1,prt_mz03_q.gat,111,22	/*To No.3-23*/
prt_mz03_q.gat,96,45,0		warp	ilmazewarp5043		1,1,prt_mz03_q.gat,48,104	/*To No.3-12*/
prt_mz03_q.gat,114,56,0		warp	ilmazewarp5044		1,1,prt_mz03_q.gat,8,140	/*To No.3-6*/
// Quest Floor No.19
prt_mz03_q.gat,139,45,0		script	#ilmazewarp5045		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_q.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_q.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_q.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_q.gat",54,8;    end;	/*To No.3-22*/
	}
}
prt_mz03_q.gat,137,74,0		warp	ilmazewarp5046		1,1,prt_mz03_q.gat,102,168	/*To No.3-3*/
// Quest Floor No.20
prt_mz03_q.gat,175,45,0		warp	ilmazewarp5047		1,1,prt_mz03_q.gat,22,191	/*To No.3-1*/
prt_mz03_q.gat,177,74,0		warp	ilmazewarp5048		1,1,prt_mz03_q.gat,23,128	/*To No.3-6*/
prt_mz03_q.gat,194,54,0		warp	ilmazewarp5049		1,1,prt_mz03_q.gat,171,94	/*To No.3-15*/
// Quest Floor No.21
prt_mz03_q.gat,23,5,0		warp	ilmazewarp5050		1,1,prt_mz03_q.gat,88,13	/*To No.3-23*/
prt_mz03_q.gat,16,34,0		warp	ilmazewarp5051		1,1,prt_mz03_q.gat,52,48	/*To No.3-17*/
// Quest Floor No.22
prt_mz03_q.gat,45,21,0		warp	ilmazewarp5052		1,1,prt_mz03_q.gat,18,151	/*To No.3-6*/
prt_mz03_q.gat,54,5,0		warp	ilmazewarp5053		1,1,prt_mz03_q.gat,71,97	/*To No.3-12*/
prt_mz03_q.gat,74,12,0		warp	ilmazewarp5054		1,1,prt_mz03_q.gat,175,168	/*To No.3-5*/
// Quest Floor No.23
prt_mz03_q.gat,85,13,0		warp	ilmazewarp5055		1,1,prt_mz03_q.gat,23,8		/*To No.3-21*/
prt_mz03_q.gat,99,34,0		warp	ilmazewarp5056		1,1,prt_mz03_q.gat,98,151	/*To No.3-8*/
prt_mz03_q.gat,114,22,0		warp	ilmazewarp5057		1,1,prt_mz03_q.gat,104,71	/*To No.3-18*/
// Quest Floor No.24
prt_mz03_q.gat,154,22,0		script	#ilmazewarp5058		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_q.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_q.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_q.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_q.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Quest Floor No.25
prt_mz03_q.gat,165,22,0		warp	ilmazewarp5059		1,1,prt_mz03_q.gat,111,145	/*To No.3-8*/
prt_mz03_q.gat,176,5,0		warp	ilmazewarp5060		1,1,prt_mz03_q.gat,111,95	/*To No.3-13*/
prt_mz03_q.gat,176,34,0		warp	ilmazewarp5061		1,1,prt_mz03_q.gat,88,56	/*To No.3-18*/
prt_mz03_q.gat,194,15,0		warp	ilmazewarp5062		1,1,prt_mz03_q.gat,8,58		/*To No.3-16*/


// Floor No.01 -------------------------------------------------------------
prt_mz03_i.gat,5,186,0		warp	ilmazewarp5101		1,1,prt_mz03_i.gat,151,134	/*To No.3-9*/
prt_mz03_i.gat,22,194,0		warp	ilmazewarp5102		1,1,prt_mz03_i.gat,175,48	/*To No.3-20*/
// Floor No.02
prt_mz03_i.gat,58,194,0		script	#ilmazewarp5103		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_i.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_i.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_i.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_i.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Floor No.03
prt_mz03_i.gat,85,174,0		warp	ilmazewarp5104		1,1,prt_mz03_i.gat,14,48	/*To No.3-16*/
prt_mz03_i.gat,102,165,0	warp	ilmazewarp5105		1,1,prt_mz03_i.gat,137,71	/*To No.3-19*/
// Floor No.04
prt_mz03_i.gat,125,171,0	warp	ilmazewarp5106		1,1,prt_mz03_i.gat,105,111	/*To No.3-13*/
prt_mz03_i.gat,154,181,0	warp	ilmazewarp5107		1,1,prt_mz03_i.gat,139,48	/*To No.3-19*/
// Floor No.05
prt_mz03_i.gat,175,165,0	warp	ilmazewarp5108		1,1,prt_mz03_i.gat,71,12	/*To No.3-22*/
prt_mz03_i.gat,194,175,0	warp	ilmazewarp5109		1,1,prt_mz03_i.gat,191,139	/*To No.3-10*/
// Floor No.06
prt_mz03_i.gat,5,140,0		warp	ilmazewarp5110		1,1,prt_mz03_i.gat,111,56	/*To No.3-18*/
prt_mz03_i.gat,18,154,0		warp	ilmazewarp5111		1,1,prt_mz03_i.gat,48,21	/*To No.3-22*/
prt_mz03_i.gat,23,125,0		warp	ilmazewarp5112		1,1,prt_mz03_i.gat,177,71	/*To No.3-20*/
// Floor No.07
prt_mz03_i.gat,54,154,0		warp	ilmazewarp5113		1,1,prt_mz03_i.gat,142,111	/*To No.3-14*/
prt_mz03_i.gat,63,125,0		warp	ilmazewarp5114		1,1,prt_mz03_i.gat,88,97	/*To No.3-13*/
// Floor No.08
prt_mz03_i.gat,85,146,0		warp	ilmazewarp5115		1,1,prt_mz03_i.gat,22,88	/*To No.3-11*/
prt_mz03_i.gat,98,154,0		warp	ilmazewarp5116		1,1,prt_mz03_i.gat,99,31	/*To No.3-23*/
prt_mz03_i.gat,114,145,0	warp	ilmazewarp5117		1,1,prt_mz03_i.gat,168,22	/*To No.3-25*/
// Floor No.09
prt_mz03_i.gat,137,125,0	warp	ilmazewarp5118		1,1,prt_mz03_i.gat,71,71	/*To No.3-17*/
prt_mz03_i.gat,154,134,0	warp	ilmazewarp5119		1,1,prt_mz03_i.gat,8,186	/*To No.3-1*/
// Floor No.10
prt_mz03_i.gat,166,139,0	warp	ilmazewarp5120		1,1,prt_mz03_i.gat,63,88	/*To No.3-12*/
prt_mz03_i.gat,194,139,0	warp	ilmazewarp5121		1,1,prt_mz03_i.gat,191,175	/*To No.3-5*/
// Floor No.11
prt_mz03_i.gat,17,114,0		warp	ilmazewarp5122		1,1,prt_mz03_i.gat,128,102	/*To No.3-14*/
prt_mz03_i.gat,22,85,0		warp	ilmazewarp5123		1,1,prt_mz03_i.gat,88,146	/*To No.3-8*/
// Floor No.12
prt_mz03_i.gat,45,104,0		warp	ilmazewarp5124		1,1,prt_mz03_i.gat,96,48	/*To No.3-18*/
prt_mz03_i.gat,63,114,0		warp	ilmazewarp5125		1,1,prt_mz03_i.gat,14,71	/*To No.3-16*/
prt_mz03_i.gat,74,97,0		warp	ilmazewarp5126		1,1,prt_mz03_i.gat,57,8		/*To No.3-22*/
prt_mz03_i.gat,63,85,0		warp	ilmazewarp5127		1,1,prt_mz03_i.gat,169,139	/*To No.3-10*/
// Floor No.13
prt_mz03_i.gat,85,97,0		warp	ilmazewarp5128		1,1,prt_mz03_i.gat,63,128	/*To No.3-7*/
prt_mz03_i.gat,105,114,0	warp	ilmazewarp5129		1,1,prt_mz03_i.gat,128,174	/*To No.3-4*/
prt_mz03_i.gat,114,95,0		warp	ilmazewarp5130		1,1,prt_mz03_i.gat,176,8	/*To No.3-25*/
// Floor No.14
prt_mz03_i.gat,125,105,0	warp	ilmazewarp5131		1,1,prt_mz03_i.gat,58,191	/*To No.3-2*/
prt_mz03_i.gat,142,114,0	warp	ilmazewarp5132		1,1,prt_mz03_i.gat,54,151	/*To No.3-7*/
// Floor No.15
prt_mz03_i.gat,168,94,0		warp	ilmazewarp5133		1,1,prt_mz03_i.gat,191,54	/*To No.3-20*/
prt_mz03_i.gat,182,85,0		warp	ilmazewarp5134		1,1,prt_mz01_i.gat,99,30
prt_mz03_i.gat,194,94,0		warp	ilmazewarp5135		1,1,prt_mz03_i.gat,151,22	/*To No.3-24*/
// Floor No.16
prt_mz03_i.gat,5,58,0		warp	ilmazewarp5136		1,1,prt_mz03_i.gat,191,15	/*To No.3-25*/
prt_mz03_i.gat,14,74,0		warp	ilmazewarp5137		1,1,prt_mz03_i.gat,63,111	/*To No.3-12*/
prt_mz03_i.gat,14,45,0		warp	ilmazewarp5138		1,1,prt_mz03_i.gat,88,174	/*To No.3-3*/
// Floor No.17
prt_mz03_i.gat,52,45,0		warp	ilmazewarp5139		1,1,prt_mz03_i.gat,16,31	/*To No.3-21*/
prt_mz03_i.gat,74,74,0		script	#ilmazewarp5140		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_i.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_i.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_i.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_i.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Floor No.18
prt_mz03_i.gat,85,56,0		warp	ilmazewarp5141		1,1,prt_mz03_i.gat,176,31	/*To No.3-25*/
prt_mz03_i.gat,104,74,0		warp	ilmazewarp5142		1,1,prt_mz03_i.gat,111,22	/*To No.3-23*/
prt_mz03_i.gat,96,45,0		warp	ilmazewarp5143		1,1,prt_mz03_i.gat,48,104	/*To No.3-12*/
prt_mz03_i.gat,114,56,0		warp	ilmazewarp5144		1,1,prt_mz03_i.gat,8,140	/*To No.3-6*/
// Floor No.19
prt_mz03_i.gat,139,45,0		script	#ilmazewarp5145		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_i.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_i.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_i.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_i.gat",54,8;    end;	/*To No.3-22*/
	}
}
prt_mz03_i.gat,137,74,0		warp	ilmazewarp5146		1,1,prt_mz03_i.gat,102,168	/*To No.3-3*/
// Floor No.20
prt_mz03_i.gat,175,45,0		warp	ilmazewarp5147		1,1,prt_mz03_i.gat,22,191	/*To No.3-1*/
prt_mz03_i.gat,177,74,0		warp	ilmazewarp5148		1,1,prt_mz03_i.gat,23,128	/*To No.3-6*/
prt_mz03_i.gat,194,54,0		warp	ilmazewarp5149		1,1,prt_mz03_i.gat,171,94	/*To No.3-15*/
// Floor No.21
prt_mz03_i.gat,23,5,0		warp	ilmazewarp5150		1,1,prt_mz03_i.gat,88,13	/*To No.3-23*/
prt_mz03_i.gat,16,34,0		warp	ilmazewarp5151		1,1,prt_mz03_i.gat,52,48	/*To No.3-17*/
// Floor No.22
prt_mz03_i.gat,45,21,0		warp	ilmazewarp5152		1,1,prt_mz03_i.gat,18,151	/*To No.3-6*/
prt_mz03_i.gat,54,5,0		warp	ilmazewarp5153		1,1,prt_mz03_i.gat,71,97	/*To No.3-12*/
prt_mz03_i.gat,74,12,0		warp	ilmazewarp5154		1,1,prt_mz03_i.gat,175,168	/*To No.3-5*/
// Floor No.23
prt_mz03_i.gat,85,13,0		warp	ilmazewarp5155		1,1,prt_mz03_i.gat,23,8		/*To No.3-21*/
prt_mz03_i.gat,99,34,0		warp	ilmazewarp5156		1,1,prt_mz03_i.gat,98,151	/*To No.3-8*/
prt_mz03_i.gat,114,22,0		warp	ilmazewarp5157		1,1,prt_mz03_i.gat,104,71	/*To No.3-18*/
// Floor No.24
prt_mz03_i.gat,154,22,0		script	#ilmazewarp5158		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "prt_mz03_i.gat",98,151;  end;	/*To No.3-8*/
		case 1:	warp "prt_mz03_i.gat",137,128; end;	/*To No.3-9*/
		case 2:	warp "prt_mz03_i.gat",14,71;   end;	/*To No.3-16*/
		case 3:	warp "prt_mz03_i.gat",54,8;    end;	/*To No.3-22*/
	}
}
// Floor No.25
prt_mz03_i.gat,165,22,0		warp	ilmazewarp5159		1,1,prt_mz03_i.gat,111,145	/*To No.3-8*/
prt_mz03_i.gat,176,5,0		warp	ilmazewarp5160		1,1,prt_mz03_i.gat,111,95	/*To No.3-13*/
prt_mz03_i.gat,176,34,0		warp	ilmazewarp5161		1,1,prt_mz03_i.gat,88,56	/*To No.3-18*/
prt_mz03_i.gat,194,15,0		warp	ilmazewarp5162		1,1,prt_mz03_i.gat,8,58		/*To No.3-16*/

prt_mz03_i.gat,0,0,0,0	monster	混沌のバフォメット.Jr	20525,25,5000,0,#IllLabyrinth::OnKilled1
prt_mz03_i.gat,0,0,0,0	monster	混沌のハンターフライ	20527,15,5000,0,#IllLabyrinth::OnKilled2
prt_mz03_i.gat,0,0,0,0	monster	混沌のキラーマンティス	20530,10,5000,0,#IllLabyrinth::OnKilled2
prt_mz03_i.gat,0,0,0,0	monster	混沌のマンティス		20528,10,5000,0,#IllLabyrinth::OnKilled3
prt_mz03_i.gat,0,0,0,0	monster	混沌のポポリン			20531,25,5000,0,#IllLabyrinth::OnKilled3
prt_mz03_i.gat,0,0,0,0	monster	混沌のサイドワインダー	20526,25,5000,0,#IllLabyrinth::OnKilled4
prt_mz03_i.gat,0,0,0,0	monster	混沌のステムワーム		20532,25,5000,0,#IllLabyrinth::OnKilled4

prt_mz03_i.gat,0,0,0	script	#IllLabyrinth	-1,{
OnKilledAndrea:  callsub L_BossKill, 0;
OnKilledAnes:    callsub L_BossKill, 1;
OnKilledSilvano: callsub L_BossKill, 2;
OnKilledCecilia: callsub L_BossKill, 3;
L_BossKill:
	set 'mob,0;
	set 'count[getarg(0)],0;
	end;
OnKilled1: callsub L_BossSummon, 0;
OnKilled2: callsub L_BossSummon, 1;
OnKilled3: callsub L_BossSummon, 2;
OnKilled4: callsub L_BossSummon, 3;
L_BossSummon:
	if('mob == 0) {
		set '@type,getarg(0);
		set 'count['@type],'count['@type]+1;
		if('count['@type] >= 'cntTbl['@type] && rand(10) == 0) {
			set 'mob,areacallmonster("prt_mz03_i.gat",0,0,0,0,"--ja--",20521+'@type,strnpcinfo(0)+"::OnKilled"+'LabelTbl$['@type]);
			set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
			mobuseskillpos 'mob,21,10,'@x,'@y,0,0;	// サンダーストーム
			mobuseskill 'mob,730,1,0,0,-1,0,0;	// M呪縛陣
			//出現セリフ不明
			switch('@type) {
			case 0: unittalk 'mob,"混沌のアンドレア : ……。"; break;
			case 1: unittalk 'mob,"混沌のアネス : ……。"; break;
			case 2: unittalk 'mob,"混沌のシルバノ : ……。"; break;
			case 3: unittalk 'mob,"混沌のセリシア : ……。"; break;
			}
		}
	}
	end;
OnInit:
	setarray 'cntTbl,3,3,4,6;
	setarray 'LabelTbl$,"Andrea","Anes","Silvano","Cecilia";
	end;
}
