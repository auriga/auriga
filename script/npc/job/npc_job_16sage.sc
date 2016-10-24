//= Athena Script ==============================================================
// Ragnarok Online Sage Jobchange Script	by Blaze
//= Registry ===================================================================
// CHANGE_SA -> 0～15
//==============================================================================

//============================================================
// 転職
//------------------------------------------------------------
yuno_in02.gat,38,61,5	script	魔法アカデミー学長	743,{
	cutin "job_sage_kayron",2;
	if(Upper == UPPER_HIGH) {
		mes "[ケイロン=グリック]";
		mes "ふむ……";
		mes "長く人を見てきたが、あなたは";
		mes "特別な「能力」を持っているね。";
		next;
		mes "[ケイロン=グリック]";
		mes "あなたはこんな場所にいないで";
		mes "もっと世に出て能力を使ってあげ";
		mes "なさい。";
		mes "初心を忘れてはならないよ。";
		close2;
		cutin "job_sage_kayron",255;
		end;
	}
	if(Job == Job_Sage) {
		mes "[ケイロン=グリック]";
		mes "ふむ、何の用かね？";
		mes "セージになったからといって";
		mes "勉強を怠ってはならないよ。";
		next;
		mes "[ケイロン=グリック]";
		mes "私達の知識は、この大陸の発展に";
		mes "大きく寄与している。";
		mes "すべての人の役にたつように";
		mes "常に研究と記録を欠かさないように。";
		close2;
		cutin "job_sage_kayron",255;
		end;
	}
	if(Job == Job_Novice) {
		mes "[ケイロン=グリック]";
		mes "ん？ここへは何の用で来たのかな？";
		mes "ここまで来るのは大変だったろうに";
		mes "よほどセージへの関心が強いのかな？";
		next;
		mes "[ケイロン=グリック]";
		mes "もしセージが学ぶ学問に興味があるなら";
		mes "まず「マジシャン」になり勉強をし、";
		mes "見識を深めてきなさい。";
		mes "いつかまた会える日を";
		mes "楽しみにしているよ。";
		close2;
		cutin "job_sage_kayron",255;
		end;
	}
	if(Job != Job_Magician) {
		mes "[ケイロン=グリック]";
		mes "ふむう……私達はこの世界について";
		mes "日々研究をしているが、足りないものが";
		mes "ある。";
		mes "それは、他の職業の人々が得る";
		mes "経験に基づいた知識です……";
		next;
		mes "[ケイロン=グリック]";
		mes "もし、近くにセージがいたら";
		mes "あなた方が得た経験についてよく";
		mes "語ってあげてもらいたい。";
		mes "彼らもあなたの助けになってくれる";
		mes "はずです。";
		close2;
		cutin "job_sage_kayron",255;
		end;
	}
	switch(CHANGE_SA) {
	case 0:
	case 1:
	case 2:
		mes "[ケイロン=グリック]";
		mes "魔法に対する情熱を持つ君を";
		mes "歓迎する。";
		mes "ここへは何の用で来たのかな？";
		next;
		switch(select("セージに転職したいです","セージ転職について教えてください","なんでもないです")) {
		case 1:
			mes "[ケイロン=グリック]";
			mes "うん……セージに転職したいと？";
			mes "転職と……";
			mes "まずその考え方から変えなくては";
			mes "ならないな。";
			next;
			mes "[ケイロン=グリック]";
			mes "セージというのは世の中の事物に";
			mes "対する果てしない研究と記録によって";
			mes "大陸の発展に寄与する人のことを指す。";
			mes "であるから、ただ服を着替え";
			mes "見た目だけ変わったとしても、";
			mes "それは意味無きことなのです。";
			next;
			mes "[ケイロン=グリック]";
			mes "まず、シュバイチェル魔法アカデミーに";
			mes "入学願書を提出しなさい。";
			mes "そちらでよく説明してくれるはずです。";
			break;
		case 2:
			mes "[ケイロン=グリック]";
			mes "セージ転職……";
			mes "誰もセージになることを「転職」とは";
			mes "言いません。";
			next;
			mes "[ケイロン=グリック]";
			mes "セージになるためには、";
			mes "まずシュバイチェル魔法アカデミーに";
			mes "入学願書を提出しなさい。";
			mes "そして入学試験を受けてみなさい。";
			next;
			mes "[ケイロン=グリック]";
			mes "試験を受けた後、専攻科目について";
			mes "研究を重ね、最後に論文を";
			mes "提出してもらいます。";
			next;
			mes "[ケイロン=グリック]";
			mes "論文は私が見、評価します。";
			mes "そこで合格すれば、セージとして";
			mes "生きていく資格を与えましょう。";
			next;
			mes "[ケイロン=グリック]";
			mes "まずはシュバイチェル魔法アカデミーに";
			mes "行って見なさい。";
			mes "メテウス=シルプという若いセージに";
			mes "申し込みをするように。";
			break;
		case 3:
			mes "[ケイロン=グリック]";
			mes "ふむ……暇があるなら本の一冊でも";
			mes "読むことをお勧めします。";
			mes "世の中のたいていのことは";
			mes "本から学ぶ事ができます。";
			next;
			mes "[ケイロン=グリック]";
			mes "勿論、本だけであらゆることが";
			mes "わかるわけではない。";
			mes "それでも私達セージは本を";
			mes "知識の宝庫として重宝しています。";
			break;
		}
		close2;
		cutin "job_sage_kayron",255;
		end;
	default:	//3～10のとき
		mes "[ケイロン=グリック]";
		mes "はは、セージになる道は決して";
		mes "易しいものではない。";
		mes "ただ魔法を良く使いこなせるだけでは";
		mes "何にもならないからね。";
		next;
		mes "[ケイロン=グリック]";
		mes "がんばって論文まで仕上げて";
		mes "きなさい。待っていますよ。";
		break;
	case 15:
		if(countitem(1550) < 1) {
			mes "[ケイロン=グリック]";
			mes "うん？論文はどうしました？";
			mes "見せたくば早く持ってきなさい。";
			next;
			mes "[ケイロン=グリック]";
			mes "まさか忘れたわけではないでしょう？";
			mes "とにかく持ってくるのを待ちましょう。";
			break;
		}
		if(SkillPoint) {
			mes "[ケイロン=グリック]";
			mes "君にはまだ割り振れる";
			mes "スキルが残っていますよ。";
			mes "論文を提出する前に";
			mes "取得できるスキルを習得してきなさい。";
			break;
		}
		mes "[ケイロン=グリック]";
		mes "うん、頑張って論文を書いたようだね。";
		mes "それでは見せてもらいましょう。";
		next;
		mes "[ケイロン=グリック]";
		mes "うん……";
		next;
		mes "[ケイロン=グリック]";
		mes "ふむ……";
		next;
		mes "[ケイロン=グリック]";
		mes "むむ……";
		next;
		mes "[ケイロン=グリック]";
		mes "まだ文体が整っていないが……";
		mes "君の論文からは研究に対する";
		mes "熱心さが見て取れる。";
		mes "よし、良いでしょう。";
		next;
		set CHANGE_SA,0;
		unequip;
		jobchange Job_Sage;
		mes "[ケイロン=グリック]";
		mes "卒業だ！";
		mes "これからはセージとして生きて";
		mes "ゆきなさい。";
		mes "今後も学ぶことへの熱心さを";
		mes "忘れないように。";
		next;
		mes "[ケイロン=グリック]";
		mes "論文は大切に保管しておきなさい。";
		mes "君が書いた唯一の書物なのだから。";
		mes "それが役立つこともあるでしょう。";
		next;
		mes "[ケイロン=グリック]";
		mes "さぁ、君自身が知識の宝庫と";
		mes "なるよう、熱心に学びなさい！";
		break;
	}
	close2;
	cutin "job_sage_kayron",255;
	end;
}

//============================================================
// 試験申請
//------------------------------------------------------------
yuno_in03.gat,154,35,4	script	アカデミー関係者	742,{
	if(Job == Job_Sage) {
		mes "[メテウス=シルプ]";
		mes "いらっしゃいませ。";
		mes "ひさしぶりですね。";
		mes "研究の方は";
		mes "はかどっていますか？";
		next;
		mes "[メテウス=シルプ]";
		mes "一人で本や資料をもとに勉強を";
		mes "するのも良いですが、";
		mes "たまには外でモンスターと直接";
		mes "対峙することも重要です。";
		next;
		mes "[メテウス=シルプ]";
		mes "セージ希望者がいらっしゃったら";
		mes "よく教えてあげてください。";
		mes "他の同僚の方々にも";
		mes "よろしくお伝えください。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[メテウス=シルプ]";
		mes "ようこそ。";
		mes "こちらは";
		mes "シュバイチェル魔法アカデミー";
		mes "です。";
		next;
		mes "[メテウス=シルプ]";
		mes "私どもはセージを育成する機関で、";
		mes "モンスターと魔法に関する研究を";
		mes "行っています。";
		mes "また、いつでも入学を歓迎しています。";
		next;
		mes "[メテウス=シルプ]";
		mes "マジシャンでJobLv 40 以上";
		mes "の方なら入学することができます。";
		mes "決められた過程を経て、";
		mes "セージになることができます。";
		next;
		mes "[メテウス=シルプ]";
		mes "もしセージに関心があれば";
		mes "また訪ねてください。";
		mes "それでは、良い一日を。";
		close;
	}
	if(Job != Job_Magician || Upper == UPPER_HIGH) {
		mes "[メテウス=シルプ]";
		mes "ようこそ。";
		mes "こちらは";
		mes "シュバイチェル魔法アカデミー";
		mes "です。";
		next;
		mes "[メテウス=シルプ]";
		mes "私どもはセージを育成する機関で、";
		mes "モンスターと魔法に関する研究を";
		mes "行っています。";
		next;
		mes "[メテウス=シルプ]";
		mes "マジシャンでJobLv 40 以上";
		mes "の方なら入学することができます。";
		mes "決められた過程を経て、";
		mes "セージになることができます。";
		mes "近くにマジシャンのお知り合いが";
		mes "いたら教えてあげてください。";
		next;
		mes "[メテウス=シルプ]";
		mes "それでは、良い一日を。";
		close;
	}
	switch(CHANGE_SA) {
	case 0:
		mes "[メテウス=シルプ]";
		mes "ようこそ。";
		mes "こちらは";
		mes "シュバイチェル魔法アカデミー";
		mes "です。";
		mes "マジシャンの方ですね。";
		mes "こちらへはどのようなご用で？";
		next;
		switch(select("セージ転職について教えてください","入学の申し込みをしたいです","なんでもないです")) {
		case 1:
			mes "[メテウス=シルプ]";
			mes "セージに転職をご希望ですか。";
			mes "しかし、私どもは転職をさせて";
			mes "あげているわけではありません。";
			next;
			mes "[メテウス=シルプ]";
			mes "当アカデミーに入学して";
			mes "規定の過程を終えた方のみ、";
			mes "正式な研究活動について認定を";
			mes "さしあげているのです。";
			next;
			mes "[メテウス=シルプ]";
			mes "ですから、私どもは転職ではなく";
			mes "卒業と呼んでいます。";
			mes "入学の申し込みと共に入学金を";
			mes "納めていただければ、試験を";
			mes "受けることができます。";
			next;
			mes "[メテウス=シルプ]";
			mes "ただ、特別に";
			mes "^3355FF古い魔法書^000000と^3355FF慧眼^000000";
			mes "を持った方々に限っては";
			mes "入学金を免除してさしあげています。";
			next;
			mes "[メテウス=シルプ]";
			mes "登録が完了ししだい、試験を受ける";
			mes "ことができます。";
			mes "入学試験にパスしたら、テーマに沿って";
			mes "研究をしていただきます。";
			mes "最後に、研究したことの論文を";
			mes "書いていただきます。";
			next;
			mes "[メテウス=シルプ]";
			mes "論文は学長が見ますので、";
			mes "学長の判断で合否が決定されます。";
			mes "合格すればセージとして研究活動に";
			mes "従事することが認められます。";
			next;
			mes "[メテウス=シルプ]";
			mes "ご希望があればいつでも";
			mes "申し込みをお待ちしております。";
			mes "それでは、良い一日を。";
			close;
		case 2:
			break;
		case 3:
			mes "[メテウス=シルプ]";
			mes "そうですか。";
			mes "ゆっくり見物していってください。";
			mes "それでは、良い一日を。";
			close;
		}
		mes "[メテウス=シルプ]";
		mes "入学の申し込みですね。";
		mes "シュバイチェル魔法アカデミーに";
		mes "ようこそ。";
		next;
		mes "[メテウス=シルプ]";
		mes "入学するための基本条件は、";
		mes "JobLv 40 以上、マジシャンとして";
		mes "過ごしてきたことです。";
		mes "そして、学習過程に必要である";
		mes "諸経費も入学金として納めなければ";
		mes "なりません。";
		next;
		mes "[メテウス=シルプ]";
		mes "入学金は 70,000Zenyです。";
		mes "または";
		mes "^3355FF古い魔法書^000000と^3355FF慧眼^000000を";
		mes "提出されれば入学金は免除となります。";
		next;
		mes "[メテウス=シルプ]";
		mes "それでは、すぐに入学の申し込みを";
		mes "されますか？";
		next;
		switch(select("入学の申し込みをします","入学金が高すぎます","後でまた来ます")) {
		case 1:
			if(JobLevel < 40) {
				mes "[メテウス=シルプ]";
				mes "まだJobLvが足りないようです。";
				mes "もう少し勉強をしてから";
				mes "いらしてください。";
				close;
			}
			if(SkillPoint) {
				mes "[メテウス=シルプ]";
				mes "取得できるスキルを習得してから";
				mes "いらしてください。";
				mes "中途半端な心構えでは";
				mes "入学を認めることができません。";
				close;
			}
			mes "[メテウス=シルプ]";
			mes "それでは、入学申込書を作成します。";
			mes "こちらにサインしてください。";
			next;
			menu strcharinfo(0),-;
			mes "[メテウス=シルプ]";
			mes "お名前は……";
			mes strcharinfo(0);
			mes "さんですね。良い名前です。";
			next;
			if(JobLevel >= 50) {
				mes "[メテウス=シルプ]";
				mes "ほう、マジシャンをマスターレベルまで";
				mes "鍛えられましたか！";
				mes "特別に入学金を";
				mes "免除してさしあげましょう！";
				next;
				mes "[メテウス=シルプ]";
				mes "はい、手続きは完了です。";
				mes "それでは入学試験を受けて";
				mes "きてください。";
				set CHANGE_SA,4;
				next;
				mes "[メテウス=シルプ]";
				mes "クレイトス教授のところに行って";
				mes "ください。奥の左側の部屋に";
				mes "いらっしゃいます。";
				close;
			}
			mes "[メテウス=シルプ]";
			mes "では、入学金 70,000 Zenyを";
			mes "納めますか？";
			mes "それとも";
			mes "^3355FF古い魔法書^000000と^3355FF慧眼^000000を";
			mes "提出しますか？";
			next;
			if(select("入学金 70,000 Zenyを払う","古い魔法書と慧眼を提出する")==1) {
				if(Zeny < 70000) {
					mes "[メテウス=シルプ]";
					mes "ん……あ、所持金が足りない";
					mes "ようです。確認してからまた";
					mes "いらしてください。";
					close;
				}
				set Zeny,Zeny-70000;
			}
			else {
				if(countitem(1006) < 1 || countitem(1007) < 1) {
					mes "[メテウス=シルプ]";
					mes "ん……？";
					mes "揃っていないようですよ？";
					mes "どこかに忘れてきてしまったのかも";
					mes "しれませんね。";
					mes "見つけしだいお戻りください。";
					close;
				}
				delitem 1006,1;
				delitem 1007,1;
			}
			mes "[メテウス=シルプ]";
			mes "はい、入学手続きが完了しました。";
			mes "それでは入学試験を受けて";
			mes "きてください。";
			set CHANGE_SA,4;
			next;
			mes "[メテウス=シルプ]";
			mes "クレイトス教授のところに行って";
			mes "ください。奥の左側の部屋に";
			mes "いらっしゃいます。";
			close;
		case 2:
			if(JobLevel < 40) {
				mes "[メテウス=シルプ]";
				mes "入学金以前に、まだJobLvが";
				mes "足りていないようです。";
				mes "もうちょっと勉強をなさってから";
				mes "おこしください。";
				close;
			}
			if(JobLevel >= 50) {
				mes "[メテウス=シルプ]";
				mes "ふむ……しかしながら";
				mes "入学金を納めていただかないと";
				mes "入学を認められません……。";
				mes "高いとお感じになられても、";
				mes "セージとなる過程に必要なお金";
				mes "なのです。";
				next;
				mes "[メテウス=シルプ]";
				mes "ん……？";
				mes "ひょっとしてあなたは……";
				mes "マジシャンをマスターされていますね？";
				mes "これは驚きました。特別に入学金を";
				mes "免除してさしあげましょう！";
				next;
				mes "[メテウス=シルプ]";
				mes "それでは、入学申込書を作成します。";
				mes "こちらにサインしてください。";
				next;
				menu strcharinfo(0),-;
				mes "[メテウス=シルプ]";
				mes "お名前は……";
				mes strcharinfo(0);
				mes "さんですね。良い名前です。";
				next;
				mes "[メテウス=シルプ]";
				mes "はい、入学手続きが完了しました。";
				mes "それでは入学試験を受けて";
				mes "きてください。";
				set CHANGE_SA,4;
				next;
				mes "[メテウス=シルプ]";
				mes "クレイトス教授のところに行って";
				mes "ください。奥の左側の部屋に";
				mes "いらっしゃいます。";
				close;
			}
			if(Zeny > 43210) {
				mes "[メテウス=シルプ]";
				mes "うーん……。";
				mes "入学金を納めなければ入学を";
				mes "認めることはできません。";
				mes "高いとお感じになられても、";
				mes "セージとなる過程に必要なお金";
				mes "なのです。";
				next;
				mes "[メテウス=シルプ]";
				mes "それとも";
				mes "^3355FF古い魔法書^000000と^3355FF慧眼^000000を";
				mes "提出なさいますか？";
				mes "それが難しいのであれば、やはり";
				mes "入学金をご用意してください。";
				next;
				mes "[メテウス=シルプ]";
				mes "それでは、良い一日を。";
				close;
			}
			mes "[メテウス=シルプ]";
			mes "ふむ……お金が足りませんか……";
			mes "規定上 70,000 Zenyを";
			mes "納めていただかなければ";
			mes "ならないのですが……";
			next;
			if(select("他の方法はないでしょうか","後でまた来ます")==1) {
				mes "[メテウス=シルプ]";
				mes "それでは特別に少し譲歩しましょう。";
				mes "入学金を 30,000 Zenyに";
				mes "下げてあげます。が、";
				mes "いくつかの品物を提出してください。";
				next;
				mes "[メテウス=シルプ]";
				mes "次の品物を提出してください。";
				set CHANGE_SA,rand(1,3);
				switch(CHANGE_SA) {
				case 1:
					mes "^3355FF鳥の羽毛^000000 50個";
					mes "^3355FF綿毛^000000 50個";
					mes "^3355FF鉄鉱石^000000 25個";
					break;
				case 2:
					mes "^3355FFクローバー^000000 50個";
					mes "^3355FFやわらかな毛^000000 50個";
					mes "^3355FF墨汁^000000 25個";
					break;
				case 3:
					mes "^3355FF鳥の羽毛^000000 50個";
					mes "^3355FF綿毛^000000 50個";
					mes "^3355FFクローバー^000000 50個";
					mes "^3355FFやわらかな毛^000000 50個";
					break;
				}
				next;
				mes "[メテウス=シルプ]";
				mes "申し上げたものを提出されたら";
				mes "入学金を 30,000 Zenyにします。";
				mes "これなら可能でしょう。";
				mes "頑張って集めてみてください。";
				next;
				mes "[メテウス=シルプ]";
				mes "もちろんその前に";
				mes "70,000 Zenyを用意できたら";
				mes "入学金を納めていただきます。";
				mes "規定は規定ですからね。";
				next;
				mes "[メテウス=シルプ]";
				mes "もしくは";
				mes "^3355FF古い魔法書^000000と^3355FF慧眼^000000を";
				mes "提出なさっても結構です。";
				mes "それでは、良い一日を。";
				close;
			}
			//elseならfall through
		case 3:
			mes "[メテウス=シルプ]";
			mes "はい、あわてず準備を整えて";
			mes "くださいね。";
			mes "それでは、良い一日を。";
			close;
		}
	case 1:
	case 2:
	case 3:
		mes "[メテウス=シルプ]";
		mes "いらっしゃいませ。";
		mes "入学のお申し込みですね？";
		next;
		if(countitem(1006) && countitem(1007)) {	//未調査
			delitem 1006,1;
			delitem 1007,1;
			mes "[メテウス=シルプ]";
			mes "古い魔法書と慧眼を提出して";
			mes "いただきました。";
			mes "入学を認めます。";
			set CHANGE_SA,4;
			break;
		}
		if(Zeny >= 70000) {
			set Zeny,Zeny-70000;
			mes "[メテウス=シルプ]";
			mes "70,000 Zenyを納めて";
			mes "いただきました。";
			mes "入学を認めます。";
			set CHANGE_SA,4;
			break;
		}
		switch(CHANGE_SA) {
		case 1:
			setarray '@need,916,914,1002;
			setarray '@amount,50,50,25;
			break;
		case 2:
			setarray '@need,705,949,1024;
			setarray '@amount,50,50,25;
			break;
		case 3:
			setarray '@need,916,914,705,949;
			setarray '@amount,50,50,50,50;
			break;
		}
		set '@max,getarraysize('@need);
		for(set '@i,0; '@i < '@max; set '@i,'@i+1) {
			if(countitem('@need['@i]) < '@amount['@i]) {
				mes "[メテウス=シルプ]";
				mes "しかしまだ準備が整っていませんね。";
				mes "必要なアイテムをもう一度確認します。";
				next;
				mes "[メテウス=シルプ]";
				mes "次の品物を提出してください。";
				for(set '@j,0; '@j < '@max; set '@j,'@j+1)
					mes "^3355FF" +getitemname('@need['@j])+ "^000000 " +'@amount['@j]+ "個";
				next;
				mes "[メテウス=シルプ]";
				mes "申し上げたものを提出されたら";
				mes "入学金を 30,000 Zenyにします。";
				mes "頑張って集めてみてください。";
				mes "それでは、良い一日を。";
				close;
			}
		}
		if(Zeny < 30000) {
			mes "[メテウス=シルプ]";
			mes "しかしまだ準備が整っていませんね。";
			mes "品物はあるものの入学金が";
			mes "足りません。";
			next;
			mes "[メテウス=シルプ]";
			mes "申し上げたように、";
			mes "品物を提出すれば";
			mes "30,000 Zenyにします。";
			mes "品物は入学金と共に納めてください。";
			close;
		}
		for(set '@i,0; '@i < '@max; set '@i,'@i+1)
			delitem '@need['@i],'@amount['@i];
		set Zeny,Zeny-30000;
		mes "[メテウス=シルプ]";
		mes "申し上げた品物を提出されましたね。";
		mes "30,000 Zenyと共に";
		mes "納めていただきました。";
		mes "入学を認めます。";
		set CHANGE_SA,4;
		next;
		mes "[メテウス=シルプ]";
		mes "それでは、入学申込書を作成します。";
		mes "こちらにサインしてください。";
		next;
		menu strcharinfo(0),-;
		mes "[メテウス=シルプ]";
		mes "お名前は……";
		mes strcharinfo(0);
		mes "さんですね。良い名前です。";
		next;
		mes "[メテウス=シルプ]";
		mes "はい、入学手続きが完了しました。";
		mes "それでは入学試験を受けて";
		mes "きてください。";
		next;
		mes "[メテウス=シルプ]";
		mes "クレイトス教授のところに行って";
		mes "ください。奥の左側の部屋に";
		mes "いらっしゃいます。";
		close;
	case 4:
		mes "[メテウス=シルプ]";
		mes "うん？何をしているのですか？";
		mes "試験が始まります。";
		mes "奥の左側の部屋にいらっしゃる";
		mes "クレイトス教授のところに";
		mes "行ってください。";
		close;
	case 15:
		mes "[メテウス=シルプ]";
		mes "あ、論文ができましたか。";
		mes "そうしたら、ケイロン学長のところに";
		mes "行ってください。";
		next;
		mes "[メテウス=シルプ]";
		mes "努力が良い結果につながると";
		mes "良いですね。";
		mes "それでは、良い一日を。";
		close;
	default:
		mes "[メテウス=シルプ]";
		mes "あ、申し訳ございません。";
		mes "今、少々立て込んでまして……";
		mes "後ほどまたいらしてください。";
		mes "本当に申し訳ございません……";
		close;
	}
	//30Kルートの申込書サイン
	mes "[メテウス=シルプ]";
	mes "それでは、入学申込書を作成します。";
	mes "こちらにサインしてください。";
	next;
	menu strcharinfo(0),-;
	mes "[メテウス=シルプ]";
	mes "お名前は……";
	mes strcharinfo(0);
	mes "さんですね。良い名前です。";
	next;
	mes "[メテウス=シルプ]";
	mes "では、まずクレイトス教授の";
	mes "筆記試験を受けてもらいます。";
	next;
	mes "[メテウス=シルプ]";
	mes "クレイトス教授は";
	mes "アカデミー内の図書室にいます。";
	mes "ここから奥の左上の部屋になるので、";
	mes "そちらまで向かってください。";
	next;
	mes "[メテウス=シルプ]";
	mes "それでは、幸運を祈ります。";
	close;
}

//==========================================
// 一次試験（筆記）
//------------------------------------------
yuno_in03.gat,105,177,5	script	筆記試験教授	754,{
	if(Job == Job_Sage) {
		mes "[クレイトス=ベルモ]";
		mes "うん？卒業した者が何の用かな？";
		mes "またまた入学をご希望かね？";
		next;
		mes "[クレイトス=ベルモ]";
		mes "気持ちはわかるが、私達が卒業を";
		mes "認めたのだから、自身を持ちなさい。";
		mes "学び舎をなつかしむのは良いが";
		mes "いつまでもここでゆっくりしていては";
		mes "いけない。たまには危険な旅も";
		mes "しなさい。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "経験したものは全て記録をとることを";
		mes "忘れないように。";
		mes "役立つ知識は他の人へも教えて";
		mes "あげるように。";
		close;
	}
	if(Job == Job_Wizard) {
		mes "[クレイトス=ベルモ]";
		mes "ん……すっかり魔力に";
		mes "魅入ってしまった者だな。";
		mes "それもまた悪くはないだろう……";
		next;
		mes "[クレイトス=ベルモ]";
		mes "ただこれだけは肝に銘じておくように。";
		mes "人は一人では生きていけない。";
		mes "自分が学んだことは、人に教えてこそ";
		mes "真価を発揮するのだ。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[クレイトス=ベルモ]";
		mes "何の用かね？";
		mes "ここは遊び場ではない。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "外でポリンとでも遊びなさい。";
		mes "ほら、出ていきなさい。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[クレイトス=ベルモ]";
		mes "ん……入学を希望しても、";
		mes "君の今の職業からセージになることは";
		mes "かなわない。";
		mes "君には他の才能がある。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "ここで油を売らず他のところへ";
		mes "行ってみなさい。";
		close;
	}
	switch(CHANGE_SA) {
	case 0:
		mes "[クレイトス=ベルモ]";
		mes "うむ……セージになりたいのだな。";
		mes "そんな表情をしている。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "それには我がアカデミーに入学";
		mes "しなくてはならない。";
		mes "手続きを済ませたらまた来なさい。";
		close;
	case 1:
	case 2:
	case 3:
		close;
	case 4:
		mes "[クレイトス=ベルモ]";
		mes "うむ、シュバイチェルアカデミーへ";
		mes "入学したことを歓迎する。";
		mes "手続きは済ませて来たな？";
		next;
		mes "[クレイトス=ベルモ]";
		mes "ちょっと見よう。名前は……";
		mes strcharinfo(0);
		mes "に間違いないな？";
		mes "よし、それではすぐ試験を始めよう。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "私が出す試験は、この世界の全てに";
		mes "関わるものだ。";
		mes "問題は20問。";
		mes "それぞれ5点の配点で、80点以上";
		mes "取れば合格となる。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "すぐに答えられなければ";
		mes "試験は中止となる。";
		mes "では始める。";
		set CHANGE_SA,5;
		break;
	case 5:
		mes "[クレイトス=ベルモ]";
		mes "それでは再試験を行う。";
		mes "今度はしっかりと勉強してきたかな？";
		next;
		mes "[クレイトス=ベルモ]";
		mes "さて、今回も合格点は同じだ。";
		mes "20問各5点配点で、80点以上で";
		mes "合格となる。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "それでは早速始めよう。";
		mes "すぐに答えなければ";
		mes "試験は中止になるので";
		mes "がんばってくれたまえ。";
		break;
	case 6:
		mes "[クレイトス=ベルモ]";
		mes "ん？また試験を受けたいのか？";
		mes "君は筆記試験には合格している。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "ヘルメス教授のところへ行って";
		mes "実技試験を受けなさい。";
		mes "のんびりしていてはいけないぞ。";
		close;
	default:
		mes "[クレイトス=ベルモ]";
		mes "今、他の入学生の試験を採点して";
		mes "いるから忙しいんだ……";
		mes "すまんが後でまた来てくれ。";
		close;
	case 15:
		mes "[クレイトス=ベルモ]";
		mes "お、頑張って論文を仕上げたな。";
		mes "しかし私は論文の採点はしていない。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "ケイロン学長にお見せしなさい。";
		mes "君の卒業可否は学長が判断";
		mes "される。";
		close;
	}
	//筆記試験ここから
	next;
	switch(rand(3)) {
	case 0:
		mes "1.";
		mes "プロンテラのプレゼント商人が";
		mes "売っていない品物はどれか。";
		next;
		if(select("白い皿","赤い額縁","花たば","ガラス玉")==3)
			set '@point,'@point+5;
		mes "2.";
		mes "スティレットが売っていない街は";
		mes "どこか。";
		next;
		if(select("プロンテラ","モロク","ゲフェン","ルティエ")==1)
			set '@point,'@point+5;
		mes "3.";
		mes "タートルアイランドから一番近い";
		mes "街はどこか。";
		next;
		if(select("アルデバラン","アルベルタ","コモド","イズルード")==2)
			set '@point,'@point+5;
		mes "4.";
		mes "次の中で、一つだけ種族の違うものが";
		mes "いる。どれか。";
		next;
		if(select("レグルロ","ペスト","フリルドラ","ヒトデ")==4)
			set '@point,'@point+5;
		mes "5.";
		mes "次の中で、一つだけ属性の違うものが";
		mes "いる。どれか。";
		next;
		if(select("マンティス","メタルラ","ロッカー","ホルン")==2)
			set '@point,'@point+5;
		mes "6.";
		mes "次の中で、一つだけ大きさの違う";
		mes "ものがいる。どれか。";
		next;
		if(select("レイドリック","レイドリックアーチャー","彷徨う者","ダークフレーム")==1)
			set '@point,'@point+5;
		mes "7.";
		mes "次の中で、アルコールを落とさない";
		mes "モンスターはどれか。";
		next;
		if(select("ホロン","プランクトン","ポイズンスポア","トード")==3)
			set '@point,'@point+5;
		mes "8.";
		mes "次の中で、ナイト転職と関係のない";
		mes "者は誰か。";
		next;
		if(select("ジェームズ=シラキューズ","トーマス=セルバンテス","エイミー=ベアトリス","エドモンド=グロスト")==2)
			set '@point,'@point+5;
		mes "9.";
		mes "次の中で、プロンテラに居ない";
		mes "者は誰か。";
		next;
		if(select("ナミ","アウルディフォン","トーマス","ホルグレン")==2)
			set '@point,'@point+5;
		mes "10.";
		mes "眼鏡をかけたカプラ職員の";
		mes "名前を答えよ。";
		next;
		if(select("ディフォルテー","テーリング","グラリス","Ｗ")==3)
			set '@point,'@point+5;
		mes "11.";
		mes "スキル「サンダーストーム」Lv7";
		mes "使用時の消費SPはいくつか。";
		next;
		if(select("49","59","69","74")==2)
			set '@point,'@point+5;
		mes "12.";
		mes "SPが 50% 残っている場合、";
		mes "スキル「エナジーコート」での";
		mes "ダメージ削減率とSP消費量は";
		mes "いくつか。";
		next;
		if(select("24%削減 SP1.5%消費","24%削減 SP2%消費","18%削減 SP1.5%消費","18%削減 SP2%消費")==4)
			set '@point,'@point+5;
		mes "13.";
		mes "マジシャンの「ボルト系魔法」に";
		mes "無い属性を答えよ。";
		next;
		if(select("水属性","地属性","火属性","風属性")==2)
			set '@point,'@point+5;
		mes "14.";
		mes "シーフのスキル";
		mes "「ダブルアタック」Lv7習得時、";
		mes "発動確率と攻撃力は";
		mes "どうなるか答えよ。";
		next;
		if(select("35% / 120%","35% / 140%","40% / 120%","40% / 140%")==2)
			set '@point,'@point+5;
		mes "15.";
		mes "プリーストのスキル";
		mes "「マグヌスエクソシズム」を習得";
		mes "するための過程に無いものは";
		mes "次のうちどれか。";
		next;
		if(select("ディバインプロテクション","ヒール","ルアフ","アクアベネティクタ")==1)
			set '@point,'@point+5;
		mes "16.";
		mes "「ウサギのヘアバンド」の";
		mes "防御値と追加能力値を答えよ。";
		next;
		if(select("1 / LUK +2","1 / LUK +5","2 / LUK +2","2 / LUK +5")==3)
			set '@point,'@point+5;
		mes "17.";
		mes "アーマーを装備できない職業は";
		mes "次のうちどれか。";
		next;
		if(select("剣士","商人","シーフ","アーチャー")==4)
			set '@point,'@point+5;
		mes "18.";
		mes "全てのHP・SPを回復してくれる";
		mes "アイテムは次のうちどれか。";
		next;
		if(select("ローヤルゼリー","イグドラシルの種","イグドラシルの実","マステラの実")==3)
			set '@point,'@point+5;
		mes "19.";
		mes "ルーンミッドガッツ王国の";
		mes "国王の名前を答えよ。";
		next;
		if(select("トリストン 3世","トリスタン 3世","トライスター 3世","トラスト 3世")==2)
			set '@point,'@point+5;
		mes "20.";
		mes "クルセイダー達が仕える神は？";
		next;
		if(select("オーディン","ロキ","トール","アラガムサレー")==1)
			set '@point,'@point+5;
		break;
	case 1:
		mes "1.";
		mes "モロクの宝石商人が売っている宝石";
		mes "にはないものを次から選べ。";
		next;
		if(select("トパーズ","ガーネット","ダイアモンド","サファイア")==2)
			set '@point,'@point+5;
		mes "2.";
		mes "化け物のエサが売っていない街は";
		mes "どこか。";
		next;
		if(select("プロンテラ","モロク","アルデバラン","アルベルタ")==3)
			set '@point,'@point+5;
		mes "3.";
		mes "迷宮の森から一番近い街は";
		mes "どこか。";
		next;
		if(select("プロンテラ","モロク","ゲフェン","フェイヨン")==1)
			set '@point,'@point+5;
		mes "4.";
		mes "次の中で、一つだけ種族の違うものが";
		mes "いる。どれか。";
		next;
		if(select("ムカー","ドロップス","プランクトン","ペノメナ")==4)
			set '@point,'@point+5;
		mes "5.";
		mes "次の中で、一つだけ属性の違うものが";
		mes "いる。どれか。";
		next;
		if(select("ドケビ","イシス","ガイアス","デビルチ")==3)
			set '@point,'@point+5;
		mes "6.";
		mes "次の中で、一つだけ大きさの";
		mes "違うものがいる。どれか。";
		next;
		if(select("雄盗蟲","ホルン","メタルラ","アルゴス")==4)
			set '@point,'@point+5;
		mes "7.";
		mes "次の中で、「イグドラシルの葉」";
		mes "を落とさないモンスターはどれか。";
		next;
		if(select("マルドゥーク","バフォメット.Jr","エンジェリング","彷徨う者")==1)
			set '@point,'@point+5;
		mes "8.";
		mes "プリースト転職と関係の無い人は";
		mes "次のうち誰か。";
		next;
		if(select("トーマス=セルバンテス","ウインザー=ベネディクト","ピーター S. アルベルト","セシル=マルガリータ")==2)
			set '@point,'@point+5;
		mes "9.";
		mes "モロクにはいない者は";
		mes "次のうち誰か。";
		next;
		if(select("アブドゥル","アラガム","アントニオ","サド")==3)
			set '@point,'@point+5;
		mes "10.";
		mes "青い髪が魅力的な";
		mes "カプラ職員の名前は？";
		next;
		if(select("ディフォルテー","テーリング","グラリス","Ｗ")==1)
			set '@point,'@point+5;
		mes "11.";
		mes "スキル「ファイアーウォール」を";
		mes "修得する過程で必要の無いものを";
		mes "次の中から選べ。";
		next;
		if(select("ファイアーボルト Lv 4","ナパームビート Lv 4","ファイアーボール Lv 5","サイト Lv 1")==2)
			set '@point,'@point+5;
		mes "12.";
		mes "スキル「SP回復力向上」を";
		mes "Lv6まで習得した場合、純粋な";
		mes "スキル効果によって10秒間で";
		mes "回復するSP値はいくつか。";
		next;
		if(select("14","16","18","21")==3)
			set '@point,'@point+5;
		mes "13.";
		mes "マジシャンがJobLv33で";
		mes "得られるINT加重値はいくつか。";
		next;
		if(select("7","6","5","4")==4)
			set '@point,'@point+5;
		mes "14.";
		mes "アーチャーのスキル「集中力向上」";
		mes "Lv5のSP消費量と持続時間は";
		mes "いくつか。";
		next;
		if(select("45 / 140秒","50 / 140秒","45 / 150秒","50 / 150秒")==1)
			set '@point,'@point+5;
		mes "15.";
		mes "ブラックスミスのスキル";
		mes "「マキシマイズパワー」を習得する";
		mes "過程に必要の無いものはどれか。";
		next;
		if(select("ヒルトバインディング","スキンテンパリング","ハンマーフォール","ウェポンパーフェクション")==2)
			set '@point,'@point+5;
		mes "16.";
		mes "リボンのヘアバンドの";
		mes "防御力と追加能力を答えよ。";
		next;
		if(select("0 / SP +20","0 / SP +30","1 / SP +20","1 / SP +30")==3)
			set '@point,'@point+5;
		mes "17.";
		mes "セイントローブを装備することが";
		mes "できない職業は次のうちどれか。";
		next;
		if(select("剣士","商人","シーフ","アコライト")==3)	//現在は剣士も装備不可能
			set '@point,'@point+5;
		mes "18.";
		mes "「緑ポーション」で回復することが";
		mes "できない状態異常は次のうちどれか。";
		next;
		if(select("沈黙","毒","暗黒","呪い")==4)
			set '@point,'@point+5;
		mes "19.";
		mes "ゲフェンのどこかから入れるという";
		mes "消えた古代王国の名前を答えよ。";
		next;
		if(select("ゲフェイヨン","ゲフェニア","ゲフェドリア","ゲフェリア")==2)
			set '@point,'@point+5;
		mes "20.";
		mes "世界の根源と言われる木の名前を";
		mes "答えよ。";
		next;
		if(select("イグドラシル","イドグラシル","マステラ","古木の枝")==1)
			set '@point,'@point+5;
		break;
	case 2:
		mes "1.";
		mes "次の中で、ゲフェンの魔法商人が";
		mes "売っていないものを答えよ。";
		next;
		if(select("メントル","ワンド","サークレット","シルバーローブ")==1)
			set '@point,'@point+5;
		mes "2.";
		mes "次の中で、「ブレイド」が売っていない";
		mes "街を選べ。";
		next;
		if(select("プロンテラ","イズルード","アルデバラン","フェイヨン")==3)
			set '@point,'@point+5;
		mes "3.";
		mes "グラストヘイムから一番近くに";
		mes "位置する街はどれか。";
		next;
		if(select("プロンテラ","ゲフェン","モロク","フェイヨン")==2)
			set '@point,'@point+5;
		mes "4.";
		mes "次の中で、一つだけ種族の違うものが";
		mes "いる。どれか。";
		next;
		if(select("ヒトデ","マルク","マルス","マーリン")==4)
			set '@point,'@point+5;
		mes "5.";
		mes "次の中で、一つだけ属性の違うものが";
		mes "いる。どれか。";
		next;
		if(select("子デザートウルフ","スモーキー","ピッキ","チョコ")==2)
			set '@point,'@point+5;
		mes "6.";
		mes "次の中で、一つだけ大きさの";
		mes "違うものがいる。どれか。";
		next;
		if(select("ドレイク","レイス","イビルドルイド","カーリッツバーグ")==1)
			set '@point,'@point+5;
		mes "7.";
		mes "次の中で、「プラコン」を";
		mes "落とさないモンスターはどれか。";
		next;
		if(select("プパ","コンドル","サベージベベ","子デザートウルフ")==2)
			set '@point,'@point+5;
		mes "8.";
		mes "次の中で、ブラックスミス転職と";
		mes "関係の無い者は誰か。";
		next;
		if(select("バイス","ヒュッケ","バルカデー","ミットマイヤ")==3)
			set '@point,'@point+5;
		mes "9.";
		mes "次の中で、アルデバランに";
		mes "居ない者は誰か。";
		next;
		if(select("RS125","マーセル","マンスタ","アイゼンバーグ")==2)
			set '@point,'@point+5;
		mes "10.";
		mes "カプラ職員の中で、一番年下の";
		mes "者の名前を答えよ。";
		next;
		if(select("ディフォルテー","テーリング","グラリス","Ｗ")==4)
			set '@point,'@point+5;
		mes "11.";
		mes "スキル「セイフティウォール」";
		mes "Lv6使用時の、消費SPと回避数を";
		mes "答えよ。";
		next;
		if(select("SP 40, 6回","SP 35, 6回","SP 35, 7回","SP 40, 7回")==4)
			set '@point,'@point+5;
		mes "12.";
		mes "スキル「ナパームビート」Lv6";
		mes "使用時、攻撃力はMATKの何倍か。";
		next;
		if(select("1.2倍","1.3倍","1.4倍","1.5倍")==2)
			set '@point,'@point+5;
		mes "13.";
		mes "マジシャン転職試験で、";
		mes "混合液4の触媒になる鉱石はどれか。";
		next;
		if(select("ブルージェムストーン","レッドジェムストーン","イエロージェムストーン","透明宝玉")==4)
			set '@point,'@point+5;
		mes "14.";
		mes "剣士のスキル「バッシュLv6」";
		mes "の攻撃力とSP消費量を答えよ。";
		next;
		if(select("250% / 8","280% / 8","280% / 15","310% / 15")==3)
			set '@point,'@point+5;
		mes "15.";
		mes "ハンターのスキル";
		mes "「クレイモアトラップ」を";
		mes "習得する過程で必要のないものは";
		mes "次のうちどれか。";
		next;
		if(select("リムーブトラップ","ランドマイン","アンクルスネア","フラッシャー")==1)
			set '@point,'@point+5;
		mes "16.";
		mes "「ヴェール」の防御力と";
		mes "追加能力値を答えよ。";
		next;
		if(select("0 / MDEF +3","0 / MDEF +5","1 / MDEF +3","1 / MDEF +5")==2)
			set '@point,'@point+5;
		mes "17.";
		mes "「ロングコート」を装備することが";
		mes "できない職業は次のうちどれか。";
		next;
		if(select("剣士","商人","シーフ","ノービス")==4)
			set '@point,'@point+5;
		mes "18.";
		mes "青色の染料の材料でないアイテムは";
		mes "次のうちどれか。";
		next;
		if(select("アルコール","ディトリミン","カルボーディル","青ハーブ")==3)
			set '@point,'@point+5;
		mes "19.";
		mes "世界が創造されるとき、神オーディンが";
		mes "使ったといわれるアイテムは";
		mes "次のうちどれか。";
		next;
		if(select("ユミルの心臓","ユミルの爪","ユミルの歯","ユミルの遺品")==2)
			set '@point,'@point+5;
		mes "20.";
		mes "この世界の運命を変えられる";
		mes "者の前に出て、運命を共にする";
		mes "という金属は次のうちどれか。";
		next;
		if(select("エンベルタコン","エンペリウム","エンペラ","プラコン")==2)
			set '@point,'@point+5;
		break;
	}
	mes "[クレイトス=ベルモ]";
	mes "よし、そこまで。";
	mes "では採点しようか。";
	next;
	mes "[クレイトス=ベルモ]";
	mes "どれ……";
	mes "うん……";
	next;
	mes "[クレイトス=ベルモ]";
	mes "採点が終わった。";
	mes "君の点数は " +'@point+ "点だ。";
	if('@point < 80) {
		mes "……";
		mes "残念だが不合格だ。";
		next;
		mes "[クレイトス=ベルモ]";
		mes "また試験を受けさせてあげるから";
		mes "もう少し世界について勉強して";
		mes "きなさい。";
		close;
	}
	else if('@point == 100) {
		mes "さすがに驚いたな。";
		mes "ここまでできるなら、";
		mes "セージになる素質は十分だ。";
	}
	else {
		mes "ふむ。";
		mes "これだけできれば良いな。";
	}
	set CHANGE_SA,6;
	next;
	mes "[クレイトス=ベルモ]";
	mes "よし、筆記試験は通過だ。";
	mes "ヘルメス教授のところへ行き、";
	mes "実技試験も受けてきなさい。";
	close;
}

//==========================================
// 二次試験（実技）
//------------------------------------------
yuno_in03.gat,169,180,3	script	実技試験教授	755,{
	if(Job == Job_Sage) {
		mes "[ヘルメス=トリス]";
		mes "やぁ、元気かい？";
		mes "顔を見たところ、それなりに";
		mes "苦労を重ねたようじゃないか。";
		next;
		mes "[ヘルメス=トリス]";
		mes "やはり、経験を重ねることは大事だね。";
		mes "知識で知っているだけと、自分の体";
		mes "で体験するのとでは大きな違いが";
		mes "生まれるからね。";
		next;
		mes "[ヘルメス=トリス]";
		mes "でも、危険なダンジョンなんかは";
		mes "頼れる仲間と一緒に行ってみると";
		mes "いい。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[ヘルメス=トリス]";
		mes "はは、かわいいノービス";
		mes "じゃないか。";
		next;
		mes "[ヘルメス=トリス]";
		mes "ミッドガルド大陸には、まだ私達すら";
		mes "知らないものがたくさんある。";
		mes "アイテムの数々、英雄と伝説……";
		next;
		mes "[ヘルメス=トリス]";
		mes "君もセージを目指して夢を";
		mes "膨らませてみないかい？";
		mes "ま、もうちょっと世界について";
		mes "勉強してからだがね。";
		next;
		mes "[ヘルメス=トリス]";
		mes "もし縁があればまた会うことも";
		mes "あるだろう。";
		mes "それでは気をつけて帰ってくれ。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[ヘルメス=トリス]";
		mes "ここは";
		mes "シュバイチェル魔法アカデミーだ。";
		next;
		mes "[ヘルメス=トリス]";
		mes "私たちセージは魔術師と言うよりは";
		mes "学者に近い存在だろうな。";
		mes "パーティーでも何かと役に立つと";
		mes "思うよ。";
		next;
		mes "[ヘルメス=トリス]";
		mes "試しに次の旅にはぜひセージを";
		mes "連れて行きなさい。";
		mes "立派に自分の役目を果たしてくれる";
		mes "だろう。";
		close;
	}
	switch(CHANGE_SA) {
	case 0:
	case 1:
	case 2:
	case 3:
		mes "[ヘルメス=トリス]";
		mes "私は実技試験を担当する";
		mes "ヘルメスという。";
		mes "セージ志望の学生か？";
		next;
		mes "[ヘルメス=トリス]";
		mes "まず、入学手続きを終わらせて";
		mes "筆記試験を受けてきなさい。";
		close;
	case 4:
	case 5:
		mes "[ヘルメス=トリス]";
		mes "私は実技試験を担当する";
		mes "ヘルメスという。";
		mes "セージ志望の学生か？";
		next;
		mes "[ヘルメス=トリス]";
		mes "クレイトス教授の筆記試験を";
		mes "パスして来るように。";
		mes "その後私の試験を受けてもらう。";
		close;
	case 6:
		mes "[ヘルメス=トリス]";
		mes "お、筆記試験をパスした学生かな？";
		mes "それならこれから実技試験を受けて";
		mes "もらう。";
		next;
		mes "[ヘルメス=トリス]";
		mes "実技試験は……なに、ルールは単純だ。";
		mes "現れたモンスターを、時間制限以内に";
		mes "全て倒せば良い。";
		next;
		mes "[ヘルメス=トリス]";
		mes "百回聞くより一回体験してみたほうが";
		mes "早い。ことわざにもあるだろう？";
		mes "さぁ、今すぐ試験を受けるかな？";
		next;
		if(select("実技試験を受けます","準備させてください")==2) {
			set CHANGE_SA,7;
			mes "[ヘルメス=トリス]";
			mes "うん、いいよ。";
			mes "しっかり準備をしてきなさい。";
			close;
		}
		set CHANGE_SA,7;
		mes "[ヘルメス=トリス]";
		mes "よし、ではすぐ始めよう。";
		mes "頑張ってくれたまえ。";
		close2;
		warp "job_sage.gat",50,154;
		end;
	case 7:
		mes "[ヘルメス=トリス]";
		mes "やぁ、今度はしっかり準備して";
		mes "きたかな？";
		mes "実技試験はそこまで難しいものでは";
		mes "ないから頑張ってほしい。";
		next;
		mes "[ヘルメス=トリス]";
		mes "さぁ、試験を受けるかな？";
		next;
		if(select("実技試験を受けます","準備する時間をください")==2) {
			mes "[ヘルメス=トリス]";
			mes "うん、いいよ。";
			mes "しっかり準備をしてきなさい。";
			close;
		}
		mes "[ヘルメス=トリス]";
		mes "よし、ではすぐ始めよう。";
		mes "頑張ってくれたまえ。";
		close2;
		warp "job_sage.gat",50,154;
		end;
	case 8:
		mes "[ヘルメス=トリス]";
		mes "よし、頑張った。";
		mes "実技試験もパスだ。";
		mes "君の入学を歓迎しよう。";
		next;
		mes "[ヘルメス=トリス]";
		mes "それでは、君に研究してもらう";
		mes "分野を決めようか……";
		mes "ちょっと待ってくれ。";
		mes "筆記試験の点数と戦闘試験で";
		mes "費やした時間を見ようか。";
		next;
		mes "[ヘルメス=トリス]";
		mes "ふむ……";
		mes "よし、これなら大丈夫だろう。";
		next;
		switch(rand(3)) {
		case 0:
			set CHANGE_SA,9;
			mes "[ヘルメス=トリス]";
			mes "君にはイグドラシルに関する研究を";
			mes "してもらう。";
			mes "私たちが住むこの世界の根源になった";
			mes "木に関する研究だ。";
			next;
			mes "[ヘルメス=トリス]";
			mes "今のこの大陸の変化や発展を";
			mes "見極めるために重要な分野だ。";
			mes "アカデミー講義室に居る";
			mes "シピエン=ライルリース教授の話を";
			mes "聞きなさい。";
			break;
		case 1:
			set CHANGE_SA,11;
			mes "[ヘルメス=トリス]";
			mes "君にはモンスターに関する研究を";
			mes "してもらう。";
			mes "大陸のあちらこちらにいる";
			mes "モンスターの研究だ。";
			next;
			mes "[ヘルメス=トリス]";
			mes "これから生きていくために";
			mes "必要になる知識を得る事が";
			mes "できるだろう。";
			mes "モンスター博物館に居る";
			mes "ルシウス=ケルソス教授の話を";
			mes "聞きなさい。";
			break;
		case 2:
			set CHANGE_SA,13;
			mes "[ヘルメス=トリス]";
			mes "君には属性魔法に関する研究を";
			mes "してもらう。";
			mes "私達が使う基本的な魔法について";
			mes "理解を深めてもらう。";
			next;
			mes "[ヘルメス=トリス]";
			mes "魔法というものの本質がわかる";
			mes "良い分野だ。";
			mes "バイオテクノロジー研究所に居る";
			mes "エベシ=ジョルダ教授の話を";
			mes "聞きなさい。";
			break;
		}
		next;
		mes "[ヘルメス=トリス]";
		mes "それでは良い結果が出るよう";
		mes "健闘を祈る。";
		close;
	case 9:
		mes "[ヘルメス=トリス]";
		mes "うん？良く聞いていなかったのか？";
		mes "イグドラシルに関する研究を";
		mes "してもらうと言ったはずだ。";
		next;
		mes "[ヘルメス=トリス]";
		mes "アカデミー講義室に居る";
		mes "シピエン=ライルリース教授の";
		mes "ところへ行きなさい。";
		close;
	case 11:
		mes "[ヘルメス=トリス]";
		mes "うん？良く聞いていなかったのか？";
		mes "モンスターに関する研究を";
		mes "してもらうと言ったはずだ。";
		next;
		mes "[ヘルメス=トリス]";
		mes "モンスター博物館に居る";
		mes "ルシウス=ケルソス教授の";
		mes "ところへ行きなさい。";
		close;
	case 13:
		mes "[ヘルメス=トリス]";
		mes "うん？良く聞いていなかったのか？";
		mes "属性魔法に関する研究を";
		mes "してもらうと言ったはずだ。";
		next;
		mes "[ヘルメス=トリス]";
		mes "バイオテクノロジー研究所に居る";
		mes "エベシ=ジョルダ教授の";
		mes "ところへ行きなさい。";
		close;
	case 15:
		mes "[ヘルメス=トリス]";
		mes "ここで何を油売っている？";
		mes "論文が出来たなら早く学長に";
		mes "お見せしなさい。";
		mes "私に見せてくれるのは良いが";
		mes "卒業は学長が判断するからね。";
		next;
		mes "[ヘルメス=トリス]";
		mes "ほらほら、早く行きなさい。";
		close;
	default:
		mes "[ヘルメス=トリス]";
		mes "んー……";
		mes "あ、ごめんよ、今ちょっと";
		mes "忙しいんだ。";
		mes "分からないことがあったら";
		mes "君の担当教授に聞いてみなさい。";
		close;
	}
}

job_sage.gat,50,165,4	script	実技試験担当#sage	700,{
	mes "[実技試験担当]";
	mes "セージ実技試験へようこそ。";
	mes "試験を受けたければ";
	mes "試験待機室へ入室してください。";
	next;
	mes "[実技試験担当]";
	mes "他の方が試験中の場合は";
	mes "しばらくお待ちください。";
	mes "進行状況がアナウンスされますので";
	mes "終わったらお呼びします。";
	next;
	mes "[実技試験担当]";
	mes "一人あたりの試験時間は";
	mes "5～10分となります。";
	mes "戦闘場から出たい場合は";
	mes "一度接続し直してください。";
	close;
OnInit:
	waitingroom "試験待機室",20,"実技試験担当#sage::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	hideonnpc "SageTestFail";
	warpwaitingpc "job_sage.gat",116,97;
	donpcevent "SageTest::OnStart1";
	end;
}

job_sage.gat,0,0,0	script	SageTest	-1,{
	end;
OnStart1:
	set 'count,16;
	set 'flag,1;	//1回目フラグ
	monster "job_sage.gat",111,102,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,93,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,98,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,98,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",115,106,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",115,90,"単位",1183,1,"SageTest::OnKilled";
	monster "job_sage.gat",103,110,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",128,110,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",103,85,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",128,85,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,106,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,106,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,89,"単位",1184,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,89,"単位",1184,1,"SageTest::OnKilled";
	initnpctimer;
	end;
OnStart2:
	set 'count,24;
	set 'flag,2;	//2回目フラグ
	monster "job_sage.gat",111,102,"数学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,102,"物理学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,102,"史学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"地理学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"天文学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"気象学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"建築学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"制御学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"計測学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"統計学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"都市学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,102,"言語学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"食品学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"栄養学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",111,93,"造形学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,93,"人類学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,93,"生物学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",120,93,"倫理学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,98,"経済学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,98,"政治学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",107,98,"魔法学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,98,"山林学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,98,"保健学",1063,1,"SageTest::OnKilled";
	monster "job_sage.gat",124,98,"心理学",1063,1,"SageTest::OnKilled";
	setnpctimer 1001;
	end;
OnStart3:
	set 'flag,3;	//3回目フラグ
	monster "job_sage.gat",116,97,"学士称号",1179,1,"SageTest::OnPass";
	monster "job_sage.gat",107,106,"欠席",1185,1;
	monster "job_sage.gat",124,106,"遅刻",1185,1;
	monster "job_sage.gat",107,89,"カンニング",1185,1;
	monster "job_sage.gat",124,89,"貸し出し",1185,1;
	setnpctimer 123001;
	end;
OnKilled:
	set 'count,'count-1;
	if('count < 1) {
		announce "試験場: " +strcharinfo(0)+ "様、モンスター撃退成功",9;
		if('flag == 1)
			donpcevent "SageTest::OnStart2";
		else if('flag == 2)
			donpcevent "SageTest::OnStart3";
	}
	end;
OnPass:
	stopnpctimer;
	killmonster "job_sage.gat","All";
	set CHANGE_SA,8;
	announce "試験場: おめでとうございます、" +strcharinfo(0)+ "様 実技試験に合格しました",9;
	sleep 2000;
	announce "試験官: それでは残りの過程も頑張ってください",9;
	sleep 2000;
	announce "試験官: これで試験終了です。次の受験者、準備してください",9;
	sleep 1000;
	areawarp "job_sage.gat",100,82,131,113,"yuno_in03.gat",163,180;
	hideoffnpc "SageTestFail";
	sleep 2000;
	announce "試験官: 次の受験者、入場してください",9;
	sleep 2000;
	enablewaitingroomevent "実技試験担当#sage";
	end;
OnTimer1000:
	if('flag == 1)
		announce "試験場: 入学実技試験を始めます。",9;
	end;
OnTimer2000:
	announce "試験場: " +(('flag==1)? "一": "二")+ "番目の試験 - 時間制限 3分",9;
	end;
OnTimer3000:
	announce "試験場: 時間以内にすべてのモンスターを撃退してください。",9;
	end;
OnTimer33000:
	announce "試験場: 残り2分 30秒",9;
	end;
OnTimer63000:
	announce "試験場: 残り2分",9;
	end;
OnTimer93000:
	announce "試験場: 残り1分 30秒",9;
	end;
OnTimer123000:
	announce "試験場: 残り1分",9;
	end;
OnTimer124000:
	if('flag == 3)
		announce "試験場: 三番目の試験 - 時間制限 1分",9;
	end;
OnTimer153000:
	announce "試験場: 残り30秒",9;
	end;
OnTimer173000:
	announce "試験場: 残り10秒",9;
	end;
OnTimer183000:
	killmonster "job_sage.gat","All";
	announce "試験場: 制限時間終了",9;
	end;
OnTimer184000:
	hideoffnpc "SageTestFail";
	end;
OnTimer185000:
	announce "次の受験者、入場してください",9;
	end;
OnTimer186000:
	stopnpctimer;
	set 'flag,0;
	enablewaitingroomevent "実技試験担当#sage";
	end;
}

job_sage.gat,116,97,0	script	SageTestFail	139,16,16,{
OnTouch:
	announce "試験場: " +strcharinfo(0)+ "様が試験に失敗しました",9;
	warp "yuno.gat",324,258;
	end;
}

//==========================================
// 三次試験（イグドラシル研究）
//------------------------------------------
yuno_in03.gat,62,176,2	script	史学教授	109,{
	if(Job == Job_Sage) {
		mes "[シピエン=ライルリース]";
		mes "誰かな……？";
		mes "ああ、私が教えた学生ですね。";
		mes "たしかアカデミーを卒業していたね。";
		next;
		mes "[シピエン=ライルリース]";
		mes "過去を知れば現在を理解し、";
		mes "未来を想像することが出来る。";
		mes "そこに全ての真理がある。";
		next;
		mes "[シピエン=ライルリース]";
		mes "今の君も過去を知ろうとしている。";
		mes "いつか「今」を回想し、懐かしみ、";
		mes "変わった自分を発見する時が";
		mes "来るでしょう。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[シピエン=ライルリース]";
		mes "ノービスさんが何の用かな？";
		next;
		mes "[シピエン=ライルリース]";
		mes "幾多の可能性を秘めた君は";
		mes "これからどんな道を歩んで";
		mes "行くのかな？";
		next;
		mes "[シピエン=ライルリース]";
		mes "それは君自身が決めることです。";
		mes "間違った道を進まないように。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[シピエン=ライルリース]";
		mes "はい、私は史学を教えています。";
		next;
		mes "[シピエン=ライルリース]";
		mes "今の世界は、幾多の記憶と歳月を";
		mes "もとに形作られたものなのです。";
		mes "過去を知ることは現在と未来を";
		mes "つなげる橋となるでしょう。";
		next;
		mes "[シピエン=ライルリース]";
		mes "君も、自分の過去を振り返って";
		mes "みなさい。きっと未来への道が";
		mes "見えてくるはずです。";
		close;
	}
	switch(CHANGE_SA) {
	case 9:
		switch(RESEARCH_SA) {
		case 0:
			mes "[シピエン=ライルリース]";
			mes "はい、" +strcharinfo(0)+ "君だね。";
			mes "よく来ました。私は講義担当の";
			mes "シピエン=ライルリースといいます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "ここでのテーマは、イグドラシル";
			mes "に関する研究です。";
			mes "イグドラシルというものがどういう";
			mes "ものか、君は知っているかな？";
			next;
			if(select("はい、知っています","いいえ、よく知りません……")==1) {
				mes "[シピエン=ライルリース]";
				mes "それではイグドラシルについて";
				mes "知っていることを話してみなさい。";
				next;
				switch(select("回復アイテムの名前です","世界の根源と言われる木です","実はよく知りません……")) {
				case 1:
					mes "[シピエン=ライルリース]";
					mes "違います。";
					mes strcharinfo(0)+ "君、";
					mes "減点10点です。";
					mes "それはその木から出た成分を";
					mes "利用して使っているだけの話です。";
					next;
					mes "[シピエン=ライルリース]";
					mes "イグドラシルというのは、";
					mes "世界の根源となった木の";
					mes "名前です。";
					break;
				case 2:
					mes "[シピエン=ライルリース]";
					mes "そうですね、イグドラシルは";
					mes "私たちが住むこの世界の";
					mes "根源となった木の名前です。";
					break;
				case 3:
					mes "[シピエン=ライルリース]";
					mes "知らないならば知らないと言いなさい。";
					mes strcharinfo(0)+ "君、";
					mes "減点10点です。";
					next;
					mes "[シピエン=ライルリース]";
					mes "イグドラシルというのは、";
					mes "世界の根源となった木の";
					mes "名前です。";
					break;
				}
			}
			else {
				mes "[シピエン=ライルリース]";
				mes "うん、少しは聞いたことがあるかも";
				mes "しれませんが、イグドラシルという";
				mes "のは、ミッドガルド大陸の根源にも";
				mes "なった木の名前です。";
			}
			next;
			mes "[シピエン=ライルリース]";
			mes "それでは講義に先立って";
			mes "いくつか準備してもらいたいものが";
			mes "あります。";
			mes "イグドラシルを理解するためには";
			mes "必要なことです。";
			next;
			mes "[シピエン=ライルリース]";
			mes "何でも良いから、イグドラシルに";
			mes "関わる物を集めてきなさい。";
			mes "種や実が一番望ましいですね。";
			mes "大変ですが頑張って見つけて";
			mes "きてください。";
			next;
			mes "[シピエン=ライルリース]";
			mes "それでは、準備が出来次第";
			mes "講義に入ります。";
			mes "いってらっしゃい。";
			set RESEARCH_SA,1;
			close;
		case 1:
			if(countitem(607) < 1 && countitem(608) < 1 && countitem(610) < 1) {
				mes "[シピエン=ライルリース]";
				mes "ん？まだ講義を受ける準備が";
				mes "できていないようですよ？";
				mes "何でも良いから、イグドラシルに";
				mes "関わる物を集めてきなさい。";
				next;
				mes "[シピエン=ライルリース]";
				mes "準備ができたら始めます。";
				mes "さぁ、行ってきなさい。";
				close;
			}
			mes "[シピエン=ライルリース]";
			mes "うむ、準備をしてきたかな？";
			if(countitem(607)) {
				mes "……！";
				mes "イグドラシルの実を持ってきましたか！";
				mes "感心感心。";
			}
			else if(countitem(608)) {
				mes "……";
				mes "ほぉ、イグドラシルの種ですか。";
				mes "苦労したでしょう。";
			}
			else if(countitem(610)) {
				mes "……";
				mes "イグドラシルの葉ですか。";
				next;
				mes "[シピエン=ライルリース]";
				mes "これは街によっては売っているね。";
				mes "横着はいけません。";
				mes strcharinfo(0)+ "君、減点10点です。";
			}
			next;
			mes "[シピエン=ライルリース]";
			mes "それでは講義を始めます。";
			mes "居眠りなどせずに聞きなさい。";
			next;
			mes "[シピエン=ライルリース]";
			mes "世界の根源である";
			mes "イグドラシルの木は";
			mes "全大陸に根付き、その高さは";
			mes "空にまで達すると言われています。";
			next;
			mes "[シピエン=ライルリース]";
			mes "大陸の外には大洋があり、";
			mes "世界を巨大な蛇である";
			mes "ヨルムンガンドが囲んでいます。";
			mes "大陸はアスガルド・ミッドガルド・";
			mes "ウトガルドに分けられます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "巨人族が住むウトガルド……";
			next;
			mes "[シピエン=ライルリース]";
			mes "私達人間が住むミッドガルド……";
			next;
			mes "[シピエン=ライルリース]";
			mes "そして神々が住むアスガルド……";
			mes "この大陸の中心にそびえたつ";
			mes "巨樹がイグドラシルなのです。";
			next;
			mes "[シピエン=ライルリース]";
			mes "太古にユミルの死をもって生まれた";
			mes "この大陸に深く根をはり、巨樹を";
			mes "支えるその根は三つのところに";
			mes "伸びています。";
			next;
			mes "[シピエン=ライルリース]";
			mes "一つ目の根は、神々が住む";
			mes "アスガルドへ。";
			mes "未だ我ら人間の見知らぬ";
			mes "地へと……";
			next;
			mes "[シピエン=ライルリース]";
			mes "二つ目は巨人達が住む";
			mes "ヨトゥンヘイムだと言われています。";
			mes "伝説や神話の節々でその名を";
			mes "聞くことがあります。";
			next;
			mes "[シピエン=ライルリース]";
			mes "三つ目はニブルヘイムに";
			mes "伸びています。";
			mes "大地は深い霧と闇と氷に";
			mes "覆われています。";
			next;
			mes "[シピエン=ライルリース]";
			mes "私達が偶然手に入れた";
			mes "イグドラシルの実・種・葉";
			mes "のような物は、まさにその巨樹の";
			mes "産物であると考えられます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "幻想的で太古の歴史を感じられる";
			mes "生命力あふれるイグドラシルの実は";
			mes "HPとSPを完全に回復してくれます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "香ばしくて苦味のある香に";
			mes "元気が湧くというイグドラシルの種は";
			mes "HPとSPを半分程回復してくれます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "強い生命力を持っている";
			mes "イグドラシルの葉は死者を";
			mes "蘇生させることができます。";
			next;
			mes "[シピエン=ライルリース]";
			mes "最後に……もし君が遠い未来に";
			mes "アスガルドへ行く方法を見つけたら、";
			mes "必ずイグドラシルを探してみなさい。";
			next;
			mes "[シピエン=ライルリース]";
			mes "もちろん、神話と伝説に基づいた";
			mes "話だが、だからこそ、イグドラシルの";
			mes "存在を究明しなければならないのです。";
			next;
			mes "[シピエン=ライルリース]";
			mes "では、講義はここまでにしましょう。";
			mes "聞いた内容をよく整理して覚えて";
			mes "おくんですよ。";
			next;
			mes "[シピエン=ライルリース]";
			mes "次は論文を書いてもらいます。";
			mes "論文を書く準備をしてきてください。";
			next;
			mes "[シピエン=ライルリース]";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[シピエン=ライルリース]";
			mes "準備ができしだい論文制作に";
			mes "入ってもらいます。";
			set RESEARCH_SA,0;
			set CHANGE_SA,10;
			close;
		}
	case 10:
		if(countitem(916) < 1 || countitem(919) < 1 || countitem(1019) < 1 || countitem(1024) < 1 || countitem(713) < 1) {
			mes "[シピエン=ライルリース]";
			mes "まだ論文を書く準備ができて";
			mes "いないようですよ。";
			mes "準備してきなさいと言ったはずです。";
			next;
			mes "[シピエン=ライルリース]";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[シピエン=ライルリース]";
			mes "準備ができしだい論文制作を";
			mes "手伝ってあげましょう。";
			mes "では、いってらっしゃい。";
			close;
		}
		delitem 916,1;
		delitem 919,1;
		delitem 1019,1;
		delitem 1024,1;
		delitem 713,1;
		mes "[シピエン=ライルリース]";
		mes "では、論文を書き始めなさい。";
		mes "横で見ててあげます。";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "大陸の外には大洋があり、";
		mes "その広い大洋を包んでいるのは";
		setarray '@word$,"巨大な水瓶だという","巨大な蛇ヨルムンガンドだという","巨大な亀と象たちだという","巨大なお皿だという";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=2)
			set '@failed,1;
		mes '@word$[@menu-1];
		mes "大陸は三つに分かれていて";
		setarray '@word$,"蜘蛛族が住むミョルニール山脈","巨人が住むウラノス","巨人が住むウトガルド","冬の国ルティエ";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=3)
			set '@failed,1;
		mes '@word$[@menu-1];
		setarray '@word$,"人間達が住むミッドガルド","人間達が住むルーンミッドガッツ","人魚が生息するトリトニア","砂漠の都市モロク";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=1)
			set '@failed,1;
		mes '@word$[@menu-1];
		setarray '@word$,"神々の住むアドガルス","神々の住むアスガルド","市民が住むシュバルツバルド","ルーンミッドガッツの首都プロンテラ";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=2)
			set '@failed,1;
		mes '@word$[@menu-1];
		mes "このように分かれる。";
		next;
		if('@failed) {
			mes "[シピエン=ライルリース]";
			mes "……";
			mes strcharinfo(0)+ "君、";
			mes "間違っている点があるね。";
			mes "これでは論文になりません。";
			next;
			mes "[シピエン=ライルリース]";
			mes "学長には見せられませんから";
			mes "書き直しです。";
			close;
		}
		mes "イグドラシルは世の中の根源である";
		setarray '@word$,"巨大な樹木であり","素敵なマステラの木であり","大きな柳であり","古い木の枝であり";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=1)
			set '@failed,1;
		mes '@word$[@menu-1];
		mes "その根は三箇所に向かって伸びる。";
		setarray '@word$,"シュバルツバルド、ヨトゥンヘイム、ニブルヘイムで","ミッドガルド、ヨトゥンヘイム、ナブルヘイムで","アスガルド、ヨトゥンヘイム、ナブルヘイムで","アスガルド、ヨトゥンヘイム、ニブルヘイムで";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=4)
			set '@failed,1;
		mes '@word$[@menu-1];
		mes "大地に固く根を張り巡らしている。";
		mes "イグドラシルの実を食べた者は";
		setarray '@word$,"すべての状態異常が回復する","HP・SPが全て回復する","HP・SPが半分回復する","沈黙・呪い・混乱から復帰する";
		if(select('@word$[0],'@word$[1],'@word$[2],'@word$[3])!=2)
			set '@failed,1;
		mes '@word$[@menu-1];
		next;
		if('@failed) {
			mes "[シピエン=ライルリース]";
			mes "……";
			mes strcharinfo(0)+ "君、";
			mes "間違っている点があるね。";
			mes "これでは論文になりません。";
			next;
			mes "[シピエン=ライルリース]";
			mes "学長には見せられませんから";
			mes "書き直しです。";
			close;
		}
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "[シピエン=ライルリース]";
		mes "うん、頑張りましたね。";
		mes "これは大切に扱ってください。";
		mes "絶対に失くしてはいけませんよ。";
		set CHANGE_SA,15;
		getitem 1550,1;
		next;
		mes "[シピエン=ライルリース]";
		mes "それでは論文を学長に見せて";
		mes "きなさい。";
		mes "卒業合否は彼が判定します。";
		close;
	case 15:
		mes "[シピエン=ライルリース]";
		mes "何をしているのですか？";
		mes "論文はできたのだから";
		mes "早く学長に見せてきなさい。";
		mes "その論文を無くさないうちに！";
		close;
	default:
		mes "[シピエン=ライルリース]";
		mes "何をしに来たのか知らないが";
		mes "今は考え事に専念したい。";
		mes "また後で訊ねてきなさい……";
		close;
	}
}

//==========================================
// 三次試験（モンスター研究）
//------------------------------------------
yuno_in03.gat,32,102,1	script	生物学教授	755,{
	if(Job == Job_Sage) {
		mes "[ルシウス=ケルソス]";
		mes "何か、不明な点でもあるのかね？";
		mes "質問があったら一週間前に";
		mes "予約してくれ。こっちも忙しくてね。";
		next;
		mes "[ルシウス=ケルソス]";
		mes "私がどれだけ忙しいか知ってるだろう？";
		mes "セージになったやつなら";
		mes "わかってると思ったが……";
		next;
		mes "[ルシウス=ケルソス]";
		mes "暇があったらダンジョンにでも";
		mes "行ってみてくれ。";
		mes "床に寝転がって天井を眺めるだけでも";
		mes "何か勉強になることがあるぞ。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[ルシウス=ケルソス]";
		mes "なんだ？";
		next;
		mes "[ルシウス=ケルソス]";
		mes "こんなところで遊んでいないで";
		mes "友達と外で遊んできなさい。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[ルシウス=ケルソス]";
		mes "ん？モンスター見物でも";
		mes "しに来たのかな？";
		next;
		mes "[ルシウス=ケルソス]";
		mes "見るのは良いが、あちこち";
		mes "触るなよ。";
		mes "触ると危険な物があるからな。";
		next;
		mes "[ルシウス=ケルソス]";
		mes "そして、もし珍しいモンスターを";
		mes "捕まえたらぜひ教えてくれ。";
		mes "高い値段で情報を買い取ろう。";
		close;
	}
	switch(CHANGE_SA) {
	case 11:
		switch(RESEARCH_SA) {
		case 0:
			mes "[ルシウス=ケルソス]";
			mes "よし、実技試験は通ったか。";
			mes "私が生物学の最先端を研究する";
			mes "ルシウス=ケルソスだ。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "人が名前を述べたら自分の名も";
			mes "言うのが礼儀ってもんだ。";
			mes "名前は？";
			next;
			menu strcharinfo(0)+ "です。",-;
			mes "[ルシウス=ケルソス]";
			mes "良い名前だ。会えて嬉しい。";
			mes "それでは、君が研究に入る分野に";
			mes "ついて説明しよう。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "知っているように君の研究テーマは";
			mes "モンスターについてだ。";
			mes "今までに、多くのモンスターに遭い、";
			mes "戦ってみたかな？";
			next;
			if(select("はい、たくさん努力しました","いいえ、あまり……")==1) {
				mes "[ルシウス=ケルソス]";
				mes "努力した？";
				mes "だいたい楽な所ばかり行ってた";
				mes "んじゃないか？";
				mes "まあいい。私の授業は楽じゃないぞ。";
			}
			else {
				mes "[ルシウス=ケルソス]";
				mes "そうか。別に構わんよ。";
				mes "私の研究室に入ったらそうも";
				mes "いかなくなるだろう。ハハハ。";
			}
			next;
			mes "[ルシウス=ケルソス]";
			mes "それでは始めようか。";
			mes "私の授業は、現場で学ぶことが";
			mes "多いということだけ肝に銘じておけ。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "よし、これらを集めてこい。";
			set RESEARCH_SA,rand(1,3);
			switch(RESEARCH_SA) {
			case 1:
				mes "^3355FF触手^000000 5個";
				mes "^3355FF単細胞^000000 5個";
				mes "^3355FF魚の尻尾^000000 5個";
			case 2:
				mes "^3355FFかにニッパ^000000 5個";
				mes "^3355FF貝のむきみ^000000 5個";
				mes "^3355FF人魚の心臓^000000 5個";
				break;
			case 3:
				mes "^3355FF血管^000000 5個";
				mes "^3355FFかにニッパ^000000 5個";
				mes "^3355FF鋭い鱗^000000 5個";
				break;
			}
			next;
			mes "[ルシウス=ケルソス]";
			mes "全て揃ったら話を続ける。";
			mes "じゃ、行ってこい。";
			close;
		case 1:
		case 2:
		case 3:
			switch(RESEARCH_SA) {
				case 1: setarray '@need,962,1052,1023;  break;
				case 2: setarray '@need,960,966,950;   break;
				case 3: setarray '@need,1050,960,963; break;
			}
			for(set '@i,0; '@i<3; set '@i,'@i+1) {
				if(countitem('@need['@i]) < 5) {
					mes "[ルシウス=ケルソス]";
					mes "おいおい、しっかりしてくれ。";
					mes "もう一度言うからよく聞いてくれ。";
					next;
					mes "[ルシウス=ケルソス]";
					for(set '@i,0; '@i<3; set '@i,'@i+1) {
						mes "^3355FF" +getitemname('@need['@i])+ "^000000 5個";
					}
					close;
				}
			}
			mes "[ルシウス=ケルソス]";
			mes "やぁ、おつかれさん。";
			mes "直接拾ってきたのか買ったのかは";
			mes "わからんが。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "とにかく、このアイテムを落とす";
			mes "やつらには共通点がある。";
			mes "それが何かわかるか？";
			next;
			switch(select("水属性です","魚貝類です","アクティブです","モンスターです")) {
			case 1:
			case 2:
				mes "[ルシウス=ケルソス]";
				mes "そう、水属性であり、魚貝類でもある。";
				mes "大部分の魚貝類は水場に生息する";
				mes "から水属性なんだ。";
				break;
			case 3:
				if(RESEARCH_SA == 3) {
					mes "[ルシウス=ケルソス]";
					mes "おい……マリンスフィアーに";
					mes "足でも生えていたのか？";
					mes "本当に血管は自力で取ってきた";
					mes "んだろうな……？";
				}
				else {
					mes "[ルシウス=ケルソス]";
					mes "最近はお化け貝も襲ってくるのか。";
					mes "それともバドンやカニがアイテムでも";
					mes "欲しがったのか……";
				}
				next;
				mes "[ルシウス=ケルソス]";
				//mes "全部先行ではないと..."; //怪奇文章なので統一
				//mes "精神ちょっと調えなさい.";
				//mes "魚貝類ながら水属性なことが共通点だ。";
				mes "全部アクティブではない！";
				mes "まったく……";
				mes "魚貝類で、水属性を持つのが";
				mes "共通点だ。";
				break;
			case 4:
				mes "[ルシウス=ケルソス]";
				mes "……";
				mes "そういうことを聞いているのではない。";
				mes "まったく……";
				mes "魚貝類で、水属性を持つのが";
				mes "共通点だ。";
				break;
			}
			next;
			mes "[ルシウス=ケルソス]";
			mes "すべての魚貝類が水属性という";
			mes "わけではないが、だいたいがそうだ。";
			mes "それでは、これら魚貝類に効く";
			mes "魔法はどれかな？";
			next;
			switch(select("ライトニングボルトです","ファイアーボルトです","サンダーストームです","フロストダイバーです")) {
			case 1:
				mes "[ルシウス=ケルソス]";
				mes "正解。水属性には風属性の";
				mes "魔法であるライトニングボルトが効く。";
				mes "詠唱に反応するモンスター達には";
				mes "注意しなければならないが。";
				break;
			case 2:
				mes "[ルシウス=ケルソス]";
				mes "川の中で焚き火でもするのか。";
				mes "効くわけないだろうが！";
				mes "魚貝類は大部分が水属性だから";
				mes "風属性の魔法がよく効くんだよ。";
				break;
			case 3:
				mes "[ルシウス=ケルソス]";
				mes "サンダーストームでも大丈夫だ。";
				mes "風属性魔法だからな。";
				mes "ただ、攻撃地点には気を";
				mes "つけなければならない。";
				break;
			case 4:
				mes "[ルシウス=ケルソス]";
				mes "……";
				mes "水が好きなやつらに水を与えて";
				mes "どうする!!!!";
				mes "水属性に水属性攻撃をしても";
				mes "ほとんど意味無し。";
				break;
			}
			mes "[ルシウス=ケルソス]";
			mes "ところがペノメナやヒトデのような";
			mes "モンスターは魚貝類だが属性が";
			mes "違うので気をつけなければならない。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "それでは、次は昆虫について";
			mes "勉強してみようか。";
			mes "では……";
			next;
			mes "[ルシウス=ケルソス]";
			mes "次はこれらを集めてこい。";
			set RESEARCH_SA,rand(4,7);
			switch(RESEARCH_SA) {
			case 4:
				mes "^3355FFくもの糸^000000 5個";
				mes "^3355FFかたい皮^000000 5個";
				mes "^3355FF虫の觸角^000000 5個";
				break;
			case 5:
				mes "^3355FF硬い角^000000 5個";
				mes "^3355FFカタシムリの皮^000000 5個";
				mes "^3355FF蛾の羽粉^000000 5個";
				break;
			case 6:
				mes "^3355FFかまきりの手^000000 5個";
				mes "^3355FF蟲の皮^000000 5個";
				mes "^3355FF華麗な蟲の皮^000000 5個";
				break;
			case 7:
				mes "^3355FFくもの糸^000000 5個";
				mes "^3355FFかまきりの手^000000 5個";
				mes "^3355FFけっこうかたい皮^000000 5個";
				break;
			}
			next;
			mes "[ルシウス=ケルソス]";
			mes "全て揃ったら話を続ける。";
			mes "じゃ、行ってこい。";
			close;
		case 4:
		case 5:
		case 6:
		case 7:
			switch(RESEARCH_SA) {
				case 4: setarray '@need,1025,935,928;  break;
				case 5: setarray '@need,947,946,1057;  break;
				case 6: setarray '@need,1031,955,1013; break;
				case 7: setarray '@need,1025,1031,943; break;
			}
			for(set '@i,0; '@i<3; set '@i,'@i+1) {
				if(countitem('@need['@i]) < 5) {
					mes "[ルシウス=ケルソス]";
					mes "何だ、聞いた品を忘れただと？";
					mes "まあいい、もう一度言うぞ。";
					next;
					for(set '@i,0; '@i<3; set '@i,'@i+1) {
						mes "^3355FFFD" +getitemname('@need['@i])+ "^000000 5個";
					}
					close;
				}
			}
			mes "[ルシウス=ケルソス]";
			mes "よし、よく集めてきた。";
			mes "観察も怠らなかっただろうな。";
			mes "まぁこれくらいならそんなに";
			mes "大変でもなかっただろう。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "昆虫は案外色々な属性を";
			mes "持っているから魔法を使う前に";
			mes "もう一度考えておかなければ";
			mes "ならないだろう。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "特に、シーフのハイディングや";
			mes "アサシンのクローキングも";
			mes "やつらには効かないという点も";
			mes "注目すべき点だ。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "中には集団行動する昆虫もいる。";
			mes "ボスクラスの昆虫が、さながら";
			mes "兵隊を従えるかのごとくな。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "女王蟻のマヤーとか……";
			mes "女王蜂のミストレス、";
			mes "盗蟲の親分－黄金蟲……";
			next;
			mes "[ルシウス=ケルソス]";
			mes "こうしたボスクラスのやつは";
			mes "一人で対峙した場合死を覚悟";
			mes "しなければならない。";
			mes "こいつらの棲み処を探索する";
			mes "場合は、仲間を連れて行くのが";
			mes "ベストだろう。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "さて、話はこれくらいにして";
			mes "そろそろ論文を書かないとな。";
			mes "形式的にも必要だからさっさと";
			mes "やってしまおう。";
			mes "その前に、以下のものを用意して";
			mes "きてくれ。";
			next;
			mes "[ルシウス=ケルソス]";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[ルシウス=ケルソス]";
			mes "集まったらまたここに来てくれ。";
			mes "もう少しだ、頑張ってな。";
			set RESEARCH_SA,0;
			set CHANGE_SA,12;
			close;
		}
	case 12:
		if(countitem(916) < 1 || countitem(919) < 1 || countitem(1019) < 1 || countitem(1024) < 1 || countitem(713) < 1) {
			mes "[ルシウス=ケルソス]";
			mes "なんだ、用意できていないじゃないか。";
			mes "もう一度言う……";
			next;
			mes "[ルシウス=ケルソス]";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[ルシウス=ケルソス]";
			mes "これまで頑張ってきたんだから";
			mes "それくらい何でもないだろう？";
			mes "ほら、早く用意してきなさい。";
			close;
		}
		delitem 916,1;
		delitem 919,1;
		delitem 1019,1;
		delitem 1024,1;
		delitem 713,1;
		mes "[ルシウス=ケルソス]";
		mes "よし、よく集めたな。";
		next;
		mes "[ルシウス=ケルソス]";
		mes "あえて君が自分で書いても良いが";
		mes "ここに例を置くから参考にしなさい。";
		next;
		mes "[ルシウス=ケルソス]";
		mes "いいだろう？";
		mes "自分の体で体験してきたことが";
		mes "もう十分に意味のあることなんだ。";
		mes "じゃ、できたら見せてもらおう。";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		menu "モンスター達は種族によって",-;
		mes "モンスター達は種族によって";
		menu "様々な属性を持っている",-;
		mes "様々な属性を持っている。";
		menu "モンスター達の属性をあらかじめ把握し",-;
		mes "モンスター達の属性をあらかじめ把握し";
		menu "的確に魔法を使わなければならない",-;
		mes "的確に魔法を使わなければならない。";
		menu "特に注意すべきモンスターは",-;
		mes "特に注意すべきモンスターは";
		menu "聖属性と闇属性のモンスターである",-;
		mes "聖属性と闇属性のモンスターである。";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "[ルシウス=ケルソス]";
		mes "うむ、おつかれさん！";
		mes "これは絶対失くすなよ！";
		set CHANGE_SA,15;
		getitem 1550,1;
		next;
		mes "[ルシウス=ケルソス]";
		mes "これを学長に読んでもらって";
		mes "卒業が決まる。";
		mes "よくここまで頑張ったな。";
		close;
	case 15:
		mes "[ルシウス=ケルソス]";
		mes "何してるんだ？論文を学長に";
		mes "見せるよう言ったはずだ。";
		mes "ほら、こんなところで油売ってないで。";
		close;
	default:
		mes "[ルシウス=ケルソス]";
		mes "う～頭が痛い……";
		mes "準備する物が多すぎるんだよ……";
		mes "何だ！こっちは忙しくてたまらん！";
		next;
		mes "[ルシウス=ケルソス]";
		mes "見学なら勝手に見ていきなさい！";
		mes "ただでさえ頭が痛いというのに……";
		mes "まったく……（ブツブツ）";
		close;
	}
}

//==========================================
// 三次試験（魔法研究）
//------------------------------------------
yuno_in03.gat,244,31,3	script	物理学教授	120,{
	if(Job == Job_Sage) {
		mes "[エベシ=ジョルダ]";
		mes "ヒョホホ、こんにちは。";
		mes "何の用かな？";
		mes "……おう、セージじゃないの～！";
		mes "会えて嬉しいねぇ～";
		next;
		mes "[エベシ=ジョルダ]";
		mes "それにしても、こんなところで";
		mes "暇つぶしかい～？";
		mes "ま、魔力に溺れた連中よりゃ";
		mes "マシだけどね～ヒョホホ。";
		next;
		mes "[エベシ=ジョルダ]";
		mes "ナニナニ、たまには学び舎に";
		mes "帰りたくなる？";
		mes "そんなこと言わないで、";
		mes "ほらほら外に出ようよ、ヒョホホ……";
		close;
	}
	if(Job == Job_Novice) {
		mes "[エベシ=ジョルダ]";
		mes "ナニナニ、かわいいノービスくん";
		mes "じゃないの～";
		next;
		mes "[エベシ=ジョルダ]";
		mes "ここには遊びに来たの？";
		mes "キャンディでも欲しいの？";
		mes "ん～っと……";
		next;
		mes "[エベシ=ジョルダ]";
		mes "ヒョホホ、キャンディ無いや……";
		mes "サンタポリンでも探してごらん、";
		mes "ヒョホホ……";
		close;
	}
	if(Job != Job_Magician) {
		mes "[エベシ=ジョルダ]";
		mes "ん？ん？ナニナニ？";
		next;
		mes "[エベシ=ジョルダ]";
		mes "ここに見物かな？";
		mes "ここにはあんまり見るものが";
		mes "無いと思うよ。";
		next;
		mes "[エベシ=ジョルダ]";
		mes "めずらしいって？";
		mes "あらそ～ヒョホホホホ";
		close;
	}
	switch(CHANGE_SA) {
	case 13:
		switch(RESEARCH_SA) {
		case 0:
			mes "[エベシ=ジョルダ]";
			mes "こんにちは、会えて嬉しいよ。";
			mes "久しぶりに来た学生だし～";
			next;
			mes "[エベシ=ジョルダ]";
			mes "ヒョホホ、私がキミを教える教授。";
			mes "どう？嬉しいでしょう？ヒョホホホ！";
			next;
			mes "[エベシ=ジョルダ]";
			mes "で、講義の前にちょっと";
			mes "頼まれてくれない～？";
			mes "いやいや、難しいことじゃないから。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "^3355FF石^000000 30個だけ持って来て。";
			mes "それだけ。あまり難しくないでしょ？";
			next;
			mes "[エベシ=ジョルダ]";
			mes "石を拾うのが大変だったら";
			mes "友達のシーフにでも頼んでごらん。";
			mes "じゃ、30個待ってるよ～";
			set RESEARCH_SA,1;
			close;
		case 1:
			if(countitem(7049) < 30) {
				mes "[エベシ=ジョルダ]";
				mes "なにするの？";
				mes "私に悪戯しに来たの？";
				mes "ほらほら遊んでないで行きなさい～！";
				next;
				mes "[エベシ=ジョルダ]";
				mes "^3355FF石^000000 30個集めてきてって";
				mes "言ったじゃないの！";
				mes "道に転がってる石なんか簡単に";
				mes "拾えるでしょ～？";
				close;
			}
			mes "[エベシ=ジョルダ]";
			mes "やぁ、よく集めてきてくれた！";
			mes "ちょっとまってねん～";
			next;
			mes "[エベシ=ジョルダ]";
			mes "アブラカタブラ!!";
			next;
			mes "[エベシ=ジョルダ]";
			mes "ア～ブラカタブラ!!";
			next;
			mes "[エベシ=ジョルダ]";
			mes "アブラカ～タブラ!!";
			next;
			delitem 7049,30;
			mes "[エベシ=ジョルダ]";
			mes "ほら、こんなただの石から";
			mes "3個の良い石ができちゃった！";
			next;
			mes "[エベシ=ジョルダ]";
			mes "満足満足。";
			mes "ね？嬉しいでしょ？ヒョホホ！";
			next;
			set RESEARCH_SA,2;
			getitem 991,1;
			getitem 993,1;
			getitem 992,1;
			mes "[エベシ=ジョルダ]";
			mes "ほら、属性原石あげる。";
			mes "それでね、それでね";
			mes "まだまだ最後まで話を聞いて。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "以下の矢を作ってきて。";
			mes "^3355FF水晶の矢^000000 50個";
			mes "^3355FF岩石の矢^000000 50個";
			mes "^3355FF風の矢^000000 50個";
			next;
			mes "[エベシ=ジョルダ]";
			mes "アーチャーの友達でも居れば";
			mes "作ってくれるでしょ。";
			mes "それじゃよろしく！ヒョホホ～";
			close;
		case 2:
			if(countitem(1754) < 50 || countitem(1756) < 50 || countitem(1755) < 50) {
				mes "[エベシ=ジョルダ]";
				mes "ナニナニ？";
				mes "さっき渡した属性原石はどうしたの？";
				mes "まさか売ったんじゃ……";
				next;
				mes "[エベシ=ジョルダ]";
				mes "^3355FF水晶の矢^000000 50個";
				mes "^3355FF岩石の矢^000000 50個";
				mes "^3355FF風の矢^000000 50個";
				mes "アーチャーの友達に頼んで";
				mes "作ってもらいな～ヒョホホ";
				close;
			}
			mes "[エベシ=ジョルダ]";
			mes "やぁ、よく持ってきたね。";
			mes "それじゃ、講義を始めよっか。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "読んであげるから良く聞いて";
			mes "大事なところに線をひくように。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "水属性魔法は火属性に強い。";
			mes "ちょうど火に水をかけると思えば良い。";
			mes "簡単でしょ？";
			next;
			mes "[エベシ=ジョルダ]";
			mes "風属性魔法は水属性に強い。";
			mes "湖に雷が落ちたらどうなるかな？";
			mes "ヒョホホ！";
			next;
			mes "[エベシ=ジョルダ]";
			mes "地属性魔法は風属性に強い。";
			mes "風を防ごうとしたら土で家を";
			mes "建てるでしょ？ソレソレ。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "火属性魔法は地属性に強い。";
			mes "火事が起こったら木が燃えちゃう";
			mes "でしょ？それと同じ……";
			next;
			mes "[エベシ=ジョルダ]";
			mes "おろ、もうこんな時間か。";
			mes "それじゃ～続きは次の時間にしよう。";
			next;
			delitem 1754,50;
			delitem 1756,50;
			delitem 1755,50;
			mes "[エベシ=ジョルダ]";
			mes "次の時間までに";
			mes "^3355FF聖水^000000 を1個だけ用意して";
			mes "おいてほしい。";
			mes "友達に聖職者がいなかったら";
			mes "一人で作るしかないね。";
			set RESEARCH_SA,3;
			close;
		case 3:
			if(countitem(523) < 1) {
				mes "[エベシ=ジョルダ]";
				mes "ナニしてるの！";
				mes "ど忘れしちゃだめじゃない～";
				next;
				mes "[エベシ=ジョルダ]";
				mes "^3355FF聖水^000000 1個";
				mes "アコライトやプリーストの友達に";
				mes "頼んでみなさい。ヒョホホ";
				close;
			}
			mes "[エベシ=ジョルダ]";
			mes "よーしよっし！";
			mes "よく持ってきた！";
			mes "さてさて、講義を続けないとね。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "今度も読んであげるからよく聴いて";
			mes "メモするんだよ。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "水属性は風属性魔法に弱い！";
			mes "凍った時、雷が落ちたら痛かった";
			mes "だろう？ヒョホホ！";
			next;
			mes "[エベシ=ジョルダ]";
			mes "風属性は地属性魔法に弱い！";
			mes "飛び回ってる子が転んだら";
			mes "大きなケガをするだろう？";
			mes "ヒョ……";
			next;
			mes "[エベシ=ジョルダ]";
			mes "地属性は火属性魔法に弱い！";
			mes "地から生える木に火がついたら";
			mes "燃えて無くなるだろう？";
			next;
			mes "[エベシ=ジョルダ]";
			mes "火属性は水属性魔法に弱い！";
			mes "熱いものを冷やすのはやっぱり";
			mes "水だからね。";
			next;
			mes "[エベシ=ジョルダ]";
			mes "よしよし、講義はこれにて";
			mes "終了～～～～～！";
			mes "よくわかったでしょ？";
			next;
			delitem 523,1;
			mes "[エベシ=ジョルダ]";
			mes "うん、あとは論文ができれば完璧。";
			mes "やっぱり私の講義は最高ね。";
			mes "ヒョホホホホホ！";
			set RESEARCH_SA,0;
			set CHANGE_SA,14;
			next;
			mes "[エベシ=ジョルダ]";
			mes "じゃ、早速論文を書く準備をしよう。";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[エベシ=ジョルダ]";
			mes "これだけ準備するように。";
			mes "待ってるよ。";
			close;
		}
	case 14:
		if(countitem(916) < 1 || countitem(919) < 1 || countitem(1019) < 1 || countitem(1024) < 1 || countitem(713) < 1) {
			mes "[エベシ=ジョルダ]";
			mes "ナニナニ？";
			mes "ど忘れはいけないな～～";
			next;
			mes "[エベシ=ジョルダ]";
			mes "筆記具に使う ^3355FF鳥の羽毛^000000 1個";
			mes "文字を入れる ^3355FF獣の皮^000000 1個";
			mes "製本に必要な ^3355FF木屑^000000 1個";
			mes "インクに使う ^3355FF墨汁^000000 1個";
			mes "墨汁を入れる ^3355FF空きビン^000000 1個";
			next;
			mes "[エベシ=ジョルダ]";
			mes "準備くらい、一人でできちゃうでしょ？";
			mes "手伝ってもらってもいいけどね～";
			mes "じゃ、待ってるから！";
			close;
		}
		delitem 916,1;
		delitem 919,1;
		delitem 1019,1;
		delitem 1024,1;
		delitem 713,1;
		mes "[エベシ=ジョルダ]";
		mes "うむ。";
		mes "じゃぁ書いてみよう。";
		mes "私が教えてあげたんだから";
		mes "大丈夫だって～～ヒョホホ！";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "属性魔法は4元素からなり、";
		setarray '@word$,"水, 地, 火, 風に分けられる","地, 水, 火, 風で分けられる","水, 風, 地, 火に分けられる";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1]+ "。";
		mes "それぞれの属性には特性があり、";
		setarray '@word$,"風属性魔法は水属性に強く","水属性魔法は火属性に強く","火属性魔法は地属性に強く";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1];
		setarray '@word$,"地属性魔法は風属性に強い。","風属性魔法は水属性に強い。","水属性魔法は火属性に強い。";
		mes '@word$[@menu-1];
		setarray '@word$,"しかし弱点も存在するから","属性武器も同様で","種族によって属性も様々であるから";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1];
		setarray '@word$,"自分の能力を把握する必要がある","場所によって属性を変えたほうが良い","赤ポーションは苺味という噂だ";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1]+ "。";
		next;
		setarray '@word$,"一番可愛い娘はプロンテラのエイミーで","赤ポーションはポリンから作ると言うが","魔法の深みは人智を超え";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1];
		setarray '@word$,"モロクの商人のお嬢さんもかわいい","どうして苺味がするのかわからない","むやみに魔力に頼ると危険だ";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1]+ "。";
		setarray '@word$,"私にウサギのヘアバンドを与えたら","それでは白ポーションの味は","適切な魔法の使用と休憩は";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1];
		setarray '@word$,"喜びを与えてくれる","想像しにくい","安全な戦闘を保障してくれる";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1]+ "。";
		setarray '@word$,"ウサギのヘアバンドはアコライトに合い","ハラハラする感じが好きで","他の職業とパーティを結び";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1];
		setarray '@word$,"ナイトにも合うのか本当に知りたい","体力が底を尽きかけても飲めない","それで戦闘に望むことが望ましい";
		set @menu,select('@word$[0],'@word$[1],'@word$[2]);
		mes '@word$[@menu-1]+ "。";
		next;
		mes "……";
		next;
		mes "…………";
		next;
		mes "………………";
		next;
		mes "[エベシ=ジョルダ]";
		mes "ほほう～";
		mes "なかなかセンスあるじゃない～";
		mes "ほら、できたね。ヒョホホ";
		set CHANGE_SA,15;
		getitem 1550,1;
		next;
		mes "[エベシ=ジョルダ]";
		mes "それを学長に見せようよ。";
		mes "そうしたらキミも卒業だ！";
		mes "ヒョホ～";
		close;
	case 15:
		mes "[エベシ=ジョルダ]";
		mes "なにしてるの？";
		mes "早く行かなきゃだめじゃな～い！";
		next;
		mes "[エベシ=ジョルダ]";
		mes "忘れ物しちゃうよ？";
		mes "手遅れになるまえにササっと";
		mes "卒業しちゃっておいで！";
		close;
	default:
		mes "[エベシ=ジョルダ]";
		mes "ナニナニ？";
		next;
		mes "[エベシ=ジョルダ]";
		mes "見学に来たの？";
		mes "ここはあまり見るもの無いよ？";
		next;
		mes "[エベシ=ジョルダ]";
		mes "まあ自由に見てらっしゃい～";
		mes "ヒョホホホホ";
		close;
	}
}
