//============================================================
// Auriga Script
//------------------------------------------------------------
// Ragnarok Online -- 冒険者アカデミー  アカデミー関係者
//                                                  by Pneuma
//------------------------------------------------------------

//----------------------------------
// 地域説明 -- arg1=mapno, arg2=語尾("です。"or"だよ。")
function	script	ac_map_info	{
	switch(getarg(0)) {
	case 0:// プロンテラ
		cutin "area_map_002",3;
		mes "ここはルーンミッドガッツ王国の首都。";
		mes "^0000FFプロンテラ^000000の街" + getarg(1);
		close;
	case 1:// イズルード
		cutin "area_map_006",3;
		mes "この街は首都プロンテラの";
		mes "衛星都市^0000FFイズルード^000000" + getarg(1);
		close;
	case 2:// モロク
		cutin "area_map_009",3;
		mes "[アカデミー関係者]";
		mes "ここはプロンテラ南西に位置する";
		mes "ソグラト砂漠にあるオアシスの街。";
		mes "^0000FFモロク^000000" + getarg(1);
		next;
		mes "[アカデミー関係者]";
		mes "とはいえ、今はこの有様だよ……";
		mes "街のオアシスは跡形もなくなった。";
		mes "いいかい、街の東側は";
		mes "かなり危険な状態になっている。";
		mes "プロンテラやフェイヨン方面に";
		mes "自力で砂漠を越えて行くのは無謀だ。";
		next;
		mes "[アカデミー関係者]";
		mes "移動したかったら転送を";
		mes "利用してね。";
		close;
	case 3:// アルベルタ
		cutin "area_map_007",3;
		mes "ここは冒険者の間でも話題の";
		mes "港町^0000FFアルベルタ^000000" + getarg(1);
		close;
	case 4:// ゲフェン
		cutin "area_map_003",3;
		mes "ここはミョルニール山脈に";
		mes "隣接している魔法都市^0000FFゲフェン^000000" + getarg(1);
		close;
	case 5:// フェイヨン
		cutin "area_map_007",3;
		mes "ここは緑に囲まれた山岳都市";
		mes "^0000FFフェイヨン^000000" + getarg(1);
		close;
	case 6://アルデバラン
		cutin "area_map_002",3;
		mes "ここはプロンテラ北に位置する";
		mes "^0000FFアルデバラン^000000の街" + getarg(1);
		close;
	case 7://ジュノー
		cutin "area_map_005",3;
		mes "この街はシュバルツバルド共和国の";
		mes "首都^0000FFジュノー^000000" + getarg(1);
		close;
	case 8://ウンバラ
		cutin "area_map_004",3;
		mes "ここは木々が生い茂った、";
		mes "自然豊かなうウータン族の村"; //本鯖どおり
		mes "^0000FFウンバラ^000000" + getarg(1);
		close;
	case 9://コモド
		cutin "area_map_004",3;
		mes "ここはルーンミッドガッツ王国";
		mes "最南端に位置する洞窟都市";
		mes "^0000FFコモド^000000" + getarg(1);
		close;
	case 10://フィゲル
		cutin "area_map_005",3;
		mes "ここはシュバルツバルド共和国";
		mes "北方に位置する田園都市";
		mes "^0000FFフィゲル^000000" + getarg(1);
		close;
	case 11://ラヘル
		cutin "area_map_010",3;
		mes "ここはアルナベルツ教国の";
		mes "首都^0000FFラヘル^000000" + getarg(1);
		close;
	case 12://リヒタルゼン
		cutin "area_map_010",3;
		mes "ここはアインブロックの南西に";
		mes "位置する企業都市都市"; //本鯖どおり
		mes "^0000FFリヒタルゼン^000000" + getarg(1);
		close;
	case 13://ベインス
		cutin "area_map_010",3;
		mes "ここは渓谷と崖の間に作られた";
		mes "都市^0000FFベインス^000000" + getarg(1);
	case 14://コンロン
		mes "ここは宙に浮く群島状の島。";
		mes "観光地としても有名な^0000FFコンロン^000000" + getarg(1);
		close;
	case 15://龍の城
		mes "ここは壮大な建造物が";
		mes "そびえる古都^0000FF龍之城^000000" + getarg(1);
		close;
	case 16://アユタヤ
		mes "ここは特有の信仰を持った民族が";
		mes "集まって暮らしている^0000FFアユタヤ^000000" + getarg(1);
		close;
	case 17://ピラ地下
		cutin "area_map_009",3;
		mes "ここは^0000FFモロク^000000の北西に位置する";
		mes "ピラミッドダンジョンにある";
		mes "シーフギルド" + getarg(1);
		close;
	case 18://アインブロック
		cutin "area_map_005",3;
		mes "ここは工業都市^0000FFアインブロック^000000" + getarg(1);
		close;
	case 19://アマツ
		mes "ここは豊かな水と見事な桜に囲まれた";
		mes "風情豊かな土地^0000FFアマツ^000000" + getarg(1);
		close;
	case 20://弓手村
		cutin "area_map_007",3;
		mes "ここは緑に囲まれた山岳都市";
		mes "^0000FFフェイヨン^000000にある";
		mes "弓手村" + getarg(1);
		close;
	case 21://アインベフ
		cutin "area_map_005",3;
		mes "ここは鉱山から資源を掘り出すために";
		mes "つくられた鉱夫の村、^0000FFアインベフ^000000" + getarg(1);
		close;
	}
	return;
}

//----------------------------------
// アカデミー関係者 (入学案内)
// AurigaはOnTouch重複不可の為、コンパスNPCも兼ねる

-	script	アカデミー関係者#func	-1,{
	function WARP_ACADEMY;
	function JOIN_ACADEMY;
	function DORAM_ACADEMY;

	set '@novice,callfunc("AC_GetNovice");
	set '@gatname$,getmapname("");
	while ('save_gatname$['@mapnumber]!='@gatname$) set '@mapnumber,'@mapnumber+1;

	if(Job == Job_Summoner){ // ドラム族専用
		DORAM_ACADEMY;
		end;
	} else
	if (AC_PASSPORT==0){ // 未入学
		JOIN_ACADEMY;
		end;
	} else
	if(AC_PASSPORT==1){ // 仮入学済
		WARP_ACADEMY;
		end;
	}

	if('@novice){
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "調子はどう？";
		mes "冒険者アカデミーにいくのかい？";
	} else {
		mes "[アカデミー関係者]";
		mes "こんにちは！";
		mes "熟練の冒険者からは^0000FF1000^000000Zenyの";
		mes "寄付金を頂いているんです。";
		mes "冒険者アカデミーへ";
		mes "転送しましょうか？";
	}
	next;
	switch(select("転送してもらう","周辺について知りたい","なんでもない")){
	case 1:
		WARP_ACADEMY;
		end;
	case 2:
		mes "[アカデミー関係者]";
		mes "このあたりのことについて";
		mes "知りたいんだね。";
		callfunc "ac_map_info", '@mapnumber,"だよ。";
		end;
	default:
		mes "[アカデミー関係者]";
		mes "そっか。";
		mes "いつでも、声をかけてくれれば、";
		mes "すぐに送ってあげるよ。";
		close;
	}

	function	WARP_ACADEMY	{
		set '@novice,callfunc("AC_GetNovice");
		if(!'@novice && AC_PASSPORT!=1){ //仮入学済みの場合は無料
			set '@price,(AC_PASSPORT ? 1000 : 2000);
			if (Zeny<'@price) {
				mes "[アカデミー関係者]";
				mes "あれ？";
				mes "お金が足りないみたいだね。";
				mes "申し訳ないけど、集まってから";
				mes "また来てね。";
				close;
			}
			set Zeny, Zeny - '@price;
		}
		mes "[アカデミー関係者]";
		if(AC_PASSPORT==1){
			//仮入学済み、転送後に蝶を使った場合のみ表示。
			mes "入学だね。";
		}
		set AC_SAVE_MAP, '@mapnumber;
		mes "それじゃ、冒険者アカデミーに";
		mes "転送するね。";
		mes " ";
		mes "‐アカデミーの拠点地点が";
		mes "^FF0000" +'save_mapname$[AC_SAVE_MAP]+ "^000000になりました‐";
		close2;
		switch(AC_PASSPORT){
		case 0:
			set AC_PASSPORT,1; //入学仮受付
		case 1:
			warp "ac_cl_room.gat",44,32;
			break;
		default:
			if('@novice) warp "ac_cl_area.gat",67,155;
			else         warp "ac_en_hall.gat",97,12;
		}
		return;
	}

	function	JOIN_ACADEMY	{
		set '@novice,callfunc("AC_GetNovice");
		if ('@novice) {
			if(getarg(0)){
				mes "[アカデミー関係者]";
				mes "おや？";
				mes "キミは新顔の人だね。";
				mes "冒険者アカデミーへ";
				mes "入学してみるかい？";
			} else {
				mes "[アカデミー関係者]";
				mes "こんにちは。";
				mes "今、新入生を募集しているんですよ。";
				mes "冒険者アカデミーに入学するかい？";
			}
			next;
			menu "冒険者アカデミー？",-;
			mes "[アカデミー関係者]";
			mes "冒険者アカデミーは";
			mes "駆け出しの冒険者から、";
			mes "熟練の冒険者まで、";
			mes "誰でも入学できる冒険者の学校さ。";
			next;
			mes "[アカデミー関係者]";
			mes "アカデミーに入学することで、";
			mes "いろいろな知識が学べるんだ。";
			mes "学んでいくことでいろんな特典が";
			mes "得られたりするね。";
			next;
			mes "[アカデミー関係者]";
			mes "冒険中の困難なできごとも、";
			mes "アカデミーにいる先生や";
			mes "先輩達に聞けば、";
			mes "すぐに解決するはずさ。";
			next;
			mes "[アカデミー関係者]";
			mes "冒険にはいろいろな困難が";
			mes "待ち構えているから、";
			mes "きっと助けになると思うよ。";
			mes "どうだい？";
			mes "冒険者アカデミーに入学するかい？";
		} else {
			mes "[アカデミー関係者]";
			mes "こんにちは。";
			mes "今、新入生を募集しているんだ。";
			mes "経験をつんだ熟練者の方も";
			mes "入れるけど、寄付金を頂いているよ。";
			mes "冒険者アカデミーに入学するかい？";
			next;
			switch(select("入学しない","入学する","冒険者アカデミーとは？")){
			case 1:
				mes "[アカデミー関係者]";
				mes "そうか。";
				mes "冒険者アカデミーはいつでも";
				mes "入学できるからね！";
				mes "わからないことがあったら、";
				mes "一度入学してみることを勧めるよ。";
				close;
			case 2:
				mes "[アカデミー関係者]";
				mes "そうか。";
				mes "きみは熟練の冒険者みたいだね。";
				mes "入学の寄付金は^0000FF2000^000000Zenyだよ。";
				mes "入学するかい？";
				break;
			case 3:
				mes "[アカデミー関係者]";
				mes "冒険者アカデミーは冒険者たちの";
				mes "サポートを行う学校だよ。";
				mes "冒険者アカデミーは寄付金で";
				mes "成り立っているんだ。";
				mes "アカデミーに入学することで";
				mes "いろいろな知識が学べるんだよ。";
				next;
				mes "[アカデミー関係者]";
				mes "冒険中の困難なできごとも、";
				mes "アカデミーにいる先生や先輩達に";
				mes "聞けば、すぐに解決するはずさ。";
				next;
				mes "[アカデミー関係者]";
				mes "とはいっても、今は新任の";
				mes "先生しかいないから、";
				mes "きみのほうが教える立場に";
				mes "なるかもしれないけどね。";
				emotion 23,"";
				next;
				mes "[アカデミー関係者]";
				mes "冒険に必要なことを学んでいくことで";
				mes "いろんな特典が得られるんだ。";
				mes " ";
				mes "冒険者を全面的にサポートする学校、";
				mes "それが冒険者アカデミーなのさ。";
				close;
			}
		}
		next;
		if(select("入学する","入学しない")==2){
			mes "[アカデミー関係者]";
			mes "そうか。";
			mes "冒険者アカデミーはいつでも";
			mes "入学できるからね！";
			mes "わからないことがあったら、";
			mes "一度入学してみることを勧めるよ。";
			close;
		}
		WARP_ACADEMY;
		return;
	}

	function	DORAM_ACADEMY	{
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "今、新入生を募集してるんだ。";
		mes "ドラムの君は冒険者アカデミーに";
		mes "入学することはできないが、";
		mes "見学するのは自由だよ。";
		mes "見学していくかい？";
		next;
		switch(select("見学しない","見学する","冒険者アカデミーとは？")) {
		case 1:
			mes "[アカデミー関係者]";
			mes "そうか。";
			mes "残念だ。";
			close;
		case 2:
			set AC_SAVE_MAP, '@mapnumber;
			mes "[アカデミー関係者]";
			mes "それじゃ、冒険者アカデミーに";
			mes "転送するね。";
			mes "　";
			mes "‐アカデミーの登録地点が";
			mes "^FF0000" +'save_mapname$[AC_SAVE_MAP]+ "^000000になりました‐";
			close2;
			warp "ac_cl_room.gat",44,32;
			end;
		case 3:
			mes "[アカデミー関係者]";
			mes "冒険者アカデミーは冒険者たちの";
			mes "サポートを行う学校だよ。";
			mes "冒険者アカデミーは寄付金で";
			mes "成り立っているんだ。";
			mes "アカデミーに入学することで、";
			mes "いろいろな知識が学べるんだよ。";
			next;
			mes "[アカデミー関係者]";
			mes "冒険中の困難なできごとも、";
			mes "アカデミーにいる先生や先輩達に";
			mes "聞けば、すぐに解決するはずさ。";
			next;
			mes "[アカデミー関係者]";
			mes "冒険に必要なことを学んでいくことで";
			mes "いろんな特典が得られるんだ。";
			mes "　";
			mes "冒険者を全面的にサポートする学校、";
			mes "それが冒険者アカデミーなのさ。";
			close;
		}
	}

OnTouch:
	set '@novice,callfunc("AC_GetNovice");
	set '@gatname$,getmapname("");
	while ('save_gatname$['@mapnumber]!='@gatname$) set '@mapnumber,'@mapnumber + 1;

	if ('@novice && AC_PASSPORT==0) JOIN_ACADEMY 1;

	// ミニマップにポイント表示 (その他エリアは npc_quest_ac_ontouch.txt 参照)
	switch('@mapnumber){
	case 0://プロンテラ
		if(AC_RANK==1 && AC_RANKTEST==2){ //第２課程
			viewpoint 1,156,22,20,0xFFFF00;
		}
		if( (AC_RANK==3 && AC_RANKTEST>=2 && AC_RANKTEST!=99)|| //第４課程
			(AC_RANK==4 && AC_RANKTEST>=2 && AC_RANKTEST!=99)){ //第５課程
			viewpoint 1,22,203,20,0xFFFF00;
		}
		if( (AC_QUEST_LV_0==0 && AC_QUEST_ST_0==1)||	//気になるあの子１
			(AC_QUEST_LV_0==1 && AC_QUEST_ST_0==1)||	//気になるあの子２
			(AC_QUEST_LV_0==2 && AC_QUEST_ST_0==1)||	//気になるあの子３
			(AC_QUEST_LV_0==3 && AC_QUEST_ST_0==1)||	//気になるあの子４
			(AC_QUEST_LV_0==5 && AC_QUEST_ST_0==1)||	//気になるあの子６
			(AC_QUEST_LV_0==6 && AC_QUEST_ST_0==1)||	//気になるあの子７
			(AC_QUEST_LV_0==7 && AC_QUEST_ST_0==3)){	//気になるあの子８
			if(AC_QUEST_ST_0==1) cutin "q_run_npc_01.bmp", 4;
			viewpoint 1,146,232,10,0x0000FF; //ハルバード
		}
		//東門
		if(AC_QUEST_LV_4==0 && AC_QUEST_ST_4==2){ //冒険者になりたい１
			viewpoint 1,289,203,14,0x00FFFF;
		}
		//南門
		if( (AC_QUEST_LV_4==1 && AC_QUEST_ST_4==2)|| //冒険者になりたい２
			(AC_QUEST_LV_4==5 && AC_QUEST_ST_4==2)){ //冒険者になりたい６
			viewpoint 1,156,22,14,0x00FFFF;
		}
		//西門
		if( (AC_QUEST_LV_4==3 && AC_QUEST_ST_4==2) || //冒険者になりたい４
			(AC_QUEST_LV_4==6 && AC_QUEST_ST_4==2) || //冒険者になりたい７
			(AC_QUEST_LV_4==8 && AC_QUEST_ST_4==2) ){ //冒険者になりたい９
			viewpoint 1,22,203,14,0x00FFFF;
		}
		if( (AC_QUEST_LV_3==1 && AC_QUEST_ST_3==2) ||	//ダンジョン救出１
			(AC_QUEST_LV_3==5 && AC_QUEST_ST_3==2) ||	//ダンジョン救出３
			(AC_QUEST_LV_3==8 && AC_QUEST_ST_3==3) ){	//実験のお手伝い５
			viewpoint 1,22,203,13,0x00FF00;
		}
		end;
	case 1://イズルード
		if(  AC_QUEST_ST_0==2 && AC_QUEST_LV_0==1){		//気になるあの子２
			viewpoint 1,148,148,10,0x0000FF; //道具屋
		} else 
		if( (AC_QUEST_LV_0==7 && AC_QUEST_ST_0==1)||	//気になるあの子８
			(AC_QUEST_LV_0==8 && AC_QUEST_ST_0==1)){	//気になるあの子９
			cutin "q_run_npc_03.bmp", 4;
			viewpoint 1,137,156,10,0x0000FF; //スザンヌ
		}
		if(  AC_QUEST_LV_2==5 && AC_QUEST_ST_2==2){		//お菓子の材料集め４
			viewpoint 1,201,181,12,0xFF9900; //船員
		}
		if( (AC_QUEST_LV_3==3 && AC_QUEST_ST_3==2) || //ダンジョン救出２
			(AC_QUEST_LV_3==7 && AC_QUEST_ST_3==2) ){ //ダンジョン救出４
			viewpoint 1,201,181,13,0x00FF00; //船員
		}
		end;
	case 2://モロク
		if(AC_RANK==5 && AC_RANKTEST>=4 && AC_RANKTEST!=99){ //第６課程
			viewpoint 1,160,17,20,0xFFFF00;
		}
		if( (AC_QUEST_LV_0==2 && AC_QUEST_ST_0==2)||	//気になるあの子３
			(AC_QUEST_LV_0==4 && AC_QUEST_ST_0==3)){	//気になるあの子５
			viewpoint 1,25,294,10,0x0000FF; //ピラ
		}
		if( (AC_QUEST_LV_4==2 && AC_QUEST_ST_4==2) || //冒険者になりたい３
			(AC_QUEST_LV_4==4 && AC_QUEST_ST_4==2) ){ //冒険者になりたい５
			viewpoint 1,160,17,14,0x00FFFF;
		}
		if(AC_QUEST_LV_3==2 && AC_QUEST_ST_3==3){ //実験のお手伝い２
			viewpoint 1,25,294,13,0x00FF00; //ピラ
		}
		end;
	case 3://アルベルタ
		if(AC_RANK==0 && AC_RANKTEST==2){ //第１課程
			viewpoint 1,15,234,20,0xFFFF00;
		}
		if(AC_QUEST_ST_1){ //奇跡の箱 全エピソード
			if(AC_QUEST_ST_1==1) cutin "q_run_npc_04.bmp", 4;
			viewpoint 1,39,46,11,0xFF0000;
		}
		end;
	case 4://ゲフェン
		if(AC_RANK==5 && AC_RANKTEST>=3 && AC_RANKTEST!=99){ //第６課程
			viewpoint 1,217,119,20,0xFFFF00;
		}
		if(AC_QUEST_LV_0==3 && AC_QUEST_ST_0==2){		//気になるあの子４
			viewpoint 1,172,174,10,0x0000FF; //主治医の家(オネストと同じ家)
		}
		if(AC_QUEST_ST_4==1){ //冒険者になりたい 全章
			cutin "q_run_npc_09.bmp", 4;
			viewpoint 1,172,174,14,0x00FFFF;
		}
		if(AC_QUEST_LV_3==0 && AC_QUEST_ST_3==3){	//実験のお手伝い１
			viewpoint 1,26,119,13,0x00FF00;
		}
		end;
	case 5://フェイヨン
		if(AC_RANK==2 && AC_RANKTEST==2){ //第３課程
			viewpoint 1,122,27,20,0xFFFF00; // フェイヨン南
		}
		if(AC_RANK==5 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //第６課程
			viewpoint 1,267,89,20,0xFFFF00; // フェイヨン東
		}
		if(AC_RANK==6 && AC_RANKTEST>=2 && AC_RANKTEST!=99){ //第７課程
			viewpoint 1,16,143,20,0xFFFF00; // フェイヨン西
		}
		if(AC_QUEST_LV_0==4 && AC_QUEST_ST_0==1){ //気になるあの子５
			cutin "q_run_npc_02.bmp", 4;
			viewpoint 1,140,85,10,0x0000FF; //ジェラルド(道具屋)
		}
		if(AC_QUEST_LV_1==1 && AC_QUEST_ST_1==2){ //奇跡の箱２
			viewpoint 1,216,120,11,0xFF0000; //ロイス
		}
		if(AC_QUEST_LV_2==8 && AC_QUEST_ST_2==2){ //お詫びの品を届けたい２
			viewpoint 1,165,99,12,0xFF9900; //ライアス
		}
		if(AC_QUEST_LV_3==4 && AC_QUEST_ST_3==3){ //実験のお手伝い３
			viewpoint 1,228,330,13,0x00FF00;	// 弓手村WP
		}
		if(AC_QUEST_LV_3==6 && AC_QUEST_ST_3==3){//	実験のお手伝い４
			viewpoint 1,122,27,13,0x00FF00;	// フェイヨン南
		}
		end;
	}
	end;
OnInit:
	if(strnpcinfo(2)!="func") waitingroom "アカデミー関係者",0;
	setarray 'save_gatname$,"prontera.gat","izlude.gat","morocc.gat","alberta.gat","geffen.gat","payon.gat";
	setarray 'save_mapname$,"プロンテラ","イズルード","モロク","アルベルタ","ゲフェン","フェイヨン";
}

prontera.gat,153,192,4	duplicate(アカデミー関係者#func)	アカデミー関係者::AC_PRO	750,8,8
izlude.gat,126,118,4	duplicate(アカデミー関係者#func)	アカデミー関係者::AC_IZL	750,8,8
geffen.gat,116,109,4	duplicate(アカデミー関係者#func)	アカデミー関係者::AC_GEF	750,8,8
morocc.gat,147,101,4	duplicate(アカデミー関係者#func)	アカデミー関係者::AC_MOR	750,8,8
payon.gat,159,205,4		duplicate(アカデミー関係者#func)	アカデミー関係者::AC_PAY	750,8,8
alberta.gat,107,132,4	duplicate(アカデミー関係者#func)	アカデミー関係者::AC_ALB	750,8,8

//-----------------------------------------
// ルーンのクエスト補助員

-	script	アカデミー関係者#func2	-1,{
	set '@novice, callfunc("AC_GetNovice");
	set '@gatname$,getmapname("");
	for(set '@i,0; 'mapname$['@i]!='@gatname$; set '@i,'@i+1){}
	set '@mapnumber,'@i;

	if(AC_PASSPORT==0){
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "僕は冒険者アカデミーの補助員です。";
		mes "何か僕に用ですか？";
		next;
		if(select("冒険者アカデミーについて","特に用は無い")==2){
			mes "[アカデミー関係者]";
			mes "そうですか、";
			mes "また、僕に用があれば";
			mes "来てくださいね。";
			close;
		}
		mes "[アカデミー関係者]";
		mes "冒険者アカデミーは";
		mes "冒険者のための学校です。";
		mes "アカデミーに入学することで、";
		mes "いろいろな知識が学べるんだ。";
		mes "学んでいくことでいろんな特典が";
		mes "得られるのです。";
		next;
		mes "[アカデミー関係者]";
		mes "冒険中の困難なできごとも、";
		mes "アカデミーにいる先生や";
		mes "先輩達に聞けば、";
		mes "すぐに解決するはずですよ。";
		next;
		mes "[アカデミー関係者]";
		mes "冒険者アカデミーに";
		mes "入学したい場合は、";
		mes "プロンテラ、モロク、ゲフェン、";
		mes "フェイヨン、アルベルタ、イズルード";
		mes "にいるアカデミー関係者に";
		mes "話しかけてくださいね。";
		close;
	}
	mes "[アカデミー関係者]";
	mes "こんにちは。";
	mes "冒険者アカデミーの生徒の方だね。";

	//転送チェック
	set '@warpflag,0;
	if('@novice) {
		// クエ進行中で且つ、依頼人の居るマップでないと
		// アカデミーへ移動させてくれない。
		switch('@mapnumber){
		case 6: //アルデバラン
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==0)||	//お世話になったあの人に
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==1)||	//お詫びの品を届けたい１
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==7)||	//お菓子お届け
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==8);	//お詫びの品を届けたい２
			break;
		case 7: //ジュノー
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==1)||	//お詫びの品を届けたい１
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==2)||	//お菓子の材料集め１
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==3)||	//お菓子の材料集め２
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==4)||	//お菓子の材料集め３
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==5)||	//お菓子の材料集め４
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==6)||	//お菓子の材料集め５
							(AC_QUEST_ST_2 && AC_QUEST_LV_2==7);	//お菓子お届け
			break;
		case 8: //ウンバラ
			set '@warpflag, (AC_QUEST_ST_1 && AC_QUEST_LV_1==6);	//奇跡の箱７
			break;
		case 9: //コモド
			set '@warpflag, (AC_QUEST_ST_0 && AC_QUEST_LV_0==5)||	//気になるあの子６
							(AC_QUEST_ST_1 && AC_QUEST_LV_1==7);	//奇跡の箱８
			break;
		case 10: //フィゲル
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==8)||	//お詫びの品を届けたい２
							(AC_QUEST_ST_3);						//実験のお手伝い(全エピソード)
			break;
		case 11: //ラヘル
			set '@warpflag, (AC_QUEST_ST_0 && AC_QUEST_LV_0==8);	//気になるあの子９
			break;
		case 12: //リヒタルゼン
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==2);	//お菓子の材料集め１
			break;
		case 13: //ベインス
			set '@warpflag, (AC_QUEST_ST_0 && AC_QUEST_LV_0==8);	//気になるあの子９
			break;
		case 14: //コンロン
			set '@warpflag, (AC_QUEST_ST_1 && AC_QUEST_LV_1==3);	//奇跡の箱４
			break;
		case 15: //龍之城
			set '@warpflag, (AC_QUEST_ST_1 && AC_QUEST_LV_1==4);	//奇跡の箱５
			break;
		case 16: //アユタヤ
			set '@warpflag, (AC_QUEST_ST_1 && AC_QUEST_LV_1==5);	//奇跡の箱６
			break;
		case 18: //アマツ
			set '@warpflag, (AC_QUEST_ST_1 && AC_QUEST_LV_1==2);	//奇跡の箱３
			break;
		case 19: //アインブロック
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==3);	//お菓子の材料集め２
			break;
		case 21: //アインベフ
			set '@warpflag, (AC_QUEST_ST_2 && AC_QUEST_LV_2==4);	//お菓子の材料集め３
			break;
		}
	}
	if('@warpflag){
		mes "もう、ルーンの用事はすんだのかな？";
		mes "用事がすんだのなら、";
		mes "冒険者アカデミーに転送して";
		mes "あげるよ。";
		next;
		set '@sel, select("転送してもらう","周辺について知りたい","特に用は無い");
	} else {
		mes "何か僕に用があるのかな？";
		next;
		set '@sel, select("周辺について知りたい","特に用は無い")+1;
	}
	switch('@sel){
	case 1:
		mes "[アカデミー関係者]";
		mes "それではいくよ！";
		close2;
		warp "ac_cl_area.gat",67,155;
		end;
	case 2:
		mes "[アカデミー関係者]";
		mes "このあたりのことについて";
		mes "知りたいんだね。";
		callfunc "ac_map_info", '@mapnumber, "だよ。";
		end;
	default:
		mes "[アカデミー関係者]";
		mes "そうかい？";
		mes "また、僕に用があれば";
		mes "来てね。";
		close;
	}
OnInit:
	setarray 'mapname$,"prontera.gat","izlude.gat","morocc.gat","alberta.gat","geffen.gat","payon.gat","aldebaran.gat","yuno.gat","umbala.gat","comodo.gat","hugel.gat","rachel.gat","lighthalzen.gat","veins.gat","gonryun.gat","louyang.gat","ayothaya.gat","moc_prybd1.gat","amatsu.gat","einbroch.gat","pay_arche.gat","einbech.gat";
	if(strnpcinfo(2)!="func2") waitingroom "アカデミー関係者",0;
}
aldebaran.gat,134,114,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#ALD	883
yuno.gat,142,176,4			duplicate(アカデミー関係者#func2)	アカデミー関係者#YNO	883
umbala.gat,93,154,4			duplicate(アカデミー関係者#func2)	アカデミー関係者#UBR	883
comodo.gat,172,165,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#CMD	883
hugel.gat,93,155,4			duplicate(アカデミー関係者#func2)	アカデミー関係者#HGL	883
rachel.gat,129,144,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#RCL	883
lighthalzen.gat,219,161,4	duplicate(アカデミー関係者#func2)	アカデミー関係者#LTZ	883
veins.gat,197,133,4			duplicate(アカデミー関係者#func2)	アカデミー関係者#VNS	883
amatsu.gat,121,155,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#AMA	883
gonryun.gat,174,134,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#GON	883
louyang.gat,215,118,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#LOU	883
ayothaya.gat,213,193,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#AYO	883
einbroch.gat,223,182,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#EIN	883
einbech.gat,171,137,4		duplicate(アカデミー関係者#func2)	アカデミー関係者#EIB	883

//----------------------------------
// 一次転職サポート

-	script	アカデミーサポート#func	-1,{
L_START:
	set '@novice, callfunc("AC_GetNovice");
	if     ("SWD"==strnpcinfo(2)) set '@job$,"ソードマン";
	else if("MGI"==strnpcinfo(2)) set '@job$,"マジシャン";
	//else if("ACO"==strnpcinfo(2)) set '@job$,"アコライト";
	else if("ARC"==strnpcinfo(2)) set '@job$,"アーチャー";
	else if("SHF"==strnpcinfo(2)) set '@job$,"シーフ";
	//else if("MRC"==strnpcinfo(2)) set '@job$,"マーチャント";
	else if("TKW"==strnpcinfo(2)) set '@job$,"テコンキッド";
	else if("GUN"==strnpcinfo(2)) set '@job$,"ガンスリンガー";
	else if("NIN"==strnpcinfo(2)) set '@job$,"忍者";
	else if("SNV"==strnpcinfo(2)) set '@job$,"スーパーノービス";
	if('@job$==""){
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "僕は冒険者アカデミーの";
		mes "新米冒険者担当で、";
		mes "ここで駆け出しの冒険者が";
		mes "転職するのに迷わないように";
		mes "サポートしているんだよ。";
	}
	else {
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "僕は冒険者アカデミーの";
		mes "新米冒険者担当で、"+'@job$+"に";
		mes "なろうとしている冒険者と";
		mes '@job$+"になりたての";
		mes "冒険者をサポートしているんです。";
	}
	if(!'@novice){
		next;
		mes "[アカデミー関係者]";
		mes "君はもう熟練冒険者だね。";
		mes "僕のサポートは必要ないみたいだ。";
		close;
	}
	next;
	menu "アカデミーに転送してもらう",L_WARP,"周辺について知りたい",L_WHERE,"職業の書が欲しい",L_GIVEBOOK,"なんでもない",L_CANCEL;
L_WARP:
	mes "[アカデミー関係者]";
	mes "転送するよ。";
	close2;
	warp "ac_cl_room.gat",44,59; end;
L_WHERE:
	set '@gatname$,getmapname("");
	for(set '@i,0; 'mapname$['@i]!='@gatname$; set '@i,'@i+1){}
	set '@mapnumber,'@i;
	mes "このあたりのことについて";
	mes "知りたいんですね。";
	callfunc "ac_map_info", '@mapnumber, "です。";
	end;
L_GIVEBOOK:
	mes "[アカデミー関係者]";
	mes "職業の書だね。";
	mes "はい、どうぞ。";
	mes "必要になったら";
	mes "いつでも言ってね。";
	if(checkweight(11055,1)) {
		switch(Job){
			case Job_Swordman:    getitem 11025,1; break; //ソードマンの書
			case Job_Thief:       getitem 11028,1; break; //シーフの書
			case Job_Archer:      getitem 11031,1; break; //アーチャーの書
			case Job_Acolyte:     getitem 11034,1; break; //アコライトの書
			case Job_Magician:    getitem 11037,1; break; //マジシャンの書
			case Job_Merchant:    getitem 11040,1; break; //マーチャントの書
			case Job_TaeKwon:     getitem 11043,1; break; //テコンキッドの書
			case Job_Ninja:       getitem 11046,1; break; //忍者の書
			case Job_Gunslinger:  getitem 11049,1; break; //ガンスリンガーの書
			case Job_SuperNovice: getitem 11052,1; break; //スーパーノービスの書
			default: getitem 11055,1;
		}
		close;
	}
	next;
	mes "[アカデミー関係者]";
	mes "……";
	mes "おや、君の荷物がいっぱいで";
	mes "職業の書を渡せないよ。";
	mes "荷物の種類数を減らしてから";
	mes "また話しかけてね。";
	close;
L_CANCEL:
	mes "[アカデミー関係者]";
	mes "そっか。";
	mes "いつでも、声をかけてくれれば、";
	mes "すぐに送ってあげるよ。";
	close;
OnTouch:
	if(AC_JOBCHANGE){
		set AC_JOBCHANGE,0;
		if(!callfunc("AC_GetNovice")) end;
		mes "[アカデミー関係者]";
		mes "こんにちは。";
		mes "僕は冒険者アカデミーの";
		mes "新米冒険者担当で、";
		mes "ここで駆け出しの冒険者が";
		mes "転職するのに迷わないように";
		mes "サポートしているんだよ。";
		next;
		if(BaseLevel<=55 && Job==Job_Novice && Upper!=1){
			mes "[アカデミー関係者]";
			mes "あれ？";
			mes "転職できなかったようだね。";
			mes "　";
			mes "1次職へ転職するには";
			mes "^0000FF「基本スキル」のレベルを9　^000000に";
			mes "する必要があるよ。";
			emotion 0;
			next;
			mes "[アカデミー関係者]";
			mes "転職してくるかい？";
			mes "それとも、冒険者アカデミーへ";
			mes "戻るかい？";
			next;
			if(select("1次職へ転職してくる","アカデミーに戻る")==2){
				mes "[アカデミー関係者]";
				mes "それじゃ、冒険者アカデミーに";
				mes "転送するよ。";
				close2;
				warp "ac_cl_room",44,59;
				end;
			}
		} else {
			mes "[アカデミー関係者]";
			mes "君のことはエーラから";
			mes "聞いたよ。";
			mes "無事、転職できた";
			mes "ようだね。";
			mes "おめでとう！";
			emotion 46;
			next;
			mes "[アカデミー関係者]";
			mes "冒険者アカデミーは";
			mes "駆け出しの冒険者が";
			mes "成長するには良い所だよ。";
			mes "　";
			mes "すぐ冒険者アカデミーに";
			mes "戻るかい？";
			next;
			if(select("アカデミーに戻る","アカデミーに戻らない")==1){
				mes "[アカデミー関係者]";
				mes "それじゃ、";
				mes "冒険者アカデミーへ";
				mes "転送するよ。";
				close2;
				warp "ac_cl_room",44,59;
				end;
			}
		}
		mes "[アカデミー関係者]";
		mes "いつでも";
		mes "冒険者アカデミーまで";
		mes "送るから、転職したら、";
		mes "また来てね。";
		close;
	}
	end;
OnInit:
	setarray 'mapname$,"prontera.gat","izlude.gat","morocc.gat","alberta.gat","geffen.gat","payon.gat","aldebaran.gat","yuno.gat","umbala.gat","comodo.gat","hugel.gat","rachel.gat","lighthalzen.gat","veins.gat","gonryun.gat","louyang.gat","ayothaya.gat","moc_prybd1.gat","einbroch.gat","amatsu.gat","pay_arche.gat";
	if(strnpcinfo(2)!="func") waitingroom "一次転職サポート",0;
}
izlude.gat,56,139,4			duplicate(アカデミーサポート#func)	アカデミーサポート#SWD	750,5,5
geffen.gat,65,170,4			duplicate(アカデミーサポート#func)	アカデミーサポート#MGI	750,5,7
prontera.gat,238,313,4		duplicate(アカデミーサポート#func)	アカデミーサポート#ACO	750,5,5
pay_arche.gat,141,165,4		duplicate(アカデミーサポート#func)	アカデミーサポート#ARC	750,5,5
moc_prydb1.gat,52,132,4		duplicate(アカデミーサポート#func)	アカデミーサポート#SHF	750
alberta.gat,46,46,4			duplicate(アカデミーサポート#func)	アカデミーサポート#MRC	750,5,5
payon.gat,161,135,4			duplicate(アカデミーサポート#func)	アカデミーサポート#TKW	750
einbroch.gat,131,196,4		duplicate(アカデミーサポート#func)	アカデミーサポート#GUN	750,5,5
amatsu.gat,151,139,4		duplicate(アカデミーサポート#func)	アカデミーサポート#NIN	750,5,5
aldebaran.gat,108,70,4		duplicate(アカデミーサポート#func)	アカデミーサポート#SNV	750,5,5
