//====================================================================
//Ragnarok Online - Rebellion Jobchange Script	by refis
//
//　■ CHANGE_RB -> 0～4
//====================================================================

moc_fild12.gat,261,318,3	script	怪しい男	998,{
	if(Job == Job_Rebellion) {
		mes "[怪しい男]";
		mes "お前は……！";
		mes "この間の賞金首";
		mes "　";
		mes "……の他人の空似！";
		next;
		mes "[怪しい男]";
		mes "いや、この間は";
		mes "間違えて申し訳なかった。";
		mes "あの後、情報も回ってきた。";
		mes "俺が動いていた時にはすでに";
		mes "本物は捕まっていたと。";
		next;
		mes "[怪しい男]";
		mes "どのみち、俺の夕飯代には";
		mes "ならなかったということだな。";
		next;
		mes "[怪しい男]";
		mes "それにしても……";
		mes "お前はリベリオンになったのか！";
		next;
		mes "[怪しい男]";
		mes "リベリオンになれたということは";
		mes "厳しい試験を越え、";
		mes "自由と反逆の意志を";
		mes "魂に宿したということ。";
		next;
		mes "[怪しい男]";
		mes "銃の道は";
		mes "明日の飯もままならぬ";
		mes "厳しいものだが";
		mes "共に頑張ろうじゃないか！";
		close;
	}
	if(Job == Job_Gunslinger && BaseLevel >= 99 && JobLevel >= 70) {
		if(CHANGE_RB) {
			mes "[怪しい男]";
			mes "あっお前は";
			mes "賞金首スパイク！";
			next;
			mes "[怪しい男]";
			mes "この前は逃がしたと思ったが";
			mes "また現れたな！　今度こそ逃がさん！";
			next;
			switch(select("またまた逃げる","迎え撃つ")) {
			case 1:
				mes "[怪しい男]";
				mes "こらー！";
				mes "逃げるな俺の賞金!!";
				mes "　";
				break;
			case 2:
				mes "‐あなたは銃を抜き、";
				mes "　男の手から武器を弾き飛ばした‐";
				soundeffect "ferus_move.wav", 0, 0;
				next;
				mes "[怪しい男]";
				mes "うわっ";
				mes "なんという命中力なんだ！";
				next;
			}
			mes "‐何度も相手にしていられない。";
			mes "　早くこの人違いをなんとかしよう‐";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "（手配書に書かれている";
			mes "^FF0000アインブロックの秘密酒場^000000に";
			mes "急ごう）";
			next;
			mes "‐アインブロックの秘密酒場に";
			mes "　向かいますか？‐";
			next;
			if(select("はい","いいえ") == 2) {
				mes "‐今はやめておこう‐";
				close;
			}
			mes "‐アインブロックへ向かった‐";
			close2;
			warp "einbroch.gat",48,97;
			end;
		}
		mes "[怪しい男]";
		mes "ついに見つけたぞ……！";
		mes "賞金首スパイク！";
		mes "その首にかかった";
		mes "懸賞金は俺のものだ！";
		next;
		mes "‐初対面の男に銃口を";
		mes "　突きつけられた！‐";
		next;
		switch(select("何事か聞く","怒る")) {
		case 1:
			mes "[怪しい男]";
			mes "とぼけても無駄だ！";
			mes "お前のその隠しきれない";
			mes "悪の匂い、まさにこの手配書にある";
			mes "賞金首と同じ！";
			break;
		case 2:
			mes "[怪しい男]";
			mes "むっ抵抗する気か！";
			mes "だが、手配書はすでに各地に";
			mes "広がっている。";
			mes "どこにも逃げ場はないぞ！";
			break;
		}
		next;
		mes "[怪しい男]";
		mes "観念して、";
		mes "俺の手柄になってもらうぞ!!";
		next;
		switch(select("逃げる","迎え撃つ")) {
		case 1:
			mes "[怪しい男]";
			mes "わああ！　こっち来るな！";
			mes "　";
			mes "‐あなたは立ちふさがる";
			mes "　怪しい男に体当たりして";
			mes "　逃げ出した‐";
			soundeffect "ghoul_die2.wav", 0, 0;
			next;
			mes "‐その時に男が持っていた";
			mes "　紙が飛ばされて、";
			mes "　あなたの視界をふさいだ‐";
			next;
			menu "うわっ！",-;
			mes "‐引きはがした手配書には";
			mes "　あなたに似た人相書き、";
			mes "　そして^FF0000発行：アインブロックの秘密酒場^000000と";
			mes "　書かれている‐";
			break;
		case 2:
			mes "‐あなたは銃を抜き、";
			mes "　男の手から武器を弾き飛ばした‐";
			soundeffect "ferus_move.wav", 0, 0;
			next;
			mes "[怪しい男]";
			mes "なんだと……!?";
			mes "　";
			mes "‐腕をおさえ、男が驚愕の表情で";
			mes "　あなたを見る‐";
			next;
			mes "[怪しい男]";
			mes "さすがの賞金首というわけか";
			mes "……くっ";
			next;
			switch(select("手配書を確保する","賞金首ではありません")) {
			case 1:
				mes "[怪しい男]";
				mes "あっ！　こら！";
				mes "返せ!!";
				mes "　";
				mes "‐あなたは男から";
				mes "　手配書を取り上げた‐";
				break;
			case 2:
				mes "[怪しい男]";
				mes "ハッ！　今までの賞金首も";
				mes "そんな風にしらばっくれたさ。";
				mes "だがな！";
				next;
				mes "[怪しい男]";
				mes "この手配書は";
				mes "^0000ffアインブロックの秘密酒場^000000で";
				mes "発行された正規のものだ！";
				mes "そうそう不備が出るはずがない！";
				break;
			}
			next;
			mes "‐手配書にはあなたに似た人相書き、";
			mes "　そして^FF0000発行：アインブロックの秘密酒場^000000と";
			mes "　書かれていた‐";
			next;
			mes "[" +strcharinfo(0)+ "]";
			mes "（アインブロック……）";
			break;
		}
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（手配書に書かれている";
		mes "^FF0000アインブロックの秘密酒場^000000に";
		mes "行ってみよう）";
		next;
		setquest 12340;
		set CHANGE_RB,1;
		mes "‐アインブロックの秘密酒場に";
		mes "　向かいますか？‐";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐アインブロックへ向かった‐";
		close2;
		warp "einbroch.gat",48,97;
		end;
	}
	mes "‐怪しい男が";
	mes "　紙を何枚も広げている‐";
	next;
	mes "[怪しい男]";
	mes "ふっふっふ……";
	mes "持てるだけ手配書をもらってきたぞ。";
	//mes "賞品首を捕まえて";
	mes "賞金首を捕まえて";
	mes "荒稼ぎしてやるぜ。";
	close;
}
einbroch.gat,54,97,3	script	ガード	10062,{
	if(CHANGE_RB == 1) {
		mes "‐手配書に書かれていた";
		mes "　^FF0000秘密酒場^000000は";
		mes "　この建物のようだ‐";
		next;
		mes "[ガード]";
		mes "おい、そこのガンスリンガー。";
		mes "いつまで突っ立って……";
		mes "　";
		mes "お前は賞金首スパイク！";
		next;
		menu "違います",-,"人違いです",-;
		mes "[ガード]";
		mes "は？";
		mes "　";
		mes "いや、そうだ。";
		mes "確かに捕まったと聞いたぞ。";
		mes "だが念のためということもあるし……";
		next;
		menu "自分は賞金首ではありません",-,"間違われて迷惑してます",-;
		mes "[ガード]";
		mes "なんだと？";
		mes "　";
		mes "‐ガードはあなたの顔を";
		mes "　いろんな方向からジロジロと";
		mes "　見つめた‐";
		next;
		mes "[ガード]";
		mes "ふうん……";
		mes "確かに、似ているが違うな。";
		next;
		mes "[ガード]";
		mes "それで、手配書に関して";
		mes "話があると、そういうことだな？";
		next;
		mes "[ガード]";
		mes "そうだな、";
		mes "私で判断できる問題じゃなさそうだし、";
		mes "お前なら、この店に";
		mes "入っても問題ないだろう。";
		next;
		mes "[ガード]";
		mes "手配書の件は";
		mes "店内にいる^0000FFクルベル^000000に";
		mes "持って行きな。";
		close2;
		warp "job_gun.gat",62,27;
		end;
	}
	else if(CHANGE_RB >= 2) {
		mes "[ガード]";
		mes "うん？　この前の奴か。";
		mes "酒場になんの用だ？";
		next;
		if(select("中に入りたい","寄ってみただけ") == 2) {
			mes "[ガード]";
			mes "用がないなら帰れ。";
			close;
		}
		mes "[ガード]";
		mes "そうか。中で問題を起こすなよ。";
		close2;
		warp "job_gun.gat",62,27;
		end;
	}
	else if(Job == Job_Rebellion) {
		mes "[ガード]";
		mes "よお、同志。";
		mes "調子はどうだ？";
		next;
		if(select("酒場に入りたい","寄ってみただけ") == 2) {
			mes "[ガード]";
			mes "そうか。";
			mes "元気そうで何よりだ。";
			mes "その調子で銃の道を";
			mes "極めろよ。";
			close;
		}
		mes "[ガード]";
		mes "そうか。中で問題を起こすなよ。";
		close2;
		warp "job_gun.gat",62,27;
		end;
	}
	else {
		// 未調査
	}
}

job_gun.gat,56,26,0	warp	リベリオン室内#1	2,2,einbroch.gat,49,97
job_gun.gat,18,10,0	warp	リベリオン室内#2	2,2,job_gun.gat,81,29
job_gun.gat,165,22,0	warp	リベリオン室内#3	2,2,job_gun.gat,197,44
job_gun.gat,197,49,0	warp	リベリオン室内#4	2,2,job_gun.gat,157,21

job_gun.gat,68,33,3	script	冷静なリベリオン	10063,{
	if(Job == Job_Rebellion) {
		if(checkquest(121920)&0x8) {
			mes "[冷静なリベリオン]";
			mes "やあ、同志よ。";
			mes "銃の扱いには常に気を配るんだぞ。";
			mes "その銃が我々の象徴だからな。";
			close;
		}
		setquest 121920;
		compquest 121920;
		mes "[冷静なリベリオン]";
		mes "やあ、新入り。";
		mes "銃の扱いには常に気を配るんだぞ。";
		mes "その銃が我々の象徴だからな。";
		close;
	}
	mes "[冷静なリベリオン]";
	mes "銃の扱い方はわかってるのか？";
	close;
}

job_gun.gat,78,33,6	script	怪しいガンマン	731,{
	if(Job == Job_Rebellion) {
		if(checkquest(121915)&0x8) {
			mes "[怪しいガンマン]";
			mes "よお、同志よ。";
			mes "自由を守るために";
			mes "銃の道を究めているか？";
			mes "銃だけになハハッ！";
			close;
		}
		setquest 121915;
		compquest 121915;
		mes "[怪しいガンマン]";
		mes "よお、同志よ。";
		mes "先輩として後輩のお前に言えるのは";
		mes "これだけだ。";
		next;
		mes "[怪しいガンマン]";
		mes "その手の銃は";
		mes "お前の自由の象徴だ。";
		mes "その自由を守るためにリベリオンは";
		mes "道を究めるのさ。";
		mes "銃だけになハハッ！";
		close;
	}
	mes "[怪しいガンマン]";
	mes "……";
	next;
	mes "[怪しいガンマン]";
	mes "は？";
	mes "俺は鍛冶なんてやってないんだが。";
	mes "俺はガンマン。";
	mes "自由に生きるガンマンだぞ。";
	close;
}

job_gun.gat,74,24,6	script	酔っ払いの男	887,{
	if(Job == Job_Rebellion) {
		if(checkquest(121905)&0x8) {
			mes "[酔っ払いの男]";
			mes "ぐおおおおおおお……";
			mes "　";
			mes "‐男は大きないびきをかいて";
			mes "　寝入っている‐";
			close;
		}
		setquest 121905;
		compquest 121905;
		mes "[酔っ払いの男]";
		mes "ここはリベリオンが集い、";
		mes "情報を交換する秘密の酒場だ。";
		mes "新米ならクルベルに";
		mes "挨拶していきな。";
		next;
		mes "[酔っ払いの男]";
		mes "私の仕事は酒の仕入れだからな。";
		close;
	}
	mes "[酔っ払いの男]";
	mes "私はこの酒場の店長だ！";
	mes "　";
	mes "……うん？";
	next;
	mes "[酔っ払いの男]";
	mes "ここが私の店？";
	mes "そもそも私は店長なのか……？";
	mes "　";
	mes "‐男はひどく酔っている‐";
	close;
}

job_gun.gat,64,33,6	script	不安な男	748,{
	if(Job == Job_Rebellion) {
		if(checkquest(121920)&0x8) {
			mes "[不安な男]";
			mes "彼らの象徴は自由らしいですけど、";
			mes "それなら私も自由にしてくださいよ。";
			next;
			mes "[冷静なリベリオン]";
			mes "何言ってんだい、あんた。";
			mes "あんたは、街へ出ては迷って";
			mes "ここにたどり着いてを";
			mes "繰り返してる";
			mes "ただの方向音痴じゃないか。";
			next;
			mes "[不安な男]";
			mes "……ううう、ここが";
			mes "入り組んでいるのが";
			mes "悪いんですよ。";
			close;
		}
		mes "[不安な男]";
		mes "あなたもこの変な場所の";
		mes "一員なんですか？";
		mes "どうすれば出られるんでしょうか。";
		close;
	}
	mes "[不安な男]";
	mes "どうやら変な場所に";
	mes "入ってきたみたいです。";
	mes "酒場じゃないんですかね？";
	mes "雰囲気変だし。";
	close;
}

job_gun.gat,86,29,3	script	クルベル	10062,{
	if(Job == Job_Rebellion) {
		if(checkquest(121910)&0x8) {
			if(checkquest(121925)&0x8 == 0) {
				setquest 121925;
				compquest 121925;
			}
			mes "[クルベル]";
			mes "る～るる～♪";
			mes "反逆の　りべりお～ん♪";
			mes "　";
			mes "‐クルベルはグラスを磨きながら";
			mes "　楽しげに歌う‐";
			next;
			mes "[クルベル]";
			mes "よお、同志。";
			mes "今日も元気にリベリオンしてるか？";
			mes "ここはリベリオンが集う";
			mes "酒場だからな。";
			mes "たまには寄ってくれよ。";
			close;
		}
		setquest 121910;
		compquest 121910;
		mes "[クルベル]";
		mes "おめでとう。";
		mes "これでお前も一人のリベリオンだな。";
		next;
		mes "[クルベル]";
		mes "手配書のことはちゃーんと";
		mes "対処しておいたから";
		mes "もう追い回されることはないぜ。";
		mes "安心してくれ。";
		next;
		mes "[クルベル]";
		mes "で、もちろんルウィーニや";
		mes "シドレンの話は聞いているよな。";
		next;
		mes "[クルベル]";
		mes "リベリオンにとって銃は";
		mes "ガンスリンガーのころよりも";
		mes "重要なものだ。";
		mes "なんせ己の志を";
		mes "その銃に込め、そして";
		mes "証明し続けるんだからな。";
		next;
		mes "[クルベル]";
		mes "志は一つ。";
		mes "自由と反逆。";
		mes "世の中にはびこる悪には";
		mes "銃で対抗するんだ。";
		mes "その自由を体現するのさ。";
		next;
		mes "[クルベル]";
		mes "何より続けることは難しいが";
		mes "何よりもカッコイイ！";
		mes "そんな存在にお前はなったんだ！";
		next;
		mes "[クルベル]";
		mes "精進しろよ新米！";
		close;
	}
	if(CHANGE_RB == 1) {
		mes "[クルベル]";
		mes "いらっしゃい。";
		mes "ガンスリンガーが";
		mes "この秘密酒場に何の用事だ？";
		next;
		if(select("手配書の話をする","注文を頼む") == 2) {
			mes "[クルベル]";
			mes "何がいいんだい？";
			mes "ドリンクにフード……";
			mes "　";
			mes "手配書かな？";
			emotion 0,"";
			next;
		}
		mes "‐あなたはクルベルに";
		mes "　手配書を突きつけた‐";
		next;
		mes "[クルベル]";
		mes "……うん。";
		mes "いや待って。ぷくく……";
		mes "　";
		mes "‐クルベルの肩が";
		mes "　激しく震えている‐";
		next;
		switch(select("怒る！","銃に手を持っていく")) {
		case 1:
			mes "[クルベル]";
			mes "はっはっは！";
			mes "すまんすまんちょっと待ってくれ。";
			break;
		case 2:
			mes "[クルベル]";
			mes "あっこら！";
			mes "店内で乱闘はごめんだぜ。";
			mes "その手を放しな。";
			next;
			break;
		}
		mes "‐ひとしきり笑って";
		mes "　満足したのか、クルベルは";
		mes "　涙をぬぐって";
		mes "　あなたに向き直った‐";
		next;
		mes "[クルベル]";
		mes "いや、賞金稼ぎから";
		mes "手配書まで手に入れるなんて";
		mes "なかなか見どころがあるじゃないか。";
		next;
		menu "どういうことでしょう？",-;
		mes "[クルベル]";
		mes strcharinfo(0)+ "、";
		mes "お前のガンスリンガーとしての";
		mes "実力は伝え聞いているぞ。";
		mes "　";
		mes "お前は^FF0000リベリオン^000000に";
		mes "興味ないか？";
		next;
		switch(select("リベリオン？","興味ないです","そんなことより手配書！")) {
		case 1:
			break;
		case 2:
			mes "[クルベル]";
			mes "すっかりへそを曲げて。";
			mes "お前はなかなかにかわいいやつだな。";
			next;
			break;
		case 3:
			mes "[クルベル]";
			mes "わかってるさ。";
			mes "せっかちなんだなお前は。";
			mes "それも関係あることだから";
			mes "まずは話を聞いてくれ。";
			next;
			break;
		}
		mes "[クルベル]";
		mes "リベリオンは";
		mes "ガンスリンガーの上位職であり、";
		mes "自由な魂の解放者だ！";
		next;
		mes "[クルベル]";
		mes "世間にはびこる悪は";
		mes "得てして権力も持ち合わせる。";
		mes "そんな悪に対して銃口を向け、";
		mes "反逆するのがリベリオンさ。";
		mes "かっこいいだろ？";
		next;
		mes "[クルベル]";
		mes "……で、ここで一つ";
		mes "種明かしなんだが。";
		mes "この手配書ミス、";
		mes "実はわざとなんだよな。";
		next;
		mes "[クルベル]";
		mes "ガンスリンガーを極めたあんたを";
		mes "スカウトすると同時に";
		mes "その心根がどういうものか";
		mes "確認させてもらったってわけさ。";
		next;
		mes "[クルベル]";
		mes "世俗の悪には";
		mes "志だけでは反逆できない。";
		mes "しかし、最初にあるのは";
		mes "理不尽を放置しない、";
		mes "反逆を決める心根一つ！";
		next;
		mes "[クルベル]";
		mes "あんたの直接乗り込む";
		mes "その意気……";
		mes "　";
		mes "気に入ったぜ！";
		next;
		mes "[クルベル]";
		mes "俺はあんたを同志に";
		mes "迎え入れたい！";
		mes "リベリオンの道を歩んで欲しい！";
		mes "心からだぜ。心の底からだ！";
		next;
		mes "[クルベル]";
		mes "改めて言おう。";
		mes "俺たちリベリオンの一員に";
		mes "なる気はないか？";
		while(1) {
			next;
			switch(select("なる","ならない","喧嘩売ってんのか")) {
			case 1:
				break;
			case 2:
				mes "[クルベル]";
				mes "いやいや、そんなこと言わずに。";
				mes "ガンスリンガーの次は";
				mes "リベリオンを極めようじゃないか。";
				next;
				mes "[クルベル]";
				mes "改めて言おう。";
				mes "俺たちリベリオンの一員に";
				mes "なる気はないか？";
				continue;
			case 3:
				mes "[クルベル]";
				mes "……いいねぇ。";
				mes "　";
				mes "あれだろ？　手配書で";
				mes "誘い出したことに対して";
				mes "反逆してくれるとは。";
				next;
				mes "[クルベル]";
				mes "リベリオンの素質としては";
				mes "もう十分な証明だね。";
				next;
				mes "[クルベル]";
				mes "……というわけで。";
				mes "改めて言おう。";
				mes "俺たちリベリオンの一員に";
				mes "なる気はないか？";
				continue;
			}
			break;
		}
		mes "[クルベル]";
		mes "いいぞいいぞ。";
		mes "よく言ってくれた！";
		mes "それじゃあ、気分が変わらないうちに";
		mes "転職試験と行こうじゃないか。";
		next;
		mes "[クルベル]";
		mes "ん？";
		mes "どうして転職試験かって？";
		next;
		mes "[クルベル]";
		mes "まあ、あんたは";
		mes "スカウトされた人材だが。";
		mes "転職試験でリベリオンとしての";
		mes "志や技術なんかも同時に学べるからさ。";
		mes "ぜひ受けてくれよ。頼むよ。";
		next;
		mes "[クルベル]";
		mes "最初の試験官は";
		mes "ルウィーニってやつさ。";
		mes "すぐわかると思うぜ。";
		next;
		mes "[クルベル]";
		mes "じゃあ、頑張ってこい。";
		mes "次に会うとき、お前は";
		mes "リベリオンになっててくれよ！";
		chgquest 12340,12341;
		set CHANGE_RB,2;
		close2;
		warp "job_gun.gat",19,15;
		end;
	}
	else if(CHANGE_RB == 2) {
		mes "[クルベル]";
		mes "まだ試験の途中のようだな。";
		mes "ルウィーニのところに";
		mes "行くか？";
		next;
		if(select("行く","行かない") == 2) {
			mes "[クルベル]";
			mes "わかった、";
			mes "それじゃ一休みに";
			mes "酒でも飲んでいくか？";
			mes "ハハハハ！";
			close;
		}
		mes "[クルベル]";
		mes "わかった、今会わせてやる。";
		mes "こっちだ。";
		close2;
		warp "job_gun.gat",19,15;
		end;
	}
	else if(CHANGE_RB == 3) {
		// 未調査
		mes "[クルベル]";
		mes "まだ試験の途中のようだな。";
		mes "シドレンのところに";
		mes "行くか？";
		next;
		if(select("行く","行かない") == 2) {
			mes "[クルベル]";
			mes "わかった、";
			mes "それじゃ一休みに";
			mes "酒でも飲んでいくか？";
			mes "ハハハハ！";
			close;
		}
		mes "[クルベル]";
		mes "わかった、今会わせてやる。";
		mes "こっちだ。";
		close2;
		warp "job_gun.gat",120,133;
		end;
	}
	else if(CHANGE_RB == 4) {
		// 未調査
		mes "[クルベル]";
		mes "試験は終わったようだな。";
		mes "シドレンのところに";
		mes "行くか？";
		next;
		if(select("行く","行かない") == 2) {
			mes "[クルベル]";
			mes "わかった、";
			mes "それじゃ一休みに";
			mes "酒でも飲んでいくか？";
			mes "ハハハハ！";
			close;
		}
		mes "[クルベル]";
		mes "わかった、今会わせてやる。";
		mes "次に会うとき、お前は";
		mes "リベリオンになっててくれよ！";
		close2;
		warp "job_gun.gat",210,132;
		end;
	}
}
job_gun.gat,19,24,3	script	ルウィーニ#1	10063,{
	if(CHANGE_RB == 2) {
		mes "[ルウィーニ]";
		mes "やあ。君が";
		mes "クルベルの言っていた";
		mes "リベリオン志望者かな？";
		mes "　";
		mes "‐鋭い目をした小柄な人物が";
		mes "　あなたを見上げた‐";
		next;
		mes "[ルウィーニ]";
		mes "クルベルの態度には";
		mes "さぞ苛立たせられたことだろうな。";
		mes "……まあ、あいつは、あれだ。";
		mes "デリカシーがなくて";
		mes "人懐こいだけなんだ。";
		mes "考えるだけ無駄だ。";
		next;
		mes "[ルウィーニ]";
		mes "……ゴホン。";
		mes "さて、それじゃあ";
		mes "試験の前に";
		mes "ここに署名してくれ。";
		next;
		mes "[ルウィーニ]";
		mes "我々も注意するが、";
		mes "機械や炎、鉄を扱うからな。";
		mes "万が一の為だ。";
		next;
		mes "‐ルウィーニの差し出した紙には";
		mes "　署名者は試験途中に";
		mes "　怪我をしたり、命を失っても";
		mes "　絶対に責任を問わないことを誓う……";
		mes "　";
		mes "　といったことが書かれていた‐";
		next;
		if(select("署名する","署名しない") == 2) {
			mes "[ルウィーニ]";
			mes "了解した。";
			mes "嫌なら仕方がないな。";
			mes "帰っていいぞ。";
			close2;
			warp "job_gun.gat",62,27;
			end;
		}
		mes "[ルウィーニ]";
		mes "書き終わったか。";
		mes "それじゃついて来な。";
		close2;
		warp "job_gun.gat",117,41;
		end;
	}
	mes "[ルウィーニ]";
	mes "なんだ？　道にでも迷ったのか？";
	mes "状況を確認してから";
	mes "試験場に来なさい。";
	close2;
	warp "job_gun.gat",62,27;
	end;
}

job_gun.gat,117,46,3	script	ルウィーニ#2	10063,{
	if(checkquest(12341))
		chgquest 12341,12342;
	if(checkquest(12342)) {
		if(sc_onparam(SC_MONSTER_TRANSFORM,1) == 2431) {
			mes "^0000ff‐すでに変身中です。";
			mes "　試験課題をすべて完了したら";
			mes "　組み立て室に行き、";
			mes "　ルウィーニに";
			mes "　報告してください‐^000000";
			close;
		}
		if(countitem(6746)) {
			delitem 6746,countitem(6746);
			mes "[ルウィーニ]";
			mes "試験で余った鉄製加工物は回収する。";
			next;
		}
		if(countitem(6747)) {
			delitem 6747,countitem(6747);
			mes "[ルウィーニ]";
			mes "規格鉄製加工物を持っているな。";
			mes "試験で余った鉄製加工物は回収する。";
			next;
		}
		if(countitem(13118)) {
			delitem 13118,1;
			mes "[ルウィーニ]";
			mes "銃は完成しているが、";
			mes "既に時間切れで失格だ。";
			mes "残念だがその銃は回収するぞ。";
			next;
		}
		mes "[ルウィーニ]";
		mes "一度しか話さないから";
		mes "よく聞きなさい。";
		next;
		menu "はい",-;
		mes "[ルウィーニ]";
		mes "ここは鋳物を扱っている場所だ。";
		mes "いたるところで鉄製加工物が";
		mes "生産されている。";
		next;
		mes "[ルウィーニ]";
		mes "リベリオンの一番の基本は、";
		mes "武器に対する広い知識。";
		mes "この試験では、";
		mes "必要な材料を選び抜き、";
		mes "己の手で直接";
		mes "銃器を組み立てることになる。";
		next;
		mes "[ルウィーニ]";
		mes "君のやるべきことは、";
		mes "南の出入り口近くにある";
		mes "^0000FF溶鉱炉制御機^000000を操作して";
		mes "取り出せる鉄製加工物の中から、";
		mes "規格に合うものを^FF00002個^000000選ぶことだ。";
		next;
		mes "[ルウィーニ]";
		mes "2個鉄製加工物を確保したら、";
		mes "隣の組み立て室で";
		mes "銃器を組み立てなさい。";
		next;
		mes "[ルウィーニ]";
		mes "銃器組み立ての時間は";
		mes "^FF00003分^000000。";
		mes "技術と知識と、スピードが";
		mes "要求されるぞ。";
		next;
		mes "[ルウィーニ]";
		mes "完成した銃器は隣の部屋で受け取ろう。";
		mes "制限時間をわかりやすくするために、";
		mes "君の外見を変えてもらうぞ。";
		next;
		mes "[ルウィーニ]";
		mes "ちなみに、変身後の姿は私の趣味だ。";
		mes "街で見かけたことがあるんだが、";
		mes "理想のタイプだったのでな。";
		mes "それだったらモチベーションが";
		mes "あがるだろう？";
		next;
		mes "[ルウィーニ]";
		mes "^0000ff3分を超えて変装が解けると";
		mes "試験は失敗。再試験^000000だ。";
		mes "せいぜい励みたまえ。";
		viewpoint 1, 165, 18, 1, 0xFFFF00;
		sc_start SC_MONSTER_TRANSFORM,180000,2431;
		close;
	}
	mes "[ルウィーニ]";
	mes "なんだ？　道にでも迷ったのか？";
	mes "状況を確認してから";
	mes "試験場に来なさい。";
	close2;
	warp "job_gun.gat",62,27;
	end;
}

job_gun.gat,198,39,3	script	ルウィーニ#3	10063,{
	if(checkquest(12342)) {
		if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 2431) {
			mes "[ルウィーニ]";
			mes "時間を過ぎている。失格だ。";
			mes "余った材料はすべて回収する。";
			delitem 6746,countitem(6746);
			delitem 6747,countitem(6747);
			next;
			if(countitem(13118)) {
				// 未調査
				delitem 13118,1;
				mes "[ルウィーニ]";
				mes "銃は完成しているが、";
				mes "既に時間切れで失格だ。";
				mes "残念だがその銃は回収するぞ。";
				next;
			}
			mes "[ルウィーニ]";
			mes "さあ、もう一度だ。";
			mes "励みたまえ。";
			close2;
			warp "job_gun.gat",117,41;
			end;
		}
		if(countitem(13118) == 0) {
			mes "[ルウィーニ]";
			mes "終わったか？";
			mes "……それにしては";
			mes "完成した銃が見当たらないようだが？";
			close;
		}
		delitem 13118,1;
		mes "[ルウィーニ]";
		mes "よし、急いで作ったようだから";
		mes "万全の状態ではないが、";
		mes "とにかく合格だ。";
		mes "余った材料はすべて回収する。";
		delitem 6746,countitem(6746);
		delitem 6747,countitem(6747);
		chgquest 12342,121930;
		set CHANGE_RB,3;
		next;
		mes "[ルウィーニ]";
		mes "それじゃあ、次のコースに案内しよう。";
		mes "次はシドレンが";
		mes "君の教育を担当する。";
		close2;
		warp "job_gun.gat",120,133;
		end;
	}
	mes "[ルウィーニ]";
	mes "なんだ？　道にでも迷ったのか？";
	mes "状況を確認してから";
	mes "試験場に来なさい。";
	close2;
	warp "job_gun.gat",62,27;
	end;
}

job_gun.gat,165,18,1	script	溶鉱炉制御機#1	844,{
	if(checkquest(12342)) {
		mes "‐溶鉱炉から完成した製品を";
		mes "　抽出しますか？‐";
		next;
		if(select("抽出する","やめる") == 2) {
			mes "‐作業を中止し、";
			mes "　待機モードに転換します‐";
			close;
		}
		donpcevent "溶鉱炉制御機#2::OnStart";
		hideonnpc "溶鉱炉制御機#1";
		mes "‐溶鉱炉制御機ZX-3100：作業を開始‐";
		close;
	}
	mes "‐許可が無い人は操作できません‐";
	close;
}

job_gun.gat,165,18,1	script	溶鉱炉制御機#2	844,{
	if(checkquest(12342)) {
		mes "‐完成した鉄製加工物の";
		mes "　抽出が行われています。";
		mes "　完了するまで";
		mes "　任意の作業はできません‐";
		close;
	}
	mes "‐許可が無い人は操作できません‐";
	close;
OnStart:
	hideoffnpc "溶鉱炉制御機#2";
	sleep 3000;
	announce "溶鉱炉制御機 : 溶鉱炉から鉄製加工物の抽出を開始します。生産ラインにて待機してください。", 0x9, 0x00ff44, 0x190, 12, 0, 0;
	sleep 500;
	for(set '@i,0; '@i<30; set '@i,'@i+1) {
		set '@r,rand(1,100);
		if('@r < 33)
			donpcevent "加熱炉#3::OnStart";
		else if('@r < 66)
			donpcevent "加熱炉#4::OnStart";
		else
			donpcevent "加熱炉#5::OnStart";
		sleep 200;
		set '@x,rand(127,143);
		set '@y,rand(26,29);
		dropitem "job_gun.gat",'@x,'@y,6746,1,0;
		if(rand(100) < 50) {
			set '@x,rand(127,143);
			set '@y,rand(26,29);
			dropitem "job_gun.gat",'@x,'@y,6747,1,0;
		}
		sleep 500;
	}
	announce "溶鉱炉制御機 : 抽出作業を完了いたします。", 0x9, 0x00ff44, 0x190, 12, 0, 0;
	sleep 100;
	hideonnpc "溶鉱炉制御機#2";
	hideoffnpc "溶鉱炉制御機#1";
	end;
OnInit:
	hideonnpc;
	end;
}

job_gun.gat,130,31,1	script	加熱炉#3	844,{
	end;
OnStart:
	misceffect 96;
	sleep 500;
	misceffect 97;
	end;
}

job_gun.gat,136,31,1	script	加熱炉#4	844,{
	end;
OnStart:
	misceffect 96;
	sleep 500;
	misceffect 97;
	end;
}

job_gun.gat,141,31,1	script	加熱炉#5	844,{
	end;
OnStart:
	misceffect 96;
	sleep 500;
	misceffect 97;
	end;
}

job_gun.gat,214,36,1	script	全自動金敷#1	844,{
	if(checkquest(12342)) {
		if(countitem(13118)) {
			mes "‐非正規ルートで精製された";
			mes "　銃器の痕跡を発見。";
			mes "　管理者ルウィーニに";
			mes "　報告してください‐";
			close;
		}
		if(countitem(6747) < 2) {
			mes "‐許可が無い人は操作できません‐";
			next;
			mes "‐溶鉱炉制御機を使用して";
			mes "　完成した製品を";
			mes "　抽出してください‐";
			viewpoint 1, 165, 18, 1, 0xFFFF00;
			close;
		}
		mes "‐全自動金敷で規格に当てはまる";
		mes "　鉄製加工物を使用し、";
		mes "　銃器製造を行いますか？‐";
		next;
		if(select("開始する","やめる") == 2) {
			mes "‐全自動金敷の制御を中止します‐";
			close;
		}
		misceffect 101;
		mes "[" +strcharinfo(0)+ "]";
		mes "（全自動金敷を使用し、";
		mes "　正常な武器を製造した。";
		mes "　変身効果が消える前に";
		mes "　報告しよう）";
		delitem 6747,2;
		getitem 13118,1;
		close;
	}
	mes "‐許可が無い人は操作できません‐";
	close;
}

job_gun.gat,95,148,10,10	monster	非射撃標的	3170,3,180000,0,0
job_gun.gat,95,148,10,10	monster	射撃標的	3169,5,180000,0,0
job_gun.gat,95,110,10,15	monster	非射撃標的	3170,3,180000,0,0
job_gun.gat,95,110,10,15	monster	射撃標的	3169,17,180000,0,0
job_gun.gat,140,100,15,10	monster	非射撃標的	3170,13,180000,0,0
job_gun.gat,140,100,15,10	monster	射撃標的	3169,7,180000,0,0
job_gun.gat,140,150,15,10	monster	非射撃標的	3170,4,180000,0,0
job_gun.gat,140,150,15,10	monster	射撃標的	3169,4,180000,0,0
job_gun.gat,115,160,10,10	monster	非射撃標的	3170,8,180000,0,0
job_gun.gat,115,160,10,10	monster	射撃標的	3169,10,180000,0,0

job_gun.gat,120,138,3	script	シドレン#1	10062,{
	if(CHANGE_RB == 3) {
		if(checkquest(12343)) {
			if(checkquest(12343)&4 && checkquest(12344)&4 == 0 && sc_onparam(SC_MONSTER_TRANSFORM,1) == 2431) {
				mes "[シドレン]";
				mes "ふむ、素晴らしいな！";
				mes "こうも簡単にクリアされるとは";
				mes "思っていなかったよ。";
				next;
				mes "[シドレン]";
				mes "最終試験はこれで終わりだ。";
				mes "君は外で待っててくれ。";
				mes "他の教官の評価を回収して";
				mes "私が試験結果を伝えよう。";
				delquest 12343;
				delquest 12344;
				setquest 12345;
				set CHANGE_RB,4;
				close2;
				warp "job_gun.gat",210,132;
				end;
			}
			mes "[シドレン]";
			mes "精度、スピード、";
			mes "何一つ褒めるところがない。";
			mes "完璧に駄目だ。";
			mes "本当に銃を手に生きてきたのか？";
			next;
			mes "[シドレン]";
			mes "すぐに再試験をはじめる。";
			mes "次はしっかり動けよ。";
			delquest 12343;
			delquest 12344;
			setquest 12343;
			setquest 12344;
			sc_start SC_MONSTER_TRANSFORM,180000,2431;
			close2;
			warp "job_gun.gat",102,146;
			end;
		}
		mes "[シドレン]";
		mes "おい！　よそ見するなよ。";
		mes "ここは実弾を使う射撃場だ。";
		mes "少しでも気を抜いたら、";
		mes "怪我につながる場所だぞ。";
		next;
		mes "[シドレン]";
		mes "さて。では最終試験について";
		mes "説明をはじめる。";
		mes "今から君は、^FF00005つの射撃場^000000内を";
		mes "走ることになる。";
		next;
		mes "[シドレン]";
		mes "これは群衆の中にいる目標を";
		mes "正確に見分ける判断力と";
		mes "それに対する迅速さを";
		mes "測定するための試験だ。";
		mes "たくさん倒すことが目的じゃないぞ！";
		next;
		mes "[シドレン]";
		mes "君は射撃場内で";
		mes "よく似た顔をしている連中の中から";
		mes "^0000ff射撃標的^000000と書かれた";
		mes "標的のみを選んで射撃すること。";
		mes "間違って関係ないやつを";
		mes "撃った場合は失点だ。";
		next;
		mes "[シドレン]";
		mes "まあ、最終試験は";
		mes "口での説明より";
		mes "直接経験した方が良いだろう。";
		mes "^0000ff射撃標的^000000という名前の幻影は数が";
		mes "限られているから正確に射撃しろよ。";
		next;
		mes "[シドレン]";
		mes "^0000ff制限時間は3分だ。";
		mes "その変装が解けたら、";
		mes "時間切れとみなして失格になる。^000000";
		mes "その場合はおとなしく私のところに";
		mes "戻ってきなさい。";
		next;
		mes "[シドレン]";
		mes "ん、何の変身か気になるのか？";
		mes "これでわかるだろう？";
		mes "　";
		mes "……ルウィーニの趣味だ。";
		next;
		mes "[シドレン]";
		mes "話を戻すぞ。";
		mes "^0000ff射撃標的を10体";
		mes "射撃できなかったり、";
		mes "不適切な目標を3体";
		mes "射撃しても失格だ。^000000";
		next;
		mes "[シドレン]";
		mes "説明は以上。";
		mes "それじゃすぐはじめることにしよう。";
		setquest 12343;
		setquest 12344;
		delquest 121930;
		sc_start SC_MONSTER_TRANSFORM,180000,2431;
		close2;
		warp "job_gun.gat",102,146;
		end;
	}
	if(CHANGE_RB == 4) {
		mes "[シドレン]";
		mes "どうしてまだここにいるんだ？";
		mes "外に出てくれ。";
		mes "すぐに私も行くから。";
		close2;
		warp "job_gun.gat",210,132;
		end;
	}
	mes "[シドレン]";
	mes "なんだ？　道にでも迷ったのか？";
	mes "状況を確認してから";
	mes "試験場に来なさい。";
	close2;
	warp "job_gun.gat",62,27;
	end;
}

job_gun.gat,88,144,0	warp	射撃場#1	2,2,job_gun.gat,93,123
job_gun.gat,105,97,0	warp	射撃場#2	2,2,job_gun.gat,125,98
job_gun.gat,156,115,0	warp	射撃場#3	2,2,job_gun.gat,157,137
job_gun.gat,152,154,0	warp	射撃場#4	2,2,job_gun.gat,135,154
job_gun.gat,130,146,0	warp	射撃場#5	2,2,job_gun.gat,120,130

job_gun.gat,220,132,3	script	シドレン#2	10062,{
	if(Job == Job_Rebellion) {
		mes "[シドレン]";
		mes "やあ。調子はどうかな？";
		mes "自由を体現するために";
		mes "悪に反逆の引き金を引くのは";
		mes "大変だが、やりがいはあるだろう。";
		close;
	}
	if(CHANGE_RB != 4) {
		mes "[シドレン]";
		mes "なんだ？　道にでも迷ったのか？";
		mes "状況を確認してから";
		mes "試験場に来なさい。";
		close2;
		warp "job_gun.gat",62,27;
		end;
	}
	if(Job == Job_Gunslinger) {
		mes "[シドレン]";
		mes "これまでの成績を総合して、";
		mes "クルベル、ルウィーニ、";
		mes "そして私シドレンが";
		mes "君のリベリオン転職に対する";
		mes "評価を決定した。";
		next;
		mes "[シドレン]";
		mes "結果は……";
		next;
		mes "[シドレン]";
		mes "今回の成績や印象を見た限り、";
		mes "不足なし。";
		next;
		mes "[シドレン]";
		mes "そうだ。";
		mes "君を私たちリベリオンの一員として";
		mes "受け入れることに決定した。";
		mes "おめでとう！";
		next;
		if(SkillPoint) {
			mes "[シドレン]";
			mes "君、^ff0000スキルポイントが";
			mes "まだ残っているぞ。^000000";
			mes "まったく、そのくらいは";
			mes "自分でチェックしといてくれよ。";
			close;
		}
		if(Weight) {
			mes "[シドレン]";
			mes "何やらいろいろ持っているな。";
			mes "邪魔だから^ff0000カルレックス^000000に";
			mes "預かってもらえ。";
			mes "彼は、すぐ近くにいるから";
			mes "わかるだろう？";
			close;
		}
		if(sc_ison(SC_ALL_RIDING)) {
			// 未調査
			mes "[シドレン]";
			mes "騎乗生物から降りてくれ。";
			mes "気持ちはわかるが";
			mes "場にふさわしくないだろ？";
			close;
		}
		resetstatus;
		resetskill;
		setoption 0;
		jobchange Job_Rebellion;
		set CHANGE_RB,0;
		chgquest 12345,201860;
		getitem 13119,1;
		mes "‐あなたは";
		mes "　^FF0000反逆の象徴リベリオン^000000に";
		mes "　転職しました！‐";
		next;
		mes "[シドレン]";
		mes "おお！";
		mes "なかなかにきまってるじゃないか。";
		mes "似合うぞ。後輩！";
		next;
		mes "[シドレン]";
		mes "今、君に渡した銃は";
		mes "ルウィーニ教官が";
		mes "君にと用意したものだ。";
		mes "かなり気をかけて磨いていたぞ。";
		mes "大事に使いなさい。";
		next;
		mes "[シドレン]";
		mes "それじゃまた会おう。";
		close2;
		warp "job_gun.gat",81,29;
		end;
	}
	mes "[シドレン]";
	mes "どうしてここにいるんだ？";
	mes "外に出てくれ。";
	close2;
	warp "job_gun.gat",210,132;
	end;
}

job_gun.gat,220,138,4	shop	小道具自販機	564,13200:1

job_gun.gat,216,138,4	script	カルレックス	47,{
	mes "[カルレックス]";
	mes "転職前に不要な物を預かります。";
	next;
	if(select("倉庫を開く","やめる") == 2) {
		mes "[カルレックス]";
		mes "ご利用いただき、";
		mes "ありがとうございます。";
		mes "さあ、リベリオンに";
		mes "転職しましょう。";
		close;
	}
	mes "[カルレックス]";
	mes "倉庫を開きます。";
	close2;
	openstorage;
	end;
}
