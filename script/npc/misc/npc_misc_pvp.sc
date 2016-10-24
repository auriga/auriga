//==============================================================================
//Ragnarok Online EP1.5  Player vs Player(PVP) Script
//==============================================================================

//====================================================================
// PVPガイド全部
//	セーブポイントが違うだけなのでduplicate
//--------------------------------------------------------------------

-	script	PvPguide	-1,{
	mes "[PVPガイド]";
	mes "こんにちは！！";
	mes "PVPモードの";
	mes "説明を担当している";
	mes "PVP ガイドです！";
	next;
	switch (select("^3355ff「PVPモード」^000000って何？","PVPモードの参加方法は？","PVPモードのルールは？","現在位置でセーブする","会話をやめる")) {
	case 1:
		mes "[PVPガイド]";
		mes "PVPモードは";
		mes "「Player VS Player Mode」";
		mes "の略で、";
		mes "仮想の世界でプレイヤー同士の";
		mes "対戦をするシステムです。";
		next;
		mes "[PVPガイド]";
		mes "ピリピリする緊張感の中で";
		mes "真剣勝負を味わえる";
		mes "一種のアリーナモードですね。";
		mes "私の隣の";
		mes "^3355FFドアマン^000000 に話かけると";
		next;
		mes "[PVPガイド]";
		mes "PVPモードの";
		mes "控え室に入ることができます。";
		mes "PVPモードはLv31以上の";
		mes "キャラクターしか参加できません。";
		next;
		mes "[PVPガイド]";
		mes "そして、PVPモードは";
		mes "大きく２つに分けて";
		mes "「ナイトメアモード」と";
		mes "「ヨーヨーモード」が";
		mes "あります。";
		next;
		mes "[PVPガイド]";
		mes "ナイトメアモードでは";
		mes "ダンジョンと同じルールが";
		mes "そのまま適用されており、";
		mes "倒された場合は経験値を";
		mes "失います。";
		next;
		mes "[PVPガイド]";
		mes "この点に気をつけて";
		mes "ご入場ください。";
		close;
	case 2:
		mes "[PVPガイド]";
		mes "私の隣にいる「PVPドアマン」";
		mes "に話かけましたら";
		mes "500 Zenyで";
		mes "PVPモードの控え室に";
		mes "移動されます。";
		next;
		mes "[PVPガイド]";
		mes "控え室はヨーヨーモード、";
		mes "ナイトメアモードそれぞれに";
		mes "用意されており、";
		mes "各部屋にはPVPモードの";
		mes "エリアにご案内する";
		mes "案内人が立っております。";
		next;
		mes "[PVPガイド]";
		mes "簡単に説明しますと、";
		mes "Lv31以上から10Lvずつ";
		mes "段階をおって担当者が";
		mes "おります。";
		next;
		mes "[PVPガイド]";
		mes "各レベルの担当者の上に";
		mes "参加可能Lvが記載されて";
		mes "おりますので、そちらを参照";
		mes "してください。";
		next;
		mes "[PVPガイド]";
		mes "また、担当者に話しかけますと";
		mes "各MAPでの参加人数が";
		mes "確認できます。";
		next;
		mes "[PVPガイド]";
		mes "「参加人数 / 参加可能最大数」";
		mes "となっております。";
		next;
		mes "[PVPガイド]";
		mes "ここで一点注意。";
		mes "PVP専用MAPは勿論、";
		mes "控え室でも位置セーブは";
		mes "不可能となっておりますので";
		mes "ご注意ください。以上です。";
		close;
	case 3:
		mes "[PVPガイド]";
		mes "PVPモードに進入すると";
		mes "画面右下にカウンターが";
		mes "出てきますが、これは";
		mes "現在ログインMAPでの";
		mes "自分の順位 / MAP内人数 を";
		next;
		mes "[PVPガイド]";
		mes "表す数値です。";
		mes "PVPモードでのポイントは";
		mes "PVPモードにのみ";
		mes "適用されており、";
		mes "初めに持っている";
		next;
		mes "[PVPガイド]";
		mes "基本値は 5 です。";
		mes "マップの中で対戦し";
		mes "勝利した場合得られるポイントは";
		mes "1 で、負けた場合";
		mes "-5 ポイントとなります。";
		next;
		mes "[PVPガイド]";
		mes "所持ポイントが";
		mes "0 以下になった場合";
		next;
		mes "[PVPガイド]";
		mes "PVPモードが解除され";
		mes "外に出されます。";
		mes "しかし数値が 0 以上の時";
		mes "戦闘不能になった場合は";
		mes "仲間や他のプレイヤーに";
		next;
		mes "[PVPガイド]";
		mes "助けて貰い続行することが";
		mes "できます。";
		next;
		mes "[PVPガイド]";
		mes "プレイヤーとの対戦ルールは";
		mes "モンスターとの戦闘ルールと";
		mes "基本的には同じです。";
		close;
	case 4:
		set '@num,strnpcinfo(2);	//NPC名の#以降の文字列を参照して数値に変換
		switch('@num) {
			case 0: savepoint "alberta_in.gat",61,143; 	break;
			case 1: savepoint "geffen_in.gat",69,59; 	break;
			case 2: savepoint "morocc_in.gat",142,140; 	break;
			case 3: savepoint "payon_in01.gat",166,107; 	break;
			case 4: savepoint "prt_in.gat",54,136; 		break;
		}
		mes "[PVPガイド]";
		mes "こちらでセーブできました。";
		mes "ご利用ありがとうございます。";
		close;
	case 5:
		mes "[PVPガイド]";
		mes "プレイヤー同士の真剣勝負を";
		mes "味わえるPVPモード！";
		mes "勇気溢れる皆様を";
		mes "お待ちしております。";
		close;
	}
}

alberta_in.gat,62,145,4	duplicate(PvPguide)	PVPガイド#0	84
geffen_in.gat,67,63,4	duplicate(PvPguide)	PVPガイド#1	84
morocc_in.gat,144,138,4	duplicate(PvPguide)	PVPガイド#2	84
payon_in01.gat,142,50,4	duplicate(PvPguide)	PVPガイド#3	84
prt_in.gat,56,140,4	duplicate(PvPguide)	PVPガイド#4	84


//====================================================================
// PVPドアマン全部
//	duplicateで使う
//--------------------------------------------------------------------

-	script	PvPdoor	-1,{
	mes "[PVPドアマン]";
	mes "PVP控え室にご案内する";
	mes "PVPドアマンです。";
	mes "PVPモードについての説明は";
	mes "隣のガイドに";
	mes "お問い合わせください。";
	next;
	set '@ret,select("^ff3355PVP ナイトメアモード^000000 控え室へ","^3355FFPVP ヨーヨーモード^000000 控え室へ","会話をやめる");
	switch('@ret) {
	case 1:
		mes "[PVPドアマン]";
		mes "ナイトメアモードでは";
		mes "ダンジョンと同じルールが";
		mes "そのまま適用されており、";
		mes "倒された場合は経験値を";
		mes "失います。";
		next;
		//fall through
	case 2:
		mes "[PVPドアマン]";
		mes "参加費は 500Zeny です。";
		if('@ret==1)
			mes "ナイトメアモード控え室へ";
		else
			mes "ヨーヨーモード控え室へ";
		mes "移動されますか？";
		next;
		if(select("移動","取り消し")==2)
			break;
		if(Zeny<500 || BaseLevel<31) {
			mes "[PVP ドアマン]";
			mes "お客様 !";
			mes "Zenyが足りないか、基本レベルが";
			mes "31になっていないようです。";
			close;
		}
		set Zeny,Zeny-500;
		if('@ret==1)
			warp "pvp_n_room.gat",51,23;
		else
			warp "pvp_y_room.gat",51,23;
		end;
	}
	//case3のときはfall through
	mes "[PVPドアマン]";
	mes "プレイヤー同士の真剣勝負を";
	mes "味わえるPVPモード！";
	mes "勇気溢れる皆様を";
	mes "お待ちしております。";
	close;
}

alberta_in.gat,58,145,4	duplicate(PvPdoor)	PVPドアマン	83
geffen_in.gat,63,63,4	duplicate(PvPdoor)	PVPドアマン	83
morocc_in.gat,144,142,4	duplicate(PvPdoor)	PVPドアマン	83
payon_in01.gat,140,53,4	duplicate(PvPdoor)	PVPドアマン	83
prt_in.gat,52,140,4	duplicate(PvPdoor)	PVPドアマン	83


//====================================================================
// PvP受付（ヨーヨー）
//	callfunc "PvPreceptY",LvNum,LowLv,HighLv;
//--------------------------------------------------------------------

function	script	PvPreceptY	{
	if( getarg(0)!=8 && (BaseLevel < getarg(1) || BaseLevel > getarg(2)) ) {
		mes "[PVP 試合場 受付]";
		mes "申し訳ありません。";
		mes "この試合場は";
		if(getarg(0)<7) {
			mes "Lv" +getarg(1)+ "からLv" +getarg(2)+ "までの方しか";
			mes "入場できません。";
		}
		else
			mes "Lv91以上の方しか入場できません。";
		return;
	}
	set @menu,select(	"プロンテラ　[" +getmapusers("pvp_y_"+getarg(0)+"-1.gat")+ " / 128]",
				"イズルード　[" +getmapusers("pvp_y_"+getarg(0)+"-2.gat")+ " / 128]",
				"フェイヨン　[" +getmapusers("pvp_y_"+getarg(0)+"-3.gat")+ " / 128]",
				"アルベルタ　[" +getmapusers("pvp_y_"+getarg(0)+"-4.gat")+ " / 128]",
				"モロク　[" 	+getmapusers("pvp_y_"+getarg(0)+"-5.gat")+ " / 128]","取り消し");
	if(@menu==6)
		return;
	if(getmapusers("pvp_y_"+getarg(0)+"-"+@menu+".gat") >= 128) {
		mes "[PVP 試合場 受付]";
		mes "満員です。";
		return;
	}
	warp "pvp_y_"+getarg(0)+"-"+@menu+".gat",0,0;
	end;
}

pvp_y_room.gat,30,85,4	script	試合場 受付#y-1pvp	105,{
	callfunc "PvPreceptY",1,31,40;
	close;
OnInit:
	waitingroom "LV 31 ~ LV 40",0;
	end;
}

pvp_y_room.gat,38,85,4	script	試合場 受付#y-2pvp	105,{
	callfunc "PvPreceptY",2,41,50;
	close;
OnInit:
	waitingroom "LV 41 ~ LV 50",0;
	end;
}

pvp_y_room.gat,46,85,4	script	試合場 受付#y-3pvp	105,{
	callfunc "PvPreceptY",3,51,60;
	close;
OnInit:
	waitingroom "LV 51 ~ LV 60",0;
	end;
}

pvp_y_room.gat,54,85,4	script	試合場 受付#y-4pvp	105,{
	callfunc "PvPreceptY",4,61,70;
	close;
OnInit:
	waitingroom "LV 61 ~ LV 70",0;
	end;
}

pvp_y_room.gat,62,85,4	script	試合場 受付#y-5pvp	105,{
	callfunc "PvPreceptY",5,71,80;
	close;
OnInit:
	waitingroom "LV 71 ~ LV 80",0;
	end;
}

pvp_y_room.gat,70,85,4	script	試合場 受付#y-6pvp	105,{
	callfunc "PvPreceptY",6,81,90;
	close;
OnInit:
	waitingroom "LV 81 ~ LV 90",0;
	end;
}

pvp_y_room.gat,78,85,4	script	試合場 受付#y-7pvp	105,{
	callfunc "PvPreceptY",7,91,255;
	close;
OnInit:
	waitingroom "LV 91 ~",0;
	end;
}

pvp_y_room.gat,86,85,4	script	試合場 受付#y-8pvp	105,{
	callfunc "PvPreceptY",8,0,0;
	close;
OnInit:
	waitingroom "無制限",0;
	end;
}


//====================================================================
// PvP受付（ナイトメア）
//	callfunc "PvPreceptN",LvNum,LowLv,HighLv;
//--------------------------------------------------------------------

function	script	PvPreceptN	{
	if( getarg(0)!=8 && (BaseLevel < getarg(1) || BaseLevel > getarg(2)) ) {
		mes "[PVP 試合場 受付]";
		mes "申し訳ありません。";
		mes "この試合場は";
		if(getarg(0)<7) {
			mes "Lv" +getarg(1)+ "からLv" +getarg(2)+ "までの方しか";
			mes "入場できません。";
		}
		else
			mes "Lv91以上の方しか入場できません。";
		return;
	}
	set @menu,select(	"南北戦争　[" 		+getmapusers("pvp_n_"+getarg(0)+"-1.gat")+ " / 64]",
				"ロックオン　["  	+getmapusers("pvp_n_"+getarg(0)+"-2.gat")+ " / 32]",
				"フォールーム　[" 	+getmapusers("pvp_n_"+getarg(0)+"-3.gat")+ " / 32]",
				"アンダークロス　[" 	+getmapusers("pvp_n_"+getarg(0)+"-4.gat")+ " / 32]",
				"ザナクルーム　[" 	+getmapusers("pvp_n_"+getarg(0)+"-5.gat")+ " / 32]","取り消し");
	if(@menu==6)
		return;
	if((@menu==1 && getmapusers("pvp_n_"+getarg(0)+"-1.gat") >= 64) ||
			(@menu>1 && getmapusers("pvp_n_"+getarg(0)+"-"+@menu+".gat") >= 32)) {
		mes "[PVP 試合場 受付]";
		mes "満員です。";
		return;
	}
	warp "pvp_n_"+getarg(0)+"-"+@menu+".gat",0,0;
	end;
}

pvp_n_room.gat,30,85,4	script	試合場 受付#n-1pvp	105,{
	callfunc "PvPreceptN",1,31,40;
	close;
OnInit:
	waitingroom "LV 31 ~ LV 40",0;
	end;
}

pvp_n_room.gat,38,85,4	script	試合場 受付#n-2pvp	105,{
	callfunc "PvPreceptN",2,41,50;
	close;
OnInit:
	waitingroom "LV 41 ~ LV 50",0;
	end;
}

pvp_n_room.gat,46,85,4	script	試合場 受付#n-3pvp	105,{
	callfunc "PvPreceptN",3,51,60;
	close;
OnInit:
	waitingroom "LV 51 ~ LV 60",0;
	end;
}

pvp_n_room.gat,54,85,4	script	試合場 受付#n-4pvp	105,{
	callfunc "PvPreceptN",4,61,70;
	close;
OnInit:
	waitingroom "LV 61 ~ LV 70",0;
	end;
}

pvp_n_room.gat,62,85,4	script	試合場 受付#n-5pvp	105,{
	callfunc "PvPreceptN",5,71,80;
	close;
OnInit:
	waitingroom "LV 71 ~ LV 80",0;
	end;
}

pvp_n_room.gat,70,85,4	script	試合場 受付#n-6pvp	105,{
	callfunc "PvPreceptN",6,81,90;
	close;
OnInit:
	waitingroom "LV 81 ~ LV 90",0;
	end;
}

pvp_n_room.gat,78,85,4	script	試合場 受付#n-7pvp	105,{
	callfunc "PvPreceptN",7,91,255;
	close;
OnInit:
	waitingroom "LV 91 ~",0;
	end;
}

pvp_n_room.gat,86,85,4	script	試合場 受付#n-8pvp	105,{
	callfunc "PvPreceptN",8,0,0;
	close;
OnInit:
	waitingroom "無制限",0;
	end;
}
