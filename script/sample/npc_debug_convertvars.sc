//=====================================================================
// ■ 変数名補償NPC
//						created by Rayce
//  NPCスクリプトの改修に伴い変数名の統廃合を行いました。
//  以下のスクリプトを各プレイヤーに実行してもらうことで
//  変数の値を引き継ぐことができます。
//  ただし一部の変数については補償しません。
//---------------------------------------------------------------------

prontera.gat,155,192,4	script	変数名補償	114,{
	mes "[変数名補償]";
	mes "フラグ名を新仕様に変更します。";
	next;
	if(select("はい","いいえ")==2)
		close;

	// townフォルダ
	// 補償しない
	set turtle_npc,0;
	set kame_quest,0;
	if(event_sushi) {
		set AMA_1QUE,event_sushi;
		set event_sushi,0;
	}
	if(event_amatsu) {
		set AMA_2QUE,event_amatsu;
		set event_amatsu,0;
	}
	if(ayo_Q1) {
		set AYO_1QUE,ayo_Q1;
		set ayo_Q1,0;
	}
	if(ayo_Q2) {
		set AYO_2QUE,ayo_Q2;
		set ayo_Q2,0;
	}
	if(ayo_Q3) {
		set AYO_3QUE,ayo_Q3;
		set ayo_Q3,0;
	}
	if(COMODO_NPC) {
		set MJO_1QUE,COMODO_NPC;
		set COMODO_NPC,0;
	}
	if(ein_Q1) {
		set EIN_1QUE,ein_Q1;
		set ein_Q1,0;
	}
	if(ein_Q2) {
		set EIN_2QUE,ein_Q2;
		set ein_Q2,0;
	}
	if(ein_Q3) {
		set EIN_3QUE,ein_Q3;
		set ein_Q3,0;
	}
	if(ein_Q4) {
		set EIN_4QUE,ein_Q4;
		set ein_Q4,0;
	}
	// 補償しない
	set event_gonryun,0;
	set gonryun_ken,0;
	if(KF_PIT) {
		set KAFRA_PIT,KF_PIT;
		set KF_PIT,0;
	}
	if(Lou_que1) {
		set LOU_1QUE,Lou_que1;
		set Lou_que1,0;
	}
	if(Lou_que2) {
		set LOU_2QUE,Lou_que2;
		set Lou_que2,0;
	}
	if(Lou_ang) {
		set LOU_2QUE,LOU_2QUE|(Lou_ang<<4);
		set Lou_ang,0;
	}
	if(Lou_que3) {
		set LOU_3QUE,Lou_que3;
		set Lou_que3,0;
	}
	if(pump_event) {
		set PUMP_EVE,pump_event;
		set pump_event,0;
	}
	if(event_key) {
		set NIF_QUE,event_key;
		set event_key,0;
	}
	if(SEWER_PRT) {
		set PRT_QUE,SEWER_PRT;
		set SEWER_PRT,0;
	}
	if(event_umbala) {
		set UMB_QUE,event_umbala;
		set event_umbala,0;
	}
	if(npc_yunoalc) {
		set YUNO_1QUE,npc_yunoalc;
		set npc_yunoalc,0;
	}

	// questフォルダ
	if(arena_point) {
		set ARENA_PIT,arena_point;
		set arena_point,0;
	}
	if(turbo_point) {
		set TURBO_PIT,turbo_point;
		set turbo_point,0;
	}
	if(KAFRA_XMAS) {
		set BUNNY_EVE,KAFRA_XMAS;
		set KAFRA_XMAS,0;
	}
	if(MOLGENSTAIN) {
		set DYE_EVE,MOLGENSTAIN;
		set MOLGENSTAIN,0;
	}
	if(hairColor) {		// 廃止
		set hairColor,0;
	}
	if(hat_orchero) {
		set ORC_EVE,hat_orchero;
		set hat_orchero,0;
	}
	if(Ma_sword) {
		set DOOM_SWORD,DOOM_SWORD|Ma_sword;
		set Ma_sword,0;
	}
	if(ex_sword) {
		set DOOM_SWORD,DOOM_SWORD|((ex_sword*2-1)<<2);
		set ex_sword,0;
	}
	if(orga_sword) {
		set DOOM_SWORD,DOOM_SWORD|((orga_sword*2-1)<<4);
		set orga_sword,0;
	}
	if(mys_sword) {
		set DOOM_SWORD,DOOM_SWORD|((mys_sword*2-1)<<6);
		set mys_sword,0;
	}
	if(event_momo) {
		switch(event_momo) {
			default: set MOMO_EVE,1; break;
			case 4: set MOMO_EVE,2; break;
			case 10: set MOMO_EVE,3; break;
		}
		set event_momo,0;
	}
	if(event_oni) {
		set ONI_EVE,event_oni;
		set event_oni,0;
	}
	if(MORISON_MEAT) {
		if(MORISON_MEAT != 15)
			set JUICE_EVE,MORISON_MEAT;
		else
			set JUICE_EVE,12;
		set MORISON_MEAT,0;
	}
	if(MOTHER_MARIENU) {
		if(MOTHER_MARIENU == 2)
			set JUICE_EVE,13;
		set MOTHER_MARIENU,0;
	}
	if(skill_nov) {
		switch(skill_nov) {
		case 1:
		case 2:
			set SKILL_AID,skill_nov;
			break;
		case 3:
		case 6:
			set skill_nov,0;
			break;
		case 4:
		case 5:
			set SKILL_DEAD,skill_nov-3;
			break;
		}
	}
	if(skill_thief_1) {
		set SKILL_SAND,skill_thief_1;
		set skill_thief_1,0;
	}
	if(event_tougijou) {
		set COLOS_EVE,event_tougijou;
		set event_tougijou,0;
	}
	if(xmas_quest1) {
		set XMAS_1QUE,xmas_quest1;
		set xmas_quest1,0;
	}
	if(xmas_quest2) {
		set XMAS_2QUE,xmas_quest2;
		set xmas_quest2,0;
	}
	if(xmas_quest3) {
		set XMAS_3QUE,xmas_quest3;
		set xmas_quest3,0;
	}
	if(npc_yuno) {
		set YUNO_2QUE,npc_yuno;
		set npc_yuno,0;
	}
	if(newyear_quest) {
		set NEWY_QUE,newyear_quest;
		set NEWY_QUE,0;
	}

	// jobフォルダ
	// 補償しない
	set NEW_GETITEM,0;
	set NEW_JOBLVUP,0;
	set NEW_LVUP0,0;
	set NEW_LVUP1,0;
	set NEW_MES_FLAG0,0;
	set NEW_MES_FLAG1,0;
	set NEW_MES_FLAG2,0;
	set NEW_MES_FLAG3,0;
	set NEW_MES_FLAG4,0;
	set NEW_MES_FLAG5,0;
	set NEW_MES_FLAG6,0;
	set NOV_3_ACOLYTE,0;
	set NOV_3_ARCHER,0;
	set NOV_3_MAGICIAN,0;
	set NOV_3_MERCHANT,0;
	set NOV_3_SWORDMAN,0;
	set NOV_3_THIEF,0;
	if(change_sword) {
		if(change_sword == 5)
			set CHANGE_SM,4;
		else
			set CHANGE_SM,change_sword;
		set change_sword,0;
	}
	if(change_magic) {
		set CHANGE_MG,change_magic;
		set change_magic,0;
	}
	if(change_archer) {
		set CHANGE_AC,change_archer;
		set change_archer,0;
	}
	if(change_acolyte) {
		switch(change_acolyte) {
			case  0: set CHANGE_AL,0; break;
			case  1: set CHANGE_AL,3; break;
			case  2: set CHANGE_AL,2; break;
			case  3: set CHANGE_AL,1; break;
			case 10: set CHANGE_AL,6; break;
			case 20: set CAHNGE_AL,5; break;
			case 30: set CAHNGE_AL,4; break;
		}
	}
	// 補償しない
	set FIRST_JOB_QUEST,0;
	set JOB_MERCHANT_Q,0;
	set JOB_MERCHANT_Q2,0;
	set JOB_THIEF_Q,0;
	set Llowlv,0;
	set NOV_1ST_COS,0;
	set NOV_1_2_COS_C,0;
	set NOV_2ND_COS,0;
	if(change_thief) {
		set CHANGE_TF,change_thief;
		set change_thief,0;
	}
	if(change_knight) {
		set CHANGE_KN,change_knight;
		set change_knight,0;
	}
	if(change_priest) {
		set CHANGE_PR,change_priest;
		set change_priest,0;
	}
	set priest_meet1,0;	// 廃止
	set priest_meet2,0;
	set priest_meet3,0;
	if(job_wiz) {
		set CHANGE_WZ,job_wiz;
		set job_wiz,0;
	}
	if(change_blacksmith) {
		set change_blacksmith,0;	// 補償しない
	}
	if(change_hunter) {
		set CHANGE_HT,change_hunter;
		set change_hunter,0;
	}
	if(change_assassin) {
		set CHANGE_AS,change_assassin;
		set change_assassin,0;
	}
	if(job2nd_sage) {
		set CHANGE_SA,job2nd_sage;
		set job2nd_sage,0;
	}
	if(job2nd_sage2) {
		set job2nd_sage2,0;	// 廃止
	}
	if(sagecheck) {
		set SCORE_SA,sagecheck;
		set sagecheck,0;
	}
	if(change_rogue) {
		set CHANGE_RG,change_rogue;
		set change_rogue,0;
	}
	if(change_alchemist) {
		if(change_alchemist == 15)
			set CHANGE_AM,14;
		else
			set CHANGE_AM,change_alchemist;
		set change_alchemist,0;
	}
	if(job_snovice) {
		set CHANGE_SNV,job_snovice;
		set job_snovice,0;
	}
	if(oldjob) {
		set OLD_CLASS,oldjob;
		set oldjob,0;
	}
	if(job_transmigration) {
		if(job_transmigration == 1)
			set TRANSMIGRATE,job_transmigration;
		set job_transmigration,0;
	}

	// warpフォルダ
	set anthell,0;	// 廃止
	mes "[変数名変更]";
	mes "変更しました。";
	close;
OnInit:
	if(getarraysize($arenarecord_name$)) {
		copyarray $ArenaName$,$arenarecord_name$[1],4;
		cleararray $arenarecord_name$,"",5;
	}
	if(getarraysize($arenarecord_time)) {
		copyarray $ArenaTime,$arenarecord_time[1],4;
		cleararray $arenarecord_time,0,5;
	}
	end;
}
