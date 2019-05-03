//= Auriga Script ==============================================================
// Ragnarok Online Wolfchev's Laboratory Script	by refis
//==============================================================================

lhz_dun04.gat,151,276,3	script	研究員#memo	865,{
	switch(LHZ_6QUE) {
	case 7:
		mes "‐研究室の扉の前で";
		mes "　ボルセブは混乱している‐";
		next;
		mes "[ボルセブ]";
		mes "キヒ……";
		mes "なぜだァ？　なぜ実験体が";
		mes "ここまで入ってこれる!?";
		mes "……まさか、あのボタンで";
		mes "暴走したのか!?";
		next;
		menu "ボルセブ!!",-;
		mes "[ボルセブ]";
		mes "キヒッ!?";
		mes "なななな、なんだ!?";
		next;
		menu "あのボタンについて問い詰める",-;
		mes "[ボルセブ]";
		mes "レ、レッケンベルから渡された";
		mes "非常ボタンだ。";
		mes "邪魔者を排除するときに";
		mes "押すように言われて……。";
		mes "……俺も襲われるなんて……";
		mes "キヒ、キヒヒ……";
		next;
		mes "[ボルセブ]";
		mes "そそそそれよりも！　システムが";
		mes "暴走したとすると、^46B951コア実験体^000000も";
		mes "目覚めてしまった可能性がある！";
		next;
		menu "^46B951コア実験体？^000000",-;
		mes "[ボルセブ]";
		mes "こ、ここにいる実験体たちを";
		mes "作り出すためのもととなった";
		mes "^46B95113体の実験体^000000のことだ。";
		next;
		mes "[ボルセブ]";
		mes "13体のコア実験体は、";
		mes "一度に目覚める事ができないよう";
		mes "制限がかかっているが……。";
		mes "1体1体が非常に強力だ。";
		next;
		mes "[ボルセブ]";
		mes "ここで動き回っている奴らとは";
		mes "比べものにならないほどの";
		mes "ぜ、絶大な力を持っている……。";
		next;
		mes "[ボルセブ]";
		mes "おおおおい、お前！";
		mes "お、お、俺は暴走した原因を";
		mes "調べなくてはいけない。";
		mes "そのためには一番奥の";
		mes "研究室まで行く必要がある！";
		next;
		mes "[ボルセブ]";
		mes "だがその一番奥の研究室というのが、";
		mes "^46B951コア実験体^000000がいる場所なんだ。";
		mes "だから、そそそれを排除したい。";
		next;
		mes "[ボルセブ]";
		mes "研究室に入れるようにしてやるから、";
		mes "^46B951コア実験体^000000を排除してくれ！";
		next;
		menu "断る",-;
		mes "[ボルセブ]";
		mes "いや！　いやいやいや！";
		mes "コア実験体が研究室の外に出たら";
		mes "大変なことになるぞォ？";
		mes "な？　止めたいだろ？";
		mes "な？　な？";
		next;
		menu "やむを得ず引き受ける",-;
		mes "[ボルセブ]";
		mes "キヒッ……";
		mes "俺の研究室の入口は、";
		mes "おおお俺にしか開けられないからな。";
		mes "よぉぉし、入れるように手配しよう。";
		next;
		mes "[ボルセブ]";
		mes "13体のコア実験体のうち、";
		mes "どれが目覚めているかを";
		mes "知ることはできない。";
		mes "すべて倒すには、何度も通って";
		mes "貰うことになる。";
		next;
		mes "[ボルセブ]";
		mes "だが、すべてのコア実験体を1度でも";
		mes "倒せば、暴走は収まるだろう。";
		mes "そのようにプログラムされている";
		mes "からなァ。";
		next;
		mes "[ボルセブ]";
		mes "すべて倒したら、れれれ礼をして";
		mes "やらんでもないぞ！　キヒヒ……";
		delquest 5111;
		setquest 5113;
		setquest 5114;
		setquest 5115;
		setquest 5116;
		setquest 5117;
		setquest 5118;
		setquest 5119;
		setquest 5120;
		setquest 5121;
		setquest 5122;
		setquest 5123;
		setquest 5124;
		setquest 5125;
		setquest 5126;
		set LHZ_6QUE,8;
		next;
		mes "[ボルセブ]";
		mes "それから、研究室へは";
		mes "パーティーを組んでいなくては";
		mes "入れないぞォ？";
		mes "危険だからなァ……。";
		next;
		mes "[ボルセブ]";
		mes "じゅじゅじゅ準備が終わったら、";
		mes "俺に言ってくれ！";
		mes "キヒヒヒヒ……";
		close;
	case 8:
	case 11:
		for(set '@i,5113;'@i<5126;set '@i,'@i+1) {
			set '@total,'@total + ((checkquest('@i) & 0x4) == 0);
		}
		if('@total == 0) {
			mes "[ボルセブ]";
			mes "キヒヒヒヒ……";
			mes "すべてのコア実験体を";
			mes "倒したようだなァ？";
			next;
			mes "[ボルセブ]";
			mes "研究所に通って、";
			mes "俺にもわかったことがあるぞォ。";
			mes "キヒヒ！　聞きたいか？";
			next;
			mes "[ボルセブ]";
			mes "実験体たちはなァ！";
			mes "暴走していたんじゃない！";
			mes "非常ボタンが押されたら、";
			mes "手当り次第に攻撃するように";
			mes "設定されていた!!";
			mes "つまり……";
			next;
			mes "[ボルセブ]";
			mes "レレレレッケンベルはァァァ！";
			mes "キヒヒ！　何かあったら俺ごと";
			mes "邪魔者を消そうとしていたと";
			mes "いうことだ!!";
			mes "キーヒヒヒヒヒ!!";
			next;
			mes "[ボルセブ]";
			mes "アァァ？　どういうことだ？";
			mes "俺も邪魔者？";
			mes "邪魔者だっていうのかぁ!?";
			mes "キヒ、キヒヒヒ！";
			next;
			mes "[ボルセブ]";
			mes "キヒヒ……";
			mes "　";
			mes "俺は……裏切られたのか……。";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "…………";
			next;
			mes "[ボルセブ]";
			mes "ああぁ!?";
			mes "いいいいま今頃気づいたのかって";
			mes "ツラ！　ツラだなぁぁぁぁ!?";
			next;
			mes "[ボルセブ]";
			mes "レッケンベルはなぁ！";
			mes "レッケンベルだけは俺の実験を";
			mes "みみみ認めて!!";
			next;
			mes "[ボルセブ]";
			mes "キ、キヒ！";
			mes "キヒヒ！";
			mes "キーヒヒヒヒヒ！";
			next;
			mes "[ボルセブ]";
			mes "レッケンベルゥゥゥ!!";
			mes "俺を裏切ったこと";
			mes "か、必ずこここ後悔！";
			mes "後悔させてやる！";
			mes "キーヒヒヒヒヒ！";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "…………";
			next;
			mes "[ボルセブ]";
			mes "おお俺がレッケンベルのために";
			mes "してやった実験結果は";
			mes "すすすすべて破壊！　してやる！";
			mes "キヒヒ！　あいつらに何一つ";
			mes "残してやるものか！";
			next;
			mes "[ボルセブ]";
			mes "一番やっかいなコア実験体は";
			mes "お前が倒してくれたからなァ。";
			mes "キヒヒヒヒ！";
			next;
			mes "‐悲惨な実験の黒幕は";
			mes "　レッケンベル社だった。";
			mes "　コア実験体の暴走を阻止したことで、";
			mes "　いったんは危機を免れた‐";
			next;
			mes "‐しかし、ボルセブも捨て駒で";
			mes "　あった以上、別の場所で今も悲劇が";
			mes "　起きている可能性がある。";
			mes "　レッケンベル社の動きには";
			mes "　注意したほうがよさそうだ‐";
			next;
			mes "[ボルセブ]";
			mes "ああ、そうだ……";
			mes "コア実験体を排除した礼をやろう！";
			mes "以前俺がいた研究室に、物置代わりに";
			mes "使っていた炉がある。";
			mes "その中のガラクタを持っていけ！";
			next;
			mes "[ボルセブ]";
			mes "俺には必要ない物だしなァ。";
			mes "キヒヒ！";
			next;
			mes "[ボルセブ]";
			mes "レッケンベルへの復讐を";
			mes "手伝ってくれるなら、";
			mes "また来てくれてもいいぜ？";
			mes "キーヒヒヒヒ！";
			next;
			mes "‐レッケンベル本社（lhz_in01）の";
			mes "　ボルセブの旧研究室（座標:43, 114）";
			mes "　に行ってみよう‐";
			for(set '@i,5113;'@i<5126;set '@i,'@i+1) {
				delquest '@i;
			}
			chgquest 5111,72020;
			set LHZ_6QUE,9;
			close;
		}
		if(getonlinepartymember() < 1) {
			mes "[ボルセブ]";
			mes "一人で研究室にィ？";
			mes "研究室の警備システムは";
			mes "お前が思っているほど";
			mes "簡単ではなーーーい！";
			mes "キヒヒヒヒ！";
			next;
			mes "[ボルセブ]";
			mes "パーティーを組んでいなくては";
			mes "入れないぞォ？";
			mes "危険だからなァ……。";
			close;
		}
		mes "[ボルセブ]";
		mes "キヒヒ……";
		mes "用意はすべて終えたのか？";
		mes "お前がパーティーリーダーなら";
		mes "研究室の入口を開けよう。";
		next;
		mes "[ボルセブ]";
		mes "残りのコア実験体は";
		mes "あと^0000ff" +'@total+ "体^000000だぞォ！";
		next;
		switch(select("注意する事はないか？","コア実験体について","研究室に入る","研究室に入らない")) {
		case 1:
			mes "[ボルセブ]";
			mes "あぁ？　そうだなァ……";
			mes "研究室は4部屋あって、";
			mes "実験体のボスは、第4研究室にいる。";
			mes "いつもなら、普通にたどり着けるが、";
			mes "今は管理システムが非常時のシステムに";
			mes "切り替わっている可能性がある。";
			next;
			mes "[ボルセブ]";
			mes "俺が非常ボタンを";
			mes "押しちまったからなァ……";
			mes "キヒ、キヒヒヒ！";
			next;
			mes "[ボルセブ]";
			mes "非常時のシステムに切り替わって";
			mes "いた場合、警備システムが作動して";
			mes "侵入者を排除しようと襲いかかる。";
			mes "気をつけな？";
			next;
			mes "[ボルセブ]";
			mes "それから、第2研究室は";
			mes "有害なガスが通ったパイプが";
			mes "張り巡らされている。";
			next;
			mes "[ボルセブ]";
			mes "このパイプの調子が最近悪くてなァ。";
			mes "圧力が急に上昇することがある。";
			mes "そうなったら、爆発する前に、";
			mes "バルブを開けるんだ。";
			next;
			mes "[ボルセブ]";
			mes "1本2本なら問題ないが、";
			mes "それ以上爆発したら、漏れたガスで";
			mes "研究室にいられなくなるからなァ？";
			close;
		case 2:
			mes "[ボルセブ]";
			mes "前にも言ったが、";
			mes "コア実験体は非常に強力だぞォ。";
			next;
			mes "[ボルセブ]";
			mes "俺の研究室では、一度に複数の";
			mes "コア実験体が目覚めないよう";
			mes "制限がかかっているが、";
			mes "今どいつが目覚めているかを";
			mes "知る方法もない。";
			next;
			mes "[ボルセブ]";
			mes "ただ……コ、コア実験体のうち6体は、";
			mes "以前から研究所の3階にも出現するのを";
			mes "確認している。";
			next;
			mes "[ボルセブ]";
			mes "どうやって俺の研究室から";
			mes "抜け出してるのかわからねぇが、";
			mes "そっちで倒してもらっても構わないぞ。";
			mes "キヒヒヒヒ……";
			close;
		case 3:
			if(checkquest(5112)) {
				if(checkquest(5112) & 0x2 == 0) {
					mes "[ボルセブ]";
					mes "まだ研究室には入れない。";
					mes "72時間後だと言っただろォ？";
					mes "後でまた来い。";
					mes "キヒヒヒヒ";
					close;
				}
				mes "[ボルセブ]";
				mes "キヒ、キヒヒ……";
				mes "お前がコア実験体相手に";
				mes "苦労している間に調べたが……。";
				next;
				mes "[ボルセブ]";
				mes "ひひひ非常ボタンが押されると、";
				mes "システムが書き換えられる";
				mes "仕組みになっていてなァ……。";
				next;
				mes "[ボルセブ]";
				mes "限られた時間しか研究室に居られないし";
				mes "一度研究室から出ると、再度入れる";
				mes "ようになるまで、72時間も待たなくては";
				mes "いけなくなっている。";
				next;
				mes "[ボルセブ]";
				mes "暴走を止めるにも、研究室に居られる";
				mes "時間がこんなに限られているんじゃ、";
				mes "何回も研究室に行く必要がある……。";
				close;
			}
			if(getonlinepartymember() < 1) {
				mes "[ボルセブ]";
				mes "キヒッ？";
				mes "研究室の出入管理システムが";
				mes "おかしい。";
				mes "少し待つんだなァ。";
				close;
			}
			if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
				mes "[ボルセブ]";
				mes "^0000ffパーティーのリーダー^000000ではないな？";
				mes "リーダーを連れて来い！";
				close;
			}
			mdcreate "Worsef";
			mes "[ボルセブ]";
			mes "キヒッ！";
			mes "よし、入口を開けてやろう！";
			next;
			mes "‐ボルセブが";
			mes "　何かを操作し始めた。‐";
			next;
			progressbar 2;
			mes "[ボルセブ]";
			mes "キヒヒ！　研究室の出入管理システムに";
			mes "^0000ff" +strcharinfo(1)+ "^000000パーティーのリーダー^0000ff" +strcharinfo(0)+ "^000000!!";
			mes "確かに入力した。";
			next;
			mes "[ボルセブ]";
			mes "これでそこの扉から";
			mes "研究室に入る事ができるぞォ？";
			close;
		case 4:
			mes "[ボルセブ]";
			mes "あぁ？";
			mes "準備がまだ終わらないのか？";
			close;
		}
	case 9:
		// 未調査
		mes "[ボルセブ]";
		mes "ああ、そうだ……";
		mes "コア実験体を排除した礼をやろう！";
		mes "以前俺がいた研究室に、物置代わりに";
		mes "使っていた炉がある。";
		mes "その中のガラクタを持っていけ！";
		next;
		mes "[ボルセブ]";
		mes "俺には必要ない物だしなァ。";
		mes "キヒヒ！";
		next;
		mes "[ボルセブ]";
		mes "レッケンベルへの復讐を";
		mes "手伝ってくれるなら、";
		mes "また来てくれてもいいぜ？";
		mes "キーヒヒヒヒ！";
		next;
		mes "‐レッケンベル本社（lhz_in01）の";
		mes "　ボルセブの旧研究室（座標:43, 114）";
		mes "　に行ってみよう‐";
		close;
	case 10:
		mes "[ボルセブ]";
		mes "また来たのかァ？";
		mes "キヒヒ……";
		next;
		mes "[ボルセブ]";
		mes "お前が帰った後、研究結果を";
		mes "破壊しようとしていたのだが……";
		mes "お前がすべて倒したはずの";
		mes "コア実験体たちが、また";
		mes "さ、さ、再生し始めやがったんだ……";
		next;
		mes "[ボルセブ]";
		mes "すべてのコア実験体を倒せば";
		mes "復活は止まるようにプログラムされて";
		mes "いたのだが、それも変更されていた";
		mes "ようだ……";
		mes "キヒ、キヒヒヒヒ……";
		next;
		mes "[ボルセブ]";
		mes "なァ？";
		mes "研究結果の破壊のため、";
		mes "再度コア実験体を倒してくれ！";
		next;
		if(select("断る","引き受ける") == 1) {
			mes "[ボルセブ]";
			mes "コ、コア実験体が外に出たら、";
			mes "大変なことになるぞ！";
			mes "おおお俺はどうなっても";
			mes "知らないからな！";
			mes "キヒヒヒヒ……";
			close;
		}
		mes "[ボルセブ]";
		mes "キヒッ！";
		mes "研究所に入れるよう";
		mes "急ぎ手配してやる！";
		set LHZ_6QUE,11;
		close;
	default:
		mes "[研究員]";
		mes "何だぁ？";
		mes "研究の邪魔だぞ！";
		close;
	}
}

lhz_dun04.gat,147,279,0	script	研究室出入口#memo	844,{
	if(LHZ_6QUE < 8) {
		mes "‐^0000FF****様の研究室";
		mes "　関係者以外の立ち入り禁止^000000‐";
		close;
	}
	if(checkquest(5112)) {
		if(checkquest(5112) & 0x2) {
			mes "[出入管理システム]";
			mes strcharinfo(0)+ "……";
			mes "^FF0000接近拒否が解除されました。^000000";
			delquest 5112;
			close;
		}
		mes "[出入管理システム]";
		mes "ビービービー！";
		mes strcharinfo(0)+ "……";
		mes "^FF0000接近拒否対象です。^000000";
		next;
		mes "‐出入管理システムが";
		mes "　研究室接近を拒否した‐";
		close;
	}
	mes "‐ボルセブ研究室に入る扉だ。";
	mes "　扉の向こうから、渦巻く怨念が";
	mes "　泣き叫ぶ声のように聞こえて来る‐";
	next;
	if(select("研究室に入る","入らない") == 2) {
		mes "‐ボルセブの研究室に";
		mes "　入るのをやめた‐";
		close;
	}
	if(mdenter("Worsef") != 0) {
		mes "[出入管理システム]";
		mes "^FF0000警告^000000";
		mes strcharinfo(0)+ "……";
		mes "^FF0000登録されてない使用者^000000";
		next;
		pushpc 8,10;
		misceffect 131;
		misceffect 16,"";
		percentheal -5,0;
		mes "‐出入管理システムから攻撃を受け";
		mes "　あなたは怪我をした‐";
		close;
	}
	setquest 5112;
	set WORSEF_1QUE,0;
	donpcevent getmdnpcname("1研究室#1_1") +"::OnStart";
	announce "研究室の出入管理システム[" +strcharinfo(1)+ "]使用者[" +strcharinfo(0)+ "]様の出入許可……",0x9,0x0df297;
	close;
}

1@lhz.gat,45,148,0	script	1研究室#1_1	139,1,1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("書類#1_1");
	hideonnpc getmdnpcname("バルブ#1_2");
	hideonnpc getmdnpcname("バルブ#1_3");
	hideonnpc getmdnpcname("#escape1");
	hideonnpc getmdnpcname("#escape2");
	hideonnpc getmdnpcname("#potal_01");
	hideonnpc getmdnpcname("#potal_02");
	hideonnpc getmdnpcname("#potal_03");
	hideonnpc getmdnpcname("ボルセブ#last");
	end;
OnStart2:
	announce "警備システム : 保安システム停止に伴い、出入口の開閉は手動で行ってください。", 0x9, 0xff9977;
	misceffect 348,getmdnpcname("書類#1_1");
	hideoffnpc getmdnpcname("書類#1_1");
	misceffect 348,getmdnpcname("バルブ#1_2");
	hideoffnpc getmdnpcname("バルブ#1_2");
	misceffect 348,getmdnpcname("バルブ#1_3");
	hideoffnpc getmdnpcname("バルブ#1_3");
	end;
OnTouch:
	initnpctimer;
	hideonnpc getmdnpcname("1研究室#1_1");
	end;
OnTimer1000:
	announce "警備システム : 警告します。警告します。侵入者感知！",0x9,0xff9977;
	end;
OnTimer4000:
	announce "警備システム : 5秒後に第1研究所保安システムが稼働します。",0x9,0xff9977;
	end;
OnTimer9000:
	stopnpctimer;
	donpcevent getmdnpcname("MobCtrl1#mob01") +"::OnStart";
	end;
}

1@lhz.gat,1,1,0	script	MobCtrl1#mob01	139,{
OnStart:
	announce "警備システム : 保安システム稼働!!　実験動物が開放されます。関係者は退避してください。",0x9,0xff9977;
	areamonster getmdmapname("1@lhz.gat"),36,156,53,169,"飢えた実験動物",2242,11,getmdnpcname("MobCtrl1#mob01")+ "::OnKilled";
	end;
OnKilled:
	initnpctimer;
	end;
OnTimer1000:
	set '@count,getmapmobs(getmdmapname("1@lhz.gat"),getmdnpcname("MobCtrl1#mob01")+ "::OnKilled");
	if('@count == 0) {
		announce "警備システム : 第1研究所の保安システムが停止しました。", 0x9, 0xff9977;
		donpcevent getmdnpcname("1研究室#1_1") +"::OnStart2";
	}
	end;
}

1@lhz.gat,39,168,0	script	書類#1_1	844,{
	mes "‐書類がばらまかれている。";
	mes "　保安システムが停止した際の";
	mes "　出入口の操作マニュアルのようだ‐";
	next;
	mes "‐マニュアルによると、手動で出入口を";
	mes "　開くためには、バルブを決まった";
	mes "　順番で操作する必要があるようだ‐";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐バルブの操作はパーティーの";
		mes "　リーダーに任せておきましょう‐";
		close;
	}
	mes "‐パーティーのリーダーである";
	mes "　あなたは、さらに内容を読み進めた‐";
	next;
	mes "[非常出入バルブの操作方法]";
	if(WORSEF_1QUE == 0)
		set WORSEF_1QUE,rand(1,6);
	switch(WORSEF_1QUE) {
	case 1:
		mes "操作するバルブ：左バルブ";
		mes "回す方向：右2周、左1周、右1周";
		break;
	case 2:
		mes "操作するバルブ：左バルブ";
		mes "回す方向：右1周、左2周、右1周";
		break;
	case 3:
		mes "操作するバルブ：左バルブ";
		mes "回す方向：右1周、左1周、右2周";
		break;
	case 4:
		mes "操作するバルブ：右バルブ";
		mes "回す方向：左2周、右1周、左1周";
		break;
	case 5:
		mes "操作するバルブ：右バルブ";
		mes "回す方向：左1周、右2周、左1周";
		break;
	case 6:
		mes "操作するバルブ：右バルブ";
		mes "回す方向：左1周、右1周、左2周";
		break;
	}
	close;
}
1@lhz.gat,41,172,0	script	バルブ#1_2	844,{
	mes "‐「非常出入用（左バルブ）」と";
	mes "　書かれたバルブがある。";
	mes "　手動で出入口を開閉する際に";
	mes "　使用されるバルブのようだ‐";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐バルブの操作は、パーティーの";
		mes "　リーダーに任せよう‐";
		close;
	}
	mes "‐どの方向に回しますか？‐";
	for(set '@i,1; '@i <= 4; set '@i,'@i+1) {
		next;
		switch(select("右","左")) {
		case 1:
			if (('@i == 1 || '@i == 4) || ('@i == 2 && WORSEF_1QUE == 1) || ('@i == 3 && WORSEF_1QUE == 3)) {
				set '@success,'@success + 1;
			}
			break;
		case 2:
			if (('@i == 2 && WORSEF_1QUE != 1) || ('@i == 3 && WORSEF_1QUE != 3)) {
				set '@success,'@success + 1;
			}
			break;
		}
		if('@success == 4) {
			mes "‐ギィィー‐";
			announce "管理システム : 第2研究室に向かう扉が開かれました。", 0x9, 0x7799ff;
			hideoffnpc "#potal_01";
			set WORSEF_1QUE,0;
			close;
		}
		if('@i == 4) {
			mes "‐ギィー";
			mes "　";
			mes "　バルブを回したが、";
			mes "　何も起きなかった‐";
			next;
			mes "‐もう一度、書類を調べて";
			mes "　見る必要がありそうだ‐";
			close;
		}
		mes "‐ギィィー";
		mes "　";
		mes "　次はどの方向に回しますか？‐";
		continue;
	}
}
1@lhz.gat,52,172,0	script	バルブ#1_3	844,{
	mes "‐「非常出入用（右バルブ）」と";
	mes "　書かれたバルブがある。";
	mes "　手動で出入口を開閉する際に";
	mes "　使用されるバルブのようだ‐";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐バルブの操作は、パーティーの";
		mes "　リーダーに任せよう‐";
		close;
	}
	mes "‐どの方向に回しますか？‐";
	for(set '@i,0;'@i<4;set '@i,'@i+1) {
		next;
		switch(select("右","左")) {
		case 1:
			if(('@i == 2 && WORSEF_1QUE != 4) || ('@i == 3 && WORSEF_1QUE != 6)) {
				set '@success,'@success + 1;
			}
			break;
		case 2:
			if(('@i == 1 || '@i == 4) || ('@i == 2 && WORSEF_1QUE == 4) || ('@i == 3 && WORSEF_1QUE == 6)) {
				set '@success,'@success + 1;
			}
			break;
		}
		if('@success == 4) {
			mes "‐ギィィー‐";
			announce "管理システム : 第2研究室に向かう扉が開かれました。",0x9,0x7799ff;
			hideoffnpc "#potal_01";
			set WORSEF_1QUE,0;
			close;
		}
		if('@i == 4) {
			mes "‐ギィー";
			mes "　";
			mes "　バルブを回したが、";
			mes "　何も起きなかった‐";
			next;
			mes "‐もう一度、書類を調べて";
			mes "　見る必要がありそうだ‐";
			close;
		}
		mes "‐ギィィー";
		mes "　";
		mes "　次はどの方向に回しますか？‐";
		continue;
	}
}

1@lhz.gat,45,173,0	warp	#potal_01	2,2,1@lhz.gat,151,29

1@lhz.gat,151,29,0	script	#2_0	139,1,1,{
	donpcevent getmdnpcname("2研究室#2_1")+"::OnStart";
	hideonnpc getmdnpcname("#2_0");
	end;
}

1@lhz.gat,1,2,0	script	2研究室#2_1	139,{
OnStart:
	initnpctimer;
	end;
OnStart2:
	announce "管理システム : 第3研究室に向かう扉が開きました。",0x9,0x7799ff;
	hideoffnpc getmdnpcname("#potal_02");
	stopnpctimer;
	end;
OnTimer1000:
	announce "警備システム : 警告！　警告！　第2研究室に侵入者を感知!!",0x9,0xff9977;
	end;
OnTimer3000:
	announce "警備システム : 5秒後に第2研究室保安システムが稼働します。",0x9,0xff9977;
	end;
OnTimer8000:
	announce "警備システム : 1次保安システム稼働!!　関係者は退避してください。",0x9,0xff9977;
	donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnStart";
	end;
OnTimer12000:
	announce "管理システム : 警告！　第2研究室パイプの圧力があまりにも高いです。",0x9,0x7799ff;
	end;
OnTimer15000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer135000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer255000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer375000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer495000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer615000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer735000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	end;
OnTimer855000:
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStart";
	stopnpctimer;
	end;
}

1@lhz.gat,1,3,0	script	2研究室#2_2	139,{
OnStart:
	switch(rand(1,6)) {
	case 1:
		announce "管理システム : 警告！　パイプの圧力が高いです。第1バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第1バルブ#2_1")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_01";
		break;
	case 2:
		announce "管理システム : 警告！　パイプの圧力が高いです。第2バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第2バルブ#2_2")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_02";
		break;
	case 3:
		announce "管理システム : 警告！　パイプの圧力が高いです。第3バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第3バルブ#2_3")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_03";
		break;
	case 4:
		announce "管理システム : 警告！　パイプの圧力が高いです。第4バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第4バルブ#2_4")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_04";
		break;
	case 5:
		announce "管理システム : 警告！　パイプの圧力が高いです。第5バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第5バルブ#2_5")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_05";
		break;
	case 6:
		announce "管理システム : 警告！　パイプの圧力が高いです。第6バルブを開けて下さい。",0x9,0x7799ff;
		donpcevent getmdnpcname("第6バルブ#2_6")+"::OnStart";
		donpcevent getmdnpcname("MobCtrl2#mob02")+"::OnSpawn_06";
		break;
	}
	initnpctimer;
	end;
OnTimer63000:
	stopnpctimer;
	set 'flag,'flag + 1;
	if('flag == 3) {
		donpcevent getmdnpcname("#2_3")+"::OnStart";
	}
	else {
		announce "管理システム : パイプ爆破感知！　これから"+ (3 - 'flag) +"個爆破時、強制脱出装置が起動します。",0x9,0x7799ff;
	}
	for(set '@i,1; '@i <= 6; set '@i,'@i+1) {
		misceffect 16, "第" +'@i+ "バルブ#2_" +'@i;
	}
	end;
OnStop:
	stopnpctimer;
	end;
}

1@lhz.gat,1,4,0	script	MobCtrl2#mob02	139,{
OnStart:
	set 'lv,1;
	setarray 'mob[1],10,20,16,19,20;
	areamonster getmdmapname("1@lhz.gat"),139,37,164,58,"飢えた実験動物",2242,'mob[lv],getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@lhz.gat"),getmdnpcname("MobCtrl2#mob02")+ "::OnKilled");
	if('@count > 0)
		end;
	set 'lv,'lv + 1;
	if('lv == 6) {
		announce "警備システム : 第2研究室の保安システムが停止しました。",0x9,0xff9977;
		donpcevent getmdnpcname("2研究室#2_1")+"::OnStart2";
		donpcevent getmdnpcname("2研究室#2_2")+"::OnStop";
	}
	else {
		initnpctimer;
		announce "警備システム : 5秒後に" +'lv+ "次保安システムが稼働します。",0x9,0xff9977;
	}
	end;
OnTimer5000:
	stopnpctimer;
	announce "警備システム : " +'lv+ "次保安システム稼働!!　関係者は退避して下さい。",0x9,0xff9977;
	areamonster getmdmapname("1@lhz.gat"),139,37,164,58,"飢えた実験動物",2242,'mob[lv],getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_01:
	areamonster getmdmapname("1@lhz.gat"),155,43,161,49,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_02:
	areamonster getmdmapname("1@lhz.gat"),137,40,143,46,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_03:
	areamonster getmdmapname("1@lhz.gat"),137,51,143,57,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_04:
	areamonster getmdmapname("1@lhz.gat"),143,56,149,62,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_05:
	areamonster getmdmapname("1@lhz.gat"),160,48,166,54,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
OnSpawn_06:
	areamonster getmdmapname("1@lhz.gat"),135,44,141,50,"飢えた実験動物",2243,5,getmdnpcname("MobCtrl2#mob02")+"::OnKilled";
	end;
}

1@lhz.gat,151,53,0	script	#2_3	139,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	announce "管理システム : システム停止！　システム停止！　10秒後に研究室の外に脱出経路を開きます。",0x9,0x7799ff;
	end;
OnTimer11000:
	announce "管理システム : 脱出してください!!",0x9,0x7799ff;
	hideoffnpc getmdnpcname("#escape1");
	hideoffnpc getmdnpcname("#escape2");
	end;
}

1@lhz.gat,46,158,0	script	#escape1	139,20,20,{
	warp "lhz_dun04.gat",147,273;
	end;
}

1@lhz.gat,151,38,0	script	#escape2	139,20,20,{
	warp "lhz_dun04.gat",147,273;
	end;
}

1@lhz.gat,158,46,0	script	第1バルブ#2_1	844,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0) || 'active <= 0) {
		mes "‐今このバルブを操作する必要はない‐";
		close;
	}
	progressbar 20;
	stopnpctimer;
	donpcevent getmdnpcname("2研究室#2_2")+"::OnStop";
	end;
OnStart:
	set 'active,20;
	initnpctimer;
	end;
OnTimer3000:
	misceffect 373;
	stopnpctimer;
	if('active) {
		set 'active,'active - 1;
		initnpctimer;
	}
	end;
}

1@lhz.gat,138,43,0	duplicate(第1バルブ#2_1)	第2バルブ#2_2	844
1@lhz.gat,139,54,0	duplicate(第1バルブ#2_1)	第3バルブ#2_3	844
1@lhz.gat,145,60,0	duplicate(第1バルブ#2_1)	第4バルブ#2_4	844
1@lhz.gat,165,51,0	duplicate(第1バルブ#2_1)	第5バルブ#2_5	844
1@lhz.gat,137,47,0	duplicate(第1バルブ#2_1)	第6バルブ#2_6	844

1@lhz.gat,151,64,0	warp	#potal_02	2,2,1@lhz.gat,84,28

1@lhz.gat,84,28,0	script	#3_0	139,1,1,{
	donpcevent getmdnpcname("3研究室#3_1")+"::OnStart";
	hideonnpc getmdnpcname("#3_0");
	end;
}

1@lhz.gat,1,5,0	script	3研究室#3_1	139,{
OnStart:
	initnpctimer;
	end;
OnStart2:
	announce "管理システム : 第4研究室に向かう扉が開きました。",0x9,0x7799ff;
	hideoffnpc getmdnpcname("#potal_03");
	end;
OnTimer1000:
	announce "警備システム : 警告！　警告！",0x9,0xff9977;
	end;
OnTimer5000:
	announce "警備システム : 第3研究室に侵入者感知!!",0x9,0xff9977;
	end;
OnTimer7000:
	announce "警備システム : 5秒後に第3研究室の保安システムが稼働します。",0x9,0xff9977;
	end;
OnTimer12000:
	announce "警備システム : 第3研究室の1次保安システム稼働!!　関係者は退避してください。",0x9,0xff9977;
	donpcevent getmdnpcname("MobCtrl3#mob03")+"::OnStart";
	stopnpctimer;
	end;
}

1@lhz.gat,1,6,0	script	MobCtrl3#mob03	139,{
OnStart:
	set 'lv,1;
	set '@map$,getmdmapname("1@lhz.gat");
	set '@label$,getmdnpcname("MobCtrl3#mob03")+"::OnKilled";
	monster '@map$,80,60,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,82,60,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,84,60,"飢えた実験動物",2243,1,'@label$;
	monster '@map$,86,60,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,81,58,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,83,58,"飢えた実験動物",2243,1,'@label$;
	monster '@map$,85,58,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,87,58,"飢えた実験動物",2242,1,'@label$;
	monster '@map$,82,56,"飢えた実験動物",2243,1,'@label$;
	monster '@map$,85,56,"飢えた実験動物",2242,1,'@label$;
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@lhz.gat"),getmdnpcname("MobCtrl3#mob03")+ "::OnKilled");
	if('@count > 0)
		end;
	set 'lv,'lv + 1;
	if('lv == 6) {
		announce "警備システム : 第3研究室の保安システムが停止しました。",0x9,0xff9977;
		donpcevent getmdnpcname("3研究室#3_1")+"::OnStart2";
	}
	else {
		initnpctimer;
		announce "警備システム : 5秒後に" +'lv+ "次保安システムが稼働します。",0x9,0xff9977;
	}
	end;
OnTimer5000:
	stopnpctimer;
	announce "警備システム : " +'lv+ "次保安システム稼働!!　関係者は退避して下さい。",0x9,0xff9977;
	set '@map$,getmdmapname("1@lhz.gat");
	set '@label$,getmdnpcname("MobCtrl3#mob03")+"::OnKilled";
	monster '@map$,80,60,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,82,60,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,84,60,"飢えた実験動物",2243,rand(1,5),'@label$;
	monster '@map$,86,60,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,81,58,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,83,58,"飢えた実験動物",2243,rand(1,5),'@label$;
	monster '@map$,85,58,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,87,58,"飢えた実験動物",2242,rand(1,5),'@label$;
	monster '@map$,82,56,"飢えた実験動物",2243,rand(1,5),'@label$;
	monster '@map$,85,56,"飢えた実験動物",2242,rand(1,5),'@label$;
	end;
}

1@lhz.gat,83,62,0	warp	#potal_03	2,2,1@lhz.gat,137,100

1@lhz.gat,137,100,0	script	#4_0	139,1,1,{
	donpcevent getmdnpcname("4研究室#4_1")+"::OnStart";
	hideonnpc getmdnpcname("#4_0");
	end;
}

1@lhz.gat,1,7,0	script	4研究室#4_1	139,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	announce "囁き : 君は誰だ……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss01";
	end;
OnTimer2000:
	misceffect 72,"Worsef_boss02";
	end;
OnTimer3000:
	announce "囁き : これ以上近寄るな……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss03";
	end;
OnTimer4000:
	misceffect 72,"Worsef_boss04";
	end;
OnTimer5000:
	announce "囁き : ここは危険だ……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss05";
	end;
OnTimer6000:
	misceffect 72,"Worsef_boss06";
	end;
OnTimer7000:
	announce "囁き : 生きて出ていけない……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss07";
	end;
OnTimer8000:
	misceffect 72,"Worsef_boss08";
	end;
OnTimer9000:
	announce "囁き : 私たちのようになりたくないなら……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss09";
	end;
OnTimer10000:
	misceffect 72,"Worsef_boss10";
	end;
OnTimer11000:
	announce "囁き : すぐに離れろ……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss11";
	end;
OnTimer12000:
	misceffect 72,"Worsef_boss12";
	end;
OnTimer13000:
	announce "囁き : 悲しみと痛みがここを満たす前に……",0x9,0x7dcbf0;
	misceffect 72,"Worsef_boss13";
	end;
OnTimer17000:
	announce "囁き : あ……あ……もう遅い……",0x9,0x7dcbf0;
	donpcevent getmdnpcname("MobCtrl4#mob04")+"::OnStart";
	stopnpctimer;
	end;
}

1@lhz.gat,1,8,0	script	MobCtrl4#mob04	139,{
OnStart:
	set 'mvp,rand(1,13);
	if('mvp > 9) {
		misceffect 183,getmdnpcname("Worsef_boss" +'mvp);
		hideonnpc getmdnpcname("Worsef_boss" +'mvp);
	}
	else {
		misceffect 183,getmdnpcname("Worsef_boss0" +'mvp);
		hideonnpc getmdnpcname("Worsef_boss0" +'mvp);
	}
	set '@map$,getmdmapname("1@lhz.gat");
	set '@label$,getmdnpcname("MobCtrl4#mob04")+"::OnKilled";
	switch('mvp) {
	case 1:
		monster '@map$,129,154,"セイレン=ウィンザー",1646,1,'@label$;
		break;
	case 2:
		monster '@map$,125,150,"セシル=ディモン",1650,1,'@label$;
		break;
	case 3:
		monster '@map$,121,146,"ガーティー=ウー",2239,1,'@label$;
		break;
	case 4:
		monster '@map$,117,142,"エレメス=ガイル",1647,1,'@label$;
		break;
	case 5:
		monster '@map$,117,125,"トレンティーニ",2241,1,'@label$;
		break;
	case 6:
		monster '@map$,121,121,"チェン=リウ",2238,1,'@label$;
		break;
	case 7:
		monster '@map$,125,117,"アルフォシオ=バジル",2240,1,'@label$;
		break;
	case 8:
		monster '@map$,129,113,"エミュール=プラメール",2236,1,'@label$;
		break;
	case 9:
		monster '@map$,146,113,"ランデル=ロレンス",2235,1,'@label$;
		break;
	case 10:
		monster '@map$,150,117,"セリア=アルデ",2237,1,'@label$;
		break;
	case 11:
		monster '@map$,154,121,"カトリーヌ=ケイロン",1651,1,'@label$;
		break;
	case 12:
		monster '@map$,158,125,"マーガレッタ=ソリン",1649,1,'@label$;
		break;
	case 13:
		monster '@map$,158,142,"ハワード=アルトアイゼン",1648,1,'@label$;
		break;
	}
	end;
OnKilled:
	switch('mvp) {
	case 1:		// セイレン=ウィンザー
		announce "うう……皆、無事か……やられてしまったのか……？",0x9,0xfd3b02;
		break;
	case 2:		// セシル=ディモン
		announce "怖い！　誰でもいいから……っお願い……！",0x9,0xfd3b02;
		break;
	case 3:		// ガーティー=ウー
		announce "くっ……油断したつもりは……なかったんだけど、ね……",0x9,0xfd3b02;
		break;
	case 4:		// エレメス=ガイル
		announce "チッ……俺の足を止められるなんてな……",0x9,0xfd3b02;
		break;
	case 5:		// トレンティーニ
		announce "もう一度……楽しく歌って……たのしく……おど、って……",0x9,0xfd3b02;
		break;
	case 6:		// チェン=リウ
		announce "ご……ごめん……俺のせいで……",0x9,0xfd3b02;
		break;
	case 7:		// アルフォシオ=バジル
		announce "トレンティーニ……新しく……作曲した歌を……共に……",0x9,0xfd3b02;
		break;
	case 8:		// エミュール=プラメール
		announce "はぁ……新しく開発したポーション……見せたかったなぁ……",0x9,0xfd3b02;
		break;
	case 9:		// ランデル=ロレンス
		announce "な、仲間たちを……守らなければ……っ！",0x9,0xfd3b02;
		break;
	case 10:	// セリア=アルデ
		announce "……この、研究……は、止めないと……",0x9,0xfd3b02;
		break;
	case 11:	// カトリーヌ=ケイロン
		announce "ああ……どうか……みんな無事で……",0x9,0xfd3b02;
		break;
	case 12:	// マーガレッタ=ソリン
		announce "泣かないで……あ……オーディン様……私たちを……",0x9,0xfd3b02;
		break;
	case 13:	// ハワード=アルトアイゼン
		announce "姉さん……もう一度……会いたい……",0x9,0xfd3b02;
		break;
	}
	hideoffnpc getmdnpcname("ボルセブ#last");
	end;
}

1@lhz.gat,127,156,5	script	セイレン=ウィンザー::Worsef_boss01	1646,{}
1@lhz.gat,123,152,5	script	セシル=ディモン::Worsef_boss02	1650,{}
1@lhz.gat,119,148,5	script	ガーティー=ウー::Worsef_boss03	2239,{}
1@lhz.gat,115,144,5	script	エレメス=ガイル::Worsef_boss04	1647,{}
1@lhz.gat,115,123,7	script	トレンティーニ::Worsef_boss05	2241,{}
1@lhz.gat,119,119,7	script	チェン=リウ::Worsef_boss06	2238,{}
1@lhz.gat,123,115,7	script	アルフォシオ=バジル::Worsef_boss07	2240,{}
1@lhz.gat,127,111,7	script	エミュール=プラメール::Worsef_boss08	2236,{}
1@lhz.gat,148,111,1	script	ランデル=ロレンス::Worsef_boss09	2235,{}
1@lhz.gat,152,115,1	script	セリア=アルデ::Worsef_boss10	2237,{}
1@lhz.gat,156,119,1	script	カトリーヌ=ケイロン::Worsef_boss11	1651,{}
1@lhz.gat,160,123,1	script	マーガレッタ=ソリン::Worsef_boss12	1649,{}
1@lhz.gat,160,144,3	script	ハワード=アルトアイゼン::Worsef_boss13	1648,{}

1@lhz.gat,137,156,7	script	ボルセブ#last	865,{
	mes "[ボルセブ]";
	mes "今すぐ研究室の外に出るのか？";
	next;
	if(select("出ない","出る") == 1) {
		mes "[ボルセブ]";
		mes "キヒヒ";
		mes "出たくなったら声をかけてくれ。";
		close;
	}
	mes "[ボルセブ]";
	mes "キヒヒ";
	mes "わかった、研究室の外に出してやる。";
	close2;
	warp "lhz_dun04.gat",147,273;
	end;
}
