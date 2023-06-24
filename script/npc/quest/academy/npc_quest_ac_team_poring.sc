//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー　ポリン団(β)
//
//                                                 by Pneuma
//------------------------------------------------------------

//ミスティ
ac_cl_area.gat,63,184,4	script	ミスティ#ac_Misty	507,{

	function checkitemblank2;
	function checkweight2;
	function Information;
	set '@novice, callfunc("AC_GetNovice");

	switch(AC_QUEST_LV_6){
	/////////   第一話   /////////
	case 0:
		switch(AC_QUEST_ST_6){
		case 0:
			mes "[謎の声A]";
			mes "おーい！　おーーい!!";
			mes "ソコの君、君じゃよー。";
			mes "　";
			mes "‐どこかからか声がする‐";
			emotion 1,"";
			next;
			mes "[謎の声B]";
			mes "もっとお腹から声を出さないと";
			mes "気づいてもらえないのだ！";
			setquest 100800;
			set AC_QUEST_ST_6,1;
			next;
			emotion 12;
			mes "[謎の声A]";
			mes "おーいっ！";
			mes "聞いておるのかーっ！";
			mes "　";
			mes "[謎の声B]";
			mes "そこの" + (Sex ? "かっこいい":"かわいい") + "君なのだ！";
			next;
			if(select("えっ、私ですか？","気のせいのようだ")==2){
				emotion 16;
				mes "[謎の声A]";
				mes "あっ！　ちょっと!!";
				mes "あぁー……";
				mes "　";
				mes "‐途方にくれたような声が";
				mes "　背後に聞こえた‐";
				close;
			}
			set '@talked,1;
		case 1:
			if('@talked){
				mes "[謎の声A]";
				mes "そうそう、そこの君じゃよ！";
				mes "急に呼び止めてしまって、すまんのぅ。";
				next;
			} else {
				mes "[謎の声A]";
				mes "うぬぅ……困ったのぅ……";
				mes "呼びかけたのに";
				mes "誰も答えてくれぬとは……";
				next;
				menu "どうしたのですか？",-;
				emotion 0;
				mes "[謎の声A]";
				mes "い、今なんと？";
				mes "それは、ワシに聞いておるのか!?";
				mes "……";
				mes "た、助かったのじゃ!!";
				mes "ワシの話を聞いてくれ！";
				next;
			}
			mes "[謎の声A＝ミスティ]";
			mes "まずは自己紹介じゃな。";
			mes "ワシの名は、ミスティじゃ。";
			mes "こちらのお方は……ネコリン殿じゃ。";
			next;
			mes "‐ミスティのそばにいる";
			mes "　耳としっぽの生えた物体が";
			mes "　こちらを見上げている‐";
			next;
			menu "えっ？　あっ、はい",-;
			emotion 20,"";
			mes "[謎の声B＝ネコリン]";
			mes "ミスティ、早く本題に入るのだ！";
			next;
			emotion 0;
			mes "[ミスティ]";
			mes "わかっておる！";
			mes "今から言おうと思っていたのじゃ。";
			next;
			menu "それで何の用でしょう",-,"早く言ってください",-;
			mes "[ミスティ]";
			mes "助けて欲しいのじゃ！";
			mes "　";
			mes "実は、落し物をしてしまってのぅ……";
			mes "見つからなくて困っておるのじゃ。";
			next;
			mes "[ネコリン]";
			mes "ミスティはいつも、そそっかしいのだ。";
			mes "ついこの間も財布を落としたし……";
			next;
			mes "[ミスティ]";
			mes "それ以上は言わんでくれ……";
			next;
			mes "[ネコリン]";
			mes "ミスティが、ドジなのが悪いのだ。";
			mes "　";
			mes "" + (Sex ? "彼":"彼女") + "が話を聞いてくれるだけでも";
			mes "ありがたいのだ！";
			next;
			emotion 28;
			mes "[ミスティ]";
			mes "うぅ……";
			next;
			mes "[ミスティ]";
			mes "どうじゃ？";
			mes "一緒に探してくれぬか？";
			mes "勿論、";
			mes "ボランティアとは言わぬ。";
			mes "少しばかりだが、礼もしよう！";
			next;
			if(select("はぁ……わかりました","嫌です")==2){
				emotion 28;
				mes "[ミスティ]";
				mes "むむぅ！";
				mes "そ、そうか、";
				mes "残念じゃのぅ……";
				mes "とても残念じゃ……";
				next;
				mes "[ネコリン]";
				mes "何とか手伝って";
				mes "やってほしいのだ。";
				next;
				menu "そこまで言うなら、手伝いましょう",-;
			}
			emotion 20,"";
			emotion 2;
			mes "[ミスティ]";
			mes "そうか!!";
			mes "恩に着るぞ♪";
			next;
			mes "[ミスティ]";
			mes "ちなみに、落した物なんじゃが";
			mes "大事なアクセサリーでな。";
			mes "　";
			mes "くねくね柔らかくて、";
			mes "フサフサした長いモノなんじゃ。";
			next;
			mes "[ネコリン]";
			mes "まぁ、ホウキのようなものなのだ！";
			next;
			emotion 23;
			mes "[ミスティ]";
			mes "ホウキではないぞ！";
			next;
			emotion 21;
			mes "[ミスティ]";
			mes "……最後にそのアクセサリーを";
			mes "確認した場所があるんじゃが";
			mes "そこは「^FF0000ポリン^000000」が";
			mes "多数生息していてのぅ。";
			next;
			mes "[ミスティ]";
			mes "奴らには落ちているアイテムを";
			mes "体内に溜め込む習性があって、";
			mes "ちょっとでも手放そうものなら";
			mes "ぱっくんしてしまうのじゃ!!";
			next;
			emotion 9, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "…………";
			next;
			emotion 32;
			mes "[ミスティ]";
			mes "今回のアクセサリーも";
			mes "奴ら^FF0000ポリン^000000が";
			mes "犯人に違いないのじゃっ!!";
			next;
			mes "[ミスティ]";
			mes "……その場所にいる奴らをすべて";
			mes "調べろとは言わないのじゃ。";
			next;
			mes "[ミスティ]";
			mes "^FF00005匹^000000、5匹でよい。";
			mes "ポリンを倒して、";
			mes "落としたアクセサリーがないか";
			mes "確認してきてほしいのじゃ。";
			mes "頼むぞ！";
			next;
			mes "[ミスティ]";
			mes "そうそう、これから行ってもらう場所は";
			mes "アカデミー内から歩いて行けるのじゃ。";
			mes "　";
			mes "今回はワシが魔法で送るが、";
			mes "後で自分の足で行ってみるのも";
			mes "良いのではないかのぅ？";
			next;
			mes "[ミスティ]";
			mes "出発の準備は良いか？";
			mes "　";
			mes "それとも、自分の力で行くかのぅ？";
			next;
			if(select("自分で行きます","いつでも出発できます")==1){
				set '@nowarp,1;
				mes "[ミスティ]";
				mes "そうか！";
				mes "頼もしいのぅ。";
				mes "　";
				mes "もし、道に迷ったりしたら";
				mes "いつでも戻ってくるのじゃ♪";
			} else {
				if('@novice){
					mes "[ミスティ]";
					mes "何か困ったことがあれば、";
					mes "現地の「^FF0000リカバリープレート^000000」と";
					mes "「^FF0000アカデミーボックス^000000」を探すのじゃ。";
					mes "　";
					mes "きっと、君の助けになるじゃろ。";
				} else {
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
				}
			}
			next;
			Information 1,0;
			if('@nowarp){
				mes "[ミスティ]";
				mes "それでは、行ってくるのじゃ!!";
				close2;
				chgquest 100800,100801;
				set AC_QUEST_ST_6, 2;
			} else {
				mes "[ミスティ]";
				mes "期待しておるぞ！";
				mes "では……";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				chgquest 100800,100801;
				set AC_QUEST_ST_6, 2;
				if('@novice) warp "ac_prac_01.gat",225,31;
				else         warp "pay_fild04.gat",200,178;
			}
			end;
		case 2:
			if(!(checkquest(100801)&0x4)){
				mes "[ミスティ]";
				mes "おやっ？　どうしたのじゃ？";
				next;
				switch(select("ポリンとネコリン……似ていますね","疲れた……","「^FF0000ポリン^000000」について教えて")){
				case 1:
					emotion 33;
					mes "[ミスティ]";
					mes "確かに似ておるのぅ……";
					mes "　";
					mes "‐ミスティはおもむろに";
					mes "　傍らのネコリンを見下ろして";
					mes "　呟いた‐";
					next;
					mes "[ミスティ]";
					mes "しかし、ネコリン殿は";
					mes "「^FF0000ポリン^000000」とは違うのじゃ！";
					mes "　";
					mes "ネコリン殿のほうがはるかに強いぞ♪";
					next;
					mes "[ミスティ]";
					mes "それよりも、今は";
					mes "アクセサリーの捜索が先決じゃ！";
					next;
					mes "[ミスティ]";
					break;
				case 2:
					while(1){
						mes "[ミスティ]";
						mes "ま、待て！　諦めてはいかん！";
						mes "諦めたらそこで冒険終了じゃ!!";
						mes "　";
						mes "ましてやワシの命が……";
						mes "あっ、いや、気にするでないぞ。";
						next;
						menu "はぁ……",-;
						emotion 20,"";
						emotion 19;
						mes "[ミスティ]";
						mes "できるできる！";
						mes "君ならできる!!";
						mes "どうしてそこで諦めるのじゃ!!";
						mes "諦めちゃダメなのじゃ!!!!";
						mes "　";
						mes "どうじゃ？　できるじゃろ？";
						next;
						if(select("はいっ！","難しいです……")==1){
							emotion 33;
							mes "[ミスティ]";
							mes "うんうん、そうじゃろそうじゃろ。";
							mes "君ならできるぞ♪";
							mes "何事もチャレンジじゃ！";
							mes "　";
							break;
						}
					}
					break;
				case 3:
					mes "[ミスティ]";
					mes "奴はピンクのナマモノじゃ！";
					mes "　";
					mes "ベトベトした体で、";
					mes "落した物をすぐ拾う習性がある。";
					mes "ワシも落とした物を";
					mes "何度持っていかれた事か……";
					close;
				}
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				set '@nowarp, (select("自分で歩きます","お願いします")==1);
				Information 1,0;
				if('@nowarp){
					emotion 21;
					mes "[ミスティ]";
					mes "なんじゃあ";
					mes "甘えれば良いのにのぅ……";
					mes "　";
					mes "まぁ、がんばるんじゃぞ！";
					close;
				}
				emotion 78;
				savepoint "ac_cl_area.gat",53,181;
				mes "[ミスティ]";
				mes "君という奴は……しかたないのぅ♪";
				mes "もう一度、魔法で送ってやろう。";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				close2;
				if('@novice)
					warp "ac_prac_01.gat",225,31;
				else
					warp "pay_fild04.gat",200,178;
				end;
			}
			mes "[ミスティ]";
			mes "ご苦労だったのぅ";
			mes "そして……すまぬ！";
			mes "　";
			mes "君を送ってから分かったのじゃが、";
			mes "ワシのなくしたアクセサリーは";
			mes "ネコリン殿が持っておったのじゃ！";
			next;
			emotion 0,"";
			emotion 17;
			mes "[ミスティ]";
			mes "という訳で、無事探し物は見つかった。";
			mes "　";
			mes "君には、迷惑をかけたのぅ。";
			next;
			mes "[ネコリン]";
			mes "ミスティ、";
			mes "あとでポリンたちにも";
			mes "謝ってくるのだ！";
			mes "ポリンたちは冤罪だったのだ！";
			next;
			emotion 19;
			mes "[ミスティ]";
			mes "そ、それはじゃな";
			mes "ネコリン殿が拾っていた事を";
			mes "早く気付いていれば……";
			next;
			emotion 7, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "拾ってしまうのは習性なのだ！";
			mes "そもそも落としたミスティが悪いのだ！";
			mes "　";
			mes "むしろ、拾ってあげた事を";
			mes "感謝して欲しいのだ！";
			next;
			menu "……",-;
			mes "[ミスティ]";
			mes "まぁまぁ、そう怖い顔をするでない。";
			mes "約束の礼じゃったな。";
			mes "　";
			mes "うーむ……君はココの生徒じゃろ？";
			mes "ならば、単位をやろう！";
			mes "卒業に沢山必要じゃからなっ!!";
			next;
			mes "[ミスティ]";
			mes "おっと、そういえば";
			mes "君の名は、なんと言うのじゃ？";
			next;
			menu "名前を名乗る",-;
			emotion 46;
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "……";
			mes "……良い名じゃのぅ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ!!";
			next;
			menu "ありがとうございます",-;
			emotion 2,"";
			chgquest 100801,100803;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight(569,50)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 50;
			chgquest 100803,100804;
			if(checkre()) {
				getexp 10,0;
				getexp 10,0;
				getexp 0,1;
				getexp 0,1;
			}
			else {
				getexp 20,0;
				getexp 20,0;
				getexp 0,8;
				getexp 0,8;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			mes "[ミスティ]";
			mes "そうそう、単位の事じゃがな……";
			mes "ルーンとミッドには内緒じゃぞ？";
			mes "　";
			mes "決して話してはならぬ……";
			mes "ばれたらワシらが怒られるでな。";
			next;
			menu "はい、わかりました",-;
			mes "[ミスティ]";
			mes "うんうん♪　そうじゃ！";
			mes "ポリン団に入らぬか？";
			next;
			menu "ポリン団？",-;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ポリン団とは！";
			mes "世界を恐怖に陥れるため";
			mes "日々活動を続ける組織の名じゃ！";
			mes "ここにおわすネコリン殿は";
			mes "そのポリン団の団長なのじゃ!!";
			next;
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "うむ！";
			mes "くるしゅうないのだ！";
			next;
			mes "[ミスティ]";
			mes "はいはい……スゴイデスネー。";
			mes "　";
			mes "で……どうじゃ？";
			mes "君なら歓迎するぞ？";
			next;
			menu "はい、結構です",-,"いいえ、結構です",-;
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "結局断るということではないか！";
			next;
			mes "[ミスティ]";
			mes "つれないのぅ～。";
			mes "まぁ気が向いたらいつでも言うのじゃ。";
			mes "　";
			mes "ポリン団は、常に新しい団員をじゃな";
			next;
			menu "これ以上付き合うのは止めよう",-;
			emotion 54,"";
			emotion 36, "ネコリン#ac_Necorin";
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ワシも入団してから随分……";
			mes "　";
			mes "……って、おーい！";
			mes "聞いておるかぁ～、おーーい……";
			next;
			mes "[ネコリン]";
			mes "また、勧誘失敗なのだ……";
			mes "ミスティは、後でお仕置きなのだ！";
			next;
			mes "‐変わった二人組と出会ってしまった。";
			mes "　彼ら（？）は「ポリン団」という";
			mes "　悪の組織らしい‐";
			next;
			mes "[^FF0000第一話終了^000000]";
			mes "‐第二話開始には、";
			mes "　^FF0000BaseLvを4以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 2,1;
			close2;
			set AC_QUEST_LV_6,1;
			set AC_QUEST_ST_6,0;
			chgquest 100804,200950;
			set AC_CREDIT, AC_CREDIT+5;
			end;
		}
		break;
	/////////   第ニ話   /////////
	case 1:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<4){
				emotion 56, "ミスティ#ac_Misty"; //54753
				mes "[ミスティ]";
				mes "ネコリン殿！";
				mes "や、やめるのじゃ！";
				mes "くすぐりの刑だけは嫌なのじゃ。";
				mes "　";
				mes "そもそもネコリン殿も……";
				next;
				emotion 29, "ネコリン#ac_Necorin"; //54754
				mes "[ネコリン]";
				mes "口答えするともっと酷いのだ！";
				mes "覚悟するのだ！";
				next;
				emotion 4,""; //self
				mes "‐今近づくのはやめておこう‐";
				next;
				mes "[^FF0000第一話終了^000000]";
				mes "‐第二話開始には、";
				mes "　^FF0000BaseLvを4以上^000000にして";
				mes "　話し掛けてみよう‐";
				next;
				Information 2,1;
				close;
			}
			mes "[ミスティ]";
			mes "大変じゃー、大変なのじゃー!!";
			mes "　";
			mes "はぁはぁ……";
			mes "　";
			mes "たいへ……ゴホッゴホッ……";
			next;
			mes "‐「ポリン団」のミスティは";
			mes "　ひどく慌てているようだ‐";
			next;
			menu "今度は一体どうしたんですか？",-;
			emotion 20,"";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！　良い所に!!";
			mes "聞いてくれぬか？";
			mes "アカデミー食堂が大変なのじゃ!!";
			mes "突然、閉鎖してしまったのじゃ!!";
			next;
			menu "食堂が!?",-;
			emotion 23,"";
			emotion 79, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そして、犠牲者も";
			mes "出てしまったのじゃ……";
			next;
			menu "そんな、一体誰が……",-;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "犠牲者とは……";
			next;
			mes "[ミスティ]";
			mes "ワシなのじゃ！";
			mes "ワシの腹が大変なのじゃ!!";
			mes "腹が減って大問題なのじゃ!!!!";
			next;
			emotion 55,"";
			mes "[ネコリン]";
			mes "ミスティは、食い意地が悪いのだ！";
			mes "食べ物の事となると、";
			mes "とたんにパニックになるのだ！";
			next;
			mes "[ミスティ]";
			mes "古来より言うじゃろ？";
			mes "腹が減っては戦は出来ぬと……";
			mes "　";
			mes "ワシの貴重な安らぎの時間が";
			mes "今ピンチに立たされておるのじゃ!!";
			next;
			menu "……用事を思い出しました",-;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あわわわ、待つのじゃ！";
			mes "　";
			mes "このままでは、";
			mes "君のご飯も無くなるのじゃぞ？";
			mes "君は本当に良いのか？";
			mes "困るじゃろ？　腹が減るじゃろ～？";
			next;
			menu "……確かにお腹は減りますね",-;
			mes "[ミスティ]";
			mes "そこでじゃ！";
			mes "ワシなりに調査して、";
			mes "食堂が利用できない原因を";
			mes "突き止めたのじゃ！";
			mes "　";
			mes "それは……マキだったのじゃ!!";
			next;
			menu "マキ??",-;
			mes "[ミスティ]";
			mes "マキがない為、";
			mes "火が起こせないのじゃ！";
			next;
			mes "[ミスティ]";
			mes "魔法で火を起こすという手も";
			mes "あるにはあるのじゃが";
			mes "料理での火加減を調節するのは";
			mes "熟練の魔法使いでも難しいのじゃ……";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "というわけで、";
			mes "犠牲者を少しでも減らす為、";
			mes "マキを集めようではないか！";
			next;
			mes "[ネコリン]";
			mes "ミスティは、腹が減っているのだ。";
			next;
			menu "そのようですね",-;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "　";
			mes "そこまで言うなら、";
			mes "ネコリン殿のご飯は無しなのじゃ！";
			mes "　";
			mes "今日も明日も明後日も無しなのじゃ！";
			next;
			emotion 36, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "…………";
			mes "何をのんびりしているのだ！";
			mes "　";
			mes "さぁ！";
			mes "" + strcharinfo(0) + "！";
			mes "急いでマキを集めに行くのだ!!";
			next;
			menu "えええー!!",-;
			emotion 23,"";
			mes "[ミスティ]";
			mes "まぁまぁ……";
			mes "今回も少しばかりじゃが、";
			mes "礼をしようではないか♪";
			mes "　";
			mes "ポリン団も総出で手伝うから";
			mes "安心するのじゃ！";
			next;
			menu "……団員は何人くらいいるんですか？",-;
			emotion 29, "ネコリン#ac_Necorin";
			mes "[ミスティ]";
			mes "メンバーを知りたいじゃと？";
			mes "ふふふっ、ポリン団メンバーは……";
			mes "ネコリン殿！　ワシ！　君の三人じゃ！";
			mes "　";
			mes "少数精鋭なのじゃ!!";
			next;
			menu "私は入団してません！",-;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "細かい事は、良いではないか♪";
			mes "　";
			mes "君には期待しておるのじゃぞ？";
			next;
			menu "はぁ……",-;
			mes "[ミスティ]";
			mes "それでは、マキ集めの説明じゃ！";
			mes "「^FF0000ウィロー^000000」という";
			mes "木のモンスターがおってのぅ、";
			mes "奴からとれるマキは最高なのじゃ。";
			next;
			mes "[ミスティ]";
			mes "「^FF0000ウィロー^000000」を^FF000010匹^000000ほど倒せば、";
			mes "マキは十分集まるはずじゃ！";
			next;
			mes "[ネコリン]";
			mes "ミスティは、20匹なのだ！";
			next;
			mes "[ミスティ]";
			mes "なんじゃって!?";
			mes "ネコリン殿……ひどいのじゃ……";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "しかたない、飯の為じゃ！";
			mes "ワシもマキ集めをするかのぅ。";
			mes "　";
			mes "善は急げじゃ！";
			mes "魔法で現地まで送るが、どうじゃ？";
			next;
			set '@nowarp, (select("自分で歩きます","お願いします")==1);
			if(!'@nowarp && !'@novice){
				setquest 100805;
				mes "[ネコリン]";
				mes "ちょっと待つのだ。";
				mes "^FF0000蝶の羽^000000は持ったのだ？";
				mes "　";
				mes "忘れていると帰りが";
				mes "大変なときもあるのだ！";
				mes "それでも、行くのだ？";
				next;
				if(select("はい","いいえ")==2){
					mes "[ネコリン]";
					mes "しっかり準備はした方が良いのだ。";
					mes "また、いつでも来るのだ。";
					mes "それじゃ、準備してくるのだ！";
					close;
				}
				mes "[ネコリン]";
				mes "持って行ったほうが良いのだ……";
				mes "　";
				mes "何があっても知らないのだ！";
				next;
			}
			setquest 100805;
			set AC_QUEST_ST_6,1;
			Information 2,0;
			if('@nowarp){
				mes "[ミスティ]";
				mes "そうか……";
				mes "魔法を使いたかったのに残念じゃのぅ。";
				mes "　";
				mes "しっかりマキ集めをするんじゃぞ～。";
				close;
			}
			emotion 78;
			mes "[ミスティ]";
			mes "うむ！";
			mes "いざ、出陣じゃ～！";
			mes "　";
			mes "まーご、まーご、けらひぃ～♪";
			mes "　";
			mes "‐^FF0000セーブ地点として記録しました^000000‐";
			savepoint "ac_cl_area.gat",53,180;
			close2;
			if('@novice)
				warp "ac_prac_01.gat",225,31;
			else
				warp "pay_fild08.gat",24,74;
			end;
		case 1:
			if(!(checkquest(100805)&0x4)){
				emotion 1;
				mes "[ミスティ]";
				mes "おやっ？　どうしたのじゃ？";
				next;
				switch(select("まだ現地に向かっていないのですか？","疲れた……","「^FF0000ウィロー^000000」について教えて")){
				case 1:
					mes "[ミスティ]";
					mes "これから向かう所じゃよ。";
					mes "　";
					mes "実はのぅ……慌ててたおかげでな、";
					mes "武器を持っていくのを忘れたのじゃ。";
					next;
					emotion 18, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "ミスティは、";
					mes "お腹が減りすぎてついに……";
					mes "　";
					mes "おかしくなったのだ!!";
					next;
					emotion 77, "ミスティ#ac_Misty";
					mes "[ミスティ]";
					mes "そ、そんな事はないぞ？";
					mes "この通り元気、元気じゃ!!";
					mes "　";
					mes "‐ミスティが笑顔で両腕を振り回すと";
					mes "　同時に";
					mes "　グーキュルルと腹の虫がないた‐";
					next;
					menu "……",-;
					mes "[ミスティ]";
					mes "あ、あはははは……";
					mes "　";
					mes "まぁ、気にするでない。";
					mes "今しばらくは我慢出来るのじゃ。";
					next; 
					mes "[ミスティ]";
					mes "とにかく、一刻も早く";
					mes "マキを集めようではないか。";
					mes "　";
					break;
				case 2:
					while(1){
						mes "[ミスティ]";
						mes "ま、待て！　諦めてはいかん！";
						mes "諦めたらそこで冒険終了じゃ！";
						mes "　";
						mes "ましてやワシの飯が……";
						next;
						menu "はぁ……",-;
						emotion 20,"";
						emotion 19;
						mes "[ミスティ]";
						mes "できるできる！";
						mes "君ならできる!!";
						mes "どうしてそこで諦めるのじゃ!!";
						mes "諦めちゃダメなのじゃ!!!!";
						mes "　";
						mes "どうじゃ？　できるじゃろ？";
						next;
						if(select("はいっ！","難しいです……")==1){
							emotion 33;
							mes "[ミスティ]";
							mes "うんうん、そうじゃろそうじゃろ。";
							mes "君ならできるぞ♪";
							mes "何事もチャレンジじゃ！";
							mes "　";
							break;
						}
					}
					break;
				case 3:
					mes "[ミスティ]";
					mes "ようは木のお化けじゃな！";
					mes "　";
					mes "体がカラッカラに乾いておるぞ。";
					mes "とってもよく燃えそうじゃな。";
					mes "マキの材料にぴったりじゃ！";
					close;
				}
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				set '@nowarp, (select("自分で歩きます","お願いします")==1);
				Information 2,0;
				if('@nowarp){
					emotion 55;
					mes "[ミスティ]";
					mes "ウチの新人は頼もしいのう……";
					next;
					menu "だから、入団していませんて！",-;
					emotion 6,"";
					emotion 12;
					mes "[ミスティ]";
					mes "気をつけて行って来るのじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "精一杯がんばるのじゃぞ";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice)
					warp "ac_prac_01.gat",225,31;
				else
					warp "pay_fild08.gat",24,74;
				end;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おー、帰ってきおったな？";
			mes "して、結果はどうじゃった？";
			next;
			menu "約束のマキです",-;
			mes "[ミスティ]";
			mes "おお！　でかしたぞ！";
			mes "　";
			mes "あとは、こっそりアカデミー食堂に";
			mes "マキを置いてくれば……";
			next;
			emotion 19, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ……";
			mes "お腹が減っているのはわかるが";
			mes "よだれが凄い事になってるのだ。";
			mes "　";
			mes "はやく食堂に行こうなのだ！";
			next;
			emotion 77, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうじゃのぅ……";
			mes "　";
			mes "おや？";
			mes "こんな所に美味しそうな肉が……";
			next;
			mes "‐ミスティは、";
			mes "　嬉しそううな笑みを浮かべると";
			mes "　思いきりネコリンの耳に";
			mes "　かじりついた！‐";
			next;
			emotion 23, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "痛い、痛いのだ!!";
			mes "それは私の耳なのだ！";
			mes "　";
			mes "‐ネコリンは、かじりついたミスティを";
			mes "　振り落とさんとばかりに飛び跳ねる‐";
			next;
			mes "[ネコリン]";
			mes "ええぃ！";
			mes "いい加減に離すのだ！";
			next;
			menu "あの……手伝ったお礼は？",-;
			emotion 20,"";
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "　";
			mes "君の単位を増やしておいたのだ。";
			mes "ついでに、これも持って行くのだ！";
			next;
			menu "ありがとうございます",-;
			emotion 2,"";
			chgquest 100805,100807;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight(569,100)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 100;
			chgquest 100807,100808;
			if(checkre()) {
				getexp 12,0;
				getexp 12,0;
				getexp 0,4;
				getexp 0,4;
			}
			else {
				getexp 88,0;
				getexp 88,0;
				getexp 0,44;
				getexp 0,44;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 19, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "では急いで食堂に行くのだ！";
			mes "また会おうなのだ！";
			mes "　";
			mes "‐ネコリンは隙をついて";
			mes "　ミスティから逃れると";
			mes "　飛び跳ね、離れていった‐";
			next;
			emotion 43;
			mes "[ミスティ]";
			mes "ああ！　ワシの肉!!";
			mes "ええぃ、待つのじゃぁ～";
			next;
			mes "[^FF0000第二話終了^000000]";
			mes "‐第三話開始には、";
			mes "　^FF0000BaseLvを7以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 3,1;
			close2;
			chgquest 100808,200955;
			set AC_QUEST_LV_6,2;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+6;
			end;
		}
		break;
	/////////   第三話   /////////
	case 2:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<7){
				mes "‐ミスティはネコリンの耳に";
				mes "　かじりついて、";
				mes "　もぐもぐ動かしている。";
				mes "　……どうやらまた";
				mes "　食べ物と間違えられているようだ‐";
				next;
				emotion 16, "ネコリン#ac_Necorin"; //54754
				mes "[ネコリン]";
				mes "イタタッ、止めるのだ！";
				mes "は、早く、はやく!!";
				mes "開いてくれなのだ！";
				mes "耳が食いちぎられるのだ！";
				next;
				emotion 77, "ミスティ#ac_Misty"; //54753
				mes "[ミスティ]";
				mes "うぅ……";
				mes "　";
				mes "肉……肉……甘い物……";
				mes "大好きなイチゴ大福も";
				mes "食べたいのじゃあ……";
				next;
				mes "[^FF0000第二話終了^000000]";
				mes "‐第三話開始には、";
				mes "　^FF0000BaseLvを7以上^000000にして";
				mes "　話し掛けてみよう‐";
				next;
				Information 3,1;
				close;
			}
			emotion 75, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "はぁ……お腹が空いたのぅ……";
			mes "　";
			mes "‐ミスティはお腹をさすり";
			mes "　憂鬱なため息をついている‐";
			next;
			mes "‐マキがないため";
			mes "　閉められた食堂の問題は";
			mes "　もう解決しているはずだ‐";
			next;
			menu "食堂へ行ったのでは？",-;
			mes "[ミスティ]";
			mes "それが、食堂に……";
			mes "アレじゃ、アレが出たのじゃ。";
			next;
			menu "アレ？",-;
			emotion 1,"";
			mes "[ミスティ]";
			mes "非常に言いにくいんじゃが……";
			mes "黒光りして足の速いＴじゃ!!";
			mes "　";
			mes "おかげで衛生の都合上、";
			mes "食堂はまだ再開できんらしい。";
			next;
			menu "じゃあ、まだ食べてないんですね？",-;
			mes "[ミスティ]";
			mes "そうなのじゃ。";
			mes "今は気力でなんとかもっておる……";
			next;
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "現在アカデミー職員が総出で、";
			mes "駆除しているらしいのだ。";
			next;
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ああ……美味しそうな肉が……";
			mes "　";
			mes "‐ミスティはネコリンを";
			mes "　光悦とした表情で見下ろしている‐";
			next;
			emotion 23, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "!!";
			mes "　";
			mes "頼むのだ!!";
			mes "このままでは私の命が危ないのだ。";
			mes "Ｔを退治してきてほしいのだ!!";
			next;
			menu "断ってもダメなんでしょう？",-;
			emotion 54,"";
			mes "[ネコリン]";
			mes "君の協力に感謝するのだ！";
			mes "　";
			mes "それでこそポリン団の一員なのだ！";
			next;
			menu "一員になった覚えは無いです",-;
			mes "[ネコリン]";
			mes "冗談を言っている場合ではないのだ。";
			mes "Tとは、「^FF0000盗蟲^000000」の事なのだ。";
			mes "　";
			mes "動きの早い、黒光りした奴なのだ！";
			next;
			mes "[ネコリン]";
			mes "奴らは食堂が発生源ではなく、";
			mes "別のところから";
			mes "侵入してきているらしいのだ。";
			mes "君はとりあえず、";
			mes "^FF000010匹^000000ほど倒してきてほしいのだ。";
			next;
			emotion 11, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "「^FF0000盗蟲^000000」は、近くに仲間がいると";
			mes "集団で襲ってくる習性があるのだ。";
			mes "　";
			mes "囲まれないように注意するのだ！";
			next;
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あれ……？";
			mes "こんな所にイチゴ大福が……";
			mes "　";
			mes "‐ミスティは目をランランと光らせて";
			mes "　ネコリンに手を伸ばした‐";
			next;
			mes "[ネコリン]";
			mes "……いよいよもって、";
			mes "ミスティが末期のようなのだ。";
			mes "　";
			mes "さぁ一刻の猶予もないのだ！";
			mes "急いで行って来てくれなのだ！";
			next;
			mes "‐生命の危険に";
			mes "　ネコリンはその都度";
			mes "　のばされるミスティの手から";
			mes "　逃げ続けている‐";
			next;
			set '@nowarp, (select("急いで行ってきます","現地まで送ってほしいです")==1);
			if(!'@nowarp && !'@novice){
				mes "[ネコリン]";
				mes "ちょっと待つのだ。";
				mes "^FF0000蝶の羽^000000は持ったのだ？";
				mes "　";
				mes "忘れていると帰りが";
				mes "大変なときもあるのだ！";
				mes "それでも、行くのだ？";
				next;
				if(select("はい","いいえ")==2){
					mes "[ネコリン]";
					mes "しっかり準備はした方が良いのだ。";
					mes "また、いつでも来るのだ。";
					mes "それじゃ、準備してくるのだ！";
					close;
				}
				mes "[ネコリン]";
				mes "持って行ったほうが良いのだ……";
				mes "　";
				mes "何があっても知らないのだ！";
				next;
			}
			Information 3,0;
			setquest 100810;
			set AC_QUEST_ST_6,1;
			if('@nowarp){
				emotion 21, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "君の健闘を祈るのだ！";
				close;
			}
			emotion 78, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "今回は急ぎなのだ！";
			mes "特別なのだ！";
			mes "　";
			mes "まーご、まーご、けらひぃ～♪";
			mes "　";
			mes "‐^FF0000セーブ地点として記録しました^000000‐";
			savepoint "ac_cl_area.gat",53,180;
			close2;
			if('@novice)
				warp "ac_prac_01.gat",225,31;
			else
				warp "prt_fild01.gat",130,340;
			end;
		case 1:
			if(!(checkquest(100810)&0x4)){
				emotion 43;
				mes "‐捕まえようとするミスティと";
				mes "　逃げ続けるネコリンとで";
				mes "　熾烈な攻防が繰り広げられている‐";
				next;
				emotion 23, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "くっ……危ないのだ！";
				mes "　";
				mes "どうしたのだ！";
				mes "討伐はまだなのだ!?";
				next;
				switch(select("準備をしていました","疲れた……","「^FF0000盗蟲^000000」について教えて")){
				case 1:
					set '@nowarp,1;
					break;
				case 2:
					mes "[ネコリン]";
					mes "ま……待つのだ！";
					mes "諦めてはいけないのだ！";
					mes "中途半端でいいのだ？";
					mes "　";
					mes "そんな風に育てた覚えはないのだ！";
					next;
					menu "育ててもらってないです",-;
					emotion 0, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "!!!!";
					mes "冷静な突っ込みはいらないのだ！";
					mes "そこを何とか頼むのだ。";
					next;
					menu "しょうがない……",-;
					emotion 54,"";
					mes "[ネコリン]";
					mes "君だけが頼りなのだ！";
					mes "現地まで送るのだ？";
					next;
					set '@nowarp, (select("自分で歩きます","お願いします")==1);
					if(!'@nowarp && !'@novice){
						mes "[ネコリン]";
						mes "ちょっと待つのだ。";
						mes "^FF0000蝶の羽^000000は持ったのだ？";
						mes "　";
						mes "忘れていると帰りが";
						mes "大変なときもあるのだ！";
						mes "それでも、行くのだ？";
						next;
						if(select("はい","いいえ")==2){
							mes "[ネコリン]";
							mes "しっかり準備はした方が良いのだ。";
							mes "また、いつでも来るのだ。";
							mes "それじゃ、準備してくるのだ！";
							close;
						}
						mes "[ネコリン]";
						mes "持って行ったほうが良いのだ……";
						mes "　";
						mes "何があっても知らないのだ！";
						next;
					}
					break;
				case 3:
					mes "[ネコリン]";
					mes "盗蟲は黒光りしてすばしっこいのだ。";
					mes "中には大きいのもいるのだ……";
					mes "でも、今回は小さい奴なのだ。";
					mes "　";
					mes "1回でも反撃されると付近の盗蟲も";
					mes "一斉に襲ってくるのだ！";
					close;
				}
				Information 3,0;
				if('@nowarp){
					mes "[ネコリン]";
					mes "君の健闘を祈るのだ！";
					close;
				}
				emotion 78, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "頼んだのだ！";
				mes "あとは任せたのだ。";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice)
					warp "ac_prac_01.gat",225,31;
				else
					warp "prt_fild01.gat",130,340;
				end;
			}
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "肉……イチゴ大福……";
			mes "　";
			mes "‐ミスティは床に倒れるように寝転がり";
			mes "　ひたすらネコリンを見続けている‐";
			next;
			mes "‐熾烈な生存争いは";
			mes "　ミスティがついに";
			mes "　空腹で動けなくなったことで";
			mes "　ひと段落ついたようだ‐";
			next;
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "おお！　待っていたのだ！";
			mes "無事で何よりなのだ。";
			mes "　";
			mes "君の活躍もあり、";
			mes "どうやら盗蟲を";
			mes "駆除出来たようなのだ。";
			next;
			mes "[ネコリン]";
			mes "食堂の騒ぎも一段落したのだ。";
			mes "　";
			mes "今回は本当に助かったのだ……";
			mes "感謝するのだ！";
			next;
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "肉……イチゴ大福……";
			next;
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "さて、ミスティを食堂に";
			mes "つれていかねばならんのだ。";
			mes "　";
			mes "おっと、その前に単位をあげるのだ！";
			mes "アイテムもサービスするのだ。";
			mes "ん～　ポリ～ンっと！";
			next;
			menu "ありがとうございます",-;
			emotion 2,"";
			chgquest 100810,100812;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight(569,150)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 150;
			chgquest 100812,100814;
			if(checkre()) {
				getexp 22,0;
				getexp 22,0;
				getexp 0,12;
				getexp 0,12;
			}
			else {
				getexp 218,0;
				getexp 218,0;
				getexp 0,125;
				getexp 0,125;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			mes "[食堂の方向から]";
			mes "キャー!!";
			mes "　";
			mes "^FF0000泥棒～!!^000000";
			next;
			emotion 0, "ネコリン#ac_Necorin";
			emotion 0,"";
			mes "[ネコリン]";
			mes "!!!!";
			mes "　";
			mes "泥棒がでたらしいのだ!!";
			next;
			mes "[ネコリン]";
			mes "この冒険者アカデミーは";
			mes "我ら^FF0000ポリン団^000000の縄張り！";
			mes "そこで泥棒なんて";
			mes "ポリン団への挑戦ともいえるのだ！";
			next;
			mes "[ネコリン]";
			mes "ミスティ！";
			mes "急いで食堂に向かうのだ!!!!";
			mes "泥棒を捕まえるのだ!!";
			next;
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "にく……いち……ご……";
			mes "　";
			mes "‐ミスティはうつろな目で";
			mes "　右拳を上げて";
			mes "　ネコリンに応えている‐";
			next;
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "君には世話になったのだ。";
			mes "また会おうなのだ！";
			mes "　";
			mes "ポリン団！　いざ出陣なのだ!!";
			next;
			emotion 43, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "だい……ふく……";
			next;
			mes "[^FF0000第三話終了^000000]";
			mes "‐第四話開始には、";
			mes "　^FF0000BaseLvを10以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 4,1;
			close2;
			chgquest 100814,200960;
			set AC_QUEST_LV_6,3;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+6;
			end;
		}
		break;
	/////////   第四話   /////////
	case 3:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<10){
				emotion 27, "ネコリン#ac_Necorin"; //54754
				mes "[ネコリン]";
				mes "ポリン団の縄張りを荒らすとは";
				mes "いい度胸なのだ！";
				mes "　";
				mes "いざ、出陣なのだ!!";
				next;
				emotion 43, "ミスティ#ac_Misty"; //54753
				mes "[ミスティ]";
				mes "肉……イチゴ大福……";
				next;
				mes "[^FF0000第三話終了^000000]";
				mes "‐第四話開始には、";
				mes "　^FF0000BaseLvを10以上^000000にして";
				mes "　話し掛けてみよう‐";
				next;
				Information 4,1;
				close;
			}
			emotion 9, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "…………";
			mes "　";
			mes "‐ミスティはこちらが覗き込むのにも";
			mes "　反応せず、精根尽き果てた様子だ‐";
			next;
			menu "動いていないようですが……",-;
			mes "[ネコリン]";
			mes "うむ……";
			mes "　";
			mes "‐ネコリンは重々しく頷いた‐";
			next;
			mes "[ネコリン]";
			mes "ミスティは、一日5回食事をするのだ。";
			mes "飯を食べられない事は、";
			mes "相当きびしい現実だったようなのだ。";
			next;
			menu "結局、食事は？",-;
			mes "[ネコリン]";
			mes "そうなのだ。";
			mes "盗蟲退治をしてもらった後、";
			mes "結局、泥棒のせいで";
			mes "食堂はいまだ閉鎖されたままなのだ。";
			next;
			menu "泥棒は、捕まっていないのですか？",-;
			emotion 57, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "それがその……";
			mes "　";
			mes "今回は相手が悪すぎるのだ。";
			mes "私の最も苦手なモンスターなのだ……";
			next;
			mes "[ネコリン]";
			mes "誰か……";
			mes "泥棒をこらしめてほしいのだ……";
			mes "　";
			mes "‐ネコリンは重々しくため息をはきつつ";
			mes "　こちらをチラッ、チラッと";
			mes "　伺っている‐";
			next;
			mes "‐ネコリンの視線は";
			mes "　" + strcharinfo(0) + "の";
			mes "　良心を刺激し続ける‐";
			next;
			menu "……なんとなく話が見えました",-;
			emotion 52,"";
			mes "[ネコリン]";
			mes "流石、私が見込んだ人材なのだ！";
			mes "　";
			mes "そうと決まれば、話は早いのだ。";
			mes "私の敵を討ってほしいのだ！";
			next;
			menu "嫌です",-;
			emotion 28, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そこを何とか頼むのだ……";
			mes "　";
			mes "奴らだけは、";
			mes "どうしても駄目なのだ……";
			next;
			menu "何故ですか？",-;
			mes "[ネコリン]";
			mes "実はなのだ……";
			mes "　";
			mes "我々は、狼が大の苦手なのだ。";
			mes "あの耳を見ただけで寒気が……";
			next;
			menu "どんな狼ですか？",-;
			mes "[ネコリン]";
			mes "おお！　頼まれてくれるのだ？";
			mes "　";
			mes "犯人は「^FF0000子デザートウルフ^000000」なのだ！";
			mes "　";
			mes "奴らは徒党を組んでるのだ！";
			next;
			emotion 29, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "奴らなら、";
			mes "何匹倒してもかまわないのだ！";
			mes "　";
			mes "根絶やしにしてくれてもいいのだ！";
			next;
			menu "根絶やしはちょっと……",-;
			mes "[ネコリン]";
			mes "うむ……残念なのだ……";
			mes "　";
			mes "ならば^FF000010匹^000000で良いのだ。";
			mes "　";
			mes "とにかく奴らを、";
			mes "たくさん倒してきてほしいのだ！";
			next;
			mes "[ネコリン]";
			mes "それで、奴らが泥棒をやめれば";
			mes "食堂の閉鎖は解かれると";
			mes "思うのだ！";
			next;
			menu "わかりました",-;
			emotion 21,"";
			mes "[ネコリン]";
			mes "君には迷惑ばかりかけて、";
			mes "本当にすまないのだ……";
			mes "　";
			mes "さぁ一刻の猶予もないのだ！";
			mes "現地まで魔法で送るのだ！";
			next;
			set '@nowarp, (select("自分で歩きます","お願いします")==1);
			if(!'@nowarp && !'@novice){
				mes "[ネコリン]";
				mes "ちょっと待つのだ。";
				mes "^FF0000蝶の羽^000000は持ったのだ？";
				mes "　";
				mes "忘れていると帰りが";
				mes "大変なときもあるのだ！";
				mes "それでも、行くのだ？";
				next;
				if(select("はい","いいえ")==2){
					mes "[ネコリン]";
					mes "しっかり準備はした方が良いのだ。";
					mes "また、いつでも来るのだ。";
					mes "それじゃ、準備してくるのだ！";
					close;
				}
				mes "[ネコリン]";
				mes "持って行ったほうが良いのだ……";
				mes "　";
				mes "何があっても知らないのだ！";
				next;
			}
			Information 4,0;
			emotion 21, "ネコリン#ac_Necorin";
			setquest 100815;
			set AC_QUEST_ST_6,1;
			if('@nowarp){
				mes "[ネコリン]";
				mes "そうなのだ？";
				mes "　";
				mes "それではあとは頼んだのだ！";
				mes "健闘を祈るのだ！";
				close;
			}
			emotion 78, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "くれぐれも手加減無用なのだ！";
			mes "それではあとは頼んだのだ。";
			mes "　";
			mes "まーご、まーご、けらひぃ～♪";
			mes "　";
			mes "‐^FF0000セーブ地点として記録しました^000000‐";
			savepoint "ac_cl_area.gat",53,180;
			close2;
			if('@novice)
				warp "ac_prac_01.gat",225,31;
			else
				warp "prt_fild09.gat",312,193;
			end;
		case 1:
			if(!(checkquest(100815)&0x4)){
				mes "‐動かないミスティを";
				mes "　尻尾でつついていたネコリンが";
				mes "　こちらに気づいた‐";
				next;
				emotion 52, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "怪我はないのだ？";
				mes "疲れてはいないのだ？";
				mes "奴らを根絶やしに出来たのだ!?";
				next;
				switch(select("いえ、急いで行ってきます","道に迷いました","「^FF0000子デザートウルフ^000000」について教えて")){
				case 1:
					set '@nowarp,1;
					break;
				case 2:
					mes "[ネコリン]";
					mes "迷子……気にするななのだ!!";
					mes "何度でも魔法で送り届けるのだ！";
					mes "　";
					mes "どうするのだ？";
					next;
					set '@nowarp, (select("自分で行きます","お願いします")==1);
					if(!'@nowarp && !'@novice){
						mes "[ネコリン]";
						mes "ちょっと待つのだ。";
						mes "^FF0000蝶の羽^000000は持ったのだ？";
						mes "　";
						mes "忘れていると帰りが";
						mes "大変なときもあるのだ！";
						mes "それでも、行くのだ？";
						next;
						if(select("はい","いいえ")==2){
							mes "[ネコリン]";
							mes "しっかり準備はした方が良いのだ。";
							mes "また、いつでも来るのだ。";
							mes "それじゃ、準備してくるのだ！";
							close;
						}
						mes "[ネコリン]";
						mes "持って行ったほうが良いのだ……";
						mes "　";
						mes "何があっても知らないのだ！";
						next;
					}
					break;
				case 3:
					mes "[ネコリン]";
					mes "想像しただけで怖いのだ……";
					mes "　";
					mes "あの狼め……すぐに吠えるのだ。";
					mes "目が鋭くて、私の事をいつも";
					mes "集団で狙っているのだ！";
					close;
				}
				Information 4,0;
				if('@nowarp){
					emotion 21, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "よろしく頼むのだ！";
					mes "健闘を祈るのだ！";
					close;
				}
				emotion 78, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "必ず倒すのだ！";
				mes "出発なのだ！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice)
					warp "ac_prac_01.gat",225,31;
				else
					warp "prt_fild09.gat",312,193;
				end;
			}
			emotion 10, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ありがとうなのだ!!";
			mes "今回の君の活躍で、";
			mes "泥棒たちが";
			mes "食料を返してきたらしいのだ。";
			mes "　";
			mes "仕事の後のゼロピは、美味いのだ！";
			next;
			menu "とても小さい狼でしたよ？",-;
			emotion 20,"";
			mes "[ネコリン]";
			mes "小さくても狼は狼なのだ。";
			next;
			menu "えぇ、まぁ……そうですが……",-;
			emotion 20,"";
			mes "[ネコリン]";
			mes "まもなく食堂も";
			mes "営業できるようになるのだ。";
			mes "　";
			mes "まずは、ミスティに飯を与えるのだ。";
			next;
			mes "[ネコリン]";
			mes "ミスティ！　飯なのだ！";
			mes "　";
			mes "‐ネコリンは空腹でぐったりしている";
			mes "　ミスティの前に";
			mes "　おいしそうなにおいの肉を置いた‐";
			next;
			mes "‐ピクリとも動かなかったミスティが";
			mes "　肉に飛びついた！‐";
			next;
			emotion 77, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "肉！　肉！";
			mes "　";
			mes "……やっぱり肉は最高なのじゃ♪";
			next;
			mes "[食堂の声]";
			mes "^0000FF長らくお待たせいたしました。";
			mes "食堂の営業を再開いたします。^000000";
			next;
			emotion 46, "ネコリン#ac_Necorin";
			emotion 2, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "どうやら、";
			mes "全てが元通りになったのだ！";
			mes "　";
			mes "さぁ今回の報酬をあげるのだ！";
			mes "ん～　ポリ～ンっと！";
			next;
			menu "ありがとうございます",-;
			emotion 2,"";
			chgquest 100815,100817;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight(569,200)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 200;
			chgquest 100817,100818;
			if(checkre()) {
				getexp 33,0;
				getexp 33,0;
				getexp 33,0;
				getexp 0,19;
				getexp 0,19;
				getexp 0,19;
			}
			else {
				getexp 333,0;
				getexp 333,0;
				getexp 333,0;
				getexp 0,190;
				getexp 0,190;
				getexp 0,190;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ふう……";
			mes "美味じゃった。";
			next;
			mes "[ミスティ]";
			mes "おや？";
			mes "" + strcharinfo(0) + "";
			mes "ではないか！　どうしたのじゃ？";
			next;
			menu "のん気ですねぇ……",-;
			emotion 54,"";
			emotion 55, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿？";
			mes "いったい何があったのじゃ？";
			next;
			emotion 36, "ネコリン#ac_Necorin";
			emotion 9,"";
			mes "[ネコリン]";
			mes "ミスティは後でお仕置きなのだ……";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "えええ～、";
			mes "そんなぁ～殺生なぁ……";
			next;
			mes "‐結局、食堂の問題は、";
			mes "　ポリン団によって全て解決した。";
			mes "　";
			mes "　ポリン団は";
			mes "　悪の組織だと言っているが、";
			mes "　本当にそうなのだろうか？";
			mes "　まだまだ謎が多い組織だ……‐";
			next;
			mes "[^FF0000第四話終了^000000]";
			mes "‐第五話開始には、";
			mes "　^FF0000BaseLvを13以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 5,1;
			close2;
			chgquest 100818,200965;
			set AC_QUEST_LV_6,4;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+6;
			end;
		}
		break;
	/////////   第五話   /////////
	case 4:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<13){
				emotion 52, "ミスティ#ac_Misty"; //54753
				mes "[ミスティ]";
				mes "ネコリン殿！";
				mes "すごい事実に気づいたのじゃ！";
				next;
				emotion 1, "ネコリン#ac_Necorin"; //54754
				mes "[ネコリン]";
				mes "何に気づいたのだ？";
				next;
				emotion 29, "ミスティ#ac_Misty"; //54753
				emotion 33, "ネコリン#ac_Necorin"; //54754
				mes "[ミスティ]";
				mes "実はのぅ……";
				next;
				mes "‐ネコリンとミスティは";
				mes "　ひそひそコソコソと";
				mes "　密談をしている‐";
				next;
				mes "[^FF0000第四話終了^000000]";
				mes "‐第五話開始には、";
				mes "　^FF0000BaseLvを13以上^000000にして";
				mes "　話し掛けてみよう‐";
				next;
				Information 5,1;
				close;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ。";
			mes "元気にしておったか？";
			next;
			mes "[ミスティ]";
			mes "先日は助かったのじゃ♪";
			mes "君の活躍で食堂は守られたのじゃ。";
			next;
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "しかしじゃ！";
			mes "ポリン団は悪の組織なのじゃ!!";
			mes "皆を困らせねばならんのじゃ!!!!";
			next;
			emotion 1,"";
			mes "[ミスティ]";
			mes "気づいておったか？";
			mes "この事実に!?";
			next;
			menu "気づいて無かったんですか？",-;
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "なんと!?";
			mes "知っておったのか！";
			next;
			emotion 54, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "気づいてないのは、";
			mes "ミスティだけなのだ！";
			mes "ミスティは、本当にバカなのだ!!";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "ネコリン殿ひどいのじゃ……";
			mes "　";
			mes "もっと早く、";
			mes "教えてくれても良いものを……";
			next;
			mes "[ミスティ]";
			mes "まぁ……過ぎた事なのじゃ！";
			mes "気にしたら負けなのじゃ！";
			mes "　";
			mes "そうそう、そうじゃ！";
			mes "先程良いものを見つけてのぅ♪";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "どこに置いたかのぅ……えっと……";
			mes "おぉ？";
			mes "あった、あった♪";
			mes "　";
			mes "この魔法書なんじゃが……";
			mes "ココの所をよく読んでみるのじゃ！";
			next;
			mes "‐ミスティは、やたらと";
			mes "　シミだらけの魔法書を";
			mes "　" + strcharinfo(0) + "の";
			mes "　目前にかざした。";
			mes "　その本のタイトルは……‐";
			next;
			menu "^FF0000誰にでも作れる魔法の秘薬^000000？",-;
			emotion 5,"";
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうじゃ、秘薬じゃ！";
			mes "しかも誰にでも作れるのじゃ!!";
			mes "　";
			mes "面白そうじゃろ？";
			next;
			menu "効果は書いてあるのですか？",-;
			emotion 1,"";
			mes "[ミスティ]";
			mes "それがわからないのじゃ……";
			mes "　";
			mes "肝心のページが、何者かによって";
			mes "破られておってなぁ……";
			next;
			menu "誰がそんな事を……",-;
			emotion 20, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "本当は、";
			mes "ミスティがジュースをこぼしたのだ。";
			mes "ジュースを飲みながら読むからなのだ。";
			mes "　";
			mes "ミスティは、嘘をついてるのだ。";
			next;
			menu "やっぱり、そういう事ですか",-;
			emotion 54,"";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿～！";
			mes "ばらさなくても良いではないか……";
			next;
			mes "[ミスティ]";
			mes "うぅ……";
			mes "そうなのじゃ！";
			mes "ワシがジュースをこぼしたのじゃ！";
			mes "　";
			mes "でも、おかげで楽しみが増えたじゃろ？";
			next;
			menu "……これをどうしたいのですか？",-;
			emotion 54,"";
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "何を言っておるか！";
			mes "　";
			mes "こんなに楽しそうなもの";
			mes "作らないわけがないじゃろ？";
			next;
			mes "[ミスティ]";
			mes "何事にもチャレンジするのじゃ！";
			mes "　";
			mes "秘薬は完成してからの";
			mes "お楽しみなのじゃ♪";
			next;
			menu "確かに秘薬の効果は気になるけど……",-;
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ、";
			mes "やはり気になるようじゃな。";
			next;
			mes "[ミスティ]";
			mes "まぁまぁ、";
			mes "作ってから考えようではないか♪";
			mes "　";
			mes "まずは、作る事が肝心なのじゃ！";
			mes "いつものアレ……欲しいじゃろ？";
			next;
			menu "しょうがないですね",-;
			emotion 14,"";
			emotion 56, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そんな事いいつつも、";
			mes "本当は作ってみたいんじゃろ？";
			mes "　";
			mes "素直に言えば良いのにのぅ♪";
			next;
			mes "[ミスティ]";
			mes "さてさて、";
			mes "魔法書を読む限りじゃと……";
			mes "　";
			mes "ふむふむ……";
			next;
			mes "[ミスティ]";
			mes "赤いきのこの根……";
			mes "青い草の汁……";
			mes "スポアの頭……";
			mes "マンドラゴラの実！";
			mes "　";
			mes "これらが必要なようじゃ！";
			next;
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000赤いきのこ^000000";
			mes "^FF0000・^000000^FF0000青い草^000000";
			mes "^FF0000・^000000^FF0000スポア^000000";
			mes "^FF0000・^000000^FF0000マンドラゴラ^000000";
			mes "なのだ！";
			next; 
			mes "[ミスティ]";
			mes "ネコリン殿は物知りだのぅ。";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING04_mobinfo	{
				switch(getarg(0)){
				case 100820:
					mes "[ミスティ]";
					mes "ただのきのこじゃな。";
					mes "　";
					mes "丸太など湿り気の多いところで";
					mes "成長する植物じゃ。";
					mes "カチカチなきのこじゃが、";
					mes "しかし、所詮ただのきのこなのじゃ！";
					break;
				case 100822:
					mes "[ミスティ]";
					mes "水辺などにまれに生える青い草じゃ。";
					mes "　";
					mes "採取できる青いハーブは、";
					mes "青ポーションの材料にもなるようじゃ。";
					mes "根が強く、中々むしれないが";
					mes "所詮、ただの青い草なのじゃ！";
					break;
				case 100824:
					mes "[ミスティ]";
					mes "きのこのお化けじゃ。";
					mes "　";
					mes "お化けと言うても、";
					mes "攻撃しなければ襲ってこないのじゃ。";
					mes "水分を多く含んでおってのぅ……";
					mes "風の力に弱そうじゃな。";
					break;
				case 100826:
					mes "[ミスティ]";
					mes "植物が凶暴化したモンスターじゃ！";
					mes "　";
					mes "困った事に、遠くから様子を見ていても";
					mes "ツタで攻撃してくのじゃ……";
					mes "しかし、こ奴から取得出来る茎は、";
					mes "様々な上級薬品の材料にもなるのじゃ！";
					break;
				}
				return;
			}
			function	AC_PORING04_warp;
			function	AC_PORING04	{
				set '@questid,0;
				//100820,魔法の秘薬①,0,1085,20,0,0,0,0
				//100822,魔法の秘薬①,0,1079,10,0,0,0,0
				//100824,魔法の秘薬①,0,1014,5,0,0,0,0
				//100826,魔法の秘薬①,0,1020,5,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000赤いきのこ^000000","^FF0000青い草^000000","^FF0000スポア^000000","^FF0000マンドラゴラ^000000")){
					case 1:
						AC_PORING04_mobinfo 100820;
						next;
						mes "[ミスティ]";
						mes "「^FF0000赤いきのこ^000000」じゃな？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100820;
						break;
					case 2:
						AC_PORING04_mobinfo 100822;
						next;
						mes "[ミスティ]";
						mes "「^FF0000青い草^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100822;
						break;
					case 3:
						AC_PORING04_mobinfo 100824;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スポア^000000」じゃな？";
						mes "　";
						mes "^FF00005匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100824;
						break;
					case 4:
						AC_PORING04_mobinfo 100826;
						next;
						mes "[ミスティ]";
						mes "「^FF0000マンドラゴラ^000000」じゃな？";
						mes "　";
						mes "^FF00005匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100826;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ネコリン]";
				mes "決定なのだ！";
				mes "　";
				switch(AC_QUEST_ST_6){
				case 100820: mes "「^FF0000赤いきのこ^000000」が、"; break;
				case 100822: mes "「^FF0000青い草^000000」が、"; break;
				case 100824: mes "「^FF0000スポア^000000」が、"; break;
				case 100826: mes "「^FF0000マンドラゴラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのだ！";
				next;
				mes "[ミスティ]";
				mes "残りはワシが集めよう！";
				mes "戦って無理と判断したら、";
				mes "いつでも戻ってくるのじゃ！";
				mes "　";
				mes "そうじゃ……";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING04_warp (select("自分で歩きます","お願いします")==1);
				end;
			}
			function	AC_PORING04_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 5,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100820:
					case 100822:
					case 100824: warp "ac_prac_01.gat",225,31; break;
					case 100826: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100820: warp "prt_fild10.gat",82,104;  break;
					case 100822: warp "gef_fild08.gat",200,352;  break;
					case 100824: warp "pay_fild01.gat",278,18; break;
					case 100826: warp "prt_fild02.gat",305,22; break;
					}
				}
				return;
			}
			AC_PORING04;
			end;
		case 100820:
		case 100822:
		case 100824:
		case 100826:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "秘薬の材料は、";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100820: set '@select$,'@select$ + "「^FF0000赤いきのこ^000000」について教えて";  break;
				case 100822: set '@select$,'@select$ + "「^FF0000青い草^000000」について教えて";  break;
				case 100824: set '@select$,'@select$ + "「^FF0000スポア^000000」について教えて"; break;
				case 100826: set '@select$,'@select$ + "「^FF0000マンドラゴラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING04_warp 0;
					end;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は鮮度が命なのじゃ！";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING04_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING04;
					end;
				case 3:
					AC_PORING04_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "どうじゃった？";
			mes "収穫のほうは？";
			next;
			menu "これで良いですか？",-;
			mes "[ミスティ]";
			mes "ご苦労じゃったのぅ。";
			mes "これだけあれば十分じゃ！";
			mes "　";
			mes "鮮度が落ちる前に";
			mes "魔法の秘薬作りに取り掛かるのじゃ！";
			next;
			menu "足りて良かったです",-;
			mes "[ミスティ]";
			mes "これだけあれば、";
			mes "4・5回は失敗できそうじゃのぅ……";
			next;
			emotion 1, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そんなに失敗するつもりなのだ？";
			next;
			mes "[ミスティ]";
			mes "いやいや、それだけ沢山集めてきて";
			mes "くれたということじゃよ♪";
			next;
			emotion 18,"";
			mes "[ネコリン]";
			mes "珍しく、失敗の事を考えて";
			mes "材料を多めに用意したのかと……";
			mes "　";
			mes "やっぱりミスティは、";
			mes "何も考えてないなかったのだ。";
			mes "安心したのだ！";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "ネコリン殿そこまで言わなくても……";
			next;
			menu "ところで……",-;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！";
			mes "そうじゃった、そうじゃった。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6,100828;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight2(569,200, 645,10)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 200;
			getitem 645, 10;
			chgquest 100828,100829;
			if(checkre()) {
				getexp 30,0;
				getexp 30,0;
				getexp 30,0;
				getexp 30,0;
				getexp 30,0;
				getexp 30,0;
				getexp 0,5;
				getexp 0,5;
				getexp 0,5;
				getexp 0,5;
				getexp 0,5;
				getexp 0,5;
			}
			else {
				getexp 300,0;
				getexp 300,0;
				getexp 300,0;
				getexp 300,0;
				getexp 300,0;
				getexp 300,0;
				getexp 0,50;
				getexp 0,50;
				getexp 0,50;
				getexp 0,50;
				getexp 0,50;
				getexp 0,50;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "よ～し、ではさっそく♪";
			mes "必要なものは……ふむふむ……";
			mes "　";
			mes "いざ進めや食堂！";
			mes "目指すは大きい鍋じゃ！";
			next;
			emotion 12, "ネコリン#ac_Necorin";
			emotion 12, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "それでは、また会おうなのだ！";
			next;
			emotion 12,"";
			mes "[ミスティ]";
			mes "おーいネコリン殿～！";
			mes "早くしないと置いてゆくぞー!!";
			next;
			mes "[^FF0000第五話終了^000000]";
			mes "‐第六話開始には、";
			mes "　^FF0000BaseLvを16以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 6,1;
			close2;
			chgquest 100829,200970;
			set AC_QUEST_LV_6,5;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+7;
			end;
		}
		break;
	/////////   第六話   /////////
	case 5:
		switch(AC_QUEST_ST_6){
		case 0:
			mes "‐ポリン団のネコリンと";
			mes "　ミスティのいる一角は";
			mes "　大きな鍋とその他怪しげな材料で";
			mes "　埋めつくされていた‐";
			next;
			emotion 33, "ミスティ#ac_Misty";
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "次は、";
			mes "スポアの頭と赤いきのこの根を";
			mes "みじん切りにするのだー！";
			next;
			if(BaseLevel<16){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第六話開始には、";
				mes "　^FF0000BaseLvを16以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 33, "ミスティ#ac_Misty";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿～。";
			mes "　";
			mes "スポアの頭のみじん切りは、";
			mes "ものすごく目にしみるのじゃあ～！";
			next;
			menu "あのー、大丈夫ですか？",-;
			emotion 12,"";
			mes "[ミスティ]";
			mes "誰なのじゃ？";
			mes "涙で前が見えないのじゃ……";
			next;
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ、";
			mes "" + strcharinfo(0) + "が";
			mes "来たのだ。";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おぉ！";
			mes "それならそうと、";
			mes "名前を言ってくれたら良いのに、";
			mes "つれないのぅ……";
			mes "　";
			mes "ネコリン殿、ちょっと顔を洗ってくる。";
			next;
			mes "‐ミスティは目をおおい、";
			mes "　ふらふらと歩いていった‐";
			next;
			menu "声でわかると思ったので……",-;
			emotion 18, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティの記憶力は、";
			mes "三歩歩いたら忘れるレベルなのだ。";
			mes "　";
			mes "どうしようもないのだ。";
			next;
			mes "[ミスティ]";
			mes "すまんのぅ……";
			mes "　";
			mes "うん、もう声を覚えた！";
			mes "次からは大丈夫じゃ！";
			next;
			menu "怪しい……本当ですか？",-;
			emotion 32,"";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "　";
			mes "少しでも良いから、";
			mes "ワシを信用してくれ……";
			next; 
			switch(select("わかりました信用します","わかりました信用しません")){
			case 1:
				emotion 18,"";
				break;
			case 2:
				emotion 22,"";
				mes "[ミスティ]";
				mes "そうか！";
				mes "信用し……ない？";
				mes "　";
				mes "信用して欲しいのじゃ……";
				next;
				break;
			}
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "次からは、絶対に大丈夫じゃ！";
			mes "　";
			mes "「泥舟」にのったつもりで";
			mes "安心するのじゃ！";
			next;
			emotion 9, "ネコリン#ac_Necorin";
			emotion 9,"";
			mes "[ネコリン]";
			mes "それを言うなら「大船」なのだ……";
			next;
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "…………";
			mes "　";
			mes "「大舟」にのったつもりで";
			mes "安心するのじゃ！";
			next;
			menu "…………",-;
			mes "[ミスティ]";
			mes "おっと、";
			mes "そういえば魔法書によると、";
			mes "まだまだ材料が必要そうじゃ！";
			next;
			menu "何が必要なのですか？",-;
			emotion 54, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "それがな……";
			mes "急に魔法書が暗号化されててな。";
			mes "　";
			mes "さっぱり解読出来ないのじゃ。";
			next;
			mes "‐ミスティは疑問符を浮かべながら";
			mes "　かかげた魔法書を見上げている。";
			mes "　……その魔法書のタイトル文は";
			mes "　上下が逆になっていた‐";
			next;
			menu "それ、上下逆さまじゃ……",-;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "…………!!";
			next;
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "の";
			mes "アドバイスで解読出来たぞ！";
			mes "さすがじゃな！";
			next;
			mes "[ネコリン]";
			mes "ミスティはどうしても";
			mes "暗号にしたいみたいなのだ！";
			next;
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "さてさて、魔法書を読む限りじゃと、";
			mes "　";
			mes "ふむふむ……";
			next;
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ロッカーの羽……";
			mes "ホーネットの羽……";
			mes "アンバーナイトの目……";
			mes "マンドラゴラの実！";
			mes "　";
			mes "これらが必要なようじゃ！";
			next;
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000ロッカー^000000";
			mes "^FF0000・^000000^FF0000ホーネット^000000";
			mes "^FF0000・^000000^FF0000アンバーナイト^000000";
			mes "^FF0000・^000000^FF0000マンドラゴラ^000000";
			mes "なのだ！";
			next;
			switch(select("わかりました","あれ？　ちょっと待って？")){
			case 1:
				emotion 33,"";
				break;
			case 2:
				emotion 1,"";
				mes "[ミスティ]";
				mes "んん？";
				mes "どうしたのじゃ？";
				next;
				menu "マンドラゴラの実は前回……",-;
				emotion 23, "ミスティ#ac_Misty";
				mes "[ミスティ]";
				mes "ぎ、ぎくぅ！";
				mes "　";
				mes "たたた、足りなかったのじゃ！";
				next;
				menu "……本当ですか？",-;
				emotion 4, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "足りなくなったのは、";
				mes "ミスティが余所見をしながら";
				mes "グニグニとつぶしてるからなのだ。";
				mes "　";
				mes "ひっくり返して、";
				mes "全部地面に落としたのだ……";
				next;
				mes "[ミスティ]";
				mes "違うのじゃぁ～。";
				mes "　";
				mes "うぅ……美味しそうなリンゴに";
				mes "気を取られてつい……";
				mes "　";
				mes "仕方なかったのじゃ！";
				next;
				emotion 17, "ミスティ#ac_Misty";
				mes "[ミスティ]";
				mes "次からは気をつけるから";
				mes "許してほしいのじゃ……";
				mes "　";
				mes "お礼もたっぷりするのじゃ！";
				next;
				menu "しょうがないですね……",-;
				break;
			}
			mes "[ミスティ]";
			mes "本当にすまんのぅ。";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "どれにするか選んでほしいのじゃ！";
			function	AC_PORING05_mobinfo	{
				switch(getarg(0)){
				case 100830:
					mes "[ミスティ]";
					mes "音楽好きのバッタじゃ。";
					mes "　";
					mes "こちらから手を出さない限り、";
					mes "無害じゃ。";
					mes "ジャンプする時の音が、";
					mes "うるさいのが難点な昆虫なのじゃ。";
					break;
				case 100832:
					mes "[ミスティ]";
					mes "働き蜂じゃな。";
					mes "女王蜂の為に働いておる。";
					mes "　";
					mes "ちなみに、";
					mes "こ奴の落とす蜂の針は人気商品でな、";
					mes "高く買い取ってくれる人もおるぞ。";
					break;
				case 100834:
					mes "[ミスティ]";
					mes "カタツムリじゃな。";
					mes "硬い殻に覆われておるぞ。";
					mes "　";
					mes "ヌメヌメと動いて足が遅いが、";
					mes "殻が硬く打撃には少し強いのじゃ。";
					break;
				case 100836:
					mes "[ミスティ]";
					mes "植物が凶暴化したモンスターじゃ！";
					mes "　";
					mes "困った事に、遠くから様子を見ていても";
					mes "ツタで攻撃してくのじゃ……";
					mes "しかし、こ奴から取得出来る茎は、";
					mes "様々な上級薬品の材料にもなるのじゃ！";
					break;
				}
				return;
			}
			function	AC_PORING05_warp;
			function	AC_PORING05	{
				set '@questid,0;
				//100830,魔法の秘薬②,0,1052,40,0,0,0,0
				//100832,魔法の秘薬②,0,1303,40,0,0,0,0
				//100834,魔法の秘薬②,0,1094,10,0,0,0,0
				//100836,魔法の秘薬②,0,1020,10,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000ロッカー^000000","^FF0000ホーネット^000000","^FF0000アンバーナイト^000000","^FF0000マンドラゴラ^000000")){
					case 1:
						AC_PORING05_mobinfo 100830;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ロッカー^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100830;
						break;
					case 2:
						AC_PORING05_mobinfo 100832;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ホーネット^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100832;
						break;
					case 3:
						AC_PORING05_mobinfo 100834;
						next;
						mes "[ミスティ]";
						mes "「^FF0000アンバーナイト^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100834;
						break;
					case 4:
						AC_PORING05_mobinfo 100836;
						next;
						mes "[ミスティ]";
						mes "「^FF0000マンドラゴラ^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100836;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ネコリン]";
				mes "決定なのだ！";
				mes "　";
				switch(AC_QUEST_ST_6){
				case 100830: mes "「^FF0000ロッカー^000000」が、"; break;
				case 100832: mes "「^FF0000ホーネット^000000」が、"; break;
				case 100834: mes "「^FF0000アンバーナイト^000000」が、"; break;
				case 100836: mes "「^FF0000マンドラゴラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのだ！";
				next;
				mes "[ミスティ]";
				mes "残りはワシが集めよう！";
				mes "戦って無理と判断したら、";
				mes "いつでも戻ってくるのじゃ！";
				mes "　";
				mes "そうじゃ……";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING05_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING05_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 6,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100830: warp "ac_prac_02.gat",108,33; break;
					case 100832: warp "ac_spec_01.gat",283,34; break;
					case 100834: warp "ac_prac_02.gat",108,33; break;
					case 100836: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100830: warp "prt_fild04.gat",380,332; break;
					case 100832: warp "mjolnir_04.gat",165,196; break;
					case 100834: warp "gef_fild09.gat",225,28; break;
					case 100836: warp "prt_fild02.gat",305,22; break;
					}
				}
				return;
			}
			AC_PORING05;
			end;
		case 100830:
		case 100832:
		case 100834:
		case 100836:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "秘薬の材料は、";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100830: set '@select$,'@select$ + "「^FF0000ロッカー^000000」について教えて";  break;
				case 100832: set '@select$,'@select$ + "「^FF0000ホーネット^000000」について教えて";  break;
				case 100834: set '@select$,'@select$ + "「^FF0000アンバーナイト^000000」について教えて"; break;
				case 100836: set '@select$,'@select$ + "「^FF0000マンドラゴラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING05_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は鮮度が命なのじゃ！";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING05_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING05;
					end;
				case 3:
					AC_PORING05_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "どうじゃった？";
			mes "収穫のほうは？";
			next;
			menu "これで良いですか？",-;
			mes "[ミスティ]";
			mes "ご苦労だったのぅ。";
			mes "これだけあれば、バッチリじゃ！";
			mes "　";
			mes "鮮度が落ちる前に、";
			mes "魔法の秘薬作りに取り掛かるのじゃ！";
			next;
			menu "今度は気をつけてくださいね？",-;
			emotion 32,"";
			mes "[ミスティ]";
			mes "今度はちゃんと見てるから大丈夫じゃ！";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "それにしても、";
			mes "一体どんな効果があるのかのぅ……";
			mes "　";
			mes "楽しみじゃなぁ♪";
			next;
			menu "そうですね",-;
			emotion 2,"";
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "私の予想では「笑い薬」なのだ！";
			mes "　";
			mes "笑いが止まらなくて、";
			mes "みんなが、困るはずなのだ……";
			mes "その間に世界を征服するのだ!!";
			next;
			mes "[ミスティ]";
			mes "いやいや、";
			mes "「ワシの命令を聞く薬」";
			mes "というのもアリじゃのぅ……";
			next;
			menu "命令を聞く薬!?",-;
			emotion 1,"";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うむ！　実は……";
			mes "ワシには凶暴な姉上がおるのじゃ！";
			mes "　";
			mes "姉上のおかげで、";
			mes "ワシはいつもいつも……";
			next;
			emotion 76, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "姉上は物凄く器用なのじゃが、";
			mes "料理だけは物凄く苦手なのじゃ。";
			mes "　";
			mes "しかもその不味さは殺人的じゃ……";
			next;
			mes "[ミスティ]";
			mes "今は、";
			mes "その料理の腕を買われて";
			mes "アサシンギルドに";
			mes "所属しておるのじゃ。";
			mes "　";
			mes "なんでも、毒薬を作っているらしいぞ？";
			next;
			menu "その薬で何をしたいの？",-;
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ワシが命令すれば、";
			mes "姉上が料理を作るようになるじゃろ？";
			mes "　";
			mes "その料理をみんなが食べれば、";
			mes "ワシと同じ苦しみを味わうのじゃ！";
			next;
			emotion 20,"";
			mes "[" + strcharinfo(0) + "]";
			mes "（その薬をみんなに";
			mes "飲ませたほうが早いのでは……？";
			mes "　";
			mes "いや、ミスティには黙っておこう）";
			next;
			menu "恐ろしいですね",-;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうじゃろ♪";
			mes "　";
			mes "いやー、楽しみじゃなぁ。";
			next;
			menu "ところで……",-;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！";
			mes "そうじゃった、そうじゃった。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6,100838;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight2(569,200, 602,5)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 200;
			getitem 602, 5;
			chgquest 100838,100839;
			if(checkre()) {
				getexp 65,0;
				getexp 65,0;
				getexp 65,0;
				getexp 65,0;
				getexp 0,25;
				getexp 0,25;
				getexp 0,25;
				getexp 0,25;
			}
			else {
				getexp 650,0;
				getexp 650,0;
				getexp 650,0;
				getexp 650,0;
				getexp 0,250;
				getexp 0,250;
				getexp 0,250;
				getexp 0,250;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "さて……まずは、";
			mes "マンドラゴラの実をゆでるのだ！";
			mes "　";
			mes "ゆでたら、";
			mes "皮をむいて青い草の汁を混ぜつつ";
			mes "グニグニとつぶすのだ！";
			next;
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "姉上！";
			mes "待っておるのじゃ!!";
			mes "もうすぐワシの言いなりに……";
			mes "　";
			mes "フッフッフッ。";
			next;
			menu "姉妹で仲が悪いのですね",-;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "……姉妹？";
			mes "　";
			mes "何を言っておるのじゃ？";
			mes "ワシは男じゃぞ？";
			next;
			menu "!?",-;
			emotion 0,"";
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "どっからどう見ても男じゃろぅ？";
			mes "　";
			mes "そうじゃよな？　ネコリン殿。";
			next;
			emotion 22, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "どっからどう見ても女なのだ。";
			next;
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そんな馬鹿な！";
			mes "　";
			mes "いいか？　良く聞くのじゃ……";
			mes "　";
			mes "^0000FFワ　シ　は　男　じ　ゃ　！^000000";
			next;
			menu "びっくりしました……",-;
			mes "[ミスティ]";
			mes "君はどこに目をつけてるのじゃ？";
			mes "君の目は節穴か!?";
			mes "　";
			mes "まったくもって失礼なのじゃ。";
			next;
			emotion 9,"";
			mes "[" + strcharinfo(0) + "]";
			mes "（どうやら自分でも気づかない間に";
			mes "疲労がたまっていたようだ。";
			mes "帰って寝た方がいいかもしれない……）";
			mes "　";
			mes "‐" + strcharinfo(0) + "は";
			mes "　きびすを返した‐";
			next;
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おーいどこへ行くのじゃ？";
			mes "　";
			mes "おーい……おーい……";
			next;
			mes "[^FF0000第六話終了^000000]";
			mes "‐第七話開始には、";
			mes "　^FF0000BaseLvを19以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			mes "[^FF0000第六話終了^000000]";
			mes "‐第七話開始には、";
			mes "　^FF0000BaseLvを19以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 7,1;
			close2;
			chgquest 100839,200975;
			set AC_QUEST_LV_6,6;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+7;
			end;
		}
		break;
	/////////   第七話   /////////
	case 6:
		switch(AC_QUEST_ST_6){
		case 0:
			mes "‐ポリン団のミスティは";
			mes "　人一人軽く納まってしまいそうな";
			mes "　大鍋の中身をぐるぐる";
			mes "　かき回している。";
			mes "　その隣で団長のネコリンが";
			mes "　テンション高く飛び跳ねていた‐";
			next;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ！";
			mes "もっと……もっとなのだ！";
			mes "　";
			mes "この魔法書によると、";
			mes "炎と友達になるまで炒めるのだ！";
			next;
			if(BaseLevel<19){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第七話開始には、";
				mes "　^FF0000BaseLvを19以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "炎は友達！　炎は友達！";
			next;
			menu "ミスティさん、だいぶ目が……",-;
			emotion 4,"";
			mes "[ネコリン]";
			mes "" + strcharinfo(0) + "";
			mes "いい所に来たのだ!!";
			next;
			menu "まさか、また材料ですか？",-;
			emotion 33, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そのまさかなのだ!!";
			mes "　";
			mes "これが最後の材料になるのだ！";
			next;
			menu "わかりました。とってきます",-;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "物分かりがよくて助かるのだ。";
			mes "　";
			mes "見ての通り、ミスティは";
			mes "必死に炒める作業をしているのだ！";
			mes "人手が足りないのだ。";
			next;
			mes "[ネコリン]";
			mes "ロッカーの葉……";
			mes "ワームテールの足……";
			mes "スケルトンの腕……";
			mes "ヒドラの皮！";
			mes "　";
			mes "これらが必要なのだ！";
			next;
			emotion 54, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "	炎は友達！";
			mes "炎はともだ……";
			mes "　";
			mes "ふう……疲れたのじゃ。";
			next;
			emotion 6, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "こら！　サボってちゃダメなのだ!!";
			mes "　";
			mes "‐額をぬぐって一息つくミスティに";
			mes "　ネコリンは活を入れた。";
			mes "　ミスティは慌てて、作業を再開する‐";
			next;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "炎は友達！　炎は友達！";
			next;
			emotion 54, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ちょっと目を離すとすぐこれなのだ。";
			mes "　";
			mes "困った奴なのだ。";
			next;
			menu "でも、頑張ってますよ",-;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "失敗したら意味がないのだ！";
			mes "　";
			mes "部下のしつけは大事なのだ！";
			next;
			menu "ところで自分は何を集めたら……",-;
			emotion 1,"";
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ！";
			next;
			mes "[ネコリン]";
			mes "材料をとれるのは、えーっと……";
			mes "^FF0000・^000000^FF0000ロッカー^000000";
			mes "^FF0000・^000000^FF0000ワームテール^000000";
			mes "^FF0000・^000000^FF0000スケルトン^000000";
			mes "^FF0000・^000000^FF0000ヒドラ^000000";
			mes "なのだ！";
			next; 
			emotion 52,""; 
			mes "[ネコリン]"; 
			mes "どれにするのか選ぶのだ！"; 
			mes "　"; mes "もちろん手伝ってくれたら"; 
			mes "単位をあげるのだ！"; 
			function	AC_PORING06_mobinfo	{
				switch(getarg(0)){
				case 100840:
					mes "[ネコリン]";
					mes "音楽好きのバッタなのだ。";
					mes "　";
					mes "こちらから手を出さない限り、";
					mes "無害なのだ。";
					mes "ジャンプする時の音が、";
					mes "うるさいのが難点な昆虫なのだ。";
					break;
				case 100842:
					mes "[ネコリン]";
					mes "可愛いモンスターなのだ。";
					mes "　";
					mes "動物のように見えるが……";
					mes "実は植物なのだ!!";
					mes "火に弱そうなのだ。";
					break;
				case 100844:
					mes "[ネコリン]";
					mes "倒れた冒険者が、";
					mes "骨になってよみがえったのだ!!";
					mes "　";
					mes "こわいのだ……";
					mes "でも聖なる攻撃や、";
					mes "回復魔法に弱いのだ！";
					break;
				case 100846:
					mes "[ネコリン]";
					mes "イソギンチャクなのだ。";
					mes "　";
					mes "水辺のモンスターで、";
					mes "動くことはないのだ。";
					mes "でも、遠距離から襲ってくるのだ。";
					mes "遠距離には遠距離なのだ！";
					break;
				}
				return;
			}
			function	AC_PORING06_warp;
			function	AC_PORING06	{
				set '@questid,0;
				//100840,魔法の秘薬③,0,1052,50,0,0,0,0
				//100842,魔法の秘薬③,0,1024,20,0,0,0,0
				//100844,魔法の秘薬③,0,1076,30,0,0,0,0
				//100846,魔法の秘薬③,0,1068,20,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000ロッカー^000000","^FF0000ワームテール^000000","^FF0000スケルトン^000000","^FF0000ヒドラ^000000")){
					case 1:
						AC_PORING06_mobinfo 100840;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ロッカー^000000」なのだ？";
						mes "　";
						mes "^FF000050匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうなのだ。";
						set '@questid, 100840;
						break;
					case 2:
						AC_PORING06_mobinfo 100842;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ワームテール^000000」なのだ？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうなのだ。";
						set '@questid, 100842;
						break;
					case 3:
						AC_PORING06_mobinfo 100844;
						next;
						mes "[ネコリン]";
						mes "「^FF0000スケルトン^000000」なのだ？";
						mes "　";
						mes "^FF000030匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうなのだ。";
						set '@questid, 100844;
						break;
					case 4:
						AC_PORING06_mobinfo 100846;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ヒドラ^000000」なのだ？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうなのだ。";
						set '@questid, 100846;
						break;
					}
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					emotion 33, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "モンスターを変えるのだ？";
					mes "　";
					mes "では、改めて選ぶのだ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ネコリン]";
				mes "決定なのだ！";
				mes "　";
				switch(AC_QUEST_ST_6){
				case 100840: mes "「^FF0000ロッカー^000000」が、"; break;
				case 100842: mes "「^FF0000ワームテール^000000」が、"; break;
				case 100844: mes "「^FF0000スケルトン^000000」が、"; break;
				case 100846: mes "「^FF0000ヒドラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのだ！";
				next;
				mes "[ネコリン]";
				mes "残りは私が集めるのだ";
				mes "戦って無理と判断したら、";
				mes "いつでも戻ってくるのだ！";
				mes "　";
				mes "魔法で現地まで送るのだ？";
				next;
				AC_PORING06_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING06_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 7,0;
				if(getarg(0)){
					emotion 21, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "君の健闘を祈るのだ！";
					mes "　";
					mes "しっかり準備をして頑張るのだ。";
					close;
				}
				emotion 78, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "うむ！";
				mes "いざ、出陣なのだ！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100840: warp "ac_prac_02.gat",108,33; break;
					case 100842: warp "ac_prac_02.gat",108,33; break;
					case 100844: warp "ac_spec_02.gat",124,59; break;
					case 100846: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100840: warp "prt_fild04.gat",380,332; break;
					case 100842: warp "pay_fild06.gat",69,286; break;
					case 100844: warp "pay_dun00.gat",21,183; break;
					case 100846: warp "iz_dun02.gat",339,328; break;
					}
				}
				return;
			}
			AC_PORING06;
			end;
		case 100840:
		case 100842:
		case 100844:
		case 100846:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				emotion 53;
				mes "[ミスティ]";
				mes "炎は友達！　炎は友達！";
				next;
				mes "[ネコリン]";
				mes "調子はどうなのだ？";
				mes "　";
				mes "秘薬の材料は、";
				mes "順調に集まってるのだ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100840: set '@select$,'@select$ + "「^FF0000ロッカー^000000」について教えて";  break;
				case 100842: set '@select$,'@select$ + "「^FF0000ワームテール^000000」について教えて";  break;
				case 100844: set '@select$,'@select$ + "「^FF0000スケルトン^000000」について教えて"; break;
				case 100846: set '@select$,'@select$ + "「^FF0000ヒドラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING06_warp 0;
				case 2:
					emotion 4, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "少し厳しかったのだ？";
					next;
					mes "[ネコリン]";
					mes "ちなみに、材料は鮮度が命なのだ。";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのだ、良いのだ？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33, "ネコリン#ac_Necorin";
						mes "[ネコリン]";
						mes "うむ。";
						mes "がんばるのだっ。";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るのだ？";
						next;
						AC_PORING06_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "では、改めて選ぶのだ！";
					AC_PORING06;
					end;
				case 3:
					AC_PORING06_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12,"";
			mes "[ミスティ]";
			mes "おお！";
			mes "お帰りなのじゃ。";
			next;
			menu "炒め終わったのですか？",-;
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うむ！";
			mes "無事、炎と友達になれたのじゃ！";
			next;
			mes "[ミスティ]";
			mes "それよりもどうじゃった？";
			mes "収穫のほうは？";
			next;
			menu "これで良いですか？",-;
			mes "[ミスティ]";
			mes "ご苦労だったのぅ。";
			mes "これだけあればばっちりじゃ！";
			mes "　";
			mes "鮮度が落ちる前に、";
			mes "魔法の秘薬作りに取り掛かるのじゃ！";
			next;
			menu "いよいよ完成ですね",-;
			emotion 2,"";
			emotion 19, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "待つのだ！";
			mes "私を忘れちゃ駄目なのだ！";
			next;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿！";
			mes "どこへ行っておったのじゃ？";
			next;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "最後の材料を集めに行ってたのだ。";
			mes "　";
			mes "さぁ！　これを使うのだ！";
			next;
			mes "[ミスティ]";
			mes "おお……忘れてたのじゃ。";
			mes "　";
			mes "フッフッフッ。";
			mes "ついに姉上に仕返しをする時が！";
			next;
			menu "効果がまだ分からないのに？",-;
			mes "[ミスティ]";
			mes "いやいや……絶対に";
			mes "「ワシの命令を聞く薬」なのじゃ！";
			mes "ワシの長年の勘がそう告げておる！";
			mes "　";
			mes "今まで作った物と、残りの材料を";
			mes "大きい鍋に入れて煮込むのじゃ！";
			next;
			emotion 9,"";
			mes "[ネコリン]";
			mes "ミスティの勘は当たった事がないのだ。";
			mes "私の予想では「笑い薬」なのだ！";
			mes "　";
			mes "笑いが止まらなくてみんな困るのだ。";
			mes "その間に世界を征服するのだ！";
			next;
			misceffect 17, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "最後の仕上げなのじゃ！";
			next;
			misceffect 608, "ミスティ#ac_Misty";
			emotion 7, "ネコリン#ac_Necorin";
			emotion 7, "ミスティ#ac_Misty";
			emotion 7,"";
			mes "‐激しい煙が";
			mes "　" + strcharinfo(0) + "達を";
			mes "　包み込んだ！‐";
			next;
			mes "[ミスティ]";
			mes "ゴホッゴホッ……";
			mes "　";
			mes "んー、イメージしてたのとは違うのぅ。";
			mes "こんな少量しか出来ないのか……";
			next;
			mes "[ネコリン]";
			mes "これでは一人分しかないのだ……";
			next;
			mes "[ミスティ]";
			mes "まあ、出来たは出来たのじゃ！";
			mes "早速、姉上に飲ませてやるのじゃ！";
			next;
			menu "どうやって飲ませるの？",-;
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ。";
			mes "この盗んだ姉上の鈴を使うのじゃ！";
			mes "　";
			mes "これは姉上の一番お気に入りの鈴……";
			mes "今頃探しているはずなのじゃ！";
			next;
			mes "[ネコリン]";
			mes "ミスティ、準備が良すぎるのだ。";
			next;
			emotion 19,"";
			mes "[ミスティ]";
			mes "姉上は、今頃走り回って疲れておる。";
			mes "ワシの所に鈴の在りかを聞きに来るのも";
			mes "時間の問題じゃ！";
			mes "　";
			mes "そこで……栄養ドリンクと";
			mes "嘘をついて飲ませるのじゃ！";
			next;
			menu "やっぱり止めたほうが……",-;
			emotion 0, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "いくらワシでも大丈夫じゃよ♪";
			mes "　";
			mes "そっと秘薬を差し出すだけの";
			mes "簡単な作業なのじゃ！";
			mes "　";
			mes "……あ！　姉上が来た！";
			next;
			cutin "job_black_hucke03.bmp", 2;
			mes "[ヒュッケ]";
			mes "……ミスティ……私の大事な鈴。";
			mes "……知らない？";
			next;
			emotion 19, "ネコリン#ac_Necorin";
			emotion 19,"";
			mes "[ミスティ]";
			mes "さぁ……ワシは知らんぞ？";
			mes "　";
			mes "それより姉上、お疲れじゃろ？";
			mes "栄養ドリンクじゃ！";
			mes "姉上のために作ったのじゃ！";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "……";
			mes "……ありがとう。";
			mes "ミスティ……気がきく……";
			mes "　";
			mes "‐ヒュッケは栄養ドリンクと偽られた";
			mes "　薬を飲んでしまった！‐";
			next;
			cutin "job_black_hucke02.bmp", 255;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ……";
			mes "飲んだ！　飲んだのじゃ！";
			next;
			mes "[ヒュッケ]";
			mes "…………!!";
			mes "くっ……力……入らない。";
			mes "……何……飲ませた！";
			next;
			mes "[ミスティ]";
			mes "姉上……";
			mes "それは栄養ドリンクではない。";
			mes "魔法の秘薬なのじゃ！";
			mes "　";
			mes "さぁ、";
			mes "ワシの命令を聞いてもらおうかのぅ。";
			next;
			menu "あわわわわ……",-,"お姉さん大丈夫ですか？",-;
			cutin "job_black_hucke01.bmp", 2;
			mes "[ヒュッケ]";
			mes "………!?";
			mes "体……傷……癒える。";
			mes "まるで……力……みなぎる！";
			next;
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "むむぅ、";
			mes "どうやら魔法の秘薬の正体は、";
			mes "健康になる薬だったようなのだ！";
			mes "　";
			mes "これでは世界征服できないのだ。";
			mes "……残念なのだ。";
			next;
			cutin "job_black_hucke02.bmp", 255;
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そ……そんなぁ！";
			mes "　";
			mes "‐その時、ミスティの懐から";
			mes "　ヒュッケの鈴が転げ落ちてしまった‐";
			next;
			cutin "job_black_hucke03.bmp", 2;
			mes "[ヒュッケ]";
			mes "それ……私の……鈴！";
			mes "……騙す……泥棒";
			mes "犯人……ミスティ！";
			mes "私は、怒った！";
			next;
			cutin "job_black_hucke03.bmp", 255;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ひゃあああぁ。";
			mes "姉上が怒った！";
			mes "　";
			mes "急いで逃げるのじゃ～!!";
			next;
			emotion 16, "ネコリン#ac_Necorin";
			emotion 16,"";
			mes "[ネコリン]";
			mes "今回の件は、";
			mes "ミスティ一人で全部やったのだ。";
			mes "　";
			mes "私と";
			mes "" + strcharinfo(0) + "は、";
			mes "関係ないのだ！";
			next;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ワシを見捨てるなんて酷いのじゃ！";
			mes "　";
			mes "助けてくれなのじゃ～～!!";
			mes "　";
			mes "‐ミスティは、一目散に逃げたした‐";
			next;
			cutin "job_black_hucke03.bmp", 2;
			mes "[ヒュッケ]";
			mes "ミスティ……待つのです！";
			mes "　";
			mes "‐逃げたミスティをヒュッケが追う。";
			mes "　" + strcharinfo(0) + "と";
			mes "　ネコリンはその様子を見送った‐";
			next;
			cutin "job_black_hucke03.bmp", 255;
			emotion 19, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ふう……助かったのだ。";
			next;
			menu "ところで……",-;
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "君の単位を増やしておいたのだ。";
			mes "ついでに、これもプレゼントなのだ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100848;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight2(569,200, 11518,50)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 200;
			getitem 11518, 50;
			chgquest 100848,100849;
			if(checkre()) {
				getexp 90,0;
				getexp 90,0;
				getexp 90,0;
				getexp 90,0;
				getexp 0,60;
				getexp 0,60;
				getexp 0,60;
				getexp 0,60;
			}
			else {
				getexp 900,0;
				getexp 900,0;
				getexp 900,0;
				getexp 900,0;
				getexp 0,600;
				getexp 0,600;
				getexp 0,600;
				getexp 0,600;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			mes "[ネコリン]";
			mes "君も大分強くなってきたのだ。";
			mes "　";
			mes "これから、もっと強いモンスターも";
			mes "どんどん出てくるのだ……";
			mes "　";
			mes "めげずに頑張るのだ！";
			next;
			menu "はいっ、がんばります！",-;
			emotion 14,"";
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "また何かあったら宜しく頼むのだ。";
			mes "　";
			mes "それではまた会おうなのだ。";
			next;
			mes "‐秘薬は結果的に良い物が出来た。";
			mes "　";
			mes "　材料集めは大変だったが、";
			mes "　秘薬の効果が楽しみだった事は";
			mes "　ポリン団には";
			mes "　伝えないでおくべきだろう‐";
			next;
			mes "[^FF0000第七話終了^000000]";
			mes "‐第八話開始には、";
			mes "　^FF0000BaseLvを22以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 8,1;
			close2;
			chgquest 100849, 200980;
			set AC_QUEST_LV_6,7;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+7;
			end;
		}
		break;
	/////////   第八話   /////////
	case 7:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<22){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第八話開始には、";
				mes "　^FF0000BaseLvを22以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ";
			mes "元気にしておったか？";
			next;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あの後、姉上に捕まってな……";
			mes "生死の狭間を彷徨っておったのじゃ。";
			mes "　";
			mes "なんせ、あの姉上の料理を";
			mes "大量に食べさせられたのじゃからなぁ。";
			next;
			menu "それは大変でしたね",-;
			mes "[ネコリン]";
			mes "ミスティはしばらく、";
			mes "生きた目をしていなかったのだ。";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あの料理の味は地獄だったのじゃ……";
			mes "過去最強の味だったのじゃ。";
			next;
			mes "[ミスティ]";
			mes "そうそう、この前作った秘薬が";
			mes "お年寄りにたくさん売れてのぅ……";
			mes "活動資金がいっぱいなのじゃ！";
			mes "　";
			mes "おかげでほれ、これを見るのじゃ！";
			next;
			emotion 0,"";
			mes "‐そう言って、ミスティが示した先……";
			mes "　本棚の影に不自然に";
			mes "　^0000FFそれ^000000はあった‐";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "‐魔王を象徴する黒光りした大きな角";
			mes "　全てをなぎ払う様な大きな鎌の影";
			mes "　獣のように素早く動く車体‐";
			next;
			mes "‐全てを見透かすかのような";
			mes "　大きな瞳からは、";
			mes "　今にも闇夜を切り裂く";
			mes "　光線をだしそうだ。‐";
			next;
			mes "‐車体には、ご丁寧に";
			mes "　製造元：ポリンＤＡＮ!!";
			mes "　とロゴまでプリントされている";
			mes "　";
			mes "　^0000FFロボット^000000であった‐";
			next;
			menu "ロボット!?",-;
			emotion 3, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうなのじゃ！";
			mes "かっこいいじゃろ？";
			mes "名前は「バフォリン」なのじゃ！";
			next;
			emotion 3, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "憧れのバフォメット様を";
			mes "モチーフにして作ったのだ！";
			next;
			mes "[ミスティ]";
			mes "悪の組織といえばロボットじゃろ？";
			mes "これで世界征服をするのじゃ！";
			next;
			menu "!!",-;
			emotion 19,"";
			mes "[ミスティ]";
			mes "ただ……";
			mes "この取扱説明書によるとな、";
			mes "｢バフォリン」を動かす為には";
			mes "莫大な燃料が必要になるのじゃ!!";
			next;
			mes "‐どうやら、ミスティが";
			mes "　大事に脇に抱えている本は";
			mes "　バフォリンの説明書のようだ。";
			mes "　やたら汚れているのは、";
			mes "　バフォリンの組み立てが";
			mes "　余程困難だったからなのだろうか？‐";
			next;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "なんじゃ？";
			mes "説明書を見てみたいのか？";
			mes "ほれ、大事に扱うのじゃぞ。";
			next;
			mes "‐ミスティが見せてくれた説明書には";
			mes "　^0000FF子供用^000000ロボットと書かれていた。";
			mes "　";
			mes "　身の周りの安全をいつも保障する";
			mes "　レッケンベル社製の";
			mes "　おもちゃのようだ。";
			mes "　安全を意味するBLZBマーク付だ‐";
			next;
			menu "…………",-;
			emotion 9,"";
			mes "[ミスティ]";
			mes "難しい説明書じゃろ？";
			mes "　";
			mes "このワシですら、";
			mes "やっとの思いで作成したのじゃ！";
			next;
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "世界征服ロボが買えるなんて……";
			mes "良い世の中になったもんじゃなぁ。";
			next;
			menu "是非とも動かしてみたいですね",-;
			emotion 33,"";
			emotion 56, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "今日の";
			mes "" + strcharinfo(0) + "は、";
			mes "ノリが良いのだ！";
			next;
			mes "[ミスティ]";
			mes "おっと、燃料の話だったかのぅ。";
			mes "　";
			mes "取扱説明書によるとな、";
			mes "「ぬるん」という燃料が必要らしいぞ。";
			next;
			mes "‐ポリン団の二人は";
			mes "　" + strcharinfo(0) + "に";
			mes "　うるうるさせた目を向けている。";
			mes "　これは……";
			mes "　今回も…………‐";
			next;
			menu "また……ですか？",-;
			emotion 32,"";
			emotion 74, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うん";
			mes "　";
			mes "またじゃなぁ……";
			next;
			emotion 74, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "うん。";
			mes "　";
			mes "またなのだ……";
			next;
			menu "……しょうがないですね",-;
			mes "[ミスティ]";
			mes "手伝ってくれてありがたいのじゃ。";
			mes "　";
			mes "もちろん、お礼はするぞ。";
			next;
			emotion 22, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "さてさて、";
			mes "この燃料を作成する為の素材には……";
			mes "えーっと……";
			mes "　";
			mes "‐ミスティはキョロキョロと";
			mes "　何かを探している‐";
			next;
			mes "[ネコリン]";
			mes "「ぬるん」の作成法は";
			mes "ロボットの説明書に";
			mes "書かれてなかったから";
			mes "ミスティに調べさせたのだ。";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "おおっ！";
			mes "あったのじゃ!!";
			mes "　";
			mes "‐積み上げられた本の中から";
			mes "　目当ての本を見つけたようだ‐";
			next;
			mes "[ミスティ]";
			mes "この「フローラの秘法」という";
			mes "書物によるとじゃな……";
			next;
			emotion 5, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "緑ゼリー……";
			mes "テントウムシの皮……";
			mes "スケルトンの頭……";
			mes "フローラの種!!";
			mes "　";
			mes "これらが必要なようじゃ！";
			next;
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000ポポリン^000000";
			mes "^FF0000・^000000^FF0000スタイナー^000000";
			mes "^FF0000・^000000^FF0000スケルトン^000000";
			mes "^FF0000・^000000^FF0000フローラ^000000";
			mes "なのだ！";
			next; 
			mes "[ミスティ]";
			mes "ネコリン殿は物知りだのぅ。";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING07_mobinfo	{
				switch(getarg(0)){
				case 100850:
					mes "[ミスティ]";
					mes "ポリンは、もう知っておるな？";
					mes "ポリンをサクラ餅に例えると";
					mes "こ奴は、ヨモギ餅じゃな♪";
					mes "　";
					mes "ただ、見た目よりかなり強いのじゃ。";
					mes "十分注意するのじゃ！";
					break;
				case 100852:
					mes "[ミスティ]";
					mes "てんとう虫じゃな。";
					mes "　";
					mes "見た目は、小さくて弱そうじゃが、";
					mes "とってもすばしっこいのじゃ!!";
					break;
				case 100854:
					mes "[ミスティ]";
					mes "倒れた冒険者が、";
					mes "骨になってよみがえったのじゃ！";
					mes "　";
					mes "すごく恐ろしいのじゃ……";
					mes "でも聖なる攻撃や、";
					mes "回復魔法に弱いのじゃ♪";
					break;
				case 100856:
					mes "[ミスティ]";
					mes "花なのじゃ……";
					mes "人を食べようとする食人植物なのじゃ！";
					mes "　";
					mes "しかし、植物だから動けないのじゃ。";
					mes "遠くから攻撃出来れば楽なんじゃがな。";
					break;
				}
				return;
			}
			function	AC_PORING07_warp;
			function	AC_PORING07	{
				set '@questid,0;
				//100850,世界征服ロボ①,0,1031,20,0,0,0,0
				//100852,世界征服ロボ①,0,1174,15,0,0,0,0
				//100854,世界征服ロボ①,0,1076,40,0,0,0,0
				//100856,世界征服ロボ①,0,1118,5,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000ポポリン^000000","^FF0000スタイナー^000000","^FF0000スケルトン^000000","^FF0000フローラ^000000")){
					case 1:
						AC_PORING07_mobinfo 100850;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ポポリン^000000」じゃな？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100850;
						break;
					case 2:
						AC_PORING07_mobinfo 100852;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スタイナー^000000」じゃな？";
						mes "　";
						mes "^FF000015匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100852;
						break;
					case 3:
						AC_PORING07_mobinfo 100854;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スケルトン^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100854;
						break;
					case 4:
						AC_PORING07_mobinfo 100856;
						next;
						mes "[ミスティ]";
						mes "「^FF0000フローラ^000000」じゃな？";
						mes "　";
						mes "^FF00005匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100856;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ネコリン]";
				mes "決定なのだ！";
				mes "　";
				switch(AC_QUEST_ST_6){
				case 100850: mes "「^FF0000ポポリン^000000」が、"; break;
				case 100852: mes "「^FF0000スタイナー^000000」が、"; break;
				case 100854: mes "「^FF0000スケルトン^000000」が、"; break;
				case 100856: mes "「^FF0000フローラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのだ！";
				next;
				mes "[ミスティ]";
				mes "残りはワシが集めよう！";
				mes "戦って無理と判断したら、";
				mes "いつでも戻ってくるのじゃ！";
				mes "　";
				mes "そうじゃ……";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING07_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING07_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 8,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100850: warp "ac_prac_01.gat",225,31; break;
					case 100852: warp "ac_prac_02.gat",108,33; break;
					case 100854: warp "ac_spec_02.gat",124,59; break;
					case 100856: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100850: warp "pay_fild04.gat",200,178; break;
					case 100852: warp "mjolnir_06.gat",380,74; break;
					case 100854: warp "pay_dun00.gat",21,183; break;
					case 100856: warp "mjolnir_11.gat",23,220; break;
					}
				}
				return;
			}
			AC_PORING07;
			end;
		case 100850:
		case 100852:
		case 100854:
		case 100856:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				emotion 2;
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「ぬるん」の材料は";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100850: set '@select$,'@select$ + "「^FF0000ポポリン^000000」について教えて";  break;
				case 100852: set '@select$,'@select$ + "「^FF0000スタイナー^000000」について教えて";  break;
				case 100854: set '@select$,'@select$ + "「^FF0000スケルトン^000000」について教えて"; break;
				case 100856: set '@select$,'@select$ + "「^FF0000フローラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING07_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は鮮度が命なのじゃ！";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING07_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING07;
					end;
				case 3:
					AC_PORING07_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12,"";
			mes "[ミスティ]";
			mes "おお！";
			mes "お帰りなのじゃ。";
			next;
			menu "素材を持ってきました",-;
			mes "[ミスティ]";
			mes "早くこっちによこすのじゃ！";
			next;
			menu "どうぞ",-;
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うんうん……これじゃ！";
			next;
			menu "ところで……",-;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！";
			mes "そうじゃった、そうじゃった。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100858;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight(569,200)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 200;
			chgquest 100858,100859;
			if(checkre()) {
				getexp 100,0;
				getexp 100,0;
				getexp 100,0;
				getexp 100,0;
				getexp 0,120;
				getexp 0,120;
				getexp 0,120;
				getexp 0,120;
			}
			else {
				getexp 1000,0;
				getexp 1000,0;
				getexp 1000,0;
				getexp 1000,0;
				getexp 0,1200;
				getexp 0,1200;
				getexp 0,1200;
				getexp 0,1200;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ。";
			mes "　";
			mes "ついに「バフォリン」が、";
			mes "起動するのじゃ！";
			next;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "燃料を作るのだ！";
			mes "　";
			mes "‐ポリン団の二人は";
			mes "　魔法の秘薬を作るのに使っていた";
			mes "　大鍋をどこからか引っ張り出すと";
			mes "　材料をどばっと入れて火をつけた‐";
			next;
			mes "（コトコトコト……）";
			next;
			mes "（コトコトコトコト……）";
			next;
			mes "‐出来上がったらしき燃料「ぬるん」を";
			mes "　ミスティはロボット「バフォリン」に";
			mes "　投入した！‐";
			next;
			misceffect 305, "ミスティ#ac_Misty";
			mes "‐大きな駆動音と共に";
			mes "　白い煙を吐き出しつつ";
			mes "　動き始めたバフォリン‐";
			next;
			misceffect 17, "ミスティ#ac_Misty";
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "これで完成なのだ！";
			mes "「バフォリン」を起動するのだ！";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "「バフォリン」起動じゃ！";
			next;
			misceffect 79, "ミスティ#ac_Misty";
			mes "‐恐ろしいほど大きな鎌を";
			mes "　振り上げバフォリンが";
			mes "　本棚の隅から動き出した‐";
			mes "　";
			mes "（バギャーン!!";
			mes "　";
			mes "　ゴゴゴゴゴッ……）";
			next;
			emotion 38, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "やったのじゃ！　起動したのじゃ！";
			next;
			mes "‐ネコリンやミスティが";
			mes "　バフォリンの起動に";
			mes "　歓喜したとたん……‐";
			next;
			emotion 23, "ネコリン#ac_Necorin";
			emotion 23, "ミスティ#ac_Misty";
			emotion 23,"";
			mes "（ブブィーン";
			mes "　かか……";
			mes "　がが……";
			mes "　ぷこっ";
			mes "　カシャン！）";
			mes "　";
			mes "‐バフォリンは動きを止めてしまった‐";
			next;
			mes "[ミスティ]";
			mes "壊れたのじゃ!?";
			mes "どうしてなのじゃ……";
			mes "　";
			mes "この本の通りに作成したのに……";
			next;
			menu "本を見せてください",-;
			mes "[ミスティ]";
			mes "これなのじゃ。";
			next;
			mes "‐香りで覚醒・フローラの秘法‐";
			mes "　";
			mes "‐肌荒れなんて、もうバイバイ!!";
			mes "　小さなお子様が、扱っても";
			mes "　心配御無用！";
			mes "　まずは、お近くの一反木綿で!!‐";
			next;
			menu "この本って……",-;
			emotion 1,"";
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ！";
			mes "「ぬるん」じゃないのだ！";
			mes "「バフォリン」の取扱説明書には";
			mes "「めるん」と書いてあるのだ！";
			next;
			mes "[ミスティ]";
			mes "な、なんじゃって！";
			next;
			emotion 57, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "　";
			mes "よく見たらこの本には、";
			mes "「お肌に優しい洗剤の作り方」";
			mes "と最後に書いてあったのじゃ……";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ショックなのじゃ……";
			mes "お金を全部使ってしまったのじゃ。";
			mes "　";
			mes "今はそっとしておいて欲しいのじゃ。";
			next;
			mes "[^FF0000第八話終了^000000]";
			mes "‐第九話開始には、";
			mes "　^FF0000BaseLvを25以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 9,1;
			close2;
			chgquest 100859,200985;
			set AC_QUEST_LV_6,8;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+8;
			end;
		}
		break;
	/////////   第九話   /////////
	case 8:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<25){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第九話開始には、";
				mes "　^FF0000BaseLvを25以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ。";
			mes "元気にしておったか？";
			next;
			emotion 8, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "この間、燃料と間違えて";
			mes "作った洗剤が";
			mes "主婦に大人気なのじゃ！";
			mes "沢山売れたのじゃぁ。";
			mes "　";
			mes "燃料作成資金も貯まったのじゃ！";
			next;
			menu "お肌にやさしいですからね",-;
			emotion 32,"";
			mes "[ネコリン]";
			mes "今度こそ間違えずに作るのだ！";
			next;
			menu "本当に大丈夫ですか？",-;
			mes "[ミスティ]";
			mes "大丈夫なのじゃ。";
			mes "ネコリン殿は信用出来るのじゃ！";
			next;
			mes "[ネコリン]";
			mes "うむ！";
			mes "手伝ってくれたら単位も上げるのだ。";
			mes "　";
			mes "どうなのだ？";
			next;
			menu "わかりました、手伝いましょう",-;
			emotion 52, "ネコリン#ac_Necorin";
			emotion 14, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "手伝ってくれてありがたいのじゃ♪";
			mes "　";
			mes "今度こそ世界征服ロボ誕生なのじゃ！";
			next;
			mes "[ミスティ]";
			mes "さてさて、";
			mes "「めるん」を作成する為の素材は";
			mes "　";
			mes "えーっと……";
			next;
			mes "‐ミスティは前回の時と同じく";
			mes "　積み上げられた本の中から";
			mes "　お目当ての本を探しているようだ‐";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ、これなのだ！";
			mes "この本に書いてあるのだ。";
			next;
			mes "[ミスティ]";
			mes "おぉ、そうじゃそうじゃ。";
			mes "この「フローラの奇跡」という";
			mes "書物によるとだな……";
			next;
			mes "[ミスティ]";
			mes "サベージベベの足……";
			mes "スモーキーの尻尾……";
			mes "ホルンのハサミ……";
			mes "フローラの花びら！";
			mes "　";
			mes "これらが必要なようじゃ！";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000サベージベベ^000000";
			mes "^FF0000・^000000^FF0000スモーキー^000000";
			mes "^FF0000・^000000^FF0000ホルン^000000";
			mes "^FF0000・^000000^FF0000フローラ^000000";
			mes "なのだ！";
			next; 
			mes "[ミスティ]";
			mes "ネコリン殿は物知りだのぅ。";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING08_mobinfo	{
				switch(getarg(0)){
				case 100860:
					mes "[ミスティ]";
					mes "可愛いのじゃ！";
					mes "　";
					mes "ブヒ♪　ブヒ♪　ブヒ♪";
					mes "　";
					mes "小さくて本当に可愛いのじゃ!!";
					mes "可愛いのは子供のうちだけなのじゃ。";
					break;
				case 100862:
					mes "[ミスティ]";
					mes "たぬきじゃな。";
					mes "　";
					mes "とっても恥ずかしがり屋なので、";
					mes "たまに姿を隠してしまうのじゃ!!";
					mes "しかも、隠れて傷を回復するから";
					mes "注意するのじゃぞ！";
					break;
				case 100864:
					mes "[ミスティ]";
					mes "大きなクワガタじゃな。";
					mes "　";
					mes "動きは、それほど早くないのじゃ。";
					mes "魔法の詠唱に反応して";
					mes "攻撃してくるのじゃ！";
					break;
				case 100866:
					mes "[ミスティ]";
					mes "花なのじゃ……";
					mes "人を食べようとする食人植物なのじゃ！";
					mes "　";
					mes "しかし、植物だから動けないのじゃ。";
					mes "遠くから攻撃出来れば楽なんじゃがな。";
					break;
				}
				return;
			}
			function	AC_PORING08_warp;
			function	AC_PORING08	{
				set '@questid,0;
				//100860,世界征服ロボ②,0,1167,100,0,0,0,0
				//100862,世界征服ロボ②,0,1056,25,0,0,0,0
				//100864,世界征服ロボ②,0,1128,20,0,0,0,0
				//100866,世界征服ロボ②,0,1118,10,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000サベージベベ^000000","^FF0000スモーキー^000000","^FF0000ホルン^000000","^FF0000フローラ^000000")){
					case 1:
						AC_PORING08_mobinfo 100860;
						next;
						mes "[ミスティ]";
						mes "「^FF0000サベージベベ^000000」じゃな？";
						mes "　";
						mes "^FF0000100匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100860;
						break;
					case 2:
						AC_PORING08_mobinfo 100862;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スモーキー^000000」じゃな？";
						mes "　";
						mes "^FF000025匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100862;
						break;
					case 3:
						AC_PORING08_mobinfo 100864;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ホルン^000000」じゃな？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100864;
						break;
					case 4:
						AC_PORING08_mobinfo 100866;
						next;
						mes "[ミスティ]";
						mes "「^FF0000フローラ^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100866;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6,'@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ミスティ]";
				mes "決定なのじゃ！";
				switch(AC_QUEST_ST_6){
				case 100860: mes "「^FF0000サベージベベ^000000」が、"; break;
				case 100862: mes "「^FF0000スモーキー^000000」が、"; break;
				case 100864: mes "「^FF0000ホルン^000000」が、"; break;
				case 100866: mes "「^FF0000フローラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのじゃ！";
				mes "　";
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING08_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING08_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 9,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100860:
					case 100862: warp "ac_prac_03.gat",29,337; break;
					case 100864: warp "ac_prac_02.gat",108,33; break;
					case 100866: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100860: warp "prt_fild09.gat",312,193; break;
					case 100862: warp "pay_fild09.gat",19,91; break;
					case 100864: warp "mjolnir_09.gat",106,34; break;
					case 100866: warp "mjolnir_11.gat",23,220; break;
					}
				}
				return;
			}
			AC_PORING08;
			end;
		case 100860:
		case 100862:
		case 100864:
		case 100866:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				emotion 2;
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「ぬるん」の材料は";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100860: set '@select$,'@select$ + "「^FF0000サベージベベ^000000」について教えて";  break;
				case 100862: set '@select$,'@select$ + "「^FF0000スモーキー^000000」について教えて";  break;
				case 100864: set '@select$,'@select$ + "「^FF0000ホルン^000000」について教えて"; break;
				case 100866: set '@select$,'@select$ + "「^FF0000フローラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING08_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は鮮度が命なのじゃ！";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING08_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING08;
					end;
				case 3:
					AC_PORING08_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12,"";
			mes "[ミスティ]";
			mes "おお！";
			mes "お帰りなのじゃ。";
			next;
			menu "素材を持ってきました",-;
			mes "[ミスティ]";
			mes "早くこっちによこすのじゃ！";
			next;
			menu "どうぞ",-;
			emotion 33, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うんうん……これじゃ！";
			next;
			menu "ところで……",-;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！";
			mes "そうじゃった、そうじゃった。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6,100868;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight2(569,200, 11518,50)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 200;
			getitem 11518, 50;
			chgquest 100868,100869;
			if(checkre()) {
				getexp 200,0;
				getexp 200,0;
				getexp 200,0;
				getexp 0,300;
				getexp 0,300;
				getexp 0,300;
			}
			else {
				getexp 2000,0;
				getexp 2000,0;
				getexp 2000,0;
				getexp 0,3000;
				getexp 0,3000;
				getexp 0,3000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ。";
			mes "　";
			mes "今度こそ！";
			mes "ついに……！";
			mes "「バフォリン」が起動するのじゃ！";
			next;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "「めるん」を作るのだ！";
			mes "　";
			mes "‐ポリン団の二人は";
			mes "　魔法の秘薬を作るのに使っていた";
			mes "　大鍋をどこからか引っ張り出すと";
			mes "　材料をどばっと入れて火をつけた‐";
			next;
			mes "（コトコトコト……）";
			next;
			mes "（コトコトコトコト……）";
			next;
			mes "‐出来上がったらしき燃料「めるん」を";
			mes "　ミスティはロボット「バフォリン」に";
			mes "　投入した！‐";
			next;
			misceffect 305, "ミスティ#ac_Misty";
			mes "‐大きな駆動音と共に";
			mes "　白い煙を吐き出しつつ";
			mes "　動き始めたバフォリン‐";
			next;
			misceffect 17, "ミスティ#ac_Misty";
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "これで完成なのだ！";
			mes "バフォリンを起動するのだ！";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "バフォリン起動じゃ！";
			next;
			misceffect 79, "ミスティ#ac_Misty";
			mes "‐鋭い目に光が宿り";
			mes "　唯でさえ大きな瞳が";
			mes "　より大きく輝き出した‐";
			mes "　";
			mes "（バギャーン!!";
			mes "　";
			mes "　ゴゴゴッ……）";
			next;
			emotion 38, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "やったのじゃ！";
			mes "起動したのじゃ！";
			mes "今度こそ成功なのじゃ！";
			next;
			mes "[バフォリン]";
			mes "^0000FFキドウチュウ……";
			mes "シバラクオマチクダサイ……";
			mes "　";
			mes "……ッマ!!!!^000000";
			next;
			mes "[ネコリン]";
			mes "まずは、試し運転なのだ！";
			mes "周りを歩かせるのだ！";
			next;
			emotion 27, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ゆけ！　バフォリン!!";
			mes "突撃するのじゃー！";
			next;
			mes "‐しかし、バフォリンは";
			mes "　動き出すと同時に";
			mes "　鋭く大きな目から発する";
			mes "　光線が激しく点滅を繰り返し";
			mes "　そのまま、光を失ってしまった‐";
			next;
			mes "[バフォリン]";
			mes "^0000FFキドウテイシ……";
			mes "キドウテイシ……";
			mes "　";
			mes "エネルギー……ゼロ……^000000";
			next;
			mes "（ウィーン……";
			mes "……ウィーン";
			mes "………………";
			mes "…………プシ^808080ュー";
			mes "^c0c0c0……^000000）";
			next;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あれ？";
			mes "動かなくなったのじゃ……";
			next;
			emotion 1, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "どうしてなのだ？";
			mes "作り方はあってるはずなのだ。";
			next;
			menu "取扱説明書を見せてください",-;
			mes "[ネコリン]";
			mes "これなのだ。";
			next;
			emotion 9, "ネコリン#ac_Necorin";
			emotion 9, "ミスティ#ac_Misty";
			mes "‐ネコリンに渡された";
			mes "　「バフォリン」の取扱説明書には";
			mes "　確かに「めるん」と書いてある。";
			mes "　";
			mes "　……おや？";
			mes "　後ろの文字が透けている？‐";
			next;
			emotion 0,"";
			mes "[" + strcharinfo(0) + "]";
			mes "（これは「めるん」ではなく";
			mes "「のるん」だ!!）";
			next;
			menu "これ「のるん」ですよ？",-;
			mes "[ネコリン]";
			mes "そんな馬鹿ななのだ！";
			mes "よく見せるのだ！";
			mes "　";
			mes "……!!";
			mes "では、この作り方の本は……";
			next;
			mes "‐みなぎるパワー・フローラの奇跡‐";
			mes "　";
			mes "‐揚げ物、炒め物、気にしない。";
			mes "　ぽっちゃり肥満も、気にしない。";
			mes "　食べて痩せれる不思議な食用油";
			mes "　早く使って！　試してみて!!";
			mes "　始めは、ポイズンスポアから!!‐";
			next;
			emotion 9,"";
			menu "体に優しい食用油だそうです",-;
			emotion 9, "ネコリン#ac_Necorin";
			emotion 9, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "また間違えたのじゃ……";
			mes "　";
			mes "でも、ワシの責任じゃないのだ。";
			mes "ネコリン殿！　どうしてくれるのじゃ！";
			next;
			emotion 6, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "うるさいのだ!!";
			mes "団長は何をしてもいいのだ！";
			next;
			emotion 57, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿はずるいのじゃ……";
			mes "またお金を全部使ってしまったのじゃ。";
			mes "　";
			mes "今は、そっとしておいて欲しいのじゃ。";
			next;
			mes "[^FF0000第九話終了^000000]";
			mes "‐第十話開始には、";
			mes "　^FF0000BaseLvを28以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 10,1;
			close2;
			chgquest 100869,200990;
			set AC_QUEST_LV_6,9;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+8;
			end;
		}
		break;
	/////////   第十話   /////////
	case 9:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<28){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十話開始には、";
				mes "　^FF0000BaseLvを28以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ミスティ]";
			mes "おお？";
			mes "" + strcharinfo(0) + "";
			mes "いい所に来た♪";
			next;
			menu "どうしたのですか？",-;
			emotion 8, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "実はな……";
			mes "　";
			mes "健康志向の奥様方に食用油「めるん」が";
			mes "馬鹿売れなのじゃ！";
			mes "　";
			mes "「のるん」作成資金も貯まったのじゃ！";
			next;
			menu "身体に優しい油ですからね",-;
			emotion 21, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "今度こそ……!!";
			mes "今度こそ間違えずに作るのだ！";
			mes "　";
			mes "だから君に「のるん」の作成方法が";
			mes "書かれた本を確認してほしいのだ！";
			next;
			menu "わかりました、見せてください",-;
			mes "[ネコリン]";
			mes "この本なのだ！";
			next;
			mes "‐廃油・燃料革命新書";
			mes "　";
			mes "　－目次－";
			mes "　１．廃油と材料を合わせる";
			mes "　２．科学反応を起こす";
			mes "　３．子供用ロボット燃料完成‐";
			next;
			menu "この本で、間違いないですね",-;
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "よかったのだ！";
			mes "ミスティ！";
			mes "さっそく材料を集めてくるのだ！";
			next;
			mes "[ミスティ]";
			mes "うぅ……";
			mes "一人だと大変なのじゃ……";
			mes "　";
			mes "むむっ!?　なるほどなるほど？";
			mes "手伝ってくれる？";
			mes "それはありがたいのじゃ♪";
			next;
			menu "手伝うとは言ってません",-;
			menu "はぁ……しょうがないですね",-;
			emotion 40, "ミスティ#ac_Misty";
			emotion 14, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "さすが";
			mes "" + strcharinfo(0) + "";
			mes "なのだ！";
			mes "　";
			mes "今回は、完璧なのだ！";
			next;
			mes "[ミスティ]";
			mes "ワシもやる気が出てきたのじゃ♪";
			mes "「のるん」を作成する為の素材は";
			mes "　";
			mes "えーっと……";
			next;
			mes "[ミスティ]";
			mes "ホルンの羽……";
			mes "猿のこしかけ……";
			mes "腐った魚の尻尾……";
			mes "マンドラゴラの汁！";
			mes "　";
			mes "これらが必要なようじゃ！";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000ホルン^000000";
			mes "^FF0000・^000000^FF0000ヨーヨー^000000";
			mes "^FF0000・^000000^FF0000メガロドン^000000";
			mes "^FF0000・^000000^FF0000マンドラゴラ^000000";
			mes "なのだ！";
			next;
			mes "[ミスティ]";
			mes "ネコリン殿は物知りだのぅ。";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING09_mobinfo	{
				switch(getarg(0)){
				case 100870:
					mes "[ミスティ]";
					mes "大きなクワガタじゃな。";
					mes "　";
					mes "動きは、それほど早くないのじゃ。";
					mes "魔法の詠唱に反応して";
					mes "攻撃してくるのじゃ！";
					break;
				case 100872:
					mes "[ミスティ]";
					mes "おさるさんなのじゃ。";
					mes "こ奴は、少しずる賢いのじゃ。";
					mes "　";
					mes "仲間が攻撃されると、";
					mes "一斉に襲ってくるのじゃ。";
					mes "なるべく1匹の所を狙うといいのじゃ。";
					break;
				case 100874:
					mes "[ミスティ]";
					mes "魚の骨なのじゃ。";
					mes "　";
					mes "特に、何もせず彷徨っておるのじゃ。";
					mes "こ奴の攻撃はなかなか痛いが、";
					mes "聖なる攻撃や、";
					mes "回復魔法に弱いのじゃ！";
					break;
				case 100876:
					mes "[ミスティ]";
					mes "植物が凶暴化したモンスターじゃ！";
					mes "　";
					mes "困った事に、遠くから様子を見ていても";
					mes "ツタで攻撃してくのじゃ……";
					mes "しかし、こ奴から取得出来る茎は、";
					mes "様々な上級薬品の材料にもなるのじゃ！";
					break;
				}
				return;
			}
			function	AC_PORING09_warp;
			function	AC_PORING09	{
				set '@questid,0;
				//100870,世界征服ロボ③,0,1128,40,0,0,0,0
				//100872,世界征服ロボ③,0,1057,20,0,0,0,0
				//100874,世界征服ロボ③,0,1064,30,0,0,0,0
				//100876,世界征服ロボ③,0,1020,60,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000ホルン^000000","^FF0000ヨーヨー^000000","^FF0000メガロドン^000000","^FF0000マンドラゴラ^000000")){
					case 1:
						AC_PORING09_mobinfo 100870;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ホルン^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100870;
						break;
					case 2:
						AC_PORING09_mobinfo 100872;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ヨーヨー^000000」じゃな？";
						mes "　";
						mes "^FF000020匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100872;
						break;
					case 3:
						AC_PORING09_mobinfo 100874;
						next;
						mes "[ミスティ]";
						mes "「^FF0000メガロドン^000000」じゃな？";
						mes "　";
						mes "^FF000030匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100874;
						break;
					case 4:
						AC_PORING09_mobinfo 100876;
						next;
						mes "[ミスティ]";
						mes "「^FF0000マンドラゴラ^000000」じゃな？";
						mes "　";
						mes "^FF000060匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100876;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ネコリン]";
				mes "決定なのだ！";
				mes "　";
				switch(AC_QUEST_ST_6){
				case 100870: mes "「^FF0000ホルン^000000」が、"; break;
				case 100872: mes "「^FF0000ヨーヨー^000000」が、"; break;
				case 100874: mes "「^FF0000メガロドン^000000」が、"; break;
				case 100876: mes "「^FF0000マンドラゴラ^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのだ！";
				next;
				mes "[ミスティ]";
				mes "残りはワシが集めよう！";
				mes "戦って無理と判断したら、";
				mes "いつでも戻ってくるのじゃ！";
				mes "　";
				mes "そうじゃ、";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING09_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING09_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 10,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100870: warp "ac_prac_02.gat",108,33; break;
					case 100872: warp "ac_prac_03.gat",29,337; break;
					case 100874: warp "ac_spec_02.gat",124,59; break;
					case 100876: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100870: warp "mjolnir_09.gat",106,34; break;
					case 100872: warp "prt_fild03.gat",368,256; break;
					case 100874: warp "beach_dun3.gat",281,56; break;
					case 100876: warp "prt_fild02.gat",305,22; break;
					}
				}
				return;
			}
			AC_PORING09;
			end;
		case 100870:
		case 100872:
		case 100874:
		case 100876:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				emotion 2;
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「のるん」の材料は、";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100870: set '@select$,'@select$ + "「^FF0000ホルン^000000」について教えて";  break;
				case 100872: set '@select$,'@select$ + "「^FF0000ヨーヨー^000000」について教えて";  break;
				case 100874: set '@select$,'@select$ + "「^FF0000メガロドン^000000」について教えて"; break;
				case 100876: set '@select$,'@select$ + "「^FF0000マンドラゴラ^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING09_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は鮮度が命なのじゃ！";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING09_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING09;
					end;
				case 3:
					AC_PORING09_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12,"";
			mes "[ミスティ]";
			mes "おお！";
			mes "お帰りなのじゃ。";
			next;
			menu "素材を持ってきました",-;
			mes "[ミスティ]";
			mes "早くこっちによこすのじゃ！";
			next;
			menu "どうぞ",-;
			mes "[ミスティ]";
			mes "うんうん……これじゃ！";
			next;
			menu "ところで……",-;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おお！";
			mes "そうじゃった、そうじゃった。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100878;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight2(569,300, 645,10)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 300;
			getitem 645, 10;
			chgquest 100878, 100879;
			if(checkre()) {
				getexp 400,0;
				getexp 400,0;
				getexp 400,0;
				getexp 0,500;
				getexp 0,500;
				getexp 0,500;
			}
			else {
				getexp 4000,0;
				getexp 4000,0;
				getexp 4000,0;
				getexp 0,5000;
				getexp 0,5000;
				getexp 0,5000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 29, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "フッフッフッ。";
			mes "　";
			mes "今度こそ……！";
			mes "今度こそ！　今度こそ!!";
			mes "バフォリンが起動するのじゃ！";
			next;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "「のるん」を作るのだ！";
			mes "　";
			mes "‐ポリン団の二人は";
			mes "　魔法の秘薬を作るのに使っていた";
			mes "　大鍋をどこからか引っ張り出すと";
			mes "　材料をどばっと入れて火をつけた‐";
			next;
			emotion 78, "ミスティ#ac_Misty";
			mes "（コトコトコト……）";
			next;
			mes "（コトコトコトコト……）";
			next;
			mes "‐出来上がったらしき燃料「のるん」を";
			mes "　ミスティはロボット「バフォリン」に";
			mes "　投入した！‐";
			next;
			misceffect 305, "ミスティ#ac_Misty";
			mes "（コトコトコト……）";
			mes "　";
			mes "‐数分後……‐";
			mes "　";
			mes "（コポコポ……ドーン！）";
			next;
			mes "‐大きな駆動音と共に";
			mes "　白い煙を吐き出しつつ";
			mes "　動き始めたバフォリン‐";
			next;
			misceffect 17, "ミスティ#ac_Misty";
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "これで完成なのだ！";
			mes "バフォリンを起動するのだ！";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "バフォリン起動じゃ！";
			next;
			misceffect 79, "ミスティ#ac_Misty";
			mes "‐鎌を激しく振り動かし";
			mes "　大きな瞳に力が宿りだす。";
			mes "　次第に、車輪の回転が力を増し……‐";
			mes "　";
			mes "（バギャーン!!";
			mes "　";
			mes "　ゴゴゴッ……）";
			next;
			emotion 38, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "やったのじゃ！";
			mes "起動したのじゃ！";
			mes "今度こそ成功なのじゃ！";
			next;
			mes "[バフォリン]";
			mes "^0000FFキドウチュウ……";
			mes "シバラクオマチクダサイ……";
			mes "　";
			mes "……ッマ!!!!^000000";
			next;
			mes "[ネコリン]";
			mes "まずは、試し運転なのだ！";
			mes "周りを歩かせるのだ！";
			next;
			emotion 27, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ゆけ！　バフォリン!!";
			mes "突撃するのじゃー！";
			next;
			mes "[バフォリン]";
			mes "^0000FFピピピ……ガーガーガー……";
			mes "　";
			mes "テキヲ、セッテイシテクダサイ……^000000";
			next;
			mes "[ネコリン]";
			mes "敵の名前……";
			mes "そんなの決まっているのだ！";
			mes "狼なのだ！　狼しかないのだ！";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿落ち着くのじゃ！";
			next;
			mes "[バフォリン]";
			mes "^0000FFピピピ……ガーガーガー……";
			mes "　";
			mes "「狼」デスネ……";
			mes "セッテイシマシタ……^000000";
			next;
			mes "[バフォリン]";
			mes "^0000FFジドウツイビ……カイシ！";
			mes "　";
			mes "……ッマ!!!!^000000";
			next;
			emotion 23, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "こらぁー、どこにいくのじゃー！";
			mes "ワシの言う事を聞くのじゃ～!!";
			next;
			mes "（ウィーン……ウィーン……";
			mes "ガタガタガタガタ……）";
			mes "　";
			mes "‐大きな鎌を掲げ土煙を上げながら";
			mes "　バフォリンは何処かへと";
			mes "　駆けて行ってしまった‐";
			next;
			menu "何処かへ行ってしまいましたね",-;
			emotion 9,"";
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "全資金を投入したのに……";
			mes "どこかにいってしまったのじゃ……";
			next;
			emotion 1, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "結局何をするロボットだったのだ。";
			mes "機能がまったくわからないのだ。";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "今はそっとしておいて欲しいのじゃ。";
			next;
			mes "‐結局、あのロボは何だったのだろう？";
			mes "　周りに迷惑をかけなければ良いが";
			mes "　……‐";
			next;
			mes "‐それにしてもポリン団は、";
			mes "　計画性がまったく無いようだ……";
			mes "　";
			mes "　行き当たりばったりなところもあるし";
			mes "　悪の組織といいつつ、";
			mes "　ひどい悪さをしているわけでもない‐";
			next;
			mes "‐正直、あなたは彼らといることが";
			mes "　楽しくなってきていた‐";
			next;
			mes "[^FF0000第十話終了^000000]";
			mes "‐第十一話開始には、";
			mes "　^FF0000BaseLvを31以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 11,1;
			close2;
			chgquest 100879, 200995;
			set AC_QUEST_LV_6,10;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+8;
			end;
		}
		break;
	/////////   第十一話   /////////
	case 10:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<31){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十一話開始には、";
				mes "　^FF0000BaseLvを31以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ。";
			mes "元気にしておったか？";
			next;
			menu "こんにちは",-;
			emotion 18, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あの後「バフォリン」が見つかってな、";
			mes "　";
			mes "なんと「子デザートウルフ」を";
			mes "追い掛け回していたのじゃ！";
			next;
			emotion 18, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "狼が食堂に来なくなったのだ。";
			mes "おかげで食堂が平和なのだ！";
			next;
			emotion 1,"";
			mes "[ミスティ]";
			mes "うんうん。";
			mes "　";
			mes "所でな、";
			mes "先日姉上にいたずらしたじゃろ？";
			next;
			menu "あの時は大変でしたね……",-;
			mes "[ミスティ]";
			mes "あれ以来、姉上が不機嫌でな。";
			mes "何かと実験台にされるのじゃ！";
			next;
			menu "自業自得ですよ",-;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうなんじゃが……";
			mes "機嫌を直してほしいのじゃ。";
			next;
			mes "[ネコリン]";
			mes "いつ八つ当たりされるか、";
			mes "怖くて夜も眠れないのだ……";
			next;
			mes "[ミスティ]";
			mes "だからその……";
			mes "姉上のご機嫌取りを手伝ってくれぬか？";
			next;
			menu "具体的に何をするのですか？",-;
			emotion 1,"";
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "姉上にプレゼントをするのじゃ！";
			mes "　";
			mes "美味しい物を食べれば、";
			mes "姉上も機嫌がよくなるのじゃ！";
			next;
			menu "食べ物？",-;
			mes "[ミスティ]";
			mes "そうなのじゃ！";
			mes "　";
			mes "ワシは美味しい物を食べると";
			mes "機嫌がいいのじゃ！";
			mes "　";
			mes "だから「究極の料理」を作るのじゃ！";
			next;
			mes "[ミスティ]";
			mes "そこでじゃ!!";
			mes "食材集めを手伝ってほしいのじゃ！";
			mes "　";
			mes "もちろん、礼もするのじゃ。";
			next;
			menu "何を集めれば？",-;
			mes "[ミスティ]";
			mes "スモーキーの肉……";
			mes "猿の手のひら……";
			mes "キャラメルの皮……";
			mes "海賊の骨!!";
			mes "これらが必要なのじゃ！";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "食材に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000スモーキー^000000";
			mes "^FF0000・^000000^FF0000ヨーヨー^000000";
			mes "^FF0000・^000000^FF0000キャラメル^000000";
			mes "^FF0000・^000000^FF0000パイレーツスケル^000000";
			mes "なのだ！";
			next;
			mes "[ミスティ]";
			mes "これで「究極の料理」が作れるのじゃ！";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING10_mobinfo	{
				switch(getarg(0)){
				case 100880:
					mes "[ミスティ]";
					mes "たぬきじゃな。";
					mes "　";
					mes "とっても恥ずかしがり屋なので、";
					mes "たまに姿を隠してしまうのじゃ!!";
					mes "しかも、隠れて傷を回復するから";
					mes "注意するのじゃぞ！";
					break;
				case 100882:
					mes "[ミスティ]";
					mes "おさるさんなのじゃ。";
					mes "こ奴は、少しずる賢いのじゃ。";
					mes "　";
					mes "仲間が攻撃されると、";
					mes "一斉に襲ってくるのじゃ。";
					mes "なるべく1匹の所を狙うといいのじゃ。";
					break;
				case 100884:
					mes "[ミスティ]";
					mes "ハリネズミじゃな。";
					mes "　";
					mes "食べ物じゃないので注意するのじゃ！";
					mes "まぁ、誰も食べないと思うがのぅ。";
					mes "　";
					mes "見た目は小さいがタフな奴じゃぞ。";
					break;
				case 100886:
					mes "[ミスティ]";
					mes "海で死んだ海賊が、";
					mes "骨になってよみがえったのじゃ！";
					mes "　";
					mes "陸で死ぬ海賊もいないかのぅ……";
					mes "元々海賊じゃから、とても好戦的じゃ。";
					mes "聖なる攻撃と回復魔法に弱いのじゃ。";
					break;
				}
				return;
			}
			function	AC_PORING10_warp;
			function	AC_PORING10	{
				set '@questid,0;
				//100880,ミスティの憂鬱①,0,1056,80,0,0,0,0
				//100882,ミスティの憂鬱①,0,1057,40,0,0,0,0
				//100884,ミスティの憂鬱①,0,1103,30,0,0,0,0
				//100886,ミスティの憂鬱①,0,1071,40,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000スモーキー^000000","^FF0000ヨーヨー^000000","^FF0000キャラメル^000000","^FF0000パイレーツスケル^000000")){
					case 1:
						AC_PORING10_mobinfo 100880;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スモーキー^000000」じゃな？";
						mes "　";
						mes "^FF000080匹^000000分ほど倒してくれば、";
						mes "食材は集まりそうじゃな♪";
						set '@questid, 100880;
						break;
					case 2:
						AC_PORING10_mobinfo 100882;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ヨーヨー^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "食材は集まりそうじゃな♪";
						set '@questid, 100882;
						break;
					case 3:
						AC_PORING10_mobinfo 100884;
						next;
						mes "[ミスティ]";
						mes "「^FF0000キャラメル^000000」じゃな？";
						mes "　";
						mes "^FF000030匹^000000分ほど倒してくれば、";
						mes "食材は集まりそうじゃな♪";
						set '@questid, 100884;
						break;
					case 4:
						AC_PORING10_mobinfo 100886;
						next;
						mes "[ミスティ]";
						mes "「^FF0000パイレーツスケル^000000」じゃな？";
						mes "　";
						mes "^FF000040匹^000000分ほど倒してくれば、";
						mes "食材は集まりそうじゃな♪";
						set '@questid, 100886;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ミスティ]";
				mes "決定なのじゃ！";
				switch(AC_QUEST_ST_6){
				case 100880: mes "「^FF0000スモーキー^000000」が、"; break;
				case 100882: mes "「^FF0000ヨーヨー^000000」が、"; break;
				case 100884: mes "「^FF0000キャラメル^000000」が、"; break;
				case 100886: mes "「^FF0000パイレーツスケル^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのじゃ！";
				mes "　";
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING10_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING10_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 11,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100880:
					case 100882:
					case 100884: warp "ac_prac_03.gat",29,337; break;
					case 100886: warp "ac_spec_02.gat",124,59; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100880: warp "pay_fild09.gat",19,91; break;
					case 100882: warp "prt_fild03.gat",368,256; break;
					case 100884: warp "lhz_fild01.gat",296,376; break;
					case 100886: warp "treasure01.gat",69,24; break;
					}
				}
				return;
			}
			AC_PORING10;
			end;
		case 100880:
		case 100882:
		case 100884:
		case 100886:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「究極の料理」の食材は、";
				mes "順調に集まっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100880: set '@select$,'@select$ + "「^FF0000スモーキー^000000」について教えて";  break;
				case 100882: set '@select$,'@select$ + "「^FF0000ヨーヨー^000000」について教えて";  break;
				case 100884: set '@select$,'@select$ + "「^FF0000キャラメル^000000」について教えて"; break;
				case 100886: set '@select$,'@select$ + "「^FF0000パイレーツスケル^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING10_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、食材は鮮度が命なのじゃ。";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING10_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING10;
					end;
				case 3:
					AC_PORING10_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12,"";
			mes "[ネコリン]";
			mes "帰ってきたのだ！";
			mes "お帰りなのだ。";
			next;
			menu "食材を集めてきました",-;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "これじゃこれっ！　助かるのじゃ!!";
			mes "これで「究極の料理」が作れるのじゃ！";
			mes "　";
			mes "さっそく作るのじゃ!!";
			next;
			mes "‐ミスティは、素早く材料を手に取り";
			mes "　それぞれに最適な下処理をしていく。";
			mes "　";
			mes "　まずは最初に、";
			mes "　スモーキーの肉に下味をつけた‐";
			next;
			mes "‐猿の手のひらは、";
			mes "　少量しか取れない部位が";
			mes "　非常に珍味となっている。";
			mes "　しかし、一度手順を間違えば";
			mes "　その部位は、素材としての輝きを";
			mes "　瞬く間に失ってしまうのだ。";
			mes "　それをじっくりと湯戻しする‐";
			next;
			mes "‐キャラメルの皮は、";
			mes "　動物性食材ではあるものの";
			mes "　軽く火で炙ると香ばしい香りと";
			mes "　サラダの様な食感を持つ、";
			mes "　不思議な食材になる‐";
			next;
			misceffect 50, "ミスティ#ac_Misty";
			mes "‐適度に熱された鍋に";
			mes "　今回の味の決め手といえる";
			mes "　猿の手のひらで香りを出す。";
			mes "　十分な香りを引き出した所で";
			mes "　メインのスモーキーの肉と絡め";
			mes "　一気に強火にする!!‐";
			next;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "炎は友達！　炎は友達！";
			next;
			mes "‐仕上げに、強火の中に";
			mes "　予め投げ入れておいた骨を";
			mes "　炎の中から取り出し";
			mes "　それを、タヌキの葉で被せる。";
			mes "　水分を多く含むタヌキの葉は";
			mes "　熱された海賊の骨を急激に冷やし、";
			mes "　大量の水蒸気を発生させる‐";
			next;
			mes "［ミスティ］";
			mes "よしっ！";
			mes "この蒸気の中に、お肉を入れれば……";
			next;
			misceffect 44, "ミスティ#ac_Misty";
			mes "‐香ばしく焼きあがったお肉と";
			mes "　爽やかな香りの蒸気立ち込める器";
			mes "　二つが合わさった時、";
			mes "　食欲をそそる甘酸っぱい香りが";
			mes "　辺りに立ち込めた‐";
			next;
			mes "［ミスティ］";
			mes "最後に、キャラメルのサラダを……";
			mes "端っこに添えてっと……";
			next;
			mes "[ミスティ]";
			mes "ついに「究極の料理」が出来たのじゃ！";
			mes "「海賊風・高原の恵みキャラメル添え」";
			mes "完成なのじゃ！";
			mes "　";
			mes "ネコリン殿、";
			mes "味見をしてほしいのじゃ!!";
			next;
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "わかったのだ。";
			next;
			mes "［ネコリン］";
			mes "……!!";
			mes "うまいのだ！";
			mes "これぞ究極の味なのだ！";
			mes "　";
			mes "‐ネコリンは鈍器で叩かれたかのように";
			mes "　衝撃に打ち震えている！‐";
			next;
			menu "私にも味見をさせて下さい",-;
			mes "[ネコリン]";
			mes "どうぞなのだ。";
			mes "　";
			mes "‐" + strcharinfo(0) + "は";
			mes "　料理を口にした‐";
			next;
			menu "美味しい!!",-;
			emotion 0,"";
			mes "[ミスティ]";
			mes "これで姉上の機嫌もよくなるのだ！";
			mes "　";
			mes "……あっ！　姉上!!";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "ミスティ……";
			mes "今日も実験……";
			mes "付き合いなさい！";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ちょ、ちょっと待ってほしいのじゃ！";
			mes "　";
			mes "姉上の為にこれを作ったのじゃ……";
			mes "食べてほしいのじゃ！";
			next;
			cutin "job_black_hucke01.bmp", 2;
			mes "[ヒュッケ]";
			mes "良い匂い……";
			mes "……!!";
			mes "私の……料理より……";
			mes "　";
			mes "美味い!!!!";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "よかったのじゃ。";
			mes "これで姉上も機嫌がよくなるのじゃ♪";
			next;
			cutin "job_black_hucke03.bmp", 2;
			mes "[ヒュッケ]";
			mes "私より……料理上手い……";
			mes "……弟なのに……";
			mes "ミスティ……私は、怒った！";
			next;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "な、な、なんでなのじゃ！";
			mes "姉上の為に作ったのに～。";
			mes "　";
			mes "助けてくれなのじゃ～～……";
			next;
			mes "[ヒュッケ]";
			mes "ミスティ……待つのです！";
			next;
			cutin "job_black_hucke03.bmp", 255;
			menu "…………",-;
			emotion 54, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "…………";
			mes "乙女心は、わからないのだ……";
			next;
			menu "あの……報酬は……？",-;
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "君の単位を増やしておいたのだ。";
			mes "ついでに、これもプレゼントなのだ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6,100888;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight2(569,300, 602,10)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 300;
			getitem 602, 10;
			chgquest 100888, 100889;
			if(checkre()) {
				getexp 800,0;
				getexp 800,0;
				getexp 0,1400;
				getexp 0,1400;
			}
			else {
				getexp 8000,0;
				getexp 8000,0;
				getexp 0,14000;
				getexp 0,14000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 12, "ネコリン#ac_Necorin";
			emotion 12,"";
			mes "[ネコリン]";
			mes "また何かあったら宜しく頼むのだ。";
			mes "　";
			mes "それではまた会おうなのだ。";
			next;
			mes "[^FF0000第十一話終了^000000]";
			mes "‐第十二話開始には、";
			mes "　^FF0000BaseLvを34以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 12,1;
			close2;
			chgquest 100889, 201000;
			set AC_QUEST_LV_6,11;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+9;
			end;
		}
		break;
	/////////   第十二話   /////////
	case 11:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<34){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十二話開始には、";
				mes "　^FF0000BaseLvを34以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ。";
			mes "元気にしておったか？";
			next;
			menu "こんにちは",-;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あの後、";
			mes "またしても姉上に捕まってのぅ……";
			mes "　";
			mes "いつもの三倍 酷い目にあったのじゃ。";
			mes "今度ばかりは死ぬかと……";
			next;
			menu "……大変ですね",-;
			mes "[ネコリン]";
			mes "ミスティは三日間も寝込んでいたのだ。";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "今度こそ姉上の機嫌をとるのじゃ！";
			next;
			menu "今度はどうやって？",-;
			mes "[ミスティ]";
			mes "先日、姉上から逃げ回った時、";
			mes "「姉上の服」が、";
			mes "ボロボロになったのじゃ……";
			next;
			emotion 3, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "だから、新しい「姉上の服」を";
			mes "プレゼントするのじゃ！";
			mes "　";
			mes "今度こそ、";
			mes "機嫌が良くなる事、間違いないのじゃ！";
			next;
			emotion 4, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "いよいよ私の身も危ないのだ……";
			next;
			mes "[ミスティ]";
			mes "だからその……今回も";
			mes "姉上のご機嫌取りを手伝ってくれぬか？";
			mes "　";
			mes "もちろん、礼もするのじゃ！";
			next;
			menu "今回は何を集めるのですか？",-;
			mes "[ミスティ]";
			mes "サベージの牙……";
			mes "サンドマンの砂……";
			mes "海水に浸かった布……";
			mes "ジオグラファーの絞り汁!!";
			mes "これらが必要なのじゃ！";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "素材に関係するモンスターは…";
			mes "^FF0000・^000000^FF0000サベージ^000000";
			mes "^FF0000・^000000^FF0000サンドマン^000000";
			mes "^FF0000・^000000^FF0000パイレーツスケル^000000";
			mes "^FF0000・^000000^FF0000ジオグラファー^000000";
			mes "なのだ！";
			next;
			mes "[ミスティ]";
			mes "これで「姉上の服」が作れるのじゃ！";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！　どれにするか選ぶのじゃ！";
			function	AC_PORING11_mobinfo	{
				switch(getarg(0)){
				case 100890:
					mes "[ミスティ]";
					mes "鼻息の荒い、イノシシなのじゃ……";
					mes "普段は大人しいが、";
					mes "たまに突進してくるので注意じゃ。";
					mes "　";
					mes "見た目通りタフで、";
					mes "攻撃力も高いので注意じゃ。";
					break;
				case 100892:
					mes "[ミスティ]";
					mes "砂のお化けみたいなモンスターじゃ。";
					mes "地上に出てる時もあるが、";
					mes "地中に隠れたりもするぞ";
					mes "　";
					mes "地面の下から奇襲してくるので";
					mes "注意するのじゃ。";
					break;
				case 100894:
					mes "[ミスティ]";
					mes "海で死んだ海賊が、";
					mes "骨になってよみがえったのじゃ！";
					mes "　";
					mes "陸で死ぬ海賊もいないかのぅ……";
					mes "元々海賊じゃから、とても好戦的じゃ。";
					mes "聖なる攻撃と回復魔法に弱いのじゃ。";
					break;
				case 100896:
					mes "[ミスティ]";
					mes "小さな花のモンスターじゃ。";
					mes "移動は出来ぬが、とても硬いのじゃ。";
					mes "　";
					mes "遠距離なら攻撃してこぬが、";
					mes "仲間同士で回復しあうぞ。";
					break;
				}
				return;
			}
			function	AC_PORING11_warp;
			function	AC_PORING11	{
				set '@questid,0;
				//100890,ミスティの憂鬱②,0,1166,25,0,0,0,0
				//100892,ミスティの憂鬱②,0,1165,10,0,0,0,0
				//100894,ミスティの憂鬱②,0,1071,61,0,0,0,0
				//100896,ミスティの憂鬱②,0,1368,5,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000サベージ^000000","^FF0000サンドマン^000000","^FF0000パイレーツスケル^000000","^FF0000ジオグラファー^000000")){
					case 1:
						AC_PORING11_mobinfo 100890;
						next;
						mes "[ミスティ]";
						mes "「^FF0000サベージ^000000」じゃな？";
						mes "　";
						mes "^FF000025匹^000000分ほど倒してくれば、";
						mes "素材は集まりそうじゃな♪";
						set '@questid, 100890;
						break;
					case 2:
						AC_PORING11_mobinfo 100892;
						next;
						mes "[ミスティ]";
						mes "「^FF0000サンドマン^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "素材は集まりそうじゃな♪";
						set '@questid, 100892;
						break;
					case 3:
						AC_PORING11_mobinfo 100894;
						next;
						mes "[ミスティ]";
						mes "「^FF0000パイレーツスケル^000000」じゃな？";
						mes "　";
						mes "^FF000060匹^000000分ほど倒してくれば、";
						mes "素材は集まりそうじゃな♪";
						set '@questid, 100894;
						break;
					case 4:
						AC_PORING11_mobinfo 100896;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ジオグラファー^000000」じゃな？";
						mes "　";
						mes "^FF00005匹^000000分ほど倒してくれば、";
						mes "素材は集まりそうじゃな♪";
						set '@questid, 100896;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ミスティ]";
				mes "決定なのじゃ！";
				switch(AC_QUEST_ST_6){
				case 100890: mes "「^FF0000サベージ^000000」が、"; break;
				case 100892: mes "「^FF0000サンドマン^000000」が、"; break;
				case 100894: mes "「^FF0000パイレーツスケル^000000」が、"; break;
				case 100896: mes "「^FF0000ジオグラファー^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのじゃ！";
				mes "　";
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING11_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING11_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 12,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100890: warp "ac_prac_03.gat",29,337; break;
					case 100892: warp "ac_spec_03.gat",98,78; break;
					case 100894: warp "ac_spec_02.gat",124,59; break;
					case 100896: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100890: warp "prt_fild10.gat",82,104; break;
					case 100892: warp "moc_fild16.gat",124,377; break;
					case 100894: warp "treasure01.gat",69,24; break;
					case 100896: warp "ein_fild04.gat",184,31; break;
					}
				}
				return;
			}
			AC_PORING11;
			end;
		case 100890:
		case 100892:
		case 100894:
		case 100896:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「姉上の服」の素材は、";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100890: set '@select$,'@select$ + "「^FF0000サベージ^000000」について教えて";  break;
				case 100892: set '@select$,'@select$ + "「^FF0000サンドマン^000000」について教えて";  break;
				case 100894: set '@select$,'@select$ + "「^FF0000パイレーツスケル^000000」について教えて"; break;
				case 100896: set '@select$,'@select$ + "「^FF0000ジオグラファー^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING11_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、素材が新鮮じゃないと";
					mes "キレイに染色できないのじゃ。";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING11_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING11;
					end;
				case 3:
					AC_PORING11_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			mes "[ネコリン]";
			mes "帰ってきたのだ！";
			mes "お帰りなのだ。";
			next;
			menu "素材を集めてきました",-;
			emotion 12,"";
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "これじゃこれっ！　助かるのじゃ!!";
			mes "これで「姉上の服」が作れるのじゃ！";
			mes "　";
			mes "さっそく作るのじゃ!!";
			next;
			mes "［ネコリン］";
			mes "料理の腕にはびっくりしたのだ。";
			mes "でも、裁縫は大丈夫なのだ？";
			next;
			mes "［ミスティ］";
			mes "フッフッフッ……";
			mes "　";
			mes "昔、よく姉上に作らされたのじゃ！";
			mes "だから、裁縫は得意なのじゃ！";
			next;
			mes "‐ミスティはネコリンに、";
			mes "　自信に満ち溢れた";
			mes "　表情で話しかけながら、";
			mes "　料理のとき同様、手早く集めてきた";
			mes "　素材の準備を始めた‐";
			next;
			mes "［ミスティ］";
			mes "このパイレーツスケルの生地は";
			mes "潮風に長い航海で耐えれるよう、";
			mes "丈夫に作ってあってじゃな……";
			next;
			misceffect 21, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "サンドマンの砂を半分利用して";
			mes "まずは、生地の汚れを洗うのじゃ。";
			mes "　";
			mes "（ごしごし、ごしごし……）";
			mes "　";
			mes "そして、次にジオグラファーの絞り汁！";
			next;
			mes "［ミスティ］";
			mes "ジオグラファーの絞り汁は、";
			mes "生地に特殊なコーティングを";
			mes "施してくれるのと同時に染色も";
			mes "行ってくれるのじゃ!!";
			mes "　";
			mes "（じゃぶ、じゃぶ……）";
			next;
			misceffect 39, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "よしっ！";
			mes "いい色合いじゃ!!";
			mes "特殊コーティングには、";
			mes "傷の治りを早くする効果があるのじゃ。";
			mes "　";
			mes "あっ、忘れておったのじゃ……";
			next;
			mes "［ミスティ］";
			mes "サベージの牙を……";
			mes "……じゃな……";
			mes "硬……い……";
			mes "…………のじゃぁ!!";
			mes "　";
			mes "切れたのじゃ！";
			next;
			mes "［ミスティ］";
			mes "この輪切りにした牙は";
			mes "姉上の腰周りについておる";
			mes "アクセサリーなのじゃ！";
			mes "決して食べ物ではないのじゃ!!";
			next;
			misceffect 43, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "次は、縫い合わせの作業じゃ！";
			mes "　";
			mes "‐そう叫ぶと";
			mes "　どこからともなく取り出した";
			mes "　裁縫道具を持ちかまえた‐";
			next;
			emotion 52, "ミスティ#ac_Misty";
			emotion 55, "ネコリン#ac_Necorin";
			mes "‐ミスティの両腕が";
			mes "　ひゅばばばばっと";
			mes "　舞い踊る‐";
			next;
			mes "［ネコリン］";
			mes "なんか、凄いのだ……";
			mes "　";
			mes "おっ！";
			mes "おおお！";
			mes "服が出来上がってきたのだ！";
			next;
			mes "［ミスティ］";
			mes "仕上げで、残りの砂を使って";
			mes "ダメージ加工を施して……";
			mes "　";
			mes "出来たのじゃ!!";
			next;
			mes "[ミスティ]";
			mes "ついに……";
			mes "「姉上の服」が完成したのじゃ!!";
			mes "　";
			mes "「ラブリーアサシンスーツ」";
			mes "完成なのじゃ！";
			next;
			mes "[ネコリン]";
			mes "ミスティ！";
			mes "早速着てみるのだ!!";
			next;
			mes "[ミスティ]";
			mes "わかったのじゃ！";
			mes "　";
			mes "よいしょっと……";
			mes "　";
			mes "サイズは、ばっちりなのじゃ！";
			next;
			menu "女の子みたい……",-;
			emotion 55,"";
			emotion 0, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "何を言うておるか、";
			mes "ワシは男……あっ！　姉上!!";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "……ミスティ。";
			mes "何……その……服装……";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "姉上の為に作った服なのじゃ!!";
			mes "　";
			mes "是非着てほしいのじゃ……";
			mes "きっと似合うのじゃ!!!!";
			next;
			cutin "job_black_hucke03.bmp", 2;
			emotion 20,"";
			mes "[ヒュッケ]";
			mes "私の……新しい服……";
			mes "…………!!";
			mes "少し……小さい？";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おかしいのじゃ！";
			mes "さっきワシが着れたのじゃ！";
			mes "　";
			mes "姉上とは双子だから、";
			mes "着れないはず無いのじゃがなぁ……";
			next;
			cutin "job_black_hucke01.bmp", 2;
			mes "[ヒュッケ]";
			mes "……";
			mes "………殺す！";
			next;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "な、な、なんでなのじゃ！";
			mes "ワシは何も悪い事してないのじゃ！";
			mes "　";
			mes "助けてくれなのじゃ～～……";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "ミスティ……待つのです！";
			next;
			cutin "job_black_hucke02.bmp", 255;
			menu "…………",-;
			mes "[ネコリン]";
			mes "…………";
			mes "何で怒ったのだ？";
			next;
			menu "あの……報酬は？",-;
			emotion 20,"";
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "君の単位を増やしておいたのだ。";
			mes "ついでに、これもプレゼントなのだ！";
			next;
			menu "ありがとうございます",-; 
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100898;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight(569,300)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 300;
			chgquest 100898, 100899;
			if(checkre()) {
				getexp 1200,0;
				getexp 1200,0;
				getexp 0,1900;
				getexp 0,1900;
			}
			else {
				getexp 12000,0;
				getexp 12000,0;
				getexp 0,19000;
				getexp 0,19000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 12, "ネコリン#ac_Necorin";
			emotion 12,"";
			mes "[ネコリン]";
			mes "また何かあったら宜しく頼むのだ。";
			mes "　";
			mes "それではまた会おうなのだ。";
			next;
			mes "[^FF0000第十二話終了^000000]";
			mes "‐第十三話開始には、";
			mes "　^FF0000BaseLvを37以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 13,1;
			close2;
			chgquest 100899, 201005;
			set AC_QUEST_LV_6,12;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+9;
			end;
		}
		break;
	/////////   第十三話   /////////
	case 12:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<37){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十三話開始には、";
				mes "　^FF0000BaseLvを37以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 6, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "もう我慢できないのじゃ！";
			mes "反撃にでるのじゃ!!";
			next;
			menu "突然どうしたのですか？",-;
			emotion 4,"";
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "このままでは身がもたないのじゃ。";
			mes "姉上から身を守る武器を作るのじゃ！";
			next;
			emotion 54, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "最初からそうすればよかったのだ。";
			next;
			menu "……物騒な話ですね",-;
			emotion 4,"";
			mes "[ミスティ]";
			mes "大丈夫なのじゃ。";
			mes "　";
			mes "ちょっと気持ちよく";
			mes "寝てもらうだけなのじゃ!!";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "「麻酔銃」をつくるのだ！";
			next;
			menu "……何が必要なのですか？",-;
			mes "[ミスティ]";
			mes "話がはやいのじゃ！";
			mes "もちろん、礼もするのじゃ!!";
			mes "　";
			mes "「麻酔銃」に必要な材料は……";
			next;
			mes "[ミスティ]";
			mes "マーティンの牙……";
			mes "モルデンの銃……";
			mes "ツルハシ……";
			mes "ジオグラファーの茎!!";
			mes "これらが必要なのじゃ！";
			next;
			emotion 5, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "材料に関係するモンスターは……";
			mes "^FF0000・^000000^FF0000マーティン^000000";
			mes "^FF0000・^000000^FF0000モルデン^000000";
			mes "^FF0000・^000000^FF0000スケルワーカー^000000";
			mes "^FF0000・^000000^FF0000ジオグラファー^000000";
			mes "なのだ！";
			next;
			mes "[ミスティ]";
			mes "これで「麻酔銃」が作れるのじゃ！";
			mes "　";
			mes "という訳で、君にはどれか一つ";
			mes "頼まれて欲しいのじゃが……";
			mes "　";
			mes "さぁ！どれにするか選ぶのじゃ！";
			function	AC_PORING12_mobinfo	{
				switch(getarg(0)){
				case 100900:
					mes "[ミスティ]";
					mes "モグラじゃな。";
					mes "　";
					mes "傷を負うと地面に潜って";
					mes "回復しだすので注意じゃ。";
					mes "たまに目潰しをしてくるので";
					mes "気を付けるのじゃ。";
					break;
				case 100902:
					mes "[ミスティ]";
					mes "銃を持ったモグラじゃな。";
					mes "地面にもぐってる事が多いのじゃ。";
					mes "　";
					mes "こ奴からは攻撃してこないが、";
					mes "仲間が攻撃されると";
					mes "近くの仲間が一斉に襲ってくるのじゃ。";
					break;
				case 100904:
					mes "[ミスティ]";
					mes "死んだ炭鉱夫が、";
					mes "骨になってよみがえったのじゃ。";
					mes "　";
					mes "持ってるツルハシでの攻撃は、";
					mes "とても強いので注意じゃ。";
					mes "聖なる攻撃や、回復魔法に弱いのじゃ。";
					break;
				case 100906:
					mes "[ミスティ]";
					mes "小さな花のモンスターじゃ。";
					mes "移動は出来ぬが、とても硬いのじゃ。";
					mes "　";
					mes "遠距離なら攻撃してこぬが、";
					mes "仲間同士で回復しあうぞ。";
					break;
				}
				return;
			}
			function	AC_PORING12_warp;
			function	AC_PORING12	{
				set '@questid,0;
				//100900,ミスティの憂鬱③,0,1145,50,0,0,0,0
				//100902,ミスティの憂鬱③,0,1628,30,0,0,0,0
				//100904,ミスティの憂鬱③,0,1169,25,0,0,0,0
				//100906,ミスティの憂鬱③,0,1368,10,0,0,0,0
				while(1){
					next;
					switch(select("^FF0000マーティン^000000","^FF0000モルデン^000000","^FF0000スケルワーカー^000000","^FF0000ジオグラファー^000000")){
					case 1:
						AC_PORING12_mobinfo 100900;
						next;
						mes "[ミスティ]";
						mes "「^FF0000マーティン^000000」じゃな？";
						mes "　";
						mes "^FF000050匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100900;
						break;
					case 2:
						AC_PORING12_mobinfo 100902;
						next;
						mes "[ミスティ]";
						mes "「^FF0000モルデン^000000」じゃな？";
						mes "　";
						mes "^FF000030匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100902;
						break;
					case 3:
						AC_PORING12_mobinfo 100904;
						next;
						mes "[ミスティ]";
						mes "「^FF0000スケルワーカー^000000」じゃな？";
						mes "　";
						mes "^FF000025匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100904;
						break;
					case 4:
						AC_PORING12_mobinfo 100906;
						next;
						mes "[ミスティ]";
						mes "「^FF0000ジオグラファー^000000」じゃな？";
						mes "　";
						mes "^FF000010匹^000000分ほど倒してくれば、";
						mes "材料は集まりそうじゃな♪";
						set '@questid, 100906;
						break;
					}
					mes "　";
					mes "こ奴でよいのか？";
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				mes "[ミスティ]";
				mes "決定なのじゃ！";
				switch(AC_QUEST_ST_6){
				case 100900: mes "「^FF0000マーティン^000000」が、"; break;
				case 100902: mes "「^FF0000モルデン^000000」が、"; break;
				case 100904: mes "「^FF0000スケルワーカー^000000」が、"; break;
				case 100906: mes "「^FF0000ジオグラファー^000000」が、"; break;
				}
				mes "沢山生息する場所を知っているのじゃ！";
				mes "　";
				mes "よかったら";
				mes "魔法で現地まで送るが、どうじゃ？";
				next;
				AC_PORING12_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING12_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 13,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100900:
					case 100902:
					case 100904: warp "ac_prac_04.gat",261,261; break;
					case 100906: warp "ac_spec_01.gat",283,34; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100900: warp "mjo_dun02.gat",125,60; break;
					case 100902: warp "hu_fild06.gat",34,119; break;
					case 100904: warp "mjo_dun02.gat",125,60; break;
					case 100906: warp "ein_fild04.gat",184,31; break;
					}
				}
				return;
			}
			AC_PORING12;
			end;
		case 100900:
		case 100902:
		case 100904:
		case 100906:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "「麻酔銃」の材料は";
				mes "順調にあつまっておるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100900: set '@select$,'@select$ + "「^FF0000マーティン^000000」について教えて";  break;
				case 100902: set '@select$,'@select$ + "「^FF0000モルデン^000000」について教えて";  break;
				case 100904: set '@select$,'@select$ + "「^FF0000スケルワーカー^000000」について教えて"; break;
				case 100906: set '@select$,'@select$ + "「^FF0000ジオグラファー^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING12_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ミスティ]";
					mes "ちなみに、材料は時間が経つと";
					mes "劣化してしまうのじゃ……";
					mes "　";
					mes "違うモンスターにすると、";
					mes "今まで集めてもらった物が、";
					mes "無駄になってしまうのじゃが良いか？";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING12_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING12;
					end;
				case 3:
					AC_PORING12_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			mes "[ネコリン]";
			mes "帰ってきたのだ！";
			mes "お帰りなのだ。";
			next;
			menu "材料を集めてきました",-;
			emotion 12,"";
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ミスティ]";
			mes "これじゃこれっ！　助かるのじゃ!!";
			mes "これで「麻酔銃」が作れるのじゃ！";
			mes "　";
			mes "さっそく作るのじゃ!!";
			next;
			mes "［ネコリン］";
			mes "料理・裁縫・工作……";
			mes "　";
			mes "ミスティの意外な才能に";
			mes "驚かされ続けているのだ。";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "今回は、もともと";
			mes "モルデンが持っておる";
			mes "銃を加工するのじゃ。";
			mes "さほど難しくはないのじゃ！";
			next;
			misceffect 2, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "まずは、ツルハシをじゃな……";
			mes "　";
			mes "……ふぬっ……ふぬぬっ!!";
			mes "　";
			mes "‐スポンッ！";
			mes "　という良い音がした‐";
			next;
			misceffect 101, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "ふぅ……";
			mes "取れたのじゃ！";
			mes "　";
			mes "この取っ手をグリップに加工して、";
			mes "手に馴染むように削りだすのじゃ！";
			next;
			emotion 4, "ネコリン#ac_Necorin";
			mes "［ネコリン］";
			mes "デザインばかり変わっていくのだ。";
			mes "本当に麻酔銃なのだ？";
			mes "心配なのだ……";
			next;
			misceffect 101, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "大丈夫！　心配ないのだ！";
			mes "　";
			mes "マーティンの牙を細く丁寧に";
			mes "削りだして……";
			mes "　";
			mes "うん！　出来たのじゃ!!";
			next;
			mes "［ミスティ］";
			mes "後は、ジオグラファーの";
			mes "茎の加工をするだけなのじゃ。";
			mes "　";
			mes "これを一度焼いて水に溶かしたものが";
			mes "強力な麻酔銃の弾になるのじゃ！";
			next;
			emotion 33, "ネコリン#ac_Necorin";
			mes "［ネコリン］";
			mes "こないだの服に使ったものは";
			mes "この植物の沈静効果を使った";
			mes "使用例の一つなのだ！";
			next;
			emotion 9, "ミスティ#ac_Misty";
			mes "［ミスティ］";
			mes "その通りなのじゃ！";
			mes "　";
			mes "慎重に、炙って……";
			mes "は、鼻がムズムズするのじゃ。";
			next;
			mes "［ネコリン］";
			mes "危ないのだ!!";
			mes "今くしゃみをしたら、";
			mes "みんな寝てしまうのだ!!";
			next;
			misceffect 305, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "が、我慢できるのじゃ！";
			mes "　";
			mes "最後に、これを水に溶かして";
			mes "溶かした物と弾を";
			mes "組み合わせたら……";
			next;
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ふぅ……";
			mes "「麻酔銃」が出来たのじゃ……";
			mes "「名銃・グッスリーナＺ」";
			mes "完成なのじゃ！";
			next;
			mes "[ネコリン]";
			mes "これで安全が保障されたのだ！";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "姉上！";
			mes "いつでもかかってくるのじゃ!!";
			mes "　";
			mes "……あっ！　姉上!!";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "……ミスティ……";
			mes "絶対……逃がさない!!";
			next;
			cutin "job_black_hucke02.bmp", 255;
			mes "[ミスティ]";
			mes "姉上!!";
			mes "年貢の納め時なのじゃ！";
			mes "これでもくらうのじゃ！";
			next;
			misceffect 107, "ミスティ#ac_Misty";
			mes "‐ドカーン……‐";
			next;
			emotion 23, "ミスティ#ac_Misty";
			emotion 9, "ネコリン#ac_Necorin";
			emotion 9,"";
			mes "[ミスティ]";
			mes "こここ……壊れたのじゃ！";
			next;
			cutin "job_black_hucke03.bmp", 2;
			mes "[ヒュッケ]";
			mes "ミスティ……また……悪巧み";
			mes "……私は、怒った！";
			mes "これから……お仕置30時間！";
			next;
			cutin "job_black_hucke01.bmp", 2;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "完成したはずじゃのに!!";
			mes "なぜ壊れたんじゃ～……";
			mes "　";
			mes "助けてくれなのじゃ～～……";
			next;
			cutin "job_black_hucke02.bmp", 2;
			mes "[ヒュッケ]";
			mes "ミスティ……待つのです！";
			next;
			cutin "job_black_hucke02.bmp", 255;
			menu "…………",-;
			next;
			cutin "job_black_hucke02.bmp", 255;
			menu "…………",-;
			emotion 9,"";
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "…………";
			mes "あ、ネジが1個落ちているのだ。";
			next;
			menu "あの……報酬は？",-;
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうだったのだ。";
			mes "　";
			mes "ん～　ポリ～ンっと！";
			mes "君の単位を増やしておいたのだ。";
			mes "ついでに、これもプレゼントなのだ！";
			next; 
			menu "ありがとうございます",-; 
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100908;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(!checkweight(569,300)){
				set AC_QUEST_ST_6,3;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "うむ。";
				mes "きちんと減らしてきたようなのだ。";
				next;
			}
			getitem 569, 300;
			chgquest 100908, 100909;
			if(checkre()) {
				getexp 2100,0;
				getexp 2100,0;
				getexp 0,2400;
				getexp 0,2400;
			}
			else {
				getexp 21000,0;
				getexp 21000,0;
				getexp 0,24000;
				getexp 0,24000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "また何かあったら宜しく頼むのだ。";
			mes "　";
			mes "それではまた会おうなのだ。";
			next;
			emotion 12,"";
			mes "‐あの姉弟、実は仲が良いのでは……";
			mes "　";
			mes "　はたして、ミスティは逃げ切る事が";
			mes "　出来るのだろうか？";
			mes "　";
			mes "　どうやらポリン団は、やる事が";
			mes "　全てが裏目に出るようだ‐";
			next;
			mes "[^FF0000第十三話終了^000000]";
			mes "‐第十四話開始には、";
			mes "　^FF0000BaseLvを40以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 14,1;
			close2;
			chgquest 100909, 201010;
			set AC_QUEST_LV_6,13;
			set AC_QUEST_ST_6,0;
			end;
		}
		break;
	/////////   第十四話   /////////
	case 13:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<40){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十四話開始には、";
				mes "　^FF0000BaseLvを40以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "久しぶりじゃのぅ";
			mes "元気にしておったか？";
			next;
			menu "こんにちは",-;
			emotion 16, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "あの後、結局姉上に捕まってな……";
			mes "酷い仕打ちを受けたのじゃ……";
			next;
			mes "[ミスティ]";
			mes "30時間も正座させられたのじゃ！";
			mes "30時間も……";
			mes "　";
			mes "しかも今回はそれだけに留まらず……";
			next;
			emotion 79, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "しびれた足を何度も何度も";
			mes "棒で突っつかれたのじゃ……";
			mes "　";
			mes "もう足がダメになるかと思ったのじゃ。";
			next;
			menu "……それは大変でしたね",-;
			emotion 4,"";
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "今回の件でわかったのだ。";
			mes "このままでは、";
			mes "ポリン団に先はないのだ！";
			next;
			menu "いきなりどうしたのですか？",-;
			emotion 0,"";
			mes "[ネコリン]";
			mes "数々の失敗には原因があったのだ。";
			mes "ポリン団には参謀……";
			mes "つまり、優秀な頭脳を持つ者が";
			mes "いなかったのだ……";
			next;
			mes "[ネコリン]";
			mes "このままでは駄目なのだ。";
			mes "ミスティの頭では限界なのだ！";
			next;
			mes "[ミスティ]";
			mes "そうなのじゃ！";
			mes "君のような知恵のある人に";
			mes "入団してほしいのじゃ！";
			next;
			menu "しかたないですね",-;
			emotion 0, "ネコリン#ac_Necorin";
			emotion 54, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "そうじゃよな……";
			mes "やっぱり入団してくれないのじゃ……";
			mes "　";
			mes "…………!?";
			mes "本当なのか!!";
			mes "嘘ではないのじゃな!?";
			next;
			emotion 10, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "やったのだ！";
			mes "ついに団員が増えたのだ！";
			next;
			emotion 38, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿～！";
			mes "諦めずに勧誘して良かったのぅ～。";
			next;
			emotion 14, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "とにかくよかったのだ。";
			mes "　";
			mes "では試験を始めるのだ!!";
			next;
			mes "[ミスティ]";
			mes "" + strcharinfo(0) + "";
			mes "試験頑張るのじゃぞ！";
			mes "君なら絶対入団出来るのじゃ！";
			next;
			menu "試験??",-;
			emotion 1,"";
			emotion 33, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "そうなのだ。";
			mes "入団するには試験が必要なのだ。";
			next;
			menu "さっき人が増えたって言ったのに",-;
			emotion 7,"";
			mes "[ネコリン]";
			mes "それはそれ、";
			mes "これはこれなのだ！";
			next;
			menu "どんな試験なのですか？",-;
			emotion 11, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "入団試験は、モンスターを倒すのだ！";
			mes "　";
			mes "「^FF0000一次試験^000000」、「^FF0000二次試験^000000」、";
			mes "「^FF0000最終試験^000000」と3回あるのだ！";
			mes "　";
			mes "まずは「^FF0000一次試験^000000」なのだ！";
			next;
			menu "試験の内容を教えてください",-;
			emotion 11, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "「^FF0000一次試験^000000」のモンスターなのだ！";
			mes "^FF0000・^000000^FF0000ヨーヨー^000000";
			mes "^FF0000・^000000^FF0000スケルワーカー^000000";
			mes "^FF0000・^000000^FF0000マスキプラー^000000";
			mes "^FF0000・^000000^FF0000スティング^000000";
			mes "のどれかを選ぶのだ！";
			next;
			mes "[ネコリン]";
			mes "途中でモンスターは変えられるのだ！";
			mes "　";
			mes "ただし、変えてしまうと、";
			mes "最初からやり直しなのだ！";
			next;
			menu "がんばります",-;
			mes "[ネコリン]";
			mes "さぁ！";
			mes "この中のどれか一つを選ぶのだ！";
			mes "　";
			mes "ミスティ！";
			mes "モンスターの説明をするのだ！";
			function	AC_PORING13_mobinfo	{
				switch(getarg(0)){
				case 100910:
					mes "[ミスティ]";
					mes "おさるさんなのじゃ。";
					mes "こ奴は、少しずる賢いのじゃ。";
					mes "　";
					mes "仲間が攻撃されると、";
					mes "一斉に襲ってくるのじゃ。";
					mes "なるべく1匹の所を狙うといいのじゃ。";
					break;
				case 100912:
					mes "[ミスティ]";
					mes "死んだ炭鉱夫が、";
					mes "骨になってよみがえったのじゃ。";
					mes "　";
					mes "持ってるツルハシでの攻撃は、";
					mes "とても強いので注意じゃ。";
					mes "聖なる攻撃や、回復魔法に弱いのじゃ。";
					break;
				case 100914:
					mes "[ミスティ]";
					mes "食人植物じゃな。";
					mes "こ奴の一撃はとても強いのじゃ。";
					mes "　";
					mes "近づくと石化や吸血をしてくるので、";
					mes "遠距離から攻撃するといいのじゃ。";
					break;
				case 100916:
					mes "[ミスティ]";
					mes "手袋のお化けみたいな奴なのじゃ。";
					mes "　";
					mes "蝶ネクタイをつけており、見た目に";
					mes "反してとってもおしゃれな奴なのじゃ。";
					mes "あやつのゲンコツはとても痛いのじゃ。";
					break;
				}
				return;
			}
			function	AC_PORING13_warp;
			function	AC_PORING13	{
				set '@questid,0;
				//100910,入団試験①,0,1057,80,0,0,0,0
				//100912,入団試験①,0,1169,50,0,0,0,0
				//100914,入団試験①,0,1780,10,0,0,0,0
				//100916,入団試験①,0,1207,5,0,0,0,0
				setarray '@mobname$, "^FF0000ヨーヨー^000000","^FF0000スケルワーカー^000000","^FF0000マスキプラー^000000","^FF0000スティング^000000";
				while(1){
					next;
					set '@sel, select(printarray('@mobname$));
					switch('@sel){
					case 1:
						AC_PORING13_mobinfo 100910;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ヨーヨー^000000」なのだ？";
						mes "　";
						mes "^FF000080匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100910;
						break;
					case 2:
						AC_PORING13_mobinfo 100912;
						next;
						mes "[ネコリン]";
						mes "「^FF0000スケルワーカー^000000」なのだ？";
						mes "　";
						mes "^FF000050匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100912;
						break;
					case 3:
						AC_PORING13_mobinfo 100914;
						next;
						mes "[ネコリン]";
						mes "「^FF0000マスキプラー^000000」なのだ？";
						mes "　";
						mes "^FF000010匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100914;
						break;
					case 4:
						AC_PORING13_mobinfo 100916;
						next;
						mes "[ネコリン]";
						mes "「^FF0000スティング^000000」なのだ？";
						mes "　";
						mes "^FF00005匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100916;
						break;
					}
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				emotion 21, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "" + '@mobname$['@sel-1] + "に";
				mes "決定なのだ！";
				mes "　";
				mes "気合をいれて倒してくるのだ!!";
				next;
				mes "[ミスティ]";
				mes "精一杯頑張るのじゃぞ♪";
				mes "　";
				mes "魔法で" + '@mobname$['@sel-1] + "の";
				mes "生息地まで送るが、どうじゃ？";
				next;
				AC_PORING13_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING13_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 14,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100910: warp "ac_prac_03.gat",29,337; break;
					case 100912: warp "ac_prac_04.gat",261,261; break;
					case 100914: warp "ac_spec_01.gat",283,34; break;
					case 100916: warp "ac_spec_03.gat",98,78; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100910: warp "prt_fild03.gat",368,256; break;
					case 100912: warp "mjo_dun02.gat",125,60; break;
					case 100914: warp "ra_fild01.gat",306,43; break;
					case 100916: warp "gl_sew03.gat",171,283; break;
					}
				}
				return;
			}
			AC_PORING13;
			end;
		case 100910:
		case 100912:
		case 100914:
		case 100916:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "順調に一次試験をこなせてるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100910: set '@select$,'@select$ + "「^FF0000ヨーヨー^000000」について教えて";  break;
				case 100912: set '@select$,'@select$ + "「^FF0000スケルワーカー^000000」について教えて";  break;
				case 100914: set '@select$,'@select$ + "「^FF0000マスキプラー^000000」について教えて"; break;
				case 100916: set '@select$,'@select$ + "「^FF0000スティング^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING13_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ネコリン]";
					mes "途中でモンスターは変えられるのだ！";
					mes "　";
					mes "ただし、変えてしまうと、";
					mes "最初からやり直しなのだ！";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING13_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING13;
					end;
				case 3:
					AC_PORING13_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			mes "[ミスティ]";
			mes "おかえりなのじゃ♪";
			next;
			menu "倒してきました",-;
			emotion 12,"";
			emotion 21, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "おめでとうなのだ！";
			mes "一次試験合格なのだ！";
			next;
			mes "[ミスティ]";
			mes "まだまだ余裕みたいじゃのぅ。";
			mes "大分腕をあげておるのじゃ！";
			next;
			menu "いえ、まだまだです",-;
			emotion 22, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "いや、そんな事はないぞ♪";
			mes "　";
			mes "しかし良い心がけじゃのぅ。";
			mes "次も頑張るのじゃぞ！";
			next;
			mes "[ネコリン]";
			mes "一次試験合格の報酬なのだ！";
			mes "受けとるのだ。";
			next;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next; 
			menu "ありがとうございます",-; 
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100918;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight(569,300)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 400;
			chgquest 100918, 100919;
			if(checkre()) {
				getexp 3500,0;
				getexp 3500,0;
				getexp 0,3000;
				getexp 0,3000;
			}
			else {
				getexp 35000,0;
				getexp 35000,0;
				getexp 0,30000;
				getexp 0,30000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 33, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "次は二次試験なのだ！";
			next;
			emotion 77, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "二次試験はワシも苦労したのじゃ。";
			mes "懐かしいのぅ……";
			next;
			menu "そんなに難しいのですか？",-;
			emotion 54, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティは、";
			mes "食べ物の匂いにつられて、";
			mes "3回も二次試験に失敗したのだ。";
			mes "　";
			mes "昔から成長していないのだ。";
			next;
			emotion 57, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "　";
			mes "ネコリン殿、";
			mes "その話はこれ以上しないで……";
			next;
			mes "[ネコリン]";
			mes "二次試験の準備をするのだ。";
			mes "それまできちんと休むのだ！";
			next;
			menu "はい！　わかりました",-;
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "寝不足で試験失敗しないようにのぅ。";
			mes "きっちり休むのじゃぞー！";
			next;
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "それでは二次試験で会おうなのだ！";
			next; 
			mes "[^FF0000第十四話終了^000000]";
			mes "‐第十五話開始には、";
			mes "　^FF0000BaseLvを43以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 15,1;
			close2;
			chgquest 100919, 201015;
			set AC_QUEST_LV_6,14;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+10;
			end;
		}
		break;
	/////////   第十五話   /////////
	case 14:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<43){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十五話開始には、";
				mes "　^FF0000BaseLvを43以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "よくきたのじゃ！";
			mes "二次試験の準備が出来たのじゃ！";
			next;
			mes "[ネコリン]";
			mes "心の準備は出来たのだ？";
			next; 
			if(select("出来ました","もう少し時間をください")==2){
				emotion 33, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "慌てず準備をしてくるのだ！";
				close;
			}
			mes "[ネコリン]";
			mes "「^FF0000二次試験^000000」は「^FF0000一次試験^000000」より";
			mes "はるかに難しいのだ……";
			next;
			emotion 52, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "でも君なら合格出来ると信じてるのだ！";
			mes "　";
			mes "「^FF0000二次試験^000000」、「^FF0000最終試験^000000」と";
			mes "残り2回なのだ！";
			next;
			menu "試験の内容を教えてください",-;
			emotion 33,"";
			mes "[ネコリン]";
			mes "「^FF0000二次試験^000000」のモンスターなのだ！";
			mes "^FF0000・^000000^FF0000ガイアス^000000";
			mes "^FF0000・^000000^FF0000銃奇兵^000000";
			mes "^FF0000・^000000^FF0000人面桃樹^000000";
			mes "^FF0000・^000000^FF0000スティング^000000";
			mes "から選ぶのだ！";
			next;
			mes "[ネコリン]";
			mes "途中でモンスターは変えられるのだ！";
			mes "　";
			mes "ただし、変えてしまうと、";
			mes "最初からやり直しなのだ！";
			next;
			menu "がんばります",-;
			mes "[ネコリン]";
			mes "さぁ！";
			mes "この中のどれか一つを選ぶのだ！";
			mes "　";
			mes "ミスティ！";
			mes "モンスターの説明をするのだ！";
			function	AC_PORING14_mobinfo	{
				switch(getarg(0)){
				case 100920:
					mes "[ミスティ]";
					mes "小さなおじいちゃん妖精なのじゃ。";
					mes "　";
					mes "いつもスコップを持っておるのじゃ。";
					mes "ちょっかいを出すと、";
					mes "それで何度も叩かれるのじゃよ。";
					break;
				case 100922:
					mes "[ミスティ]";
					mes "アマツ国で死んだ兵士が、";
					mes "骨になってよみがえったのじゃ！";
					mes "　";
					mes "銃で遠くから攻撃してくるのじゃ。";
					mes "でも聖なる攻撃や、";
					mes "回復魔法に弱いのじゃ♪";
					break;
				case 100924:
					mes "[ミスティ]";
					mes "怖い顔した樹なのじゃ……";
					mes "　";
					mes "木陰からたくさんのおさるさんが、";
					mes "かたい桃を投げてくるのじゃ！";
					mes "遠距離攻撃と、自己回復に注意じゃ。";
					break;
				case 100926:
					mes "[ミスティ]";
					mes "手袋のお化けみたいな奴なのじゃ。";
					mes "　";
					mes "蝶ネクタイをつけており、見た目に";
					mes "反してとってもおしゃれな奴なのじゃ。";
					mes "あやつのゲンコツはとても痛いのじゃ。";
					break;
				}
				return;
			}
			function	AC_PORING14_warp;
			function	AC_PORING14	{
				set '@questid,0;
				//100920,入団試験②,0,1121,40,0,0,0,0
				//100922,入団試験②,0,1403,20,0,0,0,0
				//100924,入団試験②,0,1410,10,0,0,0,0
				//100926,入団試験②,0,1207,10,0,0,0,0
				setarray '@mobname$, "^FF0000ガイアス^000000","^FF0000銃奇兵^000000","^FF0000人面桃樹^000000","^FF0000スティング^000000";
				while(1){
					next;
					set '@sel, select(printarray('@mobname$));
					switch('@sel){
					case 1:
						AC_PORING14_mobinfo 100920;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ガイアス^000000」なのだ？";
						mes "　";
						mes "^FF000040匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100920;
						break;
					case 2:
						AC_PORING14_mobinfo 100922;
						next;
						mes "[ネコリン]";
						mes "「^FF0000銃奇兵^000000」なのだ？";
						mes "　";
						mes "^FF000020匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100922;
						break;
					case 3:
						AC_PORING14_mobinfo 100924;
						next;
						mes "[ネコリン]";
						mes "「^FF0000人面桃樹^000000」なのだ？";
						mes "　";
						mes "^FF000010匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100924;
						break;
					case 4:
						AC_PORING14_mobinfo 100926;
						next;
						mes "[ネコリン]";
						mes "「^FF0000スティング^000000」なのだ？";
						mes "　";
						mes "^FF000010匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100926;
						break;
					}
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "モンスターを変えるのじゃな？";
					mes "　";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				emotion 21, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "" + '@mobname$['@sel-1] + "に";
				mes "決定なのだ！";
				mes "　";
				mes "気合をいれて倒してくるのだ!!";
				next;
				mes "[ミスティ]";
				mes "精一杯頑張るのじゃぞ♪";
				mes "　";
				mes "魔法で" + '@mobname$['@sel-1] + "の";
				mes "生息地まで送るが、どうじゃ？";
				next;
				AC_PORING14_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING14_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 15,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100920: warp "ac_prac_04.gat",261,261; break;
					case 100922: warp "ac_spec_02.gat",124,59; break;
					case 100924: warp "ac_spec_01.gat",283,34; break;
					case 100926: warp "ac_spec_03.gat",98,78; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100920: warp "mjo_dun02.gat",125,60; break;
					case 100922: warp "ama_dun01.gat",227,7; break;
					case 100924: warp "gon_dun01.gat",153,48; break;
					case 100926: warp "gl_sew03.gat",171,283; break;
					}
				}
				return;
			}
			AC_PORING14;
			end;
		case 100920:
		case 100922:
		case 100924:
		case 100926:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "順調に二次試験をこなせてるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100920: set '@select$,'@select$ + "「^FF0000ガイアス^000000」について教えて";  break;
				case 100922: set '@select$,'@select$ + "「^FF0000銃奇兵^000000」について教えて";  break;
				case 100924: set '@select$,'@select$ + "「^FF0000人面桃樹^000000」について教えて"; break;
				case 100926: set '@select$,'@select$ + "「^FF0000スティング^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING14_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ネコリン]";
					mes "途中でモンスターは変えられるのだ！";
					mes "　";
					mes "ただし、変えてしまうと、";
					mes "最初からやり直しなのだ！";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING14_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING14;
					end;
				case 3:
					AC_PORING14_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			mes "[ミスティ]";
			mes "おかえりなのじゃ♪";
			next;
			emotion 12, "ミスティ#ac_Misty";
			menu "倒してきました",-;
			mes "[ネコリン]";
			mes "おめでとうなのだ！";
			mes "二次試験合格なのだ！";
			next;
			menu "はぁはぁ……疲れました",-;
			emotion 19,"";
			emotion 18, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "なかなか苦戦しているようじゃのぅ。";
			mes "怪我はせんかったかのぅ？";
			next;
			menu "なんとか大丈夫です",-;
			emotion 19,"";
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "それはよかったのじゃ♪";
			mes "あまり無理をするでないぞ？";
			mes "　";
			mes "わかったかのぅ？";
			next;
			menu "はい",-;
			mes "[ネコリン]";
			mes "二次試験合格の報酬なのだ！";
			mes "受けとるのだ。";
			next;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next; 
			menu "ありがとうございます",-; 
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100928;
		case 3:
			if(!checkitemblank()){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight(569,400)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 400;
			chgquest 100928, 100929;
			if(checkre()) {
				getexp 4700,0;
				getexp 4700,0;
				getexp 0,3750;
				getexp 0,3750;
			}
			else {
				getexp 47000,0;
				getexp 47000,0;
				getexp 0,37500;
				getexp 0,37500;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "いよいよ最後の試験なのだ！";
			next;
			emotion 53, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "最終試験は難しいのじゃ……";
			mes "しかし、今まで学んだ事を活かせば";
			mes "必ず合格するはずじゃ！";
			next;
			menu "はいっ！",-;
			emotion 33, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティも苦労したけど、";
			mes "合格出来たのだ！";
			next;
			emotion 2, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿、";
			mes "そんなに褒めなくても♪";
			mes "　";
			mes "あの試験に合格出来たのは";
			mes "今の所ワシだけじゃからのぅ♪";
			next;
			menu "難易度が高そうですね……",-;
			emotion 19,"";
			mes "[ネコリン]";
			mes "大丈夫なのだ！";
			mes "ミスティが合格出来るレベルなのだ。";
			mes "　";
			mes "君なら合格間違い無いのだ！";
			next;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "合格間違い無しなのじゃ♪";
			mes "　";
			mes "…………？";
			mes "ネコリン殿……？";
			mes "それはどういう意味なのじゃ？";
			next;
			emotion 1, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "最終試験の準備をするのだ！";
			mes "　";
			mes "それまで、";
			mes "二次試験の疲れや怪我を、";
			mes "しっかり治すのだ！";
			next;
			menu "はい！　わかりました",-;
			emotion 21, "ネコリン#ac_Necorin";
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ちょっと？　ネコリン殿？";
			mes "話を聞いてほしいのじゃ。";
			mes "　";
			mes "ワシが合格出来るレベルって";
			mes "どういう意味なのじゃぁ～！";
			next;
			emotion 12, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "それでは最終試験で会おうなのだ！";
			next;
			mes "[^FF0000第十五話終了^000000]";
			mes "‐第十六話開始には、";
			mes "　^FF0000BaseLvを46以上^000000にして";
			mes "　話し掛けてみよう‐";
			next;
			Information 16,1;
			close2;
			chgquest 100929, 201020;
			set AC_QUEST_LV_6,15;
			set AC_QUEST_ST_6,0;
			set AC_CREDIT, AC_CREDIT+10;
			end;
		}
		break;
	/////////   第十六話   /////////
	case 15:
		switch(AC_QUEST_ST_6){
		case 0:
			if(BaseLevel<46){//未調査なのだ！
				mes "[インフォメーション]";
				mes "‐第十六話開始には、";
				mes "　^FF0000BaseLvを46以上^000000にして";
				mes "　話し掛けてみよう‐";
				close;
			}
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "よくきたのだ！";
			mes "最終試験の準備が出来たのだ！";
			next;
			mes "［ミスティ］";
			mes "はぁぁ～、";
			mes "ワシの大切なおやつが……";
			mes "　";
			mes "さぞ美味しかったじゃろうなぁ、";
			mes "美味かったじゃろうなぁ……";
			next;
			menu "ミスティは、どうしたんですか？",-;
			emotion 22,"";
			mes "[ネコリン]";
			mes "ミスティなら";
			mes "隅っこでいじけてるのだ。";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "うぅ……";
			mes "ネコリン殿、ひどいのじゃ。";
			mes "　";
			mes "ワシの隠しておいた、";
			mes "焼きゼロピーを勝手に食べたのじゃ！";
			next;
			emotion 32, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ポリン団の一員たるもの、";
			mes "細かい事をいつまでも";
			mes "気にしちゃ駄目なのだ！";
			mes "　";
			mes "いつまでも根に持ってちゃ駄目なのだ！";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ワシにとっては細かくないのじゃ。";
			mes "死活問題なのじゃ……";
			next;
			menu "あの……",-;
			emotion 19,"";
			mes "[ネコリン]";
			mes "わかったのだ……";
			mes "今度お詫びに、";
			mes "焼きゼロピーを買ってくるのだ！";
			mes "　";
			mes "だから機嫌を直すのだ!!";
			next;
			emotion 76, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "本当か？　絶対じゃぞ!?";
			mes "約束じゃからな！";
			next;
			menu "あの……もしもし……？",-;
			emotion 19,"";
			emotion 0, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "おっとそうだったのだ。";
			mes "すっかり忘れてたのだ……";
			next;
			emotion 52, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "さぁ！";
			mes "いよいよ最終試験じゃな！";
			mes "心の準備は出来たのかのぅ？";
			next;
		case 100930:
			if(AC_QUEST_ST_6==1){
				emotion 52;
				mes "[ミスティ]";
				mes "心の準備は出来たかのぅ？";
				next;
			}
			if(select("出来ました","もう少し時間をください")==2){
				set AC_QUEST_ST_6, 100930;
				setquest 100930;
				emotion 21, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "あわてず準備をしてくるのだ！";
				close;
			}
			emotion 21, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "いよいよ受けるのじゃな！";
			next;
			mes "[ネコリン]";
			mes "「^FF0000最終試験^000000」なのだ！";
			mes "　";
			mes "悔いのないよう精一杯戦うのだ！";
			next;
			menu "試験の内容を教えてください",-;
			emotion 5, "ネコリン#ac_Necorin";
			emotion 33,"";
			mes "[ネコリン]";
			mes "「^FF0000最終試験^000000」のモンスターなのだ！";
			mes "^FF0000・^000000^FF0000アナコンダク^000000";
			mes "^FF0000・^000000^FF0000ゴーレム^000000";
			mes "^FF0000・^000000^FF0000ホード^000000";
			mes "^FF0000・^000000^FF0000アーチャースケルトン^000000";
			mes "から選ぶのだ！";
			next;
			mes "[ネコリン]";
			mes "途中でモンスターは変えられるのだ！";
			mes "　";
			mes "ただし、変えてしまうと、";
			mes "最初からやり直しなのだ！";
			next;
			menu "がんばります",-;
			emotion 27, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "さぁ！";
			mes "この中のどれか一つを選ぶのだ！";
			mes "　";
			mes "ミスティ！";
			mes "モンスターの説明をするのだ！";
			function	AC_PORING15_mobinfo	{
				switch(getarg(0)){
				case 100932:
					mes "[ミスティ]";
					mes "赤いヘビなのじゃ。";
					mes "　";
					mes "こやつの毒は、アサシンが使う毒に";
					mes "よく使われておるのじゃ♪";
					mes "緑のヘビと違ってかなり強いのじゃ。";
					mes "注意が必要なのじゃ。";
					break;
				case 100934:
					mes "[ミスティ]";
					mes "大きな石の巨人なのじゃ。";
					mes "　";
					mes "体がとっても硬く、並の武器だと";
					mes "歯が立たないくらい硬いのじゃ。";
					mes "じゃが、その分動きは遅いぞ。";
					break;
				case 100936:
					mes "[ミスティ]";
					mes "砂漠地方にいるミミズじゃな。";
					mes "　";
					mes "火に弱く、いつも地面に隠れておるぞ。";
					mes "少し見つけにくいかも知れんのぅ。";
					mes "火に弱いなら別の涼しい地方に、";
					mes "住めばいいと思うんじゃがなぁ。";
					break;
				case 100938:
					mes "[ミスティ]";
					mes "死んだ弓兵が、";
					mes "骨になってよみがえったのじゃ！";
					mes "　";
					mes "弓で遠くから攻撃してくるのじゃ。";
					mes "でも聖なる攻撃や、";
					mes "回復魔法に弱いのじゃ♪";
					break;
				}
				return;
			}
			function	AC_PORING15_warp;
			function	AC_PORING15	{
				set '@questid,0;
				//100932,入団試験③,0,1030,50,0,0,0,0
				//100934,入団試験③,0,1040,50,0,0,0,0
				//100936,入団試験③,0,1127,30,0,0,0,0
				//100938,入団試験③,0,1016,20,0,0,0,0
				setarray '@mobname$, "^FF0000アナコンダク^000000","^FF0000ゴーレム^000000","^FF0000ホード^000000","^FF0000アーチャースケルトン^000000";
				while(1){
					next;
					set '@sel, select(printarray('@mobname$));
					switch('@sel){
					case 1:
						AC_PORING15_mobinfo 100932;
						next;
						mes "[ネコリン]";
						mes "「^FF0000アナコンダク^000000」なのだ？";
						mes "　";
						mes "^FF000050匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100932;
						break;
					case 2:
						AC_PORING15_mobinfo 100934;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ゴーレム^000000」なのだ？";
						mes "　";
						mes "^FF000050匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100934;
						break;
					case 3:
						AC_PORING15_mobinfo 100936;
						next;
						mes "[ネコリン]";
						mes "「^FF0000ホード^000000」なのだ？";
						mes "　";
						mes "^FF000030匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100936;
						break;
					case 4:
						AC_PORING15_mobinfo 100938;
						next;
						mes "[ネコリン]";
						mes "「^FF0000アーチャースケルトン^000000」なのだ？";
						mes "　";
						mes "^FF000020匹^000000ほど倒してくれば合格なのだ！";
						set '@questid, 100938;
						break;
					}
					next;
					if(select("そのモンスターにします","やっぱり違うモンスターに…")==1) break;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
				}
				chgquest AC_QUEST_ST_6, '@questid;
				set AC_QUEST_ST_6,'@questid;
				emotion 21, "ネコリン#ac_Necorin";
				mes "[ネコリン]";
				mes "" + '@mobname$['@sel-1] + "に";
				mes "決定なのだ！";
				mes "　";
				mes "気合をいれて倒してくるのだ!!";
				next;
				mes "[ミスティ]";
				mes "精一杯頑張るのじゃぞ♪";
				mes "　";
				mes "魔法で" + '@mobname$['@sel-1] + "の";
				mes "生息地まで送るが、どうじゃ？";
				next;
				AC_PORING15_warp (select("自分で歩きます","お願いします")==1);
				return;
			}
			function	AC_PORING15_warp	{
				if(!getarg(0) && !'@novice){
					mes "[ネコリン]";
					mes "ちょっと待つのだ。";
					mes "^FF0000蝶の羽^000000は持ったのだ？";
					mes "　";
					mes "忘れていると帰りが";
					mes "大変なときもあるのだ！";
					mes "それでも、行くのだ？";
					next;
					if(select("はい","いいえ")==2){
						mes "[ネコリン]";
						mes "しっかり準備はした方が良いのだ。";
						mes "また、いつでも来るのだ。";
						mes "それじゃ、準備してくるのだ！";
						close;
					}
					mes "[ネコリン]";
					mes "持って行ったほうが良いのだ……";
					mes "　";
					mes "何があっても知らないのだ！";
					next;
				}
				Information 16,0;
				if(getarg(0)){
					emotion 54;
					mes "[ミスティ]";
					mes "そうか……";
					mes "魔法を使いたかったのに残念じゃのぅ。";
					mes "　";
					mes "しっかり準備をして頑張るんじゃぞ～。";
					close;
				}
				emotion 78;
				mes "[ミスティ]";
				mes "うむ！";
				mes "いざ、出陣じゃ～！";
				mes "　";
				mes "まーご、まーご、けらひぃ～♪";
				mes "　";
				mes "‐^FF0000セーブ地点として記録しました^000000‐";
				savepoint "ac_cl_area.gat",53,180;
				close2;
				if('@novice){
					switch(AC_QUEST_ST_6){
					case 100932: warp "ac_prac_05.gat",57,170; break;
					case 100934: warp "ac_prac_05.gat",57,170; break;
					case 100936: warp "ac_prac_05.gat",57,170; break;
					case 100938: warp "ac_spec_02.gat",124,59; break;
					}
				}else{
					switch(AC_QUEST_ST_6){
					case 100932: warp "cmd_fild09.gat",210,270; break;
					case 100934: warp "gef_fild08.gat",200,352; break;
					case 100936: warp "moc_fild17.gat",366,272; break;
					case 100938: warp "pay_dun01.gat",283,28; break;
					}
				}
				return;
			}
			AC_PORING15;
			end;
		case 100932:
		case 100934:
		case 100936:
		case 100938:
			if(!(checkquest(AC_QUEST_ST_6)&0x4)){
				mes "[ミスティ]";
				mes "どうじゃ？　調子は♪";
				mes "　";
				mes "順調に最終試験をこなせてるかのぅ？";
				next;
				set '@select$,"現地まで送ってほしい:モンスターを変更したい:";
				switch(AC_QUEST_ST_6){
				case 100932: set '@select$,'@select$ + "「^FF0000アナコンダク^000000」について教えて";  break;
				case 100934: set '@select$,'@select$ + "「^FF0000ゴーレム^000000」について教えて";  break;
				case 100936: set '@select$,'@select$ + "「^FF0000ホード^000000」について教えて"; break;
				case 100938: set '@select$,'@select$ + "「^FF0000アーチャースケルトン^000000」について教えて"; break;
				}
				switch(select('@select$)){
				case 1:
					AC_PORING15_warp 0;
				case 2:
					emotion 4;
					mes "[ミスティ]";
					mes "少し厳しかったかのぅ？";
					next;
					mes "[ネコリン]";
					mes "途中でモンスターは変えられるのだ！";
					mes "　";
					mes "ただし、変えてしまうと、";
					mes "最初からやり直しなのだ！";
					next;
					if(select("はい、大丈夫です","やっぱり同じモンスターで")==2){
						emotion 33;
						mes "[ミスティ]";
						mes "うんうん。";
						mes "精一杯頑張るのじゃぞ♪";
						mes "　";
						mes "よかったら";
						mes "魔法で現地まで送るが、どうじゃ？";
						next;
						AC_PORING15_warp (select("自分で歩きます","お願いします")==1);
					}
					emotion 33;
					mes "[ミスティ]";
					mes "では、改めて選ぶのじゃ！";
					AC_PORING15;
					end;
				case 3:
					AC_PORING15_mobinfo AC_QUEST_ST_6;
					close;
				}
			}
			emotion 12, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "おかえりなのじゃ♪";
			next;
			menu "倒してきました",-;
			emotion 46, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "おめでとうなのだ！";
			mes "最終試験合格なのだ！";
			next;
			emotion 28, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ついに後輩が出来たのじゃ。";
			next;
			menu "よろしくお願いします、先輩！",-;
			emotion 18,"";
			emotion 0, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "先輩!?";
			mes "いい響きなのじゃ♪";
			next;
			emotion 2, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "まずは、";
			mes "最終試験合格の報酬なのだ！";
			mes "うけとるのだ。";
			next;
			emotion 46, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ん～　ポリ～ンっと！";
			mes "ほれ、君の単位を増やしておいたぞ。";
			mes "ついでに、これもプレゼントじゃ！";
			next;
			menu "ありがとうございます",-;
			emotion 15,"";
			chgquest AC_QUEST_ST_6, 100940;
		case 3:
			if(!checkitemblank2(2)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000種類^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(!checkweight2(569,400, 11518,100)){
				set AC_QUEST_ST_6,3;
				emotion 23;
				mes "[ネコリン]";
				mes "おや？";
				mes "アイテムを沢山持ち過ぎなのだ。";
				mes "「^FF0000重量^000000」を減らしてからまたくるのだ！";
				mes "　";
				mes "[ミスティ]";
				mes "そんなに持っておったのか!?";
				close;
			}
			if(AC_QUEST_ST_6==3){
				emotion 33;
				mes "[ミスティ]";
				mes "うんうん。";
				mes "きちんと減らしてきたようじゃな。";
				next;
			}
			getitem 569, 400;
			getitem 11518, 100;
			chgquest 100940, 100942;
			if(checkre()) {
				getexp 6600,0;
				getexp 6600,0;
				getexp 0,4500;
				getexp 0,4500;
			}
			else {
				getexp 66000,0;
				getexp 66000,0;
				getexp 0,45000;
				getexp 0,45000;
			}
			set AC_QUEST_ST_6,4;
		case 4:
			emotion 55,"";
			mes "[ネコリン]";
			mes "いよいよポリン団、団員No3の";
			mes "バッジをあげるのだ！";
			next;
			emotion 32, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿がNo1、";
			mes "ワシがNo2なのじゃ！";
			next;
			menu "かっこいいバッジですね",-;
			emotion 2, "ネコリン#ac_Necorin";
			emotion 2, "ミスティ#ac_Misty";
			emotion 37,"";
			mes "[ネコリン]";
			mes "さぁ受け取るのだ！";
			next;
			menu "ありがとうございます",-;
			mes "[謎の声]";
			mes "……ついに見つけたわよ！";
			next;
			emotion 23, "ネコリン#ac_Necorin";
			emotion 23, "ミスティ#ac_Misty";
			mes "[ネコリン]";
			mes "しまったのだ！";
			mes "ルーンに見つかったのだ！";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿！";
			mes "早く逃げるのじゃ！";
			next;
			menu "え？　あの、ちょっと……",-;
			emotion 19,"";
			cutin "jpn_run03.bmp", 2;
			mes "[ルーン]";
			mes "今日と言う今日は逃がさないわよ！";
			next;
			cutin "jpn_run03.bmp", 255;
			emotion 16, "ネコリン#ac_Necorin";
			mes "[ネコリン]";
			mes "ミスティ逃げるのだ！";
			mes "　";
			mes "絶対につかまってはいけないのだ!!";
			next;
			emotion 19, "ミスティ#ac_Misty";
			mes "[ミスティ]";
			mes "ネコリン殿！";
			mes "　";
			mes "待ってくだされぇー……";
			next;
			cutin "jpn_run02.bmp", 2;
			mes "[ルーン]";
			mes "ちょっとそこのあなた！";
			mes "聞きたい事があるんだけど";
			next;
			menu "は、はい！",-;
			emotion 16,"";
			cutin "jpn_run01.bmp", 2;
			mes "[ルーン]";
			mes "あなた、ポリン団を知らない？";
			next;
			switch(select("実は……ポリン団の一員です","いいえ、知りません")){
			case 1: set AC_QUEST_ST_6, 100944; break;
			case 2: set AC_QUEST_ST_6, 100946; break;
			}
			function	AC_PORING_END	{
				switch(AC_QUEST_ST_6){
				case 100944:
					emotion 33,"";
					chgquest 100942, 100944;
					cutin "jpn_run02.bmp", 2;
					mes "[ルーン]";
					mes "ふふふ、";
					mes "ついに捕まえたわよ。";
					next;
					cutin "jpn_run05.bmp", 2;
					emotion 9,"";
					mes "[ルーン]";
					mes "あなた達の活動に";
					mes "目をつむってきたけど、";
					mes "もう我慢できないわ！";
					next;
					mes "[ルーン]";
					mes "ご老人や主婦、健康志向の奥様方に";
					mes "変な物を売りつけて……";
					mes "　";
					mes "しかも何なの！";
					mes "あの変なロボットは!!";
					next;
					menu "ごめんなさい！　ごめんなさい！",-;
					emotion 17,"";
					cutin "jpn_run03.bmp", 2;
					mes "[ルーン]";
					mes "正体を隠して、影でコソコソと……";
					mes "　";
					mes "お礼をしたくても、";
					mes "これじゃ出来ないじゃないの!!";
					next;
					menu "え!?",-;
					cutin "jpn_run05.bmp", 2;
					emotion 23,"";
					mes "[ルーン]";
					mes "食堂の平和も守られて、";
					mes "みんなも感謝しているのに……";
					mes "　";
					mes "お礼を言わせず";
					mes "逃げ回るなんて許せないわ！";
					next;
					mes "[ルーン]";
					mes "たまたま、";
					mes "あなた達の作っていたものに";
					mes "製造元が入っていたから、";
					mes "見当が付いたけど……";
					mes "　";
					mes "それもご丁寧に、ポリンＤＡＮと！";
					next;
					cutin "jpn_run01.bmp", 2;
					mes "[ルーン]";
					mes "団長にこう伝えなさい！";
					mes "　";
					mes "「みんなの前に出てくるように」って♪";
					next;
					mes "[ルーン]";
					mes "いいわね！";
					next;
					menu "わかりました",-;
					emotion 33,"";
					cutin "jpn_run02.bmp", 2;
					mes "[ルーン]";
					mes "じゃぁ宜しく頼んだわよ。";
					mes "　";
					mes "　";
					mes "……あっ！　そうそう。";
					next;
					cutin "jpn_run03.bmp", 2;
					mes "[ルーン]";
					mes "あなた、ポリン団から";
					mes "こっそり単位をもらってたでしょ？";
					next;
					menu "……はい",-;
					emotion 4,"";
					cutin "jpn_run02.bmp", 2;
					mes "[ルーン]";
					mes "程々にしてちょうだい。";
					mes "　";
					mes "そんな事をしなくても、";
					mes "私がちゃんと単位をあげるわ。";
					mes "　";
					mes "それじゃ、ちゃんと伝えてね。";
					next;
					cutin "jpn_run02.bmp", 255;
					mes "‐試験は無事合格出来た‐";
					mes "　";
					mes "‐案の定、製造元が原因で";
					mes "　今までの事は、";
					mes "　全て知られていたようだ‐";
					next;
					emotion 19, "ミスティ#ac_Misty";
					emotion 19, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "ふぅ、危なかったのだ。";
					mes "ルーンから無事に逃げ切れたのだ？";
					mes "　";
					mes "最近、監視の目が厳しいのだ。";
					next;
					mes "[ミスティ]";
					mes "おや？";
					mes "" + strcharinfo(0) + "";
					mes "どうしたのじゃ？";
					next;
					menu "実は……",-;
					mes "[ミスティ]";
					mes "……なんじゃと!!";
					mes "　";
					mes "今までの活動が、";
					mes "ルーンに全てバレていたじゃと!?";
					next;
					emotion 0, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "ポリン団は";
					mes "謎の組織じゃないと駄目なのだ！";
					mes "　";
					mes "活動がバレるとは……";
					mes "不覚だったのだ。";
					next;
					emotion 2, "ミスティ#ac_Misty";
					mes "[ミスティ]";
					mes "まぁ、";
					mes "" + strcharinfo(0) + "が";
					mes "無事だったのじゃ!!";
					mes "ネコリン殿、良いではないか♪";
					mes "人に感謝されるのも";
					mes "悪い気はしないのじゃ♪";
					next;
					mes "[ミスティ]";
					mes "しかし、一体";
					mes "どこでバレたのじゃろう？";
					mes "活動だけでなく、";
					mes "組織の名前までバレているとは……";
					next;
					emotion 54, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "バレてしまってはしょうがないのだ。";
					mes "　";
					mes "しばらくは活動を自粛して、";
					mes "隠れるしかないのだ！";
					next;
					emotion 28, "ミスティ#ac_Misty";
					mes "［ミスティ］";
					mes "団員が増えたと言うのに";
					mes "活動ができないのは残念なのじゃ。";
					next;
					mes "［ネコリン］";
					mes "まったく、残念なのだ……";
					next;
					mes "［ミスティ］";
					mes "これからじゃと言うのにのぅ……";
					next;
					emotion 21, "ネコリン#ac_Necorin";
					mes "［ネコリン］";
					mes "" + strcharinfo(0) + "も";
					mes "よく知らせてくれたのだ。";
					mes "　";
					mes "おかげで捕まらずにすんだのだ。";
					next;
					mes "［ネコリン］";
					mes "活動を再開する時が来たら";
					mes "必ず召集するのだ！";
					mes "　";
					mes "その時はまた暴れるのだ!!";
					next;
					mes "［ミスティ］";
					mes "我ら生まれた時は違えども、";
					mes "捕まる時は一緒なのじゃ!!";
					mes "　";
					mes "決して捕まるでないぞ？";
					next;
					menu "はい！",-;
					emotion 12, "ネコリン#ac_Necorin";
					emotion 12, "ミスティ#ac_Misty";
					emotion 12,"";
					mes "［ネコリン］";
					mes "それでは、また会おうなのだ！";
					mes "　";
					mes "［ミスティ］";
					mes "また、会おうなのじゃ！";
					chgquest 100944, 201025;
					set AC_QUEST_LV_6, 16;
					set AC_QUEST_ST_6, 201025;
					close2;
					break;
				case 100946:
					emotion 22,"";
					chgquest 100942, 100946;
					cutin "jpn_run03.bmp", 2;
					mes "[ルーン]";
					mes "本当？";
					mes "　";
					mes "……まぁいいわ。";
					mes "あなたの事を信じてあげるわ。";
					next;
					cutin "jpn_run05.bmp", 2;
					mes "[ルーン]";
					mes "もし今度ポリン団を見かけたら、";
					mes "真っ先に私に教えてちょうだいね。";
					mes "　";
					mes "頼んだわよ。";
					next;
					menu "わかりました",-;
					emotion 33,"";
					cutin "jpn_run03.bmp", 2;
					mes "[ルーン]";
					mes "………";
					mes "まったくもう……";
					mes "　";
					mes "お礼を言いたいのに";
					mes "いつも逃げるなんて……";
					next;
					menu "何か言いましたか？",-;
					cutin "jpn_run04.bmp", 2;
					cutin "jpn_run02.bmp", 2;
					emotion 55,"";
					mes "[ルーン]";
					mes "……！";
					mes "　";
					mes "な、何でもないわ。";
					mes "それじゃ見かけたらよろしくね。";
					next;
					cutin "jpn_run02.bmp", 255;
					mes "‐試験は無事合格出来た";
					mes "　ポリン団の秘密は守る事が出来た‐";
					mes "　";
					mes "‐それにしてもルーンは";
					mes "　何を伝えたかったのだろう？‐";
					next;
					emotion 19, "ミスティ#ac_Misty";
					emotion 19, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "ふぅ、危なかったのだ。";
					mes "ルーンから無事に逃げ切れたのだ？";
					mes "　";
					mes "最近、監視の目が厳しいのだ。";
					next;
					mes "[ミスティ]";
					mes "おや？";
					mes "" + strcharinfo(0) + "";
					mes "どうしたのじゃ？";
					next;
					menu "実は……",-;
					emotion 0, "ミスティ#ac_Misty";
					mes "[ミスティ]";
					mes "そんな事があったのじゃな……";
					mes "危うくバレる所じゃった。";
					next;
					emotion 4, "ネコリン#ac_Necorin";
					mes "[ネコリン]";
					mes "危なかったのだ……";
					mes "　";
					mes "ポリン団は、";
					mes "謎の組織じゃないと駄目なのだ。";
					mes "　";
					mes "今後も気をつけるのだ!!";
					next;
					mes "［ネコリン］";
					mes "しかしなぜ、ルーンは";
					mes "ポリン団の名を？";
					mes "これは、バレているのだ？";
					next;
					menu "そういえば、製造元が……",-;
					emotion 4,"";
					emotion 0, "ネコリン#ac_Necorin";
					mes "［ネコリン］";
					mes "な、なんと言うことなのだ！";
					mes "ミスティ！";
					mes "ミスティ!!";
					mes "　";
					mes "ラベルは結局どうなったのだ!?";
					next;
					emotion 55, "ミスティ#ac_Misty";
					mes "［ミスティ］";
					mes "不味かったかのぅ？";
					mes "　";
					mes "少しでも親切に返品や苦情への";
					mes "問い合わせの為…………";
					next;
					emotion 9, "ネコリン#ac_Necorin";
					emotion 9,"";
					mes "‐ミスティの沈黙と共に";
					mes "　冷たい空気がポリン団包み込む‐";
					mes "　";
					mes "‐ミスティに突き刺さる";
					mes "　鋭いネコリンの視線‐";
					next;
					emotion 23, "ミスティ#ac_Misty";
					mes "［ミスティ］";
					mes "しまったのじゃ!!!!";
					mes "まったく気づかなかったのじゃ！";
					mes "　";
					mes "ネコリン殿、";
					mes "なぜ止めなかったのじゃ！";
					next;
					mes "［ネコリン］";
					mes "むむぅ……";
					mes "　";
					mes "夢中になりすぎて、";
					mes "まったく気づかなかったのだ！";
					next;
					mes "［ミスティ］";
					mes "ネ、ネコリン殿!!";
					next;
					emotion 54, "ネコリン#ac_Necorin";
					mes "［ネコリン］";
					mes "えぇぃ、離れるのだ！";
					mes "うっとうしいのだ！";
					mes "　";
					mes "正体がバレた可能性がある以上は、";
					mes "ほとぼりが冷めるまで";
					mes "自粛するしかないのだ……";
					next;
					emotion 28, "ミスティ#ac_Misty";
					mes "［ミスティ］";
					mes "しかし、団員が増えたと言うのに";
					mes "活動ができないのは残念なのじゃ……";
					next;
					mes "［ネコリン］";
					mes "まったく、残念なのだ……";
					next;
					mes "［ミスティ］";
					mes "これからじゃと言うのにのぅ……";
					next;
					emotion 21, "ネコリン#ac_Necorin";
					mes "［ネコリン］";
					mes "" + strcharinfo(0) + "も";
					mes "よく知らせてくれたのだ。";
					mes "　";
					mes "おかげで捕まらずにすんだのだ。";
					next;
					mes "［ネコリン］";
					mes "活動を再開する時が来たら";
					mes "必ず召集するのだ！";
					mes "　";
					mes "その時はまた暴れるのだ!!";
					next;
					mes "［ミスティ］";
					mes "我ら生まれた時は違えども、";
					mes "捕まる時は一緒なのじゃ!!";
					mes "　";
					mes "決して捕まるでないぞ？";
					next;
					menu "はい！",-;
					emotion 12, "ネコリン#ac_Necorin";
					emotion 12, "ミスティ#ac_Misty";
					emotion 12,"";
					mes "［ネコリン］";
					mes "それでは、また会おうなのだ！";
					mes "　";
					mes "［ミスティ］";
					mes "また、会おうなのじゃ！";
					chgquest 100946, 201030;
					set AC_QUEST_LV_6, 16;
					set AC_QUEST_ST_6, 201030;
					close2;
				}
				return;
			}
		case 100944:
		case 100946:
			AC_PORING_END;
			set AC_CREDIT, AC_CREDIT+10;
			end;
		}
		break;
	/////////   第十七話？   /////////
	case 16:
		emotion 1, "ネコリン#ac_Necorin";
		mes "［ネコリン］";
		mes "むむ？　君は誰なのだ？";
		mes "何かようなのだ？";
		next;
		menu "忘れたのですか？",-;
		emotion 1;
		mes "［ミスティ］";
		mes "一体なんの事じゃ？";
		mes "" + strcharinfo(0) + "とは";
		mes "話した事も無いのじゃ。";
		mes "　";
		mes "……あっ！";
		next;
		mes "［ネコリン］";
		mes "…………";
		mes "ミスティは相変わらずバカなのだ……";
		mes "　";
		mes "みんなで集まってたら見つかるのだ！";
		mes "活動を再開する時が来たら";
		mes "必ず召集するのだ！";
		next;
		emotion 36, "ネコリン#ac_Necorin";
		emotion 28;
		emotion 4,"";
		mes "［ネコリン］";
		mes "ミスティは後でお仕置きなのだ！";
		mes "それでは、また会おうなのだ！";
		mes "　";
		mes "［ミスティ］";
		mes "うぅ……ネコリン殿、";
		mes "お仕置きは許してほしいのじゃ……";
		close;
	}
	
	function	checkitemblank2	{
		getinventorylist;
		return (100-@inventorylist_count>getarg(0));
	}
	
	function	checkweight2	{
		set '@i,0;
		set '@w,0;
		set '@cnt, getargcount()/2;
		while('@i<'@cnt){
			set '@w, '@w + getiteminfo(getarg('@i*2),6) * getarg('@i*2+1);
			set '@i,'@i+1;
		}
		return (Weight+'@w < MaxWeight);
	}
	
	function	Information	{
		mes "[インフォメーション]";
		switch(getarg(0)){
		case 1:
			mes "‐第一話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：20";
				mes "JobExp：2";
			}
			else {
				mes "BaseExp：40";
				mes "JobExp：16";
			}
			mes "アイテム：";
			mes "初心者用ポーション 50個";
			break;
		case 2:	
			mes "‐第二話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：24";
				mes "JobExp：8";
			}
			else {
				mes "BaseExp：176";
				mes "JobExp：88";
			}
			mes "アイテム：";
			mes "初心者用ポーション 100個";
			break;
		case 3:
			mes "‐第三話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：44";
				mes "JobExp：24";
			}
			else {
				mes "BaseExp：436";
				mes "JobExp：250";
			}
			mes "アイテム：";
			mes "初心者用ポーション 150個";
			break;
		case 4:
			mes "‐第四話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：99";
				mes "JobExp：57";
			}
			else {
				mes "BaseExp：999";
				mes "JobExp：570";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			break;
		case 5:
			mes "‐第五話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：180";
				mes "JobExp：30";
			}
			else {
				mes "BaseExp：1800";
				mes "JobExp：300";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			mes "スピードアップポーション 10個";
			break;
		case 6:
			mes "‐第六話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：260";
				mes "JobExp：100";
			}
			else {
				mes "BaseExp：2600";
				mes "JobExp：1000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			mes "蝶の羽 5個";
			break;
		case 7:
			mes "‐第七話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：360";
				mes "JobExp：240";
			}
			else {
				mes "BaseExp：3600";
				mes "JobExp：2400";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			mes "初心者用青ポーション 50個";
			break;
		case 8:
			mes "‐第八話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：400";
				mes "JobExp：480";
			}
			else {
				mes "BaseExp：4000";
				mes "JobExp：4800";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			break;
		case 9:
			mes "‐第九話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：600";
				mes "JobExp：900";
			}
			else {
				mes "BaseExp：6000";
				mes "JobExp：9000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 200個";
			mes "初心者用青ポーション 50個";
			break;
		case 10:
			mes "‐第十話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：1200";
				mes "JobExp：1500";
			}
			else {
				mes "BaseExp：12000";
				mes "JobExp：15000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 300個";
			mes "スピードアップポーション 10個";
			break;
		case 11:
			mes "‐第十一話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：1600";
				mes "JobExp：2800";
			}
			else {
				mes "BaseExp：16000";
				mes "JobExp：28000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 300個";
			mes "蝶の羽 10個";
			break;
		case 12:
			mes "‐第十二話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：2400";
				mes "JobExp：3800";
			}
			else {
				mes "BaseExp：24000";
				mes "JobExp：38000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 300個";
			break;
		case 13:
			mes "‐第十三話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：4200";
				mes "JobExp：4800";
			}
			else {
				mes "BaseExp：42000";
				mes "JobExp：48000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 300個";
			break;
		case 14:
			mes "‐第十四話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：7000";
				mes "JobExp：6000";
			}
			else {
				mes "BaseExp：70000";
				mes "JobExp：60000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 400個";
			break;
		case 15:
			mes "‐第十五話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：9400";
				mes "JobExp：7500";
			}
			else {
				mes "BaseExp：94000";
				mes "JobExp：75000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 400個";
			break;
		case 16:
			mes "‐第十六話　報酬/獲得アイテム‐";
			if(checkre()) {
				mes "BaseExp：13200";
				mes "JobExp：9000";
			}
			else {
				mes "BaseExp：132000";
				mes "JobExp：90000";
			}
			mes "アイテム：";
			mes "初心者用ポーション 400個";
			mes "初心者用青ポーション 100個";
			break;
		}
		next;
		mes "[インフォメーション]";
		mes "‐獲得アイテムの詳細を";
		mes "確認しますか？‐";
		next;
		switch(getarg(0)){
		case 1:
		case 2:
		case 3:
		case 4:
		case 8:
		case 12:
		case 13:
		case 14:
		case 15:
			switch(select("確認しない","初心者用ポーション")){
			case 1:
				if(getarg(1)){
					mes "[インフォメーション]";
					mes "‐獲得アイテムの確認を";
					mes "行いませんでした‐";
				}
				return;
			case 2:
				mes "[インフォメーション]";
				mes "‐初心者用ポーション‐";
				mes "冒険を始めるノービスたちのために";
				mes "用意されたポーション。";
				mes "^000088HPが少量回復^000000する。";
				mes "重量 : ^7777771^000000";
				break;
			}
			break;
		case 5:
		case 10:
			switch(select("確認しない","初心者用ポーション","スピードアップポーション")){
			case 1:
				if(getarg(1)){
					mes "[インフォメーション]";
					mes "‐獲得アイテムの確認を";
					mes "行いませんでした‐";
				}
				return;
			case 2:
				mes "[インフォメーション]";
				mes "‐初心者用ポーション‐";
				mes "冒険を始めるノービスたちのために";
				mes "用意されたポーション。";
				mes "^000088HPが少量回復^000000する。";
				mes "重量 : ^7777771^000000";
				break;
			case 3:
				mes "[インフォメーション]";
				mes "‐スピードアップポーション‐";
				mes "服用すると集中力を高めてくれる";
				mes "成分を持った水薬。";
				mes "攻撃速度(Aspd)を上げる効果がある。";
				mes "すべてのキャラクターが使用できる。";
				mes "重量 : ^77777710^000000";
				break;
			}
			break;
		case 6:
		case 11:
			switch(select("確認しない","初心者用ポーション","蝶の羽")){
			case 1:
				if(getarg(1)){
					mes "[インフォメーション]";
					mes "‐獲得アイテムの確認を";
					mes "行いませんでした‐";
				}
				return;
			case 2:
				mes "[インフォメーション]";
				mes "‐初心者用ポーション‐";
				mes "冒険を始めるノービスたちのために";
				mes "用意されたポーション。";
				mes "^000088HPが少量回復^000000する。";
				mes "重量 : ^7777771^000000";
				break;
			case 3:
				mes "[インフォメーション]";
				mes "‐蝶の羽‐";
				mes "蝶の翼を切り呪術をかけた物。";
				mes "^000088セーブした所にワープする。^000000";
				mes "重量 : ^7777775^000000";
				break;
			}
			break;
		case 7:
		case 9:
		case 16:
			switch(select("確認しない","初心者用ポーション","初心者用青ポーション")){
			case 1:
				if(getarg(1)){
					mes "[インフォメーション]";
					mes "‐獲得アイテムの確認を";
					mes "行いませんでした‐";
				}
				return;
			case 2:
				mes "[インフォメーション]";
				mes "‐初心者用ポーション‐";
				mes "冒険を始めるノービスたちのために";
				mes "用意されたポーション。";
				mes "^000088HPが少量回復^000000する。";
				mes "重量 : ^7777771^000000";
				break;
			case 3:
				mes "[インフォメーション]";
				mes "‐初心者用青ポーション‐";
				mes "駆け出しの冒険者のために";
				mes "用意されたポーション。";
				mes "^000088SPを5回復^000000する。";
				mes "倉庫を含め、一切の移動が出来ない。";
				mes "重量 : ^7777775^000000";
				break;
			}
			break;
		}
		if(!getarg(1)) next;
		return;
	}

OnInit:
	waitingroom "ポリン団 参上！", 0;
	end;
}

//ネコリン
ac_cl_area.gat,64,183,4	script	ネコリン#ac_Necorin	508,{}

//クエスト案内画像表示用NPC
ac_prac_01.gat,228,31,0	script	#ac_prac_01_enter1	139,5,3{
	if(!(AC_HINT_02 & 0x2)){
		//1回目
		cutin "start_038_jp.bmp", 4;
		set AC_HINT_02, AC_HINT_02 | 0x2;
	} else
	if(!(AC_HINT_02 & 0x4)){
		//2回目
		cutin "start_040_jp.bmp", 4;
		set AC_HINT_02, AC_HINT_02 | 0x4;
	} else
	if(!(AC_HINT_02 & 0x8)){
		//3回目
		cutin "start_042_jp.bmp", 4;
		set AC_HINT_02, AC_HINT_02 | 0x8;
	}
	set @help,1;
}
ac_prac_01.gat,228,36,0	script	#ac_prac_01_enter2	139,5,3{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100801)){
		cutin "q_por_mon_01.bmp",4;
	} else
	if(checkquest(100805)){
		cutin "q_por_mon_02.bmp",4;
	} else
	if(checkquest(100810)){
		cutin "q_por_mon_03.bmp",4;
	} else
	if(checkquest(100815)){
		cutin "q_por_mon_04.bmp",4;
	} else
	if(checkquest(100820)){
		cutin "q_por_mon_05.bmp",4;
	} else
	if(checkquest(100822)){
		cutin "q_por_mon_06.bmp",4;
	} else
	if(checkquest(100824)){
		cutin "q_por_mon_07.bmp",4;
	} else
	if(checkquest(100850)){
		cutin "q_por_mon_15.bmp",4;
	}
}
ac_prac_02.gat,110,33,0	duplicate(#ac_prac_01_enter1)	#ac_prac_02_enter1	139,5,3
ac_prac_02.gat,110,39,0	script	#ac_prac_02_enter2	139,5,3,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100830) || checkquest(100840)){
		cutin "q_por_mon_09.bmp",4;
	} else
	if(checkquest(100834)){
		cutin "q_por_mon_11.bmp",4;
	} else
	if(checkquest(100842)){
		cutin "q_por_mon_12.bmp",4;
	} else
	if(checkquest(100852)){
		cutin "q_por_mon_16.bmp",4;
	} else
	if(checkquest(100864) || checkquest(100870)){
		cutin "q_por_mon_20.bmp",4;
	}
}

ac_prac_03.gat,29,345,0	duplicate(#ac_prac_01_enter1)	#ac_prac_03_enter1	139,5,3
ac_prac_03.gat,23,345,0	script	#ac_prac_03_enter2_1	139,4,1,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100860)){
		cutin "q_por_mon_18.bmp",4;
	} else
	if(checkquest(100862) || checkquest(100880)){
		cutin "q_por_mon_19.bmp",4;
	} else
	if(checkquest(100872) || checkquest(100882) || checkquest(100910)){
		cutin "q_por_mon_21.bmp",4;
	} else
	if(checkquest(100884)){
		cutin "q_por_mon_23.bmp",4;
	} else
	if(checkquest(100890)){
		cutin "q_por_mon_25.bmp",4;
	}
}
ac_prac_03.gat,22,331,0	duplicate(#ac_prac_03_enter2_1)	#ac_prac_03_enter2_2	139,1,4
ac_prac_03.gat,34,337,0	duplicate(#ac_prac_03_enter2_1)	#ac_prac_03_enter2_3	139,1,4

ac_prac_04.gat,266,261,0	duplicate(#ac_prac_01_enter1)	#ac_prac_04_enter1	139,5,1
ac_prac_04.gat,266,265,0	script	#ac_prac_04_enter2	139,5,1,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100900)){
		cutin "q_por_mon_28.bmp",4;
	} else
	if(checkquest(100902)){
		cutin "q_por_mon_29.bmp",4;
	} else
	if(checkquest(100904)){
		cutin "q_por_mon_30.bmp",4;
	} else
	if(checkquest(100920)){
		cutin "q_por_mon_33.bmp",4;
	}
}

ac_prac_05.gat,57,170,0	duplicate(#ac_prac_01_enter1)	#ac_prac_05_enter1	139,1,1
ac_prac_05.gat,59,180,0	script	#ac_prac_05_enter2_1	139,5,1,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100932)){
		cutin "q_por_mon_36.bmp",4;
	} else
	if(checkquest(100934)){
		cutin "q_por_mon_37.bmp",4;
	} else
	if(checkquest(100936)){
		cutin "q_por_mon_38.bmp",4;
	}
}
ac_prac_05.gat,61,170,0	duplicate(#ac_prac_05_enter2_1)	#ac_prac_05_enter2_2	139,1,5
ac_prac_05.gat,59,160,0	duplicate(#ac_prac_05_enter2_1)	#ac_prac_05_enter2_3	139,5,1

ac_spec_01.gat,283,26,0	duplicate(#ac_prac_01_enter1)	#ac_spec_01_enter1	139,1,1
ac_spec_01.gat,279,26,0	script	#ac_spec_01_enter2_1	139,5,1,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100826) || checkquest(100836) || checkquest(100876)){
		cutin "q_por_mon_08.bmp",4;
	} else
	if(checkquest(100832)){
		cutin "q_por_mon_10.bmp",4;
	} else
	if(checkquest(100846)){
		cutin "q_por_mon_14.bmp",4;
	} else
	if(checkquest(100856) || checkquest(100866)){
		cutin "q_por_mon_17.bmp",4;
	} else
	if(checkquest(100896) || checkquest(100906)){
		cutin "q_por_mon_27.bmp",4;
	} else
	if(checkquest(100914)){
		cutin "q_por_mon_31.bmp",4;
	} else
	if(checkquest(100924)){
		cutin "q_por_mon_35.bmp",4;
	}
}
ac_spec_01.gat,283,39,0	duplicate(#ac_spec_01_enter2_1)	#ac_spec_01_enter2_2	139,1,5
ac_spec_01.gat,287,26,0	duplicate(#ac_spec_01_enter2_1)	#ac_spec_01_enter2_3	139,5,1

ac_spec_03.gat,100,78,0	duplicate(#ac_prac_01_enter1)	#ac_spec_03_enter1	139,1,5
ac_spec_03.gat,88,68,0	script	#ac_spec_03_enter2	139,5,1,{
	if(!@help) end; //帰りには表示させない
	set @help,0;
	if(checkquest(100892)){
		cutin "q_por_mon_26.bmp",4;
	} else
	if(checkquest(100916) || checkquest(100926)){
		cutin "q_por_mon_32.bmp",4;
	}
}

ac_spec_02.gat,13,144,0	script	#ac_spec_02_sub1	139,1,1,{
	if(checkquest(100844) || checkquest(100854)){
		cutin "q_por_mon_13.bmp",4;
	} else
	if(checkquest(100874)){
		cutin "q_por_mon_22.bmp",4;
	} else
	if(checkquest(100886) || checkquest(100894)){
		cutin "q_por_mon_24.bmp",4;
	} else
	if(checkquest(100922)){
		cutin "q_por_mon_34.bmp",4;
	} else
	if(checkquest(100938)){
		cutin "q_por_mon_39.bmp",4;
	}
}
ac_spec_02.gat,82,68,0	duplicate(#ac_spec_02_sub1)	#ac_spec_02_sub2	139,1,1
ac_spec_02.gat,78,174,0	duplicate(#ac_spec_02_sub1)	#ac_spec_02_sub3	139,1,1
ac_spec_02.gat,105,125,0	duplicate(#ac_spec_02_sub1)	#ac_spec_02_sub4	139,1,1
ac_spec_02.gat,181,141,0	duplicate(#ac_spec_02_sub1)	#ac_spec_02_sub5	139,1,1
ac_spec_02.gat,181,70,0	duplicate(#ac_spec_02_sub1)	#ac_spec_02_sub6	139,1,1
