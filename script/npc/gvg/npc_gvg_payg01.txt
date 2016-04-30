//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Chung-Rim Guild 1	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
payg_cas01.gat,0,0,0	script	#AgitExe_C1	-1,{
OnAgitStart:
	callfunc "AgitEmperium",138,138,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","C1";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",138,138,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","C1";
	end;
OnAgitSummon:
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1277,9;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1208,10;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1262,5;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1102,5;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1115,1;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1129,11;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1282,4;
	areamonster "payg_cas01.gat",0,0,0,0,"--ja--",1253,5;
	monster "payg_cas01.gat",138,138,"--ja--",1150,1;
	monster "payg_cas01.gat",138,138,"--ja--",1115,1;
	monster "payg_cas01.gat",138,138,"--ja--",1208,6;
	monster "payg_cas01.gat",138,138,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
payg_cas01.gat,0,0,0	script	#AgitTreasure_C1	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1344,1345;
		setarray 'treasure_x,289,292,292,289,288,289,290,291,292,293,293,293,293,293,293,292,291,290,289,288,288,288,288,288;
		setarray 'treasure_y, 10, 10,  7,  7, 11, 11, 11, 11, 11, 11, 10,  9,  8,  7,  6,  6,  6,  6,  6,  6,  7,  8,  9, 10;
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
-	script	#GldFlag_C1a	{
	callfunc "AgitEmblemFlag",0,"payg_cas01.gat",54,144;
	close;
OnAgitInit:
OnFlagEmb_C1:
	flagemblem getcastledata("payg_cas01.gat",1);
	end;
}
pay_gld.gat,347,125,2	duplicate(#GldFlag_C1a)	ギルドフラッグ#C1a01	722
pay_gld.gat,125,236,4	duplicate(#GldFlag_C1a)	ギルドフラッグ#C1a02	722
pay_gld.gat,110,233,4	duplicate(#GldFlag_C1a)	ギルドフラッグ#C1a03	722
pay_gld.gat,116,233,4	duplicate(#GldFlag_C1a)	ギルドフラッグ#C1a04	722
pay_gld.gat,91,239,2	duplicate(#GldFlag_C1a)	ギルドフラッグ#C1a05	722

-	script	#GldFlag_C1b	{
	end;
OnAgitInit:
OnFlagEmb_C1:
	flagemblem getcastledata("payg_cas01.gat",1);
	end;
}
//payon.gat,90,322,4		duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b01	722
//payon.gat,166,177,3		duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b02	722
//payg_cas01.gat,238,67,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b03	722
//payg_cas01.gat,233,67,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b04	722
//payg_cas01.gat,221,123,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b05	722
//payg_cas01.gat,221,116,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b06	722
//payg_cas01.gat,206,108,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b07	722
//payg_cas01.gat,212,108,4	duplicate(#GldFlag_C1b)	ギルドフラッグ#C1b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
payg_cas01.gat,128,58,3	script	カプラ職員::AgitKafra_C1	117,{
	callfunc "AgitKafra",16;
	close;
OnAgitInit:
	if(getcastledata("payg_cas01.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
payg_cas01.gat,120,58,4	script	グルナンディー	55,{
	callfunc "AgitSteward","C1",'guardian_id,'guardian_x,'guardian_y,295,8;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1285,	1285,	1285,	1285,	1286;
	setarray 'guardian_x,	229,	225,	222,	99,	65,	36,	51,	138;
	setarray 'guardian_y,	92,	80,	111,	45,	31,	127,	144,	133;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("payg_cas01.gat",'@i+10))
			callguardian "payg_cas01.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
payg_cas01.gat,295,8,0	script	#AgitMaster_C1	111,{
	callfunc "AgitMaster",120,59;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
payg_cas01.gat,101,25,0	script	#AgitDungeon_C1	111,{
	callfunc "AgitDungeon","gld_dun01.gat",186,165;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
payg_cas01.gat,291,8,0	script	#AgitBanWarp_C1	139,6,6,{
	callfunc "AgitBanWarp","payon.gat",100,100;
	close;
}
