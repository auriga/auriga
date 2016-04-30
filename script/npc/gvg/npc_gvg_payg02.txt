//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Chung-Rim Guild 2	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
payg_cas02.gat,0,0,0	script	#AgitExe_C2	-1,{
OnAgitStart:
	callfunc "AgitEmperium",38,25,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","C2";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",38,25,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","C2";
	end;
OnAgitSummon:
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1277,9;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1208,10;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1262,5;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1102,5;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1115,1;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1129,11;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1282,4;
	areamonster "payg_cas02.gat",0,0,0,0,"--ja--",1253,5;
	monster "payg_cas02.gat",38,25,"--ja--",1150,1;
	monster "payg_cas02.gat",38,25,"--ja--",1115,1;
	monster "payg_cas02.gat",38,25,"--ja--",1208,6;
	monster "payg_cas02.gat",38,25,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
payg_cas02.gat,0,0,0	script	#AgitTreasure_C2	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1346,1347;
		setarray 'treasure_x,143,146,146,143,142,143,144,145,146,147,147,147,147,147,147,146,145,144,143,142,142,142,142,142;
		setarray 'treasure_y,146,146,143,143,147,147,147,147,147,147,146,145,144,143,142,142,142,142,142,142,143,144,145,146;
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
-	script	#GldFlag_C2a	{
	callfunc "AgitEmblemFlag",0,"payg_cas02.gat",278,251;
	close;
OnAgitInit:
OnFlagEmb_C2:
	flagemblem getcastledata("payg_cas02.gat",1);
	end;
}
pay_gld.gat,347,116,2	duplicate(#GldFlag_C2a)	ギルドフラッグ#C2a01	722
pay_gld.gat,292,112,6	duplicate(#GldFlag_C2a)	ギルドフラッグ#C2a02	722
pay_gld.gat,292,120,6	duplicate(#GldFlag_C2a)	ギルドフラッグ#C2a03	722
pay_gld.gat,291,135,6	duplicate(#GldFlag_C2a)	ギルドフラッグ#C2a04	722
pay_gld.gat,271,163,0	duplicate(#GldFlag_C2a)	ギルドフラッグ#C2a05	722

-	script	#GldFlag_C2b	{
	end;
OnAgitInit:
OnFlagEmb_C2:
	flagemblem getcastledata("payg_cas02.gat",1);
	end;
}
//payon.gat,97,322,4		duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b01	722
//payon.gat,166,173,3		duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b02	722
//payg_cas02.gat,254,40,6	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b03	722
//payg_cas02.gat,254,48,6	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b04	722
//payg_cas02.gat,202,49,0	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b05	722
//payg_cas02.gat,209,49,0	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b06	722
//payg_cas02.gat,59,282,4	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b07	722
//payg_cas02.gat,70,282,4	duplicate(#GldFlag_C2b)	ギルドフラッグ#C2b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
payg_cas02.gat,22,275,5	script	カプラ職員::AgitKafra_C2	117,{
	callfunc "AgitKafra",16;
	close;
OnAgitInit:
	if(getcastledata("payg_cas02.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
payg_cas02.gat,22,260,7	script	チェリオス	55,{
	callfunc "AgitSteward","C2",'guardian_id,'guardian_x,'guardian_y,141,149;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1285,	1285,	1285,	1285,	1286;
	setarray 'guardian_x,	237,	228,	210,	57,	42,	287,	264,	27;
	setarray 'guardian_y,	54,	72,	41,	241,	241,	257,	272,	20;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("payg_cas02.gat",'@i+10))
			callguardian "payg_cas02.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
payg_cas02.gat,149,149,0	script	#AgitMaster_C2	111,{
	callfunc "AgitMaster",22,261;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
payg_cas02.gat,278,247,0	script	#AgitDungeon_C2	111,{
	callfunc "AgitDungeon","gld_dun01.gat",54,165;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
payg_cas02.gat,145,144,0	script	#AgitBanWarp_C2	139,6,6,{
	callfunc "AgitBanWarp","payon.gat",100,100;
	close;
}
