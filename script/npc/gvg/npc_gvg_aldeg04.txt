//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Luina Guild 4	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
aldeg_cas04.gat,0,0,0	script	#AgitExe_L4	-1,{
OnAgitStart:
	callfunc "AgitEmperium",36,217,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","L4";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",36,217,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","L4";
	end;
OnAgitSummon:
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "aldeg_cas04.gat",0,0,0,0,"--ja--",1272,1;
	monster "aldeg_cas04.gat",36,217,"--ja--",1272,1;
	monster "aldeg_cas04.gat",36,217,"--ja--",1270,4;
	monster "aldeg_cas04.gat",36,217,"--ja--",1268,1;
	monster "aldeg_cas04.gat",36,217,"--ja--",1219,1;
	monster "aldeg_cas04.gat",36,217,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
aldeg_cas04.gat,0,0,0	script	#AgitTreasure_L4	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1330,1331;
		setarray 'treasure_x,84,85,85,84,82,83,84,85,86,87,87,87,87,87,87,86,85,84,83,82,82,82,82,82;
		setarray 'treasure_y,13,13,12,12,15,15,15,15,15,15,14,13,12,11,10,10,10,10,10,10,11,12,13,14;
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
-	script	#GldFlag_L4a	{
	callfunc "AgitEmblemFlag",1,"aldeg_cas04.gat",116,217;
	close;
OnAgitInit:
OnFlagEmb_L4:
	flagemblem getcastledata("aldeg_cas04.gat",1);
	end;
}
alde_gld.gat,262,166,5	duplicate(#GldFlag_L4a)	ギルドフラッグ#L4a01	722
alde_gld.gat,239,246,2	duplicate(#GldFlag_L4a)	ギルドフラッグ#L4a02	722
alde_gld.gat,239,239,2	duplicate(#GldFlag_L4a)	ギルドフラッグ#L4a03	722

-	script	#GldFlag_L4b	{
	end;
OnAgitInit:
OnFlagEmb_L4:
	flagemblem getcastledata("aldeg_cas04.gat",1);
	end;
}
//aldebaran.gat,131,97,4	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b01	722
//aldeg_cas04.gat,167,61,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b02	722
//aldeg_cas04.gat,164,90,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b03	722
//aldeg_cas04.gat,129,193,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b04	722
//aldeg_cas04.gat,112,206,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b05	722
//aldeg_cas04.gat,113,212,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b06	722
//aldeg_cas04.gat,77,117,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b07	722
//aldeg_cas04.gat,186,42,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b08	722
//aldeg_cas04.gat,30,69,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b09	722
//aldeg_cas04.gat,55,97,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b10	722
//aldeg_cas04.gat,45,98,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b11	722
//aldeg_cas04.gat,33,116,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b12	722
//aldeg_cas04.gat,130,180,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b13	722
//aldeg_cas04.gat,129,193,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b14	722
//aldeg_cas04.gat,33,107,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b15	722
//aldeg_cas04.gat,133,220,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b16	722
//aldeg_cas04.gat,169,22,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b17	722
//aldeg_cas04.gat,169,15,2	duplicate(#GldFlag_L4b)	ギルドフラッグ#L4b18	722

//============================================================
// カプラ職員
//------------------------------------------------------------
aldeg_cas04.gat,45,88,0	script	カプラ職員::AgitKafra_L4	117,{
	callfunc "AgitKafra",17;
	close;
OnAgitInit:
	if(getcastledata("aldeg_cas04.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
aldeg_cas04.gat,67,116,0	script	ウィリオット	55,{
	callfunc "AgitSteward","L4",'guardian_id,'guardian_x,'guardian_y,83,17;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1287,	1287,	1287,	1286,	1286;
	setarray 'guardian_x,	187,	192,	148,	145,	169,	198,	48,	55;
	setarray 'guardian_y,	100,	42,	88,	209,	53,	77,	72,	88;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("aldeg_cas04.gat",'@i+10))
			callguardian "aldeg_cas04.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
aldeg_cas04.gat,83,17,0	script	#AgitMaster_L4	111,{
	callfunc "AgitMaster",67,117;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
aldeg_cas04.gat,76,64,0	script	#AgitDungeon_L4	111,{
	callfunc "AgitDungeon","gld_dun02.gat",160,148;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
aldeg_cas04.gat,84,13,0	script	#AgitBanWarp_L4	139,8,8,{
	callfunc "AgitBanWarp","aldebaran.gat",143,112;
	close;
}
