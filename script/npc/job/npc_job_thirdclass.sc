//====================================================================
//Ragnarok Online - 3rd Class Jobchange Script	by refis
//====================================================================

//==========================================
// 転職NPC
//------------------------------------------

function	script	jobchenge3rd_func	{
	function	job_name	{
		switch(getarg(0)) {
		case Job_Knight:		return "ロードナイト";
		case Job_Priest:		return "ハイプリースト";
		case Job_Wizard:		return "ハイウィザード";
		case Job_Blacksmith:	return "ホワイトスミス";
		case Job_Hunter:		return "スナイパー";
		case Job_Assassin:		return "アサシンクロス";
		case Job_Crusader:		return "パラディン";
		case Job_Monk:			return "チャンピオン";
		case Job_Sage:			return "プロフェッサー";
		case Job_Rogue:			return "チェイサー";
		case Job_Alchemist:		return "クリエイター";
		case Job_Bard:			return "クラウン";
		case Job_Dancer:		return "ジプシー";
		case Job_RuneKnight:	return "ルーンナイト";
		case Job_Warlock:		return "ウォーロック";
		case Job_Ranger:		return "レンジャー";
		case Job_ArchBishop:	return "アークビショップ";
		case Job_Mechanic:		return "メカニック";
		case Job_Guillotine:	return "ギロチンクロス";
		case Job_RoyalGuard:	return "ロイヤルガード";
		case Job_Sorcerer:		return "ソーサラー";
		case Job_Minstrel:		return "ミンストレル";
		case Job_Wanderer:		return "ワンダラー";
		case Job_Shura:			return "修羅";
		case Job_Genetic:		return "ジェネティック";
		case Job_ShadowChaser:	return "シャドウチェイサー";
		}
	}

	set '@job,getarg(0);
	set '@3rdName$, job_name('@job);
	if(Job == '@job) {
		mes "[転職代行係]";
		mes "おお、貴方は";
		mes '@3rdName$ +"ですね。";
		mes "もう転職は完了していますよ。";
		close;
	}
	if(Job != getarg(1) || Upper == UPPER_NORMAL ||
	  (Upper == UPPER_HIGH && BaseLevel < 90) ||
	  (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50)) ) {
		mes "[転職代行係]";
		mes "こんにちは。";
		mes "貴方の周りに、";
		mes '@3rdName$ +"への";
		mes "転職を望む者はいませんか？";
		next;
		mes "[転職代行係]";
		mes "もしいましたら、";
		mes "私のところへ来るように";
		mes "伝えてください。";
		mes "今なら条件さえ満たしていれば";
		mes "すぐ転職できますよ。";
		close;
	}
	if(SkillPoint) {
		mes "‐スキルポイントが余っているため";
		mes "　進行できません‐";
		close;
	}
	mes "[転職代行係]";
	mes "こんにちは。";
	if(Upper == UPPER_HIGH)
		mes "貴方は"+ job_name(Job) +"ですね。";
	mes '@3rdName$ +"への転職を";
	mes "望みますか？";
	next;
	mes "[転職代行係]";
	mes "なお、"+ '@3rdName$ +"へ転職すると";
	mes "ステータスとスキルが全て";
	mes "リセットされます。";
	next;
	if(select("転職しない","^0000FF転職する^000000")==1) {
		mes "[転職代行係]";
		mes "わかりました。";
		mes "それもひとつの道でしょう。";
		close;
	}
	if(Weight || SkillPoint || checkriding() || checkcart() || checkfalcon() || sc_ison(SC_ALL_RIDING)) {
		mes "[転職代行係]";
		mes "あなたは準備しなければ";
		mes "ならないことがありますね。";
		mes "まずは、身を清める為に";
		mes "身のまわりのものを";
		mes "無にしてください。";
		next;
		mes "[転職代行係]";
		mes "アイテムやスキルポイントなど";
		mes "何も持たない";
		mes "状態でなければなりません。";
		mes "旅を共にした動物達やカート、";
		mes "騎乗生物なども";
		mes "持って行くことはできません。";
		next;
		mes "[転職代行係]";
		mes "それでは……用意ができましたら";
		mes "お越しください。";
		close;
	}
	if('@job == Job_RuneKnight) {
		mes "[転職代行係]";
		mes "転職する為の準備は万全のようですね。";
		mes "それでは、転職する前に、";
		mes "これからご紹介します装備のうち";
		mes "いずれか1つをお選びください。";
		mes "お選びになった装備が、";
		mes "転職の際に渡されます。";
		next;
		mes "[転職代行係]";
		mes "まず、装備の詳細について";
		mes "ご説明しますので、";
		mes "詳細が知りたい装備を";
		mes "お選び下さい。";
		while(1) {
			next;
			switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]","説明は大丈夫です")) {
			case 1:
				mes "[転職代行係]";
				mes "エナジールーンガード[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "豪華な青色の光の";
				mes "エナジールーンが";
				mes "ちりばめられている";
				mes "羽模様の盾。";
				mes "清く清明な気が溢れて";
				mes "自身と精神を刺激する。";
				next;
				mes "[装備詳細]";
				mes "系列 : 盾";
				mes "防御 : 70";
				mes "重量 : 0";
				mes "要求レベル : 99";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果： MaxSP + 2%";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 2:
				mes "[転職代行係]";
				mes "魔力石の指輪[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "不思議なルーンが";
				mes "刻まれている";
				mes "青色のリング。";
				mes "輝くルーンから";
				mes "神秘な活力が感じ取れる。";
				next;
				mes "[装備詳細]";
				mes "系列 : アクセサリー";
				mes "防御 : 0";
				mes "重量 : 0";
				mes "要求レベル : 90";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果： Str + 2";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 3:
				mes "[転職代行係]";
				mes "ルーンプレート[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "ルーンと宝石で飾られた";
				mes "プレートアーマー。";
				mes "見た目より軽いが、";
				mes "魔力により防御力が";
				mes "強化されている。";
				next;
				mes "[装備詳細]";
				mes "系列 : 鎧";
				mes "防御 : 95";
				mes "重量 : 0";
				mes "要求レベル : 99";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果：精錬不可、破壊不可。";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 4:
				mes "[転職代行係]";
				mes "それでは、貴方が欲しい";
				mes "装備をお選び下さい。";
				while(1) {
					next;
					switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]")) {
					case 1:
						set '@gain,2140;
						break;
					case 2:
						set '@gain,2794;
						break;
					case 3:
						set '@gain,15002;
						break;
					}
					next;
					mes "[転職代行係]";
					mes getitemname('@gain) +"[1]ですね。";
					mes "本当にこちらでよろしいですか？";
					next;
					if(select("はい","いいえ")==2) {
						mes "[転職代行係]";
						mes "それでは再度、";
						mes "欲しい装備を";
						mes "お選び下さい。";
						continue;
					}
					break;
				}
			}
			break;
		}
	}
	resetstatus;
	resetskill;
	setoption 0;
	jobchange '@job;
	switch(Job) {
	case Job_RuneKnight:
		setquest 201180;
		getitem 5746,1;	//ルーンサークレット
		getitem '@gain,1;	//選択装備
		break;
	case Job_ArchBishop:
		setquest 201195;
		getitem 5747,1;	//ミトラ
		break;
	case Job_Warlock:
		setquest 201185;
		getitem 5753,1;	//魔力石の帽子
		break;
	case Job_Mechanic:
		setquest 201205;
		if(Sex)
			getitem 5749,1;	//ドライバーバンド(male)
		else
			getitem 5760,1;	//ドライバーバンド(female)
		break;
	case Job_Ranger:
		setquest 201190;
		getitem 6124,1;	//狼の笛
		getitem 5748,1;	//スナイパーゴーグル
		break;
	case Job_Guillotine:
		setquest 201200;
		getitem 5755,1;	//沈黙の執行者
		getitem 12106,1;	//宝石箱
		break;
	case Job_RoyalGuard:
		setquest 201210;
		getitem 5757,1;	//シュミッツのヘルム
		break;
	case Job_Shura:
		setquest 201230;
		getitem 5754,1;	//ブレイジングソウル
		break;
	case Job_Sorcerer:
		setquest 201215;
		getitem 5756,1;	//風のささやき
		break;
	case Job_ShadowChaser:
		setquest 201235;
		getitem 6121,1;	//フェイスペイントブラシ
		getitem 6122,1;	//ペイントブラシ
		getitem 5750,1;	//シャドウクラウン
		break;
	case Job_Genetic:
		setquest 201240;
		getitem 5752,1;	//ミダスのささやき
		break;
	case Job_Minstrel:
		setquest 201220;
		getitem 5751,1;	//ミンストレルソングの帽子
		break;
	case Job_Wanderer:
		setquest 201225;
		getitem 5758,1;	//バレリーナの髪飾り
		break;
	}
	getitem 2795,1;	//熟していないリンゴの指輪
	if(Upper == UPPER_BABY) {
		for(set '@i,22954;'@i<=22969;set '@i,'@i+1) {
			if(countitem('@i))
				delitem '@i,1;
		}
		if(countitem(25018)) delitem 25018,1;
		if(countitem(25019)) delitem 25019,1;
		if(countitem(25020)) delitem 25020,1;
		if(getequipid(14) == 20307) unequip 14;
		if(countitem(20307)) delitem 20307,1;
	}
	mes "[転職代行係]";
	mes "さあ、これで貴方は";
	mes '@3rdName$ +"となりました。";
	mes "見た目も気持ちも一新ですね！";
	close;
}

prt_in.gat,162,24,3	script	転職代行係#runeknight	888,{ callfunc "jobchenge3rd_func",Job_RuneKnight,Job_Knight; }
morocc.gat,94,141,3	script	転職代行係#warlock	888,{ callfunc "jobchenge3rd_func",Job_Warlock,Job_Wizard; }
alberta.gat,223,111,5	script	転職代行係#ranger	888,{ callfunc "jobchenge3rd_func",Job_Ranger,Job_Hunter; }
prt_church.gat,103,88,3	script	転職代行係#arch	888,{ callfunc "jobchenge3rd_func",Job_ArchBishop,Job_Priest; }
yuno.gat,129,156,3	script	転職代行係#mechanic	888,{ callfunc "jobchenge3rd_func",Job_Mechanic,Job_Blacksmith; }
que_job01.gat,75,96,3	script	転職代行係#guillotine	888,{ callfunc "jobchenge3rd_func",Job_Guillotine,Job_Assassin; }
prt_castle.gat,48,161,3	script	転職代行係#roya	888,{ callfunc "jobchenge3rd_func",Job_RoyalGuard,Job_Crusader; }
gef_tower.gat,102,34,3	script	転職代行係#sorc	888,{ callfunc "jobchenge3rd_func",Job_Sorcerer,Job_Sage; }
alberta.gat,196,133,3	script	転職代行係#mins	888,{ callfunc "jobchenge3rd_func",Job_Minstrel,Job_Bard; }
xmas.gat,162,209,3	script	転職代行係#wand	888,{ callfunc "jobchenge3rd_func",Job_Wanderer,Job_Dancer; }
ve_in.gat,237,125,3	script	転職代行係#sura	888,{ callfunc "jobchenge3rd_func",Job_Shura,Job_Monk; }
alde_alche.gat,35,186,3	script	転職代行係#gene	888,{ callfunc "jobchenge3rd_func",Job_Genetic,Job_Alchemist; }
morocc.gat,156,70,3	script	転職代行係#shad	888,{ callfunc "jobchenge3rd_func",Job_ShadowChaser,Job_Rogue; }


//==========================================
// ドラゴンレンタル
//------------------------------------------

prontera.gat,129,212,5	script	ドラゴン管理兵	105,{
	if(Job != Job_RuneKnight) {
		mes "[ドラゴン管理兵]";
		mes "何の御用ですか？";
		mes "ドラゴンは、ルーンナイト様専用";
		mes "となっております。";
		close;
	}
//	mes "[ドラゴン管理]";		//脱字。本家仕様
	mes "[ドラゴン管理兵]";
	mes "いらっしゃいませ。";
	mes "ドラゴンをご利用ですか？";
	next;
	if(select("利用する","やめる")==2) {
		mes "[ドラゴン管理兵]";
		mes "そうですか。では……";
		close;
	}
	if(checkdragon()) {
		close;
	}
//	if(getskilllv(2007) < 1) {	//未修得でも騎乗可
//		close;
//	}
	setdragon;
	close;
}


//==========================================
// グリフォンレンタル
//------------------------------------------

prontera.gat,125,208,5	script	グリフォン管理兵	105,{
	if(Job != Job_RoyalGuard) {
		mes "[グリフォン管理兵]";
		mes "何の御用ですか？";
		mes "グリフォンは、ロイヤルガード様専用";
		mes "となっております。";
		close;
	}
	//未調査
	mes "[グリフォン管理兵]";
	mes "いらっしゃいませ。";
	mes "グリフォンをご利用ですか？";
	next;
	if(select("利用する","やめる")==2) {
		mes "[グリフォン管理兵]";
		mes "そうですか。では……";
		close;
	}
	if(checkriding()) {
		close;
	}
	if(getskilllv(63) < 1) {
		mes "[グリフォン管理兵]";
		mes "……まだグリフォンには";
		mes "乗れないようですね。";
		mes "スキル「ライディング」を";
		mes "覚えてからお越しください。";
		close;
	}
	setriding;
	close;
}


//==========================================
// 魔導ギアレンタル
//------------------------------------------

-	script	3rdRentalGear	-1,{
	if(Job != Job_Mechanic) {
		mes "[魔導ギア管理兵]";
		mes "私はメカニックの方へお貸しする";
		mes "魔導ギアの管理を行っています。";
		close;
	}
	mes "[魔導ギア管理兵]";
	mes "メカニックの方ですね。";
	mes "カートを利用しますか？";
	mes "それとも魔導ギアに搭乗しますか？";
	mes "無料でお貸ししますよ。";
	next;
	switch(select("カートを借りる","魔導ギアに乗る","乗らない")) {
	case 1:
		if(checkcart()) {
			mes "[魔導ギア管理兵]";
			mes "既にカートを";
			mes "利用されていますね。";
			close;
		}
		setcart;
		close;
	case 2:
		if(checkgear()) {
			mes "[魔導ギア管理兵]";
			mes "すでに魔導ギアに乗って";
			mes "いらっしゃいますね。";
			close;
		}
		if(getskilllv(2255) < 1) {
			mes "[魔導ギア管理兵]";
			mes "すみませんが、";
			mes "魔導ギアライセンスを";
			mes "習得していない方への";
			mes "貸し出しは行っていません。";
			mes "習得してからお越しください。";
			close;
		}
		setgear;
		close;
	case 3:
		mes "[魔導ギア管理兵]";
		mes "そうですか……";
		mes "魔導ギアを利用される際は";
		mes "私に声がけください。";
		close;
	}
}

prontera.gat,163,178,3		duplicate(3rdRentalGear)	魔導ギア管理兵#pro		105
dicastes01.gat,187,203,3	duplicate(3rdRentalGear)	魔導ギア管理兵#dicas	105
mora.gat,91,112,3			duplicate(3rdRentalGear)	魔導ギア管理兵#mora		105
ecl_in01.gat,41,25,5		duplicate(3rdRentalGear)	魔導ギア管理兵#ecl		105

//==========================================
// ルーン原石販売員 - ルーンナイト
//------------------------------------------

prontera.gat,168,228,3	script	ルーン原石販売員#pro	853,{
	mes "[ルーン原石販売員]";
	mes "あなたはもしかして、";
	mes "ルーン原石をお求めですかな!?";
	mes "　";
	mes "今なら、いい原石をお売りしますよ。";
	next;
	switch(select("高級なルーン原石を買う","一般的なルーン原石を買う")) {
	case 1:
		mes "[ルーン原石販売員]";
		mes "ほほ～、これはお目が高い！";
		mes "高級なルーン原石ですな。";
		set '@price,2500;
		set '@gain,12734;
		break;
	case 2:
		mes "[ルーン原石販売員]";
		mes "お～、実に堅実な方ですな！";
		mes "一般的なルーン原石をお求めとは。";
		set '@price,1000;
		set '@gain,12737;
		break;
	}
	mes "この原石は1個 "+ '@price +"Zenyで";
	mes "お売りしましょう！";
	mes "2000個までなら、1度で渡しましょう。";
	mes "いくつ買いますかな？";
	next;
	input '@num;
	if('@num == 0) {
		mes "[ルーン原石販売員]";
		mes "おや、そうですか。";
		mes "残念ですな。";
		mes "買いたくなったら、";
		mes "またお越しください。";
		close;
	}
	if('@num < 1 || '@num > 2000) {
		mes "[ルーン原石販売員]";
		mes "お客さん、冗談でしょう。";
		mes "ちゃんと数を言ってもらわないと";
		mes "用意できませんよ。";
		mes "1度でお売りできるのは";
		mes "1～2000個ですからな。";
		close;
	}
	if(Zeny < '@price*'@num) {
		mes "[ルーン原石販売員]";
		mes "おやおや？";
		mes "お客さん、困りますな～";
		mes "Zenyが足りませんよ。";
		mes "しっかり払ってもらわないと";
		mes "商売あがったりですからな。";
		mes "お金を用意して、また来てください。";
		close;
	}
	if(checkitemblank()==0) {
		mes "[ルーン原石販売員]";
		mes "おっと!?";
		mes "お客さん、ちょっと荷物が";
		mes "多すぎるようですな。";
		mes "これでは、購入数の";
		mes getitemname('@gain) +"を渡せそうにない。";
		mes "身軽にしてから、また来てください。";
		close;
	}
	if(checkweight('@gain,'@num)==0) {
		mes "[ルーン原石販売員]";
		mes "おっと!?";
		mes "お客さん、ちょっと荷物が";
		mes "重過ぎるようですな。";
		mes "これでは、購入数の";
		mes getitemname('@gain)+ "を渡せそうにない。";
		mes "身軽にしてから、また来てください。";
		close;
	}
	set Zeny,Zeny - '@price * '@num;
	getitem '@gain,'@num;
	mes "[ルーン原石販売員]";
	mes "毎度ありがたいですな。";
	mes "またのご利用、";
	mes "お待ちしておりますよ。";
	close;
}


//==========================================
// トラップ専門家 - レンジャー
//------------------------------------------

-	shop	AlloyTrapShopper	-1,7940,12341

prt_in.gat,109,68,4		substore(AlloyTrapShopper)	トラップ専門家	66
mid_camp.gat,129,284,4	substore(AlloyTrapShopper)	トラップ専門家	66
payon.gat,123,109,4		substore(AlloyTrapShopper)	トラップ専門家	66
ra_in.gat,263,281,4		substore(AlloyTrapShopper)	トラップ専門家	66
lighthalzen.gat,337,240,4	substore(AlloyTrapShopper)	トラップ専門家	66


//==========================================
// 毒製造キット販売員 - ギロチンクロス
//------------------------------------------

-	script	3rdPoisonShopper	-1,{
	mes "[毒製造キット販売員]";
	mes "毒製造キットはいりませんか～？";
	mes "　";
	mes "毒製造キットは１つ";
	mes "5000zenyですよ～";
	mes "　";
	mes "買いますか～？";
	next;
	if(select("はい","いいえ")==2) {
		mes "[毒製造キット販売員]";
		mes "そうですか～";
		mes "わかりました～";
		mes "また来てくださいね～";
		close;
	}
	if(Zeny < 5000) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、お金が足りませんよ～";
		mes "お金を増やして、またきて下さ～い。";
		close;
	}
	if(checkitemblank()==0) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、所持している荷物が";
		mes "多いですね～";
		mes "これでは毒製造キットを";
		mes "渡せませんよ～";
		mes "身を軽くしてからまたきて下さ～い。";
		close;
	}
	if(checkweight(7931,1)==0) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、所持している荷物が";
		mes "重すぎですよ～";
		mes "これでは毒製造キットを";
		mes "渡せませんよ～";
		mes "身を軽くしてからまたきて下さ～い。";
		close;
	}
	set Zeny,Zeny - 5000;
	getitem 7931,1;
	mes "[毒製造キット販売員]";
	mes "お買い上げ～";
	mes "ありがとうございま～す。";
	mes "またお越しくださ～い。";
	close;
}

morocc.gat,185,95,4	duplicate(3rdPoisonShopper)	毒製造キット販売員#moc	877
lhz_in02.gat,16,205,4	duplicate(3rdPoisonShopper)	毒製造キット販売員#lhz	877


//==========================================
// 闇販売員 - メカニック
//------------------------------------------

-	shop	MechanicShopper	-1,2139,2800,2801,2802,2803,2804,2805,2806,2807,18000,18001,18002,18003,18004,12392,12393,12394,6145,12383,6146,6147,6186,2808

prt_in.gat,175,137,4	substore(MechanicShopper)	闇販売員	49
mid_camp.gat,184,263,4	substore(MechanicShopper)	闇販売員	49
einbroch.gat,122,250,4	substore(MechanicShopper)	闇販売員	49
ra_in.gat,257,266,4		substore(MechanicShopper)	闇販売員	49
lhz_in03.gat,181,17,4	substore(MechanicShopper)	闇販売員	49


//==========================================
// 媒体販売 - ミンストレル、ワンダラー
//------------------------------------------

comodo.gat,196,162,3	shop	カリブ#comodo	479,11513,6144


//==========================================
// ポイント商人 - レンジャー、ソーサラー
//------------------------------------------

gef_tower.gat,105,172,5	script	ポイント商人	700,{
	mes "[ポイント商人]";
	mes "こんにちは。";
	mes "ここでは鉱石をさらに砕いた";
	mes "触媒として使用する";
	mes "^FF0000各種ポイント^000000を販売しています。";
	mes "何か必要ですか？";
	next;
	switch(select("スカーレットポイント(火) - 200z","ライムグリーンポイント(地) - 200z","インディゴポイント(水) - 200z","イエローウィッシュポイント(風) - 200z","会話を終える")) {
	case 1:
		set '@itemid,6360;
		set '@element$,"火属性";
		break;
	case 2:
		set '@itemid,6363;
		set '@element$,"地属性";
		break;
	case 3:
		set '@itemid,6361;
		set '@element$,"水属性";
		break;
	case 4:
		set '@itemid,6362;
		set '@element$,"風属性";
		break;
	case 5:
		mes "[ポイント商人]";
		mes "またのご利用をお待ちしています。";
		close;
	}
	mes "[ポイント商人]";
	mes "^ff0000" +getitemname('@itemid)+ "^000000ですね。";
	mes "こちらは^0000ff" +'@element$+ "^000000のポイントです。";
	mes "何個購入しますか？";
	mes "同時に1000個まで購入できます。";
	mes "キャンセルするには、";
	mes "0を入力してください。";
	next;
	input '@num;
	if('@num == 0) {
		mes "[ポイント商人]";
		mes "キャンセルしました。";
		mes "またのご利用をお待ちしています。";
		close;
	}
	if('@num < 0 || '@num > 1000) {
		mes "[ポイント商人]";
		mes "正しい数を入力してください。";
		mes "一度に購入できるのは";
		mes "1000個までとなります。";
		close;
	}
	mes "[ポイント商人]";
	mes "^ff0000" +getitemname('@itemid)+ "^000000を";
	mes "^0000ff" +'@num+ "個^000000で";
	mes "よろしいですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[ポイント商人]";
		mes "キャンセルしました。";
		mes "またのご利用をお待ちしています。";
		close;
	}
	if(200*'@num > Zeny) {
		mes "[ポイント商人]";
		mes "お客様、すみませんが、";
		mes "所持金が不足しています。";
		close;
	}
	if(checkweight('@itemid,'@num) == 0) {
		mes "[ポイント商人]";
		mes "おや、荷物が一杯のようです。";
		mes "少し数を減らしてから、";
		mes "ご利用ください。";
		close;
	}
	set Zeny,Zeny-200*'@num;
	getitem '@itemid,'@num;
	mes "[ポイント商人]";
	mes "ご利用ありがとうございます。";
	close;
}


//==========================================
// 製造本販売員 - ジェネティック
//------------------------------------------

comodo.gat,106,213,5	shop	南国の果物商人	724,6258

alde_alche.gat,31,186,3	script	製造本販売員#alde	883,{
	mes "[製造本販売員]";
	mes "こんにちは！";
	mes "私はジェネティックの";
	mes "^0000FF特別な製造本^000000を販売しています！";
	next;
	mes "[製造本販売員]";
	mes "知ってました？";
	mes "ジェネティックは製造本を";
	mes "所持していないと、";
	mes "使えない製造スキルが";
	mes "あるんですよ。";
	next;
	mes "[製造本販売員]";
	mes "所持している製造本の";
	mes "^FF0000種類^000000が多ければ多いほど、";
	mes "製造できるアイテムの種類も";
	mes "増えるんですよ。";
	next;
	mes "[製造本販売員]";
	mes "いや～、この本内容が難しいので、";
	mes "売れなくて困ってたんですよ。";
	mes "1冊あれば、製造の材料はわかるので、";
	mes "充分なんですけど、";
	mes "何冊でも売りますよ！";
	mes "製造本を購入しますか？";
	next;
	if(select("はい","いいえ")==2) {
		mes "[製造本販売員]";
		mes "では、また来てください。";
		mes "いつでも、お待ちしてますよ！";
		close;
	}
	if(checkitemblank()==0) {
		mes "[製造本販売員]";
		mes "持っている荷物の数が";
		mes "多すぎますね。";
		mes "これでは本を";
		mes "渡せませんよ。";
		mes "荷物を整理してから";
		mes "また来てください。";
		close;
	}
	if(Weight*100/MaxWeight >= 90) {
		mes "[製造本販売員]";
		mes "持っている荷物の重量が";
		mes "重すぎますね。";
		mes "これでは本を";
		mes "渡せませんよ。";
		mes "荷物を整理してから";
		mes "また来てください。";
		close;
	}
	mes "[製造本販売員]";
	mes "ほ、本当ですか～！";
	mes "ありがとうございます！";
	mes "それでは、製造本のリストを";
	mes "お見せしますね！";
	mes "できれば、いっぱい";
	mes "買っていってください！";
	while(1){
		next;
		switch(select(
			"[リンゴ爆弾製造本] 100,000 zeny",
			"[パイナップル爆弾製造本] 100,000 zeny",
			"[ココナッツ爆弾製造本] 100,000 zeny",
			"[メロン爆弾製造本] 100,000 zeny",
			"[バナナ爆弾製造本]100,000 zeny",
			"[遺伝子組み換え植物栽培法]100,000 zeny",
			"[上級ポーション製造マニュアル] 100,000 zeny",
			"[ミックスクッキング料理本] 100,000 zeny",
			"[スタミナ増進研究書] 100,000 zeny",
			"[活力ドリンク製造法]100,000 zeny",
			"購入を終了する。")) {
		case 1:		//リンゴ爆弾製造本
			set '@gain,6279;
			break;
		case 2:		//パイナップル爆弾製造本
			set '@gain,6280;
			break;
		case 3:		//ココナッツ爆弾製造本
			set '@gain,6281;
			break;
		case 4:		//メロン爆弾製造本
			set '@gain,6282;
			break;
		case 5:		//バナナ爆弾製造本
			set '@gain,6283;
			break;
		case 6:		//遺伝子組み換え植物栽培法
			set '@gain,6284;
			break;
		case 7:		//上級ポーション製造マニュアル
			set '@gain,6285;
			break;
		case 8:		//ミックスクッキング料理本
			set '@gain,11022;
			break;
		case 9:		//スタミナ増進研究書
			set '@gain,11023;
			break;
		case 10:	//活力ドリンク製造法
			set '@gain,11024;
			break;
		case 11:
			mes "[製造本販売員]";
			mes "そうですか。";
			mes "また来てくださいね！";
			close;
		}
		mes "[製造本販売員]";
		mes "^0000FF[" +getitemname('@gain)+ "]^000000は";
		mes "100,000 zenyです。";
		mes "何冊購入します？";
		mes "1冊でも充分ですけど、";
		mes "100冊とか買ってもらっても";
		mes "いいですよ！";
		next;
		input '@num;
		if('@num == 0) {
			mes "[製造本販売員]";
			mes "他の本はいかがですか。";
			continue;
		}
		if('@num < 1 || '@num > 100) {
			mes "[製造本販売員]";
			mes "う～ん、残念！";
			mes "1度に購入できるのは";
			mes "100冊までなんです。";
			continue;
		}
		mes "[製造本販売員]";
		mes "^0000FF[" +getitemname('@gain)+ "]^000000を";
		mes '@num+ " 冊購入ですね！";
		mes "　";
		mes "よろしいですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[製造本販売員]";
			mes "そ、そうですか……";
			mes "製造本はいっぱいありますから、";
			mes "遠慮することはないですよ。";
			continue;
		}
		if(Zeny < 100000 * '@num){
			mes "[製造本販売員]";
			mes "あ～、ちょっとお金が";
			mes "足りないみたいですね。";
			mes "お金を用意して来てください。";
			close;
		}
		mes "[製造本販売員]";
		mes "ありがとうございます！";
		mes "他の本はいりませんか？";
		set Zeny,Zeny - 100000 * '@num;
		getitem '@gain,'@num;
		continue;
	}
}


//==========================================
// 影工房 - シャドウチェイサー
//------------------------------------------

-	shop	PaintingShopper	-1,6123,6120

s_atelier.gat,17,110,1	substore(PaintingShopper)	販売員#sc_prt	67
s_atelier.gat,137,60,3	substore(PaintingShopper)	販売員#sc_ra	70
s_atelier.gat,114,117,1	substore(PaintingShopper)	販売員#sc_yuno	92
s_atelier.gat,15,65,5	substore(PaintingShopper)	販売員#sc_lgt	89
