//矢筒作成NPC
payon_in01.gat,5,134,4	script	発明家ゼックス	89,{
	if(Weight*100/MaxWeight >= 90) {
		mes "[発明家ゼックス]";
		mes "なんだかたくさん物を持って";
		mes "いるね。";
		mes "持ち物を減らして来たら";
		mes "いい話、してあげるんだけどな。";
		close;
	}
	mes "[発明家ゼックス]";
	mes "僕は天才発明家のゼックス！";
	mes "実は、歴史に残る大発明をしたんだ。";
	mes "その名^FF0000魔法の矢筒^000000!!";
	next;
	mes "[発明家ゼックス]";
	mes "数年間、来る日も来る日も……";
	mes "雨の日も、雪の日も……";
	mes "研究に研究を重ねてきた結果！";
	mes "なんと魔力を利用して矢を凝縮し、";
	mes "携帯できる^0000FF魔法の矢筒^000000を";
	mes "作ることに成功したんだ！";
	next;
	emotion 21;
	mes "[発明家ゼックス]";
	mes "これこそ、弓矢を使う人たちにとって";
	mes "喉から手が出るほど欲しかった";
	mes "ものに違いない！";
	mes "ふっふ～ん。";
	mes "我こそは偉大な発明家、ゼックス!!!";
	next;
	mes "[発明家ゼックス]";
	mes "さて、欲しい矢筒はあるかい？";
	mes "君の心をわしづかみにすること";
	mes "間違いなし！の品物だ。";
	next;
	switch (select("矢筒","鉄の矢筒","鋼鉄の矢筒","オリデオコンの矢筒","炎の矢筒","銀の矢筒","風の矢筒",
						"岩石の矢筒","水晶の矢筒","影の矢筒","無形の矢筒","錆びた矢筒")) {
		case 1:
			set '@arr,1750;
			set '@quiv,12004;
			break;
		case 2:
			set '@arr,1770;
			set '@quiv,12005;
			break;
		case 3:
			set '@arr,1753;
			set '@quiv,12006;
			break;
		case 4:
			set '@arr,1765;
			set '@quiv,12007;
			break;
		case 5:
			set '@arr,1752;
			set '@quiv,12008;
			break;
		case 6:
			set '@arr,1751;
			set '@quiv,12009;
			break;
		case 7:
			set '@arr,1755;
			set '@quiv,12010;
			break;
		case 8:
			set '@arr,1756;
			set '@quiv,12011;
			break;
		case 9:
			set '@arr,1754;
			set '@quiv,12012;
			break;
		case 10:
			set '@arr,1767;
			set '@quiv,12013;
			break;
		case 11:
			set '@arr,1757;
			set '@quiv,12014;
			break;
		case 12:
			set '@arr,1762;
			set '@quiv,12015;
			break;
	}
	if(countitem('@arr)<500 || Zeny<500) {
		mes "[発明家ゼックス]";
		mes "これは" +getitemname('@arr)+ "を";
		mes "500本入れることができる矢筒だよ。";
		mes "僕だけにできる特別な加工をしていて、";
		mes "500本そのまま持つより、これに";
		mes "入れた方が軽くなるという優れもの";
		mes "なんだ。";
		next;
		mes "[発明家ゼックス]";
		mes "どう？ 驚いたでしょ？";
		mes "まるで輝く宝石のような神秘の";
		mes "アイテム！ 僕の宝物さ！";
		mes "矢筒が要るなら" +getitemname('@arr)+ "500本と";
		mes "500Zenyを持ってきて。";
		mes "矢筒に入れてあげるよ。";
		close;
	}
	mes "[発明家ゼックス]";
	mes "おお、ちゃんと必要な本数を";
	mes "持っているね。";
	mes "これに入れて使ってみるかい？";
	mes "^FF0000500Zeny^000000で";
	mes getitemname('@arr)+ "500本を";
	mes "この矢筒に入れてあげるよ。";
	next;
	switch (select("組み合わせ可能なだけ入れてもらう","矢筒1個分だけ入れてもらう","やめる")) {
	case 1:
		set '@have,countitem('@arr);	//矢所持数
		set '@max,'@have/500;		//最大交換数
		set '@price,'@max*500;		//料金
		mes "[発明家ゼックス]";
		mes "所持している" +getitemname('@arr)+ " :";
		mes "^0000FF" +'@have+ " 本^000000";
		mes "組み合わせ可能な" +getitemname('@quiv)+ " :";
		mes "^0000FF" +'@max+ " 個^000000";
		mes "組み合わせに必要なZeny :";
		mes "^0000FF" +'@price+ " Zeny^000000";
		next;
		mes "交換しますか？";
		next;
		if(select("交換する","交換しない")==2) {
			mes "[発明家ゼックス]";
			mes "なんだ……";
			mes "せっかくすごい発明をしたのに……";
			close;
		}
		break;
	case 2:
		set '@max,1;
		set '@price,500;
		break;
	case 3:
		mes "[発明家ゼックス]";
		mes "なんだ……";
		mes "せっかくすごい発明をしたのに……";
		close;
	}
	delitem '@arr,'@max*500;
	set Zeny,Zeny-'@price;
	getitem '@quiv,'@max;
	mes "[発明家ゼックス]";
	mes "ほら、これだよ。";
	mes "そこで、^0000FF注意点^000000が一つだけ";
	mes "あるからよく覚えておいてね。";
	mes "^FF0000重量が90%を超えると、この矢筒は";
	mes "使えなくなるから気をつけて。^000000";
	close;
}
