//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Luina Guild 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
aldeg_cas02.gat,0,0,0	script	#AgitExe_L2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",216,23,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","L2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",216,23,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","L2";
	end;
OnAgitSummon:
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1132,4;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1219,2;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1205,1;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1216,10;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1193,18;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1269,9;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1276,7;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1208,3;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1268,1;
	areamonster "aldeg_cas02.gat",0,0,0,0,"--ja--",1272,1;
	monster "aldeg_cas02.gat",213,23,"--ja--",1272,1;
	monster "aldeg_cas02.gat",213,23,"--ja--",1270,4;
	monster "aldeg_cas02.gat",213,23,"--ja--",1268,1;
	monster "aldeg_cas02.gat",213,23,"--ja--",1219,1;
	monster "aldeg_cas02.gat",213,23,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
aldeg_cas02.gat,0,0,0	script	#AgitTreasure_L2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1326,1327;
		setarray 'treasure_x,134,135,135,134,132,133,134,135,136,137,137,137,137,137,137,136,135,134,133,132,132,132,132,132;
		setarray 'treasure_y,231,231,230,230,233,233,233,233,233,233,232,231,230,229,228,228,228,228,228,228,229,230,231,232;
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
-	script	#GldFlag_L2a	{
	callfunc "AgitEmblemFlag",1,"aldeg_cas02.gat",220,190;
	close;
OnAgitInit:
OnFlagEmb_L2:
	flagemblem getcastledata("aldeg_cas02.gat",1);
	end;
}
alde_gld.gat,257,166,5	duplicate(#GldFlag_L2a)	ギルドフラッグ#L2a01	722
alde_gld.gat,99,251,4	duplicate(#GldFlag_L2a)	ギルドフラッグ#L2a02	722
alde_gld.gat,99,244,4	duplicate(#GldFlag_L2a)	ギルドフラッグ#L2a03	722

-	script	#GldFlag_L2b	{
	end;
OnAgitInit:
OnFlagEmb_L2:
	flagemblem getcastledata("aldeg_cas02.gat",1);
	end;
}
//aldebaran.gat,149,97,4	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b01	722
//aldeg_cas02.gat,82,71,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b02	722
//aldeg_cas02.gat,67,30,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b03	722
//aldeg_cas02.gat,183,140,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b04	722
//aldeg_cas02.gat,212,152,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b05	722
//aldeg_cas02.gat,108,39,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b06	722
//aldeg_cas02.gat,57,213,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b07	722
//aldeg_cas02.gat,103,53,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b08	722
//aldeg_cas02.gat,73,53,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b09	722
//aldeg_cas02.gat,63,41,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b10	722
//aldeg_cas02.gat,229,6,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b11	722
//aldeg_cas02.gat,230,40,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b12	722
//aldeg_cas02.gat,197,40,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b13	722
//aldeg_cas02.gat,32,213,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b14	722
//aldeg_cas02.gat,121,29,2	duplicate(#GldFlag_L2b)	ギルドフラッグ#L2b15	722

//============================================================
// カプラ職員
//------------------------------------------------------------
aldeg_cas02.gat,84,74,0	script	カプラ職員::AgitKafra_L2	117,{
	callfunc "AgitKafra",17;
	close;
OnAgitInit:
	if(getcastledata("aldeg_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
aldeg_cas02.gat,78,74,0	script	チェンチェンリ	55,{
	callfunc "AgitSteward","L2",'guardian_id,'guardian_x,'guardian_y,134,225;
	close;
OnAgitInit:
	setarray 'guardian_id,	1286,	1286,	1286,	1287,	1287,	1285,	1285,	1285;
	setarray 'guardian_x,	27,	88,	117,	60,	51,	21,	36,	210;
	setarray 'guardian_y,	184,	43,	46,	203,	183,	177,	183,	7;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("aldeg_cas02.gat",'@i+10))
			callguardian "aldeg_cas02.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
aldeg_cas02.gat,139,234,0	script	#AgitMaster_L2	111,{
	callfunc "AgitMaster",78,75;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
aldeg_cas02.gat,194,136,0	script	#AgitDungeon_L2	111,{
	callfunc "AgitDungeon","gld_dun02.gat",79,30;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
aldeg_cas02.gat,135,230,0	script	#AgitBanWarp_L2	139,8,8,{
	callfunc "AgitBanWarp","aldebaran.gat",143,112;
	close;
}
