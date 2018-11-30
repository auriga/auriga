//==============================================================================
// Ragnarok Online PointShop Script
//==============================================================================

-	pointshop	SpecialItemShopper	-1,17634:5000,17290:9000,17289:5000,12913:1000,12914:1000,12918:1000,12917:1000,12927:1500,12910:500,12903:3000,12904:3000,12908:3000,12905:3000,12906:3000,12907:3000,12900:7500,16653:10000,13990:5000,12922:7500,16674:7500,12901:7000,13500:12000,12911:15000,12921:7000,12920:10000,14289:5000,14290:5000,16682:12000

payon.gat,153,96,4		substore(SpecialItemShopper)	スペシャルアイテム販売	73
alberta.gat,90,56,6		substore(SpecialItemShopper)	スペシャルアイテム販売	73
prontera.gat,123,68,2		substore(SpecialItemShopper)	スペシャルアイテム販売	73
geffen.gat,114,104,4		substore(SpecialItemShopper)	スペシャルアイテム販売	73
morocc.gat,169,80,2		substore(SpecialItemShopper)	スペシャルアイテム販売	73
aldebaran.gat,135,123,4		substore(SpecialItemShopper)	スペシャルアイテム販売	73
yuno.gat,167,187,3		substore(SpecialItemShopper)	スペシャルアイテム販売	73
einbroch.gat,242,255,3		substore(SpecialItemShopper)	スペシャルアイテム販売	73
lighthalzen.gat,187,304,3	substore(SpecialItemShopper)	スペシャルアイテム販売	73
hugel.gat,83,150,3		substore(SpecialItemShopper)	スペシャルアイテム販売	73
comodo.gat,198,149,4	substore(SpecialItemShopper)	スペシャルアイテム販売	73
rachel.gat,132,144,2	substore(SpecialItemShopper)	スペシャルアイテム販売	73
mid_camp.gat,59,130,4	substore(SpecialItemShopper)	スペシャルアイテム販売	73

//============================================================
// デフォルトカラーチケット, エクストラカラーチケット
//------------------------------------------------------------
prontera.gat,123,62,5	script	服装染色師	97,{
	// Jobに対応したファイル名を返す
	function ExcolorSample {
		switch(getarg(0)) {
		case Job_Novice:	return "excolor_novice.bmp";
		case Job_Swordman:	return "excolor_swordman.bmp";
		case Job_Magician:	return "excolor_magician.bmp";
		case Job_Archer:	return "excolor_archer.bmp";
		case Job_Acolyte:	return "excolor_acolyte.bmp";
		case Job_Merchant:	return "excolor_merchant.bmp";
		case Job_Thief:		return "excolor_thief.bmp";
		case Job_Knight:
			if(Upper == UPPER_HIGH)
				return "excolor_loadknight.bmp";
			else
				return "excolor_knight.bmp";
		case Job_Priest:
			if(Upper == UPPER_HIGH)
				return "excolor_highpriest.bmp";
			else
				return "excolor_priest.bmp";
		case Job_Wizard:
			if(Upper == UPPER_HIGH)
				return "excolor_highwizard.bmp";
			else
				return "excolor_wizard.bmp";
		case Job_Blacksmith:
			if(Upper == UPPER_HIGH)
				return "excolor_whitesmith.bmp";
			else
				return "excolor_blacksmith.bmp";
		case Job_Hunter:
			if(Upper == UPPER_HIGH)
				return "excolor_sniper.bmp";
			else
				return "excolor_hunter.bmp";
		case Job_Assassin:
			if(Upper == UPPER_HIGH)
				return "excolor_assassincross.bmp";
			else
				return "excolor_assassin.bmp";
		case Job_Crusader:
			if(Upper == UPPER_HIGH)
				return "excolor_paladin.bmp";
			else
				return "excolor_crusader.bmp";
		case Job_Monk:
			if(Upper == UPPER_HIGH)
				return "excolor_champion.bmp";
			else
				return "excolor_monk.bmp";
		case Job_Sage:
			if(Upper == UPPER_HIGH)
				return "excolor_professor.bmp";
			else
				return "excolor_sage.bmp";
		case Job_Rogue:
			if(Upper == UPPER_HIGH)
				return "excolor_chaser.bmp";
			else
				return "excolor_rogue.bmp";
		case Job_Alchemist:
			if(Upper == UPPER_HIGH)
				return "excolor_creator.bmp";
			else
				return "excolor_alchemist.bmp";
		case Job_Bard:
		case Job_Dancer:
			if(Upper == UPPER_HIGH)
				return "excolor_clown_gypsy.bmp";
			else
				return "excolor_bard_dancer.bmp";
		case Job_SuperNovice:
		case Job_ExpandedSuperNovice:	return "excolor_supernovice.bmp";
		case Job_Taekwon:		return "excolor_taekwon.bmp";
		case job_Star:			return "excolor_kwonsung.bmp";
		case Job_Linker:		return "excolor_soullinker.bmp";
		case Job_Gunslinger:	return "excolor_gunslinger.bmp";
		case Job_Ninja:			return "excolor_ninja.bmp";
		case Job_RuneKnight:	return "excolor_runeknight.bmp";
		case Job_Warlock:		return "excolor_warlock.bmp";
		case Job_Ranger:		return "excolor_ranger.bmp";
		case Job_ArchBishop:	return "excolor_archbishop.bmp";
		case Job_Mechanic:
			if(getlook(13) == 0)
				return "excolor_mechanic.bmp";
			else
				return "excolor_mechanic2.bmp";
		case Job_Guillotine:
			if(getlook(13) == 0)
				return "excolor_guillotinecross.bmp";
			else
				return "excolor_guillotinecross2.bmp";
		case Job_RoyalGuard:
			if(getlook(13) == 0)
				return "excolor_royalguard.bmp";
			else
				return "excolor_royalguard2.bmp";
		case Job_Sorcerer:		return "excolor_sorcerer.bmp";
		case Job_Minstrel:
		case Job_Wanderer:		return "excolor_minstrel_wanderer.bmp";
		case Job_Shura:			return "excolor_sura.bmp";
		case Job_Genetic:
			if(getlook(13) == 0)
				return "excolor_genetic.bmp";
			else
				return "excolor_genetic2.bmp";
		case Job_ShadowChaser:	return "excolor_shadowchaser.bmp";
		case Job_Kagerou:
		case Job_Oboro:			return "excolor_kagerou_oboro.bmp";
		}
	}

	mes "[服装染色師]";
	mes "こんにちは！";
	mes "私は皆様に個性的なスタイルを";
	mes "提供すべく、皆様のお召し物を";
	mes "美しく染色させて頂く為に参りました！";
	next;
	mes "[服装染色師]";
	mes "^0000FFエクストラカラーチケット^000000を";
	mes "お持ち頂ければ、";
	mes "あなたの服の色を";
	mes "エクストラカラーに変更できます！";
	next;
	mes "[服装染色師]";
	mes "また、元のカラーに戻す場合は、";
	mes "^FF0000デフォルトカラーチケット^000000が";
	mes "必要となります。";
	next;
	mes "[服装染色師]";
	mes "現在、用意されたエクストラカラーは";
	mes "^FF0000各職業に2種類^000000と";
	mes "なっております。";
	next;
	mes "[服装染色師]";
	mes "さて、説明は以上です。";
	mes "あなたの望むサービスを";
	mes "選択してください。";
	next;
	switch(select("^006400カラーサンプル^000000を見る","^0000FFエクストラカラー^000000に変更する","^FF0000デフォルトカラー^000000に戻す","やめる")) {
	case 1:
		mes "[服装染色師]";
		mes "サンプルをご覧になるのですね？";
		mes "えーと、あなたの職業ですと……";
		mes "こちらですね。";
		next;
		cutin ExcolorSample(Job),4;
		mes "[服装染色師]";
		mes "是非ご参考に願います。";
		mes "1番と2番、お間違えのないよう";
		mes "よくご確認くださいね。";
		close;
	case 2:
		set '@num,getlook(7);
		if('@num != 0) {
			set '@num,'@num-1;
			if('@num == 1)
				set '@excolor,2;
			else if('@num == 2)
				set '@excolor,1;
			mes "[服装染色師]";
			mes "おや？";
			mes "あなたは既に";
			mes "^FF0000" +'@num+ "番^000000の色に";
			mes "染色されているようですが……";
			mes "もう一種類の^0000FF" +'@excolor+ "番^000000の色に";
			mes "染めなおしたいのですか？";
			next;
			if(select("やめておく","^0000FF" +'@excolor+ "番^000000に染色する") == 1) {
				mes "[服装染色師]";
				mes "そうですか。";
				mes "またの機会をお待ちしております。";
				close;
			}
			if(countitem(6046) < 1) {
				mes "[服装染色師]";
				mes "おや？";
				mes "エクストラカラーチケットを";
				mes "お持ちではない？";
				mes "用意出来ましたら、またおいで下さい。";
				close;
			}
			mes "[服装染色師]";
			mes "かしこまりました。";
			mes "それでは早速染色準備にかかります！";
			mes "エイッ！";
			next;
			mes "[服装染色師]";
			mes "完成です！";
			mes "どうです？　綺麗でしょう？";
			mes "早く皆に見せびらかしたくて";
			mes "仕方ないんじゃないですか？";
			delitem 6046,1;
			setlook 7,'@excolor+1;
			close;
		}
		if(countitem(6046) < 1) {
			mes "[服装染色師]";
			mes "おや？";
			mes "エクストラカラーチケットを";
			mes "お持ちではない？";
			mes "用意出来ましたら、またおいで下さい。";
			close;
		}
		while(1) {
			mes "[服装染色師]";
			mes "エクストラカラーは";
			mes "^FF00001番^000000と^0000FF2番^000000の2種類ございますが";
			mes "どちらの色を希望されますか？";
			next;
			switch(select("^FF00001番^000000","^0000FF2番^000000","^006400カラーサンプル^000000を見る","やめる")) {
			case 1:
				set '@excolor,1;
				break;
			case 2:
				set '@excolor,2;
				break;
			case 3:
				mes "[服装染色師]";
				mes "サンプルをご覧になるのですね？";
				mes "えーと、あなたの職業ですと……";
				mes "こちらですね。";
				next;
				cutin ExcolorSample(Job), 4;
				mes "[服装染色師]";
				mes "染色されますか？";
				next;
				if(select("はい","いいえ") == 2) {
					mes "[服装染色師]";
					mes "そうですか……";
					mes "またの機会をお待ちしております。";
					close;
				}
				continue;
			case 4:
				mes "[服装染色師]";
				mes "そうですか……";
				mes "またの機会をお待ちしております。";
				close;
			}
			mes "[服装染色師]";
			mes "^FF0000" +'@excolor+ "番^000000で";
			mes "間違いありませんか？";
			next;
			if(select("ちょっと待った","^FF0000" +'@excolor+ "番^000000に染色する") == 1)
				continue;
			mes "[服装染色師]";
			mes "かしこまりました。";
			mes "それでは早速染色準備にかかります！";
			mes "エイッ！";
			next;
			mes "[服装染色師]";
			mes "完成です！";
			mes "どうです？　綺麗でしょう？";
			mes "早く皆に見せびらかしたくて";
			mes "仕方ないんじゃないですか？";
			delitem 6046,1;
			setlook 7,'@excolor+1;
			close;
		}
	case 3:
		if(getlook(7) == 0) {
			mes "[服装染色師]";
			mes "おや？";
			mes "既に元の色のようですが？";
			close;
		}
		if(countitem(6047) < 1) {
			mes "[服装染色師]";
			mes "おや？";
			mes "デフォルトカラーチケットを";
			mes "お持ちではない？";
			mes "用意出来ましたら、またおいで下さい。";
			close;
		}
		mes "[服装染色師]";
		mes "よくぞ覚悟されました。";
		mes "それでは早速染色準備にかかります！";
		mes "本当に元の色に戻しますよ？";
		next;
		if(select("やっぱりやめる","お願いします") == 1) {
			mes "[服装染色師]";
			mes "そうですか……";
			mes "またの機会をお待ちしております。";
			close;
		}
		mes "[服装染色師]";
		mes "完成です！";
		mes "ありがとうございました。";
		delitem 6047,1;
		setlook 7,0;
		close;
	case 4:
		mes "[服装染色師]";
		mes "そうですか……";
		mes "またの機会をお待ちしております。";
		close;
	}
}

//============================================================
// 騎乗用手綱
//------------------------------------------------------------
prontera.gat,125,62,4	script	騎乗協会広報員	832,{
	if(countitem(12622) > 0) {
		mes "[騎乗協会広報担当員]";
		mes "やぁ、こんにちは。";
		mes "私は^0000FFミッドガルド騎乗協会^000000の";
		mes "広報員として活動している者です。";
		next;
		mes "[騎乗協会広報員]";
		mes "貴方は我々の協会の契約者ですね！";
		next;
		mes "[騎乗協会広報員]";
		mes "引き続き騎乗生物のご愛顧";
		mes "よろしくお願いします！";
		close;
	}
	mes "[騎乗協会広報担当員]";
	mes "やぁ、こんにちは。";
	mes "私は^0000FFミッドガルド騎乗協会^000000の";
	mes "広報員として活動している者です。";
	next;
	mes "[騎乗協会広報員]";
	mes "我々は『乗ること』に特化した";
	mes "生物の発見、改良、提供を";
	mes "主業務としている組織です。";
	next;
	mes "[騎乗協会広報員]";
	mes "我々の提供する^FF0000騎乗生物^000000の";
	mes "サンプルカタログを用意しております。";
	mes "見てみませんか？";
	next;
	if(select("^006400騎乗サンプル^000000を見る","やめておく") == 2) {
		mes "[騎乗協会広報員]";
		mes "そうですか、";
		mes "もし必要になりましたら";
		mes "またおいでください。";
		close;
	}
	mes "[騎乗協会広報担当員]";
	mes "サンプルをご覧になるのですね？";
	mes "えーと、あなたの職業ですと……";
	mes "こちらですね。";
	next;
	switch(Job) {
	case Job_Novice:	set '@name$,"riding_novice.bmp"; break;
	case Job_Swordman:	set '@name$,"riding_swordman.bmp"; break;
	case Job_Magician:	set '@name$,"riding_magician.bmp"; break;
	case Job_Archer:	set '@name$,"riding_archer.bmp"; break;
	case Job_Acolyte:	set '@name$,"riding_acolyte.bmp"; break;
	case Job_Merchant:	set '@name$,"riding_merchant.bmp"; break;
	case Job_Thief:		set '@name$,"riding_thief.bmp"; break;
	case Job_Knight:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_loadknight.bmp";
		else
			set '@name$,"riding_knight.bmp";
		break;
	case Job_Priest:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_highpriest.bmp";
		else
			set '@name$,"riding_priest.bmp";
		break;
	case Job_Wizard:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_highwizard.bmp";
		else
			set '@name$,"riding_wizard.bmp";
		break;
	case Job_Blacksmith:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_whitesmith.bmp";
		else
			set '@name$,"riding_blacksmith.bmp";
		break;
	case Job_Hunter:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_sniper.bmp";
		else
			set '@name$,"riding_hunter.bmp";
		break;
	case Job_Assassin:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_assassincross.bmp";
		else
			set '@name$,"riding_assassin.bmp";
		break;
	case Job_Crusader:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_paladin.bmp";
		else
			set '@name$,"riding_crusader.bmp";
		break;
	case Job_Monk:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_champion.bmp";
		else
			set '@name$,"riding_monk.bmp";
		break;
	case Job_Sage:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_professor.bmp";
		else
			set '@name$,"riding_sage.bmp";
		break;
	case Job_Rogue:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_chaser.bmp";
		else
			set '@name$,"riding_rogue.bmp";
		break;
	case Job_Alchemist:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_creator.bmp";
		else
			set '@name$,"riding_alchemist.bmp";
		break;
	case Job_Bard:
	case Job_Dancer:
		if(Upper == UPPER_HIGH)
			set '@name$,"riding_clown_gypsy.bmp";
		else
			set '@name$,"riding_bard_dancer.bmp";
		break;
	case Job_SuperNovice:
	case Job_ExpandedSuperNovice:	set '@name$,"riding_supernovice.bmp"; break;
	case Job_Taekwon:		set '@name$,"riding_taekwon.bmp"; break;
	case job_Star:			set '@name$,"riding_kwonsung.bmp"; break;
	case Job_Linker:		set '@name$,"riding_soullinker.bmp"; break;
	case Job_Gunslinger:	set '@name$,"riding_gunslinger.bmp"; break;
	case Job_Ninja:			set '@name$,"riding_ninja.bmp"; break;
	case Job_RuneKnight:	set '@name$,"riding_runeknight.bmp"; break;
	case Job_Warlock:		set '@name$,"riding_warlock.bmp"; break;
	case Job_Ranger:		set '@name$,"riding_ranger.bmp"; break;
	case Job_ArchBishop:	set '@name$,"riding_archbishop.bmp"; break;
	case Job_Mechanic:		set '@name$,"riding_mechanic.bmp"; break;
	case Job_Guillotine:	set '@name$,"riding_guillotinecross.bmp"; break;
	case Job_RoyalGuard:	set '@name$,"riding_royalguard.bmp"; break;
	case Job_Sorcerer:		set '@name$,"riding_sorcerer.bmp"; break;
	case Job_Minstrel:
	case Job_Wanderer:		set '@name$,"riding_minstrel_wanderer.bmp"; break;
	case Job_Shura:			set '@name$,"riding_sura.bmp"; break;
	case Job_Genetic:		set '@name$,"riding_genetic.bmp"; break;
	case Job_ShadowChaser:	set '@name$,"riding_shadowchaser.bmp"; break;
	case Job_Kagerou:
	case Job_Oboro:			set '@name$,"riding_kagerou_oboro.bmp"; break;
	}
	cutin '@name$,4;
	mes "[騎乗協会広報担当員]";
	mes "あなたの服装の色に応じて";
	mes "騎乗生物の色が部分的に";
	mes "サンプルと違うこともございます。";
	mes "よくご確認くださいね。";
	close;
}

//============================================================
// コスチュームチェンジチケット
//------------------------------------------------------------
prontera.gat,127,62,4	script	ファッションデザイナー	573,{
	mes "[ファッションデザイナー]";
	mes "うぉっほん！";
	mes "私は冒険者のファッションについて";
	mes "日夜研究と制作を行っている者だ。";
	mes "衣装装備や服の染色も良いが、";
	mes "同じ職業でも服そのものを変更する";
	mes "試みに挑戦しているのだ。";
	next;
	if(Job < Job_RuneKnight || Job > Job_ShadowChaser) {
		mes "[ファッションデザイナー]";
		mes "幾度となく試行錯誤を重ね、";
		mes "新しい服……そう、";
		mes "^0000FFセカンドコスチューム^000000が";
		mes "完成したのだ！";
		next;
		mes "[ファッションデザイナー]";
		mes "セカンドコスチュームは";
		mes "デザイン性だけでなく、";
		mes "3次職ならではの激しい戦闘にも";
		mes "耐えうる機能性、耐久性に優れた";
		mes "こだわりの逸品になっている。";
		next;
		mes "[ファッションデザイナー]";
		mes "君の職業の服が";
		mes "まだ完成していなくて申し訳ない。";
		mes "現在提供している職業は";
		mes "資料を確認して欲しい。";
		next;
		mes "[ファッションデザイナー]";
		mes "時間をかけている分、";
		mes "ずっと着ていたいと思えるような";
		mes "良い物が仕立てられるように";
		mes "全力を尽くさせてもらうよ！";
		next;
		if(select("提供済み職業を確認する","やめる") == 2) {
			mes "[ファッションデザイナー]";
			mes "それでは、また。";
			close;
		}
		mes "‐セカンドコスチューム提供済み職業‐";
		mes "全職対応！^FF0000NEW!!^000000";
		mes "　";
		mes "以上";
		close;
	}
	if(getlook(13) == 0) {
		mes "[ファッションデザイナー]";
		mes "ちょうど良かった！";
		mes "君の職業の新しい服……";
		mes "セカンドコスチュームが";
		mes "完成しているぞ!!";
		next;
		mes "[ファッションデザイナー]";
		mes "^0000FFコスチュームチェンジチケット^000000を";
		mes "持ってくれば、君の服を";
		mes "一瞬で着替えさせてあげよう。";
		mes "何、一瞬だから";
		mes "恥ずかしがることはないぞ！";
		next;
		mes "[ファッションデザイナー]";
		mes "なお、元の服……";
		mes "デフォルトコスチュームに戻す場合も、";
		mes "^0000FFコスチュームチェンジチケット^000000を";
		mes "頂くので、注意してほしい。";
	}
	else {
		mes "[ファッションデザイナー]";
		mes "おお！";
		mes "君、やはり良く似合っているよ！";
		mes "どうだね、服が変わると";
		mes "気持ちも変わるだろう？";
		mes "ファッションは、人を変える";
		mes "力があるのだよ。";
		next;
		mes "[ファッションデザイナー]";
		mes "さて、本日のご用件は何かな？";
		mes "元の服……";
		mes "デフォルトコスチュームが";
		mes "恋しくなったならば、";
		mes "^0000FFコスチュームチェンジチケット^000000で";
		mes "着替えさせてあげよう。";
	}
	next;
	mes "[ファッションデザイナー]";
	mes "どんな服なのか、";
	mes "服を変えた時のエクストラカラーは";
	mes "どんな色なのか、";
	mes "服を変えた後に髪型や髪色を変えたら";
	mes "どうなるか、気になるなら";
	mes "^0000FFドレスルーム^000000を見るといい。";
	next;
	mes "[ファッションデザイナー]";
	mes "さて、どうする？";
	mes "君が望むサービスを";
	mes "選択してくれたまえ。";
	next;
	switch(select("^FF69B4ドレスルーム^000000を見る","^0000FFコスチュームを変更^000000する","やめる")) {
	case 1:
		mes "[ファッションデザイナー]";
		mes "ドレスルームを見るのだね？";
		mes "ドレスルームを開くと、";
		mes "セカンドコスチュームだけでなく";
		mes "服の色、髪型、髪色などを";
		mes "変更したときのイメージを確認できる。";
		next;
		mes "[ファッションデザイナー]";
		mes "あくまでもイメージが確認できる";
		mes "だけなので、ドレスルームで";
		mes "各種変更が実際にできるわけでは";
		mes "ないので注意してほしい。";
		next;
		mes "[ファッションデザイナー]";
		mes "それでは、ごゆっくり。";
		mes "ドレスルームを見たまま";
		mes "装備の着脱や騎乗も出来るぞ。";
		next;
		mes "‐ドレスルームウィンドウは、";
		mes "　開いたまま移動も可能です。";
		mes "　[Esc]キーか、右上の×ボタンで";
		mes "　ウィンドウを閉じることが";
		mes "　できます‐";
		opendressroom;
		close;
	case 2:
		if(getlook(13) == 0) {
			mes "[ファッションデザイナー]";
			mes "君の服装は現在";
			mes "^FF0000デフォルトコスチューム^000000だね。";
			mes "^0000FFセカンドコスチューム^000000に";
			mes "変更するかね？";
			set '@style,1;
		}
		else {
			mes "[ファッションデザイナー]";
			mes "君の服装は現在";
			mes "^FF0000セカンドコスチューム^000000だね。";
			mes "^0000FFデフォルトコスチューム^000000に";
			mes "変更するかね？";
			set '@style,0;
		}
		next;
		if(select("やめておく","^0000FF変更する^000000") == 1) {
			mes "[ファッションデザイナー]";
			mes "そうかね。";
			mes "では、またの機会に。";
			close;
		}
		if(countitem(6959) == 0) {
			mes "[ファッションデザイナー]";
			mes "おや？";
			mes "コスチュームチェンジチケットを";
			mes "持っていないようだね？";
			mes "用意出来たら、また来てくれたまえ。";
			close;
		}
		mes "[ファッションデザイナー]";
		mes "それでは早速、服を着替えさせて";
		mes "あげよう。";
		mes "…………むぅぅぅーーーん!!";
		next;
		misceffect 414,"";
		misceffect 262,"";
		misceffect 273,"";
		mes "[ファッションデザイナー]";
		mes "てやぁっっ!!";
		mes "どうかね？";
		mes "うまくいっただろう!!";
		mes "その服で気持ち新たに";
		mes "楽しく過ごしてくれたまえ!!";
		delitem 6959,1;
		setlook 13,'@style;
		close;
	case 3:
		mes "[ファッションデザイナー]";
		mes "そうかね。";
		mes "では、またの機会に。";
		close;
	}
}
