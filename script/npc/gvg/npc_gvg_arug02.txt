//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valfreyja Guild 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
arug_cas02.gat,0,0,0	script	#AgitExe_F2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",89,256,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","F2";
	callfunc "AgitBreakSE","F2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",89,256,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","F2";
	end;
OnAgitSummon:
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "arug_cas02.gat",0,0,0,0,"--ja--",1272,1;
	monster "arug_cas02.gat",89,256,"--ja--",1272,1;
	monster "arug_cas02.gat",89,256,"--ja--",1270,4;
	monster "arug_cas02.gat",89,256,"--ja--",1268,1;
	monster "arug_cas02.gat",89,256,"--ja--",1219,1;
	monster "arug_cas02.gat",89,256,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
arug_cas02.gat,0,0,0	script	#AgitTreasure_F2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1944;
		setarray 'treasure_x,382,383,384,385,386,387,384,385,386,387,388,389,382,383,384,385,386,387,384,385,386,387,388,389;
		setarray 'treasure_y,231,231,231,231,231,231,230,230,230,230,230,230,225,225,225,225,225,225,224,224,224,224,224,224;
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
arug_cas02.gat,38,259,5	script	ユネメス#F2	868,{
	if('guardian1_x[0] == 0) {
		setarray 'guardian1_x,104, 67, 67, 67, 67, 67,113, 67, 67,113,122, 20;
		setarray 'guardian1_y, 32, 36, 36, 85, 36, 85, 87, 36, 85, 87,112,169;
		setarray 'guardian2_x,175,204,204,211,204,211,209,204,211,209,161,268;
		setarray 'guardian2_y, 31, 32, 32, 63, 32, 63, 88, 32, 63, 88, 91,169;
	}
	callfunc "AgitGuard",'guardian1_x,'guardian1_y,'guardian2_x,'guardian2_y;
	close;
}

arug_cas02.gat,0,0,0	script	Guardian#F2	111,{
	end;
OnKilled1:
	set 'guardian1,'guardian1-1;
	if('guardian1 < 2)
		callfunc "AgitCallGuardian",1,0,67,85;
	end;
OnKilled2:
	set 'guardian2,'guardian2-1;
	if('guardian2 < 2)
		callfunc "AgitCallGuardian",2,0,211,63;
	end;
OnTimer300000:
	callfunc "AgitCallGuardian",1,1,67,60;
	end;
OnTimer600000:
	callfunc "AgitCallGuardian",2,0,186,170;
	end;
OnTimer900000:
	callfunc "AgitCallGuardian",1,2,90,167;
	end;
OnTimer1200000:
	callfunc "AgitCallGuardian",2,0,183,121;
	end;
OnTimer1800000:
	callfunc "AgitCallGuardian",1,3,91,119;
	end;
OnTimer2100000:
	callfunc "AgitCallGuardian",2,0,150,110;
	end;
OnTimer2700000:
	callfunc "AgitCallGuardian",1,4,122,112;
	end;
OnTimer3000000:
	callfunc "AgitCallGuardian",2,0,161,91;
	end;
OnTimer3600000:
	callfunc "AgitCallGuardian",1,5,20,169;
	end;
OnTimer3900000:
	callfunc "AgitCallGuardian",2,0,209,88;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas02.gat","Guardian#F2::OnKilled1";
	killmonster "arug_cas02.gat","Guardian#F2::OnKilled2";
	set 'guardian1,0;
	set 'guardian2,0;
	end;
}

//============================================================
// 守護石
//------------------------------------------------------------
arug_cas02.gat,0,0,0	script	GuardianStone1#F2	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas02.gat",33,168,"--ja--",1907,1,"GuardianStone1#F2::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",1;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第1守護石#F2";
	misceffect 247,"第1守護石#F2";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas02.gat","GuardianStone1#F2::OnKilled";
	set 'status,0;
	end;
}

arug_cas02.gat,33,168,0	script	第1守護石#F2	844,{
	callfunc "AgitStone",1;
	close;
OnInit:
OnAgitEnd:
	hideonnpc;
	end;
}

arug_cas02.gat,0,0,0	script	GuardianStone2#F2	111,{
OnAgitStart:
OnRepair:
	callguardian "arug_cas02.gat",245,168,"--ja--",1908,1,"GuardianStone2#F2::OnKilled";
	set 'status,0;
	end;
OnKilled:
	callfunc "AgitStoneBreak",2;
	end;
OnSet:
OnTimer300000:
	hideoffnpc "第2守護石#F2";
	misceffect 247,"第2守護石#F2";
	set 'status,2;
	stopnpctimer;
	end;
OnAgitEnd:
	stopnpctimer;
	killmonster "arug_cas02.gat","GuardianStone2#F2::OnKilled";
	set 'status,0;
	end;
}

arug_cas02.gat,245,168,0	script	第2守護石#F2	844,{
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
arug_cas02.gat,0,0,0	script	Barricade#F2	111,{
OnSet:
OnAgitStart:
	areasetcell "arug_cas02.gat",136,136,143,136,1;
	callguardian "arug_cas02.gat",137,137," ",1905,1,"Barricade#F2::OnKilled";
	callguardian "arug_cas02.gat",139,137," ",1905,1,"Barricade#F2::OnKilled";
	callguardian "arug_cas02.gat",141,137," ",1905,1,"Barricade#F2::OnKilled";
	callguardian "arug_cas02.gat",143,137," ",1905,1,"Barricade#F2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas02.gat",136,136,143,136,0;
	killmonster "arug_cas02.gat","Barricade#F2::OnKilled";
	end;
OnKilled:
	end;
}

arug_cas02.gat,143,228,0	script	制御装置01#F2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas02.gat",150,223,161,223,5;
	callguardian "arug_cas02.gat",151,222," ",1905,1,"制御装置01#F2::OnKilled";
	callguardian "arug_cas02.gat",153,222," ",1905,1,"制御装置01#F2::OnKilled";
	callguardian "arug_cas02.gat",155,222," ",1905,1,"制御装置01#F2::OnKilled";
	callguardian "arug_cas02.gat",157,222," ",1905,1,"制御装置01#F2::OnKilled";
	callguardian "arug_cas02.gat",159,222," ",1905,1,"制御装置01#F2::OnKilled";
	callguardian "arug_cas02.gat",161,222," ",1905,1,"制御装置01#F2::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第1バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas02.gat",150,223,161,223,0;
	killmonster "arug_cas02.gat","制御装置01#F2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas02.gat",150,223,161,223,0;
	killmonster "arug_cas02.gat","制御装置01#F2::OnKilled";
	set 'status,0;
	end;
}

arug_cas02.gat,118,356,0	script	制御装置02#F2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas02.gat",125,342,125,349,5;
	callguardian "arug_cas02.gat",126,343," ",1905,1,"制御装置02#F2::OnKilled";
	callguardian "arug_cas02.gat",126,345," ",1905,1,"制御装置02#F2::OnKilled";
	callguardian "arug_cas02.gat",126,347," ",1905,1,"制御装置02#F2::OnKilled";
	callguardian "arug_cas02.gat",127,344," ",1905,1,"制御装置02#F2::OnKilled";
	callguardian "arug_cas02.gat",127,346," ",1905,1,"制御装置02#F2::OnKilled";
	callguardian "arug_cas02.gat",127,348," ",1905,1,"制御装置02#F2::OnKilled";
	set 'count,6;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第2バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas02.gat",125,342,125,349,0;
	killmonster "arug_cas02.gat","制御装置02#F2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas02.gat",125,342,125,349,0;
	killmonster "arug_cas02.gat","制御装置02#F2::OnKilled";
	set 'status,0;
	end;
}

arug_cas02.gat,56,308,0	script	制御装置03#F2	111,{
	callfunc "AgitBarricade";
	close;
OnSet:
OnAgitStart:
	set 'status,0;
	areasetcell "arug_cas02.gat",38,314,49,314,5;
	callguardian "arug_cas02.gat",40,315," ",1905,1,"制御装置03#F2::OnKilled";
	callguardian "arug_cas02.gat",42,315," ",1905,1,"制御装置03#F2::OnKilled";
	callguardian "arug_cas02.gat",44,315," ",1905,1,"制御装置03#F2::OnKilled";
	callguardian "arug_cas02.gat",46,315," ",1905,1,"制御装置03#F2::OnKilled";
	set 'count,4;
	end;
OnKilled:
	set 'count,'count-1;
	if('count > 0)
		end;
	set 'status,1;
	announce "第3バリケードが突破されました!!",0x9,0xFF0000;
	areasetcell "arug_cas02.gat",38,314,49,314,0;
	killmonster "arug_cas02.gat","制御装置03#F2::OnKilled";
	end;
OnReset:
OnAgitEnd:
	areasetcell "arug_cas02.gat",38,314,49,314,0;
	killmonster "arug_cas02.gat","制御装置03#F2::OnKilled";
	set 'status,0;
	end;
}

//============================================================
// リンクフラッグ(A)
//------------------------------------------------------------
arug_cas02.gat,98,270,0	script	LF-01#F2	111,{
	setarray '@code,1,2;	//"第1拠点","第2拠点"
	setarray '@x, 10,268;
	setarray '@y,187,187;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,266,0	script	LF-02#F2	111,{
	setarray '@code,11,12;	//"防衛地域1-1","防衛地域1-2"
	setarray '@x, 66,212;
	setarray '@y, 31, 31;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,262,0	script	LF-03#F2	111,{
	setarray '@code,13,14;	//"防衛地域1-3","防衛地域1-4"
	setarray '@x, 90,188;
	setarray '@y,120,119;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,258,0	script	LF-04#F2	111,{
	setarray '@code,21,22;	//"防衛地域2-1","防衛地域2-2"
	setarray '@x,119,159;
	setarray '@y,183,183;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,253,0	script	LF-05#F2	111,{
	setarray '@code,23,24;	//"防衛地域2-3","防衛地域2-4"
	setarray '@x,156,174;
	setarray '@y,324,372;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,249,0	script	LF-06#F2	111,{
	setarray '@code,31,32;	//"防衛地域3-1","防衛地域3-2"
	setarray '@x, 28, 57;
	setarray '@y,325,325;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,245,0	script	LF-07#F2	111,{
	setarray '@code,102,103;	//"中央2区画","中央3区画"
	setarray '@x,156, 43;
	setarray '@y,263,354;
	callfunc "AgitLinkFlagA",'@code,'@x,'@y;
	close;
}

arug_cas02.gat,98,241,0	script	LF-08#F2	111,{
	callfunc "AgitLinkFlagB",1,387,323;
	close;
}

//============================================================
// リンクフラッグ(B)
//------------------------------------------------------------
-	script	#LinkFlag_F2	{
	callfunc "AgitLinkFlagB",0,43,256;
	close;
OnAgitInit:
OnFlagEmb_F2:
	if(substr(strnpcinfo(2),0,1) == "B")	//ギルドフラッグ型ならエンブレム更新
		flagemblem getcastledata("arug_cas02.gat",1);
	end;
}
arug_cas02.gat,216,92,0		duplicate(#LinkFlag_F2)	スュール#A01	111
arug_cas02.gat,63,92,0		duplicate(#LinkFlag_F2)	スュール#A02	111
arug_cas02.gat,127,133,0	duplicate(#LinkFlag_F2)	スュール#A03	111
arug_cas02.gat,152,133,0	duplicate(#LinkFlag_F2)	スュール#A04	111
arug_cas02.gat,149,218,0	duplicate(#LinkFlag_F2)	スュール#A05	111
arug_cas02.gat,162,218,0	duplicate(#LinkFlag_F2)	スュール#A06	111
arug_cas02.gat,128,350,0	duplicate(#LinkFlag_F2)	スュール#A07	111
arug_cas02.gat,128,341,0	duplicate(#LinkFlag_F2)	スュール#A08	111
arug_cas02.gat,49,317,0		duplicate(#LinkFlag_F2)	スュール#A09	111
arug_cas02.gat,38,317,0		duplicate(#LinkFlag_F2)	スュール#A10	111
arug_cas02.gat,9,190,0		duplicate(#LinkFlag_F2)	スュール#A11	111
arug_cas02.gat,271,190,0	duplicate(#LinkFlag_F2)	スュール#A12	111
arug_cas02.gat,129,178,4	duplicate(#LinkFlag_F2)	スュール#B13	722
arug_cas02.gat,149,178,4	duplicate(#LinkFlag_F2)	スュール#B14	722
arug_cas02.gat,132,38,4		duplicate(#LinkFlag_F2)	スュール#B15	722
arug_cas02.gat,147,38,4		duplicate(#LinkFlag_F2)	スュール#B16	722

//============================================================
// カプラ職員
//------------------------------------------------------------
arug_cas02.gat,354,326,3	script	カプラ職員::AgitKafra_F2	117,{
	callfunc "AgitKafra",18;
	close;
OnAgitInit:
	if(getcastledata("arug_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
arug_cas02.gat,303,341,3	script	執事	55,{
	callfunc "AgitSteward","F2",0,0,0,382,227;
	close;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
arug_cas02.gat,386,227,0	script	#AgitMaster_F2	111,{
	callfunc "AgitMaster",387,323;
	close;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_F2a	{
	callfunc "AgitEmblemFlag",3,"arug_cas02.gat",43,256;
	close;
OnAgitInit:
OnFlagEmb_F2:
	flagemblem getcastledata("arug_cas02.gat",1);
	end;
}
aru_gld.gat,80,41,6	duplicate(#GldFlag_F2a)	スュール#a01	722
aru_gld.gat,80,52,6	duplicate(#GldFlag_F2a)	スュール#a02	722
aru_gld.gat,120,83,5	duplicate(#GldFlag_F2a)	スュール#a03	722

-	script	#GldFlag_F2b	{
	end;
OnAgitInit:
OnFlagEmb_F2:
	flagemblem getcastledata("arug_cas02.gat",1);
	end;
}
//rachel.gat,136,120,5	duplicate(#GldFlag_F2b)	スュール#b01	722

//============================================================
// 不思議なヒマワリ（アジトダンジョン）
//------------------------------------------------------------
arug_cas02.gat,350,294,3	script	不思議なヒマワリ#F2	977,{
	callfunc "AgitDungeonSE","arug_dun01.gat",350,50;
	close;
}
