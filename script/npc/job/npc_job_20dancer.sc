//====================================================================
//Ragnarok Online Dancer Jobchange Script by Kalen
//ダンス試験終了時のwaitを設定 by Deme
//
//　■ CHANGE_DC -> 0～9
//====================================================================

//==========================================
// 試験申請および一次試験
//------------------------------------------

comodo.gat,193,151,4	script	ボルロブ	86,{
	mes "[ボルロブ]";
	mes "ああ……多くの人の注目を集める";
	mes "プリマドンナ！";
	mes "彼女達がダンサーになる瞬間を";
	mes "目の前で見られるなんて！";
	next;
	mes "[ボルロブ]";
	mes "この時代に生まれて本当に幸せ。";
	mes "コモドダンサーばんざい！";
	next;
	mes "[ボルロブ]";
	mes "うん？あなたもダンサー転職試験を";
	mes "見たいって？";
	next;
	if(select("ダンサー転職場に移動","取り消し")==2) {
		mes "[ボルロブ]";
		mes "ノリわる～い";
		close;
	}
	mes "[ボルロブ]";
	mes "イェェイ！レッツゴー！";
	close2;
	warp "job_duncer.gat",70,49;
	end;
}

//==============================================================
job_duncer.gat,43,93,4	script	エイル	724,{
	cutin "job_dancer_eir01",2;
	if(Upper == UPPER_HIGH) {
		mes "[エイル]";
		mes "いち、に、さん、し……";
		mes "うーん";
		next;
		mes "[エイル]";
		mes "そんなに見られていると";
		mes "練習に集中できないわ！";
		next;
		mes "[エイル]";
		mes "……";
		mes "……どこかでお会いしたような";
		mes "気がしますが……";
		next;
		mes "[エイル]";
		mes "でも思い出せないわ……";
		mes "私には練習があるから";
		mes "向こうへ行っていただけます？";
		close2;
		cutin "job_dancer_eir01",255;
		end;
	}
	if(Job == Job_Dancer) {
		mes "[エイル]";
		mes "こんにちは～";
		mes "最近はどうですか？";
		mes "人々を楽しませていますか？";
		close2;
		cutin "job_dancer_eir01",255;
		end;
	}
	if(Job != Job_Archer || Sex == 1) {
		mes "[エイル]";
		mes "お客さん、ここは関係者以外";
		mes "立ち入り禁止ですよ？";
		next;
		mes "[エイル]";
		mes "ダンススクールは誰でも入れる";
		mes "わけじゃないんですから。";
		next;
		mes "[エイル]";
		mes "見学なら村のダンスステージに";
		mes "行ってくださいね。";
		close2;
		cutin "job_dancer_eir01",255;
		end;
	}
	switch(CHANGE_DC) {
	case 0:
		mes "[エイル]";
		mes "いらっしゃいませ～";
		mes "様々な踊りを教えている";
		mes "「コモドダンススクール」です。";
		next;
		mes "[エイル]";
		mes "各地から訪れる観光客に";
		mes "素敵な踊りを提供し、";
		next;
		mes "[エイル]";
		mes "さらにはルーンミッドガッツの";
		mes "有名人になることができる";
		mes "踊り娘を育てているんです。";
		next;
		mes "[エイル]";
		mes "どうですか？";
		mes "たくさんの人々の前で派手な";
		mes "ライトを受けダンスをすることが";
		mes "できるんです。";
		mes "素敵じゃありませんか！";
		next;
		mes "[エイル]";
		mes "でも、我がダンススクールは";
		mes "誰でも入れるわけじゃないのが";
		mes "他とは違うところ。";
		next;
		mes "[エイル]";
		mes "ダンサーになれそうもない人は";
		mes "スクールで断られてしまうんです。";
		next;
		mes "[エイル]";
		mes "どうでしょう、";
		mes "お姉さんには素質がありそうな";
		mes "感じがします。";
		mes "ここでダンスレッスンを受けて";
		mes "みませんか？";
		next;
		cutin "job_dancer_eir02",2;
		mes "[エイル]";
		mes "そこにある申込書にちょこっと";
		mes "書くだけです。";
		next;
		cutin "job_dancer_eir01",2;
		mes "[エイル]";
		mes "どうです？";
		mes "申し込んでみませんか？";
		mes "ね？見学も兼ねてどうですか？";
		next;
		if(select("はい、やってみます","無視する")==2) {
			mes "[エイル]";
			mes "そんな……冷たいわ……";
			mes "また寄ってくださいね？";
			mes "ね？";
			break;
		}
		if(JobLevel < 40) {
			mes "[エイル]";
			mes "えっと……";
			mes "惜しいですがレッスンを受ける";
			mes "条件を満たしていなかった";
			mes "ようです……";
			next;
			mes "[エイル]";
			mes "少なくともJobLv40以上に";
			mes "ならないと申し込みをお受け";
			mes "することができないんです。";
			mes "それでは、またお目にかかれる";
			mes "日を楽しみにしております。";
			break;
		}
		cutin "job_dancer_eir02",2;
		mes "[エイル]";
		mes "よく決心しました！";
		mes "そこにある申込書に記入してください。";
		next;
		mes "……";
		next;
		mes "……カリカリカリ……";
		next;
		mes "……";
		next;
		cutin "job_dancer_eir01",2;
		mes "[エイル]";
		mes "お名前は……";
		mes strcharinfo(0)+ "さん……";
		mes "素敵な名前ですね！";
		mes "では少々お待ちを。";
		mes "書類をスクール長に届けてきます。";
		set CHANGE_DC,1;
		break;
	case 1:
		mes "[エイル]";
		mes "はい、さきほど申し込みを";
		mes "されましたね？";
		mes "ではレッスンに必要な物を";
		mes "用意していただきます。";
		next;
		mes "[エイル]";
		mes "備品に不足なものがあって……";
		mes "ご自分のレッスンに使うもの";
		mes "ですから、お手数ですが";
		mes "揃えてきてくださいね。";
		next;
		mes "[エイル]";
		mes "それと一応^0000FFレッスン料";
		mes "10000Zeny^000000が必要です。あと、";
		switch(rand(3)) {
			case 0:
				set CHANGE_DC,2;
				mes "靴のすべり止めにする";
				mes "^0000FFミミズの皮 5個^000000があれば";
				mes "良いでしょう。";
				next;
				mes "[エイル]";
				mes "そして足を怪我しないように";
				mes "^0000FFブーツ^000000も1足必要です。";
				break;
			case 1:
				set CHANGE_DC,3;
				mes "衣装の飾りにする^0000FF貝殻 2個^000000と";
				next;
				mes "[エイル]";
				mes "足を怪我した場合に塗る";
				mes "^0000FF黄ポーション 5個^000000、";
				mes "軟膏の代わりにする";
				mes "^0000FFゼロピー^000000も^0000FF20個^000000必要です。";
				next;
				mes "[エイル]";
				mes "あとは……";
				mes "公演用かつらを作る^0000FF長い髪 10個^000000";
				next;
				mes "[エイル]";
				mes "怪我をしないように履く";
				mes "^0000FFサンダル^000000も1足必要です。";
				break;
			case 2:		//台詞適当、未調査
				set CHANGE_DC,4;
				mes "^0000FFべとべとする液体 20個^000000";
				mes "^0000FF赤ポーション 5個^000000";
				mes "^0000FFゼロピー 3個^000000";
				mes "^0000FFシューズ^000000";
				break;
		}
		next;
		mes "[エイル]";
		mes "では、レッスンの用意ができたら";
		mes "また声をかけてください。";
		break;
	case 2:
	case 3:
	case 4:
		switch(CHANGE_DC) {
			case 2:
				setarray '@need,1055,2405;
				setarray '@amount,5,1;
				break;
			case 3:
				setarray '@need,965,503,909,1020,2401;
				setarray '@amount,2,5,20,10,1;
				break;
			case 4:
				setarray '@need,938,501,909,2403;
				setarray '@amount,20,5,3,1;
				break;
		}
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1) {
			if(countitem('@need['@i]) < '@amount['@i] || Zeny < 10000)
				break;
		}
		if('@i < getarraysize('@need)) {
			mes "[エイル]";
			mes "うん……";
			mes "ちょっと足りないみたいです。";
			mes "必要な物をもう一度教えるから";
			mes "用意してきてくださいね。";
			next;
			mes "[エイル]";
			mes "^0000FFレッスン料 10000 Zeny^000000";
			for(set '@i,0; '@i<getarraysize('@need)-1; set '@i,'@i+1)
				mes "^0000FF" +getitemname('@need['@i])+ " " +'@amount['@i]+ "個^000000";
			mes "^0000FF" +getitemname('@need['@i])+ "^000000";
			next;
			mes "[エイル]";
			mes "以上です。";
			mes "待ってますね。";
			break;
		}
		cutin "job_dancer_eir02",2;
		mes "[エイル]";
		mes "あっ全部持ってきましたね。";
		mes "ではレッスン料をいただいて";
		mes "おきます。";
		set Zeny,Zeny-10000;
		next;
		cutin "job_dancer_eir01",2;
		//fall through
	case 5:
	case 6:
		mes "[エイル]";
		mes "面接試験担当の^0000FF「ボルワージュ」^000000先生";
		mes "のところに行ってみてください。";
		mes "簡単な質問に答えるだけですから";
		mes "リラックスして受けてくださいね。";
		if(CHANGE_DC < 6)
			set CHANGE_DC,5;
		break;
	default:
		mes "[エイル]";
		mes "熱心に練習して素敵な踊りを";
		mes "見せてくださいね！";
		break;
	}
	close2;
	cutin "dummy",255;
	end;
}

//==========================================
// 二次試験および転職
//------------------------------------------

job_duncer.gat,95,93,4	script	ボルワージュ	101,{
	if(Job == Job_Dancer) {
		mes "[ボルワージュ]";
		mes "あら、こんにちは～";
		next;
		mes "[ボルワージュ]";
		mes "最近はどう？";
		mes "たくさんの人達に感動を与えてる";
		mes "かしら？";
		mes "常にダンサーとしての心構えを";
		mes "忘れないでね。";
		close;
	}
	if(Job != Job_Archer || Sex == 1) {
		mes "[ボルワージュ]";
		mes "あら、外からいらしたの？";
		mes "私の素敵な踊りを見るために、";
		mes "遠いところいらしたのね……";
		next;
		mes "[ボルワージュ]";
		mes "残念ながら私はもう現役引退して";
		mes "後輩の養成に力を注いでいるの。";
		next;
		mes "[ボルワージュ]";
		mes "村中央部のダンスステージへ";
		mes "行ってみれば、私の踊りを";
		mes "しっかり受け継いだ娘が";
		mes "踊りを披露しているはず。";
		close;
	}
	if(SkillPoint) {
		mes "[ボルワージュ]";
		mes "スキルポイントが残っていたら";
		mes "転職できません。";
		mes "消費してきなさい。";
		close;
	}
	switch(CHANGE_DC) {
	default:	//0～4のとき
		mes "[ボルワージュ]";
		mes "あら、ダンサー志望の娘ね。";
		next;
		mes "[ボルワージュ]";
		mes "ダンサーになりたければ、";
		mes "まず当スクールへの申し込みを";
		mes "済ませてらっしゃい。";
		mes "舞台の左側らへんにいる「エイル」";
		mes "に聞けばあれこれ教えてくれるはず。";
		close;
	case 5:
		mes "[ボルワージュ]";
		mes "あら、ダンサー志望生ね。";
		next;
		mes "[ボルワージュ]";
		mes "……もうちょっと体を";
		mes "引き締めないとね。";
		next;
		mes "[ボルワージュ]";
		mes "そんなに心配しなくても大丈夫。";
		mes "レッスンの途中に体もできて";
		mes "くるから。";
		mes "体型矯正レッスンもあるし。ふふ……";
		next;
		mes "[ボルワージュ]";
		mes "それではあなたダンサーになる心構えを";
		mes "知りたいから、いくつか聞いてみたいと";
		mes "思います。一応面接なんだけど";
		mes "簡単な質問だから気楽にね。";
		break;
	case 6:
		mes "[ボルワージュ]";
		mes "元気出して！";
		break;
	case 7:
		mes "[ボルワージュ]";
		mes "それでは実習にはいります。";
		mes "その前にいくつか注意事項を";
		mes "話しておきましょうか。";
		next;
		if(select("注意事項を聞く","試験場に移動する")==2) {
			set CHANGE_DC,8;
			mes "[ボルワージュ]";
			mes "それではがんばって！";
			close2;
			warp "job_duncer.gat",104,109;
			end;
		}
		mes "[ボルワージュ]";
		mes "実はこれはオーディションなの。";
		mes "^0000FF1分^000000の制限時間で";
		next;
		mes "[ボルワージュ]";
		mes "^0000FF一人づつ順番に^000000 ダンスを踊って";
		mes "もらいます。";
		mes "ダンスの経験が無くても心配しないで。";
		next;
		mes "[ボルワージュ]";
		mes "会場に入ると舞台が見えて、";
		mes "まず ^0000FF舞台全体が見渡せる^000000位置に";
		mes "立たなければならない。";
		next;
		mes "[ボルワージュ]";
		mes "^0000FF前後左右が良く見渡せるように^000000ね。";
		mes "マウスの右ボタンをダブルクリック";
		mes "して方向も初期の状態に……";
		mes "撮影用語はあまりくわしくないけど……";
		next;
		mes "[ボルワージュ]";
		mes "開始の合図があるまでは^0000FF控室^000000で";
		mes "順番を待ってね。";
		mes "前の人が脱落するか、時間が来たら";
		mes "あなたの番よ。";
		next;
		mes "[ボルワージュ]";
		mes "人が多いと控室が満員になる";
		mes "場合があります。そんな時は";
		mes "順番を守って並ぶようにしてね。";
		next;
		mes "[ボルワージュ]";
		mes "オーディションが始まると";
		mes "アナウンスが流れ、最初の立ち位置を";
		mes "基準にしてどっちの方向に移動するか";
		mes "教えます。それに合わせて動けば";
		mes "いいんです。";
		next;
		mes "[ボルワージュ]";
		mes "^0000FF指定時間内にタイミングを";
		mes "合わせることができなければ";
		mes "すぐに脱落^000000となります。";
		mes "厳しくいきますよ！";
		close;
	case 8:
		mes "[ボルワージュ]";
		mes "あら、さっきの娘ね……";
		mes "さあ、もう一度！";
		mes "リズムに乗って！";
		close2;
		warp "job_duncer.gat",104,109;
		end;
	case 9:
		mes "[ボルワージュ]";
		mes "あら、さっきの踊り、";
		mes "良かったわよ～";
		next;
		mes "[ボルワージュ]";
		mes "あれくらい踊れればダンサー";
		mes "になるのに十分ですね。";
		mes "さぁ、転職させてあげます。";
		next;
		mes "[ボルワージュ]";
		mes "汝、今……女神の加護を受け";
		next;
		mes "[ボルワージュ]";
		mes "すべての人に喜びを与える";
		mes "ダンサーになりたもう……";
		next;
		set '@itemid,(JobLevel >= 50)? 1953: 1950;
		mes "[ボルワージュ]";
		mes "これから汝が踊るたび";
		next;
		unequip;
		jobchange Job_Dancer;
		set CHANGE_DC,0;
		mes "[ボルワージュ]";
		mes "人々の微笑みがあふれんことを……";
		next;
		mes "[ボルワージュ]";
		mes "これは私からのプレゼントです。";
		mes "合格おめでとう！";
		getitem '@itemid,1;
		close;
	}
	//口頭試問ここから
	next;
	switch(rand(3)) {
	case 0:
		mes "[ボルワージュ]";
		mes "1.";
		mes "ダンサー・バード合奏スキル";
		mes "「ロキの叫び」の効果は？";
		next;
		if(select("レベル4武器の攻撃力が向上する","ダメージを二倍にしてくれる","範囲内ではスキルと魔法が使用不能になる","攻撃速度が上昇する")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "2.";
		mes "ダンスフロアでダンスをした後";
		mes "相手に対する礼儀に反する行為は？";
		next;
		if(select("相手に感謝の言葉を伝える","踊りを誉める","他のダンスも踊ろうと誘う","自分の相手には不足だと言う")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "3.";
		mes "誰かがダンスで間違った場合";
		mes "それに気づいたあなたは";
		mes "どうしますか？";
		next;
		if(select("笑顔を絶やさずダンスを続ける","間違いを指摘してあげる","気づかないふりをする","こっそり微笑んであげる")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "4.";
		mes "ダンサーに転職ができる村の名前は？";
		next;
		if(select("ココモ","サンダルマン","コムモ","コモド")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "5.";
		mes "コモドと直接繋がっている";
		mes "洞窟の数は？";
		next;
		if(select("1個","2個","3個","4個")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "6.";
		mes "次の中で、ペットできない";
		mes "モンスターは？";
		next;
		if(select("イシス","アルギオペ","ドケビ","デビルチ")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "7.";
		mes "ダンスが一番うまい人は誰か？";
		next;
		switch (select(strcharinfo(0),"ボルワージュ様","イシス","メルシー")) {
			case 1:
				set '@point,'@point-100;
				mes "…………";
				next;
				break;
			case 2:
				set '@point,'@point+10;
				break;
		}
		mes "[ボルワージュ]";
		mes "8.";
		mes "コモドにあるカプラサービスの";
		mes "拠点は何というか。";
		next;
		if(select("カプラサービス本社","カプラサービス西部地区","カプラサービス","カプラサービス西部支部")==4)
			set '@point,'@point+10;
		mes "[……]";
		mes "9.";
		mes "私の名前は何？";
		next;
		if(select("ボンソワール","ブルジョア","ボルワージュ","ボンジュール")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "10.";
		mes "スキル「子守歌」の能力は？";
		next;
		if(select("周囲に暗黒の効果","周囲に睡眠の効果","周囲に徹夜の效果","周囲に凍結の效果")==2)
			set '@point,'@point+10;
		break;
	case 1:
		mes "[ボルワージュ]";
		mes "1.";
		mes "ダンサーの「ダンスの練習」スキルの";
		mes "効果は？";
		next;
		if(select("INTを上げる","ダンススキルの効果を高める","鞭系攻撃のダメージを高める","一定範囲にスタンの効果")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "2.";
		mes "甲高い音がでる特殊な靴を履いて";
		mes "ステップを踏み、軽快なリズムを刻む";
		mes "踊りのことを何と言うか。";
		next;
		if(select("タップダンス","集中力向上","タンゴ","ダブルストレイフィング")==1)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "3.";
		mes "ダンサーの特徴から離れている";
		mes "ものを選びなさい。";
		next;
		if(select("ダンススキルを使いこなす","遠距離攻撃をする","鞭を使う","両手剣を使う")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "4.";
		mes "ダンサー達が一番多く居る街は？";
		next;
		if(select("アルデバラン","ジュノー","モロク","コモド")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "5.";
		mes "一番美しいダンスを披露する人は？";
		next;
		switch (select(strcharinfo(0),"ボルワージュ様","イシス","エメラルハンダス")) {
			case 1:
				set '@point,'@point-100;
				mes "…………";
				next;
				break;
			case 2:
				set '@point,'@point+10;
				break;
		}
		mes "[ボルワージュ]";
		mes "6.";
		mes "ダンサーが、他の職業に比べて";
		mes "秀でている点を答えなさい。";
		next;
		if(select("体力","演技力","ダンスの実力","魔法の実力")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "7.";
		mes "コモドカジノのマネージャーの名前は？";
		next;
		if(select("ルー","ムー","マーティン","ローヤー")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "8.";
		mes "ダンサーが装備できないアイテムは？";
		next;
		if(select("猫耳のヘアバンド","ツーハンドソード","サンダル","イヤリング")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "9.";
		mes "試験は退屈？";
		next;
		if(select("はい","いいえ")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "10.";
		mes "ファロス燈台島にある燈台の数は";
		mes "全部でいくつ？";
		next;
		if(select("1","2","3")==1)
			set '@point,'@point+10;
		break;
	case 2:
		mes "[ボルワージュ]";
		mes "1.";
		mes "ダンサーのダンス「幸運のキス」は";
		mes "どの能力値をあげてくれるか。";
		next;
		if(select("INT","DEX","VIT","クリティカル率")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "2.";
		mes "次の中でダンスでないものは？";
		next;
		if(select("タンゴ","タップダンス","ヒップホップ(HIP-HOP)","創作ダンス","ライトニングボルト")==5)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "3.";
		mes "次の中で、ダンサーという職を";
		mes "あらわしている言葉は？";
		next;
		if(select("大声を出す人","うるさい人","踊りを踊る人","歌を歌う人")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "4.";
		mes "次の中でコモドの特徴に";
		mes "当てはまらないものは？";
		next;
		if(select("浜辺の都市","ダンサーの転職が可能だ","いつも夜のように暗い","周囲3方向にダンジョンがある","シーフが多い")==5)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "5.";
		mes "外からコモドに来る途中にある";
		mes "ファロス燈台島から、西の方角に";
		mes "ある場所の地名を何というか。";
		next;
		if(select("エルメスプレート","コムコビーチ","ココモビーチ","ジナイ沼")==3)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "6.";
		mes "世界で一番美しい踊り娘は";
		mes "誰か？";
		next;
		switch (select(strcharinfo(0),"ボルワージュ様","エイル","ボンジュール")) {
			case 1:
				set '@point,'@point-100;
				mes "…………";
				next;
				break;
			case 2:
				set '@point,'@point+10;
				break;
		}
		mes "[ボルワージュ]";
		mes "7.";
		mes "次の中で、ダンサーと";
		mes "合唱可能な職業は？";
		next;
		if(select("アサシン","バード","アルケミスト","セージ")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "8.";
		mes "コモドの特産品でないものは？";
		next;
		if(select("バーサークポーション","貝殻","かにのこうら","光ってる石")==4)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "9.";
		mes "コモドカジノのマネージャーはだれか。";
		next;
		if(select("ローヤー","ムー","ジー・ジェイ","ルー")==2)
			set '@point,'@point+10;
		mes "[ボルワージュ]";
		mes "10.";
		mes "ダンサースクール申し込み担当者の";
		mes "名前は？";
		next;
		if(select("ボルワージュ","エイル","アッシニア","スノトラ")==2)
			set '@point,'@point+10;
		break;
	}
	mes "[ボルワージュ]";
	mes "はい、お疲れさま～";
	next;
	mes "[ボルワージュ]";
	mes "面接の結果は" +'@point+ "点……";
	if( (CHANGE_DC == 5 && '@point < 80) || (CHANGE_DC == 6 && '@point < 70) ) {
		mes "不合格。";
		mes "こんなんじゃ困るわ。";
		set CHANGE_DC,6;
		next;
		mes "[ボルワージュ]";
		mes "ちょっと難しかったかな？";
		mes "でも私の若い頃はもっとできたわよ？";
		mes "また勉強してきてね。";
		close;
	}
	if('@point < 100) {
		mes "いくつか気になる点があったけど";
		mes "まあいいでしょう。";
	}
	else
		mes "すばらしいです。合格です。";
	next;
	mes "[ボルワージュ]";
	mes "このくらいなら大丈夫ね。";
	mes "ダンスの実習はそうもいかない";
	mes "けど、努力すればなんとかなるわ。";
	set CHANGE_DC,7;
	close;
}

//==========================================
// 三次試験
//
//　　　■　　　　　４
//　　■■■　≡　５１３
//　　　■　　　　　２
//
//　　※野球の内野のポジションと同じです
//------------------------------------------

job_duncer.gat,32,152,6	script	案内要員::DC_Test	69,{
	//ダンスのステップ判定
	function Judgement {
		for(set '@i,1; '@i<=5; set '@i,'@i+1) {
			if('@i != getarg(0))
				hideoffnpc "#DC_Step"+'@i;	//指定タイル以外のハイド解除
		}
		return;
	}
	//全タイルの無効化
	function HideTile {
		hideonnpc "#DC_Step1";
		hideonnpc "#DC_Step2";
		hideonnpc "#DC_Step3";
		hideonnpc "#DC_Step4";
		hideonnpc "#DC_Step5";
		return;
	}
	//バックダンサーのエモーション
	function EmotionDancer {
		emotion 21,"DC_Dancer1";
		emotion 21,"DC_Dancer2";
		emotion 21,"DC_Dancer3";
		emotion 21,"DC_Dancer4";
		return;
	}
	end;
OnInit:
	waitingroom "ダンスレッスン待合室",20,"DC_Test::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	awake "DC_Test";
	HideTile;
	killmonster "job_duncer.gat","DC_Test::OnKilled";	//本鯖はここではkillされないけど面倒なのでkillする
	warpwaitingpc "job_duncer.gat",70,111,1;
	set 'accid,$@warpwaitingpc[0];
	initnpctimer;
	end;
OnTimer1000:
	announce "ボルワージュ: さあ、始めます。緊張を解いて。 制限時間は 1分です。",9;
	end;
OnTimer3000:
	announce "ボルワージュ:  はい、後ろへ！ : [↑]",9;
	sleep 3000;
	Judgement 4;
	end;
OnTimer7000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  前～ : [↓]",9;
	sleep 3000;
	Judgement 2;
	end;
OnTimer11000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  左～ : [←]",9;
	sleep 3000;
	Judgement 5;
	end;
OnTimer15000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  右にターン : [→]",9;
	sleep 3000;
	Judgement 3;
	end;
OnTimer19000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  真ん中に戻って : [・]",9;
	sleep 2000;
	Judgement 1;
	end;
OnTimer21000:
	EmotionDancer;
	announce "ボルワージュ:  そのままポーズ！ ",9;
	end;
OnTimer24000:
	EmotionDancer;
	announce "ボルワージュ:  ポーズの後「集中力向上」などをアドリブで入れて！ ",9;
	end;
OnTimer26000:
	announce "ボルワージュ:  そのまま～ ",9;
	end;
OnTimer27000:
	HideTile;
	announce "ボルワージュ:  左へ～ : [←]",9;
	sleep 3000;
	Judgement 5;
	end;
OnTimer31000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  前～ : [↓] ",9;
	sleep 2000;
	Judgement 2;
	end;
OnTimer34000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  すぐに右！ : [→] ",9;
	sleep 1500;
	Judgement 3;
	end;
OnTimer36000:
	EmotionDancer;
	announce "ボルワージュ:  はいポーズ！ ",9;
	end;
OnTimer39000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  左・真ん中・右・後ろ～ : [←][・][→][↑] ",9;
	sleep 5000;
	Judgement 4;
	end;
OnTimer45000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  [→] ",9;
	sleep 2000;
	Judgement 3;
	end;
OnTimer48000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  左・真ん中・前・後ろ : [←][・][↓][↑] ",9;
	sleep 5000;
	Judgement 4;
	end;
OnTimer54000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  もう一度、左・真ん中・前・後ろ : [←][・][↓][↑] ",9;
	sleep 5000;
	Judgement 4;
	end;
OnTimer60000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  前～ : [↓]",9;
	sleep 3000;
	Judgement 2;
	end;
OnTimer64000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  左 : [←] ",9;
	sleep 3000;
	Judgement 5;
	end;
OnTimer68000:
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  真ん中 : [・] ",9;
	sleep 3000;
	Judgement 1;
	end;
OnTimer72000:
	if(getareausers("job_duncer.gat",65,109,73,111) + getareausers("job_duncer.gat",68,106,70,114) > 0) {
		if(attachrid('accid))
			set CHANGE_DC,9;	//AS関係なくこの時点でクリア確定
	}
	EmotionDancer;
	HideTile;
	announce "ボルワージュ:  アローシャワーで決め！ ",9;
	monster "job_duncer.gat",69,106,"ダンスポリン",1002,1,"DC_Test::OnKilled";
	end;
OnKilled:
	stopnpctimer;
	announce "dance: ナイスショーット！",9;
	sleep 5000;
	announce "dance: お上手でした！ボルワージュ先生にアピールできたでしょう～",9;
	//fall through
OnTimer78000:
	stopnpctimer;
	killmonster "job_duncer.gat","DC_Test::OnKilled";
	areawarp "job_duncer.gat",65,109,73,111,"comodo.gat",188,162;	//タイル5,1,3の範囲
	areawarp "job_duncer.gat",68,106,70,114,"comodo.gat",188,162;	//タイル2,1,4の範囲
	enablewaitingroomevent;
	end;
}

//==============================================================
job_duncer.gat,69,110,4	script	#DC_Step1	139,1,1,{
	end;
OnTouch:
	announce "dance: " +strcharinfo(0)+ "さん～ タイミングが遅れました！",9;
	areawarp "job_duncer.gat",65,109,73,111,"comodo.gat",188,162;
	areawarp "job_duncer.gat",68,106,70,114,"comodo.gat",188,162;
	emotion 23,"DC_Dancer1";
	emotion 23,"DC_Dancer2";
	emotion 23,"DC_Dancer3";
	emotion 23,"DC_Dancer4";
	enablewaitingroomevent "DC_Test";	//タイマーは停止せずにチャットだけ有効化される本鯖仕様
	end;
OnInit:
	hideonnpc;
	end;
}

job_duncer.gat,69,107,4	duplicate(#DC_Step1)	#DC_Step2	139,1,1
job_duncer.gat,72,110,4	duplicate(#DC_Step1)	#DC_Step3	139,1,1
job_duncer.gat,69,113,4	duplicate(#DC_Step1)	#DC_Step4	139,1,1
job_duncer.gat,66,110,4	duplicate(#DC_Step1)	#DC_Step5	139,1,1

//==============================================================
job_duncer.gat,69,110,4	script	#DC_Dummy1	101,{	//セルに乗れないようにするためだけのダミーNPC
	end;
OnInit:
	hideonnpc;
	end;
}

job_duncer.gat,69,107,4	duplicate(#DC_Dummy1)	#DC_Dummy2	101
job_duncer.gat,72,110,4	duplicate(#DC_Dummy1)	#DC_Dummy3	101
job_duncer.gat,69,113,4	duplicate(#DC_Dummy1)	#DC_Dummy4	101
job_duncer.gat,66,110,4	duplicate(#DC_Dummy1)	#DC_Dummy5	101

//==============================================================
job_duncer.gat,63,110,4	script	バックダンサー::DC_Dancer1	724,{}
job_duncer.gat,66,113,4	script	バックダンサー::DC_Dancer2	724,{}
job_duncer.gat,72,113,4	script	バックダンサー::DC_Dancer3	724,{}
job_duncer.gat,75,110,4	script	バックダンサー::DC_Dancer4	724,{}
