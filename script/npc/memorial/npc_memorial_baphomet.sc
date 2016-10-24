//= Auriga Script ==============================================================
// Ragnarok Online Sealed Shrine Script	by refis
//- Registry -------------------------------------------------------------------
// BAPHO_1QUE -> 0～7
//==============================================================================

//============================================================
// 大型マジェスティックゴート製作NPC
//------------------------------------------------------------
prt_monk.gat,261,91,3	script	ブラックハンド	826,{
	mes "[ブラックハンド]";
	mes "なんだお前は？";
	mes "オレに用でもあるのか？";
	next;
	mes "[ブラックハンド]";
	mes "修道士でもないやつが";
	mes "オレに用があるってのか？";
	next;
	if(checkquest(3043)) {
		mes "[ブラックハンド]";
		mes "……って、なんだお前か。";
		mes "材料はちゃんと";
		mes "揃えてきたんだろうな？";
		next;
		if(countitem(6004) < 1 || countitem(2256) < 1 || countitem(7799) < 30 || countitem(7798) < 50 || Zeny < 990000) {
			mes "[ブラックハンド]";
			mes "フム…………";
			mes "準備できてないようだな。";
			next;
			mes "[ブラックハンド]";
			mes "もう一度材料を教えてやる。";
			next;
			mes "[ブラックハンド]";
			mes "^0000FF呪われたバフォメット人形1個^000000、";
			mes "^0000FFマジェスティックゴート[0]1個^000000、";
			mes "^0000FF闇の結晶体30個^000000、^0000FF闇の破片50個^000000";
			mes "そして！";
			mes "肝心な制作費が^0000FF990,000^000000Zenyだ。";
			mes "しっかり覚えてくれよ！";
			close;
		}
		mes "[ブラックハンド]";
		mes "フム…………";
		mes "準備できているようだな。";
		mes "んじゃ、材料をそこにおいて";
		mes "ちょっと待ってくれ。";
		next;
		mes "[ブラックハンド]";
		mes "……";
		next;
		mes "[ブラックハンド]";
		mes "…………";
		next;
		mes "[ブラックハンド]";
		mes "………………";
		misceffect 101;
		next;
		delitem 6004,1;
		delitem 2256,1;
		delitem 7799,30;
		delitem 7798,50;
		set Zeny,Zeny-990000;
		delquest 3043;
		getitem 5374,1;
		mes "[ブラックハンド]";
		mes "さぁ、これで完成だ！";
		mes "ハッハッハ、言わなくても分かる。";
		mes "今お前は感動して、";
		mes "涙を流しそうなほどうれしいんだろ？";
		next;
		mes "[ブラックハンド]";
		mes "ま、大事に使ってくれよ。";
		mes "じゃあな！";
		close;
	}
	if(countitem(6004) < 1 || !checkquest(3042)) {
		mes "[ブラックハンド]";
		mes "用がなければ話かけるな！";
		mes "オレは修道士用の装備を";
		mes "作ってるんだ。";
		mes "暇じゃねーんだぞ？";
		mes "分かったな!?";
		close;
	}
	switch(select("呪われたバフォメット人形について","会話をやめる")) {
	case 1:
		mes "[ブラックハンド]";
		mes "なにっ!?";
		mes "その人形を手に入れただと？";
		mes "ほう……";
		mes "少しは腕に自信があるようじゃねぇか。";
		next;
		mes "[ブラックハンド]";
		mes "わかってるわかってる。";
		mes "あのおっさんから人形を持ってけって";
		mes "言われて来たのだろ？";
		next;
		mes "[ブラックハンド]";
		mes "いいだろう。";
		mes "早速その不気味な人形を";
		mes "有意義な物に変えてやるよ。";
		next;
		mes "[ブラックハンド]";
		mes "その巨大な角を活かした、";
		mes "素晴らしい兜を作ってやるからさ！";
		mes "もちろん、バフォメットの";
		mes "パワーを込めてな。";
		next;
		mes "[ブラックハンド]";
		mes "通称、^0000FF大型マジェスティックゴート^000000。";
		mes "普通のマジェスティックゴートとは";
		mes "桁が違う！";
		mes "最高の代物だ。";
		next;
		mes "[ブラックハンド]";
		mes "それを作るための材料の中で";
		mes "一番大事な物がこの";
		mes "呪われたバフォメット人形！";
		mes "どうだ？　作ってほしいのか？";
		mes "材料が知りたいか？　どうする？";
		next;
		if(select("欲しい","いらない")==2) {
			//未調査
			mes "[ブラックハンド]";
			mes "用がなければ話かけるな！";
			mes "オレは修道士用の装備を";
			mes "作ってるんだ。";
			mes "暇じゃねーんだぞ？";
			mes "分かったな!?";
			close;
		}
		mes "[ブラックハンド]";
		mes "フッフッフ……";
		mes "だろう、これはいいチャンスだ。";
		mes "お前は懸命な判断をしたな。";
		mes "では材料を教えてやる。";
		next;
		mes "[ブラックハンド]";
		mes "^0000FF呪われたバフォメット人形1個^000000、";
		mes "^0000FFマジェスティックゴート[0]1個^000000、";
		mes "^0000FF闇の結晶体30個^000000、^0000FF闇の破片50個^000000";
		mes "そして！";
		mes "肝心な制作費が^0000FF990,000^000000Zenyだ。";
		mes "しっかり覚えてくれよ！";
		next;
		mes "[ブラックハンド]";
		mes "マジェスティックゴートは、";
		mes "プロンテラの迷宮の森にいる";
		mes "弱っちい方のバフォメットから";
		mes "手に入れられる。";
		mes "そして闇の結晶と闇の欠片は";
		mes "魔王モロクの現身から手に入るはず。";
		next;
		mes "[ブラックハンド]";
		mes "あの真のバフォメットも倒した";
		mes "実力だから簡単なはずだ。";
		mes "フッフッフ……";
		mes "分かったら早く材料を持ってこい！";
		chgquest 3042,3043;
		close;
	case 2:
		//未調査
		mes "[ブラックハンド]";
		mes "用がなければ話かけるな！";
		mes "オレは修道士用の装備を";
		mes "作ってるんだ。";
		mes "暇じゃねーんだぞ？";
		mes "分かったな!?";
		close;
	}
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
monk_test.gat,309,146,3	script	修道士パトリック	412,{
	if(checkitemblank() < 5) {
		mes "‐所持アイテムの種類数が多い為";
		mes "　危険です。";
		mes "　5種類以上の所持アイテムを";
		mes "　減らしてから、";
		mes "　再度話しかけてください‐";
		close;
	}
	cutin "ins_cata_pri_n",2;
	mes "[修道士パトリック]";
	mes "この世の平和が続くことなく、";
	mes "再び邪悪な気配が訪れようとしている。";
	mes "これは誰の責任なのか……";
	next;
	mes "[修道士パトリック]";
	mes "………………";
	mes "こんな大変な時だというのに……";
	mes "ここに何の用で来たのかね？";
	next;
	if(countitem(6004) > 0) {
		set '@str$,"^0000FF呪われたバフォメット人形について^000000";
	} else {
		set '@str$,"特に用はないです";
	}
	switch(select("ここは何ですか？","ここに入りたいです",'@str$,"会話をやめる")) {
	case 1:
		mes "[修道士パトリック]";
		mes "ハハハ、本当に知らないのかね？";
		mes "ここは、モンクを目指している者が";
		mes "技を磨き、祈りを捧げる場所、";
		mes "聖カピトーリナ修道院だ。";
		next;
		mes "[修道士パトリック]";
		mes "そして今、君が立っている";
		mes "この場所は……";
		mes "^0000FF封印された神殿^000000と言われる場所に";
		mes "繋がっている……";
		next;
		mes "[修道士パトリック]";
		mes "君がこの世に生を受けてもいない";
		mes "遠い昔、この大地を支配していた、";
		mes "巨大な悪魔が眠っているのだ。";
		mes "そして私はこの場所を管理している。";
		next;
		switch(select("もう少し詳しく教えてください","会話をやめる")) {
		case 1:
			cutin "ins_cata_pri_n",2;
			mes "[修道士パトリック]";
			mes "^FF0000魔王バフォメット^000000……";
			mes "それがその悪魔の名だ。";
			mes "バフォメットの名くらいは";
			mes "聞いた事があるだろう？";
			next;
			mes "[修道士パトリック]";
			mes "この悪魔を退治するために、";
			mes "ここ聖カピトーリナ修道院では";
			mes "優秀な冒険者たちを育成し、";
			mes "世の中に送り出してきたのだ。";
			next;
			mes "[修道士パトリック]";
			mes "今君の目の前にある封印石には";
			mes "計り知れない犠牲と努力で捕らえた";
			mes "魔王バフォメットが封印されている。";
			next;
			mes "[修道士パトリック]";
			mes "しかし残念な事に……";
			mes "魔王モロクの復活後あたりから";
			mes "世の中のあらゆる生命に影響が";
			mes "出始めている。";
			mes "もちろんこの魔王バフォメットにもな。";
			next;
			mes "[修道士パトリック]";
			mes "最近魔王バフォメットを封じ込める力が";
			mes "弱くなってきてな、このままだと";
			mes "封印が破られ、魔王バフォメットが";
			mes "復活する恐れがある。";
			next;
			mes "そこで私は再び封印をかけるため";
			mes "君のような冒険者たちを";
			mes "探しているのだよ。";
			mes "感じぬか？";
			mes "この邪悪な波動を。";
			break;
		case 2:
			cutin "ins_cata_pri_n",2;
			mes "[修道士パトリック]";
			mes "しかしその封印が破られそうなのだ。";
			mes "そこで私は再び封印をかけるため";
			mes "君のような冒険者たちを";
			mes "探しているのだよ。";
			mes "感じぬか？";
			mes "この邪悪な波動を。";
			break;
		}
		next;
		mes "[修道士パトリック]";
		mes "己の力を磨き、どうかその力を";
		mes "魔王バフォメットを封印する事に";
		mes "使って欲しい。";
		break;
	case 2:
		if(BaseLevel < 75) {
			mes "[修道士パトリック]";
			mes "Lv75以上はないと";
			mes "魔王バフォメットの力に";
			mes "耐えられそうにないのだ……";
			next;
			mes "[修道士パトリック]";
			mes "残念だが、また来てくれ";
			break;
		}
		mes "[修道士パトリック]";
		mes "ほう、この神殿に入り";
		mes "悪魔を退けてくれると言うのか!?";
		next;
		if(checkquest(3040)) {
			if(checkquest(3040) & 0x2) {
				mes "[修道士パトリック]";
				mes "……おお、";
				mes "ようやく君の体にかかっていた";
				mes "呪いの力が弱まってきたか……";
				mes "では私の力でその邪悪な気配を";
				mes "消し去ってしんぜよう";
				next;
				mes "[修道士パトリック]";
				mes "^FF0000ヌアァァァ!!";
				mes "パトリクパトリカパトルルルゥゥゥ！^000000";
				misceffect 152,"";
				delquest 3040;
				if(checkquest(3041)) delquest 3041;
				next;
				mes "[修道士パトリック]";
				mes "ふぅ～、";
				mes "終わったぞ。";
				mes "これであなたにかかっていた呪いは";
				mes "全て取り除かれた。";
				mes "もう出入りが出来るだろう。";
				break;
			}
			mes "[修道士パトリック]";
			mes "君は……";
			mes "既にここに入った事があるな。";
			mes "君の体にはまだ呪いが";
			mes "残っているようだ。";
			mes "封印の調整を行うことができない。";
			mes "もう少し待てば呪いが解けるだろう。";
			break;
		}
		if(getonlinepartymember() < 2 || getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[修道士パトリック]";
			mes "気持ちは分かるが、";
			mes "ここは誰でも入れる";
			mes "場所ではないのだ。";
			mes "必ず^FF00002人以上のパーティー^000000を組み、";
			mes "そのパーティーの代表が";
			mes "私と話をする資格がある。";
			next;
			mes "[修道士パトリック]";
			mes "パーティーの代表に許可が出れば";
			mes "そのパーティーメンバーにも";
			mes "許可が出る。";
			mes "これは修道院の方針なのだ。";
			mes "我慢してくれ。";
			break;
		}
		mdcreate "Sealed Shrine";
		mes "[修道士パトリック]";
		mes "パーティー名が、";
		mes "^0000FF" +getpartyname(getcharid(1))+ "^000000で……";
		mes "リーダーは";
		mes "^FF0000" +getpartyleader(getcharid(1))+ "^000000か……";
		mes "………………";
		next;
		mes "[修道士パトリック]";
		mes "……分かった。";
		mes "君たちが中に入れるよう";
		mes "入り口の封印を調整しよう。";
		next;
		mes "[修道士パトリック]";
		mes "もうしばらくすれば、君たちが";
		mes "ここを通ることができるように";
		mes "なったことが示される。";
		next;
		mes "[修道士パトリック]";
		mes "そうしたら、そこにある";
		mes "祭壇に手をかざすのだ。";
		mes "そうすれば中に入れるようになる。";
		next;
		mes "[修道士パトリック]";
		mes "また、覚えておいて欲しいことがある。";
		mes "ここに一度でも足を踏み入れた者は。";
		mes "^FF0000バフォメットの呪い^000000がかかる。";
		mes "そして呪いが解けるまでは";
		mes "一切この入り口の封印を";
		mes "くぐり抜けることができなくなる。";
		next;
		mes "[修道士パトリック]";
		mes "そしてもう一つ！";
		mes "この神殿内では呪いのせいで、";
		mes "一部のスキルやアイテムが使えない。";
		next;
		mes "[修道士パトリック]";
		mes "^0000FFテレポート、セイフティウォール";
		mes "アスムプティオ、アブラカタブラ、";
		mes "レディムプティオ^000000は使えない。";
		mes "それに^0000FFハイローゾイストカードや";
		mes "アゾート^000000のようなモンスターが";
		mes "変換する効果も発揮しない。";
		next;
		mes "[修道士パトリック]";
		mes "十分注意するのだぞ。";
		break;
	case 3:
		if(checkquest(3042) || checkquest(3043)) {
			// 未調査
			mes "[修道士パトリック]";
			mes "修道院の南にいる、";
			mes "^0000FFブラックハンド^000000と言う者だ。";
			mes "彼ならその人形をあなたに役立つ物に";
			mes "変えてくれるだろう。";
			mes "是非会ってみるといい。";
			break;
		}
		if(countitem(6004) > 0) {
			mes "[修道士パトリック]";
			mes "そ、それは……!!";
			mes "ちょっと見せてくれ！";
			mes "…………ふむぅ……！";
			next;
			mes "[修道士パトリック]";
			mes "間違いない……";
			mes "これはあの邪悪なバフォメットの";
			mes "魔力が込められた人形！";
			mes "よ、よく手に入れたな……";
			next;
			mes "[修道士パトリック]";
			mes "で……その人形を";
			mes "どうするつもりだ？";
			mes "……それはとても危険な代物だ。";
			next;
			mes "[修道士パトリック]";
			mes "……だが、";
			mes "それを役立てることが出来る";
			mes "人物が一人いる。";
			mes "紹介しよう……";
			next;
			mes "[修道士パトリック]";
			mes "修道院の南にいる、";
			mes "^0000FFブラックハンド^000000と言う者だ。";
			mes "彼ならその人形をあなたに役立つ物に";
			mes "変えてくれるだろう。";
			mes "是非会ってみるといい。";
			setquest 3042;
			break;
		}
	case 4:
		mes "[修道士パトリック]";
		mes "何だ、用がないのかね。";
		mes "実に寂しいことだ……";
		break;
	}
	close2;
	cutin "ins_cata_pri_n",255;
	end;
}

//============================================================
// 転送NPC
//------------------------------------------------------------
monk_test.gat,306,151,3	script	封印石	111,{
	if(countitem(6001) > 0)
		delitem 6001,countitem(6001);
	if(countitem(6002) > 0)
		delitem 6002,countitem(6002);
	mes "‐大きな角が生えた";
	mes "　悪魔の姿が刻まれた巨大な石だ。";
	mes "　邪悪な波動を感じる‐";
	next;
	switch(select("触ってみる","後へ下がる")) {
	case 1:
		if(checkquest(3040)) {
			if(checkquest(3040) & 0x2) {
				cutin "ins_cata_pri_n",2;
				mes "[修道士パトリック]";
				mes "……おお、";
				mes "ようやく君の体にかかっていた";
				mes "呪いの力が弱まってきたか……";
				mes "では私の力でその邪悪な気配を";
				mes "消し去ってしんぜよう";
				next;
				mes "[修道士パトリック]";
				mes "^FF0000ヌアァァァ!!";
				mes "パトリクパトリカパトルルルゥゥゥ！^000000";
				misceffect 152,"";
				delquest 3040;
				if(checkquest(3041)) delquest 3041;
				next;
				mes "[修道士パトリック]";
				mes "ふぅ～、";
				mes "終わったぞ。";
				mes "これであなたにかかっていた呪いは";
				mes "全て取り除かれた。";
				mes "もう出入りが出来るだろう。";
				close2;
				cutin "ins_cata_pri_n",255;
				end;
			}
			misceffect 152,"";
			mes "‐指先から強烈な衝撃が";
			mes "　体に伝わってきた！‐";
			next;
			cutin "ins_cata_pri_n",2;
			mes "[修道士パトリック]";
			mes "君は……";
			mes "既にここに入った事があるな。";
			mes "君の体にはまだ呪いが";
			mes "残っているようだ。";
			mes "もう少し待てば呪いが解けるだろう。";
			close2;
			cutin "ins_cata_pri_n",255;
			end;
		}
		switch(mdenter("Sealed Shrine")) {
		case 0:	// エラーなし
			announce "[" +strcharinfo(1)+ "] パーティーの [" +strcharinfo(0)+ "] が [Sealed Shrine] に入場します",0x9,0x00FF99;
			setquest 3040;
			set BAPHO_1QUE,0;
			donpcevent getmdnpcname("BaphometControl1-1")+ "::OnStart";
			end;
		default:	// エラー
			mes "‐指先から恐ろしい気配を";
			mes "　感じとれる。";
			mes "　だが特に何の反応もない‐";
			close;
		}
	case 2:
		mes "‐ここを離れよう……‐";
		break;
	}
	close;
}

//============================================================
// 封印された神殿1F
//------------------------------------------------------------
1@cata.gat,0,0,0	script	BaphometControl1-1	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;

	hideonnpc getmdnpcname("先代英雄の魂#1F");
	hideonnpc getmdnpcname("BaphometGate");

	set '@num,rand(1,13);
	for(set '@i,1; '@i<13; set '@i,'@i+1) {
		if('@num == '@i)
			hideonnpc getmdnpcname("崩れかけの墓#1F_"+'@i+"F");
		else
			hideonnpc getmdnpcname("崩れかけの墓#1F_"+'@i+"T");
	}
	for(set '@i,1; '@i<12; set '@i,'@i+1)
		hideonnpc getmdnpcname("揺らめく松明#"+'@i);

	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"デッドリーレイス",1291,40,getmdnpcname("BaphometControl1-1")+"::OnKilled1";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"カーリッツバーグ",1132,20,getmdnpcname("BaphometControl1-1")+"::OnKilled2";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"フレームスカル",1869,40,getmdnpcname("BaphometControl1-1")+"::OnKilled3";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"エンシェントミミック",1699,30,getmdnpcname("BaphometControl1-1")+"::OnKilled4";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ゾンビマスター",1298,40,getmdnpcname("BaphometControl1-1")+"::OnKilled5";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ジェネラルスケルトン",1290,40,getmdnpcname("BaphometControl1-1")+"::OnKilled6";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ウィンドゴースト",1263,30,getmdnpcname("BaphometControl1-1")+"::OnKilled7";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ルード",1509,20,getmdnpcname("BaphometControl1-1")+"::OnKilled8";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"イビルドルイド",1117,30,getmdnpcname("BaphometControl1-1")+"::OnKilled9";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バンシー",1867,10,getmdnpcname("BaphometControl1-1")+"::OnKilled10";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ダークイリュージョン",1302,1,getmdnpcname("BaphometControl1-1")+"::OnKilled11";
	end;
OnKilled:
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled1";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled2";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled3";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled4";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled5";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled6";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled7";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled8";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled9";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled10";
	killmonster getmdmapname("1@cata.gat"),getmdnpcname("BaphometControl1-1")+"::OnKilled11";
	end;
OnKilled1:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"デッドリーレイス",1291,1,getmdnpcname("BaphometControl1-1")+"::OnKilled1";
	end;
OnKilled2:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"カーリッツバーグ",1132,1,getmdnpcname("BaphometControl1-1")+"::OnKilled2";
	end;
OnKilled3:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"フレームスカル",1869,1,getmdnpcname("BaphometControl1-1")+"::OnKilled3";
	end;
OnKilled4:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"エンシェントミミック",1699,1,getmdnpcname("BaphometControl1-1")+"::OnKilled4";
	end;
OnKilled5:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ゾンビマスター",1298,1,getmdnpcname("BaphometControl1-1")+"::OnKilled5";
	end;
OnKilled6:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ジェネラルスケルトン",1290,1,getmdnpcname("BaphometControl1-1")+"::OnKilled6";
	end;
OnKilled7:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ウィンドゴースト",1263,1,getmdnpcname("BaphometControl1-1")+"::OnKilled7";
	end;
OnKilled8:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ルード",1509,1,getmdnpcname("BaphometControl1-1")+"::OnKilled8";
	end;
OnKilled9:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"イビルドルイド",1117,1,getmdnpcname("BaphometControl1-1")+"::OnKilled9";
	end;
OnKilled10:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バンシー",1867,1,getmdnpcname("BaphometControl1-1")+"::OnKilled10";
	end;
OnKilled11:
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"ダークイリュージョン",1302,1,getmdnpcname("BaphometControl1-1")+"::OnKilled11";
	end;
}

1@cata.gat,3,2,0	script	BaphometControl1-2	-1,{
OnStart:
	hideoffnpc getmdnpcname("揺らめく松明#1");
	hideoffnpc getmdnpcname("揺らめく松明#2");
	hideoffnpc getmdnpcname("揺らめく松明#3");
	hideoffnpc getmdnpcname("揺らめく松明#4");
	hideoffnpc getmdnpcname("揺らめく松明#5");
	hideoffnpc getmdnpcname("揺らめく松明#6");
	hideoffnpc getmdnpcname("揺らめく松明#7");
	hideoffnpc getmdnpcname("揺らめく松明#8");
	hideoffnpc getmdnpcname("揺らめく松明#9");
	hideoffnpc getmdnpcname("揺らめく松明#10");
	hideoffnpc getmdnpcname("揺らめく松明#11");
	hideoffnpc getmdnpcname("揺らめく松明#12");

	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1291,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1291,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1291,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1132,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1117,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1132,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1117,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1132,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1291,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1117,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled";
	end;

OnKilled:
	switch(rand(5)) {
	case 0: areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled"; break;
	case 1: areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1291,1,getmdnpcname("BaphometControl1-2")+"::OnKilled"; break;
	case 2: areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1132,1,getmdnpcname("BaphometControl1-2")+"::OnKilled"; break;
	case 3: areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1117,1,getmdnpcname("BaphometControl1-2")+"::OnKilled"; break;
	case 4: areamonster getmdmapname("1@cata.gat"),0,0,0,0,"バフォメットの使徒",1869,1,getmdnpcname("BaphometControl1-2")+"::OnKilled"; break;
	}
	getitem 6002,1;
	end;
}

1@cata.gat,141,221,0	script	崩れかけの墓	844,3,3,{
	switch(BAPHO_1QUE) {
	case 0:
		mes "‐墓石から妙な空気を感じる……";
		next;
		mes "‐墓石に手をかざしてみると";
		mes "　何かの声が心に直接聞こえてきた‐";
		next;
		misceffect 71,"";
		mes "[墓石の声]";
		mes "^556B2F……………………";
		mes "ずっと……待っていた……";
		mes "君たちのような冒険者が";
		mes "再びここを訪れてくれる日を……^000000";
		next;
		menu "……誰？",-;
		mes "[墓石の声]";
		mes "^556B2F私は君たちと同じく、";
		mes "冒険者だった……";
		mes "今はこのように魂だけの";
		mes "存在になってしまったが……^000000";
		next;
		mes "[墓石の声]";
		mes "^556B2F君たちも気付いているかもしれないが、";
		mes "許されている時間があまりない。";
		mes "^FF0000あの悪魔^556B2Fは数十年間、";
		mes "力を貯めこんできた。^000000";
		next;
		mes "[墓石の声]";
		mes "^556B2F昔……私と仲間が命を賭して";
		mes "あの悪魔を地下にある";
		mes "祭壇に封印し、そこまでの通路を";
		mes "塞いでおいた。^000000";
		next;
		mes "[墓石の声]";
		mes "^556B2F私は死ぬ直前に、あるペンダントに";
		mes "自分の魂を吹き込み、こんな形だが";
		mes "延命する事ができたが、他の仲間は";
		mes "全員死んでしまった……";
		mes "そしてずっと待っていたんだ。";
		mes "君たちのような冒険者を。^000000";
		next;
		menu "私を待っていたと？",-;
		mes "[墓石の声]";
		mes "^556B2Fあの悪魔……";
		mes "^FF0000魔王バフォメット^556B2Fの力は";
		mes "我々の予想を遥かに超え、";
		mes "封印を打ち破れるほどに成長している。";
		mes "いち早く再封印を行わなければ";
		mes "あの封印が解かれるのも時間の問題だ。";
		next;
		mes "^000000[墓石の声]";
		mes "^556B2F地下への入口を開くには、";
		mes "まず私の魂を";
		mes "実体化させる必要がある。";
		mes "それができたら入口を切り開き、";
		mes "封印の再調整を行うつもりだ。^000000";
		next;
		mes "[墓石の声]";
		mes "^556B2Fまず魂の実体化のために、";
		mes "あのペンダントを探す必要がある。";
		mes "ここの階層には、いくつもの";
		mes "崩れかけの墓が存在している。";
		mes "その中の一つにペンダントがあるはず。";
		mes "皆で手分けして探して欲しい。^000000";
		viewpoint 1,86,214,1,0x00FF00;
		viewpoint 1,200,209,2,0x00FF00;
		viewpoint 1,230,195,3,0x00FF00;
		viewpoint 1,118,182,4,0x00FF00;
		viewpoint 1,193,182,5,0x00FF00;
		viewpoint 1,253,156,6,0x00FF00;
		viewpoint 1,88,154,7,0x00FF00;
		viewpoint 1,127,116,8,0x00FF00;
		viewpoint 1,90,98,9,0x00FF00;
		viewpoint 1,188,84,10,0x00FF00;
		viewpoint 1,244,42,11,0x00FF00;
		viewpoint 1,127,32,12,0x00FF00;
		viewpoint 1,267,30,13,0x00FF00;
		next;
		mes "[墓石の声]";
		mes "^556B2Fペンダントが手に入ったら";
		mes "パーティーリーダーが";
		mes "そのペンダントを私のところに";
		mes "持ってきて欲しい……";
		mes "さあ、時間がない！";
		mes "急いでくれ！^000000";
		viewpoint 1,141,221,14,0xFF89D7;
		set BAPHO_1QUE,1;
		close;
	case 1:
		mes "[墓石の声]";
		mes "^556B2F地下への入口を開くには、";
		mes "まず私の魂を";
		mes "実体化させる必要がある。";
		mes "それができたら入口を切り開き、";
		mes "封印の再調整を行うつもりだ。^000000";
		next;
		mes "[墓石の声]";
		mes "^556B2Fまず魂の実体化のために、";
		mes "あのペンダントを探す必要がある。";
		mes "ここの階層には、いくつもの";
		mes "崩れかけの墓が存在している。";
		mes "その中の一つにペンダントがあるはず。";
		mes "皆で手分けして探して欲しい。^000000";
		viewpoint 1,86,214,1,0x00FF00;
		viewpoint 1,200,209,2,0x00FF00;
		viewpoint 1,230,195,3,0x00FF00;
		viewpoint 1,118,182,4,0x00FF00;
		viewpoint 1,193,182,5,0x00FF00;
		viewpoint 1,253,156,6,0x00FF00;
		viewpoint 1,88,154,7,0x00FF00;
		viewpoint 1,127,116,8,0x00FF00;
		viewpoint 1,90,98,9,0x00FF00;
		viewpoint 1,188,84,10,0x00FF00;
		viewpoint 1,244,42,11,0x00FF00;
		viewpoint 1,127,32,12,0x00FF00;
		viewpoint 1,267,30,13,0x00FF00;
		next;
		mes "[墓石の声]";
		mes "^556B2Fペンダントが手に入ったら";
		mes "^0000FFパーティーリーダーが^556B2F";
		mes "そのペンダントを私のところに";
		mes "持ってきて欲しい……";
		mes "さあ、時間がない！";
		mes "急いでくれ！^000000";
		viewpoint 1,141,221,14,0xFF89D7;
		close;
	case 2:
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[墓石の声]";
			mes "^556B2Fそれで……";
			mes "ペンダントは見つかったか？^000000";
			next;
			if(countitem(6003) < 1) {
				mes "^000000[墓石の声]^777777";
				mes "……まだ見つかっていないようだ";
				next;
				mes "^000000[墓石の声]^777777";
				mes "パーティーメンバーが";
				mes "ペンダントを所持しているなら";
				mes "君が受け取って渡してくれ";
				close;
			}
			viewpoint 2,86,214,1,0x00FF00;
			viewpoint 2,200,209,2,0x00FF00;
			viewpoint 2,230,195,3,0x00FF00;
			viewpoint 2,118,182,4,0x00FF00;
			viewpoint 2,193,182,5,0x00FF00;
			viewpoint 2,253,156,6,0x00FF00;
			viewpoint 2,88,154,7,0x00FF00;
			viewpoint 2,127,116,8,0x00FF00;
			viewpoint 2,90,98,9,0x00FF00;
			viewpoint 2,188,84,10,0x00FF00;
			viewpoint 2,244,42,11,0x00FF00;
			viewpoint 2,127,32,12,0x00FF00;
			viewpoint 2,267,30,13,0x00FF00;
			viewpoint 2,141,221,14,0xFF89D7;
			mes "[墓石の声]";
			mes "^556B2Fそう、これだ！";
			mes "私のペンダントに違いない！^000000";
			next;
			delitem 6003,1;
			hideoffnpc getmdnpcname("先代英雄の魂#1F");
			hideonnpc getmdnpcname("崩れかけの墓");
			viewpoint 1,176,119,2,0xFF89D7;
			mes "[墓石の声]";
			mes "^556B2Fこれで魂を";
			mes "実体化させることができる。";
			mes "ここの中央にある炎の祭壇で";
			mes "君たちを待つから来るといい。^000000";
			next;
			announce "先代英雄の魂 : 君たちのおかげで僅かな時間だが肉体を取り戻すことができた。ここの中央にある炎の祭壇で君たちを待っている。",0x9,0xFFFF00;
			mes "‐聞こえていた声が少しずつ";
			mes "　小さくなっていく……‐";
			close;
		}
	default:
		mes "[墓石の声]";
		mes "^0000FF君たちの代表^556B2Fと話がしたい。";
		mes "他の人達は少し待ってくれ。^000000";
		close;
	}
	end;

OnTouch:
	if(BAPHO_1QUE == 0) {
		mes "‐^556B2Fゴゴゴ……";
		mes "　グルルル……^000000‐";
		next;
		misceffect 322;
		mes "‐墓石から妙な空気を感じる……";
		mes "　小さな声ではあるが、";
		mes "　何かを呼んでいる様な";
		mes "　気もするが……？‐";
		close;
	}
	end;
}

1@cata.gat,176,119,4	script	先代英雄の魂#1F	411,{
	switch(BAPHO_1QUE) {
	case 2:
		cutin "ins_cata_champ_n",2;
		mes "[先代英雄の魂]";
		mes "君たちのおかげで";
		mes "僅かな時間だが";
		mes "肉体を取り戻すことができた。";
		mes "色々と話もしたいが、許された";
		mes "時間があまりない。";
		next;
		mes "[先代英雄の魂]";
		mes "この肉体に留まれる時間は";
		mes "^0000FF約1時間……^000000";
		mes "地下の^FF0000大封印祭壇^000000に行くためには";
		mes "私がこれから行う儀式を手伝って";
		mes "貰わないといけない。";
		next;
		mes "[先代英雄の魂]";
		mes "では、今から君たち各自の";
		mes "やるべきことを説明するから";
		mes "よく聞いてほしい。";
		mes "まず一つ目、ここにある墓の松明で";
		mes "聖なる^0000FF火の精髄^000000を集めること。";
		next;
		mes "[先代英雄の魂]";
		mes "二つ目は、地下に入るメンバーは";
		mes "全員^0000FF使徒の証^000000を身に付けることだ。";
		next;
		cutin "ins_cata_champ_n",2;
		menu "火の精髄とは？",-;
		mes "[先代英雄の魂]";
		mes "ここをよく探してみれば、";
		mes "いたる所から揺らめく松明が";
		mes "見つかるはずだ。";
		mes "この松明は、バフォメットの力を";
		mes "抑制させるために先代の修道士たちが";
		mes "雷神トールの火で作ったものだ。";
		next;
		mes "[先代英雄の魂]";
		mes "地下の封印された門を開くためには、";
		mes "この雷神の力が秘められている、";
		mes "^0000FF火の精髄^000000が必要なのだ。";
		mes "まずは松明から ^0000FF火の精髄^000000を";
		mes "^FF000010個^000000集めてくれ。";
		next;
		mes "[先代英雄の魂]";
		mes "ひとつ、気を付けてほしいことがある。";
		mes "松明は選ばれた継承者にのみ";
		mes "反応するようになっている。";
		mes "もし選ばれた者でない者が触れれば";
		mes "一瞬にして大変なことになる。";
		next;
		mes "[先代英雄の魂]";
		mes "これから君たちの代表者ひとりに";
		mes "継承者の印を刻印しよう。";
		mes "^0000FF火の精髄^000000を集めるのは";
		mes "代表ひとりで行うのだ。";
		next;
		menu "使徒の証とは？",-;
		mes "[先代英雄の魂]";
		mes "当時、我らの力だけではバフォメットを";
		mes "倒すことができなかった。";
		mes "数え切れないほどの冒険者たちの";
		mes "尊い命が奪われ、やっとの思いで";
		mes "地下に封印することができたのだ。";
		next;
		mes "[先代英雄の魂]";
		mes "だがバフォメットは成長し続けた。";
		mes "どんどん強力になる魔の力のせいで";
		mes "いつのまにか墓地に";
		mes "悪魔が現れはじめたのだ。";
		next;
		mes "[先代英雄の魂]";
		mes "やがて思考能力を持った";
		mes "悪魔も現れはじめた。";
		mes "使徒という名で、バフォメットの";
		mes "忠実な僕となっている。";
		next;
		mes "[先代英雄の魂]";
		mes "使徒たちは、バフォメットの力を利用し";
		mes "自分たちの複製を作り続けている。";
		mes "今見えているモンスターがそうだ。";
		next;
		mes "[先代英雄の魂]";
		mes "本体の使徒は複製とは違い";
		mes "^0000FF使徒の証^000000と言うものを持っている。";
		mes "本体を狙えば、これを入手することが";
		mes "出来るだろう。";
		next;
		mes "[先代英雄の魂]";
		mes "君たち全員が^0000FF使徒の証^000000を";
		mes "手に入れる必要がある。";
		mes "まあ、一番簡単な方法は";
		mes "目に映ったモンスターを";
		mes "全て倒すことだろうな。";
		next;
		menu "私は何をすれば？",-;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[先代英雄の魂]";
			mes "君はこのパーティの代表だな。";
			mes "では、";
			mes "松明から^0000FF火の精髄^000000を";
			mes "10個集めてくるのだ。";
			next;
			mes "[先代英雄の魂]";
			mes "これから君に継承者の印を";
			mes "刻印する。";
			mes "^0000FF火の精髄^000000は君一人で";
			mes "集めなくてはならない。";
			next;
			misceffect 152,"";
			mes "[先代英雄の魂]";
			mes "あとは^0000FF使徒の証^000000が必要だ。";
			mes "仲間から貰うか、自分でモンスターを";
			mes "倒して手に入れておくんだ。";
			next;
			mes "[先代英雄の魂]";
			mes "では準備が整ったら声をかけてくれ。";
			mes "君たちの準備ができ次第、";
			mes "封印している門を開く";
			mes "儀式をはじめる。";
			next;
			cutin "ins_cata_champ_n",2;
			mes "[先代英雄の魂]";
			mes "準備はいいか？";
			mes "では今から封印している門を開く";
			mes "儀式をはじめる。";
			next;
			mes "[先代英雄の魂]";
			mes "繰り返しになるが、";
			mes "私が実体化していられる時間は";
			mes "^0000FF約1時間^000000しかない。";
			mes "各自1時間以内に役割を果たしてくれ。";
			viewpoint 1,267,210,1,0x00FF00;
			viewpoint 1,267,154,3,0x00FF00;
			viewpoint 1,157,139,4,0x00FF00;
			viewpoint 1,193,138,5,0x00FF00;
			viewpoint 1,193,102,6,0x00FF00;
			viewpoint 1,157,102,7,0x00FF00;
			viewpoint 1,113,112,8,0x00FF00;
			viewpoint 1,253,56,9,0x00FF00;
			viewpoint 1,239,56,10,0x00FF00;
			viewpoint 1,71,42,11,0x00FF00;
			viewpoint 1,155,14,12,0x00FF00;
			viewpoint 1,85,182,13,0x00FF00;
			set BAPHO_1QUE,3;
			initnpctimer;
			donpcevent getmdnpcname("BaphometControl1-2")+"::OnStart";
		} else {
			mes "[先代英雄の魂]";
			mes "君はバフォメットの使徒を倒し、";
			mes "^0000FF使徒の証^000000を手に入れるのだ。";
			next;
			mes "[先代英雄の魂]";
			mes "使徒は見た目では区別が付かない。";
			mes "目に映ったモンスターを";
			mes "全て倒すのもいい方法だろう。";
			next;
			mes "[先代英雄の魂]";
			mes "では準備が整ったら声をかけてくれ。";
			mes "君たちの準備ができ次第、";
			mes "封印している門を開く";
			mes "儀式をはじめる。";
			next;
			cutin "ins_cata_champ_n",2;
			mes "[先代英雄の魂]";
			mes "準備はいいか？";
			mes "では今から封印している門を開く";
			mes "儀式をはじめる。";
			next;
			mes "[先代英雄の魂]";
			mes "繰り返しになるが、";
			mes "私が実体化していられる時間は";
			mes "^0000FF約1時間^000000しかない。";
			mes "各自1時間以内に役割を果たしてくれ。";
		}
		close2;
		cutin "ins_cata_champ_n",255;
		end;
	case 3:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			cutin "ins_cata_champ_n",2;
			mes "[先代英雄の魂]";
			mes "^0000FF使徒の証^000000は手に入れたか？";
			next;
			if(countitem(6002) < 1) {
				mes "[先代英雄の魂]";
				mes "まだじゃないか。";
				mes "君が準備する物は";
				mes "^0000FF使徒の証^000000だ。";
			} else {
				mes "[先代英雄の魂]";
				mes "……よし、いいだろう。";
				mes "では、他の皆の状態をもう一度確認し、";
				mes "準備ができたら私に話しかけてくれ。";
			}
			close2;
			cutin "ins_cata_champ_n",255;
			end;
		}
		cutin "ins_cata_champ_n",2;
		mes "[先代英雄の魂]";
		mes "^0000FF火の精髄^00000010個と";
		mes "^0000FF使徒の証^000000は準備できたか？";
		next;
		if((countitem(6001) < 10) || (countitem(6002) < 1)) {
			mes "[先代英雄の魂]";
			mes "まだじゃないか。";
			mes "君が準備する物は";
			mes "^0000FF火の精髄^000000 10個と";
			mes "^0000FF使徒の証^000000だ。";
		} else {
			viewpoint 2,267,210,1,0x00FF00;
			viewpoint 2,267,210,2,0x00FF00;
			viewpoint 2,267,154,3,0x00FF00;
			viewpoint 2,157,139,4,0x00FF00;
			viewpoint 2,193,138,5,0x00FF00;
			viewpoint 2,193,102,6,0x00FF00;
			viewpoint 2,157,102,7,0x00FF00;
			viewpoint 2,113,112,8,0x00FF00;
			viewpoint 2,253,56,9,0x00FF00;
			viewpoint 2,239,56,10,0x00FF00;
			viewpoint 2,71,42,11,0x00FF00;
			viewpoint 2,155,14,12,0x00FF00;
			viewpoint 2,85,182,13,0x00FF00;
			delitem 6001,countitem(6001);
			set BAPHO_1QUE,4;
			mes "[先代英雄の魂]";
			mes "……よし、いいだろう。";
			mes "では、他の皆の状態をもう一度確認し、";
			mes "準備ができたら私に話しかけてくれ。";
		}
		close2;
		cutin "ins_cata_champ_n",255;
		end;
	case 4:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			cutin "ins_cata_champ_n",2;
			mes "[先代英雄の魂]";
			mes "……これは君たち……";
			mes "新たな時代の英雄の戦いだ。";
			mes "私も後で何か手伝う方法を探してみる。";
			next;
			mes "[先代英雄の魂]";
			mes "さあ、行くんだ！";
			mes "冒険者たちよ！";
			close2;
			cutin "ins_cata_champ_n",255;
			end;
		}
		cutin "ins_cata_champ_n",2;
		mes "[先代英雄の魂]";
		mes "準備は済んだか？";
		mes "私もたった今儀式を終えたところだ。";
		mes "^0000FF使徒の証^000000はちゃんと持っているか？";
		mes "門を通るには絶対必要だからな。";
		next;
		setpartyinmap BAPHO_1QUE,5;
		hideonnpc getmdnpcname("封印魔法陣#0");
		hideonnpc getmdnpcname("封印魔法陣#2");
		hideonnpc getmdnpcname("封印魔法陣#4");
		hideonnpc getmdnpcname("封印魔法陣#8");
		hideonnpc getmdnpcname("封印魔法陣#10");
		hideonnpc getmdnpcname("先代英雄の魂#2F");
		hideoffnpc getmdnpcname("BaphometGate");
		donpcevent getmdnpcname("BaphometControl1-1")+"::OnKilled";
		mes "[先代英雄の魂]";
		mes "……これで^FF0000大封印祭壇^000000に繋がる";
		mes "門が開いた。";
		mes "位置はこの階の南東の角だ。";
		next;
		mes "[先代英雄の魂]";
		mes "……これは君たち……";
		mes "新たな時代の英雄の戦いだ。";
		mes "私も後で何か手伝う方法を探してみる。";
		next;
		mes "[先代英雄の魂]";
		mes "さあ、行くんだ！";
		mes "冒険者たちよ！";
		viewpoint 1,281,12,3,0xFF89D7;
		announce "先代英雄の魂 : 地下大封印祭壇にいく門を開放した。墓の一番南東付近だ。急げ！",0x9,0xFFFF00;
		close2;
		cutin "ins_cata_champ_n",255;
		end;
	case 5:
		cutin "ins_cata_champ_n",2;
		mes "[先代英雄の魂]";
		mes "なにをボサっとしてる！";
		mes "^FF0000大封印祭壇^000000への門を開いた！";
		mes "すぐ下りていくんだ。";
		mes "入口はこの階の南東の角だ！";
		viewpoint 1,281,12,3,0xFF89D7;
		close2;
		cutin "ins_cata_champ_n",255;
		end;
	default:
		cutin "ins_cata_champ_n",2;
		mes "[先代英雄の魂]";
		mes "……君と話すことはできない";
		close2;
		cutin "ins_cata_champ_n",255;
		end;
	}

OnTimer1800000:
	announce "先代英雄の魂 : 時間があまり残っていない。急ぐのだ！",0x9,0xFFFF00;
	end;

OnTimer2400000:
	announce "先代英雄の魂 : 肉体と魂がどんどん離れようとしている……急ぐのだ。",0x9,0xFFFF00;
	end;

OnTimer3000000:
	announce "先代英雄の魂 : 全てが終ってしまった……次を期待するしかないのか……",0x9,0xFFFF00;
	end;

OnTimer3050000:
	announce "先代英雄の魂 : 失敗だ。だが、まだチャンスはある。より経験を積んで再挑戦するんだ！",0x9,0xFFFF00;
	end;

OnTimer3100000:
	announce "大封印祭壇の封印の解除に失敗しました。",0x9,0xFF1094;
	end;

OnTimer3500000:
	mapwarp getmdmapname("1@cata.gat"),"monk_test",310,150;
	stopnpctimer;
	end;
}

1@cata.gat,281,12,0	script	BaphometGate	45,1,1,{
	if(countitem(6002) < 1) {
		mes "[先代英雄の魂]";
		mes "使徒の証はどうした？";
		mes "使徒の証を持っていないと";
		mes "^FF0000大封印祭壇^000000へ行けないぞ";
		close;
	}
	delitem 6002,countitem(6002);
	warp getmdmapname("2@cata.gat"),80,144;
	end;
}

1@cata.gat,86,214,0	script	崩れかけの墓#1F_1T	844,{
	if(BAPHO_1QUE != 1) {
		mes "‐倒れかけた墓石の下には";
		mes "　何もなかった‐";
		close;
	}
	getitem 6003,1;
	setpartyinmap BAPHO_1QUE,2;
	mes "‐倒れかけた墓石の下に";
	mes "　光る小さい物が見えた‐";
	next;
	mes "[" + strcharinfo(0) + "]";
	mes "このペンダントに違いない。";
	close;
}

1@cata.gat,86,214,0	script	崩れかけの墓#1F_1F	844,{
	mes "‐倒れかけた墓石の下には";
	mes "　何もなかった‐";
	close;
}

1@cata.gat,200,209,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_2T	844
1@cata.gat,200,209,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_2F	844
1@cata.gat,230,195,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_3T	844
1@cata.gat,230,195,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_3F	844
1@cata.gat,118,182,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_4T	844
1@cata.gat,118,182,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_4F	844
1@cata.gat,193,182,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_5T	844
1@cata.gat,193,182,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_5F	844
1@cata.gat,253,156,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_6T	844
1@cata.gat,253,156,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_6F	844
1@cata.gat,88,154,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_7T	844
1@cata.gat,88,154,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_7F	844
1@cata.gat,127,116,0	duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_8T	844
1@cata.gat,127,116,0	duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_8F	844
1@cata.gat,90,98,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_9T	844
1@cata.gat,90,98,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_9F	844
1@cata.gat,188,84,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_10T	844
1@cata.gat,188,84,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_10F	844
1@cata.gat,244,42,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_11T	844
1@cata.gat,244,42,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_11F	844
1@cata.gat,127,32,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_12T	844
1@cata.gat,127,32,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_12F	844
1@cata.gat,267,30,0		duplicate(崩れかけの墓#1F_1T)	崩れかけの墓#1F_13T	844
1@cata.gat,267,30,0		duplicate(崩れかけの墓#1F_1F)	崩れかけの墓#1F_13F	844

1@cata.gat,267,210,0	script	揺らめく松明#1	844,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		if((BAPHO_1QUE == 3) && (countitem(6001) < 10)) {
			mes "‐真っ赤に燃え上がる";
			mes "　凄まじい勢いの";
			mes "　巨大な松明が揺らめいている‐";
			next;
			mes "‐その威力に圧倒され、思わず";
			mes "　後ずさりしそうになったが、";
			mes "　勇気を出して松明に手を伸ばす‐";
			next;
			misceffect 152,"";
			getitem 6001,1;
			mes "‐先代英雄の魂から貰った";
			mes "　継承者の印が光りだし、";
			mes "　松明から小さい結晶が手の平に";
			mes "　落ちてきた‐";
			hideonnpc strnpcinfo(0);
			close;
		} else {
			mes "‐これ以上火の精髄を";
			mes "　集める必要はなさそうだ‐";
			close;
		}
	} else {
		mes "‐真っ赤に燃え上がる";
		mes "　凄まじい勢いの";
		mes "　巨大な松明が揺らめいている‐";
		next;
		mes "[正体不明の声]";
		mes "^C71585そなたは継承者ではない……";
		mes "その不浄なる手で";
		mes "神聖なる火の精髄を";
		mes "汚すことなかれ……^000000";
		misceffect 50,"";
		percentheal -50,0;
		close;
	}
}

1@cata.gat,85,182,0		duplicate(揺らめく松明#1)	揺らめく松明#2	844
1@cata.gat,267,154,0	duplicate(揺らめく松明#1)	揺らめく松明#3	844
1@cata.gat,157,139,0	duplicate(揺らめく松明#1)	揺らめく松明#4	844
1@cata.gat,193,138,0	duplicate(揺らめく松明#1)	揺らめく松明#5	844
1@cata.gat,193,102,0	duplicate(揺らめく松明#1)	揺らめく松明#6	844
1@cata.gat,157,102,0	duplicate(揺らめく松明#1)	揺らめく松明#7	844
1@cata.gat,113,112,0	duplicate(揺らめく松明#1)	揺らめく松明#8	844
1@cata.gat,253,56,0		duplicate(揺らめく松明#1)	揺らめく松明#9	844
1@cata.gat,239,56,0		duplicate(揺らめく松明#1)	揺らめく松明#10	844
1@cata.gat,71,42,0		duplicate(揺らめく松明#1)	揺らめく松明#11	844
1@cata.gat,155,14,0		duplicate(揺らめく松明#1)	揺らめく松明#12	844

//============================================================
// 封印された神殿2F
//------------------------------------------------------------
2@cata.gat,80,144,0	script	BaphometControl2-1	139,3,3,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[先代英雄の魂]";
		mes "ここが^FF0000大封印祭壇^000000だ。";
		mes "まずは中央の祭壇に向かってくれ！";
		viewpoint 0,79,65,4,0x00FF00;
		initnpctimer;
		hideonnpc getmdnpcname("BaphometControl2-1");
		close;
	}
	end;

OnTimer10000:
	announce "魔王バフォメット : 虫けらのような人間ども……また我を邪魔するつもりか……",0x9,0xdb7093;
	end;
OnTimer14000:
	announce "バフォメットの使徒 : 人間だ！　邪魔な人間どもが侵入した！",0x9,0xFFFF00;
	end;
OnTimer18000:
	announce "バフォメットの使徒 : 人間ドモヲ殺セ！　ゴ主人様ノ復活ニ邪魔ナ存在ハ全テ潰セ！",0x9,0xFFFF00;
	end;
OnTimer22000:
	announce "バフォメットの使徒 : 各封印の解体を急げ！　間もなくご主人様がお見えになる……",0x9,0xFFFF00;
	stopnpctimer;
	end;
}

2@cata.gat,50,67,0	script	BaphometLeftSlave	139,5,5,{
	announce "バフォメットの使徒 : 人間ドモヲ殺セ！　ゴ主人様ノ復活ニ邪魔ナ存在ハ全テ消セ！",0x9,0xFFFF00;
	monster getmdmapname("2@cata.gat"),55,67,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),51,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),58,67,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),53,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),54,67,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),55,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),56,67,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),58,66,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),56,66,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),60,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),59,66,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),54,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),55,66,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),56,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),50,65,"バフォメットの使徒",1867,1;
	monster getmdmapname("2@cata.gat"),61,65,"バフォメットの使徒",1292,1;
	hideonnpc getmdnpcname("BaphometLeftSlave");
	end;
}

2@cata.gat,109,67,0	script	BaphometRightSlave	139,5,5,{
	announce "バフォメットの使徒 : 人間ドモヲ殺セ！　ゴ主人様ノ復活ニ邪魔ナ存在ハ全テ消セ！",0x9,0xFFFF00;
	monster getmdmapname("2@cata.gat"),105,67,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),104,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),107,67,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),106,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),102,67,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),103,67,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),103,67,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),109,66,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),108,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),101,66,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),106,66,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),102,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),104,66,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),103,66,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),109,65,"バフォメットの使徒",1867,1;
	monster getmdmapname("2@cata.gat"),108,65,"バフォメットの使徒",1292,1;
	hideonnpc getmdnpcname("BaphometRightSlave");
	end;
}

2@cata.gat,79,39,0	script	BaphometDownSlave	139,5,5,{
	announce "バフォメットの使徒 : 人間ドモヲ殺セ！　ゴ主人様ノ復活ニ邪魔ナ存在ハ全テ消セ！",0x9,0xFFFF00;
	monster getmdmapname("2@cata.gat"),78,41,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),79,42,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),78,46,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),81,41,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),81,42,"バフォメットの使徒",1869,1;
	monster getmdmapname("2@cata.gat"),79,43,"バフォメットの使徒",1291,1;
	monster getmdmapname("2@cata.gat"),77,40,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),79,41,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),79,42,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),79,43,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),79,48,"バフォメットの使徒",1117,1;
	monster getmdmapname("2@cata.gat"),78,49,"バフォメットの使徒",1132,1;
	monster getmdmapname("2@cata.gat"),78,41,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),74,42,"バフォメットの使徒",1292,1;
	monster getmdmapname("2@cata.gat"),72,48,"バフォメットの使徒",1867,1;
	monster getmdmapname("2@cata.gat"),72,38,"バフォメットの使徒",1292,1;
	hideonnpc getmdnpcname("BaphometDownSlave");
	end;
}

2@cata.gat,79,81,0	script	封印魔法陣#0	844,{
	if(!checkquest(3041) || checkquest(3041) & 0x2) {
		if(checkquest(3041) & 0x2)
			delquest 3041;
		misceffect 87;
		hideonnpc getmdnpcname("封印魔法陣#0");
		areamobuseskill getmdmapname("2@cata.gat"),74,76,84,86,1929,686,1,0,0,26,0;
		percentheal -50,0;
		sc_start Eff_Stone,20000,0;
		setquest 3041;
		announce "封印祭壇に魔力が注入され、封印が発動しました。",0x9,0x87ceeb;
		mes "‐封印祭壇で魔力を注入すると、";
		mes "　弱まった封印祭壇の力が";
		mes "　再び戻ってくるのが感じられた‐";
		next;
		mes "‐しかし封印祭壇で魔力を";
		mes "　消耗したため、";
		mes "　今から3分間";
		mes "　魔力を注入できなくなった‐";
		close;
	}
	else {
		misceffect 193,"";
		percentheal -50,0;
		sc_start Eff_Stone,30000,0;
		mes "‐まだ封印祭壇で消耗した魔力が";
		mes "　戻ってきていない。";
		mes "　封印祭壇に魔力は奪われたが、";
		mes "　封印の力は戻っていないようだ‐";
		close;
	}
	end;
}

2@cata.gat,123,109,0	script	封印魔法陣#2	844,{
	if(!checkquest(3041) || checkquest(3041) & 0x2) {
		if(checkquest(3041) & 0x2)
			delquest 3041;
		misceffect 87;
		hideonnpc getmdnpcname("封印魔法陣#2");
		areamobuseskill getmdmapname("2@cata.gat"),118,104,128,119,1929,686,1,0,0,26,0;
		percentheal -50,0;
		sc_start Eff_Stone,20000,0;
		setquest 3041;
		announce "封印祭壇に魔力が注入され、封印が発動しました。",0x9,0x87ceeb;
		mes "‐封印祭壇で魔力を注入すると、";
		mes "　弱まった封印祭壇の力が";
		mes "　再び戻ってくるのが感じられた‐";
		next;
		mes "‐しかし封印祭壇で魔力を";
		mes "　消耗したため、";
		mes "　今から3分間";
		mes "　魔力を注入できなくなった‐";
		close;
	}
	else {
		misceffect 193,"";
		percentheal -50,0;
		sc_start Eff_Stone,30000,0;
		mes "‐まだ封印祭壇で消耗した魔力が";
		mes "　戻ってきていない。";
		mes "　封印祭壇に魔力は奪われたが、";
		mes "　封印の力は戻っていないようだ‐";
		close;
	}
	end;
}

2@cata.gat,123,22,0	script	封印魔法陣#4	844,{
	if(!checkquest(3041) || checkquest(3041) & 0x2) {
		if(checkquest(3041) & 0x2)
			delquest 3041;
		misceffect 87;
		hideonnpc getmdnpcname("封印魔法陣#4");
		areamobuseskill getmdmapname("2@cata.gat"),118,17,128,27,1929,686,1,0,0,26,0;
		percentheal -50,0;
		sc_start Eff_Stone,20000,0;
		setquest 3041;
		announce "封印祭壇に魔力が注入され、封印が発動しました。",0x9,0x87ceeb;
		mes "‐封印祭壇で魔力を注入すると、";
		mes "　弱まった封印祭壇の力が";
		mes "　再び戻ってくるのが感じられた‐";
		next;
		mes "‐しかし封印祭壇で魔力を";
		mes "　消耗したため、";
		mes "　今から3分間";
		mes "　魔力を注入できなくなった‐";
		close;
	}
	else {
		misceffect 193,"";
		percentheal -50,0;
		sc_start Eff_Stone,30000,0;
		mes "‐まだ封印祭壇で消耗した魔力が";
		mes "　戻ってきていない。";
		mes "　封印祭壇に魔力は奪われたが、";
		mes "　封印の力は戻っていないようだ‐";
		close;
	}
	end;
}

2@cata.gat,35,21,0	script	封印魔法陣#8	844,{
	if(!checkquest(3041) || checkquest(3041) & 0x2) {
		if(checkquest(3041) & 0x2)
			delquest 3041;
		misceffect 87;
		hideonnpc getmdnpcname("封印魔法陣#8");
		areamobuseskill getmdmapname("2@cata.gat"),30,16,40,26,1929,686,1,0,0,26,0;
		percentheal -50,0;
		sc_start Eff_Stone,20000,0;
		setquest 3041;
		announce "封印祭壇に魔力が注入され、封印が発動しました。",0x9,0x87ceeb;
		mes "‐封印祭壇で魔力を注入すると、";
		mes "　弱まった封印祭壇の力が";
		mes "　再び戻ってくるのが感じられた‐";
		next;
		mes "‐しかし封印祭壇で魔力を";
		mes "　消耗したため、";
		mes "　今から3分間";
		mes "　魔力を注入できなくなった‐";
		close;
	}
	else {
		misceffect 193,"";
		percentheal -50,0;
		sc_start Eff_Stone,30000,0;
		mes "‐まだ封印祭壇で消耗した魔力が";
		mes "　戻ってきていない。";
		mes "　封印祭壇に魔力は奪われたが、";
		mes "　封印の力は戻っていないようだ‐";
		close;
	}
	end;
}

2@cata.gat,35,109,0	script	封印魔法陣#10	844,{
	if(!checkquest(3041) || checkquest(3041) & 0x2) {
		if(checkquest(3041) & 0x2)
			delquest 3041;
		misceffect 87;
		hideonnpc getmdnpcname("封印魔法陣#10");
		areamobuseskill getmdmapname("2@cata.gat"),30,104,40,114,1929,686,1,0,0,26,0;
		percentheal -50,0;
		sc_start Eff_Stone,20000,0;
		setquest 3041;
		announce "封印祭壇に魔力が注入され、封印が発動しました。",0x9,0x87ceeb;
		mes "‐封印祭壇で魔力を注入すると、";
		mes "　弱まった封印祭壇の力が";
		mes "　再び戻ってくるのが感じられた‐";
		next;
		mes "‐しかし封印祭壇で魔力を";
		mes "　消耗したため、";
		mes "　今から3分間";
		mes "　魔力を注入できなくなった‐";
		close;
	}
	else {
		misceffect 193,"";
		percentheal -50,0;
		sc_start Eff_Stone,30000,0;
		mes "‐まだ封印祭壇で消耗した魔力が";
		mes "　戻ってきていない。";
		mes "　封印祭壇に魔力は奪われたが、";
		mes "　封印の力は戻っていないようだ‐";
		close;
	}
	end;
}

2@cata.gat,79,65,0	script	大封印祭壇#ss	844,{
	if((BAPHO_1QUE == 5) && (getpartyleader(getcharid(1)) == strcharinfo(0))) {
		mes "‐紫色に輝く";
		mes "　巨大な封印祭壇の下に";
		mes "　言葉にし難い程の凄まじい魔の気配が";
		mes "　蠢いている……‐";
		next;
		mes "‐今にも何かが爆発しそうな";
		mes "　雰囲気だ‐";
		next;
		mes "‐封印祭壇の床が大きく揺れ出し、";
		mes "　魔の激流が襲ってくる！‐";
		next;
		misceffect 92;
		misceffect 92;
		mes "[" +strcharinfo(0)+ "]";
		if(Sex)
			mes "みんな、気をつけるんだ！";
		else
			mes "みんな、気をつけて！";
		mes "何かが近寄ってくる!!";
		setpartyinmap BAPHO_1QUE,6;
		initnpctimer;
		hideonnpc getmdnpcname("大封印祭壇#ss");
		close;
	}
	mes "‐紫色に輝く";
	mes "　巨大な封印祭壇の下に";
	mes "　言葉にし難い程の凄まじい魔の気配が";
	mes "　蠢いている……‐";
	next;
	mes "‐今にも何かが爆発しそうな";
	mes "　雰囲気だ‐";
	close;

OnTimer2000:
	announce "先代英雄の魂 : 大変だ！　大封印祭壇の力が弱くなっていく……このままでは魔王バフォメットが出てくるのも時間の問題だ。",0x9,0xFFFF00;
	end;
OnTimer7000:
	announce "魔王バフォメット : フフフ……もう手遅れだ、人間ども。じきにお前らには死が訪れるであろう……",0x9,0xdb7093;
	end;
OnTimer12000:
	announce "魔王バフォメット : ハッハッハ！　ここではお前らの攻撃なんぞ、何の役にも立たん！　大人しく死を受け入れるがいい！",0x9,0xdb7093;
	donpcevent getmdnpcname("BaphometControl2-2")+"::OnStart";
	donpcevent getmdnpcname("BaphometControl2-3")+"::OnStart";
	stopnpctimer;
	end;
}

2@cata.gat,80,63,4	script	先代英雄の魂#2F	411,{
	cutin "ins_cata_champ_s",2;
	if(checkquest(3041)) delquest 3041;
	mes "[先代英雄の魂]";
	mes "よくやってくれた。";
	mes "私の子孫たちよ……";
	mes "君たちは、私と私の仲間の願いを";
	mes "叶えてくれた……";
	mes "本当にありがとう……";
	next;
	mes "[先代英雄の魂]";
	mes "だが、これで全てが";
	mes "終ったわけではない……";
	mes "しかし、君たちのような立派な";
	mes "冒険者たちがこの地にいると";
	mes "分かった以上……";
	mes "私の役目もここまでだろう……";
	next;
	switch(select("神殿の外に出たいです","会話をやめる")) {
	case 1:
		mes "[先代英雄の魂]";
		mes "よかろう。";
		mes "では、君たちを無事にここから";
		mes "出してあげよう。";
		next;
		mes "[先代英雄の魂]";
		mes "一つお願いがあるんだが……";
		mes "外のパトリックに安否を伝えてほしい。";
		mes "では私の子孫達よ……";
		mes "これからも悪に屈せず";
		mes "堂々と生きていってくれ。";
		close2;
		set BAPHO_1QUE,0;
		cutin "ins_cata_champ_s",255;
		warp "monk_test",310,150;
		end;
	case 2:
		// 未調査
		mes "[先代英雄の魂]";
		mes "そうか。";
		mes "だが、ここに長く留まる";
		mes "ことはできないぞ。";
		close2;
		cutin "ins_cata_champ_s",255;
		end;
	}
}

2@cata.gat,3,3,0	script	BaphometControl2-2	-1,{
OnStart:
	donpcevent getmdnpcname("BaphometSlaveTimer")+"::OnStart";
	monster getmdmapname("2@cata.gat"),79,64,"魔王バフォメット",1929,1,getmdnpcname("BaphometControl2-2")+"::OnMyMobDead";
	end;

OnMyMobDead:
	setpartyinmap BAPHO_1QUE,7;
	announce "魔王バフォメット : グオオオオォォ!!　こ、こんなはずでは……！　我が……この我が再び虫けらのような人間にやられる……だと……!!",0x9,0xdb7093;
	hideoffnpc getmdnpcname("先代英雄の魂#2F");
	hideonnpc getmdnpcname("BaphometDownSlave");
	hideonnpc getmdnpcname("BaphometLeftSlave");
	hideonnpc getmdnpcname("BaphometRightSlave");
	donpcevent getmdnpcname("BaphometTimer2")+"::OnClose";
	stopnpctimer getmdnpcname("BaphometSlaveTimer");
	hideonnpc;
	end;
}

2@cata.gat,2,2,0	script	BaphometControl2-3	-1,{
OnStart:
	initnpctimer;
	end;

OnTimer8000:
	announce "先代英雄の魂 : 慌てるな、私の子孫たちよ。魔王バフォメットの無敵化は一次的な現象にすぎない。",0x9,0xFFFF00;
	end;

OnTimer12000:
	announce "先代英雄の魂 : 今から私が言う方向の封印祭壇に行き、魔力を注入し、封印を完成させるのだ。",0x9,0xFFFF00;
	end;

OnTimer16000:
	announce "先代英雄の魂 : 魔力が注入され、封印が再び力を取り戻した時、魔王バフォメットの力は弱まるだろう。",0x9,0xFFFF00;
	end;

OnTimer20000:
	announce "先代英雄の魂 : ただし、魔力を注入するときは封印の所まで魔王バフォメットを連れていかなければならない。必ず魔王バフォメットを誘いながら封印を完成させなければいけないのだ。",0x9,0xFFFF00;
	end;

OnTimer24000:
	announce "先代英雄の魂 : 魔王バフォメットの力が完全になるまでもう1時間しか残っていない。時間が過ぎると封印祭壇は何の役にも立たなくなる。",0x9,0xFFFF00;
	end;

OnTimer28000:
	announce "魔王バフォメット : 無駄だ！　そんな貧弱な封印など、何度でも潰してやる。一人も生かしては返さぬぞ！",0x9,0xdb7093;
	end;

OnTimer32000:
	announce "先代英雄の魂 : 奴の言葉に耳を貸すな！　中央の封印祭壇の魔力が弱くなってきた……！　急いで奴を誘い出し、中央の封印祭壇に魔力を注入するのだ。",0x9,0xFFFF00;
	hideoffnpc getmdnpcname("封印魔法陣#0");
	hideonnpc getmdnpcname("封印魔法陣#2");
	hideonnpc getmdnpcname("封印魔法陣#4");
	hideonnpc getmdnpcname("封印魔法陣#8");
	hideonnpc getmdnpcname("封印魔法陣#10");
	donpcevent getmdnpcname("BaphometTimer1")+"::OnStart";
	donpcevent getmdnpcname("BaphometTimer2")+"::OnStart";
	stopnpctimer;
	end;
}

2@cata.gat,4,2,0	script	BaphometSlaveTimer	-1,{
OnStart:
	initnpctimer;
	end;

OnTimer300000:
	hideoffnpc getmdnpcname("BaphometDownSlave");
	hideoffnpc getmdnpcname("BaphometLeftSlave");
	hideoffnpc getmdnpcname("BaphometRightSlave");
	initnpctimer;
	end;
}

2@cata.gat,3,1,0	script	BaphometTimer2	-1,{
OnStart:
	initnpctimer;
	end;

OnClose:
	stopnpctimer;
	hideonnpc getmdnpcname("封印魔法陣#0");
	hideonnpc getmdnpcname("封印魔法陣#2");
	hideonnpc getmdnpcname("封印魔法陣#4");
	hideonnpc getmdnpcname("封印魔法陣#8");
	hideonnpc getmdnpcname("封印魔法陣#10");
	stopnpctimer getmdnpcname("BaphometTimer1");
	end;

OnTimer3600000:
	announce "魔王バフォメット : グハハハハ……これからは封印祭壇ごときでは我を抑えることなど出来ぬ。大人しく死を待つがいい！",0x9,0xdb7093;
	end;

OnTimer3605000:
	announce "先代英雄の魂 : これ以上封印祭壇の魔力では魔王バフォメットを抑える事ができない……もはや成すすべはないのか……",0x9,0xFFFF00;
	donpcevent getmdnpcname("BaphometTimer2")+"::OnClose";
	end;
}

2@cata.gat,3,2,0	script	BaphometTimer1	-1,{
OnStart:
	initnpctimer;
	end;

OnTimer70000:
	switch(rand(1,5)) {
	case 1:
		announce "先代英雄の魂 : 中央の封印祭壇の魔力が弱くなってきた……！　急いで中央の封印祭壇に魔王バフォメットを誘い出した状態で魔力を注入するんだ。",0x9,0xFFFF00;
		hideoffnpc getmdnpcname("封印魔法陣#0");
		hideonnpc getmdnpcname("封印魔法陣#2");
		hideonnpc getmdnpcname("封印魔法陣#4");
		hideonnpc getmdnpcname("封印魔法陣#8");
		hideonnpc getmdnpcname("封印魔法陣#10");
		break;
	case 2:
		announce "先代英雄の魂 : 北東方向にある封印祭壇の魔力が弱くなってきた。急いで北東方向にある封印祭壇に魔王バフォメットを誘い出した状態で魔力を注入するんだ。",0x9,0xFFFF00;
		hideonnpc getmdnpcname("封印魔法陣#0");
		hideoffnpc getmdnpcname("封印魔法陣#2");
		hideonnpc getmdnpcname("封印魔法陣#4");
		hideonnpc getmdnpcname("封印魔法陣#8");
		hideonnpc getmdnpcname("封印魔法陣#10");
		break;
	case 3:
		announce "先代英雄の魂 : 南東方向にある封印祭壇の魔力が弱くなってきた。急いで南東方向にある封印祭壇に魔王バフォメットを誘い出した状態で魔力を注入するんだ。",0x9,0xFFFF00;
		hideonnpc getmdnpcname("封印魔法陣#0");
		hideonnpc getmdnpcname("封印魔法陣#2");
		hideoffnpc getmdnpcname("封印魔法陣#4");
		hideonnpc getmdnpcname("封印魔法陣#8");
		hideonnpc getmdnpcname("封印魔法陣#10");
		break;
	case 4:
		announce "先代英雄の魂 : 南西方向にある封印祭壇の魔力が弱くなってきた。急いで南西方向にある封印祭壇に魔王バフォメットを誘い出した状態で魔力を注入するんだ。",0x9,0xFFFF00;
		hideonnpc getmdnpcname("封印魔法陣#0");
		hideonnpc getmdnpcname("封印魔法陣#2");
		hideonnpc getmdnpcname("封印魔法陣#4");
		hideoffnpc getmdnpcname("封印魔法陣#8");
		hideonnpc getmdnpcname("封印魔法陣#10");
		break;
	case 5:
		announce "先代英雄の魂 : 北西方向にある封印祭壇の魔力が弱くなってきた。急いで北西方向にある封印祭壇に魔王バフォメットを誘い出した状態で魔力を注入するんだ。",0x9,0xFFFF00;
		hideonnpc getmdnpcname("封印魔法陣#0");
		hideonnpc getmdnpcname("封印魔法陣#2");
		hideonnpc getmdnpcname("封印魔法陣#4");
		hideonnpc getmdnpcname("封印魔法陣#8");
		hideoffnpc getmdnpcname("封印魔法陣#10");
	}
	initnpctimer;
	end;
}
