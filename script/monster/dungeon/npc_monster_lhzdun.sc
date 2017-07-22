//= Auriga Script ==============================================================
// Ragnarok Online Lighthalzen Dungeon Monster Spawn Script　　Ep 15.2
//==============================================================================

//============================================================
// 生体工学研究所 01 - lhz_dun01.gat
//------------------------------------------------------------
lhz_dun01.gat,0,0,0,0		monster	ウィレス		1627,30,5000,0,0
lhz_dun01.gat,0,0,0,0		monster	リムーバー		1682,380,5000,0,0

//============================================================
// 生体工学研究所 02 - lhz_dun02.gat
//------------------------------------------------------------
lhz_dun02.gat,0,0,0,0		monster	ウィレス		1627,26,5000,0,0
lhz_dun02.gat,0,0,0,0		monster	イグニゼム=セニア	1652,46,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	ヒュッケバイン=トリス	1653,56,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	アルマイア=デュンゼ	1654,56,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	イレンド=エベシ		1655,46,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	カヴァク=イカルス	1656,26,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	ラウレル=ヴィンダー	1657,36,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	イグニゼム=セニア	1652,4,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	ヒュッケバイン=トリス	1653,4,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	アルマイア=デュンゼ	1654,4,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	イレンド=エベシ		1655,4,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	カヴァク=イカルス	1656,4,5000,0,1
lhz_dun02.gat,150,150,56,54	monster	ラウレル=ヴィンダー	1657,4,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	イグニゼム=セニア	1652,10,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	ヒュッケバイン=トリス	1653,10,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	アルマイア=デュンゼ	1654,10,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	イレンド=エベシ		1655,10,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	カヴァク=イカルス	1656,10,5000,0,1
lhz_dun02.gat,150,150,105,90	monster	ラウレル=ヴィンダー	1657,10,5000,0,1
lhz_dun02.gat,0,0,0,0		monster	ジェミニ-S58		1681,10,1800000,0,0
lhz_dun02.gat,0,0,0,0		monster	イグニゼム=セニア	1658,1,7200000,5400000,1
//lhz_dun02.gat,0,0,0,0		monster	ウィッシュ=マスコット	2441,1,14400000,18000000,1
//lhz_dun02.gat,0,0,0,0		monster	アーティス=マスコット	2442,1,14400000,18000000,1

//============================================================
// 生体工学研究所 03 - lhz_dun03.gat
//------------------------------------------------------------
lhz_dun03.gat,0,0,0,0	monster	セイレン=ウィンザー	1634,20,20000,0,0
lhz_dun03.gat,0,0,0,0	monster	エレメス=ガイル		1635,10,20000,0,0
lhz_dun03.gat,0,0,0,0	monster	ハワード=アルトアイゼン	1636,10,20000,0,0
lhz_dun03.gat,0,0,0,0	monster	マーガレッタ=ソリン	1637,20,20000,0,0
lhz_dun03.gat,0,0,0,0	monster	セシル=ディモン		1638,20,20000,0,0
lhz_dun03.gat,0,0,0,0	monster	カトリーヌ=ケイロン	1639,20,20000,0,0
lhz_dun03.gat,114,138,12,16	monster	セイレン=ウィンザー	1640,1,600000,0,1
lhz_dun03.gat,163,138,12,16	monster	ハワード=アルトアイゼン	1642,1,600000,0,1
lhz_dun03.gat,139,158,20,11	monster	エレメス=ガイル		1641,1,600000,0,1
lhz_dun03.gat,139,117,20,11	monster	セシル=ディモン		1644,1,600000,0,1
lhz_dun03.gat,138,138,36,34	monster	マーガレッタ=ソリン	1643,1,600000,0,1
lhz_dun03.gat,138,138,36,34	monster	カトリーヌ=ケイロン	1645,1,600000,0,1

lhz_dun03.gat,0,0,0	script	#LhzMVP3	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer6000000:
OnTimer6300000:
OnTimer6600000:
OnTimer6900000:
OnTimer7200000:
OnTimer7500000:
	if(rand(6))
		end;
OnTimer7800000:
	stopnpctimer;
	switch(rand(6)) {
	case 0: set '@x,140; set '@y,232; break;
	case 1: set '@x,75; set '@y,138; break;
	case 2: set '@x,140; set '@y,87; break;
	case 3: set '@x,205; set '@y,140; break;
	case 4: set '@x,123; set '@y,137; break;
	case 5: set '@x,157; set '@y,137; break;
	}
	monster "lhz_dun03.gat",'@x,'@y,"--ja--",1646+rand(6),1,"#LhzMVP3::OnKilled";
	end;
OnKilled:
	switch(rand(6)) {
	case 0: set '@x,183; set '@y,97; break;
	case 1: set '@x,97; set '@y,96; break;
	case 2: set '@x,47; set '@y,139; break;
	case 3: set '@x,231; set '@y,140; break;
	case 4: set '@x,139; set '@y,211; break;
	case 5: set '@x,139; set '@y,259; break;
	}
	monster "lhz_dun03.gat",'@x,'@y,"--ja--",1640+rand(6),1;
	initnpctimer;
	end;
}

//============================================================
// 生体工学研究所 04 - lhz_dun04.gat
//------------------------------------------------------------
lhz_dun04.gat,0,0,0,0	monster	ランデル=ロレンス	2221,40,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	エミュール=プラメール	2222,30,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	セリア=アルデ	2223,30,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	チェン=リウ	2224,20,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	ガーティー=ウー	2225,20,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	アルフォシオ=バジル	2226,10,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	トレンティーニ	2227,10,40000,0,0
lhz_dun04.gat,0,0,0,0	monster	ランデル=ロレンス	2228,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	エミュール=プラメール	2229,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	セリア=アルデ	2230,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	チェン=リウ	2231,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	ガーティー=ウー	2232,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	アルフォシオ=バジル	2233,1,600000,0,1
lhz_dun04.gat,0,0,0,0	monster	トレンティーニ	2234,1,600000,0,1

lhz_dun04.gat,0,0,0	script	#LhzMVP4	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer6000000:
OnTimer6300000:
OnTimer6600000:
OnTimer6900000:
OnTimer7200000:
OnTimer7500000:
	if(rand(6))
		end;
OnTimer7800000:
	stopnpctimer;
	switch(rand(7)) {
	case 0: set '@x,77; set '@y,251; break;
	case 1: set '@x,147; set '@y,224; break;
	case 2: set '@x,219; set '@y,219; break;
	case 3: set '@x,244; set '@y,120; break;
	case 4: set '@x,149; set '@y,41; break;
	case 5: set '@x,53; set '@y,109; break;
	case 6: set '@x,149; set '@y,151; break;
	}
	monster "lhz_dun04.gat",'@x,'@y,"--ja--",2235+rand(7),1,"#LhzMVP4::OnKilled";
	end;
OnKilled:
	switch(rand(7)) {
	case 0: set '@x,77; set '@y,251; break;
	case 1: set '@x,147; set '@y,224; break;
	case 2: set '@x,219; set '@y,219; break;
	case 3: set '@x,244; set '@y,120; break;
	case 4: set '@x,149; set '@y,41; break;
	case 5: set '@x,53; set '@y,109; break;
	case 6: set '@x,149; set '@y,151; break;
	}
	monster "lhz_dun04.gat",'@x,'@y,"--ja--",2228+rand(7),1;
	initnpctimer;
	end;
}
