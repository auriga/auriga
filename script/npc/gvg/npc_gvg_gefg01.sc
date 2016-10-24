//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Britoniah Guild 1	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
gefg_cas01.gat,0,0,0	script	#AgitExe_B1	-1,{
OnAgitStart:
	callfunc "AgitEmperium",197,181,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","B1";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",197,181,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","B1";
	end;
OnAgitSummon:
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1263,11;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1102,10;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1130,10;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1140,20;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1163,9;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1219,1;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "gefg_cas01.gat",0,0,0,0,"--ja--",1159,1;
	monster "gefg_cas01.gat",197,181,"--ja--",1203,1;
	monster "gefg_cas01.gat",197,181,"--ja--",1087,1;
	monster "gefg_cas01.gat",197,181,"--ja--",1213,10;
	monster "gefg_cas01.gat",197,181,"--ja--",1189,10;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
gefg_cas01.gat,0,0,0	script	#AgitTreasure_B1	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1334,1335;
		setarray 'treasure_x,153,154,154,153,151,152,153,154,155,156,156,156,156,156,156,155,154,153,152,151,151,151,151,151;
		setarray 'treasure_y,113,113,112,112,115,115,115,115,115,115,114,113,112,111,110,110,110,110,110,110,111,112,113,114;
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
-	script	#GldFlag_B1a	{
	callfunc "AgitEmblemFlag",0,"gefg_cas01.gat",197,36;
	close;
OnAgitInit:
OnFlagEmb_B1:
	flagemblem getcastledata("gefg_cas01.gat",1);
	end;
}
gef_fild07.gat,330,199,2	duplicate(#GldFlag_B1a)	ギルドフラッグ#B1a01	722
gef_fild13.gat,148,51,5		duplicate(#GldFlag_B1a)	ギルドフラッグ#B1a02	722
gef_fild13.gat,155,54,5		duplicate(#GldFlag_B1a)	ギルドフラッグ#B1a03	722
gef_fild13.gat,212,79,6		duplicate(#GldFlag_B1a)	ギルドフラッグ#B1a04	722
gef_fild13.gat,211,71,6		duplicate(#GldFlag_B1a)	ギルドフラッグ#B1a05	722

-	script	#GldFlag_B1b	{
	end;
OnAgitInit:
OnFlagEmb_B1:
	flagemblem getcastledata("gefg_cas01.gat",1);
	end;
}
//geffen.gat,109,123,2		duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b01	722
//gefg_cas01.gat,28,157,4	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b02	722
//gefg_cas01.gat,22,156,4	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b03	722
//gefg_cas01.gat,68,185,3	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b04	722
//gefg_cas01.gat,17,171,5	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b05	722
//gefg_cas01.gat,59,16,4	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b06	722
//gefg_cas01.gat,64,16,4	duplicate(#GldFlag_B1b)	ギルドフラッグ#B1b07	722

//============================================================
// カプラ職員
//------------------------------------------------------------
gefg_cas01.gat,83,47,3	script	カプラ職員::AgitKafra_B1	117,{
	callfunc "AgitKafra",15;
	close;
OnAgitInit:
	if(getcastledata("gefg_cas01.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
gefg_cas01.gat,40,48,5	script	グナフチョ	55,{
	callfunc "AgitSteward","B1",'guardian_id,'guardian_x,'guardian_y,152,117;
	close;
OnAgitInit:
	setarray 'guardian_id,	1287,	1287,	1287,	1285,	1285,	1286,	1286,	1286;
	setarray 'guardian_x,	67,	184,	62,	36,	50,	50,	189,	200;
	setarray 'guardian_y,	179,	20,	41,	186,	186,	67,	41,	167;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("gefg_cas01.gat",'@i+10))
			callguardian "gefg_cas01.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
gefg_cas01.gat,152,117,0	script	#AgitMaster_B1	111,{
	callfunc "AgitMaster",40,49;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
gefg_cas01.gat,78,84,0	script	#AgitDungeon_B1	111,{
	callfunc "AgitDungeon","gld_dun04.gat",39,258;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
gefg_cas01.gat,154,112,0	script	#AgitBanWarp_B1	139,6,6,{
	callfunc "AgitBanWarp","geffen.gat",120,38;
	close;
}
