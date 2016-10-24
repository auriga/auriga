//=========================================================================
// アジト放棄・ギルド解体共通ファンクション
//	callfunc "AgitGiveUp","AgitCode";
//
// ■ キャスト
//	"::OnFlagEmb_XY" はnpc_gvg_flag.txtを参照
//
// ■ function
//	攻城戦中ならfunction "AgitSummon" を呼び出す（npc_gvg_monster）
//-------------------------------------------------------------------------

function	script	AgitGiveUp	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	killmonsterall '@map$;
	disablenpc "AgitKafra_"+getarg(0);
	for(set '@i,1; '@i<=17; set '@i,'@i+1) {
		setcastledata '@map$,'@i,('@i==2 || '@i==3)? 1: 0;
	}
	donpcevent "::OnFlagEmb_"+getarg(0);		//フラッグエンブレムの変更
	maprespawnguildid '@map$,0,7;
	if(agitcheck())
		callfunc "AgitSummon",getarg(0);	//Mobおよびエンペ召喚
	return;
}


//=========================================================================
// 攻城戦実行部
//	全ての処理はここで行う！
//
// 　※ strnpcinfo(2) によりアジトコードを取得する
//      duplicateするので毎回NPCの居るMAP名を関数依存変数に取得する
//-------------------------------------------------------------------------

-	script	AgitExe	-1,{
OnAgitInit:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if('@map$ == "-")					//duplicate元は何もしない
		end;
	if(getcastledata('@map$,9) == 0)
		disablenpc "AgitKafra_"+strnpcinfo(2);
	for(set '@i,10; '@i<=17; set '@i,'@i+1) {	//設置済みフラグがあればガーディアン召喚
		if(getcastledata('@map$,'@i))
			callfunc "GuardianCall",strnpcinfo(2),'@i,0;
	}
	end;
OnAgitStart:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "-")
		end;
	maprespawnguildid '@map$,getcastledata('@map$,1),2;
	callfunc "AgitSummon",strnpcinfo(2);	//エンペ召喚(npc_gvg_monster.txt)
	gvgon '@map$;
	end;
OnAgitBreak:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "-")
		end;
	killmonsterall '@map$;
	set '@gid,getcharid(2);		//エンペ破壊者のRIDを取得できる
	if('@gid <= 0)
		end;
	setcastledata '@map$,1,'@gid;
	for(set '@i,2; '@i<=17; set '@i,'@i+1) {
		if('@i==2 || '@i==3) {
			set '@val,getcastledata('@map$,'@i)-5;
			setcastledata '@map$,'@i,('@val<1)? 1: '@val;
		}
		else
			setcastledata '@map$,'@i,0;
	}
	announce "エンペリウムが破壊されました",9,0x00ff00;
	sleep 800;
	announce "砦 [" +getcastlename('@map$)+ "]を [" +getguildname('@gid)+ "] ギルドが占領しました",0x20;
	donpcevent "::OnFlagEmb_"+strnpcinfo(2);	//フラッグエンブレムの変更(npc_gvg_flag.txt)
	end;
OnAgitEliminate:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "-")
		end;
	maprespawnguildid '@map$,getcastledata('@map$,1),6;
	callfunc "AgitSummon",strnpcinfo(2);	//エンペのみ再召喚(npc_gvg_monster.txt)
	end;
OnGuildBreak:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "-")
		end;
	callfunc "AgitGiveUp",strnpcinfo(2);
	end;
OnAgitEnd:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	if('@map$ == "-")
		end;
	maprespawnguildid '@map$,getcastledata('@map$,1),4;
	killmonster '@map$,strnpcinfo(0)+"::OnAgitBreak";	//エンペのみ抹殺
	gvgoff '@map$;
	end;
}

//ルイーナ
aldeg_cas01.gat,0,0,0	duplicate(AgitExe)	AgitExe#L1	-1
aldeg_cas02.gat,0,0,0	duplicate(AgitExe)	AgitExe#L2	-1
aldeg_cas03.gat,0,0,0	duplicate(AgitExe)	AgitExe#L3	-1
aldeg_cas04.gat,0,0,0	duplicate(AgitExe)	AgitExe#L4	-1
aldeg_cas05.gat,0,0,0	duplicate(AgitExe)	AgitExe#L5	-1
//ブリトニア
gefg_cas01.gat,0,0,0	duplicate(AgitExe)	AgitExe#B1	-1
gefg_cas02.gat,0,0,0	duplicate(AgitExe)	AgitExe#B2	-1
gefg_cas03.gat,0,0,0	duplicate(AgitExe)	AgitExe#B3	-1
gefg_cas04.gat,0,0,0	duplicate(AgitExe)	AgitExe#B4	-1
gefg_cas05.gat,0,0,0	duplicate(AgitExe)	AgitExe#B5	-1
//チュンリム
payg_cas01.gat,0,0,0	duplicate(AgitExe)	AgitExe#C1	-1
payg_cas02.gat,0,0,0	duplicate(AgitExe)	AgitExe#C2	-1
payg_cas03.gat,0,0,0	duplicate(AgitExe)	AgitExe#C3	-1
payg_cas04.gat,0,0,0	duplicate(AgitExe)	AgitExe#C4	-1
payg_cas05.gat,0,0,0	duplicate(AgitExe)	AgitExe#C5	-1
//ヴァルキリーレルム
prtg_cas01.gat,0,0,0	duplicate(AgitExe)	AgitExe#V1	-1
prtg_cas02.gat,0,0,0	duplicate(AgitExe)	AgitExe#V2	-1
prtg_cas03.gat,0,0,0	duplicate(AgitExe)	AgitExe#V3	-1
prtg_cas04.gat,0,0,0	duplicate(AgitExe)	AgitExe#V4	-1
prtg_cas05.gat,0,0,0	duplicate(AgitExe)	AgitExe#V5	-1
