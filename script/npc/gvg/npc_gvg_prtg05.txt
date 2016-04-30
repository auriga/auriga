//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valkyrie Realms 5	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
prtg_cas05.gat,0,0,0	script	#AgitExe_V5	-1,{
OnAgitStart:
	callfunc "AgitEmperium",266,266,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","V5";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",266,266,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","V5";
	end;
OnAgitSummon:
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1163,15;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1132,10;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1219,5;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1268,5;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1251,1;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1252,1;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1259,2;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1283,2;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "prtg_cas05.gat",0,0,0,0,"--ja--",1200,1;
	monster "prtg_cas05.gat",266,266,"--ja--",1268,1;
	monster "prtg_cas05.gat",266,266,"--ja--",1251,1;
	monster "prtg_cas05.gat",266,266,"--ja--",1252,1;
	monster "prtg_cas05.gat",266,266,"--ja--",1219,2;
	monster "prtg_cas05.gat",266,266,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
prtg_cas05.gat,0,0,0	script	#AgitTreasure_V5	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1362,1363;
		setarray 'treasure_x,275,276,276,275,273,274,275,276,277,278,278,278,278,278,278,277,276,275,274,273,273,273,273,273;
		setarray 'treasure_y,178,178,177,177,180,180,180,180,180,180,179,178,177,176,175,175,175,175,175,175,176,177,178,179;
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
-	script	#GldFlag_V5a	{
	callfunc "AgitEmblemFlag",0,"prtg_cas05.gat",52,41;
	close;
OnAgitInit:
OnFlagEmb_V5:
	flagemblem getcastledata("prtg_cas05.gat",1);
	end;
}
prt_gld.gat,167,213,5	duplicate(#GldFlag_V5a)	ギルドフラッグ#V5a01	722
prt_gld.gat,199,243,2	duplicate(#GldFlag_V5a)	ギルドフラッグ#V5a02	722
prt_gld.gat,199,236,2	duplicate(#GldFlag_V5a)	ギルドフラッグ#V5a03	722
prt_gld.gat,197,243,2	duplicate(#GldFlag_V5a)	ギルドフラッグ#V5a04	722
prt_gld.gat,197,236,2	duplicate(#GldFlag_V5a)	ギルドフラッグ#V5a05	722

-	script	#GldFlag_V5b	{
	end;
OnAgitInit:
OnFlagEmb_V5:
	flagemblem getcastledata("prtg_cas05.gat",1);
	end;
}
//prontera.gat,165,194,5	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b01	722
//prtg_cas05.gat,19,247,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b02	722
//prtg_cas05.gat,19,243,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b03	722
//prtg_cas05.gat,26,247,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b04	722
//prtg_cas05.gat,26,243,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b05	722
//prtg_cas05.gat,249,289,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b06	722
//prtg_cas05.gat,256,289,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b07	722
//prtg_cas05.gat,253,271,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b08	722
//prtg_cas05.gat,273,257,4	duplicate(#GldFlag_V5b)	ギルドフラッグ#V5b09	722

//============================================================
// カプラ職員
//------------------------------------------------------------
prtg_cas05.gat,52,41,4	script	カプラ職員::AgitKafra_V5	117,{
	callfunc "AgitKafra",14;
	close;
OnAgitInit:
	if(getcastledata("prtg_cas05.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
prtg_cas05.gat,36,37,4	script	レイノ	55,{
	callfunc "AgitSteward","V5",'guardian_id,'guardian_x,'guardian_y,281,176;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1286,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	266,	287,	245,	236,	251,	278,	32,	44;
	setarray 'guardian_y,	262,	280,	250,	63,	63,	71,	253,	248;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("prtg_cas05.gat",'@i+10))
			callguardian "prtg_cas05.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
prtg_cas05.gat,281,176,0	script	#AgitMaster_V5	111,{
	callfunc "AgitMaster",36,38;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
prtg_cas05.gat,212,95,0	script	#AgitDungeon_V5	111,{
	callfunc "AgitDungeon","gld_dun03.gat",199,28;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
prtg_cas05.gat,276,178,0	script	#AgitBanWarp_V5	139,6,6,{
	callfunc "AgitBanWarp","prontera.gat",119,64;
	close;
}
