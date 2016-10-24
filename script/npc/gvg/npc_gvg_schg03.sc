//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Nidavellir Guild 3	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
schg_cas03.gat,0,0,0	script	#AgitExe_N3	-1,{
OnAgitStart:
	callfunc "AgitEmperium",338,202,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","N3";
	callfunc "AgitBreakSE","N3";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",338,202,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","N3";
	end;
OnAgitSummon:
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "schg_cas03.gat",0,0,0,0,"--ja--",1272,1;
	monster "schg_cas03.gat",338,202,"--ja--",1272,1;
	monster "schg_cas03.gat",338,202,"--ja--",1270,4;
	monster "schg_cas03.gat",338,202,"--ja--",1268,1;
	monster "schg_cas03.gat",338,202,"--ja--",1219,1;
	monster "schg_cas03.gat",338,202,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
schg_cas03.gat,0,0,0	script	#AgitTreasure_N3	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1940;
		setarray 'treasure_x,189,190,191,192,193,194,189,190,191,192,193,194,189,190,191,192,193,194,189,190,191,192,193,194;
		setarray 'treasure_y, 21, 21, 21, 21, 21, 21, 19, 19, 19, 19, 19, 19, 17, 17, 17, 17, 17, 17, 15, 15, 15, 15, 15, 15;
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
schg_cas03.gat,287,226,5	script	エルゼ#N3	868,{
	if('guardiaN3_x[0] == 0) {
		setarray 'guardian1_x,323,273,273,288,273,288,306,273,288,306,323,306;
		setarray 'guardian1_y,308,309,309,306,309,306,326,309,306,326,308,325;
		setarray 'guardian2_x,338,364,364,365,364,365,317,364,365,317,338,364;
		setarray 'guardian2_y,309,305,305,261,305,261,318,305,261,318,310,305;
	}
	callfunc "AgitGuard",'guardian1_x,'guardian1_y,'guardian2_x,'guardian2_y;
	close;
}

schg_cas03.gat,0,0,0	script	Guardian#N3	111,{
	end;
OnKilled1:
	set 'guardian1,'guardian1-1;
	if('guardian1 < 2)
		callfunc "AgitCallGuardian",1,0,120,37;
	end;
OnKilled2:
	set 'guardian2,'guardian2-1;
	if('guardian2 < 2)
		callfunc "AgitCallGuardian",2,0,329,314;
	end;
OnTimer300000:
	callfunc "AgitCallGuardian",1,1,323,308;
	end;
OnTimer600000:
	callfunc "AgitCallGuardian",2,0,338,309;
	end;
OnTimer900000:
	callfunc "AgitCallGuardian",1,2,273,309;
	end;
OnTimer1200000:
	callfunc "AgitCallGuardian",2,0,364,305;
	end;
OnTimer1800000:
	callfunc "AgitCallGuardian",1,3,288,306;
	end;
OnTimer2100000:
	callfunc "AgitCallGuardian",2,0,365,261;
	end;
OnTimer2700000:
	callfunc "AgitCallGuardian",1,4,306,325;
	end;
OnTimer3000000:
	callfunc "AgitCallGuardian",2,0,317,318;
	end;
OnTimer3600000:
	callfunc "AgitCallGuardian",1,5,273,309;
	end;
OnTimer3900000:
	callfunc "AgitCallGuardian",2,0,364,305;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas03.gat","Guardian#N3::OnKilled1";
	killmonster "schg_cas03.gat","Guardian#N3::OnKilled2";
	set 'guardian1,0;
	set 'guardian2,0;
	end;
}

//============================================================
// 守護石
//------------------------------------------------------------
schg_cas03.gat,0,0,0	script	GuardianStone1#N3	111,{
OnAgitStart:
OnRepair:
	callguardian "schg_cas03.gat",242,309,"--ja--",1907,1,"GuardianStone1#N3::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",1;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第1守護石#N3";
	misceffect 247,"第1守護石#N3";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas03.gat","GuardianStone1#N3::OnKilled";
	set 'status,0;
	end;
}

schg_cas03.gat,242,309,0	script	第1守護石#N3	844,{
	callfunc "AgitStone",1;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

schg_cas03.gat,0,0,0	script	GuardianStone2#N3	111,{
OnAgitStart:
OnRepair:
	callguardian "schg_cas03.gat",376,251,"--ja--",1908,1,"GuardianStone2#N3::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",2;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第2守護石#N3";
	misceffect 247,"第2守護石#N3";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "schg_cas03.gat","GuardianStone2#N3::OnKilled";
	set 'status,0;
	end;
}

schg_cas03.gat,376,250,0	script	第2守護石#N3	844,{
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
schg_cas03.gat,0,0,0	script	Barricade#N3	111,{
OnSet:
OnAgitStart:
	areasetcell "schg_cas03.gat",326,301,331,301,1;
	callguardian "schg_cas03.gat",326,300," ",1905,1,"Barricade#N3::OnKilled";
	callguardian "schg_cas03.gat",328,300," ",1905,1,"Barricade#N3::OnKilled";
	callguardian "schg_cas03.gat",330,300," ",1905,1,"Barricade#N3::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas03.gat",326,301,331,301,0;
	killmonster "schg_cas03.gat","Barricade#N3::OnKilled";
	end;
OnKilled:
	end;
}

schg_cas03.gat,335,298,0	script	制御装置01#N3	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas03.gat",325,277,332,277,5;
	callguardian "schg_cas03.gat",326,278," ",1905,1,"制御装置01#N3::OnKilled";
	callguardian "schg_cas03.gat",328,278," ",1905,1,"制御装置01#N3::OnKilled";
	callguardian "schg_cas03.gat",330,278," ",1905,1,"制御装置01#N3::OnKilled";
	callguardian "schg_cas03.gat",327,279," ",1905,1,"制御装置01#N3::OnKilled";
	callguardian "schg_cas03.gat",329,279," ",1905,1,"制御装置01#N3::OnKilled";
	callguardian "schg_cas03.gat",331,279," ",1905,1,"制御装置01#N3::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第1バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas03.gat",325,277,332,277,0;
	killmonster "schg_cas03.gat","制御装置01#N3::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas03.gat",325,277,332,277,0;
	killmonster "schg_cas03.gat","制御装置01#N3::OnKilled";
	set 'status,0;
	end;
}

schg_cas03.gat,200,227,0	script	制御装置02#N3	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas03.gat",200,230,200,237,5;
	callguardian "schg_cas03.gat",201,231," ",1905,1,"制御装置02#N3::OnKilled";
	callguardian "schg_cas03.gat",201,233," ",1905,1,"制御装置02#N3::OnKilled";
	callguardian "schg_cas03.gat",201,235," ",1905,1,"制御装置02#N3::OnKilled";
	callguardian "schg_cas03.gat",202,232," ",1905,1,"制御装置02#N3::OnKilled";
	callguardian "schg_cas03.gat",202,234," ",1905,1,"制御装置02#N3::OnKilled";
	callguardian "schg_cas03.gat",202,236," ",1905,1,"制御装置02#N3::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第2バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas03.gat",200,230,200,237,0;
	killmonster "schg_cas03.gat","制御装置02#N3::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas03.gat",200,230,200,237,0;
	killmonster "schg_cas03.gat","制御装置02#N3::OnKilled";
	set 'status,0;
	end;
}

schg_cas03.gat,273,205,0	script	制御装置03#N3	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "schg_cas03.gat",285,198,285,205,5;
	callguardian "schg_cas03.gat",284,199," ",1905,1,"制御装置03#N3::OnKilled";
	callguardian "schg_cas03.gat",284,201," ",1905,1,"制御装置03#N3::OnKilled";
	callguardian "schg_cas03.gat",284,203," ",1905,1,"制御装置03#N3::OnKilled";
	callguardian "schg_cas03.gat",284,205," ",1905,1,"制御装置03#N3::OnKilled";
	set 'count,4;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第3バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "schg_cas03.gat",285,198,285,205,0;
	killmonster "schg_cas03.gat","制御装置03#N3::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "schg_cas03.gat",285,198,285,205,0;
	killmonster "schg_cas03.gat","制御装置03#N3::OnKilled";
	set 'status,0;
	end;
}

//============================================================
// リンクフラッグ(A)
//------------------------------------------------------------
schg_cas03.gat,346,211,0	script	LF-01#N3	111,{
	setarray '@code,1,2;	//"第1拠点","第2拠点"
	setarray '@x,262,378;
	setarray '@y,323,263;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,346,207,0	script	LF-02#N3	111,{
	setarray '@code,101;	//"中央1区画"
	setarray '@x,306;
	setarray '@y,320;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,346,203,0	script	LF-03#N3	111,{
	setarray '@code,21,22;	//"防衛地域2-1","防衛地域2-2"
	setarray '@x,309,348;
	setarray '@y,292,292;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,346,199,0	script	LF-04#N3	111,{
	setarray '@code,102;	//"中央2区画"
	setarray '@x,266;
	setarray '@y,263;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,346,195,0	script	LF-05#N3	111,{
	setarray '@code,31,32;	//"防衛地域3-1","防衛地域3-2"
	setarray '@x,226,185;
	setarray '@y,220,249;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,346,191,0	script	LF-06#N3	111,{
	setarray '@code,103;	//"中央3区画"
	setarray '@x,271;
	setarray '@y,226;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,301,213,0	script	LF-07#N3	111,{
	setarray '@code,1,2,101;	//"第1拠点","第2拠点","中央1区画"
	setarray '@x,262,378,306;
	setarray '@y,323,263,320;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,301,209,0	script	LF-08#N3	111,{
	setarray '@code,121,122,102;	//"区域2-1","区域2-2","中央2区画"
	setarray '@x,309,348,266;
	setarray '@y,292,292,263;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,301,194,0	script	LF-09#N3	111,{
	setarray '@code,131,132,103;	//"区域3-1","区域3-2","中央3区画"
	setarray '@x,226,185,271;
	setarray '@y,220,249,226;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

schg_cas03.gat,301,190,0	script	LF-10#N3	111,{
	callfunc "AgitLinkFlagB",1,57,13;
	close;
}

//============================================================
// リンクフラッグ(B)
//------------------------------------------------------------
-	script	#LinkFlag_N3	{
	callfunc "AgitLinkFlagB",0,308,202;
	close;
OnAgitInit:
OnFlagEmb_N3:
	if(substr(strnpcinfo(2),0,1) == "B")	//ギルドフラッグ型ならエンブレム更新
		flagemblem getcastledata("schg_cas03.gat",1);
	end;
}
schg_cas03.gat,335,305,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A01	111
schg_cas03.gat,322,305,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A02	111
schg_cas03.gat,352,248,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A03	111
schg_cas03.gat,320,283,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A04	111
schg_cas03.gat,337,283,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A05	111
schg_cas03.gat,233,320,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A06	111
schg_cas03.gat,207,239,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A07	111
schg_cas03.gat,207,228,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A08	111
schg_cas03.gat,266,206,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A09	111
schg_cas03.gat,266,197,0	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#A10	111
schg_cas03.gat,283,206,2	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#B11	722
schg_cas03.gat,283,197,2	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#B12	722
schg_cas03.gat,332,323,6	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#B13	722
schg_cas03.gat,343,323,2	duplicate(#LinkFlag_N3)	ヴィーズブラーイン#B14	722

//============================================================
// カプラ職員
//------------------------------------------------------------
schg_cas03.gat,50,50,3	script	カプラ職員::AgitKafra_N3	117,{
	callfunc "AgitKafra",13;
	close;
OnAgitInit:
	if(getcastledata("schg_cas03.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
schg_cas03.gat,88,90,3	script	執事	55,{
	callfunc "AgitSteward","N3",0,0,0,190,16;
	close;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
schg_cas03.gat,199,25,0	script	#AgitMaster_N3	111,{
	callfunc "AgitMaster",57,13;
	close;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_N3a	{
	callfunc "AgitEmblemFlag",2,"schg_cas03.gat",308,202;
	close;
OnAgitInit:
OnFlagEmb_N3:
	flagemblem getcastledata("schg_cas03.gat",1);
	end;
}
sch_gld.gat,91,191,0	duplicate(#GldFlag_N3a)	ヴィーズブラーイン#a01	722
sch_gld.gat,104,191,0	duplicate(#GldFlag_N3a)	ヴィーズブラーイン#a02	722

-	script	#GldFlag_N3b	{
	end;
OnAgitInit:
OnFlagEmb_N3:
	flagemblem getcastledata("schg_cas03.gat",1);
	end;
}
//yuno.gat,111,175,5	duplicate(#GldFlag_N3b)	ヴィーズブラーイン#b01	722

//============================================================
// 不思議なヒマワリ（アジトダンジョン）
//------------------------------------------------------------
schg_cas03.gat,25,22,3	script	不思議なヒマワリ#N3	976,{
	callfunc "AgitDungeonSE","schg_dun01.gat",79,140;
	close;
}
