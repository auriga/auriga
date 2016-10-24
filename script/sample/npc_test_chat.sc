prontera.gat,158,182,0	script	chatテスト::test0001	116,{
	mes "トリガー人数" + getwaitingroomstate(2);
	mes "トリガー状態" + getwaitingroomstate(3);
	next;
	switch(select("有効化","無効化","削除","作成")) {
	case 1:
		enablewaitingroomevent;
		close;
	case 2:
		disablewaitingroomevent;
		close;
	case 3:
		delwaitingroom;
		close;
	case 4:
		waitingroom "テスト",15,"test0001::OnChatEvent",1;
		close;
	}
	end;
OnInit:
	waitingroom "テスト",15,"test0001::OnChatEvent",1;
	end;
OnChatEvent:
	disablewaitingroomevent;
	warpwaitingpc "prontera.gat",160,180;
	end;
}
