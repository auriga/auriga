//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Vampire Quest Script	by refis
//= Registry ===================================================================
// IL_VAMP_QUE -> 0～16
//==============================================================================

gef_dun01.gat,132,223,5	script	グリム#ilgf	110,{
	switch(IL_VAMP_QUE) {
	case 0:
		if(BaseLevel < 170) {
			mes "[グリム]";
			mes "ここは危険です。";
			mes "もっと強くなってから";
			mes "いらした方が良いかと思われます。";
			close;
		}
		mes "[モジョ]";
		mes "ちょっとだけ見せてよ。";
		mes "その後、私が向こうへ行って。";
		mes "連れ戻してくればいいよね。";
		unittalk getnpcid(0,"モジョ#ilgf"),"だよね？";
		if(!sleep2(500)) end;
		emotion 1,"モジョ#ilgf01";
		cloakonnpc "モジョ#ilgf";
		cloakoffnpc "モジョ#ilgf01";
		unittalk getnpcid(0,"モジョ#ilgf01"),"だよね？";
		if(!sleep2(500)) end;
		emotion 1,"モジョ#ilgf02";
		cloakonnpc "モジョ#ilgf01";
		cloakoffnpc "モジョ#ilgf02";
		unittalk getnpcid(0,"モジョ#ilgf02"),"だよね？";
		if(!sleep2(500)) end;
		emotion 1,"モジョ#ilgf03";
		cloakonnpc "モジョ#ilgf02";
		cloakoffnpc "モジョ#ilgf03";
		unittalk getnpcid(0,"モジョ#ilgf03"),"だよね？";
		if(!sleep2(500)) end;
		emotion 1,"モジョ#ilgf03";
		cloakonnpc "モジョ#ilgf03";
		cloakoffnpc "モジョ#ilgf";
		unittalk getnpcid(0,"モジョ#ilgf"),"だよね？";
//		unittalk getnpcid(0,"モジョ#ilgf03"),"だよね？";
		next;
		mes "[グリム]";
		mes "じっとしててください！";
		mes "気が散るじゃありませんか！";
		mes "ちょっと見たら、と言ってるけど、";
		mes "持ち逃げするつもりでしょう。";
		next;
		mes "[モジョ]";
		mes "いや、本当にちょっと見るだけだよ？";
		mes "ちょっとだけ！";
		mes "1分！　いや30秒！";
		mes "10秒だけでもいいから！";
		next;
		mes "[グリム]";
		mes "ダメです！";
		mes "指一本触れさせませんからね！";
		next;
		mes "[モジョ]";
		mes "そんなに私が信じられないの？";
		mes "今までそんなに";
		mes "騙したことあったっけ？";
		next;
		mes "[グリム]";
		mes "そうですね。";
		mes "ほぼ毎日騙されてきましたね。";
		mes "人間としてのモジョさんは";
		mes "まだ信じられても、";
		mes "魔法使いとしてのモジョさんは";
		mes "信じられません！";
		next;
		mes "[モジョ]";
		mes "あぁ……本当に、";
		mes "聖職者の信仰がこんなに薄くては";
		mes "駄目だよ？";
		mes "酷過ぎない？";
		mes "人を泥棒扱いするなんて！";
		emotion 28,"モジョ#ilgf";
		next;
		mes "[グリム]";
		mes "私の信仰心は主のためのものです。";
		mes "そしてその方は私に";
		mes "こう告げています。";
		mes "「グリムよ、";
		mes "モジョを信じることなかれ。」";
		next;
		mes "[グリム]";
		mes "今も私の耳に囁きかけておられます。";
		next;
		mes "[モジョ]";
		mes "私には聞こえないよ！";
		next;
		mes "[グリム]";
		mes "当たり前ですよ。";
		mes "もし聞こえたら魔法使いでなく";
		mes "司祭になってるでしょう。";
		emotion 6,"モジョ#ilgf";
		next;
		menu "ヒール、お願いしてもよろしいでしょうか？",-;
		emotion 18,"グリム#ilgf";
		mes "[グリム]";
		mes "もちろんです、" +(Sex? "兄弟": "姉妹")+ "。";
		mes "助けが必要でしたらいつでもどうぞ。";
		misceffect 313,"";
		next;
		mes "[モジョ]";
		mes "この二枚舌。";
		mes "これだから聖職者は";
		mes "信じられないんだ。";
		next;
		menu "言い争っていたみたいですが……",-;
		mes "[グリム]";
		mes "そんなに遠くまで聞こえましたか？";
		mes "私としたことが……";
		mes "つい熱くなってしまったようです。";
		next;
		mes "[モジョ]";
		mes "そうだ！";
		mes "どっちの意見が正しいのか、";
		mes "この冒険者様に聞いてみようよ！";
		mes "それなら公正でしょ？";
		next;
		mes "[モジョ]";
		mes "どうです、冒険者様？";
		mes "よかったら話を";
		mes "聞いてはくれませんか？";
		next;
		if(select("聞きましょう","もう帰ります。") == 2) {
			mes "[グリム]";
			mes "そうですか。";
			mes "残念です……。";
			next;
			mes "[グリム]";
			mes "もし聞きたくなったら、";
			mes "いつでもお尋ねください。";
			close;
		}
		mes "[グリム]";
		mes "ふう……";
		mes "わかりました。";
		mes "それでは少し長くなるので、";
		mes "水でも飲んでから始めましょうか。";
		setquest 14652;
		set IL_VAMP_QUE,1;
		close;
	case 1:
		mes "[グリム]";
		mes "冒険者様、";
		mes "このゲフェンの地下墓地が";
		mes "かつては特別な力が流れる";
		mes "静かな墓地だったのをご存じですか？";
		next;
		mes "[グリム]";
		mes "モンスターが溢れる今とは違い、";
		mes "あの不敬な輩が特別な力で";
		mes "彷徨いだすのは";
		mes "十年に一度か二度ぐらいの";
		mes "頻度でした。";
		next;
		menu "なぜ今はこうなりましたか？",-;
		emotion 54,"グリム#ilgf";
		mes "[グリム]";
		mes "チラッ";
		next;
		emotion 1,"モジョ#ilgf";
		mes "[モジョ]";
		mes "なんでこっちを見るのよ？";
		next;
		mes "[グリム]";
		mes "昔、魔法使いたちが自分たちの塔を";
		mes "建てる場所を探して、";
		mes "大陸のあちこちを探した結果、";
		mes "この静かな地下墓地の上に";
		mes "建てることに決めたのです。";
		next;
		mes "[グリム]";
		mes "そして、そこから全ての悲劇が";
		mes "始まったのです。";
		emotion 7,"モジョ#ilgf";
		next;
		mes "[モジョ]";
		mes "あ、またその話をするー！";
		next;
		mes "[グリム]";
		mes "「毛が生えた生き物の";
		mes "好奇心は食欲に勝る」";
		mes "などと言いますが、";
		mes "魔法使いは加減というものを知らず、";
		mes "多くの人に苦労をかける";
		mes "ものなんです。";
		next;
		mes "[グリム]";
		mes "とにかく、魔法使いたちが";
		mes "ゲフェンタワーを建てると、";
		mes "地下の不敬な者たちに";
		mes "目が行くのは";
		mes "当然のことだったかも知れません。";
		next;
		mes "[グリム]";
		mes "彼らは死者たちが";
		mes "特別な力によって動いてるのを見て、";
		mes "様々な実験を施したんです。";
		next;
		mes "[モジョ]";
		mes "……真理を探究したと言ってよ。";
		next;
		mes "[グリム]";
		mes "小さな実験で終わっていたら";
		mes "良かったんでしょうが、";
		mes "やがてあの不敬な者たちのように";
		mes "命の無いものを動かそうと、";
		mes "魔力を使ってあらゆる生命体を";
		mes "創る実験を始めました。";
		next;
		mes "[グリム]";
		mes "そしてある時、";
		mes "少しずつ流れだした特別な力が、";
		mes "爆発してしまいました。";
		mes "その結果、静かだった地下墓地が";
		mes "今のような化け物だらけに";
		mes "なってしまったんです。";
		next;
		mes "[グリム]";
		mes "人として超えてはいけないラインを";
		mes "超えてしまったんです！";
		mes "それは神に対する冒涜に等しい！";
		next;
		emotion 7,"モジョ#ilgf";
		mes "[モジョ]";
		mes "あ、魔法使いの前で";
		mes "酷い言いぐさだね？";
		mes "私的な感情を込めないでくださる？";
		next;
		mes "[グリム]";
		mes "私の言葉にひと欠片の嘘でも";
		mes "ありましたか？";
		next;
		mes "[グリム]";
		mes "いかがですか、冒険者様？";
		mes "冒険者様なら慎重を期することに、";
		mes "好奇心で大きな災いを";
		mes "引き起こすような人たちに";
		mes "何かを頼みますか？";
		next;
		menu "それはちょっと……危険ですね。",-;
		mes "[モジョ]";
		mes "ちょっと待って！　冒険者様！";
		mes "私の話も聞いてくださいよ。";
		next;
		mes "[モジョ]";
		mes "真理を追究する過程において、";
		mes "その方法が常に正しいとか、";
		mes "良い結果だけを引き起こすわけでは";
		mes "ないということは、";
		mes "もちろん私たちは理解しています。";
		mes "だから注意もしています。";
		next;
		mes "[モジョ]";
		mes "確かに魔法使いたちが";
		mes "やり過ぎたことはありますが、";
		mes "それはもう過ぎたことです。";
		mes "その実験のおかげで魔法と都市が";
		mes "発展したことも事実じゃないですか？";
		next;
		mes "[モジョ]";
		mes "アルナベルツと";
		mes "シュバルツバルドという、";
		mes "そうそうたる国を両脇においた";
		mes "ルーンミッドガッツ王国が、";
		mes "どちらとも対等な国に成長したのは";
		mes "魔法のおかげじゃないですか。";
		next;
		mes "[グリム]";
		mes "そのことをある程度鑑みるとしても、";
		mes "土の中で安らぎを得るはずの人々が";
		mes "苦しめられているのも";
		mes "事実ではありませんか？";
		next;
		mes "[グリム]";
		mes "そして教会もゲフェンタワーの";
		mes "功績を認めているからこそ、";
		mes "これ以上文句言わないことは、";
		mes "何故お話ししないのです？";
		next;
		mes "[モジョ]";
		mes "ちょっとグリムさん？";
		mes "他人と会話中に";
		mes "入り込まないでくださる？";
		next;
		mes "[モジョ]";
		mes "好奇心は生を変える原動力であり、";
		mes "大きな発展の種です。";
		mes "例えば今すぐ誰も行ったことのない";
		mes "新世界を拝めるとしたら、";
		mes "冒険者様は危険だというだけで";
		mes "躊躇したりしますか？";
		next;
		menu "そこで躊躇するなら、冒険者ではありません。",-;
		mes "[モジョ]";
		mes "ですよね！";
		mes "私たち魔法使いは未知の領域を";
		mes "探検し研究する冒険者なんですよ！";
		mes "やはり冒険者様なら";
		mes "理解してもらえると思いました。";
		emotion 33,"モジョ#ilgf";
		next;
		mes "[モジョ]";
		mes "グリムさん、聞いた？　聞きました？";
		mes "ということであのノートを見せて！";
		next;
		mes "[グリム]";
		mes "それはダメです。";
		mes "冒険者様もことの危険性を";
		mes "わかってくれたんじゃありませんか？";
		next;
		mes "[モジョ]";
		mes "探検の必要性にも認めたでしょ！";
		next;
		menu "いったい何のことですか？",-;
		mes "[グリム]";
		mes "あ、お互いのことだけ話して、";
		mes "肝心なことを説明して";
		mes "いませんでしたね。";
		mes "申し訳ありません。";
		next;
		mes "[グリム]";
		mes "我らルーンミッドガッツの教会では、";
		mes "あの不敬な者たちの数が";
		mes "増え過ぎないように、";
		mes "定期的に司祭団を送って";
		mes "退治をしておりました。";
		next;
		mes "[グリム]";
		mes "今回も定期退治に来たのですが、";
		mes "ここでこんな^0000cdノート^000000を拾ったんです。";
		next;
		menu "ノートですか？",-;
		mes "[グリム]";
		mes "はい。ゲフェンタワーの魔法使いが";
		mes "落としたものだと思い、";
		mes "確認のためノートを見たら";
		mes "^0000cdボミ^000000という名前が書かれてました。";
		mes "多分持ち主の名でしょう。";
		next;
		mes "[モジョ]";
		mes "しかし、私たちはそんな名前、";
		mes "記憶にありません。";
		mes "内容を読んでみると、";
		mes "ギルド所属なのは間違いないですが。";
		mes "^0000cd現在^000000はそんな人はいません。";
		next;
		menu "現在？",-;
		emotion 33,"モジョ#ilgf";
		mes "[モジョ]";
		mes "冒険者様、感が鋭いですね。";
		mes "ギルドに問い合わせてみたら、";
		mes "遥か昔にいたらしいです。";
		mes "ボミという人がある日突然、";
		mes "行方をくらませたようですね。";
		next;
		menu "何故それが今ここに？",-;
		mes "[モジョ]";
		mes "私たちも最初はそれが";
		mes "気になったんですが、";
		mes "ノートを調べたら";
		mes "「何故？」というより";
		mes "「どうやって？」という疑問が";
		mes "浮かんできました。";
		next;
		mes "[グリム]";
		mes "内容も内容ですが、";
		mes "それより深刻なのは……";
		mes "いや直接ご覧になってください。";
		mes "だけど^0000cd最後のページ^000000までは";
		mes "めくらないように注意してください。";
		next;
		mes "[モジョ]";
		mes "うわー！";
		mes "私には見せてくれないくせに！";
		mes "差別だー！";
		mes "これが聖職者のやることかー！";
		next;
		mes "[グリム]";
		mes "モジョさんのことは気にせず、";
		mes "ご覧になってください。";
		chgquest 14652,14653;
		set IL_VAMP_QUE,2;
		close;
	case 2:
		mes "‐グリム司祭の持った本に";
		mes "　手を乗せると、";
		mes "　軽い立ちくらみがして";
		mes "　周りが揺らぐような気がした。";
		mes "　用心深くページをめくってみた‐";
		next;
		mes "[○○○日目]";
		mes "新しい呪文を取得する過程で、";
		mes "耐え切れずまた倒れてしまった。";
		mes "少ない体力、少ないマナが";
		mes "常に足を引っ張る。";
		next;
		mes "[○○○日目]";
		mes "ソフィアがマナポーションを";
		mes "飲むのを見た。";
		mes "今まで弱い肉体を魔法の力で";
		mes "克服しようと考えてきたが";
		mes "それは最善ではなさそうだ。";
		next;
		mes "普通の薬ではなく、特殊な薬ならば？";
		mes "魔法ではなく体質を改善したら";
		mes "私も強くなれるのではないか？";
		next;
		mes "[○○○日目]";
		mes "手に入るポーションは";
		mes "弱い肉体を補うものではなく、";
		mes "普通の肉体を基盤にする";
		mes "増幅剤ばかりで、";
		mes "どれも私に向いてなかった。";
		next;
		mes "だけど、私に適した筋力と魔力の";
		mes "強化剤みたいな物を、";
		mes "自分の手で作れるのでは";
		mes "ないだろうか？";
		next;
		mes "[○○○日目]";
		mes "図書館でゲフェンタワーの歴史を";
		mes "読んで、地下墓場に関して知った。";
		mes "どうやって死者たちは";
		mes "動いてるんだろう？";
		mes "その生命力はいったいなんだろう？";
		next;
		mes "墓場に行くには許可が必要か……。";
		mes "とにかく明日、墓場に行ってみよう。";
		next;
		mes "[○○○日目]";
		mes "死人に口無し。";
		mes "残念ながら……調査しても";
		mes "新たな発見は無かった。";
		next;
		mes "前に何かあったのか、";
		mes "実験の痕跡があちこちに残されてる。";
		mes "多分ギルド員の仕業だろ。";
		mes "今日はやけに疲れた。早く寝なきゃ。";
		next;
		mes "[○○○日目]";
		mes "墓場の蝙蝠たちは食べ物がないから";
		mes "ゾンビたちの血を吸っている。";
		mes "そして今日も私の血を吸おうと";
		mes "襲ってくる。";
		next;
		mes "蝙蝠を処理するのに苦労した。";
		mes "入口の近くじゃなかったら";
		mes "死んでたかも。";
		mes "疲れた。";
		next;
		mes "[○○○日目]";
		mes "本日は墓場から奇妙な音が聞こえた。";
		mes "ゾンビも蝙蝠もみんな、";
		mes "不思議なほど大人しい。";
		mes "何があったのかわからないが、";
		mes "モンスターが大人しい隙を狙って、";
		mes "明日はより深く潜ってみよう。";
		next;
		mes "‐読めるのはこの辺までだった。";
		mes "　ノートから手を離すと、";
		mes "　グリム司祭がノートを閉じた‐";
		chgquest 14653,14654;
		set IL_VAMP_QUE,3;
		close;
	case 3:
		mes "[グリム]";
		mes "これは^0000cd日記兼研究ノート^000000です。";
		mes "とある魔法使いが、不敬な者たちの";
		mes "奇怪な生命力を利用して";
		mes "^0000cd筋力と魔力を強化する薬物";
		mes "に関する研究^000000をした内容が";
		mes "書かれております。";
		next;
		menu "凄く興味深いですね。",-;
		emotion 33,"モジョ#ilgf";
		mes "[モジョ]";
		mes "同感です。";
		mes "これは魔術師ギルドの方で";
		mes "研究すべきものですよ。";
		mes "当時の記録は今じゃ";
		mes "殆ど廃棄されていますからね。";
		next;
		mes "[グリム]";
		mes "だがこのノートは";
		mes "それだけではありません。";
		mes "本に触れた時、^0000cd奇妙な気配^000000を";
		mes "感じませんでしたか？";
		next;
		mes "[グリム]";
		mes "このノートから強い思念が";
		mes "感じられます。";
		mes "ノートの持ち主が残した強い思念で、";
		mes "ノートを手に入れた者を";
		mes "^0000cd中に引きずり込もうとしています。^000000";
		next;
		mes "[モジョ]";
		mes "「なぜ？」という疑問より";
		mes "「どうやって？」の方が";
		mes "気になりますよね？";
		mes "それがどうやって可能なのか、";
		mes "なぜ今更見つかったのか、";
		mes "知りたくありませんか？";
		next;
		mes "[モジョ]";
		mes "だからちょっと貸してよ！";
		mes "マジでちょっと読むだけだから。";
		mes "私が解明してみせるんだから！";
		next;
		mes "[グリム]";
		mes "魔法使いはじっとしていなさい！";
		mes "このノートは手にしたものを";
		mes "どこかへ引っ張っていきます。";
		mes "ノートの最後のページを開くと";
		mes "そのどこかへ行けることが";
		mes "解明されたんです。";
		next;
		mes "[モジョ]";
		mes "もはや名前すら呼んでくれない！";
		next;
		mes "[グリム]";
		mes "入念に調べてみると、";
		mes "邪悪な気配はありませんでした。";
		mes "微かな悲しみ、人情、渇望……";
		next;
		mes "[グリム]";
		mes "多分このノートの持ち主は";
		mes "ノートを手に入れた者に";
		mes "^0000cd伝えたい言葉があるか、";
		mes "強い渇望を解消^000000したいのでは";
		mes "ないでしょうか。";
		next;
		mes "[グリム]";
		mes "既に司祭団と魔法使いが";
		mes "試しに向こう側へ行きました。";
		mes "それからだいぶ時間が経っているのに";
		mes "未だに戻ってきません。";
		next;
		menu "では、私が行ってみましょうか？",-;
		mes "[グリム]";
		mes "冒険者様が？";
		mes "ふむ……";
		mes "確かにこの魔法使いよりは";
		mes "頼りになると思いますが、";
		mes "大丈夫ですか？";
		next;
		menu "連れ戻せば良いですか？",-;
		mes "[グリム]";
		mes "そこまでは必要ありません。";
		mes "冒険者様が^0000cd彼らを見つけて^000000";
		mes "無事を確認し、";
		mes "助けが必要なら助けを、";
		mes "伝言があればそれを持ち帰って";
		mes "くだされば結構です。";
		next;
		mes "[モジョ]";
		mes "はい！　はい!!";
		mes "私も！　私も!!";
		next;
		mes "[グリム]";
		mes "私が行けたらいいのですが、";
		mes "ここを護る義務があるだけでなく……";
		mes "チラッ";
		next;
		mes "[モジョ]";
		mes "なんでまた私を見るのよ！";
		next;
		mes "[グリム]";
		mes "残った人が信用できない故に、";
		mes "私がこのノートを";
		mes "護らなければなりません。";
		mes "下手をしたら向こう側にいる人が";
		mes "戻れなくなる恐れがあります。";
		next;
		mes "[モジョ]";
		mes "なら、私も一緒に！";
		next;
		mes "[グリム]";
		mes "モジョさんはここで私と";
		mes "待機しましょう。";
		mes "ノートに触れようと";
		mes "思わないでくださいね。";
		next;
		emotion 28,"モジョ#ilgf";
		mes "[モジョ]";
		mes "何で？";
		mes "私が司祭様に何かしたっけ？";
		next;
		mes "[グリム]";
		mes "ジョジョさんからモジョさんが";
		mes "ノートに触れさせないようにと";
		mes "申し渡されました。";
		mes "忘れましたか？";
		next;
		mes "[モジョ]";
		mes "知らん！";
		mes "思い出せない！";
		mes "シスター・ジェムが戻ったら、";
		mes "グリムさんが私にしたことを";
		mes "全部言いつけてやるからね！";
		next;
		mes "[グリム]";
		mes "では冒険者様、準備ができたら";
		mes "いつでも声をかけてください。";
		chgquest 14654,14655;
		set IL_VAMP_QUE,4;
		close;
	default:
		mes "[グリム]";
		mes "準備は良いですか？";
		mes "ノートの向こう側へ";
		mes "行きますか？";
		next;
		if(select("はい。送ってください","いいえ") == 2) {
			mes "[グリム]";
			mes "わかりました。";
			mes "準備を済ませたら、";
			mes "いつでも声をかけてください。";
			close;
		}
		mes "[グリム]";
		mes "では、ノートを開きます。";
		next;
		mes "‐ノートに手を乗せると、";
		mes "　グリム司祭が最後のページを";
		mes "　めくった。";
		mes "　目の前が微かになり、";
		mes "　どこかへ吸い込まれる気がした‐";
		if(IL_VAMP_QUE == 4) {
			chgquest 14655,14656;
			set IL_VAMP_QUE,5;
		}
		close2;
		warp "gef_d01_i.gat", 114, 216;
		end;
	case 15:
		mes "[グリム]";
		mes "私の話を聞いてください。";
		mes "それか、タワーにお戻りください。";
		next;
		emotion 39,"モジョ#ilgf";
		mes "[モジョ]";
		mes "いーやー！";
		next;
		menu "まだ言い争ってますか？",-;
		mes "[モジョ]";
		mes "あ！";
		mes "やっと帰ってきた！";
		mes "向こうはどうでした？";
		next;
		mes "[グリム]";
		mes "冒険者様、ご無事でなによりです。";
		mes "みなさんは無事でしたか？";
		next;
		mes "‐グリム司祭とモジョさんに";
		mes "　ノートの向こう側の話をした。";
		mes "　一行は監視のため残っているとの";
		mes "　伝言を伝えた‐";
		next;
		emotion 52,"モジョ#ilgf";
		mes "[モジョ]";
		mes "うわー、すっげー！";
		mes "ここと同じようで";
		mes "全然違う世界とか！";
		next;
		mes "[モジョ]";
		mes "そんなの初めて聞いた！";
		mes "どんな原理だろ？";
		mes "やっぱこのノートが";
		mes "何かの働きをするのかな？";
		next;
		mes "[モジョ]";
		mes "しかも人間を理解する";
		mes "ヴァンパイア！";
		mes "もうこれは……！";
		next;
		mes "[モジョ]";
		mes "こうしちゃいられない！";
		mes "グリムさん！";
		mes "なんとしても行かなきゃ！";
		mes "行かせてください！　お願いします！";
		next;
		mes "[グリム]";
		mes "何があろうとも阻止します。";
		mes "手を離してください。";
		next;
		mes "[モジョ]";
		mes "あぁ、もう、ほんと！";
		mes "堅物過ぎるんだから！";
		next;
		mes "[グリム]";
		mes "冒険者様、";
		mes "慣れない場所で苦労したでしょう。";
		mes "もし時間が許されるのなら、";
		mes "たまに向こう側にいる人達の";
		mes "状況を伝えてくだされば幸いです。";
		next;
		mes "[モジョ]";
		mes "そんなことは私にお任せあれ！";
		mes "私、出来る子なんです！";
		next;
		mes "[グリム]";
		mes "モジョさんは黙ってらっしゃい。";
		next;
		mes "[グリム]";
		mes "冒険者様、";
		mes "本当にありがとうございました。";
		mes "これからも";
		mes "^0000cdノートの向こう側に行く時は、^000000";
		mes "私に声をかけてください。";
		chgquest 14666,202090;
		set IL_VAMP_QUE,16;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		getitem 25271,10;
		close;
	case 16:
		mes "[グリム]";
		mes "冒険者様、";
		mes "ノートの向こう側へ行きますか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[グリム]";
			mes "わかりました。";
			mes "必要になったら";
			mes "またいらしてください。";
			close;
		}
		mes "[グリム]";
		mes "では、";
		mes "今日もよろしくお願いいたします。";
		close2;
		warp "gef_d01_j.gat", 114, 216;
		end;
	}
}

gef_dun01.gat,134,224,1	script	モジョ#ilgf	123,{
	if(IL_VAMP_QUE == 0) {
		mes "[モジョ]";
		mes "冒険者様が何か用ですか？";
		mes "今ちょっと忙しくて……";
		mes "もし用事があるなら";
		mes "そこの司祭に話してください。";
		close;
	}
	else if(IL_VAMP_QUE < 4) {
		mes "[モジョ]";
		mes "ノート、ノート読みたい……";
		mes "ノート……。";
		close;
	}
	else if(IL_VAMP_QUE < 16) {
		mes "[モジョ]";
		mes "ノート、ノート読みたい……";
		mes "ノート……。";
		mes "ノートの向こう側に行くのでしたら、";
		mes "グリム司祭に話しかけてください。";
		mes "私も連れていって欲しい……。";
		close;
	}
	mes "[モジョ]";
	mes "あぁ～ノート、";
	mes "一回でも読めたらいいのにな～。";
	next;
	mes "[グリム]";
	mes "夢にも思わないことです。";
	next;
	mes "[モジョ]";
	mes "ノート！　ノート！";
	close;
}

gef_dun01.gat,133,221,1	script	モジョ#ilgf01	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_dun01.gat,130,222,5	script	モジョ#ilgf02	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_dun01.gat,130,224,5	script	モジョ#ilgf03	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,113,230,5	script	ジェム#ilgf01	79,{
	switch(IL_VAMP_QUE) {
	case 5:
		mes "[ジェム]";
		mes "アントワーヌさんはここに残って、";
		mes "私とマリナさんが行きます。";
		mes "異議ありますか？";
		next;
		mes "[マリナ]";
		mes "戦闘専門の私と";
		mes "アントワーヌさんで行きます。";
		mes "シスタージェムは残ってください。";
		mes "私の方が足が速いですし。";
		next;
		mes "[アントワーヌ]";
		mes "マリナさんが残り、";
		mes "僕とシスタージェムの二人の方が";
		mes "いいんじゃないですか？";
		mes "個々の能力を見ると、";
		mes "そちらがバランスが取れそうです。";
		next;
		mes "[ジェム]";
		mes "それはいけません。";
		mes "ここは不敬な者たちで一杯です。";
		mes "聖職者二人で探した方が";
		mes "やり易いです。";
		next;
		mes "[アントワーヌ]";
		mes "魔法使いとしては";
		mes "聞き逃せませんね！";
		mes "僕もゾンビ相手に上手く戦えますよ！";
		next;
		mes "[マリナ]";
		mes "むしろ二人が残り、";
		mes "一人が探索したらどうです？";
		next;
		mes "[ジェム]";
		mes "それはいけません。";
		mes "二人の方がもしもの事態に";
		mes "対応できますから。";
		next;
		mes "[アントワーヌ]";
		mes "もしここに一人で残った方に";
		mes "何かが起きたらどうしますか？";
		next;
		menu "あの……グリム司祭の使いですが。",-;
		mes "[マリナ]";
		mes "ん？　助っ人？";
		next;
		menu "何があったんですか？",-;
		mes "[マリナ]";
		mes "人を探さなくてはなりません。";
		next;
		mes "[アントワーヌ]";
		mes "結論だけ言ってどうするんですか！";
		mes "冒険者様、ここがどういう所なのか";
		mes "説明は聞きましたか？";
		mes "ことを急ぐので、";
		mes "かいつまんで説明します。";
		next;
		mes "[アントワーヌ]";
		mes "ここは現実のゲフェンの地下墓地と";
		mes "殆ど同じ場所です。";
		mes "多分、ノートの持ち主の";
		mes "記憶した姿なのでしょう。";
		next;
		mes "[アントワーヌ]";
		mes "僕たちはここがどんな力で、";
		mes "何の目的で作られたのかを";
		mes "調査しに来ました。";
		next;
		mes "[アントワーヌ]";
		mes "目に留まるものも特になく、";
		mes "調査を切り上げようとした時、";
		mes "一緒に来ていた^0000cd司祭と魔法使い^000000が";
		mes "いないことに気づきました。";
		next;
		mes "[アントワーヌ]";
		mes "辺りを探しましたが、";
		mes "ノートの持ち主の過去の記憶と";
		mes "混在した状況で……";
		mes "凄い数の魔法使いの幻が";
		mes "あちこちに現れたり";
		mes "消えたりしています。";
		next;
		mes "[アントワーヌ]";
		mes "きりがないので";
		mes "区域をわけて探そうと決めて、";
		mes "意見を交わしていた";
		mes "ところでして……。";
		next;
		mes "[アントワーヌ]";
		mes "……そんなところに冒険者様が";
		mes "いらしてくれて、本当に助かります。";
		mes "誰が残り、誰が探しに行くのか";
		mes "話していたのですが、";
		mes "四人になったので^0000cd二人ずつに分かれて^000000";
		mes "探しに行けば良いでしょう。";
		next;
		menu "消えた人達の特徴は？",-;
		mes "[ジェム]";
		mes "消えた司祭の名は^0000cdジュビリー^000000で、";
		mes "魔法使いの名は^0000cdジョジョ^000000です。";
		mes "典型的な聖職者と魔法使いの";
		mes "服装だから、すぐわかるでしょう。";
		next;
		mes "[マリナ]";
		mes "それじゃ私が行ってくる！";
		mes "冒険者様、行きましょう！";
		next;
		mes "[ジェム]";
		mes "行く前に祈りを捧げましょう。";
		mes "神よ、どうかお守りください。";
		cloakoffnpc "マリナ#ilgf03";
		cloakoffnpc "マリナ#ilgf04";
		cloakoffnpc "マリナ#ilgf05";
		cloakoffnpc "マリナ#ilgf06";
		cloakoffnpc "マリナ#ilgf07";
		cloakoffnpc "マリナ#ilgf08";
		cloakoffnpc "マリナ#ilgf09";
		chgquest 14656,14657;
		set IL_VAMP_QUE,6;
		npcskillsupport 34,10,"","";	// ブレッシング
		sc_start SC_BLESSING,240000,10;
		npcskillsupport 29,10,"","";	// 速度増加
		sc_start SC_INCREASEAGI,240000,10;
		close;
	case 6:
		mes "[ジェム]";
		mes "ジュビリーとジョジョが";
		mes "無事だといいですけどね。";
		next;
		mes "[ジェム]";
		mes "もしお帰りになるのなら、";
		mes "マリナに話しかけてください。";
		mes "元の場所へ送らせますから。";
		close;
	case 7:
		cloakonnpc "ドラキュラ#ilgf02";
		cloakonnpc "キング#ilgf01";
		cloakonnpc "魔法使い#ilgf02";
		cloakoffnpc "魔法使い#ilgf01";
		mes "[ジェム]";
		mes "ジュビリーは怪我の治療のため";
		mes "地上に戻しましたが、";
		mes "ジョジョがまだ……";
		mes "どうか無事でいて欲しいです。";
		next;
		mes "[ジェム]";
		mes "もしお帰りになるのなら、";
		mes "マリナに話しかけてください。";
		mes "元の場所へ送らせますから。";
		close;
	case 8:
		mes "[ジェム]";
		mes "ジョジョの安否が心配です。";
		next;
		mes "[ジェム]";
		mes "もしお帰りになるのなら、";
		mes "マリナに話しかけてください。";
		mes "元の場所へ送らせますから。";
		close;
	case 14:
		mes "[ジェム]";
		mes "冒険者様。";
		mes "もうお戻りになられますか？";
		next;
		menu "みなさんの無事も確認できましたし",-;
		mes "[ジェム]";
		mes "私たちの調査の結果、";
		mes "ここでの出来事は「外側」には";
		mes "^0000cd影響を与えない^000000ようです。";
		mes "何故なのかはわかりませんが、";
		mes "幸いなことです。";
		next;
		mes "[ジェム]";
		mes "しかし監視は必要です。";
		mes "冒険者様なら";
		mes "ご理解していただけますよね？";
		mes "グリム司祭にもそう伝えてください。";
		next;
		menu "しかし、意外でした。",-;
		mes "[マリナ]";
		mes "ヴァンパイアを";
		mes "すぐ処理するかと思いましたか？";
		mes "原則なら、その通りです！";
		next;
		mes "[ジェム]";
		mes "そうです。";
		mes "原則に従うならそうなりますね。";
		mes "しかし彼らを見ていたら……";
		mes "滅ぼすべき対象なのか？";
		mes "という疑問が浮かびました。";
		next;
		mes "[ジェム]";
		mes "もう少し様子をみる必要があります。";
		next;
		emotion 36,"マリナ#ilgf01";
		mes "[マリナ]";
		mes "ちょっとでも間違いを犯したら、";
		mes "私が即、倒します！";
		next;
		emotion 33,"アントワーヌ#ilgf01";
		mes "[アントワーヌ]";
		mes "はい、もしそんな時が来たら、";
		mes "私の分まで思う存分";
		mes "暴れてくださいね。";
		next;
		mes "[ジェム]";
		mes "それではグリム司祭に";
		mes "よろしく伝えておいてください。";
		mes "お疲れ様でした。";
		chgquest 14665,14666;
		set IL_VAMP_QUE,15;
		close2;
		warp "gef_dun01.gat", 133, 219;
		end;
	case 15:
		mes "[ジェム]";
		mes "グリム司祭に、";
		mes "ここに残ると伝えてください。";
		next;
		mes "[ジェム]";
		mes "外に出るには";
		mes "マリナに頼んでください。";
		close;
	}
}

gef_d01_i.gat,112,228,5	script	マリナ#ilgf01	746,{
	mes "[マリナ]";
	mes "元の場所に戻りますか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[マリナ]";
		mes "わかりました。";
		mes "戻る時はいつでも";
		mes "声をかけてください。";
		close;
	}
	mes "[マリナ]";
	mes "足元にご注意ください。";
	close2;
	warp "gef_dun01.gat", 133, 219;
	end;
}

gef_d01_i.gat,93,178,5	script	マリナ#ilgf03	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf03"),"マリナ : 東の方から微かな気配を感じます。早く行ってみましょう！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf03";
	cloakonnpc "マリナ#ilgf03";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,127,153,5	script	マリナ#ilgf04	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf04"),"マリナ : 東の方の気配が強く段々強くなります。急いでください！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf04";
	cloakonnpc "マリナ#ilgf04";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,213,237,5	script	マリナ#ilgf05	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf05"),"マリナ : 南の方から微かな気配を感じます。急いでください！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf05";
	cloakonnpc "マリナ#ilgf05";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,150,224,5	script	マリナ#ilgf06	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf06"),"マリナ : 東の方から微かな気配を感じます。早く行ってみましょう！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf06";
	cloakonnpc "マリナ#ilgf06";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,208,144,5	script	マリナ#ilgf07	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf07"),"マリナ : 気配が近づいています！　あと少し東です！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf07";
	cloakonnpc "マリナ#ilgf07";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,250,130,5	script	マリナ#ilgf08	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf08"),"マリナ : 北へ行ってみましょう！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf08";
	cloakonnpc "マリナ#ilgf08";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,255,202,5	script	マリナ#ilgf09	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"マリナ#ilgf09"),"マリナ : 南側へ行ってみましょう！";
	if(!sleep2(1500)) end;
	misceffect 304,"マリナ#ilgf09";
	cloakonnpc "マリナ#ilgf09";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,116,228,3	script	アントワーヌ#ilgf01	669,{
	if(IL_VAMP_QUE <= 5) {
		mes "[アントワーヌ]";
		mes "シスタージェム、";
		mes "僕の話を聞いてください！";
		close;
	}
	else if(IL_VAMP_QUE == 6) {
		mes "[アントワーヌ]";
		mes "二人のご無事を祈ってますが……";
		mes "少し心配です。";
		mes "何かあったんでしょうか。";
		close;
	}
	else if(IL_VAMP_QUE == 7) {
		mes "[アントワーヌ]";
		mes "ジョジョはまだですよね？";
		mes "少し心配ですね。";
		mes "ジュビリーさんは治療のため、";
		mes "地上に戻りました。";
		close;
	}
	mes "[アントワーヌ]";
	mes "ここは興味深い物が多過ぎて";
	mes "何から手をつけたら良いか";
	mes "悩ましいですね。";
	close;
}

gef_d01_i.gat,250,164,5	script	司祭#ilgf01	110,5,5,{
	if(IL_VAMP_QUE == 6) {
		mes "[司祭]";
		mes "困ったな。";
		mes "足がこれじゃ動けないし、";
		mes "気力もなくて";
		mes "テレポートもできないし……。";
		next;
		emotion 28,"司祭#ilgf01";
		mes "[司祭]";
		mes "はっ！";
		mes "まさか、これで終わりか？";
		mes "死ぬのか？";
		mes "死ぬだろうね……こんな場所で……。";
		if(!sleep2(1000)) end;
		cloakoffnpc "アンデッド#ilgf08";
		cloakoffnpc "アンデッド#ilgf09";
		unittalk getnpcid(0,"アンデッド#ilgf08"),"アンデッド : グルルルルル……。";
		unittalk getnpcid(0,"アンデッド#ilgf09"),"アンデッド : ぐおおおおお……。";
		next;
		mes "[司祭]";
		mes "ぎゃぁー！";
		mes "また現れた！";
		mes "助けて……。";
		next;
		menu "典型的な司祭の服装……？",-;
		misceffect 304,"マリナ#ilgf10";
		cloakoffnpc "マリナ#ilgf10";
		unittalk getnpcid(0,"マリナ#ilgf10"),"マリナ : こんなところに居ましたか？";
		next;
		mes "[マリナ]";
		mes "ジュビリー！";
		next;
		mes "[ジュビリー]";
		mes "あ、マリナさん！";
		mes "助けてください！";
		mes "マリナさんが後悔しないためにも、";
		mes "私を助けて！";
		if(!sleep2(1000)) end;
		misceffect 315,"司祭#ilgf01";
		next;
		mes "[マリナ]";
		mes "全ての死人たちを土へ！";
		unittalk getnpcid(0,"マリナ#ilgf10"),"マリナ : ターンアンデッド！";
		if(!sleep2(1000)) end;
		misceffect 82,"アンデッド#ilgf08";
		misceffect 82,"アンデッド#ilgf09";
		unittalk getnpcid(0,"アンデッド#ilgf08"),"アンデッド : くわああああ！";
		unittalk getnpcid(0,"アンデッド#ilgf09"),"アンデッド : ぐるるるるる！";
		if(!sleep2(1000)) end;
		misceffect 372,"アンデッド#ilgf08";
		misceffect 372,"アンデッド#ilgf09";
		cloakonnpc "アンデッド#ilgf08";
		cloakonnpc "アンデッド#ilgf09";
		next;
		unittalk getnpcid(0,"マリナ#ilgf10"),"マリナ : 大丈夫ですか？";
		next;
		mes "[マリナ]";
		mes "一体なにがあったんです？";
		mes "ジョジョさんは？";
		next;
		mes "[ジュビリー]";
		mes "ジョジョさんと共に";
		mes "この周辺を調査してましたが、";
		mes "光ってるキノコを発見した";
		mes "ジョジョさんの眼がキラリと……。";
		next;
		mes "[マリナ]";
		mes "これだから";
		mes "魔法使いは……。";
		next;
		mes "[ジュビリー]";
		mes "ジョジョさんが";
		mes "キノコに触れた瞬間、";
		mes "キノコが爆発したんですよ。";
		next;
		mes "[ジュビリー]";
		mes "気がついたらジョジョさんは";
		mes "居なくなっていて、";
		mes "私は足を怪我して";
		mes "動けなくなっていたんですよ。";
		next;
		mes "[マリナ]";
		mes "なんと、キノコにやられたんですね？";
		next;
		mes "[ジュビリー]";
		mes "マリナさん、";
		mes "ここのキノコを見ましたか？";
		mes "あの光るキノコは";
		mes "外のキノコとは全然違います！";
		mes "まるで……間違って触れたら爆発する";
		mes "小さな爆弾みたいです。";
		next;
		menu "気を付けないと",-;
		mes "[マリナ]";
		mes "ジュビリーさん、動けますか？";
		next;
		mes "[ジュビリー]";
		mes "一人で動けたら、合流してましたね。";
		next;
		menu "自己治療しないんですか？",-;
		mes "[マリナ]";
		mes "私たちは聖職者としての";
		mes "基本的な訓練はしますが、";
		mes "主な能力は各自で異なります。";
		next;
		mes "[ジュビリー]";
		mes "私の得意は聖歌です。";
		mes "オーディンの意を讃え広めることが、";
		mes "私の喜びであり生きがいなんです。";
		next;
		mes "[マリナ]";
		mes "卑屈にならないでください。";
		mes "ジュビリーさんの歌を聞くと、";
		mes "勇気と力が湧いて来ます。";
		mes "だからこのゲフェンまで";
		mes "共に参られたんですよ。";
		next;
		mes "[マリナ]";
		mes "冒険者様、私はジュビリーさんを";
		mes "シスタージェムのいるところまで";
		mes "連れて行きますから、";
		mes "周辺を探ってみてください。";
		mes "ジュビリーを連れ戻したら、";
		mes "すぐに合流します。";
		next;
		mes "[ジュビリー]";
		mes "お気をつけて。";
		mes "ここにはノートの持ち主の記憶が";
		mes "断続的に現れては消えたりします。";
		mes "注意深く見てないと、";
		mes "幻に惑わされるかも知れません。";
		next;
		mes "[ジュビリー]";
		mes "しかも……";
		mes "邪悪な気配まで感じられます。";
		mes "どうか気をつけて……。";
		next;
		mes "[マリナ]";
		mes "ジュビリーさん、行きましょう。";
		next;
		mes "‐残りの一人、";
		mes "　ジョジョさんを探そう‐";
		misceffect 304,"マリナ#ilgf10";
		misceffect 304,"司祭#ilgf01";
		cloakonnpc "マリナ#ilgf10";
		cloakonnpc "マリナ#ilgf03";
		cloakonnpc "マリナ#ilgf04";
		cloakonnpc "マリナ#ilgf05";
		cloakonnpc "マリナ#ilgf06";
		cloakonnpc "マリナ#ilgf07";
		cloakonnpc "マリナ#ilgf08";
		cloakonnpc "マリナ#ilgf09";
		cloakonnpc "司祭#ilgf01";
		cloakoffnpc "魔法使い#ilgf25";
		cloakoffnpc "魔法使い#ilgf26";
		cloakoffnpc "アンデッド#ilgf01";
		cloakoffnpc "魔法使い#ilgf24";
		cloakoffnpc "光るキノコ#ilgf01";
		cloakoffnpc "魔法使い#ilgf23";
		cloakoffnpc "早いアンデッド#ilgf01";
		cloakoffnpc "魔法使い#ilgf21";
		cloakoffnpc "魔法使い#ilgf22";
		cloakoffnpc "アンデッド#ilgf02";
		cloakoffnpc "アンデッド#ilgf03";
		cloakoffnpc "アンデッド#ilgf04";
		cloakoffnpc "魔法使い#ilgf19";
		cloakoffnpc "魔法使い#ilgf20";
		cloakoffnpc "アンデッド#ilgf05";
		cloakoffnpc "魔法使い#ilgf18";
		cloakoffnpc "誰かの夢#ilgf18";
		cloakoffnpc "魔法使い#ilgf16";
		cloakoffnpc "魔法使い#ilgf17";
		cloakoffnpc "魔法使い#ilgf12";
		cloakoffnpc "魔法使い#ilgf13";
		cloakoffnpc "名も無き墓#ilgf02";
		cloakoffnpc "魔法使い#ilgf11";
		cloakoffnpc "魔法使い#ilgf09";
		cloakoffnpc "魔法使い#ilgf10";
		cloakoffnpc "魔法使い#ilgf08";
		cloakoffnpc "名も無き墓#ilgf03";
		cloakoffnpc "魔法使い#ilgf06";
		cloakoffnpc "魔法使い#ilgf07";
		cloakonnpc "アンデッド#ilgf06";
		cloakoffnpc "魔法使い#ilgf27";
		cloakoffnpc "魔法使い#ilgf28";
		chgquest 14657,14658;
		set IL_VAMP_QUE,7;
		close;
	}
	end;
OnTouch:
	if(IL_VAMP_QUE == 6)
		unittalk getnpcid(0,"司祭#ilgf01"),"司祭 : 本当に困ったな……。";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,253,165,3	script	マリナ#ilgf10	746,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,254,162,1	script	アンデッド#ilgf08	3752,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,252,160,1	script	アンデッド#ilgf09	3753,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,250,164,0	script	#ilgf06	139,15,15,{
	if(IL_VAMP_QUE == 6)
		cloakoffnpc "司祭#ilgf01";
	if(IL_VAMP_QUE == 7)
		cloakonnpc "司祭#ilgf01";
	end;
}

gef_d01_i.gat,81,135,5	script	魔法使い#ilgf01	10224,{
	switch(IL_VAMP_QUE) {
	case 7:
		mes "[魔法使い]";
		mes "これは……";
		mes "蛍きのことはちょっと色が違う。";
		mes "新しいキノコかな？";
		mes "気をつけて採らなきゃ……。";
		next;
		menu "ジョジョさん？",-;
		emotion 0,"魔法使い#ilgf01";
		mes "[魔法使い]";
		mes "……！";
		mes "人間……？";
		next;
		mes "[魔法使い]";
		mes "私は……";
		mes "ジョジョという名では";
		mes "ありません。";
		next;
		mes "[魔法使い]";
		mes "わ、私が^0000cd人^000000に";
		mes "見えるのですか？";
		next;
		mes "[魔法使い]";
		mes "……。";
		next;
		emotion 23,"";
		menu "……人間じゃないのですか？",-;
		mes "[魔法使い]";
		mes "あ、いえ……。";
		next;
		mes "[ボミ]";
		mes "私は……私の名前は";
		mes "^0000cdボミ^000000といいます。";
		mes "お探しの人でなくて";
		mes "申し訳ありません。";
		next;
		menu "あなたのノートを見ました。",-;
		mes "[ボミ]";
		mes "……そうですか。";
		next;
		mes "[ボミ]";
		mes "……あのノートは、";
		mes "私が捨てた物です。";
		next;
		menu "何故こんなところにいるのですか？",-;
		mes "[ボミ]";
		mes "それは……";
		mes "私が、私がここから離れられない";
		mes "化け物だから。";
		mes "私がヴァンパイアだからです。";
		next;
		menu "ヴァンパイア！",-;
		mes "[ボミ]";
		mes "私も以前は人間でした。";
		mes "でも……";
		mes "信じていた……";
		mes "友達が裏切ったんです。";
		next;
		mes "[ボミ]";
		mes "人が一生懸命に生きる理由は";
		mes "なんだと思いますか？";
		mes "それは、いずれ死ぬことが";
		mes "決められているからです。";
		next;
		mes "[ボミ]";
		mes "私には……";
		mes "その与えられた時間が";
		mes "凄く短かったんです。";
		mes "生まれた時から祝福の言葉より、";
		mes "不吉な死の言葉を多く聞くほど";
		mes "貧弱だったのです。";
		next;
		mes "[ボミ]";
		mes "人は、自分に無いものを";
		mes "求め憧れるものです。";
		mes "私は^0000cd強い力に憧れ^000000ました。";
		mes "だけど私は痩せ細っていて、";
		mes "いつ死んでも";
		mes "おかしくありませんでした。";
		next;
		mes "[ボミ]";
		mes "だから魔法使いになったんです。";
		mes "身体的に強くないなら、";
		mes "違う力で強くなればいいと";
		mes "思ったんです。";
		next;
		mes "[ボミ]";
		mes "でも、";
		mes "強い精神力を手に入れるには";
		mes "強い肉体が必要だということを";
		mes "知りませんでした。";
		next;
		mes "[ボミ]";
		mes "魔法は精神力も体力も";
		mes "激しく消耗するのです。";
		mes "すぐ壁にぶつかりました。";
		mes "それでも私は諦めませんでした。";
		mes "他の方法を探ればいいだけですから。";
		next;
		mes "[ボミ]";
		mes "当時、何よりも生きてる実感が";
		mes "ありました。";
		mes "胸の中で強烈に燃え盛る炎。";
		mes "それが私を人として";
		mes "生き長らえさせたのです。";
		next;
		mes "[ボミ]";
		mes "そんなある日、";
		mes "ここで人間ではない";
		mes "^0000cd異なる存在^000000に出逢ったんですよ。";
		next;
		mes "‐ボミはちょっと言葉を";
		mes "　選んでるようだった。";
		mes "　考えがまとめられるのを待って、";
		mes "　もう一度話しかけよう‐";
		chgquest 14658,14659;
		set IL_VAMP_QUE,8;
		close;
	case 8:
		mes "[ボミ]";
		mes "ここには何が住んでいるか";
		mes "知っていますか？";
		next;
		mes "[ボミ]";
		mes "ナイトメア、キノコ、ゾンビ……";
		mes "そしてもうひとつ……";
		mes "ドラキュラです。";
		next;
		mes "[ボミ]";
		mes "彼と初めて会った時、";
		mes "まさに消滅する寸前でした。";
		next;
		mes "[ボミ]";
		mes "その弱々しい姿に";
		mes "私は自分を重ねていたのかも";
		mes "しれません。";
		next;
		mes "[ボミ]";
		mes "……だから、";
		mes "近づいてはいけないと";
		mes "知りながらも、私は自分の血を";
		mes "彼に分け与えて治療したのです";
		next;
		mes "[ボミ]";
		mes "それから私たちは";
		mes "時々会うようになり、";
		mes "徐々に親しくなりました。";
		mes "私に友達が出来たのは";
		mes "これが初めてだったんです。";
		next;
		mes "[ボミ]";
		mes "……。";
		next;
		mes "[ボミ]";
		mes "……";
		mes "…………。";
		next;
		misceffect 496,"ドラキュラ#ilgf01";
		misceffect 1003,"ドラキュラ#ilgf01";
		cloakoffnpc "ドラキュラ#ilgf01";
		if(!sleep2(4000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : 何故俺を助けた？";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : それは……ちょっと説明しづらいわ。ただ、人とはそういうものなの。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : 君はこれまで出会った人間たちとは違うな。彼らは俺を消滅させようとした。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : それぞれ違うのが、人間というものなのよ。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : お礼にプレゼントを一つあげよう。君は強い肉体と長い寿命が欲しかったはずだな。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : ええ、でもどうやって……";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : まさか……？　嫌よ、絶対！";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : 欲しいのだろう。違うか？　だからこんな所にまで来て研究をしていたんじゃないのか？";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : 欲しいわよ！　誰よりも！";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : でも……人であることを捨ててまで、手に入れたいとは思わないわ！";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : 死が怖くないのか？　君に残された時間は残り僅かだぞ……。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : その恐怖があるからこそ、私は今こうやって生きている。その恐怖が今の私をここにいさせているの。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : 私が私であることを諦めて、力を得てしまったら、過去の私や私の行動、私の守りたかったもの全てを否定することになるの。";
		if(!sleep2(4000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : それは私が守り抜いてきた、私という人間を諦めることに等しいのよ！";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : 君が俺と同族になったとしても、君は君だろう。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : そういう問題じゃないの。";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : 私は死を恐れている。だからより一生懸命に生きようとする人間としての私を守り続けたいの。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : そうか……。君の命が消えていくのを見過ごすのは、とても惜しいものだ。";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : だが君が守りたいというものを尊重するとしよう。俺には理解できないがね。";
		if(!sleep2(3000)) end;
		mes "[ボミ]";
		mes "……。";
		next;
		mes "[ボミ]";
		mes "彼は私と^0000cd約束^000000しました。";
		mes "だけどある日、";
		mes "この場所を訪れた人たちと";
		mes "争いになり……。";
		next;
		mes "[ボミ]";
		mes "気がついたら、";
		mes "私はこんな化け物になってました。";
		mes "彼は約束を破ったんです。";
		next;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"魔法使い#ilgf01"),"ボミ : 私を化け物にしたのね？";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"ドラキュラ#ilgf01"),"ドラキュラ : ……すまない。";
		if(!sleep2(2000)) end;
		misceffect 496,"ドラキュラ#ilgf01";
		cloakonnpc "ドラキュラ#ilgf01";
		if(!sleep2(1000)) end;
		mes "[ボミ]";
		mes "本当に憎かった。";
		mes "……信じていた友達だったのに。";
		next;
		mes "[ボミ]";
		mes "外では私は突然失踪してしまった";
		mes "人間になっているでしょうね？";
		mes "どれぐらいの時間が";
		mes "経ったんでしょう？";
		next;
		mes "[ボミ]";
		mes "あるいは……";
		mes "私は最初からいなかったみたいに";
		mes "忘れ去られたんでしょうか。";
		mes "とても悲しいです。";
		next;
		mes "[ボミ]";
		mes "だけど、それでも";
		mes "自分自身が化け物だと感じる瞬間が";
		mes "急に訪れます。";
		mes "その飢えと渇きに耐えていると、";
		mes "私は本物の化け物になってしまう。";
		next;
		mes "[ボミ]";
		mes "でも、渇きを解決するために";
		mes "外へ出れば……";
		mes "きっと誰かを";
		mes "害してしまうでしょうね。";
		next;
		menu "どうやって今まで耐え切れたんですか？",-;
		mes "[ボミ]";
		mes "私は足りない体力を補うために";
		mes "ずっと研究してきた";
		mes "^0000cd薬品製造に関する知識^000000があります。";
		next;
		mes "[ボミ]";
		mes "この辺で手に入る物で、";
		mes "偽物の血液を作り出して";
		mes "その日その日を耐えています。";
		mes "^0000cd人間の真似^000000をしている偽物なんです。";
		mes "もう私に本物の人間は";
		mes "何一つ残ってません。";
		next;
		mes "[ボミ]";
		mes "……ごめんなさい。";
		mes "退屈な話でしたね？";
		next;
		mes "[ボミ]";
		mes "あの、冒険者様。";
		mes "申し訳ないのですが、";
		mes "一つ頼みごとをしても";
		mes "よろしいでしょうか？";
		next;
		menu "良いですよ",-;
		mes "[ボミ]";
		mes "そんな簡単に引き受けたら";
		mes "危険ですよ。";
		mes "もし血を要求したら";
		mes "どうするつもりですか？";
		emotion 4,"";
		next;
		mes "[ボミ]";
		mes "ふふ……冗談です。";
		mes "偽物の血を作る材料を";
		mes "探していたんですが、";
		mes "今はこのキノコを";
		mes "観察しなくてはいけません。";
		next;
		mes "[ボミ]";
		mes "初めて見る種類なので、";
		mes "出来るだけ新鮮な状態を";
		mes "観察をしたいんです。";
		mes "なのでここを離れられません。";
		next;
		menu "何が必要ですか？",-;
		mes "[ボミ]";
		mes "ありがとうございます。";
		mes "偽物の血を作るには";
		mes "べとべとする血と、";
		mes "きのこの粘液が必要なんです。";
		next;
		mes "[ボミ]";
		mes "^0000cdマットドレインリアーの";
		mes "べとべとする血が1個、";
		mes "蛍きのこの";
		mes "きのこの粘液が1個^000000欲しいです。";
		mes "よろしくお願いします。";
		chgquest 14659,14660;
		set IL_VAMP_QUE,9;
		close;
	case 9:
		mes "[ボミ]";
		mes "材料を集めて来てくれたんですか？";
		mes "どれどれ……。";
		next;
		if(countitem(25268) < 1 || countitem(25269) < 1) {
			mes "[ボミ]";
			mes "あ、まだ途中みたいですね。";
			next;
			mes "[ボミ]";
			mes "^0000cdマットドレインリアーの";
			mes "べとべとする血が1個、";
			mes "蛍きのこの";
			mes "きのこの粘液が1個^000000欲しいです。";
			mes "よろしくお願いします。";
			close;
		}
		mes "[ボミ]";
		mes "これだけあれば十分です。";
		mes "本当にありがとう。";
		next;
		mes "[ボミ]";
		mes "キノコはよく見てみたら、";
		mes "別に価値の無いものでした。";
		mes "ありふれた普通のキノコ……。";
		next;
		menu "血液はどうやって作りますか？",-;
		mes "[ボミ]";
		mes "マットドレインリアーは";
		mes "死人の血を吸って生きてます。";
		next;
		mes "[ボミ]";
		mes "ただその血は毒性が強いんです。";
		mes "そこでこのキノコで中和させます。";
		next;
		mes "[ボミ]";
		mes "こんな風に！";
		misceffect 305,"魔法使い#ilgf01";
		next;
		mes "[ボミ]";
		mes "ただこの粘液でも";
		mes "毒を完全には取り除けません。";
		mes "だから毒が体内に";
		mes "一定以上貯まると時々……。";
		next;
		menu "アルケミストの才能がありますね",-;
		mes "[ボミ]";
		mes "最初進路を決めた時は、";
		mes "こんな才能があるとは";
		mes "知りませんでした。";
		mes "もし時間さえあったら、";
		mes "いろんなことを試せたはずだし、";
		mes "違う道を選んだかも知れませんね。";
		next;
		mes "[ボミ]";
		mes "あ、そうだ。";
		mes "人を探しているんでしたよね？";
		mes "ジョジョさんでしたっけ？";
		next;
		mes "[ボミ]";
		mes "最近、この辺りで人間を";
		mes "見たことはないですが……";
		mes "もし見かけたら、";
		mes "探してる人がいたと伝えますね。";
		next;
		mes "[ボミ]";
		mes "早く見つかって欲しいです。";
		mes "ここにいるのは";
		mes "私だけではないですから。";
		mes "まだ見つからないとしたら、";
		mes "もしかしたら、あそこに……。";
		next;
		mes "[ボミ]";
		mes "いや、なんでもないです。";
		mes "きっと見つかると思います。";
		mes "どうしても見つからないなら、";
		mes "南側のお墓近くを";
		mes "探してみてください。";
		next;
		mes "[ボミ]";
		mes "急いだ方が良いと思います。";
		mes "それでは。";
		cloakoffnpc "ドラキュラ#ilgf02";
		cloakoffnpc "キング#ilgf01";
		cloakoffnpc "魔法使い#ilgf02";
		delitem 25268,1;
		delitem 25269,1;
		chgquest 14660,14661;
		set IL_VAMP_QUE,10;
		close;
	case 10:
	case 11:
		mes "[ボミ]";
		mes "早く見つかるといいですね。";
		mes "どうしても見つからないなら、";
		mes "南側のお墓近くを";
		mes "探してみてください。";
		close;
	case 12:
		mes "[ボミ]";
		mes "離れて！";
		mes "私はあなたたちに";
		mes "危害は加えたりはしないわ！";
		next;
		mes "[マリナ]";
		mes "既に私たちの仲間が一人消えた！";
		mes "あんたの仕業だろ？";
		next;
		mes "[ボミ]";
		mes "私は今まで誰も";
		mes "傷つけてこなかったし、";
		mes "これからも傷つけるつもりはないわ。";
		next;
		mes "[マリナ]";
		mes "私たちに危害を加えないとしても、";
		mes "あなたの存在は消えて当然よ！";
		mes "あなたの存在そのものが、";
		mes "神の意志に逆らっているもの！";
		next;
		mes "[ボミ]";
		mes "神の意志？";
		mes "神は全てを愛する。";
		mes "あなたたちはそう言ってなかった？";
		next;
		mes "[マリナ]";
		mes "死者は土の中で";
		mes "安らぎをえるんだ！";
		mes "あなたは自分の存在を";
		mes "何だと思っているの？";
		next;
		mes "[ボミ]";
		mes "……でも、でも！";
		mes "私は本当に何もしていない！";
		next;
		mes "[マリナ]";
		mes "だが、";
		mes "これからも絶対しないという";
		mes "保証は無い！";
		next;
		mes "[ジェム]";
		mes "マリナさん、落ち着いて。";
		next;
		mes "[マリナ]";
		mes "躊躇うことなどありません！";
		mes "死者は土へ！";
		mes "アントワーヌさん！";
		next;
		mes "[アントワーヌ]";
		mes "仕方ありませんね。";
		mes "マリナさんの言うことも";
		mes "一理ありますし。";
		next;
		mes "[マリナ]";
		mes "喰らえっ！";
		unittalk getnpcid(0,"マリナ#ilgf02"),"阿修羅覇凰拳！";
		if(!sleep2(1000)) end;
		misceffect 583,"ドラキュラ#ilgf03";
		cloakoffnpc "ドラキュラ#ilgf03";
		misceffect 318,"ドラキュラ#ilgf03";
		misceffect 328,"ドラキュラ#ilgf03";
		if(!sleep2(1000)) end;
		misceffect 668,"ドラキュラ#ilgf03";
		misceffect 669,"ドラキュラ#ilgf03";
		misceffect 791,"ドラキュラ#ilgf03";
		misceffect 266,"ドラキュラ#ilgf03";
		unittalk getnpcid(0,"ドラキュラ#ilgf03"),"ドラキュラ : くっ……!!";
		next;
		misceffect 583,"キング#ilgf02";
		cloakoffnpc "キング#ilgf02";
		emotion 7,"キング#ilgf02";
		mes "[キング]";
		mes "このバカ！";
		mes "おとなしくしていれば良いものを！";
		mes "どうしてこんなことを！";
		next;
		mes "[ボミ]";
		mes "ドラキュラ……？";
		mes "あなたが……何故？";
		next;
		mes "[マリナ]";
		mes "ヴァンパイアがまた現れた!?";
		mes "おかしな場所とは思ったけど、";
		mes "ヴァンパイアの巣窟だったとは！";
		next;
		mes "[マリナ]";
		mes "そこのコウモリ！";
		mes "あんたもヴァンパイアだな!?";
		next;
		emotion 6,"キング#ilgf02";
		mes "[キング]";
		mes "コウモリだと！";
		mes "人間の癖に無礼な！";
		next;
		mes "[ジェム]";
		mes "待ちなさいマリナさん。";
		mes "少し落ち着きなさい。";
		next;
		mes "[マリナ]";
		mes "今が好機なんですよ！";
		mes "三体のうち、";
		mes "一体は動きが止まっています。";
		next;
		mes "[ジェム]";
		mes "そして一体は、";
		mes "全く攻撃の意志が無い。";
		mes "対話を求めています。";
		next;
		mes "[キング]";
		mes "対話を求めるって？";
		mes "僕は違う！";
		mes "何もせずにやられる気はない！";
		misceffect 266,"キング#ilgf02";
		misceffect 183,"マリナ#ilgf02";
		misceffect 212,"マリナ#ilgf02";
		next;
		mes "[マリナ]";
		mes "くっ……！";
		mes "ほら見て！";
		mes "もう我慢できない！";
		next;
		misceffect 304,"ジョジョ#ilgf01";
		cloakoffnpc "ジョジョ#ilgf01";
		emotion 53,"ジョジョ#ilgf01";
		mes "[ジョジョ]";
		mes "ふう、疲れた。";
		mes "みんな歩くの早過ぎるよ。";
		next;
		mes "[ジョジョ]";
		mes "みなさん落ち着いて！";
		mes "ちょっと落ち着いてください！";
		next;
		mes "[ジェム]";
		mes "ジョジョさん？";
		mes "ご無事でしたか！";
		next;
		mes "[マリナ]";
		mes "全然見つからなかったのに、";
		mes "どこに行ってたんですか？";
		next;
		mes "[アントワーヌ]";
		mes "爆発に巻き込まれたと";
		mes "聞きましたが、";
		mes "傷はほぼ治っているようですね。";
		next;
		mes "[ドラキュラ]";
		mes "ボミに手を出すな……。";
		mes "ボミと俺は……";
		mes "誰も……傷つけない……。";
		mes "それが俺が学んだ……もの。";
		next;
		mes "[ボミ]";
		mes "ドラキュラ！";
		mes "ドラキュラ!!";
		mes "早く治療を……！";
		next;
		mes "[マリナ]";
		mes "そうはさせるか！";
		next;
		mes "[ジェム]";
		mes "待ちなさい、マリナさん。";
		mes "一旦様子をみましょう。";
		mes "彼らはジョジョさんを";
		mes "治療してくれました。";
		next;
		mes "[マリナ]";
		mes "それが罠だとしたら？";
		next;
		mes "[ジェム]";
		mes "万が一攻撃してきたとしても、";
		mes "数ではこちらが優勢です。";
		next;
		mes "[アントワーヌ]";
		mes "僕もシスタージェムの考えに";
		mes "同意します。";
		mes "こんな近くで見られる機会も";
		mes "滅多にないことですし。";
		next;
		mes "[ジェム]";
		mes "ボミさん……でしたよね？";
		mes "ノートを読みました。";
		mes "いったい何があったんですか？";
		mes "あのヴァンパイアたちは";
		mes "何なのですか？";
		next;
		menu "それは、私が説明いたします。",-;
		mes "‐シスター・ジェムの一行に";
		mes "　過去のボミとドラキュラに";
		mes "　起きたことを簡単に説明した‐";
		next;
		mes "[ジェム]";
		mes "なるほど……";
		mes "そんなことが……。";
		next;
		mes "[ボミ]";
		mes "さあドラキュラ、";
		mes "これを飲んで。";
		next;
		mes "[マリナ]";
		mes "それは誰の血だ？";
		mes "飲ませる訳にはいかない！";
		next;
		mes "[ボミ]";
		mes "誰の血でもないわよ！";
		mes "これを飲ませなきゃ！";
		mes "目の前で人が死にかけてるのよ！";
		next;
		mes "[マリナ]";
		mes "あんたらは人ではない！";
		next;
		mes "[キング]";
		mes "やれやれ、バカなやつらだ。";
		mes "こいつは僕が見てるから、";
		mes "早く治療しろ。";
		next;
		mes "[ジョジョ]";
		mes "私も手伝います。";
		next;
		mes "[ジェム]";
		mes "治療してあげてください。";
		next;
		emotion 0,"マリナ#ilgf02";
		mes "[マリナ]";
		mes "ヴァンパイアを!?";
		mes "シスタージェムは私たちの";
		mes "リーダーじゃないですか！";
		mes "義務を疎かにするつもりですか？";
		next;
		mes "[ジョジョ]";
		mes "マリナさん、彼らが誰だろうが、";
		mes "私は助けてもらったんです。";
		mes "何の見返りもなく。";
		next;
		mes "[ジョジョ]";
		mes "ヴァンパイアが人間を助けるのが";
		mes "不思議だったんですが、";
		mes "今ならわかります。";
		mes "ドラキュラさんは彼女から";
		mes "学んだんですね、人間というものを。";
		next;
		mes "[ジョジョ]";
		mes "ドラキュラさんは";
		mes "人間を理解したいと言ってました。";
		mes "ボミさんを通じてね。";
		mes "私が見た限りでは、";
		mes "人間を完璧に理解しています。";
		next;
		mes "[ジョジョ]";
		mes "困難に陥った他人を、";
		mes "打算も無しに助けようとする";
		mes "理解できない行動。";
		mes "それこそ一番人間らしい";
		mes "心ではないでしょうか？";
		next;
		mes "[ジョジョ]";
		mes "他人を理解し助けるのは、";
		mes "それが誰だろうと関係ありません。";
		mes "マリナさんは目の前で人が死ぬのを";
		mes "放っておけますか？";
		next;
		mes "[マリナ]";
		mes "それは相手が人間の場合のみ";
		mes "言えることですよ！";
		mes "彼らはヴァンパイアなんです！";
		next;
		mes "[キング]";
		mes "ドラキュラがどうしてこんな風に";
		mes "なったのかやっとわかった。";
		mes "魔法使い、";
		mes "君の言葉を聞いたからだな。";
		mes "全部ドラキュラの戯言だと";
		mes "思っていたよ。";
		next;
		mes "[キング]";
		mes "なあ、そこのモンク。";
		mes "人間らしさとはなんだ？";
		mes "ヴァンパイアらしさとはなんだ？";
		mes "もし一生、一度も人に危害を加えない";
		mes "ヴァンパイアがいたら、どうする？";
		next;
		mes "[マリナ]";
		mes "もちろん、処分する。";
		next;
		mes "[キング]";
		mes "じゃあ、";
		mes "もし一生、他人を害し続けてきた";
		mes "人間がいたら、どうする？";
		next;
		mes "[マリナ]";
		mes "それは……法に託す。";
		next;
		mes "[キング]";
		mes "僕は狩りをする時、";
		mes "その人間がどんな人間だろうが";
		mes "構わず公平に狩ってきた。";
		mes "何故なら僕はヴァンパイアだから。";
		mes "それが僕たちの掟だ。";
		next;
		mes "[キング]";
		mes "彼らも同じだ。";
		mes "困った人がいたら、";
		mes "それが誰だろうがまずは助ける。";
		mes "それは本当に単純な論理じゃないか？";
		next;
		mes "[マリナ]";
		mes "……。";
		next;
		mes "[ドラキュラ]";
		mes "ううっ……ボミ？";
		next;
		mes "[ボミ]";
		mes "ドラキュラ！";
		next;
		mes "[ドラキュラ]";
		mes "君は俺を助けたのか？";
		mes "あの時のように？";
		mes "君は俺の消滅を";
		mes "望んでると思っていたのに。";
		next;
		mes "[ボミ]";
		mes "ううん……。";
		mes "あなたが私をヴァンパイアにした";
		mes "理由がわかったのよ。";
		mes "あなたは目の前で私が死ぬのが";
		mes "耐えられなかったんだよね？";
		next;
		mes "[ボミ]";
		mes "私も……";
		mes "私も一緒よ……！";
		next;
		mes "[ドラキュラ]";
		mes "ボミ……。";
		next;
		mes "[ボミ]";
		mes "ドラキュラ……。";
		next;
		mes "[キング]";
		mes "おいおい、";
		mes "あいつら何してやがる？";
		next;
		mes "[ジョジョ]";
		mes "そっとしておきましょう。";
		mes "交わす言葉も多いことでしょう。";
		next;
		mes "[ジェム]";
		mes "みなさん、こちらへ。";
		mes "少し話し合う必要が";
		mes "ありそうですね。";
		chgquest 14663,14664;
		set IL_VAMP_QUE,13;
		close;
	case 13:
		mes "[ボミ]";
		mes "ドラキュラ、";
		mes "ありがとう。";
		mes "そしてごめんなさい。";
		next;
		mes "[ドラキュラ]";
		mes "俺こそ君との約束を";
		mes "破ってすまない。";
		mes "どんな言葉でも言い尽くせないが、";
		mes "本当にすまない。";
		next;
		mes "[ボミ]";
		mes "今ならわかるわ。";
		mes "あなたが何故あんな選択を";
		mes "するしかなかったのか。";
		next;
		mes "[ジョジョ]";
		mes "え～と、ちょっと良いですか？";
		mes "二人とも、誤解は解けましたか？";
		mes "ドラキュラ様も峠は越えたから、";
		mes "安静にしていれば大丈夫です。";
		next;
		mes "[ドラキュラ]";
		mes "すまない、手間をかけたな。";
		next;
		mes "[キング]";
		mes "ふん。";
		mes "キノコ如きにやられる";
		mes "情けない奴だと思ったが、";
		mes "結構良い腕をしてるじゃないか。";
		next;
		emotion 27,"キング#ilgf02";
		mes "[キング]";
		mes "ドラキュラ、早く帰ろう。";
		mes "ここを離れて城へ戻るべきだ。";
		next;
		mes "[ドラキュラ]";
		mes "……いや、";
		mes "俺はここに残る。";
		next;
		mes "[キング]";
		mes "はあ？　何で！";
		mes "もう誤解も解けたことだし、";
		mes "全部終わっただろう？";
		next;
		mes "[ジェム]";
		mes "ちょっといいですか？";
		mes "私たちの話を";
		mes "聞いてくれませんか。";
		next;
		mes "[ジェム]";
		mes "あなたたちが誰にも危害を加えない";
		mes "ということはわかりました。";
		mes "今まで問題を起こしていないことも、";
		mes "ジョジョさんを助けてくれたことも、";
		mes "すべて理解しました。";
		next;
		mes "[ジェム]";
		mes "しかし、あなたたちの存在は、";
		mes "我らの教えに反するものです。";
		mes "私たちはこのままあなたたちを";
		mes "放ってはおけません。";
		next;
		emotion 7,"キング#ilgf02";
		mes "[キング]";
		mes "ドラキュラ！";
		mes "こいつら僕たちを邪魔する気だ。";
		mes "消してしまおう！";
		next;
		mes "[ドラキュラ]";
		mes "それはダメだ。";
		mes "　";
		mes "[ボミ]";
		mes "ダメよ！";
		next;
		mes "[マリナ]";
		mes "シスタージェム、あんな戯言を";
		mes "信じる訳にはいきません。";
		mes "奴らはいつか我々を";
		mes "攻撃するに違いありません！";
		mes "その前に処分すべきです！";
		next;
		mes "[アントワーヌ]";
		mes "マリナさんは";
		mes "少し黙っていてください。";
		mes "いつも結論を決めつけて話すから";
		mes "誤解を招くじゃありませんか？";
		mes "僕が話をつけましょう。";
		next;
		mes "[アントワーヌ]";
		mes "あなたたちが、";
		mes "誰も害しないことは";
		mes "よくわかりました。";
		mes "しかし、危険な人が";
		mes "いるのも事実ですし……。";
		next;
		emotion 6,"キング#ilgf02";
		mes "[キング]";
		mes "何で僕を見る！";
		mes "何で！　何で僕！";
		next;
		mes "[アントワーヌ]";
		mes "知ってしまった以上、";
		mes "知らない振りは出来ません。";
		mes "仮に我々が見逃しても、";
		mes "教会が見逃してくれるとは";
		mes "限りません。";
		next;
		mes "[アントワーヌ]";
		mes "そこで、今すぐどうこうせず、";
		mes "私たちがここに残って";
		mes "あなたたちを^0000cd見守ろうと^000000";
		mes "決めました。";
		next;
		emotion 7,"キング#ilgf02";
		mes "[キング]";
		mes "今僕たちを監視すると言ったな？";
		mes "ドラキュラ、僕はもう我慢できない！";
		next;
		misceffect 389,"キング#ilgf02";
		misceffect 583,"キング#ilgf02";
		if(!sleep2(1000)) end;
		setnpcdisplay "キング#ilgf02",10137;
		mes "[キング]";
		mes "みんな消してやる！";
		next;
		mes "[ドラキュラ]";
		mes "わかった。";
		mes "　";
		mes "[ボミ]";
		mes "わかりました。";
		next;
		emotion 6,"キング#ilgf02";
		mes "[キング]";
		mes "ちょ、お前ら!?";
		mes "ドラキュラ！";
		mes "人間と仲良くなりすぎて、";
		mes "人間になっちゃったんじゃないのか？";
		mes "僕たちのプライドと品位はどこへやった！";
		next;
		mes "[ドラキュラ]";
		mes "ではそれで良いか？";
		mes "俺はもう少し休まなくては。";
		mes "睡眠を取りたい。";
		next;
		mes "[ジョジョ]";
		mes "私も一緒に行きましょう。";
		mes "傷が完全に癒えるまでは";
		mes "側にいます。";
		next;
		emotion 7,"キング#ilgf02";
		misceffect 389,"キング#ilgf02";
		misceffect 583,"キング#ilgf02";
		if(!sleep2(1000)) end;
		setnpcdisplay "キング#ilgf02",799;
		mes "[キング]";
		mes "くそ、気に入らないな。";
		mes "ドラキュラ、君が回復したら、";
		mes "僕は城に帰るよ。";
		mes "わかった？　わかったか！";
		next;
		mes "[ジェム]";
		mes "同意されたということで";
		mes "よろしいですね。";
		mes "では私たちも一旦戻りましょう。";
		next;
		misceffect 304,"ジェム#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "ジェム#ilgf02";
		mes "[マリナ]";
		mes "あんたら、";
		mes "私がいつも見てるのを忘れるなよ！";
		mes "寝るときには気をつけな！";
		next;
		misceffect 304,"マリナ#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "マリナ#ilgf02";
		mes "[アントワーヌ]";
		mes "では、僕もここらで失礼します。";
		next;
		misceffect 304,"アントワーヌ#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "アントワーヌ#ilgf02";
		mes "[キング]";
		mes "あああああ！";
		mes "頭来る！";
		mes "二度と顔を見せるな！";
		mes "僕たちももう行こう！";
		next;
		misceffect 583,"キング#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "キング#ilgf02";
		mes "[ジョジョ]";
		mes "我々も行きましょう。";
		mes "早く治療を再開しないと。";
		next;
		mes "[ドラキュラ]";
		mes "ボミ、傷が癒えたら";
		mes "また話をしよう。";
		next;
		mes "[ジョジョ]";
		mes "さあ、急ぎましょう。";
		next;
		misceffect 304,"ジョジョ#ilgf01";
		misceffect 583,"ドラキュラ#ilgf03";
		if(!sleep2(1000)) end;
		cloakonnpc "ジョジョ#ilgf01";
		cloakonnpc "ドラキュラ#ilgf03";
		menu "みんな行ってしまいましたね。",-;
		mes "[ボミ]";
		mes "ありがとう。";
		mes "あなたのおかげで";
		mes "誰も傷つけずに";
		mes "事態を収めることができました。";
		next;
		menu "この前、私に人間に見えるかと聞きましたよね？",-;
		mes "[ボミ]";
		mes "……ええ。";
		next;
		menu "ボミさんは、誰が何と言おうと人間だと思います。",-;
		mes "[ボミ]";
		mes "……ありがとう。";
		mes "誰かがその言葉を言ってくれることを";
		mes "私は心から待ち望んで";
		mes "いたんだと思います。";
		next;
		mes "[ボミ]";
		mes "これまで私は化け物になったと";
		mes "苦しんでいたけど……";
		mes "以前の私を失っていないと";
		mes "確信しました。";
		mes "姿が変わっても、種族が変わっても、";
		mes "私は私だと気がつきました。";
		next;
		menu "それでは報告があるので行きますね。",-;
		mes "[ボミ]";
		mes "はい。お気をつけて。";
		mes "本当にありがとうございました。";
		chgquest 14664,14665;
		set IL_VAMP_QUE,14;
		close;
	case 14:
	case 15:
		mes "[ボミ]";
		mes "報告は済んだのですか？";
		close;
	}
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,82,132,3	script	キノコ#ilgf01	1084,{}

gef_d01_i.gat,86,133,1	script	ドラキュラ#ilgf01	10137,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,189,98,3	script	ドラキュラ#ilgf02	10137,{
	switch(IL_VAMP_QUE) {
	case 10:
		mes "[コウモリ]";
		mes "これを食ってみろよ。";
		mes "美味いぜ。";
		next;
		emotion 4,"魔法使い#ilgf02";
		mes "[魔法使い]";
		mes "いや……あの……";
		mes "それはちょっと……";
		next;
		mes "[見知らぬ男]";
		mes "キング、";
		mes "食べないと言っているだろう。";
		mes "すまない。俺が代わりに謝る。";
		next;
		mes "[魔法使い]";
		mes "だ、大丈夫です。";
		next;
		mes "[キング]";
		mes "そう言わずに一緒に食べようぜ。";
		mes "臭いはちょっと酷いけど。";
		mes "いつか死ぬ定めの人間じゃないか。";
		mes "それがちょっと早くなるだけなのに。";
		next;
		mes "[魔法使い]";
		mes "……あの失礼でなければ、";
		mes "私があのコウモリを";
		mes "倒してもいいですか？";
		next;
		mes "[見知らぬ男]";
		mes "駄目だ。";
		mes "俺の前では、誰も他人を";
		mes "傷付けてはいけない。";
		next;
		emotion 6,"キング#ilgf01";
		mes "[キング]";
		mes "人間のくせに生意気だな。";
		mes "お前の眼には";
		mes "僕がコウモリに見えるか？";
		next;
		mes "[魔法使い]";
		mes "コウモリじゃなきゃ何です？";
		next;
		misceffect 389,"キング#ilgf01";
		misceffect 583,"キング#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "キング#ilgf01",10137;
		if(!sleep2(1000)) end;
		mes "[キング]";
		mes "これで僕が何に見える？";
		next;
		emotion 23,"魔法使い#ilgf02";
		mes "[魔法使い]";
		mes "ひい！　な、何者ですか！";
		next;
		mes "[キング]";
		mes "何で？";
		mes "この姿は恐ろしい？";
		mes "ならこれは？";
		next;
		misceffect 389,"キング#ilgf01";
		misceffect 583,"キング#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "キング#ilgf01",735;
		if(!sleep2(1000)) end;
		emotion 28,"魔法使い#ilgf02";
		mes "[魔法使い]";
		mes "わ、わわわわ……私!?";
		mes "ド、ド、ドッペルゲンガー！";
		mes "も、もう駄目だ！";
		mes "私はもう死ぬ……！";
		next;
		mes "[キング]";
		mes "自分と同じ姿が怖い？　何で？";
		mes "人間は自分が好き過ぎて";
		mes "違う存在を排除するくせに、";
		mes "自分と同じ姿は受け入れない？";
		next;
		mes "[魔法使い]";
		mes "この人間の姿であることと、";
		mes "自分が自分自身の前に";
		mes "現れるのは全然違いますよ！";
		next;
		mes "[見知らぬ男]";
		mes "キング、それ以上からかうな。";
		next;
		emotion 54,"キング#ilgf01";
		mes "[キング]";
		mes "あんたは人間に甘過ぎるんだよ。";
		next;
		misceffect 389,"キング#ilgf01";
		misceffect 583,"キング#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "キング#ilgf01",799;
		mes "[魔法使い]";
		mes "あの……もう動けますし、";
		mes "悪いところも無さそうなので、";
		mes "もう行ってもいいですよね？";
		next;
		mes "[見知らぬ男]";
		mes "ああ。";
		mes "　";
		mes "[キング]";
		mes "ダメだ！";
		next;
		mes "[見知らぬ男]";
		mes "どうしてだ？　キング。";
		next;
		mes "[キング]";
		mes "いやいやいや、絶対ダメだろ！";
		mes "こいつは人間だろ。";
		mes "必ず仲間がいるはずだ。";
		mes "仲間を集めて僕たちを";
		mes "攻撃するに違いない！";
		mes "この前のことを忘れたのか？";
		next;
		mes "[魔法使い]";
		mes "そんなことしませんよ！";
		mes "私は受けた恩を忘れない人間です！";
		mes "私を助けてくれたみなさんを";
		mes "害しないと誓います！";
		mes "私を信じてください！";
		next;
		mes "[キング]";
		mes "人間は信じるに値しない。";
		mes "いつもそうだった。";
		next;
		mes "[見知らぬ男]";
		mes "キング、お前が言う";
		mes "危険性については理解するが、";
		mes "人間が信じるに値しない";
		mes "というのには同意しかねるな。";
		next;
		mes "‐普通の魔法使いの服装……";
		mes "　あれがジョジョさんだろうか‐";
		next;
		menu "ジョジョさんですか？",-;
		mes "[ジョジョ]";
		mes "ど、どなたでしょうか？";
		next;
		mes "[キング]";
		mes "ほら！　こいつの仲間が現れた！";
		mes "僕が言った通りだ！";
		mes "人間など信用できない！";
		next;
		mes "[ジョジョ]";
		mes "違います！";
		mes "あの人は私の仲間じゃありません！";
		mes "初めて見る人ですよ！　神に誓って！";
		next;
		mes "[キング]";
		mes "お前の仲間じゃなくとも、";
		mes "仲間が送った人間なんだろ。";
		mes "おいそこの人間！　答えろ！";
		next;
		menu "ジョジョさんを仲間が探しています。",-;
		mes "[見知らぬ男]";
		mes "そうか。";
		mes "モンスターに襲われ倒れていたので";
		mes "連れてきて治療していた。";
		mes "もう動けるはずだから、";
		mes "連れて帰っていいぞ。";
		next;
		menu "ジョジョさんを治療してくださったんですね。",-;
		mes "‐あなたは男に感謝の意を伝え、";
		mes "　男の名を聞いた‐";
		next;
		mes "[キング]";
		mes "ここまで来ておいて";
		mes "ドラキュラを知らない？";
		mes "ドラキュラを倒すために";
		mes "来たんじゃないのか？";
		next;
		menu "ドラキュラ？",-;
		mes "[ドラキュラ]";
		mes "そういえば、冒険者からは";
		mes "覚えのある匂いがする。";
		mes "とても懐かしい匂い。";
		next;
		mes "[ドラキュラ]";
		mes "古き友の匂いだ。";
		mes "小さく弱き友の……。";
		next;
		menu "ここに来る前、ボミさんに会いました。",-;
		mes "[ドラキュラ]";
		mes "そうか……ボミは元気か。";
		mes "俺のことを……話したか？";
		next;
		mes "[キング]";
		mes "は！";
		mes "まさか今までここにいたのは";
		mes "恩知らずで厚かましい";
		mes "あの人間のためだったのか。";
		next;
		mes "[ジョジョ]";
		mes "恩義って何のことですか？";
		next;
		mes "[キング]";
		mes "……。";
		next;
		mes "[キング]";
		mes "……永遠の命だ。";
		next;
		mes "[ジョジョ]";
		mes "え、永遠の命……!?";
		next;
		mes "[キング]";
		mes "ほら！";
		mes "これが普通の人間の反応なんだ！";
		mes "それなのにあの人間は";
		mes "恩知らずだから……！";
		next;
		menu "ドラキュラさんが裏切ったと言ってました。",-;
		emotion 6,"キング#ilgf01";
		mes "[キング]";
		mes "裏切りだと！";
		mes "あいつ、今どこにいる？";
		mes "せっかく生き返らせてやったのに、";
		mes "裏切りと言ったのか！";
		next;
		mes "[ドラキュラ]";
		mes "まだ俺を恨んでいるだろう。";
		mes "だがその時の俺には";
		mes "選択の余地など無かった……。";
		next;
		menu "何か理由がありそうですね。",-;
		mes "[ドラキュラ]";
		mes "俺が生きるためには人間が必要だ。";
		mes "人間たちの中に隠れ、";
		mes "必要な時に人間を狩るのは";
		mes "容易いことだった。";
		next;
		mes "[ドラキュラ]";
		mes "そうやって生きていた俺の前に、";
		mes "どこから嗅ぎつけたのか、";
		mes "教会の連中が現れた。";
		mes "正義を実行すると言いながら、";
		mes "俺に襲いかかってきた。";
		next;
		mes "[ドラキュラ]";
		mes "不意を突かれて";
		mes "大怪我をした俺は、";
		mes "死と生の匂いが漂う";
		mes "ここにやって来たのだ。";
		next;
		mes "[ドラキュラ]";
		mes "死人たちが彷徨うここで、";
		mes "俺に幸運な出来事などあるはずない。";
		mes "だがあったのだ。そんな出来事が。";
		next;
		mes "[ドラキュラ]";
		mes "ボミが俺を生き返らせたのだ。";
		mes "命の無い俺が生き返るという表現は";
		mes "不適切かもしれないが、";
		mes "ボミは俺に自分の血を";
		mes "分け与えたのだ。";
		next;
		mes "[ドラキュラ]";
		mes "おかげで俺は消滅することなく、";
		mes "生き長らえることができたのだ。";
		next;
		mes "[ジョジョ]";
		mes "それからどうしたんですか？";
		next;
		mes "[ドラキュラ]";
		mes "ボミは強がってはいたが、";
		mes "残された時間は僅かしかなかった。";
		mes "永遠の命を与えるとの俺の提案を";
		mes "拒否したあの子に会う度に、";
		mes "その命が消えていくのが";
		mes "俺には耐えられなかった。";
		next;
		mes "[ドラキュラ]";
		mes "ここから離れることも出来たが、";
		mes "人間として最後を迎えたいという";
		mes "ボミの意志を尊重し、";
		mes "最後を見届けたいと思った。";
		next;
		mes "[ドラキュラ]";
		mes "俺は初めて人間について考えた。";
		mes "人間というものを。";
		mes "その暖かい心と、";
		mes "自らの利益に関わらず、";
		mes "他人を助けようとする、";
		mes "その理解しがたい行動を。";
		next;
		mes "[ドラキュラ]";
		mes "ボミと過ごしてそれを";
		mes "理解しようと思った。";
		mes "だがそれは相変わらず不条理で、";
		mes "知ることと理解することの間に";
		mes "深い溝があるのを痛感した。";
		next;
		mes "[ドラキュラ]";
		mes "それは以前人間に対して";
		mes "持っていた考えとは、";
		mes "まるで違う感じだった。";
		mes "俺は理解しようと努力している";
		mes "最中だった。";
		next;
		mes "[ジョジョ]";
		mes "なのに何故、";
		mes "ボミさんの意志に背いたんですか？";
		next;
		mes "[ドラキュラ]";
		mes "事故があったのだ。";
		mes "俺を消滅寸前まで追い込んだ連中が、";
		mes "俺を追ってここまで来たのだ。";
		next;
		mes "[ドラキュラ]";
		mes "不運は常に俺をつきまとう。";
		mes "ボミが幸運のためにと";
		mes "俺にくれたお守りも、";
		mes "その不運を払うことは";
		mes "できなかった。";
		next;
		mes "[ドラキュラ]";
		mes "既に傷は癒えていた俺にとって";
		mes "連中は敵ではなかった。";
		mes "しかしボミはみんなを護ろうとした。";
		mes "俺と人間、両方の誰一人も、";
		mes "犠牲にならないようにと。";
		next;
		mes "[ドラキュラ]";
		mes "だが……その戦いの最中、";
		mes "ボミは致命傷を負ってしまった。";
		next;
		mes "[ドラキュラ]";
		mes "突然訪れたボミの死に、";
		mes "まだ覚悟できていなかった俺は";
		mes "戸惑い、悲しんだ。";
		next;
		mes "[ドラキュラ]";
		mes "そんな形でボミを失うと";
		mes "思っていなかった俺は、";
		mes "知らず知らずのうちに";
		mes "ボミを生き返らせていた。";
		mes "ボミが望まなかった";
		mes "永遠の命を与えてな……。";
		next;
		mes "[ドラキュラ]";
		mes "……。";
		next;
		mes "[ジョジョ]";
		mes "ドラキュラ様も戸惑いと悲しみで";
		mes "深く考える余裕もなく、";
		mes "生き返らせてしまったんですね。";
		next;
		mes "[ジョジョ]";
		mes "確かに私も目の前で";
		mes "大切な人が死んでしまったら、";
		mes "生き返らせることを考えるでしょう。";
		next;
		mes "[キング]";
		mes "なのに、その恩知らずの人間は、";
		mes "それを約束を破ったと";
		mes "思ってるんだよ！";
		next;
		mes "[キング]";
		mes "僕には理解できない。";
		mes "何故死が自分を生かせると思える？";
		mes "どうして永遠の命を与えたことが、";
		mes "裏切りになる？";
		next;
		mes "[ジョジョ]";
		mes "人間の私には分かります。";
		mes "残された時間が短い分、";
		mes "より一生懸命生きようと";
		mes "していたのでしょう。";
		mes "私にもし無限の時間があったなら";
		mes "今より怠惰に過ごしてます。";
		next;
		mes "[ジョジョ]";
		mes "しかし……";
		mes "二人でちゃんと話し合えば";
		mes "お互いの誤解が解けると";
		mes "思うのですが……話はしましたか？";
		next;
		mes "[ドラキュラ]";
		mes "目覚めたボミは怒り、悲しんだ。";
		mes "俺が何を言おうと";
		mes "ボミは聞き入れなかった。";
		next;
		mes "[ドラキュラ]";
		mes "ボミのためにやったことだが、";
		mes "ボミは望んでいなかったことだ。";
		mes "俺への怒りと悲しみは";
		mes "当たり前のことだ。";
		next;
		mes "[キング]";
		mes "ドラキュラ、そんな人間がどうした！";
		mes "いつまでこんなところに";
		mes "引き籠っているつもりなんだ？";
		mes "そんなことをしたって、";
		mes "誰もお前を認めてくれないぞ。";
		next;
		mes "[ドラキュラ]";
		mes "それは、俺が……";
		next;
		emotion 0,"キング#ilgf01";
		mes "[キング]";
		mes "……！";
		next;
		mes "[キング]";
		mes "ちょっと……待て。";
		mes "何か匂う。匂うぞ。";
		chgquest 14661,14662;
		set IL_VAMP_QUE,11;
		close;
	case 11:
		mes "[ドラキュラ]";
		mes "キング？　何ごとだ？";
		close;
	case 12:
	case 13:
		mes "[ドラキュラ]";
		mes "争い、まさか……！";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	case 14:
	case 15:
		mes "[ドラキュラ]";
		mes "少し休みながら";
		mes "ボミを待つとしよう。";
		close;
	}
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,185,97,5	script	キング#ilgf01	799,{
	if(IL_VAMP_QUE <= 10) {
		mes "[キング]";
		mes "何か用がある？";
		mes "なければ失せろ！";
		close;
	}
	else if(IL_VAMP_QUE == 11) {
		mes "[キング]";
		mes "^0000cd血の匂い^000000がする！";
		mes "人間の血の匂いだ！";
		next;
		mes "[ジョジョ]";
		mes "わ、私じゃありませんよ！";
		mes "怪我は全部治ったんですよ！";
		next;
		mes "[キング]";
		mes "いや、これは墓場のどこかから";
		mes "漂ってきている匂いだ。";
		mes "これは……^0000cd争い^000000！　争いだ！";
		mes "行ってみよう！";
		next;
		menu "まさか教会の人たちが……。",-;
		mes "[ドラキュラ]";
		mes "教会？";
		next;
		emotion 27,"キング#ilgf01";
		mes "[キング]";
		mes "くんくん！";
		mes "こっちだ！";
		mes "北の方から匂うぞ！";
		chgquest 14662,14663;
		set IL_VAMP_QUE,12;
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	else if(IL_VAMP_QUE == 12 || IL_VAMP_QUE == 13) {
		mes "[キング]";
		mes "くんくん！";
		mes "こっちだ！";
		mes "こっちから匂うぞ！";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	mes "[キング]";
	mes "なんだ？";
	mes "ドラキュラには休息が必要なんだ。";
	mes "邪魔するなよ。";
	close;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,191,96,3	script	魔法使い#ilgf02	735,{
	if(IL_VAMP_QUE <= 10) {
		mes "[ジョジョ]";
		mes "うう……傷は治ったのに、";
		mes "なんでこんなに痛いの。";
		close;
	}
	else if(IL_VAMP_QUE == 11) {
		mes "[ジョジョ]";
		mes "キングさんが何かの匂いに";
		mes "気づいたようです。";
		mes "私が死線を彷徨っていた時も";
		mes "彼が匂いに気づいてくれた";
		mes "らしいです。";
		close;
	}
	else if(IL_VAMP_QUE == 12 || IL_VAMP_QUE == 13) {
		mes "[ジョジョ]";
		mes "向こうで争いが";
		mes "起きているみたいですね。";
		mes "早く行ってみましょう。";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	mes "[ジョジョ]";
	mes "私は当分の間、";
	mes "こちらに残るつもりです。";
	mes "ドラキュラさんが回復するまで";
	mes "もう少し時間がかかりそうです。";
	next;
	mes "[ジョジョ]";
	mes "シスタージェム一行と";
	mes "モジョにそう伝えてください。";
	close;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,80,139,5	script	ジェム#ilgf02	79,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,86,133,1	script	マリナ#ilgf02	746,5,5,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,85,139,3	script	アントワーヌ#ilgf02	669,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,84,135,3	script	ドラキュラ#ilgf03	10137,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,87,137,3	script	キング#ilgf02	799,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,80,132,7	script	ジョジョ#ilgf01	735,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,114,216,0	script	#ilgf01	139,3,0,{
	misceffect 561,"";
	if(IL_VAMP_QUE == 6) {
		cloakonnpc "魔法使い#ilgf01";
		cloakoffnpc "司祭#ilgf01";
		cloakoffnpc "マリナ#ilgf03";
		cloakoffnpc "マリナ#ilgf04";
		cloakoffnpc "マリナ#ilgf05";
		cloakoffnpc "マリナ#ilgf06";
		cloakoffnpc "マリナ#ilgf07";
		cloakoffnpc "マリナ#ilgf08";
		cloakoffnpc "マリナ#ilgf09";
	}
	else if(IL_VAMP_QUE == 7) {
		cloakoffnpc "魔法使い#ilgf01";
		cloakonnpc "マリナ#ilgf07";
		cloakonnpc "司祭#ilgf01";
		cloakoffnpc "魔法使い#ilgf25";
		cloakoffnpc "魔法使い#ilgf26";
		cloakoffnpc "アンデッド#ilgf01";
		cloakoffnpc "魔法使い#ilgf24";
		cloakoffnpc "光るキノコ#ilgf01";
		cloakoffnpc "魔法使い#ilgf23";
		cloakoffnpc "早いアンデッド#ilgf01";
		cloakoffnpc "魔法使い#ilgf21";
		cloakoffnpc "魔法使い#ilgf22";
		cloakoffnpc "アンデッド#ilgf02";
		cloakoffnpc "アンデッド#ilgf03";
		cloakoffnpc "アンデッド#ilgf04";
		cloakoffnpc "魔法使い#ilgf19";
		cloakoffnpc "魔法使い#ilgf20";
		cloakoffnpc "アンデッド#ilgf05";
		cloakoffnpc "魔法使い#ilgf18";
		cloakoffnpc "誰かの夢#ilgf18";
		cloakoffnpc "魔法使い#ilgf16";
		cloakoffnpc "魔法使い#ilgf17";
		cloakoffnpc "魔法使い#ilgf14";
		cloakoffnpc "魔法使い#ilgf15";
		cloakoffnpc "名も無き墓#ilgf01";
		cloakoffnpc "魔法使い#ilgf12";
		cloakoffnpc "魔法使い#ilgf13";
		cloakoffnpc "名も無き墓#ilgf02";
		cloakoffnpc "魔法使い#ilgf11";
		cloakoffnpc "魔法使い#ilgf09";
		cloakoffnpc "魔法使い#ilgf10";
		cloakoffnpc "魔法使い#ilgf08";
		cloakoffnpc "名も無き墓#ilgf03";
		cloakoffnpc "魔法使い#ilgf06";
		cloakoffnpc "魔法使い#ilgf07";
		cloakoffnpc "アンデッド#ilgf06";
		cloakoffnpc "魔法使い#ilgf27";
		cloakoffnpc "魔法使い#ilgf28";
	}
	else if(IL_VAMP_QUE == 8 || IL_VAMP_QUE == 9) {
		cloakoffnpc "魔法使い#ilgf01";
		cloakonnpc "ドラキュラ#ilgf03";
		cloakonnpc "キング#ilgf02";
		cloakonnpc "ジョジョ#ilgf01";
		cloakonnpc "ジェム#ilgf02";
		cloakonnpc "マリナ#ilgf02";
		cloakonnpc "アントワーヌ#ilgf02";
	}
	end;
}

gef_d01_i.gat,96,135,0	script	#illcon01	139,5,7,{
	if(IL_VAMP_QUE < 7) {
		cloakonnpc "魔法使い#ilgf01";
		cloakonnpc "ドラキュラ#ilgf03";
		cloakonnpc "キング#ilgf02";
		cloakonnpc "ジョジョ#ilgf01";
		cloakonnpc "ジェム#ilgf02";
		cloakonnpc "マリナ#ilgf02";
		cloakonnpc "アントワーヌ#ilgf02";
	}
	else if(IL_VAMP_QUE < 12 || IL_VAMP_QUE >= 14) {
		cloakoffnpc "魔法使い#ilgf01";
		cloakonnpc "ドラキュラ#ilgf03";
		cloakonnpc "キング#ilgf02";
		cloakonnpc "ジョジョ#ilgf01";
		cloakonnpc "ジェム#ilgf02";
		cloakonnpc "マリナ#ilgf02";
		cloakonnpc "アントワーヌ#ilgf02";
	}
	else if(IL_VAMP_QUE == 12) {
		cloakoffnpc "魔法使い#ilgf01";
		cloakoffnpc "ジェム#ilgf02";
		cloakoffnpc "マリナ#ilgf02";
		cloakoffnpc "アントワーヌ#ilgf02";
		cloakonnpc "ドラキュラ#ilgf03";
		cloakonnpc "キング#ilgf02";
		cloakonnpc "ジョジョ#ilgf01";
	}
	else if(IL_VAMP_QUE == 13) {
		cloakoffnpc "魔法使い#ilgf01";
		cloakoffnpc "ジェム#ilgf02";
		cloakoffnpc "マリナ#ilgf02";
		cloakoffnpc "アントワーヌ#ilgf02";
		cloakoffnpc "ドラキュラ#ilgf03";
		cloakoffnpc "キング#ilgf02";
		cloakoffnpc "ジョジョ#ilgf01";
	}
	end;
}
gef_d01_i.gat,81,135,0	duplicate(#illcon01)	#illcon02	139,5,7
gef_d01_i.gat,81,120,0	duplicate(#illcon01)	#illcon03	139,5,7
gef_d01_i.gat,96,120,0	duplicate(#illcon01)	#illcon04	139,5,7

gef_d01_i.gat,174,83,0	script	#illcon05	139,5,7,{
	if(IL_VAMP_QUE < 9) {
		cloakonnpc "魔法使い#ilgf02";
		cloakonnpc "キング#ilgf01";
		cloakonnpc "ドラキュラ#ilgf02";
		end;
	}
	cloakoffnpc "ドラキュラ#ilgf02";
	cloakoffnpc "キング#ilgf01";
	cloakoffnpc "魔法使い#ilgf02";
	end;
}
gef_d01_i.gat,189,98,0	duplicate(#illcon05)	#illcon06	139,5,7
gef_d01_i.gat,189,83,0	duplicate(#illcon05)	#illcon07	139,5,7
gef_d01_i.gat,204,83,0	duplicate(#illcon05)	#illcon08	139,5,7
gef_d01_i.gat,174,98,0	duplicate(#illcon05)	#illcon09	139,5,7
gef_d01_i.gat,204,98,0	duplicate(#illcon05)	#illcon10	139,5,7
gef_d01_i.gat,174,113,0	duplicate(#illcon05)	#illcon11	139,5,7
gef_d01_i.gat,189,113,0	duplicate(#illcon05)	#illcon12	139,5,7
gef_d01_i.gat,204,113,0	duplicate(#illcon05)	#illcon13	139,5,7

//==============================================================================

gef_d01_i.gat,49,113,3	script	魔法使い#ilgf06	669,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 1033,"アンデッド#ilgf06";
	if(!sleep2(1000)) end;
	hideonnpc "アンデッド#ilgf06";
	unittalk getnpcid(0,"魔法使い#ilgf06"),"魔法使い : あっ！　消滅してしまった！";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf07"),"魔法使い : アンデッドだから、イグドラシルの葉の効果が逆に作用したんじゃない？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf06"),"魔法使い : そうみたいね。これからはアンデッドに会ったらイグドラシルの葉を使えばいいんじゃない？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf07"),"魔法使い : 天才だ！";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf06";
	cloakonnpc "魔法使い#ilgf07";
	cloakonnpc "アンデッド#ilgf06";
	misceffect 496,"魔法使い#ilgf06";
	misceffect 496,"魔法使い#ilgf07";
	misceffect 496,"アンデッド#ilgf06";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,46,112,5	script	魔法使い#ilgf07	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,47,110,7	script	アンデッド#ilgf06	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,137,60,3	script	魔法使い#ilgf08	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 611,"名も無き墓#ilgf03";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf08"),"魔法使い : あれ、これでも起き上がらないな。どうやって奴らは動き回ってるんだろ？";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf08";
	cloakonnpc "名も無き墓#ilgf03";
	misceffect 496,"魔法使い#ilgf08";
	misceffect 496,"名も無き墓#ilgf03";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,136,58,5	script	名も無き墓#ilgf03	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,67,85,5	script	魔法使い#ilgf09	735,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf09"),"魔法使い : このジェムストーンを砕いて混ぜて使用すれば、あの肉体と魂を繋ぐ媒体を分離できるんじゃないだろうか？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf10"),"魔法使い : 私の見解では、あのゾンビたちには魂が欠けているとみた。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf09"),"魔法使い : ならいったいどうやって動いている？　あらゆる生物には魂が宿ってるんだよ！";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf10"),"魔法使い : 筋肉の反応？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf09"),"魔法使い : あれはどう見ても死んだ体に魂が戻っている！　体から魂を自由に脱着できれば、私たちは肉体のもたらす苦痛から自由になれる！";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf10"),"魔法使い : どうだか……魂が無くても体だけ生きてるかも知れない。あれはどうみても……。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf09"),"魔法使い : つべこべ言わずに、早くこれを砕いて。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf09";
	cloakonnpc "魔法使い#ilgf10";
	misceffect 496,"魔法使い#ilgf09";
	misceffect 496,"魔法使い#ilgf10";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,67,83,1	script	魔法使い#ilgf10	673,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,156,234,3	script	魔法使い#ilgf11	567,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf11"),"魔法使い : ハロー！　冒険者？　何歳？　ここは初めて？";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : 何故ノービスがこんな場所に……？",1;
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf11"),"魔法使い : 私がノービスに見える？　かわいいね。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……何だろう？",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf11";
	misceffect 496,"魔法使い#ilgf11";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,48,255,5	script	魔法使い#ilgf12	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf12"),"魔法使い : 48回目の実験。さぁ、今度は聖水をかけてみます。";
	if(!sleep2(1500)) end;
	misceffect 628,"名も無き墓#ilgf02";
	emotion 9,"名も無き墓#ilgf02";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf12"),"魔法使い : 何の変化もありませんでした。聖水の量を増やし49回目の実験を始めます。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf13"),"魔法使い : 聖職者を呼んだ方がよくない？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf12"),"魔法使い : いけません。聖職者たちはこいつらを見た途端、消そうとするでしょう。記録に集中して。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf12";
	cloakonnpc "魔法使い#ilgf13";
	cloakonnpc "名も無き墓#ilgf02";
	misceffect 496,"魔法使い#ilgf12";
	misceffect 496,"魔法使い#ilgf13";
	misceffect 496,"名も無き墓#ilgf02";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,50,257,5	script	魔法使い#ilgf13	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,50,254,5	script	名も無き墓#ilgf02	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,112,267,3	script	魔法使い#ilgf14	735,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf14"),"魔法使い : 起き上がれ！";
	if(!sleep2(1500)) end;
	misceffect 348,"名も無き墓#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf14"),"魔法使い : ダメだった。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf15"),"魔法使い : 言ったじゃない。私が返魂のお札を457枚も使ってみたけどダメだったって。そもそも奴らは違う原理で動いてるんだよ。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf14"),"魔法使い : その原理とは何？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf15"),"魔法使い : 私が知るか。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf14";
	cloakonnpc "魔法使い#ilgf15";
	cloakonnpc "名も無き墓#ilgf01";
	misceffect 496,"魔法使い#ilgf14";
	misceffect 496,"魔法使い#ilgf15";
	misceffect 496,"名も無き墓#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,110,266,5	script	魔法使い#ilgf15	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,111,264,5	script	名も無き墓#ilgf01	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,55,167,3	script	魔法使い#ilgf16	937,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf16"),"魔法使い : ポピに会いたい。これに成功したら、真っ先にポピを呼びたい。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf17"),"魔法使い : やめろ。あれを見ると無事に戻れそうにもない。骨の代わりにあんたの足の骨を噛むよ。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf16";
	cloakonnpc "魔法使い#ilgf17";
	misceffect 496,"魔法使い#ilgf16";
	misceffect 496,"魔法使い#ilgf17";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,53,166,7	script	魔法使い#ilgf17	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,236,235,1	script	魔法使い#ilgf18	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"誰かの夢#ilgf18"),"誰かの夢 : ヒヒーン！";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf18"),"魔法使い : ああ！　ごめんなさい！　あなたが見せる夢は気持ち悪すぎる。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf18";
	cloakonnpc "誰かの夢#ilgf18";
	misceffect 496,"魔法使い#ilgf18";
	misceffect 496,"誰かの夢#ilgf18";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,233,237,5	script	誰かの夢#ilgf18	1061,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,255,201,5	script	魔法使い#ilgf19	673,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 315,"魔法使い#ilgf19";
	misceffect 315,"魔法使い#ilgf20";
	unittalk getnpcid(0,"魔法使い#ilgf19"),"魔法使い : あ……どうしよう……思ったより強い。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf20"),"魔法使い : 私たち、いつ帰れるの？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf19"),"魔法使い : あれが行くまではダメ。今出たら殺される……。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf19";
	cloakonnpc "魔法使い#ilgf20";
	cloakonnpc "アンデッド#ilgf05";
	misceffect 496,"魔法使い#ilgf19";
	misceffect 496,"魔法使い#ilgf20";
	misceffect 496,"アンデッド#ilgf05";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,254,200,5	script	魔法使い#ilgf20	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,256,198,1	script	アンデッド#ilgf05	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,204,146,1	script	魔法使い#ilgf21	673,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	emotion 23,"魔法使い#ilgf21";
	unittalk getnpcid(0,"魔法使い#ilgf21"),"魔法使い : おい！　多過ぎるじゃないか！　一匹だけ連れて来てと言ったのに、こんなに連れて来てどうする！";
	if(!sleep2(1500)) end;
	emotion 26,"魔法使い#ilgf22";
	unittalk getnpcid(0,"魔法使い#ilgf22"),"魔法使い : しょうがないだろ！　いつの間にか増えちゃったんだから！";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf21"),"魔法使い : 頭を下げて！";
	if(!sleep2(1500)) end;
	misceffect 97,"アンデッド#ilgf02";
	misceffect 97,"アンデッド#ilgf03";
	misceffect 97,"アンデッド#ilgf04";
	if(!sleep2(1500)) end;
	cloakonnpc "アンデッド#ilgf02";
	cloakonnpc "アンデッド#ilgf03";
	cloakonnpc "アンデッド#ilgf04";
	unittalk getnpcid(0,"魔法使い#ilgf22"),"魔法使い : ふう……助かった。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf21";
	cloakonnpc "魔法使い#ilgf22";
	misceffect 496,"魔法使い#ilgf21";
	misceffect 496,"魔法使い#ilgf22";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,202,149,5	script	魔法使い#ilgf22	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,202,152,5	script	アンデッド#ilgf02	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,200,151,5	script	アンデッド#ilgf03	1015,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,204,151,3	script	アンデッド#ilgf04	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,257,110,1	script	魔法使い#ilgf23	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf23"),"魔法使い : 何あれ、なんであんなに足が早いの？　調べる前に私があの世に行っちゃうわ。";
	if(!sleep2(1500)) end;
	misceffect 95,"早いアンデッド#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf23"),"魔法使い : あんなのをどうやって捕まえるの……。実験室に連れていきたいのに……。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf23";
	cloakonnpc "早いアンデッド#ilgf01";
	misceffect 496,"魔法使い#ilgf23";
	misceffect 496,"早いアンデッド#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,253,112,5	script	早いアンデッド#ilgf01	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,230,76,3	script	魔法使い#ilgf24	704,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf24"),"魔法使い : よしよし……胞子採集中に死ぬ訳にはいかん。";
	if(!sleep2(1500)) end;
	misceffect 543,"光るキノコ#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf24"),"魔法使い : これぐらいあれば、部屋中をこの光で飾れるかな？";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf24";
	cloakonnpc "光るキノコ#ilgf01";
	misceffect 496,"魔法使い#ilgf24";
	misceffect 496,"光るキノコ#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,228,75,3	script	光るキノコ#ilgf01	3755,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,93,34,1	script	魔法使い#ilgf25	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf25"),"魔法使い : 今度はスクロールとイグドラシルの葉を一緒に使ってみよう。私がスクロールを使うから、あんたはイグドラシルの葉を使って。";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf26"),"魔法使い : 了解。";
	if(!sleep2(1500)) end;
	misceffect 53,"アンデッド#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf25"),"魔法使い : 今回も失敗？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf26"),"魔法使い : なんで上手くいかないの？　理論上はこれで人間になるはずじゃ？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf25"),"魔法使い : 落ち着いて。次は違う方法でやってみよう。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf25";
	cloakonnpc "魔法使い#ilgf26";
	cloakonnpc "アンデッド#ilgf01";
	misceffect 496,"魔法使い#ilgf25";
	misceffect 496,"魔法使い#ilgf26";
	misceffect 496,"アンデッド#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,94,37,3	script	魔法使い#ilgf26	64,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,91,35,5	script	アンデッド#ilgf01	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,101,124,3	script	魔法使い#ilgf27	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"魔法使い#ilgf27"),"魔法使い : こんなところで何の実験をするの？　捕えて持ち帰ったら？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf28"),"魔法使い : ここに流れる気配を感じる？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf27"),"魔法使い : それが何か？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf28"),"魔法使い : この力を私たちが利用できると思わない？";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"魔法使い#ilgf27"),"魔法使い : うーん……。";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : これは……ノートの持ち主の古い記憶のようだ。",1;
	if(!sleep2(1000)) end;
	cloakonnpc "魔法使い#ilgf27";
	cloakonnpc "魔法使い#ilgf28";
	misceffect 496,"魔法使い#ilgf27";
	misceffect 496,"魔法使い#ilgf28";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,99,122,7	script	魔法使い#ilgf28	10224,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_j.gat,81,135,5	script	ボミ#gef_d01_j	10224,{
	if('spawn)
		set '@name$,"[ボミの手紙]";
	else
		set '@name$,"[ボミ]";
	if(checkquest(14674)) {
		if(checkquest(14674) & 0x2) {
			mes '@name$;
			mes "冒険者様、";
			mes "先程はありがとうございました。";
			mes "よろしければまた血を";
			mes "作る材料を取ってきてください。";
			mes "あなただけが頼りです。";
			mes "よろしくお願いします。";
			delquest 14674;
			setquest 14671;
			close;
		}
		mes '@name$;
		mes "冒険者様、";
		mes "先程はありがとうございました。";
		mes "今は血が足りているので";
		mes "また後で来ていただけますか？";
		close;
	}
	if(checkquest(14671)) {
		if(checkquest(14671) & 0x4 == 0 || countitem(25268) < 10 || countitem(25269) < 10) {
			mes '@name$;
			mes "冒険者様、";
			mes "何を頼まれたのか忘れたようですね。";
			next;
			mes '@name$;
			mes "^0000cdマットドレインリアーと";
			mes "蛍きのこを5体以上狩って、";
			mes "べとべとする血と";
			mes "きのこの粘液が10個^000000";
			mes "必要です。お願いします。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐所持アイテムの種類数が多い為";
			mes "　危険です。";
			mes "　所持アイテムを減らしてから、";
			mes "　再度話しかけてください‐";
			close;
		}
		mes '@name$;
		mes "冒険者様、";
		mes "助けてくれて、本当にありがとう。";
		delitem 25268,10;
		delitem 25269,10;
		chgquest 14671,14674;
		getexp 100000000,0,1;
		getexp 0,20000000,0;
		getitem 25271,2;
		$IllVampBomiQuest++;
		close;
	}
	mes '@name$;
	mes "冒険者様、";
	mes "もし時間があるなら、";
	mes "私の頼みを聞いてくれませんか？";
	next;
	if(select("もちろんです。","今はちょっと忙しいですね。") == 2) {
		mes '@name$;
		mes "そうですか……";
		mes "仕方ありませんね。";
		close;
	}
	mes '@name$;
	mes "私が偽物の血で生きてるのは、";
	mes "ご存じですよね。";
	mes "これまでは私の分だけ十分でしたが、";
	mes "これからドラキュラの分も";
	mes "作ってあげようと思います。";
	next;
	mes '@name$;
	mes "^0000cdマットドレインリアーと";
	mes "蛍きのこを5体以上狩って、";
	mes "べとべとする血と";
	mes "きのこの粘液を10個^000000";
	mes "集めてきてはくれないでしょうか。";
	next;
	mes '@name$;
	mes "ただ少し気がかりなのは、";
	mes "偽物の血にはどうしても毒素が";
	mes "残ってしまうので、";
	mes "飲みすぎると毒素が溜まり、";
	mes "一時的に理性を失ってしまうのです。";
	next;
	mes '@name$;
	mes "今までは毒が抜けるまで";
	mes "待っていればよかったのですが、";
	mes "今は私以外の人間も";
	mes "ここにいるので……";
	next;
	mes '@name$;
	mes "なのでもし私が理性を失ったら、";
	mes "他の人を害しないよう、";
	mes "冒険者様が止めてください。";
	mes "なにとぞお願いします。";
	next;
	mes '@name$;
	mes "私はこの体になってから";
	mes "まだ時間があまり経っていないので";
	mes "耐性が弱いからかも知れません。";
	mes "ドラキュラは永く生きているし、";
	mes "強いから大丈夫でしょう。";
	setquest 14671;
	close;
OnSpawn:
	setnpcdisplay "ボミ#gef_d01_j",801;
	set 'spawn,1;
	end;
OnReflesh:
	setnpcdisplay "ボミ#gef_d01_j",10224;
	set 'spawn,0;
	end;
}

gef_d01_j.gat,189,98,3	script	ドラキュラ#gef_d01_j	10137,{
	mes "[ドラキュラ]";
	mes "ボミがコウモリの血を飲んだ後、";
	mes "時々苦しみながら暴れる時がある。";
	mes "時間が経てば落ち着くのだが、";
	mes "誤って教会の人間たちを";
	mes "襲いでもしたら……。";
	close;
}

gef_d01_j.gat,113,230,5	script	ジェム#gef_d01_j	79,{
	mes "[ジェム]";
	mes "怪しい気配のする場所です。";
	mes "気をしっかり持ってください。";
	close;
}

gef_d01_j.gat,112,228,5	script	マリナ#gef_d01_j	746,{
	mes "[マリナ]";
	mes "元の場所に戻りますか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[マリナ]";
		mes "わかりました。";
		mes "戻る時はいつでも";
		mes "声をかけてください。";
		close;
	}
	mes "[マリナ]";
	mes "足元にご注意ください。";
	close2;
	warp "gef_dun01.gat", 133, 219;
	end;
}

gef_d01_j.gat,116,228,3	script	アントワーヌ#gef_d01_j	669,{
	mes "[アントワーヌ]";
	mes "ここは興味深い物が多過ぎて";
	mes "何から手をつけたら良いか";
	mes "悩ましいですね。";
	close;
}

gef_d01_j.gat,185,97,5	script	キング#gef_d01_j	799,{
	mes "[キング]";
	mes "もうほとんど治っているのに";
	mes "ここから出ようとしない。";
	mes "一体あの人間の何がそんなに";
	mes "気に入ったんだか。";
	next;
	mes "[キング]";
	mes "そういえばお前、";
	mes "何でまだここにいるんだ？";
	mes "ドラキュラはほぼ完治したぞ？";
	next;
	mes "[ジョジョ]";
	mes "ここには調べたいものが";
	mes "たくさんあるんですよ。";
	next;
	mes "[ジョジョ]";
	mes "それに、";
	mes "ドラキュラさんやキングさんと";
	mes "一緒に居れば安全ですし。";
	next;
	emotion 4,"キング#gef_d01_j";
	mes "[キング]";
	mes "お前な……。";
	close;
}

gef_d01_j.gat,191,96,3	script	ジョジョ#gef_d02_j	735,{
	mes "[ジョジョ]";
	mes "モジョは元気そうでしたか？";
	mes "あいつは好奇心の塊だから、";
	mes "グリム司祭は苦労しそうですね。";
	close;
}

gef_d01_j.gat,0,0,0	script	#IllVampire	-1,{
OnInit:
	setarray 'table,3750,3752,3753,3754;
	for(set '@i,0;'@i<6;set '@i,'@i+1)
		areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
OnSummon:
	if('mob == 0 && $IllVampBomiQuest >= 3 && rand(250) < $IllVampBomiQuest*2) {
		initnpctimer;
	}
	areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
OnTimer15000:
	stopnpctimer;
	set 'mob,areacallmonster("gef_d01_j.gat",0,0,0,0,"ボミ",3756,strnpcinfo(0)+"::OnBomiKilled");
	unittalk 'mob,"ボミ : 冒……険……者……さま……逃げ……て……";
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
	mobuseskillpos 'mob,21,10,'@x,'@y,0,0;	// サンダーストーム
	mobuseskill 'mob,730,1,0,0,-1,0,0;	// M呪縛陣
	announce "ボミ : ダ、ダメ……毒が回り始めて……！", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	donpcevent "ボミ#gef_d01_j::OnSpawn";
	end;
OnBomiKilled:
	startnpctimer;
	end;
OnTimer75000:
	announce "‐ボミが長い眠りに落ちました‐", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
	end;
OnTimer135000:
	announce "怒りのドラキュラ : ボミを傷付けるのは誰だ！", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	end;
OnTimer195000:
	stopnpctimer;
	announce "怒りのドラキュラ : それ以上ボミに手を出すな！　どうしてもと言うなら代わりに俺が相手をしてやる。", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	hideonnpc "ドラキュラ#gef_d01_j";
	areamonster "gef_d01_j.gat",40,35,250,250,"怒りのドラキュラ",3757,1,strnpcinfo(0)+"::OnDracKilled";
	end;
OnDracKilled:
	startnpctimer;
	end;
OnTimer245000:
	stopnpctimer;
	hideoffnpc "ドラキュラ#gef_d01_j";
	announce "怒りのドラキュラ : まもなくボミが目覚める。人間達よ、約束を忘れるな！", 0x9, 0x00ff00, 0x0190, 20, 0, 0;
	donpcevent "ボミ#gef_d01_j::OnReflesh";
	set 'mob,0;
	set $IllVampBomiQuest,0;
	areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
}
