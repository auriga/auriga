prontera.gat,156,183,0	script	NPCtimerテスト::npctimerX0000	116,{
	mes "タイマー値" + getnpctimer(0);
	mes "タイマー状態" + getnpctimer(1,"npctimerX0000");
	mes "イベント個数" + getnpctimer(2);
	next;
	switch(select("初期化","停止","再開","設定")) {
	case 1:
		initnpctimer;
		close;
	case 2:
		stopnpctimer;
		close;
	case 3:
		startnpctimer;
		close;
	case 4:
		input @temp;
		setnpctimer @temp;
		close;
	}
	end;
OnTimer1000:
	announce "1秒経過",0;
	end;
OnTimer5000:
	announce "5秒経過",0;
	end;
OnTimer10000:
	announce "10秒経過",0;
	end;
}
