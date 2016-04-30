//==============================================================================
// Ragnarok Online Diamond Gambling Script     by Chiffon
//==============================================================================
comodo.gat,219,158,6	script	カチュア	91,{
	cutin "katsua01",2;
	mes "[カチュア]";
	mes "以前に見た、あのとても大きな";
	mes "ダイヤモンド。きれいだったなー。";
	mes "あれは３カラットくらいかしら。";
	mes "すごく欲しいな……どうすれば";
	mes "手に入るのかしら？";
	next;
	if(select("あげましょうか？","元気を出してください")==2) {
		mes "[カチュア]";
		mes "慰めてくれてありがとう。";
		mes "ああー、もしそのダイヤモンドが";
		mes "手に入るのなら、私の大事な";
		mes "コレクションすら喜んで";
		mes "差し出すのに……";
		close2;
		cutin "katsua01",255;
		end;
	}
	if(countitem(732)<1) {
		cutin "katsua03",2;
		mes "[カチュア]";
		mes "ふん！";
		mes "本当はダイヤモンドを持って";
		mes "いないのに、どうして持っている";
		mes "かのような素振りをするの？";
		mes "私を馬鹿にするつもりですか？";
		close2;
		cutin "katsua03",255;
		end;
	}
	if((MaxWeight - Weight) < 5500) {
		mes "[カチュア]";
		mes "あら、そんなにたくさんの荷物が";
		mes "あると、お礼をお渡しできないわ。";
		mes "少し倉庫に預けてきてくださいね。";
		close2;
		cutin "katsua01",255;
		end;
	}
	cutin "katsua02",2;
	mes "[カチュア]";
	mes "ええっ?!";
	mes "本当にいいんですか？";
	mes "ありがとうございますー。";
	mes "ではお礼に、私のコレクションを";
	mes "一つ差し上げましょう。";
	next;
	mes "[カチュア]";
	mes "どちらをお望みでしょうか？";
	next;
	switch(select("武器","鎧","肩にかける物","兜","靴","盾")) {
	case 1:	//武器
		set '@gamble,rand(1000);
		if('@gamble >= 920 && '@gamble < 930) {
			set '@gamble,rand(85);
			switch('@gamble) {
				case 0: getitem 1128,1; break;	//海東剣[2]
				case 1: getitem 1120,1; break;	//ツルギ[2]
				case 2: getitem 1127,1; break;	//サーベル[3]
				case 3: getitem 1158,1; break;	//ツーハンドソード[2]
				case 4: getitem 1155,1; break;	//バスタードソード[3]
				case 5: getitem 1220,1; break;	//グラディウス[3]
				case 6: getitem 1226,1; break;	//ダマスカス[2]
				case 7: getitem 1253,1; break;	//カタール[2]
				case 8: getitem 1529,1; break;	//アイアンドライバー
				case 9: getitem 1251,1; break;	//ジュル[3]
				case 10: getitem 1361,1; break;	//ツーハンドアックス[2]
				case 11: getitem 1258,1; break;	//爆炎のカタール
				case 12: getitem 1257,1; break;	//尖ってるいばらのカタール
				case 13: getitem 1256,1; break;	//冷たい氷柱のカタール
				case 14: getitem 1259,1; break;	//疾風のカタール
				case 15: getitem 1260,1; break;	//デスナイフ
				case 16: getitem 1716,1; break;	//角弓[2]
				case 17: getitem 1715,1; break;	//アーバレスト[2]
				case 18: getitem 1711,1; break;	//クロスボウ[3]
				case 19: getitem 1702,1; break;	//ボウ[4]
				case 20: getitem 1520,1; break;	//チェイン[3]
				case 21: getitem 1611,1; break;	//アークワンド[2]
				case 22: getitem 1615,1; break;	//骸骨の杖
				case 23: getitem 1602,1; break;	//ロッド[4]
				case 24: getitem 1461,1; break;	//トライデント[3]
				case 25: getitem 1402,1; break;	//ジャベリン[4]
				case 26: getitem 1961,1; break;	//ホイップ[2]
				case 27: getitem 1957,1; break;	//ランテ[1]
				case 28: getitem 1552,1; break;	//タブレット[1]
				case 29: getitem 1551,1; break;	//バイブル[2]
				case 30: getitem 1553,1; break;	//荒れ狂う波の書
				case 31: getitem 1554,1; break;	//裂けた大地の書
				case 32: getitem 1555,1; break;	//燃える太陽の書
				case 33: getitem 1556,1; break;	//乾いてる風の書
				case 34: getitem 1951,1; break;	//ロープ[4]
				case 35: getitem 1959,1; break;	//テイル[2]
				case 36: getitem 1953,1; break;	//ライン[3]
				case 37: getitem 1955,1; break;	//ワイヤー[3]
				case 38: getitem 1810,1; break;	//クロー[2]
				case 39: getitem 1910,1; break;	//ハープ[2]
				case 40: getitem 1906,1; break;	//リュート[3]
				case 41: getitem 1902,1; break;	//バイオリン[4]
				case 42: getitem 1904,1; break;	//マンドリン[3]
				case 43: getitem 1912,1; break;	//ゴムンゴ[2]
				case 44: getitem 1908,1; break;	//ギター[1]
				case 45: getitem 1808,1; break;	//フィスト[1]
				case 46: getitem 1802,1; break;	//バグナウ[4]
				case 47: getitem 1812,1; break;	//フィンガー[2]
				case 48: getitem 1806,1; break;	//ホラ[3]
				case 49: getitem 1804,1; break;	//ナックルダスター[3]
				case 50: getitem 1550,1; break;	//ブック[3]
				case 51: getitem 1246,1; break;	//チンクエディア[2]
				case 52: getitem 1147,1; break;	//タウンソード[2]
				case 53:
				case 54: getitem 1264,1; break;	//バリアスジュル[4]
				case 55:
				case 56: getitem 1262,1; break;	//ロキの爪
				case 57:
				case 58: getitem 1622,1; break;	//催眠術師の杖[2]
				case 59: getitem 1723,1; break;	//ルナボウ
				case 60:
				case 61: getitem 1965,1; break;	//紅炎の鞭
				case 62:
				case 63: getitem 1966,1; break;	//氷剣の鞭
				case 64:
				case 65: getitem 1967,1; break;	//大地の鞭
				case 66:
				case 67: getitem 1968,1; break;	//なわとび
				case 68:
				case 69: getitem 1914,1; break;	//燃える情熱のギター
				case 70:
				case 71: getitem 1915,1; break;	//孤独なソロのギター
				case 72:
				case 73: getitem 1916,1; break;	//広大な大地のギター
				case 74:
				case 75: getitem 1917,1; break;	//柔らかなそよ風のギター
				case 76:
				case 77: getitem 13004,1; break;	//コワード[2]
				case 78:
				case 79: getitem 1307,1; break;	//ウィンドホーク
				case 80: getitem 1560,1; break;	//賢者の日記[2]
				case 81: getitem 1618,1; break;	//サバイバルロッド[1]
				case 82: getitem 1620,1; break;	//サバイバルロッド[1]
				case 83:
				case 84: getitem 1971,1; break;	//電気線
			}
		}
		else if('@gamble >= 0 && '@gamble < 200)
			getitem 1201,1;		//ナイフ[3]
		else if('@gamble >= 200 && '@gamble < 300)
			getitem 1101,1;		//ソード[3]
		else if('@gamble >= 300 && '@gamble < 400)
			getitem 1601,1;		//ロッド[3]
		else if('@gamble >= 400 && '@gamble < 500)
			getitem 1116,1;		//カタナ[3]
		else if('@gamble >= 500 && '@gamble < 600)
			getitem 1250,1;		//ジュル[2]
		else if('@gamble >= 600 && '@gamble < 700)
			getitem 1301,1;		//アックス[3]
		else if('@gamble >= 700 && '@gamble < 800)
			getitem 1701,1;		//ボウ[3]
		else if('@gamble >= 800 && '@gamble < 850)
			getitem 1504,1;		//メイス[3]
		else if('@gamble >= 850 && '@gamble < 900)
			getitem 1604,1;		//ワンド[2]
		else if('@gamble >= 900 && '@gamble < 910)
			getitem 1108,1;		//ブレイド[4]
		else if('@gamble >= 910 && '@gamble < 920)
			getitem 1163,1;		//クレイモア
		else if('@gamble >= 930 && '@gamble < 960)
			getitem 1522,1;		//スタナー
		else if('@gamble >= 960 && '@gamble < 970)
			getitem 1608,1;		//スタッフ[3]
		else if('@gamble >= 970 && '@gamble < 980)
			getitem 1408,1;		//パイク[4]
		else if('@gamble >= 980 && '@gamble < 990)
			getitem 1452,1;		//ギザルム[3]
		else
			getitem 1208,1;		//マインゴーシュ[4]
		break;
	case 2:	//鎧
		set '@gamble,rand(500);
		if('@gamble >= 299 && '@gamble < 302) {
			set '@gamble,rand(15);
			switch('@gamble) {
				case 0: getitem 2315,1; break;	//メイル[1]
				case 1: getitem 2336,1; break;	//シーフクロース[1]
				case 2: getitem 2318,1; break;	//ロードクロース[1]
				case 3: getitem 2326,1; break;	//セイントローブ[1]
				case 4: getitem 2327,1; break;	//ホーリーローブ
				case 5: getitem 2342,1; break;	//フルプレート[1]
				case 6: getitem 2331,1; break;	//タイツ[1]
				case 7: getitem 2342,1; break;	//フルプレート[1]
				case 8: getitem 2311,1; break;	//ミンクのコート[1]
				case 9: getitem 2320,1; break;	//フォーマルスーツ[1]
				case 10: getitem 2319,1; break;	//グリッタリングクロース[1]
				case 11: getitem 2344,1; break;	//ルシウス火山の激しさ
				case 12: getitem 2346,1; break;	//シャピニハ海の叫び
				case 13: getitem 2348,1; break;	//エベシ嵐のうねり
				case 14: getitem 2350,1; break;	//クレイトス大地の裂け目
			}
		}
		else if('@gamble >= 0 && '@gamble < 50)
			getitem 2301,1;		//コットンシャツ
		else if('@gamble >= 50 && '@gamble < 100)
			getitem 2302,1;		//コットンシャツ[1]
		else if('@gamble >= 100 && '@gamble < 150)
			getitem 2303,1;		//レザージャケット
		else if('@gamble >= 150 && '@gamble < 200)
			getitem 2304,1;		//レザージャケット[1]
		else if('@gamble >= 200 && '@gamble < 250)
			getitem 2305,1;		//アドベンチャースーツ
		else if('@gamble >= 250 && '@gamble < 299)
			getitem 2301,1;		//コットンシャツ
		else if('@gamble >= 302 && '@gamble < 350)
			getitem 2307,1;		//メントル
		else if('@gamble >= 350 && '@gamble < 400)
			getitem 2309,1;		//ロングコート
		else if('@gamble == 400)
			getitem 2322,1;		//シルクローブ[1]
		else if('@gamble == 401)
			getitem 2310,1;		//ロングコート[1]
		else if('@gamble >= 402 && '@gamble < 410)
			getitem 2306,1;		//アドベンチャースーツ[1]
		else if('@gamble >= 410 && '@gamble < 415)
			getitem 2308,1;		//メントル[1]
		else if('@gamble >= 415 && '@gamble < 420)
			getitem 2313,1;		//アーマー[1]
		else if('@gamble >= 420 && '@gamble < 425)
			getitem 2337,1;		//忍者スーツ
		else if('@gamble >= 425 && '@gamble < 430)
			getitem 2341,1;		//フルプレート
		else if('@gamble >= 430 && '@gamble < 435)
			getitem 2325,1;		//セイントローブ
		else if('@gamble >= 435 && '@gamble < 440)
			getitem 2316,1;		//プレート
		else if('@gamble >= 440 && '@gamble < 445)
			getitem 2330,1;		//タイツ
		else if('@gamble >= 445 && '@gamble < 450)
			getitem 2314,1;		//メイル
		else if('@gamble >= 450 && '@gamble < 455)
			getitem 2335,1;		//シーフクロース
		else if('@gamble >= 455 && '@gamble < 460)
			getitem 2324,1;		//スケーピューラ[1]
		else if('@gamble >= 460 && '@gamble < 465)
			getitem 2329,1;		//ウドゥンメイル[1]
		else if('@gamble >= 465 && '@gamble < 470)
			getitem 2340,1;		//初心者用胸当て[1]
		else if('@gamble >= 470 && '@gamble < 475)
			getitem 2312,1;		//アーマー
		else if('@gamble >= 475 && '@gamble < 480)
			getitem 2339,1;		//ブリーフ
		else if('@gamble >= 480 && '@gamble < 485)
			getitem 2328,1;		//ウドゥンメイル
		else if('@gamble >= 485 && '@gamble < 490)
			getitem 2321,1;		//シルクローブ
		else
			getitem 2323,1;		//スケーピューラ
		break;
	case 3:	//肩にかける物
		set '@gamble,rand(500);
		if('@gamble >= 200 && '@gamble < 203) {
			set '@gamble,rand(16);
			switch('@gamble) {
				case 0:
				case 1: getitem 2506,1; break;	//マント[1]
				case 2:
				case 3: getitem 2504,1; break;	//マフラー[1]
				case 4:
				case 5:
				case 6: getitem 2508,1; break;	//ぼろマント
				case 7:
				case 8:
				case 9: getitem 2507,1; break;	//昔の領主のマント
				case 10: getitem 2513,1; break;	//天女の羽衣[1]
				case 11: getitem 2514,1; break;	//ポールドロン[1]
				case 12:
				case 13: getitem 2523,1; break;	//ランニングシャツ[1]
				case 14: getitem 2509,1; break;	//サバイバルマント
				case 15: getitem 2515,1; break;	//ウィングオブイーグル[1]
			}
		}
		else if('@gamble >= 0 && '@gamble < 100)
			getitem 2503,1;		//マフラー
		else if('@gamble >= 100 && '@gamble < 200)
			getitem 2505,1;		//マント
		else if('@gamble >= 203 && '@gamble < 450)
			getitem 2501,1;		//フード
		else
			getitem 2502,1;		//フード[1]
		break;
	case 4:	//兜
		set '@gamble,rand(1000);
		if('@gamble >= 299 && '@gamble < 304) {
			set '@gamble,rand(93);
			switch('@gamble) {
				case 0:
				case 1: getitem 2251,1; break;	//聖職者の帽子
				case 2:
				case 3: getitem 2285,1; break;	//名射手のりんご
				case 4:
				case 5: getitem 2255,1; break;	//悪魔のヘアバンド
				case 6:
				case 7: getitem 5045,1; break;	//シルクハット
				case 8:
				case 9: getitem 2233,1; break;	//サークレット[1]
				case 10:
				case 11: getitem 2231,1; break;	//ジュエルヘルム[1]
				case 12:
				case 13: getitem 2217,1; break;	//ビレタ[1]
				case 14:
				case 15: getitem 2206,1; break;	//ヴェール
				case 16:
				case 17: getitem 2246,1; break;	//ゴールデンヘッドギア
				case 18:
				case 19: getitem 2261,1; break;	//プロンテラ軍帽
				case 20:
				case 21: getitem 2287,1; break;	//海賊の頭巾
				case 22:
				case 23: getitem 5012,1; break;	//学者帽
				case 24:
				case 25: getitem 2244,1; break;	//大きなリボン
				case 26:
				case 27: getitem 2213,1; break;	//猫耳のヘアバンド
				case 28:
				case 29: getitem 2248,1; break;	//ウェスタングレイス
				case 30:
				case 31: getitem 2223,1; break;	//丸いぼうし[1]
				case 32:
				case 33: getitem 2247,1; break;	//オールドスターロマンス
				case 34:
				case 35: getitem 2245,1; break;	//スイートジェントル
				case 36:
				case 37: getitem 5003,1; break;	//ピエロの帽子
				case 38:
				case 39: getitem 2225,1; break;	//ゴーグル[1]
				case 40:
				case 41: getitem 5017,1; break;	//ボーンヘルム
				case 42:
				case 43: getitem 5030,1; break;	//パンダ帽
				case 44:
				case 45: getitem 5035,1; break;	//ポリン帽
				case 46:
				case 47: getitem 2250,1; break;	//リボンのヘアバンド
				case 48:
				case 49: getitem 2277,1; break;	//看護帽
				case 50:
				case 51: getitem 5011,1; break;	//アンテナ
				case 52:
				case 53: getitem 2290,1; break;	//葬式用の帽子
				case 54:
				case 55: getitem 5010,1; break;	//インディアンのヘアバンド
				case 56:
				case 57: getitem 2259,1; break;	//プロペラ
				case 58:
				case 59: getitem 5008,1; break;	//仮初めの恋
				case 60:
				case 61: getitem 2249,1; break;	//コロネット
				case 62:
				case 63: getitem 2229,1; break;	//ヘルム[1]
				case 64: getitem 2258,1; break;	//シャープヘッドギア
				case 65: getitem 2274,1; break;	//亡者のヘアバンド
				case 66: getitem 5019,1; break;	//コルセア
				case 67: getitem 2254,1; break;	//天使のヘアバンド
				case 68: getitem 5007,1; break;	//ロードサークレット
				case 69: getitem 5066,1; break;	//サキュバスの角
				case 70: getitem 2235,1; break;	//クラウン
				case 71: getitem 2234,1; break;	//ティアラ
				case 72: getitem 2256,1; break;	//マジェスティックゴート
				case 73: getitem 5093,1; break;	//修道女のヴェール[1]
				case 74: getitem 5072,1; break;	//インキュバスの角
				case 75: getitem 5002,1; break;	//ジュエルクラウン
				case 76:
				case 77:
				case 78: getitem 5118,1; break;	//子犬のヘアバンド
				case 79:
				case 80:
				case 81: getitem 5120,1; break;	//やわらかい帽子
				case 82:
				case 83:
				case 84: getitem 5111,1; break;	//ガラパゴ帽
				case 85:
				case 86:
				case 87: getitem 5116,1; break;	//バナナの皮
				case 88:
				case 89:
				case 90: getitem 5119,1; break;	//スーパーノービス帽[1]
				case 91:
				case 92: getitem 5141,1; break;	//マリオネット人形[1]
			}
		}
		else if('@gamble >= 0 && '@gamble < 100)
			getitem 2226,1;		//キャップ
		else if('@gamble >= 100 && '@gamble < 200)
			getitem 2211,1;		//頭巾
		else if('@gamble >= 200 && '@gamble < 299)
			getitem 2209,1;		//リボン[1]
		else if('@gamble >= 304 && '@gamble < 400)
			getitem 2220,1;		//ハット
		else if('@gamble >= 400 && '@gamble < 500)
			getitem 2232,1;		//サークレット
		else if('@gamble >= 500 && '@gamble < 600)
			getitem 2216,1;		//ビレタ
		else if('@gamble >= 600 && '@gamble < 700)
			getitem 2230,1;		//ジュエルヘルム
		else if('@gamble >= 700 && '@gamble < 800)
			getitem 2224,1;		//ゴーグル
		else if('@gamble >= 800 && '@gamble < 900)
			getitem 2222,1;		//丸いぼうし
		else if('@gamble >= 900 && '@gamble < 905)
			getitem 2228,1;		//ヘルム
		else if('@gamble >= 905 && '@gamble < 910)
			getitem 2252,1;		//ウィザードハット
		else if('@gamble >= 910 && '@gamble < 915)
			getitem 2227,1;		//キャップ[1]
		else if('@gamble >= 915 && '@gamble < 920)
			getitem 2221,1;		//ハット[1]
		else if('@gamble >= 920 && '@gamble < 925)
			getitem 2299,1;		//オーク族のヘルム
		else if('@gamble >= 925 && '@gamble < 930)
			getitem 2236,1;		//サンタのぼうし
		else if('@gamble >= 930 && '@gamble < 935)
			getitem 2275,1;		//バンダナ
		else if('@gamble >= 935 && '@gamble < 940)
			getitem 5015,1;		//装飾用卵殻
		else if('@gamble >= 940 && '@gamble < 945)
			getitem 2215,1;		//花のヘアバンド
		else if('@gamble >= 945 && '@gamble < 950)
			getitem 5092,1;		//修道女のヴェール
		else
			getitem 2226,1;		//キャップ
		break;
	case 5:	//靴
		set '@gamble,rand(500);
		if('@gamble >= 299 && '@gamble < 303) {
			set '@gamble,rand(10);
			switch('@gamble) {
				case 0:
				case 1: getitem 2406,1; break;	//ブーツ[1]
				case 2:
				case 3: getitem 2412,1; break;	//グリーブ[1]
				case 4:
				case 5:
				case 6: getitem 2404,1; break;	//シューズ[1]
				case 7:
				case 8:
				case 9: getitem 2407,1; break;	//ガラスの靴
			}
		}
		else if('@gamble >= 0 && '@gamble < 200)
			getitem 2401,1;		//サンダル
		else if('@gamble >= 200 && '@gamble < 300)
			getitem 2408,1;		//足鎖
		else if('@gamble >= 303 && '@gamble < 350)
			getitem 2411,1;		//グリーブ
		else if('@gamble >= 350 && '@gamble < 400)
			getitem 2403,1;		//シューズ
		else if('@gamble >= 400 && '@gamble < 450)
			getitem 2405,1;		//ブーツ
		else if('@gamble >= 450 && '@gamble < 475)
			getitem 2409,1;		//ハイヒール
		else
			getitem 2402,1;		//サンダル[1]
		break;
	case 6:	//盾
		set '@gamble,rand(500);
		if('@gamble >= 200 && '@gamble < 204) {
			set '@gamble,rand(5);
			switch('@gamble) {
				case 0: getitem 2104,1; break;	//バックラー[1]
				case 1: getitem 2106,1; break;	//シールド[1]
				case 2: getitem 2102,1; break;	//ガード[1]
				case 3: getitem 2111,1; break;	//神の使者
				case 4: getitem 2109,1; break;	//メモライズブック
			}
		}
		else if('@gamble >= 0 && '@gamble < 200)
			getitem 2101,1;		//ガード
		else if('@gamble >= 204 && '@gamble < 300)
			getitem 2103,1;		//バックラー
		else if('@gamble >= 300 && '@gamble < 400)
			getitem 2107,1;		//ミラーシールド
		else if('@gamble >= 400 && '@gamble < 480)
			getitem 2105,1;		//シールド
		else
			getitem 2108,1;		//ミラーシールド[1]
		break;
	}
	delitem 732,1;
	mes "[カチュア]";
	mes "わあー、ダイヤモンドは";
	mes "とてもきれいでいいわよねー";
	mes "また欲しいわ……";
	close2;
	cutin "katsua02",255;
	end;
}

comodo.gat,204,148,7	script	ダビリン	90,{
	mes "[ダビリン]";
	mes "以前、旅行客がカチュア姉さんに";
	mes "とても大きなダイヤモンドを";
	mes "見せたことがあるの。";
	mes "その後、姉さんはずっと";
	mes "あんな風にダイヤモンドだけを";
	mes "追い求めてるんです。";
	next;
	mes "[ダビリン]";
	mes "姉さんはかなり執着心が強いので……";
	mes "ダイヤモンドを手に入れる為なら";
	mes "何でも……そう自分の大切な";
	mes "コレクションさえも差し出す";
	mes "つもりみたい。";
	next;
	mes "[ダビリン]";
	mes "姉さんは昔からコレクターだったの。";
	mes "お金さえあれば、すぐに気に入った物を";
	mes "買っていたわ。収集欲にとらわれて";
	mes "いつかお金を使い果たさないか……";
	mes "とてもそれが心配なの。";
	close;
}

comodo.gat,210,154,2	script	怪しい男	118,{
	if(getbaseclass(Class) == CLASS_TF) {
		mes "[ケイム]";
		mes "ほ～、同業者か。こんな所で会ったのも";
		mes "何かの縁だ。耳寄りの情報を教えて";
		mes "やろう。本来なら金をとるところだが、";
		mes "そこは同業者のよしみ、特別に";
		mes "無料にしてやろう。ありがたいだろ？";
		mes "耳をかっぽじってよく聞けよ。";
		next;
		mes "[ケイム]";
		callsub L_Routine;
		next;
		mes "[ケイム]";
		mes "その他、もっと珍しいアイテムも";
		mes "持っているらしい。どうだ？";
		mes "俺と一緒にあの嬢ちゃんに";
		mes "探りを入れにいかないか？";
		next;
		if(select("暇だね","よし、一緒に行こう！")==1) {
			mes "[ケイム]";
			mes "チェッ、どうせお前も俺と";
			mes "同じシーフ出身者じゃないか。";
			mes "何を遠慮してるんだ？";
			mes "……そうかよ、俺一人でもその";
			mes "嬢ちゃんから聞き出してやるよ。";
			close;
		}
		mes "[ケイム]";
		mes "ははは。冗談だよ、冗談。";
		mes "そんな、真に受けるなよ。";
		mes "今の言葉は忘れてくれ。";
		next;
		mes "[ケイム]";
		mes "さて、その嬢ちゃんが欲しがっている";
		mes "ダイヤモンド３カラットは";
		mes "どこで手に入るのか、だが……";
		mes "俺の仲間によると、何とかっていう";
		mes "山脈の近くに鉱山があるらしい。";
		mes "そこでなら入手できるかもしれないな。";
		next;
		mes "[ケイム]";
		mes "ダイヤモンドと引き換えに、";
		mes "嬢ちゃんから貴重なアイテムを頂く。";
		mes "な、悪くない話だろ？";
		mes "それじゃ、またな。";
		close;
	}
	else {
		mes "[ケイム]";
		mes "ちょいと耳寄りな情報があるんだが……";
		mes "どうだ？興味ないかい？";
		mes "情報料として500zenyくれれば";
		mes "教えてやるよ。";
		next;
		if(select("わかった、払うよ","いや、やめとく")==2) {
			mes "[ケイム]";
			mes "チェッ、いらないのかよ。";
			mes "今どきいい情報を得るためには";
			mes "金が必要なんだよ、金が。";
			mes "金をけちって、いい情報を";
			mes "逃すなんて馬鹿げてるぞ。";
			close;
		}
		if(Zeny < 500) {	//未調査
			mes "[ケイム]";
			mes "おいおい、500zenyもないのかよ…";
			mes "それじゃあ教えられないぜ。";
			close;
		}
		set Zeny,Zeny-500;
		mes "[ケイム]";
		mes "ありがとよ！";
		mes "んじゃ、教えてやる。";
		callsub L_Routine;
		next;
		mes "[ケイム]";
		mes "その他、もっと珍しいアイテムも";
		mes "持っているらしい。一度あの";
		mes "嬢ちゃんに会ってみるといいよ。";
		next;
		mes "[ケイム]";
		mes "さて、その嬢ちゃんが欲しがっている";
		mes "ダイヤモンド３カラットは";
		mes "どこで手に入るのか、だが……";
		mes "俺の仲間によると、何とかっていう";
		mes "山脈の近くに鉱山があるらしい。";
		mes "そこでなら入手できるかもしれないな。";
		close;
	}
L_Routine:
	mes "あっちにダイヤモンド３カラットを";
	mes "欲しがっている嬢ちゃんがいる。";
	mes "噂によると……彼女はけっこう";
	mes "いい物を持っているらしい。";
	next;
	mes "[ケイム]";
	mes "それが、めったに手に入らない物や";
	mes "高価な物をわんさかとだってさ。前に";
	mes "ちらっと見たところ、山羊の角のような";
	mes "物が生えた兜や王冠を持っていたよ。";
	return;
}

mjolnir_02.gat,85,362,3	script	ブラックスミス	726,{
	emotion 18;
	mes "[ドウェイン]";
	mes "わ～い。";
	mes "と～っても珍しいものを";
	mes "た～くさん見つけちゃった！";
	mes "きゃはは～、何だと思う？";
	mes "なんと、ダイヤモンド３カラット!!";
	mes "いいでしょ～、これで私も大金持ち！";
	next;
	if(select("ダイヤモンドを買いたい！","おめでとう！")==2) {
		mes "[ドウェイン]";
		mes "ありがとう～！";
		mes "ダイヤモンドが必要になったら";
		mes "いつでもおいで。特別に安い";
		mes "値段で売ってあげるよ。";
		close;
	}
	mes "[ドウェイン]";
	mes "おお!?";
	mes "価値がわかるんだ～！";
	mes "じゃあ……特別に１個";
	mes "55,000zenyで売ってあげよう！";
	mes "どう？　お買い得でしょ。";
	next;
	mes "[ドウェイン]";
	mes "どれくらい欲しい？";
	mes "あ～でも500個以下にしてね。";
	mes "多すぎても持てないしさ。";
	mes "それから、要らない時は";
	mes "「0」って言ってね。";
	while(1) {
		next;
		input '@num;
		if('@num <= 0) {
			mes "[ドウェイン]";
			mes "え、いらないの～？";
			mes "……じゃ、またね！";
			close;
		}
		if('@num > 500) {
			mes "[ドウェイン]";
			mes "むぅ～。";
			mes "500個以下にしてちょうだい！";
			continue;
		}
		break;
	}
	set '@price,'@num*55000;
	if(Zeny < '@price) {
		mes "[ドウェイン]";
		mes "あっ……えっと、";
		mes "お金が足りないと売れないよ。";
		mes "私も損な商売をするわけには";
		mes "いかないからさ。";
		close;
	}
	if(checkweight(732,'@num)==0) {
		mes "[ドウェイン]";
		mes "けっこう大荷物ね……";
		mes "それじゃあ、ダイヤモンドを";
		mes "持てないでしょ。ちょっと荷物を";
		mes "減らしてから来てちょうだい。";
		close;
	}
	set Zeny,Zeny-'@price;
	getitem 732,'@num;
	mes "[ドウェイン]";
	mes "毎度あり～!!";
	mes "また必要になったらいつでも来てね！";
	close;
}
