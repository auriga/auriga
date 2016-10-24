//==============================================================================
// Ragnarok Online Inn Town Script	2005-05-22	by AthenaWiki
//==============================================================================

//全てfunctionに納める
//  callfunc "TownInn",Num,"Name","Map",SaveX,SaveY,WarpX,WarpY;
//				Num = 0:共通、1:セミ、2:アルマ、3:ホテル

function	script	TownInn	{
	next;
	switch (select("位置セーブする","宿泊する - 5000z","やめる")) {
	case 1:
		savepoint getarg(2),getarg(3),getarg(4);
		mes "["+getarg(1)+"]";
		switch(getarg(0)) {
			case 0:
				mes "位置セーブしました。";
				mes "またのご利用をお待ちしております。";
				return;
			case 1:
				mes "はい、セーブできました。";
				mes "ありがとうございました！";
				break;
			case 2:
				mes "はい、こちらでセーブできました。";
				mes "ご利用ありがとうございま～す。";
				break;
			case 3:
				mes "はい、位置セーブを行いました。";
				mes "ご利用、ありがとうございます。";
				next;
				mes "[ホテル職員]";
				mes "それでは、よい一日を。";
				return;
		}
		next;	//1,2だけnextして抜ける
		break;
	case 2:
		if(Zeny<5000) {
			mes "["+getarg(1)+"]";
			switch(getarg(0)) {
			case 0:
				mes "宿泊料は5000zになります。";
				mes "もう一度所持金をご確認ください。";
				return;
			case 1:
				mes "宿泊料は5000zですが……";
				mes "ちょっとお金が足りないみたいですね。";
				return;
			case 2:
				mes "宿泊料は5000zですよ。";
				mes "もう一度、お財布の中を";
				mes "確認していただけます？";
				return;
			case 3:
				mes "宿泊料金は。5000zenyです。";
				mes "所持金を再度ご確認ください。";
				return;
			}
		}
		mes "["+getarg(1)+"]";
		switch(getarg(0)) {
			case 0: mes "ごゆっくりお休みください。"; 	break;
			case 1: mes "ごゆっくりどうぞ～。"; 		break;
			case 2: mes "ぜひ、くつろいでくださいね～。"; 	break;
			case 3: mes "ごゆっくりお休みください。"; 	break;
		}
		close2;
		set Zeny,Zeny-5000;
		warp getarg(2),getarg(5),getarg(6);
		percentheal 100,100;
		end;
	}
	//「やめる」ならfall through
	switch(getarg(0)) {
		case 0:
			break;
		case 1:
		case 2:
			mes "["+getarg(1)+"]";
			mes "またのお越しをお待ちしております～";
			break;
		case 3:
			mes "[ホテル職員]";
			mes "またのお越しをお待ちしております。";
			break;
	}
	return;
}

// プロンテラ
prt_in.gat,244,135,0	script	旅館従業員	53,{
	mes "[従業員セミ]";
	mes "いらっしゃいませ！";
	mes "旅館「ネンカラス」本館にようこそ～。";
	mes "お客様、何の御用ですか？";
	callfunc "TownInn",1,"従業員セミ","prt_in.gat",238,131,247,104;
	close;
}

prt_in.gat,61,141,4	script	旅館従業員	94,{
	mes "[従業員アルマ]";
	mes "いらっしゃいませ！";
	mes "旅館「ネンカラス」別館にようこそ～。";
	mes "お客様、何の御用ですか？";
	callfunc "TownInn",2,"従業員アルマ","prt_in.gat",63,136,60,166;
	close;
}

// アインブロック
ein_in01.gat,206,224,3	script	ホテル職員	855,{
	mes "[ホテル職員]";
	mes "ようこそいらっしゃいました。";
	mes "当ホテルは、清潔、親切、";
	mes "笑顔をモットーに、";
	mes "お客様に最高の休息を提供する、";
	mes "アインブロック最高の施設です。";
	if(EIN_2QUE == 4) {	//船員の過去クエストで発行
		next;
		mes "[ホテル職員]";
		mes "ディーター・アーク様ですか？";
		mes "少々お待ちください。";
		next;
		mes "[ホテル職員]";
		mes "アーク様は201号室に";
		mes "宿泊していらっしゃいます。";
		next;
		mes "[ホテル職員]";
		mes "それでは、よい一日を。";
		close;
	}
	callfunc "TownInn",3,"ホテル職員","ein_in01.gat",201,223,272,167;
	close;
}

// アルデバラン
aldeba_in.gat,92,58,2	script	旅館従業員	53,{
	mes "[従業員リリム]";
	mes "いらっしゃいませ。";
	mes "何をお手伝いしましょうか？";
	callfunc "TownInn",0,"従業員リリム","aldeba_in.gat",93,50,92,112;
	close;
}

// (新)フェイヨン
payon_in01.gat,132,62,2	script	旅館従業員	53,{
	mes "[従業員アキ]";
	mes "あ、お客さん";
	mes "こちらはフェイヨン旅館です。";
	mes "何をお手伝いしましょうか？";
	callfunc "TownInn",0,"従業員アキ","payon_in01.gat",135,62,132,11;
	close;
}

// モロク
//morocc_in.gat,147,141,2	script	旅館従業員	53,{
//	mes "[従業員ハーシャ]";
//	mes "いらっしゃいませ！";
//	mes "何をお手伝いしましょうか？";
//	callfunc "TownInn",0,"従業員ハーシャ","morocc_in.gat",142,139,173,135;
//	close;
//}

//morocc_in.gat,78,100,4	script	旅館従業員	53,{
//	mes "[従業員マナル]";
//	mes "いらっしゃいませ！";
//	mes "何をお手伝いしましょうか？";
//	callfunc "TownInn",0,"従業員マナル","morocc_in.gat",78,95,78,95;
//	close;
//}

// アルベルタ
alberta_in.gat,32,142,2	script	旅館従業員	53,{
	mes "[従業員ジェニー]";
	mes "いらっしゃいませ。";
	mes "こちらは旅館フィッシャーマンです。";
	mes "何をお手伝いしましょうか？";
	callfunc "TownInn",0,"従業員ジェニー","alberta_in.gat",25,142,16,105;
	close;
}

// ゲフェン
geffen_in.gat,70,64,3	script	旅館従業員	53,{
	mes "[従業員セナ]";
	mes "いらっしゃいませ。";
	mes "こちらはゲフェン唯一の";
	mes "旅館イフリートです。";
	mes "何をお手伝いしましょうか？";
	callfunc "TownInn",0,"従業員セナ","geffen_in.gat",70,60,31,31;
	close;
}

//リヒタルゼン
//　functionは使わない
lhz_in02.gat,230,284,4	script	ホテル従業員	86,{
	mes "[ホテル従業員]";
	mes "ようこそ！　世界最高のホテル、";
	mes "ロイヤルドラゴンです。";
	mes "客室数、各種サービスなど、";
	mes "他のホテルとは比べ物になりません！";
	mes "快適な環境でお客様に";
	mes "最高の時間を約束致します。";
	next;
	switch(select("位置をセーブする","ちょっと休む - 5000z","帰る")) {
	case 1:
		savepoint "lhz_in02.gat",232,273;
		mes "[ホテル従業員]";
		mes "セーブしました。";
		mes "ご利用ありがとうございます。";
		close;
	case 2:
		if(Zeny<5000) {
			mes "[ホテル従業員]";
			mes "利用料は 5000z です。";
			close;
		}
		mes "[ホテル従業員]";
		mes "ごゆっくりどうぞ";
		close2;
		sc_start 10,240000,10;	//SC_BLESSING
		set Zeny,Zeny-5000;
		warp "lhz_in02.gat",220,150;
		percentheal 100,100;
		end;
	case 3:
		mes "[ホテル従業員]";
		mes "ありがとうございます。";
		mes "またお越しくださいませ。";
		close;
	}
}

//フィゲル
hu_in01.gat,246,107,3	script	旅館職員	53,{
	mes "[旅館職員]";
	mes "いらっしゃいませ～";
	mes "うちの旅館は";
	mes "旅行客のためにいつもきれいで";
	mes "さわやかな寝具が用意されています。";
	next;
	switch(select("セーブする","宿泊する-5000z","やめる")) {
	case 1:
		savepoint "hu_in01.gat",263,95;
		mes "[旅館職員]";
		mes "はい、こちらでセーブしました。";
		mes "ご利用ありがとうございます。";
		next;
		mes "[旅館職員]";
		mes "それでは、";
		mes "楽しい一日をお過ごしください。";
		close;
	case 2:
		if(Zeny<5000) {
			mes "[旅館職員]";
			mes "旅館利用料は5000Zenyです。";
			mes "所持金が足りないみたいですね。";
			close;
		}
		mes "[旅館職員]";
		mes "どうぞごゆっくり。";
		close2;
		set Zeny,Zeny-5000;
		warp "hu_in01.gat",267,5;
		percentheal 100,100;
		end;
	case 3:
		mes "[旅館職員]";
		mes "またどうぞ～";
		close;
	}
}

//ラヘル
ra_in01.gat,376,69,4	script	ホテル職員	931,{
	mes "[ホテル職員]";
	mes "女神フレイヤ様の御加護が";
	mes "共にあらん事を……";
	mes "フレイヤ様の果てしない愛の様に";
	mes "最高の安らぎを誇る";
	mes "このラヘルホテルへようこそ。";
	next;
	switch(select("セーブする","休む - 5000z","やめる")) {
	case 1:
		savepoint "ra_in01.gat",375,61;
		mes "[ホテル職員]";
		mes "はい、ここにセーブしました。";
		mes "ご利用、ありがとうございます。";
		next;
		mes "[ホテル職員]";
		mes "それでは、";
		mes "楽しい一日をお過ごしください！";
		close;
	case 2:
		if(Zeny<5000) {
			mes "[ホテル職員]";
			mes "ホテルの利用額は 5000z です。";
			mes "持ち合わせが足りないようですね。";
			close;
		}
		mes "[ホテル職員]";
		mes "では、ごゆっくり。";
		close2;
		set Zeny,Zeny-5000;
		warp "ra_in01.gat",358,130;
		percentheal 100,100;
		end;
	case 3:
		mes "[ホテル職員]";
		mes "またのご利用をお待ちしております。";
		close;
	}
}

//ベインス
ve_in.gat,157,219,5	script	旅館の主人	709,{
	mes "[旅館の主人]";
	mes "こんにちは！";
	mes "ベインスで一番涼しい旅館へ";
	mes "ようこそ！";
	next;
	switch(select("セーブする","休む - 5000z","止める")) {
	case 1:
		savepoint "ve_in.gat",157,210;
		mes "[旅館の主人]";
		mes "はい！";
		mes "ここにセーブしました！";
		mes "毎度、ありがとうございます。";
		close;
	case 2:
		if(Zeny<5000) {
			mes "[旅館の主人]";
			mes "旅館の宿泊料は 5000z です。";
			mes "お金が足りない様ですね……。";
			close;
		}
		mes "[旅館の主人]";
		mes "では、ごゆっくりどうぞ。";
		close2;
		set Zeny,Zeny-5000;
		warp "ve_in.gat",184,228;
		percentheal 100,100;
		end;
	case 3:
		mes "[旅館の主人]";
		mes "またのご利用を";
		mes "お待ちしております。";
		mes "ありがとうございました。";
		close;
	}
}

//ブラジリス
bra_in01.gat,27,24,3	script	ホテル管理人	478,{
	mes "[ホテル管理人]";
	mes "最高級の家具でおもてなし！";
	mes "滞在中の幸せな時間をお約束する、";
	mes "ブラジリスホテルへようこそ!!";
	next;
	if(select("セーブする","一晩泊まる - 5,000zeny") == 1) {
		mes "[ホテル管理人]";
		mes "セーブポイントを";
		mes "こちらにいたしますか？";
		next;
		if(select("やめる","セーブする") == 1) {
			mes "[ホテル管理人]";
			mes "取り消しされました。";
			close;
		}
		savepoint "bra_in01.gat",144,69;
		mes "[ホテル管理人]";
		mes "セーブしました。";
		mes "では、ごゆっくりとブラジリスを";
		mes "満喫してくださいませ。";
		close;
	}
	if(Zeny < 5000) {
		mes "[ホテル管理人]";
		mes "宿泊費は一晩 5,000zeny です。";
		close;
	}
	mes "[ホテル管理人]";
	mes "最高の部屋にご案内いたします。";
	close2;
	set Zeny,Zeny-5000;
	warp "bra_in01.gat",144,69;
	percentheal 100,100;
	end;
}
