//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  ルーンの依頼
//
//                                                 by Pneuma
//------------------------------------------------------------

// ----------------------------------------------------------------------------------------
//  ミニマップの印の色
//  青：気になるあの子
//  赤：奇跡の箱
//  橙：お世話になったあの人に
//  緑：実験のお手伝い
//  水：冒険者になりたい
// ----------------------------------------------------------------------------------------
// ルーン
ac_cl_area.gat,48,145,4	script	ルーン#ac	430,{
	function GetQueLv;
	function GetQuestSelectList;
	function GetQuestName;
	function GiveExp;
	set '@novice, callfunc("AC_GetNovice");
	cutin "jpn_run01",2;
	if('@novice && AC_NOVICE_QUE==30){ //フェイの講習後
		set AC_NOVICE_QUE,31;
		mes "[ルーン]";
		mes "冒険者アカデミーへようこそ！";
		mes "新入生さんね。";
		mes "さっそくなんだけど、";
		mes "手伝って貰いたいことがあるの。";
		mes "どの依頼を手伝えそう？";
		next;
		goto L_GETQUE;
	}
	if(!'@novice && !AC_NOVICE_QUE){
		mes "[ルーン]";
		mes "冒険者アカデミーへようこそ！";
		mes "新入生さん……というには";
		mes "あなた只者ではない雰囲気を";
		mes "持っているわね。";
		mes "何か用かしら？";
	} else {
		mes "[ルーン]";
		mes "あら、こんにちは。";
		mes "何か用かしら？";
	}
	next;
L_MENU:
	menu "依頼について話す",L_QUEST,"試験について話す",L_TEST,"ルーンさんは何をしているの？",L_ABOUT,"なんでもない",L_NOTHX;
L_QUEST:
	mes "[ルーン]";
	mes "依頼についてね。";
	mes "えーと、";
	mes "依頼の何の話なのかしら？";
	next;
	menu "依頼を受ける",L_GETQUE,"依頼の確認",L_QUECHECK,"依頼の報告",L_QUEREPORT,"依頼の内容について確認したい",L_QUEINFO,"なんでもない",L_NOTHX;
L_GETQUE:
	if(AC_QUEST_LV_0+AC_QUEST_LV_1+AC_QUEST_LV_2+AC_QUEST_LV_3+AC_QUEST_LV_4==45){
		emotion 2;
		mes "[ルーン]";
		mes "今、貴方が受けられる依頼は無いわ。";
		mes "あんなに沢山あったけど、";
		mes "貴方が手伝ってくれたおかげで、";
		mes "全部かたづいちゃった、";
		mes "私もちょっと暇になるかもしれないわ。";
		mes "おいしいものでも食べに行こうかしら。";
		next;
		goto L_OTHER;
	}
	GetQuestSelectList 0,'@quecount,'@quelist$,'@queidlist,'@queidcount;
	if('@quecount==0 && (AC_QUEST_ST_0 || AC_QUEST_ST_1 || AC_QUEST_ST_2 || AC_QUEST_ST_3 || AC_QUEST_ST_4)){
		mes "[ルーン]";
		mes "貴方は今請け負ってる依頼が";
		mes "あるじゃない。";
		mes "まずは今の依頼主さんを助けてあげて。";
		next;
		goto L_OTHER;
	}
	mes "[ルーン]";
	mes "今、貴方が請け負うことの出来る";
	mes "依頼は^FF0000"+ '@quecount +"^000000つね。";
	next;
	mes "[ルーンのワンポイントアドバイス]";
	mes "^008800緑色^000000の依頼はモンスターとの";
	mes "戦闘は無いと思うわ。";
	mes "^FF0000赤色^000000の依頼はモンスターとの戦闘が";
	mes "あるかもしれない。";
	mes "準備は万全にね。";
	mes "どれを請け負う？";
	next;
	set '@que_id, '@queidlist[select('@quelist$)-1];
	if('@que_id==99) goto L_NOTHX;
	set '@quelv,GetQueLv('@que_id);
	set '@idx,'@que_id*9+'@quelv;
	if(BaseLevel < 'QUE_REQUIRE['@idx]){
		mes "[ルーン]";
		mes "この依頼には";
		mes "レベルが^006600" + ('QUE_REQUIRE['@idx]-BaseLevel) + "^000000足りないわね。";
		mes "もうちょっと成長したら、";
		mes "依頼ができるようになるわ。";
		next;
		goto L_OTHER;
	}
	set '@client_id, 'QUE_CLIENT['@idx];
	mes "[ルーン]";
	switch ('@client_id) {
	case 0:
		mes "それね？";
		mes "依頼主は、プロンテラ在住の男性";
		mes "ハルバートさんからの依頼よ。";
		next;
		mes "[ルーン]";
		mes "ハルバートさんがいる場所は";
		mes "プロンテラ中央付近";
		mes "座標でいうと(146,232)付近";
		mes "になるようね。";
		break;
	case 1:
		mes "その依頼はっと……";
		mes "フェイヨン在住の男性";
		mes "ジェラルドさんからね。";
		mes "指輪職人さんらしいわ。";
		next;
		mes "[ルーン]";
		mes "ジェラルドさんがいる場所は";
		mes "フェイヨン中央から4時方向に進んだ";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(144.85)付近のようね。";
		break;
	case 2:
		mes "その依頼は";
		mes "イズルード在住の女性";
		mes "スザンヌさんからのものね。";
		next;
		mes "[ルーン]";
		mes "スザンヌさんがいる場所は";
		mes "イズルードの中央付近";
		mes "座標で言うと(138,156)付近";
		mes "になるようね。";
		break;
	case 3:
		mes "それね？";
		mes "それは、アルベルタ在住の女性";
		mes "ルイーゼさんからのものね。";
		next;
		mes "[ルーン]";
		mes "ルイーゼさんのいる場所は";
		mes "アルベルタの8時の方向";
		mes "座標で言うと(39,46)付近";
		mes "になるようね。";
		break;
	case 4:
		mes "それね？";
		mes "それは、アルデバラン在住の女性";
		mes "ミザリーさんからのものね。";
		next;
		mes "[ルーン]";
		mes "ミザリーさんがいる場所は";
		mes "アルデバラン4時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(231,107)付近のようね。";
		break;
	case 5:
		mes "それね？";
		mes "それは、ジュノー在住の男性";
		mes "マッズイさんからのものね。";
		mes "お菓子職人さんみたい。";
		next;
		mes "[ルーン]";
		mes "マッズイさんがいる場所は";
		mes "ジュノー9時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(95,184)付近のようね。";
		break;
	case 6:
		mes "それね？";
		mes "それは、フィゲル在住の男性";
		mes "タラシー博士さんからのものね。";
		next;
		mes "[ルーン]";
		mes "タラシー博士さんがいる場所は";
		mes "フィゲル6時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(107,77)付近のようね。";
		break;
	case 7:
		mes "それね？";
		mes "それは、フィゲル在住の男性";
		mes "アムロンさんからのものね。";
		next;
		mes "[ルーン]";
		mes "アムロンさんが居る場所は";
		mes "フィゲル9時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(73,155)付近のようね。";
		break;
	case 8:
		mes "それね？";
		mes "それは、ゲフェン在住の少女";
		mes "オネストさんからのものね。";
		next;
		mes "[ルーン]";
		mes "オネストさんが居る場所は";
		mes "ゲフェン2時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(168,170)付近のようね。";
		break;
	}
	next;
	mes "[ルーン]";
	mes "依頼内容に関しては";
	mes "依頼主から";
	mes "聞いてもらうことになるわ。";
	mes "この依頼は^FF0000"+ 'QUE_CREDITS['@quelv] +"^000000単位取得よ。";
	next;
	if(!'@novice){
		mes "[ルーン]";
		mes "貴方には^0000FFボランティア^000000に";
		mes "なってしまうかもしれないけど、";
		mes "いいかしら？";
	}
	mes "‐この依頼を受けますか？‐";
	next;
	menu "はい",-,"いいえ",L_QUECANCEL;
	if('@novice){
		mes "[ルーン]";
		mes "依頼は^0000FFヘイム^000000が";
		mes "手伝ってくれるって";
		mes "言ってたわ。";
		//2011/??/??変更
		//mes "^0000FFヘイム^000000は教室棟の";
		//mes "2Fにいると思うから、";
		//mes "探してちょうだい。";
		mes "^0000FFヘイム^000000は^FF0000この場所から上の方へ";
		mes "行った所^000000にいると思うから、";
		mes "探してみてちょうだい。";
		next;
		if('QUE_BATTLE['@que_id]){
			mes "[ルーン]";
			mes "街の外に出るときは";
			mes "アイテムの準備を";
			mes "整えていくといいわ。";
			mes "依頼の無事を終えたら";
			mes "私のところに戻ってきてね。";
			next;
		}
		mes "[ルーン]";
		mes "アカデミーの関係者が";
		mes "街の中央付近にいると思うから、";
		mes "迷ったら街の中央に";
		mes "行ってみるといいわ。";
		mes "それじゃ、いってらっしゃい！";
		next;
		mes "[ルーン]";
		mes "依頼を無事終えたら";
		mes "私のところに戻ってきてね。";
		next;
	}
	else {
		mes "[ルーン]";
		mes "依頼を無事終えたら";
		mes "私のところに戻ってきてね。";
		mes "それじゃ、いってらっしゃい！";
		next;
	}
	//依頼取得完了
	switch ('@que_id) {
	case 0: set AC_QUEST_ST_0,1; break;
	case 1: set AC_QUEST_ST_1,1; break;
	case 2: set AC_QUEST_ST_2,1; break;
	case 3: set AC_QUEST_ST_3,1; break;
	case 4: set AC_QUEST_ST_4,1; break;
	}
	mes "[インフォメーション]";
	mes "‐依頼の進行中にミニマップに";
	mes "『＋』が"+'QUE_COLOR$['@que_id]+"で表示されるように";
	mes "なりました‐";
	if('@novice){
		mes " ";
		mes "‐依頼の進行中に^FF0000【ミッション】^000000の";
		mes "表示が行われるようになりました‐";
		next;
		mes "[インフォメーション]";
		mes "‐^FF0000【ミッション】^000000で表示される街の";
		mes "アカデミー関係者の近くに";
		mes "移動すると、";
		mes "^FF0000次の行き先がミニマップ上に";
		mes "『＋』で表示されます^000000‐";
	}
	goto L_CLOSE;
L_QUECANCEL:
	mes "[ルーン]";
	mes "わかったわ、受けたくなったら";
	mes "また私に話しかけてちょうだい。";
	goto L_CLOSE;
L_QUECHECK:
	GetQuestSelectList 1,'@quecount,'@quelist$,'@queidlist,'@queidcount;
	if('@quecount==0) {
		mes "["+ strcharinfo(0) +"]";
		mes "(今確認できる依頼は無いか……)";
		goto L_CLOSE;
	}
	mes "[ルーン]";
	mes "あら、依頼主の居る場所を";
	mes "もう一度聞きたいのね？";
	if('@quecount==1){
		next;
		set '@que_id, '@queidlist[0];
	} else {
		mes "何の依頼を確認したいのかしら？";
		next;
		set '@que_id, '@queidlist[select('@quelist$)-1];
	}
	set '@quelv,GetQueLv('@que_id);
	set '@idx,'@que_id*9+'@quelv;
	set '@client_id, 'QUE_CLIENT['@idx];
	mes "[ルーン]";
	switch ('@client_id) {
	case 0:
		mes "依頼主の男性";
		mes "ハルバートさんがいる場所は";
		mes "プロンテラ中央付近";
		mes "座標でいうと(146,232)付近";
		mes "になるようね。";
		break;
	case 1:
		mes "依頼主の男性";
		mes "ジェラルドさんがいる場所は";
		mes "フェイヨン中央から4時方向に進んだ";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(144.85)付近のようね。";
		break;
	case 2:
		mes "依頼主の女性";
		mes "スザンヌさんがいる場所は";
		mes "イズルードの中央付近";
		mes "座標で言うと(138,156)付近";
		mes "になるようね。";
		break;
	case 3:
		mes "依頼主の女性";
		mes "ルイーゼさんのいる場所は";
		mes "アルベルタの8時の方向";
		mes "座標で言うと(39,46)付近";
		mes "になるようね。";
		break;
	case 4:
		mes "依頼主の女性";
		mes "ミザリーさんがいる場所は";
		mes "アルデバラン4時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(231,107)付近のようね。";
		break;
	case 5:
		mes "依頼主の男性";
		mes "マッズイさんがいる場所は";
		mes "ジュノー9時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(95,184)付近のようね。";
		break;
	case 6:
		mes "依頼主の男性";
		mes "タラシー博士さんがいる場所は";
		mes "フィゲル6時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(107,77)付近のようね。";
		break;
	case 7:
		mes "依頼主の男性";
		mes "アムロンさんが居る場所は";
		mes "フィゲル9時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(73,155)付近のようね。";
		break;
	case 8:
		mes "依頼主の女性";
		mes "オネストさんが居る場所は";
		mes "ゲフェン2時方向にある";
		mes "建物の中。";
		mes "建物のある場所を座標で言うと";
		mes "(168,170)付近のようね。";
		break;
	}
	next;
	mes "[インフォメーション]";
	mes "‐^FF0000【ミッション】^000000で表示される街の";
	mes "アカデミー関係者の近くに";
	mes "移動すると、";
	mes "^FF0000次の行き先がミニマップ上に";
	mes "『＋』で表示されます^000000‐";
	next;
	mes "[ルーン]";
	mes "依頼内容に関しては";
	mes "依頼主から直接聞いてちょうだいね。";
	goto L_CLOSE;
L_QUEREPORT:
	GetQuestSelectList 2,'@quecount,'@quelist$,'@queidlist,'@queidcount;
	if('@quecount==0) {
		mes "["+ strcharinfo(0) +"]";
		mes "(今報告できる依頼は無いか……)";
		goto L_CLOSE;
	}
	mes "["+ strcharinfo(0) +"]";
	mes "(どれを報告しよう？)";
	next;
	set '@que_id, '@queidlist[select('@quelist$)-1];
	GetQuestName '@que_id,'@que_name$;
	if('@que_id==99) {
		emotion 1;
		mes "["+ strcharinfo(0) +"]";
		mes "(今報告するのはやめておこう……)";
		goto L_CLOSE;
	}
	set '@quelv,GetQueLv('@que_id);
	mes "[ルーン]";
	mes '@que_name$ + "の報告ね。";
	mes "えーと、";
	mes "今確認するから少し待ってね……";
	next;
	mes "[ルーン]";
	mes "確認できたわ。";
	mes "無事に依頼人から依頼解決の";
	mes "連絡も来ているみたい。";
	if('@novice){
		if('QUE_BATTLE['@que_id]){
			mes "貴方凄いじゃない！";
			mes "モンスターが居て大変だったでしょう？";
			mes "本当に無事でよかったわ。";
		} else {
			mes "お疲れ様！";
		}
		next;
		mes "[ルーン]";
		mes "後これ、私からのご褒美ね。";
		set '@pot_count, 150 + '@quelv*30;
		if(!checkweight(569,'@pot_count)){
			mes "あら？";
			mes "荷物がいっぱいで渡せないわ。";
			mes "荷物を預けてから、報告してね。";
			goto L_CLOSE;
		}
		GiveExp '@que_id;
		getitem 569,'@pot_count;
		mes "初心者用ポーション" + '@pot_count + "個！";
		mes "回復量は少ないけど、";
		mes "凄く軽いから冒険で役立つと思うわ。";
		next;
		mes "[ルーン]";
		mes "それと単位ね";
		mes "この依頼で取得できる単位は";
		mes "[" + 'QUE_CREDITS['@quelv] + "]単位になるわ。";
		mes "今までの単位と合計すると";
		mes "[" + AC_CREDIT + "]単位ね。";
		next;
		mes "[ルーン]";
		mes "これで手続きも完了！";
		mes "また、用があったら";
		mes "私に話しかけてちょうだいね。";
		goto L_CLOSE;
	} else {
		next;
		mes "[ルーン]";
		mes "貴方のような熟練の冒険者に";
		mes "手伝ってもらえて";
		mes "本当にうれしいわ！";
		mes "ありがとう！";
		next;
		GiveExp '@que_id;
		mes "[ルーン]";
		mes "貴方には^0000FFボランティア^000000に";
		mes "なってしまったけど、";
		mes "この依頼で[" + 'QUE_CREDITS['@quelv] + "]単位取得よ。";
		mes "今までの単位と合計すると";
		mes "[" + AC_CREDIT + "]単位。";
		next;
		mes "[ルーン]";
		mes "また、貴方に手伝ってもらえたら、";
		mes "大助かり！";
		mes "これで手続きも完了！";
		mes "また、用があったら";
		mes "私に話しかけてね。";
		goto L_CLOSE;
	}
L_QUEINFO:
	emotion 20;
	mes "[ルーン]";
	mes "依頼の内容についてね。";
	mes "んー、私から生徒に依頼内容の";
	mes "詳細を教えることはしていないのよ。";
	mes "だって生徒が沢山居るのに";
	mes "一人一人説明してたら時間が";
	mes "いくらあっても足りないじゃない？";
	next;
	mes "[ルーン]";
	mes "教えられることといえば、";
	mes "貴方達のレベルを確認して";
	mes "解決できるかどうか私が";
	mes "判断しているってこと。";
	next;
	mes "[ルーン]";
	mes "だから、もし受けられる依頼が";
	mes "一つも無いとしたら";
	mes "貴方のレベルで解決できそうな";
	mes "依頼が一つも無いってことになるから";
	mes "頑張ってレベルをあげてもらう";
	mes "必要があるわ。";
	next;
	mes "[ルーン]";
	mes "ああ！";
	mes "もう一つあったわ！";
	mes "色よ色！";
	mes "依頼に三つの色をつけてるの。";
	next;
	mes "[ルーン]";
	mes "一つは^008800緑色^000000ね。";
	mes "^008800緑色^000000は、私が見た感じモンスターと";
	mes "戦闘する可能性が少ない";
	mes "と思ったものね。";
	mes "だからちょーっと刺激が足りないかも";
	mes "しれないわ！";
	next;
	mes "[ルーン]";
	mes "二つ目は^FF0000赤色^000000ね。";
	mes "^FF0000赤色^000000ってさ、";
	mes "凄く危険なイメージがない？";
	next;
	mes "[ルーン]";
	mes "全くその通り！";
	mes "モンスターと戦闘する可能性が";
	mes "高いと思われるものに赤色を";
	mes "つけてあるの！";
	next;
	emotion 29;
	mes "[ルーン]";
	mes "ふふふ、モンスターを";
	mes "なぎ倒し、ギリギリの";
	mes "ところで生還するスリル……";
	mes "たまらないわぁ……";
	mes "うふふふっ";
	next;
	menu "えっと……",-;
	emotion 0;
	mes "[ルーン]";
	mes "はっ！";
	mes "あ、ごめんごめん。";
	mes "えと、何を話してたっけ？";
	next;
	menu "依頼の色について",-;
	mes "[ルーン]";
	mes "あ！";
	mes "そうだったわね！";
	mes "えと、後一つは";
	mes "請け負うには少しレベルが";
	mes "足りない依頼内容なんだけど";
	mes "これは^777777灰色^000000にしてあるわ。";
	next;
	mes "[ルーン]";
	mes "説明はこんなとこかな？";
	goto L_CLOSE;
L_TEST:
	///*単位再計算*/{
	//	set AC_CREDIT,0;
	//	for(set '@i,0; '@i<5; set '@i,'@i+1){
	//		for(set '@j,0; '@j < GetQueLv('@i); set '@j,'@j+1){
	//			set AC_CREDIT,AC_CREDIT+'QUE_CREDITS['@j];
	//		}
	//	}
	//}
	set '@chklv,(BaseLevel < 'TST_REQUIR_LV[AC_RANK]);
	set '@chkct,(AC_CREDIT < 'TST_REQUIR[AC_RANK]);
	mes "[ルーン]";
	mes "試験についてね。";
	mes "えーと、";
	mes "試験の何の話なのかしら？";
	next;
	menu "試験を受ける",L_GETTEST,"試験の確認",L_CHKTEST,"試験の報告",L_REPOTEST,"試験を受けるには？",L_ABOUTTEST,"なんでもない",L_NOTHX;
L_GETTEST:
	if(AC_RANK>=7){
		emotion 2;
		mes "[ルーン]";
		mes "貴方は一次課程を修了しているのね。";
		mes "今は試験を行ってないわ。";
		mes "貴方は勉強熱心なのね。";
		mes "その気持ちを駆け出しの冒険者にも";
		mes "伝えてほしいわ。";
	}
	if(AC_RANKTEST){
		mes "[ルーン]";
		mes "貴方は今試験を受けているわ。";
		mes "次の試験を受けるためには、";
		mes "今の試験をやり遂げる必要があるわ。";
		mes "まずは、今の試験を";
		mes "やり遂げてちょうだい。";
		goto L_CLOSE;
	}
	if('@chklv || '@chkct){
		mes "[ルーン]";
		mes "貴方が今受けられる試験は無いわ。";
		if('@chklv && '@chkct){
			mes "Baseレベルが^FF0000" + ('TST_REQUIR_LV[AC_RANK]-BaseLevel) + "^000000";
			mes "単位が^FF0000" + ('TST_REQUIR[AC_RANK]-AC_CREDIT) + "^000000足りないみたい。";
			mes "Baseレベルを上げ、";
		} else
		if('@chklv){
			mes "試験を受けるための単位は";
			mes "取得してあるけど、";
			mes "Baseレベルが後^FF0000" + ('TST_REQUIR_LV[AC_RANK]-BaseLevel) + "^000000足りないみたい。";
			mes "Baseレベルを上げたら";
			mes "もう一度私に言ってくれるかしら。";
			goto L_CLOSE;
		} else
		if('@chkct){
			mes "レベルは足りてるんだけど";
			mes "単位が後^FF0000" + ('TST_REQUIR[AC_RANK]-AC_CREDIT) + "^000000足りないみたい。";
		}
		mes "依頼をこなして単位を取得したら";
		mes "もう一度私に言ってちょうだい。";
		goto L_CLOSE;
	}
	set AC_RANKTEST,1; //試験受付完了 ※フラグ立てる場所ここであってます。このあとの会話でリログしても受付完了されてます。

	switch(AC_RANK){
	case 0:
		mes "[ルーン]";
		mes "第一試験を受けるのね。";
		mes "試験に関しては";
		mes "ガルドが一括でおこなっているわ。";
		next;
		break;
	case 1: 
		mes "[ルーン]";
		mes "第二試験ね？";
		mes "試験に関してはガルドが";
		mes "おこなっているわ。";
		next;
		break;
	case 2:
		mes "[ルーン]";
		mes "ちょっと確認するわね。";
		mes "えと次は、第三試験のようね？";
		mes "試験に関しては今までどおり";
		mes "ガルドから";
		mes "受けてもらうことになるわ。";
		next;
		break;
	case 3:
		mes "[ルーン]";
		mes "第四試験！";
		mes "貴方凄いじゃない";
		mes "この試験に合格すれば";
		mes "残りは三つ。";
		mes "後ちょっとよ！";
		next;
		break;
	case 4:
		mes "[ルーン]";
		mes "第五試験ね。";
		mes "この段階まで来ると、";
		mes "だいぶ試験の難易度も";
		mes "上がってきてると思うの。";
		mes "でも今まで頑張ってきた貴方なら";
		mes "きっと合格できるわ！";
		next;
		break;
	case 5: emotion 0;
		mes "[ルーン]";
		mes "貴方は……第六試験!?";
		mes "貴方がんばったじゃない！";
		mes "残りの試験は二つよ！ 二つ！";
		mes "手続きをおこなったわよ。";
		next;
		break;
	case 6: 
		emotion 29;
		mes "[ルーン]";
		mes "第七試験。";
		mes "第一過程最後の試験になるわけだから";
		mes "難易度も相当高いはずよ。";
		mes "ふふふっ";
		mes "生きて帰ってこれるのかしら？";
		next;
		mes "[ルーン]";
		mes "さぁ、";
		mes "ガルドのところにGO！よ";
		mes "GO！";
		mes "学園内2Fの試験室に";
		mes "いってらっしゃい！";
		goto L_CLOSE;
	}
	mes "[ルーン]";
	mes "ガルドは学園内2F";
	mes "試験室にいるから";
	mes "行ってみてちょうだいね。";
	goto L_CLOSE;
L_CHKTEST:
	if(AC_LANC>=7){
		mes "[ルーン]";
		mes "今、貴方が受けられる試験は無いわ。";
		mes "一次過程修了なんて凄いじゃない。";
		mes "私も頑張らなくちゃね。";
		emotion 2, "ルーン#ac"; //54752
		goto L_CLOSE;
	}
	if(AC_RANKTEST==1){
		mes "[ルーン]";
		mes "試験のことはガルドに任せているわ。";
		mes "ガルドは学園内2F";
		mes "試験室にいるから";
		mes "行ってみてちょうだいね。";
		goto L_CLOSE;
	}
	if(AC_RANKTEST){
		mes "[ルーン]";
		mes "貴方は試験中のようね。";
		mes "試験の詳しいことは";
		mes "ガルドに任せているの。";
		mes "教室棟の2Fの試験室にガルドが";
		mes "いるはずだから、確認してみてね。";
		goto L_CLOSE;
	}
	mes "[ルーン]";
	mes "えーっと……ちょっとまってね。";
	mes "あら？";
	mes "貴方は試験を受けてないみたいね。";
	goto L_CLOSE;
L_REPOTEST:
	if(AC_RANKTEST!=99){
		mes "[" + strcharinfo(0) + "]";
		mes "(今報告できる試験は無いか……)";
		goto L_CLOSE; 
	}
	emotion 46;
	switch(AC_RANK){
	case 0:
		mes "[ルーン]";
		mes "第一試験突破おめでとう！";
		mes "初めての試験は緊張したでしょ？";
		mes "また単位を取得して";
		mes "次の段階に挑戦してね。";
		next;
		emotion 5;
		mes "[ルーン]";
		mes "そうだ！";
		mes "貴方この試験を合格できたんだし";
		mes "そろそろ、アカデミー外の";
		mes "モンスターとも戦って";
		mes "みたいんじゃない？";
		mes "ん～そうねぇ";
		next;
		mes "[ルーン]";
		mes "そうだわ、教室棟の2Fに";
		mes "ヨンというおじいさんがいるから";
		mes "話しかけてみるといいわよ。";
		next;
		mes "[ルーン]";
		mes "それと、タールさんって言う";
		mes "転送サービスを行ってくれる人";
		mes "しってる？";
		mes "彼はね、アカデミーに来て";
		mes "商売をしている方なのよ。";
		next;
		mes "[ルーン]";
		mes "この前、彼と食事した時に";
		mes "アカデミーのことを詳しく聞かれたから";
		mes "駆け出しの冒険者が";
		mes "頑張っていることを話したのよ。";
		mes "そうしたら、彼も協力したいって";
		mes "言ってくれたの。";
		next;
		mes "[ルーン]";
		mes "なんと！ 駆け出しの冒険者が";
		mes "試験に合格したら";
		mes "転送サービスを割引してくれるって！";
		mes "しかも、上の試験に合格すれば";
		mes "どんどん割引率は上がるのよ？";
		mes "すごいでしょ！";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 415,225;
		mes "[ルーン]";
		mes "はい、割引証ね。";
		mes "無くさないように気をつけて！";
		break;
	case 1:
		mes "[ルーン]";
		mes "第二試験突破おめでとう！";
		mes "ガルドから聞いたら、";
		mes "試験は第七試験まで";
		mes "あるらしいから、";
		mes "次の試験もがんばって！";
		next;
		mes "[ルーン]";
		mes "そうそう、ヨンおじいさんが";
		mes "新しい場所に転送してくれるって";
		mes "言ってたから";
		mes "聞きに言ってみたら？";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 810,798;
		mes "[ルーン]";
		mes "あと、タールさんの転送サービス";
		mes "割引率を更新しておくわね。";
		mes "これで、もっと割引率が";
		mes "増えるはずよ。";
		break;
	case 2:
		mes "[ルーン]";
		mes "第三試験突破おめでとう！";
		mes "そういえば、ウルフ先生は元気だった？";
		mes "あの先生、かわいらしくって";
		mes "困るのよね～。";
		next;
		mes "[ルーン]";
		mes "しかも、一人になるとうるさくって。";
		mes "ワンワン言ってたでしょ？";
		mes "次の試験も貴方なら頑張れそうね。";
		next;
		mes "[ルーン]";
		mes "そうそう、ヨンおじいさんが";
		mes "新しい場所に転送してくれるって";
		mes "言ってたから";
		mes "聞きに言ってみたら？";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 1475,2295;
		mes "[ルーン]";
		mes "あと、タールさんの転送サービス";
		mes "割引率を更新しておくわね。";
		mes "これで、もっと割引率が";
		mes "増えるはずよ。";
		break;
	case 3:
		mes "[ルーン]";
		mes "第四試験突破おめでとう！";
		mes "ガルドから聞いたけど、";
		mes "長旅だったんだって？";
		mes "凄いじゃない!!";
		mes "貴方なら、どこでもいけると思うわ。";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 3998,5672;
		mes "[ルーン]";
		mes "あと、タールさんの転送サービス";
		mes "割引率を更新しておくわね。";
		mes "これで、もっと割引率が";
		mes "増えるはずよ。";
		break;
	case 4:
		mes "[ルーン]";
		mes "第五試験突破おめでとう！";
		mes "報告書をガルドに届けることが";
		mes "できたようね。";
		mes "無事で何よりだわ。";
		next;
		mes "[ルーン]";
		mes "そうそう、ヨンおじいさんが";
		mes "新しい場所に転送してくれるって";
		mes "言ってたから";
		mes "聞きに言ってみたら？";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 5213,7943;
		mes "[ルーン]";
		mes "あと、タールさんの転送サービス";
		mes "割引率を更新しておくわね。";
		mes "これで、もっと割引率が";
		mes "増えるはずよ。";
		break;
	case 5:
		mes "[ルーン]";
		mes "第六試験突破おめでとう！";
		mes "ホルン先生を見つけるなんて、";
		mes strcharinfo(0) + "さん、すごいわ！";
		mes "見つけられない人も多いって言うのに。";
		mes "世界中を旅してみるのも";
		mes "いいかもしれないわ。";
		next;
		mes "[ルーン]";
		mes "そうそう、ヨンおじいさんが";
		mes "新しい場所に転送してくれるって";
		mes "言ってたから";
		mes "聞きに言ってみたら？";
		next;
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 7888,12499;
		mes "[ルーン]";
		mes "あと、タールさんの転送サービス";
		mes "割引率を更新しておくわね。";
		mes "これで、もっと割引率が";
		mes "増えるはずよ。";
		break;
	case 6:
		mes "[ルーン]";
		mes "第七試験突破おめでとう！";
		mes "すごい！";
		mes "ついに第一過程全ての";
		mes "試験に合格したわね！";
		next;
		mes "[ルーン]";
		mes "これで貴方も一人前の冒険者に";
		mes "一歩近づいたわね。";
		mes "ここまで色々大変だったと思うけど、";
		mes "貴方が行ってきたことは";
		mes "きっとこれからの冒険で";
		mes "役に立つはずよ。";
		next;
		mes "[ルーン]";
		mes "がんばってきた" + strcharinfo(0) + "さんに";
		mes "私から、渡したいものがあるわ。";
		mes strcharinfo(0) + "さんはここまで";
		mes "よく頑張ってきたわね。";
		next;
		mes "[ルーン]";
		mes "これはアカデミーの";
		mes "一次課程修了の証。";
		mes "アカデミー第一修了帽子よ！";
		if(!checkweight(5407,1)){ //ごめんなさい未調査。これは想像です。
			mes "あら？";
			mes "荷物がいっぱいで渡せないわ。";
			mes "荷物を預けてから、報告してね。";
			goto L_CLOSE;
		}
		set AC_RANK,AC_RANK+1;
		set AC_RANKTEST,0;
		getexp 17106,25183;
		getitem 5407,1;
		mes "これからもいろいろな人を";
		mes "助けてあげてちょうだいね。";
		next;
		mes "[ルーン]";
		mes "あ、そうだ！";
		mes "ミッドからも渡したいものが";
		mes "あるみたいだから";
		mes "話してみるといいわよ。";
		break;
	}
	goto L_CLOSE;
L_ABOUTTEST:
	if(AC_RANK>=7){
		mes "[ルーン]";
		mes "第一過程は修了してるわね。";
		mes "試験は暫く無いわ。";
		mes "ガルドもちょっと疲れたのかしら。";
		mes "試験をまた受けたいなんて、";
		mes "貴方は勉強熱心なのね。";
		next;
		mes "[ルーン]";
		mes "他の冒険者の皆を見てあげて";
		mes "貰ってもいいかしら。";
		mes "貴方ならいろんなことを";
		mes "教えられると思うわ。";
		emotion 2, "ルーン#ac"; //54752
		goto L_CLOSE;
	}
	if('@chklv || '@chkct){
		mes "[ルーン]";
		mes "試験を受けるには単位と";
		mes "Baseレベルが一定以上必要よ。";
		mes "単位は依頼を受けていくことで";
		mes "修得できるわ。";
	} else {
		mes "[ルーン]";
		mes "試験を受けるには単位が必要よ。";
		mes "単位は依頼を受けていくことで";
		mes "修得できるわ。";
	}
	next;
	//ポリン団実装により追加
	if(AC_QUEST_LV_6 != 16){
		mes "[ルーン]";
		mes "でも最近、";
		mes "実習室の方へ向かった生徒の単位が";
		mes "増えてるような気がするのよね。";
		mes "書類には不備は見当たらない";
		mes "のだけれど……";
		mes "まあ、気のせいよね。";
	} else {
		//クリアするとセリフが変化
		mes "[ルーン]";
		mes "もちろん、ポリン団から";
		mes "もらった単位も有効よ。";
	}
	if('@chklv || '@chkct){
		if('@chklv && '@chkct){
			next;
			mes "[ルーン]";
			mes "あと^FF0000" + ('TST_REQUIR[AC_RANK]-AC_CREDIT) + "^000000の単位を修得して、";
			mes "レベルが^FF0000" + ('TST_REQUIR_LV[AC_RANK]-BaseLevel) + "^000000になれば、";
		} else
		if('@chklv){
			mes "あと^FF0000" + ('TST_REQUIR[AC_RANK]-AC_CREDIT) + "^000000の単位を修得して、";
			mes "レベルが^FF0000" + ('TST_REQUIR_LV[AC_RANK]-BaseLevel) + "^000000になれば、";
		} else
		if('@chkct){
			mes "あと^FF0000" + ('TST_REQUIR[AC_RANK]-AC_CREDIT) + "^000000の単位を修得すれば、";
		}
		mes "次の試験を受けることができるわよ。";
	} else {
		mes "[ルーン]";
		mes "貴方は次の試験に十分な単位を";
		mes "修得しているわ。";
		mes "いつでも試験を受けることが";
		mes "できるわよ。";
	}
	goto L_CLOSE;
L_ABOUT:
	if(AC_QUEST_LV_0+AC_QUEST_LV_1+AC_QUEST_LV_2+AC_QUEST_LV_3+AC_QUEST_LV_4<=15) {
		mes "[ルーン]";
		mes "ここでは、各地から集められた";
		mes "依頼を請け負うことが出来るわ。";
		mes "そして依頼を解決することで";
		mes "単位をもらうことが出来るわけ。";
		mes "要するにこの依頼が授業ってことね。";
		next;
		emotion 5;
		mes "[ルーン]";
		mes "そうだった、自己紹介が";
		mes "まだだったわね。";
		mes "私の名前はルーン";
		mes "依頼の管理をおこなっているわ。";
		mes "もし、依頼を受けたかったら";
		mes "私に声をかけてね。";
		next;
		mes "[ルーン]";
		mes "そうそう、いい忘れていたけど";
		mes "単位を付与するのも私だから";
		mes "言動には注意するように。";
		goto L_CLOSE;
	} else
	if(AC_QUEST_LV_0+AC_QUEST_LV_1+AC_QUEST_LV_2+AC_QUEST_LV_3+AC_QUEST_LV_4<=30) {
		emotion 9;
		mes "[ルーン]";
		mes "……";
		mes "見てわからない？";
		mes "仕事をしてるのよ！";
		mes "仕事！";
		mes "はぁ……";
		next;
		menu "何かあったんですか？",-;
		emotion 36;
		mes "[ルーン]";
		mes "聞いてよ！";
		mes "昨日ミッドとプロンテラのお店に";
		mes "食事に行く約束をしていたのに";
		mes "仕事が忙しいからって";
		mes "ドタキャンされたのよ！";
		mes "酷いと思わない？";
		next;
		if(select("酷い","酷くない")==1){
			emotion 29;
			mes "[ルーン]";
			mes "ひどいわよねぇ……";
			mes "すっごい楽しみにしてたのに。";
			mes "今度行くときは絶対";
			mes "全額おごらせてやるわ！";
			mes "愚痴を聞いてくれてありがとう。";
			mes "すっきりしたわ！";
			goto L_CLOSE;
		} else {
			emotion 6;
			mes "[ルーン]";
			mes "?!";
			mes "確かに仕事は大切だけど";
			mes "約束を破るのはどうかと思うわ！";
			mes "あー、すっごいイライラしてきた……";
			goto L_CLOSE;
		}
	} else {
		emotion 18;
		mes "[ルーン]";
		mes "見てわかるとは思うけど";
		mes "依頼の管理をしているのよー";
		mes "貴方が受けられる";
		mes "依頼もあるかもしれないから";
		mes "依頼を受けたかったら言ってね。";
		next;
		menu "機嫌がよさそうですね",-;
		emotion 43;
		mes "[ルーン]";
		mes "うふふふっ、わかる？";
		mes "今度、ミッドのおごりで";
		mes "有名な高級料理店に行くことに";
		mes "なったのよー";
		mes "きっと凄いおいしいのよ……";
		next;
		menu "ルーンさんよだれ！",-;
		emotion 40;
		mes "[ルーン]";
		mes "あっ!?";
		mes "私としたことが……";
		mes "恥ずかしい……";
		mes "変な姿みられちゃったわね。";
		next;
		emotion 52;
		mes "[ルーン]";
		mes "このことは他の人には";
		mes "内緒にしてね。";
		mes "もし話したら……";
		mes "大変なことになるわよ！";
		goto L_CLOSE;
	}
L_OTHER:
	mes "[ルーン]";
	mes "他に何か話したいことはある？";
	next;
	menu "はい",L_MENU,"いいえ",L_NOTHX;
L_NOTHX:
	mes "[ルーン]";
	mes "話すことがあったら、";
	mes "すぐ言ってちょうだいね。";
	goto L_CLOSE;
L_CLOSE:
	close2;
	cutin "jpn_run01",255;
	end;
OnInit:
	setarray 'QUE_NAMES$,"気になるあの子","奇跡の箱","お世話になったあの人に","お詫びの品を届けたい","お菓子の材料集め","お菓子お届け","実験のお手伝い","ダンジョン救出","冒険者になりたい";
	setarray 'QUE_CHAP$,"","①","②","③","④","⑤","⑥","⑦","⑧","⑨";
	setarray 'QUE_NAMEIDS, 0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1, 2,3,4,4,4,4,4,5,3, 6,7,6,7,6,7,6,7,6, 8,8,8,8,8,8,8,8,8;
	setarray 'QUE_CHAPTERS,1,2,3,4,5,6,7,8,9, 1,2,3,4,5,6,7,8,9, 0,1,1,2,3,4,5,0,2, 1,1,2,2,3,3,4,4,5, 1,2,3,4,5,6,7,8,9;
	setarray 'QUE_REQUIRE,1,12,15,18,21,24,27,30,33, 1,13,16,19,22,25,28,31,34, 1,14,17,20,23,26,29,32,35, 1,14,17,20,23,26,29,32,35, 1,12,15,18,21,24,27,30,33;
	setarray 'QUE_BATTLE,0,0,0,1,1;
	setarray 'QUE_CREDITS,1,1,2,2,3,3,4,4,5;
	setarray 'QUE_CLIENT, 0,0,0,0,1,0,0,2,2, 3,3,3,3,3,3,3,3,3, 4,4,5,5,5,5,5,5,4, 6,7,6,7,6,7,6,7,6, 8,8,8,8,8,8,8,8,8;
	setarray 'QUE_COLOR$,"^0000FF青色^000000","^FF0000赤色^000000","^FF9900橙色^000000","^00FF00緑色^000000","^00FFFF水色^000000";
	setarray 'QUE_EXP,160,293,485,710,995,1475,2237,4587,6984, 193,350,560,810,1180,1713,3445,5213,7888, 245,415,630,930,1252,1967,3997,5874,8839, 245,415,630,930,1252,1967,3997,5874,8839, 160,293,485,710,995,1475,2237,4587,6984;
	setarray 'QUE_JOB,104,160,334,608,1252,2294,3711,7295,10471, 121,190,387,798,1403,3058,4639,7936,12488, 140,225,445,1114,1823,3375,5663,8599,15614, 140,225,445,1114,1823,3375,5663,8599,15614, 104,160,334,608,1252,2294,3711,7295,10471;
	setarray 'TST_REQUIR,5,10,15,20,30,40,45;
	setarray 'TST_REQUIR_LV,14,19,24,29,31,34,39;
	waitingroom "ルーンの依頼", 0;
end;

	// function クエストLv取得  -----------------------------
	function	GetQueLv	{
		switch (getarg(0)) {
		case 0: set '@quelv,AC_QUEST_LV_0; break;
		case 1: set '@quelv,AC_QUEST_LV_1; break;
		case 2: set '@quelv,AC_QUEST_LV_2; break;
		case 3: set '@quelv,AC_QUEST_LV_3; break;
		case 4: set '@quelv,AC_QUEST_LV_4; break;
		}
		return '@quelv;
	}

	// function クエスト選択一覧取得(引数(0) 0:請け負い 1:確認 2:報告  -----------------------------
	function	GetQuestSelectList	{
		set '@arg,getarg(0);
		set '@quelist$, "";
		set '@quecount, 0;
		setarray '@queidlist,0;
		set '@queidcount,0; //0から始まるのでgetarraysizeが使えない
		for(set '@i,0; '@i<5; set '@i,'@i+1) {
			//クエストLvとステータス取得
			switch ('@i) {
			case 0: set '@quelv,AC_QUEST_LV_0; set '@quest,AC_QUEST_ST_0; break;
			case 1: set '@quelv,AC_QUEST_LV_1; set '@quest,AC_QUEST_ST_1; break;
			case 2: set '@quelv,AC_QUEST_LV_2; set '@quest,AC_QUEST_ST_2; break;
			case 3: set '@quelv,AC_QUEST_LV_3; set '@quest,AC_QUEST_ST_3; break;
			case 4: set '@quelv,AC_QUEST_LV_4; set '@quest,AC_QUEST_ST_4; break;
			}
			if( //既に受けている依頼は表示しない
				('@arg==0 && '@quest>0) ||
				//受けてない依頼は表示しない
				('@arg==1 && '@quest==0) ||
				//完了していない
				('@arg==2 && '@quest!=99) ||
				//クリア済は表示しない
				'@quelv==9
			) {
				continue;
			}
			set '@idx,'@i*9+'@quelv;
			//文字色決定
			if(
				//Lvが足りないものは灰色
				('@arg==0)*(BaseLevel>='QUE_REQUIRE['@idx] && '@quest==0) ||
				//受けている依頼
				('@arg==1) ||
				//報告できる依頼
				('@arg==2)
			){
				if('QUE_BATTLE['@i]) set '@color$,"^FF0000";
				else 				 set '@color$,"^008800";
				set '@quecount,'@quecount+1;
			} else {
				set '@color$,"^777777";
			}
			if('@arg==0) set '@quelist$,'@quelist$ + '@color$ +"Lv"+ 'QUE_REQUIRE['@idx] +"以上 "+ 'QUE_NAMES$['QUE_NAMEIDS['@idx]] + 'QUE_CHAP$['QUE_CHAPTERS['@idx]] +" "+ 'QUE_CREDITS['@quelv] + "単位^000000:";
			else		 set '@quelist$,'@quelist$ + '@color$ +'QUE_NAMES$['QUE_NAMEIDS['@idx]] + 'QUE_CHAP$['QUE_CHAPTERS['@idx]] +"^000000" + ('@arg==2 || '@i<4 ? ":" : "");
			set '@queidlist['@queidcount],'@i;
			set '@queidcount,'@queidcount+1;
		}
		set '@quelist$,'@quelist$ + ('@arg==0 ? "依頼を受けない" : ('@arg==2 ? "報告しない" : "") );
		set '@queidlist['@queidcount],99;

		set getarg(1),'@quecount;
		set getarg(2),'@quelist$;
		copyarray getarg(3),'@queidlist, '@queidcount+1;
		set getarg(4),'@queidcount;
		return;
	}

	// function クエスト名称取得  -----------------------------
	function	GetQuestName	{
		set '@queid,getarg(0);
		set '@quelv, GetQueLv('@queid);
		set '@idx,'@queid*9+'@quelv;
		//文字色決定
		if(BaseLevel>='QUE_REQUIRE['@idx]){
			if('QUE_BATTLE['@queid]) set '@color$,"^FF0000";
			else 					 set '@color$,"^008800";
		} else {
			set '@color$,"^777777";
		}
		set '@que_name$,'@color$ + 'QUE_NAMES$['QUE_NAMEIDS['@idx]] + 'QUE_CHAP$['QUE_CHAPTERS['@idx]] + "^000000";
		set getarg(1),'@que_name$;
		return;
	}

	// function 経験値/JOB経験地 付与  -----------------------------
	function	GiveExp	{
		set '@que_id,getarg(0);
		set '@quelv, GetQueLv('@que_id);
		set '@idx,'@queid*9+'@quelv;
		getexp 'QUE_EXP['@idx],'QUE_JOB['@idx];
		set AC_CREDIT,AC_CREDIT+'QUE_CREDITS['@quelv];
		switch ('@que_id) {
		case 0: set AC_QUEST_LV_0,AC_QUEST_LV_0+1; set AC_QUEST_ST_0,0; break;
		case 1: set AC_QUEST_LV_1,AC_QUEST_LV_1+1; set AC_QUEST_ST_1,0; break;
		case 2: set AC_QUEST_LV_2,AC_QUEST_LV_2+1; set AC_QUEST_ST_2,0; break;
		case 3: set AC_QUEST_LV_3,AC_QUEST_LV_3+1; set AC_QUEST_ST_3,0; break;
		case 4: set AC_QUEST_LV_4,AC_QUEST_LV_4+1; set AC_QUEST_ST_4,0; break;
		}
		return;
	}
}
