//= Auriga Script ==============================================================
// Ragnarok Online Old Glastheim Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
glast_01.gat,204,273,3	script	フギン	755,{
	if(BaseLevel < 130) {
		mes "[フギン]";
		mes "ふむ、君では力不足だね。";
		next;
		mes "[フギン]";
		mes "そうだな……BaseLv130以上になったら";
		mes "私を助けてもらえるかな？";
		close;
	}
	if(checkquest(12322))
		delquest 12322;
	if(checkquest(12317)) {
		if(!(checkquest(12317) & 0x2)) {
			mes "[フギン]";
			mes "おっと";
			mes "君はまだ次元旅行の後遺症が";
			mes "残っているようだ。";
			mes "今の君では次元旅行はつらいだろう。";
			next;
			mes "[フギン]";
			mes "後遺症がなくなったら";
			mes "また来てくれたまえ。";
			delquest 12318;
			delquest 12319;
			close;
		}
		mes "^0000ff‐古のグラストヘイムの後遺症が^000000";
		mes "^0000ff　全て消えました‐^000000";
		delquest 12317;
		delquest 12318;
		delquest 12319;
		next;
		mes "[フギン]";
		mes "うん？　私にあったことがある？";
		mes "ははは、人違いではないかな。";
		next;
		mes "[フギン]";
		mes "私の名はフギン。";
		mes "時間と次元の狭間を研究する者……";
		mes "とでも言っておこう。";
		next;
		mes "[フギン]";
		mes "君はグラストヘイムの過去について";
		mes "興味があるかい？";
		next;
		mes "[フギン]";
		mes "真実を知っている過去は";
		mes "はたして私にどのような";
		mes "答えを示すのか……なんてな。";
		next;
		mes "[フギン]";
		mes "次元旅行は可能になったのだが……。";
		mes "学者の私ではとてもじゃないが";
		mes "自分で確認するのは怖いのだよ。";
		next;
		mes "[フギン]";
		mes "そうだな。";
		mes "君にならできるかもしれない。";
		next;
		mes "[フギン]";
		mes "私の代わりに次元旅行を";
		mes "してみる気はないかね？";
		next;
		if(select("いいですよ","興味ありません") == 2) {
			mes "[フギン]";
			mes "そうかね？";
			mes "まあ、興味があるときにでも";
			mes "また来てくれたまえ。";
			close;
		}
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[フギン]";
			mes "話が通じる相手でよかったよ。";
			mes "ではどうするかね？ ";
			set '@str1$,"時間の歪み生成";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		else {
			mes "[フギン]";
			mes "話が通じる相手でよかったよ。";
			mes "ではどうするかね？ ";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		next;
		setquest 72950;
	}
	else if(!checkquest(72950)) {
		mes "[フギン]";
		mes "遠い昔、グラストヘイムは";
		mes "今のような姿ではなかった。";
		next;
		mes "[フギン]";
		mes "おっと、旅人を前にして";
		mes "また独り言を口走ってしまったな。";
		next;
		mes "[フギン]";
		mes "私の名はフギン。";
		mes "時間と次元の狭間を研究する者……";
		mes "とでも言っておこう。";
		next;
		menu "学者さんがなぜこんなところに？",-;
		mes "[フギン]";
		mes "君はグラストヘイムの過去について";
		mes "興味があるかい？";
		next;
		mes "[フギン]";
		mes "私は時間と次元の狭間を研究しているが";
		mes "ここが一番気になる場所だったのだよ。";
		next;
		mes "[フギン]";
		mes "はたしてシュミッツ王は";
		mes "ルーンミッドガッツの歴史通りに";
		mes "暴君だったのか……";
		mes "それとも我々の知らない";
		mes "歴史の歪曲があったのか……。";
		next;
		mes "[フギン]";
		mes "真実を知っている過去は";
		mes "はたして私にどのような";
		mes "答えを示すのか……なんてな。";
		next;
		if(select("結果が気になります","興味ありません") == 2) {
			mes "[フギン]";
			mes "そうかね？";
			mes "まあ、興味があるときにでも";
			mes "また来てくれたまえ。";
			close;
		}
		mes "[フギン]";
		mes "結果……か。";
		mes "次元旅行は可能になったのだが……。";
		mes "学者の私ではとてもじゃないが";
		mes "自分で確認するのは怖いのだよ。";
		next;
		mes "[フギン]";
		mes "そうだな。";
		mes "君にならできるかもしれない。";
		next;
		mes "[フギン]";
		mes "私の代わりに次元旅行を";
		mes "してみる気はないかね？";
		next;
		if(select("いいですよ","興味ありません") == 2) {
			mes "[フギン]";
			mes "そうかね？";
			mes "まあ、興味があるときにでも";
			mes "また来てくれたまえ。";
			close;
		}
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[フギン]";
			mes "話が通じる相手でよかったよ。";
			mes "ではどうするかね？ ";
			set '@str1$,"時間の歪み生成";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		else {
			mes "[フギン]";
			mes "話が通じる相手でよかったよ。";
			mes "ではどうするかね？ ";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		next;
		setquest 72950;
		//setquest 12316;
		//compquest 12316;
	}
	else {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			mes "[フギン]";
			mes "ではどうするかね？ ";
			set '@str1$,"時間の歪み生成";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		else {
			mes "[フギン]";
			mes "ではどうするかね？ ";
			set '@str2$,"古のグラストヘイムに入場する";
		}
		next;
	}
	if(getonlinepartymember() < 1) {
		mes "[フギン]";
		mes "1人以上のパーティーを組むか";
		mes "パーティーに入った状態で";
		mes "話しかけてくれるかな？";
		close;
	}
	set '@party$,getpartyname(getcharid(1));
	set '@leader$,getpartyleader(getcharid(1));
	switch(select('@str1$,'@str2$,"やめる")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "パーティー名：" +'@party$;
			mes "パーティーリーダー名：" +'@leader$;
			mes "^0000ffGlast Heim ^000000‐ 予約失敗";
			close;
		}
		mdcreate "Glast Heim";
		mes "[フギン]";
		mes "時間の歪みが生成されたら";
		mes "また私に話しかけてくれ。";
		close;
	case 2:
		mes "[フギン]";
		mes "それではよろしく頼む。";
		mes "なお相手は過去の時代の人間だ。";
		mes "相手に怪しまれないように";
		mes "^FF0000会話はパーティーの代表者が";
		mes "するようにした方がいい。^000000";
		next;
		mes "^ff0000‐パーティーリーダーがいない状態では^000000";
		mes "^ff0000　正常に進行しない箇所があります。^000000";
		mes "^ff0000　ご注意ください‐^000000";
		next;
		switch(mdenter("Glast Heim")) {
		case 0:	// エラーなし
			announce strcharinfo(1)+ "パーティーの" +strcharinfo(0)+ "パーティー員がGlast Heimに入場します",0x9,0x00FF99;
			delquest 72950;
			setquest 12317;
			setquest 12318;
			donpcevent getmdnpcname("#0統制")+ "::OnStart";
			//warp "1@gl_k.gat",150,20;
			end;
		case 1:	// パーティー未加入
			mes "[フギン]";
			mes "時間の歪みに入れる状態ではないね。";
			mes "パーティーを組まないと";
			mes "時間の歪みには入れないのだよ。";
			close;
		case 2:	// ダンジョン未作成
			mes "[フギン]";
			mes "まだ時間の歪みが";
			mes "生成されてないようだね";
			close;
		default:	// その他エラー
			close;
		}
	case 3:
		mes "[フギン]";
		mes "準備が出来たらまた来なさい。";
		close;
	}
}

//============================================================
// 古のグラストヘイム1F
//------------------------------------------------------------
1@gl_k.gat,1,1,1	script	#0統制	844,{
OnStart:
	if('flag > 0)
		end;
	set 'flag,1;

	hideonnpc getmdnpcname("バルムント#1");
	hideonnpc getmdnpcname("バルムント#2");
	hideonnpc getmdnpcname("ハインリヒ#1");
	hideonnpc getmdnpcname("ハインリヒ#2");
	hideonnpc getmdnpcname("ハインリヒ#3");
	hideonnpc getmdnpcname("ハインリヒ#4");
	hideonnpc getmdnpcname("ヒメルメズ#1");
	hideonnpc getmdnpcname("ヒメルメズ#2");
	hideonnpc getmdnpcname("アコライト志望生ドムン#");
	hideonnpc getmdnpcname("鍛冶屋デストロイヤー#1");

	hideonnpc getmdnpcname("#2統制");
	hideonnpc getmdnpcname("#2統制2");
	hideonnpc getmdnpcname("#3統制");
	hideonnpc getmdnpcname("#3統制2");
	hideonnpc getmdnpcname("#4統制");
	hideonnpc getmdnpcname("#4統制2");
	hideonnpc getmdnpcname("#2階入り口");
	hideonnpc getmdnpcname("#ヒメルon");

	hideonnpc getmdnpcname("ヒメルメズ#23");
	hideonnpc getmdnpcname("バルムントの幻影#1");
	hideonnpc getmdnpcname("バルムントの幻影#2");
	hideonnpc getmdnpcname("バルムントの幻影#3");
	hideonnpc getmdnpcname("バルムントの幻影#4");
	hideonnpc getmdnpcname("フギン#21");

	hideonnpc getmdnpcname("#22統制");
	hideonnpc getmdnpcname("#22統制2");
	hideonnpc getmdnpcname("#23統制");
	hideonnpc getmdnpcname("#23統制2");
	hideonnpc getmdnpcname("#24統制");
	hideonnpc getmdnpcname("#24統制2");

	hideonnpc getmdnpcname("怪しい亀裂#1");
	end;
}

1@gl_k.gat,2,1,0	script	#0統制_bc	139,{
}

1@gl_k.gat,145,104,6	script	カーリッツバーグ騎士#1	655,{
	mes "[カーリッツバーグ騎士]";
	mes "もうすぐ勤務交代の時間なのに、";
	mes "何か問題が起きたみたいで";
	mes "交代の人が来ないんです。";
	close;
}

1@gl_k.gat,145,99,6		script	白の騎士#3	657,{
	mes "[白の騎士]";
	mes "バルムント様と一緒に来た方ですか？";
	mes "司令官がお待ちしております。";
	close;
}

1@gl_k.gat,145,94,6		script	カーリッツバーグ騎士#5	655,{
	mes "[カーリッツバーグ騎士]";
	mes "昨夜の夢が気になります。";
	mes "お母さんが夢に出てきたんです。";
	mes "何かあるのかな……";
	close;
}

1@gl_k.gat,145,89,6		script	白の騎士#7	657,{
	mes "[白の騎士]";
	mes "ここでの私語はなるべく控えて下さい。";
	close;
}

1@gl_k.gat,145,84,6		script	カーリッツバーグ騎士#9	655,{
	mes "[カーリッツバーグ騎士]";
	mes "静粛にして下さい。";
	close;
}

1@gl_k.gat,145,79,6		script	白の騎士#11	657,{
	mes "[白の騎士]";
	mes "失礼ですが、バルムント様とは";
	mes "どのような関係ですか。";
	mes "人とのかかわりをあまり持たない方だと";
	mes "聞きましたが……。";
	close;
}

1@gl_k.gat,145,74,6		script	カーリッツバーグ騎士#13	655,{
	mes "[カーリッツバーグ騎士]";
	mes "城の中の気配が何か";
	mes "怪しくありませんか？";
	mes "少し前から何かの気配が";
	mes "消えた気がします。";
	close;
}

1@gl_k.gat,145,69,6		script	白の騎士#15	657,{
	mes "[白の騎士]";
	mes "勤務中の私語は";
	mes "好ましくありません。";
	close;
}

1@gl_k.gat,145,64,6		script	カーリッツバーグ騎士#17	655,{
	mes "[カーリッツバーグ騎士]";
	mes "……。";
	close;
}

1@gl_k.gat,145,59,6		script	白の騎士#19	657,{
	mes "[白の騎士]";
	mes "私に何か御用ですか？";
	close;
}

1@gl_k.gat,145,54,6		script	カーリッツバーグ騎士#21	655,{
	mes "[カーリッツバーグ騎士]";
	mes "……。";
	close;
}

1@gl_k.gat,154,104,3	script	カーリッツバーグ騎士#2	655,{
	mes "[カーリッツバーグ騎士]";
	mes "ふふ、私とお話したいんですか？";
	close;
}

1@gl_k.gat,154,99,3		script	白の騎士#4	657,{
	mes "[白の騎士]";
	mes "もうすぐ交代の時間だというのに";
	mes "交代の者が来ないのです。";
	mes "何か問題が起きたのでしょうか？";
	close;
}

1@gl_k.gat,154,94,3		script	カーリッツバーグ騎士#6	655,{
	mes "[カーリッツバーグ騎士]";
	mes "バルムント様と一緒に来た方ですね？";
	mes "司令官がお待ちしてますよ。";
	close;
}

1@gl_k.gat,154,89,3		script	白の騎士#8	657,{
	mes "[白の騎士]";
	mes "ここでの私語は控えて下さい。";
	close;
}

1@gl_k.gat,154,84,3		script	カーリッツバーグ騎士#10	655,{
	mes "[カーリッツバーグ騎士]";
	mes "静かにしなさい。";
	close;
}

1@gl_k.gat,154,79,3		script	白の騎士#12	657,{
	mes "[白の騎士]";
	mes "失礼ですが、バルムント様とは";
	mes "どのような関係ですか。";
	mes "人とのかかわりをあまり持たない方だと";
	mes "聞きましたが……。";
	close;
}

1@gl_k.gat,154,74,3		script	カーリッツバーグ騎士#14	655,{
	mes "[カーリッツバーグ騎士]";
	mes "城の中の気配が何か";
	mes "怪しくありませんか？";
	mes "少し前から何かの気配が";
	mes "消えた気がします。";
	close;
}

1@gl_k.gat,154,69,3		script	白の騎士#16	657,{
	mes "[白の騎士]";
	mes "勤務中の私語は";
	mes "好ましくありません。";
	close;
}

1@gl_k.gat,154,64,3		script	カーリッツバーグ騎士#18	655,{
	mes "[カーリッツバーグ騎士]";
	mes "……。";
	close;
}

1@gl_k.gat,154,59,3		script	白の騎士#20	657,{
	mes "[白の騎士]";
	mes "私に何か御用ですか？";
	close;
}

1@gl_k.gat,154,54,3		script	カーリッツバーグ騎士#22	655,{
	mes "[カーリッツバーグ騎士]";
	mes "……。";
	close;
}

1@gl_k.gat,149,41,5	script	バルムント#0	654,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "GL_BARMUND1",2;
		if(OLDGLAST_QUE >= 1) {
			mes "‐難しい顔をした男が立っている‐";
			next;
			if(select("急ぐ","会話をする") == 1) {
				mes "[バルムント]";
				mes "急げ！　ハインリヒ卿の所に行って";
				mes "ヒメルメズの事を知らせろ。";
				mes "私もすぐに向かう！";
				unittalk "バルムント : 急げ！　ハインリヒ卿の所に行って ヒメルメズの事を知らせろ。私もすぐに向かう！";
				close2;
				cutin "GL_BARMUND2",255;
				donpcevent getmdnpcname("バルムント#0")+"::OnStart";
				end;
			}
		}
		mes "[バルムント]";
		mes "^0000ffヘリコ^000000がよこした";
		mes "協力者というのは君なのか？";
		unittalk "バルムント : ヘリコがよこした協力者というのは君なのか？";
		next;
		mes "‐ヘリコという人物がよこした";
		mes "　協力者を待っているようだ。";
		mes "　ヘリコという人物は知らないが";
		mes "　ここは話を合わせておこう‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "あ、ははは、ヘリコさんが";
		mes "賢者バルムント様に会ってみろと";
		mes "言っていました。";
		unittalk getcharid(3),strcharinfo(0)+" : あ、ははは、ヘリコさんが賢者バルムント様に会ってみろと言っていました。";
		next;
		cutin "GL_BARMUND2",2;
		mes "[バルムント]";
		mes "そうか。早速で悪いが時間がない。";
		mes "ハインリヒ卿にヒメルメズの侵略に";
		mes "ついて話さなければならないのだ。";
		unittalk "バルムント : そうか。早速で悪いが時間がない。ハインリヒ卿にヒメルメズの侵略について話さなければならないのだ。";
		next;
		menu "ヒメルメズ？",-;
		mes "["+strcharinfo(0)+"]";
		mes "ヒメルメズとは誰ですか？";
		unittalk getcharid(3),strcharinfo(0)+" : ヒメルメズとは誰ですか？";
		next;
		cutin "GL_BARMUND3",2;
		mes "[バルムント]";
		mes "ヘリコはそんなことも";
		mes "教えてくれなかったのか？";
		unittalk "バルムント : ヘリコはそんなことも教えてくれなかったのか？";
		next;
		cutin "GL_BARMUND2",2;
		mes "[バルムント]";
		mes "死人を治める者、亡者のヴァルキリー。";
		mes "彼女は今ここに隠してある";
		mes "ユミルの心臓を手に入れるつもりだ。";
		unittalk "バルムント : 死人を治める者、亡者のヴァルキリー。彼女は今ここに隠してあるユミルの心臓を手に入れるつもりだ。";
		next;
		mes "[バルムント]";
		mes "おそらく、目的の為ならこの城ごと";
		mes "破壊してしまうだろう。";
		unittalk "バルムント : おそらく、目的の為ならこの城ごと破壊してしまうだろう。";
		next;
		mes "[バルムント]";
		mes "急げ！　ハインリヒ卿の所に行って";
		mes "ヒメルメズの事を知らせろ。";
		mes "私もすぐに向かう！";
		unittalk "バルムント : 急げ！　ハインリヒ卿の所に行って ヒメルメズの事を知らせろ。私もすぐに向かう！";
		close2;
		cutin "GL_BARMUND2",255;
		donpcevent getmdnpcname("バルムント#0")+"::OnStart";
		end;
	}
	else {
		cutin "GL_BARMUND1",2;
		mes "[バルムント]";
		mes "君たちの代表者はどこにいるんだ？";
		mes "あの者の助けが必要だ。";
		close2;
		cutin "GL_BARMUND1",255;
		end;
	}
OnStart:
	hideonnpc getmdnpcname("バルムント#0");
	hideoffnpc getmdnpcname("ハインリヒ#1");
	end;
}

1@gl_k.gat,152,97,3	script	バルムント#1	654,{
	end;
OnTalk1:
	unittalk "バルムント : 冗談ではありません、ハインリヒ卿。私の考えが正しければ、もうすぐ彼女がここに来るはずです。";
	end;
OnTalk2:
	unittalk "バルムント : 私と一緒に来たこの者は信用できる人物です。ヒメルメズがここにあるユミルの心臓の欠片を手に入れる前に、安全な場所に隠さなければなりません。";
	end;
OnTalk3:
	unittalk "バルムント : 貴様、いつの間に！";
	end;
OnTalk4:
	unittalk "バルムント : ハインリヒ卿、お気をたしかに。彼らはすでに魔物化しています。彼らに安息を与えてやるのが司令官の務めです。";
	end;
OnTalk5:
	unittalk "バルムント : 彼らはもう、人間には戻れないのです。";
	end;
OnTalk6:
	unittalk "バルムント : 今は君の力が必要だ。よろしく頼む。";
	end;
OnTalk7:
	unittalk "バルムント : ではハインリヒ卿、急いでヒメルメズの後を追いましょう。";
	end;
}

1@gl_k.gat,149,100,5	script	ハインリヒ#1	652,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		cutin "GL_HEINRICH2",2;
		if(OLDGLAST_QUE >= 1) {
			mes "‐彼がバルムントの言っていた";
			mes "　ハインリヒ卿だろう‐";
			next;
			if(select("急ぐ","会話をする") == 1) {
				for(set '@i,1; '@i<=20; set '@i,'@i+4) {
					hideonnpc getmdnpcname("カーリッツバーグ騎士#"+'@i);
					hideonnpc getmdnpcname("カーリッツバーグ騎士#"+('@i+1));
					hideonnpc getmdnpcname("白の騎士#"+('@i+2));
					hideonnpc getmdnpcname("白の騎士#"+('@i+3));
				}
				hideonnpc getmdnpcname("カーリッツバーグ騎士#21");
				hideonnpc getmdnpcname("カーリッツバーグ騎士#22");
				hideonnpc getmdnpcname("ヒメルメズ#1");
				hideonnpc getmdnpcname("バルムント#1");
				hideonnpc getmdnpcname("ハインリヒ#1");
				initnpctimer;
				setnpctimer 200000;
				cutin "GL_HEINRICH1",255;
				close;
			}
		}
		mes "["+strcharinfo(0)+"]";
		mes "あなたがハインリヒ様ですね。";
		mes "この城の事でバルムント様より";
		mes "言伝があります。";
		unittalk getcharid(3),strcharinfo(0)+" : あなたがハインリヒ様ですね。この城の事でバルムント様より言伝があります。";
		next;
		cutin "GL_HEINRICH2",2;
		mes "[ハインリヒ]";
		mes "あなたは確か、バルムント様と";
		mes "一緒に来た冒険者の方ですね。";
		mes "この城の中で何か問題でも？";
		unittalk "ハインリヒ : あなたは確か、バルムント様と一緒に来た冒険者の方ですね。この城の中で何か問題でも？";
		next;
		menu "ユミルの心臓が狙われています",-;
		mes "["+strcharinfo(0)+"]";
		mes "ヒメルメズというヴァルキリーが、";
		mes "この城の中に隠してある";
		mes "ユミルの心臓の欠片を狙っています。";
		unittalk getcharid(3),strcharinfo(0)+" : ヒメルメズというヴァルキリーが、この城の中に隠してあるユミルの心臓の欠片を狙っています。";
		next;
		cutin "GL_HEINRICH1",2;
		mes "[ハインリヒ]";
		mes "ははは、冗談はやめてください。";
		mes "そんなモノがここにあるわけ";
		mes "ないじゃないですか。";
		unittalk "ハインリヒ : ははは、冗談はやめてください。そのようなモノがここにあるわけないじゃないですか。";
		next;
		hideoffnpc getmdnpcname("バルムント#1");
		cutin "GL_BARMUND2",2;
		mes "[バルムント]";
		mes "冗談ではありません、ハインリヒ卿。";
		mes "私の考えが正しければ、";
		mes "もうすぐ彼女がここに来るはずです。";
		donpcevent getmdnpcname("バルムント#1")+"::OnTalk1";
		next;
		cutin "GL_HEINRICH1",2;
		mes "[ハインリヒ]";
		mes "これはバルムント様……。";
		mes "いくら貴方の頼みといえど……";
		mes "いや、しかし……。";
		unittalk "ハインリヒ : これはバルムント様……。いくら貴方の頼みといえど……いや、しかし……。";
		next;
		cutin "GL_BARMUND2",2;
		mes "[バルムント]";
		mes "私と一緒に来たこの者は";
		mes "信用できる人物です。";
		mes "ヒメルメズがここにある";
		mes "ユミルの心臓の欠片を手に入れる前に";
		mes "安全な場所に隠さなければなりません。";
		donpcevent getmdnpcname("バルムント#1")+"::OnTalk2";
		next;
		menu "時間がありません",-;
		cutin "GL_BARMUND2",255;
		mes "["+strcharinfo(0)+"]";
		mes "信じられないかも知れませんが";
		mes "時間がありません！";
		unittalk getcharid(3),strcharinfo(0)+" : 信じられないかも知れませんが 時間がありません！";
		next;
		cutin "GL_HEINRICH1",2;
		mes "[ハインリヒ]";
		mes "……確かに、";
		mes "この城にはユミルの心臓の欠片が";
		mes "隠されています。";
		unittalk "ハインリヒ : ……確かに、この城にはユミルの心臓の欠片が隠されています。";
		next;
		mes "[ハインリヒ]";
		mes "ですが、国王様が不在の今、";
		mes "そのような推測だけで";
		mes "ユミルの心臓を動かすわけには";
		mes "いきません。";
		unittalk "ハインリヒ : ですが、国王様が不在の今、そのような推測だけでユミルの心臓を動かすわけにはいきません。";
		close2;
		cutin "gl_heinrich1",255;
		donpcevent getmdnpcname("ハインリヒ#1")+"::OnStart";
		end;
	}
	else {
		cutin "GL_HEINRICH2",2;
		mes "[ハインリヒ]";
		mes "あなたたちは誰ですか？";
		mes "話があるのなら、";
		mes "代表者から伺いましょう。";
		close2;
		cutin "GL_HEINRICH2",255;
		end;
	}
OnStart:
	initnpctimer;
	hideonnpc getmdnpcname("ハインリヒ#1");
	announce "女性の声 : おーほっほっほ！",0x9,0xffff44;
	hideoffnpc getmdnpcname("ヒメルメズ#1");
	hideoffnpc getmdnpcname("ハインリヒ#2");
	end;
OnTimer1000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk1";
	end;
OnTimer4000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk1";
	end;
OnTimer9000:
	donpcevent getmdnpcname("バルムント#1")+"::OnTalk3";
	end;
OnTimer10000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk2";
	end;
OnTimer14000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk2";
	end;
OnTimer19000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk3";
	end;
OnTimer23000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk4";
	end;
OnTimer29000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk3";
	end;
OnTimer32000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk5";
	end;
OnTimer38000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk6";
	end;
OnTimer44000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk4";
	end;
OnTimer50000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk7";
	end;
OnTimer56000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk8";
	end;
OnTimer65000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk5";
	end;
OnTimer70000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk9";
	end;
OnTimer80000:
	donpcevent getmdnpcname("ヒメルメズ#1")+"::OnTalk10";
	end;
OnTimer86000:
	hideonnpc getmdnpcname("ヒメルメズ#1");
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk6";
	end;
OnTimer92000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk7";
	end;
OnTimer98000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk8";
	end;
OnTimer100000:
	for(set '@i,1; '@i<=20; set '@i,'@i+4) {
		hideonnpc getmdnpcname("カーリッツバーグ騎士#"+'@i);
		hideonnpc getmdnpcname("カーリッツバーグ騎士#"+('@i+1));
		hideonnpc getmdnpcname("白の騎士#"+('@i+2));
		hideonnpc getmdnpcname("白の騎士#"+('@i+3));
	}
	hideonnpc getmdnpcname("カーリッツバーグ騎士#21");
	hideonnpc getmdnpcname("カーリッツバーグ騎士#22");

	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk9";

	set '@map$,getmdmapname("1@gl_k.gat");
	set '@label$,getmdnpcname("ハインリヒ#1")+"::OnKilled";
	monster '@map$,145,104,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,104,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,145,99,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,154,99,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,145,94,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,94,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,145,89,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,154,89,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,145,84,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,84,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,145,79,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,154,79,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,145,74,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,74,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,145,69,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,154,69,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,145,64,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,64,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,145,59,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,154,59,"堕ちた白の騎士",2470,1,'@label$;
	monster '@map$,145,54,"呪いのカーリッツバーグ",2471,1,'@label$;
	monster '@map$,154,54,"呪いのカーリッツバーグ",2471,1,'@label$;
	end;
OnTimer105000:
	donpcevent getmdnpcname("バルムント#1")+"::OnTalk4";
	end;
OnTimer110000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk10";
	end;
OnTimer112000:
	donpcevent getmdnpcname("バルムント#1")+"::OnTalk5";
	end;
OnTimer116000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk11";
	end;
OnTimer120000:
	donpcevent getmdnpcname("ハインリヒ#2")+"::OnTalk12";
	end;
OnTimer126000:
	announce "ハインリヒの叫び : 死者は死者のいるべき場所へ",0x9,0xFFFF00;
	end;
OnTimer128000:
	announce "ハインリヒの叫び : 還れ！",0x9,0xFFFF00;
	end;
OnTimer128500:
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#1");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#2");
	end;
OnTimer129000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#1");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#2");
	misceffect 226,getmdnpcname("白の騎士#3");
	misceffect 226,getmdnpcname("白の騎士#4");
	end;
OnTimer129500:
	misceffect 85,getmdnpcname("白の騎士#3");
	misceffect 85,getmdnpcname("白の騎士#4");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#5");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#6");
	end;
OnTimer130000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#5");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#6");
	misceffect 226,getmdnpcname("白の騎士#7");
	misceffect 226,getmdnpcname("白の騎士#8");
	end;
OnTimer130500:
	misceffect 85,getmdnpcname("白の騎士#7");
	misceffect 85,getmdnpcname("白の騎士#8");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#9");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#10");
	end;
OnTimer131000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#9");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#10");
	misceffect 226,getmdnpcname("白の騎士#11");
	misceffect 226,getmdnpcname("白の騎士#12");
	end;
OnTimer131500:
	misceffect 85,getmdnpcname("白の騎士#11");
	misceffect 85,getmdnpcname("白の騎士#12");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#13");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#14");
	end;
OnTimer132000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#13");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#14");
	misceffect 226,getmdnpcname("白の騎士#15");
	misceffect 226,getmdnpcname("白の騎士#16");
	end;
OnTimer132500:
	misceffect 85,getmdnpcname("白の騎士#15");
	misceffect 85,getmdnpcname("白の騎士#16");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#17");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#18");
	end;
OnTimer133000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#17");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#18");
	misceffect 226,getmdnpcname("白の騎士#19");
	misceffect 226,getmdnpcname("白の騎士#20");
	end;
OnTimer133500:
	misceffect 85,getmdnpcname("白の騎士#19");
	misceffect 85,getmdnpcname("白の騎士#20");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#21");
	misceffect 226,getmdnpcname("カーリッツバーグ騎士#22");
	end;
OnTimer134000:
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#21");
	misceffect 85,getmdnpcname("カーリッツバーグ騎士#22");
	hideoffnpc getmdnpcname("ハインリヒ#3");
	hideonnpc getmdnpcname("ハインリヒ#2");
	killmonster getmdmapname("1@gl_k.gat"),getmdnpcname("ハインリヒ#1")+"::OnKilled";
	end;
OnTimer143000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk1";
	end;
OnTimer146000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk2";
	end;
OnTimer150000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk3";
	end;
OnTimer154000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk4";
	end;
OnTimer158000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk5";
	end;
OnTimer162000:
	donpcevent getmdnpcname("ハインリヒ#3")+"::OnTalk6";
	end;
OnTimer166000:
	donpcevent getmdnpcname("バルムント#1")+"::OnTalk6";
	end;
OnTimer170000:
	donpcevent getmdnpcname("バルムント#1")+"::OnTalk7";
	end;
OnTimer174000:
	hideonnpc getmdnpcname("ハインリヒ#3");
	hideonnpc getmdnpcname("バルムント#1");
	announce "ハインリヒ : 最初は西側のエリアを集中的に捜索していただけますか？",0x9,0xffff00;
	end;
OnTimer178000:
	announce "ハインリヒ : 西側は幼い子供が多くいるエリアなのです……。",0x9,0xffff00;
	end;
OnTimer182000:
	stopnpctimer;
	announce "ハインリヒ : 怯えている子供がいるかもしれません。どうかよろしくお願いします。",0x9,0xffff00;
	hideoffnpc getmdnpcname("#2統制");
	hideoffnpc getmdnpcname("#2統制2");
	donpcevent getmdnpcname("#2統制_mobdead")+ "::OnStart";
	end;
OnTimer202000:
	announce "ハインリヒ : 最初は西側のエリアを集中的に捜索していただけますか？",0x9,0xffff00;
	end;
OnTimer206000:
	announce "ハインリヒ : 西側は幼い子供が多くいるエリアなのです……。",0x9,0xffff00;
	end;
OnTimer210000:
	stopnpctimer;
	announce "ハインリヒ : 怯えている子供がいるかもしれません。どうかよろしくお願いします。",0x9,0xffff00;
	hideoffnpc getmdnpcname("#2統制");
	hideoffnpc getmdnpcname("#2統制2");
	donpcevent getmdnpcname("#2統制_mobdead")+ "::OnStart";
	end;
OnKilled:
	end;
}

1@gl_k.gat,149,89,1	script	ヒメルメズ#1	650,{
	end;
OnTalk1:
	unittalk "女性 : あら、お邪魔だったかしら？　お客様が訪ねて来たのに、誰も気づいてくれなかったから寂しくて。";
	end;
OnTalk2:
	unittalk "ヒメルメズ : 私の名前はリサ・カン・ヒメルメズ。死人を治める者、亡者のヴァルキリー、そう呼ばれてるみたいね。";
	end;
OnTalk3:
	unittalk "ヒメルメズ : あなたがハインリヒ？　へぇ～、本当に今でも若い姿のままなのね。";
	end;
OnTalk4:
	unittalk "ヒメルメズ : それに、とっても紳士的なのね。でも、あなたの主君の行方を聞いても涼しい顔をしていられるかしら？";
	end;
OnTalk5:
	unittalk "ヒメルメズ : 気になるの？　空席の玉座を欲しがりもしないで、永々と王の帰還を待っているのね……本当に不思議な男。";
	end;
OnTalk6:
	unittalk "ヒメルメズ : その純粋さ、嫌いじゃないわ。もっと違う場所で出逢えたら良かったのに。残念ね。";
	end;
OnTalk7:
	unittalk "ヒメルメズ : そうね。そう……あなたのご主人は、ルーンミッドガッツ王家に招待されているのよね。";
	end;
OnTalk8:
	unittalk "ヒメルメズ : でも変じゃない？　王が出発してからどれだけの時間が経ったかしら？";
	end;
OnTalk9:
	unittalk "ヒメルメズ : さあね～？　ゆっくり説明してあげたいけど、私の用を終わらせないと。";
	end;
OnTalk10:
	unittalk "ヒメルメズ : 私は紅茶をいただいてくるわ。この城に隠された最高の紅茶を……ね。";
	end;
}

1@gl_k.gat,149,97,5	script	ハインリヒ#2	652,{
	end;
OnTalk1:
	unittalk "ハインリヒ : 誰だ！";
	end;
OnTalk2:
	unittalk "ハインリヒ : ほう、物騒な二つ名と違って美しいレディだ。ですが、ここには貴女のお気に召すような紅茶はありませんよ。";
	end;
OnTalk3:
	unittalk "ハインリヒ : ……何だと？";
	end;
OnTalk4:
	unittalk "ハインリヒ : 戯言を……私の主はルーンミッドガッツ王家の招待に応じただけだ。";
	end;
OnTalk5:
	unittalk "ハインリヒ : ……貴様……王の身に何が起きた！";
	end;
OnTalk6:
	unittalk "ハインリヒ : ……しまった！　奴はユミルの心臓の欠片がある場所を把握している！";
	end;
OnTalk7:
	unittalk "ハインリヒ : カーリッツバーグ騎士団と白衣の騎士団は今すぐ奴を追え！";
	end;
OnTalk8:
	unittalk "ハインリヒ : ……おい、どうした！　なぜ追わない！";
	end;
OnTalk9:
	unittalk "ハインリヒ : ま、まさかこんなことが……私の部下たちが……あ、ありえない！";
	end;
OnTalk10:
	unittalk "ハインリヒ : ……。";
	end;
OnTalk11:
	unittalk "ハインリヒ : ……そうですね。すみません……。";
	end;
OnTalk12:
	unittalk "ハインリヒ : すまない、すべて私の責任だ……。せめて安らかに眠ってくれ……。";
	end;
}

1@gl_k.gat,149,100,5	script	ハインリヒ#3	652,{
	end;
OnTalk1:
	unittalk "ハインリヒ : ……バルムント様のおっしゃる通りです。悲しんでいる場合ではありません。";
	end;
OnTalk2:
	unittalk "ハインリヒ : 冒険者の方にお願いがあります。";
	end;
OnTalk3:
	unittalk "ハインリヒ : まだこの周辺に生存者がいるかもしれません。生存者を探して助けてあげて下さい。";
	end;
OnTalk4:
	unittalk "ハインリヒ : それから……ヒメルメズは生きている人間を魔物に変える能力を持っているようです。";
	end;
OnTalk5:
	unittalk "ハインリヒ : 魔物と化した者は、どうか……あなたの手で……";
	end;
OnTalk6:
	unittalk "ハインリヒ : ……私は、バルムント様と共にヒメルメズの後を追います。";
	end;
}

1@gl_k.gat,96,80,0	warp	#2統制	2,2,1@gl_k.gat,80,80
1@gl_k.gat,95,80,0	script	#2統制_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@gl_k.gat");
	set '@label$,getmdnpcname("#2統制_mobdead")+"::OnKilled";
	areamonster '@map$,6,62,11,93,"叫喚の庭園師",2464,8,'@label$;
	areamonster '@map$,30,102,36,136,"叫喚の庭園師",2464,9,'@label$;
	areamonster '@map$,9,16,15,35,"恨みのメイド",2465,8,'@label$;
	areamonster '@map$,47,16,56,35,"恨みのメイド",2465,9,'@label$;
	areamonster '@map$,76,10,87,40,"苦痛の家令",2466,5,'@label$;
	areamonster '@map$,76,50,87,99,"苦痛の家令",2466,12,'@label$;
	end;
OnKilled:
	set '@map$,getmdmapname("1@gl_k.gat");
	set '@label$,getmdnpcname("#2統制_mobdead")+"::OnKilled";
	set '@count,51 - getmapmobs('@map$,'@label$);
	if('@count >= 37) {
		initnpctimer;
		viewpoint 0,17,51,0,0xFF0000;
	}
	end;
OnTimer1000:
	stopnpctimer;
	announce "ヒメルメズの魔力でモンスター化した人々が消えていく……付近の生存者を探そう。",0x9,0xffff00;
	killmonster getmdmapname("1@gl_k.gat"),getmdnpcname("#2統制_mobdead")+"::OnKilled";
	hideoffnpc getmdnpcname("アコライト志望生ドムン#");
	end;
}

1@gl_k.gat,90,80,0	warp	#2統制2	2,2,1@gl_k.gat,105,80
1@gl_k.gat,80,80,0	script	#2ドムンの叫び	139,1,1,{
	hideonnpc;
	initnpctimer;
	announce "子供の声 : 誰か助けてーーーー!!",0x9,0xffff00;
	end;
OnTimer4000:
	announce "子供の声 : 石像の後ろに隠れたけど、魔物がいて出られないよぉ……",0x9,0xffff00;
	end;
OnTimer8000:
	stopnpctimer;
	announce "子供の声 : 誰か魔物を倒してよーーー!!",0x9,0xffff00;
	end;
}

1@gl_k.gat,17,51,3	script	アコライト志望生ドムン#	706,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[アコライト志望生ドムン]";
		mes "助けて下さい！　助けて下さい！";
		unittalk "アコライト志望生ドムン : 助けて下さい！　助けて下さい！";
		next;
		menu "大丈夫？",-;
		mes "["+strcharinfo(0)+"]";
		mes "大丈夫？";
		unittalk getcharid(3),strcharinfo(0)+" : 大丈夫？";
		next;
		mes "[アコライト志望生ドムン]";
		mes "家令様が……修道士様が……";
		mes "みんな怪物になってしまいました。";
		mes "僕は何もできなくて……。";
		unittalk "アコライト志望生ドムン : 家令様が……修道士様が……みんな怪物になってしまいました。僕は何もできなくて……。";
		next;
		mes "[アコライト志望生ドムン]";
		mes "ただ、ここに隠れているしか……";
		mes "何も、何もできませんでした……。";
		unittalk "アコライト志望生ドムン : ただ、ここに隠れているしか……何も、何もできませんでした……。";
		next;
		menu "しっかりして！",-;
		mes "["+strcharinfo(0)+"]";
		mes "しっかりして！";
		mes "中央ホールから南に向かえば";
		mes "外に出れる！";
		mes "その経路は安全だから！";
		unittalk getcharid(3),strcharinfo(0)+" : しっかりして！　中央ホールから南に向かえば外に出れる！　その経路は安全だから！";
		next;
		mes "[アコライト志望生ドムン]";
		mes "中央ホールですか？";
		mes "ひとりで？　どうやって？";
		unittalk "アコライト志望生ドムン : 中央ホールですか？　ひとりで？　どうやって？";
		next;
		mes "‐ふと足元を見ると";
		mes "　犠牲となった人の持ち物らしき";
		mes "　1本のメイスが転がっていた‐";
		unittalk getcharid(3),strcharinfo(0)+" : ‐ふと足元を見ると犠牲となった人の持ち物らしき1本のメイスが転がっていた‐";
		next;
		menu "このメイスを使って",-;
		mes "["+strcharinfo(0)+"]";
		mes "このメイスを使って。";
		mes "身を守るくらいには使えるはず。";
		mes "どうしてもダメなら目を閉じて";
		mes "振り回すんだ。";
		unittalk getcharid(3),strcharinfo(0)+" : このメイスを使って。身を守るくらいには使えるはず。どうしてもダメなら目を閉じて振り回すんだ。";
		next;
		mes "[アコライト志望生ドムン]";
		mes "わかりました。";
		mes "や、やってみます。";
		unittalk "アコライト志望生ドムン : わかりました。や、やってみます。";
		close2;
		hideonnpc;
		announce strcharinfo(0) +" : この付近の生存者は他には居ないようだ。今度は東側のエリアを集中的に捜索しよう。",0x9,0xffff00;
		viewpoint 0,202,79,0,0xFF0000;
		hideoffnpc getmdnpcname("#3統制");
		hideoffnpc getmdnpcname("#3統制2");
		donpcevent getmdnpcname("#3統制_mobdead")+ "::OnStart";
		end;
	}
	else {
		mes "[アコライト志望生ドムン]";
		mes "助けて下さい！　みんなが……";
		mes "みんなが怪物になってしまって！";
		next;
		mes "‐恐怖でパニックを起こしている。";
		mes "　パーティーリーダーで話しかけて";
		mes "　まずはドムンを落ち着かせよう‐";
		close;
	}
}

1@gl_k.gat,224,82,3		script	息絶えた男#1	849,5,5,{
	if(sc_ison(4) || sc_ison(5) || sc_ison(119) || sc_ison(402) || sc_ison(438))
		end;
	set '@num,rand(3,7);
	set '@dummy,getmapxy('@map$,'@x,'@y,1);
	misceffect 124;
	hideonnpc;
	monster '@map$,'@x,'@y,"マゴット",2467,'@num;
	end;
}

1@gl_k.gat,233,123,4	duplicate(息絶えた男#1)	息絶えた男#2	849,5,5
1@gl_k.gat,258,150,2	duplicate(息絶えた男#1)	息絶えた男#3	849,5,5
1@gl_k.gat,255,157,5	duplicate(息絶えた男#1)	息絶えた男#4	849,5,5
1@gl_k.gat,280,167,4	duplicate(息絶えた男#1)	息絶えた男#5	849,5,5
1@gl_k.gat,293,161,2	duplicate(息絶えた男#1)	息絶えた男#6	849,5,5
1@gl_k.gat,249,101,3	duplicate(息絶えた男#1)	息絶えた男#7	849,5,5
1@gl_k.gat,241,86,6		duplicate(息絶えた男#1)	息絶えた男#8	849,5,5
1@gl_k.gat,246,62,8		duplicate(息絶えた男#1)	息絶えた男#9	849,5,5
1@gl_k.gat,240,43,7		duplicate(息絶えた男#1)	息絶えた男#10	849,5,5
1@gl_k.gat,271,19,1		duplicate(息絶えた男#1)	息絶えた男#11	849,5,5
1@gl_k.gat,282,48,5		duplicate(息絶えた男#1)	息絶えた男#12	849,5,5
1@gl_k.gat,285,81,7		duplicate(息絶えた男#1)	息絶えた男#13	849,5,5
1@gl_k.gat,276,106,8	duplicate(息絶えた男#1)	息絶えた男#14	849,5,5
1@gl_k.gat,261,164,8	duplicate(息絶えた男#1)	息絶えた男#15	849,5,5
1@gl_k.gat,269,173,8	duplicate(息絶えた男#1)	息絶えた男#16	849,5,5
1@gl_k.gat,252,120,8	duplicate(息絶えた男#1)	息絶えた男#17	849,5,5
1@gl_k.gat,225,63,8		duplicate(息絶えた男#1)	息絶えた男#18	849,5,5
1@gl_k.gat,227,39,8		duplicate(息絶えた男#1)	息絶えた男#19	849,5,5
1@gl_k.gat,226,27,8		duplicate(息絶えた男#1)	息絶えた男#20	849,5,5
1@gl_k.gat,223,17,9		duplicate(息絶えた男#1)	息絶えた男#21	849,5,5
1@gl_k.gat,230,50,10	duplicate(息絶えた男#1)	息絶えた男#22	849,5,5
1@gl_k.gat,235,16,11	duplicate(息絶えた男#1)	息絶えた男#23	849,5,5
1@gl_k.gat,226,96,12	duplicate(息絶えた男#1)	息絶えた男#24	849,5,5
1@gl_k.gat,222,119,13	duplicate(息絶えた男#1)	息絶えた男#25	849,5,5
1@gl_k.gat,251,20,14	duplicate(息絶えた男#1)	息絶えた男#26	849,5,5

1@gl_k.gat,202,79,0		warp	#3統制	2,2,1@gl_k.gat,215,79
1@gl_k.gat,202,80,0		script	#3統制_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@gl_k.gat");
	set '@label$,getmdnpcname("#3統制_mobdead")+"::OnKilled";
	areamonster '@map$,235,20,255,55,"腐っていく鍛冶屋",2464,4,'@label$;
	areamonster '@map$,275,55,293,60,"腐っていく鍛冶屋",2464,5,'@label$;
	areamonster '@map$,234,82,280,180,"腐っていく鍛冶屋",2464,24,'@label$;
	areamonster '@map$,235,25,255,55,"凶悪な精錬師",2466,4,'@label$;
	areamonster '@map$,275,55,293,60,"凶悪な精錬師",2466,5,'@label$;
	areamonster '@map$,234,82,280,180,"凶悪な精錬師",2466,24,'@label$;
	end;
OnKilled:
	set '@count,66 - getmapmobs(getmdmapname("1@gl_k.gat"),getmdnpcname("#3統制_mobdead")+"::OnKilled");
	if('@count >= 56) {
		initnpctimer;
		viewpoint 0,291,145,0,0xFF0000;
	}
	end;
OnTimer1000:
	stopnpctimer;
	announce "ヒメルメズの魔力でモンスター化した人々が消えていく……付近の生存者を探そう。",0x9,0xffff00;
	killmonster getmdmapname("1@gl_k.gat"),getmdnpcname("#3統制_mobdead")+"::OnKilled";
	hideoffnpc getmdnpcname("鍛冶屋デストロイヤー#1");
	end;
}

1@gl_k.gat,206,79,0		warp	#3統制2	2,2,1@gl_k.gat,195,79

1@gl_k.gat,215,79,0		script	#3デストロイヤーの叫び	139,1,1,{
	hideonnpc;
	initnpctimer;
	announce "女性の声 : ちょっと！　近寄らないでよ！",0x9,0xffff00;
	end;
OnTimer4000:
	announce "女性の声 : これでも喰らえっ！　どりゃ～～～～っ!!!",0x9,0xffff00;
	end;
OnTimer8000:
	stopnpctimer;
	announce "女性の声 : あちゃー、数多すぎ！　仕方ない、魔物がいなくなるまで隠れるか……",0x9,0xffff00;
	end;
}

1@gl_k.gat,291,145,3	script	鍛冶屋デストロイヤー#1	726,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[鍛冶屋デストロイヤー]";
		mes "いやああ！　来ないで！";
		misceffect 102;
		unittalk "鍛冶屋デストロイヤー : いやああ！　来ないで！";
		next;
		menu "安心して下さい",-;
		mes "["+strcharinfo(0)+"]";
		mes "安心して下さい！　人間です。";
		mes "おひとりですか？";
		mes "他の生存者はいませんか？";
		unittalk getcharid(3),strcharinfo(0)+" : 安心して下さい！　人間です。おひとりですか？　他の生存者はいませんか？";
		next;
		mes "[鍛冶屋デストロイヤー]";
		mes "生き残ったのは私だけです……。";
		unittalk "鍛冶屋デストロイヤー : 生き残ったのは私だけです……。";
		next;
		menu "ここは危険です",-;
		mes "["+strcharinfo(0)+"]";
		mes "ここは危険です。";
		mes "中央ホールに行く道は解りますか？";
		mes "身重な体のようですが……。";
		mes "動けそうですか？";
		unittalk getcharid(3),strcharinfo(0)+" : ここは危険です。中央ホールに行く道は解りますか？　身重な体のようですが……動けそうですか？";
		next;
		mes "[鍛冶屋デストロイヤー]";
		mes "はい、動けます。";
		mes "この子の為にも私が動かなくちゃ。";
		unittalk "鍛冶屋デストロイヤー : はい、動けます。この子の為にも私が動かなくちゃ。";
		next;
		menu "どうかご無事で",-;
		mes "["+strcharinfo(0)+"]";
		mes "無事にその子とここから";
		mes "抜け出せることを祈っています。";
		mes "共に行けなくて申し訳ありません。";
		unittalk getcharid(3),strcharinfo(0)+" : 無事にその子とここから抜け出せることを祈っています。共に行けなくて申し訳ありません。";
		next;
		mes "[鍛冶屋デストロイヤー]";
		mes "いいえ、本当に助かりました。";
		mes "ありがとうございます。";
		unittalk "鍛冶屋デストロイヤー : いいえ、本当に助かりました。ありがとうございます。";
		close2;
		hideonnpc;
		announce strcharinfo(0) +" : この付近の生存者は他には居ないようだ。今度は北側のエリアを集中的に捜索しよう。",0x9,0xffff00;
		viewpoint 0,227,216,0,0xFF0000;
		hideoffnpc getmdnpcname("#4統制");
		hideoffnpc getmdnpcname("#4統制2");
		donpcevent getmdnpcname("#4統制_mobdead")+ "::OnStart";
		end;
	}
	else {
		mes "[鍛冶屋デストロイヤー]";
		mes "あ、あれ？　人……なの？";
		mes "た、助かった。";
		mes "私以外の人はもう……。";
		mes "あなた方のおかげで助かりました。";
		mes "ありがとうございます。";
		next;
		mes "[鍛冶屋デストロイヤー]";
		mes "ところで、あなた方の代表者は";
		mes "どこにいますか？";
		mes "代表者の方とも";
		mes "お話したいのですが……。";
		close;
	}
}

1@gl_k.gat,215,216,0	script	#4ヒメルメズの囁き	139,1,1,{
	hideonnpc;
	initnpctimer;
	announce "ヒメルメズ : ここまで来るなんて、なかなかやるじゃない。",0x9,0xffff00;
	end;
OnTimer4000:
	announce "ヒメルメズ : でも、まだ足りないわ……。",0x9,0xffff00;
	end;
OnTimer8000:
	stopnpctimer;
	announce "ヒメルメズ : ふふふ、私を捕らえたいのなら、この子たちを倒してみなさい。",0x9,0xffff00;
	end;
}

1@gl_k.gat,227,216,0	warp	#4統制	2,2,1@gl_k.gat,215,216

1@gl_k.gat,202,80,0		script	#4統制_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("1@gl_k.gat");
	set '@label$,getmdnpcname("#4統制_mobdead")+"::OnKilled";
	areamonster '@map$,64,229,209,255,"腐敗した兵士",2468,26,'@label$;
	areamonster '@map$,64,229,209,255,"徘徊する弓兵",2469,30,'@label$;
	areamonster '@map$,24,192,84,225,"餓えた兵士",2468,16,'@label$;
	areamonster '@map$,24,192,55,270,"凶暴な弓兵",2469,20,'@label$;
	end;
OnKilled:
	set '@count,92 - getmapmobs(getmdmapname("1@gl_k.gat"),getmdnpcname("#4統制_mobdead")+"::OnKilled");
	if('@count >= 86) {
		initnpctimer;
	}
	end;
OnTimer1000:
	killmonster getmdmapname("1@gl_k.gat"),getmdnpcname("#4統制_mobdead")+"::OnKilled";
	announce "ヒメルメズ : なかなかやるじゃない。ここまで生き残るなんて、意外だわ。",0x9,0xffff00;
	end;
OnTimer5000:
	stopnpctimer;
	announce "ヒメルメズ : 私を捕えたいのでしょう？　2階に続く北側の大階段前まで来るといいわ。",0x9,0xffff00;
	hideoffnpc getmdnpcname("#ヒメルon");
	hideoffnpc getmdnpcname("ヒメルメズ#2");
	end;
}

1@gl_k.gat,222,216,0	warp	#4統制2	2,2,1@gl_k.gat,235,216

1@gl_k.gat,150,257,0	script	#ヒメルon	139,6,6,{
	if(OLDGLAST_QUE >= 1) {
		mes "‐大階段の前には";
		mes "　余裕の笑みを浮かべた";
		mes "　ヒメルメズがいた‐";
		next;
		if(select("急ぐ","会話をする") == 1) {
			hideonnpc;
			hideonnpc getmdnpcname("ヒメルメズ#2");
			initnpctimer;
			setnpctimer 36000;
			close;
		}
	}
	hideonnpc;
	initnpctimer;
	end;
OnTimer1000:
	donpcevent getmdnpcname("ヒメルメズ#2")+"::OnTalk1";
	end;
OnTimer6000:
	hideoffnpc getmdnpcname("ハインリヒ#4");
	hideoffnpc getmdnpcname("バルムント#2");
	donpcevent getmdnpcname("ハインリヒ#4")+"::OnTalk1";
	end;
OnTimer7000:
	donpcevent getmdnpcname("ヒメルメズ#2")+"::OnTalk2";
	end;
OnTimer10000:
	donpcevent getmdnpcname("ハインリヒ#4")+"::OnTalk2";
	end;
OnTimer15000:
	donpcevent getmdnpcname("ヒメルメズ#2")+"::OnTalk3";
	end;
OnTimer19000:
	donpcevent getmdnpcname("バルムント#2")+"::OnTalk1";
	end;
OnTimer23000:
	donpcevent getmdnpcname("ハインリヒ#4")+"::OnTalk3";
	end;
OnTimer24000:
	donpcevent getmdnpcname("ヒメルメズ#2")+"::OnTalk4";
	end;
OnTimer29000:
	donpcevent getmdnpcname("ヒメルメズ#2")+"::OnTalk5";
	end;
OnTimer32000:
	hideonnpc getmdnpcname("ヒメルメズ#2");
	end;
OnTimer33000:
	donpcevent getmdnpcname("ハインリヒ#4")+"::OnTalk4";
	end;
OnTimer35000:
	donpcevent getmdnpcname("ハインリヒ#4")+"::OnTalk5";
	end;
OnTimer37000:
	hideonnpc getmdnpcname("ハインリヒ#4");
	hideonnpc getmdnpcname("バルムント#2");
	end;
OnTimer40000:
	announce "騎士団の奥から不気味なこだまが近づいて来ます。",0x9,0xffff00;
	end;
OnTimer45000:
	donpcevent getmdnpcname("#ボス統制")+"::OnStart";
	stopnpctimer;
	end;
}

1@gl_k.gat,150,257,3	script	ヒメルメズ#2	650,{
	cutin "GL_HIMEL2",2;
	mes "[ヒメルメズ]";
	mes "そんな不安な眼で私を見つめる";
	mes "必要はないわ。";
	mes "もうすぐ楽になるのだから……。";
	close2;
	cutin "GL_HIMEL2",255;
	end;
OnTalk1:
	unittalk "ヒメルメズ : ここまで辿りつくなんて、運がいいわね。それとも、それだけの力を持っていたのかしら。";
	end;
OnTalk2:
	unittalk "ヒメルメズ : あ～ら、追いつかれちゃったわ。でも、ここまで来るのに随分苦労したみたいね～、おほほ。";
	end;
OnTalk3:
	unittalk "ヒメルメズ : うふふ、あなたの苦しむ姿……本当に、よかったわ。ん～、でもね、楽しみはまだ始まったばかりなのよ。";
	end;
OnTalk4:
	unittalk "ヒメルメズ : 私が一人で来たと思っているの？　おほほ、それじゃあ、あなたたちは私のオモチャと遊んでいなさい。";
	end;
OnTalk5:
	unittalk "ヒメルメズ : では私はこれで。ハインリヒ……あなたとはもう一度会いたいわ。また機会があれば、ね。";
	end;
}

1@gl_k.gat,144,258,6	script	ハインリヒ#4	652,{
	cutin "GL_HEINRICH1",2;
	mes "[ハインリヒ]";
	mes "ヒメルメズ……";
	mes "私の部下たちを手にかけた罪、";
	mes "絶対に許さんぞ！";
	close2;
	cutin "GL_HEINRICH1",255;
	end;
OnTalk1:
	unittalk "ハインリヒ : ヒメルメズ！　貴様、ここにいたか！";
	end;
OnTalk2:
	unittalk "ハインリヒ : よくも部下たちを……その罪、命をもって償ってもらう！";
	end;
OnTalk3:
	unittalk "ハインリヒ : こ……これは！";
	end;
OnTalk4:
	unittalk "ハインリヒ : 待て！　ヒメルメズ!!";
	end;
OnTalk5:
	unittalk "ハインリヒ : 冒険者の方も力を貸して下さい。私とバルムント卿はヒメルメズを追います！";
	end;
}

1@gl_k.gat,156,258,3	script	バルムント#2	654,{
	if(checkquest(12318) & 0x4) {
		cutin "GL_BARMUND1",2;
		mes "[バルムント]";
		mes "あの強力なモンスターを相手に";
		mes "よく無事でいてくれた。";
		next;
		mes "[バルムント]";
		mes "ヒメルメズを追って";
		mes "2階に進んだのだが、";
		mes "どうもヒメルメズに小細工を";
		mes "弄されたようだ。";
		next;
		mes "[バルムント]";
		mes "とにかく、君も急いで2階に";
		mes "来てくれ。";
		next;
		mes "[バルムント]";
		mes "それから、戦闘のあった付近で";
		mes "結晶のような物を拾っておいた。";
		mes "おそらく、モンスターが落とした";
		mes "物なのだろう。";
		next;
		mes "[バルムント]";
		mes "この結晶は不思議な気を発している。";
		mes "いつかこれを操れる人に出会ったら";
		mes "必ず君の役に立つだろう。";
		mes "持っていくと良い";
		if(checkitemblank() < 2) {
			next;
			mes "[バルムント]";
			mes "所持品の種類が多いようだな。";
			mes "所持品の種類を減らした後に";
			mes "また来なさい。";
			close;
		}
		delquest 12318;
		setquest 12319;
		getitem 6607,1;
		getitem 6608,1;
		set OLDGLAST_QUE,1;
		close2;
		cutin "GL_BARMUND1",255;
		end;
	}
	if(checkquest(12319)) {
		cutin "GL_BARMUND1",2;
		mes "[バルムント]";
		mes "すぐ北にある階段から";
		mes "2階に行くぞ。";
		mes "ふざけた態度だが、ヒメルメズは";
		mes "ヴァルキリーの一人。";
		mes "油断するなよ。";
		close2;
		cutin "GL_BARMUND1",255;
		end;
	}
	if(checkquest(12322)) {
		cutin "GL_BARMUND1",2;
		mes "[バルムント]";
		mes "……。";
		next;
		mes "^0000ff‐バルムントは時間が止まって^000000";
		mes "^0000ff　いるかのように微動だにしない‐^000000";
		close2;
		cutin "GL_BARMUND1",255;
		end;
	}
	cutin "GL_BARMUND1",2;
	mes "[バルムント]";
	mes "ふざけた態度だが、ヒメルメズは";
	mes "ヴァルキリーの一人。";
	mes "油断するなよ。";
	close2;
	cutin "GL_BARMUND1",255;
	end;
OnTalk1:
	unittalk "バルムント : ハインリヒ卿！　何か、強大な力がこちらに向かって来ています！";
	end;
OnTalk2:
	unittalk "バルムント : 大丈夫か？　こちらもちょっと問題があってな……まずは私に話しかけてくれ。";
	end;
}

1@gl_k.gat,3,1,1	script	#ボス統制	844,{
OnStart:
	monster getmdmapname("1@gl_k.gat"),150,259,"誘いの魔眼#1",2475,1,getmdnpcname("#ボス統制")+"::OnKilled";
	end;
OnKilled:
	hideoffnpc getmdnpcname("#2階入り口");
	hideoffnpc getmdnpcname("バルムント#2");
	donpcevent getmdnpcname("バルムント#2")+"::OnTalk2";
	donpcevent getmdnpcname("#22統制_mobdead")+"::OnStart";
	donpcevent getmdnpcname("#23統制_mobdead")+"::OnStart";
	end;
}

1@gl_k.gat,150,284,0	script	#2階入り口	45,2,2,{
	if(checkquest(12318) & 0x4) {
		mes "[バルムント]";
		mes "おい、どこへ行くんだ。";
		mes "まずは私に詳しい話を";
		mes "聞かせてくれないか？";
		close;
	}
	warp getmdmapname("2@gl_k.gat"),150,46;
	end;
}
1@gl_k.gat,103,203,0	warp	#秘密部屋出入り口	2,2,1@gl_k.gat,103,227

1@gl_k.gat,269,267,3	script	怪しい亀裂#1	844,{
	if(checkquest(12322)) {
		mes "‐亀裂の奥に隠し通路を";
		mes "　見つけた‐";
		close2;
		warp getmdmapname("1@gl_k.gat"),149,198;
		end;
	}
	mes "‐怪しい亀裂がある‐";
	close;
OnInit:
	initnpctimer;
	end;
OnTimer5000:
	misceffect 14;
	initnpctimer;
	end;
}

1@gl_k.gat,165,136,3	script	ガラスケース#2	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// アメジスト、凝固された魔力、豪華な鍵、金塊、重厚な大剣
	setarray '@gain,719,719,719,719,719,719,6608,6611,7228,21007;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200,   50;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,165+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,159,136,3	script	ガラスケース#3	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// アクアマリン、凝固された魔力、豪華な鍵、銀塊、精巧な鎧
	setarray '@gain,720,720,720,720,720,720,6608,6611,7229,15066;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200,   50;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,159+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,153,136,3	script	ガラスケース#4	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// エメラルド、凝固された魔力、銀塊、白金の塊、金細工の短剣
	setarray '@gain,721,721,721,721,721,721,6608,7229,7230,13086;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200,   50;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,153+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,147,136,3	script	ガラスケース#5	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// 真珠、凝固された魔力、金貨のかご、派手なブローチ
	setarray '@gain,722,722,722,722,722,722,6608,6612,6613;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,147+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,141,136,3	script	ガラスケース#6	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// サードオニキス、凝固された魔力、豪華な鍵、金塊、儀式用の剣
	setarray '@gain,725,725,725,725,725,725,6608,6611,7228,13440;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200,   50;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,141+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,135,136,3	script	ガラスケース#7	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// サファイア、凝固された魔力、銀塊、スタッフオブゲフェン
	setarray '@gain,726,726,726,726,726,726,6608,7229,2022;
	setarray '@rate,300,300,300,300,300,300,1000, 200,  50;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,135+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

1@gl_k.gat,129,136,3	script	ガラスケース#8	844,{
	if(checkquest(12322)) {
		initnpctimer;
		misceffect 234;
		hideonnpc getmdnpcname(strnpcinfo(0));
	}
	end;
OnTimer1000:
	// オパール、凝固された魔力、豪華な鍵、金塊、銀細工のブレスレット
	setarray '@gain,727,727,727,727,727,727,6608,6611,7228,2949;
	setarray '@rate,300,300,300,300,300,300,1000, 200, 200,  10;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,129+rand(5)-2;
		set '@y,136+rand(5)+2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@gl_k.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	stopnpctimer;
	end;
}

//============================================================
// 古のグラストヘイム2F
//------------------------------------------------------------
2@gl_k.gat,149,32,0	warp	#1統制	2,2,1@gl_k.gat,150,270

2@gl_k.gat,150,66,0	script	#ハインon	139,10,10,{
	if(OLDGLAST_QUE >= 2) {
		mes "‐ハインリヒとバルムントが";
		mes "　何やら話をしている‐";
		next;
		if(select("急ぐ","会話をする") == 1) {
			hideonnpc;
			hideonnpc getmdnpcname("ハインリヒ#21");
			hideonnpc getmdnpcname("バルムント#21");
			initnpctimer;
			setnpctimer 76000;
			close;
		}
	}
	hideonnpc;
	initnpctimer;
	end;
OnTimer3000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk1";
	end;
OnTimer6000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk1";
	end;
OnTimer9000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk2";
	end;
OnTimer12000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk2";
	end;
OnTimer15000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk3";
	end;
OnTimer18000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk3";
	end;
OnTimer22000:
	misceffect 90,getmdnpcname("バルムント#21");
	end;
OnTimer25000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk4";
	end;
OnTimer27000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk5";
	end;
OnTimer30000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk6";
	end;
OnTimer34000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk7";
	end;
OnTimer37000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk8";
	end;
OnTimer41000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk9";
	end;
OnTimer46000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk4";
	end;
OnTimer49000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk5";
	end;
OnTimer52000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk10";
	end;
OnTimer55000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk11";
	end;
OnTimer57000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk12";
	end;
OnTimer60000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk13";
	end;
OnTimer64000:
	donpcevent getmdnpcname("ハインリヒ#21")+"::OnTalk6";
	end;
OnTimer68000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk14";
	end;
OnTimer72000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk15";
	end;
OnTimer75000:
	donpcevent getmdnpcname("バルムント#21")+"::OnTalk16";
	end;
OnTimer78000:
	hideonnpc getmdnpcname("ハインリヒ#21");
	hideonnpc getmdnpcname("バルムント#21");
	announce "バルムント : まずは結界が壊れた西側のエリアからだ。中央通路から移動できる。",0x9,0xffff00;
	end;
OnTimer82000:
	stopnpctimer;
	announce "バルムント : 魔物を殲滅していけば、その中に結界石を持ったものがいるはずだ。",0x9,0xffff00;
	hideoffnpc getmdnpcname("#22統制");
	hideoffnpc getmdnpcname("#22統制2");
	end;
}

2@gl_k.gat,148,67,1	script	ハインリヒ#21	652,{
	cutin "GL_HEINRICH1",2;
	mes "[ハインリヒ]";
	mes "周囲がヒメルメズの結界で";
	mes "閉ざされているのか……。";
	close2;
	cutin "GL_HEINRICH1",255;
	end;
OnTalk1:
	unittalk "ハインリヒ : ……くっ、この結界は、私の剣ではどうやっても破壊できないのか……。";
	end;
OnTalk2:
	unittalk "ハインリヒ : むう……おお、冒険者の方。よくぞご無事で。";
	end;
OnTalk3:
	unittalk "ハインリヒ : 結界に邪魔され、先に進むことができないのです。";
	end;
OnTalk4:
	unittalk "ハインリヒ : そんなこと、許されるはずがないだろう！";
	end;
OnTalk5:
	unittalk "ハインリヒ : 私はすでに多くの部下をこの手にかけた。また、罪もない者を斬れというのか！";
	end;
OnTalk6:
	unittalk "ハインリヒ : ……。";
	end;
}

2@gl_k.gat,151,71,7	script	バルムント#21	654,{
	cutin "GL_BARMUND2",2;
	mes "[バルムント]";
	mes "いったい、私はこんなことを";
	mes "何度繰り返したのか……";
	mes "夢でも数十回は繰り返し見た";
	mes "場所と感覚……。";
	close2;
	cutin "GL_BARMUND2",255;
	end;
OnTalk1:
	unittalk "バルムント : ヒメルメズの結界は、物理的なダメージを受け付けないようですね。";
	end;
OnTalk2:
	unittalk "バルムント : ヒメルメズによって今通った階段の時空が歪められ、ここに出たのだが……。";
	end;
OnTalk3:
	unittalk "バルムント : 私の魔法をもう1度試してみます。ハインリヒ卿、下がってください。";
	end;
OnTalk4:
	unittalk "バルムント : 結界の一部は壊れましたが、やはりこれ以上は無理なようですね。";
	end;
OnTalk5:
	unittalk "バルムント : 実は、以前にもこのような結界を見たことがあるのですが……";
	end;
OnTalk6:
	unittalk "バルムント : その時、ヒメルメズはアンデッド化した人の中に埋め込んだ結界石で結界を維持していました。";
	end;
OnTalk7:
	unittalk "バルムント : おそらく、この結界もそうやって維持されているのでしょう。";
	end;
OnTalk8:
	unittalk "バルムント : 他の結界を壊すには彼らの中から結界石を持った者を倒すしかありません。";
	end;
OnTalk9:
	unittalk "バルムント : しかし、私たちにはそれを見分けることはできない。つまり見かけたものすべてを浄化していくしかありません……。";
	end;
OnTalk10:
	unittalk "バルムント : ハインリヒ卿……。";
	end;
OnTalk11:
	unittalk "バルムント : あなたは優し過ぎます。";
	end;
OnTalk12:
	unittalk "バルムント : 私たちが相手にする存在は、すでに人間ではありません。";
	end;
OnTalk13:
	unittalk "バルムント : 彼らが魔物である事を否定したからといって、彼らが再び人間に戻ることはありません。";
	end;
OnTalk14:
	unittalk "バルムント : 君も戦力を整えたら、私たちについてきてくれ。";
	end;
OnTalk15:
	unittalk "バルムント : 東西のエリアを探索して結界石を持った魔物を倒すぞ。";
	end;
OnTalk16:
	unittalk "バルムント : 辛い戦いになるだろうが……頼んだぞ。";
	end;
}

2@gl_k.gat,145,123,0	warp	#22統制		2,2,2@gl_k.gat,126,123
2@gl_k.gat,136,122,0	warp	#22統制2	2,2,2@gl_k.gat,150,116

2@gl_k.gat,118,141,0	script	#2-1	139,5,5,{
OnStart:
OnTouch:
	setarray 'x[1],116,126,129, 87, 62, 60, 36;
	setarray 'y[1],139, 79, 52, 46,115, 80,136;
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@id,substr(strnpcinfo(2),2,3);
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"腐敗した兵士",2468,1,getmdnpcname("#22統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"徘徊する弓兵",2469,1,getmdnpcname("#22統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"堕ちた白の騎士",2470,1,getmdnpcname("#22統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"怨念のカーリッツバーグ",2471,1,getmdnpcname("#22統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"呪われた騎士",2472,1,getmdnpcname("#22統制_mobdead")+"::OnKilled"+'@id;
	hideonnpc;
	end;
}

2@gl_k.gat,128,81,0	duplicate(#2-1)	#2-2	139,5,5
2@gl_k.gat,131,54,0	duplicate(#2-1)	#2-3	139,5,5
2@gl_k.gat,89,48,0	duplicate(#2-1)	#2-4	139,5,5
2@gl_k.gat,64,117,0	duplicate(#2-1)	#2-5	139,5,5
2@gl_k.gat,62,82,0	duplicate(#2-1)	#2-6	139,5,5
2@gl_k.gat,38,138,0	duplicate(#2-1)	#2-7	139,5,5

2@gl_k.gat,1,1,0	script	#22統制_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@label$,getmdnpcname("#22統制_mobdead")+"::OnKilled";
	setarray 'x[1],116,126,129, 87, 62, 60, 36;
	setarray 'y[1],139, 79, 52, 46,115, 80,136;
	areamonster '@map$,31,20,124,162,"腐敗した兵士",2468,8,'@label$;
	areamonster '@map$,31,20,124,162,"徘徊する弓兵",2469,8,'@label$;
	areamonster '@map$,31,20,124,162,"堕ちた白の騎士",2470,8,'@label$;
	areamonster '@map$,31,20,124,162,"怨念のカーリッツバーグ",2471,8,'@label$;
	areamonster '@map$,31,20,124,162,"呪われた騎士",2472,8,'@label$;
	for(set '@i,1; '@i<=7; set '@i,'@i+1)
		donpcevent getmdnpcname("#2-"+'@i)+"::OnStart";
	end;
OnKilled:
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@label$,getmdnpcname("#22統制_mobdead")+"::OnKilled";
	switch(rand(5)) {
	case 0: areamonster '@map$,31,20,124,162,"腐敗した兵士",2468,1,'@label$; break;
	case 1: areamonster '@map$,31,20,124,162,"徘徊する弓兵",2469,1,'@label$; break;
	case 2: areamonster '@map$,31,20,124,162,"堕ちた白の騎士",2470,1,'@label$; break;
	case 3: areamonster '@map$,31,20,124,162,"怨念のカーリッツバーグ",2471,1,'@label$; break;
	case 4: areamonster '@map$,31,20,124,162,"呪われた騎士",2472,1,'@label$; break;
	}
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled1");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x1)) {
		set 'area,'area|0x1;
		hideoffnpc getmdnpcname("#2-1");
	}
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled2");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x2)) {
		set 'area,'area|0x2;
		hideoffnpc getmdnpcname("#2-2");
	}
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled3");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x4)) {
		set 'area,'area|0x4;
		hideoffnpc getmdnpcname("#2-3");
	}
	end;
OnKilled4:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled4");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x8)) {
		set 'area,'area|0x8;
		hideoffnpc getmdnpcname("#2-4");
	}
	end;
OnKilled5:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled5");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x10)) {
		set 'area,'area|0x10;
		hideoffnpc getmdnpcname("#2-5");
	}
	end;
OnKilled6:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled6");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x20)) {
		set 'area,'area|0x20;
		hideoffnpc getmdnpcname("#2-6");
	}
	end;
OnKilled7:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#22統制_mobdead")+"::OnKilled7");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x40)) {
		set 'area,'area|0x40;
		hideoffnpc getmdnpcname("#2-7");
	}
	end;
OnTimer1000:
	stopnpctimer;
	if('spawn)
		end;
	set 'spawn,1;

	set '@r,rand(1,7);
	areamonster getmdmapname("2@gl_k.gat"),'x['@r],'y['@r],'x['@r]+5,'y['@r]+5,"苦痛のロイヤルナイト",2473,1,getmdnpcname("#22統制_mobdead")+"::OnKilled8";
	announce "バルムント : この邪悪な気は……！　強大な力を持った魔物が近くにいるぞ！",0x9,0xffff44,0x190,15;
	end;
OnKilled8:
	hideonnpc;
	hideoffnpc getmdnpcname("#23統制");
	hideoffnpc getmdnpcname("#23統制2");
	announce "バルムント : よし、東側の結界が壊れたようだ。中央通路から東側のエリアに移動するぞ。",0x9,0xffff00;
	end;
}

2@gl_k.gat,154,101,0	warp	#23統制		2,2,2@gl_k.gat,174,101
2@gl_k.gat,165,101,0	warp	#23統制2	2,2,2@gl_k.gat,150,111

2@gl_k.gat,171,120,0	script	#3-1	139,5,5,{
OnStart:
OnTouch:
	setarray 'x[1],169,230,254,210,241,227,179;
	setarray 'y[1],118,131,147,104, 71, 24, 32;
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@id,substr(strnpcinfo(2),2,3);
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"腐敗した兵士",2468,1,getmdnpcname("#23統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"徘徊する弓兵",2469,1,getmdnpcname("#23統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"堕ちた白の騎士",2470,1,getmdnpcname("#23統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"怨念のカーリッツバーグ",2471,1,getmdnpcname("#23統制_mobdead")+"::OnKilled"+'@id;
	areamonster '@map$,'x['@id],'y['@id],'x['@id]+5,'y['@id]+5,"呪われた騎士",2472,1,getmdnpcname("#23統制_mobdead")+"::OnKilled"+'@id;
	hideonnpc;
	end;
}

2@gl_k.gat,232,133,0	duplicate(#3-1)	#3-2	139,5,5
2@gl_k.gat,256,149,0	duplicate(#3-1)	#3-3	139,5,5
2@gl_k.gat,212,106,0	duplicate(#3-1)	#3-4	139,5,5
2@gl_k.gat,243,73,0		duplicate(#3-1)	#3-5	139,5,5
2@gl_k.gat,229,26,0		duplicate(#3-1)	#3-6	139,5,5
2@gl_k.gat,181,34,0		duplicate(#3-1)	#3-7	139,5,5

2@gl_k.gat,2,1,0	script	#23統制_mobdead	139,{
OnStart:
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@label$,getmdnpcname("#23統制_mobdead")+"::OnKilled";
	setarray 'x[1],169,230,254,210,241,227,179;
	setarray 'y[1],118,131,147,104, 71, 24, 32;
	areamonster '@map$,175,18,265,163,"腐敗した兵士",2468,8,'@label$;
	areamonster '@map$,175,18,265,163,"徘徊する弓兵",2469,8,'@label$;
	areamonster '@map$,175,18,265,163,"堕ちた白の騎士",2470,8,'@label$;
	areamonster '@map$,175,18,265,163,"怨念のカーリッツバーグ",2471,8,'@label$;
	areamonster '@map$,175,18,265,163,"呪われた騎士",2472,8,'@label$;
	for(set '@i,1; '@i<=7; set '@i,'@i+1)
		donpcevent getmdnpcname("#3-"+'@i)+"::OnStart";
	end;
OnKilled:
	if('spawn)
		end;
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@label$,getmdnpcname("#23統制_mobdead")+"::OnKilled";
	switch(rand(5)) {
	case 0: areamonster '@map$,175,18,265,163,"腐敗した兵士",2468,1,'@label$; break;
	case 1: areamonster '@map$,175,18,265,163,"徘徊する弓兵",2469,1,'@label$; break;
	case 2: areamonster '@map$,175,18,265,163,"堕ちた白の騎士",2470,1,'@label$; break;
	case 3: areamonster '@map$,175,18,265,163,"怨念のカーリッツバーグ",2471,1,'@label$; break;
	case 4: areamonster '@map$,175,18,265,163,"呪われた騎士",2472,1,'@label$; break;
	}
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled1");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x1)) {
		set 'area,'area|0x1;
		hideoffnpc getmdnpcname("#3-1");
	}
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled2");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x2)) {
		set 'area,'area|0x2;
		hideoffnpc getmdnpcname("#3-2");
	}
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled3");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x4)) {
		set 'area,'area|0x4;
		hideoffnpc getmdnpcname("#3-3");
	}
	end;
OnKilled4:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled4");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x8)) {
		set 'area,'area|0x8;
		hideoffnpc getmdnpcname("#3-4");
	}
	end;
OnKilled5:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled5");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x10)) {
		set 'area,'area|0x10;
		hideoffnpc getmdnpcname("#3-5");
	}
	end;
OnKilled6:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled6");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x20)) {
		set 'area,'area|0x20;
		hideoffnpc getmdnpcname("#3-6");
	}
	end;
OnKilled7:
	set '@count,getmapmobs(getmdmapname("2@gl_k.gat"),getmdnpcname("#23統制_mobdead")+"::OnKilled7");
	set 'flag,'flag+1;
	if(!rand(35) || 'flag >= 35)
		initnpctimer;
	if('@count <= 0 && !('area&0x40)) {
		set 'area,'area|0x40;
		hideoffnpc getmdnpcname("#3-7");
	}
	end;
OnTimer1000:
	stopnpctimer;
	if('spawn)
		end;
	set 'spawn,1;

	set '@r,rand(1,7);
	areamonster getmdmapname("2@gl_k.gat"),'x['@r],'y['@r],'x['@r]+5,'y['@r]+5,"呪われたロイヤルナイト",2474,1,getmdnpcname("#23統制_mobdead")+"::OnKilled8";
	announce "バルムント : この邪悪な気は……！　強大な力を持った魔物が近くにいるぞ！",0x9,0xffff44,0x190,15;
	end;
OnKilled8:
	hideoffnpc getmdnpcname("#24統制");
	hideoffnpc getmdnpcname("#24統制2");
	announce "バルムント : よし、すべての結界が壊れたようだ。中央通路から奥に進むぞ！",0x9,0xffff00;
	end;
}

2@gl_k.gat,153,214,3	script	腐敗した死体#20	849,5,5,{
	if(sc_ison(4) || sc_ison(5) || sc_ison(119) || sc_ison(402) || sc_ison(438))
		end;
	set '@num,rand(3,7);
	set '@dummy,getmapxy('@map$,'@x,'@y,1);
	misceffect 124;
	hideonnpc;
	initnpctimer;
	killmonster getmdmapname("2@gl_k.gat"),getmdnpcname(strnpcinfo(0))+"::OnKilled";
	monster '@map$,'@x,'@y,"マゴット",2467,'@num,getmdnpcname(strnpcinfo(0))+"::OnKilled";
	end;
OnTimer60000:
	stopnpctimer;
	hideoffnpc;
	end;
}

2@gl_k.gat,155,195,4	duplicate(腐敗した死体#20)	腐敗した死体#21	849,5,5
2@gl_k.gat,154,188,2	duplicate(腐敗した死体#20)	腐敗した死体#22	849,5,5
2@gl_k.gat,143,195,5	duplicate(腐敗した死体#20)	腐敗した死体#23	849,5,5
2@gl_k.gat,132,214,4	duplicate(腐敗した死体#20)	腐敗した死体#24	849,5,5
2@gl_k.gat,125,208,2	duplicate(腐敗した死体#20)	腐敗した死体#25	849,5,5
2@gl_k.gat,114,210,3	duplicate(腐敗した死体#20)	腐敗した死体#26	849,5,5
2@gl_k.gat,137,182,6	duplicate(腐敗した死体#20)	腐敗した死体#27	849,5,5
2@gl_k.gat,138,246,8	duplicate(腐敗した死体#20)	腐敗した死体#28	849,5,5
2@gl_k.gat,132,260,7	duplicate(腐敗した死体#20)	腐敗した死体#29	849,5,5
2@gl_k.gat,128,251,1	duplicate(腐敗した死体#20)	腐敗した死体#30	849,5,5
2@gl_k.gat,179,260,3	duplicate(腐敗した死体#20)	腐敗した死体#31	849,5,5
2@gl_k.gat,170,261,4	duplicate(腐敗した死体#20)	腐敗した死体#32	849,5,5
2@gl_k.gat,177,219,2	duplicate(腐敗した死体#20)	腐敗した死体#33	849,5,5
2@gl_k.gat,190,214,5	duplicate(腐敗した死体#20)	腐敗した死体#34	849,5,5
2@gl_k.gat,201,214,4	duplicate(腐敗した死体#20)	腐敗した死体#35	849,5,5
2@gl_k.gat,143,260,4	duplicate(腐敗した死体#20)	腐敗した死体#1	849,5,5
2@gl_k.gat,145,236,4	duplicate(腐敗した死体#20)	腐敗した死体#2	849,5,5
2@gl_k.gat,141,222,2	duplicate(腐敗した死体#20)	腐敗した死体#3	849,5,5
2@gl_k.gat,147,203,5	duplicate(腐敗した死体#20)	腐敗した死体#4	849,5,5
2@gl_k.gat,167,225,4	duplicate(腐敗した死体#20)	腐敗した死体#5	849,5,5
2@gl_k.gat,172,233,2	duplicate(腐敗した死体#20)	腐敗した死体#6	849,5,5
2@gl_k.gat,176,244,3	duplicate(腐敗した死体#20)	腐敗した死体#7	849,5,5
2@gl_k.gat,184,248,6	duplicate(腐敗した死体#20)	腐敗した死体#8	849,5,5
2@gl_k.gat,193,228,8	duplicate(腐敗した死体#20)	腐敗した死体#9	849,5,5
2@gl_k.gat,206,250,7	duplicate(腐敗した死体#20)	腐敗した死体#10	849,5,5
2@gl_k.gat,130,249,1	duplicate(腐敗した死体#20)	腐敗した死体#11	849,5,5
2@gl_k.gat,122,236,5	duplicate(腐敗した死体#20)	腐敗した死体#12	849,5,5
2@gl_k.gat,130,228,7	duplicate(腐敗した死体#20)	腐敗した死体#13	849,5,5
2@gl_k.gat,106,226,8	duplicate(腐敗した死体#20)	腐敗した死体#14	849,5,5
2@gl_k.gat,104,245,8	duplicate(腐敗した死体#20)	腐敗した死体#15	849,5,5
2@gl_k.gat,131,187,8	duplicate(腐敗した死体#20)	腐敗した死体#16	849,5,5
2@gl_k.gat,121,197,8	duplicate(腐敗した死体#20)	腐敗した死体#17	849,5,5
2@gl_k.gat,107,194,8	duplicate(腐敗した死体#20)	腐敗した死体#18	849,5,5
2@gl_k.gat,92,187,8		duplicate(腐敗した死体#20)	腐敗した死体#19	849,5,5

2@gl_k.gat,150,163,0	warp	#24統制		2,2,2@gl_k.gat,150,179
2@gl_k.gat,150,167,0	warp	#24統制2	2,2,2@gl_k.gat,150,149

2@gl_k.gat,150,180,0	script	#ゲルon	139,1,1,{
	hideonnpc;
	announce "？？？ : 来ないで下さい！　周囲に罠が……うっ！",0x9,0xff7777;
	set '@map$,getmdmapname("2@gl_k.gat");
	monster '@map$,70,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,90,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,110,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,37,265,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,57,265,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,77,265,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,97,265,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,117,265,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,88,214,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";

	monster '@map$,170,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,190,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,210,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,230,172,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,188,264,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,208,264,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,220,219,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	monster '@map$,240,219,"破滅の火花",2337,1,getmdnpcname("#ゲルon")+ "::OnKilled";
	end;
}

2@gl_k.gat,158,252,1	script	ヒメルメズ#22	650,3,3,{
	if(OLDGLAST_QUE >= 2) {
		mes "‐ハインリヒ達と共に";
		mes "　ヒメルメズに追いついた‐";
		next;
		if(select("急ぐ","会話をする") == 1) {
			hideonnpc;
			hideonnpc getmdnpcname("ハインリヒ#23");
			hideonnpc getmdnpcname("バルムント#23");
			initnpctimer;
			setnpctimer 88000;
			close;
		}
	}
	hideonnpc getmdnpcname("ヒメルメズ#22");
	hideoffnpc getmdnpcname("ヒメルメズ#23");
	initnpctimer;
	end;
OnTimer1000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk1";
	end;
OnTimer3000:
	donpcevent getmdnpcname("ゲルハルト#23")+"::OnTalk1";
	end;
OnTimer7000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk1";
	end;
OnTimer10000:
	donpcevent getmdnpcname("ゲルハルト#23")+"::OnTalk2";
	end;
OnTimer13000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk2";
	end;
OnTimer16000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk2";
	end;
OnTimer19000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk3";
	end;
OnTimer23000:
	donpcevent getmdnpcname("ゲルハルト#23")+"::OnTalk3";
	end;
OnTimer28000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk4";
	end;
OnTimer34000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk3";
	end;
OnTimer38000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk4";
	end;
OnTimer42000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk5";
	end;
OnTimer46000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk6";
	end;
OnTimer49000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk7";
	end;
OnTimer51000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk8";
	end;
OnTimer55000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk5";
	end;
OnTimer57000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk9";
	end;
OnTimer60000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk10";
	end;
OnTimer65000:
	donpcevent getmdnpcname("ヒメルメズ#23")+"::OnTalk11";
	end;
OnTimer67000:
	misceffect 63,getmdnpcname("ゲルハルト#23");
	end;
OnTimer69000:
	misceffect 231,getmdnpcname("ゲルハルト#23");
	end;
OnTimer71000:
	misceffect 247,getmdnpcname("ゲルハルト#23");
	end;
OnTimer73000:
	hideonnpc getmdnpcname("ヒメルメズ#23");
	misceffect 273,getmdnpcname("ゲルハルト#23");
	end;
OnTimer75000:
	donpcevent getmdnpcname("ハインリヒ#23")+"::OnTalk6";
	end;
OnTimer78000:
	hideonnpc getmdnpcname("ハインリヒ#23");
	donpcevent getmdnpcname("バルムント#23")+"::OnTalk1";
	end;
OnTimer80000:
	misceffect 231,getmdnpcname("ゲルハルト#23");
	misceffect 247,getmdnpcname("ゲルハルト#23");
	end;
OnTimer81000:
	announce "ゲルハルトの体が変わっていく……!!",0x9,0xffffff;
	end;
OnTimer84000:
	hideonnpc getmdnpcname("バルムント#23");
	announce "バルムント : 私の幻影たちにも戦闘を手伝わせる。　幻影の指示に従うんだ。",0x9,0xffff00,0x190,15;
	misceffect 90,getmdnpcname("ゲルハルト#23");
	end;
OnTimer87000:
	stopnpctimer;
	hideonnpc getmdnpcname("ゲルハルト#23");
	donpcevent getmdnpcname("#アムダ統制")+"::OnStart";
	donpcevent getmdnpcname("#2ボス統制")+"::OnStart";
	end;
OnTimer90000:
	announce "ゲルハルトの体が変わっていく……!!",0x9,0xffffff;
	end;
OnTimer93000:
	misceffect 90,getmdnpcname("ゲルハルト#23");
	end;
OnTimer96000:
	stopnpctimer;
	hideonnpc getmdnpcname("ゲルハルト#23");
	donpcevent getmdnpcname("#アムダ統制")+"::OnStart";
	donpcevent getmdnpcname("#2ボス統制")+"::OnStart";
	end;
}

2@gl_k.gat,153,250,8	script	ハインリヒ#23	652,{
	cutin "GL_HEINRICH1",2;
	mes "[ハインリヒ]";
	mes "何を企んでいるのだ、ヒメルメズ！";
	close2;
	cutin "GL_HEINRICH1",255;
	end;
OnTalk1:
	unittalk "ハインリヒ : ゲルハルト!";
	end;
OnTalk2:
	unittalk "ハインリヒ : ゲルハルトに何をした！　ヒメルメズ！";
	end;
OnTalk3:
	unittalk "ハインリヒ : ヒメルメズ！　ユミルの心臓の欠片を見つけたならば、もうここに用は無いはずだ！";
	end;
OnTalk4:
	unittalk "ハインリヒ : ゲルハルトを離せ！　これ以上の犠牲は必要ないだろう！";
	end;
OnTalk5:
	unittalk "ハインリヒ : ヒメルメズ！　貴様、絶対に許さんぞ！";
	end;
OnTalk6:
	unittalk "ハインリヒ : このまま逃がすとでも思っているのか！　ヒメルメズ!!";
	end;
}

2@gl_k.gat,162,250,1	script	バルムント#23	654,{
	cutin "GL_BARMUND2",2;
	mes "[バルムント]";
	mes "この拘束からは永遠に";
	mes "抜け出す事はできないのだろうか……。";
	close2;
	cutin "GL_BARMUND2",255;
	end;
OnTalk1:
	unittalk "バルムント : ハインリヒ卿！　……仕方ない、残った私たちだけでアムダライスを止めなければ！";
	end;
}

2@gl_k.gat,158,255,1	script	ゲルハルト#23	651,{
	mes "[ゲルハルト]";
	mes "うう……くっ！";
	mes "司令官を連れて……";
	mes "早くここから逃げて下さい！";
	close;
OnTalk1:
	unittalk "ゲルハルト : くっ！　逃げて下さい！　これ以上は耐えられません！";
	end;
OnTalk2:
	unittalk "ゲルハルト : 司令官……急いでここから逃げ……。";
	end;
OnTalk3:
	unittalk "ゲルハルト : どれほど私の体を汚そうとも、私の魂まで汚せると思うなよ！　ヒメルメズ！";
	end;
}

2@gl_k.gat,158,252,4	script	ヒメルメズ#23	650,{
	cutin "GL_HIMEL2",2;
	mes "[ヒメルメズ]";
	mes "素晴らしいわ、ここまで来るなんて。";
	mes "敬意を払わないといけないわね。";
	close2;
	cutin "GL_HIMEL2",255;
	end;
OnTalk1:
	unittalk "ヒメルメズ : 素晴らしい！　ここまで来れるとは思っていなかったわ。";
	end;
OnTalk2:
	unittalk "ヒメルメズ : ふふふ、ユミルの心臓の欠片はすでに見つけたわよ。ハインリヒ。";
	end;
OnTalk3:
	unittalk "ヒメルメズ : 彼の邪魔さえなければもっと早かったのだけれど。";
	end;
OnTalk4:
	unittalk "ヒメルメズ : 本当にそう思っているの？　口が達者なのは王も兵士も変わらないのね……。";
	end;
OnTalk5:
	unittalk "ヒメルメズ : 嫌よ。";
	end;
OnTalk6:
	unittalk "ヒメルメズ : 彼が最後の部下なんでしょう？";
	end;
OnTalk7:
	unittalk "ヒメルメズ : 彼、かなりの腕前だったわ。";
	end;
OnTalk8:
	unittalk "ヒメルメズ : 私の新しいアムダライスの素体にぴったりな程にね。";
	end;
OnTalk9:
	unittalk "ヒメルメズ : あ～ら怖い。";
	end;
OnTalk10:
	unittalk "ヒメルメズ : まあ、あなたとはもう少し話したいこともあるし、次の機会にまた会いましょう。";
	end;
OnTalk11:
	unittalk "ヒメルメズ : けど、今は生まれ変わった部下とお喋りでもしていなさい。";
	end;
}

2@gl_k.gat,150,247,5	script	バルムントの幻影#バフ1::バルムントの幻影#1	654,3,3,{
	end;
OnTouch:
	sc_start SC_GLASTHEIM_STATE,30000,25;		//SI_GLASTHEIM_STATE
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	unittalk "バルムントの幻影 : アムダライスが強力な魔法を使用するぞ！　私の近くまで下がれ！";
	end;
OnTimer12000:
	stopnpctimer;
	hideonnpc;
	end;
}

2@gl_k.gat,165,247,3	script	バルムントの幻影#バフ2::バルムントの幻影#2	654,3,3,{
	end;
OnTouch:
	sc_start SC_GLASTHEIM_STATE,30000,25;		//SI_GLASTHEIM_STATE
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	unittalk "バルムントの幻影 : 今は攻撃のチャンスだ！　私の近くに来て強化を受けるんだ！";
	end;
OnTimer12000:
	stopnpctimer;
	hideonnpc;
	end;
}

2@gl_k.gat,150,232,8	script	バルムントの幻影#バフ3::バルムントの幻影#3	654,3,3,{
	end;
OnTouch:
	sc_start SC_GLASTHEIM_STATE,30000,25;		//SI_GLASTHEIM_STATE
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	unittalk "バルムントの幻影 : アムダライスの召喚した魔物にやられる前に、私の近くに来て態勢を立て直すんだ！";
	end;
OnTimer12000:
	stopnpctimer;
	hideonnpc;
	end;
}

2@gl_k.gat,165,232,2	script	バルムントの幻影#バフ4::バルムントの幻影#4	654,3,3,{
	end;
OnTouch:
	sc_start SC_GLASTHEIM_STATE,30000,25;		//SI_GLASTHEIM_STATE
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	unittalk "バルムントの幻影 : アムダライスの力にやられたくなければ、私の近くで補助を受けるんだ！";
	end;
OnTimer12000:
	stopnpctimer;
	hideonnpc;
	end;
}

2@gl_k.gat,3,1,0	script	#2ボス統制	844,{
OnStart:
	initnpctimer;
	end;
OnTimer32000:
	set '@map$,getmdmapname("2@gl_k.gat");
	set '@label$,getmdnpcname("#2ボス統制")+"::OnKilled";
	donpcevent getmdnpcname("#アムダ統制")+"::OnCasting";
	donpcevent getmdnpcname("#2ボス統制_bc")+"::OnStart";
	if(rand(2))
		areamonster '@map$,150,232,165,247,"#ダーク",2495,rand(2,5),'@label$;
	switch(rand(4)) {
	case 0:
		areamonster '@map$,150,232,165,247,"腐敗した兵士",2468,1,'@label$;
		areamonster '@map$,150,232,165,247,"徘徊する弓兵",2469,1,'@label$;
		areamonster '@map$,150,232,165,247,"堕ちた白の騎士",2470,1,'@label$;
		areamonster '@map$,150,232,165,247,"怨念のカーリッツバーグ",2471,1,'@label$;
		areamonster '@map$,150,232,165,247,"呪われた騎士",2472,1,'@label$;
		break;
	case 1:
		areamonster '@map$,150,232,165,247,"腐敗した兵士",2468,rand(2,5),'@label$;
		break;
	case 2:
		areamonster '@map$,150,232,165,247,"徘徊する弓兵",2469,rand(2,5),'@label$;
		break;
	case 3:
		areamonster '@map$,150,232,165,247,"堕ちた白の騎士",2470,rand(2,5),'@label$;
		break;
	case 4:
		areamonster '@map$,150,232,165,247,"怨念のカーリッツバーグ",2471,rand(2,5),'@label$;
		break;
	case 5:
		areamonster '@map$,150,232,165,247,"呪われた騎士",2472,rand(2,5),'@label$;
		break;
	}
	end;
OnTimer62000:
	killmonster getmdmapname("2@gl_k.gat"),getmdnpcname("#2ボス統制")+"::OnKilled";
	initnpctimer;
	end;
OnKilled:
	end;
}

2@gl_k.gat,4,1,0	script	#2ボス統制_bc	844,{
OnStart:
	if(rand(2)) {
		donpcevent getmdnpcname("バルムントの幻影#2")+"::OnStart";
		donpcevent getmdnpcname("バルムントの幻影#3")+"::OnStart";
	}
	else {
		donpcevent getmdnpcname("バルムントの幻影#1")+"::OnStart";
		donpcevent getmdnpcname("バルムントの幻影#4")+"::OnStart";
	}
	end;
}

2@gl_k.gat,5,1,0	script	#アムダ統制	844,{
OnStart:
	set 'mob,callmonster(getmdmapname("2@gl_k.gat"),158,255,"アムダライス#1",2476,getmdnpcname("#アムダ統制")+"::OnKilled");
	set 'maxhp,getmobhp('mob);
	end;
OnCasting:
	set '@hp,getmobhp('mob) / 'maxhp * 100;
	if('@hp < 20) {
		announce "バルムントの幻影 : やつの体力は残りわずかだ！　最後まで油断するな！",0x9,0x70dbdb;
	} else if('@hp < 50) {
		announce "バルムントの幻影 : いいぞ！　やつはだいぶ弱ってきているぞ！",0x9,0x70dbdb;
	} else if('@hp < 70) {
		announce "バルムントの幻影 : 少し動きが鈍ったようだ、この調子でいくぞ！",0x9,0x70dbdb;
	} else {
		announce "バルムントの幻影 : まだまだやつには余裕がありそうだ。気をつけろ！",0x9,0x70dbdb;
	}
	end;
OnKilled:
	killmonster getmdmapname("2@gl_k.gat"),getmdnpcname("#ゲルon")+"::OnKilled";
	hideoffnpc getmdnpcname("フギン#21");
	hideoffnpc getmdnpcname("怪しい亀裂#1");
	for(set '@i,1; '@i<=35; set '@i,'@i+1)
		hideonnpc getmdnpcname("腐敗した死体#"+'@i);
	end;
}

2@gl_k.gat,158,241,1	script	フギン#21	755,{
	if(checkquest(12319)) {
		if(checkquest(12319) & 0x4) {
			if(checkitemblank() < 2) {
				mes "[フギン]";
				mes "渡したい物があったが、";
				mes "荷物が溢れそうだな。";
				mes "持ち物の種類を減らしてから";
				mes "もう一度話しかけてくれ。";
				close;
			}
			if(!(checkquest(12321) & 0x8)) {
				delquest 12319;
				setquest 12322;
				mes "[フギン]";
				mes "初めてにしては";
				mes "良くやってくれたね。";
				mes "今回のお礼ははずもう。";
				mes "君はこれからも";
				mes "役に立ちそうだからね。";
				mes "受け取ってくれ。";
				setquest 12321;
				compquest 12321;
				getitem 6607,5;
				getitem 6608,5;
				getexp 350000,0;
				getexp 0,250000;
				set OLDGLAST_QUE,2;
			}
			else {
				delquest 12319;
				setquest 12322;
				mes "[フギン]";
				mes "よくやってくれた。";
				mes "期待した通りだ。";
				mes "これはお礼だ。";
				mes "受け取ってくれ。";
				getitem 6607,1;
				getitem 6608,1;
				set OLDGLAST_QUE,2;
			}
		}
		else {
			mes "[フギン]";
			mes "おや、苦戦したようだね。";
			mes "私にとっては十分な結果だが。";
			next;
			mes "[フギン]";
			mes "バルムントの時間は私が止めた。";
			mes "あの哀れな時間の旅人は、";
			mes "永遠にこのグラストヘイムの悲劇を";
			mes "止めようとするだろう。";
			next;
			mes "[フギン]";
			mes "だが、我々時間の注視者は";
			mes "彼の行動を監視し続ける。";
			mes "これからも永遠に……";
			next;
			mes "[フギン]";
			mes "それから君の記憶も消させてもらう。";
			mes "次に私に会ったとしても、";
			mes "何も覚えてはいないだろう。";
			next;
			mes "[フギン]";
			mes "また私のために";
			mes "働いてくれることを";
			mes "期待しているよ。";
			mes "ふふふ……";
			delquest 12319;
			//setquest 72955;
			//compquest 72955;
			close;
		}
		next;
		mes "[フギン]";
		mes "バルムントの時間は私が止めた。";
		mes "あの哀れな時間の旅人は、";
		mes "永遠にこのグラストヘイムの悲劇を";
		mes "止めようとするだろう。";
		next;
		mes "[フギン]";
		mes "だが、我々時間の注視者は";
		mes "彼の行動を監視し続ける。";
		mes "これからも永遠に……";
		next;
		mes "[フギン]";
		mes "それから君の記憶も消させてもらう。";
		mes "次に私に会ったとしても、";
		mes "何も覚えてはいないだろう。";
		next;
		mes "[フギン]";
		mes "また私のために";
		mes "働いてくれることを";
		mes "期待しているよ。";
		mes "ふふふ……";
		next;
		mes "[フギン]";
		mes "もし、記憶が残っていたら";
		mes "^FF00001階の庭園を調べてみるといい。^000000";
		mes "……覚えていられればな。";
		misceffect 134,"";
		close2;
		warp getmdmapname("2@gl_k.gat"),159,245;
		end;
	}
	mes "[フギン]";
	mes "もうすぐ時間の狭間が歪曲され";
	mes "ここは崩れてしまう！";
	mes "急いでここから出なければ。";
	mes "早くこっちに来てくれ！";
	next;
	menu "前に会ったことがある気がする……",-;
	mes "[フギン]";
	mes "……いや、君とは初対面のはずだ。";
	mes "そんなことより、";
	mes "もうすぐ時間の狭間が閉ざされる。";
	mes "急いでここから出るぞ。";
	next;
	if(select("もう少しここを見回ってから行きます","外に出して下さい") == 1) {
		mes "[フギン]";
		mes "そうか？";
		mes "ここはもうすぐ崩れる、";
		mes "急いでくれ。";
		close;
	}
	mes "[フギン]";
	mes "急ぐぞ。";
	close2;
	warp "glast_01.gat",204,270;
	end;
}
