//==============================================================================
// Ragnarok Online Halloween2006 Script
//==============================================================================

//==========================================
// パンプキンハットクエスト
//------------------------------------------
prontera.gat,164,69,3	script	素敵なデビ	738,{
	mes "-憂鬱なジャックが";
	mes "理解できない言葉で";
	mes "話しかけてきている-";
	next;
	mes "[素敵なデビ]";
	mes "何言ってるかわからないだろ？";
	mes "俺が通訳してやるよ。";
	mes "ま、そのためにこいつに";
	mes "ついてきてやったんだけどな。";
	next;
	mes "-憂鬱なジャックが";
	mes "理解できない言葉で";
	mes "デビルチと話している-";
	next;
	if(countitem(7609)) {
		mes "[素敵なデビ]";
		mes "「君が持っているのは";
		mes "僕の心じゃないかな？";
		mes "それを返してくれたら";
		mes "何かお礼をするけど……」";
		mes "ってこいつが言ってるぜ。";
		next;
		mes "[素敵なデビ]";
		mes "どうする？";
		mes "こいつの事情を説明してほしいか？";
		next;
		if(select("事情って？","いえ、知っています")==2) {
			if(countitem(535) < 1 || countitem(2226) < 1) {
				mes "[素敵なデビ]";
				mes "ん？";
				mes "パンプキンハットを作るには";
				mes "材料が足りないみたいだぜ？";
				close;
			}
			mes "[素敵なデビ]";
			mes "それをジャックに返してやったら、";
			mes "カボチャと普通のキャップを";
			mes "パンプキンハットにしてくれるぜ。";
			next;
			if(select("やだ","はい、どうぞ")==1) {
				mes "[素敵なデビ]";
				mes "……冗談だよな？";
				mes "後でそれをジャックに";
				mes "返してやるんだよな？";
				close;
			}
			delitem 7609,1;
			delitem 535,1;
			delitem 2226,1;
			getitem 5202,1;
			misceffect 200,"憂鬱なジャック";
			mes "-ジャックの元に";
			mes "ハロウィンジャックの証である";
			mes "オーラが戻ってきた-";
			next;
			misceffect 1,"憂鬱なジャック";
			mes "[素敵なデビ]";
			mes "ん？　オーラが不安定だな……";
			mes "まだ心が足りないんだろ。";
			next;
			mes "[素敵なデビ]";
			mes "ま、いつかは完全に取り戻せるだろ。";
			mes "気長に集めるんだな。";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "事情って？";
		next;
	}
	else {
		mes "[素敵なデビ]";
		mes "「昔……僕はね……";
		mes "ハロウィンジャックだったの……";
		mes "……でも、今は……」";
		next;
		mes "[素敵なデビ]";
		mes "……この口調は嫌だな……";
		mes "もういい、俺が知ってる事を";
		mes "全部話してやる！";
		next;
	}
	mes "[素敵なデビ]";
	mes "元々、こいつはこんな";
	mes "平凡なジャックじゃなくて、";
	mes "ハロウィンジャックなんだ。";
	next;
	mes "[素敵なデビ]";
	mes "でも、自分の心を";
	mes "盗まれたせいで、";
	mes "こんな憂鬱なジャックに";
	mes "なってしまったんだ。";
	next;
	mes "[素敵なデビ]";
	mes "だから、わざわざこんな所まで";
	mes "自分の心を探しに来たんだ。";
	next;
	mes "[素敵なデビ]";
	mes "盗んだ犯人も見当がついてる、";
	mes "自分がハロウィンのマスコットって";
	mes "言い触らしている^4A4AFF楽しいルード^000000。";
	mes "多分こいつだろうな。";
	next;
	mes "[素敵なデビ]";
	mes "とにかく、そのジャックの心を";
	mes "探してやってくれないか？";
	mes "礼ならこいつがちゃんとするからさ。";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "それってどんなの？";
	mes "話を聞いてから決めるよ。";
	next;
	mes "[素敵なデビ]";
	mes "^4A4AFFジャックの心、カボチャ、";
	mes "キャップを1個ずつ^000000持って来れば、";
	mes "^4A4AFFパンプキンハット 1個^000000";
	mes "と交換してくれるってさ。";
	next;
	mes "[素敵なデビ]";
	mes "ジャックの心なんて、";
	mes "あっても何の役にも立たないだろ？";
	mes "いいじゃないか。";
	mes "人間の町まで来る程困っている";
	mes "こいつを助けてやってくれよ。";
	close;
}
prontera.gat,162,69,5	script	憂鬱なジャック	1130,{}

//==========================================
// カボチャパイクエスト
//------------------------------------------
geffen.gat,145,132,3	script	ホイリン	729,{
	if(HALLOWEEN_EVE == 0) {
		mes "[ホイリン]";
		mes "カボチャこそ神さまからの";
		mes "贈り物だと思わない!?";
		mes "あの豊かなカロリーと栄養は";
		mes "私たちに不足している体力を";
		mes "補ってくれるの！";
		next;
		mes "[ホイリン]";
		mes "この私、ホイリンは！";
		mes "そんな素晴らしいカボチャを";
		mes "もっとおいしく食べるために";
		mes "色々と努力してきたの！";
		mes "そして、ある日知ったの！";
		next;
		mes "[ホイリン]";
		mes "あれさえ……";
		mes "あれさえあれば！";
		mes "私のカボチャパイが完成するって！";
		next;
		if(select("あれって何？","無視する")==2) {
			mes "[ホイリン]";
			mes "何よ！　無視するの？";
			mes "私のカボチャパイは、";
			mes "ものすっごくおいしいのに!!";
			close;
		}
		mes "[ホイリン]";
		mes "カボチャと言えば……";
		mes "そ、ジャックよね？";
		mes "私はジャックこそカボチャの";
		mes "完成形だと思ってるの！";
		next;
		mes "[ホイリン]";
		mes "そのジャックなんだけど、";
		mes "一匹ずつ、微妙に違う形を";
		mes "している事に気がついたの。";
		mes "そして、究極のジャックは";
		mes "全身が青色の光に包まれているのよ！";
		next;
		mes "[ホイリン]";
		mes "それが、ハロウィンジャック！";
		mes "そのハロウィンジャックは、";
		mes "濃縮されたカボチャ成分の結晶体である";
		mes "^4A4AFFジャックの心^000000を持っているのよ！";
		mes "それさえあれば、";
		mes "私の特製カボチャパイの完成！";
		next;
		mes "[ホイリン]";
		mes "でね、よかったらそれを";
		mes "取って来てくれないかな？";
		mes "そしたら、すぐに美味しい";
		mes "カボチャパイを作ってあげるよ。";
		mes "私のカボチャパイを食べると";
		mes "あまりの美味しさに感動しちゃうよ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "…………";
		mes "君、外見と性格が全然違うね……";
		mes "大人しそうに見えるのに";
		mes "すごく積極的……";
		mes "……ま、いっか。それで、";
		mes "そのカボチャパイの材料は？";
		next;
		mes "[ホイリン]";
		mes "良い質問です！";
		mes "私の特製カボチャパイには";
		mes "^4A4AFFジャックの心 1個、";
		mes "カボチャ 2個、卵 2個^000000。";
		mes "この三種類が必要なの！";
		next;
		mes "[ホイリン]";
		mes "他の材料は私が用意するから、";
		mes "ジャックの心、カボチャ、卵を";
		mes "持って来てね！";
		set HALLOWEEN_EVE,1;
		close;
	}
	mes "[ホイリン]";
	mes "カボチャパイの材料は";
	mes "手に入った？";
	next;
	switch(select("材料を全部持ってきた","卵はどこにあるのかな？","いえ、何も")) {
	case 1:
		if(countitem(7609) < 1 || countitem(535) < 2 || countitem(574) < 2) {
			mes "[ホイリン]";
			mes "カボチャパイを作るには足りないよ。";
			mes "^4A4AFFジャックの心 1個！";
			mes "カボチャ 2個！";
			mes "卵 2個！^000000";
			mes "これらが無いと作れないよ。";
			close;
		}
		misceffect 0,"";
		mes "[ホイリン]";
		mes "やった！";
		mes "それじゃ、さっそく！";
		next;
		misceffect 148;
		mes "[ホイリン]";
		mes "ホィーッ！";
		mes "ホイィィィッ！";
		next;
		mes "[ホイリン]";
		mes "完成！";
		mes "はい、これはあなたの分。";
		mes "ちゃんと味わってよね！";
		delitem 7609,1;
		delitem 535,2;
		delitem 574,2;
		getitem 12192,1;
		close;
	case 2:
		if(HALLOWEEN_EVE != 1) {
			mes "[ホイリン]";
			mes "卵なら、^4A4AFFニブルヘイムの秘境の村^000000で";
			mes "ニワトリを飼っている";
			mes "チェロキーってやつが売っているよ。";
			close;
		}
		mes "[ホイリン]";
		mes "卵？　卵かぁ……";
		mes "卵ならやっぱあいつかな。";
		mes "ニワトリを飼ってるやつを知ってるの。";
		mes "そいつに頼めばきっと卵をもらえるよ。";
		next;
		mes "[ホイリン]";
		mes "^4A4AFF最初の1回だけはサービス^000000で";
		mes "そいつの所に送ってあげる。";
		mes "あ、ニブルヘイムの秘境の村だから";
		mes "ちゃんと準備しないと危ないわよ。";
		next;
		mes "[ホイリン]";
		mes "それじゃ、今すぐ行く？";
		next;
		if(select("行く","行かない")==2) {
			mes "[ホイリン]";
			mes "準備不足？";
			mes "あそこは危険だもんね。";
			mes "ちゃんと準備できたら";
			mes "いつでも送ってあげる。";
			close;
		}
		mes "[ホイリン]";
		mes "それじゃ、卵をお願いね。";
		set HALLOWEEN_EVE,2;
		close2;
		warp "nif_fild01.gat",162,113;
		end;
	case 3:
		mes "[ホイリン]";
		mes "ちょっと！";
		mes "それじゃ困るよ！";
		mes "カボチャパイの材料を";
		mes "ちゃんと集めてきて！";
		next;
		mes "[ホイリン]";
		mes "いい？　もう一度言うよ。";
		mes "^4A4AFFジャックの心 1個！";
		mes "カボチャ 2個！";
		mes "卵 2個！^000000";
		mes "これが無いと作れないんだから！";
		close;
	}
}
nif_fild01.gat,165,115,3	script	チェロキー	794,{
	switch(HALLOWEEN_EVE) {
	default:
		mes "[チェロキー]";
		mes "ニワトリはどこいったんだ……";
		mes "ん？　君は……";
		mes "見覚えが無いが……";
		next;
		if(HALLOWEEN_EVE != 2) {
			mes "[チェロキー]";
			mes "ここは村だが、普通の人間が";
			mes "歩き回れる程安全じゃない。";
			mes "ケガをする前に帰った方がいい。";
			close;
		}
		mes "[チェロキー]";
		mes "ん？　卵が欲しいのか？";
		mes "最近、パイだか何だか言ってた";
		mes "客が来たが……君もか？";
		next;
		if(select("はい、卵を売ってください","特に用はない")==2) {
			mes "[チェロキー]";
			mes "なら、君に一つ忠告しよう。";
			mes "ここは危険な所だ。";
			mes "用が無いなら";
			mes "すぐに立ち去った方がいい。";
			close;
		}
		mes "[チェロキー]";
		mes "そうか……";
		mes "でも、私が育てているニワトリが";
		mes "何匹か逃げだしてしまって、";
		mes "あまり売れないんだ……";
		mes "そうだな……";
		mes "卵は1個当り 1000Zenyで売るよ。";
		next;
		if(select("2個ください","1個ください","高すぎ……")==3) {
			mes "[チェロキー]";
			mes "ん……やっぱり高いか……";
			mes "でも、ニワトリが逃げてしまって";
			mes "在庫がほとんどないんだ……";
			close;
		}
		set '@num,1+(@menu == 1? 1: 0);
		if(Zeny < '@num*1000) {
			mes "[チェロキー]";
			mes "お金が足りないんじゃないか？";
			if(@menu == 1)
				mes "1個当り 1000Zenyだから、";
			mes '@num+ "個なら" +1000*'@num+ "Zenyになるよ。";
			close;
		}
		mes "[チェロキー]";
		mes "はい、どうぞ。";
		set HALLOWEEN_EVE,3;
		set Zeny,Zeny-'@num*1000;
		getitem 574,'@num;
		close;
	case 3:
		mes "[チェロキー]";
		mes "卵がまた必要なのか……";
		mes "じゃあ、ちょっと手伝ってくれ。";
		mes "私が育てているニワトリが";
		mes "逃げ出したんだ……";
		next;
		mes "[チェロキー]";
		mes "全部探してこいとは言わない。";
		mes "1匹だけでも探してきてくれないか？";
		mes "そしたら卵を3つまで売るよ。";
		next;
		mes "[チェロキー]";
		mes "あまりこんな事はしたくないけど、";
		mes "ニワトリがいないとどうしようもないんだ。";
		mes "お互い、望む物が手に入るんだから";
		mes "正当な取り引きとでも思ってくれ……";
		next;
		mes "[チェロキー]";
		mes "ニワトリはこの辺に隠れているよ。";
		mes "別にニワトリを連れてくる必要はない。";
		mes "魔法をかけてあるから、呪文を唱えれば";
		mes "勝手に帰ってくるよ。";
		mes "呪文は^4A4AFF「非常食」^000000。";
		mes "…………";
		next;
		mes "[チェロキー]";
		mes "………………";
		mes "深く考えなくていい……";
		mes "とにかく、よろしく頼むよ。";
		close;
	case 4:
		mes "[チェロキー]";
		mes "やぁ、待ってたよ。";
		mes "君に送ってもらったニワトリは";
		mes "すぐに檻に入れておいたよ。";
		mes "いつまた逃げ出すかわからないから……";
		next;
		mes "[チェロキー]";
		mes "約束どおり卵を売るよ。";
		mes "1個、1000Zeny。";
		mes "最大3個まで売るよ。";
		mes "いくつにする？";
		next;
		while(1) {
			input '@num;
			if('@num < 0 || '@num > 3) {
				mes "[チェロキー]";
				mes "ちゃんと聞いていたかな？";
				mes "最大3個までだよ。";
				next;
				continue;
			}
			break;
		}
		if('@num == 0) {
			mes "[チェロキー]";
			mes "いらないのかな？";
			close;
		}
		if(Zeny < '@num*1000) {
			mes "[チェロキー]";
			mes "Zenyが足りないようだが？";
			mes "一度確認してみたらどうかな？";
			close;
		}
		mes "[チェロキー]";
		mes "はい、どうぞ。";
		mes "卵がもっと必要なら、";
		mes "逃げ出した他のニワトリも";
		mes "探してきてくれ。";
		set HALLOWEEN_EVE,3;
		set Zeny,Zeny-'@num*1000;
		getitem 574,'@num;
		close;
	}
}
nif_fild01.gat,167,113,3	script	チェロキーのニワトリ	800,{
	mes "眠っているニワトリだ。";
	close;
}

nif_fild01.gat,199,240,5	script	チェロキーのニワトリ#0	800,{
	if(HALLOWEEN_EVE < 3) {
		mes "眠っているニワトリだ。";
		close;
	}
	mes "チェロキーが探している";
	mes "ニワトリみたいだ。";
	mes "チェロキーが教えてくれた";
	mes "帰還魔法の呪文を唱えてみよう。";
	next;
	input '@word$;
	if('@word$ != "非常食") {
		mes "[" +strcharinfo(0)+ "]";
		mes "何も起きない。";
		mes "呪文を間違えたかな？";
		close;
	}
	misceffect 34;
	emotion 23;
	setarray '@ref,0,1,2,3,4,5,6,7;
	deletearray '@ref[strnpcinfo(2)],1;
	hideonnpc;
	hideoffnpc "チェロキーのニワトリ#" +'@ref[rand(7)];
	mes "帰還魔法が発動しました。";
	if(HALLOWEEN_EVE == 3)
		set HALLOWEEN_EVE,4;
	close;
OnInit:
	hideonnpc;
	if(strnpcinfo(2) == "0")
		hideoffnpc "チェロキーのニワトリ#"+rand(8);
	end;
}
nif_fild01.gat,219,267,4	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#1	800
nif_fild01.gat,185,325,0	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#2	800
nif_fild01.gat,147,342,0	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#3	800
nif_fild01.gat,270,145,3	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#4	800
nif_fild01.gat,331,329,0	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#5	800
nif_fild01.gat,133,105,1	duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#6	800
nif_fild01.gat,316,97,5		duplicate(チェロキーのニワトリ#0)	チェロキーのニワトリ#7	800

//==========================================
// ロリルリクエスト
//------------------------------------------
nif_in.gat,18,34,5	script	ロリルリ	1505,2,2,{
	mes "[デビルチ]";
	mes "おい、ロリルリに";
	mes "言いたいことがあるなら、";
	mes "俺に言ってみな。";
	mes "そいつはまだ人間の言葉に";
	mes "慣れていないからな。";
	close;
}
nif_in.gat,19,32,3	script	デビルチ	738,{
	mes "-ロリルリが理解できない言葉で";
	mes "話しかけてきている-";
	next;
	mes "[デビルチ]";
	mes "何言ってるかわからないだろ？";
	mes "俺が通訳してやるよ。";
	mes "ま、そのためにこいつに";
	mes "ついてきてやったんだけどな。";
	next;
	mes "-ロリルリが理解できない言葉で";
	mes "デビルチと話している-";
	next;
	mes "[デビルチ]";
	mes "…………ぇ？";
	mes "それ、そのまま言うの？";
	mes "言わなくちゃいけない？";
	next;
	mes "-ロリルリがうなづいている-";
	next;
	mes "[デビルチ]";
	mes "…………";
	mes "わかったよ……";
	mes "いいか！　今から話すのは";
	mes "全部ロリルリの言葉だ！";
	mes "俺はこんな口調じゃないからな！";
	mes "勘違いするなよ！";
	next;
	mes "[デビルチ]";
	mes "それじゃ……ゴホン。";
	next;
	mes "[デビルチ]";
	mes "「デビ……カボチャパイ……どこ？";
	mes "カボチャパイ……人間が作る。";
	mes "そこの人間……持ってない？」";
	next;
	mes "[デビルチ]";
	mes "……なんか、カボチャパイを";
	mes "一度食べてみたいんだってさ。";
	mes "もしカボチャパイを持ってるなら";
	mes "こいつにやってくれないか？";
	mes "ロリルリの機嫌が悪くなると";
	mes "俺が今よりもっと酷い目にあうんだ。";
	next;
	mes "[デビルチ]";
	mes "もちろんタダとは言わない。";
	mes "ちゃんと礼はするぜ。";
	next;
	switch(select("カボチャパイをあげる","あげない","カボチャパイって何？")) {
	case 1:
		if(countitem(12192) < 1) {
			mes "[デビルチ]";
			mes "「カボチャパイ……どこ？";
			mes "嘘……嘘ついたの？」";
			next;
			mes "[デビルチ]";
			mes "嘘つきって言ってるぞ。";
			mes "お前、酷いやつだな……";
			next;
			mes "[デビルチ]";
			mes "「カボチャパイ……くれた。";
			mes "でも……ない……";
			mes "デビ……お前……許さない。」";
			next;
			mes "[デビルチ]";
			mes "って言……あれ？";
			mes "嘘つきって俺のこと!?";
			mes "いや、俺は食ってないって！";
			mes "この人間が最初っから……";
			mes "こら！　やめ……";
			mes "アーッ!!";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "可哀相なやつ……";
			mes "嘘はいけないよね。";
			mes "ふふふふふ。";
			close;
		}
		mes "[デビルチ]";
		mes "「これが……カボチャパイ！";
		mes "ありがとう！」";
		next;
		mes "[デビルチ]";
		mes "ほら、カボチャパイをくれたんだから";
		mes "ちゃんと礼をしないとな。";
		mes "礼はするって言ってただろ？";
		next;
		mes "[デビルチ]";
		mes "「うん……";
		mes "人間……好き。";
		mes "これ……あげる。";
		mes "また……おいしい……";
		mes "カボチャパイ……ちょうだい。」";
		delitem 12192,1;
		if(rand(3))
			getitem 7460,3;
		else
			getitem 12130,1;
		next;
		mes "[デビルチ]";
		mes "お前の事が好きだってさ。";
		mes "良かったじゃねぇか。";
		mes "まだカボチャパイを欲しがってるから、";
		mes "余っているようなら";
		mes "持ってきてくれよ。";
		close;
	case 2:
		mes "[デビルチ]";
		mes "「カボチャパイ……食べたい。";
		mes "くれたら……あれ……あげる。」";
		next;
		mes "[デビルチ]";
		mes "あれが何か気にならないのか？";
		mes "それに、カボチャパイをくれたら";
		mes "ロリルリも喜ぶぜ？";
		close;
	case 3:
		mes "[デビルチ]";
		mes "自称カボチャマスターってやつが";
		mes "カボチャを材料に作ったパイらしい。";
		mes "話によると、その味は天下一品。";
		mes "一度食べるとその味を";
		mes "永久に忘れられない程らしい。";
		next;
		mes "[デビルチ]";
		mes "このロリルリも、そのカボチャパイを";
		mes "一度食べてみたいって事で";
		mes "人間が来るのを待っているんだ。";
		next;
		mes "[デビルチ]";
		mes "カボチャパイってやつを";
		mes "探してきてくれないか？";
		mes "もちろん礼はするからさ。";
		close;
	}
}
morocc.gat,159,143,3	script	パーミリア#Haloween	799,{
	mes "[パーミリア]";
	mes "私はロリルリ様の忠実なる部下、";
	mes "麗しのパーミリア。";
	mes "ロリルリ様から受けた招待状を";
	mes "持っているかしら？";
	mes "^4A4AFFニブルヘイム直行チケット^000000の事よ。";
	next;
	if(select("持っています","いいえ")==2) {
		mes "[パーミリア]";
		mes "あらそう……";
		mes "もし招待状が欲しいなら、";
		mes "ロリルリ様にカボチャパイを";
		mes "プレゼントして差し上げるといいわよ。";
		close;
	}
	mes "[パーミリア]";
	mes "それを使ってニブルヘイムに行く？";
	mes "ハロウィン期間限定で";
	mes "送ってあげるわよ。";
	next;
	if(select("行く","行かない")==2) {
		mes "[パーミリア]";
		mes "あらそう……";
		mes "でも、ニブルチケットを";
		mes "残しておいても";
		mes "使えなくなるだけよ。";
		close;
	}
	if(countitem(7460) < 1) {
		mes "[パーミリア]";
		mes "嘘つき……";
		mes "チケットを持ってないじゃない！";
		mes "嘘つきの血は吸ってやる！";
		emotion 23,"";
		percentheal -20,0;
		close;
	}
	mes "[パーミリア]";
	mes "チケットを確認したわ。";
	mes "では、行ってらっしゃい。";
	delitem 7460,1;
	close2;
	warp "nif_in",18,20;
	end;
}
prontera.gat,155,285,3	duplicate(パーミリア#Haloween)	パーミリア	799
payon.gat,156,231,3	duplicate(パーミリア#Haloween)	パーミリア	799
geffen.gat,120,188,3	duplicate(パーミリア#Haloween)	パーミリア	799
alberta.gat,80,171,3	duplicate(パーミリア#Haloween)	パーミリア	799

//==========================================
// ニワトリの幽霊クエスト
//------------------------------------------
pay_dun03.gat,0,0,0	script	ChickenGhost#pay	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer180000:
	misceffect 360,"ニワトリ#pay2";
	misceffect 360,"ニワトリ#pay5";
	misceffect 360,"ニワトリ#pay7";
	misceffect 360,"ニワトリ#pay9";
	misceffect 360,"ニワトリ#pay12";
	misceffect 360,"ニワトリ#pay15";
	misceffect 360,"ニワトリ#pay18";
	misceffect 360,"ニワトリ#pay21";
	misceffect 360,"ニワトリ#pay24";
	misceffect 360,"ニワトリ#pay27";
	misceffect 360,"ニワトリ#pay32";
	misceffect 360,"ニワトリ#pay34";
	misceffect 360,"ニワトリ#pay36";
	misceffect 360,"ニワトリ#pay39";
	if(rand(5) == 0) {
		for(set '@i,0; '@i <= 39; set '@i,'@i+1)
			hideoffnpc "ニワトリ#pay"+'@i;
		end;
	}
	initnpctimer;
	end;
OnTimer360000:
	for(set '@i,0; '@i <= 39; set '@i,'@i+1)
		hideonnpc "ニワトリ#pay"+'@i;
	initnpctimer;
	end;
}
pay_dun03.gat,151,131,4	script	ニワトリ#pay0	800,{
	hideonnpc;
	mes "ニワトリに触れようとすると、";
	mes "まるで実体がなかったかのように";
	mes "消えてしまった。";
	if(rand(5))
		close;
	mes "ニワトリがいた所には";
	mes "「卵」が一つ落ちていた";
	getitem 574,1;
	close;
OnInit:
	hideonnpc;
	end;
}
pay_dun03.gat,152,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay1	800
pay_dun03.gat,153,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay2	800
pay_dun03.gat,154,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay3	800
pay_dun03.gat,155,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay4	800
pay_dun03.gat,156,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay5	800
pay_dun03.gat,157,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay6	800
pay_dun03.gat,158,131,4	duplicate(ニワトリ#pay0)	ニワトリ#pay7	800
pay_dun03.gat,150,132,4	duplicate(ニワトリ#pay0)	ニワトリ#pay8	800
pay_dun03.gat,153,132,4	duplicate(ニワトリ#pay0)	ニワトリ#pay9	800
pay_dun03.gat,156,132,4	duplicate(ニワトリ#pay0)	ニワトリ#pay10	800
pay_dun03.gat,159,132,4	duplicate(ニワトリ#pay0)	ニワトリ#pay11	800
pay_dun03.gat,149,133,4	duplicate(ニワトリ#pay0)	ニワトリ#pay12	800
pay_dun03.gat,160,133,4	duplicate(ニワトリ#pay0)	ニワトリ#pay13	800
pay_dun03.gat,149,134,4	duplicate(ニワトリ#pay0)	ニワトリ#pay14	800
pay_dun03.gat,152,134,4	duplicate(ニワトリ#pay0)	ニワトリ#pay15	800
pay_dun03.gat,157,134,4	duplicate(ニワトリ#pay0)	ニワトリ#pay16	800
pay_dun03.gat,160,134,4	duplicate(ニワトリ#pay0)	ニワトリ#pay17	800
pay_dun03.gat,149,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay18	800
pay_dun03.gat,151,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay19	800
pay_dun03.gat,152,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay20	800
pay_dun03.gat,153,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay21	800
pay_dun03.gat,156,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay22	800
pay_dun03.gat,157,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay23	800
pay_dun03.gat,158,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay24	800
pay_dun03.gat,160,135,4	duplicate(ニワトリ#pay0)	ニワトリ#pay25	800
pay_dun03.gat,149,136,4	duplicate(ニワトリ#pay0)	ニワトリ#pay26	800
pay_dun03.gat,152,136,4	duplicate(ニワトリ#pay0)	ニワトリ#pay27	800
pay_dun03.gat,157,136,4	duplicate(ニワトリ#pay0)	ニワトリ#pay28	800
pay_dun03.gat,160,136,4	duplicate(ニワトリ#pay0)	ニワトリ#pay29	800
pay_dun03.gat,150,137,4	duplicate(ニワトリ#pay0)	ニワトリ#pay30	800
pay_dun03.gat,153,137,4	duplicate(ニワトリ#pay0)	ニワトリ#pay31	800
pay_dun03.gat,156,137,4	duplicate(ニワトリ#pay0)	ニワトリ#pay32	800
pay_dun03.gat,159,137,4	duplicate(ニワトリ#pay0)	ニワトリ#pay33	800
pay_dun03.gat,151,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay34	800
pay_dun03.gat,152,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay35	800
pay_dun03.gat,154,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay36	800
pay_dun03.gat,155,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay37	800
pay_dun03.gat,157,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay38	800
pay_dun03.gat,158,138,4	duplicate(ニワトリ#pay0)	ニワトリ#pay39	800
//------------------------------------------
prt_fild08.gat,0,0,0	script	ChickenGhost#prt	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer180000:
	misceffect 360,"ニワトリ#prt2";
	misceffect 360,"ニワトリ#prt4";
	misceffect 360,"ニワトリ#prt5";
	misceffect 360,"ニワトリ#prt8";
	misceffect 360,"ニワトリ#prt12";
	misceffect 360,"ニワトリ#prt15";
	misceffect 360,"ニワトリ#prt18";
	misceffect 360,"ニワトリ#prt20";
	misceffect 360,"ニワトリ#prt22";
	misceffect 360,"ニワトリ#prt24";
	if(rand(5) == 0) {
		for(set '@i,0; '@i <= 26; set '@i,'@i+1)
			hideoffnpc "ニワトリ#prt"+'@i;
		end;
	}
	initnpctimer;
	end;
OnTimer360000:
	for(set '@i,0; '@i <= 26; set '@i,'@i+1)
		hideonnpc "ニワトリ#prt"+'@i;
	initnpctimer;
	end;
}
prt_fild08.gat,155,350,4	script	ニワトリ#prt0	800,{
	hideonnpc;
	mes "ニワトリに触れようとすると、";
	mes "まるで実体がなかったかのように";
	mes "消えてしまった。";
	if(rand(5))
		close;
	mes "ニワトリがいた所には";
	mes "「卵」が一つ落ちていた";
	getitem 574,1;
	close;
OnInit:
	hideonnpc;
	end;
}
prt_fild08.gat,155,352,4	duplicate(ニワトリ#prt0)	ニワトリ#prt1	800
prt_fild08.gat,155,354,4	duplicate(ニワトリ#prt0)	ニワトリ#prt2	800
prt_fild08.gat,155,356,4	duplicate(ニワトリ#prt0)	ニワトリ#prt3	800
prt_fild08.gat,155,358,4	duplicate(ニワトリ#prt0)	ニワトリ#prt4	800
prt_fild08.gat,154,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt5	800
prt_fild08.gat,154,353,4	duplicate(ニワトリ#prt0)	ニワトリ#prt6	800
prt_fild08.gat,154,355,4	duplicate(ニワトリ#prt0)	ニワトリ#prt7	800
prt_fild08.gat,154,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt8	800
prt_fild08.gat,153,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt9	800
prt_fild08.gat,153,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt10	800
prt_fild08.gat,152,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt11	800
prt_fild08.gat,152,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt12	800
prt_fild08.gat,151,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt13	800
prt_fild08.gat,151,353,4	duplicate(ニワトリ#prt0)	ニワトリ#prt14	800
prt_fild08.gat,151,355,4	duplicate(ニワトリ#prt0)	ニワトリ#prt15	800
prt_fild08.gat,151,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt16	800
prt_fild08.gat,150,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt17	800
prt_fild08.gat,150,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt18	800
prt_fild08.gat,149,351,4	duplicate(ニワトリ#prt0)	ニワトリ#prt19	800
prt_fild08.gat,149,354,4	duplicate(ニワトリ#prt0)	ニワトリ#prt20	800
prt_fild08.gat,149,357,4	duplicate(ニワトリ#prt0)	ニワトリ#prt21	800
prt_fild08.gat,148,352,4	duplicate(ニワトリ#prt0)	ニワトリ#prt22	800
prt_fild08.gat,148,356,4	duplicate(ニワトリ#prt0)	ニワトリ#prt23	800
prt_fild08.gat,147,353,4	duplicate(ニワトリ#prt0)	ニワトリ#prt24	800
prt_fild08.gat,147,354,4	duplicate(ニワトリ#prt0)	ニワトリ#prt25	800
prt_fild08.gat,147,355,4	duplicate(ニワトリ#prt0)	ニワトリ#prt26	800

//==========================================
// 楽しいルード
//------------------------------------------
abyss_01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
abyss_02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
abyss_03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
alde_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
alde_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
alde_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
alde_dun04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ama_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ama_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ama_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ama_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
anthell01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
anthell02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ayo_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ayo_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ayo_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ayo_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
beach_dun.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
beach_dun2.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
beach_dun3.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
c_tower1.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
c_tower2.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
c_tower3.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
c_tower4.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
cmd_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
ein_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_dun00.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_dun03.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
gef_fild00.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild12.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild13.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gef_fild14.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gefenia01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gefenia02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gefenia03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gefenia04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_cas01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_cas02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_church.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_chyard.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_in01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_knt01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_knt02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_prison.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_prison1.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_sew01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_sew02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_sew03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_sew04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gl_step.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
glast_01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gon_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gon_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gon_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
gon_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
hu_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
in_sphinx1.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
in_sphinx2.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
in_sphinx3.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
in_sphinx4.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
in_sphinx5.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
iz_dun00.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
iz_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
iz_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
iz_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
iz_dun04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
jupe_core.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
juperos_01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
juperos_02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
kh_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
kh_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lhz_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lou_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lou_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lou_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
lou_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mag_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mag_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjo_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjo_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjo_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
mjolnir_12.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild12.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild13.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild14.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild15.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild16.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild17.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_fild18.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
moc_pryd06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
nif_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
nif_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
niflheim.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
odin_tem01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
odin_tem02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
odin_tem03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
orcsdun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
orcsdun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_dun00.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_dun04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
pay_fild11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild00.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_fild11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_maze01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_maze02.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
prt_maze03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_sewb1.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_sewb2.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_sewb3.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
prt_sewb4.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tha_t07.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tha_t08.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tha_t09.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tha_t10.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tha_t11.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tha_t12.gat,0,0,0,0	monster	楽しいルード	1812,1,0,0,0
tur_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tur_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tur_dun03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
tur_dun04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
um_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
xmas_dun01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
xmas_dun02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
xmas_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild01.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild02.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild03.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild04.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild05.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild06.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild07.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild08.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild09.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild10.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild11.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
yuno_fild12.gat,0,0,0,0	monster	楽しいルード	1812,3,0,0,0
