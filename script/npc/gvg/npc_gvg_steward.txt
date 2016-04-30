//=========================================================================
// 執事一括ファンクション
//	callfunc "StewardMain","AgitCode",MasterRoomX,MasterRoomY;
//
// ■ parse終了処理
//	内部で全てclose,endしているが、念のため呼び出し後はendを入れる
//
// ■ function
//	「ガーディアン設置」の場合は function "GuardianCall"を、
//	「アジトを放棄する」の場合は function "AgitGiveUp" を呼び出す(npc_gvg_monster.txt)
//
// 　※ NPC名はstrnpcinfo()、NPCの居るMAP名はgetmapxy() を使って自前で取得
//-------------------------------------------------------------------------

function	script	StewardMain	{
	//挨拶部分
	function StewardSpeech {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
		set '@gid,getcastledata('@map$,1);
		if('@gid <= 0) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "私は運命に導かれるまま、";
			mes "私の主人になる方を待っております。";
			mes "勇気ある方は、一度ご自分の運命を";
			mes "お試しになってはいかがでしょう。";
			close;
		}
		if(getcharid(0) != getguildmasterid('@gid)) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "あなた方がいくら脅そうとも、";
			mes "私は私のマスターである";
			mes "^ff0000" +getguildmaster('@gid)+ "^000000様にのみ";
			mes "お仕えする身である。";
			mes "ガーディアンたちはどこか！";
			mes "早くこの無礼な者等を追放しなさい！";
			close;
		}
		mes "[執事"+strnpcinfo(0)+"]";
		mes "お帰りなさいませ、^ff0000" +strcharinfo(0)+ "^000000 様。";
		mes "何なりとお申し付けくださいませ。";
		next;
		return;
	}

	//砦の状態を表示
	function StewardConf {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";
		mes "砦の状態をご報告します。";
		mes " ";
		mes "^0000ff現在の商業発展値は" +getcastledata('@map$,2)+ " です。";
		if(getcastledata('@map$,4) != 0)
			mes "- 1日以内に " +getcastledata('@map$,4)+ "の投資をしました。";
		mes "現在の防御値は" +getcastledata('@map$,3)+ " です。^000000";
		if(getcastledata('@map$,5) != 0)
			mes "^0000ff- 1日以内に " +getcastledata('@map$,5)+ "の投資をしました。^000000";
		mes " ";
		mes "以上です。";
		return;
	}

	//商業発展に投資
	function StewardEco {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";
		mes "商業発展値を高めれば、";
		mes "ギルドで生産される物流品の数が";
		mes "増えますので、先々のために";
		mes "投資をされるのもよろしいでしょう。";
		next;
		mes "[執事"+strnpcinfo(0)+"]";
		mes "通常一日に一回のみ投資可能ですが、";
		mes "追加金額を払うことにより";
		mes "2回目の投資も可能となります。";
		next;
		set '@count,getcastledata('@map$,4);
		if('@count == 2) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "^ff0000しかし、今日はすでに2回の";
			mes "投資をしたので、これ以上の投資は";
			mes "できません。";
			mes "^000000ますますのご発展を";
			mes "期待しております。";
			close;
		}
		set '@val,getcastledata('@map$,2);
		if('@val == 100) {	//未調査
			mes "[執事"+strnpcinfo(0)+"]";
			mes "^ff0000商業発展値は";
			mes "現在最大値となっております。";
			mes "今は投資する必要がありません。^000000";
		 	close;
		}
		set '@tmp,('@val-'@count)/5;
		set '@price,5000*(1+(1+'@tmp)*'@tmp/2)*(1+3*'@count);
		switch('@count) {
		case 0:
			mes "[執事"+strnpcinfo(0)+"]";
			mes "現在必要な投資金は";
			mes "^ff0000" +'@price+ "^000000 Zenyです。";
			mes "投資致しますか？";
			break;
		case 1:
			mes "[執事"+strnpcinfo(0)+"]";
			mes "現在1回投資なさってますが、";
			mes "追加投資なさいますか？";
			mes "その場合は ^ff0000" +'@price+ "^000000 Zenyが";
			mes "必要となります。";
			break;
		}
		next;
		if(select("商業発展に投資する","取り消す")==2) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "かしこまりました。";
			mes "焦る必要はございません。";
			mes "またいつでもお声をかけてください。";
			close;
		}
		if(Zeny < '@price) {	//未調査
			mes "[執事"+strnpcinfo(0)+"]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			close;
		}
		set Zeny,Zeny-'@price;
		setcastledata '@map$,4,'@count+1;
		mes "[執事"+strnpcinfo(0)+"]";
		mes "無事に投資できました！";
		mes "今後がますます楽しみですね。";
		mes "明日から発展値が上がるでしょう。";
		return;
	}

	//砦の防衛に投資
	function StewardDef {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";
		mes "防衛値を高めれば、";
		mes "ガーディアンとエンペリウムの";
		mes "耐久度が向上します。";
		mes "先々の戦闘に備え、";
		mes "強化しておくのが賢明かと思われます。";
		next;
		mes "[執事"+strnpcinfo(0)+"]";
		mes "通常一日に一回のみ投資可能ですが、";
		mes "追加金額を払うことにより";
		mes "2回目の投資も可能となります。";
		next;
		set '@count,getcastledata('@map$,5);
		if('@count == 2) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "^ff0000しかし、今日はすでに2回の";
			mes "投資をしたので、これ以上の投資は";
			mes "できません。";
			mes "^000000ますますのご発展を";
			mes "期待しております。";
			close;
		}
		set '@val,getcastledata('@map$,3);
		if('@val == 100) {	//未調査
			mes "[執事"+strnpcinfo(0)+"]";
			mes "^ff0000防衛投資値は現在100%です。";
			mes "今は投資する必要がありません。^000000";
			close;
		}
		set '@tmp,('@val-'@count)/5;
		set '@price,10000*(1+(1+'@tmp)*'@tmp/2)*(1+3*'@count);
		switch('@count) {
		case 0:
			mes "[執事"+strnpcinfo(0)+"]";
			mes "現在必要な投資金は";
			mes "^ff0000" +'@price+ "^000000 Zenyです。";
			mes "投資致しますか？";
			break;
		case 1:
			mes "[執事"+strnpcinfo(0)+"]";
			mes "現在1回投資なさってますが、";
			mes "追加投資なさいますか？";
			mes "その場合は ^ff0000" +'@price+ "^000000 Zenyが";
			mes "必要となります。";
			break;
		}
		next;
		if(select("防衛に投資する","取り消し")==2) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "かしこまりました。";
			mes "焦る必要はございません。";
			mes "またいつでもお声をかけてください。";
			close;
		}
		if(Zeny < '@price) {	//未調査
			mes "[執事"+strnpcinfo(0)+"]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			close;
		}
		set Zeny,Zeny-'@price;
		setcastledata '@map$,5,'@count+1;
		mes "[執事"+strnpcinfo(0)+"]";
		mes "無事に投資できました！";
		mes "今後がますます楽しみですね。";
		mes "明日から防衛値が上がるでしょう。";
		return;
	}

	//ガーディアン設置
	function StewardGuard {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";
		mes "ガーディアンを設置しますか？";
		mes "ガーディアンは私たちの砦を護る";
		mes "守護者となります。";
		mes "設置するガーディアンを";
		mes "選択してください。";
		next;
		//実際のMenu(B5参考)
		//menu 	"アーチャーガーディアン - 設置できます",L_MENU_1,"アーチャーガーディアン - 設置できます",L_MENU_2,
		//	"ソルジャーガーディアン - 設置できます",L_MENU_3,"ソルジャーガーディアン - 設置できます",L_MENU_4,
		//	"ナイトガーディアン - 設置できます",L_MENU_5,"ソルジャーガーディアン - 設置できます",L_MENU_6,
		//	"ナイトガーディアン - 設置できます",L_MENU_7,"マスターガーディアン - 設置できません (31214 / 31214)",L_MENU_8;
		//
		//設置できるか出来ないかの表示と、居た場合HPが表示される。
		//また、居た場合でも設置動作可能であり、その場合HPを回復させることが出来る。
		set '@ret,select("Gurdian 1","Gurdian 2","Gurdian 3","Gurdian 4","Gurdian 5","Gurdian 6","Gurdian 7","Gurdian 8")+9;
		if(getcastledata('@map$,'@ret)) {
			mes "[執事"+strnpcinfo(0)+"]";	//未調査
			mes "マスター！";
			mes "既にガーディアンが設置されています。";
			mes " ";
			mes "ガーディアン設置が取り消されました。";
			close;
		}
		mes "[執事"+strnpcinfo(0)+"]";
		mes "選択したガーディアンを";
		mes "本当に設置しますか？設置には";
		mes "^ff000010000^000000Zenyが必要です。";
		next;
		if(select("設置する","やめる")==2) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "かしこまりました。";
			mes "資金に余裕ができた時は、";
			mes "ぜひ設置されることを";
			mes "お勧め致します。";
			close;
		}
		if(getgdskilllv(getcharid(2),10002) == 0) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "マスター…ガーディアン設置に";
			mes "必要な研究知識が不足しています。";
			mes "ガーディアン設置に関する知識を";
			mes "得るためには、ギルドスキルの";
			mes "^ff0000ガーディアン製作研究^000000を";
			mes "習得しなければなりません。";
			close;
		}
		if(Zeny < 10000) {	//未調査
			mes "[執事"+strnpcinfo(0)+"]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			close;
		}
		set Zeny,Zeny-10000;
		setcastledata '@map$,'@ret,1;
		callfunc "GuardianCall",getarg(0),'@ret,1;	//ガーディアン召喚(npc_gvg_monster.txt)
		return;
	}

	//カプラとの契約・解雇
	function StewardKafra {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		if(getcastledata('@map$,9)==0) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "カプラ本社との契約をして、";
			mes "砦内にカプラ職員を雇いますか？";
			mes "雇用には^ff000010000^000000Zenyが必要ですが…";
			next;
			if(select("雇う","取り消す")==2) {
				mes "[執事"+strnpcinfo(0)+"]";
				mes "かしこまりました。";
				mes "しかし、ギルド員のためにも";
				mes "利便性の向上を忘れては";
				mes "なりません。";
				close;
			}
			if(getgdskilllv(getcharid(2),10001) == 0) {
				mes "[執事"+strnpcinfo(0)+"]";
				mes "マスター…まだカプラ本社との";
				mes "契約が結ばれていません。";
				mes "契約を締結しなければ、";
				mes "カプラ職員を雇うことができません。";
				next;
				mes "[執事"+strnpcinfo(0)+"]";
				mes "カプラ本社との契約をお望みなら、";
				mes "ギルドスキルの";
				mes " ^ff0000カプラ契約^000000 スキルを";
				mes "習得しなければなりません。";
				close;
			}
			if(Zeny < 10000) {	//未調査
				mes "[執事"+strnpcinfo(0)+"]";
				mes "マスター！お金が足りませんよ！";
				close;
			}
			set Zeny,Zeny-10000;
			enablenpc "AgitKafra_"+getarg(0);	//"AgitCode"を使って呼び出すNPC名を合成
			setcastledata '@map$,9,1;
			mes "[執事"+strnpcinfo(0)+"]";
			mes "カプラとの契約が完了しました";
			next;
			cutin "kafra_01",2;
			mes "[カプラ職員]";
			mes "初めまして、";
			mes "カプラディフォルテと申します。";
			mes "最善を尽くしますので宜しくおねがいします！";
			next;
			cutin "kafra_01",255;
			mes "[執事"+strnpcinfo(0)+"]";
			mes "ギルドベースでカプラとの契約を維持するために";
			mes "毎月Zenyを払わなければなりません。";
			mes "(未実装)";
		}
		else {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "カプラ職員との契約を破棄しますか？";
			next;
			if(select("解雇する","キャンセル")==2) {
				mes "[執事"+strnpcinfo(0)+"]";
				mes "わかりました。";
				close;
			}
			cutin "kafra_01",2;
			mes "[カプラ職員]";
			mes "私…何か間違っていましたか？";
			mes "これからは気をつけますから…";
			mes "許してはもらえませんか…";
			next;
			if(select("解雇する","キャンセル")==2) {
				mes "[カプラ職員]";
				mes "ありがとうございます。";
				mes "全力を尽くして執務につきます！";
				close2;
				cutin "kafra_01",255;
				end;
			}
			mes "[カプラ職員]";
			mes "ああ、解雇なさるんですね…";
			next;
			disablenpc "AgitKafra_"+getarg(0);
			setcastledata '@map$,9,0;
			cutin "kafra_01",255;
			mes "[執事"+strnpcinfo(0)+"]";
			mes "…";
			mes "カプラとの契約が破棄されました。";
		}
		return;
	}

	//マスターの部屋に入る
	function StewardRoom {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";
		mes "私たちの貴重な生産品の数々が";
		mes "蓄えられている部屋に";
		mes "入られるのですね？";
		mes "そこは、マスターにのみ";
		mes "入室が許された部屋でございます。";
		next;
		if(select("マスターの部屋に入る","取り消す")==1) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "それではご案内致します。";
			mes "私についていらしてください。";
			mes "帰って来る時は隠しスイッチを";
			mes "操作すれば帰れます。";
			close2;
			warp '@map$,getarg(1),getarg(2);
			end;
		}
		mes "[執事"+strnpcinfo(0)+"]";
		mes "生産品は一日に一回生産可能ですが、";
		mes "ある程度まで貯蓄されるとそれ以上";
		mes "生産されなくなります。ですから、";
		mes "私達のギルドの発展のためにも";
		mes "適度に取り出さなければなりません。";
		return;
	}

	//アジトを放棄する
	function StewardGiveup {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
		mes "[執事"+strnpcinfo(0)+"]";	//未調査？
		mes "マスター！";
		mes "アジトを放棄するんですか！？";
		mes " ";
		mes "どうか考え直してください、マスター！";
		next;
		if(select("アジトを放棄する","キャンセル")==1) {
			mes "[執事"+strnpcinfo(0)+"]";
			mes "マスター！";
			mes "どうかもう一度考え直してください…";
			mes "どうか、、お願い!!!!!!!!";
			next;
			if(select("やめる","アジトを放棄する")==2) {
				mes "[執事"+strnpcinfo(0)+"]";
				mes "マスター!!…";
				mes "…い……やだ……ぁ……";
				close2;
				announce "砦 [" +getcastlename('@map$)+ "]を [" +getguildname(getcharid(2))+ "] ギルドが放棄しました。",0x20;
				callfunc "AgitGiveUp",getarg(0);	//アジト放棄処理(npc_gvg_exe.txt)
				end;
			}
		}
		mes "[執事"+strnpcinfo(0)+"]";
		mes "イエッサー！マスター^^!";
		mes "もう、そんな冗談よしてくださいよ^^.";
		return;
	}

	//ここからmain
	StewardSpeech;
	switch (select("砦の状態を表示","商業発展に投資","砦の防衛に投資","ガーディアン設置","カプラとの契約 / 解雇","マスターの部屋に入る","アジトを放棄する")) {
		case 1:
			StewardConf;
			close;
		case 2:
			StewardEco;
			close;
		case 3:
			StewardDef;
			close;
		case 4:
			StewardGuard getarg(0);
			close;
		case 5:
			StewardKafra getarg(0);
			close;
		case 6:
			StewardRoom 0,getarg(1),getarg(2);
			close;
		case 7:
			StewardGiveup getarg(0);
			close;
	}
	return;
}


//==========================================
// ルイーナ
//------------------------------------------
aldeg_cas01.gat,218,175,0	script	アルプレド	55,{
	callfunc "StewardMain","L1",113,223;
	end;
}

aldeg_cas02.gat,78,74,0		script	チェンチェンリ	55,{
	callfunc "StewardMain","L2",134,225;
	end;
}

aldeg_cas03.gat,110,118,0	script	ナザブ	55,{
	callfunc "StewardMain","L3",219,268;
	end;
}

aldeg_cas04.gat,67,116,0	script	ウィリオット	55,{
	callfunc "StewardMain","L4",79,14;
	end;
}

aldeg_cas05.gat,51,179,0	script	ブリムヘンセン	55,{
	callfunc "StewardMain","L5",68,13;
	end;
}

//==========================================
// ブリトニア
//------------------------------------------
gefg_cas01.gat,40,48,5		script	グナフチョ	55,{
	callfunc "StewardMain","B1",151,109;
	end;
}

gefg_cas02.gat,12,66,0		script	エスマーク	55,{
	callfunc "StewardMain","B2",137,113;
	end;
}

gefg_cas03.gat,106,23,3		script	ジャン	55,{
	callfunc "StewardMain","B3",267,287;
	end;
}

gefg_cas04.gat,73,46,3		script	ケルバーリ	55,{
	callfunc "StewardMain","B4",113,115;
	end;
}

gefg_cas05.gat,70,52,3		script	ビオル	55,{
	callfunc "StewardMain","B5",141,107;
	end;
}

//==========================================
// チュンリム
//------------------------------------------
payg_cas01.gat,120,58,4		script	グルナンディー	55,{
	callfunc "StewardMain","C1",287,5;
	end;
}

payg_cas02.gat,22,260,7		script	チェリオス	55,{
	callfunc "StewardMain","C2",141,141;
	end;
}

payg_cas03.gat,50,261,3		script	ケリオ	55,{
	callfunc "StewardMain","C3",155,165;
	end;
}

payg_cas04.gat,38,284,3		script	ディージェイ	55,{
	callfunc "StewardMain","C4",143,45;
	end;
}

payg_cas05.gat,277,249,3	script	ナザブ	55,{
	callfunc "StewardMain","C5",153,129;
	end;
}

//==========================================
// ヴァルキリーレルム
//------------------------------------------
prtg_cas01.gat,112,181,0	script	アブライ	55,{
	callfunc "StewardMain","V1",7,205;
	end;
}

prtg_cas02.gat,94,61,4		script	ルエ	55,{
	callfunc "StewardMain","V2",199,225;
	end;
}

prtg_cas03.gat,51,100,4		script	ステッキ	55,{
	callfunc "StewardMain","V3",185,129;
	end;
}

prtg_cas04.gat,259,265,4	script	バンドレッド	55,{
	callfunc "StewardMain","V4",267,159;
	end;
}

prtg_cas05.gat,36,37,4		script	レイノ	55,{
	callfunc "StewardMain","V5",273,175;
	end;
}
