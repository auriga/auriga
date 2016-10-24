//====================================================================
//Ragnarok Online - ExpandedSuperNovice Jobchange Script	by refis
//
//　■ CHANGE_SNV2 -> 0～7,99
//====================================================================

aldeba_in.gat,216,169,5	script	セレイ#sp2	86,{
	if(Job == Job_Novice) {
		mes "[セレイ]";
		mes "あなたはまだ平凡な道を歩く";
		mes "楽しみを知らない人なんだね！";
		mes "あなたもノービスクラブ会員に";
		mes "なりませんか？　ノービスはいいよ。";
		next;
		mes "[セレイ]";
		mes "ノービス最高！";
		mes "はっはっはっは!!";
		close;
	}
	if(Job == Job_ExpandedSuperNovice) {
		mes "[セレイ]";
		mes "以前より強くなったようだね。";
		mes "あなたなら試験をクリアできると";
		mes "思いました。";
		close;
	}
	if(CHANGE_SNV2 >= 1 && CHANGE_SNV2 <= 7) {
		mes "[セレイ]";
		mes "ノービス界では伝説となっている方が";
		mes "数日前に「コモドに用事がある」と";
		mes "言っていなくなってしまった。";
		mes "すまないがコモドまで行って、";
		mes "その方を探してきてくれませんか。";
		next;
		mes "[セレイ]";
		mes "きっとまた、^FF0000コモド^000000で";
		mes "釣りでもしているのだと思います。";
		next;
		mes "[セレイ]";
		mes "その方ならあなたが進む道を";
		mes "提示してくれると思う……。";
		close;
	}
	if(Job != Job_SuperNovice) {
		mes "[セレイ]";
		mes "ん……";
		mes "あなたはすでに平凡な道から外れ、";
		mes "もう戻れなくなってしまったようだね。";
		mes "まあ……我等の代わりに気が済むまで";
		mes "危険に生きてください。";
		close;
	}
	if(BaseLevel < 99 || JobLevel < 99) {
		mes "[セレイ]";
		mes "うむ？　あなたは我等が";
		mes "ノービスクラブの";
		mes "会員ではありませんか？";
		mes "おぉ～服装がおしゃれですね！";
		next;
		mes "[セレイ]";
		mes "これからも普通に";
		mes "食べて生きていきましょう！";
		mes "ちなみに私はトゼーレ様直属の";
		mes "ナンバーワン会員です！　えっへん！";
		next;
		mes "[セレイ]";
		mes "そうそう、スーパーノービスの";
		mes "限界を突破する方法があるらしい";
		mes "のですが……";
		mes "スーパーノービスを";
		mes "極めたらまた来てください！";
		next;
		mes "[セレイ]";
		mes "‐^FF0000BaseLv99、JobLv99^000000になったら、";
		mes "　また来よう‐";
		close;
	}
	mes "[セレイ]";
	mes "うむ？　あなたは私達ノービスクラブの";
	mes "会員ではありませんか？";
	mes "おぉ～すっかり垢抜けて……。";
	next;
	mes "[セレイ]";
	mes "うむ！　「私は強いよ」と";
	mes "顔に書いてありますね。";
	next;
	mes "[セレイ]";
	mes "気が溢れて見えるし……";
	mes "今ならばあの方の試験を";
	mes "乗り越える事ができそうですね。";
	next;
	mes "[セレイ]";
	mes "今よりもっと強くなれる方法が";
	mes "ありますが、聞きたいですか？";
	next;
	if(select("私は今のままで満足しています","もっと強くなりたいです!!") == 1) {
		mes "[セレイ]";
		mes "今のままで満足しているのであれば";
		mes "何も言うことはないですね。";
		mes "これからも普通に";
		mes "食べて生きていきましょう！";
		close;
	}
	mes "[セレイ]";
	mes "その意気や良し!!";
	mes "それではあなたには";
	mes "ある方を探してもらいたい。";
	next;
	mes "[セレイ]";
	mes "その方はノービスの世界では";
	mes "伝説的な人物なんですが、";
	mes "数日前に「コモドに用事がある」と";
	mes "言っていなくなってしまったんです。";
	next;
	mes "[セレイ]";
	mes "きっとまた、^FF0000コモド^000000で";
	mes "釣りでもしているのだと思います。";
	next;
	set CHANGE_SNV2,1;
	setquest 5092;
	mes "[セレイ]";
	mes "その方ならあなたが進む道を";
	mes "提示してくれるでしょう！";
	close;
OnInit:
	waitingroom "限界突破!!",0;
	end;
}

comodo.gat,200,75,4	script	釣り中のノービス#sp2	567,{
	if(Job == Job_ExpandedSuperNovice) {
		set '@super2,rand(1,10);
		if('@super2 == 2) {
			mes "[ノードル]";
			mes "最近の若者は根性がない!!";
			mes "根性が!!";
			next;
			mes "[ノードル]";
			mes "何でも自分で解決しようと";
			mes "思わずに楽をしようと";
			mes "している……";
			close;
		}
		else if('@super2 == 4) {
			mes "[ノードル]";
			mes "急いでばかりで、";
			mes "ゆっくりやろうとなぜ思わないのか！";
			next;
			mes "[ノードル]";
			mes "早く早く、と急ぐと、";
			mes "さらに疲れるだけなのに……。";
			close;
		}
		else if('@super2 == 8) {
			mes "[ノードル]";
			mes "誰でも頑張って努力すると、";
			mes "努力した分認められるのだよ。";
			mes "君のようにな！";
			close;
		}
		mes "[ノードル]";
		mes "肝に銘じておけ、君はノービスだ。";
		mes "ノービスはつねにノービスらしく！";
		mes "いつも楽しく平凡な生活をすればいい。";
		close;
	}
	switch(CHANGE_SNV2) {
	case 1:
		mes "[釣り中のノービス]";
		mes "静かに!!";
		mes "静かにしてくれ。";
		mes "魚が逃げてしまうから!!";
		next;
		menu "あの……もしかして……",-;
		mes "[釣り中のノービス]";
		mes "うぉぉい！　君は何だ!!";
		mes "私は静かにしてくれと言ったよな?!";
		mes "大きな声で2回も言ったよな?!";
		mes "それなのに君がうるさいから";
		mes "魚がみんな逃げてしまった";
		mes "じゃないか!!";
		next;
		mes "[釣り中のノービス]";
		mes "なんだその目は。";
		mes "君がきて、魚がみんないなくなった、";
		mes "これは事実じゃないか。";
		mes "そもそも君は何なんだ？";
		mes "なぜ私の釣りをじゃまするのかね？";
		mes "ん？ ";
		next;
		menu "セレイさんが人を探してくれと……",-;
		emotion 20;
		mes "[釣り中のノービス]";
		mes "誰に？　セレイ？";
		mes "セレイと言ったのか？";
		mes "聞いたことあるような名前だな。";
		mes "セレイ……セレイ……ん～";
		next;
		emotion 9,"";
		emotion 9;
		mes "[釣り中のノービス]";
		mes "…………";
		next;
		emotion 0;
		mes "[釣り中のノービス]";
		mes "あ～！　あ～!!";
		mes "思い出した！　思い出した!!";
		mes "^0000FFアルデバランノービスクラブ所属^000000";
		mes "セレイだろう？";
		next;
		switch(select("いいえ","そうです")) {
		case 1:
			mes "[釣り中のノービス]";
			mes "なんと～!!　違う？";
			mes "ではいったいどこのセレイ？";
			next;
			emotion 9,"";
			emotion 9;
			mes "[釣り中のノービス]";
			mes "………………";
			next;
			mes "[釣り中のノービス]";
			mes "何？";
			mes "それは重要ではない？";
			mes "では私に何の要件だ？";
			break;
		case 2:
			mes "[釣り中のノービス]";
			mes "ふふふ……そうか！";
			mes "私の記憶は正確だな！";
			mes "ふふ～ん";
			next;
			mes "[釣り中のノービス]";
			mes "それで要件はなんだ？";
			break;
		}
		next;
		mes "‐あなたは釣り中のノービスに";
		mes "　ここまで来た理由を話した‐";
		next;
		emotion 20;
		mes "[釣り中のノービス]";
		mes "うーん、";
		mes "ノービスの更に先の道か……";
		mes "簡単なようで難しい質問だな……。";
		next;
		mes "‐小さな声でぶつぶつ";
		mes "　言っている声が聞こえる‐";
		next;
		emotion 6;
		mes "[釣り中のノービス]";
		mes "セレイの奴め……";
		mes "私の久しぶりの貴重な休暇を";
		mes "邪魔するとは。";
		mes "今度会ったら……";
		next;
		mes "‐スマイルマスクを";
		mes "　被っているノービスが";
		mes "　善良そうなお面に似合わない";
		mes "　悪口を言っている‐";
		next;
		mes "[釣り中のノービス]";
		mes "はぁ～～～";
		mes "可哀そうな私の休息！";
		mes "ああ～～面倒だ～～";
		mes "本っ当に面倒だよ～～～！";
		next;
		mes "‐釣りをしていたノービスは";
		mes "　文句を言いながら";
		mes "　じたばたしている‐";
		next;
		emotion 1;
		mes "[釣り中のノービス]";
		mes "はぁ……はぁ……はぁ……";
		mes "ふう～疲れた。";
		mes "ところで君、名前は何ていうんだ？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes strcharinfo(0)+ "です。あなたは？";
		next;
		mes "[ノードル]";
		mes "私かね？";
		mes "私の名前はノードル!!";
		mes "そう！　ノービス界の生ける伝説、";
		mes "ノードル様とは私のことだ!!";
		next;
		menu "ノードルさんですね",-;
		mes "[ノードル]";
		mes "うん、そう。";
		mes "私の名前はノードルっていうんだ。";
		next;
		mes "[ノードル]";
		mes "って、うおぉい!!";
		mes "なんだよ「ノードルさんですね」って！";
		mes "言ったよね？";
		mes "私の名前はノードルって。";
		mes "ノードル様とは私のことだ～って、";
		mes "大きな声で言ったよね？";
		next;
		mes "[ノードル]";
		mes "で……";
		mes "それに対しての返答が、";
		mes "「ノードルさんですね」？";
		mes "なんともまぁ……";
		next;
		mes "[ノードル]";
		mes "そんな驚きも！　感動も！";
		mes "なんにも感じない冷たい心!!";
		mes "この私が温めてあげたい！";
		next;
		mes "[ノードル]";
		mes "なんて思わない！";
		mes "面倒だからね！";
		mes "何しろ私は休暇中なんだ！";
		next;
		mes "[ノードル]";
		mes "まあ、だいたい君が";
		mes "何を考えているのかはわかるよ。";
		mes "顔に出ているからね。";
		next;
		mes "[ノードル]";
		mes "ノードルって名前、コンドルやら";
		mes "ビートルやらと似てるなーとか";
		mes "思っていたんだろう？";
		mes "どこまでも浅はか！";
		next;
		set CHANGE_SNV2,2;
		delquest 5092;
		setquest 5093;
		mes "[ノードル]";
		mes "まあともかく！";
		mes "せっかく来たんだし、";
		mes "どうすればノービスの道を";
		mes "更に突き進むことができるか、";
		mes "考えてやろう！";
		mes "しばらくしてから来てくれ！";
		next;
		mes "‐ノードルは何か考えだしたようだ。";
		mes "　もう一度話かけてみよう‐";
		close;
	case 2:
		mes "[ノードル]";
		mes "うむ!!";
		mes "　";
		mes "‐ノードルがあなたを意味深な";
		mes "　目でくまなく見ている‐";
		next;
		mes "[ノードル]";
		mes "さっきは気づかなかったが、";
		mes "君はかなりの実力を持っている";
		mes "^1486EBスーパーノービス^000000じゃないか！";
		next;
		mes "[ノードル]";
		mes "おい！　スーパーノービスくん。";
		mes "君は私が誰なのか知っていて";
		mes "ここまで来たのか？";
		next;
		menu "ノービスの世界では伝説的な人物だとか",-;
		mes "[ノードル]";
		mes "うむ!!";
		mes "何故私が伝説として";
		mes "語り継がれているかは";
		mes "また別の機会にとっておくとして……";
		next;
		mes "[ノードル]";
		mes "おい！　スーパーノービスくん。";
		mes "私が責任を持って強くなれるよう";
		mes "手助けをしてやるから、";
		mes "私の言うことを聞きなさい!!";
		next;
		menu "断る",-,"どうして私が？",-;
		mes "[ノードル]";
		mes "だよねー、会ったばかりの人に";
		mes "そんなこと言われても困るよねー";
		mes "じゃ、また。";
		next;
		mes "[ノードル]";
		mes "って、うおぉい!!";
		mes "今はそういう会話の流れじゃ";
		mes "ないだろう?!";
		next;
		mes "[ノードル]";
		mes "まあ、ノービスの身でそれくらいの";
		mes "実力を身につけていたら、";
		mes "強気になるのも仕方ないか……。";
		next;
		mes "[ノードル]";
		mes "しかし私はめげないくじけない！";
		mes "君がなんと言おうと、";
		mes "私が気に入ったから";
		mes "私が勝手に教える。";
		mes "そして君はそれに従うのかなー？";
		mes "もう従っちゃえ！";
		next;
		menu "…………",-;
		mes "‐なんだかこの人は変だ‐";
		next;
		mes "[ノードル]";
		mes "そういうわけで、";
		mes "今の君に問題となっているのは";
		mes "いくら修練を重ねても";
		mes "これ以上強くなれない。";
		mes "そうだよね？";
		next;
		menu "そうです。これ以上強くなれません",-;
		emotion 20;
		mes "[ノードル]";
		mes "ふむ……";
		mes "となるとあの方法しかないな！";
		next;
		mes "[ノードル]";
		mes "この方法は私しか知らないし、";
		mes "この方法以外でノービスの道の";
		mes "先を切り開くことはできない。";
		next;
		mes "[ノードル]";
		mes "もう一度聞くよ？";
		mes "私が指示することを、口答えせずに";
		mes "全てやること！";
		mes "これが君が強くなる方法を";
		mes "教える条件だ。";
		mes "どうだ？　やれるな？";
		next;
		if(select("嫌です。","や……やります。") == 1) {
			mes "[ノードル]";
			mes "嫌なのーーー?!";
			mes "そこは神妙に「やります」って";
			mes "答えるところだろう?!";
			mes "まったく強情なやつだ！";
			mes "まあ、我が道を進むのも";
			mes "悪くはないけど。";
			next;
			mes "[ノードル]";
			mes "ひとつ忠告しておこう！";
			mes "常に君が正しいとは言えない。";
			mes "時には他人の話を聞くようにしなさい。";
			mes "君の為になる時もあるから。";
			mes "肝に銘じておけよ！";
			close;
		}
		set '@test,rand(1,4);
		mes "[ノードル]";
		mes "そうか！";
		mes "強くなりたいという熱意のせいかな？";
		mes "少しは素直になったようだね。";
		next;
		mes "[ノードル]";
		mes "それではさっそくだが、";
		mes "これから指示するモンスターを";
		mes "^0000FF1,000匹^000000倒して来てくれ。";
		next;
		set CHANGE_SNV2,3;
		delquest 5093;
		switch('@test) {
		case 1:
			setquest 5094;
			set '@hunt$,"ポリン";
			break;
		case 2:
			setquest 5095;
			set '@hunt$,"ルナティック";
			break;
		case 3:
			setquest 5096;
			set '@hunt$,"ファブル";
			break;
		case 4:
			setquest 5097;
			set '@hunt$,"ピッキ";
			break;
		}
		mes "[ノードル]";
		mes "^FF0000" +'@hunt$+ "^000000というモンスターを";
		mes "知っているよな？";
		next;
		mes "[ノードル]";
		mes '@hunt$+ "を^0000FF1,000匹^000000";
		mes "倒して来なさい。";
		mes "わかった？";
		mes "できませんとは言わせないよ？";
		next;
		menu "できま……",-;
		mes "[ノードル]";
		mes "どるぅぁぁああ!!";
		mes "言わせないと言っただろう！";
		next;
		mes "[ノードル]";
		mes "それに、もう忘れたのか？";
		mes "口答えも禁止だ!!";
		mes "1,000匹倒すまでは";
		mes "戻って来ないように！";
		next;
		mes "‐" +'@hunt$+ "を^0000FF1,000匹^000000";
		mes "　倒して、ノードルに報告しよう‐";
		close;
	case 3:
		set '@poring_hunt,checkquest(5094);
		set '@lunatic_hunt,checkquest(5095);
		set '@fabre_hunt,checkquest(5096);
		set '@picky_hunt,checkquest(5097);
		mes "["+strcharinfo(0)+"]";
		mes "お～いノードル。";
		next;
		emotion 23;
		mes "[ノードル]";
		mes "うあぁぁ～～～～！";
		mes "ビックリした……。";
		mes "いきなり声をかけないでくれる?!";
		mes "ビックリするから！";
		mes "それに呼び捨てはやめなさい!!";
		next;
		mes "[ノードル]";
		mes "って、あああああ！";
		mes "騒がしくするからまた魚が";
		mes "逃げちゃったじゃないか!!";
		next;
		mes "[ノードル]";
		mes "まったく……";
		mes "で、私が指示したとおり、";
		mes "モンスターを倒してきたのか？";
		next;
		if(('@poring_hunt&0x4) || ('@fabre_hunt&0x4) || ('@lunatic_hunt&0x4) || ('@picky_hunt&0x4)) {
			mes "[ノードル]";
			mes "思っていたより早いな。";
			mes "ところで私が倒して来いと言った";
			mes "モンスターはなんだったっけ？";
		}
		else {
			mes "[ノードル]";
			mes "んん～？";
			mes "おい、スーパーノービスくん。";
			mes "1,000匹倒すまでは";
			mes "戻って来るなと言ったよな？";
			next;
			mes "[ノードル]";
			mes "早く行って来なさい。";
			close;
		}
		next;
		switch(select("ポリン","ルナティック","ファブル","ピッキ","バフォメット")) {
		case 1:
			if('@poring_hunt&0x4) {
				set '@quest,5094;
			} else {
				mes "[ノードル]";
				mes "私が指示したモンスターとは";
				mes "違うじゃないか！";
				mes "ポリンを倒して来いとは";
				mes "指示してないぞ！";
				close;
			}
			break;
		case 2:
			if('@lunatic_hunt&0x4) {
				set '@quest,5095;
			} else {
				mes "[ノードル]";
				mes "私が指示したモンスターとは";
				mes "違うじゃないか！";
				mes "ルナティックを倒して来いとは";
				mes "指示してないぞ！";
				close;
			}
			break;
		case 3:
			if('@fabre_hunt&0x4) {
				set '@quest,5096;
			} else {
				mes "[ノードル]";
				mes "私が指示したモンスターとは";
				mes "違うじゃないか！";
				mes "ファブルを倒して来いとは";
				mes "指示してないぞ！";
				close;
			}
			break;
		case 4:
			if('@picky_hunt&0x4) {
				set '@quest,5097;
			} else {
				mes "[ノードル]";
				mes "私が指示したモンスターとは";
				mes "違うじゃないか！";
				mes "ピッキを倒して来いとは";
				mes "指示してないぞ！";
				close;
			}
			break;
		case 5:
			mes "[ノードル]";
			mes "そうそう、バフォメットね！";
			mes "　";
			mes "……。";
			mes "本当に私、そんな無茶なこと";
			mes "言ったっけ……？";
			mes "嘘を言うと怒るぞ！";
			close;
		}
		emotion 18;
		mes "[ノードル]";
		mes "遊び半分でやらせた事なのに……";
		mes "これは……";
		next;
		mes "[ノードル]";
		mes "あ、いや、ハハハ……";
		mes "本当に1,000匹倒して来たのか！";
		mes "信じられない根性だな。";
		next;
		mes "[ノードル]";
		mes "わかった!!　ここまでやった以上、";
		mes "ノービスの限界を突破する方法を";
		mes "教えよう。";
		next;
		mes "[ノードル]";
		mes "しかしその前に！";
		mes "ちょっと手紙が届いているんだ。";
		mes "読み終わる頃にまた話しかけてくれ。";
		next;
		mes "‐ノードルが手紙を読み始めた。";
		mes "　もう一度話かけてみよう‐";
		set CHANGE_SNV2,4;
		delquest '@quest;
		setquest 5098;
		close;
	case 4:
		emotion 7;
		mes "[ノードル]";
		mes "ああ、まったく……";
		mes "どうしてあいつは";
		mes "こうなんだ……。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ノードル？";
		next;
		mes "[ノードル]";
		mes "おわ！　すまんすまん！";
		mes "弟が久しぶりに手紙を";
		mes "送って来たんだが、";
		mes "とんでもない内容でね。";
		mes "まあ、君もちょっと";
		mes "読んでみてくれ。";
		next;
		if(select("読む","読まない") == 2) {
			mes "[ノードル]";
			mes "うんうん、他人宛の手紙を";
			mes "読むなんて、失礼だもんね！";
			next;
			mes "[ノードル]";
			mes "……。";
			next;
			mes "[ノードル]";
			mes "読めよぉぉぉっ！";
			mes "相変わらず空気の読めない奴だ！";
			mes "ほら、読んでくれ！";
			mes "君にこれから頼む事と";
			mes "関連している内容だから。";
			next;
		}
		mes "‐ノードルはくしゃくしゃに丸めた";
		mes "　手紙を広げ、あなたに手渡した‐";
		next;
		mes "‐親愛なる兄さんノードルへ";
		mes "　";
		mes "　兄さん、愛おしい弟ヌードルだよ。";
		mes "　手紙を送るのは久しぶりだね。";
		next;
		mes "　食費がなくなったから";
		mes "　お金を少し送っておくれ。";
		mes "　兄さんはお金を沢山稼いでるだろ？";
		mes "　助けてくれよ。";
		mes "　送ってくれないとあの時の××××‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（酷くしわくちゃになっていて、";
		mes "これ以上読む事ができない……）";
		next;
		mes "‐あなたはノードルの弟、";
		mes "　ヌードルからの手紙を読んで、";
		mes "　何故か不安を感じた‐";
		next;
		mes "[ノードル]";
		mes "はぁ……一人しかいない弟が";
		mes "たまに手紙をくれたかと思ったら、";
		mes "お金を送ってくれ、と……。";
		mes "あまつさえ、最後には脅しの一文。";
		mes "あぁぁ！　私の人生って!!";
		emotion 28;
		next;
		mes "‐不吉な予感がする。";
		mes "　早くこの場所から立ち去ろう‐";
		next;
		set CHANGE_SNV2,5;
		delquest 5098;
		setquest 5099;
		mes "[ノードル]";
		mes "スーパーノービス";
		if(!Sex) {
			mes strcharinfo(0)+ "ちゃん！";
		} else {
			mes strcharinfo(0)+ "くん！";
		}
		next;
		mes "[ノードル]";
		mes "授業料の代わりだと思って";
		mes "私の弟に、お金を少し渡して来てくれ。";
		mes "シュバルツバルド国内線の";
		mes "飛行船に乗っているらしいから。";
		next;
		mes "[ノードル]";
		mes "ああもう……";
		mes "あいつは昔からどうして……";
		next;
		mes "‐シュバルツバルド国内線の";
		mes "　飛行船に乗っているヌードルに";
		mes "　お金を渡しに行こう‐";
		close;
	case 5:
		mes "[ノードル]";
		mes "あれ？　もう行って来たのか？";
		next;
		menu "いくら渡せばいいんですか？",-;
		mes "[ノードル]";
		mes "何だ……まだ行ってなかったのか？";
		mes "500,000Zenyくらい渡してくれれば";
		mes "あいつも喜ぶんじゃない？";
		close;
	case 6:
		mes "[ノードル]";
		mes "お、行って来てくれたようだね。";
		mes "今、弟から連絡を受けたよ。";
		next;
		mes "[ノードル]";
		mes "兄さんが送ってくれた人が";
		mes "500,000Zenyを渡してくれたよと";
		mes "とても自慢していたよ……。";
		next;
		mes "[ノードル]";
		mes "しかし本当に500,000Zenyも";
		mes "渡してくれるとは……";
		mes "私のメンツを立ててくれたようだね！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "もしかして……";
		next;
		mes "[ノードル]";
		mes "もしかして？　ん？";
		mes "なんだ？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "もしかして……";
		mes "これも試験の一環だった？";
		next;
		mes "[ノードル]";
		mes "!!";
		mes "あ～、そう！　そうだね!!";
		mes "これは君のお金に対するスケールを";
		mes "知る為のテストだったんだね!!";
		mes "実はそうだったんだよ!!";
		mes "はははははははは！";
		next;
		mes "[ノードル]";
		mes "……。";
		emotion 9;
		emotion 9,"";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（……考えすぎだったようだ。）";
		next;
		mes "[ノードル]";
		mes "ん？　そうだそうだ、";
		mes "忘れるところだった。";
		mes "ノービスの限界を突破する方法を";
		mes "教えないとな？";
		next;
		mes "[ノードル]";
		mes "私も君を行かせた後";
		mes "ただ遊んでいたわけでもないからな！";
		next;
		mes "[ノードル]";
		mes "ちなみに限界を突破すると、";
		mes "^FF0000ステータスもスキルもリセットされる。^000000";
		mes "昔の自分にサヨナラして、";
		mes "新しい自分に生まれ変われるんだ！";
		mes "　";
		mes "それから……";
		next;
		emotion 23;
		mes "[ノードル]";
		mes "ん～？　あれはなんだ??";
		mes "あれ……は……あーーーっ!!";
		next;
		menu "？？？？？？",-;
		emotion 19;
		mes "[ノードル]";
		mes "うわあああああ!!";
		mes "う……後ろから";
		mes "スタラクタイトゴーレムが";
		mes "群れをなしてこっちに!!";
		mes "おい！　はやく！";
		mes "はやく逃げろぉぉぉ!!";
		next;
		switch(select("はい!?","ん？")) {
		case 1:
			emotion 23,"";
			mes "‐あなたはノードルの言葉に";
			mes "　驚きながら聞きなおした‐";
			break;
		case 2:
			emotion 23,"";
			mes "‐あなたは後ろを見た。";
			mes "　後ろには何にもないと";
			mes "　言おうとした瞬間！‐";
			break;
		}
		next;
		if(sc_ison(SC_ALL_RIDING)) {
			// 未調査
			mes "[ノードル]";
			mes "何だよ……何を期待した？";
			mes "それより……";
			next;
			mes "[ノードル]";
			mes "騎乗生物に乗って楽をしているな。";
			mes "ノービスは自分の足で歩くのが";
			mes "一番自然なことなんだ！";
			mes "ノービスの魂を忘れてしまったのか？";
			next;
			mes "[ノードル]";
			mes "騎乗生物を外してから、";
			mes "再度話しかけてくれ。";
			close;
		}
		if(Weight) {
			mes "[ノードル]";
			mes "何だよ……何を期待した？";
			mes "それより……";
			next;
			mes "[ノードル]";
			mes "なんだかいろいろ持っているな。";
			mes "物に頼ってばかりだと、";
			mes "更に強くはなれないぞ。";
			next;
			mes "[ノードル]";
			mes "所持品をすべて預けてから、";
			mes "再度話しかけてくれ。";
			close;
		}
		if(checkcart()) {
			mes "[ノードル]";
			mes "何だよ……何を期待した？";
			mes "それより……";
			next;
			mes "[ノードル]";
			mes "カートを使って楽をしているな。";
			mes "自分の物くらい自力で持たないと、";
			mes "更に強くはなれないぞ。";
			next;
			mes "[ノードル]";
			mes "カートを外してから、";
			mes "再度話しかけてくれ。";
			close;
		}
		if(SkillPoint) {
			mes "[ノードル]";
			mes "何だよ……何を期待した？";
			mes "それより……";
			next;
			mes "[ノードル]";
			mes "スキルポイントが残ってるじゃないか。";
			mes "既存の物に縛られていると、";
			mes "更に強くはなれないぞ。";
			next;
			mes "[ノードル]";
			mes "スキルポイントをすべて割り振ったら";
			mes "再度話しかけてくれ。";
			close;
		}
		misceffect 90,"";
		misceffect 62,"";
		misceffect 89,"";
		set CHANGE_SNV2,7;
		delquest 5100;
		setquest 72250;
		resetstatus;
		resetskill;
		setoption 0;
		jobchange Job_ExpandedSuperNovice;
		mes "["+strcharinfo(0)+"]";
		mes "　";
		mes "!!!!!!!!";
		emotion 23,"";
		next;
		mes "[ノードル]";
		mes "うおおおおお！";
		mes "よっしゃ～～!!";
		mes "大成功～!!";
		next;
		emotion 18;
		mes "[ノードル]";
		mes "わははははは！";
		mes "いい！　いいね～!!";
		mes "その間抜けな表情!!";
		mes "一人で見るには勿体なかったよ～";
		next;
		menu "………",-;
		emotion 9,"";
		emotion 17;
		mes "[ノードル]";
		mes "あ～";
		mes "驚いたなら悪かった！";
		mes "あんまり怖い目つきで見るなよ。";
		mes "くっくっく……";
		next;
		mes "[ノードル]";
		mes "あ～、ごほん！";
		mes "私達ノービスはつまらない日常の中でも";
		mes "軽いいたずらを通じて、";
		mes "平凡で楽しい一日を作っていく";
		mes "使命と義務があるのである!!";
		next;
		mes "[ノードル]";
		mes "それはそうとして、";
		mes "何か変わった事はないか？";
		mes "体が軽くなったとか、";
		mes "今まではなかった力が";
		mes "出るようになったとか……。";
		next;
		menu "……？",-;
		emotion 1,"";
		mes "[ノードル]";
		mes "ええええええ！";
		next;
		emotion 20;
		mes "[ノードル]";
		if(!Sex) {
			mes strcharinfo(0)+ "ちゃん";
		} else {
			mes strcharinfo(0)+ "くん";
		}
		mes "本当に気付かないのか？";
		next;
		switch(select("いったい何を？","気づきました")) {
		case 1:
			mes "[ノードル]";
			mes "よし、ならば教えよう！";
			mes "君はとうとう限界を突破した！";
			mes "蛹だった君は、今、蝶になったんだ！";
			next;
			mes "[ノードル]";
			mes "簡単に言うと、これからはもっと";
			mes "強くなれるということだよ。";
			mes "強くなりたかったんじゃないのかい？";
			mes "願いが叶ったのだよ！";
			break;
		case 2:
			// 未調査
			mes "[ノードル]";
			mes "強くなりたいという君の";
			mes "願いが叶ったのだ！";
			mes "よかったじゃないか！";
			break;
		}
		next;
		mes "[ノードル]";
		mes "よ～し!!";
		mes "これからは広い世の中に出て、";
		mes "ノービスらしく自由で";
		mes "楽しい人生を生きろ、以上!!";
		next;
		mes "[ノードル]";
		mes "以上で試験は終わり！　解散!!";
		next;
		mes "‐何だかノードルの様子がおかしい。";
		mes "　早く追い払おうとしているようだ。";
		mes "　もう一度ノードルに話しかけて";
		mes "　みよう‐";
		close;
	case 7:
		mes "[ノードル]";
		mes "何だよ～！";
		mes "もう一度来ないと渡さないつもり";
		mes "だったのに来てしまったのか……。";
		next;
		mes "‐ノードルはがっかりしている‐";
		next;
		mes "[ノードル]";
		mes "まあ、来てしまったなら仕方ない！";
		mes "新しい道を歩くノービス仲間を";
		mes "祝福するために、いくつかの装備を";
		mes "プレゼントしようと思う！";
		next;
		mes "[ノードル]";
		mes "貰ってから「カバンの荷物が溢れていて";
		mes "入りません」と言わないように、";
		mes "^ff0000カバンの空きに十分な余裕があるのか";
		mes "今すぐ確認してみろ。^000000";
		next;
		if(select("あっ!!　整理してきます","大丈夫だから渡してください") == 1) {
			mes "[ノードル]";
			mes "そうか！";
			mes "私は君が戻らなくても損しないから。";
			mes "わかってるよな？";
			mes "必ず戻って来る必要はないぞ！";
			close;
		}
		if(checkitemblank() < 7) {
			mes "[ノードル]";
			mes "ほら見ろ!!　数が多すぎるだろう。";
			mes "私の言った通りだ。";
			mes "さっさと所持品を整理して来い。";
			close;
		}
		if((MaxWeight - Weight) < 5000) {
			mes "[ノードル]";
			mes "ほら見ろ!!　重くて持てないだろう。";
			mes "私の言った通りだ。";
			mes "さっさと所持品を整理して来い。";
			close;
		}
		set CHANGE_SNV2,99;
		getitem 2522,1;
		getitem 2113,1;
		getitem 2340,1;
		getitem 2416,1;
		getitem 2512,1;
		getitem 2628,1;
		getitem 5119,1;
		delquest 72250;
		setquest 201475;
		mes "[ノードル]";
		mes "私が前に使用していた";
		mes "装備なんだが、まだ使えるはずだ。";
		next;
		menu "え、新品ではなくお下がり？",-;
		emotion 6;
		mes "[ノードル]";
		mes "嫌なら返せ！";
		mes "あげたくないのを我慢して";
		mes "あげようというのに、";
		mes "何だそれは～！";
		next;
		mes "[ノードル]";
		mes "なんてね！　冗談だ！";
		mes "あげた物を返せとは言わないよ。";
		mes "では改めて祝福する事にしよう。";
		next;
		misceffect 78,"";
		misceffect 42,"";
		mes "[ノードル]";
		mes "スーパーノービス";
		mes strcharinfo(0)+ "の";
		mes "これからの道に、";
		mes "スーパーノービス守護天使の";
		mes "加護がありますように……";
		close;
	case 99:
		set CHANGE_SNV2,0;
		mes "[ノードル]";
		mes "何だ、まだいたのか？";
		mes "釣りの邪魔だ、";
		mes "早くどっか行け～！";
		close;
	default:
		mes "[釣り中のノービス]";
		mes "静かに～～～!!";
		mes "魚が逃げるから静かにしてくれ。";
		close;
	}
}

airplane.gat,33,47,5	script	ヌードル#sp2	567,{
	if(Job == Job_ExpandedSuperNovice) {
		mes "[ヌードル]";
		mes "う～わ～";
		if(!Sex) {
			mes "姉さん、うちの兄さんと";
		} else {
			mes "兄さん、うちの兄さんと";
		}
		mes "同じくらい強くなってない？";
		mes "凄い人だったんですね！";
		next;
		mes "[ヌードル]";
		mes "私もご飯をいっぱい食べて";
		mes "大きくなって、";
		mes "兄さんのように強くならないと……。";
		close;
	}
	switch(CHANGE_SNV2) {
	case 5:
		mes "[ヌードル]";
		mes "あぁぁ……飯代も全部なくなったし、";
		mes "お腹は空いたし……";
		mes "兄さんの仕送りはいつ来るんだろう？";
		next;
		menu "あの……もしかしてヌードルさん？",-;
		mes "[ヌードル]";
		mes "おわ！　ビックリした～～！";
		mes "誰ですか？　どこかで会いましたかね？";
		next;
		mes "‐あなたはヌードルに会いに来た";
		mes "　理由を説明した‐";
		next;
		mes "[ヌードル]";
		mes "そうですか!!";
		mes "兄さんの代わりに仕送りを渡しに";
		mes "来てくれたんですね？";
		next;
		mes "[ヌードル]";
		mes "うふふふ……";
		mes "それでそれで？";
		mes "兄さんはいくらくれたんですか？";
		next;
		mes "‐ヌードルが目を光らせ";
		mes "　両手を出しながら";
		mes "　お金を要求している。";
		mes "　いくら渡しますか？‐";
		next;
		if(select("渡す金がない","500,000Zenyを渡す") == 1) {
			mes "[ヌードル]";
			mes "うあぁぁ～～～～！";
			mes "兄さん嫌い～～～！";
			mes "お前も嫌い～～～!!";
			close2;
			warp "airplane.gat",70,93;
			end;
		}
		mes "[ヌードル]";
		mes "お～";
		mes "兄さんが500,000Zenyもくれたの？";
		next;
		if(Zeny < 500000) {
			mes "[ヌードル]";
			mes "ん？";
			mes "だけど500,000Zenyはどこにあるの？";
			close;
		}
		set Zeny,Zeny-500000;
		set CHANGE_SNV2,6;
		delquest 5099;
		setquest 5100;
		mes "[ヌードル]";
		mes "[ヌードル]";
		mes "へへへ、言ってみるもんだなぁ！";
		if(!Sex) {
			mes strcharinfo(0)+ "姉さん、";
		} else {
			mes strcharinfo(0)+ "兄さん、";
		}
		mes "ありがとう～！";
		next;
		mes "‐なんだか納得いかないが、";
		mes "　一応、仕送りを渡したので";
		mes "　ノードルの所に戻ることにしよう‐";
		close;
	case 6:
		mes "[ヌードル]";
		mes "うれしいな～、また度々手紙を送ろう。";
		mes "ふふふ……";
		next;
		mes "[ヌードル]";
		mes "あ、";
		if(!Sex) {
			mes strcharinfo(0)+ "姉さん！";
		} else {
			mes strcharinfo(0)+ "兄さん！";
		}
		mes "うちの兄さんには秘密だよ～？";
		close;
	default:
		mes "[ヌードル]";
		mes "あぁぁ……";
		mes "ご飯代は全部無くなったし";
		mes "お腹は減ったのに";
		mes "兄さんの仕送りはいつ来るんだろう？";
		close;
	}
}
