//= Auriga Script ==============================================================
// Ragnarok Online Cursed Knight in Ghost Palace Script	by refis
//==============================================================================

dali02.gat,58,122,3	script	好奇心旺盛な騎士#cr	418,{
	mes "[好奇心旺盛な騎士]";
	mes "近くにいる近衛兵から";
	mes "助けを求められたよ。";
	mes "次元移動機が壊れたとかで、";
	mes "修理してほしいと頼まれたが";
	mes "私では力になれなかった……。";
	next;
	mes "[好奇心旺盛な騎士]";
	mes "君が機械に精通してるなら、";
	mes "彼に協力してやってくれ。";
	mes "いったい彼が何者か、";
	mes "私も知りたいんだ。";
	mes "何か事情がありそうだからね。";
	close;
}

dali02.gat,46,135,5	script	老婆#dk	846,{
	set '@f,countitem(6672);
	mes "[老婆]";
	mes "強い思いは時に強い力を持つ……。";
	if('@f == 0) {
		mes "^ff0000記憶の欠片^000000を持っていたら";
		mes "私の所に持ってきなさい。";
		mes "^ff0000レクイエム装備^000000に";
		mes "精錬をしてあげるぞよ。";
		close;
	}
	mes "むむ？　そなた……。";
	mes "^ff0000記憶の欠片^000000を持っているな。";
	mes "私に渡せばその欠片を使って、";
	mes "レクイエム装備に精錬をしてやろう。";
	next;
	switch(select("精錬する","説明を聞く","やめておく")) {
	case 1:
		break;
	case 2:
		mes "[老婆]";
		mes "記憶の欠片は思いの塊じゃ。";
		mes "この先で入手出来る";
		mes "レクイエム装備も";
		mes "強い思いが宿った装備じゃ。";
		next;
		mes "[老婆]";
		mes "私の力を使えば";
		mes "そのレクイエム装備に";
		mes "記憶の欠片を用いる事で";
		mes "いわゆる精錬と同じ効果を";
		mes "得る事が出来るんじゃ。";
		next;
		mes "[老婆]";
		mes "精錬をしたい場合は";
		mes "精錬したい防具・武器を装備した状態で";
		mes "記憶の欠片を用意して";
		mes "私に話しかけなさい。";
		mes "^ff0000記憶の欠片1つで1回^000000";
		mes "精錬をしてやろう。";
		next;
		mes "[老婆]";
		mes "その他は通常の精錬と同様じゃ。";
		mes "^ff0000精錬に失敗してしまうと";
		mes "装備が破壊されてしまう^000000。";
		mes "破壊された装備は";
		mes "^ff00002度と使えなくなる^000000から";
		mes "注意するんじゃよ。ふぉふぉふぉ。";
		close;
	case 3:
		mes "[老婆]";
		mes "そうかい。";
		close;
	}
	mes "[老婆]";
	mes "どれを精錬するんじゃ？";
	next;
	set '@menu,select(
			(getequipid(2)!=0? "^nItemID^" +getequipid(2): "体-[装備していない]"),
			(getequipid(3)!=0? "^nItemID^" +getequipid(3): "左手-[装備していない]"),
			(getequipid(4)!=0? "^nItemID^" +getequipid(4): "右手-[装備していない]"),
			(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装備していない]"),
			(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴-[装備していない]"));
	set '@menu,'@menu+1;
	set '@refine,getequiprefinerycnt('@menu);
	switch(getequipid('@menu)) {
	case 0:
		mes "[老婆]";
		mes "ぼけているのか？";
		mes "何も装備していないようじゃぞ。";
		close;
	case 1446:
	case 1499:
	case 1698:
	case 1840:
	case 1942:
	case 1998:
	case 2032:
	case 13458:
	case 15160:
	case 15161:
	case 16042:
	case 18136:
	case 20793:
	case 21022:
	case 22088:
	case 28013:
	case 28112:
	case 28711:
	case 28911:
		break;
	default:
		mes "[老婆]";
		mes "これはレクイエム装備では無い。";
		mes "私が出来るのは";
		mes "レクイエム装備だけじゃ。";
		close;
	}
	if('@refine < 3 && '@f >= 4 - '@refine) {	// 精錬値が2以下で+4までの分の記憶の欠片があるとき
		mes "[老婆]";
		mes "おやおや、この装備はまだ";
		mes "安全に精錬が可能みたいだねぇ。";
		mes "もしよかったら";
		mes "^ff0000+4まで一気に精錬する^000000事も出来るけど";
		mes "どうするんだい？";
		next;
		switch(select("1回だけ精錬","一気に精錬","やめる")) {
		case 1:
			break;
		case 2:
			set '@num,4 - '@refine;
			mes "[老婆]";
			mes "そなたの装備の精錬値は^ff0000+" +'@refine+ "^000000じゃから";
			mes "^ff0000" +'@num+ "回^000000、一気に精錬してあげよう。";
			mes "精錬していいかい？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[老婆]";
				mes "そうか……。";
				mes "気が変わったら";
				mes "また来てくれ。";
				close;
			}
			for(set '@j,0;'@j<'@num;set '@j,'@j+1)
				successrefitem '@menu;
			delitem 6672,'@num;
			mes "[老婆]";
			mes "無事に完成したようじゃな。";
			mes "良い物が出来たぞ。";
			close;
		case 3:
			mes "[老婆]";
			mes "そうか……。";
			mes "気が変わったら";
			mes "また来てくれ。";
			close;
		}
	}
	if('@refine >= 4) {
		mes "[老婆]";
		mes "ほう。この装備は既にかなり";
		mes "精錬をしてあるようじゃな。";
		mes "これから先は";
		mes "装備が壊れるかもしれない。";
		mes "壊れると^ff00002度と使えなくなるが^000000";
		mes "それでもいいかな？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[老婆]";
			mes "そうか……。";
			mes "気が変わったら";
			mes "また来てくれ。";
			close;
		}
	}
	delitem 6672,1;
	mes "[老婆]";
	mes "それでは行くぞよ！";
	mes "……ふぉっ！";
	if(getequippercentrefinery('@i) > rand(100)) {
		successrefitem '@menu;
		next;	// modif
		mes "[老婆]";
		mes "無事に完成したようじゃな。";
		mes "良い物が出来たぞ。";
		close;
	}
	else {
		failedrefitem '@menu;
		next;	// modif
		mes "[老婆]";
		mes "くっ……";
		mes "失敗してしまったようじゃ。";
		mes "すまないのう……。";
		close;
	}
OnInit:
	waitingroom "レクイエム装備精錬",0;
	end;
}

dali02.gat,43,129,5	script	近衛兵#dk	686,{
	if(BaseLevel < 100) {
		mes "[近衛兵]";
		mes "……君は……";
		mes "旅人か……？";
		mes "何にしろ君は、自分の名前を";
		mes "忘れたりなどしていない";
		mes "だろう？";
		mes "羨ましいよ……。";
		next;
		menu "どうしました？",-;
		mes "[近衛兵]";
		mes "こんな私の話を聞いて";
		mes "くれるのか……。";
		mes "詳細を話したいところだが、";
		mes "君はまだ若いようだ。";
		mes "恐らく私の話を聞いたところで";
		mes "理解できないだろう……。";
		next;
		mes "[近衛兵]";
		mes "すまない、それ程やっかいな話なんだ。";
		mes "何より私自身が、困惑しているからね。";
		mes "　";
		mes "‐これ以上、話は聞けないようだ。";
		mes "　^ff0000Baseレベルを100以上^000000にしてから";
		mes "　また来てみよう……‐";
		close;
	}
	if(checkquest(114750) & 0x8 == 0) {
		mes "‐一人の鎧で身を固めた男が";
		mes "　虚ろな顔でなにかをつぶやいている‐";
		next;
		mes "[近衛兵]";
		mes "この機械がせめて、生きていれば……。";
		mes "誰かこの機械を直せるものがいれば";
		mes "良いのだが……。";
		next;
		menu "声をかける",-;
		mes "[近衛兵]";
		mes "……君は……!?";
		mes "……。";
		mes "そうか、冒険者か。";
		mes "まさか独り言を聞かれるとは";
		mes "恥ずかしいところを見られて";
		mes "しまったな。";
		next;
		mes "‐先ほどまでの様子が嘘のように";
		mes "　男の顔に生気が宿った。‐";
		next;
		mes "[近衛兵]";
		mes "恥ついでにもう一つ、";
		mes "君はこの^FF0000壊れた次元移動機^000000を";
		mes "修理することはできないだろうか？";
		mes "恐らくこの機械こそ、私の記憶を";
		mes "呼び戻すために必要なものだと";
		mes "思うのだが……。";
		next;
		menu "記憶……？",-;
		mes "[近衛兵]";
		mes "すまない、本来は自己紹介を";
		mes "するべきなのだろうが、";
		mes "私は^0000FF記憶を失って^000000いるんだ。";
		mes "自分の名前はおろか、";
		mes "どうしてここに居るのかも私自身、";
		mes "まったくわからないんだ。";
		next;
		mes "[近衛兵]";
		mes "ただ、この壊れた次元移動機を";
		mes "みていると不意に胸に、";
		mes "よくわからない痛みが走るんだ……。";
		mes "だから恐らくこの次元移動機に";
		mes "私が記憶をなくした理由が";
		mes "あるに違いないと思ってね。";
		next;
		if(select("調べてみましょう","機械は苦手で……") == 2) {
			mes "[近衛兵]";
			mes "そうか……仕方ない。";
			mes "誰かこの機械について";
			mes "詳しい人間が通ることを";
			mes "祈っておこう。";
			next;
			mes "[近衛兵]";
			mes "すまなかった。";
			mes "話を出来ただけでも良かった。";
			mes "ありがとう。";
			close;
		}
		mes "[近衛兵]";
		mes "ありがとう、助かるよ！";
		mes "どうも私はこの手のものが";
		mes "苦手らしい……。";
		next;
		mes "^0000FF‐次元移動機の前に、";
		mes "　アプレシアが";
		mes "　立つと、次元移動機が低い";
		mes "　起動音をあげながら";
		mes "　起動し始めた……‐^000000";
		next;
		mes "[近衛兵]";
		mes "すごいな君は……！";
		mes "何もしていない？　いや。";
		mes "だとしてもこの機械が動いたのは";
		mes "君が来てくれたお陰だ。";
		next;
		mes "[近衛兵]";
		mes "さっき会ったばかりの君に";
		mes "このようなことをいうのは";
		mes "心苦しいのだが……。";
		mes "私がこの機械を使う暫くの間、";
		mes "一緒にいてもらえないだろうか？";
		next;
		mes "[近衛兵]";
		mes "君が居なければこの機械は";
		mes "動かない。ならば君にしばらく";
		mes "一緒にいてもらい、私はなるべく";
		mes "早く、自分の記憶の手がかりを";
		mes "手に入れるように努める。";
		next;
		mes "[近衛兵]";
		mes "……どうだろうか？";
		mes "やっと記憶の手がかりと";
		mes "なりそうなこの機械が";
		mes "動いたんだ……。";
		mes "このチャンスをどうしても";
		mes "逃したくないんだ。";
		next;
		if(select("力を貸す","断る") == 2) {
			mes "[近衛兵]";
			mes "……そうだな、すまない。";
			mes "やっと記憶の手がかりが";
			mes "見つかったと喜び、";
			mes "君の都合を考えていなかった。";
			next;
			mes "[近衛兵]";
			mes "何にしろ起動することは分かった。";
			mes "後は何とか、私の力で起動するよう";
			mes "試行錯誤してみようと思う。";
			mes "ここまでで、十分だ。";
			mes "本当にありがとう。";
			close;
		}
		mes "[近衛兵]";
		mes "本当か？";
		mes "君にはどれほど感謝をしても";
		mes "足りないな。";
		mes "本当に助かるよ。";
		mes "";
		next;
		mes "[近衛兵]";
		mes "さて、君にも準備が必要だろう。";
		mes "この機械を使う準備ができたら";
		mes "私に話しかけてくれるかな？";
		setquest 114750;
		compquest 114750;
		close;
	}
	mes "[近衛兵]";
	mes "君か……。";
	mes "私に何か用なのか？";
	next;
	if(select("次元の狭間を開く","何でもない") == 2) {
		mes "[近衛兵]";
		mes "そうか……。";
		mes "君さえよければ";
		mes "私の記憶を取り戻す";
		mes "手伝いをしてくれると助かる。";
		close;
	}
	if(checkquest(1261)) {
		if(checkquest(1261) & 0x2) {
			mes "[近衛兵]";
			mes "稼動するためのパワーが";
			mes "十分、充電されたようだ。";
			mes "これならもう、";
			mes "起動は可能なはずだ。";
			delquest 1261;
			delquest 114760;
			close;
		}
		mes "[近衛兵]";
		mes "今はまだ、次元移動機が";
		mes "稼動するためのパワーが";
		mes "足りないようなんだ。";
		mes "もう少し待ってくれ。";
		next;
		mes "[インフォメーション]";
		mes "‐^ff0000入場してから1回目の午前5時以降^000000";
		mes "　且つ";
		mes "　^ff0000最後の入場から1時間経過後^000000";
		mes "　に再度入場可能になります‐";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[近衛兵]";
		mes "……すまない。";
		mes "次元移動機がまだ不安定で";
		mes "あまり負荷をかけられないんだ。";
		next;
		mes "[近衛兵]";
		mes "気持ちはありがたいが、";
		mes "次元移動機の起動は";
		mes "パーティーに所属している";
		mes "パーティーリーダーに";
		mes "限らせて貰っているんだ。";
		close;
	}
	mes "[近衛兵]";
	mes "私の記憶を取り戻すために";
	mes "協力してくれるのか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[近衛兵]";
		mes "そうか……。";
		mes "無理強いはできないからな。";
		mes "今回は諦めるとしよう。";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[近衛兵]";
		mes "おや、起動出来ないようだな。";
		mes "少し待ってくれ。";
		close;
	}
	mdcreate "Cursed Knight";
	mes "[近衛兵]";
	mes "次元移動機を起動させたぞ！";
	mes "準備を整えて、まっていてくれ。";
	close;
OnInit:
	waitingroom "呪いの剣士",0;
	end;
}

dali02.gat,40,134,5	script	次元移動機	10007,{
	if(BaseLevel < 100) {
		mes "[近衛兵]";
		mes "……君は……。";
		mes "どうやらまだまだ、";
		mes "成長段階にあるという";
		mes "感じだね。";
		next;
		mes "‐^ff0000BaseLv100以上から^000000";
		mes "　進行可能です‐";
		close;
	}
	mes "‐次元移動機がある‐";
	next;
	if(select("入る","やめておく") == 2) {
		mes "[近衛兵]";
		mes "そうか……仕方ない。";
		close;
	}
	if(checkquest(1261)) {
		if(checkquest(1261) & 0x2) {
			mes "^0000ff‐呪いの剣士の入場制限が";
			mes "　解除されました。";
			mes "　近衛兵と";
			mes "　話を進めてください‐^000000";
			delquest 1261;
			delquest 114760;
			delquest 114765;
			close;
		}
		mes "[近衛兵]";
		mes "今はまだ、次元移動機が";
		mes "稼動するためのパワーが";
		mes "足りないようなんだ。";
		mes "もう少し待ってくれ。";
		next;
		mes "[インフォメーション]";
		mes "‐^ff0000入場してから1回目の午前5時以降^000000";
		mes "　且つ";
		mes "　^ff0000最後の入場から1時間経過後^000000";
		mes "　に再度入場可能になります‐";
		close;
	}
	switch(mdenter("Cursed Knight")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[Cursed Knight] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
		donpcevent getmdnpcname("#DK_Control1")+ "::OnStart";
		setquest 1261;
		setquest 114760;
		if(checkquest(114765)&0x8)
			delquest 114765;
		close2;
		//warp "1@spa.gat",42,196;
		end;
	case 1:	// パーティー未加入
		mes "‐メモリアルダンジョンを";
		mes "　生成したパーティーのメンバーのみ、";
		mes "　メモリアルダンジョンに入れます‐";
		close;
	case 2:	// ダンジョン未作成
		mes "^ff0000‐次元の狭間が生成されていません。";
		mes "　パーティーリーダーが";
		mes "　生成することができます‐^000000";
		close;
	default:	// その他エラー
		close;
	}
}

1@spa.gat,0,0,0	script	#DK_Control1	-1,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("亡霊の王宮2階");
	hideonnpc getmdnpcname("亡霊の王宮3階");
	hideonnpc getmdnpcname("亡霊の王宮4階");
	hideonnpc getmdnpcname("亡霊の王宮5階");
	hideonnpc getmdnpcname("隣国の王子#dk3");
	hideonnpc getmdnpcname("近衛兵#dk3");
	hideonnpc getmdnpcname("魔剣タルタノス#dkt");
	hideonnpc getmdnpcname("呪いの根源#dk");
	hideonnpc getmdnpcname("黒づくめの男#dk");
	hideonnpc getmdnpcname("#dk_tb");
	hideonnpc getmdnpcname("#dk_sv");
	hideonnpc getmdnpcname("#dk_tv");
	hideonnpc getmdnpcname("亡霊の王宮出口");
	hideonnpc getmdnpcname("国王#dk11");

	donpcevent getmdnpcname("国王#dk")+ "::OnStart";
	end;
}

1@spa.gat,42,201,1	script	近衛兵#dk	686,{
	mes "‐何も反応がない……。";
	mes "　まるで時が止まっているように";
	mes "　微動だにしない……‐";
	close;
OnTalk1:
	unittalk "近衛兵 : ありがたき幸せ。……この命に代えましても必ずや姫をお守りすることを陛下と、この剣に誓いましょう。";
	end;
OnTalk2:
	unittalk "近衛兵 : ……御意にございます、陛下。おや？　なにか外が騒がしいようですね。……!?　この匂いは血の匂い……。";
	end;
OnTalk3:
	unittalk "近衛兵 : 陛下!!　何かが起きていることは事実の模様……ここに居ては危険です!!　ひとまず、お部屋へお戻りください!!";
	end;
OnTalk4:
	unittalk "近衛兵 : 御意。……。姫の私室は2階、急がねば……。　彼女にもしものことがあれば私は……。";
	end;
}

1@spa.gat,41,207,4	script	黒づくめの男#dkf1	685,{
	mes "‐全身黒づくめの";
	mes "　長い髪の男が";
	mes "　大きな剣を持ち";
	mes "　目の前の二人を";
	mes "　冷ややかな目で";
	mes "　見つめている……‐";
	close;
OnTalk1:
	unittalk "謎の声 : ほう……これは珍しい。アレを見ろ、アイツは生きた人間のようだぞ。";
	end;
OnTalk2:
	unittalk "黒づくめの男 : 人間だと……？　どうしてここに人間がいる。";
	end;
OnTalk3:
	unittalk "謎の声 : まあ待て。この人間の始末はいつでも可能なんだ。そう焦る必要もない。それに……観客は多いほうがいい。";
	end;
OnTalk4:
	unittalk "黒づくめの男 : ……そういうことらしい。ならば、お前に教えてやろう。この世界はある男の記憶だ。ゆえにお前がこいつらに干渉することは出来ない。";
	end;
OnTalk5:
	unittalk "黒づくめの男 : そこでこのバカな男の顛末を見届けるといい。ただし、干渉できないのはこのバカな男にだけだ。";
	end;
OnTalk6:
	unittalk "黒づくめの男 : モンスターどもはお前に干渉することが出来る。せいぜい殺されないようにするんだな。クックックック……。";
	end;
OnTalk7:
	unittalk "謎の声 : 人間は他人の不幸が好きらしいからな……。蜜をたっぷり吸い込んだ頃にまた会おうじゃないか。";
	end;
}

1@spa.gat,41,204,5	script	国王#dk	965,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐先ほどの近衛兵が";
		mes "　国王らしき人物と会話をしている‐";
		close;
	}
	stopnpctimer;
	mes "‐先ほどの近衛兵がいたので";
	mes "　声をかけようとした瞬間……‐";
	next;
	if(checkquest(114755)&0x8) {
		if(select("会話を省略する","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("国王#dk");
			hideonnpc getmdnpcname("近衛兵#dk");
			hideonnpc getmdnpcname("黒づくめの男#dkf1");
			donpcevent getmdnpcname("#DK_NPCTimer1")+ "::OnStart";
			misceffect 904,"";
			end;
		}
	}
	mes "[謎の声]";
	mes "ほう……これは珍しい。";
	mes "アレを見ろ、アイツは生きた";
	mes "人間のようだぞ。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk1";
	next;
	mes "[黒づくめの男]";
	mes "人間だと……？";
	mes "どうしてここに人間がいる。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk2";
	next;
	mes "‐そんな言葉と共に";
	mes "　視線を感じそちらを見ると、";
	mes "　大きな剣を持った";
	mes "　一人の黒づくめの男が";
	mes "　こちらを見つめていた‐";
	cutin "sakray.bmp",2;
	next;
	cutin "sakray.bmp",255;
	mes "‐しかし何故だろう。";
	mes "　黒づくめの男の顔と声に";
	mes "　見覚えがある気がした。";
	mes "　どこかで会ったような";
	mes "　気がする……‐";
	next;
	mes "[謎の声]";
	mes "まあ待て。";
	mes "この人間の始末はいつでも";
	mes "可能なんだ。";
	mes "そう焦る必要もない。";
	mes "それに……";
	mes "観客は多いほうがいい。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk3";
	next;
	mes "‐驚いたことに、その声は";
	mes "　^FF0000禍々しい気を放つ一振りの";
	mes "　剣^000000から聞こえていた……‐";
	cutin "tartanos.bmp",3;
	next;
	cutin "tartanos.bmp",255;
	cutin "sakray.bmp",2;
	mes "[黒づくめの男]";
	mes "……そういうことらしい。";
	mes "ならば、お前に教えてやろう。";
	mes "この世界はある男の記憶だ。";
	mes "ゆえにお前がこいつらに";
	mes "干渉することは出来ない。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk4";
	next;
	mes "[黒づくめの男]";
	mes "そこでこのバカな男の";
	mes "顛末を見届けるといい。";
	mes "ただし、干渉できないのは";
	mes "このバカな男にだけだ。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk5";
	next;
	mes "[黒づくめの男]";
	mes "モンスターどもはお前に";
	mes "干渉することが出来る。";
	mes "せいぜい殺されないように";
	mes "するんだな。";
	mes "クックックック……。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk6";
	next;
	cutin "tartanos.bmp",3;
	mes "[謎の声]";
	mes "人間は他人の不幸が";
	mes "好きらしいからな……。";
	mes "蜜をたっぷり吸い込んだ";
	mes "頃にまた会おうじゃないか。";
	donpcevent getmdnpcname("黒づくめの男#dkf1")+ "::OnTalk7";
	next;
	cutin "tartanos.bmp",255;
	misceffect 454,getmdnpcname("黒づくめの男#dkf1");
	hideonnpc getmdnpcname("黒づくめの男#dkf1");
	mes "‐そして男の姿が消えた途端、";
	mes "　止まっていた時が";
	mes "　動き出したような感覚に";
	mes "　襲われた‐";
	misceffect 454,"";
	next;
	mes "[国王]";
	mes "そなたを我が娘、ティアラ姫の";
	mes "直属の近衛兵として任命する。";
	mes "そなたの卓越した剣術と忠誠心を信じよう。";
	mes "姫をよろしく頼む。";
	unittalk "国王 : そなたを我が娘、ティアラ姫の直属の近衛兵として任命する。そなたの卓越した剣術と忠誠心を信じよう。姫をよろしく頼む。";
	next;
	mes "[近衛兵]";
	mes "ありがたき幸せ。";
	mes "……この命に代えましても";
	mes "必ずや姫をお守りすることを";
	mes "陛下と、この剣に誓いましょう。";
	donpcevent getmdnpcname("近衛兵#dk")+ "::OnTalk1";
	next;
	mes "[国王]";
	mes "幸多くも今、この城を";
	mes "訪れている隣国の王子と";
	mes "我が娘との縁談もまとまりつつある。";
	mes "この縁談がまとまれば、わが国は";
	mes "今後も末永く安泰であろう。";
	unittalk "国王 : 幸多くも今、この城を訪れている隣国の王子と我が娘との縁談もまとまりつつある。この縁談がまとまれば、わが国は今後も末永く安泰であろう。";
	next;
	mes "[国王]";
	mes "娘も今はこの縁談に";
	mes "あまり乗り気ではないようだが";
	mes "きっと必ずや、わかってくれる日が";
	mes "くるであろう。";
	mes "一国の王女としてなすべき";
	mes "ことは何かということを……。";
	unittalk "国王 : 娘も今はこの縁談にあまり乗り気ではないようだがきっと必ずや、わかってくれる日がくるであろう。一国の王女としてなすべきことは何かということを……。";
	next;
	mes "[近衛兵]";
	mes "……御意にございます、陛下。";
	mes "おや？";
	mes "なにか外が騒がしいようですね。";
	mes "……!?　この匂いは血の匂い……。";
	donpcevent getmdnpcname("近衛兵#dk")+ "::OnTalk2";
	next;
	mes "[国王]";
	mes "この音は、剣戟の音なのか!?";
	mes "どうした！　なにが起こっているのだ!?";
	mes "誰か報告をするのだ！";
	unittalk "国王 : この音は、剣戟の音なのか!?　どうした！　なにが起こっているのだ!?　誰か報告をするのだ！";
	next;
	mes "[近衛兵]";
	mes "陛下!!";
	mes "何かが起きていることは";
	mes "事実の模様……";
	mes "ここに居ては危険です!!";
	mes "ひとまず、お部屋へお戻りください!!";
	donpcevent getmdnpcname("近衛兵#dk")+ "::OnTalk3";
	next;
	mes "‐さっき見た黒づくめの男が";
	mes "　言っていたモンスターという";
	mes "　言葉が脳裏を過ぎる。";
	mes "　今回の騒動と何か";
	mes "　関係があるのだろうか……？‐";
	next;
	mes "[国王]";
	mes "私のことは心配ない。";
	mes "それよりもそなたは、娘を……";
	mes "ティアラ姫を守ってやってくれ!!";
	unittalk "国王 : 私のことは心配ない。それよりもそなたは、娘を……ティアラ姫を守ってやってくれ!!";
	next;
	mes "[近衛兵]";
	mes "御意。";
	mes "……。";
	mes "姫の私室は2階、急がねば……。";
	mes "彼女にもしものことがあれば私は……。";
	donpcevent getmdnpcname("近衛兵#dk")+ "::OnTalk4";
	close2;
	hideonnpc getmdnpcname("国王#dk");
	hideonnpc getmdnpcname("近衛兵#dk");
	donpcevent getmdnpcname("#DK_NPCTimer1")+ "::OnStart";
	misceffect 904,"";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("国王#dk");
	end;
}

1@spa.gat,1,1,0	script	#DK_NPCTimer1	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	announce "若い男の声 : そうだ……。ティアラ姫の側で彼女を守ること。それだけが私の幸せ、生きがいだった。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer6000:
	announce "若い男の声 : しかし、突然のモンスターの襲来。これが全ての悲劇の始まりだった……。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer9000:
	stopnpctimer;
	announce "‐時間が速く流れるような感覚の後、北で何かが開くような音がした‐",0x9,0xffff00,0x190,20,0,0;
	misceffect 35,getmdnpcname("亡霊の王宮2階");
	hideoffnpc getmdnpcname("亡霊の王宮2階");
	donpcevent getmdnpcname("近衛兵#dk1")+ "::OnStart";
	end;
}

1@spa.gat,41,217,0	warp	亡霊の王宮2階	2,2,1@spa.gat,114,120

1@spa.gat,135,125,3	script	ティアラ姫#dk	640,{
	mes "‐美しい女性が佇んでいる。";
	mes "　どこか儚げに見えるのは";
	mes "　気のせいだろうか？‐";
	close;
OnTalk1:
	unittalk "ティアラ姫 : この城にモンスターが入り込んだと、侍女から聞きました……。それで、お父様はご無事なのですね？";
	end;
OnTalk2:
	unittalk "ティアラ姫 : ……私にとって安全で安心な場所は一つしかありません。それは昔から、ずっと変わってはおりません……。";
	end;
OnTalk3:
	unittalk "ティアラ姫 : ……ごめんなさい。モンスターが城を襲うなど、今までなかったことが起きたせいでいやな予感がぬぐえないのです……。なにか悪いことがおきそうで……。";
	end;
OnTalk4:
	unittalk "ティアラ姫 : モンスターがこの城を襲った理由は定かではありません。そしてこのような時に、貴方にこのようなことを聞くのは不謹慎かもしれないのですが……。";
	end;
OnTalk5:
	unittalk "ティアラ姫 : ……お聞かせください。あなたにとっても私は、顔も知らない隣国の殿方と結婚の契りを交わすことが望みなのでしょうか……。私は……。私の望みはあなたと……。";
	end;
}

1@spa.gat,132,122,7	script	近衛兵#dk1	686,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[近衛兵]";
		mes "……姫様、ご無事でなによりです。";
		close;
	}
	stopnpctimer;
	mes "[近衛兵]";
	mes "……姫様、ご無事でなによりです。";
	unittalk "近衛兵 : ……姫様、ご無事でなによりです。";
	next;
	if(checkquest(114755)&0x8) {
		if(select("急ぐ","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("近衛兵#dk1");
			hideonnpc getmdnpcname("ティアラ姫#dk");
			donpcevent getmdnpcname("#DK_NPCTimer2")+ "::OnStart";
			misceffect 904,"";
			end;
		}
	}
	mes "[ティアラ姫]";
	mes "この城にモンスターが入り込んだと、";
	mes "侍女から聞きました……。";
	mes "それで、お父様はご無事なのですね？";
	donpcevent getmdnpcname("ティアラ姫#dk")+ "::OnTalk1";
	next;
	mes "[近衛兵]";
	mes "ご安心ください。";
	mes "陛下は無事です。";
	mes "姫様もここではなく";
	mes "もう少し安全な場所に参りましょう。";
	mes "このままでは";
	mes "いつ危険な目にあうか……。";
	unittalk "近衛兵 : ご安心ください。陛下は無事です。姫様もここではなくもう少し安全な場所に参りましょう。このままではいつ危険な目にあうか……。";
	next;
	mes "[ティアラ姫]";
	mes "……私にとって安全で安心な場所は";
	mes "一つしかありません。";
	mes "それは昔から、ずっと変わっては";
	mes "おりません……。";
	donpcevent getmdnpcname("ティアラ姫#dk")+ "::OnTalk2";
	next;
	mes "[近衛兵]";
	mes "ティアラ姫……。";
	unittalk "近衛兵 : ティアラ姫……。";
	next;
	mes "‐ティアラ姫と近衛兵の間に";
	mes "　主従関係を超えた";
	mes "　空気と距離感を感じる‐";
	next;
	mes "[ティアラ姫]";
	mes "……ごめんなさい。";
	mes "モンスターが城を襲うなど、";
	mes "今までなかったことが起きたせいで";
	mes "いやな予感がぬぐえないのです……。";
	mes "なにか悪いことがおきそうで……。";
	donpcevent getmdnpcname("ティアラ姫#dk")+ "::OnTalk3";
	next;
	mes "[近衛兵]";
	mes "姫様、不安を感じるのは";
	mes "よくわかります。";
	mes "ですが姫様は、今後";
	mes "この国を背負って立つお方です。";
	mes "どうか気をしっかりもち、隣国の";
	mes "あの方の、よき伴侶になってください……。";
	unittalk "近衛兵 : 姫様、不安を感じるのはよくわかります。ですが姫様は、今後この国を背負って立つお方です。どうか気をしっかりもち、隣国のあの方の、よき伴侶になってください……。";
	next;
	mes "[ティアラ姫]";
	mes "モンスターがこの城を襲った";
	mes "理由は定かではありません。";
	mes "そしてこのような時に、";
	mes "貴方にこのようなことを聞くのは";
	mes "不謹慎かもしれないのですが……。";
	donpcevent getmdnpcname("ティアラ姫#dk")+ "::OnTalk4";
	next;
	mes "[ティアラ姫]";
	mes "……お聞かせください。";
	mes "あなたにとっても私は、顔も知らない";
	mes "隣国の殿方と結婚の契りを交わすことが";
	mes "望みなのでしょうか……。";
	mes "私は……。";
	mes "私の望みはあなたと……。";
	donpcevent getmdnpcname("ティアラ姫#dk")+ "::OnTalk5";
	next;
	mes "[近衛兵]";
	mes "……姫様。";
	mes "わ、私は……。";
	unittalk "近衛兵 : ……姫様。わ、私は……。";
	next;
	mes "[近衛兵]";
	mes "!?";
	mes "騒音が……近い!!";
	unittalk "近衛兵 : !?　騒音が……近い!!";
	next;
	mes "‐剣戟と人々の叫び声が";
	mes "　すぐ側に迫っているのが";
	mes "　聞こえた！‐";
	next;
	mes "[近衛兵]";
	mes "姫様！";
	mes "安全な場所までお送りします!!";
	mes "……参りましょう！";
	unittalk "近衛兵 : 姫様！　安全な場所までお送りします!!……参りましょう！";
	close2;
	hideonnpc getmdnpcname("近衛兵#dk1");
	hideonnpc getmdnpcname("ティアラ姫#dk");
	misceffect 904,"";
	donpcevent getmdnpcname("#DK_NPCTimer2")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("近衛兵#dk1");
	end;
}

1@spa.gat,1,1,0	script	#DK_NPCTimer2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	announce "若い男の声 : 美しく聡明なティアラ姫……私は……私は……。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer6000:
	announce "若い男の声 : 願わくば貴女と、永遠の時を過ごしたかった……。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer9000:
	stopnpctimer;
	hideoffnpc getmdnpcname("隣国の王子#dk3");
	end;
}

1@spa.gat,111,133,5	script	隣国の王子#dk3	470,7,7,{
	mes "‐仕立てられた上品そうな";
	mes "　服を着た男が、不気味な笑顔を";
	mes "　浮かべながら笑っている‐";
	close;
OnTouch:
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[隣国の王子]";
		mes "あの近衛兵は使えそうだ。";
		mes "とりあえず彼には今回の";
		mes "モンスターの襲撃事件の";
		mes "首謀者という役でも";
		mes "担っていただこう……。";
		mes "ククククク。";
		unittalk "隣国の王子 : あの近衛兵は使えそうだ。とりあえず彼には今回のモンスターの襲撃事件の首謀者という役でも担っていただこう。ククククク。";
		close2;
		hideonnpc getmdnpcname("隣国の王子#dk3");
		announce "‐時間が速く流れるような感覚の後、北で何かが開くような音がした‐",0x9,0xffff00,0x190,20,0,0;
		misceffect 35,getmdnpcname("亡霊の王宮3階");
		hideoffnpc getmdnpcname("亡霊の王宮3階");
		donpcevent getmdnpcname("国王#dk1")+ "::OnStart";
	}
	end;
}

1@spa.gat,117,137,0	warp	亡霊の王宮3階	2,2,1@spa.gat,60,43

1@spa.gat,28,52,7	script	騎士団長#dk	418,{
	mes "‐男は苦渋の色を浮かべた表情で、";
	mes "　近衛兵を見つめている……‐";
	close;
}

1@spa.gat,25,53,7	script	兵士#dk1	413,{
	mes "‐男は苦渋の色を浮かべた表情で、";
	mes "　近衛兵を見つめている……‐";
	close;
}

1@spa.gat,34,53,1	script	兵士#dk2	413,{
	mes "‐男は戸惑いの表情で、";
	mes "　近衛兵を見つめている……‐";
	close;
}

1@spa.gat,30,52,7	script	兵士#dk3	417,{
	mes "‐男は戸惑いの表情で、";
	mes "　近衛兵を見つめている……‐";
	close;
}

1@spa.gat,30,58,5	script	近衛兵#dk2	10018,{
	mes "‐鎖にしっかりと繋がれ、";
	mes "　身動きがとれないようだ‐";
	close;
OnTalk1:
	unittalk "近衛兵 : 誤解です！　陛下！　私は……私は断じて陛下を、この国を裏切るような行為はおこなっておりません！";
	end;
OnTalk2:
	unittalk "近衛兵 : そ、それは……。";
	end;
OnTalk3:
	unittalk "近衛兵 : ティアラ姫……。私の者のようなもののために……。";
	end;
}

1@spa.gat,32,54,1	script	国王#dk1	965,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[国王]";
		mes "ここにモンスターを呼び寄せたのが";
		mes "まさかそなただったとは……。";
		mes "一番信頼していたそなたに";
		mes "まさか裏切られるとは……な。";
		close;
	}
	stopnpctimer;
	mes "[国王]";
	mes "ここにモンスターを呼び寄せたのが";
	mes "まさかそなただったとは……。";
	mes "一番信頼していたそなたに";
	mes "まさか裏切られるとは……な。";
	unittalk "国王 : ここにモンスターを呼び寄せたのがまさかそなただったとは……。一番信頼していたそなたにまさか裏切られるとは……な。";
	next;
	if(checkquest(114755)&0x8) {
		if(select("急ぐ","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("国王#dk1");
			hideonnpc getmdnpcname("近衛兵#dk2");
			hideonnpc getmdnpcname("騎士団長#dk");
			hideonnpc getmdnpcname("兵士#dk1");
			hideonnpc getmdnpcname("兵士#dk2");
			hideonnpc getmdnpcname("兵士#dk3");
			donpcevent getmdnpcname("#DK_NPCTimer3")+ "::OnStart";
			setnpctimer 30000,getmdnpcname("#DK_NPCTimer3");
			misceffect 904,"";
			end;
		}
	}
	mes "[近衛兵]";
	mes "誤解です！　陛下！";
	mes "私は……私は断じて";
	mes "陛下を、この国を裏切るような";
	mes "行為はおこなっておりません！";
	donpcevent getmdnpcname("近衛兵#dk2")+ "::OnTalk1";
	next;
	mes "[国王]";
	mes "私もそなたを信じたい気持ちはある。";
	mes "しかし、あの方が嘘をつく理由がない。";
	mes "今一度、問おう。";
	mes "そなたに、その理由を説明できるのか？";
	unittalk "国王 : 私もそなたを信じたい気持ちはある。しかし、あの方が嘘をつく理由がない。今一度、問おう。そなたに、その理由を説明できるのか？";
	next;
	mes "[近衛兵]";
	mes "そ、それは……。";
	donpcevent getmdnpcname("近衛兵#dk2")+ "::OnTalk2";
	next;
	mes "[国王]";
	mes "そなたのこれまでの働きに免じ";
	mes "命までは、奪わん。";
	mes "我が娘もこのことを聞いてから";
	mes "床に伏した状態が続いている。";
	mes "そなたの命を奪ったと知れば";
	mes "命を落としかねないほどに……な。";
	unittalk "国王 : そなたのこれまでの働きに免じ命までは、奪わん。我が娘もこのことを聞いてから床に伏した状態が続いている。そなたの命を奪ったと知れば命を落としかねないほどに……な。";
	next;
	mes "[近衛兵]";
	mes "ティアラ姫……。";
	mes "私のようなもののために……。";
	donpcevent getmdnpcname("近衛兵#dk2")+ "::OnTalk3";
	close2;
	hideonnpc getmdnpcname("国王#dk1");
	hideonnpc getmdnpcname("近衛兵#dk2");
	hideonnpc getmdnpcname("騎士団長#dk");
	hideonnpc getmdnpcname("兵士#dk1");
	hideonnpc getmdnpcname("兵士#dk2");
	hideonnpc getmdnpcname("兵士#dk3");
	hideoffnpc getmdnpcname("近衛兵#dk3");
	hideoffnpc getmdnpcname("魔剣タルタノス#dkt");
	donpcevent getmdnpcname("#DK_NPCTimer3")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("国王#dk1");
	end;
}

1@spa.gat,1,1,0	script	#DK_NPCTimer3	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	announce "不吉な声 : この場所に珍しく人間が来たと思えば……クックック。忠誠心高き近衛兵よ、謀られたな。",0x9,0xff0000,0x190,16,0,0;
	misceffect 885,getmdnpcname("魔剣タルタノス#dkt");
	misceffect 829,getmdnpcname("魔剣タルタノス#dkt");
	end;
OnTimer6000:
	donpcevent getmdnpcname("近衛兵#dk3")+ "::OnTalk1";
	end;
OnTimer9000:
	announce "不吉な声 : 後から来た身分で、随分なご挨拶だな。我はこの世を支配するために生まれた剣、タルタノス。",0x9,0xff0000,0x190,16,0,0;
	end;
OnTimer12000:
	announce "魔剣タルタノス : もし貴様がこの状況からの脱却を願うのであれば、我と契約をするといい。さすれば命の危険が迫る姫君もまだ、助かるかもしれぬぞ？",0x9,0xff0000,0x190,16,0,0;
	end;
OnTimer15000:
	donpcevent getmdnpcname("近衛兵#dk3")+ "::OnTalk2";
	end;
OnTimer18000:
	announce "魔剣タルタノス : 特別にもう一つ教えてやろう。貴様を陥れた相手……それこそ、あの隣国の王子だ。",0x9,0xff0000,0x190,16,0,0;
	end;
OnTimer21000:
	donpcevent getmdnpcname("近衛兵#dk3")+ "::OnTalk3";
	end;
OnTimer24000:
	announce "魔剣タルタノス : クックックッ。まだ我が言葉が信じられぬようだな。しかしそうでなくては、面白くない。",0x9,0xff0000,0x190,16,0,0;
	end;
OnTimer27000:
	announce "魔剣タルタノス : では、今回だけ特別だ。面白いショーを見せてやろう。……我を手に取れ。さすれば、わかるだろう。",0x9,0xff0000,0x190,16,0,0;
	end;
OnTimer30000:
	announce "若い男の声 : 魔剣タルタノスとの邂逅……。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer33000:
	announce "若い男の声 : 魔剣を手に取る私の心にあったのは果たして姫への想いか、それとも……。",0x9,0x7cfc00,0x190,20,0,0;
	hideonnpc getmdnpcname("近衛兵#dk3");
	hideonnpc getmdnpcname("魔剣タルタノス#dkt");
	end;
OnTimer36000:
	stopnpctimer;
	misceffect 35,getmdnpcname("亡霊の王宮4階");
	hideoffnpc getmdnpcname("亡霊の王宮4階");
	donpcevent getmdnpcname("近衛兵#dk4")+ "::OnStart";
	announce "‐時間が速く流れるような感覚の後、南東で何かが開くような音がした‐",0x9,0xffff00,0x190,20,0,0;
	end;
}

1@spa.gat,31,57,5	script	近衛兵#dk3	10018,{
	end;
OnTalk1:
	unittalk "近衛兵 : 誰だ……。誰が私に語りかけている……。私のことは放っておいてくれ……。";
	end;
OnTalk2:
	unittalk "近衛兵 : 契約？　どうして、私が契約を……！　それよりも何故だ!!　何故、姫に危険が迫っている!!";
	end;
OnTalk3:
	unittalk "近衛兵 : ……隣国の王子……!?　やはりあの時見た人影は……！　……クッ……！　この鎖さえなければ……!!";
	end;
}

1@spa.gat,35,56,5	script	魔剣タルタノス#dkt	844,{}

1@spa.gat,54,28,0	warp	亡霊の王宮4階	2,2,1@spa.gat,218,186

1@spa.gat,201,214,1	script	魔剣タルタノス#dkt1	1205,{
	end;
OnTalk1:
	unittalk "魔剣タルタノス : ……その言葉に嘘はないな？　貴様と我はいまこの時から魂をともにし、我は貴様に力を与えよう！　貴様は我に血を捧げるのだ！";
	end;
OnTalk2:
	unittalk "魔剣タルタノス : 愛しの姫君はどうやら牢獄に幽閉されているようだぞ。";
	end;
}

1@spa.gat,197,218,5	script	隣国の王子#dk	470,{
	mes "‐不適な笑みを浮かべ";
	mes "　近衛兵を見つめている‐";
	close;
OnTalk1:
	unittalk "隣国の王子 : 随分と遅かったね。君があまりにも遅いからうっかり問い詰めてきた僕の義理の父と家来を殺める結果になってしまったじゃないか。";
	end;
OnTalk2:
	unittalk "隣国の王子 : しかし、人の命なんて安いものさ。そう、君がその手に握っているその剣。呪われし魔剣タルタノスに比べたらね。……この国にそれがあると知ってから僕がどれだけその魔剣を探し求めたことか……。";
	end;
OnTalk3:
	unittalk "隣国の王子 : 誰に聞いたのか知らないけれど君のいっていることは概ね正解かな。ただ、僕だってできれば命を奪うなんて野蛮なことは避けたかったんだよ？";
	end;
OnTalk4:
	unittalk "隣国の王子 : 許婚だとかいうあの姫も近衛兵の君はそんな人じゃないって泣きながら訴えてくるしさ。あんまりにもうるさいからある場所に一人で留守番してもらっているよ。";
	end;
OnTalk5:
	unittalk "隣国の王子 : なぜだ!?　呪われし魔剣タルタノスよ！　お前が仕えるべき主人はそいつじゃなくこの僕のほうが相応しいはず!!　なぜそれがわからない!?";
	end;
OnTalk6:
	unittalk "隣国の王子 : 待てっ!!　どうして僕を無視する!!　お前達も母上や父上のように僕を無能だと思ってるんだな!?　……いいだろう。僕の本当の姿を見せてやる!!";
	end;
OnTalk7:
	unittalk "呪いの根源 : グオオオオ……ッ！　見るがいい、これが僕の本当の力!!　魔剣を……世界を……統べる新しい世界の王となる者!";
	end;
OnTalk8:
	unittalk "呪いの根源 : では、魔剣を置いていけっ!! 貴様には不要なもののはず!!　何よりその魔剣を使って、あの女を助けようなど今更手遅れだ!!";
	end;
OnTalk9:
	unittalk "呪いの根源 : あの女が悪いんだよッ!!　僕が魔物を呼び込んでるとこを見た上に、誰にも殴られたことがないこの僕を殴ったんだ……この僕を……。卑怯者っていいながらさぁ……？　許せない……許せないよ……。";
	end;
}

1@spa.gat,197,218,5	script	呪いの根源#dk	2959,{}

1@spa.gat,194,214,5	script	倒れた国王#dk	956,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}
1@spa.gat,211,194,3	script	倒れた騎士団長#dk	887,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,201,198,1	script	倒れた兵士#dk	849,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,197,190,1	script	倒れた兵士#dk1	849,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,191,207,7	script	倒れた兵士#dk2	849,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,206,209,7	script	倒れた兵士#dk3	849,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,189,195,1	script	倒れた兵士#dk4	849,{
	mes "‐返事がない……。";
	mes "　殺されて間もないようだ‐";
	close;
}

1@spa.gat,199,214,1	script	近衛兵#dk4	686,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐隣国の王子と近衛兵が";
		mes "　話しているのが見える‐";
		close;
	}
	stopnpctimer;
	mes "‐隣国の王子と近衛兵が";
	mes "　話しているのが見える‐";
	next;
	if(checkquest(114755)&0x8) {
		if(select("急ぐ","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("近衛兵#dk4");
			hideonnpc getmdnpcname("魔剣タルタノス#dkt1");
			hideonnpc getmdnpcname("倒れた国王#dk");
			hideonnpc getmdnpcname("倒れた騎士団長#dk");
			hideonnpc getmdnpcname("倒れた兵士#dk");
			hideonnpc getmdnpcname("倒れた兵士#dk1");
			hideonnpc getmdnpcname("倒れた兵士#dk2");
			hideonnpc getmdnpcname("倒れた兵士#dk3");
			hideonnpc getmdnpcname("倒れた兵士#dk4");
			misceffect 904,"";
			donpcevent getmdnpcname("#DK_NPCTimer4")+ "::OnStart";
			end;
		}
	}
	mes "[近衛兵]";
	mes "……あなたが我が主に嘘を伝え";
	mes "私を今回の事件の首謀者として";
	mes "仕立て上げたというのは本当ですか。";
	unittalk "近衛兵 : ……あなたが我が主に嘘を伝え私を今回の事件の首謀者として仕立て上げたというのは本当ですか。";
	next;
	mes "[隣国の王子]";
	mes "随分と遅かったね。";
	mes "君があまりにも遅いから";
	mes "うっかり問い詰めてきた";
	mes "僕の義理の父と家来を殺める結果に";
	mes "なってしまったじゃないか。";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk1";
	next;
	mes "[隣国の王子]";
	mes "しかし、人の命なんて安いものさ。";
	mes "そう、君がその手に握っているその剣。";
	mes "呪われし魔剣タルタノスに比べたらね。";
	mes "……この国にそれがあると知ってから";
	mes "僕がどれだけその魔剣を";
	mes "探し求めたことか……。";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk2";
	next;
	mes "[近衛兵]";
	mes "この剣を手に入れるためだけに";
	mes "あなたは国王を騙し、私を陥れ";
	mes "この城にモンスターを呼び込み";
	mes "我らが同胞の命を奪い、";
	mes "ティアラ姫まで、危険な目に";
	mes "あわせようとしたのか!?";
	unittalk "近衛兵 : この剣を手に入れるためだけにあなたは国王を騙し、私を陥れこの城にモンスターを呼び込み我らが同胞の命を奪い、ティアラ姫まで、危険な目にあわせようとしたのか!?";
	next;
	mes "[隣国の王子]";
	mes "誰に聞いたのか知らないけれど";
	mes "君のいっていることは概ね正解かな。";
	mes "ただ、僕だってできれば命を奪うなんて";
	mes "野蛮なことは避けたかったんだよ？";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk3";
	next;
	mes "[隣国の王子]";
	mes "許婚だとかいうあの姫も";
	mes "近衛兵の君はそんな人じゃないって";
	mes "泣きながら訴えてくるしさ。";
	mes "あんまりにもうるさいから";
	mes "ある場所に一人で";
	mes "留守番してもらっているよ。";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk4";
	next;
	mes "[近衛兵]";
	mes "……そうか。";
	mes "これで納得がいった。";
	mes "お前が私にいったことは";
	mes "正しかったようだな、魔剣タルタノス。";
	mes "改めて……契約成立だ。";
	unittalk "近衛兵 : ……そうか。これで納得がいった。お前が私にいったことは正しかったようだな、魔剣タルタノス。改めて……契約成立だ。";
	next;
	cutin "tartanos.bmp",3;
	mes "[魔剣タルタノス]";
	mes "……その言葉に嘘はないな？";
	mes "貴様と我はいまこの時から魂をともにし、";
	mes "我は貴様に力を与えよう！";
	mes "貴様は我に血を捧げるのだ！";
	donpcevent getmdnpcname("魔剣タルタノス#dkt1")+ "::OnTalk1";
	next;
	cutin "tartanos.bmp",255;
	mes "[隣国の王子]";
	mes "なぜだ!?";
	mes "呪われし魔剣タルタノスよ！";
	mes "お前が仕えるべき主人はそいつではなく";
	mes "この僕のほうが相応しいはず!!";
	mes "なぜそれがわからない!?";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk5";
	next;
	mes "[近衛兵]";
	mes "お前に時間をかけるほど、暇ではない。";
	mes "……私はティアラ姫を探す。";
	unittalk "近衛兵 : お前に時間をかけるほど、暇ではない。……私はティアラ姫を探す。";
	next;
	mes "[魔剣タルタノス]";
	mes "愛しの姫君はどうやら";
	mes "牢獄に幽閉されて";
	mes "いるようだぞ。";
	donpcevent getmdnpcname("魔剣タルタノス#dkt1")+ "::OnTalk2";
	next;
	mes "[隣国の王子]";
	mes "待てっ!!";
	mes "どうして僕を無視する!!";
	mes "お前達も母上や父上のように";
	mes "僕を無能だと思ってるんだな!?";
	mes "……いいだろう。";
	mes "僕の本当の姿を見せてやる!!";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk6";
	next;
	cutin "tartanos.bmp",255;
	misceffect 276,getmdnpcname("隣国の王子#dk");
	hideonnpc getmdnpcname("隣国の王子#dk");
	hideoffnpc getmdnpcname("呪いの根源#dk");
	mes "[呪いの根源]";
	mes "グオオオオ……ッ！";
	mes "見るがいい、これが僕の";
	mes "本当の力!!";
	mes "魔剣を……世界を……";
	mes "統べる新しい世界の王となる者!";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk7";
	next;
	mes "[近衛兵]";
	mes "新しい世界の王だと……？";
	mes "……くだらない……。";
	mes "私はそんなもの、興味はない。";
	mes "安心しろ。";
	unittalk "近衛兵 : 新しい世界の王だと……？　……くだらない……。私はそんなもの、興味はない。安心しろ。";
	next;
	mes "[呪いの根源]";
	mes "では、魔剣を置いていけっ!!";
	mes "貴様には不要なもののはず!!";
	mes "何よりその魔剣を使って、";
	mes "あの女を助けようなど今更";
	mes "手遅れだ!!";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk8";
	next;
	mes "[近衛兵]";
	mes "姫に……彼女に……";
	mes "何をした……ッ!!";
	unittalk "近衛兵 : 姫に……彼女に……何をした……ッ!!";
	next;
	mes "[呪いの根源]";
	mes "あの女が悪いんだよッ!!";
	mes "僕が魔物を呼び込んでるとこを";
	mes "見た上に、誰にも殴られたことがない";
	mes "この僕を殴ったんだ……この僕を……。";
	mes "卑怯者っていいながらさぁ……？";
	mes "許せない……許せないよ……。";
	donpcevent getmdnpcname("隣国の王子#dk")+ "::OnTalk9";
	next;
	mes "[近衛兵]";
	mes "……こんな奴に……こんな奴に……";
	mes "姫が……国王が……ッ!!";
	unittalk "近衛兵 : ……こんな奴に……こんな奴に……姫が……国王が……ッ!!";
	next;
	mes "[近衛兵]";
	mes "その小汚い姿を私の前に";
	mes "晒すな、失せろ……！";
	unittalk "近衛兵 : その小汚い姿を私の前に晒すな、失せろ……！";
	next;
	mes "‐近衛兵が隣国の王子に";
	mes "　一太刀浴びせると";
	mes "　隣国の王子は跡形もなく";
	mes "　消滅してしまった‐";
	misceffect 565,getmdnpcname("呪いの根源#dk");
	hideonnpc getmdnpcname("呪いの根源#dk");
	close2;
	hideonnpc getmdnpcname("近衛兵#dk4");
	hideonnpc getmdnpcname("魔剣タルタノス#dkt1");
	hideonnpc getmdnpcname("倒れた国王#dk");
	hideonnpc getmdnpcname("倒れた騎士団長#dk");
	hideonnpc getmdnpcname("倒れた兵士#dk");
	hideonnpc getmdnpcname("倒れた兵士#dk1");
	hideonnpc getmdnpcname("倒れた兵士#dk2");
	hideonnpc getmdnpcname("倒れた兵士#dk3");
	hideonnpc getmdnpcname("倒れた兵士#dk4");
	donpcevent getmdnpcname("#DK_NPCTimer4")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("近衛兵#dk4");
	end;
}

1@spa.gat,1,1,0	script	#DK_NPCTimer4	139,{
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	announce "若い男の声 : もっと力があれば、違った未来が待っていたのだろうか……。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer6000:
	announce "若い男の声 : 私は残酷な運命を、理不尽な世界を、そして無力な己を呪っていた。",0x9,0x7cfc00,0x190,20,0,0;
	end;
OnTimer9000:
	stopnpctimer;
	misceffect 35,getmdnpcname("亡霊の王宮5階");
	hideoffnpc getmdnpcname("亡霊の王宮5階");
	donpcevent getmdnpcname("ティアラ姫#dk1")+ "::OnStart";
	announce "‐時間が速く流れるような感覚の後、南西で何かが開くような音がした‐",0x9,0xffff00,0x190,20,0,0;
	end;
}

1@spa.gat,178,186,0	warp	亡霊の王宮5階	2,2,1@spa.gat,186,57

1@spa.gat,213,42,7	script	近衛兵#dk5	686,{
	mes "‐ティアラ姫を抱きかかえており、";
	mes "　その表情は見えない……‐";
	close;
OnTalk1:
	unittalk "近衛兵 : ティアラ姫……!!　すぐに、腕の良い治療術師が来るはずです……!!　気をしっかりもってください……。";
	end;
OnTalk2:
	unittalk "近衛兵 : 姫……喋らない方が……。お体に障ります……。";
	end;
OnTalk3:
	unittalk "近衛兵 : そんな……身にあまるお言葉です……。それに私は、国王に対し感謝はすれど、恨むことなどこれからもございません。ですからご安心ください。";
	end;
OnTalk4:
	unittalk "近衛兵 : 姫……血が……血が……ッ！　誰か!!　誰か居ないのか!?　早く……早く姫を……姫の治療を……ッ！　お願い……だ……。";
	end;
OnTalk5:
	unittalk "近衛兵 : 失格など!!　聡明で美しく姫様ほど王女に相応しい女性はおりません……。私が……私が身分をわきまえず心惹かれたのは、そんな姫様だからこそなのです……。";
	end;
OnTalk6:
	unittalk "近衛兵 : ……姫？　ティアラ姫……？　……私の……私の……私のせい……だ……。私が守れなかった……。私が……守っていれば……!";
	end;
OnTalk7:
	unittalk "近衛兵 : ……。いや、きっとこれは悪い夢だ……。夢なんだ……現実なわけがない……。さあ、姫様。起きてください。こんなところで寝てはお体に差し障ります。";
	end;
OnTalk8:
	unittalk "近衛兵 : 姫様？　ティアラ姫……？　どうして……どうして目を開けてくれないのですかッ!?　何故、笑ってくれないのですか……!?どうして……どうして……どうし……て……。";
	end;
}

1@spa.gat,216,43,3	script	ティアラ姫#dk1	640,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐ティアラ姫と近衛兵が";
		mes "　話しているのが見える‐";
		close;
	}
	stopnpctimer;
	if(checkquest(114755)&0x8) {
		mes "‐ティアラ姫と近衛兵が";
		mes "　話しているのが見える‐";
		next;
		if(select("急ぐ","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("ティアラ姫#dk1");
			hideonnpc getmdnpcname("近衛兵#dk5");
			misceffect 904,"";
			donpcevent getmdnpcname("#DK_BattleAnnounce")+ "::OnStart";
			end;
		}
	}
	mes "[ティアラ姫]";
	mes "貴方の腕に抱かれる日が";
	mes "くるなんて……";
	mes "夢ではないのですね。";
	mes "ゴホ、ゴホッ……。";
	unittalk "ティアラ姫 : 貴方の腕に抱かれる日がくるなんて……夢ではないのですね。ゴホ、ゴホッ……。";
	next;
	mes "[近衛兵]";
	mes "ティアラ姫……!!";
	mes "すぐに、腕の良い治療術師が";
	mes "来るはずです……!!";
	mes "気をしっかりもってください……。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk1";
	next;
	mes "‐ティアラ姫の顔に生気はなく、";
	mes "　見事な装飾が施された";
	mes "　ドレスはドス黒い染みに";
	mes "　染まっていた……‐";
	next;
	mes "[ティアラ姫]";
	mes "……どうしても貴方に、";
	mes "伝えたいことがあったのです……。";
	mes "ゴホ、ゴホッ……。";
	mes "……聞いて……くれ……";
	mes "ますか……？";
	unittalk "ティアラ姫 : ……どうしても貴方に、伝えたいことがあったのです……。ゴホ、ゴホッ……。……聞いて……くれ……ますか……？";
	next;
	mes "[近衛兵]";
	mes "姫……喋らない方が……。";
	mes "お体に障ります……。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk2";
	next;
	mes "[ティアラ姫]";
	mes "大丈夫です……。";
	mes "だから聞いて……ください……。";
	mes "どうか、過ちを犯した";
	mes "私の父を許してください。";
	mes "父も本心では、貴方のことを";
	mes "信じていたはずです。";
	unittalk "ティアラ姫 : 大丈夫です……。だから聞いて……ください……。どうか、過ちを犯した私の父を許してください。父も本心では、貴方のことを信じていたはずです。";
	next;
	mes "[近衛兵]";
	mes "そんな……身にあまるお言葉です……。";
	mes "それに私は、国王に対し";
	mes "感謝はすれど、恨むことなど";
	mes "これからもございません。";
	mes "ですからご安心ください。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk3";
	next;
	mes "[ティアラ姫]";
	mes "貴方は本当に優しいのですね……。";
	mes "私が落ち込んだときや辛いとき";
	mes "いつも貴方は傍にいて慰めてくれた。";
	mes "ずっと、そんな貴方と父とこの国で";
	mes "暮らしていたかったのに……ゴホッ。";
	unittalk "ティアラ姫 : 貴方は本当に優しいのですね……。私が落ち込んだときや辛いときいつも貴方は傍にいて慰めてくれた。ずっと、そんな貴方と父とこの国で暮らしていたかったのに……ゴホッ。";
	next;
	mes "[近衛兵]";
	mes "姫……血が……血が……ッ！";
	mes "誰か!!　誰か居ないのか!?";
	mes "早く……早く姫を……";
	mes "姫の治療を……ッ！";
	mes "お願い……だ……。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk4";
	next;
	mes "[ティアラ姫]";
	mes "泣いて……いるのです……か？";
	mes "……貴方に特別な気持ちを";
	mes "抱いてしまった私をどうか、";
	mes "ゴホゴホ……許してください……。";
	mes "叶わぬ気持ちと分かっていたのに……。";
	mes "私は王女失格です……ね……。";
	unittalk "ティアラ姫 : 泣いて……いるのです……か？　……貴方に特別な気持ちを抱いてしまった私をどうか、ゴホゴホ……許してください……。叶わぬ気持ちと分かっていたのに……。私は王女失格です……ね……。";
	next;
	mes "[近衛兵]";
	mes "失格など!!　聡明で美しく";
	mes "姫様ほど王女に相応しい女性は";
	mes "おりません……。";
	mes "私が……私が身分をわきまえず";
	mes "心惹かれたのは、そんな姫様だから";
	mes "こそなのです……。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk5";
	next;
	mes "[ティアラ姫]";
	mes "……。";
	mes "……ありがとう。";
	mes "その言葉を貴方から聞け……";
	mes "私は今、誰よりも……。";
	unittalk "ティアラ姫 : ……。……ありがとう。その言葉を貴方から聞け……私は今、誰よりも……。";
	next;
	mes "[ティアラ姫]";
	mes "…………。";
	unittalk "ティアラ姫 : …………。";
	next;
	cutin "b-tiara.BMP",3;
	mes "[近衛兵]";
	mes "……姫？　ティアラ姫……？";
	mes "……私の……私の……";
	mes "私のせい……だ……。";
	mes "私が守れなかった……。";
	mes "私が……守っていれば……!";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk6";
	next;
	mes "[近衛兵]";
	mes "……。";
	mes "いや、きっとこれは悪い夢だ……。";
	mes "夢なんだ……現実なわけがない……。";
	mes "さあ、姫様。起きてください。";
	mes "こんなところで寝てはお体に";
	mes "差し障ります。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk7";
	next;
	mes "[近衛兵]";
	mes "姫様？　ティアラ姫……？";
	mes "どうして……";
	mes "どうして目を開けてくれないのですかッ!?";
	mes "何故、笑ってくれないのですか……!?";
	mes "どうして……どうして……";
	mes "どうし……て……。";
	donpcevent getmdnpcname("近衛兵#dk5")+ "::OnTalk8";
	next;
	mes "[謎の声]";
	mes "諦めろ。";
	mes "これは現実だ。";
	mes "貴様には必要だった姫も";
	mes "この世界にとっては、";
	mes "不要だったんだよ。";
	mes "だから死んだ。";
	announce "謎の声 : 諦めろ。これは現実だ。貴様には必要だった姫もこの世界にとっては、不要だったんだよ。だから死んだ。",0x9,0xff0000,0x190,20,0,0;
	next;
	mes "[謎の声]";
	mes "それなのに一方で、";
	mes "死んでも生まれ変わった者。";
	mes "世界の力の均衡を維持する";
	mes "という大義名分で、運命を弄ぶ者。";
	mes "強大な力を持ちながら、";
	mes "私利私欲のために使う者……。";
	announce "謎の声 : それなのに一方で、死んでも生まれ変わった者。世界の力の均衡を維持するという大義名分で、運命を弄ぶ者。強大な力を持ちながら、私利私欲のために使う者……。",0x9,0xff0000,0x190,20,0,0;
	next;
	mes "[謎の声]";
	mes "この世界はそんな不条理で溢れ";
	mes "かえっているんだ。";
	mes "どうだ？　このような世界、";
	mes "存在する意味はない。";
	mes "そうだろう？";
	announce "謎の声 : この世界はそんな不条理で溢れかえっているんだ。どうだ？　このような世界、存在する意味はない。そうだろう？",0x9,0xff0000,0x190,20,0,0;
	close2;
	cutin "b-tiara.BMP",255;
	hideonnpc getmdnpcname("ティアラ姫#dk1");
	hideonnpc getmdnpcname("近衛兵#dk5");
	donpcevent getmdnpcname("#DK_BattleAnnounce")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("ティアラ姫#dk1");
	end;
}

1@spa.gat,1,1,0	script	#DK_BattleAnnounce	139,{
OnStart:
	announce "冷たい声 : 姫を守れない近衛兵とは。末代までの恥だな。",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : やめろ、やめてくれ!!　私だって……私だってこれでも……。",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled1";
	areamonster '@map$,196,42,198,45,"物欲の化身",2955,4,'@label$;
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled1");
	if('@count > 0) end;
	announce "冷たい声 : あげくに、世界を憎むのか？　悪いのは全て、弱いお前だ。",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : 私は、私は……、ただ、ただ、彼女と……。",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled2";
	areamonster '@map$,196,27,198,29,"憎しみの塊",2953,2,'@label$;
	areamonster '@map$,196,27,198,29,"取り戻せぬ愛",2954,2,'@label$;
	areamonster '@map$,196,52,198,54,"憎しみの塊",2953,2,'@label$;
	areamonster '@map$,196,52,198,54,"取り戻せぬ愛",2954,2,'@label$;
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled2");
	if('@count > 0) end;
	announce "冷たい声 : いつまで魔剣などにたぶらかされ、現実から逃げ続ける？",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : いやなんだ!!　この現実を認めてしまえば、彼女は……皆は……本当に……!!",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled3";
	areamonster '@map$,202,39,204,41,"卑屈な心",2950,2,'@label$;
	areamonster '@map$,202,39,204,41,"嫉妬の炎",2951,2,'@label$;
	areamonster '@map$,189,39,191,41,"卑屈な心",2950,2,'@label$;
	areamonster '@map$,189,39,191,41,"嫉妬の炎",2951,2,'@label$;
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled3");
	if('@count > 0) end;
	announce "冷たい声 : ほう？　その嘘のために、別の命が犠牲になってもいいというのか？",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : ……そ、それは……。",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled4";
	areamonster '@map$,183,48,185,49,"臆病な心",2948,2,'@label$;
	areamonster '@map$,183,48,185,49,"羨望する影",2958,2,'@label$;
	areamonster '@map$,194,38,195,40,"臆病な心",2948,2,'@label$;
	areamonster '@map$,194,38,195,40,"羨望する影",2958,2,'@label$;
	areamonster '@map$,178,39,178,39,"臆病な心",2948,2,'@label$;
	areamonster '@map$,178,39,178,39,"羨望する影",2958,2,'@label$;
	areamonster '@map$,201,41,202,42,"臆病な心",2948,2,'@label$;
	areamonster '@map$,201,41,202,42,"羨望する影",2958,2,'@label$;
	end;
OnKilled4:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled4");
	if('@count > 0) end;
	announce "冷たい声 : お前は人を殺める。魔剣タルタノスという大義名分を盾にして……な。",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : ……。",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled5";
	areamonster '@map$,198,28,200,30,"憎しみの塊",2953,3,'@label$;
	areamonster '@map$,198,28,200,30,"取り戻せぬ愛",2954,3,'@label$;
	areamonster '@map$,201,51,203,53,"憎しみの塊",2953,3,'@label$;
	areamonster '@map$,201,51,203,53,"取り戻せぬ愛",2954,3,'@label$;
	areamonster '@map$,197,48,198,49,"憎しみの塊",2953,3,'@label$;
	areamonster '@map$,197,48,198,49,"取り戻せぬ愛",2954,3,'@label$;
	areamonster '@map$,183,35,185,37,"憎しみの塊",2953,3,'@label$;
	areamonster '@map$,183,35,185,37,"取り戻せぬ愛",2954,3,'@label$;
	areamonster '@map$,188,22,190,24,"憎しみの塊",2953,3,'@label$;
	areamonster '@map$,188,22,190,24,"取り戻せぬ愛",2954,3,'@label$;
	end;
OnKilled5:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled5");
	if('@count > 0) end;
	announce "謎の声 : ……思い出せ!!　貴様の心の底から沸きあがる憎悪を!!",0x9,0xff0000,0x190,20,0,0;
	sleep 1000;
	announce "若い男の声 : …………。",0x9,0x7cfc00,0x190,20,0,0;
	set '@map$,getmdmapname("1@spa.gat");
	set '@label$,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled6";
	areamonster '@map$,184,50,185,51,"物欲の化身",2955,2,'@label$;
	areamonster '@map$,184,50,185,51,"抑制した破壊衝動",2956,2,'@label$;
	areamonster '@map$,184,33,185,34,"憎しみの塊",2953,2,'@label$;
	areamonster '@map$,184,33,185,34,"隠された自尊心",2957,2,'@label$;
	areamonster '@map$,200,45,202,47,"取り戻せぬ愛",2954,2,'@label$;
	areamonster '@map$,200,45,202,47,"抑えられない憤怒",2949,2,'@label$;
	areamonster '@map$,198,40,199,42,"臆病な心",2948,2,'@label$;
	areamonster '@map$,198,40,199,42,"物欲の化身",2955,2,'@label$;
	areamonster '@map$,197,24,198,25,"卑屈な心",2950,2,'@label$;
	areamonster '@map$,197,24,198,25,"孤独な夢",2952,2,'@label$;
	areamonster '@map$,206,41,208,42,"嫉妬の炎",2953,2,'@label$;
	areamonster '@map$,206,41,208,42,"羨望する影",2954,2,'@label$;
	end;
OnKilled6:
	set '@count,getmapmobs(getmdmapname("1@spa.gat"),getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled6");
	if('@count > 0) end;
	announce "冷たい声 : もう一つ。魔剣タルタノスが欲する血。本当は……お前が欲しているんじゃないか？",0x9,0xadd8e6,0x190,20,0,0;
	sleep 3000;
	announce "謎の声 : 怒りを!!　虚無を!!　これは全て最初から決められていたこと……！",0x9,0xff0000,0x190,20,0,0;
	sleep 3000;
	announce "謎の声 : 貴様と共に、この世を血で染めるために……な!!",0x9,0xff0000,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : ……否。タルタノスなど、決まりごとなど関係ない……私は……私の意思で……殺すのだ。",0x9,0x7cfc00,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : 思い出した……私は呪いの剣士サクライ。自らの意思でこの世界を憎み、破壊するもの。",0x9,0x7cfc00,0x190,20,0,0;
	sleep 3000;
	announce "若い男の声 : ケイオスも、ロキも、サラも……私の邪魔をするものは殺すだけだ。",0x9,0x7cfc00,0x190,20,0,0;
	monster getmdmapname("1@spa.gat"),197,41,"呪いの根源",2959,1,getmdnpcname("#DK_BattleAnnounce")+ "::OnKilled7";
	end;
OnKilled7:
	hideoffnpc getmdnpcname("黒づくめの男#dk");
	donpcevent getmdnpcname("黒づくめの男#dk")+ "::OnStart";
	end;
}

1@spa.gat,196,44,5	script	黒づくめの男#dk	685,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐黒づくめの男が凶々しい";
		mes "　剣を片手に立っている‐";
		close;
	}
	stopnpctimer;
	if(checkquest(114755)&0x8) {
		mes "‐黒づくめの男が凶々しい";
		mes "　剣を片手に立っている‐";
		next;
		if(select("急ぐ","二人の会話を聞く") == 1) {
			mes "‐時間が瞬時に流れたのを感じた‐";
			close2;
			hideonnpc getmdnpcname("黒づくめの男#dk");
			announce "‐周辺の風景が歪み始めた。狭間から出なければならないようだ‐",0x9,0xffff00,0x190,20,0,0;
			misceffect 904,"";
			misceffect 35,getmdnpcname("亡霊の王宮出口");
			hideoffnpc getmdnpcname("亡霊の王宮出口");
			hideoffnpc getmdnpcname("国王#dk11");
			end;
		}
	}
	mes "[黒づくめの男]";
	mes "まさか捨てたはずのものが";
	mes "再度またこの世界へと";
	mes "ノコノコ舞い戻ってくるとはな。";
	mes "あのままおとなしく";
	mes "彷徨っていればよいものを。";
	unittalk "黒づくめの男 : まさか捨てたはずのものが再度またこの世界へとノコノコ舞い戻ってくるとはな。あのままおとなしく彷徨っていればよいものを。";
	next;
	cutin "cry-b.bmp",2;
	mes "[黒づくめの男]";
	mes "これで全てというわけでは";
	mes "なさそうだが……まあいい。";
	mes "どうだ？　魔剣タルタノス。";
	mes "絶望と恐怖にまみれモンスターへ";
	mes "変貌した者たちの血は。";
	unittalk "黒づくめの男 : これで全てというわけではなさそうだが……まあいい。どうだ？　魔剣タルタノス。絶望と恐怖にまみれモンスターへ変貌した者たちの血は。";
	next;
	cutin "cry-b.bmp",255;
	mes "[魔剣タルタノス]";
	mes "愚問だな、サクライ。";
	mes "我が求める血はもっともっと";
	mes "光と闇、生と死を経験した";
	mes "深紅なる甘美な血だ……。";
	unittalk "魔剣タルタノス : 愚問だな、サクライ。我が求める血はもっともっと光と闇、生と死を経験した深紅なる甘美な血だ……。";
	next;
	mes "[魔剣タルタノス]";
	mes "……ククククク。";
	mes "そしてまた会ったな、人間。";
	mes "他人の不幸の味はどうだ？";
	mes "しかし、よい余興になると";
	mes "ここまで見逃してきたが……";
	mes "そろそろ我慢の限界だ。";
	unittalk "魔剣タルタノス : ……ククククク。そしてまた会ったな、人間。他人の不幸の味はどうだ？　しかし、よい余興になるとここまで見逃してきたが……そろそろ我慢の限界だ。";
	next;
	mes "[魔剣タルタノス]";
	mes "あの人間の血を……";
	mes "我に捧げるのだ！　サクライ。";
	mes "ここまで極上の香りがする";
	mes "血の匂いを漂わせた人間は";
	mes "かなり珍しい……！";
	unittalk "魔剣タルタノス : あの人間の血を……我に捧げるのだ！　サクライ。ここまで極上の香りがする血の匂いを漂わせた人間はかなり珍しい……！";
	next;
	mes "[サクライ]";
	mes "タルタノスが興味をもつ人間……。";
	mes "物珍しさから泳がしてみたが、";
	mes "ここまでのようだな。";
	mes "……";
	mes "お前は……。";
	unittalk "サクライ : タルタノスが興味をもつ人間……。物珍しさから泳がしてみたが、ここまでのようだな。……お前は……。";
	next;
	mes "[サクライ]";
	mes "……その顔。";
	mes "そうか、お前がアレを";
	mes "この世界へと導いた";
	mes "お人よしの冒険者だったのか。";
	unittalk "サクライ : ……その顔。そうか、お前がアレをこの世界へと導いたお人よしの冒険者だったのか。";
	next;
	menu "まさか……",-;
	mes "[サクライ]";
	mes "そう、あの時の近衛兵が私だ。";
	mes "正確には、私の中から追い出した";
	mes "感情という名のくだらない存在。";
	mes "この記憶の残滓のようなもの。";
	mes "それがお前の時代に";
	mes "どういうわけか、現れたらしい。";
	unittalk "サクライ : そう、あの時の近衛兵が私だ。正確には、私の中から追い出した感情という名のくだらない存在。この記憶の残滓のようなもの。それがお前の時代にどういうわけか、現れたらしい。";
	next;
	mes "[サクライ]";
	mes "そして僅かに残ったくだらない";
	mes "正義感からお前に助けを求め、";
	mes "ここに戻ってきたようだが";
	mes "それは今、私が取り込み消滅した。";
	mes "結局お前のやったことは、";
	mes "無駄に終わったということだ。";
	unittalk "サクライ : そして僅かに残ったくだらない正義感からお前に助けを求め、ここに戻ってきたようだがそれは今、私が取り込み消滅した。結局お前のやったことは、無駄に終わったということだ。";
	next;
	mes "[魔剣タルタノス]";
	mes "サクライ。";
	mes "無駄話をしている暇があるなら";
	mes "あの者の血を早く……";
	mes "早く我に捧げるのだ……！";
	unittalk "魔剣タルタノス : サクライ。無駄話をしている暇があるならあの者の血を早く……早く我に捧げるのだ……！";
	next;
	mes "[サクライ]";
	mes "焦るな、タルタノスよ。";
	mes "……お前に問いたいことがある。";
	mes "先ほど、お前を襲ったモンスター。";
	mes "あれはこの国に住んでいた";
	mes "兵士などの元人間。";
	mes "それらを斬った感想はどうだ？";
	unittalk "サクライ : 焦るな、タルタノスよ。……お前に問いたいことがある。先ほど、お前を襲ったモンスター。あれはこの国に住んでいた兵士などの元人間。それらを斬った感想はどうだ？";
	next;
	switch(select("答えない","答える")) {
	case 1:
		mes "[サクライ]";
		mes "ほう？";
		mes "答える気はないのか。";
		mes "だが、結果は変わらない。";
		mes "モンスターであれ、元人であれ、";
		mes "命を奪ったという事実はな!!";
		mes "何にしろ……";
		unittalk "サクライ : ほう？　答える気はないのか。だが、結果は変わらない。モンスターであれ、元人であれ、命を奪ったという事実はな!!　何にしろ……";
		break;
	case 2:
		mes "[サクライ]";
		mes "ほう、お前はそう感じたのか。";
		mes "これは面白い。";
		mes "だが、結果は変わらない。";
		mes "モンスターであれ、元人であれ、";
		mes "命を奪ったという事実はな。";
		mes "何にしろ……";
		unittalk "サクライ : ほう、お前はそう感じたのか。これは面白い。だが、結果は変わらない。モンスターであれ、元人であれ、命を奪ったという事実はな。何にしろ……";
		break;
	}
	next;
	mes "[サクライ]";
	mes "この運命は他の誰でもない。";
	mes "私が弱かったゆえの結果。";
	mes "そしてその弱さが、お前を";
	mes "この時間のこの場所に";
	mes "招き入れたのだろう……。";
	unittalk "サクライ : この運命は他の誰でもない。私が弱かったゆえの結果。そしてその弱さが、お前をこの時間のこの場所に招き入れたのだろう……。";
	next;
	menu "はじめから強い人間はいない",-;
	mes "[サクライ]";
	mes "その通りだ。";
	mes "だからこそ私は、過去の自分の弱さを";
	mes "断ち切るため、ここに来たのだ。";
	mes "しかし、今はそのお陰で私はよいことを";
	mes "思いつくことができたのだから、";
	mes "お前にはひとまず、感謝しよう。";
	unittalk "サクライ : その通りだ。だからこそ私は、過去の自分の弱さを断ち切るため、ここに来たのだ。しかし、今はそのお陰で私はよいことを思いつくことができたのだから、お前にはひとまず、感謝しよう。";
	next;
	mes "[魔剣タルタノス]";
	mes "サクライ、貴様なにを……。";
	unittalk "魔剣タルタノス : サクライ、貴様なにを……。";
	next;
	mes "[サクライ]";
	mes "タルタノスよ。奴の血は";
	mes "極上の香りだといったな？";
	mes "ならばもっとその香りの質が、";
	mes "最高の状態で味わってみたいと";
	mes "思わないか……？";
	unittalk "サクライ : タルタノスよ。奴の血は極上の香りだといったな？ならばもっとその香りの質が、最高の状態で味わってみたいと思わないか……？";
	next;
	mes "[魔剣タルタノス]";
	mes "ほう……？";
	mes "貴様にはそうなる目算が";
	mes "あるということなのだな？";
	mes "良いだろう。";
	mes "貴様の企みに乗ってやろう。";
	unittalk "ほう……？　貴様にはそうなる目算があるということなのだな？　良いだろう。貴様の企みに乗ってやろう。";
	next;
	mes "[サクライ]";
	mes "ここでお前を殺しては";
	mes "その意味が失われる。";
	mes "ゆえに今回は見逃すことにする。";
	mes "お前は見知らぬ者のために、";
	mes "ノコノコと時間移動までして";
	mes "助けようとしたほどだ。";
	unittalk "サクライ : ここでお前を殺してはその意味が失われる。ゆえに今回は見逃すことにする。お前は見知らぬ者のために、ノコノコと時間移動までして助けようとしたほどだ。";
	next;
	mes "[サクライ]";
	mes "もっと世界を知り、この世の";
	mes "不条理な理に絶望するがいい。";
	mes "そして人の力の無力さを感じ";
	mes "絶望した時……お前の血は";
	mes "さぞ、想像を絶するほど甘美な味と";
	mes "なるだろう。";
	unittalk "サクライ : もっと世界を知り、この世の不条理な理に絶望するがいい。そして人の力の無力さを感じ絶望した時……お前の血はさぞ、想像を絶するほど甘美な味となるだろう。";
	next;
	mes "‐それだけいうと";
	mes "　サクライは音もなく";
	mes "　闇の中に消えた。";
	mes "　その姿に国を愛し、";
	mes "　一人の姫を守ろうとした";
	mes "　近衛兵の面影はなかった……‐";
	close2;
	hideonnpc getmdnpcname("黒づくめの男#dk");
	hideoffnpc getmdnpcname("#dk_tb");
	hideoffnpc getmdnpcname("#dk_sv");
	hideoffnpc getmdnpcname("#dk_tv");
	donpcevent getmdnpcname("#dk_tb")+ "::OnStart";
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	emotion 9,getmdnpcname("黒づくめの男#dk");
	end;
}

1@spa.gat,196,46,1	script	#dk_tb	844,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer3000:
	unittalk "優しい声 : 私は感謝しています。貴方に会えたことを……。";
	end;
OnTimer8000:
	donpcevent getmdnpcname("#dk_sv")+ "::OnTalk1";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#dk_tv")+ "::OnTalk1";
	end;
OnTimer17000:
	donpcevent getmdnpcname("#dk_tv")+ "::OnTalk2";
	end;
OnTimer22000:
	donpcevent getmdnpcname("#dk_sv")+ "::OnTalk2";
	end;
OnTimer25000:
	donpcevent getmdnpcname("#dk_sv")+ "::OnTalk3";
	end;
OnTimer28000:
	stopnpctimer;
	hideonnpc getmdnpcname("#dk_tb");
	hideonnpc getmdnpcname("#dk_sv");
	hideonnpc getmdnpcname("#dk_tv");
	announce "‐周辺の風景が歪み始めた。狭間から出なければならないようだ‐",0x9,0xffff00,0x190,20,0,0;
	misceffect 35,getmdnpcname("亡霊の王宮出口");
	hideoffnpc getmdnpcname("亡霊の王宮出口");
	hideoffnpc getmdnpcname("国王#dk11");
	end;
}

1@spa.gat,198,43,1	script	#dk_sv	844,{
	end;
OnTalk1:
	unittalk "若い男の声 : ご安心ください。これからはずっと、姫様の傍におります。もう一人にはしません……。";
	end;
OnTalk2:
	unittalk "若い男の声 : 案ずるには及ばない。一度交わした契約を忘れるものか。";
	end;
OnTalk3:
	unittalk "若い男の声 : 我が名はサクライ。我が名をゆめゆめ忘れるな。再び、相見える日までな……。";
	end;
}

1@spa.gat,196,41,1	script	#dk_tv	844,{
	end;
OnTalk1:
	unittalk "謎の声 : 忘れるな、サクライ。私と交わした血の契約を。";
	end;
OnTalk2:
	unittalk "謎の声 : 私を満足させる血を見つけるまで、貴様の魂は私のモノだ。クククククク……。";
	end;
}

1@spa.gat,204,29,1	script	国王#dk11	965,{
	if(checkquest(114765)&0x8){
		mes "[国王]";
		mes "どうかサクライを";
		mes "救ってやってくれ……。";
		close;
	}
	mes "[国王]";
	mes "……分からぬ。";
	mes "この記憶は私のものなのか？";
	mes "それとも、サクライの記憶により";
	mes "形をかろうじて保っている";
	mes "だけの存在なのか……。";
	next;
	mes "[国王]";
	mes "この存在になってから";
	mes "私が記憶しているものが、";
	mes "私自身の記憶なのか、";
	mes "サクライ自身の記憶なのか……";
	mes "記憶が混濁しており、";
	mes "分からない状態なのだ……。";
	next;
	mes "[国王]";
	mes "それでも一つだけはっきりと";
	mes "言えることがあるとすれば、";
	mes "サクライの言葉を信じず、";
	mes "我が娘の本心を見抜けなかった";
	mes "間抜けは、他の誰でもなく";
	mes "私自身ということだ。";
	next;
	mes "[国王]";
	mes "このような身ゆえ、";
	mes "私が出来る事は限られてしまうが、";
	mes "少しでもサクライと我が娘への";
	mes "罪滅ぼしになるのであれば、";
	mes "協力は惜しまない……。";
	next;
	mes "[国王]";
	mes "この空間で生き残ったという事は";
	mes "そなたも腕に覚えがあると見える。";
	mes "頼む、どうかサクライを救ってくれ。";
	next;
	mes "[国王]";
	mes "私が出来る事は少ない。";
	mes "心ばかりではあるが";
	mes "我が国に保管されていた";
	mes "装備を授けよう。";
	next;
	mes "[国王]";
	mes "それと、この記憶の欠片を";
	mes "持っていきなさい。";
	next;
	mes "[国王]";
	mes "この記憶の欠片には";
	mes "記憶の力が宿っている。";
	mes "記憶の欠片を使用することで";
	mes "我が国に保管されていた装備を";
	mes "精錬する事ができるだろう。";
	next;
	mes "[国王]";
	mes "さて、これがそなたに授ける装備だ。";
	mes "ただ、我が国に残された宝は少ない。";
	mes "必ずしもそなたが^ff0000欲しい物が";
	mes "渡せるとは限らない^000000のだ。";
	mes "すまんな……。";
	next;
	mes "[国王]";
	mes "それではこの装備を";
	mes "そなたに授けよう。";
	mes "どうかサクライを";
	mes "救ってやってくれ……。";
	if(!checkquest(114755)) {
		setquest 114755;
		compquest 114755;
	}
	setquest 114765;
	compquest 114765;
	getitem 6672,3;
	setarray '@gain,1446,1499,1698,1840,1942,1998,2032,13458,15160,15161,16042,18136,20793,21022,22088,28013,28112,28711,28911;
	getitem '@gain[rand(getarraysize('@gain))],1;
	set '@user,getmapusers("this");
	if('@user <= 1) {
		set '@bexp,400000;
		set '@jexp,400000;
	}
	else if('@user <= 5) {
		set '@bexp,500000 * '@user;
		set '@jexp,300000 + 100000 * '@user;
	}
	else {
		set '@bexp,3000000;
		set '@jexp,1000000;
	}
	getexp '@bexp,0,1;
	getexp 0,'@jexp,0;
	close;
}

1@spa.gat,210,28,0	script	亡霊の王宮出口	45,2,2,{
	mes "‐……景色が揺らいでいる。";
	mes "　そろそろ記憶の中の世界から";
	mes "　離れる時間のようだ‐";
	close2;
	warp "dali02.gat",46,129;
	end;
}
