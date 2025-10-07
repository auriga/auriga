//= Auriga Script ==============================================================
// Ragnarok Online Warlock Jobchange Script	by Blaze
//- Registry -------------------------------------------------------------------
// CHANGE_WL -> 0～9
//==============================================================================

//============================================================
// マップフラグ
//------------------------------------------------------------
job3_war01.gat	mapflag	nomemo		dummy
job3_war01.gat	mapflag	noteleport	dummy
job3_war01.gat	mapflag	nosave		SavePoint
job3_war01.gat	mapflag	nobranch	dummy
job3_war01.gat	mapflag	nopenalty	dummy
job3_war01.gat	mapflag	noicewall	dummy
job3_war02.gat	mapflag	nomemo		dummy
job3_war02.gat	mapflag	noteleport	dummy
job3_war02.gat	mapflag	nosave		SavePoint
job3_war02.gat	mapflag	nobranch	dummy
job3_war02.gat	mapflag	nopenalty	dummy
job3_war02.gat	mapflag	noicewall	dummy

//============================================================
// モンスター
//------------------------------------------------------------
spl_fild02.gat,0,0,0,0	monster	魔力に酔ったBゴーレム	2049,20,5000,0,0
spl_fild02.gat,0,0,0,0	monster	魔力に酔ったナーガ		2047,20,5000,0,0

//============================================================
// 簡易倉庫（npc_misc_storage.scより）
//------------------------------------------------------------
splendide.gat,209,110,4	script	倉庫管理人	80,{
	callfunc "Func_StorageManager",50,0;
	close;
}
splendide.gat,206,108,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
splendide.gat,208,108,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
splendide.gat,210,108,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
splendide.gat,212,108,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// 開始NPC
//------------------------------------------------------------
morocc.gat,97,144,0	script	歪んだ空間#morroc	723,{
	if(Job == Job_Warlock) {
		mes "‐奇妙な歪みを感じる‐";
		if(checkquest(129700)) {
			next;
			mes "[インフォメーション]";
			mes "あなたは転職試験の";
			mes "クリア報酬";
			mes "ステータス・スキル一括リセット権";
			mes "を所持しています。";
			next;
			mes "[インフォメーション]";
			mes "権利を利用する場合、";
			mes "イズルードにいる";
			mes "サンシイを訪ねてください。";
		}
		close;
	}
	emotion 1,"";
	mes "‐これまで感じたことの無い";
	mes "　強力な魔力が目の前の空間から";
	mes "　溢れ出ているのを感じる‐";
	next;
	if(select("調べてみる","無視する") == 2) {
		mes "‐何が起こるかわからない。";
		mes "　近寄らない方が良さそうだ‐";
		close;
	}
	if(Job == Job_Warlock) {

	}
	if(Job != Job_Wizard || Upper == UPPER_NORMAL) {
		emotion 9,"";
		mes "‐近づくが何も感じない。";
		mes "　気にしない方が良さそうだ‐";
		close;
	}
	if((Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {
		mes "‐近づくが、強力な魔力に";
		mes "　足がすくんでしまい";
		mes "　近づくことができない‐";
		next;
		if(Upper == UPPER_HIGH)
			mes  "-^3377FFBaseLvを90以上^000000に";
		else
			mes  "-^3377FFBaseLvを99、JobLvを50^000000に";		// 養子のとき未調査
		mes "　上げてから";
		mes "　再度、調べることにしよう‐";
		close;
	}
	mes "‐キィィィィィィィィイン‐";
	next;
	mes "‐手を伸ばすと";
	mes "　自分の魔力と反応したのか";
	mes "　耳をつんざくような轟音と共に";
	mes "　目の前の空間がうねり始めた‐";
	if(CHANGE_WL == 0) {
		next;
		if(strnpcinfo(2) == "splendide")
			set '@npcname$,"転職代行係#WL2";
		else
			set '@npcname$,"転職代行係#WL";
		cloakoffnpc '@npcname$;
		misceffect 78,'@npcname$;
		if(callfunc("Func_Job3rd",Job_Warlock)) {
			cloakonnpc '@npcname$;
			end;
		}
		cloakonnpc '@npcname$;
		set CHANGE_WL,1;
		setquest 104505;
	}
	else {
		close2;
	}
	warp "spl_in02.gat",79,102;
	end;
}

splendide.gat,141,284,0	duplicate(歪んだ空間#morroc)	歪んだ空間#splendide	723

morocc.gat,94,149,3	script(CLOAKED)	転職代行係#WL	888,{
	cloakonnpc;
	end;
}

splendide.gat,140,285,3	duplicate(転職代行係#WL)	転職代行係#WL2	888

//============================================================
// マスターの部屋
//------------------------------------------------------------
spl_in02.gat,80,108,5	script	マスター	465,{
	if(Job == Job_Warlock) {
		cutin "3rd_wl_queen03",1;
		mes "[エグノロリア]";
		mes "常に自己の力量を";
		mes "正確に把握することだ。";
		next;
		mes "[エグノロリア]";
		mes "それができず、身の丈に合わない";
		mes "力を使い続ければ";
		mes "いつか自分自身の力に";
		mes "喰われてしまうだろう。";
		next;
		cutin "3rd_wl_queen05",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "死にたくなければ";
		mes "修練を怠らないことだ。";
		mes "フフフ……。";
		close2;
		cutin "3rd_wl_queen05",255;
		end;
	}
	switch(CHANGE_WL) {
	case 0:
	case 1:
		if(YGG_1QUE < 100) {	// 知恵の王の指輪クエスト
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "Ikaga　Waba？";
			mes "Zalgu　Qaguasre";
			mes "Kguawi　GakitWama？";
			next;
			cutin "war_y3",2;
			emotion 0,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "Haytaw！";
			mes "DatguaZe　Lta！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "Fooalzwa";
			mes "Atugaz　NataMauta";
			mes "Maitaga？";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "Paie　Mlzgaa！";
			mes "Wmagataz　Kutta！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "……Rtaal。";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "Xata　Xatayi！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "Owagzkg　Qgalbia";
			mes "RgaBlata　Matwaty";
			mes "Watagaz　Lalta？";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "Ettu　Ata　AgaIluti！";
			mes "Vrgao　Girwttn……";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "Eatakl……。";
			mes "Qazlga　Xtowna";
			mes "Lgarw　Mmata";
			next;
			mes "[妖精]";
			mes "MushSartas　Ir　Cyamar";
			mes "UdenLo";
			if(CHANGE_WL == 0) {
				close2;
				cutin "3rd_wl_queen01",255;
				warp "splendide.gat",200,100;
				end;
			}
			next;
			cutin "3rd_wl_queen01",255;
			misceffect 235,"";
			mes "‐緑色の髪をした妖精が";
			mes "　呪文を唱えた瞬間";
			mes "　今まで感じたことが無い";
			mes "　強力な魔力が体を包み込んできた‐";
			next;
			cutin "3rd_wl_queen02",1;
			emotion 0;
			mes "[妖精]";
			mes "ほお～、面白いじゃない。";
			mes "人間の分際で、この私の魔法に";
			mes "抵抗するなんて。";
			next;
			mes "[妖精]";
			mes "こっちの言葉がわからない";
			mes "みたいだから";
			mes "そっちの言葉で話をして";
			mes "あげるわ。";
			mes "特別サービスよ。";
			next;
			emotion 0,"";
			mes "[妖精]";
			mes "別に驚くほどのことではないわ。";
			mes "人間たちのことは、以前から";
			mes "知っているもの……。";
			mes "フフフッ……";
			next;
		}
		else {
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "何の騒ぎ？";
			mes "瞑想中は静かにしなさいと";
			mes "いつも言っているはずだけど？";
			next;
			cutin "war_y3",2;
			emotion 0,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "うわっ！";
			mes "も、申し訳ありません！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "ほお～。";
			mes "私の目の前に人間がいるようだけど";
			mes "これはいったい、どういうこと？";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "申し訳ありません！";
			mes "い、今すぐ追い払います！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "……ユッブ。";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "は、はいぃぃ！";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "お前の後ろに、開けっ放しの";
			mes "ワープポータルがあるようだけど";
			mes "私の見間違いかしら？";
			next;
			cutin "war_y3",2;
			emotion 19,"小さな妖精#WL";
			mes "[小さい妖精]";
			mes "すすす、すみません！";
			mes "また、うっかりと……";
			next;
			cutin "3rd_wl_queen01",1;
			mes "[妖精]";
			mes "この愚か者め……。";
			mes "お前への仕置きは、この人間を";
			mes "追い出してからにしよう。";
			next;
			mes "[妖精]";
			mes "MushSartas　Ir　Cyamar";
			mes "UdenLo";
			if(CHANGE_WL == 0) {
				close2;
				cutin "3rd_wl_queen01",255;
				warp "splendide.gat",200,100;
				end;
			}
			next;
			cutin "3rd_wl_queen01",255;
			misceffect 235,"";
			mes "‐緑色の髪をした妖精が";
			mes "　呪文を唱えた瞬間";
			mes "　今まで感じたことが無い";
			mes "　強力な魔力が体を包み込んできた‐";
			next;
			cutin "3rd_wl_queen02",1;
			emotion 0;
			mes "[妖精]";
			mes "ほお～、面白いじゃない。";
			mes "人間の分際で、この私の魔法に";
			mes "抵抗するなんて。";
			next;
		}
		cutin "3rd_wl_queen03",1;
		emotion 5;
		mes "[妖精]";
		mes "ふ～ん……。";
		mes "良く見たら、かなり興味深い";
		mes "人間じゃない。";
		next;
		menu "あなたはいったい？",-;
		mes "[エグノロリア]";
		mes "私は^FF0000ウォーロック^000000の指導者。";
		mes "^FF0000シラー・エグノロリア^000000。";
		mes "貴方も魔法使いを名乗るなら";
		mes "私の名前を覚えておきなさい。";
		next;
		menu "ウォーロック？",-;
		emotion 5;
		mes "[エグノロリア]";
		mes "ほお……。";
		mes "^FF0000ウォーロック^000000に興味があるみたいね？";
		next;
		mes "[エグノロリア]";
		mes "でも、ウォーロックは";
		mes "人智を超えた強大な魔法を使う者。";
		mes "言葉で説明できる存在ではない。";
		next;
		cutin "3rd_wl_queen05",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "……強大な魔力。";
		mes "それだけが、その存在を説明するの。";
		mes "フフフ……。";
		next;
		menu "私もウォーロックになれますか？",-;
		cutin "3rd_wl_queen06",1;
		emotion 56;
		mes "[エグノロリア]";
		mes "あははははは！";
		mes "人間であるお前が";
		mes "ウォーロックになりたいって？";
		next;
		emotion 56;
		mes "[エグノロリア]";
		mes "あははははは！";
		mes "本当に面白い人間ね。";
		mes "だけど、人間がウォーロックに";
		mes "なるのは無理な話よ。";
		next;
		mes "[エグノロリア]";
		mes "ウォーロックの強大な魔力に";
		mes "お前の軟弱な肉体が喰われて";
		mes "しまうからよ。";
		next;
		cutin "3rd_wl_queen05",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "はじめから死ぬつもりなら";
		mes "方法を教えてあげてもいいわよ？";
		mes "フフフ……。";
		next;
		set @menu,select("方法を教えてください","諦めて立ち去る");
		break;
	case 2:
		cutin "3rd_wl_queen01",1;
		mes "[エグノロリア]";
		mes "何をしに来たの？";
		mes "私に用でもあるのかしら？";
		next;
		set @menu,select("ウォーロックになりたいです","用事はありません");
		break;
	case 3:
		cutin "3rd_wl_queen04",1;
		mes "[エグノロリア]";
		mes "私はこれから瞑想に入るから。";
		mes "そこの「バナナの皮」みたいなやつに";
		mes "話を聞きなさい。";
		close2;
		cutin "3rd_wl_queen04",255;
		end;
	case 5:
		cutin "3rd_wl_queen05",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "ユッブから話は聞いたわ。";
		mes "かなり質のいい原石が";
		mes "出来たようね。";
		mes "フフフ……。";
		next;
		mes "[エグノロリア]";
		mes "魔力を持つ宝石は美しいものほど";
		mes "強い魔力を宿すのよ。";
		next;
		cutin "3rd_wl_queen05",1;
		mes "[エグノロリア]";
		mes "……シェーズ。";
		next;
		cutin "3rd_wl_queen05",255;
		mes "[シェーズ]";
		mes "お呼びですか、マスター。";
		next;
		cutin "3rd_wl_queen05",1;
		mes "[エグノロリア]";
		mes "この者に「魔力の部屋」の";
		mes "使用許可を与えるわ。";
		mes "お前が案内してやるように。";
		next;
		cutin "3rd_wl_queen05",255;
		mes "[シェーズ]";
		mes "了解しました、マスター。";
		set CHANGE_WL,6;
		chgquest 11108,11109;
		close;
	case 9:
		cutin "3rd_wl_queen04",1;
		mes "[エグノロリア]";
		mes "美しい光ね……。";
		mes "お前の作った虚無の石と";
		mes "お前の魂のことよ。";
		mes "私の想像以上だわ。";
		next;
		mes "[エグノロリア]";
		mes "さあ、虚無の石を受け取りなさい。";
		mes "それを身に付けることで";
		mes "お前の望む存在になれるわ。";
		next;
		if(select("虚無の石を受け取る","心の準備ができていません") == 2) {
			cutin "3rd_wl_queen06",1;
			emotion 56;
			mes "[エグノロリア]";
			mes "あはははは！";
			mes "この期に及んで臆したのか？";
			mes "フフフ……面白いヤツだ。";
			close2;
			cutin "3rd_wl_queen06",255;
			end;
		}
		mes "[エグノロリア]";
		mes "よろしい。";
		mes "さあ、受け取りなさい。";
		next;
		if(Weight || checkitemblank() < 2 || checkcart() || checkfalcon() || checkriding() || checkdragon() || checkgear() || checkwolf() || sc_ison(SC_ALL_RIDING) || getpetinfo(0)) {
			cutin "3rd_wl_queen03",1;
			mes "[エグノロリア]";
			mes "準備が整っていないわ。";
			mes "一旦、引き連れているものは全て解放し、";
			mes "重量がある物は全て預けてきなさい。";
			next;
			cutin "3rd_wl_queen06",255;
			mes "[インフォメーション]";
			mes "お持ちのアイテムは";
			mes "倉庫に預けるなどして";
			mes "所持アイテムの重量を";
			mes "^FF00000^000000にして下さい。";
			mes "空き種類数にも";
			mes "ある程度の余裕を持たせてください。";
			next;
			mes "[インフォメーション]";
			mes "カート、ファルコン、";
			mes "ペコペコ、ドラゴン、";
			mes "グリフォン、ウォーグ、";
			mes "魔導ギア、騎乗生物、";
			mes "ペットは";
			mes "外してきて下さい。";
			close;
		}
		if(SkillPoint) {
			cutin "3rd_wl_queen03",1;
			mes "[エグノロリア]";
			mes "準備が整っていないわ。";
			mes "スキルポイントが残っているから";
			mes "すべて使い切ってきなさい。";
			close2;
			cutin "3rd_wl_queen03",255;
			end;
		}
		if(Job != Job_Wizard || Upper == UPPER_NORMAL || (Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {	// 念のため職チェック
			cutin "3rd_wl_queen03",1;
			mes "[エグノロリア]";
			mes "準備が整っていないわ。";
			close2;
			cutin "3rd_wl_queen03",255;
			end;
		}
		set CHANGE_WL,0;
		chgquest 11112,201185;
		compquest 201185;
		resetstatus;
		resetskill;
		setoption 0;
		jobchange Job_Warlock;
		getitem 5753,1;		// 魔力石の帽子
		getitem 2795,1;		// 熟していないリンゴの指輪
		setquest 129700;	// ステータス＆スキル一括リセット権
		cutin "3rd_wl_queen06",1;
		mes "[エグノロリア]";
		mes "そうそう。これも渡しておくわ。";
		mes "しばらくは役に立つでしょ。";
		next;
		mes "[エグノロリア]";
		mes "おめでとう、と言っておくわ。";
		mes "まさか人間が私たちと同じ存在に";
		mes "なれるとは思っていなかったけど。";
		next;
		cutin "3rd_wl_queen03",1;
		mes "[エグノロリア]";
		mes "思えば、お前がここに来たのも";
		mes "何かの運命だったのかもしれない。";
		mes "フフフ……。";
		next;
		mes "[エグノロリア]";
		mes "今後は、ウォーロックとしての";
		mes "誇りを持ち";
		mes "その力を上手く使うことだ。";
		next;
		cutin "3rd_wl_queen01",1;
		mes "[エグノロリア]";
		mes "……とは言え、一応忠告しておこう。";
		next;
		mes "[エグノロリア]";
		mes "常に自己の力量を";
		mes "正確に把握することだ。";
		next;
		mes "[エグノロリア]";
		mes "それができず、身の丈に合わない";
		mes "力を使い続ければ";
		mes "いつか自分自身の力に";
		mes "喰われてしまうだろう。";
		next;
		cutin "3rd_wl_queen05",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "死にたくなければ";
		mes "修練を怠らないことだ。";
		mes "フフフ……。";
		next;
		cutin "3rd_wl_queen05",255;
		mes "[インフォメーション]";
		mes "転職試験のクリア報酬";
		mes "ステータス・スキル一括リセット権が";
		mes "付与されました。";
		mes "クエストウィンドウで利用方法を";
		mes "確認できます。";
		close;
	default:
		cutin "3rd_wl_queen01",1;
		mes "[エグノロリア]";
		mes "……。";
		next;
		cutin "3rd_wl_queen01",255;
		mes "[イベイン]";
		mes "エグノロリア様は瞑想中です。";
		mes "お静かに願います。";
		close;
	}
	// case1～2続き
	if(@menu == 2) {
		cutin "3rd_wl_queen04",1;
		emotion 29;
		mes "[エグノロリア]";
		mes "……つまらない答えだけど";
		mes "それが懸命な判断というものね。";
		mes "所詮、人間とはその程度の存在。";
		mes "フフフ……。";
		set CHANGE_WL,2;
		close2;
		cutin "3rd_wl_queen04",255;
		warp "splendide.gat",200,100;
		end;
	}
	cutin "3rd_wl_queen02",1;
	emotion 1;
	mes "[エグノロリア]";
	mes "……本気で言っているの？";
	mes "それほど力を求めていると……？";
	next;
	cutin "3rd_wl_queen05",1;
	mes "[エグノロリア]";
	mes "……気に入ったわ。";
	mes "より強力な力を求める欲望こそが";
	mes "魂を美しく輝かせる。";
	next;
	mes "[エグノロリア]";
	mes "その前にそんな資格があるのか";
	mes "証明してもらわないとね。";
	next;
	cutin "3rd_wl_queen01",1;
	mes "[エグノロリア]";
	mes "……ユッブ。";
	next;
	cutin "war_y3",2;
	emotion 19,"小さな妖精#WL";
	mes "[小さい妖精]";
	mes "は、はいぃぃ！";
	next;
	cutin "3rd_wl_queen01",1;
	mes "[エグノロリア]";
	mes "話は聞いていたわね？";
	mes "この人間に、^FF0000虚無の石^000000を";
	mes "与えるように。";
	next;
	cutin "3rd_wl_queen04",1;
	mes "[エグノロリア]";
	mes "人間よ、そこの「バナナの皮」から";
	mes "話を聞きなさい。";
	mes "何をすればいいか教えてくれるから。";
	set CHANGE_WL,3;
	chgquest 104505,11106;
	close2;
	cutin "3rd_wl_queen04",255;
	end;
}

spl_in02.gat,77,107,5	script	小さな妖精#WL	446,{
	if(Job == Job_Warlock) {
		cutin "war_y4",2;
		emotion 2;
		mes "[ユッブ]";
		mes "ふっふ～ん！";
		mes "「魔力の部屋」は、このユッブ様が";
		mes "技術の粋を集めて作った";
		mes "一種の魔法道具なのさ。";
		next;
		mes "[ユッブ]";
		mes "部屋の中で倒したモンスターの魔力を";
		mes "魔法石の原石に収縮させて";
		mes "強力な魔法石を生成できるのさ！";
		mes "すごいだろ！";
		close2;
		cutin "war_y4",255;
		end;
	}
	switch(CHANGE_WL) {
	case 0:
	case 1:
		if(YGG_1QUE < 100) {	// 知恵の王の指輪クエスト
			cutin "war_y1",2;
			emotion 0;
			mes "[小さい妖精]";
			mes "Lhagam!!　Kighala!?";
			mes "JatgaWagmaula！";
			mes "Luatana　Notyazutawe";
			mes "Kizgatayue！";
			close2;
			cutin "war_y1",255;
			end;
		}
		cutin "war_y1",2;
		emotion 0;
		mes "[ユッブ]";
		mes "えっ!!　人間!?";
		mes "どうやって、ここに入ってきたんだ！";
		mes "ここは特殊な扉でしか";
		mes "入れないはずなのに！";
		close2;
		cutin "war_y1",255;
		end;
	case 2:
		cutin "war_y1",2;
		emotion 0;
		mes "[ユッブ]";
		mes "ああっ！　お前はこの前の！";
		next;
		mes "[ユッブ]";
		mes "お前のせいでどれだけ";
		mes "マスターに怒られたのか";
		mes "知ってるのかよ！";
		next;
		emotion 6;
		mes "[ユッブ]";
		mes "用が無いならか";
		mes "さっさと出て行ってくれよ！";
		next;
		if(select("出る","出ない") == 2) {
			emotion 32;
			mes "[ユッブ]";
			mes "ふんっ！";
			mes "だったら、好きにしろよ。";
			mes "どうせ、マスターに追い出されるに";
			mes "決まってるんだから！";
			close2;
			cutin "war_y1",255;
			end;
		}
		emotion 32;
		mes "[ユッブ]";
		mes "ふんっ！";
		mes "そうだ、それでいいんだ！";
		close2;
		cutin "war_y1",255;
		warp "splendide.gat",200,100;
		end;
	case 3:
		cutin "war_y3",2;
		emotion 23;
		mes "[ユッブ]";
		mes "「バナナの皮」だなんて……。";
		mes "朝から念入りでセッティングした";
		mes "自慢の髪型なのに！";
		next;
		cutin "3rd_wl_queen01",1;
		mes "[エグノロリア]";
		mes "うるさいっ！";
		mes "私はまた瞑想に入るから";
		mes "指示したことはやっておくように。";
		next;
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "ちぇ～。";
		next;
		mes "[ユッブ]";
		mes "……お前、ウォーロックに";
		mes "なりたいんだって？";
		next;
		emotion 32;
		mes "[ユッブ]";
		mes "このユッブ様が直々に";
		mes "ウォーロックになるための方法を";
		mes "教えてやるから、よく聞けよ！";
		next;
		mes "[ユッブ]";
		mes "そもそも人間の体じゃ";
		mes "ウォーロックの強大な魔力に";
		mes "耐えられないんだ。";
		next;
		mes "[ユッブ]";
		mes "強大な魔力に耐えるためには";
		mes "特別な宝石を身に着ける必要がある。";
		mes "その宝石があれば、ひ弱な人間の体でも";
		mes "魔力に耐えられるって寸法だ。";
		next;
		mes "[ユッブ]";
		mes "というわけで、これからお前に";
		mes "その宝石を作ってもらう。";
		mes "まずは材料集めからだ。";
		next;
		mes "[ユッブ]";
		mes "^FF0000輝く水晶^000000と";
		mes "^FF0000巨大なブラディウムの破片^000000を";
		mes "^0000FF1個ずつ集めてくるんだ。^000000";
		next;
		mes "[ユッブ]";
		mes "スプレンディッドフィールド　02にいる";
		mes "^FF0000魔力に酔ったモンスター^000000を";
		mes "倒せば落とすはずだ。";
		next;
		mes "[ユッブ]";
		mes "わかったか？";
		mes "それと、アクセサリーを貸してやる。";
		mes "^FF0000それを装備することで";
		mes "目的のアイテムが手に入るはずだ。^000000";
		next;
		cutin "war_y1",2;
		emotion 32;
		mes "[ユッブ]";
		mes "いいか、貸してやるだけだからな！";
		mes "大事にしている物だから";
		mes "後で絶対に返せよ！";
		next;
		mes "[ユッブ]";
		mes "もし、失くしたりしたら……";
		mes "ユッブ様の超絶魔法で";
		mes "ギッタンギッタンにしてやるからな！";
		next;
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "材料が集まったら";
		mes "オレの研究室に持って来い。";
		mes "材料を調合する機材があるからな。";
		next;
		mes "[ユッブ]";
		mes "^0000FF研究室は、前線基地 スプレンディッドの";
		mes "北西にある。^000000";
		mes "ここに持って来ても";
		mes "宝石は作れないから注意しろよ。";
		next;
		if(checkitemblank() < 2) {
			mes "[ユッブ]";
			mes "……っと、その前に";
			mes "所持してるアイテムの種類が";
			mes "多すぎるじゃないか。";
			next;
			mes "[ユッブ]";
			mes "先にアイテムの所持数を減らして";
			mes "来てくれよ。";
			mes "渡すものがあるんだから。";
			close2;
			cutin "war_y2",255;
			end;
		}
		mes "[ユッブ]";
		mes "^0000FFイベイン^000000に話しかければ";
		mes "外に送ってくれる。";
		mes "まあ、精々がんばれよ。";
		set CHANGE_WL,4;
		chgquest 11106,11107;
		getitem 2796,1;		// 魔力を秘めた石（スプレンディッド）
		getitem 2797,1;		// 魔力を秘めた石（マヌク）
		close2;
		cutin "war_y2",255;
		end;
	case 4:
		if(countitem(6151) > 0 && countitem(6152) > 0) {
			cutin "war_y2",2;
			mes "[ユッブ]";
			mes "言ってたアイテムを持ってきたのか？";
			mes "でも、ここじゃあ作業が出来ないから";
			mes "オレの研究室に持って来てくれよ。";
			next;
			mes "[ユッブ]";
			mes "^0000FF研究室は、前線基地 スプレンディッドの";
			mes "北西にあるからな。^000000";
			close2;
			cutin "war_y2",255;
			end;
		}
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "^FF0000輝く水晶^000000と";
		mes "^FF0000巨大なブラディウムの破片^000000を";
		mes "^0000FF1個ずつ集めてくるんだ。^000000";
		next;
		mes "[ユッブ]";
		mes "スプレンディッドフィールド　02にいる";
		mes "^FF0000魔力に酔ったモンスター^000000を";
		mes "倒せば落とすはずだ。";
		next;
		mes "[ユッブ]";
		mes "貸してやったアクセサリーを";
		mes "^FF0000装備することで";
		mes "目的のアイテムが手に入る。^000000";
		next;
		cutin "war_y1",2;
		emotion 32;
		mes "[ユッブ]";
		mes "いいか、貸してやるだけだからな！";
		mes "大事にしている物だから";
		mes "後で絶対に返せよ！";
		next;
		mes "[ユッブ]";
		mes "もし、失くしたりしたら……";
		mes "ユッブ様の超絶魔法で";
		mes "ギッタンギッタンにしてやるからな！";
		next;
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "材料が集まったら";
		mes "オレの研究室に持って来い。";
		mes "材料を調合する機材があるからな。";
		next;
		mes "[ユッブ]";
		mes "^0000FF研究室は、前線基地 スプレンディッドの";
		mes "北西にある。^000000";
		mes "ここに持って来ても";
		mes "宝石は作れないから注意しろよ。";
		close2;
		cutin "war_y2",255;
		end;
	case 5:
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "さっき作った宝石の原石は";
		mes "マスターに渡してある。";
		next;
		mes "[ユッブ]";
		mes "マスターに話しかけて";
		mes "次にどうしたらいいか聞くんだな。";
		close2;
		cutin "war_y2",255;
		end;
	default:
		cutin "war_y4",2;
		emotion 2;
		mes "[ユッブ]";
		mes "ふっふ～ん！";
		mes "「魔力の部屋」は、このユッブ様が";
		mes "技術の粋を集めて作った";
		mes "一種の魔法道具なのさ。";
		next;
		mes "[ユッブ]";
		mes "部屋の中で倒したモンスターの魔力を";
		mes "魔法石の原石に収縮させて";
		mes "強力な魔法石を生成できるのさ！";
		mes "すごいだろ！";
		close2;
		cutin "war_y4",255;
		end;
	}
}

spl_in02.gat,84,103,3	script	小さい妖精	439,{
	if(Job == Job_Warlock) {
		mes "[シェーズ]";
		mes "貴方から強力な魔法を感じます。";
		mes "ちょっとうらやましいです……。";
		mes "ふふっ。";
		next;
		mes "[シェーズ]";
		mes "強力な力を操るには";
		mes "それに応じた代価が必要です。";
		mes "過ちを犯さないように";
		mes "気をつけてください。";
		close;
	}
	switch(CHANGE_WL) {
	case 0:
	case 1:
		if(YGG_1QUE < 100) {	// 知恵の王の指輪クエスト
			mes "[小さい妖精]";
			mes "Magigwa　Grzl？";
			mes "Oagyzywl　SaiLa？";
			close;
		}
		// fall through
	case 2:
		mes "[シェーズ]";
		mes "なぜ人間がここに？";
		mes "……いったい何の用でしょうか？";
		close;
	case 6:
		mes "[シェーズ]";
		mes "これからやってもらうことを";
		mes "説明します。";
		next;
		mes "[シェーズ]";
		mes "今から「魔力の部屋」と呼ばれる";
		mes "部屋に入ってもらい";
		mes "ユッブに作ってもらった原石に";
		mes "魔力を込める作業を行います。";
		next;
		mes "[シェーズ]";
		mes "難しく考える必要はありません。";
		mes "貴方は「魔力の部屋」の中に現れる";
		mes "モンスターを倒すだけです。";
		next;
		mes "[シェーズ]";
		mes "「魔力の部屋」でモンスターを倒すと";
		mes "倒したモンスターの魔力が収縮され";
		mes "魔法石の原石に魔力が宿るのです。";
		next;
		mes "[シェーズ]";
		mes "ただし、時間を空けずに魔力を";
		mes "収縮させる必要があります。";
		mes "強いモンスターじゃ魔力量が多いので";
		mes "時間が少々空いても大丈夫ですが……";
		next;
		mes "[シェーズ]";
		mes "弱いモンスターは魔力量が少ないので";
		mes "間断なく倒さないと";
		mes "魔力がすぐに霧散してしまいます。";
		mes "注意してください。";
		next;
		if(checkitemblank() < 4) {
			mes "[シェーズ]";
			mes "お渡ししたいものがあるのですが";
			mes "所持しているアイテムの種類が";
			mes "多すぎるようです。";
			mes "アイテムの所持数を減らしてから";
			mes "もう一度来てください。";
			close;
		}
		if(MaxWeight - Weight < 1000) {
			mes "[シェーズ]";
			mes "お渡ししたいものがあるのですが";
			mes "所持しているアイテムの重量が";
			mes "重すぎるようです。";
			mes "アイテムの所持数を減らしてから";
			mes "もう一度来てください。";
			close;
		}
		mes "[シェーズ]";
		mes "それと^FF0000虹色のルビー^000000を";
		mes "4種お渡しします。";
		if(countitem(12384)) delitem 12384,countitem(12384);	// 虹色のルビー(水)
		if(countitem(12386)) delitem 12386,countitem(12386);	// 虹色のルビー(風)
		if(countitem(12387)) delitem 12387,countitem(12387);	// 虹色のルビー(地)
		if(countitem(12385)) delitem 12385,countitem(12385);	// 虹色のルビー(火)
		getitem 12384,5;	// 虹色のルビー(水)
		getitem 12386,5;	// 虹色のルビー(風)
		getitem 12387,5;	// 虹色のルビー(地)
		getitem 12385,5;	// 虹色のルビー(火)
		next;
		mes "[シェーズ]";
		mes "たルビーには、ウォーロックの魔法が";
		mes "込められています。";
		mes "^FF0000これから案内する";
		mes "部屋の中でしか使えません^000000が";
		mes "有効に使ってください。";
		next;
		mes "[シェーズ]";
		mes "それでは、「魔力の部屋」に";
		mes "ご案内します。";
		set CHANGE_WL,7;
		chgquest 11109,11110;
		close2;
		warp "job3_war01.gat",23,20;
		end;
	case 7:
		mes "[シェーズ]";
		mes "「魔力の部屋」でモンスターを倒すと";
		mes "倒したモンスターの魔力が収縮され";
		mes "魔法石の原石に魔力が宿るのです。";
		next;
		mes "[シェーズ]";
		mes "ただし、時間を空けずに魔力を";
		mes "収縮させる必要があります。";
		mes "強いモンスターじゃ魔力量が多いので";
		mes "時間が少々空いても大丈夫ですが……";
		next;
		mes "[シェーズ]";
		mes "弱いモンスターは魔力量が少ないので";
		mes "間断なく倒さないと";
		mes "魔力がすぐに霧散してしまいます。";
		mes "注意してください。";
		next;
		mes "[シェーズ]";
		mes "それでは、もう一度、挑戦ですね。";
		mes "虹色のルビーは再支給します。";
		next;
		if(checkitemblank() < 4) {
			mes "[シェーズ]";
			mes "おや？";
			mes "所持しているアイテムの種類が";
			mes "多すぎるようです。";
			mes "アイテムの所持数を減らしてから";
			mes "もう一度来てください。";
			close;
		}
		if(MaxWeight - Weight < 1000) {
			mes "[シェーズ]";
			mes "おや？";
			mes "所持しているアイテムの重量が";
			mes "重すぎるようです。";
			mes "アイテムの所持数を減らしてから";
			mes "もう一度来てください。";
			close;
		}
		if(countitem(12384)) delitem 12384,countitem(12384);	// 虹色のルビー(水)
		if(countitem(12386)) delitem 12386,countitem(12386);	// 虹色のルビー(風)
		if(countitem(12387)) delitem 12387,countitem(12387);	// 虹色のルビー(地)
		if(countitem(12385)) delitem 12385,countitem(12385);	// 虹色のルビー(火)
		getitem 12384,5;	// 虹色のルビー(水)
		getitem 12386,5;	// 虹色のルビー(風)
		getitem 12387,5;	// 虹色のルビー(地)
		getitem 12385,5;	// 虹色のルビー(火)
		close2;
		warp "job3_war01.gat",23,20;
		end;
	case 8:
		mes "[シェーズ]";
		mes "虚無の石の結晶化に成功するなんて";
		mes "凄いことですよ。";
		mes "正直、貴方の力を疑っていました。";
		mes "……ごめんなさい。";
		next;
		mes "[シェーズ]";
		mes "これで目的の宝石は作成できました。";
		mes "^0000FFマスターに報告してください。^000000";
		if(countitem(12384)) delitem 12384,countitem(12384);	// 虹色のルビー(水)
		if(countitem(12386)) delitem 12386,countitem(12386);	// 虹色のルビー(風)
		if(countitem(12387)) delitem 12387,countitem(12387);	// 虹色のルビー(地)
		if(countitem(12385)) delitem 12385,countitem(12385);	// 虹色のルビー(火)
		set CHANGE_WL,9;
		chgquest 11111,11112;
		close;
	case 9:
		mes "[シェーズ]";
		mes "目的の宝石は作成できました。";
		mes "^0000FFマスターに報告してください。^000000";
		close;
	default:
		mes "[シェーズ]";
		mes "貴方が話しかけるべき相手は";
		mes "私ではありませんよ。";
		close;
	}
}

spl_in02.gat,78,110,5	script	小さい妖精	437,{
	if(Job == Job_Warlock) {
		mes "[イベイン]";
		mes "マスターは瞑想中ですので";
		mes "お静かに願います。";
		next;
		if(select("外に出る","やめる") == 2) {
			mes "[イベイン]";
			mes "……。";
			close;
		}
		mes "[イベイン]";
		mes "では、お気をつけて。";
		close2;
		warp "splendide.gat",200,100;
		end;
	}
	switch(CHANGE_WL) {
	case 0:
	case 1:
		if(YGG_1QUE < 100) {	// 知恵の王の指輪クエスト
			mes "[小さい妖精]";
			mes "……";
			mes "Dogi　YahlsaKa";
			mes "Yahwagu";
			mes "Cagaiw　QugaYua";
			next;
			if(select("外に出たい","やめる") == 2) {
				mes "[小さい妖精]";
				mes "……。";
				close;
			}
			mes "[小さい妖精]";
			mes "……？";
			close2;
			warp "splendide.gat",200,100;
			end;
		}
		mes "[イベイン]";
		mes "……。";
		mes "どうやって、ここに入ったのか";
		mes "分かりませんが";
		mes "出ていった方が身のためですよ。";
		break;
	case 2:
		mes "[イベイン]";
		mes "……。";
		mes "用が無いなら、出ていってください。";
		mes "外には、私がご案内しますので。";
		break;
	case 3:
		mes "[イベイン]";
		mes "……。";
		mes "私は「バナナの皮」ではありません。";
		break;
	default:
		mes "[イベイン]";
		mes "マスターは瞑想中ですので";
		mes "お静かに願います。";
		break;
	}
	next;
	if(select("外に出る","やめる") == 2) {
		mes "[イベイン]";
		mes "……。";
		close;
	}
	mes "[イベイン]";
	mes "では、お気をつけて。";
	close2;
	warp "splendide.gat",200,100;
	end;
}

//============================================================
// 魔道具作成
//------------------------------------------------------------
spl_in02.gat,60,231,5	script	小さい妖精	446,{
	if(Job == Job_Warlock) {
		// 本鯖は転職前クエスト未進行でもこのメッセージになる不具合あり
		cutin "war_y4",2;
		mes "[ユッブ]";
		mes "ああ、お前か。調子はどうだ？";
		mes "オレは、マスターからの命令で";
		mes "いろんな魔道具を作成してるんだ。";
		mes "かなり腕も上がったんだぜ？";
		next;
		emotion 2;
		mes "[ユッブ]";
		mes "……何だか魔法よりも";
		mes "魔道具作成の才能があるみたい。";
		next;
		cutin "war_y1",2;
		emotion 23;
		mes "[ユッブ]";
		mes "はっ！";
		mes "だとしても、オレは錬金術師に";
		mes "なりたいわけじゃないからな！";
		next;
		emotion 19;
		mes "[ユッブ]";
		mes "マスターに認めてもらう為に";
		mes "一生懸命に勉強してるんだからな！";
		close2;
		cutin "war_y1",255;
		end;
	}
	switch(CHANGE_WL) {
	case 0:
	case 1:
	case 2:
	case 3:
		if(YGG_1QUE < 100) {	// 知恵の王の指輪クエスト
			cutin "war_y1",2;
			mes "[小さい妖精]";
			mes "Xaga　Lritau？";
			mes "Puaga　Tattiba！";
			close2;
			cutin "war_y1",255;
			end;
		}
		cutin "war_y1",2;
		mes "[小さい妖精]";
		mes "なんだよ？";
		mes "研究の邪魔だから出てってくれよ！！";
		close2;
		cutin "war_y1",255;
		end;
	case 4:
		cutin "war_y2",2;
		mes "[ユッブ]";
		mes "言ってた材料は持って来たのか？";
		next;
		switch(select("材料を持ってきました","借りたアイテムを忘れました","何でもありません")) {
		case 1:
			if(countitem(6151) == 0 || countitem(6152) == 0) {
				cutin "war_y1",2;
				mes "[ユッブ]";
				mes "……持ってないじゃないか！";
				mes "オレは忙しいんだから";
				mes "手間取らすなよ！";
				next;
				cutin "war_y2",2;
				mes "[ユッブ]";
				mes "^FF0000輝く水晶^000000と";
				mes "^FF0000巨大なブラディウムの破片^000000を";
				mes "^0000FF1個ずつ集めてくるんだ。^000000";
				next;
				mes "[ユッブ]";
				mes "スプレンディッドフィールド　02にいる";
				mes "^FF0000魔力に酔ったモンスター^000000を";
				mes "倒せば落とすはずだ。";
				next;
				mes "[ユッブ]";
				mes "貸してやったアクセサリーを";
				mes "^FF0000装備することで";
				mes "目的のアイテムが手に入る。^000000";
				next;
				cutin "war_y1",2;
				emotion 32;
				mes "[ユッブ]";
				mes "いいか、貸してやるだけだからな！";
				mes "大事にしている物だから";
				mes "後で絶対に返せよ！";
				next;
				mes "[ユッブ]";
				mes "もし、失くしたりしたら……";
				mes "ユッブ様の超絶魔法で";
				mes "ギッタンギッタンにしてやるからな！";
				close2;
				cutin "war_y1",255;
				end;
			}
			if(equippeditem(2796) || equippeditem(2797)) {
				mes "[ユッブ]";
				mes "よ～し、それじゃあ";
				mes "先に貸してやったアクセサリーを";
				mes "返してくれ。";
				next;
				mes "[ユッブ]";
				mes "ん？　装備したままじゃないか。";
				mes "装備から外してくれよ～。";
				close2;
				cutin "war_y2",255;
				end;
			}
			// アクセサリー未所持時、未調査
			if(countitem(2796) == 0 || countitem(2797) == 0) {
				mes "[ユッブ]";
				mes "よ～し、それじゃあ";
				mes "先に貸してやったアクセサリーを";
				mes "返してくれ。";
				next;
				mes "[ユッブ]";
				mes "ん？　アクセサリーを";
				mes "持ってないようだけど……";
				mes "まさか、失くしたりしてないよな!?";
				mes "ちゃんと持ってきてくれ！";
				close2;
				cutin "war_y2",255;
				end;
			}
			mes "[ユッブ]";
			mes "うんうん、材料は全部揃ってるな！";
			mes "じゃあ、^0000FFマスターのところに";
			mes "戻ってくれ。^000000";
			mes "マスターのところには";
			mes "木の下に降りて";
			mes "北西の端から行けるぜ。";
			next;
			mes "[ユッブ]";
			mes "作業が終わったら";
			mes "オレもそっちに行くからさ。";
			set CHANGE_WL,5;
			chgquest 11107,11108;
			delitem 2796,countitem(2796);	// 魔力を秘めた石（スプレンディッド）
			delitem 2797,countitem(2797);	// 魔力を秘めた石（マヌク）
			delitem 6151,countitem(6151);	// 巨大なブラディウムの破片
			delitem 6152,countitem(6152);	// 輝く水晶
			close2;
			cutin "war_y2",255;
			end;
		case 2:
			cutin "war_y1",2;
			mes "[ユッブ]";
			mes "なに～！";
			mes "失くさないようにって";
			mes "あれ程言ったのに！";
			next;
			mes "[ユッブ]";
			mes "装備したままじゃないのか？";
			mes "鞄の隅に入ってないか？";
			mes "ちゃんと探してみてよ！";
			next;
			if(select("ありました","ありません") == 1) {
				mes "[ユッブ]";
				mes "驚かせるなよ！";
				mes "作るの本当に大変だったんだぞ！";
				close2;
				cutin "war_y1",255;
				end;
			}
			if((equippeditem(2796) || countitem(2796)) && (equippeditem(2797) || countitem(2797))) {
				if(equippeditem(2796) || equippeditem(2797)) {
					cutin "war_y2",2;
					emotion 9;
					mes "[ユッブ]";
					mes "オレの目にはあんたが";
					mes "装備しているように見えるけど？";
					close2;
					cutin "war_y2",255;
					end;
				}
				emotion 9;
				mes "[ユッブ]";
				mes "じゃあ、あんたが持っている";
				mes "それはなんなんだよ！";
				close2;
				cutin "war_y1",255;
				end;
			}
			// アクセサリー未所持時、未調査
			mes "[ユッブ]";
			mes "なんだって!?";
			mes "大事にしている物だって";
			mes "言ったじゃないか！";
			mes "それを失くしてしまうなんて……";
			next;
			mes "[ユッブ]";
			mes "仕方ないから代わりのものを作るのに";
			mes "^0000FFダイヤモンド３カラット^000000を^0000FF1つ^000000";
			mes "持ってきてくれ。";
			mes "それで手を打とうじゃないか。";
			if(countitem(732) < 1) {
				close2;
				cutin "war_y1",255;
				end;
			}
			next;
			if(select("持ってきました","少し待ってください") == 2) {
				mes "[ユッブ]";
				mes "大事なアクセサリーを失くしたんだから";
				mes "お前の誠意を見せてくれよ。";
				mes "^0000FFダイヤモンド３カラット^000000を^0000FF1つ^000000";
				mes "だからな！";
				close2;
				cutin "war_y1",255;
				end;
			}
			if(checkitemblank() < 2) {
				mes "[ユッブ]";
				mes "……っと、その前に";
				mes "所持してるアイテムの種類が";
				mes "多すぎるじゃないか。";
				next;
				mes "[ユッブ]";
				mes "先にアイテムの所持数を減らして";
				mes "来てくれよ。";
				mes "渡すものがあるんだから。";
				close2;
				cutin "war_y2",255;
				end;
			}
			mes "[ユッブ]";
			mes "確かに受け取ったぞ。";
			mes "ほら、新しいアクセサリーだ。";
			mes "もう失くすんじゃないぞ！";
			delitem 732,1;
			if(equippeditem(2796) == 0 && countitem(2796) == 0) {
				getitem 2796,1;		// 魔力を秘めた石（スプレンディッド）
			}
			if(equippeditem(2797) == 0 && countitem(2797) == 0) {
				getitem 2797,1;		// 魔力を秘めた石（マヌク）
			}
			close2;
			cutin "war_y2",255;
			end;
		case 3:
			cutin "war_y3",2;
			emotion 6;
			mes "[ユッブ]";
			mes "なんだよ～。";
			mes "忙しいから邪魔しないでくれよ～。";
			close2;
			cutin "war_y3",255;
			end;
		}
	case 5:
		mes "[ユッブ]";
		mes "じゃあ、^0000FFマスターのところに";
		mes "戻ってくれ。^000000";
		mes "マスターのところには";
		mes "木の下に降りて";
		mes "北西の端から行けるぜ。";
		next;
		mes "[ユッブ]";
		mes "作業が終わったら";
		mes "オレもそっちに行くからさ。";
		close2;
		cutin "war_y2",255;
		end;
	default:
		cutin "war_y4",2;
		mes "[ユッブ]";
		mes "ああ、お前か。調子はどうだ？";
		mes "オレは、マスターからの命令で";
		mes "いろんな魔道具を作成してるんだ。";
		mes "かなり腕も上がったんだぜ？";
		next;
		emotion 2;
		mes "[ユッブ]";
		mes "……何だか魔法よりも";
		mes "魔道具作成の才能があるみたい。";
		next;
		cutin "war_y1",2;
		emotion 23;
		mes "[ユッブ]";
		mes "はっ！";
		mes "だとしても、オレは錬金術師に";
		mes "なりたいわけじゃないからな！";
		next;
		emotion 19;
		mes "[ユッブ]";
		mes "マスターに認めてもらう為に";
		mes "一生懸命に勉強してるんだからな！";
		close2;
		cutin "war_y1",255;
		end;
	}
}

//============================================================
// 魔力の部屋
//------------------------------------------------------------
job3_war01.gat,22,22,7	script	シェーズ	439,{
	mes "[シェーズ]";
	mes "そこに立っている^0000FFイベイン^000000が";
	mes "魔力の部屋に送ってくれます。";
	mes "元の場所に戻りたい場合も";
	mes "イベインに話しかけてください。";
	close;
}

job3_war01.gat,29,25,0	script	イベイン#WL	437,{
	mes "[イベイン]";
	mes "「魔力の部屋」に入るのですか？";
	mes "待機室に入ったら送ってあげます。";
	next;
	mes "[イベイン]";
	mes "先に「魔力の部屋」を";
	mes "使っている者がいた場合は";
	mes "少々待ってもらいますが。";
	next;
	if(select("「魔力の部屋」に行きたい","外に出たい") == 1) {
		mes "[イベイン]";
		mes "では、待機室に入ってお待ち下さい。";
		close;
	}
	mes "[イベイン]";
	mes "それでは、元の場所に送りましょう。";
	close2;
	warp "spl_in02.gat",79,102;
	end;
OnInit:
	waitingroom "魔力の部屋",20,"イベイン#WL::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	donpcevent "魔力の部屋#WL1::OnStart";
	warpwaitingpc "job3_war02.gat",29,25;
	initnpctimer;
	end;
OnTimer10000:
	if(getmapusers("job3_war02.gat") > 0) {
		initnpctimer;
		end;
	}
	killmonster "job3_war02.gat","魔力の部屋#WL1::OnKilled";
	killmonster "job3_war02.gat","魔力の部屋#WL2::OnKilled";
	killmonster "job3_war02.gat","魔力の部屋#WL3::OnKilled";
	killmonster "job3_war02.gat","虚無の石#WL::OnKilled";
	stopnpctimer "魔力の部屋#WL1";
	stopnpctimer "魔力の部屋#WL2";
	stopnpctimer "魔力の部屋#WL3";
	stopnpctimer "虚無の石#WL";
	stopnpctimer;
	enablewaitingroomevent;
	end;
}

job3_war02.gat,0,0,0	script	魔力の部屋#WL1	-1,{
OnStart:
	// スタック座標で出るので座標を本鯖からずらす
	//monster "job3_war02.gat",23,32,"魔力に酔ったモンスター",2047,1,strnpcinfo(0) + "::OnKilled";
	//monster "job3_war02.gat",23,21,"魔力に酔ったモンスター",2048,1,strnpcinfo(0) + "::OnKilled";
	//monster "job3_war02.gat",34,32,"魔力に酔ったモンスター",2049,1,strnpcinfo(0) + "::OnKilled";
	//monster "job3_war02.gat",34,21,"魔力に酔ったモンスター",2050,1,strnpcinfo(0) + "::OnKilled";
	monster "job3_war02.gat",20,32,"魔力に酔ったモンスター",2047,1,strnpcinfo(0) + "::OnKilled";
	monster "job3_war02.gat",20,21,"魔力に酔ったモンスター",2048,1,strnpcinfo(0) + "::OnKilled";
	monster "job3_war02.gat",31,32,"魔力に酔ったモンスター",2049,1,strnpcinfo(0) + "::OnKilled";
	monster "job3_war02.gat",31,21,"魔力に酔ったモンスター",2050,1,strnpcinfo(0) + "::OnKilled";
	initnpctimer;
	end;
OnTimer2000:
	announce "魔力の部屋 : モンスターが出現しました",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer4000:
	announce "魔力の部屋 : 5分以内に全てのモンスターを倒してください",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer6000:
	announce "魔力の部屋 : 制限時間を越えると集めた魔力が霧散してしまいます",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer63000:
	announce "魔力の部屋 : 制限時間まで残り4分……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer123000:
	announce "魔力の部屋 : 制限時間まで残り3分……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer183000:
	announce "魔力の部屋 : 制限時間まで残り2分……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer243000:
	announce "魔力の部屋 : 制限時間まで残り1分……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer273000:
	announce "魔力の部屋 : 制限時間まで残り30秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer283000:
	announce "魔力の部屋 : 制限時間まで残り20秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer293000:
	announce "魔力の部屋 : 制限時間まで残り10秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer303000:
	announce "魔力の部屋 : 集めた魔力が霧散しました。失敗です。",0x9,0xFFFF00,0x190,12,0,0;
	killmonster "job3_war02.gat",strnpcinfo(0) + "::OnKilled";
	end;
OnTimer305000:
	mapwarp "job3_war02.gat","spl_in02.gat",79,102;
	stopnpctimer;
	end;
OnKilled:
	if(getmapmobs("job3_war02.gat",strnpcinfo(0) + "::OnKilled") == 0) {
		if(strnpcinfo(2) == "WL1") {
			announce "魔力の部屋 : 魔法石精製の第１段階が終了しました",0x9,0xFFFF00,0x190,12,0,0;
			donpcevent "魔力の部屋#WL2::OnStart";
		}
		else if(strnpcinfo(2) == "WL2") {
			announce "魔力の部屋 : 魔法石精製の第２段階が終了しました",0x9,0xFFFF00,0x190,12,0,0;
			donpcevent "魔力の部屋#WL3::OnStart";
		}
		stopnpctimer;
	}
	end;
}

job3_war02.gat,0,0,0	duplicate(魔力の部屋#WL1)	魔力の部屋#WL2	-1

job3_war02.gat,0,0,0	script	魔力の部屋#WL3	-1,{
OnStart:
	// スタック座標で出るので座標を本鯖からずらす
	//monster "job3_war02.gat",23,32,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	//monster "job3_war02.gat",23,21,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	//monster "job3_war02.gat",34,32,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	//monster "job3_war02.gat",34,21,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	monster "job3_war02.gat",20,32,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	monster "job3_war02.gat",20,21,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	monster "job3_war02.gat",31,32,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	monster "job3_war02.gat",31,21,"魔力に酔ったモンスター",1002,2,"魔力の部屋#WL3::OnKilled";
	initnpctimer;
	end;
OnTimer2000:
	announce "魔力の部屋 : モンスターが出現しました",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer4000:
	announce "魔力の部屋 : 1分以内に全てのモンスターを倒してください",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer6000:
	announce "魔力の部屋 : 制限時間を越えると集めた魔力が霧散してしまいます",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer33000:
	announce "魔力の部屋 : 制限時間まで残り30秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer43000:
	announce "魔力の部屋 : 制限時間まで残り20秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer53000:
	announce "魔力の部屋 : 制限時間まで残り10秒……",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer63000:
	announce "魔力の部屋 : 集めた魔力が霧散しました。失敗です。",0x9,0xFFFF00,0x190,12,0,0;
	killmonster "job3_war02.gat","魔力の部屋#WL3::OnKilled";
	end;
OnTimer65000:
	mapwarp "job3_war02.gat","spl_in02.gat",79,102;
	stopnpctimer;
	end;
OnKilled:
	if(getmapmobs("job3_war02.gat","魔力の部屋#WL3::OnKilled") == 0) {
		announce "魔力の部屋 : 虚無の石が実体化します",0x9,0xFFFF00,0x190,12,0,0;
		donpcevent "虚無の石#WL::OnStart";
		stopnpctimer;
	}
	end;
}

job3_war02.gat,0,0,0	script	虚無の石#WL	-1,{
OnStart:
	monster "job3_war02.gat",29,27,"虚無の石",2035,1,"虚無の石#WL::OnKilled";
	initnpctimer;
	end;
OnTimer2000:
	announce "虚無の石 : 虚無の石は魔力を吸収する性質を持っています",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer4000:
	announce "虚無の石 : 10分以内に虚無の石に魔力を与えて、結晶化させてください",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer303000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り5分……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer363000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り4分……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer423000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り3分……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer483000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り2分……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer543000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り1分……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer573000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り30秒……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer583000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り20秒……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer593000:
	announce "虚無の石 : 結晶化が出来なくなるまで残り10秒……。",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer603000:
	announce "虚無の石 : 虚無の石が結晶化できませんでした。失敗です。",0x9,0xFFFF00,0x190,12,0,0;
	killmonster "job3_war02.gat","虚無の石#WL::OnKilled";
	end;
OnTimer605000:
OnTimer616000:
	mapwarp "job3_war02.gat","spl_in02.gat",79,102;
	stopnpctimer;
	end;
OnKilled:
	announce "虚無の石 : 虚無の石を精製するための魔力が集まりました",0x9,0xFFFF00,0x190,12,0,0;
	if(CHANGE_WL == 7) {
		set CHANGE_WL,8;
		chgquest 11110,11111;
	}
	setnpctimer 610000;
	end;
}
