//= Auriga Script ==============================================================
// Ragnarok Online Fenrir and Sara Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
dali02.gat,97,142,3	script	バーンハード博士#a1	865,{
	if(checkquest(120165)&8 == 0) {
		mes "[バーンハード博士]";
		mes "私はシュバルツバルド最高の";
		mes "兵器研究をしている、";
		mes "バーンハードという者だ。";
		next;
		mes "[バーンハード博士]";
		mes "終わらなき研究の末に";
		mes "多くの兵器を作り上げてきたが、";
		mes "まだ何かが足りない気がしていた。";
		next;
		mes "[バーンハード博士]";
		mes "そんな中、私は";
		mes "古書に記された兵器の研究を";
		mes "進めていた時、";
		mes "この場所にある次元の狭間の";
		mes "存在を知った。";
		next;
		mes "[バーンハード博士]";
		mes "そして、さらに強力で、";
		mes "優れた兵器を造るためには、";
		mes "過去に輝いた時代の遺物が";
		mes "必要だと言う事実を知ったのだ。";
		next;
		mes "[バーンハード博士]";
		mes "強力な兵器を作り上げるためには、";
		mes "遠い過去、強大な力を持った";
		mes "2人の魔導士の激しい戦闘で";
		mes "現れたという^ff0000ギガンテスの破片^000000";
		mes "という物質が必要だ。";
		next;
		mes "[バーンハード博士]";
		mes "しかし私は、";
		mes "この場所を離れる訳にはいかない。";
		mes "それに、私のような非力な科学者が";
		mes "魔導士たちの激しい戦闘の場へ行っても";
		mes "何もできないだろう。";
		next;
		mes "[バーンハード博士]";
		mes "そしてこのギガンテスの破片……";
		mes "この破片から想像するに、";
		mes "ギガンテスも大きく、";
		mes "強いものであったに違いない。";
		mes "私のような者の力では";
		mes "到底敵わないだろう。";
		next;
		mes "[バーンハード博士]";
		mes "そこで私は、私の代わりに";
		mes "破片を集めてくれる";
		mes "勇者を探しているのだ。";
		mes "君が私に協力してくれると";
		mes "嬉しいのだが……。";
		next;
		mes "[バーンハード博士]";
		mes "どうだ？";
		mes "過去に行き、ギガンテスの破片を";
		mes "探し出してきてはくれないか？";
		mes "もちろん、報酬は弾むぞ。";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[バーンハード博士]";
			mes "気が変わったら";
			mes "また訪ねて来てくれ。";
			close;
		}
		mes "[バーンハード博士]";
		mes "そうか、引き受けてくれるか！";
		mes "ありがとう、本当に助かるよ。";
		next;
		mes "[バーンハード博士]";
		mes "それでは、フェンリルとサラがいた";
		mes "過去のグラストヘイムに行く時は";
		mes "私に話しかけてくれ。";
		mes "よろしく頼む。";
		setquest 120165;
		compquest 120165;
		close;
	}
	if(checkquest(9337)) {
		if(checkquest(120150) == 0) {
			mes "[バーンハード博士]";
			mes "おお、君か。";
			mes "過去のグラストヘイムは";
			mes "危険な状況だっただろう？";
			next;
			mes "[バーンハード博士]";
			mes "手伝ってくれたお礼に";
			mes "この美しいピアスの";
			mes "どちらかを受け取ってくれ。";
			next;
			mes "‐^ff0000ヒールピアス";
			mes "　ヒールLv1使用可能^000000‐";
			mes "　";
			mes "‐^5500ffテレポートピアス";
			mes "　テレポートLv1使用可能^000000‐";
			next;
			mes "[バーンハード博士]";
			mes "このピアスは私の助手が";
			mes "^ff0000ギガンテスの破片^000000と";
			mes "交換もしている。";
			mes "助手に頼めば";
			mes "無料でエンチャントも可能だ。";
			mes "きっと役に立つだろう。";
			next;
			switch(select("^ff0000ヒールピアス^000000を貰う","^5500ffテレポートピアス^000000を貰う","会話をやめる")) {
			case 1:
				set '@itemid,28384;
				break;
			case 2:
				set '@itemid,28385;
				break;
			case 3:
				mes "[バーンハード博士]";
				mes "そうか。";
				close;
			}
			mes "[バーンハード博士]";
			mes "ギガンテスの破片は";
			mes "多ければ多いほど助かる。";
			mes "たくさん集めてきて欲しい。";
			next;
			mes "[バーンハード博士]";
			mes "ただし次元移動機の";
			mes "エネルギー充填には時間がかかる。";
			mes "しばらくしてからまた来てくれ。";
		}
		else {
			mes "[バーンハード博士]";
			mes "おお、君か。";
			mes "過去のグラストヘイムはどうだったか？";
			mes "危険な状況だっただろう？";
			mes "ご苦労だった。";
			next;
			mes "[バーンハード博士]";
			mes "それで、";
			mes "ギガンテスの破片は見つかったか？";
			mes "持ち帰ってきてはくれたのか？";
			mes "破片を手に入れる事が出来たのであれば";
			mes "それを私に譲ってほしい。";
			next;
			mes "[バーンハード博士]";
			mes "君がまた私を手伝ってくれて、";
			mes "ギガンテスの破片を";
			mes "集めてくれるのであれば、";
			mes "それに相応する";
			mes "エンチャントを付けるよう";
			mes "私の助手に言っておこう。";
			next;
			mes "[バーンハード博士]";
			mes "ギガンテスの破片は";
			mes "多ければ多いほど助かる。";
			mes "たくさん集めて";
			mes "彼の元を訪れるといい。";
			next;
			mes "[バーンハード博士]";
			mes "君さえ良かったら";
			mes "また調査に協力して欲しい。";
			mes "ただし次元移動機の";
			mes "エネルギー充填には時間がかかる。";
			mes "しばらくしてからまた来てくれ。";
		}
		next;
		mes "[インフォメーション]";
		mes "‐^ff0000入場してから1回目の午前5時以降^000000";
		mes "　且つ";
		mes "　^ff0000最後の入場から1時間経過後^000000";
		mes "　に再度入場可能になります‐";
		delquest 9337;
		setquest 9337;
		delquest 9337;
		//custom
		if(checkquest(120150) == 0) {
			setquest 120150;
			compquest 120150;
		}
		if('@itemid)
			getitem '@itemid, 1;
		close;
	}
	if(checkquest(9336)) {
		if(checkquest(9336)&2 && checkquest(120195)&2) {
			mes "[バーンハード博士]";
			mes "次元移動機のエネルギー充填が";
			mes "完了したようだ。";
			mes "これで過去のグラストヘイムへ";
			mes "移動することが可能になった。";
			next;
			mes "[バーンハード博士]";
			mes "強力な兵器を作り上げるためには、";
			mes "ギガンテスの破片という物質が必要だ。";
			mes "もう一度過去に行って";
			mes "ギガンテスの破片を";
			mes "探し出してきてくれるか？";
			mes "もちろん、報酬は弾むぞ。";
			delquest 9336;
			delquest 120195;
			close;
		}
		mes "[バーンハード博士]";
		mes "次元の狭間を開くには";
		mes "多くのエネルギーが必要になるから、";
		mes "しばらくは休んでいてくれ。";
		next;
		mes "[インフォメーション]";
		mes "‐^ff0000入場してから1回目の午前5時以降^000000";
		mes "　且つ";
		mes "　^ff0000最後の入場から1時間経過後^000000";
		mes "　に再度入場可能になります‐";
		close;
	}
	mes "[バーンハード博士]";
	mes "過去のグラストヘイムに行く";
	mes "準備は出来たのか？";
	mes "そちらがよければ";
	mes "次元の狭間を開こう。";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[バーンハード博士]";
		mes "おっと、すまない。";
		mes "次元移動機を作動させたいなら";
		mes "^ff0000パーティーのリーダー^000000が";
		mes "私に話かけてくれ。";
		close;
	}
	if(select("はい","いいえ") == 2) {
		mes "[バーンハード博士]";
		mes "気が変わったら";
		mes "また訪ねて来てくれ。";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[バーンハード博士]";
		mes "まだ次元移動機が";
		mes "作動できていない。";
		mes "少し待ってくれ。";
		close;
	}
	mdcreate "glast_sara";
	mes "[バーンハード博士]";
	mes "さあ、フェンリルとサラがいた時代の";
	mes "過去のグラストヘイムに行けるよう、";
	mes "次元移動機を作動させておいた。";
	mes "あちらへ行ける時間は長くない。";
	mes "扉が開いたら、急いで向かってくれ。";
	close;
OnInit:
	waitingroom "フェンリルとサラ",0;
	end;
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
dali02.gat,93,146,6	script	助手#a1	851,{
	mes "[助手]";
	mes "ギガンテスの破片を集めています。";
	mes "特殊なピアスと交換したり、";
	mes "精錬値+9以上のサラのローブを";
	mes "覚醒させる事が出来ます。";
	mes "また、ピアスには";
	mes "無料でエンチャントも出来ますよ。";
	next;
	switch(select("ピアスの交換","エンチャント/初期化","サラのローブを覚醒させる","やめる")) {
	case 1:
		mes "[助手]";
		mes "ピアスは2種類あります。";
		mes "ヒールピアス、テレポートピアス";
		mes "どちらも^ff0000ギガンテスの破片10個^000000で";
		mes "交換可能ですよ。";
		next;
		switch(select("交換しない","ヒールピアスと交換","テレポートピアスと交換")) {
		case 1:
			mes "[助手]";
			mes "そうですか。";
			close;
		case 2:
			set '@gain,28384;
			break;
		case 3:
			set '@gain,28385;
			break;
		}
		if(checkitemblank() == 0) {
			mes "[助手]";
			mes "アイテムの種類数が多いです。";
			mes "荷物を減らしてください。";
			close;
		}
		if(countitem(6803) < 10) {
			mes "[助手]";
			mes "^006400ギガンテスの破片^00000010個を";
			mes "持っていないようです。";
			close;
		}
		delitem 6803,10;
		getitem '@gain,1;
		mes "[助手]";
		mes "^006400ギガンテスの破片^00000010個と";
		mes getitemname('@gain)+ "を";
		mes "交換しました。";
		close;
	case 2:
		break;
	case 3:
		mes "[助手]";
		mes "こちらでは、サラのローブを";
		mes "覚醒させたり、エンチャントを";
		mes "行なう事ができます。";
		next;
		switch(select("サラのローブを覚醒させる","覚醒ローブエンチャント","覚醒ローブについて聞く","やめる")) {
		case 1:
			mes "[助手]";
			mes "覚醒させる場合、精錬値やカードは";
			mes "リセットされてしまいますので";
			mes "ご注意ください。";
			mes "また、覚醒したい";
			mes "サラのローブを装備してから";
			mes "話しかけてくださいね。";
			next;
			if(select("覚醒させる","やめておく") == 2) {
				mes "[助手]";
				mes "そうですか。";
				close;
			}
			if(getequipid(2) != 15121) {
				mes "[助手]";
				mes "おや？";
				mes "サラのローブを装備されていませんね。";
				mes "覚醒させる場合には";
				mes "サラのローブを装備してから";
				mes "話しかけてくださいね。";
				close;
			}
			set '@refine,getequiprefinerycnt(2);
			if('@refine < 9) {
				mes "[助手]";
				mes "おや？";
				mes "サラのローブの精錬値が";
				mes "不足しているようですね。";
				mes "サラのローブを覚醒させるには";
				mes "精錬値が+9以上必要です。";
				close;
			}
			delequip 2;
			getitem 15157,1;
			// 未調査
			mes "[助手]";
			mes "覚醒は終了しました。";
			mes "どうぞ、お受け取り下さい。";
			close;
		case 2:
			mes "[助手]";
			mes "あなたは精錬値が+9以上の";
			mes "覚醒ローブをお持ちですか？";
			next;
			mes "[助手]";
			mes "もし、お持ちなら、";
			mes "精錬値やカードはそのままに";
			mes "暴走した魔力という能力を";
			mes "覚醒ローブに";
			mes "エンチャントします。";
			next;
			mes "[助手]";
			mes "エンチャントしますか？";
			next;
			if(select("エンチャントをする","やめておく") == 2) {
				mes "[助手]";
				mes "そうですか。";
				close;
			}
			if(getequipid(2) != 15157) {
				mes "[助手]";
				mes "おや？";
				mes "覚醒ローブを";
				mes "装備されていませんね。";
				mes "エンチャントをする場合には";
				mes "覚醒ローブを装備してから";
				mes "話しかけてくださいね。";
				close;
			}
			// エンチャント済み(仮)
			if(getequipcardid(2,3) == 4876) {
				mes "[助手]";
				mes "おや？";
				mes "その覚醒ローブは";
				mes "すでにエンチャントされています。";
				close;
			}
			set '@refine,getequiprefinerycnt(2);
			if('@refine < 9) {
				mes "[助手]";
				mes "おや？";
				mes "覚醒ローブの精錬値が";
				mes "不足しているようですね。";
				mes "覚醒ローブに";
				mes "エンチャントを行なうには";
				mes "精錬値が9以上必要です。";
				close;
			}
			set '@card[0],getequipcardid(2,0);
			set '@card[1],getequipcardid(2,1);
			set '@card[2],getequipcardid(2,2);
			set '@card[3],4876;		// 暴走した魔力
			delequip 2;
			getitem2 15157,1,1,'@refine,0,'@card[0],'@card[1],'@card[2],'@card[3];
			mes "[助手]";
			mes "エンチャントは終了しました。";
			mes "どうぞ、お受け取り下さい。";
			close;
		case 3:
			mes "[助手]";
			mes "こちらでは、精錬値が+9以上の";
			mes "サラのローブを覚醒させることが";
			mes "できます。";
			next;
			mes "[助手]";
			mes "覚醒ローブの性能は";
			mes "以下の通りです。";
			next;
			mes "[覚醒ローブ]";
			mes "Mdef + 10";
			mes "―――――――――――――";
			mes "スキルディレイ - 10%";
			mes "―――――――――――――";
			mes "詠唱が中断されない";
			mes "―――――――――――――";
			mes "[覚醒ローブ]の";
			mes "精錬値が1上がる度に、追加で";
			mes "Matk + 15";
			mes "闇属性魔法攻撃で";
			mes "与えるダメージ + 2%";
			mes "―――――――――――――";
			mes "[ヒールピアス]";
			mes "[テレポートピアス]と";
			mes "共に装備時、追加で";
			mes "詠唱時間 - 10%";
			mes "固定詠唱時間 - 50%";
			mes "―――――――――――――";
			mes "[バースリーカード]と";
			mes "共に装備時、";
			mes "絶対に凍結状態にならない";
			mes "―――――――――――――";
			mes "系列 : 鎧";
			mes "防御 : 35";
			mes "重量 : 80";
			mes "要求レベル : 100";
			mes "装備 : ノービス系を除く全ての職業";
			next;
			mes "[助手]";
			mes "また、覚醒ローブの";
			mes "精錬値を+9以上にすると";
			mes "特別なエンチャントを";
			mes "覚醒ローブに";
			mes "施して差し上げます。";
			next;
			mes "[助手]";
			mes "なんと！、";
			mes "精錬値やカードはそのままに";
			mes "暴走した魔力という能力を";
			mes "覚醒ローブに";
			mes "エンチャントできるのです。";
			next;
			mes "[助手]";
			mes "暴走した魔力の能力は";
			mes "以下の通りです。";
			next;
			mes "[暴走した魔力]";
			mes "魔法攻撃命中時、";
			mes "一定確率で10秒間、";
			mes "[暴走した魔力]発動";
			mes "―――――――――――――";
			mes "[暴走した魔力]発動時、";
			mes "Int + 200";
			mes "1秒毎にSP - 200";
			mes "―――――――――――――";
			mes "[カルデュイの耳]、";
			mes "[ラフィネシールド]と";
			mes "共に装備時、";
			mes "[コメット]の";
			mes "再使用待機時間減少効果が";
			mes "発動しない";
			mes "―――――――――――――";
			mes "[堕ちた大神官ヒバムカード]";
			mes "と共に装備時、";
			mes "[堕ちた大神官ヒバムカード]";
			mes "の効果が発動しない";
			next;
			mes "[助手]";
			mes "とても魅力的だと思いますので";
			mes "サラのローブをお持ちなら";
			mes "ぜひ、覚醒やエンチャントを";
			mes "ご依頼ください。";
			close;
		case 4:
			mes "[助手]";
			mes "そうですか。";
			close;
		}
	case 4:
		mes "[助手]";
		mes "そうですか。";
		close;
	}
	mes "[助手]";
	mes "どちらをしますか？";
	next;
	switch(select("エンチャント","初期化","会話をやめる")) {
	case 1:
		set '@type,1;
		break;
	case 2:
		set '@type,2;
		mes "[助手]";
		mes "初期化には^ff0000ギガンテスの破片5個^000000";
		mes "必要です。";
		next;
		mes "[助手]";
		mes "ですが、過去のグラストヘイムの";
		mes "調査を完了してきた方には";
		mes "^ff0000無料^000000で初期化をしています。";
		mes "ぜひ、ご利用ください。";
		next;
		mes "^ff0000‐無料の初期化は繰り返し可能です。";
		mes "　但し回数のストックは出来ません。‐^000000";
		next;
		mes "[助手]";
		mes "なお、あなたは現在、";
		if(checkquest(120170))
			mes "^0000ff無料で初期化が可能^000000";
		else
			mes "^ff0000無料で初期化ができない^000000";
		mes "みたいですね。";
		next;
		break;
	case 3:
		mes "[助手]";
		mes "そうですか。";
		close;
	}
	mes "[助手]";
	mes "エンチャントまたは初期化をするには";
	mes "ヒールピアスまたはテレポートピアスを";
	mes "装備している必要があります。";
	next;
	switch(select(
			(getequipid(7)!=0? "^nItemID^" +getequipid(7): "アクセサリー[1]‐装備していない"),
			(getequipid(8)!=0? "^nItemID^" +getequipid(8): "アクセサリー[2]‐装備していない"))
	) {
	case 1: set '@itemid,getequipid(7); set '@menu,7; break;
	case 2: set '@itemid,getequipid(8); set '@menu,8; break;
	}
	if('@itemid != 28384 && '@itemid != 28385) {
		mes "[助手]";
		mes "ヒールピアスまたはテレポートピアスを";
		mes "装備してください。";
		close;
	}
	if('@type == 1) {
		if(getequipcardid('@menu,0)) {
			mes "[助手]";
			mes "すでにエンチャント済みですね。";
			mes "　";
			mes "初期化をすれば";
			mes "もう一度エンチャントできます。";
			close;
		}
		setarray '@table1$,"Str","Agi","Vit","Int","Dex","Luk";
		setarray '@table2$,"MaxHP","MaxSP","Mdef";
		mes "[助手]";
		mes "一、二番目のスロットは";
		mes "効果の種類を選択出来ます。";
		mes "　";
		mes "一番目のスロットに";
		mes "どんな能力を付与しますか？";
		next;
		set '@socket1,select("Str","Agi","Vit","Int","Dex","Luk")-1;
		switch('@socket1) {
		case 0: setarray '@bonus1, 4700, 4701, 4702, 4703, 4704; break;
		case 1: setarray '@bonus1, 4730, 4731, 4732, 4733, 4734; break;
		case 2: setarray '@bonus1, 4740, 4741, 4742, 4743, 4744; break;
		case 3: setarray '@bonus1, 4710, 4711, 4712, 4713, 4714; break;
		case 4: setarray '@bonus1, 4720, 4721, 4722, 4723, 4724; break;
		case 5: setarray '@bonus1, 4750, 4751, 4752, 4753, 4754; break;
		}
		mes "[助手]";
		mes "二番目のスロットに";
		mes "どんな能力を付与しますか？";
		next;
		set '@socket2,select("MaxHP","MaxSP","Mdef")-1;
		switch('@socket2) {
		case 0: setarray '@bonus2, 4861, 4862, 4867, 4868, 4900; break;
		case 1: setarray '@bonus2, 4800, 4870, 4871, 4801, 4802; break;
		case 2: setarray '@bonus2, 4890, 4786, 4891, 4787, 4892; break;
		}
		mes "[助手]";
		mes "一番目のスロットは" +'@table1$['@socket1]+ "、";
		mes "二番目のスロットは" +'@table2$['@socket2]+ "、";
		mes "三番目、四番目のスロットは";
		mes "ランダムで効果がつきます。";
		mes "　";
		mes "これでよろしいですか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[助手]";
			mes "そうですか。";
			mes "考えが決まってから";
			mes "声をかけてください。";
			close;
		}
		mes "[助手]";
		mes "では、いきます。";
		next;
		if(checkitemblank() == 0) {
			mes "[助手]";
			mes "アイテムの種類数が多いです。";
			mes "荷物を減らしてください。";
			close;
		}
		setarray '@bonus3, 4945, 4946, 4762, 4942, 4949, 4767, 4806, 4869, 4815, 4832;
		setarray '@bonus4, 4946, 4947, 4943, 4944, 4949, 4950, 4815, 4814, 4832, 4833;
		misceffect 182,"";
		misceffect 205,"";
		misceffect 102,"";
		misceffect 104,"";
		set '@card[0],'@bonus1[rand(getarraysize('@bonus1))];
		set '@card[1],'@bonus2[rand(getarraysize('@bonus2))];
		set '@card[2],'@bonus3[rand(getarraysize('@bonus3))];
		set '@card[3],'@bonus4[rand(getarraysize('@bonus4))];
		delequip '@menu;
		getitem2 '@itemid,1,1,0,0,'@card[0],'@card[1],'@card[2],'@card[3];
		mes "[助手]";
		mes "はい、どうぞ。";
		close;
	}
	else {
		mes "[助手]";
		mes "初期化をした場合、失われた能力を";
		mes "戻す事は不可能です。";
		mes "本当に初期化しますか？";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[助手]";
			mes "そうですか。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[助手]";
			mes "アイテムの種類数が多いです。";
			mes "荷物を減らしてください。";
			close;
		}
		if(checkquest(120170)) {
			setquest 120170;
			delquest 120170;
		}
		else {
			if(countitem(6803) < 5) {
				mes "[助手]";
				mes "残念ですがギガンテスの破片が";
				mes "足りていません。";
				mes "5個必要です。";
				close;
			}
			delitem 6803,5;
		}
		misceffect 182,"";
		misceffect 205,"";
		misceffect 338,"";
		delequip '@menu;
		getitem '@itemid,1;
		mes "[助手]";
		mes "うまく初期化できました。";
		close;
	}

OnInit:
	waitingroom "交換・エンチャント",0;
	end;
}

dali02.gat,99,148,3	script	次元移動機#XX1	10007,{
	if(checkquest(9336)) {
		mes "‐エネルギー充填が完了していません。";
		mes "　次元移動機は";
		mes "　^ff0000入場してから1回目の午前5時以降^000000";
		mes "　且つ";
		mes "　^ff0000最後の入場から1時間経過後^000000";
		mes "　に利用可能です‐";
		close;
	}
	mes "‐フェンリルとサラが";
	mes "　激しい戦闘を行った";
	mes "　過去のグラストヘイムへと続く";
	mes "　次元移動機だ‐";
	next;
	if(select("次元の狭間に入る","次元の狭間に入らない") == 2) {
		mes "‐あなたは次元移動機から離れた‐";
		close;
	}
	switch(mdenter("glast_sara")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[glast_sara] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
		setquest 9336;
		setquest 120195;
		donpcevent getmdnpcname("FenrirSaraControl")+"::OnStart";
		close2;
		//warp "1@glast.gat",367,304;
		end;
	case 1:	// パーティー未加入
		mes "‐パーティーリーダーが";
		mes "　メモリアルダンジョンを";
		mes "　生成したパーティーのメンバーのみ、";
		mes "　メモリアルダンジョンに入れます‐";
		close;
	case 2:	// ダンジョン未作成
		mes "‐メモリアルダンジョン";
		mes "　glast_saraが存在しません。";
		mes "　パーティーリーダーが";
		mes "　メモリアルダンジョンを";
		mes "　生成していない状態です‐";
		close;
	default:	// その他エラー
		close;
	}
}

//============================================================
// フェンリルとサラ
//------------------------------------------------------------
1@glast.gat,1,1,0	script	FenrirSaraControl	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;

	hideonnpc getmdnpcname("#glast_move_01");
	hideonnpc getmdnpcname("サラ・アイリン#glast_10");
	hideonnpc getmdnpcname("#glast_move_04");
	hideonnpc getmdnpcname("サラの幻影#glast_50");
	hideonnpc getmdnpcname("フェンリル#glast_11");
	hideonnpc getmdnpcname("#glast_move_01_jp");
	hideonnpc getmdnpcname("サラ・アイリン#chase");
	hideonnpc getmdnpcname("フェンリル#chase");
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("サラの幻影#chase_"+'@i);
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("宝箱#glast_sara"+'@i);
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("レッドギガンテス#fas_0"+'@i);
	hideonnpc getmdnpcname("#fas_gimmick_1");
	hideonnpc getmdnpcname("#fas_gimmick_2");
	hideonnpc getmdnpcname("#fas_gimmick_3");
	hideonnpc getmdnpcname("#fas_gimmick_4");
	hideonnpc getmdnpcname("#fas_gimmick_5");
	hideonnpc getmdnpcname("#glast_move_05");
	hideonnpc getmdnpcname("#glast_move_06");
	hideonnpc getmdnpcname("サラの幻影#ex_battle");

	hideonnpc getmdnpcname("#effect_glast_event01");
	hideonnpc getmdnpcname("#effect_glast_event02");
	hideonnpc getmdnpcname("#effect_glast_event03");
	hideonnpc getmdnpcname("#effect_glast_event04");
	hideonnpc getmdnpcname("#effect_glast_event05");
	hideonnpc getmdnpcname("#effect_glast_event06");
	hideonnpc getmdnpcname("#effect_glast_event07");
	hideonnpc getmdnpcname("#effect_glast_event08");

	hideonnpc getmdnpcname("#fas_bgm_change01");
	donpcevent getmdnpcname("#fas_effect1")+"::OnStart";
	donpcevent getmdnpcname("#fas_effect2")+"::OnStart";
	end;
}

1@glast.gat,359,294,4	script	フェンリル#glast_01	664,{
	if(getnpctimer(1) || getpartyleader(getcharid(1)) != strcharinfo(0)) {
		//未調査
		cutin "fenrir_a", 2;
		mes "[フェンリル]";
		mes "!?　あなたは……？";
		next;
		mes "[フェンリル]";
		mes " ……敵、ではないようね。";
		mes "私は、フェンリス・フェンリル。";
		mes "あなたはここで何をしているの？";
		mes "ここは危険な場所よ。";
		close2;
		cutin "fenrir_a", 255;
		end;
	}
	if(checkquest(120150)) {
		mes "‐女性がいる‐";
		next;
		if(select("^0000FF会話を早める(ショートカット)^000000","^FF0000女性に話しかける^000000") == 1) {
			mes "‐フェンリルについていこう‐";
			close2;
			hideonnpc getmdnpcname("フェンリル#glast_01");
			hideonnpc getmdnpcname("#glast_event_3");
			hideoffnpc getmdnpcname("#glast_move_01");
			misceffect 6, getmdnpcname("#glast_move_01");
			donpcevent getmdnpcname("callmon#fas")+"::OnStart1";
			announce "‐フェンリルは南へ向かったようです。フェンリルについていこう！‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
			end;
		}
	}
	initnpctimer;
	unittalk "フェンリル : !?　あなたは……？";
	close;
OnTimer2000:
	unittalk "フェンリル : ……敵、ではないようね。";
	end;
OnTimer4000:
	unittalk "フェンリル : 私は、フェンリス・フェンリル。";
	end;
OnTimer6000:
	unittalk "フェンリル : あなたはここで何をしているの？ここは危険な場所よ。";
	end;
OnTimer8000:
	unittalk "フェンリル : ……!!";
	end;
OnTimer10000:
	unittalk "フェンリル : 気を付けて！　モンスターが襲ってくるわっ!!";
	end;
OnTimer12000:
	misceffect 60, getmdnpcname("フェンリル#glast_01");
	monster getmdmapname("1@glast.gat"),355,294,"凶悪なガリオン",3198,1,getmdnpcname("フェンリル#glast_01")+"::OnKilled";
	end;
OnTimer14000:
	unittalk "フェンリル : 少し時間を稼いで！　私の魔法で倒すわ！";
	end;
OnTimer17000:
	unittalk "フェンリル : 真なる天の怒りよ……";
	end;
OnTimer19000:
	unittalk "フェンリル : 地軸を揺るがす雷よ……";
	end;
OnTimer21000:
	unittalk "フェンリル : 私の行く手を塞ぐ者へ鉄槌を！";
	end;
OnTimer22000:
	if(getmapmobs(getmdmapname("1@glast.gat"),getmdnpcname("フェンリル#glast_01")+ "::OnKilled") > 0) {
		unittalk "フェンリル : はああぁぁ！　サンダーストーム!!!";
		misceffect 30,getmdnpcname("#effect_glast_event01");
		misceffect 30,getmdnpcname("#effect_glast_event02");
		misceffect 30,getmdnpcname("#effect_glast_event03");
		misceffect 30,getmdnpcname("#effect_glast_event04");
		misceffect 30,getmdnpcname("#effect_glast_event05");
		misceffect 30,getmdnpcname("#effect_glast_event06");
		misceffect 30,getmdnpcname("#effect_glast_event07");
		misceffect 30,getmdnpcname("#effect_glast_event08");
		killmonster getmdmapname("1@glast.gat"),getmdnpcname("フェンリル#glast_01")+ "::OnKilled";
	}
	else
		unittalk "フェンリル : 倒してくれたのね。";
	end;
OnTimer24000:
	unittalk "フェンリル : ふぅ。何故こんなところにガリオンが……。";
	end;
OnTimer26000:
	unittalk "フェンリル : この辺には生息していないはず。まさか奴らか……!!";
	end;
OnTimer28000:
	unittalk "フェンリル : だとするとまずいわね……急がないと……！";
	end;
OnTimer30000:
	unittalk "フェンリル : 私は探し物があって、グラストヘイムに来たの。";
	end;
OnTimer33000:
	unittalk "フェンリル : だけど……ここにはそれを邪魔する奴らがいるみたいだわ。";
	end;
OnTimer35000:
	unittalk "フェンリル : ……。";
	end;
OnTimer37000:
	unittalk "フェンリル : ねぇ、私に協力してくれないかしら？　お願い。";
	end;
OnTimer39000:
	unittalk "フェンリル : もし協力してくれるのならば私についてきて！　奴らが襲ってくる前に早く行きましょう！";
	end;
OnTimer42000:
	hideonnpc getmdnpcname("フェンリル#glast_01");
	misceffect 60, getmdnpcname("フェンリル#glast_01");
	announce "‐フェンリルは南へ向かったようです。フェンリルについていこう！‐", 0x9, 0xffff00, 0x190, 20, 0, 0;
	hideoffnpc getmdnpcname("#glast_move_01");
	misceffect 6, getmdnpcname("#glast_move_01");
	donpcevent getmdnpcname("callmon#fas")+"::OnStart1";
	end;
OnTimer43000:
	stopnpctimer;
	misceffect 317, getmdnpcname("#glast_move_01");
	end;
OnKilled:
	end;
}

1@glast.gat,352,279,0	script	#glast_move_01	45,4,4,{
	mes "‐フェンリルを追いかけますか？‐";
	next;
	switch(select("^0000FF急いで移動する(ショートカット)^000000","^FF0000歩いて移動する^000000")) {
	case 1:
		mes "‐あなたはフェンリルの";
		mes "　後を急いで追いかけた‐";
		close2;
		warp getmdmapname("1@glast.gat"),47,264;
		end;
	case 2:
		mes "‐あなたは歩いて";
		mes "　フェンリルの後を追う事にした。";
		mes "　フェンリルのいる";
		mes "　西側の場所まで行こう‐";
		close2;
		warp getmdmapname("1@glast.gat"),347,265;
		end;
	}
}

1@glast.gat,347,265,0	script	#fas_compass_1	139,4,4,{
	viewpoint 1, 47, 270, 0, 0xFF0000;
	end;
}

1@glast.gat,47,270,4	script	フェンリル#glast_03	664,{
	cutin "fenrir_a", 2;
	mes "[フェンリル]";
	mes "来てくれたのね、";
	mes "ありがとう！";
	close2;
	cutin "fenrir_a", 255;
	end;
}

1@glast.gat,47,270,0	script	#glast_event_7	139,5,5,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		//未調査
		end;
	}
	viewpoint 2, 1, 1, 0, 0xFFFF00;
	hideonnpc getmdnpcname("#glast_event_7");
	cutin "fenrir_a", 2;
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_03")),"フェンリル : 来てくれたのね、ありがとう！";
	set '@dummy,sleep2(2000);
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_03")),"フェンリル : 時間がないわ！　さあ、こっちよ！";
	set '@dummy,sleep2(3000);
	cutin "fenrir_a", 255;
	hideonnpc getmdnpcname("フェンリル#glast_03");
	warp getmdmapname("1@glast.gat"),40,348;
	end;
}

1@glast.gat,43,347,0	script	#fas_compass_8	139,3,3,{
	viewpoint 2, 1, 1, 0, 0xFFFF00;
	end;
}

1@glast.gat,44,357,0	script	#glast_event_9	139,3,3,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		//未調査
		end;
	}
	if(checkquest(120150)) {
		mes "‐古びた剣がある。";
		mes "　フェンリルの探し物だろうか？‐";
		next;
		if(select("^0000FF先を急ごう(ショートカット)^000000","^FF0000フェンリルに話しかける^000000") == 1) {
			mes "‐先を急ぐ事にした‐";
			close2;
			hideonnpc getmdnpcname("#glast_event_9");
			mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),199,333;
			end;
		}
	}
	cutin "fenrir_a", 2;
	mes "[フェンリル]";
	mes "この剣……";
	mes "とうとう見つけたわ！";
	close2;
	cutin "fenrir_a", 255;
	hideonnpc getmdnpcname("#glast_event_9");
	initnpctimer;
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : これがバルドルが使っていた剣、センチネルブリーズね……。";
	end;
OnTimer3000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : 千年が過ぎた今も……これでバルドルの行方を追う事が出来るわ！";
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : バルドルの生まれ変わり……やっと、やっと探せるわっ!!";
	end;
OnTimer9000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : ……ッ!?　邪悪な力を感じる！";
	end;
OnTimer12000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : 誰かいるわね！　出てきなさい！";
	end;
OnTimer15000:
	hideoffnpc getmdnpcname("サラ・アイリン#glast_10");
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_10")),"サラ : ふふふ……やっぱり追いかけて正解ね。思っていた通りだわ。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_10")),"サラ : その剣が鍵なんでしょう？";
	end;
OnTimer22000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_10")),"サラ : それを使えば、千年の封印でさえも解くことが出来る。そういう事ね、フェンリス・フェンリル？";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : まさか……ヴァルキリー！";
	end;
OnTimer28000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_10")),"サラ : 挨拶が遅れたわね。私の名前はサラ・アイリン。12ヴァルキリーの1人よ。";
	end;
OnTimer31000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_10")),"サラ : フレイヤ様の願いを成し遂げるためにも……ふふふっ……この剣はいただくわっ！";
	end;
OnTimer34000:
	hideonnpc getmdnpcname("サラ・アイリン#glast_10");
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : 待ちなさいっ！";
	end;
OnTimer35000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_04")),"フェンリル : サラを追うわ！　私についてきて！";
	end;
OnTimer38000:
	stopnpctimer;
	mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),199,333;
	end;
}

1@glast.gat,44,357,8	script	フェンリル#glast_04	664,{}

1@glast.gat,46,364,4	script	サラ・アイリン#glast_10	10066,{}

1@glast.gat,44,366,0	script	#fas_effect1	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	initnpctimer;
	misceffect 222, getmdnpcname("#fas_effect1");
	end;
}

1@glast.gat,200,346,4	script	サラ・アイリン#glast_jp	10066,{}

1@glast.gat,200,340,0	script	フェンリル#b	664,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		//未調査
		end;
	}
	mes "‐フェンリルとサラが対峙している!‐";
	if(checkquest(120150))
		set '@str$,"^0000FF先に出口へ向かう(ショートカット)^000000";
	next;
	switch(select('@str$,"^FF0000戦闘を見届ける^000000","少し考える")) {
	case 1:
		hideonnpc getmdnpcname("フェンリル#b");
		hideonnpc getmdnpcname("サラ・アイリン#glast_jp");
		mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),201,202;
		close;
	case 2:
		mes "‐二人の対決を見届ける事にした‐";
		close2;
		initnpctimer;
		end;
	case 3:
		mes "‐対峙した二人を前に、";
		mes "　あなたはどうすべきか";
		mes "　もう少し考えてみることにした‐";
		close;
	}
	end;
OnTimer1000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : やはり追って来たのね、フェンリス・フェンリル。";
	end;
OnTimer4000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : あなたにセンチネルブリーズは渡さないっ！";
	end;
OnTimer7000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : ふん、威勢ばかりは立派ね。この私を倒せるなどと本気で思っているの？";
	end;
OnTimer10000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : 凄い自信ね。さすがはヴァルキリーってところかしら。";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : でも、私を甘くみない事ね！";
	misceffect 8,getmdnpcname("フェンリル#b");
	misceffect 521,getmdnpcname("フェンリル#b");
	end;
OnTimer14000:
	misceffect 583,getmdnpcname("フェンリル#b");
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : 血を代価に召喚したのが火の精霊とは、貴様の血は随分と安いのね。";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : さて、それはどうかしら。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : ……いいわ。貴様の身体ごと、その自信も灰にしてあげる。";
	setnpcdisplay getmdnpcname("サラ・アイリン#glast_jp"),3190;
	hideoffnpc getmdnpcname("#fas_bgm_change01");
	end;
OnTimer24000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : 炎を司る汝に告げる。私が名はフェンリス・フェンリル。";
	end;
OnTimer27000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : 天を切り裂く極限の力よ！　我が手に集いて力となれ。";
	end;
OnTimer30000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : 魂をも燃やし尽くす永久の業火を今ここに！";
	misceffect 903,getmdnpcname("フェンリル#b");
	end;
OnTimer33000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : 時空を貫く天空の剣！";
	misceffect 831,getmdnpcname("サラ・アイリン#glast_jp");
	end;
OnTimer35000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : はぁぁっ!!";
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : はぁぁっ!!";
	end;
OnTimer35500:
	misceffect 886,getmdnpcname("フェンリル#b");
	misceffect 930,getmdnpcname("フェンリル#b");
	misceffect 916,getmdnpcname("サラ・アイリン#glast_jp");
	end;
OnTimer38500:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#glast_jp")),"サラ : 何ッ……!?";
	end;
OnTimer41500:
	unittalk getnpcid(0,getmdnpcname("フェンリル#b")),"フェンリル : 今です！　センチネルブリーズを！";
	end;
OnTimer45500:
	hideonnpc getmdnpcname("フェンリル#b");
	hideonnpc getmdnpcname("サラ・アイリン#glast_jp");
	hideoffnpc getmdnpcname("フェンリル#chase");
	hideoffnpc getmdnpcname("サラ・アイリン#chase");
	end;
OnTimer46500:
	unittalk getnpcid(0,getmdnpcname("フェンリル#chase")),"フェンリル : センチネルブリーズを手に入れたわ!!";
	end;
OnTimer49500:
	stopnpctimer getmdnpcname("#fas_effect2");
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : くっ……！";
	end;
OnTimer52500:
	unittalk getnpcid(0,getmdnpcname("フェンリル#chase")),"フェンリル : ふふ……、少し私の力を甘く見たようね、ヴァルキリー。";
	end;
OnTimer55500:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : くくく……楽しませてくれるじゃないか、フェンリス・フェンリル……！";
	end;
OnTimer58500:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : このまま簡単に逃げられると思わない事ね！";
	end;
OnTimer61500:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : 私の本気を見せてあげる。グラストヘイムを地獄と化してやるわ!!";
	end;
OnTimer63000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : はぁぁぁぁ!!";
	misceffect 651,getmdnpcname("サラ・アイリン#chase");
	end;
OnTimer66000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#chase")),"フェンリル : まずいっ……!!　風の精霊よ！瞬間移動させてっ！";
	end;
OnTimer69000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#chase")),"フェンリル : くっ……!?　先ほどの戦闘で力が……移動がうまくできないっ……！";
	end;
OnTimer71000:
	unittalk getnpcid(0,getmdnpcname("サラ・アイリン#chase")),"サラ : 逃がすか!!";
	end;
OnTimer73000:
	stopnpctimer;
	mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),200,203;
	end;
}

1@glast.gat,200,346,4	script	サラ・アイリン#chase	3190,{}
1@glast.gat,198,350,4	script	フェンリル#chase	664,{}

1@glast.gat,200,340,0	script	#fas_bgm_change01	139,20,20,{
	musiceffect "44";
	end;
}

1@glast.gat,200,350,0	script	#fas_effect2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	initnpctimer;
	misceffect 222, getmdnpcname("#fas_effect2");
	end;
}

1@glast.gat,199,202,0	script	#fas_bgm_change02	139,3,3,{
	musiceffect "147";
	viewpoint 1, 351, 270, 0, 0xFF0000;
	end;
}

1@glast.gat,199,205,0	script	#glast_time_q1	139,3,3,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		//未調査
		end;
	}
	donpcevent getmdnpcname("callmon#fas")+"::OnStart2";
	hideonnpc getmdnpcname("#glast_move_01");
	hideoffnpc getmdnpcname("#glast_move_04");
	hideoffnpc getmdnpcname("#fas_gimmick_1");
	hideoffnpc getmdnpcname("#fas_gimmick_2");
	hideoffnpc getmdnpcname("#fas_gimmick_3");
	hideoffnpc getmdnpcname("#fas_gimmick_4");
	hideoffnpc getmdnpcname("#fas_gimmick_5");
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideoffnpc getmdnpcname("宝箱#glast_sara"+'@i);
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideoffnpc getmdnpcname("レッドギガンテス#fas_0"+'@i);
	if(rand(2))
		hideonnpc getmdnpcname("宝箱#glast_sara8");
	else
		hideonnpc getmdnpcname("レッドギガンテス#fas_01");
	if(rand(2))
		hideonnpc getmdnpcname("宝箱#glast_sara6");
	else
		hideonnpc getmdnpcname("レッドギガンテス#fas_05");
	if(rand(2))
		hideonnpc getmdnpcname("宝箱#glast_sara1");
	else
		hideonnpc getmdnpcname("レッドギガンテス#fas_08");
	if(rand(2))
		hideonnpc getmdnpcname("宝箱#glast_sara9");
	else
		hideonnpc getmdnpcname("レッドギガンテス#fas_03");
	sleep 1000;
	announce "フェンリル : ごめんなさい、力が足りずうまく移動ができなかったわ。　入口で合流しましょう……！", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
	sleep 3000;
	announce "サラ : 逃がさないぞ!!私の魔力の恐ろしさを見せつけてやるわ!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
	sleep 2000;
	announce "‐サラの魔力の影響で、「サラの幻影」、「レッドギガンテス」、「秘宝」が出現しました！", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	initnpctimer;
	sleep 2000;
	announce "‐5分以内にフェンリルの元にたどり着くと、報酬経験値が大幅アップ！さらに「サラの幻影」と戦うことができます‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	sleep 1000;
	donpcevent getmdnpcname("#fas_chase_timer")+"::OnStart";
	end;
OnTimer13000:
OnTimer43000:
OnTimer53000:
	switch(rand(3)) {
	case 0: announce "サラ : 私に楯突いた事を後悔しなさい！", 0x9, 0x00ebff, 0x0190, 20, 0, 0;	break;
	case 1: announce "サラ : 逃げても無駄よ！　塵も残さず消し去ってあげる！", 0x9, 0x00ebff, 0x0190, 20, 0, 0;	break;
	case 2: announce "サラ : あははは！　私から逃げられると思っているの？", 0x9, 0x00ebff, 0x0190, 20, 0, 0;	break;
	}
	end;
OnTimer30000:
	switch('cnt) {
	case 0:
		announce "サラ : ネズミみたいに逃げやがって!!　消滅させてやるっ!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
		sleep 2000;
		announce "フェンリル : サラ、チューチュー。これで満足？捕まえてみなさいっ！", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
		hideonnpc getmdnpcname("#fas_bgm_change02");
		sleep 2000;
		announce "サラ : !!　フェンリル！この足でつぶしてやるわ!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
		break;
	case 1: announce "サラ : どこにいる!!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0; break;
	case 2: announce "サラ : 私の魔法で粉々にしてやるわっ!!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0; break;
	case 3: announce "サラ : 全て、全てを破壊してあげるわっ!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0;	break;
	case 4: announce "サラ : 私が破壊してやる!!!!", 0x9, 0x00ebff, 0x0190, 20, 0, 0;	break;
	}
	end;
OnTimer50000:
	if('cnt == 4)
		announce "‐10秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer55000:
	if('cnt == 4)
		announce "‐5秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer56000:
	if('cnt == 4)
		announce "‐4秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer57000:
	if('cnt == 4)
		announce "‐3秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer58000:
	if('cnt == 4)
		announce "‐2秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer59000:
	if('cnt == 4)
		announce "‐1秒前‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer60000:
	if('cnt == 4) {
		stopnpctimer getmdnpcname("#fas_chase_timer");
		announce "‐5分経過。「サラの幻影」が魔力を失い、消滅しました‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
		hideoffnpc getmdnpcname("フェンリル#glast_11");
		hideoffnpc getmdnpcname("#glast_move_05");
	}
	else {
		initnpctimer;
		set 'cnt,'cnt+1;
		announce "‐" +'cnt+ "分経過‐", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	}
	end;
OnTimer62000:
	announce "フェンリル : お待たせしました！　魔力を十分回復できました！", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer64000:
	announce "フェンリル : これよりみなさんを入口まで転送します！", 0x9, 0xffff00, 0x0190, 20, 0, 0;
	end;
OnTimer66000:
	stopnpctimer;
	mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),351,282;
	end;
}

1@glast.gat,351,269,0	script	#glast_move_04	45,2,2,{
	mes "‐この先に移動すると";
	mes "　^ff0000パーティーメンバー全員^000000が";
	mes "　^ff0000転送^000000されます。";
	mes "　移動してもよろしいですか？";
	if(select("いいえ","はい") == 1)
		close;
	announce "‐サラの魔力の影響が無くなった為、「レッドギガンテス」と「秘宝」が消滅しました‐", 0x9, 0xffff00, 0x190, 20, 0, 0;
	stopnpctimer getmdnpcname("#glast_time_q1");
	stopnpctimer getmdnpcname("#fas_chase_timer");
	hideonnpc getmdnpcname("#glast_move_04");
	hideoffnpc getmdnpcname("フェンリル#glast_11");
	donpcevent getmdnpcname("サラの幻影#glast_50")+"::OnStart";
	mapwarp getmdmapname("1@glast.gat"),getmdmapname("1@glast.gat"),351,282;
	end;
}

1@glast.gat,353,290,8	script	サラの幻影#glast_50	10066,{
	cutin "sarah_hero3_2", 2;
	mes "[サラ]";
	mes "なかなかやるじゃない、フェンリル。";
	mes "うまく逃げたわね。";
	next;
	cutin "sarah_hero3", 2;
	mes "[サラ]";
	mes "ふふ……";
	mes "今日はここまでにしてあげるわ。";
	close2;
	cutin "sarah_hero3", 255;
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	misceffect 718,getmdnpcname("サラの幻影#glast_50");
	end;
OnTimer2000:
	hideoffnpc getmdnpcname("サラの幻影#glast_50");
	misceffect 1065,getmdnpcname("サラの幻影#glast_50");
	end;
OnTimer3000:
	unittalk getnpcid(0,getmdnpcname("サラの幻影#glast_50")),"サラ : なかなかやるじゃない、フェンリル。うまく逃げたわね。";
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("サラの幻影#glast_50")),"サラ : ふふ……今日はここまでにしてあげるわ。";
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_11")),"フェンリル : 願わくば今日で終わりにして欲しいわね。";
	end;
OnTimer9000:
	unittalk getnpcid(0,getmdnpcname("サラの幻影#glast_50")),"サラ : 残念だけど、これが最後だと思わない事ね。";
	end;
OnTimer12000:
	unittalk getnpcid(0,getmdnpcname("サラの幻影#glast_50")),"サラ : きっとまた会う事になるわ!!";
	unittalk getnpcid(0,getmdnpcname("フェンリル#glast_11")),"フェンリル : そう……楽しみに待っているわ。サラ・アイリン。";
	misceffect 718,getmdnpcname("サラの幻影#glast_50");
	end;
OnTimer13000:
	stopnpctimer;
	hideonnpc getmdnpcname("サラの幻影#glast_50");
	end;
}

1@glast.gat,359,294,4	script	フェンリル#glast_11	664,{
	if(checkquest(9337)){
		cutin "fenrir_a", 2;
		mes "[フェンリル]";
		mes "また、どこかでお会いできると";
		mes "良いですね。";
		close2;
		cutin "fenrir_a", 255;
		end;
	}
	cutin "fenrir_a", 2;
	mes "[フェンリル]";
	mes "ご無事で何よりです。";
	mes "私の力が足りなかったばかりに";
	mes "ご迷惑をおかけしました。";
	next;
	set '@time,getnpctimer(0,getmdnpcname("#glast_time_q1"))/1000;
	set '@time,'@time + getvariableofnpc('cnt,getmdnpcname("#glast_time_q1")) * 60;
	if('@time >= 300) {
		mes "[フェンリル]";
		mes "サラの幻影が消えた隙に";
		mes "どうにかみなさんを";
		mes "転送することができました。";
		next;
		mes "[フェンリル]";
		mes "……さて。私はそろそろ行きます。";
		mes "手伝っていただいて";
		mes "ありがとうございました。";
		next;
		mes "[フェンリル]";
		mes "また、どこかでお会いできると";
		mes "良いですね。";
		setquest 9337;	// state=1
		compquest 9337;
		//if(checkquest(120150) == 0) {
		//	setquest 120150;
		//	compquest 120150;
		//}
		close2;
		cutin "fenrir_a", 255;
		end;
	}
	if('flag == 0) {
		set 'flag,1;
		stopnpctimer getmdnpcname("#fas_effect1");
		stopnpctimer getmdnpcname("#fas_effect2");
		hideonnpc getmdnpcname("#fas_bgm_change01");
		hideonnpc getmdnpcname("サラ・アイリン#chase");
		hideonnpc getmdnpcname("フェンリル#chase");
		hideoffnpc getmdnpcname("サラの幻影#ex_battle");
		hideoffnpc getmdnpcname("#glast_move_01_jp");
		hideoffnpc getmdnpcname("#glast_move_05");
		misceffect 6,getmdnpcname("#glast_move_01_jp");
		misceffect 6,getmdnpcname("#glast_move_05");
		donpcevent getmdnpcname("callmon#fas")+"::OnStart3";
		set '@dummy,sleep2(1000);
		misceffect 317,getmdnpcname("#glast_move_01_jp");
		misceffect 317,getmdnpcname("#glast_move_05");
	}
	mes "[フェンリル]";
	mes "それにしても";
	mes "随分早かったですね。";
	next;
	mes "[フェンリル]";
	mes "……さて。私はそろそろ行きます。";
	mes "手伝っていただいて";
	mes "ありがとうございました。";
	next;
	mes "[フェンリル]";
	mes "どうやら、先ほどサラの召喚した";
	mes "幻影や使い魔が";
	mes "まだ残っているようですが、";
	mes "このまま放っておいても";
	mes "他の冒険者に大きな被害が";
	mes "出る事はないと思います。";
	next;
	mes "[フェンリル]";
	mes "幸いサラ本人は居ませんから、";
	mes "幻影程度ならどうにかなるでしょう。";
	mes "もし、あなた方が奴らを";
	mes "倒してくださると言うのであれば";
	mes "ぜひお願いします。";
	next;
	mes "[フェンリル]";
	mes "私は先を急ぎますので、";
	mes "手伝うことはできませんが、";
	mes "大きな力が残る場所へ移動できるよう";
	mes "道を開いておきました。";
	mes "もしその力と戦うのであれば、";
	mes "南のワープより移動してください。";
	next;
	mes "[フェンリル]";
	mes "もちろん、無理強いは出来ませんので";
	mes "このままお帰りになっても";
	mes "構いませんよ。";
	mes "その場合はどうかお気をつけて";
	mes "お帰り下さい。";
	next;
	mes "[フェンリル]";
	mes "これはお手伝いをして頂いた";
	mes "お礼です。";
	mes "どうか、お受け取りください。";
	next;
	mes "^ff0000‐各種ピアスのエンチャントを";
	mes "　無料で初期化できる権利を";
	mes "　獲得しました‐^000000";
	next;
	mes "[フェンリル]";
	mes "また、どこかでお会いできると";
	mes "良いですね。";
	if(checkitemblank() == 0) {
		next;
		mes "[フェンリル]";
		mes "おや？";
		mes "どうやら荷物の種類が多いようです。";
		mes "荷物の種類を減らしてから";
		mes "また声をかけてください。";
		close2;
		cutin "fenrir_a", 255;
		end;
	}
	setquest 9337;
	compquest 9337;
	//if(checkquest(120150) == 0) {
	//	setquest 120150;
	//	compquest 120150;
	//}
	getexp 3000000,0,1;
	getexp 0,1500000,0;
	getitem 6803,1;
	if(checkquest(120170) == 0) {
		setquest 120170;
		compquest 120170;
	}
	close2;
	cutin "fenrir_a", 255;
	end;
}

1@glast.gat,352,279,0	script	#glast_move_01_jp	45,4,4,{
	mes "‐ここからサラの幻影がいる場所へ";
	mes "　行くことが出来るようだ‐";
	next;
	if(select("この場に留まる","先へ進む") == 1) {
		mes "‐あなたはこの場に留まった‐";
		close;
	}
	mes "‐先へ進むことにした‐";
	close2;
	warp getmdmapname("1@glast.gat"),199,333;
	end;
}

1@glast.gat,1,1,0	script	#fas_chase_timer	139,{
OnStart:
OnTimer5000:
	stopnpctimer;
	for(set '@i,1; '@i<=9; set '@i,'@i+1) {
		unittalk getnpcid(0,getmdnpcname("サラの幻影#chase_"+'@i)),"サラの幻影 : テレポート!!";
		misceffect 34,getmdnpcname("サラの幻影#chase_"+'@i);
	}
	sleep 500;
	for(set '@i,1; '@i<=9; set '@i,'@i+1) {
		hideoffnpc getmdnpcname("サラの幻影#chase_"+'@i);
		misceffect 135,getmdnpcname("サラの幻影#chase_"+'@i);
		set '@dummy,getmapxy('@map$,'@x,'@y,1,getmdnpcname("サラの幻影#chase_"+'@i));
		monster '@map$,'@x,'@y,"#meteo",3199,3,getmdnpcname("#fas_chase_timer")+"::OnKilled";
		monster '@map$,'@x,'@y,"#earth",3200,1,getmdnpcname("#fas_chase_timer")+"::OnKilled";
	}
	sleep 4500;
	for(set '@i,1; '@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("サラの幻影#chase_"+'@i);
	sleep 500;
	killmonster getmdmapname("1@glast.gat"),getmdnpcname("#fas_chase_timer")+"::OnKilled";
	sleep 2000;
	initnpctimer;
	end;
}

1@glast.gat,194,214,5	script	サラの幻影#chase_1	3190,{}
1@glast.gat,207,79,5	script	サラの幻影#chase_2	3190,{}
1@glast.gat,259,54,5	script	サラの幻影#chase_3	3190,{}
1@glast.gat,306,179,5	script	サラの幻影#chase_4	3190,{}
1@glast.gat,357,204,5	script	サラの幻影#chase_5	3190,{}
1@glast.gat,298,210,5	script	サラの幻影#chase_6	3190,{}
1@glast.gat,321,250,5	script	サラの幻影#chase_7	3190,{}
1@glast.gat,335,262,5	script	サラの幻影#chase_8	3190,{}
1@glast.gat,351,258,5	script	サラの幻影#chase_9	3190,{}

1@glast.gat,133,361,4	script	宝箱#glast_sara1	10005,{
	// ダイヤモンド1カラット、ジャルゴン、ルビー、アメジスト、金塊、銀塊、銀塊、ギガンテスの破片、サラのローブ
	setarray '@gain,730,912,723,719,7228,7229,7229,6803,15121;
	setarray '@rate,1000,1000,1000,1000,300,300,300,100,10;
	set '@dummy,getmapxy('@map$,'@x,'@y,1,getmdnpcname(strnpcinfo(0)));
	hideonnpc;
	misceffect 10;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@xs,'@x+rand(3)-1;
		set '@ys,'@y+rand(3)-1;
		if(rand(1000) < '@rate['@i])
			dropitem '@map$,'@xs,'@ys,'@gain['@i],('@i==0? getmapusers('@map$): 1),0;
	}
	end;
}
1@glast.gat,267,351,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara2	10005
1@glast.gat,176,178,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara3	10005
1@glast.gat,200,135,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara4	10005
1@glast.gat,97,38,4		duplicate(宝箱#glast_sara1)	宝箱#glast_sara5	10005
1@glast.gat,366,190,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara6	10005
1@glast.gat,62,279,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara7	10005
1@glast.gat,67,264,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara8	10005
1@glast.gat,302,194,4	duplicate(宝箱#glast_sara1)	宝箱#glast_sara9	10005

1@glast.gat,67,264,4	script	レッドギガンテス#fas_01	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),67,264,"レッドギガンテス#X1",3196,1;
	end;
}

1@glast.gat,245,187,4	script	レッドギガンテス#fas_02	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),245,187,"双斧レッドギガンテス#X2",3193,1;
	end;
}

1@glast.gat,302,197,4	script	レッドギガンテス#fas_03	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),302,197,"レッドギガンテス#X3",3196,1;
	end;
}

1@glast.gat,299,85,6	script	レッドギガンテス#fas_04	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),299,85,"双斧レッドギガンテス#X4",3193,1;
	end;
}

1@glast.gat,366,190,4	script	レッドギガンテス#fas_05	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),366,190,"レッドギガンテス#X5",3196,1;
	end;
}

1@glast.gat,310,299,6	script	レッドギガンテス#fas_06	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),310,299,"双斧レッドギガンテス#X6",3193,1;
	end;
}

1@glast.gat,82,109,6	script	レッドギガンテス#fas_07	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),82,109,"レッドギガンテス#X7",3196,1;
	end;
}

1@glast.gat,133,361,4	script	レッドギガンテス#fas_08	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),133,361,"双斧レッドギガンテス#X8",3193,1;
	end;
}

1@glast.gat,332,61,6	script	レッドギガンテス#fas_09	10067,6,6,{
	end;
OnTouch:
	hideonnpc;
	monster getmdmapname("1@glast.gat"),332,61,"レッドギガンテス#X5",3196,1;
	end;
}

1@glast.gat,132,130,0	script	#fas_gimmick_1	139,6,2,{
	hideonnpc;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#fas_gimmick_1")+"::OnKilled";
	if(rand(2)) {
		monster '@map$,131,120,"ギガンテス#ga1",3194,1,'@label$;
		monster '@map$,132,120,"ギガンテス#ga2",3194,1,'@label$;
		monster '@map$,133,120,"ギガンテス#ga3",3194,1,'@label$;
	}
	else {
		monster '@map$,131,140,"ギガンテス#ga1",3194,1,'@label$;
		monster '@map$,132,140,"ギガンテス#ga2",3194,1,'@label$;
		monster '@map$,133,140,"ギガンテス#ga3",3194,1,'@label$;
	}
	end;
OnKilled:
	end;
}

1@glast.gat,268,130,0	script	#fas_gimmick_2	139,6,2,{
	hideonnpc;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#fas_gimmick_2")+"::OnKilled";
	if(rand(2)) {
		monster '@map$,267,120,"ギガンテス#gb1",3194,1,'@label$;
		monster '@map$,268,120,"ギガンテス#gb2",3194,1,'@label$;
		monster '@map$,269,120,"ギガンテス#gb3",3194,1,'@label$;
	}
	else {
		monster '@map$,267,140,"ギガンテス#gb1",3194,1,'@label$;
		monster '@map$,268,140,"ギガンテス#gb2",3194,1,'@label$;
		monster '@map$,269,140,"ギガンテス#gb3",3194,1,'@label$;
	}
	end;
OnKilled:
	end;
}

1@glast.gat,238,43,0	script	#fas_gimmick_3	139,2,8,{
	hideonnpc;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#fas_gimmick_3")+"::OnKilled";
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_01");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_02");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_03");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_04");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_05");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_06");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_07");
	hideonnpc getmdnpcname("ガーゴイルの石像#fas_08");
	monster '@map$,227,48,"機動のギガンテス#gc1",3195,1,'@label$;
	monster '@map$,250,48,"機動のギガンテス#gc2",3195,1,'@label$;
	monster '@map$,230,51,"サラの使い魔#gc3",3197,1,'@label$;
	monster '@map$,235,51,"サラの使い魔#gc4",3197,1,'@label$;
	monster '@map$,240,51,"サラの使い魔#gc5",3197,1,'@label$;
	monster '@map$,245,51,"サラの使い魔#gc6",3197,1,'@label$;
	monster '@map$,230,44,"サラの使い魔#gc7",3197,1,'@label$;
	monster '@map$,235,44,"サラの使い魔#gc8",3197,1,'@label$;
	monster '@map$,240,44,"サラの使い魔#gc9",3197,1,'@label$;
	monster '@map$,245,44,"サラの使い魔#gc10",3197,1,'@label$;
	end;
OnKilled:
	end;
}

1@glast.gat,298,204,0	script	#fas_gimmick_4	139,7,2,{
	hideonnpc;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#fas_gimmick_4")+"::OnKilled";
	monster '@map$,298,218,"機動のギガンテス#gd1",3195,1,'@label$;
	monster '@map$,298,220,"機動のギガンテス#gd2",3195,1,'@label$;
	monster '@map$,298,222,"機動のギガンテス#gd3",3195,1,'@label$;
	monster '@map$,298,224,"機動のギガンテス#gd4",3195,1,'@label$;
	end;
OnKilled:
	end;
}

1@glast.gat,359,197,0	script	#fas_gimmick_5	139,15,2,{
	hideonnpc;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#fas_gimmick_5")+"::OnKilled";
	monster '@map$,355,209,"機動のギガンテス#ge1",3195,1,'@label$;
	monster '@map$,355,207,"機動のギガンテス#ge2",3195,1,'@label$;
	monster '@map$,355,205,"機動のギガンテス#ge3",3195,1,'@label$;
	monster '@map$,355,203,"機動のギガンテス#ge4",3195,1,'@label$;
	end;
OnKilled:
	end;
}

1@glast.gat,1,1,0	script	callmon#fas	139,{
OnStart1:
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("callmon#fas")+"::OnKilled";
	areamonster '@map$,60,188,75,206,"ギガンテス#aa1",3194,4,'@label$;
	areamonster '@map$,60,188,75,206,"双斧ギガンテス#bb1",3191,4,'@label$;
	areamonster '@map$,127,308,145,324,"ギガンテス#aa2",3194,4,'@label$;
	areamonster '@map$,127,308,145,324,"双斧ギガンテス#bb2",3191,4,'@label$;
	areamonster '@map$,257,318,273,331,"ギガンテス#aa3",3194,4,'@label$;
	areamonster '@map$,257,318,273,331,"双斧ギガンテス#bb3",3191,4,'@label$;
	areamonster '@map$,340,127,352,135,"ギガンテス#aa4",3194,4,'@label$;
	areamonster '@map$,340,127,352,135,"双斧ギガンテス#bb4",3191,4,'@label$;
	areamonster '@map$,190,40,205,56,"ギガンテス#aa5",3194,4,'@label$;
	areamonster '@map$,190,40,205,56,"双斧ギガンテス#bb5",3191,4,'@label$;
	areamonster '@map$,143,39,159,52,"ギガンテス#aa6",3194,4,'@label$;
	areamonster '@map$,143,39,159,52,"双斧ギガンテス#bb6",3191,4,'@label$;
	end;
OnStart2:
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("callmon#fas")+"::OnKilled";
	areamonster '@map$,60,155,78,173,"機動のギガンテス#aa1",3195,4,'@label$;
	areamonster '@map$,60,155,78,173,"機動のギガンテス#bb1",3195,4,'@label$;
	areamonster '@map$,293,76,309,93,"機動のギガンテス#aa1",3195,4,'@label$;
	areamonster '@map$,293,76,309,93,"機動のギガンテス#bb1",3195,4,'@label$;
	areamonster '@map$,329,253,344,271,"機動のギガンテス#aa1",3195,4,'@label$;
	areamonster '@map$,329,253,344,271,"機動のギガンテス#bb1",3195,4,'@label$;
	areamonster '@map$,209,56,223,70,"機動のギガンテス#aa1",3195,4,'@label$;
	areamonster '@map$,209,56,223,70,"機動のギガンテス#bb1",3195,4,'@label$;
	areamonster '@map$,331,65,344,83,"機動のギガンテス#aa1",3195,4,'@label$;
	areamonster '@map$,331,65,344,83,"機動のギガンテス#bb1",3195,4,'@label$;
	end;
OnStart3:
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("callmon#fas")+"::OnKilled";
	monster '@map$,183,333,"ギガンテス",3194,1,'@label$;
	monster '@map$,183,331,"ギガンテス",3194,1,'@label$;
	monster '@map$,183,329,"機動のギガンテス",3195,1,'@label$;
	monster '@map$,183,327,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,185,333,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,185,331,"機動のギガンテス",3195,1,'@label$;
	monster '@map$,185,329,"ギガンテス",3194,1,'@label$;
	monster '@map$,185,327,"ギガンテス",3194,1,'@label$;
	monster '@map$,213,333,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,213,331,"機動のギガンテス",3195,1,'@label$;
	monster '@map$,213,329,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,213,327,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,215,333,"機動のギガンテス",3195,1,'@label$;
	monster '@map$,215,331,"双斧ギガンテス",3191,1,'@label$;
	monster '@map$,215,329,"機動のギガンテス",3195,1,'@label$;
	monster '@map$,215,327,"機動のギガンテス",3195,1,'@label$;
	end;
OnKilled:
	end;
}

1@glast.gat,376,303,0	script	#glast_move_05	45,3,3,{
	mes "‐ここから外に出れるようだ。";
	mes "　外に出ますか？‐";
	next;
	if(select("外に出ない","外に出る") == 1) {
		mes "‐あなたはその場から離れた‐";
		close;
	}
	mes "‐外へ出ます‐";
	close2;
	warp "dali02.gat",91,140;
	end;
}

1@glast.gat,189,342,0	script	#glast_move_06	45,3,3,{
	mes "‐ここから外に出れるようだ。";
	mes "　外に出ますか？‐";
	next;
	if(select("外に出ない","外に出る") == 1) {
		mes "‐あなたはその場から離れた‐";
		close;
	}
	mes "‐外へ出ます‐";
	close2;
	getexp 4000000,0,1;
	getexp 4000000,0,1;
	getexp 4000000,0,1;
	getexp 4000000,0,1;
	getexp 4000000,0,1;
	getexp 0,2000000,0;
	getexp 0,2000000,0;
	getexp 0,2000000,0;
	getexp 0,2000000,0;
	getexp 0,2000000,0;
	warp "dali02.gat",91,140;
	end;
}

1@glast.gat,200,346,4	script	サラの幻影#ex_battle	10066,{
	mes "‐サラの幻影がいる。";
	mes "　戦おうか？‐";
	next;
	if(select("戦う","やめておく") == 2) {
		mes "‐今はやめておこう‐";
		close;
	}
	mes "‐サラの幻影と戦おうと身構えると";
	mes "　幻影もこちらに気付いたようだ‐";
	close2;
	hideonnpc getmdnpcname("サラの幻影#ex_battle");
	donpcevent getmdnpcname("#ex_battle_sara")+"::OnStart";
	end;
}

1@glast.gat,200,346,0	script	#ex_battle_sara	139,{
OnStart:
	sleep 3000;
	initnpctimer;
	set 'mob_id,callmonster(getmdmapname("1@glast.gat"),200,346,"サラの幻影#1",3190,getmdnpcname("#ex_battle_sara")+"::OnKilled");
	end;
OnTimer40000:
	if(getmobhp('mob_id) <= 0) {
		stopnpctimer;
		end;
	}
	initnpctimer;
	set '@map$,getmdmapname("1@glast.gat");
	set '@label$,getmdnpcname("#ex_battle_sara")+"::OnKilled2";
	killmonster '@map$,'@label$;
	areamonster '@map$,183,327,215,333,"機動の双斧ギガンテス",3192,4,'@label$;
	sleep 3000;
	set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob_id);
	switch(rand(5)) {
	case 0:
		mobuseskillpos 'mob_id,85,5,'@x-7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x+7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y+7,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y-7,0,0;	// ロードオブヴァーミリオン
		end;
	case 1:
		mobuseskillpos 'mob_id,85,5,'@x-7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x+7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y+7,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y-7,0,0;	// ロードオブヴァーミリオン
		sleep 5000;
		mobuseskill 'mob_id,85,10,0,0,-1,0,1;	// ロードオブヴァーミリオン
		end;
	case 2:
		mobuseskillpos 'mob_id,85,5,'@x-7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x+7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y+7,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y-7,0,0;	// ロードオブヴァーミリオン
		sleep 1000;
		mobuseskillpos 'mob_id,21,5,'@x-6,'@y-6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x-6,'@y+6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+6,'@y-6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+6,'@y+6,0,0;	// サンダーストーム
		sleep 2000;
		mobuseskillpos 'mob_id,21,5,'@x-3,'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+3,'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x,'@y+3,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x,'@y-3,0,0;	// サンダーストーム
		end;
	case 3:
		mobuseskillpos 'mob_id,85,5,'@x-7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x+7,'@y,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y+7,0,0;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,85,5,'@x,'@y-7,0,0;	// ロードオブヴァーミリオン
		sleep 1000;
		mobuseskillpos 'mob_id,21,5,'@x-6,'@y-6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x-6,'@y+6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+6,'@y-6,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+6,'@y+6,0,0;	// サンダーストーム
		sleep 3000;
		mobuseskill 'mob_id,85,10,0,0,-1,0,1;	// ロードオブヴァーミリオン
		mobuseskillpos 'mob_id,21,5,'@x-3,'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+3,'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x,'@y+3,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x,'@y-3,0,0;	// サンダーストーム
		end;
	case 4:
		mobuseskillpos 'mob_id,21,10,'@x-rand(2,8),'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,10,'@x,'@y+rand(2,8),0,0;	// サンダーストーム
		sleep 500;
		mobuseskillpos 'mob_id,21,10,'@x+rand(2,8),'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,10,'@x,'@y-rand(2,8),0,0;	// サンダーストーム
		sleep 500;
		mobuseskillpos 'mob_id,21,5,'@x-9,'@y-9,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x-10,'@y+10,0,0;	// サンダーストーム
		sleep 2500;
		set '@r,rand(4,6);
		mobuseskillpos 'mob_id,21,5,'@x-'@r,'@y-'@r,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x-'@r,'@y+'@r,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+'@r,'@y-'@r,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,5,'@x+'@r,'@y+'@r,0,0;	// サンダーストーム
		sleep 2000;
		mobuseskillpos 'mob_id,21,10,'@x-rand(1,10),'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,10,'@x-11,'@y-11,0,0;	// サンダーストーム
		sleep 500;
		mobuseskillpos 'mob_id,21,10,'@x,'@y+rand(1,10),0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,10,'@x,'@y-3,0,0;	// サンダーストーム
		sleep 500;
		mobuseskillpos 'mob_id,21,10,'@x+rand(2,6),'@y,0,0;	// サンダーストーム
		mobuseskillpos 'mob_id,21,10,'@x-12,'@y-2,0,0;	// サンダーストーム
		end;
	}
	end;
OnKilled:
	stopnpctimer;
	hideoffnpc getmdnpcname("#glast_move_06");
	misceffect 6,getmdnpcname("#glast_move_06");
	sleep 1000;
	misceffect 317,getmdnpcname("#glast_move_06");
	end;
OnKilled2:
	end;
}

1@glast.gat,352,304,4	script	#effect_glast_event01	844,{}
1@glast.gat,360,304,4	script	#effect_glast_event02	844,{}
1@glast.gat,367,304,4	script	#effect_glast_event03	844,{}
1@glast.gat,366,295,4	script	#effect_glast_event04	844,{}
1@glast.gat,359,296,4	script	#effect_glast_event05	844,{}
1@glast.gat,353,294,4	script	#effect_glast_event06	844,{}
1@glast.gat,356,284,4	script	#effect_glast_event07	844,{}
1@glast.gat,345,283,4	script	#effect_glast_event08	844,{}

1@glast.gat,230,51,3	script	ガーゴイルの石像#fas_01	10070,{}
1@glast.gat,235,51,3	script	ガーゴイルの石像#fas_02	10070,{}
1@glast.gat,240,51,3	script	ガーゴイルの石像#fas_03	10070,{}
1@glast.gat,245,51,3	script	ガーゴイルの石像#fas_04	10070,{}
1@glast.gat,230,44,1	script	ガーゴイルの石像#fas_05	10070,{}
1@glast.gat,235,44,1	script	ガーゴイルの石像#fas_06	10070,{}
1@glast.gat,240,44,1	script	ガーゴイルの石像#fas_07	10070,{}
1@glast.gat,245,44,1	script	ガーゴイルの石像#fas_08	10070,{}

1@glast.gat,42,273,0	script	#バリケード1_1	1905,{}
1@glast.gat,43,273,0	script	#バリケード1_2	1905,{}
1@glast.gat,44,273,0	script	#バリケード1_3	1905,{}
1@glast.gat,45,273,0	script	#バリケード1_4	1905,{}

1@glast.gat,198,325,0	script	#バリケードcenter_2	1905,{}

1@glast.gat,39,343,0	script	#バリケード3_1	1905,{}
1@glast.gat,42,343,0	script	#バリケード3_4	1905,{}
1@glast.gat,45,343,0	script	#バリケード3_7	1905,{}
1@glast.gat,48,343,0	script	#バリケード3_10	1905,{}

1@glast.gat,60,364,0	script	#バリケード4_1	1905,{}
1@glast.gat,60,366,0	script	#バリケード4_3	1905,{}
1@glast.gat,60,368,0	script	#バリケード4_5	1905,{}

1@glast.gat,201,325,0	script	#バリケードcenter_5	1905,{}

1@glast.gat,184,325,0	script	#バリケード6_2	1905,{}
1@glast.gat,186,325,0	script	#バリケード6_4	1905,{}
1@glast.gat,188,325,0	script	#バリケード6_6	1905,{}
1@glast.gat,190,325,0	script	#バリケード6_8	1905,{}
1@glast.gat,192,325,0	script	#バリケード6_10	1905,{}
1@glast.gat,194,325,0	script	#バリケード6_12	1905,{}

1@glast.gat,205,325,0	script	#バリケード7_2	1905,{}
1@glast.gat,207,325,0	script	#バリケード7_4	1905,{}
1@glast.gat,209,325,0	script	#バリケード7_6	1905,{}
1@glast.gat,211,325,0	script	#バリケード7_8	1905,{}
1@glast.gat,213,325,0	script	#バリケード7_10	1905,{}
1@glast.gat,215,325,0	script	#バリケード7_12	1905,{}

1@glast.gat,180,328,0	script	#バリケード8_1	1905,{}
1@glast.gat,180,330,0	script	#バリケード8_3	1905,{}
1@glast.gat,180,332,0	script	#バリケード8_5	1905,{}

1@glast.gat,187,345,0	script	#バリケード9_1	1905,{}
1@glast.gat,189,346,0	script	#バリケード9_2	1905,{}

1@glast.gat,210,346,0	script	#バリケード10_1	1905,{}
1@glast.gat,212,345,0	script	#バリケード10_2	1905,{}

1@glast.gat,219,328,0	script	#バリケード11_1	1905,{}
1@glast.gat,219,330,0	script	#バリケード11_3	1905,{}
1@glast.gat,219,332,0	script	#バリケード11_5	1905,{}

1@glast.gat,345,274,0	script	#バリケード12_1	1905,{}
1@glast.gat,347,274,0	script	#バリケード12_3	1905,{}
1@glast.gat,349,274,0	script	#バリケード12_5	1905,{}
1@glast.gat,351,274,0	script	#バリケード12_7	1905,{}
1@glast.gat,353,274,0	script	#バリケード12_9	1905,{}
1@glast.gat,355,274,0	script	#バリケード12_11	1905,{}
1@glast.gat,357,274,0	script	#バリケード12_13	1905,{}
1@glast.gat,346,273,0	script	#バリケード12_16	1905,{}
1@glast.gat,348,273,0	script	#バリケード12_18	1905,{}
1@glast.gat,350,273,0	script	#バリケード12_20	1905,{}
1@glast.gat,352,273,0	script	#バリケード12_22	1905,{}
1@glast.gat,354,273,0	script	#バリケード12_24	1905,{}
1@glast.gat,356,273,0	script	#バリケード12_26	1905,{}
1@glast.gat,358,273,0	script	#バリケード12_28	1905,{}

1@glast.gat,198,238,0	script	#バリケード13_1	1905,{}
1@glast.gat,199,238,0	script	#バリケード13_2	1905,{}
1@glast.gat,200,238,0	script	#バリケード13_3	1905,{}
1@glast.gat,201,238,0	script	#バリケード13_4	1905,{}
