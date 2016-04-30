//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Valkyrie Realms 3	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
prtg_cas03.gat,0,0,0	script	#AgitExe_V3	-1,{
OnAgitStart:
	callfunc "AgitEmperium",16,220,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","V3";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",16,220,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","V3";
	end;
OnAgitSummon:
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1163,15;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1132,10;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1219,5;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1268,5;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1251,1;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1252,1;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1259,2;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1283,2;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "prtg_cas03.gat",0,0,0,0,"--ja--",1200,1;
	monster "prtg_cas03.gat",16,220,"--ja--",1268,1;
	monster "prtg_cas03.gat",16,220,"--ja--",1251,1;
	monster "prtg_cas03.gat",16,220,"--ja--",1252,1;
	monster "prtg_cas03.gat",16,220,"--ja--",1219,2;
	monster "prtg_cas03.gat",16,220,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
prtg_cas03.gat,0,0,0	script	#AgitTreasure_V3	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1358,1359;
		setarray 'treasure_x,187,188,188,187,185,186,187,188,189,190,190,190,190,190,190,189,188,187,186,185,185,185,185,185;
		setarray 'treasure_y,132,132,131,131,134,134,134,134,134,134,133,132,131,130,129,129,129,129,129,129,130,131,132,133;
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
-	script	#GldFlag_V3a	{
	callfunc "AgitEmblemFlag",0,"prtg_cas03.gat",181,215;
	close;
OnAgitInit:
OnFlagEmb_V3:
	flagemblem getcastledata("prtg_cas03.gat",1);
	end;
}
prt_gld.gat,150,220,2	duplicate(#GldFlag_V3a)	ギルドフラッグ#V3a01	722
prt_gld.gat,147,140,4	duplicate(#GldFlag_V3a)	ギルドフラッグ#V3a02	722
prt_gld.gat,147,136,4	duplicate(#GldFlag_V3a)	ギルドフラッグ#V3a03	722
prt_gld.gat,158,140,4	duplicate(#GldFlag_V3a)	ギルドフラッグ#V3a04	722
prt_gld.gat,158,136,4	duplicate(#GldFlag_V3a)	ギルドフラッグ#V3a05	722

-	script	#GldFlag_V3b	{
	end;
OnAgitInit:
OnFlagEmb_V3:
	flagemblem getcastledata("prtg_cas03.gat",1);
	end;
}
//prontera.gat,143,203,2	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b01	722
//prtg_cas03.gat,168,28,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b02	722
//prtg_cas03.gat,182,28,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b03	722
//prtg_cas03.gat,43,50,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b04	722
//prtg_cas03.gat,48,50,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b05	722
//prtg_cas03.gat,43,58,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b06	722
//prtg_cas03.gat,48,58,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b07	722
//prtg_cas03.gat,158,210,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b08	722
//prtg_cas03.gat,169,210,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b09	722
//prtg_cas03.gat,162,201,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b10	722
//prtg_cas03.gat,165,201,4	duplicate(#GldFlag_V3b)	ギルドフラッグ#V3b11	722

//============================================================
// カプラ職員
//------------------------------------------------------------
prtg_cas03.gat,181,215,4	script	カプラ職員::AgitKafra_V3	117,{
	callfunc "AgitKafra",14;
	close;
OnAgitInit:
	if(getcastledata("prtg_cas03.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
prtg_cas03.gat,51,100,4	script	ステッキ	55,{
	callfunc "AgitSteward","V3",'guardian_id,'guardian_x,'guardian_y,190,130;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1286,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	191,	137,	45,	50,	41,	191,	179,	191;
	setarray 'guardian_y,	190,	190,	99,	87,	87,	42,	43,	72;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("prtg_cas03.gat",'@i+10))
			callguardian "prtg_cas03.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
prtg_cas03.gat,193,130,0	script	#AgitMaster_V3	111,{
	callfunc "AgitMaster",51,101;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
prtg_cas03.gat,5,70,0	script	#AgitDungeon_V3	111,{
	callfunc "AgitDungeon","gld_dun03.gat",164,179;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
prtg_cas03.gat,189,132,0	script	#AgitBanWarp_V3	139,6,6,{
	callfunc "AgitBanWarp","prontera.gat",119,64;
	close;
}
