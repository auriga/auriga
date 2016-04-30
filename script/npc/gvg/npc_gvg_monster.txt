//=========================================================================
// エンペリウムおよびモンスター召喚ファンクション
// （攻城戦開始時・アジト放棄時・エンペ破壊時に呼び出される）
//	callfunc "AgitSummon","AgitCode";
//-------------------------------------------------------------------------

function	script	AgitSummon	{
	//AgitCodeを数値に変換する関数を設定
	function enum {
		if(getarg(0)=="L1") return 11;
		if(getarg(0)=="L2") return 12;
		if(getarg(0)=="L3") return 13;
		if(getarg(0)=="L4") return 14;
		if(getarg(0)=="L5") return 15;
		if(getarg(0)=="B1") return 21;
		if(getarg(0)=="B2") return 22;
		if(getarg(0)=="B3") return 23;
		if(getarg(0)=="B4") return 24;
		if(getarg(0)=="B5") return 25;
		if(getarg(0)=="C1") return 31;
		if(getarg(0)=="C2") return 32;
		if(getarg(0)=="C3") return 33;
		if(getarg(0)=="C4") return 34;
		if(getarg(0)=="C5") return 35;
		if(getarg(0)=="V1") return 41;
		if(getarg(0)=="V2") return 42;
		if(getarg(0)=="V3") return 43;
		if(getarg(0)=="V4") return 44;
		if(getarg(0)=="V5") return 45;
		return 0;
	}

	//エンペリウムの召喚
	switch (enum(getarg(0))) {
		case 11: monster "aldeg_cas01.gat",216,24,"エンペリウム",1288,1,"AgitExe#L1::OnAgitBreak"; 	break;
		case 12: monster "aldeg_cas02.gat",214,24,"エンペリウム",1288,1,"AgitExe#L2::OnAgitBreak"; 	break;
		case 13: monster "aldeg_cas03.gat",206,32,"エンペリウム",1288,1,"AgitExe#L3::OnAgitBreak"; 	break;
		case 14: monster "aldeg_cas04.gat",36,218,"エンペリウム",1288,1,"AgitExe#L4::OnAgitBreak"; 	break;
		case 15: monster "aldeg_cas05.gat",28,102,"エンペリウム",1288,1,"AgitExe#L5::OnAgitBreak"; 	break;
		case 21: monster "gefg_cas01.gat",198,182,"エンペリウム",1288,1,"AgitExe#B1::OnAgitBreak"; 	break;
		case 22: monster "gefg_cas02.gat",176,178,"エンペリウム",1288,1,"AgitExe#B2::OnAgitBreak"; 	break;
		case 23: monster "gefg_cas03.gat",245,167,"エンペリウム",1288,1,"AgitExe#B3::OnAgitBreak"; 	break;
		case 24: monster "gefg_cas04.gat",174,178,"エンペリウム",1288,1,"AgitExe#B4::OnAgitBreak"; 	break;
		case 25: monster "gefg_cas05.gat",194,184,"エンペリウム",1288,1,"AgitExe#B5::OnAgitBreak"; 	break;
		case 31: monster "payg_cas01.gat",139,139,"エンペリウム",1288,1,"AgitExe#C1::OnAgitBreak"; 	break;
		case 32: monster "payg_cas02.gat",39,25,"エンペリウム",1288,1,"AgitExe#C2::OnAgitBreak"; 	break;
		case 33: monster "payg_cas03.gat",269,265,"エンペリウム",1288,1,"AgitExe#C3::OnAgitBreak"; 	break;
		case 34: monster "payg_cas04.gat",271,29,"エンペリウム",1288,1,"AgitExe#C4::OnAgitBreak"; 	break;
		case 35: monster "payg_cas05.gat",30,30,"エンペリウム",1288,1,"AgitExe#C5::OnAgitBreak"; 	break;
		case 41: monster "prtg_cas01.gat",197,197,"エンペリウム",1288,1,"AgitExe#V1::OnAgitBreak"; 	break;
		case 42: monster "prtg_cas02.gat",158,174,"エンペリウム",1288,1,"AgitExe#V2::OnAgitBreak"; 	break;
		case 43: monster "prtg_cas03.gat",17,221,"エンペリウム",1288,1,"AgitExe#V3::OnAgitBreak"; 	break;
		case 44: monster "prtg_cas04.gat",292,14,"エンペリウム",1288,1,"AgitExe#V4::OnAgitBreak"; 	break;
		case 45: monster "prtg_cas05.gat",266,266,"エンペリウム",1288,1,"AgitExe#V5::OnAgitBreak"; 	break;
	}
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if(getcastledata('@map$,1))
		return;					//城主ギルドが居るならこれで終了

	//各砦におけるモンスター出現座標の設定
	switch (enum(getarg(0))) {
		case 11: setarray '@pos,216,23; 	break;
		case 12: setarray '@pos,213,23; 	break;
		case 13: setarray '@pos,205,31; 	break;
		case 14: setarray '@pos,36,217; 	break;
		case 15: setarray '@pos,27,101; 	break;
		case 21: setarray '@pos,197,181; 	break;
		case 22: setarray '@pos,176,178; 	break;
		case 23: setarray '@pos,244,166; 	break;
		case 24: setarray '@pos,174,177; 	break;
		case 25: setarray '@pos,194,184; 	break;
		case 31: setarray '@pos,138,138; 	break;
		case 32: setarray '@pos,38,25; 		break;
		case 33: setarray '@pos,268,264; 	break;
		case 34: setarray '@pos,270,28; 	break;
		case 35: setarray '@pos,30,30; 		break;
		case 41: setarray '@pos,197,197; 	break;
		case 42: setarray '@pos,157,174; 	break;
		case 43: setarray '@pos,16,220; 	break;
		case 44: setarray '@pos,291,14; 	break;
		case 45: setarray '@pos,266,266; 	break;
	}
	//城主ギルド不在時のモンスターの召喚
	switch (enum(getarg(0))/10) {
	case 1:	//ルイーナ
		areamonster '@map$,0,0,0,0,"イビルドルイド",1117,10;
		areamonster '@map$,0,0,0,0,"カーリッツバーグ",1132,4;
		areamonster '@map$,0,0,0,0,"深淵の騎士",1219,2;
		areamonster '@map$,0,0,0,0,"エクスキューショナー",1205,1;
		areamonster '@map$,0,0,0,0,"ペノメナ",1216,10;
		areamonster '@map$,0,0,0,0,"アラーム",1193,17;
		areamonster '@map$,0,0,0,0,"クロック",1269,9;
		areamonster '@map$,0,0,0,0,"レイドリックアーチャー",1276,7;
		areamonster '@map$,0,0,0,0,"彷徨う者",1208,3;
		areamonster '@map$,0,0,0,0,"アリス",1275,1;
		areamonster '@map$,0,0,0,0,"ブラッディナイト",1268,1;
		areamonster '@map$,0,0,0,0,"ダークロード",1272,1;
		monster '@map$,'@pos[0],'@pos[1],"ダークロード",1272,1;
		monster '@map$,'@pos[0],'@pos[1],"時計塔管理者",1270,4;
		monster '@map$,'@pos[0],'@pos[1],"ブラッディナイト",1268,1;
		monster '@map$,'@pos[0],'@pos[1],"深淵の騎士",1219,1;
		monster '@map$,'@pos[0],'@pos[1],"レイドリックアーチャー",1276,5;
		break;
	case 2:	//ブリトニア
		areamonster '@map$,0,0,0,0,"イビルドルイド",1117,10;
		areamonster '@map$,0,0,0,0,"ウィンドゴースト",1263,11;
		areamonster '@map$,0,0,0,0,"バースリー",1102,10;
		areamonster '@map$,0,0,0,0,"ジャック",1130,10;
		areamonster '@map$,0,0,0,0,"マルドゥーク",1140,20;
		areamonster '@map$,0,0,0,0,"レイドリック",1163,9;
		areamonster '@map$,0,0,0,0,"アリス",1275,1;
		areamonster '@map$,0,0,0,0,"深淵の騎士",1219,1;
		areamonster '@map$,0,0,0,0,"月夜花",1150,1;
		areamonster '@map$,0,0,0,0,"フリオニ",1159,1;
		monster '@map$,'@pos[0],'@pos[1],"ミステルテイン",1203,1;
		monster '@map$,'@pos[0],'@pos[1],"オークヒーロー",1087,1;
		monster '@map$,'@pos[0],'@pos[1],"ハイオーク",1213,10;
		monster '@map$,'@pos[0],'@pos[1],"オークアーチャー",1189,10;
		break;
	case 3:	//チュンリム
		areamonster '@map$,0,0,0,0,"天下大将軍",1277,10;
		areamonster '@map$,0,0,0,0,"彷徨う者",1208,10;
		areamonster '@map$,0,0,0,0,"ミュータントドラゴン",1262,5;
		areamonster '@map$,0,0,0,0,"バースリー",1102,5;
		areamonster '@map$,0,0,0,0,"月夜花",1150,1;
		areamonster '@map$,0,0,0,0,"エドガ",1115,1;
		areamonster '@map$,0,0,0,0,"ホロン",1129,11;
		areamonster '@map$,0,0,0,0,"レイドリックアーチャー",1276,5;
		areamonster '@map$,0,0,0,0,"コボルドアーチャー",1282,4;
		areamonster '@map$,0,0,0,0,"ガーゴイル",1253,5;
		monster '@map$,'@pos[0],'@pos[1],"月夜花",1150,1;
		monster '@map$,'@pos[0],'@pos[1],"エドガ",1115,1;
		monster '@map$,'@pos[0],'@pos[1],"彷徨う者",1208,6;
		monster '@map$,'@pos[0],'@pos[1],"レイドリックアーチャー",1276,5;
		break;
	case 4:	//ヴァルキリーレルム
		areamonster '@map$,0,0,0,0,"レイドリック",1163,15;
		areamonster '@map$,0,0,0,0,"カーリッツバーグ",1132,10;
		areamonster '@map$,0,0,0,0,"深淵の騎士",1219,5;
		areamonster '@map$,0,0,0,0,"ブラッディナイト",1268,5;
		areamonster '@map$,0,0,0,0,"ストームナイト",1251,1;
		areamonster '@map$,0,0,0,0,"ハティー",1252,1;
		areamonster '@map$,0,0,0,0,"レイドリックアーチャー",1276,5;
		areamonster '@map$,0,0,0,0,"グリフォン",1259,2;
		areamonster '@map$,0,0,0,0,"キメラ",1283,2;
		areamonster '@map$,0,0,0,0,"アリス",1275,1;
		areamonster '@map$,0,0,0,0,"ジルタス",1200,1;
		monster '@map$,'@pos[0],'@pos[1],"ブラッディナイト",1268,1;
		monster '@map$,'@pos[0],'@pos[1],"ストームナイト",1251,1;
		monster '@map$,'@pos[0],'@pos[1],"ハティー",1252,1;
		monster '@map$,'@pos[0],'@pos[1],"深淵の騎士",1219,2;
		monster '@map$,'@pos[0],'@pos[1],"レイドリックアーチャー",1276,5;
		break;
	}
	return;
}


//=========================================================================
// ガーディアン召喚ファンクション
// （Interサーバ接続時もしくは執事による召喚で呼び出される）
//	callfunc "GuardianCall","AgitCode",Num,Mes;
//
// ■ 引数の詳細
//	"AgitCode" -> アジトを示すコード（例：L1,B2,C3,V4）
//	    Num    -> 召喚するガーディアンの番号、10～17
//	    Mes    -> 0:メッセージなし、1:メッセージあり（執事のとき）
//-------------------------------------------------------------------------

function	script	GuardianCall	{
	if(getarg(0)=="L1") {
		switch(getarg(1)) {
			case 10: monster "aldeg_cas01.gat",17,218,"--ja--",1287,1,"#GuardianKilled::On_L1_10"; 	break;
			case 11: monster "aldeg_cas01.gat",39,205,"--ja--",1285,1,"#GuardianKilled::On_L1_11"; 	break;
			case 12: monster "aldeg_cas01.gat",38,196,"--ja--",1285,1,"#GuardianKilled::On_L1_12"; 	break;
			case 13: monster "aldeg_cas01.gat",21,194,"--ja--",1286,1,"#GuardianKilled::On_L1_13"; 	break;
			case 14: monster "aldeg_cas01.gat",218,24,"--ja--",1286,1,"#GuardianKilled::On_L1_14"; 	break;
			case 15: monster "aldeg_cas01.gat",213,24,"--ja--",1286,1,"#GuardianKilled::On_L1_15"; 	break;
			case 16: monster "aldeg_cas01.gat",73,70,"--ja--",1286,1,"#GuardianKilled::On_L1_16"; 	break;
			case 17: monster "aldeg_cas01.gat",45,228,"--ja--",1285,1,"#GuardianKilled::On_L1_17"; 	break;
		}
	}
	if(getarg(0)=="L2") {
		switch(getarg(1)) {
			case 10: monster "aldeg_cas02.gat",51,183,"--ja--",1287,1,"#GuardianKilled::On_L2_10"; 	break;
			case 11: monster "aldeg_cas02.gat",27,184,"--ja--",1286,1,"#GuardianKilled::On_L2_11"; 	break;
			case 12: monster "aldeg_cas02.gat",88,43,"--ja--",1286,1,"#GuardianKilled::On_L2_12"; 	break;
			case 13: monster "aldeg_cas02.gat",210,7,"--ja--",1285,1,"#GuardianKilled::On_L2_13"; 	break;
			case 14: monster "aldeg_cas02.gat",60,203,"--ja--",1287,1,"#GuardianKilled::On_L2_14"; 	break;
			case 15: monster "aldeg_cas02.gat",21,177,"--ja--",1285,1,"#GuardianKilled::On_L2_15"; 	break;
			case 16: monster "aldeg_cas02.gat",117,46,"--ja--",1286,1,"#GuardianKilled::On_L2_16"; 	break;
			case 17: monster "aldeg_cas02.gat",36,183,"--ja--",1285,1,"#GuardianKilled::On_L2_17"; 	break;
		}
	}
	if(getarg(0)=="L3") {
		switch(getarg(1)) {
			case 10: monster "aldeg_cas03.gat",110,217,"--ja--",1285,1,"#GuardianKilled::On_L3_10"; break;
			case 11: monster "aldeg_cas03.gat",90,112,"--ja--",1286,1,"#GuardianKilled::On_L3_11"; 	break;
			case 12: monster "aldeg_cas03.gat",86,120,"--ja--",1287,1,"#GuardianKilled::On_L3_12"; 	break;
			case 13: monster "aldeg_cas03.gat",195,151,"--ja--",1285,1,"#GuardianKilled::On_L3_13"; break;
			case 14: monster "aldeg_cas03.gat",116,112,"--ja--",1286,1,"#GuardianKilled::On_L3_14"; break;
			case 15: monster "aldeg_cas03.gat",116,76,"--ja--",1287,1,"#GuardianKilled::On_L3_15"; 	break;
			case 16: monster "aldeg_cas03.gat",64,103,"--ja--",1287,1,"#GuardianKilled::On_L3_16"; 	break;
			case 17: monster "aldeg_cas03.gat",212,160,"--ja--",1285,1,"#GuardianKilled::On_L3_17"; break;
		}
	}
	if(getarg(0)=="L4") {
		switch(getarg(1)) {
			case 10: monster "aldeg_cas04.gat",187,100,"--ja--",1285,1,"#GuardianKilled::On_L4_10"; break;
			case 11: monster "aldeg_cas04.gat",192,42,"--ja--",1285,1,"#GuardianKilled::On_L4_11"; 	break;
			case 12: monster "aldeg_cas04.gat",55,88,"--ja--",1286,1,"#GuardianKilled::On_L4_12"; 	break;
			case 13: monster "aldeg_cas04.gat",145,209,"--ja--",1287,1,"#GuardianKilled::On_L4_13"; break;
			case 14: monster "aldeg_cas04.gat",169,53,"--ja--",1287,1,"#GuardianKilled::On_L4_14"; 	break;
			case 15: monster "aldeg_cas04.gat",198,77,"--ja--",1287,1,"#GuardianKilled::On_L4_15"; 	break;
			case 16: monster "aldeg_cas04.gat",148,88,"--ja--",1285,1,"#GuardianKilled::On_L4_16"; 	break;
			case 17: monster "aldeg_cas04.gat",48,72,"--ja--",1286,1,"#GuardianKilled::On_L4_17"; 	break;
		}
	}
	if(getarg(0)=="L5") {
		switch(getarg(1)) {
			case 10: monster "aldeg_cas05.gat",51,202,"--ja--",1285,1,"#GuardianKilled::On_L5_10"; 	break;
			case 11: monster "aldeg_cas05.gat",27,221,"--ja--",1286,1,"#GuardianKilled::On_L5_11"; 	break;
			case 12: monster "aldeg_cas05.gat",145,78,"--ja--",1286,1,"#GuardianKilled::On_L5_12"; 	break;
			case 13: monster "aldeg_cas05.gat",157,192,"--ja--",1287,1,"#GuardianKilled::On_L5_13"; break;
			case 14: monster "aldeg_cas05.gat",157,74,"--ja--",1287,1,"#GuardianKilled::On_L5_14"; 	break;
			case 15: monster "aldeg_cas05.gat",188,79,"--ja--",1285,1,"#GuardianKilled::On_L5_15"; 	break;
			case 16: monster "aldeg_cas05.gat",156,73,"--ja--",1286,1,"#GuardianKilled::On_L5_16"; 	break;
			case 17: monster "aldeg_cas05.gat",41,112,"--ja--",1286,1,"#GuardianKilled::On_L5_17"; 	break;
		}
	}
	if(getarg(0)=="B1") {
		switch(getarg(1)) {
			case 10: monster "gefg_cas01.gat",67,179,"--ja--",1287,1,"#GuardianKilled::On_B1_10"; 	break;
			case 11: monster "gefg_cas01.gat",36,186,"--ja--",1285,1,"#GuardianKilled::On_B1_11"; 	break;
			case 12: monster "gefg_cas01.gat",50,186,"--ja--",1285,1,"#GuardianKilled::On_B1_12"; 	break;
			case 13: monster "gefg_cas01.gat",62,41,"--ja--",1287,1,"#GuardianKilled::On_B1_13"; 	break;
			case 14: monster "gefg_cas01.gat",50,67,"--ja--",1286,1,"#GuardianKilled::On_B1_14"; 	break;
			case 15: monster "gefg_cas01.gat",184,20,"--ja--",1287,1,"#GuardianKilled::On_B1_15"; 	break;
			case 16: monster "gefg_cas01.gat",189,41,"--ja--",1286,1,"#GuardianKilled::On_B1_16"; 	break;
			case 17: monster "gefg_cas01.gat",200,167,"--ja--",1286,1,"#GuardianKilled::On_B1_17"; 	break;
		}
	}
	if(getarg(0)=="B2") {
		switch(getarg(1)) {
			case 10: monster "gefg_cas02.gat",64,168,"--ja--",1287,1,"#GuardianKilled::On_B2_10"; 	break;
			case 11: monster "gefg_cas02.gat",35,148,"--ja--",1285,1,"#GuardianKilled::On_B2_11"; 	break;
			case 12: monster "gefg_cas02.gat",20,150,"--ja--",1285,1,"#GuardianKilled::On_B2_12"; 	break;
			case 13: monster "gefg_cas02.gat",56,41,"--ja--",1287,1,"#GuardianKilled::On_B2_13"; 	break;
			case 14: monster "gefg_cas02.gat",19,41,"--ja--",1286,1,"#GuardianKilled::On_B2_14"; 	break;
			case 15: monster "gefg_cas02.gat",166,25,"--ja--",1287,1,"#GuardianKilled::On_B2_15"; 	break;
			case 16: monster "gefg_cas02.gat",166,42,"--ja--",1286,1,"#GuardianKilled::On_B2_16"; 	break;
			case 17: monster "gefg_cas02.gat",159,188,"--ja--",1286,1,"#GuardianKilled::On_B2_17"; 	break;
		}
	}
	if(getarg(0)=="B3") {
		switch(getarg(1)) {
			case 10: monster "gefg_cas03.gat",48,176,"--ja--",1285,1,"#GuardianKilled::On_B3_10"; 	break;
			case 11: monster "gefg_cas03.gat",113,214,"--ja--",1285,1,"#GuardianKilled::On_B3_11"; 	break;
			case 12: monster "gefg_cas03.gat",48,207,"--ja--",1287,1,"#GuardianKilled::On_B3_12"; 	break;
			case 13: monster "gefg_cas03.gat",157,62,"--ja--",1287,1,"#GuardianKilled::On_B3_13"; 	break;
			case 14: monster "gefg_cas03.gat",157,45,"--ja--",1286,1,"#GuardianKilled::On_B3_14"; 	break;
			case 15: monster "gefg_cas03.gat",243,41,"--ja--",1287,1,"#GuardianKilled::On_B3_15"; 	break;
			case 16: monster "gefg_cas03.gat",234,25,"--ja--",1286,1,"#GuardianKilled::On_B3_16"; 	break;
			case 17: monster "gefg_cas03.gat",238,160,"--ja--",1286,1,"#GuardianKilled::On_B3_17"; 	break;
		}
	}
	if(getarg(0)=="B4") {
		switch(getarg(1)) {
			case 10: monster "gefg_cas04.gat",53,191,"--ja--",1285,1,"#GuardianKilled::On_B4_10"; 	break;
			case 11: monster "gefg_cas04.gat",31,178,"--ja--",1285,1,"#GuardianKilled::On_B4_11"; 	break;
			case 12: monster "gefg_cas04.gat",49,220,"--ja--",1287,1,"#GuardianKilled::On_B4_12"; 	break;
			case 13: monster "gefg_cas04.gat",29,46,"--ja--",1287,1,"#GuardianKilled::On_B4_13"; 	break;
			case 14: monster "gefg_cas04.gat",57,46,"--ja--",1286,1,"#GuardianKilled::On_B4_14"; 	break;
			case 15: monster "gefg_cas04.gat",147,65,"--ja--",1287,1,"#GuardianKilled::On_B4_15"; 	break;
			case 16: monster "gefg_cas04.gat",160,50,"--ja--",1286,1,"#GuardianKilled::On_B4_16"; 	break;
			case 17: monster "gefg_cas04.gat",148,189,"--ja--",1286,1,"#GuardianKilled::On_B4_17"; 	break;
		}
	}
	if(getarg(0)=="B5") {
		switch(getarg(1)) {
			case 10: monster "gefg_cas05.gat",45,149,"--ja--",1285,1,"#GuardianKilled::On_B5_10"; 	break;
			case 11: monster "gefg_cas05.gat",71,163,"--ja--",1285,1,"#GuardianKilled::On_B5_11"; 	break;
			case 12: monster "gefg_cas05.gat",72,142,"--ja--",1287,1,"#GuardianKilled::On_B5_12"; 	break;
			case 13: monster "gefg_cas05.gat",66,47,"--ja--",1287,1,"#GuardianKilled::On_B5_13"; 	break;
			case 14: monster "gefg_cas05.gat",66,17,"--ja--",1286,1,"#GuardianKilled::On_B5_14"; 	break;
			case 15: monster "gefg_cas05.gat",177,50,"--ja--",1287,1,"#GuardianKilled::On_B5_15"; 	break;
			case 16: monster "gefg_cas05.gat",177,35,"--ja--",1286,1,"#GuardianKilled::On_B5_16"; 	break;
			case 17: monster "gefg_cas05.gat",193,166,"--ja--",1286,1,"#GuardianKilled::On_B5_17"; 	break;
		}
	}
	if(getarg(0)=="C1") {
		switch(getarg(1)) {
			case 10: monster "payg_cas01.gat",229,92,"--ja--",1285,1,"#GuardianKilled::On_C1_10"; 	break;
			case 11: monster "payg_cas01.gat",225,80,"--ja--",1285,1,"#GuardianKilled::On_C1_11"; 	break;
			case 12: monster "payg_cas01.gat",222,111,"--ja--",1285,1,"#GuardianKilled::On_C1_12"; 	break;
			case 13: monster "payg_cas01.gat",99,45,"--ja--",1285,1,"#GuardianKilled::On_C1_13"; 	break;
			case 14: monster "payg_cas01.gat",65,31,"--ja--",1285,1,"#GuardianKilled::On_C1_14"; 	break;
			case 15: monster "payg_cas01.gat",36,127,"--ja--",1285,1,"#GuardianKilled::On_C1_15"; 	break;
			case 16: monster "payg_cas01.gat",51,144,"--ja--",1285,1,"#GuardianKilled::On_C1_16"; 	break;
			case 17: monster "payg_cas01.gat",138,133,"--ja--",1286,1,"#GuardianKilled::On_C1_17"; 	break;
		}
	}
	if(getarg(0)=="C2") {
		switch(getarg(1)) {
			case 10: monster "payg_cas02.gat",237,54,"--ja--",1285,1,"#GuardianKilled::On_C2_10"; 	break;
			case 11: monster "payg_cas02.gat",228,72,"--ja--",1285,1,"#GuardianKilled::On_C2_11"; 	break;
			case 12: monster "payg_cas02.gat",210,41,"--ja--",1285,1,"#GuardianKilled::On_C2_12"; 	break;
			case 13: monster "payg_cas02.gat",57,241,"--ja--",1285,1,"#GuardianKilled::On_C2_13"; 	break;
			case 14: monster "payg_cas02.gat",42,241,"--ja--",1285,1,"#GuardianKilled::On_C2_14"; 	break;
			case 15: monster "payg_cas02.gat",287,257,"--ja--",1285,1,"#GuardianKilled::On_C2_15"; 	break;
			case 16: monster "payg_cas02.gat",264,272,"--ja--",1285,1,"#GuardianKilled::On_C2_16"; 	break;
			case 17: monster "payg_cas02.gat",27,20,"--ja--",1286,1,"#GuardianKilled::On_C2_17"; 	break;
		}
	}
	if(getarg(0)=="C3") {
		switch(getarg(1)) {
			case 10: monster "payg_cas03.gat",245,37,"--ja--",1285,1,"#GuardianKilled::On_C3_10"; 	break;
			case 11: monster "payg_cas03.gat",269,51,"--ja--",1285,1,"#GuardianKilled::On_C3_11"; 	break;
			case 12: monster "payg_cas03.gat",36,39,"--ja--",1285,1,"#GuardianKilled::On_C3_12"; 	break;
			case 13: monster "payg_cas03.gat",41,39,"--ja--",1285,1,"#GuardianKilled::On_C3_13"; 	break;
			case 14: monster "payg_cas03.gat",39,65,"--ja--",1285,1,"#GuardianKilled::On_C3_14"; 	break;
			case 15: monster "payg_cas03.gat",19,276,"--ja--",1285,1,"#GuardianKilled::On_C3_15"; 	break;
			case 16: monster "payg_cas03.gat",37,277,"--ja--",1285,1,"#GuardianKilled::On_C3_16"; 	break;
			case 17: monster "payg_cas03.gat",268,244,"--ja--",1286,1,"#GuardianKilled::On_C3_17"; 	break;
		}
	}
	if(getarg(0)=="C4") {
		switch(getarg(1)) {
			case 10: monster "payg_cas04.gat",251,212,"--ja--",1285,1,"#GuardianKilled::On_C4_10"; 	break;
			case 11: monster "payg_cas04.gat",232,212,"--ja--",1285,1,"#GuardianKilled::On_C4_11"; 	break;
			case 12: monster "payg_cas04.gat",231,175,"--ja--",1285,1,"#GuardianKilled::On_C4_12"; 	break;
			case 13: monster "payg_cas04.gat",32,287,"--ja--",1285,1,"#GuardianKilled::On_C4_13"; 	break;
			case 14: monster "payg_cas04.gat",32,232,"--ja--",1285,1,"#GuardianKilled::On_C4_14"; 	break;
			case 15: monster "payg_cas04.gat",35,45,"--ja--",1285,1,"#GuardianKilled::On_C4_15"; 	break;
			case 16: monster "payg_cas04.gat",36,17,"--ja--",1285,1,"#GuardianKilled::On_C4_16"; 	break;
			case 17: monster "payg_cas04.gat",270,41,"--ja--",1286,1,"#GuardianKilled::On_C4_17"; 	break;
		}
	}
	if(getarg(0)=="C5") {
		switch(getarg(1)) {
			case 10: monster "payg_cas05.gat",19,279,"--ja--",1285,1,"#GuardianKilled::On_C5_10"; 	break;
			case 11: monster "payg_cas05.gat",33,260,"--ja--",1285,1,"#GuardianKilled::On_C5_11"; 	break;
			case 12: monster "payg_cas05.gat",266,234,"--ja--",1285,1,"#GuardianKilled::On_C5_12"; 	break;
			case 13: monster "payg_cas05.gat",266,279,"--ja--",1285,1,"#GuardianKilled::On_C5_13"; 	break;
			case 14: monster "payg_cas05.gat",263,37,"--ja--",1285,1,"#GuardianKilled::On_C5_14"; 	break;
			case 15: monster "payg_cas05.gat",263,21,"--ja--",1285,1,"#GuardianKilled::On_C5_15"; 	break;
			case 16: monster "payg_cas05.gat",250,22,"--ja--",1285,1,"#GuardianKilled::On_C5_16"; 	break;
			case 17: monster "payg_cas05.gat",36,36,"--ja--",1286,1,"#GuardianKilled::On_C5_17"; 	break;
		}
	}
	if(getarg(0)=="V1") {
		switch(getarg(1)) {
			case 10: monster "prtg_cas01.gat",182,68,"--ja--",1287,1,"#GuardianKilled::On_V1_10"; 	break;
			case 11: monster "prtg_cas01.gat",182,116,"--ja--",1287,1,"#GuardianKilled::On_V1_11"; 	break;
			case 12: monster "prtg_cas01.gat",153,86,"--ja--",1287,1,"#GuardianKilled::On_V1_12"; 	break;
			case 13: monster "prtg_cas01.gat",59,28,"--ja--",1285,1,"#GuardianKilled::On_V1_13"; 	break;
			case 14: monster "prtg_cas01.gat",50,36,"--ja--",1285,1,"#GuardianKilled::On_V1_14"; 	break;
			case 15: monster "prtg_cas01.gat",184,183,"--ja--",1286,1,"#GuardianKilled::On_V1_15"; 	break;
			case 16: monster "prtg_cas01.gat",196,189,"--ja--",1286,1,"#GuardianKilled::On_V1_16"; 	break;
			case 17: monster "prtg_cas01.gat",107,179,"--ja--",1286,1,"#GuardianKilled::On_V1_17"; 	break;
		}
	}
	if(getarg(0)=="V2") {
		switch(getarg(1)) {
			case 10: monster "prtg_cas02.gat",188,175,"--ja--",1286,1,"#GuardianKilled::On_V2_10"; 	break;
			case 11: monster "prtg_cas02.gat",198,175,"--ja--",1286,1,"#GuardianKilled::On_V2_11"; 	break;
			case 12: monster "prtg_cas02.gat",178,44,"--ja--",1286,1,"#GuardianKilled::On_V2_12"; 	break;
			case 13: monster "prtg_cas02.gat",71,75,"--ja--",1287,1,"#GuardianKilled::On_V2_13"; 	break;
			case 14: monster "prtg_cas02.gat",49,28,"--ja--",1287,1,"#GuardianKilled::On_V2_14"; 	break;
			case 15: monster "prtg_cas02.gat",64,186,"--ja--",1285,1,"#GuardianKilled::On_V2_15"; 	break;
			case 16: monster "prtg_cas02.gat",76,196,"--ja--",1285,1,"#GuardianKilled::On_V2_16"; 	break;
			case 17: monster "prtg_cas02.gat",75,175,"--ja--",1285,1,"#GuardianKilled::On_V2_17"; 	break;
		}
	}
	if(getarg(0)=="V3") {
		switch(getarg(1)) {
			case 10: monster "prtg_cas03.gat",191,190,"--ja--",1286,1,"#GuardianKilled::On_V3_10"; 	break;
			case 11: monster "prtg_cas03.gat",137,190,"--ja--",1286,1,"#GuardianKilled::On_V3_11"; 	break;
			case 12: monster "prtg_cas03.gat",45,99,"--ja--",1286,1,"#GuardianKilled::On_V3_12"; 	break;
			case 13: monster "prtg_cas03.gat",50,87,"--ja--",1287,1,"#GuardianKilled::On_V3_13"; 	break;
			case 14: monster "prtg_cas03.gat",41,87,"--ja--",1287,1,"#GuardianKilled::On_V3_14"; 	break;
			case 15: monster "prtg_cas03.gat",191,42,"--ja--",1285,1,"#GuardianKilled::On_V3_15"; 	break;
			case 16: monster "prtg_cas03.gat",179,43,"--ja--",1285,1,"#GuardianKilled::On_V3_16"; 	break;
			case 17: monster "prtg_cas03.gat",191,72,"--ja--",1285,1,"#GuardianKilled::On_V3_17"; 	break;
		}
	}
	if(getarg(0)=="V4") {
		switch(getarg(1)) {
			case 10: monster "prtg_cas04.gat",276,14,"--ja--",1286,1,"#GuardianKilled::On_V4_10"; 	break;
			case 11: monster "prtg_cas04.gat",274,35,"--ja--",1286,1,"#GuardianKilled::On_V4_11"; 	break;
			case 12: monster "prtg_cas04.gat",246,246,"--ja--",1286,1,"#GuardianKilled::On_V4_12"; 	break;
			case 13: monster "prtg_cas04.gat",38,240,"--ja--",1287,1,"#GuardianKilled::On_V4_13"; 	break;
			case 14: monster "prtg_cas04.gat",29,240,"--ja--",1287,1,"#GuardianKilled::On_V4_14"; 	break;
			case 15: monster "prtg_cas04.gat",33,258,"--ja--",1287,1,"#GuardianKilled::On_V4_15"; 	break;
			case 16: monster "prtg_cas04.gat",78,48,"--ja--",1285,1,"#GuardianKilled::On_V4_16"; 	break;
			case 17: monster "prtg_cas04.gat",36,61,"--ja--",1285,1,"#GuardianKilled::On_V4_17"; 	break;
		}
	}
	if(getarg(0)=="V5") {
		switch(getarg(1)) {
			case 10: monster "prtg_cas05.gat",266,262,"--ja--",1286,1,"#GuardianKilled::On_V5_10"; 	break;
			case 11: monster "prtg_cas05.gat",287,280,"--ja--",1286,1,"#GuardianKilled::On_V5_11"; 	break;
			case 12: monster "prtg_cas05.gat",245,250,"--ja--",1286,1,"#GuardianKilled::On_V5_12"; 	break;
			case 13: monster "prtg_cas05.gat",236,63,"--ja--",1287,1,"#GuardianKilled::On_V5_13"; 	break;
			case 14: monster "prtg_cas05.gat",251,63,"--ja--",1287,1,"#GuardianKilled::On_V5_14"; 	break;
			case 15: monster "prtg_cas05.gat",278,71,"--ja--",1287,1,"#GuardianKilled::On_V5_15"; 	break;
			case 16: monster "prtg_cas05.gat",32,253,"--ja--",1285,1,"#GuardianKilled::On_V5_16"; 	break;
			case 17: monster "prtg_cas05.gat",44,248,"--ja--",1285,1,"#GuardianKilled::On_V5_17"; 	break;
		}
	}
	if(getarg(2)) {		//呼び出し元が執事のとき
		mes "[執事"+strnpcinfo(0)+"]";
		mes "ガーディアンが設置されました。";
		mes "ガーディアンは私達の城を";
		mes "敵から守ってくれるでしょう。";
		close;
	}
	return;
}


//=========================================================================
// 各砦のガーディアン破壊後に城データを変更
//-------------------------------------------------------------------------

-	script	#GuardianKilled	-1,{
	//ルイーナ
	On_L1_10: setcastledata "aldeg_cas01.gat",10,0; end;
	On_L1_11: setcastledata "aldeg_cas01.gat",11,0; end;
	On_L1_12: setcastledata "aldeg_cas01.gat",12,0; end;
	On_L1_13: setcastledata "aldeg_cas01.gat",13,0; end;
	On_L1_14: setcastledata "aldeg_cas01.gat",14,0; end;
	On_L1_15: setcastledata "aldeg_cas01.gat",15,0; end;
	On_L1_16: setcastledata "aldeg_cas01.gat",16,0; end;
	On_L1_17: setcastledata "aldeg_cas01.gat",17,0; end;
	On_L2_10: setcastledata "aldeg_cas02.gat",10,0; end;
	On_L2_11: setcastledata "aldeg_cas02.gat",11,0; end;
	On_L2_12: setcastledata "aldeg_cas02.gat",12,0; end;
	On_L2_13: setcastledata "aldeg_cas02.gat",13,0; end;
	On_L2_14: setcastledata "aldeg_cas02.gat",14,0; end;
	On_L2_15: setcastledata "aldeg_cas02.gat",15,0; end;
	On_L2_16: setcastledata "aldeg_cas02.gat",16,0; end;
	On_L2_17: setcastledata "aldeg_cas02.gat",17,0; end;
	On_L3_10: setcastledata "aldeg_cas03.gat",10,0; end;
	On_L3_11: setcastledata "aldeg_cas03.gat",11,0; end;
	On_L3_12: setcastledata "aldeg_cas03.gat",12,0; end;
	On_L3_13: setcastledata "aldeg_cas03.gat",13,0; end;
	On_L3_14: setcastledata "aldeg_cas03.gat",14,0; end;
	On_L3_15: setcastledata "aldeg_cas03.gat",15,0; end;
	On_L3_16: setcastledata "aldeg_cas03.gat",16,0; end;
	On_L3_17: setcastledata "aldeg_cas03.gat",17,0; end;
	On_L4_10: setcastledata "aldeg_cas04.gat",10,0; end;
	On_L4_11: setcastledata "aldeg_cas04.gat",11,0; end;
	On_L4_12: setcastledata "aldeg_cas04.gat",12,0; end;
	On_L4_13: setcastledata "aldeg_cas04.gat",13,0; end;
	On_L4_14: setcastledata "aldeg_cas04.gat",14,0; end;
	On_L4_15: setcastledata "aldeg_cas04.gat",15,0; end;
	On_L4_16: setcastledata "aldeg_cas04.gat",16,0; end;
	On_L4_17: setcastledata "aldeg_cas04.gat",17,0; end;
	On_L5_10: setcastledata "aldeg_cas05.gat",10,0; end;
	On_L5_11: setcastledata "aldeg_cas05.gat",11,0; end;
	On_L5_12: setcastledata "aldeg_cas05.gat",12,0; end;
	On_L5_13: setcastledata "aldeg_cas05.gat",13,0; end;
	On_L5_14: setcastledata "aldeg_cas05.gat",14,0; end;
	On_L5_15: setcastledata "aldeg_cas05.gat",15,0; end;
	On_L5_16: setcastledata "aldeg_cas05.gat",16,0; end;
	On_L5_17: setcastledata "aldeg_cas05.gat",17,0; end;
	//ブリトニア
	On_B1_10: setcastledata "gefg_cas01.gat",10,0; end;
	On_B1_11: setcastledata "gefg_cas01.gat",11,0; end;
	On_B1_12: setcastledata "gefg_cas01.gat",12,0; end;
	On_B1_13: setcastledata "gefg_cas01.gat",13,0; end;
	On_B1_14: setcastledata "gefg_cas01.gat",14,0; end;
	On_B1_15: setcastledata "gefg_cas01.gat",15,0; end;
	On_B1_16: setcastledata "gefg_cas01.gat",16,0; end;
	On_B1_17: setcastledata "gefg_cas01.gat",17,0; end;
	On_B2_10: setcastledata "gefg_cas02.gat",10,0; end;
	On_B2_11: setcastledata "gefg_cas02.gat",11,0; end;
	On_B2_12: setcastledata "gefg_cas02.gat",12,0; end;
	On_B2_13: setcastledata "gefg_cas02.gat",13,0; end;
	On_B2_14: setcastledata "gefg_cas02.gat",14,0; end;
	On_B2_15: setcastledata "gefg_cas02.gat",15,0; end;
	On_B2_16: setcastledata "gefg_cas02.gat",16,0; end;
	On_B2_17: setcastledata "gefg_cas02.gat",17,0; end;
	On_B3_10: setcastledata "gefg_cas03.gat",10,0; end;
	On_B3_11: setcastledata "gefg_cas03.gat",11,0; end;
	On_B3_12: setcastledata "gefg_cas03.gat",12,0; end;
	On_B3_13: setcastledata "gefg_cas03.gat",13,0; end;
	On_B3_14: setcastledata "gefg_cas03.gat",14,0; end;
	On_B3_15: setcastledata "gefg_cas03.gat",15,0; end;
	On_B3_16: setcastledata "gefg_cas03.gat",16,0; end;
	On_B3_17: setcastledata "gefg_cas03.gat",17,0; end;
	On_B4_10: setcastledata "gefg_cas04.gat",10,0; end;
	On_B4_11: setcastledata "gefg_cas04.gat",11,0; end;
	On_B4_12: setcastledata "gefg_cas04.gat",12,0; end;
	On_B4_13: setcastledata "gefg_cas04.gat",13,0; end;
	On_B4_14: setcastledata "gefg_cas04.gat",14,0; end;
	On_B4_15: setcastledata "gefg_cas04.gat",15,0; end;
	On_B4_16: setcastledata "gefg_cas04.gat",16,0; end;
	On_B4_17: setcastledata "gefg_cas04.gat",17,0; end;
	On_B5_10: setcastledata "gefg_cas05.gat",10,0; end;
	On_B5_11: setcastledata "gefg_cas05.gat",11,0; end;
	On_B5_12: setcastledata "gefg_cas05.gat",12,0; end;
	On_B5_13: setcastledata "gefg_cas05.gat",13,0; end;
	On_B5_14: setcastledata "gefg_cas05.gat",14,0; end;
	On_B5_15: setcastledata "gefg_cas05.gat",15,0; end;
	On_B5_16: setcastledata "gefg_cas05.gat",16,0; end;
	On_B5_17: setcastledata "gefg_cas05.gat",17,0; end;
	//チュンリム
	On_C1_10: setcastledata "payg_cas01.gat",10,0; end;
	On_C1_11: setcastledata "payg_cas01.gat",11,0; end;
	On_C1_12: setcastledata "payg_cas01.gat",12,0; end;
	On_C1_13: setcastledata "payg_cas01.gat",13,0; end;
	On_C1_14: setcastledata "payg_cas01.gat",14,0; end;
	On_C1_15: setcastledata "payg_cas01.gat",15,0; end;
	On_C1_16: setcastledata "payg_cas01.gat",16,0; end;
	On_C1_17: setcastledata "payg_cas01.gat",17,0; end;
	On_C2_10: setcastledata "payg_cas02.gat",10,0; end;
	On_C2_11: setcastledata "payg_cas02.gat",11,0; end;
	On_C2_12: setcastledata "payg_cas02.gat",12,0; end;
	On_C2_13: setcastledata "payg_cas02.gat",13,0; end;
	On_C2_14: setcastledata "payg_cas02.gat",14,0; end;
	On_C2_15: setcastledata "payg_cas02.gat",15,0; end;
	On_C2_16: setcastledata "payg_cas02.gat",16,0; end;
	On_C2_17: setcastledata "payg_cas02.gat",17,0; end;
	On_C3_10: setcastledata "payg_cas03.gat",10,0; end;
	On_C3_11: setcastledata "payg_cas03.gat",11,0; end;
	On_C3_12: setcastledata "payg_cas03.gat",12,0; end;
	On_C3_13: setcastledata "payg_cas03.gat",13,0; end;
	On_C3_14: setcastledata "payg_cas03.gat",14,0; end;
	On_C3_15: setcastledata "payg_cas03.gat",15,0; end;
	On_C3_16: setcastledata "payg_cas03.gat",16,0; end;
	On_C3_17: setcastledata "payg_cas03.gat",17,0; end;
	On_C4_10: setcastledata "payg_cas04.gat",10,0; end;
	On_C4_11: setcastledata "payg_cas04.gat",11,0; end;
	On_C4_12: setcastledata "payg_cas04.gat",12,0; end;
	On_C4_13: setcastledata "payg_cas04.gat",13,0; end;
	On_C4_14: setcastledata "payg_cas04.gat",14,0; end;
	On_C4_15: setcastledata "payg_cas04.gat",15,0; end;
	On_C4_16: setcastledata "payg_cas04.gat",16,0; end;
	On_C4_17: setcastledata "payg_cas04.gat",17,0; end;
	On_C5_10: setcastledata "payg_cas05.gat",10,0; end;
	On_C5_11: setcastledata "payg_cas05.gat",11,0; end;
	On_C5_12: setcastledata "payg_cas05.gat",12,0; end;
	On_C5_13: setcastledata "payg_cas05.gat",13,0; end;
	On_C5_14: setcastledata "payg_cas05.gat",14,0; end;
	On_C5_15: setcastledata "payg_cas05.gat",15,0; end;
	On_C5_16: setcastledata "payg_cas05.gat",16,0; end;
	On_C5_17: setcastledata "payg_cas05.gat",17,0; end;
	//ヴァルキリーレルム
	On_V1_10: setcastledata "prtg_cas01.gat",10,0; end;
	On_V1_11: setcastledata "prtg_cas01.gat",11,0; end;
	On_V1_12: setcastledata "prtg_cas01.gat",12,0; end;
	On_V1_13: setcastledata "prtg_cas01.gat",13,0; end;
	On_V1_14: setcastledata "prtg_cas01.gat",14,0; end;
	On_V1_15: setcastledata "prtg_cas01.gat",15,0; end;
	On_V1_16: setcastledata "prtg_cas01.gat",16,0; end;
	On_V1_17: setcastledata "prtg_cas01.gat",17,0; end;
	On_V2_10: setcastledata "prtg_cas02.gat",10,0; end;
	On_V2_11: setcastledata "prtg_cas02.gat",11,0; end;
	On_V2_12: setcastledata "prtg_cas02.gat",12,0; end;
	On_V2_13: setcastledata "prtg_cas02.gat",13,0; end;
	On_V2_14: setcastledata "prtg_cas02.gat",14,0; end;
	On_V2_15: setcastledata "prtg_cas02.gat",15,0; end;
	On_V2_16: setcastledata "prtg_cas02.gat",16,0; end;
	On_V2_17: setcastledata "prtg_cas02.gat",17,0; end;
	On_V3_10: setcastledata "prtg_cas03.gat",10,0; end;
	On_V3_11: setcastledata "prtg_cas03.gat",11,0; end;
	On_V3_12: setcastledata "prtg_cas03.gat",12,0; end;
	On_V3_13: setcastledata "prtg_cas03.gat",13,0; end;
	On_V3_14: setcastledata "prtg_cas03.gat",14,0; end;
	On_V3_15: setcastledata "prtg_cas03.gat",15,0; end;
	On_V3_16: setcastledata "prtg_cas03.gat",16,0; end;
	On_V3_17: setcastledata "prtg_cas03.gat",17,0; end;
	On_V4_10: setcastledata "prtg_cas04.gat",10,0; end;
	On_V4_11: setcastledata "prtg_cas04.gat",11,0; end;
	On_V4_12: setcastledata "prtg_cas04.gat",12,0; end;
	On_V4_13: setcastledata "prtg_cas04.gat",13,0; end;
	On_V4_14: setcastledata "prtg_cas04.gat",14,0; end;
	On_V4_15: setcastledata "prtg_cas04.gat",15,0; end;
	On_V4_16: setcastledata "prtg_cas04.gat",16,0; end;
	On_V4_17: setcastledata "prtg_cas04.gat",17,0; end;
	On_V5_10: setcastledata "prtg_cas05.gat",10,0; end;
	On_V5_11: setcastledata "prtg_cas05.gat",11,0; end;
	On_V5_12: setcastledata "prtg_cas05.gat",12,0; end;
	On_V5_13: setcastledata "prtg_cas05.gat",13,0; end;
	On_V5_14: setcastledata "prtg_cas05.gat",14,0; end;
	On_V5_15: setcastledata "prtg_cas05.gat",15,0; end;
	On_V5_16: setcastledata "prtg_cas05.gat",16,0; end;
	On_V5_17: setcastledata "prtg_cas05.gat",17,0; end;
}
