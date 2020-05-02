//= Auriga Script ==============================================================
// Ragnarok Online Portmalaya Town Script	by refis
//= Registry ===================================================================
// $MalayaName$[0] -> ポートマラヤの噂
// $MalayaName$[1] -> バリオ・マヒワガの噂
// $MalayaName$[2] -> カプレの味方の噂
// $MalayaName$[3] -> ma_fild01謎の生物の噂
// $MalayaName$[4] -> ma_fild02謎の生物の噂
// $MalayaName$[5] -> ma_scene01謎の生物の噂
// $MalayaFes -> ピンタドスフェスティバル開催期間
// $MalayaFes01 -> 小さなお守り 納品数
// $MalayaFes02 -> 銀の十字架 納品数
// $MalayaFes03 -> 染料 納品数
//==============================================================================

//============================================================
// Shop
//------------------------------------------------------------
ma_in01.gat,73,22,3	shop	武器商人	536,1207,1216,1107,1122,1116,1154,1407,1457,1354,1519
ma_in01.gat,67,13,5	shop	防具商人	536,2211,2401,2403,2501,2503,2101,2103,2305,2321,2332,2328,2627
ma_in01.gat,22,23,3	shop	道具商人	536,611,1750,501,502,503,504,645,656,601,602,1065,2239
malaya.gat,150,261,3	shop	果物商人	535,512,513,515,516,535

//============================================================
// アルベルタ⇔ポートマラヤ転送NPC
//------------------------------------------------------------
alberta.gat,196,202,3	script	オフタラマ号船員	100,{
	mes "[オフタラマ号船員]";
	mes "お～い、君。";
	mes "ポートマラヤまで10,000Zeny";
	mes "なんだけどどうだい？";
	next;
	switch(select("ポートマラヤについて","ポートマラヤに行く","やめる")) {
	case 1:
		mes "[オフタラマ号船員]";
		mes "ポートマラヤは、アルベルタから";
		mes "南西方向に位置する小さな町だ。";
		next;
		mes "[オフタラマ号船員]";
		mes "しばらく航路が封鎖されていたんだが";
		mes "最近、また行けるようになったんだ。";
		next;
		mes "[オフタラマ号船員]";
		mes "前に行った時は";
		mes "まるで故郷を思わせるような";
		mes "安らぎを感じる町だったよ。";
		mes "私もアルベルタに戻りたくないと";
		mes "思ってしまったほどだよ。";
		next;
		mes "[オフタラマ号船員]";
		mes "君もポートマラヤに行けば";
		mes "私が言っていることが";
		mes "理解できると思う。";
		close;
	case 2:
		if(Zeny < 10000) {
			mes "[オフタラマ号船員]";
			mes "おいおい、金が足りないぞ。";
			mes "ポートマラヤまでの距離を";
			mes "タダで乗せることはできない。";
			mes "悪いけど10,000Zenyを";
			mes "用意して来てくれ！ ";
			close;
		}
		mes "[オフタラマ号船員]";
		mes "よ～し";
		mes "ポートマラヤに出発!!";
		close2;
		set Zeny,Zeny-10000;
		warp "malaya.gat",271,55;
		end;
	case 3:
		mes "[オフタラマ号船員]";
		mes "最近の冒険者たちは";
		mes "とても忙しそうにしてるな。";
		mes "暇になったら来てくれ。";
		mes "ポートマラヤにでも遊びに行こう。";
		close;
	}
OnInit:
	waitingroom "ポートマラヤ行き",0;
	end;
}

malaya.gat,276,55,4	script	オフタラマ号船員	100,{
	if(MALAYA_1QUE < 2) {
		mes "[オフタラマ号船員]";
		mes "まだ町が騒がしいようだな。";
		mes "観光は終わったか？";
		mes "アルベルタに戻る船便は";
		mes "いつでもあるからな。";
	}
	else if(MALAYA_1QUE < 6) {
		mes "[オフタラマ号船員]";
		mes "ある冒険者のおかげで町の人々は";
		mes "少しは安心したようだ。";
		mes "アルベルタに戻るのか？";
	}
	else {
		mes "[オフタラマ号船員]";
		mes "君が望むならばアルベルタまで";
		mes "送ってあげよう。どうだ戻るか？";
	}
	next;
	if(select("戻る","戻らない") == 2) {
		mes "[オフタラマ号船員]";
		mes "わかった。";
		mes "アルベルタに戻りたくなったら";
		mes "また来てくれ。";
		close;
	}
	mes "[オフタラマ号船員]";
	mes "よし、アルベルタに出発!!";
	close2;
	warp "alberta.gat",192,217;
	end;
}

//============================================================
// warp
//------------------------------------------------------------
malaya.gat,178,211,0	script	旅館入り口	45,1,1,{
	if(MALAYA_1QUE < 2) {
		mes "‐扉が閉じられている。";
		mes "　住民はあなたを警戒しているようだ‐";
		close;
	}
	warp "ma_in01.gat",24,80;
	end;
}

malaya.gat,112,212,0	script	武器屋入り口	45,1,1,{
	if(MALAYA_1QUE < 6) {
		mes "‐扉が閉じられている。";
		mes "　住民はあなたを警戒しているようだ‐";
		close;
	}
	warp "ma_in01.gat",83,16;
	end;
}

malaya.gat,299,167,0	script	道具屋入り口	45,1,1,{
	if(MALAYA_1QUE < 6) {
		mes "‐扉が閉じられている。";
		mes "　住民はあなたを警戒しているようだ‐";
		close;
	}
	warp "ma_in01.gat",12,24;
	end;
}

malaya.gat,261,240,0	script	商家入り口	45,1,1,{
	if(MALAYA_1QUE < 6) {
		mes "‐扉が閉じられている。";
		mes "　住民はあなたを警戒しているようだ‐";
		close;
	}
	warp "ma_in01.gat",126,20;
	end;
}

malaya.gat,300,211,0	script	民家入り口	45,1,1,{
	if(MALAYA_1QUE < 2) {
		mes "‐扉が閉じられている。";
		mes "　住民はあなたを警戒しているようだ‐";
		close;
	}
	warp "ma_in01.gat",36,152;
	end;
}

malaya.gat,309,70,0	script	ペリー号入り口	45,1,1,{
	if(MALAYA_3QUE < 1) {
		mes "‐鍵がかかっていて";
		mes "　中に入れない‐";
		close;
	}
	warp "ma_in01.gat",108,92;
	end;
}

ma_dun01.gat,150,6,0	script	病院2階入口	45,1,1,{
	if(MALAYA_4QUE < 27) {
		mes "‐看護師ラズは、階段が";
		mes "　封鎖されていると言っていたが";
		mes "　通れるようだ‐";
		next;
		if(select("2階に行く","引き返す") == 2) {
			mes "‐あなたは階段に背を向けた‐";
			close;
		}
		mes "‐あなたは階段を上った‐";
		close2;
	}
	warp "ma_dun01_jp.gat",36,156;
	end;
}

//============================================================
// 旅館
//------------------------------------------------------------
ma_in01.gat,30,94,4	script	旅館の主	583,{
	if(MALAYA_1QUE < 6) {
		mes "[旅館の主]";
		mes "最近、町で噂になっている冒険者って";
		mes "あなたのことですよね？";
		mes "おかげ様で営業をすることが";
		mes "できるようになりました。";
		mes "ありがとうございます。";
	}
	else {
		mes "[旅館の主]";
		mes "いらっしゃいませ。";
		mes "ポートマラヤで最高の旅館";
		mes "コーラルリーフです";
	}
	next;
	mes "[旅館の主]";
	mes "休んでいかれるんですか？";
	mes "宿泊費は5000Zenyです。";
	next;
	switch(select("セーブする","休んでいく - 5000z","やめる")) {
	case 1:
		mes "[旅館の主]";
		mes "セーブしました。";
		mes "またお会いしましょう。";
		savepoint "ma_in01.gat",44,97;
		close;
	case 2:
		if(Zeny < 5000) {
			mes "[旅館の主]";
			mes "お客様、すみませんが";
			mes "宿泊費が足りないようです。";
			close;
		}
		mes "[旅館の主]";
		mes "ではゆっくり休んで下さい。";
		close2;
		set Zeny,Zeny-5000;
		warp "ma_in01.gat",43,98;
		percentheal 100,100;
		end;
	case 3:
		mes "[旅館の主]";
		mes "またのご来店をお待ちしております。";
		close;
	}
}

//============================================================
// ジプニードライバーNPC
//------------------------------------------------------------
function	script	MalayaJeepney	{
	set '@type,getarg(0);
	switch(select("搭乗する","ジプニー？","他のジプニーはありませんか？","今は乗りません")) {
	case 1:
		mes "[ジプニードライバー]";
		mes "どこにいきますか？";
		next;
		switch(select("病院前","北の住宅地","船着き場","ポートマラヤ出口","中央広場","武器防具屋前","道具屋前","ジプニーに乗り込む","やっぱりやめる")) {
		case 1:
			set '@x,66;
			set '@y,46;
			break;
		case 2:
			set '@x,183;
			set '@y,350;
			break;
		case 3:
			set '@x,258;
			set '@y,56;
			break;
		case 4:
			set '@x,361;
			set '@y,281;
			break;
		case 5:
			set '@x,239;
			set '@y,217;
			break;
		case 6:
			set '@x,119;
			set '@y,212;
			break;
		case 7:
			set '@x,292;
			set '@y,171;
			break;
		case 8:
			mes "[ジプニードライバー]";
			mes "では、楽しい時間をお送りください。";
			close2;
			warp "ma_zif0" +'@type+ ".gat",29,24;
			end;
		case 9:
			close;
		}
		mes "[ジプニードライバー]";
		mes "では、楽しい時間をお送りください。";
		close2;
		warp "malaya.gat",'@x,'@y;
		end;
	case 2:
		switch('@type) {
		case 1:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "では、説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーは元々、";
			mes "貨物用の車両だったのですが、";
			mes "乗り合いタクシーとして改造し、";
			mes "大衆交通手段となっています。";
			next;
			mes "[ジプニードライバー]";
			mes "改造する人の個性によって";
			mes "様々なデザインのジプニーを";
			mes "見ることができます。";
			close;
		case 2:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "では、説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーは元々、";
			mes "貨物用の車両だったのですが、";
			mes "乗り合いタクシーとして改造し、";
			mes "大衆交通手段となっています。";
			next;
			mes "[ジプニードライバー]";
			mes "このジプニーは私が改造しました。";
			mes "定員は少なめですが、";
			mes "重さで潰れたりはしませんよ。";
			close;
		case 3:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "では、説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーは元々、";
			mes "貨物用の車両だったのですが、";
			mes "乗り合いタクシーとして改造し、";
			mes "大衆交通手段となっています。";
			next;
			mes "[ジプニードライバー]";
			mes "改造する人の個性によって";
			mes "様々なデザインのジプニーを";
			mes "見ることができます。";
			mes "今やポートマラヤの名物です。";
			close;
		case 4:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーは元々、";
			mes "貨物用の車両だったのですが、";
			mes "乗り合いタクシーとして改造し、";
			mes "大衆交通手段となっています。";
			next;
			mes "[ジプニードライバー]";
			mes "ポートマラヤに来たからには";
			mes "ジプニーに乗らないと後悔しますよ。";
			close;
		case 5:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "まあ、サービスで説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーはポートマラヤを代表する";
			mes "大衆交通手段です。";
			mes "安全上の問題で、ジプニーごとに";
			mes "搭乗人数を調整しています。";
			next;
			mes "[ジプニードライバー]";
			mes "以前は、ジプニーに180人も";
			mes "乗る場合もあったといいますが、";
			mes "最近では、そんな大勢が乗ることは";
			mes "ありませんね。";
			close;
		case 6:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "旅行者へのご案内もドライバーの仕事！";
			mes "さっそく、ご説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "貨物用の車両を";
			mes "オシャレに改造したのがジプニーだ！";
			mes "もちろん、このジプニーは";
			mes "私が改造したんです。";
			mes "イケてるでしょう？";
			next;
			mes "[ジプニードライバー]";
			mes "たとえ、お客様が王侯貴族であっても";
			mes "私のジプニーを運転させるわけには";
			mes "いきませんよ。";
			close;
		case 7:
			mes "[ジプニードライバー]";
			mes "ジプニーはポートマラヤの";
			mes "大衆交通手段です。";
			mes "町のあちこちで見かけますし、";
			mes "なんといっても無料です！";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーによって定員がバラバラで";
			mes "統一感がありませんけど、";
			mes "誰も問題にしません。";
			mes "満員なら、他のジプニーに乗れば";
			mes "いいだけですからね。";
			close;
		case 8:
			mes "[ジプニードライバー]";
			mes "ジプニーは安全性が重視された";
			mes "大衆交通手段です。";
			next;
			mes "[ジプニードライバー]";
			mes "私のジプニーは、";
			mes "現在ポートマラヤでの最高等級";
			mes "「60人ジプニー賞」を貰っています！";
			next;
			mes "[ジプニードライバー]";
			mes "絶対!!　安全ですから";
			mes "心配しないで乗ってください。";
			close;
		case 9:
			mes "[ジプニードライバー]";
			mes "ポートマラヤの町は初めてですか？";
			mes "では、説明しましょう。";
			next;
			mes "[ジプニードライバー]";
			mes "ジプニーは元々";
			mes "貨物用の車両だったのですが、";
			mes "乗り合いタクシーとして改造し、";
			mes "大衆交通手段となっています。";
			next;
			mes "[ジプニードライバー]";
			mes "改造する人の個性によって";
			mes "様々なデザインのジプニーを";
			mes "見ることができます。";
			close;
		}
	case 3:
		mes "[ジプニードライバー]";
		mes "ここポートマラヤでは";
		mes "全部で9つのジプニーが運行中です。";
		next;
		mes "[ジプニードライバー]";
		mes "他のジプニーの位置を";
		mes "知りたいですか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[ジプニードライバー]";
			mes "わかりました。";
			mes "では、楽しい旅をお過ごしください！";
			close;
		}
		viewpoint 1,237,240,1,0xF7E009;
		viewpoint 1,67,44,2,0xF7E009;
		viewpoint 1,282,129,3,0xF7E009;
		viewpoint 1,134,250,4,0xF7E009;
		viewpoint 1,341,153,5,0xF7E009;
		viewpoint 1,293,290,6,0xF7E009;
		viewpoint 1,242,221,7,0xF7E009;
		viewpoint 1,62,245,8,0xF7E009;
		viewpoint 1,257,58,9,0xF7E009;
		mes "[ジプニードライバー]";
		mes "地図上に、ジプニーの位置を";
		mes "メモしておきました。";
		close;
	case 4:
		mes "[ジプニードライバー]";
		mes "ジプニーを利用したくなったら、";
		mes "近くのドライバーに";
		mes "声をかけてください。";
		close;
	}
}

malaya.gat,237,240,4	script	ジプニードライバー#01	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "うううううっ……";
		mes "怖い……怖いよ……";
		mes "どうしてこんなことになったんだ？";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "まだ町が物騒で……";
		mes "ジプニーを運行していいのか";
		mes "わからない……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "ははは、いらっしゃいませ。";
	mes "ジプニーを運行している";
	mes "^1561EAボル^000000といいます。";
	next;
	callfunc "MalayaJeepney",1;
	end;
}

malaya.gat,67,44,4	script	ジプニードライバー#02	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "い……いったい……";
		mes "病院で何が起こっているんだ？";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "病院から聞こえる泣き声が";
		mes "小さくなってきたようだ……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "ジプニーを運転している";
	mes "^1561EAチー^000000です。";
	mes "よろしく～";
	next;
	callfunc "MalayaJeepney",2;
	end;
}

malaya.gat,282,129,4	script	ジプニードライバー#03	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "よそ者に話すことはありません……";
		mes "ムンバキ様なら";
		mes "きっとこの事態を解決するための";
		mes "方法を知っているに違いない……";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "最近ムンバキ様に会ったというのは";
		mes "君たちなのか……？";
		mes "いや、そんな人物が";
		mes "こんなところにいるわけはないか。";
		mes "……ということは、おばけなのか？";
		mes "うわああ……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "ジプニーを運転している";
	mes "^1561EAトップ^000000です。";
	next;
	callfunc "MalayaJeepney",3;
	end;
}

malaya.gat,134,250,6	script	ジプニードライバー#04	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "あ……あっちに……行ってくれ……";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "うわああ……";
		mes "びっくりしたじゃないか……";
		mes "あっちに行けよ……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "怖がりなので安全運転を心がけている";
	mes "ジプニードライバー";
	mes "^1561EAブラブ^000000です。";
	next;
	callfunc "MalayaJeepney",4;
	end;
}

malaya.gat,341,153,4	script	ジプニードライバー#05	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "ま……町に悪霊が……";
		mes "何だ……君も悪霊にやられたのか？";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "悪霊が減ったのか……？";
		mes "少し町が静かになったようだ。";
		close;
	}
	mes "[ジプニードライバー]";
	mes "ジプニーを運転している";
	mes "^1561EAリビル^000000です。";
	next;
	callfunc "MalayaJeepney",5;
	end;
}

malaya.gat,293,290,6	script	ジプニードライバー#06	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "け……警備隊……";
		mes "警備隊はいったい何をしているんだ？";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "やっと警備隊が動き出したのか？";
		mes "とりあえずこれで何とかなるのか……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "与えられた仕事は的確に処理する";
	mes "ジプニードライバー";
	mes "^1561EAガード^000000です。";
	next;
	callfunc "MalayaJeepney",6;
	end;
}

malaya.gat,242,221,4	script	ジプニードライバー#07	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "ああ……町じゅうがおばけだらけだ。";
		mes "やはり、指導者ムンバキ様が";
		mes "行かなければならないのか……？";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "おばけ……";
		mes "ムンバキ様なら、おばけを防ぐ方法を";
		mes "知っているはずだ……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "おばけを寄せ付けない";
	mes "ジプニーを運転している";
	mes "^1561EAホート^000000です。";
	next;
	callfunc "MalayaJeepney",7;
	end;
}

malaya.gat,62,245,6	script	ジプニードライバー#08	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "来るな～";
		mes "おばけなら来るな～";
		mes "人でも来るな～";
		mes "来るな～";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "おい……君……";
		mes "人だよね？";
		mes "おばけじゃないよね？";
		mes "そうだと言ってくれ……";
		mes "お願いだ……";
		close;
	}
	mes "[ジプニードライバー]";
	mes "ジプニーを運転している";
	mes "^1561EAムヤン^000000といいます。";
	mes "会えてうれしいです。";
	next;
	callfunc "MalayaJeepney",8;
	end;
}

malaya.gat,257,58,6	script	ジプニードライバー#09	582,{
	if(MALAYA_1QUE < 2) {
		mes "[ジプニードライバー]";
		mes "……外国から来た方ですね。";
		mes "町の中は危険なので";
		mes "気を付けてください。";
		close;
	}
	else if(MALAYA_1QUE < 6) {
		mes "[ジプニードライバー]";
		mes "相変わらず町は危険です。";
		mes "町が平穏になるまでは、";
		mes "ジプニーを出せません。";
		close;
	}
	mes "[ジプニードライバー]";
	mes "初めまして、";
	mes "ジプニーを運転している";
	mes "^1561EAグラマ^000000です。";
	next;
	callfunc "MalayaJeepney",9;
	end;
}

ma_zif01.gat,30,22,0	warp	jeepney01	1,1,malaya.gat,241,238
ma_zif02.gat,30,22,0	warp	jeepney02	1,1,malaya.gat,71,43
ma_zif03.gat,30,22,0	warp	jeepney03	1,1,malaya.gat,284,129
ma_zif04.gat,30,22,0	warp	jeepney04	1,1,malaya.gat,134,247
ma_zif05.gat,30,22,0	warp	jeepney05	1,1,malaya.gat,341,150
ma_zif06.gat,30,22,0	warp	jeepney06	1,1,malaya.gat,294,293
ma_zif07.gat,30,22,0	warp	jeepney07	1,1,malaya.gat,239,221
ma_zif08.gat,30,22,0	warp	jeepney08	1,1,malaya.gat,59,246
ma_zif09.gat,30,22,0	warp	jeepney09	1,1,malaya.gat,254,68

//============================================================
// ポートマラヤ室内NPC
//------------------------------------------------------------
ma_in01_jp.gat,81,22,5	script	悩む老女	575,{
	mes "[悩む老女]";
	mes "最近この辺りの魔物が増えてきておる。";
	next;
	mes "[悩む老女]";
	mes "おそらくこの世界で活動している";
	mes "悪魔たちの力が徐々に";
	mes "強くなってきているのじゃろう……。";
	next;
	if(select("悪魔に対抗するには？","無視する") == 2) {
		mes "[悩む老女]";
		mes "悪魔との戦に勝利するように……。";
		close;
	}
	if(countitem(6497) < 3 || Zeny < 1000) {
		mes "[悩む老女]";
		mes "古くから部族に";
		mes "伝わっている方法がある……。";
		next;
		mes "[悩む老女]";
		mes "古代精霊の力を呼びだし";
		mes "使用する方法なのじゃが、";
		mes "特別な材料が必要になる。";
		next;
		menu "その材料とは？",-;
		mes "[悩む老女]";
		mes "古代精霊の力を宿らせる";
		mes "小さなお守り3個と部族に伝わる";
		mes "特別な物が必要なのじゃが……。";
		next;
		mes "[悩む老女]";
		mes "その特別な物は今では";
		mes "もう手に入れることができん……。";
		next;
		menu "お金では買えない物なんですか？",-;
		mes "[悩む老女]";
		mes "その……ま、丸い物……それは何かね？";
		next;
		menu "ひょっとしてZenyのことですか？",-;
		mes "[悩む老女]";
		mes "部族に古くから伝わる物に";
		mes "よく似ている金属で";
		mes "作られているじゃないか。";
		next;
		mes "[悩む老女]";
		mes "そ、それが沢山あれば悪魔に対抗する";
		mes "古代精霊のお守りを作ることが";
		mes "できるかもしれん……。";
		next;
		mes "[悩む老女]";
		mes "もし……君が悪魔に対抗する力が";
		mes "足りなくなった時には";
		next;
		mes "[悩む老女]";
		mes "^FF0000小さなお守り3個^000000と";
		mes "その^FF0000Zenyという物を1000個^000000ほど";
		mes "持って来なさい……。";
		next;
		mes "[悩む老女]";
		mes "20分間、悪魔たちに10%程";
		mes "さらに強い攻撃をすることができる";
		mes "古代精霊のお守りを作ってやろう。";
		close;
	}
	mes "[悩む老女]";
	mes "悪魔に対抗する力が不足しているのか。";
	next;
	mes "[悩む老女]";
	mes "どうじゃ、";
	mes "^FF0000小さなお守り3個と1,000Zeny^000000で、";
	mes "20分間、悪魔たちに10%程";
	mes "さらに強い攻撃をすることができる";
	mes "^0000FF古代精霊のお守り^000000を作ってやろうか？";
	next;
	if(select("作ります","大丈夫です") == 2) {
		mes "[悩む老女]";
		mes "悪魔との戦に勝利するように……。";
		close;
	}
	if(checkitemblank() == 0) {
		mes "[悩む老女]";
		mes "所持品の種類数が多くて";
		mes "渡せないのう。";
		mes "種類数を減らしてからまた来なさい。";
		close;
	}
	misceffect 71,"";
	misceffect 9;
	delitem 6497,3;
	set Zeny,Zeny-1000;
	getitem 12775,1;
	mes "[悩む老女]";
	mes "悪魔との戦に勝利するように……。";
	close;
}

ma_in01_jp.gat,67,22,5	script	ティクバラン専門家	582,{
	if(checkquest(7406)) {
		mes "[ティクバラン専門家]";
		mes "悪霊の骨を分けてほしい？";
		mes "ああ、バンタイのエサに使うんだな。";
		next;
		mes "[ティクバラン専門家]";
		mes "でも、悪霊の骨はとても貴重な";
		mes "研究材料なんだ。";
		mes "手に入れるのも大変な物だから";
		mes "いつも分けてあげる時には代わりに";
		mes "私の研究を手伝って貰っているんだ。";
		next;
		menu "何をすればいいですか？",-;
		mes "[ティクバラン専門家]";
		mes "私はティクバランの研究をしている。";
		mes "今回は研究の一環として";
		mes "戦闘の記録をとりたいんだ。";
		mes "そこで、君にはティクバランと";
		mes "戦闘をしてきてほしい。";
		next;
		mes "[ティクバラン専門家]";
		mes "そうだな、ティクバランを";
		mes "^FF000020匹^000000倒せば十分だろう。";
		mes "君はとても強そうだし、楽勝だろ？";
		mes "それじゃあ、よろしく頼むよ。";
		delquest 7406;
		setquest 106176;
		close;
	}
	if(checkquest(106176)) {
		if(!(checkquest(106176) & 0x4)) {
			mes "[ティクバラン専門家]";
			mes "どうした？";
			mes "早くティクバランを^FF000020匹^000000";
			mes "倒してきてくれ。";
			mes "よろしく頼むよ。";
			close;
		}
		mes "[ティクバラン専門家]";
		mes "お、ティクバランとの戦闘記録を";
		mes "持ってきてくれたのか。";
		next;
		mes "[ティクバラン専門家]";
		mes "おお！　これは凄い！";
		mes "君のおかげで、実に良い研究が";
		mes "出来そうだ。";
		mes "本当にありがとう!!";
		next;
		menu "悪霊の骨は？",-;
		mes "[ティクバラン専門家]";
		mes "ああ、すまない。";
		mes "ティクバランの事となると";
		mes "少し興奮してしまうんだ。";
		mes "ほら、これが悪霊の骨だ。";
		mes "持っていくといい。";
		next;
		if(checkitemblank() == 0) {
			mes "[ティクバラン専門家]";
			mes "おや、荷物が多くて渡せないな。";
			mes "少し荷物を減らしてきてくれ。";
			close;
		}
		delquest 106176;
		setquest 72060;
		getitem 6507,10;
		mes "[ティクバラン専門家]";
		mes "悪霊の骨が必要になったら";
		mes "また訪ねてくるといい。";
		mes "もちろん、手伝いはして貰うけどね。";
		close;
	}
	mes "[ティクバラン専門家]";
	mes "私は人生の90%を";
	mes "ティクバラン研究のために";
	mes "力を入れて来た。";
	mes "ティクバランのことなら";
	mes "なんでも聞いてくれ！";
	next;
	switch(select("まだ若いですね","ティクバラン？","ティクバランを捕まえる方法は？")) {
	case 1:
		mes "[ティクバラン専門家]";
		mes "そ、そんなことはない！";
		mes "見た目だけで判断して貰っては困る。";
		next;
		mes "[ティクバラン専門家]";
		mes "私は童顔なので見た目よりは";
		mes "歳をとっているんだ。";
		next;
		menu "………",-;
		mes "[ティクバラン専門家]";
		mes "信じろ!!　信じる者には福がある";
		mes "というじゃないか。";
		close;
	case 2:
		mes "[ティクバラン専門家]";
		mes "ふふふ……よくぞ聞いてくれた。";
		mes "それこそ私の専門分野だ。";
		mes "何でも聞いていいぞ。";
		while(1) {
			next;
			switch(select("聞きたいことはない","特性","外見","噂","生息地")) {
			case 1:
				mes "[ティクバラン専門家]";
				mes "また気になることでもあったら";
				mes "遊びに来るといい。";
				close;
			case 2:
				mes "[ティクバラン専門家]";
				mes "ティクバランたちは";
				mes "目の前に旅行者たちが現れると";
				mes "その旅行者がどこに行っても";
				mes "いくら遠くに行っても";
				mes "いつのまにか道を彷徨い続けるように";
				mes "呪いをかけてしまうんだ。";
				next;
				mes "[ティクバラン専門家]";
				mes "まあ、それを避ける方法もある。";
				mes "裏返しにシャツを着ればいい。";
				mes "シャツが無ければ上着を裏返しにして";
				mes "着てもいいぞ。";
				next;
				mes "[ティクバラン専門家]";
				mes "または道を進む時に、";
				mes "ティクバランたちの";
				mes "気を引かないように静かに進めばいい。";
				next;
				mes "[ティクバラン専門家]";
				mes "ははは、冒険者たちが道を進むときは";
				mes "静かに通らないって？";
				next;
				mes "[ティクバラン専門家]";
				mes "そればっかりは私の研究でも";
				mes "どうしようもないな。";
				break;
			case 3:
				mes "[ティクバラン専門家]";
				mes "ティクバランは";
				mes "大きな背と^AAAAAA(うらやましい……)^000000";
				mes "不自然なほど長い手足をしている。";
				mes "しゃがみこんで座っている時は";
				mes "膝が頭の上にあるくらいだ。";
				next;
				mes "[ティクバラン専門家]";
				mes "そして、馬のような頭と足をしている。";
				mes "　";
				mes "こんな姿のせいで";
				mes "ティクバランは";
				mes "地獄から送られて来た子供、";
				mes "などと言われている。";
				break;
			case 4:
				mes "[ティクバラン専門家]";
				mes "ティクバランに関する";
				mes "面白い噂もたくさんある。";
				next;
				mes "[ティクバラン専門家]";
				mes "その中の一つはティクバランたちが";
				mes "自然を崇拝している、ある王国の守護者";
				mes "という説だ。";
				next;
				mes "[ティクバラン専門家]";
				mes "その王国に敵対していたり";
				mes "悪意を持って接近する旅行者を見ると、";
				mes "同じ道を彷徨い続けるように";
				mes "呪いをかけるらしい。";
				next;
				mes "[ティクバラン専門家]";
				mes "また昔の童話ではティクバランが";
				mes "人間に変身したり、姿を透明に";
				mes "することもできると書かれているが、";
				mes "実際に確認はされてはいない。";
				break;
			case 5:
				mes "[ティクバラン専門家]";
				mes "ティクバランの主な生息地は、";
				mes "人気が少なく木や草で覆われている";
				mes "暗い場所。";
				next;
				mes "[ティクバラン専門家]";
				mes "例えば橋の下だったり";
				mes "バナナ畑、竹林、そして";
				mes "大きな木の下に生息しているらしい。";
				next;
				mes "[ティクバラン専門家]";
				mes "これは私の予想なんだが";
				mes "そのような場所に住んでいる理由は";
				mes "人々にいたずらしやすい場所だから";
				mes "ではないかと考えている。";
				break;
			}
			next;
			mes "[ティクバラン専門家]";
			mes "説明はこれくらいで十分だろう。";
			mes "これ以上説明しても";
			mes "難しい言葉が出て来るから";
			mes "話しても理解しにくいだろうしな。";
			next;
			mes "[ティクバラン専門家]";
			mes "まだ他に聞きたいことはあるか？";
		}
	case 3:
		mes "[ティクバラン専門家]";
		mes "ふふふ、この私の偉大さが";
		mes "やっとわかったようだな？";
		next;
		mes "[ティクバラン専門家]";
		mes "本来、ティクバランを捕まえることは";
		mes "とても難しく、命がけなんだけど";
		mes "実は、簡単にティクバランを";
		mes "捕まえる方法があるんだ。";
		next;
		mes "[ティクバラン専門家]";
		mes "それはこの私が開発した";
		mes "^F80835ティクバランベルト^000000を使うのだ。";
		next;
		if(countitem(6496) < 3 || countitem(6497) < 5) {
			mes "[ティクバラン専門家]";
			mes "もちろんタダで、というわけにはいかない。";
			mes "^F80835ティクバランの背骨3個^000000と";
			mes "^F80835小さなお守り5個^000000を";
			mes "持ってきたら交換してやろう。";
			close;
		}
		mes "[ティクバラン専門家]";
		mes "お、ティクバランベルトの材料の";
		mes "^F80835ティクバランの背骨3個^000000と";
		mes "^F80835小さなお守り5個^000000を";
		mes "持っているじゃないか。";
		next;
		mes "[ティクバラン専門家]";
		mes "^F80835ティクバランベルト^000000を使えば";
		mes "ティクバランを簡単に";
		mes "捕まえることができる。";
		mes "もちろん必ず成功するわけではないが。";
		mes "　";
		mes "どうだ？　作ってやろうか？";
		next;
		if(select("作って下さい","私は自分の力で捕まえる") == 2) {
			mes "[ティクバラン専門家]";
			mes "ティクバランを捕まえるのは";
			mes "命がけだ。";
			mes "素直に^F80835ティクバランベルト^000000を";
			mes "使った方が良いぞ。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[ティクバラン専門家]";
			mes "所持品の種類数が多くて";
			mes "そのままじゃ渡せないな。";
			mes "種類数を減らしてからまた来いよ。";
			close;
		}
		delitem 6496,3;
		delitem 6497,5;
		getitem 12699,1;
		mes "[ティクバラン専門家]";
		mes "ほうりゃ！　しゃ～！";
		misceffect 143;
		next;
		mes "[ティクバラン専門家]";
		mes "^F80835ティクバランベルト^000000が";
		mes "完成したぞ！";
		mes "さあ、受け取りたまえ。";
		close;
	}
}

//============================================================
// 謎の生物NPC
//------------------------------------------------------------
ma_fild01.gat,74,367,6	script	謎の生物#01	572,2,2,{
	end;
OnTouch:
	if(getcharid(1)) {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	else if($MalayaName$[3] == strcharinfo(0) || $MalayaName$[5] == strcharinfo(0)) {
		mes "‐謎の生物はあなたをちらっと";
		mes "　見た後に顔を赤くして消えた‐";
	}
	else if(rand(3) == 1) {
		set $MalayaName$[3],strcharinfo(0);
		mes "‐謎の生物はあなたをちらっと";
		mes "　見てから消えた‐";
	}
	else {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	close2;
	hideonnpc strnpcinfo(0);
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"02","03","04"; break;
	case 2: setarray '@npc$,"01","03","04"; break;
	case 3: setarray '@npc$,"01","02","04"; break;
	case 4: setarray '@npc$,"01","02","03"; break;
	case 5: setarray '@npc$,"06","07","08"; break;
	case 6: setarray '@npc$,"05","07","08"; break;
	case 7: setarray '@npc$,"05","06","08"; break;
	case 8: setarray '@npc$,"05","06","07"; break;
	case 9: setarray '@npc$,"10","11"; break;
	case 10: setarray '@npc$,"09","11"; break;
	case 11: setarray '@npc$,"09","10"; break;
	}
	hideoffnpc "謎の生物#" + '@npc$[rand(getarraysize('@npc$))];
	end;
OnInit:
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"01","02","03","04"; break;
	case 5: setarray '@npc$,"05","06","07","08"; break;
	case 9: setarray '@npc$,"09","10","11"; break;
	default: end;
	}
	set '@size,getarraysize('@npc$);
	set '@rand,rand('@size);
	for(set '@i,0; '@i<'@size; set '@i,'@i+1) {
		if('@i == '@rand)
			hideoffnpc "謎の生物#" +'@npc$['@i];
		else
			hideonnpc "謎の生物#" +'@npc$['@i];
	}
	end;
}

ma_fild01.gat,109,116,4		script	謎の生物#02	572,2,2,{
	end;
OnTouch:
	if(!getcharid(1)) {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	else if($MalayaName$[3] == strcharinfo(0) || $MalayaName$[5] == strcharinfo(0)) {
		mes "‐謎の生物はあなたをちらっと";
		mes "　見た後に顔を赤くして消えた‐";
	}
	else if(rand(3) == 1) {
		set $MalayaName$[3],strcharinfo(0);
		mes "‐謎の生物はあなたをちらっと";
		mes "　見てから消えた‐";
	}
	else {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	close2;
	hideonnpc strnpcinfo(0);
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"02","03","04"; break;
	case 2: setarray '@npc$,"01","03","04"; break;
	case 3: setarray '@npc$,"01","02","04"; break;
	case 4: setarray '@npc$,"01","02","03"; break;
	case 5: setarray '@npc$,"06","07","08"; break;
	case 6: setarray '@npc$,"05","07","08"; break;
	case 7: setarray '@npc$,"05","06","08"; break;
	case 8: setarray '@npc$,"05","06","07"; break;
	case 9: setarray '@npc$,"10","11"; break;
	case 10: setarray '@npc$,"09","11"; break;
	case 11: setarray '@npc$,"09","10"; break;
	}
	hideoffnpc "謎の生物#" + '@npc$[rand(getarraysize('@npc$))];
	end;
}

ma_fild01.gat,280,150,6		duplicate(謎の生物#02)	謎の生物#03	572,2,2
ma_fild01.gat,309,221,6		duplicate(謎の生物#02)	謎の生物#04	572,2,2
ma_fild02.gat,282,41,4		duplicate(謎の生物#01)	謎の生物#05	572,2,2

ma_fild02.gat,246,324,4		script	謎の生物#06	572,2,2,{
	end;
OnTouch:
	if(!getcharid(1)) {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	else if($MalayaName$[3] == strcharinfo(0) || $MalayaName$[5] == strcharinfo(0)) {
		mes "‐謎の生物はあなたをちらっと";
		mes "　見た後に顔を赤くして消えた‐";
	}
	else if(rand(3) == 1) {
		set $MalayaName$[4],strcharinfo(0);
		mes "‐謎の生物はあなたをちらっと";
		mes "　見てから消えた‐";
	}
	else {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	close2;
	hideonnpc strnpcinfo(0);
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"02","03","04"; break;
	case 2: setarray '@npc$,"01","03","04"; break;
	case 3: setarray '@npc$,"01","02","04"; break;
	case 4: setarray '@npc$,"01","02","03"; break;
	case 5: setarray '@npc$,"06","07","08"; break;
	case 6: setarray '@npc$,"05","07","08"; break;
	case 7: setarray '@npc$,"05","06","08"; break;
	case 8: setarray '@npc$,"05","06","07"; break;
	case 9: setarray '@npc$,"10","11"; break;
	case 10: setarray '@npc$,"09","11"; break;
	case 11: setarray '@npc$,"09","10"; break;
	}
	hideoffnpc "謎の生物#" + '@npc$[rand(getarraysize('@npc$))];
	end;
}

ma_fild02.gat,71,296,6		duplicate(謎の生物#06)	謎の生物#07	572,2,2
ma_fild02.gat,32,263,4		duplicate(謎の生物#06)	謎の生物#08	572,2,2

ma_scene01.gat,195,92,4		script	謎の生物#09	572,2,2,{
	end;
OnTouch:
	if(getcharid(1)) {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	else if($MalayaName$[3] == strcharinfo(0) || $MalayaName$[5] == strcharinfo(0)) {
		mes "‐謎の生物はあなたをちらっと";
		mes "　見た後に顔を赤くして消えた‐";
	}
//	else if($MalayaName$[2] == strcharinfo(0)) {
//		mes "‐謎の生物はあなたをちらっと";
//		mes "　見てから消えた‐";
//	}
	else if(rand(3) == 1) {
		set $MalayaName$[5],strcharinfo(0);
		mes "‐謎の生物はあなたをちらっと";
		mes "　見てから消えた‐";
	}
	else {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	close2;
	hideonnpc strnpcinfo(0);
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"02","03","04"; break;
	case 2: setarray '@npc$,"01","03","04"; break;
	case 3: setarray '@npc$,"01","02","04"; break;
	case 4: setarray '@npc$,"01","02","03"; break;
	case 5: setarray '@npc$,"06","07","08"; break;
	case 6: setarray '@npc$,"05","07","08"; break;
	case 7: setarray '@npc$,"05","06","08"; break;
	case 8: setarray '@npc$,"05","06","07"; break;
	case 9: setarray '@npc$,"10","11"; break;
	case 10: setarray '@npc$,"09","11"; break;
	case 11: setarray '@npc$,"09","10"; break;
	}
	hideoffnpc "謎の生物#" + '@npc$[rand(getarraysize('@npc$))];
	end;
OnInit:
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"01","02","03","04"; break;
	case 5: setarray '@npc$,"05","06","07","08"; break;
	case 9: setarray '@npc$,"09","10","11"; break;
	default: end;
	}
	set '@size,getarraysize('@npc$);
	set '@rand,rand('@size);
	for(set '@i,0; '@i<'@size; set '@i,'@i+1) {
		if('@i == '@rand)
			hideoffnpc "謎の生物#" +'@npc$['@i];
		else
			hideonnpc "謎の生物#" +'@npc$['@i];
	}
	end;
}

ma_scene01.gat,158,139,4	script	謎の生物#10	572,2,2,{
	end;
OnTouch:
	if(!getcharid(1)) {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	else if($MalayaName$[3] == strcharinfo(0) || $MalayaName$[5] == strcharinfo(0)) {
		mes "‐謎の生物はあなたをちらっと";
		mes "　見た後に顔を赤くして消えた‐";
	}
//	else if($MalayaName$[2] == strcharinfo(0)) {
//		mes "‐謎の生物はあなたをちらっと";
//		mes "　見てから消えた‐";
//	}
	else if(rand(3) == 1) {
		set $MalayaName$[5],strcharinfo(0);
		mes "‐謎の生物はあなたをちらっと";
		mes "　見てから消えた‐";
	}
	else {
		mes "‐謎の生物はあなたを見て";
		mes "　逃げだした‐";
	}
	close2;
	hideonnpc strnpcinfo(0);
	set '@num,strnpcinfo(2);
	switch('@num) {
	case 1: setarray '@npc$,"02","03","04"; break;
	case 2: setarray '@npc$,"01","03","04"; break;
	case 3: setarray '@npc$,"01","02","04"; break;
	case 4: setarray '@npc$,"01","02","03"; break;
	case 5: setarray '@npc$,"06","07","08"; break;
	case 6: setarray '@npc$,"05","07","08"; break;
	case 7: setarray '@npc$,"05","06","08"; break;
	case 8: setarray '@npc$,"05","06","07"; break;
	case 9: setarray '@npc$,"10","11"; break;
	case 10: setarray '@npc$,"09","11"; break;
	case 11: setarray '@npc$,"09","10"; break;
	}
	hideoffnpc "謎の生物#" + '@npc$[rand(getarraysize('@npc$))];
	end;
}

ma_scene01.gat,167,112,6	duplicate(謎の生物#10)	謎の生物#11	572,2,2

//============================================================
// 噂話NPC
//------------------------------------------------------------
malaya.gat,227,311,4	script	お婆ちゃん	575,{
	if(MALAYA_1QUE < 2) {
		mes "[お婆ちゃん]";
		mes "外から来たのかい？";
		mes "町の様子が変だから気を付けなさい。";
		next;
		mes "[お婆ちゃん]";
		mes "うちの嫁が妊娠中で大変なのよ。";
		mes "何事もなければいいのだけれど……。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[お婆ちゃん]";
		mes "この町の外から来た人が";
		mes "頑張ってくれているらしいよ。";
		next;
		mes "[お婆ちゃん]";
		mes "これでうちの嫁も安心だねえ。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[お婆ちゃん]";
			mes "最近、マナナンガルが好きで";
			mes "追っている";
			mes $MalayaName$['@rand];
			mes "という方がいましたよ。";
			next;
			mes "[お婆ちゃん]";
			mes "叶う事のない恋だけど";
			mes "応援してあげないとね。";
			close;
		}
	case 2:
		mes "[お婆ちゃん]";
		mes "嫁が妊娠をしているから心配なんだよ。";
		mes "マナナンガルが嫁に手を出さなければ";
		mes "いいのに……。";
		next;
		menu "マナナンガル？",-;
		mes "[お婆ちゃん]";
		mes "あんた、町の外から来た人かい？";
		mes "外から来た人でも気を付けなければ";
		mes "ならないからね……。";
		mes "理由を教えてあげるよ。";
		next;
		mes "[お婆ちゃん]";
		mes "マナナンガルは昔々ポートマラヤに";
		mes "住んでいた女性だったんだよ。";
		mes "良い男と出会って結婚もして、";
		mes "子供も出来たんだよ。";
		next;
		mes "[お婆ちゃん]";
		mes "だけど、みんなが幸せになるとは";
		mes "限らないだろう？";
		mes "その夫婦は結婚後に上手くいかなくて、";
		mes "結局別れてしまったんじゃ。";
		next;
		menu "可哀想ですね",-;
		mes "[お婆ちゃん]";
		mes "ほんとにねぇ……";
		mes "やがて、その女性は";
		mes "幸せな家族に嫉妬をするあまり";
		mes "悪霊マナナンガルとなり";
		mes "幸せそうな家族をみると";
		mes "子供を奪って行くようになったんだ。";
		next;
		mes "[お婆ちゃん]";
		mes "もし夜中にポートマラヤを";
		mes "歩き回っていて";
		mes "チクチクまたはワクワクという";
		mes "音がしたら、マナナンガルが";
		mes "動き回っている音だから";
		mes "注意した方がいいよ。";
		close;
	}
}

malaya.gat,189,263,4	script	太鼓を持った青年	578,{
	if(MALAYA_1QUE < 2) {
		emotion 23;
		mes "[太鼓を持った青年]";
		mes "うわああ……。";
		mes "この雰囲気はまるで";
		mes "あの時と一緒じゃないか……。";
		next;
		emotion 23;
		mes "[太鼓を持った青年]";
		mes "月が飲まれたあの時と……";
		mes "うわああ……。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[太鼓を持った青年]";
		mes "名前は知らないが";
		mes "ある冒険者のおかげで";
		mes "町が落ち着いてきたようなんだ。";
		next;
		emotion 54;
		mes "[太鼓を持った青年]";
		mes "ふうう……。";
		mes "私はまたバコナワが出たのかと";
		mes "思ったよ……。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[太鼓を持った青年]";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "バコナワが月を飲み込むのを";
			mes "防いだらしい。凄いよな。";
			mes "おかげで安心して暮らせるよ。";
			close;
		}
	case 2:
		mes "[太鼓を持った青年]";
		mes "ポートマラヤではバコナワのことを";
		mes "月を飲み込む怪物とも呼んでいる。";
		next;
		mes "[太鼓を持った青年]";
		mes "しかし、私は知っている……。";
		mes "奴は人を飲み込む怪物にも";
		mes "なれることを……。";
		next;
		menu "危険な怪物ですね",-;
		emotion 29;
		mes "[太鼓を持った青年]";
		mes "ふふふ……ところがだ、";
		mes "バコナワから身を守る方法もあるんだ。";
		next;
		mes "[太鼓を持った青年]";
		mes "月を6個も飲み込んだ恐ろしい奴にも";
		mes "弱点はあるということだ。";
		next;
		menu "その弱点とは？",-;
		mes "[太鼓を持った青年]";
		mes "奴はうるさい音……ノイズに弱い。";
		mes "奴が月を飲み込もうとする";
		mes "まさにその時!!";
		next;
		mes "[太鼓を持った青年]";
		mes "なんでもかまわない!!";
		mes "鍋、太鼓、フライパンなど";
		mes "なんでもいいから叩くんだ!!";
		next;
		mes "[太鼓を持った青年]";
		mes "そうすれば奴はびっくりして";
		mes "月を吐き出して逃げてしまう。";
		next;
		mes "[太鼓を持った青年]";
		mes "君も太鼓ひとつくらいは";
		mes "持って歩いてた方がいいよ。";
		close;
	}
}

malaya.gat,270,59,4	script	港の警備隊員	570,{
	if(MALAYA_1QUE < 2) {
		emotion 19;
		mes "[港の警備隊員]";
		mes "町の様子が慌ただしいというのに";
		mes "非番だからって休んでて";
		mes "いいんですかね？";
		close;
	}
	if(MALAYA_1QUE < 6) {
		emotion 22;
		mes "[港の警備隊員]";
		mes "町の様子は少し落ち着いてきたけど、";
		mes "まだ安心できないのでなるべく夜は";
		mes "外を歩き回らないようにしてください。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[港の警備隊員]";
			mes $MalayaName$['@rand];
			mes "という冒険者が、";
			mes "ブワヤに捕まったけど";
			mes "無事に帰って来たらしいです。";
			mes "すごい実力を持っているみたいですね。";
			close;
		}
	case 2:
		emotion 23;
		mes "[港の警備隊員]";
		mes "うん!!　港は以上なし!!";
		next;
		mes "[港の警備隊員]";
		mes "ん？　あなたでしたか。";
		mes "びっくりした。";
		mes "隊長かと思いましたよ。";
		next;
		mes "[港の警備隊員]";
		mes "あ！　そうだ！";
		mes "旅行者に知らせている";
		mes "通達があります。";
		next;
		menu "どんな通達ですか？",-;
		mes "[港の警備隊員]";
		mes "夜にモンスターがうろついているので";
		mes "気を付けろとのことです。";
		next;
		mes "[港の警備隊員]";
		mes "特にワクワクという";
		mes "モンスターが頻繁に出没するので";
		mes "注意しろとも言われました。";
		next;
		if(select("わかった","対処方法はないのか？") == 1) {
			mes "[港の警備隊員]";
			mes "夜には気を付けて！";
			close;
		}
		mes "[港の警備隊員]";
		mes "ワクワクの羽の音が";
		mes "遠くから聞こえたら急いで周辺の建物に";
		mes "入るようにした方がいいですよ。";
		next;
		emotion 20;
		mes "[港の警備隊員]";
		mes "だけど、羽の音が小さく聞こえたり";
		mes "ほとんど聞こえなかったら……。";
		mes "襲ってくる直前らしいですよ。";
		mes "あとは幸運を祈るしかありません。";
		close;
	}
}

malaya.gat,88,252,4	script	少女	576,{
	if(MALAYA_1QUE < 2) {
		mes "[少女]";
		mes "怖いです。";
		mes "森の妖精様を見に行かなきゃ";
		mes "ならないのに……。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[少女]";
		mes "えへへ～。";
		mes "町がもう少し落ち着いたら";
		mes "森の妖精様を見に行けるみたいです。";
		mes "お父さんが言ってました！";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[少女]";
			mes "少し前に";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "面白い話をして行きました。";
			next;
			mes "[少女]";
			mes "カタコンベで狩りをしてると肩こんべ！";
			mes "えへへ……面白くありませんか？";
			mes $MalayaName$['@rand];
			mes "という方は";
			mes "本当に面白い方のようです。";
			close;
		}
	case 2:
		mes "[少女]";
		mes "森の妖精様と仲良くすると";
		mes "病気にかからないと";
		mes "お父さんが言っていましたよ。";
		next;
		menu "森の妖精様？",-;
		mes "[少女]";
		mes "エンカント様です！";
		mes "森の大きな木や岩に住んでいる";
		mes "妖精様です。";
		next;
		mes "[少女]";
		mes "男の妖精様も女の妖精様もいるけど";
		mes "男の妖精様が最も綺麗らしいです。";
		mes "どうしてでしょう？";
		close;
	}
}

malaya.gat,219,92,6	script	ちびっ子	577,{
	if(MALAYA_1QUE < 2) {
		mes "[ちびっ子]";
		mes "お母さんが、危険だから";
		mes "外で遊ぶなって言うの。";
		mes "なんでだろう？";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[ちびっ子]";
		mes "お母さんが、ポートマラヤから";
		mes "離れなければ、遊んでもいいって！";
		next;
		mes "[ちびっ子]";
		mes "へへへ、最初から";
		mes "ポートマラヤの外に出る気は";
		mes "無かったけどね。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[ちびっ子]";
			mes "バリオ・マヒワガでジェジェリンの";
			mes "帽子を奪った人がいるって";
			mes "ウワサがあったんだ。";
			next;
			mes "[ちびっ子]";
			mes "モンスターの帽子を奪うなんて";
			mes $MalayaName$['@rand];
			mes "って人は";
			mes "お金がなかったのかな？";
			next;
			mes "[ちびっ子]";
			mes "あ！";
			mes "この話は秘密だったんだ！";
			mes "今の話は聞かなかったことに";
			mes "してほしいな。";
			close;
		}
	case 2:
		mes "[ちびっ子]";
		mes "このままじゃ町中の帽子が";
		mes "誰かに盗まれちゃうよ～。";
		next;
		mes "[ちびっ子]";
		mes "昨日、お母さんが洗ってくれた帽子が";
		mes "なくなったんだ。";
		mes "この前は隣の家の洗濯物からも帽子が";
		mes "無くなったらしいんだけど。";
		next;
		mes "[ちびっ子]";
		mes "もしかして……。";
		mes "ジェジェリンが盗んでいったのかな？";
		next;
		mes "[ちびっ子]";
		mes "この前、バリオ・マヒワガにいる";
		mes "友達の所に遊びに行った時";
		mes "無くなった帽子をかぶっていた";
		mes "ジェジェリンを見た気がする……。";
		close;
	}
}

malaya.gat,363,283,4	script	住民	582,{
	if(MALAYA_1QUE < 2) {
		mes "[住民]";
		mes "うむ……魔女の呪いを";
		mes "気を付けなければならない時期が";
		mes "来たのか……。";
		next;
		mes "[住民]";
		mes "マンククーラムの針には";
		mes "気を付けなさい。";
		mes "異邦人よ……。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[住民]";
		mes "ポートマラヤへようこそ。";
		mes "異邦人よ……。";
		next;
		mes "[住民]";
		mes "最近は町の様子がおかしいから";
		mes "もし赤い目をしている人を見かけたら";
		mes "その目を見ないようにしなさい……。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,5)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[住民]";
			mes "夜に町を歩き回る時は気を付けなさい。";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "ワクワクにやられたらしい。";
			close;
		}
	case 2:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[住民]";
			mes $MalayaName$['@rand];
			mes "という冒険者が、";
			mes "ティクバランを手懐けることに";
			mes "成功したという噂を聞いたが、";
			mes "本当ならばに凄いな。";
			next;
			mes "[住民]";
			mes "私もティクバランを";
			mes "手懐けてみたいものだ。";
			close;
		}
	case 3:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[住民]";
			mes "ブギスギスを見かけましたか。";
			mes "最近";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "ブギスギスをイジメている";
			mes "みたいなんです。";
			close;
		}
	case 4:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[住民]";
			mes "もし町の外に出ることがあるようなら、";
			mes "チャナックには気を付けなさい。";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "チャナックに騙され怪我をして、";
			mes "病院に運ばれたという噂がある。";
			close;
		}
	case 5:
		mes "[住民]";
		mes "町の様子が慌ただしい。";
		mes "マンククーラムが来ているのかも";
		mes "しれない。";
		next;
		menu "マンククーラム？",-;
		mes "[住民]";
		mes "魔女と呼ばれているモンスターだ。";
		mes "人と姿が似ていて、服も着ている。";
		next;
		mes "[住民]";
		mes "すれ違った人の人形を作り、";
		mes "針で刺し呪いをかけるんだ。";
		next;
		menu "区別する方法はないんですか？",-;
		mes "[住民]";
		mes "マンククーラムはみんな";
		mes "赤い目をしている。";
		mes "そこで区別することができる。";
		next;
		mes "[住民]";
		mes "ただし、ここにも注意することがある。";
		next;
		mes "[住民]";
		mes "マンククーラムの赤い目を";
		mes "長い間、見つめていると";
		mes "マンククーラムに憑りつかれてしまう。";
		next;
		mes "[住民]";
		mes "もし会うことになったら";
		mes "目を長くみないように";
		mes "注意したほうがいい。";
		close;
	}
}

malaya.gat,41,127,6	script	老人	574,{
	if(MALAYA_1QUE < 2) {
		mes "[老人]";
		mes "今のように町が荒れている時に";
		mes "異邦人が来るのは、";
		mes "正直あまり喜ばしいことではないのぅ。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[老人]";
		mes "君も本当に運がない人だね。";
		mes "よりによって町が荒れていて";
		mes "歓迎されることもない時期に来るとは。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,2)) {
	case 1:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[老人]";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "町にゼロピーを捨てたらしい。";
			next;
			mes "[老人]";
			mes "ゼロピーひとつも";
			mes "大事にできない方のようだよ。";
			close;
		}
	case 2:
		mes "[老人]";
		mes "古い木を切る時は、";
		mes "ビョンウンゴが住んでいないか";
		mes "注意したほうがいい。";
		next;
		mes "[老人]";
		mes "ビョンウンゴが住んでいる木を";
		mes "建物の柱で使用すると";
		mes "恐ろしいことが起きてしまうんだよ。";
		next;
		menu "何が起きるんですか？",-;
		mes "[老人]";
		mes "ビョンウンゴからすれば";
		mes "住んでいた家を失ったのも同然だから、";
		mes "人間に対する復讐心が強くなるんだ。";
		next;
		mes "[老人]";
		mes "もし柱周辺に寝床を用意したら";
		mes "最初は寝れないように";
		mes "いじめるくらいだけど、";
		mes "やがて復讐心が強くなり";
		mes "寝ている人が窒息するまで";
		mes "胸の上に座り続けるんだ。";
		next;
		menu "そんなことが……",-;
		mes "[老人]";
		mes "ハハハ、";
		mes "そんなに心配しなくてもいいよ。";
		mes "普通の柱にビョンウンゴはいないから。";
		close;
	}
}

malaya.gat,63,185,4	script	女性	583,{
	if(MALAYA_1QUE < 2) {
		mes "[女性]";
		mes "特にあなたと話すことはありません。";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[女性]";
		mes "子供たちが心配です。";
		mes "町に雰囲気が悪くなって";
		mes "怖がっているのではないかと……。";
		close;
	}
	set '@rand,rand(6);
	switch(rand(1,4)) {
	case 1:
		mes "[女性]";
		mes "仲良くしていたダンサーが";
		mes "あるダンサーのお話をしてくれました。";
		next;
		mes "[女性]";
		mes "「ダンサーが段差で転んだんさー」";
		next;
		mes "[女性]";
		mes "ふう……私が面白い言葉は好きですが";
		mes "聞いてあげることが辛い";
		mes "寒いジョークですね。";
		close;
	case 2:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[女性]";
			mes "私は面白い話が好きなんですが。";
			mes $MalayaName$['@rand];
			mes "という冒険者は絵が上手いとの";
			mes "噂があったので、";
			mes "私はその方にこのように";
			mes "言ってあげました。";
			next;
			mes "[女性]";
			mes "「素人が絵を描くと画家ががっかり！」";
			next;
			mes "[女性]";
			mes "ほほほ、面白いでしょう？";
			close;
		}
	case 3:
		if($MalayaName$['@rand] != "" && $MalayaName$['@rand] != strcharinfo(0)) {
			mes "[女性]";
			mes "私は面白い話が好きです。";
			mes "この前";
			mes $MalayaName$['@rand];
			mes "という冒険者が";
			mes "話をしてくれたんです。";
			next;
			mes "[女性]";
			switch(rand(5)) {
			case 1:
				mes "「ロッカーと踊ろっかー」";
				break;
			case 2:
				mes "「フェンの様子が変だ」";
				break;
			case 3:
				mes "道具店で";
				mes "「イジドル買います!!　1$で」";
				next;
				mes "[女性]";
				mes "と言ってお店から";
				mes "追い出されたらしいです。";
				break;
			case 4:
				mes "「ネペンテスが寝てんです！」";
				break;
			}
			next;
			mes "[女性]";
			mes "ほほほ、面白いでしょう？";
			close;
		}
	case 4:
		mes "[女性]";
		mes "町の外にある茂みで子供の泣き声が";
		mes "聞こえるなら、近寄らないで";
		mes "注意して下さい。";
		next;
		menu "どうしてですか？",-;
		mes "[女性]";
		mes "町の外にはチャナックという";
		mes "モンスターが赤ちゃんの姿で";
		mes "泣いたりしているんですが ";
		next;
		mes "[女性]";
		mes "心優しい旅行者たちが";
		mes "赤ちゃんを抱き上げると";
		mes "本来の姿に戻って";
		mes "旅行者を攻撃するんですよ。";
		next;
		menu "悪いモンスターですね",-;
		mes "[女性]";
		mes "確かに旅行者の優しさを利用する";
		mes "悪いモンスターなんですけど";
		next;
		mes "[女性]";
		mes "この世に未練がある子供の魂が";
		mes "化けたモンスターという話があって";
		mes "少し可哀想です。";
		close;
	}
}

//============================================================
// 警戒する街クエストNPC
//- Registry -------------------------------------------------
// MALAYA_1QUE -> 0～1
//------------------------------------------------------------
malaya.gat,266,76,3	script	警備隊員ロデル	570,7,7,{
	switch(MALAYA_1QUE) {
	case 0:
		break;
	case 1:
		mes "[警備隊員ロデル]";
		mes "まずはムンバキ・ポンに";
		mes "会ってみなさい。";
		mes "君に問題がないと認められれば、";
		mes "町の人たちも避けたりはしないだろう。";
		mes "位置を君の持っている地図に記したから";
		mes "参考にしてみてくれ。";
		viewpoint 1,185,358,0,0x0A82FF;
		close;
	case 2:
	case 3:
	case 4:
	case 5:
		mes "[警備隊員ロデル]";
		mes "不快な思いをさせて申し訳ないが、";
		mes "町の人たちの気持ちも";
		mes "理解してあげてくれないか。";
		mes "悪霊に苦しめられているから";
		mes "知らないものに対する警戒が強いんだ。";
		close;
	case 6:
		if(BaseLevel < 100) {
			mes "[警備隊員ロデル]";
			mes "ここの生活はどうだい？";
			mes "町の人もそんなに悪くないだろう。";
			next;
			mes "[警備隊員ロデル]";
			mes "そうそう、出来れば君にお願いしたい";
			mes "仕事があったんだが……";
			mes "まだちょっと無理そうだね。";
			next;
			mes "‐警備隊員に実力不足を指摘された";
			mes "　^FF0000BaseLv100以上^000000になってから";
			mes "　あらためて、話かけてみよう‐";
			close;
		}
		if(checkquest(7404)) {
			if(!(checkquest(7404) & 0x4)) {
				mes "[警備隊員ロデル]";
				mes "ジェジェリンを退治してきてくれ。";
				mes "20匹ほど退治すれば、";
				mes "奴らも少し大人しくなるだろう。";
				close;
			}
			mes "[警備隊員ロデル]";
			mes "お、ジェジェリン20匹退治、";
			mes "確かに確認した。";
			mes "これはジェジェリン退治の参加者に";
			mes "渡してくれと送られて来た褒賞だ。";
			next;
			mes "[警備隊員ロデル]";
			mes "これからもジェジェリンは";
			mes "定期的に退治する予定なので、";
			mes "良ければ次も一緒に参加してくれ。";
			setquest 7405;
			getitem 6497,1;
			if(checkre())
				getexp 50000,20000;
			else
				getexp 500000,200000;
			delquest 7404;
			set $MalayaName$[1],strcharinfo(0);
			close;
		}
		switch(rand(1,4)){
		case 1:
			if($MalayaName$[0] != "" || $MalayaName$[3] != "" || $MalayaName$[5] != "") {
				mes "[警備隊員ロデル]";
				mes "最近、勇敢な戦士として、";
				mes $MalayaName$[0];
				mes $MalayaName$[3];
				mes $MalayaName$[5];
				mes "の話題で町は持ちきりさ。";
				break;
			}
		case 2:
			if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
				mes "[警備隊員ロデル]";
				mes "最近、友達になった人がいるんだ。";
				mes $MalayaName$[2];
				mes "という人だけど知っているか？";
				mes "あ、もちろん君もいい友達だよ。";
				break;
			}
		case 3:
			mes "[警備隊員ロデル]";
			mes "ジプニーで知らない異性と";
			mes "ふたりきりになったことあるかい？";
			mes "はあ……本当にぎくしゃくしたよ……。";
			mes "こんなんで結婚できるのかな。";
			break;
		case 4:
			mes "[警備隊員ロデル]";
			mes "暇なら代わりに警備でもしてみるかい？";
			mes "最悪な仕事だよ。";
			mes "太陽が頭の上に昇っていても";
			mes "動いちゃいけないし……";
			break;
		}
		next;
		if(checkquest(7405)) {
			if(!(checkquest(7405) & 0x2)) {
				mes "[警備隊員ロデル]";
				mes "そうそう、ジェジェリン退治だけど、";
				mes "これからも定期的に討伐していく";
				mes "つもりだから、その気があるなら";
				mes "また来てくれ。";
				close;
			}
			mes "[警備隊員ロデル]";
			mes "ところで、この前のジェジェリン";
			mes "退治だけど、バリオ・マヒワガを";
			mes "行き来する人たちに、すごく評判が";
			mes "良かったよ。";
			mes "是非、もう一度参加してくれないか。";
			next;
			if(select("ジェジェリン退治に参加する","断る") == 2) {
				mes "[警備隊員ロデル]";
				mes "そうか？残念だ。";
				close;
			}
			mes "[警備隊員ロデル]";
			mes "おお、ありがとう。";
			mes "それじゃジェジェリンを";
			mes "^FF000020匹^000000倒してくれ。";
			mes "君なら簡単だろう。";
			mes "頼んだぞ。";
			delquest 7405;
			setquest 7404;
			close;
		}
		mes "[警備隊員ロデル]";
		mes "ところで君にお願いしたい";
		mes "仕事があるんだけどやってみないか？";
		next;
		mes "[警備隊員ロデル]";
		mes "バリオ・マヒワガへの往来を妨げる";
		mes "ジェジェリンを大々的に";
		mes "退治することが決定したんだ。";
		next;
		mes "[警備隊員ロデル]";
		mes "数が多いので殲滅は難しいが、";
		mes "定期的にある程度退治することで";
		mes "奴らの活動範囲を狭める事が目的だ。";
		mes "どうだろう、参加してみないか？";
		next;
		if(select("ジェジェリン退治に参加する","断る") == 2) {
			mes "[警備隊員ロデル]";
			mes "そうか？残念だ。";
			close;
		}
		mes "[警備隊員ロデル]";
		mes "おお、ありがとう。";
		mes "それじゃジェジェリンを";
		mes "^FF000020匹^000000倒してくれ。";
		mes "君なら簡単だろう。";
		mes "頼んだぞ。";
		delquest 72082;
		setquest 7404;
		close;
	}
OnTouch:
	emotion 0;
	if(MALAYA_1QUE == 0) {
		mes "[警備隊員ロデル]";
		mes "やぁ！";
		mes "ようこそポートマラヤへ！";
		next;
		mes "[警備隊員ロデル]";
		mes "これまで君が見たことのないような";
		mes "独特な雰囲気の町並みや、";
		mes "隣村バリオ・マヒワガの名物";
		mes "ピンタドスフェスティバルなど、";
		mes "見どころはいっぱいだ。";
		mes "目いっぱい観光していってくれ！";
		next;
		mes "[警備隊員ロデル]";
		mes "……と言いたいところだが、";
		mes "ちょっとばかり来る時期が悪かったな。";
		next;
		mes "[警備隊員ロデル]";
		mes "実は……";
		mes "最近、町に悪霊が出没するんだ。";
		mes "それで町の住民はみんな、恐怖と不安に";
		mes "駆られている。";
		next;
		mes "[警備隊員ロデル]";
		mes "中には、人間に化ける";
		mes "ズル賢い悪霊もいてな……";
		mes "住民は顔の知らない人には近寄らない";
		mes "ようになってしまったのさ。";
		next;
		mes "[警備隊員ロデル]";
		mes "だから……悪気はないのだけど、";
		mes "ポートマラヤの住民たちは";
		mes "外から来た冒険者の君を避けようと";
		mes "するだろう。";
		mes "旅館も、商店も外部の人には";
		mes "商売をしてくれないかもしれない。";
		next;
		mes "[警備隊員ロデル]";
		mes "町の人たちの警戒を解くために、";
		mes "まずはムンバキ・ポンに";
		mes "会ってみなさい。";
		next;
		mes "[警備隊員ロデル]";
		mes "ムンバキ・ポンは、この町の指導者だ。";
		mes "霊的な力を持っていて、";
		mes "町の住民に信頼されている。";
		mes "ムンバキ・ポンに認められれば";
		mes "みんなもきっと安心するだろう。";
		next;
		mes "[警備隊員ロデル]";
		mes "ムンバキ・ポンがいる場所を";
		mes "君の持っている地図に記しておくよ。";
		mes "このような時期で申し訳ない。";
		mes "訪問してくれたことは歓迎するよ。";
		viewpoint 1,185,358,0,0x0A82FF;
		set MALAYA_1QUE,1;
		setquest 7350;
		close;
	}
	end;
OnInit:
	waitingroom "警戒する街",0;
	end;
}

//============================================================
// 街の救済者クエストNPC
//- Registry -------------------------------------------------
// MALAYA_1QUE -> 0～6
//------------------------------------------------------------
malaya.gat,185,358,3	script	指導者ムンバキ・ポン	580,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[ムンバキ・ポン]";
		mes "海を渡って来た人だね。";
		mes "若き旅人よ";
		mes "ようこそ、ポートマラヤへ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "私はムンバキ・ポン。";
		mes "霊的な力によって、";
		mes "町の人々を導く者だ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "君が私を訪ねたのは……";
		mes "そうか、";
		mes "ロデルに言われたのだね。";
		next;
		mes "[ムンバキ・ポン]";
		mes "わかっている……";
		mes "町の人たちの態度のことだろう。";
		mes "私なら町の人たちに顔が利くから";
		mes "なんとかできるだろうと";
		mes "君を私の所によこした。";
		mes "違うかね？";
		if(MALAYA_1QUE == 0) {
			next;
			mes "[ムンバキ・ポン]";
			mes "なに。違うのか？";
			mes "では君と私の間に何か";
			mes "霊的な導きがあったからだろうな。";
			mes "これも何かの思し召しよ。";
		}
		next;
		mes "[ムンバキ・ポン]";
		mes "若き旅人よ";
		mes "とにかくよく来てくれた。";
		mes "町の人たちの警戒心が強いからといって";
		mes "どうか彼等を嫌いにならないでほしい。";
		next;
		mes "[ムンバキ・ポン]";
		mes "彼等は不安なのだよ。";
		mes "最近、悪い魂たちが激しく暴れて、";
		mes "人々を苦しめているのだ……。";
		next;
		mes "[ムンバキ・ポン]";
		mes "魂というのは、";
		mes "本来、森や海、大気といった";
		mes "大自然の守護者だ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "私たちはこれまでこの魂と供に";
		mes "平和を祈っていたのに、";
		mes "どうして人々を苦しめるような";
		mes "悪い魂が現れるようになったのか……";
		mes "まったくわからないんだ。";
		next;
		soundeffect "se_pay_grass_05.wav",0,0;
		mes "‐ムンバキ・ポンの話の最中に";
		mes "　物音が聞こえたような気がする‐";
		next;
		musiceffect "120";
		sc_start3 SC_BLIND,0,0,0,0,360000,10;
		mes "‐いつの間にかあたりは暗くなり";
		mes "　肌寒さを感じる‐";
		next;
		soundeffect "se_moaning01.wav",0,0;
		mes "[ムンバキ・ポン]";
		mes "むむ……";
		mes "さっそく来てしまったようだな。";
		next;
		cutin "malaya_ghost01",4;
		mes "^4d4dff‐ムンバキ・ポンが横を向くと";
		mes "　黒い影がぽつぽつと姿を現した。";
		mes "　周辺の人々が恐怖に怯えている‐^000000";
		next;
		soundeffect "solace_die.wav",0,0;
		mes "[住民]";
		mes "で、でたー！";
		mes "逃げろ、逃げるんだ！";
		next;
		menu "影に近寄る",-,"武器を抜く",-;
		soundeffect "se_moaning01.wav",0,0;
		mes "[ムンバキ・ポン]";
		mes "外から来た君の痕跡を";
		mes "辿って来たようだな。";
		mes "彼らにあまり近寄らないように。";
		mes "魂を奪われる可能性がある。";
		next;
		emotion 0;
		cutin "malaya_ghost02",4;
		sc_end SC_BLIND;
		mes "[ムンバキ・ポン]";
		mes "ん？　これは……どういうことだ。";
		mes "やつらが動揺している。";
		mes "いったい何が？";
		next;
		mes "[ムンバキ・ポン]";
		mes "ふむ。神聖な魂に気圧されているのか？";
		mes "まさか……この魂の気は……！";
		next;
		mes "^4d4dff‐ムンバキ・ポンが話すとおり";
		mes "　魂たちは明らかに動揺している。";
		mes "　あなたがさらに近寄ると";
		mes "　魂たちは戸惑い姿を消してしまった‐^000000";
		next;
		cutin "malaya_ghost02",255;
		mes "[住民]";
		mes "す……すごい！";
		mes "悪い魂が逃げて行ったぞ！";
		mes "お守りも持っていないのに";
		mes "いったいどうして……。";
		next;
		mes "[住民]";
		mes "そういえば、悪い魂が逃げていくとき";
		mes "ムンバキ・ポンが神聖な魂がどうとか";
		mes "言っていたが……。";
		next;
		mes "[住民]";
		mes "もしかして……";
		mes "この人は悪い魂に対抗できる";
		mes "すごい力を持っているんじゃないか!?";
		next;
		mes "[住民]";
		mes "……そうだ！　そうに違いない！";
		mes "異国からすごい力を持った";
		mes "冒険者が来たんだ！";
		next;
		mes "[住民]";
		mes "これで、この町は救われるに違いない！";
		mes "早くみんなにも知らせないと！";
		next;
		mes "‐周辺にいた人々が";
		mes "　興奮した様子で走り出した。";
		mes "　他の住民にあなたのことを";
		mes "　伝えている声が聞こえてくる‐";
		next;
		mes "[ムンバキ・ポン]";
		mes "町の者が騒いで申し訳ない。";
		mes "だが、私も驚いたよ。";
		mes "なんと巨大で純粋な魂の持ち主なんだ！";
		mes "闇に染められた魂たちが";
		mes "君の気に圧倒されていなくなるとは。";
		next;
		mes "[ムンバキ・ポン]";
		mes "まさに奇跡を目の当たりにした。";
		mes "これは町の人たちの警戒を解くのに";
		mes "充分すぎる出来事だな。";
		next;
		mes "[ムンバキ・ポン]";
		mes "この話を知れば、警戒していた人も";
		mes "きっと君を歓迎してくれるだろう。";
		mes "地図に記した場所にいる住人に";
		mes "話しかけてみてはどうだね。";
		viewpoint 1,181,353,0,0xFFFFFF;
		viewpoint 1,228,267,1,0xFFFF00;
		viewpoint 1,295,171,2,0x0000FF;
		viewpoint 1,119,217,3,0xCCCCCC;
		viewpoint 1,326,68,4,0x00FF00;
		viewpoint 1,223,267,5,0xFF0000;
		next;
		mes "[ムンバキ・ポン]";
		mes "若き冒険者よ。";
		mes "君はこの町の";
		mes "希望になれるかもしれない。";
		mes "期待させてもらうよ。";
		next;
		mes "‐町の人たちのあなたに対する";
		mes "　警戒は解けたようだ。";
		mes "　町の人たちに話しかけてみよう‐";
		setquest 201490;
		setquest 72050;
		if(MALAYA_1QUE == 1)
			delquest 7350;
		set MALAYA_1QUE,2;
		close;
	case 2:
		mes "[ムンバキ・ポン]";
		mes "君に対する警戒心は解けていると思う。";
		mes "彼らのところに行って、";
		mes "話しかけてみてはどうだね。";
		next;
		mes "[ムンバキ・ポン]";
		mes "君の魂はとても強く純粋だ。";
		mes "暗闇を恐れるな。";
		if(checkquest(7353)&8 == 0)
			viewpoint 1,181,353,0,0xFFFFFF;
		if(checkquest(7357)&8 == 0)
			viewpoint 1,228,267,1,0xFFFF00;
		if(checkquest(7355)&8 == 0)
			viewpoint 1,295,171,2,0x0000FF;
		if(checkquest(7354)&8 == 0)
			viewpoint 1,119,217,3,0xCCCCCC;
		if(checkquest(7352)&8 == 0)
			viewpoint 1,326,68,4,0x00FF00;
		if(checkquest(7356)&8 == 0)
			viewpoint 1,223,267,5,0xFF0000;
		close;
	case 3:
		mes "[ムンバキ・ポン]";
		mes "どうしたんだ？";
		mes "何か悩みがありそうな表情だな。";
		mes "服装もかなり乱れている。";
		mes "何かあったのか？";
		next;
		if(select("一部始終を説明する","何でもないです") == 2) {
			mes "[ムンバキ・ポン]";
			mes "そうか。";
			mes "もし何かあったら私に話してくれ。";
			mes "役に立てる事ならいつでも力になろう。";
			close;
		}
		mes "[ムンバキ・ポン]";
		mes "ふむ……なるほど。";
		mes "そんなことがあったのか。";
		mes "それは困った事だな。";
		next;
		mes "[ムンバキ・ポン]";
		mes "実は私も、町の人々の";
		mes "不安を取り除くために";
		mes "何かできないかと思って";
		mes "お守りを作ることにしたのだが、";
		mes "意外と準備が大変でね……。";
		mes "思うように進んでいないのだ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "そうだな……";
		mes "彼らの願いを叶えてくれないかね？";
		mes "君の所持品から";
		mes "何か選んで彼らにわけてあげるんだ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "彼らが求めているのは心の安定だ。";
		mes "小さな物ひとつに意味を見出して";
		mes "心に平穏を与えているのだよ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "これさえあれば私は大丈夫、";
		mes "と信じるその心が重要なんだろう。";
		mes "物が何かは大した問題ではない。";
		next;
		mes "[ムンバキ・ポン]";
		mes "君の古い持ち物ひとつで";
		mes "何かに恐れを持っていた者たちが";
		mes "活気を取り戻せるなら、";
		mes "それはもうお守りと言えるだろう。";
		next;
		mes "^4d4dff‐ムンバキ・ポンの助言の通りに";
		mes "　それらしい物を分けてあげよう。";
		mes "　何がお守りとしていいだろうか‐^000000";
		next;
		switch(select("聖水","ブルージェムストーン","ゼロピー")) {
		case 1:
			mes "[ムンバキ・ポン]";
			mes "それは神聖な水の事だな。";
			mes "なかなかいい案だと思う。";
			mes "ふむ。ただそれだけだと物足りないな。";
			mes "他にいいものは無いか？";
			next;
			menu "ブルージェムストーン",-;
			mes "[ムンバキ・ポン]";
			mes "ほぅ……神聖な魔法に使われる石？";
			mes "かなり良いな。";
			break;
		case 2:
			mes "[ムンバキ・ポン]";
			mes "ほぅ……神聖な魔法に使われる石？";
			mes "かなり良いな。";
			mes "しかし、それだけだと物足りないな。";
			mes "他にいいものは無いか？";
			next;
			menu "聖水",-;
			mes "[ムンバキ・ポン]";
			mes "それは神聖な水の事だな。";
			mes "なかなかいい案だと思う。";
			break;
		case 3:
			mes "[ムンバキ・ポン]";
			mes "うむ？　まあ、その……なんだ。";
			mes "確かになんでもいいとは言ったが、";
			mes "それらしいものがあれば";
			mes "町人も信頼を寄せやすいというものだ。";
			next;
			mes "[ムンバキ・ポン]";
			mes "神聖な力が感じられると";
			mes "さらに良いな。";
			mes "何かちょうどいいものはないかね？";
			next;
			menu "聖水かブルージェムストーン……？",-;
			mes "[ムンバキ・ポン]";
			mes "名前からして聖なる力が感じられるな。";
			mes "聖なる力を持った水のようだね。";
			mes "それと術者を守ってくれる石か。ふむ。";
			mes "良いじゃないか。";
			break;
		}
		next;
		mes "[ムンバキ・ポン]";
		mes "では、私がお守りを作るまでの間、";
		mes "^ff0000聖水とブルージェムストーン^000000を";
		mes "1人に1個ずつ、6人分ほど";
		mes "用意してもらえないだろうか。";
		mes "そしてそれを分けることで";
		mes "人々に安らぎを与えてほしい。";
		next;
		mes "[ムンバキ・ポン]";
		mes "そうするれば町の人たちからの";
		mes "信頼はさらに厚くなり、";
		mes "君に心を開いてくれるだろう。";
		next;
		mes "[ムンバキ・ポン]";
		mes "彼らのいる場所を地図に記そう。";
		mes "すまないが頼んだよ。";
		viewpoint 1,181,353,0,0xFFFFFF;
		viewpoint 1,228,267,1,0xFFFF00;
		viewpoint 1,295,171,2,0x0000FF;
		viewpoint 1,119,217,3,0xCCCCCC;
		viewpoint 1,326,68,4,0x00FF00;
		viewpoint 1,223,267,5,0xFF0000;
		delquest 7358;
		setquest 7351;
		set MALAYA_1QUE,4;
		close;
	case 4:
		mes "[ムンバキ・ポン]";
		mes "聖水とブルージェムストーン。";
		mes "君がその2つを町の人たちに配れば";
		mes "不安を取り除けるだろう。";
		next;
		mes "[ムンバキ・ポン]";
		mes "1人に1個ずつ、";
		mes "6人に配って来てほしい。";
		mes "彼らのいる場所を地図に記そう。";
		mes "すまないが頼んだよ。";
		if(checkquest(7360)&8 == 0)
			viewpoint 1,181,353,0,0xFFFFFF;
		if(checkquest(7364)&8 == 0)
			viewpoint 1,228,267,1,0xFFFF00;
		if(checkquest(7362)&8 == 0)
			viewpoint 1,295,171,2,0x0000FF;
		if(checkquest(7361)&8 == 0)
			viewpoint 1,119,217,3,0xCCCCCC;
		if(checkquest(7359)&8 == 0)
			viewpoint 1,326,68,4,0x00FF00;
		if(checkquest(7363)&8 == 0)
			viewpoint 1,223,267,5,0xFF0000;
		close;
	case 5:
		mes "[ムンバキ・ポン]";
		mes "町の人々が落ち着きを";
		mes "取り戻したようだね。";
		mes "君がやってくれたんだろう？";
		mes "わかっているよ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "これで君は町のみんなに";
		mes "慕われる存在になったな。";
		mes "私も感謝している。";
		mes "これまで君を避けていた住民も";
		mes "きっと心を開いてくれるだろう。";
		next;
		mes "[ムンバキ・ポン]";
		mes "そうそう、遅れていたお守り作成だが";
		mes "そこにいる孫娘のイメルダーが";
		mes "手伝ってくれることになった。";
		mes "君が渡してくれた物は今回っきりに";
		mes "なるから、次は用意しなくて大丈夫だ。";
		next;
		mes "[ムンバキ・ポン]";
		mes "この町には、まだまだ困っている";
		mes "住民がたくさんいる。";
		mes "もし困っている住民に会ったら";
		mes "助けてあげてほしい。";
		mes "よろしく頼む。";
		delquest 7365;
		setquest 201495;
		if(MALAYA_2QUE == 0)
			setquest 72070;
		if(MALAYA_3QUE == 0)
			setquest 72072;
		if(MALAYA_4QUE == 0)
			setquest 72074;
		if(MALAYA_5QUE == 0)
			setquest 72076;
		if(MALAYA_6QUE == 0)
			setquest 72078;
		if(MALAYA_7QUE == 0)
			setquest 72080;
		setquest 72082;
		setquest 72084;
		setquest 72086;
		setquest 72088;
		setquest 72092;
		setquest 72090;
		setquest 72094;
		set MALAYA_1QUE,6;
		if(checkre())
			getexp 100000,20000;
		else
			getexp 1000000,200000;
		close;
	case 6:
		switch(rand(1,4)) {
		case 1:
			if($MalayaName$[0] != "" && $MalayaName$[0] != strcharinfo(0)) {
				mes "[ムンバキ・ポン]";
				mes "君のように勇敢な冒険者がいたよ。";
				mes $MalayaName$[0];
				mes "という名前らしいが、";
				mes "知り合いかね？";
				break;
			}
		case 2:
			if($MalayaName$[0] != "" && $MalayaName$[0] != strcharinfo(0)) {
				mes "[ムンバキ・ポン]";
				mes "最近町で人気の冒険者がいる。";
				mes $MalayaName$[0];
				mes "という名前らしいが、";
				mes "血気盛んな冒険者のようだね。";
				break;
			}
		case 3:
			if($MalayaName$[1] != "" && $MalayaName$[1] != strcharinfo(0)) {
				mes "[ムンバキ・ポン]";
				mes $MalayaName$[1];
				mes "という冒険者はこの町だけでなく";
				mes "バリオ・マヒワガでも";
				mes "人々を助けているらしい。";
				mes "善良な魂の持ち主が増えてうれしいよ。";
				break;
			}
		case 4:
			mes "[ムンバキ・ポン]";
			mes "今までムンバキ・として生きてきたが、";
			mes "君のような清くて強い魂は";
			mes "他に見たことがないよ。";
			break;
		}
		switch(MALAYA_3QUE) {
		case 2:
			next;
			menu "港で起きた事を話す",-;
			mes "[ムンバキ・ポン]";
			mes "港のペリー号でそんなことが？";
			mes "なるほど、ふーむ……。";
			mes "まずは彼女がどうしてそんなに怒るのか";
			mes "理由を知る必要があるな。";
			next;
			mes "[ムンバキ・ポン]";
			mes "うむ。";
			mes "こんな時はプレゼントが一番だ。";
			mes "やはり女性の心を癒すには";
			mes "花束だな。これ以上の物はない。";
			next;
			menu "恋愛相談ではないですけど",-;
			mes "[ムンバキ・ポン]";
			mes "例えばの話だよ。";
			mes "まずは彼女の話を聞かない事には";
			mes "どうにもならない。";
			mes "それには打ち解ける必要があるだろう。";
			next;
			mes "[ムンバキ・ポン]";
			mes "生きていても死んでいても";
			mes "女性は女性だ。";
			mes "それに、年頃の女性は";
			mes "綺麗な物が好きなはずだ。";
			mes "上手くいくんじゃないかね。";
			next;
			mes "[ムンバキ・ポン]";
			mes "よし、ではこうしよう。";
			mes "^4d4dff神秘的な花、清楚な花、綺麗な花^000000を";
			mes "それぞれ3個ずつ用意してくるんだ。";
			mes "集めてきたら私が花束にして";
			mes "祝福の祈りを籠めてあげよう。";
			mes "それを持っていってみたらどうかな。";
			next;
			mes "[ムンバキ・ポン]";
			mes "まあ、花なら町の外に行けば";
			mes "何とかなるだろう。";
			mes "集めたらまた来てくれ。";
			delquest 7396;
			setquest 7397;
			set MALAYA_3QUE,3;
			close;
		case 3:
			next;
			if(countitem(6509) < 3 || countitem(6510) < 3 || countitem(6511) < 3) {
				mes "[ムンバキ・ポン]";
				mes "ところで……";
				mes "花束を作るためには、";
				mes "^4d4dff神秘的な花、清楚な花、綺麗な花^000000が";
				mes "それぞれ3個ずつ必要だ。";
				mes "用意してからまた来てくれ。";
				close;
			}
			mes "[ムンバキ・ポン]";
			mes "ところで……";
			mes "うむ、花を持ってきたようだな。";
			mes "それでは私が祈りを籠めて束ねよう。";
			next;
			mes "‐ムンバキ・ポンは大事に花を";
			mes "　束ねながら祝福の儀式を始めた。";
			mes "　神聖な雰囲気が伝わってくる‐";
			misceffect 16;
			next;
			mes "[ムンバキ・ポン]";
			mes "よし。どうだ。";
			mes "なかなかの出来だろう。";
			next;
			if(checkitemblank() == 0) {
				// 未調査
				mes "[ムンバキ・ポン]";
				mes "む、アイテムをたくさん";
				mes "持ち過ぎのようだな。";
				mes "整理してからもう一度";
				mes "来てくれないか。";
				close;
			}
			mes "[ムンバキ・ポン]";
			mes "さあ、ではその子に渡してくれ。";
			mes "心の扉を開いてくれる事を願おう。";
			delitem 6510,3;
			delitem 6509,3;
			delitem 6511,3;
			getitem 6506,1;
			delquest 7397;
			setquest 7398;
			set MALAYA_3QUE,4;
			close;
		case 4:
			next;
			mes "[ムンバキ・ポン]";
			mes "ところで……";
			mes "まだ花束を持っているみたいだな。";
			mes "渡した花束を持って";
			mes "船にいる女性と話してみなさい。";
			close;
		case 6:
			if(checkquest(7402)) {
				next;
				if(countitem(6509) < 3 || countitem(6510) < 3 || countitem(6511) < 3) {
					mes "[ムンバキ・ポン]";
					mes "ん？";
					mes "ディワタの所に行くのか？";
					mes "^4d4dff神秘的な花、清楚な花、綺麗な花^000000を";
					mes "3個ずつ持って来れば、";
					mes "祝福の祈りを籠めて花束を作るぞ。";
					close;
				}
				mes "[ムンバキ・ポン]";
				mes "お、持ってきたな。";
				mes "魂の供養は一日にして成らず。";
				mes "それじゃあ、花束に祝福を籠めよう。";
				next;
				if(checkitemblank() == 0) {
					mes "[ムンバキ・ポン]";
					mes "む、アイテムをたくさん";
					mes "持ち過ぎのようだな。";
					mes "整理してからもう一度";
					mes "来てくれないか。";
					close;
				}
				mes "[ムンバキ・ポン]";
				mes "さあ、出来たぞ。";
				mes "今日も祈る事にしよう。";
				misceffect 16;
				delitem 6509,3;
				delitem 6510,3;
				delitem 6511,3;
				getitem 6506,1;
				delquest 7402;
				setquest 72065;
				close;
			}
			if(checkquest(72065)) {
				next;
				mes "[ムンバキ・ポン]";
				mes "ところで……";
				mes "すでに花束は渡したはずだぞ。";
				mes "早く花束を持ってペリー号に行くんだ。";
				close;
			}
			if(checkquest(7401)) {
				next;
				mes "[ムンバキ・ポン]";
				mes "ところで……";
				mes "ペリー号のこともそうだが、";
				mes "浮かばれない魂が存在するのは";
				mes "悲しいことだ。";
				mes "魂のために献花をするなら";
				mes "いつでも力になろう。";
				close;
			}
		}
		close;
	}
OnInit:
	waitingroom "街の救済者",0;
	end;
}

//============================================================
// 街を思う少女クエストNPC
//- Registry -------------------------------------------------
// MALAYA_2QUE -> 0～5
//------------------------------------------------------------
malaya.gat,169,350,5	script	イメルダー	475,{
	if(MALAYA_1QUE < 2) {
		mes "[イメルダー]";
		mes "ん……なにかしら。";
		mes "用が無いなら話しかけないでくれる？";
		next;
		mes "‐少女はこちらを警戒している‐";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[イメルダー]";
		mes "ふぅん……";
		mes "なかなかやりますわね。";
		mes "うまくやってるようだけど、";
		mes "いつまで続くかしら。";
		next;
		mes "[イメルダー]";
		mes "まあ化けの皮が剥がれないように、";
		mes "せいぜい気を付けることね。";
		emotion 32;
		next;
		mes "‐少女は何故か敵対心を露わにしている‐";
		close;
	}
	switch(MALAYA_2QUE) {
	case 0:
		mes "[イメルダー]";
		mes "はぁ……材料をなんとかしなくちゃ……";
		next;
		emotion 0;
		mes "[イメルダー]";
		mes "！";
		next;
		mes "[イメルダー]";
		mes "あ、あら、インチキくさいお守りで";
		mes "町のみんなの心を掌握した";
		mes "英雄様じゃない。";
		mes "私に何か用かしら？";
		next;
		if(select("お守りを作ることになったんだって？","君には真似出来ないだろうね") == 1) {
			mes "[イメルダー]";
			mes "あら、よくご存じね。";
			mes "そうよ。私のおじいちゃんが";
			mes "本物のお守りを作ってくれたの。";
			mes "この^FF0000退魔のお守り^000000は本当に";
			mes "凄いんだから！";
		} else {
			emotion 6;
			mes "[イメルダー]";
			mes "なによ、言ってくれるじゃない！";
			mes "偶然上手くいったからって、";
			mes "いつまでも続くとは思わないことね！";
			next;
			mes "[イメルダー]";
			mes "見てなさい！";
			mes "おじいちゃんが作ってくれた";
			mes "この^FF0000退魔のお守り^000000は本当に";
			mes "凄いんだから！";
		}
		next;
		mes "[イメルダー]";
		mes "これからは私が本物のお守りを作って、";
		mes "みんなを助けるの。";
		mes "よそ者のあなたが出る場面はないわ。";
		mes "この町を守るのは私の仕事だもの！";
		next;
		if(select("何か手伝おうか？","それじゃあ一人で頑張って！") == 2) {
			mes "[イメルダー]";
			mes "ええ！　別にあなたに手伝って";
			mes "もらわなくてもけっこうよ！";
			mes "町のみんなは私が助けるわ！";
			next;
			menu "その割にはお守りが見当たらないけど……",-;
			mes "[イメルダー]";
			mes "う、うるさいわね！";
			mes "ちょうどこれから材料を、";
			mes "集めに行こうと思ってたのよ！";
			mes "忙しいんだから、邪魔するなら";
			mes "早くどこかに行って！";
			emotion 36;
			close;
		}
		mes "[イメルダー]";
		mes "どういう風の吹き回し？";
		mes "別にあなたに手伝ってもらわなくても";
		mes "私一人でできるわ。";
		mes "それともあなた、まだ町のみんなに";
		mes "良い顔をしたいのかしら？";
		next;
		if(select("そんなことないよ","君が大変そうだったから") == 1) {
			mes "[イメルダー]";
			mes "ふん、どうかしらね。";
			emotion 32;
		} else {
			mes "[イメルダー]";
			mes "な、なによ。";
			mes "そんなこと言っても";
			mes "騙されないんだから！";
			emotion 19;
		}
		next;
		if(BaseLevel < 100) {
			mes "[イメルダー]";
			mes "……まあいいわ。";
			mes "そこまで手伝いたいって言うなら、";
			mes "私の手伝いを……";
			mes "ん……弱い？";
			mes "あなたちょっと弱いわね……。";
			next;
			mes "[イメルダー]";
			mes "あなたではちょっと実力不足よ。";
			mes "そうね。少なくとも";
			mes "^FF0000BaseLv100以上^000000になってから";
			mes "また来てくれるかしら。";
			close;
		}
		mes "[イメルダー]";
		mes "……まあいいわ。";
		mes "そこまで手伝いたいって言うなら、";
		mes "手伝ってもらおうかしら。";
		next;
		mes "[イメルダー]";
		mes "^FF0000退魔のお守り^000000を作るには、";
		mes "^4d4dff尖った竹、塩袋、銀の十字架^000000が";
		mes "それぞれ6個ずつ必要なの。";
		mes "それを集めてきてくれる？";
		next;
		mes "[イメルダー]";
		mes "^4d4dff尖った竹^000000はバリオ・マヒワガ近辺に";
		mes "^FF0000黒い竹^000000が生えているから、";
		mes "それを切ってきて。";
		mes "長さは適当で構わないわ。";
		next;
		mes "[イメルダー]";
		mes "黒い竹はバリオ・マヒワガの";
		mes "警備犬がいるほうの柵の内側にあるわ。";
		mes "他にもバリオ・マヒワガの";
		mes "近辺に生えているわよ。";
		mes "見た目は他の木と変わらないけど、";
		mes "近くで見れば違いがわかるはずよ。";
		next;
		mes "[イメルダー]";
		mes "^4d4dff塩袋^000000は町の北西側の海岸付近で";
		mes "直接製塩して集める必要があるわ。";
		mes "私が掘っておいた^FF0000砂のくぼみ^000000が";
		mes "そのあたりにあるの。";
		mes "そこで取ってきて。";
		next;
		mes "[イメルダー]";
		mes "最後に^4d4dff銀の十字架^000000だけど、";
		mes "^FF0000武器屋の前にいるパンドイ^000000に";
		mes "銀のブレスレットを2個渡すと、";
		mes "1個作ってくれるはずよ。";
		next;
		mes "[イメルダー]";
		mes "……ただ銀のブレスレットは";
		mes "^FF0000マナナンガルやチャナック、ワクワク^000000が";
		mes "持っているの。";
		mes "強力なモンスターばかりだから、";
		mes "すごく危険だわ。";
		next;
		mes "[イメルダー]";
		mes "怖いならやめてもいいわよ？";
		mes "別にあなたが心配なわけじゃないけど、";
		mes "私を手伝って怪我なんてされたら、";
		mes "こっちが悪いみたいじゃない。";
		emotion 29;
		next;
		menu "集めてくるのはそれで全部？",-;
		mes "[イメルダー]";
		mes "え？";
		mes "え、ええ、そうよ。";
		mes "これで全部……。";
		next;
		mes "[イメルダー]";
		mes "じゃ、じゃあ私はここで待ってるから、";
		mes "早く集めてきて頂戴。";
		mes "せいぜい気をつけることね。";
		delquest 72070;
		setquest 7366;
		set MALAYA_2QUE,1;
		close;
	case 1:
		if(countitem(6500) < 6 || countitem(6501) < 6 || countitem(6502) < 6) {
			mes "[イメルダー]";
			mes "もしかして、必要な材料を";
			mes "忘れてしまったの？";
			mes "しょうがないわね。";
			next;
			mes "[イメルダー]";
			mes "^FF0000退魔のお守り^000000を作るのに必要な材料は、";
			mes "^4d4dff尖った竹、塩袋、銀の十字架^000000";
			mes "各6個ずつよ。";
			next;
			mes "[イメルダー]";
			mes "^4d4dff尖った竹^000000はバリオ・マヒワガ近辺の";
			mes "黒い竹から、";
			mes "^4d4dff塩袋^000000は町の北西の海岸の砂くぼみから、";
			mes "^4d4dff銀の十字架^000000は^FF0000武器屋前にいるパンドイ^000000に";
			mes "銀のブレスレットを2個渡すと";
			mes "1個作ってくれるわ。";
			next;
			mes "[イメルダー]";
			mes "銀のブレスレットは";
			mes "^FF0000マナナンガルやチャナック、ワクワク^000000が";
			mes "持っているけど、危ないと思ったら";
			mes "無理しなくてもいいわよ？";
			close;
		}
		mes "[イメルダー]";
		mes "あら、おかえりなさい。";
		mes "頼んでいたものはどうなったかしら？";
		next;
		mes "[イメルダー]";
		mes "すごい……本当に集めてきたのね。";
		mes "無理だと思ってたのに……。";
		emotion 0;
		next;
		menu "全部揃ってるかな？",-;
		mes "[イメルダー]";
		mes "え、ええ、問題ないわ。";
		mes "ありがとう……。";
		next;
		mes "[イメルダー]";
		mes "そ、それじゃあ私はこれから";
		mes "集めてくれた材料を使って、";
		mes "儀式を行うわ。";
		mes "お守り作りに必要な神聖な儀式よ。";
		next;
		mes "[イメルダー]";
		mes "儀式はすぐに終わるけど、";
		mes "とても繊細なものだから";
		mes "少し黙ってて。";
		next;
		mes "[イメルダー]";
		mes "儀式が終わったら、";
		mes "特別にお守りを見せてあげるわ。";
		mes "また話かけて頂戴。";
		delitem 6501,6;
		delitem 6500,6;
		delitem 6502,6;
		delquest 7366;
		setquest 7367;
		set MALAYA_2QUE,2;
		close;
	case 2:
		mes "[イメルダー]";
		mes "ふぅ……。";
		mes "これが今ちょうど出来上がった";
		mes "^FF0000退魔のお守り^000000よ。";
		next;
		mes "‐竹と銀で作られた";
		mes "　十字型のお守りからは、";
		mes "　神聖な力を感じる‐";
		next;
		mes "[イメルダー]";
		mes "ね？　素晴らしいでしょう？";
		mes "やっぱりおじいちゃんは凄いわ！";
		mes "これさえあれば、町のみんなを";
		mes "悩ませている悪霊も怖くなくなるわね。";
		emotion 2;
		next;
		mes "‐無事お守りを作り終えて";
		mes "　嬉しそうなイメルダーだが、";
		mes "　ずいぶん疲弊しているように見える‐";
		next;
		mes "[イメルダー]";
		mes "それじゃこのお守りを";
		mes "町のみんなに配ってこなくちゃ。";
		next;
		menu "配ってきてあげるよ",-;
		mes "[イメルダー]";
		mes "え……いいわよ。";
		mes "あなたには材料を集めもらったんだし。";
		mes "これくらい私がやるわよ。";
		next;
		mes "[イメルダー]";
		mes "それとも何？";
		mes "やっぱり町のみんなの";
		mes "人気を取りたいの？";
		next;
		menu "そうそう、だから少し休んでなよ",-;
		mes "[イメルダー]";
		mes "あ……。";
		emotion 0;
		next;
		mes "[イメルダー]";
		mes "（この人、私が疲れているからって";
		mes "　気遣ってくれてるんだ。";
		mes "　自分も疲れているはずなのに……）";
		next;
		mes "[イメルダー]";
		mes "（あんな態度をとっていた私に、";
		mes "　どうして……？）";
		next;
		mes "[イメルダー]";
		mes "……。";
		emotion 9;
		next;
		mes "[イメルダー]";
		mes "……そ、そうね、";
		mes "そんなに言うなら仕方ないわね。";
		mes "あなたに人気取りの機会をあげるわ。";
		mes "せいぜいみんなに良い顔をすると良いわ。";
		next;
		mes "[イメルダー]";
		mes "それじゃお守りと一緒に";
		mes "届け先のリストを渡しておくわ。";
		mes "地図にも記しておいたから、";
		mes "間違えないように気をつけてね。";
		next;
		mes "‐イメルダーから^FF0000退魔のお守り^000000を";
		mes "　受け取った。";
		mes "　リストを元にみんなに配ろう‐";
		viewpoint 1,181,353,0,0xFFFFFF;
		viewpoint 1,228,267,1,0xFFFF00;
		viewpoint 1,295,171,2,0x0000FF;
		viewpoint 1,119,217,3,0xCCCCCC;
		viewpoint 1,326,68,4,0x00FF00;
		viewpoint 1,223,267,5,0xFF0000;
		getitem 6503,6;
		delquest 7367;
		setquest 7368;
		setquest 7369;
		setquest 7370;
		setquest 7371;
		setquest 7372;
		setquest 7373;
		setquest 7374;
		set MALAYA_2QUE,3;
		close;
	case 3:
		mes "[イメルダー]";
		mes "^FF0000退魔のお守り^000000を渡す人の場所は";
		mes "リストと地図を見ればわかるわ。";
		mes "みんな不安だと思うから、";
		mes "できるだけ早く配ってきてね。";
		if(checkquest(7383) == 0)
			viewpoint 1,181,353,0,0xFFFFFF;
		if(checkquest(7387) == 0)
			viewpoint 1,228,267,1,0xFFFF00;
		if(checkquest(7385) == 0)
			viewpoint 1,295,171,2,0x0000FF;
		if(checkquest(7384) == 0)
			viewpoint 1,119,217,3,0xCCCCCC;
		if(checkquest(7382) == 0)
			viewpoint 1,326,68,4,0x00FF00;
		if(checkquest(7386) == 0)
			viewpoint 1,223,267,5,0xFF0000;
		close;
	case 4:
		mes "[イメルダー]";
		mes "ちゃんと全部届けてくれたのね。";
		next;
		mes "[イメルダー]";
		mes "……。";
		emotion 9;
		next;
		mes "[イメルダー]";
		mes "ひとつ聞いていい？";
		mes "どうしてあなたは";
		mes "私を手伝ってくれたの？";
		mes "あんなに酷いことを言ったのに。";
		next;
		menu "君が街のために頑張っていたから",-,"街のみんなを助けたかったから",-;
		mes "[イメルダー]";
		mes "そう……。";
		mes "　";
		mes "うふふっ";
		mes "よそ者のくせに変わった人ね。";
		next;
		mes "[イメルダー]";
		mes "あなたが戻ってくるまでの間、";
		mes "お守りを受け取った人が";
		mes "何人もここに来たわ。";
		next;
		mes "[イメルダー]";
		mes "これまで沈んでいたのが";
		mes "嘘のように明るい笑顔で、";
		mes "私とあなたにお礼を言っていたわ。";
		next;
		mes "[イメルダー]";
		mes "……。";
		emotion 9;
		next;
		mes "[イメルダー]";
		mes "最初にあなたを見たときは、";
		mes "よそ者がこの町の状況を見て、";
		mes "面白半分でみんなの話を";
		mes "聞いてまわってるんだと思ってた……。";
		next;
		mes "[イメルダー]";
		mes "でも、私を手伝ってくれる姿や";
		mes "町のみんなを見ていてわかったわ。";
		mes "あなた、本当にいい人だったのね。";
		next;
		mes "[イメルダー]";
		mes "本当は私一人じゃお守りの材料を";
		mes "集めるのも無理だったの。";
		mes "そんな時にあなたが手伝ってくれて、";
		mes "嬉しかったわ。";
		next;
		mes "[イメルダー]";
		mes "今まで生意気な事を言って";
		mes "ごめんなさい。";
		mes "それと、助けてくれてありがとう。";
		mes "これからも仲良くしてもらえるかしら？";
		next;
		menu "もちろん",-;
		mes "[イメルダー]";
		mes "良かった！　嬉しいわ。";
		mes "これからよろしくね。";
		emotion 3;
		next;
		if(checkitemblank() == 0) {
			// 未調査
			mes "[イメルダー]";
			mes "……荷物がいっぱいのようね。";
			mes "お礼を渡したいから、持ち物を";
			mes "整理して、もう一度話しかけて";
			mes "ちょうだい。";
			close;
		}
		mes "[イメルダー]";
		mes "これは手伝ってくれたお礼よ。";
		mes "受け取ってね。";
		delquest 7374;
		delquest 7379;
		setquest 7375;
		setquest 201500;
		set MALAYA_2QUE,5;
		getitem 6497,1;
		if(checkre()) {
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,300000;
		}
		else {
			getexp 5000000,0;
			getexp 5000000,0;
			getexp 0,3000000;
		}
		next;
		mes "[イメルダー]";
		mes "あと、実はお守りは";
		mes "毎日作らないといけないの。";
		mes "だから、もし時間があるなら";
		mes "手伝いに来てくれると嬉しいわ。";
		next;
		mes "[イメルダー]";
		mes "無理だったら他の人に頼むけど、";
		mes "できればあなたに手伝って欲しいの。";
		mes "お願いね。";
		emotion 40;
		close;
	case 5:
		if(checkquest(7379)) {
			emotion 15;
			mes "[イメルダー]";
			mes "全部配り終えたのね。お疲れさま。";
			next;
			mes "[イメルダー]";
			mes "でも……いつまでもお守りに";
			mes "頼っているだけでは駄目よね。";
			mes "結局お守りは強い心を持つ為の";
			mes "きっかけでしかないわ。";
			next;
			mes "[イメルダー]";
			mes "そのことに町の人々が気付いて";
			mes "このお守りがいらなくなる日が";
			mes "いつか来るのかしら。";
			mes "そうなって欲しいけど……。";
			next;
			if(checkitemblank() == 0) {
				mes "[イメルダー]";
				mes "……荷物がいっぱいのようね。";
				mes "お礼を渡したいから、持ち物を";
				mes "整理して、もう一度話しかけて";
				mes "ちょうだい。";
				close;
			}
			mes "[イメルダー]";
			mes "あっ、ごめんなさい。";
			mes "とにかく今日はこれで大丈夫。";
			mes "いつもありがとう。";
			mes "これはお礼よ。";
			setquest 7375;
			delquest 72170;
			delquest 7379;
			getitem 6497,1;
			if(checkre())
				getexp 50000,20000;
			else
				getexp 500000,200000;
			set $MalayaName$[0],strcharinfo(0);
			close;
		}
		if(checkquest(7380)) {
			if(countitem(6500) < 6 || countitem(6501) < 6 || countitem(6502) < 6) {
				mes "[イメルダー]";
				mes "^4d4dff尖った竹、塩袋、銀の十字架^000000を";
				mes "各6個ずつ集めてきてね。";
				next;
				mes "[イメルダー]";
				mes "^4d4dff尖った竹^000000はバリオ・マヒワガ近辺の";
				mes "黒い竹から、";
				mes "^4d4dff塩袋^000000は町の北西の海岸の砂くぼみから、";
				mes "^4d4dff銀の十字架^000000はパンドイに";
				mes "銀のブレスレットを渡せば";
				mes "手に入れることができるわ。";
				next;
				mes "[イメルダー]";
				mes "あなたなら大丈夫だと思うけど、";
				mes "くれぐれも無理はしないでね。";
				mes "無事を祈っています。";
				close;
			}
			emotion 2;
			mes "[イメルダー]";
			mes "全部揃ってるわね。";
			mes "いつもありがとう！";
			mes "こんなに優しい人を疑ってたなんて、";
			mes "私、恥ずかしいわ。";
			next;
			if(checkitemblank() == 0) {
				mes "[イメルダー]";
				mes "……荷物がいっぱいのようね。";
				mes "お礼を渡したいから、持ち物を";
				mes "整理して、もう一度話しかけて";
				mes "ちょうだい。";
				close;
			}
			mes "[イメルダー]";
			mes "良かったら明日もまた来てね。";
			mes "これは今回のお礼よ。";
			delitem 6501,6;
			delitem 6502,6;
			delitem 6500,6;
			delquest 7380;
			setquest 7381;
			getitem 6497,1;
			if(checkre())
				getexp 50000,20000;
			else
				getexp 500000,200000;
			set $MalayaName$[0],strcharinfo(0);
			close;
		}
		if(checkquest(72170)) {
			mes "[イメルダー]";
			mes "新しい^FF0000退魔のお守り^000000を";
			mes "町のみんなに渡してきてね。";
			mes "届け先はリストと地図を";
			mes "見ればわかるわ。";
			mes "それじゃあ、よろしくね！";
			if(checkquest(7383) == 0)
				viewpoint 1,181,353,0,0xFFFFFF;
			if(checkquest(7387) == 0)
				viewpoint 1,228,267,1,0xFFFF00;
			if(checkquest(7385) == 0)
				viewpoint 1,295,171,2,0x0000FF;
			if(checkquest(7384) == 0)
				viewpoint 1,119,217,3,0xCCCCCC;
			if(checkquest(7382) == 0)
				viewpoint 1,326,68,4,0x00FF00;
			if(checkquest(7386) == 0)
				viewpoint 1,223,267,5,0xFF0000;
			close;
		}
		mes "[イメルダー]";
		mes "あ、こんにちは。";
		mes "来てくれたのね。";
		emotion 12;
		next;
		mes "[イメルダー]";
		mes "ポートマラヤは気に入った？";
		mes "ジプニーに乗って町を回るのも";
		mes "なかなか楽しいわよ。";
		next;
		switch(select("退魔のお守り材料集めを手伝う","退魔のお守り配布を手伝う")) {
		case 1:
			if(checkquest(7381)) {
				if(!(checkquest(7381) & 0x2)) {
					mes "[イメルダー]";
					mes "気遣ってくれてありがとう。";
					mes "でも、今日は材料が十分足りているわ。";
					mes "材料が無くなったらお願いするね。";
					close;
				}
			}
			emotion 2;
			mes "[イメルダー]";
			mes "丁度お守りの材料が無くなって";
			mes "困っていたところなの。";
			mes "あなたが来てくれて助かったわ。";
			mes "それじゃお願いできる？";
			next;
			if(select("もちろん","今はできないので後で手伝う") == 2) {
				mes "[イメルダー]";
				mes "そう……わかったわ。";
				mes "また後でね。";
				close;
			}
			mes "[イメルダー]";
			mes "じゃあいつものようにお願いね。";
			mes "^4d4dff尖った竹、塩袋、銀の十字架^000000を";
			mes "各6個ずつよ。";
			if(checkquest(7381))
				delquest 7381;
			setquest 7380;
			next;
			mes "[イメルダー]";
			mes "^4d4dff尖った竹^000000はバリオ・マヒワガ近辺の";
			mes "黒い竹から、";
			mes "^4d4dff塩袋^000000は町の北西の海岸の砂くぼみから、";
			mes "^4d4dff銀の十字架^000000はパンドイに";
			mes "銀のブレスレットを渡せば";
			mes "手に入れることができるわ。";
			next;
			mes "[イメルダー]";
			mes "あなたなら大丈夫だと思うけど、";
			mes "くれぐれも無理はしないでね。";
			mes "無事を祈っています。";
			close;
		case 2:
			if(checkquest(7375)) {
				if(!(checkquest(7375) & 0x2)) {
					emotion 2;
					mes "[イメルダー]";
					mes "この前の^FF0000退魔のお守り^000000の効果が";
					mes "まだ発揮しているわ。";
					mes "だから今はまだ大丈夫。";
					mes "でもありがとう、";
					mes "その気持ちだけで嬉しいわ。";
					close;
				}
				mes "[イメルダー]";
				mes "今日もお守りを配ってくれるの？";
				next;
				if(select("配る","配らない") == 2) {
					mes "[イメルダー]";
					mes "そう……。";
					mes "残念だけど、";
					mes "あなたにも都合があるものね。";
					close;
				}
				if(checkquest(7381) & 0x2) {
					mes "[イメルダー]";
					mes "ありがとう。でも、材料がなくて";
					mes "まだ^FF0000退魔のお守り^000000が完成してないの。";
					mes "良かったら材料を集めてきてくれない？";
					close;
				}
				emotion 3;
				mes "[イメルダー]";
				mes "ありがとう！";
				mes "それじゃ今日もお願いするわ。";
				mes "届け先のリストはこれよ。";
				mes "地図にも記しておくわね。";
				mes "配り終えたらまた来てね。";
				viewpoint 1,181,353,0,0xFFFFFF;
				viewpoint 1,228,267,1,0xFFFF00;
				viewpoint 1,295,171,2,0x0000FF;
				viewpoint 1,119,217,3,0xCCCCCC;
				viewpoint 1,326,68,4,0x00FF00;
				viewpoint 1,223,267,5,0xFF0000;
				delquest 7375;
				setquest 72170;
				setquest 72174;
				setquest 72182;
				setquest 72178;
				setquest 72176;
				setquest 72172;
				setquest 72180;
				getitem 6503,6;
				close;
			}
		}
	}
OnInit:
	waitingroom "街を思う少女",0;
	end;
}

//============================================================
// 鉄鍋クエストNPC
//------------------------------------------------------------
malaya.gat,181,353,5	script	老人ナルド	574,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[老人ナルド]";
		mes "……";
		mes "この町の住人ではないようじゃな。";
		mes "私から話すことは何もない……。";
		close;
	case 2:
		if(checkquest(7353) & 0x8) {
			mes "[老人ナルド]";
			mes "お主が持っている物なら何でもいい、";
			mes "お主の気が吹き込まれている物を";
			mes "何かひとつ分けてくれないか？";
			next;
			mes "[老人ナルド]";
			mes "私はもう長くはない。";
			mes "後生のお願いじゃ。";
			close;
		}
		mes "[老人ナルド]";
		mes "お……お主は!!";
		mes "気の力が強く悪霊が近寄れないという";
		mes "若者ではないか?!";
		mes "わ……私にもその気を分けてくれないか？";
		next;
		mes "[老人ナルド]";
		mes "町をひっかき回している";
		mes "悪霊たちのせいで、";
		mes "夜もろくに眠れぬのじゃ……。";
		next;
		mes "[老人ナルド]";
		mes "その素晴らしい気を分けてくれ。";
		mes "お主の持ち物なら何でもいい！";
		mes "私にくれないか!?";
		next;
		menu "落ち着いてください",-;
		mes "[老人ナルド]";
		mes "私は落ち着いているさ！";
		mes "お主の持ち物ならきっと効果がある。";
		mes "私はお主の気が変わるまで";
		mes "ここで待っておるからの。";
		setquest 7353;
		compquest 7353;
		viewpoint 2,1,1,0,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "‐ナルドがすがるような目つきで";
		mes "　こちらを見ている。";
		mes "　ムンバキ・ポンに相談にいこう‐";
		close;
	case 4:
		if(checkquest(7360) & 0x8) {
			mes "[老人ナルド]";
			mes "実はのう。正直に話すと";
			mes "この聖なる物に本当に特別な力が";
			mes "あると思っているわけではない。";
			mes "これを持っていれば救われる、と";
			mes "信じることが、私の心を";
			mes "救ってくれるんじゃ。";
			next;
			mes "[老人ナルド]";
			mes "ともかく。お主を見直したわ。";
			mes "外部の人間だからといって";
			mes "無視してすまなかったの。";
			mes "私の考えが間違っていたようじゃ。";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[老人ナルド]";
		mes "おや、どうしたんじゃ。";
		mes "気が変わって何かくれるのか。";
		next;
		menu "準備した物を渡す",-;
		mes "‐老人ナルドに、準備した聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[老人ナルド]";
		mes "お……おお！";
		mes "あ……ありがとう。";
		mes "これで当分の間は気が楽になる。";
		mes "心が落ち着くのが一番だ。";
		delitem 717,1;
		delitem 523,1;
		setquest 7360;
		compquest 7360;
		viewpoint 2,1,1,0,0xFFFFFF;
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐老人を最後に";
			mes "　全て配り終えたようだ。";
			mes "　ムンバキ・ポンへ報告に戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[老人ナルド]";
		mes "この聖なる物に本当に特別な力が";
		mes "あると思っているわけではない。";
		mes "これを持っていれば救われる、と";
		mes "信じることが、私の心を";
		mes "救ってくれるんじゃ。";
		next;
		mes "[老人ナルド]";
		mes "そうだ。今度余裕がある時に";
		mes "私の仕事を手伝ってくれないかね？";
		mes "今は大丈夫だが、近々人手がいる。";
		mes "良かったら頼むわい。";
		close;
	case 6:
		if(checkquest(7369) || checkquest(72174)) {
			mes "[老人ナルド]";
			mes "おお、お主か。";
			mes "何か用ですかな。";
			next;
			mes "‐老人ナルドにお守りを渡した‐";
			next;
			mes "[老人ナルド]";
			mes "ほほぅ。新しいお守りか。";
			mes "ありがとう。";
			mes "イメルダーとお主には";
			mes "世話になるのう。";
			delitem 6503,1;
			if(checkquest(72174))
				delquest 72174;
			else
				delquest 7369;
			setquest 7383;
			viewpoint 2,1,1,0,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		if(checkquest(7377)) {
			mes "[老人ナルド]";
			mes "ムンバキ・キコがお礼として";
			mes "^FF0000退魔のお守り^000000をくれる手筈だが、";
			mes "ちゃんと貰って来たかの。";
			mes "お守りをたくさん集める事が";
			mes "私にとっての救いなのじゃよ。";
			next;
			if(checkitemblank() == 0) {
				mes "[老人ナルド]";
				mes "おや？";
				mes "アイテムをいっぱい持ち過ぎの";
				mes "ようじゃのう……";
				mes "アイテムを整理したらまた来るといい。";
				close;
			}
			mes "[老人ナルド]";
			mes "もしよければ次もまた来てくれ。";
			mes "バリオ・マヒワガで必要としている";
			mes "鉄鍋はいつも私が準備しているんじゃ。";
			delitem 6503,5;
			setquest 7378;
			delquest 7377;
			getitem 6497,1;
			if(checkre())
				getexp 50000,20000;
			else
				getexp 500000,200000;
			set $MalayaName$[1],strcharinfo(0);
			close;
		}
		mes "[老人ナルド]";
		mes "ポートマラヤは美しい町だ。";
		mes "伝統と新しいものが融合して";
		mes "調和をとっている。";
		next;
		mes "[老人ナルド]";
		mes "最近は悪霊に悩まされたが";
		mes "お主や多くの若者たちが";
		mes "頑張ってくれたおかげで";
		mes "安心して暮らせるようになった。";
		mes "ありがたい事だ。";
		next;
		if(checkquest(7376)) {
			if(select("話をする","鉄で作った鍋について") == 1) {
				switch(rand(1,4)) {
				case 1:
					if($MalayaName$[0] != "" && $MalayaName$[0] != strcharinfo(0)) {
						mes "[老人ナルド]";
						mes "商人たちと話していると、";
						mes $MalayaName$[0]+ "という";
						mes "名前をよく耳にする。";
						mes "その人は商才があるようだね。";
						close;
					}
				case 2:
					if($MalayaName$[1] != "" && $MalayaName$[1] != strcharinfo(0)) {
						mes "[老人ナルド]";
						mes "最近バリオ・マヒワガで";
						mes $MalayaName$[1]+ "という";
						mes "冒険者の名前を耳にする。";
						mes "君も名を知らしめてみたらどうだね。";
						close;
					}
				case 3:
					if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
						mes "[老人ナルド]";
						mes "カプレを知っているかね。";
						mes $MalayaName$[2];
						mes "という冒険者が、";
						mes "カプレを手伝っているらしい。";
						close;
					}
				case 4:
					mes "[老人ナルド]";
					mes "他の冒険者もお守りを一生懸命";
					mes "配っていたぞ。";
					mes "君たちの国の伝統なのかね。";
					close;
				}
			}
			mes "[老人ナルド]";
			mes "鍋はちゃんと渡してくれたか？";
			mes "ムンバキ・キコが^FF0000退魔のお守り^000000を";
			mes "くれるはずだ。それも持ってきてくれ。";
			mes "お守りはたくさんある方がいい。";
			close;
		}
		if(select("話をする","何か手伝いましょうか") == 1) {
			switch(rand(1,4)) {
			case 1:
				if($MalayaName$[0] != "" && $MalayaName$[0] != strcharinfo(0)) {
					mes "[老人ナルド]";
					mes "商人たちと話していると、";
					mes $MalayaName$[0]+ "という";
					mes "名前をよく耳にする。";
					mes "その人は商才があるようだね。";
					close;
				}
			case 2:
				if($MalayaName$[1] != "" && $MalayaName$[1] != strcharinfo(0)) {
					mes "[老人ナルド]";
					mes "最近バリオ・マヒワガで";
					mes $MalayaName$[1]+ "という";
					mes "冒険者の名前を耳にする。";
					mes "君も名を知らしめてみたらどうだね。";
					close;
				}
			case 3:
				if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
					mes "[老人ナルド]";
					mes "カプレを知っているかね。";
					mes $MalayaName$[2];
					mes "という冒険者が、";
					mes "カプレを手伝っているらしい。";
					close;
				}
			case 4:
				mes "[老人ナルド]";
				mes "他の冒険者もお守りを一生懸命";
				mes "配っていたぞ。";
				mes "君たちの国の伝統なのかね。";
				close;
			}
		}
		if(BaseLevel < 100) {
			mes "[老人ナルド]";
			mes "うむ……お主、私の手伝いをするには";
			mes "悪いがまだ修業が足りないようだ。";
			mes "そうじゃな。";
			mes "^FF0000BaseLv100以上^000000になったら";
			mes "その時にお願いさせてもらおう‐";
			close;
		}
		if(checkquest(7378)) {
			if(!(checkquest(7378) & 0x2)) {
				mes "[老人ナルド]";
				mes "今日はこれでもう充分だ。";
				mes "ただ、私の作った鍋も";
				mes "そう長くは持たない。";
				mes "使い方によっては一日で壊れるだろう。";
				next;
				mes "[老人ナルド]";
				mes "可能なら明日も来てくれ。";
				close;
			}
			mes "[老人ナルド]";
			mes "お主か！";
			mes "そうか。元気か。";
			next;
			mes "[老人ナルド]";
			mes "頼みがあるんじゃが……";
			mes "新しい鉄鍋を、また届けて";
			mes "ほしいんじゃ。";
			next;
			if(select("手伝う","手伝わない") == 2) {
				mes "[老人ナルド]";
				mes "そうか。すまなかったの。";
				mes "暇な時にでも手伝っておくれ。";
				close;
			}
			mes "[老人ナルド]";
			mes "この鉄で作った鍋だ。ポートマラヤの";
			mes "鍛冶屋は腕がいいからな。";
			mes "これをバリオ・マヒワガにいる";
			mes "ムンバキ・キコに渡してくれればいい。";
			mes "お礼に^FF0000退魔のお守り^000000をくれるはずだ。";
			mes "それを私の所に持ってきておくれ。";
			if(checkitemblank() == 0) {
				next;
				mes "[老人ナルド]";
				mes "おや？";
				mes "アイテムをいっぱい持ち過ぎの";
				mes "ようじゃのう……";
				mes "アイテムを整理したらまた来るといい。";
				close;
			}
			delquest 7378;
			setquest 7376;
			getitem 6504,5;
			close;
		}
		mes "[老人ナルド]";
		mes "おお、それはありがたい。";
		mes "ちょうど注文があったところでのう。";
		mes "助かるわい。";
		next;
		mes "[老人ナルド]";
		mes "お主に手伝ってほしいのは";
		mes "ここにある鉄で作った鍋を";
		mes "バリオ・マヒワガにいる";
		mes "ムンバキ・キコまで届けてほしいのだ。";
		next;
		switch(select("鉄で作った鍋？","手伝う","手伝わない")) {
		case 1:
			mes "[老人ナルド]";
			mes "そう。それはバコナワのせいだ。";
			mes "バリオ・マヒワガはバコナワの住処に";
			mes "近い為、いつも危険にさらされている。";
			mes "そのバコナワに有効なのが、";
			mes "この鉄鍋なんじゃよ。";
			next;
			mes "[老人ナルド]";
			mes "バコナワは敏感な為、音に弱い。";
			mes "この鉄鍋をトントン叩くと";
			mes "バコナワはビックリして";
			mes "飲み込んでいた月を吐き出すんじゃ。";
			next;
			mes "[老人ナルド]";
			mes "鉄鍋はバリオ・マヒワガの住人には";
			mes "欠かせない。";
			mes "いつ必要になるかわからないからな。";
			mes "それに、鍋を作る鍛冶屋は";
			mes "バリオ・マヒワガよりポートマラヤの";
			mes "方が優れているのだ。";
			next;
			mes "[老人ナルド]";
			mes "だからいつも私が";
			mes "持って行ってたのじゃが、";
			mes "最近は鍋の注文が多くてな。";
			mes "運んでくれると助かるわい。";
			close;
		case 2:
			mes "[老人ナルド]";
			mes "この鉄で作った鍋だ。ポートマラヤの";
			mes "鍛冶屋は腕がいいからな。";
			mes "これをバリオ・マヒワガにいる";
			mes "ムンバキ・キコに渡してくれればいい。";
			mes "お礼に^FF0000退魔のお守り^000000をくれるはずだ。";
			mes "それを私の所に持ってきておくれ。";
			if(checkitemblank() == 0) {
				next;
				mes "[老人ナルド]";
				mes "おや？";
				mes "アイテムをいっぱい持ち過ぎの";
				mes "ようじゃのう……";
				mes "アイテムを整理したらまた来るといい。";
				close;
			}
			delquest 72084;
			setquest 7376;
			getitem 6504,5;
			close;
		case 3:
			mes "[老人ナルド]";
			mes "そうか。すまなかったの。";
			mes "暇な時にでも手伝っておくれ。";
			close;
		}
	}
OnInit:
	waitingroom "鉄鍋",0;
	end;
}

malaya.gat,228,267,3	script	ローメル	573,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[ローメル]";
		mes "……";
		mes "　";
		mes "‐無視された‐";
		close;
	case 2:
		if(checkquest(7357) & 0x8) {
			mes "[ローメル]";
			mes "今、私たちは常に";
			mes "不安に怯えながら生きています……。";
			mes "このまま、心の安息さえ";
			mes "得ることができないのでしょうか……。";
			close;
		}
		mes "[ローメル]";
		mes "あ……";
		mes "あなたが噂の……。";
		next;
		mes "[ローメル]";
		mes "悪霊を寄せ付けないというあなたの";
		mes "持ち物を……";
		mes "お守り代わりに持てそうなものを";
		mes "ひとついただけませんか？";
		next;
		menu "持ち物はちょっと……",-;
		mes "[ローメル]";
		mes "そうですよね……。";
		mes "失礼しました。";
		mes "あなたの持ち物ならきっと";
		mes "悪霊を退けてくれるだろうと";
		mes "思ったらつい……。";
		mes "今の事は忘れてください。";
		setquest 7357;
		compquest 7357;
		viewpoint 2,1,1,1,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "‐ローメルが立ちつくし";
		mes "　悲しそうな眼をしながら";
		mes "　こちらを見ている。";
		mes "　ムンバキ・ポンに相談に行こう‐";
		close;
	case 4:
		if(checkquest(7364) & 0x8) {
			mes "[ローメル]";
			mes "本当に必要なのは";
			mes "自制心を持ち心の安定を保つことです。";
			mes "それが出来るようになれば";
			mes "悪霊とも堂々と向き合えると思います。";
			next;
			mes "[ローメル]";
			mes "今はこうした物に頼っていますが、";
			mes "これをきっかけにして";
			mes "強い心が持てるようになりたいです。";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[ローメル]";
		mes "……あなたですか。";
		mes "何の用です？";
		next;
		menu "準備した物を渡す",-;
		mes "‐ローメルに準備していた聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[ローメル]";
		mes "お……おお……！";
		mes "これを私に!?";
		mes "あ、ありがとうございます。";
		mes "あなたの気が感じられます。";
		mes "これで悪霊も怖くありません！";
		delitem 717,1;
		delitem 523,1;
		setquest 7364;
		compquest 7364;
		viewpoint 2,1,1,1,0xFFFFFF;
		if(checkquest(7363)&8 == 0) {
			next;
			mes "[ローメル]";
			mes "あの……差し出がましいとは思いますが";
			mes "私の娘にもお守りを";
			mes "いただけないでしょうか？";
			close;
		}
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐ローメルを最後に";
			mes "　全て配り終えたようだ。";
			mes "　ムンバキ・ポンへ報告に戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[ローメル]";
		mes "貰った物は大事にしています。";
		mes "娘もね。ありがとう。";
		close;
	case 6:
		if(checkquest(7373) || checkquest(72182)) {
			mes "[ローメル]";
			mes "こんにちは。";
			mes "良い天気ですね。";
			next;
			mes "‐ローメルにお守りを渡した‐";
			next;
			mes "[ローメル]";
			mes "新しいお守りですね。";
			mes "ありがとうございます。";
			delitem 6503,1;
			if(checkquest(72182))
				delquest 72182;
			else
				delquest 7373;
			setquest 7387;
			viewpoint 2,1,1,1,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		switch(rand(1,4)) {
		case 1:
			if($MalayaName$[0] != "" && $MalayaName$[0] != strcharinfo(0)) {
				mes "[ローメル]";
				mes "最近ウォアンさんが酒の席で";
				mes "俺たちの" +$MalayaName$[0];
				mes "俺たちの" +$MalayaName$[0];
				mes "と酔っぱらいながら叫んでいました。";
				mes "いったいふたりの間に";
				mes "何があったんでしょうかね。";
				close;
			}
		case 2:
			if($MalayaName$[1] != "" && $MalayaName$[1] != strcharinfo(0)) {
				mes "[ローメル]";
				mes $MalayaName$[1]+ "さんは、";
				mes "この町で一番の人気者です。";
				mes "隣町のバリオ・マヒワガでも";
				mes "有名なんですよ。";
				close;
			}
		case 3:
			if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
				mes "[ローメル]";
				mes "私の妻が時折寝言で";
				mes $MalayaName$[2];
				mes "という名前を呼んでいるんですが、";
				mes "誰なんでしょう……。";
				close;
			}
		case 4:
			mes "[ローメル]";
			mes "隣町のバリオ・マヒワガの人たちは";
			mes "本当に勇気があります。";
			mes "私は怖くて森に行くことすら無理なのに";
			mes "子供ですら平気で森に遊びに行きます。";
			close;
		}
	}
}

malaya.gat,223,267,5	script	タルラー	941,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[タルラー]";
		mes "あっ、わわ！";
		mes "　";
		mes "‐あなたと目が合うとビックリして";
		mes "　父親の後ろに隠れてしまった‐";
		close;
	case 2:
		if(checkquest(7356) & 0x8) {
			mes "[タルラー]";
			mes "タルラーは今晩";
			mes "悪霊に連れて行かれるかもしれません。";
			mes "怖い子供たちがタルラーに";
			mes "会いに来るかもしれないのです。";
			close;
		}
		mes "[タルラー]";
		mes "……タルラー……ん……あの……";
		mes "……あ……お父さん";
		next;
		mes "[ローメル]";
		mes "娘が毎晩怯えて寝れないようなんです。";
		mes "あなたの持ち物の中で";
		mes "お守り代わりに使えそうなものがあれば";
		mes "いただけませんか？";
		next;
		mes "[ローメル]";
		mes "何でもいいんです。";
		mes "お守りの代わりさえあれば、";
		mes "娘が怯える事もなくなると思うので。";
		next;
		menu "気休めにもなりませんよ",-;
		mes "[ローメル]";
		mes "そんなことはないですよ。";
		mes "それに、例え気休めだとしても";
		mes "娘が安心してくれれば良いんです。";
		mes "ですが無理強いは出来ないですね。";
		mes "気が変わったら、また来てください。";
		next;
		mes "[タルラー]";
		mes "あの……タルラーはここで待ってます。";
		mes "だから、その……お願いします。";
		setquest 7356;
		compquest 7356;
		viewpoint 2,1,1,5,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "‐タルラーが好奇心に満ちた目で";
		mes "　こちらと父親を交互に見ている‐";
		close;
	case 4:
		if(checkquest(7363) & 0x8) {
			if(checkquest(7364)&8 == 0) {
				mes "[タルラー]";
				mes "よくわからないけど";
				mes "温かい感じがします。";
				mes "あの、お父さんにも同じものを";
				mes "くれませんか？";
				close;
			}
			mes "[タルラー]";
			mes "よくわからないけど";
			mes "温かい感じがします。";
			mes "お父さんも元気になったし、";
			mes "タルラーも元気です！";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[タルラー]";
		mes "あ……挨拶してもいいですか？";
		mes "こ……こんにちは？";
		next;
		menu "準備した物を渡す",-;
		mes "‐タルラーに準備した聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[タルラー]";
		mes "光る青い石……！";
		mes "わぁ……きれい！";
		mes "これからはこの石が";
		mes "タルラーを守ってくれるんですか？";
		delitem 717,1;
		delitem 523,1;
		setquest 7363;
		compquest 7363;
		viewpoint 2,1,1,5,0xFFFFFF;
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐タルラーを最後に全員に配り終えた。";
			mes "　ムンバキ・ポンの元に戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[タルラー]";
		mes "お父さんに";
		mes "貰った石をちゃんと持ってなさい";
		mes "と、言われました。";
		mes "そうすると";
		mes "悪いお化けが近寄れないんだって！";
		close;
	case 6:
		if(checkquest(7372) || checkquest(72180)) {
			mes "[タルラー]";
			mes "こ……こんにちは。";
			mes "新しいお守りですか？";
			next;
			mes "‐タルラーに新しいお守りを渡した‐";
			next;
			mes "[タルラー]";
			mes "ありがとうございます。";
			mes "タルラーはこれがあると";
			mes "ぐっすり寝れるのです。";
			mes "お父さんも喜んでいます。";
			delitem 6503,1;
			if(checkquest(72180))
				delquest 72180;
			else
				delquest 7372;
			setquest 7386;
			viewpoint 2,1,1,5,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		mes "[タルラー]";
		mes "こ……こんにちは。";
		mes "あの……いつもお守り";
		mes "あ……ありがとうございます。";
		mes "わ……タルラーたちを";
		mes "守ってくれてるんですよね？";
		close;
	}
}

malaya.gat,62,274,0	script	砂くぼみ#mal01	557,{
	if(!checkquest(7366) && !checkquest(7380)) {
		mes "‐海水を蒸発させる簡易装置が";
		mes "　砂に埋まっている‐";
		close;
	}
	if(countitem(6501) >= 6) {
		mes "‐塩はもう十分集まった‐";
		close;
	}
	mes "‐海水を蒸発させる簡易装置が";
	mes "　砂くぼみに設置されている。";
	mes "　表面に塩が固まっている。";
	mes "　かき集めよう‐";
	next;
	if(checkitemblank() == 0) {
		mes "‐アイテムの種類数が多くて";
		mes "　持つことができない。";
		mes "　種類数を減らしてから拾おう‐";
		close;
	}
	progressbar 5;
	initnpctimer;
	hideonnpc strnpcinfo(0);
	getitem 6501,1;
	mes "‐塩を集めて袋につめた‐";
	close;
OnTimer15000:
	stopnpctimer;
	hideoffnpc strnpcinfo(0);
	end;
}

malaya.gat,66,277,0	duplicate(砂くぼみ#mal01)	砂くぼみ#mal02	557
malaya.gat,70,282,0	duplicate(砂くぼみ#mal01)	砂くぼみ#mal03	557
malaya.gat,71,288,0	duplicate(砂くぼみ#mal01)	砂くぼみ#mal04	557
malaya.gat,75,291,0	duplicate(砂くぼみ#mal01)	砂くぼみ#mal05	557
malaya.gat,80,292,0	duplicate(砂くぼみ#mal01)	砂くぼみ#mal06	557

ma_fild01.gat,178,206,0	script	黒い竹#mal01	844,8,8,{
	if(!checkquest(7366) && !checkquest(7380)) {
		mes "‐少し短めの黒い色をした竹がある‐";
		close;
	}
	if(countitem(6500) >= 6) {
		mes "‐尖った竹はもう十分集まった‐";
		close;
	}
	mes "‐全体が黒い竹がある。";
	mes "　この竹からイメルダーが欲しがる";
	mes "　尖った竹を用意できそうだ‐";
	next;
	if(checkitemblank() == 0) {
		mes "‐アイテムの種類数が多くて";
		mes "　持つことができない。";
		mes "　種類数を減らしてから拾おう‐";
		close;
	}
	progressbar 3;
	initnpctimer;
	hideonnpc strnpcinfo(0);
	getitem 6500,1;
	mes "‐適当な長さに切り整え、";
	mes "　尖った竹を手にいれた‐";
	close;
OnTouch:
	misceffect 362,strnpcinfo(0);
	end;
OnTimer30000:
	stopnpctimer;
	hideoffnpc strnpcinfo(0);
	misceffect 362,strnpcinfo(0);
	end;
}

ma_fild01.gat,225,186,0	duplicate(黒い竹#mal01)	黒い竹#mal02	844,8,8
ma_fild01.gat,230,244,0	duplicate(黒い竹#mal01)	黒い竹#mal03	844,8,8
ma_fild01.gat,174,238,0	duplicate(黒い竹#mal01)	黒い竹#mal04	844,8,8
ma_fild01.gat,180,273,0	duplicate(黒い竹#mal01)	黒い竹#mal05	844,8,8
ma_fild01.gat,179,145,0	duplicate(黒い竹#mal01)	黒い竹#mal06	844,8,8

//============================================================
// ジェジェリンの落し物クエストNPC
//------------------------------------------------------------
malaya.gat,295,171,3	script	収集品商人ウォアン	582,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[ウォアン]";
		mes "う……うう……頭が痛い……。";
		mes "俺の頭痛はきっとお前が";
		mes "外から持って来たんだろう！";
		mes "それ以外考えられん！";
		mes "あっちに行け、あっちに行ってくれ！";
		close;
	case 2:
		if(checkquest(7355) & 0x8) {
			mes "[ウォアン]";
			mes "なぁ……いいじゃないか？";
			mes "持ち物ひとつさえくれれば";
			mes "俺の心は救われるんだ。";
			mes "そんなに難しい事じゃないだろう。";
			close;
		}
		mes "[ウォアン]";
		mes "おぉ、噂の人じゃないか！";
		mes "もし仕事が必要なら";
		mes "俺がこの町で見つけてやるから……";
		mes "だから……お前の、その……";
		mes "も、持ち物をひとつくれないか？";
		next;
		mes "[ウォアン]";
		mes "お前が悪霊を追い払ったという";
		mes "噂はすでに聞いたよ！";
		mes "悪霊の恐怖で震えている";
		mes "俺の手を見てくれ。";
		emotion 28;
		next;
		mes "[ウォアン]";
		mes "お前の持ち物を何かひとつでも";
		mes "お守り代わりに貰えたら、";
		mes "この震えも収まる気がするんだ。";
		mes "なぁ……頼むよ。";
		next;
		menu "しっかりしてください",-;
		mes "[ウォアン]";
		mes "そんなこと言われても……。";
		mes "頼むよ……震えが止まらないんだ。";
		mes "お前が何か持ち物をくれるまで";
		mes "ここで待ってるからさ……。";
		setquest 7355;
		compquest 7355;
		viewpoint 2,1,1,2,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "[ウォアン]";
		mes "ふう……最近は生きて行くのが";
		mes "どうしてこんなに辛いんだ……。";
		mes "悪霊は何故出てきて";
		mes "俺たちを苦しめるんだ……。";
		mes "お守りのひとつでもあれば";
		mes "救われるのに。";
		next;
		mes "[ウォアン]";
		mes "お前の持ち物を護身用のお守りとして";
		mes "ひとつくれるだけでいいというのに！";
		mes "なぁ、人助けだと思ってさ、";
		mes "お前のその……靴下でもいいんだよ。";
		mes "くれないか？　頼む！";
		close;
	case 4:
		if(checkquest(7362) & 0x8) {
			mes "[ウォアン]";
			mes "おい、俺の手をみてくれよ。";
			mes "手の震えが前より随分と";
			mes "よくなっているようにみえないか？";
			mes "なんとなくそんな気がするが";
			mes "きっとそうに違いない。";
			mes "そうだろう？";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[ウォアン]";
		mes "ん？";
		mes "何だ、持ち物ひとつくれない、";
		mes "ケチな冒険者様か。";
		mes "何の用だ？";
		next;
		menu "準備した物を渡す",-;
		mes "‐ウォアンに準備した聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[ウォアン]";
		mes "お、おお……おぉぉ！";
		mes "素晴らしい！";
		mes "ああ、さっき言ったことは冗談だ。";
		mes "忘れてくれ。すぐ忘れてくれ。";
		mes "実はお前は必ず戻ってきてくれると、";
		mes "ずっと信じて待っていたんだよ。";
		next;
		mes "[ウォアン]";
		mes "いやぁ、助かったよ。";
		mes "これはお前の気の力の源か？";
		mes "なるほど。ほっほ～、なるほど。";
		mes "確かに涼しげながら厳かな感じがする。";
		mes "これさえあれば大丈夫だな、きっと。";
		next;
		mes "[ウォアン]";
		mes "いやぁ、ありがとう！";
		mes "後で簡単な仕事でも見つかったら、";
		mes "一番最初にお前に頼むことにするよ。";
		delitem 717,1;
		delitem 523,1;
		setquest 7362;
		compquest 7362;
		viewpoint 2,1,1,2,0xFFFFFF;
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐これですべての町人に配り終えた。";
			mes "　ムンバキ・ポンの元に戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[ウォアン]";
		mes "いやー、お前のおかげで悪霊にも";
		mes "苦しめられなくなったし、";
		mes "そろそろ事業再開するかなー。";
		mes "その時は仕事を回すから";
		mes "是非手伝ってくれよ！";
		mes "ははははは！";
		close;
	case 6:
		if(checkquest(7371) || checkquest(72178)) {
			mes "[ウォアン]";
			mes "よう、どうした？　仕事の催促か？";
			next;
			mes "‐ウォアンにお守りを渡した‐";
			next;
			mes "[ウォアン]";
			mes "おおぉ～！　新しいお守りか！";
			mes "素晴らしい。";
			mes "格式と伝統を感じるぜ。ありがとう！";
			mes "イメルダーが頑張っているようだな。";
			mes "もちろんお前にも感謝しているぜ！";
			delitem 6503,1;
			if(checkquest(72178))
				delquest 72178;
			else
				delquest 7371;
			setquest 7385;
			viewpoint 2,1,1,2,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		if(checkquest(7391)) {
			if(countitem(6498) >= 5) {
				if(checkitemblank() == 0) {
					mes "[ウォアン]";
					mes "んん～？";
					mes "持ち物がいっぱいのようだなー";
					mes "お礼を渡せないから、荷物を";
					mes "整理してから、また来てくれ。";
					close;
				}
				mes "[ウォアン]";
				mes "お、集めてきたね。";
				mes "ありがとう！";
				mes "ジェジェゼロピーは毎日集めているから";
				mes "また明日も来てくれると助かるよ。";
				mes "これはお礼だ。";
				mes "受け取ってくれ。";
				delitem 6498,5;
				setquest 7392;
				delquest 7391;
				getitem 6497,1;
				if(checkre())
					getexp 50000,20000;
				else
					getexp 500000,200000;
				set $MalayaName$[1],strcharinfo(0);
				close;
			}
		}
		mes "[ウォアン]";
		mes "おぅー。お前か！";
		next;
		menu "何か仕事は無いか",-;
		if(BaseLevel < 100) {
			mes "実は俺、こう見えて収集品商人なんだ。";
			mes "ここポートマラヤでも";
			mes "ジェジェゼロピーを収集しているんだ。";
			mes "仕事というのはその件なんだが……";
			next;
			mes "[ウォアン]";
			mes "お前にはまだ無理そうだ。 ";
			mes "この近辺は意外と危険だから";
			mes "もう少し強くなってからだな！";
			mes "そうだな。^FF0000BaseLv100以上^000000になったら";
			mes "また手伝いに来てくれよ。";
			close;
		}
		if(checkquest(7391)) {
			mes "[ウォアン]";
			mes "ん。どうした？";
			mes "^FF0000ジェジェゼロピー5個^000000だぞ。";
			mes "数は適当じゃ困るからな。";
			mes "集まったらまた来てくれ。";
			close;
		}
		if(checkquest(7392)) {
			if(!(checkquest(7392) & 0x2)) {
				mes "[ウォアン]";
				mes "お、ジェジェゼロピー収集の件か？";
				mes "今日、必要な分はすでにあるんだ。";
				mes "すまんな！";
				mes "明日、また来てくれ。";
				close;
			}
			mes "[ウォアン]";
			mes "お。今日も来てくれたか。";
			mes "ジェジェゼロピー集めを";
			mes "手伝ってくれるのか？";
			next;
			if(select("わかりました","お断りします") == 2) {
				mes "[ウォアン]";
				mes "そうか？　わかった。";
				mes "いつでも仕事が必要なら来てくれ。";
				close;
			}
			mes "[ウォアン]";
			mes "よっし。じゃあ頼むよ！";
			mes "ジェジェゼロピー5個だ。";
			mes "集まったら持ってきてくれ！";
			delquest 7392;
			setquest 7391;
			close;
		}
		mes "[ウォアン]";
		mes "実は俺は収集品商人なんだよ。";
		mes "色んな副産物を取引しているんだ。";
		mes "加工物の原材料となるからね。";
		mes "結構需要はあるんだよ。";
		next;
		mes "[ウォアン]";
		mes "というわけで色々と扱ってはいるが、";
		mes "ここポートマラヤで";
		mes "採れるものといえばやはり、";
		mes "ジェジェリンというモンスターから";
		mes "入手できるジェジェゼロピーだな！";
		next;
		mes "[ウォアン]";
		mes "というわけでお願いしたいのは";
		mes "そのジェジェゼロピー集めだ。";
		mes "^FF0000ジェジェゼロピーを5個^000000";
		mes "集めて来てくれないか？";
		next;
		if(select("わかりました","お断りします") == 2) {
			mes "[ウォアン]";
			mes "そうか。それならしょうがない。";
			mes "後で仕事が必要になったら";
			mes "その時にまた来てくれ。";
			close;
		}
		delquest 72086;
		mes "[ウォアン]";
		mes "よっし。じゃあ頼むよ！";
		mes "ジェジェゼロピー5個だ。";
		mes "集まったら持ってきてくれ！";
		setquest 7391;
		close;
	}
OnInit:
	waitingroom "ジェジェリンの落し物",0;
	end;
}

//============================================================
// パンドイのシルバーブレイドクエストNPC
//------------------------------------------------------------
malaya.gat,119,217,3	script	研修鍛冶屋パンドイ	538,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[パンドイ]";
		mes "ぎゃあ……あああ！";
		mes "お前さては悪霊の仲間だな！";
		mes "あ……あっち行け!!　早くいけ！";
		close;
	case 2:
		if(checkquest(7354) & 0x8) {
			mes "[パンドイ]";
			mes "先生……先生……！";
			mes "人助けだと思って何とかなりませんか？";
			mes "パンドイの事なんて放っておくのが";
			mes "一番だと、そんな風に";
			mes "思っているのですか！";
			next;
			mes "[パンドイ]";
			mes "先生……。お願いしますよ。";
			mes "持ち物のひとつやふたつ";
			mes "くれたっていいじゃないですか！";
			mes "先生には失望しましたよ……。";
			close;
		}
		mes "[パンドイ]";
		mes "あ、どうも！　お元気ですか？　先生！";
		mes "先生の名声はすでに轟いていますよ。";
		mes "それでね、先生。実は……";
		mes "先生にこうしてお会いできた証に";
		mes "何か1つ所持品を頂きたいのですが……";
		next;
		mes "[パンドイ]";
		mes "あ……。急に馴れ馴れしくして";
		mes "すいません。へへ。";
		mes "先生がお化けを退治したという";
		mes "噂は最近よく町で耳にしますが、";
		mes "パンドイはそれを聞く前から、先生は";
		mes "素晴らしい人だろうと思ってたんです。";
		next;
		mes "[パンドイ]";
		mes "えっ。調子の良いことを言うなって？";
		mes "いや、いやいやいや！";
		mes "パンドイは先生が町に来た時から";
		mes "素晴らしい人だと思っていたんです！";
		mes "へへ。";
		emotion 19;
		next;
		mes "[パンドイ]";
		mes "それでですね。";
		mes "先生の気が込められている物を";
		mes "何かいただければ、";
		mes "悪霊も怖くなくなると思うんですよ！";
		mes "だからお願いしますよ先生！";
		next;
		menu "気なんて込めていませんよ",-;
		mes "[パンドイ]";
		mes "そんな……！";
		mes "どうしてそんな嘘をつくんですか！";
		mes "先生はパンドイが悪霊に怯えていても";
		mes "何とも思わないのですか！";
		mes "先生……ひどいです！";
		setquest 7354;
		compquest 7354;
		viewpoint 2,1,1,3,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "[パンドイ]";
		mes "はぁ……本当……はぁ。";
		mes "最近は悪霊のせいで、";
		mes "色々つらいですよ。";
		mes "どうしてあいつら現れるんだろう。";
		next;
		mes "[パンドイ]";
		mes "先生……！";
		mes "人助けだと思って何とかなりませんか？";
		mes "パンドイの事なんて放っておくのが";
		mes "一番だと、そんな風に";
		mes "思っているのですか！";
		mes "先生には失望しましたよ……。";
		close;
	case 4:
		if(checkquest(7361) & 0x8) {
			mes "[パンドイ]";
			mes "さあ、先生のおかげで勇気も出たし、";
			mes "後は銀製品の材料を用意しに";
			mes "病院や町の外にいくだけだな！";
			mes "行くだけだな……だけ……。";
			mes "やっぱり病院は怖い……。";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[パンドイ]";
		mes "せ……先生！";
		mes "戻ってきてくれたという事は";
		mes "期待していいんですね!?";
		mes "パンドイに平穏を与えてくれると！";
		next;
		menu "準備した物を渡す",-;
		mes "‐パンドイに準備した聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[パンドイ]";
		mes "おお！　こ、これは!!";
		mes "パンドイは最初から先生は";
		mes "必ず戻ってくると信じていました！";
		mes "うおー！　先生の気を感じます！";
		mes "これで悪霊に怯えずに済みます。";
		mes "本当にありがとうございます。";
		delitem 717,1;
		delitem 523,1;
		setquest 7361;
		compquest 7361;
		viewpoint 2,1,1,3,0xFFFFFF;
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐これで全員に配り終えた。";
			mes "　ムンバキ・ポンのもとに戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[パンドイ]";
		mes "先生！　銀が必要なんですよ。";
		mes "パンドイには夢があるんです！　へへ。";
		mes "悪霊の恐怖を取り払ったら";
		mes "銀なんてすぐ採れる……。";
		mes "そう思っていたのに、";
		mes "やっぱりモンスターが怖いなぁ……。";
		close;
	case 6:
		if(checkquest(7370) || checkquest(72176)) {
			mes "[パンドイ]";
			mes "おお、先生！　それはもしかして";
			mes "イメルダーさんが作ったという";
			mes "新しいお守りですか！";
			mes "それをパンドイに？";
			next;
			mes "‐パンドイにお守りを渡した‐";
			next;
			mes "[パンドイ]";
			mes "さすが先生！　ありがとうございます！";
			mes "これでパンドイの平穏は保たれました！";
			delitem 6503,1;
			if(checkquest(72176))
				delquest 72176;
			else
				delquest 7370;
			setquest 7384;
			viewpoint 2,1,1,3,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		if((checkquest(7393) & 0x4) && countitem(6508) >= 10) {
			mes "[パンドイ]";
			mes "先生……さすがです！";
			mes "あの恐ろしい奴らを倒して";
			mes "注文通り、銀のブレスレットを";
			mes "手に入れてきてくれましたね。";
			next;
			mes "[パンドイ]";
			mes "今日から新しい銀製の武器作成を";
			mes "挑戦してみようと思います!!";
			mes "今まで一度も成功してないので";
			mes "何度も挑戦する事になると思うけど……";
			mes "最後には華麗な銀色の剣を";
			mes "自慢できるように頑張ります……!!";
			next;
			if(checkitemblank() == 0) {
				mes "[パンドイ]";
				mes "あれ？";
				mes "先生、アイテムをいっぱい";
				mes "持ち過ぎで、お礼を渡せません！";
				mes "アイテムを整理してから、";
				mes "もう一度来てください！";
				close;
			}
			mes "[パンドイ]";
			mes "さあ先生、これはお礼です。";
			mes "もし、今回の作成に失敗した時は……";
			mes "また材料の入手をお願いします！";
			delitem 6508,10;
			setquest 7394;
			delquest 7393;
			getitem 6497,1;
			if(checkre())
				getexp 50000,20000;
			else
				getexp 500000,200000;
			set $MalayaName$[1],strcharinfo(0);
			close;
		}
		switch(rand(1,4)) {
		case 1:
			if($MalayaName$[5] != "" && $MalayaName$[5] != strcharinfo(0)) {
				mes "[パンドイ]";
				mes $MalayaName$[5]+ "先生が";
				mes "とてもとても大きな発見を";
				mes "したらしいですよ。";
				mes "なんでも龍がどうとか……";
				break;
			}
		case 2:
			if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
				mes "[パンドイ]";
				mes "お会いした先生の中で、";
				mes $MalayaName$[2]+ "先生以上の";
				mes "働き者は見たことがありません。";
				mes "あの方は労働の神様です！";
				break;
			}
		case 3:
			if($MalayaName$[2] != "" && $MalayaName$[2] != strcharinfo(0)) {
				mes "[パンドイ]";
				mes "町の近くで";
				mes $MalayaName$[2]+ "先生が";
				mes "ジェジェリンを退治する姿を";
				mes "見たことがあるんですが、";
				mes "あの迫力は……";
				mes "ほ……惚れてしまいそうです！";
				break;
			}
		case 4:
			mes "[パンドイ]";
			mes "パンドイはですね、";
			mes "先生のようになりたいんです。";
			mes "先生の強さには本当に憧れます！";
			break;
		}
		next;
		switch(select("何か手伝おうか","銀の十字架を作ってほしい")) {
		case 1:
			if(BaseLevel < 100) {
				mes "[パンドイ]";
				mes "先生！　パンドイには夢があるんです！";
				mes "へへ……。";
				mes "一人前の鍛冶職人として認められる為、";
				mes "銀製の剣を作りたいんです！";
				mes "その為に必要な材料の入手を";
				mes "お願いしたかったのですが……";
				next;
				mes "[パンドイ]";
				mes "大変申し上げにくいんですが、";
				mes "先生の実力ではちょっと無理です。";
				mes "そうですね、具体的には";
				mes "^FF0000BaseLv100以上^000000になったら";
				mes "その時にでもお願いします。";
				close;
			}
			if(checkquest(7393)) {
				if(!(checkquest(7393) & 0x4)) {
					mes "[パンドイ]";
					mes "病院にはとても恐ろしい奴らがいます。";
					mes "パンドイは近づけないので";
					mes "詳しい事はよく分かりませんが……。";
					mes "とにかく病院は怖いんです。";
					next;
					mes "[パンドイ]";
					mes "病院にいる^FF0000マナナンガルとチャナックを";
					mes "10体ずつ^000000倒して、";
					mes "彼らが持っているという";
					mes "^FF0000銀のブレスレットを10個^000000";
					mes "手に入れてきて下さい！";
					mes "頼れるのは先生だけです！";
					close;
				}
				if(countitem(6508) < 10) {
					mes "[パンドイ]";
					mes "銀のブレスレットはどうしました？";
					mes "先生、ブレスレットは10個必要です。";
					mes "お願いします！　へへ。";
					close;
				}
				mes "[パンドイ]";
				mes "先生……さすがです！";
				mes "あの恐ろしい奴らを倒して";
				mes "注文通り、銀のブレスレットを";
				mes "手に入れてきてくれましたね。";
				next;
				mes "[パンドイ]";
				mes "今日から新しい銀製の武器作成を";
				mes "挑戦してみようと思います!!";
				mes "今まで一度も成功してないので";
				mes "何度も挑戦する事になると思うけど……";
				mes "最後には華麗な銀色の剣を";
				mes "自慢できるように頑張ります……!!";
				next;
				if(checkitemblank() == 0) {
					mes "[パンドイ]";
					mes "あれ？";
					mes "先生、アイテムをいっぱい";
					mes "持ち過ぎで、お礼を渡せません！";
					mes "アイテムを整理してから、";
					mes "もう一度来てください！";
					close;
				}
				mes "[パンドイ]";
				mes "さあ先生、これはお礼です。";
				mes "もし、今回の作成に失敗した時は……";
				mes "また材料の入手をお願いします！";
				delitem 6508,10;
				setquest 7394;
				delquest 7393;
				getitem 6497,1;
				if(checkre())
					getexp 50000,20000;
				else
					getexp 500000,200000;
				close;
			}
			if(checkquest(7394)) {
				if(!(checkquest(7394) & 0x2)) {
					mes "[パンドイ]";
					mes "まだ銀はいっぱい残っています。";
					mes "もし、もしも失敗して";
					mes "材料をすべて使い切ってしまったら";
					mes "その時はまた材料集めをお願いします。";
					next;
					mes "[パンドイ]";
					mes "へへ。先生！　見ててくださいね。";
					mes "やってやりますよ!!";
					mes "シルバーブレイドをね";
					mes "作って見せますよ！";
					close;
				}
				mes "[パンドイ]";
				mes "あ……せ、先生。";
				mes "パンドイはどうしたらいいでしょう？";
				mes "先生が苦労して集めてくれた材料を";
				mes "すべて使い切ったあげく……";
				mes "ろくな成果もありませんでした……。";
				next;
				mes "[パンドイ]";
				mes "やはりパンドイは鍛冶屋には";
				mes "向いてないんでしょうか……。";
				mes "銀細工なら自信があるのに！";
				next;
				if(select("また材料を集めてくるよ","諦めると楽になるよ") == 2) {
					mes "[パンドイ]";
					mes "確かにそうですね。";
					mes "パンドイにシルバーブレイドなんて";
					mes "作れるわけがなかったんです。";
					mes "さすが先生……あれ？";
					mes "違いますよ！";
					mes "私は先生に少し失望しました……。";
					close;
				}
				mes "[パンドイ]";
				mes "さすが先生です!!";
				mes "いつもありがとうございます。";
				next;
				mes "[パンドイ]";
				mes "では、今回も病院にいる";
				mes "^FF0000マナナンガルとチャナックを";
				mes "10体ずつ^000000倒して、";
				mes "^FF0000銀のブレスレット10個^000000";
				mes "集めてください。お願いします。";
				delquest 7394;
				setquest 7393;
				next;
				mes "[パンドイ]";
				mes "パンドイはお世話になりっぱなしです。";
				mes "先生に足を向けて寝れませんよ！";
				mes "へへへっ。";
				close;
			}
			mes "[パンドイ]";
			mes "先生！　パンドイには夢があるんです！";
			mes "一人前の鍛冶職人として認められる為";
			mes "銀製の剣を作りたいんです！";
			mes "その名もシルバーブレイド！";
			mes "今の所名前以外、形も性能も";
			mes "何も決まっていません！　へへ。";
			next;
			mes "[パンドイ]";
			mes "それでですね、先生。";
			mes "そのシルバーブレイドを作るには";
			mes "実は銀が必要なんです。";
			mes "それもたくさん！";
			next;
			mes "[パンドイ]";
			mes "銀を入手するにはどうしたらいいか";
			mes "パンドイは色々調べてみました。";
			mes "それによるとどうも町の病院で";
			mes "入院患者用に使用されていた";
			mes "ブレスレットが銀製だったそうです。";
			next;
			mes "[パンドイ]";
			mes "病院は今はもう閉鎖されていますが、";
			mes "当時使っていた用具であれば";
			mes "多少は残っているだろうと思って";
			mes "パンドイは病院に向かってみました。";
			next;
			mes "[パンドイ]";
			mes "ところがですよ……！";
			mes "中はひどい有様でした。";
			mes "病院というよりは、";
			mes "患者を増やす施設のような……。";
			mes "たくさんモンスターがいて、";
			mes "恐ろしい事になってたのです。";
			next;
			mes "[パンドイ]";
			mes "銀のブレスレットは";
			mes "そこにいたモンスターが";
			mes "持っているみたいです。";
			mes "でもパンドイにはモンスターを倒して";
			mes "ブレスレットを手に入れるなんて";
			mes "とてもできません。";
			next;
			mes "[パンドイ]";
			mes "そこで先生にお願いしたいんです。";
			mes "先生ならそいつらを倒して、";
			mes "銀のブレスレットを";
			mes "手に入れてこれますよね？";
			next;
			if(select("まかせて","面倒なので、お断りします") == 2) {
				mes "[パンドイ]";
				mes "ですよね……それもそうですよね。";
				mes "たとえ銀を取ってきたとしても";
				mes "パンドイにシルバーブレイドなんて";
				mes "作れるわけがないですもんね……。";
				mes "でも、何もそこまで露骨に";
				mes "嫌がらなくても……。";
				close;
			}
			mes "[パンドイ]";
			mes "やっぱり、さすが先生ですね！";
			mes "では病院にいる";
			mes "^FF0000マナナンガルとチャナックを";
			mes "10体ずつ^000000倒して、";
			mes "^FF0000銀のブレスレット10個^000000を";
			mes "集めてきてください！";
			delquest 72088;
			setquest 7393;
			next;
			mes "[パンドイ]";
			mes "先生には頭があがりません！";
			mes "へへへ。お願いします!";
			emotion 15;
			close;
		case 2:
			mes "[パンドイ]";
			mes "銀の十字架が必要ですか？　先生！";
			mes "任せてください！";
			mes "このパンドイが作って差し上げます。";
			mes "銀細工は得意なんですよ！　へへ。";
			next;
			mes "[パンドイ]";
			mes "あっと！　その前に！";
			mes "銀の十字架は一部地域では";
			mes "悪霊退治に使われるなど、";
			mes "神聖な物として取り扱われています。";
			mes "そのため、^FF0000他の人に渡したり、";
			mes "捨てたりすることができません。^000000";
			next;
			mes "[パンドイ]";
			mes "必要以上に持ち過ぎて、どうしても";
			mes "手放したい場合には、お店に引き取って";
			mes "貰ってくださいね。";
			mes "乱暴に扱ってバチが当たるのは";
			mes "さすがの先生でも嫌でしょう？　へへ。";
			next;
			mes "[パンドイ]";
			mes "さて！　銀の十字架を作るには、";
			mes "材料として銀が必要です。";
			mes "病院のモンスター達が持っている";
			mes "^4d4dff銀のブレスレット2個^000000で";
			mes "銀の十字架1個分の材料になります。";
			mes "いくつ作りますか先生？";
			next;
			switch(select("銀の十字架　1個","銀の十字架　6個","数を指定する","やめる")) {
			case 1:
				set '@num,1;
				mes "[パンドイ]";
				mes "銀の十字架、1個ですね。";
				mes "わかりました！　少し待って下さい。";
				mes "すぐに作業にとりかかります。";
				break;
			case 2:
				set '@num,6;
				mes "[パンドイ]";
				mes "お、先生もしかして";
				mes "イメルダーさんのお手伝いですか？";
				mes "銀の十字架、6個ですね。";
				mes "わかりました！　少し待って下さい。";
				break;
			case 3:
				mes "[パンドイ]";
				mes "わかりました先生！";
				mes "パンドイが一度に作れるのは";
				mes "最大50個までです！";
				mes "銀の十字架を何個作りますか？";
				next;
				input '@num;
				if('@num <= 0) {
					mes "[パンドイ]";
					mes "あれ？　銀の十字架いらないですか？";
					mes "作らなくていいなら楽できるので";
					mes "問題ないです先生！　へへ！";
					close;
				}
				if('@num > 50) {
					mes "[パンドイ]";
					mes "一度に作れるのは50個までです先生！";
					close;
				}
				if(countitem(6508) < '@num*2) {
					mes "[パンドイ]";
					mes "先生。銀が無いと作れません。";
					mes "銀の十字架を" +'@num+ "個作るためには";
					mes "銀のブレスレットが" +('@num*2)+ "個";
					mes "必要です。";
					close;
				}
				mes "[パンドイ]";
				mes "銀の十字架" +'@num+ "個ですね。";
				mes "わかりました！　少し待って下さい。";
				next;
				progressbar 15;
				delitem 6508,'@num*2;
				getitem 6502,'@num;
				mes "[パンドイ]";
				mes "これを見て下さい、先生！";
				mes "素晴らしい出来上がりです。";
				mes "やっぱりパンドイには";
				mes "細工師の方が向いているのかな。";
				close;
			case 4:
				mes "[パンドイ]";
				mes "いつでも必要な時に訪ねて下さい！";
				close;
			}
			if(countitem(6508) < '@num*2) {
				mes "[パンドイ]";
				mes "先生。銀が無いと作れません。";
				mes "銀の十字架を" +'@num+ "個作るためには";
				mes "銀のブレスレットが" +('@num*2)+ "個";
				mes "必要です。";
				close;
			}
			next;
			progressbar 5;
			delitem 6508,'@num*2;
			getitem 6502,'@num;
			mes "[パンドイ]";
			mes "これを見て下さい、先生！";
			mes "素晴らしい出来上がりです。";
			mes "やっぱりパンドイには";
			mes "細工師の方が向いているのかな。";
			close;
		}
	}
OnInit:
	waitingroom "パンドイのシルバーブレイド",0;
	end;
}

//============================================================
// ペリー号のゴーストクエストNPC
//- Registry -------------------------------------------------
// MALAYA_3QUE -> 0～6
//------------------------------------------------------------
malaya.gat,326,68,2	script	船員ペドロ	100,{
	switch(MALAYA_1QUE) {
	case 0:
	case 1:
		mes "[ペドロ]";
		mes "あ……この船は運行していません。";
		mes "いや、はは……。";
		mes "運行したくても、できないんですよ。";
		close;
	case 2:
		mes "[ペドロ]";
		mes "あれ、あなたは……";
		mes "ただ立っているだけで";
		mes "悪霊たちが逃げて行くという";
		mes "町で噂の冒険家ですか!?";
		mes "ちょっと私の話を聞いてくれますか？";
		next;
		if(select("いやです","わかりました") == 1) {
			mes "[ペドロ]";
			mes "おお、断固たる拒絶。";
			mes "悠然たる立ち居振る舞いから放たれる";
			mes "揺るぎ無い意志。";
			mes "さすがと言わざるを得ませんが、";
			mes "なんとか聞いてもらえませんか……。";
			close;
		}
		mes "[ペドロ]";
		mes "おお、ありがとうございます。";
		mes "実は、単刀直入に話しますと";
		mes "この町は今、悪霊の住み家に";
		mes "なってしまっているような状況です。";
		next;
		mes "[ペドロ]";
		mes "あそこにある船、見えますか？";
		mes "少し小さい船ですが、";
		mes "あれも悪霊のせいで足止めされて";
		mes "現在は運行を停止しています。";
		next;
		mes "[ペドロ]";
		mes "一見普通の町に見えますが、";
		mes "色々と呪われています……。";
		mes "ただ、聞くところによると";
		mes "悪霊を追い払う力をお持ちだとか……";
		mes "すごいですね。";
		next;
		menu "それほどでもない",-;
		mes "[ペドロ]";
		mes "そんなご謙遜なさらないでください。";
		mes "あなたの所持品をお守り代わりにすれば";
		mes "悪霊にも対抗できると考えています。";
		mes "お願いします。";
		mes "何かひとつ所持品をいただけませんか？";
		next;
		mes "[ペドロ]";
		mes "船が出せない事には仕事になりません。";
		mes "なので、私はあそこにいる悪霊たちと";
		mes "対峙しなければならないのです。";
		mes "しかし、悪霊達の気の力が強いため";
		mes "なかなか近くに行くことができません。";
		next;
		mes "[ペドロ]";
		mes "あっ、話が長くなってしまって";
		mes "すみませんでした。";
		mes "まあ、急に知らない人に";
		mes "所持品をくれといわれても";
		mes "なかなか難しいですよね。";
		next;
		menu "ごめんなさい",-;
		mes "[ペドロ]";
		mes "いえ、気にしないでください。";
		mes "そのかわり、悪霊に対抗できそうな";
		mes "方法がみつかった時には、";
		mes "私にも教えてくださいね。";
		if(!checkquest(7352)) {
			setquest 7352;
			compquest 7352;
		}
		viewpoint 2,1,1,4,0xFFFFFF;
		next;
		if( (
			checkquest(7352) + checkquest(7353) +
			checkquest(7354) + checkquest(7355) +
			checkquest(7356) + checkquest(7357)
		) == 48) {
			mes "‐すでに複数の町人から";
			mes "　同じようなお願いをされている。";
			mes "　どうしたものだろうか。";
			mes "　一度ムンバキ・ポンに";
			mes "　相談してみよう‐";
			delquest 7352;
			delquest 7353;
			delquest 7354;
			delquest 7355;
			delquest 7356;
			delquest 7357;
			delquest 72050;
			setquest 7358;
			set MALAYA_1QUE,3;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
			close;
		}
		mes "‐持ち物をわけてほしいと頼まれた。";
		mes "　他の町人にも話を聞いてみよう‐";
		close;
	case 3:
		mes "[ペドロ]";
		mes "はあ。";
		mes "早くなんとかしないと……。";
		close;
	case 4:
		if(checkquest(7359) & 0x8) {
			mes "[ペドロ]";
			mes "おかげ様でペリー号に居ついた";
			mes "悪霊と対峙することが出来そうです。";
			mes "後は、どうにか船の中から";
			mes "追い出すことができれば……！";
			close;
		}
		if(countitem(523) < 1 || countitem(717) < 1) {
			mes "^4d4dff‐ブルージェムストーンと聖水を";
			mes "　渡そう‐^000000";
			close;
		}
		mes "[ペドロ]";
		mes "おや、どうしました？";
		mes "何か気を感じますけど、";
		mes "もしかしてそれは……。";
		next;
		mes "[ペドロ]";
		mes "おぉ、やはりお守りですか！";
		mes "私にそれをくれるんですか?!";
		mes "本当にありがとうございます！";
		next;
		mes "‐ペドロに準備した聖水と";
		mes "　ブルージェムストーンを";
		mes "　1個ずつ渡した‐";
		next;
		mes "[ペドロ]";
		mes "冒険者様！　感謝しています！";
		mes "悪霊の問題が解決したら、";
		mes "私の船で世界の果てまで";
		mes "送って差し上げます!!";
		delitem 717,1;
		delitem 523,1;
		setquest 7359;
		compquest 7359;
		viewpoint 2,1,1,4,0xFFFFFF;
		if( (
			checkquest(7359) + checkquest(7360) +
			checkquest(7361) + checkquest(7362) +
			checkquest(7363) + checkquest(7364)
		) == 48) {
			next;
			mes "‐これですべての町人に配り終えた。";
			mes "　ムンバキ・ポンの元に戻ろう‐";
			delquest 7359;
			delquest 7360;
			delquest 7361;
			delquest 7362;
			delquest 7363;
			delquest 7364;
			delquest 7351;
			setquest 7365;
			set MALAYA_1QUE,5;
			viewpoint 2,1,1,0,0xFFFFFF;
			viewpoint 2,1,1,1,0xFFFFFF;
			viewpoint 2,1,1,2,0xFFFFFF;
			viewpoint 2,1,1,3,0xFFFFFF;
			viewpoint 2,1,1,4,0xFFFFFF;
			viewpoint 2,1,1,5,0xFFFFFF;
		}
		close;
	case 5:
		mes "[ペドロ]";
		mes "おかげ様でペリー号に居ついた";
		mes "悪霊と対峙することが出来そうです。";
		mes "後は、どうにか船の中から";
		mes "追い出すことができれば……！";
		next;
		mes "‐船の悪霊を思い出したのか、";
		mes "　ペドロの表情が緊張している‐";
		close;
	case 6:
		if(checkquest(7368) || checkquest(72172)) {
			mes "[ペドロ]";
			mes "おや、こんにちは冒険者様。";
			mes "風が気持ちいいですね。";
			next;
			mes "‐ペドロに^FF0000退魔のお守り^000000を渡した‐";
			next;
			mes "[ペドロ]";
			mes "おお、新しいお守りですか。";
			mes "ありがとうございます。";
			mes "本当に助かります。";
			delitem 6503,1;
			if(checkquest(72172))
				delquest 72172;
			else
				delquest 7368;
			setquest 7382;
			viewpoint 2,1,1,4,0xFFFFFF;
			if( (
				(checkquest(7382)&1) + (checkquest(7383)&1) +
				(checkquest(7384)&1) + (checkquest(7385)&1) +
				(checkquest(7386)&1) + (checkquest(7387)&1)
			) == 6) {
				setquest 7379;
				delquest 7382;
				delquest 7383;
				delquest 7384;
				delquest 7385;
				delquest 7386;
				delquest 7387;
				if(MALAYA_2QUE == 3)
					set MALAYA_2QUE,4;
				next;
				mes "‐すべての人に^FF0000退魔のお守り^000000を渡した。";
				mes "　イメルダーの所へ戻ろう‐";
				viewpoint 2,1,1,0,0xFFFFFF;
				viewpoint 2,1,1,1,0xFFFFFF;
				viewpoint 2,1,1,2,0xFFFFFF;
				viewpoint 2,1,1,3,0xFFFFFF;
				viewpoint 2,1,1,4,0xFFFFFF;
				viewpoint 2,1,1,5,0xFFFFFF;
			}
			close;
		}
		if(BaseLevel < 100) {
			mes "[ペドロ]";
			mes "今のペリー号は";
			mes "悪霊の住処となってしまっています。";
			mes "なんとか私の方でも頑張っていますが";
			mes "正直うまくいっていません……。";
			next;
			mes "[ペドロ]";
			mes "そこでひとつ手伝って欲しいのですが……";
			mes "冒険者様ではまだ実力不足のようです。";
			mes "そうですね、具体的には";
			mes "^FF0000BaseLv100以上^000000になったら";
			mes "その時にでもお願いします。";
			close;
		}
		switch(MALAYA_3QUE) {
		case 0:
			mes "[ペドロ]";
			mes "ひぃぃ！うわああ!!";
			next;
			mes "‐ペドロは何かに驚き、";
			mes "　震えている‐";
			next;
			if(select("声をかける","立ち去る") == 2) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "[ペドロ]";
			mes "い、い、今の見ましたか!?";
			mes "黒い霊がさーっと集まって";
			mes "ふっ、と消えたのを……。";
			mes "はぁ……。";
			mes "こんなことばかりで";
			mes "本当に気が滅入ります。";
			next;
			menu "船の運航について聞く",-;
			mes "[ペドロ]";
			mes "ペリー号はイズルードとの定期船";
			mes "なのですが……";
			next;
			mes "[ペドロ]";
			mes "今のペリー号は";
			mes "悪霊の住処となってしまっています。";
			mes "なんとか追い払って";
			mes "再出港できるようにしたいのですが";
			mes "今のところうまくいっていません……。";
			next;
			mes "[ペドロ]";
			mes "まずはこのようになった";
			mes "経緯をお話ししたいと思いますが";
			mes "よろしいでしょうか？";
			next;
			if(select("話を聞く","悪霊の話など聞きたくない") == 2) {
				mes "[ペドロ]";
				mes "そうですか……。";
				mes "悪霊の話を聞きたい人なんて";
				mes "普通いませんもんね……。";
				close;
			}
			mes "[ペドロ]";
			mes "話は私がこの町に初めて";
			mes "船を停泊する時にさかのぼります。";
			next;
			musiceffect "112";
			mes "[ペドロ]";
			mes "これまで不定期便で色々な町へ";
			mes "運航していた私にとって初めての";
			mes "定期船担当ということで、";
			mes "私は非常にワクワクしていました。";
			next;
			mes "[ペドロ]";
			mes "この港が見えたとき、イズルードからの";
			mes "航海を、無事予定した時刻に完了できた";
			mes "喜びに、私は最高に興奮しました。";
			mes "やったぞ！　完璧だ！";
			mes "ってね……。";
			next;
			sc_start3 SC_BLIND,0,0,0,0,360000,10;
			mes "[ペドロ]";
			mes "……ところが、です。";
			mes "港に停泊しようと近づくと、";
			mes "何やら1つ、2つと、黒い霧のような";
			mes "塊が見える。";
			next;
			mes "[ペドロ]";
			mes "何だろう？　と思いながらも、";
			mes "せっかくの完璧な航海を";
			mes "無駄にしたくありませんでしたから";
			mes "ペリー号を港に近づけました。";
			mes "すると、近づくうちに、黒い塊は";
			mes "どんどん増えていくようでした。";
			next;
			soundeffect "amon_ra_stand.wav",1,3000;
			mes "[ペドロ]";
			mes "いよいよいやーな予感がして……";
			mes "私はいったん船を止めようとしました。";
			mes "ですが……なぜか止まらない。";
			mes "それならばと舵を切ろうとしましたが、";
			mes "舵も効かない。";
			next;
			mes "[ペドロ]";
			mes "思いっきり力を込めても、叩いても、";
			mes "蹴飛ばしても、もちろん大きな声で";
			mes "叫んでも……無意味でした。";
			mes "言いようのない恐怖に";
			mes "私はただ震えました。";
			next;
			soundeffect "amon_ra_stand.wav",2,0;
			mes "[ペドロ]";
			mes "そうするうちにも、船は港に";
			mes "向かって進んで行きます。";
			mes "近づくにつれ、黒い塊も";
			mes "徐々に鮮明に見えて来たんです。";
			next;
			mes "[ペドロ]";
			mes "……まず、目が見えました";
			mes "黒い塊の中で真っ赤に染まる目……";
			mes "それも1つや2つではありません。";
			mes "無数の赤い目がありました。";
			next;
			soundeffect "solace_die.wav",0,0;
			mes "[ペドロ]";
			mes "そしてそれが、一様にこの船を";
			mes "見つめていたのです。";
			next;
			mes "[ペドロ]";
			mes "赤い目をし、黒い霧のような体を";
			mes "持った霊が、無数にひしめいていて……";
			mes "それが黒い塊に見えていたのでした。";
			next;
			mes "[ペドロ]";
			mes "なすすべもなく港に入ったペリー号を";
			mes "霊たちは一斉に取り囲んで、";
			mes "怪奇な音を出したり、泣き叫んだり……";
			next;
			mes "[ペドロ]";
			mes "その中の、恐ろしい女の悪霊が";
			mes "このペリー号を占拠してしまいました。";
			next;
			sc_end SC_BLIND;
			mes "[ペドロ]";
			mes "何とかしようとはしたのですが、";
			mes "その悪霊は恐ろしい力を持っていて……";
			mes "なんと、視界に入る者を触れることなく";
			mes "吹き飛ばすことができるのです。";
			next;
			mes "[ペドロ]";
			mes "私も何度も吹き飛ばされました……。";
			mes "もう私にはどうすることもできません。";
			mes "その為、船を出すことが";
			mes "出来ないでいるのです。";
			next;
			mes "[ペドロ]";
			mes "もし信じられないようでしたら";
			mes "直接船の中に入ってみて下さい。";
			mes "私が言ったことがわかるはずです。";
			delquest 72072;
			setquest 7395;
			set MALAYA_3QUE,1;
			close;
		case 1:
			mes "[ペドロ]";
			mes "もし信じられないようでしたら";
			mes "直接船の中に入ってみて下さい。";
			mes "私が言ったことがわかるはずです。";
			close;
		case 2:
			mes "[ペドロ]";
			mes "えっ。少女の霊が？";
			mes "イライラしていた？";
			mes "いったいどうなっているんでしょう。";
			mes "町の指導者ムンバキ・ポンなら";
			mes "アドバイスをくれるかもしれません。";
			close;
		case 3:
			mes "[ペドロ]";
			mes "なるほど。";
			mes "献花で少女の霊を慰めて、";
			mes "その後に話を聞くというわけですね。";
			mes "なかなか良さそうだと思います。";
			mes "では、よろしくお願いします。";
			close;
		case 4:
			mes "[ペドロ]";
			mes "ムンバキ・ポンが";
			mes "花に祝福をかけてくれたのですか。";
			mes "なるほど。";
			mes "良い結果が出る事を願っております。";
			mes "よろしくお願いします。";
			mes "私の代わりに交渉に成功して下さい！";
			close;
		case 5:
			mes "[ペドロ]";
			mes "冒険者様！";
			mes "花束を渡していただけましたか？";
			mes "それでいかがでしたか？";
			next;
			menu "ディワタについて話す",-;
			mes "[ペドロ]";
			mes "なんと！";
			mes "あの少女の霊は大自然の精霊";
			mes "だったのですか？";
			next;
			mes "[ペドロ]";
			mes "怖い顔で何度も私を";
			mes "吹き飛ばすものだから";
			mes "てっきり……";
			next;
			mes "[ペドロ]";
			mes "しかし、その精霊ディワタ様が";
			mes "この船を守ってくれると";
			mes "言ってくれたのですよね？";
			mes "それは大変心強い！";
			next;
			mes "[ペドロ]";
			mes "できれば、ディワタ様の機嫌が";
			mes "悪くならないよう、これからも";
			mes "定期的に花束を届けていただけると";
			mes "嬉しいです。";
			next;
			if(checkitemblank() == 0){
				// 未調査
				mes "[ペドロ]";
				mes "おや？";
				mes "持ち物が多すぎて、";
				mes "お礼を渡すことができません。";
				mes "持ち物を整理してから、";
				mes "もう一度来てください。";
				close;
			}
			mes "[ペドロ]";
			mes "今回はいろいろと助けて";
			mes "いただいて本当に";
			mes "ありがとうございます。";
			mes "大した物ではありませんが、";
			mes "これは私からのお礼です。";
			delquest 7399;
			setquest 7401;
			setquest 201505;
			set MALAYA_3QUE,6;
			getitem 6497,1;
			if(checkre()) {
				getexp 500000,0;
				getexp 500000,0;
				getexp 0,300000;
			}
			else {
				getexp 5000000,0;
				getexp 5000000,0;
				getexp 0,3000000;
			}
			set $MalayaName$[0],strcharinfo(0);
			next;
			mes "[ペドロ]";
			mes "私は航海の準備をします。";
			mes "運行再開の際には、無料で";
			mes "イズルードまでお送りします。";
			close;
		case 6:
			if(checkquest(7401)) {
				if(!(checkquest(7401) & 0x2)) {
					mes "[ペドロ]";
					mes "今はまだ、ディワタ様の機嫌が";
					mes "良いみたいです！";
					mes "機嫌が悪くなったら、";
					mes "また献花をお願いしますね。";
					next;
					menu "船の運航状況を聞く",-;
					mes "[ペドロ]";
					mes "アルベルタに行くなら隣にある";
					mes "大きな船を利用して下さい。";
					mes "このペリー号はイズルード行きです。";
					mes "料金は無料です。";
					next;
					if(select("利用する","利用しない") == 2) {
						mes "[ペドロ]";
						mes "ご利用の際には言ってください。";
						close;
					}
					mes "[ペドロ]";
					mes "それではイズルードに向けて";
					mes "出航します。";
					close2;
					warp "izlude.gat",195,180;
					end;
				}
				mes "[ペドロ]";
				mes "また悪霊たちが暴れ始めまして……";
				mes "それで、ディワタ様の機嫌も";
				mes "あまり良くないみたいです。";
				mes "お守りがあっても私のようなものでは";
				mes "耐えられません。";
				next;
				switch(select("船の運航状況を聞く","大変ですね","献花をしてこようか")) {
				case 1:
					mes "[ペドロ]";
					mes "悪霊が暴れていて、";
					mes "今はとても出航できるような";
					mes "状況ではありません。";
					close;
				case 2:
					mes "[ペドロ]";
					mes "お気遣いありがとうございます。";
					mes "いや、あの……出来れば……";
					mes "献花をして……いただけると……。";
					close;
				case 3:
					mes "[ペドロ]";
					mes "おお。ありがとうございます。";
					mes "是非、献花をしてあげてください。";
					mes "それでは、前回と同じ要領で";
					mes "よろしくお願いします。";
					delquest 7401;
					setquest 7402;
					close;
				}
			}
			if(checkquest(7403)) {
				mes "[ペドロ]";
				mes "ディワタ様が大人しくなりました。";
				mes "雰囲気が変わったのが";
				mes "外からも感じられます。";
				mes "毎回、世話になって本当にすみません。";
				next;
				mes "[ペドロ]";
				mes "もしよろしければ定期的に来て";
				mes "献花してあげてください。";
				next;
				if(checkitemblank() == 0){
					mes "[ペドロ]";
					mes "おや？";
					mes "持ち物が多すぎて、";
					mes "お礼を渡すことができません。";
					mes "持ち物を整理してから、";
					mes "もう一度来てください。";
					close;
				}
				mes "[ペドロ]";
				mes "これはお礼です。";
				mes "受け取ってください。";
				setquest 7401;
				delquest 7403;
				getitem 6497,1;
				if(checkre())
					getexp 50000,20000;
				else
					getexp 500000,200000;
				set $MalayaName$[0],strcharinfo(0);
				close;
			}
			mes "[ペドロ]";
			mes "前回と同じ要領で花を集めて。";
			mes "ムンバキ・ポンの所に持って行くと、";
			mes "安らぎの花束にしてくれるはずです。";
			mes "それをディワタ様に渡してください。";
			mes "よろしくお願いします。";
			next;
			menu "船の運航状況を聞く",-;
			mes "[ペドロ]";
			mes "悪霊が暴れていて、";
			mes "今はとても出航できるような";
			mes "状況ではありません。";
			close;
		}
	}
OnInit:
	waitingroom "ペリー号のゴースト",0;
	end;
}

ma_in01.gat,125,107,3	script	霊魂ディワタ	1752,4,4,{
	end;
OnTouch:
	switch(MALAYA_3QUE) {
	case 1:
		mes "‐部屋の隅に黒い何かが";
		mes "　うごめいている……";
		next;
		mes "‐よく見ると、";
		mes "　人の形をしている……！‐";
		next;
		menu "で、出たーーー!!",-,"誰だ!!",-;
		cutin "malaya_diwata01",2;
		mes "‐少女の姿をした黒いそれは、";
		mes "　こちらに気付くと、";
		mes "　苛立たしげに睨みつけてきた‐";
		next;
		mes "[ディワタ]";
		mes "……うるさい……";
		next;
		mes "‐全身黒ずくめで赤い瞳をした";
		mes "　した少女……";
		mes "　ペドロの言っていた悪霊は、";
		mes "　この少女のことだろう‐";
		next;
		mes "[ディワタ]";
		mes "出て行け!!";
		next;
		menu "待って！　話がしたい！",-;
		mes "[ディワタ]";
		mes "……お前らと話なんかない。";
		next;
		menu "お前ら？",-;
		cutin "malaya_ghost01",4;
		mes "‐振り向くと見覚えのある霊たちが";
		mes "　こちらに向かって歩いて来ている‐";
		next;
		menu "あの時の……",-;
		cutin "malaya_ghost02",4;
		mes "‐振り向いて、霊に歩み寄ると";
		mes "　町で遭遇した時と同じように";
		mes "　彼らは怯えはじめた‐";
		next;
		cutin "malaya_diwata01",2;
		mes "[ディワタ]";
		mes "……怯えている？";
		mes "なぜ……";
		next;
		mes "[ディワタ]";
		mes "……いや、そんなの関係ない！";
		mes "お前も一緒に消えろ!!";
		next;
		cutin "malaya_diwata01",255;
		mes "‐部屋に少女の声が響くと";
		mes "　不思議な力で";
		mes "　外に追い出されてしまった‐";
		setquest 7396;
		delquest 7395;
		set MALAYA_3QUE,2;
		close2;
		sc_end SC_BLIND;
		warp "malaya.gat",324,66;
		end;
	case 4:
		mes "‐ディワタが鋭い目つきで";
		mes "　こちらを見つめている。";
		mes "　用意した花束を……";
		cutin "malaya_diwata01",2;
		next;
		switch(select("正面からさっと手渡す","床に置いてそっと押し出す","武器代わりにして叩く")) {
		case 1:
			mes "‐花束をさっと手渡すと彼女は、";
			mes "　突然の贈り物に少し顔を赤らめ";
			mes "　動揺しはじめた‐";
			break;
		case 2:
			mes "‐床に花を置き彼女の方へ向けると";
			mes "　彼女は何がおきているかわからず";
			mes "　明らかに戸惑いはじめた‐";
			break;
		case 3:
			mes "[ディワタ]";
			mes "痛っ！";
			mes "ひどい……。";
			mes "どうしてそういう事するの？";
			mes "信じられない！";
			mes "早く消えてー！";
			next;
			cutin "malaya_diwata01",255;
			mes "‐部屋に少女の声が響くと";
			mes "　不思議な力で";
			mes "　外に追い出されてしまった‐";
			close2;
			warp "malaya.gat",324,66;
			end;
		}
		next;
		cutin "malaya_diwata02",2;
		mes "[ディワタ]";
		mes "花……すごい！　きれい……。";
		next;
		cutin "malaya_diwata01",2;
		mes "[ディワタ]";
		mes "これは……どういうつもり!?";
		mes "あなたは敵ではないってこと？";
		next;
		mes "[ディワタ]";
		mes "あれ？　良く見たらあなた、";
		mes "普通の人間なのね。";
		mes "……はあ～";
		mes "あの悪霊ども、人間には怯むくせに、";
		mes "私には向かってくるって、";
		mes "どういう事なの？";
		next;
		menu "君も悪霊じゃないの？",-;
		mes "[ディワタ]";
		mes "ちょっと！";
		mes "あんな奴らと私が同じものに";
		mes "見えるわけ？";
		mes "信じられない！";
		next;
		mes "[ディワタ]";
		mes "私は大自然の偉大なる精霊";
		mes "ディワタよ！";
		mes "守護する者なのっ！";
		next;
		mes "[ディワタ]";
		mes "そんな私とあいつらの区別が";
		mes "つかないなんて……";
		mes "これだから町は嫌い。";
		mes "なんかまたイライラしてきた！";
		next;
		mes "[ディワタ]";
		mes "もう消えてーーー！";
		next;
		menu "君のせいで船が出港できないんだ！",-;
		mes "[ディワタ]";
		mes "えっ……";
		mes "私のせいで船が運航できないの？";
		mes "どうして？";
		mes "　";
		mes "……あっ！";
		next;
		mes "[ディワタ]";
		mes "そういえば……";
		mes "悪霊たちと間違えて何度か";
		mes "船乗りっぽい人間も吹き飛ばして";
		mes "しまったような……";
		next;
		mes "[ディワタ]";
		mes "……でも！";
		mes "わざとじゃないの！";
		mes "あいつらが暴れるのを見ると";
		mes "気分が悪くなっちゃって。";
		next;
		mes "[ディワタ]";
		mes "それなのにあいつら、次から次と";
		mes "現れるでしょ？";
		mes "だから私も、手当り次第吹き飛ばす";
		mes "しかなくって……";
		next;
		mes "[ディワタ]";
		mes "……うん！　ごめんっ！";
		mes "見境なく吹き飛ばすなんて";
		mes "ひどいことをしてしまったわ。";
		next;
		mes "[ディワタ]";
		mes "この船の船員に伝えて。";
		mes "お詫びと言ってはなんだけど、";
		mes "この船は今後、私が守護して";
		mes "あげるって。";
		mes "もう悪霊に縛られることは";
		mes "なくなるわ。";
		next;
		mes "[ディワタ]";
		mes "ただ、さっきも言ったけど、";
		mes "あいつらを見てると私、";
		mes "どんどん気分が悪くなっちゃうんだ。";
		next;
		cutin "malaya_diwata02",2;
		mes "[ディワタ]";
		mes "だから、これからも定期的に";
		mes "お花を持ってきてくれないかな？";
		next;
		mes "[ディワタ]";
		mes "お花を見てると、とっても";
		mes "落ち着くんだ。";
		mes "えへへ……";
		next;
		mes "[ディワタ]";
		mes "よろしくね！";
		delitem 6506,1;
		delquest 7398;
		setquest 7399;
		set MALAYA_3QUE,5;
		close2;
		cutin "malaya_diwata02",255;
		end;
	case 5:
		cutin "malaya_diwata02",2;
		mes "[ディワタ]";
		mes "悪霊がこの船に悪さをしないよう";
		mes "私が守護するね。";
		next;
		mes "[ディワタ]";
		mes "でも、あいつらの相手をしているうちに";
		mes "私の気分も悪くなってしまうから、";
		mes "その時はまたお花を持ってきて";
		mes "ちょうだい！";
		close2;
		cutin "malaya_diwata02",255;
		end;
	case 6:
		if(checkquest(7401) || checkquest(7403)) {
			if(checkquest(7401) & 0x2) {
				cutin "malaya_diwata01",2;
				mes "[ディワタ]";
				mes "あっちに行って!!";
				mes "あれ？　あなたなの？";
				mes "あの田舎のごろつきお化けたちが";
				mes "また来たの！　許さない！";
				close2;
				cutin "malaya_diwata01",255;
				end;
			}
			cutin "malaya_diwata02",2;
			mes "[ディワタ]";
			mes "異国の花を見るのは楽しい。";
			mes "温かい国の花たちは";
			mes "こんな甘い香りがするんだね。";
			next;
			if(select("また持ってくるよ","なぜこの船に乗っているの？") == 1) {
				mes "[ディワタ]";
				mes "ありがとう。";
				mes "あなたが持って来る花を見ると";
				mes "心が落ち着くよ。";
				mes "……。";
				close2;
				cutin "malaya_diwata02",255;
				end;
			}
			mes "[ディワタ]";
			mes "ん……";
			mes "もともとは山に住んでいたんだけど、";
			mes "山にあった木箱の中でお昼寝して";
			mes "いたら、いつの間にかこの船に";
			mes "運ばれていたみたい。";
			next;
			mes "[ディワタ]";
			mes "いつもなら私の姿は普通の人間には";
			mes "見えないようにしているんだけど、";
			mes "悪霊どもの相手をすることに";
			mes "集中していたものだから……";
			mes "それで船員にも私が";
			mes "見えちゃったのね。";
			next;
			emotion 2;
			mes "[ディワタ]";
			mes "でも、船での生活も悪くはないわね！";
			mes "私のいた山では見たことのない花を";
			mes "いっぱい見ることができたもの。";
			close2;
			cutin "malaya_diwata02",255;
			end;
		}
		cutin "malaya_diwata01",2;
		mes "[ディワタ]";
		mes "悪霊め！　また来たの!?";
		mes "あれ？";
		mes "なんだ、あなただったの？";
		mes "今の私は機嫌があまり良くないよ。";
		next;
		mes "‐ディワタは当たり前のように";
		mes "　手を差し伸べた。";
		mes "　何かを要求しているようだ‐";
		next;
		if(select("花束を渡す","手を握り合う") == 2) {
			mes "[ディワタ]";
			mes "やめてよ、気持ち悪い！";
			mes "ああ、ただでさえ今は";
			mes "イライラしているのに！";
			mes "あなたまで私をイライラさせるの!?";
			next;
			cutin "malaya_diwata01",255;
			mes "‐イライラしているディワタの怒りと";
			mes "　共に船の外に出されてしまった‐";
			close2;
			warp "malaya.gat",324,66;
			end;
		}
		cutin "malaya_diwata02",2;
		mes "[ディワタ]";
		mes "あ……やっぱり持って来てくれたのね！";
		mes "唯一私の楽しみ、私の心が安らぐ……！";
		mes "異国の花たちよ～！";
		next;
		mes "‐ディワタの気分が良くなったせいで";
		mes "　周辺の気が温かくなって";
		mes "　雰囲気もよくなった ‐";
		next;
		mes "[ディワタ]";
		mes "ペドロに伝えてちょうだい。";
		mes "今日はディワタが太陽になるから";
		mes "気にせずに航海していいよって。";
		delitem 6506,1;
		setquest 7403;
		delquest 72065;
		next;
		cutin "malaya_diwata02",255;
		mes "‐ディワタに花束を渡した。";
		mes "　ペドロに報告しよう‐";
		close;
	default:
		cutin "malaya_diwata01",2;
		mes "[ディワタ]";
		mes "また来たな！";
		mes "早く消えろー!!";
		next;
		cutin "malaya_diwata01",255;
		mes "‐部屋に少女の声が響くと";
		mes "　不思議な力で";
		mes "　外に追い出されてしまった‐";
		close2;
		warp "malaya.gat",324,66;
		end;
	}
}

ma_in01.gat,108,92,0	script	#ディワタ演出	139,5,5,{
	if(MALAYA_3QUE == 1) {
		musiceffect "112";
		sc_start3 SC_BLIND,0,0,0,0,360000,10;
	}
	end;
}

ma_in01_jp.gat,45,154,3	script	ムンバキ・キコ	580,{
	if(checkquest(7376)) {
		mes "[ムンバキ・キコ]";
		mes "おお、これはお願いしていた鍋だな！";
		mes "なるほど、素晴らしい！";
		mes "これでバコナワを苦しめる事ができる。";
		next;
		if(checkitemblank() == 0) {
			mes "[ムンバキ・キコ]";
			mes "むむ！";
			mes "持ち物が多すぎのようだぞ。";
			mes "持ち物を整理してから、";
			mes "もう一度話しかけてくれ。";
			close;
		}
		mes "[ムンバキ・キコ]";
		mes "それじゃあ、すまないが鍋のお礼に";
		mes "このお守りを渡して来てくれないかね。";
		mes "聞いた話だと";
		mes "悪霊に苦労しているそうだな。";
		mes "これを持って行けば力になるはずだ。";
		mes "すまないが頼んだよ。";
		delitem 6504,5;
		setquest 7377;
		getitem 6503,5;
		delquest 7376;
		close;
	}
	if(checkquest(72060) && countitem(523) >= 10) {
		mes "[ムンバキ・キコ]";
		mes "うむ、この悪霊の骨には";
		mes "すべて悪い気が宿っている。";
		mes "ただその分この骨には";
		mes "強いエネルギーも含まれているんだ。";
		mes "そこでそのエネルギーを利用するために";
		mes "聖水を利用してこのようにすると……";
		next;
		if(checkitemblank() == 0) {
			mes "[ムンバキ・キコ]";
			mes "むむ！";
			mes "持ち物が多すぎのようだぞ。";
			mes "持ち物を整理してから、";
			mes "もう一度話しかけてくれ。";
			close;
		}
		mes "[ムンバキ・キコ]";
		mes "さあ、できた。";
		mes "これをバンタイに与えれば";
		mes "強い力を得る事が出来るだろう。";
		mes "それじゃあ、すまないがこの骨を";
		mes "ドンに渡してきてくれ。";
		delitem 6507,10;
		delitem 523,10;
		setquest 7407;
		getitem 6505,10;
		delquest 72060;
		close;
	}
	mes "[ムンバキ・キコ]";
	mes "ああ、今日も忙しい。";
	mes "悪霊が出没するようになって";
	mes "休む暇もなくなってしまった。";
	mes "　";
	mes "おや、冒険者の方がいらしていたのか。";
	next;
	mes "[ムンバキ・キコ]";
	mes "バリオ・マヒワガにようこそ冒険者よ。";
	mes "私はここバリオ・マヒワガで";
	mes "人と霊を見守っている霊道師";
	mes "ムンバキ・キコだ。";
	if(checkquest(7377) || checkquest(72060) || checkquest(7407)) {
		mes "何かご用かね。";
		next;
		switch(select("鉄の鍋について","悪霊の骨の浄化について")) {
		case 1:
			if(!checkquest(7377)) {
				mes "[ムンバキ・キコ]";
				mes "ん？　確かに鍋の注文はしたけど";
				mes "君には頼んでいないぞ。";
				mes "何か勘違いをしているんじゃないか？";
				close;
			}
			mes "[ムンバキ・キコ]";
			mes "ここ、バリオ・マヒワガの鍛冶屋で";
			mes "性能の良い鍋を作るのは難しい。";
			mes "それで毎回ポートマラヤにある";
			mes "鍛冶屋の世話になっている。";
			next;
			mes "[ムンバキ・キコ]";
			mes "バコナワは大きな音を嫌うのだ。";
			mes "我々はバコナワ対策として";
			mes "鉄で作った頑丈な鍋を力一杯叩く。";
			mes "その為、頻繁に鍋が壊れてしまう。";
			mes "だから替えがいくつも必要なんだ。";
			next;
			mes "[ムンバキ・キコ]";
			mes "とにかくありがとう。";
			mes "すまんがお守りを渡す件は";
			mes "頼んだよ。";
			close;
		case 2:
			if(!checkquest(7407)) {
				mes "[ムンバキ・キコ]";
				mes "バンタイが食べる骨の";
				mes "浄化のことかな。";
				mes "確かにそれは私が請け負っているが、";
				mes "ふむ。";
				mes "今の君には関係ない事だな。";
				close;
			}
			mes "[ムンバキ・キコ]";
			mes "バンタイがお腹を空かしているだろう。";
			mes "急いで持って行ってあげなさい。";
			close;
		}
	}
	close;
}

//============================================================
// 警備犬バンタイクエストNPC
//------------------------------------------------------------
ma_in01.gat,122,158,0	script	警備隊員ドン	570,{
	if(checkquest(7407)) {
		mes "[警備隊員ドン]";
		mes "これはバンタイが喜びますね！";
		mes "うーん、出来立ては新鮮だ。";
		mes "ありがとうございます！";
		next;
		if(checkweight(6497,1) == 0) {
			mes "[警備隊員ドン]";
			mes "おや？";
			mes "持ち物が多すぎて、";
			mes "お礼を渡すことができません。";
			mes "持ち物を整理してから、";
			mes "もう一度来てください。";
			close;
		}
		mes "[警備隊員ドン]";
		mes "これはお礼です。";
		mes "出来れば明日もまた";
		mes "やってもらえると助かります。";
		delitem 6505,10;
		setquest 7408;
		delquest 7407;
		getitem 6497,1;
		if(checkre())
			getexp 50000,20000;
		else
			getexp 500000,200000;
		set $MalayaName$[2],strcharinfo(0);
		close;
	}
	mes "[警備隊員ドン]";
	mes "ふうぅ……。";
	next;
	if(select("声をかける","声をかけない") == 2) {
		mes "‐声をかけずにその場を離れた。‐";
		close;
	}
	if(BaseLevel < 100) {
		mes "[警備隊員ドン]";
		mes "実は今、バンタイという警備犬の";
		mes "餌を探していたのですが、";
		mes "少し足りませんでした。";
		mes "ちょっと変わった餌なので誰かに用意を";
		mes "手伝ってもらいたかったのですが……";
		mes "あなたにはちょっと無理そうですね。";
		next;
		mes "[警備隊員ドン]";
		mes "そうですね、具体的には";
		mes "^FF0000BaseLv100以上^000000になったら";
		mes "是非その時にでも手伝ってください。";
		close;
	}
	if(checkquest(7408)) {
		if(!(checkquest(7408) & 0x2)) {
			mes "[警備隊員ドン]";
			mes "あ！";
			mes "お手伝いありがとうございました！";
			mes "これで当分の間バンタイは";
			mes "良い仕事をするでしょう。";
			next;
			mes "[警備隊員ドン]";
			mes "え、警備もせずに";
			mes "私がここで何をしているかって？";
			mes "勘違いしてはいけません。";
			mes "外はバンタイが見張ってくれてるので";
			mes "私は部屋の警備をしているのです。";
			close;
		}
		mes "[警備隊員ドン]";
		mes "バンタイに与える骨が";
		mes "足りなくなってしまいました。";
		mes "お願いします。私のかわりにどうか";
		mes "用意して来てくれませんか？";
		next;
		if(select("手伝う","手伝わない") == 2) {
			mes "[警備隊員ドン]";
			mes "そ、そんな……。";
			close;
		}
		mes "[警備隊員ドン]";
		mes "ありがとうございます。";
		mes "^FF0000悪霊の骨^000000は、北西の家にいる";
		mes "ティクバラン専門家が持っています。";
		mes "頼めば分けてくれるでしょう。";
		next;
		mes "[警備隊員ドン]";
		mes "それをムンバキ・キコの所に";
		mes "持って行くと";
		mes "バンタイが食べられるよう";
		mes "浄化の儀式をほどこしてくれます。";
		next;
		mes "[警備隊員ドン]";
		mes "それでは浄化の終わった";
		mes "^FF0000浄化した霊魂の骨^000000を10個";
		mes "持って来てください。";
		mes "そういえば浄化儀式には";
		mes "^FF0000聖水^000000も同じ数だけ使われるようです。";
		next;
		mes "[警備隊員ドン]";
		mes "では、お待ちしております。";
		delquest 7408;
		setquest 7406;
		close;
	}
	if(checkquest(7406) || checkquest(106176) || checkquest(72060)) {
		mes "[警備隊員ドン]";
		mes "悪霊の骨は、北西の家にいる";
		mes "ティクバラン専門家が持っています。";
		mes "よろしくお願いします。";
		close;
	}
	mes "[警備隊員ドン]";
	mes "こんにちは。";
	mes "私はバリオ・マヒワガの警備をしている";
	mes "ドンといいます。";
	next;
	mes "[警備隊員ドン]";
	mes "実は、警備を一緒にしている";
	mes "バンタイという犬の";
	mes "餌をちょうど探していたのです。";
	mes "村の入り口に立っていたと思います。";
	mes "非常に優秀な警備犬です。";
	next;
	mes "[警備隊員ドン]";
	mes "バンタイですが、実は";
	mes "この村の生まれではないんです。";
	mes "以前、村の住人が旅に行った際に";
	mes "帰りの船で倒れている犬を";
	mes "拾って来たんです。";
	next;
	mes "[警備隊員ドン]";
	mes "はじめて会った時のバンタイは";
	mes "すごく餓えていました。";
	mes "かわいそうに、長い間";
	mes "何も食べていなかったのでしょう。";
	mes "いきなり腕を食べようとしてきました。";
	next;
	mes "[警備隊員ドン]";
	mes "首輪もつけていたんです。";
	mes "研……実験…物……第4…？";
	mes "まぁ、よくわからなかったので、";
	mes "すぐはずしました。";
	next;
	mes "[警備隊員ドン]";
	mes "それで、私は動物が大好きなので";
	mes "その犬を引き取る事にしました。";
	mes "名前もすぐ決めましたよ。";
	mes "‐バンタイ‐";
	mes "どうです。いい名前でしょう。";
	next;
	mes "[警備隊員ドン]";
	mes "始めは色々と苦労しました。";
	mes "ここに来る以前に人を襲う訓練でも";
	mes "受けていたのでしょうか……。";
	mes "近寄ると直ぐに";
	mes "噛みついてくるんですよ。";
	next;
	mes "[警備隊員ドン]";
	mes "ただ、私は諦めませんでした。";
	mes "むしろバンタイのこの性格は";
	mes "逆にチャンスだと思ったんです。";
	next;
	mes "[警備隊員ドン]";
	mes "警備に活かせるんじゃないか、とね。";
	mes "成功すれば私は楽を出来ます。";
	mes "私が楽を出来る可能性がある、";
	mes "ということが、";
	mes "何よりも私の原動力となりました。";
	next;
	mes "[警備隊員ドン]";
	mes "そこでティクバラン専門家であり";
	mes "動物の行動に詳しい先生に";
	mes "相談しに行ったんです。";
	mes "そこで提案されたのが";
	mes "^FF0000浄化した霊魂の骨^000000というのを";
	mes "バンタイに食べさせることです。";
	next;
	mes "[警備隊員ドン]";
	mes "なんでもこれを食べると";
	mes "悪霊の気を探知し、聖なる力で";
	mes "悪霊を退治できるようになるそうです。";
	next;
	mes "[警備隊員ドン]";
	mes "狙いは見事にうまくいきました。";
	mes "浄化した霊魂の骨を食べたバンタイは";
	mes "人間を襲うことなく、";
	mes "素早く悪霊を探知し、物凄い強さで";
	mes "追い払ってくれるようになったのです。";
	next;
	mes "[警備隊員ドン]";
	mes "ただ、毎日骨は必要なので、";
	mes "いくら用意しても";
	mes "すぐに足りなくなってしまいます。";
	next;
	mes "[警備隊員ドン]";
	mes "今日もさきほどちょうど";
	mes "バンタイに与える骨が";
	mes "足りなくなってしまいました。";
	mes "お願いします。私のかわりにどうか";
	mes "用意して来てくれませんか？";
	next;
	if(select("手伝う","手伝わない") == 2) {
		mes "[警備隊員ドン]";
		mes "そ、そんな……。";
		close;
	}
	mes "[警備隊員ドン]";
	mes "ありがとうございます。";
	mes "^FF0000悪霊の骨^000000は、北西の家にいる";
	mes "ティクバラン専門家が持っています。";
	mes "頼めば分けてくれるでしょう。";
	next;
	mes "[警備隊員ドン]";
	mes "それをムンバキ・キコの所に";
	mes "持って行くと";
	mes "バンタイが食べられるよう";
	mes "浄化の儀式をほどこしてくれます。";
	next;
	mes "[警備隊員ドン]";
	mes "それでは浄化の終わった";
	mes "^FF0000浄化した霊魂の骨^000000を10個";
	mes "持って来てください。";
	mes "そういえば浄化儀式には";
	mes "^FF0000聖水^000000も同じ数だけ使われるようです。";
	next;
	mes "[警備隊員ドン]";
	mes "では、お待ちしております。";
	delquest 72090;
	setquest 7406;
	close;
OnInit:
	waitingroom "警備犬バンタイ",0;
	end;
}

ma_fild01.gat,238,257,2	script	警備犬バンタイ	972,{
	mes "[バンタイ]";
	mes "ガルゥルルゥ……。";
	mes "　";
	mes "‐あなたを警戒している‐";
	close;
}

//============================================================
// マリスの子供探しクエストNPC
//------------------------------------------------------------
ma_in01_jp.gat,42,155,7	script	マリス	579,{
	if(MALAYA_1QUE < 6) {
		mes "‐心配そうな顔で婦人が立っている‐";
		close;
	}
	if(BaseLevel < 100) {
		mes "[マリス]";
		mes "あ……あの……。";
		mes "いえ、なんでもありません。";
		mes "あなたは強そうに見えないですね。";
		mes "ごめんなさい。余裕がなくて……。";
		next;
		mes "‐何か手伝って欲しそうだが";
		mes "　今の自分では力不足のようだ。";
		mes "　^FF0000BaseLv100以上^000000になってから";
		mes "　あらためて、話かけてみよう‐";
		close;
	}
	if(checkquest(7388)) {
		mes "[マリス]";
		mes "きっと悪霊に惑わされて";
		mes "この森を彷徨っていると思います。";
		mes "お願いします。";
		mes "子供を見つけたら";
		mes "^4d4dff裏返しのシャツ^000000を";
		mes "渡してあげて下さい。";
		next;
		mes "[マリス]";
		mes "裏返しのシャツは";
		mes "モンスターを退治すれば";
		mes "手に入れることができます。";
		mes "昔はたくさん持っていたんですけど、";
		mes "全部奪われてしまったのです……。";
		next;
		mes "[マリス]";
		mes "娘たちはよく迷う場所のことを";
		mes "知っているみたいなんですけど、";
		mes "そこに行っても見つからないんです。";
		next;
		mes "[マリス]";
		mes "一か所にじっとして";
		mes "いられない子たちなので";
		mes "すれ違ってしまっているのかも";
		mes "しれません。";
		next;
		mes "[マリス]";
		mes "娘たちの話を聞いて";
		mes "もう一人の娘が";
		mes "迷っていそうな場所を";
		mes "探してきてもらえませんか？";
		close;
	}
	if(checkquest(7389)) {
		mes "[マリス]";
		mes "戻って来ましたね。";
		mes "子供はおかげ様で";
		mes "無事に家に帰ってきました。";
		next;
		if(checkweight(6497,1) == 0) {
			mes "[マリス]";
			mes "お礼をしようと思ったのですが……";
			mes "アイテムをいっぱいお持ちのようで。";
			mes "持ち物を整理してから、";
			mes "もう一度話しかけていただけますか？";
			close;
		}
		mes "[マリス]";
		mes "裏返しのシャツは、";
		mes "自身が戻るべき場所に導いてくれます。";
		mes "うちの子供たちに貴重な物を";
		mes "ありがとうございました。";
		mes "これは心ばかりのお礼です。";
		setquest 7390;
		delquest 7389;
		getitem 6497,1;
		if(checkre())
			getexp 50000,20000;
		else
			getexp 500000,200000;
		set $MalayaName$[1],strcharinfo(0);
		close;
	}
	if(checkquest(7390)) {
		if(!(checkquest(7390) & 0x2)) {
			mes "[マリス]";
			mes "裏返しのシャツさえあれば";
			mes "家に帰れると分かった子供たちが";
			mes "怖いもの知らずになってしまって、";
			mes "森で遅くまで遊んでいるのです……。";
			next;
			mes "[マリス]";
			mes "だけど、ここで遊ぶといったら";
			mes "森に入るくらいしかないですし、";
			mes "いくら言っても聞かないでしょう。";
			mes "もし、森でまた迷子になるようなら";
			mes "その時はまたあなたに";
			mes "お願いするかもしれません。";
			close;
		}
	}
	mes "[マリス]";
	mes "うちの娘が見当たらないんです。";
	mes "森へ遊びに行ったまま、";
	mes "ポートマラヤの自宅にも";
	mes "戻ってないみたいなんです。";
	next;
	mes "[マリス]";
	mes "ムンバキ・キコに捜索を頼んだのですが";
	mes "人手が不足しているせいで、";
	mes "なかなか捜索が進まなくて……";
	mes "　";
	mes "お願いします、どうか娘を";
	mes "探してきていただけないでしょうか。";
	next;
	switch(select("わかりました","今は忙しいです","あれ、娘ならそこに")) {
	case 1:
		mes "[マリス]";
		mes "おそらく娘は悪霊に惑わされて";
		mes "森を彷徨っているはずです。";
		next;
		mes "[マリス]";
		mes "もし呪いにかかっているとしたら";
		mes "そのまま連れて来ることは";
		mes "できないと思います。";
		next;
		mes "[マリス]";
		mes "なので、ちょっと面倒かもしれませんが、";
		mes "^4d4dff裏返しのシャツ^000000を";
		mes "手に入れて娘に渡して下さい。";
		mes "そのシャツを持っていると";
		mes "不思議な力が宿り戻るべき場所を";
		mes "導いてくれるのです。";
		next;
		mes "[マリス]";
		mes "裏返しのシャツは";
		mes "森に潜むモンスターを退治すれば";
		mes "手に入れることができます。";
		mes "昔はたくさん持っていたんですけど、";
		mes "全部奪われてしまったのです……。";
		next;
		mes "[マリス]";
		mes "どうか娘を探し出してください。";
		mes "お願いします。";
		next;
		mes "[マリス]";
		mes "娘たちはよく迷う場所のことを";
		mes "知っているみたいなんですけど、";
		mes "そこに行っても見つからないんです。";
		next;
		mes "[マリス]";
		mes "一か所にじっとして";
		mes "いられない子たちなので";
		mes "すれ違ってしまっているのかも";
		mes "しれません。";
		next;
		mes "[マリス]";
		mes "娘たちの話を聞いて";
		mes "もう一人の娘が";
		mes "迷っていそうな場所を";
		mes "探してきてもらえませんか？";
		if(checkquest(72092)) {
			delquest 72092;
			setquest 7388;
		} else {
			delquest 7390;
			setquest 7388;
		}
		close;
	case 2:
		mes "[マリス]";
		mes "そうですか……。";
		mes "他の方にお願いしてみます。";
		mes "ああ、かわいい娘が……。";
		close;
	case 3:
		mes "[マリス]";
		mes "実は三つ子の娘がいるんです。";
		mes "私でもたまに間違えちゃうくらいで。";
		mes "うふふ……。";
		next;
		mes "[マリス]";
		mes "ただ、なぜかわからないんですけど";
		mes "森に遊びに行くと必ず誰かが";
		mes "道に迷って帰って来れないんです。";
		mes "本当に困った事です……。";
		close;
	}
OnInit:
	waitingroom "マリスの子供探し",0;
	end;
}

ma_in01_jp.gat,38,158,7	script	女の子	576,{
	mes "[女の子]";
	mes "あのね、あのね。森は怖いけど";
	mes "おもしろい物がたっくさんあるの!!";
	mes "だからよく遊びに行くんだけど、";
	mes "なぜか道に迷っちゃうんです……。";
	next;
	mes "[女の子]";
	mes "でも、私だけ道に迷うわけでは";
	mes "ないから大丈夫～。";
	mes "必ず誰かが迷子になるのよ。";
	next;
	mes "[女の子]";
	mes "村の北西の方に行くと";
	mes "道がぐるっと一周できるの。";
	mes "ずっと歩いていると、";
	mes "どっちから来たのか";
	mes "わからなくなっちゃうの。";
	close;
}

ma_in01_jp.gat,39,158,7	script	女の子	576,{
	mes "[女の子]";
	mes "いっつも遊びにいってるのに";
	mes "なんで迷子になっちゃうんだろ～。";
	next;
	mes "[女の子]";
	mes "村の南の橋を渡ると";
	mes "分かれ道があるの。";
	mes "その近くで迷って";
	mes "助けてもらったこともあるよ。";
	next;
	mes "[女の子]";
	mes "もうひとつ橋を渡ったこともあるの。";
	mes "そっちには変な壁みたいなのが";
	mes "あったよ。";
	close;
}

ma_fild01.gat,251,93,3	script	道に迷った子供#mal01	576,{
	if(checkquest(7388)) {
		if(countitem(12700) < 1) {
			mes "[ちびっ子]";
			mes "もしかしてあなたも迷子？";
			mes "ほんとあいつらのイタズラは";
			mes "嫌になっちゃう！";
			next;
			mes "[ちびっ子]";
			mes "こんな時に裏返しのシャツがあれば";
			mes "すぐにポートマラヤまで帰れるのに～。";
			close;
		}
		mes "[ちびっ子]";
		mes "もー！　またあいつらだ！";
		mes "また私が道に迷うように";
		mes "イタズラされた！";
		next;
		menu "どうしたのか聞く",-;
		mes "[ちびっ子]";
		mes "家に帰りたいのに、何かに邪魔されて";
		mes "うまく戻る事が出来ないの……。";
		mes "早く戻らないと";
		mes "お母さんが心配しちゃう……。";
		mes "こんな時に裏返しのシャツさえあれば";
		mes "すぐポートマラヤに帰れるのに～。";
		next;
		menu "裏返しのシャツを渡す",-;
		mes "[ちびっ子]";
		mes "ほんと？";
		mes "わぁ！ありがとう～！";
		mes "これがあれば家に帰れる！";
		next;
		mes "[ちびっ子]";
		mes "ひょっとして";
		mes "お母さんに頼まれたの？";
		mes "心配していたのかな……。";
		mes "早く帰ってお母さんに謝らなきゃ！";
		mes "本当にありがとう！";
		delitem 12700,1;
		setquest 7389;
		delquest 7388;
		if(strnpcinfo(2) == "mal01") {
			if(rand(2) == 0)
				hideoffnpc "道に迷った子供#mal02";
			else
				hideoffnpc "道に迷った子供#mal03";
		} else if(strnpcinfo(2) == "mal02") {
			if(rand(2) == 0)
				hideoffnpc "道に迷った子供#mal01";
			else
				hideoffnpc "道に迷った子供#mal03";
		} else {
			if(rand(2) == 0)
				hideoffnpc "道に迷った子供#mal01";
			else
				hideoffnpc "道に迷った子供#mal02";
		}
		hideonnpc strnpcinfo(0);
		close;
	}
	if(checkquest(7389)) {
		mes "[ちびっ子]";
		mes "シャツ、ありがとうございました！";
		mes "もう少ししたら帰るー。";
		close;
	}
	mes "[ちびっ子]";
	mes "おかしいなぁ。また道に迷ったかな？";
	mes "ここは何処だろう……。";
	mes "確か三番目の木でグルグル回って、";
	mes "太陽が出てる方向にまっすぐ行くと";
	mes "家につくはずなのに……。";
	next;
	mes "[ちびっ子]";
	mes "どうしていつも～";
	mes "ここから抜け出せなくなるんだろ。";
	mes (Sex? "お兄": "お姉")+ "さんは知っていますか？";
	next;
	mes "[ちびっ子]";
	mes "なにか悪い人達がいて";
	mes "私の邪魔をしているのかな？";
	close;
OnInit:
	if(strnpcinfo(2) == "mal01") {
		hideonnpc "道に迷った子供#mal01";
		hideonnpc "道に迷った子供#mal02";
		hideonnpc "道に迷った子供#mal03";
		hideoffnpc "道に迷った子供#mal0" +rand(1,3);
	}
	end;
}
ma_fild01.gat,114,141,3	duplicate(道に迷った子供#mal01)	道に迷った子供#mal02	576
ma_fild01.gat,130,314,3	duplicate(道に迷った子供#mal01)	道に迷った子供#mal03	576

//============================================================
// 旅人の友達カプレクエストNPC
//------------------------------------------------------------
ma_fild02.gat,241,39,5	script	カプレ・ブディディ	572,{
	if(checkquest(7409)) {
		if(!(checkquest(7409) & 0x4)) {
			mes "[ブディディ]";
			mes "暴れん坊のブギスギスに";
			mes "お仕置きして！";
			mes "ブディディがまた友達のために";
			mes "歌えるように。ふわっふ～";
			close;
		}
		mes "[ブディディ]";
		mes "驚いた、旅人！";
		mes "ブギスギスの凄絶な泣き声が";
		mes "ここまで聞こえた！";
		mes "ブディディはまた友達の為に";
		mes "歌ってもいいのか!?";
		next;
		mes "[ブディディ]";
		mes "ブディディ何かお礼考える。";
		mes "そうだ！　このお守りをあげるよ。";
		mes "旅人が持っていたらいいと思う。";
		next;
		if(checkweight(6497,1) == 0) {
			mes "[ブディディ]";
			mes "旅人！";
			mes "アイテムをいっぱい持ち過ぎ！";
			mes "お礼が渡せない～";
			mes "整理したらまた来て～。";
			close;
		}
		mes "[ブディディ]";
		mes "優しいカプレ、旅人達の友達。";
		mes "また会うことができればいいと思う。";
		mes "これは友達のための祝福。";
		mes "ふわあああ～！　ふわっふ～！";
		setquest 7410;
		delquest 7409;
		getitem 6497,1;
		if(checkre())
			getexp 50000,20000;
		else
			getexp 500000,200000;
		set $MalayaName$[2],strcharinfo(0);
		close;
	}
	mes "[ブディディ]";
	mes "ふっふわふ～。";
	mes "ブディディは優しいカプレ～YO！";
	mes "男性にも優しいカプレ～YO!!";
	mes "女性にも優しいカプレ～YO!!!";
	mes "みんなに優しいカプレ～YO!!!!";
	next;
	mes "[ブディディ]";
	mes "そこの君も";
	mes "ブディディの歌聞きに来た？";
	mes "それともブディディの相談に";
	mes "のってくれるの？";
	next;
	switch(select("君は誰？","相談したいこと？","特に用は無い")) {
	case 1:
		mes "[ブディディ]";
		mes "ブディディは歌好きなカプレ。";
		mes "カプレは森に住む巨人達のこという。";
		mes "たまに森で遊ぶ子供たちを";
		mes "からかって悪さするカプレもいるけど、";
		mes "ブディディはここで歌うだけ。";
		next;
		mes "[ブディディ]";
		mes "カプレはみんな人間大好き！";
		mes "みんな^FF0000見た人間の話、する。";
		mes "その人間の噂、みんなに広まる。^000000";
		next;
		mes "[ブディディ]";
		mes "この前、魔物倒した人間の話、した。";
		mes "その話、街中に広まった。";
		mes "人間、街中で人気になった。";
		mes "人間、嬉しい。カプレ、嬉しい。";
		next;
		mes "[ブディディ]";
		mes "カプレは人間と友達なりたい。";
		mes "でもカプレ、恥ずかしがり屋多い。";
		mes "人間に見られるとすぐに隠れる。";
		next;
		mes "[ブディディ]";
		mes "ブディディは恥ずかしくない。";
		mes "友達のために歌、歌う。";
		next;
		mes "[ブディディ]";
		mes "牛、馬、羊、鶏、豚、";
		mes "みんな私の歌喜んでくれる。";
		mes "みんな友達。";
		next;
		mes "[ブディディ]";
		mes "でも、片目のブギスギスだけ違う。";
		mes "あいつ私の友達イジメる。";
		mes "本当に憎たらしい。";
		mes "でも、ブディディ弱い。";
		next;
		mes "[ブディディ]";
		mes "片目も怖いけど、";
		mes "あいつが持っている棍棒とても怖い。";
		mes "私、友達に歌を聞かせたいのに、";
		mes "あいつのせいでみんな森、来れない。";
		next;
		mes "[ブディディ]";
		mes "だからブディディここで歌う。";
		mes "旅人いっぱいここ通る。";
		mes "ブディディは旅人達の友達。";
		mes "あなたもブディディの友達だ。";
		close;
	case 2:
		if(BaseLevel < 100) {
			mes "[ブディディ]";
			mes "ブギスギスに興味あるのか？";
			mes "あれは森の暴れん坊だ！";
			mes "ブディディの友達をイジメる！";
			next;
			mes "[ブディディ]";
			mes "残念だけどブディディは";
			mes "歌う事以外は何もできない。";
			mes "棍棒持ったあいつを";
			mes "ブディディどうにもできない。";
			mes "ブディディ弱い。";
			next;
			mes "[ブディディ]";
			mes "旅人の君も同じ。やられる。";
			mes "悔しい。悲しい。だから歌う。";
			mes "ふっなふ～　ななっふ～";
			next;
			mes "‐ブギスギスの退治を";
			mes "　手伝ってあげたいが、";
			mes "　レベルが足りないようだ。";
			mes "　^FF0000BaseLv100以上^000000になってから";
			mes "　あらためて、話かけてみよう‐";
			close;
		}
		if(checkquest(7410)) {
			if(!(checkquest(7410) & 0x2)) {
				mes "[ブディディ]";
				mes "旅人、ブディディの友達！";
				mes "ブギスギスが";
				mes "遠くまで逃げたようだ。";
				mes "犬、牛、馬、羊、鶏の友達も";
				mes "きっと帰ってくる！";
				next;
				mes "[ブディディ]";
				mes "だけどブディディ不安。";
				mes "片目の怪物はきっと帰って来る。";
				mes "その時も助けてくれる？";
				next;
				mes "[ブディディ]";
				mes "旅人～ブディディの友達～";
				mes "ふっふわふ～";
				mes "本当に、ありがとう～";
				close;
			}
			mes "[ブディディ]";
			mes "親切な旅人。";
			mes "ブギスギスまた来た。";
			mes "どうしたらいい？　どしよう？";
			next;
			mes "[ブディディ]";
			mes "ブディディ歌うと、あいつは怒り出す。";
			mes "だけど、他のみんなは喜ぶ。";
			mes "なのでブディディ大変。困った。";
			next;
			if(select("ブギスギスを退治する","恐ろしい話ですね") == 2) {
				mes "[ブディディ]";
				mes "そうだよ。本当だよ。";
				mes "ブギスギスのせいで";
				mes "ブディディの友達が歌、聞けない。";
				mes "本当に何とかしたい。";
				close;
			}
			mes "[ブディディ]";
			mes "ブギスギスに";
			mes "お仕置きしてくれるのか？！";
			mes "あいつらは森の中いる。";
			mes "10匹も倒せば、きっとびっくりするよ。";
			mes "ありがとう旅人！　お願いよ！";
			delquest 7410;
			setquest 7409;
			close;
		}
		mes "[ブディディ]";
		mes "憎たらしいブギスギス！";
		mes "あれは森の暴れん坊！";
		mes "ブディディの友達イジメる！";
		next;
		mes "[ブディディ]";
		mes "残念だけどブディディは";
		mes "歌う事以外は何もできない。";
		mes "棍棒を持ったあいつを";
		mes "ブディディどうにもできない。";
		mes "ブディディ弱い。";
		next;
		mes "[ブディディ]";
		mes "ブギスギス！　憎たらしいやつ！";
		next;
		if(select("ブギスギスを退治する","恐ろしい話ですね") == 2) {
			mes "[ブディディ]";
			mes "そうだよ。本当だよ。";
			mes "ブギスギスのせいで";
			mes "ブディディの友達が歌、聞けない。";
			mes "本当に何とかしたい。";
			close;
		}
		mes "[ブディディ]";
		mes "ブギスギスに";
		mes "お仕置きしてくれるのか？！";
		mes "あいつらは森の中いる。";
		mes "10匹も倒せば、きっとびっくりするよ。";
		mes "ありがとう旅人！　お願いよ！";
		delquest 72094;
		setquest 7409;
		close;
	case 3:
		mes "[ブディディ]";
		mes "旅立つ冒険者よ～";
		mes "ブディディが歌う～";
		mes "気を付けてね～";
		mes "また来てね～";
		mes "さよなら～";
		next;
		mes "[ブディディ]";
		mes "ふっふわふ～";
		mes "優しく善良なカプレの祝福～";
		mes "カプレからのプレゼント～";
		mes "ふわっふ～";
		close;
	}
OnInit:
	waitingroom "旅人の友達カプレ",0;
	end;
}

//============================================================
// 新任看護師と病院クエストNPC
//- Registry -------------------------------------------------
// MALAYA_4QUE -> 0～29
//------------------------------------------------------------
malaya.gat,55,72,4	script	看護師	569,{
	if(MALAYA_1QUE < 6) {
		mes "[看護師]";
		mes "この町の人たちはよそ者を";
		mes "あまりにも警戒しすぎです。";
		emotion 7;
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師]";
		mes "何か理由はあると思いますが、";
		mes "もう少し話してくれてもいいのに……";
		close2;
		cutin "malaya_nurseA01",255;
		end;
	}
	if(BaseLevel < 100) {
		mes "[看護師]";
		mes "もしかして……";
		mes "この病院に入るつもりですか？";
		mes "いま、ここには入れない";
		mes "みたいなんです。";
		next;
		mes "‐クエストを進行するには";
		mes "　Baseレベルが満たないようです。";
		mes "　^FF0000Baseレベル100^000000以上になったら";
		mes "　再度話しかけてください‐";
		close;
	}
	switch(MALAYA_4QUE) {
	case 0:
		mes "[看護師]";
		mes "もしかして……";
		mes "この病院に入るつもりですか？";
		cutin "malaya_nurseA01",2;
		next;
		if(select("そうです","違います") == 2) {
			mes "[看護師]";
			mes "あ……そうですか。";
			emotion 28;
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師]";
		mes "よかった～";
		mes "朝からずっと、誰か通りかからないかと";
		mes "待っていたんですよ～";
		cutin "malaya_nurseA02",2;
		next;
		switch(select("病院のことを聞く","人を待っていた理由を聞く","無視する")) {
		case 1:
			mes "[看護師]";
			mes "ここは、この町で唯一の病院です。";
			mes "そして、もうすぐ私が勤めることになる";
			mes "職場でもあります。";
			cutin "malaya_nurseA03",2;
			next;
			mes "[看護師]";
			mes "少し前に設立された";
			mes "新しい病院だと";
			mes "聞いていたのですが……";
			mes "妙な雰囲気というか、";
			mes "営業しているように";
			mes "見えないんですよね。";
			emotion 4;
			next;
			menu "人を待っていた理由を聞く",-;
			mes "[看護師]";
			mes "この町に看護師が必要なので";
			mes "ぜひ来てほしいという連絡を受けて、";
			mes "有名病院からのスカウトを断って";
			mes "来たのですけど……";
			next;
			mes "[看護師]";
			mes "道に迷いながら";
			mes "やっと着いたと思ったら、";
			mes "扉が開かないんですよ。";
			emotion 28;
			break;
		case 2:
			mes "[看護師]";
			mes "この町に看護師が必要なので";
			mes "ぜひ来てほしいという連絡を受けて、";
			mes "有名病院からのスカウトを断って";
			mes "来たのですけど……";
			cutin "malaya_nurseA03",2;
			next;
			mes "[看護師]";
			mes "道に迷いながら";
			mes "やっと着いたと思ったら、";
			mes "扉が開かないんですよ。";
			emotion 28;
			next;
			menu "病院のことを聞く",-;
			mes "[看護師]";
			mes "ここは、この町で唯一の病院です。";
			mes "そして、もうすぐ私が勤めることになる";
			mes "職場でもあります。";
			next;
			mes "[看護師]";
			mes "少し前に設立された";
			mes "新しい病院だと";
			mes "聞いていたのですが……";
			mes "妙な雰囲気というか、";
			mes "営業しているように";
			mes "見えないんですよね。";
			emotion 4;
			break;
		case 3:
			mes "[看護師]";
			mes "お忙しいようですね。";
			mes "それなら、私のことは";
			mes "気にしないでいいです。";
			emotion 28;
			cutin "malaya_nurseA03",2;
			close2;
			cutin "malaya_nurseA03",255;
			end;
		}
		next;
		mes "[看護師]";
		mes "そういうわけで、";
		mes "私も病院に入りたいんですけど……";
		mes "手伝ってもらってもいいですか？";
		cutin "malaya_nurseA04",2;
		next;
		mes "[看護師]";
		mes "扉は開かないし、";
		mes "荷物は重いし！";
		mes "足は腫れて、もう歩けません。";
		cutin "malaya_nurseA03",2;
		next;
		mes "[看護師]";
		mes "こうなるとわかっていたら、";
		mes "歩きやすい靴を履いて来たのに……。";
		emotion 28;
		next;
		if(select("手伝う","手伝わない") == 2) {
			mes "[看護師]";
			mes "お忙しいようですね。";
			mes "それなら、私のことは";
			mes "気にしないでいいです。";
			emotion 28;
			cutin "malaya_nurseA03",2;
			close2;
			cutin "malaya_nurseA03",255;
			end;
		}
		mes "[看護師]";
		mes "こんな親切な方とお会いできるなんて、";
		mes "この世の中もまだまだ";
		mes "捨てたものではありませんね。";
		emotion 28;
		next;
		mes "[看護師ラズ]";
		mes "私はこの病院の看護師になる予定の";
		mes "ラズといいます。";
		mes "この状態では、働けるか";
		mes "失業者になるのかわかりませんが……";
		next;
		mes "[看護師ラズ]";
		mes "さっそく病院に入りたいのですが……";
		mes "その前に、";
		mes "足の皮がむけてしまって";
		mes "靴を履くこともできません。";
		mes "何か足を保護できるものを";
		mes "探してきてくれませんか？";
		emotion 26;
		cutin "malaya_nurseA04",2;
		next;
		mes "[看護師ラズ]";
		mes "そうですね、";
		mes "^0000FFくさった包帯^000000を2個";
		mes "持ってきてもらえると助かります。";
		next;
		mes "‐^0000FFくさった包帯^000000を2個持ってきて、";
		mes "　看護師ラズに渡そう‐";
		delquest 72074;
		setquest 11284;
		set MALAYA_4QUE,1;
		cutin "malaya_nurseA04",255;
		close;
	case 1:
		if(countitem(930) < 2) {
			mes "[看護師ラズ]";
			mes "さっそく病院に入りたいのですが……";
			mes "その前に、足の皮がむけてしまって";
			mes "靴を履くこともできないので、";
			mes "何か足を保護できるものを";
			mes "探してきてくれませんか？";
			emotion 26;
			cutin "malaya_nurseA03",2;
			next;
			mes "[看護師ラズ]";
			mes "そうですね、";
			mes "^0000FFくさった包帯^000000を2個";
			mes "持ってきてもらえると助かります。";
			next;
			mes "‐^0000FFくさった包帯^000000を2個持ってきて、";
			mes "　看護師ラズに渡そう‐";
			cutin "malaya_nurseA03",255;
			close;
		}
		mes "[看護師ラズ]";
		mes "あ……";
		mes "くさった包帯を持ってきて";
		mes "くれたんですね。";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "それでは、";
		mes "私の華麗な看護師デビューのために！";
		mes "えいっ！";
		next;
		mes "[看護師ラズ]";
		mes "ぐるぐる～";
		mes "ぐるっと。";
		next;
		mes "‐看護師ラズが足の処置を";
		mes "　終えたようだ。";
		mes "　もう一度話しかけてみよう‐";
		cutin "malaya_nurseA01",255;
		delitem 930,2;
		delquest 11284;
		setquest 72100;
		set MALAYA_4QUE,2;
		close;
	case 2:
		mes "[看護師ラズ]";
		mes "すぐに良くなるわけでは";
		mes "ありませんけど、";
		mes "痛みは治まってきました。";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "では！";
		mes "私一人では開けられませんでしたが、";
		mes "一緒に扉を押してみましょう！";
		next;
		mes "‐病院の扉を開けてみよう‐";
		cutin "malaya_nurseA01",255;
		delquest 72100;
		setquest 11285;
		set MALAYA_4QUE,3;
		close;
	case 3:
		mes "[看護師ラズ]";
		mes "私一人では開けられませんでしたが、";
		mes "一緒に扉を押してみましょう！";
		cutin "malaya_nurseA01",2;
		next;
		mes "‐病院の扉を開けてみよう‐";
		cutin "malaya_nurseA01",255;
		close;
	case 4:
		mes "[看護師ラズ]";
		mes "押しても引いても、";
		mes "横に動かそうとしても";
		mes "扉は開きませんね。";
		cutin "malaya_nurseA03",2;
		emotion 19,"";
		next;
		mes "[看護師ラズ]";
		mes "おかしいですね～";
		mes "病院が閉鎖されたのなら、";
		mes "私が呼ばれたのは";
		mes "なんだったんでしょう？";
		next;
		mes "[看護師ラズ]";
		mes "よし。";
		mes "もうこれ以上我慢できません！";
		emotion 6;
		next;
		mes "[看護師ラズ]";
		mes "私は本部に連絡してみます。";
		mes "その間に、町の人に";
		mes "この病院のことを";
		mes "聞いてもらえませんか？";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "ちょうど、近くに女性がいますね。";
		mes "ちょっと聞いてきてもらえますか？";
		next;
		mes "‐近くにいる町の女性に";
		mes "　病院の話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		delquest 11286;
		setquest 11287;
		set MALAYA_4QUE,5;
		close;
	case 5:
		mes "[看護師ラズ]";
		mes "私は本部に連絡してみます。";
		mes "その間に、町の人に";
		mes "この病院のことを";
		mes "聞いてもらえませんか？";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "すぐ近くに女性がいますね。";
		mes "ちょっと聞いてきてもらえますか？";
		next;
		mes "‐近くにいる町の女性に";
		mes "　病院の話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		close;
	case 6:
		mes "[看護師ラズ]";
		mes "何か聞けましたか？";
		emotion 1;
		cutin "malaya_nurseA02",2;
		next;
		menu "女性に聞いた話を伝える",-;
		mes "[看護師ラズ]";
		mes "おかしいですね。";
		mes "本部に連絡したら、";
		mes "たしかにこの病院だと";
		mes "言っていたのですけど……";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "わざわざ他の町から私を呼んでまで";
		mes "本部が嘘をつくとも思えませんし、";
		mes "たまたま、その女性が";
		mes "知らなかっただけかもしれませんね。";
		next;
		mes "[看護師ラズ]";
		mes "私はもう一度本部に連絡して";
		mes "詳しく聞いてみます。";
		mes "すみませんが、今度はお隣の";
		mes "庭付きの家にいる男性に";
		mes "話を聞いてみてくれませんか？";
		next;
		mes "‐ここから南にある家の庭にいる、";
		mes "　町の男性に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		delquest 11288;
		setquest 11289;
		set MALAYA_4QUE,7;
		close;
	case 7:
		mes "[看護師ラズ]";
		mes "私はもう一度本部に連絡して";
		mes "詳しく聞いてみます。";
		mes "すみませんが、今度はお隣の";
		mes "庭付きの家にいる男性に";
		mes "話を聞いてみてくれませんか？";
		cutin "malaya_nurseA01",2;
		next;
		mes "‐ここから南にある家の庭にいる、";
		mes "　町の男性に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		close;
	case 8:
		mes "[看護師ラズ]";
		mes "旅館ですか？";
		mes "はあ～";
		mes "そうと知っていれば、";
		mes "何時間も待たないでよかったのに！";
		emotion 32;
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "……";
		mes "それで、その……";
		next;
		mes "[看護師ラズ]";
		mes "申し訳ないんですけど、";
		mes "足が痛くてあまり遠くまで";
		mes "移動できないので、";
		mes "私の代わりに旅館まで";
		mes "行ってきてもらえませんか？";
		mes "お願いします。";
		emotion 19;
		cutin "malaya_nurseA03",2;
		next;
		mes "[看護師ラズ]";
		mes "私は荷物番をしながら、";
		mes "足の治療でもしておきます。";
		next;
		mes "‐看護師ラズの代わりに、";
		mes "　旅館の近くいるという";
		mes "　ドクターに会いに行こう‐";
		cutin "malaya_nurseA03",255;
		delquest 11290;
		setquest 11291;
		set MALAYA_4QUE,9;
		close;
	case 9:
		mes "[看護師ラズ]";
		mes "足が痛くてあまり遠くまで";
		mes "移動できないので、";
		mes "私の代わりに旅館まで";
		mes "行ってきてもらえませんか？";
		emotion 19;
		cutin "malaya_nurseA03",2;
		next;
		mes "[看護師ラズ]";
		mes "私は荷物番をしながら、";
		mes "足の治療でもしておきます。";
		next;
		mes "‐看護師ラズの代わりに、";
		mes "　旅館の近くいるという";
		mes "　ドクターに会いに行こう‐";
		cutin "malaya_nurseA03",255;
		close;
	case 10:
		mes "[看護師ラズ]";
		mes "旅館に行ってきたんですね。";
		mes "なにかわかりましたか？";
		cutin "malaya_nurseA02",2;
		next;
		menu "伝言を伝える",-;
		mes "[看護師ラズ]";
		mes "鍵ですか？";
		mes "これで病院に入れますね！";
		mes "では、さっそく鍵を使って";
		mes "扉を開けましょう！";
		next;
		mes "‐病院の鍵を使って、";
		mes "　扉を開けてみよう‐";
		cutin "malaya_nurseA02",255;
		delquest 11292;
		setquest 72105;
		set MALAYA_4QUE,11;
		close;
	case 11:
		mes "[看護師ラズ]";
		mes "鍵ですか？";
		mes "これで病院に入れますね！";
		mes "では、さっそく鍵を使って";
		mes "扉を開けましょう！";
		cutin "malaya_nurseA02",2;
		next;
		mes "‐病院の鍵を使って、";
		mes "　扉を開けてみよう‐";
		cutin "malaya_nurseA02",255;
		close;
	case 12:
		mes "[看護師ラズ]";
		mes "あれれ？";
		mes "鍵が閉まってないですね。";
		mes "でも、扉は開きませんし……";
		mes "どういうことでしょう？";
		emotion 1;
		emotion 1,"";
		cutin "malaya_nurseA04",2;
		next;
		mes "[看護師ラズ]";
		mes "はあ～";
		mes "ドクターが来てくれるまで";
		mes "待つしかないのかなあ……？";
		cutin "malaya_nurseA03",2;
		next;
		mes "[？？？]";
		mes "……";
		cutin "malaya_nurseA03",255;
		next;
		mes "[？？？]";
		mes "くくく……";
		emotion 1,"";
		emotion 1;
		next;
		mes "[？？？]";
		mes (Sex? "おじさん": "おばさん")+ "、";
		mes "病院には入れないよ。";
		next;
		mes "[看護師ラズ]";
		mes "だれ？";
		next;
		mes "[？？？]";
		mes "ふふふふ……";
		next;
		mes "[？？？]";
		mes "名前を言うわけにはいかないのだ！";
		mes "病院に来たことが";
		mes "お母さんにばれると怒られるからな。";
		next;
		switch(select("病院に入れないことについて","怒られる？","姿を見せろ","そっとしておく")) {
		case 1:
			mes "[？？？]";
			mes "隣の家に住んでいるお婆さんが";
			mes "病院の周りで、何か言いながら";
			mes "棒のような物を";
			mes "地面に突き刺していたのだ。";
			mes "きっとケッカイってやつだな。";
			next;
			mes "[？？？]";
			mes "ふふふふ……";
			mes "しゃべりすぎてしまったようだな。";
			mes "病院にいることがバレないように";
			mes "ボクは身を隠すのだ。";
			break;
		case 2:
			mes "[？？？]";
			mes "前にお母さんが言ってたのだ。";
			mes "隣のお姉さんが";
			mes "この病院に入院していたらしい。";
			mes "退院はできなかったけど……";
			next;
			mes "[？？？]";
			mes "他にも、この病院に入院した人たちに";
			mes "悪いことが沢山あったらしいよ。";
			next;
			mes "[？？？]";
			mes "だから、お母さんは";
			mes "ボクがここに来るのを禁止してるのだ。";
			break;
		case 3:
			mes "[？？？]";
			mes "それはできないのだ。";
			mes "前もバレてお尻を叩かれたから！";
			mes "知ってるか？";
			mes "お尻を叩かれるととても痛いのだぞ！";
			break;
		case 4:
			mes "[？？？]";
			mes "ふふふふ……";
			close;
		}
		next;
		mes "‐声は病院の入口近くにある";
		mes "　草むらの方から聞こえる。";
		mes "　草むらを調べてみよう‐";
		misceffect 18,"草むら";
		delquest 11293;
		setquest 11294;
		set MALAYA_4QUE,13;
		close;
	case 13:
		mes "‐声は病院の入口近くにある";
		mes "　草むらの方から聞こえる。";
		mes "　近くを調べてみよう‐";
		misceffect 18,"草むら";
		close;
	case 14:
		mes "[看護師ラズ]";
		mes "棒と病院に入れないのと、";
		mes "何か関係があるのでしょうか？";
		mes "ひとまず、病院の周辺を調べて";
		mes "おかしなところがないか";
		mes "確認した方がよさそうですね。";
		cutin "malaya_nurseA01",2;
		close2;
		cutin "malaya_nurseA01",255;
		end;
	case 15:
		mes "[看護師ラズ]";
		mes "お婆さんが刺した棒に";
		mes "それが貼ってあったんですか？";
		mes "う～ん……";
		mes "いったいどういうものなのか、";
		mes "お婆さんの所に行って";
		mes "聞いてくれませんか？";
		cutin "malaya_nurseA04",2;
		next;
		mes "[看護師ラズ]";
		mes "私はここで病院の様子を見ています。";
		mes "その……";
		mes "まだ、足が痛いので、";
		mes "一緒に行けそうにないんです。";
		next;
		if(select("行く","行かない") == 2) {
			mes "[看護師ラズ]";
			mes "え……行ってくれないんですか？";
			mes "ここにいても何にも解決しませんよ。";
			close2;
			cutin "malaya_nurseA04",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "では、お願いします。";
		mes "この病院に来る途中で、";
		mes "町の西にある民家で";
		mes "お婆さんを見た気がします。";
		next;
		mes "[看護師ラズ]";
		mes "それから、草むらにいるキミ！";
		mes "早く家に帰らないと";
		mes "お母さんに言いつけちゃうぞ！";
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA04",255;
		delquest 11296;
		setquest 11297;
		set MALAYA_4QUE,16;
		close;
	case 16:
	case 17:
		mes "[看護師ラズ]";
		mes "では、お願いします。";
		mes "この病院に来る途中で、";
		mes "町の西にある民家で";
		mes "お婆さんを見た気がします。";
		cutin "malaya_nurseA04",2;
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA04",255;
		close;
	case 18:
		mes "[看護師ラズ]";
		mes "どうでした？";
		mes "お婆さんには会えましたか？";
		cutin "malaya_nurseA02",2;
		next;
		mes "[看護師ラズ]";
		mes "そうそう、お婆さんのところに";
		mes "行ってもらっている間に、";
		mes "もしかしたらと思って";
		mes "扉を押したら、開いたんですよ。";
		next;
		mes "[看護師ラズ]";
		mes "足の痛みも治まってきたので";
		mes "入ってみましたが、";
		mes "階段が封鎖されていて、";
		mes "2階には行けませんでした。";
		cutin "malaya_nurseA03",2;
		next;
		mes "[看護師ラズ]";
		mes "とりあえず中に入りましょうか。";
		mes "2階に行けなければ、";
		mes "意味はないのですけど……。";
		emotion 28;
		delquest 11299;
		setquest 11300;
		set MALAYA_4QUE,19;
		next;
		if(select("病院に入る","入らない") == 2) {
			mes "[看護師ラズ]";
			mes "病院に入りましょうよ！";
			close2;
			cutin "malaya_nurseA03",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "さあ、行きましょう。";
		close2;
		cutin "malaya_nurseA03",255;
		warp "ma_dun01.gat",33,110;
		end;
	case 19:
		mes "[看護師ラズ]";
		mes "とりあえず中に入りましょうか。";
		mes "2階に行けなければ、";
		mes "意味はないのですけど……。";
		emotion 28;
		cutin "malaya_nurseA01",2;
		next;
		if(select("病院に入る","入らない") == 2) {
			mes "[看護師ラズ]";
			mes "病院に入りましょうよ！";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "さあ、行きましょう。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "ma_dun01.gat",33,110;
		end;
	case 20:
		mes "[看護師ラズ]";
		mes "封鎖されている2階に";
		mes "行きたいのですけれど、";
		mes "階段を見てきてもらえますか？";
		cutin "malaya_nurseA01",2;
		next;
		if(select("病院に入る","入らない") == 2) {
			mes "[看護師ラズ]";
			mes "他に用事があるんですか？";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "さあ、行きましょう。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "ma_dun01.gat",33,110;
		end;
	case 21:
		mes "[看護師ラズ]";
		mes "お守りですか？";
		mes "他にも何かないか、";
		mes "もう少し階段のあたりを";
		mes "探してみてくれませんか。";
		cutin "malaya_nurseA01",2;
		next;
		if(select("病院に入る","入らない") == 2) {
			mes "[看護師ラズ]";
			mes "他に用事があるんですか？";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "お願いしますね。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "ma_dun01.gat",33,110;
		end;
	case 22:
		mes "[看護師ラズ]";
		mes "お守りと看護師？";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "お守りは、私も見つけましたけど";
		mes "気味が悪かったので、";
		mes "近づきませんでした。";
		next;
		mes "[看護師ラズ]";
		mes "あ！";
		mes "病院の周りにお守りを置いていた";
		mes "お婆さんなら、";
		mes "何か知っているかも！";
		mes "聞きに行ってもらえますか？";
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		delquest 11303;
		setquest 11304;
		set MALAYA_4QUE,23;
		close;
	case 23:
		mes "[看護師ラズ]";
		mes "病院の周りにお守りを置いていた";
		mes "お婆さんなら、";
		mes "何か知っているかも！";
		mes "聞きに行ってもらえますか？";
		cutin "malaya_nurseA01",2;
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		close;
	case 24:
		mes "[看護師ラズ]";
		mes "シャーマンですか……";
		mes "そのシャーマンにも話を聞いた方が";
		mes "良さそうですね。";
		cutin "malaya_nurseA01",2;
		close2;
		cutin "malaya_nurseA01",255;
		end;
	case 25:
		mes "[看護師ラズ]";
		mes "あれ！";
		mes "すごい気配を感じますけど、";
		mes "何があったんですか？";
		cutin "malaya_nurseA01",2;
		next;
		menu "シャーマンの札を貰った",-;
		mes "[看護師ラズ]";
		mes "シャーマンですか……";
		mes "そうだ！";
		mes "そのシャーマンの札を";
		mes "階段近くにあったお守りに";
		mes "貼ってみましょうよ。";
		emotion 5;
		next;
		mes "[看護師ラズ]";
		mes "もしかしたら、不吉な気配を";
		mes "防いでくれるかもしれませんよ！";
		delquest 11306;
		setquest 11307;
		set MALAYA_4QUE,26;
		close2;
		cutin "malaya_nurseA01",255;
		end;
	case 26:
		mes "[看護師ラズ]";
		mes "そのシャーマンの札を";
		mes "階段近くにあったお守りに";
		mes "貼ってみましょうよ。";
		emotion 5;
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "もしかしたら、不吉な気配を";
		mes "防いでくれるかもしれませんよ！";
		close2;
		cutin "malaya_nurseA01",255;
		end;
	case 27:
		mes "[看護師マエン]";
		mes "なんとか、逃げ切れたわね。";
		mes "……かわりに、彼女を2階に";
		mes "行かせてしまったわ。";
		cutin "malaya_nurseB",2;
		next;
		mes "‐看護師は深々と";
		mes "　ため息を吐いた‐";
		next;
		mes "[看護師マエン]";
		mes "あなたが後ろで";
		mes "うろうろしている時から";
		mes "あやしいと思っていたけど……";
		next;
		mes "[看護師マエン]";
		mes "まさか、こんなことを";
		mes "しでかすなんてね。";
		emotion 9;
		next;
		mes "[看護師マエン]";
		mes "ビョンウンゴを";
		mes "退治するチャンスだったのに、";
		mes "邪魔をしてくれたわね。";
		next;
		switch(select("ビョンウンゴ？","誰？")) {
		case 1:
			mes "[看護師マエン]";
			mes "ビョンウンゴは、";
			mes "この病院に棲みついている";
			mes "とても強力なモンスターよ。";
			next;
			mes "[看護師マエン]";
			mes "いえ……";
			mes "モンスターというよりも";
			mes "呪い、病の化身……";
			mes "あるいは、木に棲みつく";
			mes "妖怪だったという伝説もあるわ。";
			next;
			mes "[看護師マエン]";
			mes "いずれにしても、";
			mes "彼女がこの病院の患者を";
			mes "苦しめているのは確かでしょうね。";
			next;
			menu "誰？",-;
			mes "[看護師マエン]";
			mes "私のこと？";
			mes "新しくこの病院に赴任してきた";
			mes "看護師よ。";
			mes "もっとも、患者の看護よりも";
			mes "「こういう」のが専門なんだけど。";
			next;
			mes "[看護師マエン]";
			mes "超常現象……神秘的な力によって";
			mes "引き起こされた異常の";
			mes "治療とでもいえば";
			mes "わかってもらえるかしら？";
			next;
			mes "[看護師マエン]";
			mes "どうやら、ビョンウンゴは";
			mes "派遣されてきた看護師……";
			mes "つまり、私に成りすまして";
			mes "あなたを利用したようね。";
			mes "思った以上に賢いやつ……。";
			break;
		case 2:
			mes "[看護師マエン]";
			mes "私のこと？";
			mes "新しくこの病院に赴任してきた";
			mes "看護師よ。";
			mes "もっとも、患者の看護よりも";
			mes "「こういう」のが専門なんだけど。";
			cutin "malaya_nurseB",2;
			next;
			mes "[看護師マエン]";
			mes "超常現象……神秘的な力によって";
			mes "引き起こされた異常の";
			mes "治療とでもいえば";
			mes "わかってもらえるかしら？";
			next;
			mes "[看護師マエン]";
			mes "どうやら、ビョンウンゴは";
			mes "派遣されてきた看護師……";
			mes "つまり、私に成りすまして";
			mes "あなたを利用したようね。";
			mes "思った以上に賢いやつ……。";
			next;
			menu "ビョンウンゴ？",-;
			mes "[看護師マエン]";
			mes "ビョンウンゴは、";
			mes "この病院に棲みついている";
			mes "とても強力なモンスターよ。";
			next;
			mes "[看護師マエン]";
			mes "いえ……";
			mes "モンスターというよりも";
			mes "呪い、病の化身……";
			mes "あるいは、木に棲みつく";
			mes "妖怪だったという伝説もあるわ。";
			next;
			mes "[看護師マエン]";
			mes "いずれにしても、";
			mes "彼女がこの病院の患者を";
			mes "苦しめているのは確かでしょうね。";
			break;
		}
		next;
		menu "病院で起こっていることについて聞く",-;
		mes "[看護師マエン]";
		mes "私も、何が起こったか";
		mes "全部を知ってるわけじゃないけど……";
		next;
		mes "[看護師マエン]";
		mes "この病院は、ビョンウンゴの";
		mes "宿った木で建てられたみたいなの。";
		mes "彼女は弱っている入院患者に";
		mes "悪夢を見せて、力を奪っていたようね。";
		next;
		mes "[看護師マエン]";
		mes "私は、入院患者が2階に";
		mes "集められていることを突き止め、";
		mes "ビョンウンゴが1階に降りた隙に";
		mes "階段に結界を張って、これ以上";
		mes "彼女が力を増すのを防いでいたの。";
		next;
		mes "[看護師マエン]";
		mes "狙った通り、ビョンウンゴは";
		mes "2階に戻れず弱っていたわ。";
		mes "そのまま病院を浄化する";
		mes "つもりだったけど……";
		mes "彼女が戻ってしまった以上、";
		mes "簡単にはいかないでしょうね。";
		next;
		mes "[看護師マエン]";
		mes "あなたにも";
		mes "彼女を案内してしまった";
		mes "責任を取ってもらうわよ。";
		mes "もちろん、協力してくれるよね？";
		next;
		mes "[看護師マエン]";
		mes "ビョンウンゴは悪夢の力で";
		mes "隠れているわ。";
		mes "ただ2階に行くだけでは、";
		mes "倒すどころか戦うことすら";
		mes "できないはずよ。";
		next;
		mes "[看護師マエン]";
		mes "私がビョンウンゴをおびき寄せるから";
		mes "階段のところで話しかけてちょうだい。";
		mes "彼女の始末は任せるわよ。";
		next;
		mes "[看護師マエン]";
		mes "これを渡しておくわ。";
		mes "ビョンウンゴ退治の";
		mes "役に立つかもしれないから。";
		if(checkitemblank() < 3) {
			mes "……と思ったけど、持てないみたいね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てね。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		if((MaxWeight - Weight) < 1000) {
			mes "……と思ったけど、持てないみたいね。";
			mes "アイテムの重量を減らしてから";
			mes "また来てね。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		getitem 6499,3;
		getitem 6497,5;
		getitem 617,1;
		if(checkre()) {
			for(set '@i,0;'@i<6;set '@i,'@i+1)
				getexp 500000,0;
			for(set '@i,0;'@i<2;set '@i,'@i+1)
				getexp 0,500000;
		}
		else {
			for(set '@i,0;'@i<6;set '@i,'@i+1)
				getexp 5000000,0;
			for(set '@i,0;'@i<2;set '@i,'@i+1)
				getexp 0,5000000;
		}
		delquest 11308;
		setquest 11309;
		setquest 201515;
		set MALAYA_4QUE,28;
		next;
		mes "[看護師マエン]";
		mes "ビョンウンゴは手強いわよ。";
		mes "しっかり準備を整えてから";
		mes "来てちょうだい。";
		close2;
		cutin "malaya_nurseB",255;
		end;
	case 28:
	case 29:
		if(MALAYA_4QUE == 28) {
			mes "[看護師マエン]";
			mes "病院を浄化する";
			mes "つもりだったけど……";
			mes "彼女が戻ってしまった以上、";
			mes "簡単にはいかないでしょうね。";
			cutin "malaya_nurseB",2;
			next;
			mes "[看護師マエン]";
			mes "あなたにも";
			mes "彼女を案内してしまった";
			mes "責任を取ってもらうわよ。";
			mes "もちろん、協力してくれるよね？";
		}
		else {
			mes "[看護師マエン]";
			mes "ビョンウンゴの力は予想以上ね。";
			mes "いまだに彼女の気が感じられるわ。";
			cutin "malaya_nurseB",2;
		}
		next;
		mes "[看護師マエン]";
		mes "ビョンウンゴは悪夢の力で";
		mes "隠れているわ。";
		mes "ただ2階に行くだけでは、";
		mes "倒すどころか戦うことすら";
		mes "できないはずよ。";
		next;
		mes "[看護師マエン]";
		mes "私がビョンウンゴをおびき寄せるから";
		mes "階段のところで話しかけてちょうだい。";
		mes "彼女の始末は任せるわよ。";
		next;
		if(select("病院に入る","やめる") == 2) {
			mes "[看護師マエン]";
			mes "そう……";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		mes "[看護師マエン]";
		mes "中に入るのね。";
		close2;
		cutin "malaya_nurseB",255;
		warp "ma_dun01.gat",33,110;
		end;
	}
OnInit:
	waitingroom "新任看護師と病院",0;
	end;
}

ma_dun01.gat,35,108,4	script	看護師	569,{
	switch(MALAYA_4QUE) {
	case 19:
		mes "‐病院内を、たくさんの";
		mes "　モンスターが徘徊している。";
		mes "　看護師ラズは、この中を";
		mes "　見てきたというのだろうか？‐";
		next;
		mes "[看護師ラズ]";
		mes "さっき見てきたところ、";
		mes "階段が封鎖されていました。";
		mes "2階に行きたいのですけれど、";
		mes "階段を見てきてもらえますか？";
		delquest 11300;
		setquest 11301;
		set MALAYA_4QUE,20;
		cutin "malaya_nurseA01",2;
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師ラズ]";
			mes "お願いします。";
			mes "2階への階段は、この建物の";
			mes "南東にあります。";
			next;
			mes "‐南東にある2階への階段付近を";
			mes "　調べよう‐";
			cutin "malaya_nurseA01",255;
			close;
		}
		mes "[看護師ラズ]";
		mes "外に出るんですか？";
		mes "わかりました。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 20:
		mes "[看護師ラズ]";
		mes "2階に行きたいのですけれど、";
		mes "階段を見てきてもらえますか？";
		cutin "malaya_nurseA01",2;
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師ラズ]";
			mes "お願いします。";
			next;
			mes "‐南東にある2階への階段付近を";
			mes "　調べよう‐";
			cutin "malaya_nurseA01",255;
			close;
		}
		mes "[看護師ラズ]";
		mes "外に出るんですか？";
		mes "わかりました。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 21:
		mes "[看護師ラズ]";
		mes "お守りですか？";
		mes "他にも何かないか、";
		mes "もう少し階段のあたりを";
		mes "探してみてくれませんか。";
		cutin "malaya_nurseA01",2;
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師ラズ]";
			mes "お願いします。";
			next;
			mes "‐南東にある2階への階段付近を";
			mes "　もう少し調べよう‐";
			cutin "malaya_nurseA01",255;
			close;
		}
		mes "[看護師ラズ]";
		mes "外に出るんですか？";
		mes "わかりました。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 22:
		mes "[看護師ラズ]";
		mes "お守りと看護師？";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "お守りは、私も見つけましたけど";
		mes "気味が悪かったので、";
		mes "近づきませんでした。";
		next;
		mes "[看護師ラズ]";
		mes "あ！";
		mes "病院の周りにお守りを置いていた";
		mes "お婆さんなら、";
		mes "何か知っているかも！";
		mes "聞きに行ってもらえますか？";
		delquest 11303;
		setquest 11304;
		set MALAYA_4QUE,23;
		next;
		if(select("お婆さんに話を聞きに行く","病院から出ない") == 2) {
			mes "[看護師ラズ]";
			mes "まだ病院に何かご用ですか？";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "お婆さんから話を聞いて";
		mes "来てくださいね。";
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		close2;
		warp "malaya.gat",58,76;
		end;
	case 23:
		mes "[看護師ラズ]";
		mes "病院の周りにお守りを置いていた";
		mes "お婆さんなら、";
		mes "何か知っているかも！";
		mes "聞きに行ってもらえますか？";
		cutin "malaya_nurseA01",2;
		next;
		if(select("お婆さんに話を聞きに行く","病院から出ない") == 2) {
			mes "[看護師ラズ]";
			mes "まだ病院に何かご用ですか？";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "お婆さんから話を聞いて";
		mes "来てくださいね。";
		next;
		mes "‐ポートマラヤの西の民家にいる";
		mes "　老婆に話を聞いてみよう‐";
		cutin "malaya_nurseA01",255;
		close2;
		warp "malaya.gat",58,76;
		end;
	case 24:
		mes "[看護師ラズ]";
		mes "シャーマンですか……";
		mes "そのシャーマンにも話を聞いた方が";
		mes "良さそうですね。";
		cutin "malaya_nurseA01",2;
		next;
		if(select("シャーマンに話を聞きに行く","病院から出ない") == 2) {
			mes "[看護師ラズ]";
			mes "まだ病院に何かご用ですか？";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "シャーマンから話を聞いて";
		mes "来てくださいね。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 25:
		mes "[看護師ラズ]";
		mes "あれ！";
		mes "すごい気配を感じますけど、";
		mes "何があったんですか？";
		cutin "malaya_nurseA01",2;
		next;
		menu "シャーマンの札を貰った",-;
		mes "[看護師ラズ]";
		mes "シャーマンの札ですか……";
		mes "そうだ！";
		mes "そのシャーマンの札を";
		mes "階段近くにあったお守りに";
		mes "貼ってみましょうよ。";
		next;
		mes "[看護師ラズ]";
		mes "もしかしたら、不吉な気配を";
		mes "防いでくれるかもしれませんよ！";
		delquest 11306;
		setquest 11307;
		set MALAYA_4QUE,26;
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師ラズ]";
			mes "お願いします。";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "外に出るんですか？";
		mes "わかりました。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 26:
		mes "[看護師ラズ]";
		mes "そのシャーマンの札を";
		mes "階段近くにあったお守りに";
		mes "貼ってみましょうよ。";
		cutin "malaya_nurseA01",2;
		next;
		mes "[看護師ラズ]";
		mes "もしかしたら、不吉な気配を";
		mes "防いでくれるかもしれませんよ！";
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師ラズ]";
			mes "お願いします。";
			close2;
			cutin "malaya_nurseA01",255;
			end;
		}
		mes "[看護師ラズ]";
		mes "外に出るんですか？";
		mes "わかりました。";
		close2;
		cutin "malaya_nurseA01",255;
		warp "malaya.gat",58,76;
		end;
	case 27:
		mes "[看護師マエン]";
		mes "いったん病院の外に出ましょう。";
		mes "さあ、早く！";
		cutin "malaya_nurseB",2;
		close2;
		cutin "malaya_nurseB",255;
		warp "malaya.gat",58,76;
		end;
	case 28:
	case 29:
		if(MALAYA_4QUE == 28) {
			mes "[看護師マエン]";
			mes "病院を浄化する";
			mes "つもりだったけど……";
			mes "彼女が戻ってしまった以上、";
			mes "簡単にはいかないでしょうね。";
			cutin "malaya_nurseB",2;
			next;
			mes "[看護師マエン]";
			mes "あなたにも";
			mes "彼女を案内してしまった";
			mes "責任を取ってもらうわよ。";
			mes "もちろん、協力してくれるよね？";
		}
		else {
			mes "[看護師マエン]";
			mes "まだビョンウンゴの気配が";
			mes "完全に消えてはいないようね。";
			cutin "malaya_nurseB",2;
		}
		next;
		mes "[看護師マエン]";
		mes "ビョンウンゴは悪夢の力で";
		mes "隠れているわ。";
		mes "ただ2階に行くだけでは、";
		mes "倒すどころか戦うことすら";
		mes "できないはずよ。";
		next;
		mes "[看護師マエン]";
		mes "私がビョンウンゴをおびき寄せるから";
		mes "階段のところで話しかけてちょうだい。";
		mes "彼女の始末は任せるわよ。";
		next;
		if(select("いったん外に出る","病院の奥に向かう") == 2) {
			mes "[看護師マエン]";
			mes "準備ができたら、";
			mes "階段のところにいらっしゃい。";
			close2;
			cutin "malaya_nurseB",255;
			end;
		}
		mes "[看護師マエン]";
		mes "外に出るのね？";
		mes "わかったわ。";
		close2;
		cutin "malaya_nurseB",255;
		warp "malaya.gat",58,76;
		end;
	}
}

ma_dun01.gat,152,23,4	script	怪しい木の棒	858,{
	switch(MALAYA_4QUE) {
	case 19:
		mes "‐なぜかこんなところに";
		mes "　木の棒がある‐";
		close;
	case 20:
		mes "‐病院の外にあったお守りと";
		mes "　似た模様の入った木の棒だ‐";
		next;
		if(select("棒を引き抜く","そのままにしておく") == 2) {
			mes "‐あなたは木の棒には手を触れず";
			mes "　その場を後にした‐";
			close;
		}
		mes "‐……抜けない。";
		mes "　力を込めてみても、";
		mes "　まったく動かない。";
		mes "　あなたは、棒から手を放した‐";
		next;
		mes "‐これも何かのお守りだろうか？";
		mes "　もう少し周囲を調べてみよう‐";
		delquest 11301;
		setquest 11302;
		set MALAYA_4QUE,21;
		close;
	case 21:
		mes "‐病院の外にあったお守りと";
		mes "　似た模様の入った木の棒だ。";
		mes "　これも何かのお守りだろうか？";
		mes "　もう少し周囲を調べてみよう‐";
		close;
	case 26:
		mes "‐病院の外にあったお守りと";
		mes "　似た模様の入った木の棒だ。";
		mes "　看護師ラズは、悪い気配がすると";
		mes "　言っていた‐";
		next;
		if(select("シャーマンの札を貼る","やっぱり貼らない") == 2) {
			mes "‐あなたは、その場を後にした‐";
			close;
		}
		mes "‐木の棒にシャーマンの札を貼った。";
		mes "　張りつめていた気配が";
		mes "　弱まったような気がする‐";
		next;
		mes "[看護師ラズ]";
		mes "……き……た";
		cutin "malaya_nurseA05",2;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "？";
		emotion 1,"";
		cutin "malaya_nurseA05",255;
		next;
		mes "[看護師ラズ]";
		mes "できた、できた";
		cutin "malaya_nurseA05",2;
		next;
		mes "[看護師ラズ]";
		mes "できた、できた";
		mes "できたできたできたできたできたできた";
		mes "できたできたできたできたできたできた";
		mes "できたできたできたできたできたできた";
		mes "できたできたできたできたできたできた";
		mes "できたできたできたできたできたできた";
		next;
		mes "[看護師ラズ]";
		mes "じゃまなおまもりがきえた";
		next;
		mes "[看護師ラズ]";
		mes "くくくく";
		next;
		mes "‐看護師ラズの瞳が";
		mes "　妖しい輝きを放った‐";
		next;
		mes "‐頭の中をかき回されるような";
		mes "　苦痛に襲われ、床に膝をついた‐";
		next;
		mes "[看護師ラズ]";
		mes "うまいうまいうまいうまい";
		mes "もっともっともっともっと";
		mes "よこせよこせよこせよこせ";
		next;
		mes "[看護師ラズ]";
		mes "あくむをあくむをあくむをあくむを";
		next;
		mes "‐力が吸い取られる……";
		mes "　だんだん視界がぼやけ始めた‐";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "何が……";
		mes "……おまえは……？";
		mes "ああ…………";
		mes "……だ……め";
		next;
		mes "[？？？]";
		mes "そこまでよ！";
		cutin "malaya_nurseA05",255;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "（か、看護師が……";
		mes "　もうひとり……？）";
		next;
		mes "[看護師]";
		mes "その子から離れなさい!!";
		cutin "malaya_nurseB",2;
		next;
		mes "‐看護師ラズに向かって";
		mes "　小さなお守りが投げつけられる。";
		mes "　看護師ラズの注意が逸れ、";
		mes "　あなたは苦痛から解放される‐";
		next;
		mes "[看護師]";
		mes "ここは私に任せて";
		mes "あなたは病院の外に逃げなさい。";
		mes "さあ、早く！";
		next;
		mes "‐先ほどまでの苦痛に";
		mes "　意識が途切れそうになりながら";
		mes "　あなたは歩き出した‐";
		cutin "malaya_nurseB",255;
		next;
		mes "‐看護師ラズの声が、";
		mes "　どこまでも追いかけてくるように";
		mes "　頭の中で反響していた‐";
		delquest 11307;
		setquest 11308;
		set MALAYA_4QUE,27;
		close2;
		warp "malaya.gat",58,76;
		end;
	default:
		if(MALAYA_4QUE < 27) {
			mes "‐病院の外にあったお守りと";
			mes "　似た模様の入った木の棒だ‐";
			close;
		}
		mes "‐お守りからは";
		mes "　何の気配も感じられない‐";
		close;
	}
}

malaya.gat,48,76,4	script	病院扉	844,{
	switch(MALAYA_4QUE) {
	case 3:
		mes "‐力いっぱい扉を押したが、";
		mes "　まるで壁を押しているかのように";
		mes "　まったく動かない‐";
		next;
		mes "‐引いたり、横に動かそうと";
		mes "　力を入れたりしてみても";
		mes "　まったく動かない。";
		mes "　ひとまず、看護師ラズと話そう‐";
		delquest 11285;
		setquest 11286;
		set MALAYA_4QUE,4;
		close;
	case 4:
		mes "‐押しても引いても";
		mes "　扉はまったく動かない。";
		mes "　ひとまず、看護師ラズと話そう‐";
		close;
	case 11:
		mes "‐扉の鍵穴に鍵を入れた。";
		mes "　鍵を回すと、小さな音がして";
		mes "　鍵がかかった手ごたえがあった。";
		mes "　どうやら、元から鍵はかかって";
		mes "　いなかったようだ‐";
		next;
		mes "‐鍵がかかっていないのに";
		mes "　扉が開かないのは";
		mes "　どういうことなのだろう？";
		mes "　看護師ラズに話しかけよう‐";
		delquest 72105;
		setquest 11293;
		set MALAYA_4QUE,12;
		close;
	case 12:
		mes "‐どうやら、元から鍵はかかって";
		mes "　いなかったようだ。";
		mes "　鍵がかかっていないのに";
		mes "　扉が開かないのは";
		mes "　どういうことなのだろう？";
		mes "　看護師ラズに話しかけよう‐";
		close;
	default:
		if(MALAYA_4QUE < 19) {
			mes "‐病院の入り口だ。";
			mes "　今は扉が閉まっているようだ‐";
			close;
		}
		mes "‐扉に鍵はかかっていないようだ‐";
		next;
		if(select("病院に入る","入らない") == 2) {
			mes "‐あなたは病院の扉から離れた‐";
			close;
		}
		mes "‐病院の扉を開け、中に入った‐";
		close2;
		warp "ma_dun01.gat",33,110;
		end;
	}
}

malaya.gat,64,78,4	script	町の女	583,{
	if(MALAYA_1QUE < 6) {
		mes "[町の女]";
		mes "……";
		next;
		mes "‐こちらを探るような目つきで";
		mes "　見ている。";
		mes "　警戒されているようだ‐";
		close;
	}
	if(MALAYA_4QUE == 6) {
		mes "[町の女]";
		mes "新しく来る看護師……ですか？";
		mes "さあ……";
		mes "病院が閉鎖されているのに";
		mes "看護師が来るなんていうことが";
		mes "あるのかしら？";
		next;
		mes "‐町の女性から話を聞いた。";
		mes "　病院に新しい看護師が来るという";
		mes "　話は聞いていないらしい。";
		mes "　看護師ラズに伝えよう‐";
		close;
	}
	mes "[町の女]";
	mes "冒険者さんですか？";
	mes "最近、この町を訪れる";
	mes "冒険者が増えましたね。";
	next;
	mes "[町の女]";
	mes "私はこの町で生まれ育ちましたけど";
	mes "冒険者たちの話を聞いていると、";
	mes "どこか遠くへ旅行するのも";
	mes "おもしろそうだなって思います。";
	if(MALAYA_4QUE == 5) {
		next;
		if(select("病院のことを聞く","話を終える") == 2) {
			mes "[町の女]";
			mes "ゆっくり滞在してくださいね。";
			close;
		}
		mes "[町の女]";
		mes "病院ですか？";
		mes "少し前から閉鎖されていましたよ。";
		mes "なにか事故があったみたいで、";
		mes "病院の話になると";
		mes "事情を知っている町の人は";
		mes "みんな口を閉ざすんです。";
		next;
		mes "[町の女]";
		mes "私が病院のお世話になったのは";
		mes "お腹が痛くなった時くらいです。";
		mes "いい思い出はありませんが、";
		mes "特別、気にするようなことも";
		mes "ありませんでした。";
		next;
		menu "看護師のことを聞く",-;
		mes "[町の女]";
		mes "新しく来る看護師……ですか？";
		mes "さあ……";
		mes "病院が閉鎖されているのに";
		mes "看護師が来るなんていうことが";
		mes "あるのかしら？";
		next;
		mes "‐町の女性から話を聞いた。";
		mes "　病院に新しい看護師が来るという";
		mes "　話は聞いていないらしい。";
		mes "　看護師ラズに伝えよう‐";
		delquest 11287;
		setquest 11288;
		set MALAYA_4QUE,6;
		close;
	}
	close;
}

malaya.gat,62,37,4	script	町の男	582,{
	if(MALAYA_1QUE < 6) {
		mes "[町の男]";
		mes "見かけない顔だな。";
		mes "この町に何か用かね？";
		next;
		mes "‐こちらを探るような目つきで";
		mes "　見ている。";
		mes "　警戒されているようだ‐";
		close;
	}
	if(MALAYA_4QUE == 8) {
		mes "[町の男]";
		mes "病院が閉鎖されてからは、";
		mes "ドクターは旅館に泊まっているんだ。";
		mes "私が連絡を入れておくので、";
		mes "町の中央の旅館の近くにいる";
		mes "ドクターのところまで、";
		mes "看護師を連れて行ってくれないか？";
		next;
		mes "‐病院のドクターは";
		mes "　旅館の近くにいるらしい。";
		mes "　看護師ラズにそのことを伝えよう‐";
		close;
	}
	mes "[町の男]";
	mes "ふむふむ。";
	mes "他の町からわざわざ来たのかね。";
	mes "時間があるようなら、";
	mes "私のパイナップル農場を";
	mes "見ていかないかね。";
	next;
	mes "[町の男]";
	mes "少し町から離れちゃいるが、";
	mes "旅の話を聞かせてくれるなら";
	mes "パイナップルを食わせてやるからさ。";
	if(MALAYA_4QUE == 7) {
		next;
		menu "あまり暇ではない",-;
		mes "[町の男]";
		mes "そうか、残念だな。";
		mes "何か用事でもあるのかい？";
		next;
		if(select("病院のことを聞く","話を終える") == 2) {
			mes "[町の男]";
			mes "時間ができたらまた来てくれよ。";
			close;
		}
		mes "[町の男]";
		mes "そこの病院のことか……。";
		next;
		mes "[町の男]";
		mes "少し前に事故があってな、";
		mes "その後、閉鎖されちまったんだ。";
		mes "町のイメージを損なうから、";
		mes "外から来た人に";
		mes "あまり話すわけにもいかなくてな。";
		next;
		menu "看護師のことを聞く",-;
		mes "[町の男]";
		mes "おお!!";
		mes "看護師に会ったのか?!";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "先ほどから病院の前にいましたよ。";
		mes "今は本部に連絡しているはずですけど。";
		next;
		mes "[町の男]";
		mes "そうだったのか。";
		mes "急いで来てくれと要請していたんだ。";
		mes "例の看護師がもう来ているとは！";
		mes "いやあ、よかった。";
		next;
		menu "例の看護師とは？",-;
		mes "[町の男]";
		mes "町の病院を再開させるために";
		mes "わざわざ招待した方なんだ。";
		mes "早速、ドクターたちに知らせないと。";
		next;
		mes "[町の男]";
		mes "病院が閉鎖されてからは、";
		mes "ドクターは旅館に泊まっているんだ。";
		mes "私が連絡を入れておくので、";
		mes "町の中央の旅館の近くにいる";
		mes "ドクターのところまで、";
		mes "看護師を連れて行ってくれないか？";
		next;
		mes "‐病院のドクターは";
		mes "　旅館の近くにいるらしい。";
		mes "　看護師ラズにそのことを伝えよう‐";
		delquest 11289;
		setquest 11290;
		set MALAYA_4QUE,8;
		close;
	}
	close;
}

malaya.gat,210,200,5	script	ドクタープン	865,{
	if(MALAYA_1QUE < 6) {
		mes "[ドクタープン]";
		mes "……";
		next;
		mes "‐警戒されているようだ‐";
		close;
	}
	switch(MALAYA_4QUE) {
	case 9:
		mes "[ドクタープン]";
		mes "おや？";
		mes "君が新しく来た看護師ですか？";
		next;
		if(select("そうです","違います") == 1) {
			mes "[ドクタープン]";
			mes "待っていました。";
			mes "頼んでいた仕事の前に……";
			mes "まずは手を貸してください。";
			mes "今日は患者が多くて忙しいのです！";
			mes "さあ、早く着替えて！";
			close;
		}
		mes "[ドクタープン]";
		mes "おっと、すみません！";
		mes "新任の看護師が来ることになっていて";
		mes "勘違いしてしまいました。";
		next;
		menu "事情を説明する",-;
		mes "[ドクタープン]";
		mes "看護師の代わりに来てくれたんですか。";
		mes "わざわざありがとうございます。";
		mes "本来はこちらに";
		mes "来てもらうはずでしたが、";
		mes "途中で間違って";
		mes "伝わってしまったのかもしれませんね。";
		next;
		mes "[ドクタープン]";
		mes "病院がああなってしまってからは、";
		mes "ずっとこの旅館で泊まりながら";
		mes "診察しているんです。";
		next;
		mes "[ドクタープン]";
		mes "……病院を元に戻したくても";
		mes "町の患者を放り出すわけにもいかず、";
		mes "指導者や本部にかけあって、";
		mes "ようやく人を派遣してもらったのです。";
		next;
		mes "[ドクタープン]";
		mes "看護師には申し訳ないのですが、";
		mes "今日の診察が終わるまで";
		mes "私はここを離れられません。";
		mes "もしよかったら、";
		mes "君が看護師に病院の鍵を";
		mes "届けてくれませんか？";
		next;
		mes "[ドクタープン]";
		mes "そして、";
		mes "「好きなように仕事をしてください」";
		mes "と伝えてください。";
		mes "お願いします。";
		next;
		mes "[ドクタープン]";
		mes "意味がわかりませんか？";
		mes "看護師が評判通りの人なら、";
		mes "そう言えば、伝わるはずです。";
		next;
		mes "[ドクタープン]";
		mes "それ以上は……";
		mes "あなたのような親切な人に、";
		mes "この町のよくないところを";
		mes "知られたくありませんので……";
		next;
		mes "‐看護師ラズに病院の鍵を渡し、";
		mes "　ドクタープンの伝言を伝えよう‐";
		delquest 11291;
		setquest 11292;
		set MALAYA_4QUE,10;
		close;
	case 10:
		mes "[ドクタープン]";
		mes "看護師には申し訳ないのですが、";
		mes "今日の診察が終わるまで、";
		mes "私はここを離れられません。";
		mes "もしよかったら、";
		mes "君が看護師に病院の鍵を";
		mes "届けてくれませんか？";
		next;
		mes "[ドクタープン]";
		mes "そして、";
		mes "「好きなように仕事をしてください」";
		mes "と伝えてください。";
		mes "お願いします。";
		next;
		mes "‐看護師ラズに病院の鍵を渡し、";
		mes "　ドクタープンの伝言を伝えよう‐";
		close;
	default:
		mes "[ドクタープン]";
		mes "むむむ……";
		mes "し……仕事が終わらない……";
		mes "私一人で町じゅうの患者を診るなんて";
		mes "とてもじゃないが、手が回らない！";
		next;
		mes "[ドクタープン]";
		mes "ん？";
		mes "医者がなぜ旅館にいるのかって？";
		mes "旅館にいたっていいじゃないか！";
		close;
	}
}

malaya.gat,53,68,4	script	草むら	844,{
	switch(MALAYA_4QUE) {
	case 13:
		mes "[？？？]";
		mes "近寄るな！";
		mes (Sex? "おじ": "おば")+ "さん！";
		mes "なぜ、ボクがここにいることを";
		mes "知っているのだ？";
		emotion 23;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes (Sex? "おじ": "おば")+ "さんじゃない！";
		emotion 6,"";
		next;
		switch(select("病院に入れないことについて","怒られる？","誰だ？","お婆さんのことを聞く","そっとしておく")) {
		case 1:
			mes "[？？？]";
			mes "隣の家に住んでいるお婆さんが";
			mes "病院の周りで、何か言いながら";
			mes "棒のような物を";
			mes "地面に突き刺していたのだ。";
			mes "きっとケッカイってやつだな。";
			next;
			mes "[？？？]";
			mes "ふふふふ……";
			mes "しゃべりすぎてしまったようだな。";
			mes "病院にいることがバレないように";
			mes "ボクは身を隠すのだ。";
			break;
		case 2:
			mes "[？？？]";
			mes "前にお母さんが言ってたのだ。";
			mes "隣のお姉さんが";
			mes "この病院に入院していたらしい。";
			mes "退院はできなかったけど……";
			next;
			mes "[？？？]";
			mes "他にも、この病院に入院した人たちに";
			mes "悪いことが沢山あったらしいよ。";
			next;
			mes "[？？？]";
			mes "だから、お母さんは";
			mes "ボクがここに来るのを禁止してるのだ。";
			break;
		case 3:
			mes "[？？？]";
			mes "それだけは教えられないのだ。";
			mes "前もバレてお尻を叩かれたから！";
			mes "知ってるか？";
			mes "お尻を叩かれるととても痛いのだぞ！";
			break;
		case 4:
			mes "[？？？]";
			mes "うちの隣に住んでいる";
			mes "お婆さんなんだけど、";
			mes "何日か前に病院の周りで";
			mes "何かしていたのだ。";
			next;
			mes "[？？？]";
			mes "ここにいるのがばれないように";
			mes "遠くから見ていたから";
			mes "何をしているかわからなかったけど、";
			mes "お婆さんが帰った後に";
			mes "何かしていたあたりを見たら";
			mes "棒のようなものがあったのだ。";
			next;
			mes "[？？？]";
			mes "嘘だと思うなら、";
			mes "病院の周りを調べてみればいいのだ。";
			mes "いくつも棒があるんだから！";
			next;
			mes "‐病院の周りにあるという";
			mes "　棒を調べてみよう‐";
			delquest 11294;
			setquest 11295;
			set MALAYA_4QUE,14;
			close;
		case 5:
			mes "[？？？]";
			mes "ふふふふ……";
			emotion 29;
			close;
		}
		next;
		mes "[？？？]";
		mes "ボクがここにいることは内緒だぞ。";
		mes "特にお母さんには絶対に言わないで！";
		mes "くくくくく……";
		close;
	case 14:
		mes "[？？？]";
		mes "ここにいるのがばれないように";
		mes "遠くから見ていたから";
		mes "何をしているかわからなかったけど、";
		mes "お婆さんが帰った後に";
		mes "何かしていたあたりを見たら";
		mes "棒のようなものがあったのだ。";
		next;
		mes "[？？？]";
		mes "嘘だと思うなら、";
		mes "病院の周りを調べてみればいいのだ。";
		mes "いくつも棒があるんだから！";
		next;
		mes "‐病院の周りにあるという";
		mes "　棒を調べてみよう‐";
		close;
	case 15:
		mes "[？？？]";
		mes "近寄るな！";
		mes (Sex? "おじ": "おば")+ "さん！";
		mes "なぜ、ボクがここにいることを";
		mes "知っているのだ？";
		emotion 23;
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes (Sex? "おじ": "おば")+ "さんじゃない。";
		emotion 6,"";
		close;
	default:
		if(MALAYA_4QUE < 16) {
			mes "‐ただの草むらだ。";
			mes "　触ると草がこすれる音がする‐";
			close;
		}
		mes "‐小さな足跡が残っている。";
		mes "　今は誰もいないようだ‐";
		close;
	}
}

malaya.gat,40,52,4	script	怪しい木の棒#ma1	858,{
	if(MALAYA_4QUE == 14) {
		mes "‐奇妙な形をした木の棒が";
		mes "　地面に突き立てられている。";
		mes "　不思議な気配を感じる‐";
		next;
		if(select("棒を引き抜く","そのままにしておく") == 2) {
			mes "‐あなたは木の棒には手を触れず";
			mes "　その場を後にした‐";
			close;
		}
		if(rand(3) == 0) {
			if(checkitemblank() == 0) {
				mes "‐これ以上、アイテムを持つことは";
				mes "　できません。";
				mes "　アイテムの種類数を減らしてから";
				mes "　再度、調べてください‐";
				close;
			}
			if(checkweight(6497,1) == 0) {
				mes "‐これ以上、アイテムを持つことは";
				mes "　できません。";
				mes "　アイテムの重量を減らしてから";
				mes "　再度、調べてください‐";
				close;
			}
			mes "‐木の棒を引き抜いた。";
			mes "　よく見るとお守りが貼られている。";
			mes "　";
			mes "　不思議な気配が弱まった";
			mes "　ような気がする‐";
			if(rand(2) == 0)
				getitem 6497,1;
			else {
				delquest 11295;
				setquest 11296;
				set MALAYA_4QUE,15;
				getitem 6497,1;
				next;
				mes "‐このお守りは何だろう？";
				mes "　ひとまず、ラズのところに戻ろう‐";
			}
		} else {
			mes "‐木の棒を引き抜いた。";
			mes "　不思議な気配が弱まった";
			mes "　ような気がする‐";
		}
		initnpctimer;
		close;
	}
	mes "‐奇妙な形をした木の棒が";
	mes "　地面に突き立てられている‐";
	close;
OnTimer1000:
	hideonnpc strnpcinfo(0);
	end;
OnTimer16000:
	stopnpctimer;
	hideoffnpc strnpcinfo(0);
	end;
}

malaya.gat,31,42,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma2	858
malaya.gat,34,36,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma3	858
malaya.gat,40,32,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma4	858
malaya.gat,50,85,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma5	858
malaya.gat,46,93,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma6	858
malaya.gat,36,98,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma7	858
malaya.gat,48,79,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma8	858
malaya.gat,50,46,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma9	858
malaya.gat,59,84,4	duplicate(怪しい木の棒#ma1)	怪しい木の棒#ma10	858

malaya.gat,114,183,3	script	腰の曲がった老婆	575,{
	switch(MALAYA_4QUE) {
	case 17:
		mes "[腰の曲がった老婆]";
		mes "あの病院にはきっと何かいる！";
		next;
		menu "木の棒を見せる",-;
		mes "[腰の曲がった老婆]";
		mes "ん？";
		mes "その棒は……";
		emotion 23;
		next;
		mes "[腰の曲がった老婆]";
		mes "ええええええ!!";
		emotion 23;
		next;
		mes "[腰の曲がった老婆]";
		mes "き、き、キサマ!!";
		mes "なんちゅーことをしてくれたんじゃ！";
		next;
		mes "[腰の曲がった老婆]";
		mes "それはヤツを封じるための";
		mes "お守りだったのに！";
		mes "それを抜いたら、またヤツが";
		mes "悪さをはじめてしまう！";
		next;
		mes "[腰の曲がった老婆]";
		mes "ワシは見たのじゃ！";
		mes "病院の窓に映ったヤツの影を。";
		next;
		mes "[腰の曲がった老婆]";
		mes "……入院患者は誰一人として";
		mes "帰ってこなかった。";
		mes "おそらく、ヤツは患者達に悪夢を見せ";
		mes "自分の糧にしていたに違いない。";
		next;
		mes "[腰の曲がった老婆]";
		mes "私の娘も、同じように……";
		mes "…………";
		next;
		mes "‐病院の前には看護師ラズが";
		mes "　一人で待っているはずだ。";
		mes "　老婆の言う通りならば、";
		mes "　「ヤツ」が病院から";
		mes "　出てくるかもしれない。";
		mes "　急いで病院に戻ろう‐";
		delquest 11298;
		setquest 11299;
		set MALAYA_4QUE,18;
		close;
	case 18:
		mes "‐病院の前には看護師ラズが";
		mes "　一人で待っているはずだ。";
		mes "　老婆の言う通りならば、";
		mes "　「ヤツ」が病院から";
		mes "　出てくるかもしれない。";
		mes "　急いで病院に戻ろう‐";
		close;
	case 23:
		mes "[腰の曲がった老婆]";
		mes "おや？";
		mes "おまえさんは、たしか……？";
		mes "……誰じゃったかのう？";
		next;
		mes "[腰の曲がった老婆]";
		mes "病院の中のお守り？";
		mes "……おそらく、町のシャーマンが";
		mes "作ったものじゃろう。";
		mes "シャーマンは";
		mes "町の北の方にいるはずじゃ。";
		next;
		mes "[腰の曲がった老婆]";
		mes "それほど有名ではないが、";
		mes "あのシャーマンの作る";
		mes "お守りの効果は確かじゃぞ。";
		next;
		mes "‐ポートマラヤの北にいるという";
		mes "　シャーマンに話を聞きに行こう‐";
		delquest 11304;
		setquest 11305;
		set MALAYA_4QUE,24;
		close;
	case 24:
		mes "[腰の曲がった老婆]";
		mes "シャーマンは";
		mes "町の北の方にいるはずじゃ。";
		next;
		mes "[腰の曲がった老婆]";
		mes "それほど有名ではないのじゃが、";
		mes "あのシャーマンの作る";
		mes "お守りの効果は確かじゃぞ。";
		next;
		mes "‐ポートマラヤの北にいるという";
		mes "　シャーマンに話を聞きに行こう‐";
		close;
	}
	mes "[腰の曲がった老婆]";
	mes "おほほほ。";
	next;
	mes "[腰の曲がった老婆]";
	mes "え？";
	mes "これ以上食べられんよ。";
	next;
	mes "[腰の曲がった老婆]";
	mes "そうじゃない？";
	mes "ワシも若いころは";
	mes "町で評判の美人だったのじゃ。";
	if(MALAYA_4QUE == 16) {
		next;
		mes "[腰の曲がった老婆]";
		mes "違う？";
		mes "すまないねえ。";
		mes "大きい声で話してくれんかね。";
		next;
		mes "[腰の曲がった老婆]";
		mes "病院のことじゃと？";
		mes "お～、そうかそうか、病院か。";
		next;
		mes "[腰の曲がった老婆]";
		mes "ん……病院？";
		mes "病院じゃと！";
		next;
		mes "[腰の曲がった老婆]";
		mes "ああああの病院は呪われておる！";
		mes "とても悪いものが";
		mes "憑りついておるのじゃあ！";
		next;
		mes "[腰の曲がった老婆]";
		mes "ワシの娘も、ヤツに連れて行かれて";
		mes "しまったのじゃ。";
		mes "けして……けっして";
		mes "近寄ってはならぬぞ。";
		next;
		if(select("病院のことを聞く","娘のことを聞く") == 2) {
			mes "[腰の曲がった老婆]";
			mes "私の娘は、命を落とすほどの";
			mes "病ではなかった。";
			mes "ただの風邪だったのじゃ……";
			next;
			mes "[腰の曲がった老婆]";
			mes "あの病院にはきっと何かいる！";
			mes "きっとワシの娘も、";
			mes "ヤツにやられたに違いないのじゃ！";
			close;
		}
		mes "[腰の曲がった老婆]";
		mes "病院の設立が決まった時には、";
		mes "みんな喜んだものじゃよ。";
		mes "大きな病院のある町まで";
		mes "行かなくても、";
		mes "治療を受けられるようになるとな。";
		next;
		mes "[腰の曲がった老婆]";
		mes "じゃが、どういうわけか";
		mes "病院で治療を受けた者は";
		mes "余計に悪くなっていったのじゃ。";
		mes "やはり……町の古木を切って";
		mes "病院を建築したのが";
		mes "良くなかったに違いない。";
		next;
		mes "[腰の曲がった老婆]";
		mes "病院がおかしいと気づいた者は";
		mes "指導者様に陳情にも行ったのじゃ。";
		mes "だが、何もしてくれなかった……";
		next;
		mes "[腰の曲がった老婆]";
		mes "そうしているうちに、";
		mes "入院していた人たちが";
		mes "次々に亡くなったと伝えられた。";
		mes "私の娘と同じように……";
		next;
		mes "‐病院が呪われていると";
		mes "　老婆は言っている。";
		mes "　抜いた木の棒をこの老婆に";
		mes "　見せてみよう‐";
		delquest 11297;
		setquest 11298;
		set MALAYA_4QUE,17;
	}
	close;
}

malaya.gat,276,367,4	script	腰の曲がったシャーマン	782,{
	if(MALAYA_1QUE < 6) {
		mes "[腰の曲がったシャーマン]";
		mes "…………";
		next;
		mes "‐こちらに気づいていないようだ‐";
		close;
	}
	mes "[腰の曲がったシャーマン]";
	mes "うむ……";
	mes "感じる……";
	next;
	mes "[腰の曲がったシャーマン]";
	mes "何か不吉な気配を";
	mes "おぬしから感じる……";
	if(MALAYA_4QUE == 24) {
		next;
		mes "[腰の曲がったシャーマン]";
		mes "……";
		mes "何も言わなくてもいい。";
		mes "これが必要になるじゃろう。";
		next;
		mes "[腰の曲がったシャーマン]";
		mes "この札はな、";
		mes "強い力を封じ込めることが";
		mes "できるのじゃ。";
		next;
		mes "[腰の曲がったシャーマン]";
		mes "きわめて強力な効果を持つゆえ";
		mes "使い方を誤れば、災いを招くじゃろう。";
		mes "……だが、おぬしには必要なものじゃ。";
		mes "持っていくがいい。";
		next;
		mes "[腰の曲がったシャーマン]";
		mes "大丈夫じゃ。";
		mes "お金は必要ない。";
		mes "これはこの町の因果なのじゃ……";
		next;
		mes "‐シャーマンの札を受け取った。";
		mes "　看護師ラズのところに戻ろう‐";
		delquest 11305;
		setquest 11306;
		set MALAYA_4QUE,25;
		close;
	}
	if(MALAYA_4QUE == 25) {
		next;
		mes "‐看護師ラズのところに戻ろう‐";
		close;
	}
	close;
}

ma_dun01_jp.gat,108,176,0	script	#mirror2	844,{
	mes "‐鏡には元の世界が映しだされている。";
	mes "　近づけば戻ることができそうだ‐";
	close;
}

ma_dun01_jp.gat,108,49,0	script	#mirror1	844,{
	mes "‐鏡には元の世界が映しだされている。";
	mes "　近づけば戻ることができそうだ‐";
	close;
}

//============================================================
// 森の中の秘密クエストNPC
//- Registry -------------------------------------------------
// MALAYA_5QUE -> 0～15
//------------------------------------------------------------
malaya.gat,305,281,3	script	警備隊員	570,7,7,{
	if(MALAYA_1QUE < 2) {
		mes "‐警備隊員は警戒中のようだ。";
		mes "　相手をしてくれそうにない‐";
		close;
	}
	if(MALAYA_1QUE < 6) {
		mes "[警備隊員]";
		mes "ポートマラヤの外には";
		mes "^3131FFバリオ・マヒワガ^000000という";
		mes "小さな地域があります。";
		mes "ここと比べて少しは";
		mes "自然に近い生活をしています。";
		next;
		mes "[警備隊員]";
		mes "だけど、そこは";
		mes "恐ろしいモンスターもいるので、";
		mes "もし行くのなら気を付けて下さい。";
		close;
	}
	if(BaseLevel < 100) {
		mes "[警備隊員]";
		mes "最近は人知れず町を離れる人たちが";
		mes "増えています。";
		mes "あなたも神秘の宝を探しに";
		mes "森に行こうとしているんですか？";
		next;
		mes "[警備隊員]";
		mes "しかし……今のあなたの実力では";
		mes "難しいと思います。";
		mes "森の道中で倒れてしまうかも……。";
		next;
		mes "‐警備隊員に実力不足を指摘された。";
		mes "　^FF0000BaseLv100以上^000000になってから";
		mes "　あらためて、話かけてみよう‐";
		close;
	}
	switch(MALAYA_5QUE) {
	case 0:
		mes "[警備隊員]";
		mes "最近は人知れず町を離れる";
		mes "人が増えています。";
		mes "あなたも神秘の宝を探しに";
		mes "森に行こうとしているんですか？";
		next;
		if(select("宝？","いいえ、違います") == 2) {
			mes "[警備隊員]";
			mes "そうですか……。";
			close;
		}
		mes "[警備隊員]";
		mes "あれ？　宝探しでは無いのですか？";
		next;
		mes "[警備隊員]";
		mes "最近、町の人たちの間では";
		mes "森にすごい宝が隠されているとの";
		mes "ウワサが広まっています。";
		next;
		mes "[警備隊員]";
		mes "そこで噂話をしている人たちも";
		mes "毎日宝の話をしています。";
		mes "もし興味があるなら";
		mes "一度話を聞くといいでしょう。";
		delquest 72076;
		setquest 2271;
		set MALAYA_5QUE,1;
		close;
	case 1:
		mes "[警備隊員]";
		mes "そこで噂話をしている人たちも";
		mes "毎日宝の話をしています。";
		mes "もし興味があるなら";
		mes "一度話を聞くといいでしょう。";
		close;
	default:
		mes "[警備隊員]";
		mes "やはり宝の話は";
		mes "ただのウワサだったんでしょうか。";
		close;
	}
OnTouch:
	if(MALAYA_1QUE == 6 && MALAYA_5QUE < 1) {
		emotion 0,"";
		emotion 0;
	}
	end;
OnInit:
	waitingroom "森の中の秘密",0;
	end;
}

malaya.gat,276,288,5	script	話好きな住民	582,{
	if(MALAYA_1QUE < 6) {
		mes "‐住民たちはとても警戒しながら、";
		mes "　自分たちだけで話をしている‐";
		close;
	}
	switch(MALAYA_5QUE) {
	case 1:
		emotion 0,"話好きな住民";
		mes "[話好きな住民]";
		mes "森で迷子になったんじゃないかな。";
		mes "こんな小さな町で";
		mes "宝を隠す人がいると思うか？";
		next;
		emotion 19,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "モンスターにやられたのでは？";
		mes "深い森の奥には頭が大きな竜が";
		mes "住んでるとお婆ちゃんが言ってたわ。";
		next;
		emotion 22,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "違う、俺の話をよく聞くんだ。";
		next;
		mes "[お調子者の住民]";
		mes "お前ら^3131FFトトイ^000000は知っているな。";
		mes "^3131FF旅館^000000に住んでいる子だよ。";
		mes "あいつがこの前、森に";
		mes "行ってたのを知っているか？";
		next;
		emotion 23,"話好きな住民";
		emotion 23,"聞き上手な住民";
		mes "[話好きな住民]";
		mes "本当か!?　無事に帰って来たのか？";
		next;
		emotion 0,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "そう、しかも怪しいのは";
		mes "あのわんぱくな^3131FFトトイ^000000が";
		mes "その後、家から外に出てこないんだよ。";
		next;
		emotion 1,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "どうしてかしら？";
		next;
		emotion 0,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "決まってるだろ。";
		mes "あいつが宝を見つけたに違いない。";
		next;
		emotion 23,"話好きな住民";
		emotion 23,"聞き上手な住民";
		mes "[話好きな住民]";
		mes "まさか!?";
		mes "すると^3131FFトトイ^000000はお金持ちに？";
		next;
		emotion 22,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "それはまだだと思う。";
		mes "^3131FFトトイ^000000の奴が";
		mes "家に戻ってくるのを見たけど、";
		mes "何にも持っていなかったんだ。";
		next;
		emotion 1,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "じゃあ^3131FFトトイ^000000は家で";
		mes "何をしているのかしら？";
		next;
		emotion 9,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "町の人たちにばれないよう";
		mes "密かに宝を持って来るために";
		mes "計画をたてているんだろう。";
		mes "誰にもばれなければ";
		mes "すべての宝を独り占めできるからな。";
		next;
		emotion 0,"話好きな住民";
		mes "[話好きな住民]";
		mes "なるほど！";
		mes "それなら確かにつじつまが合う！";
		next;
		emotion 14,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "お宝。いいなぁ～～。";
		mes "私ならピカピカに磨いて";
		mes "誰よりも美しく飾る自信があるのに！";
		next;
		emotion 9,"お調子者の住民";
		mes "[お調子者の住民]";
		mes "だから私たちが^3131FFトトイ^000000の奴を";
		mes "うまく説得して宝の在り処を";
		mes "聞き出そうじゃないか！　どうだい？";
		next;
		emotion 0,"話好きな住民";
		mes "[話好きな住民]";
		mes "いいアイディアだ！";
		next;
		emotion 9,"話好きな住民";
		mes "[話好きな住民]";
		mes "ただ、^3131FFトトイ^000000の奴が";
		mes "簡単にそれを教えてくれるか？";
		mes "奴は宝を独り占めしようと";
		mes "しているというのに……。";
		next;
		emotion 28,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "じゃあ私たちは宝探しではなく";
		mes "^3131FFトトイ^000000を説得する方法を";
		mes "今度は考えないといけないのかな？";
		next;
		emotion 28,"聞き上手な住民";
		mes "[聞き上手な住民]";
		mes "あ～～美しい物を手に入れるのって";
		mes "本当にむずかし～～!!";
		delquest 2271;
		setquest 2272;
		set MALAYA_5QUE,2;
		close;
	case 2:
		mes "‐これ以上の情報はなさそうだ。";
		mes "　トトイという人を探してみよう‐";
		close;
	default:
		mes "‐町の住民たちが";
		mes "　深刻な顔をしながら";
		mes "　何か話している‐";
		close;
	}
}
malaya.gat,278,288,3	duplicate(話好きな住民)	聞き上手な住民	583
malaya.gat,276,286,7	duplicate(話好きな住民)	お調子者の住民	582

ma_in01.gat,47,101,3	script	トトイ	577,7,7,{
	switch(MALAYA_5QUE) {
	case 3:
		if(countitem(506) < 1){
			mes "[トトイ]";
			mes "理由は後で説明するから";
			mes "まずは目を治してくれない？";
			mes "多分棚の中に^3131FF緑ポーション^000000が";
			mes "残っているはずなんだ。";
			mes "悪いけど、それを持ってきてよ。";
			close;
		}
		mes "[トトイ]";
		mes "あれ、まだそこにいるの？";
		mes "緑ポーションはあった？";
		mes "前が見えなくてどうにかなりそう。";
		next;
		if(select("緑ポーションを渡す","渡さない") == 2) {
			mes "[トトイ]";
			mes "何だよ！";
			mes "意地悪するなよ！";
			close;
		}
		mes "[トトイ]";
		mes "緑ポーションだ。ありがとう！";
		mes "よし。これをこうして……";
		mes "ゴクゴク……";
		mes "……";
		mes "パチパチ……パチパチ……";
		mes "おぉ。おぉぉ！";
		delitem 506,1;
		delquest 72150;
		setquest 72155;
		set MALAYA_5QUE,4;
		close;
	case 4:
		emotion 0;
		mes "[トトイ]";
		mes "見える!!　目が見える！";
		mes "やった！";
		next;
		emotion 9,"";
		emotion 21;
		mes "[トトイ]";
		mes "ふぅ……。";
		mes "あーよかったぁ。";
		mes "ありがとう！";
		next;
		mes "[トトイ]";
		mes "それで、さっき何て言ったっけ？　宝？";
		mes "ボクが宝を見つけたとか。";
		mes "いったいそれは何の話なの？";
		next;
		menu "住民が話していた内容を聞かせる",-;
		emotion 18;
		mes "[トトイ]";
		mes "何だって？";
		mes "宝を見つけて、ボクがお金持ち!?";
		mes "何言ってるの!？";
		next;
		emotion 32;
		mes "[トトイ]";
		mes "どうして一体";
		mes "そんなわけのわからない話に……";
		mes "ははっ。ははは……";
		mes "はぁ……。";
		next;
		mes "[トトイ]";
		mes "……。";
		next;
		mes "[トトイ]";
		mes "森には、虫を捕まえるために";
		mes "行っただけだよ。";
		mes "宝なんか見たこともない。";
		mes "それより……。";
		next;
		emotion 9;
		mes "[トトイ]";
		mes "まさかあんなことになるなんて……。";
		next;
		menu "何があったか聞く",-;
		mes "[トトイ]";
		mes "かわいい虫を取ってきて";
		mes "いたずらしようと思ってたんだ。";
		next;
		emotion 18;
		mes "[トトイ]";
		mes "服の中に氷とか虫をいれるのは";
		mes "挨拶のようなもんでしょ？";
		mes "町のひとが大騒ぎしながら";
		mes "走り回るのが楽しくて！";
		next;
		mes "[トトイ]";
		mes "それで、普通の虫じゃあ";
		mes "みんなもあまり驚かないと思って";
		mes "エドーと一緒に森に入ったんだ。";
		mes "森なら珍しい虫がたくさんいるからね。";
		next;
		mes "[トトイ]";
		mes "あ、エドーはかわいいワンちゃんだよ。";
		mes "おとなしくて愛嬌がある大事な友達。";
		mes "ちょっと臆病なところがあって";
		mes "何にでもすぐ吠えるんだよね。";
		next;
		emotion 9;
		mes "[トトイ]";
		mes "その日、森で虫を探していた時も";
		mes "森の奥深くまで入ったあたりから";
		mes "エドーはワンワンよく吠えてた。";
		mes "ただ、いつもの事だしその時は";
		mes "そんなに気にしていなかったんだ。";
		next;
		mes "[トトイ]";
		mes "でもね。しばらくしてもエドーは";
		mes "全然鳴きやまなかったんだ。";
		mes "さすがにちょっとおかしいな、と思って";
		mes "仕方なく振り返ってみたんだよ。";
		mes "その時さ……。";
		next;
		musiceffect "42";
		mes "‐トトイは他の誰かに聞かれないよう";
		mes "　身を寄せて耳元でささやいた‐";
		next;
		mes "[トトイ]";
		mes "怪物がいたんだ。";
		next;
		menu "怪物!?",-;
		mes "[トトイ]";
		mes "今まで生きてきたなかで";
		mes "あれほど大きな口は初めて見たよ。";
		next;
		mes "[トトイ]";
		mes "大きな口が雲のように覆ってきて……";
		mes "所々にぶら下がっていたのは";
		mes "歯……かな。でっかい槍みたいな……。";
		next;
		mes "[トトイ]";
		mes "そのあいだからゆっくりと";
		mes "唾？　のようなものが流れ落ちてた。";
		next;
		mes "[トトイ]";
		mes "唾が流れ落ちた先には";
		mes "池のような水たまりがあって、";
		mes "ちゃぷちゃぷ、揺れてたんだ……。";
		next;
		mes "[トトイ]";
		mes "とにかくわけが、わからなかったよ。";
		next;
		menu "襲われなかった？",-;
		emotion 28;
		mes "[トトイ]";
		mes "うん。";
		mes "実はその時、ボクの大事なエドーが";
		mes "力一杯怪物の足を噛んでくれてたんだ。";
		mes "普段は臆病ですぐ吠えるのに。";
		mes "おかげでボクは逃げ切れたけど、";
		mes "多分エドーは……エドーは……。";
		next;
		mes "[トトイ]";
		mes "目はその時にやられた。";
		mes "どうやって帰ってきたのかは";
		mes "正直あんまり覚えてない。";
		next;
		menu "怪物はなんだったのかな",-;
		mes "[トトイ]";
		mes "う～ん、一番特徴的だったのは、";
		mes "背中に大きな箱を乗せていた";
		mes "ことだけど……";
		mes "ボクは見たことも聞いたことも";
		mes "ないような怪物だった。";
		next;
		mes "[トトイ]";
		mes "そもそもあの怪物を見て";
		mes "生きて帰ってきた人が";
		mes "あまりいないんじゃないかな。";
		next;
		mes "[トトイ]";
		mes "あぁ。^FF0000狩りの達人^000000なら";
		mes "何かを知っているかもしれないよ。";
		mes "道具屋の近くにいると思うよ。";
		mes "気になるなら、聞いてみたらどう。";
		next;
		mes "[トトイ]";
		mes "あぁ、エドー。";
		mes "エドー……。";
		mes "お願いだから無事でいて……。";
		musiceffect "149";
		delquest 72155;
		setquest 2273;
		set MALAYA_5QUE,5;
		close;
	case 5:
		mes "[トトイ]";
		mes "ボクのかわいいエドー……。";
		mes "お願いだからどうか無事でいて……。";
		mes "エドー!!　うわあぁぁ！";
		emotion 28;
		close;
	case 6:
		mes "[トトイ]";
		mes "エドー！　エ～～～ド～～～!!";
		mes "ボクを助ける為に死ぬなんて。";
		mes "うわあぁぁぁ!!";
		emotion 28;
		close;
	case 7:
		mes "[トトイ]";
		mes "エドー……エドー……。";
		mes "えっ？";
		mes "怪物と遭遇した場所が何処かって？";
		next;
		mes "[トトイ]";
		mes "うーん……うーん……。";
		mes "あまり覚えてないなぁ。";
		next;
		mes "[トトイ]";
		mes "かなり奥深い森だったから";
		mes "バリオ・マヒワガも通り越してたかな。";
		mes "^3131FF水の音^000000も聞こえた気がする。";
		mes "覚えているのはそのくらい。";
		close;
	case 8:
	case 9:
	case 10:
	case 11:
		mes "[トトイ]";
		mes "エドーに会いたい。エドー……。";
		mes "うわあぁぁ!!";
		close;
	case 12:
		emotion 28;
		mes "[トトイ]";
		mes "エドーに会いたい。エドー……。";
		mes "うわあぁぁ!!";
		next;
		mes "[エドー]";
		mes "ワン！　ワン!!";
		donpcevent "犬#totoi::OnStart";
		next;
		emotion 23;
		mes "[トトイ]";
		mes "!?";
		mes "エドー！　エドーなの!?";
		mes "えええええええ!!!!!!　なんで!?";
		mes "本当に？　本当!!　エドー!!";
		mes "エドー！　やった！　信じられない!!";
		next;
		mes "[トトイ]";
		mes "あなたがエドーを助けてくれたの？";
		mes "本当にありがとう！";
		mes "あの怪物と会わなかった？";
		next;
		menu "大丈夫。君も森には二度と近づかないでね",-;
		mes "[トトイ]";
		mes "うん!!";
		mes "えへへ。エドー。";
		mes "森は危険だからもう行かないよ！";
		next;
		mes "[エドー]";
		mes "……";
		next;
		mes "[トトイ]";
		mes "けど他にも遊ぶ場所はいっぱいあるから";
		mes "心配しないでね！";
		next;
		mes "[エドー]";
		mes "ワンワン!!";
		next;
		mes "[トトイ]";
		mes "本当にありがとう" +(Sex? "お兄": "お姉")+ "ちゃん！";
		next;
		mes "[トトイ]";
		mes "ボクも大きくなったら、";
		mes "お姉ちゃんみたいに綺麗で";
		mes "優しい女性になりたいな～！";
		mes "ねえねえ、なれるかなぁ？";
		next;
		menu "……もしかして女の子？",-;
		mes "[トトイ]";
		mes "そうだよ！";
		mes "よく男の子と間違われるけど……。";
		mes "名前がトトイだからなのかなぁ？";
		next;
		mes "[トトイ]";
		mes "まだお母さんのお腹の中にいた時に";
		mes "ボクがあまりに元気だったから、";
		mes "両親が男の子だと勘違いして";
		mes "こんな名前にしちゃったんだ。";
		mes "あはは。";
		next;
		mes "[トトイ]";
		mes "大事な友達を";
		mes "見つけてくれてありがと。";
		mes "何かお礼をしなくちゃ……。";
		mes "棚を調べてみるから、";
		mes "少ししたらもう一度話しかけてね。";
		delquest 2278;
		setquest 2279;
		set MALAYA_5QUE,13;
		close;
	case 13:
		mes "[トトイ]";
		mes "見つけた！";
		next;
		mes "[トトイ]";
		mes "これはボクのお母さんが";
		mes "くれた物なんだけど、";
		mes "ボクは何に使うのか";
		mes "よくわからないから。えへへ。";
		mes "役に立つといいんだけど。";
		next;
		if(checkitemblank() == 0) {
			mes "[トトイ]";
			mes "あれ、アイテムがいっぱいだよ？";
			mes "種類数を減らしてから";
			mes "もう一度話かけて！";
			close;
		}
		if(checkweight(6497,5) == 0) {
			mes "[トトイ]";
			mes "あれ、アイテムがいっぱいだよ？";
			mes "重量を減らしてから";
			mes "もう一度話かけて！";
			close;
		}
		getitem 6497,5;
		delquest 2279;
		setquest 2280;
		set MALAYA_5QUE,14;
		mes "[トトイ]";
		mes "それじゃあ。";
		mes "トトイに会いたくなったら";
		mes "また遊びに来てね！";
		next;
		mes "[エドー]";
		mes "ワンワンワン！";
		hideonnpc "犬#totoi";
		close;
	case 14:
	case 15:
		mes "[トトイ]";
		mes "エドーは遊びに行ってるから";
		mes "今はボクひとりなんだ。";
		mes "ねえ。何かおもしろい";
		mes "いたずらはないかな??";
		close;
	default:
		mes "‐ブルブル震えている‐";
		if(MALAYA_5QUE == 2) {
			next;
			if(select("肩を叩いてみる","そのままにしておく") == 2) {
				mes "‐少年は、何かに怯えるように";
				mes "　膝を抱えて震えている‐";
				close;
			}
			emotion 23;
			mes "[トトイ]";
			mes "ヒ！　ヒイイ!!　ヒイイイッ！";
			mes "く、来るな！　あっちに行け!!";
			next;
			menu "大丈夫？",-;
			mes "[トトイ]";
			mes "あれ……人……？　だ、誰？";
			next;
			mes "‐子供はこちらを見つめているが";
			mes "　何か様子がおかしい‐";
			next;
			mes "[トトイ]";
			mes "そこに誰かいるでしょ？　誰？";
			next;
			menu "住民から聞いた話をする",-;
			mes "[トトイ]";
			mes "宝？　何の話をしてるの!?";
			mes "そんなことより今、目が見えなくって。";
			mes "悪いけどまずはボクの目を";
			mes "治してくれない？";
			next;
			menu "なぜ目を……？",-;
			mes "[トトイ]";
			mes "理由は後で説明するよ。";
			mes "まずは先に目を治すのを";
			mes "手伝ってくれない？";
			mes "多分棚の中に^3131FF緑ポーション^000000が";
			mes "残っているはずなんだ。";
			mes "悪いけど、それを持ってきてよ。";
			delquest 2272;
			setquest 72150;
			set MALAYA_5QUE,3;
		}
		close;
	}
OnTouch:
	if(MALAYA_5QUE < 4)
		emotion 23;
	end;
}

ma_in01.gat,43,101,7	script	犬#totoi	81,{
	end;
OnStart:
	initnpctimer;
	hideoffnpc "犬#totoi";
	end;
OnTimer300000:
	stopnpctimer;
OnInit:
	hideonnpc "犬#totoi";
	end;
}

ma_in01.gat,44,105,3	script	棚	844,{
	if(MALAYA_5QUE == 3) {
		mes "‐あなたは棚を開けて";
		mes "　緑ポーションを探した‐";
		next;
		mes "‐ごそごそ‐";
		next;
		mes "‐ごそごそ‐";
		mes "‐ごそごそ‐";
		next;
		mes "‐バタバタ‐";
		next;
		mes "‐空の瓶しか見当たらない。";
		mes "　自分で用意するしかなさそうだ‐";
		close;
	}
	mes "‐棚がある‐";
	close;
}

malaya.gat,290,152,5	script	狩りの達人	578,{
	switch(MALAYA_5QUE) {
	case 5:
		mes "[狩りの達人]";
		mes "ひゅぅぅう！　ふぉぉぉぉ！";
		mes "私は狩りの達人。";
		mes "昨日はルーンミッドガッツ王国の";
		mes "ごっついミノタウロスを";
		mes "左手だけで倒してしまった。";
		mes "おっと。何か用かな？";
		next;
		if(select("トトイから聞いた話をする","特に用は無い") == 2) {
			mes "[狩りの達人]";
			mes "おい？　君！　どこに行くんだ?!";
			close;
		}
		mes "[狩りの達人]";
		mes "なんだって!?";
		mes "怪物を見たことがある人がいる？";
		next;
		mes "[狩りの達人]";
		mes "大げさな事をいっちゃいけないよ。";
		mes "モンスターならポートマラヤ中に";
		mes "いくらでもいるんだ。";
		mes "そのくらいでびっくりするなよ？";
		next;
		menu "背中に箱を乗せた怪物らしい",-;
		mes "[狩りの達人]";
		mes "背中に箱を乗せた怪物だと！";
		mes "そんな怪物がどこにいるというんだ!?";
		mes "私は狩りの達人だが、";
		mes "そんな怪物は見たことがない。";
		next;
		mes "[狩りの達人]";
		mes "ああ。きっとその子が";
		mes "その辺にいるコンドルを";
		mes "驚いて見間違えたんだろう。";
		next;
		mes "[狩りの達人]";
		mes "大人をバカにしてはいけないよ。";
		mes "きっと、この狩りの達人の関心を";
		mes "独り占めしたいんだろう。";
		mes "全く、強すぎるのも罪である。";
		mes "ひゅぅうぅぅ!!　ふぉぉぉぉ！";
		next;
		if(select("トトイを信じる","トトイを疑う") == 2) {
			mes "[狩りの達人]";
			mes "子供たちはよく";
			mes "自分たちが有利な話だけをする。";
			mes "その子もそうだったんだろう。";
			set MALAYA_5QUE,6;
			close;
		}
	case 6:
		if(MALAYA_5QUE == 6) {
			mes "[狩りの達人]";
			mes "なんだ、また来たのか。";
			next;
			if(select("怪物を探してみる！","怪物はいないようです") == 2) {
				mes "[狩りの達人]";
				mes "全部子供のいたずらだよ。";
				close;
			}
		}
		mes "[狩りの達人]";
		mes "ほう？　そこまで言うなら";
		mes "何か証拠を持って来てくれ。";
		next;
		mes "[狩りの達人]";
		mes "そうだな。生きているものはみな";
		mes "自身の痕跡を";
		mes "何らかの形で必ず残している。";
		mes "トイレを使わずに生活する事は";
		mes "不可能だろう？";
		mes "ふふふ。まぁそういう事だ。";
		emotion 29;
		next;
		mes "[狩りの達人]";
		mes "その子が怪物を見たという場所で";
		mes "^FF0000あれの標本^000000を10個";
		mes "採集して来てくれ。";
		mes "集めてきてくれたら";
		mes "その中に怪物の痕跡があるか";
		mes "調べようじゃないか。";
		next;
		mes "[狩りの達人]";
		mes "綺麗な女性の手で";
		mes "そのような物を触らせるのは忍びないが";
		mes "まぁ……うん。";
		mes "君ならなんとかしてくれるだろ？";
		delquest 2273;
		setquest 2274;
		set MALAYA_5QUE,7;
		close;
	case 7:
		if(countitem(6519) < 10) {
			mes "[狩りの達人]";
			mes "どうした。標本はまだか？";
			mes "それとも君には難しかったかな。";
			close;
		}
		delitem 6519,10;
		delquest 2274;
		setquest 2275;
		set MALAYA_5QUE,8;
		mes "[狩りの達人]";
		mes "むむ。この香り!!ぐっ。";
		mes "は……はぁ。た、確かに。";
		mes "私が頼んだ標本のようだな。";
		mes "とりあえずだ。そこに標本を置いて";
		mes "手をよく洗って来てくれ。";
		emotion 76;
		close;
	case 8:
		mes "[狩りの達人]";
		mes "では標本を調べてみよう。";
		next;
		mes "‐ごそごそ‐";
		next;
		mes "‐ごそごそ‐";
		mes "‐ごそごそ‐";
		next;
		mes "‐ごそごそ‐";
		mes "‐（く、臭い）‐";
		mes "‐ごそごそ‐";
		next;
		mes "[狩りの達人]";
		mes "む…！　こ、これは!!";
		next;
		mes "[狩りの達人]";
		mes "おお！　お！　お！　お！　ほおおお!!";
		next;
		mes "[狩りの達人]";
		mes "ちょっと君！";
		mes "ここに来てこれを触ってみろ！";
		delquest 2275;
		setquest 72160;
		set MALAYA_5QUE,9;
		hideoffnpc "#buwaya_soil";
		close;
	case 9:
		mes "[狩りの達人]";
		mes "早くあの標本を直接触ってみろ！";
		hideoffnpc "#buwaya_soil";
		close;
	case 10:
		mes "[狩りの達人]";
		mes "急いで警備隊長に";
		mes "ブワヤが活動再開したことを";
		mes "知らせるんだ。";
		mes "警備隊長は";
		mes "町の北側の地域にいるはずだ。";
		close;
	default:
		if(MALAYA_5QUE < 11) {
			mes "[狩りの達人]";
			mes "ひゅぅぅう！　ふぉぉぉぉ！";
			mes "私は狩りの達人！";
			mes "勇敢な私に怖い物はないが";
			mes "極度の人見知りなんだ……。";
			close;
		}
		mes "[狩りの達人]";
		mes "くうう……。";
		close;
	}
}

malaya.gat,291,152,3	script	#buwaya_soil	557,{
	if(MALAYA_5QUE != 9) {
		mes "‐何かひどく臭うものがある‐";
		close;
	}
	mes "‐ごそごそ‐";
	next;
	mes "‐ごそごそ‐";
	mes "‐のろのろ‐";
	next;
	mes "‐ごそごそ‐";
	mes "‐のろのろ‐";
	mes "‐ごそごそ‐";
	next;
	mes "‐手先に何か尖った物の";
	mes "　感触が伝わってきた‐";
	next;
	menu "なんですかこれは",-;
	mes "[狩りの達人]";
	mes "ほお！　その大きくて丈夫な物は！";
	next;
	mes "[狩りの達人]";
	mes "それは^3131FFブワヤ^000000の歯だ！";
	mes "まさか。こんなことが！";
	next;
	menu "ブワヤ？",-;
	mes "[狩りの達人]";
	mes "そうだ！　ブワヤだ。";
	mes "おい。くっ……もう持たなくていいぞ。";
	mes "き、強烈すぎる。";
	emotion 75,"狩りの達人";
	next;
	mes "[狩りの達人]";
	mes "……";
	mes "…………";
	mes "スー、ハァ～。";
	mes "ふうぅ。";
	emotion 54,"狩りの達人";
	next;
	mes "[狩りの達人]";
	mes "うむ。それでだ。";
	mes "その子が見たと言う";
	mes "背中に箱を乗せた怪物というのは";
	mes "ブワヤに間違いない。";
	next;
	mes "[狩りの達人]";
	mes "昔の話であまり覚えていないが";
	mes "うちのお母さんのお父さんの";
	mes "奥さんもそいつにやられたという";
	mes "話を聞いたことがある。";
	mes "私のおばあさんだ。";
	next;
	mes "[狩りの達人]";
	mes "ブワヤが通り過ぎた場所には";
	mes "どんな生命体も残らないと言う話だ。";
	mes "そのトトイという子は";
	mes "本当に運が良かったな。";
	next;
	menu "昔からいたんですか？",-;
	mes "[狩りの達人]";
	mes "ああ、一昔前は";
	mes "噂話として色々な事が聞けたものだが";
	mes "最近は全然聞かなくなっていたな。";
	mes "冬眠でもしていたんだろうか。";
	next;
	mes "[狩りの達人]";
	mes "とにかく、そのような恐ろしい怪物が";
	mes "活動を再開したということであれば";
	mes "我々も当分の間は";
	mes "気を付けた方が良さそうだな。";
	mes "町の人たちにも森の奥には";
	mes "入らないよう注意しておこう。";
	next;
	mes "[狩りの達人]";
	mes "よし。すまないが君、";
	mes "町の警備隊長の所に行って";
	mes "ブワヤが活動中だということを";
	mes "知らせてくれないか。";
	next;
	mes "[狩りの達人]";
	mes "私も他のハンターたちと";
	mes "連絡をとって奴を倒す方法を";
	mes "調べて見ることにしよう。";
	hideonnpc "#buwaya_soil";
	delquest 72160;
	setquest 2276;
	set MALAYA_5QUE,10;
	close;
OnInit:
	hideonnpc "#buwaya_soil";
	end;
}

ma_fild02.gat,155,235,3	script	何かの痕跡#01	557,{
	if(MALAYA_5QUE == 7) {
		if(countitem(6519) >= 10) {
			mes "‐標本はもうこれ以上";
			mes "　集めなくても良さそうだ‐";
			close;
		}
		mes "‐土と草などが混ざっている";
		mes "　何かの痕跡が見える‐";
		next;
		if(checkitemblank() == 0) {
			mes "‐アイテムの種類数が多くて";
			mes "　これ以上持つことができない。";
			mes "　種類数を減らしてから試そう‐";
			close;
		}
		if(rand(3) == 0) {
			mes "‐溢れる臭いに目まいをおこし";
			mes "　うまく採集ができなかった‐";
			sc_start3 SC_POISON,0,0,0,0,5000,10;
			close;
		}
		mes "‐少しの温かさを含んだ";
		mes "　柔らかいその標本を";
		mes "　あなたはゆっくりと採集した‐";
		getitem 6519,1;
		initnpctimer;
		hideonnpc strnpcinfo(0);
		close;
	}
	end;
OnTimer20000:
	stopnpctimer;
	hideoffnpc strnpcinfo(0);
	end;
}
ma_fild02.gat,143,142,3	duplicate(何かの痕跡#01)	何かの痕跡#02	557
ma_fild02.gat,266,155,3	duplicate(何かの痕跡#01)	何かの痕跡#03	557
ma_fild02.gat,221,91,3	duplicate(何かの痕跡#01)	何かの痕跡#04	557
ma_fild02.gat,205,85,3	duplicate(何かの痕跡#01)	何かの痕跡#05	557
ma_fild02.gat,300,98,3	duplicate(何かの痕跡#01)	何かの痕跡#06	557
ma_fild02.gat,100,275,3	duplicate(何かの痕跡#01)	何かの痕跡#07	557

malaya.gat,290,340,3	script	警備隊長	571,{
	if(MALAYA_1QUE < 6) {
		mes "‐警備隊長は鋭い目で";
		mes "　あなたを睨みながら警戒している‐";
		close;
	}
	switch(MALAYA_5QUE) {
	case 10:
		mes "[警備隊長]";
		mes "悪霊やモンスターへの対応で";
		mes "いま、私たちは忙しいんだ。";
		next;
		mes "[警備隊長]";
		mes "だが、警備は万全の体制で臨んでいる。";
		mes "安心してポートマラヤを楽しんでくれ。";
		next;
		if(select("ブワヤの事を知らせる","会話を終える") == 2)
			close;
		mes "[警備隊長]";
		mes "なに!?　ブワヤだって？";
		mes "噂でしか聞いたことが無かったが、";
		mes "本当に実在したとは！　何という事だ。";
		next;
		mes "[警備隊長]";
		mes "困ったぞ。";
		mes "今の私たちは町の中に";
		mes "ほとんどの戦力を配置した状態だ。";
		next;
		mes "[警備隊長]";
		mes "といって森を全面立入禁止に";
		mes "することは容易ではない……。";
		mes "森で食糧を集めて";
		mes "生計を立てている人もいるのだ。";
		mes "死活問題になってしまう……。";
		next;
		mes "[警備隊長]";
		mes "そうだ！　すまないが君";
		mes "ポートマラヤのために";
		mes "少し力を貸してくれるかね？";
		next;
		if(select("任せて下さい","お断りします") == 2) {
			mes "[警備隊長]";
			mes "ばかな!?";
			mes "このままでは町の人たちが";
			mes "無残にやられてしまう。";
			mes "よく考え直してくれ。";
			close;
		}
		mes "[警備隊長]";
		mes "頼もしい！　ありがとう。";
		mes "ではお願いさせてもらおう。";
		next;
		mes "[警備隊長]";
		mes "町の住民たちの生活環境を";
		mes "最大限確保するためには";
		mes "ブワヤが出没しそうな場所を";
		mes "把握しなければならない。";
		mes "その為には、ブワヤの住処を";
		mes "見つけるのが一番いいだろう。";
		next;
		mes "[警備隊長]";
		mes "君にはこの^3131FF煙幕弾^000000を渡しておく。";
		mes "まずはどこかにあるであろう";
		mes "ブワヤの住処を探してきてほしい。";
		next;
		mes "[警備隊長]";
		mes "それらしき場所を見つけたら";
		mes "^3131FF空に向けて煙幕弾を撃ってくれ。^000000";
		mes "その後、我々警備隊員が";
		mes "合図を頼りに向かうようにする。";
		next;
		mes "[警備隊長]";
		mes "くれぐれも気を付けてくれ。";
		mes "健闘を祈る。";
		delquest 2276;
		setquest 2277;
		set MALAYA_5QUE,11;
		close;
	case 11:
		mes "[警備隊長]";
		mes "まずはどこかにあるであろう";
		mes "ブワヤの住処を探してきてほしい。";
		mes "それらしき場所を見つけたら";
		mes "^3131FF空に向けて煙幕弾を撃ってくれ。^000000";
		mes "その後、我々警備隊員が";
		mes "合図を頼りに向かうようにする。";
		close;
	case 12:
	case 13:
		mes "‐まずはトトイのもとに";
		mes "　エドーを連れていってあげよう‐";
		close;
	case 14:
		mes "[警備隊長]";
		mes "無事に警備隊員からブワヤの住処を";
		mes "伝達してもらったよ。";
		mes "よくやってくれた。";
		next;
		mes "[警備隊長]";
		mes "ブワヤ討伐に向けた戦力調達など";
		mes "課題は色々あるが";
		mes "討伐に向けて大きく一歩前進したよ。";
		next;
		mes "[警備隊長]";
		mes "さあ、これは我々警備隊からの";
		mes "感謝の気持ちだ。";
		mes "ブワヤ退治にも協力してくれるなら";
		mes "いつでも来てくれ。";
		mes "では、また会うことにしよう。";
		if(checkre()) {
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,300000;
		}
		else {
			getexp 5000000,0;
			getexp 5000000,0;
			getexp 0,3000000;
		}
		delquest 2280;
		setquest 201520;
		set MALAYA_5QUE,15;
		close;
	case 15:
		if(checkquest(2281)) {
			if(checkquest(2281) & 0x4) {
				mes "[警備隊長]";
				mes "なに！　ブワヤを本当に倒すとは！";
				mes "素晴らしい。君のおかげで";
				mes "村の住人たちも少しの間";
				mes "安心できるようになった。";
				next;
				mes "[警備隊長]";
				mes "だがまだ油断できない。";
				mes "第2、第3のブワヤが";
				mes "続々目撃報告されているのだ。";
				mes "是非また協力してくれ。";
				next;
				mes "[警備隊長]";
				mes "これは今回の討伐のお礼だ。";
				mes "本当にご苦労だった。ありがとう。";
				delquest 2281;
				getitem 6497,3;
				close;
			}
			mes "[警備隊長]";
			mes "ブワヤ退治の首尾はどうだ？";
			next;
			if(select("諦めます","努力している最中です") == 2) {
				mes "[警備隊長]";
				mes "とても危険な任務なので";
				mes "くれぐれも慎重に進めてほしい。";
				mes "必ず仲間とパーティーを組んで";
				mes "討伐に挑んでくれ。";
				close;
			}
			mes "[警備隊長]";
			mes "そうか。諦めるというのか。";
			mes "ブワヤはとても恐ろしい怪物として";
			mes "知られている。";
			mes "君が恐れをなすのも無理はない。";
			mes "協力する気になってくれたら";
			mes "いつでもまた声をかけてくれ。";
			delquest 2281;
			close;
		}
		mes "[警備隊長]";
		mes "バリオ・フォレストの深い森で";
		mes "ブワヤが発見されたらしい。";
		next;
		if(BaseLevel < 130) {
			mes "[警備隊長]";
			mes "ブワヤはとても恐ろしい怪物だ";
			mes "今の君の手には余るだろう。";
			mes "^FF0000BaseLv130以上^000000になったら";
			mes "また来てくれ。";
			close;
		}
		mes "[警備隊長]";
		mes "知っていると思うが、";
		mes "警備隊は皆、悪霊やモンスターの";
		mes "掃討に総力をあげている。";
		next;
		mes "[警備隊長]";
		mes "その影響によりブワヤの退治には";
		mes "外部の力を借りるしかない状態だ。";
		mes "ブワヤはとても恐ろしい怪物だと";
		mes "伝えられている。";
		mes "討伐にはたくさんの力が必要だ。";
		mes "ブワヤ退治に協力してくれないか？";
		next;
		if(select("協力する","協力しない") == 2) {
			mes "[警備隊長]";
			mes "ブワヤはとても恐ろしい怪物として";
			mes "知られている。";
			mes "君が恐れをなすのも無理はない。";
			mes "協力する気になってくれたら";
			mes "いつでもまた声をかけてくれ。";
			close;
		}
		mes "[警備隊長]";
		mes "そうか。ありがとう！";
		mes "聞いた話によるとブワヤは、";
		mes "背中にある箱で人を捕まえて";
		mes "食べてしまうという恐ろしい怪物だ。";
		next;
		mes "[警備隊長]";
		mes "とても危険な任務なので";
		mes "くれぐれも慎重に進めてほしい。";
		mes "必ず仲間とパーティーを組んで";
		mes "討伐に挑んでくれ。";
		setquest 2281;
		close;
	default:
		mes "[警備隊長]";
		mes "お化けやモンスターへの対応で";
		mes "いま、私たちは忙しいんだ。";
		next;
		mes "[警備隊長]";
		mes "だが、警備は万全の体制で臨んでいる。";
		mes "安心してポートマラヤを楽しんでくれ。";
		close;
	}
}

ma_fild02.gat,307,245,0	script	#todog1	139,3,3,{
	if(MALAYA_5QUE == 11) {
		hideoffnpc "犬#buwaya";
		mes "[どこからか聞こえる音]";
		mes "ワンワン！！";
		close;
	}
	end;
}
ma_fild02.gat,320,241,0	duplicate(#todog1)	#todog2	139,3,3
ma_fild02.gat,317,250,0	duplicate(#todog1)	#todog3	139,3,3

ma_fild02.gat,312,259,3	script	犬#buwaya	81,{
	mes "[犬]";
	mes "ワンワン!!";
	if(MALAYA_5QUE == 11) {
		next;
		mes "‐犬はこちらを見つめながら";
		mes "　懸命に吠えている‐";
		next;
		if(select("犬を調べる","放っておく") == 2) {
			mes "‐犬を横目にこの場を去った‐";
			close;
		}
		mes "‐懸命に吠えている犬を持ち上げると";
		mes "　首輪が目にはいってきた。";
		mes "　";
		mes "　「トトイといつまでも一緒」";
		mes "　と、書かれている‐";
		next;
		menu "まさか、エドー!?",-;
		emotion 33;
		mes "[犬]";
		mes "ワン！";
		mes "クーン。クーン。";
		next;
		mes "‐エドー、と呼ぶこちらの声に";
		mes "　反応して尻尾を大きく振りはじめた‐";
		next;
		mes "[犬]";
		mes "ワンワン!!";
		next;
		mes "‐どうやらエドーは無事だったようだ。";
		mes "　後でトトイに知らせてあげよう‐";
		next;
		emotion 5;
		mes "[エドー]";
		mes "ワン!!　ワワン！";
		mes "ワワワワワン！";
		next;
		emotion 26;
		mes "‐エドーは北へ向き直り";
		mes "　なおも吠え続けている。";
		mes "　何か伝えようとしてるのだろうか‐";
		next;
		menu "もしかして、この先にブワヤが？",-;
		emotion 33;
		mes "[エドー]";
		mes "ワワワンワン！";
		next;
		mes "‐どうやらこの先に、";
		mes "　ブワヤの住処があるようだ。";
		mes "　警備隊に知らせないと‐";
		next;
		mes "‐あなたは";
		mes "　警備隊長から受け取った煙幕弾を";
		mes "　空に向かって勢いよく撃ち上げた‐";
		next;
		mes "^FF0000‐ヒュウウウウウ‐^000000";
		misceffect 709,"";
		hideoffnpc "警備隊員#buwaya";
		next;
		mes "[警備隊員]";
		mes "ご苦労様です！";
		mes "まさかこんな場所に";
		mes "ブワヤが住んでいたとは！";
		mes "早速、警備隊長に伝えておきます！";
		hideonnpc "警備隊員#buwaya";
		next;
		mes "‐無事役目を果たす事が出来た。";
		mes "　まずはトトイのもとに";
		mes "　エドーを連れていってあげよう‐";
		next;
		mes "[エドー]";
		mes "ワンワン!!";
		hideonnpc "犬#buwaya";
		delquest 2277;
		setquest 2278;
		set MALAYA_5QUE,12;
	}
	close;
OnInit:
	hideonnpc "犬#buwaya";
	end;
}

ma_fild02.gat,305,268,3	script	警備隊員#buwaya	570,{
	end;
OnInit:
	hideonnpc "警備隊員#buwaya";
	end;
}

//============================================================
// バコナワの伝説クエストNPC
//- Registry -------------------------------------------------
// MALAYA_6QUE -> 0～7
//------------------------------------------------------------
malaya.gat,280,331,4	script	歌う男	578,{
	if(MALAYA_6QUE < 6) {
		mes "[歌う男]";
		mes "湖に住んでいる龍のお話し～";
		mes "遠い昔龍になってしまった ";
		mes "ある老婆のお話し～";
		next;
		mes "[歌う男]";
		mes "異境に旅立った";
		mes "息子を待ちながら、";
		mes "あの月が90回昇ると";
		mes "私の息子が戻って来る～";
		next;
		mes "[歌う男]";
		mes "月が89回、";
		mes "月が90回、";
		mes "月が190回……";
		next;
		mes "[歌う男]";
		mes "あの月が私の息子を奪ったよ～";
		mes "あの恐ろしいモノが私の息子を";
		mes "飲み込んじまったから、";
		mes "私があの月に罰を与えよう～";
		next;
		mes "[歌う男]";
		mes "月が怒り姿を隠した日";
		mes "すべての地に暴雨が現れて";
		mes "町と人が水の下で死を迎えた～";
		next;
		mes "[歌う男]";
		mes "老婆の呪いで月が怒り～";
		mes "老婆を追い出して月を慰めないと～";
		mes "老婆さえいなければ";
		mes "老婆さえいなければ……";
		next;
		mes "[歌う男]";
		mes "噂が聞こえてくる～";
		mes "老婆が湖に身を投げた～";
		mes "龍になった老婆が月を飲み込んで、";
		mes "その内この町も飲み込むだろう～";
		close;
	}
	mes "[歌う男]";
	mes "バコナワについての伝説は";
	mes "すべて嘘だったと言うのですか？";
	mes "つまりあなたは、私の先祖たちみんなが";
	mes "嘘つきだったと言っているのですね？";
	next;
	mes "[歌う男]";
	mes "ふざけないでください。";
	mes "この町は昔からの歴史の上に";
	mes "建てられています。";
	mes "あなたのような外から来た人間の話で";
	mes "揺さぶられる私たちではありません。";
	mes "帰って下さい。";
	close;
}

malaya.gat,275,333,5	script	歌う女	579,{
	if(MALAYA_6QUE < 6) {
		mes "[歌う女]";
		mes "湖に住んでいるバコナワ、";
		mes "龍になった老婆の話。";
		next;
		mes "[歌う女]";
		mes "月が90回昇ると戻って来ると";
		mes "言っていた息子は";
		mes "月が数百回昇っても戻らなかった～";
		mes "月が老婆の息子を飲み込んだ～";
		next;
		mes "[歌う女]";
		mes "月よ、月よ、老婆の呪いを受け取れ～";
		mes "怒り出した月が降らせた雨と洪水で";
		mes "町のすべてが死の恐怖に飲み込まれた～";
		next;
		mes "[歌う女]";
		mes "月よ、月よ、老婆を追い出したので";
		mes "怒りをおさめてくれ～";
		mes "老婆が湖で死んだ～";
		next;
		mes "[歌う女]";
		mes "バコナワになりお前を飲み込んで、";
		mes "町を罰するためにもうすぐ";
		mes "やって来るだろう～";
		mes "月が死ぬ日が来れば";
		mes "町も一緒に死ぬだろう～";
		close;
	}
	mes "[歌う女]";
	mes "伝説がすべて嘘だと言うんですか？";
	mes "どうしてそんなことが言えるんですか？";
	mes "私たちがずっと信じてきたことを、";
	mes "なぜあなたが簡単に嘘だと";
	mes "言えるのですか？";
	mes "そんなの信じられるわけがありません。";
	next;
	mes "[歌う女]";
	mes "可哀そうなバコナワ……。";
	mes "あなたのような人はバコナワに";
	mes "噛まれればいいのに！";
	close;
}

malaya.gat,290,329,4	script	恐怖に怯えている少年	577,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_6QUE < 6) {
		mes "[恐怖に怯えている少年]";
		mes "恐ろしいバコナワがもうすぐ";
		mes "月を飲み込んで、町に復讐しに";
		mes "来るらしいですよ。";
		mes "怖いです、助けて下さい……。";
		close;
	}
	mes "[恐怖に怯えている少年]";
	mes "バコナワの伝説が";
	mes "全部嘘だと言うんですか？";
	mes "ではバコナワも偽物なんですか？";
	next;
	mes "[恐怖に怯えている少年]";
	mes "それなら後で友達とバコナワの湖に";
	mes "遊びに行きます。";
	mes "大丈夫なんですよね？";
	mes "伝説は嘘だと言いましたよね？";
	close;
}

malaya.gat,264,338,4	script	恐怖に怯えている女性	576,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_6QUE < 6) {
		mes "[恐怖に怯えている女性]";
		mes "バコナワは騒音を嫌うらしいです。";
		mes "助かりたいなら早く鍋を叩いて下さい！";
		next;
		switch(select("騒音を嫌うんですか？","バコナワとは？")) {
		case 1:
			mes "[恐怖に怯えている女性]";
			mes "死んだ老婆がバコナワに";
			mes "成り変わったことは";
			mes "すでにご存知ですか？";
			next;
			mes "[恐怖に怯えている女性]";
			mes "伝説によると老婆は";
			mes "遠くに行った息子を待ちながら";
			mes "常に気を使っていたので";
			mes "音に敏感らしいです。";
			next;
			mes "[恐怖に怯えている女性]";
			mes "それでバコナワも聴覚が";
			mes "とても発達しています。";
			mes "人々が手に鍋や、フライパンなどを";
			mes "叩くのはそのためです。";
			close;
		case 2:
			mes "[恐怖に怯えている女性]";
			mes "湖に住んでいる怖い怪物です。";
			mes "いつ町を襲撃して来るかもしれないので";
			mes "いつも怯えています。";
			next;
			mes "[恐怖に怯えている女性]";
			mes "バコナワは月を飲み込むことに";
			mes "夢中になっているという噂ですので";
			mes "いっそ月を飲み込んで、町のことは";
			mes "忘れてほしいです……。";
			close;
		}
	}
	mes "[恐怖に怯えている女性]";
	mes "町の人たちはあなたの事を";
	mes "嫌っています。";
	mes "バコナワの伝説が嘘だと言って……";
	next;
	mes "[恐怖に怯えている女性]";
	mes "なぜ町の人たちをだまそうとするの？";
	mes "あなたのほうが怪物よりも悪よ！";
	close;
}

malaya.gat,272,339,5	script	老いた占い師	575,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_6QUE < 6) {
		mes "[老いた占い師]";
		mes "バコナワを憎んではいけません。";
		mes "あれに対する憎しみがバコナワの";
		mes "怒りをさらに増幅させているんです。";
		next;
		mes "[老いた占い師]";
		mes "死んだ老婆の恨みを慰めるために";
		mes "毎年この時期になると料理を捧げたり、";
		mes "行事を行っているが、";
		mes "どんどん大きくなっているその怒りを";
		mes "どうしても慰める方法がありません。";
		next;
		mes "[老いた占い師]";
		mes "このままでは危険です。";
		mes "私にはわかります。";
		mes "もうすぐバコナワは月を飲み込んで";
		mes "町を罰しにくるはずです。";
		close;
	}
	mes "[老いた占い師]";
	mes "伝説が嘘！";
	mes "なんというバチ当たりな……";
	next;
	mes "[老いた占い師]";
	mes "ああ、あなたのせいでバコナワの";
	mes "怒りがさらに大きくなった！";
	mes "町が侵略されることになれば、";
	mes "それは全部あなたの責任だ！";
	close;
}

malaya.gat,285,332,4	script	伝説に詳しい老人	574,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(BaseLevel < 120) {
		mes "[伝説に詳しい老人]";
		mes "君は私を手伝うにはまだ";
		mes "力不足のようだな。";
		mes "十分強くなってから";
		mes "もう一度訪ねて来てくれ。";
		next;
		mes "‐^FF0000BaseLv120以上^000000になってから";
		mes "　また来よう‐";
		close;
	}
	switch(MALAYA_6QUE) {
	case 0:
		mes "[伝説に詳しい老人]";
		mes "とうとう怪物バコナワが";
		mes "この町まで報復をしにくる……。";
		mes "バコナワを慰めなくては。";
		mes "これ以上の災いを防ぐために。";
		next;
		if(select("詳しく聞く","その場を離れる") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "[伝説に詳しい老人]";
		mes "ここからずっと東に行ったところに";
		mes "ある湖に、バコナワという怪物が";
		mes "住んでいる。";
		next;
		mes "[伝説に詳しい老人]";
		mes "このバコナワには、私たちの町に";
		mes "古くから伝わる伝説があってな。";
		mes "外から来た者は知らぬだろうから、";
		mes "私が伝説を語って聞かせよう。";
		next;
		mes "[伝説に詳しい老人]";
		mes "今から百年前、旅に出た息子の帰りを";
		mes "待つ老婆がおった。";
		mes "息子は月が90回昇った頃に帰ると";
		mes "言っていたが、数百回月が昇っても";
		mes "帰ってこない。";
		next;
		mes "[伝説に詳しい老人]";
		mes "老婆は思った。";
		mes "息子は月に飲み込まれたのだ、と。";
		mes "老婆は月を呪った。";
		mes "月に仕返しをするため、強く強く";
		mes "呪った。";
		next;
		mes "[伝説に詳しい老人]";
		mes "それを知った月はひどく怒り、";
		mes "姿を隠すと、激しい風雨がこの町と";
		mes "人々を襲った。";
		mes "人々は、月を呪った老婆の存在を知り、";
		mes "老婆を責め、町から追い出そうとした。";
		mes "月の怒りをしずめるためにな。";
		next;
		mes "[伝説に詳しい老人]";
		mes "老婆は絶望し、湖に自ら身を投げた。";
		mes "嵐は治まり、人々は安堵して、";
		mes "話はそれで終わったかに思われた。";
		mes "……しかし、そうではなかったのだ。";
		next;
		mes "[伝説に詳しい老人]";
		mes "老婆は恨みのあまり、バコナワという";
		mes "龍に姿を変えたのだ。";
		mes "月と町と人を食らう龍にな。";
		next;
		mes "[伝説に詳しい老人]";
		mes "……しばらくの間は月を恨み、";
		mes "町の人たちに失望する気持ちしか";
		mes "なかっただろう。";
		mes "しかし、歳月が経つほど恨みは大きく";
		mes "なった。";
		next;
		mes "[伝説に詳しい老人]";
		mes "何のために怪物になったと思う？";
		mes "その長い間、老婆の頭の中を何が";
		mes "支配していたと思う？";
		mes "怒りと復讐だよ。";
		next;
		mes "[伝説に詳しい老人]";
		mes "自分を捨てた月と町に対する";
		mes "忘れる事ができないほどの怨念……。";
		mes "老婆は町の人たちの利己心のせいで";
		mes "残念な死を迎えなければならなかった。";
		mes "だから慰めないといけないんだよ。";
		mes "私たちこの町の人間がね。";
		next;
		menu "どうやって慰める？",-;
		mes "[伝説に詳しい老人]";
		mes "老婆は息子への愛に溢れている人で、";
		mes "ずっと息子の帰りを待っていた。";
		mes "だから、百年前の息子の行方を";
		mes "調べて、その遺品だけでも";
		mes "仏壇に置き魂を慰めれば、";
		mes "きっと静まってくれるはずだ。";
		next;
		mes "‐周辺にいた住民たちが";
		mes "　ざわめいた‐";
		next;
		mes "[町の人たち]";
		mes "そんな無茶な！";
		next;
		mes "[町の人たち]";
		mes "百年も前の人のことを調べるなんて";
		mes "無理です！";
		next;
		mes "[伝説に詳しい老人]";
		mes "もちろん、百年前の人の痕跡を";
		mes "探すというのは無謀かもしれない……。";
		next;
		mes "[伝説に詳しい老人]";
		mes "けれどやってみる価値は";
		mes "あるのではないか？";
		mes "私たちは、老婆の怒りと恨みを";
		mes "慰める方法を探す義務が";
		mes "あるのではないか？";
		next;
		mes "[町の人たち]";
		mes "…………。";
		next;
		mes "[伝説に詳しい老人]";
		mes "……旅の者よ。";
		mes "私たちは私たちの先祖が犯した罪を";
		mes "償わなくてはならない。";
		next;
		mes "[伝説に詳しい老人]";
		mes "しかし、悔しく情けない話ではあるが、";
		mes "私たちにはそのための力がない……。";
		mes "助けてくれ、私達を……。";
		next;
		if(select("力になる","断る") == 2) {
			mes "[伝説に詳しい老人]";
			mes "そう、君の考えていることも正しい。";
			mes "相手は人ではない。";
			mes "怪物なのだから……。";
			mes "それでも私は老婆の心の優しさを";
			mes "信じているのだ。";
			next;
			mes "[伝説に詳しい老人]";
			mes "気が変わったら、";
			mes "また話かけてくれ……。";
			close;
		}
		mes "[伝説に詳しい老人]";
		mes "ありがたい……。";
		mes "それではまず、私の孫娘から";
		mes "^FF0000石版の欠片^000000をもらって来て";
		mes "くれるか？";
		next;
		mes "[伝説に詳しい老人]";
		mes "その^FF0000石版の欠片^000000は、";
		mes "老婆の息子が残した物だ。";
		mes "損傷がひどくて原型を知ることは";
		mes "できないがな。";
		next;
		mes "[伝説に詳しい老人]";
		mes "道に沿って南の方に行くと";
		mes "港近くに私の孫娘がいるから、";
		mes "貰って来てくれ。";
		mes "頼んだぞ。";
		next;
		mes "‐伝説に詳しい老人の孫娘から";
		mes "　^FF0000石版の欠片^000000をもらってこよう。";
		mes "　孫娘は港近くにいるらしい‐";
		set MALAYA_6QUE,1;
		delquest 72078;
		setquest 1174;
		close;
	case 1:
		mes "[伝説に詳しい老人]";
		mes "^FF0000石版の欠片^000000を持って来てくれ";
		mes "道に沿って南の方に行くと";
		mes "港近くに私の孫娘がいるから、";
		mes "もらって来てくれ。";
		next;
		mes "‐伝説に詳しい老人の孫娘から";
		mes "　^FF0000石版の欠片^000000をもらってこよう。";
		mes "　孫娘は港近くにいるらしい‐";
		close;
	case 2:
		mes "[伝説に詳しい老人]";
		mes "無事に石版をもらって来たか。";
		mes "すぐに必要となる物ではないが、";
		mes "老婆の息子の足跡を追う数少ない";
		mes "手がかりの一つだ。";
		mes "なくさない様に大切に持っていてくれ。";
		mes "きっと大きな力になるはずだ。";
		next;
		mes "[伝説に詳しい老人]";
		mes "さて次だが……";
		mes "伝説によると、老婆の息子は";
		mes "片足が不自由で、足を引きずりながら";
		mes "木偶を売るさすらいの商人だった";
		mes "ようだ。";
		next;
		mes "[伝説に詳しい老人]";
		mes "バリオ・フォレストの北西側の";
		mes "端っこに一人で住んでいる男が、";
		mes "老婆の息子が作った木偶を";
		mes "持っているという話がある。";
		next;
		menu "バリオ・フォレスト？",-;
		mes "[伝説に詳しい老人]";
		mes "ここから東に行くと、";
		mes "バリオ・マヒワガという村がある。";
		mes "その北にあるのが、";
		mes "バリオ・フォレストだ。";
		next;
		mes "[伝説に詳しい老人]";
		mes "かなり辺鄙な場所だから、";
		mes "私のような老人に行ける";
		mes "場所ではなくてな……";
		mes "君が行って、話を聞いてきて";
		mes "くれないか？";
		next;
		if(select("引き受ける","断る") == 2) {
			mes "[伝説に詳しい老人]";
			mes "そうか……";
			mes "残念だが、強要はできん……。";
			mes "気が変わったら、また話しかけてくれ。";
			close;
		}
		mes "[伝説に詳しい老人]";
		mes "君は本当に心優しい若者だ……";
		mes "バリオ・フォレストの西側の";
		mes "橋を渡ると、^0000FFポートマラヤ移住民^000000が";
		mes "いるはずだ。";
		mes "私たちのためにすまない……。";
		mes "幸運を祈る。";
		next;
		mes "‐バリオ・フォレストの西の";
		mes "　橋を渡ったところにいる";
		mes "　^0000FFポートマラヤ移住民^000000から、";
		mes "　話を聞いてこよう‐";
		set MALAYA_6QUE,3;
		delquest 1175;
		setquest 1176;
		close;
	case 3:
		mes "[伝説に詳しい老人]";
		mes "バリオ・フォレストの西側の";
		mes "橋を渡ると、^0000FFポートマラヤ移住民^000000が";
		mes "いるはずだ。";
		next;
		menu "バリオ・フォレストへの行き方を聞く",-;
		mes "[伝説に詳しい老人]";
		mes "ここから東に行くと、";
		mes "バリオ・マヒワガという村がある。";
		mes "その北にあるのが、";
		mes "バリオ・フォレストだ。";
		mes "幸運を祈る。";
		next;
		mes "‐バリオ・フォレストの西の";
		mes "　橋を渡ったところにいる";
		mes "　^0000FFポートマラヤ移住民^000000から、";
		mes "　話を聞いてこよう‐";
		close;
	case 4:
	case 5:
		mes "[伝説に詳しい老人]";
		mes "老婆の息子が、商人では";
		mes "なかった可能性がある？";
		mes "むむむ……";
		mes "となると、彼はいったい";
		mes "何者だったのだ？";
		next;
		mes "[伝説に詳しい老人]";
		mes "すまないが、息子がその後向かった";
		mes "バリオ・マヒワガに行って、";
		mes "真実の一片でもいい、";
		mes "見つけてきてくれないか。";
		next;
		mes "[伝説に詳しい老人]";
		mes "バリオ・マヒワガは、";
		mes "この町の東にある。";
		mes "頼んだぞ。";
		close;
	case 6:
		mes "[伝説に詳しい老人]";
		mes "それは本当なのか？";
		mes "怪物バコナワが老婆に化け、";
		mes "伝説をでっち上げていたとは……";
		next;
		mes "[伝説に詳しい老人]";
		mes "今まで……町のすべての住民が";
		mes "あの怪物に踊らされていたのか……";
		next;
		mes "[伝説に詳しい老人]";
		mes "もうためらう理由がなくなった！";
		mes "バコナワが来る前に";
		mes "バコナワの住む湖に行って奴を";
		mes "倒さなければ。";
		mes "君を信じてもいいんだな？";
		next;
		if(select("それは……","もちろんです！") == 1) {
			mes "[伝説に詳しい老人]";
			mes "むむ……";
			mes "まだ不可解なことが";
			mes "残っているのか？";
			next;
			mes "[伝説に詳しい老人]";
			mes "わかった。";
			mes "この結論に自信を持って";
			mes "答えられるようになったら、";
			mes "もう一度話しかけてくれ。";
			next;
			mes "[伝説に詳しい老人]";
			mes "ただな……";
			mes "君は、もう少し自分の";
			mes "探し出した真実に、";
			mes "自信を持って良いと思うぞ。";
			close;
		}
		mes "[伝説に詳しい老人]";
		mes "君がバコナワの湖に";
		mes "出入できるように町長に";
		mes "よく話しておく。";
		mes "必ず怪物を退治してくれ。";
		next;
		if(checkitemblank() == 0) {
			mes "[伝説に詳しい老人]";
			mes "お礼をしようと思ったが、";
			mes "たくさんのアイテムを持っておる";
			mes "ようだな。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてくれ。";
			close;
		}
		if(checkweight(6499,3) == 0) {
			mes "[伝説に詳しい老人]";
			mes "お礼をしようと思ったが、";
			mes "たくさんのアイテムを持っておる";
			mes "ようだな。";
			mes "アイテムの重量を減らしてから";
			mes "もう一度話しかけてくれ。";
			close;
		}
		if(BaseLevel < 140) {
			mes "[伝説に詳しい老人]";
			mes "バコナワは恐ろしい怪物じゃ。";
			mes "万全の準備をしてから挑むのじゃぞ。";
			next;
			mes "‐^FF0000BaseLv140以上^000000になってから";
			mes "　バコナワに挑もう‐";
			next;
		}
		mes "[伝説に詳しい老人]";
		mes "それから、これはお礼だ。";
		mes "私たちのために真実を";
		mes "探し出してくれて、";
		mes "本当にありがとう。";
		set MALAYA_6QUE,7;
		delquest 1179;
		setquest 201525;
		getitem 6499,3;
		if(checkre()) {
			getexp 500000,0;
			getexp 500000,0;
			getexp 0,300000;
		}
		else {
			getexp 5000000,0;
			getexp 5000000,0;
			getexp 0,3000000;
		}
		next;
		mes "[伝説に詳しい老人]";
		mes "ただ……";
		mes "伝説が嘘だったことを";
		mes "受け入れられない者も";
		mes "多くいるだろう。";
		mes "君に心無い言葉を浴びせる者も";
		mes "いるかもしれない。";
		next;
		mes "[伝説に詳しい老人]";
		mes "だが、どうか彼らを許して";
		mes "やってほしい……";
		mes "私たちはずっと、バコナワに";
		mes "深い畏敬の念を抱いて来た。";
		mes "すぐには考えを変えられない";
		mes "者もいる。";
		next;
		mes "[伝説に詳しい老人]";
		mes "彼らには時間が必要なのだ。";
		mes "どうか、君の優しい心で";
		mes "彼らを許してやってくれ……。";
		close;
	case 7:
		if(MALAYA_7QUE < 15) {
			mes "[伝説に詳しい老人]";
			mes "もしよかったら";
			mes "町長を手伝ってくれないか？";
			mes "バコナワのせいでみんな";
			mes "心に余裕をなくしているから……";
			next;
		}
		mes "[伝説に詳しい老人]";
		mes "百年の間";
		mes "信じて来た伝説が";
		mes "すべて嘘だったとは……";
		mes "必ず怪物を退治してくれ。";
		if(BaseLevel < 140) {
			next;
			mes "[伝説に詳しい老人]";
			mes "バコナワは恐ろしい怪物じゃ。";
			mes "万全の準備をしてから挑むのじゃぞ。";
			next;
			mes "‐^FF0000BaseLv140以上^000000になってから";
			mes "　バコナワに挑もう‐";
		}
		close;
	}
OnInit:
	waitingroom "バコナワの伝説",0;
	end;
}

malaya.gat,304,100,4	script	老人の孫娘	576,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	switch(MALAYA_6QUE) {
	case 0:
		mes "[老人の孫娘]";
		mes "お爺ちゃんはバコナワを";
		mes "おとなしくできると";
		mes "信じています。";
		mes "本当にできるんですかね？";
		close;
	case 1:
		mes "[老人の孫娘]";
		mes "^FF0000石版の欠片^000000ですか？";
		mes "お爺ちゃんが持ってこいって？";
		mes "何に使うんだろ……";
		mes "とりあえずお渡ししますね。";
		next;
		mes "‐石版の欠片を手に入れた。";
		mes "　^FF0000伝説に詳しい老人^000000のところに";
		mes "　戻ろう‐";
		set MALAYA_6QUE,2;
		delquest 1174;
		setquest 1175;
		close;
	case 2:
		mes "[老人の孫娘]";
		mes "石版の欠片、ちゃんとお渡し";
		mes "しましたよね？";
		next;
		mes "‐石版の欠片を受け取ったので";
		mes "　^FF0000伝説に詳しい老人^000000のところに";
		mes "　戻ろう‐";
		close;
	default:
		mes "[老人の孫娘]";
		mes "バコナワのせいで";
		mes "町の雰囲気が暗いです。";
		close;
	}
}

ma_fild02.gat,40,240,4	script	ポートマラヤ移住民	578,{
	switch(MALAYA_6QUE) {
	case 3:
		mes "[ポートマラヤ移住民]";
		mes "このような辺鄙な場所まで来るとは";
		mes "すごい方ですね？";
		mes "最近のポートマラヤはどうですか？";
		mes "湖に住んでいる怪物バコナワが";
		mes "町を脅かしているそうで、";
		mes "行けなくて困っています。";
		next;
		mes "[ポートマラヤ移住民]";
		mes "このような辺鄙な場所まで来るとは";
		mes "すごい方ですね？";
		mes "最近のポートマラヤはどうですか？";
		mes "湖に住んでいる怪物バコナワが";
		mes "町を脅かしているそうで、";
		mes "行けなくて困っています。";
		next;
		mes "[ポートマラヤ移住民]";
		mes "木偶を売っていた";
		mes "さすらいの商人ですか？";
		mes "う～ん……";
		mes "商人ではありませんが……。";
		next;
		mes "‐ポートマラヤ移住民は、カバンから";
		mes "　木彫りの人形を取り出した‐";
		next;
		mes "[ポートマラヤ移住民]";
		mes "木偶とはこれのことですか？";
		mes "この木偶については、";
		mes "どのように受け取ったのか、";
		mes "昔聞いたことがあります。";
		next;
		switch(select("木偶を受け取った話を聞く","石版の欠片について知っていることを聞く","さすらいの商人の正体は？")) {
		case 1:
			mes "[ポートマラヤ移住民]";
			mes "百年近く前の出来事ですが、";
			mes "まあ、簡単な話です。";
			next;
			mes "[ポートマラヤ移住民]";
			mes "^0000FF足に大怪我を負い、^000000";
			mes "^0000FF剣を杖替わりにした男が^000000";
			mes "^0000FF家に倒れこんできました。^000000";
			next;
			mes "[ポートマラヤ移住民]";
			mes "^0000FF私の先祖が治療を施したところ、^000000";
			mes "^0000FFお礼にと魔除けの木偶を^000000";
			mes "^0000FF作ってくれたそうです。^000000";
			mes "^0000FFその後その人は、足を引きずり^000000";
			mes "^0000FFながらバリオ・マヒワガに^000000";
			mes "^0000FF向かったとのことです。^000000";
			next;
			menu "バリオ・マヒワガに？",-;
			mes "[ポートマラヤ移住民]";
			mes "伝わって来る話ではそうです。";
			mes "商人ではなく、使い古された、";
			mes "しかしたいそう立派な剣を持った";
			mes "戦士だったと聞いています。";
			mes "ただ、何分昔の話ですからね。";
			mes "真実だとはお約束できません。";
			next;
			mes "‐伝説に詳しい老人の話では、";
			mes "　老婆の息子はさすらいの商人だった。";
			mes "　しかし、ポートマラヤ移住民は";
			mes "　木偶をくれたのは戦士だったという。";
			mes "　話が食い違っているのはなぜだろう‐";
			next;
			mes "‐老婆の息子が向かったという";
			mes "　バリオ・マヒワガで、息子の";
			mes "　正体と行方がわかるかもしれない。";
			mes "　バリオ・マヒワガに行ってみよう‐";
			set MALAYA_6QUE,4;
			delquest 1176;
			setquest 1177;
			close;
		case 2:
			mes "[ポートマラヤ移住民]";
			mes "かなり古い石版ですね。";
			mes "残念ですが、初めて見る物です。";
			mes "何かの文字が書かれてあるみたい";
			mes "ですが、まったく読み取れません。";
			next;
			mes "‐ポートマラヤ移住民は、石版の欠片に";
			mes "　ついては、何も知らないようだ。";
			mes "　木偶について聞いてみよう‐";
			close;
		case 3:
			mes "[ポートマラヤ移住民]";
			mes "う～ん……。";
			mes "はたして彼は商人だったのでしょうか？";
			mes "そのような話はまったく聞いていない";
			mes "ですねぇ……。";
			next;
			mes "[ポートマラヤ移住民]";
			mes "この木偶は、魔除けと聞いています。";
			mes "魔除けのために彼が彫ったと。";
			mes "持っていた商品をくれた、という";
			mes "話は聞いてないですよ。";
			next;
			mes "‐ポートマラヤ移住民は、木偶をくれた";
			mes "　人物について、商人であったとは";
			mes "　聞いていないようだ。";
			mes "　木偶について聞いてみよう‐";
			close;
		}
	case 4:
	case 5:
		mes "[ポートマラヤ移住民]";
		mes "こんにちは。";
		mes "何かご用ですか？";
		next;
		switch(select("木偶を受け取った話を聞く","石版の欠片について知っていることを聞く","さすらいの商人の正体は？")) {
		case 1:
			mes "[ポートマラヤ移住民]";
			mes "それでは、口伝されている話を";
			mes "もう一度ゆっくり聞かせてあげます。";
			mes "よく聞いて下さいね。";
			mes "忘れちゃダメですよ。";
			next;
			mes "[口伝されている話]";
			mes "^0000FF足に大怪我を負い、^000000";
			mes "^0000FF剣を杖替わりにした男が^000000";
			mes "^0000FF家に倒れこんできました。^000000";
			mes "^0000FF私の先祖が治療を施したところ、^000000";
			mes "^0000FFお礼にと魔除けの木偶を^000000";
			mes "^0000FF作ってくれたそうです。^000000";
			next;
			mes "[口伝されている話]";
			mes "^0000FFその後その人は、バリオ・マヒワガに^000000";
			mes "^0000FF向かったとのことです。^000000";
			next;
			mes "‐老婆の息子が向かったという";
			mes "　バリオ・マヒワガで、息子の";
			mes "　正体と行方がわかるかもしれない。";
			mes "　バリオ・マヒワガに行ってみよう‐";
			close;
		case 2:
			mes "[ポートマラヤ移住民]";
			mes "かなり古い石版ですね。";
			mes "残念ですが、初めて見る物です。";
			mes "何かの文字が書かれてあるみたい";
			mes "ですが、まったく読み取れません。";
			next;
			mes "‐ポートマラヤ移住民は、石版の欠片に";
			mes "　ついては、何も知らないようだ‐";
			close;
		case 3:
			mes "[ポートマラヤ移住民]";
			mes "う～ん……";
			mes "はたして彼は商人だったのでしょうか？";
			mes "そのような話はまったく聞いていない";
			mes "ですねぇ……。";
			next;
			mes "[ポートマラヤ移住民]";
			mes "たいそう立派な剣を持った、";
			mes "戦士だったと聞いています。";
			next;
			mes "[ポートマラヤ移住民]";
			mes "それに、この木偶は魔除けのために";
			mes "彼が彫ったと聞いています。";
			mes "持っていた商品をくれた、という";
			mes "話は聞いてないですよ。";
			next;
			mes "‐ポートマラヤ移住民は、木偶をくれた";
			mes "　人物について、商人ではなく、";
			mes "　戦士だったと聞いているようだ‐";
			next;
			mes "‐伝説に詳しい老人の話と";
			mes "　食い違っているのはなぜだろう‐";
			close;
		}
	default:
		mes "[ポートマラヤ移住民]";
		mes "このような辺鄙な場所まで来るとは";
		mes "すごい方ですね？";
		mes "最近のポートマラヤはどうですか？";
		mes "湖に住んでいる怪物バコナワが";
		mes "町を脅かしているそうで、";
		mes "行けなくて困っています。";
		close;
	}
}

ma_fild01.gat,165,237,4	script	ポートマラヤ移住民	582,{
	switch(MALAYA_6QUE) {
	case 4:
		mes "[ポートマラヤ移住民]";
		mes "木偶ですか？";
		mes "木偶にまつわる昔話がありますが……";
		mes "それを聞くために";
		mes "ここまで来たのですか？";
		next;
		if(select("遊びに来た","その昔話を聞かせて下さい") == 1) {
			mes "[ポートマラヤ移住民]";
			mes "そうですか。";
			mes "特に何かある村ではありませんが、";
			mes "のんびりしていってくださいね！";
			close;
		}
		mes "[ポートマラヤ移住民]";
		mes "昔話なので";
		mes "全部は覚えていませんよ？";
		next;
		mes "[昔話]";
		mes "遠い昔、5人の剣客が怪獣バコナワに";
		mes "戦いを挑んだ。";
		mes "巨大なバコナワを相手に、5人は力を";
		mes "合わせて戦い、致命的な傷を与えた。";
		next;
		mes "[昔話]";
		mes "しかし、剣客側も4人が命を落とし、";
		mes "残る1人も足に大怪我を負って、";
		mes "戦うことができなくなった。";
		next;
		mes "[昔話]";
		mes "致命傷を負ったバコナワは、";
		mes "いったん身を隠したのち、";
		mes "人間に化けて剣客を追った。";
		mes "足を怪我した剣客は、バコナワの脅威を";
		mes "遠ざけるための魔除けの木偶を彫った。";
		next;
		mes "[ポートマラヤ移住民]";
		mes "大体このような内容です。";
		mes "ちゃんとした終わりもない……。";
		next;
		mes "[ポートマラヤ移住民]";
		mes "剣客が残していた記録も、";
		mes "この村にあります。";
		mes "なぜポートマラヤではなく、";
		mes "このような遠い所にそれを";
		mes "書いて残したのかは";
		mes "わかりませんが。";
		next;
		menu "その記録という物が見たいです",-;
		mes "[ポートマラヤ移住民]";
		mes "この、目の前にある岩に、";
		mes "記録が残されてあります。";
		mes "しかし、記録の大事な部分が";
		mes "削り取られてしまっているので、";
		mes "内容を確認することは難しいと";
		mes "思います。";
		next;
		mes "‐前にある岩を調査してみよう‐";
		set MALAYA_6QUE,5;
		delquest 1177;
		setquest 1178;
		close;
	case 5:
		mes "[ポートマラヤ移住民]";
		mes "この前にある岩には遠い昔剣客が";
		mes "残した記録が刻まれてあります。";
		next;
		switch(select("剣客のその後について聞く","昔話をもう一度聞く")) {
		case 1:
			mes "[ポートマラヤ移住民]";
			mes "剣客のその後、ですか……。";
			mes "前にも言ったとおり、この昔話は";
			mes "ちゃんとした終わりがありません。";
			mes "剣客のその後も、伝えられていない";
			mes "ので、誰も知らないと思います。";
			close;
		case 2:
			mes "[昔話]";
			mes "遠い昔、5人の剣客が怪獣バコナワに";
			mes "戦いを挑んだ。";
			mes "巨大なバコナワを相手に、5人は力を";
			mes "合わせて戦い、致命的な傷を与えた。";
			next;
			mes "[昔話]";
			mes "しかし、剣客側も4人が命を落とし、";
			mes "残る1人も足に大怪我を負って、";
			mes "戦うことができなくなった。";
			next;
			mes "[昔話]";
			mes "致命傷を負ったバコナワは、";
			mes "いったん身を隠したのち、";
			mes "人間に化けて剣客を追った。";
			mes "足を怪我した剣客は、バコナワの脅威を";
			mes "遠ざけるための魔除けの木偶を彫った。";
			close;
		}
	case 6:
	case 7:
		mes "[ポートマラヤ移住民]";
		mes "昔話がまた聞きたいんですか？";
		mes "何回でもお話ししますよ！";
		next;
		mes "[昔話]";
		mes "遠い昔、5人の剣客が怪獣バコナワに";
		mes "戦いを挑んだ。";
		mes "巨大なバコナワを相手に、5人は力を";
		mes "合わせて戦い、致命的な傷を与えた。";
		next;
		mes "[昔話]";
		mes "しかし、剣客側も4人が命を落とし、";
		mes "残る1人も足に大怪我を負って、";
		mes "戦うことができなくなった。";
		next;
		mes "[昔話]";
		mes "致命傷を負ったバコナワは、";
		mes "いったん身を隠したのち、";
		mes "人間に化けて剣客を追った。";
		mes "足を怪我した剣客は、バコナワの脅威を";
		mes "遠ざけるための魔除けの木偶を彫った。";
		close;
	default:
		mes "[ポートマラヤ移住民]";
		mes "もしかしてポートマラヤから";
		mes "来たのですか？";
		mes "ポートマラヤのことが";
		mes "気になるのですが、モンスターが";
		mes "あちこちにいるのでなかなか";
		mes "行くことができません。";
		close;
	}
}

ma_fild01.gat,172,233,1	script	岩	844,{
	if(MALAYA_6QUE < 5) {
		mes "‐文字らしきものが刻まれた岩がある。";
		mes "　しかし、大事な部分が欠けていて";
		mes "　読み取ることができない‐";
		close;
	}
	else if(MALAYA_6QUE == 5) {
		mes "‐文字らしきものが刻まれた岩がある。";
		mes "　しかし、大事な部分が欠けていて";
		mes "　読み取ることができない‐";
		next;
		mes "‐持ってきた石版の欠片を";
		mes "　岩のへこみに埋め込んでみると、";
		mes "　パズルのピースのようにはまった。";
		mes "　なんとか内容を読むことができる‐";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "バコナワとの戦いで致命傷をうけ、";
		mes "ここまで来ることになった。";
		mes "今の私ができることは、";
		mes "奴が現れそうな所に木偶を";
		mes "置くことしかない。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "^0000FFバコナワ^000000が私を殺すために";
		mes "^0000FF子供や老婆に化け^000000探している。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "奴も致命的な負傷をしているから、";
		mes "月の力を吸収し、本来の力を取り戻す";
		mes "には、百年近い時間がかかるだろう。";
		mes "月が消える日は警戒するように。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "今後、再びバコナワが暴れる日が";
		mes "来るだろう。";
		mes "しかし、百年という時間は";
		mes "十分であろう。";
		mes "私より優れた誰かが";
		mes "必ず奴を倒してくれる。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "遠い未来の彼らを信じている。";
		next;
		mes "‐「老婆」は、剣客に復讐しようと";
		mes "　していたバコナワが化けたもの";
		mes "　であり、「足の悪い息子」は、";
		mes "　本当はバコナワを倒そうとした";
		mes "　剣客の一人だったようだ‐";
		next;
		mes "‐老婆に化けたバコナワが、";
		mes "　剣客に復讐するために流した嘘が、";
		mes "　ポートマラヤで長い間伝説として";
		mes "　口伝されてきていたのだ‐";
		next;
		mes "‐バコナワはただの凶暴な怪獣に";
		mes "　過ぎないことを知った。";
		mes "　ポートマラヤの^0000FF伝説に詳しい老人^000000に";
		mes "　急いでこの事実を知らせよう‐";
		set MALAYA_6QUE,6;
		delquest 1178;
		setquest 1179;
		close;
	}
	else if(MALAYA_6QUE >= 6) {
		mes "‐百年前、剣客が刻んだ";
		mes "　記録がある‐";
		next;
		if(select("もう読まない","もう一度読んでみる") == 1) {
			if(MALAYA_6QUE == 6) {
				mes "‐内容は十分に記憶している。";
				mes "　ポートマラヤの^0000FF伝説に詳しい老人^000000に";
				mes "　調べた事を伝えよう‐";
				close;
			}
			mes "‐内容は十分に記憶している‐";
			close;
		}
		mes "[百年前に剣客が書き込んだ内容]";
		mes "バコナワとの戦いで致命傷をうけ、";
		mes "ここまで来ることになった。";
		mes "今の私ができることは、";
		mes "奴が現れそうな所に木偶を";
		mes "置くことしかない。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "^0000FFバコナワ^000000が私を殺すために";
		mes "^0000FF子供や老婆に化け^000000探している。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "奴も致命的な負傷をしているから、";
		mes "月の力を吸収し、本来の力を取り戻す";
		mes "には、百年近い時間がかかるだろう。";
		mes "月が消える日は警戒するように。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "今後、再びバコナワが";
		mes "暴れる日が来るだろう。";
		mes "しかし、百年という時間は";
		mes "十分であろう。";
		mes "私より優れた誰かが";
		mes "必ず奴を倒してくれる。";
		next;
		mes "[百年前に剣客が書き込んだ内容]";
		mes "遠い未来の彼らを信じている。";
		if(MALAYA_6QUE == 6) {
			next;
			mes "‐「老婆」は、剣客に復讐しようと";
			mes "　していたバコナワが化けたもの";
			mes "　であり、「足の悪い息子」は、";
			mes "　本当はバコナワを倒そうとした";
			mes "　剣客の一人だったようだ‐";
			next;
			mes "‐老婆に化けたバコナワが、";
			mes "　剣客に復讐するために流した嘘が、";
			mes "　ポートマラヤで長い間伝説として";
			mes "　口伝されてきていたのだ‐";
			next;
			mes "‐バコナワはただの凶暴な怪獣に";
			mes "　過ぎないことを知った。";
			mes "　ポートマラヤの^0000FF伝説に詳しい老人^000000に";
			mes "　急いでこの事実を知らせよう‐";
		}
		close;
	}
}

//============================================================
// 消えた住民とバコナワクエストNPC
//- Registry -------------------------------------------------
// MALAYA_7QUE -> 0～15
//------------------------------------------------------------
malaya.gat,286,269,4	script	激憤している男	578,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	mes "[激憤している男]";
	mes "バコナワの犠牲になった人が";
	mes "何人いるか知っていますか？";
	mes "私ひとりだけでも戦います！";
	close;
}

malaya.gat,276,269,5	script	落ち着いている少女	579,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	mes "[落ち着いている少女]";
	mes "バコナワに立ち向かうのは";
	mes "とても危険です。";
	mes "もし怒りを買うと、子供や老人まで";
	mes "危険になります。";
	close;
}

malaya.gat,276,262,4	script	激憤している少年	577,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	mes "[激憤している少年]";
	mes "バコナワにお父さんと友達を";
	mes "奪われました……。";
	mes "必ず復讐します！";
	close;
}

malaya.gat,283,265,4	script	町長	580,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(BaseLevel < 120) {
		mes "[町長]";
		mes "助けが必要な状況ですが";
		mes "あなたではまだ力不足のようです。";
		mes "十分強くなってから";
		mes "もう一度来てください。";
		next;
		mes "‐^FF0000BaseLv120以上^000000になってから";
		mes "　また来よう‐";
		close;
	}
	switch(MALAYA_7QUE) {
	case 0:
		if(MALAYA_6QUE == 0) {
			mes "[町長]";
			mes "バコナワに立ち向かうべきなのか、";
			mes "これまで通り、貢物を納め、";
			mes "祀るべきなのか……";
			mes "非常に悩んでいます。";
			next;
			mes "[町長]";
			mes "バコナワはご存知ですか？";
			mes "月を食うと言われている龍です。";
			mes "この町に伝わるバコナワの";
			mes "伝説を知りたい場合には、";
			mes "^FF0000伝説に詳しい老人^000000から話を";
			mes "聞くといいでしょう。";
			next;
			mes "[町長]";
			mes "最近、住民の失踪事件が連続して";
			mes "発生しておりまして……";
			mes "町の人々の間では、バコナワに";
			mes "襲われたのではないか、と噂されて";
			mes "いるのです。";
		}
		else if(MALAYA_6QUE == 7) {
			mes "[町長]";
			mes "伝説がすべて嘘？";
			mes "怪物に町の人たちみんなが";
			mes "踊らされたようですね……。";
			next;
			mes "[町長]";
			mes "最近、住民の失踪事件が連続して";
			mes "発生しておりまして……";
			mes "町の人々の間では、バコナワに";
			mes "襲われたのではないか、と";
			mes "噂されています。";
		}
		else {
			mes "[町長]";
			mes "バコナワに立ち向かうべきなのか、";
			mes "これまで通り、貢物を納め、";
			mes "祀るべきなのか……";
			mes "非常に悩んでいます。";
			next;
			mes "[町長]";
			mes "というのも、最近、住民の失踪事件が";
			mes "連続して発生しておりまして……";
			mes "町の人々の間では、バコナワに";
			mes "襲われたのではないか、と噂されて";
			mes "いるのです。";
		}
		next;
		mes "[町長]";
		mes "ただ、本当にバコナワにやられたのか、";
		mes "それとも単純な失踪なのかを";
		mes "判断することができません。";
		next;
		mes "[町長]";
		mes "そこでお願いなのですが……";
		mes "バリオ・マヒワガの周辺で";
		mes "失踪者たちの所持品が頻繁に";
		mes "発見されています。";
		next;
		mes "[町長]";
		mes "^0000FF失踪者の所持品^000000を";
		mes "見かけたという場所を教えますので、";
		mes "それを見つけ出し、失踪者の家族に";
		mes "渡していただけないでしょうか？";
		next;
		if(select("断る","引き受ける") == 1) {
			mes "[町長]";
			mes "確かにあなたに頼むのは";
			mes "間違っているのかもしれない……。";
			mes "ただ、我々では力が足りないのです。";
			mes "気が変わったら、もう一度話しかけて";
			mes "ください。";
			mes "お願いします。";
			close;
		}
		mes "[町長]";
		mes "ありがとうございます。";
		mes "所持品を探して欲しい失踪者は";
		mes "4人います。";
		next;
		mes "[町長]";
		mes "^0000FF失踪者の所持品^000000を";
		mes "見かけたという場所を教えますね。";
		mes "見つけたらまずは";
		mes "^0000FF失踪した青年の父親^000000に";
		mes "渡してください。";
		next;
		mes "‐町長から、失踪者の所持品が";
		mes "　見かけられた場所を聞いた。";
		mes "　バリオ・マヒワガに行って";
		mes "　探してみよう‐";
		set MALAYA_7QUE,1;
		delquest 72080;
		setquest 1180;
		close;
	case 1:
		mes "[町長]";
		mes "バリオ・マヒワガで";
		mes "^FF0000失踪者の所持品^000000を見つけ出して";
		mes "^0000FF失踪した青年の父親^000000に";
		mes "渡してください。";
		close;
	case 2:
		mes "[町長]";
		mes "バリオ・マヒワガで";
		mes "^FF0000失踪者の所持品^000000を見つけ出して";
		mes "^0000FF失踪した少女の友達^000000に";
		mes "渡してください。";
		close;
	case 3:
		mes "[町長]";
		mes "バリオ・マヒワガで";
		mes "^FF0000失踪者の所持品^000000を見つけ出して";
		mes "^0000FF失踪した男性の息子^000000に";
		mes "渡してください。";
		close;
	case 4:
		mes "[町長]";
		mes "バリオ・マヒワガで";
		mes "^FF0000失踪者の所持品^000000を見つけ出して";
		mes "^0000FF失踪した少年の母親^000000に";
		mes "渡してください。";
		close;
	case 5:
		mes "[町長]";
		mes "あなたが届けてくれた失踪者の所持品を";
		mes "調べてみたところ、いずれも";
		mes "巨大な生物に襲われた痕跡が";
		mes "ありました……。";
		next;
		mes "[町長]";
		mes "失踪者たちは全員バコナワに";
		mes "やられたに違いありません。";
		next;
		mes "‐周辺にいた住民たちが";
		mes "　どよめいた‐";
		next;
		mes "[町の人たち]";
		mes "バコナワを退治しよう！";
		mes "私たちの手で怪物を退治しよう！";
		next;
		mes "[町長]";
		mes "これ以上バコナワを慰める行事を";
		mes "行うことは無意味ですね……。";
		next;
		mes "[町長]";
		mes "そうだ。";
		mes "若い占い師が、「月の様子が怪しい」";
		mes "「あなたの助けが必要だ」と";
		mes "言っていました。";
		mes "話を聞きに行ってもらえますか？";
		next;
		if(checkitemblank() == 0) {
			mes "[町長]";
			mes "失踪者の所持品を届けてくれた";
			mes "お礼をしようと思いましたが、";
			mes "アイテムの種類数が多すぎるようです。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "[町長]";
		mes "これは失踪者の所持品を";
		mes "届けてくれたお礼です。";
		mes "我々は、バコナワと戦うための";
		mes "準備を進めておきます。";
		set MALAYA_7QUE,6;
		delquest 1184;
		setquest 1185;
		getitem 12700,5;
		close;
	case 6:
		mes "[町長]";
		mes "若い占い師が、「月の様子が怪しい」";
		mes "「あなたの助けが必要だ」と";
		mes "言っていました。";
		mes "話を聞きに行ってもらえますか？";
		close;
	case 7:
		mes "[町長]";
		mes "遠い昔、月が消えた時に恐ろしいことが";
		mes "沢山起きたということです。";
		mes "どうかあなたの力で、早く月が";
		mes "力を取り戻せますように……";
		close;
	case 8:
		mes "[町長]";
		mes "占い師の手助けをしてくれたのですね。";
		mes "ありがとうございます。";
		mes "彼女が必要としている物は、";
		mes "町の者に届けさせましょう。";
		next;
		mes "[町長]";
		mes "それより、今すぐに処理しなければ";
		mes "ならないことがあります。";
		next;
		mes "[町長]";
		mes "バコナワがいつ町を襲撃して来るかも";
		mes "知れないので、町の入口と洞窟近くに";
		mes "落とし穴を設置しなければなりません。";
		mes "そのお手伝いをあなたにお願いしたい";
		mes "と思っています。";
		next;
		mes "[町長]";
		mes "落とし穴を設置する場所の近くに";
		mes "作業員たちを配置しておきました。";
		mes "落とし穴は5か所、順番に1か所ずつ";
		mes "回って、落とし穴を作って";
		mes "いただけませんか？";
		next;
		if(select("断る","引き受ける") == 1) {
			mes "[町長]";
			mes "何から何まであなたに頼りきりで、";
			mes "情けないのですが……";
			mes "どうか力を貸してください。";
			mes "気が変わりましたら、";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "[町長]";
		mes "最初の落とし穴は、町の入口近く";
		mes "バリオ・マヒワガの周辺に設置する";
		mes "予定です。";
		mes "^0000FF無口な作業員^000000を待機させておいたので";
		mes "困ったら彼に話かけてください。";
		set MALAYA_7QUE,9;
		delquest 1187;
		setquest 1188;
		close;
	case 9:
		mes "[町長]";
		mes "最初の落とし穴は、町の入口近く";
		mes "バリオ・マヒワガの周辺に設置する";
		mes "予定です。";
		mes "^0000FF無口な作業員^000000を待機させて";
		mes "おいたので、彼に話かけてください。";
		close;
	case 10:
		mes "[町長]";
		mes "二番目の落とし穴は";
		mes "バリオ・マヒワガから";
		mes "バコナワの湖に繋がる場所の近くに";
		mes "設置するのがよさそうです。";
		mes "そこに^0000FF不満そうな作業員^000000がいるので";
		mes "力になれると思います。";
		close;
	case 11:
		mes "[町長]";
		mes "三番目の落とし穴は";
		mes "バコナワ湖の入口に";
		mes "設置しようと思います。";
		mes "^0000FF腰抜け作業員^000000がいるので";
		mes "力になれると思います。";
		close;
	case 12:
		mes "[町長]";
		mes "四番目の落とし穴も、";
		mes "バコナワ湖の入口に";
		mes "設置しようと思います。";
		mes "そこに^0000FF憂鬱な作業員^000000がいるので";
		mes "力になれると思います。";
		close;
	case 13:
		mes "[町長]";
		mes "五番目の落とし穴も、";
		mes "バコナワ湖の入口に";
		mes "設置した方がよさそうです。";
		mes "^0000FF感激している作業員^000000がいるので";
		mes "力になれると思います。";
		close;
	case 14:
		mes "[町長]";
		mes "落とし穴の設置がすべて";
		mes "終わったようですね。";
		mes "こちらもちょうどバコナワに関する";
		mes "会議を終えました。";
		next;
		mes "[町長]";
		mes "我々は、バコナワに立ち向かうことに";
		mes "決めました。";
		mes "あなたも奴の住む湖に突入して";
		mes "なにとぞ私たちに力を貸してください。";
		next;
		if(checkitemblank() == 0) {
			mes "[町長]";
			mes "これまでのお礼を、と思いましたが、";
			mes "アイテムの種類数が多すぎるようです。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "[町長]";
		mes "これは、少ないですが、";
		mes "これまで協力してくれたお礼です。";
		mes "どうぞお納めください。";
		set MALAYA_7QUE,15;
		delquest 1193;
		setquest 201530;
		if(checkre()) {
			for(set '@i,0;'@i<6;set '@i,'@i+1)
				getexp 500000,0;
			for(set '@i,0;'@i<2;set '@i,'@i+1)
				getexp 0,500000;
		}
		else {
			for(set '@i,0;'@i<6;set '@i,'@i+1)
				getexp 5000000,0;
			for(set '@i,0;'@i<2;set '@i,'@i+1)
				getexp 0,5000000;
		}
		getitem 6497,5;
		if(BaseLevel < 140) {
			next;
			mes "[町長]";
			mes "ただバコナワの力は非常に強力です。";
			mes "今のあなたの力で立ち向かうには";
			mes "少し厳しいでしょう。";
			mes "バコナワに挑む前に、";
			mes "もう少し力をつけてください。";
			next;
			mes "‐^FF0000BaseLv140以上^000000になってから";
			mes "　バコナワに挑もう‐";
		}
		close;
	case 15:
		if(MALAYA_6QUE < 7) {
			mes "[町長]";
			mes "バコナワの住む湖への突入は";
			mes "もう少し先です。";
			mes "余裕があるうちに^0000FF伝説に詳しい老人^000000の";
			mes "手助けをしていただけませんか？";
			mes "きっと、あなたの力を必要と";
			mes "していると思います。";
			close;
		}
		mes "[町長]";
		mes "バコナワ湖にいるタホーが、";
		mes "バコナワの棲み処に行くために";
		mes "協力してくれるでしょう。";
		next;
		if(BaseLevel < 140) {
			mes "[町長]";
			mes "ただバコナワの力は非常に強力です。";
			mes "今のあなたの力で立ち向かうには";
			mes "少し厳しいでしょう。";
			mes "バコナワに挑む前に、";
			mes "もう少し力をつけてください。";
			next;
			mes "‐^FF0000BaseLv140以上^000000になってから";
			mes "　バコナワに挑もう‐";
			close;
		}
		mes "[町長]";
		mes "今までの犠牲者たちのためにも";
		mes "バコナワを必ず退治してください。";
		close;
	}
OnInit:
	waitingroom "消えた住民とバコナワ",0;
	end;
}

ma_fild01.gat,69,180,0	script	茂み#01	844,{
	if(MALAYA_7QUE == 1) {
		if(checkquest(72225) & 0x8) {
			mes "‐失踪者の所持品を";
			mes "　失踪した青年の父親に早く届けよう‐";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐アイテムの種類数が多くて";
			mes "　持つことができない。";
			mes "　種類数を減らしてから拾おう‐";
			close;
		}
		mes "‐茂みの中から";
		mes "　失踪者の所持品を見つけた‐";
		getitem 6520,1;
		setquest 72225;
		compquest 72225;
		close;
	}
	end;
}

ma_fild01.gat,44,69,0	script	茂み#02	844,{
	if(MALAYA_7QUE == 2) {
		if(checkquest(72230) & 0x8) {
			mes "‐失踪者の所持品を";
			mes "　失踪した少女の友達に早く届けよう‐";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐アイテムの種類数が多くて";
			mes "　持つことができない。";
			mes "　種類数を減らしてから拾おう‐";
			close;
		}
		mes "‐茂みの中から";
		mes "　失踪者の所持品を見つけた‐";
		getitem 6520,1;
		setquest 72230;
		compquest 72230;
		close;
	}
	end;
}

ma_fild01.gat,173,94,0	script	茂み#03	844,{
	if(MALAYA_7QUE == 3) {
		if(checkquest(72235) & 0x8) {
			mes "‐失踪者の所持品を";
			mes "　失踪した男性の息子に早く届けよう‐";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐アイテムの種類数が多くて";
			mes "　持つことができない。";
			mes "　種類数を減らしてから拾おう‐";
			close;
		}
		mes "‐茂みの中から";
		mes "　失踪者の所持品を見つけた‐";
		getitem 6520,1;
		setquest 72235;
		compquest 72235;
		close;
	}
	end;
}

ma_fild01.gat,294,94,0	script	茂み#04	844,{
	if(MALAYA_7QUE == 4) {
		if(checkquest(72240) & 0x8) {
			mes "‐失踪者の所持品を";
			mes "　失踪した少年の母親に早く届けよう‐";
			close;
		}
		if(checkitemblank() == 0) {
			mes "‐アイテムの種類数が多くて";
			mes "　持つことができない。";
			mes "　種類数を減らしてから拾おう‐";
			close;
		}
		mes "‐茂みの中から";
		mes "　失踪者の所持品を見つけた‐";
		getitem 6520,1;
		setquest 72240;
		compquest 72240;
		close;
	}
	end;
}

malaya.gat,269,267,5	script	失踪した青年の父親	582,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_7QUE == 1) {
		if(checkquest(72225) & 0x8) {
			mes "‐失踪した青年の父親に";
			mes "　^FF0000失踪者の所持品^000000を渡した‐";
			next;
			mes "[失踪した青年の父親]";
			mes "これは……息子が持っていたもので";
			mes "間違いありません。";
			mes "息子は怪物に……。";
			next;
			mes "‐男は涙を我慢している……‐";
			next;
			mes "‐失踪者たちの所持品探しを続けよう。";
			mes "　バリオ・マヒワガで";
			mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
			mes "　^0000FF失踪した少女の友達^000000に渡そう‐";
			delitem 6520,1;
			set MALAYA_7QUE,2;
			delquest 72225;
			delquest 1180;
			setquest 1181;
			close;
		}
		mes "[失踪した青年の父親]";
		mes "^FF0000失踪者の所持品^000000を探している？";
		mes "もしかして……";
		mes "うちの子はもう帰ってこないと";
		mes "言いたいんですか？";
		close;
	}
	else if(MALAYA_7QUE >= 2) {
		mes "[失踪した青年の父親]";
		mes "可哀そうな……私の子供……";
		next;
		mes "‐男は涙を必死に我慢している……‐";
		if(MALAYA_7QUE != 2)
			close;
		next;
		mes "‐失踪者たちの所持品探しを続けよう。";
		mes "　バリオ・マヒワガで";
		mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
		mes "　^0000FF失踪した少女の友達^000000に渡そう‐";
		close;
	}
	mes "[失踪した青年の父親]";
	mes "お願いです、うちの子供を";
	mes "探してください。";
	mes "バコナワにやられたとは思えません。";
	mes "きっとどこかにいるはずです。";
	close;
}

malaya.gat,265,274,5	script	失踪した少女の友達	577,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_7QUE == 2) {
		if(checkquest(72230) & 0x8) {
			mes "‐失踪した少女の友達に";
			mes "　^FF0000失踪者の所持品^000000を渡した‐";
			next;
			mes "[失踪した少女の友達]";
			mes "これは僕がプレゼントした";
			mes "オモチャだけど……";
			mes "僕の友達はどこにいるの？";
			mes "連れて来てよ、早く連れて来てよ！";
			next;
			mes "‐友達を失った子供が泣いている‐";
			next;
			mes "‐失踪者たちの所持品探しを続けよう。";
			mes "　バリオ・マヒワガで";
			mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
			mes "　^0000FF失踪した男性の息子^000000に渡そう‐";
			delitem 6520,1;
			set MALAYA_7QUE,3;
			delquest 72230;
			delquest 1181;
			setquest 1182;
			close;
		}
		mes "[失踪した少女の友達]";
		mes "^FF0000失踪者の所持品^000000を";
		mes "探しているの？";
		mes "僕の友達は帰ってくるよ！";
		close;
	}
	else if(MALAYA_7QUE >= 3) {
		mes "[失踪した少女の友達]";
		mes "僕の友達を連れて来て。";
		mes "早く連れて来てよ……";
		mes "僕の友達は生きているよ。";
		mes "もう帰ってこないなんて嘘だ！";
		next;
		mes "‐友達を失った子供が泣いている‐";
		if(MALAYA_7QUE != 3)
			close;
		next;
		mes "‐失踪者たちの所持品探しを続けよう。";
		mes "　バリオ・マヒワガで";
		mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
		mes "　^0000FF失踪した男性の息子^000000に渡そう‐";
		close;
	}
	mes "[失踪した少女の友達]";
	mes "僕の友達を探して！";
	mes "一緒にボール遊びをしていたのに";
	mes "急にいなくなったんだ……。";
	close;
}

malaya.gat,270,278,4	script	失踪した男性の息子	578,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_7QUE == 3) {
		if(checkquest(72235) & 0x8) {
			mes "‐失踪した男性の息子に";
			mes "　^FF0000失踪者の所持品^000000を渡した‐";
			next;
			mes "[失踪した男性の息子]";
			mes "これは確かにお父さんのだけど……";
			mes "まさか……お父さん！";
			next;
			mes "‐男は泣き出した……‐";
			next;
			mes "‐失踪者たちの所持品探しを続けよう。";
			mes "　バリオ・マヒワガで";
			mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
			mes "　^0000FF失踪した少年の母親^000000に渡そう‐";
			delitem 6520,1;
			set MALAYA_7QUE,4;
			delquest 72235;
			delquest 1182;
			setquest 1183;
			close;
		}
		mes "[失踪した男性の息子]";
		mes "お父さんの所持品を探して";
		mes "いるのですか？";
		mes "どうしてお父さんではなく所持品を……";
		mes "お父さんは生きているはずです！";
		mes "お父さんを探してください！";
		close;
	}
	else if(MALAYA_7QUE >= 4) {
		mes "[失踪した男性の息子]";
		mes "どうしてこんなことに……";
		next;
		mes "‐男は泣いている……‐";
		if(MALAYA_7QUE != 4)
			close;
		next;
		mes "‐失踪者たちの所持品探しを続けよう。";
		mes "　バリオ・マヒワガで";
		mes "　^FF0000失踪者の所持品^000000を見つけ出し、";
		mes "　^0000FF失踪した少年の母親^000000に渡そう‐";
		close;
	}
	mes "[失踪した男性の息子]";
	mes "お父さんがバコナワに殺されて";
	mes "しまったなんて、信じられません。";
	mes "お父さんを探してください！";
	close;
}

malaya.gat,265,284,4	script	失踪した少年の母親	579,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_7QUE == 4) {
		if(checkquest(72240) & 0x8) {
			mes "‐失踪した少年の母親に";
			mes "　^FF0000失踪者の所持品^000000を渡した‐";
			next;
			mes "[失踪した少年の母親]";
			mes "これはうちの子のブラシだけど……";
			mes "あなたがどうして……？";
			mes "……怪物に……襲われた？";
			next;
			mes "[失踪した少年の母親]";
			mes "あ……";
			mes "うちの子の声が聞こえる……";
			mes "うちの子が戻ってくる前に";
			mes "家に帰らないと。";
			mes "お腹を空かしているだろうから";
			mes "ご飯の用意をしておかなくちゃ……。";
			next;
			mes "‐母親は精神的なショックを";
			mes "　受けてしまったようだ……‐";
			next;
			mes "‐失踪者の所持品探しを終えたので";
			mes "　町長に報告しよう‐";
			delitem 6520,1;
			set MALAYA_7QUE,5;
			delquest 72240;
			delquest 1183;
			setquest 1184;
			close;
		}
		mes "[失踪した少年の母親]";
		mes "うちの子の所持品を探している？";
		mes "どういうことですか？";
		mes "うちの子はもう帰ってこないと";
		mes "いうことですか？";
		close;
	}
	else if(MALAYA_7QUE >= 5) {
		mes "[失踪した少年の母親]";
		mes "うちの子の声が聞こえます。";
		mes "耳をすませてみてください。";
		mes "お母さんと呼んでいる声が";
		mes "聞こえますよね？";
		if(MALAYA_7QUE != 5)
			close;
		next;
		mes "‐母親は精神的なショックを";
		mes "　受けてしまったようだ……‐";
		next;
		mes "‐失踪者の所持品探しを終えたので";
		mes "　町長に報告しよう‐";
		close;
	}
	mes "[失踪した少年の母親]";
	mes "うちの子を探してください。";
	mes "近くまで買い物を頼んだのに";
	mes "まだ帰って来ないんです……";
	close;
}

malaya.gat,289,364,4	script	若い占い師	583,{
	if(MALAYA_1QUE < 6) {
		mes "‐あなたを警戒している‐";
		close;
	}
	if(MALAYA_7QUE == 6) {
		mes "[若い占い師]";
		mes "この数日の間に、";
		mes "月の力が弱まっています。";
		mes "町の近くでモンスターが増えたのも、";
		mes "バコナワの犠牲者が増えたのも";
		mes "そのせいです。";
		next;
		mes "[若い占い師]";
		mes "モンスターたちの血を捧げ";
		mes "月の力を戻す儀式を行うので、";
		mes "バリオ・マヒワガの周辺にいる";
		mes "^FF0000ティクバラン^000000を15匹";
		mes "退治してください。";
		next;
		if(select("断る","引き受ける") == 1) {
			mes "[若い占い師]";
			mes "ご迷惑だということは承知しています。";
			mes "ですが、私たちはあなたに";
			mes "お願いするしかありません……。";
			mes "力を貸していただけないでしょうか？";
			mes "気が変わりましたら、";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "[若い占い師]";
		mes "ありがとうございます。";
		mes "では、申し訳ありませんが、";
		mes "急いでいただけますか？";
		mes "このまま完全に月が姿を隠して";
		mes "しまったら大きな災いが起きます。";
		set MALAYA_7QUE,7;
		delquest 1185;
		setquest 1186;
		close;
	}
	else if(MALAYA_7QUE == 7) {
		if(checkquest(1186) & 0x4) {
			mes "[若い占い師]";
			mes "^FF0000ティクバラン^000000を退治した";
			mes "ようですね。";
			mes "これで儀式を始められます。";
			next;
			if(checkitemblank() == 0) {
				mes "[若い占い師]";
				mes "お礼を、と思いましたが、";
				mes "アイテムの種類数が多すぎるようです。";
				mes "アイテムの種類数を減らしてから";
				mes "もう一度話しかけてください。";
				close;
			}
			mes "[若い占い師]";
			mes "これはお礼です。";
			mes "必要な品物があるので、町長様に";
			mes "報告をしていただけますか？";
			set MALAYA_7QUE,8;
			delquest 1186;
			setquest 1187;
			getitem 12699,5;
			close;
		}
		mes "[若い占い師]";
		mes "バリオ・マヒワガの周辺にいる";
		mes "^FF0000 ティクバラン^000000を15匹";
		mes "退治してください。";
		next;
		mes "[若い占い師]";
		mes "急いでください。";
		mes "このまま完全に月が姿を隠して";
		mes "しまったら大きな災いが起きます。";
		close;
	}
	else if(MALAYA_7QUE == 8) {
		mes "[若い占い師]";
		mes "これで儀式を始められます。";
		mes "必要な品物があるので、町長様に";
		mes "報告をしていただけますか？";
		close;
	}
	else if(MALAYA_7QUE >= 9) {
		mes "[若い占い師]";
		mes "月が完全に姿を隠す日、";
		mes "龍が町を襲撃するでしょう。";
		mes "多くの犠牲者がでるはずです。";
		close;
	}
	mes "[若い占い師]";
	mes "月の力が弱まっています。";
	mes "町の近くでモンスターが増えたのも、";
	mes "バコナワの犠牲者が増えたのも、";
	mes "そのせいです。";
	close;
}

ma_fild01.gat,54,253,4	script	無口な作業員	582,{
	if(MALAYA_7QUE == 9) {
		mes "[無口な作業員]";
		mes "この手前に落とし穴を設置する。";
		mes "ここから数歩南に行って見てくれ。";
		if(!checkquest(72200)) {
			setquest 72200;
			compquest 72200;
		}
		close;
	}
	else if(MALAYA_7QUE == 10) {
		mes "[無口な作業員]";
		mes "バリオ・マヒワガから";
		mes "バコナワの湖につながる場所の近くに";
		mes "^0000FF不満そうな作業員^000000がいる。";
		mes "そこに行って一緒に落とし穴を";
		mes "設置してくれ。";
		close;
	}
	else if(MALAYA_7QUE >= 11) {
		mes "[無口な作業員]";
		mes "ここに落とし穴があると";
		mes "ばれてしまう。";
		mes "そこから離れてくれ。";
		close;
	}
	mes "[無口な作業員]";
	mes "町長様から、頼みたいことがあるから";
	mes "ここで待っていてくれと言われた。";
	close;
}
ma_fild01.gat,54,244,0	script	#bako2	139,2,2,{
	if(MALAYA_7QUE == 9) {
		if(checkquest(72200) & 0x8) {
			mes "‐ここら辺に落とし穴を";
			mes "　設置するのが良さそうだ‐";
			next;
			misceffect 0;
			mes "[無口な作業員]";
			mes "道具を持って";
			mes "このように！";
			next;
			misceffect 0;
			mes "[無口な作業員]";
			mes "叩けば！";
			next;
			misceffect 49;
			mes "‐無口な作業員と協力し、";
			mes "　落とし穴を設置した‐";
			next;
			mes "[無口な作業員]";
			mes "できたな。";
			next;
			mes "[無口な作業員]";
			mes "バリオ・マヒワガから";
			mes "バコナワの湖につながる場所の近くに";
			mes "^0000FF不満そうな作業員^000000がいる。";
			mes "そこに行って一緒に落とし穴を";
			mes "設置してくれ。";
			set MALAYA_7QUE,10;
			delquest 72200;
			delquest 1188;
			setquest 1189;
			close;
		}
	}
	else if(MALAYA_7QUE == 10) {
		// 未調査
		mes "‐ここに落とし穴を設置した‐";
		next;
		mes "[無口な作業員]";
		mes "ここに落とし穴があると";
		mes "ばれてしまう。";
		mes "そこから離れてくれ。";
		next;
		mes "[無口な作業員]";
		mes "バリオ・マヒワガから";
		mes "バコナワの湖につながる場所の近くに";
		mes "^0000FF不満そうな作業員^000000がいる。";
		mes "そこに行って一緒に落とし穴を";
		mes "設置してくれ。";
		close;
	}
	end;
}

ma_fild01.gat,236,119,5	script	不満そうな作業員	577,{
	if(MALAYA_7QUE == 10) {
		mes "[不満そうな作業員]";
		mes "ここに穴を掘らなければならない？";
		mes "俺も掘らなければいけないのか？";
		mes "なんでそんな面倒なことを……";
		next;
		mes "[不満そうな作業員]";
		mes "まあ、さっさと終わらせるか。";
		mes "……なあ、あんた！";
		mes "俺のところからちょっと南東に";
		mes "進んでみてくれ。";
		if(!checkquest(72205)) {
			setquest 72205;
			compquest 72205;
		}
		close;
	}
	else if(MALAYA_7QUE == 11) {
		mes "[不満そうな作業員]";
		mes "バコナワの湖に行く途中に";
		mes "^0000FF腰抜け作業員^000000がいるから";
		mes "そこに行ってみな。";
		close;
	}
	else if(MALAYA_7QUE >= 12) {
		mes "[不満そうな作業員]";
		mes "やっと出来上がった落とし穴を";
		mes "どうしてアピールしているんだ！";
		mes "あっちに行ってくれ！";
		close;
	}
	mes "[不満そうな作業員]";
	mes "町長様から、頼みたいことがあるから";
	mes "ここで待っていてくれと言われたんだ。";
	mes "しかし暇だなぁ……";
	close;
}
ma_fild01.gat,242,116,0	script	#bako3	139,2,2,{
	if(MALAYA_7QUE == 10) {
		if(checkquest(72205) & 0x8) {
			mes "‐ここら辺に落とし穴を";
			mes "　設置するのが良さそうだ‐";
			next;
			mes "[不満そうな作業員]";
			mes "ああ、面倒くせぇ……";
			mes "…………。";
			next;
			misceffect 0;
			mes "[不満そうな作業員]";
			mes "つるはしを持って、";
			mes "掘る！";
			next;
			misceffect 0;
			mes "[不満そうな作業員]";
			mes "一生懸命に掘る！";
			next;
			misceffect 49;
			mes "‐不満そうな作業員と協力し、";
			mes "　落とし穴を設置した‐";
			next;
			mes "[不満そうな作業員]";
			mes "ずいぶん不恰好だが、";
			mes "とりあえずできたからいいだろ。";
			next;
			mes "[不満そうな作業員]";
			mes "バコナワの湖に行く途中に";
			mes "^0000FF腰抜け作業員^000000がいるから";
			mes "そこに行ってみな。";
			set MALAYA_7QUE,11;
			delquest 72205;
			delquest 1189;
			setquest 1190;
			close;
		}
	}
	else if(MALAYA_7QUE == 11) {
		mes "‐ここに落とし穴を設置した‐";
		next;
		mes "[不満そうな作業員]";
		mes "落とし穴がしっかり設置されているか";
		mes "自分の体で確認するつもりか？";
		mes "早くそこから離れろ！";
		next;
		mes "[不満そうな作業員]";
		mes "バコナワの湖に行く途中に";
		mes "^0000FF腰抜け作業員^000000がいるから";
		mes "そこに行ってみな。";
		close;
	}
	end;
}

ma_scene01.gat,177,89,4	script	腰抜け作業員	578,{
	if(MALAYA_7QUE == 11) {
		mes "[腰抜け作業員]";
		mes "ここに落とし穴を設置するんですか？";
		mes "町長様がそのように？";
		mes "落とし穴ができたら帰れるんですね？";
		next;
		mes "[腰抜け作業員]";
		mes "わ、わかりました！";
		mes "それでは私の位置から少し";
		mes "南東に進んでもらえますか？";
		if(!checkquest(72210)) {
			setquest 72210;
			compquest 72210;
		}
		close;
	}
	else if(MALAYA_7QUE == 12) {
		mes "[腰抜け作業員]";
		mes "ここから奥に進み、西に行くと";
		mes "^0000FF憂鬱な作業員^000000がいるはずだから";
		mes "行ってみてください。";
		close;
	}
	else if(MALAYA_7QUE >= 13) {
		mes "[腰抜け作業員]";
		mes "あっちに行ってください！";
		mes "あなたのせいでバコナワが";
		mes "現れたらどうするんですか。";
		mes "怖いんですよ！";
		close;
	}
	mes "[腰抜け作業員]";
	mes "町長様にここで待っていてくれと";
	mes "指示されました。";
	mes "こんな怖いところに……";
	mes "早く帰りたい……。";
	close;
}
ma_scene01.gat,179,85,0	script	#bako4	139,2,2,{
	if(MALAYA_7QUE == 11) {
		if(checkquest(72210) & 0x8) {
			mes "‐ここら辺に落とし穴を";
			mes "　設置するのが良さそうだ‐";
			next;
			mes "[腰抜け作業員]";
			mes "まさか怪しい物が";
			mes "埋まっていたりしないですよね？";
			mes "…………。";
			next;
			misceffect 0;
			mes "[腰抜け作業員]";
			mes "スコップを持って、掘る！";
			next;
			misceffect 0;
			mes "[腰抜け作業員]";
			mes "ここを掘る！";
			next;
			misceffect 49;
			mes "‐腰抜け作業員と協力し、";
			mes "　落とし穴を設置した‐";
			next;
			mes "[腰抜け作業員]";
			mes "良かった……";
			mes "何事もなく設置できて……";
			next;
			mes "[腰抜け作業員]";
			mes "ここから奥に進み、西に行くと";
			mes "^0000FF憂鬱な作業員^000000がいるはずだから";
			mes "行ってみてください。";
			set MALAYA_7QUE,12;
			delquest 72210;
			delquest 1190;
			setquest 1191;
			close;
		}
	}
	else if(MALAYA_7QUE == 12) {
		mes "‐ここに落とし穴を設置した‐";
		next;
		mes "[腰抜け作業員]";
		mes "早くそこから離れて下さい！";
		mes "バコナワに落とし穴だとばれて";
		mes "しまったらどうするんですか！";
		next;
		mes "[腰抜け作業員]";
		mes "ここから奥に進み、西に行くと";
		mes "^0000FF憂鬱な作業員^000000がいるはずだから";
		mes "行ってみてください。";
		emotion 4,"";
		close;
	}
	end;
}

ma_scene01.gat,141,118,4	script	憂鬱な作業員	582,{
	if(MALAYA_7QUE == 12) {
		mes "[憂鬱な作業員]";
		mes "落とし穴を設置したい？";
		mes "ふーん……じゃあ、ここから";
		mes "ちょっと北西に歩いてみて。";
		mes "はああ……何でこんなことを";
		mes "頼まれるんだ……。";
		if(!checkquest(72215)) {
			setquest 72215;
			compquest 72215;
		}
		close;
	}
	else if(MALAYA_7QUE == 13) {
		mes "[憂鬱な作業員]";
		mes "この道を辿って上の方まで上がって行くと";
		mes "^0000FF感激している作業員^000000がいるはず。";
		mes "行ってみたら？";
		mes "どうせみんな、バコナワに";
		mes "殺されるんだろうけど……。";
		close;
	}
	else if(MALAYA_7QUE >= 14) {
		mes "[憂鬱な作業員]";
		mes "何をしてもバコナワは攻めて来るのに";
		mes "どうしてこんな苦労をしなければ";
		mes "ならないんだ……。";
		close;
	}
	mes "[憂鬱な作業員]";
	mes "町長様がいろと言ったから";
	mes "ここにいるけど……。";
	mes "何かやらせたいことでも";
	mes "あるのかな。";
	mes "ふう……";
	close;
}
ma_scene01.gat,138,122,0	script	#bako5	139,2,2,{
	if(MALAYA_7QUE == 12) {
		if(checkquest(72215) & 0x8) {
			mes "‐ここら辺に落とし穴を";
			mes "　設置するのが良さそうだ‐";
			next;
			misceffect 0;
			mes "[憂鬱な作業員]";
			mes "網を張れ、";
			mes "網を！";
			next;
			misceffect 0;
			mes "[憂鬱な作業員]";
			mes "このように網を！";
			next;
			misceffect 49;
			mes "‐憂鬱な作業員と協力し、";
			mes "　落とし穴を設置した‐";
			next;
			mes "[憂鬱な作業員]";
			mes "はぁぁ……";
			mes "これが本当に";
			mes "役に立つんだろうか……";
			next;
			mes "[憂鬱な作業員]";
			mes "この道を辿って上の方まで上って行くと";
			mes "^0000FF感激している作業員^000000がいるはず。";
			mes "行ってみたら？";
			set MALAYA_7QUE,13;
			delquest 72215;
			delquest 1191;
			setquest 1192;
			close;
		}
	}
	else if(MALAYA_7QUE == 13) {
		mes "‐ここに落とし穴を設置した‐";
		next;
		mes "[憂鬱な作業員]";
		mes "落とし穴なんかあっても……";
		mes "きっと思ったようには";
		mes "作動しないんだろうな……。";
		close;
	}
	end;
}

ma_scene01.gat,175,170,5	script	感激している作業員	578,{
	if(MALAYA_7QUE == 13) {
		mes "[感激している作業員]";
		mes "なるほど！";
		mes "私たちが協力して、このあたりに";
		mes "落とし穴を作るのですね！";
		mes "なんだかワクワクしてきますね！";
		mes "それでは北西に少し進んで";
		mes "いただけますか？";
		if(!checkquest(72220)) {
			setquest 72220;
			compquest 72220;
		}
		close;
	}
	else if(MALAYA_7QUE == 14) {
		mes "[感激している作業員]";
		mes "落とし穴を全部設置したから、";
		mes "町長様に報告するんですか？";
		mes "うわ～、楽しそう！";
		close;
	}
	else if(MALAYA_7QUE >= 15) {
		mes "[感激している作業員]";
		mes "考えただけで楽しいです。";
		mes "隠れて落とし穴を見張る……。";
		mes "あぁ！　誰かに言いたくなります！";
		mes "私の前に落とし穴があるぞ！";
		mes "はははは～!!";
		emotion 19,"";
		close;
	}
	mes "[感激している作業員]";
	mes "なんと町長様から直々に、ここで";
	mes "待つようにと指示をいただきました！";
	mes "何かビックリするようなイベントでも";
	mes "あるんですかね？";
	mes "何だろ～！";
	close;
}
ma_scene01.gat,171,174,0	script	#bako6	139,2,2,{
	if(MALAYA_7QUE == 13) {
		if(checkquest(72220) & 0x8) {
			mes "‐ここら辺に落とし穴を";
			mes "　設置するのが良さそうだ‐";
			next;
			mes "[感激している作業員]";
			mes "うわあ！";
			mes "ここは落とし穴を設置するのに";
			mes "本当にいい場所ですね。";
			next;
			misceffect 0;
			mes "[感激している作業員]";
			mes "縄を投げますよ！";
			mes "ほおら！";
			next;
			misceffect 0;
			mes "[感激している作業員]";
			mes "縄を受け取ってください～!!";
			next;
			misceffect 49;
			mes "‐感激している作業員と協力し、";
			mes "　落とし穴を設置した‐";
			next;
			mes "[感激している作業員]";
			mes "できた！　ほら見てください！";
			mes "できましたよ！";
			mes "すごいなぁ。";
			mes "立派な落とし穴ですよ～～！";
			next;
			mes "‐落とし穴をすべて設置した。";
			mes "　町長に報告しよう‐";
			set MALAYA_7QUE,14;
			delquest 72220;
			delquest 1192;
			setquest 1193;
			close;
		}
	}
	else if(MALAYA_7QUE == 14) {
		mes "ここに落とし穴を設置した。";
		next;
		mes "[感激している作業員]";
		mes "試しに落ちてみてください！";
		mes "気になって仕方ないんです、";
		mes "どうなるのかが……。";
		mes "きっと楽しいですよね！";
		close;
	}
	end;
}

//============================================================
// ピンタドスフェスティバルNPC
//------------------------------------------------------------
ma_in01_jp.gat,45,148,1	script	イスコ#pin	577,{
	if($MalayaFes01 >= 100 && $MalayaFes02 >= 100 && $MalayaFes03 >= 30) {
		mes "[イスコ]";
		mes "準備も整ったし、";
		mes "いつでもピンタドスフェスティバルを";
		mes "始められますよ。";
		mes "開催してもいいですか？";
		next;
		if(select("ピンタドスフェスティバルを開催する","ちょっと待って") == 2) {
			// 未調査
			close;
		}
		emotion 3;	//はーと
		donpcevent "イスコ#pin::OnStart";
		mes "[イスコ]";
		mes "冒険者のお兄さん、お姉さんたちが";
		mes "手伝ってくれたおかげで、";
		mes "フェスティバルに必要な品物を";
		mes "揃えることができました。";
		next;
		emotion 3;	//♪
		mes "[イスコ]";
		mes "エヘヘ……。";
		mes "これで^7A96E0ピンタドスフェスティバル^000000を";
		mes "開催することができます。";
		close;
	}
	emotion 53;
	mes "[イスコ]";
	mes "あああ、どうしよう……。";
	mes "フェスティバルまで開催まで";
	mes "もう時間がないのに……。";
	next;
	switch(select("どうしたの？","どのくらい集まったの？","材料を持ってきたよ")) {
	case 1:
		mes "[イスコ]";
		mes "バリオ・マヒワガには";
		mes "古くから伝えられている";
		mes "^7A96E0ピンタドスフェスティバル^000000という";
		mes "お祭があるんです。";
		mes "僕はその準備をしていたんですが、";
		next;
		emotion 57;
		mes "[イスコ]";
		mes "ポートマラヤまでお遣いに行った帰り、";
		mes "いきなり目の前に現れた";
		mes "^FF8440ブギスギス^000000たちに";
		mes "材料を奪われてしまったんです……。";
		next;
		mes "[イスコ]";
		mes "ムンバキ・キコに相談しようと";
		mes "ここまで来たのですが、";
		mes "せっかく任せてくれたお仕事を";
		mes "失敗したなんて言い出せなくて……。";
		next;
		mes "[イスコ]";
		mes "材料を買いなおすお金は無いし";
		mes "僕一人では材料を集められません。";
		mes "ああ、どうしよう……。";
		mes "このままじゃ、次のフェスティバルが";
		mes "開催できません……。";
		next;
		menu "材料の内容は？",-;
		mes "[イスコ]";
		mes "奪われた材料は、";
		mes "小さなお守り100個";
		mes "銀の十字架100個";
		mes "染料30個です。";
		next;
		menu "怪我はなかった？",-;
		emotion 54;
		mes "[イスコ]";
		mes "怪我はしませんでしたが、材料がないと";
		mes "^7A96E0ピンタドスフェスティバル^000000が……";
		mes "どうしよう……。";
		close;
	case 2:
		mes "[イスコ]";
		mes "冒険者のお兄さん、お姉さんたちが";
		mes "材料を集めてきてくれているけど、";
		next;
		mes "[イスコ]";
		mes "まだ";
		mes "小さなお守り" +$MalayaFes01+ "個";
		mes "銀の十字架" +$MalayaFes02+ "個";
		mes "染料" +$MalayaFes03+ "個";
		mes "しか集まっていないんです。";
		next;
		emotion 54;
		mes "[イスコ]";
		mes "はああ……まだ足りません。";
		mes "^7A96E0ピンタドスフェスティバル^000000を";
		mes "開催できるかな……。";
		close;
	case 3:
		emotion 3;
		mes "[イスコ]";
		mes "え？　本当？";
		mes "わ～！　ありがとう!!";
		mes strcharinfo(0)+(Sex? "お兄": "お姉")+ "さん!!";
		mes "何を持って来てくれたんですか？";
		next;
		switch(select("小さなお守り(^FF0000" +(100-$MalayaFes01)+ "個不足^000000)","銀の十字架(^FF0000" +(100-$MalayaFes02)+ "個不足^000000)","染料(^FF0000" +(30-$MalayaFes03)+ "個不足^000000)")) {
		case 1:
			set '@itemid,6497;
			set '@itemname$,getitemname('@itemid);
			set '@temp,100-$MalayaFes01;
			mes "[イスコ]";
			mes getitemname('@itemid)+ "を持って来て";
			mes "くれたんですね？";
			next;
			mes "[イスコ]";
			mes "ちょっと待って下さいね。";
			mes "ええと……。";
			next;
			if($MalayaFes01 >= 100) {
				// 適当
				mes "[イスコ]";
				mes getitemname('@itemid)+ "は";
				mes "必要な数が集まりました。やった～！";
				close;
			}
			mes "[イスコ]";
			mes getitemname('@itemid)+ "は今";
			mes '@temp+ "個足りません。";
			mes "いくつ持って来てくれたんですか？";
			break;
		case 2:
			set '@itemid,6502;
			set '@itemname$,getitemname('@itemid);
			set '@temp,100-$MalayaFes02;
			mes "[イスコ]";
			mes getitemname('@itemid)+ "を持って来て";
			mes "くれたんですね？";
			next;
			mes "[イスコ]";
			mes "ちょっと待って下さいね。";
			mes "ええと……。";
			next;
			if($MalayaFes02 >= 100) {
				// 適当
				mes "[イスコ]";
				mes getitemname('@itemid)+ "は";
				mes "必要な数が集まりました。やった～！";
				close;
			}
			mes "[イスコ]";
			mes getitemname('@itemid)+ "は今";
			mes '@temp+ "個足りません。";
			mes "いくつ持って来てくれたんですか？";
			break;
		case 3:
			set '@itemname$,"染料";
			set '@temp,30-$MalayaFes03;
			mes "[イスコ]";
			mes "染料を持って来てくれたんですね？";
			next;
			mes "[イスコ]";
			mes "ちょっと待って下さいね。";
			mes "ええと……。";
			next;
			if($MalayaFes03 >= 30) {
				// 適当
				mes "[イスコ]";
				mes getitemname('@itemid)+ "は";
				mes "必要な数が集まりました。やった～！";
				close;
			}
			mes "[イスコ]";
			mes "染料は今" +'@temp+ "個足りません。";
			mes "どの染料を持って来てくれましたか？";
			next;
			switch(
				select(	"赤色の染料(^FF0000" +countitem(975)+ "^000000)",
						"黄色の染料(^FF0000" +countitem(976)+ "^000000)",
						"青色の染料(^FF0000" +countitem(978)+ "^000000)",
						"緑色の染料(^FF0000" +countitem(979)+ "^000000)",
						"紅色の染料(^FF0000" +countitem(980)+ "^000000)",
						"紫色の染料(^FF0000" +countitem(981)+ "^000000)",
						"白色の染料(^FF0000" +countitem(982)+ "^000000)",
						"黒色の染料(^FF0000" +countitem(983)+ "^000000)"
				)
			) {
			case 1: set '@itemid,975; break;
			case 2: set '@itemid,976; break;
			case 3: set '@itemid,978; break;
			case 4: set '@itemid,979; break;
			case 5: set '@itemid,980; break;
			case 6: set '@itemid,981; break;
			case 7: set '@itemid,982; break;
			case 8: set '@itemid,983; break;
			}
			if(countitem('@itemid) < 1) {
				mes "[イスコ]";
				mes "あれ、" +getitemname('@itemid)+ "は";
				mes "持っていないようですが。";
				close;
			}
			mes "[イスコ]";
			mes (Sex? "お兄": "お姉")+ "さんが持っている" +getitemname('@itemid)+ "は";
			mes countitem('@itemid)+ "個ですね。";
			mes "いくつくれるんですか？";
			break;
		}
		break;
	}
	next;
	if(select("1個","数量を指定する") == 1) {
		if('@itemid == 6497) {
			mes "[イスコ]";
			mes "へへへ……。";
			mes "ひとつ持って来てくれたんですね。";
		} else {
			mes "[イスコ]";
			mes "へへへ……。";
			mes "ひとつ持って来たんですね。";
		}
		next;
		set '@num,1;
	} else {
		mes "[イスコ]";
		mes "へへへ……。";
		mes "まだ足し算があまりできなくて、";
		//mes "一度に30個までしか";
		mes "一度に50個までしか";
		mes "計算ができないんです。";
		mes "いくつ持って来てくれたんですか？";
		next;
		input '@num;
		if('@num <= 0 || '@num > 50) {
			if('@itemid == 6497) {
				mes "[イスコ]";
				mes "意地悪……数字がおかしいと";
				mes "足し算ができませんよ……。";
				close;
			} else {
				mes "[イスコ]";
				mes "意地悪～。";
				mes "数字がおかしいと足し算が";
				mes "できませんよ……。";
				close;
			}
		}
	}
	if(countitem('@itemid) < '@num) {
		mes "[イスコ]";
		mes "あれ？　" +(Sex? "お兄": "お姉")+ "さん！";
		mes getitemname('@itemid)+ "はどこにあるんですか？";
		close;
	}
	delitem '@itemid,'@num;
	if('@itemid == 6497) {
		set $MalayaFes01,$MalayaFes01+'@num;
	} else if('@itemid == 6402) {
		set $MalayaFes02,$MalayaFes02+'@num;
	} else {
		set $MalayaFes03,$MalayaFes03+'@num;
	}
	set '@temp,'@temp-'@num;
	mes "[イスコ]";
	mes "へへへ……。";
	mes "ありがとうございます。" +(Sex? "お兄": "お姉")+ "さん!";
	if('@temp > 0) {
		mes "これで必要な" +'@itemname$+ "は、";
		mes "あと" +'@temp+ "個になりました。";
	}
	else {
		mes "これで" +'@itemname$+ "は";
		mes "必要な数が集まりました。やった～！";
	}
	close;
OnStart:
	initnpctimer;
	set $MalayaFes,1;
	hideoffnpc "観光客#pin1";
	hideoffnpc "観光客#pin2";
	hideoffnpc "観光客#pin3";
	hideoffnpc "観光客#pin4";
	hideoffnpc "若いタトゥーイスト#pin";
	hideoffnpc "太鼓を叩く青年#pin1";
	hideoffnpc "太鼓を叩く青年#pin2";
	hideoffnpc "太鼓を叩く青年#pin3";
	hideoffnpc "拍子を合わせる少年#pin1";
	hideoffnpc "拍子を合わせる少年#pin2";
	hideoffnpc "拍子を合わせる少年#pin3";
	announce "ただ今から一週間、バリオ・マヒワガでピンタドスフェスティバルが開催されます。",0;
	end;
OnReset:
	set $MalayaFes,0;
	set $MalayaFes01,0;
	set $MalayaFes02,0;
	set $MalayaFes03,0;
	hideonnpc "観光客#pin1";
	hideonnpc "観光客#pin2";
	hideonnpc "観光客#pin3";
	hideonnpc "観光客#pin4";
	hideonnpc "若いタトゥーイスト#pin";
	hideonnpc "太鼓を叩く青年#pin1";
	hideonnpc "太鼓を叩く青年#pin2";
	hideonnpc "太鼓を叩く青年#pin3";
	hideonnpc "拍子を合わせる少年#pin1";
	hideonnpc "拍子を合わせる少年#pin2";
	hideonnpc "拍子を合わせる少年#pin3";
	announce "ピンタドスフェスティバルは盛況の末、終了しました。",0;
	stopnpctimer;
	end;
OnTimer3600000:
	if($MalayaFes < 169) {
		set $MalayaFes,$MalayaFes+1;
		initnpctimer;
	}
	else if($MalayaFes == 169) {
		donpcevent "イスコ#pin::OnReset";
	}
	end;
OnInit:
	waitingroom "ピンタドスフェスティバル",0;
	if($MalayaFes >= 1)
		initnpctimer;
	end;
}

ma_fild01.gat,192,200,8	script	観光客#pin1	58,{
	mes "[観光客]";
	mes "ここでピンタドスフェスティバルを";
	mes "やるというからすべて投げ出して";
	mes "遊びに来たんだ。";
	next;
	mes "[観光客]";
	mes "遊びに来たのは後悔してないけど……。";
	next;
	mes "[観光客]";
	mes "思い切って入れたタトゥーが";
	mes "イマイチ気にいらないんだ。";
	next;
	mes "[観光客]";
	mes "背中に入れて貰ったタトゥーを";
	mes "水面に映して見てるけど……。";
	mes "どうもタトゥーイストが";
	mes "失敗したようなんだ。";
	next;
	mes "[観光客]";
	mes "楽しみだったのに……。";
	next;
	mes "[観光客]";
	mes "あ～あ……。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "観光客#pin1";
	end;
}

ma_fild01.gat,211,200,6	script	観光客#pin2	775,{
	mes "[観光客]";
	mes "ピンタドスフェスティバルを";
	mes "開催するといわれてコンロンから";
	mes "遊びに来たんだ。";
	next;
	mes "[観光客]";
	mes "誤解しているかもしれないから";
	mes "先に言っておくけど、";
	mes "私の顔はタトゥーを入れたのではなく";
	mes "仮面だからな……。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "観光客#pin2";
	end;
}

ma_fild01.gat,251,205,2	script	観光客#pin3	824,{
	mes "[観光客]";
	mes "これは私が求めていた";
	mes "タトゥーじゃないぞ!!";
	next;
	mes "[観光客]";
	mes "私はスタイリッシュなタトゥーに";
	mes "してくれと頼んだのに……。";
	mes "ビョンウンゴがこんなに";
	mes "ふとましい格好だったとは!!";
	mes "イメージと大違いだ！";
	mes "やり直してくれ！";
	next;
	mes "[若いタトゥーイスト]";
	mes "あの……お客さん、";
	mes "ビョンウンゴはそういうものだと";
	mes "説明したじゃないですか。";
	mes "も～、だから思いつきでいれるのは";
	mes "やめた方がいいと言ったのに……。";
	next;
	mes "[観光客]";
	mes "いやいや。いやいやいや!!";
	mes "これじゃ駄目だ！違う！";
	mes "頼むからやり直してくれ！";
	next;
	mes "[若いタトゥーイスト]";
	mes "あー、もう！";
	mes "困ったな……。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "観光客#pin3";
	end;
}

ma_fild01.gat,162,235,6	script	観光客#pin4	815,{
	mes "[観光客]";
	mes "ピンタドスフェスティバルは";
	mes "一週間だけ開催されるらしいですね。";
	next;
	mes "[観光客]";
	mes "私は遠くの龍之城から遊びに来てたけど、";
	mes "ちょうどピンタドスフェスティバルの";
	mes "開催期間中だったとは……。";
	mes "運が良かったようです。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "観光客#pin4";
	end;
}

ma_fild01.gat,249,206,6	script	若いタトゥーイスト#pin	582,{
	mes "[若いタトゥーイスト]";
	mes "無計画な人がお客様だと";
	mes "本当に困ります。";
	next;
	mes "[若いタトゥーイスト]";
	mes "最近は気軽に入れる方が多いですが";
	mes "やはりタトゥーは覚悟や信念を";
	mes "刻むものだと思っています。";
	mes "気に入らないから";
	mes "やり直してくれと言われても……";
	mes "困ったものです。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "若いタトゥーイスト#pin";
	end;
}

ma_fild01.gat,164,234,6	script	太鼓を叩く青年#pin1	578,{
	mes "‐ドドドドーン‐";
	next;
	mes "[太鼓を叩く青年]";
	mes "やはりピンタドスフェスティバルの";
	mes "期間中は、太鼓を叩きながら";
	mes "楽しむのが一番だな。";
	next;
	mes "[太鼓を叩く青年]";
	mes "君も楽しんだらどうだ？";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "太鼓を叩く青年#pin1";
	end;
}

ma_fild01.gat,170,231,4	script	太鼓を叩く青年#pin2	578,{
	mes "‐ドドドドーン‐";
	next;
	mes "[太鼓を叩く青年]";
	mes "ピンタドスフェスティバルの";
	mes "ピンタドスは、私達の言葉で";
	mes "塗られているという意味です。";
	next;
	mes "[太鼓を叩く青年]";
	mes "だから、この期間の間だけ";
	mes "特別なタトゥーを入れてくれる方も";
	mes "いるんですよ。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "太鼓を叩く青年#pin2";
	end;
}

ma_fild01.gat,164,228,6	script	太鼓を叩く青年#pin3	578,{
	mes "‐ドドドドーン‐";
	next;
	mes "[太鼓を叩く青年]";
	mes "よく覚えてないが、";
	next;
	mes "[太鼓を叩く青年]";
	mes "俺が子供の頃の";
	mes "ピンタドスフェスティバルは";
	mes "今ほどタトゥーを前面に";
	mes "押し出した祭ではなく、";
	mes "豊かな収穫を喜ぶ祭だったらしい。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "太鼓を叩く青年#pin3";
	end;
}

ma_fild01.gat,170,234,4	script	拍子を合わせる少年#pin1	577,{
	mes "‐タタタタン‐";
	next;
	mes "[拍子を合わせる少年]";
	mes "太鼓の音と棒で拍子を合わせる音は";
	mes "いつ聞いても盛り上がりますね。";
	next;
	mes "[拍子を合わせる少年]";
	mes "タタタターンタタタターン";
	mes "楽しいな～。";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "拍子を合わせる少年#pin1";
	end;
}

ma_fild01.gat,164,231,6	script	拍子を合わせる少年#pin2	577,{
	mes "‐タタタタン‐";
	next;
	mes "[拍子を合わせる少年]";
	mes "今は棒を使って";
	mes "拍子を合わせてるけど";
	next;
	mes "[拍子を合わせる少年]";
	mes "いつかは僕も太鼓を叩く日が";
	mes "くるのかな？";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "拍子を合わせる少年#pin2";
	end;
}

ma_fild01.gat,170,228,4	script	拍子を合わせる少年#pin3	577,{
	mes "‐タタタタン‐";
	next;
	mes "[拍子を合わせる少年]";
	mes "今は棒を使って";
	mes "拍子を合わせてるけど";
	next;
	mes "[拍子を合わせる少年]";
	mes "いつかは僕も太鼓を叩く日が";
	mes "くるのかな？";
	close;
OnInit:
	if($MalayaFes == 0)
		hideonnpc "拍子を合わせる少年#pin3";
	end;
}
