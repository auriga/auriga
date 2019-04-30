//=========================================================================
// カプラ職員一括ファンクション
//	callfunc "KafraMain",Speech,SelectNum,"OutSave",OutX,OutY,"InSave",InX,InY,
//				Storage,Cart,MapCodeArray,PriceArray;
// ■ 引数の詳細
//	Speech -> セリフの分岐
//			0: 挨拶3行
//			1: 挨拶4行
//			2: コモド用
//			3: 特殊用、セリフなし
//			4: アインブログ・アインベフ用（空間移動選択時）
//	SelectNum -> 7つのサービスの中から選択するビットフラグ（0x1ffで7個全部）
//			+1:   位置セーブ
//			+2:   倉庫
//			+4:   空間移動
//			+8:   カート
//			+16:  カプラポイント
//			+32:  カプラ配置案内
//			+64:  装備解除
//			+128: 倉庫ショートカット
//			+256: 終了
//	"OutSave",OutX,OutY -> 「外でセーブ」のセーブポイント
//	                        選択肢が出ない場合もこれに該当
//	"InSave",InX,InY    -> 「中でセーブ」のセーブポイント
//	                        選択肢が出ない場合は"InSave"を"NULL"にする
//	                        ただし位置セーブサービス自体がない場合は完全に無視
//	Storage -> 倉庫料金
//	Cart -> カート利用料金
//	MapCodeArray -> 空間移動先のMAPコードを格納した配列変数
//	PriceArray -> 必要な料金を格納した配列変数
//
// ■ 空間移動用MAPコード
//	1	プロンテラ
//	2	イズルード
//	3	ゲフェン
//	4	フェイヨン
//	5	モロク
//	6	アルベルタ
//	7	オークダンジョン
//	8	アルデバラン
//	9	ミョルニール廃鉱
//	10	コモド
//	11	ファロス燈台島
//	12	コモドファロス燈台（11の別表示名）
//	13	ジュノー
//	14	プロンテラ（アジト）
//	15	ゲフェン（アジト）
//	16	フェイヨン（アジト）
//	17	アルデバラン（アジト）
//	18	ラヘル（アジト）
//	19	ウンバラ
//	20	予備1
//
// ■ parse終了処理
//	「カプラ配置案内」がある場合にはviewpointを付け加え、cutinを消す
//	ない場合はendで終了（なくても良い）
//
// ■ キャラクタ永続変数
//	KAFRA_PIT -> カプラポイント
//-------------------------------------------------------------------------

function	script	KafraMain	{
	//挨拶部分
	function KafraSpeech {
		if(getarg(0)!=3) {
			mes "[カプラ職員]";
			mes "いらっしゃいませ";
			mes "カプラサービスは";
			mes "いつも皆様のそばにいます。";
			switch(getarg(0)) {
			case 0:
				break;
			case 1:
			case 4:	//case4はアインブログ・アインベフ
				mes "何をお手伝いいたしましょう？";
				break;
			case 2:	//コモド
				mes "当、カプラサービス西部支部は";
				mes "サービスプログラム改良により";
				mes "より高品質のサービスをお約束します。";
				break;
			}
			next;
		}
		return;
	}

	//位置セーブサービス
	function KafraSave {
		if(getarg(5) == "NULL")
			savepoint getarg(2),getarg(3),getarg(4);	//選択肢なしでOutSave
		else if(select("町の外でセーブ","町の中でセーブ")==1)
			savepoint getarg(2),getarg(3),getarg(4);	//OutSave
		else
			savepoint getarg(5),getarg(6),getarg(7);	//InSave
		mes "[カプラ職員]";
		mes "セーブしました。";
		mes "ご利用ありがとうございます。";
		return;
	}

	//空間移動サービス
	function KafraTrans {
		if(getarg(0)==4) {	//アインブログ・アインベフ
			mes "[カプラ職員]";
			mes "当カプラサービスの";
			mes "シュバルツバルド本部では、";
			mes "シュバルツバルド共和国との協定";
			mes "「^FF0000空間移動サービス制限^000000」";
			mes "により、本サービスは";
			mes "行わない方針となっております。";
			next;
			mes "[カプラ職員]";
			mes "他地域への移動には、";
			mes "飛行船をご利用ください。";
			return;
		}
		copyarray '@price,getarg(11),getarraysize(getarg(11));	//受け取ったPriceArrayを配列に展開
		//初回呼び出し時のみsetarrayする
		if('placename$[0] == "") {
			setarray 'placename$,	"プロンテラ","イズルード","ゲフェン","フェイヨン","モロク","アルベルタ",
						"オークダンジョン","アルデバラン","ミョルニール廃鉱","コモド","ファロス燈台島",
						"コモドファロス燈台","ジュノー","プロンテラ","ゲフェン","フェイヨン","アルデバラン",
						"ラヘル","ウンバラ","予備1";
		}
		for(set '@i,0; '@i<getarraysize('@price); set '@i,'@i+1)
			set '@place$['@i],'placename$[ getelementofarray(getarg(10),'@i)-1 ] +" -> "+ '@price['@i] +" z";
		mes "[カプラ職員]";
		mes "目的地をお選び下さい。";
		next;
		set '@j,select(		'@place$[0],'@place$[1],'@place$[2],'@place$[3],'@place$[4],'@place$[5],'@place$[6],'@place$[7],
					'@place$[8],'@place$[9],'@place$[10],'@place$[11],'@place$[12],'@place$[13],'@place$[14],'@place$[15],
					'@place$[16],'@place$[17],'@place$[18],'@place$[19],"取り消し")-1;
		if('@j==20) {
			mes "[カプラ職員]";
			mes "ありがとうございました。";
			mes "またご利用くださいませ。";
			return;
		}
		if(Zeny<'@price['@j]) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りません。";
			mes "所持金をお確かめください。";
			return;
		}
		set Zeny,Zeny-'@price['@j];
		set KAFRA_PIT,KAFRA_PIT+('@price['@j]/10);
		switch ( getelementofarray(getarg(10),'@j) ) {
			case 1: warp "prontera.gat",116,72; 	break;
			case 2: warp "izlude.gat",91,105; 	break;
			case 3: warp "geffen.gat",120,39; 	break;
			case 4: warp "payon.gat",160,58; 	break;
			case 5: warp "morocc.gat",156,46; 	break;
			case 6: warp "alberta.gat",117,56; 	break;
			case 7: warp "gef_fild10.gat",52,326; 	break;
			case 8: warp "aldebaran.gat",167,112; 	break;
			case 9: warp "mjolnir_02.gat",99,351; 	break;
			case 10: warp "comodo.gat",209,143; 	break;
			case 11:
			case 12:
				 warp "cmd_fild07.gat",127,134; break;
			case 13: warp "yuno.gat",158,124; 	break;
			//アジト専属カプラ用
			case 14: warp "prontera.gat",278,211; 	break;
			case 15: warp "geffen.gat",120,39; 	break;
			case 16: warp "payon.gat",158,88; 	break;
			case 17: warp "aldebaran.gat",132,103;	break;
			case 18: warp "rachel.gat",115,125;	break;
			case 19: warp "umbala",100,154;		break;
			//予備
			case 20: warp "SavePoint",0,0;		break;
		}
		end;
	}

	//カートサービス
	function KafraCart {
		if(getbaseclass(Class) != CLASS_MC) {
			mes "[カプラ職員]";
			mes "申し訳ございません。";
			mes "カートは商人とその上位職専用の";
			mes "サービスです。";
			return;
		}
		if(checkcart()) {
			mes "[カプラ職員]";
			mes "お客様は現在カートを";
			mes "利用されています。";
			return;
		}
		mes "[カプラ職員]";
		mes "カート利用料金は" +getarg(9)+ "Zenyです。";
		mes "また、カートを利用するには";
		mes "「プッシュカート」スキルが必要です。";
		mes "そのスキルがないとカートを利用";
		mes "できずにお金だけ消えてしまいます。";
		mes "準備はよろしいですか？";
		next;
		if(select("利用する","取り消し")==2) {
			mes "[カプラ職員]";
			mes "ありがとうございました。";
			mes "またご利用くださいませ。";
			return;
		}
		if(Zeny<getarg(9)) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りません。";
			mes "カート利用料金は"+getarg(9)+"Zenyです。";
			return;
		}
		set Zeny,Zeny-getarg(9);
		set KAFRA_PIT,KAFRA_PIT+(getarg(9)/10);
		setcart;
		return;
	}

	//カプラポイント確認
	function KafraPoint {
		mes "[カプラ職員]";
		mes strcharinfo(0)+ "様の獲得ポイントは、";
		mes KAFRA_PIT+ "点です。";
		next;
		mes "[カプラ職員]";
		mes "カプラポイントは当カプラサービスの";
		mes "本社で賞品と引き換えが可能です。";
		mes "今後ともカプラサービスをよろしく";
		mes "お願い致します。";
		return;
	}

	//装備解除サービス
	function KafraUnequip {
		misceffect 389,"";
		misceffect 411,"";
		unequip -2;
		mes "[カプラ職員]";
		mes "装備アイテムを解除いたしました。";
		mes "ご利用ありがとうございます。";
		return;
	}

	//「倉庫ショートカット」の設定変更
	function KafraStorageConf {
		mes "[カプラ職員]";
		mes "「倉庫ショートカット」の";
		mes "設定を変更していただけます。";
		if(checkquest(202060) & 0x8)
			mes "現在は「設定^FF0000ON^000000」となっています。";
		else
			mes "現在は「設定^0000FFOFF^000000」となっています。";
		mes "いかがいたしましょうか？";
		next;
		if(select("切り替える","やっぱりやめる") == 2) {
			mes "[カプラ職員]";
			mes "かしこまりました。";
			mes "設定を変更する際は";
			mes "またお越しくださいませ。";
			return;
		}
		if(checkquest(202060) & 0x8) {
			setquest 202060;
			delquest 202060;
		}
		else {
			setquest 202060;
			compquest 202060;
		}
		misceffect 128,"";
		mes "[カプラ職員]";
		if(checkquest(202060) & 0x8)
			mes "「設定^FF0000ON^000000」に切り替えました。";
		else
			mes "「設定^0000FFOFF^000000」に切り替えました。";
		mes "設定を変更する際は";
		mes "またお越しくださいませ。";
		return;
	}

	//初回設定
	function KafraInit {
		mes "[カプラ職員]";
		mes "冒険者の皆様に、より満足いただけるよう";
		mes "「^FF0000倉庫ショートカット^000000」サービスと";
		mes "「^FF0000装備解除^000000」サービスの提供を";
		mes "開始いたしました。";
		next;
		mes "[カプラ職員]";
		mes "「^FF0000倉庫ショートカット^000000」サービスは";
		mes "設定を「ON」にすることで";
		mes "ご利用いただけます。";
		mes "現在は「設定^0000FFOFF^000000」となっています。";
		mes "今すぐ設定を切り替えますか？";
		mes "後程、切り替えることもできます。";
		next;
		switch(select("今はやめておく","「ON」に切り替える")) {
		case 1:
			mes "[カプラ職員]";
			mes "かしこまりました。";
			break;
		case 2:
			setquest 202060;
			compquest 202060;
			misceffect 128,"";
			mes "[カプラ職員]";
			mes "「設定^FF0000ON^000000」に切り替えました。";
			break;
		}
		mes "設定を変更する際は";
		mes "「^FF0000「倉庫ショートカット」の設定変更^000000」と";
		mes "お申し付けください。";
		next;
		setquest 202065;
		compquest 202065;
		return;
	}

	//終了
	function KafraEnd {
		mes "[カプラ職員]";
		mes "我々カプラサービスは、より完璧な";
		mes "サービスと管理業務を目指し";
		mes "お客様が安心してご利用いただけるよう";
		mes "いつも最善を尽くしています。";
		mes "（株）カプラサービスをご利用いただき";
		mes "ありがとうございました。";
		return;
	}

	//ここからmain
	KafraSpeech getarg(0);
	if(!checkquest(202065)) {
		KafraInit;
	}
	if(checkquest(202060) & 0x8) {
		while(1) {
			switch(select("^0000FF倉庫^000000を開く","装備の解除","いつものサービスを利用")) {
			case 1:
				//倉庫サービスは分離
				callfunc "KafraStorage",getarg(8);
				end;
			case 2:
				misceffect 389,"";
				misceffect 411,"";
				unequip -2;
				mes "[カプラ職員]";
				mes "装備アイテムを解除いたしました。";
				mes "続けて倉庫サービスをご利用いただけます。";
				next;
				continue;
			case 3:
				break;
			}
			break;
		}
	}
	setarray '@serv$,"位置セーブサービス","倉庫サービス -> " +getarg(8)+ "zeny","空間移動サービス",
				"カートサービス","カプラポイント確認","カプラ職員配置案内","装備解除サービス","「倉庫ショートカット」の設定変更","終了";
	for(set '@i,0; '@i<9; set '@i,'@i+1) {
		if(getarg(1)&(1<<'@i) == 0)
			set '@serv$['@i],"";	//SelectNumのビットフラグが立ってなければ空で埋める
	}
	switch (select('@serv$[0],'@serv$[1],'@serv$[2],'@serv$[3],'@serv$[4],'@serv$[5],'@serv$[6],'@serv$[7],'@serv$[8])) {
		case 1:
			//0,1はダミー
			KafraSave 0,1,getarg(2),getarg(3),getarg(4),getarg(5),getarg(6),getarg(7);
			break;
		case 2:
			//倉庫サービスは分離
			callfunc "KafraStorage",getarg(8);
			end;
		case 3:
			//1～9はダミー
			if(getarg(0) != 4)
				KafraTrans getarg(0),1,2,3,4,5,6,7,8,9,getarg(10),getarg(11);
			else
				KafraTrans getarg(0);
			break;
		case 4:
			//0～8はダミー
			KafraCart 0,1,2,3,4,5,6,7,8,getarg(9);
			break;
		case 5:
			KafraPoint;
			break;
		case 6:
			mes "[カプラ職員]";
			mes "ミニMAP表示地点に";
			mes "カプラ職員がいます。";
			return;	//case6のみreturnして配置案内
		case 7:
			KafraUnequip;
			break;
		case 8:
			KafraStorageConf;
			break;
		case 9:
			KafraEnd;
			break;
	}
	close2;
	cutin "kafra_01",255;
	end;
}

//倉庫サービスだけ分離
function	script	KafraStorage	{
	if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
		mes "[カプラ職員]";
		mes "倉庫は基本スキルレベル6を";
		mes "習得してから利用可能となります。";
	}
	else if(Zeny<getarg(0)) {
		mes "[カプラ職員]";
		mes "お客様、お金が足りません。";
		mes "倉庫利用料金は"+getarg(0)+"Zenyです。";
	}
	else {
		set Zeny,Zeny-getarg(0);
		set KAFRA_PIT,KAFRA_PIT+(getarg(0)/10);
		openstorage;
		cutin "kafra_01",255;
		close;
	}
	close2;
	cutin "kafra_01",255;
	return;
}

//----------------------------------
// < プロンテラ - 中央 >
//----------------------------------

prontera.gat,146,89,6	script	カプラ職員	117,{
	cutin "kafra_01",2;
	setarray '@code,2,3,4,5,6,8,7;
	setarray '@price,600,1200,1200,1200,1800,2000,1700;
	callfunc "KafraMain",1,0x1ff,"prontera.gat",116,72,"NULL",0,0,40,800,'@code,'@price;
	close2;
	viewpoint 1,146,89,1,0x0000FF;
	viewpoint 1,282,200,2,0x0000FF;
	viewpoint 1,151,29,3,0x0000FF;
	viewpoint 1,29,207,4,0x0000FF;
	cutin "kafra_01",255;
	end;
}

//----------------------------------
// < プロンテラ - 東カプラ >
//----------------------------------

prontera.gat,282,200,2	script	カプラ職員	114,{
	cutin "kafra_04",2;
	setarray '@code,2,3,4,5,6,8,7;
	setarray '@price,600,1200,1200,1200,1800,2000,1700;
	callfunc "KafraMain",1,0x1ff,"prt_fild06.gat",33,192,"prontera.gat",279,200,40,800,'@code,'@price;
	close2;
	viewpoint 1,146,89,1,0x0000FF;
	viewpoint 1,282,200,2,0x0000FF;
	viewpoint 1,151,29,3,0x0000FF;
	viewpoint 1,29,207,4,0x0000FF;
	cutin "kafra_04",255;
	end;
}

//----------------------------------
// < プロンテラ - 南カプラ >
//----------------------------------

prontera.gat,151,29,0	script	カプラ職員	115,{
	cutin "kafra_03",2;
	setarray '@code,2,3,4,5,6,8,7;
	setarray '@price,600,1200,1200,1200,1800,2000,1700;
	callfunc "KafraMain",1,0x1ff,"prt_fild08.gat",170,368,"prontera.gat",116,72,40,800,'@code,'@price;
	close2;
	viewpoint 1,146,89,1,0x0000FF;
	viewpoint 1,282,200,2,0x0000FF;
	viewpoint 1,151,29,3,0x0000FF;
	viewpoint 1,29,207,4,0x0000FF;
	cutin "kafra_03",255;
	end;
}

//----------------------------------
// < プロンテラ - 西カプラ >
//----------------------------------

prontera.gat,29,207,6	script	カプラ職員	113,{
	cutin "kafra_05",2;
	setarray '@code,2,3,4,5,6,8,7;
	setarray '@price,600,1200,1200,1200,1800,2000,1700;
	callfunc "KafraMain",1,0x1ff,"prt_fild05.gat",368,205,"prontera.gat",33,207,40,800,'@code,'@price;
	close2;
	viewpoint 1,146,89,1,0x0000FF;
	viewpoint 1,282,200,2,0x0000FF;
	viewpoint 1,151,29,3,0x0000FF;
	viewpoint 1,29,207,4,0x0000FF;
	cutin "kafra_05",255;
	end;
}

//----------------------------------
// < プロンテラ - 北カプラ >
//----------------------------------

prt_fild01.gat,198,47,0	script	カプラ職員	112,{
	cutin "kafra_06",2;
	setarray '@code,2,3,4,5,6,8,7;
	setarray '@price,600,1200,1200,1200,1800,2000,1700;
	callfunc "KafraMain",1,0x1df,"prt_fild01.gat",198,51,"NULL",0,0,40,800,'@code,'@price;
	end;
}

//----------------------------------
// < プロンテラ - 地下水路前のカプラ >
//----------------------------------

prt_fild05.gat,290,224,4	script	カプラ職員	114,{
	cutin "kafra_04",2;
	callfunc "KafraMain",0,0x1db,"prt_fild05.gat",274,244,"NULL",0,0,30,800;
	end;
}

//----------------------------------
// < イズルード - 町の中 >
//----------------------------------

izlude.gat,134,88,4	script	カプラ職員	115,{
	cutin "kafra_03",2;
	setarray '@code,1,5,4,3,8;
	setarray '@price,600,1200,1200,1200,1800;
	callfunc "KafraMain",1,0x1ff,"prt_fild08.gat",350,202,"izlude.gat",94,103,30,800,'@code,'@price;
	close2;
	viewpoint 1,136,88,1,0x0000FF;
	cutin "kafra_03",255;
	end;
}

//----------------------------------
// < ゲフェン - 南噴水 >
//----------------------------------

geffen.gat,120,62,0	script	カプラ職員	115,{
	cutin "kafra_03",2;
	setarray '@code,1,8,7,9;
	setarray '@price,1200,1200,1700,1700;
	callfunc "KafraMain",0,0x1ff,"geffen.gat",120,38,"NULL",0,0,30,800,'@code,'@price;
	close2;
	viewpoint 1,120,62,1,0x0000FF;
	viewpoint 1,203,123,2,0x0000FF;
	cutin "kafra_03",255;
	end;
}

//----------------------------------
// < ゲフェン - 東入り口 >
//----------------------------------

geffen.gat,203,123,4	script	カプラ職員	114,{
	cutin "kafra_04",2;
	setarray '@code,1,8,7,9;
	setarray '@price,1200,1200,1700,1700;
	callfunc "KafraMain",0,0x1ff,"gef_fild00.gat",55,222,"geffen.gat",120,38,30,800,'@code,'@price;
	close2;
	viewpoint 1,120,62,1,0x0000FF;
	viewpoint 1,203,123,2,0x0000FF;
	cutin "kafra_04",255;
	end;
}

//----------------------------------
// < モロク - 南 >
//----------------------------------

morocc.gat,156,97,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	setarray '@code,1,4,6,10,11;
	setarray '@price,1200,1200,1800,1800,1200;
	callfunc "KafraMain",1,0x1ff,"morocc.gat",156,46,"NULL",0,0,40,800,'@code,'@price;
	close2;
	viewpoint 1,160,258,1,0x0000FF;
	viewpoint 1,159,97,2,0x0000FF;
	cutin "kafra_05",255;
	end;
}

//----------------------------------
// < モロク - 北入り口 >
//----------------------------------

morocc.gat,160,258,4	script	カプラ職員	114,{
	cutin "kafra_04",2;
	setarray '@code,1,4,6,10,11;
	setarray '@price,1200,1200,1800,1800,1200;
	callfunc "KafraMain",1,0x1ff,"moc_fild07.gat",211,29,"morocc.gat",160,283,40,800,'@code,'@price;
	close2;
	viewpoint 1,160,258,1,0x0000FF;
	viewpoint 1,159,97,2,0x0000FF;
	cutin "kafra_04",255;
	end;
}

//----------------------------------
// < モロク - ピラミッド入り口 >
//----------------------------------

moc_ruins.gat,59,157,6	script	カプラ職員	117,{
	cutin "kafra_01",2;
	callfunc "KafraMain",1,0x1da,0,0,0,0,0,0,50,800;
	end;
}

//----------------------------------
// < アルベルタ - 北入り口 >
//----------------------------------

alberta.gat,28,229,0	script	カプラ職員	116,{
	cutin "kafra_02",2;
	setarray '@code,4,1,5;
	setarray '@price,1200,1800,1800;
	callfunc "KafraMain",1,0x1ff,"pay_fild03.gat",387,76,"alberta.gat",31,231,50,800,'@code,'@price;
	close2;
	viewpoint 1,28,229,1,0x0000FF;
	viewpoint 1,113,60,2,0x0000FF;
	cutin "kafra_02",255;
	end;
}

//----------------------------------
// < アルベルタ - 南噴水 >
//----------------------------------

alberta.gat,113,60,6	script	カプラ職員#alberta2	112,{
	cutin "kafra_06",2;
	setarray '@code,4,1,5;
	setarray '@price,1200,1800,1800;
	callfunc "KafraMain",1,0x1ff,"alberta.gat",117,56,"NULL",0,0,50,800,'@code,'@price;
	close2;
	viewpoint 1,28,229,1,0x0000FF;
	viewpoint 1,113,60,2,0x0000FF;
	cutin "kafra_06",255;
	end;
}

//----------------------------------
// < アルベルタ - 島 >
//----------------------------------

alb2trea.gat,59,69,6	script	カプラ職員	117,{
	cutin "kafra_01",2;
	callfunc "KafraMain",0,0x1da,0,0,0,0,0,0,50,800;
	end;
}

//----------------------------------
// < フェイヨン - 北 >
//----------------------------------

payon.gat,175,226,4	script	カプラ職員	116,{
	cutin "kafra_02",2;
	setarray '@code,6,1,5;
	setarray '@price,1200,1200,1200;
	callfunc "KafraMain",1,0x1df,"payon.gat",207,113,"NULL",0,0,40,800,'@code,'@price;
	end;
}

//----------------------------------
// < フェイヨン - 南 >
//----------------------------------

payon.gat,181,104,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	setarray '@code,6,1,5;
	setarray '@price,1200,1200,1200;
	callfunc "KafraMain",1,0x1df,"payon.gat",160,58,"NULL",0,0,40,800,'@code,'@price;
	end;
}

//----------------------------------
// < フェイヨン - アーチャー村 >
//----------------------------------

pay_arche.gat,55,123,4	script	カプラ職員	114,{
	cutin "kafra_04",2;
	callfunc "KafraMain",1,0x1db,"pay_arche.gat",50,145,"NULL",0,0,40,800;
	end;
}

//----------------------------------
// < アルデバラン >
//----------------------------------

aldebaran.gat,143,119,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	setarray '@code,3,13,2,1,9;
	setarray '@price,1200,1200,1800,2000,1700;
	callfunc "KafraMain",0,0x1df,"aldebaran.gat",167,112,"NULL",0,0,40,800,'@code,'@price;
	end;
}

//----------------------------------
// < コモド 室内 >
//----------------------------------

cmd_in02.gat,146,180,4	script	カプラ職員	721,{
	cutin "kafra_07",2;
	setarray '@code,5,12;
	setarray '@price,1800,1200;
	callfunc "KafraMain",2,0x1df,"comodo.gat",209,143,"NULL",0,0,40,800,'@code,'@price;
	end;
}

//----------------------------------
// < コモド ファロス 燈台 >
//----------------------------------

cmd_fild07.gat,136,134,4	script	カプラ職員	721,{
	cutin "kafra_07",2;
	setarray '@code,10,5;
	setarray '@price,1200,1200;
	callfunc "KafraMain",2,0x1df,"cmd_fild07.gat",127,134,"NULL",0,0,80,1000,'@code,'@price;
	end;
}

//----------------------------------
// < コモド > 
//----------------------------------

comodo.gat,195,150,4	script	カプラ職員	721,{
	cutin "kafra_07",2;
	setarray '@code,5,12,19;
	setarray '@price,1800,1200,1800;
	callfunc "KafraMain",2,0x1df,"comodo.gat",180,151,"NULL",0,0,80,1000,'@code,'@price;
	end;
}

//----------------------------------
// < オークダンジョン前 >
//----------------------------------

gef_fild10.gat,73,340,5	script	カプラ職員	117,{
	cutin "kafra_01",2;
	setarray '@code,3,8;
	setarray '@price,1700,1700;
	callfunc "KafraMain",0,0x1da,0,0,0,0,0,0,130,800;
	end;
}

//----------------------------------
// < ミョルニール廃鉱前 >
//----------------------------------

mjolnir_02.gat,82,362,4	script	カプラ職員	117,{
	cutin "kafra_01",2;
	setarray '@code,1,3;
	setarray '@price,1700,1700;
	callfunc "KafraMain",1,0x1da,0,0,0,0,0,0,100,800;
	end;
}

//----------------------------------
// < ジュノー > 南入り口
//----------------------------------

yuno.gat,152,187,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	set '@code,8;
	set '@price,1200;
	callfunc "KafraMain",0,0x1ff,"yuno.gat",158,124,"NULL",0,0,40,800,'@code,'@price;
	close2;
	viewpoint 1,327,109,2,0x0000FF;
	viewpoint 1,277,221,3,0x0000FF;
	cutin "kafra_05",255;
	end;
}

//----------------------------------
// < ジュノー > 南東
//----------------------------------

yuno.gat,327,109,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	set '@code,8;
	set '@price,1200;
	callfunc "KafraMain",0,0x1ff,"yuno.gat",327,100,"NULL",0,0,40,800,'@code,'@price;
	close2;
	viewpoint 1,152,187,1,0x0000FF;
	viewpoint 1,277,221,3,0x0000FF;
	cutin "kafra_05",255;
	end;
}

//----------------------------------
// < ジュノー > 北東
//----------------------------------

yuno.gat,277,221,4	script	カプラ職員	113,{
	cutin "kafra_05",2;
	set '@code,8;
	set '@price,1200;
	callfunc "KafraMain",0,0x1ff,"yuno.gat",275,229,"NULL",0,0,40,800,'@code,'@price;
	close2;
	viewpoint 1,152,187,1,0x0000FF;
	viewpoint 1,327,109,2,0x0000FF;
	cutin "kafra_05",255;
	end;
}

//----------------------------------
// < アマツ >
//----------------------------------

amatsu.gat,102,149,5	script	カプラ職員#amatsunomal	116,{
	cutin "kafra_02",2;
	mes "[カプラ職員]";
	mes "まったくもう、研修に送ったコは";
	mes "どこにいっちゃったのかしら……";
	mes "お客様もこんなに遠くまで観光ですか？";
	mes "私もせっかく来たんだからゆっくり";
	mes "していこっと。";
	mes "空気は良いし、お花も綺麗ですしね。";
	next;
	mes "[カプラ職員]";
	mes "さて、カプラサービスはたとえ";
	mes "異国の地でもお客様のために";
	mes "サービスを欠かしません。";
	mes "何をお手伝いいたしましょう？";
	next;
	callfunc "KafraMain",3,0x1db,"amatsu.gat",116,94,"NULL",0,0,80,700;
	end;
}

//----------------------------------
// < コンロン >
//----------------------------------

gonryun.gat,159,122,4	script	カプラ職員	116,{
	cutin "kafra_02",2;
	callfunc "KafraMain",1,0x1db,"gonryun.gat",160,62,"NULL",0,0,80,700;
	end;
}

//----------------------------------
// < ウンバラ >
//----------------------------------

umbala.gat,87,160,5	script	カプラ職員	721,{
	cutin "kafra_07",2;
	set '@code,10;
	set '@price,1800;
	callfunc "KafraMain",0,0x1d7,"umbala.gat",100,154,"NULL",0,0,80,0,'@code,'@price;
	end;
}

//----------------------------------
// < ニブルヘイム >
//----------------------------------

niflheim.gat,202,180,3	script	カプラ職員	791,{
	mes "[カプラ職員]";
	mes "いらっしゃいませ……";
	mes "カプラサービスは……";
	mes "死んでも皆様のそばにいます。";
	mes "何をお手伝いしましょう？";
	next;
	if(select("倉庫サービス","終了")==2) {
		percentheal 0,-25;
		mes "[カプラ職員]";
		mes "我々カプラサービスは…… ";
		mes "いつでもどこででも…… ";
		mes "お客様のそばに……います。";
		mes "……ですから決して……";
		mes "忘れないでください……";
		close;
	}
	if(basicskillcheck() && ((getskilllv(1) < 6 && Job != Job_Summoner) || (getskilllv(5018) < 1 && Job == Job_Summoner))) {
		mes "[カプラ職員]";
		mes "倉庫は……基本スキルレベル6を";
		mes "習得してから利用可能となります……";
		close;
	}
	else if(Zeny < 150) {
		percentheal -50,-50;
		mes "[カプラ職員]";
		mes "お客様……お金が足りません。";
		mes "倉庫利用料金は 150 Zenyです……";
		mes "足りなければ……あなたの生命を……";
		mes "私に……分けてください……";
		close;
	}
	set Zeny,Zeny-150;
	percentheal 0,-10;
	openstorage;
	close;
}

//----------------------------------
// < 龍之城 >
//----------------------------------

louyang.gat,210,104,4	script	カプラ職員	116,{
	cutin "kafra_02",2;
	callfunc "KafraMain",1,0x1db,"louyang.gat",218,97,"NULL",0,0,80,700;
	end;
}

//----------------------------------
// < アユタヤ >
//----------------------------------

ayothaya.gat,212,169,6	script	カプラ職員	116,{
	cutin "kafra_02",2;
	callfunc "KafraMain",1,0x1db,"ayothaya.gat",217,187,"NULL",0,0,80,700;
	end;
}

//----------------------------------
// < アインブロック - 広場 >
//----------------------------------

einbroch.gat,242,205,5	script	カプラ職員#einbroch1	116,{
	cutin "kafra_02",2;
	callfunc "KafraMain",4,0x1ff,"einbroch.gat",239,197,"NULL",0,0,40,800;
	close2;
	viewpoint 1,242,205,1,0x0000FF;
	viewpoint 1,59,203,2,0x0000FF;
	cutin "kafra_02",255;
	end;
}

//----------------------------------
// < アインブロック - 空港 >
//----------------------------------

einbroch.gat,59,203,5	script	カプラ職員#einbroch2	117,{
	cutin "kafra_01",2;
	callfunc "KafraMain",4,0x1ff,"einbroch.gat",239,197,"NULL",0,0,40,800;
	close2;
	viewpoint 1,242,205,1,0x0000FF;
	viewpoint 1,59,203,2,0x0000FF;
	cutin "kafra_01",255;
	end;
}

//----------------------------------
// < アインベフ >
//----------------------------------

einbech.gat,181,132,5	script	カプラ職員	115,{
	cutin "kafra_03",2;
	callfunc "KafraMain",4,0x1ff,"einbech.gat",181,123,"NULL",0,0,40,850;
	close2;
	viewpoint 1,181,132,1,0x0000FF;
	cutin "kafra_03",255;
	end;
}

//----------------------------------
// < リヒタルゼン北 >
//----------------------------------

lighthalzen.gat,191,320,4	script	カプラ職員	861,{
	cutin "kafra_09",2;
	callfunc "KafraMain",4,0x1df,"lighthalzen.gat",194,313,"NULL",0,0,40,800;
	end;
}

//----------------------------------
// < リヒタルゼン南 >
//----------------------------------

lighthalzen.gat,164,100,4	script	カプラ職員	860,{
	cutin "kafra_08",2;
	callfunc "KafraMain",4,0x1df,"lighthalzen.gat",158,96,"NULL",0,0,40,800;
	end;
}

//----------------------------------
// < リヒタルゼンホテル >
//----------------------------------

lhz_in02.gat,237,284,4	script	カプラ職員	861,{
	cutin "kafra_09",2;
	callfunc "KafraMain",4,0x1df,"lhz_in02.gat",278,214,"NULL",0,0,40,800;
	end;
}

//----------------------------------
// < モスコビア >
//----------------------------------

moscovia.gat,223,191,3	script	カプラ職員	114,{
	cutin "kafra_04",2;
	callfunc "KafraMain",1,0x1db,"moscovia.gat",220,193,"NULL",0,0,80,700;
	end;
}

//----------------------------------
// < ブラジリス >
//----------------------------------

brasilis.gat,197,221,3	script	カプラ職員	112,{
	cutin "kafra_06",2;
	callfunc "KafraMain",1,0x1db,"brasilis.gat",195,259,"NULL",0,0,40,700;
	end;
}

//----------------------------------
// < デワタ >
//----------------------------------

dewata.gat,202,184,6	script	カプラ職員	117,{
	cutin "kafra_01",2;
	callfunc "KafraMain",1,0x1db,"dewata.gat",199,177,"NULL",0,0,40,800;
	end;
}

//----------------------------------
// < ポートマラヤ >
//----------------------------------

malaya.gat,71,79,4	script	カプラ職員	581,{
	callfunc "KafraMain",1,0x1db,"malaya.gat",44,54,"NULL",0,0,500,800;
	end;
}

malaya.gat,234,204,4	script	カプラ職員	581,{
	callfunc "KafraMain",1,0x1db,"malaya.gat",281,211,"NULL",0,0,500,800;
	end;
}

//----------------------------------
// < プロンテラ - 昔の剣士ギルド >
//----------------------------------

prontera.gat,248,42,0	script	カプラ職員#ProSword	116,{
	cutin "kafra_02",2;
	mes "[カプラ職員]";
	mes "いらっしゃいませ、（株）カプラです。";
	mes "ご覧のとおり剣士ギルドは";
	mes "首都プロンテラから";
	mes "衛星都市「イズルード」に";
	mes "移転しました。";
	next;
	mes "[カプラ職員]";
	mes "我々（株）カプラでは";
	mes "ここプロンテラからイズルードまで";
	mes "利用料 600 Zenyで移動サービスを";
	mes "行っています。";
	next;
	switch (select("利用する","カプラポイント確認","終了")) {
	case 1:
		if(Zeny<600) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りないようですが。";
			break;
		}
		set Zeny,Zeny-600;
		set KAFRA_PIT,KAFRA_PIT+60;
		warp "izlude.gat",94,103;
		end;
	case 2:	//function内からコピー
		mes "[カプラ職員]";
		mes strcharinfo(0)+ "様の獲得ポイントは、";
		mes KAFRA_PIT+ "点です。";
		next;
		mes "[カプラ職員]";
		mes "カプラポイントは当カプラサービスの";
		mes "本社で賞品と引き換えが可能です。";
		mes "今後ともカプラサービスをよろしく";
		mes "お願い致します。";
		break;
	case 3:
		mes "[カプラ職員]";
		mes "ありがとうございました。";
		break;
	}
	close2;
	cutin "kafra_02",255;
	end;
}

//----------------------------------
// < イズルード - バイラン島 >
//----------------------------------

izlu2dun.gat,106,58,4	script	カプラ職員#Byalan	116,{
	cutin "kafra_02",2;
	callfunc "KafraMain",0,0x1da,0,0,0,0,0,0,40,800;
	end;
}
