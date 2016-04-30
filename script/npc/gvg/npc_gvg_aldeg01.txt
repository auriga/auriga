//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Luina Guild 1	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
aldeg_cas01.gat,0,0,0	script	#AgitExe_L1	-1,{
OnAgitStart:
	callfunc "AgitEmperium",216,23,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","L1";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",216,23,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","L1";
	end;
OnAgitSummon:
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "aldeg_cas01.gat",0,0,0,0,"--ja--",1272,1;
	monster "aldeg_cas01.gat",216,23,"--ja--",1272,1;
	monster "aldeg_cas01.gat",216,23,"--ja--",1270,4;
	monster "aldeg_cas01.gat",216,23,"--ja--",1268,1;
	monster "aldeg_cas01.gat",216,23,"--ja--",1219,1;
	monster "aldeg_cas01.gat",216,23,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
aldeg_cas01.gat,0,0,0	script	#AgitTreasure_L1	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1324,1325;
		setarray 'treasure_x,115,122,115,122,116,117,118,119,120,121,121,121,121,121,121,120,119,118,117,116,116,116,116,116;
		setarray 'treasure_y,226,226,219,219,225,225,225,225,225,225,224,223,222,221,220,220,220,220,220,220,221,222,223,224;
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
-	script	#GldFlag_L1a	{
	callfunc "AgitEmblemFlag",1,"aldeg_cas01.gat",218,170;
	close;
OnAgitInit:
OnFlagEmb_L1:
	flagemblem getcastledata("aldeg_cas01.gat",1);
	end;
}
alde_gld.gat,257,153,7	duplicate(#GldFlag_L1a)	ギルドフラッグ#L1a01	722
alde_gld.gat,61,87,6	duplicate(#GldFlag_L1a)	ギルドフラッグ#L1a02	722
alde_gld.gat,61,79,6	duplicate(#GldFlag_L1a)	ギルドフラッグ#L1a03	722
alde_gld.gat,45,87,8	duplicate(#GldFlag_L1a)	ギルドフラッグ#L1a04	722
alde_gld.gat,51,87,8	duplicate(#GldFlag_L1a)	ギルドフラッグ#L1a05	722

-	script	#GldFlag_L1b	{
	end;
OnAgitInit:
OnFlagEmb_L1:
	flagemblem getcastledata("aldeg_cas01.gat",1);
	end;
}
//aldebaran.gat,152,97,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b01	722
//aldeg_cas01.gat,30,248,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b02	722
//aldeg_cas01.gat,30,246,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b03	722
//aldeg_cas01.gat,37,248,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b04	722
//aldeg_cas01.gat,37,246,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b05	722
//aldeg_cas01.gat,95,80,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b06	722
//aldeg_cas01.gat,95,59,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b07	722
//aldeg_cas01.gat,62,75,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b08	722
//aldeg_cas01.gat,66,75,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b09	722
//aldeg_cas01.gat,70,75,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b10	722
//aldeg_cas01.gat,74,75,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b11	722
//aldeg_cas01.gat,62,64,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b12	722
//aldeg_cas01.gat,66,64,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b13	722
//aldeg_cas01.gat,70,64,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b14	722
//aldeg_cas01.gat,74,64,2	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b15	722
//aldeg_cas01.gat,203,150,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b16	722
//aldeg_cas01.gat,210,150,4	duplicate(#GldFlag_L1b)	ギルドフラッグ#L1b17	722

//============================================================
// カプラ職員
//------------------------------------------------------------
aldeg_cas01.gat,218,170,0	script	カプラ職員::AgitKafra_L1	117,{
	callfunc "AgitKafra",17;
	close;
OnAgitInit:
	if(getcastledata("aldeg_cas01.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
aldeg_cas01.gat,218,175,0	script	アルプレド	55,{
	callfunc "AgitSteward","L1",'guardian_id,'guardian_x,'guardian_y,113,223;
	close;
OnAgitInit:
	setarray 'guardian_id,	1287,	1285,	1285,	1285,	1286,	1286,	1286,	1286;
	setarray 'guardian_x,	17,	39,	38,	45,	21,	218,	213,	73;
	setarray 'guardian_y,	218,	205,	196,	228,	194,	24,	24,	70;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("aldeg_cas01.gat",'@i+10))
			callguardian "aldeg_cas01.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
aldeg_cas01.gat,123,223,0	script	#AgitMaster_L1	111,{
	callfunc "AgitMaster",218,176;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
aldeg_cas01.gat,211,181,0	script	#AgitDungeon_L1	111,{
	callfunc "AgitDungeon","gld_dun02.gat",32,122;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
aldeg_cas01.gat,118,223,0	script	#AgitBanWarp_L1	139,8,8,{
	callfunc "AgitBanWarp","aldebaran.gat",143,112;
	close;
}
