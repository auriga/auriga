//= Auriga Script ==============================================================
// Ragnarok Online GvG Script	by Blaze
//==============================================================================

//============================================================
// 攻城戦の制御
//------------------------------------------------------------
-	script	#AgitConfig	-1,{
OnAgitInit:
//---------------攻城戦を開催する曜日の設定-------------------
// 攻城戦の開催曜日
// 無し = 0, 日 = +1, 月 = +2, 火 = +4, 水 = +8, 木 = +16, 金 = +32, 土 = +64
// 攻城戦を行う曜日を加算（攻城戦無しなら0）
// 毎日行なう場合は'weekdayを127にする
	set 'weekday,1;

//---------------攻城戦の開催時間の設定（全体）---------------
// 攻城戦の開催時間と終了時間（時単位）
// 24時の場合は「24」と記載（0ではダメ）
// 開始時間と終了時間を同じにするとその日は攻城戦を終了させない
	set 'st_time,20;
	set 'ed_time,22;

//---------------攻城戦の開催時間の設定（個別）---------------
// 曜日毎に攻城戦の開催時間と終了時間を設定する
// 有効にするにはコメントアウトを外す
// 無効時、全体の開催時間設定が優先される
	// 日曜
	//set 'st_time[1],20;
	//set 'ed_time[1],22;

	// 月曜
	//set 'st_time[2],20;
	//set 'ed_time[2],22;

	// 火曜
	//set 'st_time[3],20;
	//set 'ed_time[3],22;

	// 水曜
	//set 'st_time[4],20;
	//set 'ed_time[4],22;

	// 木曜
	//set 'st_time[5],20;
	//set 'ed_time[5],22;

	// 金曜
	//set 'st_time[6],20;
	//set 'ed_time[6],22;

	// 土曜
	//set 'st_time[7],20;
	//set 'ed_time[7],22;

//---------------サーバー再起動時、攻城戦の再開時間-----------
// サーバー起動時に攻城戦の開催時間内だった場合、
// 攻城戦を再開するまでの猶予時間（単位:msec、60000 = 60秒）
	sleep 1000;

//---------------攻城戦の設定ここまで-------------------------
OnMinute00:
	set '@day,gettime(4);
	set '@hour,gettime(3);
	if('weekday & (1<<'@day)) {
		if('st_time['@day+1] == 0 && 'ed_time['@day+1] == 0) {
			set '@st_time,'st_time;
			set '@ed_time,'ed_time;
		}
		else {
			set '@st_time,'st_time['@day+1];
			set '@ed_time,'ed_time['@day+1];
		}
		if('@st_time == '@ed_time || ('@hour >= '@st_time  && '@hour < '@ed_time)) {
			if(!agitcheck()) {
				debugmes "攻城戦開始 [ " +gettimestr("%H:%M",6)+ " ]";
				agitstart;
			}
		}
		else if(agitcheck()) {
			debugmes "攻城戦終了 [ " +gettimestr("%H:%M",6)+ " ]";
			agitend;
		}
	}
	else if(agitcheck()) {
		debugmes "攻城戦終了 [ " +gettimestr("%H:%M",6)+ " ]";
		agitend;
	}
	end;
}

//============================================================
// エンペリウム召喚
//	callfunc "AgitEmperium",EmperiumX,EmperiumY,StartFlag;
//------------------------------------------------------------
function	script	AgitEmperium	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	maprespawnguildid '@map$,getcastledata('@map$,1),2;
	callguardian '@map$,getarg(0),getarg(1),"--ja--",1288,1,strnpcinfo(0)+"::OnAgitBreak";
	if(getarg(2)) {		// 攻城戦開始処理か？
		gvgon '@map$;
		if(getcastledata('@map$,1))
			announce "砦 [" +getcastlename('@map$,0)+ "] の " +getcastlename('@map$,1)+ " を [" +getguildname(getcastledata('@map$,1))+ "] ギルドが占領しました",0x20;
		else
			donpcevent strnpcinfo(0)+"::OnAgitSummon";	//モンスター召喚
	}
	return;
}

//============================================================
// アジト占領
//	callfunc "AgitBreak","AgitCode";
//------------------------------------------------------------
function	script	AgitBreak	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	killmonsterall '@map$;
	set '@gid,getcharid(2);		//エンペリウム破壊者のGIDを取得
	if('@gid <= 0)
		return;

	// 砦情報の書き換え
	setcastledata '@map$,1,'@gid;
	for(set '@i,2; '@i<=17; set '@i,'@i+1) {
		if('@i==2 || '@i==3) {	// 商業値・防衛値
			set '@val,getcastledata('@map$,'@i)-5;
			setcastledata '@map$,'@i,('@val<1)? 1: '@val;
		}
		else
			setcastledata '@map$,'@i,0;
	}
	announce "エンペリウムが破壊されました",0x9,0x00ff00,0x2bc,10,0,40;
	sleep 7000;
	announce "砦 [" +getcastlename('@map$,0)+ "] の " +getcastlename('@map$,1)+ " を [" +getguildname(getcastledata('@map$,1))+ "] ギルドが占領しました",0x20;
	donpcevent "::OnFlagEmb_"+getarg(0);	//フラッグエンブレムの変更
	return;
}

//============================================================
// 攻城戦終了
//	callfunc "AgitEnd";
//------------------------------------------------------------
function	script	AgitEnd	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	maprespawnguildid '@map$,getcastledata('@map$,1),4;
	killmonster '@map$,strnpcinfo(0)+"::OnAgitBreak";	//エンペのみ抹殺
	gvgoff '@map$;
	if(getcastledata('@map$,1))
		announce "砦 [" +getcastlename('@map$,0)+ "] の " +getcastlename('@map$,1)+ " を [" +getguildname(getcastledata('@map$,1))+ "] ギルドが占領しました",0x20;
	return;
}

//============================================================
// アジト放棄
//	callfunc "AgitGiveUp","AgitCode";
//------------------------------------------------------------
function	script	AgitGiveUp	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	killmonsterall '@map$;
	hideonnpc "AgitKafra_"+getarg(0);
	setcastledata '@map$,1,0;
	for(set '@i,4; '@i<=17; set '@i,'@i+1) {
		setcastledata '@map$,'@i,0;
	}
	donpcevent "::OnFlagEmb_"+getarg(0);		//フラッグエンブレムの変更
	maprespawnguildid '@map$,0,7;
	if(agitcheck()) {
		donpcevent strnpcinfo(0)+"::OnAgitEliminate";	//エンペリウム召喚
		donpcevent strnpcinfo(0)+"::OnAgitSummon";	//モンスター召喚
	}
	return;
}

//============================================================
// 宝箱
//	callfunc "AgitTreasure",TBoxIDArray,TBoxXArray,TBoxYArray;
//------------------------------------------------------------
function	script	AgitTreasure	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー

	// 商業値
	set '@economy,getcastledata('@map$,2) + getcastledata('@map$,4);
	if(getcastledata('@map$,4)) {
		if(getgdskilllv(getcastledata('@map$,1),10014)) // 永久的な発展
			set '@economy,'@economy + rand(2);
	}
	set '@economy,('@economy > 100)? 100: '@economy;

	// 防衛値
	set '@defense,getcastledata('@map$,3) + getcastledata('@map$,5);
	set '@defense,('@defense > 100)? 100: '@defense;

	// 砦情報更新
	setcastledata '@map$,2,'@economy;
	setcastledata '@map$,3,'@defense;
	setcastledata '@map$,4,0;	// 商業投資回数リセット
	setcastledata '@map$,5,0;	// 防衛投資回数リセット

	// 宝箱
	killmonster '@map$,strnpcinfo(0)+"::OnKilled";
	set '@count,('@economy / 5) + 4;
	set '@max,getarraysize(getarg(0));
	copyarray '@id,getarg(0),'@max;
	copyarray '@x,getarg(1),'@count;
	copyarray '@y,getarg(2),'@count;
	for(set '@i,0; '@i < '@count; set '@i,'@i+1) {
		if('@x['@i] && '@y['@i])	// x座標,y座標が正しいかチェック
			monster '@map$,'@x['@i],'@y['@i],"--ja--",'@id['@i % '@max],1,strnpcinfo(0)+"::OnKilled";
	}
	return;
}

//============================================================
// ギルドフラッグ
//	callfunc "AgitEmblemFlag",Type,"WarpMap",WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitEmblemFlag	{
	set '@gid,getcastledata(getarg(1),1);
	if(getcharid(2) > 0 && getcharid(2) == '@gid) {
		mes "[ 声 ]";
		mes "勇者よ…";
		mes "君の地に帰るか？";
		next;
		if(select("砦に帰る","やめる") == 1) {
			// 移動前に再チェック
			set '@gid,getcastledata(getarg(1),1);
			if(getcharid(2) > 0 && getcharid(2) == '@gid)
				warp getarg(1),getarg(2),getarg(3);
		}
		return;
	}
	if(getarg(0) == 1) {
		mes "[ ルーンミッドガッツ王国領 ]";
		mes " ";
		mes "1.";
		mes "こちらはルーンミッドガッツ王国と";
		mes "シュバルツバルド共和国の協定により、";
	}
	else if(getarg(0) == 2) {
		mes "[シュバルツバルド共和国布告]";
		mes " ";
		mes "1.";
		mes "こちらは";
		mes "シュバルツバルド共和国令により、";
	}
	else if(getarg(0) == 3) {
		mes "[アルナベルツ教国布告]";
		mes " ";
		mes "1.";
		mes "こちらはアルナベルツ教国令により、";
	}
	else {
		mes "[ ルーンミッドガッツ王国領 ]";
		mes " ";
		mes "1.";
		mes "こちらはルーンミッドガッツ王国に";
		mes "よって";
	}
	if('@gid <= 0) {
		mes "正式所有者がないアジトであることを";
		mes "公表する。";
		next;
		mes " ";
		mes "2.";
		mes "こちらを守っている凄じい";
		mes "試練に勝って、エンペリウムを";
		mes "破壊する勇者には国王が";
		mes "認定するアジト所有権が附与される";
		return;
	}
	mes "ギルド ^ff0000 " +getguildname('@gid)+ " ^000000の";
	mes "所有であることを認められている。";
	next;
	mes " ";
	mes "2.";
	mes "^ff0000 " +getguildname('@gid)+ " ^000000 のマスターは";
	mes "^ff0000 " +getguildmaster('@gid)+ " ^000000である。";
	mes "これに異議のある者は、剣を取り";
	mes "力を以って名誉を勝ち取りなさい。";
	return;
}

//============================================================
// カプラ職員
//	callfunc "AgitKafra",MapCode;
//------------------------------------------------------------
function	script	AgitKafra	{
	cutin "kafra_01",2;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(2) != '@gid) {
		mes "[カプラ職員]";
		mes "私は、ギルド";
		mes "^ff0000" + getguildname('@gid) + "^000000";
		mes "の皆様にだけお仕えするように";
		mes "契約されております。";
		mes "他のカプラサービスを";
		mes "ご利用くださいませ。";
		close2;
		cutin "kafra_01",255;
		return;
	}
	mes "[カプラ職員]";
	mes "いらっしゃいませ^ff0000" +getguildname('@gid)+ "^000000の皆さん";
	mes "カプラサービスは";
	mes "いつも皆様のそばにいます。";
	next;
	set '@code,getarg(0);
	set '@price,200;
	callfunc "KafraMain",3,0x4e,0,0,0,0,0,0,40,800,'@code,'@price;
	return;
}

//============================================================
// 執事
//	callfunc "AgitSteward","AgitCode",GuardianIDArray,GuardianXArray,GuardianYArray,MasterRoomX,MasterRoomY;
//------------------------------------------------------------
function	script	AgitSteward	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	set '@name$,"執事" +(getarg(1)? strnpcinfo(0): "");	//SEでないなら固有名
	if('@gid <= 0) {
		mes "[" +'@name$+ "]";
		mes "私は運命に導かれるまま、";
		mes "私の主人になる方を待っております。";
		mes "勇気ある方は、一度ご自分の運命を";
		mes "お試しになってはいかがでしょう。";
		return;
	}
	if(getcharid(0) != getguildmasterid('@gid)) {
		mes "[" +'@name$+ "]";
		mes "あなた方がいくら脅そうとも、";
		mes "私は私のマスターである";
		mes "^ff0000" +getguildmaster('@gid)+ "^000000様にのみ";
		mes "お仕えする身である。";
		mes "ガーディアンたちはどこか！";
		mes "早くこの無礼な者等を追放しなさい！";
		return;
	}
	mes "[" +'@name$+ "]";
	mes "お帰りなさいませ、^ff0000" +strcharinfo(0)+ "^000000 様。";
	mes "何なりとお申し付けくださいませ。";
	next;
	set '@tmp$,getarg(1)? "ガーディアン設置": "";	//SEはガーディアン設置メニューを表示しない
	switch(select("砦の状態を表示","商業発展に投資","砦の防衛に投資",'@tmp$,"カプラとの契約 / 解雇","マスターの部屋に入る")) {
	case 1:		// 砦の状態を表示
		mes "[" +'@name$+ "]";
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
		break;
	case 2:		// 商業発展に投資
		mes "[" +'@name$+ "]";
		mes "商業発展値を高めれば、";
		mes "ギルドで生産される物流品の数が";
		mes "増えますので、先々のために";
		mes "投資をされるのもよろしいでしょう。";
		next;
		mes "[" +'@name$+ "]";
		mes "通常一日に一回のみ投資可能ですが、";
		mes "追加金額を払うことにより";
		mes "2回目の投資も可能となります。";
		next;
		set '@count,getcastledata('@map$,4);
		if('@count == 2) {
			mes "[" +'@name$+ "]";
			mes "^ff0000しかし、今日はすでに2回の";
			mes "投資をしたので、これ以上の投資は";
			mes "できません。";
			mes "^000000ますますのご発展を";
			mes "期待しております。";
			break;
		}
		set '@val,getcastledata('@map$,2);
		if('@val >= 100) {	//未調査
			mes "[" +'@name$+ "]";
			mes "^ff0000商業発展値は";
			mes "現在最大値となっております。";
			mes "今は投資する必要がありません。^000000";
		 	break;
		}
		set '@tmp,('@val-'@count)/5;
		set '@price,5000*(1+(1+'@tmp)*'@tmp/2)*(1+3*'@count);
		switch('@count) {
		case 0:
			mes "[" +'@name$+ "]";
			mes "現在必要な投資金は";
			mes "^ff0000" +'@price+ "^000000 Zenyです。";
			mes "投資致しますか？";
			break;
		case 1:
			mes "[" +'@name$+ "]";
			mes "現在1回投資なさってますが、";
			mes "追加投資なさいますか？";
			mes "その場合は ^ff0000" +'@price+ "^000000 Zenyが";
			mes "必要となります。";
			break;
		}
		next;
		if(select("商業発展に投資する","取り消す") == 2) {
			mes "[" +'@name$+ "]";
			mes "かしこまりました。";
			mes "焦る必要はございません。";
			mes "またいつでもお声をかけてください。";
			break;
		}
		if(Zeny < '@price) {	//未調査
			mes "[" +'@name$+ "]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			break;
		}
		set Zeny,Zeny-'@price;
		setcastledata '@map$,4,'@count+1;
		mes "[" +'@name$+ "]";
		mes "無事に投資できました！";
		mes "今後がますます楽しみですね。";
		mes "明日から発展値が上がるでしょう。";
		break;
	case 3:		// 砦の防衛に投資
		mes "[" +'@name$+ "]";
		mes "防衛値を高めれば、";
		mes "ガーディアンとエンペリウムの";
		mes "耐久度が向上します。";
		mes "先々の戦闘に備え、";
		mes "強化しておくのが賢明かと思われます。";
		next;
		mes "[" +'@name$+ "]";
		mes "通常一日に一回のみ投資可能ですが、";
		mes "追加金額を払うことにより";
		mes "2回目の投資も可能となります。";
		next;
		set '@count,getcastledata('@map$,5);
		if('@count == 2) {
			mes "[" +'@name$+ "]";
			mes "^ff0000しかし、今日はすでに2回の";
			mes "投資をしたので、これ以上の投資は";
			mes "できません。";
			mes "^000000ますますのご発展を";
			mes "期待しております。";
			break;
		}
		set '@val,getcastledata('@map$,3);
		if('@val >= 100) {	//未調査
			mes "[" +'@name$+ "]";
			mes "^ff0000防衛投資値は現在100%です。";
			mes "今は投資する必要がありません。^000000";
			break;
		}
		set '@tmp,('@val-'@count)/5;
		set '@price,10000*(1+(1+'@tmp)*'@tmp/2)*(1+3*'@count);
		if('@count) {
			mes "[" +'@name$+ "]";
			mes "現在1回投資なさってますが、";
			mes "追加投資なさいますか？";
			mes "その場合は ^ff0000" +'@price+ "^000000 Zenyが";
			mes "必要となります。";
		}
		else {
			mes "[" +'@name$+ "]";
			mes "現在必要な投資金は";
			mes "^ff0000" +'@price+ "^000000 Zenyです。";
			mes "投資致しますか？";
		}
		next;
		if(select("防衛に投資する","取り消し") == 2) {
			mes "[" +'@name$+ "]";
			mes "かしこまりました。";
			mes "焦る必要はございません。";
			mes "またいつでもお声をかけてください。";
			break;
		}
		if(Zeny < '@price) {	//未調査
			mes "[" +'@name$+ "]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			break;
		}
		set Zeny,Zeny-'@price;
		setcastledata '@map$,5,'@count+1;
		mes "[" +'@name$+ "]";
		mes "無事に投資できました！";
		mes "今後がますます楽しみですね。";
		mes "明日から防衛値が上がるでしょう。";
		break;
	case 4:		// ガーディアン設置
		set '@max,getarraysize(getarg(1));
		copyarray '@id,getarg(1),'@max;
		mes "[" +'@name$+ "]";
		mes "ガーディアンを設置しますか？";
		mes "ガーディアンは私たちの砦を護る";
		mes "守護者となります。";
		mes "設置するガーディアンを";
		mes "選択してください。";
		next;
		for(set '@i,0; '@i < '@max; set '@i,'@i+1) {
			set '@name$,getmobname('@id['@i]);
			if(getcastledata('@map$,'@i+10) == 0)
				set '@stat$,"設置できます";
			else
				//表示範囲からはみ出るので表示をアレンジ
				//set '@stat$,"設置できません (" +getguardianinfo('@map$,'@i+1,3)+ " / " +getguardianinfo('@map$,'@i+1,4)+ ")";
				set '@stat$,"(" +getguardianinfo('@map$,'@i+1,3)+ " / " +getguardianinfo('@map$,'@i+1,4)+ ")";
			set '@tmp$['@i],'@name$ + " - " + '@stat$;
		}
		set '@ret,select(printarray('@tmp$))+9;
		mes "[" +'@name$+ "]";
		mes "選択したガーディアンを";
		mes "本当に設置しますか？設置には";
		mes "^ff000010000^000000Zenyが必要です。";
		next;
		if(select("設置する","やめる") == 2) {
			mes "[" +'@name$+ "]";
			mes "かしこまりました。";
			mes "資金に余裕ができた時は、";
			mes "ぜひ設置されることを";
			mes "お勧め致します。";
			break;
		}
		if(getgdskilllv(getcharid(2),10002) == 0) {
			mes "[" +'@name$+ "]";
			mes "マスター…ガーディアン設置に";
			mes "必要な研究知識が不足しています。";
			mes "ガーディアン設置に関する知識を";
			mes "得るためには、ギルドスキルの";
			mes "^ff0000ガーディアン製作研究^000000を";
			mes "習得しなければなりません。";
			break;
		}
		if(getcastledata('@map$,'@ret)) {
			mes "[" +'@name$+ "]";	//未調査
			mes "マスター！";
			mes "既にガーディアンが設置されています。";
			mes " ";
			mes "ガーディアン設置が取り消されました。";
			break;
		}
		if(Zeny < 10000) {	//未調査
			mes "[" +'@name$+ "]";
			mes "マスター！";
			mes "投資に必要なお金がありません。";
			mes "投資を取り消しました。";
			break;
		}
		set Zeny,Zeny-10000;
		copyarray '@x,getarg(2),'@max;
		copyarray '@y,getarg(3),'@max;
		set '@ret,'@ret-10;
		callguardian '@map$,'@x['@ret],'@y['@ret],"--ja--",'@id['@ret],1,"",'@ret+1;
		mes "[" +'@name$+ "]";
		mes "ガーディアンが設置されました。";
		mes "ガーディアンは私達の城を";
		mes "敵から守ってくれるでしょう。";
		break;
	case 5:		// カプラとの契約 / 解雇
		if(getcastledata('@map$,9) == 0) {
			mes "[" +'@name$+ "]";
			mes "カプラ本社との契約をして、";
			mes "砦内にカプラ職員を雇いますか？";
			mes "雇用には^ff000010000^000000Zenyが必要ですが…";
			next;
			if(select("雇う","取り消す") == 2) {
				mes "[" +'@name$+ "]";
				mes "かしこまりました。";
				mes "しかし、ギルド員のためにも";
				mes "利便性の向上を忘れては";
				mes "なりません。";
				break;
			}
			if(getgdskilllv(getcharid(2),10001) == 0) {
				mes "[" +'@name$+ "]";
				mes "マスター…まだカプラ本社との";
				mes "契約が結ばれていません。";
				mes "契約を締結しなければ、";
				mes "カプラ職員を雇うことができません。";
				next;
				mes "[" +'@name$+ "]";
				mes "カプラ本社との契約をお望みなら、";
				mes "ギルドスキルの";
				mes " ^ff0000カプラ契約^000000 スキルを";
				mes "習得しなければなりません。";
				break;
			}
			if(Zeny < 10000) {	//未調査
				mes "[" +'@name$+ "]";
				mes "マスター！お金が足りませんよ！";
				break;
			}
			set Zeny,Zeny-10000;
			hideoffnpc "AgitKafra_"+getarg(0);	//"AgitCode"を使って呼び出すNPC名を合成
			setcastledata '@map$,9,1;
			mes "[" +'@name$+ "]";
			mes "カプラとの契約が完了しました";
			next;
			cutin "kafra_01",2;
			mes "[カプラ職員]";
			mes "初めまして、";
			mes "カプラディフォルテと申します。";
			mes "最善を尽くしますので宜しくおねがいします！";
			close2;
			cutin "kafra_01",255;
			//mes "[" +'@name$+ "]";
			//mes "ギルドベースでカプラとの契約を維持するために";
			//mes "毎月Zenyを払わなければなりません。";
			//mes "(未実装)";
			break;
		}
		mes "[" +'@name$+ "]";
		mes "カプラ職員との契約を破棄しますか？";
		next;
		if(select("解雇する","キャンセル") == 2) {
			mes "[" +'@name$+ "]";
			mes "わかりました。";
			break;
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
			break;
		}
		mes "[カプラ職員]";
		mes "ああ、解雇なさるんですね…";
		next;
		hideonnpc "AgitKafra_"+getarg(0);
		setcastledata '@map$,9,0;
		cutin "kafra_01",255;
		mes "[" +'@name$+ "]";
		mes "…";
		mes "カプラとの契約が破棄されました。";
		break;
	case 6:		// マスターの部屋に入る
		mes "[" +'@name$+ "]";
		mes "私たちの貴重な生産品の数々が";
		mes "蓄えられている部屋に";
		mes "入られるのですね？";
		mes "そこは、マスターにのみ";
		mes "入室が許された部屋でございます。";
		next;
		if(select("マスターの部屋に入る","取り消す") == 2) {
			mes "[" +'@name$+ "]";
			mes "生産品は一日に一回生産可能ですが、";
			mes "ある程度まで貯蓄されるとそれ以上";
			mes "生産されなくなります。ですから、";
			mes "私達のギルドの発展のためにも";
			mes "適度に取り出さなければなりません。";
			break;
		}
		mes "[" +'@name$+ "]";
		mes "それではご案内致します。";
		mes "私についていらしてください。";
		mes "帰って来る時は隠しスイッチを";
		mes "操作すれば帰れます。";
		close2;
		warp '@map$,getarg(4),getarg(5);
		break;
	}
	return;
}

//============================================================
// マスタールームのスイッチ
//	callfunc "AgitMaster",WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitMaster	{
	mes "小さなレバーがあります。";
	mes "引きますか？";
	next;
	if(select("引く","引かない") == 1) {
		set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
		warp '@map$,getarg(0),getarg(1);
	}
	return;
}

//============================================================
// ギルドダンジョンへのスイッチ
//	callfunc "AgitDungeon","WarpMap",WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitDungeon	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0) {
		mes "[声]";	//未調査
		mes "多くの困難を乗り越え";
		mes "試練に打ち勝った者、";
		mes "その者に更なる試練を与えん";
		return;
	}
	mes "[声]";
	mes "試練に挑むならば先へ進むがよい";
	next;
	mes " ";
	mes "小さなレバーがあります。";
	mes "引きますか？";
	next;
	if(select("引く","引かない") == 2)
		return;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid && '@gid == getcharid(2)) {
		warp getarg(0),getarg(1),getarg(2);
		return;
	}
	mes " ";
	mes "しかし何も起こらなかった。";
	return;
}

//============================================================
// マスタールーム制限
//	callfunc "AgitBanWarp","WarpMap",WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitBanWarp	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(0) != getguildmasterid('@gid))	//マスターか？
		warp getarg(0),getarg(1),getarg(2);
	return;
}

//============================================================
// SEアジト占領
//	callfunc "AgitBreakSE","AgitCode";
//------------------------------------------------------------
function	script	AgitBreakSE	{
	donpcevent "Barricade#"+getarg(0)+"::OnReset";
	donpcevent "制御装置01#"+getarg(0)+"::OnReset";
	donpcevent "制御装置02#"+getarg(0)+"::OnReset";
	donpcevent "制御装置03#"+getarg(0)+"::OnReset";
	sleep 10000;
	set getvariableofnpc('guardian1,"Guardian#"+getarg(0)),0;
	set getvariableofnpc('guardian2,"Guardian#"+getarg(0)),0;
	set getvariableofnpc('status,"制御装置01#"+getarg(0)),1;
	set getvariableofnpc('status,"制御装置02#"+getarg(0)),1;
	set getvariableofnpc('status,"制御装置03#"+getarg(0)),2;
	donpcevent "GuardianStone1#"+getarg(0)+"::OnSet";
	donpcevent "GuardianStone2#"+getarg(0)+"::OnSet";
	announce "各守護石の修理ポイントと第3バリケードの制御装置が作動しました",0x9,0x00FF00;
	return;
}

//============================================================
// SE守備担当
//	callfunc "AgitGuard";
//------------------------------------------------------------
function	script	AgitGuard	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(2) != '@gid) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "誰ですか？";
		mes "今すぐこの砦から出ていってください！";
		return;
	}
	if(getcharid(0) != getguildmasterid('@gid)) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "私は砦の守備を担当している者です。";
		mes "詳しい話はマスターとします。";
		return;
	}
	if(agitcheck()) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "マスター！";
		mes "なんなりとご命令ください！";
		next;
		switch(select("砦の守備強化","現在状況報告","取り消し")) {
		case 1:
			if(getgdskilllv(getcharid(2),10002) == 0) {
				// 未調査
				mes "[" +strnpcinfo(1)+ "]";
				mes "ガーディアン設置に";
				mes "必要な研究知識が不足しています。";
				mes "ガーディアン設置に関する知識を";
				mes "得るためには、ギルドスキルの";
				mes "^FF0000ガーディアン製作研究^000000を";
				mes "習得しなければなりません。";
				return;
			}
			mes "[" +strnpcinfo(1)+ "]";
			mes "外の^FF0000守護石^000000を通じて^4D4DFFガーディアン^000000を";
			mes "召喚するように命令します。";
			mes "しかし、^FF0000守護石^000000が破壊されていたら";
			mes "^4D4DFFガーディアン^000000の召喚はできません。";
			mes "その際は^FF0000守護石^000000を再構築すれば";
			mes "^4D4DFFガーディアン^000000が召喚されます。";
			set '@def,getcastledata('@map$,3);
			set '@count,getvariableofnpc('guardian1,"Guardian#"+strnpcinfo(2));
			if(getvariableofnpc('status,"GuardianStone1#"+strnpcinfo(2)) == 0 && '@count == 0) {
				copyarray '@x,getarg(0),getarraysize(getarg(0));
				copyarray '@y,getarg(1),getarraysize(getarg(1));
				callguardian '@map$,'@x[0],'@y[0],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
				if('@def > 10 && '@def < 31) {
					callguardian '@map$,'@x[1],'@y[1],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					set '@count,'@count+2;
				}
				else if('@def > 30 && '@def < 51) {
					callguardian '@map$,'@x[2],'@y[2],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[3],'@y[3],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					set '@count,'@count+3;
				}
				else if('@def > 50 && '@def < 71) {
					callguardian '@map$,'@x[4],'@y[4],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[5],'@y[5],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[6],'@y[6],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					set '@count,'@count+4;
				}
				else if('@def > 70) {
					callguardian '@map$,'@x[7],'@y[7],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[8],'@y[8],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[9],'@y[9],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					callguardian '@map$,'@x[10],'@y[10],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					set '@count,'@count+5;
				}
				else {
					callguardian '@map$,'@x[11],'@y[11],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled1";
					set '@count,'@count+2;
				}
				set getvariableofnpc('guardian1,"Guardian#"+strnpcinfo(2)),'@count;
				initnpctimer "Guardian#"+strnpcinfo(2);
			}
			set '@count,getvariableofnpc('guardian2,"Guardian#"+strnpcinfo(2));
			if(getvariableofnpc('status,"GuardianStone2#"+strnpcinfo(2)) == 0 && '@count == 0) {
				copyarray '@x,getarg(2),getarraysize(getarg(2));
				copyarray '@y,getarg(3),getarraysize(getarg(3));
				callguardian '@map$,'@x[0],'@y[0],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
				if('@def > 10 && '@def < 31) {
					callguardian '@map$,'@x[1],'@y[1],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					set '@count,'@count+2;
				}
				else if('@def > 30 && '@def < 51) {
					callguardian '@map$,'@x[2],'@y[2],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[3],'@y[3],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					set '@count,'@count+3;
				}
				else if('@def > 50 && '@def < 71) {
					callguardian '@map$,'@x[4],'@y[4],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[5],'@y[5],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[6],'@y[6],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					set '@count,'@count+4;
				}
				else if('@def > 70) {
					callguardian '@map$,'@x[7],'@y[7],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[8],'@y[8],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[9],'@y[9],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					callguardian '@map$,'@x[10],'@y[10],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					set '@count,'@count+5;
				}
				else {
					callguardian '@map$,'@x[11],'@y[11],"--ja--",1899,1,"Guardian#"+strnpcinfo(2)+"::OnKilled2";
					set '@count,'@count+2;
				}
				set getvariableofnpc('guardian2,"Guardian#"+strnpcinfo(2)),'@count;
				initnpctimer "Guardian#"+strnpcinfo(2);
			}
			return;
		case 2:
			mes "[" +strnpcinfo(1)+ "]";
			mes "現在の状況をご報告します。";
			set '@status,getvariableofnpc('status,"GuardianStone1#"+strnpcinfo(2));
			mes "第1守護石 : " +('@status == 1? "^FF0000破壊^000000": '@status == 2? "^008000復旧可能^000000": "^4D4DFF正常^000000");
			set '@status,getvariableofnpc('status,"GuardianStone2#"+strnpcinfo(2));
			mes "第2守護石 : " +('@status == 1? "^FF0000破壊^000000": '@status == 2? "^008000復旧可能^000000": "^4D4DFF正常^000000");
			set '@status,getvariableofnpc('status,"制御装置01#"+strnpcinfo(2));
			mes "第1バリケード : " +('@status == 1? "^FF0000破壊^000000": '@status == 2? "^008000復旧可能^000000": "^4D4DFF正常^000000");
			set '@status,getvariableofnpc('status,"制御装置02#"+strnpcinfo(2));
			mes "第2バリケード : " +('@status == 1? "^FF0000破壊^000000": '@status == 2? "^008000復旧可能^000000": "^4D4DFF正常^000000");
			set '@status,getvariableofnpc('status,"制御装置03#"+strnpcinfo(2));
			mes "第3バリケード : " +('@status == 1? "^FF0000破壊^000000": '@status == 2? "^008000復旧可能^000000": "^4D4DFF正常^000000");
			return;
		case 3:
			mes "[" +strnpcinfo(1)+ "]";
			mes "私はいつでもここに居ますから、";
			mes "必要な時はいつでもご用命ください。";
			return;
		}
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "私は砦の守備を担当している";
	mes strnpcinfo(1)+ "と申します。";
	mes "只今、異常はありません。";
	next;
	if(select("会話を続ける","やめる") == 2) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "私はいつでもここに居ますから、";
		mes "必要な時はいつでもご用命ください。";
		return;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "砦について";
	mes "何か質問はございますか？";
	next;
	switch(select("^FF0000守護石^000000とは？","^4D4DFFバリケード^000000とは？","^008000フラッグ^000000の用途とは？","どんな戦略が良い？","ない")) {
	case 1:
		mes "[" +strnpcinfo(1)+ "]";
		mes "砦には^9C009C一つのエンペリウム^000000と";
		mes "^FF0000二つの守護石^000000が存在します。";
		mes "この^FF0000守護石^000000は砦を守るための";
		mes "最初の防御手段であり、";
		mes "^FF0000守護石が全て破壊されない限り";
		mes "敵は砦に侵入する事ができません^000000。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "砦の入口には^4D4DFF城門バリケード^000000があり";
		mes "^FF0000二つの守護石^000000は";
		mes "^4D4DFF城門バリケード^000000と連動しています。";
		mes "城門バリケードは守護石が全て";
		mes "破壊されない限り、一切攻撃出来ず";
		mes "通過することもできません。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "この^FF0000守護石^000000がある場所を";
		mes "『^FF0000拠点^000000』と呼びます。";
		mes "『^FF0000拠点^000000』と^FF0000守護石^000000を";
		mes "完璧に防御する事ができれば、";
		mes "敵はエンペリウムに近づけないのです。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "また、この^FF0000守護石^000000は";
		mes "砦を守護する^9C009Cガーディアンを";
		mes "召喚する役目^000000もありますので、";
		mes "色々と重要な部分です。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "そして^FF0000守護石^000000が召喚する";
		mes "^9C009Cガーディアン^000000の固体数は";
		mes "^4D4DFF砦の防衛値^000000と関係があります。";
		mes "^4D4DFF防衛値^000000が高いほど^FF0000守護石^000000が召喚する";
		mes "ガーディアンの数も多くなりますので、";
		mes "防御も投資も頑張ってください。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "破壊された^FF0000守護石^000000は一定時間が経つと";
		mes "再構築できますが、それは";
		mes "ギルドメンバーの皆様の役目です。";
		mes "^FF0000守護石^000000の状態は私を通じて";
		mes "確認できますので、";
		mes "いつでもご命令ください。";
		return;
	case 2:
		mes "[" +strnpcinfo(1)+ "]";
		mes "^4D4DFFバリケード^000000は^FF0000守護石^000000の次の";
		mes "防衛手段として、砦で構築している";
		mes "二次防御機能です。";
		mes "^FF0000守護石^000000が全て破壊されると";
		mes "^4D4DFF城門バリケード^000000が消滅し";
		mes "砦への進入が可能になってしまいます。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "敵を内部で防ぐのが城内の";
		mes "^4D4DFF第1～第3バリケード^000000です。";
		mes "この^4D4DFF3つのバリケード^000000が、";
		mes "砦の要所要所で敵の侵入を";
		mes "防いでいます。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "^4D4DFFバリケード^000000が耐えているうちは";
		mes "ある程度時間を稼げるでしょう。ただし";
		mes "^FF0000一度破壊されたバリケードは";
		mes "修理不可能^000000ですので、ご注意ください。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "^4D4DFFバリケード^000000は、攻城戦開始時に";
		mes "自動的に構築されますが、";
		mes "戦闘が始まり破壊されると";
		mes "もう修復することは出来ません。";
		mes "構築できるタイミングは、砦の持ち主が";
		mes "変わったときだけです。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "なお、^4D4DFFバリケード^000000の構築作業は";
		mes "^FF0000ギルドマスターのみ可能^000000と";
		mes "なっております。";
		mes "また、第3バリケードから順に";
		mes "構築が可能となります。";
		mes "この点もお忘れなきようお願いします。";
		return;
	case 3:
		mes "[" +strnpcinfo(1)+ "]";
		mes "砦の中には^008000フラッグ^000000が多数あります。";
		mes "^4D4DFFバリケード^000000によって移動の制限が";
		mes "発生しますので、これを越えるためにと";
		mes "設置したのがこの^008000フラッグ^000000です。";
		mes "通称『^008000リンクフラッグ^000000』と";
		mes "呼んでいます。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "どの^008000フラッグ^000000がどの場所に";
		mes "繋がっているのか……";
		mes "それは……全部覚える事が";
		mes "できていませんが、";
		mes "大体^FF0000一番のフラッグ^000000が";
		mes "各^FF0000拠点^000000へ繋がっていました。";
		next;
		mes "[" +strnpcinfo(1)+ "]";
		mes "砦の^008000フラッグ^000000は基本的に";
		mes "『^9C009Cエンペリウム^000000』がある所へ";
		mes "繋がっていますし、";
		mes "ギルドメンバーの皆さんのための";
		mes "便利機能としての^008000フラッグ^000000は、";
		mes "だいたい最後の番号のものでしょう。";
		return;
	case 4:
		mes "[" +strnpcinfo(1)+ "]";
		mes "戦略ですか……";
		mes "それは、私ではなくマスターが直接";
		mes "考えるべきだと思いますが……";
		mes "まあ、^FF0000拠点^000000と^4D4DFFバリケード^000000を最大限";
		mes "活用して、復旧のタイミングに";
		mes "気をつけること、でしょうね。";
		return;
	case 5:
		mes "[" +strnpcinfo(1)+ "]";
		mes "私はいつでもここに居ますから、";
		mes "必要な時はいつでもご用命ください。";
		return;
	}
}

//============================================================
// SEガーディアン召喚
//	callfunc "AgitCallGuardian",GuardianNo,Announce,PosX,PosY;
//------------------------------------------------------------
function	script	AgitCallGuardian	{
	if(getvariableofnpc('status,"GuardianStone"+getarg(0)+"#"+strnpcinfo(2)) != 0)
		return;
	switch(getarg(1)) {
		case 1: announce "拠点にガーディアンを一次追加召喚します。",0x9,0xFF4500; break;
		case 2: announce "拠点にガーディアンを二次追加召喚します。",0x9,0xFF4500; break;
		case 3: announce "拠点にガーディアンを三次追加召喚します。",0x9,0xFF4500; break;
		case 4: announce "拠点にガーディアンを四次追加召喚します。",0x9,0xFF4500; break;
		case 5: announce "拠点にガーディアンを五次追加召喚します。",0x9,0xFF4500; break;
		default: break;
	}
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);
	callguardian '@map$,getarg(2),getarg(3),"--ja--",1899,1,strnpcinfo(0)+"::OnKilled"+getarg(0);
	if(getarg(0) == 1)
		set getvariableofnpc('guardian1,strnpcinfo(0)),getvariableofnpc('guardian1,strnpcinfo(0))+1;
	else if(getarg(0) == 2)
		set getvariableofnpc('guardian2,strnpcinfo(0)),getvariableofnpc('guardian2,strnpcinfo(0))+1;
	return;
}

//============================================================
// SE守護石
//	callfunc "AgitStone",StoneNo;
//------------------------------------------------------------
function	script	AgitStone	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(2) != '@gid)
		return;
	mes "[" +strnpcinfo(1)+ "]";
	mes "破壊された守護石を再構築します。";
	mes "再構築には次の鉱石が必要です。";
	next;
	mes "[" +strnpcinfo(1)+ "]";
	mes "オリデオコン　^4D4DFF1個^000000";
	mes "エルニウム　^4D4DFF1個^000000";
	mes "石　^4D4DFF30個^000000";
	mes "ブルージェムストーン　^4D4DFF5個^000000";
	mes "イエロージェムストーン　^4D4DFF5個^000000";
	mes "レッドジェムストーン　^4D4DFF5個^000000";
	next;
	mes "[" +strnpcinfo(1)+ "]";
	mes "作業を続けますか？";
	next;
	if(select("やめる","続ける") == 1) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "全ての作業が取り消されました。";
		return;
	}
	if(countitem(984) < 1 || countitem(985) < 1 || countitem(7049) < 30 || countitem(715) < 5 || countitem(716) < 5 || countitem(717) < 5) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "材料が足りません。";
		return;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "■Phase：1";
	mes "以下の順で鉱石を配置してください。";
	mes " ";
	mes "^008000石^000000⇒^FF0000エルニウム^000000⇒^4D4DFFオリデオコン^000000";
	next;
	set '@point,0;
	setarray '@tmp$,"^4D4DFFオリデオコン^000000","^FF0000エルニウム^000000","^008000石^000000";
	for(set '@i,1; '@i <= 3; set '@i,'@i+1) {
		set @menu,select(printarray('@tmp$));
		mes "[" +strnpcinfo(1)+ "]";
		mes "■Phase：1-" +'@i;
		mes '@tmp$[@menu-1]+ "を配置。";
		mes " ";
		if('@i < 3)
			mes "次に配置する鉱石を選択してください。";
		else
			mes "次のフェーズに移行します。";
		if('@i == 1 && @menu == 3 || '@i == 2 && @menu == 2 || '@i == 3 && @menu == 1)
			set '@point,'@point+10;
		next;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "■Phase：2";
	mes "発動する魔力と一致する魔力が";
	mes "込められたジェムストーンを";
	mes "配置してください。";
	mes "魔力の性質は発動時の効果で";
	mes "判断できます。";
	next;
	mes "[" +strnpcinfo(1)+ "]";
	mes "■Phase：2";
	mes "また、";
	mes "情愛は燃えるように赤く、";
	mes "閃きは光のように黄色く、";
	mes "水滴は青く冷涼な様を表します。";
	next;
	setarray '@tmp$,"レッドジェムストーン","イエロージェムストーン","ブルージェムストーン";
	for(set '@i,1; '@i <= 8; set '@i,'@i+1) {
		set '@pattern,rand(1,3);
		switch('@pattern) {
		case 1:
			misceffect 225;
			emotion 3;
			break;
		case 2:
			misceffect 57;
			emotion 5;
			break;
		case 3:
			misceffect 54;
			emotion 4;
			break;
		}
		mes "[" +strnpcinfo(1)+ "]";
		mes "■Phase：2-" +'@i;
		mes "発動した魔力と一致する魔力が";
		mes "込められたジェムストーンを";
		mes "配置してください。";
		next;
		set @menu,select(printarray('@tmp$));
		mes "[" +strnpcinfo(1)+ "]";
		mes "■Phase：2-" +'@i;
		mes '@tmp$[@menu-1]+ "を配置します。";
		if(@menu != '@pattern) {
			next;
			mes "[" +strnpcinfo(1)+ "]";
			mes "■^FF0000MISS^000000";
			mes "お互いの魔力が衝突して";
			mes "^FF0000守護石^000000の再構築に失敗しました。";
			return;
		}
		set '@point,'@point+10;
		misceffect 18;
		next;
	}
	if('@point < 100) {
		// 未調査
		mes "[" +strnpcinfo(1)+ "]";
		mes "………………";
		mes "-状況に適切な対処ができず、";
		mes "　修復に失敗した。";
		mes "　資源の一部を失った-";
		delitem 7049,10;
		delitem 715,2;
		delitem 716,2;
		delitem 717,2;
		return;
	}
	if(getvariableofnpc('status,"GuardianStone"+getarg(0)+"#"+strnpcinfo(2)) == 0) {
		// 未調査
		mes "[" +strnpcinfo(1)+ "]";
		mes "ジェムストーンの配置が終わりました。";
		return;
	}
	if(agitcheck() == 0) {
		// 未調査
		mes "[" +strnpcinfo(1)+ "]";
		mes "エンペリウムが消滅し、";
		mes "守護石の再構築に失敗しました。";
		return;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "ジェムストーンの配置が終わりました。";
	mes "^FF0000守護石^000000の再構築に^4D4DFF成功^000000しました!!";
	delitem 984,1;
	delitem 985,1;
	delitem 7049,30;
	delitem 715,5;
	delitem 716,5;
	delitem 717,5;
	misceffect 135;
	hideonnpc;
	donpcevent "GuardianStone"+getarg(0)+"#"+strnpcinfo(2)+"::OnRepair";
	if(getvariableofnpc('status,"GuardianStone1#"+strnpcinfo(2))+getvariableofnpc('status,"GuardianStone2#"+strnpcinfo(2)) == 0) {
		announce "守護石が完全復旧し、城門バリケードが復活しました。",0x9,0x00FF00;
		donpcevent "Barricade#"+strnpcinfo(2)+"::OnSet";
	}
	else
		announce "第"+getarg(0)+"守護石の再構築に成功しました！",0x9,0x00FF00;
	return;
}

//============================================================
// SE守護石破壊
//	callfunc "AgitStoneBreak",StoneNo;
//------------------------------------------------------------
function	script	AgitStoneBreak	{
	set getvariableofnpc('status,strnpcinfo(0)),1;
	set '@status1,getvariableofnpc('status,"GuardianStone1#"+strnpcinfo(2));
	set '@status2,getvariableofnpc('status,"GuardianStone2#"+strnpcinfo(2));
	if(('@status1 == 1 || '@status1 == 2) && ('@status2 == 1 || '@status2 == 2)) {
		announce "全ての守護石が破壊され、城門バリケードが消滅しました！",0x9,0xFF0000;
		donpcevent "Barricade#"+strnpcinfo(2)+"::OnReset";
		stopnpctimer "Guardian#"+strnpcinfo(2);
	}
	else {
		announce "第"+getarg(0)+"守護石が破壊されました！",0x9,0xFF4500;
	}
	killmonster "this","Guardian#"+strnpcinfo(2)+"::OnKilled"+getarg(0);
	initnpctimer;
	return;
}

//============================================================
// SEバリケード制御装置
//	callfunc "AgitBarricade";
//------------------------------------------------------------
function	script	AgitBarricade	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if(getcharid(0) != getguildmasterid('@gid) || getvariableofnpc('status,strnpcinfo(0)) != 2)
		return;
	mes "[" +strnpcinfo(1)+ "]";
	mes "破損したバリケードの修復が可能です。";
	mes "次の資材が必要です。";
	mes "木屑　^4D4DFF30個^000000";
	mes "鋼鉄　^4D4DFF10個^000000";
	mes "エンベルタコン　^4D4DFF10個^000000";
	mes "オリデオコン　^4D4DFF5個^000000";
	next;
	if(select("やめる","続ける") == 1) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "全ての作業が取り消されました。";
		return;
	}
	if(countitem(1019) < 30 || countitem(999) < 10 || countitem(1011) < 10 || countitem(984) < 5) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "材料が足りません。";
		return;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "^4D4DFF支柱の補強^000000が必要な場合は";
	mes "^4D4DFF木屑^000000を使います。";
	mes "^FF0000耐久力の強化^000000には^FF0000オリデオコン^000000、";
	mes "^008000強化接着^000000には^008000鋼鉄^000000を使います。";
	mes "^9C009C全般的な補修^000000には";
	mes "^9C009Cエンベルタコン^000000をお使いください。";
	next;
	set '@success,rand(5,10);
	set '@fail,0;
	set '@point,0;
	setarray '@tmp$,"木屑","鋼鉄","エンベルタコン","オリデオコン";
	while('@point < '@success) {
		set '@pattern,rand(1,4);
		switch('@pattern) {
		case 1:
			mes "-破壊された地点が深く掘られている。";
			mes "　支柱の補強が必要だ-";
			break;
		case 2:
			mes "-あちこち割れているのが気になる。";
			mes "　強い接着や溶接を";
			mes "　しなければならないようだ-";
			break;
		case 3:
			mes "-全般的な補修作業が必要そうだ-";
			break;
		case 4:
			mes "-簡単に破壊されないように";
			mes "　耐久力の強化が必要そうだ-";
			break;
		}
		next;
		set @menu,select(printarray('@tmp$));
		if('@pattern == 2 && @menu == 1) {
			mes "（木屑を使ってウドゥンアーマーを";
			mes "　作ってみた。";
			mes "　これを着せれば……）";
			set '@fail,1;
			next;
			continue;
		}
		if(@menu != '@pattern) {
			mes "（" +'@tmp$[@menu-1]+ "を利用してみようと";
			mes "　したが、うまくできない。";
			mes "　最初からやり直した方が";
			mes "　良さそうだ。）";
			return;
		}
		switch('@pattern) {
		case 1:
			mes "（木屑を使って支柱を補強した。）";
			break;
		case 2:
			mes "（鋼鉄を利用して溶接を試みた。";
			mes "　立派なスチールアーマーを";
			mes "　着せたような気がする。）";
			break;
		case 3:
			mes "（エンベルタコンを利用して";
			mes "　全般的な補修作業をした。）";
			break;
		case 4:
			mes "（ホルグレンが武器精錬を";
			mes "　する時のようにオリデオコンで";
			mes "　打ってみた。いい感じだ。）";
			break;
		}
		set '@point,'@point+1;
		misceffect 101,"";
		next;
	}
	mes "-大体終わったようだ-";
	next;
	if(agitcheck() == 0) {
		// 未調査
		mes "-しかし、エンペリウムが消滅し、";
		mes "　バリケードの構築ができなかった-";
		return;
	}
	if('@fail) {
		mes "[" +strnpcinfo(1)+ "]";
		mes "………………";
		mes "-状況に適切な対処ができず、";
		mes "　修復に失敗した。";
		mes "　資源の一部を失った-";
		delitem 984,2;
		delitem 999,4;
		delitem 1019,14;
		delitem 1011,3;
		return;
	}
	mes "[" +strnpcinfo(1)+ "]";
	mes "^4D4DFFバリケード^000000を修復しました！";
	delitem 1019,30;
	delitem 999,10;
	delitem 1011,10;
	delitem 984,5;
	set getvariableofnpc('status,strnpcinfo(0)),0;
	if(strnpcinfo(1) == "制御装置03") {
		mes "-^FF0000制御装置02が作動^000000しました。";
		mes "　第2バリケードの修復が可能です-";
		set getvariableofnpc('status,"制御装置02#"+strnpcinfo(2)),2;
		announce "第3バリケードの修復に成功しました！",0x9,0x00FF00;
	}
	else if(strnpcinfo(1) == "制御装置02") {
		mes "-^FF0000制御装置01が作動^000000しました。";
		mes "　第1バリケードの修復が可能です-";
		set getvariableofnpc('status,"制御装置01#"+strnpcinfo(2)),2;
		announce "第2バリケードの修復に成功しました！",0x9,0x00FF00;

	}
	else
		announce "第1バリケードの修復に成功しました！",0x9,0x00FF00;
	donpcevent strnpcinfo(0)+"::OnSet";
	return;
}

//============================================================
// SEリンクフラッグA（各地域へのワープ）
//	callfunc "AgitLinkFlagA",SelectMenuArray,WarpXArray,WarpYArray;
//------------------------------------------------------------
function	script	AgitLinkFlagA	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(2) != '@gid)
		return;
	mes "[リンクフラッグ]";
	mes "移動する場所を選んでください。";
	set '@max,getarraysize(getarg(0));
	copyarray '@code,getarg(0),'@max;
	for(set '@i,0; '@i < '@max; set '@i,'@i+1) {
		switch('@code['@i]) {
			case 1: set '@disp$['@i],"第1拠点"; break;
			case 2: set '@disp$['@i],"第2拠点"; break;
			case 11: set '@disp$['@i],"防衛地域1-1"; break;
			case 12: set '@disp$['@i],"防衛地域1-2"; break;
			case 13: set '@disp$['@i],"防衛地域1-3"; break;
			case 14: set '@disp$['@i],"防衛地域1-4"; break;
			case 21: set '@disp$['@i],"防衛地域2-1"; break;
			case 22: set '@disp$['@i],"防衛地域2-2"; break;
			case 23: set '@disp$['@i],"防衛地域2-3"; break;
			case 24: set '@disp$['@i],"防衛地域2-4"; break;
			case 31: set '@disp$['@i],"防衛地域3-1"; break;
			case 32: set '@disp$['@i],"防衛地域3-2"; break;
			case 33: set '@disp$['@i],"防衛地域3-3"; break;
			case 34: set '@disp$['@i],"防衛地域3-4"; break;
			case 111: set '@disp$['@i],"区域1-1"; break;
			case 112: set '@disp$['@i],"区域1-2"; break;
			case 113: set '@disp$['@i],"区域1-3"; break;
			case 114: set '@disp$['@i],"区域1-4"; break;
			case 121: set '@disp$['@i],"区域2-1"; break;
			case 122: set '@disp$['@i],"区域2-2"; break;
			case 123: set '@disp$['@i],"区域2-3"; break;
			case 124: set '@disp$['@i],"区域2-4"; break;
			case 131: set '@disp$['@i],"区域3-1"; break;
			case 132: set '@disp$['@i],"区域3-2"; break;
			case 133: set '@disp$['@i],"区域3-3"; break;
			case 134: set '@disp$['@i],"区域3-4"; break;
			case 100: set '@disp$['@i],"拠点への道"; break;
			case 101: set '@disp$['@i],"中央1区画"; break;
			case 102: set '@disp$['@i],"中央2区画"; break;
			case 103: set '@disp$['@i],"中央3区画"; break;
			default: set '@disp$['@i],"わからない所"; break;
		}
	}
	set '@disp$['@max],"取り消し";
	set @menu,select(printarray('@disp$))-1;
	if(@menu == '@max)	//取り消し
		return;
	copyarray '@x,getarg(1),'@max;
	copyarray '@y,getarg(2),'@max;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	warp '@map$,'@x[@menu],'@y[@menu];
	return;
}

//============================================================
// SEリンクフラッグB（ギルドルームへのワープ）
//	callfunc "AgitLinkFlagB",Type,WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitLinkFlagB	{
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid <= 0 || getcharid(2) != '@gid)
		return;
	mes "[リンクフラッグ]";
	if(getarg(0)) {		//Typeが0以外のときはギルドルームのメッセージ
		mes "ギルドメンバーの利便性向上のために";
		mes "造られた地域への移動が可能です。";
	}
	else {		//Typeが0のときは中央作戦地域のメッセージ
		mes "^9C009Cエンペリウム^000000がある";
		mes "中央作戦地域に移動します。";
	}
	mes "移動しますか？";
	if(select("移動","取り消し") == 2)
		return;
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	warp '@map$,getarg(1),getarg(2);
	return;
}

//============================================================
// SEギルドダンジョン移動
//	callfunc "AgitDungeonSE","WarpMap",WarpX,WarpY;
//------------------------------------------------------------
function	script	AgitDungeonSE	{
	if(!getcharid(2))
		return;
	mes "‐随分大きな、";
	mes "　不思議なヒマワリだ……";
	mes "　ほんの僅かではあるが";
	mes "　魔力が感じられる‐";
	next;
	if(select("^0000FF触れてみる^000000","やめる") == 2) {
		mes "‐未知の世界に";
		mes "　吸い込まれてしまいそうな";
		mes "　気がする……";
		mes "　やめておこう‐";
		return;
	}
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	set '@gid,getcastledata('@map$,1);
	if('@gid && '@gid == getcharid(2)) {
		warp getarg(0),getarg(1),getarg(2);
		return;
	}
	mes "‐しかし何も起こらなかった‐";
	return;
}
