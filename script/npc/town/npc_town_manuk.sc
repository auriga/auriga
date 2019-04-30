//= Auriga Script ==============================================================
// Ragnarok Online Manuk Town Script	by refis
//==============================================================================

//============================================================
// 猫の手職員
//------------------------------------------------------------
manuk.gat,108,357,4	script	猫の手職員	421,{
	if(CATHAND_POINT == 0) {
		mes "[猫の手職員]";
		mes "ご利用ありがとうございます。";
		mes "猫の手サービスでございます。";
		next;
		mes "[猫の手職員]";
		mes "……うにゃにゃ？";
		mes "あなたは";
		mes "猫の手サービスと";
		mes "会員契約していないようですなあ。";
		next;
		mes "[猫の手職員]";
		mes "この機会に是が非でも";
		mes "会員契約して欲しいです！";
		mes "契約すると便利なサービスを";
		mes "受けれるんですよ。";
		next;
		mes "[猫の手職員]";
		mes "契約は";
		mes "^FF0000ミッドガルド連合軍駐屯地にいる";
		mes "猫の手職員^000000がしてくれるから";
		mes "是非、彼に話しかけて";
		mes "契約してください。";
		close;
	}
	mes "[猫の手職員]";
	mes "うにゃ、";
	mes "いつも^FF0000猫の手サービス^000000";
	mes "ご利用ありがとうございます。";
	next;
	mes "[猫の手職員]";
	mes "現在、あなたの";
	mes "猫の手信用ポイントは、";
	mes "^FF0000" +CATHAND_POINT+ "^000000ポイントです。";
	mes "今日は、どのサービスをご利用ですか？";
	next;
	setarray '@str$,(CATHAND_POINT >= 10)? "倉庫サービス": "",
			(CATHAND_POINT >= 100)? "猫ワープ": "";
	switch(select("位置保存サービス(連合軍駐屯地)",'@str$[0],'@str$[1],"やめる")) {
	case 1:
		savepoint "mid_camp.gat",56,138;
		mes "[猫の手職員]";
		mes "この先にある街の住民達の";
		mes "反発があって";
		mes "ここではセーブできないんです。";
		next;
		mes "[猫の手職員]";
		mes "だから、";
		mes "ミッドガルド連合軍駐屯地";
		mes "にセーブしておきました。";
		mes "申し訳ないうにゃ。";
		mes "実は反発の原因は私です。";
		next;
		mes "[猫の手職員]";
		mes "この前、木だと思って爪とぎをしたら";
		mes "悲鳴が聞こえたんです。";
		mes "不思議に思ってよく見たら、";
		mes "木ではなくこの先の街の住民でした。";
		mes "それからですにゃ、";
		mes "住民が冷たくなったのは。";
		close;
	case 2:
		if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "おかしいですね。";
			mes "ここに新米冒険者は";
			mes "来れないはずなのに……";
			next;
			mes "[猫の手職員]";
			mes "基本スキルをレベル6まで";
			mes "習得していないと";
			mes "倉庫は利用できないのです。";
			close;
		}
		if(Zeny < 60) {
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "Zenyが足りないようですよ。";
			mes "我々猫の手サービスの";
			mes "倉庫利用料は60Zenyです。";
			mes "お安いでしょう？";
			close;
		}
		set Zeny,Zeny-60;
		openstorage;
		close;
	case 3:
		mes "[猫の手職員]";
		mes "現在、";
		mes strcharinfo(0)+ "様の";
		mes "猫の手信用ポイントは、";
		mes "^FF0000" +CATHAND_POINT+ "^000000ポイント";
		mes "ですので、次の街への";
		mes "猫ワープサービスが利用できます。";
		next;
		switch(select("連合軍駐屯地----5500z","スプレンディッドフィールド02----7500z","やめる")) {
		case 1:
			set '@map$,"mid_camp.gat";
			set '@warpx,56;
			set '@warpy,139;
			set '@zeny,5500;
			break;
		case 2:
			set '@map$,"spl_fild02.gat";
			set '@warpx,32;
			set '@warpy,225;
			set '@zeny,7500;
			break;
		case 3:
			mes "[猫の手職員]";
			mes "わかりました。";
			mes "またの利用をお待ちしています。";
			close;
		}
		if(Zeny < '@zeny) {
			mes "[猫の手職員]";
			mes "にゃにゃ、お金が足りませんよ。";
			close;
		}
		mes "[猫の手職員]";
		mes "にゃにゃ、";
		mes "それではお送りします。";
		close2;
		set Zeny,Zeny - '@zeny;
		warp '@map$,'@warpx,'@warpy;
		end;
	case 4:
		mes "[猫の手職員]";
		mes "わかりました。";
		mes "またお待ちしております。";
		close;
	}
}

//============================================================
// マヌク商人
//------------------------------------------------------------
man_in01.gat,286,16,1	script	マヌク商人	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[マヌク商人]";
		mes "∬⊃∑";
		mes "∝⊂∫　⊂　￢";
		close;
	}
	mes "[マヌク商人]";
	mes "いらっしゃいませ。";
	mes "何をお求めでしょうか？";
	next;
	switch(select("商品の説明書を見る","マヌクの豪気","マヌクの意思","マヌクの信念","やめておく")) {
	case 1:
		mes "[マヌク商人]";
		mes "はい、";
		mes "こちら商品の説明書です。";
		close2;
		openbook 11019;
		end;
	case 2:
		set '@gain,12342;
		break;
	case 3:
		set '@gain,12343;
		break;
	case 4:
		set '@gain,12348;
		break;
	case 5:
		mes "[マヌク商人]";
		mes "そうですか、";
		mes "またお越しください。";
		close;
	}
	mes "[マヌク商人]";
	mes "^3131FFマヌクコイン1個^000000につき";
	mes getitemname('@gain)+ "を";
	mes "^3131FF3個^000000ご購入できます。";
	next;
	if(select("買う","買わない") == 2) {
		mes "[マヌク商人]";
		mes "そうですか、";
		mes "またお越しください。";
		close;
	}
	if(countitem(6080) < 1) {
		mes "[マヌク商人]";
		mes "申し訳ありませんが";
		mes "コインが足りませんよ。";
		close;
	}
	if(checkitemblank() == 0) {
		mes "[商人]";
		mes "あれ？";
		mes "荷物を持ちすぎですよ。";
		mes "これでは商品を渡すことは出来ません。";
		mes "荷物の種類を減らしてから";
		mes "また話しかけてくださいね。";
		close;
	}
	if(checkweight('@gain,3) == 0) {
		mes "[商人]";
		mes "あれ？";
		mes "荷物を持ちすぎですよ。";
		mes "これでは商品を渡すことは出来ません。";
		mes "荷物の重量を減らしてから";
		mes "また話しかけてくださいね。";
		close;
	}
	mes "[マヌク商人]";
	mes "ご利用、ありがとうございました。";
	delitem 6080,1;
	getitem '@gain,3;
	close;
}

//============================================================
// マヌク住人
//------------------------------------------------------------
manuk.gat,215,132,4	script	青年	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[青年]";
		mes "∠∫∋ ⊆ ∪∑∧ ∃ ∧∮⊃";
		mes "∑⊂∠ ∑ ∋∵∝ ∫ ∀∝";
		mes "∽￢∋ ⊆ ⊆⊃∮ ⊃ ";
		mes "⊂∵∵ ∬ ∃∫⊆ ⊆ ⊂∵";
		close;
	}
	mes "[青年]";
	mes "お前は……小さいな。";
	mes "しかし妖精とは異なる種のようだな。";
	mes "妖精ではないということは";
	mes "我々の敵ではないということだ。";
	close;
}

manuk.gat,188,216,3	script	学者	449,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[学者]";
		mes "∠∪∑ ∪ ∀⊆∝ ⊃ ∽";
		mes "￢∀∑ ∈ ∈∈∪ ∩ ";
		mes "∋⊇∫ ∪ ∝?∮ ∩ ∫";
		next;
		mes "[学者]";
		mes "∬?∑ ∪ ∈⊇∵ ∠ ";
		mes "∝∋￢ ⊇ ∵⊂∬";
		mes "∩?￢ ⊃ ⊃?∃ ? ";
		close;
	}
	mes "[学者]";
	mes "お前はどうしてここに来た？";
	mes "お前は妖精とは異なる種なのか？";
	mes "この場所はお前が立ち入って";
	mes "良い場所ではない。";
	next;
	mes "[学者]";
	mes "この場所は神聖なる我等の大地、";
	mes "^0000ffヨトゥンへイム^000000。";
	mes "軽い好奇心で立ち寄られては困る。";
	close;
}

manuk.gat,169,260,3	script	青年	455,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[青年]";
		mes "∵￢∋ ∬ ∽￢∪ ∠ ";
		mes "∑∧∵ ∧ ⊂⊆∮";
		mes "∃∫∩ ∬ ∈∩∬ ⊇ ";
		mes "∬∀∬ ∈ ∀∠∃ ∩ ∝";
		mes "∵∝∪ ∀ ";
		close;
	}
	mes "[青年]";
	mes "我々サファ族は一心同体。";
	mes "何時いかなる時でも常に";
	mes "心は1つなのだ。";
	mes "そう、私がこうやって壁を";
	mes "見つめている時もな……";
	close;
}

manuk.gat,218,163,3	script	巨人の戦士	450,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[巨人の戦士]";
		mes "∵∬∈ ∠ ∽∈⊃ ∑ ∫";
		mes "∑⊇⊃ ⊃ ∀∩∫ ∃ ";
		mes "∵∃⊂ ∫ ∮∩∈ ∠ ";
		next;
		mes "[巨人の戦士]";
		mes "∮∵⊂ ⊆ ⊃⊃∝ ∫ ";
		mes "∵∽∃ ￢ ∀∽∝ ⊃ ∋";
		mes "∋∃∧ ? ∠∝∵ ∋ ∬∈";
		mes "∵∃∀ ∬ ∽∫∬ ∠ ";
		close;
	}
	mes "[巨人の戦士]";
	mes "最近、我等の周りを飛び回る";
	mes "小さな妖精どもが頻繁に現れる。";
	next;
	mes "[巨人の戦士]";
	mes "まぁ、奴らの出来る事といえば、";
	mes "遠くからチマチマと魔法で";
	mes "攻撃することくらいだ。";
	mes "面倒ではあるが怖くも何ともない。";
	mes "私が本気を出せば、";
	mes "一瞬で蹴散らすことができるしな。";
	close;
}

manuk.gat,266,199,5	script	巨人の戦士	450,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[巨人の戦士]";
		mes "∈∀∪ ⊂ ∽∀∑ ∧ ?";
		mes "∧∫∪ ∈ ∬∀∪ ⊂ ";
		mes "⊂∽⊇ ⊆ ∑∮∫ ∫ ⊂";
		mes "∬∮∋";
		close;
	}
	mes "[巨人の戦士]";
	mes "これだけのブラディウムの";
	mes "貯蓄があれば、一安心ではあるが";
	mes "またいつ底をつくとも限らん。";
	mes "もっと集めないとな。";
	close;
}

manuk.gat,225,129,5	script	学者	449,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[学者]";
		mes "∽⊂∋ ∩ ∬∠⊃ ? ∃?⊇";
		mes "∈∵⊆ ∧ ∩∀￢ ? ∫∬";
		mes "∧∪￢ ∀ ⊇∵∋ ￢ ∀?∋";
		mes "∈⊂∬ ∋ ∝∽";
		close;
	}
	mes "[学者]";
	mes "おっと！";
	mes "妖精かと思ったら違うのか！";
	mes "小さいから間違いそうになったよ。";
	next;
	mes "[学者]";
	mes "…";
	mes "……で、お前は何者だ？";
	mes "喋れるのか？";
	mes "我々の言葉はわかるのか？";
	mes "みればみるほど珍しい奴だな……。";
	close;
}

manuk.gat,286,147,3	script	青年	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[青年]";
		mes "∬∬∽ ∩ ∮∝∵ ∠ ∬";
		mes "∩∠￢ ∈ ∝∮∽ ∀ ⊆∮";
		mes "⊇∈∪ ∩ ∮⊆∑ ⊆ ∽￢";
		mes "∀∈∃ ∮ ∝∋⊇";
		next;
		mes "[青年]";
		mes "∮⊆∀ ⊃ ￢∮∽ ∩ ∝∋";
		mes "∮￢⊃ ⊆ ￢∝∠ ∋ ";
		mes "∠∵ ￢ ";
		close;
	}
	mes "[青年]";
	mes "この土地を開拓した";
	mes "我々の祖先達の苦労を";
	mes "私は忘れない。";
	mes "彼らの苦労を無駄にしない為にも";
	mes "我々も頑張らねばな。";
	next;
	mes "[青年]";
	mes "まずは、あのラフィネ族だとかいう";
	mes "妖精どもを追い払う術を";
	mes "考えなければいけないな。";
	close;
}

manuk.gat,183,185,5	script	青年	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[青年]";
		mes "⊃∑∠ ∫ ∫∋∽ ∮ ";
		mes "⊇∈ ⊂ ∃∀∩ ⊆";
		mes "∮∧∝ ⊂ ∩∬∫ ∈ ";
		mes "∀∬∮ ∠ ∮";
		next;
		mes "[青年]";
		mes "∑∮∫ ∧ ∝∵∪ ∫ ";
		mes "∃⊇∈ ∬ ∑∋∪ ∑ ";
		mes "∬∬⊂ ∀ ∽";
		close;
	}
	mes "[青年]";
	mes "『皆は一人の為に、";
	mes "一人は皆の為に』";
	mes "この言葉は、我が一族の信条だ。";
	next;
	mes "[青年]";
	mes "私もその教えに従い、";
	mes "皆と共に一丸となって働く！";
	mes "全てはサファ族のために！";
	close;
}

manuk.gat,256,143,3	script	巨人の戦士	450,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[巨人の戦士]";
		mes "⊂∫ ⊆ ∧∃⊇ ∬ ∽";
		mes "∀∑∈ ∈ ∽⊂∑ ∀ ￢";
		mes "∬∠ ∑ ∠ ⊂ ⊆ ∀⊃";
		close;
	}
	mes "[巨人の戦士]";
	mes "敵に勝利し、我々サファ族を";
	mes "守り続けることができるのであれば、";
	mes "我が身が砕けようとも惜しくない。";
	close;
}

manuk.gat,245,124,3	script	青年	455,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[青年]";
		mes "∀⊃∧ ⊂ ⊇∃∽ ⊇ ⊃";
		mes "∑∧∵ ∩∧∫";
		mes "∝∠? ∩ ∫∧ ∪ ";
		mes "∃∪⊆ ∪ ∃∬∬";
		mes "∩∝∫ ⊂ ∽⊂⊃ ∑ ";
		close;
	}
	mes "[青年]";
	mes "お前達の目には、";
	mes "我々の戦いがどのように映るのか、";
	mes "わからないが、我々は命がけの";
	mes "戦いをしているのだ。";
	mes "それだけは覚えておいて欲しい。";
	close;
}

manuk.gat,103,354,5	script	戦士	450,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[戦士]";
		mes "∀⊇∪　￢　∧∵∬　⊇";
		mes "∬∀∽　⊆　⊆∠⊇　⊆　?";
		close;
	}
	mes "[戦士]";
	mes "ここは、";
	mes "ベルゲルミルの子孫である";
	mes "サファ族の街マヌクです。";
	close;
}

manuk.gat,122,354,3	script	戦士	450,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[戦士]";
		mes "∀⊇∪　￢　∧∵∬ ⊇";
		mes "∬∀∽　⊆　⊆∠⊇　⊆　?";
		close;
	}
	mes "[戦士]";
	mes "ここは、";
	mes "ベルゲルミルの子孫である";
	mes "サファ族の街マヌクです。";
	close;
}

manuk.gat,99,334,5	script	工員	460,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "⊂∪∬　?　∋￢∬";
		mes "∫　∪∬⊃　∈∈";
		mes "∩∧∮　⊂　∩∃⊂　∀　∮⊆";
		mes "∑∧?　∃　∽∈?　∈　∬∪∋";
		mes "∧　∝??　∧　∽∮∪　∀　∝?";
		mes "￢⊆⊂　?　∑∵⊇";
		close;
	}
	mes "[工員]";
	mes "俺達サファ族には";
	mes "それぞれ役割があるんだよ。";
	mes "ちなみに俺は^0000ffピオム^000000っていう役割だ。";
	mes "ブラディウム工場の工員だとか";
	mes "マヌクでの労働を担当しているんだ。";
	next;
	mes "[工員]";
	mes "兵役を担当しているのが^0000ffガルトン^000000だ。";
	mes "彼らがいるから";
	mes "俺達は安心して生活できるんだ。";
	mes "本当に尊敬しているぜ。";
	next;
	mes "[工員]";
	mes "ほかにも色々な役割があるんだぜ。";
	close;
}

manuk.gat,103,311,3	script	工員	455,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "∧∀∪　⊇　";
		mes "∧∫∠　∪　∈∋∈　∩　∬";
		close;
	}
	mes "[工員]";
	mes "あ、足が……";
	mes "もうブラディウムを注射する時間か……";
	close;
}

manuk.gat,293,203,3	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "∋∃∈ ⊆ ∫";
		mes "∽⊇∠　?　￢∀⊃　￢";
		mes "∠∈⊇　∫　∫∽∧　∫";
		mes "⊃⊂￢　￢　⊆∬⊇　∋　∵∈";
		close;
	}
	mes "[工員]";
	mes "ああっ、気をつけて!!";
	mes "これはサファ族の命ともいえる";
	mes "ブラディウムなんだ！";
	mes "取り扱い要注意！";
	close;
}

manuk.gat,253,173,3	script	学者	449,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[学者]";
		mes "⊂∧∠　⊃　∽∑";
		mes "∑∫∧　∬　∮⊃∫　∋";
		mes "∠?⊆　∮　∮∈∈　∮　∫∑";
		mes "∵⊃⊃　∀　∠∠⊂ ∃　∩⊃";
		close;
	}
	mes "[学者]";
	mes "あの銅像が見えますか？";
	mes "あのお方は、我がサファ族の先祖";
	mes "ベルゲルミル様です。";
	mes "威風堂々としていて";
	mes "素晴らしいと思いませんか？";
	close;
}

man_in01.gat,346,135,0	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "Π∫〓　∫　Π∫∃　⊇　〓∽∀";
		mes "〓∩∬　〓　∀⊆〓　Σ　";
		mes "∀〓∧　∃　∫∀∝　∈　";
		close;
	}
	mes "[工員]";
	mes "ちゃんとバルブの";
	mes "チェックをしないとね。";
	mes "この前、うっかり開けっ放しにして";
	mes "大事故になりそうになったんだ～。";
	close;
}

man_in01.gat,393,134,3	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "∈⊃⊆　⊃　⊆〓∩";
		mes "∧∪⊃　∩";
		close;
	}
	mes "[工員]";
	mes "ここは我々にとって、";
	mes "重要な施設なのだ。";
	mes "ゆえに、徹底的な危機管理が";
	mes "必要なのだ。";
	next;
	mes "[工員]";
	mes "恥ずかしい話だが、";
	mes "この前、工員の一人のミスで";
	mes "大事故になりそうになったのだ。";
	mes "再発防止を徹底しなくてな。";
	close;
}

man_in01.gat,377,143,5	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "〓∽∋　Σ　∩∪∧";
		mes "∪　∠⊆∩　Σ　Π　Σ ";
		close;
	}
	mes "[工員]";
	mes "動作に異常なし……と。";
	close;
}

man_in01.gat,333,128,5	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "⊆〓〓　⊃　〓∩Π";
		mes "∠　∩Π⊇";
		close;
	}
	mes "[工員]";
	mes "ねぇねぇ！";
	mes "君の世界には巨大な";
	mes "人型兵器があるって本当!?";
	next;
	mes "[工員]";
	mes "来るべき決戦の時、";
	mes "神殿が真っ二つに分かれ、";
	mes "その中から現れるって聞いたよ！";
	next;
	mes "[工員]";
	mes "口から荒れ狂う風を吐き、";
	mes "角からは雷を発し、";
	mes "拳からは数万の刃物を放ち、";
	mes "胸からは熱い炎が出るらしいね！";
	next;
	mes "[工員]";
	mes "この前、アルナベルツって";
	mes "国から来た人が言っていたんだ。";
	mes "いいなあ、見たいなあ。";
	close;
}

man_in01.gat,336,128,5	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "〓∩∧ ⊇ ∈⊃";
		close;
	}
	mes "[工員]";
	mes "この前、ミッドガルドから来たという";
	mes "研究者達がここを見学して行ったぞ。";
	mes "その研究者達にミッドガルドの話を";
	mes "色々と聞けて面白かったぜ。";
	close;
}

man_in01.gat,283,288,3	script	工員	454,{
	if(!equippeditem(2782) || YGG_1QUE < 100) {
		mes "[工員]";
		mes "∫Π⊂　∫ 〓∫∃";
		mes "∧　∽⊆∈　∠　∽Σ　∠";
		next;
		mes "[工員]";
		mes "∝〓⊇　∠　∈⊇〓";
		mes "∩　∠∠∋　Σ　Σ";
		close;
	}
	mes "[工員]";
	mes "うん、なかなか質のよい";
	mes "ブラディウムだ。";
	next;
	mes "[工員]";
	mes "ブラディウムは";
	mes "私たちの命だからね。";
	close;
}
