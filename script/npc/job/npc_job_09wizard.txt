//====================================================================
//Ragnarok Online Wizard jobchange script
//
//　■ CHANGE_WZ    -> 0～12
//     $@wz_tester$ -> 実技挑戦者のキャラ名
//====================================================================

//==========================================
// 試験申請・一次試験（収集）・転職
//------------------------------------------

gef_tower.gat,111,37,4	script	ギルド関係者	70,{
	if(Upper == UPPER_HIGH) {
		mes "[カトリーヌ]";
		mes "うん？";
		mes "こんな所まで何かご用かしら？";
		next;
		mes "[カトリーヌ]";
		mes "なんだか普通じゃない気配を";
		mes "持っているわね。";
		mes "その調子で頑張ってね。";
		close;
	}
	if(Job == Job_Wizard) {
		mes "[カトリーヌ]";
		mes "もうウィザードであるあなたには";
		mes "こちらへの用は無いはず。";
		next;
		mes "[カトリーヌ]";
		if(Sex == 0) {	//未調査
			mes "ボーイフレンドでも出来たら";
			mes "連れてきてね。フフッ";
		}
		else
			mes "デートの申し込みなら嬉しいけど。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[魔術師ギルド関係者]";
		mes "あら、こんな高いところまで何の用？";
		mes "特に用が無ければ降りてくださいね。";
		mes "ここはウィザードのための場所よ。";
		next;
		mes "[魔術師ギルド関係者]";
		mes "さ、気をつけて降りてね。";
		close;
	}
	switch(CHANGE_WZ) {
	case 0:
		mes "[魔術師ギルド関係者]";
		mes "あら、こんな高いところまで上って";
		mes "くるなんて。何の用事で来たの？";
		next;
		if(select("ウィザードに転職しに来ました","…なんでもないです")==2) {
			mes "[魔術師ギルド関係者]";
			mes "ん…";
			mes "特に用がなければ";
			mes "降りてください～。";
			close;
		}
		mes "[魔術師ギルド関係者]";
		mes "そうね、それ以外の理由で";
		mes "こんな高いところまで上ってこない";
		mes "わよね。とにかくよく来ました。";
		mes "私が転職のお手伝いをします。";
		next;
		mes "[魔術師ギルド関係者]";
		mes "私の名前はカトリーヌ=メディッチ。";
		mes "私も転職してからそんなに経ってない";
		mes "ウィザードよ。気楽に「カトリーヌ」と";
		mes "呼んでくれていいわ。ふふ…";
		next;
		mes "[カトリーヌ]";
		mes "ウィザードになりたがる人は多いけど";
		mes "脱落する人も多い…";
		mes "ウィザードになるのは大変なことなの。";
		next;
		mes "[カトリーヌ]";
		mes "まず、転職するにはJobレベル40";
		mes "は最低必要。";
		mes "そうでないと、ウィザードになるだけの";
		mes "魔法力が備わってないから。";
		next;
		mes "[カトリーヌ]";
		mes "詳しい説明は、転職申し込みを";
		mes "した後にするわ。";
		mes "どう？今すぐ申込書を作る？";
		next;
		if(select("はい、おねがいします","もうちょっと考えてみます")==2) {
			mes "[カトリーヌ]";
			mes "わかりました。ゆっくり考えなさい。";
			mes "転職申し込みは、いつでも";
			mes "受け付けているから。";
			close;
		}
		if(JobLevel < 40) {
			mes "[カトリーヌ]";
			mes "ほら、私がさっき言ったのを";
			mes "思い出して。Jobレベルが40以上";
			mes "じゃないと転職できないわよ。";
			next;
			mes "[魔術師ギルド関係者]";
			mes "焦らないで、もう少し勉強してきて。";
			mes "転職条件を満たしたら受けさせて";
			mes "あげます。";
			close;
		}
		if(SkillPoint) {	//未調査
			mes "[カトリーヌ]";
			mes "あらあら、スキルポイントが";
			mes "余っているみたいね。";
			mes "スキルポイントを使い切ってから";
			mes "来てくださいね。";
			close;
		}
		mes "[カトリーヌ]";
		mes "はい、それでは転職申し込みを";
		mes "受け付けます。";
		mes "名前は " +strcharinfo(0)+ " ね。";
		next;
		mes "[カトリーヌ]";
		mes "ウィザード転職試験は";
		mes "三つに分かれていて、";
		mes "一つめは魔法アイテム集め。";
		mes "二つめは筆記試験";
		mes "三つめは魔法実技試験。";
		next;
		mes "[カトリーヌ]";
		mes "この中の一番目の試験は、";
		mes "Jobレベル50の人は免除になるわ。";
		mes "もう十分に努力してるから。";
		next;
		if(JobLevel >= 50) {
			mes "[カトリーヌ]";
			mes "あら、あなたJobレベル50";
			mes "になってますね。";
			mes "よっぽど頑張ったんですね。";
			mes "素敵なウィザードになるでしょう。";
			next;
			mes "[カトリーヌ]";
			mes "それでは一つめの試験は";
			mes "免除にしましょう。";
			mes "でも、まだ二つの試験が";
			mes "残ってるから安心しないでね。";
			next;
			mes "[カトリーヌ]";
			mes "じゃあ、あの隅にいる人に";
			mes "話しかけてみてください。";
			mes "かなり難しいと思うから";
			mes "気をつけてね。";
			set CHANGE_WZ,3;
			close;
		}
		mes "[カトリーヌ]";
		mes "それでは、申し込みを完了したので";
		mes "一つめの試験に移りましょうか。";
		next;
		mes "[カトリーヌ]";
		mes "魔法アイテムを集めてくるのが";
		mes "一つ目の試験です。";
		mes "大事なのは、自分の力で集めて";
		mes "くるということです。";
		next;
		mes "[カトリーヌ]";
		mes "あなたが集めてくるアイテムは、";
		if(rand(2)) {	//台詞未調査
			set CHANGE_WZ,1;
			mes "^3051FDイエロージェムストーン^000000 10個,";
			mes "^3051FDレッドジェムストーン^000000 10個,";
			mes "^3051FDブルージェムストーン^000000 10個,";
		}
		else {
			set CHANGE_WZ,2;
			mes "^3051FDクリスタルブルー^000000 5個,";
			mes "^3051FDイエローライブ^000000 5個,";
			mes "^3051FDレッドブラッド^000000 5個,";
			mes "^3051FDウィンドオブヴェルデュール^000000 5個,";
		}
		mes "少し手間がかかるけど";
		mes "なんとかなるでしょう。";
		next;
		mes "[カトリーヌ]";
		mes "それではいってらっしゃい～。";
		mes "ゆっくり待ってます。";
		close;
	case 1:
	case 2:
		mes "[カトリーヌ]";
		mes "はい、アイテムは集めてきましたか？";
		mes "それではちゃんと集められたか";
		mes "見てみましょうか。";
		next;
		if(CHANGE_WZ == 1) {
			setarray '@need,715,716,717;
			set '@amount,10;
		}
		else {
			setarray '@need,990,991,992,993;
			set '@amount,5;
		}
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1) {	//必要アイテムのチェック
			if(countitem('@need['@i]) < '@amount)
				break;
		}
		if('@i < getarraysize('@need)) {
			mes "[カトリーヌ]";
			mes "ん？全部揃っていないわ。";
			next;
			mes "[カトリーヌ]";
			mes "せっかく上ってきて大変だったけど、";
			mes "もう一度いってらっしゃい。";
			mes "今度はしっかり集めてきてね。";
			next;
			mes "[カトリーヌ]";
			for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1)
				mes "^3051FD" +getitemname('@need['@i])+ "^000000 " +'@amount+ "個,";
			mes "よく覚えてしっかり集めてきてね。";
			close;
		}
		mes "[カトリーヌ]";
		mes "お、正確ですね！";
		mes "よく集めてきました。";
		mes "それらのアイテムは、ギルドで";
		mes "有効に使わせていただきますね。";
		next;
		set CHANGE_WZ,3;
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1)
			delitem '@need['@i],'@amount;
		mes "[カトリーヌ]";
		mes "はい、一つめの試験は合格です。";
		mes "でも、まだ二つの試験が";
		mes "残ってるから安心しないでね。";
		next;
		mes "[カトリーヌ]";
		mes "じゃあ、あの隅にいる人に";
		mes "話しかけてみてください。";
		mes "かなり難しいと思うから";
		mes "気をつけてね。";
		close;
	case 3:
	case 4:
		mes "[カトリーヌ]";
		mes "ん？どうしたの？";
		mes "一つめの試験は終わったから";
		mes "あの隅にいる人のところに";
		mes "行きなさい。";
		next;
		mes "[カトリーヌ]";
		mes "二つめの試験を受けなければ";
		mes "ならないから。";
		mes "待っているでしょうから早く行って";
		mes "あげて。";
		close;
	case 5:
		mes "[カトリーヌ]";
		mes "ふふ、聞いていたわよ。";
		mes "問題を解くのに苦労したわね。";
		mes "何か贈り物でもしてあげたいけど、";
		mes "最後の試験が残っているわね。";
		next;
		mes "[カトリーヌ]";
		mes "もう少しであなたもウィザードに";
		mes "なれるから、贈り物はその時に";
		mes "しましょう。";
		next;
		mes "[カトリーヌ]";
		mes "それでは行ってらっしゃい。";
		mes "あの人が待ってるわ。";
		close;
	default:	//6～11のとき
		mes "[カトリーヌ]";
		mes "あらあら、試験を抜け出してきては";
		mes "だめじゃないの。";
		next;
		if(Sex == 0) {
			mes "[カトリーヌ]";
			mes "女の子が弱いふりをしたってだめ。";
			mes "あなただってウィザードになるために";
			mes "ここまで来たんでしょう？";
			next;
			mes "[カトリーヌ]";
			mes "私だって難しかったけど";
			mes "諦めなかったんだから。";
			mes "今後を生きていくつもりなら、";
			mes "これくらいの試験なんか";
			mes "こなせなくちゃだめ。";
		}
		else {
			mes "マジシャンだからといって、男が";
			mes "弱気になっちゃだめ。";
		}
		mes "[カトリーヌ]";
		mes "それでは、元気を出して行きなさい。";
		mes "あの人が待ってるわ。";
		close;
	case 12:
		mes "[カトリーヌ]";
		mes "全ての試験に合格、";
		mes "おめでとうございます！";
		next;
		mes "[カトリーヌ]";
		mes "ああ、こうしてる場合じゃないわ。";
		mes "すぐに転職させてあげなければ。";
		next;
		unequip;
		jobchange Job_Wizard;
		set CHANGE_WZ,0;
		mes "[カトリーヌ]";
		mes "もうあなたもウィザード。";
		mes "正々堂々として、しっかりと";
		mes "生きていかなければならないわ。";
		mes "私達ウィザードはとても強力な";
		mes "魔法が使えるから、その分";
		mes "行動は控え目にしなきゃだめよ。";
		next;
		mes "[カトリーヌ]";
		mes "街でいたずらに魔法を使ったり、";
		mes "人の邪魔をしたりするのは厳禁。";
		mes "ウィザードの魔法っていうのは";
		mes "モンスターとの戦いで真価を発揮";
		mes "するものだからね。";
		next;
		mes "[カトリーヌ]";
		mes "他の人とパーティーを組んで、";
		mes "彼らの助けになってあげてね。";
		mes "あ…あと、あなたにプレゼントが";
		mes "あります。ちょっと待ってね…";
		next;
		mes "[カトリーヌ]";
		mes "ごそごそ…";
		mes "がさごそ…";
		next;
		getitem 505,6;
		mes "[カトリーヌ]";
		mes "必要な時、有効に使ってくれたらと";
		mes "思うわ。";
		mes "私があげたんだから、売らずに";
		mes "自分で使ってちょうだいね。";
		next;
		mes "[カトリーヌ]";
		mes "さあ、ウィザードとして素敵に";
		mes "暮らしてくださいね。";
		close;
	}
}

//==============================================================
gef_tower.gat,107,36,4	script	白い毛の犬	81,{
	if(Job == Job_Wizard) {
		mes "[マリア]";
		mes "ここに居るより外に出て、君が";
		mes "どれくらい強くなったか試して";
		mes "みてはいかが？";
		next;
		mes "[マリア]";
		mes "一日一日、違った成長をするのが";
		mes "私達ウィザードだということを";
		mes "忘れずに。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[犬]";
		mes "ふん…魔法も使うことができない";
		mes "人が何しに来たのよ？";
		mes "暇ならゲフェン塔の下で運動でも";
		mes "していなさい～。";
		next;
		mes "[犬]";
		mes "早く降りなさい！";
		mes "あんたと話している暇はないの！";
		close;
	}
	switch(CHANGE_WZ) {
	case 0:
		mes "[犬]";
		mes "あ、何の話をしたいかわかるよ。";
		mes "ウィザードに転職したいんでしょう？";
		next;
		mes "[犬]";
		mes "転職したいなら、横のカトリーヌに";
		mes "相談してみて。";
		mes "彼女ならよく手伝ってくれるでしょう。";
		next;
		mes "[犬]";
		mes "転職試験の過程でわからないことが";
		mes "あったら私にも聞いて。";
		mes "こう見えても物知りなんだから。";
		next;
		if(select("……","犬が喋ってる…")==1) {
			mes "[犬]";
			mes "ん？何…その間は…";
			mes "犬が喋ってるのを見るのは";
			mes "初めて？";
			next;
			mes "[犬]";
			mes "ふむ…犬が喋るところは";
			mes "そうそう見られるものではないわね。";
			mes "ふむふむ…";
			mes "……";
		}
		else {
			mes "[犬]";
			mes "そんな露骨に言わなくても";
			mes "いいじゃない！";
			mes "どうしてこうなったかの訳も知らない";
			mes "くせに…";
		}
		next;
		mes "[犬]";
		mes "私の名前は";
		mes "「マリア=スプル=ロドプスカ」";
		mes "そのまま「マリア」と呼んで";
		mes "くれればいい。";
		mes "ここであんたのようなウィザード";
		mes "転職希望者の手伝いをしているのよ。";
		next;
		mes "[マリア]";
		mes "私が犬になった理由は…";
		mes "いくつかの実験をしているときに、";
		mes "ボーイフレンドのミスでこうなって";
		mes "しまったの…。";
		next;
		mes "[マリア]";
		mes "理論上では数ヵ月後には薬の効き目が";
		mes "切れるはずなんだけど…";
		next;
		mes "[マリア]";
		mes "まあいいわ…";
		mes "試験を受けるなら助けになるわ。";
		next;
		mes "[マリア]";
		mes "転職についてはさっきも言った通り、";
		mes "まずカトリーヌに話を聞きなさい。";
		mes "彼女もウィザードになってから";
		mes "日が浅いのよ…フフ。";
		next;
		mes "[マリア]";
		mes "転職試験の過程について";
		mes "詳しく説明できるけど…";
		mes "どう？私から説明してあげようか？";
		next;
		switch (select("はい！説明をお願いします","いいえ、大丈夫です","犬がものを話すのね…")) {
			case 1:
				mes "[マリア]";
				mes "ん。あんたには特別に詳しく";
				mes "教えてあげるわ。";
				next;
				mes "[マリア]";
				mes "ウィザードへ転職するには三つの";
				mes "試験を通過しなければならないの。";
				mes "最初に、魔法アイテムを集めてくる";
				mes "試験があるわ。";
				next;
				mes "[マリア]";
				mes "それは、カトリーヌに試験申込書を";
				mes "提示したらすぐ始まるわ。";
				mes "各ジェムストーンや属性原石を";
				mes "集めるのよ。";
				next;
				mes "[マリア]";
				mes "二つ目は魔法クイズ。";
				mes "あそこの隅っこにいるラウレル";
				mes "という陰気な人が担当してる。";
				next;
				mes "[マリア]";
				mes "魔法に関する問題や、モンスターに";
				mes "関する問題、またはマジシャンに関する";
				mes "問題だったはずよ。";
				mes "10問も問題を出すのに、全部正解";
				mes "しないとどんどん落第させていく";
				mes "らしいわ…。";
				next;
				mes "[マリア]";
				mes "彼がそのまま三つ目の試験に";
				mes "案内してくれるわ。";
				mes "三つ目の試験は、モンスター達を";
				mes "倒す試験よ。";
				next;
				mes "[マリア]";
				mes "各部屋に入ると、それぞれの部屋の";
				mes "属性と同じ属性のモンスターが出現";
				mes "するから、より効果的な魔法を駆使して";
				mes "進むことが大事ね。";
				next;
				mes "[マリア]";
				mes "私の説明はこれくらい。";
				mes "聞くより自分で体験したほうが";
				mes "良いからね。";
				close;
			case 2:
				mes "[マリア]";
				mes "そう、それじゃ申し込みをして";
				mes "頑張っていらっしゃい。";
				close;
			case 3:
				mes "[マリア]";
				mes "犬で悪かったわね!!";
				next;
				mes "[マリア]";
				mes "もう、どっか行っちゃえ!!";
				close2;
				warp "gef_dun00.gat",116,102;
				end;
		}
	case 1:
	case 2:
		mes "[マリア]";
		mes "見たところどうしていいかわからない";
		mes "っていう顔ね。";
		mes "転職試験の申し込みは済ませて、";
		mes "アイテムを集めてくるように";
		mes "言われてたんでしょ？";
		next;
		mes "[マリア]";
		mes "一応これも試験だから、自分の力で";
		mes "なんとかしないとだめ。";
		next;
		mes "[マリア]";
		mes "聞いたところによると属性原石を";
		mes "集めてくるのよね。";
		mes "集めるのは手伝えないけど、";
		mes "助言くらいはしてあげられるわ。";
		next;
		mes "[マリア]";
		mes "クリスタルブルーは、バイラン島に";
		mes "行ってみなさい。";
		mes "カナトウス、ククレ、マリナ、バドン…";
		mes "このへんのモンスターから";
		mes "手に入れやすいでしょう。";
		next;
		mes "[マリア]";
		mes "イエローライブは、昆虫型モンスター";
		mes "らから手に入るわ。";
		mes "ホルンやマンティス、ビタタといった";
		mes "モンスターを倒してみて。";
		next;
		mes "[マリア]";
		mes "レッドブラッドはエルダーウィローから";
		mes "たくさん出ると言けど、砂漠に行って";
		mes "メタルラやスコーピオンを倒してみる";
		mes "のもいいかもね。";
		next;
		mes "[マリア]";
		mes "ウィンドオブヴェルデュールは";
		mes "ホーネット、スタイナー、";
		mes "スティールチョンチョンあたりかな。";
		mes "少し頑張れば手に入るわ。";
		next;
		mes "[マリア]";
		mes "それじゃ頑張ってみて。";
		mes "ウィザードになるためには";
		mes "これくらい基本だから。";
		close;
	case 3:
	case 4:
		mes "[マリア]";
		mes "一つ目の試験が終わって安心している";
		mes "ようね…でも！";
		mes "まだ試験は二つ残っているから気を";
		mes "抜いちゃだめよ！";
		close;
	case 5:
		mes "[マリア]";
		mes "うん、よく解いて来たわね。";
		next;
		mes "[マリア]";
		mes "それでは最後の試験まで気を抜かずに";
		mes "頑張っていらっしゃい。";
		mes "ラウレルが待ってるよ。";
		close;
	default:	//6～11のとき
		mes "[マリア]";
		mes "駄目ね…あきらめて帰って来たの？";
		mes "まったくもう…そんなことでは";
		mes "良いウィザードになれないわよ！";
		next;
		mes "[マリア]";
		mes "各部屋には、その部屋と同じ属性の";
		mes "モンスターが出るのはわかったわね？";
		mes "魔法を扱う人間なら、どの属性がその";
		mes "モンスターに効果的なのかもしっかり";
		mes "理解していなければならないわ。";
		next;
		mes "[マリア]";
		mes "スキルを使うモンスターへの対処も";
		mes "できていなければならないから、";
		mes "スキルで死んでしまう人は、それを";
		mes "食らう前に倒してしまわなければ";
		mes "ならない。";
		next;
		mes "[マリア]";
		mes "とにかく戻ってもう一度挑戦して";
		mes "いらっしゃい。こんなところで音を";
		mes "あげていてはだめ。";
		close;
	case 12:
		mes "[マリア]";
		mes "やっぱりやりとげたわね！";
		mes "これからはウィザードって呼んでも";
		mes "遜色は無いでしょうね。";
		next;
		mes "[マリア]";
		mes "おめでとう。これからも頑張るのよ。";
		close;
	}
}


//==========================================
// 二次試験（筆記）
//------------------------------------------

gef_tower.gat,102,24,8	script	陰気なウィザード	735,{

	function Routine {
		mes "[ラウレル]";
		mes "真面目なやつだ…。";
		mes "どれ…今から説明してやろう。";
		mes "もし試験が難しいと思っても、";
		mes "言われたとおりにすれば早く簡単に";
		mes "終えることができるだろう。";
		next;
		mes "[ラウレル]";
		mes "試験は戦闘をこなしてくることだ。";
		mes "水の部屋、地の部屋、火の部屋と";
		mes "順に進み、各部屋にはそれぞれの";
		mes "部屋の属性を持ったモンスターが";
		mes "出現する。";
		next;
		mes "[ラウレル]";
		mes "どんなモンスターが出てくるかは";
		mes "入ればわかる。";
		mes "そこでは、各属性に効果的な属性で";
		mes "対抗することによって、より簡単に";
		mes "抜けることができるだろう…";
		next;
		mes "[ラウレル]";
		mes "制限時間内に、出現したモンスターを";
		mes "全部倒し、さらに立ちふさがるゲート";
		mes "モンスターを倒せば次の部屋に";
		mes "移動できる。";
		next;
		mes "[ラウレル]";
		mes "そして私のところに戻れば、";
		mes "転職試験は終了となる。晴れて";
		mes "ウィザードになれるというわけだ。";
		return;
	}

	if(Job == Job_Novice) {
		mes "[ラウレル]";
		mes "ひよっこがなぜこんな場所に来た？";
		mes "すぐに立ち去りなさい。";
		close2;
		warp "geffen.gat",120,110;
		end;
	}
	if(Job == Job_Priest) {
		mes "[ラウレル]";
		mes "帰るんだ。神の仕いに用はない。";
		mes "魔力と神力は相容れないからな。";
		next;
		mes "[ラウレル]";
		mes "それでなくとも私の体調はよくない…";
		mes "近づかずあちらへ行きなさい。";
		close;
	}
	if(Job == Job_Wizard) {
		mes "[ラウレル]";
		mes "…私に何の用だ？";
		mes "お前も魔法を使う者なら魔法について";
		mes "よく知っていなければならない。";
		next;
		mes "[ラウレル]";
		mes "魔法を不真面目に扱っていると";
		mes "強力な魔法を使った時、自分の";
		mes "魔法を制御できなくなるだろう…。";
		mes "そうなりたくなければ、魔法について";
		mes "深く理解しておくべきだ。";
		next;
		mes "[ラウレル]";
		mes "残りの人生を、廃人として";
		mes "終わらせたくなければな…。";
		close;
	}
	if(Job != Job_Magician) {
		mes "[ラウレル]";
		mes "うう…苦しい…。";
		mes "全身がまるで冷たい氷に";
		mes "浸かっているような感じだ…。";
		next;
		mes "[ラウレル]";
		mes "何だお前は…";
		mes "あっちに行ってくれないか…。";
		close;
	}
	switch(CHANGE_WZ) {
	case 0:
		mes "[ラウレル]";
		mes "…何をしたいのかわからないが";
		mes "今はお前に付き合っている暇は無い。";
		next;
		mes "[ラウレル]";
		mes "向こうへ行きなさい。";
		close;
	case 1:
	case 2:
		mes "[ラウレル]";
		mes "ククク…";
		mes "ウィザードになりたいという奴か。";
		next;
		mes "[ラウレル]";
		mes "そのままでいると、狩りもちびちび";
		mes "としかできないだろう。";
		next;
		mes "[ラウレル]";
		mes "ウィザードの素晴らしさを";
		mes "後で思い知るだろう…ククク…。";
		close;
	case 3:
		mes "[ラウレル]";
		mes "ククク…一つめの試験を越えて来たか。";
		mes "そう…私が二つめの試験を担当する";
		mes "ラウレル=アスパゴラス様だ。";
		next;
		mes "[ラウレル]";
		mes "今からでも遅くないから";
		mes "町に戻って平和な生活を";
		mes "続けたらどうだ？ふふ…。";
		next;
		mes "[ラウレル]";
		mes "ククク…魔力をあやつるには";
		mes "お前はまだ不完全だろう。";
		mes "非常に危険だ…。";
		break;
	case 4:
		mes "[ラウレル]";
		mes "ククク…未練があるようだな。";
		next;
		mes "[ラウレル]";
		mes "そんなに平和な暮らしが気に食わない";
		mes "というのか？";
		next;
		mes "[ラウレル]";
		mes "魔力を操るにはお前はまだ";
		mes "不完全だ…。考え直したほうが良いな。";
		break;
	case 5:
		set CHANGE_WZ,6;
		mes "[ラウレル]";
		mes "よし…十分に休んだか？";
		mes "それでは、ウィザード転職への";
		mes "最終試験だ。";
		next;
		mes "[ラウレル]";
		mes "試験について簡単に";
		mes "説明してやろうか…。";
		next;
		if(select("いいえ、結構です","少し聞いてみます")==1) {
			mes "[ラウレル]";
			mes "無謀な奴だ…。まあ骨は拾ってやる。";
			mes "モンスターらがお前を迎えてくれる";
			mes "だろう。";
			next;
		}
		else {
			Routine;
			next;
			mes "[ラウレル]";
			mes "ククク…恐ろしいという表情だな。";
			mes "まだ遅くは無い。今からでもあきらめる";
			mes "なら、町に返してやるぞ…どうする？";
			next;
			if(select("試験を続けてください","恐ろしいから帰ります")==2) {
				mes "[ラウレル]";
				mes "よく考えたな。そう…お前は";
				mes "そのままが似合っている。";
				mes "町に帰って平凡な人生を歩みなさい。";
				close2;
				warp "geffen.gat",120,110;
				end;
			}
		}
		//台詞未調査
		mes "[ラウレル]";
		mes "それでは望みどおり、今すぐ";
		mes "送ってやる。好きなように";
		mes "暴れてきなさい。";
		next;
		warp "job_wiz.gat",57,154;
		end;
	default:	//6～9のとき
		mes "[ラウレル]";
		mes "なに？また試験を受けると…？";
		mes "戦闘試験に失敗したくせに…ククク…。";
		mes "それだけ魔法が好きなんだな…。";
		next;
		mes "[ラウレル]";
		mes "まともにいかないところを見ると、";
		mes "お前はもっと別の試験も";
		mes "受けなくてはならないな…。";
		mes "不満があるならもっと良い";
		mes "結果を出すことだ。";
		next;
		mes "[ラウレル]";
		mes "それでは一度解いてみなさい…クク…。";
		next;
		mes "[ラウレル]";
		mes "1. 次の中で、";
		mes "属性の違うものを選べ。";
		next;
		if(select("マンティス","カナトウス","ガイアス","キャラメル")==2)
			set '@point,'@point+20;
		mes "[ラウレル]";
		mes "2. 次の中で、ルートモンスター";
		mes "ではないモンスターを答えよ。";
		next;
		if(select("ヨーヨー","白蓮玉","メタルラ","ゼロム")==4)
			set '@point,'@point+20;
		mes "[ラウレル]";
		mes "3. 次の中で詠唱反応しない";
		mes "モンスターはどれか。";
		next;
		if(select("マリナ","ビタタ","スコーピオン","ガイアス")==1)
			set '@point,'@point+20;
		mes "[ラウレル]";
		mes "4. マリンスフィアーに効果的な";
		mes "魔法を答えよ。";
		next;
		if(select("コールドボルト","ファイアーボルト","ライトニングボルト","ストーンカース")==3)
			set '@point,'@point+20;
		mes "[ラウレル]";
		mes "5. 次の中から移動するモンスター";
		mes "を選べ。";
		next;
		if(select("ヒドラ","マンドラゴラ","天下大将軍","フリルドラ")==4)
			set '@point,'@point+20;
		mes "[ラウレル]";
		mes "クク…さあ…出来はどうだ？";
		next;
		set CHANGE_WZ,CHANGE_WZ+1;
		mes "[ラウレル]";
		mes "点数は… " +'@point+ "点だ。";
		if('@point < 40) {
			mes "不合格だ。もう少し勉強してこい…。";
			next;
			mes "[ラウレル]";
			mes "やはりお前にはまだ足りないものが";
			mes "ある。だから失敗するのだ…。";
			close;
		}
		if('@point == 40) {
			mes "クク…まあまあだな…";
			mes "また戦闘試験を受けさせてやるぞ…。";
		}
		else {
			mes "こんなに良く解けていて、なぜ";
			mes "実戦になるとああも弱いのだ…。";
		}
		next;
		if(select("試験に臨みます","試験についてもう一度説明して")==2) {
			Routine;
			next;
		}
		//台詞未調査
		mes "[ラウレル]";
		mes "今度は泣きながら帰ってくるな…。";
		mes "ククク…。";
		mes "望み通りすぐに送ってやる！";
		close2;
		warp "job_wiz.gat",57,154;
		end;
	case 10:
		//台詞未調査
		set CHANGE_WZ,11;
		mes "[ラウレル]";
		mes "…なんて奴だ。";
		mes "ここまでしつこく試験に挑む奴は";
		mes "初めてだ…。";
		next;
		mes "[ラウレル]";
		mes "よし…私から一つ提案がある。";
		mes "お前も疲れただろうから…ククク…";
		mes "そう、^3051FD古い巻物^000000を一つ";
		mes "持って来なさい。";
		next;
		mes "[ラウレル]";
		mes "それが嫌ならもう一度試験を受けて";
		mes "受かってみろ。";
		mes "試験場に送ってやる…。";
		close2;
		warp "job_wiz.gat",57,154;
		end;
	case 11:
		mes "[ラウレル]";
		mes "そうか…また来たか…ククク。";
		mes "試験に挑戦するのか…それとも";
		mes "^3051FD古い巻物^000000を持って来たのか？";
		next;
		if(select("試験に挑戦","古い巻物を…")==1) {
			mes "[ラウレル]";
			mes "ククク…それくらいの根性が無いとな。";
			mes "また送ってやるから、頑張れ…。";
			close2;
			warp "job_wiz.gat",57,154;
			end;
		}
		if(countitem(618) < 1) {
			mes "[ラウレル]";
			mes "持っていないではないか…。";
			close;
		}
		delitem 618,1;
		set CHANGE_WZ,12;
		mes "[ラウレル]";
		mes "ククク…結局手に入れてきたか。";
		mes "まあよくやった。";
		mes "これでまた私の研究を続けることが";
		mes "できる。感謝するぞ…。";
		next;
		mes "[ラウレル]";
		mes "ククク…カトリーヌに試験は通ったと";
		mes "伝えておく…クククク…。";
		mes "よく頑張った。";
		close;
	case 12:
		mes "[ラウレル]";
		mes "試験は合格だ。";
		mes "カトリーヌの元へ行き";
		mes "転職の手続きを済ますがいい…。";
		next;
		mes "[ラウレル]";
		mes "行きなさい…。そして";
		mes "望んだウィザードになりなさい…。";
		mes "でも気をつけるんだ…魔力は常に";
		mes "お前を狙っている…ククククク…。";
		close;
	}
	//筆記試験ここから
	next;
	if(select("平凡なマジシャンとして生きます","転職試験を続けてください")==1) {
		mes "[ラウレル]";
		mes "ははは…よく選択した。";
		mes "ウィザードに夢を抱くんじゃない";
		mes "魔法を使わなければならないという";
		mes "決まりも無いな…。";
		next;
		mes "[ラウレル]";
		mes "ゆっくり塔を降りなさい。";
		mes "決して振り返らず。";
		mes "今持っている能力を使いながら";
		mes "のんびりと町で暮らしなさい。";
		close;
	}
	if(CHANGE_WZ == 3) {
		mes "[ラウレル]";
		mes "うはははは！";
		mes "お前がどれほどのものか";
		mes "私の目ではっきり見てやる…。";
	}
	else {
		mes "[ラウレル]";
		mes "ハハハ…お前も懲りないな…。";
		mes "どれ、それではどれだけ勉強して来たか";
		mes "見てやろう…。";
	}
	next;
	mes "[ラウレル]";
	mes "それでは試験を始めよう。";
	mes "全部正解しなければだめだ。";
	next;
	mes "[ラウレル]";
	mes "10問出題するから、全て答えなさい。";
	mes "間違ってもどこが間違ったのかは";
	mes "教えられない。";
	next;
	mes "[ラウレル]";
	mes "クックック…それでは試験開始。";
	next;
	switch(rand(3)) {
	case 0:
		mes "[ラウレル]";
		mes "1. スロットのある「ガード」は";
		mes "どのモンスターから手に入れられるか？";
		next;
		if(select("盗蟲","ペコペコ","プパ","コボルト")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "2. 次の中で、マジシャンが一番";
		mes "倒しやすいモンスターはどれか。";
		next;
		if(select("フローラ","ガイアス","ゴーレム","ミスト")==1)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "3. ストーンカースが全く通じない";
		mes "モンスターはどれか。";
		next;
		if(select("エルダーウィロー","イビルドルイド","白蓮玉","マルク")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "4. 風属性で水属性Lv3モンスター";
		mes "を攻撃する場合のダメージ率は？";
		next;
		if(select("125%","150%","175%","200%")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "5. 子デザートウルフとファミリアー";
		mes "が戦ったら、どっちが勝つか。";
		next;
		if(select("子デザートウルフ","ファミリアー","相打ち","わからない")==1)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "6. 次の中でキューペットにできない";
		mes "モンスターはどれか。";
		next;
		if(select("ポポリン","ロッダフロッグ","スモーキー","ポイズンスポア")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "7. 次の中で火属性が一番有効な";
		mes "モンスターを選べ。";
		next;
		if(select("ゴブリン（短剣）","ゴブリン（フレイル）","ゴブリン（斧）","ゴブリン（ハンマー）")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "8. 次の中で魔法防御力が一番高い";
		mes "モンスターを選べ。";
		next;
		if(select("ホルン","チョンチョン","アンドレ","キャラメル")==3)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "9. 種族の違うモンスターを";
		mes "一つ選べ。";
		next;
		if(select("ポリン","マスターリング","ゴーストリング","スポア")==3)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "10. 次の中でアンデットではない";
		mes "モンスターは？";
		next;
		if(select("ドレイク","メガロドン","デビアス","カーリッツバーグ")==3)
			set '@point,'@point+10;
		break;
	case 1:
		mes "[ラウレル]";
		mes "1. マジシャンで一番重要な";
		mes "ステータスは？";
		next;
		if(select("INT","AGI","DEX","VIT")==1)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "2. マジシャンの「ボルト」系列の";
		mes "魔法に無い属性が一つある。どれか。";
		next;
		if(select("水属性","地属性","火属性","風属性")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "3. マジシャンの特徴から一番";
		mes "離れているものを選べ。";
		next;
		if(select("体力が少ない","遠距離攻撃ができる","お金を儲けるのに良い","SPが多い")==3)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "4. マジシャンたちが一番多い街は？";
		next;
		if(select("プロンテラ","モロク","アルベルタ","ゲフェン")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "5. INTが上昇しないカードは？";
		next;
		if(select("アンドレの幼虫カード","ビタタカード","子デザートウルフカード","エルダーウィローカード")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "6. マジシャンの長所を選べ。";
		next;
		if(select("すぐれた歌唱力","すぐれた演技力","すぐれたダンス能力","すぐれた魔法力")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "7. マジシャンがJobLv40の時";
		mes "加重値で得られるINT追加値は？";
		next;
		if(select("8","7","6","5")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "8. マジシャンが装備することが";
		mes "できないアイテムは？";
		next;
		if(select("ナイフ","キャップ","サンダル","医者のヘアバンド")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "9. マジシャン転職試験で、";
		mes "「混合液3」の触媒になる鉱石は";
		mes "どれか。";
		next;
		if(select("ブルージェムストーン","レッドジェムストーン","イエロージェムストーン","レッドブラッド")==1)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "10. 魔法と関係ないカードは？";
		next;
		if(select("マルドゥークカード","白蓮玉カード","ウィローカード","マヤーカード")==2)
			set '@point,'@point+10;
		break;
	case 2:
		mes "[ラウレル]";
		mes "1. ファイアーウォールを覚えるのに";
		mes "必要でないスキルは？";
		next;
		if(select("ファイアーボルト Lv 4","ファイアーボール Lv 5","サイト Lv 1","ナパームビート Lv 4")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "2. フロストダイバーでモンスターを";
		mes "凍結させた場合、その属性は";
		mes "どうなるか？";
		next;
		if(select("水属性","地属性","火属性","風属性")==1)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "3. ナパームビートをマスター";
		mes "した時、モンスターに与える";
		mes "ダメージはMATKの何倍か？";
		next;
		if(select("1.6倍","1.7倍","2倍","20倍")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "4. ストーンカース使用の時に";
		mes "必要なアイテムは？";
		next;
		if(select("レッドブラッド","ブルージェムストーン","イエロージェムストーン","レッドジェムストーン")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "5. セイフティウォールを覚える";
		mes "のに必要でないスキルは？";
		next;
		if(select("ナパームビート Lv 7","ソウルストライク Lv 5","SP 回復力向上 Lv 6","サイト Lv 1")==3)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "6. SP回復力向上を Lv7まで";
		mes "習得した場合、純粋なスキル効果";
		mes "により10秒間で回復するSPは？";
		next;
		if(select("14","21","28","35")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "7. SPが 50%残っている場合、";
		mes "エナジーコートによるダメージ";
		mes "減少量とSP消費量は？";
		next;
		if(select("ダメージ18% SP1.5%","ダメージ18% SP2%","ダメージ24% SP1.5%","ダメージ24% SP2%")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "8. セイフティウォールLv6使用";
		mes "の時消費SPと回避回数は？";
		next;
		if(select("SP 40. 6回","SP 35. 6回","SP 40. 7回","SP 35. 7回")==4)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "9. Lv10サンダーストーム使用";
		mes "の時消費するSPの量は？";
		next;
		if(select("84","74","64","54")==2)
			set '@point,'@point+10;
		mes "[ラウレル]";
		mes "10. イズルードダンジョンで効果が";
		mes "高いスキルは？";
		next;
		if(select("ライトニングボルト","ファイアーボルト","コールドボルト","サイト")==1)
			set '@point,'@point+10;
		break;
	}
	mes "[ラウレル]";
	mes "ご苦労様…。";
	next;
	mes "[ラウレル]";
	mes "どれ…点数は… " +'@point+ "点…";
	switch(CHANGE_WZ) {
	case 3:
		if('@point < 100) {
			mes "不合格だ。";
			next;
			mes "[ラウレル]";
			mes "その程度でウィザードになろうと";
			mes "思ったのか…。";
			mes "勉強して出直しなさい。";
			set CHANGE_WZ,4;
			close;
		}
		mes "ククク…良い。二つ目の試験も通過だ。";
		next;
		mes "[ラウレル]";
		mes "まだ安心するな。三つ目の試験が";
		mes "残っている。休んでおきなさい…";
		mes "ククククク…。";
		break;
	case 4:
		if('@point < 80) {
			mes "不合格だ。";
			next;
			mes "[ラウレル]";
			mes "まだまだ勉強が足りない…。";
			mes "その程度ではウィザードになっても";
			mes "モンスターに簡単にやられるぞ。";
			close;
		}
		mes "ふん…そこそこの出来か…。";
		mes "まあいいだろう。通過だ。";
		mes "一度で通過できなかったが、";
		mes "努力だけは認めてやる。";
		next;
		mes "[ラウレル]";
		mes "まだ安心するなよ。三つ目の試験がある";
		mes "。";
		mes "次の試験の前に休んでおきなさい…。";
		break;
	}
	set CHANGE_WZ,5;
	close;
}


//==========================================
// 三次試験（実技）
//	水×2, 地×2, 火×2の計6段階
//------------------------------------------

job_wiz.gat,50,165,4	script	戦闘進行要員::WZ_ChatRoom	700,{
	mes "[戦闘進行要員]";
	mes "戦闘試験場へようこそ。";
	mes "試験を受ける方は、試験待合室";
	mes "へお入りください。";
	next;
	mes "[戦闘進行要員]";
	mes "他の転職希望者が試験中の場合は";
	mes "そのまましばらくお待ちください。";
	mes "進行状況がアナウンスされますので、";
	mes "前の方が終わったら入場となります。";
	next;
	mes "[戦闘進行要員]";
	mes "お一人様の戦闘試験は";
	mes "約5分から10分程度となります。";
	mes "もし、試験中断をご希望の場合は";
	mes "そのままログアウトしてください。";
	close;
OnInit:
	waitingroom "試験待合室",10,"WZ_ChatRoom::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		set $@wz_tester$,strcharinfo(0);
		donpcevent "WZ_Water1::OnStart";
		warp "job_wiz.gat",116,171;
	}
	else
		enablewaitingroomevent;
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Water1	-1,{
	end;
OnStart:
	set 'count,7;
	monster "job_wiz.gat",118,174,"--ja--",1074,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",118,165,"--ja--",1067,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",109,165,"--ja--",1066,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",109,174,"--ja--",1158,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",126,157,"--ja--",1242,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",101,157,"--ja--",1141,1,"WZ_Water1::OnKilled";
	monster "job_wiz.gat",98,170,"--ja--",1138,1,"WZ_Water1::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		announce "水の部屋: " +$@wz_tester$+ "様、モンスター排除成功",9;
		donpcevent "WZ_Water2::OnStart";
	}
	end;
OnTimer1000:
	announce "水の部屋: 水の部屋、戦闘試験開始です",9;
	end;
OnTimer2000:
	announce "水の部屋: 制限時間は 3分",9;
	end;
OnTimer3000:
	announce "水の部屋: 時間内にすべてのモンスターを排除してください",9;
	end;
OnTimer33000:
	announce "水の部屋: 残り2分 30秒",9;
	end;
OnTimer63000:
	announce "水の部屋: 残り2分",9;
	end;
OnTimer93000:
	announce "水の部屋: 残り1分 30秒",9;
	end;
OnTimer123000:
	announce "水の部屋: 残り1分",9;
	end;
OnTimer153000:
	announce "水の部屋: 残り30秒",9;
	end;
OnTimer173000:
	announce "制限時間まで後 10秒！",9;
	end;
OnTimer183000:
	announce "水の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Water1::OnKilled";
	end;
OnTimer184000:
	announce "水の部屋: " +$@wz_tester$+ "様、モンスター排除失敗",9;
	areawarp "job_wiz.gat",95,150,135,190,"geffen.gat",120,110;
	end;
OnTimer185000:
	announce "水の部屋: 次の方、入場してください",9;
	end;
OnTimer186000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Water2	-1,{
	end;
OnStart:
	set 'count,5;
	monster "job_wiz.gat",114,171,"--ja--",1068,1,"WZ_Water2::OnKilled";
	monster "job_wiz.gat",116,169,"--ja--",1068,1,"WZ_Water2::OnKilled";
	monster "job_wiz.gat",114,167,"--ja--",1068,1,"WZ_Water2::OnKilled";
	monster "job_wiz.gat",112,169,"--ja--",1068,1,"WZ_Water2::OnKilled";
	monster "job_wiz.gat",114,169,"--ja--",1170,1,"WZ_Water2::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		announce "水の部屋: " +$@wz_tester$+ "様、門番モンスター排除成功",9;
		areawarp "job_wiz.gat",95,150,135,190,"job_wiz.gat",116,97;
		donpcevent "WZ_Earth1::OnStart";
	}
	end;
OnTimer1000:
	announce "水の部屋: 門番モンスターが登場しました。制限時間は 1分です",9;
	end;
OnTimer30000:
	announce "水の部屋: 残り30秒",9;
	end;
OnTimer50000:
	announce "水の部屋: 残り10秒",9;
	end;
OnTimer60000:
	announce "水の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Water2::OnKilled";
	end;
OnTimer61000:
	announce "水の部屋: " +$@wz_tester$+ "様、モンスター排除失敗",9;
	areawarp "job_wiz.gat",98,154,129,185,"geffen.gat",120,110;
	end;
OnTimer62000:
	announce "水の部屋: 次の方、入場してください",9;
	end;
OnTimer63000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Earth1	-1,{
	end;
OnStart:
	if( attachrid(getcharid(3,$@wz_tester$)) )
		percentheal 100,100;
	set 'count,8;
	monster "job_wiz.gat",120,102,"--ja--",1127,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",120,102,"--ja--",1105,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",124,98,"--ja--",1023,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",120,93,"--ja--",1121,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",111,93,"--ja--",1166,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",107,98,"--ja--",1060,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",111,102,"--ja--",1057,1,"WZ_Earth1::OnKilled";
	monster "job_wiz.gat",111,102,"--ja--",1103,1,"WZ_Earth1::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		announce "地の部屋: " +$@wz_tester$+ "様、モンスター排除成功",9;
		donpcevent "WZ_Earth2::OnStart";
	}
	end;
OnTimer1000:
	announce "地の部屋: 地の部屋、戦闘試験開始です",9;
	end;
OnTimer2000:
	announce "地の部屋: 制限時間は 3分",9;
	end;
OnTimer3000:
	announce "地の部屋: 時間内にすべてのモンスターを排除してください",9;
	end;
OnTimer33000:
	announce "地の部屋: 残り2分 30秒",9;
	end;
OnTimer63000:
	announce "地の部屋: 残り2分",9;
	end;
OnTimer93000:
	announce "地の部屋: 残り1分 30秒",9;
	end;
OnTimer123000:
	announce "地の部屋: 残り1分",9;
	end;
OnTimer153000:
	announce "地の部屋: 残り30秒",9;
	end;
OnTimer173000:
	announce "地の部屋: 残り10秒",9;
	end;
OnTimer183000:
	announce "地の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Earth1::OnKilled";
	end;
OnTimer184000:
	announce "地の部屋: " +$@wz_tester$+ "様、モンスター排除失敗",9;
	areawarp "job_wiz.gat",95,75,135,120,"geffen.gat",120,110;
	end;
OnTimer185000:
	mapannounce "job_wiz.gat","地の部屋: 次の方、入場してください",9;
	end;
OnTimer186000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Earth2	-1,{
	end;
OnStart:
	set 'count,7;
	monster "job_wiz.gat",116,100,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",118,99,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",118,95,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",116,94,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",114,95,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",114,99,"--ja--",1020,1,"WZ_Earth2::OnKilled";
	monster "job_wiz.gat",116,97,"--ja--",1118,1,"WZ_Earth2::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		announce "地の部屋: " +$@wz_tester$+ "様、門番モンスター排除成功",9;
		areawarp "job_wiz.gat",95,75,135,120,"job_wiz.gat",46,99;
		donpcevent "WZ_Fire1::OnStart";
	}
	end;
OnTimer1000:
	announce "地の部屋: 門番モンスターが登場しました。制限時間は 1分です",9;
	end;
OnTimer30000:
	announce "地の部屋: 残り30秒",9;
	end;
OnTimer50000:
	announce "地の部屋: 残り10秒",9;
	end;
OnTimer60000:
	announce "地の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Earth2::OnKilled";
	end;
OnTimer61000:
	announce "地の部屋: " +$@wz_tester$+ "様、モンスター排除失敗",9;
	areawarp "job_wiz.gat",95,75,135,120,"geffen.gat",120,110;
	end;
OnTimer62000:
	announce "地の部屋: 次の方、入場してください",9;
	end;
OnTimer63000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Fire1	-1,{
	end;
OnStart:
	if( attachrid(getcharid(3,$@wz_tester$)) )
		percentheal 100,100;
	set 'count,7;
	monster "job_wiz.gat",51,103,"--ja--",1119,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",51,92,"--ja--",1033,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",40,92,"--ja--",1019,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",40,103,"--ja--",1001,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",58,110,"--ja--",1178,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",37,89,"--ja--",1058,1,"WZ_Fire1::OnKilled";
	monster "job_wiz.gat",33,110,"ゴブリン",1123,1,"WZ_Fire1::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		announce "火の部屋: " +$@wz_tester$+ "様、モンスター排除成功",9;
		donpcevent "WZ_Fire2::OnStart";
	}
	end;
OnTimer1000:
	announce "火の部屋: 火の部屋、戦闘試験開始です",9;
	end;
OnTimer2000:
	announce "火の部屋: 最後の部屋です。制限時間は 3分",9;
	end;
OnTimer3000:
	announce "火の部屋: 時間内にすべてのモンスターを排除してください",9;
	end;
OnTimer33000:
	announce "火の部屋: 残り2分 30秒",9;
	end;
OnTimer63000:
	announce "火の部屋: 残り2分",9;
	end;
OnTimer93000:
	announce "火の部屋: 残り1分 30秒",9;
	end;
OnTimer123000:
	announce "火の部屋: 残り1分",9;
	end;
OnTimer153000:
	announce "火の部屋: 残り30秒",9;
	end;
OnTimer173000:
	announce "火の部屋: 残り10秒",9;
	end;
OnTimer183000:
	announce "火の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Fire1::OnKilled";
	end;
OnTimer184000:
	announce "火の部屋: " +$@wz_tester$+ "様、モンスター排除失敗",9;
	areawarp "job_wiz.gat",25,75,65,120,"geffen.gat",120,110;
	end;
OnTimer185000:
	announce "火の部屋: 次の方、入場してください",9;
	end;
OnTimer186000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}

//==============================================================
job_wiz.gat,0,0,0	script	WZ_Fire2	-1,{
	end;
OnStart:
	set 'count,3;
	monster "job_wiz.gat",43,99,"--ja--",1129,1,"WZ_Fire2::OnKilled";
	monster "job_wiz.gat",45,99,"--ja--",1129,1,"WZ_Fire2::OnKilled";
	monster "job_wiz.gat",44,99,"--ja--",1277,1,"WZ_Fire2::OnKilled";
	initnpctimer;
	end;
OnKilled:
	set 'count,'count-1;
	if('count <= 0) {
		stopnpctimer;
		killmonster "job_wiz.gat","WZ_Fire2::OnKilled";
		set CHANGE_WZ,12;
		announce "火の部屋: おめでとうございます！ " +$@wz_tester$+ "様が試験に合格しました。",9;
		areawarp "job_wiz.gat",95,75,135,120,"job_wiz.gat",46,99;
		sleep 3000;
		announce "試験終了: 試験官の元に戻り、残りの手続きを終えてください",9;
		sleep 3000;
		announce "試験終了: 試験を終わります。次の受験者は用意してください",9;
		areawarp "job_wiz.gat",30,82,61,113,"gef_tower.gat",110,33;
		sleep 1000;
		announce "試験終了: 次の方、入場してください",9;
		sleep 1000;
		enablewaitingroomevent "WZ_ChatRoom";
		end;
	}
	end;
OnTimer1000:
	announce "火の部屋: 門番モンスターが登場しました。制限時間は 2分です",9;
	end;
OnTimer30000:
	announce "火の部屋: 残り1分 30秒",9;
	end;
OnTimer60000:
	announce "火の部屋: 残り1分",9;
	end;
OnTimer90000:
	announce "火の部屋: 残り30秒",9;
	end;
OnTimer110000:
	announce "火の部屋: 残り10秒",9;
	end;
OnTimer120000:
	announce "火の部屋: 終了",9;
	killmonster "job_wiz.gat","WZ_Fire2::OnKilled";
	end;
OnTimer121000:
	announce $@wz_tester$+ "様が試験に失敗しました！",9;
	areawarp "job_wiz.gat",25,75,65,120,"geffen.gat",120,110;
	end;
OnTimer122000:
	announce "火の部屋: 次の方、入場してください",9;
	end;
OnTimer123000:
	stopnpctimer;
	enablewaitingroomevent "WZ_ChatRoom";
	end;
}
