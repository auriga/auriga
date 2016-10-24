//クエストスキル
prontera.gat,152,187,4	script	スキル屋	779,{
	mes "[スキル屋]";
	mes "職業を選んでください";
	next;
	set @menu,select("剣士系","ウィザード系","アーチャー系","アコライト系","シーフ系","商人系","やめる");
	if(@menu == 7) {
		close;
	}
	mes "[スキル屋]";
	mes "覚えるスキルを選んでください";
	next;
	if(@menu == 1) {
		switch(select("チャージアタック","シュリンク")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_KN)
				skill 1001,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_CR)
				skill 1002,1,0;
			close;
		}
	}
	else if(@menu == 2) {
		switch(select("サイトブラスター","コンバーター製造","水属性エレメンタルチェンジ","地属性エレメンタルチェンジ","火属性エレメンタルチェンジ","風属性エレメンタルチェンジ")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_WZ)
				skill 1006,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_SA)
				skill 1007,1,0;
			close;
		case 3:
			set '@skillid,1008;
			break;
		case 4:
			set '@skillid,1017;
			break;
		case 5:
			set '@skillid,1018;
			break;
		case 6:
			set '@skillid,1019;
			break;
		}
		// 3～6のとき続き
		if(getbaseclass(Class,2) == CLASS_SA && getskilllv(1008) <= 0 && getskilllv(1017) <= 0 && getskilllv(1018) <= 0 && getskilllv(1019) <= 0)
			skill '@skillid,1,0;
		close;
	}
	else if(@menu == 3) {
		switch(select("ファンタスミックアロー","パンボイス","魅惑のウィンク")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_HT)
				skill 1009,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_BA)
				skill 1010,1,0;
			close;
		case 3:
			if(getbaseclass(Class,2) == CLASS_DC)
				skill 1011,1,0;
			close;
		}
	}
	else if(@menu == 4) {
		switch(select("レデムプティオ","気注入","気爆発")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_PR)
				skill 1014,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_MO)
				skill 1015,1,0;
			close;
		case 3:
			if(getbaseclass(Class,2) == CLASS_MO)
				skill 1016,1,0;
			close;
		}
	}
	else if(@menu == 5) {
		switch(select("ソニックアクセラレーション","ベナムナイフ","クローズコンファイン")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_AS)
				skill 1003,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_AS)
				skill 1004,1,0;
			close;
		case 3:
			if(getbaseclass(Class,2) == CLASS_RG)
				skill 1005,1,0;
			close;
		}
	}
	else if(@menu == 6) {
		switch(select("アンフェアリートリック","貪欲")) {
		case 1:
			if(getbaseclass(Class,2) == CLASS_BS)
				skill 1012,1,0;
			close;
		case 2:
			if(getbaseclass(Class,2) == CLASS_BS)
				skill 1013,1,0;
			close;
		}
	}
	close;
}
