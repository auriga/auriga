//= Auriga Script ==============================================================
// Ragnarok Online Nightmare mode Pyramids Script	by refis
//==============================================================================

//============================================================
// ピラミッドナイトメア 転送NPC
//------------------------------------------------------------
moc_prydb1.gat,103,54,3	script	怪しい猫#prydn1	547,{
	if(BaseLevel < 100) {
		mes "[怪しい猫]";
		mes "まさかマミーに";
		mes "やられてしまうとは……";
		mes "‐^ff0000BaseLv100以上^000000になると";
		mes "　この場所から";
		mes "　ピラミッドダンジョン　秘密の地下室";
		mes "　入場が可能となります‐";
		close;
	}
	mes "[怪しい猫]";
	mes "この先に行きたいのか？";
	mes "この先は私が発見した特別な場所だ！";
	mes "どうしても行きたいと言うなら";
	mes "通行料として^ff00005,000^000000Zenyいただこう！";
	next;
	switch(select("5,000Zenyを払って出発","話を聞く","その場を去る")) {
	case 1:
		if(Zeny < 5000) {
			// 未調査
			mes "[怪しい猫]";
			mes "にゃにゃ！";
			mes "お金が足りないなら話にならない！";
			close;
		}
		mes "[怪しい猫]";
		mes "よし。それじゃあついて来て！";
		close2;
		set Zeny,Zeny-5000;
		warp "moc_prydn1.gat",93,96;
		end;
	case 2:
		mes "[怪しい猫]";
		mes "今まで長い間、積み上げてきた名声が";
		mes "地に落ちてしまう日が来るとは……。";
		next;
		mes "[怪しい猫]";
		mes "あいつら本当におかしいんだ……。";
		mes "マミーのくせに。　マミーだろ!!";
		mes "あんなに強いなんて！";
		next;
		if(select("続けて聞く","会話をやめる") == 2) {
			mes "‐あなたはその場を去った‐";
			close;
		}
		mes "[怪しい猫]";
		mes "そう。それは私が偶然";
		mes "隠し通路の先にある、宝を見つけて";
		mes "採掘をしていた時の事だ。";
		next;
		mes "[怪しい猫]";
		mes "遠くからマミーが近寄って来たんだよ。";
		mes "一目見てマミーだとわかったから";
		mes "気にせず作業をしていたんだ。";
		mes "マミーなんて私の敵ではないからね。";
		mes "そうしたらだ……！";
		next;
		mes "[怪しい猫]";
		mes "体が飛んで行くくらいの";
		mes "強烈なビンタをうたれたよ。";
		mes "このカワイイ猫を……。";
		mes "まさかあんなに強いとは。";
		mes "覚えとけよ、包帯野郎め!!";
		next;
		mes "[怪しい猫]";
		mes "この中にいるモンスター達の";
		mes "^ff0000見た目に惑わされるなよ^000000。";
		mes "今まで遭遇した事のある奴だと";
		mes "油断していると痛い目に遭うぞ！";
		next;
		mes "[怪しい猫]";
		mes "というわけで採掘が出来ない代わりに";
		mes "ここを通る冒険者から通行料を取って";
		mes "生計を立てる事にした。";
		mes "猫にも生活があるんだよ！";
		next;
		mes "[怪しい猫]";
		mes "そうそう、中に行けばきっと";
		mes "仲間が採掘を試みてるだろう。";
		mes "手伝ってくれれば";
		mes "一攫千金のチャンスに";
		mes "ありつけるかもしれないぞ。";
		close;
	case 3:
		mes "‐あなたはその場を去った‐";
		close;
	}
OnInit:
	waitingroom "秘密の地下室",0;
	end;
}

moc_prydn1.gat,94,98,3	script	怪しい猫#prydn2	547,{
	mes "[怪しい猫]";
	mes "怪しいモンスターが";
	mes "うようよしているな……。";
	mes "物騒だし早く元の場所に帰ろう。";
	next;
	if(select("戻る","まだ残る") == 2) {
		emotion 4;
		mes "[怪しい猫]";
		mes "まだ残るのか？";
		mes "戻りたくなったら";
		mes "声をかけてくれ。";
		close;
	}
	mes "[怪しい猫]";
	mes "さぁさぁ、早く戻ろう。";
	close2;
	warp "moc_prydb1.gat",100,57;
	end;
}

//============================================================
// ピラミッドナイトメア 討伐NPC
//------------------------------------------------------------
moc_ruins.gat,75,170,3	script	採掘に向かう猫#prydn	561,{
	if(!checkquest(118850)) {
		mes "[採掘に向かう猫]";
		if(strnpcinfo(2) == "prydn_out") {
			mes "さーて、行くかな。";
		}
		else {
			mes "くそっ、やはりモンスターが多いな。";
		}
		mes "　";
		if(BaseLevel < 100 || BaseLevel > 135) {
			mes "‐^ff0000BaseLv100から135の間のみ^000000";
			mes "　受諾する事が出来るクエストです‐";
			close;
		}
		mes "おっ、なんだお前。冒険者か？";
		mes "くくっ。いい所にきたな。";
		mes "ちょっと俺の手伝いをしてくれないか？";
		next;
		mes "[採掘に向かう猫]";
		mes "俺は今この辺に眠っているお宝を探して";
		mes "採掘をしているんだ。";
		mes "ただ、採掘場所ではモンスターが";
		mes "邪魔をしてきてな。";
		next;
		mes "[採掘に向かう猫]";
		mes "俺も戦闘は嫌いじゃないんだが";
		mes "今は採掘に集中したいし、";
		mes "ちょっとした理由もあってな。";
		mes "お前にモンスターを";
		mes "倒して来て欲しいんだ。";
		next;
		mes "[採掘に向かう猫]";
		mes "もちろん、お礼ははずむぞ。";
		mes "モンスターを倒して来た数に応じて";
		mes "おたから袋から報酬を渡してやる。";
		mes "どうだ。やってくれないか？";
		next;
		if(select("手伝う","断る") == 2) {
			mes "[採掘に向かう猫]";
			mes "ちっ。";
			mes "なんだよつれねえな。";
			close;
		}
		mes "[採掘に向かう猫]";
		mes "ありがてえ。";
		mes "それじゃあもう一度話しかけてくれ。";
		setquest 118850;
		compquest 118850;
		close;
	}
	if(checkquest(118855) & 0x2)
		delquest 118855;
	if(checkquest(118860) & 0x2)
		delquest 118860;
	mes "[採掘に向かう猫]";
	mes "おう。よく来たな。";
	mes "今日はどうする？";
	next;
	set '@str$,"討伐を受ける/報告する";
	if(BaseLevel < 100 || BaseLevel > 135)
		set '@str$,"報告する";
	switch(select('@str$,"討伐をあきらめる","説明を聞く","会話をやめる")) {
	case 1:
		if((checkquest(118855) && checkquest(118855) & 0x2 == 0) ||
			(checkquest(118860) && checkquest(118860) & 0x2 == 0)) {
			mes "[採掘に向かう猫]";
			mes "ん。お前か";
			mes "今はまだ大丈夫だ。";
			mes "あまり根詰めずにやってくれ。";
			mes "　";
			mes "‐このクエストは";
			mes "　1時間に1回、挑戦出来ます‐";
			close;
		}
		set '@d[0],checkquest(97000);
		set '@d[1],checkquest(97002);
		set '@d[2],checkquest(97004);
		set '@d[3],checkquest(97006);
		set '@d[4],checkquest(97008);
		set '@d[5],checkquest(97010);
		if('@d[0]+'@d[1]+'@d[2]+'@d[3]+'@d[4]+'@d[5] == 6) {
			mes "[採掘に向かう猫]";
			mes "どうだ進み具合は？";
			mes "結構あいつら強いだろう。";
			mes "期待しているぞ。";
			close;
		}
		if(('@d[0]+'@d[1]+'@d[2]) > 3 || ('@d[3]+'@d[4]+'@d[5]) > 3) {
			set '@cnt,'@cnt + ('@d[0]&4)? 1: 0;
			set '@cnt,'@cnt + ('@d[1]&4)? 3: 0;
			set '@cnt,'@cnt + ('@d[2]&4)? 6: 0;
			set '@cnt,'@cnt + ('@d[3]&4)? 1: 0;
			set '@cnt,'@cnt + ('@d[4]&4)? 3: 0;
			set '@cnt,'@cnt + ('@d[5]&4)? 6: 0;
			mes "[採掘中の猫]";
			mes "ほう。充分な量のモンスターを";
			mes "倒して来てくれたようだな。";
			mes "それじゃあお前には";
			mes "おたから袋から^ff0000" +'@cnt+ "^000000個ほど";
			mes "アイテムを渡すことにしよう。";
			mes "報酬を受け取るか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[採掘中の猫]";
				mes "なんだ。荷物でも多いのか？";
				mes "報酬を受け取る準備が出来たら";
				mes "またくるんだな。";
				close;
			}
			mes "[採掘中の猫]";
			mes "それじゃあ渡そう。";
			mes "この^ff0000おたから袋^000000には";
			mes "色々なものが入っている。";
			mes "何が出るかはお前の運しだいだ。";
			mes "幸運を祈るんだな。";
			next;
			if('@d[0]&4) {
				delquest 97000;
				delquest 97002;
				delquest 97004;
			}
			if('@d[3]&4) {
				delquest 97006;
				delquest 97008;
				delquest 97010;
			}
			//ダイヤモンド１カラット,ダイヤモンド２カラット,ダイヤモンド３カラット
			//銀の指輪,金の指輪,ダイヤの指輪,黄金,宝箱　1個,宝箱　2個,宝箱　5個
			setarray '@gain,731,732,2611,2610,2613,969,7444,7444,7444, 730;
			setarray '@num,   1,  1,   1,   1,   1,  1,   1,   2,   5,   1;
			setarray '@rate,300,100, 300, 200, 200,100, 100,  80,  50,1000;
			for(set '@i,0; '@i < '@cnt; set '@i,'@i+1) {
				for(set '@j,0; '@j < getarraysize('@gain); set '@j,'@j+1) {
					if(rand(1000) < '@rate['@j]) {
						getitem '@gain,'@num;
						break;
					}
				}
			}
			mes "[採掘中の猫]";
			mes "よし。こんなもんだな。";
			mes "ありがとうな。";
			close;
		}
		if(BaseLevel < 100 || BaseLevel > 135) {
			// 未調査
			mes "‐^ff0000BaseLv100から135の間のみ^000000";
			mes "　受諾する事が出来るクエストです‐";
			close;
		}
		mes "[採掘に向かう猫]";
		mes "^ff0000グレイヴアクラウス^000000と";
		mes "^ff0000グレイヴミノタウロス^000000を";
		mes "倒してきてくれ。";
		if(!checkquest(118855))
			setquest 118855;
		if(!checkquest(97000)) {
			setquest 97000;
			setquest 97002;
			setquest 97004;
		}
		if(!checkquest(118860))
			setquest 118860;
		if(!checkquest(97006)) {
			setquest 97006;
			setquest 97008;
			setquest 97010;
		}
		if(checkquest(118855) && !checkquest(118860)) {
			next;
			mes "[採掘中の猫]";
			mes "おっと。";
			mes "グレイヴミノタウロス討伐は";
			mes "お願いしたばかりのようだな。";
			mes "これは無しにしよう。";
			next;
			mes "[採掘中の猫]";
		}
		else if(!checkquest(118855) && checkquest(118860)) {
			next;
			mes "[採掘中の猫]";
			mes "おっと。";
			mes "グレイヴアクラウス討伐は";
			mes "お願いしたばかりのようだな。";
			mes "これは無しにしよう。";
			next;
			mes "[採掘中の猫]";
		}
		mes "頼んだぞ。";
		close;
	case 2:
		if(!checkquest(97000) && !checkquest(97006)) {
			mes "[採掘に向かう猫]";
			mes "ん？　依頼を諦めたい？";
			mes "だが、おまえにお願いしている";
			mes "依頼は無いようだぞ。";
			close;
		}
		mes "[採掘に向かう猫]";
		mes "お前には荷が重かったか？";
		mes "まぁ仕方ない。";
		mes "もしあきらめるのであれば";
		mes "途中まで進行したものも含めて";
		mes "全て無しになるが本当に良いか？";
		next;
		if(select("もう少し頑張る","^ff0000依頼をあきらめる^000000") == 1) {
			mes "[採掘に向かう猫]";
			mes "そうか。";
			mes "それじゃ頼んだぞ！";
			close;
		}
		mes "[採掘に向かう猫]";
		mes "そうか。仕方ないな。";
		mes "わかったよ。";
		mes "その気になったらまた来てくれよな。";
		if(checkquest(97000)) {
			delquest 97000;
			delquest 97002;
			delquest 97004;
		}
		if(checkquest(97006)) {
			delquest 97006;
			delquest 97008;
			delquest 97010;
		}
		close;
	case 3:
		mes "[採掘に向かう猫]";
		mes "簡単な事さ。";
		mes "この辺に生息するモンスターのうち";
		mes "特に採掘の邪魔となる";
		mes "^ff0000グレイヴミノタウロス^000000と";
		mes "^ff0000グレイヴアクラウス^000000を";
		mes "倒して来て欲しいんだ。";
		next;
		mes "[採掘に向かう猫]";
		mes "たくさん倒して来たら";
		mes "たくさん報酬をやろう。";
		mes "　";
		mes "ただし！";
		mes "腕の立つ冒険者は";
		mes "悪いが断らせてもらっている。";
		next;
		mes "‐インフォメーション‐";
		mes "　^ff0000BaseLv100から135までの間^000000";
		mes "　受諾する事が出来るクエストです。";
		mes "　報告後、^ff00001時間^000000は再受諾出来ません。";
		mes "　BaseLv136以上になると、";
		mes "　進行中のクエストのみ";
		mes "　報告が可能です。";
		next;
		mes "[採掘に向かう猫]";
		mes "俺達のような猫は冒険者との共存は";
		mes "必要不可欠だ。";
		mes "俺は腕っぷしならその辺の冒険者には";
		mes "負けるつもりは無いけどな。";
		mes "仲間の猫みんなが";
		mes "そういうわけじゃねえ。";
		next;
		mes "[採掘に向かう猫]";
		mes "だから仲間内で集まったときに";
		mes "みんなで集めたこのおたからの一部で";
		mes "成長中の冒険者の補助をしていこうと";
		mes "話をしていたのさ。";
		next;
		mes "[採掘に向かう猫]";
		mes "それならばと俺らのリーダーが";
		mes "現在採掘中のこのピラミッドで";
		mes "採掘の邪魔をするモンスターを";
		mes "倒してくれる冒険者に";
		mes "報酬という形で渡してはどうだと";
		mes "提案をしたんだよ。";
		next;
		mes "[採掘に向かう猫]";
		mes "これなら俺らにとっても";
		mes "手が減らせるし恩恵がある。";
		mes "　";
		mes "どうだ。なかなか名案だろ？";
		next;
		mes "[採掘に向かう猫]";
		mes "ということで報酬は";
		mes "豪華だと思ってくれていいぜ。";
		next;
		mes "[採掘に向かう猫]";
		mes "ただ、俺は細かい話が苦手でな。";
		mes "報酬については計算の得意な仲間に";
		mes "メモで書いてもらってある。";
		mes "詳しくはそれを見てくれ。";
		next;
		mes "‐あなたはきれいにたたまれた";
		mes "　手紙を受け取り、目を通した‐";
		next;
		mes "[手紙]";
		mes "　このお手紙を読んでいるあなたへ。";
		mes "　我々の採掘の手伝いをしてくれて";
		mes "　ありがとうですにゃ。";
		mes "　今から手伝ってくれた際の";
		mes "　報酬について説明しますにゃ。";
		next;
		mes "[手紙]";
		mes "　お渡しする報酬は次の通りですにゃ。";
		mes "　^ff0000グレイヴミノタウロス^000000、を";
		mes "　100体倒す……おたから袋の中身^ff00001^000000個";
		mes "　200体倒す……おたから袋の中身^ff00003^000000個";
		mes "　300体倒す……おたから袋の中身^ff00006^000000個";
		next;
		mes "[手紙]";
		mes "　^ff0000グレイヴアクラウス^000000、を";
		mes "　20体倒す……おたから袋の中身^ff00001^000000個";
		mes "　40体倒す……おたから袋の中身^ff00003^000000個";
		mes "　60体倒す……おたから袋の中身^ff00006^000000個";
		next;
		mes "[手紙]";
		mes "　^ff0000おたから袋^000000とは";
		mes "　我々が採掘して集めた貴重な品々を";
		mes "　一時的に保管している袋ですにゃ。";
		mes "　ダイヤモンドから宝箱まで";
		mes "　色々なものが入っていますにゃ。";
		mes "　中身は全て価値のあるものですにゃ！";
		next;
		mes "[手紙]";
		mes "　そうそう。";
		mes "　報酬は^ff0000複数合わせて^000000渡しますにゃ。";
		mes "　例えば200体倒してきた場合は";
		mes "　100体倒してきた分の報酬と";
		mes "　200体倒してきた分の報酬を";
		mes "　両方渡しますにゃ。";
		next;
		mes "[手紙]";
		mes "　受注した後、1時間待ってくれれば";
		mes "　何度でも^ff0000繰り返し出来ます^000000にゃ。";
		mes "　いっぱい手伝ってくださいにゃ。";
		mes "　採掘がはかどりますにゃ。";
		mes "　にゃっはっは。";
		mes "　以上ですにゃ！";
		next;
		mes "‐手紙はここまでのようだ‐";
		next;
		mes "[採掘に向かう猫]";
		mes "読んでくれたか？";
		mes "というわけでよろしく頼むぜ。";
		mes "期待しているぞ。";
		close;
	case 4:
		mes "[採掘に向かう猫]";
		mes "なんだ。";
		mes "声をかけるのは用がある時にしてくれ。";
		close;
	}
OnInit:
	waitingroom "討伐クエスト", 0;
	end;
}

moc_prydn1.gat,97,96,3	duplicate(採掘に向かう猫#prydn)	採掘中の猫#prydn_f1	561
moc_prydn2.gat,97,59,3	duplicate(採掘に向かう猫#prydn)	採掘中の猫#prydn_f2	561

moc_prydn2.gat,198,11,0	warp	pd_nightmare_2to1	1,1,moc_prydn1.gat,213,10
moc_prydn1.gat,218,9,0	warp	pd_nightmare_1to2	1,1,moc_prydn2.gat,195,11

//============================================================
// ピラミッドナイトメア1F 隠しワープ
//------------------------------------------------------------
moc_prydn1.gat,17,186,0	script	#prydn_Secret_1-1	139,0,10,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,24,171,0	script	#prydn_Secret_1-2	139,1,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",219,40;
	end;
}

moc_prydn1.gat,214,31,0	script	#prydn_Secret_2-1	139,10,0,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,219,44,0	script	#prydn_Secret_2-2	139,1,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",24,175;
	end;
}

moc_prydn1.gat,15,58,0	script	#prydn_Secret_3-1	139,10,0,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,9,72,0	script	#prydn_Secret_3-2	139,2,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",220,133;
	end;
}

moc_prydn1.gat,214,157,0	script	#prydn_Secret_4-1	139,10,0,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,220,129,0	script	#prydn_Secret_4-2	139,2,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",9,68;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn1.gat,58,57,0	script	#prydn_Secret_5-1	139,0,10,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,72,52,0	script	#prydn_Secret_5-2	139,1,2,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",35,220;
	end;
}

moc_prydn1.gat,59,214,0	script	#prydn_Secret_6-1	139,0,10,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,31,219,0	script	#prydn_Secret_6-2	139,1,2,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",68,52;
	end;
}

moc_prydn1.gat,101,169,0	script	#prydn_Secret_7-1	139,0,10,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,87,164,0	script	#prydn_Secret_7-1	139,1,2,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",194,66;
	end;
}

moc_prydn1.gat,183,72,0	script	#prydn_Secret_8-1	139,10,0,{
	emotion 1,"";
	end;
}

moc_prydn1.gat,198,66,0	script	#prydn_Secret_8-2	139,1,2,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn1.gat",91,164;
	end;
}

//============================================================
// ピラミッドナイトメア2F 隠しワープ
//------------------------------------------------------------
moc_prydn2.gat,179,99,0	script	#prydn_Secret_A	139,1,1,{
	soundeffect "complete.wav", 0, 0;
	warp "moc_prydn2.gat",195,11;
	end;
}

moc_prydn2.gat,193,16,0	script	#prydn_Secret_B-1	139,1,1,{
	showmessage "!?","";
	soundeffect "se_door02.wav", 0, 0;
	hideonnpc "#prydn_Secret_B-1";
	hideoffnpc "#prydn_Secret_B-2";
	initnpctimer;
	end;
OnTimer8000:
	stopnpctimer;
	hideonnpc "#prydn_Secret_B-2";
	hideoffnpc "#prydn_Secret_B-1";
	end;
}

moc_prydn2.gat,193,5,0	script	#prydn_Secret_B-2	139,1,1,{
	soundeffect "complete.wav", 0, 0;
	warp "moc_prydn2.gat",101,187;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,127,47,0	script	#prydn_Secret_C-1	139,1,1,{
	showmessage "!?","";
	soundeffect "se_door02.wav", 0, 0;
	hideonnpc "#prydn_Secret_C-1";
	hideoffnpc "#prydn_Secret_C-2";
	initnpctimer;
	end;
OnTimer8000:
	stopnpctimer;
	hideonnpc "#prydn_Secret_C-2";
	hideoffnpc "#prydn_Secret_C-1";
	end;
}

moc_prydn2.gat,128,58,0	script	#prydn_Secret_C-2	139,1,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn2.gat",135,59;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,133,75,0	script	#prydn_Secret_C-3	139,1,1,{
	showmessage "!?","";
	soundeffect "se_door02.wav", 0, 0;
	hideonnpc "#prydn_Secret_C-3";
	hideoffnpc "#prydn_Secret_C-4";
	initnpctimer;
	end;
OnTimer8000:
	stopnpctimer;
	hideonnpc "#prydn_Secret_C-4";
	hideoffnpc "#prydn_Secret_C-3";
	end;
}

moc_prydn2.gat,133,49,0	script	#prydn_Secret_C-4	139,1,1,{
	soundeffect "se_door02.wav", 0, 0;
	warp "moc_prydn2.gat",126,51;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,29,88,0	script	#prydn_Secret_D-1	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_D-1";
		hideoffnpc "#prydn_Secret_D-2";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_D-2";
	hideoffnpc "#prydn_Secret_D-1";
	end;
}

moc_prydn2.gat,44,95,0	script	#prydn_Secret_D-2	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",49,95;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,45,87,0	script	#prydn_Secret_D-3	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_D-3";
		hideoffnpc "#prydn_Secret_D-4";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_D-4";
	hideoffnpc "#prydn_Secret_D-3";
	end;
}

moc_prydn2.gat,45,95,0	script	#prydn_Secret_D-4	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",40,95;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,29,172,0	script	#prydn_Secret_E-1	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_E-1";
		hideoffnpc "#prydn_Secret_E-2";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_E-2";
	hideoffnpc "#prydn_Secret_E-1";
	end;
}

moc_prydn2.gat,44,178,0	script	#prydn_Secret_E-2	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",51,178;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,47,196,0	script	#prydn_Secret_E-3	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_E-3";
		hideoffnpc "#prydn_Secret_E-4";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_E-4";
	hideoffnpc "#prydn_Secret_E-3";
	end;
}

moc_prydn2.gat,47,187,0	script	#prydn_Secret_E-4	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",40,187;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,156,196,0	script	#prydn_Secret_F-1	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_F-1";
		hideoffnpc "#prydn_Secret_F-2";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_F-2";
	hideoffnpc "#prydn_Secret_F-1";
	end;
}

moc_prydn2.gat,156,187,0	script	#prydn_Secret_F-2	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",163,187;
	end;
OnInit:
	hideonnpc;
	end;
}

moc_prydn2.gat,174,172,0	script	#prydn_Secret_F-3	139,1,0,{
OnTouch:
	switch('flag) {
	case 0:
		showmessage "?","";
		set 'flag,1;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 1:
		showmessage "!?","";
		set 'flag,2;
		soundeffect "alarm_move.wav", 0, 0;
		end;
	case 2:
		soundeffect "se_door02.wav", 0, 0;
		hideonnpc "#prydn_Secret_F-3";
		hideoffnpc "#prydn_Secret_F-4";
		initnpctimer;
		end;
	}
OnTimer8000:
	set 'flag,0;
	stopnpctimer;
	hideonnpc "#prydn_Secret_F-4";
	hideoffnpc "#prydn_Secret_F-3";
	end;
}

moc_prydn2.gat,159,178,0	script	#prydn_Secret_F-4	139,1,1,{
	soundeffect "se_door01.wav", 0, 0;
	warp "moc_prydn2.gat",152,178;
	end;
OnInit:
	hideonnpc;
	end;
}

//============================================================
// ピラミッドナイトメアMVP
//------------------------------------------------------------
moc_prydn2.gat,102,182,4	script	アメンホテプの棺#prydn	801,{}

moc_prydn2.gat,0,0,0	script	#moc_prydn2MVP	-1,{
	end;
OnInit:
	initnpctimer;
	end;
OnTimer18000000:
OnTimer19800000:
OnTimer21600000:
OnTimer23400000:
OnTimer25200000:
OnTimer27000000:
OnTimer28800000:
OnTimer30600000:
	if(rand(8))
		end;
OnTimer32400000:
	stopnpctimer;
	hideonnpc "アメンホテプの棺#prydn";
	areamonster "moc_prydn2.gat",0,0,0,0,"墓地の守護者",1098,15,"#moc_prydn2MVP::OnKilled2";
	monster "moc_prydn2.gat",102,85,"アメンホテプ",2362,1,"#moc_prydn2MVP::OnKilled";
	end;
OnKilled:
	initnpctimer;
	hideoffnpc "アメンホテプの棺#prydn";
	end;
OnKilled2:
	end;
}
