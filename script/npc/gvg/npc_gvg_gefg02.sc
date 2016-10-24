//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Britoniah Guild 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
gefg_cas02.gat,0,0,0	script	#AgitExe_B2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",176,178,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","B2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",176,178,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","B2";
	end;
OnAgitSummon:
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1263,11;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1102,10;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1130,10;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1140,20;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1163,9;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1219,1;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "gefg_cas02.gat",0,0,0,0,"--ja--",1159,1;
	monster "gefg_cas02.gat",176,178,"--ja--",1203,1;
	monster "gefg_cas02.gat",176,178,"--ja--",1087,1;
	monster "gefg_cas02.gat",176,178,"--ja--",1213,10;
	monster "gefg_cas02.gat",176,178,"--ja--",1189,10;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
gefg_cas02.gat,0,0,0	script	#AgitTreasure_B2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1336,1337;
		setarray 'treasure_x,139,140,140,139,137,138,139,140,141,142,142,142,142,142,142,141,140,139,138,137,137,137,137,137;
		setarray 'treasure_y,115,115,114,114,117,117,117,117,117,117,116,115,114,113,112,112,112,112,112,112,113,114,115,116;
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
-	script	#GldFlag_B2a	{
	callfunc "AgitEmblemFlag",0,"gefg_cas02.gat",178,43;
	close;
OnAgitInit:
OnFlagEmb_B2:
	flagemblem getcastledata("gefg_cas02.gat",1);
	end;
}
gef_fild07.gat,330,204,2	duplicate(#GldFlag_B2a)	ギルドフラッグ#B2a01	722
gef_fild13.gat,303,243,4	duplicate(#GldFlag_B2a)	ギルドフラッグ#B2a02	722
gef_fild13.gat,312,243,4	duplicate(#GldFlag_B2a)	ギルドフラッグ#B2a03	722
gef_fild13.gat,290,243,4	duplicate(#GldFlag_B2a)	ギルドフラッグ#B2a04	722
gef_fild13.gat,324,243,4	duplicate(#GldFlag_B2a)	ギルドフラッグ#B2a05	722

-	script	#GldFlag_B2b	{
	end;
OnAgitInit:
OnFlagEmb_B2:
	flagemblem getcastledata("gefg_cas02.gat",1);
	end;
}
//geffen.gat,112,129,1		duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b01	722
//gefg_cas02.gat,65,130,5	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b02	722
//gefg_cas02.gat,30,123,5	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b03	722
//gefg_cas02.gat,65,139,6	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b04	722
//gefg_cas02.gat,37,177,6	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b05	722
//gefg_cas02.gat,37,168,6	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b06	722
//gefg_cas02.gat,68,47,2	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b07	722
//gefg_cas02.gat,68,36,2	duplicate(#GldFlag_B2b)	ギルドフラッグ#B2b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
gefg_cas02.gat,23,66,3	script	カプラ職員::AgitKafra_B2	117,{
	callfunc "AgitKafra",15;
	close;
OnAgitInit:
	if(getcastledata("gefg_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
gefg_cas02.gat,12,66,5	script	エスマーク	55,{
	callfunc "AgitSteward","B2",'guardian_id,'guardian_x,'guardian_y,145,115;
	close;
OnAgitInit:
	setarray 'guardian_id,	1287,	1287,	1287,	1285,	1285,	1286,	1286,	1286;
	setarray 'guardian_x,	64,	56,	166,	35,	20,	19,	166,	159;
	setarray 'guardian_y,	168,	41,	25,	148,	150,	41,	42,	188;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("gefg_cas02.gat",'@i+10))
			callguardian "gefg_cas02.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
gefg_cas02.gat,145,114,0	script	#AgitMaster_B2	111,{
	callfunc "AgitMaster",12,67;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
gefg_cas02.gat,167,40,0	script	#AgitDungeon_B2	111,{
	callfunc "AgitDungeon","gld_dun04.gat",125,270;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
gefg_cas02.gat,140,116,0	script	#AgitBanWarp_B2	139,6,6,{
	callfunc "AgitBanWarp","geffen.gat",120,38;
	close;
}
