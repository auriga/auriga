// Produce NPC by kalen
// 仕様書
//
//・デフォルトの材料
//　作りたい属性武器の元武器を２個
//　属性を入れるなら属性石５個
//　星１つにつきかけらを１０個
//
//・元武器については、チェックが複雑になるのでS最低(店売り？)のみカウントします。
//　作成する武器もS最低(チェックしたIDと同一)なので、同じ武器を連続作成したり、
//　手持ちで既に属性武器があったりすると、材料として使われてしまう可能性があります。
//・'producer_idを自分の鯖の特定のキャラIDにあわせて使用してください。
//　「NPC作成」とかのキャラを作成しそれにあわせて使うといいでしょう。

prontera.gat,129,191,0	script	作成NPC	726,{
	if('producer_id == 0)
		set 'producer_id,150000;	// 作成者ID（デフォルト150000）
	mes "[作成NPC]";
	mes "こちらでは、属性武器の作成をしております。";
	mes "材料は作りたい装備が2つで、";
	mes "属性入りの場合は^0000ff属性石5つ^000000";
	mes "★入りの場合は^0000ff星のかけら10つ^000000";
	mes "で★1個となります。";
	next;
	switch(select("^ff0000必ずお読み下さい。^000000","短剣系列","片手剣系列","両手剣系列","槍系列","斧系列列","鈍器系列","ナックル系列")) {
	case 1:
		mes "[作成NPC]";
		mes "基本的に全部Sが最低のものでないと";
		mes "カウントされません。";
		mes "同じ武器を連続して作成すると";
		mes "一つ前に作ったものを";
		mes "材料にしてしまう事があります。";
		next;
		mes "[作成NPC]";
		mes "重要なItemや、作ったものは、";
		mes "かならず預けるか";
		mes "カートに入れてからお願いします。";
		mes "尚Itemが消えても補償はいたしません。";
		close;
	case 2:	// 短剣
		setarray '@id,1201,1204,1207,1210,1213,1216,1219,1222;
		break;
	case 3:	// 片手剣
		setarray '@id,1101,1104,1107,1110,1113,1122,1119,1123,1126,1129;
		break;
	case 4:	// 両手剣
		setarray '@id,1116,1151,1154,1157,1160,1163;
		break;
	case 5:	// 槍
		setarray '@id,1401,1404,1407,1451,1454,1457,1460,1463,1410;
		break;
	case 6:	// 斧
		setarray '@id,1301,1351,1354,1357,1360;
		break;
	case 7:	// 鈍器
		setarray '@id,1501,1504,1507,1510,1519,1513,1516,1522;
		break;
	case 8:	// ナックル
		setarray '@id,1801,1803,1805,1807,1809,1811;
		break;
	}

	// getitemname(0) は ""（空文字）が返るのでそのままselectに使って問題ない
	set '@n,select(getitemname('@id[0]),getitemname('@id[1]),getitemname('@id[2]),getitemname('@id[3]),getitemname('@id[4]),
	               getitemname('@id[5]),getitemname('@id[6]),getitemname('@id[7]),getitemname('@id[8]),getitemname('@id[9]))-1;
	if(countitem('@id['@n]) < 2) {
		mes "[作成NPC]";
		mes "材料が足りないようです。";
		close;
	}
	mes "[作成NPC]";
	mes "属性はどうしますか？";
	mes "属性を付与したい場合、";
	mes "^3355ff属性石5つ^000000が必要となります。";
	next;

	switch(select("いらない","^ff0000火属性^000000","^0033ff水属性^000000","^996600土属性^000000","^00cc66風属性^000000")) {
	case 1:
		break;
	case 2:
		set '@opt,3;
		set '@attr,994;
		break;
	case 3:
		set '@opt,1;
		set '@attr,995;
		break;
	case 4:
		set '@opt,2;
		set '@attr,997;
		break;
	case 5:
		set '@opt,4;
		set '@attr,996;
		break;
	}
	if('@attr > 0 && countitem('@attr) < 5) {
		mes "[作成NPC]";
		mes "材料が足りないようです。";
		close;
	}
	mes "[作成NPC]";
	mes "★はどうしますか？";
	mes "★を付与したい場合、";
	mes "^3355ff星のかけら10つ^000000が必要となります。";
	next;
	switch(select("いらない","★一つ","★二つ",('@opt == 0)? "★三つ": "")) {
	case 1:
		break;
	case 2:
		set '@opt,'@opt+0x500*1;
		set '@star,10;
		break;
	case 3:
		set '@opt,'@opt+0x500*2;
		set '@star,20;
		break;
	case 4:
		set '@opt,'@opt+0x500*3;
		set '@star,30;
		break;
	}
	if('@star > 0 && countitem(1000) < '@star) {
		mes "[作成NPC]";
		mes "材料が足りないようです。";
		close;
	}
	mes "[作成NPC]";
	mes "それでは、作成します。";
	next;
	delitem '@id['@n],2;
	delitem 1000,'@star;
	delitem '@attr,5;
	getitem2 '@id['@n],1,1,0,0,255,'@opt,'producer_id&0xffff,('producer_id>>16)&0xffff;
	mes "[作成NPC]";
	mes "完了しました。";
	close;
}
