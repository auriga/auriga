//==============================================================================
// Town Warp Point Script   2005-06-28(β3 mod by kia)
//==============================================================================

//-------------------------------------------
// warp0xxx 	MAPの区切り  	
// warp01xx 	街へ         	(使わない)
// warp02xx 	GvGルームへ  	(使わない)
// warp03xx 	砦へ         	
// warp04xx 	ダンジョンへ 	
// warp05xx 	フィールドへ 	
// warp06xx 	JOBステージへ	(使わない)
// warp07xx 	PvPステージへ	
// warp1xxx 	街           	
// warp2xxx 	GvGルーム    	
// warp3xxx 	GvG 砦       	(使わない)
// warp31xx 	GvG 砦１     	
// warp32xx 	GvG 砦２     	
// warp33xx 	GvG 砦３     	
// warp34xx 	GvG 砦４     	
// warp35xx 	GvG 砦５     	
// warp4xxx 	ダンジョン   	(使わない)
// warp5xxx 	フィールド   	(使わない)
// warp6xxx 	JOBステージ  	
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
// ----- Xmas ルティエ -----
// xmas.gat 		雪の街ルティエ
// xmas_in.gat		ルティエ室内
// -----
// mas_fild01.gat	ルティエフィールド
// xmas_dun01.gat	おもちゃ工場倉庫
//==============================================================
xmas.gat,143,314,0  		warp	xmaswarp0401		1,1,xmas_dun01.gat,205,16
xmas.gat,149,41,0   		warp	xmaswarp0501		18,1,xmas_fild01.gat,80,248

xmas.gat,120,131,0		warp	xmaswarp1001		1,1,xmas_in.gat,44,33
xmas_in.gat,46,33,0		warp	xmaswarp1002		1,1,xmas.gat,122,131
xmas.gat,119,162,0		warp	xmaswarp1003		1,1,xmas_in.gat,36,91
xmas_in.gat,38,89,0		warp	xmaswarp1004		1,1,xmas.gat,122,159
xmas.gat,174,131,0		warp	xmaswarp1005		1,1,xmas_in.gat,155,32
xmas_in.gat,153,32,0		warp	xmaswarp1006		1,1,xmas.gat,172,131
xmas.gat,173,160,0		warp	xmaswarp1007		1,1,xmas_in.gat,165,95
xmas_in.gat,163,93,0		warp	xmaswarp1008		1,1,xmas.gat,172,158
xmas.gat,181,169,0		warp	xmaswarp1009		1,1,xmas_in.gat,177,107
xmas_in.gat,179,109,0		warp	xmaswarp1010		1,1,xmas.gat,184,168
xmas.gat,142,239,0		warp	xmaswarp1011		1,1,xmas_in.gat,94,85
xmas_in.gat,94,83,0		warp	xmaswarp1012		1,1,xmas.gat,142,237
xmas.gat,149,239,0		warp	xmaswarp1013		1,1,xmas_in.gat,104,85
xmas_in.gat,104,83,0		warp	xmaswarp1014		1,1,xmas.gat,149,237
xmas.gat,149,256,0		warp	xmaswarp1015		1,1,xmas_in.gat,104,115
xmas_in.gat,104,117,0		warp	xmaswarp1016		1,1,xmas.gat,149,258
xmas.gat,142,256,0		warp	xmaswarp1017		1,1,xmas_in.gat,94,115
xmas_in.gat,94,117,0		warp	xmaswarp1018		1,1,xmas.gat,142,258
xmas.gat,104,289,0		warp	xmaswarp1019		1,1,xmas_in.gat,30,163
xmas_in.gat,30,161,0		warp	xmaswarp1020		1,1,xmas.gat,104,286
xmas.gat,189,278,0		warp	xmaswarp1021		1,1,xmas_in.gat,168,164
xmas_in.gat,168,160,0		warp	xmaswarp1022		1,1,xmas.gat,189,275



//==============================================================
// ----- 聖カピトーリナ修道院 -----
// prt_monk.gat		聖カピトーリナ修道院
// monk_in.gat		聖カピトーリナ修道院内
// job_monk.gat		聖カピトーリナ修道院
// monk_test.gat	聖カピトーリナ修道院(test)
// -----
// prt_fild03.gat	プロンテラフィールド
//==============================================================
prt_monk.gat,22,248,0		warp	monkwarp0501		2,2,prt_fild03.gat,368,256

prt_monk.gat,245,106,0		warp	monkwarp6001		1,1,monk_in.gat,98,30
prt_monk.gat,245,137,0		warp	monkwarp6002		1,1,monk_in.gat,98,183
monk_in.gat,98,27,0		warp	monkwarp6003		5,2,prt_monk.gat,245,104
monk_in.gat,98,186,0		warp	monkwarp6004		3,2,prt_monk.gat,245,139
monk_in.gat,128,46,0		warp	monkwarp6005		1,3,monk_in.gat,161,38
monk_in.gat,159,38,0		warp	monkwarp6006		1,3,monk_in.gat,126,46
monk_in.gat,128,84,0		warp	monkwarp6007		1,3,monk_in.gat,161,90
monk_in.gat,159,90,0		warp	monkwarp6008		1,3,monk_in.gat,126,84
monk_in.gat,40,38,0		warp	monkwarp6009		1,3,monk_in.gat,71,46
monk_in.gat,69,46,0		warp	monkwarp6010		1,3,monk_in.gat,38,38
monk_in.gat,40,92,0		warp	monkwarp6011		1,3,monk_in.gat,71,84
monk_in.gat,69,84,0		warp	monkwarp6012		1,3,monk_in.gat,38,92
monk_in.gat,99,102,0		warp	monkwarp6013		5,1,monk_in.gat,99,143
monk_in.gat,99,141,0		warp	monkwarp6014		3,1,monk_in.gat,99,100

prt_monk.gat,192,172,0		warp	monkwarp6015		1,1,monk_test.gat,329,50
monk_test.gat,329,47,0		warp	monkwarp6016		1,1,prt_monk.gat,193,166
monk_test.gat,329,76,0		warp	monkwarp6017		1,1,monk_test.gat,259,118
monk_test.gat,259,115,0		warp	monkwarp6018		1,1,monk_test.gat,329,71
monk_test.gat,272,125,0		warp	monkwarp6019		1,1,monk_test.gat,301,127
monk_test.gat,298,127,0		warp	monkwarp6020		1,1,monk_test.gat,268,125



//==============================================================
// ----- オーク村の室内 -----
// in_orcs01.gat	オーク村の室内
// -----
// orcsdun01.gat	オーク地下洞窟
// orcsdun02.gat	オーク地下洞窟
// gef_fild10.gat	ゲフェンフィールド 00 ～ 11
//==============================================================
in_orcs01.gat,30,182,0		warp	orcswarp0401		2,1,orcsdun01.gat,32,170
in_orcs01.gat,108,114,0		warp	orcswarp0402		2,1,orcsdun02.gat,180,17

in_orcs01.gat,108,86,0		warp	orcswarp0501		3,2,gef_fild10.gat,223,203
in_orcs01.gat,124,171,0		warp	orcswarp0502		1,3,gef_fild10.gat,138,329
in_orcs01.gat,162,55,0		warp	orcswarp0503		4,1,gef_fild10.gat,214,53
in_orcs01.gat,29,116,0		warp	orcswarp0504		4,1,gef_fild10.gat,137,286
in_orcs01.gat,30,154,0		warp	orcswarp0505		3,2,gef_fild10.gat,65,335



//==============================================================
// ----- Assassin アサシンギルド -----
// in_moc_16.gat	アサシンギルド
// -----
// moc_fild01.gat	ソクラド砂漠 01 ～ 19
//==============================================================
// アサシンギルド
in_moc_16.gat,18,8,0		warp	assassinwarp0501	1,1,moc_fild16.gat,205,291



//==============================================================
// ----- Novice 初心者修練場 -----
// new_1-1.gat		初心者修練場 1 ～ 4
// new_2-1.gat		初心者修練場 1 ～ 4
// new_3-1.gat		初心者修練場 1 ～ 4
// new_4-1.gat		初心者修練場 1 ～ 4
// new_5-1.gat		初心者修練場 1 ～ 4
// -----
//==============================================================
new_1-1.gat,148,112,0		warp	newwarp6001		2,2,new_1-2.gat,33,179
new_1-2.gat,100,6,0		warp	newwarp6002		2,2,new_1-2.gat,33,179
new_1-2.gat,126,106,0		warp	newwarp6003		2,2,new_1-2.gat,33,179
new_1-2.gat,156,171,0		warp	newwarp6004		2,2,new_1-2.gat,33,179
new_1-2.gat,73,106,0		warp	newwarp6005		2,2,new_1-2.gat,33,179
new_1-2.gat,46,172,0		warp	newwarp6006		2,2,new_1-2.gat,33,179
//new_1-1.gat,148,112,0		warp	newwarp6001		2,2,new_1-2.gat,100,9
//new_1-2.gat,100,6,0		warp	newwarp6002		2,2,new_1-1.gat,144,112
//new_1-2.gat,126,106,0		warp	newwarp6003		2,2,new_1-2.gat,160,171
//new_1-2.gat,156,171,0		warp	newwarp6004		2,2,new_1-2.gat,123,106
//new_1-2.gat,73,106,0		warp	newwarp6005		2,2,new_1-2.gat,41,172
//new_1-2.gat,46,172,0		warp	newwarp6006		2,2,new_1-2.gat,78,106



//==============================================================
// ----- Thief シーフ -----
// moc_prydb1.gat	シーフギルド
// job_thief1.gat	シブのキノコ農場
// -----
// moc_ruins.gat	モロク - ピラミッド周辺
// moc_pryd05.gat	ピラミッドダンジョン B2F
//==============================================================
job_thief1.gat,180,15,0		warp	thiefwarp0101		7,1,moc_ruins.gat,145,117
moc_prydb1.gat,100,55,0		warp	thiefwarp0401		2,1,moc_pryd05.gat,94,96

moc_prydb1.gat,100,104,0	warp	thiefwarp6001		5,2,moc_prydb1.gat,100,74
moc_prydb1.gat,100,77,0		warp	thiefwarp6002		5,2,moc_prydb1.gat,100,107
moc_prydb1.gat,111,115,0	warp	thiefwarp6003		2,6,moc_prydb1.gat,145,115
moc_prydb1.gat,142,115,0	warp	thiefwarp6004		2,6,moc_prydb1.gat,108,115
moc_prydb1.gat,59,115,0		warp	thiefwarp6005		2,6,moc_prydb1.gat,90,115
moc_prydb1.gat,87,115,0		warp	thiefwarp6006		2,6,moc_prydb1.gat,56,115



//==============================================================
// ----- Hunter ハンターギルド -----
// in_hunter.gat	ハンターギルド
// job_hunte.gat	ハンター転職試験場
// hunter_1-1.gat	ハンター転職所
// hunter_2-1.gat	ハンター転職所
// hunter_3-1.gat	ハンター転職所
// -----
// pay_fild01.gat	フェイヨン迷いの森 01 ～ 11
//==============================================================
in_hunter.gat,99,13,0		warp	hunterwarp0502		1,1,pay_fild10.gat,148,252



//==============================================================
// ----- Knight ナイト -----
// knight_1-1.gat	ナイト転職所
// knight_2-1.gat	ナイト転職所
// knight_3-1.gat	ナイト転職所
// job_knt.gat		ナイト転職試験場
// -----
//==============================================================



//==============================================================
// ----- Priest プリースト -----
// priest_1-1.gat	プリースト転職所
// priest_2-1.gat	プリースト転職所
// priest_3-1.gat	プリースト転職所
// job_prist.gat	プリースト転職試験場
// -----
//==============================================================



//==============================================================
// ----- Swordman 剣士 -----
// sword_1-1.gat	剣士転職所
// sword_2-1.gat	剣士転職所
// sword_3-1.gat	剣士転職所
// -----
//==============================================================
sword_1-1.gat,65,117,0		warp	swordwarp6001		1,1,sword_1-1.gat,10,245
sword_1-1.gat,98,27,0		warp	swordwarp6002		1,1,sword_1-1.gat,11,207
sword_1-1.gat,161,27,0		warp	swordwarp6003		1,1,sword_1-1.gat,11,207
sword_1-1.gat,223,205,0		warp	swordwarp6004		1,1,sword_1-1.gat,11,168
sword_1-1.gat,223,243,0		warp	swordwarp6005		1,1,sword_1-1.gat,11,206
sword_1-1.gat,239,117,0		warp	swordwarp6006		1,1,sword_1-1.gat,11,169



//==============================================================
// ----- Wizerd ウィザード -----
// wizard_1-1.gat	ウィザード転職所
// wizard_2-1.gat	ウィザード転職所
// wizard_3-1.gat	ウィザード転職所
// job_wiz.gat		ウィザード転職試験場
// -----
//==============================================================



//==============================================================
// ----- Alberta アルベルタ -----
// alberta.gat		港の都市アルベルタ
// alberta_in		港の都市アルベルタ 室内#
// alb_ship.gat		アルベルタ船舶の中
// -----
// pay_fild01.gat	フェイヨン迷いの森 01 ～ 11
//==============================================================
alberta.gat,15,234,0		warp	albertawarp0501		2,5,pay_fild03.gat,388,63

alberta.gat,117,38,0		warp	albertawarp1001		2,2,alberta_in.gat,180,30
alberta_in.gat,180,34,0		warp	albertawarp1002		2,2,alberta.gat,117,42
alberta.gat,134,38,0		warp	albertawarp1003		1,1,alberta_in.gat,70,141
alberta_in.gat,73,141,0		warp	albertawarp1004		2,3,alberta.gat,137,37
alberta.gat,33,42,0		warp	albertawarp1005		2,2,alberta_in.gat,74,44
alberta_in.gat,78,44,0		warp	albertawarp1006		2,5,alberta.gat,37,41
alberta.gat,65,233,0		warp	albertawarp1007		2,2,alberta_in.gat,18,141
alberta_in.gat,14,141,0		warp	albertawarp1008		2,3,alberta.gat,61,233
alberta.gat,93,205,0		warp	albertawarp1009		2,2,alberta_in.gat,114,134
alberta_in.gat,114,130,0	warp	albertawarp1010		2,2,alberta.gat,93,201
alberta.gat,98,153,0		warp	albertawarp1011		2,2,alberta_in.gat,185,89
alberta_in.gat,189,89,0		warp	albertawarp1012		2,2,alberta.gat,102,153
alberta.gat,99,221,0		warp	albertawarp1013		2,2,alberta_in.gat,122,161
alberta_in.gat,125,161,0	warp	albertawarp1014		2,2,alberta.gat,102,222
alberta_in.gat,114,183,0	warp	albertawarp1015		1,1,alberta_in.gat,148,186
alberta_in.gat,152,186,0	warp	albertawarp1016		1,1,alberta_in.gat,118,183
alberta_in.gat,114,49,0		warp	albertawarp1017		2,2,alberta_in.gat,155,153
alberta_in.gat,159,153,0	warp	albertawarp1018		2,2,alberta_in.gat,117,49
alberta_in.gat,114,97,0		warp	albertawarp1019		2,2,alberta_in.gat,155,175
alberta_in.gat,159,175,0	warp	albertawarp1020		2,2,alberta_in.gat,117,97
alberta_in.gat,22,113,0		warp	albertawarp1021		3,2,alberta_in.gat,22,134
alberta_in.gat,22,130,0		warp	albertawarp1022		3,2,alberta_in.gat,22,109
alberta_in.gat,22,153,0		warp	albertawarp1023		3,2,alberta_in.gat,22,174
alberta_in.gat,22,170,0		warp	albertawarp1024		3,2,alberta_in.gat,22,149
alberta_in.gat,24,33,0		warp	albertawarp1025		3,2,alberta_in.gat,64,35
alberta_in.gat,64,31,0		warp	albertawarp1026		3,2,alberta_in.gat,24,29
alberta_in.gat,24,54,0		warp	albertawarp1027		3,2,alberta_in.gat,64,53
alberta_in.gat,64,57,0		warp	albertawarp1028		3,2,alberta_in.gat,24,58
alberta_in.gat,66,113,0		warp	albertawarp1029		3,1,alberta_in.gat,66,132
alberta_in.gat,66,130,0		warp	albertawarp1030		3,1,alberta_in.gat,66,111
alberta_in.gat,66,153,0		warp	albertawarp1031		3,2,alberta_in.gat,66,173
alberta_in.gat,66,170,0		warp	albertawarp1032		3,2,alberta_in.gat,66,149

alberta.gat,170,170,0		warp	albertawarp1033		1,1,alb_ship.gat,26,168
alb_ship.gat,26,166,0		warp	albertawarp1034		4,1,alberta.gat,170,168
alberta.gat,178,165,0		warp	albertawarp1035		1,2,alb_ship.gat,39,163
alb_ship.gat,41,163,0		warp	albertawarp1036		1,3,alberta.gat,180,165
alberta.gat,209,173,0		warp	albertawarp1037		1,2,alb_ship.gat,162,171
alb_ship.gat,160,171,0		warp	albertawarp1038		1,3,alberta.gat,207,173
alb_ship.gat,37,174,0		warp	albertawarp1039		1,2,alb_ship.gat,70,99
alb_ship.gat,68,99,0		warp	albertawarp1040		1,3,alb_ship.gat,35,173



//==============================================================
// ----- Aldebarana アルデバラン -----
// aldebaran.gat	国境都市アルデバラン
// aldeba_in.gat	国境都市アルデバラン 室内
// alde_alche.gat	アルケミストギルド
// alde_gld.gat		アルデバラン衛星都市ルイーナ
// -----
// c_tower1.gat		アルデバラン時計塔地上 1F
// mjolnir_01.gat	ミョルニール山脈 01 ～ 12
// yuno_fild01.gat	国境検問所
// aldeg_cas01.gat	ルイーナ 砦 1 ～ 5
//==============================================================
alde_gld.gat,48,79,0		warp	aldebaranwarp0301	1,1,aldeg_cas01.gat,34,248
alde_gld.gat,95,253,0		warp	aldebaranwarp0302	1,1,aldeg_cas02.gat,88,163
alde_gld.gat,142,81,0		warp	aldebaranwarp0303	1,1,aldeg_cas03.gat,114,286
alde_gld.gat,243,242,0		warp	aldebaranwarp0304	1,1,aldeg_cas04.gat,149,17
alde_gld.gat,259,90,0		warp	aldebaranwarp0305	1,1,aldeg_cas05.gat,216,103
aldebaran.gat,139,135,0		warp	aldebaranwarp0401	1,1,c_tower1.gat,199,159
aldebaran.gat,138,34,0		warp	aldebaranwarp0501	2,2,mjolnir_12.gat,199,375
aldebaran.gat,140,243,0		warp	aldebaranwarp0502	1,1,yuno_fild01.gat,208,22

aldebaran.gat,118,63,0		warp	aldebaranwarp1001	1,1,aldeba_in.gat,211,117
aldeba_in.gat,208,117,0		warp	aldebaranwarp1002	2,2,aldebaran.gat,116,63
aldebaran.gat,197,70,0		warp	aldebaranwarp1003	1,1,aldeba_in.gat,94,41
aldeba_in.gat,94,38,0		warp	aldebaranwarp1004	3,2,aldebaran.gat,197,68
aldebaran.gat,225,54,0		warp	aldebaranwarp1005	1,1,aldeba_in.gat,149,120
aldeba_in.gat,149,123,0		warp	aldebaranwarp1006	3,2,aldebaran.gat,223,56
aldebaran.gat,233,105,0		warp	aldebaranwarp1007	1,1,aldeba_in.gat,157,190
aldeba_in.gat,157,193,0		warp	aldebaranwarp1008	3,2,aldebaran.gat,231,107
aldebaran.gat,51,218,0		warp	aldebaranwarp1009	1,1,aldeba_in.gat,24,227
aldeba_in.gat,24,224,0		warp	aldebaranwarp1010	2,2,aldebaran.gat,53,216
aldebaran.gat,61,229,0		warp	aldebaranwarp1011	1,1,aldeba_in.gat,148,227
aldeba_in.gat,148,224,0		warp	aldebaranwarp1012	2,2,aldebaran.gat,63,227
aldebaran.gat,72,197,0		warp	aldebaranwarp1013	1,1,aldeba_in.gat,27,37
aldeba_in.gat,27,34,0		warp	aldebaranwarp1014	2,2,aldebaran.gat,72,195
aldebaran.gat,89,234,0		warp	aldebaranwarp1015	1,1,aldeba_in.gat,242,237
aldeba_in.gat,245,237,0		warp	aldebaranwarp1016	2,2,aldebaran.gat,91,234
aldeba_in.gat,103,157,0		warp	aldebaranwarp1017	2,2,aldeba_in.gat,137,237
aldeba_in.gat,134,237,0		warp	aldebaranwarp1018	2,2,aldeba_in.gat,100,157
aldeba_in.gat,103,61,0		warp	aldebaranwarp1019	2,2,aldeba_in.gat,97,105
aldeba_in.gat,97,102,0		warp	aldebaranwarp1020	2,2,aldeba_in.gat,103,58
aldeba_in.gat,144,92,0		warp	aldebaranwarp1021	2,2,aldeba_in.gat,149,52
aldeba_in.gat,149,55,0		warp	aldebaranwarp1022	2,2,aldeba_in.gat,144,95
aldeba_in.gat,217,131,0		warp	aldebaranwarp1023	2,2,aldeba_in.gat,217,163
aldeba_in.gat,217,160,0		warp	aldebaranwarp1024	2,2,aldeba_in.gat,217,128
aldeba_in.gat,218,104,0		warp	aldebaranwarp1025	2,2,aldeba_in.gat,218,68
aldeba_in.gat,217,71,0		warp	aldebaranwarp1026	2,2,aldeba_in.gat,218,107
aldeba_in.gat,27,71,0		warp	aldebaranwarp1027	2,2,aldeba_in.gat,27,105
aldeba_in.gat,27,102,0		warp	aldebaranwarp1028	2,2,aldeba_in.gat,27,68
aldeba_in.gat,37,238,0		warp	aldebaranwarp1029	2,2,aldeba_in.gat,67,157
aldeba_in.gat,64,157,0		warp	aldebaranwarp1030	2,2,aldeba_in.gat,34,238
aldeba_in.gat,83,191,0		warp	aldebaranwarp1031	2,2,aldeba_in.gat,83,227
aldeba_in.gat,83,224,0		warp	aldebaranwarp1032	2,2,aldeba_in.gat,83,188

// Town - Alchemist , Alchemist - Town
aldebaran.gat,54,66,0		warp	aldebaranwarp1033	1,1,alde_alche.gat,41,174
alde_alche.gat,41,171,0		warp	aldebaranwarp1034	1,1,aldebaran.gat,56,68
// Alchemist Hall 1st Floor Top Rooms
alde_alche.gat,129,104,0	warp	aldebaranwarp1035	1,1,alde_alche.gat,163,163
alde_alche.gat,159,163,0	warp	aldebaranwarp1036	1,1,alde_alche.gat,126,104
alde_alche.gat,131,77,0		warp	aldebaranwarp1037	1,1,alde_alche.gat,162,107
alde_alche.gat,159,107,0	warp	aldebaranwarp1038	1,1,alde_alche.gat,128,77
// Alchemist Hall 1st Floor Bottom Rooms
alde_alche.gat,47,103,0		warp	aldebaranwarp1039	1,1,alde_alche.gat,155,18
alde_alche.gat,159,18,0		warp	aldebaranwarp1040	1,1,alde_alche.gat,50,103
alde_alche.gat,47,77,0		warp	aldebaranwarp1041	1,1,alde_alche.gat,88,18
alde_alche.gat,92,18,0		warp	aldebaranwarp1042	1,1,alde_alche.gat,50,77

// Alchemist Hall 2nd Floor - 1st Floor Link
alde_alche.gat,14,184,0		warp	aldebaranwarp1043	1,1,alde_alche.gat,88,113
alde_alche.gat,88,117,0		warp	aldebaranwarp1044	1,1,alde_alche.gat,14,180
// Alchemist Hall 2nd Floor Rooms
alde_alche.gat,19,171,0		warp	aldebaranwarp1045	1,1,aldebaran.gat,68,56
aldebaran.gat,66,54,0		warp	aldebaranwarp1046	1,1,alde_alche.gat,19,175
alde_alche.gat,18,28,0		warp	aldebaranwarp1047	1,1,alde_alche.gat,89,66
alde_alche.gat,89,63,0		warp	aldebaranwarp1048	1,1,alde_alche.gat,18,24
// Alchemist Hall 3rd Floor
alde_alche.gat,41,187,0		warp	aldebaranwarp1049	1,1,alde_alche.gat,114,178
alde_alche.gat,114,182,0	warp	aldebaranwarp1050	1,1,alde_alche.gat,41,183

// aldebaran guild
aldebaran.gat,35,140,0		warp	aldebaranwarp2001	1,1,alde_gld.gat,280,160
alde_gld.gat,284,160,0		warp	aldebaranwarp2002	1,1,aldebaran.gat,39,140



//==============================================================
// ----- Geffen ゲフェン -----
// geffen.gat		魔法の都市ゲフェン
// geffen_in.gat	魔法の都市ゲフェン 室内
// gef_tower.gat	ゲフェン中央塔
// quiz_00.gat		○×クイズ会場
// quiz_01.gat		○×クイズ会場
// -----
// gef_dun00.gat	ゲフェン地下ダンジョン B1F
// gef_fild00.gat	ゲフェンフィールド 00 ～ 11
//==============================================================
gef_tower.gat,153,28,0		warp	geffenwarp0401		4,2,gef_dun00.gat,104,99
geffen.gat,217,119,0		warp	geffenwarp0501		2,4,gef_fild00.gat,46,199
geffen.gat,119,213,0		warp	geffenwarp0502		3,2,gef_fild04.gat,187,42
geffen.gat,26,119,0		warp	geffenwarp0503		2,3,gef_fild07.gat,336,187

geffen.gat,138,138,0		warp	geffenwarp1001		1,1,geffen_in.gat,28,110
geffen_in.gat,28,106,0		warp	geffenwarp1002		1,3,geffen.gat,136,136
geffen.gat,172,174,0		warp	geffenwarp1003		2,2,geffen_in.gat,70,52
geffen_in.gat,70,48,0		warp	geffenwarp1004		3,2,geffen.gat,168,170
geffen.gat,182,59,0		warp	geffenwarp1005		2,2,geffen_in.gat,106,177
geffen_in.gat,106,181,0		warp	geffenwarp1006		2,2,geffen.gat,180,61
geffen.gat,43,85,0		warp	geffenwarp1007		2,2,geffen_in.gat,70,138
geffen_in.gat,70,132,0		warp	geffenwarp1008		3,1,geffen.gat,46,88
geffen.gat,61,180,0		warp	geffenwarp1009		3,3,geffen_in.gat,162,97
geffen_in.gat,163,94,0		warp	geffenwarp1010		4,2,geffen.gat,65,176
geffen.gat,98,141,0		warp	geffenwarp1011		2,2,geffen_in.gat,28,160
geffen_in.gat,28,156,0		warp	geffenwarp1012		3,1,geffen.gat,101,138
geffen_in.gat,100,67,0		warp	geffenwarp1013		2,3,geffen_in.gat,84,65
geffen_in.gat,87,66,0		warp	geffenwarp1014		2,3,geffen_in.gat,103,67
geffen_in.gat,104,109,0		warp	geffenwarp1015		2,2,geffen_in.gat,76,107
geffen_in.gat,79,107,0		warp	geffenwarp1016		2,2,geffen_in.gat,107,109
geffen_in.gat,113,163,0		warp	geffenwarp1017		2,2,geffen_in.gat,139,169
geffen_in.gat,136,169,0		warp	geffenwarp1018		2,2,geffen_in.gat,110,163
geffen_in.gat,114,37,0		warp	geffenwarp1019		1,1,geffen_in.gat,114,63
geffen_in.gat,114,60,0		warp	geffenwarp1020		1,2,geffen_in.gat,114,34
geffen_in.gat,138,149,0		warp	geffenwarp1021		2,2,geffen_in.gat,138,165
geffen_in.gat,138,162,0		warp	geffenwarp1022		2,2,geffen_in.gat,138,146
geffen_in.gat,26,60,0		warp	geffenwarp1023		1,2,geffen_in.gat,26,34
geffen_in.gat,26,37,0		warp	geffenwarp1024		1,1,geffen_in.gat,26,63
geffen_in.gat,52,65,0		warp	geffenwarp1025		2,3,geffen_in.gat,38,67
geffen_in.gat,41,67,0		warp	geffenwarp1026		2,3,geffen_in.gat,55,65
geffen_in.gat,70,149,0		warp	geffenwarp1027		3,2,geffen_in.gat,70,161
geffen_in.gat,70,158,0		warp	geffenwarp1028		3,2,geffen_in.gat,70,146
geffen_in.gat,70,83,0		warp	geffenwarp1029		3,2,geffen_in.gat,72,101
geffen_in.gat,72,98,0		warp	geffenwarp1030		3,2,geffen_in.gat,70,80

//geffen tower
geffen.gat,120,114,0		warp	geffenwarp1031		3,1,gef_tower.gat,52,177
gef_tower.gat,52,181,0		warp	geffenwarp1032		4,1,geffen.gat,120,110
gef_tower.gat,106,115,0		warp	geffenwarp1033		1,1,gef_tower.gat,106,72
gef_tower.gat,106,69,0		warp	geffenwarp1034		1,1,gef_tower.gat,106,112
gef_tower.gat,44,36,0		warp	geffenwarp1035		1,1,gef_tower.gat,106,162
gef_tower.gat,106,158,0		warp	geffenwarp1036		1,1,gef_tower.gat,44,33
gef_tower.gat,118,68,0		warp	geffenwarp1037		1,1,gef_tower.gat,116,28
gef_tower.gat,116,31,0		warp	geffenwarp1038		1,1,gef_tower.gat,118,71
gef_tower.gat,120,158,0		warp	geffenwarp1039		1,1,gef_tower.gat,118,111
gef_tower.gat,118,114,0		warp	geffenwarp1040		1,1,gef_tower.gat,120,161
gef_tower.gat,158,104,0		warp	geffenwarp1041		2,2,gef_tower.gat,156,90
gef_tower.gat,156,93,0		warp	geffenwarp1042		2,2,gef_tower.gat,158,107
gef_tower.gat,158,150,0		warp	geffenwarp1043		1,2,gef_tower.gat,158,124
gef_tower.gat,158,128,0		warp	geffenwarp1044		2,1,gef_tower.gat,158,153
gef_tower.gat,158,174,0		warp	geffenwarp1045		2,1,gef_tower.gat,52,140
gef_tower.gat,52,136,0		warp	geffenwarp1046		2,1,gef_tower.gat,158,169
gef_tower.gat,38,160,0		warp	geffenwarp1047		2,1,gef_tower.gat,42,90
gef_tower.gat,42,86,0		warp	geffenwarp1048		1,1,gef_tower.gat,38,157
gef_tower.gat,66,156,0		warp	geffenwarp1049		2,1,gef_tower.gat,42,90
gef_tower.gat,60,32,0		warp	geffenwarp1050		1,1,gef_tower.gat,62,90
gef_tower.gat,62,87,0		warp	geffenwarp1051		1,1,gef_tower.gat,60,30



//==============================================================
// ----- Morocc モロク -----
// morocc.gat		砂漠の都市モロク
// morocc_in.gat	砂漠の都市モロク 室内
// moc_castle.gat	モロク城内
// moc_ruins.gat	モロク - ピラミッド周辺
// -----
// moc_pryd01.gat	ピラミッドダンジョン 1F
// moc_fild01.gat	ソクラド砂漠 01 ～ 19
// moc_fild20.gat	次元の狭間 01
//==============================================================
moc_ruins.gat,54,161,0		warp	moroccwarp0401		2,3,moc_pryd01.gat,192,9
moc_ruins.gat,71,16,0		warp	moroccwarp0501		8,2,moc_fild19.gat,71,167
morocc.gat,160,297,0		warp	moroccwarp0502		2,2,moc_fild07.gat,198,25
//morocc.gat,302,207,0		warp	moroccwarp0503		2,2,moc_fild10.gat,22,207
morocc.gat,299,207,0		warp	moroccwarp0503		1,1,moc_fild20.gat,36,177
morocc.gat,160,17,0		warp	moroccwarp0504		2,2,moc_fild12.gat,159,378
morocc.gat,24,164,0		warp	moroccwarp0505		1,2,moc_fild19.gat,164,107

morocc.gat,197,66,0		warp	moroccwarp1001		1,1,morocc_in.gat,83,92
morocc_in.gat,83,90,0		warp	moroccwarp1002		4,1,morocc.gat,199,64
morocc.gat,253,56,0		warp	moroccwarp1003		2,1,morocc_in.gat,134,74
morocc_in.gat,134,77,0		warp	moroccwarp1004		3,1,morocc.gat,251,59
morocc.gat,274,269,0		warp	moroccwarp1005		2,2,morocc_in.gat,138,136
morocc_in.gat,136,136,0		warp	moroccwarp1006		1,4,morocc.gat,271,269
morocc.gat,46,46,0		warp	moroccwarp1007		2,1,morocc_in.gat,68,72
morocc_in.gat,68,75,0		warp	moroccwarp1008		2,1,morocc.gat,49,49
morocc.gat,52,259,0		warp	moroccwarp1009		1,2,morocc_in.gat,180,65
morocc_in.gat,183,65,0		warp	moroccwarp1010		2,3,morocc.gat,55,259
morocc.gat,283,170,0		warp	moroccwarp1011		2,2,morocc_in.gat,108,176
morocc_in.gat,108,179,0		warp	moroccwarp1012		2,2,morocc.gat,283,173
morocc.gat,85,55,0		warp	moroccwarp1013		2,2,morocc_in.gat,44,149
morocc_in.gat,44,146,0		warp	moroccwarp1014		3,2,morocc.gat,82,52
morocc.gat,98,68,0		warp	moroccwarp1015		1,1,morocc_in.gat,44,175
morocc_in.gat,44,178,0		warp	moroccwarp1016		2,2,morocc.gat,100,70
morocc_in.gat,93,95,0		warp	moroccwarp1017		1,3,morocc_in.gat,109,95
morocc_in.gat,105,95,0		warp	moroccwarp1018		1,3,morocc_in.gat,90,95
morocc_in.gat,93,123,0		warp	moroccwarp1019		1,3,morocc_in.gat,109,123
morocc_in.gat,106,123,0		warp	moroccwarp1020		1,3,morocc_in.gat,90,123
morocc_in.gat,144,122,0		warp	moroccwarp1021		3,1,morocc_in.gat,144,106
morocc_in.gat,144,109,0		warp	moroccwarp1022		3,1,morocc_in.gat,144,125
morocc_in.gat,144,151,0		warp	moroccwarp1023		3,1,morocc_in.gat,144,169
morocc_in.gat,144,166,0		warp	moroccwarp1024		3,1,morocc_in.gat,144,148
morocc_in.gat,149,129,0		warp	moroccwarp1025		1,2,morocc_in.gat,169,129
morocc_in.gat,166,130,0		warp	moroccwarp1026		1,3,morocc_in.gat,146,130
morocc_in.gat,171,50,0		warp	moroccwarp1027		4,1,morocc_in.gat,171,35
morocc_in.gat,171,37,0		warp	moroccwarp1028		4,1,morocc_in.gat,171,52
morocc_in.gat,174,151,0		warp	moroccwarp1029		3,1,morocc_in.gat,174,169
morocc_in.gat,174,166,0		warp	moroccwarp1030		3,1,morocc_in.gat,174,148
morocc_in.gat,23,161,0		warp	moroccwarp1031		1,2,morocc_in.gat,37,161
morocc_in.gat,34,161,0		warp	moroccwarp1032		1,2,morocc_in.gat,20,161
morocc_in.gat,68,123,0		warp	moroccwarp1033		1,3,morocc_in.gat,52,123
morocc_in.gat,55,123,0		warp	moroccwarp1034		1,3,morocc_in.gat,71,123
morocc_in.gat,68,95,0		warp	moroccwarp1035		1,3,morocc_in.gat,52,95
morocc_in.gat,55,95,0		warp	moroccwarp1036		1,3,morocc_in.gat,71,95
morocc_in.gat,57,161,0		warp	moroccwarp1037		1,3,morocc_in.gat,73,161
morocc_in.gat,70,161,0		warp	moroccwarp1038		1,3,morocc_in.gat,54,161
morocc_in.gat,68,62,0		warp	moroccwarp1039		2,1,morocc_in.gat,68,38
morocc_in.gat,68,42,0		warp	moroccwarp1040		2,1,morocc_in.gat,68,65
morocc_in.gat,174,109,0		warp	moroccwarp1041		3,1,morocc_in.gat,174,125
morocc_in.gat,174,122,0		warp	moroccwarp1042		3,1,morocc_in.gat,174,106
morocc_in.gat,86,101,0		warp	moroccwarp1043		2,1,morocc_in.gat,86,120
morocc_in.gat,86,117,0		warp	moroccwarp1044		3,1,morocc_in.gat,86,98

// morocc castle
//morocc.gat,160,183,0		warp	moroccwarp1045		2,1,moc_castle.gat,94,181
morocc.gat,287,64,0		warp	moroccwarp1045		2,1,moc_castle.gat,134,136
moc_castle.gat,94,183,0		warp	moroccwarp1046		2,1,morocc.gat,160,185
moc_castle.gat,107,163,0	warp	moroccwarp1047		2,3,moc_castle.gat,124,163
moc_castle.gat,120,163,0	warp	moroccwarp1048		2,3,moc_castle.gat,103,163
moc_castle.gat,120,75,0		warp	moroccwarp1049		2,3,moc_castle.gat,56,33
moc_castle.gat,59,34,0		warp	moroccwarp1050		2,3,moc_castle.gat,124,75
moc_castle.gat,134,101,0	warp	moroccwarp1051		1,1,moc_castle.gat,134,128
moc_castle.gat,134,124,0	warp	moroccwarp1052		2,2,moc_castle.gat,134,98
//moc_castle.gat,134,139,0	warp	moroccwarp1053		1,1,moc_castle.gat,134,160
moc_castle.gat,134,139,0	warp	moroccwarp1053		1,1,morocc.gat,283,64
moc_castle.gat,134,156,0	warp	moroccwarp1054		2,2,moc_castle.gat,134,136
moc_castle.gat,149,163,0	warp	moroccwarp1055		2,3,moc_castle.gat,162,163
moc_castle.gat,158,163,0	warp	moroccwarp1056		2,3,moc_castle.gat,145,163
moc_castle.gat,16,131,0		warp	moroccwarp1057		1,2,moc_castle.gat,16,164
moc_castle.gat,16,160,0		warp	moroccwarp1058		1,2,moc_castle.gat,16,125
moc_castle.gat,170,131,0	warp	moroccwarp1059		2,2,moc_castle.gat,170,163
moc_castle.gat,170,160,0	warp	moroccwarp1060		1,1,moc_castle.gat,170,128
moc_castle.gat,29,163,0		warp	moroccwarp1061		2,2,moc_castle.gat,44,163
moc_castle.gat,40,163,0		warp	moroccwarp1062		2,2,moc_castle.gat,25,163
moc_castle.gat,51,114,0		warp	moroccwarp1063		3,2,moc_castle.gat,54,65
moc_castle.gat,54,69,0		warp	moroccwarp1064		3,2,moc_castle.gat,52,117
//moc_castle.gat,54,139,0	warp	moroccwarp1065		2,2,moc_castle.gat,54,160
moc_castle.gat,54,156,0		warp	moroccwarp1066		2,2,moc_castle.gat,54,134
moc_castle.gat,63,89,0		warp	moroccwarp1067		2,3,moc_castle.gat,83,89
moc_castle.gat,80,89,0		warp	moroccwarp1068		2,3,moc_castle.gat,60,89
moc_castle.gat,69,163,0		warp	moroccwarp1069		2,2,moc_castle.gat,86,163
moc_castle.gat,82,163,0		warp	moroccwarp1070		2,2,moc_castle.gat,66,163
moc_castle.gat,88,93,0		warp	moroccwarp1071		1,1,moc_castle.gat,94,119
moc_castle.gat,94,116,0		warp	moroccwarp1072		1,1,moc_castle.gat,88,90
moc_castle.gat,96,90,0		warp	moroccwarp1073		1,1,moc_castle.gat,94,119
moc_castle.gat,92,67,0		warp	moroccwarp1074		3,2,moc_castle.gat,92,85
moc_castle.gat,92,82,0		warp	moroccwarp1075		3,2,moc_castle.gat,92,63
moc_castle.gat,94,143,0		warp	moroccwarp1076		3,2,moc_castle.gat,94,160
moc_castle.gat,94,156,0		warp	moroccwarp1077		3,2,moc_castle.gat,94,140

// ピラミッド周辺
morocc.gat,25,294,0		warp	moroccwarp1078		3,3,moc_ruins.gat,156,42
moc_ruins.gat,159,37,0		warp	moroccwarp1079		3,3,morocc.gat,28,291



//==============================================================
// ----- Payon フェイヨン -----
// payon.gat		山岳の都市フェイヨン
// payon_in01.gat	山岳の都市フェイヨン 室内 1 ～ 3
// pay_arche.gat	山岳の都市フェイヨン
// pay_gld.gat		チュンリム湖
// -----
// pay_fild01.gat	フェイヨン迷いの森 01 ～ 11
// moc_fild01.gat	ソクラド砂漠 01 ～ 19
// pay_dun00.gat	フェイヨン地下洞窟 B1F
// payg_cas01.gat	チュンリム湖 砦 1 ～ 5
//==============================================================
pay_gld.gat,121,238,0		warp	payonwarp0301		1,1,payg_cas01.gat,214,48
pay_gld.gat,291,116,0		warp	payonwarp0302		1,1,payg_cas02.gat,272,57
pay_gld.gat,321,293,0		warp	payonwarp0303		1,1,payg_cas03.gat,226,26
pay_gld.gat,140,156,0		warp	payonwarp0304		1,1,payg_cas04.gat,252,271
pay_gld.gat,204,270,0		warp	payonwarp0305		1,1,payg_cas05.gat,62,227
pay_arche.gat,36,131,0		warp	payonwarp0401		2,2,pay_dun00.gat,21,183
payon.gat,122,27,0		warp	payonwarp0501		5,3,pay_fild01.gat,333,356
payon.gat,267,89,0		warp	payonwarp0502		2,4,pay_fild08.gat,20,74
pay_gld.gat,16,276,0		warp	payonwarp0503		1,1,moc_fild02.gat,374,272

// 酒場
payon.gat,223,117,0		warp	payonwarp1001		2,2,payon_in01.gat,175,11
payon_in01.gat,172,11,0		warp	payonwarp1002		2,2,payon.gat,219,117
payon_in01.gat,180,43,0		warp	payonwarp1003		2,2,payon_in01.gat,181,73
payon_in01.gat,181,70,0		warp	payonwarp1004		2,2,payon_in01.gat,180,40
payon_in01.gat,193,92,0		warp	payonwarp1005		2,2,payon_in01.gat,143,61
payon_in01.gat,146,61,0		warp	payonwarp1006		2,2,payon_in01.gat,193,89
payon_in01.gat,133,42,0		warp	payonwarp1007		2,2,payon_in01.gat,133,18
payon_in01.gat,133,21,0		warp	payonwarp1008		2,2,payon_in01.gat,133,45
// 道具店と道具商人
payon.gat,140,85,0		warp	payonwarp1009		2,2,payon_in01.gat,14,51
payon_in01.gat,17,51,0		warp	payonwarp1010		2,2,payon.gat,143,85
payon_in01.gat,10,59,0		warp	payonwarp1011		2,2,payon_in01.gat,10,83
payon_in01.gat,10,80,0		warp	payonwarp1012		2,2,payon_in01.gat,10,56
payon_in01.gat,10,38,0		warp	payonwarp1013		2,2,payon_in01.gat,10,14
payon_in01.gat,10,17,0		warp	payonwarp1014		2,2,payon_in01.gat,10,41
// 武器・防具屋
payon.gat,135,158,0		warp	payonwarp1015		2,2,payon_in01.gat,20,129
payon_in01.gat,23,129,0		warp	payonwarp1016		2,2,payon.gat,138,158
payon.gat,130,169,0		warp	payonwarp1017		2,2,payon_in01.gat,13,136
payon_in01.gat,13,139,0		warp	payonwarp1018		2,2,payon.gat,130,172
// アーチャー兄弟の家
payon.gat,151,127,0		warp	payonwarp1019		2,2,payon_in01.gat,56,53
payon_in01.gat,56,50,0		warp	payonwarp1020		2,2,payon.gat,151,124
// 中央宮
payon.gat,156,247,0		warp	payonwarp1021		2,2,payon_in03.gat,98,117
payon_in03.gat,98,114,0		warp	payonwarp1022		2,2,payon.gat,156,244
payon_in03.gat,90,124,0		warp	payonwarp1023		2,2,payon_in03.gat,80,124
payon_in03.gat,83,124,0		warp	payonwarp1024		2,2,payon_in03.gat,93,124
payon_in03.gat,99,133,0		warp	payonwarp1025		2,2,payon_in03.gat,99,151
payon_in03.gat,99,148,0		warp	payonwarp1026		2,2,payon_in03.gat,99,130
payon_in03.gat,107,124,0	warp	payonwarp1027		2,2,payon_in03.gat,117,124
payon_in03.gat,114,124,0	warp	payonwarp1028		2,2,payon_in03.gat,104,124
// ハンターの家
payon.gat,189,233,0		warp	payonwarp1029		2,2,payon_in03.gat,149,39
payon_in03.gat,146,39,0		warp	payonwarp1030		2,2,payon.gat,186,233
payon_in03.gat,158,32,0		warp	payonwarp1031		2,2,payon_in03.gat,130,14
payon_in03.gat,130,17,0		warp	payonwarp1032		2,2,payon_in03.gat,158,35
payon_in03.gat,172,32,0		warp	payonwarp1033		2,2,payon_in03.gat,160,14
payon_in03.gat,160,17,0		warp	payonwarp1034		2,2,payon_in03.gat,172,35
payon_in03.gat,186,32,0		warp	payonwarp1035		2,2,payon_in03.gat,190,13
payon_in03.gat,190,17,0		warp	payonwarp1036		2,2,payon_in03.gat,186,35
// -- House --
payon.gat,256,285,0		warp	payonwarp1037		2,2,payon_in01.gat,45,11
payon_in01.gat,42,11,0		warp	payonwarp1038		2,2,payon.gat,253,285
// -- Old Archer Village Warps --
payon.gat,228,330,0		warp	payonwarp1039		4,2,pay_arche.gat,81,22
pay_arche.gat,81,18,0		warp	payonwarp1040		5,2,payon.gat,228,326
//pay_arche.gat,81,17,0		warp	payonwarp1040		5,2,payon.gat,175,185
pay_arche.gat,71,156,0		warp	payonwarp1041		2,2,payon_in02.gat,82,41
pay_arche.gat,92,170,0		warp	payonwarp1042		2,2,payon_in02.gat,50,7
pay_arche.gat,145,165,0		warp	payonwarp1043		2,2,payon_in02.gat,64,60
payon_in02.gat,10,25,0		warp	payonwarp1044		2,2,payon_in02.gat,72,67
payon_in02.gat,35,67,0		warp	payonwarp1045		2,2,payon_in02.gat,55,67
payon_in02.gat,50,4,0		warp	payonwarp1046		3,1,pay_arche.gat,92,166
payon_in02.gat,52,67,0		warp	payonwarp1047		2,2,payon_in02.gat,32,67
payon_in02.gat,61,33,0		warp	payonwarp1048		2,2,payon_in02.gat,73,33
payon_in02.gat,64,56,0		warp	payonwarp1049		2,2,pay_arche.gat,141,161
payon_in02.gat,70,33,0		warp	payonwarp1050		2,2,payon_in02.gat,58,33
payon_in02.gat,75,67,0		warp	payonwarp1051		2,2,payon_in02.gat,13,25
payon_in02.gat,82,45,0		warp	payonwarp1052		2,2,pay_arche.gat,74,153
// 宮殿の別館
payon.gat,128,204,0		warp	payonwarp1053		2,2,payon_in03.gat,82,19
payon_in03.gat,85,19,0		warp	payonwarp1054		2,2,payon.gat,130,204
payon_in03.gat,74,19,0		warp	payonwarp1055		2,2,payon_in03.gat,64,19
payon_in03.gat,67,19,0		warp	payonwarp1056		2,2,payon_in03.gat,77,19
payon_in03.gat,46,19,0		warp	payonwarp1057		2,2,payon_in03.gat,36,19
payon_in03.gat,39,19,0		warp	payonwarp1058		2,2,payon_in03.gat,49,19
payon_in03.gat,28,19,0		warp	payonwarp1059		2,2,payon_in03.gat,18,19
payon_in03.gat,21,19,0		warp	payonwarp1060		2,2,payon_in03.gat,31,19
// 弓手の間
payon.gat,155,328,0		warp	payonwarp1061		2,2,payon_in03.gat,165,143
payon_in03.gat,165,140,0	warp	payonwarp1062		2,2,payon.gat,155,325
payon_in03.gat,185,178,0	warp	payonwarp1063		2,2,payon_in03.gat,185,150
payon_in03.gat,185,153,0	warp	payonwarp1064		2,2,payon_in03.gat,185,181
// 宮殿の前庭
payon.gat,107,327,0		warp	payonwarp1065		2,2,payon_in03.gat,20,63
payon_in03.gat,20,60,0		warp	payonwarp1066		2,2,payon.gat,107,323
payon_in03.gat,20,73,0		warp	payonwarp1067		2,2,payon_in03.gat,20,90
payon_in03.gat,20,86,0		warp	payonwarp1068		2,2,payon_in03.gat,20,70
payon_in03.gat,20,103,0		warp	payonwarp1069		2,2,payon_in03.gat,20,121
payon_in03.gat,20,118,0		warp	payonwarp1070		2,2,payon_in03.gat,20,100
payon_in03.gat,12,131,0		warp	payonwarp1071		2,2,payon_in03.gat,12,145
payon_in03.gat,12,142,0		warp	payonwarp1072		2,2,payon_in03.gat,12,128
payon_in03.gat,28,131,0		warp	payonwarp1073		2,2,payon_in03.gat,28,145
payon_in03.gat,28,142,0		warp	payonwarp1074		2,2,payon_in03.gat,28,128
payon_in03.gat,12,161,0		warp	payonwarp1075		2,2,payon_in03.gat,12,175
payon_in03.gat,12,172,0		warp	payonwarp1076		2,2,payon_in03.gat,12,158
payon_in03.gat,28,161,0		warp	payonwarp1077		2,2,payon_in03.gat,28,175
payon_in03.gat,28,172,0		warp	payonwarp1078		2,2,payon_in03.gat,28,158
// 民家
payon_in01.gat,86,9,0		warp	payonwarp1079		2,2,payon.gat,266,152
payon.gat,270,152,0		warp	payonwarp1080		2,2,payon_in01.gat,89,9
payon_in01.gat,107,71,0		warp	payonwarp1081		2,2,payon_in01.gat,95,37
payon_in01.gat,92,37,0		warp	payonwarp1082		2,2,payon_in01.gat,104,71

// payon guild
payon.gat,16,143,0		warp	payonwarp2001		1,1,pay_gld.gat,370,149
pay_gld.gat,374,149,0		warp	payonwarp2002		1,1,payon.gat,19,143



//==============================================================
// ----- Prontera プロンテラ -----
// prontera.gat		ルーンミッドガッツ王国の首都プロンテラ
// prt_in.gat		プロンテラ 室内
// prt_church.gat	プロンテラ聖堂内
// prt_castle.gat	プロンテラ城内
// prt_gld.gat		ヴァルキリーレルム
// job_cru.gat		クルセイダー転職試験場
// -----
// prt_fild00.gat	プロンテラフィールド 00 ～ 11
// prtg_cas01.gat	ヴァルキリーレルム 砦 1 ～ 5
//==============================================================
prt_gld.gat,129,65,0		warp	pronterawarp0301	1,1,prtg_cas01.gat,99,32
prt_gld.gat,240,124,0		warp	pronterawarp0302	1,1,prtg_cas02.gat,43,229
prt_gld.gat,153,141,0		warp	pronterawarp0303	1,1,prtg_cas03.gat,168,12
prt_gld.gat,107,240,0		warp	pronterawarp0304	1,1,prtg_cas04.gat,86,13
prt_gld.gat,212,240,0		warp	pronterawarp0305	1,1,prtg_cas05.gat,17,235
//prt_castle.gat,102,181,0	warp	pronterawarp0501	6,2,prt_fild01.gat,199,30
prt_gld.gat,159,298,0		warp	pronterawarp0501	1,1,prt_fild01.gat,199,30
prontera.gat,22,203,0		warp	pronterawarp0502	2,3,prt_fild05.gat,367,205
prontera.gat,289,203,0		warp	pronterawarp0503	2,3,prt_fild06.gat,27,193
prontera.gat,156,22,0		warp	pronterawarp0504	3,2,prt_fild08.gat,170,375

// prontera castle
prontera.gat,156,360,0		warp	pronterawarp1001	4,2,prt_castle.gat,102,20
prt_castle.gat,102,16,0		warp	pronterawarp1002	6,2,prontera.gat,156,356
prt_castle.gat,102,129,0	warp	pronterawarp1003	3,2,prt_castle.gat,102,143
prt_castle.gat,102,140,0	warp	pronterawarp1004	3,2,prt_castle.gat,102,126
prt_castle.gat,102,73,0		warp	pronterawarp1005	3,2,prt_castle.gat,102,91
prt_castle.gat,102,88,0		warp	pronterawarp1006	3,2,prt_castle.gat,102,70
prt_castle.gat,113,107,0	warp	pronterawarp1007	2,3,prt_castle.gat,134,107
prt_castle.gat,130,107,0	warp	pronterawarp1008	2,3,prt_castle.gat,110,107
prt_castle.gat,121,29,0		warp	pronterawarp1009	1,1,prt_castle.gat,148,29
prt_castle.gat,144,29,0		warp	pronterawarp1010	2,2,prt_castle.gat,117,29
prt_castle.gat,135,153,0	warp	pronterawarp1011	1,1,prt_castle.gat,167,145
prt_castle.gat,164,145,0	warp	pronterawarp1012	1,1,prt_castle.gat,132,153
prt_castle.gat,149,113,0	warp	pronterawarp1013	1,1,prt_castle.gat,175,113
prt_castle.gat,172,113,0	warp	pronterawarp1014	1,1,prt_castle.gat,146,113
prt_castle.gat,170,138,0	warp	pronterawarp1015	3,2,prt_castle.gat,176,118
prt_castle.gat,176,121,0	warp	pronterawarp1016	3,2,prt_castle.gat,170,141
prt_castle.gat,28,121,0		warp	pronterawarp1017	2,2,prt_castle.gat,40,141
prt_castle.gat,40,138,0		warp	pronterawarp1018	3,2,prt_castle.gat,28,118
prt_castle.gat,31,113,0		warp	pronterawarp1019	1,1,prt_castle.gat,58,113
prt_castle.gat,54,113,0		warp	pronterawarp1020	1,1,prt_castle.gat,27,113
prt_castle.gat,45,145,0		warp	pronterawarp1021	1,1,prt_castle.gat,72,153
prt_castle.gat,68,153,0		warp	pronterawarp1022	1,1,prt_castle.gat,42,145
prt_castle.gat,59,29,0		warp	pronterawarp1023	2,2,prt_castle.gat,85,29
prt_castle.gat,82,29,0		warp	pronterawarp1024	1,1,prt_castle.gat,56,29
prt_castle.gat,75,107,0		warp	pronterawarp1025	2,3,prt_castle.gat,95,107
prt_castle.gat,92,107,0		warp	pronterawarp1026	2,3,prt_castle.gat,72,107
// church
prontera.gat,237,317,0		warp	pronterawarp1027	2,2,prt_church.gat,100,60
prt_church.gat,100,56,0		warp	pronterawarp1028	7,1,prontera.gat,234,314
prt_church.gat,109,81,0		warp	pronterawarp1029	1,2,prt_church.gat,172,19
prt_church.gat,168,19,0		warp	pronterawarp1030	1,2,prt_church.gat,105,81
prt_church.gat,31,19,0		warp	pronterawarp1031	1,2,prt_church.gat,94,81
prt_church.gat,90,81,0		warp	pronterawarp1032	1,2,prt_church.gat,27,19
// 街
prontera.gat,107,215,0		warp	pronterawarp1033	2,2,prt_in.gat,240,139
prt_in.gat,240,141,0		warp	pronterawarp1034	3,1,prontera.gat,107,218
prontera.gat,120,267,0		warp	pronterawarp1035	2,2,prt_in.gat,180,97
prt_in.gat,183,97,0		warp	pronterawarp1036	1,2,prontera.gat,120,264
prontera.gat,133,183,0		warp	pronterawarp1037	2,2,prt_in.gat,50,105
prt_in.gat,53,105,0		warp	pronterawarp1038	1,2,prontera.gat,136,186
prontera.gat,134,221,0		warp	pronterawarp1039	1,1,prt_in.gat,131,71
prt_in.gat,135,71,0		warp	pronterawarp1040	1,2,prontera.gat,136,219
prontera.gat,177,221,0		warp	pronterawarp1041	2,2,prt_in.gat,168,128
prt_in.gat,168,124,0		warp	pronterawarp1042	2,1,prontera.gat,174,218
prontera.gat,179,184,0		warp	pronterawarp1043	2,2,prt_in.gat,60,73
prt_in.gat,60,77,0		warp	pronterawarp1044	2,1,prontera.gat,175,188
prontera.gat,192,267,0		warp	pronterawarp1045	2,2,prt_in.gat,178,55
prt_in.gat,181,55,0		warp	pronterawarp1046	1,2,prontera.gat,192,264
prontera.gat,204,192,0		warp	pronterawarp1047	2,2,prt_in.gat,68,134
prt_in.gat,68,130,0		warp	pronterawarp1048	2,1,prontera.gat,204,188
prontera.gat,208,154,0		warp	pronterawarp1049	2,2,prt_in.gat,172,29
prt_in.gat,172,33,0		warp	pronterawarp1050	2,1,prontera.gat,205,157
prontera.gat,42,67,0		warp	pronterawarp1051	2,2,prt_in.gat,44,29
prt_in.gat,47,29,0		warp	pronterawarp1052	2,1,prontera.gat,46,67
prontera.gat,45,346,0		warp	pronterawarp1053	2,2,prt_in.gat,80,110
prt_in.gat,80,113,0		warp	pronterawarp1054	2,1,prontera.gat,48,343
prontera.gat,73,100,0		warp	pronterawarp1055	1,1,prt_in.gat,208,176
prt_in.gat,208,179,0		warp	pronterawarp1056	3,1,prontera.gat,76,102
prontera.gat,74,90,0		warp	pronterawarp1057	2,2,prt_in.gat,248,170
prt_in.gat,248,173,0		warp	pronterawarp1058	3,2,prontera.gat,77,93
prt_in.gat,282,179,0		warp	pronterawarp1059	3,1,prontera.gat,87,91
prontera.gat,84,89,0		warp	pronterawarp1060	1,1,prt_in.gat,282,176
prt_in.gat,217,163,0		warp	pronterawarp1061	1,3,prt_in.gat,236,163
prt_in.gat,234,163,0		warp	pronterawarp1062	1,3,prt_in.gat,215,163
prt_in.gat,254,113,0		warp	pronterawarp1063	3,2,prt_in.gat,256,134
prt_in.gat,256,131,0		warp	pronterawarp1064	2,2,prt_in.gat,254,110
prt_in.gat,263,163,0		warp	pronterawarp1065	1,3,prt_in.gat,276,163
prt_in.gat,274,163,0		warp	pronterawarp1066	1,3,prt_in.gat,261,163
prt_in.gat,37,65,0		warp	pronterawarp1067	1,3,prt_in.gat,51,65
prt_in.gat,48,65,0		warp	pronterawarp1068	1,3,prt_in.gat,34,65
prt_in.gat,69,65,0		warp	pronterawarp1069	1,3,prt_in.gat,85,65
prt_in.gat,82,65,0		warp	pronterawarp1070	1,3,prt_in.gat,66,65
prt_in.gat,70,143,0		warp	pronterawarp1071	2,1,prt_in.gat,70,165
prt_in.gat,70,162,0		warp	pronterawarp1072	2,1,prt_in.gat,70,140

// prontera guild
prt_castle.gat,102,181,0	warp	pronterawarp2001	6,2,prt_gld.gat,159,28
prt_gld.gat,159,25,0		warp	pronterawarp2002	6,2,prt_castle.gat,102,178



//==============================================================
// ----- Izlude イズルード -----
// izlude.gat		衛星都市イズルード
// izlude_in.gat	衛星都市イズルード 室内
// prt_are_in.gat	アリーナ待機室
// arena_room.gat	アリーナ待機室
// -----
// prt_fild00.gat	プロンテラフィールド 00 ～ 11
//==============================================================
izlude.gat,30,78,0		warp	izludewarp0501		3,3,prt_fild08.gat,367,212

izlude.gat,109,151,0		warp	izludewarp1001		3,3,izlude_in.gat,65,87
izlude_in.gat,65,84,0		warp	izludewarp1002		5,2,izlude.gat,113,147
izlude.gat,148,148,0		warp	izludewarp1003		2,2,izlude_in.gat,116,49
izlude_in.gat,116,46,0		warp	izludewarp1004		3,2,izlude.gat,145,145
izlude.gat,216,129,0		warp	izludewarp1005		3,2,izlude_in.gat,151,127
izlude_in.gat,148,127,0		warp	izludewarp1006		2,5,izlude.gat,212,129
izlude.gat,52,140,0		warp	izludewarp1007		2,2,izlude_in.gat,74,161
izlude_in.gat,74,158,0		warp	izludewarp1008		3,2,izlude.gat,52,136
izlude_in.gat,108,169,0		warp	izludewarp1009		2,3,izlude_in.gat,84,169
izlude_in.gat,87,169,0		warp	izludewarp1010		2,3,izlude_in.gat,111,169
izlude_in.gat,171,97,0		warp	izludewarp1011		3,2,izlude_in.gat,172,119
izlude_in.gat,172,116,0		warp	izludewarp1012		3,2,izlude_in.gat,172,94
izlude_in.gat,172,139,0		warp	izludewarp1013		3,2,izlude_in.gat,172,161
izlude_in.gat,172,158,0		warp	izludewarp1014		3,2,izlude_in.gat,172,136

// Swordman
izlude_in.gat,43,169,0		warp	izludewarp1015		2,3,izlude_in.gat,64,169

// イズルード空港
izlude.gat,149,39,0		warp	izludewarp1016		1,1,izlude.gat,182,56
izlude.gat,176,56,0		warp	izludewarp1017		1,1,izlude.gat,145,40

// arena
izlude.gat,128,226,0		warp	izludewarp1101		1,1,arena_room.gat,100,30
arena_room.gat,99,24,0		warp	izludewarp1102		1,1,izlude.gat,128,220
arena_room.gat,84,71,0		warp	izludewarp1103		1,1,arena_room.gat,60,50
arena_room.gat,63,53,0		warp	izludewarp1104		1,1,arena_room.gat,86,74
arena_room.gat,77,88,0		warp	izludewarp1105		1,1,arena_room.gat,46,87
arena_room.gat,49,87,0		warp	izludewarp1106		1,1,arena_room.gat,80,88
arena_room.gat,84,103,0		warp	izludewarp1107		1,1,arena_room.gat,63,130
arena_room.gat,63,126,0		warp	izludewarp1108		1,1,arena_room.gat,86,101
arena_room.gat,115,71,0		warp	izludewarp1109		1,1,arena_room.gat,139,50
arena_room.gat,136,53,0		warp	izludewarp1110		1,1,arena_room.gat,113,74
arena_room.gat,123,88,0		warp	izludewarp1111		1,1,arena_room.gat,153,87
arena_room.gat,150,87,0		warp	izludewarp1112		1,1,arena_room.gat,120,88
//arena_room.gat,114,102,0	warp	izludewarp1113		1,1,arena_room.gat,135,129
arena_room.gat,135,126,0	warp	izludewarp1114		1,1,arena_room.gat,111,99
prt_are_in.gat,54,13,0		warp	izludewarp1115		1,1,arena_room.gat,100,77



//==============================================================
// ----- Glast Heim グラストヘイム -----
// glast_01.gat		グラストヘイム古城
// -----
// gl_step.gat		グラストヘイム 階段ダンジョン
// gl_knt01.gat		グラストヘイム 騎士団内
// gl_in01.gat		グラストヘイム 室内
// gl_cas01.gat		グラストヘイム古城 1F
// gl_cas02.gat		グラストヘイム古城 2F
// gl_church.gat	グラストヘイム 修道院
// gef_fild00.gat	ゲフェンフィールド 00 ～ 11
//==============================================================
glast_01.gat,51,108,0		warp	glastwarp0401		1,1,gl_step.gat,12,7
glast_01.gat,77,193,0		warp	glastwarp0402		1,1,gl_knt01.gat,150,15
glast_01.gat,162,330,0		warp	glastwarp0403		1,1,gl_in01.gat,77,68
glast_01.gat,179,360,0		warp	glastwarp0404		1,1,gl_in01.gat,80,174
glast_01.gat,220,360,0		warp	glastwarp0405		1,1,gl_in01.gat,110,125
glast_01.gat,237,330,0		warp	glastwarp0406		1,1,gl_in01.gat,122,59
glast_01.gat,200,297,0		warp	glastwarp0407		1,1,gl_cas01.gat,199,29
glast_01.gat,199,322,0		warp	glastwarp0408		1,1,gl_cas02.gat,104,189
glast_01.gat,200,137,0		warp	glastwarp0409		1,1,gl_church.gat,156,7

glast_01.gat,380,304,0		warp	glastwarp0501		3,3,gef_fild06.gat,22,304



//---JP2.0 追加マップ---


//==============================================================
// ----- Comodo コモド -----
// comodo.gat		幻想の島コモド
// cmd_in01.gat		コモド室内
// cmd_in02.gat		コモド室内
// job_duncer.gat	コモド小劇場
// -----
// beach_dun.gat	西洞窟 カル
// beach_dun2.gat	北洞窟 ルワンダ
// beach_dun3.gat	東洞窟 マオ
//==============================================================
comodo.gat,25,214,0		warp	comodowarp0401		1,1,beach_dun.gat,266,67
comodo.gat,176,358,0		warp	comodowarp0402		1,1,beach_dun2.gat,154,25
comodo.gat,332,175,0		warp	comodowarp0403		1,1,beach_dun3.gat,23,260

comodo.gat,140,90,0		warp	comodowarp1001		1,1,cmd_in02.gat,74,25
cmd_in02.gat,74,21,0		warp	comodowarp1002		1,1,comodo.gat,140,86
comodo.gat,126,98,0		warp	comodowarp1003		1,1,cmd_in02.gat,144,97
cmd_in02.gat,139,97,0		warp	comodowarp1004		1,1,comodo.gat,122,98
comodo.gat,153,97,0		warp	comodowarp1004		1,1,cmd_in02.gat,212,97
cmd_in02.gat,216,97,0		warp	comodowarp1005		1,1,comodo.gat,157,97
comodo.gat,140,111,0		warp	comodowarp1006		1,1,cmd_in02.gat,178,132
cmd_in02.gat,178,136,0		warp	comodowarp1007		1,1,comodo.gat,140,115
comodo.gat,130,195,0		warp	comodowarp1008		1,1,cmd_in02.gat,143,173
cmd_in02.gat,139,169,0		warp	comodowarp1009		1,1,comodo.gat,127,191
comodo.gat,265,74,0		warp	comodowarp1010		1,1,cmd_in01.gat,123,180
cmd_in01.gat,123,186,0		warp	comodowarp1011		1,1,comodo.gat,265,79
comodo.gat,92,128,0		warp	comodowarp1012		1,1,cmd_in01.gat,85,174
cmd_in01.gat,90,174,0		warp	comodowarp1013		1,1,comodo.gat,97,128
comodo.gat,236,298,0		warp	comodowarp1014		1,1,cmd_in01.gat,179,81
cmd_in01.gat,183,81,0		warp	comodowarp1015		1,1,comodo.gat,239,296
comodo.gat,115,291,0		warp	comodowarp1016		1,1,cmd_in02.gat,67,132
cmd_in02.gat,69,129,0		warp	comodowarp1017		4,4,comodo.gat,115,288
comodo.gat,271,271,0		warp	comodowarp1018		1,1,cmd_in01.gat,113,125
cmd_in01.gat,109,125,0		warp	comodowarp1019		1,1,comodo.gat,269,273
comodo.gat,145,328,0		warp	comodowarp1020		1,1,cmd_in01.gat,120,71
cmd_in01.gat,120,67,0		warp	comodowarp1021		1,1,comodo.gat,145,324
cmd_in02.gat,90,37,0		warp	comodowarp1022		1,1,cmd_in02.gat,191,77
cmd_in02.gat,187,78,0		warp	comodowarp1023		1,1,cmd_in02.gat,84,37
cmd_in02.gat,58,74,0		warp	comodowarp1024		1,1,cmd_in02.gat,166,116
cmd_in02.gat,168,113,0		warp	comodowarp1025		1,1,cmd_in02.gat,63,73
cmd_in02.gat,208,206,0		warp	comodowarp1026		1,1,cmd_in02.gat,97,211
cmd_in02.gat,98,216,0		warp	comodowarp1027		1,1,cmd_in02.gat,207,210
comodo.gat,192,294,0		warp	comodowarp1028		1,1,cmd_in01.gat,177,123
cmd_in01.gat,183,123,0		warp	comodowarp1029		1,1,comodo.gat,195,294

// duncer
job_duncer.gat,69,43,0		warp	comodowarp6001		1,1,comodo.gat,185,156



//---JP2.5 追加マップ---


//---JP3.0 追加マップ---


//==============================================================
// ----- Yuno ジュノー -----
// yuno.gat 		シュバルツバルド共和国の首都ジュノー
// yuno_in01.gat	ジュノー室内
// yuno_in02.gat	セージキャッスル室内
// yuno_in03.gat	ジュノー室内
// yuno_in04.gat	共和国図書館
// yuno_in05.gat	ユミルの心臓動力室
// job_sage.gat		セージ転職試験場
// -----
// yuno_fild04.gat	エルメスプレート
//==============================================================
yuno.gat,158,13,0		warp	yunowarp0501		1,1,yuno_fild04.gat,231,284

//武器防具屋(左下)
yuno.gat,117,135,0		warp	yunowarp1001		1,1,yuno_in01.gat,116,37
yuno_in01.gat,116,40,0		warp	yunowarp1002		1,1,yuno.gat,120,138
yuno_in01.gat,88,36,0		warp	yunowarp1003		1,1,yuno_in01.gat,173,34
yuno_in01.gat,176,34,0		warp	yunowarp1004		1,1,yuno_in01.gat,91,36
//カブトの家(左下)
yuno.gat,48,105,0		warp	yunowarp1005		1,1,yuno_in01.gat,37,176
yuno_in01.gat,40,176,0		warp	yunowarp1006		1,1,yuno.gat,51,105
yuno_in01.gat,32,182,0		warp	yunowarp1007		1,1,yuno_in01.gat,86,164
yuno_in01.gat,82,164,0		warp	yunowarp1008		1,1,yuno_in01.gat,28,182
//ステンクルの家(左)
yuno.gat,48,151,0		warp	yunowarp1009		1,1,yuno_in01.gat,30,100
yuno_in01.gat,34,100,0		warp	yunowarp1010		1,1,yuno.gat,51,151
//無人図書館(左)
yuno.gat,93,180,0		warp	yunowarp1011		1,1,yuno_in04.gat,33,127
yuno_in04.gat,33,130,0		warp	yunowarp1012		1,1,yuno.gat,95,184
//道具屋(右下)
yuno.gat,196,138,0		warp	yunowarp1013		1,1,yuno_in01.gat,32,33
yuno_in01.gat,32,36,0		warp	yunowarp1014		1,1,yuno.gat,193,142
//家(右下賢者前)
yuno.gat,264,87,0		warp	yunowarp1015		1,1,yuno_in01.gat,168,101
yuno_in01.gat,168,104,0		warp	yunowarp1016		1,1,yuno.gat,264,90
//女医の家(右下)
yuno.gat,245,147,0		warp	yunowarp1017		1,1,yuno_in01.gat,101,88
yuno_in01.gat,101,85,0		warp	yunowarp1018		1,1,yuno.gat,245,144
//共和国図書館
yuno.gat,342,203,0		warp	yunowarp1019		1,1,yuno_in04.gat,32,58
yuno_in04.gat,28,58,0		warp	yunowarp1020		1,1,yuno.gat,338,203
yuno_in04.gat,52,58,0		warp	yunowarp1021		1,1,yuno_in04.gat,97,58
yuno_in04.gat,95,58,0		warp	yunowarp1022		1,1,yuno_in04.gat,50,58
yuno_in04.gat,103,64,0		warp	yunowarp1023		1,1,yuno_in04.gat,103,95
yuno_in04.gat,103,93,0		warp	yunowarp1024		1,1,yuno_in04.gat,103,62
yuno_in04.gat,115,64,0		warp	yunowarp1025		1,1,yuno_in04.gat,115,95
yuno_in04.gat,115,93,0		warp	yunowarp1026		1,1,yuno_in04.gat,115,62
yuno_in04.gat,115,51,0		warp	yunowarp1027		1,1,yuno_in04.gat,115,20
yuno_in04.gat,115,22,0		warp	yunowarp1028		1,1,yuno_in04.gat,115,53
yuno_in04.gat,103,51,0		warp	yunowarp1029		1,1,yuno_in04.gat,103,20
yuno_in04.gat,103,22,0		warp	yunowarp1030		1,1,yuno_in04.gat,103,53
yuno_in04.gat,122,57,0		warp	yunowarp1031		1,1,yuno_in04.gat,164,110
yuno_in04.gat,161,110,0		warp	yunowarp1032		1,1,yuno_in04.gat,120,57
//魔法アカデミー
yuno.gat,323,284,0		warp	yunowarp1033		1,1,yuno_in03.gat,167,22
yuno_in03.gat,167,19,0		warp	yunowarp1034		1,1,yuno.gat,323,280
yuno_in03.gat,167,72,0		warp	yunowarp1035		1,1,yuno_in03.gat,179,113
yuno_in03.gat,179,109,0		warp	yunowarp1036		1,1,yuno_in03.gat,167,69
yuno_in03.gat,186,119,0		warp	yunowarp1037		1,1,yuno_in03.gat,163,174
yuno_in03.gat,161,174,0		warp	yunowarp1038		1,1,yuno_in03.gat,183,119
yuno_in03.gat,186,131,0		warp	yunowarp1039		1,1,yuno_in03.gat,163,187
yuno_in03.gat,161,187,0		warp	yunowarp1040		1,1,yuno_in03.gat,183,131
yuno_in03.gat,173,118,0		warp	yunowarp1041		1,1,yuno_in03.gat,120,178
yuno_in03.gat,124,178,0		warp	yunowarp1042		1,1,yuno_in03.gat,176,118
yuno_in03.gat,111,192,0		warp	yunowarp1043		1,1,yuno_in03.gat,162,132
yuno_in03.gat,162,129,0		warp	yunowarp1044		1,1,yuno_in03.gat,111,188
yuno_in03.gat,153,134,0		warp	yunowarp1045		1,1,yuno_in03.gat,62,186
yuno_in03.gat,66,186,0		warp	yunowarp1046		1,1,yuno_in03.gat,156,134
//モンスター研究所
yuno.gat,278,293,0		warp	yunowarp1047		1,1,yuno_in03.gat,25,15
yuno_in03.gat,25,11,0		warp	yunowarp1048		1,1,yuno.gat,278,290
yuno_in03.gat,25,56,0		warp	yunowarp1049		1,1,yuno_in03.gat,32,92
yuno_in03.gat,32,89,0		warp	yunowarp1050		1,1,yuno_in03.gat,25,53
//ユミルの心臓
yuno.gat,284,366,0		warp	yunowarp1051		1,1,yuno_in03.gat,224,23
yuno_in03.gat,224,19,0		warp	yunowarp1052		1,1,yuno.gat,282,363
yuno_in03.gat,219,50,0		warp	yunowarp1053		1,1,yuno_in03.gat,104,118
yuno_in03.gat,104,115,0		warp	yunowarp1054		1,1,yuno_in03.gat,219,47
yuno_in03.gat,244,52,0		warp	yunowarp1055		1,1,yuno_in03.gat,235,94
yuno_in03.gat,235,91,0		warp	yunowarp1056		1,1,yuno_in03.gat,244,49
yuno_in03.gat,231,56,0		warp	yunowarp1057		1,1,yuno_in03.gat,239,144
yuno_in03.gat,239,141,0		warp	yunowarp1058		1,1,yuno_in03.gat,231,59
yuno_in03.gat,223,167,0		warp	yunowarp1059		1,1,yuno_in03.gat,96,59
yuno_in03.gat,96,62,0		warp	yunowarp1060		1,1,yuno_in03.gat,223,170
//セージキャッスル
yuno.gat,87,321,0		warp	yunowarp1061		1,1,yuno_in02.gat,168,61
yuno_in02.gat,172,61,0		warp	yunowarp1062		1,1,yuno.gat,90,318
//セージキャッスル地下(Random)
yuno_in02.gat,82,14,0		warp	yunowarp1063		1,1,yuno_in05.gat,192,194
yuno_in05.gat,196,194,0		warp	yunowarp1064		1,1,yuno_in02.gat,85,14
// Yuno In05 (Entering Random Warps) -------------------------------------------
yuno_in05.gat,153,142,0		warp	yunowarp1065		1,1,yuno_in05.gat,192,103
yuno_in05.gat,196,103,0		warp	yunowarp1066		1,1,yuno_in05.gat,156,142
// Yuno In05 (Random Warps - Cross-Shaped) -------------------------------------------
yuno_in05.gat,181,116,0		warp	yunowarp1067		1,1,yuno_in05.gat,177,12
yuno_in05.gat,165,103,0		warp	yunowarp1068		1,1,yuno_in05.gat,145,83
yuno_in05.gat,181,91,0		warp	yunowarp1069		1,1,yuno_in05.gat,177,49
// Yuno In05 (Random Warps - T-Shaped) -----------------------------------------
yuno_in05.gat,148,83,0		warp	yunowarp1070		1,1,yuno_in05.gat,168,103
yuno_in05.gat,125,83,0		warp	yunowarp1071		1,1,yuno_in05.gat,192,103
yuno_in05.gat,137,71,0		warp	yunowarp1072		1,1,yuno_in05.gat,15,185
// Yuno In05 (Random Warps - Other) --------------------------------------------
yuno_in05.gat,16,188,0		warp	yunowarp1073		1,1,yuno_in05.gat,137,74
yuno_in05.gat,177,9,0		warp	yunowarp1074		1,1,yuno_in05.gat,181,113
yuno_in05.gat,177,52,0		warp	yunowarp1075		1,1,yuno_in05.gat,181,94
// Yuno In05 (Destination - Room) ----------------------------------------------
yuno_in05.gat,40,178,0		script	#yunowarp1076	45,1,1,{
	switch(rand(3)) {
		case 0:	warp "yuno_in05.gat",181,94; end;
		case 1:	warp "yuno_in05.gat",177,12; end;
		case 2:	warp "yuno_in05.gat",137,74; end;
	}
}
yuno_in05.gat,47,186,0		script	#yunowarp1077	45,1,1,{
	switch(rand(3)) {
		case 0:	warp "yuno_in05.gat",181,94; end;
		case 1:	warp "yuno_in05.gat",177,12; end;
		case 2:	warp "yuno_in05.gat",137,74; end;
	}
}
// Yuno In05 (Destination - Escaped Random Warps) ------------------------------
yuno_in05.gat,31,167,0		warp	yunowarp1078		1,1,yuno_in05.gat,50,85
yuno_in05.gat,50,88,0		warp	yunowarp1079		1,1,yuno_in02.gat,85,14


//ジュノー空港
yuno.gat,53,214,0		warp	yunowarp1080		1,1,y_airport.gat,143,23
y_airport.gat,143,16,0		warp	yunowarp1081		1,1,yuno.gat,53,207
yuno.gat,59,240,0		warp	yunowarp1082		1,1,y_airport.gat,143,54
yuno.gat,47,240,0		warp	yunowarp1083		1,1,y_airport.gat,143,54
//飛行船
yuno.gat,96,261,0		warp	yunowarp1084		1,1,airplane.gat,244,58
yuno.gat,6,261,0		warp	yunowarp1085		1,1,airplane_01.gat,244,58
//シュバルツバルド政府庁舎
yuno.gat,157,322,0		warp	yunowarp1086		1,1,yuno_pre.gat,69,13
yuno_pre.gat,69,10,0		warp	yunowarp1087		1,1,yuno.gat,157,317
yuno_pre.gat,113,48,0		warp	yunowarp1088		1,1,yuno_pre.gat,84,22
yuno_pre.gat,81,68,0		warp	yunowarp1089		1,1,yuno_pre.gat,95,68



//==============================================================
// ----- Rogue ローグ -----
// in_rogue.gat		ローグギルド
// -----
// cmd_fild07.gat	ファロス灯台島
//==============================================================
in_rogue.gat,375,46,0		warp	roguewarp0501		1,1,cmd_fild07.gat,196,117

in_rogue.gat,375,33,0		warp	roguewarp6001		1,1,in_rogue.gat,380,125
in_rogue.gat,375,125,0		warp	roguewarp6002		1,1,in_rogue.gat,379,33



//---アマツ追加マップ---


//==============================================================
// ----- Amatsu アマツ -----
// amatsu.gat		泉水の国アマツ
// ama_in01.gat		アマツ 室内
// ama_in02.gat		東湖城 泉水閣
// -----
// ama_fild01.gat	アマツフールド
//==============================================================
amatsu.gat,248,292,0		warp	amatsuwarp0501		1,1,ama_fild01.gat,75,33
ama_in01.gat,175,171,0		warp	amatsuwarp0502		1,1,ama_fild01.gat,174,328
ama_in01.gat,174,121,0		warp	amatsuwarp0503		1,1,ama_fild01.gat,330,139

//道具
amatsu.gat,94,117,0		warp	amatsuwarp1001		1,1,ama_in01.gat,30,24
ama_in01.gat,33,24,0		warp	amatsuwarp1002		1,1,amatsu.gat,97,117
//防具
amatsu.gat,132,117,0		warp	amatsuwarp1003		1,1,ama_in01.gat,89,23
ama_in01.gat,86,23,0		warp	amatsuwarp1004		1,1,amatsu.gat,129,117
//蔵左
amatsu.gat,52,148,0		warp	amatsuwarp1005		1,1,ama_in01.gat,88,97
ama_in01.gat,88,94,0		warp	amatsuwarp1006		1,1,amatsu.gat,52,145
//蔵右
amatsu.gat,168,182,0		warp	amatsuwarp1007		1,1,ama_in01.gat,34,99
ama_in01.gat,34,96,0		warp	amatsuwarp1008		1,1,amatsu.gat,168,179
//民家中央
amatsu.gat,177,138,0		warp	amatsuwarp1009		1,1,ama_in01.gat,28,176
ama_in01.gat,31,176,0		warp	amatsuwarp1010		1,1,amatsu.gat,180,138
//寿司
amatsu.gat,217,116,0		warp	amatsuwarp1011		1,1,ama_in01.gat,162,25
ama_in01.gat,157,25,0		warp	amatsuwarp1012		1,1,amatsu.gat,214,116
ama_in01.gat,162,34,0		warp	amatsuwarp1013		1,1,ama_in01.gat,166,77
ama_in01.gat,166,73,0		warp	amatsuwarp1014		1,1,ama_in01.gat,162,31
//民家東
amatsu.gat,248,160,0		warp	amatsuwarp1015		1,1,ama_in01.gat,79,178
ama_in01.gat,76,178,0		warp	amatsuwarp1016		1,1,amatsu.gat,245,160
//城
amatsu.gat,85,235,0		warp	amatsuwarp1017		1,1,ama_in02.gat,223,45
ama_in02.gat,226,45,0		warp	amatsuwarp1018		1,1,amatsu.gat,88,235
ama_in02.gat,195,44,0		warp	amatsuwarp1019		1,1,ama_in02.gat,65,40
ama_in02.gat,65,37,0		warp	amatsuwarp1020		1,1,ama_in02.gat,195,41
ama_in02.gat,56,44,0		warp	amatsuwarp1021		1,1,ama_in02.gat,59,144
ama_in02.gat,59,141,0		warp	amatsuwarp1022		1,1,ama_in02.gat,56,41
ama_in02.gat,222,161,0		warp	amatsuwarp1023		1,1,ama_in02.gat,130,163
ama_in02.gat,127,163,0		warp	amatsuwarp1024		1,1,ama_in02.gat,220,161
ama_in02.gat,59,160,0		warp	amatsuwarp1025		1,1,ama_in02.gat,215,152
ama_in02.gat,215,149,0		warp	amatsuwarp1026		1,1,ama_in02.gat,59,156



//---コンロン追加マップ---



//==============================================================
// ----- Gonryun コンロン -----
// gonryun.gat		神仙の島コンロン
// gon_in.gat		室内
// -----
// gon_dun01.gat	西王母神殿へ
// gon_fild01.gat	南フィールドへ
//==============================================================
gonryun.gat,159,201,0		warp	gonryunwarp0402		1,1,gon_dun01.gat,153,48
gonryun.gat,161,8,0		warp	gonryunwarp0501		1,1,gon_fild01.gat,191,261

//民家
gonryun.gat,195,93,0		warp	gonryunwarp1001		1,1,gon_in.gat,95,23
gon_in.gat,95,26,0		warp	gonryunwarp1002		1,1,gonryun.gat,195,96
//宿
gonryun.gat,215,114,0		warp	gonryunwarp1003		1,1,gon_in.gat,152,24
gon_in.gat,149,24,0		warp	gonryunwarp1004		1,1,gonryun.gat,212,114
//宿2F↓
gon_in.gat,184,11,0		warp	gonryunwarp1005		1,1,gon_in.gat,189,85
gon_in.gat,186,85,0		warp	gonryunwarp1006		1,1,gon_in.gat,181,11
//宿2F↑
gon_in.gat,186,107,0		warp	gonryunwarp1007		1,1,gon_in.gat,181,36
gon_in.gat,184,36,0		warp	gonryunwarp1008		1,1,gon_in.gat,189,107
//民家
gonryun.gat,221,162,0		warp	gonryunwarp1009		1,1,gon_in.gat,112,98
gon_in.gat,109,98,0		warp	gonryunwarp1010		1,1,gonryun.gat,218,162
//民家北西
gonryun.gat,107,184,0		warp	gonryunwarp1011		1,1,gon_in.gat,72,70
gon_in.gat,72,67,0		warp	gonryunwarp1012		1,1,gonryun.gat,107,181
//村長宅
gonryun.gat,109,131,0		warp	gonryunwarp1013		1,1,gon_in.gat,44,24
gon_in.gat,47,24,0		warp	gonryunwarp1014		1,1,gonryun.gat,112,131
//村長宅2F
gon_in.gat,42,35,0		warp	gonryunwarp1015		1,1,gon_in.gat,34,97
gon_in.gat,31,97,0		warp	gonryunwarp1016		1,1,gon_in.gat,39,35



//---ウンバラ追加マップ


//==============================================================
// ----- Umbala ウンバラ -----
// umbala.gat		ウータン族の村ウンバラ
// um_in.gat		ウータン族の村ウンバラ 室内
// -----
// um_dun01.gat		大樹の道
// um_fild04.gat	フムガジャング
//==============================================================
//umbala.gat,106,285,0		warp	umbalawarp0401		1,1,um_dun01.gat,42,30
umbala.gat,106,285,0		warp	umbalawarp0401		1,1,yggdrasil01.gat,39,63
umbala.gat,130,79,0		warp	umbalawarp0501		1,1,um_fild04.gat,215,336

//チャビバタンの家北
umbala.gat,100,203,0		warp	umbalawarp1001		1,1,um_in.gat,163,69
um_in.gat,166,69,0		warp	umbalawarp1002		1,1,umbala.gat,102,205
//チャビバタンの家南
umbala.gat,94,186,0		warp	umbalawarp1003		1,1,um_in.gat,141,42
um_in.gat,141,39,0		warp	umbalawarp1004		1,1,umbala.gat,94,183
//酋長の家
umbala.gat,68,253,0		warp	umbalawarp1005		1,1,um_in.gat,38,113
um_in.gat,38,110,0		warp	umbalawarp1006		1,1,umbala.gat,66,250
//ウェナタンの家
umbala.gat,107,130,0		warp	umbalawarp1007		1,1,um_in.gat,99,66
um_in.gat,99,63,0		warp	umbalawarp1008		1,1,umbala.gat,108,127
//武器屋
umbala.gat,125,157,0		warp	umbalawarp1009		1,1,um_in.gat,155,114
um_in.gat,155,111,0		warp	umbalawarp1010		1,1,umbala.gat,126,154
//道具屋
umbala.gat,138,129,0		warp	umbalawarp1011		1,1,um_in.gat,99,114
um_in.gat,99,111,0		warp	umbalawarp1012		1,1,umbala.gat,136,127
//シャーマンの家
//npc_town_umbala.txtに記述



//---ニブルヘイム追加マップ


//==============================================================
// ----- Niflheimg ニブルヘイム -----
// niflheim.gat		死者の街ニブルヘイム
// nif_in.gat		ニブルヘイム 室内
// -----
// nif_fild02.gat	ギョル渓谷
//==============================================================
niflheim.gat,19,154,0		warp	niflheimwarp0501	1,1,nif_fild02.gat,375,235

//House1(Girl)
niflheim.gat,166,162,0		warp	niflheimwarp1001	1,1,nif_in.gat,157,81
nif_in.gat,154,78,0		warp	niflheimwarp1002	1,1,niflheim.gat,169,162
nif_in.gat,169,82,0		warp	niflheimwarp1003	1,1,nif_in.gat,189,106
nif_in.gat,186,106,0		warp	niflheimwarp1004	1,1,nif_in.gat,166,82
//House2(Waste Shop)
niflheim.gat,189,210,0		warp	niflheimwarp1005	1,1,nif_in.gat,23,14
nif_in.gat,23,11,0		warp	niflheimwarp1006	1,1,niflheim.gat,189,207
nif_in.gat,34,34,0		warp	niflheimwarp1007	1,1,nif_in.gat,88,32
nif_in.gat,88,29,0		warp	niflheimwarp1008	1,1,nif_in.gat,34,30
//House3(Item Shop)
niflheim.gat,219,198,0		warp	niflheimwarp1009	1,1,nif_in.gat,137,15
nif_in.gat,135,13,0		warp	niflheimwarp1010	1,1,niflheim.gat,217,196
//House4(Equip Shop)
niflheim.gat,219,169,0		warp	niflheimwarp1011	1,1,nif_in.gat,14,88
nif_in.gat,11,88,0		warp	niflheimwarp1012	1,1,niflheim.gat,216,171
//House5(Minstrel's house)
niflheim.gat,189,241,0		warp	niflheimwarp1013	1,1,nif_in.gat,81,77
nif_in.gat,78,74,0		warp	niflheimwarp1014	1,1,niflheim.gat,186,241
niflheim.gat,202,248,0		warp	niflheimwarp1015	1,1,nif_in.gat,95,102
nif_in.gat,95,106,0		warp	niflheimwarp1016	1,1,niflheim.gat,202,254
//House6(Witch's house)
niflheim.gat,255,194,0		warp	niflheimwarp1017	1,1,nif_in.gat,21,157
nif_in.gat,18,154,0		warp	niflheimwarp1018	1,1,niflheim.gat,253,191
nif_in.gat,65,174,0		warp	niflheimwarp1019	1,1,nif_in.gat,140,174
nif_in.gat,140,171,0		warp	niflheimwarp1020	1,1,nif_in.gat,65,170



//---転生システム追加マップ


//==============================================================
// ----- Valkyrie ヴァルキリー神殿 -----
// valkyrie.gat		ヴァルキリー神殿
//==============================================================
valkyrie.gat,49,67,0	warp	valkyriewarp6001	1,1,valkyrie.gat,49,75
valkyrie.gat,49,72,0	warp	valkyriewarp6002	1,1,valkyrie.gat,49,63



//---龍之城追加マップ


//==============================================================
// ----- Louyang 龍之城 -----
// louyang.gat		古都 龍之城
// lou_in01.gat		龍之城 室内
// lou_in02.gat		龍之城 室内
// -----
// lou_dun01.gat	王陵
// lou_fild01.gat	龍之城フィールド
//==============================================================
louyang.gat,37,271,0		warp	louyangwarp0401		1,1,lou_dun01.gat,218,195
louyang.gat,218,19,0		warp	louyangwarp0501		3,1,lou_fild01.gat,233,353

// 城
louyang.gat,218,255,0		warp	louyangwarp1001		2,1,lou_in01.gat,101,122
lou_in01.gat,101,119,0		warp	louyangwarp1002		1,1,louyang.gat,218,252
// 城 -> 右の部屋
lou_in01.gat,125,140,0		warp	louyangwarp1003		2,1,lou_in01.gat,156,141
lou_in01.gat,153,141,0		warp	louyangwarp1004		1,1,lou_in01.gat,122,141
// 城 -> 左の部屋
lou_in01.gat,79,141,0		warp	louyangwarp1005		2,1,lou_in01.gat,47,141
lou_in01.gat,50,141,0		warp	louyangwarp1006		1,1,lou_in01.gat,82,141
// 病院
louyang.gat,263,93,0		warp	louyangwarp1007		1,1,lou_in02.gat,245,59
lou_in02.gat,242,59,0		warp	louyangwarp1008		1,1,louyang.gat,260,93
// 道具屋
louyang.gat,136,97,0		warp	louyangwarp1009		1,1,lou_in02.gat,250,174
lou_in02.gat,253,177,0		warp	louyangwarp1010		1,1,louyang.gat,139,100
// 倉庫
louyang.gat,125,121,0		warp	louyangwarp1011		1,1,lou_in02.gat,198,161
lou_in02.gat,198,159,0		warp	louyangwarp1012		1,1,louyang.gat,125,118
louyang.gat,129,121,0		warp	louyangwarp1013		1,1,lou_in02.gat,203,161
lou_in02.gat,203,159,0		warp	louyangwarp1014		1,1,louyang.gat,129,118
// 武器屋
louyang.gat,145,174,0		warp	louyangwarp1015		1,1,lou_in02.gat,126,168
lou_in02.gat,126,165,0		warp	louyangwarp1016		1,1,louyang.gat,145,171
// 酒屋
louyang.gat,280,167,0		warp	louyangwarp1017		1,1,lou_in02.gat,58,173
lou_in02.gat,58,170,0		warp	louyangwarp1018		1,1,louyang.gat,280,164
// 酒屋 -> 2F左
lou_in02.gat,35,190,0		warp	louyangwarp1019		1,1,lou_in02.gat,41,138
lou_in02.gat,44,138,0		warp	louyangwarp1020		1,1,lou_in02.gat,38,190
// 酒屋 -> 2F右
lou_in02.gat,80,190,0		warp	louyangwarp1021		1,1,lou_in02.gat,74,140
lou_in02.gat,71,140,0		warp	louyangwarp1022		1,1,lou_in02.gat,77,190
// 官庁
louyang.gat,309,80,0		warp	louyangwarp1023		1,1,lou_in02.gat,189,77
lou_in02.gat,189,74,0		warp	louyangwarp1024		1,1,louyang.gat,309,77
// 官庁2F
lou_in02.gat,201,94,0		warp	louyangwarp1025		1,1,lou_in02.gat,173,46
lou_in02.gat,176,46,0		warp	louyangwarp1026		1,1,lou_in02.gat,204,94
// 世捨て人の家
louyang.gat,130,63,0		warp	louyangwarp1027		1,1,lou_in02.gat,72,31
lou_in02.gat,72,28,0		warp	louyangwarp1028		1,1,louyang.gat,130,60
// 毒薬王の家
louyang.gat,317,176,0		warp	louyangwarp1029		1,1,lou_in02.gat,121,31
lou_in02.gat,121,28,0		warp	louyangwarp1030		1,1,louyang.gat,317,173
// 展望台
louyang.gat,133,245,0		warp	louyangwarp1031		1,1,lou_in01.gat,25,19
lou_in01.gat,28,19,0		warp	louyangwarp1032		1,1,louyang.gat,136,245
lou_in01.gat,14,18,0		warp	louyangwarp1033		0,0,louyang.gat,90,254



//==============================================================
// ----- Jawaii ジャワイ -----
// jawaii.gat		常夏の島 ジャワイ
// jawaii_in.gat	ジャワイ 室内
// -----
//==============================================================
//秘密酒場
jawaii.gat,192,215	warp	jaw001	1,1,jawaii_in.gat,27,94

jawaii_in.gat,27,91,0	script	jaw001-1	45,1,1,{
	if(PartnerId)
		warp "jawaii.gat",192,218;
	else
		warp "jawaii_in.gat",27,94;
	end;
}
//スイートルーム
jawaii_in.gat,113,61	warp	jaw01	1,1,jawaii.gat,136,203
//アンティークルーム
jawaii_in.gat,132,107	warp	jaw02	1,1,jawaii.gat,114,196
//ハニールーム
jawaii_in.gat,89,117	warp	jaw03	1,1,jawaii.gat,111,186
//ビラルーム
jawaii_in.gat,90,78	warp	jaw04	1,1,jawaii.gat,117,175



//---神器クエスト追加マップ


//---アユタヤ追加マップ


//==============================================================
// ----- Ayothaya アユタヤ -----
// ayothaya.gat		アユタヤ
// ayo_in01.gat		アユタヤ 室内
// ayo_in02.gat		アユタヤ 室内
// -----
//==============================================================
ayothaya.gat,276,176,0	warp	ayothayawarp0501	1,1,ayo_fild01.gat,37,241

//船降りて桟橋左の建物
ayothaya.gat,130,75,0	warp	ayothayawarp1001	1,1,ayo_in01.gat,17,156
ayo_in01.gat,17,153,0	warp	ayothayawarp1002	1,1,ayothaya.gat,132,73
ayothaya.gat,130,97,0	warp	ayothayawarp1003	1,1,ayo_in01.gat,43,183
ayo_in01.gat,46,183,0	warp	ayothayawarp1004	1,1,ayothaya.gat,132,99
ayothaya.gat,129,86,0	warp	ayothayawarp1005	1,1,ayo_in01.gat,21,178
ayo_in01.gat,23,175,0	warp	ayothayawarp1006	1,1,ayothaya.gat,132,86
//船降りて桟橋右の建物
ayothaya.gat,165,90,0	warp	ayothayawarp1007	1,1,ayo_in01.gat,77,174
ayo_in01.gat,73,174,0	warp	ayothayawarp1008	1,1,ayothaya.gat,162,90
ayothaya.gat,177,90,0	warp	ayothayawarp1009	1,1,ayo_in01.gat,95,175
ayo_in01.gat,98,175,0	warp	ayothayawarp1010	1,1,ayothaya.gat,180,90
ayothaya.gat,173,77,0	warp	ayothayawarp1011	1,1,ayo_in01.gat,85,152
ayo_in01.gat,85,149,0	warp	ayothayawarp1012	1,1,ayothaya.gat,173,74
//旅館
ayothaya.gat,202,161,0	warp	ayothayawarp1015	1,1,ayo_in01.gat,31,108
ayo_in01.gat,31,111,0	warp	ayothayawarp1016	1,1,ayothaya.gat,202,164
ayothaya.gat,191,150,0	warp	ayothayawarp1013	1,1,ayo_in01.gat,13,94
ayo_in01.gat,10,94,0	warp	ayothayawarp1014	1,1,ayothaya.gat,189,150
ayothaya.gat,211,150,0	warp	ayothayawarp1017	1,1,ayo_in01.gat,47,94
ayo_in01.gat,50,94,0	warp	ayothayawarp1018	1,1,ayothaya.gat,214,150
ayothaya.gat,202,140,0	warp	ayothayawarp1019	1,1,ayo_in01.gat,31,81
ayo_in01.gat,31,78,0	warp	ayothayawarp1020	1,1,ayothaya.gat,202,137
//旅館部屋
ayo_in01.gat,13,107,0	warp	ayothayawarp1021	1,1,ayo_in01.gat,132,27
ayo_in01.gat,135,27,0	warp	ayothayawarp1022	1,1,ayo_in01.gat,17,107
ayo_in01.gat,48,107,0	warp	ayothayawarp1023	1,1,ayo_in01.gat,179,27
ayo_in01.gat,176,27,0	warp	ayothayawarp1024	1,1,ayo_in01.gat,45,107
ayo_in01.gat,13,82,0	warp	ayothayawarp1025	1,1,ayo_in01.gat,18,14
ayo_in01.gat,21,14,0	warp	ayothayawarp1026	1,1,ayo_in01.gat,17,82
ayo_in01.gat,48,82,0	warp	ayothayawarp1027	1,1,ayo_in01.gat,63,14
ayo_in01.gat,60,14,0	warp	ayothayawarp1028	1,1,ayo_in01.gat,45,82
//マーリーパイ食堂
ayothaya.gat,229,69,0	warp	ayothayawarp1029	1,1,ayo_in01.gat,137,192
ayo_in01.gat,137,195,0	warp	ayothayawarp1030	1,1,ayothaya.gat,229,72
//シャーマン民家
ayothaya.gat,62,104,0	warp	ayothayawarp1031	1,1,ayo_in01.gat,191,183
ayo_in01.gat,194,183,0	warp	ayothayawarp1032	1,1,ayothaya.gat,65,104
//民家
ayothaya.gat,111,109,0	warp	ayothayawarp1033	1,1,ayo_in01.gat,180,129
ayo_in01.gat,177,129,0	warp	ayothayawarp1034	1,1,ayothaya.gat,111,106
//神殿
ayothaya.gat,208,283,0	warp	ayothayawarp1035	1,1,ayo_in02.gat,100,152
ayo_in02.gat,100,148,0	warp	ayothayawarp1036	1,1,ayothaya.gat,208,280




//---アルデバランターボトラック追加マップ


//---鋼鉄の都市アインブロック追加マップ


//==============================================================
// ----- Einbroch アインブロック -----
// einbroch.gat		鋼鉄の都市アインブロック
// einbech.gat		採鉱の村アインベフ
// ein_in01.gat		アインブロック室内
// airport.gat		空港
// airplane.gat		飛行船
// -----
// ein_dun01.gat	鉱山ダンジョン
// ein_fild08.gat	アインブロックフィールド
// ein_fild09.gat	アインブロックフィールド
//==============================================================
//採鉱の村アインベフ⇒鉱山ダンジョン
einbech.gat,138,252,0		warp	einbrochwarp0401	1,1,ein_dun01.gat,22,14
//鋼鉄の都市アインブロック⇒アインブロックフィールド
einbroch.gat,150,25,0		warp	einbrochwarp0501	1,1,ein_fild08.gat,164,377
//採鉱の村アインベフ⇒アインブロックフィールド
einbech.gat,62,29,0		warp	einbrochwarp0502	1,1,ein_fild09.gat,74,350

//工場
einbroch.gat,179,73,0	warp	einbrochwarp1001	1,1,ein_in01.gat,81,203
ein_in01.gat,81,198,0	warp	einbrochwarp1002	1,1,einbroch.gat,179,70
einbroch.gat,132,79,0	warp	einbrochwarp1003	1,1,ein_in01.gat,17,213
ein_in01.gat,13,213,0	warp	einbrochwarp1004	1,1,einbroch.gat,129,79
//駅
einbroch.gat,214,263,0	warp	einbrochwarp1005	1,1,einbroch.gat,233,315
einbroch.gat,233,312,0	warp	einbrochwarp1006	1,1,einbroch.gat,214,260
einbroch.gat,250,263,0	warp	einbrochwarp1007	1,1,einbroch.gat,269,315
einbroch.gat,269,312,0	warp	einbrochwarp1008	1,1,einbroch.gat,250,260
//武器屋
einbroch.gat,216,214,0	warp	einbrochwarp1009	1,1,ein_in01.gat,108,17
ein_in01.gat,108,13,0	warp	einbrochwarp1010	1,1,einbroch.gat,216,211
//ホテル
einbroch.gat,257,199,0	warp	einbrochwarp1011	1,1,ein_in01.gat,198,224
ein_in01.gat,195,224,0	warp	einbrochwarp1012	1,1,einbroch.gat,254,199
//ホテル1F⇔2F
ein_in01.gat,211,216,0	warp	einbrochwarp1013	1,1,ein_in01.gat,274,218
ein_in01.gat,271,218,0	warp	einbrochwarp1014	1,1,ein_in01.gat,208,216
ein_in01.gat,211,232,0	warp	einbrochwarp1015	1,1,ein_in01.gat,274,232
ein_in01.gat,271,232,0	warp	einbrochwarp1016	1,1,ein_in01.gat,208,232
//ホテル左下の部屋
ein_in01.gat,264,203,0	warp	einbrochwarp1017	1,1,ein_in01.gat,232,173
ein_in01.gat,232,176,0	warp	einbrochwarp1018	1,1,ein_in01.gat,264,206
//ホテル左上の部屋
ein_in01.gat,264,246,0	warp	einbrochwarp1019	1,1,ein_in01.gat,231,276
ein_in01.gat,231,273,0	warp	einbrochwarp1020	1,1,ein_in01.gat,264,243
//ホテル右下の部屋
ein_in01.gat,274,203,0	warp	einbrochwarp1021	1,1,ein_in01.gat,274,173
ein_in01.gat,274,176,0	warp	einbrochwarp1022	1,1,ein_in01.gat,274,206
//ホテル右上の部屋
ein_in01.gat,274,246,0	warp	einbrochwarp1023	1,1,ein_in01.gat,273,276
ein_in01.gat,273,273,0	warp	einbrochwarp1024	1,1,ein_in01.gat,274,243
//ホテル中央の部屋
ein_in01.gat,284,224,0	warp	einbrochwarp1025	1,1,ein_in01.gat,177,277
ein_in01.gat,180,277,0	warp	einbrochwarp1026	1,1,ein_in01.gat,280,224
//ブラックスミスギルド
einbroch.gat,255,107,0	warp	einbrochwarp1027	1,1,ein_in01.gat,14,17
ein_in01.gat,14,14,0	warp	einbrochwarp1028	1,1,einbroch.gat,255,110
ein_in01.gat,39,36,0	warp	einbrochwarp1029	1,1,ein_in01.gat,35,83
ein_in01.gat,39,85,0	warp	einbrochwarp1030	1,1,ein_in01.gat,36,36
//研究所
//einbroch.gat,51,52,0	warp	einbrochwarp1031	1,1,ein_in01.gat,285,25
ein_in01.gat,288,25,0	warp	einbrochwarp1032	1,1,einbroch.gat,54,52
//カーラの家
einbroch.gat,129,229,0	warp	einbrochwarp1033	1,1,ein_in01.gat,14,147
ein_in01.gat,11,147,0	warp	einbrochwarp1034	1,1,einbroch.gat,126,229
//ギルナーの家
einbroch.gat,290,222,0	warp	einbrochwarp1035	1,1,ein_in01.gat,121,80
ein_in01.gat,121,77,0	warp	einbrochwarp1036	1,1,einbroch.gat,290,219
einbroch.gat,278,233,0	warp	einbrochwarp1037	1,1,ein_in01.gat,107,95
ein_in01.gat,103,95,0	warp	einbrochwarp1038	1,1,einbroch.gat,275,233
ein_in01.gat,126,88,0	warp	einbrochwarp1039	1,1,ein_in01.gat,100,139
ein_in01.gat,100,142,0	warp	einbrochwarp1040	1,1,ein_in01.gat,123,85
//空港
einbroch.gat,64,207,0	warp	einbrochwarp1041	1,1,airport.gat,143,17
airport.gat,143,14,0	warp	einbrochwarp1042	1,1,einbroch.gat,64,204
airport.gat,142,61,0	warp	einbrochwarp1043	1,1,einbroch.gat,62,246
einbroch.gat,64,234,0	warp	einbrochwarp1044	1,1,airport.gat,138,51
//空港1F⇔2F
airport.gat,124,13,0	warp	einbrochwarp1045	1,1,airport.gat,19,21
airport.gat,19,18,0	warp	einbrochwarp1046	1,1,airport.gat,122,16
airport.gat,161,13,0	warp	einbrochwarp1047	1,1,airport.gat,47,21
airport.gat,47,18,0	warp	einbrochwarp1048	1,1,airport.gat,163,16
//飛行船
einbroch.gat,92,281,0	warp	einbrochwarp1049	1,1,airplane.gat,224,64
airplane.gat,254,54,0	warp	einbrochwarp1050	1,1,airplane.gat,91,67
airplane.gat,87,67,0	warp	einbrochwarp1051	1,1,airplane.gat,250,54
//酒場
einbech.gat,145,112,0	warp	einbrochwarp1052	1,1,ein_in01.gat,268,104
ein_in01.gat,265,104,0	warp	einbrochwarp1053	1,1,einbech.gat,141,112
einbech.gat,154,106,0	warp	einbrochwarp1054	1,1,ein_in01.gat,285,89
ein_in01.gat,288,89,0	warp	einbrochwarp1055	1,1,einbech.gat,157,106
//道具屋
einbech.gat,177,136,0	warp	einbrochwarp1056	1,1,ein_in01.gat,190,35
ein_in01.gat,190,38,0	warp	einbrochwarp1057	1,1,einbech.gat,177,133
//共同住宅
einbech.gat,214,121,0	warp	einbrochwarp1058	1,1,ein_in01.gat,205,84
ein_in01.gat,205,81,0	warp	einbrochwarp1059	1,1,einbech.gat,214,118
einbech.gat,207,135,0	warp	einbrochwarp1060	1,1,ein_in01.gat,190,99
ein_in01.gat,187,99,0	warp	einbrochwarp1061	1,1,einbech.gat,204,135
//剣士ギルド
einbech.gat,257,109,0	warp	einbrochwarp1062	1,1,ein_in01.gat,148,153
ein_in01.gat,145,153,0	warp	einbrochwarp1063	1,1,einbech.gat,253,109



//---企業都市リヒタルゼン追加マップ


//==============================================================
// -----  リヒタルゼン -----
// lighthalzen.gat	企業都市リヒタルゼン
// -----
// lhz_dun01.gat	生体実験研究所地下１階
// lhz_fild01.gat	リヒタルゼンフィールド
//==============================================================
einbroch.gat,157,331,0	warp	lighthalzenwarp0501	1,1,ein_fild04.gat,184,31
lighthalzen.gat,214,329,0	warp	lighthalzenwarp0502	1,1,lhz_fild01.gat,209,23

//レッケンベル本社
lighthalzen.gat,101,248,0	warp	lighthalzenwarp1001	1,1,lhz_in01.gat,111,126
lhz_in01.gat,111,121,0	warp	lighthalzenwarp1002	1,1,lighthalzen.gat,101,243
lighthalzen.gat,106,248,0	warp	lighthalzenwarp1003	1,1,lhz_in01.gat,116,126
lhz_in01.gat,116,121,0	warp	lighthalzenwarp1004	1,1,lighthalzen.gat,106,243
//レッケンベル本社-パーティー会場
lhz_in01.gat,149,179,0	warp	lighthalzenwarp1005	1,1,lhz_in01.gat,15,24
lhz_in01.gat,11,24,0	warp	lighthalzenwarp1006	1,1,lhz_in01.gat,145,178
//レッケンベル本社-1F奥
lhz_in01.gat,88,215,0	warp	lighthalzenwarp1007	1,1,lhz_in01.gat,106,18
lhz_in01.gat,106,15,0	warp	lighthalzenwarp1008	1,1,lhz_in01.gat,88,211
lhz_in01.gat,140,215,0	warp	lighthalzenwarp1009	1,1,lhz_in01.gat,158,18
lhz_in01.gat,158,15,0	warp	lighthalzenwarp1010	1,1,lhz_in01.gat,140,211
//レッケンベル本社-1F⇔2F
lhz_in01.gat,76,254,0	warp	lighthalzenwarp1011	1,1,lhz_in01.gat,100,52
lhz_in01.gat,98,55,0	warp	lighthalzenwarp1012	1,1,lhz_in01.gat,76,250
lhz_in01.gat,188,254,0	warp	lighthalzenwarp1013	1,1,lhz_in01.gat,191,52
lhz_in01.gat,194,55,0	warp	lighthalzenwarp1014	1,1,lhz_in01.gat,188,250
//レッケンベル本社-秘書室
lhz_in01.gat,231,226,0	warp	lighthalzenwarp1015	1,1,lhz_in01.gat,257,226
lhz_in01.gat,251,226,0	warp	lighthalzenwarp1016	1,1,lhz_in01.gat,225,226
//レッケンベル本社-レケンジュルム研究所
lhz_in01.gat,40,224,0	warp	lighthalzenwarp1017	1,1,lhz_in01.gat,19,129
lhz_in01.gat,15,129,0	warp	lighthalzenwarp1018	1,1,lhz_in01.gat,34,224
//レッケンベル本社-レケンジュルム北研究室
lhz_in01.gat,43,144,0	warp	lighthalzenwarp1019	1,1,lhz_in01.gat,278,161
lhz_in01.gat,278,157,0	warp	lighthalzenwarp1020	1,1,lhz_in01.gat,43,139
//レッケンベル本社-レケンジュルム南研究室
//lhz_in01.gat,43,114,0	warp	lighthalzenwarp1021	1,1,lhz_in01.gat,277,130
lhz_in01.gat,278,132,0	warp	lighthalzenwarp1022	1,1,lhz_in01.gat,43,120
//レッケンベル本社-レケンジュルム東研究室
lhz_in01.gat,58,129,0	warp	lighthalzenwarp1021	1,1,lhz_in01.gat,196,127
lhz_in01.gat,191,127,0	warp	lighthalzenwarp1022	1,1,lhz_in01.gat,53,129

//警察署
lighthalzen.gat,236,276,0	warp	lighthalzenwarp1023	1,1,lhz_in02.gat,133,199
lhz_in02.gat,129,199,0	warp	lighthalzenwarp1024	1,1,lighthalzen.gat,232,275
//銀行
lighthalzen.gat,198,257,0	warp	lighthalzenwarp1025	1,1,lhz_in02.gat,39,28
lhz_in02.gat,44,28,0	warp	lighthalzenwarp1026	1,1,lighthalzen.gat,203,257
//ホテル
lighthalzen.gat,159,133,0	warp	lighthalzenwarp1027	1,1,lhz_in02.gat,232,265
lhz_in02.gat,232,261,0	warp	lighthalzenwarp1028	1,1,lighthalzen.gat,158,129
//ホテル-バー
lhz_in02.gat,250,278,0	warp	lighthalzenwarp1029	1,1,lhz_in02.gat,265,278
lhz_in02.gat,261,278,0	warp	lighthalzenwarp1030	1,1,lhz_in02.gat,246,278
//ホテル-1F⇔2F
lhz_in02.gat,210,284,0	warp	lighthalzenwarp1031	1,1,lhz_in02.gat,241,219
lhz_in02.gat,236,219,0	warp	lighthalzenwarp1032	1,1,lhz_in02.gat,206,284
//ホテル-客室
lhz_in02.gat,254,212,0	warp	lighthalzenwarp1033	1,1,lhz_in02.gat,273,212
lhz_in02.gat,269,212,0	warp	lighthalzenwarp1034	1,1,lhz_in02.gat,250,212
lhz_in02.gat,231,200,0	warp	lighthalzenwarp1035	1,1,lhz_in02.gat,212,200
lhz_in02.gat,216,200,0	warp	lighthalzenwarp1036	1,1,lhz_in02.gat,235,200
lhz_in02.gat,231,182,0	warp	lighthalzenwarp1037	1,1,lhz_in02.gat,212,182
lhz_in02.gat,216,182,0	warp	lighthalzenwarp1038	1,1,lhz_in02.gat,235,182
lhz_in02.gat,238,169,0	warp	lighthalzenwarp1039	1,1,lhz_in02.gat,238,150
lhz_in02.gat,238,154,0	warp	lighthalzenwarp1040	1,1,lhz_in02.gat,238,173
//宝石店
lighthalzen.gat,93,110,0	warp	lighthalzenwarp1041	1,1,lhz_in02.gat,104,26
lhz_in02.gat,108,26,0	warp	lighthalzenwarp1042	1,1,lighthalzen.gat,96,110
//武器屋
lighthalzen.gat,196,46,0	warp	lighthalzenwarp1043	1,1,lhz_in02.gat,282,83
lhz_in02.gat,282,79,0	warp	lighthalzenwarp1044	1,1,lighthalzen.gat,194,48
lighthalzen.gat,197,36,0	warp	lighthalzenwarp1045	1,1,lhz_in02.gat,284,30
lhz_in02.gat,288,30,0	warp	lighthalzenwarp1046	1,1,lighthalzen.gat,194,35
//武器屋-1F⇔2F
lhz_in02.gat,274,82,0	warp	lighthalzenwarp1047	1,1,lhz_in02.gat,270,14
lhz_in02.gat,265,14,0	warp	lighthalzenwarp1048	1,1,lhz_in02.gat,269,82
//デパート
lighthalzen.gat,198,163,0	warp	lighthalzenwarp1049	1,1,lhz_in02.gat,21,195
lhz_in02.gat,21,191,0	warp	lighthalzenwarp1050	1,1,lighthalzen.gat,202,160
//デパート-1F⇔2F
lhz_in02.gat,39,204,0	warp	lighthalzenwarp1051	1,1,lhz_in02.gat,41,136
lhz_in02.gat,36,136,0	warp	lighthalzenwarp1052	1,1,lhz_in02.gat,34,204
//デパート-2F⇔3F
lhz_in02.gat,13,155,0	warp	lighthalzenwarp1053	1,1,lhz_in02.gat,84,223
lhz_in02.gat,79,223,0	warp	lighthalzenwarp1054	1,1,lhz_in02.gat,17,155
lhz_in02.gat,49,154,0	warp	lighthalzenwarp1055	1,1,lhz_in02.gat,98,155
lhz_in02.gat,103,155,0	warp	lighthalzenwarp1056	1,1,lhz_in02.gat,44,154
//デパート-3F
lhz_in02.gat,94,212,0	warp	lighthalzenwarp1057	1,1,lhz_in02.gat,94,144
lhz_in02.gat,89,144,0	warp	lighthalzenwarp1058	1,1,lhz_in02.gat,89,212
//ジョンダイベント臨時本部
lighthalzen.gat,238,220,0	warp	lighthalzenwarp1059	1,1,lhz_in02.gat,28,270
lhz_in02.gat,27,265,0	warp	lighthalzenwarp1060	1,1,lighthalzen.gat,238,217
//ジョンダイベント臨時本部-1F⇔2F
lhz_in02.gat,13,284,0	warp	lighthalzenwarp1061	1,1,lhz_in02.gat,89,285
lhz_in02.gat,95,285,0	warp	lighthalzenwarp1062	1,1,lhz_in02.gat,18,284
//ジョンダイベント臨時本部-2F奥
lhz_in02.gat,114,272,0	warp	lighthalzenwarp1063	1,1,lhz_in02.gat,153,282
lhz_in02.gat,149,282,0	warp	lighthalzenwarp1064	1,1,lhz_in02.gat,109,272
//ケルラソス家
lighthalzen.gat,251,299,0	warp	lighthalzenwarp1065	1,1,lhz_in03.gat,97,21
lhz_in03.gat,93,21,0	warp	lighthalzenwarp1066	1,1,lighthalzen.gat,247,299
//ケルラソス家-1F⇔2F
lhz_in03.gat,134,14,0	warp	lighthalzenwarp1067	1,1,lhz_in03.gat,125,90
lhz_in03.gat,120,90,0	warp	lighthalzenwarp1068	1,1,lhz_in03.gat,130,14
//民家
lighthalzen.gat,50,86,0	warp	lighthalzenwarp1069	1,1,lhz_in03.gat,45,31
lhz_in03.gat,50,31,0	warp	lighthalzenwarp1070	1,1,lighthalzen.gat,55,86
//民家-1F⇔2F
lhz_in03.gat,13,31,0	warp	lighthalzenwarp1071	1,1,lhz_in03.gat,15,99
lhz_in03.gat,20,99,0	warp	lighthalzenwarp1072	1,1,lhz_in03.gat,17,31

//貧民街-道具屋
lighthalzen.gat,324,301,0	warp	lighthalzenwarp1073	1,1,lhz_in03.gat,241,100
lhz_in03.gat,237,100,0	warp	lighthalzenwarp1074	1,1,lighthalzen.gat,322,296
//貧民街-道具屋1F⇔2F
lhz_in03.gat,257,83,0	warp	lighthalzenwarp1075	1,1,lhz_in03.gat,255,14
lhz_in03.gat,250,14,0	warp	lighthalzenwarp1076	1,1,lhz_in03.gat,252,83
//貧民街-酒場
lighthalzen.gat,345,231,0	warp	lighthalzenwarp1077	1,1,lhz_in03.gat,188,15
lhz_in03.gat,188,11,0	warp	lighthalzenwarp1078	1,1,lighthalzen.gat,344,227
lighthalzen.gat,340,240,0	warp	lighthalzenwarp1079	1,1,lhz_in03.gat,180,86
lhz_in03.gat,180,90,0	warp	lighthalzenwarp1080	1,1,lighthalzen.gat,339,245
//貧民街-酒場1F⇔2F
lhz_in03.gat,191,35,0	warp	lighthalzenwarp1081	1,1,lhz_in03.gat,191,103
lhz_in03.gat,190,100,0	warp	lighthalzenwarp1082	1,1,lhz_in03.gat,190,31
//貧民街-長老の家
lighthalzen.gat,347,261,0	warp	lighthalzenwarp1083	1,1,lhz_in03.gat,14,218
lhz_in03.gat,10,216,0	warp	lighthalzenwarp1084	1,1,lighthalzen.gat,341,261
//貧民街-足の悪い少女の家
//lighthalzen.gat,323,322,0	warp	lighthalzenwarp1085	1,1,lhz_in03.gat,15,162
lhz_in03.gat,12,162,0	warp	lighthalzenwarp1086	1,1,lighthalzen.gat,321,322

//リヒタルゼン空港
lighthalzen.gat,267,75,0	warp	lighthalzenwarp1087	1,1,lhz_airport.gat,142,17
lhz_airport.gat,142,13,0	warp	lighthalzenwarp1088	1,1,lighthalzen.gat,262,75
lhz_airport.gat,142,60,0	warp	lighthalzenwarp1089	1,1,lighthalzen.gat,296,76
lighthalzen.gat,294,76,0	warp	lighthalzenwarp1090	1,1,lhz_airport.gat,143,53
//リヒタルゼン空港-1F⇔2F
lhz_airport.gat,124,13,0	warp	lighthalzenwarp1091	1,1,lhz_airport.gat,19,21
lhz_airport.gat,19,18,0	warp	lighthalzenwarp1092	1,1,lhz_airport.gat,122,16
lhz_airport.gat,161,13,0	warp	lighthalzenwarp1093	1,1,lhz_airport.gat,47,21
lhz_airport.gat,47,18,0	warp	lighthalzenwarp1094	1,1,lhz_airport.gat,163,16
//飛行船
lighthalzen.gat,308,76,0	warp	lighthalzenwarp1095	1,1,airplane.gat,244,58
airplane.gat,208,53,0		warp	lighthalzenwarp1096	1,1,airplane.gat,239,160
airplane.gat,245,160,0		warp	lighthalzenwarp1097	1,1,airplane.gat,214,54
//飛行船-国際線
airplane_01.gat,254,54,0	warp	lighthalzenwarp1098	1,1,airplane_01.gat,91,67
airplane_01.gat,87,67,0		warp	lighthalzenwarp1099	1,1,airplane_01.gat,250,54
airplane_01.gat,245,160,0	warp	lighthalzenwarp1100	1,1,airplane_01.gat,214,54
airplane_01.gat,208,53,0	warp	lighthalzenwarp1101	1,1,airplane_01.gat,239,160
airplane_01.gat,245,160,0	warp	lighthalzenwarp1102	1,1,airplane_01.gat,214,54





//==============================================================
// -----  フィゲル -----
// hugel.gat		田園都市フィゲル
// hu_in01.gat		フィゲル室内
// -----
// kh_vila.gat		キルハイルの別荘
// kh_school.gat	キルハイル学院
// kh_rossi.gat		ロシミエルの邸宅
// kh_mansion.gat	キルハイルの邸宅
// -----
// hu_fild06.gat	フィゲルフィールド06
// yuno_fild02.gat	ジュノーフィールド02
// yuno_fild08.gat	ジュノーフィールド08
//==============================================================
//田園都市フィゲル⇒フィゲルフィールド06
hugel.gat,95,33,0	warp	hugelwarp0501	1,1,hu_fild06.gat,200,367

//教会
hugel.gat,155,114,0	warp	hugelwarp1001	1,1,hu_in01.gat,211,177
hu_in01.gat,211,173,0	warp	hugelwarp1002	1,1,hugel.gat,159,114
hu_in01.gat,195,192,0	warp	hugelwarp1003	1,1,hu_in01.gat,158,168
hu_in01.gat,162,168,0	warp	hugelwarp1004	1,1,hu_in01.gat,200,192
hu_in01.gat,195,219,0	warp	hugelwarp1005	1,1,hu_in01.gat,159,228
hu_in01.gat,162,228,0	warp	hugelwarp1006	1,1,hu_in01.gat,199,219
//旅館
hugel.gat,104,79,0	warp	hugelwarp1007	1,1,hu_in01.gat,235,107
hu_in01.gat,231,107,0	warp	hugelwarp1008	1,1,hugel.gat,101,77
hu_in01.gat,268,123,0	warp	hugelwarp1009	1,1,hu_in01.gat,265,36
hu_in01.gat,265,42,0	warp	hugelwarp1010	1,1,hu_in01.gat,262,123
//酒場
hugel.gat,129,66,0	warp	hugelwarp1011	1,1,hu_in01.gat,350,107
hu_in01.gat,345,107,0	warp	hugelwarp1012	1,1,hugel.gat,126,64
hu_in01.gat,381,118,0	warp	hugelwarp1013	1,1,hu_in01.gat,379,173
hu_in01.gat,379,178,0	warp	hugelwarp1014	1,1,hu_in01.gat,376,118
//武器屋
hugel.gat,70,157,0	warp	hugelwarp1015	1,1,hu_in01.gat,110,373
hu_in01.gat,110,369,0	warp	hugelwarp1016	1,1,hugel.gat,73,155
hu_in01.gat,108,390,0	warp	hugelwarp1017	1,1,hu_in01.gat,107,322
hu_in01.gat,114,322,0	warp	hugelwarp1018	1,1,hu_in01.gat,113,389
//道具屋
hugel.gat,92,167,0	warp	hugelwarp1019	1,1,hu_in01.gat,246,363
hu_in01.gat,246,359,0	warp	hugelwarp1020	1,1,hugel.gat,92,163
hu_in01.gat,248,388,0	warp	hugelwarp1021	1,1,hu_in01.gat,250,315
hu_in01.gat,244,315,0	warp	hugelwarp1022	1,1,hu_in01.gat,243,388
hu_in01.gat,229,313,0	warp	hugelwarp1023	1,1,hu_in01.gat,164,315
hu_in01.gat,168,315,0	warp	hugelwarp1024	1,1,hu_in01.gat,234,313
hu_in01.gat,168,307,0	warp	hugelwarp1025	1,1,hu_in01.gat,167,376
hu_in01.gat,168,379,0	warp	hugelwarp1026	1,1,hu_in01.gat,168,311
//パーティ用品店
hugel.gat,91,104,0	warp	hugelwarp1027	1,1,hu_in01.gat,30,304
hu_in01.gat,30,299,0	warp	hugelwarp1028	1,1,hugel.gat,95,103
hu_in01.gat,34,318,0	warp	hugelwarp1029	1,1,hu_in01.gat,34,251
hu_in01.gat,34,246,0	warp	hugelwarp1030	1,1,hu_in01.gat,34,313
//民家
hugel.gat,153,153,0	warp	hugelwarp1031	1,1,hu_in01.gat,287,231
hu_in01.gat,287,227,0	warp	hugelwarp1032	1,1,hugel.gat,153,149
hu_in01.gat,263,252,0	warp	hugelwarp1033	1,1,hu_in01.gat,360,253
hu_in01.gat,365,253,0	warp	hugelwarp1034	1,1,hu_in01.gat,268,252
//民家
hugel.gat,80,230,0	warp	hugelwarp1035	1,1,hu_in01.gat,24,364
hu_in01.gat,24,362,0	warp	hugelwarp1036	1,1,hugel.gat,83,228
//民家
hugel.gat,153,216,0	warp	hugelwarp1037	1,1,hu_in01.gat,305,379
hu_in01.gat,301,379,0	warp	hugelwarp1038	1,1,hugel.gat,147,216
hu_in01.gat,314,386,0	warp	hugelwarp1039	1,1,hu_in01.gat,312,322
hu_in01.gat,307,322,0	warp	hugelwarp1040	1,1,hu_in01.gat,310,386
//ハンターギルド
hugel.gat,206,228,0	warp	hugelwarp1041	1,1,hu_in01.gat,381,368
hu_in01.gat,381,363,0	warp	hugelwarp1042	1,1,hugel.gat,208,226
hu_in01.gat,388,388,0	warp	hugelwarp1043	1,1,hu_in01.gat,385,319
hu_in01.gat,380,319,0	warp	hugelwarp1044	1,1,hu_in01.gat,382,388
//神殿発掘団
//hugel.gat,52,90,0	warp	hugelwarp1045	1,1,hu_in01.gat,33,90
hu_in01.gat,37,90,0	warp	hugelwarp1046	1,1,hugel.gat,52,95
//hu_in01.gat,15,108,0	warp	hugelwarp1047	1,1,hu_in01.gat,15,155
hu_in01.gat,15,151,0	warp	hugelwarp1048	1,1,hu_in01.gat,15,104
hu_in01.gat,15,70,0	warp	hugelwarp1049	1,1,hu_in01.gat,15,25
hu_in01.gat,15,29,0	warp	hugelwarp1050	1,1,hu_in01.gat,15,74
hu_in01.gat,177,90,0	warp	hugelwarp1051	1,1,hugel.gat,52,95
hu_in01.gat,107,90,0	warp	hugelwarp1052	1,1,hugel.gat,52,95
hu_in01.gat,85,108,0	warp	hugelwarp1053	1,1,hu_in01.gat,85,155
hu_in01.gat,85,151,0	warp	hugelwarp1054	1,1,hu_in01.gat,85,104
hu_in01.gat,85,70,0	warp	hugelwarp1055	1,1,hu_in01.gat,85,25
hu_in01.gat,85,29,0	warp	hugelwarp1056	1,1,hu_in01.gat,85,74
//ビンゴゲーム会場
hugel.gat,55,208,0	warp	hugelwarp1057	1,1,que_bingo.gat,49,9
que_bingo.gat,49,7,0	warp	hugelwarp1058	1,1,hugel.gat,57,207
que_bingo.gat,39,34,0	warp	hugelwarp1059	1,1,que_bingo.gat,34,109
que_bingo.gat,34,105,0	warp	hugelwarp1060	1,1,que_bingo.gat,38,28
que_bingo.gat,53,34,0	warp	hugelwarp1061	1,1,que_bingo.gat,49,71
que_bingo.gat,48,66,0	warp	hugelwarp1062	1,1,que_bingo.gat,53,29
//==============================================================
//ガンスリンガー転職所
que_ng.gat,130,166,0	warp	ngwarp0101	1,1,einbroch.gat,130,197
einbroch.gat,137,199,0	warp	ngwarp0601	1,1,que_ng.gat,138,167
que_ng.gat,165,137,0	warp	ngwarp6001	1,1,que_ng.gat,177,41
que_ng.gat,172,42,0	warp	ngwarp6002	1,1,que_ng.gat,160,139
que_ng.gat,178,162,0	warp	ngwarp6003	1,1,que_ng.gat,176,86
que_ng.gat,170,85,0	warp	ngwarp6004	1,1,que_ng.gat,182,161
//忍者転職所
que_ng.gat,20,138,0	warp	ngwarp0102	1,1,amatsu.gat,147,136
amatsu.gat,148,140,0	warp	ngwarp0602	1,1,que_ng.gat,20,142
que_ng.gat,10,183,0	warp	ngwarp6005	1,1,que_ng.gat,33,64
que_ng.gat,37,64,0	warp	ngwarp6006	1,1,que_ng.gat,15,182
que_ng.gat,30,37,0	warp	ngwarp6007	1,1,que_ng.gat,67,28
que_ng.gat,63,30,0	warp	ngwarp6008	1,1,que_ng.gat,25,37
//==============================================================
//キル・ハイル学院
kh_school.gat,76,156,0		warp	khwarp1001	1,1,yuno_fild08.gat,155,189
kh_school.gat,30,125,0		warp	khwarp1002	1,1,kh_school.gat,67,14
kh_school.gat,71,14,0		warp	khwarp1003	1,1,kh_school.gat,36,125
kh_school.gat,30,185,0		warp	khwarp1004	1,1,kh_school.gat,67,74
kh_school.gat,71,74,0		warp	khwarp1005	1,1,kh_school.gat,35,184
kh_school.gat,35,133,0		warp	khwarp1006	1,1,kh_school.gat,148,16
kh_school.gat,153,16,0		warp	khwarp1007	1,1,kh_school.gat,39,136
kh_school.gat,35,176,0		warp	khwarp1008	1,1,kh_school.gat,148,56
kh_school.gat,153,56,0		warp	khwarp1009	1,1,kh_school.gat,40,176
kh_school.gat,30,155,0		warp	khwarp1010	1,1,kh_school.gat,182,116
kh_school.gat,186,117,0		warp	khwarp1011	1,1,kh_school.gat,35,155
//キル・ハイルの別荘
kh_vila.gat,191,18,0		warp	khwarp1012	1,1,yuno_fild02.gat,74,215
kh_vila.gat,79,11,0		warp	khwarp1013	1,1,yuno_fild02.gat,92,208
kh_vila.gat,71,38,0		warp	khwarp1014	1,1,kh_vila.gat,42,38
kh_vila.gat,46,38,0		warp	khwarp1015	1,1,kh_vila.gat,75,38
kh_vila.gat,71,54,0		warp	khwarp1016	1,1,kh_vila.gat,42,54
kh_vila.gat,46,54,0		warp	khwarp1017	1,1,kh_vila.gat,75,54
kh_vila.gat,84,66,0		warp	khwarp1018	1,1,kh_vila.gat,44,107
kh_vila.gat,44,103,0		warp	khwarp1019	1,1,kh_vila.gat,84,62
kh_vila.gat,34,66,0		warp	khwarp1020	1,1,kh_vila.gat,20,108
kh_vila.gat,20,103,0		warp	khwarp1021	1,1,kh_vila.gat,34,61
kh_vila.gat,32,128,0		warp	khwarp1022	1,1,kh_vila.gat,23,171
kh_vila.gat,22,167,0		warp	khwarp1023	1,1,kh_vila.gat,32,123
kh_vila.gat,90,47,0		warp	khwarp1024	1,1,kh_vila.gat,119,47
kh_vila.gat,115,47,0		warp	khwarp1025	1,1,kh_vila.gat,85,47
kh_vila.gat,126,75,0		warp	khwarp1026	1,1,kh_vila.gat,180,176
kh_vila.gat,180,171,0		warp	khwarp1027	1,1,kh_vila.gat,126,70
kh_vila.gat,175,71,0		warp	khwarp1028	1,1,kh_vila.gat,136,64
//キル・ハイル邸
lighthalzen.gat,188,204,0	warp	khwarp1029	1,1,kh_mansion.gat,84,49
kh_mansion.gat,88,50,0		warp	khwarp1030	1,1,lighthalzen.gat,188,199
kh_mansion.gat,21,11,0		warp	khwarp1031	1,1,kh_mansion.gat,72,49
//ロシミエル邸
kh_rossi.gat,15,92,0		warp	khwarp1032	1,1,yuno.gat,270,139
kh_rossi.gat,35,98,0		warp	khwarp1033	1,1,kh_rossi.gat,27,147
kh_rossi.gat,27,143,0		warp	khwarp1034	1,1,kh_rossi.gat,35,94
kh_rossi.gat,35,87,0		warp	khwarp1035	1,1,kh_rossi.gat,27,37
kh_rossi.gat,27,42,0		warp	khwarp1036	1,1,kh_rossi.gat,35,91
kh_rossi.gat,63,87,0		warp	khwarp1037	1,1,kh_rossi.gat,99,38
kh_rossi.gat,99,42,0		warp	khwarp1038	1,1,kh_rossi.gat,63,91
kh_rossi.gat,90,87,0		warp	khwarp1039	1,1,kh_rossi.gat,168,30
kh_rossi.gat,168,34,0		warp	khwarp1040	1,1,kh_rossi.gat,90,90
kh_rossi.gat,42,26,0		warp	khwarp1041	1,1,kh_rossi.gat,92,25
kh_rossi.gat,87,25,0		warp	khwarp1042	1,1,kh_rossi.gat,36,26
kh_rossi.gat,90,101,0		warp	khwarp1043	1,1,kh_rossi.gat,282,64
kh_rossi.gat,282,60,0		warp	khwarp1044	1,1,kh_rossi.gat,90,96
kh_rossi.gat,222,25,0		warp	khwarp1045	1,1,kh_rossi.gat,22,219
kh_rossi.gat,22,222,0		warp	khwarp1046	1,1,kh_rossi.gat,222,29
kh_rossi.gat,248,25,0		warp	khwarp1047	1,1,kh_rossi.gat,88,217
kh_rossi.gat,88,222,0		warp	khwarp1048	1,1,kh_rossi.gat,248,29
kh_rossi.gat,222,68,0		warp	khwarp1049	1,1,kh_rossi.gat,22,277
kh_rossi.gat,22,273,0		warp	khwarp1050	1,1,kh_rossi.gat,222,64
kh_rossi.gat,248,68,0		warp	khwarp1051	1,1,kh_rossi.gat,88,277
kh_rossi.gat,88,273,0		warp	khwarp1052	1,1,kh_rossi.gat,248,64
kh_rossi.gat,259,46,0		warp	khwarp1053	1,1,kh_rossi.gat,224,234
kh_rossi.gat,228,234,0		warp	khwarp1054	1,1,kh_rossi.gat,263,46
kh_rossi.gat,188,238,0		warp	khwarp1055	1,1,kh_rossi.gat,148,283
kh_rossi.gat,148,279,0		warp	khwarp1056	1,1,kh_rossi.gat,188,235
kh_rossi.gat,204,238,0		warp	khwarp1057	1,1,kh_rossi.gat,204,283
kh_rossi.gat,204,279,0		warp	khwarp1058	1,1,kh_rossi.gat,204,235
kh_rossi.gat,220,238,0		warp	khwarp1059	1,1,kh_rossi.gat,261,283
kh_rossi.gat,260,279,0		warp	khwarp1060	1,1,kh_rossi.gat,220,235
kh_rossi.gat,188,231,0		warp	khwarp1061	1,1,kh_rossi.gat,148,186
kh_rossi.gat,148,190,0		warp	khwarp1062	1,1,kh_rossi.gat,188,234
kh_rossi.gat,204,231,0		warp	khwarp1063	1,1,kh_rossi.gat,204,186
kh_rossi.gat,204,190,0		warp	khwarp1064	1,1,kh_rossi.gat,204,234
kh_rossi.gat,220,231,0		warp	khwarp1065	1,1,kh_rossi.gat,260,186
kh_rossi.gat,260,190,0		warp	khwarp1066	1,1,kh_rossi.gat,220,234



//---ラヘル追加マップ


//==============================================================
// -----  ラヘル -----
// rachel.gat		アルナベルツ教国首都 ラヘル
// ra_in01.gat		ラヘル 室内
// ra_temple.gat	フレイヤ大神殿（セスルムニル）
// ra_temin.gat		フレイヤ大神殿 室内
// ra_temsky.gat	教皇執務室（空中庭園）
// -----
// ra_fild11.gat	ラヘルフィールド11（イダ平原）
// ra_fild12.gat	ラヘルフィールド12（イダ平原）
//==============================================================
//アルナベルツ教国首都ラヘル⇔フレイヤ大神殿
rachel.gat,150,249,0	warp	rachelwarp0101	1,1,ra_temple.gat,120,30
ra_temple.gat,120,22,0	warp	rachelwarp0102	1,1,rachel.gat,150,243
//アルナベルツ教国首都ラヘル⇒ラヘルフィールド11
rachel.gat,25,125,0	warp	rachelwarp0501	1,1,ra_fild11.gat,353,226
//アルナベルツ教国首都ラヘル⇒ラヘルフィールド12
rachel.gat,275,125,0	warp	rachelwarp0502	1,1,ra_fild12.gat,40,226

//ホテル
rachel.gat,115,149,0	warp	rachelwarp1001	1,1,ra_in01.gat,386,43
ra_in01.gat,386,39,0	warp	rachelwarp1002	1,1,rachel.gat,115,144
rachel.gat,105,171,0	warp	rachelwarp1003	1,1,ra_in01.gat,309,65
ra_in01.gat,309,70,0	warp	rachelwarp1004	1,1,rachel.gat,108,175
rachel.gat,116,158,0	warp	rachelwarp1005	1,1,ra_in01.gat,375,114
ra_in01.gat,375,109,0	warp	rachelwarp1006	1,1,rachel.gat,116,154
ra_in01.gat,357,61,0	warp	rachelwarp1007	1,1,ra_in01.gat,310,62
ra_in01.gat,314,62,0	warp	rachelwarp1008	1,1,ra_in01.gat,361,61
ra_in01.gat,297,59,0	warp	rachelwarp1009	1,1,ra_in01.gat,339,116
ra_in01.gat,339,120,0	warp	rachelwarp1010	1,1,ra_in01.gat,297,63
//武器屋
rachel.gat,42,109,0	warp	rachelwarp1011	1,1,ra_in01.gat,171,388
ra_in01.gat,172,392,0	warp	rachelwarp1012	1,1,rachel.gat,42,114
rachel.gat,42,87,0	warp	rachelwarp1013	1,1,ra_in01.gat,171,359
ra_in01.gat,171,355,0	warp	rachelwarp1014	1,1,rachel.gat,42,82
ra_in01.gat,165,369,0	warp	rachelwarp1015	1,1,ra_in01.gat,122,334
ra_in01.gat,126,334,0	warp	rachelwarp1016	1,1,ra_in01.gat,169,369
ra_in01.gat,178,370,0	warp	rachelwarp1017	1,1,ra_in01.gat,113,385
ra_in01.gat,109,385,0	warp	rachelwarp1018	1,1,ra_in01.gat,174,370
//道具屋
rachel.gat,83,78,0	warp	rachelwarp1019	1,1,ra_in01.gat,249,266
ra_in01.gat,249,262,0	warp	rachelwarp1020	1,1,rachel.gat,83,73
ra_in01.gat,241,299,0	warp	rachelwarp1021	1,1,ra_in01.gat,193,312
ra_in01.gat,197,312,0	warp	rachelwarp1022	1,1,ra_in01.gat,245,299
ra_in01.gat,185,303,0	warp	rachelwarp1023	1,1,ra_in01.gat,194,249
ra_in01.gat,194,245,0	warp	rachelwarp1024	1,1,ra_in01.gat,190,302
//ジェドの屋敷
rachel.gat,103,240,0	warp	rachelwarp1025	1,1,ra_in01.gat,343,193
ra_in01.gat,339,193,0	warp	rachelwarp1026	1,1,rachel.gat,98,238
ra_in01.gat,381,200,0	warp	rachelwarp1027	1,1,ra_in01.gat,377,268
ra_in01.gat,381,268,0	warp	rachelwarp1028	1,1,ra_in01.gat,387,200
ra_in01.gat,367,255,0	warp	rachelwarp1029	1,1,ra_in01.gat,326,296
ra_in01.gat,330,296,0	warp	rachelwarp1030	1,1,ra_in01.gat,371,255
ra_in01.gat,319,303,0	warp	rachelwarp1031	1,1,ra_in01.gat,381,320
ra_in01.gat,381,324,0	warp	rachelwarp1032	1,1,ra_in01.gat,319,299
//屋敷
rachel.gat,179,220,0	warp	rachelwarp1033	1,1,ra_in01.gat,295,352
ra_in01.gat,295,348,0	warp	rachelwarp1034	1,1,rachel.gat,179,215
ra_in01.gat,312,374,0	warp	rachelwarp1035	1,1,ra_in01.gat,359,374
ra_in01.gat,355,374,0	warp	rachelwarp1036	1,1,ra_in01.gat,308,374
ra_in01.gat,291,371,0	warp	rachelwarp1037	1,1,ra_in01.gat,225,380
ra_in01.gat,221,380,0	warp	rachelwarp1038	1,1,ra_in01.gat,287,371
//カッティングシュエルの家
rachel.gat,61,33,0	warp	rachelwarp1039	1,1,ra_in01.gat,181,198
ra_in01.gat,181,202,0	warp	rachelwarp1040	1,1,rachel.gat,61,38
rachel.gat,81,33,0	warp	rachelwarp1041	1,1,ra_in01.gat,237,198
ra_in01.gat,237,202,0	warp	rachelwarp1042	1,1,rachel.gat,81,38
ra_in01.gat,175,189,0	warp	rachelwarp1043	1,1,ra_in01.gat,132,189
ra_in01.gat,136,189,0	warp	rachelwarp1044	1,1,ra_in01.gat,179,189
ra_in01.gat,188,189,0	warp	rachelwarp1045	1,1,ra_in01.gat,263,144
ra_in01.gat,259,144,0	warp	rachelwarp1046	1,1,ra_in01.gat,184,189
ra_in01.gat,296,144,0	warp	rachelwarp1047	1,1,ra_in01.gat,235,189
ra_in01.gat,231,189,0	warp	rachelwarp1048	1,1,ra_in01.gat,292,144
ra_in01.gat,244,189,0	warp	rachelwarp1049	1,1,ra_in01.gat,291,189
ra_in01.gat,287,189,0	warp	rachelwarp1050	1,1,ra_in01.gat,240,189
//ブルーの家
rachel.gat,217,55,0	warp	rachelwarp1051	1,1,ra_in01.gat,250,34
ra_in01.gat,250,38,0	warp	rachelwarp1052	1,1,rachel.gat,217,60
ra_in01.gat,235,21,0	warp	rachelwarp1053	1,1,ra_in01.gat,187,31
ra_in01.gat,183,31,0	warp	rachelwarp1054	1,1,ra_in01.gat,239,21
//民家
rachel.gat,216,160,0	warp	rachelwarp1055	1,1,ra_in01.gat,135,282
ra_in01.gat,135,286,0	warp	rachelwarp1056	1,1,rachel.gat,216,164
//民家
rachel.gat,108,200,0	warp	rachelwarp1057	1,1,ra_in01.gat,213,83
ra_in01.gat,213,79,0	warp	rachelwarp1058	1,1,rachel.gat,108,195
//民家
rachel.gat,90,189,0	warp	rachelwarp1059	1,1,ra_in01.gat,192,148
ra_in01.gat,192,152,0	warp	rachelwarp1060	1,1,rachel.gat,90,193

//フレイヤ大神殿 室内⇒フレイヤ大神殿
ra_temin.gat,169,18,0	warp	rachelwarp1061	1,1,ra_temple.gat,119,175
//フレイヤ神殿 室内1F⇔フレイヤ神殿 室内2F
ra_temin.gat,130,93,0	warp	rachelwarp1062	1,1,ra_temin.gat,239,258
ra_temin.gat,239,253,0	warp	rachelwarp1063	1,1,ra_temin.gat,130,88
ra_temin.gat,206,93,0	warp	rachelwarp1064	1,1,ra_temin.gat,312,258
ra_temin.gat,312,253,0	warp	rachelwarp1065	1,1,ra_temin.gat,206,88
//フレイヤ神殿 室内2F⇔フレイヤ神殿 聖域前
ra_temin.gat,275,332,0	warp	rachelwarp1066	1,1,ra_temin.gat,27,305
ra_temin.gat,27,299,0	warp	rachelwarp1067	1,1,ra_temin.gat,275,328
//フレイヤ神殿 執務室前⇒フレイヤ神殿 執務室入口
ra_temin.gat,275,243,0	warp	rachelwarp1068	1,1,ra_temin.gat,131,131
//フレイヤ神殿 室内⇔教皇執務室
//ra_temin.gat,275,226,0	warp	rachelwarp1069	1,1,ra_temsky.gat,99,11
ra_temsky.gat,99,8,0	warp	rachelwarp1070	1,1,ra_temin.gat,275,231
//教皇執務室
ra_temsky.gat,99,118,0	warp	rachelwarp1071	1,1,ra_temsky.gat,99,140
ra_temsky.gat,99,135,0	warp	rachelwarp1072	1,1,ra_temsky.gat,99,113
ra_temsky.gat,87,143,0	warp	rachelwarp1073	1,1,ra_temsky.gat,58,139
ra_temsky.gat,62,139,0	warp	rachelwarp1074	1,1,ra_temsky.gat,91,143
ra_temsky.gat,112,143,0	warp	rachelwarp1075	1,1,ra_temsky.gat,141,139
ra_temsky.gat,137,139,0	warp	rachelwarp1076	1,1,ra_temsky.gat,109,143
//フレイヤ神殿 室内（クエスト）
que_rachel.gat,130,93,0		warp	rachelwarp1077	1,1,que_rachel.gat,239,258
que_rachel.gat,239,253,0	warp	rachelwarp1078	1,1,que_rachel.gat,130,88
que_rachel.gat,206,93,0		warp	rachelwarp1079	1,1,que_rachel.gat,312,258
que_rachel.gat,312,253,0	warp	rachelwarp1080	1,1,que_rachel.gat,206,88
que_rachel.gat,275,332,0	warp	rachelwarp1081	1,1,que_rachel.gat,27,305
que_rachel.gat,27,299,0		warp	rachelwarp1082	1,1,que_rachel.gat,275,328



//---ベインス追加マップ


//==============================================================
// -----  ベインス -----
// veins.gat		峡谷都市ベインス
// ve_in.gat		ベインス 室内
// ve_in02.gat		ベインス 室内
// -----
// ve_fild06.gat	ベインスフィールド 06
// ve_fild07.gat	ベインスフィールド 07
//==============================================================
//峡谷都市ベインス⇒ベインスフィールド 06
veins.gat,218,361,0	warp	veinswarp0501	1,1,ve_fild06.gat,148,225
//峡谷都市ベインス⇒ベインスフィールド 07
veins.gat,143,25,0	warp	veinswarp0502	1,1,ve_fild07.gat,147,366
//アルナベルツ教国首都 ラヘル⇒ベインスフィールド 02
rachel.gat,130,21,0	warp	veinswarp0502	1,1,ve_fild02.gat,195,377

//セスルムニル神殿
veins.gat,197,260,0	warp	veinswarp1001	1,1,ve_in.gat,351,321
ve_in.gat,351,317,0	warp	veinswarp1002	1,1,veins.gat,197,255
//旅館
veins.gat,114,278,0	warp	veinswarp1003	1,1,ve_in.gat,183,207
ve_in.gat,183,203,0	warp	veinswarp1004	1,1,veins.gat,110,278
veins.gat,128,270,0	warp	veinswarp1005	1,1,ve_in.gat,201,211
ve_in.gat,206,211,0	warp	veinswarp1006	1,1,veins.gat,128,266
//旅館別館
veins.gat,130,238,0	warp	veinswarp1007	1,1,ve_in.gat,99,219
ve_in.gat,99,215,0	warp	veinswarp1008	1,1,veins.gat,127,235
ve_in.gat,76,229,0	warp	veinswarp1009	1,1,ve_in.gat,75,160
ve_in.gat,71,160,0	warp	veinswarp1010	1,1,ve_in.gat,72,229
//武器屋
veins.gat,150,179,0	warp	veinswarp1011	1,1,ve_in.gat,349,223
ve_in.gat,349,219,0	warp	veinswarp1012	1,1,veins.gat,150,175
ve_in.gat,347,250,0	warp	veinswarp1013	1,1,ve_in.gat,282,223
ve_in.gat,286,223,0	warp	veinswarp1014	1,1,ve_in.gat,352,250
//道具屋
veins.gat,230,166,0	warp	veinswarp1015	1,1,ve_in.gat,251,287
ve_in.gat,251,283,0	warp	veinswarp1016	1,1,veins.gat,230,161
ve_in.gat,261,315,0	warp	veinswarp1017	1,1,ve_in.gat,177,297
ve_in.gat,177,293,0	warp	veinswarp1018	1,1,ve_in.gat,261,311
//酒場
veins.gat,148,220,0	warp	veinswarp1019	1,1,ve_in.gat,252,127
ve_in.gat,256,127,0	warp	veinswarp1020	1,1,veins.gat,150,215
ve_in.gat,224,115,0	warp	veinswarp1021	1,1,ve_in.gat,313,114
ve_in.gat,309,114,0	warp	veinswarp1022	1,1,ve_in.gat,220,115
//治安管理所
veins.gat,88,173,0	warp	veinswarp1023	1,1,ve_in.gat,77,295
ve_in.gat,77,291,0	warp	veinswarp1024	1,1,veins.gat,88,168
ve_in.gat,98,299,0	warp	veinswarp1025	1,1,ve_in.gat,124,372
ve_in.gat,128,372,0	warp	veinswarp1026	1,1,ve_in.gat,102,299
//民家
veins.gat,337,231,0	warp	veinswarp1027	1,1,ve_in.gat,194,374
ve_in.gat,194,369,0	warp	veinswarp1028	1,1,veins.gat,331,231
//工場
veins.gat,267,230,0	warp	veinswarp1029	1,1,ve_in02.gat,17,19
ve_in02.gat,13,19,0	warp	veinswarp1030	1,1,veins.gat,269,225



//---名もなき島追加マップ


//==============================================================
// nameless_i.gat	名もなき島 朝
// nameless_n.gat	名もなき島 夜
// nameless_in.gat	名もなき島 室内
// -----
// abbey01.gat		修道院 01
//==============================================================
//名もなき島 夜⇒修道院
nameless_n.gat,157,184,0	warp	namelesswarp0401	1,1,abbey01.gat,51,15

//北東の家
nameless_i.gat,228,232,0	warp	namelesswarp1001	1,1,nameless_in.gat,12,172
nameless_in.gat,12,169,0	warp	namelesswarp1002	1,1,nameless_i.gat,230,229
//北西の家
nameless_i.gat,75,251,0		warp	namelesswarp1003	1,1,nameless_in.gat,82,159
nameless_in.gat,86,159,0	warp	namelesswarp1004	1,1,nameless_i.gat,78,246
nameless_i.gat,100,259,0	warp	namelesswarp1005	1,1,nameless_in.gat,97,180
nameless_in.gat,96,177,0	warp	namelesswarp1006	1,1,nameless_i.gat,99,255
//南東の家
nameless_i.gat,252,130,0	warp	namelesswarp1007	1,1,nameless_in.gat,26,128
nameless_in.gat,23,128,0	warp	namelesswarp1008	1,1,nameless_i.gat,249,127
nameless_i.gat,253,116,0	warp	namelesswarp1009	1,1,nameless_in.gat,12,109
nameless_in.gat,12,112,0	warp	namelesswarp1010	1,1,nameless_i.gat,254,121



//---モスコビア追加マップ


//==============================================================
// -----  モスコビア -----
// moscovia.gat		モスコビア
// mosk_in.gat		モスコビア 内部
// -----
// mosk_dun02.gat	深い森
//==============================================================
//王宮
moscovia.gat,256,138,0	warp	moscoviawarp1001	1,1,mosk_in.gat,96,61
mosk_in.gat,93,61,0	warp	moscoviawarp1002	1,1,moscovia.gat,255,140
mosk_in.gat,99,126,0	warp	moscoviawarp1003	1,1,mosk_in.gat,21,116
mosk_in.gat,21,113,0	warp	moscoviawarp1004	1,1,mosk_in.gat,99,123
//武器屋
moscovia.gat,185,188,0	warp	moscoviawarp1005	1,1,mosk_in.gat,15,179
mosk_in.gat,12,179,0	warp	moscoviawarp1006	1,1,moscovia.gat,186,191
//防具屋
moscovia.gat,203,171,0	warp	moscoviawarp1007	1,1,mosk_in.gat,86,180
mosk_in.gat,89,180,0	warp	moscoviawarp1008	1,1,moscovia.gat,204,169
//道具屋
moscovia.gat,223,174,0	warp	moscoviawarp1009	1,1,mosk_in.gat,14,246
mosk_in.gat,11,246,0	warp	moscoviawarp1010	1,1,moscovia.gat,222,176
//旅館
moscovia.gat,229,208,0	warp	moscoviawarp1011	1,1,mosk_in.gat,142,178
mosk_in.gat,142,175,0	warp	moscoviawarp1012	1,1,moscovia.gat,227,207
mosk_in.gat,150,192,0	warp	moscoviawarp1013	1,1,mosk_in.gat,204,188
mosk_in.gat,202,188,0	warp	moscoviawarp1014	1,1,mosk_in.gat,148,192
//民家
moscovia.gat,256,179,0	warp	moscoviawarp1015	1,1,mosk_in.gat,211,114
mosk_in.gat,211,111,0	warp	moscoviawarp1016	1,1,moscovia.gat,253,179
mosk_in.gat,222,128,0	warp	moscoviawarp1017	1,1,mosk_in.gat,288,118
mosk_in.gat,288,116,0	warp	moscoviawarp1018	1,1,mosk_in.gat,222,126
//ミハイルの家
moscovia.gat,205,98,0	warp	moscoviawarp1019	1,1,mosk_in.gat,214,255
mosk_in.gat,214,252,0	warp	moscoviawarp1020	1,1,moscovia.gat,203,96
mosk_in.gat,220,273,0	warp	moscoviawarp1021	1,1,mosk_in.gat,152,275
mosk_in.gat,152,272,0	warp	moscoviawarp1022	1,1,mosk_in.gat,220,270
//ババヤガの家
mosk_in.gat,215,36,0	warp	moscoviawarp1023	1,1,mosk_dun02.gat,53,217



//---アッシュ・バキューム追加マップ


//==============================================================
// -----  ミッドガルド連合軍駐屯地  -----
// mid_camp.gat		ミッドガルド連合軍駐屯地
// mid_campin.gat	ミッドガルド連合軍駐屯地内部
//==============================================================
//連合軍本部
mid_camp.gat,214,249,0		warp	midcampwarp1001		1,1,mid_campin.gat,89,102
mid_campin.gat,89,99,0		warp	midcampwarp1002		1,1,mid_camp.gat,215,247
mid_campin.gat,66,114,0		warp	midcampwarp1003		1,1,mid_campin.gat,22,80
mid_campin.gat,25,80,0		warp	midcampwarp1004		1,1,mid_campin.gat,70,114
mid_campin.gat,66,120,0		warp	midcampwarp1005		1,1,mid_campin.gat,22,124
mid_campin.gat,25,124,0		warp	midcampwarp1006		1,1,mid_campin.gat,70,120
mid_campin.gat,68,128,0		warp	midcampwarp1007		1,1,mid_campin.gat,22,168
mid_campin.gat,25,168,0		warp	midcampwarp1008		1,1,mid_campin.gat,71,128
mid_campin.gat,86,141,0		warp	midcampwarp1009		1,1,mid_campin.gat,66,181
mid_campin.gat,65,178,0		warp	midcampwarp1010		1,1,mid_campin.gat,86,138
mid_campin.gat,94,141,0		warp	midcampwarp1011		1,1,mid_campin.gat,117,181
mid_campin.gat,117,178,0	warp	midcampwarp1012		1,1,mid_campin.gat,94,138
mid_campin.gat,111,128,0	warp	midcampwarp1013		1,1,mid_campin.gat,165,170
mid_campin.gat,162,170,0	warp	midcampwarp1014		1,1,mid_campin.gat,108,128
//mid_campin.gat,113,120,0	warp	midcampwarp1015		1,1,mid_campin.gat,165,126
mid_campin.gat,162,126,0	warp	midcampwarp1016		1,1,mid_campin.gat,110,120
mid_campin.gat,113,114,0	warp	midcampwarp1017		1,1,mid_campin.gat,165,82
mid_campin.gat,162,82,0		warp	midcampwarp1018		1,1,mid_campin.gat,110,114
//武器庫
mid_camp.gat,205,211,0		warp	midcampwarp1019		1,1,mid_campin.gat,229,123
mid_campin.gat,232,123,0	warp	midcampwarp1020		1,1,mid_camp.gat,208,211
mid_campin.gat,223,109,0	warp	midcampwarp1021		1,1,mid_camp.gat,198,205
mid_camp.gat,196,204,0		warp	midcampwarp1022		1,1,mid_campin.gat,220,109
//宿舎（東）
mid_camp.gat,266,260,0		warp	midcampwarp1023		1,1,mid_campin.gat,286,124
mid_campin.gat,283,124,0	warp	midcampwarp1024		1,1,mid_camp.gat,263,260
//宿舎（西）
mid_camp.gat,163,231,0		warp	midcampwarp1025		1,1,mid_campin.gat,376,133
mid_campin.gat,376,136,0	warp	midcampwarp1026		1,1,mid_camp.gat,163,234


//==============================================================
// -----  鉱山の街 マヌク  -----
// manuk.gat		鉱山の街 マヌク
// man_in01.gat		マヌク 内部
// -----
// man_fild02.gat	マヌクフィールド 02
//==============================================================
//鉱山の街 マヌク⇒マヌクフィールド 02
manuk.gat,114,357,0	warp	manukwarp0501	1,1,man_fild02.gat,138,43

//首長の家
manuk.gat,311,142,0	warp	manukwarp1001	1,1,man_in01.gat,277,41
man_in01.gat,275,41,0	warp	manukwarp1002	1,1,manuk.gat,309,142
man_in01.gat,318,17,0	warp	manukwarp1003	1,1,man_in01.gat,388,16
man_in01.gat,390,16,0	warp	manukwarp1004	1,1,man_in01.gat,316,17
//研究所
manuk.gat,310,201,0	warp	manukwarp1005	1,1,man_in01.gat,358,121
man_in01.gat,358,119,0	warp	manukwarp1006	1,1,manuk.gat,310,199
man_in01.gat,328,141,0	warp	manukwarp1007	1,1,man_in01.gat,324,220
man_in01.gat,324,222,0	warp	manukwarp1008	1,1,man_in01.gat,328,139
//地下監獄
manuk.gat,255,110,0	warp	manukwarp1009	1,1,man_in01.gat,7,61
man_in01.gat,5,61,0	warp	manukwarp1010	1,1,manuk.gat,253,110
man_in01.gat,11,19,0	warp	manukwarp1011	1,1,man_in01.gat,182,32
man_in01.gat,182,34,0	warp	manukwarp1012	1,1,man_in01.gat,11,21
//住居
manuk.gat,257,228,0	warp	manukwarp1013	1,1,man_in01.gat,130,267
man_in01.gat,130,265,0	warp	manukwarp1014	1,1,manuk.gat,258,226
manuk.gat,265,237,0	warp	manukwarp1015	1,1,man_in01.gat,180,267
man_in01.gat,180,265,0	warp	manukwarp1016	1,1,manuk.gat,267,235
manuk.gat,276,247,0	warp	manukwarp1017	1,1,man_in01.gat,230,267
man_in01.gat,230,265,0	warp	manukwarp1018	1,1,manuk.gat,276,245
manuk.gat,288,249,0	warp	manukwarp1019	1,1,man_in01.gat,280,267
man_in01.gat,280,265,0	warp	manukwarp1020	1,1,manuk.gat,289,247
manuk.gat,302,243,0	warp	manukwarp1021	1,1,man_in01.gat,330,267
man_in01.gat,330,265,0	warp	manukwarp1022	1,1,manuk.gat,300,241
manuk.gat,311,234,0	warp	manukwarp1023	1,1,man_in01.gat,380,267
man_in01.gat,380,265,0	warp	manukwarp1024	1,1,manuk.gat,309,232
//食堂
manuk.gat,253,195,0	warp	manukwarp1025	1,1,man_in01.gat,24,284
man_in01.gat,26,284,0	warp	manukwarp1026	1,1,manuk.gat,255,195
man_in01.gat,5,275,0	warp	manukwarp1027	1,1,man_in01.gat,7,221
man_in01.gat,7,219,0	warp	manukwarp1028	1,1,man_in01.gat,7,276
man_in01.gat,22,275,0	warp	manukwarp1029	1,1,man_in01.gat,76,279
man_in01.gat,74,279,0	warp	manukwarp1030	1,1,man_in01.gat,20,275
manuk.gat,235,124,0	warp	manukwarp1031	1,1,man_in01.gat,70,171
man_in01.gat,70,169,0	warp	manukwarp1032	1,1,manuk.gat,235,122
man_in01.gat,61,190,0	warp	manukwarp1033	1,1,man_in01.gat,63,238
man_in01.gat,61,238,0	warp	manukwarp1034	1,1,man_in01.gat,61,188
man_in01.gat,61,173,0	warp	manukwarp1035	1,1,man_in01.gat,20,173
man_in01.gat,20,175,0	warp	manukwarp1036	1,1,man_in01.gat,61,175
//民家
manuk.gat,279,115,0	warp	manukwarp1037	1,1,man_in01.gat,123,224
man_in01.gat,123,226,0	warp	manukwarp1038	1,1,manuk.gat,278,117


//==============================================================
// -----  前線基地 スプレンディッド  -----
// splendide.gat	前線基地 スプレンディッド
// spl_in01.gat		スプレンディッド 内部01
// spl_in02.gat		スプレンディッド 内部02
// -----
// spl_fild02.gat	スプレンディッドフィールド 02
//==============================================================
//前線基地 スプレンディッド⇒スプレンディッドフィールド 02
splendide.gat,388,252,0	warp	splendidewarp0501	1,1,spl_fild02.gat,8,241

//司令部
splendide.gat,197,193,0	warp	splendidewarp1001	1,1,spl_in01.gat,110,19
spl_in01.gat,110,17,0	warp	splendidewarp1002	1,1,splendide.gat,197,191
spl_in01.gat,124,38,0	warp	splendidewarp1003	1,1,spl_in01.gat,236,36
spl_in01.gat,238,36,0	warp	splendidewarp1004	1,1,spl_in01.gat,126,38
spl_in01.gat,95,38,0	warp	splendidewarp1005	1,1,spl_in01.gat,199,36
spl_in01.gat,197,36,0	warp	splendidewarp1006	1,1,spl_in01.gat,93,38
spl_in01.gat,218,22,0	warp	splendidewarp1007	1,1,spl_in01.gat,310,19
spl_in01.gat,310,17,0	warp	splendidewarp1008	1,1,spl_in01.gat,218,20
//住居
splendide.gat,240,317,0	warp	splendidewarp1009	1,1,spl_in02.gat,224,232
spl_in02.gat,222,232,0	warp	splendidewarp1010	1,1,splendide.gat,238,317
splendide.gat,230,299,0	warp	splendidewarp1011	1,1,spl_in02.gat,207,195
spl_in02.gat,207,193,0	warp	splendidewarp1012	1,1,splendide.gat,228,299
splendide.gat,214,310,0	warp	splendidewarp1013	1,1,spl_in02.gat,180,223
spl_in02.gat,180,221,0	warp	splendidewarp1014	1,1,splendide.gat,214,308
splendide.gat,157,316,0	warp	splendidewarp1015	1,1,spl_in02.gat,108,213
spl_in02.gat,108,211,0	warp	splendidewarp1016	1,1,splendide.gat,157,314
splendide.gat,119,324,0	warp	splendidewarp1017	1,1,spl_in02.gat,61,229
spl_in02.gat,62,227,0	warp	splendidewarp1018	1,1,splendide.gat,119,322
splendide.gat,286,128,0	warp	splendidewarp1019	1,1,spl_in02.gat,236,63
spl_in02.gat,234,64,0	warp	splendidewarp1020	1,1,splendide.gat,284,129
splendide.gat,259,112,0	warp	splendidewarp1021	1,1,spl_in02.gat,189,41
spl_in02.gat,187,42,0	warp	splendidewarp1022	1,1,splendide.gat,259,114
splendide.gat,286,229,0	warp	splendidewarp1023	1,1,spl_in02.gat,137,66
spl_in02.gat,135,66,0	warp	splendidewarp1024	1,1,splendide.gat,284,228
splendide.gat,299,251,0	warp	splendidewarp1025	1,1,spl_in02.gat,140,93
spl_in02.gat,139,91,0	warp	splendidewarp1026	1,1,splendide.gat,297,250
splendide.gat,132,68,0	warp	splendidewarp1027	1,1,spl_in02.gat,45,52
spl_in02.gat,44,54,0	warp	splendidewarp1028	1,1,splendide.gat,133,70
//地下監獄
splendide.gat,170,168,0	warp	splendidewarp1029	1,1,spl_in01.gat,190,301
spl_in01.gat,190,299,0	warp	splendidewarp1030	1,1,splendide.gat,170,166
spl_in01.gat,191,320,0	warp	splendidewarp1031	1,1,spl_in01.gat,276,334
spl_in01.gat,276,336,0	warp	splendidewarp1032	1,1,spl_in01.gat,190,322
//食堂
splendide.gat,156,210,0	warp	splendidewarp1033	1,1,spl_in01.gat,171,189
spl_in01.gat,171,187,0	warp	splendidewarp1034	1,1,splendide.gat,156,208
//商店
splendide.gat,198,240,0	warp	splendidewarp1035	1,1,spl_in01.gat,110,301
spl_in01.gat,110,299,0	warp	splendidewarp1036	1,1,splendide.gat,198,238
//民家
splendide.gat,238,212,0	warp	splendidewarp1037	1,1,spl_in01.gat,30,215
spl_in01.gat,30,213,0	warp	splendidewarp1038	1,1,splendide.gat,237,210
//研究所
splendide.gat,228,164,0	warp	splendidewarp1039	1,1,spl_in01.gat,30,301
spl_in01.gat,30,299,0	warp	splendidewarp1040	1,1,splendide.gat,228,162



//---ブラジリス追加マップ


//==============================================================
// -----  ブラジリス -----
// brasilis.gat		ブラジリス
// bra_in01.gat		ブラジリス 室内
// -----
// bra_fild01.gat	ブラジリスフィールド 01
//==============================================================
//ブラジリス⇒ブラジリスフィールド 01
brasilis.gat,308,336,0	warp	brasiliswarp0501	1,1,bra_fild01.gat,74,34

//ホテル
brasilis.gat,274,153,0	warp	brasiliswarp1001	1,1,bra_in01.gat,38,9
bra_in01.gat,39,7,0		warp	brasiliswarp1002	1,1,brasilis.gat,273,151
bra_in01.gat,52,27,0	warp	brasiliswarp1003	1,1,bra_in01.gat,85,26
bra_in01.gat,83,27,0	warp	brasiliswarp1004	1,1,bra_in01.gat,50,27
bra_in01.gat,31,29,0	warp	brasiliswarp1005	1,1,bra_in01.gat,23,70
bra_in01.gat,25,70,0	warp	brasiliswarp1006	1,1,bra_in01.gat,32,26
bra_in01.gat,9,67,0		warp	brasiliswarp1007	1,1,bra_in01.gat,154,22
bra_in01.gat,156,23,0	warp	brasiliswarp1008	1,1,bra_in01.gat,11,65
bra_in01.gat,31,74,0	warp	brasiliswarp1009	1,1,bra_in01.gat,149,59
bra_in01.gat,148,57,0	warp	brasiliswarp1010	1,1,bra_in01.gat,31,72
bra_in01.gat,52,67,0	warp	brasiliswarp1011	1,1,bra_in01.gat,87,66
bra_in01.gat,85,67,0	warp	brasiliswarp1012	1,1,bra_in01.gat,50,66

//美術博物館
brasilis.gat,146,162,0	warp	brasiliswarp1013	1,1,bra_in01.gat,17,137
bra_in01.gat,17,134,0	warp	brasiliswarp1014	1,1,brasilis.gat,148,161
bra_in01.gat,50,171,0	warp	brasiliswarp1015	1,1,bra_in01.gat,82,168
bra_in01.gat,79,169,0	warp	brasiliswarp1016	1,1,bra_in01.gat,46,170
bra_in01.gat,50,145,0	warp	brasiliswarp1017	1,1,bra_in01.gat,81,143
bra_in01.gat,79,142,0	warp	brasiliswarp1018	1,1,bra_in01.gat,47,144
bra_in01.gat,138,174,0	warp	brasiliswarp1019	1,1,bra_in01.gat,12,183
bra_in01.gat,206,98,0	warp	brasiliswarp1020	1,1,brasilis.gat,120,160



//---エルディカスティス追加マップ


//==============================================================
// -----  エルディカスティス -----
// dicastes01.gat	サファ族の首都 エルディカスティス
// dicastes02.gat	ブルーメヴァルト
// dic_in01.gat		エルディカスティス 室内
// -----
// dic_fild01.gat	カミダル山麓 01
//==============================================================
//サファ族の首都 エルディカスティス⇒カミダル山麓 01
dicastes01.gat,199,34,0		warp	dicasteswarp0501	1,1,dic_fild01.gat,149,279

//サファ族の首都 エルディカスティス⇔ブルーメヴァルト
dicastes01.gat,198,353,0	warp	dicasteswarp1001	1,1,dicastes02.gat,120,80
dicastes02.gat,120,77,0		warp	dicasteswarp1002	1,1,dicastes01.gat,197,351
//ブルーメヴァルト⇔ディエル
dicastes02.gat,120,237,0	warp	dicasteswarp1003	1,1,dic_in01.gat,45,246
dic_in01.gat,45,244,0		warp	dicasteswarp1004	1,1,dicastes02.gat,119,235
//酒場バールブルーメ
dicastes01.gat,136,103,0	warp	dicasteswarp1005	1,1,dic_in01.gat,26,98
dic_in01.gat,26,96,0		warp	dicasteswarp1006	1,1,dicastes01.gat,137,106
//戦士の訓練所
dicastes01.gat,255,175,0	warp	dicasteswarp1007	1,1,dic_in01.gat,344,272
dic_in01.gat,342,271,0		warp	dicasteswarp1008	1,1,dicastes01.gat,255,173
//工場
dicastes01.gat,94,259,0		warp	dicasteswarp1009	1,1,dic_in01.gat,390,53
dic_in01.gat,390,55,0		warp	dicasteswarp1010	1,1,dicastes01.gat,95,257
//居住区域
dicastes01.gat,283,285,0	warp	dicasteswarp1011	1,1,dic_in01.gat,45,30
dic_in01.gat,45,28,0		warp	dicasteswarp1012	1,1,dicastes01.gat,281,284
//研究所
dicastes01.gat,163,297,0	warp	dicasteswarp1013	1,1,dic_in01.gat,371,101
dic_in01.gat,372,99,0		warp	dicasteswarp1014	1,1,dicastes01.gat,163,295
//アハト執務室
dic_in01.gat,299,248,0		warp	dicasteswarp1015	1,1,dic_in01.gat,262,191



//---デワタ追加マップ


//==============================================================
// -----  デワタ -----
// dewata.gat		デワタ
// dew_in01.gat		デワタ 室内
// -----
// dew_fild01.gat	デワタフィールド 01
//==============================================================
//デワタ⇒デワタフィールド 01
dewata.gat,44,252,0		warp	dewatawarp0501	1,1,dew_fild01.gat,373,212
//デワタ 室内⇒デワタフィールド 01
dew_in01.gat,16,31,0	warp	dewatawarp0502	1,1,dew_fild01.gat,59,273



//---3次職追加マップ


//==============================================================
// -----  影工房 -----
// s_atelier.gat		影工房
//==============================================================
//プロンテラ影工房
prontera.gat,272,108,0	warp	s_atelierwarp1001	1,1,s_atelier.gat,13,119
s_atelier.gat,10,119,0	warp	s_atelierwarp1002	1,1,prontera.gat,268,108
s_atelier.gat,31,128,0	warp	s_atelierwarp1003	1,1,s_atelier.gat,76,125
s_atelier.gat,76,128,0	warp	s_atelierwarp1004	1,1,s_atelier.gat,28,128
//ラヘル影工房
rachel.gat,180,115,0	warp	s_atelierwarp1005	1,1,s_atelier.gat,130,70
s_atelier.gat,131,75,0	warp	s_atelierwarp1006	1,1,rachel.gat,180,118
s_atelier.gat,117,71,0	warp	s_atelierwarp1007	1,1,s_atelier.gat,171,72
s_atelier.gat,166,72,0	warp	s_atelierwarp1008	1,1,s_atelier.gat,117,67
//ジュノー影工房
yuno.gat,278,67,0		warp	s_atelierwarp1009	1,1,s_atelier.gat,109,123
s_atelier.gat,105,123,0	warp	s_atelierwarp1010	1,1,yuno.gat,275,67
s_atelier.gat,108,129,0	warp	s_atelierwarp1011	1,1,s_atelier.gat,159,125
s_atelier.gat,159,130,0	warp	s_atelierwarp1012	1,1,s_atelier.gat,112,129
//リヒタルゼン影工房
lighthalzen.gat,41,52,0	warp	s_atelierwarp1013	1,1,s_atelier.gat,18,75
s_atelier.gat,18,79,0	warp	s_atelierwarp1014	1,1,lighthalzen.gat,41,56
s_atelier.gat,32,64,0	warp	s_atelierwarp1015	1,1,s_atelier.gat,80,63
s_atelier.gat,80,66,0	warp	s_atelierwarp1016	1,1,s_atelier.gat,32,62



//---ビフロスト追加マップ


//==============================================================
// -----  ビフロスト -----
// splendide.gat	前線基地 スプレンディッド
// -----
// bif_fild01.gat	ビフロストフィールド 01
//==============================================================
//前線基地 スプレンディッド⇒ビフロストフィールド 01
splendide.gat,275,390,0		warp	bifrostwarp0501	1,1,bif_fild01.gat,316,50



//---マラン島追加マップ


//==============================================================
// -----  マラン島 -----
// malangdo.gat	マラン島
// -----
// mal_in01.gat	マラン島 室内
// mal_in02.gat	ナビ号 船内
// mal_dun01.gat	星明りの珊瑚礁
//==============================================================
//マラン島⇒星明りの珊瑚礁
malangdo.gat,73,239,0	warp	malangdowarp0401	1,1,mal_dun01.gat,33,230

//ナビ号
malangdo.gat,162,163,0	warp	malangdowarp1001	1,1,mal_in02.gat,58,61
mal_in02.gat,60,61,0	warp	malangdowarp1002	1,1,malangdo.gat,164,163
mal_in02.gat,51,60,0	warp	malangdowarp1003	1,1,mal_in02.gat,31,60
mal_in02.gat,34,60,0	warp	malangdowarp1004	1,1,mal_in02.gat,53,59
mal_in02.gat,63,66,0	warp	malangdowarp1005	1,1,mal_in02.gat,63,89
mal_in02.gat,64,87,0	warp	malangdowarp1006	1,1,mal_in02.gat,63,64
mal_in02.gat,101,66,0	warp	malangdowarp1007	1,1,mal_in02.gat,101,89
mal_in02.gat,102,87,0	warp	malangdowarp1008	1,1,mal_in02.gat,101,64
mal_in02.gat,137,66,0	warp	malangdowarp1009	1,1,mal_in02.gat,139,89
mal_in02.gat,140,87,0	warp	malangdowarp1010	1,1,mal_in02.gat,137,64
mal_in02.gat,63,53,0	warp	malangdowarp1011	1,1,mal_in02.gat,63,33
mal_in02.gat,63,35,0	warp	malangdowarp1012	1,1,mal_in02.gat,64,55
mal_in02.gat,101,53,0	warp	malangdowarp1013	1,1,mal_in02.gat,101,33
mal_in02.gat,101,35,0	warp	malangdowarp1014	1,1,mal_in02.gat,102,55
mal_in02.gat,137,53,0	warp	malangdowarp1015	1,1,mal_in02.gat,139,33
mal_in02.gat,139,35,0	warp	malangdowarp1016	1,1,mal_in02.gat,138,55
mal_in02.gat,142,60,0	warp	malangdowarp1017	1,1,mal_in02.gat,162,61
mal_in02.gat,159,61,0	warp	malangdowarp1018	1,1,mal_in02.gat,140,59
//西の家
malangdo.gat,112,167,0	warp	malangdowarp1019	1,1,mal_in01.gat,17,163
mal_in01.gat,18,161,0	warp	malangdowarp1020	1,1,malangdo.gat,115,166
mal_in01.gat,18,173,0	warp	malangdowarp1021	1,1,mal_in01.gat,72,173
mal_in01.gat,75,174,0	warp	malangdowarp1022	1,1,mal_in01.gat,18,171
mal_in01.gat,73,170,0	warp	malangdowarp1023	1,1,mal_in01.gat,124,172
mal_in01.gat,124,175,0	warp	malangdowarp1024	1,1,mal_in01.gat,70,170
//民家
malangdo.gat,113,151,0	warp	malangdowarp1025	1,1,mal_in01.gat,28,118
mal_in01.gat,30,119,0	warp	malangdowarp1026	1,1,malangdo.gat,115,150
mal_in01.gat,20,119,0	warp	malangdowarp1027	1,1,mal_in01.gat,65,117
mal_in01.gat,67,118,0	warp	malangdowarp1028	1,1,mal_in01.gat,21,117
//旅館
malangdo.gat,135,109,0	warp	malangdowarp1029	1,1,mal_in01.gat,19,76
mal_in01.gat,18,78,0	warp	malangdowarp1030	1,1,malangdo.gat,135,111
mal_in01.gat,18,67,0	warp	malangdowarp1031	1,1,mal_in01.gat,65,65
mal_in01.gat,67,66,0	warp	malangdowarp1032	1,1,mal_in01.gat,20,67
//道具屋
malangdo.gat,240,150,0	warp	malangdowarp1033	1,1,mal_in01.gat,11,17
mal_in01.gat,9,16,0		warp	malangdowarp1034	1,1,malangdo.gat,238,149
mal_in01.gat,20,15,0	warp	malangdowarp1035	1,1,mal_in01.gat,65,11
mal_in01.gat,67,12,0	warp	malangdowarp1036	1,1,mal_in01.gat,20,13



//---ポートマラヤ追加マップ


//==============================================================
// -----  ポートマラヤ -----
// malaya.gat		ポートマラヤ
// ma_in01.gat		ポートマラヤ 室内
// ma_in01_jp.gat	ポートマラヤ 室内
// -----
// ma_fild01.gat	バリオ・マヒワガ
//==============================================================
//ポートマラヤ⇒バリオ・マヒワガ
malaya.gat,370,277,0	warp	malayawarp0501	1,1,ma_fild01.gat,40,272
//ポートマラヤ 室内⇒バリオ・マヒワガ
ma_in01.gat,105,160,0	warp	malayawarp0502	1,1,ma_fild01.gat,248,190
ma_in01_jp.gat,86,17,0	warp	malayawarp0503	1,1,ma_fild01.gat,162,221
ma_in01_jp.gat,33,152,0	warp	malayawarp0504	1,1,ma_fild01.gat,257,212

//旅館
ma_in01.gat,24,77,0		warp	malayawarp1001	1,1,malaya.gat,178,208
//武器屋
ma_in01.gat,86,16,0		warp	malayawarp1002	1,1,malaya.gat,115,212
//道具屋
ma_in01.gat,9,24,0		warp	malayawarp1003	1,1,malaya.gat,296,167
//商家
ma_in01.gat,126,17,0	warp	malayawarp1004	1,1,malaya.gat,261,237
//民家
ma_in01.gat,33,152,0	warp	malayawarp1005	1,1,malaya.gat,296,210
//ペリー号
ma_in01.gat,105,92,0	warp	malayawarp1006	1,1,malaya.gat,310,67



//---エクラージュ追加マップ


//==============================================================
// -----  エクラージュ -----
// eclage.gat		ラフィネ族の首都 エクラージュ
// ecl_in01.gat		エクラージュ 内部
// ecl_in02.gat		エクラージュ 内部
// ecl_in03.gat		エクラージュ 内部
// ecl_hub01.gat	エクラージュ通路
//==============================================================
//エクラージュ⇔エクラージュ 内部
eclage.gat,299,309,0	warp	eclagewarp1001	1,1,ecl_in01.gat,47,11
ecl_in01.gat,47,8,0		warp	eclagewarp1002	1,1,eclage.gat,297,307

//エクラージュ 内部
ecl_in01.gat,8,67,0		warp	eclagewarp1003	1,1,ecl_hub01.gat,38,94
ecl_hub01.gat,40,95,0	warp	eclagewarp1004	1,1,ecl_in01.gat,11,67
ecl_hub01.gat,22,109,0	warp	eclagewarp1005	1,1,ecl_in02.gat,99,7
ecl_in02.gat,98,4,0		warp	eclagewarp1006	1,1,ecl_hub01.gat,23,107
ecl_in02.gat,80,18,0	warp	eclagewarp1007	1,1,ecl_in02.gat,157,66
ecl_in02.gat,157,68,0	warp	eclagewarp1008	1,1,ecl_in02.gat,83,18
ecl_in01.gat,84,68,0	warp	eclagewarp1009	1,1,ecl_hub01.gat,107,107
ecl_hub01.gat,107,110,0	warp	eclagewarp1010	1,1,ecl_in01.gat,82,68
ecl_hub01.gat,127,95,0	warp	eclagewarp1011	1,1,ecl_hub01.gat,18,32
ecl_hub01.gat,18,34,0	warp	eclagewarp1012	1,1,ecl_hub01.gat,125,94
ecl_hub01.gat,40,14,0	warp	eclagewarp1013	1,1,ecl_in03.gat,144,17
ecl_in03.gat,144,14,0	warp	eclagewarp1014	1,1,ecl_hub01.gat,40,11
ecl_hub01.gat,105,36,0	warp	eclagewarp1015	1,1,ecl_in01.gat,82,68
ecl_in01.gat,138,17,0	warp	eclagewarp1016	1,1,ecl_hub01.gat,18,32



//---ラザーニャ追加マップ


//==============================================================
// -----  ラザーニャ -----
// lasagna.gat		港町ラザーニャ
// conch_in.gat		コンキリエ号
// -----
// lasa_fild01.gat	ラビオル平原 01
// lasa_fild02.gat	ラビオル森 01
//==============================================================
//港町ラザーニャ⇒ラビオル平原 01
lasagna.gat,150,54,0	warp	lasagnawarp0501	2,2,lasa_fild01.gat,131,378
lasagna.gat,327,51,0	warp	lasagnawarp0502	2,2,lasa_fild01.gat,344,371
//港町ラザーニャ⇒ラビオル森 01
lasagna.gat,358,91,0	warp	lasagnawarp0503	2,2,lasa_fild02.gat,20,98

//港町ラザーニャ⇔コンキリエ号
lasagna.gat,205,327,0	warp	lasagnawarp1001	2,2,conch_in.gat,55,61
conch_in.gat,59,62,0	warp	lasagnawarp1002	2,2,lasagna.gat,205,324

//コンキリエ号
conch_in.gat,50,60,0	warp	lasagnawarp1003	2,2,conch_in.gat,30,60
conch_in.gat,36,60,0	warp	lasagnawarp1004	2,2,conch_in.gat,54,60
conch_in.gat,143,60,0	warp	lasagnawarp1005	2,2,conch_in.gat,165,60
conch_in.gat,159,60,0	warp	lasagnawarp1006	2,2,conch_in.gat,138,60



//---ロックリッジ追加マップ


//==============================================================
// -----  ロックリッジ -----
// harboro1.gat		ロックリッジ
// har_in01.gat		ロックリッジ 室内
//==============================================================
//ロックリッジ⇔保安官事務室
harboro1.gat,241,218,0	warp	rockwarp1001	1,1,har_in01.gat,18,18
har_in01.gat,18,15,0	warp	rockwarp1002	1,1,harboro1.gat,241,215

//ロックリッジ⇔道具屋
harboro1.gat,312,193,0	warp	rockwarp1003	1,1,har_in01.gat,26,87
har_in01.gat,26,90,0	warp	rockwarp1004	1,1,harboro1.gat,312,197
