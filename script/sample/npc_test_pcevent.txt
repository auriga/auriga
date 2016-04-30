//=====================================================================
// ■ OnPCイベントラベル テストスクリプト
//						created by Rayce
//　注：battle_auriga.confで該当の項目を有効化して
//　　　利用してください。
//---------------------------------------------------------------------

//---------------------------------------------------------------------
//城2Fでのみ死亡したらアイテムを全部消される

gl_cas02.gat,0,0,0	script	DieControl	-1,{
OnPCDie:
	clearitem;
	end;
}


//---------------------------------------------------------------------
//MAP内で倒した人数を返す

pvp_y_1-1.gat,155,192,4	script	記録者	711,{
	mes "[記録者]";
	mes "あなたが倒した人数は";
	mes "^3355FF" +@pvcount+ " ^000000人です。";
	close;
OnPCKill:
	set '@aid,getcharid(3,getcharname(PC_KILLED_CHAR));
	if(attachrid('@aid)) {
		set @pvcount,@pvcount+1;	//殺した相手のカウンタを加算する
		detachrid;
	}
	end;
}


//---------------------------------------------------------------------
//プレイヤーのMAPに関わらずログイン・ログアウト時にアナウンスが流れる
//ただしこのNPCを設置したMAPサーバ内に限る

-	script	Login/Logout	-1,{
	function Area {
		set '@name$,substr(getarg(0),0,3);
		if('@name$ == "prt" || '@name$ == "pro")
			return "プロンテラ";
		if('@name$ == "gef")
			return "ゲフェン";
		if('@name$ == "moc" || '@name$ == "mor")
			return "モロク";
		if('@name$ == "pay")
			return "フェイヨン";
		else
			return "その他の";
	}
OnPCLogin:
	announce strcharinfo(0)+ "さんが" +Area(getmapname(strcharinfo(0)))+ "エリアにログインしました",8,0xDDA0DD;
	end;
OnPCLogout:
	announce strcharinfo(0)+ "さんが" +Area(getmapname(strcharinfo(0)))+ "エリアでログアウトしました",8,0xDDA0DD;
	end;
}


//---------------------------------------------------------------------
//プロンテラ、イズルード、アルベルタを訪れたのべ人数を返す
//ただし3つのNPCが同一のMAPサーバに存在するときのみ動作が保証される

prontera.gat,146,92,6	script	観光地案内#pro	114,{
	set '@total,'count + getvariableofnpc('count,"観光地案内#izl") + getvariableofnpc('count,"観光地案内#alb");
	mes "[観光地案内]";
	mes "ここプロンテラを訪れた人は";
	mes "のべ ^3355FF" +'count+ " ^000000人です。";
	mes "イズルードとアルベルタを合わせると";
	mes "総計^3355FF " +'@total+ " ^000000人となります。";
	close;
OnPCMoveMap:
	set 'count,'count+1;
	end;
}

izlude.gat,134,91,4	script	観光地案内#izl	114,{
	set '@total,'count + getvariableofnpc('count,"観光地案内#pro") + getvariableofnpc('count,"観光地案内#alb");
	mes "[観光地案内]";
	mes "ここイズルードを訪れた人は";
	mes "のべ ^3355FF" +'count+ " ^000000人です。";
	mes "プロンテラとアルベルタを合わせると";
	mes "総計^3355FF " +'@total+ " ^000000人となります。";
	close;
OnPCMoveMap:
	set 'count,'count+1;
	end;
}

alberta.gat,113,57,6	script	観光地案内#alb	114,{
	set '@total,'count + getvariableofnpc('count,"観光地案内#pro") + getvariableofnpc('count,"観光地案内#izl");
	mes "[観光地案内]";
	mes "ここアルベルタを訪れた人は";
	mes "のべ ^3355FF" +'count+ " ^000000人です。";
	mes "プロンテラとイズルードを合わせると";
	mes "総計^3355FF " +'@total+ " ^000000人となります。";
	close;
OnPCMoveMap:
	set 'count,'count+1;
	end;
}
