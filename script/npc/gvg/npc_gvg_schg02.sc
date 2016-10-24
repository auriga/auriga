//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Nidavellir Guild 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
schg_cas02.gat,0,0,0	script	#AgitExe_N2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",162,193,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","N2";
	callfunc "AgitBreakSE","N2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",162,193,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","N2";
	end;
OnAgitSummon:
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "schg_cas02.gat",0,0,0,0,"--ja--",1272,1;
	monster "schg_cas02.gat",162,193,"--ja--",1272,1;
	monster "schg_cas02.gat",162,193,"--ja--",1270,4;
	monster "schg_cas02.gat",162,193,"--ja--",1268,1;
	monster "schg_cas02.gat",162,193,"--ja--",1219,1;
	monster "schg_cas02.gat",162,193,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
schg_cas02.gat,0,0,0	script	#AgitTreasure_N2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1939;
		setarray 'treasure_x,249,250,251,252,253,246,247,248,249,250,250,251,252,253,246,247,248,249,250,249,250,251,252,253;
		setarray 'treasure_y,378,378,378,378,378,376,376,376,376,376,374,374,374,374,372,372,372,372,372,370,370,370,370,370;
	}
	callfunc "AgitTreasure",'treasure_id,'treasure_x,'treasure_y;
	end;
OnKilled:
	// dummy event
	end;
}

//============================================================
// 守備担当
//------------------------------------------------------------
schg_cas02.gat,140,184,3	script	エンディプ#N2	868,{
	if('guardiaN2_x[0] == 0) {
		setarray 'guardian1_x,326,337,337,334,337,334,296,337,334,296,285,337;
		setarray 'guardian1_y, 83, 95, 95,119, 95,119, 82, 95,119, 82, 40, 95;
		setarray 'guardian2_x,359,300,300,337,300,337,317,300,337,317,307,307;
		setarray 'guardian2_y, 85,119,119,154,119,154,183,119,154,183,222,222;
	}
	callfunc "AgitGuard",'guardian1_x,'guardian1_y,'guardian2_x,'guardian2_y;
	close;
}

schg_cas02.gat,0,0,0	script	Guardian#N2	111,{
	end;
OnKilled1:
	set 'guardian1,'guardian1-1;
	if('guardian1 < 2)
		callfunc "AgitCallGuardian",1,0,334,119;
	end;
OnKilled2:
	set 'guardian2,'guardian2-1;
	if('guardian2 < 2)
		callfunc "AgitCallGuardian",2,0,236,41;
	end;
OnTimer300000:
	callfunc "AgitCallGuardian",1,1,236,41;
	end;
OnTimer600000:
	callfunc "AgitCallGuardian",2,0,300,119;
	end;
OnTimer900000:
	callfunc "AgitCallGuardian",1,2,285,40;
	end;
OnTimer1200000:
	callfunc "AgitCallGuardian",2,0,337,154;
	end;
OnTimer1800000:
	callfunc "AgitCallGuardian",1,3,296,82;
	end;
OnTimer2100000:
	callfunc "AgitCallGuardian",2,0,317,183;
	end;
OnTimer2700000:
	callfunc "AgitCallGuardian",1,4,334,119;
	end;
OnTimer3000000:
	callfunc "AgitCallGuardian",2,0,307,222;
	end;
OnTimer3600000:
	callfunc "AgitCallGuardian",1,5,337,95;
	end;
OnTimer3900000:
	callfunc "AgitCallGuardian",2,0,359,85;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas02.gat","Guardian#N2::OnKilled1";
	killmonster "schg_cas02.gat","Guardian#N2::OnKilled2";
	set 'guardian1,0;
	set 'guardian2,0;
	end;
}

//============================================================
// 守護石
//------------------------------------------------------------
schg_cas02.gat,0,0,0	script	GuardianStone1#N2	111,{
OnAgitStart:
OnRepair:
	callguardian "schg_cas02.gat",231,58,"--ja--",1907,1,"GuardianStone1#N2::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",1;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第1守護石#N2";
	misceffect 247,"第1守護石#N2";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas02.gat","GuardianStone1#N2::OnKilled";
	set 'status,0;
	end;
}

schg_cas02.gat,231,57,0	script	第1守護石#N2	844,{
	callfunc "AgitStone",1;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

schg_cas02.gat,0,0,0	script	GuardianStone2#N2	111,{
OnAgitStart:
OnRepair:
	callguardian "schg_cas02.gat",335,230,"--ja--",1908,1,"GuardianStone2#N2::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",2;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第2守護石#N2";
	misceffect 247,"第2守護石#N2";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas02.gat","GuardianStone2#N2::OnKilled";
	set 'status,0;
	end;
}

schg_cas02.gat,335,231,0	script	第2守護石#N2	844,{
	callfunc "AgitStone",2;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

//============================================================
// バリケード
//------------------------------------------------------------
schg_cas02.gat,0,0,0	script	Barricade#N2	111,{
OnSet:
OnAgitStart:
	areasetcell "schg_cas02.gat",290,98,290,105,1;
	callguardian "schg_cas02.gat",289,98," ",1905,1,"Barricade#N2::OnKilled";
	callguardian "schg_cas02.gat",289,100," ",1905,1,"Barricade#N2::OnKilled";
	callguardian "schg_cas02.gat",289,102," ",1905,1,"Barricade#N2::OnKilled";
	callguardian "schg_cas02.gat",289,104," ",1905,1,"Barricade#N2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas02.gat",290,98,290,105,0;
	killmonster "schg_cas02.gat","Barricade#N2::OnKilled";
	end;
OnKilled:
	end;
}

schg_cas02.gat,288,97,0	script	制御装置01#N2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas02.gat",279,98,279,105,5;
	callguardian "schg_cas02.gat",280,98," ",1905,1,"制御装置01#N2::OnKilled";
	callguardian "schg_cas02.gat",280,100," ",1905,1,"制御装置01#N2::OnKilled";
	callguardian "schg_cas02.gat",280,102," ",1905,1,"制御装置01#N2::OnKilled";
	callguardian "schg_cas02.gat",281,99," ",1905,1,"制御装置01#N2::OnKilled";
	callguardian "schg_cas02.gat",281,101," ",1905,1,"制御装置01#N2::OnKilled";
	callguardian "schg_cas02.gat",281,103," ",1905,1,"制御装置01#N2::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第1バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas02.gat",279,98,279,105,0;
	killmonster "schg_cas02.gat","制御装置01#N2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas02.gat",279,98,279,105,0;
	killmonster "schg_cas02.gat","制御装置01#N2::OnKilled";
	set 'status,0;
	end;
}

schg_cas02.gat,230,209,0	script	制御装置02#N2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas02.gat",230,213,230,218,5;
	callguardian "schg_cas02.gat",231,214," ",1905,1,"制御装置02#N2::OnKilled";
	callguardian "schg_cas02.gat",231,216," ",1905,1,"制御装置02#N2::OnKilled";
	//callguardian "schg_cas02.gat",231,218," ",1905,1,"制御装置02#N2::OnKilled";
	callguardian "schg_cas02.gat",231,215," ",1905,1,"制御装置02#N2::OnKilled";
	callguardian "schg_cas02.gat",232,213," ",1905,1,"制御装置02#N2::OnKilled";
	callguardian "schg_cas02.gat",232,215," ",1905,1,"制御装置02#N2::OnKilled";
	callguardian "schg_cas02.gat",232,217," ",1905,1,"制御装置02#N2::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第2バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas02.gat",230,213,230,218,0;
	killmonster "schg_cas02.gat","制御装置02#N2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas02.gat",230,213,230,218,0;
	killmonster "schg_cas02.gat","制御装置02#N2::OnKilled";
	set 'status,0;
	end;
}

schg_cas02.gat,159,143,0	script	制御装置03#N2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas02.gat",160,141,165,141,5;
	callguardian "schg_cas02.gat",160,140," ",1905,1,"制御装置03#N2::OnKilled";
	callguardian "schg_cas02.gat",162,140," ",1905,1,"制御装置03#N2::OnKilled";
	callguardian "schg_cas02.gat",164,140," ",1905,1,"制御装置03#N2::OnKilled";
	callguardian "schg_cas02.gat",166,140," ",1905,1,"制御装置03#N2::OnKilled";
	set 'count,4;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第3バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas02.gat",160,141,165,141,0;
	killmonster "schg_cas02.gat","制御装置03#N2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas02.gat",160,141,165,141,0;
	killmonster "schg_cas02.gat","制御装置03#N2::OnKilled";
	set 'status,0;
	end;
}

//============================================================
// リンクフラッグ(A)
//------------------------------------------------------------
schg_cas02.gat,143,198,0	script	LF-01#N2	111,{
	setarray '@code,1,2;	//"第1拠点","第2拠点"
	setarray '@x,235,302;
	setarray '@y, 44,233;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,143,202,0	script	LF-02#N2	111,{
	setarray '@code,11,12;	//"防衛地域1-1","防衛地域1-2"
	setarray '@x,317,359;
	setarray '@y, 83, 83;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,143,206,0	script	LF-03#N2	111,{
	setarray '@code,21,22;	//"防衛地域2-1","防衛地域2-2"
	setarray '@x,283,280;
	setarray '@y, 79,122;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,145,208,0	script	LF-04#N2	111,{
	setarray '@code,31,32;	//"防衛地域3-1","防衛地域3-2"
	setarray '@x,215,255;
	setarray '@y,110,215;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,180,208,0	script	LF-05#N2	111,{
	setarray '@code,101,102;	//"中央1区画","中央2区画"
	setarray '@x,338,213;
	setarray '@y,153,226;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,182,206,0	script	LF-06#N2	111,{
	setarray '@code,111,121,131;	//"区域1-1","区域2-1","区域3-1"
	setarray '@x,317,283,215;
	setarray '@y, 83, 79,110;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,182,202,0	script	LF-07#N2	111,{
	setarray '@code,112,122,132;	//"区域1-2","区域2-2","区域3-2"
	setarray '@x,359,280,255;
	setarray '@y, 83,122,215;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas02.gat,182,198,0	script	LF-08#N2	111,{
	callfunc "AgitLinkFlagB",1,101,306;
	close;
}

//============================================================
// リンクフラッグ(B)
//------------------------------------------------------------
-	script	#LinkFlag_N2	{
	callfunc "AgitLinkFlagB",0,136,188;
	close;
OnAgitInit:
OnFlagEmb_N2:
	if(substr(strnpcinfo(2),0,1) == "B")	//ギルドフラッグ型ならエンブレム更新
		flagemblem getcastledata("schg_cas02.gat",1);
	end;
}
schg_cas02.gat,235,222,0	duplicate(#LinkFlag_N2)	アンドラング#A01	111
schg_cas02.gat,157,136,0	duplicate(#LinkFlag_N2)	アンドラング#A02	111
schg_cas02.gat,168,136,0	duplicate(#LinkFlag_N2)	アンドラング#A03	111
schg_cas02.gat,320,232,0	duplicate(#LinkFlag_N2)	アンドラング#A04	111
schg_cas02.gat,295,109,0	duplicate(#LinkFlag_N2)	アンドラング#A05	111
schg_cas02.gat,295,92,0		duplicate(#LinkFlag_N2)	アンドラング#A06	111
schg_cas02.gat,285,90,0		duplicate(#LinkFlag_N2)	アンドラング#A07	111
schg_cas02.gat,285,109,0	duplicate(#LinkFlag_N2)	アンドラング#A08	111
schg_cas02.gat,238,66,0		duplicate(#LinkFlag_N2)	アンドラング#A09	111
schg_cas02.gat,230,45,0		duplicate(#LinkFlag_N2)	アンドラング#A10	111
schg_cas02.gat,233,120,0	duplicate(#LinkFlag_N2)	アンドラング#A11	111
schg_cas02.gat,247,120,0	duplicate(#LinkFlag_N2)	アンドラング#A12	111
schg_cas02.gat,261,162,0	duplicate(#LinkFlag_N2)	アンドラング#A13	111
schg_cas02.gat,244,162,0	duplicate(#LinkFlag_N2)	アンドラング#A14	111
schg_cas02.gat,235,207,0	duplicate(#LinkFlag_N2)	アンドラング#A15	111

//============================================================
// カプラ職員
//------------------------------------------------------------
schg_cas02.gat,131,365,3	script	カプラ職員::AgitKafra_N2	117,{
	callfunc "AgitKafra",13;
	close;
OnAgitInit:
	if(getcastledata("schg_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
schg_cas02.gat,105,378,3	script	執事	55,{
	callfunc "AgitSteward","N2",0,0,0,249,373;
	close;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
schg_cas02.gat,257,369,0	script	#AgitMaster_N2	111,{
	callfunc "AgitMaster",339,79;
	close;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_N2a	{
	callfunc "AgitEmblemFlag",2,"schg_cas02.gat",136,188;
	close;
OnAgitInit:
OnFlagEmb_N2:
	flagemblem getcastledata("schg_cas02.gat",1);
	end;
}
sch_gld.gat,296,247,4	duplicate(#GldFlag_N2a)	アンドラング#a01	722
sch_gld.gat,280,247,4	duplicate(#GldFlag_N2a)	アンドラング#a02	722

-	script	#GldFlag_N2b	{
	end;
OnAgitInit:
OnFlagEmb_N2:
	flagemblem getcastledata("schg_cas02.gat",1);
	end;
}
//yuno.gat,110,171,5	duplicate(#GldFlag_N2b)	アンドラング#b01	722

//============================================================
// 不思議なヒマワリ（アジトダンジョン）
//------------------------------------------------------------
schg_cas02.gat,174,328,3	script	不思議なヒマワリ#N2	976,{
	callfunc "AgitDungeonSE","schg_dun01.gat",94,284;
	close;
}
