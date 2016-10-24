//= Auriga Script ==============================================================
// Ragnarok Online GvG Script - Chung-Rim Guild 3	by Blaze
//==============================================================================

//============================================================
// GvGメイン処理
//------------------------------------------------------------
payg_cas03.gat,0,0,0	script	#AgitExe_C3	-1,{
OnAgitStart:
	callfunc "AgitEmperium",268,264,1;
	end;
OnAgitBreak:
	callfunc "AgitBreak","C3";
	end;
OnAgitEliminate:
	callfunc "AgitEmperium",268,264,0;
	end;
OnAgitEnd:
	callfunc "AgitEnd";
	end;
OnGuildBreak:
	callfunc "AgitGiveUp","C3";
	end;
OnAgitSummon:
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1277,9;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1208,10;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1262,5;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1102,5;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1150,1;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1115,1;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1129,11;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1276,5;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1282,4;
	areamonster "payg_cas03.gat",0,0,0,0,"--ja--",1253,5;
	monster "payg_cas03.gat",268,264,"--ja--",1150,1;
	monster "payg_cas03.gat",268,264,"--ja--",1115,1;
	monster "payg_cas03.gat",268,264,"--ja--",1208,6;
	monster "payg_cas03.gat",268,264,"--ja--",1276,5;
	end;
}

//============================================================
// 宝箱
//------------------------------------------------------------
payg_cas03.gat,0,0,0	script	#AgitTreasure_C3	-1,{
OnClock0000:
	if('treasure_id[0] == 0) {
		setarray 'treasure_id,1348,1349;
		setarray 'treasure_x,158,159,159,158,156,157,158,159,160,161,161,161,161,161,161,160,159,158,157,156,156,156,156,156;
		setarray 'treasure_y,169,169,168,168,171,171,171,171,171,171,170,169,168,167,166,166,166,166,166,166,167,168,169,170;
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
-	script	#GldFlag_C3a	{
	callfunc "AgitEmblemFlag",0,"payg_cas03.gat",9,263;
	close;
OnAgitInit:
OnFlagEmb_C3:
	flagemblem getcastledata("payg_cas03.gat",1);
	end;
}
pay_gld.gat,341,106,0	duplicate(#GldFlag_C3a)	ギルドフラッグ#C3a01	722
pay_gld.gat,321,298,2	duplicate(#GldFlag_C3a)	ギルドフラッグ#C3a02	722
pay_gld.gat,321,289,2	duplicate(#GldFlag_C3a)	ギルドフラッグ#C3a03	722
pay_gld.gat,327,304,1	duplicate(#GldFlag_C3a)	ギルドフラッグ#C3a04	722
pay_gld.gat,333,254,4	duplicate(#GldFlag_C3a)	ギルドフラッグ#C3a05	722

-	script	#GldFlag_C3b	{
	end;
OnAgitInit:
OnFlagEmb_C3:
	flagemblem getcastledata("payg_cas03.gat",1);
	end;
}
//payon.gat,113,322,4		duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b01	722
//payon.gat,166,169,3		duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b02	722
//payg_cas03.gat,236,54,2	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b03	722
//payg_cas03.gat,236,45,2	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b04	722
//payg_cas03.gat,259,66,4	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b05	722
//payg_cas03.gat,266,66,4	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b06	722
//payg_cas03.gat,34,31,4	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b07	722
//payg_cas03.gat,43,31,4	duplicate(#GldFlag_C3b)	ギルドフラッグ#C3b08	722

//============================================================
// カプラ職員
//------------------------------------------------------------
payg_cas03.gat,9,263,5	script	カプラ職員::AgitKafra_C3	117,{
	callfunc "AgitKafra",16;
	close;
OnAgitInit:
	if(getcastledata("payg_cas03.gat",9) == 0)
		hideonnpc;
	end;
}

//============================================================
// 執事
//------------------------------------------------------------
payg_cas03.gat,50,261,3	script	ケリオ	55,{
	callfunc "AgitSteward","C3",'guardian_id,'guardian_x,'guardian_y,163,167;
	close;
OnAgitInit:
	setarray 'guardian_id,	1285,	1285,	1285,	1285,	1285,	1285,	1285,	1286;
	setarray 'guardian_x,	245,	269,	36,	41,	39,	19,	37,	268;
	setarray 'guardian_y,	37,	51,	39,	39,	65,	276,	277,	244;
	for(set '@i,0; '@i < 8; set '@i,'@i+1) {
		if(getcastledata("payg_cas03.gat",'@i+10))
			callguardian "payg_cas03.gat",'guardian_x['@i],'guardian_y['@i],"--ja--",'guardian_id['@i],1,"",'@i+1;
	}
	end;
}

//============================================================
// マスタールームのスイッチ
//------------------------------------------------------------
payg_cas03.gat,163,167,0	script	#AgitMaster_C3	111,{
	callfunc "AgitMaster",50,261;
	close;
}

//============================================================
// ギルドダンジョンへのスイッチ
//------------------------------------------------------------
payg_cas03.gat,38,42,0	script	#AgitDungeon_C3	111,{
	callfunc "AgitDungeon","gld_dun01.gat",54,39;
	close;
}

//============================================================
// マスタールーム制限
//------------------------------------------------------------
payg_cas03.gat,159,168,0	script	#AgitBanWarp_C3	139,6,6,{
	callfunc "AgitBanWarp","payon.gat",100,100;
	close;
}
