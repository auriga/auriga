//==================================================================================
// Dungeon Warp Point Script   2005-06-28(mod by kia)
//==================================================================================

//-------------------------------------------
// warp0xxx 	MAPの区切り  	
// warp01xx 	街へ         	
// warp02xx 	GvGルームへ  	
// warp03xx 	砦へ         	
// warp04xx 	ダンジョンへ 	(使わない)
// warp05xx 	フィールドへ 	
// warp06xx 	JOBステージへ	
// warp07xx 	PvPステージへ	
// warp1xxx 	街           	(使わない)
// warp2xxx 	GvGルーム    	(使わない)
// warp3xxx 	GvG 砦       	(使わない)
// warp31xx 	GvG 砦１     	
// warp32xx 	GvG 砦２     	
// warp33xx 	GvG 砦３     	
// warp34xx 	GvG 砦４     	
// warp35xx 	GvG 砦５     	
// warp4xxx 	ダンジョン   	
// warp5xxx 	フィールド   	(使わない)
// warp6xxx 	JOBステージ  	(使わない)
// warp7xxx 	PvPステージ  	(使わない)
// warp71xxx	PvPステージ１	
// warp72xxx	PvPステージ２	
// warp73xxx	PvPステージ３	
// warp74xxx	PvPステージ４	
// warp75xxx	PvPステージ５	
// warp76xxx	PvPステージ６	
// warp77xxx	PvPステージ７	
// warp78xxx	PvPステージ８	
//-------------------------------------------
// #        	script warp	
//-------------------------------------------
// TAB :    	8
//-------------------------------------------


//==============================================================
// gefenia04.gat	ゲフェニア遺跡
// gefenia03.gat	ゲフェニア遺跡
// gefenia02.gat	ゲフェニア遺跡
// gefenia01.gat	ゲフェニア遺跡
// -----
//==============================================================



//==============================================================
// xmas_dun01.gat	おもちゃ工場倉庫
// xmas_dun02.gat	おもちゃ分類所
// -----
// xmas.gat		雪の街ルティエ
//==============================================================
xmas_dun01.gat,205,13,0		warp	xmaswarp0101		1,1,xmas.gat,143,311

xmas_dun01.gat,129,130,0	warp	xmaswarp4001		1,1,xmas_dun02.gat,131,130
xmas_dun02.gat,129,130,0	warp	xmaswarp4002		1,1,xmas_dun01.gat,132,130



//==============================================================
// anthell01.gat	蟻地獄ダンジョン B1F
// anthell02.gat	蟻地獄ダンジョン B2F
// -----
// moc_fild20.gat	次元の狭間 01
//==============================================================
//anthell01.gat,35,267,0	warp	anthellwarp0501		1,1,moc_fild04.gat,213,327
//anthell02.gat,171,169,0	warp	anthellwarp0502		1,2,moc_fild04.gat,213,327
//anthell01.gat,35,267,0		script	#anthellwarp0501	45,1,1,{
//	if(ANTHELL_FLAG)
//		warp "moc_fild15.gat",251,248;
//	else
//		warp "moc_fild04.gat",213,327;
//	end;
//}
//anthell02.gat,171,169,0		script	#anthellwarp0502	45,1,2,{
//	if(ANTHELL_FLAG)
//		warp "moc_fild04.gat",213,327;
//	else
//		warp "moc_fild15.gat",251,248;
//	end;
//}
//anthell01.gat,35,267,0	warp	anthellwarp0501		1,1,moc_fild20.gat,161,144
//anthell02.gat,171,170,0	warp	anthellwarp0502		1,1,moc_fild20.gat,333,315
anthell01.gat,35,267,0		warp	anthellwarp0501		1,1,cmd_fild08.gat,330,355
anthell02.gat,171,170,0		warp	anthellwarp0502		1,1,cmd_fild08.gat,344,82

anthell01.gat,253,32,0		warp	anthellwarp4001		2,1,anthell02.gat,34,263
anthell02.gat,32,267,0		warp	anthellwarp4001		2,2,anthell01.gat,253,35



//==============================================================
// gef_dun00.gat	ゲフェン地下ダンジョン B1F
// gef_dun01.gat	ゲフェン地下ダンジョン B2F
// gef_dun02.gat	ゲフェニアダンジョン
// gef_dun03.gat	ゲフェニアダンジョン
// -----
// moc_fild01.gat	ソクラド砂漠 01 ～ 19
//==============================================================
gef_dun00.gat,104,103,0		warp	geffenwarp0101		3,3,gef_tower.gat,153,31

gef_dun00.gat,107,169,0		warp	geffenwarp4001		2,1,gef_dun01.gat,115,236
gef_dun01.gat,115,240,0		warp	geffenwarp4002		2,2,gef_dun00.gat,107,165
gef_dun01.gat,197,38,0		warp	geffenwarp4003		2,1,gef_dun02.gat,106,132
gef_dun02.gat,106,134,0		warp	geffenwarp4004		2,1,gef_dun01.gat,197,40
//gef_dun02.gat,215,67,0		warp	geffenwarp4005		2,1,gef_dun03.gat,203,200
//gef_dun03.gat,203,204,0		warp	geffenwarp4006		2,1,gef_dun02.gat,215,63



//==============================================================
// iz_dun00.gat		イズルード海底洞窟1層
// iz_dun01.gat		イズルード海底洞窟2層
// iz_dun02.gat		イズルード海底洞窟3層
// iz_dun03.gat		イズルード海底洞窟4層
// iz_dun04.gat		イズルード海底神殿
// iz_dun05.gat		イズルード海底都市
// -----
// izlu2dun.gatt	バイラン島
//==============================================================
iz_dun00.gat,168,173,0		warp	izludewarp0501		3,3,izlu2dun.gat,108,88

iz_dun00.gat,352,342,0		warp	izludewarp4001		5,2,iz_dun01.gat,253,252
iz_dun01.gat,253,258,0		warp	izludewarp4002		2,2,iz_dun00.gat,352,337
iz_dun00.gat,39,41,0		warp	izludewarp4003		5,2,iz_dun01.gat,41,37
iz_dun01.gat,41,32,0		warp	izludewarp4004		2,2,iz_dun00.gat,39,46
iz_dun01.gat,118,170,0		warp	izludewarp4005		5,2,iz_dun02.gat,236,204
iz_dun02.gat,236,198,0		warp	izludewarp4006		5,3,iz_dun01.gat,118,165
iz_dun02.gat,339,331,0		warp	izludewarp4007		2,2,iz_dun03.gat,32,63
iz_dun03.gat,29,63,0		warp	izludewarp4008		2,2,iz_dun02.gat,339,328
iz_dun03.gat,264,245,0		warp	izludewarp4009		1,2,iz_dun04.gat,26,27
iz_dun04.gat,26,24,0		warp	izludewarp4010		2,2,iz_dun03.gat,261,245
iz_dun05.gat,141,188,0		warp	izludewarp4011		1,1,iz_dun04.gat,129,225



//==============================================================
// in_sphinx1.gat	スフィンクスダンジョン B1F
// in_sphinx2.gat	スフィンクスダンジョン B2F
// in_sphinx3.gat	スフィンクスダンジョン B3F
// in_sphinx4.gat	スフィンクスダンジョン B4F
// in_sphinx5.gat	スフィンクスダンジョン B5F
// -----
// moc_fild01.gat	ソクラド砂漠 01 ～ 19
//==============================================================
in_sphinx1.gat,288,6,0		warp	sphinxwarp0501		5,1,moc_fild19.gat,100,99

in_sphinx1.gat,80,191,0		warp	sphinxwarp4001		2,1,in_sphinx2.gat,149,81
in_sphinx2.gat,149,77,0		warp	sphinxwarp4002		3,2,in_sphinx1.gat,80,189
in_sphinx2.gat,276,272,0	warp	sphinxwarp4003		1,3,in_sphinx3.gat,210,54
in_sphinx3.gat,210,57,0		warp	sphinxwarp4004		4,1,in_sphinx2.gat,274,272
in_sphinx3.gat,35,227,0		warp	sphinxwarp4005		2,4,in_sphinx3.gat,62,227
in_sphinx3.gat,60,227,0		warp	sphinxwarp4006		1,4,in_sphinx3.gat,32,227
in_sphinx3.gat,70,111,0		warp	sphinxwarp4007		1,1,in_sphinx3.gat,70,81
in_sphinx3.gat,70,83,0		warp	sphinxwarp4008		4,1,in_sphinx3.gat,70,113
in_sphinx3.gat,12,69,0		warp	sphinxwarp4009		4,1,in_sphinx4.gat,10,222
in_sphinx4.gat,10,224,0		warp	sphinxwarp4010		2,1,in_sphinx3.gat,12,71
in_sphinx4.gat,120,113,0	warp	sphinxwarp4011		4,2,in_sphinx5.gat,100,99
in_sphinx5.gat,100,96,0		warp	sphinxwarp4012		4,2,in_sphinx4.gat,120,116
in_sphinx5.gat,11,16,0		warp	sphinxwarp4013		3,1,in_sphinx5.gat,189,181
in_sphinx5.gat,11,183,0		warp	sphinxwarp4014		3,1,in_sphinx5.gat,11,18
in_sphinx5.gat,189,16,0		warp	sphinxwarp4015		3,1,in_sphinx5.gat,11,181
in_sphinx5.gat,16,188,0		warp	sphinxwarp4016		1,3,in_sphinx5.gat,181,188
in_sphinx5.gat,16,10,0		warp	sphinxwarp4017		1,3,in_sphinx5.gat,181,10
in_sphinx5.gat,183,10,0		warp	sphinxwarp4018		1,3,in_sphinx5.gat,18,188
in_sphinx5.gat,183,188,0	warp	sphinxwarp4019		1,3,in_sphinx5.gat,18,10
in_sphinx5.gat,189,183,0	warp	sphinxwarp4020		3,1,in_sphinx5.gat,189,18



//==============================================================
// moc_pryd01.gat	ピラミッドダンジョン 1F
// moc_pryd02.gat	ピラミッドダンジョン 2F
// moc_pryd03.gat	ピラミッドダンジョン 3F
// moc_pryd04.gat	ピラミッドダンジョン 4F
// moc_pryd05.gat	ピラミッドダンジョン B2F
// moc_pryd06.gat	ピラミッドダンジョン B3F
// -----
// moc_ruins.gat	モロク - ピラミッド周辺
// moc_prydb1.gat	シーフギルド
//==============================================================
moc_pryd01.gat,195,9,0		warp	pyramidwarp0101		2,5,moc_ruins.gat,60,161
moc_pryd05.gat,94,98,0		warp	pyramidwarp0601		2,1,moc_prydb1.gat,100,57

moc_pryd01.gat,10,195,0		warp	pyramidwarp4001		5,2,moc_pryd02.gat,10,192
moc_pryd02.gat,10,195,0		warp	pyramidwarp4002		5,2,moc_pryd01.gat,10,192
moc_pryd01.gat,90,109,0		warp	pyramidwarp4003		1,2,moc_prydb1.gat,100,185
moc_prydb1.gat,100,191,0	warp	pyramidwarp4004		2,2,moc_pryd01.gat,90,105
moc_pryd02.gat,100,99,0		warp	pyramidwarp4005		3,2,moc_pryd03.gat,100,92
moc_pryd03.gat,100,97,0		warp	pyramidwarp4006		3,2,moc_pryd02.gat,100,92
moc_pryd03.gat,12,15,0		warp	pyramidwarp4007		3,2,moc_pryd04.gat,12,18
moc_pryd04.gat,12,15,0		warp	pyramidwarp4008		3,2,moc_pryd03.gat,12,18
moc_pryd03.gat,15,187,0		warp	pyramidwarp4009		2,3,moc_pryd04.gat,18,187
moc_pryd04.gat,15,187,0		warp	pyramidwarp4010		2,3,moc_pryd03.gat,18,187
moc_pryd03.gat,184,11,0		warp	pyramidwarp4011		2,3,moc_pryd04.gat,181,11
moc_pryd04.gat,184,11,0		warp	pyramidwarp4012		2,3,moc_pryd03.gat,181,11
moc_pryd03.gat,188,184,0	warp	pyramidwarp4013		3,2,moc_pryd04.gat,188,181
moc_pryd04.gat,188,184,0	warp	pyramidwarp4014		3,2,moc_pryd03.gat,188,181
moc_pryd05.gat,223,9,0		warp	pyramidwarp4015		2,2,moc_pryd06.gat,192,10
moc_pryd06.gat,195,10,0		warp	pyramidwarp4016		2,3,moc_pryd05.gat,220,9



//==============================================================
// mjo_dun01.gat	ミョルニール廃鉱 B1F
// mjo_dun02.gat	ミョルニール廃鉱 B2F
// mjo_dun03.gat	ミョルニール廃鉱 B3F
// -----
// mjolnir_01.gat	ミョルニール山脈 01 ～ 12
//==============================================================
mjo_dun01.gat,52,14,0		warp	mjolnirwarp0501		4,2,mjolnir_02.gat,79,363

mjo_dun01.gat,14,283,0		warp	mjolnirwarp4001		2,4,mjo_dun02.gat,381,343
mjo_dun02.gat,384,343,0		warp	mjolnirwarp4002		2,4,mjo_dun01.gat,17,283
mjo_dun02.gat,31,21,0		warp	mjolnirwarp4003		1,1,mjo_dun03.gat,302,262
mjo_dun03.gat,302,264,0		warp	mjolnirwarp4004		1,1,mjo_dun02.gat,31,23
mjo_dun02.gat,39,21,0		warp	mjolnirwarp4005		1,1,mjo_dun03.gat,308,262
mjo_dun03.gat,308,264,0		warp	mjolnirwarp4006		1,1,mjo_dun02.gat,39,23



//==============================================================
// orcsdun01.gat	オーク地下洞窟
// orcsdun02.gat	オーク地下洞窟
// -----
// in_orcs01.gat	オーク村の室内
//==============================================================
orcsdun01.gat,32,172,0		warp	orcswarp0101		3,1,in_orcs01.gat,30,180
orcsdun02.gat,180,15,0		warp	orcswarp0102		2,1,in_orcs01.gat,108,112

orcsdun01.gat,183,8,0		warp	orcswarp4001		4,2,orcsdun02.gat,21,185
orcsdun02.gat,21,188,0		warp	orcswarp4002		8,2,orcsdun01.gat,183,11



//==============================================================
// pay_dun00.gat	フェイヨン地下洞窟 B1F
// pay_dun01.gat	フェイヨン地下洞窟 B2F
// pay_dun02.gat	フェイヨン地下洞窟 B3F
// pay_dun03.gat	フェイヨン地下寺院
// pay_dun04.gat	フェイヨン地下寺院
// -----
// pay_arche.gat	山岳の都市フェイヨン
//==============================================================
pay_dun00.gat,21,186,0		warp	payonwarp0101		2,2,pay_arche.gat,39,131

pay_dun00.gat,184,33,0		warp	payonwarp4001		2,7,pay_dun01.gat,19,33
pay_dun01.gat,15,33,0		warp	payonwarp4002		2,6,pay_dun00.gat,181,33
pay_dun01.gat,286,25,0		warp	payonwarp4003		2,7,pay_dun02.gat,19,63
pay_dun02.gat,16,63,0		warp	payonwarp4004		2,7,pay_dun01.gat,283,28
pay_dun02.gat,137,128,0		warp	payonwarp4005		4,1,pay_dun03.gat,155,159
pay_dun03.gat,155,161,0		warp	payonwarp4006		2,1,pay_dun02.gat,137,126
//pay_dun03.gat,127,62,0	warp	payonwarp4007		1,2,pay_dun04.gat,201,204

pay_dun03.gat,127,62,4		script	#payonwarp4008		45,1,2,{
	switch(rand(4)) {
		case 0:	warp "pay_dun04.gat",201,204; end;
		case 1:	warp "pay_dun04.gat",189,43;  end;
		case 2:	warp "pay_dun04.gat",43,40;   end;
		case 3:	warp "pay_dun04.gat",34,202;  end;
	}
}
pay_dun04.gat,40,37,0		warp	payonwarp4009		2,2,pay_dun03.gat,125,62
pay_dun04.gat,191,41,0		warp	payonwarp4010		1,1,pay_dun03.gat,125,62
pay_dun04.gat,202,206,0		warp	payonwarp4011		1,1,pay_dun03.gat,125,62
pay_dun04.gat,32,204,0		warp	payonwarp4012		2,1,pay_dun03.gat,125,62



//==============================================================
// prt_sewb1.gat	プロンテラ地下水路 B1F
// prt_sewb2.gat	プロンテラ地下水路 B2F
// prt_sewb3.gat	プロンテラ地下水路 B3F
// prt_sewb4.gat	プロンテラ地下水路 B4F
// -----
// prt_fild00.gat	プロンテラフィールド 00 ～ 11
//==============================================================
prt_sewb1.gat,135,248,0		warp	sewbwarp0501		2,2,prt_fild05.gat,274,208

prt_sewb1.gat,188,247,0		warp	sewbwarp5001		1,3,prt_sewb2.gat,19,19
prt_sewb2.gat,19,12,0		warp	sewbwarp5002		2,2,prt_sewb1.gat,192,247
prt_sewb2.gat,100,176,0		warp	sewbwarp5003		4,2,prt_sewb2.gat,140,28
prt_sewb2.gat,140,24,0		warp	sewbwarp5004		4,2,prt_sewb2.gat,100,172
prt_sewb2.gat,180,24,0		warp	sewbwarp5005		4,2,prt_sewb3.gat,180,169
prt_sewb3.gat,180,173,0		warp	sewbwarp5006		4,2,prt_sewb2.gat,180,28
prt_sewb2.gat,19,175,0		warp	sewbwarp5007		4,2,prt_sewb2.gat,60,28
prt_sewb2.gat,60,24,0		warp	sewbwarp5008		4,2,prt_sewb2.gat,19,171
prt_sewb3.gat,20,185,0		warp	sewbwarp5009		3,2,prt_sewb4.gat,100,92
prt_sewb4.gat,100,96,0		warp	sewbwarp5010		3,2,prt_sewb3.gat,19,180



//==============================================================
// treasure01.gat	沈没船1層
// treasure02.gat	沈没船2層
// -----
// alb2trea.gat		沈没船の付近の島
//==============================================================
treasure01.gat,69,22,0		warp	treasurewarp0501	4,1,alb2trea.gat,85,107

treasure01.gat,112,164,0	warp	treasurewarp4001	1,4,treasure01.gat,97,164
treasure01.gat,99,164,0		warp	treasurewarp4002	1,4,treasure01.gat,114,164
treasure01.gat,125,161,0	warp	treasurewarp4003	1,3,treasure01.gat,144,161
treasure01.gat,142,161,0	warp	treasurewarp4004	1,3,treasure01.gat,123,161
treasure01.gat,164,114,0	warp	treasurewarp4005	3,1,treasure01.gat,164,88
treasure01.gat,164,91,0		warp	treasurewarp4006	5,1,treasure01.gat,164,116
treasure01.gat,27,164,0		warp	treasurewarp4007	1,4,treasure01.gat,40,164
treasure01.gat,38,164,0		warp	treasurewarp4008	1,4,treasure01.gat,25,164
treasure01.gat,41,111,0		warp	treasurewarp4009	1,3,treasure01.gat,63,111
treasure01.gat,61,111,0		warp	treasurewarp4010	1,3,treasure01.gat,39,111
treasure01.gat,41,37,0		warp	treasurewarp4011	1,3,treasure01.gat,61,37
treasure01.gat,58,37,0		warp	treasurewarp4012	1,3,treasure01.gat,39,37
treasure01.gat,69,75,0		warp	treasurewarp4013	2,1,treasure01.gat,69,106
treasure01.gat,69,102,0		warp	treasurewarp4014	2,1,treasure01.gat,69,77
treasure01.gat,69,125,0		warp	treasurewarp4015	4,1,treasure01.gat,69,142
treasure01.gat,69,140,0		warp	treasurewarp4016	4,1,treasure01.gat,69,123
treasure01.gat,79,37,0		warp	treasurewarp4017	1,3,treasure01.gat,98,37
treasure01.gat,96,37,0		warp	treasurewarp4018	1,3,treasure01.gat,77,37
treasure01.gat,76,111,0		warp	treasurewarp4019	1,3,treasure01.gat,100,111
treasure01.gat,98,111,0		warp	treasurewarp4020	1,3,treasure01.gat,74,111
treasure01.gat,69,177,0		warp	treasurewarp4021	3,1,treasure02.gat,102,27
treasure02.gat,102,24,0		warp	treasurewarp4022	3,1,treasure01.gat,69,179
treasure02.gat,102,103,0	warp	treasurewarp4023	5,1,treasure02.gat,102,120
treasure02.gat,102,118,0	warp	treasurewarp4024	5,1,treasure02.gat,102,101
treasure02.gat,123,72,0		warp	treasurewarp4025	1,4,treasure02.gat,140,72
treasure02.gat,138,72,0		warp	treasurewarp4026	1,4,treasure02.gat,121,72
treasure02.gat,155,99,0		warp	treasurewarp4027	1,1,treasure02.gat,155,130
treasure02.gat,155,128,0	warp	treasurewarp4028	1,1,treasure02.gat,155,97
treasure02.gat,49,128,0		warp	treasurewarp4029	1,1,treasure02.gat,49,97
treasure02.gat,49,99,0		warp	treasurewarp4030	1,1,treasure02.gat,49,130
treasure02.gat,65,72,0		warp	treasurewarp4031	1,4,treasure02.gat,82,72
treasure02.gat,80,72,0		warp	treasurewarp4032	1,4,treasure02.gat,63,72



//==============================================================
// izlu2dun.gat		バイラン島
// -----
// iz_dun00.gat		イズルード海底洞窟1層
//==============================================================
izlu2dun.gat,108,83,0		warp	izludewarp0401		3,2,iz_dun00.gat,168,168




//==============================================================
// alde_dun01.gat	アルデバラン時計塔地下 1F ～ 4F
// c_tower1.gat		アルデバラン時計塔地上 1F ～ 4F
// -----
// aldebaran.gat	
//==============================================================
c_tower1.gat,200,157,0		warp	clockwarp0101		1,1,aldebaran.gat,139,131

c_tower1.gat,235,226,0		warp	clockwarp4001		1,1,c_tower2.gat,268,26
c_tower1.gat,123,22,0		warp	clockwarp4002		1,1,alde_dun01.gat,297,25
c_tower2.gat,142,283,0		warp	clockwarp4003		1,1,c_tower3.gat,65,147
c_tower2.gat,24,24,0		warp	clockwarp4004		1,1,alde_dun03.gat,277,178
c_tower2.gat,273,26,0		warp	clockwarp4005		1,1,c_tower1.gat,235,223
//random 2-1
c_tower2.gat,13,288,4		script	#clockwarp4006		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",13,282;    end;
		case 1:	warp "alde_dun03.gat",175,131; end;
		case 2:	warp "c_tower3.gat",235,7;     end;
	}
}
//random 2-2
c_tower2.gat,223,267,4		script	#clockwarp4007		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",228,267;   end;
		case 1:	warp "alde_dun03.gat",130,130; end;
		case 2:	warp "c_tower3.gat",252,29;    end;
	}
}
c_tower3.gat,60,147,0		warp	clockwarp4009		1,1,c_tower2.gat,148,283
c_tower3.gat,212,159,0		warp	clockwarp4010		1,1,alde_dun03.gat,276,53
c_tower3.gat,7,39,0 		warp	clockwarp4011		1,1,alde_dun01.gat,171,158
c_tower3.gat,42,41,0		warp	clockwarp4012		1,1,alde_dun02.gat,127,169
c_tower3.gat,146,8,0		warp	clockwarp4013		1,1,c_tower1.gat,235,223
//random3-1
c_tower3.gat,163,252,4		script	#clockwarp4014		45,1,1,{
	switch(rand(2)) {
		case 0:	warp "c_tower3.gat",168,252;  end;
		case 1:	warp "alde_dun02.gat",262,41; end;
	}
}
//random3-2
c_tower3.gat,240,7,4		script	#clockwarp4015		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",13,282;    end;
		case 1:	warp "alde_dun03.gat",175,131; end;
		case 2:	warp "c_tower3.gat",235,7;     end;
	}
}
//random3-3
c_tower3.gat,252,24,4		script	#clockwarp4016		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",228,267;   end;
		case 1:	warp "alde_dun03.gat",130,130; end;
		case 2:	warp "c_tower3.gat",252,29;    end;
	}
}
c_tower4.gat,37,70,0		warp	clockwarp4017		1,1,alde_dun03.gat,277,54
c_tower4.gat,51,156,0		warp	clockwarp4018		1,1,alde_dun01.gat,171,158
c_tower4.gat,68,46,0		warp	clockwarp4019		1,1,c_tower4.gat,73,154
c_tower4.gat,70,19,0		warp	clockwarp4020		2,2,c_tower3.gat,151,8
c_tower4.gat,79,49,0		warp	clockwarp4021		2,2,c_tower4.gat,204,60
c_tower4.gat,133,202,0		warp	clockwarp4022		1,1,c_tower4.gat,140,149
c_tower4.gat,153,107,0		warp	clockwarp4023		1,1,c_tower2.gat,228,267
c_tower4.gat,171,179,0		warp	clockwarp4024		1,1,alde_dun03.gat,276,53
c_tower4.gat,198,59,0		warp	clockwarp4025		1,1,c_tower4.gat,152,98
c_tower4.gat,204,57,0		warp	clockwarp4026		1,1,c_tower4.gat,65,77

c_tower4.gat,75,156,4		script	#clockwarp4027		45,0,0,{
	switch(rand(4)) {
		case 0:	warp "c_tower3.gat",168,252;  end;
		case 1:	warp "alde_dun02.gat",262,41; end;
		case 2:	warp "c_tower4.gat",73,154;   end;
		case 3:	warp "c_tower4.gat",140,149;  end;
	}
}
c_tower4.gat,68,79,4		script	#clockwarp4028		45,0,0,{
	switch(rand(4)) {
		case 0:	warp "c_tower2.gat",13,282;    end;
		case 1:	warp "alde_dun03.gat",175,131; end;
		case 2:	warp "c_tower3.gat",235,7;     end;
		case 3:	warp "c_tower4.gat",65,77;     end;
	}
}
c_tower4.gat,142,151,4		script	#clockwarp4029		45,0,0,{
	switch(rand(4)) {
		case 0:	warp "c_tower3.gat",168,252;  end;
		case 1:	warp "alde_dun02.gat",262,41; end;
		case 2:	warp "c_tower4.gat",73,154;   end;
		case 3: warp "c_tower4.gat",140,149;  end;
	}
}
c_tower4.gat,151,96,4		script	#clockwarp4030		45,0,0,{
	switch(rand(4)) {
		case 0:	warp "c_tower2.gat",228,267;   end;
		case 1:	warp "alde_dun03.gat",130,130; end;
		case 2:	warp "c_tower3.gat",252,29;    end;
		case 3:	warp "c_tower4.gat",152,95;    end;
	}
}
c_tower4.gat,189,40,4		script	#clockwarp4031		45,2,2,{
	switch(rand(4)) {
		case 0:	warp "c_tower2.gat",228,267;   end;
		case 1:	warp "alde_dun03.gat",130,130; end;
		case 2:	warp "c_tower3.gat",252,29;    end;
		case 3:	warp "c_tower4.gat",152,95;    end;
	}
}

alde_dun01.gat,292,306,0	warp	clockwarp4101		2,1,alde_dun02.gat,43,24
alde_dun01.gat,167,158,0	warp	clockwarp4102		2,2,c_tower2.gat,148,283
alde_dun01.gat,302,25,0		warp	clockwarp4103		2,2,c_tower1.gat,125,22
alde_dun02.gat,43,20,0		warp	clockwarp4104		1,1,alde_dun01.gat,292,300
alde_dun02.gat,279,250,0	warp	clockwarp4105		2,2,alde_dun03.gat,18,267
alde_dun02.gat,122,169,0	warp	clockwarp4106		2,2,c_tower3.gat,47,41
alde_dun02.gat,187,234,0	warp	clockwarp4107		2,2,c_tower3.gat,65,147
//randomB2
alde_dun02.gat,267,41,4		script	#clockwarp4108		45,1,1,{
	switch(rand(2)) {
		case 0:	warp "c_tower3.gat",168,252;   end;
		case 1:	warp "alde_dun02.gat",262,141; end;
	}
}
alde_dun03.gat,12,267,0		warp	clockwarp4109		2,2,alde_dun02.gat,273,250
alde_dun03.gat,277,183,0	warp	clockwarp4110		2,2,c_tower2.gat,27,27
alde_dun03.gat,191,31,0		warp	clockwarp4111		2,2,c_tower3.gat,217,159
alde_dun03.gat,276,48,0		warp	clockwarp4112		2,2,c_tower1.gat,235,223
//7(npc)
//alde_dun03.gat,264,16,0	warp	clockwarp4113		2,2,alde_dun04.gat,80,268
//randomB3-1
alde_dun03.gat,130,125,4	script	#clockwarp4114		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",228,267;   end;
		case 1:	warp "alde_dun03.gat",130,130; end;
		case 2:	warp "c_tower3.gat",252,29;    end;
	}
}
//random3-2
alde_dun03.gat,171,127,4	script	#clockwarp4115		45,1,1,{
	switch(rand(3)) {
		case 0:	warp "c_tower2.gat",13,282;    end;
		case 1:	warp "alde_dun03.gat",175,131; end;
		case 2:	warp "c_tower3.gat",235,7;     end;
	}
}
alde_dun04.gat,80,273,0		warp	clockwarp4116		2,2,alde_dun03.gat,263,26
alde_dun04.gat,207,225,0	warp	clockwarp4117		1,1,c_tower3.gat,7,34
alde_dun04.gat,215,192,0	warp	clockwarp4118		1,1,c_tower2.gat,148,283
alde_dun04.gat,32,74,0		warp	clockwarp4119		1,1,alde_dun02.gat,187,239
alde_dun04.gat,208,58,0		warp	clockwarp4120		2,2,alde_dun04.gat,268,74
alde_dun04.gat,272,74,0		warp	clockwarp4121		2,2,alde_dun04.gat,204,62

alde_dun04.gat,80,34,4		script	#clockwarp4122		45,1,1,{
	switch(rand(4)) {
		case 0:	warp "c_tower2.gat",13,282;    end;
		case 1:	warp "alde_dun03.gat",175,131; end;
		case 2:	warp "c_tower3.gat",235,7;     end;
		case 3:	warp "alde_dun04.gat",84,36;   end;
	}
}



//==============================================================
// gl_cas01.gat		グラストヘイム古城 1F
// gl_cas02.gat		グラストヘイム古城 2F
// gl_church.gat	グラストヘイム 修道院
// gl_chyard.gat	グラストヘイム カタコンベ
// gl_dun01.gat		グラストヘイム 最下層 地下洞窟
// gl_dun02.gat		グラストヘイム 最下層 地下洞窟
// gl_in01.gat		グラストヘイム 室内
// gl_knt01.gat		グラストヘイム 騎士団内
// gl_knt02.gat		グラストヘイム 騎士団内
// gl_prison.gat	グラストヘイム 地下監獄
// gl_prison1.gat	グラストヘイム 地下監獄
// gl_sew01.gat		グラストヘイム地下水路
// gl_sew02.gat		グラストヘイム地下水路
// gl_sew03.gat		グラストヘイム地下水路
// gl_sew04.gat		グラストヘイム地下水路
// gl_step.gat		グラストヘイム 階段ダンジョン
// -----
// glast_01.gat		グラストヘイム古城
//==============================================================
// Glast Heim

gl_step.gat,8,7,0		warp	glastwarp0101		1,1,glast_01.gat,54,108
gl_knt01.gat,150,6,0		warp	glastwarp0102		2,2,glast_01.gat,74,193
gl_in01.gat,81,68,0		warp	glastwarp0103		1,1,glast_01.gat,165,330
gl_in01.gat,83,174,0		warp	glastwarp0104		1,1,glast_01.gat,181,357
gl_in01.gat,106,125,0		warp	glastwarp0105		1,1,glast_01.gat,219,357
gl_in01.gat,118,59,0		warp	glastwarp0106		1,1,glast_01.gat,234,330
gl_cas01.gat,200,18,0		warp	glastwarp0107		2,2,glast_01.gat,200,294
gl_cas02.gat,104,193,0		warp	glastwarp0108		1,1,glast_01.gat,199,325
gl_church.gat,156,4,0		warp	glastwarp0109		1,1,glast_01.gat,200,134

gl_cas01.gat,200,165,0		warp	glastwarp4001		1,1,gl_cas02.gat,104,25
gl_cas02.gat,104,15,0		warp	glastwarp4002		1,1,gl_cas01.gat,200,160
gl_church.gat,16,299,0		warp	glastwarp4003		1,1,gl_chyard.gat,147,284
gl_chyard.gat,147,287,0		warp	glastwarp4004		1,1,gl_church.gat,16,295
gl_church.gat,301,46,0		warp	glastwarp4005		1,1,gl_chyard.gat,147,15
gl_chyard.gat,147,12,0		warp	glastwarp4006		1,1,gl_church.gat,295,46
gl_dun01.gat,225,18,0		warp	glastwarp4007		1,1,gl_dun02.gat,224,274
gl_dun02.gat,224,277,0		warp	glastwarp4008		1,1,gl_dun01.gat,225,22
gl_knt01.gat,12,148,0		warp	glastwarp4009		1,1,gl_knt02.gat,15,140
gl_knt02.gat,10,138,0		warp	glastwarp4010		1,1,gl_knt01.gat,7,148
gl_knt01.gat,104,204,0		warp	glastwarp4011		1,1,gl_knt01.gat,123,292
gl_knt01.gat,128,292,0		warp	glastwarp4012		1,1,gl_knt01.gat,104,199
gl_knt01.gat,150,291,0		warp	glastwarp4013		1,1,gl_knt02.gat,157,287
gl_knt02.gat,157,292,0		warp	glastwarp4014		1,1,gl_knt01.gat,150,286
gl_knt01.gat,287,144,0		warp	glastwarp4015		1,1,gl_knt02.gat,283,140
gl_knt02.gat,289,138,0		warp	glastwarp4016		1,1,gl_knt01.gat,292,144
gl_prison.gat,149,183,0		warp	glastwarp4017		1,1,gl_prison1.gat,150,14
gl_prison1.gat,150,10,0		warp	glastwarp4018		1,1,gl_prison.gat,149,178
gl_sew01.gat,19,21,0		warp	glastwarp4019		1,1,gl_sew02.gat,108,291
gl_sew02.gat,109,294,0		warp	glastwarp4020		1,1,gl_sew01.gat,19,24
gl_sew01.gat,258,258,0		warp	glastwarp4021		1,1,gl_prison1.gat,61,183
gl_prison1.gat,62,187,0		warp	glastwarp4022		1,1,gl_sew01.gat,258,255
gl_sew02.gat,299,294,0		warp	glastwarp4023		1,1,gl_sew03.gat,171,283
gl_sew03.gat,171,286,0		warp	glastwarp4024		1,1,gl_sew02.gat,295,294
gl_sew02.gat,30,273,0		warp	glastwarp4025		1,1,gl_chyard.gat,15,149
gl_chyard.gat,12,149,0		warp	glastwarp4026		1,1,gl_sew02.gat,29,270
gl_sew02.gat,290,156,0		warp	glastwarp4027		1,1,gl_step.gat,117,124
gl_step.gat,120,124,0		warp	glastwarp4028		1,1,gl_sew02.gat,285,158
gl_sew02.gat,296,18,0		warp	glastwarp4029		1,1,gl_knt01.gat,231,192
gl_knt01.gat,231,197,0		warp	glastwarp4030		1,1,gl_sew02.gat,296,22
gl_sew02.gat,16,26,0		warp	glastwarp4031		1,1,gl_prison1.gat,61,183

gl_prison.gat,10,70,4		script	#glastwarp4032		45,1,1,{
	switch(rand(2)) {
		case 0:	warp "gl_cas01.gat",237,192; end;
		case 1:	warp "gl_cas01.gat",368,301; end;
	}
}
gl_sew03.gat,64,10,0		warp	glastwarp4033		1,1,gl_sew04.gat,68,277
gl_sew04.gat,68,280,0		warp	glastwarp4034		1,1,gl_sew03.gat,64,13
gl_sew04.gat,104,78,0		warp	glastwarp4035		1,1,gl_dun01.gat,133,271
gl_dun01.gat,133,277,0		warp	glastwarp4036		1,1,gl_sew04.gat,101,78
gl_cas01.gat,135,40,0		warp	glastwarp4037		1,1,gl_cas01.gat,144,314
gl_cas01.gat,149,314,0		warp	glastwarp4038		1,1,gl_prison.gat,14,70
gl_cas01.gat,167,191,0		warp	glastwarp4039		1,1,gl_prison.gat,14,70
gl_cas01.gat,234,192,0		warp	glastwarp4040		1,1,gl_prison.gat,14,70
gl_cas01.gat,371,301,0		warp	glastwarp4041		1,1,gl_prison.gat,14,70
gl_cas01.gat,185,236,0		warp	glastwarp4042		1,1,gl_cas01.gat,163,191
gl_cas01.gat,215,236,0		warp	glastwarp4043		1,1,gl_cas01.gat,238,192
gl_cas01.gat,372,39,0		warp	glastwarp4044		1,1,gl_cas01.gat,367,301



//---JP2.0 追加マップ---


//==============================================================
// beach_dun.gat	西洞窟 カル
// beach_dun2.gat	北洞窟 ルワンダ
// beach_dun3.gat	東洞窟 マオ
// -----
// comodo.gat		幻想の島コモド
// um_fild01.gat	ルルカ森
// cmd_fild01.gat	パプチカ森
//==============================================================
beach_dun.gat,276,67,0		warp	beachwarp0101		1,1,comodo.gat,31,215
beach_dun2.gat,154,13,0		warp	beachwarp0102		2,1,comodo.gat,176,353
beach_dun3.gat,17,265,0		warp	beachwarp0103		1,1,comodo.gat,328,175

beach_dun2.gat,258,244,0	warp	beachwarp0501		1,1,um_fild01.gat,35,276
beach_dun3.gat,286,57,0		warp	beachwarp0502		1,1,cmd_fild01.gat,30,317

//beach_dun.gat,89,28,0		warp	beachwarp4001		3,3,beach_dun2.gat,15,182
//beach_dun2.gat,13,182,0	warp	beachwarp4002		3,3,beach_dun.gat,89,30



//---JP2.5 追加マップ---


//==============================================================
// gld_dun01.gat	ギルドダンジョン フェイヨン
// gld_dun02.gat	ギルドダンジョン アルデバラン
// gld_dun03.gat	ギルドダンジョン プロンテラ
// gld_dun04.gat	ギルドダンジョン ゲフェン
// -----
// pay_gld.gat		チュンリム湖
// alde_gld.gat		アルデバラン衛星都市ルイーナ
// prt_gld.gat		ヴァルキリーレルム
// gef_fild13.gat	ブリトニア
//==============================================================
gld_dun01.gat,119,14,0		warp	gldwarp0201		1,1,pay_gld.gat,53,141
gld_dun02.gat,180,112,0		warp	gldwarp0202		1,1,alde_gld.gat,242,121
gld_dun02.gat,20,160,0		warp	gldwarp0203		1,1,alde_gld.gat,229,185
gld_dun03.gat,42,30,0		warp	gldwarp0204		1,1,prt_gld.gat,63,66
gld_dun03.gat,238,274,0		warp	gldwarp0205		1,1,prt_gld.gat,252,247
gld_dun04.gat,37,230,0		warp	gldwarp0501		1,1,gef_fild13.gat,42,331
gld_dun04.gat,110,20,0		warp	gldwarp0501		1,1,gef_fild13.gat,373,62



//==============================================================
// tur_dun01.gat	タートルアイランド
// tur_dun02.gat	タートルアイランドダンジョン
// tur_dun03.gat	タートルアイランド 陽居村
// tur_dun04.gat	タートルアイランド 久陽宮
// tur_dun05.gat	地下湿地帯
// tur_dun06.gat	地下湿地帯
// -----
//==============================================================
tur_dun01.gat,154,241,0		warp	turtlewarp4001		1,1,tur_dun02.gat,148,264
tur_dun02.gat,148,268,0		warp	turtlewarp4002		1,1,tur_dun01.gat,154,237
tur_dun02.gat,167,19,0		warp	turtlewarp4003		1,1,tur_dun03.gat,132,189
tur_dun03.gat,132,193,0		warp	turtlewarp4004		1,1,tur_dun02.gat,167,23
tur_dun03.gat,217,71,0		warp	turtlewarp4005		1,1,tur_dun04.gat,100,192
tur_dun04.gat,100,196,0		warp	turtlewarp4006		1,1,tur_dun03.gat,215,75
tur_dun05.gat,89,69,0		warp	turtlewarp4007		1,1,tur_dun02.gat,148,264
tur_dun05.gat,9,45,0		warp	turtlewarp4008		1,1,tur_dun01.gat,154,237



//---JP3.0 追加マップ---


//==============================================================
// mag_dun01.gat	ノーグロード 1層
// mag_dun02.gat	ノーグロード 2層
// -----
// yuno_fild03.gat	エルメスプレート
//==============================================================
mag_dun01.gat,126,66,0		warp	nogloadwarp0501		1,1,yuno_fild03.gat,36,139

mag_dun01.gat,242,241,0		warp	nogloadwarp4001		1,1,mag_dun02.gat,47,31
mag_dun02.gat,47,28,0		warp	nogloadwarp4002		1,1,mag_dun01.gat,240,238



//---アマツ追加マップ---


//==============================================================
// ama_dun01.gat	畳の迷宮
// ama_dun02.gat	地下戦場跡
// ama_dun03.gat	アマツ地下神社
// ama_test.gat		モモタロ体験館
// -----
//==============================================================
ama_dun01.gat,235,144,0		warp	amatsuwarp0401		1,1,ama_dun02.gat,33,40
ama_dun02.gat,30,40,0		warp	amatsuwarp0402		1,1,ama_dun01.gat,232,144
ama_dun02.gat,196,123,0		warp	amatsuwarp0403		1,1,ama_dun03.gat,120,12
ama_dun03.gat,120,9,0		warp	amatsuwarp0404		1,1,ama_dun02.gat,196,120



//---コンロン追加マップ---


//==============================================================
// gon_dun01.gat	西王母神殿
// gon_dun02.gat	神仙の碁盤
// gon_dun03.gat	武陵桃源
// gon_test.gat		格闘場
// -----
// gonryun.gat		神仙の島コンロン
//==============================================================
//1F
gon_dun01.gat,153,45,0		warp	gonryunwarp0101		1,1,gonryun.gat,159,198

//2F
gon_dun01.gat,162,273,0		warp	gonryunwarp4001		1,1,gon_dun02.gat,17,113
gon_dun02.gat,14,113,0		warp	gonryunwarp4002		1,1,gon_dun01.gat,162,270
//2F碁盤迷路郡
//左大地
gon_dun02.gat,56,119,0		warp	gonryunwarp4003		1,1,gon_dun02.gat,47,210	/*相互F*/
//左上大碁盤
gon_dun02.gat,92,190,0		warp	gonryunwarp4004		1,1,gon_dun02.gat,199,20	/*相互E*/
gon_dun02.gat,44,213,0		warp	gonryunwarp4005		1,1,gon_dun02.gat,51,119	/*相互F*/
gon_dun02.gat,44,166,0		warp	gonryunwarp4006		1,1,gon_dun02.gat,97,121	/*確定*/
//左真中小碁盤
gon_dun02.gat,94,118,0		warp	gonryunwarp4007		1,1,gon_dun02.gat,177,189	/*確定*/
//左真中孤島
gon_dun02.gat,76,100,0		warp	gonryunwarp4008		1,1,gon_dun02.gat,145,62	/*確定*/
//左下碁盤
gon_dun02.gat,63,66,0		warp	gonryunwarp4009		1,1,gon_dun02.gat,203,94	/*相互A*/
gon_dun02.gat,86,44,0		warp	gonryunwarp4010		1,1,gon_dun02.gat,145,233	/*確定*/
//中央上碁盤
gon_dun02.gat,148,236,0		warp	gonryunwarp4011		1,1,gon_dun02.gat,234,194	/*相互D*/
gon_dun02.gat,171,258,0		warp	gonryunwarp4012		1,1,gon_dun02.gat,76,96		/*確定*/
//中央小碁盤/*無石*/
gon_dun02.gat,180,189,0		warp	gonryunwarp4013		1,1,gon_dun02.gat,170,164	/*確定*/
gon_dun02.gat,165,189,0		warp	gonryunwarp4014		1,1,gon_dun02.gat,235,135	/*相互C*/
//真ん中丸型大地
gon_dun02.gat,170,161,0		warp	gonryunwarp4015		1,1,gon_dun02.gat,89,41		/*確定*/
//中央下碁盤
gon_dun02.gat,168,92,0		warp	gonryunwarp4016		1,1,gon_dun02.gat,273,76	/*相互B*/
gon_dun02.gat,145,66,0		warp	gonryunwarp4017		1,1,gon_dun02.gat,199,20	/*確定*/
//右上大地
gon_dun02.gat,234,191,0		warp	gonryunwarp4018		1,1,gon_dun02.gat,145,233	/*相互D*/
//右下碁盤
gon_dun02.gat,235,138,0		warp	gonryunwarp4019		1,1,gon_dun02.gat,168,189	/*相互C*/
gon_dun02.gat,199,94,0		warp	gonryunwarp4020		1,1,gon_dun02.gat,60,70		/*相互A*/
gon_dun02.gat,276,76,0		warp	gonryunwarp4021		1,1,gon_dun02.gat,163,87	/*相互B*/
//右下葉
gon_dun02.gat,196,20,0		warp	gonryunwarp4022		1,1,gon_dun02.gat,95,190	/*相互E*/
//3F
gon_dun02.gat,251,268,0		warp	gonryunwarp4023		1,1,gon_dun03.gat,68,9
gon_dun03.gat,68,6,0		warp	gonryunwarp4024		1,1,gon_dun02.gat,251,265



//==============================================================
// sec_pri.gat		ヴァルハラ宮監獄
// sec_in01.gat		ヴァルハラ宮内部
// sec_in02.gat		ヴァルハラ宮内部
// -----
//==============================================================



//---ウンバラ追加マップ


//==============================================================
// um_dun01.gat		大樹の道
// um_dun02.gat		深奥の密林
// -----
// umbala.gat		ウータン族の村ウンバラ
// yggdrasil01.gat	フベルゲルミルの泉(イグドラシルの幹)
//==============================================================
um_dun01.gat,42,27,0		warp	umbalawarp0101		1,1,umbala.gat,109,284
um_dun02.gat,126,162,0		warp	umbalawarp0501		1,1,yggdrasil01.gat,39,63

//D1F ⇔ D2F
um_dun01.gat,149,198,0		warp	umbalawarp4001		1,1,um_dun02.gat,52,22
um_dun02.gat,55,18,0		warp	umbalawarp4002		1,1,um_dun01.gat,152,198
//2FLink A
um_dun02.gat,64,79,0		warp	umbalawarp4003		1,1,um_dun02.gat,219,261
um_dun02.gat,222,259,0		warp	umbalawarp4004		1,1,um_dun02.gat,67,77
//2FLink B
um_dun02.gat,169,38,0		warp	umbalawarp4005		1,1,um_dun02.gat,215,88
um_dun02.gat,215,85,0		warp	umbalawarp4006		1,1,um_dun02.gat,166,38
//2FLink C
um_dun02.gat,32,249,0		warp	umbalawarp4007		1,1,um_dun02.gat,117,208
um_dun02.gat,113,208,0		warp	umbalawarp4008		1,1,um_dun02.gat,35,252
//2FLink D
um_dun02.gat,177,38,0		warp	umbalawarp4009		1,1,um_dun02.gat,100,208
um_dun02.gat,103,208,0		warp	umbalawarp4010		1,1,um_dun02.gat,180,38
//2FLink E
um_dun02.gat,231,255,0		warp	umbalawarp4011		1,1,um_dun02.gat,25,241
um_dun02.gat,24,244,0		warp	umbalawarp4012		1,1,um_dun02.gat,233,253
//2FLink F
um_dun02.gat,215,77,0		warp	umbalawarp4013		1,1,um_dun02.gat,60,92
um_dun02.gat,60,89,0		warp	umbalawarp4014		1,1,um_dun02.gat,215,74



//---ニブルヘイム追加マップ


//==============================================================
// valkyrie.gat		ヴァルキリー神殿
// -----
//==============================================================



//---龍之城追加マップ


//==============================================================
// lou_dun01.gat	王陵
// lou_dun02.gat	王陵 内部
// lou_dun03.gat	白羊宮
// -----
// louyang.gat		古都 龍之城
//==============================================================
lou_dun01.gat,221,195,0		warp	louyangwarp0101		1,1,louyang.gat,40,273

// Lou_dun01 -> Lou_dun02
lou_dun01.gat,40,201,0		warp	louyangwarp1001		1,1,lou_dun02.gat,285,18
lou_dun02.gat,288,18,0		warp	louyangwarp1002		1,2,lou_dun01.gat,38,203
// Lou_dun02 -> Lou_dun03
lou_dun02.gat,165,269,0		warp	louyangwarp1003		1,1,lou_dun03.gat,165,38
lou_dun03.gat,165,35,0		warp	louyangwarp1004		1,1,lou_dun02.gat,165,266



//---神器クエスト追加マップ


//==============================================================
// que_god01.gat	神器クエストMap01
// que_god02.gat	神器クエストMap02
// -----
//==============================================================



//---アユタヤ追加マップ


//==============================================================
// ayo_dun01.gat	古代神殿迷宮
// ayo_dun02.gat	古代神殿内部
// -----
//==============================================================
ayo_dun01.gat,274,14,0	warp	ayothayawarp0501	1,1,ayo_fild02.gat,279,150

// Ayo_dun02 -> Ayo_dun01
ayo_dun02.gat,23,22,0	warp	ayothayawarp1001	1,1,ayo_dun01.gat,24,280
ayo_dun02.gat,275,22,0	warp	ayothayawarp1002	1,1,ayo_dun01.gat,24,280




//---アルデバランターボトラック追加マップ


//---鋼鉄の都市アインブロック追加マップ


//==============================================================
// ----- Einbroch アインブロック -----
// ein_dun01.gat	鉱山ダンジョン
// ein_dun02.gat	鉱山ダンジョン
// -----
// einbech.gat		採鉱の村アインベフ
//==============================================================
//鉱山ダンジョン⇒採鉱の村アインベフ
ein_dun01.gat,22,11,0	warp	einbrochwarp0101	1,1,einbech.gat,138,249
//鉱山ダンジョン１⇔鉱山ダンジョン２
ein_dun01.gat,261,255,0	warp	einbrochwarp4001	1,1,ein_dun02.gat,291,292
ein_dun02.gat,286,292,0	warp	einbrochwarp4002	1,1,ein_dun01.gat,261,258
//鉱山ダンジョン２
ein_dun02.gat,210,225,0	warp	einbrochwarp4003	1,1,ein_dun02.gat,216,207
ein_dun02.gat,216,210,0	warp	einbrochwarp4004	1,1,ein_dun02.gat,208,228
ein_dun02.gat,195,130,0	warp	einbrochwarp4005	1,1,ein_dun02.gat,233,109
ein_dun02.gat,228,109,0	warp	einbrochwarp4006	1,1,ein_dun02.gat,191,130




//==============================================================
// ----- Gefenia ゲフェニア -----
// gefenia01.gat	ゲフェニア
// gefenia02.gat	ゲフェニア
// gefenia03.gat	ゲフェニア
// gefenia04.gat	ゲフェニア
//==============================================================
//ゲフェニア01⇔02
gefenia01.gat,236,259,0	warp	gefeniawarp1001	1,1,gefenia02.gat,242,24
gefenia02.gat,241,19,0	warp	gefeniawarp1002	1,1,gefenia01.gat,236,251
gefenia01.gat,199,269,0	warp	gefeniawarp1003	1,1,gefenia02.gat,204,35
gefenia02.gat,204,29,0	warp	gefeniawarp1004	1,1,gefenia01.gat,199,261
//ゲフェニア01⇔04
gefenia01.gat,38,103,0	warp	gefeniawarp1005	1,1,gefenia04.gat,279,93
gefenia04.gat,287,93,0	warp	gefeniawarp1006	1,1,gefenia01.gat,44,103
//ゲフェニア02⇔03
gefenia02.gat,18,239,0	warp	gefeniawarp1007	1,1,gefenia03.gat,263,235
gefenia03.gat,269,235,0	warp	gefeniawarp1008	1,1,gefenia02.gat,22,236
gefenia02.gat,17,174,0	warp	gefeniawarp1009	1,1,gefenia03.gat,252,170
gefenia03.gat,258,170,0	warp	gefeniawarp1010	1,1,gefenia02.gat,24,173
//ゲフェニア03⇔04
gefenia03.gat,58,26,0	warp	gefeniawarp1011	1,1,gefenia04.gat,35,266
gefenia04.gat,35,273,0	warp	gefeniawarp1012	1,1,gefenia03.gat,58,32
gefenia03.gat,145,28,0	warp	gefeniawarp1013	1,1,gefenia04.gat,130,271
gefenia04.gat,131,275,0	warp	gefeniawarp1014	1,1,gefenia03.gat,145,34




//---企業都市リヒタルゼン追加マップ


//==============================================================
// lhz_dun01.gat	生体実験研究所地下１階
// lhz_dun02.gat	生体実験研究所地下２階
// lhz_dun03.gat	生体実験研究所最下層
// -----
// lighthalzen.gat	企業都市リヒタルゼン
//==============================================================
//生体工学研究所１⇒レッケンベル本社
lhz_dun01.gat,149,291,0		warp	lighthalzenwarp0101	1,1,lhz_in01.gat,19,129
//下水溝⇒企業都市リヒタルゼン
lhz_cube.gat,231,12,0		warp	lighthalzenwarp0102	1,1,lighthalzen.gat,310,302
//下水溝⇔生体工学研究所２
lhz_cube.gat,231,96,0		warp	lighthalzenwarp4001	1,1,lhz_dun02.gat,220,6
lhz_dun02.gat,224,6,0		warp	lighthalzenwarp4002	1,1,lhz_cube.gat,231,90

//生体工学研究所１⇔生体工学研究所２
lhz_dun01.gat,18,145,0		warp	lighthalzenwarp4003	1,1,lhz_dun02.gat,17,150
lhz_dun02.gat,17,156,0		warp	lighthalzenwarp4004	1,1,lhz_dun01.gat,18,150
lhz_dun01.gat,149,9,0		warp	lighthalzenwarp4005	1,1,lhz_dun02.gat,153,19
lhz_dun02.gat,146,19,0		warp	lighthalzenwarp4006	1,1,lhz_dun01.gat,144,9
lhz_dun01.gat,281,150,0		warp	lighthalzenwarp4007	1,1,lhz_dun02.gat,282,153
lhz_dun02.gat,282,161,0		warp	lighthalzenwarp4008	1,1,lhz_dun01.gat,281,154
//生体工学研究所２⇔生体工学研究所３
lhz_dun02.gat,149,149,0		script	lighthalzenwarp4009	45,1,1,{
	if((Upper != UPPER_HIGH && BaseLevel >= 95) || (Upper == UPPER_HIGH && BaseLevel >= 90))
		warp "lhz_dun03.gat",140,133;
	else
		warp "lhz_dun02.gat",145,149;
	end;
}
lhz_dun03.gat,139,137,0		warp	lighthalzenwarp4010	1,1,lhz_dun02.gat,149,142

//---ノーグハルト追加マップ


//==============================================================
// tha_scene01.gat	タナトスタワー前
// tha_t01.gat		タナトスタワー下層部
// tha_t02.gat		タナトスタワー下層部
// tha_t03.gat		タナトスタワー下層部
// tha_t04.gat		タナトスタワー下層部
// tha_t05.gat		タナトスタワー上層部
// tha_t06.gat		タナトスタワー上層部
// tha_t07.gat		タナトスタワー上層部
// tha_t08.gat		タナトスタワー上層部
// tha_t09.gat		タナトスタワー上層部
// tha_t10.gat		タナトスタワー上層部
// tha_t11.gat		タナトスタワー上層部
// tha_t12.gat		タナトスタワー上層部
// thana_step.gat	タナトスタワー上層部
// thana_boss.gat	タナトスタワー最上階
// abyss_01.gat		アビスレイク地下洞窟
// abyss_02.gat		アビスレイク地下洞窟
// abyss_03.gat		アビスレイク地下洞窟
// -----
// hu_fild01.gat	タナトスタワー
// hu_fild05.gat	アビスレイク
//==============================================================
tha_t01.gat,149,33,0		warp	thanatoswarp0501	1,1,hu_fild01.gat,140,158

tha_scene01.gat,144,198,0	warp	thanatoswarp4001	1,1,tha_t01.gat,149,38
//タナトスタワー1F⇔タナトスタワー2F
tha_t01.gat,150,150,0		warp	thanatoswarp4002	1,1,tha_t02.gat,149,130
tha_t02.gat,149,125,0		warp	thanatoswarp4003	1,1,tha_t01.gat,150,145
//タナトスタワー3F⇒タナトスタワー2F
tha_t03.gat,217,165,0		warp	thanatoswarp4004	1,1,tha_t02.gat,227,158
//タナトスタワー3F⇔タナトスタワー4F
tha_t03.gat,59,140,0		warp	thanatoswarp4005	1,1,tha_t04.gat,60,142
tha_t04.gat,60,137,0		warp	thanatoswarp4006	1,1,tha_t03.gat,59,135
//タナトスタワー4F⇒タナトスタワー5F
tha_t04.gat,81,36,0		warp	thanatoswarp4007	1,1,tha_t05.gat,62,8
//タナトスタワー5F
tha_t05.gat,62,157,0		warp	thanatoswarp4008	1,1,tha_t05.gat,213,97
tha_t05.gat,208,97,0		warp	thanatoswarp4009	1,1,tha_t05.gat,62,162
//タナトスタワー5F⇒タナトスタワー6F
tha_t05.gat,185,235,0		warp	thanatoswarp4010	1,1,tha_t06.gat,206,11
//タナトスタワー6F⇒タナトスタワー7F
tha_t06.gat,119,120,0		script	thanatoswarp4011	45,1,1,{
	if( (Class >= CLASS_KN_H && Class <= CLASS_CR2_H) || (Class >= CLASS_RK && Class <= CLASS_NC2_B) || (BaseLevel >= 95 && (Job >=  Job_SuperNovice && Job <= Job_DarkCollector || Job >= Job_ExpandedSuperNovice)) )
		warp "thana_step.gat",69,369;
	else {
		mes "-何か巨大な力に阻まれている……-";
		close;
	}
	end;
}
thana_step.gat,173,372,0	warp	thanatoswarp4012	1,1,tha_t07.gat,30,166
tha_t07.gat,26,166,0		warp	thanatoswarp4013	1,1,thana_step.gat,168,372
//タナトスタワー7F⇔タナトスタワー8F
tha_t07.gat,114,166,0		warp	thanatoswarp4014	1,1,thana_step.gat,73,287
thana_step.gat,69,287,0		warp	thanatoswarp4015	1,1,tha_t07.gat,110,166
thana_step.gat,174,288,0	warp	thanatoswarp4016	1,1,tha_t08.gat,28,43
tha_t08.gat,25,44,0			warp	thanatoswarp4017	1,1,thana_step.gat,170,288
//タナトスタワー8F⇔タナトスタワー9F
tha_t08.gat,114,43,0		warp	thanatoswarp4018	1,1,thana_step.gat,34,223
thana_step.gat,30,223,0		warp	thanatoswarp4019	1,1,tha_t08.gat,110,43
thana_step.gat,32,166,0		warp	thanatoswarp4020	1,1,tha_t09.gat,20,96
tha_t09.gat,16,94,0			warp	thanatoswarp4021	1,1,thana_step.gat,36,166
//タナトスタワー9F⇔タナトスタワー10F
tha_t09.gat,92,146,0		warp	thanatoswarp4022	1,1,thana_step.gat,183,223
thana_step.gat,179,223,0	warp	thanatoswarp4023	1,1,tha_t09.gat,88,146
thana_step.gat,182,166,0	warp	thanatoswarp4024	1,1,tha_t10.gat,155,100
tha_t10.gat,163,94,0		warp	thanatoswarp4025	1,1,thana_step.gat,186,166
//タナトスタワー10F⇔タナトスタワー11F
tha_t10.gat,170,138,0		warp	thanatoswarp4026	1,1,thana_step.gat,17,73
thana_step.gat,13,73,0		warp	thanatoswarp4027	1,1,tha_t10.gat,166,138
thana_step.gat,15,15,0		warp	thanatoswarp4028	1,1,tha_t11.gat,47,17
tha_t11.gat,51,17,0			warp	thanatoswarp4029	1,1,thana_step.gat,19,15
//タナトスタワー11F⇔タナトスタワー12F
tha_t11.gat,92,36,0		warp	thanatoswarp4030	1,1,thana_step.gat,183,73
thana_step.gat,179,73,0		warp	thanatoswarp4031	1,1,tha_t11.gat,88,36
thana_step.gat,181,15,0		warp	thanatoswarp4032	1,1,tha_t12.gat,115,16
tha_t12.gat,121,17,0		warp	thanatoswarp4033	1,1,thana_step.gat,185,15

//アビスレイク地下洞窟1層⇒アビスレイク
abyss_01.gat,265,274,0		warp	abysswarp0501	1,1,hu_fild05.gat,177,211
//アビスレイク地下洞窟1層⇔アビスレイク地下洞窟2層
abyss_01.gat,25,24,0		warp	abysswarp4001	1,1,abyss_02.gat,271,270
abyss_02.gat,277,270,0		warp	abysswarp4002	1,1,abyss_01.gat,25,30
//アビスレイク地下洞窟2層⇔アビスレイク地下洞窟3層
abyss_02.gat,145,280,0		warp	abysswarp4003	1,1,abyss_03.gat,115,35
abyss_03.gat,115,25,0		warp	abysswarp4004	1,1,abyss_02.gat,145,275


//---機械人形工場追加マップ


//==============================================================
// kh_dun01.gat	機械人形工場 1F
// kh_dun02.gat	機械人形工場 2F
//==============================================================
//機械人形工場 1F
kh_dun01.gat,3,234,0		warp	khwarp0501	1,1,yuno_fild08.gat,74,174
kh_dun01.gat,63,7,0		warp	khwarp5001	1,1,kh_dun01.gat,227,176
kh_dun01.gat,232,176,0		warp	khwarp5002	1,1,kh_dun01.gat,63,12
kh_dun01.gat,232,226,0		warp	khwarp5003	1,1,kh_dun01.gat,13,12
//機械人形工場 2F⇒1F
kh_dun02.gat,43,195,0		warp	khwarp5004	1,1,kh_dun01.gat,32,199


//---ラヘル追加マップ


//==============================================================
// ra_san01.gat		フレイヤ大神殿聖域 01
// ra_san02.gat		フレイヤ大神殿聖域 02
// ra_san03.gat		フレイヤ大神殿聖域 03
// ra_san04.gat		フレイヤ大神殿聖域 04
// ra_san05.gat		フレイヤ大神殿聖域 05
// -----
// ice_dun01.gat	氷の洞窟 01
// ice_dun02.gat	氷の洞窟 02
// ice_dun03.gat	氷の洞窟 03
// ice_dun04.gat	氷の洞窟 04
// -----
// ra_temple.gat	フレイヤ大神殿（セスルムニル）
// ra_temin.gat		フレイヤ大神殿 室内
// ra_fild01.gat	ラヘルフィールド 01（アウドムラ草原）
//==============================================================
//フレイヤ大神殿聖域01⇒フレイヤ大神殿室内
ra_san01.gat,139,139,0	warp	rachelwarp0101	1,1,ra_temin.gat,27,314
//フレイヤ大神殿聖域05⇒フレイヤ大神殿
ra_san05.gat,150,7,0	warp	rachelwarp0102	1,1,ra_temple.gat,119,153

//氷の洞窟01⇒ラヘルフィールド01
ice_dun01.gat,157,10,0	warp	rachelwarp0501	1,1,ra_fild01.gat,233,327

//フレイヤ大神殿聖域02～04⇒フレイヤ大神殿聖域01
ra_san02.gat,213,280,0	warp	rachelwarp4002	1,1,ra_san01.gat,140,19
ra_san03.gat,123,283,0	warp	rachelwarp4003	1,1,ra_san01.gat,140,19
ra_san04.gat,119,104,0	warp	rachelwarp4004	1,1,ra_san01.gat,140,19
//フレイヤ大神殿聖域02⇔フレイヤ大神殿聖域03
ra_san02.gat,289,149,0	warp	rachelwarp4005	1,1,ra_san03.gat,10,149
ra_san03.gat,5,149,0	warp	rachelwarp4006	1,1,ra_san02.gat,284,149
//フレイヤ大神殿聖域02⇔フレイヤ大神殿聖域04
ra_san02.gat,213,4,0	warp	rachelwarp4007	1,1,ra_san04.gat,35,216
ra_san04.gat,35,221,0	warp	rachelwarp4008	1,1,ra_san02.gat,213,9
//フレイヤ大神殿聖域03⇔フレイヤ大神殿聖域04
ra_san03.gat,85,15,0	warp	rachelwarp4009	1,1,ra_san04.gat,203,216
ra_san04.gat,203,221,0	warp	rachelwarp4010	1,1,ra_san03.gat,85,20
//フレイヤ大神殿聖域02～04⇒フレイヤ大神殿聖域05
ra_san02.gat,30,21,0	warp	rachelwarp4011	1,1,ra_san05.gat,14,149
ra_san03.gat,279,21,0	warp	rachelwarp4012	1,1,ra_san05.gat,282,149
ra_san04.gat,120,48,0	warp	rachelwarp4013	1,1,ra_san05.gat,150,282

//氷の洞窟01⇔氷の洞窟02
ice_dun01.gat,146,161,0	warp	rachelwarp4014	1,1,ice_dun02.gat,151,139
ice_dun02.gat,151,145,0	warp	rachelwarp4015	1,1,ice_dun01.gat,146,157
//氷の洞窟02⇔氷の洞窟03
ice_dun02.gat,150,285,0	warp	rachelwarp4016	1,1,ice_dun03.gat,149,24
ice_dun03.gat,149,19,0	warp	rachelwarp4017	1,1,ice_dun02.gat,150,280
//氷の洞窟04⇒氷の洞窟03
ice_dun04.gat,33,140,0	warp	rachelwarp4018	1,1,ice_dun03.gat,149,130



//---ベインス追加マップ


//==============================================================
// thor_v01.gat		トール火山ダンジョン 01
// thor_v02.gat		トール火山ダンジョン 02
// thor_v03.gat		トール火山ダンジョン 03
// -----
// que_thor.gat		トール火山ダンジョン
// thor_camp.gat	トール火山兵站基地
// ve_fild03.gat	ベインスフィールド 03
//==============================================================
//トール火山ダンジョン 01⇒ベインスフィールド 03
thor_v01.gat,21,224,0	warp	veinswarp0501	1,1,ve_fild03.gat,168,235

//トール火山ダンジョン 01⇔トール火山ダンジョン 02
thor_v01.gat,201,37,0	warp	veinswarp4001	1,1,thor_v02.gat,78,203
thor_v02.gat,73,203,0	warp	veinswarp4002	1,1,thor_v01.gat,196,37
//トール火山ダンジョン 02⇔トール火山ダンジョン 03
thor_v02.gat,192,60,0	warp	veinswarp4003	1,1,thor_v03.gat,35,262
thor_v03.gat,30,262,0	warp	veinswarp4004	1,1,thor_v02.gat,187,58



//---名もなき島追加マップ


//==============================================================
// nameless_n.gat	名もなき島 夜
// -----
// abbey01.gat		修道院 01
// abbey02.gat		修道院 02
// abbey03.gat		修道院 03
//==============================================================
//修道院 01⇒名もなき島 夜
abbey01.gat,51,10,0	warp	namelesswarp0101	1,1,nameless_n.gat,162,184

//修道院 01
abbey01.gat,87,122,0	warp	namelesswarp4001	1,1,abbey01.gat,12,200
abbey01.gat,12,205,0	warp	namelesswarp4002	1,1,abbey01.gat,89,118
//修道院 01⇔修道院 02
abbey01.gat,322,101,0	warp	namelesswarp4003	1,1,abbey02.gat,149,12
abbey02.gat,149,7,0	warp	namelesswarp4004	1,1,abbey01.gat,322,96
//修道院 02⇔修道院 03
abbey02.gat,149,290,0	warp	namelesswarp4005	1,1,abbey03.gat,120,9
abbey03.gat,119,6,0	warp	namelesswarp4006	1,1,abbey02.gat,149,285
//修道院 02 外周リンク
abbey02.gat,106,30,0	warp	namelesswarp4007	1,1,abbey02.gat,198,30
abbey02.gat,193,30,0	warp	namelesswarp4008	1,1,abbey02.gat,101,30
abbey02.gat,106,270,0	warp	namelesswarp4009	1,1,abbey02.gat,198,270
abbey02.gat,193,270,0	warp	namelesswarp4010	1,1,abbey02.gat,101,270



//---モスコビア追加マップ


//==============================================================
// -----  モスコビア -----
// mosk_dun01.gat	森
// mosk_dun02.gat	深い森
// -----
// mosk_fild02.gat	モスコビアフィールド
// mosk_in.gat		モスコビア 内部
//==============================================================
//深い森⇒ババヤガの家
//mosk_dun02.gat,53,220,0	warp	moscoviawarp0101	1,1,mosk_in.gat,215,41

//森⇒モスコビアフィールド
mosk_dun01.gat,189,42,0	warp	moscoviawarp0501	1,1,mosk_fild02.gat,190,254



//---イグドラシル追加マップ


//==============================================================
// nyd_dun01.gat	イグドラシル中心部 01
// nyd_dun02.gat	イグドラシル中心部 02
//==============================================================
//イグドラシル中心部 01⇔イグドラシル中心部 02
nyd_dun01.gat,255,142,0	warp	nydhogwarp4001	1,1,nyd_dun02.gat,61,265
nyd_dun02.gat,56,264,0	warp	nydhogwarp4002	1,1,nyd_dun01.gat,249,143



//---ブラジリス追加マップ


//==============================================================
// -----  ブラジリス -----
// bra_dun01.gat	滝の中の洞窟 01
// bra_dun02.gat	滝の中の洞窟 02
//==============================================================
//滝の中の洞窟 01⇔滝の中の洞窟 02
bra_dun01.gat,199,35,0	warp	brasiliswarp4001	1,1,bra_dun02.gat,261,263
bra_dun02.gat,261,265,0	warp	brasiliswarp4002	1,1,bra_dun01.gat,199,37



//---エルディカスティス追加マップ


//==============================================================
// -----  エルディカスティス -----
// dic_dun01.gat	カミダルトンネル
// dic_dun02.gat	スカラバホール
// dic_dun03.gat	スカラバガーデン
//==============================================================
//カミダルトンネル
dic_dun01.gat,87,212,0		warp	dicasteswarp4001	1,1,dic_dun01.gat,169,227
dic_dun01.gat,165,227,0		warp	dicasteswarp4002	1,1,dic_dun01.gat,83,212
dic_dun01.gat,371,228,0		warp	dicasteswarp4003	1,1,dic_dun01.gat,32,156
dic_dun01.gat,28,156,0		warp	dicasteswarp4004	1,1,dic_dun01.gat,367,228
dic_dun01.gat,371,172,0		warp	dicasteswarp4005	1,1,dic_dun01.gat,32,100
dic_dun01.gat,28,100,0		warp	dicasteswarp4006	1,1,dic_dun01.gat,367,172
dic_dun01.gat,371,100,0		warp	dicasteswarp4007	1,1,dic_dun01.gat,33,43
dic_dun01.gat,29,43,0		warp	dicasteswarp4008	1,1,dic_dun01.gat,367,100
//スカラバホール⇒カミダルトンネル
dic_dun02.gat,102,148,0		warp	dicasteswarp4009	1,1,dic_dun01.gat,290,99
//スカラバガーデン⇒カミダルトンネル
dic_dun03.gat,102,148,0		warp	dicasteswarp4010	1,1,dic_dun01.gat,290,99



//---デワタ追加マップ


//==============================================================
// -----  デワタ -----
// dew_dun02.gat	イスタナ洞窟
// -----
// dew_fild01.gat	デワタフィールド 01
//==============================================================
//イスタナ洞窟⇒デワタフィールド 01
dew_dun02.gat,305,30,0		warp	dewatawarp0501	1,1,dew_fild01.gat,50,65



//---マラン島追加マップ


//==============================================================
// -----  マラン島 -----
// mal_dun01.gat	星明りの珊瑚礁
// -----
// malangdo.gat		マラン島
//==============================================================
//星明りの珊瑚礁⇒マラン島
mal_dun01.gat,30,230,0		warp	malangdowarp0101	1,1,malangdo.gat,75,236



//---ポートマラヤ追加マップ


//==============================================================
// -----  ポートマラヤ -----
// ma_scene01.gat	バコナワ湖
// ma_c_jp.gat		ブワヤの洞窟
// ma_dun01.gat		ビョンウンゴ病院1階
// ma_dun01_jp.gat	ビョンウンゴ病院2階
// -----
// ma_fild01.gat	バリオ・マヒワガ
// ma_fild02.gat	バリオ・フォレスト
//==============================================================
//バコナワ湖⇒バリオ・マヒワガ
ma_scene01.gat,140,80,0		warp	malayawarp0505	1,1,ma_fild01.gat,288,55
//ブワヤの洞窟⇒バリオ・フォレスト
ma_c_jp.gat,28,56,0			warp	malayawarp0506	1,1,ma_fild02.gat,315,319

//ビョンウンゴ病院2階⇒ビョンウンゴ病院1階
ma_dun01_jp.gat,33,156,0	warp	malayawarp4001	1,1,ma_dun01.gat,150,8
//ビョンウンゴ病院2階
ma_dun01_jp.gat,107,157,0	warp	malayawarp4002	1,1,ma_dun01_jp.gat,113,157
ma_dun01_jp.gat,110,157,0	warp	malayawarp4003	1,1,ma_dun01_jp.gat,104,157
ma_dun01_jp.gat,107,63,0	warp	malayawarp4004	1,1,ma_dun01_jp.gat,113,63
ma_dun01_jp.gat,110,63,0	warp	malayawarp4005	1,1,ma_dun01_jp.gat,104,63
ma_dun01_jp.gat,111,176,0	warp	malayawarp4006	1,1,ma_dun01_jp.gat,113,49
ma_dun01_jp.gat,111,49,0	warp	malayawarp4007	1,1,ma_dun01_jp.gat,113,176



//---エクラージュ追加マップ


//==============================================================
// -----  エクラージュ -----
// ecl_tdun01.gat	ビフロストタワー 1階
// ecl_tdun02.gat	ビフロストタワー 2階
// ecl_tdun03.gat	ビフロストタワー 3階
// -----
// ecl_fild01.gat	花が咲き始めた大地
//==============================================================
//ビフロストタワー⇒花が咲き始めた大地
ecl_tdun01.gat,61,11,0	warp	eclagewarp0501	1,1,ecl_fild01.gat,182,92

//ビフロストタワー
ecl_tdun01.gat,67,106,0	warp	eclagewarp4001	1,1,ecl_tdun02.gat,60,88
ecl_tdun02.gat,60,90,0	warp	eclagewarp4002	1,1,ecl_tdun01.gat,70,105
ecl_tdun02.gat,52,9,0	warp	eclagewarp4003	1,1,ecl_tdun03.gat,47,13
ecl_tdun03.gat,49,11,0	warp	eclagewarp4004	1,1,ecl_tdun02.gat,50,11



//---ラザーニャ追加マップ


//==============================================================
// -----  ラザーニャ -----
// lasa_dun01.gat	龍の巣 01
// lasa_dun02.gat	龍の巣 02
// lasa_dun03.gat	龍の巣 03
// -----
// lasa_fild02.gat	ラビオル森 01
//==============================================================
//龍の巣 01⇒ラビオル森 01
lasa_dun01.gat,18,143,0	warp	lasagnawarp0501	2,2,lasa_fild02.gat,344,243

//龍の巣 01⇔龍の巣 02
lasa_dun01.gat,157,98,0	warp	lasagnawarp4001	2,2,lasa_dun02.gat,22,171
lasa_dun02.gat,18,171,0	warp	lasagnawarp4002	2,2,lasa_dun01.gat,153,98

//龍の巣 02⇔龍の巣 03
lasa_dun02.gat,146,58,0	warp	lasagnawarp4003	2,2,lasa_dun03.gat,190,18
lasa_dun03.gat,190,15,0	warp	lasagnawarp4004	2,2,lasa_dun02.gat,146,54



//---ロックリッジ追加マップ


//==============================================================
// -----  ロックリッジ -----
// rockmi1.gat	ロックリッジ地下街
// rockmi1.gat	ロックリッジ地下街 奥地
// rockmi1.gat	ロックリッジ鉱山 01
// rockmi3.gat	ロックリッジ鉱山 01 奥地
// -----
// rockrdg2.gat	キワワ砂漠 02
// rockrdg2.gat	キワワ砂漠 02
//==============================================================
//ロックリッジ地下街⇒ロックリッジ
harboro2.gat,284,104,0	warp	rockwarp0501	2,2,harboro1.gat,318,124
harboro3.gat,284,104,0	warp	rockwarp0502	2,2,harboro1.gat,318,124

//ロックリッジ鉱山⇒キワワ砂漠 02
rockmi1.gat,247,16,0	warp	rockwarp0503	1,1,rockrdg2.gat,304,344
rockmi3.gat,247,16,0	warp	rockwarp0504	1,1,rockrdg2.gat,304,344
