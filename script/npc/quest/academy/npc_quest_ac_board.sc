//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  案内板
//                                                  by Pneuma
//------------------------------------------------------------

ac_en_hall.gat,110,10,6	script	案内板	837,{
	cutin "ad_ac_guide12.bmp",2;
	mes "[エントランス]";
	mes "この先、図書室";
	close2;
	cutin "ad_ac_guide12.bmp",255;
	end;
}

ac_library.gat,30,65,6	script	案内板	837,{
	cutin "ad_ac_guide16.bmp",2;
	mes "[図書室]";
	mes "ここは図書室となります。";
	mes "図書室には多くの書物があり、";
	mes "いろいろなことを";
	mes "調べることが出来ます。";
	close2;
	cutin "ad_ac_guide16.bmp",255;
	end;
}

ac_library.gat,108,63,6	script	案内板	837,{
	cutin "ad_ac_guide14.bmp",2;
	mes "[図書室]";
	mes "◆操作系関連の部屋";
	close2;
	cutin "ad_ac_guide14.bmp",255;
	end;
}

ac_library.gat,109,52,6	script	案内板	837,{
	cutin "ad_ac_guide13.bmp",2;
	mes "[図書室]";
	mes "◆知識関連、戦闘関連の部屋";
	close2;
	cutin "ad_ac_guide13.bmp",255;
	end;
}

ac_library.gat,120,61,6	script	案内板	837,{
	cutin "ad_ac_guide15.bmp",2;
	mes "[図書室]";
	mes "◆コミュニティ関連、生活関連の部屋";
	close2;
	cutin "ad_ac_guide15.bmp",255;
	end;
}

ac_en_hall.gat,86,10,6	script	案内板	837,{
	cutin "ad_ac_guide11.bmp",2;
	mes "[エントランス]";
	mes "この先、教室棟";
	mes "受付、講習室、自習室、";
	mes "研究室、試験室、資料室";
	mes "実習室、特別室";
	close2;
	cutin "ad_ac_guide11.bmp",255;
	end;
}

ac_cl_hall.gat,172,71,6	script	案内板	837,{
	cutin "ad_ac_guide07.bmp",2;
	mes "[教室棟ホール]";
	mes "この先、教室棟1F";
	mes "受付、講習室、自習室、";
	mes "研究室、試験室、資料室";
	close2;
	cutin "ad_ac_guide07.bmp",255;
	end;
}

ac_cl_hall.gat,163,63,6	script	案内板	837,{
	cutin "ad_ac_guide08.bmp",2;
	mes "[教室棟ホール]";
	mes "◆実習室・特別室　入口";
	mes " ";
	mes "Lv1～55の冒険者の方専用";
	mes "ノービス、一次職、";
	mes "特殊一次職の冒険者の";
	mes "実習室・特別室";
	close2;
	cutin "ad_ac_guide08.bmp",255;
	end;
}
ac_cl_hall.gat,160,45,6	script	案内板	837,{
	cutin "ad_ac_guide10.bmp",2;
	mes "[教室棟ホール]";
	mes "◆実習室・特別室　入口";
	mes " ";
	mes "Lv1～55の冒険者の方専用";
	mes "ノービス、一次職、";
	mes "特殊一次職の冒険者の";
	mes "実習室・特別室";
	close2;
	cutin "ad_ac_guide10.bmp",255;
	end;
}
ac_cl_hall.gat,174,25,6	script	案内板	837,{
	cutin "ad_ac_guide09.bmp",2;
	mes "[教室棟ホール]";
	mes "◆実習室・特別室　入口";
	mes " ";
	mes "Lv1～55の冒険者の方専用";
	mes "ノービス、一次職、";
	mes "特殊一次職の冒険者の";
	mes "実習室・特別室";
	close2;
	cutin "ad_ac_guide09.bmp",255;
	end;
}

ac_cl_room.gat,46,29,6	script	受付、講習室	837,{
	cutin "ad_ac_guide17.bmp",2;
	mes "[教室棟1F]";
	mes "◆受付";
	mes "◆講習室";
	close2;
	cutin "ad_ac_guide17.bmp",255;
	end;
}

ac_cl_room.gat,156,25,4	script	自習室	837,{
	cutin "ad_ac_guide18.bmp",2;
	mes "[教室棟1F]";
	mes "◆自習室";
	close2;
	cutin "ad_ac_guide18.bmp",255;
	end;
}

// 案内板
ac_cl_area.gat,39,172,4	script	案内板	837,{
	cutin "ad_ac_guide05.bmp",2;
	mes "[教室棟1F]";
	mes "◆自習室";
	close2;
	cutin "ad_ac_guide05.bmp",255;
	end;
}
ac_cl_area.gat,39,136,4	script	案内板	837,1,4,{
	cutin "ad_ac_guide06.bmp",2;
	mes "[教室棟1F]";
	mes "◆講習室";
	close2;
	cutin "ad_ac_guide06.bmp",255;
	end;
OnTouch:
	if(!(AC_HINT_02 & 0x1)){
		cutin "start_030_jp.bmp", 4;
		set AC_HINT_02, AC_HINT_02 | 0x1;
	}
}

ac_cl_area.gat,65,12,4	script	案内板	837,{
	cutin "ad_ac_guide04.bmp",2;
	mes "[教室棟2F]";
	mes "◆資料室";
	mes "◆研究室";
	mes "◆試験室";
	mes "◆講義室";
	close2;
	cutin "ad_ac_guide04.bmp",255;
	end;
}

ac_cl_area.gat,76,60,4	script	研究室	837,{
	cutin "ad_ac_guide02.bmp",2;
	mes "[研究室]";
	mes "ここは研究室になります。";
	mes "研究室では、";
	mes "現在研究員を募集中です。";
	close2;
	cutin "ad_ac_guide02.bmp",255;
	end;
}

ac_cl_area.gat,49,53,4	script	講義室	837,{
	cutin "ad_ac_guide19.bmp",2;
	mes "[講義室]";
	mes "ここは講義室になります。";
	mes "さまざまな講義が行われる場所です。";
	close2;
	cutin "ad_ac_guide19.bmp",255;
	end;
}

ac_cl_area.gat,26,43,4	script	資料室	837,{
	cutin "ad_ac_guide01",2;
	mes "[資料室]";
	mes "ここは資料室になります。";
	mes "沢山の蔵書を管理しています。";
	close2;
	cutin "ad_ac_guide01",255;
	end;
}
ac_cl_area.gat,76,39,4	script	試験室	837,{
	cutin "ad_ac_guide03.bmp",2;
	mes "[試験室]";
	mes "ここは試験室になります。";
	mes "さまざまな試験が行われる場所です。";
	close2;
	cutin "ad_ac_guide03.bmp",255;
	end;
}
