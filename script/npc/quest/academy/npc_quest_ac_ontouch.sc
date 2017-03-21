//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- –`Œ¯ŽÒƒAƒJƒfƒ~[
//                                                  by Pneuma
// Ž©“®‰ï˜bŠÖŒW ----------------------------------------------

//------------------------------------------------------------------------------
// ƒ~ƒjƒ}ƒbƒv•\Ž¦(–{ŽI‚Å‚ÍNPC–¼ uƒRƒ“ƒpƒXv)
//
// ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚P‚Åƒ^ƒbƒ`‚·‚é‚à‚Ì‚ÍƒAƒJƒfƒ~[ŠÖŒWŽÒ‚ÌOnTouchŽQÆ
// NPC‚ªd‚È‚é‚ÆOnTouch‚ª”­¶‚µ‚È‚¢ˆ×A‘S‚Ä‚±‚±‚ÉI
//
// *ID‚Íviewpoint‚ÅŽg—p‚·‚éID
// ÂF 0x0000FF ID:10 (‹C‚É‚È‚é‚ ‚ÌŽq)
// ÔF 0xFF0000 ID:11 (ŠïÕ‚Ì” )
// žòF 0xFF9900 ID:12 (‚¨¢˜b‚É‚È‚Á‚½‚ ‚Ìl‚Ö)
// —ÎF 0x00FF00 ID:13 (ŽÀŒ±‚Ì‚¨Žè“`‚¢/ƒ_ƒ“ƒWƒ‡ƒ“‹~o)
// …F 0x00FFFF ID:14 (–`Œ¯ŽÒ‚É‚È‚è‚½‚¢)
// ‰©F 0xFFFF00 ID:20 (‘SŽŽŒ±)
//
//------------------------------------------------------------------------------

pay_fild03.gat,388,63,0	script	AC_TSTVP1_02	139,1,1,{ //ŠX‚©‚ç‚Ìƒ[ƒvæ‚Åƒ^ƒbƒ`
	if(AC_RANK==0 && AC_RANKTEST==2){ //‘æ‚P‰Û’ö
		viewpoint 1,209,143,20,0xFFFF00;
	}
}
prt_fild08.gat,170,375,0	script	AC_TSTVP2_02	139,1,1,{ //ƒvƒ“ì‚Åƒ^ƒbƒ`
	if(AC_RANK==1 && AC_RANKTEST==2){ //‘æ‚Q‰Û’ö
		viewpoint 1,233,16,20,0xFFFF00;
	}
	if( (AC_QUEST_LV_4==1 && AC_QUEST_ST_4==2)|| //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚Q
		(AC_QUEST_LV_4==5 && AC_QUEST_ST_4==2)){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚U
		viewpoint 1,233,16,14,0x00FFFF;
	}
}
moc_fild01.gat,238,378,0	script	AC_TSTVP2_03	139,1,1,{ //ŽqƒfƒUƒ}ƒbƒv‚Åƒ^ƒbƒ`
	if(AC_RANK==1 && AC_RANKTEST==2){ //‘æ‚Q‰Û’ö
		viewpoint 1,379,162,20,0xFFFF00;
	}
	if(AC_QUEST_LV_4==1 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚Q
		viewpoint 1,379,162,14,0x00FFFF;
	}
	if(AC_QUEST_LV_4==5 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚U
		viewpoint 1,322,16,14,0x00FFFF;
	}
}
pay_fild04.gat,20,165,0		script	AC_TSTVP2_04	139,1,1,{ //ƒ|ƒŠƒ““‡‚Åƒ^ƒbƒ`
	if(AC_RANK==1 && AC_RANKTEST==2){ //‘æ‚Q‰Û’ö
		viewpoint 1,350,330,20,0xFFFF00;
	}
	if(AC_QUEST_LV_4==1 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚Q
		viewpoint 1,267,193,14,0x00FFFF; //ŽB‰eƒ|ƒCƒ“ƒg‚Q
	}
}
pay_fild01.gat,333,356,0				script	AC_TSTVP3_02	139,1,1,{ //ƒtƒFƒC“ì‚Åƒ^ƒbƒ`
	if(AC_QUEST_LV_3==6 && AC_QUEST_ST_3==3){//	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚S
		viewpoint 1,353,14,13,0x00FF00;	// ƒEƒ‹ƒtƒ}ƒbƒv“ü‚èŒû(‰E‰º)
	}
	if(AC_RANK==2 && AC_RANKTEST==2){ //‘æ‚R‰Û’ö
		viewpoint 1,353,14,20,0xFFFF00;
	}
}
pay_fild02.gat,160,381,0				script	AC_TSTVP2_03	139,1,1,{ //ƒEƒ‹ƒtƒ}ƒbƒv‰EãWP‚Åƒ^ƒbƒ`
	if(AC_QUEST_LV_3==6 && AC_QUEST_ST_3==3){//	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚S
		viewpoint 1,52,125,13,0x00FF00;	// ‚ ‚â‚µ‚¢ƒLƒmƒR
	}
	if(AC_RANK==2 && AC_RANKTEST==2){ //‘æ‚R‰Û’ö
		viewpoint 1,105,242,20,0xFFFF00;
	}
}
pay_fild02.gat,83,382,0					script	AC_TSTVP2_04	139,1,1,{ //ƒEƒ‹ƒtƒ}ƒbƒvã’†‰›WP‚Åƒ^ƒbƒ`(‚¢‚ç‚È‚¢H)
	if(AC_RANK==2 && AC_RANKTEST==2){ //‘æ‚R‰Û’ö
		viewpoint 1,105,242,20,0xFFFF00;
	}
}
mjolnir_09.gat,106,34,0					script	AC_TSTVP4_03	139,1,1,{ //ƒvƒ©ªƒ[ƒvæ‚Åƒ^ƒbƒ`
	if(AC_RANK==3 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚S‰Û’ö
		viewpoint 1,30,249,20,0xFFFF00;
	}
	if(AC_RANK==4 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚T‰Û’ö
		viewpoint 1,100,365,20,0xFFFF00;
	}
}
gef_fild00.gat,376,140,0				script	AC_TSTVP4_05	139,1,1,{ //ƒQƒtƒF“Œ
	if(AC_RANK==3 && AC_RANKTEST>=7 && AC_RANKTEST!=99){ //‘æ‚S‰Û’ö
		viewpoint 1,40,199,20,0xFFFF00;
	}
}
prt_fild00.gat,380,249,0				script	AC_TSTVP4_05	139,1,1,{ //ƒvƒ©ª©ƒ[ƒvæ‚Åƒ^ƒbƒ`
	if(AC_RANK==3 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚S‰Û’ö
		viewpoint 1,152,250,20,0xFFFF00;
	}
}
prt_fild05.gat,367,205,0				script	AC_TSTVP5_02	139,1,1,{ //ƒvƒ¼
	if( (AC_QUEST_LV_3==1 && AC_QUEST_ST_3==2) ||	//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚P
		(AC_QUEST_LV_3==5 && AC_QUEST_ST_3==2) ||	//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚R
		(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==3) 		//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚T
	){
		viewpoint 1,270,212,13,0x00FF00;	//’n‰º…˜HŠÇ—•º
	}
	if( (AC_QUEST_LV_4==3 && AC_QUEST_ST_4==2) || //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚S
		(AC_QUEST_LV_4==6 && AC_QUEST_ST_4==2) ){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚V
		viewpoint 1,13,63,14,0x00FFFF;
	}
	if(AC_QUEST_LV_4==8 && AC_QUEST_ST_4==2){	//–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚X
		viewpoint 1,270,212,14,0x00FFFF; //’n‰º…˜HŠÇ—•º
	}
	if(AC_RANK==3 && AC_RANKTEST==2){ //‘æ‚S‰Û’ö
		viewpoint 1,105,381,20,0xFFFF00;
		mes "[" + strcharinfo(0) + "]";
		mes "ƒKƒ‹ƒh‚Í^0000FFƒvƒƒ“ƒeƒ‰^000000‚©‚ç^0000FFƒQƒtƒFƒ“^000000‚Ö";
		mes "•à‚­‚±‚Æ‚Á‚ÄŒ¾‚Á‚Ä‚½‚Á‚¯B";
		mes "“r’†‚Å^FF0000ƒhƒ‰ƒbƒvæ¶^000000‚É‚¨•Ù“–‚ð";
		mes "“n‚³‚È‚­‚¿‚áB";
		mes "‚Ü‚¸‚Í^FF0000–k¼‚Ì•ûŠp‚Ö^000000•à‚¢‚Ä‚¢‚±‚¤B";
		close2;
		set AC_RANKTEST,3; //ƒtƒ‰ƒOXV
		end;
	}
	if(AC_RANK==4 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚T‰Û’ö
		viewpoint 1,105,381,20,0xFFFF00;
	}
}
prt_fild05.gat,357,205,0				script	AC_TSTVP5_02	139,7,7,{ //ƒvƒ¼iƒ[ƒv‘Oj
	if(AC_RANK==6 && AC_RANKTEST==15){
		mes "[" + strcharinfo(0) + "]";
		mes "ƒvƒƒ“ƒeƒ‰‚ªŒ©‚¦‚éB";
		mes "‚ ‚Æ­‚µ‚¾I";
		close2;
		set AC_RANKTEST,16;
		end;
	}
}
pay_fild08.gat,20,74,0					script	AC_TSTVP6_02	139,1,1,{ //ƒtƒFƒC“Œ
	if(AC_RANK==5 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚U‰Û’ö
		viewpoint 1,167,332,20,0xFFFF00;
	}
}
gef_fild00.gat,46,199,0					script	AC_TSTVP6_04	139,1,1,{ //ƒQƒtƒFƒ““Œ
	if(AC_RANK==5 && AC_RANKTEST>=3 && AC_RANKTEST!=99){ //‘æ‚U‰Û’ö
		viewpoint 1,267,382,20,0xFFFF00;
	}
}
mjolnir_06.gat,265,32,0					script	AC_TSTVP6_05	139,1,1,{ //ƒ~ƒ‡ƒ‹ƒj[ƒ‹ŽR–¬06
	if(AC_RANK==5 && AC_RANKTEST>=3 && AC_RANKTEST!=99){ //‘æ‚U‰Û’ö
		viewpoint 1,226,183,20,0xFFFF00;
	}
}
moc_fild12.gat,159,378,0				script	AC_TSTVP6_07	139,1,1,{ //ƒ‚ƒƒN“ì
	if(AC_RANK==5 && AC_RANKTEST>=4 && AC_RANKTEST!=99){ //‘æ‚U‰Û’ö
		viewpoint 1,118,30,20,0xFFFF00;
	}
	if( (AC_QUEST_LV_4==2 && AC_QUEST_ST_4==2) || //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚R
		(AC_QUEST_LV_4==4 && AC_QUEST_ST_4==2) ){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚T
		viewpoint 1,118,30,14,0x00FFFF;
	}
}
moc_fild18.gat,158,379,0				script	AC_TSTVP6_07	139,1,1,{ //ƒ\ƒOƒ‰ƒg»”™18
	if(AC_RANK==5 && AC_RANKTEST>=4 && AC_RANKTEST!=99){ //‘æ‚U‰Û’ö
		viewpoint 1,211,95,20,0xFFFF00;
	}
	if(AC_QUEST_LV_4==2 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚R
		viewpoint 1,232,217,14,0x00FFFF; //ŽB‰eƒ|ƒCƒ“ƒg‚R
	}
	if(AC_QUEST_LV_4==4 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚T
		viewpoint 1,382,305,14,0x00FFFF;
	}
}
pay_gld.gat,370,149,0					script	AC_TSTVP7_02	139,1,1,{ //ƒ`ƒ…ƒ“ƒŠƒ€ŒÎ
	if(AC_RANK==6 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //‘æ‚V‰Û’ö
		viewpoint 1,273,307,20,0xFFFF00;
	}
}
moc_fild01.gat,315,25,0					script	AC_TSTVP7_03	139,1,1,{ //ƒ\ƒOƒ‰ƒg»”™01
	if(AC_RANK==6 && AC_RANKTEST>=7 && AC_RANKTEST!=99){ //‘æ‚V‰Û’ö
		viewpoint 1,190,38,20,0xFFFF00;
	}
}
prt_fild09.gat,380,237,0				script	AC_TSTVP7_04	139,1,1,{
	if(AC_RANK==6 && AC_RANKTEST>=9 && AC_RANKTEST!=99){ //‘æ‚V‰Û’ö
		viewpoint 1,304,193,20,0xFFFF00;
	}
}
prt_fild07.gat,206,15,0					script	AC_TSTVP7_05	139,1,1,{
	if(AC_RANK==6 && AC_RANKTEST>=14 && AC_RANKTEST!=99){ //‘æ‚V‰Û’ö
		viewpoint 1,248,376,20,0xFFFF00;
	}
}
prt_fild05.gat,257,18,0					script	AC_TSTVP7_06	139,1,1,{
	if(AC_RANK==6 && AC_RANKTEST>=15 && AC_RANKTEST!=99){ //‘æ‚V‰Û’ö
		viewpoint 1,367,205,20,0xFFFF00;
	}
}
moc_ruins.gat,156,42,0		script	AC_QUEVP00_04	139,1,1,{
	if( (AC_QUEST_ST_0==2 && AC_QUEST_LV_0==2)||	//‹C‚É‚È‚é‚ ‚ÌŽq‚R
		(AC_QUEST_ST_0==3 && AC_QUEST_LV_0==4)){	//‹C‚É‚È‚é‚ ‚ÌŽq‚T
		viewpoint 1,114,100,10,0x0000FF; //ƒsƒ‰‘OƒXƒUƒ“ƒk
	}
	if(AC_QUEST_LV_3==2 && AC_QUEST_ST_3==3){ //ŽÀŒ±‚Ì‚¨Žè“`‚¢‚Q
		viewpoint 1,54,161,13,0x00FF00; //ƒsƒ‰“ü‚èŒû
	}
}
comodo.gat,172,165,0		script	AC_QUEVP00_05	139,7,7,{ //ƒRƒ‚ƒh ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_0==2 && AC_QUEST_LV_0==5){		//‹C‚É‚È‚é‚ ‚ÌŽq‚U
		viewpoint 1,165,163,10,0x0000FF; //ƒmƒGƒŠƒA
	}
	if(AC_QUEST_LV_1==7 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚W
		viewpoint 1,113,219,11,0xFF0000; //ƒ^[ƒjƒƒ
	}
}
prt_fild06.gat,27,193,0		script	AC_QUEVP00_06	139,1,1,{
	if(AC_QUEST_ST_0==2 && AC_QUEST_LV_0==6){		//‹C‚É‚È‚é‚ ‚ÌŽq‚U
		viewpoint 1,277,320,10,0x0000FF; //ƒJƒsƒg[ƒŠƒiC“¹‰@‚Ö
	}
	if(AC_QUEST_LV_4==0 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚P
		viewpoint 1,277,320,14,0x00FFFF;
	}
}
prt_fild02.gat,305,22,0		script	AC_QUEVP00_07	139,1,1,{
	if(AC_QUEST_ST_0==2 && AC_QUEST_LV_0==6){		//‹C‚É‚È‚é‚ ‚ÌŽq‚U
		viewpoint 1,380,347,10,0x0000FF; //ƒJƒsƒg[ƒŠƒiC“¹‰@‚Ö
	}
	if(AC_QUEST_LV_4==0 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚P
		viewpoint 1,305,157,14,0x00FFFF; //ŽB‰eƒ|ƒCƒ“ƒg‚P
	}
}
prt_fild03.gat,23,249,0		script	AC_QUEVP00_08	139,1,1,{
	if(AC_QUEST_ST_0==2 && AC_QUEST_LV_0==6){		//‹C‚É‚È‚é‚ ‚ÌŽq‚U
		viewpoint 1,371,256,10,0x0000FF; //ƒJƒsƒg[ƒŠƒiC“¹‰@‚Ö
	}
}
rachel.gat,129,144,0		script	AC_QUEVP00_10	139,7,7,{	//ƒ‰ƒwƒ‹ ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_0==2 && AC_QUEST_LV_0==8){		//‹C‚É‚È‚é‚ ‚ÌŽq‚X
		viewpoint 1,148,190,10,0x0000FF;
	}
}
veins.gat,197,133,0			script	AC_QUEVP00_11	139,7,7,{	//ƒxƒCƒ“ƒX ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_0==3 && AC_QUEST_LV_0==8){		//‹C‚É‚È‚é‚ ‚ÌŽq‚X
		viewpoint 1,148,329,10,0x0000FF;
	}
}
amatsu.gat,121,155,0	script	#AC_QUEVP01_03	139,7,7,{	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_LV_1==2 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚R
		viewpoint 1,212,141,11,0xFF0000; //ƒA[ƒ`ƒ{ƒ‹ƒh
	}
}
gonryun.gat,174,134,0	script	#AC_QUEVP01_04	139,7,7,{	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_LV_1==3 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚S
		viewpoint 1,140,65,11,0xFF0000; //ƒQƒCƒ\ƒ“
	}
}
louyang.gat,215,118,0	script	#AC_QUEVP01_05	139,7,7,{	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_LV_1==4 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚T
		viewpoint 1,229,109,11,0xFF0000; //ƒhƒiƒeƒ
	}
}
ayothaya.gat,213,193,0	script	#AC_QUEVP01_06	139,7,7,{	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_LV_1==5 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚U
		viewpoint 1,212,176,11,0xFF0000; //ƒfƒ…[ƒC
	}
}
umbala.gat,93,154,0		script	#AC_QUEVP01_07	139,7,7,{	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_LV_1==6 && AC_QUEST_ST_1==2){ //ŠïÕ‚Ì” ‚V
		viewpoint 1,96,164,11,0xFF0000; //ƒfƒjƒX
	}
}
prt_fild04.gat,374,73,0			script	AC_QUEVP04_13	139,1,1,{
	if( (AC_QUEST_LV_4==3 && AC_QUEST_ST_4==2) || //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚S
		(AC_QUEST_LV_4==6 && AC_QUEST_ST_4==2) ){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚V
		viewpoint 1,17,114,14,0x00FFFF;
	}
}
gef_fild01.gat,375,111,0		script	AC_QUEVP04_14	139,1,1,{
	if(AC_QUEST_LV_4==3 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚S
		viewpoint 1,208,242,14,0x00FFFF;//ŽB‰eƒ|ƒCƒ“ƒg‚S
	}
	if(AC_QUEST_LV_4==6 && AC_QUEST_ST_4==2){ //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚V
		viewpoint 1,16,102,14,0x00FFFF;
	}
}
moc_fild17.gat,33,300,0		script	AC_QUEVP04_15	139,1,1,{
	if(AC_QUEST_LV_4==4 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚T
		viewpoint 1,146,145,14,0x00FFFF;//ŽB‰eƒ|ƒCƒ“ƒg‚T
	}
}
moc_fild02.gat,77,338,0		script	AC_QUEVP04_19	139,1,1,{
	if(AC_QUEST_LV_4==5 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚U
		viewpoint 1,332,19,14,0x00FFFF;
	}
}
gef_fild09.gat,368,92,0		script	AC_QUEVP04_20	139,1,1,{
	if(AC_QUEST_LV_4==6 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚V
		viewpoint 1,225,25,14,0x00FFFF;
	}
}
aldebaran.gat,134,114,0		script	AC_QUEVP04_21	139,7,7,{ 	//ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if( (AC_QUEST_LV_2==0 && AC_QUEST_ST_2==1) || // ‚¨¢˜b‚É‚È‚Á‚½‚ ‚Ìl‚É‚P
		(AC_QUEST_LV_2==1 && AC_QUEST_ST_2==1) || // ‚¨˜l‚Ñ‚Ì•i‚ð“Í‚¯‚½‚¢‚P
		(AC_QUEST_LV_2==7 && AC_QUEST_ST_2==2) || // ‚¨‰ÙŽq‚¨“Í‚¯
		(AC_QUEST_LV_2==8 && AC_QUEST_ST_2==1)) { // ‚¨˜l‚Ñ‚Ì•i‚ð“Í‚¯‚½‚¢‚Q
		if(AC_QUEST_ST_2==1) cutin "q_run_npc_05.bmp", 4;
		viewpoint 1,231,107,12,0xFF9900; //ƒ~ƒUƒŠ[‚Ì‰Æ
	}
	if(AC_QUEST_LV_4==7 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚W
		viewpoint 1,168,168,14,0x00FFFF; //ƒŠƒ“ƒNƒTƒ“ƒ^
	}
}
aldebaran.gat,231,107,0				script	AC_QUEVP02_02	139,1,1,{ //ƒ~ƒUƒŠ[‚ÌŒš•¨‚©‚ço‚½
	if(AC_QUEST_LV_2==0 && AC_QUEST_ST_2==2) {
		viewpoint 1,168,166,12,0xFF9900; //ƒŠƒ“ƒNƒTƒ“ƒ^
	}
}
xmas_fild01.gat,100,100,0	script	AC_QUEVP04_22	139,1,1,{
	if(AC_QUEST_LV_2==0 && AC_QUEST_ST_2==2) { // ‚¨¢˜b‚É‚È‚Á‚½‚ ‚Ìl‚É‚P
		viewpoint 1,84,248,12,0xFF9900;
	}
	if(AC_QUEST_LV_4==7 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚W
		viewpoint 1,84,248,14,0x00FFFF;
	}
}
xmas.gat,149,44,0			script	AC_QUEVP04_23	139,1,1,{
	if(AC_QUEST_LV_2==0 && AC_QUEST_ST_2==2) { //‚¨¢˜b‚É‚È‚Á‚½‚ ‚Ìl‚É‚P
		viewpoint 1,189,276,12,0xFF9900;
	}
	if(AC_QUEST_LV_4==7 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚W
		viewpoint 1,143,314,14,0x00FFFF;
	}
}
xmas_dun01.gat,205,16,0		script	AC_QUEVP04_24	139,1,1,{
	if(AC_QUEST_LV_4==7 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚W
		viewpoint 1,129,130,14,0x00FFFF;
	}
}
prt_sewb1.gat,131,247,0		script	AC_QUEVP04_25	139,1,1,{	//ƒvƒ’n‰º…˜H‚P
	if(AC_QUEST_LV_3==1 && AC_QUEST_ST_3==2){ //	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚P
		viewpoint 1,301,206,13,0x00FF00; //ƒ`ƒXƒ[
	} else
	if( (AC_QUEST_LV_3==5 && AC_QUEST_ST_3==2) ||	//	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚R
		(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==3) ){	//	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚T
		viewpoint 1,188,247,13,0x00FF00; //2‘w“ü‚èŒû
	}
	if(AC_QUEST_LV_4==8 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚X
		viewpoint 1,188,247,14,0x00FFFF;
	}
}
prt_sewb2.gat,19,19,0		script	AC_QUEVP04_26	139,1,1,{	//ƒvƒ’n‰º…˜H‚Q
	if(AC_QUEST_LV_3==5 && AC_QUEST_ST_3==2){ //	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚R
		viewpoint 1,159,182,13,0x00FF00; //ƒƒ‹ƒV[‚¿‚á‚ñ
	} else
	if(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==3){ //	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚T
		viewpoint 1,180,24,13,0x00FF00; //3‘w“ü‚èŒû
	}
	if(AC_QUEST_LV_4==8 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚X
		viewpoint 1,180,24,14,0x00FFFF;
	}
}
prt_sewb3.gat,180,169,0		script	AC_QUEVP04_27	139,1,1,{	//ƒvƒ’n‰º…˜H‚R
	if(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==3){ //	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚T
		viewpoint 1,184,17,13,0x00FF00; //ƒ~ƒ“ƒ~ƒ“‘
	}
	if(AC_QUEST_LV_4==8 && AC_QUEST_ST_4==2) { //–`Œ¯ŽÒ‚É‚È‚è‚½‚¢‚X
		viewpoint 1,20,185,14,0x00FFFF;
	}
}
yuno.gat,142,176,0					script	AC_QUEVP02_05	139,7,7,{ //ƒ}ƒbƒYƒC‚Ì‰Æ
	if( (AC_QUEST_LV_2==1 && AC_QUEST_ST_2==2) || //‚¨˜l‚Ñ‚Ì•i‚ð“Í‚¯‚½‚¢‚P
		(AC_QUEST_LV_2>=2 && AC_QUEST_LV_2<=7 && AC_QUEST_ST_2==1) //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚P`‚TE‚¨‰ÙŽq‚¨“Í‚¯
	){
		viewpoint 1,95,182,12,0xFF9900;
	}
}
lighthalzen.gat,219,161,0			script	AC_QUEVP02_06	139,7,7,{ //ƒŠƒq ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_2==2 && AC_QUEST_LV_2==2){ //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚P
		viewpoint 1,51,161,12,0xFF9900;  //–Ø
	}
}
einbroch.gat,223,182,0			script	AC_QUEVP02_07	139,7,7,{ //ƒAƒCƒ“ƒuƒƒbƒN ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_2==2 && AC_QUEST_LV_2==3){ //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚Q
		viewpoint 1,111,261,12,0xFF9900; //ƒhƒu
	}
}
einbech.gat,171,137,0			script	AC_QUEVP02_08	139,7,7,{ //ƒAƒCƒ“ƒxƒt ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_2==2 && AC_QUEST_LV_2==4){ //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚R
		viewpoint 1,130,247,12,0xFF9900; //ƒhƒ‹ƒhƒC
	}
}
izlu2dun.gat,107,50,0			script	AC_QUEVP02_09	139,1,1,{ //ƒoƒCƒ‰ƒ““‡
	if(AC_QUEST_ST_2==2 && AC_QUEST_LV_2==5){ //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚S
		viewpoint 1,136,50,12,0xFF9900; //ƒ“ƒ‰ƒCƒo
	}
	if( (AC_QUEST_LV_3==3 && AC_QUEST_ST_3==2) || //ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚Q
		(AC_QUEST_LV_3==7 && AC_QUEST_ST_3==2) ){ //ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚S
		viewpoint 1,108,83,13,0x00FF00;	// ŠC’ê“´ŒA“ü‚èŒû
	}
}
alb2trea.gat,43,53,0	script	AC_QUEVP02_10	139,1,1,{ //’¾–v‘D
	if(AC_QUEST_ST_2==2 && AC_QUEST_LV_2==6){ //‚¨‰ÙŽq‚ÌÞ—¿W‚ß‚T
		viewpoint 1,105,95,12,0xFF9900; //ƒAƒCƒŠƒ“
	}
}
hugel.gat,93,155,0	script	AC_QUEVP02_11	139,8,9,{ //ƒtƒBƒQƒ‹ ƒAƒJƒfƒ~[ŠÖŒWŽÒƒ^ƒCƒv‚Q
	if(AC_QUEST_ST_2==3 && AC_QUEST_LV_2==8){ //‚¨˜l‚Ñ‚Ì•i‚ð“Í‚¯‚½‚¢‚Q
		viewpoint 1,72,90,12,0xFF9900; //ƒƒbƒNƒX
	} else
	if( (AC_QUEST_LV_3==0 && AC_QUEST_ST_3==1) ||	//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚P
		(AC_QUEST_LV_3==2 && AC_QUEST_ST_3==1) ||	//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚Q
		(AC_QUEST_LV_3==4 && AC_QUEST_ST_3==1) ||	//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚R
		(AC_QUEST_LV_3==6 && AC_QUEST_ST_3==1) ||	//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚S
		(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==1)		//ŽÀŒ±‚Ì‚¨Žè“`‚¢‚T
	){
		viewpoint 1,104,79,13,0x00FF00;
	} else
	if( (AC_QUEST_LV_3==1 && AC_QUEST_ST_3==1) ||	//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚P
		(AC_QUEST_LV_3==3 && AC_QUEST_ST_3==1) ||	//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚Q
		(AC_QUEST_LV_3==5 && AC_QUEST_ST_3==1) ||	//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚R
		(AC_QUEST_LV_3==7 && AC_QUEST_ST_3==1)		//ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚S
	){
		viewpoint 1,73,152,13,0x00FF00;
	}
}
gef_fild07.gat,336,187,0	script	AC_QUEVP03_01	139,1,1,{ //ƒQƒtƒFƒ“¼
	if(AC_QUEST_LV_3==0 && AC_QUEST_ST_3==3){ //	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚P
		viewpoint 1,185,249,13,0x00FF00;
	}
}
moc_pryd01.gat,192,9,0	script	AC_QUEVP03_03	139,1,1,{ //ƒsƒ‰ƒ~ƒbƒh’nã1F
	if(AC_QUEST_LV_3==2 && AC_QUEST_ST_3==3){ //ŽÀŒ±‚Ì‚¨Žè“`‚¢‚Q
		viewpoint 1,193,193,13,0x00FF00; //ƒ‰ƒCƒ‰ƒC‘
	}
}
iz_dun00.gat,168,168,0	script	AC_QUEVP03_05	139,1,1,{ //ŠC’ê“´ŒA1‘w
	if(AC_QUEST_LV_3==3 && AC_QUEST_ST_3==2){//	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚Q
		viewpoint 1,351,45,13,0x00FF00;	// ƒcƒC[ƒtƒ‰
	} else
	if(AC_QUEST_LV_3==7 && AC_QUEST_ST_3==2){//	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚S
		viewpoint 1,352,341,13,0x00FF00;	//2‘w“ü‚èŒû(‰Eã)
	}
}
iz_dun01.gat,253,252,0	script	AC_QUEVP03_06	139,1,1,{ //ŠC’ê“´ŒA2‘w
	if(AC_QUEST_LV_3==7 && AC_QUEST_ST_3==2){//	ƒ_ƒ“ƒWƒ‡ƒ“‹~o‚S
		viewpoint 1,129,79,13,0x00FF00;	//ƒU[ƒpƒt
	}
}
pay_arche.gat,81,22,0	script	AC_QUEVP03_07	139,1,1,{ //‹|Žè‘º“ü‚èŒû
	if(AC_QUEST_LV_3==4 && AC_QUEST_ST_3==3){//	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚R
		viewpoint 1,36,131,13,0x00FF00;	// ƒtƒFƒCƒˆƒ“ƒ_ƒ“ƒWƒ‡ƒ“
	}
}
pay_dun00.gat,21,183,0	script	AC_QUEVP03_08	139,1,1,{ //ƒtƒFƒCƒˆƒ“ƒ_ƒ“ƒWƒ‡ƒ“
	if(AC_QUEST_LV_3==4 && AC_QUEST_ST_3==3){//	ŽÀŒ±‚Ì‚¨Žè“`‚¢‚R
		viewpoint 1,154,172,13,0x00FF00;	// •‚¢•Ï‚ÈƒLƒmƒR
	}
}
