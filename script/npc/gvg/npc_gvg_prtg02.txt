//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valkyrie Realms 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
prtg_cas02.gat,0,0,0	script	#AgitExe_V2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",157,174,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","V2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",157,174,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","V2";
	end;
OnAgitSummon:
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1163,15;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1132,10;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1219,5;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1268,5;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1251,1;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1252,1;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1259,2;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1283,2;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "prtg_cas02.gat",0,0,0,0,"--ja--",1200,1;
	monster "prtg_cas02.gat",157,174,"--ja--",1268,1;
	monster "prtg_cas02.gat",157,174,"--ja--",1251,1;
	monster "prtg_cas02.gat",157,174,"--ja--",1252,1;
	monster "prtg_cas02.gat",157,174,"--ja--",1219,2;
	monster "prtg_cas02.gat",157,174,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
prtg_cas02.gat,0,0,0	script	#AgitTreasure_V2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1356,1357;
		setarray 'treasure_x,201,202,202,201,199,200,201,202,203,204,204,204,204,204,204,203,202,201,200,199,199,199,199,199;
		setarray 'treasure_y,228,228,227,227,230,230,230,230,230,230,229,228,227,226,225,225,225,225,225,225,226,227,228,229;
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
-	script	#GldFlag_V2a	{
	callfunc "AgitEmblemFlag",0,"prtg_cas02.gat",169,55;
	close;
OnAgitInit:
OnFlagEmb_V2:
	flagemblem getcastledata("prtg_cas02.gat",1);
	end;
}
prt_gld.gat,153,213,3	duplicate(#GldFlag_V2a)	ギルドフラッグ#V2a01	722
prt_gld.gat,244,126,8	duplicate(#GldFlag_V2a)	ギルドフラッグ#V2a02	722
prt_gld.gat,244,128,8	duplicate(#GldFlag_V2a)	ギルドフラッグ#V2a03	722
prt_gld.gat,236,126,8	duplicate(#GldFlag_V2a)	ギルドフラッグ#V2a04	722
prt_gld.gat,236,128,8	duplicate(#GldFlag_V2a)	ギルドフラッグ#V2a05	722

-	script	#GldFlag_V2b	{
	end;
OnAgitInit:
OnFlagEmb_V2:
	flagemblem getcastledata("prtg_cas02.gat",1);
	end;
}
//prontera.gat,146,194,3	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b01	722
//prtg_cas02.gat,40,227,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b02	722
//prtg_cas02.gat,46,227,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b03	722
//prtg_cas02.gat,11,219,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b04	722
//prtg_cas02.gat,11,214,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b05	722
//prtg_cas02.gat,20,219,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b06	722
//prtg_cas02.gat,20,214,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b07	722
//prtg_cas02.gat,79,227,8	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b08	722
//prtg_cas02.gat,70,227,8	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b09	722
//prtg_cas02.gat,38,189,8	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b10	722
//prtg_cas02.gat,34,189,8	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b11	722
//prtg_cas02.gat,153,161,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b12	722
//prtg_cas02.gat,162,161,4	duplicate(#GldFlag_V2b)	ギルドフラッグ#V2b13	722

//============================================================
// カプラ職員
//------------------------------------------------------------
prtg_cas02.gat,71,36,4	script	カプラ職員::AgitKafra_V2	117,{
	callfunc "AgitKafra",14;
	close;
OnAgitInit:
	if(getcastledata("prtg_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
prtg_cas02.gat,94,61,4	script	ルエ	55,{
	callfunc "AgitSteward","V2",'guardian_id,'guardian_x,'guardian_y,207,229;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1286,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	162,	153,	178,	71,	49,	64,	76,	75;
	setarray 'guardian_y,	161,	161,	44,	75,	28,	186,	196,	175;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("prtg_cas02.gat",'@i+10))
			callguardian "prtg_cas02.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
prtg_cas02.gat,207,228,0	script	#AgitMaster_V2	111,{
	callfunc "AgitMaster",94,62;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
prtg_cas02.gat,84,72,0	script	#AgitDungeon_V2	111,{
	callfunc "AgitDungeon","gld_dun03.gat",164,268;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
prtg_cas02.gat,202,228,0	script	#AgitBanWarp_V2	139,6,6,{
	callfunc "AgitBanWarp","prontera.gat",119,64;
	close;
}
