//script: 稀枝(kohri.net) rev. 1.3 //

prontera.gat,148,187,4	script	砦管理委員会員	105,{
	mes "[砦管理委員会員]";
	mes "私たちはルーンミッドガルドの砦を";
	mes "常に調査し、最新の情報をお伝えし";
	mes "ております。どの地域の砦についで";
	mes "お調べですか？";
	next;
	switch(select("アルデバラン","ゲフェン","フェイヨン","プロンテラ")) {
		case 1: setarray '@map$,"aldeg_cas01.gat","aldeg_cas02.gat","aldeg_cas03.gat","aldeg_cas04.gat","aldeg_cas05.gat"; break;
		case 2: setarray '@map$,"gefg_cas01.gat","gefg_cas02.gat","gefg_cas03.gat","gefg_cas04.gat","gefg_cas05.gat";      break;
		case 3: setarray '@map$,"payg_cas01.gat","payg_cas02.gat","payg_cas03.gat","payg_cas04.gat","payg_cas05.gat";      break;
		case 4: setarray '@map$,"prtg_cas01.gat","prtg_cas02.gat","prtg_cas03.gat","prtg_cas04.gat","prtg_cas05.gat";      break;
	}
	mes "[砦管理委員会員]";
	mes "現時点では、";
	for(set '@i,0; '@i < 4; set '@i,'@i+1) {
		set '@gid,getcastledata('@map$['@i],1);
		mes getcastlename('@map$['@i]);
		mes "^CE2AEA所有：^000000" + (('@gid == 0)? "なし": getguildname('@gid) +" ("+ getguildmaster('@gid) +")");
	}
	mes "となっております。";
	close;
}
