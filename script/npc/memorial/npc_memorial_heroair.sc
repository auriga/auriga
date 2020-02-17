//= Auriga Script ==============================================================
// Ragnarok Online Hero in the Air Script	by refis
//==============================================================================

//============================================================
// 専用装備精練NPC
//------------------------------------------------------------
dali02.gat,139,87,3	script	道楽裁縫師#refine	70,{
	mes "[道楽裁縫師]";
	mes "私は裁縫師をしています。";
	mes "私に飛行船で入手できる装備を";
	mes "渡して頂ければ";
	mes "装備同士を組み合わせて";
	mes "精錬をすることができます。";
	next;
	mes "[道楽裁縫師]";
	mes "装備の精錬を行いますか？";
	next;
	switch(select("飛行船シリーズを精錬","ペルロックシリーズを精錬","説明を聞く","やめる")) {
	case 1:
		setarray '@target,15159,20792,22087;
		break;
	case 2:
		setarray '@target,15158,20791,22086;
		break;
	case 3:
		mes "[道楽裁縫師]";
		mes "メモリアルダンジョン「飛行船襲撃」。";
		mes "ここで入手できる";
		mes "^0000ff飛行船シリーズ^000000こと";
		mes "^0000ff飛行船スーツ^000000、^0000ff飛行船マント^000000、";
		mes "^0000ff飛行船ブーツ^000000。";
		next;
		mes "[道楽裁縫師]";
		mes "そして、^ff0000ペルロックシリーズ^000000である";
		mes "^ff0000ペルロックのスーツ^000000、";
		mes "^ff0000ペルロックのマント^000000、";
		mes "^ff0000ペルロックのブーツ^000000。";
		next;
		mes "[道楽裁縫師]";
		mes "この装備は通常の精錬はできませんが、";
		mes "私ならば精錬できるのです！";
		mes "もし、精錬したい場合は";
		mes "是非、持ってきてください。";
		next;
		mes "[道楽裁縫師]";
		mes "やり方は簡単！";
		mes "まず、精錬したい対象装備を";
		mes "装備してください。";
		next;
		mes "[道楽裁縫師]";
		mes "対象装備が飛行船シリーズであれば、";
		mes "素材として";
		mes "飛行船シリーズのどれかの装備1個";
		mes "を持ってきてください。";
		mes "その装備1個を消費して、";
		mes "精錬して差し上げましょう。";
		next;
		mes "[道楽裁縫師]";
		mes "すなわち、もし";
		mes "飛行船スーツを精錬したい場合は、";
		mes "飛行船スーツ、飛行船マント、";
		mes "飛行船ブーツのいずれか1個消費して";
		mes "精錬できるということです。";
		next;
		mes "[道楽裁縫師]";
		mes "同様に、";
		mes "対象装備がペルロックシリーズであれば、";
		mes "素材として";
		mes "ペルロックシリーズのいずれかを";
		mes "1個持ってきてください。";
		next;
		mes "[道楽裁縫師]";
		mes "注意して頂きたいことは、";
		mes "素材にした装備の^ff0000精錬値は引き継がれず";
		mes "素材に挿さっていたカードも消滅する^000000";
		mes "という事です。";
		next;
		mes "[道楽裁縫師]";
		mes "ちなみに私、ホルグレンさんと違って、";
		mes "^0000ff精錬1から失敗して";
		mes "破壊してしまう事がある女^000000なので";
		mes "そこのところはご了承くださいね。";
		next;
		mes "[道楽裁縫師]";
		mes "それではいつでも";
		mes "精錬しにきてください！";
		close;
	case 4:
		mes "[道楽裁縫師]";
		mes "そうですか。";
		mes "また、ご入用の時は";
		mes "いつでも来てください。";
		close;
	}
	mes "[道楽裁縫師]";
	mes "どれを精錬しますか？";
	next;
	switch(select(
		(getequipid(2)!=0? "^nItemID^" +getequipid(2): "体-[装備していない]"),
		(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装備していない]"),
		(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴-[装備していない]")
	)) {
	case 1: set '@itemid,getequipid(2); set '@menu,2; break;
	case 2: set '@itemid,getequipid(5); set '@menu,5; break;
	case 3: set '@itemid,getequipid(6); set '@menu,6; break;
	}
	if('@itemid == 0) {
		mes "[道楽裁縫師]";
		mes "何も装備していませんよ？";
		mes "必ず、精錬したい装備を";
		mes "装備した状態で話しかけてください。";
		close;
	}
	set '@len,getarraysize('@target);
	for(set '@i,0; '@i < '@len; set '@i,'@i+1) {
		if('@itemid == '@target['@i])
			break;
	}
	if('@i == '@len) {
		mes "[道楽裁縫師]";
		mes "対象装備を装備していません。";
		mes "必ず飛行船で入手した装備を";
		mes "装備してくださいね。";
		close;
	}
	set '@refine,getequiprefinerycnt('@menu);
	if('@refine>=10) {
		mes "[道楽裁縫師]";
		mes "これ以上は精練できませんね。";
		close;
	}
	set '@card1,getequipcardid('@menu,0);
	mes "[道楽裁縫師]";
	mes "素材にはどれを使いますか？";
	next;
	set '@rec,select(getitemname('@target[0]),getitemname('@target[1]),getitemname('@target[2]));
	set '@req,('@itemid=='@target['@rec-1])? 2: 1;		// 対象装備と素材が同じ場合は2つ分判定が必要
	if(countitem('@target['@rec-1]) < '@req) {
		mes "[道楽裁縫師]";
		mes "素材になる装備を";
		mes "持っていないようです。";
		mes "お手持ちの装備品を";
		mes "確認してから、";
		mes "また来てください。";
		close;
	}
	mes "[道楽裁縫師]";
	mes "それでは精錬を開始しますが";
	mes "素材になるアイテムを";
	mes "複数所持している場合、";
	mes "どれが使用されるかわかりません。";
	next;
	mes "[道楽裁縫師]";
	mes "大事な装備が使用されないように";
	mes "使用したくない装備は";
	mes "必ず倉庫に預けておいてください。";
	next;
	mes "[道楽裁縫師]";
	mes "それでは精錬をしても";
	mes "よろしいですか？";
	next;
	if(select("精錬する","やめる") == 2) {
		mes "[道楽裁縫師]";
		mes "そうですか。";
		mes "また、ご入用の時は";
		mes "いつでも来てください。";
		close;
	}
	mes "[道楽裁縫師]";
	mes "うりゃー！";
	mes "うりゃりゃりゃー！";
	next;
	delequip '@menu;
	delitem '@target['@rec-1],1;
	setarray '@rate,9000,7000,5000,3000,1000,500,300,100,50,10;
	if(rand(10000) < '@rate['@refine]) {
		misceffect 154,"";
		mes "[道楽裁縫師]";
		mes "よし、完成！";
		mes "良い物ができました！";
		getitem2 '@itemid,1,1,'@refine+1,0,'@card1,0,0,0;
		close;
	}
	else {
		misceffect 155,"";
		mes "[道楽裁縫師]";
		mes "クホホッ……";
		mes "失敗してしまいました……。";
		mes "申し訳ありません……。";
		close;
	}
OnInit:
	waitingroom "飛行船装備【精錬】",0;
	end;
}

//============================================================
// 専用装備交換NPC
//------------------------------------------------------------
dali02.gat,133,87,3	script	飛行船愛好家#sell	755,{
	mes "[飛行船愛好家]";
	mes "ここでは飛行船装備の";
	mes "買取や交換を行っています。";
	mes "私、好きなんです！飛行船装備！";
	next;
	switch(select("買取してほしい","交換してほしい","説明を聞く")) {
	case 1:
		break;
	case 2:
		mes "[飛行船愛好家]";
		mes "飛行船装備の交換ですね。";
		mes "交換を行う場合は";
		mes "必ず交換したい装備を";
		mes "装備した状態で";
		mes "話しかけて下さいね！";
		next;
		mes "[飛行船愛好家]";
		mes "さて、何と交換しましょうか？";
		next;
		set '@menu,select("ペルロックの帽子[1]","エクソダスジョーカーXIII[1]","やめる");
		switch('@menu) {
		case 1:
			mes "[飛行船愛好家]";
			mes "ふむ。";
			mes "ペルロックの帽子ですね。";
			next;
			mes "[飛行船愛好家]";
			mes "そちらのアイテムだと";
			mes "^ff0000[衣装]ペルロックの帽子^000000と";
			mes "交換ではどうでしょうか？";
			set '@gain,19144;
			break;
		case 2:
			mes "[飛行船愛好家]";
			mes "ふむ。";
			mes "エクソダスジョーカーXIIIですね。";
			next;
			mes "[飛行船愛好家]";
			mes "そちらのアイテムだと";
			mes "^ff0000+7以上の";
			mes "ペルロック系装備^000000と";
			mes "交換ではどうでしょうか？";
			set '@gain,28214;
			break;
		case 3:
			mes "[飛行船愛好家]";
			mes "そうですか。";
			mes "気が変わったら";
			mes "またいつでも来てください。";
			close;
		}
		next;
		mes "[飛行船愛好家]";
		mes "交換上の注意ですが";
		mes "こちらの要求以上のアイテムを";
		mes "交換対象にされても取引内容に";
		mes "変化はありませんので";
		mes "ご注意ください。";
		next;
		mes "[飛行船愛好家]";
		mes "では、どれと交換しましょう？";
		next;
		switch(select(
			(getequipid(2)!=0? "^nItemID^" +getequipid(2): "体-[装備していない]"),
			(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装備していない]"),
			(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴-[装備していない]"),
			(getequipid(12)!=0? "^nItemID^" +getequipid(12): "衣装‐上‐[装備していない]")
		)) {
		case 1: if(getequipid(2) == 15158 && '@menu == 2) set '@i,2; break;
		case 2: if(getequipid(5) == 20791 && '@menu == 2) set '@i,5; break;
		case 3: if(getequipid(6) == 22086 && '@menu == 2) set '@i,6; break;
		case 4: if(getequipid(12) == 19914 && '@menu == 1) set '@i,12; break;
		}
		if('@i == 0) {
			mes "[飛行船愛好家]";
			mes "対象装備を装備していません。";
			mes "必ず飛行船で入手した装備を";
			mes "装備してくださいね。";
			close;
		}
		// 以下未調査
		if('@menu == 2 && getequiprefinerycnt('@i) < 7) {
			mes "[飛行船愛好家]";
			mes "対象装備の精練値が足りませんね。";
			mes "^ff0000+7以上の";
			mes "ペルロック系装備^000000を";
			mes "装備してください。";
			close;
		}
		mes "[飛行船愛好家]";
		mes "では、";
		mes "^nItemID^" +getequipid('@i)+ "と";
		mes "^nItemID^" +'@gain+ "を";
		mes "交換します。";
		mes "よろしいですか？";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[飛行船愛好家]";
			mes "そうですか。";
			mes "残念です。";
			close;
		}
		delequip '@i;
		getitem '@gain,1;
		mes "[飛行船愛好家]";
		mes "ありがとうございます！";
		mes "大切に使ってくださいね！";
		close;
	case 3:
		mes "[飛行船愛好家]";
		mes "私は飛行船シリーズと";
		mes "ペルロックシリーズを";
		mes "買取ったり交換したりしています。";
		mes "精錬値が高いほど";
		mes "高く査定させていただきます。";
		next;
		mes "[飛行船愛好家]";
		mes "なお、引き取る装備に";
		mes "カードが挿さっていた場合、";
		mes "^ff0000カードはお返しできません。^000000";
		mes "また、どのようなカードであっても";
		mes "^ff0000買取額に変更はありません^000000ので";
		mes "ご注意ください。";
		next;
		mes "[飛行船愛好家]";
		mes "これが買取表ですよ！";
		next;
		mes "‐買取表‐";
		mes "　^0000ff飛行船シリーズ^000000の場合！";
		mes "　（飛行船スーツ、飛行船マント";
		mes "　飛行船ブーツのいずれか）";
		mes "　";
		mes "　未精錬　　10,000zeny";
		mes "　精錬値+1　30,000zeny";
		mes "　精錬値+2　90,000zeny";
		mes "　精錬値+3　270,000zeny";
		mes "　精錬値+4　810,000zeny";
		mes "　精錬値+5　2,430,000zeny";
		mes "　精錬値+6　7,290,000zeny";
		mes "　精錬値+7　21,870,000zeny";
		mes "　精錬値+8　65,610,000zeny";
		mes "　精錬値+9　196,830,000zeny";
		mes "　精錬値+10　590,490,000zeny";
		next;
		mes "‐買取表‐";
		mes "　^ff0000ペルロックシリーズ^000000の場合！";
		mes "　（ペルロックスーツ、";
		mes "　ペルロックマント、";
		mes "　ペルロックブーツのいずれか）";
		mes "　";
		mes "　未精錬　　20,000zeny";
		mes "　精錬値+1　60,000zeny";
		mes "　精錬値+2　180,000zeny";
		mes "　精錬値+3　540,000zeny";
		mes "　精錬値+4　1,620,000zeny";
		mes "　精錬値+5　4,860,000zeny";
		mes "　精錬値+6　14,580,000zeny";
		mes "　精錬値+7　43,740,000zeny";
		mes "　精錬値+8　131,220,000zeny";
		mes "　精錬値+9　393,660,000zeny";
		mes "　精錬値+10　1,180,980,000zeny";
		next;
		mes "[飛行船愛好家]";
		mes "あと、交換対象アイテムは";
		mes "その時々で対象となる";
		mes "アイテムが異なりますので";
		mes "ご注意ください。";
		close;
	}
	mes "[飛行船愛好家]";
	mes "飛行船装備の買取ですね。";
	mes "飛行船装備は精錬値によって";
	mes "買取額が増えますよ。";
	next;
	mes "[飛行船愛好家]";
	mes "買い取って欲しい装備は";
	mes "必ず装備した状態で";
	mes "話しかけて下さいね！";
	next;
	mes "[飛行船愛好家]";
	mes "さて、どれを買取ましょうか？";
	next;
	switch(select("飛行船装備","ペルロック装備","やめる")) {
	case 1:
		setarray '@target,15159,20792,22087;
		set '@zeny,10000;
		break;
	case 2:
		setarray '@target,15158,20791,22086;
		set '@zeny,20000;
		break;
	case 3:
		mes "[飛行船愛好家]";
		mes "そうですか。";
		mes "気が変わったら";
		mes "またいつでも来てください。";
		close;
	}
	mes "[飛行船愛好家]";
	mes "どれを買取ましょう？";
	next;
	switch(select(
		(getequipid(2)!=0? "^nItemID^" +getequipid(2): "体-[装備していない]"),
		(getequipid(5)!=0? "^nItemID^" +getequipid(5): "肩にかける物-[装備していない]"),
		(getequipid(6)!=0? "^nItemID^" +getequipid(6): "靴-[装備していない]")
	)) {
	case 1: set '@itemid,getequipid(2); set '@menu,2; break;
	case 2: set '@itemid,getequipid(5); set '@menu,5; break;
	case 3: set '@itemid,getequipid(6); set '@menu,6; break;
	}
	if('@itemid == 0) {
		mes "[飛行船愛好家]";
		mes "何も装備していませんよ？";
		mes "必ず、買い取って欲しい装備を";
		mes "装備した状態で話しかけてください。";
		close;
	}
	set '@len,getarraysize('@target);
	for(set '@i,0; '@i < '@len; set '@i,'@i+1) {
		if('@itemid == '@target['@i])
			break;
	}
	if('@i == '@len) {
		mes "[飛行船愛好家]";
		mes "対象装備を装備していません。";
		mes "必ず飛行船で入手した装備を";
		mes "装備してくださいね。";
		close;
	}
	set '@refine,getequiprefinerycnt('@menu);
	set '@price,'@zeny * 3 ** '@refine;
	mes "[飛行船愛好家]";
	mes "そちらのアイテムは";
	mes "^0000ff" +'@price+ "^000000zenyで";
	mes "買取ます。";
	mes "よろしいですか？";
	next;
	if(select("いいえ","はい") == 1) {
		mes "[飛行船愛好家]";
		mes "そうですか。";
		mes "残念です。";
		close;
	}
	if(2147483647 - Zeny < '@price) {
		mes "[飛行船愛好家]";
		mes "所持金が多すぎますね。";
		mes "少し減らしてから来てください。";
		close;
	}
	mes "[飛行船愛好家]";
	mes "それでは買取ます。";
	mes "はい、どうぞ。";
	delequip '@menu;
	set Zeny,Zeny+'@price;
	close;
OnInit:
	waitingroom "飛行船装備【交換・買取】",0;
	end;
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
dali02.gat,136,79,3	script	探検家リオン#air1	945,{
	mes "[探検家リオン]";
	mes "私がここ数日間";
	mes "この場所を調べてみた結果、";
	mes "ここにはある飛行船の記憶が";
	mes "刻まれているようだ。";
	next;
	mes "[探検家リオン]";
	mes "……それが全部だ。";
	mes "私にもそれ以上の事は";
	mes "わからないんだ……。";
	next;
	mes "[探検家リオン]";
	mes "無駄だと思うが、";
	mes "調べたいならそこの移動機を";
	mes "調べてみたらどうだ？";
	mes "私も調べたが結局何も";
	mes "見つからなかった……。";
	mes "悔しい限りだ。";
	close;
}

dali02.gat,142,81,3	script	次元移動機#sara	10007,{
	if(BaseLevel < 70) {
		mes "^ff0000‐BaseLv70以上の方のみ";
		mes "　入場可能なダンジョンです‐^000000";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "^ff0000‐次元の狭間に入場するためには";
		mes "　パーティーを結成してください‐^000000";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "^ff0000‐このメモリアルダンジョンは";
		mes "　1人用のダンジョンです。";
		mes "　パーティーリーダーのみ";
		mes "　入場が可能です‐^000000";
		close;
	}
	if(checkquest(15050)) {
		if(!(checkquest(15050)&2) || !(checkquest(120205)&2)) {
			mes "‐この先は入場してから1回目の";
			mes "　^ff0000午前5時以降^000000に進行可能です。";
			mes "　但し、最後の入場をしてから";
			mes "　^ff00001時間^000000経過するまでは";
			mes "　進行できませんのでご注意ください‐";
			close;
		}
		delquest 15050;
		delquest 120205;
	}
	mes "‐次元移動機がある‐";
	set '@party$,strcharinfo(1);
	set '@leader$,strcharinfo(0);
	next;
	switch(select("次元の狭間の生成","飛行船襲撃に入場","やめる")) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "‐パーティー名";
			mes "　"+ '@party$;
			mes "　パーティーリーダー";
			mes "　"+ '@leader$;
			mes "^0000ffhero_air^000000";
			mes "生成に失敗しました‐";
			close;
		}
		mdcreate "hero_air";
		mes "^ff0000‐次元の狭間を生成します‐^000000";
		close;
	case 2:
		if(getonlinepartymember() != 1) {
			mes "‐次元の狭間が不安定なため";
			mes "　一人しか入ることができない‐";
			close;
		}
		if(getmercinfo(0)) {
			mes "‐次元の狭間が不安定なため";
			mes "　傭兵と一緒に入ることができない‐";
			close;
		}
		switch(mdenter("hero_air")) {
		case 0:	// エラーなし
			announce "メモリアルダンジョン[hero_air] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99,0x190,12,0,0;
			setquest 15050;
			setquest 120205;
			set HEROAIR_1QUE,0;
			donpcevent getmdnpcname("#HeroAirManager")+ "::OnStart";
			close2;
			//warp "1@air1.gat",244,73;
			end;
		case 1:	// パーティー未加入
			mes "‐次元の狭間が不安定なため";
			mes "　一人しか入ることができない‐";
			close;
		case 2:	// ダンジョン未作成
			mes "^ff0000‐次元の狭間が生成されていません。";
			mes "　パーティーリーダーが";
			mes "　生成することができます‐^000000";
			close;
		default:	// その他エラー
			close;
		}
	case 3:
		mes "‐次元移動機から離れた‐";
		close;
	}
OnInit:
	waitingroom "飛行船襲撃",0;
	end;
}

//============================================================
// 飛行船襲撃
//------------------------------------------------------------
1@air1.gat,1,1,0	script	#HeroAirManager	139,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("ワイバーン#air1");
	hideonnpc getmdnpcname("ワイバーンキッド#1air1");
	hideonnpc getmdnpcname("レッサーワイバーン#1air");
	hideonnpc getmdnpcname("スカイジャイロ#1air1");
	hideonnpc getmdnpcname("スカイジャイロ#1air2");
	hideonnpc getmdnpcname("スカイグレムリン#1air1");
	hideonnpc getmdnpcname("スカイグレムリン#2air1");
	hideonnpc getmdnpcname("スカイグレムリン#3air1");
	hideonnpc getmdnpcname("スカイグレムリン#4air1");
	hideonnpc getmdnpcname("スカイグレムリン#5air1");
	hideonnpc getmdnpcname("スカイグレムリン#6air1");
	hideonnpc getmdnpcname("スカイグレムリン#7air1");
	hideonnpc getmdnpcname("スカイグレムリン#8air1");
	hideonnpc getmdnpcname("スカイグレムリン#1air2");
	hideonnpc getmdnpcname("スカイグレムリン#2air2");
	hideonnpc getmdnpcname("スカイグレムリン#3air2");
	hideonnpc getmdnpcname("スカイグレムリン#4air2");
	hideonnpc getmdnpcname("スカイグレムリン#5air2");
	hideonnpc getmdnpcname("スカイグレムリン#6air2");
	hideonnpc getmdnpcname("スカイグレムリン#7air2");
	hideonnpc getmdnpcname("スカイグレムリン#8air2");

	hideonnpc getmdnpcname("スカイグレムリン#2aair1");
	hideonnpc getmdnpcname("アイリス#2air1");
	hideonnpc getmdnpcname("ケイオス#2air1");
	hideonnpc getmdnpcname("ロキ#air2");

	hideonnpc getmdnpcname("アイリス#2air2");
	hideonnpc getmdnpcname("船長ペルロック#air2");
	hideonnpc getmdnpcname("船長ペルロック#2air2");
	hideonnpc getmdnpcname("ケイオス#air2");
	hideonnpc getmdnpcname("warp1#air1");
	hideonnpc getmdnpcname("warp2a#air1");
	hideonnpc getmdnpcname("warp2b#air1");
	hideonnpc getmdnpcname("warp3a#air1");
	hideonnpc getmdnpcname("warp3b#air1");
	hideonnpc getmdnpcname("warp4a#air2");
	hideonnpc getmdnpcname("warp5a#air2");

	end;
}

1@air1.gat,217,67,3	script	船長ペルロック#air1	873,{
	switch(HEROAIR_1QUE) {
	case 0:
		if(checkquest(120200)&8) {
			mes "‐ケイオスとアイリスが";
			mes "　船長らしき人物と話をしている‐";
			next;
			if(select("先を急ぐ","話を聞く") == 1) {
				mes "‐先を急ぐことにした‐";
				close2;
				set HEROAIR_1QUE,1;
				hideoffnpc getmdnpcname("ワイバーン#air1");
				hideoffnpc getmdnpcname("ワイバーンキッド#1air1");
				hideoffnpc getmdnpcname("レッサーワイバーン#1air");
				hideoffnpc getmdnpcname("スカイジャイロ#1air1");
				hideoffnpc getmdnpcname("スカイジャイロ#1air2");
				hideoffnpc getmdnpcname("スカイグレムリン#1air1");
				hideoffnpc getmdnpcname("スカイグレムリン#2air1");
				hideoffnpc getmdnpcname("スカイグレムリン#3air1");
				hideoffnpc getmdnpcname("スカイグレムリン#4air1");
				hideoffnpc getmdnpcname("スカイグレムリン#5air1");
				hideoffnpc getmdnpcname("スカイグレムリン#6air1");
				hideoffnpc getmdnpcname("スカイグレムリン#7air1");
				hideoffnpc getmdnpcname("スカイグレムリン#8air1");
				setnpcdisplay getmdnpcname("スカイグレムリン#1air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#2air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#3air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#4air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#5air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#6air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#7air1"),3183;
				setnpcdisplay getmdnpcname("スカイグレムリン#8air1"),3183;
				donpcevent getmdnpcname("船長ペルロック#air1")+ "::OnStart";
				end;
			}
		}
		cutin "h_iris02.bmp", 2;
		mes "[アイリス]";
		mes "うわあ～!!";
		mes "気持ちのいい風ー♪";
		mes "私たち空を飛んでるよ！";
		mes "やっほ～！";
		next;
		mes "[アイリス]";
		mes "魔法も使わずにこんな大きな船が";
		mes "空を飛ぶなんて、";
		mes "とっても不思議じゃない？";
		mes "ねぇ、ケイオス？";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "……。";
		next;
		cutin "h_iris02.bmp", 2;
		mes "[アイリス]";
		mes "……？　ケイオス？";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "…………。";
		mes "　";
		mes "^0000FF‐ケイオスは真剣な顔で";
		mes "　遠くの空を見つめている。";
		mes "　何か考え込んでいるようだ‐^000000";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "ケーイーオースー!?";
		mes "私の話を聞かないで……。";
		mes "何、ボーっと";
		mes "してるの……よっ!!";
		next;
		cutin "h_chaos03.bmp", 2;
		mes "[ケイオス]";
		mes "うわっ！";
		mes "　";
		mes "^0000FF‐アイリス怒りの";
		mes "　体当たりがケイオスの";
		mes "　背中を襲った!!‐^000000";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "ふん！　ぼーっとしてた罰よ！";
		next;
		cutin "h_chaos03.bmp", 2;
		mes "[ケイオス]";
		mes "ア、アイリス!!";
		mes "俺を殺す気かっ!!";
		mes "ちょっと考え事をしてた";
		mes "だけだろ!!";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "ふーんだ！";
		mes "私の話を聞かないケイオスが";
		mes "悪いんだからね！";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "おい!!";
		mes "船内で危険な悪ふざけは禁止だ!!";
		mes "これだから人間はダメなんだ。";
		mes "行儀が悪いんだよ、行儀が！";
		mes "それ以上ふざけると";
		mes "下に落としてしまうぞ!!";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "あ……船長！";
		mes "ご、ごめん！";
		mes "初めて飛行船に乗ったから";
		mes "はしゃいじゃった……。";
		next;
		cutin "h_iris02.bmp", 2;
		mes "[アイリス]";
		mes "ところで船長、";
		mes "こんな大きな飛行船が";
		mes "どうやって空に浮いてるの？";
		mes "不思議でしょうがないよ。";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "ん？　いい質問だ。";
		mes "少し難しい話になるが";
		mes "特別に教えてやる。";
		next;
		mes "[船長ペルロック]";
		mes "大型のボイラーで水を沸かせ、";
		mes "そこから出る蒸気の圧力で";
		mes "ピストンを動かし、歯車を回す。";
		mes "その力を利用し、";
		mes "タービンを動かして";
		mes "プロペラを回しているんだ。";
		next;
		cutin "h_iris02.bmp", 2;
		mes "[アイリス]";
		mes "へえ……!!";
		mes "そうやってこんな大きな船が";
		mes "空に浮いていたんだね。";
		next;
		mes "[アイリス]";
		mes "もっと不思議な力で";
		mes "空を飛んでいると思っていたから、";
		mes "神秘的なイメージは消えちゃったなぁ。";
		mes "もう少しそれらしい装置があると";
		mes "思っていたから";
		mes "ちょっとがっかり……。";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "ほほう、なかなか鋭い人間だな。";
		mes "そうだ。蒸気だけではこんな大きな船を";
		mes "空に浮かべる事は出来ない。";
		mes "だから^FF0000ルーン機関^000000という";
		mes "増幅器を使用している。";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "ルーン機関？";
		mes "それって一体……。";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "魔法のエネルギーを使用した装置だ。";
		mes "まあ、伝説にあるなんとかの心臓が";
		mes "割れた時に出来た物だという";
		mes "ありえない話もあるが……。";
		next;
		mes "[船長ペルロック]";
		mes "そう。";
		mes "俗にいう^0000FFユミルの涙^000000という石だ。";
		mes "それを蒸気機関のような運動機関に";
		mes "接続すると、その石から流れてくる";
		mes "ルーンでエネルギーを増幅できるんだ。";
		next;
		mes "[船長ペルロック]";
		mes "あの親指くらいの大きさの石ひとつで";
		mes "この船が動いていると言っても";
		mes "過言ではない。";
		mes "そのくらい強力な力を持っているんだ。";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "ユミルの涙……。";
		mes "たったあれだけの大きさで";
		mes "この船を動かしてる";
		mes "なんてすごい……。";
		next;
		cutin "ep14_roki02.bmp", 2;
		mes "[ロキ]";
		mes "お前達。";
		mes "無駄話はそこまでにしろ。";
		mes "……何かが来る。";
		next;
		cutin "ep14_roki02.bmp", 255;
		mes "[飛行船乗務員]";
		mes "非常事態!!　非常事態!!";
		mes "7時方向に";
		mes "ワイバーンの大部隊が出現!!";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "なにぃ!?";
		mes "ワイバーンだと!!";
		next;
		cutin "fly_felrock2.bmp", 255;
		mes "[飛行船乗務員]";
		mes "スカイグレムリンだ!!";
		mes "ワイバーンからスカイグレムリンが";
		mes "降りてきましたーっ!!";
		set HEROAIR_1QUE,1;
		hideoffnpc getmdnpcname("ワイバーン#air1");
		hideoffnpc getmdnpcname("ワイバーンキッド#1air1");
		hideoffnpc getmdnpcname("レッサーワイバーン#1air");
		hideoffnpc getmdnpcname("スカイジャイロ#1air1");
		hideoffnpc getmdnpcname("スカイジャイロ#1air2");
		hideoffnpc getmdnpcname("スカイグレムリン#1air1");
		hideoffnpc getmdnpcname("スカイグレムリン#2air1");
		hideoffnpc getmdnpcname("スカイグレムリン#3air1");
		hideoffnpc getmdnpcname("スカイグレムリン#4air1");
		hideoffnpc getmdnpcname("スカイグレムリン#5air1");
		hideoffnpc getmdnpcname("スカイグレムリン#6air1");
		hideoffnpc getmdnpcname("スカイグレムリン#7air1");
		hideoffnpc getmdnpcname("スカイグレムリン#8air1");
		setnpcdisplay getmdnpcname("スカイグレムリン#1air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#2air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#3air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#4air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#5air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#6air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#7air1"),3183;
		setnpcdisplay getmdnpcname("スカイグレムリン#8air1"),3183;
		next;
	case 1:
		cutin "h_chaos01.bmp", 2;
		mes "[ケイオス]";
		mes "おい……!!";
		mes "ワイバーンに人間が";
		mes "乗ってるぞ……!!";
		next;
		cutin "h_arcana02.bmp", 2;
		mes "[アルカナ]";
		mes "ウフフフフ！";
		mes "長らくお待たせいたしました!!";
		mes "^0000FF天才美女魔道士アルカナ^000000がお送りする";
		mes "空中モンスターサプライズショー!!";
		next;
		cutin "h_chaos03.bmp", 2;
		mes "[ケイオス]";
		mes "ショーだと!?";
		next;
		cutin "h_arcana02.bmp", 2;
		mes "[アルカナ]";
		mes "さあ……始めなさい。";
		mes "私のかわいいスカイグレムリン達!!";
		mes "楽しい楽しい";
		mes "ショータイムよっ!!";
		next;
		cutin "h_arcana02.bmp", 255;
		mes "[飛行船乗務員]";
		mes "せ、船長！　大変です！";
		mes "スカイグレムリンが船のあちこちで";
		mes "暴れ回っています!!";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "なんだと!!　スカイグレムリンが!?";
		mes "今すぐに船から引きはがして";
		mes "船を守れ!!　今すぐだ！";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "船長。";
		mes "そこまで興奮する必要は";
		mes "ないんじゃない？";
		mes "スカイグレムリンはただ機械に";
		mes "いたずらをしてるだけみたいだし。";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "バカな事を言うな!!";
		mes "ここは高度8000の上空なんだぞ!!";
		mes "ちょっとした故障でも";
		mes "私たちは死ぬかもしれないんだ！";
		next;
		cutin "fly_felrock2.bmp", 255;
		mes "[飛行船乗務員]";
		mes "うわっ!!　1番後方エンジンが!!";
		mes "……大変です！";
		mes "やつら機関室に向かっています！";
		mes "ルーン機関を守らなければ!!";
		next;
		cutin "fly_felrock2.bmp", 2;
		mes "[船長ペルロック]";
		mes "なんだと!!　私の武器はどこだ……!!";
		mes "おい。そこの人間たち!!";
		mes "私が船長室で武器を探してくる間、";
		mes "あの厄介者たちを食い止めろ!!";
		next;
		mes "[船長ペルロック]";
		mes "やつらが機関室に進入するのを";
		mes "防がなければならない!!";
		mes "ルーン機関が破壊されたら";
		mes "この船は墜落する!!";
		next;
		mes "[船長ペルロック]";
		mes "くそ!!";
		mes "私の武器さえあればあんな奴ら……!!";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "アイリス!!";
		mes "俺たちは機関室のある";
		mes "下の階まで降りるぞ！";
		mes "ロキとフェンリルはここを頼む！";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "う、うん！　分かった！";
		mes "一緒に行こう!!";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "悪いが、そこのお前も";
		mes "手伝ってくれ。";
		mes "俺たちは先に行く。";
		mes "機関室で落ち合おうぜ！";
		close2;
		cutin "h_chaos02.bmp", 255;
		donpcevent getmdnpcname("船長ペルロック#air1")+ "::OnStart";
		end;
	}
OnStart:
	initnpctimer;
	hideoffnpc getmdnpcname("warp1#air1");
	hideonnpc getmdnpcname("船長ペルロック#air1");
	hideonnpc getmdnpcname("ケイオス#air1");
	hideonnpc getmdnpcname("アイリス#air1");
	end;
OnTimer1000:
	announce "モンスターが飛行船を破壊しようとしています。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	end;
OnTimer4000:
	announce "飛行船の下の階へ降りてモンスターを倒してください。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	end;
OnTimer7000:
	stopnpctimer;
	announce "フロアにいるモンスターをすべて倒すと先へ進むことができるようになります。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	end;
}

1@air1.gat,248,54,0	script	warp1#air1	45,2,2,{
	hideonnpc getmdnpcname("warp1#air1");
	donpcevent getmdnpcname("mob#air1")+ "::OnStart";
	warp getmdmapname("1@air1.gat"),91,68;
	end;
}

1@air1.gat,215,67,5	script	アイリス#air1	666,{
	if(HEROAIR_1QUE == 0) {
		cutin "h_iris02.bmp", 2;
		mes "[アイリス]";
		mes "こんなに高い空を飛べるなんて、";
		mes "とってもステキだと思わない？";
		close2;
		cutin "h_iris02.bmp", 255;
		end;
	}
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "ここはフェンリルとロキに任せて";
	mes "急いで機関室に行かないと！";
	close2;
	cutin "h_iris01.bmp", 255;
	end;
}

1@air1.gat,214,66,5	script	ケイオス#air1	683,{
	if(HEROAIR_1QUE == 0) {
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "…………。";
		mes "　";
		mes "^0000FF‐ケイオスは真剣な顔で";
		mes "　遠くの空を見つめている。";
		mes "　何か考え込んでいるようだ‐^000000";
		close2;
		cutin "h_chaos02.bmp", 255;
		end;
	}
	cutin "h_chaos02.bmp", 2;
	mes "[ケイオス]";
	mes "悪いが、そこのお前も";
	mes "手伝ってくれ。";
	mes "俺たちは先に行く。";
	mes "機関室で落ち合おうぜ！";
	close2;
	cutin "h_chaos02.bmp", 255;
	end;
}

1@air1.gat,235,57,5	script	フェンリル#air1	664,{
	if(HEROAIR_1QUE == 0) {
		cutin "fenrir_a.bmp", 2;
		mes "[フェンリル]";
		mes "機械の力で空を飛べるなんて……。";
		mes "技術の発展は本当に素晴らしいわね。";
		next;
		mes "[フェンリル]";
		mes "だけどこの飛行船からは";
		mes "強力な力を感じる……。";
		mes "この飛行船が飛んでいるのは";
		mes "機械の力だけではないのかも";
		mes "しれないわね……。";
		close2;
		cutin "fenrir_a.bmp", 255;
		end;
	}
	cutin "fenrir_b.bmp", 2;
	mes "[フェンリル]";
	mes "私がここのモンスターの相手をするわ!!";
	mes "ケイオス、アイリスと一緒に";
	mes "急いで飛行船の下の階に";
	mes "いって頂戴!!";
	close2;
	cutin "fenrir_a.bmp", 255;
	end;
}

1@air1.gat,240,57,3	script	ロキ#air1	512,{
	if(HEROAIR_1QUE == 0) {
		cutin "ep14_roki02.bmp", 2;
		mes "[ロキ]";
		mes "……。";
		mes "ここは静かでいい。";
		close2;
		cutin "ep14_roki02.bmp", 255;
		end;
	}
	cutin "ep14_roki02.bmp", 2;
	mes "[ロキ]";
	mes "……ここは俺が防いでおく。";
	mes "飛行船の下の階に行け。";
	close2;
	cutin "ep14_roki02.bmp", 255;
	end;
}

1@air1.gat,213,75,5	script	ワイバーン#air1	2146,{}
1@air1.gat,218,78,3	script	ワイバーンキッド#1air1	3185,{}
1@air1.gat,208,78,5	script	レッサーワイバーン#1air	3186,{}
1@air1.gat,200,78,5	script	スカイロータージャイロ::スカイジャイロ#1air1	1392,{}
1@air1.gat,223,78,3	script	スカイロータージャイロ::スカイジャイロ#1air2	1392,{}
1@air1.gat,236,57,3	script	スカイグレムリン#1air1	844,{}
1@air1.gat,239,57,5	script	スカイグレムリン#2air1	844,{}
1@air1.gat,230,50,5	script	スカイグレムリン#3air1	844,{}
1@air1.gat,226,62,3	script	スカイグレムリン#4air1	844,{}
1@air1.gat,241,48,3	script	スカイグレムリン#5air1	844,{}
1@air1.gat,225,40,7	script	スカイグレムリン#6air1	844,{}
1@air1.gat,236,48,7	script	スカイグレムリン#7air1	844,{}
1@air1.gat,224,66,5	script	スカイグレムリン#8air1	844,{}

1@air1.gat,58,197,3	script	旅行客#1air1	887,{
	mes "[旅行客]";
	mes "……五月蝿いなあ……Zzz……。";
	mes "静かにしてくれ……。";
	mes "誰だよ、うなり声上げてるの……。";
	close;
}

1@air1.gat,49,169,5	script	旅行客#2air1	887,{
	mes "[旅行客]";
	mes "……くうう……ぐうう……。 ";
	mes "……はっ。";
	mes "寝息と、腹の虫がコラボした……。";
	mes "……腹減ったなあ……。";
	mes "でも起きるの面倒だよ……。";
	close;
}

1@air1.gat,42,205,3	script	小さな国の王#air1	956,{
	mes "[小さな国の王]";
	mes "……ううむ。 ";
	mes "流石に故郷のベットほど";
	mes "寝心地はよくないな……むにゃ。";
	mes "……ぐぅ……Zzzz……。";
	close;
}

1@air1.gat,43,191,4	script	王の護衛兵#1air1	105,{
	mes "[王の護衛兵]";
	mes "どんな事があっても";
	mes "気持ちよくお休みになっている陛下を";
	mes "起こしてはならない！";
	close;
}

1@air1.gat,39,191,4	script	王の護衛兵#2air1	105,{
	mes "[王の護衛兵]";
	mes "どんな事があっても";
	mes "気持ちよくお休みになっている陛下は";
	mes "寝つきがいい！";
	close;
}

1@air1.gat,93,193,3	script	飛行船乗務員#1air1	852,{
	if(HEROAIR_1QUE < 3) {
		mes "[飛行船乗務員]";
		mes "ここは機関室に行く入口だ。";
		mes "ここに入って来れないように";
		mes "やつらを防いでくれ！";
		close;
	}
	mes "[飛行船乗務員]";
	mes "やつらの侵入を許したのか!?";
	mes "ここは危険だから";
	mes "デッキまで退避するんだ！";
	close;
}

1@air1.gat,22,182,7	script	飛行船乗務員#2air1	852,{
	if(HEROAIR_1QUE < 3) {
		mes "[飛行船乗務員]";
		mes "ううう、モンスターが多すぎる！";
		mes "このままだと機関室がやられてしまう!!";
		close;
	}
	mes "[飛行船乗務員]";
	mes "機関室が壊されるなんて！";
	mes "あわわわわ……。";
	close;
}

1@air1.gat,120,62,3	script	旅行中の騎士#air1	733,{
	mes "[旅行中の騎士]";
	mes "何なんだこいつらは……。";
	mes "私が全部切ってしまおうか？";
	mes "……いや、金にもならないなら";
	mes "私がやる必要はないな……。";
	close2;
	emotion 54, getmdnpcname("旅行中の騎士#air1");
	end;
}

1@air1.gat,95,47,3	script	倒れた酔っ払い#air1	887,{
	mes "[倒れた酔っ払い]";
	mes "うああ……揺れる……！";
	mes "揺れるのは、私の";
	mes "恋心だけにしてくれ……むにゃ。";
	close2;
	emotion 53, getmdnpcname("倒れた酔っ払い#air1");
	end;
}

1@air1.gat,75,71,5	script	食事中のお金持ち#air1_0	55,{
	mes "[食事中のお金持ち]";
	mes "な、なんだこの怪物たちは?!";
	mes "私の大事な食事の時間の";
	mes "邪魔をするとは！";
	mes "ボディーガード！　どこにいる！";
	close;
}

1@air1.gat,61,88,5	script	無賃乗車した吟遊詩人#ai	51,{
	mes "[無賃乗車した吟遊詩人]";
	mes "ゴージャス～！";
	mes "ファンタスティック～!!";
	mes "このなんとも言えない光景を表現する";
	mes "歌詞を考えないと！";
	close;
}

1@air1.gat,46,61,5	script	飛行船食堂支配人#air1_0	61,{
	mes "[飛行船食堂支配人]";
	mes "凶悪な姿をしていますが、";
	mes "あのモンスターたちも";
	mes "私の食堂を訪ねて来たお客さまです。";
	mes "何にいたしますか？　お客様。";
	close;
}

1@air1.gat,28,67,5	script	ギャンブラーマグイー#ai	853,{
	mes "[ギャンブラーマグイー]";
	mes "おい！　カードに触るな！";
	mes "ルールを守れ！";
	next;
	mes "[ギャンブラーマグイー]";
	mes "ん……?!";
	mes "体が暖まって来て";
	mes "これからだと思ったのに、";
	mes "なんだよ！　このモンスターたちは?!";
	close;
}

1@air2.gat,120,62,3	script	旅行中の騎士#air2	733,{
	mes "[旅行中の騎士]";
	mes "爆発する！　飛ぶんだ……。";
	mes "あの向こうに見える飛行船に";
	mes "飛び移るんだあああ!!";
	mes "でも、防具や武器が重くて";
	mes "飛ぶ自信がないんだあああ!!";
	close;
}

1@air2.gat,95,47,3	script	倒れた酔っ払い#air2	887,{
	mes "[倒れた酔っ払い]";
	mes "揺れに続いて……";
	mes "なんだか煙たい……。";
	mes "どうなってんだ？";
	mes "……ぐうう……Zzz……。";
	close2;
	emotion 53, getmdnpcname("倒れた酔っ払い#air2");
	end;
}

1@air2.gat,75,71,5	script	食事中の金持ち#air2	55,{
	mes "[食事中の金持ち]";
	mes "助けてくれ!!";
	mes "金ならいくらでも出す！　お願いだ！";
	mes "私をここから脱出させてくれ!!";
	mes "ボディーガードは";
	mes "一体どこにいるんだ?!";
	next;
	mes "[食事中の金持ち]";
	mes "こんなことならフルコースを";
	mes "頼むんじゃなかった……。";
	mes "お陰で逃げ遅れてしまった……。";
	close;
}

1@air2.gat,61,88,5	script	無賃乗車した吟遊詩人#ai	51,{
	mes "[無賃乗車した吟遊詩人]";
	mes "ゴージャス～ファンタスティック～♪";
	mes "爆発する船も素晴らしい～♪";
	mes "ヒャッホーイ♪";
	close;
}

1@air2.gat,46,61,5	script	飛行船食堂支配人#air2_0	61,{
	mes "[飛行船食堂支配人]";
	mes "この船が……落ちるのか……";
	mes "私はこの船と運命を共にします。";
	mes "この船と私は……ひとつですから！";
	next;
	mes "[飛行船食堂支配人]";
	mes "なんてかっこうつけてる";
	mes "場合じゃないっ!!";
	mes "う、うわあ！　助けてえぇぇぇっ!!";
	close;
}

1@air2.gat,28,67,5	script	ギャンブラーマグイー#ai	853,{
	mes "[ギャンブラーマグイー]";
	mes "ギャンブラーの血が滾る!!";
	mes "って、おい……本当に熱いじゃないか!!";
	mes "火……だと……!?";
	mes "火事だ!!　火事だあああっ!!";
	mes "うひゃああああ～!!";
	close;
}

1@air1.gat,1,1,0	script	mob#air1	139,{
OnStart:
	areamonster getmdmapname("1@air1.gat"),77,57,82,65,"スカイビホルダー",3184,3,getmdnpcname("mob#air1")+ "::OnKilled1";
	areamonster getmdmapname("1@air1.gat"),77,57,82,65,"スカイロータージャイロ",3182,2,getmdnpcname("mob#air1")+ "::OnKilled1";
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air1")+ "::OnKilled1");
	if('@count > 0)
		end;
	announce "12時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air1.gat"),61,77,68,85,"スカイビホルダー",3184,5,getmdnpcname("mob#air1")+ "::OnKilled2";
	areamonster getmdmapname("1@air1.gat"),61,77,68,85,"スカイロータージャイロ",3182,3,getmdnpcname("mob#air1")+ "::OnKilled2";
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air1")+ "::OnKilled2");
	if('@count > 0)
		end;
	announce "9時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air1.gat"),20,60,28,66,"スカイビホルダー",3184,3,getmdnpcname("mob#air1")+ "::OnKilled3";
	areamonster getmdmapname("1@air1.gat"),20,60,28,66,"スカイロータージャイロ",3182,3,getmdnpcname("mob#air1")+ "::OnKilled3";
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air1")+ "::OnKilled3");
	if('@count > 0)
		end;
	announce "このフロアにはもうモンスターの気配がないようだ。下の階へ進もう。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	donpcevent getmdnpcname("mob#air2")+ "::OnStart";
	hideoffnpc getmdnpcname("warp2a#air1");
	hideoffnpc getmdnpcname("warp2b#air1");
	end;
}

1@air1.gat,104,72,0	warp	warp2a#air1	2,2,1@air1.gat,101,200
1@air1.gat,104,52,0	warp	warp2b#air1	2,2,1@air1.gat,101,176

1@air1.gat,1,1,0	script	mob#air2	139,{
OnStart:
	areamonster getmdmapname("1@air1.gat"),108,185,114,192,"スカイグレムリン",3183,3,getmdnpcname("mob#air2")+ "::OnKilled1";
	areamonster getmdmapname("1@air1.gat"),108,185,114,192,"レッサーワイバーン",3186,3,getmdnpcname("mob#air2")+ "::OnKilled1";
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air2")+ "::OnKilled1");
	if('@count > 0)
		end;
	announce "9時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air1.gat"),60,185,68,192,"スカイグレムリン",3183,3,getmdnpcname("mob#air2")+ "::OnKilled2";
	areamonster getmdmapname("1@air1.gat"),60,185,68,192,"レッサーワイバーン",3186,3,getmdnpcname("mob#air2")+ "::OnKilled2";
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air2")+ "::OnKilled2");
	if('@count > 0)
		end;
	announce "9時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air1.gat"),18,185,26,191,"スカイグレムリン",3183,3,getmdnpcname("mob#air2")+ "::OnKilled3";
	areamonster getmdmapname("1@air1.gat"),18,185,26,191,"レッサーワイバーン",3186,3,getmdnpcname("mob#air2")+ "::OnKilled3";
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("1@air1.gat"),getmdnpcname("mob#air2")+ "::OnKilled3");
	if('@count > 0)
		end;
	announce "このフロアにはもうモンスターの気配がないようだ。機関室入口へ向かおう。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	hideoffnpc getmdnpcname("アイリス#2air1");
	hideoffnpc getmdnpcname("ケイオス#2air1");
	hideoffnpc getmdnpcname("スカイグレムリン#2aair1");
	setnpcdisplay getmdnpcname("スカイグレムリン#2aair1"),3183;
	end;
}

1@air1.gat,93,188,5	script	スカイグレムリン#2aair1	844,{
	end;
OnStart:
OnTimer4000:
	initnpctimer;
	misceffect 106, getmdnpcname("スカイグレムリン#2aair1");
	end;
}

1@air1.gat,88,189,5	script	アイリス#2air1	666,{
	switch(HEROAIR_1QUE) {
	case 1:
		if(checkquest(120200)&8) {
			mes "‐ケイオスとアイリスが";
			mes "　機関室の前で話をしている‐";
			next;
			if(select("先を急ぐ","話を聞く") == 1) {
				mes "‐先を急ぐことにした‐";
				close2;
				setnpcdisplay getmdnpcname("スカイグレムリン#2aair1"),844;
				hideonnpc getmdnpcname("スカイグレムリン#2aair1");
				hideoffnpc getmdnpcname("warp3a#air1");
				hideoffnpc getmdnpcname("warp3b#air1");
				hideonnpc getmdnpcname("アイリス#2air1");
				hideonnpc getmdnpcname("ケイオス#2air1");
				announce "モンスターの気配がする。倒しながら戻ったほうがいいだろう。", 0x9, 0xffff00, 0x190, 12, 0, 0;
				donpcevent getmdnpcname("スカイグレムリン#2aair1")+ "::OnStart";
				donpcevent getmdnpcname("firecontrol#air")+ "::OnStart";
				end;
			}
		}
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "はぁ……はぁ……。";
		mes "ケイオス……。";
		mes "モンスターはこれで全部？";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "ああ……。";
		mes "モンスターは食い止められたようだな。";
		mes "何とか機関室は守りきったみたいだ。";
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "あ……！　ケイオス!!";
		mes "あそこっ!!";
		mes "スカイグレムリンが一匹、機関室に!!";
		next;
		cutin "h_chaos03.bmp", 2;
		mes "[ケイオス]";
		mes "……くっ!!";
		mes "あいつめ！";
		mes "あのスカイグレムリンを止めるぞ!!";
		next;
		cutin "h_chaos03.bmp", 255;
		mes "[スカイグレムリン]";
		mes "キイイイ……!!";
		mes "　";
		mes "‐スカイグレムリンは長い舌で";
		mes "　機関室に設置された機械に";
		mes "　穴を開け、外装を鋭い爪で";
		mes "　剥がしはじめた!!‐";
	case 2:
		if(HEROAIR_1QUE == 1) {
			set HEROAIR_1QUE,2;
			setnpcdisplay getmdnpcname("スカイグレムリン#2aair1"),844;
			hideonnpc getmdnpcname("スカイグレムリン#2aair1");
			next;
			misceffect 183, getmdnpcname("スカイグレムリン#2aair1");
			mes "^ff0000‐ジッ…ジジッ……";
			mes "　バチバチ……バチッ……";
			mes "　";
			mes "　ズガガガガーンッ!!‐^000000";
		}
		else {
			misceffect 183, getmdnpcname("スカイグレムリン#2aair1");
			mes "‐^ff0000……ドガガガ……ッ!!^000000";
			mes "　";
			mes "　どこからか激しい音が鳴り響いた!!‐";
		}
		next;
		cutin "h_iris01.bmp", 2;
		mes "[アイリス]";
		mes "きゃあああ!!";
		next;
		cutin "h_iris01.bmp", 255;
		mes "[飛行船乗務員]";
		mes "うわあああ！　ルーン機関が!!";
		mes "エンジン室が爆発した!!";
		mes "消火班！　早く火を消せ!!";
		next;
		mes "[飛行船乗務員]";
		mes "そこのあなた達!!";
		mes "ここは危険だ！　離れて！";
		mes "デッキへ上がってください!!!!";
		next;
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "ダメだ!!　ここは危険だ！";
		mes "まずはここを離れよう！";
		mes "アイリス、急げ!!";
		close2;
		cutin "h_chaos02.bmp", 255;
		set HEROAIR_1QUE,3;
		donpcevent getmdnpcname("アイリス#2air1")+ "::OnStart";
		donpcevent getmdnpcname("スカイグレムリン#2aair1")+ "::OnStart";
		donpcevent getmdnpcname("firecontrol#air")+ "::OnStart";
		end;
	}
	end;
OnStart:
	hideonnpc getmdnpcname("アイリス#2air1");
	hideonnpc getmdnpcname("ケイオス#2air1");
	hideoffnpc getmdnpcname("warp3a#air1");
	hideoffnpc getmdnpcname("warp3b#air1");
	donpcevent getmdnpcname("mob#air3")+ "::OnStart";
	announce "モンスターの気配を感じる!!　モンスターを倒しながら戻ろう!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	end;
}

1@air1.gat,88,187,5	script	ケイオス#2air1	683,{
	if(HEROAIR_1QUE == 1) {
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "アイリス！　大丈夫か？";
		mes "くそっ！";
		mes "数だけは多いな……。";
		close2;
		cutin "h_chaos02.bmp", 255;
		end;
	}
	cutin "h_chaos02.bmp", 2;
	mes "[ケイオス]";
	mes "ダメだ!!　ここは危険だ！";
	mes "まずはここを離れよう！";
	mes "アイリス、急げ!!";
	close2;
	cutin "h_chaos02.bmp", 255;
	end;
}

1@air2.gat,1,1,0	script	mob#air3	139,{
OnStart:
	areamonster getmdmapname("1@air2.gat"),109,59,115,66,"ワイバーンキッド",3185,3,getmdnpcname("mob#air3")+ "::OnKilled1";
	areamonster getmdmapname("1@air2.gat"),109,59,115,66,"スカイビホルダー",3184,3,getmdnpcname("mob#air3")+ "::OnKilled1";
	end;
OnKilled1:
	set '@count,getmapmobs(getmdmapname("1@air2.gat"),getmdnpcname("mob#air3")+ "::OnKilled1");
	if('@count > 0)
		end;
	announce "6時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air2.gat"),60,35,70,45,"ワイバーンキッド",3185,3,getmdnpcname("mob#air3")+ "::OnKilled2";
	areamonster getmdmapname("1@air2.gat"),60,35,70,45,"スカイビホルダー",3184,3,getmdnpcname("mob#air3")+ "::OnKilled2";
	end;
OnKilled2:
	set '@count,getmapmobs(getmdmapname("1@air2.gat"),getmdnpcname("mob#air3")+ "::OnKilled2");
	if('@count > 0)
		end;
	announce "9時方向に敵の気配を感じた!!", 0x9, 0xffff00, 0x190, 12, 0, 0;
	areamonster getmdmapname("1@air2.gat"),20,60,30,70,"ワイバーンキッド",3185,3,getmdnpcname("mob#air3")+ "::OnKilled3";
	areamonster getmdmapname("1@air2.gat"),20,60,30,70,"スカイビホルダー",3184,3,getmdnpcname("mob#air3")+ "::OnKilled3";
	end;
OnKilled3:
	set '@count,getmapmobs(getmdmapname("1@air2.gat"),getmdnpcname("mob#air3")+ "::OnKilled3");
	if('@count > 0)
		end;
	announce "この階にはもうモンスターの気配がないようだ。デッキまで上がろう。", 0x9, 0xffff00, 0x190, 12, 0, 0;
	hideoffnpc getmdnpcname("warp4a#air2");
	end;
}

1@air1.gat,103,200,0	warp	warp3a#air1	2,2,1@air2.gat,104,72
1@air1.gat,103,176,0	warp	warp3b#air1	2,2,1@air2.gat,104,52

1@air2.gat,1,1,0	script	firecontrol#air	139,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	misceffect 106, getmdnpcname("fire1#air2");
	misceffect 106, getmdnpcname("fire8#air2");
	misceffect 106, getmdnpcname("fire21#air2");
	misceffect 106, getmdnpcname("fire29#air2");
	end;
OnTimer1500:
	misceffect 106, getmdnpcname("fire2#air2");
	misceffect 106, getmdnpcname("fire9#air2");
	misceffect 106, getmdnpcname("fire22#air2");
	misceffect 106, getmdnpcname("fire30#air2");
	end;
OnTimer2000:
	misceffect 106, getmdnpcname("fire3#air2");
	misceffect 106, getmdnpcname("fire10#air2");
	misceffect 106, getmdnpcname("fire23#air2");
	end;
OnTimer2500:
	misceffect 106, getmdnpcname("fire4#air2");
	misceffect 106, getmdnpcname("fire11#air2");
	misceffect 106, getmdnpcname("fire24#air2");
	end;
OnTimer3000:
	misceffect 106, getmdnpcname("fire5#air2");
	misceffect 106, getmdnpcname("fire12#air2");
	misceffect 106, getmdnpcname("fire25#air2");
	end;
OnTimer3500:
	misceffect 106, getmdnpcname("fire6#air2");
	misceffect 106, getmdnpcname("fire13#air2");
	misceffect 106, getmdnpcname("fire26#air2");
	end;
OnTimer4000:
	misceffect 106, getmdnpcname("fire7#air2");
	misceffect 106, getmdnpcname("fire14#air2");
	misceffect 106, getmdnpcname("fire27#air2");
	end;
OnTimer4500:
	misceffect 106, getmdnpcname("fire15#air2");
	misceffect 106, getmdnpcname("fire28#air2");
	initnpctimer;
	end;
}

1@air2.gat,113,52,0	script	fire1#air2	139,{}
1@air2.gat,115,68,0	script	fire2#air2	139,{}
1@air2.gat,96,58,0	script	fire3#air2	139,{}
1@air2.gat,90,75,0	script	fire4#air2	139,{}
1@air2.gat,92,51,0	script	fire5#air2	139,{}
1@air2.gat,77,42,0	script	fire6#air2	139,{}
1@air2.gat,69,77,0	script	fire7#air2	139,{}
1@air2.gat,50,49,0	script	fire8#air2	139,{}
1@air2.gat,44,61,0	script	fire9#air2	139,{}
1@air2.gat,31,53,0	script	fire10#air2	139,{}
1@air2.gat,24,74,0	script	fire11#air2	139,{}
1@air2.gat,43,45,0	script	fire12#air2	139,{}
1@air2.gat,73,65,0	script	fire13#air2	139,{}
1@air2.gat,53,72,0	script	fire14#air2	139,{}
1@air2.gat,82,62,0	script	fire15#air2	139,{}
1@air2.gat,234,70,0	script	fire21#air2	139,{}
1@air2.gat,247,64,0	script	fire22#air2	139,{}
1@air2.gat,230,33,0	script	fire23#air2	139,{}
1@air2.gat,200,52,0	script	fire24#air2	139,{}
1@air2.gat,227,39,0	script	fire25#air2	139,{}
1@air2.gat,223,50,0	script	fire26#air2	139,{}
1@air2.gat,208,67,0	script	fire27#air2	139,{}
1@air2.gat,208,39,0	script	fire28#air2	139,{}
1@air2.gat,238,70,0	script	fire29#air2	139,{}
1@air2.gat,238,32,0	script	fire30#air2	139,{}

1@air2.gat,88,67,0	warp	warp4a#air2	2,2,1@air2.gat,247,53

1@air2.gat,213,75,5	script	ワイバーン#air2	2146,{}

1@air2.gat,235,59,3	script	ワイバーン#2air2	2146,{}
1@air2.gat,235,49,3	script	ワイバーン#3air2	2146,{}
1@air2.gat,218,78,3	script	ワイバーンキッド#1air2	3185,{}
1@air2.gat,208,78,5	script	レッサーワイバーン#2air	3186,{}
1@air2.gat,200,78,5	script	スカイロータージャイロ	1392,{}
1@air2.gat,223,78,3	script	スカイロータージャイロ	1392,{}
1@air2.gat,236,57,3	script	スカイグレムリン#1air2	844,{}
1@air2.gat,239,57,5	script	スカイグレムリン#2air2	844,{}
1@air2.gat,230,50,5	script	スカイグレムリン#3air2	844,{}
1@air2.gat,226,62,3	script	スカイグレムリン#4air2	844,{}
1@air2.gat,241,48,3	script	スカイグレムリン#5air2	844,{}
1@air2.gat,225,40,7	script	スカイグレムリン#6air2	844,{}
1@air2.gat,236,48,7	script	スカイグレムリン#7air2	844,{}
1@air2.gat,224,66,5	script	スカイグレムリン#8air2	844,{}

1@air2.gat,229,56,5	script	ロキ#air2	512,{
	cutin "ep14_roki02.bmp", 2;
	mes "[ロキ]";
	mes "次から次へと……面倒なやつらだ。";
	close2;
	cutin "ep14_roki02.bmp", 255;
	end;
}

1@air2.gat,229,54,5	script	フェンリル#air2	664,{
	if(checkquest(120200)&8) {
		mes "‐フェンリルがモンスターと";
		mes "　戦っている‐";
		next;
		if(select("先を急ぐ","話を聞く") == 1) {
			mes "‐先を急ぐことにした‐";
			close2;
			hideonnpc getmdnpcname("ロキ#air2");
			setnpcdisplay getmdnpcname("ワイバーン#2air2"),844;
			setnpcdisplay getmdnpcname("ワイバーン#3air2"),844;
			hideonnpc getmdnpcname("ワイバーン#2air2");
			hideonnpc getmdnpcname("ワイバーン#3air2");
			hideonnpc getmdnpcname("アイリス#air2");
			hideonnpc getmdnpcname("フェンリル#air2");
			donpcevent getmdnpcname("mob#air4")+ "::OnStart";
			end;
		}
	}
	cutin "fenrir_a.bmp", 2;
	mes "[フェンリル]";
	mes "……こいつら";
	mes "いくら倒してもキリが無いわね。";
	next;
	cutin "h_guardian2.bmp", 1;
	mes "[？？？？？]";
	mes "やっぱり、私たちが感じた力は";
	mes "間違ってなかったわね。";
	mes "悪の波動を追って遠い所まで";
	mes "来た甲斐があったようだわ！";
	next;
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "……誰なの!!";
	next;
	cutin "h_guardian2.bmp", 1;
	mes "[？？？？？]";
	mes "紹介しよう……。";
	next;
	cutin "h_guardian1.bmp", 1;
	mes "[？？？？？]";
	mes "燃える赤がトレードマーク！";
	mes "シヴァ！";
	mes "センターは譲れない!!";
	mes "バサラ！";
	mes "サラサラヘアーの金髪が目印♪";
	mes "ラクシュミー！";
	next;
	mes "[ガーディアンヒロインズ]";
	mes "私たちは無敵のレンジャー！";
	mes "その名も……";
	mes "^FF0000ガーディアンヒロインズ!!^000000";
	next;
	cutin "h_chaos03.bmp", 2;
	mes "[ケイオス]";
	mes "……。";
	next;
	cutin "fenrir_a.bmp", 2;
	mes "[フェンリル]";
	mes "……。";
	next;
	cutin "h_guardian1.bmp", 1;
	mes "[シヴァ]";
	mes "あれ？　反応悪すぎじゃね？";
	mes "どうしてみんな黙ってんの……？";
	mes "やり過ぎたってこと……？";
	next;
	mes "[バサラ]";
	mes "ふふっ、違うね。";
	mes "あまりにもかっこいい登場だったから";
	mes "みんな放心してるんだよ。";
	next;
	mes "[ラクシュミー]";
	mes "そうですわ。";
	mes "英雄の登場でこのくらいの演出は";
	mes "当たり前でしてよ。";
	next;
	cutin "h_iris02.bmp", 2;
	mes "[アイリス]";
	mes "ぷ……ッ！";
	mes "アハハハハハハ!!!!";
	next;
	mes "[アイリス]";
	mes "何なの？　この人たち！";
	mes "ヒロインズ？　英雄??";
	mes "しかもあの服見た!?";
	mes "舞台衣装のつもり？";
	mes "英雄じゃなくて芸人じゃない？";
	next;
	cutin "h_guardian3.bmp", 1;
	mes "[ラクシュミー]";
	mes "あなた、この服の価値を";
	mes "ご存じないからそんな事を";
	mes "仰っていますのね？";
	mes "これだから流行に疎い女性は";
	mes "困りますわ。";
	next;
	mes "[バサラ]";
	mes "みんな！　今は悠長に";
	mes "おしゃべりしてる場合じゃない！";
	mes "早く悪の波動を消し飛ばすわよ!!";
	next;
	mes "[シヴァ]";
	mes "了解だぜ、バサラ！";
	mes "速攻で終わらせてやる……。";
	mes "必殺！　風魔手裏剣!!";
	mes "セイッ！　ヤッ！";
	next;
	cutin "h_iris02.bmp", 255;
	mes "‐^ff0000ドガガガガッ！^000000‐";
	mes "　";
	mes "‐^0000FFシヴァの放った風魔手裏剣が";
	mes "　設備に命中し崩れた!!^000000‐";
	donpcevent getmdnpcname("フェンリル#air2")+ "::OnEff1";
	next;
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "な、何なのこいつら！";
	mes "完全に狂ってる……。";
	next;
	cutin "h_arcana02.bmp", 2;
	mes "[アルカナ]";
	mes "これはこれは。";
	mes "予想外の協力者がいましたね。";
	mes "フフッ、思っていた以上に";
	mes "楽しいパーティーになりそうですね。";
	next;
	cutin "fenrir_a.bmp", 2;
	mes "[フェンリル]";
	mes "そのパーティー、この辺で";
	mes "終わりにして欲しいわね。";
	mes "貴女は……";
	mes "フレイヤの指示で来たの？";
	next;
	cutin "h_arcana02.bmp", 2;
	mes "[アルカナ]";
	mes "あらら、生意気ですねぇ。";
	mes "人間の分際でフレイヤ様の名前を";
	mes "軽々しく口にするとは……。";
	next;
	cutin "fenrir_a.bmp", 2;
	mes "[フェンリル]";
	mes "やっぱり……";
	mes "フレイヤの手先のようね。";
	next;
	cutin "h_arcana01.bmp", 2;
	mes "[アルカナ]";
	mes "口のきき方には気をつけるように";
	mes "いわれませんでしたか？";
	mes "あまり無礼がすぎると……";
	mes "天罰を受けることになりますよ？";
	next;
	cutin "fenrir_b.bmp", 2;
	mes "[フェンリル]";
	mes "……!!";
	donpcevent getmdnpcname("フェンリル#air2")+ "::OnEff1";
	next;
	cutin "h_arcana02.bmp", 2;
	mes "[アルカナ]";
	mes "面白いものを";
	mes "ご覧にいれましょう。";
	mes "これを見て少しは";
	mes "頭を冷やしてくださいね？";
	next;
	cutin "fenrir_b.bmp", 255;
	mes "[ワイバーン]";
	mes "クオオオオ……ッ!!";
	next;
	cutin "fenrir_b.bmp", 2;
	mes "[フェンリル]";
	mes "ワイバーンのその動作……";
	mes "まさかブレスを!?";
	next;
	cutin "h_arcana02.bmp", 2;
	mes "[アルカナ]";
	mes "ビ・ン・ゴ♪";
	mes "まあ、この船に火を";
	mes "つける程度ならこの火力で";
	mes "問題ないでしょう。";
	next;
	cutin "fenrir_b.bmp", 2;
	mes "[フェンリル]";
	mes "だ、だめ!!";
	next;
	hideoffnpc getmdnpcname("ロキ#air2");
	misceffect 183, getmdnpcname("ロキ#air2");
	cutin "fenrir_b.bmp", 255;
	mes "‐ワイバーンの炎が放たれた";
	mes "　その瞬間……!!";
	mes "　ロキが自分の体で";
	mes "　ブレスを全て受け止めた!!‐";
	next;
	cutin "fenrir_a.bmp", 2;
	mes "[フェンリル]";
	mes "……?!";
	mes "ロキ!!";
	next;
	cutin "ep14_roki02.bmp", 2;
	mes "[ロキ]";
	mes "……フン。";
	mes "この程度とはな。";
	next;
	cutin "h_arcana02.bmp", 2;
	mes "[アルカナ]";
	mes "あら……。";
	mes "ワイバーンのブレスを弾くとは……。";
	mes "少しは骨のある人間が現れましたね。";
	mes "でもこいつらの相手はどうでしょう？";
	next;
	cutin "ep14_roki02.bmp", 255;
	mes "[ワイバーン]";
	mes "クオオオ……!!";
	next;
	cutin "ep14_roki02.bmp", 2;
	mes "[ロキ]";
	mes "おい、そこのお前。";
	mes "一匹は俺が相手をする。";
	mes "お前はあいつの相手をしてくれ。";
	close2;
	cutin "ep14_roki02.bmp", 255;
	hideonnpc getmdnpcname("ロキ#air2");
	setnpcdisplay getmdnpcname("ワイバーン#2air2"),844;
	setnpcdisplay getmdnpcname("ワイバーン#3air2"),844;
	hideonnpc getmdnpcname("ワイバーン#2air2");
	hideonnpc getmdnpcname("ワイバーン#3air2");
	hideonnpc getmdnpcname("アイリス#air2");
	hideonnpc getmdnpcname("フェンリル#air2");
	donpcevent getmdnpcname("mob#air4")+ "::OnStart";
	end;
OnEff1:
	misceffect 183, getmdnpcname("スカイグレムリン#1air2");
	sleep 1000;
	misceffect 183, getmdnpcname("スカイグレムリン#2air2");
	sleep 1000;
	misceffect 183, getmdnpcname("スカイグレムリン#3air2");
	end;
}

1@air2.gat,241,54,3	script	アイリス#air2	666,{
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "せっかくの素敵な空の旅だったのに！";
	mes "どうしてこーなっちゃうワケ!?";
	close2;
	cutin "h_iris01.bmp", 255;
	end;
}

1@air2.gat,232,51,5	script	アイリス#2air2	666,{
	if(checkquest(120200)&8) {
		mes "‐アイリスがスカイグレムリンと";
		mes "　戦っている‐";
		next;
		if(select("先を急ぐ","話を聞く") == 1) {
			mes "‐船長が暴れているようだ。";
			mes "　どうしようか……‐";
			while(1) {
				next;
				switch(select("離れて落ち着くのを待つ",
							"^0000ff説得する(戦闘なし)^000000",
							"^ff0000怒りの船長と戦闘！^000000(難易度：^0000ff低^000000)",
							"^ff0000暴走した船長と戦闘！^000000(難易度：^ff0000高^000000)"
				)) {
				case 1:
					mes "‐船長は暴れ続けている。";
					mes "　どうしようか……‐";
					continue;
				case 2:
					mes "‐あなたは船長に呼びかけ、";
					mes "　説得を試みた。";
					mes "　船長は我に返り、攻撃の手を止めた‐";
					close2;
					set HEROAIR_1QUE,4;
					hideonnpc getmdnpcname("船長ペルロック#air2");
					hideonnpc getmdnpcname("アイリス#2air2");
					setnpcdisplay getmdnpcname("スカイグレムリン#1air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#2air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#3air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#4air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#5air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#6air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#7air2"),844;
					setnpcdisplay getmdnpcname("スカイグレムリン#8air2"),844;
					hideonnpc getmdnpcname("スカイグレムリン#1air2");
					hideonnpc getmdnpcname("スカイグレムリン#2air2");
					hideonnpc getmdnpcname("スカイグレムリン#3air2");
					hideonnpc getmdnpcname("スカイグレムリン#4air2");
					hideonnpc getmdnpcname("スカイグレムリン#5air2");
					hideonnpc getmdnpcname("スカイグレムリン#6air2");
					hideonnpc getmdnpcname("スカイグレムリン#7air2");
					hideonnpc getmdnpcname("スカイグレムリン#8air2");
					hideoffnpc getmdnpcname("ケイオス#air2");
					hideoffnpc getmdnpcname("船長ペルロック#2air2");
					end;
				case 3:
					mes "‐あなたは武器を構え、";
					mes "　怒りの船長へ向かって行った！‐";
					close2;
					set HEROAIR_1QUE,5;
					cutin "h_iris01.bmp", 255;
					donpcevent getmdnpcname("アイリス#2air2")+ "::OnStart";
					donpcevent getmdnpcname("callboss#air")+ "::OnStart1";
					end;
				case 4:
					mes "‐あなたは武器を構え、";
					mes "　暴走した船長へ向かって行った！‐";
					close2;
					set HEROAIR_1QUE,6;
					cutin "h_iris01.bmp", 255;
					donpcevent getmdnpcname("アイリス#2air2")+ "::OnStart";
					donpcevent getmdnpcname("callboss#air")+ "::OnStart2";
					end;
				}
			}
		}
	}
	mes "[スカイグレムリン]";
	mes "キイイイッ……";
	mes "クワアアアア～ッ!!";
	next;
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "きゃああ！";
	mes "こいつらまだこんなにいる!!";
	mes "もう!!";
	mes "しつこいわね!!";
	next;
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "見つけたぞ！　私の武器！";
	mes "ふふふふふ!!";
	next;
	mes "[船長ペルロック]";
	mes "私の船で騒ぎを起こすとどうなるか、";
	mes "思い知らせてやる！";
	next;
	mes "[船長ペルロック]";
	mes "特別に製作した";
	mes "エクソダスジョーカーXIII世";
	mes "ドゥームライフルで終わらせてくれる!!";
	next;
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "ちょ、ちょっと船長!!";
	mes "本当にそれをココで撃つ気なの!?";
	next;
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "当たり前だ！";
	mes "ふははははははははは！";
	next;
	cutin "h_iris01.bmp", 255;
	mes "‐^ff0000パン！　パパン！　パンッ！^000000‐";
	next;
	misceffect 183, getmdnpcname("スカイグレムリン#1air2");
	misceffect 183, getmdnpcname("スカイグレムリン#2air2");
	misceffect 183, getmdnpcname("スカイグレムリン#3air2");
	setnpcdisplay getmdnpcname("スカイグレムリン#1air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#2air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#3air2"),844;
	hideonnpc getmdnpcname("スカイグレムリン#1air2");
	hideonnpc getmdnpcname("スカイグレムリン#2air2");
	hideonnpc getmdnpcname("スカイグレムリン#3air2");
	mes "[スカイグレムリン]";
	mes "クエエッ!!";
	next;
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "くはははは！";
	mes "どうだ？　俺の銃の威力は!!";
	mes "くわっはははは!!";
	next;
	cutin "h_iris01.bmp", 255;
	mes "‐^ff0000パン！　パパン！　パンッ！^000000‐";
	next;
	misceffect 183, getmdnpcname("スカイグレムリン#1air2");
	misceffect 183, getmdnpcname("スカイグレムリン#2air2");
	misceffect 183, getmdnpcname("スカイグレムリン#3air2");
	mes "[飛行船乗務員]";
	mes "わあああ……！";
	mes "エ、エンジンが！";
	next;
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "なんだとっ!!";
	mes "ヤツら怒ってさらに";
	mes "エンジンを攻撃しはじめたぞ!?";
	next;
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "あなたが原因よ!!";
	mes "船長っ!!";
	next;
	cutin "h_iris01.bmp", 255;
	mes "‐^ff0000パン！　パパン！　パンッ！^000000‐";
	next;
	misceffect 183, getmdnpcname("スカイグレムリン#1air2");
	misceffect 183, getmdnpcname("スカイグレムリン#2air2");
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "こいつら！";
	mes "ゆるさん!!　全滅させてやる！";
	mes "くははははーっ!!";
	next;
	misceffect 183, getmdnpcname("スカイグレムリン#3air2");
	cutin "h_iris01.bmp", 2;
	mes "[アイリス]";
	mes "ああ……だめ！";
	mes "船長のせいで船が沈みそう……。";
	mes "暴走してる船長を止めないと!";
	next;
	mes "[アイリス]";
	mes "どうすればいいかって？";
	mes "そうね……。";
	mes "死なない程度に衝撃を与えれば";
	mes "正気に戻るかも……。";
	mes "飛行船が壊れる前に、お願い！";
	while(1) {
		next;
		switch(select("離れて落ち着くのを待つ",
					"^0000ff説得する(戦闘なし)^000000",
					"^ff0000怒りの船長と戦闘！^000000(難易度：^0000ff低^000000)",
					"^ff0000暴走した船長と戦闘！^000000(難易度：^ff0000高^000000)"
		)) {
		case 1:
			mes "‐船長は暴れ続けている。";
			mes "　どうしようか……‐";
			continue;
		case 2:
			mes "‐あなたは船長に呼びかけ、";
			mes "　説得を試みた。";
			mes "　船長は我に返り、攻撃の手を止めた‐";
			close2;
			set HEROAIR_1QUE,4;
			hideonnpc getmdnpcname("船長ペルロック#air2");
			hideonnpc getmdnpcname("アイリス#2air2");
			setnpcdisplay getmdnpcname("スカイグレムリン#1air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#2air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#3air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#4air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#5air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#6air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#7air2"),844;
			setnpcdisplay getmdnpcname("スカイグレムリン#8air2"),844;
			hideonnpc getmdnpcname("スカイグレムリン#1air2");
			hideonnpc getmdnpcname("スカイグレムリン#2air2");
			hideonnpc getmdnpcname("スカイグレムリン#3air2");
			hideonnpc getmdnpcname("スカイグレムリン#4air2");
			hideonnpc getmdnpcname("スカイグレムリン#5air2");
			hideonnpc getmdnpcname("スカイグレムリン#6air2");
			hideonnpc getmdnpcname("スカイグレムリン#7air2");
			hideonnpc getmdnpcname("スカイグレムリン#8air2");
			hideoffnpc getmdnpcname("ケイオス#air2");
			hideoffnpc getmdnpcname("船長ペルロック#2air2");
			end;
		case 3:
			mes "‐あなたは武器を構え、";
			mes "　怒りの船長へ向かって行った！‐";
			close2;
			set HEROAIR_1QUE,5;
			cutin "h_iris01.bmp", 255;
			donpcevent getmdnpcname("アイリス#2air2")+ "::OnStart";
			donpcevent getmdnpcname("callboss#air")+ "::OnStart1";
			end;
		case 4:
			mes "‐あなたは武器を構え、";
			mes "　暴走した船長へ向かって行った！‐";
			close2;
			set HEROAIR_1QUE,6;
			cutin "h_iris01.bmp", 255;
			donpcevent getmdnpcname("アイリス#2air2")+ "::OnStart";
			donpcevent getmdnpcname("callboss#air")+ "::OnStart2";
			end;
		}
	}
OnStart:
	hideonnpc getmdnpcname("船長ペルロック#air2");
	hideonnpc getmdnpcname("アイリス#2air2");
	setnpcdisplay getmdnpcname("スカイグレムリン#1air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#2air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#3air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#4air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#5air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#6air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#7air2"),844;
	setnpcdisplay getmdnpcname("スカイグレムリン#8air2"),844;
	hideonnpc getmdnpcname("スカイグレムリン#1air2");
	hideonnpc getmdnpcname("スカイグレムリン#2air2");
	hideonnpc getmdnpcname("スカイグレムリン#3air2");
	hideonnpc getmdnpcname("スカイグレムリン#4air2");
	hideonnpc getmdnpcname("スカイグレムリン#5air2");
	hideonnpc getmdnpcname("スカイグレムリン#6air2");
	hideonnpc getmdnpcname("スカイグレムリン#7air2");
	hideonnpc getmdnpcname("スカイグレムリン#8air2");
	end;
}

1@air2.gat,1,1,0	script	mob#air4	139,{
OnStart:
	monster getmdmapname("1@air2.gat"),235,49,"ワイバーン",3187,1,getmdnpcname("mob#air4")+ "::OnKilled";
	end;
OnKilled:
	hideoffnpc getmdnpcname("アイリス#2air2");
	hideoffnpc getmdnpcname("船長ペルロック#air2");
	setnpcdisplay getmdnpcname("スカイグレムリン#1air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#2air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#3air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#4air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#5air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#6air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#7air2"),3183;
	setnpcdisplay getmdnpcname("スカイグレムリン#8air2"),3183;
	hideoffnpc getmdnpcname("スカイグレムリン#1air2");
	hideoffnpc getmdnpcname("スカイグレムリン#2air2");
	hideoffnpc getmdnpcname("スカイグレムリン#3air2");
	hideoffnpc getmdnpcname("スカイグレムリン#4air2");
	hideoffnpc getmdnpcname("スカイグレムリン#5air2");
	hideoffnpc getmdnpcname("スカイグレムリン#6air2");
	hideoffnpc getmdnpcname("スカイグレムリン#7air2");
	hideoffnpc getmdnpcname("スカイグレムリン#8air2");
	end;
}

1@air2.gat,1,1,0	script	callboss#air	139,{
OnStart1:
	monster getmdmapname("1@air2.gat"),247,51,"怒りの船長ペルロック",3188,1,getmdnpcname("callboss#air")+ "::OnKilled";
	end;
OnStart2:
	monster getmdmapname("1@air2.gat"),247,51,"暴走した船長ペルロック",3181,1,getmdnpcname("callboss#air")+ "::OnKilled";
	end;
OnKilled:
	hideoffnpc getmdnpcname("ケイオス#air2");
	hideoffnpc getmdnpcname("船長ペルロック#2air2");
	end;
}

1@air2.gat,247,51,3	script	船長ペルロック#air2	873,{
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "船を荒らす不届きもの達め！";
	mes "私の武器で葬ってやろう!!";
	close2;
	cutin "fly_felrock2.bmp", 255;
	end;
}

1@air2.gat,243,58,3	script	船長ペルロック#2air2	873,{
	cutin "fly_felrock2.bmp", 2;
	mes "[船長ペルロック]";
	mes "私の船を……!!";
	mes "ゆるせん!!!!";
	close2;
	cutin "fly_felrock2.bmp", 255;
	end;
}

1@air2.gat,239,58,5	script	ケイオス#air2	683,{
	if(HEROAIR_1QUE >= 4 && HEROAIR_1QUE <= 6) {
		if(checkquest(120200)&8) {
			mes "‐船長は正気を取り戻したようで";
			mes "　ケイオスと話をしている‐";
			next;
			if(select("先を急ぐ","話を聞く") == 1) {
				mes "‐先を急ぐことにした‐";
				close2;
				set '@skip,1;
			}
		}
		if('@skip == 0) {
			cutin "fly_felrock2.bmp", 2;
			mes "[船長ペルロック]";
			mes "クッ、無駄に撃ち過ぎてしまった。";
			mes "おかげでスカイグレムリンが";
			mes "かなり消えたようだけどな。";
			mes "フフフフフフ……。";
			next;
			cutin "h_iris01.bmp", 2;
			mes "[アイリス]";
			mes "ちょっと!!";
			mes "大体は船長のせいで";
			mes "船が壊れたのよ!?";
			next;
			cutin "h_arcana02.bmp", 2;
			mes "[アルカナ]";
			mes "私の代わりに船を壊してくれて";
			mes "助かりました。";
			mes "ふむ、まあ……";
			mes "このくらいでいいでしょう。";
			next;
			mes "[アルカナ]";
			mes "それでは、私たちはこの辺で。";
			next;
			cutin "h_guardian1.bmp", 1;
			mes "[ラクシュミー]";
			mes "あら……。";
			mes "ねえ、バサラ。";
			mes "あの人たち、";
			mes "撤収するみたいですわよ？";
			next;
			mes "[バサラ]";
			mes "ふーん。";
			mes "奴らやっと私たちの実力に";
			mes "気が付いたようね!!";
			mes "おほほほほ!!";
			next;
			mes "[シヴァ]";
			mes "それじゃあ……";
			mes "最後の風魔手裏剣ってな!!";
			next;
			cutin "fly_felrock2.bmp", 255;
			mes "‐シュッ！　カカカカッ！";
			mes "　";
			mes "　シヴァの投げた風魔手裏剣は";
			mes "　フェンリルの居た足場を、";
			mes "　崩壊させた!!‐";
			next;
			misceffect 183, getmdnpcname("スカイグレムリン#1air2");
			misceffect 183, getmdnpcname("スカイグレムリン#2air2");
			misceffect 183, getmdnpcname("スカイグレムリン#3air2");
			cutin "fenrir_b.bmp", 2;
			mes "[フェンリル]";
			mes "……!!";
			next;
			mes "[フェンリル]";
			mes "くっ……！　落ちるッ!!";
			mes "あと少しなのに手が……";
			mes "届かない……!!";
			next;
			mes "[フェンリル]";
			mes "……ここで終わってしまうの？";
			mes "あの時のように……";
			mes "また届かない場所に";
			mes "いってしまうの……？";
			mes "…ケイオス……。";
			next;
			cutin "ep14_roki02.bmp", 2;
			mes "[ロキ]";
			mes "……世話が焼ける。";
			next;
			cutin "ep14_roki02.bmp", 255;
			mes "‐足場が崩れ、";
			mes "　空中に投げ出されたフェンリルの手を";
			mes "　ロキがつかんだ‐";
			next;
			cutin "fenrir_b.bmp", 2;
			mes "[フェンリル]";
			mes "ロ……キ……？";
			next;
			cutin "ep14_roki02.bmp", 2;
			mes "[ロキ]";
			mes "何をしている。さあ、早く登れ。";
			next;
			cutin "fly_felrock2.bmp", 255;
			mes "[飛行船乗務員]";
			mes "直にこの船は墜落します！";
			mes "幸い、墜落まで、猶予がありますので";
			mes "落ち着いて脱出してください!!";
			next;
			cutin "fly_felrock2.bmp", 2;
			mes "[船長ペルロック]";
			mes "あいつら！　覚えてろよ!!";
			mes "みんな、救命艇に搭乗するんだ！";
			mes "乗客を最優先だ!!";
			mes "搭乗が完了した救命艇は";
			mes "船から出発させろ!!";
			next;
			cutin "fly_felrock2.bmp", 255;
			mes "[飛行船乗務員]";
			mes "はい、船長!!";
			mes "さあ乗客のみなさん、こちらです！";
			mes "救命艇へ移動してください！";
			next;
			cutin "h_chaos01.bmp", 2;
			mes "[ケイオス]";
			mes "これが本当の";
			mes "乗りかかった船ってヤツか？";
			mes "モンスターは俺たちが何とかする！";
			mes "みんな慌てず、";
			mes "落ち着いて移動してくれよ！";
			next;
			cutin "h_guardian1.bmp", 1;
			mes "[バサラ]";
			mes "私たちもスカイグレムリンの";
			mes "相手をしている場合じゃないな。";
			next;
			mes "[バサラ]";
			mes "さらに大きな悪の波動を感じる。";
			mes "後はこいつらに任せる事にしよう。";
			mes "みんな行くぞ！";
			next;
			mes "[ラクシュミー＆シヴァ]";
			mes "了解!!　レンジャー飛行形態!!";
			next;
			cutin "h_iris01.bmp", 2;
			mes "[アイリス]";
			mes "ちょ……ちょっと!!";
			mes "あんたたち船をこんな状態にして";
			mes "逃げる気なの!?";
			next;
			mes "[アイリス]";
			mes "次にどこかで会ったら本気で";
			mes "許さないから覚悟しときなさいよ!?";
			mes "この田舎者の英雄気取りっ!!";
			next;
			cutin "h_guardian3.bmp", 1;
			mes "[ガーディアンヒロインズ]";
			mes "……田舎者の英雄気取り……？";
			next;
			mes "[ガーディアンヒロインズ]";
			mes "正義の道をけなす者に……";
			mes "私たちは正義の審判を";
			mes "下さなければ、いけないようね。";
			next;
			mes "[ガーディアンヒロインズ]";
			mes "悪党め!!　くらえ風魔手裏剣!!";
			next;
			cutin "h_iris01.bmp", 255;
			mes "‐シュッ！　カカカカッ！";
			mes "　";
			mes "　ガーディアンヒロインズの";
			mes "　投げた風魔手裏剣はアイリスの";
			mes "　足場を崩壊させた!!‐";
			next;
			misceffect 183, getmdnpcname("スカイグレムリン#1air2");
			misceffect 183, getmdnpcname("スカイグレムリン#2air2");
			misceffect 183, getmdnpcname("スカイグレムリン#3air2");
			cutin "h_iris01.bmp", 2;
			mes "[アイリス]";
			mes "きゃあああああ!!";
			next;
			cutin "h_guardian1.bmp", 1;
			mes "[ガーディアンヒロインズ]";
			mes "あははははははははっ!!";
			mes "ざまあみろ!!　行くよ!!";
			next;
			cutin "h_iris01.bmp", 2;
			mes "[アイリス]";
			mes "あ～い～つ～ら～!!";
			mes "なんてヤツらなのっ！";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "アイリス!!　こっちに来い!!";
			mes "早くここを片付けて、";
			mes "俺たちも脱出するぞ！";
			next;
			cutin "h_iris02.bmp", 2;
			mes "[アイリス]";
			mes "確か、こういう時は";
			mes "「おかし」が大事なんだよね！";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "……お菓子？";
			mes "今は別に腹は空いてないぞ？";
			next;
			cutin "h_iris02.bmp", 2;
			mes "[アイリス]";
			mes "お菓子じゃなくて「おかし」！";
			mes "避難をする時に大事な行動の";
			mes "おさない、かけない、しゃべらない！";
			mes "３つの頭文字を取った言葉だよ。";
			mes "小さい頃に教わらなかった？";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "それなら……";
			mes "おさない、はしらない、しゃべらない";
			mes "で、「おはし」じゃなかったか？";
			next;
			cutin "fly_felrock2.bmp", 2;
			mes "[船長ペルロック]";
			mes "名前なんてどちらでも良い！";
			mes "くだらない事を話す暇があるなら";
			mes "脱出するんだ！";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "わ、悪かった……。";
			next;
		}
		if(HEROAIR_1QUE == 5) {
			cutin "fly_felrock2.bmp", 2;
			mes "[船長ペルロック]";
			mes "そこの君はちょっと待ってくれ。";
			mes "君には助けられてしまったからな。";
			mes "心ばかりだが礼をさせてくれ。";
			next;
			mes "[船長ペルロック]";
			mes "いくつか用意したのだが、";
			mes "どれがいいかね？";
			mes "一つ選んでくれ。";
			while(1) {
				next;
				switch(select("飛行船スーツ","飛行船マント","飛行船ブーツ")) {
				case 1:
					cutin "fly_felrock2.bmp", 255;
					mes "^0000FF飛行船スーツ^000000";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "[飛行船ブーツ]、";
					mes "[飛行船マント]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[飛行船スーツ]、";
					mes "[飛行船ブーツ]、";
					mes "[飛行船マント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[飛行船スーツ]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[飛行船スーツ]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^7777770^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,15159;
					break;
				case 2:
					cutin "fly_felrock2.bmp", 255;
					mes "^0000FF飛行船マント^000000";
					mes "MaxHP + 300";
					mes "―――――――――――――";
					mes "[飛行船スーツ]、";
					mes "[飛行船ブーツ]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[飛行船スーツ]、";
					mes "[飛行船ブーツ]、";
					mes "[飛行船マント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[飛行船マント]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[飛行船マント]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^777777100^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,20792;
					break;
				case 3:
					cutin "fly_felrock2.bmp", 255;
					mes "^0000FF飛行船ブーツ^000000";
					mes "MaxHP + 200 , MaxSP + 20";
					mes "―――――――――――――";
					mes "[飛行船スーツ]、";
					mes "[飛行船マント]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[飛行船スーツ]、";
					mes "[飛行船ブーツ]、";
					mes "[飛行船マント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[飛行船ブーツ]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[飛行船ブーツ]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^7777770^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,22087;
					break;
				}
				next;
				cutin "fly_felrock2.bmp", 2;
				mes "[船長ペルロック]";
				mes "これでいいか？";
				next;
				if(select("他のアイテムも見てみる","これにする") == 1) {
					mes "[船長ペルロック]";
					mes "どれにする？";
					continue;
				}
				break;
			}
			mes "[船長ペルロック]";
			mes "わかった。";
			mes "それではこれを渡そう。";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "話は済んだか？";
			mes "船の高度も下がってきている。";
			mes "俺たちも脱出しよう！";
			next;
		}
		else if(HEROAIR_1QUE == 6) {
			cutin "fly_felrock2.bmp", 2;
			mes "[船長ペルロック]";
			mes "そこの君はちょっと待ってくれ。";
			mes "君には助けられてしまったからな。";
			mes "心ばかりだが礼をさせてくれ。";
			next;
			mes "[船長ペルロック]";
			mes "いくつか用意したのだが、";
			mes "どれがいいかね？";
			mes "一つ選んでくれ。";
			while(1) {
				next;
				switch(select("ペルロックのスーツ","ペルロックのマント","ペルロックのブーツ")) {
				case 1:
					cutin "fly_felrock2.bmp", 255;
					mes "^ff0000ペルロックのスーツ^000000";
					mes "Mdef + 10";
					mes "―――――――――――――";
					mes "MaxHP + 500";
					mes "―――――――――――――";
					mes "[ペルロックのブーツ]、";
					mes "[ペルロックのマント]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[ペルロックのスーツ]、";
					mes "[ペルロックのブーツ]、";
					mes "[ペルロックのマント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのスーツ]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのスーツ]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777鎧^000000";
					mes "防御 : ^7777770^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,15158;
					break;
				case 2:
					cutin "fly_felrock2.bmp", 255;
					mes "^ff0000ペルロックのマント^000000";
					mes "MaxHP + 300";
					mes "―――――――――――――";
					mes "[ペルロックのスーツ]、";
					mes "[ペルロックのブーツ]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[ペルロックのスーツ]、";
					mes "[ペルロックのブーツ]、";
					mes "[ペルロックのマント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのマント]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのマント]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777肩にかける物^000000";
					mes "防御 : ^777777100^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,20791;
					break;
				case 3:
					cutin "fly_felrock2.bmp", 255;
					mes "^ff0000ペルロックのブーツ^000000";
					mes "MaxHP + 200 , MaxSP + 20";
					mes "―――――――――――――";
					mes "[ペルロックのスーツ]、";
					mes "[ペルロックのマント]と";
					mes "共に装備時、追加で";
					mes "Def + 200 , Mdef + 20";
					mes "MaxHP + 500 , MaxSP + 50";
					mes "[ペルロックのスーツ]、";
					mes "[ペルロックのブーツ]、";
					mes "[ペルロックのマント]の";
					mes "精錬値合計が15以上の時、";
					mes "追加で";
					mes "MaxHP + 1000";
					mes "MaxSP + 30";
					mes "精錬値合計が20以上の時、";
					mes "追加で";
					mes "MaxHP + 1500";
					mes "MaxSP + 100";
					mes "精錬値合計が25以上の時、";
					mes "追加で";
					mes "MaxHP + 2000";
					mes "MaxSP + 200";
					mes "―――――――――――――";
					mes "精錬不可";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのブーツ]は";
					mes "NPC「道楽裁縫師」でのみ";
					mes "精錬が可能です。^000000";
					mes "―――――――――――――";
					mes "^ff0000[ペルロックのブーツ]は";
					mes "NPC売却・倉庫への";
					mes "移動が可能です。^000000";
					mes "―――――――――――――";
					mes "系列 : ^777777靴^000000";
					mes "防御 : ^7777770^000000";
					mes "重量 : ^777777100^000000";
					mes "要求レベル : ^77777750^000000";
					mes "装備 : ^777777全ての職業^000000";
					set '@gain,22086;
					break;
				}
				next;
				cutin "fly_felrock2.bmp", 2;
				mes "[船長ペルロック]";
				mes "これでいいか？";
				next;
				if(select("他のアイテムも見てみる","これにする") == 1) {
					mes "[船長ペルロック]";
					mes "どれにする？";
					continue;
				}
				break;
			}
			mes "[船長ペルロック]";
			mes "わかった。";
			mes "それではこれを渡そう。";
			next;
			cutin "h_chaos02.bmp", 2;
			mes "[ケイオス]";
			mes "話は済んだか？";
			mes "船の高度も下がってきている。";
			mes "俺たちも脱出しよう！";
			next;
		}
		cutin "h_chaos02.bmp", 2;
		mes "[ケイオス]";
		mes "あんたは先に脱出してくれ！";
		mes "俺たちもここを片付けたら";
		mes "すぐ脱出する！";
		hideoffnpc getmdnpcname("warp5a#air2");
		if(HEROAIR_1QUE == 5)
			set '@num,5;
		else if(HEROAIR_1QUE == 6)
			set '@num,10;
		else
			set '@num,3;
		for(set '@i,0;'@i<'@num;set '@i,'@i+1)
			getexp 100000,0,1;
		for(set '@i,0;'@i<'@num;set '@i,'@i+1)
			getexp 0,50000,0;
		if('@gain)
			getitem '@gain, 1;
		set HEROAIR_1QUE,7;
		if(!checkquest(120200)) {
			setquest 120200;
			compquest 120200;
		}
		close2;
		cutin "h_chaos02.bmp", 255;
		end;
	}
	cutin "h_chaos02.bmp", 2;
	mes "[ケイオス]";
	mes "この船は危険だ!!";
	mes "あんたも早く脱出してくれ！";
	close2;
	cutin "h_chaos01.bmp", 255;
	end;
}

1@air2.gat,244,73,0	script	warp5a#air2	45,1,1,{
	mes "‐ここから時の通路へ戻れそうだ。";
	mes "　時の通路へ戻りますか？‐";
	next;
	if(select("戻らない","時の通路へ戻る") == 1) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	mes "‐時の通路へ戻ります‐";
	close2;
	warp "dali02.gat",137,82;
	end;
}
