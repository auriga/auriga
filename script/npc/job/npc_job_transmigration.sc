//====================================================================
//Ragnarok Online - Transmigration NPC Script	by Blaze
//
//　■ TRANSMIGRATE -> 0～2
//　   OLD_CLASS    -> 転生前の職業を保存
//====================================================================

//==========================================
// セージキャッスル
//------------------------------------------

yuno_in02.gat,88,164,5	script	メテウスシルプ	742,{
	if(TRANSMIGRATE == 0) {
		if(BaseLevel < 99 || JobLevel < 50 || Class < CLASS_KN || Class > CLASS_CR2) {
			mes "[メテウスシルプ]";
			mes "いらっしゃいませ。";
			mes "こちらはシュバイチェル";
			mes "魔法アカデミー図書館です。";
			mes "ここには貴重な書籍が";
			mes "たくさんあります。";
			mes "ゆっくりご見学ください。";
			close;
		}
		mes "[メテウスシルプ]";
		mes "いらっしゃいませ。";
		mes "こちらはシュバイチェル";
		mes "魔法アカデミー図書館です。";
		mes "今回ご来館されたのは、";
		mes "「ユミルの書」をお読みになる";
		mes "ためでしょう？";
		next;
		mes "[メテウスシルプ]";
		mes "ユミルの書は印刷物としても";
		mes "公開しております。";
		mes "それでも時々、直接読みたいと";
		mes "おっしゃる方がいます……";
		next;
		mes "[メテウスシルプ]";
		mes "しかし原本の状態があまり";
		mes "良くありません。";
		mes "そこで閲覧をご希望の方には、";
		mes "寄付金を頂くことによって";
		mes "特別に許可をしております。";
		next;
		mes "[メテウスシルプ]";
		mes "寄付金は1,285,000Zenyです。";
		mes "これは書籍の安全な保存と";
		mes "古書籍研究に利用させて頂きます。";
		mes "申し訳ありませんが、閲覧を";
		mes "ご希望でしたらお納めください。";
		mes "ご寄付なさいますか？";
		next;
		if(select("寄付する","やめる")==2) {
			mes "[メテウスシルプ]";
			mes "ゆっくりご見学ください。";
			mes "楽しい旅行になるとよいですね。";
			close;
		}
		if(Zeny < 1285000) {
			mes "[メテウスシルプ]";
			mes "少々持ち合わせが足りないようですね。";
			mes "所持金を再度ご確認なさってから";
			mes "お越しください。";
			close;
		}
		set Zeny,Zeny-1285000;
		set TRANSMIGRATE,1;
		setquest 1000;
	}
	mes "[メテウスシルプ]";
	mes "ありがとうございます。";
	mes "寄付金は当アカデミーの研究資金として";
	mes "大切に使わせて頂きます。";
	mes "では、どうぞ中へお入りください。";
	close;
}

//==============================================================
yuno_in02.gat,93,207,0	script	ユミルの書	111,{
	if(Upper == UPPER_HIGH) {
		mes "[ユミルの書]";
		mes "……栄光の神殿への入り口は";
		mes "生まれ変わりし者全てに開かれている。";
		mes "英雄が歩む道への手助けとして";
		mes "世界中どこでも開かれている。";
		next;
		mes "[ユミルの書]";
		mes "そこでは、彼らの為にあらゆる";
		mes "準備がなされている。";
		mes "更に現実では成すことができぬ";
		mes "願いすらも、その神殿では";
		mes "成就できると言われている。";
		next;
		if(select("読むのをやめる","続きを読む")==1) {
			mes "[ユミルの書]";
			mes "…………";
			close;
		}
		mes "[ユミルの書]";
		mes "空に一番近き場所。そこに";
		mes "ヴァルキリーの神殿へ通じる道ありき。";
		mes "だが、資格なき者は永遠に";
		mes "知ることはできぬ。";
		close2;
		warp "valkyrie.gat",48,8;
		end;
	}
	if(TRANSMIGRATE == 0) {
		mes "[ユミルの書]";
		mes "…………";
		close;
	}
	mes "[ユミルの書]";
	mes "……そして先代の幾多の業績の数々と";
	mes "共に疑問視されたことは、英雄達にも";
	mes "不可避に迫り来る「死」という";
	mes "問題であった。英雄といえども";
	mes "最期の瞬間は必ず訪れるものであろう。";
	next;
	mes "[ユミルの書]";
	mes "しかしどんな英雄にまつわる詩や";
	mes "記録、口頭による伝承さえも、";
	mes "その最期の記録は残っていなかった。";
	mes "これに対し一つ注目する点がある。";
	mes "それは「ラグナロク」に記述された";
	mes "ヴァルキリーに関する内容だ。";
	next;
	mes "[ユミルの書]";
	mes "人間として最上の時に最高の資質を";
	mes "持ちし者。その者は最終聖戦において";
	mes "戦士として戦った。そしてその魂は";
	mes "ヴァルキリーの導きにより、";
	mes "ヴァルハラへ向かったようである。";
	mes "これは普通の人々の最期とは異なる。";
	next;
	mes "[ユミルの書]";
	mes "英雄達は輪廻することによって";
	mes "真の英雄として生まれ変わり、";
	mes "新たな時代へ光明を照らす者となる。";
	mes "そして倒れし肉体は再び蘇り、";
	mes "魂は新しい能力を得るであろう。";
	next;
	mes "[ユミルの書]";
	mes "しかし不幸にも、ユミルの心臓は";
	mes "聖戦後、大陸全土へ消失してしまった。";
	mes "そこで私は様々な方法によって";
	mes "更なる解明を目指した。だが……";
	next;
	mes "[ユミルの書]";
	mes "残念ながらこれ以上";
	mes "何も知ることができなかった。";
	mes "それゆえ私はここに記録を残そう。";
	next;
	mes "[ユミルの書]";
	mes "後代の誰かがこの記録を見つけ出し、";
	mes "その意志と希望、時代の最後の光を";
	mes "見出す英雄として生まれ変わることを、";
	mes "そして今一度ヴァルキリーの神殿で";
	mes "英雄達を導く者が現われることを";
	mes "切に待ち望む。またその後に……";
	set TRANSMIGRATE,2;
	close;
}

//==============================================================
yuno_in05.gat,49,43,0	script	ユミルの心臓	111,{
	if(TRANSMIGRATE == 2)
		warp "valkyrie.gat",48,8;
	end;
}


//==========================================
// ヴァルキリー神殿
//------------------------------------------

valkyrie.gat,48,86,4	script	ヴァルキリー	811,{
	if(Upper != UPPER_NORMAL) {
		mes "[ヴァルキリー]";
		mes "栄光のヴァルハラへよくぞ";
		mes "お越しくださいました。";
		mes "少しお体を休ませるとよいでしょう。";
		mes "戦士達に光あれ！";
		close;
	}
	mes "[ヴァルキリー]";
	mes "栄光のヴァルハラへよくぞ";
	mes "お越しくださいました。";
	mes "これから現在までの生を整理し、";
	mes "新たな生を得ることになります。";
	mes "戦士達に光あれ！";
	next;
	if(Weight || checkcart() || checkfalcon() || checkriding() || sc_ison(SC_ALL_RIDING)) {
		mes "[ヴァルキリー]";
		mes "あなたは準備しなければ";
		mes "ならないことがあります。";
		mes "しばしお休みください……";
		mes "そして、身と心を無にしてください。";
		mes "名誉というのは無心の時に";
		mes "表れるものですから。";
		next;
		mes "[ヴァルキリー]";
		mes "アイテムやお金……何も持たない";
		mes "空の状態でなければなりません。";
		mes "旅を共にした動物達やカートなども";
		mes "持って行くことはできません。";
		mes "それでは……用意ができましたら";
		mes "お越しください。";
		close2;
		warp "yuno_in02.gat",93,205;
		end;
	}
	mes "[ヴァルキリー]";
	mes "身も心も無にしましたね。";
	mes "……綺麗なお心です。";
	mes "無心になった今、あなたの";
	mes "名誉がよく表れております。";
	next;
	if(SkillPoint) {
		mes "[ヴァルキリー]";
		mes "……未練があるようですね。";
		mes "地上へ戻り、その未練を全て";
		mes "お捨てになってからお越しください。";
		close2;
		warp "yuno_in02.gat",93,205;
		end;
	}
	mes "[ヴァルキリー]";
	mes "お眠りなさい……";
	mes "あなたに刻まれている";
	mes "過去の記憶を消し、";
	mes "あなたの精神に";
	mes "現在までの栄光の証を";
	mes "記憶させます。";
	next;
	mes "[ヴァルキリー]";
	mes "では……";
	mes "一つ、ウルドに過去の記憶を残します。";
	mes "二つ、ヴェルダンディに現在の";
	mes "栄光の瞬間を憶えてもらいます。";
	mes "三つ、スクルドに未来への生を";
	mes "与えさせるようにします。";
	next;
	mes "[ヴァルキリー]";
	mes "一つ";
	next;
	mes "[ヴァルキリー]";
	mes "二つ……";
	next;
	mes "[ヴァルキリー]";
	mes "三つ……";
	set OLD_CLASS,Job;
	jobchange Job_Novice,UPPER_HIGH;
	set BaseLevel,1;
	resetstatus;
	resetskill;
	setoption 0x0000;
	skill 143,1,0;
	skill 142,1,0;
	set SkillPoint,0;
	set StatusPoint,100;
	set TRANSMIGRATE,0;
	chgquest 1000,50000;
	next;
	getitem 1202,1;
	getitem 2302,1;
	mes "[ヴァルキリー]";
	mes "おめでとうございます。";
	mes "全ての儀式が終了いたしました。";
	mes "こちらは、新たな道を歩む";
	mes "戦士へのささやかな贈り物です。";
	next;
	mes "[ヴァルキリー]";
	mes "くれぐれも、過去のウルドが";
	mes "記憶したあなたの生が無駄に";
	mes "ならないようにして欲しいと思います。";
	mes "また現在のヴェルダンディが記憶した";
	mes "あなたの栄光が再現することを、";
	next;
	mes "[ヴァルキリー]";
	mes "そして未来のスクルドが記憶した";
	mes "あなたの新たな生に光あることを";
	mes "願います。";
	close2;
	switch(OLD_CLASS) {
		case Job_Knight:
		case Job_Crusader:
			warp "izlude.gat",94,103;
			break;
		case Job_Priest:
		case Job_Monk:
			warp "prontera.gat",273,354;
			break;
		case Job_Wizard:
		case Job_Sage:
			warp "geffen.gat",120,100;
			break;
		case Job_Blacksmith:
		case Job_Alchemist:
			warp "alberta.gat",116,57;
			break;
		case Job_Hunter:
		case Job_Bard:
		case Job_Dancer:
			warp "payon.gat",160,58;
			break;
		case Job_Assassin:
		case Job_Rogue:
			warp "morocc.gat",160,94;
			break;
	}
	end;
}

//==============================================================
valkyrie.gat,44,33,5	script	テレポーター	124,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[テレポーター]";
			mes "転生おめでとう！";
			mes "戦士達に光あれ！";
		}
		else {
			mes "[テレポーター]";
			mes "展示品に触らないで！";
		}
		close;
	}
	mes "[テレポーター]";
	mes "戦士、どこへ帰りたい？";
	next;
	switch (select("プロンテラ","モロク","フェイヨン","ゲフェン","アルベルタ","イズルード","アルデバラン","コモド","ジュノー")) {
		case 1: savepoint "prontera.gat",116,72; 	break;
		case 2: savepoint "morocc.gat",156,46; 		break;
		case 3: savepoint "payon.gat",160,58; 		break;
		case 4: savepoint "geffen.gat",120,39; 		break;
		case 5: savepoint "alberta.gat",117,56; 	break;
		case 6: savepoint "izlude.gat",91,105; 		break;
		case 7: savepoint "aldebaran.gat",160,109; 	break;
		case 8: savepoint "comodo.gat",209,143; 	break;
		case 9: savepoint "yuno.gat",328,101; 		break;
	}
	warp "SavePoint",0,0;
	end;
}

//==============================================================
valkyrie.gat,44,39,5	script	ロードナイト	56,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[ロードナイト]";
			mes "転生おめでとう！";
			mes "戦士に光あれ！";
		}
		else {
			mes "[ロードナイト]";
			mes "皆、君を評価している。";
			mes "君に異を唱える者は誰もいない。";
			mes "あとは君自身の評価だな。";
			mes "君の評価は……";
			next;
			mes "[ロードナイト]";
			mes "よし、大丈夫だな。";
		}
		close;
	}
	callfunc "JobChanger","ロードナイト",Job_Swordman,Job_Knight;
	mes "[ロードナイト]";
	mes "栄光のヴァルハラへよく来たな。";
	mes "しばし休息をとりたまえ。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,44,42,5	script	ハイプリースト	60,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[ハイプリースト]";
			mes "転生のお祝いを申し上げます。";
			mes "英雄に祝福を！";
		}
		else {
			mes "[ハイプリースト]";
			mes "神よ、今ここに立つ者に";
			mes "祝福の鐘をお鳴らしください。";
			mes "そしてこの者が奥深き意志を";
			mes "地上へ広める為の力を";
			mes "お与えください。";
		}
		close;
	}
	callfunc "JobChanger","ハイプリースト",Job_Acolyte,Job_Priest;
	mes "[ハイプリースト]";
	mes "栄光のヴァルハラへよくぞ";
	mes "お越しくださいました。";
	mes "是非、休息をおとりください。";
	mes "戦士に祝福を！";
	close;
}

//==============================================================
valkyrie.gat,44,47,5	script	ハイウィザード	735,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[ハイウィザード]";
			mes "転生おめでとうございます。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[ハイウィザード]";
			mes "君も正式なハイウィザードですから、";
			mes "ハイウィザードらしい行動を";
			mes "心がけてください。";
			mes "私達ハイウィザードは";
			mes "強力な魔法を持つゆえ、控え目に";
			mes "行動しなければなりません。";
		}
		close;
	}
	callfunc "JobChanger","ハイウィザード",Job_Magician,Job_Wizard;
	mes "[ハイウィザード]";
	mes "栄光のヴァルハラへようこそ。";
	mes "しばし休息をおとりください。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,44,50,5	script	ホワイトスミス	731,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[ホワイトスミス]";
			mes "転生おめでとう！";
			mes "戦士に光あれ！";
		}
		else {
			mes "[ホワイトスミス]";
			mes "配達ご苦労様。";
			mes "ほれ"+strcharinfo(0)+"、領収書だ。";
			mes "ん？なんだ違うのか。";
		}
		close;
	}
	callfunc "JobChanger","ホワイトスミス",Job_Merchant,Job_Blacksmith;
	mes "[ホワイトスミス]";
	mes "栄光のヴァルハラによく来たな。";
	mes "まあ、少し休んでいけよ。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,44,55,5	script	スナイパー	727,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[スナイパー]";
			mes "転生お祝い申し上げます。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[スナイパー]";
			mes "^6B8C21では、転職試験を始めましょう。";
			mes "たくさんいるモンスターの中で";
			mes "名前が「転職試験用モンスター」のみを";
			mes "倒してください。あと";
			mes "- 落とし穴に気をつけてください。 -^000000";
			mes "ん？違いましたか？";
		}
		close;
	}
	callfunc "JobChanger","スナイパー",Job_Archer,Job_Hunter;
	mes "[スナイパー]";
	mes "栄光のヴァルハラへようこそ。";
	mes "是非おくつろぎください。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,44,58,5	script	アサシンクロス	725,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[アサシンクロス]";
			mes "転生お祝い申し上げる。";
			mes "幸運を祈る！";
		}
		else {
			mes "[アサシンクロス]";
			mes "誰が何と言おうと「砂漠の牙」としての";
			mes "プライドは大事にしろ！";
			mes "決してプライドを捨てるなよ！";
		}
		close;
	}
	callfunc "JobChanger","アサシンクロス",Job_Thief,Job_Assassin;
	mes "[アサシンクロス]";
	mes "ヴァルハラへよく来たな。";
	mes "少し休んでいけ。";
	mes "幸運を祈る！";
	close;
}

//==============================================================
valkyrie.gat,53,39,3	script	パラディン	752,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[パラディン]";
			mes "転生の祝いを申し上げよう。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[パラディン]";
			mes "聖戦が近づきつつあることを決して";
			mes "忘れずに、絶えず己を鍛えなさい！";
			mes "君にオーディンのご加護があるように！";
			mes "さあ、行きなさい！";
		}
		close;
	}
	callfunc "JobChanger","パラディン",Job_Swordman,Job_Crusader;
	mes "[パラディン]";
	mes "栄光のヴァルハラへよくぞ来た。";
	mes "少し休んでいきなさい。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,53,42,3	script	チャンピオン	52,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[チャンピオン]";
			mes "転生おめでとう！";
			mes "戦士に光あれ！";
		}
		else {
			mes "[チャンピオン]";
			mes "ではこれから換骨奪胎の儀を行う。";
			next;
			mes "[チャンピオン]";
			mes "……おい。お前は既に";
			mes "転職してるじゃないか。";
		}
		close;
	}
	callfunc "JobChanger","チャンピオン",Job_Acolyte,Job_Monk;
	mes "[チャンピオン]";
	mes "栄光のヴァルハラへよく来た。";
	mes "少し休んでいきな。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,53,47,3	script	プロフェッサー	743,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[プロフェッサー]";
			mes "転生おめでとう。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[プロフェッサー]";
			mes "論文は大切に保管しなさい。";
			mes "君が書いた大事な書物だからね。";
			mes "いつかそれが役立つことも";
			mes "あるでしょう。";
			mes "読み返して記憶しておきなさい。";
		}
		close;
	}
	callfunc "JobChanger","プロフェッサー",Job_Magician,Job_Sage;
	mes "[プロフェッサー]";
	mes "栄光のヴァルハラによくぞ来ました。";
	mes "しばしの休息を得なさい。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,53,58,3	script	チェイサー	747,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[チェイサー]";
			mes "転生おめでと～！";
			mes "幸運を祈るよ！";
		}
		else {
			mes "[チェイサー]";
			mes "そうそう、合言葉は";
			mes "^3333FFアラガムは精錬用品を";
			mes "横領していない^000000だよ。";
			mes "な～んてね。あはは！";
		}
		close;
	}
	callfunc "JobChanger","チェイサー",Job_Thief,Job_Rogue;
	mes "[チェイサー]";
	mes "ヴァルハラへよく来たな～！";
	mes "ちょいと休みなよ。";
	mes "幸運を祈る！";
	close;
}

//==============================================================
valkyrie.gat,53,50,3	script	クリエイター	122,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[クリエイター]";
			mes "転生おめでとう。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[クリエイター]";
			mes "突然だが、質問だ。";
			mes "防具商人からヘルム5個を";
			mes "ディスカウント24%で買った場合と";
			mes "ディスカウント20%で買った場合の";
			mes "金額の差はいくらか？";
			mes "どうだ？こんなの簡単だろ。";
		}
		close;
	}
	callfunc "JobChanger","クリエイター",Job_Merchant,Job_Alchemist;
	mes "[クリエイター]";
	mes "栄光のヴァルハラへようこそ！";
	mes "少しここで休んでいきな。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,53,54,3	script	クラウン	741,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[クラウン]";
			mes "転生お祝い申し上げます。";
			mes "戦士に光あれ！";
		}
		else {
			mes "[クラウン]";
			mes "私と一緒に歌ってみましょう。";
			mes "この曲なんかどうです？";
		}
		close;
	}
	callfunc "JobChanger","クラウン",Job_Archer,Job_Bard;
	mes "[クラウン]";
	mes "栄光のヴァルハラへようこそ。";
	mes "少しここで休息をとるとよいでしょう。";
	mes "戦士に光あれ！";
	close;
}

//==============================================================
valkyrie.gat,53,56,3	script	ジプシー	101,{
	if(Upper != UPPER_HIGH) {
		if(rand(3)) {
			mes "[ジプシー]";
			mes "転生おめでとう！";
			mes "戦士に光あれ！";
		}
		else {
			mes "[ジプシー]";
			mes "はい左、みーぎ : [→]";
			mes "…………";
		}
		close;
	}
	callfunc "JobChanger","ジプシー",Job_Archer,Job_Dancer;
	mes "[ジプシー]";
	mes "栄光のヴァルハラへようこそ！";
	mes "少し休んでから帰りなさいな。";
	mes "戦士に光あれ！";
	close;
}


//==========================================
// 転生二次転職ファンクション
//	callfunc "JobChanger","Name",1stClass,2ndClass
//------------------------------------------

function	script	JobChanger	{
	if(JobLevel < 40 || Job != getarg(1) || OLD_CLASS != getarg(2))
		return;
	mes "["+getarg(0)+"]";
	mes "本来の姿を取り戻し、";
	mes "世界に新たな光をもたらす";
	mes "時が訪れました。";
	mes "新たな姿であなたの道を";
	mes "歩んでください。";
	next;
	mes "["+getarg(0)+"]";
	mes getarg(0)+"に";
	mes "転職なさいますか？";
	next;
	if(select("いいえ","はい")==1) {
		mes "["+getarg(0)+"]";
		mes "準備ができましたら、";
		mes "再度私をお訪ねください。";
		mes "英雄に祝福を！";
		close;
	}
	if(sc_ison(SC_ALL_RIDING)) {
		mes "‐騎乗生物を利用した状態では";
		mes "　進行できません。";
		mes "　騎乗生物から降りてください‐";
		close;
	}
	if(SkillPoint) {
		mes "["+getarg(0)+"]";
		mes "まだ学ばなければならないことが";
		mes "おありのようですね。";
		mes "スキルポイントを全て消費してから";
		mes "お越しください。";
		close;
	}
	unequip;
	jobchange getarg(2),UPPER_HIGH;
	if(getbaseclass(Class,2) == CLASS_AM && SKILL_BIOETHICS == 13) {
		skill 238,1,0;
		set SKILL_BIOETHICS,0;
	}
	mes "["+getarg(0)+"]";
	mes "お祝い申し上げます。";
	mes "地上へ戻り、あなたのお力で";
	mes "人々をお導きください。";
	close;
}
