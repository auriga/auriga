// Card removal NPC by TyrNemesis^ 日本語訳：胡蝶蘭
prt_in.gat,28,73,4	script	賢い老女	78,{
	mes "[賢い老女]";
	mes "いい天気だね、若いの。";
	mes "ところで、アタシは武具に装着している";
	mes "カードを取り外す力を持っているけど、";
	mes "力を貸そうかね？";
	next;
	switch(select("お願いします","いくらかかるんですか？","必要ないです")) {
	case 3:
		break;
	case 2:
		mes "[賢い老女]";
		mes "そうだね、";
		mes "まず基本料金として^4040FF200000z^000000。";
		mes "そしてカード１枚につき^4040FF25000z^000000貰うよ。";
		mes "あとは、魔法を使うために^4040FF星のかけら^000000と";
		mes "^4040FFイエロージェムストーン^000000が１つずつ必要だよ。";
		next;
		if(select("お願いします","必要ないです") == 2) {
			break;
		}
		// fall through
	case 1:
		mes "[賢い老女]";
		mes "よしよし。";
		mes "どの武具のカードを取り外すんだね？";
		next;
		set '@part,select("やっぱりやめます",
		                  getequipname(1),getequipname(2),getequipname(3),getequipname(4),getequipname(5),
		                  getequipname(6),getequipname(7),getequipname(8),getequipname(9),getequipname(10))-1;
		if('@part == 0)
			break;
		set '@count,getequipcardcnt('@part);
		if('@count <= 0) {
			mes "[賢い老女]";
			mes "若いの、カードがついてないよ。";
			mes "それじゃアタシの出番はないさ。";
			close;
		}
		mes "[賢い老女]";
		mes "この武具には" + '@count + "つカードがついてるね。";
		mes "^0000FF" + ('@count * 25000 + 200000) + "^000000Zenyと^0000FF星のかけら^000000と";
		mes "^0000FFイエロージェムストーン^000000が必要だよ。";
		next;
		if(select("わかりました、お願いします","やっぱりやめます") == 2) {
			break;
		}
		mes "[賢い老女]";
		mes "おっと言い忘れるところだったね。";
		mes "この魔法はとても難しいから、";
		mes "^FF4040失敗するかもしれない^000000のさ。";
		mes "失敗したらカードか武具、あるいは";
		mes "その両方が^FF4040破壊されてしまう^000000かも";
		mes "しれないんだよ。";
		next;
		mes "[賢い老女]";
		mes "失敗しても^FF4040返金はしない^000000から、";
		mes "一応聞いて置くけど、比べるなら";
		mes "カードと武具のどっちが大切だい？";
		next;
		set '@failtype,select("それならやめます","武具の方が大切です","カードの方が大切です")-1;
		if('@failtype == 0)
			break;
		mes "[賢い老女]";
		mes "よし、始めるよ。";
		next;
		if(Zeny < '@count * 25000 + 200000 || countitem(1000) < 1 || countitem(715) < 1) {
			mes "[賢い老女]";
			mes "必要なアイテムが足りないようだね。";
			mes "アイテムを揃えてもう一度来な。";
			close;
		}
		set Zeny,Zeny - ('@count * 25000 + 200000);
		delitem 1000,1;
		delitem 715,1;
		set '@rate,rand(100);
		if('@rate < 2) {
			failedremovecards '@part,0;
			mes "[賢い老女]";
			mes "残念だけど完全に失敗したよ。";
			mes "武具もカードも壊れてしまった。";
			close;
		}
		if('@rate < 6) {
			failedremovecards '@part,'@failtype;
			if('@failtype == 1) {
				mes "[賢い老女]";
				mes "頑張ったけどね、";
				mes "カードのほうは全部壊れてしまったよ。";
				mes "でも武具の方は無事だったよ。";
			}
			else {
				mes "[賢い老女]";
				mes "不運だったね。";
				mes "カードを取り外すのはうまくいったけど";
				mes "武具が壊れてしまったよ。";
			}
			close;
		}
		if('@rate < 10) {
			failedremovecards '@part,3;
			mes "[賢い老女]";
			mes "カードを取り外すのに失敗したよ。";
			mes "でも、不幸中の幸いさ。";
			mes "武具もカードも無事だよ。";
			close;
		}
		successremovecards '@part;
		mes "[賢い老女]";
		mes "うまくいったよ。";
		mes "これらが武具とアイテムさ。じゃあね。";
		close;
	}
	mes "[賢い老女]";
	mes "わかったよ。";
	mes "アタシの力が必要ならいつでも来な。";
	close;
}
