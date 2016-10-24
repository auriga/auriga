//========================================================================================
//=================枝プロンテラNPC改造版(個数制限あり)====================================
//========================================================================================
prontera.gat,166,125,4	script	モンスター召還屋	738,{
	if(Zeny < 50000) {
		mes "[モンスター召還屋]";
		mes "お金が足りません。";
		close;
	}
	if($@prtmob >= 5) {
		mes "[モンスター召還屋]";
		mes "一度に出せるのは5匹までです。";
		close;
	}
	set Zeny,Zeny-50000;
	switch(rand(4)) {
		case 0: monster "this",162,126,"--ja--",-1,1,"prtmobdie"; break;
		case 1: monster "this",162,112,"--ja--",-1,1,"prtmobdie"; break;
		case 2: monster "this",149,126,"--ja--",-1,1,"prtmobdie"; break;
		case 3: monster "this",149,112,"--ja--",-1,1,"prtmobdie"; break;
	}
	set $@prtmob,$@prtmob+1;
OnCount:
OnInit:
	waitingroom "[" + $@prtmob + "/5匹]1回 50,000z",0;
	end;
}

//=====================カウント部===============================
prontera.gat,0,0,0	script	prtmobdie	-1,{
	set $@prtmob,$@prtmob-1;
	donpcevent "モンスター召還屋::OnCount";
	end;
}

//=====================リセット(デビルチより召喚されたMobのみリセット)=================================
prontera.gat,168,125,4	script	モンスターリセット屋	81,{
	mes "[モンスターリセット屋]";
	mes "モンスターをリセットします。";
	next;
	if(select("はい","いいえ") == 1) {
		killmonster "prontera.gat","prtmobdie";
		mes "[モンスターリセット屋]";
		mes "Mobdelete完了";
		next;
		set $@prtmob,0;
		mapannounce "prontera.gat","[南十字路情報] " + strcharinfo(0) + "によりMobリセットされました。",20;
		mes "[モンスターリセット屋]";
		mes "FlagReset完了";
	}
	donpcevent "モンスター召還屋::OnCount";
	close;
}
