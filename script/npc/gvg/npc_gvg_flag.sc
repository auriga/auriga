//=========================================================================
// ギルドフラッグ共通ファンクション
//	callfunc "FlagSrc",AreaIndex,"MAP",X,Y;
//
// ■ 引数の詳細
//	AreaIndex -> 0:ルイーナ、1:その他
//-------------------------------------------------------------------------

function	script	FlagSrc	{
	set '@gid,getcastledata(getarg(1),1);
	if('@gid > 0 && getcharid(2)=='@gid && getarg(2)) {	//城主ギルドでX座標の値があればtrue
		mes "[ 声 ]";
		mes "勇者よ…";
		mes "君の地に帰るか？";
		next;
		if(select("砦に帰る","やめる")==1) {
			//選択待ち中に城主が変更された場合を考慮して再度チェック
			set '@gid,getcastledata(getarg(1),1);
			if('@gid > 0 && getcharid(2)=='@gid && getarg(2)) {
				warp getarg(1),getarg(2),getarg(3);
				end;
			}
		}
		return;
	}
	mes "[ ルーンミッドガッツ王国領 ]";
	mes " ";
	mes "1.";
	switch(getarg(0)) {
	case 0:
		mes "こちらはルーンミッドガッツ王国と";
		mes "シュバルツバルド共和国の協定により、";
		break;
	case 1:
		mes "こちらはルーンミッドガッツ王国に";
		mes "よって";
		break;
	}
	if('@gid <= 0) {
		mes "正式所有者がないアジトであることを";
		mes "公表する。";
		next;
		mes " ";
		mes "2.";
		mes "こちらを守っている凄じい";
		mes "試練に勝って、エンペリウムを";
		mes "破壊する勇者には国王が";
		mes "認定するアジト所有権が附与される";
	}
	else {
		mes "ギルド ^ff0000 " +getguildname('@gid)+ " ^000000の";
		mes "所有であることを認められている。";
		next;
		mes " ";
		mes "2.";
		mes "^ff0000 " +getguildname('@gid)+ " ^000000 のマスターは";
		mes "^ff0000 " +getguildmaster('@gid)+ " ^000000である。";
		mes "これに異議のある者は、剣を取り";
		mes "力を以って名誉を勝ち取りなさい。";
	}
	return;
}


//-------------------------------------------
// ■ Interサーバ接続時にOnAgitInitが、
//    城主変更時にOnFlagEmb_XYが呼び出される
//-------------------------------------------

//==========================================
// L1 : ルイーナ
//------------------------------------------
-	script	GdFlag_L1	722,{
	callfunc "FlagSrc",0,"aldeg_cas01.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_L1:
	if(strnpcinfo(0) != "GdFlag_L1")
		flagemblem getcastledata("aldeg_cas01.gat",1);
	end;
}

alde_gld.gat,257,153,7	script	ギルドフラッグ#L1-00	722,{
	callfunc "FlagSrc",0,"aldeg_cas01.gat",218,170;
	close;
OnAgitInit:
OnFlagEmb_L1:
	flagemblem getcastledata("aldeg_cas01.gat",1);
	end;
}

alde_gld.gat,61,87,6		duplicate(GdFlag_L1)	ギルドフラッグ#L1-01	722
alde_gld.gat,61,79,6		duplicate(GdFlag_L1)	ギルドフラッグ#L1-02	722
alde_gld.gat,45,87,8		duplicate(GdFlag_L1)	ギルドフラッグ#L1-03	722
alde_gld.gat,51,87,8		duplicate(GdFlag_L1)	ギルドフラッグ#L1-04	722
//aldeg_cas01.gat,30,248,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-05	722
//aldeg_cas01.gat,30,246,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-06	722
//aldeg_cas01.gat,37,248,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-07	722
//aldeg_cas01.gat,37,246,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-08	722
//aldeg_cas01.gat,95,80,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-09	722
//aldeg_cas01.gat,95,59,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-10	722
//aldeg_cas01.gat,62,75,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-11	722
//aldeg_cas01.gat,70,75,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-12	722
//aldeg_cas01.gat,74,75,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-13	722
//aldeg_cas01.gat,62,64,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-14	722
//aldeg_cas01.gat,66,64,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-15	722
//aldeg_cas01.gat,70,64,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-16	722
//aldeg_cas01.gat,74,64,2		duplicate(GdFlag_L1)	ギルドフラッグ#L1-17	722
//aldeg_cas01.gat,203,150,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-18	722
//aldeg_cas01.gat,210,150,4	duplicate(GdFlag_L1)	ギルドフラッグ#L1-19	722

//==========================================
// L2 : ルイーナ
//------------------------------------------
-	script	GdFlag_L2	722,{
	callfunc "FlagSrc",0,"aldeg_cas02.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_L2:
	if(strnpcinfo(0) != "GdFlag_L2")
		flagemblem getcastledata("aldeg_cas02.gat",1);
	end;
}

alde_gld.gat,257,166,5	script	ギルドフラッグ#L2-00	722,{
	callfunc "FlagSrc",0,"aldeg_cas02.gat",84,74;
	close;
OnAgitInit:
OnFlagEmb_L2:
	flagemblem getcastledata("aldeg_cas02.gat",1);
	end;
}

//aldeg_cas02.gat,82,71,2		duplicate(GdFlag_L2)	ギルドフラッグ#L2-01	722
//aldeg_cas02.gat,67,30,2		duplicate(GdFlag_L2)	ギルドフラッグ#L2-02	722
//aldeg_cas02.gat,183,140,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-03	722
//aldeg_cas02.gat,212,152,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-04	722
//aldeg_cas02.gat,108,39,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-05	722
//aldeg_cas02.gat,57,213,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-06	722
//aldeg_cas02.gat,91,181,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-07	722
//aldeg_cas02.gat,103,53,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-08	722
//aldeg_cas02.gat,73,53,2		duplicate(GdFlag_L2)	ギルドフラッグ#L2-09	722
//aldeg_cas02.gat,63,41,2		duplicate(GdFlag_L2)	ギルドフラッグ#L2-10	722
//aldeg_cas02.gat,229,6,2		duplicate(GdFlag_L2)	ギルドフラッグ#L2-11	722
//aldeg_cas02.gat,230,40,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-12	722
//aldeg_cas02.gat,197,40,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-13	722
//aldeg_cas02.gat,32,213,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-14	722
//aldeg_cas02.gat,88,180,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-15	722
//aldeg_cas02.gat,121,29,2	duplicate(GdFlag_L2)	ギルドフラッグ#L2-16	722

//==========================================
// L3 : ルイーナ
//------------------------------------------
-	script	GdFlag_L3	722,{
	callfunc "FlagSrc",0,"aldeg_cas03.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_L3:
	if(strnpcinfo(0) != "GdFlag_L3")
		flagemblem getcastledata("aldeg_cas03.gat",1);
	end;
}

alde_gld.gat,262,153,7	script	ギルドフラッグ#L3-00	722,{
	callfunc "FlagSrc",0,"aldeg_cas03.gat",118,76;
	close;
OnAgitInit:
OnFlagEmb_L3:
	flagemblem getcastledata("aldeg_cas03.gat",1);
	end;
}

//aldeg_cas03.gat,176,175,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-01	722
//aldeg_cas03.gat,85,103,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-02	722
//aldeg_cas03.gat,77,115,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-03	722
//aldeg_cas03.gat,77,215,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-04	722
//aldeg_cas03.gat,112,107,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-05	722
//aldeg_cas03.gat,112,117,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-06	722
//aldeg_cas03.gat,69,71,2		duplicate(GdFlag_L3)	ギルドフラッグ#L3-07	722
//aldeg_cas03.gat,91,69,2		duplicate(GdFlag_L3)	ギルドフラッグ#L3-08	722
//aldeg_cas03.gat,108,60,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-09	722
//aldeg_cas03.gat,121,73,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-10	722
//aldeg_cas03.gat,121,73,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-11	722
//aldeg_cas03.gat,75,102,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-12	722
//aldeg_cas03.gat,199,169,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-13	722
//aldeg_cas03.gat,181,179,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-14	722
//aldeg_cas03.gat,192,44,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-15	722
//aldeg_cas03.gat,88,108,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-16	722
//aldeg_cas03.gat,208,145,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-17	722
//aldeg_cas03.gat,207,75,2	duplicate(GdFlag_L3)	ギルドフラッグ#L3-18	722
//aldeg_cas03.gat,96,62,2		duplicate(GdFlag_L3)	ギルドフラッグ#L3-19	722

//==========================================
// L4 : ルイーナ
//------------------------------------------
-	script	GdFlag_L4	722,{
	callfunc "FlagSrc",0,"aldeg_cas04.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_L4:
	if(strnpcinfo(0) != "GdFlag_L4")
		flagemblem getcastledata("aldeg_cas04.gat",1);
	end;
}

alde_gld.gat,262,166,5	script	ギルドフラッグ#L4-00	722,{
	callfunc "FlagSrc",0,"aldeg_cas04.gat",45,88;
	close;
OnAgitInit:
OnFlagEmb_L4:
	flagemblem getcastledata("aldeg_cas04.gat",1);
	end;
}

//aldeg_cas04.gat,167,61,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-01	722
//aldeg_cas04.gat,164,90,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-02	722
//aldeg_cas04.gat,143,209,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-03	722
//aldeg_cas04.gat,129,193,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-04	722
//aldeg_cas04.gat,112,206,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-05	722
//aldeg_cas04.gat,113,212,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-06	722
//aldeg_cas04.gat,77,117,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-07	722
//aldeg_cas04.gat,186,42,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-08	722
//aldeg_cas04.gat,30,69,2		duplicate(GdFlag_L4)	ギルドフラッグ#L4-09	722
//aldeg_cas04.gat,55,97,2		duplicate(GdFlag_L4)	ギルドフラッグ#L4-10	722
//aldeg_cas04.gat,45,98,2		duplicate(GdFlag_L4)	ギルドフラッグ#L4-11	722
//aldeg_cas04.gat,33,116,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-12	722
//aldeg_cas04.gat,130,180,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-13	722
//aldeg_cas04.gat,129,193,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-14	722
//aldeg_cas04.gat,142,209,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-15	722
//aldeg_cas04.gat,33,107,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-16	722
//aldeg_cas04.gat,133,220,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-17	722
//aldeg_cas04.gat,169,22,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-18	722
//aldeg_cas04.gat,169,15,2	duplicate(GdFlag_L4)	ギルドフラッグ#L4-19	722

//==========================================
// L5 : ルイーナ
//------------------------------------------
-	script	GdFlag_L5	722,{
	callfunc "FlagSrc",0,"aldeg_cas05.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_L5:
	if(strnpcinfo(0) != "GdFlag_L5")
		flagemblem getcastledata("aldeg_cas05.gat",1);
	end;
}

alde_gld.gat,267,153,7	script	ギルドフラッグ#L5-00	722,{
	callfunc "FlagSrc",0,"aldeg_cas05.gat",31,190;
	close;
OnAgitInit:
OnFlagEmb_L5:
	flagemblem getcastledata("aldeg_cas05.gat",1);
	end;
}

//aldeg_cas05.gat,170,85,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-01	722
//aldeg_cas05.gat,142,212,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-02	722
//aldeg_cas05.gat,149,196,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-03	722
//aldeg_cas05.gat,41,180,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-04	722
//aldeg_cas05.gat,38,201,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-05	722
//aldeg_cas05.gat,65,182,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-06	722
//aldeg_cas05.gat,65,205,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-07	722
//aldeg_cas05.gat,10,218,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-08	722
//aldeg_cas05.gat,164,201,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-09	722
//aldeg_cas05.gat,216,96,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-10	722
//aldeg_cas05.gat,217,80,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-11	722
//aldeg_cas05.gat,14,117,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-12	722
//aldeg_cas05.gat,10,225,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-13	722
//aldeg_cas05.gat,187,59,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-14	722
//aldeg_cas05.gat,154,51,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-15	722
//aldeg_cas05.gat,22,211,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-16	722
//aldeg_cas05.gat,150,202,2	duplicate(GdFlag_L5)	ギルドフラッグ#L5-17	722

//==========================================
// B1 : ブリトニア
//------------------------------------------
-	script	GdFlag_B1	722,{
	callfunc "FlagSrc",1,"gefg_cas01.gat",0,0;
	close;
OnAgit:
OnFlagEmb_B1:
	if(strnpcinfo(0) != "GdFlag_B1")
		flagemblem getcastledata("gefg_cas01.gat",1);
	end;
}

gef_fild07.gat,330,199,2	script	ギルドフラッグ#B1-00	722,{
	callfunc "FlagSrc",1,"gefg_cas01.gat",83,47;
	close;
OnAgitInit:
OnFlagEmb_B1:
	flagemblem getcastledata("gefg_cas01.gat",1);
	end;
}

gef_fild13.gat,148,51,5		duplicate(GdFlag_B1)	ギルドフラッグ#B1-01	722
gef_fild13.gat,155,54,5		duplicate(GdFlag_B1)	ギルドフラッグ#B1-02	722
gef_fild13.gat,212,79,6		duplicate(GdFlag_B1)	ギルドフラッグ#B1-03	722
gef_fild13.gat,211,71,6		duplicate(GdFlag_B1)	ギルドフラッグ#B1-04	722
//gefg_cas01.gat,28,157,4		duplicate(GdFlag_B1)	ギルドフラッグ#B1-05	722
//gefg_cas01.gat,22,156,5		duplicate(GdFlag_B1)	ギルドフラッグ#B1-06	722
//gefg_cas01.gat,68,185,3		duplicate(GdFlag_B1)	ギルドフラッグ#B1-07	722
//gefg_cas01.gat,17,171,5		duplicate(GdFlag_B1)	ギルドフラッグ#B1-08	722
//gefg_cas01.gat,59,16,4		duplicate(GdFlag_B1)	ギルドフラッグ#B1-09	722
//gefg_cas01.gat,64,16,4		duplicate(GdFlag_B1)	ギルドフラッグ#B1-10	722

//==========================================
// B2 : ブリトニア
//------------------------------------------
-	script	GdFlag_B2	722,{
	callfunc "FlagSrc",1,"gefg_cas02.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_B2:
	if(strnpcinfo(0) != "GdFlag_B2")
		flagemblem getcastledata("gefg_cas02.gat",1);
	end;
}

gef_fild07.gat,330,204,2	script	ギルドフラッグ#B2-00	722,{
	callfunc "FlagSrc",1,"gefg_cas02.gat",23,66;
	close;
OnAgitInit:
OnFlagEmb_B2:
	flagemblem getcastledata("gefg_cas02.gat",1);
	end;
}

gef_fild13.gat,303,243,4	duplicate(GdFlag_B2)	ギルドフラッグ#B2-01	722
gef_fild13.gat,312,243,4	duplicate(GdFlag_B2)	ギルドフラッグ#B2-02	722
gef_fild13.gat,290,243,4	duplicate(GdFlag_B2)	ギルドフラッグ#B2-03	722
gef_fild13.gat,324,243,4	duplicate(GdFlag_B2)	ギルドフラッグ#B2-04	722
//gefg_cas02.gat,65,130,5		duplicate(GdFlag_B2)	ギルドフラッグ#B2-05	722
//gefg_cas02.gat,30,123,5		duplicate(GdFlag_B2)	ギルドフラッグ#B2-06	722
//gefg_cas02.gat,65,139,6		duplicate(GdFlag_B2)	ギルドフラッグ#B2-07	722
//gefg_cas02.gat,37,177,6		duplicate(GdFlag_B2)	ギルドフラッグ#B2-08	722
//gefg_cas02.gat,37,168,6		duplicate(GdFlag_B2)	ギルドフラッグ#B2-09	722
//gefg_cas02.gat,68,47,2		duplicate(GdFlag_B2)	ギルドフラッグ#B2-10	722
//gefg_cas02.gat,68,36,2		duplicate(GdFlag_B2)	ギルドフラッグ#B2-11	722

//==========================================
// B3 : ブリトニア
//------------------------------------------
-	script	GdFlag_B3	722,{
	callfunc "FlagSrc",1,"gefg_cas03.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_B3:
	if(strnpcinfo(0) != "GdFlag_B3")
		flagemblem getcastledata("gefg_cas03.gat",1);
	end;
}

gef_fild07.gat,330,176,2	script	ギルドフラッグ#B3-00	722,{
	callfunc "FlagSrc",1,"gefg_cas03.gat",116,89;
	close;
OnAgitInit:
OnFlagEmb_B3:
	flagemblem getcastledata("gefg_cas03.gat",1);
	end;
}

gef_fild13.gat,78,182,4		duplicate(GdFlag_B3)	ギルドフラッグ#B3-01	722
gef_fild13.gat,87,182,4		duplicate(GdFlag_B3)	ギルドフラッグ#B3-02	722
gef_fild13.gat,73,295,7		duplicate(GdFlag_B3)	ギルドフラッグ#B3-03	722
gef_fild13.gat,113,274,7	duplicate(GdFlag_B3)	ギルドフラッグ#B3-04	722
gef_fild13.gat,144,235,6	duplicate(GdFlag_B3)	ギルドフラッグ#B3-05	722
gef_fild13.gat,144,244,4	duplicate(GdFlag_B3)	ギルドフラッグ#B3-06	722
//gefg_cas03.gat,122,220,6	duplicate(GdFlag_B3)	ギルドフラッグ#B3-07	722
//gefg_cas03.gat,122,229,6	duplicate(GdFlag_B3)	ギルドフラッグ#B3-08	722
//gefg_cas03.gat,91,257,7		duplicate(GdFlag_B3)	ギルドフラッグ#B3-09	722
//gefg_cas03.gat,52,276,7		duplicate(GdFlag_B3)	ギルドフラッグ#B3-10	722
//gefg_cas03.gat,56,164,4		duplicate(GdFlag_B3)	ギルドフラッグ#B3-11	722
//gefg_cas03.gat,65,164,4		duplicate(GdFlag_B3)	ギルドフラッグ#B3-12	722
//gefg_cas03.gat,37,214,1		duplicate(GdFlag_B3)	ギルドフラッグ#B3-13	722
//gefg_cas03.gat,34,208,1		duplicate(GdFlag_B3)	ギルドフラッグ#B3-14	722

//==========================================
// B4 : ブリトニア
//------------------------------------------
-	script	GdFlag_B4	722,{
	callfunc "FlagSrc",1,"gefg_cas04.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_B4:
	if(strnpcinfo(0) != "GdFlag_B4")
		flagemblem getcastledata("gefg_cas04.gat",1);
	end;
}

gef_fild07.gat,330,171,2	script	ギルドフラッグ#B4-00	722,{
	callfunc "FlagSrc",1,"gefg_cas04.gat",59,70;
	close;
OnAgitInit:
OnFlagEmb_B4:
	flagemblem getcastledata("gefg_cas04.gat",1);
	end;
}

gef_fild13.gat,190,283,3	duplicate(GdFlag_B4)	ギルドフラッグ#B4-01	722
gef_fild13.gat,199,274,3	duplicate(GdFlag_B4)	ギルドフラッグ#B4-02	722
//gefg_cas04.gat,24,157,4		duplicate(GdFlag_B4)	ギルドフラッグ#B4-03	722
//gefg_cas04.gat,35,158,4		duplicate(GdFlag_B4)	ギルドフラッグ#B4-04	722
//gefg_cas04.gat,44,184,4		duplicate(GdFlag_B4)	ギルドフラッグ#B4-05	722
//gefg_cas04.gat,51,184,4		duplicate(GdFlag_B4)	ギルドフラッグ#B4-06	722
//gefg_cas04.gat,39,212,7		duplicate(GdFlag_B4)	ギルドフラッグ#B4-07	722
//gefg_cas04.gat,29,212,1		duplicate(GdFlag_B4)	ギルドフラッグ#B4-08	722
//gefg_cas04.gat,24,73,1		duplicate(GdFlag_B4)	ギルドフラッグ#B4-09	722
//gefg_cas04.gat,35,73,4		duplicate(GdFlag_B4)	ギルドフラッグ#B4-10	722

//==========================================
// B5 : ブリトニア
//------------------------------------------
-	script	GdFlag_B5	722,{
	callfunc "FlagSrc",1,"gefg_cas05.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_B5:
	if(strnpcinfo(0) != "GdFlag_B5")
		flagemblem getcastledata("gefg_cas05.gat",1);
	end;
}

gef_fild07.gat,330,166,2	script	ギルドフラッグ#B5-00	722,{
	callfunc "FlagSrc",1,"gefg_cas05.gat",61,52;
	close;
OnAgitInit:
OnFlagEmb_B5:
	flagemblem getcastledata("gefg_cas05.gat",1);
	end;
}

gef_fild13.gat,302,87,7		duplicate(GdFlag_B5)	ギルドフラッグ#B5-01	722
gef_fild13.gat,313,83,0		duplicate(GdFlag_B5)	ギルドフラッグ#B5-02	722
gef_fild13.gat,252,51,2		duplicate(GdFlag_B5)	ギルドフラッグ#B5-03	722
gef_fild13.gat,26,147,2		duplicate(GdFlag_B5)	ギルドフラッグ#B5-04	722
//gefg_cas05.gat,77,185,7		duplicate(GdFlag_B5)	ギルドフラッグ#B5-05	722
//gefg_cas05.gat,92,181,0		duplicate(GdFlag_B5)	ギルドフラッグ#B5-06	722
//gefg_cas05.gat,83,158,1		duplicate(GdFlag_B5)	ギルドフラッグ#B5-07	722
//gefg_cas05.gat,62,144,7		duplicate(GdFlag_B5)	ギルドフラッグ#B5-08	722
//gefg_cas05.gat,62,66,4		duplicate(GdFlag_B5)	ギルドフラッグ#B5-09	722
//gefg_cas05.gat,69,66,4		duplicate(GdFlag_B5)	ギルドフラッグ#B5-10	722

//==========================================
// C1 : チュンリム
//------------------------------------------
-	script	GdFlag_C1	722,{
	callfunc "FlagSrc",1,"payg_cas01.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_C1:
	if(strnpcinfo(0) != "GdFlag_C1")
		flagemblem getcastledata("payg_cas01.gat",1);
	end;
}

pay_gld.gat,347,125,2	script	ギルドフラッグ#C1-00	722,{
	callfunc "FlagSrc",1,"payg_cas01.gat",212,108;
	close;
OnAgitInit:
OnFlagEmb_C1:
	flagemblem getcastledata("payg_cas01.gat",1);
	end;
}

pay_gld.gat,125,236,4		duplicate(GdFlag_C1)	ギルドフラッグ#C1-01	722
pay_gld.gat,110,233,4		duplicate(GdFlag_C1)	ギルドフラッグ#C1-02	722
pay_gld.gat,116,233,4		duplicate(GdFlag_C1)	ギルドフラッグ#C1-03	722
pay_gld.gat,91,239,2		duplicate(GdFlag_C1)	ギルドフラッグ#C1-04	722
//payg_cas01.gat,238,67,4		duplicate(GdFlag_C1)	ギルドフラッグ#C1-05	722
//payg_cas01.gat,233,67,4		duplicate(GdFlag_C1)	ギルドフラッグ#C1-06	722
//payg_cas01.gat,221,123,4	duplicate(GdFlag_C1)	ギルドフラッグ#C1-07	722
//payg_cas01.gat,221,116,4	duplicate(GdFlag_C1)	ギルドフラッグ#C1-08	722
//payg_cas01.gat,206,108,4	duplicate(GdFlag_C1)	ギルドフラッグ#C1-09	722
//payg_cas01.gat,212,108,4	duplicate(GdFlag_C1)	ギルドフラッグ#C1-10	722

//==========================================
// C2 : チュンリム
//------------------------------------------
-	script	GdFlag_C2	722,{
	callfunc "FlagSrc",1,"payg_cas02.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_C2:
	if(strnpcinfo(0) != "GdFlag_C2")
		flagemblem getcastledata("payg_cas02.gat",1);
	end;
}

pay_gld.gat,347,116,2	script	ギルドフラッグ#C2-00	722,{
	callfunc "FlagSrc",1,"payg_cas02.gat",22,275;
	close;
OnAgitInit:
OnFlagEmb_C2:
	flagemblem getcastledata("payg_cas02.gat",1);
	end;
}

pay_gld.gat,292,112,6		duplicate(GdFlag_C2)	ギルドフラッグ#C2-01	722
pay_gld.gat,292,120,6		duplicate(GdFlag_C2)	ギルドフラッグ#C2-02	722
pay_gld.gat,291,135,6		duplicate(GdFlag_C2)	ギルドフラッグ#C2-03	722
pay_gld.gat,271,163,0		duplicate(GdFlag_C2)	ギルドフラッグ#C2-04	722
//payg_cas02.gat,254,40,6		duplicate(GdFlag_C2)	ギルドフラッグ#C2-05	722
//payg_cas02.gat,254,48,6		duplicate(GdFlag_C2)	ギルドフラッグ#C2-06	722
//payg_cas02.gat,202,49,0		duplicate(GdFlag_C2)	ギルドフラッグ#C2-07	722
//payg_cas02.gat,209,49,0		duplicate(GdFlag_C2)	ギルドフラッグ#C2-08	722
//payg_cas02.gat,59,282,4		duplicate(GdFlag_C2)	ギルドフラッグ#C2-09	722
//payg_cas02.gat,70,282,4		duplicate(GdFlag_C2)	ギルドフラッグ#C2-10	722

//==========================================
// C3 : チュンリム
//------------------------------------------
-	script	GdFlag_C3	722,{
	callfunc "FlagSrc",1,"payg_cas03.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_C3:
	if(strnpcinfo(0) != "GdFlag_C3")
		flagemblem getcastledata("payg_cas03.gat",1);
	end;
}

pay_gld.gat,341,106,0	script	ギルドフラッグ#C3-00	722,{
	callfunc "FlagSrc",1,"payg_cas03.gat",9,263;
	close;
OnAgitInit:
OnFlagEmb_C3:
	flagemblem getcastledata("payg_cas03.gat",1);
	end;
}

pay_gld.gat,321,298,2		duplicate(GdFlag_C3)	ギルドフラッグ#C3-01	722
pay_gld.gat,321,289,2		duplicate(GdFlag_C3)	ギルドフラッグ#C3-02	722
pay_gld.gat,327,304,1		duplicate(GdFlag_C3)	ギルドフラッグ#C3-03	722
pay_gld.gat,333,254,4		duplicate(GdFlag_C3)	ギルドフラッグ#C3-04	722
//payg_cas03.gat,236,54,2		duplicate(GdFlag_C3)	ギルドフラッグ#C3-05	722
//payg_cas03.gat,236,45,2		duplicate(GdFlag_C3)	ギルドフラッグ#C3-06	722
//payg_cas03.gat,259,66,4		duplicate(GdFlag_C3)	ギルドフラッグ#C3-07	722
//payg_cas03.gat,266,66,4		duplicate(GdFlag_C3)	ギルドフラッグ#C3-08	722
//payg_cas03.gat,34,31,4		duplicate(GdFlag_C3)	ギルドフラッグ#C3-09	722
//payg_cas03.gat,43,31,4		duplicate(GdFlag_C3)	ギルドフラッグ#C3-10	722

//==========================================
// C4 : チュンリム
//------------------------------------------
-	script	GdFlag_C4	722,{
	callfunc "FlagSrc",1,"payg_cas04.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_C4:
	if(strnpcinfo(0) != "GdFlag_C4")
		flagemblem getcastledata("payg_cas04.gat",1);
	end;
}

pay_gld.gat,330,106,0	script	ギルドフラッグ#C4-00	722,{
	callfunc "FlagSrc",1,"payg_cas04.gat",40,235;
	close;
OnAgitInit:
OnFlagEmb_C4:
	flagemblem getcastledata("payg_cas04.gat",1);
	end;
}

pay_gld.gat,137,160,0		duplicate(GdFlag_C4)	ギルドフラッグ#C4-01	722
pay_gld.gat,143,160,0		duplicate(GdFlag_C4)	ギルドフラッグ#C4-02	722
pay_gld.gat,133,151,2		duplicate(GdFlag_C4)	ギルドフラッグ#C4-03	722
pay_gld.gat,153,166,1		duplicate(GdFlag_C4)	ギルドフラッグ#C4-04	722
//payg_cas04.gat,255,259,0	duplicate(GdFlag_C4)	ギルドフラッグ#C4-05	722
//payg_cas04.gat,248,259,0	duplicate(GdFlag_C4)	ギルドフラッグ#C4-06	722
//payg_cas04.gat,248,168,6	duplicate(GdFlag_C4)	ギルドフラッグ#C4-07	722
//payg_cas04.gat,248,160,6	duplicate(GdFlag_C4)	ギルドフラッグ#C4-08	722
//payg_cas04.gat,232,181,4	duplicate(GdFlag_C4)	ギルドフラッグ#C4-09	722
//payg_cas04.gat,239,181,4	duplicate(GdFlag_C4)	ギルドフラッグ#C4-10	722

//==========================================
// C5 : チュンリム
//------------------------------------------
-	script	GdFlag_C5	722,{
	callfunc "FlagSrc",1,"payg_cas05.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_C5:
	if(strnpcinfo(0) != "GdFlag_C5")
		flagemblem getcastledata("payg_cas05.gat",1);
	end;
}

pay_gld.gat,318,106,0	script	ギルドフラッグ#C5-00	722,{
	callfunc "FlagSrc",1,"payg_cas05.gat",276,227;
	close;
OnAgitInit:
OnFlagEmb_C5:
	flagemblem getcastledata("payg_cas05.gat",1);
	end;
}

pay_gld.gat,208,268,4		duplicate(GdFlag_C5)	ギルドフラッグ#C5-01	722
pay_gld.gat,199,268,4		duplicate(GdFlag_C5)	ギルドフラッグ#C5-02	722
pay_gld.gat,190,277,3		duplicate(GdFlag_C5)	ギルドフラッグ#C5-03	722
pay_gld.gat,187,294,2		duplicate(GdFlag_C5)	ギルドフラッグ#C5-04	722
//payg_cas05.gat,32,249,4		duplicate(GdFlag_C5)	ギルドフラッグ#C5-05	722
//payg_cas05.gat,24,249,4		duplicate(GdFlag_C5)	ギルドフラッグ#C5-06	722
//payg_cas05.gat,62,271,0		duplicate(GdFlag_C5)	ギルドフラッグ#C5-07	722
//payg_cas05.gat,57,271,0		duplicate(GdFlag_C5)	ギルドフラッグ#C5-08	722
//payg_cas05.gat,55,252,2		duplicate(GdFlag_C5)	ギルドフラッグ#C5-09	722
//payg_cas05.gat,55,260,2		duplicate(GdFlag_C5)	ギルドフラッグ#C5-10	722

//==========================================
// V1 : ヴァルキリーレルム
//------------------------------------------
-	script	GdFlag_V1	722,{
	callfunc "FlagSrc",1,"prtg_cas01.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_V1:
	if(strnpcinfo(0) != "GdFlag_V1")
		flagemblem getcastledata("prtg_cas01.gat",1);
	end;
}

prt_gld.gat,160,210,4	script	ギルドフラッグ#V1-00	722,{
	callfunc "FlagSrc",1,"prtg_cas01.gat",97,174;
	close;
OnAgitInit:
OnFlagEmb_V1:
	flagemblem getcastledata("prtg_cas01.gat",1);
	end;
}

prt_gld.gat,131,60,6		duplicate(GdFlag_V1)	ギルドフラッグ#V1-01	722
prt_gld.gat,138,68,6		duplicate(GdFlag_V1)	ギルドフラッグ#V1-02	722
prt_gld.gat,138,60,6		duplicate(GdFlag_V1)	ギルドフラッグ#V1-03	722
prt_gld.gat,135,60,6		duplicate(GdFlag_V1)	ギルドフラッグ#V1-04	722
//prtg_cas01.gat,58,56,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-05	722
//prtg_cas01.gat,64,56,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-06	722
//prtg_cas01.gat,76,32,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-07	722
//prtg_cas01.gat,84,32,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-08	722
//prtg_cas01.gat,94,39,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-09	722
//prtg_cas01.gat,94,24,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-10	722
//prtg_cas01.gat,73,14,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-11	722
//prtg_cas01.gat,73,6,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-12	722
//prtg_cas01.gat,55,46,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-13	722
//prtg_cas01.gat,45,46,4		duplicate(GdFlag_V1)	ギルドフラッグ#V1-14	722

//==========================================
// V2 : ヴァルキリーレルム
//------------------------------------------
-	script	GdFlag_V2	722,{
	callfunc "FlagSrc",1,"prtg_cas02.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_V2:
	if(strnpcinfo(0) != "GdFlag_V2")
		flagemblem getcastledata("prtg_cas02.gat",1);
	end;
}

prt_gld.gat,153,213,3	script	ギルドフラッグ#V2-00	722,{
	callfunc "FlagSrc",1,"prtg_cas02.gat",71,36;
	close;
OnAgitInit:
OnFlagEmb_V2:
	flagemblem getcastledata("prtg_cas02.gat",1);
	end;
}

prt_gld.gat,244,126,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-01	722
prt_gld.gat,244,128,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-02	722
prt_gld.gat,236,126,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-03	722
prt_gld.gat,236,128,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-04	722
//prtg_cas02.gat,40,227,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-05	722
//prtg_cas02.gat,46,227,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-06	722
//prtg_cas02.gat,11,219,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-07	722
//prtg_cas02.gat,11,214,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-08	722
//prtg_cas02.gat,20,219,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-09	722
//prtg_cas02.gat,20,214,4		duplicate(GdFlag_V2)	ギルドフラッグ#V2-10	722
//prtg_cas02.gat,79,227,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-11	722
//prtg_cas02.gat,70,227,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-12	722
//prtg_cas02.gat,38,189,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-13	722
//prtg_cas02.gat,34,189,8		duplicate(GdFlag_V2)	ギルドフラッグ#V2-14	722
//prtg_cas02.gat,153,161,4	duplicate(GdFlag_V2)	ギルドフラッグ#V2-15	722
//prtg_cas02.gat,162,161,4	duplicate(GdFlag_V2)	ギルドフラッグ#V2-16	722

//==========================================
// V3 : ヴァルキリーレルム
//------------------------------------------
-	script	GdFlag_V3	722,{
	callfunc "FlagSrc",1,"prtg_cas03.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_V3:
	if(strnpcinfo(0) != "GdFlag_V3")
		flagemblem getcastledata("prtg_cas03.gat",1);
	end;
}

prt_gld.gat,150,220,2	script	ギルドフラッグ#V3-00	722,{
	callfunc "FlagSrc",1,"prtg_cas03.gat",181,215;
	close;
OnAgitInit:
OnFlagEmb_V3:
	flagemblem getcastledata("prtg_cas03.gat",1);
	end;
}

prt_gld.gat,147,140,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-01	722
prt_gld.gat,147,136,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-02	722
prt_gld.gat,158,140,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-03	722
prt_gld.gat,158,136,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-04	722
//prtg_cas03.gat,168,28,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-05	722
//prtg_cas03.gat,182,28,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-06	722
//prtg_cas03.gat,43,50,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-07	722
//prtg_cas03.gat,48,50,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-08	722
//prtg_cas03.gat,43,58,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-09	722
//prtg_cas03.gat,48,58,4		duplicate(GdFlag_V3)	ギルドフラッグ#V3-10	722
//prtg_cas03.gat,158,210,4	duplicate(GdFlag_V3)	ギルドフラッグ#V3-11	722
//prtg_cas03.gat,169,210,4	duplicate(GdFlag_V3)	ギルドフラッグ#V3-12	722
//prtg_cas03.gat,162,201,4	duplicate(GdFlag_V3)	ギルドフラッグ#V3-13	722
//prtg_cas03.gat,165,201,4	duplicate(GdFlag_V3)	ギルドフラッグ#V3-14	722

//==========================================
// V4 : ヴァルキリーレルム
//------------------------------------------
-	script	GdFlag_V4	722,{
	callfunc "FlagSrc",1,"prtg_cas04.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_V4:
	if(strnpcinfo(0) != "GdFlag_V4")
		flagemblem getcastledata("prtg_cas04.gat",1);
	end;
}

prt_gld.gat,169,220,6	script	ギルドフラッグ#V4-00	722,{
	callfunc "FlagSrc",1,"prtg_cas04.gat",258,247;
	close;
OnAgitInit:
OnFlagEmb_V4:
	flagemblem getcastledata("prtg_cas04.gat",1);
	end;
}

prt_gld.gat,120,243,6		duplicate(GdFlag_V4)	ギルドフラッグ#V4-01	722
prt_gld.gat,120,236,6		duplicate(GdFlag_V4)	ギルドフラッグ#V4-02	722
prt_gld.gat,122,243,6		duplicate(GdFlag_V4)	ギルドフラッグ#V4-03	722
prt_gld.gat,122,236,6		duplicate(GdFlag_V4)	ギルドフラッグ#V4-04	722
//prtg_cas04.gat,82,29,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-05	722
//prtg_cas04.gat,75,29,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-06	722
//prtg_cas04.gat,75,27,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-07	722
//prtg_cas04.gat,82,27,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-08	722
//prtg_cas04.gat,59,29,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-09	722
//prtg_cas04.gat,67,29,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-10	722
//prtg_cas04.gat,258,25,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-11	722
//prtg_cas04.gat,258,20,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-12	722
//prtg_cas04.gat,263,20,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-13	722
//prtg_cas04.gat,263,27,4		duplicate(GdFlag_V4)	ギルドフラッグ#V4-14	722

//==========================================
// V5 : ヴァルキリーレルム
//------------------------------------------
-	script	GdFlag_V5	722,{
	callfunc "FlagSrc",1,"prtg_cas05.gat",0,0;
	close;
OnAgitInit:
OnFlagEmb_V5:
	if(strnpcinfo(0) != "GdFlag_V5")
		flagemblem getcastledata("prtg_cas05.gat",1);
	end;
}

prt_gld.gat,167,213,5	script	ギルドフラッグ#V5-00	722,{
	callfunc "FlagSrc",1,"prtg_cas05.gat",52,41;
	close;
OnAgitInit:
OnFlagEmb_V5:
	flagemblem getcastledata("prtg_cas05.gat",1);
	end;
}

prt_gld.gat,199,243,2		duplicate(GdFlag_V5)	ギルドフラッグ#V5-01	722
prt_gld.gat,199,236,2		duplicate(GdFlag_V5)	ギルドフラッグ#V5-02	722
prt_gld.gat,197,243,2		duplicate(GdFlag_V5)	ギルドフラッグ#V5-03	722
prt_gld.gat,197,236,2		duplicate(GdFlag_V5)	ギルドフラッグ#V5-04	722
//prtg_cas05.gat,19,247,4		duplicate(GdFlag_V5)	ギルドフラッグ#V5-05	722
//prtg_cas05.gat,19,243,4		duplicate(GdFlag_V5)	ギルドフラッグ#V5-06	722
//prtg_cas05.gat,26,247,4		duplicate(GdFlag_V5)	ギルドフラッグ#V5-07	722
//prtg_cas05.gat,26,243,4		duplicate(GdFlag_V5)	ギルドフラッグ#V5-08	722
//prtg_cas05.gat,249,289,4	duplicate(GdFlag_V5)	ギルドフラッグ#V5-09	722
//prtg_cas05.gat,256,289,4	duplicate(GdFlag_V5)	ギルドフラッグ#V5-10	722
//prtg_cas05.gat,253,271,4	duplicate(GdFlag_V5)	ギルドフラッグ#V5-11	722
//prtg_cas05.gat,273,257,4	duplicate(GdFlag_V5)	ギルドフラッグ#V5-12	722
