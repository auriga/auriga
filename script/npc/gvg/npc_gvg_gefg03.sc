//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Britoniah Guild 3	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
gefg_cas03.gat,0,0,0	script	#AgitExe_B3	-1,{
OnAgitStart:
	callfunc "AgitEmperium",244,166,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","B3";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",244,166,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","B3";
	end;
OnAgitSummon:
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1117,10;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1263,11;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1102,10;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1130,10;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1140,20;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1163,9;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1275,1;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1219,1;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "gefg_cas03.gat",0,0,0,0,"--ja--",1159,1;
	monster "gefg_cas03.gat",244,166,"--ja--",1203,1;
	monster "gefg_cas03.gat",244,166,"--ja--",1087,1;
	monster "gefg_cas03.gat",244,166,"--ja--",1213,10;
	monster "gefg_cas03.gat",244,166,"--ja--",1189,10;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
gefg_cas03.gat,0,0,0	script	#AgitTreasure_B3	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1338,1339;
		setarray 'treasure_x,269,270,270,269,267,268,269,270,271,272,272,272,272,272,272,271,270,269,268,267,267,267,267,267;
		setarray 'treasure_y,291,291,290,290,293,293,293,293,293,293,292,291,290,289,288,288,288,288,288,288,289,290,291,292;
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
-	script	#GldFlag_B3a	{
	callfunc "AgitEmblemFlag",0,"gefg_cas03.gat",221,30;
	close;
OnAgitInit:
OnFlagEmb_B3:
	flagemblem getcastledata("gefg_cas03.gat",1);
	end;
}
gef_fild07.gat,330,176,2	duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a01	722
gef_fild13.gat,78,182,4		duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a02	722
gef_fild13.gat,87,182,4		duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a03	722
gef_fild13.gat,73,295,7		duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a04	722
gef_fild13.gat,113,274,7	duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a05	722
gef_fild13.gat,144,235,6	duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a06	722
gef_fild13.gat,144,244,6	duplicate(#GldFlag_B3a)	ギルドフラッグ#B3a07	722

-	script	#GldFlag_B3b	{
	end;
OnAgitInit:
OnFlagEmb_B3:
	flagemblem getcastledata("gefg_cas03.gat",1);
	end;
}
//geffen.gat,120,132,8		duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b01	722
//gefg_cas03.gat,122,220,6	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b02	722
//gefg_cas03.gat,122,229,6	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b03	722
//gefg_cas03.gat,91,257,7	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b04	722
//gefg_cas03.gat,52,276,7	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b05	722
//gefg_cas03.gat,56,164,4	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b06	722
//gefg_cas03.gat,65,164,4	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b07	722
//gefg_cas03.gat,37,214,1	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b08	722
//gefg_cas03.gat,34,208,1	duplicate(#GldFlag_B3b)	ギルドフラッグ#B3b09	722

//============================================================
// カプラ職員
//------------------------------------------------------------
gefg_cas03.gat,116,89,5	script	カプラ職員::AgitKafra_B3	117,{
	callfunc "AgitKafra",15;
	close;
OnAgitInit:
	if(getcastledata("gefg_cas03.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
gefg_cas03.gat,106,23,5	script	ジャン	55,{
	callfunc "AgitSteward","B3",'guardian_id,'guardian_x,'guardian_y,275,289;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1287,	1287,	1287,	1286,	1286,	1286;
	setarray 'guardian_x,	48,	113,	48,	157,	243,	157,	234,	238;
	setarray 'guardian_y,	176,	214,	207,	62,	41,	45,	25,	160;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("gefg_cas03.gat",'@i+10))
			callguardian "gefg_cas03.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
gefg_cas03.gat,275,289,0	script	#AgitMaster_B3	111,{
	callfunc "AgitMaster",106,24;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
gefg_cas03.gat,221,43,0	script	#AgitDungeon_B3	111,{
	callfunc "AgitDungeon","gld_dun04.gat",268,251;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
gefg_cas03.gat,271,290,0	script	#AgitBanWarp_B3	139,6,6,{
	callfunc "AgitBanWarp","geffen.gat",120,38;
	close;
}
