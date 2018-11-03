//=========================================================================
// アジト専属カプラのメニューファンクション
//	callfunc "GvKafraMenu";
//-------------------------------------------------------------------------

function	script	GvKafraMenu	{
	cutin "kafra_01",2;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid == 0 || getcharid(2) != '@gid) {
		mes "[カプラ職員]";
		mes "私は、ギルド";
		mes "^ff0000" + getguildname('@gid) + "^000000";
		mes "の皆様にだけお仕えするように";
		mes "契約されております。";
		mes "他のカプラサービスを";
		mes "ご利用くださいませ。";
		close2;
		cutin "kafra_01",255;
		end;
	}
	mes "[カプラ職員]";
	mes "いらっしゃいませ^ff0000" +getguildname('@gid)+ "^000000の皆さん";
	mes "カプラサービスは";
	mes "いつも皆様のそばにいます。";
	next;
	return;
}


//-------------------------------------------
// ■ カプラのメイン部分の処理は
//    npc_town_kafra.txt内のfunction参照
//-------------------------------------------

//==========================================
// ルイーナ
//------------------------------------------
-	script	AgitKafra_L0	-1,{
	callfunc "GvKafraMenu";
	set '@code,17;
	set '@price,200;
	callfunc "KafraMain",3,0x1ce,0,0,0,0,0,0,40,800,'@code,'@price;
	end;
}

aldeg_cas01.gat,218,170,0	duplicate(AgitKafra_L0)	カプラ職員::AgitKafra_L1	117
aldeg_cas02.gat,84,74,0		duplicate(AgitKafra_L0)	カプラ職員::AgitKafra_L2	117
aldeg_cas03.gat,118,76,0	duplicate(AgitKafra_L0)	カプラ職員::AgitKafra_L3	117
aldeg_cas04.gat,45,88,0		duplicate(AgitKafra_L0)	カプラ職員::AgitKafra_L4	117
aldeg_cas05.gat,31,190,0	duplicate(AgitKafra_L0)	カプラ職員::AgitKafra_L5	117

//==========================================
// ブリトニア
//------------------------------------------
-	script	AgitKafra_B0	-1,{
	callfunc "GvKafraMenu";
	set '@code,15;
	set '@price,200;
	callfunc "KafraMain",3,0x1ce,0,0,0,0,0,0,40,800,'@code,'@price;
	end;
}

gefg_cas01.gat,83,47,3		duplicate(AgitKafra_B0)	カプラ職員::AgitKafra_B1	117
gefg_cas02.gat,23,66,3		duplicate(AgitKafra_B0)	カプラ職員::AgitKafra_B2	117
gefg_cas03.gat,116,89,5		duplicate(AgitKafra_B0)	カプラ職員::AgitKafra_B3	117
gefg_cas04.gat,59,70,3		duplicate(AgitKafra_B0)	カプラ職員::AgitKafra_B4	117
gefg_cas05.gat,61,52,5		duplicate(AgitKafra_B0)	カプラ職員::AgitKafra_B5	117

//==========================================
// チュンリム
//------------------------------------------
-	script	AgitKafra_C0	-1,{
	callfunc "GvKafraMenu";
	set '@code,16;
	set '@price,200;
	callfunc "KafraMain",3,0x1ce,0,0,0,0,0,0,40,800,'@code,'@price;
	end;
}

payg_cas01.gat,128,58,3		duplicate(AgitKafra_C0)	カプラ職員::AgitKafra_C1	117
payg_cas02.gat,22,275,5		duplicate(AgitKafra_C0)	カプラ職員::AgitKafra_C2	117
payg_cas03.gat,9,263,5		duplicate(AgitKafra_C0)	カプラ職員::AgitKafra_C3	117
payg_cas04.gat,40,235,1		duplicate(AgitKafra_C0)	カプラ職員::AgitKafra_C4	117
payg_cas05.gat,276,227,1	duplicate(AgitKafra_C0)	カプラ職員::AgitKafra_C5	117

//==========================================
// ヴァルキリーレルム
//------------------------------------------
-	script	AgitKafra_V0	-1,{
	callfunc "GvKafraMenu";
	set '@code,14;
	set '@price,200;
	callfunc "KafraMain",3,0x1ce,0,0,0,0,0,0,40,800,'@code,'@price;
	end;
}

prtg_cas01.gat,96,173,0		duplicate(AgitKafra_V0)	カプラ職員::AgitKafra_V1	117
prtg_cas02.gat,71,36,4		duplicate(AgitKafra_V0)	カプラ職員::AgitKafra_V2	117
prtg_cas03.gat,181,215,4	duplicate(AgitKafra_V0)	カプラ職員::AgitKafra_V3	117
prtg_cas04.gat,258,247,4	duplicate(AgitKafra_V0)	カプラ職員::AgitKafra_V4	117
prtg_cas05.gat,52,41,4		duplicate(AgitKafra_V0)	カプラ職員::AgitKafra_V5	117
