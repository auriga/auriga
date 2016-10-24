//=========================================================================
// アジトダンジョン行きのスイッチ
//	callfunc "DungeonSwitch","MAP",X,Y;
//-------------------------------------------------------------------------

function	script	DungeonSwitch	{
	mes "[声]";
	mes "試練に挑むならば先へ進むがよい";
	next;
	mes " ";
	mes "小さなレバーがあります。";
	mes "引きますか？";
	next;
	if(select("引く","引かない")==2)
		return;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid && '@gid == getcharid(2)) {
		warp getarg(0),getarg(1),getarg(2);
		end;
	}
	mes " ";
	mes "しかし何も起こらなかった。";
	return;
}


//==========================================
// ルイーナ
//------------------------------------------
aldeg_cas01.gat,211,179,0	script	#DungeonSwitch_L1	111,{
	callfunc "DungeonSwitch","gld_dun02.gat",32,122;
	close;
}

aldeg_cas02.gat,194,136,0	script	#DungeonSwitch_L2	111,{
	callfunc "DungeonSwitch","gld_dun02.gat",79,30;
	close;
}

aldeg_cas03.gat,200,177,0	script	#DungeonSwitch_L3	111,{
	callfunc "DungeonSwitch","gld_dun02.gat",165,38;
	close;
}

aldeg_cas04.gat,76,64,0		script	#DungeonSwitch_L4	111,{
	callfunc "DungeonSwitch","gld_dun02.gat",160,148;
	close;
}

aldeg_cas05.gat,23,205,0		script	#DungeonSwitch_L5	111,{
	callfunc "DungeonSwitch","gld_dun02.gat",103,169;
	close;
}

//==========================================
// ブリトニア
//------------------------------------------
gefg_cas01.gat,78,84,0	script	#DungeonSwitch_B1	111,{
	callfunc "DungeonSwitch","gld_dun04.gat",39,258;
	close;
}

gefg_cas02.gat,167,40,0	script	#DungeonSwitch_B2	111,{
	callfunc "DungeonSwitch","gld_dun04.gat",125,270;
	close;
}

gefg_cas03.gat,221,43,0	script	#DungeonSwitch_B3	111,{
	callfunc "DungeonSwitch","gld_dun04.gat",268,251;
	close;
}

gefg_cas04.gat,58,75,0	script	#DungeonSwitch_B4	111,{
	callfunc "DungeonSwitch","gld_dun04.gat",268,108;
	close;
}

gefg_cas05.gat,65,22,0	script	#DungeonSwitch_B5	111,{
	callfunc "DungeonSwitch","gld_dun04.gat",230,35;
	close;
}

//==========================================
// チュンリム
//------------------------------------------
payg_cas01.gat,101,25,0		script	#DungeonSwitch_C1	111,{
	callfunc "DungeonSwitch","gld_dun01.gat",186,165;
	close;
}

payg_cas02.gat,278,247,0	script	#DungeonSwitch_C2	111,{
	callfunc "DungeonSwitch","gld_dun01.gat",54,165;
	close;
}

payg_cas03.gat,38,42,0		script	#DungeonSwitch_C3	111,{
	callfunc "DungeonSwitch","gld_dun01.gat",54,39;
	close;
}

payg_cas04.gat,52,48,0		script	#DungeonSwitch_C4	111,{
	callfunc "DungeonSwitch","gld_dun01.gat",186,39;
	close;
}

payg_cas05.gat,238,11,0		script	#DungeonSwitch_C5	111,{
	callfunc "DungeonSwitch","gld_dun01.gat",223,202;
	close;
}

//==========================================
// ヴァルキリーレルム
//------------------------------------------
prtg_cas01.gat,94,200,0	script	#DungeonSwitch_V1	111,{
	callfunc "DungeonSwitch","gld_dun03.gat",28,251;
	close;
}

prtg_cas02.gat,84,72,0	script	#DungeonSwitch_V2	111,{
	callfunc "DungeonSwitch","gld_dun03.gat",164,268;
	close;
}

prtg_cas03.gat,5,70,0	script	#DungeonSwitch_V3	111,{
	callfunc "DungeonSwitch","gld_dun03.gat",164,179;
	close;
}

prtg_cas04.gat,56,283,0	script	#DungeonSwitch_V4	111,{
	callfunc "DungeonSwitch","gld_dun03.gat",268,203;
	close;
}

prtg_cas05.gat,212,95,0	script	#DungeonSwitch_V5	111,{
	callfunc "DungeonSwitch","gld_dun03.gat",199,28;
	close;
}
