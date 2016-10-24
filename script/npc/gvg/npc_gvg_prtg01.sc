//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valkyrie Realms 1	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
prtg_cas01.gat,0,0,0	script	#AgitExe_V1	-1,{
OnAgitStart:
	callfunc "AgitEmperium",197,197,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","V1";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",197,197,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","V1";
	end;
OnAgitSummon:
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1163,15;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1132,10;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1219,5;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1268,5;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1251,1;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1252,1;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1259,2;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1283,2;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "prtg_cas01.gat",0,0,0,0,"--ja--",1200,1;
	monster "prtg_cas01.gat",197,197,"--ja--",1268,1;
	monster "prtg_cas01.gat",197,197,"--ja--",1251,1;
	monster "prtg_cas01.gat",197,197,"--ja--",1252,1;
	monster "prtg_cas01.gat",197,197,"--ja--",1219,2;
	monster "prtg_cas01.gat",197,197,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
prtg_cas01.gat,0,0,0	script	#AgitTreasure_V1	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1354,1355;
		setarray 'treasure_x, 10, 11, 11, 10,  8,  9, 10, 11, 12, 13, 13, 13, 13, 13, 13, 12, 11, 10,  9,  8,  8,  8,  8,  8;
		setarray 'treasure_y,209,209,208,208,211,211,211,211,211,211,210,209,208,207,206,206,206,206,206,206,207,208,209,210;
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
-	script	#GldFlag_V1a	{
	callfunc "AgitEmblemFlag",0,"prtg_cas01.gat",96,173;
	close;
OnAgitInit:
OnFlagEmb_V1:
	flagemblem getcastledata("prtg_cas01.gat",1);
	end;
}
prt_gld.gat,160,210,4	duplicate(#GldFlag_V1a)	ギルドフラッグ#V1a01	722
prt_gld.gat,131,60,6	duplicate(#GldFlag_V1a)	ギルドフラッグ#V1a02	722
prt_gld.gat,138,68,6	duplicate(#GldFlag_V1a)	ギルドフラッグ#V1a03	722
prt_gld.gat,138,60,6	duplicate(#GldFlag_V1a)	ギルドフラッグ#V1a04	722
prt_gld.gat,135,60,6	duplicate(#GldFlag_V1a)	ギルドフラッグ#V1a05	722

-	script	#GldFlag_V1b	{
	end;
OnAgitInit:
OnFlagEmb_V1:
	flagemblem getcastledata("prtg_cas01.gat",1);
	end;
}
//prontera.gat,155,190,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b01	722
//prtg_cas01.gat,58,56,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b02	722
//prtg_cas01.gat,64,56,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b03	722
//prtg_cas01.gat,76,32,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b04	722
//prtg_cas01.gat,84,32,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b05	722
//prtg_cas01.gat,94,39,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b06	722
//prtg_cas01.gat,94,24,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b07	722
//prtg_cas01.gat,73,14,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b08	722
//prtg_cas01.gat,73,6,4		duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b09	722
//prtg_cas01.gat,55,46,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b10	722
//prtg_cas01.gat,45,46,4	duplicate(#GldFlag_V1b)	ギルドフラッグ#V1b11	722

//============================================================
// カプラ職員
//------------------------------------------------------------
prtg_cas01.gat,96,173,0	script	カプラ職員::AgitKafra_V1	117,{
	callfunc "AgitKafra",14;
	close;
OnAgitInit:
	if(getcastledata("prtg_cas01.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
prtg_cas01.gat,112,181,0	script	アブライ	55,{
	callfunc "AgitSteward","V1",'guardian_id,'guardian_x,'guardian_y,15,209;
	close;
OnAgitInit:
	setarray 'guardian_id,	1287,	1287,	1287,	1285,	1285,	1286,	1286,	1286;
	setarray 'guardian_x,	182,	182,	153,	59,	50,	184,	196,	107;
	setarray 'guardian_y,	68,	116,	86,	28,	36,	183,	189,	179;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("prtg_cas01.gat",'@i+10))
			callguardian "prtg_cas01.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
prtg_cas01.gat,15,208,0	script	#AgitMaster_V1	111,{
	//callfunc "AgitMaster",112,183;
	callfunc "AgitMaster",111,183;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
prtg_cas01.gat,94,200,0	script	#AgitDungeon_V1	111,{
	callfunc "AgitDungeon","gld_dun03.gat",28,251;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
prtg_cas01.gat,11,208,0	script	#AgitBanWarp_V1	139,6,6,{
	callfunc "AgitBanWarp","prontera.gat",119,64;
	close;
}
