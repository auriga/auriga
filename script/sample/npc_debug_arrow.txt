//
// 矢製作スキルができるまでの間の、弓矢使い救済NPCに使ってやって下さい (^^;
// ただ単に店NPCじゃ詰まらないので、簡単なイベントに。
// 値段は、適当デス。	write by huge
//

payon.gat,98,57,6	script	ラウリィ	86,{
	if(getbaseclass(Class) != CLASS_AC && getbaseclass(Class) != CLASS_TF) {
		mes "[ラウリィ]";
		mes "やぁ、初めまして。旅人さん。";
		mes "今日も天気がいいですねっ。";
		mes "川の流れも穏やかだ。";
		close;
	}
	if(ARROW_NPC == 0) {
		mes "[ラウリィ]";
		mes "やぁ、初めまして。旅人さん。";
		mes "おや、あなたは弓使いのようですね。";
		mes "私も昔、ハンターだったんですよ。";
		next;
		mes "[ラウリィ]";
		mes "でも、とある事情で退職しました。";
		mes "あの頃は、毎日が楽しかったなぁ・・・。";
		mes "あ、そうだ！。";
		next;
		mes "[ラウリィ]";
		mes "私が昔使っていた矢の余りを";
		mes "あなたにあげましょう。";
		mes "ただ、私も退職した身なので少々お代は頂きますが。";
		next;
		mes "[ラウリィ]";
		mes "この街の中央広場に居るおじさんに";
		mes "全部預けてるので、話しかけてみてください。";
		mes "私からあなたの事を伝えておきます";
		mes "ので。";
		set ARROW_NPC,1;
		close;
	}
	mes "[ラウリィ]";
	mes "やぁ、また会いましたね。旅人さん。";
	mes "バドラックおじさんには会えました？";
	mes "この街の中央広場に居ますよ。";
	close;
}

payon.gat,100,121,3	script	バドラック	85,{
	if(ARROW_NPC == 0) {
		if(Sex) {
			mes "[バドラック]";
			mes "誰だお前は！";
			mes "気安く話しかけんじゃねぇ！";
			mes "俺は、男には興味はねぇんだよ。";
			mes "さっさと立ち去りな！";
		}
		else {
			mes "[バドラック]";
			mes "よぉ、ねぇちゃん。";
			mes "おじさんと一杯やらないかい？";
		}
		close;
	}
	mes "[バドラック]";
	mes "あんたかラウリィの知り合いってのは。";
	mes "アイツは、あー見えても結構な腕でな、";
	mes "現役の頃は、弓使いでその名を知らない";
	mes "やつは居ないってくらいだったぜ。";
	mes "だから、世界中の矢が揃ってやがるぜ！";
	next;
	mes "[バドラック]";
	mes "じゃ、さっそく矢を選んでくれ。";
	mes "ただし軽いモンだからまとめ売りだぞ。";
	next;
	switch(select("いらない",
	              "矢×1000 -> 1,000z",
	              "岩石の矢×500 -> 1,500z",
	              "錆びた矢×500 -> 1,500z",
	              "鋭い矢×500 -> 1,500z",
	              "鉄の矢×500 -> 1,500z",
	              "鋼鉄の矢×500 -> 1,500z",
	              "銀の矢×500 -> 1,500z",
	              "炎の矢×500 -> 2,500z",
	              "氷の矢×500 -> 2,500z",
	              "風の矢×500 -> 2,500z",
	              "水晶の矢×500 -> 2,500z",
	              "無形の矢×500 -> 2,500z",
	              "毒矢×500 -> 3,500z",
	              "カースアロー×500 -> 3,500z",
	              "スタンアロー×500 -> 3,500z",
	              "スリープアロー×500 -> 3,500z",
	              "フラッシュアロー×500 -> 3,500z",
	              "サイレンスアロー×500 -> 3,500z",
	              "影矢×500 -> 3,500z",
	              "破魔矢×100 -> 40,000z",
	              "オリデオコンの矢×100 -> 50,000z")) {
	case 1:		// cancel
		mes "[バドラック]";
		mes "いらんなら最初から話しかけんな！";
		close;
	case 2:		// 矢
		set '@zeny,1000;
		set '@itemid,1750;
		set '@amount,1000;
		break;
	case 3:		// 岩石の矢
		set '@zeny,1500;
		set '@itemid,1756;
		set '@amount,500;
		break;
	case 4:		// 錆びた矢
		set '@zeny,1500;
		set '@itemid,1762;
		set '@amount,500;
		break;
	case 5:		// 鋭い矢
		set '@zeny,1500;
		set '@itemid,1764;
		set '@amount,500;
		break;
	case 6:		// 鉄の矢
		set '@zeny,1500;
		set '@itemid,1770;
		set '@amount,500;
		break;
	case 7:		// 鋼鉄の矢
		set '@zeny,1500;
		set '@itemid,1753;
		set '@amount,500;
		break;
	case 8:		// 銀の矢
		set '@zeny,1500;
		set '@itemid,1751;
		set '@amount,500;
		break;
	case 9:		// 炎の矢
		set '@zeny,2500;
		set '@itemid,1752;
		set '@amount,500;
		break;
	case 10:	// 氷の矢
		set '@zeny,2500;
		set '@itemid,1759;
		set '@amount,500;
		break;
	case 11:	// 風の矢
		set '@zeny,2500;
		set '@itemid,1755;
		set '@amount,500;
		break;
	case 12:	// 水晶の矢
		set '@zeny,2500;
		set '@itemid,1754;
		set '@amount,500;
		break;
	case 13:	// 無形の矢
		set '@zeny,2500;
		set '@itemid,1757;
		set '@amount,500;
		break;
	case 14:	// 毒矢
		set '@zeny,3500;
		set '@itemid,1763;
		set '@amount,500;
		break;
	case 15:	// カースアロー
		set '@zeny,3500;
		set '@itemid,1761;
		set '@amount,500;
		break;
	case 16:	// スタンアロー
		set '@zeny,3500;
		set '@itemid,1758;
		set '@amount,500;
		break;
	case 17:	// スリープアロー
		set '@zeny,3500;
		set '@itemid,1768;
		set '@amount,500;
		break;
	case 18:	// フラッシュアロー
		set '@zeny,3500;
		set '@itemid,1760;
		set '@amount,500;
		break;
	case 19:	// サイレンスアロー
		set '@zeny,3500;
		set '@itemid,1769;
		set '@amount,500;
		break;
	case 20:	// 影矢
		set '@zeny,3500;
		set '@itemid,1767;
		set '@amount,500;
		break;
	case 21:	// 破魔矢
		set '@zeny,40000;
		set '@itemid,1766;
		set '@amount,100;
		break;
	case 22:	// オリデオコンの矢
		set '@zeny,50000;
		set '@itemid,1765;
		set '@amount,100;
		break;
	}
	if(Zeny < '@zeny) {
		mes "[バドラック]";
		mes "持ち金が足らんようだな。。";
		mes "出直してこいや。";
		mes "俺はいつでもここに居るからな。";
		close;
	}
	if(!checkweight('@itemid,'@amount)) {
		mes "[バドラック]";
		mes "重量を軽くしてから来い。";
		close;
	}
	set Zeny,Zeny-'@zeny;
	getitem '@itemid,'@amount;
	mes "[バドラック]";
	mes "まいどありー。";
	close;
}
