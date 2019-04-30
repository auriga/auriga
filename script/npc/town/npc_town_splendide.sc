//= Auriga Script ==============================================================
// Ragnarok Online Splendide Town Script	by refis
//==============================================================================

//============================================================
// 猫の手職員
//------------------------------------------------------------
spl_fild02.gat,373,240,4	script	猫の手職員	421,{
	if(CATHAND_POINT == 0) {
		mes "[猫の手職員]";
		mes "いつもご利用ありがとうございます。";
		mes "猫の手サービスです。";
		next;
		mes "[猫の手職員]";
		mes "……にゃお？";
		mes "あなた様は";
		mes "まだ猫の手サービスと";
		mes "会員契約していないようですね。";
		next;
		mes "[猫の手職員]";
		mes "是非、会員契約して欲しいです！";
		mes "契約すると便利なサービスを";
		mes "受けれるんです！";
		next;
		mes "[猫の手職員]";
		mes "契約は";
		mes "^FF0000ミッドガルド連合軍駐屯地にいる";
		mes "猫の手職員^000000がしてくれるから";
		mes "是非、彼に話しかけて";
		mes "契約してくださいね！";
		close;
	}
	mes "[猫の手職員]";
	mes "にゃお～、";
	mes "いつも^FF0000猫の手サービス^000000";
	mes "ご利用ありがとうございます。";
	next;
	mes "[猫の手職員]";
	mes "現在、あなた様の";
	mes "猫の手信用ポイントは、";
	mes "^FF0000" +CATHAND_POINT+ "^000000ポイントです。";
	mes "今日は、どのサービスをご利用ですか？";
	next;
	setarray '@str$,(CATHAND_POINT >= 10)? "倉庫サービス -> 60zeny": "",
			(CATHAND_POINT >= 100)? "猫ワープ": "";
	switch(select("位置保存サービス(連合軍駐屯地)",'@str$[0],'@str$[1],"やめる")) {
	case 1:
		savepoint "mid_camp.gat",56,138;
		mes "[猫の手職員]";
		mes "この先にある街の住民達の";
		mes "反発があって";
		mes "ここではセーブできないんです。";
		next;
		mes "[猫の手職員]";
		mes "にゃお……";
		mes "羽がパタパタしているものだから";
		mes "ちょうちょだと思って";
		mes "追いかけたら";
		mes "街の住民だったみたいで……";
		mes "そのことが悪かったのかも……";
		next;
		mes "[猫の手職員]";
		mes "だから、";
		mes "ミッドガルド連合軍駐屯地";
		mes "にセーブしておきました。";
		mes "申し訳ないにゃお……";
		close;
	case 2:
		if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "おかしいですね。";
			mes "ここに新米冒険者は";
			mes "来れないはずなのに……";
			next;
			mes "[猫の手職員]";
			mes "基本スキルをレベル6まで";
			mes "習得していないと";
			mes "倉庫は利用できないのです。";
			close;
		}
		if(Zeny < 60) {
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "Zenyが足りないようですよ。";
			mes "我々猫の手サービスの";
			mes "倉庫利用料は60Zenyです。";
			mes "お安いでしょう？";
			close;
		}
		set Zeny,Zeny-60;
		openstorage;
		close;
	case 3:
		mes "[猫の手職員]";
		mes "現在、";
		mes strcharinfo(0)+ "様の";
		mes "猫の手信用ポイントは、";
		mes "^FF0000" +CATHAND_POINT+ "^000000ポイント";
		mes "ですので、次の街への";
		mes "猫ワープサービスが利用できます。";
		next;
		switch(select("連合軍駐屯地----5500z","マヌクフィールド02----7500z","やめる")) {
		case 1:
			set '@map$,"mid_camp.gat";
			set '@warpx,56;
			set '@warpy,139;
			set '@zeny,5500;
			break;
		case 2:
			set '@map$,"man_fild02.gat";
			set '@warpx,129;
			set '@warpy,61;
			set '@zeny,7500;
			break;
		case 3:
			mes "[猫の手職員]";
			mes "わかりました。";
			mes "またの利用をお待ちしています。";
			close;
		}
		if(Zeny < '@zeny) {
			mes "[猫の手職員]";
			mes "にゃにゃ、お金が足りませんよ。";
			close;
		}
		mes "[猫の手職員]";
		mes "にゃにゃ、";
		mes "それではお送りします。";
		close2;
		set Zeny,Zeny - '@zeny;
		warp '@map$,'@warpx,'@warpy;
		end;
	case 4:
		mes "[猫の手職員]";
		mes "そうですか～。";
		mes "またお待ちしております。";
		close;
	}
}

//============================================================
// スプレンディッド商人
//------------------------------------------------------------
spl_in01.gat,110,326,5	script	スプレンディッド商人	439,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[商人]";
		mes "BurWehAla";
		mes "tasnarAndu　Ie　Ru";
		close;
	}
	mes "[商人]";
	mes "いらっしゃいませ。";
	mes "何をお探しですか？";
	next;
	switch(select("商品の説明書を見る","ピンギキュラの果実ジャム","ルシオラヴェスパのハチ蜜","コルヌスの涙","やめておく")) {
	case 1:
		mes "[商人]";
		mes "はい、商品の説明書！";
		close2;
		openbook 11018;
		end;
	case 2:
		set '@gain,12344;
		break;
	case 3:
		set '@gain,12345;
		break;
	case 4:
		set '@gain,12349;
		break;
	case 5:
		mes "[商人]";
		mes "そうですか、残念です。";
		mes "またお待ちしております。";
		close;
	}
	mes "[商人]";
	mes "^3131FFスプレンディッドコイン1個^000000につき";
	mes getitemname('@gain)+ "を";
	mes "^3131FF3個^000000ご購入できます。";
	next;
	mes "[商人]";
	mes "いらっしゃいませ。";
	mes "何をお探しですか？";
	next;
	if(select("買う","買わない") == 2) {
		mes "[商人]";
		mes "そうですか、残念です。";
		mes "またお待ちしております。";
		close;
	}
	if(countitem(6081) < 1) {
		mes "[商人]";
		mes "おやおや、";
		mes "コインが足りませんよ。";
		close;
	}
	if(checkitemblank() == 0) {
		mes "[商人]";
		mes "あれ？";
		mes "荷物を持ちすぎですよ。";
		mes "これでは商品を渡すことは出来ません。";
		mes "荷物の種類を減らしてから";
		mes "また話しかけてくださいね。";
		close;
	}
	if(checkweight('@gain,3) == 0) {
		mes "[商人]";
		mes "あれ？";
		mes "荷物を持ちすぎですよ。";
		mes "これでは商品を渡すことは出来ません。";
		mes "荷物の重量を減らしてから";
		mes "また話しかけてくださいね。";
		close;
	}
	mes "[商人]";
	mes "はい、";
	mes getitemname('@gain)+ "です！";
	mes "ありがとうございました！";
	delitem 6081,1;
	getitem '@gain,3;
	close;
}

//============================================================
// スプレンディッド住人
//------------------------------------------------------------
splendide.gat,159,164,3	script	妖精の兵士	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精]";
		mes "RiniHirDieb Ie nahImanMe Di Mush";
		mes "mahnarAsh So HirAnMod O Ras";
		mes "neaLoDath Ha KoRivehWha So Thusnea";
		close;
	}
	mes "[妖精の兵士]";
	mes "この気高い俺様が巨人のような";
	mes "大きさだけがとりえのバカ達と";
	mes "戦わなきゃいけないなんて、";
	mes "面倒な話だよなぁ……。";
	close;
}

splendide.gat,229,54,3	script	少女のような妖精	439,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[少女のような妖精]";
		mes "ImanAnuUor Yee NeUorVer Ir RivehAshOsa";
		mes "AdorserHir er OsaAlahAno Mu RivehDath";
		next;
		mes "[少女のような妖精]";
		mes "LarsFuloSar Yu VilGotheor Yu nes";
		mes "Anuneseor Ie remuSeDieb er ";
		mes "WosLoNud Ko NuffDuIman Ir ";
		close;
	}
	mes "[少女のような妖精]";
	mes "ふ～ん、お前が人間なの……？";
	mes "巨人族よりはマシだけど……";
	mes "美しくないわね……";
	next;
	mes "[少女のような妖精]";
	mes "どうやってここまで来たのか";
	mes "知らないけど、近寄らないでくださる？";
	mes "私の美しさが穢れるじゃない！";
	mes "あっちに行きなさいよ！!";
	close;
}

splendide.gat,89,235,5	script	少女のような妖精	446,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[少女のような妖精]";
		mes "WehVeldHir Or ThusNorAnu";
		mes "ReImanWos Yu marFuloNor Yee ";
		mes "SharneaVrum Ir Ruff";
		next;
		mes "[少女のような妖精]";
		mes "BurKoWeh Ie nesThusLu Ee ";
		close;
	}
	mes "[少女のような妖精]";
	mes "ランランラン～ル～ン♪";
	mes "楽しいわ～歌うのは楽しい～!!";
	mes "あたいの声はお美しい～♪";
	emotion 2;
	next;
	mes "[少女のような妖精]";
	mes "あ～ぁ～、あたいってば";
	mes "美しすぎる～。";
	close;
}

splendide.gat,245,243,3	script	妖精の兵士	462,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "DiebVohlWeh Ko RasVeldFar Ie AshVohl";
		mes "neaAmanIman Ie DorDuMe No Hireo";
		mes "tassermaur Yee DorAdorNud Ee ";
		mes "NohThorVe O FusImanAman";
		next;
		mes "[妖精の兵士]";
		mes "OsaVeldWeh U GothIyazVer Or ";
		mes "LarsAnDor Yee TurVeldVil";
		close;
	}
	mes "[妖精の兵士]";
	mes "この地はね、昔は汚くて住むには";
	mes "不向きの寒い土地だったのよ。";
	mes "でも、優秀な私達の手で";
	mes "住みやすい土地になったわけ。";
	next;
	mes "[妖精の兵士]";
	mes "あとはあの巨人達を追い出せば";
	mes "完璧になるんだけどね。";
	close;
}

splendide.gat,230,142,3	script	少女のような妖精	439,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[少女のような妖精]";
		mes "AgolWhaNe O LoRini";
		close;
	}
	mes "[少女のような妖精]";
	mes "うふふふ……。";
	mes "なんでこんなに";
	mes "私は美しいのでしょう！";
	close;
}

splendide.gat,274,203,3	script	少年のような妖精	444,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[少年のような妖精]";
		mes "AnnarNor So marFarAno Di ";
		mes "NudThusNei Ir  Ir ";
		mes "narVaTi Mu SharDimmaur Or Ano";
		mes "WhaModKo Or eoNeiNor Di ";
		mes "ImanDunah O  O ";
		close;
	}
	mes "[少年のような妖精]";
	mes "ねぇねぇ、そこの人！";
	mes "貴方は人間なんでしょう？";
	mes "ここにはどうやって来たの？";
	mes "人間達が住んでいる世界は";
	mes "どんなところなの？";
	mes "楽しいところなの？教えてよ～。";
	close;
}

splendide.gat,275,141,3	script	妖精の兵士	447,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "narnahNoh Di WehRiniLars ";
		mes "Yee ModAnu";
		mes "LuAlahNe Or FarAnduOsa No AgolKo";
		next;
		mes "[妖精の兵士]";
		mes "LarsVilDim No WhaVilFus Ha Ash";
		mes "ReLarsShar Mu AnduLoLon Ie Nufftas";
		close;
	}
	mes "[妖精の兵士]";
	mes "私に話しかけるな！";
	mes "ん？喧嘩を売るつもりじゃないって？";
	mes "そんなのはわかってるさ。";
	mes "私は天才だから";
	mes "全てお見通しさ！";
	next;
	mes "[妖精の兵士]";
	mes "だから、誰かと話す";
	mes "必要なんてないんだよ。";
	mes "私は完璧で、全て一人で";
	mes "解決できるのだから。";
	close;
}

splendide.gat,224,230,3	script	少女のような妖精	440,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[少女のような妖精]";
		mes "NuffMushLars Ra WehVilnah";
		mes "Ra DielWeh RivehnarWos ";
		mes "Ra YurSharRe TalVaThor";
		mes "O VerWhatas FuloDimIyaz";
		mes "Mu WhaNoreo U AlahNeLo";
		mes "Ra UorOsa SeAnduMush Ur";
		close;
	}
	mes "[少女のような妖精]";
	mes "さぁ、私の後に続いて踊りなさい！";
	mes "ハイッ！　ワンツー！　ワンツー！";
	mes "誰にだって出来るわよー!!簡単簡単!!";
	mes "さぁ、お尻を突きだして";
	mes "可愛く見せるのよ！";
	mes "ハイッ！　ワンツー！　ワンツー！";
	next;
	mes "‐どうやらダンスを教える";
	mes "　練習をしているようだ‐";
	close;
}

splendide.gat,223,36,3	script	妖精の兵士	462,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "AshAmanNei Ir LonVeldremu O ";
		mes "AnduSarHir No NudAnumaur Ha Veld";
		mes "Semarmah U VeTingDieb Yu ";
		mes "mahsertas Ra marAmanAdor Ir ";
		next;
		mes "[妖精の兵士]";
		mes "TingAgolLu So MushAndumah U neseor";
		mes "WhaDuFulo er ImanThusNe Di Tur";
		mes "DathUornah Ir MemaurDeh Yu Fulo";
		mes "CyaMeDor Ko VeLarsAgol";
		close;
	}
	mes "[妖精の兵士]";
	mes "巨人と関わりたいなんて";
	mes "これっぽっちも思ってないけど、";
	mes "お前達が我々と敵対している以上";
	mes "仕方ない……。";
	next;
	mes "[妖精の兵士]";
	mes "気は進まないけど、";
	mes "まぁ……、今回に限っては、";
	mes "この伝家の宝刀を";
	mes "ふるう時がきたようだ！";
	mes "私と戦えることを光栄に思うがいい！";
	mes "この巨人め！";
	next;
	mes "‐どうやら巨人達に出会った時の";
	mes "　台詞の練習をしているようだ。‐";
	close;
}

splendide.gat,305,129,3	script	気楽な妖精	436,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[気楽な妖精]";
		mes "AnduNothUor O eomaurShar Mu AnduVeld";
		mes "AdorFulotas Ko NorAlahAsh Ie Ala";
		mes "KoOsaLon Ha AnuNeiNoh Di Ting";
		mes "tasKoDiel O IyazGoth";
		emotion 45;
		next;
		mes "[気楽な妖精]";
		mes "OdesmahHir Or mahneaLars So ";
		mes "HirNudAman O AdorWosDu";
		mes "DimYurVa So DanaRuYur";
		close;
	}
	mes "[気楽な妖精]";
	mes "う～ん、退屈だわ～。";
	mes "面白い事もないし～。";
	mes "巨人達と戦うと言っても";
	mes "私には何にも関係ないし～。";
	mes "いまいちピンとこないわよね。";
	emotion 45;
	next;
	mes "[気楽な妖精]";
	mes "やることもないし～";
	mes "自分の美容を保つ事に";
	mes "専念した方が良いよね～。";
	mes "貴方もそう思うでしょう？";
	close;
}

splendide.gat,142,315,3	script	妖精の兵士	462,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "WharemuLars Ur SharUdenWha Yu Agol";
		mes "LontasSar Ra DathVeAlah Ee Noh";
		mes "LarsLonnah Ko TalnesIman Ie Diel";
		next;
		mes "[妖精の兵士]";
		mes "tasSarNuff Or WehFarDieb Ir FarRu";
		mes "FusYurnah So MeAshnar O Noth";
		mes "YurBurDu Yu VeldVaMush So Thor";
		mes "AgolDiebUor No TurnahAla O ";
		emotion 20;
		close;
	}
	mes "[妖精の兵士]";
	mes "飛ぶのも意外と大変なんですよ。";
	mes "でも、歩くよりは楽だから";
	mes "良しとしますか…。";
	next;
	mes "[妖精の兵士]";
	mes "あら？　貴方は人間なんですね？";
	mes "我々のように美しい羽が";
	mes "ついていれば、歩くなんて";
	mes "面倒ことをしなくてもいいのに……。";
	mes "貴方も大変ですね……。";
	emotion 20;
	close;
}

splendide.gat,181,107,5	script	妖精の兵士	462,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "hFarDieb Ir FarRu";
		mes "Yu VeldVaMush  So MeAs";
		mes "YurBurDu So ThorFusYurnah";
		mes "No TurnahAla OAgolDiebUor";
		close;
	}
	mes "[妖精の兵士]";
	mes "スマートで綺麗な私は美しい！";
	mes "それに比べて、他の種族は汚いし、";
	mes "ブサイクだし……。";
	mes "うぅ～、思い出すだけで";
	mes "嫌気がさしてきたわ！";
	close;
}

splendide.gat,188,76,5	script	兵士	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[兵士]";
		mes "SeAshLu　Di　YurDiebTing";
		mes "Ee　VeModTur　No";
		mes "NuffLarsVa　No";
		close;
	}
	mes "[兵士]";
	mes "ここは、";
	mes "ラフィネ族の前線基地";
	mes "スプレンディッドです。";
	close;
}

splendide.gat,201,76,3	script	兵士	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[兵士]";
		mes "SeAshLu　Di　YurDiebTing";
		mes "Ee　VeModTur　No";
		mes "NuffLarsVa　No";
		close;
	}
	mes "[兵士]";
	mes "ここは、";
	mes "ラフィネ族の前線基地";
	mes "スプレンディッドです。";
	close;
}

splendide.gat,207,97,5	script	妖精	443,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精]";
		mes "sehrVa";
		mes "IyazAnman　Di　TurHirCya";
		misceffect 362;
		close;
	}
	mes "[妖精]";
	mes "やあ！";
	mes "僕もこの環境浄化装置のように";
	mes "光を出せるんだよ。";
	mes "そりゃ!!";
	mes "どう、かっこいい？";
	misceffect 362;
	close;
}

splendide.gat,210,95,3	script	妖精	442,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精]";
		mes "MushIyazTur　Ee　YurDana";
		emotion 21;
		close;
	}
	mes "[妖精]";
	mes "うわあ！";
	mes "超かっこいい!!";
	emotion 21;
	close;
}

spl_in01.gat,190,314,5	script	保安担当官	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[保安担当官]";
		mes "GothremuAman　Ha";
		mes "DimDielNuff";
		mes "GothAnAsh　er　NohVaAgol";
		mes "Yee CyaOsaDor　U　Aman　U";
		mes "TurOdesVrum　Ir　TalDathOsa";
		close;
	}
	mes "[保安担当官]";
	mes "ここはスプレンディッドの地下監獄さ。";
	mes "収監されたくなかったら、";
	mes "大人しくしてたほうがいいぜ。";
	close;
}

spl_in01.gat,281,329,3	script	保安担当官	447,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[保安担当官]";
		mes "AnduVeldRe　Ko";
		mes "VeldReFulo　S";
		mes "LomaurDu　SoSo";
		close;
	}
	mes "[保安担当官]";
	mes "静かに！";
	mes "囚人に刺激をあたえるな！";
	close;
}

spl_in01.gat,287,306,3	script	#spl_prs	111,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[サファ族の捕虜]";
		mes "∩∵￢ ∮";
		mes "⊇∮￢　∪　∫⊆∪";
		close;
	}
	mes "[サファ族の捕虜]";
	mes "体が、体が……";
	mes "頼むっ……";
	mes "ブラディウムをくれ……";
	close;
}

spl_in01.gat,265,315,0	script	#spl_prs1	139,5,5,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[遠くから聞こえる声]";
		mes "RuffUdeneo　Mu　VilAsh";
		mes "YurReDur　Ha　DielTalNe";
		mes "Ko　Lars";
		mes "HirVerWeh　Yu　AnuNud";
		close;
	}
	mes "[遠くから聞こえる声]";
	mes "助けてくれ、オレは潔白だ！";
	mes "サファ族のスパイなんかじゃない!!";
	mes "早くオレをここから出せ！";
	mes "出せったら出せっ!!";
	close;
}

spl_in01.gat,172,225,3	script	放浪詩人	51,{
	cutin "god_nelluad02",2;
	mes "‐男が楽器を演奏している‐";
	next;
	cutin "god_nelluad01",2;
	mes "‐詩人はあなたがいることに";
	mes "　気付き、あなたに話しかけた‐";
	next;
	mes "[放浪詩人ネル]";
	mes "こんにちわ。";
	mes "よかったら演奏を";
	mes "聴いていってください。";
	next;
	menu "あなたは？",-;
	mes "[放浪詩人ネル]";
	mes "僕はネルと言います。";
	mes "妖精たちに";
	mes "演奏を聴いてもらっていたんです。";
	next;
	mes "[放浪詩人ネル]";
	mes "僕は、風の吹くままに遠征隊に入り、";
	mes "川の流れるままに";
	mes "この地にやって来ました。";
	next;
	mes "[放浪詩人ネル]";
	mes "そうこうしている内に";
	mes "こうして";
	mes "妖精たちとも仲良くなり、";
	mes "ここで演奏をしているんです。";
	next;
	mes "[放浪詩人ネル]";
	mes "言葉が通じなくても音楽で";
	mes "彼らと通じ合うことができました。";
	mes "彼らは風流が解る種族で";
	mes "とても嬉しいです。";
	next;
	mes "[放浪詩人ネル]";
	mes "どうですか、";
	mes "君も聴いていきませんか？";
	next;
	if(select("曲をリクエストする","けっこうです") == 2) {
		cutin "god_nelluad03",2;
		mes "[放浪詩人ネル]";
		mes "そうか、残念ですね。";
		next;
		mes "[放浪詩人ネル]";
		mes "僕はしばらく";
		mes "ここにいるつもりなので";
		mes "演奏が聞きたくなったら";
		mes "いつでも来てくださいね。";
		close2;
		cutin "god_nelluad03",255;
		end;
	}
	mes "[放浪詩人ネル]";
	mes "では、好きな曲を";
	mes "選んでください。";
	next;
	switch(select("ブラギの詩","永遠の混沌","夕陽のアサシンクロス","ニーベルングの指輪")) {
	case 1:
		cutin "god_nelluad02",2;
		mes "[放浪詩人ネル]";
		mes "ブラギの詩ですね。";
		mes "詩人の心を聴いてください。";
		soundeffect "bragis_poem.wav",0,0;
		close2;
		cutin "god_nelluad02",255;
		end;
	case 2:
		cutin "god_nelluad02",2;
		mes "[放浪詩人ネル]";
		mes "永遠の混沌、";
		mes "これは雄大な曲です。";
		mes "ところでこの題目、";
		mes "混沌状態が永遠に続くのか、";
		mes "それとも永遠と混沌が同じものなのか、";
		mes "果たしてどっちの意味なんでしょう？";
		soundeffect "chaos_of_eternity.wav",0,0;
		close2;
		cutin "god_nelluad02",255;
		end;
	case 3:
		cutin "god_nelluad02",2;
		mes "[放浪詩人ネル]";
		mes "夕陽のアサシンクロス。";
		mes "死の影に包まれたアサシンクロスが";
		mes "夕日を背にたたずむ……";
		mes "哀愁漂う素晴らしい光景ですよね。";
		soundeffect "assassin_of_sunset.wav",0,0;
		close2;
		cutin "god_nelluad02",255;
		end;
	case 4:
		cutin "god_nelluad02",2;
		mes "[放浪詩人ネル]";
		mes "ニーベルングの指輪。";
		mes "興味深い歌詞ですよね。";
		mes "では、弾いてみましょう。";
		next;
		mes "[放浪詩人ネル]";
		mes "大いなる河の底に巨大な黄金ありき。";
		mes "愛を断つ者が、隠されし秘密を知り";
		mes "その黄金から指輪を鍛え上げし時、";
		mes "その者は全能な力を得る。";
		mes "それは神々さえ支配下におく";
		mes "全世界の王の指輪であった～。";
		soundeffect "ring_of_nibelungen.wav",0,0;
		next;
		mes "[放浪詩人ネル]";
		mes "ヴァルハラを築いた巨人たちが";
		mes "望むもの、それは美しき女神フレイヤ。";
		mes "姑息なロキの取り引きにより、";
		mes "かの女神は突如姿を消した。";
		next;
		mes "[放浪詩人ネル]";
		mes "女神の代わりとなれるもの";
		mes "それはアルベリヒの宝物。";
		mes "神々さえ支配するという";
		mes "あの指輪であった～。";
		next;
		mes "[放浪詩人ネル]";
		mes "魔法の頭巾を持つアルベリヒ。";
		mes "何にでもなれる、無限に手に入る";
		mes "黄金で世の中を思いのままにできる。";
		mes "そんな喜びに浸っている彼に";
		mes "ロキはささやいた。";
		next;
		mes "[放浪詩人ネル]";
		mes "可哀相なアルベリヒは";
		mes "その言葉に惑わされ、その身を";
		mes "なんとひき蛙へと変えてしまい";
		mes "捕まってしまった。";
		next;
		mes "[放浪詩人ネル]";
		mes "アルベリヒは呪った。";
		mes "自らの手を去った指輪、その主人と";
		mes "なる者は、災いをうけ、やがて死に";
		mes "至るようにと。指輪を受けとった";
		mes "巨人たち、彼らは互いの宝物を";
		mes "奪い合う。";
		next;
		mes "[放浪詩人ネル]";
		mes "結局、呪いを受けた弟は、";
		mes "兄を殴り殺してしまった。";
		close2;
		cutin "god_nelluad02",255;
		end;
	}
}

spl_in01.gat,182,213,1	script	休憩中の妖精	438,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[休憩中の妖精]";
		mes "IyazLarsSe Or An.";
		mes "marLoOsa Yee NeiBur";
		mes "Rinisehrnea Mu...? ";
		close;
	}
	mes "[休憩中の妖精]";
	mes "あの詩人は本当に不思議。";
	mes "突然現れて、";
	mes "言葉も通じないのに";
	mes "演奏を始めたの。";
	next;
	mes "[休憩中の妖精]";
	mes "最近はいつも";
	mes "ここで演奏をしているわ。";
	mes "あのメロディは";
	mes "あなた達の国の音楽でしょう？";
	mes "悪くないですね。";
	close;
}

spl_in01.gat,181,218,5	script	休憩中の妖精	446,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "‐目を閉じたまま演奏を聴いている‐";
		next;
		mes "[休憩中の妖精]";
		mes "GothTingNoth Di~ nar..";
		mes "DiebIyazNud Yu FarAn";
		mes "nesFarDor U ~";
		close;
	}
	mes "‐目を閉じたまま演奏を聴いている‐";
	next;
	mes "[休憩中の妖精]";
	mes "この楽器の音色は";
	mes "本当に素晴らしい……";
	close;
}

spl_in01.gat,161,213,7	script	食事中の妖精	447,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[食事中の妖精]";
		mes "NothFarLu　Ra...?";
		mes "RuffYur..!";
		next;
		mes "‐食事中の妖精は、";
		mes "　一度手を止め、";
		mes "　不快そうな顔であなたを見た‐";
		close;
	}
	mes "[食事中の妖精]";
	mes "ここの食事はもう飽きたな……";
	mes "でもスープだけは最高にうまいから";
	mes "それだけは助かる。";
	next;
	mes "[食事中の妖精]";
	mes "……";
	mes "ところでそこの君。";
	mes "食事をしているのに";
	mes "そうやってじっと見つめられたら";
	mes "いい気分はしないぜ。";
	close;
}

spl_in01.gat,162,202,5	script	メモ中の妖精	436,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[メモ中の妖精]";
		mes "TiTalLars　Ur";
		mes "tasThorNoth　OAnImanWha.";
		mes "FusLuRuff.....Mu";
		mes "TingLuAla Yee AnmanAndu";
		close;
	}
	mes "[メモ中の妖精]";
	mes "異国にも";
	mes "このような素晴らしい音楽が";
	mes "あるんですね。";
	mes "あの詩人の演奏を聴いて";
	mes "感動してしまいました。";
	next;
	mes "[メモ中の妖精]";
	mes "^0000ffヤイ^000000に戻ったら";
	mes "早速この曲を研究してみます。";
	mes "私もあの詩人のように";
	mes "演奏できるようになりたいです。";
	close;
}

spl_in01.gat,167,207,7	script	無言の妖精	445,{
	mes "‐向こうにいる詩人の";
	mes "　演奏に聴き入っている。";
	mes "　邪魔しないでおこう‐";
	close;
}

spl_in01.gat,180,201,3	script	妖精の兵士	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[妖精の兵士]";
		mes "FusVohlAnu Ur　Lon.";
		mes "LoUdenFar　Ha　Dormaur?";
		mes "...marAmanYur Mu.";
		close;
	}
	mes "[妖精の兵士]";
	mes "君はその詩人と同じ世界の人だろう？";
	mes "私はもしもの時に備えて、";
	mes "あの詩人を監視しているのだ。";
	next;
	mes "[妖精の兵士]";
	mes "もちろん、君も監視対象だ。";
	mes "君たちの種族は";
	mes "我々に敵意がないようだが";
	mes "いつ何が起こるかわからないからな。";
	next;
	mes "[妖精の兵士]";
	mes "……";
	mes "それはそれで、";
	mes "あの詩人が演奏している";
	mes "あの楽器の名称はなんだ？";
	next;
	mes "[妖精の兵士]";
	mes "いい音色だよな。";
	mes "演奏している彼も素晴らしい。";
	mes "ファンになってしまったよ。";
	close;
}

spl_in01.gat,189,207,3	script	従業員	439,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[従業員妖精]";
		mes "VeldAnoWeh　Or";
		mes "TurWos";
		mes "……ah……";
		close;
	}
	mes "[従業員妖精]";
	mes "ん、何か用ですか？";
	mes "ラフィネ族以外には";
	mes "食べ物を売りませんよ。";
	next;
	mes "[従業員妖精]";
	mes "それに私たちの食料の量では、";
	mes "あなたのその大きなお腹は";
	mes "満足しないはずです。";
	next;
	mes "[従業員妖精]";
	mes "きっとあなたは";
	mes "大食いに違いないです。";
	next;
	mes "[従業員妖精]";
	mes "でも、補給倉庫に行けば";
	mes "あなたのその大きなお腹が";
	mes "いっぱいになるような食べ物が";
	mes "あるかもしれません。";
	close;
}

spl_in01.gat,154,207,5	script	従業員	440,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[従業員]";
		mes "NorVerNuff　Ee　Re!";
		mes "remuDurOdes　Mu　AshFus~!";
		mes "OdesTalWeh　Ur???";
		close;
	}
	mes "[従業員]";
	mes "このスプレンディッドは";
	mes "あの忌々しい巨人の一族";
	mes "サファ族を打倒するために";
	mes "作られた軍事施設です。";
	next;
	mes "[従業員]";
	mes "彼らはイグドラシルを";
	mes "傷つけているのです。";
	mes "その暴挙をやめさせる為に";
	mes "私達ラフィネ族はこの地に来たのです！";
	close;
}

spl_in01.gat,122,314,5	script	指揮官	461,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[兵士]";
		mes "NorVerNuff　Ee　Re....";
		next;
		mes "[指揮官]";
		mes "FusVerAlah　Di";
		mes "ModNorNor　U DimVohlWeh";
		mes "O　DimAmannea　An";
		mes "WosAnoNoh　An";
		mes "AnduMeOdes　So";
		mes "TalAdor.";
		next;
		mes "[指揮官]";
		mes "DurNohHir　Ha";
		mes "UorVaThus　Di　AshNuffLon";
		mes "U　mahNuffThus　";
		mes "U RuAmanAgol　Ir　NohHir...?";
		close;
	}
	mes "[指揮官]";
	mes "何か新しい武器はないのか？";
	next;
	mes "[兵士]";
	mes "はっ!!";
	mes "ここにあるのが新製品であります！";
	mes "この剣は、なんと";
	mes "水も両断できてしまう程に";
	mes "鋭利な刃が特徴となっております！";
	next;
	mes "[指揮官]";
	mes "ほほう。";
	mes "しかし、私は";
	mes "あまり剣を使う機会がなくてね。";
	next;
	mes "‐二人は新しい武器について";
	mes "　話し合っている‐";
	close;
}

spl_in01.gat,122,311,1	script	兵士	447,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[兵士]";
		mes "NorVerNuff　Ee　Re";
		next;
		mes "[指揮官]";
		mes "FusVerAlah　Di　";
		mes "ModNorNor　U　";
		mes "DimVohlWeh　O　";
		mes "DimAmannea";
		mes "An　WosAnoNoh　An";
		mes "AnduMeOdes　So　TalAdor.";
		next;
		mes "[兵士]";
		mes "DurNohHir　Ha";
		mes "UorVaThus　Di";
		mes "AshNuffLon　U";
		mes "mahNuffThus　U";
		mes "RuAmanAgol　Ir　NohHir?";
		close;
	}
	mes "[兵士]";
	mes "ん？";
	mes "ここで何をしているのですか？";
	mes "私達の軍事物資を";
	mes "調べるために来たとか？";
	next;
	mes "[指揮官]";
	mes "好きにさせとけ。";
	mes "この繊細な武器を、";
	mes "あの不器用そうな手で";
	mes "扱えるわけがない。";
	next;
	mes "[兵士]";
	mes "な、なるほど！";
	emotion 0;
	close;
}
