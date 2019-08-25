//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー          by Pneuma
//
// -----------------------------------------------------------

//============================================================
// WARP

// 2010/05/04以降、乗ると初回のみ確認メッセージが出るWPについては
// コメントアウトし、別途下部にスクリプトとして追加しました。

// ------------------------------------------------------------------------------
//エントランス⇔教室棟ホール
//ac_en_hall.gat,54,13,0		warp	acwarp003	1,1,ac_cl_hall.gat,167,22
//ac_cl_hall.gat,167,19,0		warp	acwarp004	1,1,ac_en_hall.gat,57,13

// ------------------------------------------------------------------------------
//エントランス⇔図書館
//ac_en_hall.gat,143,13,0		warp	acwarp005	1,1,ac_library.gat,32,58
ac_library.gat,29,58,0		warp	acwarp006	1,1,ac_en_hall.gat,140,13

// ------------------------------------------------------------------------------
//教室棟ホール⇔教室棟1F
//ac_cl_hall.gat,167,72,0		warp	acwarp018	1,1,ac_cl_area.gat,73,156
//ac_cl_area.gat,76,156,0		warp	acwarp019	1,1,ac_cl_hall.gat,167,69

// ------------------------------------------------------------------------------
//受付⇔教室棟1F
//ac_cl_area.gat,35,133,0		warp	acwarp020	2,2,ac_cl_room.gat,43,19

// ------------------------------------------------------------------------------
//教室棟1F⇔自習室
//ac_cl_area.gat,35,176,0		warp	acwarp021	2,2,ac_cl_room.gat,152,21
//ac_cl_room.gat,152,18,0		warp	acwarp022	1,1,ac_cl_area.gat,38,176

// ------------------------------------------------------------------------------
//教室棟1F⇔教室棟2F
//ac_cl_area.gat,30,185,0		warp	acwarp023	2,2,ac_cl_area.gat,67,74
//ac_cl_area.gat,71,74,0		warp	acwarp024	1,1,ac_cl_area.gat,36,185
//ac_cl_area.gat,30,125,0		warp	acwarp025	2,2,ac_cl_area.gat,67,14
//ac_cl_area.gat,71,14,0		warp	acwarp026	1,1,ac_cl_area.gat,36,125

// ------------------------------------------------------------------------------
//図書館入り口⇔図書館中央
ac_library.gat,52,58,0		warp	acwarp006	1,1,ac_library.gat,98,58
ac_library.gat,95,58,0		warp	acwarp007	1,1,ac_library.gat,49,58

// ------------------------------------------------------------------------------
//図書館中央⇔図書館内上の部屋
ac_library.gat,103,64,0		warp	acwarp008	1,1,ac_library.gat,103,96
ac_library.gat,103,93,0		warp	acwarp009	1,1,ac_library.gat,103,61
ac_library.gat,115,64,0		warp	acwarp010	1,1,ac_library.gat,115,95
ac_library.gat,115,93,0		warp	acwarp011	1,1,ac_library.gat,115,61

// ------------------------------------------------------------------------------
//図書館中央⇔図書館内下の部屋
ac_library.gat,103,51,0		warp	acwarp012	1,1,ac_library.gat,103,19
ac_library.gat,103,22,0		warp	acwarp013	1,1,ac_library.gat,103,54
ac_library.gat,115,51,0		warp	acwarp014	1,1,ac_library.gat,115,19
ac_library.gat,115,22,0		warp	acwarp015	1,1,ac_library.gat,115,54

// ------------------------------------------------------------------------------
//図書館中央⇔図書館内右の部屋
ac_library.gat,122,57,0		warp	acwarp016	1,1,ac_library.gat,164,110
ac_library.gat,161,110,0	warp	acwarp017	1,1,ac_library.gat,119,57

// ------------------------------------------------------------------------------
//実習室（海岸）
ac_prac_01.gat,225,25,0		warp	acpracwp01		3,2,ac_cl_area.gat,53,181
//実習室（島）
ac_prac_02.gat,108,27,0		warp	acpracwp02		1,1,ac_cl_area.gat,53,181
//実習室（高原）
ac_prac_03.gat,29,343,0		warp	acpracwp03		1,1,ac_cl_area.gat,53,181
//実習室（炭鉱）
ac_prac_04.gat,261,255,0	warp	acpracwp04		1,1,ac_cl_area.gat,53,181
//実習室（砂漠）
ac_prac_05.gat,51,170,0		warp	acpracwp05		1,3,ac_cl_area.gat,53,181
//特別室（湖）
ac_spec_01.gat,283,28,0		warp	acpracwp05		1,3,ac_cl_area.gat,53,181
//特別室（廃墟）
ac_spec_02.gat,118,59,0		warp	acpracwp06		1,3,ac_cl_area.gat,53,181
ac_spec_02.gat,185,70,0		warp	acpracwp07		1,3,ac_spec_02.gat,181,141
ac_spec_02.gat,185,141,0	warp	acpracwp08		1,1,ac_spec_02.gat,180,70
ac_spec_02.gat,106,125,0	warp	acpracwp09		1,1,ac_spec_02.gat,73,174
ac_spec_02.gat,83,174,0		warp	acpracwp10		1,1,ac_spec_02.gat,110,125
ac_spec_02.gat,15,144,0		warp	acpracwp11		1,1,ac_spec_02.gat,77,68
ac_spec_02.gat,81,68,0		warp	acpracwp12		1,1,ac_spec_02.gat,19,144
//特別室（地下道）
ac_spec_03.gat,105,78		warp	acpracwp13		1,1,ac_cl_area.gat,53,181

// -----------------------------------------------------------------------------
// 確認メッセージ付きWARP

ac_cl_area.gat,71,74,0	script	#教室棟2F_warp1	45,1,1,{/* 52554 */
	if(!(AC_HINT_01 & 0x1) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟1F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟1F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x1;
	}
	warp "ac_cl_area.gat",36,185;
	end;
}

ac_cl_area.gat,71,14,0	script	#教室棟2F_warp2	45,1,1,{/* 52555 */
	if(!(AC_HINT_01 & 0x1) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟1F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟1F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x1;
	}
	warp "ac_cl_area.gat",36,125;
	end;
}

ac_cl_room.gat,152,18,0	script	#自習室_warp1	45,1,1,{/* 52556 */
	if(!(AC_HINT_01 & 0x2) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟1F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟1F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x2;
	}
	warp "ac_cl_area.gat",38,176;
	end;
}

ac_cl_area.gat,30,185,0	script	#教室棟1F_warp1	45,1,1,{/* 52557 */
	if(!(AC_HINT_01 & 0x4) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟2F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟2F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x4;
	}
	warp "ac_cl_area.gat",67,74;
	end;
}

ac_cl_area.gat,35,176,0	script	#教室棟1F_warp2	45,1,1,{/* 52558 */
	if(!(AC_HINT_01 & 0x8) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000自習室^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000自習室^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x8;
	}
	warp "ac_cl_room.gat",152,21;
	end;
}

ac_cl_area.gat,35,133,0	script	#教室棟1F_warp3	45,1,1,{/* 52559 */
	if(Job == Job_Summoner) {
		mes "[インフォメーション]";
		mes "‐ドラム族はこの先に";
		mes "　進むことができません‐";
		close;
	}
	if(!(AC_HINT_01 & 0x10)){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000受付・講習室^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000受付・講習室^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x10;
	}
	warp "ac_cl_room.gat",43,19;
	end;
}

ac_cl_area.gat,30,125,0	script	#教室棟1F_warp4	45,1,1,{/* 52560 */
	if(!(AC_HINT_01 & 0x20) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟2F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟2F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x20;
	}
	warp "ac_cl_area.gat",67,14;
	end;
}

ac_cl_area.gat,76,156,0	script	#教室棟1F_warp5	45,1,1,{/* 52561 */
	if(!(AC_HINT_01 & 0x40) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟ホール^000000です‐";
		mes "‐武器・防具などの販売や";
		mes "　アカデミー内のダンジョン";
		mes "　実習室があります‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟ホール^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x40;
	}
	warp "ac_cl_hall.gat",167,69;
	end;
}

ac_cl_hall.gat,167,72,0	script	#教室ホール_warp1	45,1,1,{/* 52562 */
	if(!(AC_HINT_01 & 0x80) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟1F^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟1F^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x80;
	}
	warp "ac_cl_area.gat",73,156;
	end;
}

ac_cl_hall.gat,167,19,0	script	#教室ホール_warp5	45,1,1,{/* 52563 */
	if(!(AC_HINT_01 & 0x100) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000エントランスホール^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000エントランスホール^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x100;
	}
	warp "ac_en_hall.gat",57,13;
	end;
}

ac_en_hall.gat,54,13,0	script	#入り口_warp1	45,1,1,{/* 52564 */
	if(!(AC_HINT_01 & 0x200) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000教室棟ホール^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000教室棟ホール^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x200;
	}
	warp "ac_cl_hall.gat",167,22;
	end;
}

ac_en_hall.gat,97,7,0	script	#入り口_warp2	45,1,1,{/* 52565 */
	switch(AC_SAVE_MAP){
	case 0: mes "‐プロンテラの"; break;
	case 1: mes "‐イズルードの"; break;
	case 2: mes "‐モロクの"; break;
	case 3: mes "‐アルベルタの"; break;
	case 4: mes "‐ゲフェンの"; break;
	case 5: mes "‐フェイヨンの"; break;
	}
	mes "街に戻りますか？‐";
	next;
	if(select("戻る","戻らない")==2){
		mes "‐戻るのをやめた‐";
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "(街に戻ろう)";
	close2;
	callfunc "AC_WarpTown",AC_SAVE_MAP;
	end;
}

ac_en_hall.gat,143,13,0	script	#入り口_warp3	45,1,1,{/* 52566 */
	if(!(AC_HINT_01 & 0x400) && Job!=Job_Summoner){
		mes "[インフォメーション]";
		mes "‐この先は^FF0000図書室^000000です‐";
		mes "‐このまま進みますか？‐";
		next;
		if(select("はい","いいえ")==2){
			mes "‐立ち止まった‐";
			close;
		}
		mes "[インフォメーション]";
		mes "‐^FF0000図書室^000000へ移動します‐";
		close2;
		set AC_HINT_01, AC_HINT_01 | 0x400;
	}
	warp "ac_library.gat",32,58;
	end;
}
