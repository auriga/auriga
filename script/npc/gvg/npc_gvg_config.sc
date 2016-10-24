//=========================================================================
// 攻城戦の開始・終了タイマー
//	const.txtより設定時間を取得
//	（GvGWeekDay, GvGTimeST, GvGTimeST, GvGTime*ST, GvGTime*ED）
//
//　■MAPサーバを起動してから60秒後に開始するかどうかを判断
//-------------------------------------------------------------------------

-	script	#AgitConfig	-1,{
	end;
OnInit:
	if(GvGWeekDay == 0)
		end;
	//開催曜日のビットフラグがあれば1をセット
	for(set '@i,0; '@i<7; set '@i,'@i+1) {
		set 'open['@i],(GvGWeekDay &(1<<'@i))? 1: 0;
	}
	//曜日で時間を変える場合
	if(GvGTimeST == GvGTimeED) {
		setarray 'dbt,GvGTime0ST,GvGTime1ST,GvGTime2ST,GvGTime3ST,GvGTime4ST,GvGTime5ST,GvGTime6ST;
		setarray 'fin,GvGTime0ED,GvGTime1ED,GvGTime2ED,GvGTime3ED,GvGTime4ED,GvGTime5ED,GvGTime6ED;
	}
	//毎日同じ時間の場合
	else {
		cleararray 'dbt,GvGTimeST,7;
		cleararray 'fin,GvGTimeED,7;
	}
	sleep 60000;
	set '@day,gettime(4);
	set '@min,gettime(3)*100+gettime(2);
	//今日が開催日で且つ既に開催時間中なら
	if('open['@day] && '@min>='dbt['@day] && '@min<'fin['@day]) {
		debugmes "攻城戦再開 [ " +gettimestr("%H:%M",6)+ " ]";
		agitstart;
	}
	sleep (60-gettime(1))*1000;	//秒が繰り上がるまで待機

OnTimer60000:
	initnpctimer;
	set '@day,gettime(4);
	set '@min,gettime(3)*100+gettime(2);

	//24時終了の例外処理
	if('@min == 0) {
		set '@prev,('@day>0)? '@day-1: 6;
		if('open['@prev] && 'fin['@prev]==2400) {
			if('open['@day]==0 || 'dbt['@day]>0) {
				debugmes "攻城戦終了 [ " +gettimestr("%H:%M",6)+ " ]";
				agitend;
			}
			end;
		}
	}
	if('open['@day]==0)
		end;
	if('@min == 'dbt['@day]) {
		debugmes "攻城戦開始 [ " +gettimestr("%H:%M",6)+ " ]";
		agitstart;
	}
	else if('@min == 'fin['@day]) {
		debugmes "攻城戦終了 [ " +gettimestr("%H:%M",6)+ " ]";
		agitend;
	}
	end;
}


//-----GM専用デバッグモード-----
//===========================================================
//prontera.gat,152,208,0	script	GvG-Control	111,{
//	if(getgmlevel(0)==0)
//		end;
//	mes "[GvG-Control^ff0000(GM専用)^000000]";
//	mes "攻城戦モード設定";
//	next;
//	switch (select("開始","停止","デバッグ","キャンセル")) {
//	case 1:
//		announce "攻城戦開始",0;
//		agitstart;
//		break;
//	case 2:
//		announce "攻城戦終了",0;
//		agitend;
//		break;
//	case 3:
//		setarray '@chr$,"日","月","火","水","木","金","土";
//		for(set '@i,0; '@i<7; set '@i,'@i+1)
//			mes '@chr$['@i]+ "曜日 ： " +(getelementofarray( getvariableofnpc('open,"#AgitConfig"),'@i ))? "○": "×";
//		next;
//		if(GvGTimeST != GvGTimeED) {
//			mes "毎回　" +GvGTimeST+ " ～ " +GvGTimeED;
//			break;
//		}
//		for(set '@i,0; '@i<7; set '@i,'@i+1) {
//			mes '@chr$['@i]+ "曜日 ： " +getelementofarray( getvariableofnpc('dbt,"#AgitConfig"),'@i )+
//						" ～ " +getelementofarray( getvariableofnpc('fin,"#AgitConfig"),'@i );
//		}
//		break;
//	}
//	close;
//}
//===========================================================
