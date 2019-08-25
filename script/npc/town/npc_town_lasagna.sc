//====================================================================
//Ragnarok Online - Lasagna Town Script	by refis
//====================================================================

//============================================================
// 治療師
//============================================================
lasagna.gat,305,242,4	script	治療師ハル	10164,{
	set '@price,5000;

	mes "[治療師ハル]";
	if(Job == Job_Summoner) {
		mes "やあ。調子はどうだい？";
		mes "治療なら任せてくれよ。";
		if(BaseLevel < 100) {
			mes "いまならBaseLv100以下の";
			mes "新米ドラムは無料で";
			mes "治療してあげるよ。";
			set '@price,0;
		}
	}
	else {
		mes "パースタ大陸へようこそ！";
		mes "私はラザーニャ唯一の治療師の";
		mes "ハルと言います。";
	}
	next;
	if(select("完全回復を頼む　^0000FF" +'@price+ "Zeny^000000","やめる") == 2) {
		mes "[治療師ハル]";
		mes "またのご利用を";
		mes "お待ちしております。";
		close;
	}
	if(Zeny < '@price) {
		mes "[治療師ハル]";
		mes "おや……？";
		mes "お金が足りないようですね。";
		mes "治療にも費用が必要です。";
		mes "どうかご理解を……。";
		close;
	}
	misceffect 7,"";
	misceffect 14,"";
	misceffect 492,"";
	percentheal 100,100;
	npcskillsupport 28,9999;
	set Zeny,Zeny - '@price;
	mes "[治療師ハル]";
	if(Job == Job_Summoner) {
		mes "ふぅ、終わったよ。";
		mes "治療が必要になったら";
		mes "また来てくださいね。";
	}
	else {
		mes "治療が終わりました。";
		mes "またのご利用を";
		mes "お待ちしています。";
	}
	close;
}

//============================================================
// 転送NPC
//============================================================
izlude.gat,181,187,3	script	ドラム船員#izlude	544,{
	mes "[ドラム船員]";
	mes "ミッドガルド大陸から";
	mes "パースタ大陸へ！";
	mes "港町ラザーニャまで";
	mes "^0000cd500Zeny^000000でご案内！";
	next;
	if(select("ラザーニャ -> 500 z","やめる") == 2) {
		mes "[ドラム船員]";
		mes "わかりました";
		close;
	}
	if(Zeny < 500) {
		mes "[ドラム船員]";
		mes "Zenyが足りないんですが？";
		mes "所持金を確認していただけますか？";
		close;
	}
	set Zeny,Zeny-500;
	warp "lasagna.gat",206,297;
	end;
}

malangdo.gat,218,81,0	script	ドラム船員#malangdo	544,{
	mes "[ドラム船員]";
	mes "マラン島から";
	mes "パースタ大陸へ！";
	mes "港町ラザーニャまで";
	mes "^0000cd500Zeny^000000でご案内！";
	next;
	if(select("ラザーニャ -> 500 z","やめる") == 2) {
		mes "[ドラム船員]";
		mes "わかりました";
		close;
	}
	if(Zeny < 500) {
		mes "[ドラム船員]";
		mes "Zenyが足りないんですが？";
		mes "所持金を確認していただけますか？";
		close;
	}
	set Zeny,Zeny-500;
	warp "lasagna.gat",206,297;
	end;
}

lasagna.gat,203,324,5	script	エッグリン#do_tu02	10157,{
	mes "[エッグリン]";
	if(Job == Job_Summoner) {
		mes "料理長から罰として";
		mes "大量の雑用を押し付けられたんだ。";
		mes "サボらなきゃやってられないよね。";
	}
	else {
		mes "あー";
		mes "良い天気だなー。";
		mes "絶好のサボり日和だねえ。";
	}
	next;
	mes "[エッグリン]";
	mes "ん？";
	mes "どこかに行きたいの？";
	next;
	switch(select("イズルード -> 0 z","マラン島 -> 0 z","行かない")) {
	case 1:
		warp "izlude.gat",194,180;
		end;
	case 2:
		warp "malangdo.gat",217,85;
		end;
	case 3:
		mes "[エッグリン]";
		mes "あー眠いなあ。";
		close;
	}
}

//============================================================
// Shop
//============================================================
lasagna.gat,312,259,5	shop	道具商人#lasagna	553,11602,515,567,601,602,610,656,525,611
lasagna.gat,339,248,3	shop	婚礼品商人#lasagna	10163,744,745,2338,2206,7170,2613

lasagna.gat,293,289,5	script	武具商人#do_su03	10162,{
	mes "[武具商人]";
	mes "いらっしゃい。";
	mes "うちの品物は一級品ばかりだよ。";
	mes "何を見ていくんだい？";
	next;
	switch(select("武器","防具","アクセサリー","消耗品","やめる")) {
	case 1:
		switch(select("物理タイプ","魔法タイプ","支援回復タイプ","やめる")) {
		case 1:
			switch(select("猫じゃらしの模型[1]","大きな猫じゃらしの模型[1]","繊細な猫じゃらしの模型[1]","精巧な猫じゃらしの模型[1]","黄色い猫じゃらしの模型[0]","やめる")) {
			case 1: set '@itemid,26133; set '@price,500000; set '@dpoint,50; break;
			case 2: set '@itemid,26127; set '@price,500000; set '@dpoint,50; break;
			case 3: set '@itemid,26134; set '@price,1500000; set '@dpoint,100; break;
			case 4: set '@itemid,26136; set '@price,15000000; set '@dpoint,150; break;
			case 5: set '@itemid,26137; set '@price,100000000; set '@dpoint,1000; break;
			case 6:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 2:
			switch(select("トンボがとまった猫じゃらし[1]","トンボがとまった妙なる猫じゃらし[1]","トンボがとまった神妙な猫じゃらし[1]","トンボがとまった魔力の猫じゃらし[1]","トンボがとまった黄色い猫じゃらし[0]","やめる")) {
			case 1: set '@itemid,26126; set '@price,500000; set '@dpoint,50; break;
			case 2: set '@itemid,26129; set '@price,500000; set '@dpoint,50; break;
			case 3: set '@itemid,26130; set '@price,1500000; set '@dpoint,100; break;
			case 4: set '@itemid,26131; set '@price,15000000; set '@dpoint,150; break;
			case 5: set '@itemid,26132; set '@price,100000000; set '@dpoint,1000; break;
			case 6:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 3:
			switch(select("長い回復の猫じゃらし[1]","豊富な回復の猫じゃらし[1]","やめる")) {
			case 1: set '@itemid,26125; set '@price,500000; set '@dpoint,50; break;
			case 2: set '@itemid,26124; set '@price,15000000; set '@dpoint,150; break;
			case 3:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 4:
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		break;
	case 2:
		switch(select("ドラムスーツ[1]","高級ドラムスーツ[1]","特選ドラムスーツ[1]","ドラムシューズ[1]","高級ドラムシューズ[1]","特選ドラムシューズ[1]","ドラムケープ[1]","高級ドラムケープ[1]","特選ドラムケープ[1]","ドラムシールド[0]","やめる")) {
		case 1: set '@itemid,15275; set '@price,1000000; set '@dpoint,100; break;
		case 2: set '@itemid,15276; set '@price,10000000; set '@dpoint,1000; break;
		case 3: set '@itemid,15277; set '@price,150000000; set '@dpoint,1500; break;
		case 4: set '@itemid,22185; set '@price,1000000; set '@dpoint,100; break;
		case 5: set '@itemid,22186; set '@price,10000000; set '@dpoint,1000; break;
		case 6: set '@itemid,22187; set '@price,150000000; set '@dpoint,1500; break;
		case 7: set '@itemid,20915; set '@price,1000000; set '@dpoint,100; break;
		case 8: set '@itemid,20916; set '@price,10000000; set '@dpoint,1000; break;
		case 9: set '@itemid,20917; set '@price,150000000; set '@dpoint,1500; break;
		case 10: set '@itemid,28948; set '@price,10000000; set '@dpoint,1000; break;
		case 11:
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		break;
	case 3:
		switch(select("物理タイプ","魔法タイプ","支援回復タイプ","やめる")) {
		case 1:
			switch(select("新鮮な草のネックレス[1]","ぽっちゃりミミズのお守り[1]","ウサギのお守り[1]","高級ウサギのお守り[1]","特選ウサギのお守り[1]","やめる")) {
			case 1: set '@itemid,28577; set '@price,100000000; set '@dpoint,2000; break;
			case 2: set '@itemid,28591; set '@price,300000000; set '@dpoint,2000; break;
			case 3: set '@itemid,28586; set '@price,1000000; set '@dpoint,100; break;
			case 4: set '@itemid,28587; set '@price,10000000; set '@dpoint,1000; break;
			case 5: set '@itemid,28588; set '@price,500000000; set '@dpoint,5000; break;
			case 6:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 2:
			switch(select("魔力の草のネックレス[1]","光る枝のお守り[1]","葉のお守り[1]","高級葉のお守り[1]","特選葉のお守り[1]","やめる")) {
			case 1: set '@itemid,28579; set '@price,100000000; set '@dpoint,2000; break;
			case 2: set '@itemid,28589; set '@price,300000000; set '@dpoint,2000; break;
			case 3: set '@itemid,28583; set '@price,1000000; set '@dpoint,100; break;
			case 4: set '@itemid,28584; set '@price,10000000; set '@dpoint,1000; break;
			case 5: set '@itemid,28585; set '@price,500000000; set '@dpoint,5000; break;
			case 6:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 3:
			switch(select("可愛い草のネックレス[1]","新鮮なマグロのお守り[1]","アジのお守り[1]","高級アジのお守り[1]","特選アジのお守り[1]","やめる")) {
			case 1: set '@itemid,28578; set '@price,100000000; set '@dpoint,2000; break;
			case 2: set '@itemid,28590; set '@price,300000000; set '@dpoint,2000; break;
			case 3: set '@itemid,28580; set '@price,1000000; set '@dpoint,100; break;
			case 4: set '@itemid,28581; set '@price,10000000; set '@dpoint,1000; break;
			case 5: set '@itemid,28582; set '@price,500000000; set '@dpoint,5000; break;
			case 6:
				mes "[武具商人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			break;
		case 4:
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		break;
	case 4:
		setarray '@itemname$[1],"おいしいイワシ 100個","カルーニャミルク","バジル","ラザーニャ特産缶詰","やめる";
		set '@menu,select(printarray('@itemname$));
		switch('@menu) {
		case 1: set '@itemid,11601; set '@price,1000000; set '@dpoint,15; set '@num,100; break;
		case 2: set '@itemid,22984; set '@price,100000; set '@dpoint,5; set '@num,1; break;
		case 3: set '@itemid,22985; set '@price,100000; set '@dpoint,5; set '@num,1; break;
		case 4: set '@itemid,23705; set '@price,100000; set '@dpoint,5; set '@num,1; break;
		case 5:
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		mes "[武具商人]";
		mes '@itemname$['@menu]+ "は";
		mes "Zenyかドラムポイントで購入可能だ。";
		if('@menu == 1) {
			mes "ちなみに、^0000ffおいしいイワシ^000000だけは";
			mes "^0000ff100個で1セット^000000の販売になるよ。";
		}
		mes "^ff0000所持ドラムポイント : " +DORAM_POINT+ "^000000";
		next;
		switch(select('@price+"Zenyで買う",'@dpoint+"ドラムポイントで買う","やめる")) {
		case 1:
			set '@dpoint,0;
			break;
		case 2:
			set '@price,0;
			break;
		case 3:
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		mes "[武具商人]";
		mes "了解した。";
		mes '@itemname$['@menu]+ "を";
		mes "何個（セット）購入するんだい？";
		mes "止めたいときは「0」を入れてね。";
		while(1) {
			next;
			input '@set;
			if('@set == 0) {
				mes "[武具商人]";
				mes "了解したよ。";
				mes "気が変わったらまた来てね。";
				close;
			}
			if('@set < 0 || '@set > 1000) {
				mes "[武具商人]";
				mes "申し訳ないけど、1回の取引は";
				mes "1000個以下にしてもらえるかな。";
				continue;
			}
			break;
		}
		mes "[武具商人]";
		mes "確認だけど、";
		mes '@itemname$['@menu]+ "を";
		mes '@set +"個（セット）";
		if('@price)
			mes ('@price*'@set) +"Zenyで買う";
		else
			mes ('@dpoint*'@set) +"ドラムポイントで買う";
		mes "で良いんだね。";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[武具商人]";
			mes "わかった。";
			mes "気が変わったらまた来てね。";
			close;
		}
		if('@price && '@price*'@set > Zeny) {
			mes "[武具商人]";
			mes "Zenyが足りないみたいだよ。";
			mes "もう一度確認してもらえるかな。";
			close;
		}
		if('@dpoint && '@dpoint*'@set > DORAM_POINT) {
			mes "[武具商人]";
			mes "ドラムポイントが";
			mes "足りないみたいだよ。";
			mes "もう一度確認してもらえるかな。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "^009eff【インフォメーション】";
			mes "これ以上多くの種類の";
			mes "荷物を持つことが出来ません。";
			mes "1個以上の空きを作ってください。^000000";
			close;
		}
		if(checkweight('@itemid,'@num*'@set) == 0) {
			set '@weight,getiteminfo('@itemid,6)/10 * '@num * '@set + 1;
			mes "^009eff【インフォメーション】";
			mes "これ以上多くの";
			mes "荷物を持つことが出来ません。";
			mes '@weight +"以上の";
			mes "重量の空きを作ってください。^000000";
			close;
		}
		if('@price)
			set Zeny,Zeny - '@price*'@set;
		if('@dpoint)
			set DORAM_POINT,DORAM_POINT - '@dpoint*'@set;
		getitem '@itemid,'@num*'@set;
		mes "[武具商人]";
		mes "お買い上げありがとうございます。";
		mes "また来てくださいね。";
		close;
	case 5:
		mes "[武具商人]";
		mes "わかった。";
		mes "気が変わったらまた来てね。";
		close;
	}
	mes "[武具商人]";
	mes getitemname('@itemid)+ "[" +getiteminfo('@itemid,10)+ "]は";
	mes "Zenyかドラムポイントで購入可能だ。";
	mes "^ff0000所持ドラムポイント : " +DORAM_POINT+ "^000000";
	next;
	switch(select('@price+"Zenyで買う",'@dpoint+"ドラムポイントで買う","やめる")) {
	case 1:
		set '@dpoint,0;
		break;
	case 2:
		set '@price,0;
		break;
	case 3:
		mes "[武具商人]";
		mes "わかった。";
		mes "気が変わったらまた来てね。";
		close;
	}
	mes "[武具商人]";
	mes "確認だけど、";
	mes getitemname('@itemid)+ "[" +getiteminfo('@itemid,10)+ "]を";
	if('@price)
		mes '@price+"Zenyで買う";
	else
		mes '@dpoint+"ドラムポイントで買う";
	mes "で良いんだね。";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[武具商人]";
		mes "わかった。";
		mes "気が変わったらまた来てね。";
		close;
	}
	if('@price && '@price > Zeny) {
		mes "[武具商人]";
		mes "Zenyが足りないみたいだよ。";
		mes "もう一度確認してもらえるかな。";
		close;
	}
	if('@dpoint && '@dpoint > DORAM_POINT) {
		mes "[武具商人]";
		mes "ドラムポイントが";
		mes "足りないみたいだよ。";
		mes "もう一度確認してもらえるかな。";
		close;
	}
	if(checkitemblank() == 0) {
		mes "^009eff【インフォメーション】";
		mes "これ以上多くの種類の";
		mes "荷物を持つことが出来ません。";
		mes "1個以上の空きを作ってください。^000000";
		close;
	}
	if(checkweight('@itemid,1) == 0) {
		set '@weight,getiteminfo('@itemid,6)/10 + 1;
		mes "^009eff【インフォメーション】";
		mes "これ以上多くの";
		mes "荷物を持つことが出来ません。";
		mes '@weight +"以上の";
		mes "重量の空きを作ってください。^000000";
		close;
	}
	if('@price)
		set Zeny,Zeny - '@price;
	if('@dpoint)
		set DORAM_POINT,DORAM_POINT - '@dpoint;
	getitem '@itemid,1;
	mes "[武具商人]";
	mes "お買い上げありがとうございます。";
	mes "また来てくださいね。";
	close;
}

lasagna.gat,298,289,5	script	加工職人#do_su03	555,{
	mes "[加工職人]";
	mes "いらっしゃい。";
	mes "今日はどうしたんだい？";
	next;
	switch(select("アップグレード","アップグレード対応のリストを見る","やめる")) {
	case 1:
		mes "[加工職人]";
		mes "アップグレードをご希望だね。";
		mes "まずは説明をするよ。";
		next;
		mes "[加工職人]";
		mes "君の装着している装備を";
		mes "一段階上の装備に";
		mes "アップグレードして渡すよ。";
		mes "その際の注意点だけど、";
		mes "精錬値が「0」に戻ってしまうから";
		mes "よく考えてから利用してね。";
		next;
		mes "[加工職人]";
		mes "^0000ff装着されているカードは";
		mes "アップグレード後に対応する";
		mes "スロットがあればそのまま";
		mes "維持できるよ。^000000これが";
		mes "僕の提供するアップグレードの";
		mes "メリットさ。";
		next;
		mes "[加工職人]";
		mes "ちなみに、アップグレードすると";
		mes "元の装備に戻すことは";
		mes "決してできないので、注意してね。";
		next;
		mes "[加工職人]";
		mes "後、アップグレードの際に";
		mes "手数料として相応のZenyか";
		mes "ドラムポイントを頂くよ。";
		while(1) {
			next;
			mes "[加工職人]";
			mes "では、アップグレードしたい";
			mes "装備を選んでくれるかな。";
			setarray '@item,15275,15276,22185,22186,20915,20916,28580,28581,28583,28584,28586,28587,26134,26125,26126,26127,26129,26130,26133;
			setarray '@gain,15276,15277,22186,22187,20916,20917,28581,28582,28584,28585,28587,28588,26136,26124,26129,26134,26130,26131,26127;
			setarray '@price,10000000,150000000,10000000,150000000,10000000,150000000,10000000,500000000,10000000,500000000,10000000,500000000,15000000,15000000,500000,1500000,1500000,15000000,500000;
			setarray '@dpoint,1000,1500,1000,1500,1000,1500,1000,5000,1000,5000,1000,5000,150,150,50,100,100,150,50;
			setarray '@pos,2,4,5,6,7,8;
			set '@len,getarraysize('@item);
			for(set '@k,0; '@k<getarraysize('@pos); set '@k,'@k+1) {
				for(set '@j,0; '@j<'@len; set '@j,'@j+1) {
					if(getequipid('@pos['@k]) == '@item['@j]) {
						set '@str$['@k],"^nItemID^"+ '@item['@j];
						break;
					}
				}
			}
			next;
			switch(select("少し考える",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4],'@str$[5],"やめる")) {
			case 1:
				continue;
			case 2: set '@i,2; break;
			case 3: set '@i,4; break;
			case 4: set '@i,5; break;
			case 5: set '@i,6; break;
			case 6: set '@i,7; break;
			case 7: set '@i,8; break;
			case 8:
				mes "[加工職人]";
				mes "そうかい。";
				mes "必要になったら";
				mes "また来てくれよな。";
				close;
			}
			for(set '@j,0; '@j<'@len; set '@j,'@j+1) {
				if(getequipid('@i) == '@item['@j]) {
					break;
				}
			}
			if('@j=='@len) {
				mes "[加工職人]";
				mes "対象装備を身に着けてないな。";
				mes "もう一度確認してから";
				mes "また来てくれよな。";
				close;
			}
			mes "[加工職人]";
			mes "君の装備している";
			mes getitemname('@item['@j])+ "[" +getiteminfo('@item['@j],10)+ "]を";
			mes getitemname('@gain['@j])+ "[" +getiteminfo('@gain['@j],10)+ "]に";
			mes "アップグレードするよ。";
			mes "支払い方法はどちらにするんだい？";
			mes "^ff0000所持ドラムポイント : " +DORAM_POINT+ "^000000";
			next;
			switch(select('@price['@j]+"Zenyを払う",'@dpoint['@j]+"ドラムポイントを払う","やめる")) {
			case 1:
				set '@price,'@price['@j];
				break;
			case 2:
				set '@dpoint,'@dpoint['@j];
				break;
			case 3:
				mes "[加工職人]";
				mes "そうかい。";
				mes "必要になったら";
				mes "また来てくれよな。";
				close;
			}
			// 未調査
			mes "[加工職人]";
			mes "確認だけど、";
			mes getitemname('@item['@j])+ "[" +getiteminfo('@item['@j],10)+ "]を";
			mes getitemname('@gain['@j])+ "[" +getiteminfo('@gain['@j],10)+ "]に";
			if('@price)
				mes '@price+"Zenyで";
			else
				mes '@dpoint+"ドラムポイントで";
			mes "アップグレードする";
			mes "で良いんだね。";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[加工職人]";
				mes "わかった。";
				mes "気が変わったらまた来てね。";
				close;
			}
			if('@price && '@price > Zeny) {
				mes "[加工職人]";
				mes "うん？Zenyが足りないよ。";
				mes "もう一度確認してから";
				mes "また来てくれよな。";
				close;
			}
			if('@dpoint && '@dpoint > DORAM_POINT) {
				mes "[加工職人]";
				mes "うん？ドラムポイントが足りないよ。";
				mes "もう一度確認してから";
				mes "また来てくれよな。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "^009eff【インフォメーション】";
				mes "これ以上多くの種類の";
				mes "荷物を持つことが出来ません。";
				mes "1個以上の空きを作ってください。^000000";
				close;
			}
			if(checkweight('@gain['@j],1) == 0) {
				set '@weight,getiteminfo('@gain['@j],6)/10 + 1;
				mes "^009eff【インフォメーション】";
				mes "これ以上多くの";
				mes "荷物を持つことが出来ません。";
				mes '@weight +"以上の";
				mes "重量の空きを作ってください。^000000";
				close;
			}
			if('@price)
				set Zeny,Zeny - '@price;
			if('@dpoint)
				set DORAM_POINT,DORAM_POINT - '@dpoint;
			set '@card1,getequipcardid('@menu,0);
			delequip '@i;
			getitem2 '@gain['@j],1,1,0,0,'@card1,0,0,0;
			getitem '@gain['@j],1;
			mes "[武具商人]";
			mes "お買い上げありがとうございます。";
			mes "また来てくださいね。";
			close;
		}
	case 2:
		mes "＜アップグレード交換対応リスト＞";
		mes "ドラムスーツ[1]";
		mes "→　高級ドラムスーツ[1]";
		mes "　";
		mes "高級ドラムスーツ[1]";
		mes "→　特選ドラムスーツ[1]";
		mes "　";
		mes "ドラムシューズ[1]";
		mes "→　高級ドラムシューズ[1]";
		mes "　";
		mes "高級ドラムシューズ[1]";
		mes "→　特選ドラムシューズ[1]";
		mes "　";
		mes "ドラムケープ[1]";
		mes "→　高級ドラムケープ[1]";
		mes "　";
		mes "高級ドラムケープ[1]";
		mes "→　特選ドラムケープ[1]";
		mes "　";
		mes "アジのお守り[1]";
		mes "→　高級アジのお守り[1]";
		mes "　";
		mes "高級アジのお守り[1]";
		mes "→　特選アジのお守り[1]";
		mes "　";
		mes "葉のお守り[1]";
		mes "→　高級葉のお守り[1]";
		mes "　";
		mes "高級葉のお守り[1]";
		mes "→　特選葉のお守り[1]";
		mes "　";
		mes "ウサギのお守り[1]";
		mes "→　高級ウサギのお守り[1]";
		mes "　";
		mes "高級ウサギのお守り[1]";
		mes "→　特選ウサギのお守り[1]";
		mes "　";
		mes "繊細な猫じゃらしの模型[1]";
		mes "→　精巧な猫じゃらしの模型[1]";
		mes "　";
		mes "長い回復の猫じゃらし[1]";
		mes "→　豊富な回復の猫じゃらし[1]";
		mes "　";
		mes "トンボがとまった猫じゃらし[1]";
		mes "→　トンボがとまった妙なる猫じゃらし[1]";
		mes "　";
		mes "大きな猫じゃらしの模型[1]";
		mes "→　繊細な猫じゃらしの模型[1]";
		mes "　";
		mes "トンボがとまった妙なる猫じゃらし[1]";
		mes "→　トンボがとまった神妙な猫じゃらし[1]";
		mes "　";
		mes "トンボがとまった神妙な猫じゃらし[1]";
		mes "→　トンボがとまった魔力の猫じゃらし[1]";
		mes "　";
		mes "猫じゃらしの模型[1]";
		mes "→　大きな猫じゃらしの模型[1]";
		close;
	case 3:
		mes "[加工職人]";
		mes "そうかい、残念だね。";
		mes "また必要になったら";
		mes "声をかけておくれ。";
		close;
	}
}

lasagna.gat,289,287,5	script	鍛冶職人#lasagna	561,{
	callfunc "BlackSmith","鍛冶職人",21,23;
	close;
}

//============================================================
// 看板
//============================================================
lasagna.gat,321,242,4	script	看板#1lasagna	835,7,7,{
	unittalk "北西側：道具商人　／　東側：髪型変更・スペシャルアイテム販売員",1;
	end;
}

lasagna.gat,312,251,4	script	看板#2lasagna	835,7,7,{
	unittalk "北西側：精錬・修理・ドラム武具販売・アップグレード",1;
	end;
}

lasagna.gat,297,229,4	script	チュートリアル掲示板#01	857,{
	mes "‐チュートリアルで学んだことが";
	mes "　確認できる掲示板だ。";
	mes "　どれを読みますか‐";
	while(1) {
		next;
		switch(select("やめる","左クリック","クエストウィンドウ","ミニマップと現在地の確認","アイテムウィンドウ","アイテムの精錬","ステータス","スキル","ショートカットウィンドウ","自然回復と重量","アイテムの購入と売却","クエストウィンドウに直接入るアイテム","ワープリンク","パーティー結成","プレイヤーとの取引","カプラサービス")) {
		case 1:		//やめる
			cutin "do_su_001",255;
			mes "‐あなたはこの場を離れた‐";
			close;
		case 2:		//左クリック
			cutin "do_su_001",3;
			mes "【インフォメーション】";
			mes "マウスのクリックでゲーム内の";
			mes "各種インターフェースを操作出来ます。";
			next;
			mes "【インフォメーション】";
			mes "NPCとの会話や移動、モンスターへの攻撃は";
			mes "マウスの左クリックを使用します。";
			continue;
		case 3:		//クエストウィンドウ
			cutin "do_su_002",3;
			mes "【インフォメーション】";
			mes "クエストウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<U>キー^000000で";
			mes "開くことができます。";
			next;
			cutin "do_su_003",3;
			mes "【インフォメーション】";
			mes "クエストウィンドウには";
			mes "行き先や目標が書いてあります。";
			mes "まずはそこを目指しましょう！";
			continue;
		case 4:		//ミニマップと現在地の確認
			cutin "do_su_001",255;
			mes "【インフォメーション】";
			mes "画面右上のミニマップに";
			mes "自分の今いる場所や座標が";
			mes "表示されています。";
			next;
			cutin "do_su_028",3;
			mes "【インフォメーション】";
			mes "また、チャットウィンドウに";
			mes "^ff0000「/where」^000000と入力すると";
			mes "自分のいるマップ名を";
			mes "調べることができます。";
			continue;
		case 5:		//アイテムウィンドウ
			cutin "do_su_004",3;
			mes "【インフォメーション】";
			mes "アイテムウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<E>キー^000000で";
			mes "開くことができます。";
			next;
			cutin "do_su_018",3;
			mes "【インフォメーション】";
			mes "消耗タブのアイテムを";
			mes "ダブルクリックすると、";
			mes "アイテムを使用することが";
			mes "できます。";
			next;
			cutin "do_su_005",3;
			mes "【インフォメーション】";
			mes "装備しているアイテムは";
			mes "装備ウィンドウで確認できます。";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<Q>キー^000000で";
			mes "開くことができます。";
			next;
			cutin "do_su_006",3;
			mes "【インフォメーション】";
			mes "装備タブのアイテムを";
			mes "ダブルクリックすると、";
			mes "アイテムを装備することができます。";
			next;
			mes "【インフォメーション】";
			mes "ダブルクリック以外にも、";
			mes "アイテムウィンドウから";
			mes "装備したいアイテムを";
			mes "装備ウィンドウに";
			mes "ドラッグ＆ドロップする事で、";
			mes "装備を変更することができます。";
			next;
			mes "【インフォメーション】";
			mes "ただし、装備欄を開いていない時に";
			mes "ドラッグ＆ドロップで";
			mes "地面を指定すると";
			mes "アイテムを落としてしまうので";
			mes "注意してください。";
			next;
			mes "【インフォメーション】";
			mes "ドロップロックボタンを押して";
			mes "ロック状態にすれば地面に";
			mes "アイテムが捨てられることはなくなります。";
			mes "心配な人はロック状態に";
			mes "しておきましょう。";
			next;
			mes "【インフォメーション】";
			mes "なお、NPCと会話中はアイテムが";
			mes "使用できない場合があるので";
			mes "注意してください！";
			continue;
		case 6:		//アイテムの精錬
			cutin "do_su_023",3;
			mes "【インフォメーション】";
			mes "装備を精錬することで";
			mes "武器や防具の性能を";
			mes "上昇させることができます。";
			mes "精錬に必要な費用や素材は";
			mes "アイテムによって異なります。";
			next;
			cutin "do_su_024",3;
			mes "【インフォメーション】";
			mes "特定の精錬値を超えて精錬すると、";
			mes "精錬に失敗することがあります。";
			mes "安全な精錬値は装備によって異なり、";
			mes "^ff0000精錬に失敗したアイテムは";
			mes "消失してしまうので";
			mes "気をつけてください！^000000";
			continue;
		case 7:		//ステータス
			cutin "do_su_007",3;
			mes "【インフォメーション】";
			mes "ステータスは6種類あります。";
			mes "それぞれの特性を";
			mes "しっかりと把握しておきましょう！";
			next;
			cutin "do_su_008",3;
			mes "【インフォメーション】";
			mes "ステータスウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<A>キー^000000で";
			mes "で開くことができます。";
			mes "まずはウィンドウを開いてみましょう！";
			next;
			cutin "do_su_009",3;
			mes "【インフォメーション】";
			mes "矢印をクリックすると";
			mes "Status Pointを消費し、";
			mes "ステータスが上昇します。";
			mes "Status PointはBaseLvが";
			mes "上がるごとに増えます。";
			next;
			mes "【インフォメーション】";
			mes "一度消費したStatus Pointは";
			mes "戻すことができません。";
			mes "間違えて別のステータスに";
			mes "ポイントを使用しないように";
			mes "気を付けましょう。";
			next;
			mes "【インフォメーション】";
			mes "ステータスの";
			mes "「+○」という部分は";
			mes "装備やJobLvによる";
			mes "ステータスボーナスです。";
			mes "Status Pointを消費して";
			mes "上昇はさせることはできません。";
			next;
			mes "【インフォメーション】";
			mes "ステータスの上げ方次第で";
			mes "モンスターとの戦い方は";
			mes "大きく変わります。";
			mes "自分に合ったステータスを";
			mes "探してみましょう。";
			continue;
		case 8:		//スキル
			cutin "do_su_001",255;
			mes "【インフォメーション】";
			mes "スキルは職業毎に異なり";
			mes "サモナーの職業は";
			mes "攻撃や回復、補助のスキルを";
			mes "覚えることができます。";
			next;
			cutin "do_su_010",3;
			mes "【インフォメーション】";
			mes "スキルウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<S>キー^000000で";
			mes "開くことができます。";
			mes "まずはウィンドウを開いてみましょう！";
			next;
			cutin "do_su_011",3;
			mes "【インフォメーション】";
			mes "習得したいスキルを左クリックし";
			mes "確定ボタンを押して、";
			mes "確認に同意するとスキルポイントを";
			mes "消費してスキルを習得します。";
			mes "スキルポイントはJobLvが";
			mes "1上がるごとに1ポイント増えます。";
			next;
			mes "【インフォメーション】";
			mes "一度消費したスキルポイントは";
			mes "戻すことができません。";
			mes "間違えて別のスキルに";
			mes "ポイントを使用しないように";
			mes "気を付けましょう。";
			next;
			mes "【インフォメーション】";
			mes "なお、スキルの中には覚えるための";
			mes "条件があるものもあります。";
			mes "例えば「かみつく」を習得するには";
			mes "「ドラム基本スキル」Lv1を";
			mes "習得している必要があります。";
			next;
			cutin "do_su_010",3;
			mes "【インフォメーション】";
			mes "また、^ff0000クエストを達成することで";
			mes "習得できるスキルがあり、";
			mes "クエストスキルといいます。^000000";
			mes "クエストスキルはスキルポイントを";
			mes "消費せずに覚えることができます。";
			next;
			mes "【インフォメーション】";
			mes "習得するスキル次第で";
			mes "モンスターとの戦い方は";
			mes "大きく変わります。";
			mes "自分に合ったスキルを";
			mes "探してみましょう。";
			continue;
		case 9:		//ショートカットウィンドウ
			cutin "do_su_027",3;
			mes "【インフォメーション】";
			mes "ショートカットウィンドウは";
			mes "^ff0000<Ctrl>キー+<F12>キー^000000で";
			mes "開くことができます。";
			mes "ショートカットウィンドウは<F12>キーで";
			mes "切り替えることができ、";
			mes "最大で4つまで登録できます。";
			next;
			cutin "do_su_012",3;
			mes "【インフォメーション】";
			mes "ショートカットウィンドウに";
			mes "スキルやアイテムを";
			mes "ドラッグ＆ドロップすることで";
			mes "登録できます。";
			next;
			cutin "do_su_013",3;
			mes "【インフォメーション】";
			mes "登録したスキルやアイテムに";
			mes "対応したファンクションキーを";
			mes "押すことで、";
			mes "それらを使用することができます。";
			continue;
		case 10:		//自然回復と重量
			cutin "do_su_014",3;
			mes "【インフォメーション】";
			mes "HPとSPは時間が経てば";
			mes "自然に回復しますが、";
			mes "座ることで回復する速度を";
			mes "早めることができます。";
			next;
			mes "【インフォメーション】";
			mes "「立つ」と「座る」は^ff0000<Insert>キー^000000で";
			mes "切り替えることができます。";
			next;
			cutin "do_su_015",3;
			mes "【インフォメーション】";
			mes "なお所持アイテムの重量が";
			mes "総重量の50%以上になると";
			mes "自然回復が発生しなくなります。";
			next;
			mes "【インフォメーション】";
			mes "さらに90%以上になると、";
			mes "通常攻撃やスキル攻撃が";
			mes "できなくなります。";
			mes "もしそうなってしまったら";
			mes "アイテムを捨てたり倉庫に預けて";
			mes "重量を減らしましょう！";
			continue;
		case 11:		//アイテムの購入と売却
			cutin "do_su_016",3;
			mes "【インフォメーション】";
			mes "アイテムをNPCに売却すると";
			mes "Zenyになります。";
			next;
			mes "【インフォメーション】";
			mes "売却したいアイテムを";
			mes "「売りたい品物」に移動し、";
			mes "売却数を入力してから";
			mes "[sell]をクリックすると";
			mes "アイテムを売却できます。";
			next;
			cutin "do_su_017",3;
			mes "【インフォメーション】";
			mes "商人が販売しているアイテムは";
			mes "Zenyを支払うことで";
			mes "購入することができます。";
			next;
			mes "【インフォメーション】";
			mes "購入したいアイテムを";
			mes "「買いたい品物」に移動し、";
			mes "購入数を入力してから";
			mes "[buy]をクリックすると";
			mes "アイテムを購入できます。";
			continue;
		case 12:		//クエストウィンドウに直接入るアイテム
			cutin "do_su_019",3;
			mes "【インフォメーション】";
			mes "通常、アイテムはモンスターを";
			mes "倒した際に地面にドロップしますが、";
			mes "クエストによっては対象のアイテムが";
			mes "直接アイテムウィンドウに";
			mes "入る場合があります。";
			continue;
		case 13:		//ワープリンク
			cutin "do_su_020",3;
			mes "【インフォメーション】";
			mes "ワープリンクに触れると";
			mes "別のマップに移動できます。";
			continue;
		case 14:		//パーティー結成
			cutin "do_su_021",3;
			mes "【インフォメーション】";
			mes "パーティーウィンドウは";
			mes "アイコンを左クリックするか";
			mes "^ff0000<Alt>キー+<Z>キー^000000で";
			mes "で開くことができます。";
			mes "開いたら「パーティー作成」で";
			mes "パーティーを作ってみましょう！";
			next;
			cutin "do_su_022",3;
			mes "【インフォメーション】";
			mes "パーティー名を決めて";
			mes "パーティーを作ったら、";
			mes "他のプレイヤーを右クリックすると";
			mes "「パーティー加入要請」を";
			mes "することができます。";
			next;
			mes "【インフォメーション】";
			mes "相手がパーティー要請を承認すると、";
			mes "パーティーに入れることができます。";
			mes "お友達を誘ってパーティーを";
			mes "組んでみましょう！";
			continue;
		case 15:		//プレイヤーとの取引
			cutin "do_su_029",3;
			mes "【インフォメーション】";
			mes "プレイヤー同士で";
			mes "アイテムやZenyの取引を";
			mes "したい場合は、";
			mes "他のプレイヤーを右クリックして";
			mes "「取引要請」を選んでください。";
			next;
			mes "【インフォメーション】";
			mes "相手が要請に応じると、";
			mes "アイテム交換ウィンドウが";
			mes "開きます。";
			mes "左側が自分が相手に渡すもの、";
			mes "右側が相手が自分に渡すものに";
			mes "なります。";
			next;
			cutin "do_su_030",3;
			mes "【インフォメーション】";
			mes "自分が渡すアイテムや";
			mes "Zenyの額を決定したら、";
			mes "左下の「OK」をクリックします。";
			mes "すると自分の欄が灰色になります。";
			next;
			mes "【インフォメーション】";
			mes "相手側が渡すアイテムや";
			mes "Zenyの額を決定すると、";
			mes "相手側の欄が灰色になります。";
			mes "お互いの欄が灰色になったら";
			mes "中央の「trade」をクリックすれば";
			mes "取引が成立します。";
			next;
			mes "【インフォメーション】";
			mes "なお、取引するものを間違えたり、";
			mes "取引の内容が気に入らない場合は";
			mes "「trade」を押す前に";
			mes "右下の「cancel」を押せば";
			mes "取引を中止できます。";
			next;
			mes "【インフォメーション】";
			mes "意図しないアイテムやZenyを";
			mes "渡してしまわないよう、";
			mes "取引を行う際には";
			mes "十分注意しましょう。";
			continue;
		case 16:		//カプラサービス
			cutin "kafra_01",255;
			mes "【インフォメーション】";
			mes "各地にいるカプラサービスでは";
			mes "位置セーブサービスや";
			mes "倉庫サービス、";
			mes "空間移動サービスなど、";
			mes "冒険に必要なサポートを";
			mes "受けることができます。";
			next;
			cutin "do_su_025",3;
			mes "【インフォメーション】";
			mes "倉庫サービスは所持している";
			mes "アイテムを倉庫に預けることが";
			mes "できます。";
			mes "預けたアイテムは種別ごとの";
			mes "タブに分けられて保管されます。";
			next;
			cutin "do_su_026",3;
			mes "【インフォメーション】";
			mes "倉庫に預けたアイテムは";
			mes "別の場所の倉庫からも";
			mes "取り出すことができます。";
			mes "また、同じアカウント内の";
			mes "別のキャラクターで";
			mes "取り出すこともできます。";
			continue;
		}
	}
}

//============================================================
// 住民
//============================================================
lasa_fild01.gat,35,288,3	script	自警団員アジェニャー#la	10162,{
	mes "[自警団員アジェニャー]";
	if(Job == Job_Summoner) {
		mes "お、無事に入団出来たか。";
		mes "これからよろしくな！";
	}
	else {
		mes "新大陸発見以来、";
		mes "ラザーニャの町はお祭り騒ぎだ。";
	}
	close;
}

lasa_fild01.gat,60,322,3	script	自警団員アリオ#lasa_fil	10154,{
	mes "[自警団員アリオ]";
	if(Job == Job_Summoner) {
		mes "ミッドガルドには行けたか？";
		mes "大丈夫、君なら何が来ても";
		mes "乗り越えていけるさ。";
	}
	else {
		mes "私はアリオ。ここで自警団への";
		mes "入団希望者のレクチャーをしている。";
	}
	close;
}

lasa_dun01.gat,29,146,5	script	自警団員#lasa_dun01	10162,{
	mes "[自警団員]";
	if(Job == Job_Summoner) {
		mes "おや、冒険者さん。";
		mes "タルトゥーフィに";
		mes "会いに来たんですか？";
	}
	else {
		mes "おや、新大陸の冒険者さんが";
		mes "こんなところに何の用ですか？";
	}
	close;
}

lasa_dun03.gat,162,158,3	script	タルトゥーフィ	10161,{
	mes "[タルトゥーフィ]";
	if(Job == Job_Summoner) {
		mes "やあ、この前は世話になったね。";
		mes "もうミッドガルドには";
		mes "行ったのかい？";
		next;
		mes "[タルトゥーフィ]";
		mes "こっちはバジルリスクのやつらが";
		mes "また騒ぎ出したみたいなんだ。";
		mes "まったくうっとおしい連中だよ。";
	}
	else {
		mes "君はミッドガルド大陸の冒険者？";
		mes "良かったら面白い話でも";
		mes "聞かせてよ。";
	}
	close;
}

lasagna.gat,235,198,5	script	ペロン団長	10152,{
	mes "[ペロン団長]";
	if(Job == Job_Summoner) {
		mes "ミッドガルド大陸は";
		mes "とても厳しい所だ。";
		mes "日頃からの鍛錬を忘れないように。";
	}
	else {
		mes "自警団を統括するペロンと申します。";
		mes "何もない島ですが、";
		mes "ゆっくりしていってください。";
		mes "人族の方々は大歓迎ですよ。";
	}
	close;
}

conch_in.gat,26,64,5	script	ガムベリー船長	10153,{
	mes "[ガムベリー船長]";
	if(Job == Job_Summoner) {
		mes "そろそろ出航だ。";
		mes "準備はいいか？";
	}
	else {
		mes "新大陸の冒険者か。";
		mes "私はこの船の船長ガムベリーだ。";
	}
	close;
}

conch_in.gat,24,62,5	script	ステルロー	10156,{
	mes "[ステルロー]";
	if(Job == Job_Summoner) {
		mes "なんだ？";
		mes "航海士の仕事に興味があるのか？";
	}
	else {
		mes "俺はステルロー。";
		mes "この船の航海士をやっている。";
	}
	close;
}

conch_in.gat,181,61,5	script	甲板長	421,{
	mes "[甲板長]";
	if(Job == Job_Summoner) {
		mes "もう積み荷は全部片付いたぜ。";
		mes "悪くなっちまう前に、";
		mes "さっさと出航といこうや！";
	}
	else {
		mes "ここの料理長、顔はこええが";
		mes "料理の腕は確かなんだぜ。";
	}
	close;
}

conch_in.gat,181,58,3	script	操舵手	561,{
	mes "[操舵手]";
	if(Job == Job_Summoner) {
		mes "いよいよ出航か。";
		mes "ようやく俺の腕の見せ所が";
		mes "やってきたな。";
	}
	else {
		mes "エッグリンのやろう。";
		mes "まーたサボってやがるな。";
	}
	close;
}

conch_in.gat,186,57,3	script	料理長	548,{
	mes "[料理長]";
	if(Job == Job_Summoner) {
		mes "もう腹が減ったのか？";
		mes "飯にはまだ早いぞ。";
	}
	else {
		mes "なんだ？";
		mes "今は忙しいから後にしてくれ。";
	}
	close;
}

conch_in.gat,122,61,5	script	船員	559,{
	mes "[船員]";
	mes "新大陸には初めてですか？";
	mes "一度も行って見たことない場所に";
	mes "行く気分はどうですか？";
	next;
	mes "[船員]";
	mes "どきどきしませんか？";
	mes "私も初めての時は眠れませんでした。";
	mes "いまだに新大陸に行くときには";
	mes "そう感じます。";
	close;
}

conch_in.gat,169,70,3	script	船員	545,{
	mes "[船員]";
	mes "ステルロー一等航海士なら";
	mes "地図にもない新大陸への航路を";
	mes "また見つけ出しそうな気がする。";
	next;
	mes "[船員]";
	mes "発見の瞬間を自分の目で";
	mes "見るためにも、";
	mes "一日でも長く";
	mes "この船に乗っていなきゃ。";
	close;
}

conch_in.gat,166,68,6	script	船員	544,{
	mes "[船員]";
	mes "ミッドガルドも発見されたけど、";
	mes "他にもあるかな？";
	mes "地図にもない場所。";
	mes "まだ私たちが行ったこともない場所。";
	mes "そんな場所あるかな？";
	close;
}

lasagna.gat,226,181,3	script	カルルー	548,{
	mes "[カルルー]";
	mes "カルーニャミルクの";
	mes "主な材料を知っているか？";
	mes "カルーニャという特別な貝を";
	mes "発酵させて作ったエッセンスと";
	mes "新鮮な牛乳で作られている。";
	next;
	mes "[カルルー]";
	mes "それを適切な量で混ぜる。";
	mes "そこにニャンダレの実を一緒に";
	mes "添えるとみんなが愛する";
	mes "カルーニャミルクになるんだ。";
	close;
}

lasagna.gat,225,290,5	script	作業班長	421,{
	mes "[作業班長]";
	mes "この仕事をやったことある？";
	mes "すぐに覚えられる簡単な事だ。";
	mes "コンキリナ号のガムベリー船長は";
	mes "特に上手かったな。";
	close;
}

lasagna.gat,139,299,3	script	イワシ漁船船長	561,{
	mes "[イワシ漁船船長]";
	mes "イワシ産業が";
	mes "以前より落ち込んでいても";
	mes "人手は常に不足している。";
	close;
}

lasagna.gat,263,156,5	script	おばあちゃん	554,{
	mes "[おばあちゃん]";
	mes "昔のラザーニャは凄かった。";
	mes "道も住民もボロボロ。";
	mes "当時は暗黒期と呼ばれているよ。";
	next;
	mes "[おばあちゃん]";
	mes "ある時、何の遊びなのかしらないが、";
	mes "悪がきどもが";
	mes "他のチンピラたちを更生させる、と";
	mes "無理やり自分たちが作った自警団や";
	mes "猫の手サービスに入れ始めたんだ。";
	next;
	mes "[おばあちゃん]";
	mes "更生したくない奴らは";
	mes "みんなラザーニャを去り、";
	mes "新しい人生を歩んでみたい";
	mes "やつだけが残った。";
	mes "今のラザーニャは";
	mes "全部あの子たちが作ったんだ。";
	close;
}

lasagna.gat,244,231,3	script	イワシ漁船員	544,{
	mes "[イワシ漁船員]";
	mes "この黄色いチーズ道に沿って";
	mes "歩いて行けば、";
	mes "私たちの故郷が現れる。";
	mes "いつかは戻りたい。";
	close;
}

lasagna.gat,260,134,3	script	ラスムス	546,{
	mes "[ラスムス]";
	mes "この黄色いチーズ道は";
	mes "自警団と猫の手サービスが";
	mes "作ったものなんだ。";
	mes "パースタ大陸のどこからでも";
	mes "この黄色のチーズ道を辿っていけば";
	mes "ラザーニャへ帰って来れる。";
	close;
}

lasagna.gat,141,166,5	script	クルメ	555,{
	mes "[クルメ]";
	mes "道を歩いていると悟ることがある。";
	mes "この世界のどこからでも";
	mes "ミートソースの匂いが";
	mes "するということを。";
	close;
}

lasagna.gat,233,174,5	script	酔っ払い	561,{
	mes "[飲み手]";
	mes "カルーニャミルクは";
	mes "ゆっくり混ぜてから飲まなきゃ。";
	mes "最近ここに来た流れ者たちは";
	mes "振って飲んでいるみたいだけど、";
	mes "それはお子ちゃまのやることさ。";
	close;
}

lasagna.gat,236,173,3	script	酔っ払い	561,{
	mes "[飲み手]";
	mes "カルーニャミルクは";
	mes "よく振ってから飲むのが一番だ。";
	mes "発酵されたカルーニャが";
	mes "牛乳と混ざることで作り出される";
	mes "繊細な味を感じることができる。";
	close;
}

lasagna.gat,200,278,5	script	心配そうなドラム	559,{
	emotion 54,"心配そうなドラム#lasagn";
	mes "[心配そうなドラム]";
	mes "最近、不法にイワシを獲る漁船に";
	mes "騙されて乗せられるドラムが";
	mes "多いらしい。怖い世の中になったね。";
	mes "自警団が本気になって";
	mes "探しまわっているらしいですよ。";
	close;
}

lasagna.gat,202,276,5	script	浮かれたドラム	560,{
	emotion 18,"浮かれたドラム#lasagna";
	mes "[浮かれたドラム]";
	mes "やった！";
	mes "豪華クルーズ旅行が当たったぞ！";
	mes "なんて運が良いんだ！";
	mes "早く集合場所の";
	mes "イワシ漁船前に行かなきゃ！";
	close;
}

lasagna.gat,209,301,3	script	ムスタチ	10167,{
	mes "[ムスタチ]";
	mes "新大陸に旅立つ前に";
	mes "身だしなみを整えてみては？";
	close;
}

lasagna.gat,236,179,5	script	ニャンクン	10163,{
	mes "[ニャンクン]";
	mes "困った事があるなら";
	mes "自警団に頼んでみたら？";
	close;
}

lasagna.gat,229,197,5	script	トス	10164,{
	emotion 22;
	mes "[トス]";
	mes "やはり有名な場所だから人が多いな。";
	close;
}

lasagna.gat,228,193,5	script	ポルト	10163,{
	emotion 32;
	mes "[ポルト]";
	mes "ここに来たなら";
	mes "カルーニャミルクは";
	mes "飲んでおかないとな！";
	close;
}

lasagna.gat,226,196,5	script	アラム	10166,{
	emotion 7;
	mes "[アラム]";
	mes "きょろきょろしないの！";
	mes "田舎者丸出しじゃない！";
	close;
}

lasagna.gat,227,187,1	script	ヴォンゴロ	544,{
	mes "[ヴォンゴロ]";
	mes "こんにちは。";
	mes "パブ「オーブン」へようこそ。";
	mes "注文は決まりましたか？";
	next;
	mes "[ヴォンゴロ]";
	mes "ペロン団長、ガムベリー船長、";
	mes "トーマス船長による";
	mes "「オーブンの誓い」の影響で、";
	mes "みんなカルーニャミルクを";
	mes "注文しますが、一番味に";
	mes "自信のあるのはボスの料理です。";
	next;
	mes "[ヴォンゴロ]";
	mes "白身魚に心を込めて手入れした後、";
	mes "ゆでた豆とイモを";
	mes "混ぜてつぶして形作って";
	mes "揚げたものです。";
	mes "本当に美味しいのに";
	mes "誰も注文しません。";
	next;
	mes "[ヴォンゴロ]";
	mes "だから最近は材料も";
	mes "準備しておかないので、";
	mes "急な注文が入ると、";
	mes "魚屋さんまで走って";
	mes "買いに行くんです。";
	next;
	emotion 54;
	mes "[ヴォンゴロ]";
	mes "あーあ、本当に美味しいのに……。";
	close;
}

lasagna.gat,232,187,6	script	フェットゥチーニャ	545,{
	mes "[フェットゥチーニャ]";
	mes "ここで働いてそれなりに経つけど、";
	mes "未だに下っ端なので皿洗いは";
	mes "すべて私の担当です。";
	next;
	mes "[フェットゥチーニャ]";
	mes "船に乗りに行く前に一杯、";
	mes "長い航海を終えて一杯、";
	mes "各地から訪ねて来た冒険者が一杯、";
	mes "元から飲んでいる人が一杯、";
	mes "周りにつられて飲みだす人が一杯……";
	next;
	mes "[フェットゥチーニャ]";
	mes "とにかく洗わないといけない";
	mes "食器の数が想像を超えます。";
	mes "それだけではありませんよ、";
	mes "自警団と猫の手職員たちの泣き言、";
	mes "新米冒険者たちからの相談等々……";
	next;
	emotion 28;
	mes "[フェットゥチーニャ]";
	mes "24時間じゃ足りないです。";
	mes "従業員を増やせばいいのに！";
	close;
}

lasagna.gat,232,181,5	script	リンギュイーネ	559,{
	mes "[リンギュイーネ]";
	mes "ここは自警団本部ですが、";
	mes "冒険者が立ち寄っていく";
	mes "パブでもあります。";
	mes "各地から押し寄せて来た冒険者が";
	mes "経験談を交わしたり、";
	mes "冒険の仲間を探したりもします。";
	next;
	mes "[リンギュイーネ]";
	mes "最近では新大陸に旅立つ前に";
	mes "情報を仕入れに来る人が増えました。";
	next;
	mes "[リンギュイーネ]";
	mes "十数年前には不良ドラムたちを";
	mes "更生させて自警団に入団させるための";
	mes "場所としても使われました。";
	mes "それ以前は荒くれ者の船乗りたちが";
	mes "一日の疲れを癒す場所だったんです。";
	next;
	mes "[リンギュイーネ]";
	mes "ペロン団長、ガムベリー船長、";
	mes "トーマス船長もここで出会いました。";
	mes "3人はここで義兄弟の絆を結び、";
	mes "その後の功労でここラザーニャの";
	mes "生きる伝説になりました。";
	next;
	mes "[リンギュイーネ]";
	mes "彼らに憧れてやってくる";
	mes "冒険者も多いんですよ。";
	close;
}

lasagna.gat,190,239,5	script	幼いニャンコ#lasagna_01	559,{
	unittalk "幼いニャンコ : 私はこの遊び場の隊長だにゃ～。";
	end;
}

lasagna.gat,180,230,7	script	幼いニャンコ#lasagna_02	560,{
	unittalk "幼いニャンコ : ハァ……こんな幼稚なやつらとは一緒に遊べないにゃ～。";
	end;
}

lasagna.gat,192,245,7	script	幼いニャンコ#lasagna_03	554,{
	unittalk "幼いニャンコ : 毛糸の塊がひとつ、ななつ、ふたつ、むっつ……多いにゃ!!";
	end;
}

lasagna.gat,184,234,5	script	幼いニャンコ#lasagna_04	422,{
	unittalk "幼いニャンコ : これどうして転がらないにゃ～？転がるようにしてにゃ～。";
	end;
}

lasagna.gat,186,231,3	script	幼いニャンコ#lasagna_05	10167,{
	emotion 28;
	unittalk "幼いニャンコ : シーソーに乗りながら一緒に遊びたいやつは集まれ～。";
	end;
}

lasagna.gat,211,186,5	script	乗船案内員	559,{
	mes "[乗船案内員]";
	mes "こんにちは！";
	mes "新大陸に旅立つ船はここから北の";
	mes "船着き場に停泊していますよ。";
	close;
}

lasagna.gat,222,187,3	script	ボス	548,{
	mes "[ボス]";
	mes "なんだ？";
	mes "あんたもカルーニャミルクかい？";
	close;
}

lasagna.gat,202,291,3	script	自警団案内員	10162,{
	mes "[自警団案内員]";
	mes "港町ラザーニャへようこそ！";
	mes "助けが必要な時は";
	mes "いつでもファルファーレ自警団を";
	mes "訪ねて下さい。";
	close;
}

lasagna.gat,174,160,3	script	自警団案内員	10162,{
	mes "[自警団案内員]";
	mes "こんにちは。";
	mes "良い天気ですにゃ。";
	close;
}

lasagna.gat,233,197,5	script	自警団員オリオ	10155,{
	mes "[自警団員オリオ]";
	mes "この方はファルファーレ自警団の";
	mes "団長であるペロン様だ！";
	close;
}

lasagna.gat,77,263,5	script	タルリー	10166,{
	mes "[タルリー]";
	mes "早く仕事を仕上げないと……";
	mes "待ち合わせに間に合わないわ。";
	close;
}

lasagna.gat,191,174,3	script	ゴルリ	547,{
	emotion 45,"ゴルリ#lasagna";
	mes "[ゴルリ]";
	mes "良い天気だにゃあ。";
	close;
}

lasagna.gat,165,125,5	script	道具商人	10163,{
	mes "[道具商人]";
	mes "うちの息子はいったいどこまで";
	mes "配達に行ったっていうんだ？";
	close;
}

lasagna.gat,175,209,3	script	小物売り	547,{
	mes "[小物売り]";
	mes "みんなバーで飲んでて誰も来ない。";
	mes "暇だ……。";
	close;
}

lasagna.gat,73,237,5	script	落ち着きたいドラム	544,{
	mes "[落ち着きたいドラム]";
	mes "この辺りは静かでいい……。";
	mes "中心部は旅行者や酔っ払いが";
	mes "うるさくてたまらん。";
	close;
}

lasagna.gat,71,200,3	script	困っているドラム	546,{
	mes "[困っているドラム]";
	mes "あれ？";
	mes "今日は休みか。";
	mes "どうしよう……。";
	close;
}

lasagna.gat,61,115,3	script	快活なドラム	560,{
	mes "[快活なドラム]";
	mes "俺は気になる物は";
	mes "片っ端から調べる性格なんだ。";
	mes "他人の家の物だって";
	mes "片っ端から調べちゃうぜ！";
	close;
}

lasagna.gat,88,91,3	script	旅に出るドラム	555,{
	mes "[旅に出るドラム]";
	mes "早く新大陸に行かないと！";
	mes "野菜作ってる場合じゃねえ！";
	close;
}

lasagna.gat,186,193,3	script	外から来たドラム	553,{
	mes "[外から来たドラム]";
	mes "ここがラザーニャかぁ！";
	mes "よーし、やってやるぞー！";
	close;
}

lasagna.gat,103,119,5	script	賢いドラム	545,{
	mes "[賢いドラム]";
	mes "この世のすべての生命体は";
	mes "属性を持っている。";
	mes "各々の属性の相性を理解すれば";
	mes "戦いを有利に進められるだろう。";
	next;
	mes "[賢いドラム]";
	mes "無属性？";
	mes "ほう、そうきたか……。";
	close;
}

lasagna.gat,140,269,3	script	繊細な長女	10166,{
	mes "[ゴマー]";
	mes "ねえ、ヨター！";
	mes "ちゃんと片づけなさい！";
	mes "そこに呪符の破片が落ちてるわよ！";
	next;
	emotion 6;
	mes "[ゴマー]";
	mes "ジョギー、";
	mes "タンディが泣きそうじゃない！";
	mes "少しはじっとしていられないの？";
	next;
	emotion 7;
	mes "[ゴマー]";
	mes "ああもう、集中できない！";
	mes "弟たちの面倒を見ていると";
	mes "一日があっという間に過ぎちゃうわ！";
	close;
}

lasagna.gat,131,269,5	script	誠実な次男	555,{
	mes "[ヨター]";
	mes "お父さん、お母さん、";
	mes "無事に戻って来て下さい。";
	next;
	mes "‐呟きながら何かを作っている‐";
	close;
}

lasagna.gat,131,274,5	script	勇敢な三男	10164,{
	mes "[ジョギー]";
	mes "ウィィィィン！";
	mes "イヌハッカ爆撃のジョギーだぞ！";
	mes "武器を捨てて投降しろ！";
	close;
}

lasagna.gat,140,274,3	script	弱気な四男	546,{
	mes "[タンディ]";
	mes "お姉ちゃんはよく怒るけど、";
	mes "いつも綺麗にいられるように";
	mes "新しい洋服を作ってくれるんです。";
	mes "お姉ちゃんは大好きです。";
	next;
	mes "[タンディ]";
	mes "兄ちゃんたちは怖いです。";
	mes "タンディ言われた事は";
	mes "ちゃんと聞くように努力してます。";
	next;
	emotion 28;
	mes "[タンディ]";
	mes "それでもヨター兄ちゃんは";
	mes "笑顔を見せないし、";
	mes "ジョギー兄ちゃんは気合が足りないと";
	mes "よくミミズを持って来るんです。";
	mes "泣きたいです……。";
	close;
}

//============================================================
// 婚礼NPC
//============================================================
lasagna.gat,200,300,3	script	結婚式場の案内#wedd01	10162,{
	mes "[結婚式場の案内]";
	mes "こんにちは！　いい天気ですよね？";
	mes "気持ちのいい日差しです。";
	mes "こんな日に結婚式を挙げるカップルは、";
	mes "一生幸せになる気がします。";
	next;
	mes "[結婚式場の案内]";
	mes "^0000cd結婚式^0000cdに";
	mes "出席しにいらっしゃいましたか？";
	mes "それとも";
	mes "式場の下見にいらっしゃいましたか？";
	next;
	if(select("結婚式ですか？","結婚式場の案内をお願いします") == 1) {
		mes "[結婚式場の案内]";
		mes "はい！";
		mes "愛する人と一秒でも長く一緒に居たいと";
		mes "思ったことのある人なら、";
		mes "お分かりですよね？";
		next;
		mes "[結婚式場の案内]";
		mes "この人となら一生を共にしたい";
		mes "という気持ちが！";
		next;
		mes "[結婚式場の案内]";
		mes "結婚すれば、いつもそばにいられるから";
		mes "良いですよね！";
		mes "それ以外にも特別なスキルを使用し、";
		mes "逢いたくなった時に、";
		mes "自分の前に召喚することも出来ますよ。";
		next;
		mes "[結婚式場の案内]";
		mes "伴侶が危ない時、";
		mes "相手を護れるスキルも使用できます。";
		next;
		mes "[結婚式場の案内]";
		mes "その他にも良いところはありますが、";
		mes "新婚の二人だけが行けるリゾート地の";
		mes "ジャワイで二人きりの時間を過ごせるのも";
		mes "最高です。";
		next;
		mes "[結婚式場の案内]";
		mes "また、可愛い子供を二人だけの";
		mes "養子として迎え、幸せな家庭を";
		mes "築くこともできます。";
		next;
		mes "[結婚式場の案内]";
		mes "ここ、ラザーニャには各地から";
		mes "多様な人たちが愛を誓い合うために";
		mes "訪れます。";
		next;
		mes "[結婚式場の案内]";
		mes "美しい結婚式場で、";
		mes "愛する人との結婚式をあげるのは";
		mes "いかがでしょうか？";
		close;
	}
	mes "[結婚式場の案内]";
	mes "結婚式場へ行かれますか？";
	next;
	mes "[結婚式場の案内]";
	mes "結婚式場は";
	mes "^0000cdラザーニャの北東にある橋を渡る^0000cdと";
	mes "すぐですから、探しやすいです。";
	next;
	mes "[結婚式場の案内]";
	mes "この赤い毛糸を追って行くと、";
	mes "道に迷うことはありません。";
	next;
	mes "[結婚式場の案内]";
	mes "では幸せに！";
	close2;
	warp "lasagna.gat",335,246;
	end;
}
lasagna.gat,163,84,3	duplicate(結婚式場の案内#wedd01)	結婚式場の案内#wedd02	10162

lasagna.gat,344,275,3	script	フローリン#do_wedd	10163,{
	mes "[フローリン]";
	mes "お花の香りがいいでしょう？";
	mes "新しい門出を迎える";
	mes "幸せな新婚さんのために、";
	mes "特別準備したお花なんです。";
	next;
	mes "[フローリン]";
	mes "微かな風でも、香りが漂います。";
	mes "二人の将来に好い香りが";
	mes "いっぱい広がって欲しいとの、";
	mes "私の願いを込めたお花です。";
	close;
}

lasagna.gat,320,268,7	script	シト#do_wedd	10166,{
	mes "[シト]";
	mes "新しい門出を迎える二人は、";
	mes "いつ見ても美しいですね。";
	next;
	mes "[シト]";
	mes "ここを美しく飾る仕事は難しいです。";
	mes "それでも、見る人が";
	mes "幸福感に浸ってくれたら嬉しいです。";
	close;
}

lasagna.gat,319,290,1	script	女性#do_wedd01	882,{
	mes "[女性]";
	mes "もし人生で一番の出来事が";
	mes "何かと聞かれたら、";
	mes "アナタと結婚したことだと答えるわ。";
	next;
	mes "[男性]";
	mes "俺は二番目の出来事が、";
	mes "キミと結婚したことだけど。";
	next;
	mes "[女性]";
	mes "えぇ？　じゃあ、一番目は？";
	next;
	mes "[男性]";
	mes "キミに初めて出逢った時、";
	mes "その場で求婚したことだね。";
	mes "俺の人生でその時ほど、";
	mes "確信に満ちた時もなかったよ。";
	emotion 31,"男性#do_wedd01";
	misceffect 343,"男性#do_wedd01";
	next;
	mes "[女性]";
	mes "なら私も一番目は、";
	mes "その場で承諾したことにする。";
	emotion 30,"女性#do_wedd01";
	next;
	mes "[男性]";
	mes "俺たち、本当にお似合いだよね。";
	mes "永遠に一緒だよ。";
	close;
}

lasagna.gat,320,291,3	script	男性#do_wedd01	881,{
	mes "[女性]";
	mes "ここの結婚式場、すっごくいいよね？";
	next;
	mes "[男性]";
	mes "そうだな。";
	mes "俺たちの時はこんな場所なかったのに。";
	mes "綺麗だね……。";
	next;
	mes "[女性]";
	mes "でも、大聖堂であげた私たちの結婚式も";
	mes "良かったよね。";
	mes "本当、いつまでも忘れられないよ。";
	emotion 30,"女性#do_wedd01";
	misceffect 343,"女性#do_wedd01";
	next;
	mes "[男性]";
	mes "俺もだよ。";
	emotion 31,"男性#do_wedd01";
	next;
	mes "[女性]";
	mes "私たちの25周年は、";
	mes "ここでまた結婚式をあげようか？";
	next;
	mes "[男性]";
	mes "それ、いいね!!";
	next;
	mes "[女性]";
	mes "25周年はまだ遠いけど、";
	mes "ジャワイへ行きあの日の想い出を";
	mes "振り返るのはすぐ出来るよね！";
	next;
	mes "[男性]";
	mes "そうだね！　あの時の想い出を！";
	next;
	mes "[女性]";
	mes "今すぐ行こう！　はやく！";
	close;
}

lasagna.gat,316,206,5	script	女性#do_wedd02	958,{
	mes "[女性]";
	mes "ダーリンはどうして";
	mes "見ても見てもまた見たくなるの？";
	emotion 3,"女性#do_wedd02";
	next;
	mes "[あなたに逢いたい]";
	misceffect 343,"女性#do_wedd02";
	next;
	mes "[男性]";
	mes "俺もハニーをずっとずっと見ていたい。";
	emotion 3,"男性#do_wedd02";
	next;
	mes "[男性]";
	mes "ところで、";
	mes "ここまで来るのに疲れたりしてない？";
	next;
	mes "[君だけは護るよ]";
	misceffect 313,"女性#do_wedd02";
	next;
	mes "[女性]";
	mes "ダーリンがいてくれて、本当に助かるわ。";
	emotion 30,"女性#do_wedd02";
	next;
	mes "[男性]";
	mes "俺がハニーの回復剤だからね。";
	emotion 31,"男性#do_wedd02";
	close;
}

lasagna.gat,317,205,1	script	男性#do_wedd02	962,{
	mes "[男性]";
	mes "ここが結婚式場らしい。";
	mes "見て！　本当に綺麗だ。";
	emotion 3,"男性#do_wedd02";
	next;
	mes "[女性]";
	mes "私たちも、";
	mes "ここで式をあげましょう！";
	emotion 3,"女性#do_wedd02";
	next;
	mes "[男性]";
	mes "今の言葉……プロポーズ？";
	next;
	mes "[女性]";
	mes "そう、プロポーズなんです！";
	mes "私のダーリン。";
	emotion 30,"女性#do_wedd02";
	misceffect 343,"女性#do_wedd02";
	next;
	mes "[男性]";
	mes "お、お……俺、今、凄く感動しすぎて、";
	mes "こと……言葉が上手く出ない……。";
	emotion 28,"男性#do_wedd02";
	next;
	mes "[女性]";
	mes "泣くのはいいけれど、";
	mes "返事はしなくちゃね。";
	next;
	mes "[男性]";
	mes "はい、解りました。";
	mes "あなたと永遠を誓います。";
	emotion 31,"男性#do_wedd02";
	misceffect 343,"男性#do_wedd02";
	close;
}

lasagna.gat,346,237,5	script	父さん#do_wedd01	10164,{
	mes "[父さん]";
	mes "ジャジャーン!!";
	mes "ここが僕の住んでいたラザーニャだよ！";
	mes "どう？";
	next;
	mes "[父さん]";
	mes "あれ？　母さん？　坊や？";
	mes "みんなどこ？";
	mes "まだ到着しなかったのかな？";
	emotion 1,"父さん#do_wedd01";
	next;
	mes "[父さん]";
	mes "母さん～、はやく来て！";
	next;
	mes "[あなたに逢いたい]";
	next;
	mes "[父さん]";
	mes "母さん～、はやく来て！";
	misceffect 36,"母さん#do_wedd01";
	cloakoffnpc "母さん#do_wedd01";
	next;
	mes "[母さん]";
	mes "あっ、ここはどこ？";
	next;
	mes "[父さん]";
	mes "来ないから、僕が呼んだよ。";
	mes "坊やも呼ばなきゃ。";
	next;
	mes "[坊や、いらっしゃい]";
	next;
	mes "[父さん]";
	mes "坊や～";
	misceffect 36,"子ども#do_wedd01";
	cloakoffnpc "子ども#do_wedd01";
	next;
	mes "[母さん]";
	mes "大きな魚を解体するのを";
	mes "見てる最中だったのに。";
	next;
	mes "[子ども]";
	mes "そうそう！　面白かったのに！";
	next;
	mes "[父さん]";
	mes "そう？　ごめん。";
	mes "代わりに父さんがもっと面白いものを";
	mes "見せてあげるよ。";
	next;
	mes "[子ども]";
	mes "うん！";
	mes "でもさっき見てたのを見てから！";
	cloakonnpc "子ども#do_wedd01";
	next;
	mes "[母さん]";
	mes "私も見てから来るね。";
	cloakonnpc "母さん#do_wedd01";
	next;
	mes "[父さん]";
	mes "母さん、坊や……。";
	mes "僕も、僕も連れてって……。";
	emotion 28,"父さん#do_wedd01";
	close;
}

lasagna.gat,347,235,7	script	母さん#do_wedd01	10148,{
	end;
OnInit:
	cloakonnpc;
	end;
}

lasagna.gat,349,237,1	script	子ども#do_wedd01	10167,{
	end;
OnInit:
	cloakonnpc;
	end;
}

lasagna.gat,302,323,3	script	ジャワイブ	10159,{
	mes "[ジャワイブ]";
	mes "新婚さんも、結婚された2人も、";
	mes "いつでも行ける幻のリゾート地。";
	mes "「ジャワイ」にみなさまを";
	mes "招待いたします！";
	next;
	if(select("ジャワイ？","ジャワイへ出発～") == 1) {
		mes "[ジャワイブ]";
		mes "ミッドガルド大陸から遠く離れた";
		mes "とある場所に、ひとつの島があります。";
		mes "ロマンチックで甘い時間を";
		mes "過ごせる場所なんです。";
		next;
		mes "[ジャワイブ]";
		mes "そこはハネムーンで有名な場所で、";
		mes "結婚された方のみ行けます。";
		next;
		mes "[ジャワイブ]";
		mes "その特別な場所への船賃は";
		mes "^0000cd100,000z^000000になります。";
		next;
		mes "[ジャワイブ]";
		mes "特別な人がいらしたら、";
		mes "共に甘い時間を過ごしてみるのは";
		mes "いかがですか？";
		close;
	}
	if(!(PartnerId)) {
		mes "[ジャワイブ]";
		mes "どうされましたか？";
		mes "この船は、ハネムーンで有名な";
		mes "ジャワイへ行く船です。";
		next;
		mes "[ジャワイブ]";
		mes "大変残念ながら、";
		mes "ジャワイへ行けるのは";
		mes "既婚者のみになります。";
		next;
		mes "[ジャワイブ]";
		mes "代わりに心躍る冒険の旅へ";
		mes "出かけるのは如何ですか？";
		close;
	}
	if(Zeny < 100000) {
		mes "[ジャワイブ]";
		mes "申し訳ありませんが、";
		mes "ジャワイ行きの船賃は";
		mes "^0000cd100,000z^000000になります。";
		mes "所持金をご確認ください。";
		close;
	}
	// 未調査
	mes "[ジャワイブ]";
	mes "楽しいご旅行になりますように。";
	mes "では、「ジャワイ」へ出発します！";
	close2;
	set Zeny,Zeny-100000;
	warp "jawaii.gat",245,125;
	end;
}
