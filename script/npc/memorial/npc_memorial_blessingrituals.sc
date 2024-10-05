prt_lib.gat,56,61,4	script	守護騎士#ep16_roomguard	751,{
	if(EP16_1QUE < 13) {
		unittalk "守護騎士 : どうかされましたか。",1;
		end;
	}
	mes "[守護騎士]";
	mes "外出されますか？";
	mes "私がお送りする場所には、";
	mes "監視者がいらっしゃいます。";
	mes "移動しましたら、";
	mes "彼に声をかけてください。";
	next;
	if(select("外へ出る","外へ出ない")==2) {
		mes "[守護騎士]";
		mes "外へ出られる際は";
		mes "声をかけてください。";
		close;
	}
	mes "[守護騎士]";
	mes "ご案内いたします。";
	close2;
	warp "prt_pri00.gat",60,127;
	end;
}
prt_lib.gat,9,24,0	script	lib_to_prt_prison	45,1,1,{
OnTouch:
	if(EP16_1QUE < 14) {
		mes "[守護騎士]";
		mes "その先は侵入禁止です。";
		close2;
		warp "prt_lib.gat",60,61;
		end;
	}
	warp "prt_pri00.gat",60,127;
	end;
}

prt_lib.gat,91,78,2	script(CLOAKED)	マクシーミリアン#ep16_lib01	10133,{
	if(EP16_1QUE == 9) {
		mes "[マクシーミリアン]";
		mes "なんとういうことだ。";
		mes "王位継承の儀式が襲撃されるとは！";
		close;
	}
	end;
}
prt_lib.gat,80,79,3	script(CLOAKED)	クロネカー・ハイネン#ep16_lib01	10119,{
	if(EP16_1QUE == 9) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "ううむ……";
		mes "どうしたものか。";
		close2;
		cutin "ep16_kronecker_granz_heine",255;
		end;
	} else if(EP16_1QUE == 22) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "何か収穫はあったのか？";
		next;
		menu "見てきた事を話す",-;
		mes "[クロネカー]";
		mes "……そんな事があったとは！";
		mes "過去にプロンテラで";
		mes "大きな異変があった事は";
		mes "記録されているが……";
		next;
		mes "[クロネカー]";
		mes "儀式の部屋にあったユミルの心臓が";
		mes "12ヴァルキリーによって";
		mes "持ち去られたということなのか!?";
		mes "何故その事は記録されていない？";
		next;
		mes "[クロネカー]";
		mes "そうだ！";
		mes "この文書を読んでみてくれ！";
		mes "君が目撃したものが真実なら";
		mes "封印は解けるかもしれない！";
		next;
		cutin "ep16_kronecker_granz_heine",255;
		mes "‐クロネカーから渡された";
		mes "　本の真っ白なページに触れた途端、";
		mes "　そのページは光を放ち、";
		mes "　文字が浮かび上がって出て来た‐";
		next;
		mes "^4d4dff‐……";
		mes "　^4d4dffヴァルキリーの襲撃によって";
		mes "　^4d4dff儀式の部屋に封印されていた";
		mes "　^4d4dffユミルの心臓が消えた‐";
		next;
		mes "^4d4dff‐王室の正当性を象徴する物を";
		mes "　^4d4dff消失したことに恐れを抱いた。";
		mes "　^4d4dff戴冠式でテラグローリアの光を";
		mes "　^4d4dff見る事ができないと考えたら";
		mes "　^4d4dff目の前が真っ暗になった‐";
		next;
		mes "^4d4dff‐私ではなく、";
		mes "　^4d4dffこの次の代の即位式から";
		mes "　^4d4dff問題が発生するだろう‐";
		next;
		mes "^4d4dff‐王が即位するのに";
		mes "　^4d4dff大地が祝福を与えなければ、";
		mes "　^4d4dff王国の国民たちは今までなかった";
		mes "　^4d4dff異変を恐れながら未来に";
		mes "　^4d4dff怯える事になる‐";
		next;
		mes "^4d4dff‐秘密裏に大賢者バルムントに";
		mes "　^4d4dffこの状況を伝えた。";
		mes "　^4d4dff彼は自分なら何か";
		mes "　^4d4dff力になれると言い、";
		mes "　^4d4dff儀式の部屋に何かを設置した‐";
		next;
		mes "^4d4dff‐設置されたあれは驚くほど";
		mes "　^4d4dffテラグローリアに反応した。";
		mes "　^4d4dffテラグローリアの祝福の星に";
		mes "　^4d4dff十分な魔力を供給してくれた‐";
		next;
		mes "^4d4dff‐テラグローリアは名前通り、";
		mes "　^4d4dffいつもと変わらない大地の祝福を";
		mes "　^4d4dff与える事が出来るようになった‐";
		next;
		mes "^4d4dff‐全てが安定した。";
		mes "　^4d4dffたとえそれが偽物である";
		mes "　^4d4dffユミルの心臓によるもの";
		mes "　^4d4dffだったとしても‐";
		next;
		mes "^4d4dff‐テラグローリア……";
		mes "　^4d4dff私たちの美しい王冠。";
		mes "　^4d4dff祝福を受けた王冠には";
		mes "　^4d4dff代々プロンテラを守ってきた";
		mes "　^4d4dffユミルの心臓の欠片の一部が";
		mes "　^4d4dff残っている‐";
		next;
		mes "^4d4dff‐これで十分だ。";
		mes "　^4d4dff末裔たちはこれだけでも";
		mes "　^4d4dff十分なはずだ‐";
		next;
		mes "^4d4dff‐故に私はこの記録を";
		mes "　^4d4dff誰も見ないことを望み、";
		mes "　^4d4dff成立不可能な条件を付けて";
		mes "　^4d4dff封印する事にした‐";
		next;
		mes "^4d4dff‐だが万が一、我が末裔の誰かが";
		mes "　^4d4dffこの記録を見ることがあったなら、";
		mes "　^4d4dffテラグローリアだけは";
		mes "　^4d4dff何があっても守りなさい。";
		mes "　^4d4dff私たちに残された";
		mes "　^4d4dff最後のユミルの心臓なのだから‐^000000";
		next;
		mes "……";
		next;
		menu "全部読みました……",-;
		mes "[ニルレム]";
		mes "私、これで死ぬんですか？";
		mes "王家の秘密を知ってしまったので";
		mes "処刑されてしまうんですか？";
		next;
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "……ふむ";
		mes "君が死にたいのであれば、";
		mes "処刑してやっても良いが。";
		mes "今はまだ駄目だ。";
		next;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_warp"),"ニルレム : うぅ……",1;
		mes "[司書]";
		mes "そ……それでは私は？";
		cutin "ep16_kronecker_granz_heine",255;
		next;
		mes "[クロネカー]";
		mes "君はもうそれ以上";
		mes "何も言わなくていい。";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[クロネカー]";
		mes "驚くべき内容だったな。";
		mes "つまり破壊されたのは";
		mes "やつらの言うとおり、";
		mes "^4d4dff偽物のユミルの心臓^000000";
		mes "だったということか。";
		next;
		mes "[クロネカー]";
		mes "偽物でも長い時間";
		mes "ユミルの心臓の代わりとして";
		mes "誰にも気づかれることなく";
		mes "この地に祝福を";
		mes "与え続けられるということだな。";
		next;
		mes "[クロネカー]";
		mes "それよりも問題は";
		mes "テラグローリアの方か。";
		mes "あれはユミルの心臓の一部の欠片を";
		mes "細工したものなのだから……。";
		mes "代わりになるものなど作れるかどうか。";
		next;
		mes "[クロネカー]";
		mes "シュバルツバルドの企業と";
		mes "交渉をしなければならないのか……";
		mes "いや、待てよ……。";
		next;
		menu "私はどうすれば？",-;
		mes "[クロネカー]";
		mes "おお、これは申し訳ない。";
		mes "君を立たせたまま";
		mes "考えに耽ってしまった。";
		mes "ご苦労だった。";
		next;
		mes "[クロネカー]";
		mes "私からひとつお願いがある。";
		mes "これからもニルレムと共に";
		mes "あの場所に行ってみてくれないか？";
		next;
		mes "[クロネカー]";
		mes "会議の場で正式に議論すべきことだが、";
		mes "おそらくすぐに大きな動きは";
		mes "できないだろうと思っている。";
		next;
		mes "[クロネカー]";
		mes "そこで再び過去の儀式の間に行き、";
		mes "ユミルの心臓を守るか、";
		mes "可能ならばこちらへ持って来てくれ。";
		mes "過去を変えることなど";
		mes "できないかもしれないが、";
		mes "それでも何か得られるかもしれない。";
		next;
		mes "[クロネカー]";
		mes "いつでも王家の記憶の間に入れるよう";
		mes "許可はこちらで取っておく。";
		mes "フリードリヒに詳しい話を";
		mes "しておくから、これから";
		mes "やるべきことは彼から聞いてくれ。";
		next;
		mes "[クロネカー]";
		mes "なんとも情けない話だが、";
		mes "私たちには君しかいない。";
		mes "それではよろしく頼む。";
		delquest 7703;
		setquest 7704;
		set EP16_1QUE,23;
		next;
		cutin "ep16_kronecker_granz_heine",255;
		mes "^4d4dff‐フリードリヒ・シュトルツ";
		mes "　^4d4dff・ハイネンを通じて";
		mes "　^4d4dff過去の儀式の部屋と関連した";
		mes "　^4d4dffメモリアルダンジョンに";
		mes "　^4d4dff入場することができるように";
		mes "　^4d4dffなりました‐^000000";
		close;
	} else if(EP16_1QUE == 23) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "それでは当分の間、";
		mes "今回の件に関しては";
		mes "君とニルレムに一任する。";
		next;
		mes "[クロネカー]";
		mes "王室の正当性がかかった問題なのだ。";
		mes "極秘に遂行してくれ。";
		close2;
		cutin "ep16_kronecker_granz_heine",255;
		end;
	}
	end;
}

prt_lib.gat,81,79,5	script(CLOAKED)	クロネカー・ハイネン#ep16_lib02	10119,{}

prt_lib.gat,88,80,0	script	#ep16_lib_evt01	139,12,12,{
OnTouch:
	if(EP16_1QUE == 9) {
		cloakoffnpc "イアン・バルター#ep16_lib01";
		cloakoffnpc "ルヴィエル・ウィグナー#ep16_lib01";
		cloakoffnpc "マクシーミリアン#ep16_lib01";
		cloakoffnpc "クロネカー・ハイネン#ep16_lib01";
		cloakoffnpc "ニーヒル・ハイネン#ep16_lib01";
		mes "[イアン]";
		mes "お待ちしていました。";
		mes "あなたにお聞きしたいことが";
		mes "あります。";
		close;
	}
	end;
}
prt_lib.gat,83,80,5	script(CLOAKED)	ニーヒル・ハイネン#ep16_lib01	10114,{
	if(EP16_1QUE == 9) {
		cutin "ep16_nihi_miseria_heine01",0;
		mes "‐ニーヒルがいる‐";
		close2;
		cutin "ep16_nihi_miseria_heine01",255;
		end;
	}
	end;
}
prt_lib.gat,94,82,3	script(CLOAKED)	次元移動機#ep16_lib	10007,{
	if(EP16_1QUE > 17) {
		mes "[ニルレム]";
		mes "それじゃ強制的に";
		mes "次元の狭間に繋げてみます。";
		mes "見えない狭間だとしても";
		mes "亀裂は亀裂。 ";
		next;
		mes "[ニルレム]";
		mes "きっと、互いに大きな事件が";
		mes "起きたと思われる時点に";
		mes "繋がるはずですよ。";
		mes "準備出来ましたか？";
		next;
		if(select("準備できた","もうちょっと準備する")==2) {
			mes "[ニルレム]";
			mes "拍子抜けしますね……。";
			close;
		}
		mes "[ニルレム]";
		mes "それでは、良い夢を！";
		close2;
		warp "prt_lib_q.gat",89,43;
		end;
	}
	end;
}
prt_lib.gat,85,82,5	script(CLOAKED)	イアン・バルター#ep16_lib01	55,{
	if(EP16_1QUE == 9) {
		mes "[イアン]";
		mes "私たちがあなたを";
		mes "待っていた理由、";
		mes "すでにおわかりでしょうか。";
		next;
		mes "[イアン]";
		mes "あなたは";
		mes "^4d4dff儀式について";
		mes "^4d4dff誰かに話したことがありますか？^000000";
		next;
		mes "[イアン]";
		mes "この王家の記憶の間も";
		mes "祝福の儀式も、";
		mes "一部の関係者以外は";
		mes "知りえない場所なのです……。";
		next;
		menu "それは……",-;
		mes "[マクシーミリアン]";
		mes "そんな風に回りくどく";
		mes "言ったら伝わりませんよ。";
		mes "単刀直入に話してください。";
		next;
		menu "私を疑っているんですか？",-;
		mes "[イアン]";
		mes "いや、決してそういうわけでは……";
		next;
		mes "[イアン]";
		mes "ただ今回の儀式を知っている";
		mes "唯一の、外部の人間であるため";
		mes "形式にのっとってですね……";
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_lib01"),"ニーヒル : ……",1;
		next;
		cutin "ep16_nihi_miseria_heine01",0;
		mes "[ニーヒル]";
		mes "お待ちください。";
		mes "彼ではありません。";
		mes "彼は王家の記憶の間の存在、";
		mes "場所さえも知らなかったのです。";
		next;
		mes "[ニーヒル]";
		mes "私たちは、この方に";
		mes "王位継承者が決まったら";
		mes "儀式を参観してくれと";
		mes "話をしただけのはず。";
		next;
		mes "[ニーヒル]";
		mes "それがどこでどうやって";
		mes "行われるのかについては、";
		mes "冒険者様は直前まで";
		mes "知らされてもいなかった。";
		next;
		mes "[ニーヒル]";
		mes "予想外の事態に";
		mes "必要以上に警戒するのもわかりますが";
		mes "何の罪のないこの方を";
		mes "疑うような事はしないで下さい。";
		next;
		unittalk getnpcid(0,"クロネカー・ハイネン#ep16_lib01"),"クロネカー : ほう……。",1;
		mes "[ニーヒル]";
		mes "そして、それは……";
		next;
		cloakonnpc "クロネカー・ハイネン#ep16_lib01";
		cloakoffnpc "クロネカー・ハイネン#ep16_lib02";
		mes "[クロネカー]";
		mes "大変だ!!";
		mes "君たちこの文書を";
		mes "見たことあるか？";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[ルヴィエル]";
		mes "どうしました？";
		mes "何かありましたか？";
		mes "今は重要な話を……";
		cutin "ep16_kronecker_granz_heine",255;
		next;
		mes "[クロネカー]";
		mes "これほど重要な事はない！";
		mes "^4d4dffテラグローリア^000000が奪われた。";
		mes "私たちはいずれ来る未来に";
		mes "備えなければならない。";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[クロネカー]";
		mes "しかし^4d4dffテラグローリア^000000は消えた……。";
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : テラグローリアが？",1;
		unittalk getnpcid(0,"ルヴィエル・ウィグナー#ep16_lib01"),"ルヴィエル : 消えた？　それはいったい……！",1;
		unittalk getnpcid(0,"マクシーミリアン#ep16_lib01"),"マクシーミリアン : !!",1;
		next;
		mes "[クロネカー]";
		mes "そうだ……。";
		mes "先ほどピーターを介抱している時には";
		mes "消えてなくなっていた。";
		mes "おそらく爆発を起こし、";
		mes "こちらが混乱している隙に";
		mes "やつらが持ち去ったのだろう。";
		next;
		mes "[クロネカー]";
		mes "そして……";
		mes "やつらはこう話していた。";
		mes "^4d4dffユミルの心臓は偽物^000000だと。";
		next;
		mes "[ニーヒル]";
		mes "お話中に申し訳ございません。";
		mes "報告したいことがあります。";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		mes "[クロネカー]";
		mes "なんだ！";
		mes "今は立て込んでいると";
		mes "見てわかるだろう！";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[ニーヒル]";
		mes "重要な事ですので……。";
		mes "この一連の事件の元凶について";
		mes "ご説明しようと思います。";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		mes "[イアン]";
		mes "事件の元凶？";
		mes "それは……機密を漏らした者を";
		mes "公子は知っているという意味ですか？";
		cutin "ep16_nihi_miseria_heine01",255;
		next;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_lib01"),"ニーヒル : ……",1;
		cutin "ep16_nihi_miseria_heine01",0;
		mes "[ニーヒル]";
		mes "儀式に関する事を";
		mes "外部に漏らした者……。";
		mes "それは……";
		if(!sleep2(1000)) end;
		mes "他ならぬ私です。";
		if(!sleep2(500)) end;
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : 何!?",1;
		unittalk getnpcid(0,"ルヴィエル・ウィグナー#ep16_lib01"),"ルヴィエル : !!",1;
		unittalk getnpcid(0,"マクシーミリアン#ep16_lib01"),"マクシーミリアン : ふう……",1;
		mes "……ですので";
		next;
		mes "[ニーヒル]";
		mes "罪を問うのなら私に。";
		next;
		mes "[クロネカー]";
		mes "どういう事だニーヒル！";
		mes "お前がどうして！";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[ニーヒル]";
		mes "おそらく、私のはずです。";
		mes "朦朧とした意識の中、";
		mes "儀式について誰かに";
		mes "話してしまった記憶があります。";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		menu "(まさか、あの時の……？)",-;
		cutin "ep16_nihi_miseria_heine01",255;
		mes "‐あなたは、祝宴会場で";
		mes "　ニーヒルが侍従に";
		mes "　酔いつぶされたときのことを";
		mes "　思い出した‐";
		next;
		cutin "ep16_nihi_miseria_heine01",0;
		mes "[ニーヒル]";
		mes "私の責任です。";
		mes "面目ありません。";
		next;
		mes "[イアン]";
		mes "こんな事が……";
		mes "ハイネンの大公子が……。";
		mes "私たちバルター家は";
		mes "今回の王位継承候補からは";
		mes "外されているが、";
		mes "今回の事は決して無視できません！";
		cutin "ep16_nihi_miseria_heine01",255;
		next;
		mes "[マクシーミリアン]";
		mes "なんてことを……";
		mes "何を考えてそんな事をしたのだ？";
		next;
		mes "[マクシーミリアン]";
		mes "意味がわからないぞ。";
		mes "王位欲しさに邪魔なピーターを";
		mes "殺そうとしたのか？";
		next;
		mes "[ニーヒル]";
		mes "……そうではありません。";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		mes "[クロネカー]";
		mes "弁明があれば言ってみなさい。";
		mes "それでお前が使えない人間ということが";
		mes "変わるわけではないがな。";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[ニーヒル]";
		mes "弁明はありません。";
		mes "ただ……";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		mes "[ニーヒル]";
		mes "私もルーンミッドガッツ王国の";
		mes "七王家であるハイネン家の者です。";
		mes "そんな事をする理由がありません。";
		next;
		mes "[マクシーミリアン]";
		mes "うーむ、ニーヒル。";
		mes "さっぱりわからないぞ。";
		mes "頼むから説明をしてくれ。";
		cutin "ep16_nihi_miseria_heine01",255;
		next;
		mes "[ニーヒル]";
		mes "……。";
		cutin "ep16_nihi_miseria_heine01",0;
		next;
		menu "間に入る",-;
		mes "[イアン]";
		mes "なんだね？";
		mes "何か知っている事があるのかね？";
		mes "先ほどは余計な疑いを";
		mes "かけてしまって申し訳なかった。";
		mes "何か言いたい事があるなら";
		mes "話してみなさい。";
		cutin "ep16_nihi_miseria_heine01",255;
		next;
		menu "祝宴場でのことを話す",-;
		mes "[ルヴィエル]";
		mes "……そんな事が？";
		mes "怪しい葡萄酒を勧めてきた侍従、";
		mes "直後に公子がまるで泥酔したように……";
		next;
		mes "[ルヴィエル]";
		mes "それでは公子は何者かに";
		mes "利用されたと……。";
		next;
		mes "[マクシーミリアン]";
		mes "なるほど……";
		mes "しかし、事が事だけに、";
		mes "安易にその話を鵜呑みにすることは";
		mes "出来ません。";
		mes "何かそのことを証明するものは";
		mes "ありますか？";
		next;
		menu "^4d4dffネリウス家のお嬢様^000000なら……",-;
		mes "[イアン]";
		mes "ふむ……";
		mes "ネリウス家のお嬢様も";
		mes "一緒に目撃したのか……。";
		next;
		mes "[イアン]";
		mes "グランツ。";
		mes "これからどうするつもりなんだ？";
		next;
		mes "[クロネカー]";
		mes "仮に不可抗力だったとしても、";
		mes "ニーヒルが儀式のことを";
		mes "口外してしまったのは";
		mes "間違いない事実。";
		mes "なかった事にはできない。";
		cutin "ep16_kronecker_granz_heine",2;
		next;
		mes "[クロネカー]";
		mes "立場上、個人的見解を述べるのは";
		mes "些か問題はあるが……";
		mes "一歩間違えれば王家に対する";
		mes "反逆行為だ。";
		mes "それは言い逃れはできない。";
		next;
		mes "[クロネカー]";
		mes "……ニーヒルには当分の間、";
		mes "自粛する意味として謹慎を命じる。";
		mes "必要な者たち以外、";
		mes "他の者との接触も禁止だ。";
		next;
		mes "[クロネカー]";
		mes "そして、消えた^4d4dffテラグローリア^000000と";
		mes "破壊されたユミルの心臓に対しても";
		mes "対策を講じなければならぬ。";
		next;
		mes "[イアン]";
		mes "長い会議が必要になりそうだ。";
		mes "私がすぐに会議を招集しよう。";
		cutin "ep16_kronecker_granz_heine",255;
		next;
		mes "[イアン]";
		mes "それでは後でお会いしましょう。";
		delquest 7693;
		setquest 73057;
		set EP16_1QUE,10;
		close2;
		pcblockmove 1;
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : マジシャン！　ゲートを開いてくれ。",1;
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_warp"),"ニルレム : あっ、はい。ゲートは既に開いている状態です！",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : そうなのか。それでは失礼する。",1;
		if(!sleep2(3000)) end;
		cloakonnpc "イアン・バルター#ep16_lib01";
		if(!sleep2(500)) end;
		cloakonnpc "ルヴィエル・ウィグナー#ep16_lib01";
		cloakonnpc "マクシーミリアン#ep16_lib01";
		if(!sleep2(500)) end;
		unittalk getnpcid(0,"クロネカー・ハイネン#ep16_lib02"),"クロネカー : ニーヒルも一緒に来なさい。",1;
		if(!sleep2(3000)) end;
		cloakonnpc "クロネカー・ハイネン#ep16_lib02";
		cloakonnpc "ニーヒル・ハイネン#ep16_lib01";
		pcblockmove 0;
		end;
	}
	if(EP16_1QUE > 9) {
		mes "[イアン]";
		mes "長い会議が必要になりそうだ。";
		mes "私がすぐに会議を招集しよう。";
		close2;
		pcblockmove 1;
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : マジシャン！　ゲートを開いてくれ。",1;
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_warp"),"ニルレム : あっ、はい。ゲートは既に開いている状態です！",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"イアン・バルター#ep16_lib01"),"イアン : そうなのか。それでは失礼する。",1;
		if(!sleep2(3000)) end;
		cloakonnpc "イアン・バルター#ep16_lib01";
		if(!sleep2(500)) end;
		cloakonnpc "ルヴィエル・ウィグナー#ep16_lib01";
		cloakonnpc "マクシーミリアン#ep16_lib01";
		if(!sleep2(500)) end;
		unittalk getnpcid(0,"クロネカー・ハイネン#ep16_lib02"),"クロネカー : ニーヒルも一緒に来なさい。",1;
		if(!sleep2(3000)) end;
		cloakonnpc "クロネカー・ハイネン#ep16_lib02";
		cloakonnpc "ニーヒル・ハイネン#ep16_lib01";
		pcblockmove 0;
		end;
	}
	end;
}
prt_lib.gat,88,83,4	script(CLOAKED)	ルヴィエル・ウィグナー#ep16_lib01	10132,{
	if(EP16_1QUE == 9) {
		mes "[ルヴィエル]";
		mes "恐ろしい事態になった……。";
		close;
	}
	end;
}

prt_lib.gat,76,80,3	script	司書リント#ep16_lindt	47,{
	if(EP16_1QUE == 11) {
		mes "[司書]";
		mes "先ほど見ていたものを";
		mes "もう一度見たいのですね？";
		mes "まだ整理する前だったので";
		mes "ここにあります。";
		mes "^4d4dff王家の記録^000000という歴史書です。";
		next;
		mes "‐司書から受け取った文書は";
		mes "　儀式の部屋と関連している";
		mes "　王室の記録だった‐";
		unittalk getnpcid(0,"司書リント#ep16_lindt"),"司書 : 見ても無駄だと思いますが……",1;
		next;
		mes "‐文書の中に";
		mes "　何も書かれていない";
		mes "　白紙が何枚かある‐";
		next;
		menu "ここはどうして白紙に？",-;
		mes "[司書]";
		mes "上に書いてある文字を見て下さい。";
		mes "ここです。";
		next;
		mes "[司書]";
		mes "^4d4dff真実を知る者だけが知る事ができる。^000000";
		mes "ここに書いてありますよね？";
		mes "おそらく……";
		next;
		mes "[司書]";
		mes "真実を知っている者というのは、";
		mes "この世に残っていないでしょう。";
		mes "ですのでこの部分は永遠に";
		mes "知る事の出来ない内容、";
		mes "という事になります。";
		next;
		mes "[司書]";
		mes "それでグランツ大公様も";
		mes "諦めてそのまま戻ったのです。";
		mes "確認はもうよろしいですか？";
		mes "これはまた整理しておきます。";
		set EP16_1QUE,12;
		close;
	}
	if(EP16_1QUE == 22) {
		mes "[司書]";
		mes "あ、来ましたね。";
		mes "グランツ大公が先ほどから";
		mes "お待ちしております。";
		close;
	}
	mes "[司書]";
	mes "私の家門は代々続けて";
	mes "王家の記憶の間を管理しています。";
	mes "王室専用記録室なので";
	mes "当たり前ですが。";
	next;
	mes "[司書]";
	mes "実は、先代から受けついたばかりで";
	mes "知らない事が多い状態です……";
	mes "こんなにも多くの公爵閣下が";
	mes "訪ねて来るとは思っても";
	mes "いませんでしたから……";
	close;
}

prt_lib.gat,91,85,3	script	マジシャン・ニルレム#ep16_warp	735,{
	switch(EP16_1QUE) {
	case 8:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "‐^4d4dffこのイベントは";
			mes "　^4d4dffメモリアルダンジョンで進行します。";
			mes "　^4d4dffパーティーを結成した後、";
			mes "　^4d4dffもう一度試して下さい^000000‐";
			close;
		}
		if(getonlinepartymember() != 1) {
			mes "‐^4d4dffこのイベントは";
			mes "　^4d4dff1人専用のメモリアルダンジョンで";
			mes "　^4d4dff進行します。";
			mes "　^4d4dffパーティーメンバーが1人の状態で";
			mes "　^4d4dffもう一度試して下さい^000000‐";
			close;
		}
		mes "[ニルレム]";
		mes "私たちが一番最後ですよ。";
		mes "他の方たちはすでに";
		mes "入場したみたいです。";
		mes "王位継承の儀式に参加しますか？";
		next;
		mes "‐^4d4dff王位継承の儀式の注意事項^000000‐";
		mes "　以下のクエストは";
		mes "　王位継承の儀式を開始する前の";
		mes "　設定でストーリーが進行します。";
		mes "　";
		mes "　・ウィグナー家の心の箱クエスト";
		mes "　・ウィグナー家の心の箱(おまけ)クエスト";
		mes "　・レベンブルグ家の絆クエスト";
		mes "　・エルンスト王子とゲオルグ家クエスト";
		mes "　・バルター家の調査クエスト";
		mes "　";
		mes "　もしストーリーの内容を";
		mes "　より楽しみたい場合は";
		mes "　上記のクエストを先に進行することを";
		mes "　お勧めいたします。";
		next;
		switch(select("すぐに入場する","入場しない","説明してほしい","部屋に戻りたい")) {
		case 1:
			mes "[ニルレム]";
			mes "儀式の間へのゲートが";
			mes "開きました！";
			mes "さあ、行きましょう！";
			cloakoffnpc "儀式の間への入口#evt_gate01";
			mdcreate "blessing_rituals";
			close;
		case 2:
			mes "[ニルレム]";
			mes "そうですか……";
			mes "あまり遅くなるのも";
			mes "よくないのに……。";
			close;
		case 3:
			mes "[ニルレム]";
			mes "あれ～、聞いてないんですか～？";
			mes "王位継承の儀式が始まるんです！";
			mes "他の方たちはすでに";
			mes "入場したみたいですよ～。";
			close;
		case 4:
			mes "[ニルレム]";
			mes "忘れものですか～？";
			mes "儀式が始まっちゃいますよ！";
			mes "急いでくださいね！";
			close2;
			warp "prt_cas_q.gat",30,28;
			end;
		}
	case 9:
		mes "[ニルレム]";
		mes "中で何か起きたのですか？";
		mes "これは一体……。";
		next;
		mes "[ニルレム]";
		mes "私が知るべき事ではなく、";
		mes "私が出しゃばる場面でもありませんが";
		mes "気になりますね。";
		next;
		mes "[ニルレム]";
		mes "魔力の動きが怪しいですね。";
		mes "……ゲートが不安定に見えるのは";
		mes "気のせいでしょうか？";
		close;
	case 10:
		mes "[ニルレム]";
		mes "これは困りましたね。";
		mes "今、移動した方を最後に";
		mes "ゲートに問題が発生しました……。";
		next;
		mes "[ニルレム]";
		mes "ここは魔法の制約が";
		mes "非常に大きい場所ですので、";
		mes "私もゲートを開く程度しか";
		mes "出来なくて……。";
		next;
		menu "つまりどういう事？",-;
		mes "[ニルレム]";
		mes "つまりですね……。";
		mes "歩いて行かなければならなくなった。";
		mes "とまぁ、そんな話です。";
		mes "……そうだ！";
		next;
		mes "[ニルレム]";
		mes "^4d4dff先ほど大公閣下が";
		mes "^4d4dffご覧になっていた資料^000000、";
		mes ""+strcharinfo(0)+"様も";
		mes "一度ご覧になりますか？";
		next;
		mes "[ニルレム]";
		mes "べ、別に気になるわけでは";
		mes "ありませんよ？";
		next;
		mes "[ニルレム]";
		mes "ちょっとした好奇心……";
		mes "いえ、何でもないです。";
		mes "どうです？　見てみませんか！";
		mes "そして私にもその内容をぜひ！";
		setquest 7694;	// state=1
		delquest 73057;
		set EP16_1QUE,11;
		close;
	case 11:
		mes "[ニルレム]";
		mes "気にならないんですか!?";
		mes "大公閣下たちと";
		mes "一緒に出てきましたから、";
		mes "司書にも怪しまれないで";
		mes "見せてくれるはずなのに？";
		next;
		mes "[ニルレム]";
		mes "その間、どうすればゲートを";
		mes "開く事ができるか調べてみます。";
		close;
	case 12:
		mes "[ニルレム]";
		mes "……";
		mes "^4d4dff真実を知る者だけが知る事ができる、^000000";
		mes "とは……。";
		mes "ああ、意味がないよ。";
		next;
		mes "[ニルレム]";
		mes "ちぇっ、";
		mes "これ以上ここにいても";
		mes "何の意味もありませんよ。";
		mes "あまり良い空気でもないですし、";
		mes "早くここから出ましょう。";
		next;
		mes "[ニルレム]";
		mes "ゲートを調べてみましたが、";
		mes "内部で大きな魔力の";
		mes "爆発のようなものが";
		mes "起こりませんでしたか？";
		next;
		mes "[ニルレム]";
		mes "一種の魔力歪曲が感じられます。";
		mes "そうですね……";
		mes "^4d4dff次元の狭間^000000と似た感じの";
		mes "魔力の歪みですね。";
		next;
		mes "[ニルレム]";
		mes "ここに次元ゲートを作れるのかな……";
		mes "それはそれで面白そうですけどね。";
		next;
		mes "[ニルレム]";
		mes "いろいろあって今はゲートが";
		mes "使い物にならないので";
		mes "歩いて出ましょう。";
		next;
		mes "[ニルレム]";
		mes "あちらにクルセイダーの方が";
		mes "いますよね？";
		mes "出入りする通路を管理していますので、";
		mes "あの方が案内してくれますよ。";
		delquest 7694;
		setquest 7695;
		set EP16_1QUE,13;
		close;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "[ニルレム]";
		mes "いろいろあって今はゲートが";
		mes "使い物にならないので";
		mes "歩いて出ましょう。";
		next;
		mes "[ニルレム]";
		mes "あちらにクルセイダーの方が";
		mes "いますよね？";
		mes "出入りする通路を管理していますので、";
		mes "あの方が案内してくれますよ。";
		close;
	case 18:
		mes "[ニルレム]";
		mes "ふふふ……";
		mes "それでは行きますよ。";
		mes "出でよ！";
		mes "^4d4dffどこでも次元移動機～～^000000!!";
		next;
		cloakoffnpc "次元移動機#ep16_lib";
		mes "[ニルレム]";
		mes "さあ、行きましょうか。";
		mes "今回は何を見ることが";
		mes "できるのか楽しみです。";
		setquest 7700;
		delquest 7699;
		set EP16_1QUE,19;
		close;
	case 19:
	case 20:
	case 21:
		mes "[ニルレム]";
		mes "ふふふ……";
		mes "それでは行きますよ。";
		mes "出でよ！";
		mes "^4d4dffどこでも次元移動機～～^000000!!";
		next;
		cloakoffnpc "次元移動機#ep16_lib";
		mes "[ニルレム]";
		mes "さあ、行きましょうか。";
		mes "今回は何を見ることが";
		mes "できるのか楽しみです。";
		close;
	case 22:
		mes "[ニルレム]";
		mes "何をしているんですか？";
		mes "早く司書に言って";
		mes "王室の記録を読ませてもらわないと！";
		mes "真実を知った今なら";
		mes "何かわかるかもしれません！";
		next;
		cloakoffnpc "クロネカー・ハイネン#ep16_lib01";
		mes "[ニルレム]";
		mes "何の為に私たちは";
		mes "あんな苦労をしてきたんですか？";
		mes "あ、見てください。";
		mes "グランツ大公が";
		mes "いらっしゃいましたよ。";
		close;
	case 23:
		mes "[ニルレム]";
		mes "^4d4dffハイネン家が「王家の記憶の間」に";
		mes "自由に出入り出来るように";
		mes "許可^000000を取ってくれるらしいですね。";
		mes "私たち、これから嫌というほど";
		mes "会うことになりますね。";
		mes "ふふ、これが運命というものです。";
		next;
		mes "[ニルレム]";
		mes "何をしているんですか？";
		mes "^4d4dffフリードリヒ公爵閣下に会って";
		mes "許可が下りたか確認^000000しないと！";
		close;
	case 24:
		mes "[ニルレム]";
		mes "今日も私たちだけの隠密旅行に";
		mes "出かけるんですね！";
		mes "ハッハッハ、期待してて下さい！";
		mes "もちろん特別待遇ですから！";
		next;
		cloakoffnpc "次元移動機#ep16_lib";
		mes "[ニルレム]";
		mes "さ、出発しますよ。";
		mes "今日は何か成果が出ますかね？";
		mes "多分、失敗だとは思いますけど。";
		mes "あははははは。";
		close;
	}
	end;
}
prt_lib.gat,88,90,1	script(CLOAKED)	儀式の間への入口#evt_gate01	10007,{
	if(EP16_1QUE == 8) {
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "‐^4d4dffこのイベントは";
			mes "　^4d4dffメモリアルダンジョンで進行します。";
			mes "　^4d4dffパーティーを結成した後、";
			mes "　^4d4dffもう一度試して下さい^000000‐";
			close;
		}
		if(getonlinepartymember() != 1) {
			mes "‐^4d4dffこのイベントは";
			mes "　^4d4dff1人専用のメモリアルダンジョンで";
			mes "　^4d4dff進行します。";
			mes "　^4d4dffパーティーメンバーが1人の状態で";
			mes "　^4d4dffもう一度試して下さい^000000‐";
			close;
		}
		mes "‐祝福の儀式が行われる場所に";
		mes "　移動が可能です‐";
		next;
		if(select("入る","入らない") == 2) {
			mes "[ニルレム]";
			mes "このゲートは一時的に";
			mes "開いたものなので";
			mes "長くは持ちませんよ……";
			close;
		}
		switch(mdenter("blessing_rituals")) {
		case 0:	// エラーなし
			announce "メモリアルダンジョン[blessing_rituals] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
			donpcevent getmdnpcname("#royal_Control1")+ "::OnStart";
			close;
		case 1:	// パーティー未加入
			mes "‐メモリアルダンジョンを";
			mes "　生成したパーティーのメンバーのみ、";
			mes "　メモリアルダンジョンに入れます‐";
			close;
		case 2:	// ダンジョン未作成
			mes "[ニルレム]";
			mes "儀式の間に向かうゲートが";
			mes "ちゃんと開いていません。";
			mes "ちょっと待って下さい。";
			close;
		default:	// その他エラー
			close;
		}
	}
}

2@mir.gat,0,0,0		script	#royal_Control1	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("エルンスト・ゲオルグ#02");
	hideonnpc getmdnpcname("ヘルムト・レベンブルグ#02");
	hideonnpc getmdnpcname("ルヴィエル・ウィグナー#02");
	hideonnpc getmdnpcname("ユルゲン・ウィグナー#02");
	hideonnpc getmdnpcname("マクシーミリアン#02");
	hideonnpc getmdnpcname("ヴォルフ・レベンブルグ#02");
	hideonnpc getmdnpcname("アグネス・レベンブルグ#02");
	hideonnpc getmdnpcname("アイザック・ウィグナー#02");
	hideonnpc getmdnpcname("カトリン・ウィグナー#02");
	hideonnpc getmdnpcname("キャサリン・ゲオルグ#02");
	hideonnpc getmdnpcname("スピーカ・ネリウス#02");
	hideonnpc getmdnpcname("エルンスト・ゲオルグ#03");
	hideonnpc getmdnpcname("スキア・ネリウス#03");
	hideonnpc getmdnpcname("ポー・リハルト#02");
	hideonnpc getmdnpcname("イアン・バルター#02");
	hideonnpc getmdnpcname("アイゼン・アノ#02");
	hideonnpc getmdnpcname("フリードリヒ・ハイネン#02");
	hideonnpc getmdnpcname("クロネカー・ハイネン#02");
	hideonnpc getmdnpcname("倒れたピーター#02");
	hideonnpc getmdnpcname("ニーヒル・ハイネン#03");
	hideonnpc getmdnpcname("ニーヒル・ハイネン#02");
	hideonnpc getmdnpcname("スキア・ネリウス#02");
	hideonnpc getmdnpcname("侵入者#hunter01");
	hideonnpc getmdnpcname("侵入者#hunter02");
	hideonnpc getmdnpcname("侵入者#hunter03");
	hideonnpc getmdnpcname("侵入者#hunter04");
	hideonnpc getmdnpcname("侵入者#hunter05");
	hideonnpc getmdnpcname("侵入者#hunter06");
	end;
}

2@mir.gat,101,12,0	script	royal_evt01		139,1,1,{
OnTouch:
	disablenpc;
	hideonnpc getmdnpcname("to_prt_lib");
	initnpctimer getmdnpcname("#royal_evt02");
	mes "["+strcharinfo(0)+"]";
	mes "（まもなく儀式がはじまるようだ）";
	mes "　";
	mes "‐祝福の儀式に参列しよう‐";
	close;
}

2@mir.gat,101,10,0	script	to_prt_lib					45,1,1,{
	end;
OnTouch:
	mes "（ここから元いた場所へ";
	mes "戻れそうだ……）";
	mes "　";
	mes "‐戻りますか？‐";
	next;
	if(select("戻らない","戻る")==1) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	close2;
	warp "prt_lib.gat",88,80;
	end;
}

2@mir.gat,103,17,3	script	ニーヒル・ハイネン#01		10114,{
	mes "[スキア]";
	mes "いらっしゃいましたね！";
	mes "お待ちしておりました。";
	cutin "ep16_skia_nerius01",0;
	next;
	mes "[ニーヒル]";
	mes "待っていました。";
	mes "他の家門の方たちは";
	mes "全員揃っています。";
	cutin "ep16_nihi_miseria_heine01",2;
	next;
	mes "[ニーヒル]";
	mes "……";
	mes "何か違和感があります。";
	mes "先ほど誰かが入室したように";
	mes "見えたのですが……";
	mes "気のせいでしょうか？";
	next;
	mes "[スキア]";
	mes "急ぎましょう。";
	mes "これ以上、皆を待たせる訳には";
	mes "いきません。";
	cutin "ep16_skia_nerius01.bmp",0;
	next;
	mes "[スキア]";
	mes "^4d4dffリハルト大公子様の隣の席へ";
	mes "^4d4dffお進みください。^000000";
	mes "そこが参観員として出席される";
	mes "あなたに用意された席です。";
	next;
	mes "[スキア]";
	mes "さあ、行きましょう。";
	cutin "ep16_skia_nerius01.bmp",0;
	close2;
	hideonnpc getmdnpcname("ニーヒル・ハイネン#01");
	hideonnpc getmdnpcname("スキア・ネリウス#01");
	hideoffnpc getmdnpcname("ニーヒル・ハイネン#02");
	hideoffnpc getmdnpcname("スキア・ネリウス#02");
	cutin "ep16_skia_nerius01",255;
	end;
}
2@mir.gat,100,17,5	script	スキア・ネリウス#01			10116,{
	mes "[スキア]";
	mes "いらっしゃいましたね！";
	mes "お待ちしておりました。";
	cutin "ep16_skia_nerius01",0;
	next;
	mes "[ニーヒル]";
	mes "待っていました。";
	mes "他の家門の方たちは";
	mes "全員揃っています。";
	cutin "ep16_nihi_miseria_heine01",2;
	next;
	mes "[ニーヒル]";
	mes "……";
	mes "何か違和感があります。";
	mes "先ほど誰かが入室したように";
	mes "見えたのですが……";
	mes "気のせいでしょうか？";
	next;
	mes "[スキア]";
	mes "急ぎましょう。";
	mes "これ以上、皆を待たせる訳には";
	mes "いきません。";
	cutin "ep16_skia_nerius01.bmp",0;
	next;
	mes "[スキア]";
	mes "^4d4dffリハルト大公子様の隣の席へ";
	mes "^4d4dffお進みください。^000000";
	mes "そこが参観員として出席される";
	mes "あなたに用意された席です。";
	next;
	mes "[スキア]";
	mes "さあ、行きましょう。";
	cutin "ep16_skia_nerius01.bmp",0;
	close2;
	hideonnpc getmdnpcname("ニーヒル・ハイネン#01");
	hideonnpc getmdnpcname("スキア・ネリウス#01");
	hideoffnpc getmdnpcname("ニーヒル・ハイネン#02");
	hideoffnpc getmdnpcname("スキア・ネリウス#02");
	cutin "ep16_skia_nerius01",255;
	end;
}

2@mir.gat,101,88,4	script	クロネカー・ハイネン#01		10119,{
	end;
OnStart:
	set .phase,1;
	initnpctimer;
	hideonnpc getmdnpcname("ニーヒル・ハイネン#01");
	hideonnpc getmdnpcname("スキア・ネリウス#01");
	hideoffnpc getmdnpcname("ニーヒル・ハイネン#02");
	hideoffnpc getmdnpcname("スキア・ネリウス#02");
	announce "クロネカー : 遅くなったが儀式を進めよう。", 0x9, 0x00ff99;
	end;
OnTimer3000:
	announce "クロネカー : 王室の伝統に則り、七王家の意思と立ち合いを確認したい。", 0x9, 0x00ff99;
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("フリードリヒ・ハイネン#01")),"フリードリヒ : ハイネン";
	unittalk getnpcid(0,getmdnpcname("ニーヒル・ハイネン#02")),"ニーヒル : ハイネン";
	end;
OnTimer9000:
	unittalk getnpcid(0,getmdnpcname("スキア・ネリウス#02")),"スキア : ネリウス";
	unittalk getnpcid(0,getmdnpcname("スピーカ・ネリウス#01")),"スピーカ : ネリウス";
	end;
OnTimer12000:
	unittalk getnpcid(0,getmdnpcname("アイゼン・アノ#01")),"アイゼン・アノ : バルター";
	unittalk getnpcid(0,getmdnpcname("イアン・バルター#01")),"イアン : バルター";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ルヴィエル・ウィグナー#01")),"ルヴィエル : ウィグナー";
	unittalk getnpcid(0,getmdnpcname("ユルゲン・ウィグナー#01")),"ユルゲン : ウィグナー";
	unittalk getnpcid(0,getmdnpcname("アイザック・ウィグナー#01")),"アイザック : ウィグナー";
	unittalk getnpcid(0,getmdnpcname("カトリン・ウィグナー#01")),"カトリン : ウィグナー";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("キャサリン・ゲオルグ#01")),"キャサリン : ゲオルグ";
	unittalk getnpcid(0,getmdnpcname("エルンスト・ゲオルグ#01")),"エルンスト : ゲオルグ";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ポー・リハルト#01")),"ポー : リハルト";
	end;
OnTimer24000:
	unittalk getnpcid(0,getmdnpcname("マクシーミリアン#01")),"マクシーミリアン : レベンブルグ";
	unittalk getnpcid(0,getmdnpcname("ヴォルフ・レベンブルグ#01")),"ヴォルフ : レベンブルグ";
	unittalk getnpcid(0,getmdnpcname("ヘルムト・レベンブルグ#01")),"ヘルムト : レベンブルグ";
	unittalk getnpcid(0,getmdnpcname("アグネス・レベンブルグ#01")),"アグネス : レベンブルグ";
	end;
OnTimer27000:
	announce "クロネカー : ルーンミッドガッツを支える七王家の意を受け継いで", 0x9, 0x00ff99;
	end;
OnTimer30000:
	announce "クロネカー : ここに新しい代理者が選定された。", 0x9, 0x00ff99;
	end;
OnTimer33000:
	announce "クロネカー : 大地の栄光と祝福がそなたと共にあることを祈る。", 0x9, 0x00ff99;
	end;
OnTimer36000:
	unittalk getnpcid(0,getmdnpcname("フリードリヒ・ハイネン#01")),"フリードリヒ : 存在するすべてのものに許可された根源の力と";
	unittalk getnpcid(0,getmdnpcname("ニーヒル・ハイネン#02")),"ニーヒル : 存在するすべてのものに許可された根源の力と";
	end;
OnTimer39000:
	unittalk getnpcid(0,getmdnpcname("キャサリン・ゲオルグ#01")),"キャサリン : いかなる時も退かず、更なる一歩踏み出し、敵を制圧する勇気と";
	unittalk getnpcid(0,getmdnpcname("エルンスト・ゲオルグ#01")),"エルンスト : いかなる時も退かず、更なる一歩踏み出し、敵を制圧する勇気と";
	end;
OnTimer42000:
	unittalk getnpcid(0,getmdnpcname("スキア・ネリウス#02")),"スキア : 世の中にあるすべてを包み込むことができる寛大な心と";
	unittalk getnpcid(0,getmdnpcname("スピーカ・ネリウス#01")),"スピーカ : 世の中にあるすべてを包み込むことができる寛大な心と";
	end;
OnTimer45000:
	unittalk getnpcid(0,getmdnpcname("ポー・リハルト#01")),"ポー : 懐に抱いた全てを守れる強靭な覚悟と";
	end;
OnTimer48000:
	unittalk getnpcid(0,getmdnpcname("アイゼン・アノ#01")),"アイゼン・アノ : 何が起こっても正義と信念を曲げない誇りと";
	unittalk getnpcid(0,getmdnpcname("イアン・バルター#01")),"イアン : 何が起こっても正義と信念を曲げない誇りと";
	end;
OnTimer51000:
	unittalk getnpcid(0,getmdnpcname("マクシーミリアン#01")),"マクシーミリアン : 自身より他者を守り、慈しむ美徳と";
	unittalk getnpcid(0,getmdnpcname("ヴォルフ・レベンブルグ#01")),"ヴォルフ : 自身より他者を守り、慈しむ美徳と";
	unittalk getnpcid(0,getmdnpcname("ヘルムト・レベンブルグ#01")),"ヘルムト : 自身より他者を守り、慈しむ美徳と";
	unittalk getnpcid(0,getmdnpcname("アグネス・レベンブルグ#01")),"アグネス : 自身より他者を守り、慈しむ美徳と";
	end;
OnTimer54000:
	unittalk getnpcid(0,getmdnpcname("ルヴィエル・ウィグナー#01")),"ルヴィエル : 真実を見通す事ができる知恵と曇りなき瞳を";
	unittalk getnpcid(0,getmdnpcname("ユルゲン・ウィグナー#01")),"ユルゲン : 真実を見通す事ができる知恵と曇りなき瞳を";
	unittalk getnpcid(0,getmdnpcname("アイザック・ウィグナー#01")),"アイザック : 真実を見通す事ができる知恵と曇りなき瞳を";
	unittalk getnpcid(0,getmdnpcname("カトリン・ウィグナー#01")),"カトリン : 真実を見通す事ができる知恵と曇りなき瞳を";
	end;
OnTimer57000:
	announce "クロネカー : 七王家の名の元に、新しい王をここに……", 0x9, 0x00ff99;
	end;
OnTimer60000:
	announce "ピーター : うあっっ!!　お、おまえは…･･･!?", 0x9, 0x00ff99, 0x0190, 24, 0, 0;
	end;
OnTimer63000:
	announce "？？？ : ギャハハッッ!!　ピーター王を討ち取ったり～～!!", 0x9, 0x00ff99, 0x0190, 24, 0, 0;
	end;
OnTimer63500:
	misceffect 563,"ピーター・ハイネン#01";
	hideonnpc getmdnpcname("ピーター・ハイネン#01");
	hideoffnpc getmdnpcname("倒れたピーター#02");
	end;
OnTimer65000:
	announce "クロネカー : ピーター!?", 0x9, 0x00ff99;
	end;
OnTimer65500:
	hideonnpc getmdnpcname("クロネカー・ハイネン#01");
	hideoffnpc getmdnpcname("クロネカー・ハイネン#02");
	end;
OnTimer66000:
	hideoffnpc getmdnpcname("侵入者#hunter01");
	announce "？？？ : 七王家の皆様おそろいで！　貴方が噂の大賢者グランツ大公ですね！", 0x9, 0x00ff99;
	end;
OnTimer69000:
	announce "クロネカー : 貴様、何者だッ！　何の目的で、どうやってここに入ってきた!?", 0x9, 0x00ff99;
	end;
OnTimer73000:
	announce "？？？ : いやぁ……ひどいじゃないですか～！我々を騙すなんて～～!!", 0x9, 0x00ff99;
	end;
OnTimer76000:
	announce "？？？ : こちらにとても貴重な物が隠してあると聞きつけてせっかくやってきたのに……!", 0x9, 0x00ff99;
	end;
OnTimer79000:
	announce "？？？ : ……これ、偽物じゃないですか!!", 0x9, 0x00ff99;
	misceffect 12,getmdnpcname("クロネカー・ハイネン#02");
	end;
OnTimer79500:
	misceffect 58,getmdnpcname("侵入者#hunter01");
	misceffect 200,getmdnpcname("侵入者#hunter01");
	end;
OnTimer81500:
	announce "？？？ : このユミルの心臓は偽物!!　ひどいひどい!!　七王家は嘘をついていたんだああ!!", 0x9, 0x00ff99;
	end;
OnTimer84500:
	announce "？？？ : お前らがいうユミルの心臓！　王位継承の儀式で、この場所の封印が解放されるって聞いたから来たのに。", 0x9, 0x00ff99;
	end;
OnTimer87500:
	announce "？？？ : 偽物偽物偽物偽物偽物!!ユミルの心臓が偽物でしたーー!!", 0x9, 0x00ff99;
	end;
OnTimer91000:
	announce "クロネカー : ……なんのことだ！", 0x9, 0x00ff99;
	end;
OnTimer93500:
	announce "？？？ : おや？　知らないとおっしゃいますか？　御冗談を。", 0x9, 0x00ff99;
	end;
OnTimer96500:
	announce "？？？ : それが何かを知ってるからこそ、こんな地下の隠れた場所で儀式をしているのでしょう？", 0x9, 0x00ff99;
	end;
OnTimer99500:
	announce "クロネカー : ……！", 0x9, 0x00ff99;
	end;
OnTimer101500:
	announce "？？？ : そんなに睨まないでくださいよ～。私も無駄足だったとガックリ、肩を落としている所です。", 0x9, 0x00ff99;
	end;
OnTimer104500:
	announce "？？？ : だから～～、代わりに～、ピーター王の心臓を持っていくことにしました!!", 0x9, 0x00ff99;
	end;
OnTimer107500:
	announce "？？？ : 別にいいでしょ～？　爺さんたちが談合して勝手に決めた王様なんだもん！", 0x9, 0x00ff99;
	end;
OnTimer110500:
	announce "？？？ : 七王家の利益のために～、決められた偽者の王様～！", 0x9, 0x00ff99;
	end;
OnTimer113500:
	announce "？？？ : ルーンミッドガッツ王国は偽物だらけ～～っ!!", 0x9, 0x00ff99;
	end;
OnTimer116500:
	announce "？？？ : 偽物こそがこの国の真実！　図星だからお前らは何も反論できない～～!!　", 0x9, 0x00ff99;
	end;
OnTimer119500:
	announce "クロネカー : くっ！　おのれ～～!!", 0x9, 0x00ff99;
	end;
OnTimer122500:
	announce "？？？ : ああ～ッ!!　何だお前！　一人でノコノコと!!", 0x9, 0x00ff99;
	hideonnpc getmdnpcname("ニーヒル・ハイネン#02");
	hideoffnpc getmdnpcname("ニーヒル・ハイネン#03");
	end;
OnTimer125500:
	announce "ニーヒル : 黙れ!!!", 0x9, 0x00ff99, 0x0190, 24, 0, 0;
	misceffect 1,getmdnpcname("侵入者#hunter01");
	end;
OnTimer128500:
	announce "クロネカー : ニーヒル!!", 0x9, 0x00ff99;
	end;
OnTimer131500:
	announce "ニーヒル : 祖父を、ハイネン家を……", 0x9, 0x00ff99, 0x0190, 24, 0, 0;
	end;
OnTimer134500:
	announce "ニーヒル : ルーンミッドガッツ王国を愚弄するのは、私が許さない！", 0x9, 0x00ff99, 0x0190, 24, 0, 0;
	end;
OnTimer137500:
	announce "？？？ : てめぇ……俺をぶちやがったな～～～ッ!!　もう許さねぇ!!　全員の心臓を切り抜いてやる!!", 0x9, 0x00ff99;
	misceffect 220,getmdnpcname("侵入者#hunter01");
	misceffect 55,getmdnpcname("侵入者#hunter01");
	misceffect 563,getmdnpcname("ピーター・ハイネン#01");
	misceffect 90,getmdnpcname("クロネカー・ハイネン#02");
	misceffect 90,getmdnpcname("ルヴィエル・ウィグナー#01");
	misceffect 90,getmdnpcname("キャサリン・ゲオルグ#01");
	hideonnpc getmdnpcname("イアン・バルター#01");
	hideonnpc getmdnpcname("ルヴィエル・ウィグナー#01");
	hideonnpc getmdnpcname("ユルゲン・ウィグナー#01");
	hideonnpc getmdnpcname("キャサリン・ゲオルグ#01");
	hideoffnpc getmdnpcname("イアン・バルター#02");
	hideoffnpc getmdnpcname("ルヴィエル・ウィグナー#02");
	hideoffnpc getmdnpcname("ユルゲン・ウィグナー#02");
	hideoffnpc getmdnpcname("アイザック・ウィグナー#02");
	hideoffnpc getmdnpcname("カトリン・ウィグナー#02");
	hideoffnpc getmdnpcname("キャサリン・ゲオルグ#02");
	misceffect 90,getmdnpcname("マクシーミリアン#01");
	hideonnpc getmdnpcname("エルンスト・ゲオルグ#01");
	hideonnpc getmdnpcname("マクシーミリアン#01");
	hideonnpc getmdnpcname("ヴォルフ・レベンブルグ#01");
	hideonnpc getmdnpcname("アグネス・レベンブルグ#01");
	hideoffnpc getmdnpcname("エルンスト・ゲオルグ#02");
	hideoffnpc getmdnpcname("マクシーミリアン#02");
	hideoffnpc getmdnpcname("ヴォルフ・レベンブルグ#02");
	hideoffnpc getmdnpcname("アグネス・レベンブルグ#02");
	misceffect 90,getmdnpcname("アグネス・レベンブルグ#02");
	end;
OnTimer138000:
	announce "？？？ : ギャハハハハッッ!!　私の部下どもと最後に楽しい時間をお過ごしくださいね～!!", 0x9, 0x00ff99;
	hideonnpc getmdnpcname("侵入者#hunter01");
	hideoffnpc getmdnpcname("侵入者#hunter02");
	hideoffnpc getmdnpcname("侵入者#hunter03");
	hideoffnpc getmdnpcname("侵入者#hunter04");
	hideoffnpc getmdnpcname("侵入者#hunter05");
	hideoffnpc getmdnpcname("侵入者#hunter06");
	end;
OnTimer138500:
	set .phase,2;
	hideonnpc getmdnpcname("アイゼン・アノ#01");
	hideonnpc getmdnpcname("スキア・ネリウス#02");
	hideonnpc getmdnpcname("ニーヒル・ハイネン#01");
	hideonnpc getmdnpcname("フリードリヒ・ハイネン#01");
	hideonnpc getmdnpcname("スピーカ・ネリウス#01");
	hideonnpc getmdnpcname("ヘルムト・レベンブルグ#01");
	hideonnpc getmdnpcname("ポー・リハルト#01");
	hideonnpc getmdnpcname("アイザック・ウィグナー#01");
	hideonnpc getmdnpcname("カトリン・ウィグナー#01");
	hideoffnpc getmdnpcname("アイゼン・アノ#02");
	hideoffnpc getmdnpcname("スキア・ネリウス#03");
	hideoffnpc getmdnpcname("ニーヒル・ハイネン#03");
	hideoffnpc getmdnpcname("フリードリヒ・ハイネン#02");
	hideoffnpc getmdnpcname("スピーカ・ネリウス#02");
	hideoffnpc getmdnpcname("ポー・リハルト#02");
	hideoffnpc getmdnpcname("ヘルムト・レベンブルグ#02");
	donpcevent getmdnpcname("callmon#royal")+ "::OnSummon";
	initnpctimer getmdnpcname("侵入者#hunter02");
	initnpctimer getmdnpcname("侵入者#hunter03");
	initnpctimer getmdnpcname("侵入者#hunter04");
	initnpctimer getmdnpcname("侵入者#hunter05");
	initnpctimer getmdnpcname("侵入者#hunter06");
	stopnpctimer;
	end;
}

2@mir.gat,1,0,0		script	callmon#royal	-1,{
	end;
OnSummon:
	set 'count,3;
	monster getmdmapname("2@mir.gat"),98,73,"怪しい侵入者#1",3454,1,getmdnpcname("callmon#royal")+"::OnKilled1";
	monster getmdmapname("2@mir.gat"),107,73,"怪しい侵入者#2",3454,1,getmdnpcname("callmon#royal")+"::OnKilled2";
	monster getmdmapname("2@mir.gat"),101,83,"怪しい侵入者#3",3454,1,getmdnpcname("callmon#royal")+"::OnKilled3";
	end;
OnKilled1:
	misceffect 276,getmdnpcname("侵入者#hunter04");
	hideonnpc getmdnpcname("侵入者#hunter04");
	stopnpctimer getmdnpcname("侵入者#hunter04");
	set 'count,'count-1;
	if('count > 0)
		end;
	callsub L_Clear;
	end;
OnKilled2:
	misceffect 276,getmdnpcname("侵入者#hunter03");
	hideonnpc getmdnpcname("侵入者#hunter03");
	stopnpctimer getmdnpcname("侵入者#hunter03");
	set 'count,'count-1;
	if('count > 0)
		end;
	callsub L_Clear;
	end;
OnKilled3:
	misceffect 276,getmdnpcname("侵入者#hunter02");
	hideonnpc getmdnpcname("侵入者#hunter02");
	stopnpctimer getmdnpcname("侵入者#hunter02");
	set 'count,'count-1;
	if('count > 0)
		end;
	callsub L_Clear;
	end;
L_Clear:
	set 'flag,1;
	set .phase,3;
	stopnpctimer getmdnpcname("侵入者#hunter02");
	stopnpctimer getmdnpcname("侵入者#hunter03");
	stopnpctimer getmdnpcname("侵入者#hunter04");
	stopnpctimer getmdnpcname("侵入者#hunter05");
	stopnpctimer getmdnpcname("侵入者#hunter06");
	announce "？？？ : 作戦班、撤収するぞ!!", 0x9, 0xdddddd;
	misceffect 276,getmdnpcname("侵入者#hunter02");
	hideonnpc getmdnpcname("侵入者#hunter02");
	misceffect 276,getmdnpcname("侵入者#hunter03");
	hideonnpc getmdnpcname("侵入者#hunter03");
	misceffect 276,getmdnpcname("侵入者#hunter04");
	hideonnpc getmdnpcname("侵入者#hunter04");
	misceffect 276,getmdnpcname("侵入者#hunter05");
	hideonnpc getmdnpcname("侵入者#hunter05");
	misceffect 276,getmdnpcname("侵入者#hunter06");
	hideonnpc getmdnpcname("侵入者#hunter06");
	return;
}

2@mir.gat,102,97,3	script	侵入者#hunter01				3454,{}

2@mir.gat,110,82,3	script	侵入者#hunter02				3454,{
	end;
OnTimer1000:
	misceffect 81;
	end;
OnTimer2000:
	misceffect 153,getmdnpcname("アイゼン・アノ#02");
	end;
OnTimer4000:
	misceffect 245;
	end;
OnTimer5000:
	unittalk "？？？ : させるか！";
	misceffect 266,getmdnpcname("アイゼン・アノ#02");
	end;
OnTimer7000:
	misceffect 246;
	end;
OnTimer8000:
	misceffect 273,getmdnpcname("アイゼン・アノ#02");
	end;
OnTimer10000:
	misceffect 81;
	end;
OnTimer11000:
	misceffect 266,getmdnpcname("アイゼン・アノ#02");
	unittalk getnpcid(0,getmdnpcname("アイゼン・アノ#02")),"アイゼン・アノ : クッ……！";
	initnpctimer;
	end;

}
2@mir.gat,111,78,3	script	侵入者#hunter03				3454,{
	end;
OnTimer1000:
	misceffect 182;
	end;
OnTimer2000:
	misceffect 266,getmdnpcname("スキア・ネリウス#03");
	end;
OnTimer4000:
	misceffect 4;
	end;
OnTimer5000:
	misceffect 5,getmdnpcname("スキア・ネリウス#03");
	end;
OnTimer7000:
	misceffect 1;
	end;
OnTimer8000:
	unittalk "？？？ : させるか！";
	misceffect 0,getmdnpcname("スキア・ネリウス#03");
	end;
OnTimer10500:
	misceffect 245;
	end;
OnTimer11500:
	misceffect 0,getmdnpcname("スキア・ネリウス#03");
	initnpctimer;
	end;
}
2@mir.gat,96,83,5	script	侵入者#hunter04				3454,{
	end;
OnTimer1000:
	misceffect 182;
	end;
OnTimer2000:
	misceffect 266,getmdnpcname("フリードリヒ・ハイネン#02");
	end;
OnTimer3500:
	misceffect 4;
	end;
OnTimer4500:
	misceffect 5,getmdnpcname("フリードリヒ・ハイネン#02");
	unittalk "？？？ : ふん!!";
	end;
OnTimer7000:
	misceffect 1;
	end;
OnTimer8000:
	misceffect 0,getmdnpcname("フリードリヒ・ハイネン#02");
	end;
OnTimer10000:
	misceffect 245;
	end;
OnTimer11000:
	misceffect 131,getmdnpcname("フリードリヒ・ハイネン#02");
	unittalk getnpcid(0,getmdnpcname("フリードリヒ・ハイネン#02")),"フリードリヒ : ……こいつら、どこから入ってきたんだ!?";
	initnpctimer;
	end;
}
2@mir.gat,105,68,7	script	侵入者#hunter05				3454,{
	end;
OnTimer1000:
	misceffect 182;
	end;
OnTimer2000:
	misceffect 266,getmdnpcname("ヘルムト・レベンブルグ#02");
	end;
OnTimer4000:
	unittalk "？？？ : おとなしく倒れろ！";
	misceffect 4;
	end;
OnTimer4500:
	unittalk getnpcid(0,getmdnpcname("ヘルムト・レベンブルグ#02")),"ヘルムト : それはこちらの台詞だ！";
	misceffect 5,getmdnpcname("ヘルムト・レベンブルグ#02");
	end;
OnTimer7000:
	misceffect 1;
	end;
OnTimer8000:
	misceffect 0,getmdnpcname("ヘルムト・レベンブルグ#02");
	end;
OnTimer10000:
	misceffect 245;
	end;
OnTimer11000:
	misceffect 131,getmdnpcname("ヘルムト・レベンブルグ#02");
	unittalk getnpcid(0,getmdnpcname("ヘルムト・レベンブルグ#02")),"ヘルムト : うおらあああ!!!!";
	initnpctimer;
	end;

}
2@mir.gat,92,77,7	script	侵入者#hunter06				3454,{
	end;
OnTimer1000:
	misceffect 180;
	end;
OnTimer2000:
	misceffect 266,getmdnpcname("ポー・リハルト#02");
	end;
OnTimer4000:
	unittalk getnpcid(0,getmdnpcname("ポー・リハルト#02")),"ポー : まったく。こういう面白さは好まないよ。";
	misceffect 29;
	end;
OnTimer5000:
	misceffect 5,getmdnpcname("ポー・リハルト#02");
	end;
OnTimer7000:
	misceffect 186;
	end;
OnTimer8000:
	misceffect 0,getmdnpcname("ポー・リハルト#02");
	end;
OnTimer10000:
	misceffect 32;
	end;
OnTimer12000:
	unittalk getnpcid(0,getmdnpcname("ポー・リハルト#02")),"ポー : この場から出て行ってくれないかな！";
	initnpctimer;
	end;
}

2@mir.gat,107,77,0	script	#royal_evt02	139,1,1,{
	end;
OnTouch:
	stopnpctimer;
	donpcevent getmdnpcname("クロネカー・ハイネン#01")+ "::OnStart";
	hideonnpc;
	end;
OnTimer5000:
	initnpctimer;
	misceffect 222;
	end;
}

2@mir.gat,97,80,7	script	フリードリヒ・ハイネン#01	10120,{
	unittalk "フリードリヒ : ……静かに。";
	end;
}
2@mir.gat,100,80,7	script	ニーヒル・ハイネン#02		10114,{}

2@mir.gat,97,77,7	script	スキア・ネリウス#02			10116,{}
2@mir.gat,100,77,7	script	スピーカ・ネリウス#01		10115,{}

2@mir.gat,97,68,7	script	アイザック・ウィグナー#01	10126,{}
2@mir.gat,100,68,7	script	カトリン・ウィグナー#01		10125,{}
2@mir.gat,97,71,7	script	ルヴィエル・ウィグナー#01	10132,{}
2@mir.gat,100,71,7	script	ユルゲン・ウィグナー#01		989,{}

2@mir.gat,103,80,2	script	キャサリン・ゲオルグ#01		10121,{}
2@mir.gat,106,80,2	script	エルンスト・ゲオルグ#01		985,{}

2@mir.gat,103,77,2	script	ポー・リハルト#01			993,{}

2@mir.gat,103,74,2	script	マクシーミリアン#01			10133,{}
2@mir.gat,106,74,2	script	ヴォルフ・レベンブルグ#01	10128,{}
2@mir.gat,103,71,2	script	ヘルムト・レベンブルグ#01	10127,{}
2@mir.gat,106,71,2	script	アグネス・レベンブルグ#01	10130,{}

2@mir.gat,97,74,7	script	アイゼン・アノ#01			983,{}
2@mir.gat,100,74,7	script	イアン・バルター#01			55,{}

2@mir.gat,99,77,2	script	エルンスト・ゲオルグ#02		985,{
	if(.phase < 3)
		end;
	mes "[エルンスト]";
	mes "こっちへ！　早く！";
	close2;
	hideonnpc getmdnpcname("エルンスト・ゲオルグ#02");
	hideonnpc getmdnpcname("キャサリン・ゲオルグ#02");
	end;
}
2@mir.gat,103,17,2	script	エルンスト・ゲオルグ#03		985,{
	mes "[エルンスト]";
	mes "……";
	mes "ハイネン家のニーヒル。";
	mes "大したものだ。";
	next;
	mes "[エルンスト]";
	mes "ピーター王が刺され、";
	mes "この国を偽物と否定され、";
	mes "誰もが動くことができなかった。";
	next;
	mes "[エルンスト]";
	mes "七王家に、";
	mes "まだあのような男が……";
	mes "面白いな。";
	close;
}

2@mir.gat,95,74,4	script	アイザック・ウィグナー#02	10126,{
	if(.phase < 3) {
		unittalk "アイザック : 頑張って下さい！";
		npcskillsupport 34,10;
		sc_start 10,240000,10;
	}
	end;
}
2@mir.gat,97,75,3	script	カトリン・ウィグナー#02		10125,{}
2@mir.gat,98,72,2	script	ルヴィエル・ウィグナー#02	10132,{}
2@mir.gat,96,72,3	script	ユルゲン・ウィグナー#02		989,{
	if(.phase < 3) {
		unittalk "ユルゲン : よろしくお願いします！";
		npcskillsupport 29,10;
		sc_start 12,240000,10;
		end;
	}
	mes "[ユルゲン]";
	mes "みんな大丈夫ですか？";
	mes "ひとまずここから離れましょう。";
	close2;
	hideonnpc getmdnpcname("ルヴィエル・ウィグナー#02");
	hideonnpc getmdnpcname("ユルゲン・ウィグナー#02");
	hideonnpc getmdnpcname("アイザック・ウィグナー#02");
	hideonnpc getmdnpcname("カトリン・ウィグナー#02");
	end;
}
2@mir.gat,106,69,2	script	ヘルムト・レベンブルグ#02	10127,{
	if(.phase < 3) {
		unittalk "ヘルムト : ふん！";
		end;
	}
	mes "[ヘルムト]";
	mes "全員、無事だな！";
	mes "　";
	mes "……俺たちは先に戻らせてもらうぞ。";
	mes "家族の顔色が悪いんでな。";
	close2;
	hideonnpc getmdnpcname("ヘルムト・レベンブルグ#02");
	hideonnpc getmdnpcname("アグネス・レベンブルグ#02");
	hideonnpc getmdnpcname("ヴォルフ・レベンブルグ#02");
	hideonnpc getmdnpcname("マクシーミリアン#02");
	end;
}
2@mir.gat,106,72,2	script	マクシーミリアン#02			10133,{}
2@mir.gat,108,72,6	script	ヴォルフ・レベンブルグ#02	10128,{}
2@mir.gat,107,73,2	script	アグネス・レベンブルグ#02	10130,{
	if(.phase < 3) {
		unittalk "アグネス : 冒険者様！　お気を付けて！";
	}
	end;
}

2@mir.gat,100,75,2	script	キャサリン・ゲオルグ#02		10121,{
	if(.phase < 3) {
		unittalk "キャサリン : わたくしの祈りがそなたの力になることを！";
		npcskillsupport 28,1748;
		heal 1748,0;
	}
	end;
}
2@mir.gat,108,76,6	script	スピーカ・ネリウス#02		10115,{
	if(.phase < 3) {
		unittalk "スピーカ : ……スキア……";
	}
	end;
}
2@mir.gat,109,78,6	script	スキア・ネリウス#03			10116,{
	if(.phase < 3) {
		unittalk "スキア : ……どこからこんな奴らが現れたのでしょうか?!";
		end;
	}
	mes "[スキア]";
	mes "ふう、まずはここから離れましょう。";
	mes "スピーカ！　行こう！";
	close2;
	hideonnpc getmdnpcname("スキア・ネリウス#03");
	hideonnpc getmdnpcname("スピーカ・ネリウス#02");
	end;
}
2@mir.gat,94,78,4	script	ポー・リハルト#02			993,{
	if(.phase < 3) {
		unittalk "ポー : ……ははっ、まさかここで戦うことになるとは！";
		end;
	}
	mes "[ポー]";
	mes "私も戻るとしよう。";
	close2;
	hideonnpc getmdnpcname("ポー・リハルト#02");
	end;
}
2@mir.gat,107,80,0	script	イアン・バルター#02			55,{}
2@mir.gat,108,82,6	script	アイゼン・アノ#02			983,{
	if(.phase < 3) {
		unittalk "アイゼン・アノ : 雑談なんかする余裕がありません！";
		end;
	}
	mes "[アイゼン・アノ]";
	mes "なんということだ……";
	mes "とりあえず";
	mes "一旦、ここから出ましょう。";
	next;
	mes "[アイゼン・アノ]";
	mes "みんな無事で……";
	close2;
	hideonnpc getmdnpcname("アイゼン・アノ#02");
	hideonnpc getmdnpcname("イアン・バルター#02");
	end;
}
2@mir.gat,97,82,1	script	フリードリヒ・ハイネン#02	10120,{
	if(.phase < 3) {
		unittalk "フリードリヒ : 他の者たちを頼む。";
		end;
	}
	mes "[フリードリヒ]";
	mes "……早く負傷者を連れてここから出ろ。";
	unittalk getnpcid(0,getmdnpcname("フリードリヒ・ハイネン#02")),"フリードリヒ : ……早く負傷者を連れてここから出ろ。";
	close2;
	hideonnpc getmdnpcname("エルンスト・ゲオルグ#02");
	hideonnpc getmdnpcname("キャサリン・ゲオルグ#02");
	hideonnpc getmdnpcname("ルヴィエル・ウィグナー#02");
	hideonnpc getmdnpcname("ユルゲン・ウィグナー#02");
	hideonnpc getmdnpcname("アイザック・ウィグナー#02");
	hideonnpc getmdnpcname("カトリン・ウィグナー#02");
	hideonnpc getmdnpcname("ヘルムト・レベンブルグ#02");
	hideonnpc getmdnpcname("アグネス・レベンブルグ#02");
	hideonnpc getmdnpcname("ヴォルフ・レベンブルグ#02");
	hideonnpc getmdnpcname("マクシーミリアン#02");
	hideonnpc getmdnpcname("スキア・ネリウス#03");
	hideonnpc getmdnpcname("スピーカ・ネリウス#02");
	hideonnpc getmdnpcname("ポー・リハルト#02");
	hideonnpc getmdnpcname("アイゼン・アノ#02");
	hideonnpc getmdnpcname("イアン・バルター#02");
	end;
}
2@mir.gat,101,93,7	script	クロネカー・ハイネン#02		10119,{
	if(EP16_1QUE == 9) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "ピーターの傷が思ったより深い。";
		mes "一刻も早く手当をせねば……";
		next;
		mes "[クロネカー]";
		mes "お主も速やかに退出してくれ。";
		mes "出入口は開いておる。";
		mes "しばらく一人にして欲しい……";
		close2;
		cutin "ep16_kronecker_granz_heine",255;
		end;
	}
	if(.phase == 2) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "ピーターの傷が思ったより深い。";
		mes "一刻も早く手当をせねば……";
		close2;
		cutin "ep16_kronecker_granz_heine",255;
		end;
	}
	if(.phase == 3) {
		cutin "ep16_kronecker_granz_heine",2;
		mes "[クロネカー]";
		mes "…";
		mes "…^4d4dffテラグローリア^000000が消えた……";
		next;
		menu "テラグローリア？",-;
		mes "[クロネカー]";
		mes "古くより、";
		mes "ルーンミッドガッツ王室に伝わる王冠だ。";
		mes "王室にとって特別なものなのだ。";
		next;
		mes "[クロネカー]";
		mes "まさか……！";
		mes "先ほどの奴らが持ち出したのか……!?";
		mes "なんという事だ……!!";
		next;
		mes "[クロネカー]";
		mes "ありえない……";
		mes "ここに何があるのか、七王家以外は";
		mes "決して知るはずがないのだ！";
		next;
		mes "[クロネカー]";
		mes "……まさか……";
		mes "いや、そんなはずは……";
		next;
		mes "[クロネカー]";
		mes "一旦、ここから退出してくれ……";
		mes "私は少し調べる事がある。";
		mes "もうじきピーターの救護に呼んだ";
		mes "兵士達も来るだろう。";
		next;
		mes "[クロネカー]";
		mes "まだ残っている者たちは";
		mes "周辺の負傷者たちをつれて";
		mes "速やかに退出するように。";
		mes "当分の間、儀式の部屋は封印する！";
		setquest 7693;
		delquest 7692;
		set EP16_1QUE,9;
		hideonnpc getmdnpcname("フリードリヒ・ハイネン#02");
		hideonnpc getmdnpcname("ニーヒル・ハイネン#03");
		hideonnpc getmdnpcname("エルンスト・ゲオルグ#02");
		hideonnpc getmdnpcname("キャサリン・ゲオルグ#02");
		hideonnpc getmdnpcname("ルヴィエル・ウィグナー#02");
		hideonnpc getmdnpcname("ユルゲン・ウィグナー#02");
		hideonnpc getmdnpcname("アイザック・ウィグナー#02");
		hideonnpc getmdnpcname("カトリン・ウィグナー#02");
		hideonnpc getmdnpcname("ヘルムト・レベンブルグ#02");
		hideonnpc getmdnpcname("アグネス・レベンブルグ#02");
		hideonnpc getmdnpcname("ヴォルフ・レベンブルグ#02");
		hideonnpc getmdnpcname("マクシーミリアン#02");
		hideonnpc getmdnpcname("スキア・ネリウス#03");
		hideonnpc getmdnpcname("スピーカ・ネリウス#02");
		hideonnpc getmdnpcname("ポー・リハルト#02");
		hideonnpc getmdnpcname("アイゼン・アノ#02");
		hideonnpc getmdnpcname("イアン・バルター#02");
		hideoffnpc getmdnpcname("to_prt_lib");
		hideoffnpc getmdnpcname("エルンスト・ゲオルグ#03");
		close2;
		cutin "ep16_kronecker_granz_heine",255;
		end;
	}
	end;
}
2@mir.gat,101,94,0	script	ピーター・ハイネン#01		987,{}
2@mir.gat,101,95,3	script	倒れたピーター#02			10117,{}
2@mir.gat,103,95,2	script	ニーヒル・ハイネン#03		10114,{
	if(.phase < 3) {
		end;
	}
	mes "[ニーヒル]";
	mes "なんという事だ……";
	close;
}
