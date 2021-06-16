//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Turtle Island Quest Script	by refis
//= Registry ===================================================================
// IL_TUR_QUE -> 0～9
//==============================================================================

//============================================================
// クエストNPC
//------------------------------------------------------------
alberta.gat,211,28,5	script	騎士エイルバル#illtur	405,{
	switch(IL_TUR_QUE) {
	case 0:
		if(BaseLevel < 170) {
			mes "[騎士エイルバル]";
			mes "もしかして冒険者様ですか？";
			mes "もしそうなら是非";
			mes "お願いしたいことが……。";
			next;
			mes "[騎士エイルバル]";
			mes "……おや、まだ修行中の";
			mes "冒険者でしたか。";
			mes "失礼いたしました。";
			mes "危険な仕事に修行中の方を、";
			mes "巻き込む訳にはいきません。";
			next;
			mes "‐^4d4dffBaseLv170以上の時";
			mes "　進行可能なクエストです。^000000‐";
			close;
		}
		mes "[騎士エイルバル]";
		mes "もしかして冒険者様ですか？";
		mes "もしそうなら是非";
		mes "お願いしたいことがあります。";
		next;
		if(select("どういうことですか？","今は忙しいので") == 2) {
			mes "[騎士エイルバル]";
			mes "突然のご無礼をお許し下さい。";
			mes "冒険者様に祝福を。";
			close;
		}
		mes "[騎士エイルバル]";
		mes "突然のご無礼をお許し下さい。";
		mes "私はアルベルタ警備隊、";
		mes "第1騎士団所属、騎士エイルバルであります。";
		next;
		mes "[騎士エイルバル]";
		mes "私は騎士団の命を受け、";
		mes "タートルアイランドで過去失踪した";
		mes "アルベルタ第2騎士団の";
		mes "捜索任務をしておりました。";
		next;
		mes "[騎士エイルバル]";
		mes "しかし生憎と先日の航海で嵐に会い";
		mes "何日も海の上を彷徨った末";
		mes "タートルアイランドであって";
		mes "タートルアイランドでない場所に";
		mes "辿りつきました。";
		emotion 1,"";
		next;
		menu "それはどのような場所ですか？",-;
		mes "[騎士エイルバル]";
		mes "私にも上手く説明はできません。";
		mes "そこはタートルアイランドに";
		mes "間違いないのですが、";
		mes "妙にぞっとするところでした。";
		next;
		mes "[騎士エイルバル]";
		mes "恐る恐る探索を始めた私でしたが";
		mes "そこで危機に瀕してしまい";
		mes "もはや絶望的という状況まで";
		mes "追い込まれてしまったのです。";
		next;
		mes "[騎士エイルバル]";
		mes "もうダメかと思ったその時";
		mes "誰かが私をそこから";
		mes "抜け出せるように";
		mes "誘導してくれたのです。";
		next;
		mes "[騎士エイルバル]";
		mes "あの時は無我夢中だったため";
		mes "あまり詳しく覚えていないのですが";
		mes "気が付けば私はアルベルタの";
		mes "海風の吹く港に立っていて、";
		mes "この亀の甲羅の欠片の2枚だけが";
		mes "手の中にありました。";
		next;
		mes "[騎士エイルバル]";
		mes "何が起こったのかは分かりません。";
		mes "どうにか生きて帰ってきたこと……";
		mes "それだけは分かりました。";
		next;
		menu "亀の甲羅の欠片は2枚あったのでは？",-;
		mes "[騎士エイルバル]";
		mes "もう1枚は私の友人が持っています。";
		mes "いや、持っているはずと";
		mes "言うべきでしょうか。";
		next;
		switch(select("その友人に何か？","信じがたいですね")) {
		case 1:
			emotion 19;
			mes "[騎士エイルバル]";
			mes "先ほどのお願いというのは";
			mes "他でもない友人の話です。";
			mes "前置きが長くなってすみません。";
			mes "宜しければもう少しだけ";
			mes "私の話を聞いてください。";
			break;
		case 2:
			emotion 19;
			mes "[騎士エイルバル]";
			mes "仰る通りだと思います。";
			mes "私さえ狼狽えましたから。";
			mes "しかし、もう少しだけ聞いてください。";
			mes "私の友人を救うためにも。";
			break;
		}
		next;
		mes "[騎士エイルバル]";
		mes "友人の名は^0000CDイエルフェン^000000。";
		mes "ジュノーで考古学の教授をやっています。";
		mes "私が彼に、この欠片を見せたら";
		mes "大変興味を持ってくれました。";
		mes "^0000CDタートルアイランドにのみ生息する";
		mes "亀の甲羅で作ったものだと関心してました^000000。";
		next;
		mes "[騎士エイルバル]";
		mes "しかし、私がその欠片を渡した後に";
		mes "欠片を調べていたイエルフェンが、";
		mes "いきなり何かに巻き込まれたかのように";
		mes "影も形も無く消え失せてしまいました。";
		emotion 20,"";
		next;
		mes "[騎士エイルバル]";
		mes "信じられないのも無理はありません。";
		mes "ですが、この目でハッキリ見たんです。";
		mes "この場所でイエルフェンが消えるのを！";
		next;
		mes "[騎士エイルバル]";
		mes "……これがもう^FF0000半日前^000000のことです。";
		mes "その間、ジュノーの大学にも連絡して";
		mes "タートルアイランドにも行って来ましたが、";
		mes "何の成果も無く藁にもすがる思いで";
		mes "イエルフェンの消えたこの場所に";
		mes "亀の甲羅の欠片を持ってきました。";
		next;
		mes "[騎士エイルバル]";
		mes "冒険者様、お願いです。";
		mes "私の友人を探すのを";
		mes "手伝っていただけませんか？";
		mes "この亀の甲羅の欠片だけが";
		mes "手がかりなのです。";
		next;
		menu "友人の見た目を教えてください",-;
		mes "[騎士エイルバル]";
		mes "^0000CD青い髪で、眼鏡をかけてます^000000。";
		mes "^0000CD顔に学者と書かれてるような姿^000000だから、";
		mes "見ればすぐ分かるでしょう。";
		next;
		menu "亀の甲羅の欠片を見せてください",-;
		mes "‐騎士が渡してくれた";
		mes "　亀の甲羅の欠片を手に持ってみた。";
		mes "　亀の青い甲羅に小さい葉が";
		mes "　一枚刻まれている。";
		mes "　拙い作りだが";
		mes "　どこか温かい感じがする。‐";
		next;
		mes "‐^424242しばらく欠片を調べていたら";
		mes "　頭の中に微かに何かが";
		mes "　浮かんでくるのを感じた直後";
		mes "　いきなり突風が巻き起こり";
		mes "　視界が黒くなっていく。^000000‐";
		next;
		emotion 16;
		mes "[騎士エイルバル]";
		mes "うぐ、以前の航海の時も";
		mes "こんな風が吹いていました。";
		mes "冒険者様、大丈夫ですか!?";
		next;
		mes "‐^424242エイルバルの声と共に、";
		mes "　意識が遠くなってゆく。";
		mes "　湿った泥の匂いがしてきた……。^000000‐";
		close2;
		if(checkitemblank() == 0) {
			mes "^009eff【インフォメーション】";
			mes "これ以上多くの種類の";
			mes "荷物を持つことが出来ません。";
			mes "1個以上の空きを作ってください。^000000";
			close;
		}
		getitem 25315,1;
		setquest 16096;
		set IL_TUR_QUE,1;
		warp "tur_d03_i.gat",132,187;
		end;
	case 1:
		mes "‐^424242意識が遠くなってゆく。";
		mes "　湿った泥の匂いがしてきた……。^000000‐";
		close2;
		warp "tur_d03_i.gat",132,187;
		end;
	case 2:
	case 3:
		emotion 0,"騎士エイルバル#illtur";
		mes "[騎士エイルバル]";
		mes "冒険者様！ご無事でしたか！";
		mes "イエルフェンに続いて";
		mes "冒険者様まで消えてしまい";
		mes "本当に心配しておりました。";
		next;
		menu "イエルフェン教授の手掛かりを見つけました",-;
		emotion 0,"騎士エイルバル#illtur";
		mes "[騎士エイルバル]";
		mes "本当ですか？";
		mes "ああ、本当に良かった。";
		next;
		mes "[騎士エイルバル]";
		mes "またイエルフェンを";
		mes "探しに行かれるのですか？";
		mes "是非、私も同行させてください。";
		next;
		if(select("私が行きます","準備があります") == 2) {
			mes "[騎士エイルバル]";
			mes "どうかイエルフェンのこと";
			mes "お願いいたします。";
			close;
		}
		mes "[騎士エイルバル]";
		mes "ありがとうございます。";
		mes "本当にありがとうございます。";
		mes "どうかイエルフェンを";
		mes "お救いください。";
		next;
		mes "‐^424242亀の甲羅の欠片を握りしめると";
		mes "　風で髪の毛がなびくのを感じた。^000000‐";
		next;
		mes "[騎士エイルバル]";
		mes "どうか、お気をつけて。";
		next;
		mes "‐^424242完全に目の前が暗くなる前";
		mes "　頬にやや冷たい空気が触れた……。^000000 ‐";
		close2;
		warp "tur_d03_i.gat",132,187;
		end;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		emotion 0,"騎士エイルバル#illtur";
		mes "[騎士エイルバル]";
		mes "冒険者様！ご無事でしたか！";
		mes "イエルフェンに続いて";
		mes "冒険者様まで消えてしまい";
		mes "本当に心配しておりました。";
		next;
		menu "イエルフェン教授を見つけました",-;
		emotion 0,"騎士エイルバル#illtur";
		mes "[騎士エイルバル]";
		mes "本当ですか？";
		mes "ああ、本当に良かった。";
		next;
		mes "[騎士エイルバル]";
		mes "またイエルフェンの元に";
		mes "行かれるのですか？";
		mes "是非、私も同行させてください。";
		next;
		if(select("私が行きます","準備があります") == 2) {
			mes "[騎士エイルバル]";
			mes "どうかイエルフェンのこと";
			mes "お願いいたします。";
			close;
		}
		mes "[騎士エイルバル]";
		mes "ありがとうございます。";
		mes "本当にありがとうございます。";
		mes "どうかイエルフェンを";
		mes "お救いください。";
		next;
		mes "‐^424242亀の甲羅の欠片を握りしめると";
		mes "　風で髪の毛がなびくのを感じた。^000000‐";
		next;
		mes "[騎士エイルバル]";
		mes "どうか、お気をつけて。";
		next;
		mes "‐^424242完全に目の前が暗くなる前";
		mes "　頬にやや冷たい空気が触れた……。^000000 ‐";
		close2;
		warp "tur_d03_i.gat",132,187;
		end;
	case 9:
		mes "[騎士エイルバル]";
		mes "冒険者様、こんにちは。";
		next;
		switch(select("また向こうへ行く","雑談をしにきた","何でもない")) {
		case 1:
			switch(select("悲しみの陽居村へ","悲しみの陽居村(クエスト)へ")) {
			case 1:
				set '@map$,"tur_d03_j.gat";
				break;
			case 2:
				set '@map$,"tur_d03_i.gat";
				break;
			}
			mes "‐亀の甲羅の欠片を握りしめると";
			mes "　風で髪の毛がなびくのを感じた。‐";
			next;
			mes "[騎士エイルバル]";
			mes "どうか、お気をつけて。";
			next;
			mes "‐^424242完全に目の前が暗くなる前";
			mes "　頬にやや冷たい空気が触れた……。^000000 ‐";
			close2;
			warp '@map$,132,187;
			end;
		case 2:
			mes "[騎士エイルバル]";
			mes "冒険者様、こんにちは。";
			mes "イエルフェンに全ての話を聞きました。";
			mes "あいつは人を心配させておいて";
			mes "また行ってしまいました。";
			mes "向こうの秘密を解いたら";
			mes "戻ると言ってましたね。";
			next;
			mes "[騎士エイルバル]";
			mes "イエルフェンだけでなく、";
			mes "ナリンという少女も";
			mes "助けられたと聞きました。";
			mes "冒険者様は立派な方だと信じた";
			mes "私の目に狂いは無かったようです。";
			next;
			mes "[騎士エイルバル]";
			mes "向こうに行くときは";
			mes "イエルフェンの様子も";
			mes "見に行ってあげてください。";
			mes "自分自身よりも";
			mes "研究が大事な奴なので";
			mes "友人としては心配です。";
			next;
			mes "[騎士エイルバル]";
			mes "しかし、これまでの事を";
			mes "騎士団に報告したら";
			mes "幸いなことに私は";
			mes "イエルフェンの研究を";
			mes "支援する任務を任されました。";
			next;
			mes "[騎士エイルバル]";
			mes "今は手の届かない所にいますが";
			mes "数日に1度はイエルフェンの";
			mes "元気な姿を見れますし";
			mes "少しは安心できます。";
			next;
			mes "[騎士エイルバル]";
			mes "イエルフェンに会ったら";
			mes "奴が睡眠を取っているか";
			mes "確認をお願いします。";
			close;
		case 3:
			mes "[騎士エイルバル]";
			mes "困ったことがありましたら";
			mes "いつでも私を頼ってください。";
			mes "冒険者様には感謝しても";
			mes "しきれないほどの";
			mes "御恩がありますから。";
			close;
		}
	}
}

tur_d03_i.gat,139,186,3	script	少女#illtur01	10238,{
	switch(IL_TUR_QUE) {
	case 0:
	case 1:
		mes "[少女]";
		mes "また見知らぬ人。";
		mes "しかも、やっぱり";
		mes "持ち帰ってきたのね。";
		mes "その亀の甲羅の欠片を。";
		next;
		emotion 19,"";
		menu "君は？",-;
		mes "[少女]";
		mes "あなたに関係ない。";
		mes "あなたが知らなくていい者。";
		next;
		menu "ここはどこ？",-;
		mes "[少女]";
		mes "あなたがいてはいけない場所。";
		next;
		menu "どうしてここに？",-;
		mes "[少女]";
		mes "あなたが知る必要はない。";
		next;
		mes "[少女]";
		mes "何も知らなくていい。";
		mes "だけど、^0000CDここにいてはいけない人^000000が";
		mes "あなた以外にもいるの。";
		mes "元の場所へ連れて帰って。";
		mes "^0000CD青い髪の学者^000000。知ってる？";
		next;
		menu "その人を探しに来た",-;
		mes "[少女]";
		mes "それはよかった。";
		mes "今はどこにいるのか";
		mes "分からないけど、";
		mes "居そうな場所はいくつかあるから";
		mes "教えてあげる。";
		viewpoint 1, 80, 180, 1, 0xFFFF33;
		viewpoint 1, 235, 187, 2, 0xFFFF33;
		viewpoint 1, 217, 73, 3, 0xFFFF33;
		next;
		mes "[少女]";
		mes "^0000CDここの二か所、下の二か所^000000。";
		mes "教えたから、探して連れて帰って。";
		mes "そして二度と来ないで。";
		next;
		mes "‐あなたは目の前の少女に";
		mes "　いくつか質問をすることにした。‐";
		next;
		menu "君は誰？何故イエルフェンを知っている？",-;
		mes "[少女]";
		mes "さっきも答えたとおり。";
		mes "あなたは二度と";
		mes "ここに来る必要のない人。";
		mes "それを知る必要はない。";
		next;
		menu "どうやったら帰れる？",-;
		emotion 9,"少女#illtur01";
		mes "[少女]";
		mes "帰り方は知らない。";
		mes "どこから来たのかも知らないのに、";
		mes "どこへ行けばいいのか";
		mes "分かる訳がない。";
		next;
		mes "[少女]";
		mes "でもあっち、黒い穴の中に……";
		mes "何かあるかも。詳しくは知らない。";
		mes "あなたの方が知ってるはず。";
		next;
		mes "‐^424242少女は光の群れの方に";
		mes "　目配りをした。";
		mes "　元の場所に帰りたい時は";
		mes "　近付いて調べてみよう。^000000‐";
		next;
		misceffect 778,"少女#illtur01";
		if(!sleep2(1000)) end;
		misceffect 778,"";
		misceffect 877,"";
		menu "これは？",-;
		mes "[少女]";
		mes "あなたをしばらくの間、守る呪術。";
		mes "しかし、それらは常に側にいる。";
		if(!sleep2(1000)) end;
		mes "無暗に好奇心を抱かないで。";
		if(!sleep2(1000)) end;
		mes "微かなものを見つめないで。";
		if(!sleep2(1000)) end;
		mes "一本道で振り返らないで。";
		if(!sleep2(1000)) end;
		mes "他人の背中を見ながら話さないで。";
		next;
		mes "[少女]";
		mes "^FF0000あなたが見知らぬ息をする者であると、";
		mes "決してバレないで。^000000";
		delquest 16096;
		setquest 16097;
		setquest 16098;
		setquest 16099;
		set IL_TUR_QUE,2;
		close;
	case 2:
	case 3:
	case 4:
	case 5:
		mes "[少女]";
		mes "……まだ、生きていたんだね。";
		next;
		mes "[少女]";
		mes "危険な目にあう前に";
		mes "あの人を連れてここから出てって。";
		next;
		mes "[少女]";
		mes "居そうな場所はいくつかあるから";
		mes "教えてあげる。";
		viewpoint 1, 80, 180, 1, 0xFFFF33;
		viewpoint 1, 235, 187, 2, 0xFFFF33;
		viewpoint 1, 217, 73, 3, 0xFFFF33;
		close;
	case 6:
		mes "[少女]";
		mes "無事だったんだね。二人とも。";
		mes "……危険にさせてごめん。";
		next;
		cloakoffnpc "考古学者イエルフェン#i1";
		emotion 4,"考古学者イエルフェン#i1";
		mes "[考古学者イエルフェン]";
		mes "……ふう、死ぬかと思いました。";
		next;
		mes "[少女]";
		mes "じゃもう帰って。元の場所へ。";
		mes "そして全部忘れて。";
		next;
		mes "[考古学者イエルフェン]";
		mes "はい？いきなりどういうことですか。";
		mes "僕は戻ってきますよ。";
		mes "ここの秘密を全て解明するまではね。";
		next;
		mes "[少女]";
		mes "なぜ、そんなことをする？";
		mes "傲慢だね。";
		next;
		emotion 32,"考古学者イエルフェン#i1";
		mes "[考古学者イエルフェン]";
		mes "僕は学者ですから。";
		next;
		mes "[少女]";
		mes "あなたが学者だとしても";
		mes "ここをいじり回す権利はない。";
		next;
		menu "さっきのことを詳しく聞かせてほしい",-;
		mes "[少女]";
		mes "知る必要はない。";
		mes "どうせ離れていく人たち。";
		mes "前も話したけど誰も帰って来なかった。";
		mes "もう期待しない。そうすれば";
		mes "失望することもないから。";
		next;
		emotion 1,"";
		if(!sleep2(1000)) end;
		emotion 9,"";
		mes "[少女]";
		mes "……誰も帰って来ない。";
		mes "来ない方がいい。";
		mes "ここは危ないから。";
		next;
		emotion 0,"考古学者イエルフェン#i1";
		mes "[考古学者イエルフェン]";
		mes "あなたが欲しいのは";
		mes "それでもここに帰ってくる";
		mes "誰かですよね。";
		next;
		if(!sleep2(3000)) end;
		emotion 7,"少女#illtur01";
		unittalk getnpcid(0,"少女#illtur01"),"少女 : ……本当、勝手な考え。";
		next;
		mes "[少女]";
		mes "ふう……分かった。";
		mes "話してあげる。";
		mes "聞いたら帰ると約束して。";
		mes "あまり話したいもの、ではないけど。";
		mes "あなたたちがしつこ過ぎるから";
		mes "特別に話してあげる。";
		next;
		mes "[少女]";
		mes "……ちょっと待ってて。";
		mes "整理する時間が必要。";
		mes "すごく永い間";
		mes "語ってなかった話だから。";
		next;
		emotion 54,"";
		mes "[考古学者イエルフェン]";
		mes "それじゃ、僕は";
		mes "ちょっとこの辺を回ってきます。";
		next;
		cloakonnpc "考古学者イエルフェン#i1";
		mes "[少女]";
		mes "少し待ってから";
		mes "また話しかけてくれる？";
		chgquest 16104,16116;
		set IL_TUR_QUE,7;
		close;
	case 7:
		cloakoffnpc "考古学者イエルフェン#i1";
		mes "[ナリン]";
		mes "待ってくれてありがとう。";
		mes "自己紹介から始めた方がいいよね。";
		mes "私、ナリン。^0000CD古い霊魂。^000000";
		next;
		mes "[ナリン]";
		mes "私たちと普通に";
		mes "会話できるのをみると";
		mes "あなたはこれまでに";
		mes "沢山の経験をしたみたいね。";
		next;
		mes "[ナリン]";
		mes "今はある物のおかげで";
		mes "お話できてるけど";
		mes "教授のような平凡な人は";
		mes "本当なら私たちを";
		mes "見ることも出来ない。";
		next;
		mes "[ナリン]";
		mes "ここの住民たちは";
		mes "みんな怨念に縛られた霊魂だよ。";
		mes "死んだ当時から";
		mes "切に願った何かに囚われ";
		next;
		mes "[ナリン]";
		mes "自身が死んだことにさえ";
		mes "気付くこともできずに";
		mes "いつまでも同じことを繰り返す。";
		next;
		mes "[ナリン]";
		mes "私はマシな方で、たまに";
		mes "そこから抜け出せるけど";
		mes "結局は元に戻って";
		mes "同じことを繰り返す。";
		next;
		unittalk getnpcid(0,"少女#illtur01"),"ナリン  :  私たちは増悪する。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"少女#illtur01"),"ナリン  :  生きてる者。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"少女#illtur01"),"ナリン  :  怨念に縛られない者。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"少女#illtur01"),"ナリン  :  見知らぬ息をする者。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"少女#illtur01"),"ナリン  :  最後の息を、聞きたがる。";
		if(!sleep2(1000)) end;
		mes "[ナリン]";
		mes "だけど、幸いなことに";
		mes "あなたたちが私たちに";
		mes "気付かない限り私たちも";
		mes "あなたたちに気付けない。";
		next;
		mes "[ナリン]";
		mes "だけど、それも長くは続かない。";
		mes "ここに長くいればいるほど";
		mes "お互いに気付いてしまう。少しずつ。";
		mes "そしていきなり気づいてしまう。";
		mes "あれは見慣れていないものだと。";
		mes "……そうなれば、終わり。";
		next;
		mes "[ナリン]";
		mes "教授は私の物を持ってるから";
		mes "すぐ分かったけど。";
		mes "普通なら私も気付かない。";
		next;
		mes "[考古学者イエルフェン]";
		mes "ナリンさんの物とは";
		mes "亀の甲羅の欠片のことですか？";
		mes "エイルバルを助けたのも";
		mes "やはり、あなたでしたか。";
		mes "友人を助けてくれてありがとう。";
		next;
		mes "[ナリン]";
		mes "私のためにやったことだった。";
		mes "感謝されるものじゃない。";
		mes "私を縛ってる怨念は";
		mes "^0000CDここで、誰か死なせたくない。";
		mes "みんなを救いたい^000000。";
		mes "という、ものだから。";
		next;
		emotion 7,"少女#illtur01";
		mes "[ナリン]";
		mes "う……本当、バカな話だよ。";
		mes "……ごめん、ちょっとだけ";
		mes "一人にしてくれない？";
		mes "時間を潰してきて。";
		next;
		mes "[考古学者イエルフェン]";
		mes "問題ありません。";
		mes "ちょっと席を外しておきましょう。";
		mes strcharinfo(0)+"様、行きましょうか。";
		emotion 33,"";
		chgquest 16116,16117;
		set IL_TUR_QUE,8;
		close2;
		cloakonnpc "考古学者イエルフェン#i1";
		end;
	case 8:
		cloakoffnpc "考古学者イエルフェン#i1";
		emotion 2,"考古学者イエルフェン#i1";
		mes "[考古学者イエルフェン]";
		mes "もう宜しいのですか?";
		mes "無理しなくて良いですよ。";
		mes "この辺には興味深いものが";
		mes "多いですから。";
		next;
		mes "[ナリン]";
		mes "待ってくれてありがとう。";
		mes "もう大丈夫。残りを話してあげる。";
		next;
		mes "[ナリン]";
		mes "ここに来た人は";
		mes "教授の友人が初めてじゃない。";
		mes "稀だけど以前にも";
		mes "迷い込んできた人たちがいた。";
		next;
		mes "[ナリン]";
		mes "古い霊魂だった私は";
		mes "初めてここに来た人を見た時に";
		mes "自分が何を望んでいたのかを";
		mes "思い出した。";
		next;
		mes "[ナリン]";
		mes "その人は私の事を";
		mes "死ぬほど恐がっていたけど";
		mes "最後は生きてここから出てった。";
		mes "その時は私も久しぶりに自我を";
		mes "保つことができた。";
		next;
		mes "[ナリン]";
		mes "怨念に流され理性も感性も失わず";
		mes "私のままでいられる時間……";
		mes "本当に久しぶりで";
		mes "とっても嬉しかった。";
		next;
		mes "[ナリン]";
		mes "だから、みんなを救いたかった。";
		mes "流れてきた人々を";
		mes "永遠に縛られた者たちさえも。";
		mes "だけど、気付いた。";
		mes "私が救った人たちはみんな";
		mes "自分のいるべき場所に帰ってしまった。";
		next;
		mes "[ナリン]";
		mes "そして私は独りぼっちになった。";
		mes "私が誰で、何をしているかを";
		mes "はっきり感じながら。";
		mes "長い長い時を延々と。";
		next;
		mes "[ナリン]";
		mes "それは、むしろ";
		mes "怨念に縛られた霊魂たちが";
		mes "羨ましいほどの";
		mes "苦しみだった。";
		next;
		mes "[ナリン]";
		mes "だけど見捨てることも";
		mes "出来なかった。";
		mes "危険に陥った人たちを。";
		mes "ここを出れば二度と";
		mes "帰ってこないと知りながら。";
		next;
		mes "[ナリン]";
		mes "期待はしたくない。";
		mes "期待すれば裏切られるから。";
		mes "……これでお終い、私の話。";
		mes "もうその欠片は返して、二人も帰って。";
		next;
		mes "[ナリン]";
		mes "そうだ忘れるところだった。";
		mes "また掛けてあげる、呪術。";
		mes "弱くて、長く続かない。";
		mes "切れる前に、出て行って。";
		if(!sleep2(500)) end;
		misceffect 778,"少女#illtur01";
		if(!sleep2(1000)) end;
		misceffect 778,"";
		misceffect 778,"考古学者イエルフェン#i1";
		misceffect 877,"";
		misceffect 877,"考古学者イエルフェン#i1";
		next;
		menu "苦労したんだね",-;
		mes "[ナリン]";
		mes "……同情されるため";
		mes "長い話したんじゃ、ない。";
		mes "気になるようなこと";
		mes "言わないで。";
		next;
		menu "帰らない",-;
		emotion 0,"少女#illtur01";
		mes "[ナリン]";
		mes "何を言ってるの!?";
		mes "話を聞いたら";
		mes "帰れと言った……！";
		mes "もう、もう期待しないと";
		mes "言ったじゃない！";
		next;
		mes "[考古学者イエルフェン]";
		mes "僕たちはまた来ますよ。";
		mes "独りで寂しくないように。";
		mes "ここの他の魂たちも";
		mes "自我を取り戻せるように";
		mes "手伝いますよ。";
		next;
		emotion 9,"少女#illtur01";
		mes "[ナリン]";
		mes "それは本当？";
		mes "……ううん。";
		mes "偶然だと言った。";
		mes "私のようにはいかない、彼らは。";
		next;
		mes "[考古学者イエルフェン]";
		mes "それはやってみないと分かりません。";
		mes "そうでしょう？";
		mes "もし上手く行かなくても";
		mes "私たちはまた試しに来ますから。";
		next;
		mes "[ナリン]";
		mes "だめ、来ないで。";
		mes "ここは危険。";
		mes "もう来ちゃだめ。";
		next;
		mes "[ナリン]";
		mes "もういい。";
		mes "私は二人のこと忘れる。";
		mes "ここの怨霊は全て";
		mes "そう出来てるから。";
		next;
		emotion 0,"";
		mes "[ナリン]";
		mes "私はみんなより";
		mes "ほんの少し長く覚えてられる";
		mes "だけど結局忘れる。";
		mes "忘れても思い出せるのは";
		mes "昔からずっと持っていた";
		mes "亀の甲羅の欠片のおかげ。";
		next;
		mes "[ナリン]";
		mes "自分ではどうしても";
		mes "その亀の甲羅の欠片を";
		mes "捨てることができなかった。";
		mes "二人が捨ててくれれば";
		mes "私は全てを";
		mes "忘れることができる。";
		next;
		mes "[ナリン]";
		mes "……そのつもりで";
		mes "教授の友人に持たせたの。";
		mes "全てを忘れるために。";
		next;
		mes "[ナリン]";
		mes "それにそれが無かったら";
		mes "二人はきっと";
		mes "ここまで来られない。";
		mes "どちらにしても";
		mes "私は二人の事を忘れる。";
		next;
		menu "たとえ忘れても思い出はナリンの中にある",-;
		mes "[ナリン]";
		mes "みんなを救いたいという";
		mes "願いさえあれば";
		mes "またきっと思い出せる？";
		mes "……二人の事も？";
		next;
		menu "もし忘れても何度でも思い出させる",-;
		mes "[考古学者イエルフェン]";
		mes "僕もナリンさんが";
		mes "寂しい思いをしないように";
		mes "また必ず来ます。";
		mes "研究のためもありますが";
		mes "ナリンさんと";
		mes "まだまだお話したいですから。";
		next;
		mes "[ナリン]";
		mes "本当……本当の本当？";
		mes "私を訪ねてきてくれる？";
		mes "……独りぼっちじゃ……";
		mes "なくても、いい？";
		next;
		menu "約束する",-;
		mes "[ナリン]";
		mes "……。";
		next;
		mes "[ナリン]";
		mes "……あ……。";
		next;
		mes "[ナリン]";
		mes "ありがとう……";
		mes "本当に……。";
		next;
		if(countitem(25315) > 0)
			delitem 25315,1;
		misceffect 861,"";
		misceffect 861,"考古学者イエルフェン#i1";
		if(!sleep2(500)) end;
		emotion 0,"考古学者イエルフェン#i1";
		mes "[考古学者イエルフェン]";
		mes "お、おや？持っていた";
		mes "亀の甲羅の欠片が消えました。";
		mes "急に溶けたみたいに。";
		next;
		mes "[ナリン]";
		mes "それは私の願いが";
		mes "込められた物だったから。";
		mes "もう……存在する必要が";
		mes "なくなったから。";
		next;
		mes "[考古学者イエルフェン]";
		mes "それはどういうことですか？";
		next;
		emotion 7,"少女#illtur01";
		mes "[ナリン]";
		mes "詳しいことは知らない。";
		mes "ただそうかも知れないだけ。";
		next;
		mes "[ナリン]";
		mes "そうだ。これあげる。";
		mes "これ、教授にも。";
		next;
		mes "[考古学者イエルフェン]";
		mes "こ……これは、幻想の石！";
		next;
		mes "[ナリン]";
		mes "……そんな名前だった？";
		mes "綺麗だったから持っていた。";
		mes "何なのかも分からない。";
		next;
		mes "[ナリン]";
		mes "これ約束の証。";
		mes "二人を思い出すように努力する。";
		mes "だから必ず訪ねて来て。";
		mes "……必ず。";
		next;
		mes "[ナリン]";
		mes "明日も、明後日も……";
		mes "待っているから……。";
		mes (Sex? "兄": "姉")+ "さん、教授。";
		next;
		mes "[考古学者イエルフェン]";
		mes "約束します。";
		mes "また必ずお会いしましょう。";
		next;
		menu "他の人たちも助けたい",-;
		mes "[ナリン]";
		mes "方法はある。";
		mes "それを教える。";
		mes "どうやったら……助けられるか。";
		next;
		mes "[ナリン]";
		mes "^0000CD彼らの願いごとを叶えて。";
		mes (Sex? "兄": "姉")+ "さんにはどんなに";
		mes "つまらないことでも";
		mes "彼らが喜ぶものなら、叶えて。^000000";
		mes "そうしてると、彼らもいつかは……。";
		next;
		menu "分かった",-;
		emotion 40,"少女#illtur01";
		mes "[ナリン]";
		mes "ふふ……。";
		next;
		mes "[ナリン]";
		mes "私、今まで独りで";
		mes "耐えられたのは";
		mes "いつか二人に";
		mes "出逢えるからだったかな……。";
		next;
		emotion 33,"少女#illtur01";
		mes "[ナリン]";
		mes "きっと、そう。";
		if(!sleep2(1000)) end;
		mes "必ず……思い出すから……";
		mes "絶対……また来て。";
		if(!sleep2(1000)) end;
		mes "……約束。";
		next;
		mes "[考古学者イエルフェン]";
		mes "僕はここの秘密を";
		mes "解き明かすまでは";
		mes "ずっとここにいますからね。";
		mes "心配しないで。";
		mes "僕も"+strcharinfo(0)+"さんも";
		mes "ナリンさんを忘れやしません。";
		close2;
		if(checkitemblank() == 0) {
			mes "^009eff【インフォメーション】";
			mes "これ以上多くの種類の";
			mes "荷物を持つことが出来ません。";
			mes "1個以上の空きを作ってください。^000000";
			close;
		}
		delquest 16117;
		setquest 16105;
		setquest 202095;
		set IL_TUR_QUE,9;
		getitem 25271,10;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		unittalk getnpcid(0,"考古学者イエルフェン#i1"),"イエルフェン : それじゃ、また来ます！";
		cloakonnpc "考古学者イエルフェン#i1";
		end;
	case 9:
		mes "[ナリン]";
		mes "また来てねとは言ったけど……";
		mes "今日はもう帰って。";
		mes "長くいると危険。";
		mes "呪術を掛けて守るにも";
		mes "限界があるから。";
		next;
		mes "[ナリン]";
		mes "また二人で一緒に来て。";
		mes "その時また呪術を掛けてあげる。";
		mes "……もし私が忘れたら";
		mes "必ずまた思い出すから……。";
		close;
	}
}

tur_d03_i.gat,132,194,3	script	光の群れ#illtur01	10042,{
	if(IL_TUR_QUE <= 1) {
		mes "[少女]";
		mes "また見知らぬ人。";
		mes "しかも、やっぱり";
		mes "持ち帰ってきたのね。";
		mes "その亀の甲羅の欠片を。";
		close;
	}
	if(IL_TUR_QUE == 9) {
		if(select("アルベルタに戻る","ここに残る") == 2) {
			mes "‐まだここで";
			mes "　やるべきことが残ってる。‐";
			close;
		}
		warp "alberta.gat",219,31;
		end;
	}
	mes "‐^424242扉の向こうは黒く染まり、";
	mes "　何も存在しないかのように見えた。";
	mes "　黒い虚構の前、薄赤い光の群れが";
	mes "　漂っている。少女はこちらを、";
	mes "　ちょっともどかしそうに見た。^000000‐";
	next;
	mes "[少女]";
	mes "あなたの持つ";
	mes "亀の甲羅の欠片が助けてくれる。";
	mes "強く握ってみて。";
	next;
	mes "[少女]";
	mes "……ここは念願の場所。";
	mes "切なくて、心苦しく";
	mes "だから毒になる。";
	next;
	if(select("アルベルタに戻る","ここに残る") == 2) {
		mes "[少女]";
		mes "……帰らない……つもり？";
		next;
		mes "‐まだここで";
		mes "　やるべきことが残ってる。‐";
		close;
	}
	mes "‐^424242曖昧な話だが";
	mes "　不思議と信じられる気がした。";
	mes "　少女の教え通りに亀の甲羅の欠片を";
	mes "　強く握った。^000000‐";
	next;
	mes "[少女]";
	mes "そう。早く";
	mes "……帰ってしまえ。";
	next;
	mes "‐^424242塩辛い匂いのする風が、裾を揺らした。";
	mes "　アルベルタの港の波音と";
	mes "　カモメの鳴き声が聞こえる。^000000‐";
	close2;
	warp "alberta.gat",219,31;
	end;
}

tur_d03_i.gat,136,187,5	script	考古学者イエルフェン#i1	740,{
	end;
OnInit:
	cloakonnpc;
	end;
}

tur_d03_i.gat,80,180,1	script	気の早い男#illtur01	10239,{
	switch(IL_TUR_QUE) {
	case 0:
	case 1:
		donpcevent "気の早い男#illtur01::OnTalk"+ rand(1,3);
		mes "[気の早い男]";
		mes "なくしちゃった、なくしちゃった。";
		mes "我が子。我が愛しい子。";
		mes "どこへ行ったの？我が子。";
		mes "名前が何だったの我が娘。";
		mes "娘？我が子。";
		next;
		mes "[気の早い男]";
		mes "誰だ？";
		mes "我が子、誰だ？";
		close;
	case 2:
	case 3:
	case 4:
		if(checkquest(16097) == 0){
			donpcevent "気の早い男#illtur01::OnTalk"+ rand(1,3);
			mes "[気の早い男]";
			mes "^FF0000いない、我が娘。愛^000000しい我が子供。";
			mes "もういない。なく^FF0000しちゃっ^000000た。";
			mes "なくしちゃった。ふう……ふうう……";
			mes "愛^FF0000しい我が子供……みつか^000000";
			mes "らな^FF0000い、み、つか^000000ら";
			mes "ない、ない、 ^FF0000み、みつから^000000、ない……。";
			close;
		}
		donpcevent "気の早い男#illtur01::OnTalk"+ rand(1,3);
		mes "[気の早い男]";
		mes "なくしちゃった、なくしちゃった。";
		mes "我が子。我が愛しい子。";
		mes "どこへ行ったの？我が子。";
		mes "名前が何だったの我が娘。";
		mes "娘？我が子。";
		next;
		mes "[気の早い男]";
		mes "誰だ？我が子、どこにいる？";
		mes "我が娘？我が……娘？";
		mes "はは、ははは。なくしちゃった。";
		mes "なくしちゃった。";
		next;
		menu "子供をお探しですか？",-,"私が手伝いましょうか？",-;
		mes "[気の早い男]";
		mes "ちがう。";
		mes "^FF0000見つけられない^000000。";
		next;
		mes "[気の早い男]";
		mes "い^FF0000ない。いない。";
		mes "見つけ^000000られない。";
		next;
		mes "[気の早い男]";
		mes "もうい^FF0000ない。";
		mes "我が娘^000000。子供……子供？";
		mes "いない。ははっ、はは^FF0000はは。";
		mes "いない。はっ、は^000000は、くすくす";
		mes "可^FF0000愛い我が子^000000供、";
		mes "我が愛しい我が^FF0000娘、いない^000000。いない。";
		next;
		mes "‐どうも会話が成立しそうにない。‐";
		next;
		delquest 16097;
		if(checkquest(16097) == 0 && checkquest(16098) == 0 && checkquest(16099) == 0) {
			mes "‐あの少女が教えてくれた";
			mes "　場所が^0000CDもう一か所^000000ある。";
			mes "　^0000CD薄暗い久陽宮^000000に";
			mes "　降りて探してみるか。‐";
			setquest 16100;
			set IL_TUR_QUE,3;
			close;
		}
		mes "‐あの少女が教えてくれた";
		mes "　場所がまだある。";
		mes "　他の場所へ行ってみよう。‐";
		close;
	default:
		donpcevent "気の早い男#illtur01::OnTalk"+ rand(1,3);
		mes "[気の早い男]";
		mes "^FF0000いない、我が娘。愛^000000しい我が子供。";
		mes "もういない。なく^FF0000しちゃっ^000000た。";
		mes "なくしちゃった。ふう……ふうう……";
		mes "愛^FF0000しい我が子供……みつか^000000";
		mes "らな^FF0000い、み、つか^000000ら";
		mes "ない、ない、 ^FF0000み、みつから^000000、ない……。";
		close;
	}
OnTalk1:
	sleep 3000;
	unittalk "気の早い男 : 我が子、なくしちゃった。なくしちゃったよ。愛しい我が子供。どこ行った？";
	sleep 3000;
	unittalk "気の早い男 : 我が子？子供？なくしちゃっ、なく、我が娘……子供。どこ……どこ？";
	sleep 3000;
	end;
OnTalk2:
	sleep 3000;
	unittalk "気の早い男 : いない。探せられない。我が子。もういない。愛しい我が娘。";
	sleep 3000;
	unittalk "気の早い男 : もういない。探せられない……我が娘、我が……娘？娘、娘？我が……";
	sleep 3000;
	end;
OnTalk3:
	sleep 3000;
	unittalk "気の早い男 : 子供がいない……我が子が、いなくなった。愛しい我が娘。";
	sleep 3000;
	unittalk "気の早い男 : 自分とそっくりな人形があんなに好きだったのに。もう人形はない。娘もいない。";
	sleep 3000;
	end;
}

tur_d03_i.gat,235,187,7	script	細かい軍人#illtur01	10240,{
	switch(IL_TUR_QUE) {
	default:
		donpcevent "細かい軍人#illtur01::OnTalk"+ rand(1,3);
		mes "[細かい軍人]";
		mes "クスクス……";
		mes "^FF0000ブツ^000000、ブツ。^FF0000クスクス^000000……";
		mes "あのく^BDBDBDそ^000000みたいな";
		mes "モン^BDBDBDス^000000ターさえいなかったら……。";
		next;
		mes "[細かい軍人]";
		mes "ぜ……全部、俺の物に";
		mes "^BDBDBDなっ^000000た^BDBDBDはず^000000なのに……";
		mes "お…俺の宝^BDBDBD物^000000が……";
		mes "^FF0000クスクス^000000……。";
		close;
	case 2:
	case 3:
		donpcevent "細かい軍人#illtur01::OnTalk"+ rand(1,3);
		mes "[細かい軍人]";
		mes "クスクス……";
		mes "^FF0000ブツ^000000、ブツ。^FF0000クスクス^000000……";
		mes "あのく^BDBDBDそ^000000みたいな";
		mes "モン^BDBDBDス^000000ターさえいなかったら……。";
		next;
		mes "[細かい軍人]";
		mes "ぜ……全部、俺の物に";
		mes "^BDBDBDなっ^000000た^BDBDBDはず^000000なのに……";
		mes "お…俺の宝^BDBDBD物^000000が……";
		mes "^FF0000クスクス^000000……。";
		if(checkquest(16098) == 0){
			close;
		}
		next;
		mes "[細かい軍人]";
		mes "ブツ、ブツ……クスクス……";
		mes "宝^BDBDBD物^000000……俺の^BDBDBD宝^000000物……";
		mes "全部^BDBDBD手に^000000入れる……。";
		next;
		switch(select("近くで人を見なかった？","大丈夫ですか？")) {
		case 1:
			misceffect 563,"細かい軍人#illtur01";
			mes "[細かい軍人]";
			mes "^BDBDBD人^000000間？人間^BDBDBDだ^000000と？";
			mes "そんなのがい^BDBDBDる^000000訳がない^BDBDBDじゃん^000000!!";
			break;
		case 2:
			misceffect 563,"細かい軍人#illtur01";
			mes "[細かい軍人]";
			mes "^BDBDBD大^000000丈夫？何が！";
			mes "大丈^BDBDBD夫な^000000訳が^BDBDBDな^000000いだろ!!";
			break;
		}
		mes "バ^BDBDBDカ^000000やろう！";
		mes "俺をバカ^BDBDBDに^000000しや^BDBDBDがっ^000000て";
		mes "ゆるさ^BDBDBDな^000000い！";
		next;
		mes "[細かい軍人]";
		mes "くそ^BDBDBDみ^000000たいな……^BDBDBDく^000000そお……";
		mes "クス、クスクス……^FF0000ブツ^000000、ブツ……。";
		next;
		mes "‐どうも会話が成立しそうにない。‐";
		next;
		delquest 16098;
		if(checkquest(16097) == 0 && checkquest(16098) == 0 && checkquest(16099) == 0) {
			mes "‐あの少女が教えてくれた";
			mes "　場所が^0000CDもう一か所^000000ある。";
			mes "　^0000CD薄暗い久陽宮^000000に";
			mes "　降りて探してみるか。‐";
			setquest 16100;
			set IL_TUR_QUE,3;
			close;
		}
		mes "‐あの少女が教えてくれた";
		mes "　場所がまだある。";
		mes "　他の場所へ行ってみよう。";
		close;
	}
OnTalk1:
	sleep 3000;
	unittalk "細かい軍人 : クス……クスクス……ブツ、ブツブツ……クス……";
	sleep 3000;
	unittalk "細かい軍人 : お、俺の宝物……クスクス、許さん……";
	sleep 3000;
	end;
OnTalk2:
	sleep 3000;
	unittalk "細かい軍人 : 復讐……復讐しなきゃ…ブツブツ、ブツ、クスクス、クスクスクス……";
	sleep 3000;
	unittalk "細かい軍人 : 全部……復讐しなきゃ…不吉なアサルトタートル……俺の宝物を奪った！";
	sleep 3000;
	end;
OnTalk3:
	sleep 3000;
	unittalk "細かい軍人 : 俺の宝物、不吉なアサルトタートルさえいなかったら……全部、ブツ、ブツブツ……";
	sleep 3000;
	unittalk "細かい軍人 : クスクス、宝物……俺の宝物……ブツ……ブツブツ、クスクス……";
	sleep 3000;
	end;
}

tur_d04_i.gat,96,112,1	script	元気のない女#illtur01	10241,{
	switch(IL_TUR_QUE) {
	default:
		donpcevent "元気のない女#illtur01::OnTalk"+ rand(1,3);
		mes "[元気のない女]";
		mes "ひもじいです。";
		mes "動けそうにもありません。";
		mes "どうか慈悲を恵んでください。";
		mes "あまりにも飢えてます……。";
		close;
	case 2:
	case 3:
		if(checkquest(16099) == 0){
			donpcevent "元気のない女#illtur01::OnTalk"+ rand(1,3);
			mes "[元気のない女]";
			mes "ひもじいです。";
			mes "動けそうにもありません。";
			mes "どうか慈悲を恵んでください。";
			mes "あまりにも飢えてます……。";
			close;
		}
		donpcevent "元気のない女#illtur01::OnTalk"+ rand(1,3);
		mes "[元気のない女]";
		mes "ひもじいです。";
		mes "動けそうにもありません。";
		mes "どうか慈悲を恵んでください。";
		mes "あまりにも飢えてます……。";
		next;
		mes "[元気のない女]";
		mes "今日何も食べれませんでした。";
		mes "昨日も、一昨日も、その前も。";
		mes "死んでしまいます。慈悲を恵んでください。";
		mes "どうか……どうか慈悲を。";
		next;
		menu "助けます",-;
		mes "[元気のない女]";
		mes "このままだと死んでしまいます。";
		mes "死んでしまいます。";
		mes "ひもじいです。";
		mes "とってもひもじいです。";
		next;
		mes "[元気のない女]";
		mes "今日何も食べれませんでした。";
		mes "昨日も飢えました。";
		mes "子供も飢えてます。夫も飢えてます。";
		mes "死んでしまいます。";
		mes "みんな死んでしまいますよ。";
		next;
		mes "‐どうも会話が成立しそうにない。‐";
		next;
		delquest 16099;
		if(checkquest(16097) == 0 && checkquest(16098) == 0 && checkquest(16099) == 0) {
			mes "‐あの少女が教えてくれた";
			mes "　場所が^0000CDもう一か所^000000ある。";
			mes "　^0000CD薄暗い久陽宮^000000と言っていたので";
			mes "　捜してみよう。-";
			setquest 16100;
			set IL_TUR_QUE,3;
			close;
		}
		mes "‐あの少女が教えてくれた";
		mes "　場所がまだある。";
		mes "　他の場所へ行ってみよう。";
		close;
	case 5:
		donpcevent "元気のない女#illtur01::OnTalk"+ rand(1,3);
		cloakoffnpc "考古学者イエルフェン#i2";
		mes "[考古学者イエルフェン]";
		mes "この周辺ですか？";
		mes "何度か来た場所ですが……。";
		next;
		mes "[元気のない女]";
		mes "ひもじいです。腹が減り過ぎました。";
		mes "このままじゃ死んじゃいます……。";
		mes "どうか、どうか助けて。";
		next;
		menu "この方です",-;
		mes "[考古学者イエルフェン]";
		mes "……あの、冒険者様。";
		mes "今、誰と話してますか？";
		mes "ここには僕たち二人以外";
		mes "誰もいませんが。";
		next;
		unittalk getnpcid(0,"元気のない女#illtur01"),"あは、見つけた。";
		cloakonnpc "元気のない女#illtur01";
		misceffect 563,"怨霊#illtur01";
		misceffect 847,"怨霊#illtur01";
		cloakoffnpc "怨霊#illtur01";
		next;
		misceffect 563,"怨霊#illtur02";
		misceffect 847,"怨霊#illtur02";
		cloakoffnpc "怨霊#illtur02";
		sc_start3 SC_BLIND,0,0,0,0,10000,10;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur02"),"見つけた。";
		misceffect 847,"怨霊#illtur03";
		cloakoffnpc "怨霊#illtur03";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur03"),"息をする者だ。";
		misceffect 563,"怨霊#illtur04";
		misceffect 847,"怨霊#illtur04";
		cloakoffnpc "怨霊#illtur04";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur04"),"生きてる者を見つけた。";
		misceffect 847,"怨霊#illtur05";
		cloakoffnpc "怨霊#illtur05";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur05"),"捕まえて！";
		misceffect 847,"怨霊#illtur06";
		cloakoffnpc "怨霊#illtur06";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur06"),"殺せ！";
		misceffect 563,"怨霊#illtur07";
		misceffect 847,"怨霊#illtur07";
		cloakoffnpc "怨霊#illtur07";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur07"),"バラバラにしろ！";
		mes "[考古学者イエルフェン]";
		mes "うあ……ああああ！";
		mes "なんだよこれは！";
		next;
		sc_end SC_BLIND;
		cloakoffnpc "少女#illtur02";
		mes "[少女]";
		mes "これを噛んで。";
		mes "しーっ、静かに！";
		mes "息を止めて。";
		mes "そこの学者さんも。";
		next;
		menu "これは亀の甲羅の欠片？",-;
		misceffect 120,"";
		unittalk getnpcid(0,"考古学者イエルフェン#i2"),"イエルフェン : またあらわれまびた？このびどはだででづか？";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"少女#illtur02"),"少女 : 息、止めて！喋らない！";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"考古学者イエルフェン#i2"),"イエルフェン : はっ……。";
		misceffect 120,"考古学者イエルフェン#i2";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"怨霊#illtur01"),"どこへ行った？";
		unittalk getnpcid(0,"怨霊#illtur03"),"生きた者たちが消えた。";
		unittalk getnpcid(0,"怨霊#illtur05"),"消えてしまった。";
		unittalk getnpcid(0,"怨霊#illtur07"),"どうやって消えた？";
		unittalk getnpcid(0,"怨霊#illtur04"),"誰の仕業だ？";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"怨霊#illtur02"),"消えてしまった！";
		unittalk getnpcid(0,"怨霊#illtur06"),"消えた。完全に消えちゃった！";
		unittalk getnpcid(0,"怨霊#illtur04"),"生きてる者たち、ハッキリ見たのに？";
		unittalk getnpcid(0,"怨霊#illtur03"),"見つけたのに、私が見つけ出したのに！";
		unittalk getnpcid(0,"怨霊#illtur05"),"バラバラにしなくちゃ！";
		if(!sleep2(1000)) end;
		mes "[少女]";
		mes "私も、もう二人の姿が見えない。";
		mes "……どこかへ行っちゃダメ。";
		mes "小さい声で話すから。";
		mes "……そこにいるよね？";
		next;
		mes "[少女]";
		mes "側に……いるよね？";
		mes "信じて。話をする。";
		mes "一度だけ言うからよく聞いて。";
		next;
		mes "[少女]";
		mes "それを口に噛み";
		mes "吐息を漏らさない限り、ばれない。";
		mes "出来る限り早くここから抜け出して。";
		mes "さっき私のいた場所へ戻って。";
		next;
		mes "[少女]";
		mes "私と最初に出逢った場所、覚えてる？";
		mes "待ってる。";
		next;
		unittalk getnpcid(0,"怨霊#illtur04"),"いない。生きてる者たちがいない。";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur04";
		cloakonnpc "怨霊#illtur04";
		unittalk getnpcid(0,"怨霊#illtur02"),"いない、我が子…";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur02";
		cloakonnpc "怨霊#illtur02";
		unittalk getnpcid(0,"怨霊#illtur06"),"ここは死んだ者しかいない。";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur06";
		cloakonnpc "怨霊#illtur06";
		unittalk getnpcid(0,"怨霊#illtur03"),"俺の宝物…";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur03";
		cloakonnpc "怨霊#illtur03";
		unittalk getnpcid(0,"少女#illtur02"),"帰ろう、みんな。";
		if(!sleep2(1000)) end;
		cloakonnpc "少女#illtur02";
		unittalk getnpcid(0,"怨霊#illtur01"),"ひもじい…ひもじい。";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur01";
		cloakonnpc "怨霊#illtur01";
		cloakoffnpc "元気のない女#illtur01";
		unittalk getnpcid(0,"怨霊#illtur07"),"いつもそうだったように。";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur07";
		cloakonnpc "怨霊#illtur07";
		unittalk getnpcid(0,"怨霊#illtur05"),"死人だけだ…";
		if(!sleep2(1000)) end;
		misceffect 847,"怨霊#illtur05";
		cloakonnpc "怨霊#illtur05";
		if(!sleep2(3000)) end;
		menu "あの子を信じましょう",-;
		mes "‐^424242イエルフェン教授は";
		mes "　息を止めたまま、頷いた。^000000‐";
		chgquest 16103,16104;
		set IL_TUR_QUE,6;
		close2;
		cloakonnpc "考古学者イエルフェン#i2";
		end;
	}
	end;
OnTalk1:
	sleep 3000;
	unittalk "元気のない女 : 助けてください。ひもじいです。どうか助けてください。";
	sleep 3000;
	unittalk "元気のない女 : もう何でも食べますから。どうか何でも恵んでください。";
	sleep 3000;
	end;
OnTalk2:
	sleep 3000;
	unittalk "元気のない女 : ひもじいです。ひもじいです。どうか助けてください。";
	sleep 3000;
	unittalk "元気のない女 : このままじゃ死んでしまいます。死んでしまいます。死にます。";
	sleep 3000;
	end;
OnTalk3:
	sleep 3000;
	unittalk "元気のない女 : 飢え死になってしまいます。何か食べないと。死にます。";
	sleep 3000;
	unittalk "元気のない女 : ひもじいです。どうか助けてください。どうか……";
	sleep 3000;
	end;
}

tur_d03_i.gat,147,170,7	script	#illturg11	844,{
	mes "["+strcharinfo(0)+"]";
	mes "何か見えた気がしたけど…";
	close;
}
tur_d03_i.gat,137,170,0	script	#illturgg11	139,10,10,{
	setnpcdisplay "#illturg11",796;
	unittalk getnpcid(0,"#illturg11"),"ここどこ？みんなどこへ行った？";
	sleep 1000;
	setnpcdisplay "#illturg11",844;
	unittalk getnpcid(0,"#illturg11"),"喉が渇いた……喉が。";
	end;
}

tur_d03_i.gat,142,229,1	script	#illturg12	844,{
	mes "["+strcharinfo(0)+"]";
	mes "ちょっと寒気がするようだ。";
	close;
}
tur_d03_i.gat,146,223,0	script	#illturgg12	139,10,10,{
	setnpcdisplay "#illturg12",792;
	unittalk getnpcid(0,"#illturg12"),"嘘つき、嘘つき。";
	sleep 1000;
	setnpcdisplay "#illturg12",844;
	unittalk getnpcid(0,"#illturg12"),"帰ってくると言ったのに？";
	end;
}

tur_d03_i.gat,214,105,7	script	#illturg13	844,{
	mes "["+strcharinfo(0)+"]";
	mes "気分がおかしい…";
	close;
}
tur_d03_i.gat,207,104,0	script	#illturgg13	139,10,10,{
	setnpcdisplay "#illturg13",792;
	unittalk getnpcid(0,"#illturg13"),"あは、あははは、あはは……";
	sleep 1000;
	setnpcdisplay "#illturg13",844;
	unittalk getnpcid(0,"#illturg13"),"あはは……は……ふ、ふええん……";
	end;
}

tur_d04_i.gat,99,153,7	script	#illturg21	844,{
	mes "‐気のせいか。‐";
	close;
}
tur_d04_i.gat,99,160,0	script	#illturgg21	139,10,10,{
	setnpcdisplay "#illturg21",792;
	unittalk getnpcid(0,"#illturg21"),"ここはどこ？隊長はどこへ行った？";
	sleep 1000;
	setnpcdisplay "#illturg21",844;
	unittalk getnpcid(0,"#illturg21"),"誰かいるか？そこ誰だ？";
	end;
}
tur_d04_i.gat,37,137,7	script	#illturg22	844,{
	mes "‐何かを感じるが誰もいないようだ。‐";
	close;
}
tur_d04_i.gat,45,137,0	script	#illturgg22	139,{
	setnpcdisplay "#illturg22",796;
	unittalk getnpcid(0,"#illturg22"),"はあ、はあ、寒い……帰りたい……";
	sleep 1000;
	setnpcdisplay "#illturg22",844;
	unittalk getnpcid(0,"#illturg22"),"誰もいませんか？誰も……？";
	end;
}

tur_d04_i.gat,76,35,7	script	#illturg23	844,{
	mes "‐気分が悪くなった。‐";
	close;
}
tur_d04_i.gat,69,31,0	script	#illturgg23	139,{
	setnpcdisplay "#illturg23",792;
	setnpcdisplay "#illturg23",844;
	unittalk getnpcid(0,"#illturg23"),"あはははははははははははははは";
}

tur_d04_i.gat,135,133,1	script	#illturg24	844,{
	mes "‐何か声が聞こえた気がした。‐";
	close;
}
tur_d04_i.gat,137,126,0	script	#illturgg24	139,{
	setnpcdisplay "#illturg24",796;
	unittalk getnpcid(0,"#illturg24"),"待ってた？私を待ってくれた？";
	sleep 1000;
	setnpcdisplay "#illturg24",844;
	unittalk getnpcid(0,"#illturg24"),"遅い、もう遅い。";
	end;
}

tur_d04_i.gat,26,167,0	script	#illtur01	139,15,15,{
	if(IL_TUR_QUE == 3 || IL_TUR_QUE == 4)
		cloakoffnpc "考古学者イエルフェン#t2";
	end;
}
tur_d04_i.gat,26,167,5	script	考古学者イエルフェン#t2	740,{
	switch(IL_TUR_QUE) {
	case 3:
		emotion 0;
		mes "[考古学者イエルフェン]";
		mes "信じられない……人間、人間ですよね？";
		mes "本当に人間ですよね？";
		mes "……僕を助けに？";
		mes "ありがとうございます。";
		mes "ここで野垂れ死ぬかと思いましたよ！";
		next;
		mes "[考古学者イエルフェン]";
		mes "しかし、僕を";
		mes "どこで知ったんですか？";
		next;
		menu "エイルバルさんから聞きました",-;
		mes "[考古学者イエルフェン]";
		mes strcharinfo(0)+"さんと仰るのですね。";
		mes "ふう……エイルバルと";
		mes strcharinfo(0)+"さんがいなかったら、";
		mes "本当に死ぬところでした。";
		mes "^FF0000何日も^000000ろくに眠れず食べれないまま、";
		mes "彷徨っていましたから。";
		next;
		mes "[考古学者イエルフェン]";
		mes "僕が消えたのが半日前のことだと？";
		mes "それはおかしいですね。";
		mes "……いや、あり得るかもしれません。";
		mes "少なくともここは僕たちの知る";
		mes "タートルアイランドではありません。";
		next;
		mes "[考古学者イエルフェン]";
		mes "エイルバルから話は聞きましたか？";
		mes "僕も最初は半信半疑でしたが";
		mes "どうやら、ここはエイルバルの話した";
		mes "妙にぞっとするところで";
		mes "間違いないようです。";
		next;
		mes "[考古学者イエルフェン]";
		mes "もしかしたら時の流れさえも";
		mes "我々のいた場所とは";
		mes "違う空間である可能性があります。";
		next;
		mes "[考古学者イエルフェン]";
		mes "調査したいことが多すぎますが";
		mes "一端、元の場所に戻りましょう。";
		mes "あまりに疲れ果ててますし";
		mes "まともに記録を残す道具も無いので";
		mes "集めてきます。";
		next;
		emotion 32;
		mes "[考古学者イエルフェン]";
		mes "ここに戻るつもりかって？";
		mes "もちろん戻ります。";
		mes "タートルアイランドの歴史について";
		mes "新しい事実が究明されるかも知れませんよ。";
		next;
		mes "‐戻ろうとしたその時、";
		mes "　ぐぅぅと重たい大きな音が";
		mes "　イエルフェンのお腹から";
		mes "　鳴り響いた。‐";
		next;
		emotion 4;
		mes "[考古学者イエルフェン]";
		mes "う、うう……";
		mes "すみません。どうしても腹が減って……";
		mes "とても歩けそうにありません。";
		mes "もしよろしければ、この辺のモンスターを";
		mes "少し狩って持ってきてくれませんか？";
		next;
		mes "[考古学者イエルフェン]";
		mes "調査が長引くと、何食かは";
		mes "現地で調達できるようになります。";
		mes "ここにはモンスターしかいませんが";
		mes "本質は亀ですから十分食べれるはずです。";
		next;
		mes "[考古学者イエルフェン]";
		mes "しかし残念ながら";
		mes "僕1人では狩れませんでした。";
		mes "こちらのモンスターたちは、";
		mes "僕たちの知ってる";
		mes "タートルアイランドのものより";
		mes "ずっと強かったからです。";
		next;
		mes "[考古学者イエルフェン]";
		mes "それでも僕を探しに";
		mes "ここまで来れた";
		mes strcharinfo(0)+"様なら";
		mes "倒せるのではないでしょうか。";
		mes "お願いしても宜しいですか？";
		next;
		mes "[考古学者イエルフェン]";
		mes "もしモンスター狩りが";
		mes "面倒そうでしたら";
		mes "僕を背負ってもらっても";
		mes "大丈夫ですよ。";
		next;
		menu "どのモンスターを狩ってきましょうか？",-;
		mes "[考古学者イエルフェン]";
		mes "快く受諾していただき";
		mes "ありがとうございます。";
		mes "^0000CD不吉なフリーズタートルと";
		mes "不吉なヒートタートル^000000を";
		mes "^0000CD各1体ずつ^000000狩って来てください。";
		next;
		mes "[考古学者イエルフェン]";
		mes "そして^0000CDそこから得られる";
		mes "お肉^000000も^0000CD1個^000000お願いします。";
		next;
		mes "[考古学者イエルフェン]";
		mes "その間、僕は火を熾してみます。";
		mes "いきなりサバイバルに挑むことになるとは。";
		mes "僕は考古学者であり";
		mes "物語の主人公ではないのに。";
		chgquest 16100,16102;
		set IL_TUR_QUE,4;
		close;
	case 4:
		if(checkquest(16102) & 0x4 == 0 || countitem(7564) < 1) {
			mes "[考古学者イエルフェン]";
			mes "うまく火が付きませんね。";
			mes "本や家具を燃やす訳にも";
			mes "いきませんし。";
			next;
			mes "[考古学者イエルフェン]";
			mes "^0000CD腐った肉^000000でも";
			mes "構いませんから^0000CD1個^000000お願いします。";
			mes "何か食べないと、一歩も";
			mes "動けそうにもありません……。";
			close;
		}
		unittalk "あ、お帰りなさい、"+strcharinfo(0)+"様。";
		mes "[考古学者イエルフェン]";
		mes "あ、お帰りなさい";
		mes strcharinfo(0)+"様。";
		mes "困ったことに";
		mes "燃やせそうな物が無かったもので";
		mes "結局、火を熾せませんでした。";
		next;
		mes "[考古学者イエルフェン]";
		mes "え？モンスターの肉が";
		mes "全部腐っていたのですか？";
		mes "おかしいですね。";
		mes "生きてるモンスターを倒したのに、";
		mes "何故腐った肉が出るのでしょう？";
		next;
		mes "[考古学者イエルフェン]";
		mes "火も通していない腐った肉か……";
		mes "それでも食べれば";
		mes "エネルギーにはなるでしょう！";
		mes "もぐもぐ……";
		mes "う、うええ……";
		mes "ぺっぺっ！";
		next;
		emotion 28;
		mes "[考古学者イエルフェン]";
		mes "うぐ……申し訳ありません……";
		mes "とても食えるものではありませんね。";
		mes "無駄骨を折らせてしまいました。";
		next;
		mes "[考古学者イエルフェン]";
		mes "ふう。こちらは僕と冒険者さま以外に";
		mes "誰もいないですよね？";
		mes "何日も歩き回ったんですが";
		mes "^FF0000たった1人にも会えませんでした^000000。";
		mes "誰かが住んでいたら";
		mes "助けを求めたのですが。";
		next;
		emotion 23;
		mes "[考古学者イエルフェン]";
		mes "本当ですか、人間が住んでいると？";
		mes "住民たちを見たのですね？";
		mes "いやぁ、早く話してくだされば";
		mes "良かったのに。";
		next;
		mes "[考古学者イエルフェン]";
		mes "どこで見ましたか？";
		mes "今すぐ行って話を聞いてみましょう！";
		mes "聞きたいことが多いです！";
		next;
		mes "[考古学者イエルフェン]";
		mes "歩けない？何を言ってるんですか。";
		mes "早く行きましょう！";
		mes "ちょっと変わった人々ばかりで";
		mes "言葉が通じるか分からなかった？";
		mes "それなら大丈夫です。";
		next;
		mes "[考古学者イエルフェン]";
		mes "もし言葉が通じなくとも";
		mes "人々の生活する姿を見ると";
		mes "分かることは多いですから。";
		mes "さぁ早く行きましょう！";
		mes "案内お願いします。";
		mes "一番近い場所から！";
		next;
		mes "[考古学者イエルフェン]";
		mes "あ、この腐った肉は";
		mes "お返しします。";
		mes "僕の歯形が付いて";
		mes "しまっていますが";
		mes "商人に売る分には";
		mes "問題ないでしょう。";
		next;
		emotion 20,"";
		mes "‐^FF0000元気のない女^000000のところまで";
		mes "　イエルフェンを案内しよう。‐";
		chgquest 16102,16103;
		set IL_TUR_QUE,5;
		close;
	case 5:
		mes "[考古学者イエルフェン]";
		mes "いやぁこんな場所があるなんて。";
		mes "世界はまだまだ";
		mes "未知で溢れてますね！";
		close;
	}
	end;
OnInit:
	cloakonnpc;
	end;
}

tur_d04_i.gat,100,112,3	script	少女#illtur02	10238,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,101,110,3	script	考古学者イエルフェン#i2	740,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,96,112,5	script	怨霊#illtur01	792,{
	unittalk "私は…何をしていたんだろ…";
	if(!sleep2(3000)) end;
	cloakonnpc "怨霊#illtur01";
	cloakonnpc "怨霊#illtur02";
	cloakonnpc "怨霊#illtur03";
	cloakonnpc "怨霊#illtur04";
	cloakonnpc "怨霊#illtur05";
	cloakonnpc "怨霊#illtur06";
	cloakonnpc "怨霊#illtur07";
	if(!sleep2(1000)) end;
	cloakoffnpc "元気のない女#illtur01";
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,94,108,7	script	怨霊#illtur02	796,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,91,111,5	script	怨霊#illtur03	792,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,97,104,7	script	怨霊#illtur04	792,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,107,109,3	script	怨霊#illtur05	792,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,104,112,3	script	怨霊#illtur06	796,{
	end;
OnInit:
	cloakonnpc;
	end;
}
tur_d04_i.gat,102,102,1	script	怨霊#illtur07	796,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//============================================================
// ダンジョンNPC
//------------------------------------------------------------
tur_d03_j.gat,132,194,3	script	光の群れ#illtur02	10042,{
	if(select("アルベルタに戻る","ここに残る") == 2) {
		mes "‐まだここで";
		mes "　やるべきことが残ってる。‐";
		close;
	}
	warp "alberta.gat",219,31;
	end;
}

tur_d03_j.gat,139,186,3	script	ナリン#illtur01	10238,{
	if(checkquest(16105))
		delquest 16105;
	if(checkquest(16108)) {
		if(checkquest(16108)&0x2 == 0) {
			mes "[ナリン]";
			mes (Sex? "兄": "姉")+ "さん……まだいたの？";
			mes "呪術は一日過ぎたら";
			mes "消えてしまうから……";
			mes "^4d4dff次の午前5時を過ぎたら^000000";
			mes "また来て。";
			next;
			mes "[ナリン]";
			mes "私が" +(Sex? "兄": "姉")+ "さんを忘れたとしても";
			mes "避けちゃダメ。";
			mes "……絶対、絶対だよ。";
			close;
		}
		delquest 16108;
	}
	if(checkquest(16107)) {
		if(checkquest(16110) == 0 && checkquest(16113) == 0) {
			mes "[ナリン]";
			mes "悲しみの陽居村にいる";
			mes "^4d4dff細かい軍人^000000か";
			mes "薄暗い久陽宮にいる";
			mes "^4d4dff元気のない女^000000の";
			mes "願いごとを叶えてあげて。";
			next;
			mes "[ナリン]";
			mes (Sex? "兄": "姉")+ "さん。";
			mes "気を付けてね。";
			close;
		}
		cloakoffnpc "考古学者イエルフェン#i3";
		mes "[ナリン]";
		mes "彼らの願いごとを";
		mes "叶えてくれたんだね。";
		mes "ありがとう" +(Sex? "兄": "姉")+ "さん。";
		next;
		mes "[ナリン]";
		mes "これは今日の約束の証。";
		mes "教授、" +(Sex? "兄": "姉")+ "さん。";
		mes "また来てくれて……ありがとう。";
		mes "明日も待ってるから。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"考古学者イエルフェン#i3"),"イエルフェン : また明日、ナリンさん。";
		close2;
		if(checkquest(16110))
			delquest 16110;
		if(checkquest(16113))
			delquest 16113;
		delquest 16107;
		setquest 16108;
		getitem 25271,2;
		getexp 100000000,0,1;
		getexp 0,20000000,0;
		if(!sleep2(1000)) end;
		cloakonnpc "考古学者イエルフェン#i3";
		end;
	}
	if(select("急いで話す(会話スキップ)","ゆっくり話す") == 2) {
		mes "[少女]";
		mes "見知らぬ人。";
		mes "危険な目にあう前に";
		mes "ここから出てって。";
		next;
		mes "[ナリン]";
		mes "……また誰か来た。";
		next;
		cloakoffnpc "考古学者イエルフェン#i3";
		mes "[考古学者イエルフェン]";
		mes "僕も来ました。";
		mes "お元気でしたか？";
		mes "ナリンさん。";
		next;
		mes "[ナリン]";
		mes "……。";
		next;
		mes "[ナリン]";
		mes "…………。";
		next;
		mes "[ナリン]";
		mes "……………………。";
		next;
		mes "[ナリン]";
		mes "……………………うう。";
		next;
		emotion 4;
		mes "[ナリン]";
		mes "……また……";
		mes "忘れてしまった……。";
		next;
		mes "[ナリン]";
		mes "私、覚えてる間は";
		mes "ずっと待っていた……確かに。";
		mes "ありがとう……";
		mes "また来てくれて、嬉しい。";
		next;
		mes "[ナリン]";
		mes "……そうだ";
		mes "呪術をかけてあげる。";
		mes "今日も他の人のとこ行くよね？";
		next;
		mes "[ナリン]";
		mes "悲しみの陽居村にいる";
		mes "^4d4dff細かい軍人^000000か";
		mes "薄暗い久陽宮にいる";
		mes "^4d4dff元気のない女^000000の";
		mes "願いごとを叶えてあげて。";
		next;
	}
	else {
		cloakoffnpc "考古学者イエルフェン#i3";
	}
	mes "[ナリン]";
	mes "今日も二人が無事なように……。";
	misceffect 778;
	if(!sleep2(1000)) end;
	misceffect 778,"";
	misceffect 778,"考古学者イエルフェン#i3";
	misceffect 877,"";
	misceffect 877,"考古学者イエルフェン#i3";
	setquest 16107;
	if(!sleep2(1000)) end;
	cloakonnpc "考古学者イエルフェン#i3";
	close;
}

tur_d03_j.gat,136,187,5	script	考古学者イエルフェン#i3	740,{
	end;
OnInit:
	cloakonnpc;
	end;
}

tur_d03_j.gat,80,180,1	script	気の早い男#illtur02	10239,{
	mes "[気の早い男]";
	mes "なくしちゃった、なくしちゃった。";
	mes "我が子。我が愛しい子。";
	mes "どこへ行ったの？我が子。";
	mes "名前が何だったの我が娘。";
	mes "娘？我が子。";
	next;
	mes "[気の早い男]";
	mes "誰だ？";
	mes "我が子、誰だ？";
	close;
}

tur_d03_j.gat,235,187,7	script	細かい軍人#illtur02	10240,{
	if(checkquest(16110)) {
		mes "[細かい軍人]";
		mes "ふ……ふふ……ふふ^BDBDBDふ^000000ふ……";
		mes "ふふ^BDBDBDふ^000000ふふふ……。";
		mes "ピカピカ……ピカピカする……";
		mes "綺麗、とっても綺麗だ。";
		next;
		mes "‐ぼろぼろの金属片に";
		mes "　夢中なようだ。‐";
		close;
	}
	if(checkquest(16109)) {
		if(checkquest(16109)&0x4 == 0 || countitem(25316) < 10) {
			misceffect 563;
			mes "[細かい軍人]";
			mes "^FF0000足りない!!^000000";
			next;
			mes "[細かい軍人]";
			mes "^FF0000俺の、宝物……俺の復讐……。";
			mes "足りない、足りない!!^000000";
			next;
			mes "‐不吉なヒートタートル、";
			mes "　不吉なフリーズタートルを";
			mes "　10体討伐し、ぼろぼろの金属片を";
			mes "　10個持ってこよう。‐";
			close;
		}
		mes "[細かい軍人]";
		mes "復讐した？あの忌々しい^BDBDBD奴ら^000000に？";
		mes "そして俺の、宝物……^FF0000ブツブツ^000000、ブツ";
		mes "……宝物も持って^BDBDBDき^000000た？";
		next;
		misceffect 563;
		mes "[細かい軍人]";
		mes "^FF0000早く寄こせ^000000！俺の宝物！";
		next;
		mes "[細かい軍人]";
		mes "ふ……ふふ……ふふ^BDBDBDふ^000000ふ……";
		mes "ふふ^BDBDBDふ^000000ふふふ……。";
		mes "ピカピカ……ピカピカする……";
		mes "綺麗、とっても綺麗だ。";
		delitem 25316,10;
		delquest 16109;
		setquest 16110;
		close;
	}
	if(checkquest(16107)) {
		mes "[細かい軍人]";
		mes "クスクス……^FF0000ブツ^000000、ブツ。";
		mes "^FF0000クスクス^000000……。";
		mes "あのく^BDBDBDそ^000000みたいな";
		mes "モン^BDBDBDス^000000ターさえいなかったら……。";
		next;
		mes "[細かい軍人]";
		mes "ぜ……全部、俺の物に^BDBDBDなれ^000000た^BDBDBDはず^000000なのに……。";
		mes "お……俺の宝^BDBDBD物^000000が……";
		mes "^FF0000クスクス^000000……。";
		next;
		menu "私が取り戻しましょう",-;
		mes "[細かい軍人]";
		mes "お前が？お前^BDBDBDが^000000行くだと？";
		mes "行って^BDBDBD取り^000000戻せ！";
		mes "俺の宝^BDBDBD物^000000！";
		mes "奴らが持っているはずだ！";
		mes "大事な宝物^BDBDBD^000000！";
		next;
		mes "[細かい軍人]";
		mes "それと^0000CD不吉なヒートタートル^000000と";
		mes "^0000CD不吉なフリーズタートル^000000を";
		mes "10体……消せ！消し^BDBDBDて^000000しまえ!!";
		mes "消し^BDBDBDて^000000しまえ!!";
		next;
		if(select("分かりました","また後で") == 2) {
			mes "[細かい軍人]";
			mes "クスクス……";
			mes "^FF0000ブツ^000000、ブツ。^FF0000クスクス^000000……";
			mes "あのく^BDBDBDそ^000000みたいな";
			mes "モン^BDBDBDス^000000ターさえいなかったら……。";
			next;
			mes "[細かい軍人]";
			mes "ぜ……全部、俺の物に";
			mes "^BDBDBDなっ^000000た^BDBDBDはず^000000なのに……";
			mes "お…俺の宝^BDBDBD物^000000が……";
			mes "^FF0000クスクス^000000……。";
			close;
		}
		mes "[細かい軍人]";
		mes "^FF0000復讐^000000……クスクス";
		mes "……俺の復讐^BDBDBDも^000000してくれ……。";
		setquest 16109;
		close;
	}
	mes "[細かい軍人]";
	mes "い^BDBDBDた^000000よ……生き^BDBDBDて^000000いたぞ……畜生！";
	mes "^BDBDBD生き^000000ている?!俺は！";
	mes "俺は死んだ^BDBDBDの^000000に！";
	mes "ゆるさ^BDBDBDない^000000！探し^BDBDBD出し^000000て";
	mes "^BDBDBD殺^000000してやる!!";
	mes "^FF0000クス^000000……クスクス……。";
	close;
}

tur_d04_j.gat,96,112,1	script	元気のない女#illtur02	10241,{
	if(checkquest(16113)) {
		mes "[元気のない女]";
		mes "ああ、もう腹いっぱい。";
		mes "これで死なない。もう腹いっぱい。";
		mes "ありがとう。";
		next;
		mes "‐今はお腹いっぱいで";
		mes "　満足しているようだ。‐";
		close;
	}
	if(checkquest(16111)) {
		if(checkquest(16111)&0x4 == 0 || countitem(7564) < 10) {
			mes "[元気のない女]";
			mes "狩りをお願いします。";
			mes "タートルたちを。";
			mes "^0000CD不吉なアサルトタートル、";
			mes "不吉なPタートルを10体ずつ。^000000";
			mes "持ってきてください。";
			mes "^0000CD腐った肉を10個。^000000";
			close;
		}
		mes "[元気のない女]";
		mes "ああ、お肉の匂いだ。";
		mes "お肉の匂い。";
		mes "美味しそう、とっても美味しそう。";
		mes "早くください。";
		mes "ひもじいです。早く。";
		next;
		mes "[元気のない女]";
		mes "コツッ、バリ、バリバリ";
		mes "くちゃくちゃ、ごっくり……。";
		mes "ああ、もう腹いっぱい。";
		mes "これで死なない。もう腹いっぱい。";
		mes "ありがとう。";
		delitem 7564,10;
		delquest 16111;
		setquest 16113;
		close;
	}
	if(checkquest(16107)) {
		mes "[元気のない女]";
		mes "ひもじいです。";
		mes "助けてください、どうか。";
		mes "ひもじいです。";
		next;
		menu "どうしたらいいですか？",-;
		mes "[元気のない女]";
		mes "助けてくれますか？本当に？";
		mes "飢えて死なないように";
		mes "助けてくれますか？";
		next;
		mes "[元気のない女]";
		mes "それなら狩りをお願いします。";
		mes "タートルたちを。";
		mes "^0000CD不吉なアサルトタートル^000000、";
		mes "^0000CD不吉なパーメットタートル^000000を10体ずつ。";
		mes "持ってきてください。";
		mes "^0000CD腐った肉を10個。^000000";
		next;
		if(select("分かりました","また後で") == 2) {
			mes "[元気のない女]";
			mes "それでは私、死んじゃいます。";
			mes "すぐ飢えて死にます。";
			next;
			mes "[元気のない女]";
			mes "^FF0000何でも食べるのに。";
			mes "本当に何でも食べれるのに。";
			mes "かりかりぽりぽりと";
			mes "噛み砕き吸い込んで食べれるのに。^000000";
			close;
		}
		mes "[元気のない女]";
		mes "ありがとう。";
		mes "肉、食べたら死にません。";
		mes "もっと生きれます。";
		mes "もっと……もっと";
		mes "生きていけますよ。";
		setquest 16111;
		close;
	}
	mes "[元気のない女]";
	mes "ひもじいです。";
	mes "ひもじくて";
	mes "動けそうにもありません。";
	mes "どうか……どうか";
	mes "慈悲を恵んでください。";
	mes "あまりにも長く飢えてます……。";
	next;
	mes "‐話しかけるのは危険そうだ。";
	mes "　先にナリンに呪術を";
	mes "　掛けてもらってこよう。‐";
	close;
}

tur_d04_j.gat,26,167,5	script	考古学者イエルフェン#i4	740,{
	mes "[考古学者イエルフェン]";
	mes "こんにちは";
	mes strcharinfo(0)+"さん。";
	mes "今日も来ましたね。";
	next;
	mes "[考古学者イエルフェン]";
	mes "ご飯と睡眠はアルベルタで";
	mes "とるようにしています。";
	mes "ここの正体を解き明かすまでは";
	mes "ジュノーに戻るつもりは";
	mes "ありませんからね。";
	next;
	emotion 4,"";
	mes "[考古学者イエルフェン]";
	mes "あ、そういえば";
	mes "言い忘れましたが";
	mes "僕は長期休暇中ですので";
	mes "授業の心配はありませんよ。";
	close;
}

tur_d03_j.gat,0,0,0	script	#IllTurtleIsland01	-1,{
OnInit:
	for(set '@i,0;'@i<10;set '@i,'@i+1)
		areamonster "tur_d03_j.gat",0,0,0,0,"--ja--",rand(2)? 3801: 3803,1,strnpcinfo(0)+"::OnSummon";
	end;
OnSummon:
	if('mob == 0 && rand(500) == 0) {
		set 'mob,areacallmonster("tur_d03_j.gat",0,0,0,0,"不吉なソリッドタートル",3802,strnpcinfo(0)+"::OnKilled");
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		mobuseskillpos 'mob,21,10,'@x,'@y,0,0;	// サンダーストーム
		mobuseskill 'mob,730,1,0,0,0,1;	// M呪縛陣
		unittalk 'mob,"不吉なソリッドタートル : ……。";
	}
	else {
		areamonster "tur_d03_j.gat",0,0,0,0,"--ja--",rand(2)? 3801: 3803,1,strnpcinfo(0)+"::OnSummon";
	}
	end;
OnKilled:
	set 'mob,0;
	areamonster "tur_d03_j.gat",0,0,0,0,"--ja--",rand(2)? 3801: 3803,1,strnpcinfo(0)+"::OnSummon";
	end;
}

tur_d04_j.gat,0,0,0	script	#IllTurtleIsland02	-1,{
OnInit:
	for(set '@i,0;'@i<10;set '@i,'@i+1)
		areamonster "tur_d04_j.gat",0,0,0,0,"--ja--",rand(2)? 3799: 3800,1,strnpcinfo(0)+"::OnSummon";
	end;
OnSummon:
	if('mob == 0 && rand(500) == 0) {
		set 'mob,areacallmonster("tur_d04_j.gat",0,0,0,0,"不吉なソリッドタートル",3802,strnpcinfo(0)+"::OnKilled");
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
		mobuseskillpos 'mob,21,10,'@x,'@y,0,0;	// サンダーストーム
		mobuseskill 'mob,730,1,0,0,0,1;	// M呪縛陣
		unittalk 'mob,"不吉なソリッドタートル : ……。";
	}
	else {
		areamonster "tur_d04_j.gat",0,0,0,0,"--ja--",rand(2)? 3799: 3800,1,strnpcinfo(0)+"::OnSummon";
	}
	end;
OnKilled:
	set 'mob,0;
	areamonster "tur_d04_j.gat",0,0,0,0,"--ja--",rand(2)? 3799: 3800,1,strnpcinfo(0)+"::OnSummon";
	end;
}
