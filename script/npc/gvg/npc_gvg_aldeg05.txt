//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Luina Guild 5	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
aldeg_cas05.gat,0,0,0	script	#AgitExe_L5	-1,{
OnAgitStart:
	callfunc "AgitEmperium",27,101,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","L5";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",27,101,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","L5";
	end;
OnAgitSummon:
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "aldeg_cas05.gat",0,0,0,0,"--ja--",1272,1;
	monster "aldeg_cas05.gat",27,101,"--ja--",1272,1;
	monster "aldeg_cas05.gat",27,101,"--ja--",1270,4;
	monster "aldeg_cas05.gat",27,101,"--ja--",1268,1;
	monster "aldeg_cas05.gat",27,101,"--ja--",1219,1;
	monster "aldeg_cas05.gat",27,101,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
aldeg_cas05.gat,0,0,0	script	#AgitTreasure_L5	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1332,1333;
		setarray 'treasure_x,61,62,62,61,59,60,61,62,63,64,64,64,64,64,64,63,62,61,60,59,59,59,59,59;
		setarray 'treasure_y,12,12,11,11,14,14,14,14,14,14,13,12,11,10, 9, 9, 9, 9, 9, 9,10,11,12,13;
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
-	script	#GldFlag_L5a	{
	callfunc "AgitEmblemFlag",1,"aldeg_cas05.gat",167,225;
	close;
OnAgitInit:
OnFlagEmb_L5:
	flagemblem getcastledata("aldeg_cas05.gat",1);
	end;
}
alde_gld.gat,267,153,7	duplicate(#GldFlag_L5a)	ギルドフラッグ#L5a01	722
alde_gld.gat,265,93,6	duplicate(#GldFlag_L5a)	ギルドフラッグ#L5a02	722
alde_gld.gat,265,87,6	duplicate(#GldFlag_L5a)	ギルドフラッグ#L5a03	722

-	script	#GldFlag_L5b	{
	end;
OnAgitInit:
OnFlagEmb_L5:
	flagemblem getcastledata("aldeg_cas05.gat",1);
	end;
}
//aldebaran.gat,128,97,4	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b01	722
//aldeg_cas05.gat,170,85,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b02	722
//aldeg_cas05.gat,142,212,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b03	722
//aldeg_cas05.gat,149,196,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b04	722
//aldeg_cas05.gat,41,180,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b05	722
//aldeg_cas05.gat,38,201,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b06	722
//aldeg_cas05.gat,65,182,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b07	722
//aldeg_cas05.gat,65,205,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b08	722
//aldeg_cas05.gat,10,218,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b09	722
//aldeg_cas05.gat,164,201,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b10	722
//aldeg_cas05.gat,14,117,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b11	722
//aldeg_cas05.gat,10,225,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b12	722
//aldeg_cas05.gat,187,59,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b13	722
//aldeg_cas05.gat,154,51,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b14	722
//aldeg_cas05.gat,22,211,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b15	722
//aldeg_cas05.gat,150,202,2	duplicate(#GldFlag_L5b)	ギルドフラッグ#L5b16	722

//============================================================
// カプラ職員
//------------------------------------------------------------
aldeg_cas05.gat,31,190,0	script	カプラ職員::AgitKafra_L5	117,{
	callfunc "AgitKafra",17;
	close;
OnAgitInit:
	if(getcastledata("aldeg_cas05.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
aldeg_cas05.gat,51,179,0	script	ブリムヘンセン	55,{
	callfunc "AgitSteward","L5",'guardian_id,'guardian_x,'guardian_y,64,8;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1287,	1287,	1286,	1286,	1286,	1286;
	setarray 'guardian_x,	51,	188,	157,	157,	27,	145,	156,	41;
	setarray 'guardian_y,	202,	79,	192,	74,	221,	78,	73,	112;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("aldeg_cas05.gat",'@i+10))
			callguardian "aldeg_cas05.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
aldeg_cas05.gat,64,8,0	script	#AgitMaster_L5	111,{
	callfunc "AgitMaster",51,179;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
aldeg_cas05.gat,22,205,0	script	#AgitDungeon_L5	111,{
	callfunc "AgitDungeon","gld_dun02.gat",103,169;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
aldeg_cas05.gat,62,12,0	script	#AgitBanWarp_L5	139,8,8,{
	callfunc "AgitBanWarp","aldebaran.gat",143,112;
	close;
}
