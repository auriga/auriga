//=========================================================================
// 宝箱発生NPC
//-------------------------------------------------------------------------

-	script	#TresureBox	-1,{
	function MakeTBox {
		setcastledata getarg(0),2,getcastledata(getarg(0),2)+getcastledata(getarg(0),4);
		setcastledata getarg(0),3,getcastledata(getarg(0),3)+getcastledata(getarg(0),5);
		setcastledata getarg(0),4,0;	//商業投資回数リセット
		setcastledata getarg(0),5,0;	//防衛投資回数リセット
		killmonster getarg(0),"#TresureBox::OnKilled";
		set '@num1,2+(getcastledata(getarg(0),2)+5)/10;
		set '@num2,2+getcastledata(getarg(0),2)/10;
		if('@num1 > 12)
			set '@num1,12;
		if('@num2 > 12)
			set '@num2,12;
		areamonster getarg(0),getarg(1),getarg(2),getarg(3),getarg(4),"宝箱",getarg(5),'@num1,"#TresureBox::OnKilled";
		areamonster getarg(0),getarg(1),getarg(2),getarg(3),getarg(4),"宝箱",getarg(6),'@num2,"#TresureBox::OnKilled";
		return;
	}
	end;

OnClock0000:
	MakeTBox "aldeg_cas01.gat",114,218,123,227,1324,1325;
	MakeTBox "aldeg_cas02.gat",130,226,139,235,1326,1327;
	MakeTBox "aldeg_cas03.gat",220,264,229,273,1328,1329;
	MakeTBox "aldeg_cas04.gat",80,8,89,17,1330,1331;
	MakeTBox "aldeg_cas05.gat",58,8,67,17,1332,1333;
	MakeTBox "gefg_cas01.gat",150,108,157,115,1334,1335;
	MakeTBox "gefg_cas02.gat",136,112,145,118,1336,1337;
	MakeTBox "gefg_cas03.gat",266,286,273,293,1338,1339;
	MakeTBox "gefg_cas04.gat",112,114,119,123,1340,1341;
	MakeTBox "gefg_cas05.gat",140,106,147,113,1342,1343;
	MakeTBox "payg_cas01.gat",286,4,295,7,1344,1345;
	MakeTBox "payg_cas02.gat",140,140,149,143,1346,1347;
	MakeTBox "payg_cas03.gat",154,164,162,172,1348,1349;
	MakeTBox "payg_cas04.gat",142,44,151,51,1350,1351;
	MakeTBox "payg_cas05.gat",152,128,161,131,1352,1353;
	MakeTBox "prtg_cas01.gat",7,205,15,212,1354,1355;
	MakeTBox "prtg_cas02.gat",198,224,205,231,1356,1357;
	MakeTBox "prtg_cas03.gat",184,128,192,135,1358,1359;
	MakeTBox "prtg_cas04.gat",266,158,273,165,1360,1361;
	MakeTBox "prtg_cas05.gat",272,174,279,181,1362,1363;
	end;
OnKilled:
	end;	//ダミーイベント
}


//-----GM専用デバッグモード-----
/*
===========================================================
prontera.gat,156,195,0	script	TBOX-Control	111,{
	if(getgmlevel()==0)
		end;
	mes "[TBOX-Control^ff0000(GM専用)^000000]";
	mes "宝箱を発生させますか？";
	next;
	if(select("はい","いいえ")==2)
		close;
	donpcevent "#TresureBox::OnClock0000";
	mes "[TBOX-Control^ff0000(GM専用)^000000]";
	mes "宝箱を発生させました。";
	close;
}
===========================================================
*/
