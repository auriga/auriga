//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Moonlight Quest Script	by refis
//= Registry ===================================================================
// IL_MOON_QUE -> 0～10
//==============================================================================
payon.gat,164,229,5	script	元老サンユル#ilp01	78,{
	if(BaseLevel < 170) {
		mes "[サンユル]";
		mes "何か怪しい事が";
		mes "起きている予感がします。";
		mes "君がもう少し強い冒険者なら";
		mes "話をしてみるが……残念だ。";
		next;
		mes "- ^4d4dffBaseLv170以上の時";
		mes "  進行可能なクエストです。^000000 -";
		close;
	}
	if(IL_MOON_QUE == 0) {
		mes "[サンユル]";
		mes "今回の件は私たちの手には";
		mes "負えないようだ。";
		mes "これでもう何回目だ。";
		next;
		mes "[ジャギョム]";
		mes "対処法を考えるにも";
		mes "情報が足りていない。";
		mes "まずはムヒョンを";
		mes "待つことにしよう。";
		mes "無事だと良いのだが。";
		next;
		menu "あの",-;
		mes "[サンユル]";
		mes "うむ？冒険者ではないか。";
		mes "私たちの話を";
		mes "聞いていたのか？";
		next;
		mes "[サンユル]";
		mes "……ふむ、そうか。";
		mes "これも全て神様の";
		mes "意向なのだろう。";
		mes "ひょっとしたら君が私たちの";
		mes "力になるかもしれない。";
		next;
		mes "[サンユル]";
		mes "フェイヨンの裏の方にある弓手村に";
		mes "洞窟があるのは知っているか？";
		mes "そこでは定期的に";
		mes "亡霊たちが現れるから";
		mes "浄化儀式を行っているんだ。";
		next;
		mes "[サンユル]";
		mes "だが私たちが考えてるより";
		mes "九尾狐の怨念が強いのだろう。";
		mes "狐の魂を浄化しようとすると";
		mes "浄化している者に";
		mes "狐の魂が移ってしまい";
		mes "悪夢にうなされていた。";
		next;
		mes "[サンユル]";
		mes "今回はついに気を失ったまま";
		mes "洞窟に走って行ってしまったんだ。";
		mes "だから心配でしょうがない。";
		next;
		menu "ムヒョンさんのことですか？",-;
		mes "[サンユル]";
		mes "ムヒョンはソウルリンカーだ。";
		mes "今頃は探しに向かうため";
		mes "兵士が洞窟近くに来ているので";
		mes "大丈夫だとは思うが。";
		next;
		mes "[ジャギョム]";
		mes "そうだな。しかし";
		mes "万が一があるかもしれない。";
		mes "君もそこに行って無事なのか";
		mes "確認してくれないか？";
		next;
		if(select("分かりました","お化けが怖いので無理です") == 2) {
			mes "[サンユル]";
			mes "私たちがいつ";
			mes "お化けがでると言った？";
			mes "言ったか？";
			close;
		}
		mes "[ジャギョム]";
		mes "兵士が無事に見つける事が";
		mes "出来たなら良いが、";
		mes "それが出来なかったなら";
		mes "洞窟の奥にある廃村まで";
		mes "行ってしまったはずだ。";
		next;
		mes "[ジャギョム]";
		mes "一旦、洞窟近くにムヒョンと兵士が";
		mes "出て来ているか確認してくれ。";
		mes "若い学士も後を追って行ったけど";
		mes "やっぱり任せられないからな。";
		next;
		mes "[ジャギョム]";
		mes "その学士に会って";
		mes "事情を聴いてみるのもいい。";
		setquest 7776;
		set IL_MOON_QUE,1;
		next;
		mes "- 学士のところに";
		mes "  向かいますか？ -";
		next;
		if(select("向かう","後にする") == 2) {
			mes "- 後にしよう -";
			close;
		}
		mes "- 学士の元に向かった -";
		close2;
		warp "pay_arche.gat",48,133;
		end;
	}
	else if(IL_MOON_QUE == 1) {
		mes "[ジャギョム]";
		mes "兵士が無事に見つける事が";
		mes "出来たなら良いが、";
		mes "それが出来なかったなら";
		mes "洞窟の奥にある廃村まで";
		mes "行ってしまったはずだ。";
		next;
		mes "[ジャギョム]";
		mes "一旦、洞窟近くにムヒョンと兵士が";
		mes "出て来ているか確認してくれ。";
		mes "若い学士も後を追って行ったけど";
		mes "やっぱり任せられないからな。";
		next;
		mes "[ジャギョム]";
		mes "その学士に会って";
		mes "事情を聴いてみるのもいい。";
		next;
		mes "- 学士のところに";
		mes "  向かいますか？ -";
		next;
		if(select("向かう","後にする") == 2) {
			mes "- 後にしよう -";
			close;
		}
		mes "- 学士の元に向かった -";
		close2;
		warp "pay_arche.gat",48,133;
		end;
	}
	mes "[サンユル]";
	mes "大したことなければいいが。";
	mes "うん？裏山にある洞窟の話だ。 ";
	mes "そこで起きている事のせいで";
	mes "色々悩みが多くて困っている。";
	close;
}

payon.gat,167,229,3	script	元老ジャギョム#ilp02	901,{
	if(IL_MOON_QUE == 0) {
		mes "[ジャギョム]";
		mes "まずはムヒョンを待つことにしよう。";
		mes "あの者が無事でないと。";
		close;
	}
	else if(IL_MOON_QUE == 1) {
		mes "[ジャギョム]";
		mes "まずは弓手村にある洞窟の";
		mes "入り口へ向かってみなさい。";
		mes "若い学士がいたらムヒョンの";
		mes "行方を聞いてみたらいい。";
		close;
	}
	mes "[ジャギョム]";
	mes "やはりこれからのことは";
	mes "若い者たちに任すべきだな。";
	mes "年寄の出る幕ではない。";
	close;
}

pay_arche.gat,48,137,3	script	青年学士#ilp03	92,{
	if(IL_MOON_QUE == 0) {
		unittalk "青年学士 : どうして出てこないんだ……",1;
		end;
	}
	else if(IL_MOON_QUE == 1) {
		mes "[青年学士]";
		mes "こんな幸運が起きるなんて！";
		mes "困った時に待っていたかのように";
		mes "冒険者が目の前に現れるとは！";
		next;
		mes "[青年学士]";
		mes "私が聞くに冒険者は";
		mes "色んな仕事を我々の代わりに";
		mes "務めてくれるというのは本当ですか？";
		next;
		menu "すでに仕事を受けている",-;
		mes "[青年学士]";
		mes "……そうですか。";
		mes "忙しいみたいですね。";
		mes "大変失礼しました。";
		mes "ここには何用で";
		mes "いらっしゃったんですか？";
		next;
		menu "ムヒョンを見ませんでしたか？",-;
		mes "[青年学士]";
		mes "ムヒョン？ソウルリンカーの";
		mes "ムヒョンのことですか？";
		mes "いや、まだ正式なソウルリンカーではなく";
		mes "修練中の身ですが……。";
		next;
		mes "[青年学士]";
		mes "浄化をしていたムヒョンが";
		mes "何かに憑りつかれて";
		mes "洞窟の奥まで入ってしまったので";
		mes "ジュウヒ……いや、";
		mes "兵士が探しに入ったのですが";
		mes "まだ何の知らせもありません。";
		next;
		mes "[青年学士]";
		mes "私は2人の帰りをここで";
		mes "待っていたのですが";
		mes "あまりにも音沙汰がないため";
		mes "別の人を探して";
		mes "探索に向かわせるかどうか";
		mes "悩んでいたところでした。";
		next;
		mes "[青年学士]";
		mes "何事もなければいいですが…";
		cloakoffnpc "ムヒョン#ilp04";
		cloakoffnpc "兵士シンジュウヒ#ilp05";
		if(!sleep2(2000)) end;
		unittalk "青年学士 : 出て来ました！無事みたいです！",1;
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"ムヒョン#ilp04"),"ムヒョン : ああ！もうやめる！浄化なんかやめたぁぁぁ!!",1;
		if(!sleep2(100)) end;
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp05"),"兵士シンジュウヒ : ……。",1;
		next;
		mes "[ムヒョン]";
		mes "あれ、ホドニ？";
		mes "君はどうしてここにいるの？";
		next;
		mes "[青年学士]";
		mes "それは心配だったから……。";
		next;
		mes "[ムヒョン]";
		mes "心配だと言う割には";
		mes "ここでこうしているのが";
		mes "精一杯なんでしょ？";
		mes "ホドニに心配してもらう";
		mes "筋合いはないから。";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp05"),"兵士シンジュウヒ : 適当にやってろ。",1;
		if(!sleep2(100)) end;
		unittalk "青年学士 : ちょっと、酷くないか。",1;
		next;
		mes "[ムヒョン]";
		mes "あ！私もうこれやめた。";
		mes "やらないから爺たちに";
		mes "代わりに伝えておいて！";
		mes "それじゃあバイバイ！";
		next;
		cloakonnpc "ムヒョン#ilp04";
		mes "[青年学士]";
		mes "……詳しい話は";
		mes "何もしないで";
		mes "行ってしまいましたね。";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp05"),"兵士シンジュウヒ : ふう、それでは私もこれで失礼する。一旦ムヒョンを追うから、元老たちに伝えてくれ。",1;
		if(!sleep2(1000)) end;
		cloakonnpc "兵士シンジュウヒ#ilp05";
		next;
		mes "[青年学士]";
		mes "うわあ！ジュウヒまで！";
		mes "そういえば冒険者様";
		mes "ムヒョンに用事があると";
		mes "言っていたのでは？";
		next;
		menu "戻るしかない",-;
		mes "[青年学士]";
		mes "ムヒョンは多分^4d4dffフェイヨン離宮^000000へ向かったと思います。";
		mes "一緒に行きませんか？";
		chgquest 7776,7777;
		set IL_MOON_QUE,2;
		next;
		if(select("一緒に行く","別々に行く") == 2) {
			mes "[青年学士]";
			mes "ムヒョンは多分";
			mes "^4d4dffフェイヨン離宮^000000へ";
			mes "向かったと思います。";
			mes "そこに行って詳しい話を";
			mes "聞いてみることにしましょう。";
			mes "元老たちには私が伝えておきます。";
			close;
		}
		mes "[青年学士]";
		mes "それじゃ離宮へと…";
		close2;
		warp "payon.gat",105,320;
		end;
	}
	else if(IL_MOON_QUE == 2) {
		mes "[青年学士]";
		mes "ムヒョンは多分^4d4dffフェイヨン離宮^000000へ向かったと思います。";
		mes "一緒に行きませんか？";
		next;
		if(select("一緒に行く","別々に行く") == 2) {
			mes "[青年学士]";
			mes "ムヒョンは多分";
			mes "^4d4dffフェイヨン離宮^000000へ";
			mes "向かったと思います。";
			mes "そこに行って詳しい話を";
			mes "聞いてみることにしましょう。";
			mes "元老たちには私が伝えておきます。";
			close;
		}
		mes "[青年学士]";
		mes "それじゃ離宮へと…";
		close2;
		warp "payon.gat",105,320;
		end;
	}
	else if(IL_MOON_QUE < 6) {
		mes "[青年学士]";
		mes "その昔、徳を長く積み上げた神獣が";
		mes "九尾狐になったらしいです。";
		mes "その子孫が月夜花になった";
		mes "という話もあります。";
		mes "十分に研究してみる価値のある";
		mes "話だと考えています。";
		close;
	}
	else if(IL_MOON_QUE >= 6) {
		mes "[青年学士]";
		mes "廃村に早く調査を！";
		mes "一緒に行きますか？";
		next;
		if(select("一緒に行く","別々に行く") == 2) {
			mes "[青年学士]";
			mes "それでは私たちもジュウヒを呼んで";
			mes "すぐに後を追って行くようにします！";
			close;
		}
		mes "[青年学士]";
		mes "さあ、早く行きましょう！";
		close2;
		warp "pay_dun03.gat",145,43;
		end;
	}
}

pay_arche.gat,46,135,5	script	ムヒョン#ilp04	644,{
	end;
OnInit:
	cloakonnpc;
	end;
}

pay_arche.gat,44,133,7	script	兵士シンジュウヒ#ilp05	708,{
	end;
OnInit:
	cloakonnpc;
	end;
}

payon.gat,103,322,4	script	フェイヨン兵士 #ilp06	708,{
	if(IL_MOON_QUE == 2) {
		mes "[ジュウヒ]";
		mes "前に洞窟の前で見た";
		mes "冒険者じゃないか。";
		mes "ムヒョンを探しに来たなら";
		mes "中に入ってみろ。";
		close;
	}
	mes "[兵士]";
	mes "ここはフェイヨン離宮です。";
	close;
}

payon_in03.gat,33,95,3	script	ムヒョン#ilp07	644,{
	if(IL_MOON_QUE < 2) {
		mes "[ムヒョン]";
		mes "イェジョル先生を探しに来たなら";
		mes "もっと奥の部屋に行って下さい。";
		close;
	}
	else if(IL_MOON_QUE == 2) {
		unittalk "ムヒョン : だからいくら話しても私はもうやりません！",1;
		if(!sleep2(3000)) end;
		unittalk "ムヒョン : これでもう三回目ですよ。もうこの悪夢とは関わりたくないです。",1;
		if(!sleep2(100)) end;
		unittalk getcharid(3),strcharinfo(0)+ " : 悪夢？",1;
		if(!sleep2(100)) end;
		unittalk getnpcid(0,"青年学士#ilp08"),"青年学士 : 悪夢？",1;
		if(!sleep2(3000)) end;
		unittalk "ムヒョン : 狐の悪夢だよ。そこに九尾狐と月夜花がいたんだ。",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : とても酷い内容だった。二度とあんな経験をしたくない。",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ジャギョム#ilp09"),"ジャギョム : だけど君がやらなければ誰がそれを浄化するんだ？",1;
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"ジャギョム#ilp09"),"ジャギョム : みんな出来ないと辞めていった。それでもムヒョン君は三回もやったじゃないか。",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : それがですね、今回は嫌な夢で終わるだけではなかったんですよ。",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : 今までは狐玉に込められた悪夢の気を浄化すると、嫌な夢を見ていただけだったのに……",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"青年学士#ilp08"),"青年学士 : 今回は何が違うんですか？",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : ……",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : 夢と現実の境界が崩れるのではと不安を感じた。",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ジャギョム#ilp09"),"ジャギョム : ……それは何の話だ！今まではただ九尾狐の怨念を鎮めるだけで良かったじゃないか。",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ジャギョム#ilp09"),"ジャギョム : いったい洞窟で何を見たんだ？",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : 私が言葉でいくら説明するより、直接見た方が良いと思いますよ。",1;
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : どうせなら強い方がいいです。今いらっしゃっている冒険者の人くらい。",1;
		chgquest 7777,7778;
		set IL_MOON_QUE,3;
		end;
	}
	else if(IL_MOON_QUE == 3) {
		menu "悪夢について教えてほしい",-;
		mes "[ムヒョン]";
		mes "分かりました。";
		mes "……悪夢を見せる前に";
		mes "少しだけ昔話をしましょう。";
		next;
		mes "[ムヒョン]";
		mes "フェイヨン洞窟は昔に発生した";
		mes "ある事件で山崩れが起きて";
		mes "村の一部が埋まって作られたものです。";
		next;
		mes "[ムヒョン]";
		mes "当たり前だと思いますが";
		mes "悔しい思いを抱えたまま";
		mes "死を迎えた者たちも";
		mes "多かったのでしょう。";
		mes "今でも亡霊たちが";
		mes "たくさん残っています。";
		next;
		mes "[ムヒョン]";
		mes "特に廃村に生息する";
		mes "九尾狐たちの怨念は";
		mes "凄まじいほど強力なので定期的に";
		mes "浄化儀式を行うのですが";
		mes "問題はここからです。";
		next;
		mes "[ムヒョン]";
		mes "原因は誰にも分かりませんが";
		mes "最近になって狐たちの怨念が";
		mes "さらに強くなってしまったんです。";
		mes "強くなったと言うよりは";
		mes "浄化がうまく行われていないと";
		mes "言った方が正しいかも知れません。";
		next;
		mes "[ムヒョン]";
		mes "九尾狐たちの怨念は凄まじく";
		mes "普段通り浄化をしたら";
		mes "怨念によって悪夢を見たり";
		mes "感応して泣いたり……。";
		mes "そのような嫌なことが";
		mes "起きるようになりました。";
		next;
		mes "[ムヒョン]";
		mes "ソウルリンカーというのが";
		mes "魂の共感を行う職業なので";
		mes "稀にですが退魔儀式を行った後、";
		mes "夢見が悪くなることがあります。";
		next;
		mes "[ムヒョン]";
		mes "私もただ疲れてるとしか";
		mes "考えていませんでした。";
		mes "しかし今回の件で知る事が出来ました。";
		mes "そうじゃなかったと！";
		next;
		mes "[ムヒョン]";
		mes "何が狐たちの怨念を";
		mes "増幅させているかは知りません。";
		mes "私は自分の意識をなくし、たくさんの";
		mes "狐の泣き声が聞こえる廃村に";
		mes "私自身も知らず知らずのうちに";
		mes "向かっていました。";
		next;
		mes "[ムヒョン]";
		mes "そして見てしまったのです。";
		mes "この世の向こう側を。";
		mes "これ以上、人が近づいてはダメです！";
		next;
		mes "[ムヒョン]";
		mes "とても不吉な何かが";
		mes "起きそうな予感がします。";
		mes "いや、すでに始まっているのかも。";
		next;
		mes "[ムヒョン]";
		mes "私が見たぼんやりした残像の";
		mes "向こう側は地獄でした。";
		mes "怨念を浄化した後は";
		mes "いつも見ていた狐たちの悪夢。";
		next;
		mes "[ムヒョン]";
		mes "……なのでもう二度と私に";
		mes "この仕事をさせないで下さい。";
		mes "私の精神の弱さから";
		mes "始まった悪夢なら";
		mes "私が甘受すべきことです。";
		next;
		mes "[ムヒョン]";
		mes "だけど狐たちの悪夢には";
		mes "二度と関わりたくありません。";
		next;
		mes "[ムヒョン]";
		mes "本当に気になるのであれば";
		mes "直接経験してみた方がいいですよ。";
		mes "丁度、先ほど浄化しようとしていた";
		mes "狐の魂があるので、準備ができましたら";
		mes "いつでも教えて下さい。";
		chgquest 7778,7779;
		set IL_MOON_QUE,4;
		close;
	}
	else if(IL_MOON_QUE == 4) {
		mes "[ムヒョン]";
		mes "準備は出来ましたか？";
		next;
		if(select("出来ました","まだです") == 2) {
			mes "[ムヒョン]";
			mes "お待ちしていますので";
			mes "準備ができましたら";
			mes "教えて下さい。";
			close;
		}
		mes "[ムヒョン]";
		mes "分かりました。";
		mes "これはまだ浄化が";
		mes "終わっていない狐の魂です。";
		mes "これを手の上にのせて…";
		next;
		mes "[ムヒョン]";
		mes "精神を集中し";
		mes "心を穏やかにして下さい。";
		mes "心の扉を開いて";
		mes "受け入れなければなりません。";
		close2;
		unittalk "ムヒョン : 見よ、聞きなさい、彷徨う魂よ",1;
		if(!sleep2(100)) end;
		misceffect 389, "ムヒョン#ilp07";
		misceffect 513, "ムヒョン#ilp07";
		if(!sleep2(2500)) end;
		unittalk "ムヒョン : 三途の川の向こうを見ろ。",1;
		if(!sleep2(100)) end;
		misceffect 402, "ムヒョン#ilp07";
		misceffect 458, "ムヒョン#ilp07";
		if(!sleep2(400)) end;
		cloakoffnpc "#狐魂ilp10";
		if(!sleep2(500)) end;
		cloakoffnpc "#狐魂ilp11";
		if(!sleep2(500)) end;
		cloakoffnpc "#狐魂ilp12";
		if(!sleep2(500)) end;
		cloakoffnpc "#狐魂ilp13";
		if(!sleep2(500)) end;
		misceffect 368, "#狐魂ilp10";
		misceffect 368, "#狐魂ilp11";
		misceffect 368, "#狐魂ilp12";
		misceffect 368, "#狐魂ilp13";
		misceffect 458, "#狐魂ilp10";
		misceffect 458, "#狐魂ilp11";
		misceffect 458, "#狐魂ilp12";
		misceffect 458, "#狐魂ilp13";
		unittalk "ムヒョン : 見るな、聞くな、悔しい魂よ。",1;
		misceffect 475,"";
		misceffect 458, "#狐魂ilp10";
		misceffect 458, "#狐魂ilp11";
		misceffect 458, "#狐魂ilp12";
		misceffect 458, "#狐魂ilp13";
		unittalk getnpcid(0,"#狐魂ilp10"),"狐魂 : 死ね",1;
		if(!sleep2(1000)) end;
		misceffect 480,"";
		misceffect 458, "#狐魂ilp10";
		misceffect 458, "#狐魂ilp11";
		misceffect 458, "#狐魂ilp12";
		misceffect 458, "#狐魂ilp13";
		unittalk getnpcid(0,"#狐魂ilp11"),"狐魂 : 死ね";
		unittalk "ムヒョン : この世から背を向け",1;
		if(!sleep2(100)) end;
		misceffect 484,"";
		misceffect 458, "#狐魂ilp10";
		misceffect 458, "#狐魂ilp11";
		misceffect 458, "#狐魂ilp12";
		misceffect 458, "#狐魂ilp13";
		unittalk getnpcid(0,"#狐魂ilp12"),"狐魂 : 死ね",1;
		if(!sleep2(1500)) end;
		misceffect 899, "ムヒョン#ilp07";
		if(!sleep2(100)) end;
		unittalk getnpcid(0,"#狐魂ilp13"),"狐魂 : 死ね",1;
		if(!sleep2(1000)) end;
		unittalk "ムヒョン : 重いものはここに置いて",1;
		if(!sleep2(100)) end;
		misceffect 692, "#狐魂ilp10";
		misceffect 692, "#狐魂ilp11";
		misceffect 692, "#狐魂ilp12";
		misceffect 692, "#狐魂ilp13";
		unittalk getnpcid(0,"#狐魂ilp10"),"狐魂 : 死ね！！",1;
		unittalk getnpcid(0,"#狐魂ilp11"),"狐魂 : 死ね！！",1;
		unittalk getnpcid(0,"#狐魂ilp12"),"狐魂 : 死ね！！",1;
		unittalk getnpcid(0,"#狐魂ilp13"),"狐魂 : 死ね！！",1;
		if(!sleep2(1500)) end;
		misceffect 899, "ムヒョン#ilp07";
		misceffect 563, "ムヒョン#ilp07";
		if(!sleep2(2000)) end;
		unittalk "ムヒョン : 川の向こうへと飛んで行け",1;
		if(!sleep2(100)) end;
		misceffect 626, "#狐魂ilp10";
		misceffect 626, "#狐魂ilp11";
		misceffect 626, "#狐魂ilp12";
		misceffect 626, "#狐魂ilp13";
		unittalk getnpcid(0,"#狐魂ilp10"),"狐魂 : 死ね！！！！",1;
		misceffect 563, "ムヒョン#ilp07";
		if(!sleep2(900)) end;
		unittalk getnpcid(0,"#狐魂ilp11"),"狐魂 : 死ね！！！！",1;
		if(!sleep2(100)) end;
		misceffect 563, "ムヒョン#ilp07";
		if(!sleep2(900)) end;
		unittalk getnpcid(0,"#狐魂ilp12"),"狐魂 : 死ね！！！！",1;
		if(!sleep2(100)) end;
		misceffect 563, "ムヒョン#ilp07";
		if(!sleep2(900)) end;
		unittalk getnpcid(0,"#狐魂ilp13"),"狐魂 : 死ね！！！！",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"#狐魂ilp10"),"狐魂 : 死ね！！！！！",1;
		unittalk getnpcid(0,"#狐魂ilp11"),"狐魂 : 死ね！！！！！",1;
		unittalk getnpcid(0,"#狐魂ilp12"),"狐魂 : 死ね！！！！！",1;
		unittalk getnpcid(0,"#狐魂ilp13"),"狐魂 : 死ね！！！！！",1;
		misceffect 1072,"";
		if(!sleep2(400)) end;
		chgquest 7779,7780;
		set IL_MOON_QUE,5;
		warp "pay_dun03.gat",142,44;
		end;
	}
	else if(IL_MOON_QUE == 5) {
		mes "[ムヒョン]";
		mes "……これで分かりましたね？";
		mes "私が何を経験したのかを。";
		mes "もっと詳しい真相を調査するなら";
		mes "もう一度、廃村に";
		mes "行かなければなりません。";
		next;
		mes "[ムヒョン]";
		mes "冒険者様が";
		mes "今回の現象に対して";
		mes "調査するのなら";
		mes "そこにいるバカが";
		mes "とても喜びそうですね。";
		close;
	}
	else if(IL_MOON_QUE < 9) {
		mes "[ムヒョン]";
		mes "イェジョル先生を探しに来たなら";
		mes "もっと奥の部屋に行って下さい。";
		close;
	}
	else if(IL_MOON_QUE == 9) {
		mes "[ムヒョン]";
		mes "そうですか。";
		mes "結局、具体化されて";
		mes "しまったのですね。";
		mes "理由については";
		mes "知らないんですよね？";
		next;
		mes "[ムヒョン]";
		mes "具体化されたと言うよりは";
		mes "夢と現実の境界が崩れたと";
		mes "言うのが正しいでしょうか？";
		mes "普通の人が誰かの夢の中を";
		mes "あんな風に行き来することは";
		mes "出来ません。";
		next;
		mes "[ムヒョン]";
		mes "それが^4d4dff月夜花の悪夢^000000だと";
		mes "言うのはよく分かりました。";
		mes "でもどうやってそれが現実と";
		mes "繋がるようになったのかは";
		mes "誰も知りません。";
		next;
		mes "[ムヒョン]";
		mes "これと似た事例でもあったら";
		mes "参考にしますけど";
		mes "まだそのような話は";
		mes "聞いた事もありません。";
		mes "まあ、その部分については";
		mes "ホドニがうまく調査するかと。";
		next;
		mes "[ムヒョン]";
		mes "よし～！では久しぶりに";
		mes "少し休んでみようかな！";
		mes "これで余計な事は考えずに";
		mes "ぐっすり寝れそうです。";
		next;
		mes "[ムヒョン]";
		mes "浄化作業をするよりも";
		mes "その夢さえ処理すれば";
		mes "一気に解決できそうなので！";
		mes "私は解放！解放です！";
		mes "ありがとうございます";
		mes "冒険者様！";
		if(checkitemblank() == 0) {
			next;
			mes "[ムヒョン]";
			mes "お礼を渡そうと思ったのですが";
			mes "持てそうにありませんね。";
			close;
		}
		chgquest 7788,202075;
		set IL_MOON_QUE,10;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		getitem 25271,10;
		close;
	}
	else if(IL_MOON_QUE == 10) {
		mes "[ムヒョン]";
		mes "ホドニと一緒に調査、研究！";
		mes "頑張って下さい！";
		mes "九尾狐の悪夢が消えたら";
		mes "このうんざりする儀式も";
		mes "無くなりますから～！";
		next;
		mes "[ムヒョン]";
		mes "なぜ知っているのか";
		mes "気になるんですか？";
		mes "ただの勘ですよ！あははははは！";
		mes "多分消えないであのまま";
		mes "一生いるかも知れないけど！";
		mes "私と関係ないことですから！";
		close;
	}
}

payon_in03.gat,33,93,1	script	青年学士#ilp08	92,{
	if(IL_MOON_QUE < 2) {
		mes "[青年学士]";
		mes "フェイヨンは昔から";
		mes "神獣たちと一緒に暮らす街でした。";
		mes "山で隔離されていて";
		mes "余所と比べると考え方に";
		mes "かなり違いがあります。";
		close;
	}
	else if(IL_MOON_QUE == 2) {
		unittalk "青年学士 : ムヒョンはとても興奮しています。話を聞いてみないといけないのですが……",1;
		end;
	}
	else if(IL_MOON_QUE < 5) {
		unittalk "青年学士 : ムヒョンの話から聞いてみた方がよさそうです。",1;
		end;
	}
	else if(IL_MOON_QUE == 5) {
		mes "[青年学士]";
		mes "本当に悲惨ですね。";
		mes "こんなことをムヒョンが";
		mes "ひとりで背負っていたんですね。";
		mes "九尾狐の怨念が";
		mes "想像していた以上で驚きました。";
		next;
		mes "[青年学士]";
		mes "もう少し研究が必要です。";
		mes "やはり直接、廃村に";
		mes "行ってみるしかなさそうです。";
		close;
	}
	else if(IL_MOON_QUE >= 6) {
		mes "[青年学士]";
		mes "当分の間は廃村で";
		mes "この奇妙な現象を";
		mes "研究することにします。";
		mes "どうしてもひとりじゃ大変なので";
		mes "外にいるジュウヒと一緒に";
		mes "行動しようと考えています。";
		next;
		mes "[青年学士]";
		mes "この前にみたいに冒険者様が";
		mes "一緒にいてくれるなら申し分ないです。";
		mes "それでは廃村で会いましょう。";
		close;
	}
}

payon_in03.gat,30,96,5	script	ジャギョム#ilp09	901,{
	if(IL_MOON_QUE < 2) {
		mes "[ジャギョム]";
		mes "宮内では静かにしなさい。";
		close;
	}
	else if(IL_MOON_QUE == 2) {
		unittalk "ジャギョム : ムヒョン、君がやらないと誰が代わりになってやってくれると言うんだ？",1;
		end;
	}
	else if(IL_MOON_QUE < 5) {
		unittalk "ジャギョム : まずはムヒョンの話を聞いてみることにしよう。",1;
		end;
	}
	else if(IL_MOON_QUE == 5) {
		mes "[ジャギョム]";
		mes "……やはりまずは";
		mes "事態の把握を優先にしないと。";
		mes "冒険者の君が";
		mes "力を貸してくれるなら";
		mes "大きな助けになるのだが。";
		close;
	}
	else if(IL_MOON_QUE < 9) {
		mes "[ジャギョム]";
		mes "宮内では静かにしなさい。";
		close;
	}
	else if(IL_MOON_QUE == 9) {
		mes "[ジャギョム]";
		mes "……やはりまずは";
		mes "事態の把握を優先にしないと。";
		mes "冒険者の君が";
		mes "力を貸してくれるなら";
		mes "大きな助けになるのだが。";
		close;
	}
	else if(IL_MOON_QUE == 10) {
		mes "[ジャギョム]";
		mes "月夜花が過去の事件を";
		mes "悪夢として見せているというのか。";
		mes "……その者も被害者で";
		mes "あるかもしれないというのに。";
		next;
		mes "[ジャギョム]";
		mes "その具体化された夢の境界線と";
		mes "言ったらいいのか？";
		mes "街の者たちには";
		mes "そこには近づかないよう";
		mes "伝えておこう。";
		close;
	}
}

payon_in03.gat,31,96,5	script	#狐魂ilp10	1180,{
	end;
OnInit:
	cloakonnpc;
	end;
}

payon_in03.gat,35,96,3	script	#狐魂ilp11	1180,{
	end;
OnInit:
	cloakonnpc;
	end;
}

payon_in03.gat,31,93,7	script	#狐魂ilp12	1180,{
	end;
OnInit:
	cloakonnpc;
	end;
}

payon_in03.gat,35,93,1	script	#狐魂ilp13	1180,{
	end;
OnInit:
	cloakonnpc;
	end;
}

pay_dun03.gat,140,46,3	script	揺らぐ空間#ilp14	10043,{
	if(IL_MOON_QUE < 5) {
		mes "怪しい気が揺らいでいる。";
		mes "不気味な感じがする。";
		close;
	}
	else if(IL_MOON_QUE == 5) {
		mes "空間が歪んでいるような部分が見える。";
		next;
		cloakoffnpc "青年学士#ilp15";
		cloakoffnpc "兵士シンジュウヒ#ilp16";
		unittalk getnpcid(0,"青年学士#ilp15"),"青年学士 : はあはあ、ここにいらっしゃったのですね。",1;
		mes "[青年学士]";
		mes "急に消えて";
		mes "びっくりしました。";
		mes "これがムヒョンの言っていた";
		mes "具体化された悪夢と";
		mes "いうものなんですか？";
		next;
		menu "これから調査をしようと考えている",-;
		mes "[青年学士]";
		mes "それじゃその調査に";
		mes "私も同行したらダメですか？";
		mes "勿論、私ひとりでは";
		mes "危険だと思いますが";
		mes "ここにいるジュウヒと一緒なら";
		mes "大丈夫だと思いませんか？！";
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp16"),"兵士シンジュウヒ : 予想はしていたけど……ホドニ、お前は本当に適当じゃないか？",1;
		next;
		mes "[青年学士]";
		mes "それじゃ、こ……これに触れればいいのかな？";
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp16"),"兵士シンジュウヒ : 勝手に触るな！",1;
		chgquest 7780,7781;
		set IL_MOON_QUE,6;
		close2;	// 以下タイマー不明
		misceffect 890, "青年学士#ilp15";
		misceffect 895, "青年学士#ilp15";
		unittalk getnpcid(0,"青年学士#ilp15"),"青年学士 : うわあああああ～！！！",1;
		if(!sleep2(500)) end;
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp16"),"兵士シンジュウヒ : おい～！ホドニ！！！",1;
		if(!sleep2(2000)) end;
		cloakonnpc "青年学士#ilp15";
		unittalk getnpcid(0,"兵士シンジュウヒ#ilp16"),"兵士シンジュウヒ : ……あのバカが余計なことをしやがって！！！",1;
		if(!sleep2(2000)) end;
		misceffect 890, "兵士シンジュウヒ#ilp16";
		misceffect 895, "兵士シンジュウヒ#ilp16";
		if(!sleep2(500)) end;
		cloakonnpc "兵士シンジュウヒ#ilp16";
		end;
	}
	else {
		mes "歪曲された空間の向こうに";
		mes "何かが映る。";
		mes "どうしようかな？";
		next;
		if(select("進入する","やめる") == 2) {
			mes "今はやめておこう。";
			close;
		}
		warp "pay_d03_i.gat",140,44;
		end;
	}
}

pay_dun03.gat,138,43,7	script	青年学士#ilp15	92,{
	end;
OnInit:
	cloakonnpc;
	end;
}

pay_dun03.gat,142,45,3	script	兵士シンジュウヒ#ilp16	708,{
	end;
OnInit:
	cloakonnpc;
	end;
}

pay_d03_i.gat,149,45,4	script	学士ホドニ#ilp18	92,{
	if(IL_MOON_QUE == 6) {
		mes "[ホドニ]";
		mes "ちょっとこっちを見て下さい！";
		mes "先ほど私たちがいた";
		mes "廃村に間違いないのに";
		mes "そうじゃないようにも見えます！";
		next;
		mes "[ホドニ]";
		mes "ここにいる人たちも";
		mes "九尾狐たちも何か様子が変です。";
		mes "特に妙な魔法使いが";
		mes "歩き回っているのですが";
		mes "この事件の元凶ではないんでしょうか？";
		next;
		mes "[ホドニ]";
		mes "そして九尾狐たち！";
		mes "人々！死霊たち！";
		mes "まるで昔話に聞いた事件の";
		mes "山崩れで村が埋まったその時に";
		mes "戻ってしまったような……。";
		next;
		mes "[ホドニ]";
		mes "調査！調査が必要になると思います。";
		mes "勿論、協力して頂けますよね？";
		next;
		mes "[ホドニ]";
		mes "準備ができたら";
		mes "話かけて下さい。";
		chgquest 7781,7783;
		set IL_MOON_QUE,7;
		close;
	}
	else if(IL_MOON_QUE == 7) {
		mes "[ホドニ]";
		mes "ここの人々から聞けた話は";
		mes "怪しい魔法使いのことばかりでした。";
		next;
		mes "[ホドニ]";
		mes "何も考えずに大魔法を使い";
		mes "そのせいで地盤が崩れて";
		mes "山崩れが起きたそうです。";
		mes "当たり前だと思うけど";
		mes "そんな事件なら住民も";
		mes "たくさん死んだんでしょうね。";
		next;
		mes "[ホドニ]";
		mes "いくら考えても、悪夢の元凶は";
		mes "その怪しい魔法使いでしょう。";
		mes "悪夢の元凶を除去すれば";
		mes "この悪夢は具体化されず";
		mes "消えるのではないでしょうか？";
		next;
		mes "[ホドニ]";
		mes "実際には魔法使いは";
		mes "何も関連の無い人物である";
		mes "可能性もありますが";
		mes "調べてみる価値は";
		mes "あると考えています。";
		next;
		mes "[ホドニ]";
		mes "ただ今回の件で最も重要なのは";
		mes "夢と現実の境界がなぜ崩れたのかです。";
		mes "他の場所でもこのようなことが";
		mes "また発生するのでしょうか？";
		next;
		mes "[ホドニ]";
		mes "とにかく調査してみましょう。";
		mes "^4d4dff真理の魔法使い^000000は";
		mes "かなり強力そうに見えるので";
		mes "気を付けてください。";
		mes "冒険者様の仲間がいるなら一緒に";
		mes "相手する事をお勧めします。";
		next;
		if(select("調査をする","断る") == 2) {
			mes "[ホドニ]";
			mes "うう……では他の要素を";
			mes "調査するしかありませんね！";
			mes "勿論、今回のことで";
			mes "私が冒険者様を恨んだりはしませんが！";
			close;
		}
		mes "[ホドニ]";
		mes "私もその間に";
		mes "周囲を調べてみますので";
		mes "少し経ったら";
		mes "もう一度話しかけてください。";
		chgquest 7783,7782;
		set IL_MOON_QUE,8;
		close;
	}
	else if(IL_MOON_QUE == 8) {
		mes "[ホドニ]";
		mes "お待たせいたしました。";
		mes "何となく今回の件の";
		mes "原因が掴めてきましたよ。";
		next;
		mes "[ホドニ]";
		mes "ムヒョンが言っていたことを";
		mes "覚えていますか？";
		mes "狐の悪夢が具体化されたと";
		mes "言っていたのを。";
		next;
		mes "[ホドニ]";
		mes "周辺を調査しながら";
		mes "考えてみましたが";
		mes "ここはやはり月夜花が作り出した";
		mes "悪夢のようです。";
		next;
		mes "[ホドニ]";
		mes "どうして悪夢が現実と";
		mes "繋がるようになったのか";
		mes "分かりませんが、ひとつだけ";
		mes "確かなことがあります。";
		next;
		mes "[ホドニ]";
		mes "月夜花が過去の事件を";
		mes "まだ忘れていないということです。";
		next;
		mes "[ホドニ]";
		mes "当時の事件が";
		mes "大きいな苦痛として残り";
		mes "今現在まで恨みとして";
		mes "積もり続けていたようです。";
		mes "それが何かの切っ掛けで";
		mes "爆発したのではないかと……。";
		next;
		mes "[ホドニ]";
		mes "まだ知らない事実が";
		mes "あると思いませんか？";
		mes "もう少しここで";
		mes "調査を続けようと思います。";
		next;
		mes "[ホドニ]";
		mes "このことをフェイヨン離宮にいる";
		mes "ムヒョンにも伝えて下さい。";
		mes "私はそれまでの間";
		mes "ジュウヒと一緒に";
		mes "付近を回って調べてみます。";
		next;
		mes "[ホドニ]";
		mes "この現象に対する";
		mes "何かしらの解答が";
		mes "出るならいいですが。";
		if(checkitemblank() == 0) {
			next;
			mes "[ホドニ]";
			mes "調査のお礼を";
			mes "渡そうと思ったのですが";
			mes "持てそうにありませんね。";
			close;
		}
		chgquest 7782,7788;
		set IL_MOON_QUE,9;
		getexp 150000000,0,1;
		getexp 0,30000000,0;
		getitem 25271, 5;
		close;
	}
	mes "[ホドニ]";
	mes "まだ知らない事実が";
	mes "あると思いませんか？";
	mes "もう少しここで";
	mes "調査を続けようと思います。";
	next;
	mes "[ホドニ]";
	mes "この現象に対する";
	mes "何かしらの解答が";
	mes "出るならいいですが。";
	close;
}

pay_d03_i.gat,152,45,3	script	兵士シンジュウヒ#ilp17	708,{
	if(IL_MOON_QUE <= 6) {
		mes "[ジュウヒ]";
		mes "何の対策もないまま";
		mes "入った時から感じてましたが、";
		mes "少しの間、ホドニと一緒に";
		mes "行動をしなければならなさそうですね。";
		next;
		mes "[ジュウヒ]";
		mes "何よりもここの九尾狐は";
		mes "亡霊たちからよくない気配が感じられます。";
		mes "…これは困ったことになりました。";
		close;
	}
	mes "[ジュウヒ]";
	mes "ここに入って来た時と";
	mes "同様の歪曲された空間があります。";
	mes "触れてみると元の廃村に";
	mes "出る事が出来ました。";
	next;
	menu "怒りの九尾狐について",-;
	if(checkquest(7785)) {
		if(checkquest(7785)&2 == 0) {
			mes "[ジュウヒ]";
			mes "九尾狐の怒りは";
			mes "一旦落ち着いたようですね。";
			mes "^4d4dff次の午前5時を過ぎたら^000000";
			mes "また来てください。";
			next;
			mes "[ジュウヒ]";
			mes "ホドニの調査によれば";
			mes "ここは月夜花の悪夢の中だそうです。";
			mes "幻影にすぎない九尾狐ですが";
			mes "こいつらが万が一";
			mes "生きている人に害を及ぼすなら";
			mes "退治するのは当然だと考えています。";
			next;
			mes "[ジュウヒ]";
			mes "死霊に慈悲も";
			mes "持たない奴だと言われても";
			mes "返す言葉はありません。";
			mes "それじゃ私はホドニと一緒に";
			mes "他の場所を見回ってみることにします。";
			close;
		}
		delquest 7785;
		mes "[ジュウヒ]";
		mes "少しは休めましたか？";
		mes "変化のない日常ですがホドニが";
		mes "付近の調査を円滑に行うために";
		mes "周辺を整理したいので";
		mes "^4d4dff怒りの九尾狐^000000を";
		mes "少し退治してくれませんか？";
		next;
		if(select("受託する","断る") == 2) {
			mes "[ジュウヒ]";
			mes "遠くまで調査に出かけることは";
			mes "出来なさそうですね。";
			close;
		}
		mes "[ジュウヒ]";
		mes "それではお願いします。";
		mes "^4d4dff怒りの九尾狐^000000の";
		mes "心情を理解できないわけでは";
		mes "ありませんけど、それはそれ";
		mes "これはこれですから。";
		setquest 7784;
		close;
	}
	if(checkquest(7784)) {
		if(checkquest(7784)&4 == 0) {
			mes "[ジュウヒ]";
			mes "周辺にいる^4d4dff怒りの九尾狐^000000を";
			mes "退治してください。";
			mes "ホドニの調査がもう少し円滑になる為です。";
			close;
		}
		mes "[ジュウヒ]";
		mes "これが実体であろうがなかろうが";
		mes "危険要素になるのは間違いありません。";
		mes "よく処理して下さいました。";
		next;
		mes "[ジュウヒ]";
		mes "ホドニの調査も終わりに";
		mes "向かっているようですし";
		mes "そろそろ帰還の準備を";
		mes "しておいた方がよさそうですね。";
		setquest 7785;
		delquest 7784;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		getitem 25271,15;
		close;
	}
	mes "[ジュウヒ]";
	mes "近くいる怒りの九尾狐たちが";
	mes "脅かしに来てホドニは調査に";
	mes "苦労しているみたいです。";
	mes "冒険者様に九尾狐たちの退治を";
	mes "お願いしたいですが……。";
	next;
	if(select("受諾する","断る") == 2) {
		mes "[ジュウヒ]";
		mes "そうですか。";
		mes "そうなると遠くまで";
		mes "調査に出かけることは";
		mes "出来なさそうですね。";
		close;
	}
	mes "[ジュウヒ]";
	mes "それではお願いします。";
	mes "^4d4dff怒りの九尾狐^000000の";
	mes "心情を理解できないわけでは";
	mes "ありませんけど、それはそれ";
	mes "これはこれですから。";
	setquest 7784;
	close;
}

pay_d03_i.gat,140,46,3	script	揺らぐ空間#ilp10	10043,{
	mes "元の廃村に戻ることができる。";
	mes "どうしようかな？";
	next;
	if(select("戻る","戻らない") == 2) {
		mes "今はやめておこう。";
		close;
	}
	warp "pay_dun03.gat",145,43;
	end;
}

pay_d03_i.gat,82,237,3	script	村人#ilp17	75,{
	mes "[村人]";
	mes "あ……ああ……";
	close;
}

pay_d03_i.gat,254,206,3	script	村人#ilp18	90,{
	mes "[村人]";
	mes "それは違う……！";
	mes "魔法を、魔法を止めて……！";
	mes "く、崩れる!!きゃああ!!";
	close;
}

pay_d03_i.gat,81,136,3	script	村人#ilp19	59,{
	mes "[村人]";
	mes "いったい私たちが";
	mes "何をしたと？";
	mes "神獣と魔物も";
	mes "区別できない奴らが……！";
	next;
	mes "[村人]";
	mes "……ああ……狐様。";
	mes "助けて……助けてよ……!!";
	close;
}

pay_d03_i.gat,160,260,3	script	村人#ilp21	59,{
	mes "[村人]";
	mes "いったい、あなた達は……。";
	mes "あの怪しい魔法使いは";
	mes "なぜ私たちを……。";
	next;
	mes "[村人]";
	mes "お前も……";
	mes "お前もあの者たちと同じだ!!";
	mes "私たちが何をした!!";
	close;
}

pay_d03_i.gat,43,150,5	script	村人#ilp22	75,{
	mes "[村人]";
	mes "どうか私たちを";
	mes "放っておいてください！";
	next;
	mes "[村人]";
	mes "私たちは魔物に";
	mes "仕えるつもりはありません。";
	next;
	mes "[村人]";
	mes "あ……光が……";
	mes "魔法……魔法を……止めてください。";
	mes "どうか……";
	mes "魔法を止めてください。どうか…";
	close;
}

pay_d03_i.gat,0,0,0	script	#IllMoonlight	-1,{
OnInit:
	for(set '@i,0;'@i<5;set '@i,'@i+1)
		areamonster "pay_d03_i.gat",40,35,160,115,"--ja--",3759+rand(3),1,"::OnSummon1";
	for(set '@i,0;'@i<5;set '@i,'@i+1)
		areamonster "pay_d03_i.gat",40,140,160,260,"--ja--",3759+rand(3),1,"::OnSummon2";
	for(set '@i,0;'@i<5;set '@i,'@i+1)
		areamonster "pay_d03_i.gat",150,180,270,260,"--ja--",3759+rand(3),1,"::OnSummon3";
	end;

OnSummon1:
	if('mob1 == 0 && rand(1000) == 0) {
		set 'mob1,callmonster("pay_d03_i.gat",96,83,"真理の魔法使い",3764,strnpcinfo(0)+"::OnKilled1");
		unittalk 'mob1,"真理の魔法使い : 真理のための礎になりなさい";
	}
	else {
		areamonster "pay_d03_i.gat",40,35,160,115,"--ja--",3759+rand(3),1,"::OnSummon1";
	}
	end;
OnKilled1:
	set 'mob1,0;
	areamonster "pay_d03_i.gat",40,35,160,115,"--ja--",3759+rand(3),1,"::OnSummon1";
	end;
OnSummon2:
	if('mob2 == 0 && rand(1000) == 0) {
		set 'mob2,callmonster("pay_d03_i.gat",94,188,"真理の魔法使い",3764,strnpcinfo(0)+"::OnKilled2");
		unittalk 'mob2,"真理の魔法使い : 真理のための礎になりなさい";
	}
	else {
		areamonster "pay_d03_i.gat",40,140,160,260,"--ja--",3759+rand(3),1,"::OnSummon2";
	}
	end;
OnKilled2:
	set 'mob2,0;
	areamonster "pay_d03_i.gat",40,140,160,260,"--ja--",3759+rand(3),1,"::OnSummon2";
	end;
OnSummon3:
	if('mob3 == 0 && rand(1000) == 0) {
		set 'mob3,callmonster("pay_d03_i.gat",210,221,"真理の魔法使い",3764,strnpcinfo(0)+"::OnKilled3");
		unittalk 'mob3,"真理の魔法使い : 真理のための礎になりなさい";
	}
	else {
		areamonster "pay_d03_i.gat",150,180,270,260,"--ja--",3759+rand(3),1,"::OnSummon3";
	}
	end;
OnKilled3:
	set 'mob3,0;
	areamonster "pay_d03_i.gat",150,180,270,260,"--ja--",3759+rand(3),1,"::OnSummon3";
	end;
}
