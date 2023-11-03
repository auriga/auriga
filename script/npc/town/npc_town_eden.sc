//====================================================================
// Ragnarok Online - Eden Group Script	by refis
//====================================================================
prontera.gat,122,52,3	script	楽園団空間移動員	729,{
	mes "[楽園団空間移動員]";
	mes "この世界の全てが";
	mes "初めての経験であるあなた！";
	mes "是非、ここに来てみてください！";
	mes "その名もズバリ!!";
	mes "^ff0000楽園団^000000の登場です！";
	next;
	mes "[楽園団空間移動員]";
	mes "現在、正式稼動に向けて";
	mes "暫定オープン中です。";
	mes "正式稼動時は混むことが";
	mes "予想されますので興味ある方は";
	mes "今すぐ^ff0000楽園団^000000へ";
	mes "お越しください！";
	next;
	if(select("楽園団に行きたい","会話をやめる") == 2) {
		mes "[楽園団空間移動員]";
		mes "いつでもあなたのご参加、";
		mes "お待ちしています！";
		close;
	}
	mes "[楽園団空間移動員]";
	mes "さぁ、楽園団に行ってみましょう！";
	mes "しゅっぱーつ！";
	close2;
	warp "moc_para01.gat",31,14;
	end;
OnInit:
	waitingroom "楽園団",0;
	end;
}

moc_para01.gat,27,35,5	script	事務担当ライム	952,{
	cutin "laime_evenor01",2;
	if(checkquest(117099) & 0x8 == 0) {
		mes "[ライム]";
		mes "夢とロマンスを追い求める";
		mes "冒険者たちよ。";
		mes "あなた達の楽園は";
		mes "恋人の温もりや、";
		mes "安らぎの子守唄でもない。";
		mes "そう、ここにあるのです。";
		next;
		cutin "laime_evenor02",2;
		mes "[ライム]";
		mes "はじめまして。";
		mes "私は楽園団の受付担当";
		mes "^0000FFライム・イヴェノル^000000と申します。";
		mes "気軽にライムとお呼び下さい。";
		mes "^FF0000登録証^000000をお持ちでないようなので";
		mes "楽園団について説明しますね。";
		next;
		cutin "laime_evenor03",2;
		mes "[ライム]";
		mes "楽園団では、";
		mes "ミッドガルド中の困っている人達を";
		mes "助ける目的で作られた機関であり、";
		mes "彼らの苦情や問題などを";
		mes "解決する業務を行う予定です。";
		next;
		mes "[ライム]";
		mes "予定と言った通り、";
		mes "まだ準備段階の状態なんです。";
		mes "というのも、担当する人間が";
		mes "まだ足りない状態で……";
		next;
		mes "[ライム]";
		mes "とはいえこれから続々と";
		mes "人を増やして便利になる予定です。";
		mes "是非、今後にご期待下さい。";
		mes "簡単ですが説明は以上です。";
		next;
		mes "[ライム]";
		mes "ちなみに楽園団への登録は";
		mes "簡単な登録手続きを済ませば、";
		mes "誰でも楽園団のメンバーになれます。";
		mes "楽園団に入会されますか？";
		next;
		if(select("はい","いいえ") == 2) {
			cutin "laime_evenor04",2;
			mes "[ライム]";
			mes "ふむ……残念です。";
			mes "もし気が変わりましたら";
			mes "また、声をかけてください。";
			close2;
			cutin "laime_evenor04",255;
			end;
		}
		cutin "laime_evenor01",2;
		mes "[ライム]";
		mes "分かりました。";
		mes "入会をご希望ですね。";
		mes "ではこちらに名前を書いてください。";
		next;
		mes "-差し出された用紙に名前を書いた‐";
		next;
		emotion 21;
		cutin "laime_evenor02",2;
		mes "[ライム]";
		mes "ありがとうございます。";
		mes "^3131FF" +strcharinfo(0)+ "^000000様ですね？";
		mes "楽園団会員リストに";
		mes "あなたのお名前を登録いたしました。";
		mes "これで登録作業は完了です。";
		mes "ようこそ、楽園団へ！";
		next;
		cutin "laime_evenor01",2;
		mes "[ライム]";
		mes "最後に注意事項ですが";
		mes "お渡しした登録証がないと";
		mes "メンバー認証が出来ませんので";
		mes "再度、登録手続きからとなります。";
		mes "失くさないように気をつけて";
		mes "お持ち下さい。";
		next;
		if(checkitemblank() == 0) {
			mes "[ライム]";
			mes "あらあら……。";
			mes "登録証を渡そうと思いましたが";
			mes "アイテムの種類数が多いようです。";
			mes "種類の数を減らしてから";
			mes "また声をかけてください。";
			close2;
			cutin "laime_evenor04.bmp", 255;
			end;
		}
		cutin "laime_evenor04",2;
		mes "[ライム]";
		mes "何せ登録者数が多いもので";
		mes "一人一人の顔を憶えるのは";
		mes "不可能ですからね……。";
		mes "この登録証で、判別しています。";
		getitem 6219,1;
		setquest 117099;
		compquest 117099;
		next;
		cutin "laime_evenor01",2;
		mes "[ライム]";
		mes "ところで……";
		mes "楽園団に登録されたなら是非、";
		mes "楽園団メンバー専用の扉をくぐり";
		mes "左手のワープポータルを抜けた";
		mes "部屋に行ってみてください。";
		next;
		mes "[ライム]";
		mes "そこに現在のメンバーが";
		mes "集まっているはずです。";
		mes "他の部屋はまだいろいろ";
		mes "準備中ですので解放されるまで";
		mes "今しばらくお待ちください。";
		close2;
		cutin "laime_evenor01",255;
		end;
	}
	if(countitem(6219) < 1) {	// 楽園団の証
		mes "[ライム]";
		mes "^ff0000楽園団の証^000000を";
		mes "無くしてしまったんですか？";
		mes "再発行はすぐに出来ますが、";
		mes "今すぐ再発行しますか？";
		next;
		if(select("再発行してもらう","今はまだいい") == 2) {
			cutin "laime_evenor01",2;
			mes "[ライム]";
			mes "荷物の整理が必要ですか？";
			mes "再発行する際には";
			mes "声をかけてください。";
			close2;
			cutin "laime_evenor04",255;
			end;
		}
		if(checkitemblank() == 0) {
			mes "[ライム]";
			mes "あらあら……。";
			mes "登録証を渡そうと思いましたが";
			mes "アイテムの種類数が多いようです。";
			mes "種類の数を減らしてから";
			mes "また声をかけてください。";
			close2;
			cutin "laime_evenor04.bmp", 255;
			end;
		}
		cutin "laime_evenor04", 2;
		mes "[ライム]";
		mes "はい、新しい登録証です。";
		mes "今度は無くさないよう";
		mes "気を付けてくださいね。";
		getitem 6219, 1;
		close2;
		cutin "laime_evenor04",255;
		end;
	}
	mes "[ライム]";
	mes "夢とロマンスを追い求める";
	mes "冒険者たちよ。";
	mes "あなた達の楽園は";
	mes "恋人の温もりや、";
	mes "安らぎの子守唄でもない。";
	mes "そう、ここにあるのです。";
	next;
	cutin "laime_evenor01",2;
	mes "[ライム]";
	mes "おや、" +strcharinfo(0)+ "様。";
	mes "楽園団に登録されたなら是非、";
	mes "楽園団メンバー専用の扉をくぐり";
	mes "左手のワープポータルを抜けた";
	mes "部屋に行ってみてください。";
	next;
	mes "[ライム]";
	mes "そこに現在のメンバーが";
	mes "集まっているはずです。";
	mes "他の部屋はまだいろいろ";
	mes "準備中ですので解放されるまで";
	mes "今しばらくお待ちください。";
	close2;
	cutin "laime_evenor01",255;
	end;
}

moc_para01.gat,30,10,0	warp	#eden_out		1,1,prontera.gat,119,52
moc_para01.gat,48,16,0	warp	#warp_2_2f		1,1,moc_para01.gat,48,164
moc_para01.gat,47,161,0	warp	#warp_2_1f		1,1,moc_para01.gat,47,18
moc_para01.gat,107,12,0	warp	#warp_2_din_2	1,1,moc_para01.gat,47,36
moc_para01.gat,100,27,0	warp	#warp_2_gym		1,1,moc_para01.gat,47,85
moc_para01.gat,49,86,0	warp	#warp_2_pass_1	1,1,moc_para01.gat,103,27

moc_para01.gat,47,38,0	script	#warp_2_pass	45,1,1,{
	if(countitem(6219) < 1) {	// 楽園団の証
		mes "‐扉に注意書きが書いてある‐";
		mes "　";
		mes "‐^FF0000この先は楽園団メンバー専用ルームに";
		mes "　なっております。";
		mes "　楽園団メンバーの方なら";
		mes "　いつでもご利用頂けます^000000‐";
		next;
		mes "‐この扉を開けるためには";
		mes "　^FF0000楽園団への登録^000000が";
		mes "　必要なようだ……‐";
		close;
	}
	warp "moc_para01.gat",106,14;
	end;
}

moc_para01.gat,16,22,7	script	老冒険家	900,{
	mes "[老冒険家]";
	mes "私はアドバイザーとして";
	mes "ここに呼ばれたんだ。";
	mes "冒険者の楽園となるような";
	mes "施設にするにはどうしたら";
	mes "いいかとライムから";
	mes "相談される日々だよ。";
	next;
	mes "[老冒険家]";
	mes "私の時代にはこんな施設、";
	mes "存在すらしなかったからね。";
	mes "そう考えると今の若い冒険者は";
	mes "恵まれているね。";
	close;
}

moc_para01.gat,20,35,5	script	事務補助ニデ	814,{
	mes "[ニデ]";
	mes "私が楽園団に配属されて";
	mes "まだ間もないと思っていたのですが、";
	mes "よくよく考えてみると";
	mes "もう配属されて半月ほど、";
	mes "経過していたのですね……。";
	next;
	mes "[ニデ]";
	mes "つい時間を忘れてしまう程、";
	mes "仕事に追われる日々を送っていました。";
	mes "準備中な上に人手が全然、";
	mes "足りない状態ですからね……。";
	next;
	mes "[ニデ]";
	mes "こんな状態じゃ正式稼動は";
	mes "いつになることやらと";
	mes "暗くなりがちですけど、";
	mes "皆さんの元気な姿を見ていると";
	mes "頑張ろうという気になるので";
	mes "助かっています。";
	close;
}
