//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  実習室      by Pneuma
//------------------------------------------------------------

//----------------------------
// 旧実習室
//

//ac_cl_hall.gat,149,64,0	script	実習室A_WP	45,1,1,{
//	set '@novice, (BaseLevel<=25 && Upper!=1 && (Job<=6 || Job==Job_TaeKwon || Job==Job_Gunslinger || Job==Job_Ninja));
//	if(!'@novice) {
//		mes "‐ミッドの注意書き‐";
//		mes "この先は^FF0000Lv1～Lv25^000000の";
//		mes "冒険者専用の実習室になるよ！";
//		mes "^FF0000転生、2次職以上^000000の冒険者も";
//		mes "実習室には入れません。";
//		mes "駆け出しの冒険者を";
//		mes "サポートしてあげてね！";
//		close;
//	}
//	warp "ac_prac_a.gat",209,47;
//	end;
//}

//ac_cl_hall.gat,151,42,0	script	実習室B_WP	45,1,1,{
//	set '@novice, (BaseLevel>=20 && BaseLevel<=35 && Upper!=1 && (Job<=6 || Job==Job_TaeKwon || Job==Job_Gunslinger || Job==Job_Ninja));
//	if(!'@novice) {
//		mes "‐ミッドの注意書き‐";
//		mes "この先は^FF0000Lv20～Lv35^000000の";
//		mes "冒険者専用の実習室になるよ！";
//		mes "^FF0000転生、2次職以上^000000の冒険者も";
//		mes "実習室には入れません。";
//		mes "駆け出しの冒険者を";
//		mes "サポートしてあげてね！";
//		close;
//	}
//	warp "ac_prac_b.gat",0,0;
//	end;
//}

//ac_cl_hall.gat,182,21,0	script	実習室C_WP	45,1,1,{
//	set '@novice, (BaseLevel>=30 && BaseLevel<=45 && Upper!=1 && (Job<=6 || Job==Job_TaeKwon || Job==Job_Gunslinger || Job==Job_Ninja));
//	if(!'@novice) {
//		mes "‐ミッドの注意書き‐";
//		mes "この先は^FF0000Lv30～Lv45^000000の";
//		mes "冒険者専用の実習室になるよ！";
//		mes "^FF0000転生、2次職以上^000000の冒険者も";
//		mes "実習室には入れません。";
//		mes "駆け出しの冒険者を";
//		mes "サポートしてあげてね！";
//		close;
//	}
//	warp "ac_prac_c.gat",0,0;
//	end;
//}

ac_cl_hall.gat,167,53,0	script	磨り減った跡	111,{
	mes "‐銅像に張り紙が貼ってある‐";
	next;
	mes "[ミッドの注意書き]";
	mes "「こちらの実習室は封鎖されました」";
	next;
	mes "‐ここに実習室があったようだ‐";
	close;
//2010/04/13削除
//	mes "‐磨り減ったレールのような";
//	mes "跡がある‐";
//	set '@novice, (BaseLevel>=40 && BaseLevel<=55 && Upper!=1 && (Job<=6 || Job==Job_TaeKwon || Job==Job_Gunslinger || Job==Job_Ninja));
//	if('@novice){
//		next;
//		mes "銅像を押してみますか？";
//		next;
//		if(select("押してみる","何もしない")==2){
//			mes "[" +strcharinfo(0)+ "]";
//			mes "（触るのはやめておこう……）";
//			close;
//		}
//		mes "[" +strcharinfo(0)+ "]";
//		mes "（なんだろう？）";
//		mes " ";
//		mes "‐銅像を力いっぱい押してみた‐";
//		close2;
//		warp "ac_prac_d.gat",104,20;
//		end;
//	}
//	close;
}

//----------------------------------
//実習室・特別室 転送装置
ac_cl_area.gat,57,185,4		script	転送装置#AC_PRACBD01	857,{
	set '@novice, callfunc("AC_GetNovice");
	mes "[転送装置]";
	mes "こちらは実習室・特別室の";
	mes "入り口です。";
	mes "モンスターとの戦闘を";
	mes "練習したい生徒は";
	mes "行ってみましょう。";
	next;
	if(!'@novice) {
		mes "[ミッドの注意書き]";
		mes "この先は^FF0000Lv1～Lv55^000000の";
		mes "冒険者専用の実習室になるよ！";
		mes "^FF0000転生、2次職以上^000000の冒険者や";
		mes "ドラム族は実習室には入れません。";
		mes "駆け出しの冒険者を";
		mes "サポートしてあげてね！";
		close;
	}
	switch(Job){
	case Job_Novice:
		mes "‐転送装置にミッドの";
		mes "　注意書きが書いてある‐";
		next;
		mes "[ミッドの注意書き]";
		mes "この実習室は1次職に";
		mes "転職しても入れるよ！";
		mes "^0000FFノービス^000000の生徒は";
		mes "^0000FF1次職へ転職してこよう！^000000";
		mes "転職は講習室の「^FF0000フェイ^000000」が";
		mes "サポートしてくれるよ！";
		next;
		break;
	case Job_Gunslinger:
		mes "[ミッドの注意書き]";
		mes "ガンスリンガーの生徒は";
		mes "^0000FF銃弾^000000の装備を";
		mes "忘れないでね！";
		mes "銃を装備していても";
		mes "^0000FF銃弾^000000を装備していないと";
		mes "モンスターに攻撃できないよ！";
		next;
		mes "[ミッドの注意書き]";
		mes "銃弾を装備していない生徒は";
		mes "^0000FF「所持アイテム」^000000ウィンドウ内の";
		mes "^0000FF「etc」^000000タブをクリックして、";
		mes "銃弾を^0000FF「装備アイテムウィンドウ」^000000へ";
		mes "ドラッグアンドドロップして";
		mes "装備しようね！";
		next;
		mes "[ミッドの注意書き]";
		mes "もし、^0000FF「etc」^000000タブに";
		mes "銃弾がなかったら、転職時に貰った";
		mes "バレットケースが^0000FF「item」^000000タブに";
		mes "あるから、バレットケースを";
		mes "ダブルクリックして、";
		mes "銃弾（バレット）を取り出してね！";
		next;
		set '@hint,1;
		break;
	}
	menu "実習室・特別室に行く",L_PRAC,"ミッドの注意書きを読む",L_ABOUT,"何もしない",L_CANCEL;
L_PRAC:
	mes "[転送装置]";
	mes "どちらへ行きますか？";
	mes " ";
	mes "‐行くことができる実習室・特別室は";
	mes "^FF0000赤^000000、又は^0000FF青^000000で表示されます‐";
	next;
	set '@list$,"";
	for(set '@i,0; '@i<8; set '@i,'@i+1){
		if(BaseLevel>='LVREQUIRE['@i]){
			set '@list$,'@list$ + 'COLORSTR$['MAPNAMECL['@i]] + 'MAPLVSTR$['@i] + 'MAPNAME$['@i] + ":";
		} else {
			set '@list$,'@list$ + "^777777" + 'MAPLVSTR$['@i] + 'MAPNAME$['@i] + ":";
		}
	}
	set '@list$,'@list$ + "^000000まだ、準備することがある";
	set '@num,select('@list$)-1;
	if('@num==8){
		mes "[" + strcharinfo(0) + "]";
		mes "（準備してこよう）";
		close;
	}
	if(BaseLevel < 'LVREQUIRE['@num]){
		mes "[転送装置]";
		mes "この実習室を利用するためには";
		mes "^0000FFBaseLvが後 " + ('LVREQUIRE['@num] - BaseLevel) + "^000000 必要です。";
		next;
		goto L_PRAC;
	}
	savepoint "ac_cl_area.gat",53,180;
	mes "[転送装置]";
	mes "^FF0000" + 'MAPNAME$['@num] + "^000000へ転送します。";
	mes " ";
	mes "‐^0000FFセーブ位置が教室棟1F";
	mes "実習室の入り口前に^000000";
	mes "設定されました‐";
	close2;
	switch('@num){
	case 0: warp "ac_prac_01.gat",225,31; end;
	case 1: warp "ac_prac_02.gat",108,33; end;
	case 2: warp "ac_prac_03.gat",29,337; end;
	case 3: warp "ac_prac_04.gat",261,261; end;
	case 4: warp "ac_prac_05.gat",57,170; end;
	case 5: warp "ac_spec_01.gat",283,34; end;
	case 6: warp "ac_spec_02.gat",124,59; end;
	case 7: warp "ac_spec_03.gat",98,78; end;
	}
L_ABOUT:
	mes "[ミッドの注意書き]";
	mes "実習室・特別室では";
	mes "^0000FFリカバリープレート^000000を利用しよう！";
	mes "^0000FFHPとSPが回復^000000できるぞ！";
	mes " ";
	mes "^0000FF属性付与の効果^000000もあるから、";
	mes "属性効果の違いも体験してみよう！‐";
	close;
L_CANCEL:
	mes "‐何もしなかった‐";
	close2;
	switch('@hint){
	case 1:
		cutin "start_035_jp.bmp", 4;
		break;
	}
	end;
OnInit:
	waitingroom "実習室の入り口",0;
	setarray 'MAPNAME$, "実習室（海岸）","実習室（島）","実習室（高原）","実習室（炭鉱）","実習室（砂漠）","特別室（湖）","特別室（廃墟）","特別室（地下道）";
	setarray 'MAPLVSTR$,"Lv1以上　","Lv15以上 ","Lv25以上 ","Lv35以上 ","Lv45以上 ","Lv10以上 ","Lv10以上 ","Lv10以上 ";
	setarray 'LVREQUIRE,1,15,25,35,45,10,10,10;
	setarray 'MAPNAMECL,0,0,0,0,0,1,1,1;
	setarray 'COLORSTR$,"^FF0000","^0000FF";
}
ac_cl_hall.gat,152,66,4		duplicate(転送装置#AC_PRACBD01)		転送装置#AC_PRACBD02	857
ac_cl_hall.gat,154,44,4		duplicate(転送装置#AC_PRACBD01)		転送装置#AC_PRACBD03	857
ac_cl_hall.gat,174,22,4		duplicate(転送装置#AC_PRACBD01)		転送装置#AC_PRACBD04	857
ac_cl_area.gat,57,187,0		duplicate(転送装置#AC_PRACBD01)		WP#AC_PRACBD01	45,1,1
ac_cl_hall.gat,149,64,0		duplicate(転送装置#AC_PRACBD01)		WP#AC_PRACBD02	45,1,1
ac_cl_hall.gat,151,42,0		duplicate(転送装置#AC_PRACBD01)		WP#AC_PRACBD03	45,1,1
ac_cl_hall.gat,182,21,0		duplicate(転送装置#AC_PRACBD01)		WP#AC_PRACBD04	45,1,1

//----------------------------------
// 実習室 立ち入り禁止看板
function	script	stopboard_func	{
	viewpoint 1,getarg(0),getarg(1),1,0xFF0000;
	mes "‐この先立ち入り禁止‐";
	mes " ";
	mes "‐迷ってしまった生徒は";
	mes "ミニマップの「^FF0000+^000000」を頼りに";
	mes "戻ってくること‐";
	close;
}
//実習室（海岸）
ac_prac_01.gat,299,57,4		script	#ac_exerboard_P11	837,{ callfunc "stopboard_func",225,31; }
ac_prac_01.gat,370,93,4		script	#ac_exerboard_P12	837,{ callfunc "stopboard_func",225,31; }
ac_prac_01.gat,22,59,4		script	#ac_exerboard_P13	837,{ callfunc "stopboard_func",225,31; }
//実習室（島）
ac_prac_02.gat,111,91,4		script	#ac_exerboard_P21	837,{ callfunc "stopboard_func",108,27; }
//実習室（高原）
ac_prac_03.gat,27,241,4		script	#ac_exerboard_P31	837,{ callfunc "stopboard_func",29,343; }
ac_prac_03.gat,191,236,4	script	#ac_exerboard_P32	837,{ callfunc "stopboard_func",29,343; }
//実習室（炭鉱）
ac_prac_04.gat,19,15,0		script	#ac_exerboard_P41	837,{ callfunc "stopboard_func",261,261; }
//実習室（砂漠）
ac_prac_05.gat,160,378,4	script	#ac_exerboard_P51	837,{ callfunc "stopboard_func",51,170; }
ac_prac_05.gat,380,308,4	script	#ac_exerboard_P52	837,{ callfunc "stopboard_func",51,170; }
//特別室（湖）
ac_spec_01.gat,371,345,4	script	#ac_exerboard_S11	837,{ callfunc "stopboard_func",283,34; }
ac_spec_01.gat,35,26,4		script	#ac_exerboard_S12	837,{ callfunc "stopboard_func",283,34; }
ac_spec_01.gat,17,172,4		script	#ac_exerboard_S13	837,{ callfunc "stopboard_func",283,34; }
ac_spec_01.gat,378,168,4	script	#ac_exerboard_S14	837,{ callfunc "stopboard_func",283,34; }
//特別室（地下道）
ac_spec_03.gat,67,278,4		script	#ac_exerboard_S31	837,{ callfunc "stopboard_func",105,78; }

//----------------------------------
// リカバリープレート
-	script	リカバリープレート#func	-1,{
	setarray 'RECOVER_TIME,0,1,2,4,8;
	set '@time,(BaseLevel>20) * 'RECOVER_TIME[(BaseLevel-11)/10];
	mes "[リカバリープレート]";
	if(BaseLevel>60){
		set @AC_RECOVERTIME,0;
		mes "[ミッドの注意書き]";
		mes "‐このリカバリープレートは";
		mes "実習中の^FF0000冒険者見習い^000000の為に";
		mes "用意された実習用の機械さ！‐";
		mes " ";
		mes "‐一人前の冒険者には";
		mes "利用することが出来ないんだ！‐";
		close;
	}
	if(gettimetick(2) < @AC_RECOVERTIME) { //タイマーチェック
		set '@min,(((@AC_RECOVERTIME-gettimetick(2))/60) % 60);
		if('@min==0){
			mes "^FF0000リカバリー起動準備開始……^000000";
		} else {
			mes "^FF0000再リカバリーまで、およそ"+'@min+"分^000000";
		}
		mes " ";
		mes "‐何をしますか？‐";
		next;
		menu "注意書きを読む",L_ABOUT,"何もしない",L_CANCEL;
	} else {
		set @AC_RECOVERTIME,0;
		mes "^FF0000リカバリー可能^000000";
		mes " ";
		mes "‐何をしますか？‐";
		next;
		menu "リカバリーを行う",-,"注意書きを読む",L_ABOUT,"何もしない",L_CANCEL;
	}
	mes "[リカバリープレート]";
	mes "何の属性を付与しますか？^FF0000";
	mes "‐属性付与は武器を装備した状態で";
	mes "行うことができます-^000000";
	next;
	set '@num,select("火属性を付与","地属性を付与","風属性を付与","水属性を付与","聖属性を付与","毒属性を付与","属性を付与しない","何もしない");
	if('@num==8) goto L_CANCEL;
	mes "[リカバリープレート]";
	switch('@num) {
		case 1: npcskillsupport 280,4,"","";  sc_start 90,1800000,5; mes "‐^FF0000火^000000属性の付与を行いました‐";break;
		case 2: npcskillsupport 283,4,"","";  sc_start 93,1800000,5; mes "‐^FF0000土^000000属性の付与を行いました‐";break;
		case 3: npcskillsupport 282,4,"","";  sc_start 92,1800000,5; mes "‐^FF0000風^000000属性の付与を行いました‐";break;
		case 4: npcskillsupport 281,4,"","";  sc_start 91,1800000,5; mes "‐^FF0000水^000000属性の付与を行いました‐";break;
		case 5: npcskillsupport 425,7,"","";  sc_start 17,300000,5;  mes "‐^FF0000聖^000000属性の付与を行いました‐";break;
		case 6: npcskillsupport 138,10,"",""; sc_start  6,900000,5;  mes "‐^FF0000毒^000000属性の付与を行いました‐";break;
		case 7: break;
	}
	mes "‐HP、SPが回復しました‐";
	set @AC_RECOVERTIME,gettimetick(2) + ('@time * 60); //タイマーセット
	misceffect 7,"";
	percentheal 100,100;
	close;
L_ABOUT:
	mes "[ミッドの注意書き]";
	mes "‐このリカバリープレートは";
	mes "実習中の冒険者のために";
	mes "用意された実習用の機械さ！‐";
	next;
	mes "[ミッドの注意書き]";
	if('@time>0) mes "‐今の君は^FF0000約" + '@time + "^000000分おきに";
	else         mes "‐今の君は^FF0000いつでも^000000";
	mes "リカバリーを行えるよ！‐";
	mes " ";
	mes "‐リカバリーとは？‐";
	mes "‐HP、SPの回復、属性付与を";
	mes "行うことさ！‐";
	next;
	mes "[ミッドの注意書き]";
	mes "‐上級者になればなるほど";
	mes "リカバリーを実行する時の";
	mes "^FF0000パワーが必要^000000なんだ！‐";
	mes " ";
	mes "‐上級者は、パワーの充電に";
	mes "時間がかかるので注意してね！‐";
	next;
	mes "[ミッドの注意書き]";
	mes "‐属性付与は";
	mes "火属性、地属性、風属性、水属性、";
	mes "毒属性、聖属性、を付与できる！‐";
	next;
	mes "[ミッドの注意書き]";
	mes "‐いろんな属性を試してみよう！-^FF0000";
	mes "‐属性付与は武器を装備した状態で";
	mes "行うことができるよ！-^000000";
	close;
L_CANCEL:
	mes "[リカバリープレート]";
	mes "‐操作を取り消しました‐";
	close;
}
//実習室（海岸）
ac_prac_01.gat,236,51,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_01.gat,52,30,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_01.gat,322,179,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_01.gat,141,130,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_01.gat,354,34,4		duplicate(リカバリープレート#func)	リカバリープレート	857

//実習室（島）
ac_prac_02.gat,116,58,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_02.gat,171,131,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_02.gat,58,150,4		duplicate(リカバリープレート#func)	リカバリープレート	857

//実習室（高原）
ac_prac_03.gat,46,310,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_03.gat,132,35,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_03.gat,26,90,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_03.gat,119,174,4	duplicate(リカバリープレート#func)	リカバリープレート	857

//実習室（炭鉱）
ac_prac_04.gat,287,271,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_04.gat,228,78,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_04.gat,141,178,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_04.gat,12,119,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_04.gat,44,273,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_04.gat,119,32,4		duplicate(リカバリープレート#func)	リカバリープレート	857

//実習室（砂漠）
ac_prac_05.gat,150,323,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_05.gat,229,288,3	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_05.gat,357,252,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_05.gat,229,204,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_05.gat,120,178,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_prac_05.gat,264,112,4	duplicate(リカバリープレート#func)	リカバリープレート	857

//特別室（湖）
ac_spec_01.gat,261,47,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_01.gat,310,271,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_01.gat,236,337,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_01.gat,140,137,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_01.gat,123,236,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_01.gat,232,121,4	duplicate(リカバリープレート#func)	リカバリープレート	857

//特別室（廃墟）
ac_spec_02.gat,140,72,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,185,40,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,174,147,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,72,176,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,25,155,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,74,72,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,29,33,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_02.gat,120,130,4	duplicate(リカバリープレート#func)	リカバリープレート	857

//特別室（地下道）
ac_spec_03.gat,140,168,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,204,46,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,73,220,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,283,275,4	duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,256,81,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,9,220,4		duplicate(リカバリープレート#func)	リカバリープレート	857
ac_spec_03.gat,194,179,4	duplicate(リカバリープレート#func)	リカバリープレート	857

//----------------------------------
-	script	アカデミーボックス#func		-1,{
	mes "[アカデミーボックス]";
	mes "ウィーン…　ピピピッ…";
	mes " ";
	mes "アカデミー生徒　確認完了";
	mes "各種機能　ヲ　選択シテクダサイ";
	next;
	menu "ポーション交換サービス",L_POTION,"入り口転送サービス",L_TENSOU,"アカデミーボックスの手引き",L_HOWTO,"やっぱり止める",L_CANCEL;
L_POTION:
	setarray '@potname$,"初心者用ポーション","初心者用青ポーション","スピードアップポーション","ハイスピードポーション";
	setarray '@potid,569,11518,645,656;
	mes "[アカデミーボックス]";
	mes "交換シタイ";
	mes "ポーション ヲ";
	mes "選択シテクダサイ";
	next;
	set '@num,select("初心者用ポーション","初心者用青ポーション","スピードアップポーション","ハイスピードポーション","やっぱり止める")-1;
	if('@num==4) goto L_CANCEL;
	mes "[アカデミーボックス]";
	switch('@num){
	case 0:
		mes "初心者用ポーション";
		mes "効果:HP回復";
		next;
		setarray '@item,914,507,945;
		setarray '@amount,10,5,20;
		setarray '@amount2,25,50,100;
		setarray '@name$,"綿毛","赤ハーブ","タヌキの葉"; //タヌキの葉で本鯖通り
		break;
	case 1:
		mes "初心者用青ポーション";
		mes "効果:SP回復^FF0000";
		mes "※コノアイテムハ 倉庫ヲ含メ、";
		mes "　一切ノ移動ガ出来マセン^000000";
		next;
		setarray '@item,1026,998,549;
		setarray '@amount,1,1,1;
		setarray '@amount2,1,2,5;
		setarray '@name$,"どんぐり","鉄","おいしい焼きいも";
		break;
	case 2:
		mes "スピードアップポーション";
		mes "Lv制限:1以上";
		mes "効果:攻撃速度上昇（小）";
		mes "利用可能ナ1次職業:スベテノ1次職";
		next;
		setarray '@item,940;
		setarray '@amount,30;
		setarray '@amount2,1;
		setarray '@name$,"バッタの足";
		break;
	case 3:
		mes "ハイスピードポーション";
		mes "Lv制限:40以上";
		mes "効果:攻撃速度上昇（中）";
		mes "利用可能な1次職:";
		mes "アコライト ヲ除ク スベテノ1次職";
		next;
		setarray '@item,1018;
		setarray '@amount,15;
		setarray '@amount2,1;
		setarray '@name$,"土竜の爪";
		break;
	}
	mes "[アカデミーボックス]";
	mes '@potname$['@num] + "交換リスト";
	set '@select$,"";
	for(set '@i,0; '@i<getarraysize('@name$); set '@i,'@i+1){
		mes "　" + '@name$['@i] + ('@amount['@i]) + "個＝" + '@amount2['@i] + "個";
		set '@select$,'@select$ + '@name$['@i] + ":";
	}
	set '@select$,'@select$ + '@name$['@i] + "交換しない";
	if('@num>1) mes " ";
	mes "交換スル アイテム ヲ";
	mes "選択シテ クダサイ";
	next;
	set '@trade,select('@select$)-1;
	if('@trade==getarraysize('@name$)) goto L_CANCEL;
	mes "[アカデミーボックス]";
	mes '@name$['@trade] + ('@amount['@trade]) + "個 ヲ";
	mes '@potname$['@num] + ('@amount2['@trade]) + "個ニ";
	mes "交換シマス";
	mes " ";
	mes "ヨロシイデスカ？";
	next;
	menu "はい",-,"やっぱり止める",L_CANCEL;
	if(countitem('@item['@trade])<'@amount['@trade]){
		mes "[アカデミーボックス]";
		mes "ガガピー……　ガガッ…";
		mes " ";
		mes "交換 ニ 必要 ナ";
		mes "アイテム ガ 足リマセン";
		mes " ";
		mes "確認シテカラ御利用クダサイ";
		close;
	}
	if(!checkweight('@potid['@num],'@amount2['@trade])){
		mes "[アカデミーボックス]";
		mes "ガガピー……　ガガッ…";
		mes " ";
		mes "重量 ガ 超過シテイルヨウデス";
		mes " ";
		mes "アイテム ヲ 預ケルカ 捨テルナド";
		mes "調整シテカラ御利用クダサイ";
		close;
	}
	delitem '@item['@trade],'@amount['@trade];
	getitem '@potid['@num],'@amount2['@trade];
	mes "[アカデミーボックス]";
	mes "ピピピッ…ピーッ！";
	mes " ";
	mes "（コロン、コロン）";
	mes " ";
	mes "御利用アリガトウゴザイマシタ";
	mes "又 ノ 御利用オ待チシテオリマス";
	close;
L_TENSOU:
	mes "[アカデミーボックス]";
	mes "転送エネルギー ニ";
	mes "ゼロピー 2 個 ガ 必要デス";
	mes "エネルギー ヲ 充電スル事 デ";
	mes "アカデミー入り口 へ 転送デキマス";
	mes " ";
	mes "利用シマスカ？";
	next;
	menu "はい",-,"やっぱり止める",L_CANCEL;
	if(countitem(909)<2){
		mes "[アカデミーボックス]";
		mes "ガガピー……　ガガッ…";
		mes " ";
		mes "ゼロピー ガ 不足シテイル カ";
		mes "アイテム ノ 種類 ガ 違ウヨウデス";
		mes " ";
		mes "アカデミー転送 ヲ 中止シマシタ";
		close;
	}
	mes "[アカデミーボックス]";
	mes "ソレデハ 転送シマス";
	close2;
	delitem 909,2;
	warp "ac_cl_area.gat",53,181;
	end;
L_HOWTO:
	mes "‐アカデミーボックスを利用する為に、";
	mes "各交換リストに対応したアイテムを";
	mes "必要数用意する必要があります";
	mes "まず、ポリンやファブルを倒すことで";
	mes "機能を体験することができるでしょう";
	mes " ";
	mes "と、手引きには書いてあった‐";
	close;
L_CANCEL:
	mes "‐アカデミーボックスの";
	mes "操作を中止した‐";
	close;
}
//実習室（海岸）
ac_prac_01.gat,236,56,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_01.gat,52,35,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_01.gat,141,125,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_01.gat,317,174,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_01.gat,354,40,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888

//実習室（島）
ac_prac_02.gat,111,58,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_02.gat,171,126,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_02.gat,56,145,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888

//実習室（高原）
ac_prac_03.gat,42,306,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_03.gat,137,41,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_03.gat,26,85,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_03.gat,114,174,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888

//実習室（炭鉱）
ac_prac_04.gat,279,279,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_04.gat,223,88,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_04.gat,145,177,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_04.gat,19,119,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_04.gat,49,269,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_04.gat,116,27,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888

//実習室（砂漠）
ac_prac_05.gat,154,323,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_05.gat,223,288,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_05.gat,357,247,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_05.gat,225,204,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_05.gat,117,168,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_prac_05.gat,256,103,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888

//特別室（湖）
ac_spec_01.gat,265,52,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_01.gat,310,277,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_01.gat,240,333,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_01.gat,134,144,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_01.gat,128,236,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_01.gat,236,117,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888

//特別室（廃墟）
ac_spec_02.gat,140,68,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,180,40,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,180,147,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,69,178,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,38,155,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,70,76,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,29,38,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_02.gat,123,133,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888

//特別室（地下道）
ac_spec_03.gat,140,163,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,207,46,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,251,81,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,282,280,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,73,216,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,9,216,4		duplicate(アカデミーボックス#func)	アカデミーボックス	888
ac_spec_03.gat,194,184,4	duplicate(アカデミーボックス#func)	アカデミーボックス	888
