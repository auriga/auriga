//==============================================================================
// Ragnarok Online Valentine2006 Script     by Blaze
//==============================================================================
//==============================================================
// ブレイド
//	 2～ 4時	プロンテラ←	クエスト△	居眠りルート
//	 4～ 7時	プロンテラ↓	クエスト△	居眠りルート
//	 8～10時	プロンテラ南	クエスト○	ゼロピールート
//	12～15時	プロンテラ南西	クエスト○	カカオ販売ルート
//	15～17時	プロンテラ←	クエスト○	詩ルート
//	17～19時	プロンテラ↓	クエスト×	詩ルート
//	21～23時	プロンテラ南	クエスト○	ゼロピールート
// Function
//	getarg(0)	最初のイベント内容
//		0=ロックの参照渡し専用
//		1=回復1	2=回復2	3=紹介	4=販売
//	getarg(1)	時刻
//		1=昼	2=夜
//	getarg(2)	途中のイベント内容
//		1=居眠りルート
//		2=ゼロピールート
//		3=詩ルート
//		4=カカオ販売ルート
//	getarg(3)	クエスト可否
//		1=可能	2=不可	3=男性のみ可
//--------------------------------------------------------------

function	script	ValentineBreid	{
	if(getarg(0)==0)
		return 'flag;	//値を渡して終了
	if((Weight*100/MaxWeight) >= 90) {
		mes "所持アイテムの重量が多いため";
		mes "アイテムを受けとることができません-";
		mes "-所持アイテムを減らしてから、再度";
		mes "話しかけてください-";
		close;
	}
	if('flag) {	//複数人同時アタッチ防止
		mes "何やら忙しそうだ";
		mes "後でまた声を掛けてみよう";
		close;
	}
	set 'flag,1;
	initnpctimer "V_BreidTimer";
	switch(QUEST_VALENTINE1) {
		case 0:
			function PatternA;
			PatternA getarg(0),getarg(1);
			break;
		case 1:
			function PatternB;
			PatternB;
			break;
		case 2:
		case 3:
		case 4:
			function PatternC;
			PatternC getarg(0);
			break;
		case 5:
			function PatternD;
			PatternD 0,0,0,getarg(3);
			break;
		case 6:
			function PatternE;
			PatternE 0,0,0,getarg(3);
			break;
		case 7:
			function PatternF;
			PatternF;
			break;
		case 8:
			function PatternG;
			PatternG;
			break;
		default:
			function PatternH;
			PatternH 0,0,getarg(2);
			break;
		case 17:
			function PatternI;
			PatternI;
			break;
		case 18:
			function PatternJ;
			PatternJ;
			break;
		case 19:
			function PatternK;
			PatternK;
			break;
		case 20:
			function PatternL;
			PatternL;
			break;
	}
	set 'flag,0;
	close2;
	cutin "dummy",255;
	return;

	function PatternA {	//case0
		switch(getarg(0)) {
		case 1:
		case 2:
			cutin "v_breid05",2;
			if(getarg(1)==1) {
				mes "[ブレイド]";
				mes "ん……呼んだか？";
				next;
				mes "[ブレイド]";
				mes "ふぁぁ……";
				mes "とりあえず、回復してやろう。";
			}
			else {
				mes "[ブレイド]";
				mes "こんな時間まで、ご苦労だな。";
				next;
				mes "[ブレイド]";
				mes "相当疲れているようだが……";
				mes "とりあえず、回復してやろう。";
			}
			next;
			misceffect 207,"";
			percentheal 100,0;
			mes "["+strcharinfo(0)+"]";
			mes "え……？";
			mes "何をするって？";
			mes "うわっ!?";
			mes " ";
			mes "-明るい光とともに体力が回復した-";
			next;
			if(getarg(0)==1) {
				mes "[ブレイド]";
				mes "経験を積むことや、";
				mes "富や名声を得ることは、";
				mes "冒険者として重要なことかもしれない。";
				mes "だが、根を詰めすぎじゃないか？";
				next;
				mes "[ブレイド]";
				mes "体を壊してしまっては、今までの努力が";
				mes "すべて無駄になってしまうぞ。";
			}
			else {
				mes "[ブレイド]";
				mes "少しは元気になったか？";
			}
			next;
			if(select("だ、誰？　いきなり何を!?","あ、ありがとう")==2) {
				mes "[ブレイド]";
				mes "礼はいいさ。";
				mes "はぁ～誰だってこんな時間にまで、";
				mes "外へ出て働きたくないよなぁ……";
				mes "家でゆっくり休みたいもんだぜ。";
				next;
				cutin "v_breid02",2;
				mes "[ブレイド]";
				mes "さぁ……もう安め。";
				mes "あまり無理はするなよ。";
				set QUEST_VALENTINE1,2;
				return;
			}
			cutin "v_breid03",2;
			if(getarg(0)==1) {
				mes "[ブレイド]";
				mes "オレは、ここを警備している騎士だ。";
				mes "人が好意で回復してやったというのに、";
				mes "その態度はなんだ!?";
				mes "礼の一つも言えないのか!?";
			}
			else {
				mes "[ブレイド]";
				mes "ん、何だ？　疲れているようだから";
				mes "回復してやったんだが？";
			}
			next;
			if(select("余計なお世話です","なんだ、警備のおじさんか……")==1) {
				mes "[ブレイド]";
				mes "余計なお世話だと!?";
				mes "オレが体力を回復してやったことで、";
				mes "オマエに何か迷惑かけたか？";
				mes "オレは自分の任務を果たしただけだ。";
				next;
				mes "[ブレイド]";
				mes "ちょっとお節介を焼いただけで、";
				mes "そう怒られては敵わんな。";
				mes "今後オマエの手助けは一切しない。";
				mes "一人でなんとかするんだな。";
			}
			else {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "お……おじさん!?";
				mes "おじさんだとぉぉぉぉ!?";
				mes "この、オレが……おじさん!?";
				next;
				mes "[ブレイド]";
				mes "ブレイドと呼べ！";
				mes "おじさんとは何だ、おじさんとは！";
				mes "まったく……";
				mes "オマエみたいに失礼な奴がいると、";
				mes "警備の仕事も気疲れしちまうぜ。";
				next;
				mes "[ブレイド]";
				mes "まぁいい。休暇が終わったら、";
				mes "こんな街とはおさらばだしな！";
				mes "さぁ、さっさと消えろ！";
			}
			set QUEST_VALENTINE1,1;
			return;
		case 3:
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "今日も平和だ……異常なし！";
			mes "ルーンミッドガッツ王国！";
			mes "万歳!!";
			next;
			menu "誰ですか……？",-;
			mes "[ブレイド]";
			mes "よくぞ聞いてくれた！　オレはな、";
			mes "さすらいの冒険者だ!!";
			mes "……";
			next;
			cutin "v_breid03",2;
			mes "[ブレイド]";
			mes "ええぃ、そう睨むなよ！";
			mes "オレだってなぁ、やりたくて";
			mes "やってるわけじゃないんだぞ！";
			mes "でもな、生活のためには仕事を";
			mes "しなきゃいけないんだ！　しかし、";
			mes "なんでオレがこんなことを……!!";
			next;
			misceffect 207,"";
			percentheal 100,0;
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "はぁ……オマエに八つ当たりしても";
			mes "しょうがないか。";
			mes "ちなみに、今キャンペーン中で、";
			mes "無料で回復してるんだ。";
			mes "ケガでもしたら、気軽に来るといい。";
			set QUEST_VALENTINE1,2;
			return;
		case 4:
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "カカオ～カカオ～安いよっ！";
			mes "カカオはいりませんか～？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "カカオ……？";
			next;
			cutin "v_breid06",2;
			mes "[ブレイド]";
			mes "ヘイ、お客さん!!　カカオ買うかい？";
			next;
			if(select("あなた……騎士じゃないんですか？","いくらですか？")==1) {
				cutin "v_breid01",2;
				mes "[ブレイド]";
				mes "……";
				mes "アルバイトだよ。";
				mes "ちょっと金が必要でな……";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "プロンテラ騎士団は、そんなに";
				mes "貧しいんですか……？";
				next;
				mes "[ブレイド]";
				mes "いや、そういうわけじゃないが……";
				mes "ちょっと人には言えない";
				mes "事情があってね。";
				mes "とにかく金が必要なんだ。";
				mes "あ～そうそう。オレがアルバイトを";
				mes "してること、騎士団に言うなよ？";
				next;
				if(select("理由を知りたいです","騎士団に報告します")==1) {
					mes "[ブレイド]";
					mes "また会う機会があったら、その時に";
					mes "教えてあげるよ。";
					mes "今はアルバイト中だからな。";
				}
				else {
					cutin "v_breid03",2;
					mes "[ブレイド]";
					mes "おい……オマエな……";
					mes "ちっ、勝手にしろ!!";
				}
				set QUEST_VALENTINE1,2;
				break;
			}
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "カカオは、非常食としても、色々な";
			mes "食べ物の原料としても使用される、";
			mes "とても貴重なものだ。";
			mes "単価300Zeny！";
			mes "5つセットで1500Zenyだ。";
			next;
			mes "[ブレイド]";
			mes "しかし、な、何と！　今なら特別に、";
			mes "5つセット1499Zenyで販売中!!";
			next;
			if(select("ちょっと考える","買います")==1) {
				mes "[ブレイド]";
				mes "押し売りするつもりはないから、";
				mes "無理に買う必要はないよ。";
				mes "オレもただのアルバイトだしね。";
			}
			else if(Zeny < 1499) {
				cutin "v_breid03",2;
				mes "[ブレイド]";
				mes "ん……Zenyが足りないみたいだね。";
				mes "悪いけど、値引きすることは";
				mes "できないんだ。";
			}
			else {
				cutin "v_breid02",255;
				mes "[ブレイド]";
				mes "はいよ、カカオ5つ。";
				mes "毎度～！　今日も売れ行き好調だ～！";
				mes "さぁて、そろそろ警備の準備するかな。";
				set Zeny,Zeny-1499;
				getitem 7182,5;
			}
			set QUEST_VALENTINE1,2;
			return;
		}
	}

	function PatternB {	//case1
		cutin "v_breid03",2;
		mes "[ブレイド]";
		mes "……";
		mes "この前の失礼極まりない奴か。";
		mes "今更オレに、何か用か？";
		next;
		if(select("仲直りしたくて……","いや、何でもない")==2) {
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "フン……そうかい。";
			mes "なら結構だ。";
			return;
		}
		cutin "v_breid05",2;
		mes "[ブレイド]";
		mes "今更仲直りだと!?";
		mes "キミにとってオレは、所詮";
		mes "人生における幾多の出会いの一つだ。";
		mes "それをわざわざ仲直りだと!?";
		mes "冷やかしなら、帰れ!!";
		next;
		mes "[ブレイド]";
		mes "……それとも、";
		mes "本気で仲直りをしたいと言うなら、";
		mes "何か誠意を見せてもらおうじゃないか。";
		next;
		if(select("どうすれば？","いやなこった")==2) {
			mes "[ブレイド]";
			mes "フン……そうかい。";
			mes "なら結構だ。";
			return;
		}
		mes "[ブレイド]";
		mes "そうだな……せめて";
		mes "ゼロピーの一つでもくれたら、";
		mes "誠意があると認めてやろう。";
		mes "さぁ、どうなんだ？";
		next;
		if(countitem(909)) {
			if(select("あげる","あげない")==1) {
				mes "["+strcharinfo(0)+"]";
				mes "ゼロピーなら持ってるけど……";
				mes "でも、何故ゼロピーなんかを？";
				next;
				mes "[ブレイド]";
				mes "ここで警備してても、退屈だからな。";
				mes "あんまり暇でつい腹が減るから、";
				mes "おやつにゼロピーでも食おうかな～と。";
				next;
				menu "食べる!?",-;
				cutin "v_breid06",2;
				mes "[ブレイド]";
				mes "何をそんなに驚いているんだ？";
				mes "ゼロピーを食べたことないのか？";
				mes "オレはよく食べてたぞ。";
				mes "なんとなく甘くてな……";
				next;
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "みんな数年前は、";
				mes "貧しい時などおやつ代わりに";
				mes "ゼロピーを食べたもんだ。";
				next;
				mes "[ブレイド]";
				mes "……いかにも意外って顔だな。";
				mes "最近の若者は、貧しい時代を";
				mes "知らないんだな……";
				delitem 909,1;
				set QUEST_VALENTINE1,2;
				return;
			}
		}
		mes "["+strcharinfo(0)+"]";
		mes "ゼロピー？　持ってないけど……";
		mes "でも、何故ゼロピーなんかを？";
		next;
		cutin "v_breid06",2;
		mes "[ブレイド]";
		mes "ここで警備してても、退屈だからな。";
		mes "あんまり暇でつい腹が減るから、";
		mes "おやつにゼロピーでも食おうかな～と。";
		next;
		menu "え、食べるんですか!?",-;
		mes "[ブレイド]";
		mes "何をそんなに驚いているんだ？";
		mes "ゼロピーを食べたことないのか？";
		mes "オレはよく食べてたぞ。";
		mes "なんとなく甘くてな……";
		next;
		cutin "v_breid05",2;
		mes "[ブレイド]";
		mes "みんな数年前は、";
		mes "貧しい時などおやつ代わりに";
		mes "ゼロピーを食べたもんだ。";
		next;
		mes "[ブレイド]";
		mes "……いかにも意外って顔だな。";
		mes "フン……所詮最近の若者には、";
		mes "貧しい時代なんて理解できないんだな。";
		mes "用は済んだ……帰れ。";
		return;
	}

	function PatternC {	//case2,3,4
		switch(getarg(0)) {
		case 1:
			if(rand(3)==0) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "平和だな……しかし眠い。";
				mes "何故こんな時間にまで、";
				mes "働かなきゃいかんのだ!?";
				mes "完全に寝不足だ……";
				next;
				mes "[ブレイド]";
				mes "アンタもよく頑張るな。";
				mes "何のために、そう頑張ってるんだ？";
				next;
				if(select("ええと、それは……","一攫千金を狙って!!")==1) {
					cutin "v_breid06",2;
					mes "[ブレイド]";
					mes "ウガァァァァ～～～!!";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "うわっ、な……何!?";
					next;
					cutin "v_breid05",2;
					mes "[ブレイド]";
					mes "あ、すまんすまん。";
					mes "驚かすつもりじゃなかったんだが……";
					mes "いやぁ、あんまり暇でさ……";
					mes "いっそ、何か問題でも起きないかねぇ。";
					next;
					mes "[ブレイド]";
					mes "こんな時間に外を出歩く奴がいなきゃ、";
					mes "オレはこんな所で死ぬほど退屈しながら";
					mes "警備する必要もないんだがな。";
					next;
					mes "^4A4AFF-あなたに対するブレイドの好感度が";
					mes "少し上昇しました-^000000";
					set QUEST_VALENTINE1,QUEST_VALENTINE1+1;
					return;
				}
				mes "[ブレイド]";
				mes "……アルベルタに、ある商人がいてな。";
				mes "ゼロピーを集めて、必死に金を貯めた。";
				mes "そして、ダイヤモンドを掘り当てて";
				mes "一攫千金を夢見て、コモドへ旅立った。";
				next;
				mes "[ブレイド]";
				mes "……結果は悲惨なものだった。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……何故そんな話をするんです？";
				next;
				mes "[ブレイド]";
				mes "一攫千金を狙うのはいいが、";
				mes "危険を伴うぞってことだ。";
				mes "一度失敗すると、やり直すのは";
				mes "大変だからな。";
				next;
				cutin "v_breid02",2;
				mes "[ブレイド]";
				mes "まぁキミは、こんな時間まで一生懸命";
				mes "頑張ってるし、心配ないとは思うがな。";
				return;
			}
			break;	//ポーション鮮度ルートへ
		case 2:
			if(rand(3)==0) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "なぁ、ゼロピー持ってないか？";
				mes "あったら、一つくれないか？";
				next;
				if(countitem(909)<1) {
					menu "いえ、持ってません",-;
					cutin "v_breid06",2;
					mes "[ブレイド]";
					mes "なんだ、ゼロピーすら持ってないのか？";
					mes "世代の違いなのか……";
					return;
				}
				if(select("あげない","あげる")==1) {
					mes "["+strcharinfo(0)+"]";
					mes "ゼロピーなんて、持ってませんよ。";
					mes "それに、何に使うんですか？";
					next;
					mes "[ブレイド]";
					mes "何って……食べるんだが？";
					mes "たまに食べるとうまいぞ。";
					mes "なんとなく甘みがあってな……";
					next;
					menu "食べる!?　よっぽど貧乏なんですね!?",-;
					cutin "v_breid03",2;
					mes "[ブレイド]";
					mes "……";
					mes "貧乏で悪かったな……";
					return;
				}
				mes "["+strcharinfo(0)+"]";
				mes "ゼロピーなら持ってるけど……";
				mes "でも、何故ゼロピーなんかを？";
				next;
				mes "[ブレイド]";
				mes "ここで警備してても、退屈だからな。";
				mes "あんまり暇でつい腹が減るから、";
				mes "おやつにゼロピーでも食おうかな～と。";
				next;
				menu "食べる!?",-;
				cutin "v_breid06",2;
				mes "[ブレイド]";
				mes "何をそんなに驚いているんだ？";
				mes "ゼロピーを食べたことないのか？";
				mes "オレはよく食べてたぞ。";
				mes "なんとなく甘くてな……";
				next;
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "みんな数年前は、";
				mes "貧しい時などおやつ代わりに";
				mes "ゼロピーを食べたもんだ。";
				next;
				mes "[ブレイド]";
				mes "……いかにも意外って顔だな。";
				mes "最近の若者は、貧しい時代を";
				mes "知らないんだな……";
				delitem 909,1;
				set QUEST_VALENTINE1,1;
				return;
			}
			break;	//回復ルートへ
		case 3:
			if(rand(3)==0) {
				cutin "v_breid01",2;
				mes "[ブレイド]";
				mes "はぁ～退屈だ……";
				mes "そうだ、ポエムでも作るか？";
				next;
				mes "[ブレイド]";
				mes "方法は簡単！";
				mes "各々があらかじめ文章を作り、";
				mes "それを交互につなげるんだ。";
				next;
				mes "[ブレイド]";
				mes "めちゃくちゃなのが";
				mes "出来るかもしれないが、";
				mes "結構面白いぞ？";
				mes "どうだ、やってみるか？";
				next;
				if(select("ええ、ぜひやりましょう","馬鹿馬鹿しくてやる気が……")==2) {
					cutin "v_breid03",2;
					mes "[ブレイド]";
					mes "やってもみないで馬鹿馬鹿しいとは、";
					mes "酷いじゃないか！";
					return;
				}
				mes "[ブレイド]";
				mes "それじゃ、先に2つ文章を作ってみて。";
				mes "まず一番目の……";
				next;
				input '@poem1$;
				mes "["+strcharinfo(0)+"]";
				mes "一番目は……";
				mes '@poem1$+ "で。";
				next;
				input '@poem2$;
				mes "["+strcharinfo(0)+"]";
				mes "一番目は……";
				mes '@poem1$+ "で、";
				mes "二番目は……";
				mes '@poem2$+ "！";
				mes "どうですか？";
				next;
				mes "[ブレイド]";
				mes "おれの方もできたぞ。";
				mes "よーし、つなげてみるか。";
				next;
				switch(rand(6)) {
				case 0:
					mes "^218C21ポリンポリン！違うぜポポリン!!^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21ポリンポリン！違うぜサンタポリン！^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				case 1:
					mes "^218C21ポッポッポッポーションピッチャー♪^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21極上回復！　ポーションピッチャー♪^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				case 2:
					mes "^218C21オレの心に微かに残る～♪^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21プライドを捨て～られなくて～♪^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				case 3:
					mes "^218C21団長殿は仰せになる！警備！警備！^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21昼夜警備のおかげで～世界は平和～!!^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				case 4:
					mes "^218C21腹ペコ！　腹ペコ！　腹ペコペコ！^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21金も無いぜ！　腹ペコペコ!!^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				case 5:
					mes "^218C21月日は～常に過ぎ行く～♪^000000";
					mes "^4A4AFF" +'@poem1$+ "^000000";
					mes "^218C21アルデバランの水車のように～!!^000000";
					mes "^4A4AFF" +'@poem2$+ "^000000";
					break;
				}
				next;
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "……何か……";
				mes "オレらアホだな……";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……うん……";
				mes "アホだね……";
				set QUEST_VALENTINE1,QUEST_VALENTINE1+1;
				return;
			}
			break;	//ポーション鮮度ルートへ
		case 4:
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "いらっしゃい！　カカオ買うかい？";
			next;
			if(select("買います","結構です")==2) {
				mes "[ブレイド]";
				mes "押し売りするつもりはないから、";
				mes "無理に買う必要はないよ。";
				mes "ところで……カカオって、このまま";
				mes "食べてもうまいのかなぁ……";
				return;
			}
			mes "[ブレイド]";
			mes "5つセットで1499Zenyだよ！";
			mes "いいね？";
			next;
			if(select("何で5つセットなんですか？","はい")==1) {
				mes "[ブレイド]";
				mes "そりゃ、バラ売りは面倒だし……";
				mes "……";
				mes "不満があるなら、買わなくていいさ。";
				return;
			}
			if(Zeny < 1499) {
				cutin "v_breid03",2;
				mes "[ブレイド]";
				mes "ん……Zenyが足りないみたいだね。";
				mes "悪いけど、値引きすることは";
				mes "できないんだ。";
				return;
			}
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "はいよ、カカオ5つ。";
			mes "毎度～！　今日も売れ行き好調だ～！";
			set Zeny,Zeny-1499;
			getitem 7182,5;
			set QUEST_VALENTINE1,QUEST_VALENTINE1+1;
			return;
		}
		//回復・ポーション鮮度ルートここから
		if(getarg(0)==3) {
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "少し疲れているようだが……";
			mes "回復してやろうか？";
			next;
			if(select("ええ、お願いします","いいえ、大丈夫です")==1) {
				mes "[ブレイド]";
				mes "ほらよっと。";
				mes "あまり無理をするなよ。";
				misceffect 207,"";
				percentheal 100,0;
			}
			else {
				mes "[ブレイド]";
				mes "無料だから遠慮することないぞ？";
				mes "必要なら、いつでも言ってくれ。";
			}
			return;
		}
		cutin "v_breid01",2;
		mes "[ブレイド]";
		mes "回復してほしい時は、";
		mes "いつでも言ってくれ。";
		mes "ポーションで回復してやるからな。";
		mes "鮮度が落ちる前に使わないと、";
		mes "もったいないからな。";
		next;
		set @menu,select("鮮度って？","回復してほしい");
		mes "[ブレイド]";
		mes "ポーションに鮮度があるのを";
		mes "知らないだろう？";
		mes "古くなっても、味が変わったり、";
		mes "飲んで腹を壊すものではないが、";
		mes "効果が微妙に落ちるもんだ。";
		next;
		if(@menu==1) {
			mes "[ブレイド]";
			mes "なるべく鮮度が高い最良の状態で";
			mes "飲みたいもんだな。";
			mes "まぁ、違いは微々たるものだし、";
			mes "それ程気にする必要もないだろうが……";
			next;
			cutin "v_breid02",2;
			mes "[ブレイド]";
			mes "しかし、絶体絶命の瞬間!!";
			mes "最後の一つのポーションを飲んだら";
			mes "古くて効果がいまいちだったりすると、";
			mes "結構泣けるもんだ。";
		}
		else {
			cutin "v_breid02",2;
			mes "[ブレイド]";
			mes "さ、こいつは鮮度がめちゃ高い";
			mes "最上級のポーションだ。";
			mes "これくらい鮮度が高い良品だと、";
			mes "使った価値あり!!　って感じるなぁ。";
			misceffect 207,"";
			percentheal 100,0;
		}
		return;
	}

	function PatternD {	//case5
		if(getarg(3)==3 && QUEST_VALENTINE1_FLAG==1) {
			cutin "v_breid04",2;
			mes "[ブレイド]";
			mes "……";
			mes "その顔……";
			mes "この前オレが寝惚けて殴ったこと？";
			next;
			mes "[ブレイド]";
			mes "ごめんね。寝てる時に触られると、";
			mes "無意識に体が反応しちゃうんだ。";
			next;
			if(select("気にしないでください","気をつけてくださいよ")==1) {
				mes "["+strcharinfo(0)+"]";
				mes "先にいたずらしたのは私だから。";
				mes "むしろ私が謝らなくては……";
				next;
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そうか。じゃ、謝ってもらおう。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……";
				next;
				cutin "v_breid02",2;
				mes "[ブレイド]";
				mes "冗談、冗談だって。";
				mes "そう、ムッとするな!!";
				mes "あ～ところで、後で街の南西にある";
				mes "広場まで来てくれないか？";
				mes "ベンチが並んでる所な。";
				next;
				mes "^4A4A4A-あなたに対するブレイドの親密度が";
				mes "上昇しました-^000000";
				set QUEST_VALENTINE1,6;
				set QUEST_VALENTINE1_FLAG,2;
				return;
			}
			cutin "v_breid06",2;
			mes "["+strcharinfo(0)+"]";
			mes "無意識だからといって、";
			mes "許されるものじゃないでしょ！";
			mes "もっと周りに気をつけてくださいよ！";
			mes "そんな無神経だと、";
			mes "友達もいないんじゃないの!?";
			next;
			cutin "v_breid03",2;
			mes "[ブレイド]";
			mes "なっ……何だと!?";
			mes "人がわざわざ頭を下げて";
			mes "謝ってやってるのに!!";
			next;
			misceffect 2,"";
			percentheal -50,0;
			mes "[ブレイド]";
			mes "もう一度言ってみろ!!";
			next;
			misceffect 2,"";
			percentheal -40,0;
			mes "[ブレイド]";
			mes "オレが無神経だとっ!?";
			mes "ちょっと寝惚けたくらいで、";
			mes "そこまで言われて黙ってられるか!!";
			mes "さぁ、もう一度言ってみろ!!";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "いたっ……いたたっ……!!";
			mes "やめて……やめてください!!";
			mes "私が悪かった、言い過ぎました！";
			mes "謝るから、やめてください！";
			next;
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "ちっ……";
			mes "……";
			mes "ようやく理解したか。";
			next;
			misceffect 207,"";
			percentheal 100,0;
			mes "[ブレイド]";
			mes "……治療してやる……";
			mes "言っておくが、これは好意じゃないぞ。";
			mes "仕事だからしょうがなく、回復して";
			mes "やるんだ。勘違いするなよ。";
			return;
		}
		if(getarg(3)==3 && QUEST_VALENTINE1_FLAG==0 && rand(3)==0) {
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "……………";
			mes "……………";
			next;
			if(select("声をかける","様子をみる")==2) {
				mes "^4A4AFF-ブレイドの目の前で手を振ってみたが";
				mes "反応がない-";
				mes "-目を開いたまま";
				mes "居眠りをしているようだ-^000000";
				next;
				if(select("髪の毛を抜いてみる","声をかける")==1) {
					mes "^4A4AFF-ブレイドの髪の毛の中で、";
					mes "長めの髪の毛を一本しっかりつまみ……";
					mes "一気に抜いてみる-^000000";
					next;
					cutin "v_breid03",2;
					mes "[ブレイド]";
					mes "いてっ!! な、何をするんだ!?";
					mes "暴力反対！";
					mes "文句があるなら、口で言え！";
					if(Sex==0)
						return;
					next;
					misceffect 2,"";
					percentheal -50,0;
					mes "[ブレイド]";
					mes "こんなふうにな!!";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "わ、私が悪かったです！";
					mes "ぼ、暴力反対！　その拳を";
					mes "下ろしてください！";
					next;
					cutin "v_breid06",2;
					mes "[ブレイド]";
					mes "ん……おお？";
					mes "その顔、どうかしたのか？";
					mes "ケガしてるぞ？";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "あなたが殴ったんでしょ!!";
					mes "たった今！　その拳で！";
					mes "暴力反対とか言いながら、";
					mes "私の顔を殴ったのはどこの誰ですか!?";
					next;
					misceffect 207,"";
					percentheal 100,0;
					cutin "v_breid04",2;
					mes "[ブレイド]";
					mes "ん、なんだオマエかぁ……";
					mes "寝惚けてたもんでな……";
					mes "んまぁ、寝てる所を不用意に";
					mes "近づく奴が悪いんだぞ？";
					mes "治療してやるから気にするな。";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "……いくら寝惚けてたからって、";
					mes "いきなり殴るなんて……";
					next;
					cutin "v_breid03",2;
					mes "[ブレイド]";
					mes "ええい、うるさい！";
					mes "回復したら、さっさとモンスターでも";
					mes "狩りに行ってこい！";
					set QUEST_VALENTINE1_FLAG,1;
					return;
				}
			}
			mes "["+strcharinfo(0)+"]";
			mes "何をしているんですか？";
			next;
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "あぁ……キミか。";
			mes "今日もまったく異常なしっ！";
			mes "もう平和で平和で……";
			mes "眠くなってきてさ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "毎日そこで警備してれば、飽きる";
			mes "でしょうね……たまには休んだら？";
			next;
			mes "[ブレイド]";
			mes "言ってなかったか？";
			mes "体調崩して寝込んだ団員がいてさ。";
			mes "休暇中だってのに、そいつの代わりに";
			mes "働かなきゃいけないんだ。";
			mes "ま、休暇が終わったら、自分の";
			mes "持ち場に戻ることになるけどね。";
			next;
			cutin "v_breid04",2;
			mes "[ブレイド]";
			mes "あと数日の辛抱だから、大丈夫さ。";
			mes "心配してくれてありがとう。";
			return;
		}
		cutin "v_breid05",2;
		mes "[ブレイド]";
		mes "はぁ～平和で、退屈で、眠い……";
		mes "グググゥ～";
		mes "……腹も減る……";
		next;
		if(select("ゼロピーいりますか？","私は減ってませんが……")==1) {
			mes "[ブレイド]";
			mes "いらない。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "人が好意で言ってるのに！";
			next;
			mes "[ブレイド]";
			mes "相当眠いので、勤務が終わりしだい";
			mes "倒れるように寝るつもりだ。";
			mes "これでもかってくらい爆睡してやる！";
			mes "もう火事だろうが事件だろうが、";
			mes "絶っっっ対に起きないからな。";
			next;
			mes "[ブレイド]";
			mes "だから、勤務時間が終わるまであと少し";
			mes "じっとこのまま何もせずに耐える!!";
		}
		else {
			cutin "v_breid03",2;
			mes "[ブレイド]";
			mes "……";
			mes "オマエは、疲れてもなく、";
			mes "眠くもなく、腹も空いてもいない……";
			next;
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "それに……自由に歩き回れていいね。";
			mes "オレも騎士を辞めて冒険しようかなぁ。";
			next;
			mes "[ブレイド]";
			mes "まぁ、もう少しでこの勤務も終わりか。";
			mes "平和なプロンテラとはおさらばだ。";
			mes "元の持ち場に戻らなくてはな。";
			mes "それに、アルバイトも終わりか……";
			next;
			menu "アルバイト？",-;
			mes "[ブレイド]";
			mes "ああ……";
			mes "この警備の勤務は仲間の代行でしてる";
			mes "だけだから、手当ては出ないんだ。";
			next;
			mes "[ブレイド]";
			mes "アルバイトでもしなけりゃ、";
			mes "生活が苦しくてさ。";
			mes "……って、オレ、何でこんな話を";
			mes "してるんだ……？";
		}
		set QUEST_VALENTINE1,6;
		return;
	}

	function PatternE {	//case6
		switch(getarg(3)) {
		case 1:
			if(QUEST_VALENTINE1_FLAG==2) {
				set QUEST_VALENTINE1,7;
				set QUEST_VALENTINE1_FLAG,0;
				getitem 573,1;
				getitem 7182,5;
				cutin "v_breid01",2;
				mes "[ブレイド]";
				mes "おう！　待っていた!!";
				mes "まぁまぁ、とりあえずこれ飲め！";
				mes "んでもって、これを持って！";
				next;
				mes "[ブレイド]";
				mes "よし、飲んだな。";
				mes "それじゃ、飲み物代として、";
				mes "そのカカオをアルベルタまで";
				mes "配達よろしく！";
				next;
				menu "……そのために呼んだの？",-;
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そうだ。";
				mes "何だぁ？　他に何か期待してたのか？";
				mes "自分で届けようと思ったんだが、";
				mes "警備中だろ……？";
				mes "団長の目を盗んで抜け出すことが、";
				mes "なかなかできなくってさ……";
				next;
				mes "[ブレイド]";
				mes "^4A4AFFアルベルタ^000000の^4A4AFFショコラ=バシニオ^000000だ。";
				mes "頼むぞ。";
				return;
			}
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "あのさ……すまないが、";
			mes "各地で集めた品物を、";
			mes "アルベルタまで配達を";
			mes "頼みたいんだ。";
			next;
			mes "[ブレイド]";
			mes "バイトで配達をしているんだが、";
			mes "アルベルタまで到底行けないからなぁ。";
			next;
			if(select("いいですよ","忙しいです")==2) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そうか……";
				mes "困ったな、どうしよう……";
				return;
			}
			mes "[ブレイド]";
			mes "配達品は、カカオ5つだ。受取人は、";
			mes "アルベルタのショコラ=バシニオだ。";
			next;
			set QUEST_VALENTINE1,7;
			getitem 7182,5;
			mes "[ブレイド]";
			mes "品物の代金はもうもらっているから、";
			mes "ただ、届けてくれればいい。";
			next;
			mes "[ブレイド]";
			mes "^4A4AFFアルベルタ^000000の^4A4AFFショコラ=バシニオ^000000だ。";
			mes "頼むぞ。";
			return;
		case 2:
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "^4A4AFF" +'name$+ "^000000という";
			mes "女の子を知らないか？";
			mes "こないだ退屈しのぎに西門まで";
			mes "送ってあげた子なんだが。";
			mes "……いや、すまん。こんな話を";
			mes "するつもりはなかったんだがな。";
			return;
		case 3:
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "それではまた、プロンテラで会おう。";
			close2;
			set 'flag,0;
			cutin "v_breid01",255;
			return;
		}
	}

	function PatternF {	//case7
		cutin "v_breid05",2;
		mes "[ブレイド]";
		mes "^4A4AFFアルベルタ^000000の^4A4AFFショコラ=バシニオ^000000だ。";
		mes "配達する物は^4A4AFFカカオ5つ^000000。";
		mes "頼むぞ。";
		return;
	}

	function PatternG {	//case8
		cutin "v_breid01",2;
		mes "[ブレイド]";
		mes "お、ご苦労だったな。";
		mes "ちゃんと届けてくれたか？";
		next;
		switch (select("手数料としてもらったチョコを渡す","もらったチョコを食べたと言う")) {
		case 1:
			if(countitem(558)<1) {
				cutin "v_breid05",2;
				mes "["+strcharinfo(0)+"]";
				mes "あ、あれ？　おかしいな……";
				mes "配達手数料としてもらったはずの";
				mes "チョコレートがなくなっちゃった!?!";
				mes "う～ん、どこにいったんだろう……";
				next;
				cutin "v_breid02",2;
				mes "[ブレイド]";
				mes "配達したのはキミだから、手数料なら";
				mes "キミが食べて良かったんだが……";
				mes "なくしちゃったのか。残念だな。";
				break;
			}
			mes "[ブレイド]";
			mes "ん……何だ？　チョコレート？";
			mes "くれるのか？";
			next;
			if(select("手数料としてもらったと言う","私の気持ちだと言う")==1) {
				mes "["+strcharinfo(0)+"]";
				mes "配達先は、チョコレートのお店でした。";
				mes "配達手数料にともらったので、";
				mes "食べてください。";
				next;
				mes "[ブレイド]";
				mes "配達したのはキミだから、";
				mes "配達手数料ならキミが食べていいよ。";
				break;
			}
			if(Sex==0) {
				mes "[ブレイド]";
				mes "え……オ、オレに……？";
				next;
				delitem 558,1;
				set QUEST_VALENTINE1,QUEST_VALENTINE1+3;
				cutin "v_breid04",2;
				mes "[ブレイド]";
				mes "あ、ありがとう。";
				next;
				mes "^4A4A4A-あなたに対するブレイドの好感度が";
				mes "大幅に上昇しました-^000000";
				if('name$=="" || rand(3)==0)
					set 'name$,strcharinfo(0);
			}
			else {
				cutin "v_breid04",2;
				mes "[ブレイド]";
				mes "なっ……";
				mes "じょ、冗談だろ!?";
				mes "オレは……そういう趣味はないぞ!!";
				set QUEST_VALENTINE1,9;
			}
			return;
		case 2:
			mes "["+strcharinfo(0)+"]";
			mes "配達先は、チョコレートのお店でした。";
			mes "配達手数料にと一つもらったので、";
			mes "食べさせて頂きました。";
			next;
			cutin "v_breid06",2;
			mes "[ブレイド]";
			break;
		}
		mes "カカオはチョコレートの原料なんだ。";
		mes "知らなかった？";
		next;
		cutin "v_breid02",2;
		mes "[ブレイド]";
		mes "そういや、チョコレートが大好きな";
		mes "幼馴染がいたな。なんか思い出したら、";
		mes "久しぶりに会いたくなったな。";
		mes "とにかく、配達ありがとう。";
		next;
		mes "^4A4A4A-あなたに対するブレイドの親密度が";
		mes "上昇しました-^000000";
		set QUEST_VALENTINE1,9;
		return;
	}

	function PatternH {	//case9～16
		switch(getarg(2)) {
		case 1:
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "^4A4AFF" +'name$+ "^000000という";
			mes "女の子を知らないか？";
			mes "こないだ退屈しのぎに西門まで";
			mes "送ってあげた子なんだが。";
			mes "……いや、すまん。こんな話を";
			mes "するつもりはなかったんだがな。";
			return;
		case 2:
		case 3:
			cutin "v_breid01",2;
			if(rand(3)) {
				mes "[ブレイド]";
				mes "ポーションピッチャー！";
				misceffect 207,"";
				percentheal 100,0;
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……";
				next;
				mes "[ブレイド]";
				mes "…………";
				mes "……";
				next;
				mes "[ブレイド]";
				mes "あ～暇だ、暇だ！　暇なんだよ!!";
				mes "もうこんな勤務うんざりなんだよ!!";
				return;
			}
			mes "[ブレイド]";
			mes "この前カカオを配達してもらった所さ、";
			mes "チョコレートで有名な店なんだ。";
			mes "ちょうど期間限定販売してるから、";
			mes "キミも買ったらどうだい？";
			mes "今じゃないと手に入らないよ。";
			next;
			mes "[ブレイド]";
			mes "売れれば売れる程カカオの需要が増え、";
			mes "オレも取引増加!!　商売繁盛!!";
			mes "利益倍増!!　ってな～！";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "……";
			mes "なるほど、それが目的ですか……";
			next;
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "……ポーションピッチャー！";
			misceffect 207,"";
			percentheal 100,0;
			next;
			mes "["+strcharinfo(0)+"]";
			mes "ごまかすなっ!!";
			set QUEST_VALENTINE1,QUEST_VALENTINE1+1;
			return;
		case 4:
			if(rand(3)) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そろそろアルバイトも終わりか。";
				mes "荷物の整理をしないとなぁ。";
				next;
				menu "え、どこに行くんですか？",-;
				mes "[ブレイド]";
				mes "アルベルタに帰るのさ。";
				mes "そろそろ本業に戻らないとね。";
				mes "また、プロンテラに来た時にでも";
				mes "会えるといいな。";
				return;
			}
			cutin "v_breid01",2;
			mes "[ブレイド]";
			mes "カカオいるかい？";
			mes "単価300Zeny！";
			mes "5つセットで大特価1499Zeny!!";
			next;
			if(select("笑えない冗談だね……","あ、丁度ほしかったとこです")==1) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "……笑えない冗談って……";
				mes "オレ、何か変なこと言ったか？";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "値段がおかしいんですよ！";
				mes "値段が!!";
				next;
				cutin "v_breid03",2;
				mes "[ブレイド]";
				mes "はぁ～、これだから素人は……";
				mes "限定商品の価値を判ってないな？";
				mes "それはそうそう簡単に手に入る品物じゃ";
				mes "ないんだぞ!?";
				mes "早くしないと売り切れるぞ？";
				mes "今買わなきゃ、他の奴が買っちゃうぞ？";
				next;
				if(select("誰にでもそう言ってるんでしょ……","じゃ、今すぐ売ってください")==1) {
					cutin "v_breid05",2;
					mes "[ブレイド]";
					mes "もちろん、みんなにそう言うが……";
					mes "…………";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "じゃ、限定って？";
					mes "どこに限定の価値があるんです!?";
					next;
					cutin "v_breid02",2;
					mes "[ブレイド]";
					mes "……そりゃぁ……";
					mes "オレが売ることに決まってるだろう？";
					return;
				}
			}
			if(Zeny < 1499) {
				cutin "v_breid03",2;
				mes "[ブレイド]";
				mes "ん……Zenyが足りないみたいだね。";
				mes "悪いけど、値引きすることは";
				mes "できないんだ。";
				return;
			}
			cutin "v_breid02",2;
			mes "[ブレイド]";
			mes "毎度っ！";
			mes "限定って言葉に、みんな弱いよな！";
			set Zeny,Zeny-1499;
			getitem 7182,5;
			set QUEST_VALENTINE1,QUEST_VALENTINE1+1;
			return;
		}
	}

	function PatternI {	//case17
		if(rand(3)==0) {
			cutin "v_breid05",2;
			mes "[ブレイド]";
			mes "オマエ、チョコレートは好きか？";
			next;
			if(select("ええ、大好きです","いえ、あまり……")==1) {
				if(Sex==0) {
					//未調査？
				}
				cutin "v_breid02",2;
				mes "[ブレイド]";
				mes "そうか……それなら、";
				mes "プロンテラ南西の酒場にいる、";
				mes "アルル=オルレアンに会うといい。";
				mes "そいつが、チョコレートを";
				mes "売ってくれるよ。";
				next;
				mes "[ブレイド]";
				mes "恋人がいるなら、";
				mes "一つプレゼントしてあげたらどうだ？";
			}
			else if(Sex==0) {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そうか…………";
				mes "それだったら、これは友達にでも";
				mes "あげてくれ。";
				next;
				mes "[ブレイド]";
				mes "べ、別に、何か意味があって";
				mes "あげようとしたわけじゃないからな!?";
				mes "チョコレートの店をやってる友達から";
				mes "たまたま一つもらったから、";
				mes "もしキミが好物ならあげようかな～と";
				mes "思っただけだ！";
				getitem 559,1;
			}
			else {
				cutin "v_breid05",2;
				mes "[ブレイド]";
				mes "そっか……たまに食べると";
				mes "結構うまいもんだよ。";
				mes "溶けてくると手がべたつくのが、";
				mes "ちょっと気になるがな。";
				next;
				mes "[ブレイド]";
				mes "それに、人に贈るには最適の品物だ。";
				mes "チョコレートなら、大抵の人は";
				mes "喜んでくれるからな。";
				next;
				mes "[ブレイド]";
				mes "もしプレゼントする相手がいるなら、";
				mes "プロンテラ南西の酒場にいる";
				mes "アルル=オルレアンに会うといい。";
				mes "彼がチョコレートを売ってくれるよ。";
				set QUEST_VALENTINE1_FLAG,1;
			}
			set QUEST_VALENTINE1,18;
			return;
		}
	}

	function PatternJ {	//case18
		cutin "v_breid01",2;
		mes "[ブレイド]";
		mes "プロンテラの南西の酒場にいる";
		mes "アルル=オルレアンって奴が、";
		mes "チョコレートを売っている。";
		next;
		mes "[ブレイド]";
		mes "今しか買えないから、キミも";
		mes "買っておくといいよ。";
		return;
	}

	function PatternK {	//case19
		cutin "v_breid01",2;
		mes "[ブレイド]";
		mes "どうだ……？";
		mes "このチョコレートは美味しいだろう？";
		if(Sex==0) {
			mes "オレがキミにしてあげられることは、";
			mes "これくらいしかないからなぁ。";
		}
		else {
			mes "ぜひ、ガールフレンドにも";
			mes "プレゼントしてあげるといい。";
		}
		next;
		if(QUEST_VALENTINE1_FLAG==1) {
			mes "[ブレイド]";
			mes "短い間だったが、寒い中色々と";
			mes "話し相手になってくれてありがとう。";
			mes "残念だが、もう故郷に戻らなくちゃな。";
			mes "楽しかったよ。";
			mes "これは、オレから別れのプレゼントだ。";
			mes "親しい人にあげるといい。";
			getitem 573,1;
			set QUEST_VALENTINE1_FLAG,0;
		}
		else {
			mes "[ブレイド]";
			mes "……";
			mes "プロンテラでキミと出会えたこと、";
			mes "忘れないよ……";
		}
		set QUEST_VALENTINE1,20;
		return;
	}

	function PatternL {	//case20
		cutin "v_breid01",2;
		mes "[ブレイド]";
		mes "今日も平和だ……異常なし！";
		mes "ルーンミッドガッツ王国！";
		mes "万歳!!";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "気合い入ってますね。";
		next;
		cutin "v_breid02",2;
		mes "[ブレイド]";
		mes "うん……世の中、いつ何が起きるか";
		mes "わからないだろ？";
		mes "だから、今を一生懸命生きなきゃな、";
		mes "と思ってね。";
		return;
	}
}

prontera.gat,0,0,0	script	V_BreidTimer	-1,{
	end;
OnTimer180000:
	set callfunc("ValentineBreid",0),0;	//複数人同時アタッチ防止ロック解除
	end;
}

// ブレイド 2～4時 15～17時
prt_fild05.gat,360,252,3	script	ブレイド#Valentine1	733,{
	if(gettime(3)>= 2 && gettime(3)< 4) callfunc "ValentineBreid",1,2,1,3;
	if(gettime(3)>=15 && gettime(3)<17) callfunc "ValentineBreid",1,1,3,1;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=2 && gettime(3)<4) || (gettime(3)>=15 && gettime(3)<17))
		hideoffnpc;
	end;
OnClock0205:
OnClock1505:
	hideoffnpc;
	end;
OnHour04:
OnHour17:
	hideonnpc;
	end;
}

// ブレイド 4～7時 17～19時
prt_fild08.gat,162,367,5	script	ブレイド#Valentine2	733,{
	if(gettime(3)>= 4 && gettime(3)< 7) callfunc "ValentineBreid",2,2,1,3;
	if(gettime(3)>=17 && gettime(3)<19) callfunc "ValentineBreid",2,1,3,2;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=4 && gettime(3)<7) || (gettime(3)>=17 && gettime(3)<19))
		hideoffnpc;
	end;
OnClock0405:
OnClock1705:
	hideoffnpc;
	end;
OnHour07:
OnHour19:
	hideonnpc;
	end;
}

// ブレイド 8～10時 21～23時
prontera.gat,116,69,3	script	ブレイド#Valentine3	733,{
	if(gettime(3)>= 8 && gettime(3)<10) callfunc "ValentineBreid",3,1,2,1;
	if(gettime(3)>=21 && gettime(3)<23) callfunc "ValentineBreid",3,2,2,1;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=8 && gettime(3)<10) || (gettime(3)>=21 && gettime(3)<23))
		hideoffnpc;
	end;
OnClock0805:
OnClock2105:
	hideoffnpc;
	end;
OnHour10:
OnHour23:
	hideonnpc;
	end;
}

// ブレイド 12～15時
prontera.gat,58,70,3	script	ブレイド#Valentine4	733,{
	callfunc "ValentineBreid",4,1,4,1;
	end;
OnInit:
	if(gettime(3)<12 || gettime(3)>=15)
		hideonnpc;
	end;
OnClock1205:
	hideoffnpc;
	end;
OnHour15:
	hideonnpc;
	end;
}


//==============================================================
// スプラキ
//	 2～ 4時	聖水		クエスト○	名前入れ○
//	 4～ 6時	お皿		クエスト○	名前入れ○
//	 7～ 9時	盗蟲		クエスト○	名前入れ○
//	 9～11時	聖堂		クエスト×	名前入れ×
//	11～13時	聖水		クエスト○	名前入れ○
//	13～15時	盗蟲（クルセ）	クエスト×	名前入れ×
//	15～17時	お皿		クエスト○	名前入れ○
//	17～19時	休憩		クエスト×	名前入れ○
//	19～21時	牢獄		クエスト×	名前入れ×
//	21～23時	盗蟲		クエスト○	名前入れ○
// Function
//	getarg(0)	最初の会話内容
//		0=ロックの参照渡し専用
//		1=昼	2=夜	3=仕事	4=看朝	5=看夜	6=聖堂
//	getarg(1)	途中のイベント内容
//		1=聖水	2=お皿	3=盗蟲	4=聖堂	5=盗蟲2	6=休憩	7=牢獄
//	getarg(2)	クエスト可否
//		1=可能	2=不可	3=途中まで可	4=名前入れのみ可
//--------------------------------------------------------------

function	script	ValentineSprakki	{
	if(getarg(0)==0)
		return 'flag;	//値を渡して終了
	if((Weight*100/MaxWeight) >= 90) {
		mes "所持アイテムの重量が多いため";
		mes "アイテムを受けとることができません-";
		mes "-所持アイテムを減らしてから、再度";
		mes "話しかけてください-";
		close;
	}
	if('flag) {	//複数人同時アタッチ防止
		mes "-忙しそうだ-";
		mes "-少し待ってから、また声を掛けよう-";
		close;
	}
	set 'flag,1;
	initnpctimer "V_SprakkiTimer";
	switch(QUEST_VALENTINE2) {
		case 0:
			function PatternA;
			PatternA getarg(0);
			break;
		default:
			function PatternB;
			PatternB getarg(0),getarg(1);
			break;
		case 10:
			function PatternC;
			PatternC 0,0,getarg(2);
			break;
		case 11:
			function PatternD;
			PatternD;
			break;
		case 12:
			function PatternE;
			PatternE;
			break;
		case 13:
			function PatternF;
			PatternF 0,0,getarg(2);
			break;
		case 14:
			function PatternG;
			PatternG;
			break;
		case 15:
			function PatternH;
			PatternH;
			break;
		case 16:
			function PatternI;
			PatternI 0,0,getarg(2);
			break;
	}
	set 'flag,0;
	close2;
	cutin "dummy",255;
	return;

	function PatternA {	//case0
		switch(getarg(0)) {
		default:
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "何のご用ですか？";
			mes "あなたも私のように";
			mes "お城で働いている方でしょうか？";
			next;
			if(select("そうです","いや、違います")==1) {
				mes "[スプラキ]";
				mes "わぁ、嬉しい！";
				mes "私はこちらに来てからまだ間もなくて、";
				mes "知り合いがいなかったのですが";
				mes "同じ場所で働いているなら";
				mes "よく会うこともありますよね？";
				next;
				mes "[スプラキ]";
				mes "あなたは主に";
				mes "どこでお仕事をなさってるんですか？";
				mes "私は看護将校様の補助と";
				mes "クルセイダー職務室の担当を";
				mes "しているんです。";
				next;
				mes "[スプラキ]";
				mes "あ、毎朝大聖堂に行く許可を";
				mes "受けているんですが、";
				mes "一緒にいらっしゃいませんか？";
				next;
				if(select("……本当は働いていません","（このままでは収拾がつかなそうだ）")==2) {
					mes "["+strcharinfo(0)+"]";
					mes "（何も考えずに答えたら嘘をついたのが";
					mes "　ばれてしまう……。";
					mes "　ここは大げさに誤魔化して";
					mes "　この場を離れよう。）";
					next;
					cutin "v_sprakki05",2;
					mes "["+strcharinfo(0)+"]";
					mes "私が言ったことは全て忘れてください！";
					mes "あははは……";
					mes "では、忙しいのでこれで失礼！";
					return;
				}
			}
			mes "[スプラキ]";
			mes "あら、では何をなさっている方ですか？";
			mes "王室のお客様？　ただの通りすがり？";
			mes "そうじゃなければ……刺客?!";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "そんなわけないです!!!!";
			next;
			mes "[スプラキ]";
			mes "あは、そんなわけないのが解ってて";
			mes "言いました。";
			mes "本当に刺客だったら、";
			mes "まず私の手を掴んでるでしょうね。";
			break;
		case 4:
		case 5:
			cutin "v_sprakki05",2;
			mes "[スプラキ]";
			mes "あら、外部の方……";
			if(getarg(0)==4)
				mes "朝から看護室にいらっしゃるなんて、";
			else {
				mes "こんな夜おそく……看護室に";
				mes "いらっしゃるなんて、";
			}
			mes "何かご用ですか？";
			next;
			if(select("何でもないです","痛くてたまりません")==1) {
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "そうですか。";
				mes "お元気なのは良いことです。";
				if(getarg(0)==4) {
					mes "昨晩はよく寝れましたか？";
					mes "いい夢を見れましたか？";
				}
				else
					mes "私は、もうお休みの時間なのですよ……";
				break;
			}
			mes "[スプラキ]";
			mes "痛いのですか？　すごく？";
			mes "どこが痛いんです？";
			mes "え、えっと……まずは治療剤を……";
			next;
			misceffect 207,"";
			percentheal 100,0;
			mes "[スプラキ]";
			mes "えっ、こんなに!?";
			mes "ひどい傷……";
			mes "お薬、ちゃんと当たってますか？";
			next;
			mes "[スプラキ]";
			mes "どうですか？";
			mes "まだ痛みますか……？";
			mes "ごめんなさい……";
			mes "私、まだ未熟者ですから";
			mes "まともにお薬を扱えないんです……";
			next;
			if(select("ありがとう！　元気になりました","痛い！　ひどい治療だ！")==1) {
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "良かった……！";
				mes "不慣れなものでしたから";
				mes "心配だったんです。";
				break;
			}
			mes "[スプラキ]";
			mes "きゃっ！　びっくりした……";
			mes "そんなに叫ばなくても";
			mes "いいじゃないですか。";
			mes "一生懸命がんばったのに……";
			mes "ごめんなさい……未熟者で……";
			next;
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "今度は、ちゃんとやってみせます。";
			mes "でも……そんな風に";
			mes "人の誠意を無視してかっと叫ぶのは";
			mes "失礼ですよ？";
			next;
			mes "[スプラキ]";
			mes "そんなちょっとした一言でも";
			mes "傷ついてしまう人だって";
			mes "いるんですから……";
			mes "まあ、私は平気ですけどね。";
			break;
		case 6:
			mes "何かとても真剣に";
			mes "お祈りをしているようだ。";
			next;
			if(select("何をお祈りしているんですか？","邪魔しないでおこう")==2) {
				mes "-話しかけるのを止めた-";
				return;
			}
			cutin "v_sprakki05",2;
			mes "[スプラキ]";
			mes "きゃっ……";
			next;
			mes "[スプラキ]";
			mes "……聖堂では静かにしないと";
			mes "駄目ですよ……。";
			next;
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "えっ？";
			mes "私が何をお祈りしていたか";
			mes "知りたいのですか？";
			mes "私は世界の平和をお祈りしていました。";
			mes "あなたは何かお祈りをしましたか？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "……";
			mes "私は……";
			next;
			input '@mes$;
			mes "["+strcharinfo(0)+"]";
			mes "……";
			mes "私は……";
			mes "^4A4AFF" +'@mes$+ "^000000と";
			mes "お祈りしました!!";
			next;
			mes "[スプラキ]";
			mes '@mes$+ "ですか……";
			mes "神はお聞きくださるでしょうか？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "世界平和よりは実現しそうですよ？";
			next;
			cutin "v_sprakki02",2;
			mes "[スプラキ]";
			mes "ふふっ、それは冗談ですよ。";
			mes "実は世界の平和は祈ってません。";
			next;
			mes "^4A4AFF-……と彼女は小声でそう言うと";
			mes "舌を出して微笑んだ-^000000";
			next;
			mes "[スプラキ]";
			mes "あの……よろしければ";
			mes "お城へ遊びにきてくれませんか？";
			mes "城内では雑事を手伝っていますから";
			mes "またいつプロンテラに来れるか";
			mes "解りませんし……";
			next;
			mes "[スプラキ]";
			mes "お城での知り合いは";
			mes "看護将校様、クルセイダーの方々、";
			mes "聖堂の修道女様と神父様だけですが";
			mes "皆さん、とても忙しそうです……。";
			next;
			mes "[スプラキ]";
			mes "それと私は朝のお祈り時間にしか";
			mes "外出することができません。";
			next;
			if(select("いつでも遊びに行きますよ！","そんなつもりはない")==2) {
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "そうですよね……";
				mes "やっぱり初面の方に";
				mes "そんなお願いをするのは";
				mes "失礼ですよね……。";
				return;
			}
			mes "[スプラキ]";
			mes "本当ですか!? 嬉しい！";
			mes strcharinfo(0)+ "さん、ですね？";
			mes "ちゃんと憶えておきます。";
			mes "私と友達になってください！";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "ところで本当のお祈りは何だったの？";
			next;
			mes "[スプラキ]";
			mes "う～ん……秘密です。";
			mes "でも、神はもう私の願いを";
			mes "聞き入れてくれたようです。";
			next;
			mes "^4A4AFF-あなたに対するスプラキの好感度が";
			mes "上昇しました-^000000";
			if('name$=="" || rand(3)==0)
				set 'name$,strcharinfo(0);
			set QUEST_VALENTINE2,1;
			return;
		}
		//6以外の続き
		mes "^4A4AFF-彼女は、わずかに微笑んで";
		mes "辺りを見回した-^000000";
		next;
		mes "[スプラキ]";
		mes "あの……よろしければ";
		mes "また遊びに来てくれませんか？";
		mes "いつもここでお手伝いをしていますから";
		mes "来ていただけると嬉しいです。";
		next;
		mes "[スプラキ]";
		mes "私の知り合いといえば、";
		mes "看護将校様やクルセイダーの方々、";
		mes "それに大聖堂の神父様や修道女様";
		mes "だけなのですが……";
		next;
		mes "[スプラキ]";
		mes "皆さん、普段は忙しくて……";
		next;
		if(select("では、時間を見つけて遊びに来ますね","ごめんなさい、忙しいので……")==2) {
			cutin "v_sprakki03",2;
			mes "[スプラキ]";
			mes "そうですか、残念です。";
			mes "良い友達になれると思ったのに……";
			next;
			switch(getarg(0)) {
			case 1:
				mes "[スプラキ]";
				mes "私、疲れてしまったので";
				mes "ちょっと休まないと……";
				mes "もう出て行ってください。";
				return;
			case 2:
			case 5:
				mes "[スプラキ]";
				mes "今日もあちこち掃除して、大変でした。";
				mes "疲れていますので、これから休みます。";
				mes "もう出て行ってもらえますか？";
				return;
			case 3:
				mes "[スプラキ]";
				mes "私は今している仕事を";
				mes "全部しなければならないので";
				mes "もうお帰りくださいますか？";
				return;
			case 4:
				mes "[スプラキ]";
				mes "そろそろ、看護将校様が";
				mes "私を捜しに来ます。";
				mes "もう出て行ってくださいますか？";
				return;
			}
			return;
		}
		cutin "v_sprakki02",2;
		mes "[スプラキ]";
		mes "本当ですか!? 嬉しい！";
		mes strcharinfo(0)+ "さん、ですね？";
		mes "私の友達になってください！";
		next;
		switch(getarg(0)) {
		case 2:
			mes "[スプラキ]";
			mes "今日もあちこち掃除して、大変でした。";
			mes "疲れていますので、これから休みます。";
			next;
			mes "[スプラキ]";
			mes "また遊びに来てくださいね。";
			mes "夜もおそくなってしまったので、";
			mes "ゆっくり眠ります。";
			break;
		case 4:
			mes "[スプラキ]";
			mes "あ、そうだ。";
			mes "隣の部屋の看護将校様が";
			mes "気づく前にここを離れて下さい。";
			mes "怒ると本当に怖い人なんです！";
			next;
			mes "[スプラキ]";
			mes "後ほど、午後にでも";
			mes "遊びに来てくださいね。";
			break;
		default:
			mes "[スプラキ]";
			mes "また遊びに来てくださいね。";
			break;
		}
		next;
		mes "^4A4AFF-あなたに対するスプラキの好感度が";
		mes "上昇しました-^000000";
		if('name$=="" || rand(3)==0)
			set 'name$,strcharinfo(0);
		set QUEST_VALENTINE2,1;
		return;
	}

	function PatternB {	//case1～9
		switch(getarg(1)) {
		case 1:
			if(rand(3)==0) {
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "あ、" +strcharinfo(0)+ "さん！";
				mes "聖水持ってませんか？";
				mes "持っていたら、";
				mes "譲っていただきたいのですが……";
				next;
				if(countitem(523)) {
					if(select("ありますよ","今は持ってません")==1) {
						mes "["+strcharinfo(0)+"]";
						mes "持ってますよ。どうぞ。";
						mes "何に使うんですか？";
						next;
						mes "[スプラキ]";
						mes "見てください、この植物。";
						mes "葉は枯れ、幹は萎びてしまって……";
						mes "水をあげても、すぐに乾いて";
						mes "しまうんです。";
						next;
						mes "[スプラキ]";
						mes "栄養満点な聖水をあげれば、";
						mes "元気になってくれると思うんです。";
						next;
						delitem 523,1;
						cutin "v_sprakki02",2;
						mes "[スプラキ]";
						mes "どうもありがとう。";
						next;
						mes "^4A4AFF-あなたに対するスプラキの好感度が";
						mes "上昇しました-^000000";
						set QUEST_VALENTINE2,QUEST_VALENTINE2+1;
						return;
					}
				}
				mes "["+strcharinfo(0)+"]";
				mes "今は持ってないんです。";
				next;
				mes "[スプラキ]";
				mes "そうですか……残念です。";
				mes "明日、聖堂に寄って貰ってこなきゃ……";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "何故聖水が必要なんですか？";
				next;
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "見てください、この植物。";
				mes "葉は枯れ、幹は萎びてしまって……";
				mes "水をあげても、すぐに乾いて";
				mes "しまうんです。";
				next;
				mes "[スプラキ]";
				mes "栄養満点な聖水をあげれば、";
				mes "元気になると思ったんですが……";
				return;
			}
			if(getarg(0)==1) {
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "ちょうどお腹がすく時間でしょう？";
				mes "せっかくいらっしゃったんですから";
				mes "何かおやつでもご一緒したいですね～";
				next;
				mes "[スプラキ]";
				mes "こんな時はなんとなく";
				mes "食べ残しておいたクッキーが";
				mes "ひと切れしかないのが";
				mes "惜しいですね……";
				next;
				if(countitem(538)) {
					if(select("クッキーを渡す","そうですね")==1) {
						mes "[スプラキ]";
						mes "あら、これは";
						mes "よく焼いたクッキーですね？";
						mes "うわ～♪";
						if(Sex==0) {
							mes "やっぱり同じ女の子同士";
							mes "通じるところがあるんでしょうか～";
						}
						next;
						cutin "v_sprakki02",2;
						mes "[スプラキ]";
						mes "クッキーに合うお茶でも出しますね。";
						mes "ぶどう汁にハーブを入れたお茶です。";
						mes "ブドウジュースとあまり";
						mes "変わりませんけどね。";
						next;
						mes "^4A4AFF-スプラキが差し出した";
						mes "小さな湯飲みには、綺麗な濃い";
						mes "紫色のハーブティーが";
						mes "淹れられていた-^000000";
						next;
						mes "^4A4AFF-ブドウ特有のやや酸っぱい";
						mes "香りが鼻腔をくすぐる-";
						mes "-一口飲むと口の中いっぱいに";
						mes "甘酸っぱい香りが広がる-^000000";
						percentheal 100,0;
						misceffect 83,"";
						delitem 538,1;
						return;
					}
				}
				mes "[スプラキ]";
				mes "私が少しはまともに料理が";
				mes "できれば、こういう時に";
				mes "おやつを作っておけるんですけど……";
				mes "なかなかうまくできないですね。";
				return;
			}
			if(getarg(0)==2) {
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "せっかくいらっしゃったのですから、";
				mes "お茶でも飲んでください。";
				mes "何にしますか？";
				next;
				switch(select("グレープハーブティー","ウッドティー","ミックスハーブティー","結構です")) {
				case 1:
					mes "[スプラキ]";
					mes "ブドウ汁にハーブを入れたお茶です。";
					mes "ブドウジュースとあまり";
					mes "変わりませんけどね。";
					next;
					mes "^4A4AFF-スプラキが差し出した";
					mes "小さな湯飲みには、綺麗な濃い";
					mes "紫色のハーブティーが";
					mes "淹れられていた-^000000";
					next;
					mes "^4A4AFF-ブドウ特有のやや酸っぱい";
					mes "香りが鼻腔をくすぐる-";
					mes "-一口飲むと口の中いっぱいに";
					mes "甘酸っぱい香りが広がる-^000000";
					misceffect 83,"";
					return;
				case 2:
					mes "[スプラキ]";
					mes "木の根を煎じたお茶ですね。";
					mes "フフ……意外ですね。";
					mes "ウッドティーは主にお年寄りの方が";
					mes "好んで飲むものですからね。";
					next;
					mes "[スプラキ]";
					mes "フェイヨンでは木の根が得やすいので、";
					mes "お年寄りの方がよく飲んでましたよ。";
					mes "ウィローから採れた木の根と";
					mes "エルダーウィローから採れた木の根では";
					mes "味が違うらしいですね。";
					next;
					mes "[スプラキ]";
					mes "私にはさっぱりわかりませんが……";
					mes "あなたは違いがわかるんですか？";
					mes "フフ……出来ました。";
					mes "さぁ、どうぞ。";
					next;
					mes "^4A4AFF-彼女が差し出したカップには";
					mes "褐色の液体が波々と注がれていて";
					mes "異様な香りを発している-^000000";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "うわっ、な、何だこれ!!";
					mes "すっごく苦い!!　それに……";
					mes "やたらとドロドロしてて気持ち悪い!!";
					misceffect 118,"";
					next;
					cutin "v_sprakki05",255;
					mes "[スプラキ]";
					mes "え……飲んだことなかったのですか？";
					mes "ウッドティーはそういうものですよ？";
					mes "もう、どうして注文したんですか!!";
					return;
				case 3:
					cutin "v_sprakki01",2;
					mes "[スプラキ]";
					mes "何種類ものハーブを混ぜ合わせた、";
					mes "ミックスハーブティーですね。";
					mes "香りがもの凄く強いですよ。";
					next;
					mes "[スプラキ]";
					mes "味は……";
					mes "飲んでみればわかります……";
					next;
					mes "^4A4AFF-彼女が差し出したカップには";
					mes "ピンク色の液体が波々と注がれていて";
					mes "赤い葉が一枚漂っている-";
					mes "-そして、目眩がする程";
					mes "強烈な香りを放っている-^000000";
					next;
					mes "^4A4AFF-味は……-^000000";
					next;
					mes "[スプラキ]";
					mes "ええっと……表情を見れば、";
					mes "感想を聞く必要はなさそうですね……";
					mes "これは香りを楽しむ飲み物ですね。";
					mes "強烈なハーブの香りをゆっくり吸うと、";
					mes "頭がすっきりするんですよ。";
					misceffect 14,"";
					return;
				case 4:
					cutin "v_sprakki01",2;
					mes "[スプラキ]";
					mes "そうですか……残念です。";
					return;
				}
			}
		case 2:
			if(rand(3)==0) {
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "あああ……!!";
				mes "困ったわ……私って、";
				mes "どうしてこうドジなんだろう……";
				next;
				menu "どうしたんですか？",-;
				mes "[スプラキ]";
				mes "それが……";
				mes "テーブルを拭いていたのですが、";
				mes "うっかりデザート用のお皿を落として";
				mes "割ってしまったのです……";
				next;
				mes "[スプラキ]";
				mes "はぁ……お給料から弁償しなければ";
				mes "いけないですね……";
				mes "あ、まったく同じお皿があれば、";
				mes "それでもいいかな。";
				mes "こんなことを聞くのも変ですが、";
				mes "これと同じお皿、持ってませんか……？";
				next;
				if(countitem(736)) {
					if(select("お皿を持ち歩くと思います？","持っています。あげますよ")==2) {
						cutin "v_sprakki05",2;
						mes "[スプラキ]";
						mes "え!?";
						mes "いつもお皿を持ち歩いてる人なんて、";
						mes "いるわけ……";
						mes "あ……からかってるんですねっ!?";
						next;
						mes "[スプラキ]";
						mes "^4A4AFF-懐から白い皿を取り出し、";
						mes "彼女の前に置いた-";
						mes "-お皿の表面がキラリと光った-^000000";
						next;
						mes "[スプラキ]";
						mes "ああっ!!　本当にお皿を持ってる！";
						mes "それに……";
						mes "私が割ったお皿とそっくり!!";
						mes "これ、本当に私にくださるのですか？";
						next;
						delitem 736,1;
						cutin "v_sprakki02",2;
						mes "[スプラキ]";
						mes "ありがとう！";
						mes "あなたみたいに優しい人は、";
						mes "世界に一人しかいないですね！";
						next;
						mes "^4A4AFF-あなたに対するスプラキの好感度が";
						mes "上昇しました-^000000";
						set QUEST_VALENTINE2,QUEST_VALENTINE2+1;
						return;
					}
				}
				else {
					mes "["+strcharinfo(0)+"]";
					mes "さすがにお皿は持ってませんね……";
					next;
				}
				mes "[スプラキ]";
				mes "ですよね……";
				mes "いつもお皿を持ち歩いてる人なんて、";
				mes "いませんよねぇ……";
				mes "やっぱり、後で料理長に謝って";
				mes "おかなきゃダメですね。";
				next;
				mes "[スプラキ]";
				mes "はぁ、もっと慎ましく行動しなきゃ……";
				return;
			}
			if(getarg(0)==1) {
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "きちんと食事は摂ってますか？";
				mes "仕事や冒険もいいですけど、";
				mes "健康が一番大切ですよ。";
				next;
				mes "[スプラキ]";
				mes "食後は、軽く散歩すると良いですよ。";
				mes "私が何故そんな話をするのかって";
				mes "顔してますね……";
				next;
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "実は私、これから食事をする";
				mes "ところなのです……";
				next;
				if(select("私も一緒に食べたいです","あ、失礼しました。")==1) {
					cutin "v_sprakki03",2;
					mes "[スプラキ]";
					mes "え……";
					mes "部外者の方と食事をすると、";
					mes "料理長に怒られてしまいますので……";
					mes "ごめんなさい。";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "そうですか、残念です。";
					mes "食事の邪魔しちゃいましたね。";
					mes "失礼しますね。";
					mes "ああ……どこで何を食べようかな……";
					return;
				}
				mes "[スプラキ]";
				mes "フフ……ごめんなさいね、";
				mes "気を遣わせちゃって。";
				mes "また後でも来てくだされば、";
				mes "お茶でもご馳走しますね。";
				return;
			}
			if(getarg(0)==2) {
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "この時間は静かで良いですね。";
				mes "まだちょっと体がだるいけれど、";
				mes "用はどんな一日になるかなぁ～って";
				mes "色々考えるんです。";
				next;
				mes "[スプラキ]";
				mes strcharinfo(0)+ "さんは、";
				mes "どうしてこんな時間に";
				mes "私を訪ねて来たんですか？";
				next;
				if(select("ただ退屈で……","仕事のついでに立ち寄ったんです")==1) {
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "もう帰って休んだらどうですか？";
					mes "でないと、体がもちませんよ？";
					return;
				}
				mes "[スプラキ]";
				mes "お仕事、大変なんですね……";
				mes "でも、きちんと体を休めてくださいね。";
				mes "夜勤なんですか？";
				mes "手当てはちゃんと出るんですか？";
				next;
				cutin "v_sprakki03",255;
				mes "[スプラキ]";
				mes "私は実習生なので、";
				mes "夜勤手当がないんです……";
				mes "勉強のためなのでしかたないのですが、";
				mes "ちょっと挫折しそうになります……";
				next;
				cutin "v_sprakki02",255;
				mes "[スプラキ]";
				mes "でも、お金ばかりを気にしてては";
				mes "いけませんね。";
				mes strcharinfo(0)+ "さんのような";
				mes "優しい人にも出会えたし……";
				mes "ねっ？";
				return;
			}
		case 3:
		case 5:
			if(rand(3)==0) {
				cutin "v_sprakki05",2;
				mes "[スプラキ]";
				mes "きゃっ！　わわっ!!";
				mes "そ、そこ！　気をつけて!!";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "え？　なんです？";
				mes "何に気をつけるんですか？";
				next;
				mes "[スプラキ]";
				mes "掃除をしていたら中に……";
				mes "シーツを整理していたら中に……";
				mes "あ、あの……あれ！　あれが!!";
				next;
				mes "[スプラキ]";
				mes "あれが出たんですっ!!";
				mes "真っ黒で、すごく早くて";
				mes "一匹見たら何百匹はいると言う!!";
				next;
				if(select("うわあ!!　やめて!!","盗蟲ですか？")==1) {
					mes "["+strcharinfo(0)+"]";
					mes "盗蟲なんて、まっぴらごめんだ!!!!";
					return;
				}
				mes "[スプラキ]";
				mes "そ、その名前を口に出さないで!!";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "何かで払い落とせば";
				mes "いいじゃないですか。";
				next;
				if(getarg(1)==3) monster "prt_castle.gat",167,164,"あれ",1051,1,"Thiefbug#Valentine";
				if(getarg(1)==5) monster "prt_castle.gat",33,165,"あれ",1051,1,"Thiefbug#Valentine";
				mes "^8C1010-カサカサ-";
				mes "-ギーギー　ギーギー-^000000";
				next;
				mes "[スプラキ]";
				mes "で……出た!!";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "私が捕りましょうか？";
				mes "こんな感じですよ。";
				next;
				mes "^4A4AFF-私はそっと";
				mes "手を盗蟲の上に伸ばした-^000000";
				next;
				killmonster "prt_castle.gat","Thiefbug#Valentine";
				mes "^4A4AFF-バンッ！-";
				mes "-ブチュ……-^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "捕った！";
				mes "見ます？　捕りましたよ。";
				mes "ふふふっ……";
				next;
				mes "[スプラキ]";
				mes "そ、そうですね……";
				mes "は……はい……";
				next;
				mes "[スプラキ]";
				mes "あ、ありがとう……";
				mes "ありがとうございますっ!!";
				mes "でも、その手で近付かないでえええ!!";
				next;
				if(select("はぁ？　ひどいなあ!?","大丈夫、近づきませんよ")==1) {
					mes "["+strcharinfo(0)+"]";
					mes "あなたのためを思って";
					mes "捕ってあげたのに……";
					next;
					cutin "v_sprakki03",2;
					mes "[スプラキ]";
					mes "あっ、はい……ごめんなさい……";
					mes "でも……でも……";
					mes "それが、本当に怖いんです。";
					mes "わかってください。";
					next;
					mes "[スプラキ]";
					mes "本当に感謝してます……";
				}
				else {
					cutin "v_sprakki03",2;
					mes "[スプラキ]";
					mes "ごめんなさい……";
					mes "本当に怖いんです……";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "ええ、わかりますよ。";
					mes "盗蟲を嫌う人は多いですものね。";
					next;
					mes "[スプラキ]";
					mes "そうなんです……";
					mes "おかげでシーツの整理を";
					mes "続けることができます。";
					mes "本当にありがとうございます！";
				}
				next;
				mes "^4A4AFF-あなたに対するスプラキの好感度が";
				mes "上昇しました-^000000";
				set QUEST_VALENTINE2,QUEST_VALENTINE2+1;
				return;
			}
			if(getarg(0)==4) {
				mes "^4A4AFF-鼻歌を歌いながら";
				mes "シーツを整理している彼女が";
				mes "なんとなく楽しそうに見える-^000000";
				next;
				cutin "v_sprakki02",2;
				mes "["+strcharinfo(0)+"]";
				mes "なんだかご機嫌ですね？";
				next;
				mes "[スプラキ]";
				mes "はい！　後で大聖堂へ行くので、";
				mes "またあの人を見られるかなって";
				mes "なんとなく期待しちゃって……";
				next;
				menu "あの人？",-;
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "あ、いえ、何でもないんです。";
				mes "それじゃ、私はシーツの整理を";
				mes "全部終わらせないといけないから";
				mes "ちょっと席を外して";
				mes "くださいませんか？";
				return;
			}
			if(getarg(0)==5) {
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "ららら～、ららら～";
				mes "シーツの整理もみんな終わって、";
				mes "あれも出ないから、";
				mes "あ～ 幸せ!!";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "なんだかご機嫌ですね？";
				next;
				mes "[スプラキ]";
				mes "はい！　今日は早く休めますよ。";
				mes "ふふ、最近休み時間に、";
				mes "こっそり料理の勉強をしています。";
				next;
				mes "[スプラキ]";
				mes "デザート担当のアルルさんには、";
				mes "遠く及ばないけれど、";
				mes "すごく努力しているんですよ。";
				mes "いつか、チョコレートでも";
				mes "作れるようになったら、";
				mes "差し上げますわ。";
				next;
				mes "[スプラキ]";
				mes "ウフフッ……";
				return;
			}
		case 4:
			if(QUEST_VALENTINE2_FLAG==1) {
				if(countitem(2608)) {
					mes "["+strcharinfo(0)+"]";
					mes "これ……";
					mes "このロザリーを使ってください。";
					mes "昨日のうちに持ってくることが";
					mes "できなくてごめんなさい。";
					next;
					cutin "v_sprakki05",2;
					mes "[スプラキ]";
					mes "えっ？　捜してくれたのですか？";
					mes "どこで見つけたんですか？";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "いや、見つけたものではなくて……";
					mes "あの……私のものなんです。";
					mes "良かったらこれを使ってください。";
					next;
					mes "[スプラキ]";
					mes "えっ、本当に良いんですか？";
					mes "喜んで受け取らせていただきます。";
					mes "本当にありがとうございます！";
					next;
					delitem 2608,1;
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes strcharinfo(0)+ "さんの";
					mes "贈り物だと思って大事にしますね。";
					next;
					mes "^4A4AFF-あなたに対する彼女の好感度が";
					mes "大幅に上昇しました-^000000";
					set QUEST_VALENTINE2,QUEST_VALENTINE2+3;
					if(QUEST_VALENTINE2 > 10)
						set QUEST_VALENTINE2,10;
					set QUEST_VALENTINE2_FLAG,2;
					return;
				}
				cutin "v_sprakki01",2;
				mes "[スプラキ]";
				mes "あ、ご機嫌いかがですか？";
				mes "よく眠れましたか？";
				next;
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "まだ、見つかっていないみたいですね。";
				mes "私もまだ見つけることが";
				mes "できていません。ミサはそのまま";
				mes "ぼんやり聞き過ごしてしまいました。";
				next;
				if(select("必ず見つけてあげますよ","これ以上は助けることができません")==1) {
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "そこまでおっしゃっていただけるなんて";
					mes "本当に申し訳ないです。";
					mes "でも……何だかうれしいです。";
					mes "一緒に心配してくれる人が";
					mes "そばに居てくれるなんて……";
					return;
				}
				mes "[スプラキ]";
				mes "無理しなくてもいいですよ。";
				mes "私一人で捜してみます。";
				mes strcharinfo(0)+ "さんもご自分の";
				mes "お仕事がおありでしょうから……";
				mes "私は大丈夫です。";
				set QUEST_VALENTINE2_FLAG,2;
				return;
			}
			if(rand(3)==0) {
				if(QUEST_VALENTINE2_FLAG==2) {
					cutin "v_sprakki01",2;
					mes "[スプラキ]";
					mes "あ、おはようございます。";
					mes "早朝から礼拝してはいるけれど、";
					mes "私、信徒というわけではないんです。";
					mes "礼拝なんて、今までほとんど";
					mes "したことないですし……";
					next;
					mes "[スプラキ]";
					mes "ずっとお城の中にいると息苦しく";
					mes "なってくるので、気分転換に";
					mes "ここまで足を運んでみたんです。";
					mes "それに、プロンテラの街を";
					mes "色々見て回りたかったの。";
					next;
					mes "[スプラキ]";
					mes "プロンテラの街を見て回るなら、";
					mes "何も礼拝に参加しなくてもいいのに……";
					mes "フフ……何やってるんだろう、私。";
					next;
					mes "[スプラキ]";
					mes "私はもうすぐ看護実習が終わるので、";
					mes "フェイヨンに帰るんです。";
					mes "もっとプロンテラの街を色々と";
					mes "見ておけば良かったな……";
					mes "でも、あなたとお話することができたし";
					mes "礼拝に来て良かったかな。";
					next;
					mes "[スプラキ]";
					mes "神に感謝のお祈りしなきゃね。";
					mes "何に対する感謝かは秘密です♪";
					mes "フフ……";
					next;
					mes "^4A4AFF-彼女はそう囁くと静かに祈り始めた-^000000";
					return;
				}
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "どうしよう……";
				mes "大切なものを";
				mes "失くしてしまいました……。";
				next;
				if(select("どうしたのか聞いてみる","別に気にしない")==2) {
					mes "-気にしないことにした-";
					return;
				}
				mes "["+strcharinfo(0)+"]";
				mes "何かお困りですか？";
				next;
				mes "[スプラキ]";
				mes "あ……" +strcharinfo(0)+ "さん！";
				mes "実はロザリーを";
				mes "無くしてしまったんです。";
				mes "ロザリーがないとミサができません。";
				next;
				mes "[スプラキ]";
				mes "私は自分の魂ともいえるものを";
				mes "失くしてどうやって生きていけば";
				mes "いいのでしょうか……。";
				next;
				if(select("私も捜してみましょう","よく捜してみては？　どこかにありますよ")==2) {
					cutin "v_sprakki01",2;
					mes "[スプラキ]";
					mes "はい、よく捜してみます。";
					mes "心配してくれてありがとう。";
					return;
				}
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "本当にありがとうございます。";
				mes strcharinfo(0)+ "さんは";
				mes "とてもやさしい方ですね。";
				mes "本当にありがとう。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "（ロザリーを一つ買って";
				mes "渡せばいいかな？）";
				mes " ";
				mes "少し待っててください。";
				mes "ロザリーを捜してきます。";
				next;
				mes "[スプラキ]";
				mes "はい。";
				mes "私も懸命に捜してみます。";
				mes "できればミサに遅れたくありません。";
				mes "どうかよろしくお願いします……。";
				set QUEST_VALENTINE2_FLAG,1;
				return;
			}
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "真面目なんですね。";
			mes "まだ早朝なのに……";
			next;
			if(select("あなたに会いたくて来ました","色々と忙しくて……")==1) {
				if(QUEST_VALENTINE2 < 5) {
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "うふふ、うれしいです。";
					mes "そんなお世辞には";
					mes "騙されませんよ？";
					next;
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "聖堂で声を上げるのは";
					mes "気がひけますので";
					mes "後でお城に遊びに来てください。";
					mes "場所は知っていますか？";
					set QUEST_VALENTINE2,QUEST_VALENTINE2+1;
					return;
				}
				mes "[スプラキ]";
				mes "悪い冗談は嫌いです。";
				next;
				if(select("冗談はお嫌いですか？","冗談です。ごめんなさい")==1) {
					mes "[スプラキ]";
					mes "はい。冗談やいたずらでしたら、";
					mes "私が笑って聞いている間に";
					mes "やめてください。";
					mes "最初の数回くらいなら";
					mes "冗談だと思えますが……。";
					next;
					mes "["+strcharinfo(0)+"]";
					mes "い、いい意味で受け取ってください。";
					mes "好意的な意味です……。";
					next;
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "わかりました。";
					mes "さあ、聖堂へ来たのですから";
					mes "お祈りをしましょう？";
					mes "今日も世界が平和であるように。";
					return;
				}
				cutin "v_sprakki02",2;
				mes "[スプラキ]";
				mes "わかりました。";
				mes "では、お祈りをしましょうか？";
				mes "今日も世界が平和であるように。";
				return;
			}
			mes "[スプラキ]";
			mes "そうなんですか、大変ですね。";
			next;
			mes "[スプラキ]";
			mes "そうだ……！";
			mes strcharinfo(0)+ "さんの";
			mes "今日の運勢を占ってあげましょう。";
			next;
			mes "[スプラキ]";
			mes strcharinfo(0)+ "さんの";
			mes "今日の運勢は……";
			next;
			switch(rand(3)) {
				case 0:
					cutin "v_sprakki02",2;
					mes "[スプラキ]";
					mes "わぁ～、すごく運が良いみたいですよ？";
					mes "今日は何かにチャレンジしてみては";
					mes "いかがですか？";
					mes "ホルグレンさんに精錬を";
					mes "お願いするのも良いかもしれませんね！";
					return;
				case 1:
					mes "[スプラキ]";
					mes "普通……みたいですね。";
					mes "いつも通り平穏な一日となりそうです。";
					mes "平穏なのは、良いことですよね？";
					mes "フフフ……";
					return;
				case 2:
					cutin "v_sprakki05",2;
					mes "[スプラキ]";
					mes "あ……これは……え～っと……";
					mes "今日の運勢は……あの……その……";
					mes "お大事に……";
					next;
					mes "[スプラキ]";
					mes strcharinfo(0)+ "さんの";
					mes "無事を祈ってます……";
					return;
			}
		case 6:
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "ららら～、ららら～";
			mes "ちょっぴり休憩たいむ～♪";
			next;
			mes "[スプラキ]";
			mes "^4A4AFF" +'name$+ "^000000さんを";
			mes "ご存じですか？";
			mes "とても親切で素敵な方なんですが……";
			next;
			mes "[スプラキ]";
			mes "あ、別にあなたと比べようと";
			mes "思ったわけではなかったのですが。";
			return;
		case 7:
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "あの……ここから出てくれますか？";
			mes "ここは安易に出入りする場所では";
			mes "ありませんから……";
			return;
		}
	}

	function PatternC {	//case10
		if(getarg(2)==2 || getarg(2)==4 || rand(3)) {
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "ひょっとして、";
			mes "^4A4AFF" +'name$+ "^000000さんを";
			mes "ご存じですか？";
			mes "とってもオシャレな方なんですよ……";
			next;
			mes "[スプラキ]";
			mes "でも、" +strcharinfo(0)+ "さんも";
			mes "とても素敵ですよ。";
			return;
		}
		cutin "v_sprakki01",2;
		mes "[スプラキ]";
		mes "えっと……";
		mes "最近私、お菓子作りを";
		mes "しているんです。";
		mes "もちろんこっそりしているのですが……";
		next;
		mes "[スプラキ]";
		mes "それで、一度チョコレートを";
		mes "作ってみたいと思ったんです。";
		mes "でも、レシピを持っていないんです……";
		next;
		mes "[スプラキ]";
		mes "ご存知のとおり、私は午前中の";
		mes "ミサに行くこと以外、お城を出ることが";
		mes "できないのです。ですので……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "私に、代わりにレシピを";
		mes "手に入れてきて欲しいと";
		mes "いうわけですね？";
		next;
		mes "[スプラキ]";
		mes "はい！　毎年今頃になると";
		mes "チョコレートを作って";
		mes "売っている方々がいらっしゃいます。";
		mes "バシニオ家の方々なのですが、";
		mes "レシピをちょっと貰ってきて";
		mes "くれませんか？";
		next;
		if(select("お安い御用です","そんな余裕はないですね……")==2) {
			cutin "v_sprakki03",2;
			mes "[スプラキ]";
			mes "そうですか……";
			mes "あ、急いではいませんから";
			mes "大丈夫です。";
			mes "でも、レシピを貰っておいたほうが";
			mes "いいのに……";
			next;
			mes "[スプラキ]";
			mes "チョコレート……";
			mes "すごくおいしいのに……";
			mes "そう思いませんか？";
			return;
		}
		mes "[スプラキ]";
		mes "ありがとうございます！";
		mes "たぶん、バシニオ家の方々は";
		mes "例年どおりアルベルタで";
		mes "商売をしていると思います。";
		next;
		mes "[スプラキ]";
		mes "それではお願いしますね！";
		set QUEST_VALENTINE2,11;
		set QUEST_VALENTINE2_FLAG,0;
		return;
	}

	function PatternD {	//case11
		cutin "v_sprakki01",2;
		mes "[スプラキ]";
		mes "バシニオ家の方々は大抵";
		mes "アルベルタで商売をしています。";
		mes "フェイヨンで暮らしていた頃、";
		mes "たびたび訪ねてはチョコレートを";
		mes "買ってきたりしていました。";
		next;
		mes "[スプラキ]";
		mes "いつかレシピをくれると";
		mes "約束もしましたから、";
		mes "私の名前を出せば貰えると思います。";
		mes "よろしくお願いしますね。";
		return;
	}

	function PatternE {	//case12
		cutin "v_sprakki01",2;
		mes "[スプラキ]";
		mes "レシピを貰ってきてくれたのですか!?";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ええ、ここにありますよ。";
		mes "ところで本当に作れるのですか？";
		mes "こんな材料で？";
		mes "カカオ、ミルク……";
		mes "携帯用溶鉱炉はなぜ必要なのですか？";
		next;
		mes "^4A4AFF-スプラキにショコラから貰った";
		mes "チョコレートのレシピを渡した-^000000";
		next;
		mes "[スプラキ]";
		mes "作ってみれば分かりますよ。";
		mes "でも、カカオだなんて……";
		mes "カカオをどこで";
		mes "手に入れればいいのでしょう？";
		mes "まだまだ前途多難ですね。";
		next;
		cutin "v_sprakki02",2;
		mes "[スプラキ]";
		mes "とにかくありがとうございます。";
		mes "私、いつも" +strcharinfo(0)+ "さんに";
		mes "ありがとうってばかり言ってますね。";
		mes "でも……本当にうれしいです。";
		next;
		mes "^4A4AFF-あなたに対するスプラキの親密度が";
		mes "上昇しました-^000000";
		set QUEST_VALENTINE2,13;
		return;
	}

	function PatternF {	//case13
		if(getarg(2)==1) {
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "ひょっとして、";
			mes "^4A4AFF" +'name$+ "^000000さんを";
			mes "ご存じですか？";
			mes "とってもオシャレな方なんですよ……";
			next;
			mes "[スプラキ]";
			mes "でも、" +strcharinfo(0)+ "さんも";
			mes "とても素敵ですよ。";
			return;
		}
		cutin "v_sprakki01",2;
		mes "[スプラキ]";
		mes "あの……プロンテラのどこかで";
		mes "カカオを売っているお店があるという";
		mes "話を聞きました。";
		mes "どこにあるかご存じですか？";
		next;
		if(select("私が捜してみましょうか？","知らないです")==2) {
			mes "[スプラキ]";
			mes "やっぱり他の方と同じで";
			mes "ご存じないですか……";
			mes "後で詳しそうな人に訊いてみます。";
			mes "カカオを買うのが";
			mes "こんなに大変だなんて……";
			return;
		}
		cutin "v_sprakki02",2;
		mes "[スプラキ]";
		mes "本当ですか!? 嬉しい！";
		mes "それじゃあ、カカオを";
		mes "^4A4AFF5つ^000000お願いしてもいいですか？";
		mes strcharinfo(0)+ "さんは";
		mes "とっても優しい方ですね！";
		set QUEST_VALENTINE2,14;
		return;
	}

	function PatternG {	//case14
		cutin "v_sprakki01",2;
		mes "[スプラキ]";
		mes "お願いしたカカオはどうなりましたか？";
		next;
		if(countitem(7182)>=5) {
			delitem 7182,5;
			set QUEST_VALENTINE2,15;
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "さすが" +strcharinfo(0)+ "さん！";
			mes "これで私もチョコレートを";
			mes "作ることができます。";
			mes "うふふ、本当にありがとう！";
			next;
			mes "^4A4AFF-あなたに対するスプラキの親密度が";
			mes "上昇しました-^000000";
			return;
		}
		cutin "v_sprakki03",2;
		mes "[スプラキ]";
		mes "あ……まだカカオは";
		mes "手に入れられませんか。";
		mes "……やはり、森の中へ行って";
		mes "直接採らなければならないでしょうか？";
		mes "でも、それは危険ですし……";
		return;
	}

	function PatternH {	//case15
		cutin "v_sprakki02",2;
		mes "[スプラキ]";
		mes "見ててくださいね、";
		mes "チョコレートを作りますよ～。";
		mes strcharinfo(0)+ "さんも";
		mes "約束どおり色々と手伝ってくれたから";
		mes "チョコレートをさしあげます。";
		next;
		mes "[スプラキ]";
		mes "もし誰かにプレゼントしたいなら";
		mes "いつでもカカオを5つ";
		mes "集めてきてくださいね。";
		mes "あまり上手ではありませんが";
		mes "私が作ってあげます。";
		next;
		mes "[スプラキ]";
		mes "私がプロンテラで過ごせる時間は";
		mes "あと少しです。";
		mes "故郷に帰る準備も";
		mes "しなければいけません。";
		mes "でも、それまで私はここにいます。";
		next;
		mes "[スプラキ]";
		mes "お礼には足らないかもしれませんが";
		mes "感謝の気持ちを込めて贈ります。";
		mes "よかったら受け取ってくださいね。";
		getitem 558,1;
		set QUEST_VALENTINE2,16;
		return;
	}

	function PatternI {	//case16
		if(getarg(2)!=1 && getarg(2)!=4) {
			cutin "v_sprakki01",2;
			mes "[スプラキ]";
			mes "ひょっとして、";
			mes "^4A4AFF" +'name$+ "^000000さんを";
			mes "ご存じですか？";
			mes "とってもオシャレな方なんですよ……";
			next;
			mes "[スプラキ]";
			mes "でも、" +strcharinfo(0)+ "さんも";
			mes "とても素敵ですよ。";
			return;
		}
		cutin "v_sprakki02",2;
		mes "[スプラキ]";
		mes "チョコレートを作りましょうか？";
		mes "実は、あのアルル=オルレアンさんの";
		mes "チョコレートを見よう見まねだけど";
		mes "作れるようになったんですよ。";
		mes "うふふっ。";
		next;
		mes "[スプラキ]";
		mes "チョコレートに名前を入れることも";
		mes "できるようになりました！";
		next;
		mes "[スプラキ]";
		mes "どう？　すごいでしょう？";
		mes "もし手作りチョコを持っていたら";
		mes "渡してくださいね。";
		mes "私が今すぐ素敵な名前を";
		mes "入れてあげましょう！";
		next;
		if(select("チョコレートを作ってください","名前を入れてください")==1) {
			if(countitem(7182)<5) {
				cutin "v_sprakki03",2;
				mes "[スプラキ]";
				mes "チョコレートを作ってあげたい";
				mes "気持ちは山々なのですが……";
				mes "あの……カカオがないと";
				mes "作ることができないんです。";
				mes "ごめんなさい……";
				return;
			}
			mes "[スプラキ]";
			mes "はい！　がんばって作りますよ！";
			mes "このチョコレートを受け取る方が";
			mes strcharinfo(0)+ "さんのことを";
			mes "想ってくれているといいですね～";
			next;
			mes "[スプラキ]";
			mes "では……";
			next;
			mes "[スプラキ]";
			mes "出来ました～！";
			mes "私がお役に立てるなんて";
			mes "嬉しいです！";
			if(rand(5)==0) {
				mes "今回はホワイトチョコに";
				mes "してみました。";
				getitem 560,1;
			}
			else
				getitem 558,1;
			return;
		}
		getinventorylist;
		for(set '@i,0; '@i<@inventorylist_count; set '@i,'@i+1) {
			if(@inventorylist_id['@i] == 559 || @inventorylist_id['@i] == 560) {
				if(@inventorylist_card3['@i] && @inventorylist_card4['@i]) {
					mes "[スプラキ]";
					mes "もう名前が入っていますね……";
					return;
				}
				mes "[スプラキ]";
				mes "あなたが持っている、その";
				mes getitemname(@inventorylist_id['@i])+ "に";
				mes "直接名前を入れますね。";
				next;
				mes "[スプラキ]";
				mes "うふふ、" +strcharinfo(0)+ "さんの名前を";
				mes "入れましたよ。";
				mes "どうです？　上手くできてますか？";
				delitem @inventorylist_id['@i],1;
				getitem2 @inventorylist_id['@i],1,1,0,0,254,0,getcharid(0)&0xffff,(getcharid(0)>>16)&0xffff;
				return;
			}
		}
		cutin "v_sprakki03",2;
		mes "[スプラキ]";
		mes "手作りチョコでないと";
		mes "名前を入れることはできないです……";
		mes "ごめんなさい……";
		return;
	}
}

prt_castle.gat,0,0,0	script	V_SprakkiTimer	-1,{
	end;
Ontimer180000:
	set callfunc("ValentineSprakki",0),0;	//複数人同時アタッチ防止ロック解除
	end;
}

// スプラキ 2～4時 11～13時
prt_castle.gat,133,99,3	script	スプラキ#Valentine1	90,{
	if(gettime(3)>= 2 && gettime(3)< 4) callfunc "ValentineSprakki",2,1,1;
	if(gettime(3)>=11 && gettime(3)<13) callfunc "ValentineSprakki",1,1,1;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=2 && gettime(3)<4) || (gettime(3)>=11 && gettime(3)<13))
		hideoffnpc;
	end;
OnClock0205:
OnClock1105:
	hideoffnpc;
	end;
OnHour04:
OnHour13:
	hideonnpc;
	end;
}

// スプラキ 4～6時 15～17時
prt_castle.gat,33,106,3	script	スプラキ#Valentine2	90,{
	if(gettime(3)>= 4 && gettime(3)< 6) callfunc "ValentineSprakki",2,2,1;
	if(gettime(3)>=15 && gettime(3)<17) callfunc "ValentineSprakki",1,2,1;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=4 && gettime(3)<6) || (gettime(3)>=15 && gettime(3)<17))
		hideoffnpc;
	end;
OnClock0405:
OnClock1505:
	hideoffnpc;
	end;
OnHour06:
OnHour17:
	hideonnpc;
	end;
}

// スプラキ 7～9時 21～23時
prt_castle.gat,169,168,3	script	スプラキ#Valentine3	90,{
	if(gettime(3)>= 7 && gettime(3)< 9) callfunc "ValentineSprakki",4,3,1;
	if(gettime(3)>=21 && gettime(3)<23) callfunc "ValentineSprakki",5,3,1;
	end;
OnInit:
	hideonnpc;
	if((gettime(3)>=7 && gettime(3)<9) || (gettime(3)>=21 && gettime(3)<23))
		hideoffnpc;
	end;
OnClock0705:
OnClock2105:
	hideoffnpc;
	end;
OnHour09:
OnHour23:
	hideonnpc;
	end;
}

// スプラキ 9～11時
prt_church.gat,92,115,7	script	スプラキ#Valentine4	90,{
	callfunc "ValentineSprakki",6,4,2;
	end;
OnInit:
	if(gettime(3)<9 || gettime(3)>=11)
		hideonnpc;
	end;
OnClock0905:
	hideoffnpc;
	end;
OnHour11:
	hideonnpc;
	end;
}

// スプラキ 13～15時
prt_castle.gat,32,168,3	script	スプラキ#Valentine5	90,{
	callfunc "ValentineSprakki",3,5,3;
	end;
OnInit:
	if(gettime(3)<13 || gettime(3)>=15)
		hideonnpc;
	end;
OnClock1305:
	hideoffnpc;
	end;
OnHour15:
	hideonnpc;
	end;
}

// スプラキ 17～19時
prt_castle.gat,172,102,3	script	スプラキ#Valentine6	90,{
	callfunc "ValentineSprakki",1,6,4;
	end;
OnInit:
	if(gettime(3)<17 || gettime(3)>=19)
		hideonnpc;
	end;
OnClock1705:
	hideoffnpc;
	end;
OnHour19:
	hideonnpc;
	end;
}

// スプラキ 19～21時
prt_castle.gat,165,28,3	script	スプラキ#Valentine7	90,{
	callfunc "ValentineSprakki",3,7,2;
	end;
OnInit:
	if(gettime(3)<19 || gettime(3)>=21)
		hideonnpc;
	end;
OnClock1905:
	hideoffnpc;
	end;
OnHour21:
	hideonnpc;
	end;
}

// 盗蟲用ダミーイベント
prt_castle.gat,0,0,0	script	Thiefbug#Valentine	-1,{}


//==============================================================
alberta.gat,26,243,3	script	ショコラ=バシニオ	96,{
	if((Weight*100/MaxWeight) >= 90) {
		mes "[ショコラ=バシニオ]";
		mes "お客様、荷物をたくさん";
		mes "お持ちのようですね。";
		mes "カプラさんに少しお預けになって";
		mes "きてはいかがでしょうか？";
		close;
	}
	if(QUEST_VALENTINE1==7) {
		if(countitem(7182)<5) {
			mes "[ショコラ=バシニオ]";
			mes "カ……カカオ……";
			next;
			mes "[ショコラ=バシニオ]";
			mes "あぁ……ごめんなさい。";
			mes "カカオを持っていらした";
			mes "配達員の方かと思いました。";
			mes "やっぱり注文した分の";
			mes "カカオをお持ちではありませんね。";
			close;
		}
		mes "[ショコラ=バシニオ]";
		mes "カ……カカオー!!!";
		mes "そそそそのカカオは";
		mes "どどこに？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "どこにって……";
		mes "私はただ、これを届けに";
		mes "来ただけですけど？";
		mes "ショコラ=バシニオさん";
		mes "じゃないのですか？";
		mes "間違えたか……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "いいえ！　よく来てくださいました！";
		mes "それにしても、なぜこんなに";
		mes "遅くなったのでしょうか……";
		mes "お店が開けなくなるところでしたよ～。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "持っていらしたカカオは";
		mes "私へくださいな。";
		mes "もう、遅かったんですから、";
		mes "配達料はこれで構いませんでしょ？";
		delitem 7182,5;
		getitem 558,1;
		set QUEST_VALENTINE1,8;
		close;
	}
	if(QUEST_VALENTINE1 >= 8 && QUEST_VALENTINE2 != 11) {
		mes "[ショコラ=バシニオ]";
		mes "いらっしゃいませ、";
		mes "「バシニオチョコレート」です。";
		mes "今は申し訳ないんですが、";
		mes "少数の販売はお断りさせて";
		mes "いただいているんです。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "でも、カカオを";
		mes "届けてくださった方ですから、";
		mes "お売りしますよ。";
		mes "チョコレートをお求めですか？";
		mes "一つ2,000Zenyになりますが……";
		next;
		if(select("チョコレートをください","やめる")==2) {
			mes "[ショコラ=バシニオ]";
			mes "え～";
			mes "チョコレートをあげる方とか";
			mes "いらっしゃらないんですか？";
			mes "ブ～";
			mes "おいしいのに、残念ですわ～。";
			close;
		}
		mes "[ショコラ=バシニオ]";
		mes "今年はママもお店ができず、";
		mes "私が一人で作らないとならないし、";
		mes "限られた取引先にだけ";
		mes "お売りしているので、";
		mes "たくさんはお売りできません。";
		mes "五つまででしたら良いですよ。";
		while(1) {
			next;
			input '@num;
			if('@num==0) {
				mes "[ショコラ=バシニオ]";
				mes "え～";
				mes "チョコレートをあげる方とか";
				mes "いらっしゃらないんですか？";
				mes "ブ～";
				mes "おいしいのに、残念ですわ～。";
				close;
			}
			if(('@num>5)||('@num<0)) {
				mes "[ショコラ=バシニオ]";
				mes "申し訳ありません、";
				mes "六つ以上はご遠慮ください。";
				continue;
			}
			break;
		}
		if(Zeny<'@num*2000) {
			mes "[ショコラ=バシニオ]";
			mes "あらあら……";
			mes "お金がちょっと足りないようですよ。";
			mes "お手持ちのお金を";
			mes "確かめてくださいね。";
			mes "大丈夫です、お待ちしていますから。";
			close;
		}
		mes "[ショコラ=バシニオ]";
		mes "はい、こちらですね。";
		mes "プレゼントにぴったり！";
		mes "おいしいチョコレートです。";
		mes "オホホホホ";
		mes "どうぞお召し上がりになって、";
		mes "ごひいきにしてくださいね！";
		set Zeny,Zeny-('@num*2000);
		getitem 558,'@num;
		close;
	}
	mes "[ショコラ=バシニオ]";
	mes "いらっしゃいませ……";
	mes "「バシニオチョコレート」の";
	mes "ショコラです。";
	mes "今は材料が足りなくて、";
	mes "チョコレートを作ることが";
	mes "できないんですの。";
	next;
	if(QUEST_VALENTINE2==11) {
		mes "[ショコラ=バシニオ]";
		mes "はい？　レシピですか？";
		mes "ああ、スプラキさん!?";
		mes "それでは、簡単なチョコレートを";
		mes "作るためのレシピを差し上げますよ。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "う～ん、でも、材料を集めることが";
		mes "できるかわかりませんよ……";
		mes "とにかく、よろしくお伝えくださいね。";
		next;
		mes "^4A4AFF ショコラは、あちこち身の回りを";
		mes "探して、小さく折られた紙切れを";
		mes "見つけると、それを渡してきた。";
		mes "たぶんこれがそのレシピなんだろう。^000000";
		next;
		mes "[ショコラ=バシニオ]";
		mes "材料が届きましたら、";
		mes "チョコレートをたくさん作って";
		mes "売りますから、その時また";
		mes "お寄りになってくださいね～。";
		set QUEST_VALENTINE2,12;
		close;
	}
	mes "[ショコラ=バシニオ]";
	mes "また後日、いらしてください。";
	mes "本当に申し訳ございません。";
	close;
}

prt_in.gat,41,40,3	script	助手パティシエ	86,{
	if(QUEST_VALENTINE1==18) {
		mes "[アルル=オルレアン]";
		mes "どのようなご用件ですか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ある人に、チョコレート作りが上手い";
		mes "友達がいるので、あなたのところへ";
		mes "行ってみなさいと言われて……";
		next;
		mes "[アルル=オルレアン]";
		mes "お、ブレイドですか。";
		mes "それはそれは、";
		mes "よくいらっしゃいました。";
		next;
		mes "[アルル=オルレアン]";
		mes "あなたがブレイドの";
		mes "仕事を手伝ってくださったのですか？";
		mes "おかげさまで、カカオの流通が良くなり";
		mes "私も質の良い材料を";
		mes "手に入れられるようになりました。";
		next;
		mes "[アルル=オルレアン]";
		mes "あまりこんなことは普段しないのですが";
		mes "もしチョコレートをお求めに";
		mes "なりたかったらお売りいたしますよ。";
		mes "いつでもいらしてください。";
		set QUEST_VALENTINE1,19;
		close;
	}
	if(QUEST_VALENTINE1>=19) {
		mes "[アルル=オルレアン]";
		mes "いらっしゃいませ。";
		mes "チョコレートをお求めですか？";
		next;
		switch(select("はい、一つください","作って欲しいです","結構です。ご挨拶に来ました")) {
		case 1:
			mes "[アルル=オルレアン]";
			mes "はい、かしこまりました。";
			mes "お一つ2万Zenyと、少々お高く";
			mes "感じられるかもしれませんが、";
			mes "真心を込めて作らせていただいて";
			mes "おりますので……";
			next;
			mes "[アルル=オルレアン]";
			mes "恋人達に愛と希望に満ちた";
			mes "未来が訪れんことを……";
			mes "はい、聖なる祈りを込めた";
			mes "手作りチョコでございます。";
			next;
			set Zeny,Zeny-20000;
			if(Sex==0) getitem 559,1;
			if(Sex==1) getitem 560,1;
			mes "[アルル=オルレアン]";
			mes "はい、こちらです。";
			mes "ありがとうございます。";
			mes "また是非ご利用ください。";
			close;
		case 2:
			mes "[アルル=オルレアン]";
			mes "それでは、普通のチョコレートを";
			mes "7個お持ちいただけますか？";
			mes "最高の飾りつけをして";
			mes "お作りいたします。";
			if(countitem(558)<7) close;
			mes "おお、もう材料をお持ちですね。";
			mes "それでは早速お作りしましょうか？";
			next;
			if(select("お願いします","あ、待ってください")==2) {
				mes "[アルル=オルレアン]";
				mes "おお、どうしましたか？";
				mes "お客様はブレイドとご友人の";
				mes "ようでしたのでチョコレートを";
				mes "お作りしてさしあげようと……";
				mes "とはいえ、無料でお作りする";
				mes "わけにもまいりませんので……";
				close;
			}
			mes "[アルル=オルレアン]";
			mes "チョコレートには、その甘い味の";
			mes "裏側に、苦味も潜ませています。";
			mes "人と人との関係には、";
			mes "楽しい出来事もありますが、";
			mes "悲しいこともあります……";
			mes "なんとなく似ていますよね……";
			next;
			mes "[アルル=オルレアン]";
			mes "これはプレゼント用ですよね？";
			mes "飾りは派手すぎず、地味にならないよう";
			mes "がんばって作りました。";
			mes "お気に召せば幸いです。";
			next;
			delitem 558,7;
			getitem 559,1;
			mes "[アルル=オルレアン]";
			mes "はい、こちらです。";
			mes "ありがとうございます。";
			mes "また是非ご利用ください。";
			close;
		case 3:
			mes "[アルル=オルレアン]";
			mes "それはそれは。";
			mes "ごゆっくりなさっていってください。";
			mes "もしよろしければ、材料さえ";
			mes "お持ちいただければチョコレートを";
			mes "お作りしますので、遠慮なく";
			mes "おっしゃってください。";
			next;
			mes "[アルル=オルレアン]";
			mes "チョコレートを7個いただければ、";
			mes "手作りチョコにしてさしあげますよ。";
			close;
		}
	}
	mes "[アルル=オルレアン]";
	mes "どのようなご用件でこちらに";
	mes "おこしになったのでしょう？";
	mes "もしや……手作りチョコを";
	mes "お求めにいらっしゃったのですか？";
	next;
	mes "[アルル=オルレアン]";
	mes "今、材料を揃えてくれる";
	mes "取引先が、材料を仕入れることが";
	mes "できていないため、こちらにも";
	mes "届いていないのですよ……";
	next;
	mes "[アルル=オルレアン]";
	mes "せっかくおこしになったのに";
	mes "申し訳ないのですが……";
	close;
}


/*
// 旧バレンタイン
// Valentine Script 2004-02-12
alberta.gat,26,243,4	script	チョコレート商人	58,{	//男女購入可能
	mes "[マルコ=バジニオ]";
	mes "ルーンミッドガッツ王国では滅多に";
	mes "味わえない特産品！";
	mes "一口食べれば誰でも幸せにトロ～リ";
	mes "とろけるお菓子！";
	mes "自分で食べてもいいし、贈り物にも";
	mes "ピッタリだ！";
	next;
	mes "[マルコ=バジニオ]";
	mes "そんなチョコレートが ^ff0000一個";
	mes "5000zeny^000000！";
	next;
	if(select("チョコレートください！","いりません！")==1) {
		mes "[マルコ=バジニオ]";
		mes "ウホ！ありがとうございます、お客様！";
		mes "このチョコレートは職人の魂が詰まって";
		mes "いると言っても過言ではないのです！";
		mes "なので、一回のお買い上げにつき";
		mes "^ff00005個まで^000000となっております！";
		next;
		mes "[マルコ=バジニオ]";
		mes "もっと欲しいのでしたら、また後で再購";
		mes "入おねがいします！では、いくつ欲しい";
		mes "のでしょうか！";
		while(1) {
			next;
			input '@num;
			if('@num>5) {
				mes "[マルコ=バジニオ]";
				mes "ウホホホホホホ、駄目、駄目駄目！";
				mes "一回のお買い上げで5個までと説明しま";
				mes "したよね！私はたくさーんの人に、この";
				mes "チョコレートを味わって欲しいのです！";
				mes "それに、食べすぎると太ります！";
				continue;
			}
			break;
		}
		if('@num>0) {
			if(Zeny<'@num*5000) {
				mes "[マルコ=バジニオ]";
				mes "ウホ？あれあれ、あれれ……お客さん！";
				mes "お金が足りませんよ。それではチョコ";
				mes "レートを売ることは出来ません！";
				mes "私は、もうしばらくここにいますから";
				mes "お金が出来たらまたどうぞ！";
				close;
			}
			set Zeny,Zeny-'@num*5000;
			getitem 558,'@num;
			mes "[マルコ=バジニオ]";
			mes "ありがとうございます！";
			mes "私は、もうしばらくここにいますから";
			mes "チョコレートが欲しくなったら、また";
			mes "どうぞ！お待ちしております！";
			close;
		}
	}
	mes "[マルコ=バジニオ]";
	mes "ウホ？こ～んなスペシャルなチョコレー";
	mes "トが欲しくないと……残念ですね！";
	mes "今だけしか買えないスペシャルで特別な";
	mes "お菓子ですよ！考え直して、チョコレー";
	mes "トが欲しくなったら是非是非是非また";
	mes "来てください！お待ちしております！";
	close;
}

alberta.gat,29,243,4	script	チョコレート商人の恋人	53,{
	if(Sex || countitem(7182)<5 || countitem(7134)<1 || countitem(519)<1 || countitem(612)<1) {
		mes "[エステル=ローズ]";
		mes "こんにちは。実は、私の彼が売っている";
		mes "チョコレートは私が作っているんです。";
		mes "外国で、作る方法を学んできたのです。";
		next;
		mes "[エステル=ローズ]";
		mes "外国では、この時期に好きな人にチョコ";
		mes "レートをプレゼントする風習がありま";
		mes "す。甘い気持ちを、甘いチョコレートに";
		mes "託す……すばらしいと思いませんか？";
		next;
		mes "[エステル=ローズ]";
		mes "私のチョコレートが少しでもお役に立て";
		mes "ればと、たくさんたくさん、チョコレー";
		mes "トを作ったんです。";
		next;
		mes "[エステル=ローズ]";
		mes "彼は、そんな私を見て「自分に出来る";
		mes "ことをするんだ」って頑張ってチョコ";
		mes "レートを売ってくれているんです。";
		mes "その気持ちも嬉しいけど、チョコレー";
		mes "トを買ってくれた方々の笑顔が、何より";
		mes "私を幸せにしてくれるんです。";
		next;
		if(Sex) {	//男なら終了
			mes "[エステル=ローズ]";
			mes "だから、一個一個大事に大事に作って";
			mes "いるんです。自分でも美味しくできた";
			mes "と思いますし、一度召し上がってみて";
			mes "くださいね。ふう、頑張ってもっと";
			mes "作らなきゃ！";
			close;
		}
		mes "[エステル=ローズ]";
		mes "先ほども言いましたが、外国ではこの時期";
		mes "好きな人にチョコレートをプレゼント";
		mes "するんです。もし、好きな方がいるなら";
		mes "チョコレートと一緒に気持ちを伝えて";
		mes "みませんか？";
		next;
		mes "[エステル=ローズ]";
		mes "材料を持って来てくれれば、チョコレー";
		mes "トを作ります。私の彼が売っているチョ";
		mes "コレートでもいいのですが……";
		mes "お金で買うより、自分で集めた材料で";
		mes "作ったチョコレートのほうが、その……";
		next;
		mes "[エステル=ローズ]";
		mes "自分の気持ちが相手に伝わるような気が";
		mes "しませんか？";
		next;
		mes "[エステル=ローズ]";
		mes "材料ですが、メモの準備はいいですか？";
		mes "^3355ffカカオ 5個";
		mes "ミルク 1個";
		mes "乳鉢 1個";
		mes "携帯用溶鉱炉 1個^000000";
		next;
		mes "[エステル=ローズ]";
		mes "準備ができたら、教えてください。";
		mes "美味しいチョコレートを作らせて";
		mes "いただきます。";
		close;
	}
	mes "[エステル=ローズ]";
	mes "準備が出来たんですね！では、早速腕を";
	mes "奮わせていただきます！";
	mes "あ、隣にいる彼には内緒ですよ。";
	next;
	delitem 7182,5;
	delitem 7134,1;
	delitem 519,1;
	delitem 612,1;
	getitem 558,1;
	mes "[エステル=ローズ]";
	mes "はい、出来上がりました！";
	mes "プレゼントなさるのですか？";
	mes "気持ちが伝わるといいですね。";
	mes "幸せになってください～。";
	close;
}

prt_castle.gat,42,35,3	script	王宮デザート職人	47,{
	if(Sex) {
		mes "[シャルル=オルレアン]";
		mes "ボンジュ～ル_ムッシュー。ワタクシは";
		mes "遥か遠い場所から芸術を生み出すため、";
		mes "このアトリエに舞い降りたところなの";
		mes "です。";
		next;
		mes "[シャルル=オルレアン]";
		mes "オゥ、ノンノン！私の清らかな瞳は";
		mes "愛らしい女性のみを映す鏡なのです。";
		next;
		mes "[シャルル=オルレアン]";
		mes "オゥ～、それでなくても忙しいのに";
		mes "このシャルル=オルレアンを煩わせる";
		mes "なんて。オゥ～、ノンノンノン。";
		close;
	}
	mes "[シャルル=オルレアン]";
	mes "オゥ、マドモアゼル！";
	mes "貴方がそこにいるだけで、このむさ";
	mes "苦しい場所が天国に等しくなる。";
	next;
	mes "[シャルル=オルレアン]";
	mes "天使のように愛くるしい貴方が";
	mes "いったい何用でここにいらしたのかな？";
	mes "ワタクシめでよければ、何でも願いを";
	mes "聞きましょう。";
	next;
	if(select("チョコレートを作ってくれますか？","お疲れ様です。")==2) {
		mes "[シャルル=オルレアン]";
		mes "オゥ、その一言……ワタクシの存在を";
		mes "無に帰すような……その氷の刃のような";
		mes "一言が、私の身を削り、魂さえ痩せ衰え";
		mes "させてしまう……";
		next;
		mes "[シャルル=オルレアン]";
		mes "オゥ、マドモアゼル！";
		mes "どうすればどうすれば……貴方の心を";
		mes "再びワタクシの虜と出来るのか!?";
		close;
	}
	if(countitem(558)<3) {
		mes "[シャルル=オルレアン]";
		mes "オゥ、マドモアゼル！";
		mes "ワタクシは神でも錬金術師でもないので";
		mes "す。変な材料から芸術品を創り出すこと";
		mes "など出来ません！そして、平凡なアイテ";
		mes "ムから平凡な作品を作るなど、偉大な芸";
		mes "術家のワタクシには不可能!!";
		next;
		mes "[シャルル=オルレアン]";
		mes "ワタクシが創造する物は、世界中の誰も";
		mes "が感嘆のため息を吐く、誰にも到底真似";
		mes "出来ない芸術品なのです。";
		next;
		mes "[シャルル=オルレアン]";
		mes "ワタクシが貴方の苦労に報いる為には";
		mes "^3355ffチョコレート3個^000000が絶対必要なのです。";
		mes "それ以下でも、それ以上でもない。";
		mes "ピッタリ3個……。";
		next;
		mes "[シャルル=オルレアン]";
		mes "マドモアゼルの光輝く美貌と華奢な身に";
		mes "隠された強靭な意志なら、きっと手に";
		mes "入れてくることが可能でしょう。";
		next;
		mes "[シャルル=オルレアン]";
		mes "いいですか。^3355ffチョコレート3個^000000を持って";
		mes "来てください。出来ることなら火の中";
		mes "水の中、地獄の底へでも、貴方の為に";
		mes "ワタクシが直接手に入れて差し上げたい";
		mes "が、今のワタクシは王宮の業務に終始";
		mes "終われる身……オゥ……";
		next;
		mes "[シャルル=オルレアン]";
		mes "オ レヴォワー マドモアゼル……";
		mes "貴方の帰りを心からお待ちして";
		mes "おります……";
		close;
	}
	mes "[シャルル=オルレアン]";
	mes "オゥ、マドモアゼル！";
	mes "ワタクシの持てる全ての感性を持って";
	mes "貴方のチョコレートを美しくすばらしく";
	mes "煌びやかな芸術へと昇華させていただ";
	mes "きましょう！";
	next;
	mes "[シャルル=オルレアン]";
	mes "貴方の瞳という宝石が、世界中の誰もを";
	mes "魅了する、透明で神秘的な愛の光を放つ";
	mes "ように……";
	next;
	mes "[シャルル=オルレアン]";
	mes "アン ドゥ トロワ クァトル……";
	mes "みにくいアヒルの子が美しい白鳥に変身";
	mes "したように……平凡なチョコレートが美";
	mes "しい芸術に変身するのだ……!!";
	next;
	mes "[シャルル=オルレアン]";
	mes "暖かく包み込み……そしてふんわりと";
	mes "変化するがいい！";
	mes "強靭にて、偉大なる時代の名作よ……！";
	next;
	delitem 558,3;
	getitem 559,1;
	mes "[シャルル=オルレアン]";
	mes "オゥ、フェリシタシオン！オゥ～ララ♪";
	mes "こんな素敵な作品を作り出せるとは……";
	mes "ワタクシはなんと罪深いのだ……！";
	mes "マドモアゼル、この貴方の至極の微笑み";
	mes "とも言える芸術品、気に入っていただけ";
	mes "たかな。";
	next;
	mes "[シャルル=オルレアン]";
	mes "では、オ レヴォワ～。";
	close;
}
*/
