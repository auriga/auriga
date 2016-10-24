//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valkyrie Realms 4	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
prtg_cas04.gat,0,0,0	script	#AgitExe_V4	-1,{
OnAgitStart:
	callfunc "AgitEmperium",291,14,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","V4";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",291,14,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","V4";
	end;
OnAgitSummon:
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1163,15;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1132,10;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1219,5;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1268,5;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1251,1;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1252,1;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1259,2;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1283,2;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "prtg_cas04.gat",0,0,0,0,"--ja--",1200,1;
	monster "prtg_cas04.gat",291,14,"--ja--",1268,1;
	monster "prtg_cas04.gat",291,14,"--ja--",1251,1;
	monster "prtg_cas04.gat",291,14,"--ja--",1252,1;
	monster "prtg_cas04.gat",291,14,"--ja--",1219,2;
	monster "prtg_cas04.gat",291,14,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
prtg_cas04.gat,0,0,0	script	#AgitTreasure_V4	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1360,1361;
		setarray 'treasure_x,269,270,270,269,267,268,269,270,271,272,272,272,272,272,272,271,270,269,268,267,267,267,267,267;
		setarray 'treasure_y,162,162,161,161,164,164,164,164,164,164,163,162,161,160,159,159,159,159,159,159,160,161,162,163;
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
-	script	#GldFlag_V4a	{
	callfunc "AgitEmblemFlag",0,"prtg_cas04.gat",258,247;
	close;
OnAgitInit:
OnFlagEmb_V4:
	flagemblem getcastledata("prtg_cas04.gat",1);
	end;
}
prt_gld.gat,169,220,6	duplicate(#GldFlag_V4a)	ギルドフラッグ#V4a01	722
prt_gld.gat,120,243,6	duplicate(#GldFlag_V4a)	ギルドフラッグ#V4a02	722
prt_gld.gat,120,236,6	duplicate(#GldFlag_V4a)	ギルドフラッグ#V4a03	722
prt_gld.gat,122,243,6	duplicate(#GldFlag_V4a)	ギルドフラッグ#V4a04	722
prt_gld.gat,122,236,6	duplicate(#GldFlag_V4a)	ギルドフラッグ#V4a05	722

-	script	#GldFlag_V4b	{
	end;
OnAgitInit:
OnFlagEmb_V4:
	flagemblem getcastledata("prtg_cas04.gat",1);
	end;
}
//prontera.gat,167,203,6	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b01	722
//prtg_cas04.gat,82,29,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b02	722
//prtg_cas04.gat,75,29,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b03	722
//prtg_cas04.gat,75,27,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b04	722
//prtg_cas04.gat,82,27,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b05	722
//prtg_cas04.gat,59,29,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b06	722
//prtg_cas04.gat,67,29,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b07	722
//prtg_cas04.gat,258,25,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b08	722
//prtg_cas04.gat,258,20,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b09	722
//prtg_cas04.gat,263,20,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b10	722
//prtg_cas04.gat,263,27,4	duplicate(#GldFlag_V4b)	ギルドフラッグ#V4b11	722

//============================================================
// カプラ職員
//------------------------------------------------------------
prtg_cas04.gat,258,247,4	script	カプラ職員::AgitKafra_V4	117,{
	callfunc "AgitKafra",14;
	close;
OnAgitInit:
	if(getcastledata("prtg_cas04.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
prtg_cas04.gat,259,265,4	script	バンドレッド	55,{
	callfunc "AgitSteward","V4",'guardian_id,'guardian_x,'guardian_y,275,160;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1286,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	276,	274,	246,	38,	29,	33,	78,	36;
	setarray 'guardian_y,	14,	35,	246,	240,	240,	258,	48,	61;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("prtg_cas04.gat",'@i+10))
			callguardian "prtg_cas04.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
prtg_cas04.gat,275,160,0	script	#AgitMaster_V4	111,{
	callfunc "AgitMaster",259,265;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
prtg_cas04.gat,56,283,0	script	#AgitDungeon_V4	111,{
	callfunc "AgitDungeon","gld_dun03.gat",268,203;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
prtg_cas04.gat,271,162,0	script	#AgitBanWarp_V4	139,6,6,{
	callfunc "AgitBanWarp","prontera.gat",119,64;
	close;
}
