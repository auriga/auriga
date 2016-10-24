//==============================================================================
// Ragnarok Online Arena Script     by AthenaDev
//
//   ■ ARENA_PIT -> アリーナポイント
//	TURBO_PIT -> ターボトラックポイント
//	$ArenaName$[] -> 1位記録者のキャラ名、要素はセクションごとに0～4
//	$ArenaTime[]   -> 記録タイム、要素は同上
//==============================================================================

//==============================================================
arena_room.gat,94,93,4	script	ベンデゴス	97,{
	mes "[ベンデゴス]";
	mes "アリーナの世界へようこそ!!";
	mes "私が案内を務めているベンデゴスです。";
	next;
	mes "[ベンデゴス]";
	mes "質問があればお答えしましょう！";
	while(1) {
		next;
		switch (select("アリーナって？","アリーナポイントって？","アリーナポイントの確認","なんでもないです")) {
		case 1:
			mes "[ベンデゴス]";
			mes "アリーナでは^3131FF個人戦^000000と^3131FFパーティー戦^000000が";
			mes "あり、制限時間以内でどれだけ早く";
			mes "モンスターを倒せるかを競って";
			mes "いただきます。";
			next;
			mes "[ベンデゴス]";
			mes "^3131FF個人戦^000000は";
			mes "　レベル50～69";
			mes "　レベル60～79";
			mes "　レベル70～89";
			mes "　レベル80～99";
			mes "のセクションに分かれています。";
			next;
			mes "[ベンデゴス]";
			mes "^3131FFパーティー戦^000000は5人編成の";
			mes "パーティーで挑戦する方式です。";
			next;
			mes "[ベンデゴス]";
			mes "個人戦ではレベル別に、担当者が";
			mes "チャットルームを開設してお待ちして";
			mes "います。チャットルーム内の待機順に";
			mes "アリーナに挑戦することが出来ます。";
			break;
		case 2:
			mes "[ベンデゴス]";
			mes "^3131FFアリーナポイント^000000についてご説明";
			mes "いたします。";
			mes "アリーナポイントとは^3131FFアリーナを^000000";
			mes "^3131FFクリアした時^000000に与えられるポイントで";
			mes "最大3万ポイントまで獲得することが";
			mes "出来ます。";
			next;
			mes "[ベンデゴス]";
			mes "クリア時間を超過しても、わずかでは";
			mes "ありますが、参加ポイントが支給され";
			mes "ます。";
			next;
			mes "[ベンデゴス]";
			mes "アリーナポイントの使用については";
			mes "担当者のギブをお探しください。";
			break;
		case 3:
			mes "[ベンデゴス]";
			mes strcharinfo(0)+ "様の";
			mes "アリーナポイントを確認いたします。";
			next;
			mes "[ベンデゴス]";
			mes strcharinfo(0)+ "様の";
			mes "アリーナポイントは……";
			mes "^3131FF" +ARENA_PIT+ "^000000点です";
			next;
			mes "[ベンデゴス]";
			mes "アリーナポイントの使用に関しては";
			mes "^3131FFアリーナポイントって？^000000で説明させて";
			mes "いただいておりますので、そちらを";
			mes "ご参考ください。";
			break;
		case 4:
			mes "[ベンデゴス]";
			mes "それでは楽しい一時をお過ごし";
			mes "下さいませ。";
			close;
		}
		next;
		mes "[ベンデゴス]";
		mes "他になにかございますか？";
	}
}

arena_room.gat,105,82,2	script	アリーナ記録担当	57,{
	mes "[アウェンキープ]";
	mes "こんにちは。";
	mes "アリーナの記録を管理している";
	mes "アウェンキープです。";
	next;
	mes "[アウェンキープ]";
	mes "各セクションで最短時間を記録した";
	mes "勇士の名前を知りたいのですか？";
	mes "ご希望のセクションを教えてください。";
	next;
	setarray '@sect$,"個人戦LV50～69","個人戦LV60～79","個人戦LV70～89","個人戦LV80～99","パーティー戦";
	set '@i,select('@sect$[0],'@sect$[1],'@sect$[2],'@sect$[3],'@sect$[4])-1;
	mes "[アウェンキープ]";
	mes "現在、" +'@sect$['@i]+ "は";
	mes "^3131FF" +$ArenaName$['@i]+ "^000000様が";
	mes "1位です。記録は";
	mes "^3131FF" +$ArenaTime['@i]/60000+"^000000分^3131FF"+$ArenaTime['@i]%60000/1000+"^000000秒です。";
	close;
}

arena_room.gat,105,93,2	script	(株)闇転送	55,{
	mes "[(株)闇転送]";
	mes "アリーナじゃない空間に行くかい？";
	next;
	if(select("行く","行かない")==1) {
		mes "[(株)闇転送]";
		mes "じゃあついてきな。";
		close2;
		warp "prt_are_in.gat",60,14;
		end;
	}
	mes "[(株)闇転送]";
	mes "気が向いたらまたおいで。";
	close;
}

prt_are_in.gat,98,14,3	script	ギブ#arena	728,{
	//写真撮影するNPC名を返す
	function PhotoName {
		switch(getarg(0)) {
			case 0: return "バフォメット";
			case 1: return "ダークロード";
			case 2: return "ドッペルゲンガー";
			case 3: return "エドガ";
			case 4: return "ドラキュラ";
			case 5: return "怨霊武士";
			case 6: return "ストームナイト";
			case 7: return "フリオニ";
			case 8: return "女の子";
			case 9: return "ヴァルキリー";
		}
	}

	//タイマーカウンタに応じたエモーション番号を返す
	function EmotionNumber {
		switch(getarg(0)) {
			case 0: return 3;
			case 1: return 10;
			case 2: return 21;
			case 3: return 23;
			case 4: return 29;
			case 5: return 30;
		}
	}

	mes "[ギブ]";
	mes "こんにちは。";
	mes "私が、アリーナポイントの交換を";
	mes "担当しているギブです。";
	next;
	mes "[ギブ]";
	mes "こちらでは、あなたが取得したアリーナ";
	mes "ポイントをアイテムなどと交換する";
	mes "ことが出来ます。";
	mes "どのサービスをご希望しますか？";
	next;
	switch (select("景品と交換","経験値と交換","写真撮影したい","アリーナポイントを確認")) {
	case 1:
		mes "[ギブ]";
		mes "どの景品と交換しますか？";
		next;
		switch (select("ハチ蜜","ローヤルゼリー","マステラの実","ホワイトスリムポーション","アンティペインメント",
						"イグドラシルの種","イグドラシルの実","アリーナコイン","古く青い箱","古い紫色の箱","古いカード帖")) {
			case 1:
				set '@point,20;
				set '@amount,5;
				set '@itemid,518;
				break;
			case 2:
				set '@point,30;
				set '@amount,5;
				set '@itemid,526;
				break;
			case 3:
				set '@point,30;
				set '@amount,5;
				set '@itemid,522;
				break;
			case 4:
				set '@point,30;
				set '@amount,8;
				set '@itemid,547;
				break;
			case 5:
				set '@point,20;
				set '@amount,3;
				set '@itemid,605;
				break;
			case 6:
				set '@point,20;
				set '@amount,1;
				set '@itemid,608;
				break;
			case 7:
				set '@point,40;
				set '@amount,1;
				set '@itemid,607;
				break;
			case 8:
				set '@point,60;
				set '@amount,1;
				set '@itemid,6365;
				break;
			case 9:
				set '@point,100;
				set '@amount,1;
				set '@itemid,603;
				break;
			case 10:
				set '@point,300;
				set '@amount,1;
				set '@itemid,617;
				break;
			case 11:
				set '@point,1000;
				set '@amount,1;
				set '@itemid,616;
				break;
		}
		mes "[ギブ]";
		mes "アリーナポイントを" +getitemname('@itemid)+ "に";
		mes "交換ですね。交換レートは";
		mes "^3131FF" +'@point+ "ポイント＝" +getitemname('@itemid) + '@amount+ "個^000000です。";
		mes "取り消す時は0を、そうでなければ";
		mes "^3131FF何回分^000000交換するか教えてください。";
		next;
		input '@num;
		if('@num==0) {
			mes "[ギブ]";
			mes "取り消しました。";
			close;
		}
		if('@num<0) {
			mes "[ギブ]";
			mes "数が正しくないようです。";
			close;
		}
		if(ARENA_PIT < '@point*'@num) {
			mes "[ギブ]";
			mes "アリーナポイントが不足しています。";
			mes "所有ポイント数を確認してください。";
			close;
		}
		getitem '@itemid,'@num*'@amount;
		set ARENA_PIT,ARENA_PIT - '@point*'@num;
		mes "[ギブ]";
		mes "ご利用、ありがとうございました。";
		close;
	case 2:
		mes "[ギブ]";
		mes "アリーナポイントを経験値に";
		mes "換算ですね。換算には";
		mes "40ポイントが必要となります。";
		next;
		if(select("しない","する")==1) {
			mes "[ギブ]";
			mes "取り消しました。";
			close;
		}
		if(ARENA_PIT < 40) {
			mes "[ギブ]";
			mes "アリーナポイントが不足しています。";
			mes "所有ポイント数を確認してください。";
			close;
		}
		if(BaseLevel >= 90) 			getexp 30000,0;
		if(BaseLevel >= 80 && BaseLevel < 90) 	getexp 10000,0;
		if(BaseLevel >= 70 && BaseLevel < 80) 	getexp 9000,0;
		if(BaseLevel < 70) 			getexp 3000,0;
		set ARENA_PIT,ARENA_PIT-40;
		mes "[ギブ]";
		mes "アリーナポイントを経験値に";
		mes "換算いたしました。";
		close;
	case 3:
		mes "[ギブ]";
		mes "写真撮影をご希望ですね。";
		next;
		if(select("写真撮影って？","写真撮影する")==1) {
			mes "[ギブ]";
			mes "私の右に階段があるのが見えますか？";
			next;
			mes "[ギブ]";
			mes "あの階段に、ご希望のNPCをお呼び";
			mes "しますので、1分間、ご自由に";
			mes "スクリーンショット機能を使って";
			mes "撮影を楽しんでください。";
			next;
			mes "[ギブ]";
			mes "撮影中、NPCもエモーションを出して";
			mes "くれますので、是非タイミングを";
			mes "合わせ記念撮影してみてください。";
			close;
		}
		if('flag) {
			mes "[ギブ]";
			mes "写真撮影中です。少々お待ちください。";
			close;
		}
		mes "[ギブ]";
		mes "一緒に撮影したいNPCを選択ください。";
		mes "NPCを1分間呼び出すのに、10アリーナ";
		mes "ポイントが必要となります。";
		next;
		set '@i,select("バフォメット","ダークロード","ドッペルゲンガー","エドガ","ドラキュラ",
							"怨霊武士","ストームナイト","フリオニ","女の子","ヴァルキリー")-1;
		mes "[ギブ]";
		if(ARENA_PIT < 10) {
			mes "アリーナポイントが不足しています。";
			mes "所有ポイント数を確認してください。";
			close;
		}
		if('@i==8)
			mes "可愛い女の子達をお呼びしますか？";
		else
			mes PhotoName('@i)+ "をお呼びしますか？";
		next;
		if(select("うん","やめておく")==2) {
			mes "[ギブ]";
			mes "もう少しお考えになりますか？";
			close;
		}
		if('flag) {	//もう1回重複チェック
			mes "[ギブ]";
			mes "写真撮影中です。少々お待ちください。";
			close;
		}
		set ARENA_PIT,ARENA_PIT-10;
		set 'flag,1;
		set 'i,'@i;	//写真撮影可能なら選択番号をスクリプト依存変数へ移し替え！
		if('@i==8) {
			hideoffnpc "女の子#arena1";
			hideoffnpc "女の子#arena2";
			hideoffnpc "女の子#arena3";
			hideoffnpc "女の子#arena4";
		}
		else
			hideoffnpc PhotoName('@i)+ "#arena";
		set 'count,0;
		donpcevent "ギブ#arena::OnStart";	//スクリプト依存変数に頼るのでこのNPC内部で全部処理する！
		mes "[ギブ]";
		if('@i==8)
			mes "可愛い女の子達をお呼びしました。";
		else
			mes PhotoName('@i)+ "をお呼びしました。";
		close;
	case 4:
		mes "[ギブ]";
		mes strcharinfo(0)+ "様の";
		mes "アリーナポイントを確認いたします。";
		next;
		mes "[ギブ]";
		mes strcharinfo(0)+ "様の";
		mes "アリーナポイントは";
		mes "^3131FF" +ARENA_PIT+ "^000000点です";
		close;
	}
OnStart:
	sleep 2000;
	announce "ギブ : タイミングを合わせてエモーションを出してくださ～い",9,0xFFCE00;
	initnpctimer;
	end;
OnTimer5000:
	switch('count) {	//タイマーループカウンタ
	case 0:
		announce "エモーション : /ハート でお願いします",9,0xFFCE00;
		break;
	case 1:
		announce "エモーション : チョキ(CTRL+－) でお願いします",9,0xFFCE00;
		break;
	case 2:
		announce "エモーション : /最高 でお願いします",9,0xFFCE00;
		break;
	case 3:
		announce "エモーション : /ショックでお願いします",9,0xFFCE00;
		break;
	case 4:
		announce "エモーション : /くすくす でお願いします",9,0xFFCE00;
		break;
	case 5:
		announce "エモーション : /ちゅ でお願いします",9,0xFFCE00;
		break;
	case 6:
		announce "写真撮影終了です。ご利用ありがとうございました。",9,0xFFCE00;
		if('i==8) {
			hideonnpc "女の子#arena1";
			hideonnpc "女の子#arena2";
			hideonnpc "女の子#arena3";
			hideonnpc "女の子#arena4";
		}
		else
			hideonnpc PhotoName('i)+"#arena";
		set 'flag,0;
		stopnpctimer;
		break;
	}
	end;
OnTimer7000:
	announce "3",9,0xFFCE00;
	sleep 1000;
	announce "2",9,0xFFCE00;
	sleep 1000;
	announce "1",9,0xFFCE00;
	sleep 1000;
	//ループ回数'count毎にエモーション変わる
	if('i==8) {
		emotion EmotionNumber('count),"女の子#arena1";
		emotion EmotionNumber('count),"女の子#arena2";
		emotion EmotionNumber('count),"女の子#arena3";
		emotion EmotionNumber('count),"女の子#arena4";
	}
	else
		emotion EmotionNumber('count),PhotoName('i)+"#arena";
	set 'count,'count+1;
	initnpctimer;	//再始動
	end;
OnInit:
	for(set '@j,0; '@j<10; set '@j,'@j+1) {
		if('@j==8) {
			hideonnpc "女の子#arena1";
			hideonnpc "女の子#arena2";
			hideonnpc "女の子#arena3";
			hideonnpc "女の子#arena4";
		}
		else
			hideonnpc PhotoName('@j)+"#arena";
	}
	end;
}

prt_are_in.gat,96,28,4	script	バフォメット#arena	736,{}
prt_are_in.gat,96,28,4	script	ダークロード#arena	737,{}
prt_are_in.gat,96,28,4	script	ドッペルゲンガー#arena	739,{}
prt_are_in.gat,96,28,4	script	エドガ#arena		1115,{}
prt_are_in.gat,96,28,4	script	ドラキュラ#arena	1389,{}
prt_are_in.gat,96,28,4	script	怨霊武士#arena		1492,{}
prt_are_in.gat,96,28,4	script	ストームナイト#arena	1251,{}
prt_are_in.gat,96,28,4	script	フリオニ#arena		1159,{}
prt_are_in.gat,94,26,4	script	女の子#arena1		714,{}
prt_are_in.gat,96,28,4	script	女の子#arena2		714,{}
prt_are_in.gat,100,28,4	script	女の子#arena3		714,{}
prt_are_in.gat,102,26,4	script	女の子#arena4		714,{}
prt_are_in.gat,96,28,4	script	ヴァルキリー#arena	811,{}


prt_are_in.gat,103,11,3	script	ポイント管理人	732,{
	mes "[アリーナポイントガイド]";
	mes "お楽しみいただけましたでしょうか？";
	mes "こちらでは……";
	mes "アルデバランの^3131FFターボトラック^000000と";
	mes "イズルードの^FF0000タイムバトルアリーナ^000000の";
	mes "ポイントを交換することができます。";
	mes "何をお望みですか？";
	next;
	set @menu,select("ポイントの確認","アリーナポイントとの交換");
	mes "[アリーナポイントガイド]";
	mes strcharinfo(0)+ "様の";
	mes "ポイントは次の通りです。";
	mes "ターボトラックポイント：" +TURBO_PIT+ "点";
	mes "アリーナポイント：" +ARENA_PIT+ "点";
	next;
	mes "[アリーナポイントガイド]";
	mes "ターボトラックポイントを";
	mes "アリーナポイントに";
	mes "交換することはできます。";
	if(@menu==1) {
		mes "ポイント利用のご参考に";
		mes "していただければと思います。";
		close;
	}
	next;
	mes "[アリーナポイントガイド]";
	mes "その際の交換比率は";
	mes "「ターボトラック：アリーナ＝２:１」";
	mes "となります。つまり……";
	mes "10点のターボトラックポイントは";
	mes "5点のアリーナポイントに";
	mes "交換することができます。";
	next;
	mes "[アリーナポイントガイド]";
	mes "交換方法をお選びください。但し、";
	mes "10点以上のポイント交換に関しては";
	mes "^4A4AFF10点単位の交換数……";
	mes "つまり、倍数^000000を入力してください。";
	next;
	switch (select("ターボトラック 2点 -> アリーナ 1点","ターボトラック 4点 -> アリーナ 2点","ターボトラック 6点 -> アリーナ 3点",
							"ターボトラック 8点 -> アリーナ 4点","ターボトラック 10点単位で交換","取り消し")) {
	default:
		set '@point,@menu*2;
		break;
	case 5:
		mes "[アリーナポイントガイド]";
		mes "ターボトラックポイントを";
		mes "アリーナポイントに";
		mes "^4A4AFF10点単位で交換^000000します。";
		mes "^4A4AFF一度に交換できる";
		mes "ターボトラックポイントは";
		mes "10点の20倍、200点まで^000000です。";
		next;
		mes "[アリーナポイントガイド]";
		mes "では、ターボトラックポイントを";
		mes "10点の何倍、アリーナポイントに";
		mes "交換するかを入力してください。";
		mes "取り消す場合は「0」を";
		mes "入力してください。";
		next;
		input '@num;
		if('@num == 0) {
			mes "[アリーナポイントガイド]";
			mes "取り消しました。";
			close;
		}
		if('@num<0 || '@num>20) {
			mes "[アリーナポイントガイド]";
			mes "交換可能範囲を超えています。";
			mes "一度に交換できる";
			mes "ターボトラックポイントは";
			mes "10点の20倍までです。";
			close;
		}
		set '@point,'@num*10;
		break;
	case 6:
		mes "[アリーナポイントガイド]";
		mes "取り消しました。";
		close;
	}
	if(TURBO_PIT < '@point) {
		mes "[アリーナポイントガイド]";
		mes "ターボトラックポイントが";
		mes "足りません。";
		mes "ターボトラックポイントは、";
		mes '@point+ "点以上必要です。";
		mes "ターボトラックポイントを";
		mes "再度ご確認ください。";
		close;
	}
	set ARENA_PIT,ARENA_PIT+'@point/2;
	set TURBO_PIT,TURBO_PIT-'@point;
	mes "[アリーナポイントガイド]";
	mes strcharinfo(0)+ "様の";
	mes "ターボトラックポイント" +'@point+ "点を";
	mes "アリーナポイント" +'@point/2+ "点に";
	mes "交換しました。";
	next;
	mes "[アリーナポイントガイド]";
	mes strcharinfo(0)+ "様の";
	mes "ポイントは次の通りになります。";
	mes "ターボトラックポイント：" +TURBO_PIT+ "点";
	mes "アリーナポイント：" +ARENA_PIT+ "点";
	mes "ご利用頂きありがとうございました。";
	close;
}


//==============================================================
// Function
//callfunc "ArenaAnnounce","ArenaSection",LimitTime;
function	script	ArenaAnnounce	{
	sleep 2000;
	announce strnpcinfo(1)+ ": こんにちは。タイムアタックバトル、" +getarg(0)+ "セクション司会者、" +strnpcinfo(1)+ "です！",9;
	sleep 1000;
	announce strnpcinfo(1)+ ": 時間をどう節約するかが勝敗のコツです。慎重に！",9;
	sleep 1000;
	announce strnpcinfo(1)+ ": ゴールへは時計回りに進んでください。まず、左側の入口から開始します。制限時間は" +getarg(1)+ "分間です。では、GOOD LUCK!!",9;
	return;
}

//callfunc "ArenaKilled",LvNumber,NextStage,"NpcName",'mob;
function	script	ArenaKilled	{
	set getarg(3),getarg(3)-1;	//'mobカウンタを1減らす
	if(getarg(3) <= 0) {
		killmonsterall "this";
		enablenpc "Arena"+getarg(0)+"warp#"+getarg(1);
		switch(getarg(1)) {
		case 2:
		case 3:
			announce getarg(2)+ ": 北部屋のドアが開きました！",9;
			break;
		case 4:
			announce getarg(2)+ ": クリア！東部屋のドアが開きました！",9;
			break;
		case 5:
			announce getarg(2)+ ": 東部屋のドアが開きました！",9;
			break;
		case 6:
			announce getarg(2)+ ": クリア！南部屋のドアが開きました！",9;
			break;
		case 7:
			announce getarg(2)+ ": 南部屋のドアが開きました！",9;
			break;
		case 8:
			announce getarg(2)+ ": クリア！西部屋のドアが開きました！",9;
			break;
		case 10:
			announce getarg(2)+ ": クリア!! 北出口が開きました。お疲れ様でした！",9;
			break;
		}
	}
	return;
}

//callfunc "ArenaClear",ArenaLevel,RoomNumber,"ArenaSection";
function	script	ArenaClear	{
	mes "[進行要員]";
	mes "お疲れ様でした。";
	mes "お名前は……";
	mes "^3131FF" +strcharinfo(0)+ "^000000様ですね？";
	mes "^3131FF" +strcharinfo(0)+ "^000000様が";
	mes "アリーナをクリアするのにかかった";
	mes "時間は……";
	next;
	mes "[進行要員]";
	set '@time,getvariableofnpc('time,"ArenaStage"+getarg(0));
	mes '@time/60000+ "分" +'@time%60000/1000+ "秒です！";
	if('@time <= $ArenaTime[getarg(0)] || $ArenaTime[getarg(0)] == 0) {	//最高記録樹立
		next;
		mes "[進行要員]";
		mes "ウオオッ!!　新記録ーーー!!";
		mes "おめでとうございます!!!!";
		next;
		mes "[進行要員]";
		mes "^FF0000タイムアタック";
		mes getarg(2)+ "セクション^000000にあなたの";
		mes "名前^3131FF" +strcharinfo(0)+ "^000000を";
		mes "記録いたします。";
		next;
		mes "[進行要員]";
		mes "アリーナの記録の確認は";
		mes "アリーナ控室の^3131FFアウェンキープ^000000に";
		mes "お問い合わせください。";
		next;
		mes "[進行要員]";
		mes "それではアリーナポイントを";
		mes "支給いたします。新記録達成";
		mes "ですので、ボーナスポイントも";
		mes "支給いたします。";
		next;
		mes "[進行要員]";
		mes "それでは、入口にお送りしましょう。";
		mes "お疲れさまでした～。またの";
		mes "お越しをお待ちしております。";
		close2;
		set $ArenaName$[getarg(0)],strcharinfo(0);
		set $ArenaTime[getarg(0)],'@time;
		set ARENA_PIT,ARENA_PIT+60;
	}
	else {
		mes "おめでとうございます!!";
		next;
		mes "[進行要員]";
		mes "現在、タイムアタック";
		mes getarg(2)+ "セクションを一番早く";
		mes "クリアした人は……";
		mes "^3131FF" +$ArenaName$[getarg(0)]+ "^000000様です。";
		next;
		mes "[進行要員]";
		mes "^3131FF" +$ArenaName$[getarg(0)]+ "^000000様の";
		mes "タイムは^3131FF" +$ArenaTime[getarg(0)]/60000+ "^000000分^3131FF" +$ArenaTime[getarg(0)]%60000/1000+ "^000000秒です。";
		next;
		mes "[進行要員]";
		mes "記録更新は成せませんでしたが、";
		mes "次の機会には是非成功させてください。";
		next;
		mes "[進行要員]";
		mes "それでは、アリーナポイントを";
		mes "支給いたします。";
		mes "アリーナポイントの確認は";
		mes "アリーナ控室の^3131FFベンデゴス^000000に";
		mes "お問い合わせください。";
		next;
		mes "[進行要員]";
		mes "それでは、入口にお送りしましょう。";
		mes "お疲れさまでした～。またの";
		mes "お越しをお待ちしております。";
		close2;
		set ARENA_PIT,ARENA_PIT+20;
	}
	stopnpctimer "ArenaStage" +getarg(0);
	enablewaitingroomevent "[LV " +getarg(1)+ "]控室#arena";
	warp "arena_room.gat",100,75;
	return;
}


//==============================================================================
// 個人戦 LV50～69
//==============================================================================
arena_room.gat,68,135,3	script	コンパニオン ペツ	726,{
	mes "[ペツ]";
	mes "こんにちは～";
	mes "個人戦LV50～69セクションの";
	mes "コンパニオン、ペツです。";
	next;
	mes "[ペツ]";
	mes "^3131FF個人戦LV50～69^000000セクションは";
	mes "^FF0000レベル50^000000から^FF0000レベル69^000000まで入場";
	mes "できます。";
	next;
	mes "[ペツ]";
	mes "高レベルプレイヤーが自分よりレベルの";
	mes "低いアリーナでランキング獲得するのを";
	mes "防止するため、制限を設けております。";
	next;
	mes "[ペツ]";
	mes "個人戦参加料は1000zです。";
	next;
	mes "[ペツ]";
	mes "それでは、アリーナ進行方法に関して";
	mes "ご案内いたします。";
	next;
	mes "[ペツ]";
	mes "参加控室となる^3131FFチャットルームの中で";
	mes "自分の順番をお待ちください。^000000";
	mes "自分の順になればアリーナ内へ自動的に";
	mes "移動となります。";
	next;
	mes "[ペツ]";
	mes "アリーナ入場と同時にカウントダウンが";
	mes "始まります。";
	mes "^3131FFヒルト^000000がクリア条件を出題しますので";
	mes "条件に従ってクリアを目指して下さい";
	next;
	mes "[ペツ]";
	mes "持ち時間は^3131FF5分^000000ですので慌てず";
	mes "かつ迅速に行動することをお勧め";
	mes "いたします。";
	next;
	mes "[ペツ]";
	mes "最後のボスルームをクリアすれば";
	mes "^3131FF終了控室^000000に移動となります。";
	mes "^3131FF終了控室^000000には1分しか居られませんので";
	mes "担当者からアリーナポイントをいただい";
	mes "て素早く外に出てください。";
	next;
	mes "[ペツ]";
	mes "終了控室でアリーナポイントを受け取る";
	mes "ことができなかった場合、アリーナ";
	mes "ポイントの補償は行っておりませんので";
	mes "くれぐれもご注意ください！";
	next;
	mes "[ペツ]";
	mes "以上、個人戦LV50～69についてでした。";
	mes "是非アリーナにご参加くださいませ～。";
	close;
}

arena_room.gat,64,138,5	script	[LV 50]控室#arena	124,{
	end;
OnInit:
	waitingroom "個人戦 LV50～69",20,"[LV 50]控室#arena::OnStart",1,1000,50,69;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		if(Zeny >= 1000) {
			set Zeny,Zeny-1000;
			killmonsterall "force_1-1.gat";
			donpcevent "ヒルト#arena::OnStart";
			warp "force_1-1.gat",100,12;
			end;
		}
		kickwaitingroom '@accid;
	}
	enablewaitingroomevent;
	end;
}

force_1-1.gat,99,20,3	script	ヒルト#arena	124,{
	end;
OnStart:
	set 'count,5;
	enablenpc "Arena0warp#1";
	disablenpc "Arena0warp#9";
	initnpctimer;
	callfunc "ArenaAnnounce","LV50～69",5;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
OnTimer300000:
	set 'count,'count-1;
	if('count)
		announce "ヒルト: 残り時間 : " +'count+ " 分",9;
	else
		announce "ヒルト: 時間切れです。残念！",9;
	end;
OnTimer305000:
	stopnpctimer;
	areawarp "force_1-1.gat",0,0,200,200,"prt_are_in.gat",126,192;
	enablewaitingroomevent "[LV 50]控室#arena";
	end;
}

force_1-1.gat,0,0,0	script	ArenaStage0	-1,{
OnSummon1:
	set 'mob,5;
	disablenpc "Arena0warp#2";
	monster "force_1-1.gat",25,25,"スモーキー",1561,1,"ArenaStage0::OnKilled1";
	monster "force_1-1.gat",18,25,"スモーキー",1561,1,"ArenaStage0::OnKilled1";
	monster "force_1-1.gat",32,25,"スモーキー",1561,1,"ArenaStage0::OnKilled1";
	monster "force_1-1.gat",25,32,"スモーキー",1561,1,"ArenaStage0::OnKilled1";
	monster "force_1-1.gat",25,18,"スモーキー",1561,1,"ArenaStage0::OnKilled1";
	monster "force_1-1.gat",25,26,"ドロップス",1572,1;
	monster "force_1-1.gat",15,25,"ドロップス",1572,1;
	monster "force_1-1.gat",30,25,"ドロップス",1572,1;
	monster "force_1-1.gat",25,31,"ドロップス",1572,1;
	monster "force_1-1.gat",24,19,"ドロップス",1572,1;
	monster "force_1-1.gat",25,28,"ドロップス",1572,1;
	monster "force_1-1.gat",18,23,"ドロップス",1572,1;
	monster "force_1-1.gat",24,25,"ドロップス",1572,1;
	monster "force_1-1.gat",23,18,"ドロップス",1572,1;
	monster "force_1-1.gat",20,18,"ドロップス",1572,1;
	monster "force_1-1.gat",35,31,"ヒドラ",1579,1;
	monster "force_1-1.gat",35,28,"ヒドラ",1579,1;
	monster "force_1-1.gat",35,25,"ヒドラ",1579,1;
	monster "force_1-1.gat",35,21,"ヒドラ",1579,1;
	monster "force_1-1.gat",26,16,"大口蛙",1556,1;
	monster "force_1-1.gat",26,15,"大口蛙",1556,1;
	monster "force_1-1.gat",26,14,"大口蛙",1556,1;
	monster "force_1-1.gat",23,17,"大口蛙",1556,1;
	monster "force_1-1.gat",23,18,"大口蛙",1556,1;
	monster "force_1-1.gat",23,19,"大口蛙",1556,1;
	monster "force_1-1.gat",29,20,"大口蛙",1556,1;
	monster "force_1-1.gat",23,16,"大口蛙",1556,1;
	monster "force_1-1.gat",19,16,"大口蛙",1556,1;
	monster "force_1-1.gat",32,19,"大口蛙",1556,1;
	sleep 500;
	announce "ヒルト: クリア条件 : スモーキーを全て退治してください",9;
	end;
OnKilled1:
	callfunc "ArenaKilled",0,2,"ヒルト",'mob;
	end;
OnSummon2:
	monster "force_1-1.gat",24,76,"ファミリアー",1419,1;
	monster "force_1-1.gat",28,76,"ファミリアー",1419,1;
	monster "force_1-1.gat",24,86,"ファミリアー",1419,1;
	monster "force_1-1.gat",26,86,"グール",1423,1;
	monster "force_1-1.gat",25,100,"グール",1423,1;
	monster "force_1-1.gat",26,118,"グール",1423,1;
	monster "force_1-1.gat",28,79,"マミー",1393,1;
	monster "force_1-1.gat",23,87,"マミー",1393,1;
	monster "force_1-1.gat",28,99,"マミー",1393,1;
	monster "force_1-1.gat",23,112,"マミー",1393,1;
	monster "force_1-1.gat",28,128,"マミー",1393,1;
	sleep 500;
	announce "ヒルト: クリア条件 : モンスターを避けて北出口から脱出してください！",9;
	end;
OnSummon3:
	set 'mob,5;
	disablenpc "Arena0warp#4";
	monster "force_1-1.gat",23,174,"カラ傘",1544,1,"ArenaStage0::OnKilled3";
	monster "force_1-1.gat",18,173,"カラ傘",1544,1,"ArenaStage0::OnKilled3";
	monster "force_1-1.gat",33,173,"カラ傘",1544,1,"ArenaStage0::OnKilled3";
	monster "force_1-1.gat",26,181,"カラ傘",1544,1,"ArenaStage0::OnKilled3";
	monster "force_1-1.gat",26,166,"カラ傘",1544,1,"ArenaStage0::OnKilled3";
	monster "force_1-1.gat",26,173,"ヒドラ",1579,1;
	monster "force_1-1.gat",21,173,"ヒドラ",1579,1;
	monster "force_1-1.gat",31,173,"ヒドラ",1579,1;
	monster "force_1-1.gat",26,186,"マルス",1551,1;
	monster "force_1-1.gat",26,161,"マルス",1551,1;
	monster "force_1-1.gat",13,173,"マルス",1551,1;
	monster "force_1-1.gat",38,173,"マルス",1551,1;
	monster "force_1-1.gat",29,174,"マルス",1551,1;
	sleep 500;
	announce "ヒルト: クリア条件 : カラ傘を全て退治してください",9;
	end;
OnKilled3:
	callfunc "ArenaKilled",0,4,"ヒルト",'mob;
	end;
OnSummon4:
	set 'mob,3;
	disablenpc "Arena0warp#5";
	monster "force_1-1.gat",85,172,"コボルド",1546,1,"ArenaStage0::OnKilled4";
	monster "force_1-1.gat",95,172,"コボルド",1546,1,"ArenaStage0::OnKilled4";
	monster "force_1-1.gat",120,172,"コボルド",1545,1,"ArenaStage0::OnKilled4";
	monster "force_1-1.gat",99,174,"ファミリアー",1419,1;
	monster "force_1-1.gat",103,174,"ファミリアー",1419,1;
	monster "force_1-1.gat",107,174,"ファミリアー",1419,1;
	monster "force_1-1.gat",111,176,"ファミリアー",1419,1;
	monster "force_1-1.gat",115,176,"ファミリアー",1419,1;
	monster "force_1-1.gat",119,172,"ファミリアー",1419,1;
	monster "force_1-1.gat",95,178,"ファミリアー",1419,1;
	monster "force_1-1.gat",100,178,"ファミリアー",1419,1;
	monster "force_1-1.gat",105,172,"ファミリアー",1419,1;
	monster "force_1-1.gat",110,172,"フローラ",1575,1;
	monster "force_1-1.gat",115,172,"フローラ",1575,1;
	monster "force_1-1.gat",120,172,"フローラ",1575,1;
	monster "force_1-1.gat",125,172,"フローラ",1575,1;
	monster "force_1-1.gat",105,178,"フローラ",1575,1;
	sleep 500;
	announce "ヒルト: クリア条件 : コボルドを全て退治してください",9;
	end;
OnKilled4:
	callfunc "ArenaKilled",0,5,"ヒルト",'mob;
	end;
OnSummon5:
	set 'mob,6;
	disablenpc "Arena0warp#6";
	monster "force_1-1.gat",173,166,"ヒドラ",1579,1,"ArenaStage0::OnKilled5";
	monster "force_1-1.gat",171,170,"ヒドラ",1579,1,"ArenaStage0::OnKilled5";
	monster "force_1-1.gat",177,170,"ヒドラ",1579,1,"ArenaStage0::OnKilled5";
	monster "force_1-1.gat",183,173,"オークレディ",1452,1,"ArenaStage0::OnKilled5";
	monster "force_1-1.gat",173,173,"オークレディ",1452,1,"ArenaStage0::OnKilled5";
	monster "force_1-1.gat",181,173,"ゴーレム",1540,1,"ArenaStage0::OnKilled5";
//	monster "force_1-1.gat",171,177,"ゴーレム",1540,1,"ArenaStage0::OnKilled5";
	sleep 500;
	announce "ヒルト: クリア条件 : 最初からいるモンスターを全て退治してください",9;
	end;
OnKilled5:
	if(rand(2))
		monster "force_1-1.gat",174,174,"デザートウルフ",1432,1;
	else
		monster "force_1-1.gat",173,173,"ゼロム",1470,1;
	callfunc "ArenaKilled",0,6,"ヒルト",'mob;
	end;
OnSummon6:
	set 'mob,5;
	disablenpc "Arena0warp#7";
	monster "force_1-1.gat",173,90,"ドロップス",1572,1,"ArenaStage0::OnKilled6";
	monster "force_1-1.gat",173,79,"ドロップス",1572,1,"ArenaStage0::OnKilled6";
	monster "force_1-1.gat",172,70,"ドロップス",1572,1,"ArenaStage0::OnKilled6";
	monster "force_1-1.gat",175,70,"ドロップス",1572,1,"ArenaStage0::OnKilled6";
	monster "force_1-1.gat",171,118,"ドロップス",1572,1,"ArenaStage0::OnKilled6";
	monster "force_1-1.gat",173,118,"スモーキー",1561,1;
	monster "force_1-1.gat",173,108,"スモーキー",1561,1;
	monster "force_1-1.gat",173,99,"スモーキー",1561,1;
	monster "force_1-1.gat",171,108,"ゴーレム",1540,1;
	monster "force_1-1.gat",171,99,"スケルワーカー",1469,1;
	monster "force_1-1.gat",171,85,"スケルワーカー",1469,1;
	monster "force_1-1.gat",171,90,"ゴーレム",1540,1;
	monster "force_1-1.gat",171,79,"スコーピオン",1559,1;
	monster "force_1-1.gat",175,118,"スコーピオン",1559,1;
	monster "force_1-1.gat",175,108,"サンドマン",1558,1;
	monster "force_1-1.gat",175,99,"サンドマン",1558,1;
	sleep 500;
	announce "ヒルト: クリア条件 : ドロップスを全て退治してください",9;
	end;
OnKilled6:
	callfunc "ArenaKilled",0,7,"ヒルト",'mob;
	end;
OnSummon7:
	set 'mob,1;
	disablenpc "Arena0warp#8";
	monster "force_1-1.gat",174,25,"赤い草",1078,1,"ArenaStage0::OnKilled7";
	monster "force_1-1.gat",163,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",167,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",171,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",175,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",179,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,36,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,32,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,28,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,24,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,20,"ヒドラ",1579,1;
	monster "force_1-1.gat",183,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",179,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",175,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",171,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",167,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,16,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,20,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,24,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,28,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,32,"ヒドラ",1579,1;
	monster "force_1-1.gat",163,31,"パンク",1481,1;
	monster "force_1-1.gat",163,23,"パンク",1481,1;
	sleep 500;
	announce "ヒルト: クリア条件 : ヒドラの攻撃を避けながら、中央の赤い草を駆除してください",9;
	end;
OnKilled7:
	callfunc "ArenaKilled",0,8,"ヒルト",'mob;
	end;
OnSummon8:
	disablenpc "Arena0warp#1";
	enablenpc "Arena0warp#9";
	sleep 500;
	announce "ヒルト: 北出口から脱出してください！",9;
	end;
OnSummon9:
	set 'mob,1;
	disablenpc "Arena0warp#10";
	monster "force_1-1.gat",99,99,"ボーカル",1581,1,"ArenaStage0::OnKilled9";
	monster "force_1-1.gat",110,110,"ファミリアー",1419,1;
	monster "force_1-1.gat",89,110,"ファミリアー",1419,1;
	monster "force_1-1.gat",89,89,"ファミリアー",1419,1;
	monster "force_1-1.gat",110,89,"ファミリアー",1419,1;
	monster "force_1-1.gat",105,105,"ファミリアー",1419,1;
	monster "force_1-1.gat",94,105,"ファミリアー",1419,1;
	monster "force_1-1.gat",94,94,"ファミリアー",1419,1;
	monster "force_1-1.gat",110,110,"ファミリアー",1419,1;
	monster "force_1-1.gat",89,110,"ファミリアー",1419,1;
	monster "force_1-1.gat",89,89,"ファミリアー",1419,1;
	monster "force_1-1.gat",110,89,"ファミリアー",1419,1;
	monster "force_1-1.gat",105,105,"ファミリアー",1419,1;
	monster "force_1-1.gat",94,105,"ファミリアー",1419,1;
	monster "force_1-1.gat",94,94,"ファミリアー",1419,1;
	monster "force_1-1.gat",105,94,"ファミリアー",1419,1;
	sleep 500;
	announce "ヒルト: クリア条件 : ボスモンスター、ボーカル出現！ボーカルを倒してください",9;
	end;
OnKilled9:
	callfunc "ArenaKilled",0,10,"ヒルト",'mob;
	if('mob <= 0)
		set 'time,getnpctimer(0,"ヒルト#arena");	//タイム記録
	end;
//クリア時の1分タイマー
OnTimer2000:
	mapannounce "prt_are_in.gat","タイムアタックLV50～69に関する案内放送です。",0,0xFFCE00;
	end;
OnTimer3000:
	mapannounce "prt_are_in.gat","円滑な進行のため、クリア後控室の滞在は1分とさせていただいています。",0,0xFFCE00;
	end;
OnTimer4000:
	mapannounce "prt_are_in.gat","アリーナポイントの受け取りは速やかにお済ませください。",0,0xFFCE00;
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "prt_are_in.gat",14,178,29,195,"arena_room",100,75;
	enablewaitingroomevent "[LV 50]控室#arena";
	end;
}

force_1-1.gat,62,25,0	script	Arena0warp#1	45,1,1,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "force_1-1.gat",40,26; 	break;
		case 2: warp "force_1-1.gat",25,69; 	break;
		case 3: warp "force_1-1.gat",25,159; 	break;
		case 4: warp "force_1-1.gat",69,174; 	break;
		case 5: warp "force_1-1.gat",159,174; 	break;
		case 6: warp "force_1-1.gat",174,130; 	break;
		case 7: warp "force_1-1.gat",174,40; 	break;
		case 8: warp "force_1-1.gat",132,26; 	break;
		case 9: warp "force_1-1.gat",99,86; 	break;
	}
	donpcevent "ArenaStage0::OnSummon"+'@num;
	end;
}

force_1-1.gat,25,44,0		duplicate(Arena0warp#1)		Arena0warp#2	45,1,1
force_1-1.gat,25,134,0		duplicate(Arena0warp#1)		Arena0warp#3	45,1,1
force_1-1.gat,44,173,0		duplicate(Arena0warp#1)		Arena0warp#4	45,1,1
force_1-1.gat,134,173,0		duplicate(Arena0warp#1)		Arena0warp#5	45,1,1
force_1-1.gat,174,155,0		duplicate(Arena0warp#1)		Arena0warp#6	45,1,1
force_1-1.gat,174,65,0		duplicate(Arena0warp#1)		Arena0warp#7	45,1,1
force_1-1.gat,155,26,0		duplicate(Arena0warp#1)		Arena0warp#8	45,1,1
force_1-1.gat,99,54,0		duplicate(Arena0warp#1)		Arena0warp#9	45,1,1

force_1-1.gat,99,123,0	script	Arena0warp#10	45,1,1,{
	stopnpctimer "ヒルト#arena";
	initnpctimer "ArenaStage0";
	warp "prt_are_in.gat",22,192;
	end;
}

prt_are_in.gat,25,187,3	script	進行要員	67,{
	callfunc "ArenaClear",0,50,"LV50～69";
	end;
}

//duplicate元としても使われる
prt_are_in.gat,129,187,3	script	進行要員#arenafailed	67,{
	mes "[進行要員]";
	mes "お疲れ様でした。";
	mes "タイムアタックは失敗でしたが、";
	mes "アリーナポイントを支給いたします。";
	next;
	mes "[進行要員]";
	mes "今日はお疲れ様でした。";
	mes "それでは、またのお越しを、";
	mes "お待ちしております。";
	close2;
	set ARENA_PIT,ARENA_PIT+1;
	warp "arena_room.gat",100,75;
	end;
}


//==============================================================================
// 個人戦 LV60～79
//==============================================================================
arena_room.gat,41,93,5	script	コンパニオン ベン	750,{
	mes "[ベン]";
	mes "ようこそ。";
	mes "個人戦LV60～79セクションの";
	mes "コンパニオン、ベンと申します。";
	next;
	mes "[ベン]";
	mes "^3131FF個人戦LV60～79^000000セクションは";
	mes "^FF0000レベル60^000000から^FF0000レベル79^000000まで入場";
	mes "可能となっております。";
	next;
	mes "[ベン]";
	mes "高レベルプレイヤーによる、低レベル";
	mes "アリーナでのランキング獲得防止のため";
	mes "レベル制限を設けております。";
	mes "ご了承くださいませ。";
	next;
	mes "[ベン]";
	mes "個人戦参加料は1000zです。";
	next;
	mes "[ベン]";
	mes "それでは、アリーナ進行方法に関して";
	mes "ご案内いたします。";
	next;
	mes "[ベン]";
	mes "参加控室となる^3131FFチャットルームの中で";
	mes "自分の順番をお待ちください。^000000";
	mes "自分の順になればアリーナ内へ自動的に";
	mes "移動となります。";
	next;
	mes "[ベン]";
	mes "アリーナ入場と同時にカウントダウンが";
	mes "開始いたします。";
	mes "司会担当の^3131FFミロ^000000がクリア条件を提示";
	mes "します。その条件に従ってクリアを目指";
	mes "して下さい。";
	next;
	mes "[ベン]";
	mes "持ち時間は^3131FF6分^000000です。";
	mes "トップスコアを狙うなら、時間調節が";
	mes "重要となります。";
	next;
	mes "[ベン]";
	mes "最後のボスルームをクリアすれば";
	mes "^3131FF終了控室^000000に移動となります。";
	mes "^3131FF終了控室^000000には1分しか居られませんので";
	mes "担当者からアリーナポイントをいただい";
	mes "て素早く外に出てください。";
	next;
	mes "[ベン]";
	mes "終了控室でアリーナポイントを受け取る";
	mes "ことができなかった場合、アリーナ";
	mes "ポイントの補償は行っておりません。";
	next;
	mes "[ベン]";
	mes "以上、個人戦LV60～79についての案内を";
	mes "終了いたします。アリーナ参加のご参";
	mes "考になれば幸いと存じます。";
	close;
}

arena_room.gat,38,87,6	script	[LV 60]控室#arena	124,{
	end;
OnInit:
	waitingroom "個人戦 LV60～79",20,"[LV 60]控室#arena::OnStart",1,1000,60,79;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		if(Zeny >= 1000) {
			set Zeny,Zeny-1000;
			killmonsterall "force_2-1.gat";
			donpcevent "ミロ#arena::OnStart";
			warp "force_2-1.gat",100,12;
			end;
		}
		kickwaitingroom '@accid;
	}
	enablewaitingroomevent;
	end;
}

force_2-1.gat,99,20,3	script	ミロ#arena	124,{
	end;
OnStart:
	set 'count,6;
	enablenpc "Arena1warp#1";
	disablenpc "Arena1warp#9";
	initnpctimer;
	callfunc "ArenaAnnounce","LV60～79",6;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
OnTimer300000:
OnTimer360000:
	set 'count,'count-1;
	if('count)
		announce "ミロ: 残り時間 : " +'count+ " 分",9;
	else
		announce "ミロ: 時間切れです。残念！",9;
	end;
OnTimer365000:
	stopnpctimer;
	areawarp "force_2-1.gat",0,0,200,200,"prt_are_in.gat",126,140;
	enablewaitingroomevent "[LV 60]控室#arena";
	end;
}

force_2-1.gat,0,0,0	script	ArenaStage1	-1,{
OnSummon1:
	set 'mob,5;
	disablenpc "Arena1warp#2";
	monster "force_2-1.gat",25,32,"ゴブリンアーチャー",1577,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",21,26,"ゴブリン",1534,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",25,36,"ゴブリン",1536,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",20,15,"ゴブリンアーチャー",1577,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",23,33,"ゴブリン",1537,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",25,15,"ゴブリン",1534,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",40,30,"ゴブリン",1536,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",20,23,"ゴブリン",1535,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",23,22,"ゴブリンアーチャー",1577,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",25,24,"ゴブリン",1534,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",25,9,"ゴブリン",1536,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",28,15,"ゴブリンアーチャー",1577,1,"ArenaStage1::OnKilled1";
//	monster "force_2-1.gat",25,16,"ゴブリン",1537,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",12,33,"ゴブリン",1536,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",24,20,"ゴブリン",1535,1,"ArenaStage1::OnKilled1";
	monster "force_2-1.gat",25,25,"ロータージャイロ",1557,1;
	sleep 500;
	announce "ミロ: クリア条件 : ロータージャイロを避けながら、ゴブリンを5体以上退治してください",9;
	end;
OnKilled1:
	callfunc "ArenaKilled",1,2,"ミロ",'mob;
	end;
OnSummon2:
	monster "force_2-1.gat",24,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",28,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",24,86,"ドレインリアー",1434,1;
	monster "force_2-1.gat",24,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",28,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",24,86,"ドレインリアー",1434,1;
	monster "force_2-1.gat",24,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",28,76,"ドレインリアー",1434,1;
	monster "force_2-1.gat",23,76,"レクイエム",1468,1;
	monster "force_2-1.gat",27,76,"レクイエム",1468,1;
	monster "force_2-1.gat",25,86,"レクイエム",1468,1;
	monster "force_2-1.gat",26,86,"グール",1423,1;
	monster "force_2-1.gat",25,100,"グール",1423,1;
	monster "force_2-1.gat",26,118,"グール",1423,1;
	monster "force_2-1.gat",25,100,"グール",1423,1;
	monster "force_2-1.gat",26,118,"グール",1423,1;
	monster "force_2-1.gat",28,79,"ゼロム",1470,1;
	monster "force_2-1.gat",23,87,"ゼロム",1470,1;
	monster "force_2-1.gat",28,99,"ゼロム",1470,1;
	monster "force_2-1.gat",23,112,"ゼロム",1470,1;
	monster "force_2-1.gat",28,128,"マーター",1460,1;
	monster "force_2-1.gat",28,128,"マーター",1460,1;
	monster "force_2-1.gat",28,128,"マーター",1460,1;
//	monster "force_2-1.gat",28,128,"マーター",1460,1;
	monster "force_2-1.gat",28,128,"オークゾンビ",1463,1;
	monster "force_2-1.gat",28,128,"オークゾンビ",1463,1;
	monster "force_2-1.gat",28,128,"オークゾンビ",1463,1;
	monster "force_2-1.gat",28,128,"オークゾンビ",1463,1;
	monster "force_2-1.gat",28,128,"オークゾンビ",1463,1;
	monster "force_2-1.gat",28,128,"マーター",1460,1;
	monster "force_2-1.gat",28,128,"マーター",1460,1;
	sleep 500;
	announce "ミロ: クリア条件 : モンスターを避けて北出口から脱出してください",9;
	end;
OnSummon3:
	set 'mob,4;
	disablenpc "Arena1warp#4";
	monster "force_2-1.gat",23,174,"マンティス",1457,1,"ArenaStage1::OnKilled3";
	monster "force_2-1.gat",18,173,"マンティス",1457,1,"ArenaStage1::OnKilled3";
	monster "force_2-1.gat",33,173,"マンティス",1457,1,"ArenaStage1::OnKilled3";
	monster "force_2-1.gat",26,181,"マンティス",1457,1,"ArenaStage1::OnKilled3";
//	monster "force_2-1.gat",26,166,"マンティス",1457,1,"ArenaStage1::OnKilled3";
	monster "force_2-1.gat",26,173,"ヒドラ",1579,1;
	monster "force_2-1.gat",21,173,"ヒドラ",1579,1;
	monster "force_2-1.gat",31,173,"ヒドラ",1579,1;
	monster "force_2-1.gat",26,178,"ヒドラ",1579,1;
	monster "force_2-1.gat",21,178,"ヒドラ",1579,1;
	monster "force_2-1.gat",31,178,"ヒドラ",1579,1;
	monster "force_2-1.gat",19,174,"オボンヌ",1425,1;
	monster "force_2-1.gat",26,161,"オボンヌ",1425,1;
	monster "force_2-1.gat",13,173,"オボンヌ",1425,1;
	monster "force_2-1.gat",38,173,"オボンヌ",1425,1;
//	monster "force_2-1.gat",19,174,"オボンヌ",1425,1;
	sleep 500;
	announce "ミロ: クリア条件 : マンティスを全て退治してください",9;
	end;
OnKilled3:
	callfunc "ArenaKilled",1,4,"ミロ",'mob;
	end;
OnSummon4:
	set 'mob,2;
	disablenpc "Arena1warp#5";
	monster "force_2-1.gat",79,174,"ゴーレム",1540,1,"ArenaStage1::OnKilled4";
	monster "force_2-1.gat",131,178,"マルス",1551,1,"ArenaStage1::OnKilled4";
	monster "force_2-1.gat",84,177,"サスカッチ",1442,1;
	monster "force_2-1.gat",125,170,"サスカッチ",1442,1;
	monster "force_2-1.gat",109,172,"コウ",1524,1;
	monster "force_2-1.gat",121,172,"コウ",1524,1;
	monster "force_2-1.gat",104,173,"チェペット",1444,1;
	monster "force_2-1.gat",75,174,"ドケビ",1491,1;
//	monster "force_2-1.gat",95,175,"ドケビ",1491,1;
	monster "force_2-1.gat",102,176,"ドケビ",1491,1;
	sleep 500;
	announce "ミロ: クリア条件 : アクティブモンスターを避けて非アクティブモンスターを全て退治してください",9;
	end;
OnKilled4:
	callfunc "ArenaKilled",1,5,"ミロ",'mob;
	end;
OnSummon5:
	set 'mob,5;
	disablenpc "Arena1warp#6";
	monster "force_2-1.gat",163,173,"ドレインリアー",1434,1,"ArenaStage1::OnKilled5";
	monster "force_2-1.gat",173,173,"ミスト",1553,1,"ArenaStage1::OnKilled5";
	monster "force_2-1.gat",181,173,"オークスケルトン",1462,1,"ArenaStage1::OnKilled5";
	monster "force_2-1.gat",171,177,"オークスケルトン",1462,1,"ArenaStage1::OnKilled5";
	monster "force_2-1.gat",173,181,"レグルロ",1445,1,"ArenaStage1::OnKilled5";
	monster "force_2-1.gat",168,177,"ヒドラ",1579,1;
	monster "force_2-1.gat",170,179,"ヒドラ",1579,1;
	monster "force_2-1.gat",177,179,"ヒドラ",1579,1;
	monster "force_2-1.gat",179,178,"ヒドラ",1579,1;
	monster "force_2-1.gat",179,170,"ヒドラ",1579,1;
	monster "force_2-1.gat",177,168,"ヒドラ",1579,1;
	monster "force_2-1.gat",170,168,"ヒドラ",1579,1;
	monster "force_2-1.gat",173,174,"ヒドラ",1579,1;
	monster "force_2-1.gat",174,174,"ヒドラ",1579,1;
	monster "force_2-1.gat",173,173,"ヒドラ",1579,1;
	monster "force_2-1.gat",174,173,"ヒドラ",1579,1;
	monster "force_2-1.gat",173,181,"河童",1543,1;
	sleep 500;
	announce "ミロ: クリア条件 : ヒドラと河童を除いた全てのモンスターを退治してください",9;
	end;
OnKilled5:
	callfunc "ArenaKilled",1,6,"ミロ",'mob;
	end;
OnSummon6:
	set 'mob,2;
	disablenpc "Arena1warp#7";
	monster "force_2-1.gat",174,100,"雅人形",1552,1,"ArenaStage1::OnKilled6";
	monster "force_2-1.gat",174,80,"雅人形",1552,1,"ArenaStage1::OnKilled6";
	monster "force_2-1.gat",169,130,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,130,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,125,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,125,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,120,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,120,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,115,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,115,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,110,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,110,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,105,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,105,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,100,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,100,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,95,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,95,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,90,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,90,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,85,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,85,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,80,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,80,"天下大将軍",1541,1;
	monster "force_2-1.gat",169,75,"天下大将軍",1541,1;
	monster "force_2-1.gat",178,75,"天下大将軍",1541,1;
	sleep 500;
	announce "ミロ: クリア条件 : 雅人形を全て退治してください",9;
	end;
OnKilled6:
	switch(rand(3)) {
		case 0: areamonster "force_2-1.gat",170,70,177,120,"サイドワインダー",1424,1; 	break;
		case 1: areamonster "force_2-1.gat",170,70,177,120,"老人参",1565,1; 		break;
		case 2: areamonster "force_2-1.gat",170,70,177,120,"クルーザー",1443,1; 	break;
	}
	callfunc "ArenaKilled",1,7,"ミロ",'mob;
	end;
OnSummon7:
	set 'mob,4;
	disablenpc "Arena1warp#8";
	monster "force_2-1.gat",170,25,"ジャック",1436,1,"ArenaStage1::OnKilled7";
	monster "force_2-1.gat",170,25,"ジャック",1436,1,"ArenaStage1::OnKilled7";
	monster "force_2-1.gat",175,25,"イシス",1421,1,"ArenaStage1::OnKilled7";
	monster "force_2-1.gat",179,25,"ミスト",1553,1,"ArenaStage1::OnKilled7";
	sleep 500;
	announce "ミロ: クリア条件 : モンスターを全て退治してください",9;
	end;
OnKilled7:
	callfunc "ArenaKilled",1,8,"ミロ",'mob;
	end;
OnSummon8:
	disablenpc "Arena1warp#1";
	enablenpc "Arena1warp#9";
	sleep 500;
	announce "ミロ: 北出口から脱出してください！",9;
	end;
OnSummon9:
	set 'mob,1;
	disablenpc "Arena1warp#10";
	monster "force_2-1.gat",99,99,"ゴブリンリーダー",1539,1,"ArenaStage1::OnKilled9";
	monster "force_2-1.gat",90,100,"ホロン",1578,1;
	monster "force_2-1.gat",92,100,"ホロン",1578,1;
	monster "force_2-1.gat",99,100,"ホロン",1578,1;
	monster "force_2-1.gat",105,100,"ホロン",1578,1;
	monster "force_2-1.gat",85,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",87,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",89,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",91,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",93,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",95,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",85,112,"天下大将軍",1541,1;
	monster "force_2-1.gat",85,110,"天下大将軍",1541,1;
	monster "force_2-1.gat",85,108,"天下大将軍",1541,1;
	monster "force_2-1.gat",85,106,"天下大将軍",1541,1;
	monster "force_2-1.gat",85,104,"天下大将軍",1541,1;
	monster "force_2-1.gat",103,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",105,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",107,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",109,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",111,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",113,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,114,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,112,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,110,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,108,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,106,"天下大将軍",1541,1;
	monster "force_2-1.gat",115,104,"天下大将軍",1541,1;
	sleep 500;
	announce "ミロ: クリア条件 : ボスモンスター、ゴブリンリーダー出現！ゴブリンリーダーを倒してください",9;
	end;
OnKilled9:
	callfunc "ArenaKilled",1,10,"ミロ",'mob;
	if('mob <= 0)
		set 'time,getnpctimer(0,"ミロ#arena");	//タイム記録
	end;
//クリア時の1分タイマー
OnTimer2000:
	mapannounce "prt_are_in.gat","タイムアタックLV60～79に関する案内放送です。",0,0xFFCE00;
	end;
OnTimer3000:
	mapannounce "prt_are_in.gat","円滑な進行のため、クリア後控室の滞在は1分とさせていただいています。",0,0xFFCE00;
	end;
OnTimer4000:
	mapannounce "prt_are_in.gat","アリーナポイントの受け取りは速やかにお済ませください。",0,0xFFCE00;
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "prt_are_in.gat",14,126,29,143,"arena_room",100,75;
	enablewaitingroomevent "[LV 60]控室#arena";
	end;
}

force_2-1.gat,62,25,0	script	Arena1warp#1	45,1,1,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "force_2-1.gat",40,26; 	break;
		case 2: warp "force_2-1.gat",25,69; 	break;
		case 3: warp "force_2-1.gat",25,159; 	break;
		case 4: warp "force_2-1.gat",69,174; 	break;
		case 5: warp "force_2-1.gat",159,174; 	break;
		case 6: warp "force_2-1.gat",174,130; 	break;
		case 7: warp "force_2-1.gat",174,40; 	break;
		case 8: warp "force_2-1.gat",132,26; 	break;
		case 9: warp "force_2-1.gat",99,86; 	break;
	}
	donpcevent "ArenaStage1::OnSummon"+'@num;
	end;
}

force_2-1.gat,25,44,0		duplicate(Arena1warp#1)		Arena1warp#2	45,1,1
force_2-1.gat,25,134,0		duplicate(Arena1warp#1)		Arena1warp#3	45,1,1
force_2-1.gat,44,173,0		duplicate(Arena1warp#1)		Arena1warp#4	45,1,1
force_2-1.gat,134,173,0		duplicate(Arena1warp#1)		Arena1warp#5	45,1,1
force_2-1.gat,174,155,0		duplicate(Arena1warp#1)		Arena1warp#6	45,1,1
force_2-1.gat,174,65,0		duplicate(Arena1warp#1)		Arena1warp#7	45,1,1
force_2-1.gat,155,26,0		duplicate(Arena1warp#1)		Arena1warp#8	45,1,1
force_2-1.gat,99,54,0		duplicate(Arena1warp#1)		Arena1warp#9	45,1,1

force_2-1.gat,99,123,0	script	Arena1warp#10	45,1,1,{
	stopnpctimer "ミロ#arena";
	initnpctimer "ArenaStage1";
	warp "prt_are_in.gat",22,140;
	end;
}

prt_are_in.gat,25,135,3	script	進行要員	67,{
	callfunc "ArenaClear",1,60,"LV60～79";
	end;
}

prt_are_in.gat,129,135,3	duplicate(進行要員#arenafailed)	進行要員	67


//==============================================================================
// 個人戦 LV70～89
//==============================================================================
arena_room.gat,53,48,2	script	コンパニオン ビショス	730,{
	mes "[ビショス]";
	mes "……どうも。";
	mes "個人戦LV70～89セクションの";
	mes "コンパニオン、ビショスだ。";
	mes "(……どうして俺がこんなことを)";
	mes "(……ブツブツ……)";
	next;
	mes "[ビショス]";
	mes "^3131FF個人戦LV70～89^000000は";
	mes "^FF0000レベル70^000000から^FF0000レベル89^000000まで入場";
	mes "できる。";
	next;
	mes "[ビショス]";
	mes "レベルが高いプレイヤーが自分より低い";
	mes "レベルのアリーナで威張りちらして";
	mes "ランクを横取りしないように制限を";
	mes "つくった。";
	next;
	mes "[ビショス]";
	mes "個人戦参加料は1000zだ。";
	next;
	mes "[ビショス]";
	mes "それじゃ、アリーナ進行について";
	mes "教えてやる。";
	next;
	mes "[ビショス]";
	mes "参加控室の^3131FFチャットルームに入って";
	mes "自分の順番を待っていればいい。^000000";
	mes "自分の順になれば勝手にアリーナに";
	mes "移動される。";
	next;
	mes "[ビショス]";
	mes "アリーナに入った瞬間にカウントが";
	mes "始まってるからな。";
	mes "^3131FFキャラック^000000がクリア条件を出すから";
	mes "その通りに戦っていけ。";
	next;
	mes "[ビショス]";
	mes "持ち時間は^3131FF7分^000000だ。";
	mes "たいして長くないから、集中して効率を";
	mes "考えないと無理だろうよ。";
	next;
	mes "[ビショス]";
	mes "最後のボスルームをクリアすれば";
	mes "^3131FF終了控室^000000に移動だ。";
	mes "^3131FF終了控室^000000の滞在時間は";
	mes "1分だけだ。担当者からさっさとアリー";
	mes "ナポイントをもらって、さっさと外に";
	mes "出ることだな。";
	next;
	mes "[ビショス]";
	mes "終了控室でアリーナポイントを受け取れ";
	mes "なくても、補償はしてないからな。";
	mes "泣いたって知らねぇぜ。";
	next;
	mes "[ビショス]";
	mes "俺が教えられるのはここまでだ。";
	mes "わかったか？";
	close;
}

arena_room.gat,52,42,7	script	[LV 70]控室#arena	124,{
	end;
OnInit:
	waitingroom "個人戦 LV70～89",20,"[LV 70]控室#arena::OnStart",1,1000,70,89;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		if(Zeny >= 1000) {
			set Zeny,Zeny-1000;
			killmonsterall "force_3-1.gat";
			donpcevent "キャラック#arena::OnStart";
			warp "force_3-1.gat",100,12;
			end;
		}
		kickwaitingroom '@accid;
	}
	enablewaitingroomevent;
	end;
}

force_3-1.gat,99,20,3	script	キャラック#arena	124,{
	end;
OnStart:
	set 'count,7;
	enablenpc "Arena2warp#1";
	disablenpc "Arena2warp#9";
	initnpctimer;
	callfunc "ArenaAnnounce","LV70～89",7;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
OnTimer300000:
OnTimer360000:
OnTimer420000:
	set 'count,'count-1;
	if('count)
		announce "キャラック: 残り時間 : " +'count+ " 分",9;
	else
		announce "キャラック: 時間切れです。残念！",9;
	end;
OnTimer425000:
	stopnpctimer;
	areawarp "force_3-1.gat",0,0,200,200,"prt_are_in.gat",126,88;
	enablewaitingroomevent "[LV 70]控室#arena";
	end;
}

force_3-1.gat,0,0,0	script	ArenaStage2	-1,{
OnSummon1:
	set 'mob,5;
	disablenpc "Arena2warp#2";
	monster "force_3-1.gat",25,36,"コボルド",1545,1,"ArenaStage2::OnKilled1";
	monster "force_3-1.gat",20,36,"コボルド",1545,1,"ArenaStage2::OnKilled1";
	monster "force_3-1.gat",25,20,"コボルド",1546,1,"ArenaStage2::OnKilled1";
	monster "force_3-1.gat",30,36,"コボルド",1547,2,"ArenaStage2::OnKilled1";
	monster "force_3-1.gat",28,15,"コボルド",1547,2,"ArenaStage2::OnKilled1";
	sleep 500;
	announce "キャラック: クリア条件 : コボルドを全て退治してください",9;
	end;
OnKilled1:
	callfunc "ArenaKilled",2,2,"キャラック",'mob;
	end;
OnSummon2:
	set 'mob,2;
	disablenpc "Arena2warp#3";
	monster "force_3-1.gat",25,79,"ホロン",1578,1,"ArenaStage2::OnKilled2";
	monster "force_3-1.gat",29,114,"ホロン",1578,1,"ArenaStage2::OnKilled2";
	monster "force_3-1.gat",21,78,"アーチャースケルトン",1420,1;
	monster "force_3-1.gat",22,93,"アーチャースケルトン",1420,1;
	monster "force_3-1.gat",29,93,"アーチャースケルトン",1420,1;
	monster "force_3-1.gat",25,101,"マミー",1393,1;
	monster "force_3-1.gat",26,101,"マミー",1393,1;
	monster "force_3-1.gat",27,101,"マミー",1393,1;
	monster "force_3-1.gat",28,101,"マミー",1393,1;
	monster "force_3-1.gat",24,104,"グール",1423,1;
	monster "force_3-1.gat",24,113,"グール",1423,1;
	monster "force_3-1.gat",29,120,"グール",1423,1;
	monster "force_3-1.gat",29,126,"グール",1423,1;
	monster "force_3-1.gat",30,110,"グール",1423,1;
	sleep 500;
	announce "キャラック: クリア条件 : ホロンを全て退治してください",9;
	end;
OnKilled2:	//killmonsterしないのでfunction使わない
	set 'mob,'mob-1;
	if('mob <= 0) {
		enablenpc "Arena2warp#3";
		announce "キャラック: 北部屋のドアが開きました！",9;
	}
	end;
OnSummon3:
	set 'mob,3;
	disablenpc "Arena2warp#4";
	monster "force_3-1.gat",23,174,"フェアリーフ",1555,1,"ArenaStage2::OnKilled3";
	monster "force_3-1.gat",33,173,"フェアリーフ",1555,1,"ArenaStage2::OnKilled3";
	monster "force_3-1.gat",26,166,"パピヨン",1526,1,"ArenaStage2::OnKilled3";
	monster "force_3-1.gat",10,170,"人面桃樹",1550,1;
	monster "force_3-1.gat",26,180,"人面桃樹",1550,1;
	sleep 500;
	announce "キャラック: クリア条件 : 人面桃樹を除いたモンスターを全て退治してください",9;
	end;
OnKilled3:
	callfunc "ArenaKilled",2,4,"キャラック",'mob;
	end;
OnSummon4:
	set 'mob,3;
	disablenpc "Arena2warp#5";
	monster "force_3-1.gat",87,174,"ステムワーム",1440,1,"ArenaStage2::OnKilled4";
	monster "force_3-1.gat",103,174,"ステムワーム",1440,1,"ArenaStage2::OnKilled4";
	monster "force_3-1.gat",96,170,"ステムワーム",1440,1,"ArenaStage2::OnKilled4";
	monster "force_3-1.gat",72,126,"バースリー",1525,1;
	monster "force_3-1.gat",110,179,"バースリー",1525,1;
	monster "force_3-1.gat",80,140,"バースリー",1525,1;
	monster "force_3-1.gat",100,170,"バースリー",1525,1;
	monster "force_3-1.gat",92,135,"バースリー",1525,1;
	monster "force_3-1.gat",125,169,"バースリー",1525,1;
	sleep 500;
	announce "キャラック: クリア条件 : バースリーを避けながらステムワームを退治してください",9;
	end;
OnKilled4:
	callfunc "ArenaKilled",2,5,"キャラック",'mob;
	end;
OnSummon5:
	set 'mob,5;
	disablenpc "Arena2warp#6";
	monster "force_3-1.gat",164,183,"アルギオペ",1429,1,"ArenaStage2::OnKilled5";
	monster "force_3-1.gat",168,158,"アルギオペ",1429,1,"ArenaStage2::OnKilled5";
	monster "force_3-1.gat",175,174,"アルギオペ",1429,1,"ArenaStage2::OnKilled5";
	monster "force_3-1.gat",176,179,"アルギオペ",1429,1,"ArenaStage2::OnKilled5";
	monster "force_3-1.gat",183,160,"アルギオペ",1429,1,"ArenaStage2::OnKilled5";
	sleep 500;
	announce "キャラック: クリア条件 : アルギオペを全て退治してください",9;
	end;
OnKilled5:
	switch(rand(3)) {
		case 0: monster "force_3-1.gat",174,174,"ライドワード",1478,1; break;
		case 1: monster "force_3-1.gat",173,173,"マンティス",1457,1; break;
		case 2: break;
	}
	callfunc "ArenaKilled",2,6,"キャラック",'mob;
	end;
OnSummon6:
	set 'mob,5;
	disablenpc "Arena2warp#7";
	monster "force_3-1.gat",179,90,"ゴブリン",1537,1,"ArenaStage2::OnKilled6";
	monster "force_3-1.gat",173,120,"ゴブリン",1537,1,"ArenaStage2::OnKilled6";
	monster "force_3-1.gat",172,113,"ゴブリン",1537,1,"ArenaStage2::OnKilled6";
	monster "force_3-1.gat",175,98,"ゴブリン",1537,1,"ArenaStage2::OnKilled6";
	monster "force_3-1.gat",170,118,"ゴブリン",1537,1,"ArenaStage2::OnKilled6";
//	monster "force_3-1.gat",171,126,"ゴブリン",1534,1;
	monster "force_3-1.gat",176,99,"ゴブリン",1534,1;
	monster "force_3-1.gat",170,86,"ゴブリン",1535,1;
	monster "force_3-1.gat",176,97,"ゴブリン",1535,1;
	monster "force_3-1.gat",170,108,"ゴブリン",1535,1;
	monster "force_3-1.gat",176,112,"ゴブリン",1536,1;
	monster "force_3-1.gat",173,120,"ゴブリン",1536,1;
	monster "force_3-1.gat",177,74,"ゴブリン",1536,1;
	monster "force_3-1.gat",173,118,"ゴブリン",1538,1;
	monster "force_3-1.gat",171,101,"ゴブリン",1538,1;
	monster "force_3-1.gat",174,118,"ゴブリン",1538,1;
	sleep 500;
	announce "キャラック: クリア条件 : ゴブリンの中からゴブリン(槌)だけを倒してください",9;
	end;
OnKilled6:
	callfunc "ArenaKilled",2,7,"キャラック",'mob;
	end;
OnSummon7:
	set 'mob,1;
	disablenpc "Arena2warp#8";
	monster "force_3-1.gat",174,25,"アリス",1521,1,"ArenaStage2::OnKilled7";
	monster "force_3-1.gat",168,26,"ナイトメア",1427,1;
	monster "force_3-1.gat",186,23,"ナイトメア",1427,1;
	monster "force_3-1.gat",160,23,"ナイトメア",1427,1;
	monster "force_3-1.gat",188,33,"ナイトメア",1427,1;
	monster "force_3-1.gat",174,13,"レイドリック",1467,1;
	monster "force_3-1.gat",163,15,"ファミリアー",1419,1;
	monster "force_3-1.gat",164,15,"ファミリアー",1419,1;
	monster "force_3-1.gat",163,16,"ファミリアー",1419,1;
	monster "force_3-1.gat",164,16,"ファミリアー",1419,1;
	monster "force_3-1.gat",187,13,"ファミリアー",1419,1;
	monster "force_3-1.gat",187,14,"ファミリアー",1419,1;
	monster "force_3-1.gat",186,13,"ファミリアー",1419,1;
	monster "force_3-1.gat",186,14,"ファミリアー",1419,1;
	sleep 500;
	announce "キャラック: クリア条件 : アリスを倒してください",9;
	end;
OnKilled7:
	callfunc "ArenaKilled",2,8,"キャラック",'mob;
	end;
OnSummon8:
	disablenpc "Arena2warp#1";
	enablenpc "Arena2warp#9";
	sleep 500;
	announce "キャラック: 北出口から脱出してください！",9;
	end;
OnSummon9:
	set 'mob,4;
	disablenpc "Arena2warp#10";
	monster "force_3-1.gat",99,99,"コボルドリーダー",1548,1,"ArenaStage2::OnKilled9";
	monster "force_3-1.gat",98,99,"コボルド",1545,1,"ArenaStage2::OnKilled9";
	monster "force_3-1.gat",100,99,"コボルド",1546,1,"ArenaStage2::OnKilled9";
	monster "force_3-1.gat",99,98,"コボルド",1547,1,"ArenaStage2::OnKilled9";
	monster "force_3-1.gat",93,100,"ファミリアー",1419,1;
	monster "force_3-1.gat",94,100,"ファミリアー",1419,1;
	monster "force_3-1.gat",93,99,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",87,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",89,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",91,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",93,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",95,114,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,112,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,110,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,108,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,106,"ファミリアー",1419,1;
	monster "force_3-1.gat",85,104,"ファミリアー",1419,1;
	sleep 500;
	announce "キャラック: クリア条件 : ボスモンスター、コボルドリーダー出現！コボルドリーダーとコボルドを倒してください",9;
	end;
OnKilled9:
	callfunc "ArenaKilled",2,10,"キャラック",'mob;
	if('mob <= 0)
		set 'time,getnpctimer(0,"キャラック#arena");	//タイム記録
	end;
//クリア時の1分タイマー
OnTimer2000:
	mapannounce "prt_are_in.gat","タイムアタックLV70～89に関する案内放送です。",0,0xFFCE00;
	end;
OnTimer3000:
	mapannounce "prt_are_in.gat","円滑な進行のため、クリア後控室の滞在は1分とさせていただいています。",0,0xFFCE00;
	end;
OnTimer4000:
	mapannounce "prt_are_in.gat","アリーナポイントの受け取りは速やかにお済ませください。",0,0xFFCE00;
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "prt_are_in.gat",14,74,29,91,"arena_room",100,75;
	enablewaitingroomevent "[LV 70]控室#arena";
	end;
}

force_3-1.gat,62,25,0	script	Arena2warp#1	45,1,1,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "force_3-1.gat",40,26; break;
		case 2: warp "force_3-1.gat",25,69; break;
		case 3: warp "force_3-1.gat",25,159; break;
		case 4: warp "force_3-1.gat",69,174; break;
		case 5: warp "force_3-1.gat",159,174; break;
		case 6: warp "force_3-1.gat",174,130; break;
		case 7: warp "force_3-1.gat",174,40; break;
		case 8: warp "force_3-1.gat",132,26; break;
		case 9: warp "force_3-1.gat",99,86; break;
	}
	donpcevent "ArenaStage2::OnSummon"+'@num;
	end;
}

force_3-1.gat,25,44,0		duplicate(Arena2warp#1)		Arena2warp#2	45,1,1
force_3-1.gat,25,134,0		duplicate(Arena2warp#1)		Arena2warp#3	45,1,1
force_3-1.gat,44,173,0		duplicate(Arena2warp#1)		Arena2warp#4	45,1,1
force_3-1.gat,134,173,0		duplicate(Arena2warp#1)		Arena2warp#5	45,1,1
force_3-1.gat,174,155,0		duplicate(Arena2warp#1)		Arena2warp#6	45,1,1
force_3-1.gat,174,65,0		duplicate(Arena2warp#1)		Arena2warp#7	45,1,1
force_3-1.gat,155,26,0		duplicate(Arena2warp#1)		Arena2warp#8	45,1,1
force_3-1.gat,99,54,0		duplicate(Arena2warp#1)		Arena2warp#9	45,1,1

force_3-1.gat,99,123,0	script	Arena2warp#10	45,1,1,{
	stopnpctimer "キャラック#arena";
	initnpctimer "ArenaStage2";
	warp "prt_are_in.gat",22,88;
	end;
}

prt_are_in.gat,25,83,3	script	進行要員	67,{
	callfunc "ArenaClear",2,70,"LV70～89";
	end;
}

prt_are_in.gat,129,83,3	duplicate(進行要員#arenafailed)	進行要員	67


//==============================================================================
// 個人戦 LV80～99
//==============================================================================
arena_room.gat,147,49,2	script	コンパニオン エピン	727,{
	mes "[エピン]";
	mes "こんにちは～♪";
	mes "個人戦LV80～99のコンパニオンやって";
	mes "ま～す。名前は～、エピンで～す♪";
	mes "趣味は読書で、年は……";
	mes "……ぇ、聞きたくない？";
	next;
	emotion 28;
	mes "[エピン]";
	mes "ぐっすん、わかりました……";
	mes "……つまらないよ～……";
	next;
	mes "[エピン]";
	mes "^3131FF個人戦LV80～99^000000セクションは";
	mes "^FF0000レベル80^000000から^FF0000レベル99^000000まで入場";
	mes "できま～す。";
	next;
	mes "[エピン]";
	mes "参加料は1000zですよ。";
	next;
	mes "[エピン]";
	mes "アリーナの進めかたは～";
	mes "参加控室の^3131FFチャットルーム内で";
	mes "自分の順番を待っててね。^000000";
	mes "自分の順になればアリーナに自動的に";
	mes "移動できちゃいます。";
	next;
	mes "[エピン]";
	mes "アリーナに入るとカウントSTART!!";
	mes "^3131FFアトス^000000がクリア条件を教えてくれるから";
	mes "その通りにモンスターをボコボコに";
	mes "すればOKよ。";
	next;
	mes "[エピン]";
	mes "持ち時間は^3131FF8分^000000だから";
	mes "うま～く時間を使ってね。";
	mes "思ってるほど簡単じゃないわよ～。";
	next;
	mes "[エピン]";
	mes "最後のボスルームをクリアすると";
	mes "^3131FF終了控室^000000に移動します。";
	mes "^3131FF終了控室^000000には1分しか居られない";
	mes "から担当者からチャッチャとアリーナ";
	mes "ポイントをもらってね。";
	next;
	mes "[エピン]";
	mes "もし、終了控室でアリーナポイントを";
	mes "受け取れなかったら、ごめんね。";
	mes "アリーナポイントの補償はしてないの。";
	mes "だから絶対！気をつけてね。";
	next;
	mes "[エピン]";
	mes "以上で～す。わかったかな？";
	mes "ランクインするといいね。";
	mes "ファイト～!!";
	close;
}

arena_room.gat,147,42,1	script	[LV 80]控室#arena	124,{
	end;
OnInit:
	waitingroom "個人戦 LV80～99",20,"[LV 80]控室#arena::OnStart",1,1000,80,99;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		if(Zeny >= 1000) {
			set Zeny,Zeny-1000;
			killmonsterall "force_4-1.gat";
			donpcevent "アトス#arena::OnStart";
			warp "force_4-1.gat",100,12;
			end;
		}
		kickwaitingroom '@accid;
	}
	enablewaitingroomevent;
	end;
}

force_4-1.gat,99,20,3	script	アトス#arena	124,{
	end;
OnStart:
	set 'count,8;
	enablenpc "Arena3warp#1";
	disablenpc "Arena3warp#9";
	initnpctimer;
	callfunc "ArenaAnnounce","LV80～99",8;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
OnTimer300000:
OnTimer360000:
OnTimer420000:
OnTimer480000:
	set 'count,'count-1;
	if('count)
		announce "アトス: 残り時間 : " +'count+ " 分",9;
	else
		announce "アトス: 時間切れです。残念！",9;
	end;
OnTimer485000:
	stopnpctimer;
	areawarp "force_4-1.gat",0,0,200,200,"prt_are_in.gat",178,192;
	enablewaitingroomevent "[LV 80]控室#arena";
	end;
}

force_4-1.gat,0,0,0	script	ArenaStage3	-1,{
OnSummon1:
	set 'mob,4;
	disablenpc "Arena3warp#2";
	monster "force_4-1.gat",35,13,"ナイトメア",1427,1,"ArenaStage3::OnKilled1";
	monster "force_4-1.gat",25,36,"ナイトメア",1427,1,"ArenaStage3::OnKilled1";
	monster "force_4-1.gat",22,23,"ナイトメア",1427,1,"ArenaStage3::OnKilled1";
	monster "force_4-1.gat",25,17,"ナイトメア",1427,1,"ArenaStage3::OnKilled1";
//	monster "force_4-1.gat",25,15,"ナイトメア",1427,1,"ArenaStage3::OnKilled1";
	monster "force_4-1.gat",11,25,"ハンターフライ",1422,1;
	monster "force_4-1.gat",22,22,"ハンターフライ",1422,1;
//	monster "force_4-1.gat",25,25,"ハンターフライ",1422,1;
	monster "force_4-1.gat",35,13,"ハンターフライ",1422,1;
	monster "force_4-1.gat",18,33,"ハンターフライ",1422,1;
	sleep 500;
	announce "アトス: クリア条件 : ナイトメアを全て退治してください",9;
	end;
OnKilled1:
	callfunc "ArenaKilled",3,2,"アトス",'mob;
	end;
OnSummon2:
	set 'mob,15;
	disablenpc "Arena3warp#3";
	monster "force_4-1.gat",24,80,"マリオネット",1459,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",23,110,"マリオネット",1459,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",26,90,"マリオネット",1459,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",28,75,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",24,90,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",28,85,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",24,82,"デビルチ",1433,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",28,86,"スケルプリズナー",1479,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",27,73,"スケルプリズナー",1479,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",26,118,"スケルプリズナー",1479,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",25,127,"スケルプリズナー",1479,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",28,128,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",27,100,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",29,90,"ゾンビ",1394,1,"ArenaStage3::OnKilled2";
	monster "force_4-1.gat",28,128,"レイドリックアーチャー",1453,1,"ArenaStage3::OnKilled2";
	sleep 500;
	announce "アトス: クリア条件 : モンスターを全て退治してください",9;
	end;
OnKilled2:
	callfunc "ArenaKilled",3,3,"アトス",'mob;
	end;
OnSummon3:
	set 'mob,2;
	disablenpc "Arena3warp#4";
	monster "force_4-1.gat",23,174,"アサルトタートル",1364,1,"ArenaStage3::OnKilled3";
	monster "force_4-1.gat",18,173,"アサルトタートル",1364,1,"ArenaStage3::OnKilled3";
	monster "force_4-1.gat",26,173,"時計塔管理者",1527,1;
	monster "force_4-1.gat",21,173,"マリオネット",1459,1;
	monster "force_4-1.gat",31,173,"時計塔管理者",1527,1;
	monster "force_4-1.gat",26,178,"マリオネット",1459,1;
	monster "force_4-1.gat",21,178,"マリオネット",1459,1;
	monster "force_4-1.gat",31,178,"マリオネット",1459,1;
//	monster "force_4-1.gat",26,186,"サイドワインダー",1424,1;
	monster "force_4-1.gat",26,161,"サイドワインダー",1424,1;
	sleep 500;
	announce "アトス: クリア条件 : アサルトタートルを全て退治してください",9;
	end;
OnKilled3:
	callfunc "ArenaKilled",3,4,"アトス",'mob;
	end;
OnSummon4:
	set 'mob,4;
	disablenpc "Arena3warp#5";
	monster "force_4-1.gat",80,172,"九尾狐",1471,1,"ArenaStage3::OnKilled4";
	monster "force_4-1.gat",105,172,"九尾狐",1471,1,"ArenaStage3::OnKilled4";
	monster "force_4-1.gat",90,172,"九尾狐",1471,1,"ArenaStage3::OnKilled4";
	monster "force_4-1.gat",117,172,"九尾狐",1471,1,"ArenaStage3::OnKilled4";
	monster "force_4-1.gat",99,174,"アーチャースケルトン",1420,1;
	monster "force_4-1.gat",101,174,"アーチャースケルトン",1420,1;
	monster "force_4-1.gat",103,174,"アーチャースケルトン",1420,1;
//	monster "force_4-1.gat",105,174,"アーチャースケルトン",1420,1;
	monster "force_4-1.gat",107,174,"アーチャースケルトン",1420,1;
	monster "force_4-1.gat",109,177,"パサナ",1464,1;
	monster "force_4-1.gat",99,170,"ミノタウロス",1461,1;
//	monster "force_4-1.gat",111,170,"ミノタウロス",1461,1;
	monster "force_4-1.gat",110,170,"ラーヴァゴーレム",1549,1;
	sleep 500;
	announce "アトス: クリア条件 : 九尾狐を全て退治してください",9;
	end;
OnKilled4:
	callfunc "ArenaKilled",3,5,"アトス",'mob;
	end;
OnSummon5:
	set 'mob,4;
	disablenpc "Arena3warp#6";
	monster "force_4-1.gat",164,174,"プティット",1465,1,"ArenaStage3::OnKilled5";
	monster "force_4-1.gat",169,159,"プティット",1465,1,"ArenaStage3::OnKilled5";
	monster "force_4-1.gat",174,183,"プティット",1465,1,"ArenaStage3::OnKilled5";
	monster "force_4-1.gat",177,170,"プティット",1465,1,"ArenaStage3::OnKilled5";
	monster "force_4-1.gat",168,190,"プティット",1466,1;
//	monster "force_4-1.gat",173,166,"プティット",1466,1;
//	monster "force_4-1.gat",171,170,"プティット",1466,1;
	monster "force_4-1.gat",188,167,"プティット",1466,1;
	sleep 500;
	announce "アトス: クリア条件 : プティット地を全て退治してください",9;
	end;
OnKilled5:
	monster "force_4-1.gat",168,190,"プティット",1466,1;
//	monster "force_4-1.gat",173,166,"プティット",1466,1;
//	monster "force_4-1.gat",171,170,"プティット",1466,1;
	monster "force_4-1.gat",188,167,"プティット",1466,1;
	callfunc "ArenaKilled",3,6,"アトス",'mob;
	end;
OnSummon6:
	set 'mob,6;
	disablenpc "Arena3warp#7";
	monster "force_4-1.gat",173,118,"バフォメットJr.",1431,1,"ArenaStage3::OnKilled6";
	monster "force_4-1.gat",173,90,"バフォメットJr.",1431,1,"ArenaStage3::OnKilled6";
//	monster "force_4-1.gat",177,72,"バフォメットJr.",1431,1,"ArenaStage3::OnKilled6";
	monster "force_4-1.gat",171,108,"デビルチ",1433,1,"ArenaStage3::OnKilled6";
	monster "force_4-1.gat",171,85,"デビルチ",1433,1,"ArenaStage3::OnKilled6";
	monster "force_4-1.gat",171,79,"アリス",1521,1,"ArenaStage3::OnKilled6";
	monster "force_4-1.gat",172,118,"アリス",1521,1,"ArenaStage3::OnKilled6";
//	monster "force_4-1.gat",175,99,"アリス",1521,1,"ArenaStage3::OnKilled6";
	sleep 500;
	announce "アトス: クリア条件 : モンスターを全て退治してください",9;
	end;
OnKilled6:
	callfunc "ArenaKilled",3,7,"アトス",'mob;
	end;
OnSummon7:
	set 'mob,3;
	disablenpc "Arena3warp#8";
	monster "force_4-1.gat",165,27,"オットー",1533,1,"ArenaStage3::OnKilled7";
	monster "force_4-1.gat",184,23,"オットー",1533,1,"ArenaStage3::OnKilled7";
	monster "force_4-1.gat",174,19,"オットー",1533,1,"ArenaStage3::OnKilled7";
//	monster "force_4-1.gat",160,34,"半漁人",1451,1;
	monster "force_4-1.gat",163,27,"半漁人",1451,1;
	monster "force_4-1.gat",163,23,"半漁人",1451,1;
	sleep 500;
	announce "アトス: クリア条件 : オットーを全て退治してください",9;
	end;
OnKilled7:
	callfunc "ArenaKilled",3,8,"アトス",'mob;
	end;
OnSummon8:
	disablenpc "Arena3warp#1";
	enablenpc "Arena3warp#9";
	sleep 500;
	announce "アトス: 北出口から脱出してください！",9;
	end;
OnSummon9:
	set 'mob,1;
	disablenpc "Arena3warp#10";
	monster "force_4-1.gat",99,99,"エンシェントマミー",1522,1,"ArenaStage3::OnKilled9";
	monster "force_4-1.gat",91,99,"アルゴス",1430,1;
	monster "force_4-1.gat",95,105,"アルゴス",1430,1;
	monster "force_4-1.gat",122,99,"アルゴス",1430,1;
	monster "force_4-1.gat",88,107,"アルゴス",1430,1;
	monster "force_4-1.gat",85,104,"アルゴス",1430,1;
	sleep 500;
	announce "アトス: クリア条件 : ボスモンスター、エンシェントマミー出現！エンシェントマミーを倒してください",9;
	end;
OnKilled9:
	callfunc "ArenaKilled",3,10,"アトス",'mob;
	if('mob <= 0)
		set 'time,getnpctimer(0,"アトス#arena");	//タイム記録
	end;
//クリア時の1分タイマー
OnTimer2000:
	mapannounce "prt_are_in.gat","タイムアタックLV80～99に関する案内放送です。",0,0xFFCE00;
	end;
OnTimer3000:
	mapannounce "prt_are_in.gat","円滑な進行のため、クリア後控室の滞在は1分とさせていただいています。",0,0xFFCE00;
	end;
OnTimer4000:
	mapannounce "prt_are_in.gat","アリーナポイントの受け取りは速やかにお済ませください。",0,0xFFCE00;
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "prt_are_in.gat",66,178,81,195,"arena_room",100,75;
	enablewaitingroomevent "[LV 80]控室#arena";
	end;
}

force_4-1.gat,62,25,0	script	Arena3warp#1	45,1,1,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "force_4-1.gat",40,26; 	break;
		case 2: warp "force_4-1.gat",25,69; 	break;
		case 3: warp "force_4-1.gat",25,159; 	break;
		case 4: warp "force_4-1.gat",69,174; 	break;
		case 5: warp "force_4-1.gat",159,174; 	break;
		case 6: warp "force_4-1.gat",174,130; 	break;
		case 7: warp "force_4-1.gat",174,40; 	break;
		case 8: warp "force_4-1.gat",132,26; 	break;
		case 9: warp "force_4-1.gat",99,86; 	break;
	}
	donpcevent "ArenaStage3::OnSummon"+'@num;
	end;
}

force_4-1.gat,25,44,0		duplicate(Arena3warp#1)		Arena3warp#2	45,1,1
force_4-1.gat,25,134,0		duplicate(Arena3warp#1)		Arena3warp#3	45,1,1
force_4-1.gat,44,173,0		duplicate(Arena3warp#1)		Arena3warp#4	45,1,1
force_4-1.gat,134,173,0		duplicate(Arena3warp#1)		Arena3warp#5	45,1,1
force_4-1.gat,174,155,0		duplicate(Arena3warp#1)		Arena3warp#6	45,1,1
force_4-1.gat,174,65,0		duplicate(Arena3warp#1)		Arena3warp#7	45,1,1
force_4-1.gat,155,26,0		duplicate(Arena3warp#1)		Arena3warp#8	45,1,1
force_4-1.gat,99,54,0		duplicate(Arena3warp#1)		Arena3warp#9	45,1,1

force_4-1.gat,99,123,0	script	Arena3warp#10	45,1,1,{
	stopnpctimer "アトス#arena";
	initnpctimer "ArenaStage3";
	warp "prt_are_in.gat",74,192;
	end;
}

prt_are_in.gat,77,187,3	script	進行要員	67,{
	callfunc "ArenaClear",3,80,"LV80～99";
	end;
}

prt_are_in.gat,181,187,3	duplicate(進行要員#arenafailed)	進行要員	67


//==============================================================================
// パーティー戦
//==============================================================================
arena_room.gat,158,93,4	script	コンパニオン ルーク	828,{
	mes "[ルーク]";
	mes "こんにちは。";
	mes "パーティー戦の説明を担当してます、";
	mes "ルークです。";
	mes "パーティー戦は個人戦とかなり違うので";
	mes "ちゃんと聞いてください。";
	next;
	mes "[ルーク]";
	mes "^3131FFパーティー戦^000000は、";
	mes "^FF0000レベル10^000000から^FF0000レベル99^000000まで";
	mes "入場可能です。";
	next;
	mes "[ルーク]";
	mes "5人でパーティーを組んでいれば";
	mes "参加できます。";
	mes "入場料は、お1人1000zです。";
	next;
	mes "[ルーク]";
	mes "それでは、アリーナ進行に関して";
	mes "説明します。";
	next;
	mes "[ルーク]";
	mes "まず、^3131FF仲間とパーティーを組んで^000000";
	mes "控室の^3131FFチャットルームで^000000順番を待って";
	mes "ください。いいですか、^3131FF必ず^000000パーティー";
	mes "を組んでご参加ください。パーティーを";
	mes "組まないでの参加でトラブルが起こって";
	mes "も、こちらは対応いたしかねます。";
	next;
	mes "[ルーク]";
	mes "チャットルームには、パーティーを";
	mes "組んだ^3131FF5人全員^000000で入ってください。";
	next;
	mes "[ルーク]";
	mes "ここで注意ですが、チャットルーム内の";
	mes "順番に、パーティーメンバー以外の方が";
	mes "途中交じっていると、その方も一緒に";
	mes "転送されてしまいます。";
	mes "気をつけてください。";
	next;
	mes "[ルーク]";
	mes "チャットルームで待機中、順番になれば";
	mes "担当コンパニオンがいるマップに移動";
	mes "します。パーティーがそろわないまま";
	mes "移動してしまった場合、マップ下の";
	mes "ワープで控室のある場所に戻れます。";
	next;
	mes "[ルーク]";
	mes "パーティー戦を開始する時は、担当者に";
	mes "話しかけると進行できます。担当者には";
	mes "該当マップにいる^FF0000誰か1人^000000が";
	mes "話しかければ大丈夫です。";
	next;
	mes "[ルーク]";
	mes "パーティー戦を開始すると、その場に";
	mes "いる全員がアリーナ内に移動しますが";
	mes "^3131FF入場料が足りない方^000000は入場出来ません。";
	next;
	mes "[ルーク]";
	mes "アリーナ前の控室の時間は^FF00001分^000000ですので";
	mes "ご注意ください。";
	next;
	mes "[ルーク]";
	mes "アリーナ入場と同時にカウントが";
	mes "始まります。";
	mes "^3131FFスルラン^000000がクリア条件を出題します。";
	mes "その条件をクリアして、ゴールを";
	mes "目指してください。";
	next;
	mes "[ルーク]";
	mes "待ち時間は^3131FF10分^000000です。";
	mes "無駄にできる時間はありませんから";
	mes "注意してください。";
	next;
	mes "[ルーク]";
	mes "最後のボスルームをクリアすれば";
	mes "^3131FF終了控室^000000に移動します。";
	mes "^3131FF終了控室^000000には1分しか居られませんから";
	mes "素早く、担当者からアリーナポイントを";
	mes "もらってください。";
	next;
	mes "[ルーク]";
	mes "終了控室でアリーナポイントを受け取る";
	mes "ことができなかった場合、アリーナ";
	mes "ポイントの補償は行っておりませんので";
	mes "くれぐれもご注意ください。";
	next;
	mes "[ルーク]";
	mes "パーティーが新記録を達成した場合、";
	mes "^3131FFパーティー名^000000を殿堂に";
	mes "記録することが出来ます。";
	next;
	mes "[ルーク]";
	mes "クリア時にパーティーメンバーが欠けて";
	mes "いると^FF0000正常な記録が出来ません^000000ので";
	mes "必ず開始前に5人パーティーを組み、";
	mes "全員で参加するようお願いします。";
	next;
	mes "[ルーク]";
	mes "パーティー戦については以上です。";
	mes "あなたのご参加、お待ちしています。";
	close;
}

arena_room.gat,158,82,0	script	コンパニオン ロニ	828,{
	emotion 21;
	mes "[ロニ]";
	mes "ヨッシャーッ！";
	mes "ロニに、お任せですよーッ!!";
	next;
	mes "[ロニ]";
	mes "今、中に人が居るか居ないか";
	mes "わからなくて不安なんでしょ？";
	mes "よーし、ロニが教えてあげましょうーッ";
	next;
	mes "[ロニ]";
	mes "どーれどれ……";
	next;
	if(getareausers("prt_are_in.gat",66,74,81,91) || getmapusers("force_1-2.gat")) {
		emotion 24;
		mes "[ロニ]";
		mes " Y E S - !!";
		mes "誰か中に居るみたい～";
		next;
		mes "[ロニ]";
		mes "もうちょっと待つと良い～って";
		mes "感じ、かな。";
	}
	else {
		emotion 25;
		mes "[ロニ]";
		mes " N O - !!!!!!!";
		mes "誰も居ないッ。よし、出陣だーッ♪";
	}
	close;
}

arena_room.gat,162,88,2	script	ポノ#arena	124,{
	end;
OnInit:
	waitingroom "パーティー戦[5人制限]",10,"ポノ#arena::OnStart",5,1000,10,99;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid getvariableofnpc('id,"コンパニオン#arena");
	initnpctimer "コンパニオン#arena";
	warpwaitingpc "prt_are_in.gat",73,78;
	end;
}

prt_are_in.gat,76,87,3	script	コンパニオン#arena	67,{
	if('flag) {
		mes "[リリー]";
		mes "他の方が話しかけられましたので";
		mes "只今、そちらの対応をしております。";
		mes "そのままお待ち下さい。";
		mes "但し、1分以上経過してしまった際は、";
		mes "再度チャットルームからのご入場を";
		mes "お願いします。";
		close;
	}
	set 'flag,1;
	mes "[リリー]";
	mes "こんにちは。";
	mes "こちらでアリーナ用パーティーを";
	mes "準備していってください。";
	next;
	mes "[リリー]";
	mes "こちらには1分以上滞在できません。";
	mes "すぐアリーナに移動しますか？";
	next;
	if(select("もうちょっと考える","移動する")==1) {
		mes "[リリー]";
		mes "わかりました。";
		mes "但し、1分以上経過してしまった際は、";
		mes "再度チャットルームからのご入場を";
		mes "お願いします。";
		set 'flag,0;
		close;
	}
	mes "[リリー]";
	mes "アリーナへ移動します～。";
	mes "アリーナ行きワープを開きます。";
	mes "モンスターとの死闘を生き残り、";
	mes "その栄光と共にご自分の名前を";
	mes "歴史に刻み込めるよう";
	mes "お祈りしております。";
	close2;
	stopnpctimer;
	killmonsterall "force_1-2.gat";
	for(set '@i,0; '@i<5; set '@i,'@i+1) {
		if(attachrid('id['@i])) {
			set '@dummy,getmapxy('@map$,'@x,'@y,0);
			if(Zeny >= 1000 && '@map$ == "prt_are_in.gat" && '@x >= 66 && '@x <= 81 && '@y >= 74 && '@y <= 91) {
				set Zeny,Zeny-1000;
				warp "force_1-2.gat",99,26;
			}
		}
	}
	areawarp "prt_are_in.gat",66,74,81,91,"arena_room",100,75;
	set 'flag,0;
	donpcevent "スルラン#arena::OnStart";
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "prt_are_in.gat",66,74,81,91,"arena_room",100,75;
	set 'flag,0;
	enablewaitingroomevent "ポノ#arena";
	end;
}
prt_are_in.gat,73,74,0	warp	Arena4warp	1,1,arena_room.gat,100,75

force_1-2.gat,99,31,4	script	スルラン#arena	124,{
	end;
OnStart:
	set 'count,10;
	initnpctimer;
	sleep 2000;
	announce "スルラン: こんにちは。タイムアタックバトル、パーティー戦セクション司会者、スルランです！",9;
	sleep 1000;
	announce "スルラン: こちらのアリーナでは、モンスターの全滅が目標です。",9;
	sleep 1000;
	announce "スルラン: まずは、ここから上・左右どれかの部屋に進んでください。",9;
	sleep 1000;
	announce "スルラン: 制限時間は10分です。みなさんの勇姿を期待しております！",9;
	end;
OnTimer60000:
OnTimer120000:
OnTimer180000:
OnTimer240000:
OnTimer300000:
OnTimer360000:
OnTimer420000:
OnTimer480000:
OnTimer540000:
OnTimer600000:
	set 'count,'count-1;
	if('count)
		announce "スルラン: 残り時間 : " +'count+ " 分",9;
	else
		announce "スルラン: 時間切れです。残念！",9;
	end;
OnTimer605000:
	stopnpctimer;
	areawarp "force_1-2.gat",0,0,200,200,"prt_are_in.gat",177,140;
	set getvariableofnpc('flag,"ArenaStage4"),0;
	enablewaitingroomevent "ポノ#arena";
	end;
}

force_1-2.gat,0,0,0	script	ArenaStage4	-1,{
OnSummon1:
	if('flag&0x001)
		end;
	set 'flag,'flag|0x001;
	set 'mob1,26;
	disablenpc "Arena4warp#4";
	monster "force_1-2.gat",15,35,"ペノメナ",1441,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",35,35,"ペノメナ",1441,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",15,15,"ペノメナ",1441,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",35,15,"ペノメナ",1441,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",15,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",17,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",19,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",21,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",15,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",17,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",19,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",21,25,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",15,30,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",17,22,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",19,32,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",21,22,"クロック",1528,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",26,33,"時計塔管理者",1527,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",26,33,"時計塔管理者",1527,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",26,14,"エンシェントワーム",1567,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",30,27,"エンシェントワーム",1567,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",29,25,"エンシェントワーム",1567,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",26,14,"エンシェントワーム",1567,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",33,26,"インキュバス",1580,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",29,28,"インキュバス",1580,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",33,20,"インキュバス",1580,1,"ArenaStage4::OnKilled1";
	monster "force_1-2.gat",33,30,"インキュバス",1580,1,"ArenaStage4::OnKilled1";
	end;
OnKilled1:
	set 'mob1,'mob1-1;
	if('mob1)
		end;
	set 'flag,'flag|0x002;
	enablenpc "Arena4warp#4";
	if('flag == 0x03F) {
		enablenpc "Arena4warp#7";
		announce "スルラン: 東の4番目の部屋のドアが開きました！",9;
	}
	else
		announce "スルラン: クリア！東部屋のドアが開きました！",9;
	end;
OnSummon2:
	if('flag&0x004)
		end;
	set 'flag,'flag|0x004;
	set 'mob2,30;
	disablenpc "Arena4warp#5";
	monster "force_1-2.gat",163,36,"ペノメナ",1441,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",184,36,"ペノメナ",1441,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",184,16,"ペノメナ",1441,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",163,16,"ペノメナ",1441,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",171,37,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",177,37,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",184,29,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",184,22,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",177,16,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",170,16,"ジョーカー",1437,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",169,28,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",171,28,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",173,28,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",175,28,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",177,28,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",177,23,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",175,23,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",173,23,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",171,23,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",169,23,"バースリー",1525,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,30,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,30,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,30,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,22,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,22,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",187,22,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",173,40,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",173,40,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",181,25,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	monster "force_1-2.gat",181,25,"アクラウス",1477,1,"ArenaStage4::OnKilled2";
	end;
OnKilled2:
	set 'mob2,'mob2-1;
	if('mob2)
		end;
	set 'flag,'flag|0x008;
	enablenpc "Arena4warp#5";
	if('flag == 0x03F) {
		enablenpc "Arena4warp#7";
		announce "スルラン: 東の4番目の部屋のドアが開きました！",9;
	}
	else
		announce "スルラン: クリア！西部屋のドアが開きました！",9;
	end;
OnSummon3:
	if('flag&0x010)
		end;
	set 'flag,'flag|0x010;
	set 'mob3,26;
	disablenpc "Arena4warp#6";
	disablenpc "Arena4warp#7";
	disablenpc "Arena4warp#9";
	monster "force_1-2.gat",89,81,"半漁人",1451,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",90,81,"半漁人",1451,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",91,81,"半漁人",1451,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",92,81,"半漁人",1451,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",93,81,"半漁人",1451,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",96,85,"ウィンドゴースト",1450,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",98,85,"ウィンドゴースト",1450,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",100,85,"ウィンドゴースト",1450,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",102,85,"ウィンドゴースト",1450,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",104,85,"ウィンドゴースト",1450,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",88,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",90,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",92,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",94,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",96,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",98,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",100,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",102,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",104,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",106,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",108,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",110,79,"デビルチ",1433,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",91,86,"彷徨う者",1490,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",108,86,"彷徨う者",1490,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",91,69,"彷徨う者",1490,1,"ArenaStage4::OnKilled3";
	monster "force_1-2.gat",108,69,"彷徨う者",1490,1,"ArenaStage4::OnKilled3";
	end;
OnKilled3:
	set 'mob3,'mob3-1;
	if('mob3)
		end;
	set 'flag,'flag|0x020;
	enablenpc "Arena4warp#6";
	if('flag == 0x03F) {
		enablenpc "Arena4warp#7";
		announce "スルラン: 東の4番目の部屋のドアが開きました！",9;
	}
	else
		announce "スルラン: クリア！南部屋のドアが開きました！",9;
	end;
OnSummon4:
	if('flag&0x040)
		end;
	set 'flag,'flag|0x040;
	set 'mob,22;
	disablenpc "Arena4warp#8";
	monster "force_1-2.gat",174,78,"ペノメナ",1441,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",184,78,"ペノメナ",1441,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",184,68,"ペノメナ",1441,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",174,68,"ペノメナ",1441,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",169,87,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",170,87,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",171,87,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",172,87,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",169,77,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",170,77,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",171,77,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",172,77,"ライドワード",1478,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",183,83,"デッドリーレイス",1566,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",183,80,"デッドリーレイス",1566,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",183,73,"デッドリーレイス",1566,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",183,70,"デッドリーレイス",1566,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",179,77,"デッドリーレイス",1566,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",169,72,"アサルトタートル",1364,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",171,72,"アサルトタートル",1364,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",173,72,"アサルトタートル",1364,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",175,72,"アサルトタートル",1364,1,"ArenaStage4::OnKilled4";
	monster "force_1-2.gat",177,72,"アサルトタートル",1364,1,"ArenaStage4::OnKilled4";
	end;
OnKilled4:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#8";
	enablenpc "Arena4warp#9";
	announce "スルラン: 西の部屋をクリアしてください！",9;
	end;
OnSummon5:
	if('flag&0x080)
		end;
	set 'flag,'flag|0x080;
	set 'mob,24;
	disablenpc "Arena4warp#10";
	monster "force_1-2.gat",25,68,"ペノメナ",1441,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",36,68,"ペノメナ",1441,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",16,88,"ペノメナ",1441,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",15,78,"ペノメナ",1441,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",33,89,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",29,87,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",25,81,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",25,78,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",25,72,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",29,70,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",21,70,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",19,76,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",19,83,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",23,89,"スティング",1489,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",22,85,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",23,85,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",24,85,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",23,86,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",22,86,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",22,71,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",22,72,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",23,71,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",23,72,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	monster "force_1-2.gat",24,71,"クランプ",1570,1,"ArenaStage4::OnKilled5";
	end;
OnKilled5:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#10";
	announce "スルラン: 北部屋のドアが開きました！",9;
	end;
OnSummon6:
	if('flag&0x100)
		end;
	set 'flag,'flag|0x100;
	set 'mob,22;
	disablenpc "Arena4warp#11";
	monster "force_1-2.gat",24,127,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",27,127,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",24,128,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",27,128,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",24,129,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",27,129,"カブキ忍者",1560,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",19,135,"天邪仙人",1531,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",24,135,"天邪仙人",1531,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",28,135,"天邪仙人",1531,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",32,135,"天邪仙人",1531,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,140,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,136,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,132,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,128,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,124,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,120,"酒天狗",1563,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,140,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,136,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,132,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,128,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,124,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	monster "force_1-2.gat",16,120,"天仙娘々",1564,1,"ArenaStage4::OnKilled6";
	end;
OnKilled6:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#11";
	announce "スルラン: 東部屋のドアが開きました！",9;
	end;
OnSummon7:
	if('flag&0x200)
		end;
	set 'flag,'flag|0x200;
	set 'mob,12;
	disablenpc "Arena4warp#12";
	monster "force_1-2.gat",108,140,"キメラ",1456,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",98,122,"エクスキューショナー",1487,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",98,122,"カーリッツバーグ",1438,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",90,119,"カーリッツバーグ",1438,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",104,134,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",104,136,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",104,137,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",104,139,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",111,134,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",111,136,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",111,137,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	monster "force_1-2.gat",111,139,"天下大将軍",1541,1,"ArenaStage4::OnKilled7";
	end;
OnKilled7:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#12";
	announce "スルラン: 北部屋のドアが開きました！",9;
	end;
OnSummon8:
	if('flag&0x400)
		end;
	set 'flag,'flag|0x400;
	set 'mob,35;
	disablenpc "Arena4warp#13";
	monster "force_1-2.gat",174,145,"キメラ",1456,1,"ArenaStage4::OnKilled8";
	monster "force_1-2.gat",174,145,"ゴーストリング",1576,1,"ArenaStage4::OnKilled8";
	monster "force_1-2.gat",172,154,"ブラッディナイト",1569,1,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"インジャスティス",1446,5,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"レイドリックアーチャー",1453,1,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"ナイトメアテラー",1554,5,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"エンシェントマミー",1522,6,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"スケルプリズナー",1479,10,"ArenaStage4::OnKilled8";
	areamonster "force_1-2.gat",162,122,184,185,"ハンターフライ",1422,5,"ArenaStage4::OnKilled8";
	end;
OnKilled8:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#13";
	announce "スルラン: 西部屋のドアが開きました！",9;
	end;
OnSummon9:
	if('flag&0x800)
		end;
	set 'flag,'flag|0x800;
	set 'mob,15;
	disablenpc "Arena4warp#14";
	disablenpc "Arena4warp#16";
	monster "force_1-2.gat",122,177,"ラーヴァゴーレム",1549,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",112,179,"ラーヴァゴーレム",1549,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",122,178,"アノリアン",1488,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",121,177,"アノリアン",1488,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",122,177,"アノリアン",1488,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",86,180,"エルダー",1573,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",86,176,"エルダー",1573,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",95,183,"エルダー",1573,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",94,175,"エルダー",1573,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",76,178,"エルダー",1573,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",84,179,"エクスプロージョン",1532,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",74,181,"エクスプロージョン",1532,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",73,176,"エクスプロージョン",1532,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",62,178,"エクスプロージョン",1532,1,"ArenaStage4::OnKilled9";
	monster "force_1-2.gat",68,177,"エクスプロージョン",1532,1,"ArenaStage4::OnKilled9";
	end;
OnKilled9:
	set 'mob,'mob-1;
	if('mob)
		end;
	enablenpc "Arena4warp#14";
	announce "スルラン: 西部屋のドアが開きました！",9;
	end;
OnSummon10:
	if('flag&0x1000)
		end;
	set 'flag,'flag|0x1000;
	disablenpc "Arena4warp#15";
	if(rand(2))
		monster "force_1-2.gat",16,179,"黒蛇王",1529,1,"ArenaStage4::OnKilled10_1";
	else
		monster "force_1-2.gat",24,179,"ドラキュラ",1530,1,"ArenaStage4::OnKilled10_1";
	end;
OnKilled10_1:
	set 'mob,6;
	monster "force_1-2.gat",16,179,"怨霊武士",1542,1,"ArenaStage4::OnKilled10_2";
	monster "force_1-2.gat",16,179,"カブキ忍者",1560,1,"ArenaStage4::OnKilled10_2";
	monster "force_1-2.gat",16,179,"カブキ忍者",1560,1,"ArenaStage4::OnKilled10_2";
	monster "force_1-2.gat",16,179,"カブキ忍者",1560,1,"ArenaStage4::OnKilled10_2";
	monster "force_1-2.gat",16,179,"カブキ忍者",1560,1,"ArenaStage4::OnKilled10_2";
	monster "force_1-2.gat",16,179,"カブキ忍者",1560,1,"ArenaStage4::OnKilled10_2";
	end;
OnKilled10_2:
	set 'mob,'mob-1;
	if('mob)
		end;
	set 'time,getnpctimer(0,"スルラン#arena");
	enablenpc "Arena4warp#15";
	announce "スルラン: ボスステージをクリア！東出口から脱出してください！",9;
	end;
OnSummon11:
	if('flag&0x2000)
		end;
	set 'flag,'flag|0x2000;
	enablenpc "Arena4warp#16";
	monster "force_1-2.gat",95,177,"さようなら",1393,1;
	monster "force_1-2.gat",95,177,"あなたが嫌い",1543,1;
	monster "force_1-2.gat",95,177,"チョコレートが好き",1472,1;
	monster "force_1-2.gat",95,177,"あなたは好きですか？",1472,1;
	monster "force_1-2.gat",95,177,"ごめんなさい",1420,1;
	monster "force_1-2.gat",95,177,"トリスタン2世",1562,1;
	monster "force_1-2.gat",95,177,"お腹空いた",1468,1;
	monster "force_1-2.gat",95,177,"バイバイ",1419,1;
	monster "force_1-2.gat",95,177,"注意",1394,1;
	monster "force_1-2.gat",95,177,"セクシーボディ",1578,1;
	monster "force_1-2.gat",95,177,"プレッシャー",1471,1;
	monster "force_1-2.gat",95,177,"気楽に",1491,1;
	monster "force_1-2.gat",95,177,"叩くつもりですか？",1555,1;
	monster "force_1-2.gat",95,177,"商人",1428,1;
	monster "force_1-2.gat",95,177,"キムさん",1472,1;
	monster "force_1-2.gat",95,177,"格闘技",1472,1;
	monster "force_1-2.gat",95,177,"パートタイマー",1420,1;
	monster "force_1-2.gat",95,177,"ボス",1562,1;
	monster "force_1-2.gat",95,177,"古く黄色の箱",1474,1;
	monster "force_1-2.gat",95,177,"コウモリ",1419,1;
	monster "force_1-2.gat",95,177,"エキストラ",1394,1;
	monster "force_1-2.gat",95,177,"ミルク商人",1578,1;
	monster "force_1-2.gat",95,177,"ダーリン",1471,1;
	monster "force_1-2.gat",95,177,"鬼",1491,1;
	monster "force_1-2.gat",95,177,"レイスじゃないよ",1566,1;
	monster "force_1-2.gat",95,177,"レイスママ",1566,1;
	monster "force_1-2.gat",95,177,"レイスパパ",1566,1;
	monster "force_1-2.gat",95,177,"ブック[3]",1478,1;
	monster "force_1-2.gat",95,177,"交換日記",1478,1;
	sleep 500;
	announce "スルラン: モンスターを避けて北出口から脱出してください！",9;
	end;
//クリア時の1分タイマー
OnTimer2000:
	mapannounce "prt_are_in.gat","タイムアタックパーティ戦に関する案内放送です。",0,0xFFCE00;
	end;
OnTimer3000:
	mapannounce "prt_are_in.gat","円滑な進行のため、クリア後控室の滞在は1分とさせていただいています。",0,0xFFCE00;
	end;
OnTimer4000:
	mapannounce "prt_are_in.gat","アリーナポイントの受け取りは速やかにお済ませください。",0,0xFFCE00;
	end;
OnTimer60000:
	stopnpctimer;
	areawarp "force_1-2.gat",0,0,200,200,"arena_room",100,75;
	areawarp "prt_are_in.gat",66,126,81,143,"arena_room",100,75;
	enablewaitingroomevent "ポノ#arena";
	set 'flag,0;
	end;
}

force_1-2.gat,85,26,0	script	Arena4warp#1	45,1,1,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "force_1-2.gat",37,26;	donpcevent "ArenaStage4::OnSummon1";	break;
		case 2: warp "force_1-2.gat",162,26;	donpcevent "ArenaStage4::OnSummon2";	break;
		case 3: warp "force_1-2.gat",99,66;	donpcevent "ArenaStage4::OnSummon3";	break;
		case 4: warp "force_1-2.gat",89,26; 	break;
		case 5: warp "force_1-2.gat",110,26;	break;
		case 6: warp "force_1-2.gat",99,36; 	break;
		case 7: warp "force_1-2.gat",162,78;	donpcevent "ArenaStage4::OnSummon4";	break;
		case 8: warp "force_1-2.gat",110,78; 	break;
		case 9: warp "force_1-2.gat",37,78;	donpcevent "ArenaStage4::OnSummon5";	break;
		case 10: warp "force_1-2.gat",26,118;	donpcevent "ArenaStage4::OnSummon6";	break;
		case 11: warp "force_1-2.gat",91,125;	donpcevent "ArenaStage4::OnSummon7";	break;
		case 12: warp "force_1-2.gat",173,118;	donpcevent "ArenaStage4::OnSummon8";	break;
		case 13: warp "force_1-2.gat",133,178;	donpcevent "ArenaStage4::OnSummon9";	break;
		case 14: warp "force_1-2.gat",29,178;	donpcevent "ArenaStage4::OnSummon10";	break;
		case 15: warp "force_1-2.gat",59,178;	donpcevent "ArenaStage4::OnSummon11";	break;
	}
	//donpcevent "ArenaStage4::OnSummon"+'@num;
	end;
}

force_1-2.gat,114,26,0		duplicate(Arena4warp#1)		Arena4warp#2	45,1,1
force_1-2.gat,99,40,0		duplicate(Arena4warp#1)		Arena4warp#3	45,1,1
force_1-2.gat,41,26,0		duplicate(Arena4warp#1)		Arena4warp#4	45,1,1
force_1-2.gat,158,26,0		duplicate(Arena4warp#1)		Arena4warp#5	45,1,1
force_1-2.gat,99,63,0		duplicate(Arena4warp#1)		Arena4warp#6	45,1,1
force_1-2.gat,115,78,0		duplicate(Arena4warp#1)		Arena4warp#7	45,1,1
force_1-2.gat,158,77,0		duplicate(Arena4warp#1)		Arena4warp#8	45,1,1
force_1-2.gat,84,77,0		duplicate(Arena4warp#1)		Arena4warp#9	45,1,1
force_1-2.gat,25,93,0		duplicate(Arena4warp#1)		Arena4warp#10	45,1,1
force_1-2.gat,49,130,0		duplicate(Arena4warp#1)		Arena4warp#11	45,1,1
force_1-2.gat,107,145,0		duplicate(Arena4warp#1)		Arena4warp#12	45,1,1
force_1-2.gat,158,178,0		duplicate(Arena4warp#1)		Arena4warp#13	45,1,1
force_1-2.gat,55,178,0		duplicate(Arena4warp#1)		Arena4warp#14	45,1,1
force_1-2.gat,33,178,0		duplicate(Arena4warp#1)		Arena4warp#15	45,1,1
force_1-2.gat,95,187,0	script	Arena4warp#16	45,1,1,{
	stopnpctimer "スルラン#arena";
	initnpctimer "ArenaStage4";
	warp "prt_are_in.gat",74,140;
	end;
}

prt_are_in.gat,77,135,3	script	進行要員	67,{
	mes "[進行要員]";
	mes "お疲れ様でした。";
	mes "お名前は……";
	mes "^3131FF" +strcharinfo(0)+ "^000000様ですね？";
	mes "^3131FF" +strcharinfo(0)+ "^000000様が";
	mes "アリーナをクリアするのにかかった";
	mes "時間は……";
	next;
	mes "[進行要員]";
	set '@time,getvariableofnpc('time,"ArenaStage4");
	mes '@time/60000+ "分" +'@time%60000/1000+ "秒です！";
	if('@time <= $ArenaTime[4] || $ArenaTime[4] == 0) {	//パーティ分記録更新
		next;
		mes "[進行要員]";
		mes "ウオオッ!!　新記録ーーー!!";
		mes "おめでとうございます!!!!";
		next;
		mes "[進行要員]";
		mes "^FF0000タイムアタック";
		mes "パーティー戦セクション^000000にあなたの";
		mes "パーティー^3131FF" +strcharinfo(1)+ "^000000を";
		mes "記録いたします。";
		next;
		mes "[進行要員]";
		mes "アリーナの記録の確認は";
		mes "アリーナ控室の^3131FFアウェンキープ^000000に";
		mes "お問い合わせください。";
		next;
		mes "[進行要員]";
		mes "それではアリーナポイントを";
		mes "支給いたします。新記録達成";
		mes "ですので、ボーナスポイントも";
		mes "支給いたします。";
		next;
		mes "[進行要員]";
		mes "それでは、入口にお送りしましょう。";
		mes "お疲れさまでした～。またの";
		mes "お越しをお待ちしております。";
		close2;
		set $ArenaName$[4],strcharinfo(1);
		set $ArenaTime[4],'@time;
		set ARENA_PIT,ARENA_PIT+100;
	}
	else {
		mes "おめでとうございます!!";
		next;
		mes "[進行要員]";
		mes "現在、タイムアタック";
		mes "パーティー戦セクションを一番早く";
		mes "クリアしたパーティーは……";
		mes "^3131FF" +$ArenaName$[4]+ "^000000様です。";
		next;
		mes "[進行要員]";
		mes "^3131FF" +$ArenaName$[4]+ "^000000様の";
		mes "タイムは^3131FF" +$ArenaTime[4]/60000+ "^000000分^3131FF" +$ArenaTime[4]%60000/1000+ "^000000秒です。";
		next;
		mes "[進行要員]";
		mes "記録更新は成せませんでしたが、";
		mes "次の機会には是非成功させてください。";
		next;
		mes "[進行要員]";
		mes "それでは、アリーナポイントを";
		mes "支給いたします。";
		mes "アリーナポイントの確認は";
		mes "アリーナ控室の^3131FFベンデゴス^000000に";
		mes "お問い合わせください。";
		next;
		mes "[進行要員]";
		mes "それでは、入口にお送りしましょう。";
		mes "お疲れさまでした～。またの";
		mes "お越しをお待ちしております。";
		close2;
		set ARENA_PIT,ARENA_PIT+40;
	}
	warp "arena_room.gat",100,75;
	end;
}

prt_are_in.gat,181,135,3	duplicate(進行要員#arenafailed)	進行要員	67


//==============================================================================
// 聖職者セクション
//
// 　■ $ArenaName$[] -> 1位記録者のキャラ名、要素はモードごとに5～9
//                       （通常およびPTセクションが0～4）
//      $ArenaTime[]   -> 記録タイム、要素は同上
//==============================================================================

arena_room.gat,94,82,2	script	アリーナ記録担当	79,{
	mes "[マティア]";
	mes "こんにちは。";
	mes "アリーナの聖職者セクションの";
	mes "記録を管理・案内している";
	mes "マティアと申します。";
	mes "他セクションの記録は、そちらにいる";
	mes "アウェンキープにお尋ねください。";
	next;
	mes "[マティア]";
	mes "各モードで最短時間を";
	mes "記録した方々のお名前を";
	mes "知りたいのですか？";
	mes "ご希望のモードをお選びください。";
	next;
	switch (select("アコライト","上位職-LV70未満","上位職-LV70～79","上位職-LV80～89","上位職-LV90～Lv99")) {
		case 1: set '@word$,"アコライトモード"; 	break;
		case 2: set '@word$,"上位職モードLV70未満"; 	break;
		case 3: set '@word$,"上位職モードLV70～79"; 	break;
		case 4: set '@word$,"上位職モードLV80～89"; 	break;
		case 5: set '@word$,"上位職モードLV90～99"; 	break;
	}
	mes "[マティア]";
	mes "現在、聖職者セクション";
	mes '@word$+ "は、";
	mes "^3131FF" +$ArenaName$[@menu+4]+ "^000000様が";
	mes "1位です。記録は";
	mes "^3131FF" +$ArenaTime[@menu+4]/60000+"^000000分^3131FF"+$ArenaTime[@menu+4]%60000/1000+"^000000秒です。";
	close;
}

arena_room.gat,114,102,0	script	#ArenaAcoMode	45,1,1,{
	if(getbaseclass(Class) == CLASS_AL) {
		warp "area_room.gat",135,129;
		end;
	}
	mes "こちらは、アコライトと";
	mes "その上位職の方を対象とした";
	mes "聖職者セクションです。";
	close;
}

arena_room.gat,140,136,2	script	コンパニオン・アラス	729,{
	mes "[アラス]";
	mes "こんにちは。";
	mes "私は聖職者セクションの";
	mes "案内を担当するアラスと言います。";
	mes "では、聖職者セクションについて";
	mes "ご説明しましょう。";
	next;
	mes "[アラス]";
	mes "聖職者セクションには、";
	mes "^3131FFアコライトモード^000000と";
	mes "^3131FF上位職モード^000000があります。";
	next;
	mes "[アラス]";
	mes "アコライトやその上位職の方が";
	mes "^3131FF聖職者控室^000000にて";
	mes "待機していますと、";
	mes "ご自分の番になり次第、";
	mes "アリーナに挑戦することができます。";
	mes "入場料は、お一人様1000zです。";
	next;
	mes "[アラス]";
	mes "控え室は皆様ご一緒になりますが、";
	mes "難易度についてはご心配いりません。";
	mes "各自のレベルに応じたモードを";
	mes "ご用意してあります。";
	next;
	mes "[アラス]";
	mes "さて注意事項ですが、";
	mes "アリーナに登場する^3131FF赤い草^000000と";
	mes "^3131FFパーメットタートル^000000は、";
	mes "^FF0000経験値とアイテムをドロップする";
	mes "一般モンスター^000000となっております。";
	mes "ご了承ください。";
	next;
	mes "[アラス]";
	mes "それから、アリーナに移動後は、";
	mes "司会者の^3131FFトロコ^000000の指示に従って";
	mes "時計方向に各部屋をまわってください。";
	mes "尚、制限時間は、^3131FF8分^000000です。";
	next;
	mes "[アラス]";
	mes "アリーナクリア後、";
	mes "ワープリンクをご利用なされば、";
	mes "^3131FF控え室^000000に移動します。";
	next;
	mes "[アラス]";
	mes "こちらでアリーナポイントを";
	mes "受けとることができますが、";
	mes "^3131FF1分以上滞在することは";
	mes "できません^000000ので";
	mes "ご注意ください。";
	next;
	mes "[アラス]";
	mes "1分経過して外へ出た後は、";
	mes "アリーナポイントを";
	mes "受け取ることはできませんので、";
	mes "必ず時間内にポイントを";
	mes "受け取ってください。";
	mes "よろしいでしょうか？";
	next;
	mes "[アラス]";
	mes "それでは、よい時を！";
	mes "Good Luck!!";
	close;
}

arena_room.gat,136,138,4	script	聖職者控室#arena	124,{
	end;
OnInit:
	//ここでは他職排除しないが念のため
	waitingroom "個人戦-聖職者専用",20,"聖職者控室#arena::OnStart",1,1000,0,255,(1<<CLASS_AL)|(1<<CLASS_PR)|(1<<CLASS_MO),0;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		if(Zeny >= 1000) {
			set Zeny,Zeny-1000;
			killmonsterall "force_5-1.gat";
			donpcevent "トコロ#arena::OnStart";
			//warp "force_5-1.gat",100,12;
			end;
		}
		kickwaitingroom '@accid;
	}
	enablewaitingroomevent;
	end;
}

force_5-1.gat,0,0,0	script	トコロ#arena	-1,{
OnStart:
	end;
}
