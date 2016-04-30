//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Chung-Rim Guild 4	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
payg_cas04.gat,0,0,0	script	#AgitExe_C4	-1,{
OnAgitStart:
	callfunc "AgitEmperium",270,28,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","C4";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",270,27,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","C4";
	end;
OnAgitSummon:
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1277,9;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1208,10;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1262,5;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1102,5;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1115,1;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1129,11;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1282,4;
	areamonster "payg_cas04.gat",0,0,0,0,"--ja--",1253,5;
	monster "payg_cas04.gat",270,27,"--ja--",1150,1;
	monster "payg_cas04.gat",270,27,"--ja--",1115,1;
	monster "payg_cas04.gat",270,27,"--ja--",1208,6;
	monster "payg_cas04.gat",270,27,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
payg_cas04.gat,0,0,0	script	#AgitTreasure_C4	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1350,1351;
		setarray 'treasure_x,146,147,147,146,144,145,146,147,148,149,149,149,149,149,149,148,147,146,145,144,144,144,144,144;
		setarray 'treasure_y, 48, 48, 47, 47, 50, 50, 50, 50, 50, 50, 49, 48, 47, 46, 45, 45, 45, 45, 45, 45, 46, 47, 48, 49;
	}
	callfunc "AgitTreasure",'treasure_id,'treasure_x,'treasure_y;
	end;
OnKilled:
	// dummy event
	end;
}

//============================================================
// ギルドフラッグ
//------------------------------------------------------------
-	script	#GldFlag_C4a	{
	callfunc "AgitEmblemFlag",0,"payg_cas04.gat",40,235;
	close;
OnAgitInit:
OnFlagEmb_C4:
	flagemblem getcastledata("payg_cas04.gat",1);
	end;
}
pay_gld.gat,330,106,0	duplicate(#GldFlag_C4a)	ギルドフラッグ#C4a01	722
pay_gld.gat,137,160,0	duplicate(#GldFlag_C4a)	ギルドフラッグ#C4a02	722
pay_gld.gat,143,160,0	duplicate(#GldFlag_C4a)	ギルドフラッグ#C4a03	722
pay_gld.gat,133,151,2	duplicate(#GldFlag_C4a)	ギルドフラッグ#C4a04	722
pay_gld.gat,153,166,1	duplicate(#GldFlag_C4a)	ギルドフラッグ#C4a05	722

-	script	#GldFlag_C4b	{
	end;
OnAgitInit:
OnFlagEmb_C4:
	flagemblem getcastledata("payg_cas04.gat",1);
	end;
}
//payon.gat,118,322,4		duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b01	722
//payon.gat,166,165,3		duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b02	722
//payg_cas04.gat,255,259,0	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b03	722
//payg_cas04.gat,248,259,0	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b04	722
//payg_cas04.gat,248,168,6	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b05	722
//payg_cas04.gat,248,160,6	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b06	722
//payg_cas04.gat,232,181,4	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b07	722
//payg_cas04.gat,239,181,4	duplicate(#GldFlag_C4b)	ギルドフラッグ#C4b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
payg_cas04.gat,40,235,1	script	カプラ職員::AgitKafra_C4	117,{
	callfunc "AgitKafra",16;
	close;
OnAgitInit:
	if(getcastledata("payg_cas04.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
payg_cas04.gat,38,284,3	script	ディージェイ	55,{
	callfunc "AgitSteward","C4",'guardian_id,'guardian_x,'guardian_y,151,47;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1285,	1285,	1285,	1285,	1286;
	setarray 'guardian_x,	251,	232,	231,	32,	32,	35,	36,	270;
	setarray 'guardian_y,	212,	212,	175,	287,	232,	45,	17,	41;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("payg_cas04.gat",'@i+10))
			callguardian "payg_cas04.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
payg_cas04.gat,151,47,0	script	#AgitMaster_C4	111,{
	callfunc "AgitMaster",38,285;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
payg_cas04.gat,52,48,0	script	#AgitDungeon_C4	111,{
	callfunc "AgitDungeon","gld_dun01.gat",186,39;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
payg_cas04.gat,147,48,0	script	#AgitBanWarp_C4	139,6,6,{
	callfunc "AgitBanWarp","payon.gat",100,100;
	close;
}
