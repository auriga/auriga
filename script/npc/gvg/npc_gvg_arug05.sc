//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valfreyja Guild 5	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
arug_cas05.gat,0,0,0	script	#AgitExe_F5	-1,{
OnAgitStart:
	callfunc "AgitEmperium",141,293,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","F5";
	callfunc "AgitBreakSE","F5";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",141,293,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","F5";
	end;
OnAgitSummon:
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "arug_cas05.gat",0,0,0,0,"--ja--",1272,1;
	monster "arug_cas05.gat",141,293,"--ja--",1272,1;
	monster "arug_cas05.gat",141,293,"--ja--",1270,4;
	monster "arug_cas05.gat",141,293,"--ja--",1268,1;
	monster "arug_cas05.gat",141,293,"--ja--",1219,1;
	monster "arug_cas05.gat",141,293,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
arug_cas05.gat,0,0,0	script	#AgitTreasure_F5	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1945;
		setarray 'treasure_x,291,292,293,294,295,296,293,294,295,296,297,298,291,292,293,294,295,296,293,294,295,296,297,298;
		setarray 'treasure_y,276,276,276,276,276,276,274,274,274,274,274,274,272,272,272,272,272,272,269,269,269,269,269,269;
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
arug_cas05.gat,146,315,3	script	イオス#F5	868,{
	if('guardian1_x[0] == 0) {
		setarray 'guardian1_x,130,128,128,128,128,128,128,128,128,128,110, 66;
		setarray 'guardian1_y, 60, 77, 77, 90, 77, 90,100, 77, 90,100, 96,157;
		setarray 'guardian2_x,156,172,172,154,172,154,156,172,154,156,155,211;
		setarray 'guardian2_y,101, 95, 95, 90, 95, 90, 77, 95, 90, 77, 60,159;
	}
	callfunc "AgitGuard",'guardian1_x,'guardian1_y,'guardian2_x,'guardian2_y;
	close;
}

arug_cas05.gat,0,0,0	script	Guardian#F5	111,{
	end;
OnKilled1:
	set 'guardian1,'guardian1-1;
	if('guardian1 < 2)
		callfunc "AgitCallGuardian",1,0,128,77;
	end;
OnKilled2:
	set 'guardian2,'guardian2-1;
	if('guardian2 < 2)
		callfunc "AgitCallGuardian",2,0,172,95;
	end;
OnTimer300000:
	callfunc "AgitCallGuardian",1,1,91,53;
	end;
OnTimer600000:
	callfunc "AgitCallGuardian",2,0,187,54;
	end;
OnTimer900000:
	callfunc "AgitCallGuardian",1,2,65,71;
	end;
OnTimer1200000:
	callfunc "AgitCallGuardian",2,0,212,67;
	end;
OnTimer1800000:
	callfunc "AgitCallGuardian",1,3,65,103;
	end;
OnTimer2100000:
	callfunc "AgitCallGuardian",2,0,211,105;
	end;
OnTimer2700000:
	callfunc "AgitCallGuardian",1,4,110,96;
	end;
OnTimer3000000:
	callfunc "AgitCallGuardian",2,0,155,60;
	end;
OnTimer3600000:
	callfunc "AgitCallGuardian",1,5,128,100;
	end;
OnTimer3900000:
	callfunc "AgitCallGuardian",2,0,156,77;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas05.gat","Guardian#F5::OnKilled1";
	killmonster "arug_cas05.gat","Guardian#F5::OnKilled2";
	set 'guardian1,0;
	set 'guardian2,0;
	end;
}

//============================================================
// 守護石
//------------------------------------------------------------
arug_cas05.gat,0,0,0	script	GuardianStone1#F5	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas05.gat",65,171,"--ja--",1907,1,"GuardianStone1#F5::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",1;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第1守護石#F5";
	misceffect 247,"第1守護石#F5";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas05.gat","GuardianStone1#F5::OnKilled";
	set 'status,0;
	end;
}

arug_cas05.gat,65,171,0	script	第1守護石#F5	844,{
	callfunc "AgitStone",1;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

arug_cas05.gat,0,0,0	script	GuardianStone2#F5	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas05.gat",212,149,"--ja--",1908,1,"GuardianStone2#F5::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",2;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第2守護石#F5";
	misceffect 247,"第2守護石#F5";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas05.gat","GuardianStone2#F5::OnKilled";
	set 'status,0;
	end;
}

arug_cas05.gat,212,149,0	script	第2守護石#F5	844,{
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
arug_cas05.gat,0,0,0	script	Barricade#F5	111,{
OnSet:
OnAgitStart:
	areasetcell "arug_cas05.gat",138,110,145,110,1;
	callguardian "arug_cas05.gat",139,111," ",1905,1,"Barricade#F5::OnKilled";
	callguardian "arug_cas05.gat",141,111," ",1905,1,"Barricade#F5::OnKilled";
	callguardian "arug_cas05.gat",143,111," ",1905,1,"Barricade#F5::OnKilled";
	callguardian "arug_cas05.gat",145,111," ",1905,1,"Barricade#F5::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas05.gat",138,110,145,110,0;
	killmonster "arug_cas05.gat","Barricade#F5::OnKilled";
	end;
OnKilled:
	end;
}

arug_cas05.gat,136,158,0	script	制御装置01#F5	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas05.gat",139,158,144,158,5;
	callguardian "arug_cas05.gat",140,157," ",1905,1,"制御装置01#F5::OnKilled";
	callguardian "arug_cas05.gat",142,157," ",1905,1,"制御装置01#F5::OnKilled";
	callguardian "arug_cas05.gat",144,157," ",1905,1,"制御装置01#F5::OnKilled";
	callguardian "arug_cas05.gat",139,156," ",1905,1,"制御装置01#F5::OnKilled";
	callguardian "arug_cas05.gat",141,156," ",1905,1,"制御装置01#F5::OnKilled";
	callguardian "arug_cas05.gat",143,156," ",1905,1,"制御装置01#F5::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第1バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas05.gat",139,158,144,158,0;
	killmonster "arug_cas05.gat","制御装置01#F5::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas05.gat",139,158,144,158,0;
	killmonster "arug_cas05.gat","制御装置01#F5::OnKilled";
	set 'status,0;
	end;
}

arug_cas05.gat,135,212,0	script	制御装置02#F5	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas05.gat",138,210,145,210,5;
	callguardian "arug_cas05.gat",140,209," ",1905,1,"制御装置02#F5::OnKilled";
	callguardian "arug_cas05.gat",142,209," ",1905,1,"制御装置02#F5::OnKilled";
	callguardian "arug_cas05.gat",144,209," ",1905,1,"制御装置02#F5::OnKilled";
	callguardian "arug_cas05.gat",139,208," ",1905,1,"制御装置02#F5::OnKilled";
	callguardian "arug_cas05.gat",141,208," ",1905,1,"制御装置02#F5::OnKilled";
	callguardian "arug_cas05.gat",143,208," ",1905,1,"制御装置02#F5::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第2バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas05.gat",138,210,145,210,0;
	killmonster "arug_cas05.gat","制御装置02#F5::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas05.gat",138,210,145,210,0;
	killmonster "arug_cas05.gat","制御装置02#F5::OnKilled";
	set 'status,0;
	end;
}

arug_cas05.gat,134,266,0	script	制御装置03#F5	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas05.gat",138,263,145,263,5;
	callguardian "arug_cas05.gat",139,262," ",1905,1,"制御装置03#F5::OnKilled";
	callguardian "arug_cas05.gat",141,262," ",1905,1,"制御装置03#F5::OnKilled";
	callguardian "arug_cas05.gat",143,262," ",1905,1,"制御装置03#F5::OnKilled";
	callguardian "arug_cas05.gat",145,262," ",1905,1,"制御装置03#F5::OnKilled";
	set 'count,4;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第3バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas05.gat",138,263,145,263,0;
	killmonster "arug_cas05.gat","制御装置03#F5::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas05.gat",138,263,145,263,0;
	killmonster "arug_cas05.gat","制御装置03#F5::OnKilled";
	set 'status,0;
	end;
}

//============================================================
// リンクフラッグ(A)
//------------------------------------------------------------
arug_cas05.gat,122,314,0	script	LF-01#F5	111,{
	setarray '@code,1,2;	//"第1拠点","第2拠点"
	setarray '@x, 84,197;
	setarray '@y,158,136;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,125,314,0	script	LF-02#F5	111,{
	setarray '@code,11,12;	//"防衛地域1-1","防衛地域1-2"
	setarray '@x, 65,211;
	setarray '@y, 94, 97;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,128,314,0	script	LF-03#F5	111,{
	setarray '@code,13,14;	//"防衛地域1-3","防衛地域1-4"
	setarray '@x,112,171;
	setarray '@y, 73, 73;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,131,314,0	script	LF-04#F5	111,{
	setarray '@code,21,22;	//"防衛地域2-1","防衛地域2-2"
	setarray '@x,112,172;
	setarray '@y,152,152;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,134,314,0	script	LF-05#F5	111,{
	setarray '@code,23,24;	//"防衛地域2-3","防衛地域2-4"
	setarray '@x,120,162;
	setarray '@y,186,186;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,149,314,0	script	LF-06#F5	111,{
	setarray '@code,31,32;	//"防衛地域3-1","防衛地域3-2"
	setarray '@x,116,164;
	setarray '@y,235,235;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,152,314,0	script	LF-07#F5	111,{
	setarray '@code,11,21,31;	//"防衛地域1-1","防衛地域2-1","防衛地域3-1"
	setarray '@x, 65,112,116;
	setarray '@y, 94,152,235;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,155,314,0	script	LF-08#F5	111,{
	setarray '@code,11,21,31;	//"防衛地域1-2","防衛地域2-2","防衛地域3-2"
	setarray '@x,211,172,164;
	setarray '@y, 97,152,235;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,158,314,0	script	LF-09#F5	111,{
	setarray '@code,14,24;	//"防衛地域1-4","防衛地域2-4"
	setarray '@x,171,162;
	setarray '@y, 73,186;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas05.gat,161,314,0	script	LF-10#F5	111,{
	callfunc "AgitLinkFlagB",1,321,57;
	close;
}

//============================================================
// リンクフラッグ(B)
//------------------------------------------------------------
-	script	#LinkFlag_F5	{
	callfunc "AgitLinkFlagB",0,121,318;
	close;
OnAgitInit:
OnFlagEmb_F5:
	if(substr(strnpcinfo(2),0,1) == "B")	//ギルドフラッグ型ならエンブレム更新
		flagemblem getcastledata("arug_cas05.gat",1);
	end;
}
arug_cas05.gat,45,158,0		duplicate(#LinkFlag_F5)	ヴァナディース#A01	111
arug_cas05.gat,226,156,0	duplicate(#LinkFlag_F5)	ヴァナディース#A02	111
arug_cas05.gat,134,62,0		duplicate(#LinkFlag_F5)	ヴァナディース#A03	111
arug_cas05.gat,149,62,0		duplicate(#LinkFlag_F5)	ヴァナディース#A04	111
arug_cas05.gat,123,154,0	duplicate(#LinkFlag_F5)	ヴァナディース#A05	111
arug_cas05.gat,160,154,0	duplicate(#LinkFlag_F5)	ヴァナディース#A06	111
arug_cas05.gat,135,205,0	duplicate(#LinkFlag_F5)	ヴァナディース#A07	111
arug_cas05.gat,148,205,0	duplicate(#LinkFlag_F5)	ヴァナディース#A08	111
arug_cas05.gat,134,260,0	duplicate(#LinkFlag_F5)	ヴァナディース#A09	111
arug_cas05.gat,149,260,0	duplicate(#LinkFlag_F5)	ヴァナディース#A10	111
arug_cas05.gat,148,103,4	duplicate(#LinkFlag_F5)	ヴァナディース#B11	722
arug_cas05.gat,135,103,4	duplicate(#LinkFlag_F5)	ヴァナディース#B12	722
arug_cas05.gat,63,51,7		duplicate(#LinkFlag_F5)	ヴァナディース#B13	722
arug_cas05.gat,214,51,1		duplicate(#LinkFlag_F5)	ヴァナディース#B14	722

//============================================================
// カプラ職員
//------------------------------------------------------------
arug_cas05.gat,315,98,5	script	カプラ職員::AgitKafra_F5	117,{
	callfunc "AgitKafra",18;
	close;
OnAgitInit:
	if(getcastledata("arug_cas05.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
arug_cas05.gat,328,98,3	script	執事	55,{
	callfunc "AgitSteward","F5",0,0,0,292,266;
	close;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
arug_cas05.gat,299,277,0	script	#AgitMaster_F5	111,{
	callfunc "AgitMaster",321,57;
	close;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_F5a	{
	callfunc "AgitEmblemFlag",3,"arug_cas05.gat",121,318;
	close;
OnAgitInit:
OnFlagEmb_F5:
	flagemblem getcastledata("arug_cas05.gat",1);
	end;
}
aru_gld.gat,289,103,6	duplicate(#GldFlag_F5a)	ヴァナディース#a01	722
aru_gld.gat,289,112,6	duplicate(#GldFlag_F5a)	ヴァナディース#a02	722
aru_gld.gat,350,98,6	duplicate(#GldFlag_F5a)	ヴァナディース#a03	722
aru_gld.gat,350,88,6	duplicate(#GldFlag_F5a)	ヴァナディース#a04	722

-	script	#GldFlag_F5b	{
	end;
OnAgitInit:
OnFlagEmb_F5:
	flagemblem getcastledata("arug_cas05.gat",1);
	end;
}
//rachel.gat,124,130,1	duplicate(#GldFlag_F5b)	ヴァナディース#b01	722

//============================================================
// 不思議なヒマワリ（アジトダンジョン）
//------------------------------------------------------------
arug_cas05.gat,312,154,3	script	不思議なヒマワリ#F5	977,{
	callfunc "AgitDungeonSE","arug_dun01.gat",200,385;
	close;
}
