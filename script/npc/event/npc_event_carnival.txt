//==============================================================================
//Ragnarok Online - Carnival Event Script (1st)
//==============================================================================
izlude.gat,139,93,3	script	(有)闇転送	82,{
	mes "[闇転送職員]";
	mes "ふ…カプラサービスに仕事を";
	mes "取られて今じゃこのありさまさ…";
	mes "だが！奴らを上回るサービスで";
	mes "会社を再建してみせる！";
	mes "送料はすべて当社負担?!";
	mes "さぁ…選べ！";
	next;
	switch (select("おまかせ -> ？z","プロンテラ","ゲフェン","フェイヨン","やめる")) {
	case 1:
		switch(rand(10)) {
			case 0: warp "gl_dun02.gat",234,64; 	break;
			case 1: warp "gl_dun02.gat",219,192; 	break;
			case 2: warp "gl_dun02.gat",221,261; 	break;
			case 3: warp "gl_dun01.gat",215,101; 	break;
			case 4: warp "gl_dun01.gat",237,170; 	break;
			case 5: warp "gl_dun01.gat",163,247; 	break;
			case 6: warp "gl_dun01.gat",64,73; 	break;
			case 7: warp "gl_knt02.gat",100,87; 	break;
			case 8: warp "alde_dun04.gat",173,152; 	break;
			case 9: warp "c_tower04.gat",110,73; 	break;
		}
		end;
	default:
		mes "[闇転送職員]";
		mes "近いな";
		mes "歩いていってくれ";
		close;
	case 5:
		close;
	}
}

//カーニバルイベント SHOP
geffen.gat,76,135,8	shop	あやしい商人	89,998,999,984
payon.gat,136,185,8	shop	巫女	720,1766
