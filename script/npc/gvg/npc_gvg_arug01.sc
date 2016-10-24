//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valfreyja Guild 1	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
arug_cas01.gat,0,0,0	script	#AgitExe_F1	-1,{
OnAgitStart:
	callfunc "AgitEmperium",87,219,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","F1";
	callfunc "AgitBreakSE","F1";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",87,219,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","F1";
	end;
OnAgitSummon:
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "arug_cas01.gat",0,0,0,0,"--ja--",1272,1;
	monster "arug_cas01.gat",87,219,"--ja--",1272,1;
	monster "arug_cas01.gat",87,219,"--ja--",1270,4;
	monster "arug_cas01.gat",87,219,"--ja--",1268,1;
	monster "arug_cas01.gat",87,219,"--ja--",1219,1;
	monster "arug_cas01.gat",87,219,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
arug_cas01.gat,0,0,0	script	#AgitTreasure_F1	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1943;
		setarray 'treasure_x,251,252,253,254,255,256,257,258,251,252,253,254,255,256,257,258,251,252,253,254,255,256,257,258;
		setarray 'treasure_y,369,369,369,369,368,368,368,368,367,367,367,367,366,366,366,366,365,365,365,365,364,364,364,364;
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
arug_cas01.gat,112,193,1	script	ブレイス#F1	868,{
	if('guardian1_x[0] == 0) {
		setarray 'guardian1_x,233,252,252,232,252,232,201,252,232,201,224,195;
		setarray 'guardian1_y, 83, 81, 81,108, 81,108,130, 81,108,130,168,250;
		setarray 'guardian2_x,294,256,256,240,256,240,246,256,240,246,235,292;
		setarray 'guardian2_y,210,203,203,133,203,133, 92,203,133, 92,132,188;
	}
	callfunc "AgitGuard",'guardian1_x,'guardian1_y,'guardian2_x,'guardian2_y;
	close;
}

arug_cas01.gat,0,0,0	script	Guardian#F1	111,{
	end;
OnKilled1:
	set 'guardian1,'guardian1-1;
	if('guardian1 < 2)
		callfunc "AgitCallGuardian",1,0,222,129;
	end;
OnKilled2:
	set 'guardian2,'guardian2-1;
	if('guardian2 < 2)
		callfunc "AgitCallGuardian",2,0,242,151;
	end;
OnTimer300000:
	callfunc "AgitCallGuardian",1,1,196,137;
	end;
OnTimer600000:
	callfunc "AgitCallGuardian",2,0,235,132;
	end;
OnTimer900000:
	callfunc "AgitCallGuardian",1,2,269,89;
	end;
OnTimer1200000:
	callfunc "AgitCallGuardian",2,0,246,92;
	end;
OnTimer1800000:
	callfunc "AgitCallGuardian",1,3,252,81;
	end;
OnTimer2100000:
	callfunc "AgitCallGuardian",2,0,240,133;
	end;
OnTimer2700000:
	callfunc "AgitCallGuardian",1,4,201,130;
	end;
OnTimer3000000:
	callfunc "AgitCallGuardian",2,0,256,203;
	end;
OnTimer3600000:
	callfunc "AgitCallGuardian",1,5,224,168;
	end;
OnTimer3900000:
	callfunc "AgitCallGuardian",2,0,254,95;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas01.gat","Guardian#F1::OnKilled1";
	killmonster "arug_cas01.gat","Guardian#F1::OnKilled2";
	set 'guardian1,0;
	set 'guardian2,0;
	end;
}

//============================================================
// 守護石
//------------------------------------------------------------
arug_cas01.gat,0,0,0	script	GuardianStone1#F1	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas01.gat",210,234,"--ja--",1907,1,"GuardianStone1#F1::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",1;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第1守護石#F1";
	misceffect 247,"第1守護石#F1";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas01.gat","GuardianStone1#F1::OnKilled";
	set 'status,0;
	end;
}

arug_cas01.gat,211,234,0	script	第1守護石#F1	844,{
	callfunc "AgitStone",1;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

arug_cas01.gat,0,0,0	script	GuardianStone2#F1	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas01.gat",308,189,"--ja--",1908,1,"GuardianStone2#F1::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",2;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第2守護石#F1";
	misceffect 247,"第2守護石#F1";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas01.gat","GuardianStone2#F1::OnKilled";
	set 'status,0;
	end;
}

arug_cas01.gat,308,189,0	script	第2守護石#F1	844,{
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
arug_cas01.gat,0,0,0	script	Barricade#F1	111,{
OnSet:
OnAgitStart:
	areasetcell "arug_cas01.gat",238,74,245,74,1;
	callguardian "arug_cas01.gat",239,73," ",1905,1,"Barricade#F1::OnKilled";
	callguardian "arug_cas01.gat",241,73," ",1905,1,"Barricade#F1::OnKilled";
	callguardian "arug_cas01.gat",243,73," ",1905,1,"Barricade#F1::OnKilled";
	callguardian "arug_cas01.gat",245,73," ",1905,1,"Barricade#F1::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas01.gat",238,74,245,74,0;
	killmonster "arug_cas01.gat","Barricade#F1::OnKilled";
	end;
OnKilled:
	end;
}

arug_cas01.gat,247,52,0	script	制御装置01#F1	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas01.gat",239,53,246,53,5;
	callguardian "arug_cas01.gat",239,55," ",1905,1,"制御装置01#F1::OnKilled";
	callguardian "arug_cas01.gat",241,55," ",1905,1,"制御装置01#F1::OnKilled";
	callguardian "arug_cas01.gat",243,55," ",1905,1,"制御装置01#F1::OnKilled";
	callguardian "arug_cas01.gat",240,54," ",1905,1,"制御装置01#F1::OnKilled";
	callguardian "arug_cas01.gat",242,54," ",1905,1,"制御装置01#F1::OnKilled";
	callguardian "arug_cas01.gat",244,54," ",1905,1,"制御装置01#F1::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第1バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas01.gat",239,53,246,53,0;
	killmonster "arug_cas01.gat","制御装置01#F1::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas01.gat",239,53,246,53,0;
	killmonster "arug_cas01.gat","制御装置01#F1::OnKilled";
	set 'status,0;
	end;
}

arug_cas01.gat,118,131,0	script	制御装置02#F1	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas01.gat",107,124,112,124,5;
	callguardian "arug_cas01.gat",107,122," ",1905,1,"制御装置02#F1::OnKilled";
	callguardian "arug_cas01.gat",109,122," ",1905,1,"制御装置02#F1::OnKilled";
	callguardian "arug_cas01.gat",111,122," ",1905,1,"制御装置02#F1::OnKilled";
	callguardian "arug_cas01.gat",108,123," ",1905,1,"制御装置02#F1::OnKilled";
	callguardian "arug_cas01.gat",110,123," ",1905,1,"制御装置02#F1::OnKilled";
	callguardian "arug_cas01.gat",112,123," ",1905,1,"制御装置02#F1::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第2バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas01.gat",107,124,112,124,0;
	killmonster "arug_cas01.gat","制御装置02#F1::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas01.gat",107,124,112,124,0;
	killmonster "arug_cas01.gat","制御装置02#F1::OnKilled";
	set 'status,0;
	end;
}

arug_cas01.gat,82,172,0	script	制御装置03#F1	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas01.gat",84,171,91,171,5;
	callguardian "arug_cas01.gat",84,170," ",1905,1,"制御装置03#F1::OnKilled";
	callguardian "arug_cas01.gat",86,170," ",1905,1,"制御装置03#F1::OnKilled";
	callguardian "arug_cas01.gat",88,170," ",1905,1,"制御装置03#F1::OnKilled";
	callguardian "arug_cas01.gat",90,170," ",1905,1,"制御装置03#F1::OnKilled";
	set 'count,4;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第3バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas01.gat",84,171,91,171,0;
	killmonster "arug_cas01.gat","制御装置03#F1::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas01.gat",84,171,91,171,0;
	killmonster "arug_cas01.gat","制御装置03#F1::OnKilled";
	set 'status,0;
	end;
}

//============================================================
// リンクフラッグ(A)
//------------------------------------------------------------
arug_cas01.gat,74,232,0	script	LF-01#F1	111,{
	setarray '@code,1,2;	//"第1拠点","第2拠点"
	setarray '@x,158,297;
	setarray '@y,237,248;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,77,232,0	script	LF-02#F1	111,{
	setarray '@code,11,12;	//"防衛地域1-1","防衛地域1-2"
	setarray '@x,197,245;
	setarray '@y,144,103;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,80,232,0	script	LF-03#F1	111,{
	setarray '@code,21,22;	//"防衛地域2-1","防衛地域2-2"
	setarray '@x,256,186;
	setarray '@y, 35, 26;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,83,232,0	script	LF-04#F1	111,{
	setarray '@code,23,24;	//"防衛地域2-3","防衛地域2-4"
	setarray '@x,146,176;
	setarray '@y, 65,111;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,86,232,0	script	LF-05#F1	111,{
	setarray '@code,31,32;	//"防衛地域3-1","防衛地域3-2"
	setarray '@x, 94,126;
	setarray '@y,126,126;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,89,232,0	script	LF-06#F1	111,{
	setarray '@code,33,34;	//"防衛地域3-3","防衛地域3-4"
	setarray '@x, 68,105;
	setarray '@y,171,182;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,92,232,0	script	LF-07#F1	111,{
	setarray '@code,100;	//"拠点への道"
	setarray '@x,233;
	setarray '@y,130;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,95,232,0	script	LF-08#F1	111,{
	setarray '@code,111,121,131;	//"区域1-1","区域2-1","区域3-1"
	setarray '@x,197,256,146;
	setarray '@y,144, 35, 65;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,98,232,0	script	LF-09#F1	111,{
	setarray '@code,112,122,132;	//"区域1-2","区域2-2","区域3-2"
	setarray '@x,245,186, 68;
	setarray '@y,103, 26,171;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas01.gat,101,232,0	script	LF-10#F1	111,{
	callfunc "AgitLinkFlagB",1,121,357;
	close;
}

//============================================================
// リンクフラッグ(B)
//------------------------------------------------------------
-	script	#LinkFlag_F1	{
	callfunc "AgitLinkFlagB",0,67,193;
	close;
OnAgitInit:
OnFlagEmb_F1:
	if(substr(strnpcinfo(2),0,1) == "B")	//ギルドフラッグ型ならエンブレム更新
		flagemblem getcastledata("arug_cas01.gat",1);
	end;
}
arug_cas01.gat,72,176,0		duplicate(#LinkFlag_F1)	マルドル#A01	111
arug_cas01.gat,103,186,0	duplicate(#LinkFlag_F1)	マルドル#A02	111
arug_cas01.gat,92,126,0		duplicate(#LinkFlag_F1)	マルドル#A03	111
arug_cas01.gat,127,126,0	duplicate(#LinkFlag_F1)	マルドル#A04	111
arug_cas01.gat,150,102,0	duplicate(#LinkFlag_F1)	マルドル#A05	111
arug_cas01.gat,208,68,0		duplicate(#LinkFlag_F1)	マルドル#A06	111
arug_cas01.gat,249,52,0		duplicate(#LinkFlag_F1)	マルドル#A07	111
arug_cas01.gat,234,76,0		duplicate(#LinkFlag_F1)	マルドル#A08	111
arug_cas01.gat,249,76,0		duplicate(#LinkFlag_F1)	マルドル#A09	111
arug_cas01.gat,204,142,0	duplicate(#LinkFlag_F1)	マルドル#A10	111
arug_cas01.gat,183,244,0	duplicate(#LinkFlag_F1)	マルドル#A11	111
arug_cas01.gat,292,219,0	duplicate(#LinkFlag_F1)	マルドル#A12	111
arug_cas01.gat,102,120,4	duplicate(#LinkFlag_F1)	マルドル#B13	722
arug_cas01.gat,117,120,4	duplicate(#LinkFlag_F1)	マルドル#B14	722
arug_cas01.gat,233,140,4	duplicate(#LinkFlag_F1)	マルドル#B15	722

//============================================================
// カプラ職員
//------------------------------------------------------------
arug_cas01.gat,31,362,3	script	カプラ職員::AgitKafra_F1	117,{
	callfunc "AgitKafra",18;
	close;
OnAgitInit:
	if(getcastledata("arug_cas01.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
arug_cas01.gat,92,380,3	script	執事	55,{
	callfunc "AgitSteward","F1",0,0,0,250,363;
	close;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
arug_cas01.gat,259,371,0	script	#AgitMaster_F1	111,{
	callfunc "AgitMaster",121,357;
	close;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_F1a	{
	callfunc "AgitEmblemFlag",3,"arug_cas01.gat",67,193;
	close;
OnAgitInit:
OnFlagEmb_F1:
	flagemblem getcastledata("arug_cas01.gat",1);
	end;
}
aru_gld.gat,164,270,4	duplicate(#GldFlag_F1a)	マルドル#a01	722
aru_gld.gat,142,235,4	duplicate(#GldFlag_F1a)	マルドル#a02	722
aru_gld.gat,164,245,5	duplicate(#GldFlag_F1a)	マルドル#a03	722
aru_gld.gat,182,255,5	duplicate(#GldFlag_F1a)	マルドル#a04	722

-	script	#GldFlag_F1b	{
	end;
OnAgitInit:
OnFlagEmb_F1:
	flagemblem getcastledata("arug_cas01.gat",1);
	end;
}
//rachel.gat,124,120,3	duplicate(#GldFlag_F1b)	マルドル#b01	722

//============================================================
// 不思議なヒマワリ（アジトダンジョン）
//------------------------------------------------------------
arug_cas01.gat,157,345,3	script	不思議なヒマワリ#F1	977,{
	callfunc "AgitDungeonSE","arug_dun01.gat",350,350;
	close;
}
