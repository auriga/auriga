//====================================================================
//Ragnarok Online Hunter jobchange script
//
//　■ CHANGE_HT
//	1	シェリンの質問
//	2	シェリンの質問クリア
//	3	アイテム収集１
//	4	アイテム収集２
//	5	アイテム収集３
//	6	アイテム収集４
//	7	アイテム収集５
//	8	アイテム収集６
//	9	アイテム収集７
//	10	ギルドマスター弓手村
//	11	ギルドマスター中央宮
//	12	戦闘試験
//	13	戦闘試験中
//	14	戦闘試験クリア
//	15	慧眼入手-試験クリア
//
//　■ $@ht_tester$ -> 戦闘試験挑戦中のキャラ名
//====================================================================

//==========================================
// 試験申請および転職
//------------------------------------------

//pay_fild10.gat,148,252,4	script	ハンターギルド関係者	98,{
//	mes "[ハンターギルド員]";
//	mes "こんにちは。";
//	mes "ハンターギルドへご用でしたら";
//	mes "私がご案内します。";
//	next;
//	if(select("連れて行ってください","特に用はありません")==2) {
//		mes "[ハンターギルド員]";
//		mes "それではまた。";
//		close;
//	}
//	mes "[ハンターギルド員]";
//	mes "はい、それではご案内します。";
//	close2;
//	warp "in_hunter.gat",100,18;
//	end;
//}

pay_fild10.gat,148,252,3	script	案内板	837,{
	mes "==============案内==============";
	mes "ハンター転職所は";
	mes "シュバルツバルド共和国の";
	mes "^FF0000フィゲル^000000に移動しました。";
	next;
	mes "フィゲル路線が新たに開通したので、";
	mes "飛行船を利用して";
	mes "フィゲルに移動することができます。";
	next;
	mes "転職試験を受ける方々は";
	mes "^FF0000フィゲル^000000の^FF0000右上^000000に";
	mes "移転した転職所まで来てください。";
	next;
	mes "^844200（一番下にも何か書いてある）^000000";
	mes "……ファルコン管理者も一緒に行った。";
	close;
}

//==============================================================
//in_hunter.gat,99,99,4	script	ハンターギルド員	727,{
hu_in01.gat,386,373,4	script	ハンターギルド員	727,{
	if(Upper == UPPER_HIGH) {
		mes "[ハンター・シェリン]";
		mes "あら、こんにちは！";
		mes "元気でしたか？";
		mes "以前お会いしてからだいぶ";
		mes "経ちますよね……";
		next;
		mes "[ハンター・シェリン]";
		mes "あら……？";
		mes "ごめんなさい、人違いだったかしら？";
		next;
		mes "[ハンター・シェリン]";
		mes "……";
		mes "どこかでお会いしたような……";
		next;
		mes "[ハンター・シェリン]";
		mes "う～ん、思い出せないですね。";
		mes "私が人を間違えるのって";
		mes "とてもめずらしいんですけど……";
		mes "とにかく、良い一日を過ごして";
		mes "くださいね。";
		close;
	}
	if(Job == Job_Novice) {
		mes "[ハンターギルド員]";
		mes "あら、ノービスさん…";
		mes "この辺ではあまり見かけませんねぇ…。";
		close;
	}
	if(Job == Job_Hunter) {
		mes "[ハンターギルド員]";
		mes "あ、" +strcharinfo(0)+ "さん！";
		mes "お久しぶりです～。";
		mes "今日はどんなご用ですか？";
		mes "ギルドからはこれといった告知は";
		mes "出ていませんが、どうぞゆっくり";
		mes "なさっていってください。";
		close;
	}
	if(Job != Job_Archer) {
		mes "[ハンターギルド員]";
		mes "あら、いらっしゃいませ！";
		mes "嬉しいですね～。";
		mes "こちらまで訪ねて来られる方が";
		mes "めっきり少なくなりまして…。";
		close;
	}
	switch(CHANGE_HT) {
	case 0:
		if(JobLevel < 40) {
			mes "[ハンターギルド員]";
			mes "あ…まだ弓の扱いが十分では";
			mes "ありませんね…。";
			mes "少なくとも、ハンターになるには";
			mes "アーチャーとしての修練をある水準まで";
			mes "積まなければなりません。";
			next;
			mes "[ハンターギルド員]";
			mes "もうすこし修練を積んできてください。";
			mes "正確な転職条件は、";
			mes "JobLv40以上です。";
			mes "もちろんそれ以上修練してくださっても";
			mes "問題ないですよ。";
			mes "それでは次にお会いする時を楽しみに";
			mes "しております。";
			close;
		}
		if(SkillPoint) {
			mes "[ハンター・シェリン]";
			mes "スキルポイントが残っていると転職";
			mes "できません。全て消費されてから";
			mes "おこしください。";
			close;
		}
		mes "[ハンターギルド員]";
		mes "あら、アーチャーさんですね。";
		mes "見たところ、相当な訓練をされて";
		mes "きましたね。";
		mes "そして、ハンターへの転職をご希望で";
		mes "訪ねていらしたのですね？";
		next;
		switch(select("はい、そのために来ました","転職条件を伺いに来ました","まだ転職しません")) {
			case 1:
				mes "[ハンターギルド員]";
				mes "へへ、当たりですね～。";
				mes "それでは手続きを…と…";
				next;
				mes "[ハンターギルド員]";
				mes "まず、最初に面接をします。";
				mes "楽な気持ちで答えてくださいね。";
				next;
				mes "ごそごそ…";
				next;
				mes "[ハンターギルド員]";
				mes "あっ、";
				mes "申し遅れました。";
				mes "私は「シェリン」と言います。";
				mes "お会いできて嬉しいです！";
				next;
				mes "[ハンター・シェリン]";
				mes "はい、それでは面接を始めます～";
				next;
				if(select("おねがいします","用事の途中なのでまた来ます")==2) {
					mes "[ハンター・シェリン]";
					mes "それでは、またいつでもいらっしゃって";
					mes "くださいね。";
					close;
				}
				mes "[ハンター・シェリン]";
				mes "では、私がお話をし、時たま質問を";
				mes "投げ掛けます。";
				mes "それに答えてくだされば良いです。";
				next;
				mes "[ハンター・シェリン]";
				mes "どんな考えをお持ちでハンターを";
				mes "希望したか知るためですから、気を楽に";
				mes "して答えてくださいね。";
				set CHANGE_HT,1;
				break;
			case 2:
				mes "[ハンターギルド員]";
				mes "転職条件です。";
				mes "一．アーチャーであること";
				mes "二．JobLvが40以上であること";
				mes "三．ギルドから要求された";
				mes "　　アイテムを集めてくること";
				mes "四．ギルドで行う試験に合格すること";
				next;
				mes "[ハンターギルド員]";
				mes "アーチャーでしっかりと修練を積んでいたら";
				mes "試験には合格できるはずです。";
				close;
			case 3:
				mes "[ハンターギルド員]";
				mes "それでは、またいつでもいらっしゃって";
				mes "くださいね。";
				close;
		}
		break;
	case 1:
		mes "[ハンター・シェリン]";
		mes "またいらっしゃいましたね！";
		mes "では面接から始めますよ～";
		mes "今度はシェリンの問いに";
		mes "しっかり答えてくださいね！";
		break;
	case 2:
		mes "[ハンター・シェリン]";
		mes "あら？";
		next;
		mes "[ハンター・シェリン]";
		mes "デーモンハンター様をまだ見つけ";
		mes "られないんですか？";
		mes "デーモンハンター様は向かって";
		mes "左側にいらっしゃいますよ。";
		next;
		mes "[ハンター・シェリン]";
		mes "早く転職した姿がみたいですね～";
		mes "素敵なハンターになりそうですから。";
		close;
	default:	//3～9のとき
		mes "[ハンター・シェリン]";
		mes "あちらにいらっしゃる";
		mes "デーモンハンター様の元に";
		mes "アイテムを揃えて持っていけば";
		mes "良いんです。";
		next;
		mes "[ハンター・シェリン]";
		mes "ハンターになるときは、必ずシェリンの";
		mes "所に来てくださいね。";
		mes "あなたはとても" +(Sex? "格好良い": "綺麗だ")+ "から、";
		mes "ハンターになった姿も絶対に";
		mes "見たいんです。ふふ…";
		close;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		mes "[ハンター・シェリン]";
		mes "うーん…私ではなく、他へ出張に";
		mes "出てらっしゃるギルドマスター様";
		mes "にご用ですか？";
		next;
		mes "[ハンター・シェリン]";
		mes "私が聞くところによると、";
		mes "フェイヨン中央宮か弓手村のどちらかに";
		mes "いらっしゃるはずです。";
		mes "そちらへ行ってみてくださいね。";
		close;
	case 15:
		if(countitem(1007) < 1) {
			mes "[ハンター・シェリン]";
			mes "はい、試験に合格されたという連絡を";
			mes "受けておりますが、印である「慧眼」";
			mes "をお持ちでないですね。";
			next;
			mes "[ハンター・シェリン]";
			mes "お無くしになったことは";
			mes "ギルドマスターには内緒にしておき";
			mes "ますから、とにかく「慧眼」を";
			mes "見つけてきてくださいね。";
			close;
		}
		if(Skillpoint) {
			mes "[ハンター・シェリン]";
			mes "スキルポイントが残っていると転職";
			mes "できません。全て消費されてから";
			mes "おこしください。";
			close;
		}
		set '@itemid,(JobLevel >= 50)? 1718: 1710;
		mes "[ハンター・シェリン]";
		mes "あ、転職試験に合格されましたね！";
		mes "お祝い申し上げます！";
		next;
		mes "[ハンター・シェリン]";
		mes "さぁ、それでは早速ハンターへ";
		mes "転職させてさしあげます。";
		next;
		delitem 1007,1;
		unequip;
		jobchange Job_Hunter;
		set CHANGE_HT,0;
		mes "[ハンター・シェリン]";
		mes "改めてお祝いいたします。";	
		mes "うん、ハンターの服装もよく似合って";
		mes "らっしゃいますね！";
		next;
		mes "[ハンター・シェリン]";
		mes "ハンターとして恥ずかしくない行動を";
		mes "取ると共に、自然を愛する心を忘れ";
		mes "ないでくださいね！";
		next;
		getitem '@itemid,1;
		mes "[ハンター・シェリン]";
		mes "そして、これはあなたの努力に";
		mes "敬意を表して差し上げるものです。";
		close;
	}
	//面接ここから
	next;
	mes "[ハンター・シェリン]";
	mes "ではいきます。";
	next;
	mes "[ハンター・シェリン]";
	mes "あなたはアーチャー。どこかに狩りへ";
	mes "出かけたいのですが、どこに行ったら";
	mes "良いか分かりません。";
	mes "さて、どうしましょう。";
	next;
	if(select("どこが良いかと叫んで歩き回る","通りかかった人に声をかけて聞く","一人であちこち回って探す")==2)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "狩場を決めました。";
	mes "ソグラト砂漠に生息する「ホード」と";
	mes "いうモンスターを狩ることにしました。";
	next;
	mes "[ハンター・シェリン]";
	mes "しかしここはフェイヨン。";
	mes "どうやって砂漠まで行きましょうか。";
	next;
	if(select("プリースト様に頼んで転送してもらう","カプラ職員を利用する","友達と歩いて行く")==3)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "近くにプリースト様も友達も居ません。";
	mes "カプラ職員を利用することにしましたが";
	mes "お金が足りません。どうしましょう。";
	next;
	if(select("物乞いする","必要の無いアイテムを売ってお金にする","近くの森で狩りをする")==2)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "なんとかホードのいる砂漠に到着";
	mes "しました。";
	mes "ところがホードを狩るには少し";
	mes "自分の腕が足りなかったようです…。";
	next;
	mes "[ハンター・シェリン]";
	mes "どうしますか？";
	next;
	if(select("丘の上から下にいるホードを攻撃します","街に向かいます","人が戦っているホードを攻撃する")==2)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "狩りをやめ、街に帰ってきました。";
	next;
	mes "[ハンター・シェリン]";
	mes "気がつくと体力が底を尽きかけて";
	mes "いました。回復の依頼をしますが";
	mes "どのように頼みますか？";
	next;
	if(select("よろしければヒールをお願いできますか？","ヒールください","ヒールくれ")==1)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "ん？狩りをしていたらいつの間にか";
	mes "珍しいアイテムを手に入れて";
	mes "ました。早速、品物を売りに広場に";
	mes "出ましたが、多くの露店やチャット";
	mes "ルームが開かれています。";
	next;
	mes "[ハンター・シェリン]";
	mes "そんな場合、アイテムを売るには";
	mes "どうするのが一番良いでしょうか？";
	next;
	if(select("皆に聞こえるように知らせながら歩く","チャットルームを開いて待つ","求めている人がいるか探してみる")==3)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "そうして待っていると、物乞いを";
	mes "する人が現れました。";
	mes "どう対応しますか？";
	next;
	if(select("自分のお金とアイテムを差し出す","無視して歩き去る","その人に適した狩場を教えてあげる")==3)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "今度は迷宮の森へ出かけました。";
	next;
	mes "[ハンター・シェリン]";
	mes "そこで道に迷った人に会いました。";
	mes "どうすればよいでしょうか。";
	next;
	if(select("道を教えてあげる","目的地まで案内してあげる","無視する")==2)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "その人の道案内をしながら狩りを";
	mes "続けましたが、その途中で誰かが";
	mes "ました。早速、品物を売りに広場に";
	mes "ボスモンスターと戦闘しています。";
	next;
	mes "[ハンター・シェリン]";
	mes "どうすれば良いでしょうか。";
	next;
	if(select("助けて欲しいと要請があったら支援する","とにかく攻撃する","そのまま街に帰る")==1)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "もう相当、旅の疲れが出てきました。";
	mes "街へ帰ろうと思います。";
	next;
	mes "[ハンター・シェリン]";
	mes "そんな時、道に珍しいアイテムが";
	mes "落ちています。";
	mes "どのようにしますか？";
	next;
	if(select("拾って自分で持ち帰る","誰の物か探してみる","通り過ぎる")==2)
		set '@point,'@point+10;
	mes "[ハンター・シェリン]";
	mes "はい、お疲れ様でした～。";
	mes "質問は以上となります。";
	next;
	if('@point < 50) {
		mes "[ハンター・シェリン]";
		mes "うーん…ちょっと難しいです…";
		mes "基本的な心構えができていなければ";
		mes "ハンターになっていただくことが";
		mes "できません。";
		next;
		mes "[ハンター・シェリン]";
		mes "私の質問がどんなだったか、";
		mes "よく思い出してもう一度考えてみて";
		mes "ください。";
		mes "自然に対する心を見るのに、人との";
		mes "接し方は非常に参考になるんです。";
		close;
	}
	set CHANGE_HT,2;
	if('@point == 100) {
		mes "[ハンター・シェリン]";
		mes "良いですね、その心構えで";
		mes "転職試験に臨んでください。";
		mes "十分にハンターになる素質があります。";
		next;
		mes "[ハンター・シェリン]";
		mes "これで面接は終わります。";
		mes "あちらの隅にいる方に、転職に必要な";
		mes "アイテムを教わってください。";
		close;
	}
	mes "[ハンター・シェリン]";
	mes "多少気にかかる部分がありましたが、";
	mes "面接の方はこれで終わります。";
	mes "後でもう一度、今の質問を思い出して";
	mes "よく考えてみてください。";
	next;
	mes "[ハンター・シェリン]";
	mes "残った試験も是非頑張って、";
	mes "シェリンに良い結果を聞かせて";
	mes "くださいね。";
	close;
}


//==========================================
// 一次試験（アイテム収集）
//------------------------------------------

//in_hunter.gat,55,99,4	script	ハンターギルド試験受付	732,{
hu_in01.gat,382,382,4	script	ハンターギルド試験受付	732,{
	switch(CHANGE_HT) {
	case 0:
	case 1:
		mes "[デーモンハンター]";
		mes "ハンターへの転職試験を受けたければ";
		mes "まず受付を済ませてください。";
		close;
	case 2:
		mes "[ハンターギルド試験受付員]";
		mes "よく来ました。私はハンターギルド";
		mes "試験受付員「デーモンハンター」";
		mes "と言います。";
		mes "お名前は " +strcharinfo(0);
		mes "さんですね？";
		next;
		if(select("はい、そうです","違います(フフ…)")==2) {
			mes "[デーモンハンター]";
			mes "ふざけないでください…。";
			mes strcharinfo(0)+ "さんでしょ？";
			next;
			if(select("う…すいません","あはは")==2) {
				mes "[デーモンハンター]";
				mes "冷やかしに来たのなら出て行き";
				mes "なさい！敬意を込めてお話を";
				mes "しているのにそんな態度をするとは！";
				close2;
				//warp "pay_fild10.gat",133,235;
				warp "hugel.gat",208,223;
				end;
			}
		}
		mes "[デーモンハンター]";
		mes "はい、それでは転職試験に必要な";
		mes "物をお知らせします。";
		mes "弓矢の材料になるものを集めてきて";
		mes "ください。私共も財政不足でして…";
		mes "えっと…今不足している物は…";
		next;
		switch(rand(7)) {
			case 0:
				mes "[デーモンハンター]";
				mes "矢先に使われる";
				mes "「こうもりの牙」3個";
				mes "あちこちに接着剤として使われる";
				mes "「べとべとする液体」1個";
				mes "そして…「くまの足の裏」1個。";
				mes "以上となります。";
				set CHANGE_HT,3;
				break;
			case 1:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「サルのしっぽ」1個";
				mes "「ハリネズミの針」2個";
				mes "そして…「どんぐり」1個。";
				mes "以上となります。";
				set CHANGE_HT,4;
				break;
			case 2:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「ドケビの角」3個";
				mes "「割れた卵のかけら」3個";
				mes "そして…「綿毛」10個。";
				mes "以上となります。";
				set CHANGE_HT,5;
				break;
			case 3:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「鳥のくちばし」3個";
				mes "「スケルボーン」5個";
				mes "そして…「緑ハーブ」3個。";
				mes "以上となります。";
				set CHANGE_HT,6;
				break;
			case 4:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「白ハーブ」3個";
				mes "「木屑」5個";
				mes "そして…「砂漠狼の爪」5個。";
				mes "以上となります。";
				set CHANGE_HT,7;
				break;
			case 5:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「黄ハーブ」9個";
				mes "「蟲の皮」9個";
				mes "そして…「かたい皮」9個。";
				mes "以上となります。";
				set CHANGE_HT,8;
				break;
			case 6:		//メッセージ未調査
				mes "[デーモンハンター]";
				mes "「毒の牙」3個";
				mes "「獣の皮」3個";
				mes "そして…「赤ハーブ」5個。";
				mes "以上となります。";
				set CHANGE_HT,9;
				break;
		}
		next;
		mes "[デーモンハンター]";
		mes "あと、フェイヨンの方に出張に";
		mes "行かれているギルドマスター様が";
		mes "試験を取り仕切られていますから、";
		mes "一度お会いください。";
		mes "それでは、全て揃えてからまた";
		mes "きてください。";
		close;
	default:	//3～9のとき
		mes "[デーモンハンター]";
		mes "えーと…";
		next;
		switch(CHANGE_HT) {
			case 3:
				setarray '@need,913,938,948;
				setarray '@amount,3,1,1;
				break;
			case 4:
				setarray '@need,942,1027,1026;
				setarray '@amount,1,2,1;
				break;
			case 5:
				setarray '@need,1021,7032,914;
				setarray '@amount,3,3,10;
				break;
			case 6:
				setarray '@need,925,932,511;
				setarray '@amount,3,5,3;
				break;
			case 7:
				setarray '@need,509,1019,7030;
				setarray '@amount,3,5,5;
				break;
			case 8:
				setarray '@need,508,955,935;
				setarray '@amount,9,9,9;
				break;
			case 9:
				setarray '@need,937,919,507;
				setarray '@amount,3,3,5;
				break;
		}
		for(set '@i,0; '@i<3; set '@i,'@i+1) {	//必要アイテムチェック
			if(countitem('@need['@i]) < '@amount['@i]) {
				mes "[デーモンハンター]";
				mes "まだ準備ができていないようですね。";
				mes "必要な物は…";
				for(set '@i,0; '@i<3; set '@i,'@i+1)
					mes "「" +getitemname('@need['@i])+ "」" +'@amount['@i]+ "個";
				mes "です。全て揃えて来てください。";
				close;
			}
		}
		mes "[デーモンハンター]";
		mes "うん、私が言った物を全て";
		mes "集めてくれましたね！";
		mes "あとはフェイヨンの方へ出張中の";
		mes "ギルドマスター様にお会いすれば";
		mes "次の試験に案内してくれるでしょう。";
		for(set '@i,0; '@i<3; set '@i,'@i+1)
			delitem '@need['@i],'@amount['@i];
		set CHANGE_HT,10+rand(2);
		close;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		mes "[デーモンハンター]";
		mes "ギルドマスター様がフェイヨン中央宮か";
		mes "弓手村に行ったのは確かです。";
		mes "少し探してみてくださいー。";
		close;
	case 15:
		mes "[デーモンハンター]";
		mes "おお、試験に合格しましたか！";
		mes "シェリンのところへ行ってあげて";
		mes "ください。";
		close;
	}
}


//==========================================
// 二次試験（戦闘試験）
//------------------------------------------

-	script	ハンターギルドマスター	-1,{
	cutin "job_huntermaster",2;
	switch(CHANGE_HT) {
	case 0:
	case 1:
	case 2:
		mes "[ハンター]";
		mes "どんな用事ですか？";
		mes "私は出張に来ているので忙しいんです。";
		mes "どうか構わないでください。";
		close2;
		cutin "job_huntermaster",255;
		end;
	default:	//3～9のとき
		mes "[ハンターギルドマスター]";
		mes "うん？アーチャーさんが";
		mes "どんな用で来ましたか？";
		mes "特にハンターギルドからは連絡を受けて";
		mes "ませんが、中間過程を省略して試験を";
		mes "受けに来たわけではありませんよね？";
		next;
		mes "[ハンターギルドマスター]";
		mes "まず、転職試験に必要なアイテムを";
		mes "集め、ハンターギルドに納めてから";
		mes "こちらに来てください。";
		close2;
		cutin "job_huntermaster",255;
		end;
	case 10:
	case 11:
		set '@num,strnpcinfo(2);
		if(CHANGE_HT != '@num) {	//指定のマスターと合致しないとき
			mes "[ハンター]";
			mes "うん？";
			mes "転職をご希望ならハンターギルドの";
			mes "方で申し込みを済ませて来てください。";
			close2;
			cutin "job_huntermaster",255;
			end;
		}
		mes "[ハンターギルドマスター]";
		mes "うん…？転職試験ですか。";
		mes "それでは試験の内容を申し上げます。";
		mes "知りたい項目をあげてください。";
		break;
	case 12:
	case 13:
		mes "[ハンターギルドマスター]";
		mes "うん？以前に転職試験を受けた方";
		mes "ですね？";
		mes "準備ができたら試験を開始します。";
		mes "聞きたいことがあればどうぞ。";
		break;
	case 14:
		mes "[ハンターギルドマスター]";
		mes "うん、無事に終えて戻ってきましたね。";
		mes "それでは、試験を終えた印を渡します。";
		mes "ハンターギルドの方へ戻ってください。";
		mes "私はもう少しここですることが残って";
		mes "いますから…";
		next;
		mes "[ハンターギルドマスター]";
		mes "さあ、これです。";
		mes "それではこれで…";
		getitem 1007,1;
		set CHANGE_HT,15;
		close2;
		cutin "job_huntermaster",255;
		end;
	case 15:
		mes "[ハンターギルドマスター]";
		mes "早くハンターになりたいでしょう？";
		mes "私もハンターになる時、一目散に";
		mes "走って行きました。";
		next;
		mes "[ハンターギルドマスター]";
		mes "早くハンターギルドに帰ってみなさいー。";
		close2;
		cutin "job_huntermaster",255;
		end;
	}
	//戦闘試験ここから
	while(1) {
		next;
		switch (select("試験の内容","試験の合格条件","注意事項","試験を始める")) {
		case 1:
			mes "[ハンターギルドマスター]";
			mes "あちこちにある落とし穴を避け、";
			mes "ある決められたモンスターだけを";
			mes "狩るのが試験の内容です。";
			next;
			mes "[ハンターギルドマスター]";
			mes "ハンターになるために一番重要な";
			mes "目標識別能力と、素早さを試す";
			mes "ためのものです。";
			continue;
		case 2:
			mes "[ハンターギルドマスター]";
			mes "MAPの6時方向から始まり、";
			mes "制限時間内に目標モンスターを";
			mes "狩ると、";
			next;
			mes "[ハンターギルドマスター]";
			mes "マップの中央に脱出用スイッチが";
			mes "出現するので、それを押して";
			mes "12時方向に脱出すればクリア。";
			continue;
		case 3:
			mes "[ハンターギルドマスター]";
			mes "注意事項ですか…";
			mes "当たり前のことですが、";
			mes "落とし穴に落ちるとまた最初から";
			mes "始めなければなりません。";
			next;
			mes "[ハンターギルドマスター]";
			mes "一度に一人ずつ試験を受けることに";
			mes "なります。";
			mes "私が試験場の方に送ると、控え室が";
			mes "見えるはずですから、もし前の人が";
			mes "試験中でしたらチャットルームで";
			mes "待機していてください。";
			next;
			mes "[ハンターギルドマスター]";
			mes "前の人が脱落するか、クリアすれば";
			mes "チャットルームで待機中の人から";
			mes "順番に入ることができます。";
			mes "また、試験中の人が居なければ、";
			mes "すぐに開始できます。";
			continue;
		}
		break;
	}
	if(CHANGE_HT <= 11) {
		mes "[ハンターギルドマスター]";
		mes "わかりました。今すぐに送って";
		mes "あげましょう。説明の通りやれば";
		mes "大丈夫のはずです。";
		next;
		mes "[ハンターギルドマスター]";
		mes "あと、ギルド物資のために";
		mes "持ってきていただいた材料から";
		mes "矢を作りましたので、これを持って";
		mes "転職試験に臨んでください。";
		getitem 1751,200;
		set CHANGE_HT,12;
		next;
		mes "[ハンターギルドマスター]";
		mes "それでは健闘を祈ります。";
	}
	else {
		mes "[ハンターギルドマスター]";
		mes "わかりました。";
		mes "すぐに送ってあげます。";
		next;
		mes "[ハンターギルドマスター]";
		mes "うん…？銀の矢は前に渡しました。";
		mes "二度目は差し上げられません。";
		mes "では、始めましょうか。";
		next;
		if(select("いきます","ちょっと待ってください。")==2) {
			mes "[ハンターギルドマスター]";
			mes "準備を整えてまたいらっしゃい。";
			close2;
			cutin "job_huntermaster",255;
			end;
		}
		mes "[ハンターギルドマスター]";
		mes "よし！今度は合格してくださいね！";
	}
	close2;
	cutin "job_huntermaster",255;
	savepoint "job_hunte.gat",176,22;
	warp "SavePoint",0,0;
	end;
}

payon_in02.gat,21,31,3	duplicate(ハンターギルドマスター)	ハンター#10	59
payon_in03.gat,131,7,3	duplicate(ハンターギルドマスター)	ハンター#11	59

//==============================================================================
job_hunte.gat,178,32,4	script	案内員	107,5,2,{
OnTouch:
	if(CHANGE_HT != 13) {
		mes "[案内員]";
		mes "ハンター転職試験場へようこそ。";
		next;
		mes "[案内員]";
		mes "私のそばにある控え室に入れば";
		mes "まもなく試験が始まる。";
		next;
		mes "[案内員]";
		mes "開始位置から移動しつつ、";
		mes "「転職試験用モンスター」という名前の";
		mes "標的を４つ以上倒せば、MAP中央に";
		mes "あるスイッチが押せるようになる。";
		next;
		mes "[案内員]";
		mes "スイッチを押せば、MAP12時方向の";
		mes "出口より脱出することができる。";
		mes "制限時間内に目的を完遂し脱出";
		mes "してくれ。";
		next;
		mes "[案内員]";
		mes "戦闘不能に陥ったり、落とし穴に";
		mes "落ちたり、制限時間を超過した場合は";
		mes "失格となり再度試験を受けなければ";
		mes "ならない。";
		next;
		mes "[案内員]";
		mes "矢はギルドより支給されているはず。";
		mes "だから、弓のみ用意してくれれば";
		mes "良いだろう。";
		mes "では、用意ができたら控え室へ";
		mes "入室してくれ。";
		close;
	}
	percentheal 100,100;
	mes "[案内員]";
	mes "失敗したか…";
	mes "HPとSPを回復してやろう。";
	mes "無理そうなら出直すことも";
	mes "可能だがどうする？";
	next;
	if(select("まだまだ挑戦","一旦あきらめる")==1) {
		mes "[案内員]";
		mes "よし、頑張って立派なハンターに";
		mes "なってほしい。";
		mes "では控え室へ。";
		mes "先に入った人間が居れば";
		mes "そいつの試験が終わるまで";
		mes "そのまま待機していろ。";
		close;
	}
	announce "案内員: " +strcharinfo(0)+ "様の試験を中断、次の方入ってください",9;
	mes "[案内員]";
	mes "ではフェイヨンに送ってやる。";
	mes "またな。";
	close2;
	set CHANGE_HT,12;
	savepoint "payon.gat",104,99;
	warp "SavePoint",0,0;
	end;
}

//==============================================================================
job_hunte.gat,176,38,4	script	ハンター転職控え室::HT_ChatRoom	66,{
	end;
OnInit:
	waitingroom "転職試験場控室",10,"HT_ChatRoom::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		set $@ht_tester$,strcharinfo(0);	//挑戦者の名前
		set CHANGE_HT,13;
		donpcevent "HT_Center::OnStart";
		warp "job_hunte.gat",90,68;
	}
	else
		enablewaitingroomevent;
	end;
}

//==============================================================================
job_hunte.gat,0,0,0	script	HT_Center	-1,{
	end;
OnStart:
	set 'count,4;
	hideonnpc "スイッチ#HT_Test";
	hideonnpc "脱出口#HT_Test";
	monster "job_hunte.gat",54,73,"転職試験用モンスター",1041,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",54,73,"転職試験モンスター",1002,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",54,73,"モンスターサンプル",1002,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",54,73,"ハンター転職用見本",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",54,106,"転職試験モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",54,106,"ハンター試験用見本",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",54,106,"いじめないでください",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",68,80,"転職試験用モンスター",1015,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",68,80,"ハンター転職用モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",72,103,"転職実験用モンスター",1041,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",72,103,"転職試験管モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",72,103,"殴らないでください",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",78,110,"転職試験モンスター",1016,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",78,110,"転職実験用モンスター",1016,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",78,110,"ハンター転職用見本",1016,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",79,94,"転職試験用モンスター",1015,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",79,94,"ハンター転職用モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",83,112,"転職試験管モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",83,112,"いかしてください",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",89,129,"転職試験用モンスター",1002,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",89,129,"転職実験用モンスター",1002,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",90,91,"転職試験モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",90,91,"アノリアン",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",90,91,"転職試験管モンスター",1041,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",90,92,"転職試験用モンスター",1015,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",93,101,"転職試験管モンスター",1002,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",108,102,"転職試験管モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",108,102,"転職実験用モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",108,102,"殺さないでください",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",114,78,"転職試験用モンスター",1015,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",115,139,"ダイム",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",115,139,"フィリップアンゼルモ",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",115,139,"フォール",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",115,139,"レックス",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",125,69,"転職試験用モンスター",1016,1,"HT_Center::OnKillOK";
	monster "job_hunte.gat",125,69,"転職試験モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",125,69,"転職実験用モンスター",1015,1,"HT_Center::OnKillNG";
	monster "job_hunte.gat",125,69,"ハンター転職用見本",1015,1,"HT_Center::OnKillNG";
	initnpctimer;
	end;
OnKillOK:
	set 'count,'count-1;
	if('count) {
		announce "試験監督: まだだ、頑張れ！",9;
		end;
	}
	announce "試験監督: よし、良くやった。落とし穴に気をつけ、MAP中央部のスイッチを探せ",9;
	killmonster "job_hunte.gat","All";
	hideoffnpc "スイッチ#HT_Test";
	end;
OnKillNG:
	stopnpctimer;
	announce "試験監督:  " +$@ht_tester$+ "さん、間違えましたね。また挑戦してください",9;
	areawarp "job_hunte.gat",50,64,129,143,"job_hunte.gat",176,22;
	killmonster "job_hunte.gat","All";
	enablewaitingroomevent "HT_ChatRoom";
	end;
OnTimer1000:
	announce "試験監督: それでは転職試験を始めます",9;
	end;
OnTimer3000:
	announce "試験監督: 「転職試験用モンスター」だけを選んで倒してください",9;
	end;
OnTimer5000:
	announce "試験監督: 脱出用スイッチを操作すれば、MAP12時方向の出口が開かれます",9;
	end;
OnTimer7000:
	announce "試験監督: 脱出までの制限時間は3分です",9;
	end;
OnTimer9000:
	announce "試験監督: 1分経過ごとにお知らせします。それではスタート！",9;
	end;
OnTimer11000:
	announce "試験監督:  ******残り 3 分 ******",9;
	end;
OnTimer71000:
	announce "試験監督:  ******残り 2 分 ******",9;
	end;
OnTimer131000:
	announce "試験監督:  ******残り 1 分 ******",9;
	end;
OnTimer161000:
	announce "試験監督:  ******残り 30 秒 ******",9;
	end;
OnTimer186000:
	announce "試験監督:  試験終了 5 秒前. . . . .",9;
	end;
OnTimer187000:
	announce "試験監督:  試験終了 4 秒前. . . .",9;
	end;
OnTimer188000:
	announce "試験監督:  試験終了 3 秒前. . .",9;
	end;
OnTimer189000:
	announce "試験監督:  試験終了 2 秒前. .",9;
	end;
OnTimer190000:
	announce "試験監督:  試験終了 1 秒前.",9;
	end;
OnTimer191000:
	announce "試験監督:  0",9;
	end;
OnTimer192000:
	announce "試験監督:  制限時間を過ぎました。次の挑戦をお待ちしています",9;
	areawarp "job_hunte.gat",50,64,129,143,"job_hunte.gat",176,22;
	end;
OnTimer195000:
	stopnpctimer;
	killmonster "job_hunte.gat","All";
	enablewaitingroomevent "HT_ChatRoom";
	end;
}

//==============================================================================
job_hunte.gat,93,101,0		script	スイッチ#HT_Test	723,1,1,{
OnTouch:
	mes "脱出用スイッチがあり、";
	mes "ボタンが三つ見える。";
	next;
	switch (select("脱出","取り消し","再試験")) {
	case 1:
		mes "脱出口が開きました";
		announce "switch:  ## 脱出口が開きました ##",9;
		hideoffnpc "脱出口#HT_Test";
		close;
	case 2:
		mes "操作が取り消されました";
		announce "switch:  ## 操作が取り消されました ##",9;
		close;
	case 3:
		mes "控え室に転送されます";
		announce "switch:  ## 転職試験が中断されます…… ##",9;
		close2;
		stopnpctimer "HT_Center";
		warp "job_hunte.gat",176,22;
		killmonster "job_hunte.gat","All";
		enablewaitingroomevent "HT_ChatRoom";
		end;
	}
}

//==============================================================================
job_hunte.gat,89,139,0		script	脱出口#HT_Test	45,1,1,{
	stopnpctimer "HT_Center";
	set CHANGE_HT,14;
	savepoint "payon.gat",104,99;
	if(rand(2))
		warp "payon_in02.gat",17,31;
	else
		warp "payon_in03.gat",128,7;
	killmonster "job_hunte.gat","All";
	enablewaitingroomevent "HT_ChatRoom";
	end;
}

//==============================================================================
job_hunte.gat,52,67,0	script	#HT_Abyss	139,0,1,{
	stopnpctimer "HT_Center";
	announce "試験監督:  " +$@ht_tester$+ "様、落とし穴に落ちました。",9;
	warp "job_hunte.gat",176,22;
	killmonster "job_hunte.gat","All";
	enablewaitingroomevent "HT_ChatRoom";
	end;
}

job_hunte.gat,53,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,53,69,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,54,68,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,54,70,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,55,70,0		duplicate(#HT_Abyss)	落とし穴	139,0,1

job_hunte.gat,59,66,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,59,67,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,61,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,61,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,68,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,69,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,68,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,69,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,76,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,76,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,68,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,68,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,96,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,96,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,97,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,97,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,100,68,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,100,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,101,68,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,101,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,107,66,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,107,67,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,109,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,109,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,117,68,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,117,69,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,119,68,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,119,69,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,124,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,124,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,66,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,67,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,70,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,126,71,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,70,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,71,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,124,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,124,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,82,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,126,83,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,82,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,83,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,86,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,126,87,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,86,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,87,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,125,96,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,125,97,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,127,96,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,97,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,107,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,127,107,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,126,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,124,119,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,125,119,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,124,121,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,121,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,126,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,124,130,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,124,131,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,130,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,125,131,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,126,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,2
job_hunte.gat,127,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,2
job_hunte.gat,126,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,127,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,120,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,120,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,121,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,121,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,116,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,116,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,117,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,117,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,112,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,112,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,120,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,120,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,121,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,121,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,106,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,107,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,106,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,107,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,99,138,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,99,139,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,101,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,101,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,138,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,78,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,78,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,140,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,72,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,73,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,72,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,73,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,62,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,63,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,64,140,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,64,141,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,62,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,52,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,53,139,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,54,140,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,54,141,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,52,141,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,52,133,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,53,133,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,52,135,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,53,135,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,52,122,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,53,122,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,54,120,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,54,121,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,52,120,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,54,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,55,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,54,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,55,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,53,101,0		duplicate(#HT_Abyss)	落とし穴	139,1,1
job_hunte.gat,53,103,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,55,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,55,103,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,54,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,54,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,55,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,55,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,52,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,52,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,53,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,53,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,52,86,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,52,87,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,53,86,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,53,87,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,54,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,55,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,54,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,55,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,78,80,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,78,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,80,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,74,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,74,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,75,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,75,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,66,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,66,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,64,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,65,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,64,83,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,83,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,66,88,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,66,89,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,88,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,89,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,64,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,64,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,66,100,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,66,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,100,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,64,106,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,64,107,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,106,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,107,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,64,112,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,64,113,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,112,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,113,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,66,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,66,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,66,120,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,66,121,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,120,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,67,121,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,64,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,64,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,65,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,68,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,68,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,69,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,69,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,75,128,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,75,129,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,77,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,96,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,96,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,97,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,97,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,100,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,100,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,101,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,101,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,106,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,106,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,107,128,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,107,129,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,112,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,112,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,126,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,127,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,114,118,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,114,119,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,118,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,119,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,114,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,114,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,112,110,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,112,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,110,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,112,103,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,113,103,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,112,105,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,105,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,114,96,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,114,97,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,96,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,97,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,112,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,112,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,113,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,114,84,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,114,85,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,84,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,85,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,114,80,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,114,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,80,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,115,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,110,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,110,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,111,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,111,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,104,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,104,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,105,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,105,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,101,80,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,101,81,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,103,80,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,81,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,94,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,94,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,95,78,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,95,79,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,76,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,76,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,80,110,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,80,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,81,110,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,81,111,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,86,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,86,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,87,114,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,87,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,82,100,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,82,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,100,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,83,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,76,94,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,76,95,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,94,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,77,95,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,78,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,78,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,79,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,86,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,86,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,87,92,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,87,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,90,96,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,90,97,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,91,96,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,91,97,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,99,94,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,99,95,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,100,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,101,93,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,101,95,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,102,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,102,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,90,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,91,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,102,98,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,102,99,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,98,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,99,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,106,104,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,106,105,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,107,104,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,107,105,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,102,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,102,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,116,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,103,117,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,76,98,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,76,99,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,78,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,3
job_hunte.gat,79,101,0		duplicate(#HT_Abyss)	落とし穴	139,0,3
job_hunte.gat,81,104,0		duplicate(#HT_Abyss)	落とし穴	139,5,0
job_hunte.gat,81,105,0		duplicate(#HT_Abyss)	落とし穴	139,5,0
job_hunte.gat,86,106,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,87,106,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,87,104,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,90,108,0		duplicate(#HT_Abyss)	落とし穴	139,0,6
job_hunte.gat,91,108,0		duplicate(#HT_Abyss)	落とし穴	139,0,6
job_hunte.gat,92,114,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,92,115,0		duplicate(#HT_Abyss)	落とし穴	139,1,0
job_hunte.gat,90,115,0		duplicate(#HT_Abyss)	落とし穴	139,0,0

job_hunte.gat,94,98,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,94,99,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,96,102,0		duplicate(#HT_Abyss)	落とし穴	139,0,4
job_hunte.gat,97,102,0		duplicate(#HT_Abyss)	落とし穴	139,0,4
job_hunte.gat,94,108,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,95,108,0		duplicate(#HT_Abyss)	落とし穴	139,0,1
job_hunte.gat,96,106,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,96,107,0		duplicate(#HT_Abyss)	落とし穴	139,2,0
job_hunte.gat,98,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,2
job_hunte.gat,99,109,0		duplicate(#HT_Abyss)	落とし穴	139,0,2
job_hunte.gat,99,106,0		duplicate(#HT_Abyss)	落とし穴	139,0,0
job_hunte.gat,102,108,0		duplicate(#HT_Abyss)	落とし穴	139,4,0
job_hunte.gat,102,109,0		duplicate(#HT_Abyss)	落とし穴	139,4,0


//==========================================
// ファルコンレンタル
//------------------------------------------

//in_hunter.gat,146,99,2	script	ファルコン管理兵	105,{
hu_in01.gat,381,304,5	script	ファルコン管理兵	105,{
	if(Job != Job_Hunter && Job != Job_Ranger) {
		mes "バカやろ～！ファルコンは";
		mes "ハンターとスナイパーと";
		mes "レンジャー専用だ！";
		close;
	}
	mes "[ファルコン管理兵]";
	mes "ファルコンが必要か？";
	mes "一羽 2500 zenyだ！";
	next;
	if(select("利用する","やめる")==2) {
		mes "[ファルコン管理兵]";
		mes "おい! 何のまねだ。";
		mes "そこの君！";
		mes "停止しろ！停止！";
		close;
	}
	if(checkfalcon()) {
		mes "[ファルコン管理兵]";
		mes "君にはもうファルコンが";
		mes "いるじゃないか。";
		close;
	}
	if(Zeny < 2500) {
		mes "[ファルコン管理兵]";
		mes "お金が足りない！";
		close;
	}
	if(getskilllv(127) < 1) {
		//未調査
		close;
	}
	set Zeny,Zeny-2500;
	setfalcon;
	close;
}
