//= Auriga Script ==============================================================
// Ragnarok Online Quest List Script
//==============================================================================
-	script	エイド#Quest	468,{
	misceffect 12,"";
	emotion 0;
	mes "[エイド]";
	mes "む……？";
	mes "この感じは……。";
	next;
	mes "[エイド]";
	mes "ちょっとそこのオマエ";
	mes "顔を見せてみろ。";
	next;
	mes "[エイド]";
	mes "オマエは多くの経験を";
	mes "積み重ねてきた冒険者のようだな。";
	mes "いい目をしている。";
	mes "オマエのような奴は嫌いではない。";
	next;
	mes "[エイド]";
	mes "さて、とくに用件が";
	mes "あったわけではないが";
	mes "呼び止めて";
	mes "しまったしな。";
	next;
	mes "[エイド]";
	mes "これも何かの縁だ。";
	mes "オマエの旅の軌跡を";
	mes "見てやろうか？";
	next;
	menu "え？",-;
	mes "[エイド]";
	mes "オレの左目は人の過去を";
	mes "見透かすことができる。";
	mes "別に金をとったりはしない。";
	mes "さて、どうする？";
	next;
	mes "[インフォメーション]";
	mes "^FF0000-既にクリアーされた";
	mes "クエストがクエストウィンドウに";
	mes "表示されるようになります。";
	mes "詳しくはクエストウィンドウ(Alt+U)を";
	mes "ご確認ください-";
	next;
	mes "[インフォメーション]";
	mes "^FF0000-なお、表示されるクエストは";
	mes "現在クエストウィンドウで";
	mes "対応されたもののみ";
	mes "表示されます-";
	next;
	if(select("お願いします","また今度にします") == 2) {
		mes "[エイド]";
		mes "そうか…。";
		mes "まぁいい。";
		mes "また、気が向いたら来るといい。";
		close;
	}
	mes "[エイド]";
	mes "わかった。";
	mes "そのまましばし待て。";
	next;
	mes "-エイドは何か呟きはじめた-";
	next;
	misceffect 8,"";
	misceffect 36,"";
	mes "[エイド]";
	mes "呪われし我がまなこ";
	mes "この者の旅の軌跡を示せ。";
	next;
	mes "[エイド]";
	mes "…";

	// ソードマン転職 [npc_job_01swordman.txt]
	if(CHANGE_SM > 0) setquest 1014;
	if(getbaseclass(Class,1) == CLASS_SM) chgquest 1014,50165;

	// マジシャン転職 [npc_job_02magician.txt]
	switch(CHANGE_MG) {
		case 1: setquest 1005; break;
		case 2: setquest 1006; break;
		case 3: setquest 1007; break;
		case 4: setquest 1008; break;
		default:
			if(getbaseclass(Class,1) == CLASS_MG) {
				chgquest 1005,50385;
				chgquest 1006,50385;
				chgquest 1007,50385;
				chgquest 1008,50385;
			}
			break;
	}

	// アーチャー転職 [npc_job_03archer.txt]
	if(CHANGE_AC > 0) setquest 1004;
	if(getbaseclass(Class,1) == CLASS_AC) chgquest 1004,50055;

	// アコライト転職 [npc_job_04acolyte.txt]
	switch(CHANGE_AL) {
		case 1: setquest 1001; break;
		case 2: setquest 1002; break;
		case 3: setquest 1003; break;
		case 4: chgquest 1001,50330; break;
		case 5: chgquest 1002,50335; break;
		case 6: chgquest 1003,50340; break;
		default:
			if(getbaseclass(Class,1) == CLASS_AL) {
				chgquest 50330,50345;
				chgquest 50335,50345;
				chgquest 50340,50345;
			}
			break;
	}

	// マーチャント転職 [npc_job_05merchant.txt]
	switch(CHANGE_MC) {
		case 1: case 2: case 9: case 10:
			setquest 1009;
			break;
		case 3: case 4: case 11: case 12:
			setquest 1010;
			break;
		case 5: case 6: case 13: case 14:
			setquest 1011;
			break;
		case 7: case 8: case 15: case 16:
			setquest 1012;
			break;
		case 17: case 18:
			chgquest 1009,50440;
			break;
		case 19: case 20:
			chgquest 1010,50445;
			break;
		case 21: case 22:
			chgquest 1011,50450;
			break;
		case 23: case 24:
			chgquest 1012,50455;
			break;
		case 25:
			chgquest 50440,50460;
			chgquest 50445,50460;
			chgquest 50450,50460;
			chgquest 50455,50460;
			break;
		default:
			if(getbaseclass(Class,1) == CLASS_MC)
				chgquest 50460,50465;
			break;
	}

	// シーフ転職 [npc_job_06thief.txt]
	switch(CHANGE_TF) {
		case 2: setquest 1013; break;
		case 3: chgquest 1013,50110; break;
		default:
			if(getbaseclass(Class,1) == CLASS_TF)
				chgquest 50110,50115;
			break;
	}

	// スーパーノービス転職 [npc_job_23supernovice.txt]
	if(CHANGE_SNV > 0) setquest 6010;
	if(getbaseclass(Class,1) == CLASS_SNV) chgquest 6010,50275;

	// テコンキッド転職 [npc_job_24taekwonkid.txt]
	switch(CHANGE_TK) {
		case 1: setquest 6000; break;
		case 2: chgquest 6000,6001; break;
		case 3: chgquest 6001,6002; break;
		default:
			if(getbaseclass(Class,1) == CLASS_TK)
				chgquest 6002,50220;
			break;
	}

	// ガンスリンガー転職 [npc_job_28gunslinger.txt]
	switch(CHANGE_GS) {
		case 1: setquest 6020; break;
		case 2: chgquest 6020,6021; break;
		case 3: chgquest 6021,6022; break;
		case 4: chgquest 6022,6023; break;
		case 5: chgquest 6023,6024; break;
		default:
			if(getbaseclass(Class,1) == CLASS_GS)
				chgquest 6024,50550;
			break;
	}

	// 忍者転職 [npc_job_29ninja.txt]
	switch(CHANGE_NJ) {
		case 1: setquest 6015; break;
		case 2: chgquest 6015,6016; break;
		case 3: chgquest 6016,6017; break;
		case 4: chgquest 6017,6018; break;
		default:
			if(getbaseclass(Class,1) == CLASS_NJ)
				chgquest 6018,50495;
			break;
	}

	// 転生 [npc_job_transmigration.txt]
	if(TRANSMIGRATE > 0) setquest 1000;
	if(Upper == UPPER_HIGH) chgquest 1000,50000;

	// 魔王モロク討伐 [npc_town_morocc.txt]
	switch(MOC_2QUE) {
		case 1: setquest 3050; break;
		case 2: chgquest 3050,3051; break;
		case 3: chgquest 3051,3052; break;
		case 4: chgquest 3052,3053; break;
		case 5: chgquest 3053,3055; break;
		case 6: chgquest 3055,3056; break;
		case 7: chgquest 3056,59345; break;
	}

	// 運命のカラス [npc_town_morocc.txt]
	switch(MOC_3QUE) {
		case 1:
			setquest 2063;
			break;
		case 2: case 3: case 4: case 5: case 6:
			chgquest 2063,2064;
			break;
		case 7:
			chgquest 2064,2065;
			break;
		case 8: case 9:
			chgquest 2065,2066;
			break;
		case 10:
			chgquest 2066,2067;
			break;
		case 11: case 12: case 13: case 14:
			chgquest 2067,2068;
			break;
		case 15:
			chgquest 2068,59455;
			break;
		case 16:
			chgquest 59455,59460;
			break;
	}

	next;
	mes "[エイド]";
	mes "……";
	next;
	mes "[エイド]";
	mes "………。";
	mes "ふむ、オマエの旅の";
	mes "軌跡を見せてもらった。";
	mes "また、気が向いたら来るといい。";
	close;
}

prontera.gat,106,69,5	duplicate(エイド#Quest)	エイド	880
izlude.gat,133,92,3	duplicate(エイド#Quest)	エイド	880
geffen.gat,115,65,5	duplicate(エイド#Quest)	エイド	880
morocc.gat,160,97,3	duplicate(エイド#Quest)	エイド	880
payon.gat,178,104,3	duplicate(エイド#Quest)	エイド	880
alberta.gat,122,59,3	duplicate(エイド#Quest)	エイド	880
