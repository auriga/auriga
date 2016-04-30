//====================================================================
//Ragnarok Online Crusader jobchange script
//
//　■ CHANGE_CRU -> 0～10
//====================================================================

//==========================================
// 試験申請および転職
//------------------------------------------

prt_castle.gat,45,169,4	script	マスタークルセイダー	752,{
	if(Job == Job_Crusader) {
		mes "[ミケル=レカント=ニキータ]";
		mes "貴公は聖戦に拠り為す者か。";
		mes "ここに留まらず己を鍛えるがよい。";
		mes "修練積む者には勝利の光が射す。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "世界の危機は、いつ訪れるか";
		mes "わからない。オーディンの意志を";
		mes "継ぎ魔族を退け、我ら人間の";
		mes "理想郷を建設するその日まで";
		mes "怠らず己を鍛えなさい。";
		close;
	}
	switch(CHANGE_CRU) {
	case 0:
		mes "[ミケル=レカント=ニキータ]";
		mes "私たちはクルセイダー。";
		mes "オーディンの意志によって";
		mes "聖戦に備える者だ。";
		if(Upper == UPPER_HIGH) {
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "千年前のように、またいつか";
			mes "魔族を討伐する日が来るだろう……";
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "貴公はここにいるべき者ではない。";
			mes "怠らず己を鍛えなさい。";
			close;
		}
		if(Job == Job_Novice) {
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "君も我らに賛同したくば、";
			mes "剣士として十分な修練を";
			mes "積んで来るように……";
			close;
		}
		if(Job != Job_Swordman) {
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "千年前のように、またいつか";
			mes "魔族を討伐する日が来るだろう……";
			close;
		}
		mes "何の事で訪ねてきたのか";
		next;
		if(select("私も聖戦に加わりたい","なんでもないです")==2) {
			mes "[ミケル=レカント=ニキータ]";
			mes "君も剣を扱う者ならば";
			mes "絶え間ない修練を心がけなさい。";
			mes "聖戦の時は誰にもわからない。";
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "今は理解できなくとも";
			mes "君にもオーディンの声が";
			mes "届く時がくるかもしれない。";
			close;
		}
		mes "[ミケル=レカント=ニキータ]";
		mes "君、クルセイダーになりたいと";
		mes "言うのか？";
		mes "我々と歩むことはそんなに";
		mes "たやすいことではないぞ。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "私はミケル=レカント=ニキータ。";
		mes "聖戦に備える者の一人だ。";
		mes "我々は厚い信頼と果てしなき";
		mes "忠誠心の元で絶えず己を";
		mes "鍛えている。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "剣士の中でも頼もしい者から";
		mes "頼もしい者を選抜しているが、";
		mes "オーディンの意志により戦士と";
		mes "して生まれた者ならば我々に";
		mes "賛同することを勧める。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "特に、^3152FF忠節の証^000000と^3152FF聖痕^000000を持つ";
		mes "剣士はクルセイダーたる素質を";
		mes "天から与えられたのである。";
		mes "そんな剣士は、ある試練を";
		mes "乗り越えればクルセイダーとなる";
		mes "ことができる。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "私にはまだ、君がどんな素質を";
		mes "持っているか図りかねる。";
		mes "一度試練に挑戦してみないか？";
		next;
		if(select("はい、やってみます","考えさせてください")==2) {
			mes "[ミケル=レカント=ニキータ]";
			mes "そうか。";
			mes "良く準備を整えてから来なさい。";
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "オーディンの声が聞こえたら";
			mes "すぐに試練を受けに来るように。";
			close;
		}
		if(JobLevel < 40) {
			mes "[ミケル=レカント=ニキータ]";
			mes "気の毒だが……";
			mes "クルセイダーになる前に";
			mes "JobLvを40以上にしなければ";
			mes "ならない。";
			next;
			mes "[ミケル=レカント=ニキータ]";
			mes "剣士としてもう少し修練を積み";
			mes "オーディンの声がかかるのを";
			mes "待つのだ。";
			mes "その気鋭は認めるがな……";
			close;
		}
		if(SkillPoint) {
			mes "[ミケル=レカント=ニキータ]";
			mes "うむ……君はまだ剣士として";
			mes "取得できるスキルが残って";
			mes "いるようだ。他のスキルを習得";
			mes "してからまたこい。";
			close;
		}
		mes "[ミケル=レカント=ニキータ]";
		mes "それでは、君がクルセイダーに";
		mes "ふさわしい者かどうかを";
		mes "見させてもらおう。";
		mes "名前は" +strcharinfo(0)+ "か。";
		next;
		if(countitem(1004) && countitem(1009))	//忠節の証と聖痕所持時
			break;
		mes "[ミケル=レカント=ニキータ]";
		mes "うむ……";
		mes "君のクルセイダーとしての素質は";
		mes "いまいち図りかねる……";
		mes "しかしその意志だけは伝わってきた。";
		mes "努力することによりそれを証明して";
		mes "見せよ。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "君にはこれらの物を集めてもらおう。";
		set CHANGE_CRU,rand(1,3);
		switch(CHANGE_CRU) {
			case 1:
				mes "^3152FF亡者の爪^000000 10個";
				mes "^3152FFくさった鱗^000000 10個";
				mes "^3152FFボロボロ囚人服^000000 10個";
				mes "^3152FFピッグテールリボン^000000 10個";
				break;
			case 2:
				mes "^3152FFスケルボーン^000000 10個";
				mes "^3152FFオークの爪^000000 10個";
				mes "^3152FF手錠^000000 10個";
				mes "^3152FF短いピッグテールリボン^000000 10個";
				break;
			case 3:
				mes "^3152FF亡者の牙^000000 10個";
				mes "^3152FFくさった包帯^000000 10個";
				mes "^3152FFランタン^000000 10個";
				mes "^3152FFカボチャの頭^000000 10個";
				break;
		}
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "君の努力しだいで、クルセイダー";
		mes "への試練を受けてもらうかどうかを";
		mes "決める。";
		mes "では行ってくるように。";
		mes "君にオーディンの加護があらんことを。";
		close;
	case 1:
	case 2:
	case 3:
		mes "[ミケル=レカント=ニキータ]";
		mes "君はオーディンの声を聞いた者か？";
		mes "または己の努力を証明しに";
		mes "来た者か？";
		next;
		if(countitem(1004) && countitem(1009))	//忠節の証と聖痕所持時
			break;
		switch(CHANGE_CRU) {
			case 1:	setarray '@need,957,959,1099,901; 	break;
			case 2:	setarray '@need,932,1043,1098,1094; 	break;
			case 3:	setarray '@need,958,930,1041,1062; 	break;
		}
		for(set '@i,0; '@i<4; set '@i,'@i+1) {
			if(countitem('@need['@i]) < 10) {
				mes "[ミケル=レカント=ニキータ]";
				mes "君を見るに、まだクルセイダーと";
				mes "しての資質が見受けられない。";
				mes "君の意志を見せたくば、";
				mes "努力を以って見せてみよ。";
				next;
				mes "[ミケル=レカント=ニキータ]";
				mes "君にはこれらの物を集めてもらおう。";
				for(set '@i,0; '@i<4; set '@i,'@i+1)
					mes "^3152FF" +getitemname('@need['@i])+ "^000000 10個";
				next;
				mes "[ミケル=レカント=ニキータ]";
				mes "もう少し努力した姿を見せてほしい。";
				mes "では行ってくるように。";
				mes "君にオーディンの加護があらんことを。";
				close;
			}
		}
		mes "[ミケル=レカント=ニキータ]";
		mes "よし！努力したな！";
		mes "君の努力を認め、クルセイダーへの";
		mes "試練を受けることを認めよう。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "ムルナク=ミヨオに会ってみよ。";
		mes "このプロンテラ城地下監獄に居る。";
		mes "まずは彼と会って話をするのだ。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "彼が君のすべきことを";
		mes "教えてくれるだろう。";
		mes "すべての試練が終わったら";
		mes "また私の元へ戻ってこい。";
		for(set '@i,0; '@i<4; set '@i,'@i+1)
			delitem '@need['@i],10;
		set CHANGE_CRU,4;
		close;
	default:	//4～9のとき
		mes "[ミケル=レカント=ニキータ]";
		mes "君はまだすべての試練を";
		mes "達成していない。";
		mes "今の君にクルセイダーになる";
		mes "資質があるかもわからない。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "全ての試練を達成してから";
		mes "また来るように。";
		mes "その時評価を下す。";
		close;
	case 10:
		if(SkillPoint) {
			mes "[ミケル=レカント=ニキータ]";
			mes "うむ……君はまだ剣士として";
			mes "取得できるスキルが残って";
			mes "いるようだ。他のスキルを習得";
			mes "してからまたこい。";
			close;
		}
		mes "[ミケル=レカント=ニキータ]";
		mes "君は全ての試練を乗り越えた！";
		mes "立派だ。";
		mes "もう心身共に、我々と聖戦に備える";
		mes "ことができる。";
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "おめでとう。";
		mes "今、君は我々の同志として";
		mes "生まれ変わったのだ。";
		set '@amount,(JobLevel >= 50)? 12: 6;
		unequip;
		jobchange Job_Crusader;
		set CHANGE_CRU,0;
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "そしてこれは緊急を要す場合に";
		mes "使うと良い……。";
		mes "私たちクルセイダーに、今一度";
		mes "戦う力を与えてくれるだろう。";
		getitem 504,'@amount;
		next;
		mes "[ミケル=レカント=ニキータ]";
		mes "聖戦がおとずれることを常に";
		mes "頭に入れ、修練を続けなさい。";
		mes "君にオーディンの加護があらんことを。";
		mes "では行きなさい！";
		close;
	}
	mes "[ミケル=レカント=ニキータ]";
	mes "うむ……";
	mes "君の中にクルセイダーとしての";
	mes "素質を垣間見た気がする。";
	mes "しかしそれだけではまだ";
	mes "わからない。試練を受けてもらう。";
	next;
	mes "[ミケル=レカント=ニキータ]";
	mes "ムルナク=ミヨオに会ってみよ。";
	mes "このプロンテラ城地下監獄に居る。";
	mes "まずは彼と会って話をするのだ。";
	next;
	mes "[ミケル=レカント=ニキータ]";
	mes "彼が君のすべきことを";
	mes "教えてくれるだろう。";
	mes "すべての試練が終わったら";
	mes "また私の元へ戻ってこい。";
	delitem 1004,1;
	delitem 1009,1;
	set CHANGE_CRU,4;
	close;
}


//==========================================
// 一次試験（忍耐力試験）
//------------------------------------------

prt_castle.gat,164,32,0	script	苦しむ者	733,{
	if(Job == Job_Novice) {
		mes "[ムルナク=ミヨオ]";
		mes "ノービスですか……";
		mes "私は悪者ではありません。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "自分を鍛えるためこちらに";
		mes "入っているのです。";
		close;
	}
	if(Job == Job_Crusader) {
		mes "[ムルナク=ミヨオ]";
		mes "こんな所で立ち止まらず";
		mes "前に進みなさい。";
		mes "いつか私達皆が剣を取り";
		mes "戦うその日まで……";
		close;
	}
	if(Job != Job_Swordman) {
		mes "[ムルナク=ミヨオ]";
		mes "気が散ります。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "私の修練の邪魔をしないでください。";
		close;
	}
	switch(CHANGE_CRU) {
	default:	//0～3のとき
		mes "[ムルナク=ミヨオ]";
		mes "なんですか？";
		mes "特に用が無いならば、こちらから";
		mes "出ていってください……";
		mes "修練中の私に必要なのは、";
		mes "何より「静けさ」なのだから。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "いつか迫ってくる聖戦のために";
		mes "常に平常心を保たなければならない。";
		mes "ですから、席をはずしてください。";
		close;
	case 4:
		mes "[ムルナク=ミヨオ]";
		mes "何の用ですか？";
		mes "修練中の私に何か用でもおありですか？";
		next;
		if(select("クルセイダーになりたいんです","なんでもないです")==2) {
			mes "[ムルナク=ミヨオ]";
			mes "暇なんですか？";
			mes "こんなところで遊んでいないで";
			mes "表に出てゼロピーでも拾って";
			mes "いなさい。";
			close;
		}
		mes "[ムルナク=ミヨオ]";
		mes "クルセイダー志望者か……";
		mes "めずらしい……";
		mes "私の名前はムルナク=ミヨオ";
		mes "聖戦への準備をする一人だ。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "名前は……";
		mes strcharinfo(0)+ "ですか。";
		mes "よく姿を見せてください。";
		next;
		if(equippeditem(2608) < 1) {	//ロザリー未装備
			mes "[ムルナク=ミヨオ]";
			mes "しかし！";
			mes "クルセイダーになろうという者が";
			mes "ロザリーも身につけていないとは";
			mes "どういうことですか。";
			mes "そんな心構えの方に私から";
			mes "話すことはありません。";
			next;
			mes "[ムルナク=ミヨオ]";
			mes "外に出て行きなさい。";
			close;
		}
		mes "[ムルナク=ミヨオ]";
		mes "なるほど……";
		mes "心構えは良いでしょう。";
		mes "それだけでクルセイダーに";
		mes "なれるわけではありませんが。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "では、まずあなたの忍耐力を";
		mes "見ることにしましょう。";
		mes "クルセイダーには物事に耐える";
		mes "強い精神力が必要なのです。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "すぐに始めましょう。";
		mes "なに、さほど難しくもありません。";
		mes "ただ道を最後まで進むだけで";
		mes "良いのですから……";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "一つだけ肝に銘じておいて";
		mes "ほしいことがあります。";
		mes "何があってもモンスターを";
		mes "倒してはいけません。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "それでは行きなさい。";
		break;
	case 5:
		mes "[ムルナク=ミヨオ]";
		mes "先ほどの剣士よ、何の用事ですか？";
		mes "ふむ……失敗しましたか……";
		next;
		if(select("また挑戦させてください","これはどういう試練ですか？")==2) {
			mes "[ムルナク=ミヨオ]";
			mes "……ん？";
			mes "いかにも私からの試練が気に食わない";
			mes "といったふうですね。";
			mes "あなたのような人には、聖戦への";
			mes "備えに加わってほしくありません。";
			next;
			mes "[ムルナク=ミヨオ]";
			mes "心を入れ替えて来るまで";
			mes "私に話しかけないでください。";
			close;
		}
		mes "[ムルナク=ミヨオ]";
		mes "何度でも挑戦させてあげます。";
		mes "しかし、失敗するということは";
		mes "あなたの心に問題があるという";
		mes "ことです。";
		next;
		if(equippeditem(2608) < 1) {	//ロザリー未装備
			mes "[ムルナク=ミヨオ]";
			mes "またロザリーをどこかに置いて";
			mes "きてしまったのですか？";
			mes "オーディンの加護を受けている";
			mes "私達が、ロザリーを粗末に扱っては";
			mes "なりません。";
			next;
			mes "[ムルナク=ミヨオ]";
			mes "何も考えず剣を振りかざすだけでは";
			mes "モンスターとさほど違いはありません。";
			mes "試練に挑戦したくば、まず心構えとして";
			mes "ロザリーを身につけてきなさい。";
			close;
		}
		mes "[ムルナク=ミヨオ]";
		mes "普段からモンスターを見ると";
		mes "すぐ剣を抜く……その癖が";
		mes "抜けていないようですね。";
		mes "私が見るのはあなたの忍耐力";
		mes "だということを忘れないでください。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "それではもう一度言いますが、";
		mes "ただ道を進み最後まで辿り着けば";
		mes "良いのです。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "何があってもモンスターを";
		mes "倒してはなりません。";
		mes "そこのところを肝に銘じて";
		mes "進みなさい。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "それでは始めます。";
		break;
	case 6:
		mes "[ムルナク=ミヨオ]";
		mes "よし、良いですね。";
		mes "どうでした？さほど難しくは";
		mes "なかったでしょう。";
		mes "もう私からは話すことは";
		mes "ありません。";
		next;
		mes "[ムルナク=ミヨオ]";
		mes "プロンテラ大聖堂に居る";
		mes "ケイナ=バレンタインに";
		mes "会ってみてください。";
		mes "次の試練を与えてくれるでしょう。";
		mes "それでは。";
		close;
	case 7:
	case 8:
	case 9:
	case 10:
		mes "[ムルナク=ミヨオ]";
		mes "こんなところで油を売っていては";
		mes "なりませんよ。";
		close;
	}
	//5,6のときの続き
	close2;
	warp "job_cru.gat",98,40;
	if(getnpctimer(1,"#CRU_1stTest") == 0) {	//タイマーが停止してるなら動かす
		donpcevent "#CRU_1stTest::OnStart";
		for(set '@i,0; '@i<3 ; set '@i,'@i+1)
			awake "#CRU_1stTest";
	}
	end;
}

//==============================================================
job_cru.gat,0,0,0	script	#CRU_1stTest	-1,{
	end;
OnTimer150000:
	if(getareausers("job_cru.gat",90,34,105,105) == 0) {	//誰も居ないならmobを抹消
		for(set '@i,0; '@i<3 ; set '@i,'@i+1)
			awake "#CRU_1stTest";
		killmonster "job_cru.gat","All";
		stopnpctimer;
		end;
	}
OnStart:
	initnpctimer;
	killmonster "job_cru.gat","#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,50,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,55,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,60,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,65,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,70,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,75,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,80,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,85,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	monster "job_cru.gat",98,90,"ファミリアー",1005,1,"#CRU_1stTest::OnKilled1";
	sleep 50000;
	killmonster "job_cru.gat","#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,45,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,45,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,55,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,55,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,65,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,65,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,75,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,75,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,85,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,85,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",94,95,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	monster "job_cru.gat",101,95,"マンドラゴラ",1020,1,"#CRU_1stTest::OnKilled2";
	sleep 50000;
	killmonster "job_cru.gat","#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",98,50,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",92,60,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",104,60,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",98,70,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",92,80,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",104,80,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	monster "job_cru.gat",98,90,"フローラ",1118,1,"#CRU_1stTest::OnKilled3";
	sleep 50000;
	killmonster "job_cru.gat","#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",90,50,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",105,50,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",98,60,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",90,70,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",105,70,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",98,80,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",90,90,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	monster "job_cru.gat",105,90,"天下大将軍",1277,1,"#CRU_1stTest::OnKilled4";
	end;
OnKilled1:
OnKilled2:
OnKilled3:
OnKilled4:
	warp "prt_fild05.gat",353,251;
	end;
}

job_cru.gat,98,105,0	script	#CRU_1stWarp	45,1,1,{
	set CHANGE_CRU,6;
	warp "prt_castle.gat",164,28;
	end;
}


//==========================================
// 二次試験（筆記試験）
//------------------------------------------

prt_church.gat,95,127,4	script	聖堂騎士	745,{
	switch(CHANGE_CRU) {
	case 0:
		mes "[ケイナ=バレンタイン]";
		mes "いらっしゃいませ。";
		mes "私はクルセイダーです。";
		mes "いつか訪れるという聖戦に";
		mes "備える者です。";
		next;
		if(Job == Job_Novice) {
			mes "[ケイナ=バレンタイン]";
			mes "もしクルセイダーに関心があれば、";
			mes "剣士として修練を積んでください。";
			mes "ご自分である程度剣士として";
			mes "修練を積んだと判断されたら";
			mes "またこちらへいらしてください。";
			next;
			mes "[ケイナ=バレンタイン]";
			mes "私達はプロンテラ城に出仕して";
			mes "います。";
			mes "一度立ち寄ってみては";
			mes "いかがでしょうか。";
			close;
		}
		if(Job == Job_Crusader) {
			mes "[ケイナ=バレンタイン]";
			mes "いらっしゃいませ、クルセイダー様。";
			mes "しっかりと修練を積み重ねて";
			mes "いらっしゃるご様子。";
			next;
			mes "[ケイナ=バレンタイン]";
			mes "いつか訪れる聖戦のために";
			mes "備えは万端に……";
			close;
		}
		if(Job != Job_Swordman) {
			mes "[ケイナ=バレンタイン]";
			mes "あなたも常に自分を鍛え";
			mes "未来に備えてくださいね。";
			close;
		}
		mes "[ケイナ=バレンタイン]";
		mes "もしクルセイダーに転職したければ";
		mes "プロンテラ城内に居る私達の";
		mes "マスターを訪ねてみてください。";
		close;
	default:	//1～5のとき
		mes "[ケイナ=バレンタイン]";
		mes "あなたはクルセイダーへの転職";
		mes "希望者ですね？";
		mes "まだ私に会う段階まで試練を";
		mes "こなしていません。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "他の試練を受けてから、";
		mes "再度いらしてください。";
		mes "お待ちしております。";
		mes "それでは……";
		close;
	case 6:
		mes "[ケイナ=バレンタイン]";
		mes "いらっしゃいませ。";
		mes "忍耐の試練を通過しましたね。";
		mes "次の試練は私が担当します。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "私の名前はケイナ=バレンタイン。";
		mes "聖戦に備える者の一人です。";
		mes "こちらの聖堂では、聖職者護衛の";
		mes "任務についております。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "私は、あなたがクルセイダーに";
		mes "なれるだけの知識をお持ちか";
		mes "どうかを見させていただきます。";
		mes "ただ剣を振るだけでは聖戦で";
		mes "勝利を収めることができません。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "では、問題を10個出します。";
		mes "良く聞いて、正しい答えを出して";
		mes "ください。";
		set CHANGE_CRU,7;
		break;
	case 7:
		mes "[ケイナ=バレンタイン]";
		mes "いらっしゃいませ。";
		mes "準備は万端ですか？";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "今回も問題を10個出します。";
		mes "よく聞いて、正しい答えを";
		mes "出してくださいね。";
		break;
	case 8:
	case 9:
		mes "[ケイナ=バレンタイン]";
		mes "申し上げたように、";
		mes "次の試練へ向かってください。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "プロンテラ城にいらっしゃる";
		mes "ブリッテン=ヒルド様にお会いして";
		mes "ください。";
		close;
	case 10:
		mes "[ケイナ=バレンタイン]";
		mes "こちらで何をなさっているのですか？";
		mes "試練は全てクリアしたはずです。";
		mes "マスター団長にお会いしてみては？";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "クルセイダーになるのもすぐそこです。";
		mes "つまり、私達の一員となるわけです。";
		mes "転職後も鍛錬を怠らずに。";
		close;
	}
	//筆記試験ここから
	next;
	switch(rand(3)) {
	case 0:
		mes "[ケイナ=バレンタイン]";
		mes "1.";
		mes "アンデットに効果的な属性攻撃は？";
		next;
		if(select("無属性","地属性","不死属性","聖属性")==4)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "2.";
		mes "モンスターが不死属性Lv2の時、";
		mes "聖属性攻撃によって与える";
		mes "ダメージはどうなるか。";
		next;
		if(select("125%","150%","175%","200%")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "3.";
		mes "イビルドルイドから得ることが";
		mes "できないアイテムはどれか。";
		next;
		if(select("聖職者の帽子","イグドラシルの葉","白ハーブ","返魂のお札")==1)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "4.";
		mes "次のアンデッドたちの中で";
		mes "一番HPの高いものは？";
		next;
		if(select("グール","スケルプリズナー","レイス","ゾンビプリズナー")==4)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "5.";
		mes "次のアンデッドの中で";
		mes "大きさの違う物はどれか。";
		next;
		if(select("レイス","カーリッツバーグ","ドレイク","イビルドルイド")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "6.";
		mes "不死属性攻撃に耐性を持つカードは？";
		next;
		if(select("オークスケルトンカード","オークゾンビカード","グールカード","スケルワーカーカード")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "7.";
		mes "ムナックとボンゴンは昔";
		mes "どんな関係だったか。";
		next;
		if(select("実の兄妹","同じ村の姉弟みたいな仲","義理の兄妹","不明")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "8.";
		mes "次の中で、先制攻撃を";
		mes "してこないアンデッドを選べ。";
		next;
		if(select("ソルジャースケルトン","オークスケルトン","スケルトン","スケルワーカー")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "9.";
		mes "ムナックカードをつけた";
		mes "シールドの名前は？";
		next;
		if(select("アトミック シールド","アムレット シールド","ヒプノティック シールド","ホメーロス シールド")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "10.";
		mes "死者の遺品を落とさないアンデッドは？";
		next;
		if(select("ムナック","グール","マミー","ソルジャースケルトン")==1)
			set '@point,'@point+10;
		break;
	case 1:
		mes "[ケイナ=バレンタイン]";
		mes "1.";
		mes "次の中で、属性の違う悪魔種族";
		mes "モンスターはどれか。";
		next;
		if(select("ジェスター","ウィンドゴースト","イシス","彷徨う者")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "2.";
		mes "悪魔種族モンスターに効果的な";
		mes "剣は次の中でどれか。";
		next;
		//if(select("デクストロース ツルギ","ハロウド ツルギ","ハイブリッド ツルギ","サイドライク ツルギ")==2) //本鯖仕様
		if(select("デクストロース ツルギ","ディカーセイト ツルギ","ハイブリッド ツルギ","サイドライク ツルギ")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "3.";
		mes "ドケビが落とさないアイテムは";
		mes "次のうちどれか。";
		next;
		if(select("エルニウム原石","ゴールデンメイス","ソードメイス","マイトスタッフ")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "4.";
		mes "次の中でHPが一番高いモンスターは？";
		next;
		if(select("ガイアス","白蓮玉","ドケビ","マリオネット")==4)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "5.";
		mes "次の悪魔種族モンスターの中で";
		mes "大きさの違うものは？";
		next;
		if(select("ゴーストリング","ウィスパー","デビルチ","バフォメットジュニア")==1)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "6.";
		mes "闇属性攻撃に耐性を持つ";
		mes "マフラーは次のうちどれか。";
		next;
		if(select("グロリアス マフラー","ディバイン マフラー","エンジェリック マフラー","モッキング マフラー")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "7.";
		mes "ウィンドゴーストに効果的な";
		mes "属性攻撃は？";
		next;
		if(select("水属性","地属性","火属性","風属性")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "8.";
		mes "次の悪魔種族モンスターで";
		mes "先制攻撃してくるものはどれか。";
		next;
		if(select("ソヒー","ガイアス","ドケビ","ウィスパー")==4)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "9.";
		mes "マリオネットカードの能力は？";
		next;
		if(select("闇属性攻撃に対する耐性 30%","毒属性攻撃に対する耐性 30%","念属性攻撃に対する耐性 30%","無属性攻撃に対する耐性 30%")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "10.";
		mes "悪魔種族モンスターに遭遇した";
		mes "時の効果的な対処法は？";
		next;
		if(select("「悪魔め、退きなさい！」と叫ぶ","魂を捧げて契約する","武器に聖水をかけて攻撃する","子悪魔帽をかぶる")==3)
			set '@point,'@point+10;
		break;
	case 2:
		mes "[ケイナ=バレンタイン]";
		mes "1.";
		mes "デーモンベインを取得するための";
		mes "ディバインプロテクション最低Lvは？";
		next;
		if(select("Lv1","Lv2","Lv3","Lv4")==3)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "2.";
		mes "BaseLv55で、Job加重値も";
		mes "含んだINTが30の場合、";
		mes "ヒールLv5の回復量は？";
		next;
		if(select("396","440","484","528")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "3.";
		mes "ディバインプロテクションLv7の時";
		mes "アンデッドからの防御力は";
		mes "いくつ増えるか。";
		next;
		if(select("21","22","23","24")==1)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "4.";
		mes "次の中で、念属性であるナイトメアを";
		mes "攻撃することができる槍はどれか。";
		next;
		if(select("ランス","パルチザン","クレセントサイダー","ゼピュロス")==4)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "5.";
		mes "キュアーを習得するための";
		mes "ヒール最低Lvはいくつか。";
		next;
		if(select("Lv1","Lv2","Lv3","Lv4")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "6.";
		mes "騎兵修練をLv3まで習得すると";
		mes "騎乗時攻撃速度はどうなるか。";
		next;
		if(select("通常の 70%","通常の 80%","通常の 90%","通常の 100%")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "7.";
		mes "次の中で、デーモンベインの";
		mes "説明と違う物を選べ。";
		next;
		if(select("アンデッドに対する攻撃力増加","アコライトだけのスキル","マスターの時 +30 増加","パッシブスキル")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "8.";
		mes "ヒールLv7のSP消費量は？";
		next;
		if(select("30","31","33","35")==2)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "9.";
		mes "キュアーで治療することができない";
		mes "状態異常は？";
		next;
		if(select("呪い","沈黙","混乱","暗黒")==1)
			set '@point,'@point+10;
		mes "[ケイナ=バレンタイン]";
		mes "10.";
		mes "クルセイダーとはどんな存在か";
		next;
		if(select("お菓子を備える者","聖戦に備える者","酒を備える者","ポーションを備える者")==2)
			set '@point,'@point+10;
		break;
	}
	mes "[ケイナ=バレンタイン]";
	mes "お疲れさまでした。";
	mes "それでは結果をお知らせします。";
	next;
	mes "[ケイナ=バレンタイン]";
	mes strcharinfo(0)+ "様の点数は";
	mes '@point+ "点です。";
	if( (CHANGE_CRU == 6 && '@point < 90) || (CHANGE_CRU == 7 && '@point < 80) ) {
		mes "惜しかったですね……";
		mes "もう少し勉強をしてから";
		mes "いらしてください。";
		next;
		mes "[ケイナ=バレンタイン]";
		mes "多くの知識が必要ですから、";
		mes "準備ができるまでお待ちして";
		mes "おります。";
		mes "自信がついたらまたいらして";
		mes "ください。";
		close;
	}
	mes ('@point < 100)? "良いですね。": "立派です……";
	mes "次の試練へ向かってください。";
	next;
	mes "[ケイナ=バレンタイン]";
	mes "プロンテラ城にいらっしゃる";
	mes "ブリッテン=ヒルド様にお会いして";
	mes "ください。";
	mes "彼に準備していただくよう伝達";
	mes "しておきます。";
	set CHANGE_CRU,8;
	close;
}


//==========================================
// 三次試験（浄化）
//------------------------------------------

prt_castle.gat,35,151,4	script	守備兵	751,{
	switch(CHANGE_CRU) {
	case 0:
		mes "[ブリッテン=ヒルド]";
		mes "よく来ました。";
		if(Job == Job_Crusader) {
			next;
			mes "[ブリッテン=ヒルド]";
			mes "毎日修練を積み重ね、";
			mes "立派なクルセイダーに";
			mes "なってください。";
			close;
		}
		mes "我々はクルセイダーです。";
		mes "未来に訪れる聖戦へ備える者達です。";
		next;
		if(Job == Job_Novice) {
			mes "[ブリッテン=ヒルド]";
			mes "もしクルセイダーに関心が";
			mes "おありなら、いつでも入団を歓迎";
			mes "します。";
			next;
			mes "[ブリッテン=ヒルド]";
			mes "剣士としてある程度修練を積み、";
			mes "オーディンの思し召しを悟った";
			mes "方ならばより歓迎します。";
			close;
		}
		if(Job != Job_Swordman) {
			mes "[ブリッテン=ヒルド]";
			mes "平和な日常の中にあっても、";
			mes "絶えず備えを怠りません。";
			mes "いつか来るその日のために……";
			close;
		}
		mes "[ブリッテン=ヒルド]";
		mes "もしクルセイダーに関心が";
		mes "おありなら、いつでも入団を歓迎";
		mes "します。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "クルセイダーになるためには、";
		mes "剣士のJobLvを40まで鍛えな";
		mes "ければなりません。";
		mes "詳しくは、中にいらっしゃるマスター";
		mes "に伺ってください。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "それでは、";
		mes "貴公にオーディンの加護あらんことを。";
		close;
	default:	//1～7のとき
		mes "[ブリッテン=ヒルド]";
		mes "よく来ました。";
		mes "貴公はクルセイダーへの";
		mes "試練に挑戦中ですね。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "しかし、まだ私からの試練を";
		mes "受けるには早すぎます。";
		mes "他の方々からの試練をすべて";
		mes "越えてからまた来てください。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "ではお待ちしています。";
		mes "貴公にオーディンの加護あらんことを。";
		close;
	case 8:
		mes "[ブリッテン=ヒルド]";
		mes "よく来ました。";
		mes "歓迎します。";
		mes "次なる試練が最後の試練です。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "私の名前はブリッテン=ヒルド。";
		mes "聖戦へ備える者の一人です。";
		mes "ここまでよく頑張りました。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "最後に私から出す試練は、";
		mes "実戦訓練です。";
		mes "クルセイダーたる者、戦闘力も";
		mes "秀でていなければなりません。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "試練を受ける前に、^3152FF聖水^000000を";
		mes "一つ準備してください。";
		mes "試練を受ける者を浄化するためです。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "では、始めましょうか。";
		mes "それとも準備をしますか？";
		set CHANGE_CRU,9;
		break;
	case 9:
		mes "[ブリッテン=ヒルド]";
		mes "よく来ました。";
		mes "準備はしてきましたね？";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "それでは試練を受けますか？";
		mes "それとも準備をしますか？";
		break;
	case 10:
		mes "[ブリッテン=ヒルド]";
		mes "おめでとうございます。";
		mes "これでクルセイダーへの試練を";
		mes "完遂しました。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "中にいらっしゃるマスターのもとへ";
		mes "行けば、その時から貴公も聖戦に";
		mes "加わる一員となるでしょう。";
		close;
	}
	//浄化試練ここから
	next;
	if(select("始めます","準備をしてきます")==2) {
		mes "[ブリッテン=ヒルド]";
		mes "わかりました。";
		mes "準備ができたらまた来て下さい。";
		mes "お待ちしています。";
		close;
	}
	if(equippeditem(2608)==0) {	//ロザリー未装備
		mes "[ブリッテン=ヒルド]";
		mes "……ん？";
		mes "貴公はロザリーを身につけて";
		mes "いませんね。";
		mes "試練を受ける際は常にロザリーを";
		mes "身につけていなければなりません。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "ロザリーを身につけてから";
		mes "また来て下さい。";
		close;
	}
	if(countitem(523) < 1) {
		mes "[ブリッテン=ヒルド]";
		mes "試練を受けるためには^3152FF聖水^000000を";
		mes "一つ準備してください。";
		mes "さきほど申し上げたように、";
		mes "試練を受ける者を浄化するためです。";
		next;
		mes "[ブリッテン=ヒルド]";
		mes "準備してまた来て下さい。";
		mes "待っています。";
		close;
	}
	mes "[ブリッテン=ヒルド]";
	mes "それでは始めましょう。";
	mes "まずはあなたの身を清めます。";
	delitem 523,1;
	next;
	mes "[ブリッテン=ヒルド]";
	mes "……";
	next;
	mes "[ブリッテン=ヒルド]";
	mes "では入って控室で待機して";
	mes "ください。";
	mes "現れたモンスターをすべて";
	mes "撃退すれば良いです。";
	close2;
	warp "job_cru.gat",24,169;
	end;
}

//==============================================================
job_cru.gat,24,187,4	script	守備騎士::CRU_ChatRoom	751,{
	mes "[ブリッテン=ヒルド]";
	mes "ようこそ。";
	mes "ここでは最後の試練を受けて";
	mes "もらいます。";
	mes "始めるならば控室に入室して";
	mes "ください。";
	next;
	mes "[ブリッテン=ヒルド]";
	mes "試練場へ入れるのは一度に";
	mes "一人だけ。";
	mes "他の方が受けている場合は";
	mes "控室にて待機してください。";
	next;
	mes "[ブリッテン=ヒルド]";
	mes "一人あたり4分の時間制限が";
	mes "ありますが、途中でやめたい";
	mes "場合は一度接続しなおして";
	mes "ください。";
	close;
OnInit:
	waitingroom "控室",20,"CRU_ChatRoom::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	hideoffnpc "#CRU_3rdTest1";
	hideoffnpc "#CRU_3rdTest2";
	hideoffnpc "#CRU_3rdTest3";
	hideoffnpc "#CRU_3rdTest4";
	hideonnpc "#CRU_3rdWarp";
	warpwaitingpc "job_cru.gat",168,17;
	initnpctimer;
	end;
OnKilled:
	hideoffnpc "#CRU_3rdWarp";
	end;
OnTimer240000:
	stopnpctimer;
	areawarp "job_cru.gat",160,14,175,179,"prt_fild05.gat",353,251;
	areakillmonster "job_cru.gat",160,14,175,179;
	enablewaitingroomevent;
	end;
}

//==============================================================
job_cru.gat,168,17,0	script	#CRU_Messanger	139,2,2,{
	mes "[ブリッテン=ヒルド]";
	mes "進みながら、現れた敵を";
	mes "全て撃退してください。";
	mes "一つでも残せば不合格です。";
	next;
	mes "[ブリッテン=ヒルド]";
	mes "4分間与えます。";
	mes "では行ってください。";
	close;
}

//==============================================================
job_cru.gat,168,45,0	script	#CRU_3rdTest1	139,8,1,{
	monster "job_cru.gat",168,45,"ゾンビ",1015,6;
	hideonnpc;
	end;
}

job_cru.gat,168,80,0	script	#CRU_3rdTest2	139,8,1,{
	monster "job_cru.gat",168,80,"ソルジャースケルトン",1028,3;
	hideonnpc;
	end;
}

job_cru.gat,168,110,0	script	#CRU_3rdTest3	139,8,1,{
	monster "job_cru.gat",168,105,"アーチャースケルトン",1016,1;
	monster "job_cru.gat",168,110,"マミー",1041,1;
	hideonnpc;
	end;
}

job_cru.gat,168,150,0	script	#CRU_3rdTest4	139,8,1,{
	monster "job_cru.gat",168,150,strcharinfo(0),1036,1,"CRU_ChatRoom::OnKilled";
	hideonnpc;
	end;
}

job_cru.gat,168,180,0	script	#CRU_3rdWarp	45,1,1,{
	if(getareamobs("job_cru.gat",160,14,175,179) == 0)
		set CHANGE_CRU,10;
	warp "prt_castle.gat",35,147;
	areakillmonster "job_cru.gat",160,14,175,179;
	enablewaitingroomevent "CRU_ChatRoom";
	end;
}


//==========================================
// ペコペコレンタル
//------------------------------------------

prontera.gat,232,318,3	script	ペコペコ管理兵	105,{
	if(Job != Job_Crusader) {
		mes "[ペコペコ管理兵]";
		mes "何の用事でいらっしゃったんですか";
		mes "私どものペコペコは、";
		mes "クルセイダー専用となっています。";
		close;
	}
	mes "[ペコペコ管理兵]";
	mes "いらっしゃいませ、";
	mes (Upper == UPPER_HIGH)? "パラディン様。": "クルセイダー様。";
	mes "特別なペコペコをご用意して";
	mes "おります。";
	mes "一匹3500Zenyで貸与します。";
	next;
	if(select("利用する","やめる")==2) {
		mes "[ペコペコ管理兵]";
		mes "了解";
		close;
	}
	if(checkriding()) {
		mes "[ペコペコ管理兵]";
		mes "すでにペコペコに乗っておられます。";
		close;
	}
	if(Zeny < 3500) {
		mes "[ペコペコ管理兵]";
		mes "お金が不足しております。";
		mes "3500Zenyご用意してください。";
		close;
	}
	if(getskilllv(63) < 1) {
		mes "[ペコペコ管理兵]";
		mes "まずペコペコに乗る訓練を";
		mes "してきてください。";
		close;
	}
	set Zeny,Zeny-3500;
	setriding;
	close;
}
