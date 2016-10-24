//==============================================================================
// Ragnarok Online Whiteday2006 Script     by Blaze
//==============================================================================
alberta.gat,26,243,3	script	ショコラ=バシニオ	96,{
	if((Weight*100/Maxweight) >= 90) {
		mes "-所持アイテムの重量が多いため";
		mes "アイテムを受けとることができません-";
		mes "-所持アイテムを減らしてから、再度";
		mes "話しかけてください-";
		close;
	}
	switch(QUEST_WHITEDAY) {
	case 0:
		mes "[ショコラ=バシニオ]";
		mes "こんにちは～！";
		mes "真心と愛で恋人たちのための";
		mes "チョコレートを作るショコラです。";
		next;
		if(select("チョコレートはありますか？","何か良いことでもあったんですか？")==2) {
			mes "[ショコラ=バシニオ]";
			mes "良いことですって!?";
			mes "あははははは……";
			mes "ふふふふふ……";
			mes "あっはははは……";
			mes "はぁ……";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（何か悪いことでもあったのかな？）";
			mes "ところでチョコレートは";
			mes "ありますか？";
			next;
		}
		mes "[ショコラ=バシニオ]";
		mes "ごめんなさい。";
		mes "今チョコレートは無いんです。";
		mes "バレンタインのときは";
		mes "カカオが足りなくて大変でしたし";
		mes "今度は泥棒が……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "泥棒？";
		mes "何があったんですか？";
		next;
		mes "[ショコラ=バシニオ]";
		mes "泥棒なのかどうか";
		mes "私にも良く分からないのです。";
		mes "売る分を作り置きしておくと、";
		mes "次の日には必ず";
		mes "どこかに消えてしまうんですよ。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "それと、不思議なことに";
		mes "部屋に誰かが入ってきた";
		mes "形跡がないのです。";
		mes "ちょっと目を離した隙に、";
		mes "消えてしまうこともあるのですよ。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "誰かが変な魔法とかを";
		mes "かけているのかもしれません……";
		mes "なので、今は商売が出来ないんです。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "ううぅ……";
		mes "作っては消え、作っては消え……";
		mes "本当に不思議です……";
		mes "もう、本当に商売を止めてしまおうと";
		mes "思っていたところでした。";
		next;
		mes "[ショコラ=バシニオ]";
		mes "ははは……";
		mes "本当に申し訳ないのですけど";
		mes "今日はお引取りください……";
		set QUEST_WHITEDAY,1;
		close;
	case 1:
		mes "[ショコラ=バシニオ]";
		mes "ううっ……";
		mes "チョコレートを作っているだけですのに";
		mes "誰だかわからないですけど";
		mes "本当に酷いですよね……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "それに、チョコレートを作れなければ";
		mes "プロンテラのアルルさんも";
		mes "困ってしまうはずです……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "こうなったら、材料がなくなるまで";
		mes "とことん作ってさしあげますわ!!";
		mes "……";
		mes "うううっ……";
		mes "先ほど作ったばかりのチョコレートが";
		mes "なくなってました……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "あ！　そうだ！";
		mes "もし、よろしければ";
		mes "今作ったチョコレートを";
		mes "プロンテラのアルルさんに";
		mes "届けていただけませんか？";
		next;
		mes "[ショコラ=バシニオ]";
		mes "盗まれてしまう前に、";
		mes "アルルさんにお届けしたいのです。";
		mes "お願いします……";
		next;
		if(select("いいですよ","うーん、今は忙しい")==2) {
			mes "[ショコラ=バシニオ]";
			mes "ううぅ……";
			mes "でも、忙しいのでしたら";
			mes "仕方ないですね……";
			close;
		}
		mes "[ショコラ=バシニオ]";
		mes "ありがとうございます！";
		mes "アルルさんには";
		mes "迷惑をかけてしまったので";
		mes "代金はいらないと伝えてください。";
		mes "あと、事情の説明もおねがいします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "わかりました。";
		mes "商品が消えてしまう話ですね。";
		mes "ところでチョコレートはどこに？";
		next;
		mes "[ショコラ=バシニオ]";
		mes "あ、これです。";
		mes "包装しておいたので";
		mes "このまま渡してください。";
		mes "それでは、お願いします～！";
		set QUEST_WHITEDAY,2;
		getitem 7432,1;
		close;
	case 2:
		mes "[ショコラ=バシニオ]";
		mes "アルルさんは、プロンテラ西の方にある";
		mes "酒場にいます。";
		mes "あ、レストランなんでしょうか？";
		mes "それではお願いします。";
		close;
	default:
		mes "[ショコラ=バシニオ]";
		mes "ありがとうございました～";
		mes "アルルさんから聞きましたよ！";
		mes "チョコレートをしっかり";
		mes "届けてくれたのですってね。";
		mes "でも、このままじゃ……";
		mes "商売にならないですね……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "ううぅ……";
		mes "どうしよう、どうしよう～!!";
		mes "ご飯が食べられなくなってしまう……";
		mes "あ……ご、ごめんなさい……";
		mes "興奮してしまいました……";
		next;
		mes "[ショコラ=バシニオ]";
		mes "アルルさんも";
		mes "商品が消えてしまうことに対して、";
		mes "調査をすると言っていましたし……";
		mes "良い結果が出ればいいのですけど……";
		mes "はうっ……";
		close;
	case 6:
		mes "[ショコラ=バシニオ]";
		mes "いらっしゃいませ～！　栄養満点！";
		mes "愛いっぱい！　幸せ百倍！";
		mes "「バシニオチョコレート」です！";
		next;
		mes "[ショコラ=バシニオ]";
		mes "あ！　今私のテンションが高いなって";
		mes "思いましたね？";
		mes "正解!!!!";
		mes "実は、チョコレートニンフを";
		mes "育てるようになったのですよ！";
		next;
		mes "[ショコラ=バシニオ]";
		mes "ふふ、すっごい可愛いんですよ！";
		mes "しかも、私が作るチョコレートと";
		mes "全く同じものを作ってくれるんです！";
		mes "今シーズンはこの子にお任せです！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（なんだ……、これからは泥棒が来ても";
		mes "かまわないってことなのかな……）";
		mes "はははっ……";
		mes "そのニンフ本当に可愛いですね。";
		mes "……";
		close;
	}
}

prt_in.gat,41,40,3	script	アルル=オルレアン	86,{
	if((Weight*100/Maxweight) >= 90) {
		mes "-所持アイテムの重量が多いため";
		mes "アイテムを受けとることができません-";
		mes "-所持アイテムを減らしてから、再度";
		mes "話しかけてください-";
		close;
	}
	switch(QUEST_WHITEDAY) {
	case 0:
	case 1:
		mes "[アルル=オルレアン]";
		mes "変ですね……";
		mes "何処に消えたんでしょう……";
		mes "まさか、誰かの嫌がらせでしょうか？";
		next;
		mes "[アルル=オルレアン]";
		mes "あ、お客様……";
		mes "申し訳ありませんが、商品がなくて";
		mes "お売りする事が出来ないんです。";
		mes "頼んでおいた商品が、";
		mes "届いてないんですよ。";
		next;
		mes "[アルル=オルレアン]";
		mes "本当に申し訳ありません。";
		mes "また、来ていただけますか……";
		close;
	case 2:
		if(countitem(7432)==0) {
			mes "[アルル=オルレアン]";
			mes "おかしい……";
			mes "バシニオチョコレートが届かない……";
			mes "今まで配達が遅れるなんてこと";
			mes "なかったのに……";
			mes "一度連絡を入れたほうが";
			mes "よさそうですね……";
			next;
			mes "[アルル=オルレアン]";
			mes "あ！　お客さん……";
			mes "申し訳ありませんが、商品がなくて";
			mes "お売りする事が出来ないんです。";
			mes "頼んでおいた商品が、";
			mes "届いてなくて……";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "あ、そのことなんですけど";
			mes "ショコラさんに頼まれて……";
			mes "（あれ？　渡された";
			mes "チョコレートが無い!?";
			mes "大変だ……どうしよう……）";
			next;
			mes "[アルル=オルレアン]";
			mes "おお、それでショコラさんはなんと？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "い、いえ、間違いでした……";
			mes "何でもありません……";
			mes "（何処に行ったんだろう？";
			mes "とにかく探さないと……）";
			next;
			mes "[アルル=オルレアン]";
			mes "そうですか……";
			mes "はぁ……";
			close;
		}
		mes "[アルル=オルレアン]";
		mes "何か用ですか？";
		mes "ちょっと今は忙しくて……";
		mes "申し訳ないのですが";
		mes "特に用事がないようでしたら";
		mes "お引取りいただけますか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "これを、ショコラさんから";
		mes "預かってきました。";
		next;
		mes "[アルル=オルレアン]";
		mes "え？　本当ですか？";
		mes "……";
		mes "あ！　これはバシニオチョコレート！";
		mes "これです、これを待っていたんですよ！";
		mes "よかったー！";
		next;
		mes "[アルル=オルレアン]";
		mes "でも……";
		mes "何故こんなに遅かったんでしょう？";
		mes "今までは納品が遅れるなんてこと";
		mes "なかったんですけど。";
		mes "まさか!!";
		mes "ショコラさんに何かあったんですか!?";
		next;
		mes "-納品が遅れた事情を説明した-";
		next;
		mes "[アルル=オルレアン]";
		mes "なるほど……";
		mes "そういうことだったのですね。";
		mes "でも……変ですね……";
		mes "実は、私も似たようなことが";
		mes "あったんですよ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "似たようなこと？";
		mes "どんなことですか？";
		next;
		mes "[アルル=オルレアン]";
		mes "実はですね……";
		mes "ちょっと目をはなした隙に";
		mes "売り物のチョコレートが";
		mes "全部消えてしまったんですよ。";
		mes "物音もしなかったですし……";
		next;
		mes "[アルル=オルレアン]";
		mes "それで、チョコレートが";
		mes "なくなった場所に";
		mes "こんなものが落ちていたんです。";
		mes "もし、泥棒の仕業なら";
		mes "これと関係があるのでしょうか？";
		next;
		mes "-アルル=オルレアンが見せて";
		mes "くれたのは、小さな露だった-";
		next;
		mes "[アルル=オルレアン]";
		mes "これは、「イグドラシルの露」";
		mes "と呼ばれるもので、";
		mes "アルケミストのスキル";
		mes "ホムンクルスに使うものです。";
		next;
		mes "[アルル=オルレアン]";
		mes "もし誰かの仕業なら";
		mes "アルケミストが犯人という可能性が";
		mes "高いと思うんですよ。";
		mes "誰か、私の代わりに";
		mes "調査してくれる人がいれば";
		mes "助かるのですけど……";
		next;
		mes "[アルル=オルレアン]";
		mes "あ、そうでした。";
		mes "配達をしてくれて、";
		mes "ありがとうございました。";
		mes "代金のことに関しては、";
		mes "ショコラさんと話しておきますね。";
		set QUEST_WHITEDAY,3;
		close;
	case 3:
		mes "[アルル=オルレアン]";
		mes "やはり、犯人はアルケミストである";
		mes "可能性が高いと思うんです。";
		mes "アルデバランの";
		mes "アルケミストギルドに行って";
		mes "調査しなければなりません！";
		next;
		mes "[アルル=オルレアン]";
		mes "でも……";
		mes "私は商売がありますし、";
		mes "ここを動くわけにはいかない……";
		mes "誰か調べてくれる人がいれば";
		mes "本当に助かるのですけど……";
		next;
		if(select("私が代わりに調べましょうか？","販売はいつから再開するのですか？")==2) {
			mes "[ショコラ=バシニオ]";
			mes "あー、そうですね……";
			mes "この事件の真相を明らかにするまでは";
			mes "販売はむずかしいでしょう……";
			mes "ホワイトデー期間が終わる前に";
			mes "稼がないといけないのですが……";
			next;
			mes "[ショコラ=バシニオ]";
			mes "私は貴方のように";
			mes "冒険者でもありませんし";
			mes "助けてくれる人もいないので……";
			next;
			mes "[ショコラ=バシニオ]";
			mes "私は別に大それた野望を";
			mes "持っているわけではないんです。";
			mes "商売して生活費を稼げればいい。";
			mes "ただ、それだけなんです……";
			mes "それなのに、何でこんなことに……";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "お気の毒に……";
			mes "いつになるか分からないのですね。";
			next;
			mes "[ショコラ=バシニオ]";
			mes "そうですね……";
			mes "いつになるんでしょうか……";
			mes "ホワイトデーシーズンが";
			mes "終わった後ですかね？";
			mes "あはははは……";
			close;
		}
		mes "[アルル=オルレアン]";
		mes "本当ですか!?";
		mes "ありがとうございます！";
		mes "さっきも言ったとおり、";
		mes "アルケミストギルドは、";
		mes "アルデバランにあります。";
		next;
		mes "[アルル=オルレアン]";
		mes "あ！　何かがわかりましたら、";
		mes "教えていただけますか？";
		mes "解決していただけたなら";
		mes "もちろんお礼はいたしますよ。";
		mes "それでは、よろしくお願いします。";
		set QUEST_WHITEDAY,4;
		close;
	case 4:
	case 5:
		mes "[アルル=オルレアン]";
		mes "アルケミストといえば";
		mes "やはり、アルデバランですね。";
		mes "良い結果を心待ちにしています。";
		close;
	case 6:
		mes "[アルル=オルレアン]";
		mes "あ！　私が前に泥棒に関しての";
		mes "調査をお願いした方ですね。";
		mes "その節はありがとうございました！";
		mes "でも、今はどうでもいいことなんです。";
		next;
		mes "[アルル=オルレアン]";
		mes "実はですね……";
		mes "信じてくれるか分かりませんが";
		mes "チョコレートニンフを";
		mes "育てているんですよ！";
		next;
		mes "[アルル=オルレアン]";
		mes "はっはっは!!";
		mes "この子が凄いんですよ！";
		mes "バシニオチョコレートと全く同じ";
		mes "チョコレートを作るんです！";
		next;
		mes "[アルル=オルレアン]";
		mes "いつもカップルを見て";
		mes "さびしい気持ちになっていた私が";
		mes "こんなに暖かい気持ちを";
		mes "持てるなんて……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（なんだ……、これからは泥棒が来ても";
		mes "かまわないってことなのかな……）";
		mes "はははっ……";
		mes "そのニンフ本当に可愛いですね。";
		mes "……";
		next;
		getinventorylist;
		for(set '@i,0; '@i<@inventorylist_count; set '@i,'@i+1) {
			if(@inventorylist_id['@i] == 559 || @inventorylist_id['@i] == 560) {
				if(@inventorylist_card3['@i]==0 && @inventorylist_card4['@i]==0) {
					mes "[アルル=オルレアン]";
					mes "おお！";
					mes "素敵なチョコレートを持っていますね！";
					mes "これはサービスです！";
					delitem @inventorylist_id['@i],1;
					getitem2 @inventorylist_id['@i],1,1,0,0,254,0,getcharid(0)&0xffff,(getcharid(0)>>16)&0xffff;
					next;
					break;
				}
			}
		}
		mes "[アルル=オルレアン]";
		mes "はっはははは!!";
		close;
	}
}

aldebaran.gat,155,88,3	script	訝しい少女	729,{
	if((Weight*100/Maxweight) >= 90) {
		mes "-所持アイテムの重量が多いため";
		mes "アイテムを受けとることができません-";
		mes "-所持アイテムを減らしてから、再度";
		mes "話しかけてください-";
		close;
	}
	switch(QUEST_WHITEDAY) {
	default:	//0～4のとき
		mes "[チェリーベリー]";
		mes "これは凄い発見だわ！";
		mes "雨の後……これはこうで……";
		mes "ん？　そこのあなた！";
		mes "人の話を盗み聞きするなんて失礼ね！";
		if(QUEST_WHITEDAY<4) close;
		next;
		if(select("何かあったんですか？","失礼しました……")==2) {
			mes "[チェリーベリー]";
			mes "変な人……";
			close;
		}
		mes "[チェリーベリー]";
		mes "ふふふ、私ホムンクルスの研究をしてて";
		mes "凄い発見をしたの！";
		mes "名づけて！　チョコレートニンフ！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "チョコレートニンフ？";
		mes "……";
		mes "（この子、消えたチョコレートと";
		mes "何か関係があるのかな？）";
		next;
		mes "[チェリーベリー]";
		mes "あなたも育ててみる？";
		mes "育てるなら、私が特別に用意した";
		mes "ニンフの種をあげるよ！";
		next;
		if(select("ください！","嘘でしょう？")==2) {
			mes "[チェリーベリー]";
			mes "ふーん、信じてないんだ。";
			mes "それじゃ、あげないわよ。";
			close;
		}
		mes "[チェリーベリー]";
		mes "うふふふ……";
		mes "これで、バレンタイン、ホワイトデー";
		mes "関係無しに、恋人がいなくたって";
		mes "チョコレートを";
		mes "た～っくさん食べられるわ！";
		next;
		mes "[チェリーベリー]";
		mes "恋人がいなくたって";
		mes "誰にでもチョコレートを";
		mes "もらう権利がある！";
		mes "あなたもそう思うでしょ？";
		mes "思うよね!!!?";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……";
		mes "ま、まあそうかもしれませんね……";
		mes "（嬉しくないと思うけど……）";
		next;
		mes "[チェリーベリー]";
		mes "ああ、ごめんなさい。";
		mes "話が長くなってしまったわ。";
		mes "早速ニンフの種と";
		mes "マニュアルをあげるね。";
		next;
		set QUEST_WHITEDAY,5;
		set QUEST_WHITEDAY_POSITION,rand(1,9);
		getitem 7182,1;
		mes "[チェリーベリー]";
		mes "肝心なことを言い忘れていたわ、";
		mes "種を植える場所なんだけど";
		mes "チョコレートニンフは森が";
		mes "大好きなのよね。";
		mes "だから、フェイヨンとか";
		mes "アルベルタ付近の森に行ってみて。";
		next;
		mes "[チェリーベリー]";
		mes "種を植えるのに最適な場所に近づくと";
		mes "マニュアルガイドが";
		mes "自動的に発動して、教えてくれるから、";
		mes "その後はガイドの指示に、";
		mes "従えばいいよ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "分かりました。";
		mes "（まあ、騙されたと思って";
		mes "一度やってみよう。";
		mes "フェイヨンかアルベルタ";
		mes "近隣の森か……）";
		close;
	case 5:
		mes "[チェリーベリー]";
		mes "調子はどう？";
		close;
	case 6:
		if(QUEST_WHITEDAY_POSITION) {
			mes "[チェリーベリー]";
			mes "ふふふ……";
			mes "これだけチョコレートを配れば";
			mes "ホワイトデーなんて、";
			mes "特別な日じゃなくなるわよね。";
			mes "……クックックック……";
			close;
		}
		mes "[チェリーベリー]";
		mes "チョコレートニンフに会ってみた？";
		mes "もう一度呼び出してみる？";
		next;
		if(select("やめてください！","もう一度やってみたい！")==1) {
			mes "[チェリーベリー]";
			mes "ちょっとー……";
			mes "チョコレート手に入ったんでしょ？";
			mes "何で怒ってるのよ？";
			mes "意味が分からないわ。";
			close;
		}
		mes "[チェリーベリー]";
		mes "わかったわ！";
		mes "それじゃ、マニュアルと";
		mes "ニンフの種のカカオの代金で";
		mes "25,000Zenyね！";
		mes "どう？　安いでしょ？";
		next;
		if(select("いりません","おねがいします")==1) {
			mes "[チェリーベリー]";
			mes "あっそう。";
			mes "まあいいけどね……";
			close;
		}
		mes "[チェリーベリー]";
		mes "ふふ、分かったわ！";
		next;
		if(Zeny<25000) {
			mes "[チェリーベリー]";
			mes "あなた……";
			mes "お金が足りないわよ……";
			mes "私に材料費も出させるつもり？";
			close;
		}
		mes "[チェリーベリー]";
		mes "一度やってるから";
		mes "改めて説明はしないよ。";
		mes "あとは、マニュアルを参考にしてね。";
		set QUEST_WHITEDAY_NYMPH,0;
		set QUEST_WHITEDAY_POSITION,rand(1,9);
		getitem 7182,1;
		close;
	}
}

//==============================================================

-	script	WhitedayNavi#0	-1,{
	set '@num,strnpcinfo(2);
	if(QUEST_WHITEDAY_POSITION/3 != '@num+1)	//1～3、4～6、7～9の3パターン
		end;
	mes "^4A4AFF-自動コンパニオンシステム作動-^000000";
	next;
	switch(QUEST_WHITEDAY_POSITION) {
		case 1: viewpoint 1,216,118,1,0x0000FF; break;
		case 2: viewpoint 1,176,120,1,0x0000FF; break;
		case 3: viewpoint 1,192,212,1,0x0000FF; break;
		case 4: viewpoint 1,158,80,1,0x0000FF; break;
		case 5: viewpoint 1,351,106,1,0x0000FF; break;
		case 6: viewpoint 1,194,212,1,0x0000FF; break;
		case 7: viewpoint 1,222,183,1,0x0000FF; break;
		case 8: viewpoint 1,237,349,1,0x0000FF; break;
		case 9: viewpoint 1,61,345,1,0x0000FF; break;
	}
	mes "^4A4AFFこんにちは！";
	mes "チョコレートコンパニオンです。";
	mes "まず、ミニマップを見てください。";
	mes "種を植えるのに適した場所を";
	mes "表示しております。^000000";
	next;
	mes "^4A4AFFミニマップの表示を確認して";
	mes "該当の場所に種を植えてください。^000000";
	close;
}

pay_fild01.gat,216,118,0	duplicate(WhitedayNavi#0)	WhitedayNavi#1	139,3,3
pay_fild03.gat,373,69,0		duplicate(WhitedayNavi#0)	WhitedayNavi#2	139,3,3
pay_fild08.gat,43,77,0		duplicate(WhitedayNavi#0)	WhitedayNavi#3	139,3,3


-	script	茂み#NYMPH	111,{
	if(QUEST_WHITEDAY_NYMPH==13) {
		mes "-自称チョコレートニンフが";
		mes "いた場所には、もう誰もいなかった-";
		close;
	}
	set '@num,strnpcinfo(2);
	if(QUEST_WHITEDAY<5 || QUEST_WHITEDAY_POSITION != '@num) {
		mes "-何か妙な気配を感じる-";
		mes "-見えない何かがいるようだ-";
		close;
	}
	switch(QUEST_WHITEDAY_NYMPH) {
	case 0:
		mes "^4A4AFF本当に探してきたんですね。";
		mes "ではその種をここに植えてください。^000000";
		next;
		if(countitem(7182)<1) {
			mes "^4A4AFFカカオを植えてください。^000000";
			close;
		}
		mes "^4A4AFFカカオを植えました？";
		mes "芽がよくでるように";
		mes "聖水やミルクをあげるといいですよ。^000000";
		delitem 7182,1;
		set QUEST_WHITEDAY_NYMPH,1;
		close;
	case 1:
		mes "^4A4AFF水が必要なんですが、";
		mes "聖水かミルク持っていますか？^000000";
		next;
		switch(select("聖水がある","ミルクがある","取り消し")) {
			case 1:
				set '@item,523;
				break;
			case 2:
				set '@item,519;
				break;
			case 3:
				mes "^4A4AFF種を育てるために、";
				mes "聖水かミルクを持ってきてください。^000000";
				close;
		}
		mes "^4A4AFF種を植えた場所に、";
		mes getitemname('@item)+ "を撒いてください。";
		mes "10個くらいが丁度良いと思います。";
		mes "多すぎても少なすぎても";
		mes "だめですからね。^000000";
		next;
		if(countitem('@item) < 10) {
			mes "^4A4AFF" +getitemname('@item)+ "を10個用意してください。^000000";
			close;
		}
		mes "["+strcharinfo(0)+"]";
		mes "なるほど" +getitemname('@item)+ "をあげればいいんだね。";
		mes "じゃあ……1個……2個……";
		next;
		misceffect 18,"";
		mes "["+strcharinfo(0)+"]";
		mes "3個……4個……";
		mes "まだ芽は出ないなぁ。";
		mes "5個……6個……";
		next;
		misceffect 18,"";
		mes "["+strcharinfo(0)+"]";
		mes "……………………";
		mes "ぴかぴかと光ってるなぁ。";
		mes "何かが飛び出してきたりしないかな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "9個目……";
		mes "よし、たっぷり" +getitemname('@item)+ "をあげたけど";
		mes "まだ芽が出てこないよ。";
		next;
		mes "^4A4AFFすぐには芽はでませんよ。";
		mes "愛情をもって待っていれば";
		mes "そのうち芽がでてきます。^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "うぅ、こいつ全然役に立たない……";
		delitem '@item,10;
		set QUEST_WHITEDAY_NYMPH,2;
		close;
	case 2:
		if(rand(5)) {
			mes "^4A4AFFまだ何も変化がないようですね。";
			mes "もうちょっと見守っていましょう。^000000";
			close;
		}
		mes "["+strcharinfo(0)+"]";
		mes "芽が出ていない!?";
		mes "だまされたのかもしれないな……";
		mes "……";
		mes "あ！";
		next;
		cutin "white_seed",2;
		mes "-茂みに何か小さな芽が伸びている-";
		mes "-小指くらいの大きさで";
		mes "まるい葉っぱが可愛い-";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "もしかして、これが若葉なのかな？";
		next;
		mes "^4A4AFFやっと芽がでてきましたね。";
		mes "それではちょっと";
		mes "栄養をあげましょう。^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "栄養というと？";
		next;
		mes "^4A4AFFそうですね……";
		mes "ミルク、聖水、魔女の星の砂、";
		mes "リンゴジュース、フェイヨン水溶液。";
		mes "この中から選ぶと良いですよ。^000000";
		set QUEST_WHITEDAY_NYMPH,3;
		break;
	case 3:
		cutin "white_seed",2;
		mes "^4A4AFF用意したものを見せてください。^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……えっと。";
		next;
		switch(select("ミルク","聖水","魔女の星の砂","リンゴジュース","フェイヨン水溶液","持っていない")) {
			case 1:
				if(countitem(519)<1) {
					mes "^4A4AFFミルクを持ってないじゃないですか！^000000";
					close2;
					cutin "white_seed",255;
					end;
				}
				mes "^4A4AFF早速ミルクを撒いてください。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "うん……";
				mes "……………………";
				mes "よし、撒いたよ。どうかな？";
				next;
				mes "^4A4AFFでは、しばらく待ちましょうか。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……………………";
				mes "また、待つのですか……";
				set QUEST_WHITEDAY_SEX,0;
				delitem 519,1;
				break;
			case 2:
				if(countitem(523)<1) {
					mes "^4A4AFF聖水を持ってないじゃないですか！^000000";
					close2;
					cutin "white_seed",255;
					end;
				}
				mes "^4A4AFF早速聖水を撒いてください。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "うん……";
				mes "……………………";
				mes "よし、撒いたよ。どうかな？";
				next;
				mes "^4A4AFFでは、しばらく待ちましょうか。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……………………";
				mes "また、待つのですか……";
				set QUEST_WHITEDAY_SEX,0;
				delitem 523,1;
				break;
			case 3:
				if(countitem(1061)<1) {
					mes "^4A4AFF魔女の星の砂を";
					mes "持ってないみたいですね。^000000";
					close2;
					cutin "white_seed",255;
					end;
				}
				mes "^4A4AFFえ、魔女の星の砂？";
				mes "本当に撒くのですか？^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "え？　だって魔女の星の砂も";
				mes "候補にあがっていたよね？";
				mes "さらさらさら～っと。";
				mes "撒いた！　さあ、どうかな!?";
				next;
				mes "^4A4AFFどうって言われても……^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "（おいおい、君がもってこいって";
				mes "言ったのに……）";
				mes "何もおこらないね……";
				set QUEST_WHITEDAY_SEX,0;
				delitem 1061,1;
				break;
			case 4:
				if(countitem(531)<1) {
					mes "^4A4AFFリンゴジュースを";
					mes "持ってないみたいですね。^000000";
					close2;
					cutin "white_seed",255;
					end;
				}
				mes "^4A4AFF早速リンゴジュースを撒いてください。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "わかった！";
				mes "……………………";
				mes "よし、撒いたよ。どうかな？";
				next;
				mes "^4A4AFFでは、しばらく待ちましょうか。^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……………………";
				mes "また、待つのか……";
				set QUEST_WHITEDAY_SEX,1;
				delitem 531,1;
				break;
			case 5:
				if(countitem(1089)<1) {
					mes "^4A4AFFあら？　フェイヨン水溶液を";
					mes "もっていないみたいですね。^000000";
					close2;
					cutin "white_seed",255;
					end;
				}
				mes "^4A4AFFえ？　フェイヨン水溶液を";
				mes "本当に撒くのですか？^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "もちろんだよ。";
				mes "きっと凄い芽になるよ。";
				mes "ばしゃーっと……";
				mes "撒いた！　さあ、どうだ!?";
				next;
				mes "^4A4AFF……………………";
				mes "どうなるのか待って見ますか……^000000";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "何、その冷たい態度は……";
				set QUEST_WHITEDAY_SEX,1;
				delitem 1089,1;
				break;
			case 6:
				mes "^4A4AFF……愛情を込めて育ててくださいね。";
				mes "ちゃんと栄養になるものを";
				mes "もってきてください。^000000";
				close2;
				cutin "white_seed",255;
				end;
		}
		set QUEST_WHITEDAY_NYMPH,4;
		break;
	case 4:
		if(rand(5)) {
			cutin "white_seed",2;
			mes "^4A4AFFまだ、変化がおこりませんね。";
			mes "他に何か撒いてみますか？^000000";
			next;
			if(countitem(504)) {
				delitem 504,1;
				mes "["+strcharinfo(0)+"]";
				mes "白ポーション……これでいいかな？";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……反応が無いね……";
				mes "結構高かったんだけどなぁ。";
			}
			else if(countitem(505)) {
				delitem 505,1;
				mes "["+strcharinfo(0)+"]";
				mes "青ポーション、どうかな。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……無反応。";
				mes "何をあげればいいんだろう……";
			}
			else if(countitem(519)) {
				delitem 519,1;
				mes "["+strcharinfo(0)+"]";
				mes "ミルク、これならどうだ！";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……だめだ";
				mes "栄養が足りないのかなぁ。";
			}
			else if(countitem(523)) {
				delitem 523,1;
				mes "["+strcharinfo(0)+"]";
				mes "聖水！　これならいける！";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "あら……反応がないね";
				mes "栄養が足りないのかなぁ。";
			}
			else if(countitem(531)) {
				delitem 531,1;
				mes "["+strcharinfo(0)+"]";
				mes "リンゴジュース、これでどうかな。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……無反応。";
				mes "結構高かったんだけどなぁ。";
			}
			else if(countitem(1061)) {
				delitem 1061,1;
				mes "["+strcharinfo(0)+"]";
				mes "魔女の星の砂、これはどうかな。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "……無反応。";
				mes "おかしいなぁ。";
			}
			else {
				mes "^4A4AFF何か栄養のあるものを、";
				mes "持って来てください。";
				mes "栄養が足りていないのだと思います。^000000";
			}
			close2;
			cutin "white_seed",255;
			end;
		}
		mes "^4A4AFFもうそろそろですよ。";
		mes "よく見ててください。^000000";
		next;
		mes "^4A4AFFおめでとうございます！";
		mes "ニンフを呼び出すことができましたね。^000000";
		next;
		if(QUEST_WHITEDAY_SEX==0)
			cutin "white_choco",2;
		else
			cutin "white_retto",2;
		mes "["+strcharinfo(0)+"]";
		mes "うわ……本当に出た……";
		next;
		mes "[チョコレートニンフ]";
		if(QUEST_WHITEDAY_SEX==0)
			mes "うっにゃあ……";
		else
			mes "うーん……";
		set QUEST_WHITEDAY_NYMPH,5;
		break;
	case 5:
		mes "["+strcharinfo(0)+"]";
		mes "お願い、もう一度姿を現して……";
		next;
		mes "-茂みの中をかきわけると";
		mes "私が植えた種から生まれた";
		mes "正体不明の生き物が姿を現わした-";
		next;
		mes "[チョコレートニンフ]";
		if(QUEST_WHITEDAY_SEX==0) {
			mes "お腹すいたなぁ～";
			cutin "white_choco",2;
		}
		else {
			mes "呼んだ？";
			cutin "white_retto",2;
		}
		next;
		if(select("願い事をする","言葉が通じるか試す")==1) {
			mes "["+strcharinfo(0)+"]";
			mes "う～ん、お願いでもしてみようかな。";
			mes "でも、何をお願いしよう……";
			mes "古く青い箱をくださいとか？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "よし、私の願いを聞いてください!!";
			next;
			if(QUEST_WHITEDAY_SEX==0) {
				mes "[チォチォコ]";
				mes "チォチォコ……";
				mes "お腹すいたよぅ。";
				mes (Sex)? "パパー": "ママー";
			}
			else {
				mes "[レト]";
				mes "はぁ？　なんのこと？";
				mes "そんなこと言ってる暇があったら";
				mes "食べるものもってきてよ。";
			}
		}
		else {
			mes "["+strcharinfo(0)+"]";
			if(QUEST_WHITEDAY_SEX==0) {
				mes "えっと、なにか話せるかな？";
				mes "言ってる意味わかる？";
				next;
				mes "[チォチォコ]";
				mes "チォチォコ……";
				mes "お腹すいたよぅ。";
				mes (Sex)? "パパー": "ママー";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "ちゃんとしゃべれるんだね。";
			}
			else {
				mes "そ、そこの謎の生命体。";
				mes "言葉はわかるかい？";
				next;
				mes "[レト]";
				mes "謎の生命体ではなくレトだ。";
				next;
				mes "["+strcharinfo(0)+"]";
				mes "お、ちゃんと話せる！";
			}
		}
		next;
		mes "^4A4AFFどうやら";
		mes "お腹がすいているみたいですね。^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "うわっ！　びっくりした!!";
		mes "突然出てこないでよ！";
		mes "なぜいつも人を、";
		mes "驚かせることばかりするんだ？";
		next;
		mes "^4A4AFFごめんなさい。";
		mes "驚かせるつもりなかったんですよ……^000000";
		next;
		mes "^4A4AFFもっと驚くかもしれないけど、";
		mes "私は人工知能マニュアルシステムを";
		mes "装った魂なんですよ。";
		mes "生涯一度も";
		mes "チョコレートをもらえなかった";
		mes "寂しい寂しい魂なんです……^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……（このアルケミストは一体……）";
		mes "君の事情なんてどうでもいいよ！";
		next;
		if(QUEST_WHITEDAY_SEX==0) {
			mes "[チォチォコ]";
			mes "……チョコレートほしい？";
		}
		else {
			mes "[レト]";
			mes "チョコレート欲しいのかい？";
		}
		next;
		mes "["+strcharinfo(0)+"]";
		mes "え？　今なんて言ったの？";
		next;
		if(QUEST_WHITEDAY_SEX==0) {
			mes "[チォチォコ]";
			mes "……";
			mes "ニンジン。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "ん？";
			mes "ニンジンがどうかしたの？";
		}
		else {
			mes "[レト]";
			mes "……";
			mes "お腹が減った。";
			mes "ニンジン持ってきてよ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "……ええ？";
			mes "さっき、別のこと言ってたよね……";
		}
		next;
		mes "^4A4AFFニンジンが欲しいみたいですね。";
		mes "ちゃんと面倒をみないとダメですよ。^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "あぁ、そうか、なるほど……";
		mes "大丈夫、ちゃんと面倒みるよ。";
		mes "ニンジンなんて欲しいのか……";
		set QUEST_WHITEDAY_NYMPH,6;
		break;
	default:	//6～9のとき
		switch(QUEST_WHITEDAY_NYMPH) {
			case 6: set '@item,515; break;	//ニンジン
			case 7: set '@item,512; break;	//リンゴ
			case 8: set '@item,519; break;	//ミルク
			case 9: set '@item,1061; break;	//魔女の星の砂
		}
		if(countitem('@item)<1) {
			mes "^4A4AFF" +getitemname('@item)+ "をまだ";
			mes "用意していなかったんですか？^000000";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "君に言われなくても";
			mes "わかってるよ!!";
			close;
		}
		cutin "white_seed",2;
		mes "["+strcharinfo(0)+"]";
		mes "おーい、" +getitemname('@item)+ "持ってきたよ。";
		mes "どこにいるの？";
		next;
		if(QUEST_WHITEDAY_SEX==0) {
			cutin "white_choco",2;
			mes "[チォチォコ]";
			mes "チォチォコここにいるー。";
			mes getitemname('@item)+ "嫌いだよー。";
			set QUEST_WHITEDAY_NYMPH,rand(6,10);
			switch(QUEST_WHITEDAY_NYMPH) {
			case 6:
				mes "チォチォコ、ニンジン好き。";
				break;
			case 7:
				mes "チォチォコ、リンゴ好き。";
				break;
			case 8:
				mes "チォチォコ、ミルク好き。";
				break;
			case 9:
				mes "チォチォコ、";
				mes "キラキラ魔女の星の砂欲しい。";
				break;
			case 10:
				mes "チォチォコ、";
				mes "キラキラ透明な宝石欲しい。";
				break;
			}
		}
		else {
			cutin "white_retto",2;
			mes "[レト]";
			mes "ここだここだ。";
			mes "本当に持って来たな！";
			mes "ありがとう！";
			set QUEST_WHITEDAY_NYMPH,rand(6,10);
			switch(QUEST_WHITEDAY_NYMPH) {
			case 6:
				mes "ところでニンジンない？";
				mes "目が覚めたばかりで";
				mes "栄養がたくさん必要なんだ。";
				break;
			case 7:
				mes "ところでリンゴない？";
				mes "目が覚めたばかりで";
				mes "栄養がたくさん必要なんだ。";
				break;
			case 8:
				mes "ところでミルクない？";
				mes "目が覚めたばかりで";
				mes "栄養がたくさん必要なんだ。";
				break;
			case 9:
				mes "ところで魔女の星の砂ない？";
				mes "目が覚めたばかりで";
				mes "魔力がたくさん必要なんだ。";
				break;
			case 10:
				mes "ダイヤモンド持ってる？";
				mes "あったらちょうだい。";
				mes "きっとお返しはするよ。";
				break;
			}
		}
		delitem '@item,1;
		break;
	case 10:
		if(countitem(730)<1) {
			mes "^4A4AFFあのー……";
			mes "ダイヤモンド1カラットじゃないと";
			mes "だめみたいですよ。^000000";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "1カラットか……";
			close;
		}
		if(QUEST_WHITEDAY_SEX==0) {
			cutin "white_choco",2;
			mes "["+strcharinfo(0)+"]";
			mes "おーい、チョコじゃなくてチォチォコ！";
			mes "ダイヤモンド1カラット持ってきたよ。";
			next;
			mes "[チォチォコ]";
			mes "うわーぃ！";
			mes "本当にありがとう。";
			mes "私もなにかお返ししなくちゃね。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（あれ？　急に言葉がうまくなってる）";
			mes "何をしてくれるのかな？";
			next;
			mes "[チォチォコ]";
			mes "チォチォコはチョコレートのチォコ！";
			mes "おいしいチョコレートあげるよー。";
		}
		else {
			cutin "white_retto",2;
			mes "["+strcharinfo(0)+"]";
			mes "おーい、レト、いる？";
			mes "ダイヤモンド1カラットを";
			mes "持ってきたよ。";
			next;
			mes "[レト]";
			mes "わー、いよいよだ。";
			mes "これで帰ることができる。";
			mes "連絡はするよ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（帰るだって？）";
			mes "何を言ってるの？";
			next;
			mes "[チォチォコ]";
			mes "レトはチョコレートニンフ。";
			mes "今はその時期だし、";
			mes "僕を呼び出した理由も";
			mes "なんとなくわかるよ。";
			mes "チョコレートが欲しいのかな？";
		}
		delitem 730,1;
		set QUEST_WHITEDAY_NYMPH,11;
		break;
	case 11:
		if(QUEST_WHITEDAY_SEX==0) {
			cutin "white_choco",2;
			mes "[チォチォコ]";
		}
		else {
			cutin "white_retto",2;
			mes "[レト]";
		}
		mes "周りに邪魔者はいない？";
		next;
		switch(select("人がいる","モンスターがいる","誰もいない")) {
			case 1:
				if(QUEST_WHITEDAY_SEX==0) {
					mes "[チォチォコ]";
					mes "人がいれば争いが起こる。";
					mes "チォチォコは見たくないよ。";
					mes "争いごとなんて見たくないよ。";
				}
				else {
					mes "[レト]";
					mes "人は同族なのにすぐ喧嘩をする……";
					mes "そんなのは見たくない……";
				}
				break;
			case 2:
				if(QUEST_WHITEDAY_SEX==0) {
					mes "[チォチォコ]";
					mes "モンスターいるの……？";
					mes "モンスター怖いよぅ。";
				}
				else {
					mes "[レト]";
					mes "モンスターに襲われたくはない。";
					mes "また後にしよう……";
				}
				break;
			case 3:
				if(QUEST_WHITEDAY_SEX==0) {
					mes "[チォチォコ]";
					mes "^00FF00本当に？^000000";
				}
				else {
					mes "[レト]";
					mes "^00FF00本当に誰もいない？^000000";
				}
				next;
				if(select("本当はいる","本当にいない")==1) {
					if(QUEST_WHITEDAY_SEX==0) {
						mes "[チォチォコ]";
						mes "だめだよ。";
						mes "チォチォコはみんなが欲に目がくらんで";
						mes "争うのを見たくないよ。";
					}
					else {
						mes "[レト]";
						mes "人が争っている姿なんて";
						mes "見たくない！";
					}
					break;
				}
				if(QUEST_WHITEDAY_SEX==0) {
					mes "[チォチォコ]";
					mes "チォチォコを育ててくれて";
					mes "ありがとう♪";
					if(rand(2)) {
						getitem 560,6;
						getitem 559,2;
						getitem 558,2;
					}
					else {
						getitem 559,1;
						getitem 560,3;
						getitem 530,3;
					}
				}
				else {
					mes "[レト]";
					mes "わかった！";
					mes "僕を育ててくれたお礼を渡すよ！";
					if(rand(2)) {
						getitem 560,4;
						getitem 573,3;
					}
					else {
						getitem 560,4;
						getitem 559,2;
						getitem 558,2;
					}
				}
				set QUEST_WHITEDAY_NYMPH,12;
				break;
		}
		break;
	case 12:
		if(QUEST_WHITEDAY_SEX==0) {
			cutin "white_choco",2;
			mes "[チォチォコ]";
			mes "これぐらいでいい？";
			mes "チョコレート沢山だよ。";
			next;
			menu "このチョコレート何処から来たの？",-;
			mes "[チォチォコ]";
			mes "チォチォコはチョコレートの妖精。";
			mes "だけど、何もなしにチョコレートを";
			mes "作るのはできないの。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "え!?";
			mes "じゃあどうやって作ってるの？";
			next;
			mes "[チォチォコ]";
			mes "作るというか、";
			mes "チョコレートが出てくるの。";
			mes "何処から来たのか分からないけど。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "チョコレートが出てくる？";
			mes "作られたチョコレートが";
			mes "突然消えた原因はこれだったんだ！";
			next;
			mes "[チォチォコ]";
			mes "え？　チォチォコはもう行くよ。";
			mes "じゃあね！";
		}
		else {
			cutin "white_retto",2;
			mes "[レト]";
			mes "どうかな？";
			mes "この位で十分？";
			next;
			menu "チョコレートをどうやって作ったの？",-;
			mes "[レト]";
			mes "レトはチョコレートニンフだけど、";
			mes "材料もなしにチョコレートを";
			mes "作ることはできないよ。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "え!?";
			mes "じゃあどうやって作ってるの？";
			next;
			mes "[レト]";
			mes "作るというか、";
			mes "チョコレートが出て来るんだよな。";
			mes "何処から出てきているのかは、";
			mes "分からないんだけどね。";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "チョコレートが出てくる？";
			mes "作られたチョコレートが";
			mes "突然消えた原因はこれだったんだ！";
			next;
			mes "[レト]";
			mes "それじゃあ、僕は帰るよ。";
			mes "じゃあね。";
		}
		if(QUEST_WHITEDAY==5)
			set QUEST_WHITEDAY,6;
		set QUEST_WHITEDAY_NYMPH,13;
		set QUEST_WHITEDAY_SEX,0;
		set QUEST_WHITEDAY_POSITION,0;
		break;
	}
	close2;
	cutin "dummy",255;
	end;
}

pay_fild01.gat,216,118,0	duplicate(茂み#NYMPH)	茂み#1	111
pay_fild01.gat,176,120,0	duplicate(茂み#NYMPH)	茂み#2	111
pay_fild01.gat,192,212,0	duplicate(茂み#NYMPH)	茂み#3	111
pay_fild03.gat,158,80,0		duplicate(茂み#NYMPH)	茂み#4	111
pay_fild03.gat,351,106,0	duplicate(茂み#NYMPH)	茂み#5	111
pay_fild03.gat,194,212,0	duplicate(茂み#NYMPH)	茂み#6	111
pay_fild08.gat,222,183,0	duplicate(茂み#NYMPH)	茂み#7	111
pay_fild08.gat,237,349,0	duplicate(茂み#NYMPH)	茂み#8	111
pay_fild08.gat,61,345,0		duplicate(茂み#NYMPH)	茂み#9	111


/* 旧ホワイトデー
alberta.gat,188,64,4	script	お菓子商人	91,{
	mes "[メイプル=シュガー]";
	mes "いらっしゃいませ！";
	mes "美味しいお菓子はいかがですか？";
	mes "お師匠様……じゃなくて……";
	mes "アルベルタのお菓子職人が";
	mes "一生懸命つくったお菓子です。";
	next;
	mes "[メイプル=シュガー]";
	mes "愛しい人からもらった";
	mes "プレゼントのお返しに……";
	mes "心のこもった、あまぁ～い";
	mes "お菓子はいかがですか～？";
	next;
	switch (select("ください！","いりません。","お師匠様？")) {
	case 1:
		mes "[メイプル=シュガー]";
		mes "はい！";
		mes "こちらがメニューになっております～";
		mes "数に限りがあるため";
		mes "まとめ買いは^ff00005つ^000000までと";
		mes "させていただきますね。";
		next;
		switch (select("キャンディ","スティックキャンディ","よく焼いたクッキー")) {
			case 1:
				set '@itemid,529;
				set '@price,3000;
				break;
			case 2:
				set '@itemid,530;
				set '@price,4000;
				break;
			case 3:
				set '@itemid,538;
				set '@price,2000;
				break;
		}
		mes "[メイプル=シュガー]";
		mes getitemname('@itemid)+ "ですね～";
		mes '@price+ "Zenyになります～";
		mes "いくつお買い上げですか？";
		while(1) {
			next;
			input '@num;
			if('@num>5) {
				mes "[メイプル=シュガー]";
				mes "あら？あらら？";
				mes "何個っておっしゃいました？";
				mes "今、私聞き逃しちゃったみたいです。";
				mes "もう一度おっしゃっていただけますか？";
				mes "一度にお買い上げいただけるのは";
				mes "^ff00005つ^000000までです～";
				continue;
			}
			break;
		}
		if('@num<=0)
			break;	//switch文抜ける
		if(Zeny<'@price*'@num) {
			mes "[メイプル=シュガー]";
			mes "あらら……？";
			mes "お客様、お金が足りませんよ～";
			mes "もう一度所持金をお確かめの上";
			mes "ご注文をお願いいたします～";
			close;
		}
		set Zeny,Zeny-'@price*'@num;
		getitem '@itemid,'@num;
		mes "[メイプル=シュガー]";
		mes "ありがとうございます～";
		mes "このお菓子、本当に美味しいんですよ～";
		mes "お師匠のお菓子は世界一なんですから！";
		mes "ご自分で食べてもよろしいですけど";
		mes "やみつきになって太らないように";
		mes "気をつけてくださいねぇ。";
		close;
	case 2:
		break;
	case 3:
		mes "[メイプル=シュガー]";
		mes "あ、はい。";
		mes "私のお師匠様は";
		mes "お菓子職人のクーベル様と";
		mes "キルシュ様です。";
		mes "お二人の元でお菓子作りの";
		mes "修行をさせていただいております～";
		next;
		mes "[メイプル=シュガー]";
		mes "この時期はお師匠様達が直々に";
		mes "移動販売をしているらしいのですが……";
		mes "今どこに居られるのかは、";
		mes "私にはわかりませんけど、";
		mes "どこかで会えるかもしれませんね～";
		close;
	}
	mes "[メイプル=シュガー]";
	mes "そうですか……残念です。";
	mes "しばらくはこちらで";
	mes "販売させていただきますので、";
	mes "もし欲しくなったら、";
	mes "声をおかけください！";
	if(@menu==2)
		close;
	next;
	mes "[メイプル=シュガー]";
	mes "ただし、数に限りがございますので";
	mes "お早めに……";
	mes "ありがとうございました。";
	close;
}
*/