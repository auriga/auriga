//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Britoniah Guild 5	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
gefg_cas05.gat,0,0,0	script	#AgitExe_B5	-1,{
OnAgitStart:
	callfunc "AgitEmperium",194,184,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","B5";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",194,184,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","B5";
	end;
OnAgitSummon:
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1263,11;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1102,10;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1130,10;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1140,20;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1163,9;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1219,1;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "gefg_cas05.gat",0,0,0,0,"--ja--",1159,1;
	monster "gefg_cas05.gat",194,184,"--ja--",1203,1;
	monster "gefg_cas05.gat",194,184,"--ja--",1087,1;
	monster "gefg_cas05.gat",194,184,"--ja--",1213,10;
	monster "gefg_cas05.gat",194,184,"--ja--",1189,10;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
gefg_cas05.gat,0,0,0	script	#AgitTreasure_B5	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1342,1343;
		setarray 'treasure_x,143,144,144,143,141,142,143,144,145,146,146,146,146,146,146,145,144,143,142,141,141,141,141,141;
		setarray 'treasure_y,110,110,109,109,112,112,112,112,112,112,111,110,109,108,107,107,107,107,107,107,108,109,110,111;
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
-	script	#GldFlag_B5a	{
	callfunc "AgitEmblemFlag",0,"gefg_cas05.gat",168,31;
	close;
OnAgitInit:
OnFlagEmb_B5:
	flagemblem getcastledata("gefg_cas05.gat",1);
	end;
}
gef_fild07.gat,330,166,2	duplicate(#GldFlag_B5a)	ギルドフラッグ#B5a01	722
gef_fild13.gat,302,87,7		duplicate(#GldFlag_B5a)	ギルドフラッグ#B5a02	722
gef_fild13.gat,313,83,0		duplicate(#GldFlag_B5a)	ギルドフラッグ#B5a03	722
gef_fild13.gat,252,51,2		duplicate(#GldFlag_B5a)	ギルドフラッグ#B5a04	722
gef_fild13.gat,26,147,2		duplicate(#GldFlag_B5a)	ギルドフラッグ#B5a05	722

-	script	#GldFlag_B5b	{
	end;
OnAgitInit:
OnFlagEmb_B5:
	flagemblem getcastledata("gefg_cas05.gat",1);
	end;
}
//geffen.gat,131,123,6		duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b01	722
//gefg_cas05.gat,77,185,7	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b02	722
//gefg_cas05.gat,92,181,0	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b03	722
//gefg_cas05.gat,83,158,1	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b04	722
//gefg_cas05.gat,62,144,7	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b05	722
//gefg_cas05.gat,62,66,4	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b06	722
//gefg_cas05.gat,69,66,4	duplicate(#GldFlag_B5b)	ギルドフラッグ#B5b07	722

//============================================================
// カプラ職員
//------------------------------------------------------------
gefg_cas05.gat,61,52,5	script	カプラ職員::AgitKafra_B5	117,{
	callfunc "AgitKafra",15;
	close;
OnAgitInit:
	if(getcastledata("gefg_cas05.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
gefg_cas05.gat,70,52,3	script	ビオル	55,{
	callfunc "AgitSteward","B5",'guardian_id,'guardian_x,'guardian_y,149,106;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1287,	1287,	1287,	1286,	1286,	1286;
	setarray 'guardian_x,	45,	71,	72,	66,	177,	66,	177,	193;
	setarray 'guardian_y,	149,	163,	142,	47,	50,	17,	35,	166;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("gefg_cas05.gat",'@i+10))
			callguardian "gefg_cas05.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
gefg_cas05.gat,149,107,0	script	#AgitMaster_B5	111,{
	callfunc "AgitMaster",70,53;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
gefg_cas05.gat,65,22,0	script	#AgitDungeon_B5	111,{
	callfunc "AgitDungeon","gld_dun04.gat",230,35;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
gefg_cas05.gat,144,110,0	script	#AgitBanWarp_B5	139,6,6,{
	callfunc "AgitBanWarp","geffen.gat",120,38;
	close;
}
