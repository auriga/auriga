//= Auriga Script ==============================================================
// Ragnarok Online Storage NPC Script	by Blaze
//==============================================================================

//============================================================
// Function
//------------------------------------------------------------
// Func_StorageManager
//   arg(0)：Zeny
//   arg(1)：メッセージタイプ（0:カプラサービス、1:猫）
function	script	Func_StorageManager	{
	mes "[倉庫管理人]";
	switch(getarg(1)) {
	default:
		mes "こんにちは～";
		mes "こちらでは、㈱カプラサービスより";
		mes "正式な業務委託を受けて";
		mes "簡易的な倉庫サービスを";
		mes "提供しております！";
		break;
	case 1:
		mes "にゃにゃ！";
		mes "こちらでは、";
		mes "簡易的な倉庫サービスを";
		mes "提供しているにゃ！";
		break;
	}
	next;
	mes "[倉庫管理人]";
	mes "^0000FFメイン倉庫^000000と";
	mes "^FF0000サブ倉庫^000000を";
	mes "一発簡単 ^FF0000" +getarg(0)+ " Zeny^000000でオープン可能！";
	mes "是非ご利用くださいね～♪";
	return;
}

// Func_Storage
//   arg(0)：Zeny
//   arg(1)：倉庫番号（未実装）
function	script	Func_Storage	{
	if(basicskillcheck() && getskilllv(1) < 6 && getskilllv(5018) < 1) {
		mes "[倉庫管理人]";
		mes "倉庫機能は基本スキルの保管倉庫使用を";
		mes "習得してから利用可能となります。";
		close2;
		return;
	}
	else if(Zeny < getarg(0)) {
		mes "[倉庫管理人]";
		mes "この倉庫を利用するには";
		mes "^FF0000 " +getarg(0)+ " Zeny^000000が必要です。";
		close2;
		return;
	}
	set Zeny,Zeny - getarg(0);
	openstorage;
	return;
}

//============================================================
// モロク
//------------------------------------------------------------
morocc.gat,182,56,4	script	倉庫管理人#moc	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
morocc.gat,179,55,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
morocc.gat,181,55,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
morocc.gat,183,55,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
morocc.gat,185,55,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// フェイヨン
//------------------------------------------------------------
payon.gat,180,67,4	script	倉庫管理人#pay	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
payon.gat,177,66,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
payon.gat,179,66,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
payon.gat,179,66,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
payon.gat,179,66,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// アルベルタ
//------------------------------------------------------------
alberta.gat,147,62,4	script	倉庫管理人#alb	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
alberta.gat,144,61,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
alberta.gat,146,61,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
alberta.gat,148,61,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
alberta.gat,150,61,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// アルデバラン
//------------------------------------------------------------
aldebaran.gat,172,126,4	script	倉庫管理人#alde	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
aldebaran.gat,169,125,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
aldebaran.gat,171,125,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
aldebaran.gat,173,125,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
aldebaran.gat,175,125,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// コモド
//------------------------------------------------------------
comodo.gat,165,177,4	script	倉庫管理人#cmd	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
comodo.gat,162,176,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
comodo.gat,164,176,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
comodo.gat,166,176,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
comodo.gat,168,176,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// リヒタルゼン
//------------------------------------------------------------
lighthalzen.gat,169,124,4	script	倉庫管理人#lhz	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
lighthalzen.gat,166,123,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
lighthalzen.gat,168,123,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
lighthalzen.gat,170,123,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
lighthalzen.gat,172,123,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// ミッドガルド連合軍駐屯地
//------------------------------------------------------------
mid_camp.gat,46,163,4	script	倉庫管理人#mid	553,{
	callfunc "Func_StorageManager",50,1;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
mid_camp.gat,43,161,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
mid_camp.gat,45,161,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
mid_camp.gat,47,161,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
mid_camp.gat,49,161,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// ブラジリス
//------------------------------------------------------------
brasilis.gat,177,225,4	script	倉庫管理人#bra	80,{
	callfunc "Func_StorageManager",50,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫 【50Zeny】",0;
	end;
}
brasilis.gat,174,224,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
brasilis.gat,176,224,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
brasilis.gat,178,224,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
brasilis.gat,180,224,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// 次元の狭間
//------------------------------------------------------------
dali02.gat,102,94,5	script	倉庫管理人#dali	80,{
	callfunc "Func_StorageManager",40,0;
	close;
OnInit:
// signboard表示する場合はコメントアウト
	waitingroom "倉庫",0;
	end;
}
dali02.gat,106,93,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",40,0;
	end;
}
dali02.gat,109,94,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",40,1;
	end;
}
dali02.gat,112,95,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",40,2;
	end;
}
dali02.gat,115,96,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",40,3;
	end;
}
