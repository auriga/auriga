//= Auriga Script ==============================================================
// Ragnarok Online Dynamic NPC Call Script by refis
//====================================================================

function	script	CallDynamicNPC	{
	set '@dummy,getmapxy('@map$,'@x,'@y,0);
	if(!checkmapflag('@map$,mf_town))	// Townフラグ以外では使用不可
		return;
	set '@class,0;
	setarray '@mapname1$,	"prontera.gat","morocc.gat","payon.gat","comodo.gat","aldebaran.gat",
							"einbroch.gat","lighthalzen.gat","rachel.gat","mid_camp.gat","dicastes01.gat",
							"eclage.gat","louyang.gat","amatsu.gat","moscovia.gat","xmas.gat",
							"dewata.gat","malangdo.gat","lasagna.gat";
	for(set '@i,0;'@i<getarraysize('@mapname1$);set '@i,'@i+1) {
		if('@map$ == '@mapname1$['@i]) {
			set '@class,10145;
			break;
		}
	}
	if(!'@class) {
		setarray '@mapname2$,	"izlude.gat","geffen.gat","alberta.gat","yuno.gat","einbech.gat","hugel.gat",
								"verus04.gat","veins.gat","mora.gat","moro_vol.gat","dali","gonryun",
								"ayothaya","umbala","nif_in","brasilis","malaya","harboro1";
		for(set '@i,0;'@i<getarraysize('@mapname2$);set '@i,'@i+1) {
			if('@map$ == '@mapname2$['@i]) {
				set '@class,10146;
				break;
			}
		}
	}
	if(!'@class) {
		set '@class,10243;
	}
	if('@class == 10145)
		dynamicnpc "ジョンダノービス#n01","",0,0,6,'@class;
	else if('@class == 10146)
		dynamicnpc "ジョンダノービス#n02","",0,0,6,'@class;
	else
		dynamicnpc "ジョンダバルサミコ#do01","",0,0,6,'@class;
	return;
}

-	script	Dynamicnpc#zonda	-1,{
	set '@npcname$,"["+strnpcinfo(1)+"]";
	if(countitem(14902) < 1) {
		// 未調査
		cutin "zonda_" +strnpcinfo(2)+ ".bmp", 2;
		mes '@npcname$;
		mes "こんにちは、冒険者様。";
		mes "私はジョンダパスをお持ちの冒険者様を";
		mes "サポートしております。";
		mes "残念ながら冒険者様は、ジョンダパスを";
		mes "所持しておられないようです。";
		next;
		mes '@npcname$;
		mes "サポートをお求めの場合、";
		mes "ジョンダパスを所持した状態で";
		mes "お声掛けください。";
		close2;
		cutin "zonda_n01.bmp", 255;
		end;
	}
	misceffect 7,"";
	misceffect 14,"";
	set '@class,getbaseclass(Class);
	set '@class2,getbaseclass(Class,2);
	if(BaseLevel >= 85 &&
		('@class == CLASS_SM || '@class == CLASS_MC || '@class2 == CLASS_RG || Job == Job_Mage ||
		'@class2 == CLASS_WZ || '@class == CLASS_TK || '@class == CLASS_GS)
	)
		sc_start SC_SpeedPot2,10800000,0;
	else if(BaseLevel >= 40 &&
		Job != Job_Acolyte && '@class2 != CLASS_PR && '@class2 != CLASS_BA && '@class2 != CLASS_DC
	)
		sc_start SC_SpeedPot1,10800000,0;
	else
		sc_start SC_SpeedPot0,10800000,0;
	sc_start SC_MFLEE,10800000,10;
	sc_start SC_MHIT,10800000,10;
	sc_start SC_SUPPORT_HPSP,10800000,20;
	sc_start SC_SUPPORT_SPEED,10800000,0;
	sc_start SC_SUPPORT_EXP,10800000,5;
	percentheal 100,100;
	repairitem;
	cutin "zonda_" +strnpcinfo(2)+ ".bmp", 2;
	mes '@npcname$;
	mes "お呼びですか、" +(Sex? "ご主人": "お嬢")+ "様。";
	mes "ジョンダパスをお持ちのようですね。";
	mes "各種サービスをご用意しておりますので";
	mes "お好きなサービスを";
	mes "ご自由にお選びください。";
	next;
	switch(select("倉庫サービス","転送サービス","属性付与サービス","装備解除サービス","売却サービス","やめておく")) {
	case 1:
		mes '@npcname$;
		mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
		mes "ご利用ありがとうございました。";
		close2;
		openstorage;
		cutin "zonda_n01.bmp", 255;
		end;
	case 2:
		break;
	case 3:
		mes '@npcname$;
		mes "^0000FF属性付与サービス^000000でございますね。";
		mes "『^FF0000火^000000』『^1E90FF水^000000』『^800000地^000000』『^006400風^000000』の四属性の";
		mes "いずれか1つを武器に付与いたします。";
		next;
		switch(select("^FF0000火属性^000000を付与してもらう","^1E90FF水属性^000000を付与してもらう","^800000地属性^000000を付与してもらう","^006400風属性^000000を付与してもらう")) {
		case 1:
			set '@eff,255;
			set '@type,SC_FireWeapon;
			break;
		case 2:
			set '@eff,256;
			set '@type,SC_WaterWeapon;
			break;
		case 3:
			set '@eff,258;
			set '@type,SC_GroundWeapon;
			break;
		case 4:
			set '@eff,257;
			set '@type,SC_WindWeapon;
			break;
		}
		misceffect '@eff,"";
		sc_start '@type,10800000,5;
		mes '@npcname$;
		mes "いかがでしょうか、" +(Sex? "ご主人": "お嬢")+ "様。";
		mes "改めてサービスをご利用の際は";
		mes "私にお声掛けください。";
		mes "ご利用ありがとうございました。";
		close2;
		cutin "zonda_n01.bmp", 255;
		end;
	case 4:
		misceffect 389,"";
		misceffect 411,"";
		unequip -2;
		mes '@npcname$;
		mes "装備アイテムを解除いたしました。";
		mes "ご利用ありがとうございます。";
		close2;
		cutin "zonda_n01.bmp", 255;
		end;
	case 5:
		mes '@npcname$;
		mes "かしこまりました。";
		mes "お売りになりたいものを";
		mes "お選びください。";
		mes "^FF0000[インフォメーション]";
		mes "‐ジョンダノービス帰還後は";
		mes "　アイテム売却がキャンセルされます‐^000000";
		close2;
		cutin "zonda_n01.bmp", 255;
		callshop "zonda_callshop",2;
		end;
	case 6:
		mes '@npcname$;
		mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
		mes "改めてサービスをご利用の際は";
		mes "私にお声掛けください。";
		mes "ご利用ありがとうございました。";
		close2;
		cutin "zonda_n01.bmp", 255;
		end;
	}
	// 以下転送サービス
	while(1) {
		mes '@npcname$;
		mes "^0000FF転送サービス^000000でございますね。";
		mes "では、転送の種類をお選びください。";
		next;
		switch(select("^FF0000都市転送^000000","^0000FFダンジョン転送^000000")) {
		case 1:	// 都市転送
			while(1) {
				mes '@npcname$;
				mes "都市転送、承知いたしました。";
				mes "続いて、行き先をお選びください。";
				next;
				switch(select(	"^FF0000ルーンミッドガッツ^000000",
								"^0000FFシュバルツバルド^000000",
								"^006400アルナベルツ^000000",
								"^FF6400異世界^000000",
								"^8B008B周辺都市^000000",
								"^8B008Bパースタ大陸^000000",
								"カテゴリ選択に戻る"
				)) {
				case 1:	// ルーンミッドガッツ
					mes '@npcname$;
					mes "^FF0000ルーンミッドガッツ^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"プロンテラ",
									"イズルード",
									"ゲフェン",
									"モロク",
									"フェイヨン",
									"アルベルタ",
									"コモド",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"prontera.gat";	set '@x,118;	set '@y,80;		break;
					case 2: set '@map$,"izlude.gat";	set '@x,128;	set '@y,91;		break;
					case 3: set '@map$,"geffen.gat";	set '@x,120;	set '@y,69;		break;
					case 4: set '@map$,"morocc.gat";	set '@x,156;	set '@y,92;		break;
					case 5: set '@map$,"payon.gat";		set '@x,183;	set '@y,100;	break;
					case 6: set '@map$,"alberta.gat";	set '@x,117;	set '@y,56;		break;
					case 7: set '@map$,"comodo.gat";	set '@x,209;	set '@y,143;	break;
					case 8:
						continue;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				case 2:	// シュバルツバルド
					mes '@npcname$;
					mes "^0000FFシュバルツバルド^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"アルデバラン",
									"ジュノー",
									"アインブロック",
									"アインベフ",
									"リヒタルゼン",
									"フィゲル",
									"ウェルス発掘地",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"aldebaran.gat";		set '@x,140;	set '@y,113;	break;
					case 2: set '@map$,"yuno.gat";			set '@x,157;	set '@y,196;	break;
					case 3: set '@map$,"einbroch.gat";		set '@x,242;	set '@y,197;	break;
					case 4: set '@map$,"einbech.gat";		set '@x,173;	set '@y,129;	break;
					case 5: set '@map$,"lighthalzen.gat";	set '@x,159;	set '@y,92;		break;
					case 6: set '@map$,"hugel.gat";			set '@x,96;		set '@y,160;	break;
					case 7: set '@map$,"verus04.gat";		set '@x,123;	set '@y,249;	break;
					case 8:
						continue;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				case 3:	// アルナベルツ
					mes '@npcname$;
					mes "^006400アルナベルツ^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"ラヘル",
									"ベインス",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"rachel.gat";		set '@x,139;	set '@y,134;	break;
					case 2: set '@map$,"veins.gat";			set '@x,204;	set '@y,124;	break;
					case 3:
						continue;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				case 4:	// 異世界
					mes '@npcname$;
					mes "^FF6400異世界^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"ミッドガルド連合軍駐屯地",
									"スプレンディッド",
									"マヌク",
									"エルディカスティス",
									"モーラ",
									"エクラージュ",
									"フレイムヴァレー",
									"次元の狭間 時の通路01",
									"次元の狭間 時の通路02",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"mid_camp.gat";		set '@x,46;		set '@y,120;	break;
					case 2: set '@map$,"splendide.gat";		set '@x,232;	set '@y,151;	if(ASH_1QUE < 100) set '@flag,1;	break;	// 異世界クエスト
					case 3: set '@map$,"manuk.gat";			set '@x,293;	set '@y,141;	if(ASH_1QUE < 100) set '@flag,1;	break;	// 異世界クエスト
					case 4: set '@map$,"dicastes01.gat";	set '@x,197;	set '@y,145;	break;
					case 5: set '@map$,"mora.gat";			set '@x,113;	set '@y,109;	break;
					case 6: set '@map$,"eclage.gat";		set '@x,109;	set '@y,37;		break;
					case 7: set '@map$,"moro_vol.gat";		set '@x,93;		set '@y,99;		if(FVOL_1QUE < 100) set '@flag,1;	break;	// フレイムヴァレーへの道クエスト
					case 8: set '@map$,"dali.gat";			set '@x,107;	set '@y,89;		break;
					case 9: set '@map$,"dali02.gat";		set '@x,107;	set '@y,89;		break;
					case 10:
						continue;
					}
					if('@flag) {
						mes '@npcname$;
						mes (Sex? "ご主人": "お嬢")+ "様はまだ、そこに行く";
						mes "資格をお持ちでないようです。";
						mes "ご希望に添うことができず";
						mes "申し訳ありません。";
						mes "またのご利用をお待ちしております。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				case 5:	// 周辺都市
					mes '@npcname$;
					mes "^8B008B周辺都市^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"コンロン",
									"アユタヤ",
									"龍之城",
									"アマツ",
									"ウンバラ",
									"ニブルヘイム",
									"モスコビア",
									"ルティエ",
									"ブラジリス",
									"デワタ",
									"マラン島",
									"ポートマラヤ",
									"ロックリッジ",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"gonryun.gat";		set '@x,161;	set '@y,117;	break;
					case 2: set '@map$,"ayothaya.gat";		set '@x,216;	set '@y,167;	break;
					case 3: set '@map$,"louyang.gat";		set '@x,218;	set '@y,114;	break;
					case 4: set '@map$,"amatsu.gat";		set '@x,109;	set '@y,149;	break;
					case 5: set '@map$,"umbala.gat";		set '@x,88;		set '@y,153;	break;
					case 6: set '@map$,"nif_in.gat";		set '@x,18;		set '@y,20;		break;
					case 7: set '@map$,"moscovia.gat";		set '@x,229;	set '@y,194;	break;
					case 8: set '@map$,"xmas.gat";			set '@x,143;	set '@y,299;	break;
					case 9: set '@map$,"brasilis.gat";		set '@x,225;	set '@y,192;	break;
					case 10: set '@map$,"dewata.gat";		set '@x,190;	set '@y,190;	break;
					case 11: set '@map$,"malangdo.gat";		set '@x,184;	set '@y,132;	break;
					case 12: set '@map$,"malaya.gat";		set '@x,242;	set '@y,211;	break;
					case 13: set '@map$,"harboro1.gat";		set '@x,297;	set '@y,203;	break;
					case 14:
						continue;
					}
					if('@flag) {
						mes '@npcname$;
						mes (Sex? "ご主人": "お嬢")+ "様はまだ、そこに行く";
						mes "資格をお持ちでないようです。";
						mes "ご希望に添うことができず";
						mes "申し訳ありません。";
						mes "またのご利用をお待ちしております。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				case 6:	// パースタ大陸
					mes '@npcname$;
					mes "^8B008Bパースタ大陸^000000の";
					mes "どこに向かわれますか？";
					next;
					switch(select(	"港町ラザーニャ",
									"都市選択に戻る"
					)) {
					case 1: set '@map$,"lasagna.gat";		set '@x,298;	set '@y,238;	break;
					case 2:
						continue;
					}
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				default:
					break;
				}
				break;
			}
			continue;
		case 2:	// ダンジョン転送
			while(1) {
				set '@map$,"";
				mes '@npcname$;
				mes "ダンジョン転送、承知いたしました。";
				mes "続いて、行き先をお選びください。";
				next;
				switch(select(	"^FF0000ダンジョン【ア行】^000000",
								"^8B008Bダンジョン【カ行】^000000",
								"^0000FFダンジョン【サ～タ行】^000000",
								"^005566ダンジョン【ナ～ハ行】^000000",
								"^006400ダンジョン【マ～ワ行】^000000",
								"^DE1039イリュージョンダンジョン^000000",
								"^EB5B0Fテラーダンジョン^000000",
								"^FF6400異世界^000000",
								"^8B008Bその他^000000",
								"^640000メモリアルダンジョン^000000",
								"カテゴリ選択に戻る"
				)) {
				case 1:	// ダンジョン【ア行】
					mes '@npcname$;
					mes "かしこまりました。";
					mes "^FF0000ダンジョン【ア行】^000000から始まる";
					mes "ダンジョンは、こちらになります。";
					next;
					switch(select(	"アビスレイク",
									"アマツダンジョン",
									"蟻地獄ダンジョン",
									"アユタヤダンジョン",
									"イズルード海底洞窟",
									"",						// ヴェルナー研究所
									"おもちゃ工場",
									"オーク地下洞窟",
									"オーディン神殿",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000アビスレイク^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("アビスレイク 入口","アビスレイク地下洞窟 03","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"hu_fild05.gat";	set '@x,167;	set '@y,298;	break;
						case 2: set '@map$,"abyss_03.gat";	set '@x,115;	set '@y,30;		break;
						default:
							continue;
						}
						break;
					case 2:
						mes '@npcname$;
						mes "^FF0000アマツダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						// 未調査
						switch(select("アマツダンジョン 03","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"ama_dun03.gat";	set '@x,120;	set '@y,12;	if(AMA_1QUE < 6) set '@flag,1;	break;	// 通行手形クエスト
						default:
							continue;
						}
						break;
					case 3:
						mes '@npcname$;
						mes "^FF0000蟻地獄ダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("蟻地獄ダンジョン B1F","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"anthell01.gat";	set '@x,35;	set '@y,257;	break;
						default:
							continue;
						}
						break;
					case 4:
						mes '@npcname$;
						mes "^FF0000アユタヤダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						// 未調査
						switch(select("アユタヤダンジョン 02","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"ayo_dun02.gat";	set '@x,23;	set '@y,26;	if(AYO_1QUE < 11) set '@flag,1;	break;	// 古代遺跡クエスト
						default:
							continue;
						}
						break;
					case 5:
						mes '@npcname$;
						mes "^FF0000イズルード海底洞窟^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("イズルード海底洞窟 入口","イズルード海底洞窟 3層","イズルード海底神殿","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"izlu2dun.gat";	set '@x,107;	set '@y,93;		break;
						case 2: set '@map$,"iz_dun02.gat";	set '@x,340;	set '@y,324;	break;
						case 3: set '@map$,"iz_dun04.gat";	set '@x,129;	set '@y,232;	break;
						default:
							continue;
						}
						break;
					case 6:
						mes '@npcname$;
						mes "^FF0000ヴェルナー研究所^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ヴェルナー研究所 A棟","ヴェルナー研究所 B棟","ヴェルナー研究所 C棟","ヴェルナー研究所 D棟","ダンジョン選択へ戻る")) {
						case 1: set '@flag,1;	break;
						case 2: set '@flag,1;	break;
						case 3: set '@flag,1;	break;
						case 4: set '@flag,1;	break;
						default:
							continue;
						}
						break;
					case 7:
						mes '@npcname$;
						mes "^FF0000おもちゃ工場^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("おもちゃ工場ダンジョン 02","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"xmas_dun02.gat";	set '@x,134;	set '@y,129;	break;
						default:
							continue;
						}
						break;
					case 8:
						mes '@npcname$;
						mes "^FF0000オーク地下洞窟^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("オーク地下洞窟 入口","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"gef_fild10.gat";	set '@x,70;	set '@y,336;	break;
						default:
							continue;
						}
						break;
					case 9:
						mes '@npcname$;
						mes "^FF0000オーディン神殿^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("オーディン神殿 01","オーディン神殿 03","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"odin_tem01.gat";	set '@x,379;	set '@y,334;	break;
						case 2: set '@map$,"odin_tem03.gat";	set '@x,240;	set '@y,36;		break;
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 2:	// ダンジョン【カ行】
					mes '@npcname$;
					mes "かしこまりました。";
					mes "^8B008Bダンジョン【カ行】^000000から始まる";
					mes "ダンジョンは、こちらになります。";
					next;
					switch(select(	"機械人形工場",
									"グラストヘイム",
									"ゲフェニア",
									"ゲフェン地下ダンジョン",
									"氷の洞窟",
									"コンロンダンジョン",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000機械人形工場^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("機械人形工場 入口","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"yuno_fild08.gat";	set '@x,74;	set '@y,179;	break;
						default:
							continue;
						}
						break;
					case 2:
						mes '@npcname$;
						mes "^FF0000グラストヘイム^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("グラストヘイム 入口","グラストヘイム 修道院","グラストヘイム 古城","グラストヘイム 騎士団","グラストヘイム 地下水路02","グラストヘイム 最下層地下洞窟01","悪夢のグラストヘイムカタコンベ","悪夢のグラストヘイム古城2F","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"glast_01.gat";		set '@x,371;	set '@y,304;	break;
						case 2: set '@map$,"glast_01.gat";		set '@x,204;	set '@y,133;	break;
						case 3: set '@map$,"glast_01.gat";		set '@x,197;	set '@y,290;	break;
						case 4: set '@map$,"glast_01.gat";		set '@x,67;		set '@y,192;	break;
						case 5: set '@map$,"gl_sew02.gat";		set '@x,293;	set '@y,295;	break;
						case 6: set '@map$,"gl_dun01.gat";		set '@x,222;	set '@y,24;		break;
						case 7: set '@map$,"gl_chyard_.gat";	set '@x,148;	set '@y,144;	if(Job >= Job_RuneKnight) set '@flag,1;	break;
						case 8: set '@map$,"gl_cas02_.gat";		set '@x,105;	set '@y,190;	if(Job < Job_RuneKnight || (Job == Job_Summoner && BaseLevel < 90)) set '@flag,1;	break;
						default:
							continue;
						}
						break;
					case 3:
						mes '@npcname$;
						mes "^FF0000ゲフェニア^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ゲフェニア 04","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"gefenia04.gat";	set '@x,129;	set '@y,91;	break;
						default:
							continue;
						}
						break;
					case 4:
						mes '@npcname$;
						mes "^FF0000ゲフェン地下ダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ゲフェン地下ダンジョン B2F","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"gef_dun01.gat";	set '@x,200;	set '@y,44;	break;
						default:
							continue;
						}
						break;
					case 5:
						mes '@npcname$;
						mes "^FF0000氷の洞窟^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("氷の洞窟 入口","氷の洞窟 02","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"ra_fild01.gat";	set '@x,234;	set '@y,326;	break;
						case 2: set '@map$,"ice_dun02.gat";	set '@x,152;	set '@y,281;	break;
						default:
							continue;
						}
						break;
					case 6:
						mes '@npcname$;
						mes "^FF0000コンロンダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("コンロンダンジョン 03","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"gon_dun03.gat";	set '@x,65;	set '@y,10;	break;
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 3:	// ダンジョン【サ～タ行】
					mes '@npcname$;
					mes "かしこまりました。";
					mes "^0000FFダンジョン【サ～タ行】^000000から始まる";
					mes "ダンジョンは、こちらになります。";
					next;
					switch(select(	"ジュピロス廃墟",
									"",							// 侵攻されたプロンテラ
									"スフィンクスダンジョン",
									"生体工学研究所",
									"",							// 戦死者の墓
									"タナトスタワー",
									"タートルアイランド",
									"沈没船付近の島",
									"デワタダンジョン",
									"",							// 特殊警戒地域オース
									"時計塔",
									"トール火山",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000ジュピロス廃墟^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ジュピロス廃墟 入口","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"jupe_cave.gat";	set '@x,140;	set '@y,51;	break;
						default:
							continue;
						}
						break;
					case 2:
						continue;
						//mes '@npcname$;
						//mes "^FF0000侵攻されたプロンテラ^000000の";
						//mes "どちらに向かわれますか？";
						//next;
						//switch(select("侵攻されたプロンテラ","ダンジョン選択へ戻る")) {
						//case 1: set '@map$,"prt_q_jp.gat";	set '@x,153;	set '@y,324;	break;
						//default:
						//	continue;
						//}
						//break;
					case 3:
						mes '@npcname$;
						mes "^FF0000スフィンクスダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("スフィンクスダンジョン 入口","スフィンクスダンジョン B4F","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"moc_fild19.gat";	set '@x,104;	set '@y,99;		break;
						case 2: set '@map$,"in_sphinx4.gat";	set '@x,119;	set '@y,118;	break;
						default:
							continue;
						}
						break;
					case 4:
						mes '@npcname$;
						mes "^FF0000生体工学研究所^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("生体工学研究所 02","生体工学研究所 04","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"lhz_dun02.gat";	set '@x,150;	set '@y,114;	if(LHZ_1QUE < 9) set '@flag,1;	break;	// 研究所進入クエスト
						case 2: set '@map$,"lhz_dun04.gat";	set '@x,241;	set '@y,58;		if(LHZ_1QUE < 9) set '@flag,1;	break;	// 研究所進入クエスト
						default:
							continue;
						}
						break;
					case 5:
						mes '@npcname$;
						mes "^FF0000戦死者の墓^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("戦死者の墓(思念の間)","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"lhz_dun_n_c.gat";	set '@x,139;	set '@y,261;	break;
						default:
							continue;
						}
						break;
					case 6:
						mes '@npcname$;
						mes "^FF0000タナトスタワー^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("タナトスタワー 入口","タナトスタワー上層部 06","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"hu_fild01.gat";	set '@x,140;	set '@y,159;	break;
						case 2: set '@map$,"tha_t06.gat";	set '@x,124;	set '@y,120;	if(THA_1QUE < 1) set '@flag,1;	break;	// タナトスタワー進入
						default:
							continue;
						}
						break;
					case 7:
						mes '@npcname$;
						mes "^FF0000タートルアイランド^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("タートルアイランドダンジョン 01","タートルアイランドダンジョン 03","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"tur_dun02.gat";	set '@x,145;	set '@y,264;	if(TUR_1QUE < 1) set '@flag,1;	break;	// タートルアイランドクエスト
						case 2: set '@map$,"tur_dun04.gat";	set '@x,97;		set '@y,193;	if(TUR_1QUE < 1) set '@flag,1;	break;	// タートルアイランドクエスト
						default:
							continue;
						}
						break;
					case 8:
						mes '@npcname$;
						mes "^FF0000沈没船付近の島^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("沈没船 入口","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"alb2trea.gat";	set '@x,63;	set '@y,68;	break;
						default:
							continue;
						}
						break;
					case 9:
						mes '@npcname$;
						mes "^FF0000デワタダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("イスタナ洞窟 入口","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"dew_fild01.gat";	set '@x,54;	set '@y,65;	break;
						default:
							continue;
						}
						break;
					case 10:
						mes '@npcname$;
						mes "^FF0000特殊警戒地域オース^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("特殊警戒地域オース","ダンジョン選択へ戻る")) {
						case 1: set '@flag,1;	break;
						default:
							continue;
						}
						break;
					case 11:
						mes '@npcname$;
						mes "^FF0000時計塔^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("アルデバラン時計塔地上 2F","アルデバラン時計塔地上 4F","アルデバラン時計塔地下 2F","アルデバラン時計塔地下 4F","捻じれた時間の時計塔 1階","捻じれた時間の時計塔 2階","捻じれた時間の時計塔 3階","捻じれた時間の時計塔 4階","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"c_tower2.gat";	set '@x,147;	set '@y,283;	break;
						case 2: set '@map$,"c_tower4.gat";	set '@x,183;	set '@y,41;	break;
						case 3: set '@map$,"alde_dun02.gat";	set '@x,127;	set '@y,169;	break;
						case 4: set '@map$,"alde_dun04.gat";	set '@x,79;		set '@y,269;	break;
						case 5: set '@map$,"c_tower1_.gat";	set '@x,235;	set '@y,223;	if(BaseLevel < 150) set '@flag,1;	break;	// 未調査
						case 6: set '@map$,"c_tower2_.gat";	set '@x,268;	set '@y,26;		if(BaseLevel < 150) set '@flag,1;	break;	// 未調査
						case 7: set '@map$,"c_tower3_.gat";	set '@x,65;		set '@y,147;	if(BaseLevel < 150) set '@flag,1;	break;	// 未調査
						case 8: set '@map$,"c_tower4_.gat";	set '@x,185;	set '@y,44;		if(BaseLevel < 150) set '@flag,1;	break;	// 未調査
						default:
							continue;
						}
						break;
					case 12:
						mes '@npcname$;
						mes "^FF0000トール火山^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("トール火山 入口","トール火山ダンジョン 02","ダンジョン選択へ戻る")) {
						case 1: set '@map$,"ve_fild03.gat";	set '@x,168;	set '@y,234;	break;
						case 2: set '@map$,"thor_v02.gat";	set '@x,186;	set '@y,62;		break;
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 4:	// ダンジョン【ナ～ハ行】
					mes '@npcname$;
					mes "かしこまりました。";
					mes "^005566ダンジョン【ナ～ハ行】^000000から始まる";
					mes "ダンジョンは、こちらになります。";
					next;
					switch(select(	"名もなき島",
									"ノーグロード",
									"",						// 廃棄場ルドゥス
									"ピラミッドダンジョン",
									"フェイヨン地下洞窟",
									"ブラジリスダンジョン",
									"フレイヤ大神殿聖域",
									"プロンテラ地下監獄",
									"プロンテラ地下水路",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000名もなき島^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("名もなき島 入口","修道院 01","ダンジョン選択に戻る")) {
						case 1: set '@map$,"ve_fild07.gat";	set '@x,129;	set '@y,132;	break;
						case 2: set '@map$,"abbey01.gat";	set '@x,324;	set '@y,98;		if(NAME_1QUE < 17) set '@flag,1;	break;	// 名もなき島の秘密クエスト
						default:
							continue;
						}
						break;
					case 2:
						mes '@npcname$;
						mes "^FF0000ノーグロード^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ノーグロード 1層","ダンジョン選択に戻る")) {
						case 1: set '@map$,"mag_dun01.gat";	set '@x,237;	set '@y,236;	break;
						default:
							continue;
						}
						break;
					case 3:
						mes '@npcname$;
						mes "^FF0000廃棄場ルドゥス^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("廃棄場ルドゥス　1階","廃棄場ルドゥス　2階","廃棄場ルドゥス　3階","ダンジョン選択に戻る")) {
						case 1: set '@flag,1;	break;
						case 2: set '@flag,1;	break;
						case 3: set '@flag,1;	break;
						default:
							continue;
						}
						break;
					case 4:
						mes '@npcname$;
						mes "^FF0000ピラミッドダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ピラミッドダンジョン 入口","ピラミッドダンジョン 3F","ピラミッドダンジョン B3F","秘密の地下室01","秘密の地下室02","ダンジョン選択に戻る")) {
						case 1: set '@map$,"moc_ruins.gat";		set '@x,64;		set '@y,157;	break;
						case 2: set '@map$,"moc_pryd03.gat";	set '@x,20;		set '@y,187;	break;
						case 3: set '@map$,"moc_pryd06.gat";	set '@x,192;	set '@y,12;		break;
						case 4: set '@map$,"moc_prydn1.gat";	set '@x,93;		set '@y,96;		if(BaseLevel < 100) set '@flag,1;	break;
						case 5: set '@map$,"moc_prydn2.gat";	set '@x,195;	set '@y,11;		if(BaseLevel < 100) set '@flag,1;	break;
						default:
							continue;
						}
						break;
					case 5:
						mes '@npcname$;
						mes "^FF0000フェイヨン地下洞窟^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("フェイヨン地下洞窟 入口","フェイヨン地下洞窟 B3F","フェイヨン地下洞窟 B4F","ダンジョン選択に戻る")) {
						case 1: set '@map$,"pay_arche.gat";	set '@x,48;		set '@y,126;	break;
						case 2: set '@map$,"pay_dun02.gat";	set '@x,22;		set '@y,62;	break;
						case 3: set '@map$,"pay_dun03.gat";	set '@x,120;	set '@y,65;	break;
						default:
							continue;
						}
						break;
					case 6:
						mes '@npcname$;
						mes "^FF0000ブラジリスダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						// 未調査
						switch(select("滝の中の洞窟 01","ダンジョン選択に戻る")) {
						case 1: set '@map$,"bra_dun01.gat";	set '@x,87;	set '@y,47;	if(BRA_3QUE < 8) set '@flag,1;	break;	// トイレのオバケクエスト
						default:
							continue;
						}
						break;
					case 7:
						mes '@npcname$;
						mes "^FF0000フレイヤ大神殿聖域^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("フレイヤ大神殿聖域 入口","ダンジョン選択に戻る")) {
						case 1: set '@map$,"ra_temin.gat";	set '@x,32;	set '@y,312;	if(RA_1QUE < 10) set '@flag,1;	break;	// フレイヤ大神殿クエスト
						default:
							continue;
						}
						break;
					case 8:
						mes '@npcname$;
						mes "^FF0000プロンテラ地下監獄^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("プロンテラ地下監獄 入口","ダンジョン選択に戻る")) {
						case 1: set '@map$,"prt_pri00.gat";	set '@x,51;	set '@y,120;	if(EP16_1QUE < 2) set '@flag,1;	break;	// 七王家とユミルの心臓
						default:
							continue;
						}
						break;
					case 9:
						mes '@npcname$;
						mes "^FF0000プロンテラ地下水路^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("プロンテラ地下水路 入口","プロンテラ地下水路 B2F","プロンテラ地下水路 B4F","ダンジョン選択に戻る")) {
						case 1: set '@map$,"prt_fild05.gat";	set '@x,274;	set '@y,213;	break;
						case 2: set '@map$,"prt_sewb2.gat";		set '@x,19;		set '@y,19;		if(PRT_1QUE < 1) set '@flag,1;	break;	// プロンテラ地下水路クエスト
						case 3: set '@map$,"prt_sewb4.gat";		set '@x,100;	set '@y,90;		if(PRT_1QUE < 1) set '@flag,1;	break;	// プロンテラ地下水路クエスト
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 5:	// ダンジョン【マ～ワ行】
					mes '@npcname$;
					mes "かしこまりました。";
					mes "^006400ダンジョン【マ～ワ行】^000000から始まる";
					mes "ダンジョンは、こちらになります。";
					next;
					switch(select(	"ミョルニール廃鉱",
									"迷宮の森",
									"モスコビアダンジョン",
									"龍之城ダンジョン",
									"龍の巣",
									"ロックリッジダンジョン",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000ミョルニール廃鉱^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ミョルニール廃鉱 入口","ミョルニール廃鉱 B2F","ダンジョン選択に戻る")) {
						case 1: set '@map$,"mjolnir_02.gat";	set '@x,83;	set '@y,356;	break;
						case 2: set '@map$,"mjo_dun02.gat";		set '@x,39;	set '@y,27;		break;
						default:
							continue;
						}
						break;
					case 2:
						mes '@npcname$;
						mes "^FF0000迷宮の森^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("迷宮の森 02","ダンジョン選択に戻る")) {
						case 1: set '@map$,"prt_maze02.gat";	set '@x,105;	set '@y,96;	break;
						default:
							continue;
						}
						break;
					case 3:
						mes '@npcname$;
						mes "^FF0000モスコビアダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						// 未調査
						switch(select("奥深い森","ダンジョン選択に戻る")) {
						case 1: set '@map$,"mosk_dun03.gat";	set '@x,32;	set '@y,135;	if(MOSK_1QUE < 39) set '@flag,1;	break;	// クジラ島をたずねてクエスト
						default:
							continue;
						}
						break;
					case 4:
						mes '@npcname$;
						mes "^FF0000龍之城ダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("龍之城ダンジョン 03","ダンジョン選択に戻る")) {
						case 1: set '@map$,"lou_dun03.gat";	set '@x,165;	set '@y,40;	break;
						default:
							continue;
						}
						break;
					case 5:
						mes '@npcname$;
						mes "^FF0000龍の巣^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("龍の巣 01","龍の巣 02","ダンジョン選択に戻る")) {
						case 1: set '@map$,"lasa_dun01.gat";	set '@x,24;		set '@y,143;	break;
						case 2: set '@map$,"lasa_dun02.gat";	set '@x,146;	set '@y,53;		break;
						default:
							continue;
						}
						break;
					case 6:
						mes '@npcname$;
						mes "^FF0000ロックリッジダンジョン^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ロックリッジ鉱山 01","ロックリッジ鉱山 01 奥地","ロックリッジ地下街","ロックリッジ地下街 奥地","ダンジョン選択に戻る")) {
						case 1: set '@map$,"rockmi1.gat";	set '@x,247;	set '@y,19;		break;
						case 2: set '@map$,"rockmi3.gat";	set '@x,247;	set '@y,19;		break;
						case 3: set '@map$,"harboro2.gat";	set '@x,281;	set '@y,104;	break;
						case 4: set '@map$,"harboro3.gat";	set '@x,281;	set '@y,104;	break;
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 6:	// イリュージョンダンジョン
					mes '@npcname$;
					mes "^DE1039イリュージョンダンジョン^000000でございますね。";
					mes "ご希望の場所をお選びください。";
					next;
					switch(select(	"月夜花の悪夢",
									"フローズンメモリー",
									"250 ページ",
									"悲しみの陽居村",
									"ネジリアン帝国",
									"幻想の北洞窟ルワンダ",
									"歪んだ迷宮の森",
									"ダンジョン選択に戻る"
					)) {
					case 1: set '@map$,"pay_dun03.gat";		set '@x,150;	set '@y,45;	break;
					case 2: set '@map$,"ice_dun02.gat";		set '@x,150;	set '@y,16;	break;
					case 3: set '@flag,1; break;
					case 4: set '@flag,1; break;
					case 5: set '@flag,1; break;
					case 6: set '@flag,1; break;
					case 7: set '@flag,1; break;
					default:
						continue;
					}
					break;
				case 7:	// テラーダンジョン
					mes '@npcname$;
					mes "^EB5B0Fテラーダンジョン^000000でございますね";
					mes "ご希望の場所をお選びください。";
					next;
					switch(select(	"ノーグロード3層",
									"グラストヘイムアビス",
									"ダンジョン選択に戻る"
					)) {
					case 1: set '@flag,1;	break;
					case 2: set '@flag,1;	break;
					default:
						continue;
					}
					break;
				case 8:	// 異世界
					mes '@npcname$;
					mes "^FF6400異世界^000000でございますね。";
					mes "ご希望の場所をお選びください。";
					next;
					switch(select(	"イグドラシル中心部",
									"エクラージュ",
									"カミダルトンネル",
									"ダンジョン選択に戻る"
					)) {
					case 1:
						mes '@npcname$;
						mes "^FF0000イグドラシル中心部^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("イグドラシル中心部 02","ダンジョン選択に戻る")) {
						case 1: set '@map$,"nyd_dun02.gat";	set '@x,63;	set '@y,269;	if(YGG_2QUE < 5) set '@flag,1;	break;	// 二つの種族クエスト
						default:
							continue;
						}
						break;
					case 2:
						mes '@npcname$;
						mes "^FF0000エクラージュ^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("花が咲き始めた大地","ビフロストタワー 2階","ダンジョン選択に戻る")) {
						case 1: set '@map$,"ecl_fild01.gat";	set '@x,183;	set '@y,93;	if(ASH_1QUE < 100) set '@flag,1;	break;	// 異世界クエスト
						case 2: set '@map$,"ecl_tdun02.gat";	set '@x,47;		set '@y,11;	if(ASH_1QUE < 100) set '@flag,1;	break;	// 異世界クエスト
						default:
							continue;
						}
						break;
					case 3:
						mes '@npcname$;
						mes "^FF0000カミダルトンネル^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("スカラバダンジョン 入口","ダンジョン選択に戻る")) {
						case 1: set '@map$,"dic_dun01.gat";	set '@x,290;	set '@y,98;	if(DIC_1QUE < 100) set '@flag,1;	break;	// エルディカスティスクエスト
						default:
							continue;
						}
						break;
					default:
						continue;
					}
					break;
				case 9:	// その他
					mes '@npcname$;
					mes "^8B008Bその他^000000でございますね。";
					mes "ご希望の場所をお選びください。";
					next;
					switch(select(	"聖カピトーリナ修道院",
									"フェイヨン迷いの森 04",
									"アサシンギルド内",
									"ファロス燈台島",
									"ココモビーチ",
									"アインブロックフィールド 04",
									"ジュノーフィールド 06",
									"ダンジョン選択に戻る"
					)) {
					case 1: set '@map$,"prt_monk.gat";		set '@x,223;	set '@y,172;	break;
					case 2: set '@map$,"pay_fild04.gat";	set '@x,24;		set '@y,169;	break;
					case 3: set '@map$,"in_moc_16.gat";		set '@x,16;		set '@y,14;		break;
					case 4: set '@map$,"cmd_fild07.gat";	set '@x,138;	set '@y,129;	break;
					case 5: set '@map$,"cmd_fild02.gat";	set '@x,219;	set '@y,372;	break;
					case 6: set '@map$,"ein_fild04.gat";	set '@x,184;	set '@y,32;		break;
					case 7: set '@map$,"yuno_fild06.gat";	set '@x,363;	set '@y,134;	break;
					default:
						continue;
					}
					break;
				case 10:	// メモリアルダンジョン
					mes '@npcname$;
					mes "^640000メモリアルダンジョン^000000でございますね。";
					mes "ご希望の場所をお選びください。";
					next;
					switch(select(	"悪夢のジターバグ",
									"暗黒時代の記憶",
									"古のグラストヘイム",
									"ヴェルナー研究所中央室",
									"永劫の戦",
									"英雄の痕跡",
									"エンドレスタワー",
									"オークの記憶",
									"オース二次捜索",
									"過去の儀式の間",
									"霧の森",
									"禁忌の研究所",
									"空中要塞",
									"コルメモリアル",
									"最後の部屋",
									"生体工学研究所の記録",
									"地下排水路",
									"チャールストン工場",
									"中央実験室",
									"ニーズヘッグの巣",
									"ネコリンの秘密研究所",
									"ハートハンター軍事基地",
									"バコナワの棲み処",
									"封印された神殿",
									"フレイムケイブ",
									"ブワヤの巣",
									"暴窟王の洞窟",
									"ホラーおもちゃ工場",
									"真昼の弦月",
									"闇のビョンウンゴ病院",
									"ダンジョン選択に戻る"
					)) {
					case 1: set '@flag,1;	break;	// 悪夢のジターバグ
					case 2: set '@flag,1;	break;	// 暗黒時代の記憶
					case 3: set '@map$,"glast_01.gat";		set '@x,200;	set '@y,264;	break;
					case 4: set '@flag,1;	break;	// ヴェルナー研究所中央室
					case 5: set '@flag,1;	break;	// 永劫の戦
					case 6:
						mes '@npcname$;
						mes "^FF0000英雄の痕跡^000000の";
						mes "どちらに向かわれますか？";
						next;
						switch(select("ゲフェン魔法大会","サラの記憶","呪いの剣士","飛行船襲撃","フェイスワームの巣","フェンリルとサラ","魔神の塔","ダンジョン選択に戻る")) {
						case 1: break;
						case 2: break;
						case 3: break;
						case 4: break;
						case 5: break;
						case 6: break;
						case 7: break;
						default:
							continue;
						}
						break;
					case 7: set '@map$,"alberta.gat";		set '@x,214;	set '@y,72;		break;
					case 8: set '@map$,"gef_fild10.gat";	set '@x,240;	set '@y,197;	break;
					case 9: set '@flag,1;	break;	// オース二次捜索
					case 10: set '@flag,1;	break;	// 過去の儀式の間
					case 11: set '@map$,"bif_fild01.gat";	set '@x,160;	set '@y,334;	break;
					case 12: set '@map$,"lhz_dun04.gat";	set '@x,148;	set '@y,273;	break;
					case 13: set '@flag,1;	break;	// 空中要塞
					case 14: set '@flag,1;	break;	// コルメモリアル
					case 15: set '@flag,1;	break;	// 最後の部屋
					case 16: set '@flag,1;	break;	// 生体工学研究所の記録
					case 17: set '@map$,"mal_in01.gat";		set '@x,170;	set '@y,34;	break;
					case 18: set '@flag,1;	break;	// チャールストン工場
					case 19: set '@flag,1;	break;	// 中央実験室
					case 20: set '@map$,"nyd_dun02.gat";	set '@x,94;		set '@y,192;	break;
					case 21: set '@flag,1;	break;	// ネコリンの秘密研究所
					case 22: set '@flag,1;	break;	// ハートハンター軍事基地
					case 23: set '@map$,"ma_scene01.gat";	set '@x,171;	set '@y,175;	break;
					case 24: set '@map$,"monk_test.gat";	set '@x,302;	set '@y,140;	break;
					case 25: set '@map$,"moro_cav.gat";		set '@x,45;		set '@y,66;		break;
					case 26: set '@map$,"ma_fild02.gat";	set '@x,315;	set '@y,313;	break;
					case 27: set '@map$,"mal_dun01.gat";	set '@x,152;	set '@y,231;	break;
					case 28: set '@map$,"xmas.gat";			set '@x,234;	set '@y,289;	break;
					case 29: set '@flag,1;	break;	// 真昼の弦月
					case 30: set '@map$,"malaya.gat";		set '@x,56;		set '@y,78;		break;
					default:
						continue;
					}
					break;
				default:
					continue;
				}
				if('@flag) {
					mes '@npcname$;
					mes (Sex? "ご主人": "お嬢")+ "様はまだ、そこに行く";
					mes "資格をお持ちでないようです。";
					mes "ご希望に添うことができず";
					mes "申し訳ありません。";
					mes "またのご利用をお待ちしております。";
					close2;
					cutin "zonda_n01.bmp", 255;
					end;
				}
				if('@map$ != "") {
					mes '@npcname$;
					mes "承知いたしました。";
					mes "それではお送りいたしますが";
					mes "よろしいですか？";
					next;
					if(select("出発する","やめる") == 2) {
						mes '@npcname$;
						mes "かしこまりました、" +(Sex? "ご主人": "お嬢")+ "様";
						mes "改めてサービスをご利用の際は";
						mes "私にお声掛けください。";
						mes "ご利用ありがとうございました。";
						close2;
						cutin "zonda_n01.bmp", 255;
						end;
					}
					misceffect 35,"";
					mes '@npcname$;
					mes "いってらっしゃいませ、" +(Sex? "ご主人": "お嬢")+ "様。";
					mes "どうかお気をつけて。";
					close2;
					cutin "zonda_n01.bmp", 255;
					warp '@map$,'@x,'@y;
					end;
				}
				break;
			}
			continue;
		}
	}
}

-	shop	zonda_callshop	-1,512
-	duplicate(Dynamicnpc#zonda)	ジョンダノービス#n01	-1
-	duplicate(Dynamicnpc#zonda)	ジョンダノービス#n02	-1
-	duplicate(Dynamicnpc#zonda)	ジョンダバルサミコ#do01	-1
