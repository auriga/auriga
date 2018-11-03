//==============================================================================
// Ragnarok Online XmasEvent2006 Script     by AthenaDev
//==============================================================================
xmas_in.gat,87,91,6	script	カプラディフォルテー	117,{
	cutin "kafra_01",2;
	mes "[カプラディフォルテー]";
	mes "いらっしゃいませ";
	mes "カプラサービスは";
	mes "いつも皆様のそばにいます。";
	mes "只今、クリスマス期間限定";
	mes "「ラッピングサービス」を";
	mes "ご提供しております。";
	next;
	mes "[カプラディフォルテー]";
	mes "友達や家族、恋人に特別な贈り物を";
	mes "したい方の為に、プレゼントボックスを";
	mes "紙とリボンでお包みしております。";
	mes "また包装だけでなく、贈り主の方の";
	mes "お名前もプレゼントボックスへ";
	mes "記入しております。";
	next;
	mes "[カプラディフォルテー]";
	mes "「ラッピングサービス」はクリスマス";
	mes "期間中に材料をご用意くだされば";
	mes "どなたでもご利用になれます。";
	mes "想いを伝えたい方へ心をこめた";
	mes "贈り物をなさりたければ、是非";
	mes "カプラ職員にお申し付けください。";
	close2;
	cutin "kafra_01",255;
	end;
}

xmas_in.gat,87,89,6	script	カプラテーリング	116,{
	cutin "kafra_02",2;
	mes "[カプラテーリング]";
	mes "クリスマス期間限定カプラサービス";
	mes "「ラッピングサービス」です！";
	mes "どなたが受け取ってもきっと";
	mes "喜ばれると思います。";
	next;
	switch (select("プレゼントボックスを包んでください","けっこうです")) {
	case 1:
		if(countitem(644)<1 || countitem(7174)<1 || countitem(7175)<1) {
			mes "[カプラテーリング]";
			mes "ラッピングサービスのご利用には、";
			mes "ご用意していただく物がございます。";
			mes "私は他のお客様の包装作業が";
			mes "ございますので申し訳ありませんが、";
			mes "必要材料に関しては私のそばにいる";
			mes "カプラソリンにお尋ねください。";
			break;
		}
		mes "[カプラテーリング]";
		mes "ラッピングサービスの";
		mes "ご利用ありがとうございます。";
		mes "お客様の心が伝わるよう";
		mes "祈っております。では、";
		mes "真心をこめてお包みしましょう。";
		next;
		mes "[カプラテーリング]";
		mes "お待たせしました。";
		mes "こちらになります。";
		mes "ご持参された材料でお包みしました。";
		mes "そしてお客様のお名前を";
		mes "記入しましたので、温かい";
		mes "お心が伝わると思います。";
		delitem 644,1;
		delitem 7174,1;
		delitem 7175,1;
		set Zeny,Zeny-1000;
		if(BaseLevel<50)
			set '@itemid,664;
		if(BaseLevel>=50 && BaseLevel<70)
			set '@itemid,665;
		if(BaseLevel>=70 && BaseLevel<90)
			set '@itemid,666;
		if(BaseLevel>=90)
			set '@itemid,667;
		getitem2 '@itemid,1,1,0,0,254,0,getcharid(0),(getcharid(0)>>16)&0xffff;
		next;
		mes "[カプラテーリング]";
		mes "また包装したい贈り物がございましたら";
		mes "いつでもおっしゃってください。";
		break;
	case 2:
		mes "[カプラテーリング]";
		mes "お包みしたい贈り物がございましたら";
		mes "いつでもおっしゃってください。";
		break;
	}
	close2;
	cutin "kafra_02",255;
	end;
}

xmas_in.gat,87,87,6	script	カプラソリン	115,{
	cutin "kafra_03",2;
	mes "[カプラソリン]";
	mes "こんにちは";
	mes "カプラ出張スペシャルサービス";
	mes "「ラッピングサービス！」";
	mes "ご利用に必要な材料をお教えしますので";
	mes "しっかり聞いて準備してください。";
	next;
	mes "[カプラソリン]";
	mes "まず、お客様が包装したい";
	mes "プレゼントボックス1箱が必要です。";
	mes "包む贈り物自体がないと";
	mes "何もできませんからね。";
	next;
	mes "[カプラソリン]";
	mes "そして、包装リボンと包装紙が1個ずつ";
	mes "必要になります。最初、私共は";
	mes "それらを用意していたのですが";
	mes "……倉庫にしまってあった材料が";
	mes "何者かに盗まれてしまったのです。";
	next;
	mes "[カプラソリン]";
	mes "ああ！私がその場にいたら……";
	mes "そいつをバシッと捕まえて";
	mes "思いっきり殴って";
	mes "蹴飛ばして突き飛ばして……";
	next;
	mes "[カプラソリン]";
	mes "ハッ、私は一体何を……？";
	mes "あ、あのお客様、";
	mes "今の話は忘れてくださいね。こほん。";
	mes "それから包装手数料として1000Zenyが";
	mes "必要です。これはお客様のお名前を";
	mes "記入するための費用となります。";
	next;
	mes "[カプラソリン]";
	mes "それでは必要なものを整理します。";
	mes "^3131FFプレゼントボックス1個";
	mes "包装リボン1個";
	mes "包装紙1個";
	mes "1000Zeny^000000";
	next;
	mes "[カプラソリン]";
	mes "以上の材料が全て揃いましたら";
	mes "テーリングにお申し付けください。";
	mes "カプラサービスはクリスマスも";
	mes "お客様のそばにいます。";
	close2;
	cutin "kafra_03",255;
	end;
}

xmas_in.gat,112,86,4	script	カプラビニット	114,{
	cutin "kafra_04",2;
	mes "[カプラビニット]";
	mes "こんにちは、カプラサービスです。";
	mes "お客様だけに、今回の事件の秘密を";
	mes "こっそりとおしえちゃいます。";
	mes "たいした秘密でもないんです";
	mes "けどね……";
	next;
	mes "[カプラビニット]";
	mes "うちのカプラ倉庫を襲ったり";
	mes "子供達の靴下に穴を開けて";
	mes "プレゼントを盗もうとしていた";
	mes "のは、去年も現れたアンソニという";
	mes "サンタだといいます……";
	next;
	mes "[カプラビニット]";
	mes "人々は、アンソニがサンタになる";
	mes "ための訓練が辛くて逃げ出した";
	mes "んだと思っていますが、";
	mes "実はそうじゃないんですよ。";
	mes "私が聞いた話では、アンソニの";
	mes "幼い頃に原因があるとか……";
	next;
	mes "[カプラビニット]";
	mes "クリスマスには、子供達はサンタさんに";
	mes "プレゼントをもらいましたが、";
	mes "アンソニのお父さんは";
	mes "「サンタなんていない」";
	mes "と言っていてプレゼントを";
	mes "あげなかったみたいなんです……";
	next;
	mes "[カプラビニット]";
	mes "それで、毎年この時期になると";
	mes "幸せそうな子供がとても憎かった";
	mes "みたいなんですよ。";
	next;
	mes "[カプラビニット]";
	mes "シィーッ！";
	mes "他の人に聞かれちゃうかも";
	mes "しれませんから……";
	next;
	mes "[カプラビニット]";
	mes "実は、アンソニのお父さんは";
	mes "生活のためのお金で青い箱や";
	mes "紫色の箱を買ってきては";
	mes "自分で全部開けちゃってた";
	mes "らしいんです……";
	next;
	mes "[カプラビニット]";
	mes "そのまま不幸な幼少時代を過ごした";
	mes "アンソニが育って、幸せそうな人を";
	mes "憎むようになっちゃったんです。";
	mes "アンソニのお父さんはそれでも";
	mes "青い箱や紫色の箱の魔力に";
	mes "取り憑かれたままだったみたいですが。";
	next;
	mes "[カプラビニット]";
	mes "そして、アンソニは今、";
	mes "ルティエで何かを企んでいる";
	mes "みたいなんです。";
	mes "いったい何をしようとしているの";
	mes "かしら……";
	next;
	mes "[カプラビニット]";
	mes "もしよろしければ、サンタのぼうしを";
	mes "かぶったモンスター達を退治して";
	mes "くれませんか？";
	mes "私達の倉庫を襲ったのもおそらく";
	mes "アンソニの一味でしょうから……";
	close2;
	cutin "kafra_04",255;
	end;
}

xmas_in.gat,97,99,4	script	カプラグラリス	113,{
	cutin "kafra_05",2;
	callfunc "KafraMain",1,0x102,0,0,0,0,0,0,100,0;
	end;
}

xmas_in.gat,87,102,0	script	カプラＷ	112,{
	cutin "kafra_06",2;
	if(countitem(2636) || countitem(2637)) {
		mes "[カプラＷ]";
		mes "仕事が終わったら開けますねー。";
		mes "ありがとう！";
		mes "メリークリスマスー！";
		close2;
		cutin "kafra_06",255;
		end;
	}
	mes "[カプラＷ]";
	mes "こんにちはぁー。";
	mes "カプラサービスのご利用";
	mes "ありがとうございます。";
	mes "メリークリスマスー！";
	next;
	mes "[カプラＷ]";
	mes "私はテーリング姉ちゃんの";
	mes "包装作業のお手伝いをしていますー。";
	mes "私のお仕事は包装された箱に名前を";
	mes "書くことです。包装紙の上に書くので";
	mes "プレゼントを開けたら、意味が";
	mes "なくなっちゃいますけどね。";
	next;
	mes "[カプラＷ]";
	mes "本当は楽しいクリスマス……";
	mes "のはずなのに倉庫の物を";
	mes "悪い人たちに盗まれちゃったんで";
	mes "落ち込み気味なんですー。";
	mes "うわ～ん……お仕事があるから";
	mes "元気を出さなきゃいけないのに……";
	next;
	switch (select("プレゼントに名前を書いてください","指輪に名前を書いてください","元気を出してください！")) {
	case 1:
		mes "[カプラＷ]";
		mes "プレゼントに名前を書いて欲しいなら";
		mes "あそこにいるテーリング姉ちゃんに";
		mes "包装を頼んでください。";
		mes "私は包装紙に名前を書いているって";
		mes "言ったじゃないですかー。";
		close2;
		cutin "kafra_06",255;
		end;
	case 2:
		emotion 28;
		mes "[カプラＷ]";
		mes "指輪ですか～？そんな物に";
		mes "名前を刻むサービスはしてません。";
		mes "そうでなくても、包装紙に名前を";
		mes "書いてばかりいるから手が痛いですー。";
		mes "シクシク……";
		mes "みんな幸せそうでいいな。";
		close2;
		cutin "kafra_06",255;
		end;
	}
	//case3はfall through
	mes "[カプラＷ]";
	mes "うう、気持ちだけでもありがとう。";
	mes "でも元気が出ないんです……";
	mes "ルティエに出張ってことで";
	mes "とても楽しみにしてたんですけどね。";
	mes "サンタのぼうしを見ると";
	mes "気分が沈むんですー。";
	next;
	if(select("私が元気にしてあげます","頑張ってください！")==2) {
		mes "[カプラＷ]";
		mes "ひっく、ひっく……";
		mes "話だけでも聞いてくれてありがとう。";
		mes "メリークリスマスー！";
		close2;
		cutin "kafra_06",255;
		end;
	}
	emotion 28;
	mes "[カプラＷ]";
	mes "本当ですかー？";
	mes "シクシク……";
	mes "どんなことをしてくれるんですか？";
	mes "シクシク……";
	next;
	switch (select("プレゼントボックスをあげます","サンタのぼうしをあげます","キャロルを歌ってあげます","愉快なダンスを踊ってあげます")) {
	case 1:
		//どの種類のPBoxも持ってない、もしくは金・銀いずれの指輪も持ってないならtrue
		if((countitem(664)<1 && countitem(665)<1 && countitem(666)<1 && countitem(667)<1) ||
									(countitem(2610)<1 && countitem(2611)<1)) {
			mes "[カプラＷ]";
			mes "知らない人から物をいただく";
			mes "わけにはいかないですー。";
			mes "お姉さんたちに怒られてしまいます。";
			mes "大丈夫ですから、";
			mes "気を使わないでください。";
			break;
		}
		emotion 28;
		mes "[カプラＷ]";
		mes "シクシク……";
		mes "きれいに包装までしてある";
		mes "大事なプレゼントを私が";
		mes "もらってもいいんですか？";
		next;
		if(select("メリークリスマス！","やっぱりあげません")==2) {
			emotion 28;
			mes "[カプラＷ]";
			mes "うえ～ん……";
			break;
		}
		emotion 15;
		mes "[カプラＷ]";
		mes "わあ～、ありがとうー！";
		mes "すーっごく嬉しいですー。";
		mes "こんなに大事な物をいただいたからには";
		mes "私も何かお礼をしなきゃ";
		mes "いけないですね。";
		next;
		mes "[カプラＷ]";
		mes "あ、指輪を持っているんですか。";
		mes "じゃあ、その指輪に名前を";
		mes "書いてあげます。";
		mes "えへへ……";
		mes "遠慮なんかいらないですよー。";
		next;
		mes "[カプラＷ]";
		mes "あ、金の指輪を持っている場合は";
		mes "金の指輪に書いちゃいます。";
		mes "もし、金の指輪と銀の指輪を";
		mes "持っていて、銀の指輪の方に";
		mes "名前を書いてほしかったら";
		next;
		mes "[カプラＷ]";
		mes "金の指輪はどこかにあずけて";
		mes "きてくださいね。";
		next;
		switch (select("金の指輪に書いて","銀の指輪に書いて","ちょっとまってて")) {
			case 1:
				set '@itemid,2610;
				set '@gain,2636;
				break;
			case 2:
				set '@itemid,2611;
				set '@gain,2637;
				break;
			case 3:
				mes "[カプラＷ]";
				mes "はい、お待ちしてまーす。";
				close2;
				cutin "kafra_06",255;
				end;
		}
		if(countitem('@itemid)<1) {
			mes "[カプラＷ]";
			mes "あれ？" +getitemname('@itemid)+ "、持っていない";
			mes "みたいですけどー。";
			break;
		}
		if('@itemid==2611 && countitem(2610)) {
			mes "[カプラＷ]";
			mes "ちょっと待ってください。";
			mes "金の指輪を持ってるみたいですよ。";
			mes "金の指輪はあずけてきてくださいね";
			break;
		}
		mes "[カプラＷ]";
		mes "はい、じゃ書いちゃいます。";
		mes "カキカキカキカキ……";
		next;
		mes "[カプラＷ]";
		mes "はい、どうぞ。";
		mes "プレゼント、本当にありがとう！";
		mes "メリークリスマスー！";
		delitem '@itemid,1;
		if(countitem(664))
			delitem 664,1;
		else if(countitem(665))
			delitem 665,1;
		else if(countitem(666))
			delitem 666,1;
		else
			delitem 667,1;
		getitem2 '@gain,1,1,0,0,254,0,getcharid(0),(getcharid(0)>>16)&0xffff;
		break;
	case 2:
		emotion 6;
		mes "[カプラＷ]";
		mes "……いじわるです!!";
		break;
	case 3:
		mes "[カプラＷ]";
		mes "……本当は歌うことが";
		mes "得意じゃないんでしょ？";
		mes "いいですよ、無理しなくて！";
		break;
	case 4:
		emotion 9;
		mes "[カプラＷ]";
		mes "………";
		next;
		emotion 9;
		mes "^FF0000ピョコピョコピョコ、キュッキュッ";
		mes "タタッタタタッタ、パンパンパン！^000000";
		next;
		mes "[カプラＷ]";
		mes "うう、シクシク……";
		next;
		emotion 28;
		mes "[カプラＷ]";
		mes "シクシクシクシク……";
		break;

	}
	close2;
	cutin "kafra_06",255;
	end;
}

//==============================================================
// ロバートメイの発明品
//==============================================================
xmas_in.gat,93,97,0	script	ロバートメイ	873,{
	mes "[ロバートメイ]";
	mes "笑いものにされたお前の鼻♪";
	mes "夜になるほど光ってる鼻♪";
	next;
	emotion 23;
	emotion 23,"";
	mes "[ロバートメイ]";
	mes "まったく！";
	mes "誰が笑いものだ！";
	mes "ふざけおって！";
	next;
	mes "[ロバートメイ]";
	mes "いや……これは失礼した。";
	mes "最近は無礼な子供が多くてな……";
	next;
	mes "[ロバートメイ]";
	mes "ところで、君は";
	mes "「笑いものにされた鼻」の";
	mes "本当の価値を知っているかね？";
	next;
	if(select("いえ","知っています")==1) {
		mes "[ロバートメイ]";
		mes "では、「ピエロの鼻」をつけて";
		mes "自分の姿を客観的に見たまえ。";
		close;
	}
	mes "[ロバートメイ]";
	mes "それなら話が早い！";
	mes "私はクリスマスのために、";
	mes "特別なアイテムを開発したのだ。";
	next;
	mes "[ロバートメイ]";
	mes "雪が降り積もるクリスマス♪";
	mes "サンタが言うよ～♪";
	mes "お前の鼻が明るいから♪";
	mes "安心してソリに乗れるよ♪";
	next;
	mes "[ロバートメイ]";
	mes "歌詞通り、一寸先も見えない雪の中で";
	mes "道に迷わないよう明るく照らしてくれる";
	mes "アイテム、「トナカイの鼻」";
	mes "今なら材料さえあればすぐにでも";
	mes "作ってあげよう。";
	mes "どうするかね？";
	next;
	if(select("興味ないです","お願いします！")==1) {
		mes "[ロバートメイ]";
		mes "ふん！";
		mes "君もつまらない人間の一人か。";
		close;
	}
	mes "[ロバートメイ]";
	mes "ほほぅ……いい返事だ。";
	mes "では、材料を教えよう。";
	next;
	mes "[ロバートメイ]";
	mes "まず、ベースとなる^0000FFピエロの鼻 1個^000000、";
	mes "明るい光を出すために";
	mes "^0000FF損傷したダイヤモンド 2個^000000、";
	mes "その光を維持させる^0000FF星の粉 1個^000000、";
	mes "以上が必要となる。";
	next;
	mes "[ロバートメイ]";
	mes "では、材料を集めてくるんだ。";
	mes "私はここで待っているからな。";
	next;
	if(select("材料をもう一度教えてください","手に入れてきました！")==2) {
		mes "[ロバートメイ]";
		mes "おぉッ！";
		mes "なかなか行動力があるではないか！";
		mes "では、さっそく確認しよう。";
		next;
		if(countitem(2262) && countitem(733) >= 2 && countitem(1001)) {
			mes "[ロバートメイ]";
			mes "よし、よし。";
			mes "全部そろっているな。";
			next;
			mes "[ロバートメイ]";
			mes "では、さっそく作ってあげよう！";
			mes "まずはこの損傷したダイヤモンドを";
			mes "粉にしなければならない。";
			next;
			mes "[ロバートメイ]";
			mes "ダイヤモンドという宝石だけあって、";
			mes "いくら損傷していたとしても、";
			mes "普通の方法で割るなんて不可能だ。";
			next;
			emotion 23;
			misceffect 101;
			mes "[ロバートメイ]";
			mes "しかし！　私の長年の友！";
			mes "ホルグ……ごほごほごほん……";
			mes "いや……友から教えてもらった";
			mes "この力を使えば、こんなものは";
			mes "簡単に割ることができる！";
			mes "「ショック」するのがポイントだ！";
			next;
			misceffect 72;
			mes "[ロバートメイ]";
			mes "さあ、次はこのピエロの鼻に";
			mes "粉にしたダイヤモンドを振り撒く！";
			mes "回転させながら満遍なくつけるんだ。";
			next;
			misceffect 273;
			mes "[ロバートメイ]";
			mes "最後に、星の粉を振り撒く！";
			next;
			emotion 18;
			mes "[ロバートメイ]";
			mes "よし、完成だ！";
			mes "適当に作っているように見えただろうが";
			mes "そんなことはない！";
			mes "誰にも真似出来ない技術を";
			mes "駆使しているのだ！";
			next;
			mes "[ロバートメイ]";
			mes "さあ、受け取りなさい。";
			mes "これで君も、友人たちと";
			mes "楽しいクリスマスをすごすといい。";
			delitem 2262,1;
			delitem 733,2;
			delitem 1001,1;
			getitem 5204,1;
			close;
		}
		mes "[ロバートメイ]";
		mes "……？";
		mes "材料を用意したんじゃないのかね？";
		mes "忘れたならもう一度言おう。";
		next;
	}
	mes "[ロバートメイ]";
	mes "まず、ベースとなる^0000FFピエロの鼻 1個^000000、";
	mes "明るい光を出すために";
	mes "^0000FF損傷したダイヤモンド 2個^000000、";
	mes "その光を維持させる^0000FF星の粉 1個^000000、";
	mes "以上が必要となる。";
	next;
	mes "[ロバートメイ]";
	mes "では、材料を集めてくるんだ。";
	close;
}

//==============================================================
// ルティエに響け！
//==============================================================
xmas.gat,147,95,5	script	チェリス	97,{
	mes "[チェリス]";
	mes "クリスマスを記念して、";
	mes "普段言えない事を";
	mes "思い切って告白してみませんか！";
	mes "人呼んで「私の気持ちを受けとって！」";
	next;
	mes "[チェリス]";
	mes "何年も大切にしてきた";
	mes "この恋心をどうやって伝えようか……";
	mes "数日前にケンカした友達と";
	mes "どうやって仲直りしようか……";
	next;
	mes "[チェリス]";
	mes "何でもいいのです！";
	mes "告白したい事があるなら";
	mes "今が絶好のチャンス！";
	next;
	mes "[チェリス]";
	mes "スティックキャンディ一個で";
	mes "メガホンをお貸しします！";
	mes "ルティエ中に響くぐらい大きな声で、";
	mes "自分の本音を言ってみてください！";
	next;
	if(select("また今度で","メガホンを貸してください！")==1) {
		mes "[チェリス]";
		mes "クリスマス期間中ずっといますので、";
		mes "いつでも来てくださいね！";
		close;
	}
	if(countitem(530) < 1) {
		mes "[チェリス]";
		mes "スティックキャンディを";
		mes "持ってきてください！";
		mes "そしたら、このメガホンを";
		mes "お貸ししますよ！";
		close;
	}
	delitem 530,1;
	mes "[チェリス]";
	mes "わかりました！";
	mes "メガホンの使い方は簡単です。";
	mes "勇気を出して告白する！";
	mes "ただそれだけです！";
	next;
	mes "[チェリス]";
	mes "例えば、こんな感じです！";
	next;
	switch(rand(5)) {
	case 0: announce "今すぐ私と結婚してぇぇぇぇぇぇぇぇ!!!!",9,0x63FFCE; break;
	case 1: announce "実は俺、カプラＷが大好きなんだぁぁぁぁぁぁぁ!!!!",9,0x63FFCE; break;
	case 2: announce "私たちはいつも二人で一つなんだぁぁぁぁぁぁぁぁ!!!!",9,0x63FFCE; break;
	case 3: announce "ずっと前から君のことが好きでしたぁぁぁぁぁぁぁ!!!!",9,0x63FFCE; break;
	case 4: announce "ちょっとレディータニーに会いに行ってきます!!!!",9,0x63FFCE; break;
	}
	mes "[チェリス]";
	mes "さあ、要領はわかりましたか？";
	mes "今度はあなたの番ですよ！";
	next;
	mes "[チェリス]";
	mes "1！";
	next;
	mes "[チェリス]";
	mes "1！";
	mes "2！";
	next;
	mes "[チェリス]";
	mes "1！";
	mes "2！";
	mes "3!!";
	next;
	mes "[チェリス]";
	mes "1！";
	mes "2！";
	mes "3!!";
	mes "どうぞ！";
	next;
	input '@mes$;
	announce strcharinfo(0)+ "様の言葉：" +'@mes$,9,0x63FFCE;
	next;
	mes "[チェリス]";
	mes "どうですか？";
	mes "気持ちはスッキリしましたか？";
	next;
	mes "[チェリス]";
	mes "また何か言いたいことができたら";
	mes "いつでも来てください。";
	mes "スティックキャンディ一つで";
	mes "皆さんの気持ちは解決です！";
	close;
}

//==============================================================
// 再襲！ソロ軍団
//==============================================================
prontera.gat,155,285,3	script	エンジョイ#Xmas	753,{
	switch(XMAS_1EVE) {
	case 0:
		mes "[エンジョイ]";
		mes "いきなりだが質問だ。";
		mes "お前はクリスマスを誰と";
		mes "すごすつもりだ？";
		next;
		switch(select("友達と一緒に……","家族と一緒に……","恋人と一緒に","そんなこと聞くな!!")) {
		case 1:
			mes "[エンジョイ]";
			mes "そうか、そうか！";
			mes "友達と一緒にだな！";
			mes "異性の友達と二人なわけないよな！";
			mes "うんうん。";
			mes "俺にはわかっているぞ。";
			next;
			mes "[エンジョイ]";
			mes "これはクリスマスを友達と楽しむ";
			mes "君への贈り物だ！";
			mes "メリークリスマス！";
			break;
		case 2:
			mes "[エンジョイ]";
			mes "そうだ！";
			mes "クリスマスは家族の間の絆を";
			mes "深めてくれる重要な行事の一つなのだ！";
			next;
			mes "[エンジョイ]";
			mes "よし！";
			mes "これはクリスマスを家族と楽しむ";
			mes "君への贈り物だ！";
			mes "メリークリスマス！";
			break;
		case 3:
			misceffect 42;
			mes "[エンジョイ]";
			mes "…………";
			next;
			misceffect 43;
			mes "[エンジョイ]";
			mes "………………";
			next;
			misceffect 254;
			mes "[エンジョイ]";
			mes "……………………";
			next;
			misceffect 328;
			misceffect 1,"";
			heal -(Hp-1),-(Sp-1);
			mes "[エンジョイ]";
			mes "…………………………";
			mes "とっとと消えろ、この悪魔め!!";
			close2;
			warp "prontera.gat",155,230;
			end;
		case 4:
			mes "[エンジョイ]";
			mes "何か深い事情があるようだな……";
			next;
			mes "[エンジョイ]";
			mes "さあ、これで元気を出すといい。";
			mes "メリークリスマス。";
			break;
		}
		set XMAS_1EVE,1;
		getitem 12200,1;
		close;
	case 1:
		mes "[エンジョイ]";
		mes "ん？　何だ？";
		mes "プレゼントはもう無いぞ。";
		mes "それとも、何か別の用なのか？";
		next;
		if(select("特に何も……","今年はしないのですか？")==1) {
			mes "[エンジョイ]";
			mes "そんなに暇なら";
			mes "俺じゃなくて他の奴のとこにいけ！";
			close;
		}
		mes "[エンジョイ]";
		mes "何が言いたいんだ？";
		next;
		menu "カップルへの天罰です！",-;
		mes "[エンジョイ]";
		mes "しぃッ！";
		mes "静かにしろ！";
		next;
		mes "-彼は慌てて飛びかかってきて、";
		mes "あなたの口を手で塞いだ-";
		mes "-そして小さな声で言った-";
		next;
		mes "[エンジョイ]";
		mes "……何だ？";
		mes "お前、まだソロなのか？";
		mes "情けない青春を送っているなぁ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "…………";
		mes "そう言うエンジョイさんは";
		mes "恋人でもできたんですか？";
		next;
		mes "[エンジョイ]";
		mes "冗談を言うな！";
		mes "俺のどこを見て";
		mes "そんな考えが思いつくんだ！";
		next;
		misceffect 330;
		mes "[エンジョイ]";
		mes "そうか！　お前は悪魔だな！";
		mes "とっとと消えろ、この悪魔め!!";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "わわわわわ！";
		mes "ちょ、ちょっと待ってください！";
		mes "それはないでしょ!?";
		mes "何でそんなに怒るんですか!?";
		next;
		mes "[エンジョイ]";
		mes "恋人なんていう言葉を軽々しく";
		mes "口にするからだ！";
		mes "俺は誇りあるソロ部隊の統率者だ！";
		mes "カップルなんて……カップルなんて";
		mes "一度もうらやましいなんて";
		mes "思ったことはない！";
		next;
		mes "[エンジョイ]";
		mes "カップルなんて……";
		mes "カップルなんて…………";
		mes "……ウッ……";
		next;
		mes "-彼は慌てて顔を上げた-";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……エンジョイさん……？";
		next;
		misceffect 328;
		misceffect 1,"";
		percentheal -50,0;
		mes "[エンジョイ]";
		mes "……ッ！";
		mes "まだいたのか！";
		mes "とっとと消えろ、この悪魔め!!";
		set XMAS_1EVE,2;
		close2;
		warp "prontera.gat",155,230;
		end;
	default:
		misceffect 328;
		misceffect 1,"";
		percentheal -50,0;
		mes "[エンジョイ]";
		mes "まだいたのか！";
		mes "とっとと消えろ、この悪魔め!!";
		close2;
		warp "prontera.gat",155,230;
		end;
	}
}

prontera.gat,155,237,0	script	手紙#Xmas1	844,3,3,{
	if(XMAS_1EVE < 2) {
		mes "-手紙が落ちている-";
		close;
	}
	if(XMAS_1EVE >= 3) {
		mes "[" +strcharinfo(0)+ "]";
		mes "う……これは……";
		mes "そうか！";
		mes "仲間を集めて、ある場所に";
		mes "来いと言っているのか！";
		next;
		emotion 5,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "なら……最初に行くのは……";
		mes "あの人がいる所だ！";
		close;
	}
	mes "-エンジョイさんからの";
	mes "メッセージのようだ-";
	next;
	if(select("読んで見る","読まない")==2) {
		mes "-何故か読まなかった-";
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "何が書かれてるんだろう……？";
	next;
	mes "-あなたはきれいに折りたたまれた";
	mes "紙を広げてみた-";
	next;
	mes "今年も……地獄の季節がやって来た!!";
	mes "いてつく冷たい風が体の中を通り抜け、";
	mes "体の芯まで冷やされ、心の奥底まで";
	mes "凍りついたソロたちよ！";
	mes "クリスマスがカップルたちの日だと";
	mes "一体誰が決めたというのだ!!!!";
	next;
	mes "「クリスマスは家族と一緒に」という";
	mes "美しい言葉を掲げながらも、デートに";
	mes "出かける妹を見送った寒い夜。";
	next;
	mes "寂しさと戦いながら、いっそのこと";
	mes "ヤケ酒でもしようかと思ってしまう";
	mes "地獄のような一日を煩わしく感じる、";
	mes "情けない魂たちよ！";
	next;
	mes "この俺が君達の代わりに";
	mes "大声で叫ぼう！";
	mes "今年のクリスマスは……";
	mes "我々が主役だ!!";
	mes "我々も楽しむのだー!!!!";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "オ、オオーッ!!";
	mes "……それにしても……";
	mes "どうしてわざわざこんな手紙で？";
	next;
	if(select("それより眠い……","続きを読む")==1) {
		mes "[" +strcharinfo(0)+ "]";
		mes "……文を読んでいると";
		mes "ついつい眠くなってしまう……";
		close;
	}
	mes "我々は、素直に！";
	mes "そして楽しく遊ぶのだ!!";
	next;
	mes "だが、我らの計画は去年より";
	mes "もっと静かに、迅速に";
	mes "進めなければならない！";
	next;
	mes "何故なら、去年の作戦によって";
	mes "我々は常に目を付けられている！";
	mes "作戦の成功のためには、";
	mes "何よりも秘密保持と水面下での";
	mes "無駄の無い行動が必要不可欠なのを";
	mes "忘れるな！";
	next;
	mes "作戦内容が漏れないように";
	mes "^0000FF仲間の一人一人にヒントを託した。";
	mes "我々の作戦実行の場^000000まで、";
	mes "誰一人欠ける事無く、集まってほしい！";
	next;
	mes "俺は一足先に待っている！";
	mes "軽薄なカップルに天罰を！";
	next;
	mes "……なお、この手紙は";
	mes "自動的に消失する。";
	next;
	mes "-3-";
	next;
	mes "-3-";
	mes "-2-";
	next;
	mes "-3-";
	mes "-2-";
	mes "-1-";
	next;
	mes "-3-";
	mes "-2-";
	mes "-1-";
	mes "-^FF00000^000000-";
	next;
	misceffect 183;
	emotion 23,"";
	percentheal -30,0;
	set XMAS_1EVE,3;
	close;
OnTouch:
	if(XMAS_1EVE != 2)
		end;
	mes "[" +strcharinfo(0)+ "]";
	mes "何故？";
	mes "どうしてエンジョイさんは";
	mes "あんなに怒ってるんだ!?";
	next;
	mes "-混乱しているあなたの目に";
	mes "地面に落ちている何かが映った-";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……？";
	mes "これは……？";
	close;
}

prontera.gat,188,177,4	script	ハッピー	869,{
	if(XMAS_1EVE <= 3) {
		emotion 28;
		mes "[ハッピー]";
		mes "今年も！　今年までも！";
		mes "神は俺を見捨てた！";
		mes "ホルグレンまでもが俺を見捨てた！";
		if(XMAS_1EVE != 3)
			close;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……ハッピーさん？";
		next;
		mes "[ハッピー]";
		mes "何だ？　笑いたいなら笑えばいい!!";
		mes "今年こそはと精錬をしたが、";
		mes "クリスマスにもらったのは";
		mes "クホホホホという言葉だけだ！";
		mes "お前には理解できないだろ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ハッピーさん！";
		mes "エンジョイさんが今年も……";
		next;
		mes "-あなたは慌てて口を閉じ、";
		mes "周りを気にしながら";
		mes "ハッピーに声をかけた-";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "エンジョイさんが……";
		mes "何か言っていませんでしたか？";
		next;
		mes "[ハッピー]";
		mes "……お前！";
		mes "エンジョイさんを知っているのか!?";
		next;
		mes "[ハッピー]";
		mes "……よし。";
		mes "エンジョイさんから自分の事を";
		mes "聞きにくる人への伝言を";
		mes "頼まれている。";
		mes "よく聞いておくんだ。";
		next;
		mes "[ハッピー]";
		mes "それは、^0000FF花壇^000000！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……え？";
		mes "何、何ですって？";
		next;
	}
	mes "[ハッピー]";
	mes "^0000FF花壇^000000！";
	next;
	mes "[ハッピー]";
	mes "俺はそれしか聞いていない。";
	mes "後は他の仲間たちに聞いてみるんだ。";
	next;
	mes "[ハッピー]";
	mes "では、決戦のその場で会おう！";
	if(XMAS_1EVE == 3)
		set XMAS_1EVE,4;
	close;
}

prontera.gat,62,339,3	script	メリー	875,{
	if(XMAS_1EVE <= 4) {
		mes "[メリー]";
		mes "ペコちゃん、ペコちゃん。";
		mes "今日はどこを走ってみようか？";
		mes "いつまでも俺たち二人で";
		mes "荒野のようなこの世界を走ろう。";
		mes "そうだ、そうしよう！";
		if(XMAS_1EVE != 4)
			close;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あの……メリーさん？";
		next;
		mes "[メリー]";
		mes "何だ！　貴様は!!";
		mes "俺のペコちゃんは";
		mes "人見知りが激しいんだ！";
		mes "ああ～、怖かったろうペコちゃん？";
		mes "大丈夫、大丈夫だからね～。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "そのペコペコ……雄じゃ……";
		mes "いや、それより。";
		mes "エンジョ……";
		next;
		mes "[メリー]";
		mes "なにを言うか！";
		mes "たとえ雄だとしても、";
		mes "こんなに可愛いペコちゃんなら";
		mes "問題無しだ！";
		mes "わかったか！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ぇ……ぁ……はい……";
		mes "ところで、エンジョイさんが";
		mes "メリーさんに何か……";
		next;
		mes "[メリー]";
		mes "エンジョイさんだって!?";
		mes "そうか……時が来たのか。";
		mes "なら、よく聞いておくんだ。";
		next;
		mes "[メリー]";
		mes "^0000FFベンチの下^000000！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ぇ、下？";
		mes "何の下ですか？";
		next;
	}
	mes "[メリー]";
	mes "^0000FFベンチの下^000000！";
	next;
	mes "[メリー]";
	mes "俺が知っているのはそれだけだ。";
	mes "後は他の仲間たちに聞いてみるんだ。";
	next;
	mes "[メリー]";
	mes "では、決戦のその場で会おう！";
	if(XMAS_1EVE == 4)
		set XMAS_1EVE,5;
	close;
}

prontera.gat,163,66,7	script	クリス	748,{
	if(XMAS_1EVE <= 5) {
		mes "[クリス]";
		mes "ハーブを！　ポーションを！";
		mes "ソロでもランカーになれるって";
		mes "やつらに教えてやるんだ！";
		mes "他には何もいらない！";
		mes "もっと、もっと名声を！";
		if(XMAS_1EVE != 5)
			close;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あの……クリスさん？";
		next;
		mes "[クリス]";
		mes "あ？　ん？　誰だ君は！";
		mes "いや、余計な事を考えてる暇はない！";
		mes "話かけるな！";
		next;
		mes "[クリス]";
		mes "……でも……";
		mes "そんな風に話しかけられると";
		mes "胸のあたりが何か……";
		mes "あ、しまった！";
		mes "また余計な事を考えてしまった！";
		mes "それどころじゃないんだ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "落ち着いてください！";
		mes "私はただエンジョイさんが";
		mes "何か伝言を……";
		next;
		mes "[クリス]";
		mes "エンジョイ？";
		mes "エンジョイさんって言ったか？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "そうです。";
		mes "エンジョイさんがクリスさんに";
		mes "何か伝言を残しませんでしたか？";
		next;
		mes "[クリス]";
		mes "もうそんな日か？";
		mes "ああ、そうだ、そうだ!!";
		mes "毎日ハーブを集めて、";
		mes "ポーションばかり作っていたせいで、";
		mes "すっかり忘れていた！";
		mes "よし、よく聞いておくんだ。";
		next;
		mes "[クリス]";
		mes "^0000FF日が暮れる方^000000！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ぇ？　なんですって？";
		next;
	}
	mes "[クリス]";
	mes "^0000FF日が暮れる方^000000！";
	next;
	mes "[クリス]";
	mes "私が知っているのはそれだけだ。";
	mes "後は他の仲間たちに聞いてみるんだ。";
	next;
	mes "[クリス]";
	mes "では、決戦のその場で会おう！";
	if(XMAS_1EVE == 5)
		set XMAS_1EVE,6;
	close;
}

prontera.gat,35,209,5	script	マス	881,{
	if(XMAS_1EVE <= 6) {
		emotion 23,"";
		mes "[マス]";
		mes "…………";
		mes "私も大好きだよ、カプラお姉様～!!";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（あまり関わりたくない人がいる……）";
		next;
		mes "[マス]";
		mes "うん、わかってるよ、ティーベ。";
		mes "この前、サキュバスお姉様が僕に";
		mes "ハートを飛ばしてきたよね。";
		mes "僕もこれからは街の外に";
		mes "出るようにするよ……";
		mes "ヒヒッ、ヒヒヒヒッ……。";
		next;
		emotion 29;
		mes "-彼は、自分の右手に持つ";
		mes "何かに向かい、にやにやしながら";
		mes "話しかけている-";
		if(XMAS_1EVE != 6)
			close;
		next;
		emotion 28,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "マ、マスさん……";
		mes "エンジョイさんから何か";
		mes "聞いていませんか？";
		mes "（この人はやばい！　やばすぎる！）";
		next;
		mes "[マス]";
		mes "ふふ、聞いたかい、ティーベ。";
		mes "カプラサービスはいつも皆様の";
		mes "そばにあるんだってさ。";
		mes "恥ずかしがらず、素直に";
		mes "「あなたのそばにいたいです」";
		mes "って言えば良いのに……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あ、あの……";
		mes "エンジョイさんから何か";
		mes "頼まれていませんか？";
		mes "（やっぱりこの人は苦手だ！）";
		next;
		mes "[マス]";
		mes "……^0000FFもう一つのメッセージ^000000。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "え、え？";
		mes "今なんて？";
		next;
	}
	mes "[マス]";
	mes "^0000FFもう一つのメッセージ^000000。";
	next;
	mes "[マス]";
	mes "フフフ。わからない振りをして";
	mes "何度も僕の声を聞こうとするなんてね。";
	mes "見え見えだよ、ねぇ？　ティーベ。";
	mes "クックックックックッ。";
	next;
	mes "[マス]";
	mes "じゃ、続きは決戦の場で……";
	mes "フフフ……";
	if(XMAS_1EVE == 6)
		set XMAS_1EVE,7;
	close;
}

prt_fild05.gat,355,254,0	script	手紙#Xmas2	844,3,3,{
	if(XMAS_1EVE < 7) {
		mes "-手紙が落ちている-";
		close;
	}
	if(XMAS_1EVE >= 8) {
		mes "[" +strcharinfo(0)+ "]";
		mes "う……またか……";
		mes "アイテムを集めて、ある場所に";
		mes "来いと言っているのか……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "確かアイテムは……";
		mes "^0000FF木屑 5個";
		mes "木の節目 5個";
		mes "古木の枝 1個^000000";
		mes "だったかな……";
		next;
		emotion 5,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "そして……";
		mes "^0000FF水と森が出会う場所";
		mes "その小さな飛び石に集え^000000";
		mes "……うーん……";
		mes "よし、大体想像がつくぞ！";
		close;
	}
	mes "-エンジョイさんからの";
	mes "メッセージのようだ-";
	next;
	if(select("読んで見る","読まない")==2) {
		mes "-何となく読まなかった-";
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "今度は何が書かれてるんだろう……？";
	next;
	mes "-あなたはきれいに折りたたまれた";
	mes "紙を広げてみた-";
	next;
	mes "よくここまで来た！";
	mes "下に書いてある物を集め、";
	mes "秘密の場所まで来てほしい！";
	next;
	mes "^0000FF木屑 5個";
	mes "木の節目 5個";
	mes "古木の枝 1個^000000";
	next;
	mes "^0000FF水と森が出会う場所";
	mes "その小さな飛び石に集え^000000";
	next;
	mes "俺は一足先に待っている！";
	mes "軽薄なカップルに天罰を！";
	next;
	mes "なお、この手紙は";
	mes "自動的に消失する。";
	next;
	mes "-3-";
	next;
	mes "-3-";
	mes "-2-";
	next;
	mes "-3-";
	mes "-2-";
	mes "-1-";
	next;
	mes "-3-";
	mes "-2-";
	mes "-1-";
	mes "-^FF00000^000000-";
	next;
	misceffect 183;
	emotion 23,"";
	percentheal -30,0;
	set XMAS_1EVE,8;
	close;
OnTouch:
	if(XMAS_1EVE != 7)
		end;
	mes "[" +strcharinfo(0)+ "]";
	mes "花壇、ベンチの下、日が暮れる方、";
	mes "もう一つのメッセージ？";
	mes "一体どういうことだろう……";
	next;
	mes "-混乱しているあなたの目に";
	mes "地面に落ちている何かが映った-";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……？";
	mes "これは……？";
	close;
}

prt_fild05.gat,101,160,0	script	飛び石#Xmas	139,3,3,{
	if(XMAS_1EVE != 8)
		end;
	mes "[" +strcharinfo(0)+ "]";
	mes "^0000FF水と森が出会う場所";
	mes "その小さな飛び石に集え^000000";
	mes "この辺の事かな……？";
	next;
	mes "[??????]";
	mes "……おい！　お前！";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "え？　誰ですか！";
	next;
	mes "[??????]";
	mes "指示したアイテムは";
	mes "ちゃんと集めてきたのか！";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "あ、エンジョイさん？";
	mes "エンジョイさんですね！";
	mes "どこにいるんですか？";
	next;
	mes "[??????]";
	mes "質問に答えるんだ！";
	mes "アイテムは集めてきたのか!?";
	next;
	if(select("まだです……","ここに！")==1) {
		mes "[??????]";
		mes "何をしている！";
		mes "早く集めてくるんだ！";
		close;
	}
	if(countitem(1019) < 5 || countitem(7222) < 5 || countitem(604) < 1) {
		mes "[??????]";
		mes "どこにあるというのだ！";
		mes "持っているならちゃんと見せてみろ！";
		close;
	}
	mes "[??????]";
	mes "よし！　準備が整ったな！";
	mes "それでは始めるとしよう!!";
	hideonnpc;
	hideoffnpc "エンジョイ#Xmas";
	hideoffnpc "ハッピー#Xmas";
	hideoffnpc "メリー#Xmas";
	hideoffnpc "クリス#Xmas";
	hideoffnpc "マス#Xmas";
	emotion 27,"ハッピー#Xmas";
	emotion 27,"メリー#Xmas";
	emotion 27,"クリス#Xmas";
	emotion 27,"マス#Xmas";
	close;
}

prt_fild05.gat,101,161,4		script	エンジョイ#Xmas	753,{
	if(XMAS_1EVE == 9) {
		mes "[エンジョイ]";
		mes "見よ……いまだソロの立場は狭い。";
		mes "だが！　ソロであろうと、";
		mes "背筋を伸ばして歩ける未来を";
		mes "この手に掴むまで！";
		mes "常に進むのだ！　同士たちよ！";
		next;
		mes "[エンジョイ]";
		mes "栄光をつかむその日まで！";
		mes "ソロが心の平安を取り戻すその日まで、";
		mes "この挑戦は果てしなく続くだろう。";
		mes "力を出せ、戦友よ！";
		mes "心が解放されるまで、思う存分楽しめ！";
		set XMAS_1EVE,0;
		hideonnpc;
		close;
	}
	if(XMAS_1EVE != 8)
		end;
	if(countitem(1019) < 5 || countitem(7222) < 5 || countitem(604) < 1) {
		mes "[エンジョイ]";
		mes "何だ！　アイテムが揃ってないぞ！";
		mes "お前がためらっているこの時も、";
		mes "カップルどもは楽しいクリスマスを";
		mes "すごそうと準備しているのだ！";
		next;
		mes "[エンジョイ]";
		mes "^0000FF木屑 5個^000000!!";
		mes "^0000FF木の節目 5個^000000!!";
		mes "^0000FF古木の枝 1個^000000!!";
		mes "早く集めてくるんだ！";
		hideonnpc;
		hideonnpc "ハッピー#Xmas";
		hideonnpc "メリー#Xmas";
		hideonnpc "クリス#Xmas";
		hideonnpc "マス#Xmas";
		hideoffnpc "飛び石#Xmas";
		close;
	}
	mes "[エンジョイ]";
	mes "歓迎するぞ諸君!!";
	next;
	mes "[エンジョイ]";
	mes "一人身というのが";
	mes "まるで罪であるかのように、";
	mes "カップルたちの目を避け、";
	mes "世間の目を避け、";
	mes "賑やかな記念日の度に";
	mes "陰に追いやられてきたソロたちよ！";
	next;
	mes "[エンジョイ]";
	mes "下等極まりない存在！";
	mes "ただカップルというだけで";
	mes "まるで勝者のようにふるまう";
	mes "馬鹿者どもに今こそ言おう！";
	next;
	mes "[エンジョイ]";
	mes "これ以上！";
	mes "ソロというだけで！";
	mes "敗者のように！";
	mes "頭を下げて暮らしはしない!!";
	next;
	mes "[エンジョイ]";
	mes "過去に受けた傷！";
	mes "咲くこともできず、";
	mes "散っていった心に未練を残さない！";
	mes "寂しいからといって！";
	mes "泣き崩れたりはしない!!";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "（……え？";
	mes "過去に受けた傷？";
	mes "散っていった心？";
	mes "寂しい？）";
	next;
	mes "-不思議そうなあなたの顔を見て、";
	mes "みんながささやいてきた-";
	next;
	mes "[ハッピー]";
	mes "エンジョイさん、ふられたんだよ。";
	next;
	mes "[メリー]";
	mes "クリスマスの十日前にな。";
	next;
	mes "[クリス]";
	mes "生まれて初めてソロじゃない";
	mes "クリスマスを迎えれそうだったのにね。";
	next;
	mes "[マス]";
	mes "……フフフ……";
	next;
	mes "[エンジョイ]";
	mes "……戻らないというなら！";
	mes "何も思い出しはしない！";
	mes "すべての思い出！";
	mes "ここで全て焼き尽くすのだ!!!!";
	next;
	mes "[一同]";
	mes "オオオオオオッ!!!";
	next;
	mes "-エンジョイは草の影に隠しておいた";
	mes "焚き火に向かって、色々なアイテムを";
	mes "投げ込んだ-";
	next;
	mes "[エンジョイ]";
	mes "堂々と生きて行くのだ!!";
	mes "我々は、誇るべきソロなのだ!!!!!!";
	next;
	mes "[エンジョイ]";
	mes "我らの心！";
	mes "恨み！　怒り！　苦悩!!";
	mes "全てをここに!!!!";
	next;
	set XMAS_1EVE,9;
	set 'name$,strcharinfo(0);
	misceffect 330;
	hideonnpc;
	hideonnpc "ハッピー#Xmas";
	hideonnpc "メリー#Xmas";
	hideonnpc "クリス#Xmas";
	hideonnpc "マス#Xmas";
	initnpctimer;
	close;
OnTimer3000:
	announce "過去に受けた傷に泣かされたりはしない!!",9,0x73DEDE;
	monster "prt_fild05.gat",117,154,'name$+"の挫折",1062,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",117,155,'name$+"の爆弾",1062,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",117,156,'name$+"の苦悩",1062,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",117,157,'name$+"の妬み",1062,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",117,158,'name$+"の絶望",1062,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",118,154,'name$+"の怒り",1246,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",118,155,'name$+"の恨み",1246,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",118,156,'name$+"の呪い",1246,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",118,157,'name$+"の傷心",1246,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",118,158,'name$+"の憎悪",1246,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",119,154,'name$+"のむせび",1245,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",119,155,'name$+"の孤独",1245,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",119,156,'name$+"の闇",1245,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",119,157,'name$+"の裁き",1245,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",119,158,'name$+"の嫉妬",1245,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",120,154,'name$+"の憂鬱",1244,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",120,155,'name$+"の癇癪",1244,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",120,156,'name$+"の囁き",1244,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",120,157,'name$+"の泣き叫び",1244,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",120,158,'name$+"の悪夢",1244,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",121,154,'name$+"の八つ当たり",1588,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",121,155,'name$+"の悲しみ",1588,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",121,156,'name$+"の攻撃",1588,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",121,157,'name$+"の影",1588,1,"エンジョイ#Xmas::OnKilled";
	monster "prt_fild05.gat",121,158,'name$+"の後悔",1588,1,"エンジョイ#Xmas::OnKilled";
	end;
OnTimer6000:
	announce "ソロ部隊員 " +'name$+ "様の心の中にある悲しみの黒い雲が、空を覆い尽くす。",9,0x73DEDE;
	end;
OnTimer9000:
	announce "気まぐれな連絡なんて待ちはしない!!",9,0x73DEDE;
	end;
OnTimer12000:
	announce "散っていった心に未練なんて残さない!!",9,0x73DEDE;
	end;
OnTimer15000:
	announce "寂しくなったからといって、泣き崩れたりしない!!",9,0x73DEDE;
	end;
OnTimer18000:
	announce "不必要な記憶は思い出さない!!",9,0x73DEDE;
	end;
OnTimer21000:
	announce "私は、誇りあるソロ軍団員だ!!",9,0x73DEDE;
	end;
OnTimer180000:
	stopnpctimer;
	set 'name$,0;
	announce "ソロ軍団員達が、皆で楽しいクリスマスを迎えられるよう祈りました。",9,0x73DEDE;
	killmonster "prt_fild05.gat","エンジョイ#Xmas::OnKilled";
	hideoffnpc;
	end;
OnKilled:	//ダミーイベント
	end;
OnInit:
	hideonnpc;
	hideonnpc "ハッピー#Xmas";
	hideonnpc "メリー#Xmas";
	hideonnpc "クリス#Xmas";
	hideonnpc "マス#Xmas";
	end;
}

prt_fild05.gat,97,164,5		script	ハッピー#Xmas	869,{}
prt_fild05.gat,103,163,4	script	メリー#Xmas	875,{}
prt_fild05.gat,103,159,1	script	クリス#Xmas	748,{}
prt_fild05.gat,97,159,0		script	マス#Xmas	881,{}

//==============================================================
// 不気味な卵……
//==============================================================
xmas.gat,152,290,3	script	ポウ	716,{
	switch(XMAS_2EVE) {
	case 0:
		mes "[ポウ]";
		mes "えい！";
		mes "この！　この！";
		next;
		misceffect 1;
		mes "[ポウ]";
		mes "こいつ！　この！";
		mes "さっさと起きろ！";
		mes "この！　このぉ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "わ、何してるの!?";
		next;
		mes "[ポウ]";
		mes "な、なんだよ。";
		mes "あんた誰だよ!?";
		next;
		switch(select("愛と勇気の勇者！","通りすがりの者","暇な万能解決者！")) {
		case 1:
			mes "[ポウ]";
			mes "……ママが危ない人とは";
			mes "話をしちゃいけないって言ってた。";
			close;
		case 2:
			mes "[ポウ]";
			mes "……そのままあっち行けよ。";
			close;
		case 3:
			break;
		}
		mes "[ポウ]";
		mes "え、何？　暇なの？";
		mes "友達いないの？";
		mes "……しょうがないなぁ。";
		mes "僕が友達になってあげようか？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "い、いいよ！";
		mes "私にだって友達はいるから。";
		mes "ちょっと今は一人で";
		mes "遊んでいるだけ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "それより、さっき何してたの？";
		mes "カバンを殴っていたみたいだけど……";
		mes "そんな事しちゃいけないよ。";
		next;
		mes "[ポウ]";
		mes "……でも、こいつ";
		mes "全然起きないんだ……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "起きない？";
		next;
		mes "-子供は抱いていたカバンを";
		mes "あなたに向かって突き出した-";
		next;
		mes "[ポウ]";
		mes "中に卵が入ってるんだ。";
		mes "ちゃんと育てるなら飼ってもいいって";
		mes "ママが言ってたけど、";
		mes "育てようにも卵から出てこないんだ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ん？";
		mes "その卵、どこで手に入れてきたの？";
		next;
		mes "[ポウ]";
		mes "わ……触わるな！";
		mes "これはおもちゃ工場の近くで";
		mes "僕が見つけたんだ。";
		next;
		mes "-子供が見せてくれたカバンの中には";
		mes "見たこともない卵が入っていた-";
		next;
		mes "[ポウ]";
		mes "……それに……この卵を拾ってから、";
		mes "変な事が起きるようになったんだ。";
		next;
		mes "[ポウ]";
		mes "僕の部屋から夜中に";
		mes "誰かが跳びはねるような";
		mes "音が聞こえてうるさいとか……";
		mes "くすくす笑うような声が";
		mes "聞こえるとか……";
		next;
		mes "[ポウ]";
		mes "一度、卵をベットに";
		mes "縛り付けておいたけど、";
		mes "いつのまにか階段にいて、";
		mes "パパが転んで怪我したんだ。";
		next;
		mes "[ポウ]";
		mes "それで、パパもママも怒っちゃって、";
		mes "中身もわからないそんな卵、";
		mes "早く捨てろって言うんだ……";
		mes "でも……でも……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "うう～ん……";
		mes "でも、その話もわかるな。";
		mes "ほら、見てよこの卵の模様。";
		mes "なんだか……不気味……";
		mes "すぐにでも手放さないと";
		mes "もっと酷い事が起きるかもしれないよ？";
		next;
		mes "[ポウ]";
		mes "触わるなって言ってるだろ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "今までいろんな冒険をしてきた";
		mes "私の話を少しぐらい聞いてよ。";
		mes "それは本当に危険かもしれない。";
		mes "普通の人、しかも君みたいな";
		mes "子供じゃ……";
		next;
		emotion 28;
		mes "[ポウ]";
		mes "やだ！";
		mes "もうあっち行け！";
		mes "行けったらもう……";
		mes "あぁぁぁぁぁぁん。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ああ、泣かないで。";
		mes "私がなんとかしてあげるから！";
		mes "ね？　だから泣かないで。";
		next;
		mes "[ポウ]";
		mes "……グス……";
		mes "……どうするのさ。";
		next;
	case 1:
	case 2:
		mes "[" +strcharinfo(0)+ "]";
		mes "まずはその卵を";
		mes "浄化しないといけないと思う。";
		mes "一度大聖堂で調べてみるから、";
		mes "その卵を貸して…………";
		next;
		emotion 28;
		mes "[ポウ]";
		mes "やだぁぁぁぁぁぁ！";
		next;
		emotion 16,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "……っというのは無理みたいだから、";
		mes "とりあえず卵について";
		mes "大聖堂まで聞いてくるよ。";
		mes "その間、卵に変な事が起きないよう";
		mes "ちゃんと見張っててね。";
		if(XMAS_2EVE == 0)
			set XMAS_2EVE,1;
		close;
	case 3:
		misceffect 1;
		mes "[ポウ]";
		mes "こいつ！　早く起きろ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "わわ、ストップ、ストップ！";
		mes "ほら、もらってきたよ！";
		mes "^0000FF祝福の粉^000000。";
		mes "これでなんとかなるみたいだよ。";
		next;
		mes "[ポウ]";
		mes "え、ホント？";
		mes "それがあればこいつも";
		mes "目が覚めるの？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "う……た、たぶん……";
		mes "あのホーリーさんを見る限り";
		mes "ちょっと不安だけど……";
		mes "試してみる価値はあるよ！";
		mes "……きっと……";
		next;
		mes "[ポウ]";
		mes "早く！　早くやってみてよ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "それじゃ、いくよ！";
		mes "…………";
		mes "（……って、これどうやって使うの？）";
		next;
		switch(select("卵と一緒に水に入れて沸かす","卵に穴を空けて粉を入れる","卵の表面に粉を振り掛ける","粉を水に溶かして塗りつける")) {
		case 1:
			misceffect 302,"";
			mes "[" +strcharinfo(0)+ "]";
			mes "（こうかな？）";
			mes "粉を水で溶かして";
			mes "卵と一緒に沸かしてみよう。";
			next;
			emotion 23;
			mes "[ポウ]";
			mes "わ、何をするんだ！";
			mes "僕の卵をゆでて食べるつもりだな！";
			mes "鬼！　悪魔！　人でなし！";
			mes "あっちにいけ！";
			close2;
			warp "xmas.gat",148,116;
			end;
		case 2:
			misceffect 194,"";
			mes "[" +strcharinfo(0)+ "]";
			mes "（こうかな？）";
			mes "卵の上の方に穴をあけて";
			mes "粉を入れてみよう。";
			next;
			emotion 23;
			mes "[ポウ]";
			mes "わ、何をするんだ！";
			mes "僕の卵を壊して食べるつもりだな！";
			mes "鬼！　悪魔！　人でなし！";
			mes "あっちにいけ！";
			close2;
			warp "xmas.gat",148,116;
			end;
		case 3:
			break;
		case 4:
			misceffect 214,"";
			mes "[" +strcharinfo(0)+ "]";
			mes "（こうかな？）";
			mes "粉を水に溶かして";
			mes "パックのように塗ってみよう。";
			next;
			emotion 23;
			mes "[ポウ]";
			mes "わ、何をするんだ！";
			mes "僕の卵を窒息させて食べるつもりだな！";
			mes "鬼！　悪魔！　人でなし！";
			mes "あっちにいけ！";
			close2;
			warp "xmas.gat",148,116;
			end;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "（こうかな？）";
		mes "粉をそのまま卵に振りかけてみよう。";
		next;
		misceffect 77,"";
		emotion 0;
		emotion 0,"";
		mes "-あなたは^0000FF祝福の粉^000000を";
		mes "指でつまみ、卵に向かって";
		mes "振りかけた-";
		next;
		mes "-不気味な模様が描かれた卵に";
		mes "祝福の粉を振り掛けると、";
		mes "たった今生まれたばかりのような";
		mes "綺麗な卵へと変化していった-";
		next;
		mes "[ポウ]";
		mes "成功……したの？";
		mes "もう、こいつは変なことしないの？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "う～ん……どうかな？";
		mes "模様は消えたけど、";
		mes "まだ卵の中身が何かわからないし……";
		mes "この卵を私に任せてくれないかな？";
		next;
		mes "[ポウ]";
		mes "いやだ！";
		mes "僕は今まで一人だったんだ！";
		mes "どんなモンスターでもいい。";
		mes "弟や妹がほしいんだ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "でもね、もしこの卵の中に";
		mes "聞いた事もないようなモンスターが";
		mes "入ってたら……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "やっぱりそんな危険な卵は";
		mes "普通の家庭には置いておけないよ。";
		mes "それも君みたいな小さな子じゃ";
		mes "なおさら……";
		next;
		emotion 28;
		mes "[ポウ]";
		mes "うるさぃ！";
		mes "僕の卵は絶対に渡さない!!";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "うぅ……";
		mes "困ったなぁ……";
		mes "どうすれば……";
		next;
		emotion 5,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "あ！　そうだ！";
		mes "じゃあこうしよう！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "可愛いモンスターを";
		mes "テイミングできちゃう素敵なアイテムと";
		mes "その卵を交換しようよ。";
		next;
		mes "[ポウ]";
		mes "…………";
		mes "テイミング？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "そ、テイミング！";
		mes "気に入ったモンスターをテイミング！";
		mes "弟や妹にするなら自分の好きな子。";
		mes "そのほうがいいでしょ？";
		next;
		mes "[ポウ]";
		mes "…………ぅ……ん……";
		mes "そうだね……";
		mes "うん、それならいいよ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "よし！";
		mes "それじゃあさっそく";
		mes "テイミングアイテムを";
		mes "探してくるから！";
		mes "ちょっとだけ待っててね！";
		set XMAS_2EVE,4;
		close;
	case 4:
		mes "[ポウ]";
		mes "っで、どうなったの？";
		mes "テイミングアイテムっての";
		mes "持ってきてくれたの？";
		next;
		switch(select("ポリン","ドロップス","ポポリン","ルナティック","ピッキ","サベージベベ","チョンチョン","スポア","ポイズンスポア","ペコペコ","スチールチョンチョン","ハンターフライ",
				"スモーキー","ロッカー","ドケビ","デザートウルフ(子)","イシス","プティット","ムナック","ボンゴン","オークウォリアー","バフォメット.Jr","デビルチ","ソヒー","ヨーヨー")) {
		case 1:
			set '@itemid,619;
			set '@mobname$,"ポリン";
			break;
		case 2:
			set '@itemid,620;
			set '@mobname$,"ドロップス";
			break;
		case 3:
			set '@itemid,621;
			set '@mobname$,"ポポリン";
			break;
		case 4:
			set '@itemid,622;
			set '@mobname$,"ルナティック";
			break;
		case 5:
			set '@itemid,623;
			set '@mobname$,"ピッキ";
			break;
		case 6:
			set '@itemid,627;
			set '@mobname$,"サベージベベ";
			break;
		case 7:
			set '@itemid,624;
			set '@mobname$,"チョンチョン";
			break;
		case 8:
			set '@itemid,630;
			set '@mobname$,"スポア";
			break;
		case 9:
			set '@itemid,631;
			set '@mobname$,"ポイズンスポア";
			break;
		case 10:
			set '@itemid,632;
			set '@mobname$,"ペコペコ";
			break;
		case 11:
			set '@itemid,625;
			set '@mobname$,"スチールチョンチョン";
			break;
		case 12:
			set '@itemid,626;
			set '@mobname$,"ハンターフライ";
			break;
		case 13:
			set '@itemid,633;
			set '@mobname$,"スモーキー";
			break;
		case 14:
			set '@itemid,629;
			set '@mobname$,"ロッカー";
			break;
		case 15:
			set '@itemid,637;
			set '@mobname$,"ドケビ";
			break;
		case 16:
			set '@itemid,628;
			set '@mobname$,"デザートウルフの子供";
			break;
		case 17:
			set '@itemid,639;
			set '@mobname$,"イシス";
			break;
		case 18:
			set '@itemid,640;
			set '@mobname$,"プティット";
			break;
		case 19:
			set '@itemid,636;
			set '@mobname$,"ムナック";
			break;
		case 20:
			set '@itemid,659;
			set '@mobname$,"ボンゴン";
			break;
		case 21:
			set '@itemid,635;
			set '@mobname$,"オークウォリアー";
			break;
		case 22:
			set '@itemid,642;
			set '@mobname$,"バフォメット.Jr";
			break;
		case 23:
			set '@itemid,643;
			set '@mobname$,"デビルチ";
			break;
		case 24:
			set '@itemid,638;
			set '@mobname$,"ソヒー";
			break;
		case 25:
			set '@itemid,634;
			set '@mobname$,"ヨーヨー";
			break;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "うん、持ってきたよ。";
		mes "「" +getitemname('@itemid)+ "」！";
		switch(@menu) {
		case 1: //まだ熟してないリンゴ
			mes "すっぱくて苦いけど、";
			break;
		case 2: //オレンジジュース
			mes "果汁を集めた飲み物で、";
			break;
		case 3: //とても苦い草
			mes "食べると誰だって";
			mes "顔が歪んでしまうぐらい苦い！";
			break;
		case 4: //虹色ニンジン
			mes "虹色の光を出している上、";
			mes "とっても素敵な香り！";
			break;
		case 5: //ハンサムな青年ミミズ
			mes "首にある蝶ネクタイがポイント！";
			break;
		case 6: //甘い牛乳
			mes "特殊加工された";
			mes "甘く、美味しいミルク！";
			break;
		case 7: //腐った魚
			mes "すごく腐っているけど、";
			break;
		case 8: //朝の露が宿っている苔
			mes "少しだけ水を含んだ緑色の苔で、";
			break;
		case 9: //猛毒草
			mes "猛毒を持った危険な草だけど、";
			break;
		case 10: //太っているミミズ
			mes "元気いっぱい、ぽっちゃりスタイル！";
			break;
		case 11: //錆びた鉄
			mes "すごく錆びていて、";
			mes "とてもじゃないけど使えない。";
			break;
		case 12: //モンスタージュース
			mes "血で作られたジュース。";
			mes "とても飲めるようなものじゃないけど、";
			break;
		case 13: //焼き芋
			mes "ふっくらあつあつ、";
			mes "よーく焼いてあるお芋。";
			break;
		case 14: //歌う花
			mes "不思議なことに、花なのに歌う。";
			break;
		case 15: //古いホウキ
			mes "代々受け継がれてきたという";
			mes "とっても古いホウキ。";
			break;
		case 16: //よく乾いている骨
			mes "太陽の光でよーく乾かした骨。";
			break;
		case 17: //服従の腕輪
			mes "綺麗な装飾がされてあるけど、";
			mes "どこか悲しそうに見える腕輪。";
			break;
		case 18: //光っている石
			mes "綺麗に光っている石！";
			break;
		case 19: //宛てがない手紙
			mes "送る相手の名前が無くて";
			mes "届けられなかった手紙。";
			break;
		case 20: //彼女の想い
			mes "ある女の子の秘密の想いが";
			mes "込められた書物。";
			break;
		case 21: //組織の掟
			mes "組織が持つ厳しい規律が";
			mes "感じられる象徴！";
			break;
		case 22: //悪魔召還書
			mes "悪魔を召還する秘法が書かれている";
			mes "禁じられた書物！";
			break;
		case 23: //闇の契約書
			mes "その名の通りの契約書！";
			break;
		case 24: //純潔の小太刀
			mes "純潔を象徴するかのような";
			mes "白銀の刃を持つ小太刀！";
			break;
		case 25: //熱帯のバナナ
			mes "熱帯地方で育った最高級のバナナ！";
			break;
		}
		mes '@mobname$+ "の大好物！";
		next;
		if(countitem('@itemid) < 1) {
			mes "[ポウ]";
			mes "……って、どこにあるの？";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "だからここに！";
			mes " ";
			mes "…………あれ？";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "えーっと……";
			mes "ど、どこにやったかな？";
			mes "ちょ、ちょっと待って！";
			mes "すぐ探してくるから！";
			close;
		}
		mes "[ポウ]";
		mes "へぇ……それで" +'@mobname$+ "を";
		mes "テイミングできるんだ……";
		mes "……うん、ありがとう。";
		mes "それじゃ、この子はあげるけど、";
		mes "ちゃんと育ててあげてよね！";
		next;
		mes "[ポウ]";
		mes "あ、ついでにこれもあげる。";
		mes "クリスマスプレゼント！";
		mes "色々としてくれたお礼。";
		mes "ありがとね！";
		mes "じゃーねー。";
		mes "メリークリスマース！";
		set XMAS_2EVE,5;
		delitem '@itemid,1;
		if(@menu <= 5)
			getitem 12200,3;
		else if(@menu <= 11 || @menu == 14)
			getitem 12200,5;
		else if(@menu <= 21) {
			getitem 12200,7;
			getitem 12130,1;
		}
		else {
			getitem 12200,10;
			getitem 12130,3;
		}
		makepet 9029;
		close;
	case 5:
		mes "[ポウ]";
		mes "僕があげた卵、どうなってる？";
		mes "ホントはちゃんと育てたかったな……";
		next;
		mes "[ポウ]";
		mes "僕の代わりにちゃんと育ててよ！";
		mes "約束だからね！";
		close;
	}
}

prontera.gat,226,306,3	script	ホーリー	79,{
	if(XMAS_2EVE != 2) {
		misceffect 75;
		mes "[ホーリー]";
		mes "楽しいこの日がやってきた♪";
		mes "みんなはとっても幸せに♪";
		next;
		mes "[ホーリー]";
		mes "メリークリスマ～ス♪";
		mes "今年も素敵なクリスマスを";
		mes "すごしましょ～";
		if(XMAS_2EVE != 1)
			close;
		next;
		mes "[ホーリー]";
		mes "でも、あなたにとって";
		mes "素敵な日じゃないみたいですね？";
		mes "こんなに素晴らしい日なのに、";
		mes "顔色がよくありませんよ？";
		mes (Sex? "兄弟": "姉妹")+ "よ、何か心配の種でも";
		mes "あるのですか？";
		next;
		mes "[ホーリー]";
		mes "私に出来ることがあるなら、";
		mes "何でもお手伝いいたしますよ。";
		mes "私を信じて、";
		mes "悩みを言ってみてください。";
		next;
		if(select("悩みなんてありません","実は……")==1) {
			mes "[ホーリー]";
			mes "そうなのですか？";
			mes "では、ご一緒にこのクリスマスを";
			mes "楽しみましょう！";
			next;
			misceffect 75;
			mes "[ホーリー]";
			mes "楽しいこの日がやってきた♪";
			mes "みんなはとっても幸せに♪";
			next;
			mes "[ホーリー]";
			mes "メリークリスマ～ス♪";
			mes "今年も素敵なクリスマスを";
			mes "すごしましょ～";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "実は……";
		mes "不気味な模様を浄化できないかと思い、";
		mes "この大聖堂を訪ねにきました。";
		next;
		mes "[ホーリー]";
		mes "えぇッ!?　不気味な模様ですって!?";
		mes "こんな神聖な日に、悪魔がどこかで";
		mes "何かしているというのですか!?";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "いえ……それがまだ、";
		mes "悪魔か何かわからなくて……";
		mes "実は、その模様はたま……";
		next;
		mes "[ホーリー]";
		mes "あああ！　そんな邪悪な存在が";
		mes "近くにいるというのに";
		mes "何も気づかなかったなんて！";
		mes "……そう……そうね！";
		mes "悪ふざけばかりするアンソニのせいね！";
		mes "そう、きっとそうよ！";
		next;
		mes "[ホーリー]";
		mes "神の意向に沿い、邪悪なる者に";
		mes "無慈悲なる天罰を下しましょう！";
		mes "さあ！　どこにいるのですか！";
		mes "その悪魔は！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あ……いえ……";
		mes "そうじゃなくて、私の話をき……";
		next;
		mes "[ホーリー]";
		mes "さぁ！　すぐに案内してください！";
		mes "この手は神を奉ずる手！";
		mes "この手をもって、悪魔をこの地から";
		mes "退散させましょう！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "だから！";
		mes "そうじゃないんですって!!";
		next;
		mes "-あなたはホーリーさんに";
		mes "ポウが見つけた卵について";
		mes "落ち着いて、正確に説明した-";
		next;
		mes "[ホーリー]";
		mes "アハッ、そういうことだったのですね？";
		mes "そうならそうと早く言ってくださいよ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "いや……聞いてなかったし……";
		next;
		mes "[ホーリー]";
		mes "では、邪悪な模様が描かれた卵を";
		mes "浄化したいのですね。";
		mes "それなら簡単です。";
		mes "^0000FF祝福の粉^000000をかければいいだけです。";
		next;
		mes "[ホーリー]";
		mes "材料を持ってきてくだされば";
		mes "私でも作れます。";
		mes "がんばって材料を集めてきてください。";
		set XMAS_2EVE,2;
		close;
	}
	if(countitem(733) < 1 || countitem(715) < 1 || countitem(716) < 1 || countitem(523) < 3) {
		mes "[ホーリー]";
		mes "材料さえあれば^0000FF祝福の粉^000000を";
		mes "作ってさしあげますよ？";
		mes "さぁ、早く集めてきてください。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……材料を聞いてないのですが……";
		next;
		mes "[ホーリー]";
		mes "…………はい！";
		mes "^0000FF損傷したダイヤモンド 1個、";
		mes "イエロージェムストーン 1個、";
		mes "レッドジェムストーン 1個、";
		mes "聖水 3個^000000。";
		mes "以上です！";
		next;
		mes "[ホーリー]";
		mes "……物忘れが酷いのかしら……";
		mes "ちゃんと言ったと思ったのに……";
		mes "…………";
		mes "……ぁ、ほら！";
		mes "早く集めてきてください！";
		close;
	}
	misceffect 75;
	mes "[ホーリー]";
	mes "楽しいこの日がやってきた♪";
	mes "みんなはとっても幸せに♪";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "あの……ホーリーさん？";
	mes "材料を持ってきました。";
	next;
	mes "[ホーリー]";
	mes "はい？";
	mes "材料？";
	mes "……何の話ですか？";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "^0000FF祝福の粉^000000を作ってくれるって";
	mes "おっしゃったじゃないですか！";
	mes "忘れたんですか!?";
	next;
	mes "[ホーリー]";
	mes "………………………………ぇ？";
	next;
	mes "[ホーリー]";
	mes "…………";
	mes "あ……いや……アハハハハハハハ。";
	mes "忘れてませんよ！";
	mes "ホントに忘れてませんからね！";
	next;
	mes "[ホーリー]";
	mes "…………";
	mes "……で…………";
	mes "どうして^0000FF祝福の粉^000000を";
	mes "作るんでしたっけ？";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "（すっかり忘れてるし！）";
	mes "……ですから……";
	next;
	switch(select("悪魔を退治するために","卵を浄化するために","昨夜の二日酔いが……")) {
	case 1:
		mes "[ホーリー]";
		mes "……ぇ？";
		mes "悪魔退治ですか？";
		next;
		mes "[ホーリー]";
		mes "それなら！";
		mes "わざわざ^0000FF祝福の粉^000000を";
		mes "用意する必要なんてありません！";
		next;
		mes "[ホーリー]";
		mes "私が直接、悪魔たちに";
		mes "裁きを下してさしあげます！";
		close;
	case 2:
		break;
	case 3:
		mes "[ホーリー]";
		mes "あらあら。";
		mes "クリスマスだからってはしゃぐから";
		mes "そうなっちゃうんですよ。";
		mes "お酒を飲むなら、ちゃんと自分の体と";
		mes "相談して飲まないといけません。";
		next;
		mes "[ホーリー]";
		mes "それに、二日酔いには^0000FF祝福の粉^000000より";
		mes "もっと効くものがありますよ。";
		mes "さあ、気を楽にしてください。";
		next;
		misceffect 75;
		misceffect 194,"";
		emotion 23,"";
		percentheal -30,0;
		mes "[ホーリー]";
		mes "ではいきますよ！";
		mes "「傷を撫でる神の癒し！　第1楽章！」";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "うわ！";
		mes "あ、頭が割れそうに痛い！";
		next;
		mes "[ホーリー]";
		mes "第74楽章まで聞けば";
		mes "気持ちよくなりますよ。";
		mes "ぁ、どこに行くんですか？";
		mes "まだ73楽章も残っているんですよ！";
		close;
	}
	mes "[ホーリー]";
	mes "……あぁ～そうでしたねぇ……";
	mes "ぁ……いえいえ、わかってますよ。";
	mes "わかっていましたとも！";
	next;
	mes "[ホーリー]";
	mes "材料もちゃんとあるようですし、";
	mes "さっそく作りますね！";
	next;
	emotion 23;
	misceffect 101;
	mes "[ホーリー]";
	mes "まず、損傷したダイヤモンドを";
	mes "砕いて粉にします。";
	mes "これは少しコツが必要ですが、";
	mes "ある鍛冶屋の方に教わりました。";
	next;
	mes "[ホーリー]";
	mes "一度驚く振りをしながら割るのが";
	mes "ポイントです。";
	next;
	misceffect 302;
	mes "[ホーリー]";
	mes "次に、大きな器に聖水を注ぎ、";
	mes "ゆっくりと加熱しながら、";
	mes "レッドジェムストーンと";
	mes "イエロージェムストーンを入れ、";
	mes "完全に溶かします。";
	next;
	misceffect 256;
	mes "[ホーリー]";
	mes "ジェムストーンと聖水が混ざった";
	mes "液体に、先ほどの粉を混ぜ合わせ、";
	mes "水分が蒸発するまで加熱すれば完成！";
	mes "はい、^0000FF祝福の粉^000000！";
	next;
	emotion 18;
	mes "[ホーリー]";
	mes "ではさっそく、先ほど話された卵を";
	mes "浄化してきてください。";
	mes "良い結果となるよう、";
	mes "あなたの幸運を祈ります。";
	next;
	mes "^0000FF-祝福の粉を手に入れた！-^000000";
	set XMAS_2EVE,3;
	close;
}

//==============================================================
// サンタクロースに代わって
//==============================================================
prontera.gat,156,268,3	script	サンタクロース	718,{
	switch(XMAS_3EVE) {
	case 0:
		mes "[サンタクロース]";
		mes "ホーホーホー";
		mes "メリークリスマス！";
		mes "今年も良い子でいたかな？";
		next;
		mes "[サンタクロース]";
		mes "君はクリスマスと聞いて";
		mes "何が一番最初に思いつくかな？";
		next;
		switch(select("サンタクロースです！","プレゼントボックスです！","赤い鼻です！","サンタのぼうしです！","カップル地獄!!")) {
		case 1:
			break;
		case 2:
			mes "[サンタクロース]";
			mes "プレゼントボックスとな？";
			mes "寝ている間に枕元に置かれる";
			mes "サンタクロースからのプレゼントは、";
			mes "朝が待ち遠しくなるもんじゃ。";
			next;
			mes "[サンタクロース]";
			mes "じゃが、毎年クリスマスに暴れる";
			mes "アンソニという悪いサンタがおる。";
			mes "世界中にいるサンタの悩みの種じゃ。";
			mes "ホーホーホー";
			close;
		case 3:
			mes "[サンタクロース]";
			mes "赤い鼻とな？";
			mes "わしの長年の友人が持つ";
			mes "赤い鼻のことかのぅ？";
			mes "友人の鼻はひかっておるから、";
			mes "とても役にたっておるよ。";
			next;
			mes "[サンタクロース]";
			mes "そういえば、今年はルティエで";
			mes "それを見立てたアイテムを";
			mes "作っているそうじゃ。";
			next;
			mes "[サンタクロース]";
			mes "皆で光る鼻をつければ";
			mes "キラキラして楽しいクリスマスを";
			mes "すごせるんじゃないかのぅ？";
			mes "ホーホーホー";
			close;
		case 4:
			mes "[サンタクロース]";
			mes "サンタのぼうしとな？";
			mes "実は、わしのようなサンタが";
			mes "被っているサンタのぼうしと、";
			mes "モンスターが被っている";
			mes "サンタのぼうしは別物なんじゃよ。";
			next;
			mes "[サンタクロース]";
			mes "しかしのぅ、この広い世界には";
			mes "見かけだけのサンタのぼうしを元に";
			mes "わしの持つサンタのぼうしに近い";
			mes "力を持たせる事が出来るデザイナーが";
			mes "いるらしい……";
			next;
			mes "[サンタクロース]";
			mes "毎年、クリスマスを狙って";
			mes "多くのモンスターが現れるが、";
			mes "アンソニという悪いサンタだけは";
			mes "簡単には捕まらない理由が";
			mes "その帽子のおかげという";
			mes "うわさがあるんじゃ。";
			close;
		case 5:
			mes "[サンタクロース]";
			mes "おや？";
			mes "少し前にあった青年も";
			mes "君と同じような事を言ってたが……";
			next;
			mes "[サンタクロース]";
			mes "今度は一体何をするのやら……";
			mes "まったく、クリスマスだというのに";
			mes "不安の種があるとはのぅ。";
			mes "ホーホーホー";
			close;
		}
		mes "[サンタクロース]";
		mes "ホーホーホー！";
		mes "君はとっても良い子みたいじゃな！";
		mes "その君を見込んで、少し";
		mes "お願いがあるのだが、";
		mes "いいかな？";
		next;
		if(select("嫌です","何でもどうぞ！")==1) {
			mes "[サンタクロース]";
			mes "ホッホッホ。";
			mes "自分の気持ちに正直じゃな。";
			next;
			mes "[サンタクロース]";
			mes "気が変わったらいつでも来なさい。";
			mes "クリスマスは手がいくつあっても";
			mes "足りないんじゃ。";
			close;
		}
		mes "[サンタクロース]";
		mes "うむ。";
		mes "しっかり者で心優しいのぅ。";
		mes "わしが見込んだだけある。";
		next;
		mes "[サンタクロース]";
		mes "時間が無いからすぐに説明するぞ。";
		mes "君には世界中の子供たちを幸せにする";
		mes "手伝いをしてもらいたいんじゃ。";
		next;
		mes "[サンタクロース]";
		mes "そう、プレゼントボックスの配達じゃ。";
		mes "毎年この時期は、手がいくつあっても";
		mes "足りないぐらいなんじゃ。";
		next;
		set XMAS_3EVE,rand(1,5);
		mes "[サンタクロース]";
		mes "さあ、このプレゼントを受け取る";
		mes "子供の名前は「" +(XMAS_3EVE==1? "アンズ": (XMAS_3EVE==2? "レイシ": (XMAS_3EVE==3? "デーマリー": (XMAS_3EVE==4? "ミヒル": "イシテ"))))+ "」じゃ。";
		switch(XMAS_3EVE) {
		case 1:
			mes "^0000FF迷宮の森の近くを";
			mes "探検するのが好きな女の子。^000000";
			break;
		case 2:
			mes "^0000FFフェイヨンにいる無口な女の子。^000000";
			break;
		case 3:
			mes "^0000FFアルベルタ近くの";
			mes "難破船にいる男の子。^000000";
			break;
		case 4:
			mes "^0000FFジュノーにいる可愛い女の子。^000000";
			break;
		case 5:
			mes "^0000FFルティエにいる善良な少女？^000000";
			mes "……疑問系……？";
			break;
		}
		mes (XMAS_3EVE==5? "で、": "")+ "では、頼んだぞ！";
		next;
		mes "-リボンに「" +(XMAS_3EVE==1? "アンズ": (XMAS_3EVE==2? "レイシ": (XMAS_3EVE==3? "デーマリー": (XMAS_3EVE==4? "ミヒル": "イシテ"))))+ "へ」と書かれた";
		mes "プレゼントボックスを受け取った-";
		break;
	default:
		mes "[サンタクロース]";
		mes "プレゼントを受け取る子供の名前は";
		mes "「" +(XMAS_3EVE==1? "アンズ": (XMAS_3EVE==2? "レイシ": (XMAS_3EVE==3? "デーマリー": (XMAS_3EVE==4? "ミヒル": "イシテ"))))+ "」じゃ。";
		switch(XMAS_3EVE) {
		case 1:
			mes "^0000FF迷宮の森の近くを";
			mes "探検するのが好きな女の子。^000000";
			break;
		case 2:
			mes "^0000FFフェイヨンにいる無口な女の子。^000000";
			break;
		case 3:
			mes "^0000FFアルベルタ近くの";
			mes "難破船にいる男の子。^000000";
			break;
		case 4:
			mes "^0000FFジュノーにいる可愛い女の子。^000000";
			break;
		case 5:
			mes "^0000FFルティエにいる善良な少女？^000000";
			break;
		}
		mes (XMAS_3EVE==5? "で、": "")+ "では、頼んだぞ！";
		break;
	case 6:
		mes "[サンタクロース]";
		mes "どうじゃった？";
		mes "プレゼントは無事に渡せたかのぅ？";
		next;
		mes "[サンタクロース]";
		mes "子供達がプレゼントをもらって";
		mes "喜ぶ顔を見ると、幸せにならんか？";
		mes "ホーホーホー";
		next;
		mes "[サンタクロース]";
		mes "わしの頼みを聞いてくれてありがとう。";
		mes "これは感謝の気持ちじゃ。";
		mes "この袋の中に手を入れて、";
		mes "好きな物を一つだけ持って行きなさい。";
		next;
		mes "[サンタクロース]";
		mes "ご苦労様。";
		mes "こんなおいぼれを助けてくれて";
		mes "本当にありがとう。";
		mes "ホーホーホー";
		set XMAS_3EVE,7;
		switch(rand(30)) {
		case 0:
		case 1:
		case 2:
			getitem 529,10; //キャンディ 10
			break;
		case 3:
		case 4:
		case 5:
			getitem 530,7; //スティックキャンディ 7
			break;
		case 6:
		case 7:
		case 8:
			getitem 538,5; //よく焼いたクッキー 5
			break;
		case 9:
		case 10:
		case 11:
			getitem 558,3; //チョコレート 3
			break;
		case 12:
		case 13:
		case 14:
			getitem 12200,3; //クリスマスケーキ 3
			break;
		case 15:
		case 16:
			getitem 12200,5; //クリスマスケーキ 5
			break;
		case 17:
			getitem 12200,7; //クリスマスケーキ 7
			break;
		case 18:
		case 19:
			getitem 522,1; //マステラの実 1
			break;
		case 20:
			getitem 526,1; //ローヤルゼリー 1
			break;
		case 21:
			getitem 608,1; //イグドラシルの種 1
			break;
		case 22:
		case 23:
		case 24:
			getitem 12130,1; //菓子包み 1
			break;
		case 25:
			getitem 644,1; //プレゼントボックス 1
			break;
		case 26:
			getitem 604,1; //古木の枝 1
			break;
		case 27:
			getitem 2236,1; //サンタのぼうし 1
			break;
		case 28:
			getitem 2262,1; //ピエロの鼻 1
			break;
		case 29:
			getitem 7034,1; //穴が開いている赤い靴下 1
			break;
		}
		close;
	case 7:
		mes "[サンタクロース]";
		mes "おかげで少し余裕ができたわい。";
		mes "また忙しくなったら";
		mes "このおいぼれの仕事を";
		mes "手伝っておくれ。";
		next;
		mes "[サンタクロース]";
		mes "いくら忙しくても、今はクリスマス。";
		mes "君も色んな事を楽しむんじゃぞ。";
		mes "ホーホーホー";
		set XMAS_3EVE,0;
		close;
	}
	mes "[サンタクロース]";
	mes "プレゼントを届ける時は、";
	mes "^0000FF「ルイーゼのサンタ帽」と「白ひげ」^000000";
	mes "を必ず着けていくんじゃぞ。";
	mes "子供たちが持つサンタクロースの";
	mes "イメージを壊しちゃならん。";
	mes "ホーホーホー";
	close;
}

prt_fild01.gat,141,363,3	script	アンズ	96,{
	if(XMAS_3EVE == 6) {
		mes "[アンズ]";
		mes "とっっっても素敵なプレゼント！";
		mes "本当にありがとう!!";
		mes "これからも良い子でいるね！";
		mes "キャー、キャアアアアアア!!";
		next;
		mes "-少女はプレゼントを抱きしめながら";
		mes "嬉しそうにはしゃいでいる-";
		close;
	}
	mes "[アンズ]";
	mes "鐘を鳴らしなさい、鐘の音を♪";
	mes "喜びの歌を歌いながら走ろう♪";
	if(XMAS_3EVE != 1)
		close;
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "可愛い歌声だね。";
	mes "はい、これ。";
	mes "今年も良い子でいたアンズに";
	mes "サンタさんからのプレゼントだよ。";
	next;
	if(getequipid(1) != 5136 || getequipid(10) != 2241) {
		mes "[アンズ]";
		mes "……あのねぇ……";
		mes "サンタクロースっていうのはね……";
		next;
		mes "[アンズ]";
		mes "クリスマスに良い子に";
		mes "プレゼントを持ってきてくれるの。";
		mes "そこまではあってるけど……";
		next;
		misceffect 1,"";
		emotion 23,"";
		percentheal -50,0;
		mes "[アンズ]";
		mes "赤い帽子を被って、";
		mes "白いおひげを生やしてないのは、";
		mes "それこそ真っ赤な偽物なの！";
		mes "子供だからってバカにしないでよ！";
		close;
	}
	mes "[アンズ]";
	mes "え？";
	mes "あ、ありがとう。サンタさん。";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "さっそく箱を開けてみたら？";
	mes "君の欲しい物が";
	mes "入っているかもしれないよ。";
	next;
	mes "-アンズは少し嬉しそうにしながら、";
	mes "ゆっくりとプレゼントボックスの";
	mes "包装を解いた-";
	next;
	emotion 9;
	mes "[アンズ]";
	mes "こ！　これは！";
	mes "ジェームズオリーブの食器セット！";
	mes "キャアアアアアアアアア!!";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……ッ…………";
	mes "……気にいった？";
	next;
	emotion 18;
	mes "[アンズ]";
	mes "もー！　ほんっと！";
	mes "ほんとに嬉しい！";
	mes "ありがとう！";
	mes "一生家宝にするわ！";
	mes "キャアアアアアア!!";
	next;
	mes "-少女は迷惑なぐらい喜んでいる-";
	mes "-プレゼントは無事に渡せた！-";
	set XMAS_3EVE,6;
	close;
}

payon.gat,242,282,3	script	レイシ	703,{
	if(XMAS_3EVE == 6) {
		mes "[レイシ]";
		mes "本当に……嬉しい……";
		mes "これからも……";
		mes "良い子で……います……";
		next;
		mes "-少女はプレゼントを";
		mes "大事そうに抱きしめながら、";
		mes "軽く会釈をした-";
		close;
	}
	mes "[レイシ]";
	mes "静かな夜……神秘的な夜……";
	mes "きっと……あなたは……";
	mes "やってくる……";
	if(XMAS_3EVE != 2)
		close;
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "素敵な歌声だね。";
	mes "はい、これ。";
	mes "今年も良い子でいたレイシに";
	mes "サンタさんからのプレゼントだよ。";
	next;
	if(getequipid(1) != 5136 || getequipid(10) != 2241) {
		mes "[レイシ]";
		mes "……";
		next;
		misceffect 1,"";
		emotion 23,"";
		percentheal -50,0;
		mes "[レイシ]";
		mes "……サンタじゃない……";
		close;
	}
	mes "[レイシ]";
	mes "……ありがとう……サンタさん……";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "さっそく箱を開けてみたら？";
	mes "君の欲しい物が";
	mes "入っているかもしれないよ。";
	next;
	mes "-レイシは表情を変えずに、";
	mes "ゆっくりとプレゼントボックスの";
	mes "包装を解いた-";
	next;
	emotion 9;
	mes "[レイシ]";
	mes "……これは……";
	mes "ジョシュア先生が描いた……";
	mes "マイゴツと……タクの……";
	mes "悲しい恋の……物語……";
	mes "悲哀シリーズ……初版……";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……ぇ…………";
	mes "気に……いっ……た？";
	next;
	emotion 9;
	mes "[レイシ]";
	mes "本当に……嬉しい……";
	mes "ありがとう……";
	mes "一生……家宝にします……";
	next;
	mes "-少女が本当に喜んでいるのか、";
	mes "無表情な為わからないが、";
	mes "プレゼントは無事に渡せた！-";
	set XMAS_3EVE,6;
	close;
}

alb2trea.gat,110,99,0	script	デーマリー	706,{
	if(XMAS_3EVE == 6) {
		mes "[デーマリー]";
		mes "もっと釣竿欲しいからな！";
		mes "これからも良い子でいるよ！";
		next;
		mes "-少年は両手でプレゼントを抱えて、";
		mes "とても嬉しそうに笑った-";
		close;
	}
	mes "[デーマリー]";
	mes "白いおひげを揺らして滑る♪";
	mes "そりで走って気持ちは爽快♪";
	if(XMAS_3EVE != 3)
		close;
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "いい歌声だね。";
	mes "はい、これ。";
	mes "今年も良い子でいたデーマリーに";
	mes "サンタさんからのプレゼントだよ。";
	next;
	if(getequipid(1) != 5136 || getequipid(10) != 2241) {
		mes "[デーマリー]";
		mes "……サンタ？";
		next;
		mes "[デーマリー]";
		mes "はん、嘘ってばればれだよ。";
		next;
		misceffect 1,"";
		emotion 23,"";
		percentheal -50,0;
		mes "[デーマリー]";
		mes "サンタはな、赤い帽子を被って";
		mes "白いひげを生やしてるんだよ！";
		mes "そんな事も知らねぇのかよ。";
		close;
	}
	mes "[デーマリー]";
	mes "わぁッ！";
	mes "クリスマスプレゼントだ！";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "さっそく箱を開けてみたら？";
	mes "君の欲しい物が";
	mes "入っているかもしれないよ。";
	next;
	mes "-デーマリーはわくわくしながら、";
	mes "急いでプレゼントボックスの";
	mes "包装を解いた-";
	next;
	emotion 18;
	mes "[デーマリー]";
	mes "やった！";
	mes "かっこいい釣竿とミミズのセット！";
	mes "これで釣りができるぜ！";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……ぇ…………";
	mes "気に……いったの……？";
	next;
	emotion 52;
	mes "[デーマリー]";
	mes "あったりまえだ！";
	mes "これからさっそく釣りをするぜ！";
	mes "いやっほぅぅぅぅぅ！";
	next;
	mes "-少年はすごく嬉しそうだ-";
	mes "-プレゼントは無事に渡せた！-";
	set XMAS_3EVE,6;
	close;
}

yuno.gat,103,185,3	script	ミヒル	72,{
	if(XMAS_3EVE == 6) {
		mes "[ミヒル]";
		mes "素敵なプレゼントありがとう！";
		mes "これからも良い子でいるね。";
		mes "フフフフフ……";
		next;
		mes "-少女はプレゼントを抱きしめて、";
		mes "とても嬉しそうに笑った-";
		close;
	}
	mes "[ミヒル]";
	mes "泣いてはいけない、泣いてはいけない♪";
	mes "サンタさんは泣いてる子供に";
	mes "会いにこない♪";
	if(XMAS_3EVE != 4)
		close;
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "綺麗な歌声だね。";
	mes "はい、これ。";
	mes "今年も良い子でいたミヒルに";
	mes "サンタさんからのプレゼントだよ。";
	next;
	if(getequipid(1) != 5136 || getequipid(10) != 2241) {
		mes "[ミヒル]";
		mes "……サンタさん？";
		next;
		mes "[ミヒル]";
		mes "ふん、嘘つき！";
		next;
		misceffect 1,"";
		emotion 23,"";
		percentheal -50,0;
		mes "[ミヒル]";
		mes "サンタさんはそんなかっこじゃない！";
		close;
	}
	mes "[ミヒル]";
	mes "わぁ！　ありがとう、サンタさん！";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "さっそく箱を開けてみたら？";
	mes "君の欲しい物が";
	mes "入っているかもしれないよ。";
	next;
	mes "-ミヒルはわくわくしながら、";
	mes "綺麗にプレゼントボックスの";
	mes "包装を解いた-";
	next;
	emotion 18;
	mes "[ミヒル]";
	mes "わぁ……間違いない！";
	mes "これは、あのキッズ様が";
	mes "着ていたという幻のマフラー！";
	mes "あぁ……これがあの方の香り……";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "……ぇ…………";
	mes "気に……いったの……？";
	next;
	emotion 52;
	mes "[ミヒル]";
	mes "えぇ、もちろん！";
	mes "フフフ、ありがとう。";
	mes "ずっと大切に使うね。";
	mes "フフフフフフ。";
	next;
	mes "-少女の笑顔がどこか怖いが、";
	mes "プレゼントは無事に渡せた！-";
	set XMAS_3EVE,6;
	close;
}

//==============================================================
// キャンプファイア大作戦
//==============================================================
xmas.gat,137,233,3	script	イシテ	793,{
	if(XMAS_3EVE == 6) {
		mes "[イシテ]";
		mes "プレゼント、とっても気に入ったわ。";
		mes "フフフ……これからも良い子でいるわ。";
		mes "フフフフフフフ……";
		next;
		mes "-少女はプレゼントの箱を抱えながら";
		mes "どこか不気味な微笑みを向けた-";
		close;
	}
	if(XMAS_3EVE == 5) {
		mes "[イシテ]";
		mes "マッチ、マッチはいりませんか～？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（どこかで見たような子だな……）";
		mes "こんなに寒いのに大変だね。";
		mes "はい、これ。";
		mes "今年も良い子でいたイシテに";
		mes "サンタさんからのプレゼントだよ。";
		next;
		if(getequipid(1) != 5136 || getequipid(10) != 2241) {
			mes "[イシテ]";
			mes "……サンタ？";
			next;
			misceffect 49,"";
			emotion 23,"";
			percentheal -50,0;
			mes "[イシテ]";
			mes "サンタって言う前に、";
			mes "少しはそれらしい変装でもしたら？";
			close;
		}
		mes "[イシテ]";
		mes "え？";
		mes "ほ、本当ですか？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "さっそく箱を開けてみたら？";
		mes "君の欲しい物が";
		mes "入っているかもしれないよ。";
		next;
		mes "-イシテは嬉しそうな顔をしながら、";
		mes "慎重にプレゼントボックスの";
		mes "包装を解いた-";
		next;
		emotion 29;
		mes "[イシテ]";
		mes "……ふふ……これは使えるわ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "何？　気にいった？";
		next;
		emotion 52;
		mes "[イシテ]";
		mes "フフフ……ありがとう。";
		mes "早速使わせてもらうわ。";
		mes "フフフフフフフ……";
		next;
		mes "-少女の笑みがどこか不気味だったが、";
		mes "プレゼントは無事に渡せた！-";
		set XMAS_3EVE,6;
		close;
	}
	switch(XMAS_4EVE) {
	case 0:
		mes "[イシテ]";
		mes "ゴホン、ゴホン……";
		mes "マッチ、マッチはいりませんか～？";
		mes "チェペットから奪っ……ぁ……、";
		mes "えっと……チェペットが";
		mes "落としたマッチなんです……";
		mes "……ゴホンゴホン……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（どこかで見たような子だな……）";
		mes "（なにか……話しかけると";
		mes "大変な事になる気がする……）";
		next;
		mes "[イシテ]";
		mes "ゴホン、ゴホン、ゴホン！";
		mes "ああ……このマッチを全部売らないと、";
		mes "可哀相な私のお兄ちゃんは";
		mes "今日もご飯を食べれない！";
		next;
		mes "[イシテ]";
		mes "ゴホ！　ゴホン、ゴホン！";
		mes "お兄ちゃんはもう五日も！";
		mes "五日もご飯を食べていないのに!!";
		mes "ゴホ……ゴホ……ゴホ……";
		next;
		mes "-女の子はしゃがみ込み、セキ込んだ-";
		next;
		mes "-っと思っていたら、";
		mes "いきなりあなたを指でさし、";
		mes "にらみつけてきた-";
		next;
		mes "[イシテ]";
		mes "あなた、私の事見てたでしょ？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "え？　……いや、その……";
		next;
		emotion 23,"";
		mes "-女の子はいきなりの事で戸惑う";
		mes "あなたの手首をつかみ、";
		mes "ぐいっと引き寄せた-";
		mes "-そして、小さな声でささやいた-";
		next;
		mes "[イシテ]";
		mes "なにあんた。";
		mes "こんな可哀想な女の子を見ても";
		mes "何とも思わないの？";
		mes "何も感じないの？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "え……あ、いや……";
		mes "その……ごめんなさい……";
		mes "マッチ……買います。";
		mes "いくらですか？";
		next;
		mes "[イシテ]";
		mes "繊細な少女の心を傷つけておいて、";
		mes "マッチ一つで済むと思ってんの？";
		mes "世の中そんなに甘くないのよ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ど……どうすればいいんですか？";
		next;
		mes "[イシテ]";
		mes "別に難しい事じゃないわ。";
		mes "ちょっとしたお願いを一つ";
		mes "聞いて欲しいってだけ。";
		mes "オーケー？";
		next;
		mes "[イシテ]";
		mes "この家に「イシル」って人がいるわ。";
		mes "その人を少し手伝ってあげて。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "なんで私がそんなことし……";
		next;
	default:
		emotion 18;
		emotion 23,"";
		mes "[イシテ]";
		mes "フフフ……カプラ倉庫かぁ……";
		mes "ねぇ？";
		mes "キャンプファイアは好き？";
		mes "私はだ～い好き♪";
		mes "フフ……フフフフフ……";
		next;
		mes "-少女は持っていたマッチに火をつけて";
		mes "微笑んでいる-";
		mes "-…………-";
		mes "-言うとおりにしたほうがいいだろう-";
		if(XMAS_4EVE == 0)
			set XMAS_4EVE,1;
		close;
	case 11:
		mes "[イシテ]";
		mes "……お疲れ様。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "言われた事はした！";
		mes "君の事も言わなかった！";
		mes "もういいでしょ！";
		next;
		mes "[イシテ]";
		mes "……そうね……";
		mes "でも、あと一つだけいい？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ま、またぁ!?";
		mes "いくらなんでも酷すぎない!?";
		next;
		mes "[イシテ]";
		mes "……そのように言われると……";
		mes "私、傷ついちゃって……";
		mes "心がとっても寒くなっちゃう……";
		mes "そんな心を暖めるには、";
		mes "マッチを灯して……";
		mes "そして手が滑って……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あーもう、わかった！";
		mes "わかったよ！";
		mes "今度は何!?";
		mes " ";
		mes "（イシテ！　恐ろしい少女！）";
		next;
	case 12:
		if(XMAS_4EVE == 12 && countitem(525))
			break;
		mes "[イシテ]";
		mes "「^0000FF万能薬^000000」";
		mes "1個でいいから手に入る？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "え？　あーそれ位なら……";
		mes "うん、それならすぐに手に入る！";
		mes "だから火遊びはだめだからね！";
		next;
		mes "-少女はしばらくうつむいていたが、";
		mes "持っていたマッチを、フッと吹いて";
		mes "火を消した-";
		next;
		mes "[イシテ]";
		mes "ふぅ……";
		mes "早く行ってくれないと、";
		mes "マッチが……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "行ってまいります！";
		if(XMAS_4EVE == 11)
			set XMAS_4EVE,12;
		close;
	}
	//12の続き
	mes "[" +strcharinfo(0)+ "]";
	mes "た、ただいま！";
	mes "ほら！　万能薬！";
	next;
	mes "[イシテ]";
	mes "……………………ありがとう。";
	next;
	emotion 23,"";
	mes "[" +strcharinfo(0)+ "]";
	mes "も、もういいでしょ！";
	mes "……これ以上は……ぇ？";
	next;
	emotion 32;
	mes "-少女はマッチに点いていた火を";
	mes "小さな口で吹き消した-";
	next;
	mes "[イシテ]";
	mes "…………ふぅ……";
	mes "ありがとうございました。";
	mes "ずっと前にパパとママが";
	mes "いなくなってから、お兄ちゃん以外で";
	mes "こんなに構ってくれたのは";
	mes "あなたが初めてです……";
	next;
	mes "[イシテ]";
	mes "私のために無茶ばかりして、";
	mes "風邪をひいちゃったお兄ちゃん……";
	mes "そのお兄ちゃんに、この万能薬を";
	mes "どうしてもあげたかった……";
	next;
	mes "[イシテ]";
	mes "私のためにクリスマスツリーを";
	mes "準備するって言ってるけど、";
	mes "クリスマスツリーを作って";
	mes "暖かい家庭の真似をしたかったのは";
	mes "お兄ちゃん……";
	next;
	mes "[イシテ]";
	mes "そんなお兄ちゃんのために、";
	mes "最高のクリスマスを用意してあげよう！";
	mes "お兄ちゃんが夢見てたクリスマスに";
	mes "したかったから……";
	mes "あなたに色んな事をさせてしまった……";
	next;
	mes "[イシテ]";
	mes "……私の無茶なお願いを聞いてくれて、";
	mes "本当にありがとうございました……";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "あ、いや……ハハ……";
	mes "（お願いじゃなくて脅迫でしょ！）";
	next;
	mes "[イシテ]";
	mes "あなたの苦労に比べると";
	mes "大したものじゃないけど……";
	mes "これをどうぞ……";
	next;
	emotion 18;
	mes "[イシテ]";
	mes "これは^4A4AFFルイーゼ^000000というデザイナーから";
	mes "かっぱらっ…………";
	mes "……頂いたサンタの衣装です。";
	mes "気に入ってもらえると思います。";
	next;
	emotion 18,"";
	mes "[" +strcharinfo(0)+ "]";
	mes "ぇ……ぁ……これはどうも……";
	next;
	mes "[イシテ]";
	mes "じゃ、またがんばって。";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "え？　今、何て？";
	next;
	emotion 18;
	mes "[イシテ]";
	mes "いえ！　なんでもありません。";
	mes "さぁ、早くこれを受け取ってください。";
	next;
	sc_start3 SC_BLIND,0,0,0,0,5000,10;
	mes "-あなたは少女が渡してくれた箱を";
	mes "開けようとした-";
	mes "-その瞬間！-";
	mes "-後頭部から激しい痛みが走り、";
	mes "目の前が真っ黒になった-";
	next;
	mes "[イシテ]";
	mes "本当にありがとう。";
	mes "そして、またよろしく。";
	mes "フフフフフ。";
	next;
	mes "-意識を失う瞬間、";
	mes "少女がマッチに火を付け、";
	mes "ふっと息で吹き消すのが見えた-";
	mes "-そして、あなたの頭の中がどんどん";
	mes "真っ白になっていった……-";
	set XMAS_4EVE,0;
	delitem 525,1;
	getitem 12132,1;
	close;
}

xmas_in.gat,109,109,3	script	イシル	887,{
	switch(XMAS_4EVE) {
	case 0:
	case 1:
		mes "[イシル]";
		mes "……ううう……";
		mes "バイトをしなきゃいけないのに……";
		mes "ゲホゲホ……。";
		mes "今年もイシテにクリスマス";
		mes "プレゼントをあげたいのに……";
		mes "ヘックション！　ゲホゲホ……。";
		if(XMAS_4EVE != 1)
			close;
		next;
		mes "[イシル]";
		mes "よりによってこんな時に";
		mes "風邪をひくなんて……";
		mes "できの悪い兄でごめんよ……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "困っているんですか!?";
		mes "私が手伝いますよ！";
		next;
		mes "[イシル]";
		mes "えっ？　あ、誰？";
		mes "どうしてここに……？";
		mes "それに、どこかで見たような……";
		mes "ックシュン！　ゲホ。";
		next;
		emotion 28,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "早くやらなきゃいけない事を";
		mes "教えてください!!";
		mes "何です？　何をすればいいんですか!?";
		mes " ";
		mes "（キャンプファイアされる！";
		mes "キャンプファイアだけはだめだ!!）";
		next;
		mes "[イシル]";
		mes "ヒッ……あ、えと……";
		mes "やらなくちゃいけないのは";
		mes "ケーキを配達するバイトで……";
		mes "ゲホ、ゲホゲホ、ゲホ……";
		next;
		mes "[イシル]";
		mes "ヘックシュ！";
		mes "……今日まで一週間働けば……";
		mes "クシュ！　小さいけどツリーにできる";
		mes "もみの木をもらえ……";
		next;
		mes "[イシル]";
		mes "ゲホ……ゲホッ……";
		mes "風邪をひいちゃって……";
		mes "……ックシュ！　ゲホゲホ。";
		mes "体が辛くて……";
		next;
		mes "[イシル]";
		mes "ツリーも無い寂しいクリスマス……";
		mes "ゲホ……";
		mes "がっかりするイシテを思うと……";
		mes "でも、もう指に力が入らない……";
		mes "……ゲホ、ゲホ……";
		next;
		mes "[イシル]";
		mes "^4A4AFFレッドニア^000000さんが……";
		mes "待っているのに……";
		mes "ゲホ……ゴホ……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "いいから寝ててください！";
		mes "大丈夫、わかりました！";
		mes "後は任せてください！";
		mes "じゃ、私はこれで!!";
		next;
		mes "[イシル]";
		mes "え？　ゴホ……ちょっと待って。";
		mes "あなたは一体……";
		next;
		mes "-背中越しに声が聞こえたが、";
		mes "気にしていられない-";
		mes "-無視して「レッドニア」という人を";
		mes "訪ねに行こう！-";
		mes "-キャンプファイアだけは困る！-";
		set XMAS_4EVE,2;
		close;
	default:
		mes "[イシル]";
		mes "ゴホ……あ、あなたは……";
		mes "どうして^4A4AFFレッドニア^000000さんの……";
		mes "ゴホ！　仕事を聞いていったのですか？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……実は……";
		next;
		mes "[??????]";
		mes "…………";
		mes "-シュッ！-";
		next;
		mes "-窓の外から、";
		mes "マッチに火を点けるような";
		mes "摩擦音が聞こえてきた-";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（……しゃべるなって事か……）";
		mes "いえ、お気になさらずに！";
		mes "では、私はこれで！";
		next;
		mes "[イシル]";
		mes "え？　ゴホ……ちょっと待って。";
		mes "あなたは一体……";
		next;
		mes "-背中越しに声が聞こえたが、";
		mes "気にしていられない-";
		mes "-無視して「レッドニア」という人を";
		mes "訪ねに行こう！-";
		mes "-キャンプファイアだけは困る！-";
		close;
	case 9:
		mes "[イシル]";
		mes "ゴホ！　ゴホ……";
		mes "うぅ……ゴホゴホ……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "イシル！";
		mes "しっかりして！";
		mes "大丈夫ですか!?";
		next;
		mes "[イシル]";
		mes "…………ぇ？";
		mes "あなたは……";
		mes "……そ、その手に持っている木は!?";
		mes "まさか！";
		mes "僕のバイトを横取りしたんですか！";
		next;
		mes "[イシル]";
		mes "僕には、妹がいるのに……";
		mes "ゴホ！　ゴホ……";
		mes "二人だけで生活しなきゃいけないのに！";
		mes "それなのにあなたは！";
		mes "……グ……ゲホ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ご、誤解しないでください！";
		mes "そうじゃないんです！";
		mes "私はただ、君の手伝いをしたかった。";
		mes "ただそれだけなんです！";
		mes "この木も、バイトが無事に終わったから";
		mes "届けにきたんですよ？";
		next;
		mes "-朦朧としながら咳き込むイシルに";
		mes "小さなもみの木を触らせると、";
		mes "少しだけ驚いた顔をした-";
		next;
		mes "[イシル]";
		mes "……ゴホ……どうして？";
		mes "初めて会う僕をどうして";
		mes "助けてくれるんですか……？";
		mes "……いや……どこかで会ったような";
		mes "気もするけど……ゴホ！　ゴホ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "それは君の……";
		mes "…………!?";
		next;
		mes "-視界の隅に入った窓の外には、";
		mes "火の点いたマッチを持つ";
		mes "小さな手があった-";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "え……ぁ……そんなの当然です！";
		mes "私は……私は……";
		mes "えーっと…………私は……";
		mes "（もう、何でもいいや！）";
		mes "そう！　私は……";
		next;
		input '@word$;
		emotion 23;
		emotion 23,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "私は^4A4AFF" +'@word$+ "^000000ですから！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……えーっと……だから……";
		mes "その……";
		next;
		emotion 5;
		mes "[イシル]";
		mes "……そう……だったんですか……";
		mes "あなたは^4A4AFF" +'@word$+ "^000000……";
		mes "何をお願いしてもいいんですね……";
		mes "ゴ……ゴホ……ゴホ！　ゴホ！";
		next;
		emotion 4,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "（……あれー……）";
		mes "（何か変な方向に話が進んでるー……）";
		mes " ";
		mes "は……ははは。そう！　そうなの！";
		mes "何でも言っていいんだよ！";
		mes "（もうどうにでもなれー！）";
		next;
		mes "[イシル]";
		mes "ああ……本当に……ゴホ……";
		mes "^3131FF" +'@word$+ "^000000なんですね。";
		mes "では、お願いです。僕の代わりに";
		mes "クリスマスツリーの飾りつけ……ゴホ。";
		mes "お願いします……";
		break;
	case 10:
		if(countitem(7219) < 3 || countitem(538) < 1) {
			mes "[イシル]";
			mes "お願いです……僕の変わりに";
			mes "クリスマスツリーの飾りつけ……ゴホ。";
			mes "お願いします……";
			break;
		}
		mes "[イシル]";
		mes "ゴホ！　ゴホ、ゴホ！";
		mes "僕が頼んだ物はどうですか……？";
		mes "縞模様の靴下 3個と、";
		mes "よく焼いたクッキー 1個……ゴホ！";
		mes "そして、人形はどんなのですか？";
		next;
		switch(select("ポリン人形","チョンチョン人形","ぬいぐるみ","吊り下げられた人形","スポア人形","タヌキ人形",
					"サル人形","バッタ人形","黒猫の人形","ムナック人形","オシリス人形","バフォメット人形")) {
			case 1:	set '@itemid,741; break;
			case 2:	set '@itemid,742; break;
			case 3:	set '@itemid,740; break;
			case 4:	set '@itemid,7212; break;
			case 5:	set '@itemid,743; break;
			case 6:	set '@itemid,754; break;
			case 7:	set '@itemid,753; break;
			case 8:	set '@itemid,752; break;
			case 9:	set '@itemid,7206; break;
			case 10: set '@itemid,7277; break;
			case 11: set '@itemid,751; break;
			case 12: set '@itemid,750; break;
		}
		if(countitem('@itemid) < 1) {
			emotion 1;
			mes "[イシル]";
			mes "……え？";
			mes "どこですか……ゴホ、ゴホ！";
			mes "すみません……";
			mes "よく見えないのですが……";
			close;
		}
		mes "[イシル]";
		switch(@menu) {
		case 1:
			mes "あ……可愛いポリン人形ですね。";
			mes "ゴホ！　ゴホ！";
			break;
		case 2:
			mes "あ……チョンチョン人形ですね。";
			mes "ゴホ！　ゴホ！";
			mes "きっと……ゴホ！";
			break;
		case 3:
			mes "あ……綺麗なぬいぐるみですね。";
			mes "ゴホ！　ゴホ！";
			mes "とても可愛いし……ゴホ！";
			break;
		case 4:
			mes "ぇ……吊り下げられた人形？";
			mes "ゴホ！　ゴホ！";
			mes "……いえ、きっと……ゴホ！";
			break;
		case 5:
			mes "これは……スポア人形ですね。";
			mes "ゴホ！　ゴホ！";
			mes "とても可愛……ゴホ！";
			break;
		case 6:
			mes "あ……それはタヌキ人形……";
			mes "ゴホ！　ゴホ！";
			mes "初めて見ました……ゴホ！";
			break;
		case 7:
			mes "あ……サル人形ですか？";
			mes "ゴホ！　ゴホ！";
			mes "よく手に入りましたね……ゴホ！";
			break;
		case 8:
			mes "あ……バッタ人形ですか？";
			mes "ゴホ！　ゴホ！";
			mes "こんなのもあるんですね……ゴホ！";
			break;
		case 9:
			mes "あ……黒猫の人形ですか！";
			mes "ゴホ！　ゴホ！";
			mes "ぼ、僕が欲しいぐらい……ゴホ！";
			break;
		case 10:
			mes "あ……ムナック人形ですか。";
			mes "ゴホ！　ゴホ！";
			mes "とても可愛いですね……ゴホ！";
			break;
		default: //オシリス・バフォメット人形
			mes "そ……それは" +getitemname('@itemid)+ "!?";
			mes "ゴホ！　ゴホ！";
			mes "本当にあったんだ……ゴホ！";
			break;
		}
		mes "妹も" +(@menu==9? "絶対": "")+ "喜んでくれると思います。";
		mes "本当に……ありがとうございます……";
		next;
		mes "-イシルに見えるように、";
		mes "クッキーと縞模様の靴下、";
		mes "そして人形をもみの木に飾りつけた-";
		mes "-そちょっとバランスは悪いが";
		mes "イシルはすごく嬉しそうだ-";
		next;
		mes "[イシル]";
		mes "ゴホ……ゴホ！";
		mes "本当にありがとうございます。";
		mes "何もできない兄だけど、";
		mes "あなたのおかげで……ゴホ！";
		mes "妹は喜んでくれます……";
		next;
		mes "[イシル]";
		mes "よかったら……";
		mes "以前のバイトでもらったのを";
		mes "もらってください……ゴホ！";
		mes "僕なりの……感謝の気持ちです……";
		set XMAS_4EVE,11;
		delitem 7219,3;
		delitem 538,1;
		delitem '@itemid,1;
		switch(@menu) {
		case 1: //ポリン人形
		case 2: //チョンチョン人形
		case 3: //ぬいぐるみ
		case 4: //吊り下げられた人形
			getitem 12200,3;
			getitem 12130,1;
			break;
		case 5: //スポア人形
		case 6: //タヌキ人形
		case 7: //サル人形
		case 8: //バッタ人形
			getitem 12200,5;
			getitem 12130,1;
			getitem 522,1;
			break;
		case 9: //黒猫の人形
		case 10: //ムナック人形
			getitem 12200,5;
			getitem 12130,3;
			getitem 548,3;
			break;
		case 11: //オシリス人形
		case 12: //バフォメット人形
			getitem 12200,7;
			getitem 12130,5;
			getitem 607,1;
			break;
		}
		close;
	case 11:
	case 12:
		mes "[イシル]";
		mes "……ゴホ！　ゴホゴホ！";
		mes "本当にありがとうございます……";
		mes "今はもう……ゴホ！";
		mes "楽しいクリスマスを迎えるのを";
		mes "祈るだけです……ゴホゴホ。";
		close;
	}
	//9,10の続き
	next;
	mes "[イシル]";
	mes "靴下と人形を……クシュン！";
	mes "つけてもらえたら……ゴホ！";
	mes "あと、クッキーがあれば……";
	mes "ゴホゴホ！　ゴホ……";
	next;
	mes "[イシル]";
	mes "^0000FF縞模様の靴下 3個と、";
	mes "よく焼いたクッキー 1個^000000……ゴホ。";
	mes "そして、^0000FF何でもいいので人形を一つ。^000000";
	mes "どうか……ゴホ、お願いします……";
	next;
	mes "-イシルはクシャミとセキに";
	mes "攻められながらも、";
	mes "懸命に自分の願いを言った-";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "それ位ならお安い御用！";
	mes "後は私に任せて、ゆっくり休んでて！";
	mes " ";
	mes "（キャンプファイアはやだ！";
	mes "キャンプファイアの馬鹿！）";
	if(XMAS_4EVE == 9)
		set XMAS_4EVE,10;
	close;
}

xmas.gat,138,140,0	script	レッドニア	873,{
	switch(XMAS_4EVE) {
	case 0:
	case 1:
	case 2:
		emotion 6;
		mes "[レッドニア]";
		mes "くそ、まだ来ねぇのか！";
		mes "これじゃ、クリスマスケーキが";
		mes "ただのケーキになっちまうじゃねぇか！";
		mes "^4A4AFFイシル^000000は何やってんだ！";
		if(XMAS_4EVE != 2)
			close;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "イシルの代わりで来ました！";
		mes "何をすればいいんですか！";
		next;
		mes "[レッドニア]";
		mes "……何だお前？";
		mes "仕事はイシルが……";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "イシルは今、風邪をひいてしまって";
		mes "動く事もできないんです！";
		mes "私にすべてを任せ、休んでます。";
		mes "だからはやく私に仕事を！";
		next;
		mes "[レッドニア]";
		mes "……お前、目が燃えているな！";
		mes "よし、気に入った！";
		mes "お前にクリスマスのケーキを";
		mes "配達してもらおう！";
		next;
		mes "[レッドニア]";
		mes "さぁ、はやく行けぇ！";
		mes "楽しいクリスマスの運命が";
		mes "お前の手にかかっていると、";
		mes "肝に銘じておけッ！";
		set XMAS_4EVE,3;
		close;
	case 3:
		mes "[レッドニア]";
		mes "何をぐずぐずしている！";
		mes "早くケーキを配達してこい！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "あの、配達先は？";
		next;
		mes "[レッドニア]";
		mes "あん？　聞いてないのか？";
		mes "しょうがねぇなぁ。";
		mes "^0000FF一度だけ教えてやるから";
		mes "よーく聞くんだぞ!!!!^000000";
		next;
		mes "[レッドニア]";
		mes "ケーキの名前をちゃんと覚えろよ！";
		mes "まず、^0000FF「ジャストシーズン」^000000は";
		mes "^FF0000「パレス」^000000さん宅に！";
		next;
		mes "[レッドニア]";
		mes "^0000FF「マザーガーデン」^000000は";
		mes "^FF0000「ナビダ」^000000さん宅に！";
		next;
		mes "[レッドニア]";
		mes "^0000FF「マイレディーサンタクロース」^000000は";
		mes "^FF0000「ジョイユ」^000000さん宅に！";
		next;
		mes "[レッドニア]";
		mes "^0000FF「ジングルベルハッピー」^000000は";
		mes "^FF0000「ノエル」^000000さん宅に！";
		next;
		mes "[レッドニア]";
		mes "今言った順に届けるんだ。";
		mes "さぁ、わかったらさっさと行けぇ！";
		set XMAS_4EVE,4;
		close;
	default:
		mes "[レッドニア]";
		mes "さぁ、はやく行けぇ！";
		mes "楽しいクリスマスの運命が";
		mes "お前の手にかかっていると、";
		mes "肝に銘じておけッ！";
		close;
	case 8:
		mes "[レッドニア]";
		mes "おう、戻ってきたか。";
		mes "無事に届いたって連絡は来ているよ。";
		mes "お客さんもみんな満足しているようだ。";
		mes "本当にご苦労さん。";
		next;
		mes "[レッドニア]";
		mes "よし！";
		mes "これはイシルと約束したバイト代だ！";
		mes "小さいけれど、それなりの木だ。";
		mes "さっさと風邪なんて治して、";
		mes "働けるようになれって言っといてくれ。";
		next;
	case 9:
		mes "[レッドニア]";
		mes "ちゃんとイシルに渡すんだぞ。";
		mes "ま、今夜はお前が";
		mes "サンタクロースってとこだな。";
		mes "ハッハッハッハッハ。";
		next;
		emotion 18;
		mes "[レッドニア]";
		mes "メリークリスマス！";
		mes "お前も祝福のクリスマスを楽しめよ！";
		if(XMAS_4EVE == 8) {
			next;
			mes "^0000FF-レッドニアから";
			mes "小さなもみの木を受け取った！-";
			set XMAS_4EVE,9;
		}
		close;
	case 10:
	case 11:
	case 12:
		mes "[レッドニア]";
		mes "くそ！　誰が赤鼻だ！";
		mes "俺はソリなんぞに興味はない！";
		close;
	}
}

xmas.gat,168,160,4	script	パレス	46,{
	if(XMAS_4EVE < 4) {
		mes "[パレス]";
		mes "あぁもぅ！";
		mes "クリスマスケーキはまだか！";
		mes "まさか、ケーキの無い";
		mes "地獄のようなクリスマスを";
		mes "迎える事になるんじゃないだろうな！";
		next;
		mes "[パレス]";
		mes "^4A4AFFレッドニア^000000さんは何をしているんだ！";
		close;
	}
	if(XMAS_4EVE >= 5) {
		emotion 18;
		mes "[パレス]";
		mes "本当にありがとう。";
		mes "これで楽しいクリスマスを";
		mes "すごす準備は終わったよ。";
		mes "君も幸せなクリスマスを";
		mes "すごせるようにね。";
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "遅れて申し訳ありません！";
	mes "クリスマスケーキの配達です！";
	next;
	mes "[パレス]";
	mes "おぉ！　やっと来たか！";
	mes "今年はケーキ無しで";
	mes "クリスマスをすごすのかと";
	mes "心配してた所だよ。";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "本当にすみません。";
	mes "えっと……「パレス」さん宅には";
	mes "このケーキですね……";
	next;
	input '@word$;
	mes "[" +strcharinfo(0)+ "]";
	mes "「パレス」さん宅宛てに";
	mes "注文されたケーキは、この";
	if('@word$ != "ジャストシーズン") {
		mes '@word$+ "ですか？";
		next;
		mes "[パレス]";
		mes "……いや？";
		mes "私の注文したケーキとは";
		mes "違うんだが……";
		close;
	}
	mes "^0000FF「ジャストシーズン」^000000ですか？";
	next;
	emotion 18;
	mes "[パレス]";
	mes "そう、それ！";
	mes "本当においしそうだ！";
	mes "ありがとう、そしてご苦労様。";
	set XMAS_4EVE,5;
	close;
}

xmas.gat,113,273,4	script	ナビダ	711,{
	if(XMAS_4EVE < 5) {
		mes "[ナビダ]";
		mes "ああ……";
		mes "クリスマスケーキはまだかしら？";
		next;
		mes "[ナビダ]";
		mes "^4A4AFFレッドニア^000000さんは";
		mes "何をしているのかしら？";
		close;
	}
	if(XMAS_4EVE >= 6) {
		emotion 18;
		mes "[ナビダ]";
		mes "今年も、暖かくて幸せな";
		mes "クリスマスになりそうだわ。";
		mes "あなたも幸せなクリスマスを。";
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "遅れて申し訳ありません！";
	mes "クリスマスケーキの配達です！";
	next;
	mes "[ナビダ]";
	mes "やっと来たわね。";
	mes "あんまり遅いから、";
	mes "事故にでもあったのかと心配したわ。";
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "本当にすみません。";
	mes "えっと……「ナビダ」さん宅には";
	mes "このケーキですね……";
	next;
	input '@word$;
	mes "[" +strcharinfo(0)+ "]";
	mes "「ナビダ」さん宅宛てに";
	mes "注文されたケーキは、この";
	if('@word$ != "マザーガーデン") {
		mes '@word$+ "ですか？";
		next;
		mes "[ナビダ]";
		mes "……あら？";
		mes "私の注文したケーキじゃないみたいよ？";
		close;
	}
	mes "^0000FF「マザーガーデン」^000000ですか？";
	next;
	emotion 18;
	mes "[ナビダ]";
	mes "あらあら、とってもおいしそう。";
	mes "本当にご苦労様でした。";
	set XMAS_4EVE,6;
	close;
}

xmas.gat,119,155,5	script	ジョイユ	878,{
	if(Sex == 0) {
		if(XMAS_4EVE < 6) {
			mes "[ジョイユ]";
			mes "こんなに寒い日に、";
			mes "どこへ行こうというのですか？";
			mes "よろしければ、この家屋で暖まり、";
			mes "チョコレートでもご一緒しませんか？";
			next;
			emotion 30;
			mes "[ジョイユ]";
			mes "^4A4AFFレッドニア^000000の怠慢で、";
			mes "まだクリスマスケーキが";
			mes "用意できていませんが、";
			mes "レディーの甘い瞳で私の心を";
			mes "満たしてくれるなら、";
			mes "ケーキなんて必要無いでしょう。";
			close;
		}
		if(XMAS_4EVE >= 7) {
			emotion 30;
			mes "[ジョイユ]";
			mes "ようこそ！";
			mes "ようこそいらっしゃいました、";
			mes "マイスイートハニー。";
			mes "パーティーの準備はできていませんが、";
			mes "あなたがいるだけで十分です！";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "遅れて申し訳ありません！";
		mes "クリスマスケーキの配達です！";
		next;
		mes "[ジョイユ]";
		mes "ああ……こんなに美しい方が";
		mes "どうしてこんな事を……";
		mes "あなたの手が冷たい風にさらされ、";
		mes "すっかり冷たくなっているでは";
		mes "ありませんか！";
		next;
		mes "-彼はあなたの手を取り、";
		mes "熱心な息づかいで暖めようとした-";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "うわ……あ、いえ……";
		mes "アハハ……大丈夫ですから……";
		mes "配達が遅れて本当にすみません。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "えっと……「ジョイユ」さん宅には";
		mes "このケーキですね……";
		next;
		input '@word$;
		mes "[" +strcharinfo(0)+ "]";
		mes "「ジョイユ」さん宅宛てに";
		mes "注文されたケーキは、この";
		if('@word$ != "マイレディーサンタクロース") {
			mes '@word$+ "ですか？";
			next;
			mes "[ジョイユ]";
			mes "あぁ～";
			mes "あなたが届けてくださったケーキなら";
			mes "たとえ土で出来ていたとしても";
			mes "残らず全部食べてしまいます。";
			next;
			emotion 19,"";
			mes "[" +strcharinfo(0)+ "]";
			mes "……これじゃないみたいだ……";
			close;
		}
		mes "^0000FF「マイレディーサンタクロース」^000000";
		mes "ですか？";
		next;
		mes "[ジョイユ]";
		mes "あぁ！";
		mes "レディーが持って来てくださった";
		mes "このケーキ！";
		mes "本当においしそうです。";
		mes "どうです？　ご一緒にパーティなど？";
		next;
		emotion 19,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "いや……アハハハハ……";
		mes "有難いお話ですが、";
		mes "まだ配達が残っているので……";
		next;
		mes "[ジョイユ]";
		mes "レ、レディー！";
		mes strcharinfo(0)+ "!!";
		mes "いつでも、寂しくなったら";
		mes "この私に会いにきてください！";
		next;
		emotion 30;
		mes "[ジョイユ]";
		mes "私はいつでも！";
		mes "あなたを暖かく迎え入れましょう。";
		mes "この美しいケーキのように";
		mes "甘い、愛の言葉を囁きながら！";
		set XMAS_4EVE,7;
		close;
	}
	else {
		if(XMAS_4EVE < 6) {
			mes "[ジョイユ]";
			mes "何を見ている？";
			mes "道にでも迷ったのか？";
			next;
			mes "[ジョイユ]";
			mes "それにしても、^4A4AFFレッドニア^000000は";
			mes "何をしているんだ？";
			mes "私の可愛いレディーたちが";
			mes "ケーキを待ちくたびれている";
			mes "ではないか……";
			close;
		}
		if(XMAS_4EVE >= 7) {
			emotion 32;
			mes "[ジョイユ]";
			mes "何を突っ立っているんだ？";
			mes "配達が終わったんなら";
			mes "さっさとどっか行け。";
			mes "いくら君の視線にさらされようが、";
			mes "私はレディー以外に興味は無い！";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "遅れて申し訳ありません！";
		mes "クリスマスケーキの配達です！";
		next;
		mes "[ジョイユ]";
		mes "フン！";
		mes "そんなにトロくて配達が勤まるか！";
		mes "来年の夏頃にケーキが来るかと";
		mes "期待してたところだったぞ！";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ハハ……本当にすみません。";
		mes "えっと……「ジョイユ」さん宅には";
		mes "このケーキですね……";
		next;
		input '@word$;
		mes "[" +strcharinfo(0)+ "]";
		mes "「ジョイユ」さん宅宛てに";
		mes "注文されたケーキは、この";
		if('@word$ != "マイレディーサンタクロース") {
			mes '@word$+ "ですか？";
			next;
			mes "[ジョイユ]";
			mes "ハ！　注文まで間違うとはな！";
			mes "どこか頭でもやられたんじゃないのか？";
			mes "医者にでも見てもらったらどうだ！";
			close;
		}
		mes "^0000FF「マイレディーサンタクロース」^000000";
		mes "ですか？";
		next;
		mes "[ジョイユ]";
		mes "注文はちゃんと聞いていたようだな。";
		mes "よし、そのままそこに置いて行け。";
		set XMAS_4EVE,7;
		close;
	}
}

xmas.gat,157,126,5	script	ノエル	717,{
	if(Sex == 1) {
		if(XMAS_4EVE < 7) {
			mes "[ノエル]";
			mes "キャハハ♪";
			mes "メリークリスマ～ス。";
			mes "素敵なお・兄・さ・ん♪";
			next;
			emotion 30;
			mes "[ノエル]";
			mes "^4A4AFFレッドニア^000000さんに会ったら";
			mes "クリスマスケーキを早くって";
			mes "伝えてくれない？";
			mes "もー、おっそいの！";
			close;
		}
		if(XMAS_4EVE >= 8) {
			mes "[ノエル]";
			mes "まだ行ってなかったの？";
			mes "さっきはごめんね～";
			mes "私の恋人って嫉妬しやすいから。";
			mes "キャハ♪";
			next;
			mes "[??????]";
			mes "おい、ノエル！";
			mes "また外に出て、何やってるんだ！";
			next;
			emotion 18;
			mes "[ノエル]";
			mes "何でもないよ～";
			mes "すぐ戻るって～";
			next;
			emotion 9,"";
			mes "-彼女は声のした方に向かって、";
			mes "にっこりと微笑みかけた-";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "遅れて申し訳ありません！";
		mes "クリスマスケーキの配達です！";
		next;
		mes "[ノエル]";
		mes "素敵なお・に・い・さ・ん♪";
		mes "もう少し遅かったら";
		mes "オシオキする所だったよ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "ハハ……本当にすみません。";
		mes "えっと……「ノエル」さん宅には";
		mes "このケーキですね……";
		next;
		input '@word$;
		mes "[" +strcharinfo(0)+ "]";
		mes "「ノエル」さん宅宛てに";
		mes "注文されたケーキは、この";
		if('@word$ != "ジングルベルハッピー") {
			mes '@word$+ "ですか？";
			next;
			mes "[ノエル]";
			mes "キャハ♪";
			mes "それは注文したケーキじゃないよ。";
			mes "素敵なお兄さんでも間違いはするんだ？";
			close;
		}
		mes "^0000FF「ジングルベルハッピー」^000000ですか？";
		next;
		mes "[ノエル]";
		mes "キャハ♪";
		mes "こんな素敵なお兄さんが";
		mes "届けてくれたクリスマスケーキ。";
		mes "今年のクリスマスもすごく";
		mes "あ・ま・そ・う♪";
		next;
		mes "[??????]";
		mes "おい、ノエル！";
		mes "その男は誰だ！";
		next;
		mes "[ノエル]";
		mes "キャ、何でもないわよ。";
		mes "クリスマスケーキを届けてくれた人。";
		next;
		emotion 9,"";
		mes "-彼女は声のした方に向かって、";
		mes "にっこりと微笑みかけた-";
		set XMAS_4EVE,8;
		close;
	}
	else {
		if(XMAS_4EVE < 7) {
			mes "[ノエル]";
			mes "ああ、寒……";
			mes "^4A4AFFレッドニア^000000さんはいつになったら";
			mes "クリスマスケーキを届けてくるの！";
			mes "もー……ん？";
			next;
			emotion 18;
			mes "[ノエル]";
			mes "キャハッ♪";
			mes "こんな日に一人？";
			mes "あなた本当に可哀想ね。";
			mes "恋人でもできるように";
			mes "お祈りしてあげましょうか？";
			mes "キャハハハハ。";
			close;
		}
		if(XMAS_4EVE >= 8) {
			emotion 18;
			emotion 9,"";
			mes "[ノエル]";
			mes "キャハッ♪　まだ行ってないの？";
			mes "ぼーっとしてたら、";
			mes "もっとお腹が膨らんじゃうよ？";
			mes "キャハハハハハハ。";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "遅れて申し訳ありません！";
		mes "クリスマスケーキの配達です！";
		next;
		emotion 18;
		emotion 6,"";
		mes "[ノエル]";
		mes "キャハッ♪";
		mes "お姉さんはもうちょっとがんばって";
		mes "走り回らなくちゃいけないよね。";
		mes "お腹のお肉のためにね～";
		mes "キャハハハハハハ。";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "……本当にすみません。";
		mes "えっと……「ノエル」さん宅には";
		mes "このケーキですね……";
		next;
		input '@word$;
		mes "[" +strcharinfo(0)+ "]";
		mes "「ノエル」さん宅宛てに";
		mes "注文されたケーキは、この";
		if('@word$ != "ジングルベルハッピー") {
			mes '@word$+ "ですか？";
			next;
			mes "[ノエル]";
			mes "キャハハハハ。";
			mes "栄養が全部お腹にいって、";
			mes "頭は空っぽなの？";
			mes "そんなケーキ、";
			mes "私は注文してないよ～";
			next;
			emotion 6,"";
			mes "[" +strcharinfo(0)+ "]";
			mes "………………………………";
			close;
		}
		mes "^0000FF「ジングルベルハッピー」^000000ですか？";
		next;
		mes "[ノエル]";
		mes "配達でも、がんばってあちこちに";
		mes "走り回れば贅肉もなんとかなるかもね？";
		mes "キャハ♪　がんばってね。";
		mes "ぁ、ケーキはそこに置いといてね～";
		next;
		emotion 6,"";
		mes "[" +strcharinfo(0)+ "]";
		mes "ハ……ハハハ……";
		set XMAS_4EVE,8;
		close;
	}
}

//==============================================================
// ルイーゼのサンタ帽
//==============================================================
xmas_in.gat,89,92,4	script	ルイーゼ	714,{
	mes "[アーティスト・ルイーゼ]";
	mes "ねぇねぇ。";
	mes "あの赤い布製の三角帽";
	mes "「サンタのぼうし」のデザインって";
	mes "ちょっとダサイと思わない？";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "そこで！　アーティストである";
	mes "このルイーゼが、一肌脱いで、";
	mes "あの帽子を美しく素敵に、";
	mes "立派にしてあげましょう～！";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "あ、ちょっと話は変わるけど、";
	mes "あの悪名高いアンソニが";
	mes "被っている帽子……実は";
	mes "この私が作ってあげたものなのよ。";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "アンソニを捕まえづらいのは、";
	mes "彼の帽子に特殊な力があるせいなの。";
	mes "ウフフ……私が帽子に";
	mes "ちょっとした力を与えたからね。";
	next;
	emotion 3;
	mes "[アーティスト・ルイーゼ]";
	mes "さて、ただの布っきれに過ぎない";
	mes "普通の「サンタのぼうし」があったら、";
	mes "私のとこに持って来てくれない？";
	mes "そしたら、私自ら";
	mes "新しい帽子を作ってあげるわよ。";
	next;
	if(countitem(2236)<1) {
		mes "[アーティスト・ルイーゼ]";
		mes "後で「サンタのぼうし」を見れば、";
		mes "私の言っていることが分かるわよ。";
		mes "ホ～ント平凡だから、";
		mes "すっごく物足りなく感じるはず！";
		next;
		emotion 18;
		mes "[アーティスト・ルイーゼ]";
		mes "この私が天才的デザインセンスを";
		mes "発揮して、あの帽子を";
		mes "素晴らしいものにしてあげる。";
		mes "遠慮なく持ってきてね！";
		close;
	}
	if(select("これのことですか？","遠慮します")==2) {
		emotion 18;
		mes "[アーティスト・ルイーゼ]";
		mes "そう～？";
		mes "む～、仕方ないわね。";
		mes "ぜ～ったい損にはならないのに。";
		mes "……またよかったら、来てね！";
		close;
	}
	mes "[アーティスト・ルイーゼ]";
	mes "おお！　そう、これよこれ。";
	mes "うん、フムフム。そうね～。";
	mes "あれをこうして、あそこをああして、";
	mes "ここをああすれば、うん、いけるわね。";
	mes "あ、この帽子を素敵にするために、";
	mes "ちょっと必要な物があるんだけど……。";
	next;
	if(select("何が必要ですか？","大変そうなので、けっこうです")==2) {
		emotion 18;
		mes "[アーティスト・ルイーゼ]";
		mes "ええ～っ！";
		mes "よ～く考えてみて！";
		mes "こんなチャンス滅多にないのよ。";
		mes "……またよかったら、来てよ！";
		close;
	}
	mes "[アーティスト・ルイーゼ]";
	mes "物分りがいいわね。その姿勢好きよ。";
	mes "じゃあ、材料だけど、基本はやっぱり";
	mes "「サンタのぼうし」そのもの。";
	mes "それを、この私の才能を少し使って";
	mes "素晴らしくアレンジしてあげるわ。";
	mes "だから、他の帽子は必要ないわよ。";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "じゃ、材料を言うわよ～。";
	mes "ベースとなる^0000FFサンタのぼうし^000000と";
	mes "帽子を編む為の^0000FFサボテンの針1個^000000。";
	mes "祝福を与える為の^0000FF聖水10個^000000。";
	mes "幸運を呼び込む為の^0000FFロザリー1個^000000。";
	mes "これだけあれば、十分！";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "これで立派に、私の名声にもふさわしい";
	mes "素晴らしい帽子を作ってあげるわ。";
	next;
	if(countitem(2236)<1 || countitem(952)<1 || countitem(523)<10 || countitem(2608)<1) {
		emotion 3;
		mes "[アーティスト・ルイーゼ]";
		mes "材料さえあれば、私自ら";
		mes "帽子をアレンジしてあげるよ！";
		mes "そうね～、特別に手数料はいらないわ！";
		mes "もし気が向いたら、連絡ちょうだい。";
		close;
	}
	menu "あ、それならここに……",-;
	emotion 21;
	mes "[アーティスト・ルイーゼ]";
	mes "わお！";
	mes "物分りだけがいいだけでなく";
	mes "行動力もあるのね！";
	mes "よし、それなら、すぐにできるわ。";
	mes "アーティストルイーゼの能力を";
	mes "目の前でとくと見せてあげましょう～！";
	next;
	mes "-彼女は、材料を全部受け取った-";
	mes "-そして歌を口ずさみながら、";
	mes "聖水を注いだ筒に帽子を浸してすぐに";
	mes "取り出し、糸を素早くほどいた-";
	next;
	misceffect 42;
	emotion 2;
	mes "[アーティスト・ルイーゼ]";
	mes "アーティストルイーゼの手にかかれば～";
	mes "世の中全ての祝福が与えられる～♪";
	next;
	mes "-彼女は、よく分からない溶液に";
	mes "ロザリーを入れて溶かした-";
	mes "-そして、筆をその溶液につけ、";
	mes "帽子を構成していた糸";
	mes "一本一本に、丁寧に塗った-";
	next;
	misceffect 75;
	emotion 2;
	mes "[アーティスト・ルイーゼ]";
	mes "アーティストルイーゼの手にかかれば～";
	mes "世の中全ての幸福が与えられる～♪";
	next;
	mes "-サボテンの針を使って、";
	mes "彼女はその糸の塊を素早く編み、";
	mes "帽子を作った-";
	next;
	misceffect 91;
	emotion 3;
	mes "[アーティスト・ルイーゼ]";
	mes "これはアーティストルイーゼの奇跡～";
	mes "大天才デザイナーの名は、そう！";
	mes "ア～ティスト、ルイ～ゼよ～♪";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "さあ、完成！";
	mes "どう？　素敵でしょ？";
	mes "思いっきり褒めてくれていいのよ。";
	mes "私の作品は素晴らしいでしょ～♪";
	mes "あのデザイナーピエールも";
	mes "泣いちゃう程いいものよ。";
	next;
	emotion 18;
	mes "[アーティスト・ルイーゼ]";
	mes "本当なら多少の手数料を";
	mes "請求するところだけど……";
	mes "クリスマス特別大サービス!!";
	mes "この帽子を他の人にも";
	mes "見せてあげるってことで";
	mes "タダにしましょう！";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "どこに行っても何をしてても";
	mes "絶対絶対絶対!!";
	mes "この帽子を脱がないでね！";
	next;
	mes "[アーティスト・ルイーゼ]";
	mes "これほど素晴らしい帽子は";
	mes "よそではいくらお金をかけても";
	mes "手に入れられないからね！";
	mes "失くしたら二度と手にすることが";
	mes "できない、す～っごく貴重な";
	mes "お宝だからね!!";
	next;
	emotion 2;
	mes "[アーティスト・ルイーゼ]";
	mes "それじゃ、早く帽子を他の人に";
	mes "自慢しにいってらっしゃい～。";
	mes "ああ～、アーティストルイーゼに～";
	mes "アレンジできないものなど、";
	mes "この世にない～♪";
	delitem 2236,1;
	delitem 952,1;
	delitem 523,10;
	delitem 2608,1;
	getitem 5136,1;
	close;
}
