//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Luina Guild 3	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
aldeg_cas03.gat,0,0,0	script	#AgitExe_L3	-1,{
OnAgitStart:
	callfunc "AgitEmperium",205,31,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","L3";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",205,31,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","L3";
	end;
OnAgitSummon:
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "aldeg_cas03.gat",0,0,0,0,"--ja--",1272,1;
	monster "aldeg_cas03.gat",205,31,"--ja--",1272,1;
	monster "aldeg_cas03.gat",205,31,"--ja--",1270,4;
	monster "aldeg_cas03.gat",205,31,"--ja--",1268,1;
	monster "aldeg_cas03.gat",205,31,"--ja--",1219,1;
	monster "aldeg_cas03.gat",205,31,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
aldeg_cas03.gat,0,0,0	script	#AgitTreasure_L3	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1328,1329;
		setarray 'treasure_x,224,225,225,224,222,223,224,225,226,227,227,227,227,227,227,226,225,224,223,222,222,222,222,222;
		setarray 'treasure_y,269,269,268,268,271,271,271,271,271,271,270,269,268,267,266,266,266,266,266,266,267,268,269,270;
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
-	script	#GldFlag_L3a	{
	callfunc "AgitEmblemFlag",1,"aldeg_cas03.gat",205,186;
	close;
OnAgitInit:
OnFlagEmb_L3:
	flagemblem getcastledata("aldeg_cas03.gat",1);
	end;
}
alde_gld.gat,262,153,7	duplicate(#GldFlag_L3a)	ギルドフラッグ#L3a01	722
alde_gld.gat,146,82,8	duplicate(#GldFlag_L3a)	ギルドフラッグ#L3a02	722
alde_gld.gat,138,82,8	duplicate(#GldFlag_L3a)	ギルドフラッグ#L3a03	722

-	script	#GldFlag_L3b	{
	end;
OnAgitInit:
OnFlagEmb_L3:
	flagemblem getcastledata("aldeg_cas03.gat",1);
	end;
}
//aldebaran.gat,134,97,4	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b01	722
//aldeg_cas03.gat,176,175,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b02	722
//aldeg_cas03.gat,77,115,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b03	722
//aldeg_cas03.gat,77,215,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b04	722
//aldeg_cas03.gat,112,107,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b05	722
//aldeg_cas03.gat,112,117,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b06	722
//aldeg_cas03.gat,69,71,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b07	722
//aldeg_cas03.gat,91,69,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b08	722
//aldeg_cas03.gat,108,60,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b09	722
//aldeg_cas03.gat,121,73,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b10	722
//aldeg_cas03.gat,75,102,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b11	722
//aldeg_cas03.gat,199,169,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b12	722
//aldeg_cas03.gat,181,179,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b13	722
//aldeg_cas03.gat,192,44,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b14	722
//aldeg_cas03.gat,208,145,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b15	722
//aldeg_cas03.gat,207,75,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b16	722
//aldeg_cas03.gat,96,62,2	duplicate(#GldFlag_L3b)	ギルドフラッグ#L3b17	722

//============================================================
// カプラ職員
//------------------------------------------------------------
aldeg_cas03.gat,118,76,0	script	カプラ職員::AgitKafra_L3	117,{
	callfunc "AgitKafra",17;
	close;
OnAgitInit:
	if(getcastledata("aldeg_cas03.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
aldeg_cas03.gat,110,118,0	script	ナザプ	55,{
	callfunc "AgitSteward","L3",'guardian_id,'guardian_x,'guardian_y,229,267;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1287,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	90,	116,	86,	116,	64,	212,	195,	110;
	setarray 'guardian_y,	112,	112,	120,	76,	103,	160,	151,	217;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("aldeg_cas03.gat",'@i+10))
			callguardian "aldeg_cas03.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
aldeg_cas03.gat,229,267,0	script	#AgitMaster_L3	111,{
	callfunc "AgitMaster",110,119;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
aldeg_cas03.gat,200,177,0	script	#AgitDungeon_L3	111,{
	callfunc "AgitDungeon","gld_dun02.gat",165,38;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
aldeg_cas03.gat,225,269,0	script	#AgitBanWarp_L3	139,8,8,{
	callfunc "AgitBanWarp","aldebaran.gat",143,112;
	close;
}
