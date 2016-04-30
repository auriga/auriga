//==============================================================================
// Ragnarok Online Slot Enchant Script     by Blaze
//==============================================================================
-	script	セヤブルレム#slot	84,{
	mes "[セヤブルレム]";
	mes "私は一般的な武器や防具に";
	mes "スロットエンチャントが";
	mes "できる技術者です。";
	mes "スロットエンチャントとは、";
	mes "装備品にスロットを追加する";
	mes "技術の事です。";
	next;
	mes "[セヤブルレム]";
	mes "スロットの追加とだけ聞くと";
	mes "簡単そうに思うでしょうが、";
	mes "そんな事はありません。";
	next;
	mes "[セヤブルレム]";
	mes "その証拠に、私以外にこんな技術を";
	mes "持った人がいませんよね？";
	mes "それだけスロットを追加する技術は";
	mes "難しいという事です。";
	next;
	mes "[セヤブルレム]";
	mes "さて、スロットを追加したい";
	mes "装備品はありますか？";
	mes "品によって、手数料や必要な材料、";
	mes "成功確率が違いますのでご注意を。";
	next;
	switch(select("武器","防具","説明を詳しく聞く","話をやめる")) {
	case 1:
		set '@equip$,"武器";
		break;
	case 2:
		set '@equip$,"防具";
		break;
	case 3:
		mes "[セヤブルレム]";
		mes "スロットエンチャントとは、";
		mes "装備品にスロットを追加する技術。";
		mes "成否に関わらず材料は全て消滅します。";
		mes "また、例え成功したとしても";
		mes "精錬・カード・属性等の付与効果は";
		mes "全て消滅します。";
		next;
		mes "[セヤブルレム]";
		mes "さらに、一部の装備品だけですが";
		mes "スロットが同時に複数追加されたり、";
		mes "基本性能が変化する物があります。";
		next;
		mes "[セヤブルレム]";
		mes "そして、気をつけなければならない点が";
		mes "一つあります。";
		mes "例えば……「+7マント [0]」と";
		mes "ただの「マント [0]」を持って、";
		mes "私にスロットエンチャントを依頼すると";
		mes "どちらが対象になると思いますか？";
		next;
		mes "[セヤブルレム]";
		mes "正解はわからない……";
		mes "つまり、対象のアイテムが";
		mes "どういった物か、私は一切";
		mes "気にせずに作業するという事です。";
		next;
		mes "[セヤブルレム]";
		mes "^FF0000スロット数以外は、";
		mes "一切関係ありません。";
		mes "例え未鑑定だろうが、";
		mes "破損していようが、";
		mes "スロットエンチャントを行います。^000000";
		next;
		mes "[セヤブルレム]";
		mes "^FF0000しかし、誰かが作った製造品だと";
		mes "スロットの数に関係なく";
		mes "スロットエンチャントの";
		mes "対象アイテムとなります。^000000";
		next;
		mes "[セヤブルレム]";
		mes "^FF0000特定のアイテムだけに";
		mes "スロットエンチャントを";
		mes "行いたいのなら、同じ名前の";
		mes "アイテムを倉庫にでも";
		mes "預けておいた方がいいです。^000000";
		next;
		mes "[セヤブルレム]";
		mes "この事を忘れ、別のアイテムが";
		mes "スロットエンチャントの対象になっても";
		mes "私は一切責任を取りません。";
		mes "十分に注意してください。";
		next;
		mes "[セヤブルレム]";
		mes "他に説明する事は特にありません。";
		mes "百聞は一見にしかず。";
		mes "まずはスロットエンチャントに";
		mes "挑戦してみたらどうですか？";
		close;
	case 4:
		mes "[セヤブルレム]";
		mes "そうですか……";
		close;
	}
	mes "[セヤブルレム]";
	mes "OK、" +'@equip$+ "ですね。";
	mes '@equip$+ "となると……";
	mes "手数料や材料などによって";
	mes "4階級に分かれています。";
	mes "まず、スロットを追加したいアイテムの";
	mes "階級を選んでください。";
	next;
	set '@class,select("C級","B級","A級","S級");
	switch('@class) {
	case 1:
		mes "[セヤブルレム]";
		mes "わかりました。";
		mes "C級のどの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("トライデント [2]","ロープ [3]","バイオリン [3]")) {
			case 1: //トライデント
				setarray '@delid,1460,1462;
				set '@getid,1461;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			case 2: //ロープ
				set '@delid,1950;
				set '@getid,1951;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			case 3: //バイオリン
				set '@delid,1901;
				set '@getid,1902;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			}
		}
		else {
			switch(select("メントル [0]","ロングコート [0]","サークレット [0]","ビレタ [0]")) {
			case 1: //メントル
				set '@delid,2307;
				set '@getid,2308;
				set '@need,999;
				set '@amount,3;
				set '@zeny,200000;
				break;
			case 2: //ロングコート
				set '@delid,2309;
				set '@getid,2310;
				set '@need,999;
				set '@amount,3;
				set '@zeny,200000;
				break;
			case 3: //サークレット
				set '@delid,2232;
				set '@getid,2233;
				set '@need,999;
				set '@amount,3;
				set '@zeny,200000;
				break;
			case 4: //ビレタ
				set '@delid,2216;
				set '@getid,2217;
				set '@need,999;
				set '@amount,3;
				set '@zeny,200000;
				break;
			}
		}
		break;
	case 2:
		mes "[セヤブルレム]";
		mes "無難なB級ですね。";
		mes "どの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("チェイン [2]","グラディウス [2]","角弓 [1]","パイク [3]","海東剣 [1]","リュート [2]","ワイヤー [2]","バグナウ [3]","アーバレスト [1]")) {
			case 1: //チェイン
				setarray '@delid,1519,1521;
				set '@getid,1520;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,300000;
				break;
			case 2: //グラディウス
				setarray '@delid,1219,1221;
				set '@getid,1220;
				setarray '@need,984,999;
				setarray '@amount,1,5;
				set '@zeny,300000;
				break;
			case 3: //角弓
				set '@delid,1714;
				set '@getid,1716;
				setarray '@need,984,999;
				setarray '@amount,2,5;
				set '@zeny,300000;
				break;
			case 4: //パイク
				setarray '@delid,1407,1409;
				set '@getid,1408;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,300000;
				break;
			case 5: //海東剣
				set '@delid,1123;
				set '@getid,1128;
				setarray '@need,984,999;
				setarray '@amount,2,5;
				set '@zeny,300000;
				break;
			case 6: //リュート
				set '@delid,1905;
				set '@getid,1906;
				set '@need,1011;
				set '@amount,10;
				set '@zeny,300000;
				break;
			case 7: //ワイヤー
				set '@delid,1954;
				set '@getid,1955;
				set '@need,1011;
				set '@amount,10;
				set '@zeny,300000;
				break;
			case 8: //バグナウ
				set '@delid,1801;
				set '@getid,1802;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,300000;
				break;
			case 9: //アーバレスト
				set '@delid,1713;
				set '@getid,1715;
				setarray '@need,984,999;
				setarray '@amount,2,5;
				set '@zeny,300000;
				break;
			}
		}
		else {
			switch(select("ミラーシールド [0]","メイル [0]","セイントローブ [0]","シルクローブ [0]","ブーツ [0]","シューズ [0]","マフラー [0]","ガード [0]","バックラー [0]","シールド [0]","ボンゴン帽 [0]")) {
			case 1: //ミラーシールド
				set '@delid,2107;
				set '@getid,2108;
				set '@need,999;
				set '@amount,5;
				set '@zeny,250000;
				break;
			case 2: //メイル
				set '@delid,2314;
				set '@getid,2315;
				set '@need,999;
				set '@amount,5;
				set '@zeny,250000;
				break;
			case 3: //セイントローブ
				set '@delid,2325;
				set '@getid,2326;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 4: //シルクローブ
				set '@delid,2321;
				set '@getid,2322;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 5: //ブーツ
				set '@delid,2405;
				set '@getid,2406;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 6: //シューズ
				set '@delid,2403;
				set '@getid,2404;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 7: //マフラー
				set '@delid,2503;
				set '@getid,2504;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 8: //ガード
				set '@delid,2101;
				set '@getid,2102;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 9: //バックラー
				set '@delid,2103;
				set '@getid,2104;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 10: //シールド
				set '@delid,2105;
				set '@getid,2106;
				set '@need,999;
				set '@amount,5;
				set '@zeny,250000;
				break;
			case 11: //ボンゴン帽
				set '@delid,5046;
				set '@getid,5168;
				set '@need,999;
				set '@amount,5;
				set '@zeny,250000;
				break;
			}
		}
		break;
	case 3:
		mes "[セヤブルレム]";
		mes "A級……少し難しいですね。";
		mes "どの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("ハンターボウ [0]","サバイバルロッド(INT) [0]","ツヴァイハンダー [0]","フランベルジェ [0]","裏切り者 [0]","バリスタ [0]","スタナー [0]","ベルセルク [0]","クレイモア [0]")) {
			case 1: //ハンターボウ
				set '@delid,1718;
				set '@getid,1726;
				setarray '@need,984,999;
				setarray '@amount,2,10;
				set '@zeny,500000;
				break;
			case 2: //サバイバルロッド（INT）
				set '@delid,1619;
				set '@getid,1620;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,500000;
				break;
			case 3: //ツヴァイハンダー
				set '@delid,1168;
				set '@getid,1171;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,800000;
				break;
			case 4: //フランベルジェ
				set '@delid,1129;
				set '@getid,1149;
				setarray '@need,984,999;
				setarray '@amount,2,10;
				set '@zeny,500000;
				break;
			case 5: //裏切り者
				set '@delid,1261;
				set '@getid,1266;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,700000;
				break;
			case 6: //バリスタ
				set '@delid,1722;
				set '@getid,1727;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,500000;
				break;
			case 7: //スタナー
				set '@delid,1522;
				set '@getid,1532;
				setarray '@need,984,999;
				setarray '@amount,2,10;
				set '@zeny,500000;
				break;
			case 8: //ベルセルク
				set '@delid,1814;
				set '@getid,1816;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,500000;
				break;
			case 9: //クレイモア
				set '@delid,1163;
				set '@getid,1172;
				setarray '@need,984,999;
				setarray '@amount,2,10;
				set '@zeny,500000;
				break;
			}
		}
		else {
			switch(select("ジュエルヘルム [0]","やわらかい帽子 [0]","メモライズブック [0]","タイツ [0]","フルプレート [0]","プレート [0]","シーフクロース [0]","グリーブ [0]","修道女のヴェール [0]","マント [0]","ヘルム [0]","忍者スーツ [0]","オーク族のヘルム [0]","昔の領主のマント [0]","聖職者の帽子 [0]","ゴールデンヘッドギア [0]","ブローチ [0]","ムナック帽 [0]")) {
			case 1: //ジュエルヘルム
				set '@delid,2230;
				set '@getid,2231;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 2: //やわらかい帽子
				set '@delid,5114;
				set '@getid,5120;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 3: //メモライズブック
				set '@delid,2109;
				set '@getid,2121;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 4: //タイツ
				set '@delid,2330;
				set '@getid,2331;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 5: //フルプレート
				set '@delid,2341;
				set '@getid,2342;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 6: //プレート
				set '@delid,2316;
				set '@getid,2317;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 7: //シーフクロース
				set '@delid,2335;
				set '@getid,2336;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 8: //グリーブ
				set '@delid,2411;
				set '@getid,2412;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 9: //修道女のヴェール
				set '@delid,5092;
				set '@getid,5093;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 10: //マント
				set '@delid,2505;
				set '@getid,2506;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 11: //ヘルム
				set '@delid,2228;
				set '@getid,2229;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 12: //忍者スーツ
				set '@delid,2337;
				set '@getid,2359;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 13: //オーク族のヘルム
				set '@delid,2299;
				set '@getid,5157;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 14: //昔の領主のマント
				set '@delid,2507;
				set '@getid,2525;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 15: //聖職者の帽子
				set '@delid,2251;
				set '@getid,5158;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 16: //ゴールデンヘッドギア
				set '@delid,2246;
				set '@getid,5159;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 17: //ブローチ
				set '@delid,2605;
				set '@getid,2625;
				set '@need,985;
				set '@amount,1;
				set '@zeny,400000;
				break;
			case 18: //ムナック帽
				set '@delid,2264;
				set '@getid,5167;
				set '@need,985;
				set '@amount,1;
				set '@zeny,300000;
				break;
			}
		}
		break;
	case 4:
		mes "[セヤブルレム]";
		mes "え……S級ですか！";
		mes "……どの" +'@equip$+ "ですか？";
		next;
		if('@equip$ == "武器") {
			switch(select("グングニール [0]","ポイズンナイフ [0]","錐 [0]","スクサマッド [0]","ギンヌンガガップ [0]","カトラス [0]","クレセントサイダー [0]","サバイバルロッド(DEX) [0]")) {
			case 1: //グングニール
				set '@delid,1413;
				set '@getid,1418;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 2: //ポイズンナイフ
				set '@delid,1239;
				set '@getid,13016;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 3: //錐
				set '@delid,1230;
				set '@getid,13017;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 4: //スクサマッド
				set '@delid,1236;
				set '@getid,13018;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 5: //ギンヌンガガップ
				set '@delid,13002;
				set '@getid,13019;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,700000;
				break;
			case 6: //カトラス
				set '@delid,1135;
				set '@getid,13400;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 7: //クレセントサイダー
				set '@delid,1466;
				set '@getid,1476;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 8: //サバイバルロッド(DEX)
				set '@delid,1617;
				set '@getid,1618;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,2000000;
				break;
			}
		}
		else {
			switch(select("マジェスティックゴート [0]","シャープヘッドギア [0]","ボーンヘルム [0]","コルセア [0]","クラウン [0]","ティアラ [0]","スフィンクス帽 [0]","キャスティングローブ [0]","イヤリング [0]","リング [0]","弓用の指貫 [0]")) {
			case 1: //マジェスティックゴート
				set '@delid,2256;
				set '@getid,5160;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 2: //シャープヘッドギア
				set '@delid,2258;
				set '@getid,5161;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 3: //ボーンヘルム
				set '@delid,5017;
				set '@getid,5162;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 4: //コルセア
				set '@delid,5019;
				set '@getid,5163;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 5: //クラウン
				set '@delid,2235;
				set '@getid,5165;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 6: //ティアラ
				set '@delid,2234;
				set '@getid,5164;
				set '@need,985;
				set '@amount,2;
				set '@zeny,2000000;
				break;
			case 7: //スフィンクス帽
				set '@delid,5053;
				set '@getid,5166;
				set '@need,985;
				set '@amount,2;
				set '@zeny,1000000;
				break;
			case 8: //キャスティングローブ
				set '@delid,2343;
				set '@getid,2360;
				set '@need,985;
				set '@amount,2;
				set '@zeny,1000000;
				break;
			case 9: //イヤリング
				set '@delid,2602;
				set '@getid,2622;
				set '@need,985;
				set '@amount,2;
				set '@zeny,1000000;
				break;
			case 10: //リング
				set '@delid,2601;
				set '@getid,2621;
				set '@need,985;
				set '@amount,2;
				set '@zeny,1000000;
				break;
			case 11: //弓用の指貫
				set '@delid,2619;
				set '@getid,2671;
				set '@need,985;
				set '@amount,2;
				set '@zeny,1000000;
				break;
			}
		}
		break;
	}
	mes "[セヤブルレム]";
	mes getitemname('@delid)+ " [" +getiteminfo('@delid,10)+ "]ですね。";
	mes "手数料は^FF0000" +'@zeny/10000+ "万Zeny^000000、";
	if('@amount[1]) {
		mes "材料は" +getitemname('@need[0])+'@amount[0]+ "個^000000、";
		mes "^FF0000" +getitemname('@need[1])+'@amount[1]+ "個^000000です。";
	}
	else
		mes "材料は" +getitemname('@need)+'@amount+ "個^000000です。";
	mes "もちろん、" +getitemname('@delid)+ " [" +getiteminfo('@delid,10)+ "]も必要です。";
	next;
	mes "[セヤブルレム]";
	mes "なお、注意点として";
	mes "スロットエンチャントを行うと";
	mes "成否に関わらず材料は全て消滅します。";
	mes "また、例え成功したとしても";
	mes "精錬・カード・属性等の付与効果は";
	mes "全て消滅します。";
	next;
	if(select("スロットエンチャントを頼む","話をやめる")==2) {
		mes "[セヤブルレム]";
		mes "また来てください。";
		close;
	}
	if((countitem('@delid[0]) < 1 && countitem('@delid[1]) < 1) || Zeny < '@zeny) {
		mes "[セヤブルレム]";
		mes "材料かお金が足りませんよ？";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1) {
		if(countitem('@need['@i]) < '@amount['@i]) {
			mes "[セヤブルレム]";
			mes "材料かお金が足りませんよ？";
			close;
		}
	}
	if(countitem('@delid))
		delitem '@delid,1;
	else
		delitem '@delid[1],1;
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1)
		delitem '@need['@i],'@amount['@i];
	set Zeny,Zeny-'@zeny;
	switch('@class) {
		case 1: set '@success,25; break; //C級
		case 2: set '@success,20; break; //B級
		case 3: set '@success,20; break; //A級
		case 4: set '@success,10; break; //S級
	}
	if(rand(100) < '@success) {
		if('@class == 4)
			misceffect 90;
		else
			misceffect 83;
		mes "[セヤブルレム]";
		mes "OK、成功しました。";
		mes "おめでとうございます。";
		getitem '@getid,1;
	}
	else {
		misceffect 183;
		mes "[セヤブルレム]";
		mes "う……失敗です。";
		mes "どうやら運が無かったようです。";
		mes "……そう落ち込まないでください。";
		mes "今度はきっと成功しますよ。";
	}
	next;
	mes "[セヤブルレム]";
	mes "それでは、またご利用ください。";
	close;
}

-	script	青年#slot	97,{
	mes "[青年]";
	mes "気をつけてください。";
	mes "スロットエンチャントを行うと、";
	mes "装備品に付与された効果は";
	mes "消えてしまいます。";
	next;
	mes "[青年]";
	mes "また、スロットエンチャントの";
	mes "副作用により、基本性能が";
	mes "変化する装備品もあります。";
	next;
	mes "[青年]";
	mes "そして、とても珍しい事ですが、";
	mes "スロットが複数追加される";
	mes "装備品があります。";
	mes "もちろん、全ての装備品で";
	mes "起きる事ではありません。";
	mes "あくまで一部の装備品のみです。";
	next;
	mes "[青年]";
	mes "私も今から勉強して、";
	mes "セヤブルレムさんのように";
	mes "スロットを追加する技術を";
	mes "身につけたいです。";
	close;
}

prt_in.gat,33,69,4	duplicate(セヤブルレム#slot)	セヤブルレム	84
prt_in.gat,31,57,0	duplicate(青年#slot)	青年	97
morocc.gat,51,41,5	duplicate(セヤブルレム#slot)	セヤブルレム	84
morocc.gat,60,42,3	duplicate(青年#slot)	青年	97
payon.gat,140,151,5	duplicate(セヤブルレム#slot)	セヤブルレム	84
payon.gat,143,143,7	duplicate(青年#slot)	青年	97
lhz_in02.gat,281,35,4	duplicate(セヤブルレム#slot)	セヤブルレム	84
lhz_in02.gat,269,33,4	duplicate(青年#slot)	青年	97
//==============================================================================
-	script	レアブルレム#slot	86,{
	mes "[レアブルレム]";
	mes "私は一般的な武器や防具に";
	mes "スロットエンチャントが";
	mes "できる技術者です。";
	mes "スロットエンチャントとは、";
	mes "装備品にスロットを追加する";
	mes "技術の事です。";
	next;
	mes "[レアブルレム]";
	mes "兄であるセヤブルレムに";
	mes "技術指導をして貰っているので";
	mes "大抵の事は出来ます。";
	next;
	mes "[レアブルレム]";
	mes "まあ、……兄と比べると";
	mes "出来る事は少ないのですが。";
	next;
	mes "[レアブルレム]";
	mes "兄は技術を教えてくれながら";
	mes "私の個性が消えないように";
	mes "非常に気を配ってくれまして。";
	mes "お陰で、私にしか出来ない";
	mes "特別なスロットエンチャントも";
	mes "習得しました。";
	next;
	mes "[レアブルレム]";
	mes "兄は余りにも危険だから、と";
	mes "特別なスロットエンチャントは";
	mes "お気に召さなかったようですが……";
	next;
	mes "[レアブルレム]";
	mes "さて、スロットを追加したい";
	mes "装備品はありますか？";
	mes "品によって、手数料や必要な材料、";
	mes "成功確率が違いますのでご注意を。";
	next;
	switch(select("武器","防具","特別なスロットエンチャント？","説明を詳しく聞く","話をやめる")) {
	case 1:
		set '@equip$,"武器";
		break;
	case 2:
		set '@equip$,"防具";
		break;
	case 3:
		mes "[レアブルレム]";
		mes "ええ。";
		mes "兄が言うには、人間が行っていい行為";
		mes "ではないと。";
		mes "神に対する不遜な行いらしいです。";
		next;
		mes "[レアブルレム]";
		mes "成功率はとても高いのですが、";
		mes "材料も作業にかかる手数料も莫大で、";
		mes "依頼する人もいるのかどうか……";
		mes "正直、疑問です。";
		next;
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "興味があるんですね？";
		mes "まあ、説明くらいなら……";
		mes "ただし、兄には秘密でお願いしますよ？";
		mes "私がこんな話をしたことがバレたら";
		mes "酷い目に会わされてしまいますから！";
		next;
		mes "[レアブルレム]";
		mes "成功率は 90%、黄金 2個、";
		mes "2億Zenyもの大金がかかります。";
		next;
		mes "[レアブルレム]";
		mes "その技術とは……";
		mes "あの太陽神の兜にスロットを追加する";
		mes "という超絶技術なのです!!";
		next;
		if(select("スロットエンチャントを頼む","話をやめる")==2) {
			mes "[レアブルレム]";
			mes "また来てください。";
			close;
		}
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "私の話を聞いていました？";
		mes "これは、タブー行為なんですよ！";
		mes "やってはいけないのです！";
		next;
		mes "[レアブルレム]";
		mes "やりませんよ！";
		next;
		mes "[レアブルレム]";
		mes "やりませんってば！";
		next;
		mes "[レアブルレム]";
		mes "……やりません。";
		next;
		mes "[レアブルレム]";
		mes "…………";
		next;
		mes "[レアブルレム]";
		mes "……";
		next;
		mes "[レアブルレム]";
		mes "…………うーん。";
		mes "わかりました！";
		mes "今回だけは、例外ですよ！";
		next;
		mes "[レアブルレム]";
		mes "太陽神の兜ですね。";
		mes "手数料は^FF0000 2億Zeny^000000、";
		mes "材料は^FF0000黄金 2個^000000です。";
		mes "もちろん、太陽神の兜[0]も";
		mes "必要です。";
		next;
		mes "[レアブルレム]";
		mes "なお、注意点として";
		mes "スロットエンチャントを行うと";
		mes "成否に関わらず材料は全て消滅します。";
		mes "また、例え成功したとしても";
		mes "精錬・カード・属性等の付与効果は";
		mes "全て消滅します。";
		next;
		if(countitem(5022) < 1 || countitem(969) < 2 || Zeny < 200000000) {
			mes "[レアブルレム]";
			mes "材料かお金が足りませんよ？";
			close;
		}
		if(select("スロットエンチャントを頼む","話をやめる")==2) {
			mes "[レアブルレム]";
			mes "また来てください。";
			close;
		}
		delitem 5022,1;
		delitem 969,2;
		set Zeny,Zeny-200000000;
		if(rand(100) < 90) {
			misceffect 90;
			mes "[レアブルレム]";
			mes "OK、成功しました。";
			mes "おめでとうございます。";
			getitem 5353,1;
		}
		else {
			misceffect 183;
			mes "[レアブルレム]";
			mes "う……失敗です。";
			mes "どうやら運が無かったようです。";
			mes "……そう落ち込まないでください。";
			mes "今度はきっと成功しますよ。";
		}
		next;
		mes "[レアブルレム]";
		mes "それでは、またご利用ください。";
		close;
	case 4:
		mes "[レアブルレム]";
		mes "スロットエンチャントとは、";
		mes "装備品にスロットを追加する技術。";
		mes "成否に関わらず材料は全て消滅します。";
		mes "また、例え成功したとしても";
		mes "精錬・カード・属性等の付与効果は";
		mes "全て消滅します。";
		next;
		mes "[レアブルレム]";
		mes "さらに、一部の装備品だけですが";
		mes "スロットが同時に複数追加されたり、";
		mes "基本性能が変化する物があります。";
		next;
		mes "[レアブルレム]";
		mes "そして、気をつけなければならない点が";
		mes "一つあります。";
		mes "例えば……「+7マント [0]」と";
		mes "ただの「マント [0]」を持って、";
		mes "私にスロットエンチャントを依頼すると";
		mes "どちらが対象になると思いますか？";
		next;
		mes "[レアブルレム]";
		mes "正解はわからない……";
		mes "つまり、対象のアイテムが";
		mes "どういった物か、私は一切";
		mes "気にせずに作業するという事です。";
		next;
		mes "[レアブルレム]";
		mes "^FF0000スロット数以外は、";
		mes "一切関係ありません。";
		mes "例え未鑑定だろうが、";
		mes "破損していようが、";
		mes "スロットエンチャントを行います。^000000";
		next;
		mes "[レアブルレム]";
		mes "^FF0000しかし、誰かが作った製造品だと";
		mes "スロットの数に関係なく";
		mes "スロットエンチャントの";
		mes "対象アイテムとなります。^000000";
		next;
		mes "[レアブルレム]";
		mes "^FF0000特定のアイテムだけに";
		mes "スロットエンチャントを";
		mes "行いたいのなら、同じ名前の";
		mes "アイテムを倉庫にでも";
		mes "預けておいた方がいいです。^000000";
		next;
		mes "[レアブルレム]";
		mes "この事を忘れ、別のアイテムが";
		mes "スロットエンチャントの対象になっても";
		mes "私は一切責任を取りません。";
		mes "十分に注意してください。";
		next;
		mes "[レアブルレム]";
		mes "他に説明する事は特にありません。";
		mes "百聞は一見にしかず。";
		mes "まずはスロットエンチャントに";
		mes "挑戦してみたらどうですか？";
		close;
	case 5:
		mes "[レアブルレム]";
		mes "そうですか……";
		close;
	}
	mes "[レアブルレム]";
	mes "OK、" +'@equip$+ "ですね。";
	mes '@equip$+ "となると……";
	mes "手数料や材料などによって";
	mes "4階級に分かれています。";
	mes "まず、スロットを追加したいアイテムの";
	mes "階級を選んでください。";
	next;
	set '@class,select("C級","B級","A級","S級");
	switch('@class) {
	case 1:
		mes "[レアブルレム]";
		mes "わかりました。";
		mes "C級のどの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("裂けた大地の書","荒れ狂う波の書","乾いてる風の書","燃える太陽の書")) {
			case 1: //裂けた大地の書
				set '@delid,1554;
				set '@getid,1569;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			case 2: //荒れ狂う波の書
				set '@delid,1553;
				set '@getid,1568;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			case 3: //乾いてる風の書
				set '@delid,1556;
				set '@getid,1571;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			case 4: //燃える太陽の書
				set '@delid,1555;
				set '@getid,1570;
				set '@need,1010;
				set '@amount,10;
				set '@zeny,200000;
				break;
			}
		}
		else {
			switch(select("装飾用ひまわり","学者帽","大きなリボン","学生帽")) {
			case 1: //装飾用ひまわり
				set '@delid,2253;
				set '@getid,5351;
				set '@need,999;
				set '@amount,3;
				set '@zeny,100000;
				break;
			case 2: //学者帽
				set '@delid,5012;
				set '@getid,5347;
				set '@need,999;
				set '@amount,3;
				set '@zeny,100000;
				break;
			case 3: //大きなリボン
				set '@delid,2244;
				set '@getid,5348;
				set '@need,999;
				set '@amount,5;
				set '@zeny,100000;
				break;
			case 4: //学生帽
				set '@delid,5016;
				set '@getid,5349;
				set '@need,999;
				set '@amount,5;
				set '@zeny,100000;
				break;
			}
		}
		break;
	case 2:
		mes "[レアブルレム]";
		mes "無難なB級ですね。";
		mes "どの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("オーキッシュアックス","シミター","スパイク")) {
			case 1: //オーキッシュアックス
				set '@delid,1304;
				set '@getid,1309;
				set '@need,984;
				set '@amount,1;
				set '@zeny,200000;
				break;
			case 2: //シミター
				setarray '@delid,1113,1115;
				set '@getid,1114;
				set '@need,984;
				set '@amount,1;
				set '@zeny,200000;
				break;
			case 3: //スパイク
				set '@delid,1523;
				set '@getid,1538;
				set '@need,984;
				set '@amount,1;
				set '@zeny,300000;
				break;
			}
		}
		else {
			switch(select("骸骨の指輪","ハイヒール")) {
			case 1: //骸骨の指輪
				set '@delid,2609;
				set '@getid,2715;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			case 2: //ハイヒール
				set '@delid,2409;
				set '@getid,2432;
				set '@need,999;
				set '@amount,5;
				set '@zeny,300000;
				break;
			}
		}
		break;
	case 3:
		mes "[レアブルレム]";
		mes "A級……少し難しいですね。";
		mes "どの" +'@equip$+ "にしますか？";
		next;
		if('@equip$ == "武器") {
			switch(select("ドラゴンキラー","尖ってるいばらのカタール","爆炎のカタール","冷たい氷柱のカタール","疾風のカタール","ゴールデンメイス","琵琶","女王の鞭","妖怪の槍","ゲイボルグ","シュバイチェルサーベル")) {
			case 1: //ドラゴンキラー
				set '@delid,13001;
				set '@getid,13030;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 2: //尖ってるいばらのカタール
				set '@delid,1257;
				set '@getid,1276;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 3: //爆炎のカタール
				set '@delid,1258;
				set '@getid,1277;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 4: //冷たい氷柱のカタール
				set '@delid,1256;
				set '@getid,1275;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 5: //疾風のカタール
				set '@delid,1259;
				set '@getid,1278;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 6: //ゴールデンメイス
				set '@delid,1524;
				set '@getid,1539;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 7: //琵琶
				set '@delid,1918;
				set '@getid,1922;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 8: //女王の鞭
				set '@delid,1970;
				set '@getid,1976;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 9: //妖怪の槍
				set '@delid,1477;
				set '@getid,1479;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 10: //ゲイボルグ
				set '@delid,1474;
				set '@getid,1480;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			case 11: //シュバイチェルサーベル
				set '@delid,1167;
				set '@getid,1178;
				set '@need,984;
				set '@amount,2;
				set '@zeny,500000;
				break;
			}
		}
		else {
			switch(select("海賊の頭巾","黒革のブーツ","特殊忍者スーツ")) {
			case 1: //海賊の頭巾
				set '@delid,2287;
				set '@getid,5350;
				set '@need,985;
				set '@amount,1;
				set '@zeny,500000;
				break;
			case 2: //黒革のブーツ
				set '@delid,2425;
				set '@getid,2434;
				set '@need,985;
				set '@amount,1;
				set '@zeny,500000;
				break;
			case 3: //特殊忍者スーツ
				set '@delid,15053;
				set '@getid,15056;
				set '@need,985;
				set '@amount,1;
				set '@zeny,500000;
				break;
			}
		}
		break;
	case 4:
		mes "[レアブルレム]";
		mes "え……S級ですか！";
		mes "……どの" +'@equip$+ "ですか？";
		next;
		if('@equip$ == "武器") {
			switch(select("ゼピュロス","メイルブレイカー","ドラゴンスレイヤー","ソードブレイカー","アサシンダガー","グランドクロス","エクスキューショナー")) {
			case 1: //ゼピュロス
				set '@delid,1468;
				set '@getid,1481;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 2: //メイルブレイカー
				set '@delid,1225;
				set '@getid,13032;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 3: //ドラゴンスレイヤー
				set '@delid,1166;
				set '@getid,1180;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 4: //ソードブレイカー
				set '@delid,1224;
				set '@getid,13031;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 5: //アサシンダガー
				set '@delid,1232;
				set '@getid,13033;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 6: //グランドクロス
				set '@delid,1528;
				set '@getid,1540;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			case 7: //エクスキューショナー
				set '@delid,1169;
				set '@getid,1179;
				setarray '@need,984,999;
				setarray '@amount,5,10;
				set '@zeny,1000000;
				break;
			}
		}
		else {
			switch(select("マジックコート","ホーリーローブ","神の使者","ランニングシャツ","ブリーフ")) {
			case 1: //マジックコート
				set '@delid,2334;
				set '@getid,2372;
				set '@need,985;
				set '@amount,1;
				set '@zeny,1000000;
				break;
			case 2: //ホーリーローブ
				set '@delid,2327;
				set '@getid,2373;
				set '@need,985;
				set '@amount,1;
				set '@zeny,1000000;
				break;
			case 3: //神の使者
				set '@delid,2111;
				set '@getid,2128;
				set '@need,985;
				set '@amount,1;
				set '@zeny,1000000;
				break;
			case 4: //ランニングシャツ
				set '@delid,2522;
				set '@getid,2523;
				set '@need,985;
				set '@amount,1;
				set '@zeny,1000000;
				break;
			case 5: //ブリーフ
				set '@delid,2339;
				set '@getid,2371;
				set '@need,985;
				set '@amount,1;
				set '@zeny,1000000;
				break;
			}
		}
		break;
	}
	mes "[レアブルレム]";
	mes getitemname('@delid)+ "ですか。";
	mes "手数料は^FF0000" +'@zeny/10000+ "万Zeny^000000、";
	if('@amount[1]) {
		mes "材料は" +getitemname('@need[0])+'@amount[0]+ "個^000000、";
		mes "^FF0000" +getitemname('@need[1])+'@amount[1]+ "個^000000です。";
	}
	else
		mes "材料は" +getitemname('@need)+'@amount+ "個^000000です。";
	mes "もちろん、" +getitemname('@delid)+ " [" +getiteminfo('@delid,10)+ "]も必要です。";
	next;
	mes "[レアブルレム]";
	mes "なお、注意点として";
	mes "スロットエンチャントを行うと";
	mes "成否に関わらず材料は全て消滅します。";
	mes "また、例え成功したとしても";
	mes "精錬・カード・属性等の付与効果は";
	mes "全て消滅します。";
	next;
	if(select("スロットエンチャントを頼む","話をやめる")==2) {
		mes "[レアブルレム]";
		mes "また来てください。";
		close;
	}
	if((countitem('@delid[0]) < 1 && countitem('@delid[1]) < 1) || Zeny < '@zeny) {
		mes "[レアブルレム]";
		mes "材料かお金が足りませんよ？";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1) {
		if(countitem('@need['@i]) < '@amount['@i]) {
			mes "[レアブルレム]";
			mes "材料かお金が足りませんよ？";
			close;
		}
	}
	if(countitem('@delid))
		delitem '@delid,1;
	else
		delitem '@delid[1],1;
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1)
		delitem '@need['@i],'@amount['@i];
	set Zeny,Zeny-'@zeny;
	switch('@class) {
		case 1: set '@success,25; break; //C級
		case 2: set '@success,20; break; //B級
		case 3: set '@success,20; break; //A級
		case 4: set '@success,10; break; //S級
	}
	if(rand(100) < '@success) {
		if('@class == 4)
			misceffect 90;
		else
			misceffect 83;
		mes "[レアブルレム]";
		mes "OK、成功しました。";
		mes "おめでとうございます。";
		getitem '@getid,1;
	}
	else {
		misceffect 183;
		mes "[レアブルレム]";
		mes "う……失敗です。";
		mes "どうやら運が無かったようです。";
		mes "……そう落ち込まないでください。";
		mes "今度はきっと成功しますよ。";
	}
	next;
	mes "[レアブルレム]";
	mes "それでは、またご利用ください。";
	close;
}

prontera.gat,244,169,5	duplicate(レアブルレム#slot)	レアブルレム	86
moc_ruins.gat,154,86,3	duplicate(レアブルレム#slot)	レアブルレム	86
payon.gat,236,199,3	duplicate(レアブルレム#slot)	レアブルレム	86
lighthalzen.gat,96,137,3	duplicate(レアブルレム#slot)	レアブルレム	86

//==================================================
// プロブルレム
//==================================================
prontera.gat,81,106,6	script	プロブルレム	97,{
	mes "[プロブルレム]";
	mes "私は異世界の技術を使い";
	mes "防具にスロットエンチャントが";
	mes "できる技術者です。";
	mes "スロットエンチャントとは、";
	mes "装備品にスロットを追加する";
	mes "技術の事です。";
	next;
	mes "[プロブルレム]";
	mes "二人の兄に指導してもらった技術と";
	mes "独自に入手した異世界の技術を融合し";
	mes "非常に高度なスロットエンチャントに";
	mes "成功する事が出来ました。";
	next;
	mes "[プロブルレム]";
	mes "あまりにも危険な技術の為、";
	mes "二人の兄は反対しましたが";
	mes "私はこのスロットエンチャントを";
	mes "もっと世界に広めて";
	mes "有効に使って欲しいと思っています。";
	next;
	mes "[プロブルレム]";
	mes "もし、武器に対して";
	mes "スロットを追加したかったら";
	mes "双子の兄のアラブルレムに";
	mes "頼んで見てください。";
	next;
	mes "[プロブルレム]";
	mes "さて、スロットを追加したい";
	mes "防具はありますか？";
	mes "品によって、手数料や必要な材料、";
	mes "成功率が違いますのでご注意を。";
	next;
	switch(select("防具を選ぶ","説明を詳しく聞く","話をやめる")) {
	case 1:
		mes "[プロブルレム]";
		mes "手数料や材料などによって";
		mes "4段級に分かれています。";
		mes "まず、スロットを追加したいアイテムの";
		mes "階級を選んで下さい。";
		next;
		set '@class,select("C級","B級","A級","S級","やめる");
		switch('@class) {
			case 1:	//C級
				mes "[プロブルレム]";
				mes "わかりました。";
				mes "C級のどの防具にしますか？";
				next;
				switch(select("ゴヴニュの軍靴","マグニキャップ","フレイシューズ","駆魔の聖書","やめる")) {
					case 1:	//ゴヴニュの軍靴
						set '@delid,2419;
						set '@getid,2493;
						set '@need,999;
						set '@amount,10;
						set '@price,50000;
						break;
					case 2:	//マグニキャップ
						set '@delid,5122;
						set '@getid,18594;
						set '@need,999;
						set '@amount,30;
						set '@price,100000;
						break;
					case 3:	//フレイシューズ
						set '@delid,2417;
						set '@getid,2488;
						set '@need,999;
						set '@amount,50;
						set '@price,200000;
						break;
					case 4:	//駆魔の聖書
						set '@delid,2129;
						set '@getid,2166;
						set '@need,999;
						set '@amount,50;
						set '@price,200000;
						break;
					case 5:	//やめる
						mes "[プロブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 2:	//B級
				mes "[プロブルレム]";
				mes "わかりました。";
				mes "B級のどの防具にしますか？";
				next;
				switch(select("シャドウウォーカー","ぼろマント","クリティカルリング","やめる")) {
					case 1:	//シャドウウォーカー
						set '@delid,2426;
						set '@getid,2486;
						set '@need,985;
						set '@amount,15;
						set '@price,400000;
						break;
					case 2:	//ぼろマント
						set '@delid,2508;
						set '@getid,2588;
						set '@need,985;
						set '@amount,20;
						set '@price,500000;
						break;
					case 3:	//クリティカルリング
						set '@delid,2616;
						set '@getid,2943;
						set '@need,985;
						set '@amount,20;
						set '@price,500000;
						break;
					case 4:	//やめる
						mes "[プロブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 3:	//A級
				mes "[プロブルレム]";
				mes "わかりました。";
				mes "A級のどの防具にしますか？";
				next;
				switch(select("ヴィダルのブーツ","セフィロトシューズ","モリガンのベルト","モルフェウスの腕輪","ゴヴニュの肩飾り","やめる")) {
					case 1:	//ヴィダルのブーツ
						set '@delid,2418;
						set '@getid,2489;
						set '@need,985;
						set '@amount,30;
						set '@price,700000;
						break;
					case 2:	//セフィロトシューズ
						set '@delid,2450;
						set '@getid,2487;
						set '@need,985;
						set '@amount,30;
						set '@price,700000;
						break;
					case 3:	//モリガンのベルト
						set '@delid,2650;
						set '@getid,2900;
						set '@need,985;
						set '@amount,50;
						set '@price,800000;
						break;
					case 4:	//モルフェウスの腕輪
						set '@delid,2649;
						set '@getid,2903;
						set '@need,985;
						set '@amount,50;
						set '@price,800000;
						break;
					case 5:	//ゴヴニュの肩飾り
						set '@delid,2520;
						set '@getid,2599;
						set '@need,985;
						set '@amount,50;
						set '@price,800000;
						break;
					case 6:	//やめる
						mes "[プロブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 4:	//S級
				mes "[プロブルレム]";
				mes "わかりました。";
				mes "S級のどの防具にしますか？";
				next;
				switch(select("モリガンのペンダント","モルフェウスの指輪","ガラスの靴","エベシ嵐のうねり","クレイトス大地の裂け目","シャピニハ海の叫び","ルシウス火山の激しさ","ルーンブーツ","やめる")) {
					case 1:	//モリガンのペンダント
						set '@delid,2651;
						set '@getid,2901;
						set '@need,6223;
						set '@amount,1;
						set '@price,1000000;
						break;
					case 2:	//モルフェウスの指輪
						set '@delid,2648;
						set '@getid,2902;
						set '@need,6223;
						set '@amount,1;
						set '@price,1000000;
						break;
					case 3:	//ガラスの靴
						set '@delid,2407;
						set '@getid,2494;
						set '@need,6223;
						set '@amount,1;
						set '@price,1000000;
						break;
					case 4:	//エベシ嵐のうねり
						set '@delid,2348;
						set '@getid,2349;
						set '@need,6223;
						set '@amount,2;
						set '@price,2000000;
						break;
					case 5:	//クレイトス大地の裂け目
						set '@delid,2350;
						set '@getid,2351;
						set '@need,6223;
						set '@amount,2;
						set '@price,2000000;
						break;
					case 6:	//シャピニハ海の叫び
						set '@delid,2346;
						set '@getid,2347;
						set '@need,6223;
						set '@amount,2;
						set '@price,2000000;
						break;
					case 7:	//ルシウス火山の激しさ
						set '@delid,2344;
						set '@getid,2345;
						set '@need,6223;
						set '@amount,2;
						set '@price,2000000;
						break;
					case 8:	//ルーンブーツ
						set '@delid,2481;
						set '@getid,2490;
						set '@need,969;
						set '@amount,1;
						set '@price,3000000;
						break;
					case 9:	//やめる
						mes "[プロブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 5:	//やめる
				mes "[プロブルレム]";
				mes "わかりました。";
				mes "もし興味がわきましたら";
				mes "またお越しください。";
				close;
		}
		mes "[プロブルレム]";
		mes "^3355FF" +getitemname('@delid)+ "^000000ですね。";
		mes "ではご確認します。";
		mes "　";
		mes "まず、手数料として^3355FF" +'@price+ "Zeny^000000と";
		mes "^3355FF" +getitemname('@need)+ "^000000を^3355FF" +'@amount+ "個^000000いただきます。";
		next;
		mes "[プロブルレム]";
		mes "そして、エンチャントは";
		mes "必ずしも成功するとは限りません。";
		mes "^FF0000失敗すると、防具は消えてしまいます。^000000";
		mes "また、成功すると、今までの";
		mes "^FF0000精錬値及び挿していたカードが^000000";
		mes "^FF0000消えてしまいます。";
		next;
		mes "[プロブルレム]";
		mes "エンチャントを行いますか？";
		next;
		if(select("^FF0000今回はやめておく^000000","^3355FFお願いします^000000") == 1) {
			mes "[プロブルレム]";
			mes "わかりました。";
			mes "もし興味がわきましたら";
			mes "またお越しください。";
			close;
		}
		if(countitem('@delid) < 1 || countitem('@need) < '@amount || Zeny < '@price) {
			mes "[プロブルレム]";
			mes "材料かお金が足りませんよ？";
			close;
		}
		delitem '@delid,1;
		delitem '@need,'@amount;
		set Zeny,Zeny-'@price;
		switch('@class) {
			case 1: set '@success,25; break; //C級
			case 2: set '@success,20; break; //B級
			case 3: set '@success,15; break; //A級
			case 4: set '@success,10; break; //S級
		}
		if(rand(100) < '@success) {
			if('@class == 4)
				misceffect 90;
			else
				misceffect 83;
			mes "[プロブルレム]";
			mes "OK、成功しました。";
			mes "おめでとうございます。";
			getitem '@getid,1;
		}
		else {
			misceffect 183;
			mes "[プロブルレム]";
			mes "う……失敗です。";
			mes "どうやら運が無かったようです。";
			mes "……そう落ち込まないでください。";
			mes "今度はきっと成功しますよ。";
		}
		next;
		mes "[プロブルレム]";
		mes "それでは、またご利用ください。";
		close;
	case 2:
		mes "[プロブルレム]";
		mes "スロットエンチャントとは、";
		mes "装備品にスロットを追加する技術。";
		mes "成否に関わらず材料は全て消滅します。";
		next;
		mes "[プロブルレム]";
		mes "また、例え成功したとしても";
		mes "精錬・カード・属性、";
		mes "ヒドゥンスロットエンチャント等の";
		mes "付与効果は全て消滅します。";
		next;
		mes "[プロブルレム]";
		mes "さらに、一部の装備品だけですが";
		mes "スロットが同時に複数追加されたり、";
		mes "基本性能が変化する物があります。";
		next;
		mes "[プロブルレム]";
		mes "そして、気をつけなければならない点が";
		mes "一つあります。";
		mes "例えば……「+7マント [0]」と";
		mes "ただの「マント [0]」を持って、";
		mes "私にスロットエンチャントを依頼すると";
		mes "どちらが対象になると思いますか？";
		next;
		mes "[プロブルレム]";
		mes "正解はわからない……";
		mes "つまり、対象のアイテムが";
		mes "どういった物か、私は一切";
		mes "気にせずに作業するという事です。";
		next;
		mes "[プロブルレム]";
		mes "^FF0000スロット数以外は、^000000";
		mes "^FF0000一切関係ありません。^000000";
		mes "^FF0000例え未鑑定だろうが、^000000";
		mes "^FF0000破損していようが、^000000";
		mes "^FF0000スロットエンチャントを行います。^000000";
		next;
		mes "[プロブルレム]";
		mes "^FF0000しかし、誰かが作った製造品だと^000000";
		mes "^FF0000スロットの数に関係なく^000000";
		mes "^FF0000スロットエンチャントの^000000";
		mes "^FF0000対象アイテムとなります。^000000";
		next;
		mes "[プロブルレム]";
		mes "^FF0000特定のアイテムだけに^000000";
		mes "^FF0000スロットエンチャントを^000000";
		mes "^FF0000行いたいのなら、同じ名前の^000000";
		mes "^FF0000アイテムを倉庫にでも^000000";
		mes "^FF0000預けておいた方がいいです。^000000";
		next;
		mes "[プロブルレム]";
		mes "この事を忘れ、別のアイテムが";
		mes "スロットエンチャントの対象になっても";
		mes "私は一切責任を取りません。";
		mes "十分に注意してください。";
		next;
		mes "[プロブルレム]";
		mes "他に説明する事は特にありません。";
		mes "百聞は一見にしかず。";
		mes "まずはスロットエンチャントに";
		mes "挑戦してみたらどうですか？";
		close;
	case 3:
		mes "[プロブルレム]";
		mes "そうですか……";
		close;
	}
}

//==================================================
// アラブルレム
//==================================================
prontera.gat,79,104,6	script	アラブルレム	97,{
	mes "[アラブルレム]";
	mes "私は異世界の技術を使い";
	mes "武器にスロットエンチャントが";
	mes "できる技術者です。";
	mes "スロットエンチャントとは、";
	mes "装備品にスロットを追加する";
	mes "技術の事です。";
	next;
	mes "[アラブルレム]";
	mes "二人の兄に指導してもらった技術と";
	mes "独自に入手した異世界の技術を融合し";
	mes "非常に高度なスロットエンチャントに";
	mes "成功する事が出来ました。";
	next;
	mes "[アラブルレム]";
	mes "あまりにも危険な技術の為、";
	mes "二人の兄は反対しましたが";
	mes "私はこのスロットエンチャントを";
	mes "もっと世界に広めて";
	mes "有効に使って欲しいと思っています。";
	next;
	mes "[アラブルレム]";
	mes "もし、防具に対して";
	mes "スロットを追加したかったら";
	mes "双子の弟のプロブルレムに";
	mes "頼んで見てください。";
	next;
	mes "[アラブルレム]";
	mes "さて、スロットを追加したい";
	mes "武器はありますか？";
	mes "品によって、手数料や必要な材料、";
	mes "成功率が違いますのでご注意を。";
	next;
	switch(select("武器を選ぶ","説明を詳しく聞く","話をやめる")) {
	case 1:
		mes "[アラブルレム]";
		mes "手数料や材料などによって";
		mes "4段級に分かれています。";
		mes "まず、スロットを追加したいアイテムの";
		mes "階級を選んで下さい。";
		next;
		set '@class,select("C級","B級","A級","S級","やめる");
		switch('@class) {
			case 1:	//C級
				mes "[アラブルレム]";
				mes "わかりました。";
				mes "C級のどの武器にしますか？";
				next;
				switch(select("骸骨の杖","オーキッシュソード","ファイアーブランド","アイスファルシオン","治癒の杖","やめる")) {
					case 1:	//骸骨の杖
						set '@delid,1615;
						set '@getid,1662;
						set '@need,999;
						set '@amount,30;
						set '@price,100000;
						break;
					case 2:	//オーキッシュソード
						set '@delid,1124;
						set '@getid,13437;
						set '@need,999;
						set '@amount,30;
						set '@price,100000;
						break;
					case 3:	//ファイアーブランド
						set '@delid,1133;
						set '@getid,13435;
						set '@need,999;
						set '@amount,50;
						set '@price,200000;
						break;
					case 4:	//アイスファルシオン
						set '@delid,1131;
						set '@getid,13436;
						set '@need,999;
						set '@amount,50;
						set '@price,200000;
						break;
					case 5:	//治癒の杖
						set '@delid,1625;
						set '@getid,1666;
						set '@need,999;
						set '@amount,50;
						set '@price,200000;
						break;
					case 6:	//やめる
						mes "[アラブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 2:	//B級
				mes "[アラブルレム]";
				mes "わかりました。";
				mes "B級のどの武器にしますか？";
				next;
				switch(select("ネメシス","ドラゴンの遺産","カウンターダガー","アイボリーナイフ","ブラディウムハンマー","やめる")) {
					case 1:	//ネメシス
						set '@delid,1541;
						set '@getid,16022;
						set '@need,984;
						set '@amount,3;
						set '@price,300000;
						break;
					case 2:	//ドラゴンの遺産
						set '@delid,1559;
						set '@getid,1589;
						set '@need,984;
						set '@amount,3;
						set '@price,300000;
						break;
					case 3:	//カウンターダガー
						set '@delid,1242;
						set '@getid,13073;
						set '@need,984;
						set '@amount,5;
						set '@price,400000;
						break;
					case 4:	//アイボリーナイフ
						set '@delid,13039;
						set '@getid,13082;
						set '@need,984;
						set '@amount,5;
						set '@price,400000;
						break;
					case 5:	//ブラディウムハンマー
						set '@delid,1385;
						set '@getid,1397;
						set '@need,984;
						set '@amount,10;
						set '@price,500000;
						break;
					case 6:	//やめる
						mes "[アラブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 3:	//A級
				mes "[アラブルレム]";
				mes "わかりました。";
				mes "A級のどの武器にしますか？";
				next;
				switch(select("スタッフオブオルド","インバーススケイル","ブラッディティアーズ","ディバインクロス","スタッフオブピアーシング","やめる")) {
					case 1:	//スタッフオブオルド
						set '@delid,1648;
						set '@getid,1663;
						set '@need,6224;
						set '@amount,5;
						set '@price,700000;
						break;
					case 2:	//インバーススケイル
						set '@delid,1269;
						set '@getid,1297;
						set '@need,6224;
						set '@amount,5;
						set '@price,700000;
						break;
					case 3:	//ブラッディティアーズ
						set '@delid,1271;
						set '@getid,1295;
						set '@need,6224;
						set '@amount,10;
						set '@price,800000;
						break;
					case 4:	//ディバインクロス
						set '@delid,2001;
						set '@getid,2017;
						set '@need,6224;
						set '@amount,10;
						set '@price,800000;
						break;
					case 5:	//スタッフオブピアーシング
						set '@delid,1626;
						set '@getid,1665;
						set '@need,6224;
						set '@amount,10;
						set '@price,800000;
						break;
					case 6:	//やめる
						mes "[アラブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 4:	//S級
				mes "[アラブルレム]";
				mes "わかりました。";
				mes "S級のどの武器にしますか？";
				next;
				switch(select("村正","アルカブリンガー","カドリール","茨の杖","オークアーチャーの弓","やめる")) {
					case 1:	//村正
						set '@delid,1164;
						set '@getid,21003;
						set '@need,6224;
						set '@amount,15;
						set '@price,1000000;
						break;
					case 2:	//アルカブリンガー
						set '@delid,1191;
						set '@getid,21004;
						set '@need,6224;
						set '@amount,15;
						set '@price,1000000;
						break;
					case 3:	//カドリール
						set '@delid,1527;
						set '@getid,16024;
						set '@need,6224;
						set '@amount,15;
						set '@price,1000000;
						break;
					case 4:	//茨の杖
						set '@delid,1636;
						set '@getid,1664;
						set '@need,6224;
						set '@amount,20;
						set '@price,2000000;
						break;
					case 5:	//オークアーチャーの弓
						set '@delid,1734;
						set '@getid,18115;
						set '@need,6224;
						set '@amount,20;
						set '@price,2000000;
						break;
					case 6:	//やめる
						mes "[アラブルレム]";
						mes "わかりました。";
						mes "もし興味がわきましたら";
						mes "またお越しください。";
						close;
				}
				break;
			case 5:	//やめる
				mes "[アラブルレム]";
				mes "わかりました。";
				mes "もし興味がわきましたら";
				mes "またお越しください。";
				close;
			}
		mes "[アラブルレム]";
		mes "^3355FF" +getitemname('@delid)+ "^000000ですね。";
		mes "ではご確認します。";
		mes "　";
		mes "まず、手数料として^3355FF" +'@price+ "Zeny^000000と";
		mes "^3355FF" +getitemname('@need)+ "^000000を^3355FF" +'@amount+ "個^000000いただきます。";
		next;
		mes "[アラブルレム]";
		mes "そして、エンチャントは";
		mes "必ずしも成功するとは限りません。";
		mes "^FF0000失敗すると、防具は消えてしまいます。^000000";
		mes "また、成功すると、今までの";
		mes "^FF0000精錬値及び挿していたカードが^000000";
		mes "^FF0000消えてしまいます。";
		next;
		mes "[アラブルレム]";
		mes "エンチャントを行いますか？";
		next;
		if(select("^FF0000今回はやめておく^000000","^3355FFお願いします^000000") == 1) {
			mes "[アラブルレム]";
			mes "わかりました。";
			mes "もし興味がわきましたら";
			mes "またお越しください。";
			close;
		}
		if(countitem('@delid) < 1 || countitem('@need) < '@amount || Zeny < '@price) {
			mes "[アラブルレム]";
			mes "材料かお金が足りませんよ？";
			close;
		}
		delitem '@delid,1;
		delitem '@need,'@amount;
		set Zeny,Zeny-'@price;
		switch('@class) {
			case 1: set '@success,25; break; //C級
			case 2: set '@success,20; break; //B級
			case 3: set '@success,15; break; //A級
			case 4: set '@success,10; break; //S級
		}
		if(rand(100) < '@success) {
			if('@class == 4)
				misceffect 90;
			else
				misceffect 83;
			mes "[アラブルレム]";
			mes "OK、成功しました。";
			mes "おめでとうございます。";
			getitem '@getid,1;
		}
		else {
			misceffect 183;
			mes "[アラブルレム]";
			mes "う……失敗です。";
			mes "どうやら運が無かったようです。";
			mes "……そう落ち込まないでください。";
			mes "今度はきっと成功しますよ。";
		}
		next;
		mes "[アラブルレム]";
		mes "それでは、またご利用ください。";
		close;
	case 2:
		mes "[アラブルレム]";
		mes "スロットエンチャントとは、";
		mes "装備品にスロットを追加する技術。";
		mes "成否に関わらず材料は全て消滅します。";
		next;
		mes "[アラブルレム]";
		mes "また、例え成功したとしても";
		mes "精錬・カード・属性、";
		mes "ヒドゥンスロットエンチャント等の";
		mes "付与効果は全て消滅します。";
		next;
		mes "[アラブルレム]";
		mes "さらに、一部の装備品だけですが";
		mes "スロットが同時に複数追加されたり、";
		mes "基本性能が変化する物があります。";
		next;
		mes "[アラブルレム]";
		mes "そして、気をつけなければならない点が";
		mes "一つあります。";
		mes "例えば……「+7マント [0]」と";
		mes "ただの「マント [0]」を持って、";
		mes "私にスロットエンチャントを依頼すると";
		mes "どちらが対象になると思いますか？";
		next;
		mes "[アラブルレム]";
		mes "正解はわからない……";
		mes "つまり、対象のアイテムが";
		mes "どういった物か、私は一切";
		mes "気にせずに作業するという事です。";
		next;
		mes "[アラブルレム]";
		mes "^FF0000スロット数以外は、^000000";
		mes "^FF0000一切関係ありません。^000000";
		mes "^FF0000例え未鑑定だろうが、^000000";
		mes "^FF0000破損していようが、^000000";
		mes "^FF0000スロットエンチャントを行います。^000000";
		next;
		mes "[アラブルレム]";
		mes "^FF0000しかし、誰かが作った製造品だと^000000";
		mes "^FF0000スロットの数に関係なく^000000";
		mes "^FF0000スロットエンチャントの^000000";
		mes "^FF0000対象アイテムとなります。^000000";
		next;
		mes "[アラブルレム]";
		mes "^FF0000特定のアイテムだけに^000000";
		mes "^FF0000スロットエンチャントを^000000";
		mes "^FF0000行いたいのなら、同じ名前の^000000";
		mes "^FF0000アイテムを倉庫にでも^000000";
		mes "^FF0000預けておいた方がいいです。^000000";
		next;
		mes "[アラブルレム]";
		mes "この事を忘れ、別のアイテムが";
		mes "スロットエンチャントの対象になっても";
		mes "私は一切責任を取りません。";
		mes "十分に注意してください。";
		next;
		mes "[アラブルレム]";
		mes "他に説明する事は特にありません。";
		mes "百聞は一見にしかず。";
		mes "まずはスロットエンチャントに";
		mes "挑戦してみたらどうですか？";
		close;
	case 3:
		mes "[アラブルレム]";
		mes "そうですか……";
		close;
	}
}
