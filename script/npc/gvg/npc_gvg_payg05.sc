//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Chung-Rim Guild 5	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
payg_cas05.gat,0,0,0	script	#AgitExe_C5	-1,{
OnAgitStart:
	callfunc "AgitEmperium",30,30,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","C5";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",30,30,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","C5";
	end;
OnAgitSummon:
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1277,9;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1208,10;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1262,5;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1102,5;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1115,1;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1129,11;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1282,4;
	areamonster "payg_cas05.gat",0,0,0,0,"--ja--",1253,5;
	monster "payg_cas05.gat",30,30,"--ja--",1150,1;
	monster "payg_cas05.gat",30,30,"--ja--",1115,1;
	monster "payg_cas05.gat",30,30,"--ja--",1208,6;
	monster "payg_cas05.gat",30,30,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
payg_cas05.gat,0,0,0	script	#AgitTreasure_C5	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1352,1353;
		setarray 'treasure_x,155,158,158,155,154,155,156,157,158,159,159,159,159,159,159,158,157,156,155,154,154,154,154,154;
		setarray 'treasure_y,134,134,131,131,135,135,135,135,135,135,134,133,132,131,130,130,130,130,130,130,131,132,133,134;
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
-	script	#GldFlag_C5a	{
	callfunc "AgitEmblemFlag",0,"payg_cas05.gat",243,27;
	close;
OnAgitInit:
OnFlagEmb_C5:
	flagemblem getcastledata("payg_cas05.gat",1);
	end;
}
pay_gld.gat,318,106,0	duplicate(#GldFlag_C5a)	ギルドフラッグ#C5a01	722
pay_gld.gat,208,268,4	duplicate(#GldFlag_C5a)	ギルドフラッグ#C5a02	722
pay_gld.gat,199,268,4	duplicate(#GldFlag_C5a)	ギルドフラッグ#C5a03	722
pay_gld.gat,190,277,3	duplicate(#GldFlag_C5a)	ギルドフラッグ#C5a04	722
pay_gld.gat,187,294,2	duplicate(#GldFlag_C5a)	ギルドフラッグ#C5a05	722

-	script	#GldFlag_C5b	{
	end;
OnAgitInit:
OnFlagEmb_C5:
	flagemblem getcastledata("payg_cas05.gat",1);
	end;
}
//payon.gat,123,322,4		duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b01	722
//payon.gat,166,161,3		duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b02	722
//payg_cas05.gat,32,249,4	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b03	722
//payg_cas05.gat,24,249,4	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b04	722
//payg_cas05.gat,62,271,0	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b05	722
//payg_cas05.gat,57,271,0	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b06	722
//payg_cas05.gat,55,252,2	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b07	722
//payg_cas05.gat,55,260,2	duplicate(#GldFlag_C5b)	ギルドフラッグ#C5b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
payg_cas05.gat,276,227,1	script	カプラ職員::AgitKafra_C5	117,{
	callfunc "AgitKafra",16;
	close;
OnAgitInit:
	if(getcastledata("payg_cas05.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
payg_cas05.gat,277,249,3	script	ナザブ	55,{
	callfunc "AgitSteward","C5",'guardian_id,'guardian_x,'guardian_y,153,137;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1285,	1285,	1285,	1285,	1286;
	setarray 'guardian_x,	19,	33,	266,	266,	263,	263,	250,	36;
	setarray 'guardian_y,	279,	260,	234,	279,	37,	21,	22,	36;
	for(set '@i,10; '@i <= 17; set '@i,'@i+1) {
		if(getcastledata("payg_cas05.gat",'@i))
			callguardian "payg_cas05.gat",'guardian_x['@i-10],'guardian_y['@i-10],"--ja--",'guardian_id['@i-10],1,"",'@i;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
payg_cas05.gat,161,136,0	script	#AgitMaster_C5	111,{
	callfunc "AgitMaster",277,250;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
payg_cas05.gat,249,15,0	script	#AgitDungeon_C5	111,{
	callfunc "AgitDungeon","gld_dun01.gat",223,202;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
payg_cas05.gat,157,132,0	script	#AgitBanWarp_C5	139,6,6,{
	callfunc "AgitBanWarp","payon.gat",100,100;
	close;
}
