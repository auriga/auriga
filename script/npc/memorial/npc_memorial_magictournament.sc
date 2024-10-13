//==============================================================================
// Geffen Magic Tournament Memorial Dungeon Script
//==============================================================================

//==========================================
// 時の通路
//------------------------------------------
dali.gat,98,141,3	script	次元の狭間研究学者#a1	903,{
	if(BaseLevel <= 89) {
		mes "[次元の狭間研究学者]";
		mes "ゲフェン魔法大会への参加者は";
		mes "強者揃いだ。";
		mes "君の実力ではまだ厳しいだろう。";
		next;
		mes "‐この先に進むには^ff0000BaseLv90以上^000000が";
		mes "　必要です‐";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[次元の狭間研究学者]";
		mes "次元の狭間は非常に不安定で";
		mes "一人でしか入れないのだ。";
		mes "パーティーリーダー以外の";
		mes "進入は制限しているから、";
		mes "入りたければ^ff0000パーティーリーダーに";
		mes "なってから私に話しかけてくれないか。^000000";
		close;
	}
	if(getonlinepartymember() >= 2) {
		mes "[次元の狭間研究学者]";
		mes "次元の狭間は非常に不安定で";
		mes "一人でしか入れないのだ。";
		mes "すまないがメンバーを";
		mes "一人に絞ってくれないか。";
		close;
	}
	if(checkquest(9315)) {
		if(checkquest(9309)) {	// 敗退
			delquest 9309;
			delquest 9310;
			delquest 9311;
			delquest 9312;
			delquest 9313;
			delquest 9314;
			mes "[次元の狭間研究学者]";
			mes "狭間から帰ってきたか！";
			mes "それで何があったのだ？";
			next;
			mes "‐狭間での出来事について";
			mes "　知っている内容を話した‐";
			next;
			mes "[次元の狭間研究学者]";
			mes "ふむ……";
			mes "そうかそうか。";
			mes "少し情報が足りないが";
			mes "非常に助かったよ。";
			next;
			mes "[次元の狭間研究学者]";
			mes "だがまだまだ足りない！";
			mes "また私を助けて欲しいのだ。";
			mes "狭間でゲフェン魔法大会について";
			mes "調べてくれないか？";
			mes "待っているよ。";
			delquest 9315;
			close;
		}
		if(checkquest(9308)) {	// 優勝
			delquest 9308;
			delquest 9310;
			delquest 9311;
			delquest 9312;
			delquest 9313;
			delquest 9314;
			mes "[次元の狭間研究学者]";
			mes "無事に帰ってきたか！";
			mes "さあ、どんなことがあったのだ？";
			next;
			mes "‐あなたは狭間での出来事を";
			mes "　話してあげた‐";
			next;
			mes "[次元の狭間研究学者]";
			mes "おおお！";
			mes "そうかそうか！";
			mes "ありがとう、ありがとう!!";
			next;
			mes "[次元の狭間研究学者]";
			mes "だがまだまだ足りない！";
			mes "また私を助けて欲しいのだ。";
			mes "狭間でゲフェン魔法大会について";
			mes "調べてくれないか？";
			mes "待っているよ。";
			delquest 9315;
			close;
		}
		mes "[次元の狭間研究学者]";
		mes "狭間から帰ってきたか！";
		mes "それで何があったのだ？";
		next;
		mes "‐狭間での出来事について";
		mes "　知っている内容を話した‐";
		next;
		mes "[次元の狭間研究学者]";
		mes "うむむ……";
		mes "新しいことは何もないが……。";
		mes "ご苦労だったよ。";
		mes "次も頑張ってくれ。";
		next;
		mes "[次元の狭間研究学者]";
		mes "やはりまだまだ足りない！";
		mes "また私を助けて欲しいのだ。";
		mes "ゲフェン魔法大会について";
		mes "調べてくれないか？";
		mes "待っているよ";
		delquest 9315;
		close;
	}
	if(checkquest(9316)) {
		if(checkquest(9316) & 0x2 == 0 || checkquest(118924) & 0x2 == 0) {
			mes "[次元の狭間研究学者]";
			mes "また調べてきてくれるのか？";
			mes "ん？　しかし……";
			mes "前回の探検から充分な時間が";
			mes "経過していないようだな。";
			next;
			mes "[次元の狭間研究学者]";
			mes "次元の狭間は非常に不安定なんだ。";
			mes "入場してから1回目の";
			mes "^ff0000午前5時以降^000000に来てくれ。";
			mes "但し、最後の入場をしてから";
			mes "^ff00002時間^000000経過しないと";
			mes "中には入れないぞ。";
			close;
		}
		mes "[次元の狭間研究学者]";
		mes "また来てくれると信じていたよ。";
		mes "ありがとう！";
		next;
		mes "[次元の狭間研究学者]";
		mes "次元移動機を通じて";
		mes "狭間の中に入り、";
		mes "ゲフェン魔法大会に参加して";
		mes "昔、存在していた世界の";
		mes "英雄の痕跡を";
		mes "私に知らせてくれないか？";
		next;
		mes "[次元の狭間研究学者]";
		mes "ただ、狭間は非常に不安定で";
		mes "多くの人は入れないのだ。";
		mes "たった一人でしか入れない";
		mes "という点を注意して欲しい。";
		mes "それじゃ入るかい？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[次元の狭間研究学者]";
			mes "そうかい、気が変わったら";
			mes "ぜひとも調べてくれ。";
			close;
		}
		mdcreate "Magic Tournament";
		mes "[次元の狭間研究学者]";
		mes "次元移動機の起動に成功した。";
		mes "起動時間が過ぎる前に";
		mes "早めに出発してくれ。";
		close;
	}
	mes "[次元の狭間研究学者]";
	mes "君は遠い昔、";
	mes "ゲフェンで魔法大会が";
	mes "行われていたことを知っているか？";
	next;
	mes "[次元の狭間研究学者]";
	mes "私はその真実が知りたくて";
	mes "数十年間研究を続けたのだ。";
	mes "そしてこの狭間を";
	mes "ついに見つけたのだ！";
	next;
	mes "[次元の狭間研究学者]";
	mes "しかし私では狭間に入ることが";
	mes "できなかったのだ。";
	mes "おかげでここで研究ばかり";
	mes "していたのだが、";
	mes "そこに君が現れたのさ。";
	next;
	mes "[次元の狭間研究学者]";
	mes "ここまでたどり着いた";
	mes "君なら十二分にこの狭間に入り、";
	mes "ゲフェン魔法大会についても";
	mes "調べられるだろう。";
	next;
	mes "[次元の狭間研究学者]";
	mes "次元移動機を通じて";
	mes "狭間の中に入り、";
	mes "ゲフェン魔法大会に参加して";
	mes "昔、存在していた世界の";
	mes "英雄の痕跡を";
	mes "私に知らせてくれないか？";
	next;
	mes "[次元の狭間研究学者]";
	mes "ただ、狭間は非常に不安定で";
	mes "多くの人は入れないのだ。";
	mes "たった一人でしか入れない";
	mes "という点を注意して欲しい。";
	mes "それじゃ入るかい？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[次元の狭間研究学者]";
		mes "そうかい、気が変わったら";
		mes "ぜひとも調べてくれ。";
		close;
	}
	mdcreate "Magic Tournament";
	mes "[次元の狭間研究学者]";
	mes "次元移動機の起動に成功した。";
	mes "起動時間が過ぎる前に";
	mes "早めに出発してくれ。";
	close;
OnInit:
	waitingroom "ゲフェン魔法大会", 20;
	end;
}

dali.gat,100,147,3	script	次元移動機#a1	10007,{
	if(checkquest(9316)) {
		if(checkquest(9316) & 0x2 == 0 || checkquest(118924) & 0x2 == 0) {
			mes "‐次元の狭間が閉じている。";
			mes "　入場してから1回目の^ff0000午前5時以降^000000に";
			mes "　再度、入場できるだろう。";
			mes "　但し、最後の入場をしてから";
			mes "　^ff00002時間^000000経過しないと";
			mes "　中には入れないようだ‐";
			close;
		}
		if(checkquest(9285)) delquest 9285;
		if(checkquest(9290)) delquest 9290;
		if(checkquest(9287)) delquest 9287;
		if(checkquest(9291)) delquest 9291;
		if(checkquest(9289)) delquest 9289;
		if(checkquest(9292)) delquest 9292;

		if(checkquest(9286)) delquest 9286;
		if(checkquest(9288)) delquest 9288;
		if(checkquest(9308)) delquest 9308;
		if(checkquest(9309)) delquest 9309;
		delquest 9310;
		delquest 9311;
		delquest 9312;
		delquest 9313;
		delquest 9314;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[次元の狭間研究学者]";
		mes "次元の狭間は非常に不安定で";
		mes "一人でしか入れないのだ。";
		mes "パーティーリーダー以外の";
		mes "進入は制限しているから、";
		mes "入りたければ^ff0000パーティーリーダーに";
		mes "なってから私に話しかけてくれないか。^000000";
		close;
	}
	if(getonlinepartymember() >= 2) {
		mes "[次元の狭間研究学者]";
		mes "次元の狭間は非常に不安定で";
		mes "一人でしか入れないのだ。";
		mes "すまないがメンバーを";
		mes "一人に絞ってくれないか。";
		close;
	}
	mes "‐次元移動機がある。";
	mes "　ゲフェン魔法大会に行きますか？‐";
	next;
	if(select("行く","行かない") == 2) {
		mes "‐あなたは次元移動機から離れた‐";
		close;
	}
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "‐次元の狭間が不安定なため";
		mes "　パーティーリーダー一人しか";
		mes "　入ることができない‐";
		close;
	}
	switch(mdenter("Magic Tournament")) {
	case 0:		// エラーなし
		announce "メモリアルダンジョン[Magic Tournament] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99;
		donpcevent getmdnpcname("#メモリアル開始")+ "::OnStart";
		setquest 9316;
		setquest 118924;
		setquest 9315;
		end;
	case 1:		// パーティー未加入
		mes "‐次元の狭間が不安定なため";
		mes "　パーティーリーダー一人しか";
		mes "　入ることができない‐";
		close;
	case 2:		// ダンジョン未作成
		mes "‐パーティーリーダーがダンジョンを";
		mes "　生成していません‐";
		close;
	default:		// その他エラー
		close;
	}
}

dali.gat,92,147,3	script	ゲフェンコイン交換員#1	893,{
	mes "[ゲフェンコイン交換員]";
	mes "こんにちは。";
	mes "私は研究のお手伝いで";
	mes "ゲフェン魔法大会コインを";
	mes "集めています。";
	mes "お礼は色々用意していますので";
	mes "一度ご覧になってください。";
	while(1) {
		next;
		switch(select("盾","アクセサリー","鎧","消耗品","経験値","会話を終了する")) {
		case 1:
			mes "[ゲフェンコイン交換員]";
			mes "盾は2種類が用意されています。";
			mes "どれをご覧になりますか。";
			while(1) {
				next;
				switch(select("マジックリフレクター <^006400コイン^000000 900枚>","大百科事典改訂版 <^006400コイン^000000 900枚>","以前のリストに戻る")) {
				case 1:
					mes "‐<ITEM>マジックリフレクター[1]<INFO>2185</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,2185;
					set '@cost,900;
					break;
				case 2:
					mes "‐<ITEM>大百科事典改訂版[1]<INFO>2186</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,2186;
					set '@cost,900;
					break;
				case 3:
					set '@gain,0;
					break;
				}
				if('@gain == 0) {
					break;
				}
				next;
				mes "[ゲフェンコイン交換員]";
				mes getitemname('@gain)+ "は";
				mes "ゲフェン魔法大会コイン" +'@cost+ "枚と";
				mes "交換可能です。";
				mes "交換なさいますか？";
				next;
				if(select("交換しない","交換する") == 1) {
					mes "[ゲフェンコイン交換員]";
					mes "他の品物もご覧になってください。";
					continue;
				}
				if(countitem(6671) < '@cost) {
					break;
				}
				delitem 6671,'@cost;
				getitem '@gain,1;
				mes "[ゲフェンコイン交換員]";
				mes "^006400ゲフェン魔法大会コイン^000000 " +'@cost+ "枚と";
				mes "^006400" +getitemname('@gain)+ "^000000 1個を";
				mes "交換します。";
				mes "他にもご用件はありますか？";
				continue;
			}
			if('@gain == 0) {
				continue;
			}
			break;
		case 2:
			mes "[ゲフェンコイン交換員]";
			mes "アクセサリーは2種類が";
			mes "用意されています。";
			while(1) {
				next;
				switch(select("身体強化リング <^006400コイン^000000 1800枚>","魔力増幅リング <^006400コイン^000000 1800枚>","以前のリストに戻る")) {
				case 1:
					mes "‐<ITEM>身体強化リング[1]<INFO>2963</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,2963;
					set '@cost,1800;
					break;
				case 2:
					mes "‐<ITEM>魔力増幅リング[1]<INFO>2964</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,2964;
					set '@cost,1800;
					break;
				case 3:
					set '@gain,0;
					break;
				}
				if('@gain == 0) {
					break;
				}
				next;
				mes "[ゲフェンコイン交換員]";
				mes getitemname('@gain)+ "は";
				mes "ゲフェン魔法大会コイン" +'@cost+ "枚と";
				mes "交換可能です。";
				mes "交換なさいますか？";
				next;
				if(select("交換しない","交換する") == 1) {
					mes "[ゲフェンコイン交換員]";
					mes "他の品物もご覧になってください。";
					continue;
				}
				if(countitem(6671) < '@cost) {
					break;
				}
				delitem 6671,'@cost;
				getitem '@gain,1;
				mes "[ゲフェンコイン交換員]";
				mes "^006400ゲフェン魔法大会コイン^000000 " +'@cost+ "枚と";
				mes "^006400" +getitemname('@gain)+ "^000000 1個を";
				mes "交換します。";
				mes "他にもご用件はありますか？";
				continue;
			}
			if('@gain == 0) {
				continue;
			}
			break;
		case 3:
			mes "[ゲフェンコイン交換員]";
			mes "鎧は2種類が";
			mes "用意されています。";
			while(1) {
				next;
				switch(select("アンティマジックスーツ <^006400コイン^000000 1350枚>","ゲフェンマジックローブ <^006400コイン^000000 1350枚>","以前のリストに戻る")) {
				case 1:
					mes "‐<ITEM>アンティマジックスーツ[1]<INFO>15073</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,15073;
					set '@cost,1350;
					break;
				case 2:
					mes "‐<ITEM>ゲフェンマジックローブ[1]<INFO>15074</INFO></ITEM>‐";
					mes "-上記アイテム名をクリックして";
					mes "効果をご確認ください-";
					set '@gain,15074;
					set '@cost,1350;
					break;
				case 3:
					set '@gain,0;
					break;
				}
				if('@gain == 0) {
					break;
				}
				next;
				mes "[ゲフェンコイン交換員]";
				mes getitemname('@gain)+ "は";
				mes "ゲフェン魔法大会コイン" +'@cost+ "枚と";
				mes "交換可能です。";
				mes "交換なさいますか？";
				next;
				if(select("交換しない","交換する") == 1) {
					mes "[ゲフェンコイン交換員]";
					mes "他の品物もご覧になってください。";
					continue;
				}
				if(countitem(6671) < '@cost) {
					break;
				}
				delitem 6671,'@cost;
				getitem '@gain,1;
				mes "[ゲフェンコイン交換員]";
				mes "^006400ゲフェン魔法大会コイン^000000 " +'@cost+ "枚と";
				mes "^006400" +getitemname('@gain)+ "^000000 1個を";
				mes "交換します。";
				mes "他にもご用件はありますか？";
				continue;
			}
			if('@gain == 0) {
				continue;
			}
			break;
		case 4:
			mes "[ゲフェンコイン交換員]";
			mes "消耗品は1種類が";
			mes "用意されています。";
			next;
			if(select("フェンリルの呪符 <^006400コイン^000000 20枚>","以前のリストに戻る") == 2) {
				continue;
			}
			mes "‐フェンリルの呪符‐";
			mes "‐<ITEM>フェンリルの呪符<INFO>22511</INFO></ITEM>‐";
			mes "-上記アイテム名をクリックして";
			mes "効果をご確認ください-";
			next;
			mes "[ゲフェンコイン交換員]";
			mes "フェンリルの呪符は";
			mes "ゲフェン魔法大会コイン20枚と";
			mes "交換可能です。";
			mes "一度に50個まで交換出来ます。";
			mes "いくつ交換なさいますか？";
			mes "0を入力するとキャンセル出来ます。";
			next;
			input '@num;
			if('@num == 0) {
				mes "[ゲフェンコイン交換員]";
				mes "キャンセルしました。";
				mes "またのご利用をお待ちしています。";
				close;
			}
			if('@num < 0 || '@num > 50) {
				mes "[ゲフェンコイン交換員]";
				mes "正しい数を入力してください。";
				mes "一度に交換できるのは";
				mes "50個までとなります。";
				close;
			}
			set '@cost,20 * '@num;
			mes "[ゲフェンコイン交換員]";
			mes "フェンリルの呪符";
			mes "^0000ff" +'@num+ "個^000000を";
			mes "コイン" +'@cost+ "枚と";
			mes "交換します。";
			mes "よろしいですか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[ゲフェンコイン交換員]";
				mes "キャンセルしました。";
				close;
			}
			if(countitem(6671) < '@cost) {
				break;
			}
			delitem 6671,'@value;
			getitem 22511,'@num;
			mes "[ゲフェンコイン交換員]";
			mes "はい、どうぞ。";
			mes "ありがとうございました。";
			close;
		case 5:
			mes "[ゲフェンコイン交換員]";
			mes "経験値は^FF000023時間に1回^000000";
			mes "^FF0000BaseLv90以上の方のみ";
			mes "交換することができます。";
			next;
			mes "[ゲフェンコイン交換員]";
			mes "なお、ゲフェン魔法大会コイン";
			mes "1枚につき";
			mes "BaseExp100,000、または";
			mes "JobExp　50,000、もらえます。";
			mes "交換単位は5枚、10枚、15枚です。";
			mes "どちらの経験値をご希望ですか？";
			next;
			while(1) {
				switch(select("BaseExpを貰う","JobExpを貰う","以前のリストに戻る")) {
				case 1:
					set '@exptype$,"BaseExp";
					break;
				case 2:
					set '@exptype$,"JobExp";
					break;
				case 3:
					set '@exptype$,"";
					break;
				}
				if(BaseLevel <= 89) {
					mes "[ゲフェンコイン交換員]";
					mes "おや？";
					mes "あなたは対象BaseLvの方では";
					mes "ありませんね？";
					mes "経験値につきましては";
					mes "^FF0000BaseLv90以上の方のみ";
					mes "交換することができます。";
					continue;
				}
				if('@exptype$ == "") {
					break;
				}
				mes "[ゲフェンコイン交換員]";
				mes '@exptype$+ "が欲しいのですね。";
				mes "　";
				mes "何枚利用しますか？";
				next;
				switch(select("5枚","10枚","15枚")) {
				case 1: set '@cost,5; break;
				case 2: set '@cost,10; break;
				case 3: set '@cost,15; break;
				}
				if('@exptype$ == "BaseExp") {
					set '@exp,100000 * '@cost;
				}
				else {
					set '@exp,50000 * '@cost;
				}
				mes "[ゲフェンコイン交換員]";
				mes "ゲフェン魔法大会コイン、" +'@cost+ "枚で";
				mes '@exptype$+ "を";
				mes '@exp+ "、入手できますね。";
				mes "これで良いですか？";
				next;
				if(select("はい","いいえ") == 2) {
					continue;
				}
				if(checkquest(114730)) {
					if(checkquest(114730) & 0x2 == 0) {
						mes "[ゲフェンコイン交換員]";
						mes "おや？　前回の交換から、";
						mes "23時間経過していないようですね。";
						mes "経験値は^FF000023時間に1回^000000だけ";
						mes "交換することができますので";
						mes "しばらく経ってからお越し下さい。";
						continue;
					}
				}
				if(countitem(6671) < '@cost) {
					break;
				}
				if(checkquest(114730))
					delquest 114730;
				setquest 114730;
				mes "[ゲフェンコイン交換員]";
				mes "はい、どうぞ。";
				delitem 6671,'@cost;
				for(set '@i,0; '@i<'@cost; set '@i,'@i+1) {
					if('@exptype$ == "BaseExp") {
						getexp 100000,0;
					}
					else {
						getexp 0,50000;
					}
				}
				close;
			}
			if('@exptype$ == "") {
				continue;
			}
			break;
		case 6:
			mes "[ゲフェンコイン交換員]";
			mes "またのお越しをおまちしています。";
			close;
		}
		break;
	}
	mes "[ゲフェンコイン交換員]";
	mes "^006400ゲフェン魔法大会コイン^000000 " +'@cost+ "枚を";
	mes "所持していないため";
	mes "交換できませんでした。";
	next;
	mes "[ゲフェンコイン交換員]";
	mes "^006400ゲフェン魔法大会コイン^000000は";
	mes "ゲフェン魔法大会に参加し";
	mes "良い成績を残すと獲得できます。";
	close;
OnInit:
	waitingroom "コイン交換", 0;
	end;
}

//==========================================
// 開始 ～ 受付
//------------------------------------------
function	script	#魔法大会進行度	{
	set '@target,getarg(0);
	switch('@target) {
	case 1:		// アルヒ
		set '@quest1,115550;
		set '@quest2,115551;
		set '@quest3,115552;
		break;
	case 2:		// ディオ・アネモス
		set '@quest1,115553;
		set '@quest2,115554;
		set '@quest3,115555;
		break;
	case 3:		// ビリー・コスルリース
		set '@quest1,115556;
		set '@quest2,115557;
		set '@quest3,115558;
		break;
	case 4:		// ヒピア・スニキ
		set '@quest1,115559;
		set '@quest2,115560;
		set '@quest3,115561;
		break;
	case 5:		// ブラック・カネイリー
		set '@quest1,115562;
		set '@quest2,115563;
		set '@quest3,115564;
		break;
	case 6:		// フェモン
		set '@quest1,115565;
		set '@quest2,115566;
		set '@quest3,115567;
		break;
	case 7:		// オルドル
		set '@quest1,115568;
		set '@quest2,115569;
		set '@quest3,115570;
		break;
	case 8:		// ブルート・ハゼ
		set '@quest1,115571;
		set '@quest2,115572;
		set '@quest3,115573;
		break;
	case 9:		// 黒魔
		set '@quest1,115574;
		set '@quest2,115575;
		set '@quest3,115576;
		break;
	case 10:	// イフォドス
		set '@quest1,115577;
		set '@quest2,115578;
		set '@quest3,115579;
		break;
	case 11:	// レチェニエ
		set '@quest1,115580;
		set '@quest2,115581;
		set '@quest3,115582;
		break;
	case 12:	// ユメヒメ
		set '@quest1,115583;
		set '@quest2,115584;
		set '@quest3,115585;
		break;
	case 13:	// ジュー
		set '@quest1,115586;
		set '@quest2,115587;
		set '@quest3,115588;
		break;
	case 14:	// ディワイ
		set '@quest1,115589;
		set '@quest2,115590;
		set '@quest3,115591;
		break;
	case 15:	// フェイ・カナビアン
		set '@quest1,115592;
		set '@quest2,115593;
		set '@quest3,115594;
		break;
	}

	set '@q1,checkquest('@quest1);
	set '@q2,checkquest('@quest2);
	set '@q3,checkquest('@quest3);

	if('@q1 != 0) set '@check,'@check | 0x1;
	if('@q2 != 0) set '@check,'@check | 0x2;
	if('@q3 != 0) set '@check,'@check | 0x4;

	return '@check;
}

1@gef.gat,119,199,0	script	#メモリアル開始	139,5,5,{
OnStart:
	donpcevent getmdnpcname("#イベント管理")+ "::OnStart";

	for(set '@i,1;'@i<=10;set '@i,'@i+1) {
		donpcevent getmdnpcname("#魔法大会花火_"+ '@i)+ "::OnStart";
		donpcevent getmdnpcname("#魔法大会花火_b"+ '@i)+ "::OnStart";
	}
	donpcevent getmdnpcname("男冒険者#a7")+ "::OnStart";

	donpcevent getmdnpcname("#応援NPC制御")+ "::OnStart";
	end;
OnTouch:
	hideonnpc;
	initnpctimer;
	set .Name$,strcharinfo(0);
	mapannounce getmdmapname("1@gef.gat"),"ゲフェン放送 : ついに！　待ちに待ったゲフェン魔法大会が間もなく開始されます！", 0x1, 0x00ebff, 0x190, 12, 0, 0;
	viewpoint 1, 122, 58, 1, 0x000000;
	hideonnpc getmdnpcname("#メモリアル開始");
	misceffect 1, getmdnpcname("#メモリアル開始");
	end;
OnTimer3000:
	mapannounce getmdmapname("1@gef.gat"),"ゲフェン放送 : ゲフェン市民の皆様と冒険者の皆さんの奮ってのご参加をお待ちしております！", 0x1, 0x00ebff, 0x190, 12, 0, 0;
	end;
OnTimer6000:
	mapannounce getmdmapname("1@gef.gat"),"ゲフェン放送 : ゲフェン魔法大会への参加をご希望の方はゲフェン6時方向にある噴水台にお集まりください！", 0x1, 0x00ebff, 0x190, 12, 0, 0;
	end;
OnTimer20000:
	stopnpctimer;
	mapannounce getmdmapname("1@gef.gat"),"ゲフェン放送 : ゲフェン魔法大会への参加をご希望の方はゲフェン6時方向にある噴水台にお集まりください！", 0x1, 0x00ebff, 0x190, 12, 0, 0;
	end;
}

1@gef.gat,119,199,0	script	#イベント管理	139,{
	end;
OnStart:
	hideonnpc getmdnpcname("#イベント1開始2");
	hideonnpc getmdnpcname("#イベント番外1");
	hideonnpc getmdnpcname("ケイオス#1");
	hideonnpc getmdnpcname("ゲフェン不良#1");
	hideonnpc getmdnpcname("ビリー・コスルリース#2");
	hideonnpc getmdnpcname("ゲフェン不良#3");
	hideonnpc getmdnpcname("ゲフェン不良#11");
	hideonnpc getmdnpcname("ビリー・コスルリース#22");
	hideonnpc getmdnpcname("ゲフェン不良#33");
	hideonnpc getmdnpcname("カプラの女性#1");
	hideonnpc getmdnpcname("ケイオス#2");
	hideonnpc getmdnpcname("ケイオス#3");
	hideonnpc getmdnpcname("アイリス#1");

	hideonnpc getmdnpcname("#イベント2開始2");
	hideonnpc getmdnpcname("#イベント番外2");
	hideonnpc getmdnpcname("ロキ#1");
	hideonnpc getmdnpcname("ヒピア・スニキ#1");
	hideonnpc getmdnpcname("ゲフェンごろつき#2");
	hideonnpc getmdnpcname("ゲフェンごろつき#3");
	hideonnpc getmdnpcname("ゲフェンごろつき#22");
	hideonnpc getmdnpcname("ヒピア・スニキ#11");
	hideonnpc getmdnpcname("ゲフェンごろつき#33");
	hideonnpc getmdnpcname("魔法アカデミー学生#1");
	hideonnpc getmdnpcname("魔法アカデミー学生#2");
	hideonnpc getmdnpcname("フェンリル#1");
	hideonnpc getmdnpcname("ロキ#2");
	hideonnpc getmdnpcname("ロキ#3");

	hideonnpc getmdnpcname("#イベント3開始2");
	hideonnpc getmdnpcname("ブラック・カネイリー#2");
	hideonnpc getmdnpcname("ブラック・カネイリー#1");
	hideonnpc getmdnpcname("ブラック・カネイリー#3");
	hideonnpc getmdnpcname("ブラック・カネイリー#11");
	hideonnpc getmdnpcname("ブラック・カネイリー#22");
	hideonnpc getmdnpcname("ブラック・カネイリー#33");
	hideonnpc getmdnpcname("#イベント番外3");
	hideonnpc getmdnpcname("リディア#1");
	hideonnpc getmdnpcname("ゲフェン住民#1");
	hideonnpc getmdnpcname("ゲフェン住民#2");
	hideonnpc getmdnpcname("ゲフェン住民#3");
	end;
}

1@gef.gat,121,58,0	script	#魔法大会受付1	139,15,15,{
	end;
OnTouch:
	hideonnpc;
	unittalk getcharid(3),strcharinfo(0)+" : 魔法大会受付員がいる。参加申し込みをしよう。";
	if(checkquest(9285)) {
		delquest 9285;
		setquest 9290;		// ビリー・コスルリースと対戦
	}
	if(checkquest(9287)) {
		delquest 9287;
		setquest 9291;		// ヒピア・スニキと対戦
	}
	if(checkquest(9289)) {
		delquest 9289;
		setquest 9292;		// ブラック・カネイリーと対戦
	}
	delquest 9293;
	delquest 9294;
	hideonnpc getmdnpcname("#イベント1開始1");
	hideonnpc getmdnpcname("#イベント2開始1");
	hideonnpc getmdnpcname("#イベント3開始1");
	donpcevent getmdnpcname("#イベント管理")+ "::OnStart";
	end;
}

1@gef.gat,122,58,4	script	魔法大会受付員#1	937,{
	if(checkquest(9308)) {
		mes "[魔法大会受付員]";
		mes "魔法大会で優勝するとは！";
		mes "すばらしい！";
		next;
		mes "[魔法大会受付員]";
		mes "サインの一枚でも";
		mes "貰いたいくらいです。";
		mes "優勝おめでとうございます！";
		close;
	}
	if(checkquest(9309)) {
		mes "[魔法大会受付員]";
		mes "今回の魔法大会では";
		mes "フェンリル様が優勝しました！";
		next;
		mes "[魔法大会受付員]";
		mes "魔法大会の試合を見て";
		mes "私もファンになってしまいました！";
		close;
	}
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	if(checkquest(9294)) {
		mes "[魔法大会受付員]";
		mes "魔法大会が間もなく始まります！";
		mes "6時方向の入口から";
		mes "大会に参加することができます。";
		next;
		mes "[魔法大会受付員]";
		mes "それではご武運を！";
		close;
	}
	if(checkquest(9293) & 0x4) {
		mes "[魔法大会受付員]";
		mes "試験合格、おめでとうございます。";
		next;
		mes "[魔法大会受付員]";
		mes "それでは登録手続きを進めますね。";
		mes "試験は問題なく合格……。";
		mes "職業……、装備……。";
		mes "名前を教えてください。";
		next;
		menu "名乗る",-;
		mes "[魔法大会受付員]";
		mes strcharinfo(0)+ "様、ですね。";
		mes "登録しました。";
		mes "これで登録完了です！";
		next;
		mes "[魔法大会受付員]";
		mes "魔法大会は1回勝利するごとに";
		mes "ゲフェン魔法大会コインがもらえます。";
		mes "入手出来なくなってしまわぬよう";
		mes "ゲフェン魔法大会コインの";
		mes "所持数にはご注意ください！";
		next;
		mes "[魔法大会受付員]";
		mes "魔法大会は間もなく始まります！";
		mes "6時方向の入口から";
		mes "大会に参加することができます。";
		next;
		mes "[魔法大会受付員]";
		mes "それではご武運を！";
		delquest 9293;
		setquest 9294;
		viewpoint 1, 120, 34, 2, 0x000000;
		hideoffnpc getmdnpcname("#大会入口");
		close;
	}
	if(checkquest(9293)) {
		mes "[魔法大会受付員]";
		mes "魔法大会参加試験に";
		mes "再挑戦しますか？";
		mes "60秒以内に「デザートウルフ」を";
		mes "倒せば合格となります。";
		next;
		mes "[魔法大会受付員]";
		mes "もし失敗した場合は";
		mes "試験失敗となりますが、";
		mes "いつでも再挑戦が可能です。";
		mes "それでは試験を開始しますか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[魔法大会受付員]";
			mes "魔法大会に参加することは";
			mes "大変名誉なことです。";
			mes "気が変わったら";
			mes "またいらしてください。";
			close;
		}
		mes "[魔法大会受付員]";
		mes "がんばって試験を合格し";
		mes "魔法大会に参加できると";
		mes "いいですね。";
		mes "それでは！　開始！";
		close2;
		hideoffnpc getmdnpcname("#魔法大会受付2");
		initnpctimer getmdnpcname("#魔法大会受付2");
		unittalk "魔法大会受付員 : 制限時間は60秒です！　がんばってください！";
		monster getmdmapname("1@gef.gat"),120,62,"デザートウルフ",1106,1,getmdnpcname("#魔法大会受付2")+"::OnKilled";
		hideonnpc;
		end;
	}
	mes "[魔法大会受付員]";
	mes "こんにちは！";
	mes "ゲフェン魔法大会にようこそ！";
	mes "ご用件はなんでしょうか？";
	while(1) {
		next;
		switch(select("ゲフェン魔法大会参加受付:ゲフェン魔法大会について:ゲフェン魔法大会出場報酬:会話をやめる")) {
		case 1:
			mes "[魔法大会受付員]";
			mes "魔法大会の選手登録は";
			mes "別途の参加費はありません。";
			mes "が、実力を試させてもらいます。";
			mes "そのために簡単な試験を";
			mes "受けていただきます。";
			next;
			mes "[魔法大会受付員]";
			mes "試験はいたって簡単。";
			mes "「デザートウルフ」を一匹";
			mes "召喚しますので";
			mes "60秒以内に倒せば合格です。";
			next;
			mes "[魔法大会受付員]";
			mes "もし失敗した場合は";
			mes "試験失敗となりますが、";
			mes "いつでも再挑戦が可能です。";
			mes "それでは試験を開始しますか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[魔法大会受付員]";
				mes "魔法大会に参加することは";
				mes "大変名誉なことです。";
				mes "気が変わったら";
				mes "またいらしてください。";
				break;
			}
			mes "[魔法大会受付員]";
			mes "がんばって試験を合格し";
			mes "魔法大会に参加できると";
			mes "いいですね。";
			mes "それでは！　開始！";
			close2;
			hideoffnpc getmdnpcname("#魔法大会受付2");
			initnpctimer getmdnpcname("#魔法大会受付2");
			unittalk "魔法大会受付員 : 制限時間は60秒です！　がんばってください！";
			setquest 9293;
			monster getmdmapname("1@gef.gat"),120,62,"デザートウルフ",1106,1,getmdnpcname("#魔法大会受付2")+"::OnKilled";
			hideonnpc;
			end;
		case 2:
			mes "[魔法大会受付員]";
			mes "ゲフェン魔法大会は";
			mes "3年毎に開かれる";
			mes "魔法祭の中でも";
			mes "名実共に最高峰の行事です。";
			next;
			mes "[魔法大会受付員]";
			mes "以前は魔法研究の";
			mes "成果を発表し発展方向や、";
			mes "研究方法を話し合う";
			mes "行事でしたが、時間が経つにつれて";
			mes "現在のお祭のような";
			mes "行事になりました。";
			next;
			mes "[魔法大会受付員]";
			mes "魔法祭の華である";
			mes "魔法大会ですので、";
			mes "世界中のマジシャンが集まります。";
			mes "中には相当な実力者もいるので";
			mes "非常にレベルの高い大会となります。";
			break;
		case 3:
			mes "[魔法大会受付員]";
			mes "ゲフェン魔法大会にて";
			mes "よい成績を上げると";
			mes "ゲフェン魔法大会コインを";
			mes "受け取ることができます。";
			next;
			mes "[魔法大会受付員]";
			mes "コインは魔法大会に参加した方のみに";
			mes "お配りしているもので、";
			mes "これを集めている人も沢山います。";
			break;
		case 4:
			mes "[魔法大会受付員]";
			mes "それではゲフェン魔法大会を";
			mes "心行くまで楽しんでください。";
			close;
		}
		next;
		mes "[魔法大会受付員]";
		mes "他にご用件はありますか？";
	}
	end;
}

1@gef.gat,120,46,0	script(HIDDEN)	#魔法大会受付2	139,{
	end;
OnKilled:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会受付員#1");
	hideonnpc;
	end;
OnTimer60000:
	stopnpctimer;
	killmonster getmdmapname("1@gef.gat"),getmdnpcname("魔法大会受付員#1")+"::OnKilled";
	hideoffnpc getmdnpcname("魔法大会受付員#1");
	unittalk getnpcid(0,getmdnpcname("魔法大会受付員#1")),"魔法大会受付員 : 失敗してしまいましたね。またの挑戦をお待ちしています";
	hideonnpc;
	end;
}

1@gef.gat,120,34,0	script(HIDDEN)	#大会入口	45,2,2,{
	end;
OnTouch:
	hideonnpc;
	set .Progress,0;
	warp getmdmapname("1@ge_st.gat"),104,50;
	end;
}

1@gef.gat,119,213,0	script(HIDDEN)	#大会出口	45,2,2,{
	mes "‐ここから次元の狭間へ";
	mes "　移動することができるようです。";
	mes "　魔法大会を終了して";
	mes "　次元の狭間、時の通路に";
	mes "　戻りますか？‐";
	next;
	if(select("もう少し見回ってみる","次元の狭間に戻る") == 1) {
		mes "‐あなたはその場を離れた‐";
		close;
	}
	warp "dali.gat",94,144;
	end;
}

//==========================================
// 魔法大会進行係
//------------------------------------------
// 「魔法大会進行係#1」が「アカデミーマスター#」もしくは「#試合中アナウンス_timer」を呼び出し、自身をハイドオン。
// （スキップ可）「アカデミーマスター#」が「#試合中アナウンス_timer」を呼び出す。
// 「#試合中アナウンス_timer」がmonsterを発生させる。（フェンリルのみ決勝戦アナウンス_timer）
// OnKilledイベントで「#対戦相手管理」を呼び出し
// 「#対戦相手管理」が「対戦相手のイベント」を呼び出し。
// 「対戦相手のイベント」が「魔法大会進行係#1」をハイドオフ。（フェンリルのみ魔法大会進行係#2）
//------------------------------------------
1@ge_st.gat,107,57,4	script	魔法大会進行係#1	899,{
	set '@Skip,0;
	if(.Progress == 0) {
		set '@prog,callfunc("#魔法大会進行度",1);
		if('@prog > 0) {
			mes "[魔法大会進行係]";
			mes "これより第1試合を開始致します。";
			mes "選手紹介などをせずに";
			mes "すぐに試合を開始できますが";
			mes "いかが致しますか？";
			next;
			if(select("すぐに第1試合を始める","会話を聞く") == 1) {
				set '@Skip,1;
				close2;
			}
		}
		hideoffnpc getmdnpcname("アカデミーマスター#1");
		if('@Skip == 0) {
			cutin "acamaster_a.bmp", 2;
			mes "[ゲフェンアカデミーマスター]";
			mes "レディースアンドジェントルメン！";
			mes "長い歴史と伝統が息づく";
			mes "ゲフェン魔法大会に";
			mes "ようこそいらっしゃいました！";
			next;
			mes "[ゲフェンアカデミーマスター]";
			mes "3年毎に開かれる";
			mes "最高のイベント!!";
			mes "ゲフェン魔法大会!!";
			next;
			mes "[ゲフェンアカデミーマスター]";
			mes "ゲフェン魔法大会はA組とB組に";
			mes "分かれて予選が進められ";
			mes "決勝はA組とB組の";
			mes "最終勝利者同士の対決となります！";
			next;
			mes "[ゲフェンアカデミーマスター]";
			mes "私はA組の司会を担当する";
			mes "ゲフェンアカデミーマスター!!";
			mes "アークメイジ、ザンジバル・ヘルモード";
			mes "と申します！";
			next;
			mes "[ゲフェンアカデミーマスター]";
			mes "本日はこの栄誉ある司会役を";
			mes "任されたことに感謝いたします！";
			mes "そろそろ開始の時間が迫ってきました！";
			next;
			mes "[ゲフェンアカデミーマスター]";
			mes "ゴホン……ゲホゲホ！";
			close2;
			cutin "acamaster_a.bmp", 255;
		}
		hideonnpc getmdnpcname("魔法大会進行係#1");
		set .MobName$,"アルヒ";
		set .MobNum,2549;
		delquest 9294;
		setquest 9295;
		set .Progress,1;
		if('@Skip == 0) {
			set .Sleep,0;
			donpcevent getmdnpcname("アカデミーマスター#1")+"::OnStart";
			end;
		}
		set .Sleep,5000;
		hideoffnpc getmdnpcname(.MobName$+ "#1");
		warp getmdmapname("1@ge_st.gat"),104,50;
		donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
		end;
	}
	set '@Game1,.Progress;
	set .Progress,.Progress+1;
	if(.Progress <= 10) {
		set '@Game1$,"第" +'@Game1+ "試合";
		set '@Game2$,"第" +.Progress+ "試合";
	} else if(.Progress == 11) {
		set '@Game1$,"第" +'@Game1+ "試合";
		set '@Game2$,"準々決勝";
	} else if(.Progress == 12) {
		set '@Game1$,"準々決勝";
		set '@Game2$,"準決勝";
	} else if(.Progress == 13) {
		set '@Game1$,"準決勝";
		set '@Game2$,"決勝";
	}
	mes "[魔法大会進行係]";
	mes '@Game1$+ "を勝ち残りましたね!!";
	mes "おめでとうございます！";
	next;
	if(.Progress == 3) {
    	set .flag3,3;
    	if(checkquest(9290)) set .flag3,1;
    	if(checkquest(9291)) set .flag3,2;
    }
	if(.Progress == 12) {
	    set .flag12,rand(1,2);
	}
	set '@Sel1$,"";
	switch(.Progress) {
	case 2: if(callfunc("#魔法大会進行度",2)) set '@Sel1$,"-"; break;
	case 3: if(.flag3 == 1 && callfunc("#魔法大会進行度",3)) set '@Sel1$,"-";
			if(.flag3 == 2 && callfunc("#魔法大会進行度",4)) set '@Sel1$,"-";
			if(.flag3 == 3 && callfunc("#魔法大会進行度",5)) set '@Sel1$,"-";
			break;
	case 4: if(callfunc("#魔法大会進行度",6)) set '@Sel1$,"-"; break;
	case 5: if(callfunc("#魔法大会進行度",7)) set '@Sel1$,"-"; break;
	case 6: if(callfunc("#魔法大会進行度",8)) set '@Sel1$,"-"; break;
	case 7: if(callfunc("#魔法大会進行度",9)) set '@Sel1$,"-"; break;
	case 8: if(callfunc("#魔法大会進行度",10)) set '@Sel1$,"-"; break;
	case 9: if(callfunc("#魔法大会進行度",11)) set '@Sel1$,"-"; break;
	case 10:if(callfunc("#魔法大会進行度",12)) set '@Sel1$,"-"; break;
	case 11:if(callfunc("#魔法大会進行度",13)) set '@Sel1$,"-"; break;
	case 12:if(.flag12 == 1 && callfunc("#魔法大会進行度",14)) set '@Sel1$,"-";
			if(.flag12 == 2 && callfunc("#魔法大会進行度",15)) set '@Sel1$,"-";
			break;
	case 13: if(checkquest(115595) & 0x8) set '@Sel1$,"-"; break;
	}
	if('@Sel1$ == "-")
		set '@Sel1$,"すぐに" +'@Game2$+ "を始める";
	set '@Sel2$,'@Game2$+ "を始める";
	switch(select('@Sel1$,'@Sel2$,"会話を終了する","ここで試合を棄権する")) {
	case 1:
		set '@Skip,1;
	case 2:
		if(.Progress <= 12) {
			mes "[魔法大会進行係]";
			mes "試合に勝利した選手には";
			mes "勝利手当てとして";
			mes "^006400ゲフェン魔法大会コイン^000000を";
			mes "お渡ししています。";
			next;
			if(checkitemblank() == 0) {
				mes "[魔法大会進行係]";
				mes "あら……";
				mes "荷物が多くて渡せませんね。";
				mes "種類数を減らしてきてもらえますか？";
				close;
			}
			mes "[魔法大会進行係]";
			mes "それでは次のA組" +'@Game2$+ "を";
			mes "始めたいと思います！";
		} else {
			if(checkitemblank() == 0) {
				mes "[魔法大会進行係]";
				mes "あら……";
				mes "荷物が多くて渡せませんね。";
				mes "種類数を減らしてきてもらえますか？";
				close;
			}
			mes "[魔法大会進行係]";
			mes "それでは最後の試合……";
			mes "決勝戦だけですね。";
			mes "ご武運を！";
		}
		close2;
		callsub CoinExp,'@Game1;
		hideonnpc getmdnpcname("魔法大会進行係#1");
		hideonnpc getmdnpcname("魔法大会医療班#1");
		switch(.Progress) {
		case 2:
			set .MobName$,"ディオ・アネモス";
			set .MobNum,2550;
			delquest 9295;
			setquest 9296;
			break;
		case 3:
			if(.flag3 == 1) {
				set .MobName$,"ビリー・コスルリース";
				set .MobNum,2553;
				delquest 9296;
				setquest 9297;
			}
			if(.flag3 == 2) {
				set .MobName$,"ヒピア・スニキ";
				set .MobNum,2552;
				delquest 9296;
				setquest 9297;
			}
			if(.flag3 == 3) {
				set .MobName$,"ブラック・カネイリー";
				set .MobNum,2551;
				delquest 9296;
				setquest 9297;
			}
			break;
		case 4:
			set .MobName$,"フェモン";
			set .MobNum,2554;
			delquest 9297;
			setquest 9298;
			break;
		case 5:
			set .MobName$,"オルドル";
			set .MobNum,2555;
			delquest 9298;
			setquest 9299;
			break;
		case 6:
			set .MobName$,"ブルート・ハゼ";
			set .MobNum,2556;
			delquest 9299;
			setquest 9300;
			break;
		case 7:
			set .MobName$,"黒魔";
			set .MobNum,2557;
			delquest 9300;
			setquest 9301;
			break;
		case 8:
			set .MobName$,"イフォドス";
			set .MobNum,2558;
			delquest 9301;
			setquest 9302;
			break;
		case 9:
			set .MobName$,"レチェニエ";
			set .MobNum,2559;
			delquest 9302;
			setquest 9303;
			break;
		case 10:
			set .MobName$,"ユメヒメ";
			set .MobNum,2560;
			delquest 9303;
			setquest 9304;
			break;
		case 11:
			set .MobName$,"ジュー";
			set .MobNum,2561;
			delquest 9304;
			setquest 9305;
			break;
		case 12:
			if(.flag12 == 1) {
				set .MobName$,"ディワイ";
				set .MobNum,2562;
				delquest 9305;
				setquest 9306;
			}
			if(.flag12 == 2) {
				set .MobName$,"フェイ・カナビアン";
				set .MobNum,2563;
				delquest 9305;
				setquest 9306;
			}
			break;
		case 13:
			set .MobName$,"フェンリル";
			set .MobNum,2564;
			delquest 9306;
			setquest 9307;
			break;
		}
		if('@Skip == 0 && .Progress != 13)
			set .Sleep,27000 + 5000;
		if('@Skip == 0 && .Progress == 13)
			set .Sleep,31000 + 5000;
		if('@Skip == 1)
			set .Sleep,5000;
		if(.Progress != 3 && .Progress != 13)
			hideoffnpc getmdnpcname(.MobName$+ "#1");
		if(.Progress == 3)
			hideoffnpc getmdnpcname(.MobName$+ "#n1");
		if(.Progress == 13)
			hideoffnpc getmdnpcname(.MobName$+ "#13");
		warp getmdmapname("1@ge_st.gat"),104,50;
		if('@Skip == 0) {
			if(.Progress != 3 && .Progress != 12)
				donpcevent getmdnpcname("アカデミーマスター#" +.Progress)+"::OnStart";
			if(.Progress == 3)
				donpcevent getmdnpcname("アカデミーマスター#" +.Progress+.flag3)+"::OnStart";
			if(.Progress == 12)
				donpcevent getmdnpcname("アカデミーマスター#" +.Progress+.flag12)+"::OnStart";
			end;
		}
		if(.Progress != 13)
			donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
		if(.Progress == 13)
			donpcevent getmdnpcname("#決勝戦アナウンス_timer")+"::OnStart";
		end;
	case 3:
		mes "[魔法大会進行係]";
		mes "準備が完了しましたら";
		mes "話しかけてください。";
		close;
	case 4:
		mes "[魔法大会進行係]";
		mes "えっ！";
		mes "ここで試合を棄権するのですか？";
		mes "棄権しても勝利手当ての";
		mes "^006400ゲフェン魔法大会コイン^000000は";
		mes "きちんとお渡ししますが……。";
		next;
		mes "[魔法大会進行係]";
		mes "本当に棄権しますか？";
		next;
		if(select("勝利手当てをもらって棄権する","棄権するのをやめる") == 2) {
			mes "[魔法大会進行係]";
			mes "やっぱり棄権しないのですね。";
			mes "わかりました。";
			close;
		}
		mes "[魔法大会進行係]";
		mes "わかりました。";
		mes "試合を棄権する手続きを行います。";
		mes "その前に、";
		mes "^006400ゲフェン魔法大会コイン^000000をお渡しします。";
		next;
		if(checkitemblank() == 0) {
			mes "[魔法大会進行係]";
			mes "あら……";
			mes "荷物が多くて渡せませんね。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "[魔法大会進行係]";
		mes "では、ここでは次の試合の方に";
		mes "邪魔になりますので";
		mes "出口に移動します。";
		close2;
		callsub CoinExp,'@Game1;
		hideoffnpc getmdnpcname("#魔法大会終了1");
		end;
	}
CoinExp:
	switch(getarg(0)) {
	case 1:
	case 2:
		getitem 6671, 5;
		return;
	case 3:
		getitem 6671, 5;
		set '@Exp,200000;
		set '@Job,100000;
		break;
	case 4:
	case 5:
		getitem 6671, 5;
		return;
	case 6:
		getitem 6671, 15;
		set '@Exp,400000;
		set '@Job,200000;
		break;
	case 7:
	case 8:
		getitem 6671, 5;
		return;
	case 9:
		getitem 6671, 20;
		set '@Exp,600000;
		set '@Job,300000;
		break;
	case 10:
		getitem 6671, 5;
		return;
	case 11:
		getitem 6671, 10;
		return;
	case 12:
		getitem 6671, 10;
		set '@Exp,1000000;
		set '@Job,500000;
		break;
	}
	getexp '@Exp,0,0;
	getexp '@Exp,0,0;
	getexp '@Exp,0,0;
	getexp '@Exp,0,0;
	getexp '@Exp,0,0;
	getexp 0,'@Job,0;
	getexp 0,'@Job,0;
	getexp 0,'@Job,0;
	getexp 0,'@Job,0;
	getexp 0,'@Job,0;
	return;
}

1@ge_st.gat,107,57,4	script(HIDDEN)	魔法大会進行係#2	899,{
	mes "[魔法大会進行係]";
	mes "魔法大会での優勝!!";
	mes "本当におめでとうございます！";
	next;
	if(select("勝利手当てをもらって試合会場からでる","会話を終了する") == 2) {
		mes "[魔法大会進行係]";
		mes "優勝おめでとうございます！";
		close;
	}
	mes "[魔法大会進行係]";
	mes "あ、大会で司会を務めた";
	mes "ゲフェンアカデミーマスターさんから";
	mes "お話したいことがあるそうです。";
	next;
	cutin "acamaster_a.bmp", 2;
	mes "[ゲフェンアカデミーマスター]";
	mes "おめでとうございます！";
	mes "ゲフェン最高のお祭、";
	mes "魔法大会で最高の試合を見せた";
	mes "あなたに敬意を表します。";
	next;
	mes "[ゲフェンアカデミーマスター]";
	mes "あなたの名声は";
	mes "広く世界に轟くことでしょう。";
	mes "そして多くの人々が";
	mes "今日の決勝戦について長らく";
	mes "語り継ぐことでしょう。";
	next;
	mes "[ゲフェンアカデミーマスター]";
	mes "もう一度、優勝おめでとうございます！";
	mes "ゲフェンアカデミーマスターであり";
	mes "今大会の司会として";
	mes "感謝いたします。";
	mes "残りのゲフェン祭を心行くまで";
	mes "お楽しみください!!";
	cutin "acamaster_a.bmp", 255;
	if(checkquest(9290)) delquest 9290;
	if(checkquest(9291)) delquest 9291;
	if(checkquest(9292)) delquest 9292;
	setquest 9308;
	close2;
	delquest 9307;
	getitem 6671, 15;
	getexp 2000000,0,0;
	getexp 2000000,0,0;
	getexp 2000000,0,0;
	getexp 2000000,0,0;
	getexp 2000000,0,0;
	getexp 0,1000000,0;
	getexp 0,1000000,0;
	getexp 0,1000000,0;
	getexp 0,1000000,0;
	getexp 0,1000000,0;
	donpcevent getmdnpcname("#魔法大会終了1")+"::OnStart";
	end;
}

//==========================================
// 試合中アナウンス_timer
//------------------------------------------
1@ge_st.gat,92,51,0		script	#試合中アナウンス_timer	139,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 制限時間は3分！　制限時間内に勝負がつかない場合は", 0x9, 0xffff00, 0x0190, 14, 0, 0;
	end;
OnTimer3000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 審判判定で決定されます！　それでは試合……", 0x1, 0xffff00, 0x190, 14, 0, 0;
	end;
OnTimer5000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 始め!!!!", 0x1, 0xffff00, 0x190, 18, 0, 0;
	if(.Progress != 3 && .Progress != 13)
		hideonnpc getmdnpcname(.MobName$+ "#1");
	if(.Progress == 3)
		hideonnpc getmdnpcname(.MobName$+ "#n1");
	if(.Progress == 13)
		hideonnpc getmdnpcname(.MobName$+ "#13");
	monster getmdmapname("1@ge_st.gat"),114,50,.MobName$,.MobNum,1,getmdnpcname("#対戦相手管理")+ "::OnKilled";
	if(.Progress == 12 && .flag12 == 2) {
		hideoffnpc getmdnpcname("#アルフォン召喚");
		monster getmdmapname("1@ge_st.gat"),111,49,"アルフォン",2565,1,getmdnpcname("#アルフォン召喚")+ "::OnKilled";
	}
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : さあ、試合が始まりました！　どのような結果になるのか今から見ものです！";
	end;
OnTimer65000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 残り時間2分となりました！　白熱した戦いです！", 0x9, 0xffff00;
	end;
OnTimer95000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 残り時間1分30秒！　半分を切りました！", 0x9, 0xffff00;
	end;
OnTimer125000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 残り時間あと1分になりました！", 0x9, 0xffff00;
	end;
OnTimer155000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 残り30秒!!　このまま判定まで持ち越しになるのか!!", 0x9, 0xffff00;
	end;
OnTimer165000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : あと20秒!!　緊迫してまいりました！", 0x9, 0xffff00;
	end;
OnTimer175000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 10!!", 0x9, 0xffff00;
	end;
OnTimer176000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 9!!", 0x9, 0xffff00;
	end;
OnTimer177000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 8!!", 0x9, 0xffff00;
	end;
OnTimer178000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 7!!", 0x9, 0xffff00;
	end;
OnTimer179000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 6!!", 0x9, 0xffff00;
	end;
OnTimer180000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 5!!", 0x9, 0xffff00;
	end;
OnTimer181000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 4!!", 0x9, 0xffff00;
	end;
OnTimer182000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 3!!", 0x9, 0xffff00;
	end;
OnTimer183000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 2!!!!", 0x9, 0xffff00;
	end;
OnTimer184000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 1!!!!!!", 0x9, 0xffff00;
	end;
OnTimer185000:
	killmonster getmdmapname("1@ge_st.gat"),getmdnpcname("#対戦相手管理")+ "::OnKilled";
	if(.Progress == 12 && .flag12 == 2)
		killmonster getmdmapname("1@ge_st.gat"),getmdnpcname("#アルフォン召喚")+ "::OnKilled";
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : しゅ～りょ～!!　時間切れのため、審判判定に持ち越されます！", 0x9, 0xffff00, 0x0190, 18, 0, 0;
	end;
OnTimer190000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : 現在審判判定中ですのでしばらくお待ちください!!", 0x9, 0xffff00;
	end;
OnTimer195000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター  : おーっと！　どうやら審判判定が出たようです!!　結果はいかに!!", 0x9, 0xffff00;
	end;
OnTimer198000:
	set '@Lose,rand(75,89);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 最初の審判の判定は……" +'@Lose+ " : " +'@Win+ "!!";
	end;
OnTimer200000:
	set '@Lose,rand(74,88);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 続いての審判の判定は……" +'@Win+ " : " +'@Lose+ "!!";
	end;
OnTimer202000:
	set '@Lose,rand(70,84);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 最後の審判判定は……" +'@Win+ " : " +'@Lose+ "!!";
	end;
OnTimer204000:
	if(.Progress == 1)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1で勝利者は仮面のノービス！　アルヒ!!";
	if(.Progress == 2)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　A組第2試合の勝利者は！　心だけは大魔法使い！　ディオ・アネモス。";
	if(.Progress == 3 && .flag3 == 1)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果!!　2対1でA組第3試合の勝利者は！　脚線美命同好会会長！　ビリー・コスルリース!!";
	if(.Progress == 3 && .flag3 == 2)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果!!　2対1でA組第3試合の勝利者は！　兄貴組切り込み隊長！　ヒピア・スニキ!!!";
	if(.Progress == 3 && .flag3 == 3)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判の判定結果、2対1でA組第3試合の勝利者は!!　「お前のZenyも俺のZeny、俺のZenyは俺のZeny」ギルドのマスター!!　ブラック・カネイリー!!!";
	if(.Progress == 4)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第4試合の勝利者は！　麗しのプロンテラ!!　フェモン!!";
	if(.Progress == 5)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第5試合の勝利者は!!　努力派戦闘マスター!!　オルドル!!!";
	if(.Progress == 6)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第6試合の勝利者は！　血塗られたうさ耳!!　ブルート・ハゼ!!!";
	if(.Progress == 7)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第7試合の勝利者は！　漆黒の牙！　黒魔!!";
	if(.Progress == 8)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第8試合の勝利者は!!　鉄壁の防御！　イフォドス!!";
	if(.Progress == 9)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第9試合の勝利者は!!　死のレディー!!　レチェニエ!!";
	if(.Progress == 10)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組第10試合の勝利者は!!　死を導く踊り手！　ユメヒメ!!";
	if(.Progress == 11)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組準々決勝の勝利者は!!　実戦戦闘の達人!!　ジュー!!!";
	if(.Progress == 12 && .flag12 == 1)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組最後の試合、準決勝の勝利者は!!　戦場のマエストロ!!　ディワイ!!!";
	if(.Progress == 12 && .flag12 == 2)
		unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でA組最後の試合、準決勝の勝利者は!!　アルデバランの錬金術師！　フェイ・カナビアン!!!";
	end;
OnTimer206000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 敗北してしまった選手には励ましの拍手をお願い致します！";
	if(.Progress != 3) set '@str$,"#1";
	if(.Progress == 3) set '@str$,"#n1";
	set .Sleep,0;
	hideoffnpc getmdnpcname(.MobName$+'@str$);
	setnpctimer 100000,getmdnpcname(.MobName$+'@str$);
	startnpctimer getmdnpcname(.MobName$+'@str$);
	end;
OnTimer208000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : また、敗北した選手は試合進行のため、強制的に試合会場から移動していただきますのでご了承ください！";
	end;
}

1@ge_st.gat,92,51,0		script	#決勝戦アナウンス_timer	139,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 決勝戦は制限時間5分となっております！　制限時間内に勝負がつかない場合は！", 0x9, 0xffff00, 0x0190, 14, 0, 0;
	end;
OnTimer3000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 審判判定で決定されます！　それでは試合……", 0x1, 0xffff00, 0x190, 14, 0, 0;
	end;
OnTimer5000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 始め!!!!", 0x1, 0xffff00, 0x190, 18, 0, 0;
	hideonnpc getmdnpcname(.MobName$+ "#13");
	monster getmdmapname("1@ge_st.gat"),114,50,.MobName$,.MobNum,1,getmdnpcname("#対戦相手管理")+ "::OnKilled";
	end;
OnTimer6000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : ついに決勝戦が始まりました!!　手に汗を握る試合です！", 0x9, 0xffff00;
	end;
OnTimer65000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間4分！　まだまだ結果はわかりません!!", 0x9, 0xffff00;
	end;
OnTimer125000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り3分を切りました！　勝者はどちらになるのか!!", 0x9, 0xffff00;
	end;
OnTimer185000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間2分！　さあ、どうなる！", 0x9, 0xffff00;
	end;
OnTimer215000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 1分30秒です！　残り時間わずかになって来ました！", 0x9, 0xffff00;
	end;
OnTimer245000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間1分！　決着がつきません！", 0x9, 0xffff00;
	end;
OnTimer275000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間30秒!!　決勝にふさわしい戦いです！", 0x9, 0xffff00;
	end;
OnTimer285000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間20秒！　緊迫してまいりました！", 0x9, 0xffff00;
	end;
OnTimer295000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 残り時間10秒！　さあ、どちらが勝利を手にするのか！", 0x9, 0xffff00;
	end;
OnTimer296000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 9秒！", 0x9, 0xffff00;
	end;
OnTimer297000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 8秒！", 0x9, 0xffff00;
	end;
OnTimer298000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 7秒！", 0x9, 0xffff00;
	end;
OnTimer299000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 6秒！", 0x9, 0xffff00;
	end;
OnTimer300000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 5秒！", 0x9, 0xffff00;
	end;
OnTimer301000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 4秒！", 0x9, 0xffff00;
	end;
OnTimer302000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 3秒！", 0x9, 0xffff00;
	end;
OnTimer303000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 2秒！", 0x9, 0xffff00;
	end;
OnTimer304000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 1秒！", 0x9, 0xffff00;
	end;
OnTimer305000:
	killmonster getmdmapname("1@ge_st.gat"),getmdnpcname("#対戦相手管理")+ "::OnKilled";
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 試合終了!!　ついに時間内には決着がつきませんでした！", 0x9, 0xffff00, 0x0190, 18, 0, 0;
	end;
OnTimer307000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : それでは審判の方々に判定をお願いしましょう！", 0x9, 0xffff00;
	end;
OnTimer309000:
	mapannounce getmdmapname("1@ge_st.gat"),"ゲフェンアカデミーマスター : 判定結果が出ました！　今ゲフェン魔法大会の優勝者は!!", 0x9, 0xffff00;
	end;
OnTimer311000:
	set '@Lose,rand(75,89);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 最初の審判の判定は……" +'@Lose+ " : " +'@Win+ "!!";
	end;
OnTimer313000:
	set '@Lose,rand(74,88);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 続いての審判の判定は……" +'@Win+ " : " +'@Lose+ "!!";
	end;
OnTimer315000:
	set '@Lose,rand(70,84);
	set '@Win,'@Lose + rand(1,5);
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 最後の審判判定は……" +'@Win+ " : " +'@Lose+ "!!";
	end;
OnTimer317000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 審判判定結果！　2対1でゲフェン魔法大会決勝戦の優勝者は!!　蒼い服の魔導士!!　フェンリス・フェンリル!!!!";
	end;
OnTimer319000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 敗北してしまった選手には励ましの拍手をお願い致します！";
	end;
OnTimer321000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : また、敗北した選手は試合進行のため、強制的に試合会場から移動していただきますのでご了承ください！";
	set .Sleep,0;
	hideoffnpc getmdnpcname(.MobName$+"#13");
	setnpctimer 100000,getmdnpcname(.MobName$+"#13");
	startnpctimer getmdnpcname(.MobName$+"#13");
	end;
}

//==========================================
// 大会運営その他
//------------------------------------------
1@ge_st.gat,109,49,0	script	#対戦相手管理	139,{
	end;
OnKilled:
	if(.Progress != 13)
		stopnpctimer getmdnpcname("#試合中アナウンス_timer");
	if(.Progress == 13)
		stopnpctimer getmdnpcname("#決勝戦アナウンス_timer");
	switch(.Progress) {
	case 1:
		set '@value,1;
		set '@quest1,115550;
		set '@quest2,115551;
		set '@quest3,115552;
		break;
	case 2:
		set '@value,2;
		set '@quest1,115553;
		set '@quest2,115554;
		set '@quest3,115555;
		break;
	case 3:
    	if(.flag3 == 1) {
			set '@value,3;
			set '@quest1,115556;
			set '@quest2,115557;
			set '@quest3,115558;
		}
    	if(.flag3 == 2) {
			set '@value,4;
			set '@quest1,115559;
			set '@quest2,115560;
			set '@quest3,115561;
		}
    	if(.flag3 == 3) {
			set '@value,5;
			set '@quest1,115562;
			set '@quest2,115563;
			set '@quest3,115564;
		}
		break;
	case 4:
		set '@value,6;
		set '@quest1,115565;
		set '@quest2,115566;
		set '@quest3,115567;
		break;
	case 5:
		set '@value,7;
		set '@quest1,115568;
		set '@quest2,115569;
		set '@quest3,115570;
		break;
	case 6:
		set '@value,8;
		set '@quest1,115571;
		set '@quest2,115572;
		set '@quest3,115573;
		break;
	case 7:
		set '@value,9;
		set '@quest1,115574;
		set '@quest2,115575;
		set '@quest3,115576;
		break;
	case 8:
		set '@value,10;
		set '@quest1,115577;
		set '@quest2,115578;
		set '@quest3,115579;
		break;
	case 9:
		set '@value,11;
		set '@quest1,115580;
		set '@quest2,115581;
		set '@quest3,115582;
		break;
	case 10:
		set '@value,12;
		set '@quest1,115583;
		set '@quest2,115584;
		set '@quest3,115585;
		break;
	case 11:
		set '@value,13;
		set '@quest1,115586;
		set '@quest2,115587;
		set '@quest3,115588;
		break;
	case 12:
		if(.flag12 == 1) {
			set '@value,14;
			set '@quest1,115587;
			set '@quest2,115588;
			set '@quest3,115589;
		}
		if(.flag12 == 2) {
			set '@value,15;
			set '@quest1,115590;
			set '@quest2,115591;
			set '@quest3,115592;
		}
		break;
	case 13:
		if(!checkquest(115595)) {
			setquest 115595;
			compquest 115595;
		}
		break;
	}
	set '@prog,callfunc("#魔法大会進行度",'@value);
	if('@prog >= 7)
		set '@quest,0;
	else
		set '@quest,'@prog+1;
	if('@quest | 0x1) {
		setquest '@quest1;
		compquest '@quest1;
	} else if(checkquest('@quest1)) {
		setquest '@quest1;
		delquest '@quest1;
	}
	if('@quest | 0x2) {
		setquest '@quest2;
		compquest '@quest2;
	} else if(checkquest('@quest2)) {
		setquest '@quest2;
		delquest '@quest2;
	}
	if('@quest | 0x4) {
		setquest '@quest3;
		compquest '@quest3;
	} else if(checkquest('@quest3)) {
		setquest '@quest3;
		delquest '@quest3;
	}
	set .Sleep,0;
	if(.Progress != 3 && .Progress != 13)
		donpcevent getmdnpcname(.MobName$+ "#1")+"::OnStart";
	if(.Progress == 3)
		donpcevent getmdnpcname(.MobName$+ "#n1")+"::OnStart";
	if(.Progress == 13) {
		donpcevent getmdnpcname(.MobName$+ "#13")+"::OnStart";
	}
	end;
}

1@ge_st.gat,109,49,0	script(HIDDEN)	#魔法大会終了1	139,21,12,{
	end;
OnTouch:
	switch(.Progress) {
	case 1:		// アルヒ
		delquest 9295;
		setquest 9309;
		break;
	case 2:		// ディオ・アネモス
		delquest 9296;
		setquest 9309;
		break;
	case 3:
		if(.flag3 == 1) {		// ビリー・コスルリース
			delquest 9290;
			delquest 9297;
			setquest 9309;
		}
		if(.flag3 == 2) {		// ヒピア・スニキ
			delquest 9291;
			delquest 9297;
			setquest 9309;
		}
		if(.flag3 == 3) {		// ブラック・カネイリー
			delquest 9292;
			delquest 9297;
			setquest 9309;
		}
		break;
	case 4:		// フェモン
		delquest 9298;
		setquest 9309;
		break;
	case 5:		// オルドル
		delquest 9299;
		setquest 9309;
		break;
	case 6:		// ブルート・ハゼ
		delquest 9300;
		setquest 9309;
		break;
	case 7:		// 黒魔
		delquest 9301;
		setquest 9309;
		break;
	case 8:		// イフォドス
		delquest 9302;
		setquest 9309;
		break;
	case 9:		// レチェニエ
		delquest 9303;
		setquest 9309;
		break;
	case 10:		// ユメヒメ
		delquest 9304;
		setquest 9309;
		break;
	case 11:		// ジュー
		delquest 9305;
		setquest 9309;
		break;
	case 12:
		if(.flag12 == 1) {		// ディワイ
			delquest 9306;
			setquest 9309;
		}
		if(.flag12 == 2) {		// フェイ・カナビアン
			delquest 9306;
			setquest 9309;
		}
		break;
	case 13:		// フェンリル
		delquest 9307;
		setquest 9309;
		break;
	}
	goto OnStart;
	end;
OnStart:
	hideoffnpc getmdnpcname("アイリス#a1");
	hideoffnpc getmdnpcname("ケイオス#a1");
	hideoffnpc getmdnpcname("リディア#a1");
	hideoffnpc getmdnpcname("フェンリル#a1");
	hideoffnpc getmdnpcname("ロキ#a1");
	hideoffnpc getmdnpcname("#大会出口");
	hideonnpc getmdnpcname("案内要員#5");
	hideoffnpc getmdnpcname("案内要員#6");
	mapwarp getmdmapname("1@ge_st.gat"), getmdmapname("1@gef.gat"), 120, 104;
	end;
}

1@ge_st.gat,109,49,0	script(HIDDEN)	#魔法大会優勝1	139,{
	end;
OnStart:
	hideonnpc getmdnpcname("フェンリル#13");
	hideoffnpc getmdnpcname("魔法大会進行係#2");
	hideoffnpc getmdnpcname("アルヒ#q1");
	hideoffnpc getmdnpcname("ディオ・アネモス#q1");
	hideoffnpc getmdnpcname("フェモン#q1");
	hideoffnpc getmdnpcname("オルドル#q1");
	hideoffnpc getmdnpcname("ブルート・ハゼ#q1");
	hideoffnpc getmdnpcname("黒魔#q1");
	hideoffnpc getmdnpcname("イフォドス#q1");
	hideoffnpc getmdnpcname("レチェニエ#q1");
	hideoffnpc getmdnpcname("ユメヒメ#q1");
	hideoffnpc getmdnpcname("ジュー#q1");
	hideoffnpc getmdnpcname("ディワイ#q1");
	hideoffnpc getmdnpcname("フェイ・カナビアン#q1");
	hideoffnpc getmdnpcname("フェンリル#q1");
	mapwarp getmdmapname("1@ge_st.gat"), getmdmapname("1@ge_st.gat"), 109, 50;
	end;
}

1@ge_st.gat,109,51,4	script(HIDDEN)	魔法大会医療班#1	475,{
	mes "[魔法大会医療班]";
	mes "ここまで勝ち残った選手は";
	mes "一旦治療を受けることができます。";
	mes "治療を受けますか？";
	next;
	if(select("治療を受ける","会話を終了する") == 2) {
		mes "[魔法大会医療班]";
		mes "優勝できるといいですね。";
		close;
	}
	mes "[魔法大会医療班]";
	mes "治療が完了しました。";
	mes "次の試合も頑張ってください！";
	percentheal 100,100;
	close2;
	hideonnpc;
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆アルヒ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#1	10006,{
	end;
OnStart:
	unittalk "ゲフェンアカデミーマスター : それでは!!　ゲフェン!!　魔法!!　大会を!!　かいすぃ!!";
	initnpctimer;
	end;
OnTimer1500:
	unittalk "ゲフェンアカデミーマスター : いったしぃ!!　ま!!";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : すうううううう!!　ヒアウィゴー!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : おおお！　始まる始まる！";
	misceffect 89, getmdnpcname("#魔法大会花火_11");
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : どれどれ！　誰が勝つかな？";
	misceffect 89, getmdnpcname("#魔法大会花火_13");
	end;
OnTimer4000:
	hideoffnpc getmdnpcname("アルヒ#1");
	end;
OnTimer6000:
	unittalk "ゲフェンアカデミーマスター : それではA組第1試合を開始いたします！";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a2")),"魔法アカデミー学生 : イヤッホー!!";
	misceffect 30, getmdnpcname("#魔法大会花火_11");
	misceffect 89, getmdnpcname("#魔法大会花火_12");
	misceffect 30, getmdnpcname("#魔法大会花火_13");
	misceffect 89, getmdnpcname("#魔法大会花火_14");
	end;
OnTimer8000:
	unittalk "ゲフェンアカデミーマスター : 今回が魔法大会初参加の謎の選手！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 早く！　試合！　早く！";
	end;
OnTimer9000:
	misceffect 92, getmdnpcname("#魔法大会花火_11");
	misceffect 30, getmdnpcname("#魔法大会花火_12");
	misceffect 92, getmdnpcname("#魔法大会花火_13");
	misceffect 30, getmdnpcname("#魔法大会花火_14");
	end;
OnTimer10000:
	unittalk "ゲフェンアカデミーマスター : 名前さえ知られていない無名の流れ者！　" +.Name$+ "!!";
	end;
OnTimer12000:
	misceffect 89, getmdnpcname("#魔法大会花火_17");
	misceffect 92, getmdnpcname("#魔法大会花火_12");
	misceffect 89, getmdnpcname("#魔法大会花火_19");
	misceffect 92, getmdnpcname("#魔法大会花火_14");
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : あいつ初参加か？　気合入れろよ！";
	end;
OnTimer15000:
	unittalk "ゲフェンアカデミーマスター : そして相手は!!";
	misceffect 30, getmdnpcname("#魔法大会花火_17");
	misceffect 89, getmdnpcname("#魔法大会花火_18");
	misceffect 30, getmdnpcname("#魔法大会花火_19");
	misceffect 89, getmdnpcname("#魔法大会花火_20");
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : いけいけ～!!";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a1")),"アルベルタ観覧客 : 期待してるぞ!!";
	end;
OnTimer17000:
	unittalk "ゲフェンアカデミーマスター : 名家の御曹司がゲフェン魔法大会に挑戦！　気は弱いがやる気は十分！";
	end;
OnTimer18000:
	misceffect 92, getmdnpcname("#魔法大会花火_17");
	misceffect 30, getmdnpcname("#魔法大会花火_18");
	misceffect 92, getmdnpcname("#魔法大会花火_19");
	misceffect 30, getmdnpcname("#魔法大会花火_20");
	end;
OnTimer19000:
	unittalk "ゲフェンアカデミーマスター : 幼い挑戦者、仮面のノービス！　アルヒ！";
	end;
OnTimer21000:
	misceffect 92, getmdnpcname("#魔法大会花火_18");
	end;
OnTimer21500:
	misceffect 92, getmdnpcname("#魔法大会花火_20");
	end;
OnTimer22000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : 大丈夫……。";
	end;
OnTimer24000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : 僕には父様と母様にもらったこれがある。";
	end;
OnTimer26000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : ヴィゾフニルの羽飾りと女神の仮面。";
	end;
OnTimer28000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : せせせせ、精一杯がんばります。";
	end;
OnTimer30000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : よ、よろしくおねがいひまひゅ……！";
	end;
OnTimer32000:
	unittalk getnpcid(0,getmdnpcname("アルヒ#1")),"アルヒ : あ、噛んじゃった……。";
	end;
OnTimer34000:
	misceffect 89, getmdnpcname("#魔法大会花火_11");
	misceffect 89, getmdnpcname("#魔法大会花火_13");
	end;
OnTimer35000:
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a5")),"魔法アカデミー学生 : どっちもがんばれー!!";
	end;
OnTimer37000:
	misceffect 30, getmdnpcname("#魔法大会花火_11");
	misceffect 89, getmdnpcname("#魔法大会花火_12");
	misceffect 30, getmdnpcname("#魔法大会花火_13");
	misceffect 89, getmdnpcname("#魔法大会花火_14");
	end;
OnTimer38000:
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a2")),"魔法アカデミー学生 : ドキドキする！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : いい試合をみせてね！";
	end;
OnTimer39000:
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
OnTimer40000:
	misceffect 92, getmdnpcname("#魔法大会花火_11");
	misceffect 30, getmdnpcname("#魔法大会花火_12");
	misceffect 92, getmdnpcname("#魔法大会花火_13");
	misceffect 30, getmdnpcname("#魔法大会花火_14");
	end;
OnTimer43000:
	stopnpctimer;
	misceffect 92, getmdnpcname("#魔法大会花火_12");
	misceffect 92, getmdnpcname("#魔法大会花火_14");
	end;
OnWin1:
	if(.Progress <= 10) {
		set '@Game$,"第" +.Progress+ "試合";
	} else if(.Progress == 11) {
		set '@Game$,"準々決勝";
	} else if(.Progress == 12) {
		set '@Game$,"準決勝";
	} else if(.Progress == 13) {
		set '@Game$,"決勝";
	}
	if(.Progress <= 11)
		unittalk "ゲフェンアカデミーマスター : A組の" +'@Game$+ "が終了しました！　勝利した選手は勝利手当てを毎試合ごとに受け取ることが出来ます。";
	if(.Progress == 12)
		unittalk "ゲフェンアカデミーマスター : A組最後の試合！　準決勝が終了しました！　勝利した選手は勝利手当てを毎試合ごとに受け取ることが出来ます。";
	end;
OnWin2:
	unittalk "ゲフェンアカデミーマスター : また、次の試合の準備をする時間が与えられます！";
	end;
OnWin3:
	unittalk "ゲフェンアカデミーマスター : 魔法大会進行係に準備完了を知らせていただければ次の試合を開始いたします。";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	アルヒ#1	670,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "アルヒ : うぅ……完敗です……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "アルヒ : 僕とは次元が違うことを痛感しました……。";
	end;
OnTimer5000:
	unittalk "アルヒ : 僕の試合はここで終わりですが……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "アルヒ : 次の試合もがんばってください！";
	end;
OnTimer9000:
	unittalk "アルヒ : お、応援しています！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	hideonnpc;
	end;
OnTimer12000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "アルヒ : さすがに、僕の腕じゃこれが限界か……。";
	end;
OnTimer104000:
	unittalk "アルヒ : まだまだ経験不足を痛感する試合でした。";
	end;
OnTimer106000:
	unittalk "アルヒ : でも、お陰で少し自信がついた気がします！";
	end;
OnTimer108000:
	unittalk "アルヒ : 次の試合も、精一杯がんばります！";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ディオ・アネモス（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#2	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは!!　A組第2試合、開始と参ります！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 初参加にして、第1試合を勝ち残った謎の挑戦者！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : どこまで勝ち進めるのか!!　" +.Name$;
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 盛り上がってるな～！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうは！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : どっちを応援しようかな！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : アカデミーでも注目される期待の成長株！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : ところでフェイヨンからは誰も出ないのか？";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 心だけは大魔法使い！　ディオ・アネモス！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : 僕はねぇ……";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : 無駄なことってあんまり好きじゃないんだ。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : とっとと、始めようじゃないか。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : まあ、結果はもうすでに決まってるんだけどね。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : 早く終わらせてマイハニーに思いを告げるのさぁ。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ディオ・アネモス#1")),"ディオ・アネモス : まあ、告白の結果も、もうすでに決まってるんだけどねぇ！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a1")),"魔法アカデミー学生 : どっちも頑張って！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : 始まる!!";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ディオ・アネモス#1	669,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ディオ・アネモス : ……さ、最近買い換えたこの武器が";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ディオ・アネモス : 僕の手に馴染んでなかったからだ！";
	end;
OnTimer5000:
	unittalk "ディオ・アネモス : うん、負けたのは僕の実力じゃない！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ディオ・アネモス : この武器が悪いんだ！";
	end;
OnTimer9000:
	unittalk "ディオ・アネモス : ってことで、君は運が良かったようだねぇ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ディオ・アネモス : まったく……さすがの僕も君の悪運には勝てなかったようだよ。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ディオ・アネモス : おかしいなー？";
	end;
OnTimer104000:
	unittalk "ディオ・アネモス : 君に華麗に勝って次の試合に行くはずだったのに。";
	end;
OnTimer106000:
	unittalk "ディオ・アネモス : まあ、たまにこういうこともないとねぇ。";
	end;
OnTimer108000:
	unittalk "ディオ・アネモス : それじゃ、お疲れさま！";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ビリー・コスルリース（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#31	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　第3試合を！　始めさせていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : なぜか事件に巻き込まれる！　そんな体質を背負った不幸な選手！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 苦労だけはすでに優勝者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 初参加クン頑張るねぇ！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : へえ、なかなかやるじゃない。";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そして相手は！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 期待の新人さん登場ね！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どのくらいの強さかな？";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 女性の美しい脚をこよなく愛する！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 脚線美命同好会会長！　ビリー・コスルリース！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : あのカプラの脚線美……。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : おれの中でもかなり高評価だったんだ！";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : なぜお前にはあの良さがわからないんだ！";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : この試合で、お前に脚線美の良さを思い知らせてやるぜ！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : そしてお前も今日から、同好会の仲間にしてやる！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#n1")),"ビリー・コスルリース : そんじゃ行くぜ!!";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 新参者か！応援しようかな！";
	unittalk getnpcid(0,getmdnpcname("コモド観覧客#a1")),"コモド観覧客 : すぐに負けるんじゃないよ！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : おお！　俺はあいつを応援するぞ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どうかな？どっちが勝つかな～。";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ビリー・コスルリース#n1	682,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ビリー・コスルリース : クククク……バカめ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ビリー・コスルリース : このおれは脚線美命同好会でも最弱。";
	end;
OnTimer5000:
	unittalk "ビリー・コスルリース : 第二、第三の同好会メンバーがお前を……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ビリー・コスルリース : え？　負けたらおしまい？";
	end;
OnTimer9000:
	unittalk "ビリー・コスルリース : チキショーッ!!";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ビリー・コスルリース : ガクッ……。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : あーっと！　B組の試合情報が入ってきました！";
	end;
OnTimer16000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : フェンリルという選手が破竹の勢いで連勝しているそうです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ビリー・コスルリース : やれやれ。";
	end;
OnTimer104000:
	unittalk "ビリー・コスルリース : 応援する観客の脚線美がなかったら負けてたぜ……。";
	end;
OnTimer106000:
	unittalk "ビリー・コスルリース : まったく、脚線美ってやつは罪だよな。";
	end;
OnTimer108000:
	unittalk "ビリー・コスルリース : おれをここまで本気にさせちまうんだからよ。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ヒピア・スニキ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#32	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　第3試合を！　始めさせていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : なぜか事件に巻き込まれる！　そんな体質を背負った不幸な選手！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 苦労だけはすでに優勝者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 初参加クン頑張るねぇ！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : へえ、なかなかやるじゃない。";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 期待の新人さん登場ね！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どのくらいの強さかな？";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 愛用の斧、ハンドちゃんで猛威をふるう！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 兄貴組切り込み隊長!!　ヒピア・スニキ！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : 待ってたぜェ。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : この瞬間をな！";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : 決着つけよーじゃねーか！";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : 泣いて家に帰る準備するんだな！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : 俺と、俺のお手製手斧「ハンドちゃん」で";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#n1")),"ヒピア・スニキ : ボコボコにしてやる!!";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 新参者か！応援しようかな！";
	unittalk getnpcid(0,getmdnpcname("コモド観覧客#a1")),"コモド観覧客 : すぐに負けるんじゃないよ！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : おお！　俺はあいつを応援するぞ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どうかな？どっちが勝つかな～。";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ヒピア・スニキ#n1	681,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ヒピア・スニキ : !?";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ヒピア・スニキ : この俺が負けただと……。";
	end;
OnTimer5000:
	unittalk "ヒピア・スニキ : ハンドちゃん……すまねェ……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ヒピア・スニキ : 精錬値が足りなかったようだ……。";
	end;
OnTimer9000:
	unittalk "ヒピア・スニキ : クソッ……オリデオコンをケチるんじゃ……なかった……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ヒピア・スニキ : ガクッ……。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : あーっと！　B組の試合情報が入ってきました！";
	end;
OnTimer16000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : フェンリルという選手が破竹の勢いで連勝しているそうです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ヒピア・スニキ : 俺に負けるのはある意味仕方ねェ。";
	end;
OnTimer104000:
	unittalk "ヒピア・スニキ : 俺のお手製の手斧「ハンドちゃん」。";
	end;
OnTimer106000:
	unittalk "ヒピア・スニキ : その必殺技であるマキシマイズパワー。";
	end;
OnTimer108000:
	unittalk "ヒピア・スニキ : これが炸裂しちまったんだからよ。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ブラック・カネイリー（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#33	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　第3試合を！　始めさせていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : なぜか事件に巻き込まれる！　そんな体質を背負った不幸な選手！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 苦労だけはすでに優勝者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 初参加クン頑張るねぇ！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : へえ、なかなかやるじゃない。";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてそれに立ち向かうは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 期待の新人さん登場ね！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どのくらいの強さかな？";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 前から見ても泥棒、横からみてもドロボウ！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 「お前のZenyも俺のZeny、俺のZenyは俺のZeny」ギルドのマスター!!　ブラック・カネイリー！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : ここで会ったが100万Zenyね！";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : 最初にいっておくけど、あたし別にあんたと戦いたいわけじゃないから。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : ちょっと金目のモノもらえたら満足だし。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : ってことで、金目のモノを差し出しなさい！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : それで話が済むんだから簡単でしょ!?";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#n1")),"ブラック・カネイリー : Zenyがあれば戦わないですむんだから、やっぱりZenyが最高よね！";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 新参者か！応援しようかな！";
	unittalk getnpcid(0,getmdnpcname("コモド観覧客#a1")),"コモド観覧客 : すぐに負けるんじゃないよ！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : おお！　俺はあいつを応援するぞ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どうかな？どっちが勝つかな～。";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ブラック・カネイリー#n1	671,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ブラック・カネイリー : あんた、少しは手加減っていうものをしらないの!?";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ブラック・カネイリー : この感じならどうせ、Zenyの扱いもどんぶり勘定なんでしょ!?";
	end;
OnTimer5000:
	unittalk "ブラック・カネイリー : もう少し、Zenyと人の扱いについて勉強しなさいよね!?";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ブラック・カネイリー : そんなんじゃ、Zenyがいつまでたっても貯まらないわよ。";
	end;
OnTimer9000:
	unittalk "ブラック・カネイリー : おかげでこっちの売り上げにも響くのよ！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ブラック・カネイリー : ちょっとは考えてよね。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : あーっと！　B組の試合情報が入ってきました！";
	end;
OnTimer16000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : フェンリルという選手が破竹の勢いで連勝しているそうです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ブラック・カネイリー : あんたに教えてあげる。";
	end;
OnTimer104000:
	unittalk "ブラック・カネイリー : Zenyは裏切らない。あんたもZenyを貯めて、強くなりなさい。";
	end;
OnTimer106000:
	unittalk "ブラック・カネイリー : 孤児院を建てるのがあたしの目標で、本当はzeny稼ぎに忙しいんだけど、なんだったらあたしが雇ってあげるわよ。";
	end;
OnTimer108000:
	unittalk "ブラック・カネイリー : そのかわりあんたは孤児院が建つまではタダ働きだけどね♪";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆フェモン（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#4	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　第4試合を！　始めさせていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 初参加で連勝!!　人気が出てきたか?!";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 無冠の勇者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : がんばれ～！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : あいつなかなかやるな！　気に入ったぞ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : これまた連勝で勝ちあがって来た相手は！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 面白い戦いになりそうね！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 女性観客からの人気上昇中！　美しく雄々しい挑戦者！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 麗しのプロンテラ!!　フェモン！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : 面倒だけど、ほしいものを買うのに魔法大会コインを売った金が必要でね。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : そんなわけだから、さっさと終わらせようぜ。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : ああ、すまない。オレとしたことが……。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : あまりに早く終わらせるとオレのファンが悲しむ。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : ほどほどに時間をかけてやるか。";
	end;
	unittalk getnpcid(0,getmdnpcname("フェモン#1")),"フェモン : その方がお互い、幸せだろ？";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : おお！　プロンテラ出身の選手か！";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a2")),"プロンテラ観覧客 : 同郷を応援するぞぉ！";
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a4")),"魔法アカデミー学生 : 新参選手も負けるなよ～！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : 頑張れ～！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 期待半分、心配半分ってとこだな。";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	フェモン#1	672,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "フェモン : こんなところで負けるとはな……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "フェモン : でもオレは、無粋な男どものように悔しがったりしない。";
	end;
OnTimer5000:
	unittalk "フェモン : 悔しがる姿は、美しくないからな。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "フェモン : 悔しさに身悶えするオレが好きなファンもいるだろうが……。";
	end;
OnTimer9000:
	unittalk "フェモン : ここで見せるべきじゃないしな。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "フェモン : それじゃ、お疲れ。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "フェモン : フフ……。";
	end;
OnTimer104000:
	unittalk "フェモン : 今だけは、オレのファン以外にもオレの美しさを堪能する時間をくれてやる。";
	end;
OnTimer106000:
	unittalk "フェモン : さーて、次の試合に備えて身だしなみを整えないとな。";
	end;
OnTimer108000:
	unittalk "フェモン : このオレの美しさが劣化したら、ファンが可哀想だしな。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆オルドル（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#5	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　第5試合を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : もう無名とは呼ばせない！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 注目のルーキー！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : かっくい～！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : そういえば今回の大会レベル高いね！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a1")),"アルベルタ観覧客 : なかなか面白い！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 礼儀正しく優しい魔法使い！　しかし実力はカナリのもの！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 努力派戦闘マスター!!　オルドル!!!";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : 私は、オルドルと申します。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : あなたと戦えるのを楽しみにしていました。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : 是非、この私と正々堂々……";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : 小細工なしで、手合わせをお願いします！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : ふう。私としたことが少し、緊張しているようです……。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("オルドル#1")),"オルドル : 早く落ち着かなければ……。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : イヤッホー！　ファイト！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : なかなかいい対戦カードね！　楽しみ！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a2")),"プロンテラ観覧客 : いけいけ～！　頑張れ～！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : いい試合を頼むぜ！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	オルドル#1	673,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "オルドル : ありがとうございました。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "オルドル : 今回の試合は、とても有意義なものでした。";
	end;
OnTimer5000:
	unittalk "オルドル : 残念ながら私に勝利の女神は微笑まなかったようですが……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "オルドル : 次の試合もあなたが勝つと信じて……";
	end;
OnTimer9000:
	unittalk "オルドル : 観覧席から拝見させていただきます。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "オルドル : 次の試合もがんばってください。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "オルドル : ……流石です。";
	end;
OnTimer104000:
	unittalk "オルドル : かなり白熱した戦いを堪能させていただきました。";
	end;
OnTimer106000:
	unittalk "オルドル : ここまで本気で力を出した試合は久しぶりです。";
	end;
OnTimer108000:
	unittalk "オルドル : また機会がありましたら手合わせをお願いします。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ブルート・ハゼ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#6	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組！　第6試合を開始させていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 初参加にもかかわらず、魔法大会の強豪を次々蹴散らす!!";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 注目度ナンバーワンのスーパールーキー！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : ドキドキするよ～。";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a1")),"アルベルタ観覧客 : おおお！今度の試合もすごそうだ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : 頑張れー！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 目が離せないわ！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : かわいい外見に惑わされるな！　残忍かもしれない！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 血塗られたうさ耳!!　ブルート・ハゼ！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : ボクはキミの血がみたいんだ！";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : ……あれ？";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : なんだかプロポーズの言葉みたいだね！";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : 今のは無論、冗談だよ！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : でも、ボクのあまりの強さに本当にほれちゃだめだからねー！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ブルート・ハゼ#1")),"ブルート・ハゼ : ボクはお兄ちゃんが一番好きだし！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : 新参者もなかなか頑張ってるな！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : このまま優勝しちゃったりして?!";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a2")),"魔法アカデミー学生 : うさ耳かわいいな～。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : いい選手が集まったな！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ブルート・ハゼ#1	674,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ブルート・ハゼ : ちょっと！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ブルート・ハゼ : うさ耳が壊れるんじゃないかと、ヒヤヒヤしたわよ……！";
	end;
OnTimer5000:
	unittalk "ブルート・ハゼ : お兄ちゃんに、子供のころ誕生日祝いだってもらったのに！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ブルート・ハゼ : お陰で、試合に集中できないし……。";
	end;
OnTimer9000:
	unittalk "ブルート・ハゼ : ……ハッ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ブルート・ハゼ : え、えーっと……じゃ、ボクはこれでー！";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : おっと！　ここでB組の試合続報が入ってきました！";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 多くの選手が奮闘していますが、その中でもフェンリルという選手が";
	end;
OnTimer18000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 6連勝を達成し大会最高のダークホースとして名を上げています！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ブルート・ハゼ : うーん、ちょっと物足りなかったかなー？";
	end;
OnTimer104000:
	unittalk "ブルート・ハゼ : キミももう少し、鉄分とったほうがいいと思うよー！";
	end;
OnTimer106000:
	unittalk "ブルート・ハゼ : そんなんじゃ、すぐに血が足りなくなってボクがたのしめないしー。";
	end;
OnTimer108000:
	unittalk "ブルート・ハゼ : さーて、ボクは次の対戦相手の血液型でも予想しようかなっ。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆黒魔（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#7	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組！　第7試合を始めたいとおもいます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 破竹の勢い！　誰が止められるものか！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : このまま優勝まで爆走か?!　疾走の" +.Name$+ "!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 今度の試合も期待できそうだ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a1")),"アルベルタ観覧客 : 1年前から予約した甲斐があったよ！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 凶悪な強さで挑戦者をなぎ倒す！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 熱い試合を期待するわ！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 漆黒の牙！　黒魔！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : ふぁーあ……。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : やれやれ。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : こんなおままごとみたいな試合、何が楽しいのかね。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : 命を賭した戦いじゃなけりゃ、全然ヤル気が出ないぜ……。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : 俺様のターゲットも負けたしな。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("黒魔#1")),"黒魔 : そんなわけだ、お前は適当に相手してやる。";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a1")),"アルベルタ観覧客 : あの冒険者なかなかやるな……！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : そろそろ始まるか!!";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	黒魔#1	675,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "黒魔 : フンッ……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "黒魔 : 俺様に相手を殺さないように手加減しろとか、めんどくせーな……！";
	end;
OnTimer5000:
	unittalk "黒魔 : お陰で、あの女も殺せず仕舞い。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "黒魔 : 死ぬか生きるかの方が、シンプルだろ。";
	end;
OnTimer9000:
	unittalk "黒魔 : まったく、今回は色々ついてねーぜ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "黒魔 : ……仕方ねぇ、今日の仕事はここまでだな。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "黒魔 : つまらん。命を賭した試合でなければ、こんなにもぬるいのかよ。";
	end;
OnTimer104000:
	unittalk "黒魔 : 一度ケチがつくと、お前を殺しても意味がねぇ。";
	end;
OnTimer106000:
	unittalk "黒魔 : 本来のターゲットも、お前のせいで番狂わせがおきちまったし。";
	end;
OnTimer108000:
	unittalk "黒魔 : 今回は見逃してやるが、次はないと思え。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆イフォドス（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#8	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組第8試合を始めさせていただきます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 名実共に今大会のダークホース！　その実力は折り紙つき！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 飛び入りルーンミッドガッツの実力者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : こんなに期待したの初めて！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 強い選手ばかりだわ！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a1")),"フェイヨン観覧客 : 最強はだれかしら！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 鋼鉄のような防御で相手の攻撃もなんのその！";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 本当に目が離せないよ!!";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 熱い闘争心！　鉄壁の防御！　イフォドス！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : 俺と戦ったやつは大概、俺のことを忘れられなくなるらしい！";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : ……なぜかジューのやつは忘れてたけどな！";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : な、泣いてないぞ！";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : こ、これは汗なんだからな！";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : うぅー……よろしくなーっ！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("イフォドス#1")),"イフォドス : それじゃ始めるぞーっ!!";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("コモド観覧客#a1")),"コモド観覧客 : 強いやつらばっかり！　面白いね！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : どっちも強そうだ！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	イフォドス#1	676,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "イフォドス : うおおおおおおおおおおおっ！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "イフォドス : よくわからないうちに負けていた！";
	end;
OnTimer5000:
	unittalk "イフォドス : ということでお前も俺の無敗メモに名前を書く！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "イフォドス : そしてジューの次の目標は、お前だ！";
	end;
OnTimer9000:
	unittalk "イフォドス : 覚悟しておくんだなっ！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "イフォドス : チキショーッ！";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "イフォドス : か、勝った……！　きっと竜の激辛スープを、朝から飲んだおかげだな！";
	end;
OnTimer104000:
	unittalk "イフォドス : うおおおおおおおおおおおっ！　さて、次はジュー！";
	end;
OnTimer106000:
	unittalk "イフォドス : お前に勝って、無敗メモを更新してやるぜ！";
	end;
OnTimer108000:
	unittalk "イフォドス : 待ってろおおおおおおお！";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆レチェニエ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#9	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組！　第9試合を始めたいとおもいます！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 誰が止められるのか！　ダークホースを通り越した超本命！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : その実力は本物！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : うわ～もう第9試合だ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 息をするのも忘れてたよ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 見入ってしまって時間があっという間よ！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 蝶の様な可憐な一面と、毒蛇の様な残忍な一面をあわせもつ聖職者！";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a2")),"プロンテラ観覧客 : いい戦いを期待してるぞー！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : 今回の大会の選手は個性があって面白いな。";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 死のレディー!!　レチェニエ!!";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : ケッ……！";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : 始まるまでが、なげーんだよ！";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : どうせオメーらも最初だけ盛り上がって、";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : 途中から飽きるんだろうがッ!!";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : オラッ！　審判！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("レチェニエ#1")),"レチェニエ : ぐずぐずしてないではじめろッ！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a1")),"フェイヨン観覧客 : 怖そうな選手……！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : ここまで残った選手はみんなすごい！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : あくびが出るくらいつまらない戦いはするなよ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : もっと派手にやって！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	レチェニエ#1	677,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "レチェニエ : あら、私は負けてしまったの？";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "レチェニエ : 変ね……。";
	end;
OnTimer5000:
	unittalk "レチェニエ : 戦った記憶がまったくありませんわ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "レチェニエ : でもここに立っているということは、その通りなのでしょうね。";
	end;
OnTimer9000:
	unittalk "レチェニエ : 前からちょくちょくあるんですの。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "レチェニエ : 不思議ですわ……。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 試合も後半に差し迫っています！　ここでB組の続報!!";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 他の選手とは圧倒的な実力差を見せ付けている選手がいるそうです！";
	end;
OnTimer18000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : それはフェンリス・フェンリル選手とのことです！　A組の選手の皆さん、少し気は早いですが注意する必要がありそうです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "レチェニエ : スゲー物足りねェ……。逆に欲求不満になっちまったじゃねーかッ!!";
	end;
OnTimer104000:
	unittalk "レチェニエ : ったく、これだから大会なんざ出場したくなかったのによ!!";
	end;
OnTimer106000:
	unittalk "レチェニエ : あのクソ司教、無理やり出場させやがって……。";
	end;
OnTimer108000:
	unittalk "レチェニエ : オイ！　次の試合早くしろッ！";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ユメヒメ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#10	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組！　第10試合を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 初参加にして、魔法大会の実力者たちを次々と倒す！！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 実力派の挑戦者！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 手に汗握る!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : 早く始めて！　待ちきれない！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : 見ごたえがある試合ばかり！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : 大会もそろそろ大詰めだ！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 魅惑のダンス！　悩ましげなボディーライン！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 死を導く踊り手!!　ユメヒメ!!";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : やっぱり観覧席で見るのと、雰囲気が違うわね！";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : これだけで参加してよかったかなっておもっちゃったわ。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : ……年甲斐もなく、とか思ってない？";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : まあ、いいわ♪";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : とにかく、お互い楽しみましょう♪";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ユメヒメ#1")),"ユメヒメ : みんなも応援よろしくね～。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : きゃ～!!　ステキ!!";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : 美しい……!!";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : 退屈しないわ!!";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ユメヒメ#1	678,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ユメヒメ : いや～ん！";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ユメヒメ : やっぱり、経験と年の差が出た感じね……。";
	end;
OnTimer5000:
	unittalk "ユメヒメ : でもいい試合だったと思うわ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ユメヒメ : 勝てなかったのは残念だったけど、楽しかったわ。";
	end;
OnTimer9000:
	unittalk "ユメヒメ : 久々に、若い頃の情熱が戻った感じ♪";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ユメヒメ : ありがと♪";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ユメヒメ : ごめんなさいね。";
	end;
OnTimer104000:
	unittalk "ユメヒメ : あまり痛くないように気をつけたつもりなんだけど……。";
	end;
OnTimer106000:
	unittalk "ユメヒメ : 優勝できたら、フベルゲルミルの酒でもおごるわね。";
	end;
OnTimer108000:
	unittalk "ユメヒメ : 良かったら応援よろしくね♪";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ジュー（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#11	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それではA組！　準々決勝を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 勝利への快進撃！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : その勢いは誰にも止められない！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("ロキ#a2")),"ロキ : 血が騒ぐ……。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : どれだけ頑張ったんだろう……！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("アイリス#a2")),"アイリス : 熱い試合ばかりね！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 謎の覆面！　その前に立ったものは誰も生き残れない！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 実戦戦闘の達人！　ジュー!";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : このような場を設けていただき、感謝だ。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : 久しく実戦から離れていたとはいえ……。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : そなたに遅れをとるほど、腕はなまっていないはずだ。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : 全身全霊をかけて、かかってくるとよい。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : 拙者も、全身全霊をかけてお相手しよう。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ジュー#1")),"ジュー : いざ、尋常に勝負！";
	unittalk getnpcid(0,getmdnpcname("ケイオス#a2")),"ケイオス : なかなかいい試合続きだな！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : 今度の試合も期待できるな！";
	unittalk getnpcid(0,getmdnpcname("リディア#a2")),"リディア : ドキドキするわ！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ジュー#1	679,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ジュー : 拙者がこの大会にでたことが、間違いでなかったことを確信した。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ジュー : そなたというこれからの成長が楽しみな若者に出会えたのだから……。";
	end;
OnTimer5000:
	unittalk "ジュー : 次の試合も気を抜かずに挑めば、優勝も、夢ではないだろう。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ジュー : 私の優勝への夢はここで消えてしまったが……。";
	end;
OnTimer9000:
	unittalk "ジュー : 私の分までどうかがんばってほしい。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ジュー : 健闘を祈る！";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	stopnpctimer;
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ジュー : ……そなたの腕前は十分だった。";
	end;
OnTimer104000:
	unittalk "ジュー : そなたが負けた原因はただ1つ、実戦経験の差だ。";
	end;
OnTimer106000:
	unittalk "ジュー : ……まだまだ人生は長い。";
	end;
OnTimer108000:
	unittalk "ジュー : これからも精進されよ。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆ディワイ（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#121	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　最後の試合！　準決勝を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 優勝するまで止まらない！　ここでは止まれない！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 止まらない熱い闘志！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : すごい！　もう準決勝だ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : あっという間だなぁ。";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 数多くの弟子の尊敬を集めるアカデミーの主席教授にして最高の魔法使い！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 今からドキドキしてきたわ！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : どっちを応援しようか悩むよ!!";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 戦場のマエストロ！　ディワイ！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 私の名は、ディワイ。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 君のような人が相手となると、私もローブを正さなければいけないね。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 今回の試合も、無様な姿は見せられない……。";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 育ての親である、ウンバラの皆と族長様、可愛い弟子たち。";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 私にとって、大事な人たちが集まってくれたのだ。";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("ディワイ#1")),"ディワイ : 君も悔いが残らないよう、全力をだしてくれ。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : くう～！　興奮するぜ！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : これで勝った方が決勝戦か！";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a5")),"魔法アカデミー学生 : わあ！　うちの先生だ!!";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a3")),"魔法アカデミー学生 : 先生!!　頑張ってください!!";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a4")),"魔法アカデミー学生 : すごい……私も先生みたいになるんだ……。";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : B組の優勝候補フェンリルも期待大だし！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どっちがフェンリルと戦うことになるのかな！";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a2")),"魔法アカデミー学生 : 私は先生が負けるなんて想像も出来ない！";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a5")),"魔法アカデミー学生 : みんな！先生に届くくらい大声で応援しようよ！";
	end;
OnTimer27000:
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	end;
OnTimer29000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : うう……息するのを忘れてた……げほげほ。";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a2")),"魔法アカデミー学生 : せ～の！　先生!!　ファイト!!";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a3")),"魔法アカデミー学生 : せ～の！　先生!!　ファイト!!";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a4")),"魔法アカデミー学生 : せ～の！　先生!!　ファイト!!";
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#a5")),"魔法アカデミー学生 : せ～の！　先生!!　ファイト!!";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	ディワイ#1	680,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ディワイ : 今回の戦い、きっとウンバラの皆と族長様……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "ディワイ : それに、ゲフェン魔法学校の弟子の皆にとっても納得いくはずだ。";
	end;
OnTimer5000:
	unittalk "ディワイ : 何より、戦った私自身がとてもよい試合をできたと思っているからね。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "ディワイ : 次の試合もがんばってほしい";
	end;
OnTimer9000:
	unittalk "ディワイ : 次の試合に臨む、君に餞別だ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "ディワイ : フェンリルの実力は並大抵ではないと弟子から伝言があった。健闘を祈る。";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : さあて、魔法大会A組およびB組の試合が全て終了いたしました！";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 実在していたのか疑問視されていた呪文を使う選手がいるそうです！";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 名前はフェンリス・フェンリル選手！　堂々とB組1位を勝ち取ったそうです！";
	end;
OnTimer20000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : A組1位との決勝戦が非常に楽しみです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "ディワイ : 勝てたことは勝てたが、辛勝という感じだな……。";
	end;
OnTimer104000:
	unittalk "ディワイ : 君のような人間が、この大会に居てくれて、嬉しかった。";
	end;
OnTimer106000:
	unittalk "ディワイ : 私にもまだまだ甘い部分があることがわかったしな。";
	end;
OnTimer108000:
	unittalk "ディワイ : 本当によい試合をありがとう。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆フェイ・カナビアン（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#122	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組！　最後の試合！　準決勝を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 優勝するまで止まらない！　ここでは止まれない！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : 止まらない熱い闘志！　" +.Name$+ "！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : すごい！　もう準決勝だ！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : そしてこれに立ち向かうのは！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : あっという間だなぁ。";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 静かなるアルデバランからの天才錬金術師!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : 今からドキドキしてきたわ！";
	unittalk getnpcid(0,getmdnpcname("アルベルタ観覧客#a2")),"アルベルタ観覧客 : どっちを応援しようか悩むよ!!";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : フェイ・カナビアン!!　そして彼女の自信作!!　突然変異巨大ホムンクルスのアルフォン！";
	end;
OnTimer13000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : どこであの子を出すと効果的かな……。";
	end;
OnTimer15000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : やっぱりあたしがピンチになったらがいいか。";
	end;
OnTimer17000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : う？";
	end;
OnTimer19000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : 試合始まってるの？";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : ごめんごめん、気づかなかった！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("フェイ・カナビアン#1")),"フェイ・カナビアン : さっ、はじめよっか！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : くう～！　興奮するぜ！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : これで勝った方が決勝戦か！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : B組の優勝候補フェンリルも期待大だし！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どっちがフェンリルと戦うことになるのかな！";
	end;
OnTimer27000:
	stopnpctimer;
	donpcevent getmdnpcname("#試合中アナウンス_timer")+"::OnStart";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a3")),"魔法大会観覧者 : うう……息するのを忘れてた……げほげほ。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : 早く始めて！こっちが緊張してきたわ！";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	フェイ・カナビアン#1	665,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(.Sleep >= 27000) {
		if(!sleep2(12000)) end;
		cutin "paycana_a.bmp", 0;
		if(!sleep2(12000)) end;
		cutin "paycana_a.bmp", 255;
		if(!sleep2(8000)) end;
		end;
	}
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	hideonnpc getmdnpcname("#アルフォン召喚");
	initnpctimer;
	end;
OnTimer1000:
	unittalk "フェイ・カナビアン : ……おっかしいなあ。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin1";
	end;
OnTimer3000:
	unittalk "フェイ・カナビアン : あたしが負ける要素って多分、0.00001パーセントくらいだよ!?";
	end;
OnTimer5000:
	unittalk "フェイ・カナビアン : 何度も繰り返し計算して出した結果なのに～……。";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	end;
OnTimer7000:
	unittalk "フェイ・カナビアン : こんな結果、ありえないよ～……。";
	end;
OnTimer9000:
	unittalk "フェイ・カナビアン : だってどう計算しても、あたしが優勝するパターンだよ？";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	end;
OnTimer11000:
	unittalk "フェイ・カナビアン : 絶対おかしいよ!?";
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : さあて、魔法大会A組およびB組の試合が全て終了いたしました！";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 実在していたのか疑問視されていた呪文を使う選手がいるそうです！";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 名前はフェンリス・フェンリル選手！　堂々とB組1位を勝ち取ったそうです！";
	end;
OnTimer20000:
	stopnpctimer;
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : A組1位との決勝戦が非常に楽しみです！";
	hideoffnpc getmdnpcname("魔法大会進行係#1");
	hideoffnpc getmdnpcname("魔法大会医療班#1");
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "フェイ・カナビアン : んー、あたしの計算じゃもう少し早くケリがつく予定だったのに。";
	end;
OnTimer104000:
	unittalk "フェイ・カナビアン : どこかで計算、間違ったのかな？";
	end;
OnTimer106000:
	unittalk "フェイ・カナビアン : ま、優勝の方程式は間違いじゃないし、いいか。";
	end;
OnTimer108000:
	unittalk "フェイ・カナビアン : あの子も十分、目立ったはずだしね～！";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

1@ge_st.gat,115,50,0	script(HIDDEN)	#アルフォン召喚	139,{
	end;
OnStart:
	monster getmdmapname("1@ge_st.gat"),108,51,"アルフォン・ジュニア",2566,1,getmdnpcname("#アルフォン召喚")+"::OnKilled";
	monster getmdmapname("1@ge_st.gat"),110,51,"アルフォン・ジュニア",2566,1,getmdnpcname("#アルフォン召喚")+"::OnKilled";
	monster getmdmapname("1@ge_st.gat"),109,49,"アルフォン・ジュニア",2566,1,getmdnpcname("#アルフォン召喚")+"::OnKilled";
	end;
OnKilled:
	set '@Count,getmapmobs(getmdmapname("1@ge_st.gat"),getmdnpcname("#アルフォン召喚")+ "::OnKilled");
	if('@Count == 0)
		donpcevent getmdnpcname("#アルフォン召喚")+"::OnStart";
	if('flag) end;
	set 'flag,1;
	unittalk "フェイ・カナビアン : あたしのかわいいアルフォンが～！　許さないよっ！";
	end;
}

//==========================================
// アカデミーマスター（試合開始）＆フェンリル（試合終了）
//------------------------------------------
1@ge_st.gat,109,57,4	script(HIDDEN)	アカデミーマスター#13	10006,{
	end;
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	unittalk "ゲフェンアカデミーマスター : それでは！　A組とB組の最終進出者による！　最後の試合！　決・勝・戦を開始いたします！";
	end;
OnTimer3000:
	unittalk "ゲフェンアカデミーマスター : 誰も予想だにしなかった勇者！";
	end;
OnTimer5000:
	unittalk "ゲフェンアカデミーマスター : しかし決勝戦のチケットを実力でもぎ取った冒険者！";
	end;
OnTimer7000:
	unittalk "ゲフェンアカデミーマスター : 今や人気最高峰の！　優勝候補！";
	end;
OnTimer9000:
	unittalk "ゲフェンアカデミーマスター : 最後の戦場に立つもの！　" +.Name$+ "～!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : ついに決勝戦！";
	end;
OnTimer11000:
	unittalk "ゲフェンアカデミーマスター : 対するは！";
	unittalk getnpcid(0,getmdnpcname("ロキ#a2")),"ロキ : ここまで勝ち進むとは……さすがだな。";
	end;
OnTimer13000:
	unittalk "ゲフェンアカデミーマスター : 圧倒的な実力で相手を葬ってきた最強のウォーロック!!";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : どっちが勝つかわからないな！";
	unittalk getnpcid(0,getmdnpcname("ベインス観覧客#a1")),"ベインス観覧客 : どうしよ！　興奮して鼻血出そう！";
	end;
OnTimer15000:
	unittalk "ゲフェンアカデミーマスター : 見るものを圧倒する、怒涛の勢いの快進撃！";
	unittalk getnpcid(0,getmdnpcname("ケイオス#a2")),"ケイオス : 決勝戦か！　最高の試合が見れそうだ！";
	end;
OnTimer17000:
	unittalk "ゲフェンアカデミーマスター : ルーンミッドガッツ……いや世界最強かも知れない！";
	end;
OnTimer19000:
	unittalk "ゲフェンアカデミーマスター : 蒼い服の魔導士！　フェンリス！　フェンリル!!";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#13")),"フェンリル : ……ついに決勝戦ね。";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a2")),"魔法大会観覧者 : フェンリルを応援するか！";
	unittalk getnpcid(0,getmdnpcname("フェイヨン観覧客#a2")),"フェイヨン観覧客 : 初参加のアイツもすごいよ！俺はあいつを応援するぜ！";
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#13")),"フェンリル : ここまで来たということは……";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a4")),"魔法大会観覧者 : どんな試合になるんだろう、目が離せないよ！";
	unittalk getnpcid(0,getmdnpcname("アイリス#a2")),"アイリス : なかなか面白そうな試合じゃない！";
	end;
OnTimer25000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#13")),"フェンリル : 相当の実力の持ち主だとお見受けするわ。";
	unittalk getnpcid(0,getmdnpcname("プロンテラ観覧客#a1")),"プロンテラ観覧客 : サイン欲しい!!";
	end;
OnTimer27000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#13")),"フェンリル : 私も今回ばかりは、最初から全力でお相手させて頂くわ。";
	end;
OnTimer29000:
	unittalk getnpcid(0,getmdnpcname("フェンリル#13")),"フェンリル : だからあなたも、全力でかかってきてちょうだい。";
	unittalk getnpcid(0,getmdnpcname("リディア#a2")),"リディア : 困った！　どっちも勝ってほしいわ！";
	unittalk getnpcid(0,getmdnpcname("魔法大会観覧者#a1")),"魔法大会観覧者 : いけ～！　最高の試合の開始だぜ!!";
	end;
OnTimer31000:
	stopnpctimer;
	donpcevent getmdnpcname("#決勝戦アナウンス_timer")+"::OnStart";
	end;
}

1@ge_st.gat,114,50,4	script(HIDDEN)	フェンリル#13	664,10,1,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	if(.Sleep >= 31000) {
		if(!sleep2(20000)) end;
		cutin "fenrir_b.bmp", 0;
		if(!sleep2(10000)) end;
		cutin "fenrir_b.bmp", 255;
		if(!sleep2(6000)) end;
		end;
	}
	if(!sleep2(.Sleep)) end;
	end;
OnStart:
	hideoffnpc;
	initnpctimer;
	end;
OnTimer1000:
	unittalk "フェンリル : ……私の完敗よ。";
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : ゲフェン魔法大会!!　決勝戦の勝敗が決まりました!!";
	end;
OnTimer3000:
	unittalk "フェンリル : これほどの実力を持った参加者が居るとは思わなかったわ。";
	misceffect 90,getmdnpcname("アルヒ#q1");
	misceffect 90,getmdnpcname("オルドル#q1");
	misceffect 90,getmdnpcname("黒魔#q1");
	misceffect 90,getmdnpcname("イフォドス#q1");
	end;
OnTimer5000:
	unittalk "フェンリル : 私もまだまだ、精進する必要があるわね……。";
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : 皆さん！　優勝者と準優勝者に惜しみのない拍手をお願い致します!!";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin2";
	misceffect 89,getmdnpcname("アルヒ#q1");
	misceffect 89,getmdnpcname("オルドル#q1");
	misceffect 89,getmdnpcname("黒魔#q1");
	misceffect 89,getmdnpcname("イフォドス#q1");
	end;
OnTimer7000:
	unittalk "フェンリル : とにかく、あなたと決勝戦で戦えてよかったわ。";
	misceffect 62,getmdnpcname("アルヒ#q1");
	misceffect 62,getmdnpcname("オルドル#q1");
	misceffect 62,getmdnpcname("黒魔#q1");
	misceffect 62,getmdnpcname("イフォドス#q1");
	end;
OnTimer9000:
	unittalk "フェンリル : ゲフェン魔法大会、優勝おめでとう。";
	unittalk getnpcid(0,getmdnpcname("アカデミーマスター#1")),"ゲフェンアカデミーマスター : ゲフェン魔法大会はこれにて終了となります!!　次の大会もふるってのご参加をお願いいたします!!";
	donpcevent getmdnpcname("アカデミーマスター#1")+"::OnWin3";
	misceffect 225,getmdnpcname("アルヒ#q1");
	misceffect 225,getmdnpcname("オルドル#q1");
	misceffect 225,getmdnpcname("黒魔#q1");
	misceffect 225,getmdnpcname("イフォドス#q1");
	end;
OnTimer11000:
	unittalk "フェンリル : でも……次は必ず私が勝つから、覚悟しててね。";
	misceffect 234,getmdnpcname("アルヒ#q1");
	misceffect 234,getmdnpcname("オルドル#q1");
	misceffect 234,getmdnpcname("黒魔#q1");
	misceffect 234,getmdnpcname("イフォドス#q1");
	end;
OnTimer13000:
	hideonnpc;
	end;
OnTimer15000:
	stopnpctimer;
	hideoffnpc getmdnpcname("#魔法大会優勝1");
	donpcevent getmdnpcname("#魔法大会優勝1")+"::OnStart";
	end;
OnTimer100000:
	end;
OnTimer102000:
	unittalk "フェンリル : お疲れ様。";
	end;
OnTimer104000:
	unittalk "フェンリル : 決勝の対戦相手があなたで、本当に良かったわ。";
	end;
OnTimer106000:
	unittalk "フェンリル : おかげで久しぶりに楽しく戦えたもの。";
	end;
OnTimer108000:
	unittalk "フェンリル : またいつか、手合わせをお願いするわね。";
	end;
OnTimer110000:
	stopnpctimer;
	hideonnpc;
	hideoffnpc getmdnpcname("#魔法大会終了1");
	end;
}

//==========================================
// 魔法大会観覧者
//------------------------------------------
1@ge_st.gat,95,62,6		script	魔法大会観覧者#a1	870,{}
1@ge_st.gat,113,62,4	script	魔法大会観覧者#a2	868,{}
1@ge_st.gat,99,62,6		script	魔法大会観覧者#a3	727,{}
1@ge_st.gat,119,62,4	script	魔法大会観覧者#a4	728,{}
1@ge_st.gat,123,62,4	script	魔法アカデミー学生#a1	805,{}
1@ge_st.gat,103,62,6	script	魔法アカデミー学生#a2	84,{}
1@ge_st.gat,114,62,4	script	魔法アカデミー学生#a3	86,{}
1@ge_st.gat,109,62,4	script	魔法アカデミー学生#a4	921,{}
1@ge_st.gat,122,62,4	script	魔法アカデミー学生#a5	72,{}
1@ge_st.gat,97,62,6		script	プロンテラ観覧客#a1	985,{}
1@ge_st.gat,115,62,4	script	プロンテラ観覧客#a2	945,{}
1@ge_st.gat,117,62,4	script	フェイヨン観覧客#a1	803,{}
1@ge_st.gat,101,62,6	script	フェイヨン観覧客#a2	828,{}
1@ge_st.gat,121,62,4	script	アルベルタ観覧客#a1	712,{}
1@ge_st.gat,105,62,6	script	アルベルタ観覧客#a2	89,{}
1@ge_st.gat,107,62,6	script	ベインス観覧客#a1	558,{}
1@ge_st.gat,111,62,4	script	コモド観覧客#a1	850,{}
1@ge_st.gat,106,62,6	script	ロキ#a2	512,{}
1@ge_st.gat,108,62,6	script	ケイオス#a2	683,{}
1@ge_st.gat,110,62,4	script	アイリス#a2	666,{}
1@ge_st.gat,112,62,4	script	リディア#a2	10010,{}
1@ge_st.gat,93,62,6		script	魔法大会観覧者#a5	46,{}
1@ge_st.gat,94,62,6		script	魔法大会観覧者#a6	67,{}
1@ge_st.gat,96,62,6		script	魔法大会観覧者#a8	47,{}
1@ge_st.gat,98,62,6		script	魔法大会観覧者#a10	48,{}
1@ge_st.gat,100,62,6	script	魔法大会観覧者#a12	49,{}
1@ge_st.gat,102,62,6	script	魔法大会観覧者#a14	66,{}
1@ge_st.gat,104,62,6	script	魔法大会観覧者#a16	68,{}
1@ge_st.gat,116,62,4	script	魔法大会観覧者#a28	69,{}
1@ge_st.gat,118,62,4	script	魔法大会観覧者#a30	70,{}
1@ge_st.gat,120,62,4	script	魔法大会観覧者#a32	51,{}
1@ge_st.gat,124,62,4	script	魔法大会観覧者#a36	71,{}
1@ge_st.gat,125,62,4	script	魔法大会観覧者#a37	52,{}
1@ge_st.gat,87,59,6		script	魔法大会観覧者#a198	484,{}
1@ge_st.gat,87,60,6		script	魔法大会観覧者#a199	534,{}
1@ge_st.gat,88,61,6		script	魔法大会観覧者#a200	540,{}
1@ge_st.gat,89,62,6		script	魔法大会観覧者#a201	923,{}
1@ge_st.gat,90,63,6		script	魔法大会観覧者#a202	124,{}
1@ge_st.gat,91,63,6		script	魔法大会観覧者#a203	838,{}
1@ge_st.gat,92,64,6		script	魔法大会観覧者#a38	771,{}
1@ge_st.gat,93,64,6		script	魔法大会観覧者#a39	73,{}
1@ge_st.gat,94,64,6		script	魔法大会観覧者#a40	74,{}
1@ge_st.gat,95,64,6		script	魔法大会観覧者#a41	54,{}
1@ge_st.gat,96,64,6		script	魔法大会観覧者#a42	55,{}
1@ge_st.gat,97,64,6		script	魔法大会観覧者#a43	56,{}
1@ge_st.gat,98,64,6		script	魔法大会観覧者#a44	57,{}
1@ge_st.gat,99,64,6		script	魔法大会観覧者#a45	75,{}
1@ge_st.gat,100,64,6	script	魔法大会観覧者#a46	76,{}
1@ge_st.gat,101,64,6	script	魔法大会観覧者#a47	77,{}
1@ge_st.gat,102,64,6	script	魔法大会観覧者#a48	78,{}
1@ge_st.gat,103,64,6	script	魔法大会観覧者#a49	58,{}
1@ge_st.gat,104,64,6	script	魔法大会観覧者#a50	106,{}
1@ge_st.gat,105,64,6	script	魔法大会観覧者#a51	59,{}
1@ge_st.gat,106,64,6	script	魔法大会観覧者#a52	60,{}
1@ge_st.gat,107,64,6	script	魔法大会観覧者#a53	79,{}
1@ge_st.gat,108,64,6	script	魔法大会観覧者#a54	80,{}
1@ge_st.gat,109,64,4	script	魔法大会観覧者#a55	947,{}
1@ge_st.gat,110,64,4	script	魔法大会観覧者#a56	53,{}
1@ge_st.gat,111,64,4	script	魔法大会観覧者#a57	62,{}
1@ge_st.gat,112,64,4	script	魔法大会観覧者#a58	107,{}
1@ge_st.gat,113,64,4	script	魔法大会観覧者#a59	108,{}
1@ge_st.gat,114,64,4	script	魔法大会観覧者#a60	61,{}
1@ge_st.gat,115,64,4	script	魔法大会観覧者#a61	804,{}
1@ge_st.gat,116,64,4	script	魔法大会観覧者#a62	123,{}
1@ge_st.gat,117,64,4	script	魔法大会観覧者#a63	90,{}
1@ge_st.gat,118,64,4	script	魔法大会観覧者#a64	91,{}
1@ge_st.gat,119,64,4	script	魔法大会観覧者#a65	92,{}
1@ge_st.gat,120,64,4	script	魔法大会観覧者#a65	300,{}
1@ge_st.gat,121,64,4	script	魔法大会観覧者#a67	920,{}
1@ge_st.gat,122,64,4	script	魔法大会観覧者#a68	806,{}
1@ge_st.gat,123,64,4	script	魔法大会観覧者#a69	807,{}
1@ge_st.gat,124,64,4	script	魔法大会観覧者#a70	808,{}
1@ge_st.gat,125,64,4	script	魔法大会観覧者#a71	711,{}
1@ge_st.gat,126,64,4	script	魔法大会観覧者#a72	714,{}
1@ge_st.gat,127,63,4	script	魔法大会観覧者#a73	724,{}
1@ge_st.gat,128,63,4	script	魔法大会観覧者#a74	885,{}
1@ge_st.gat,129,62,4	script	魔法大会観覧者#a75	809,{}
1@ge_st.gat,130,61,4	script	魔法大会観覧者#a76	810,{}
1@ge_st.gat,130,60,4	script	魔法大会観覧者#a77	63,{}
1@ge_st.gat,128,60,4	script	魔法大会観覧者#a78	744,{}
1@ge_st.gat,128,59,4	script	魔法大会観覧者#a79	953,{}
1@ge_st.gat,128,58,4	script	魔法大会観覧者#a80	408,{}
1@ge_st.gat,128,57,4	script	魔法大会観覧者#a81	473,{}
1@ge_st.gat,128,56,4	script	魔法大会観覧者#a82	64,{}
1@ge_st.gat,128,55,4	script	魔法大会観覧者#a83	65,{}
1@ge_st.gat,128,54,4	script	魔法大会観覧者#a84	740,{}
1@ge_st.gat,128,53,4	script	魔法大会観覧者#a85	473,{}
1@ge_st.gat,128,52,4	script	魔法大会観覧者#a86	474,{}
1@ge_st.gat,128,51,4	script	魔法大会観覧者#a87	478,{}
1@ge_st.gat,128,45,2	script	魔法大会観覧者#a88	741,{}
1@ge_st.gat,128,44,2	script	魔法大会観覧者#a89	122,{}
1@ge_st.gat,128,43,2	script	魔法大会観覧者#a90	121,{}
1@ge_st.gat,128,42,2	script	魔法大会観覧者#a91	879,{}
1@ge_st.gat,128,41,2	script	魔法大会観覧者#a92	979,{}
1@ge_st.gat,128,40,2	script	魔法大会観覧者#a93	914,{}
1@ge_st.gat,128,39,2	script	魔法大会観覧者#a94	813,{}
1@ge_st.gat,128,38,2	script	魔法大会観覧者#a95	120,{}
1@ge_st.gat,128,37,2	script	魔法大会観覧者#a96	742,{}
1@ge_st.gat,128,33,2	script	魔法大会観覧者#a101	816,{}
1@ge_st.gat,127,33,2	script	魔法大会観覧者#a102	817,{}
1@ge_st.gat,125,32,2	script	魔法大会観覧者#a104	886,{}
1@ge_st.gat,123,32,2	script	魔法大会観覧者#a106	745,{}
1@ge_st.gat,121,32,2	script	魔法大会観覧者#a108	82,{}
1@ge_st.gat,119,32,2	script	魔法大会観覧者#a110	941,{}
1@ge_st.gat,117,32,2	script	魔法大会観覧者#a112	83,{}
1@ge_st.gat,115,32,2	script	魔法大会観覧者#a114	951,{}
1@ge_st.gat,113,32,2	script	魔法大会観覧者#a116	983,{}
1@ge_st.gat,111,32,2	script	魔法大会観覧者#a118	846,{}
1@ge_st.gat,109,32,2	script	魔法大会観覧者#a120	985,{}
1@ge_st.gat,107,32,8	script	魔法大会観覧者#a122	701,{}
1@ge_st.gat,105,32,8	script	魔法大会観覧者#a124	987,{}
1@ge_st.gat,103,32,8	script	魔法大会観覧者#a126	989,{}
1@ge_st.gat,101,32,8	script	魔法大会観覧者#a128	466,{}
1@ge_st.gat,99,32,8	script	魔法大会観覧者#a130	892,{}
1@ge_st.gat,97,32,8	script	魔法大会観覧者#a132	991,{}
1@ge_st.gat,95,32,8	script	魔法大会観覧者#a134	993,{}
1@ge_st.gat,93,32,8	script	魔法大会観覧者#a136	748,{}
1@ge_st.gat,92,32,8	script	魔法大会観覧者#a137	725,{}
1@ge_st.gat,91,33,8	script	魔法大会観覧者#a138	726,{}
1@ge_st.gat,89,38,8	script	魔法大会観覧者#a144	542,{}
1@ge_st.gat,89,39,8	script	魔法大会観覧者#a145	937,{}
1@ge_st.gat,89,40,8	script	魔法大会観覧者#a146	757,{}
1@ge_st.gat,89,41,8	script	魔法大会観覧者#a147	758,{}
1@ge_st.gat,89,42,8	script	魔法大会観覧者#a148	759,{}
1@ge_st.gat,89,43,8	script	魔法大会観覧者#a149	892,{}
1@ge_st.gat,89,44,8	script	魔法大会観覧者#a150	760,{}
1@ge_st.gat,89,45,8	script	魔法大会観覧者#a151	761,{}
1@ge_st.gat,89,51,6	script	魔法大会観覧者#a189	982,{}
1@ge_st.gat,89,52,6	script	魔法大会観覧者#a190	919,{}
1@ge_st.gat,89,53,6	script	魔法大会観覧者#a191	413,{}
1@ge_st.gat,89,54,6	script	魔法大会観覧者#a192	943,{}
1@ge_st.gat,89,55,6	script	魔法大会観覧者#a193	538,{}
1@ge_st.gat,89,56,6	script	魔法大会観覧者#a194	536,{}
1@ge_st.gat,89,57,6	script	魔法大会観覧者#a195	482,{}
1@ge_st.gat,89,58,6	script	魔法大会観覧者#a196	95,{}
1@ge_st.gat,89,59,6	script	魔法大会観覧者#a197	911,{}
1@ge_st.gat,94,34,8	script	魔法大会観覧者#a153	87,{}
1@ge_st.gat,96,34,8	script	魔法大会観覧者#a155	704,{}
1@ge_st.gat,98,34,8	script	魔法大会観覧者#a157	894,{}
1@ge_st.gat,100,34,8	script	魔法大会観覧者#a159	906,{}
1@ge_st.gat,102,34,8	script	魔法大会観覧者#a161	476,{}
1@ge_st.gat,104,34,8	script	魔法大会観覧者#a163	995,{}
1@ge_st.gat,106,34,8	script	魔法大会観覧者#a165	839,{}
1@ge_st.gat,108,34,8	script	魔法大会観覧者#a167	717,{}
1@ge_st.gat,110,34,2	script	魔法大会観覧者#a169	863,{}
1@ge_st.gat,112,34,2	script	魔法大会観覧者#a171	819,{}
1@ge_st.gat,114,34,2	script	魔法大会観覧者#a173	821,{}
1@ge_st.gat,116,34,2	script	魔法大会観覧者#a175	917,{}
1@ge_st.gat,118,34,2	script	魔法大会観覧者#a177	793,{}
1@ge_st.gat,120,34,2	script	魔法大会観覧者#a179	823,{}
1@ge_st.gat,122,34,2	script	魔法大会観覧者#a181	825,{}
1@ge_st.gat,124,34,2	script	魔法大会観覧者#a183	918,{}
1@ge_st.gat,92,59,0		script	#魔法大会花火_11	139,{}
1@ge_st.gat,100,60,0	script	#魔法大会花火_12	139,{}
1@ge_st.gat,109,60,0	script	#魔法大会花火_13	139,{}
1@ge_st.gat,118,60,0	script	#魔法大会花火_14	139,{}
1@ge_st.gat,126,59,0	script	#魔法大会花火_15	139,{}
1@ge_st.gat,126,37,0	script	#魔法大会花火_16	139,{}
1@ge_st.gat,118,36,0	script	#魔法大会花火_17	139,{}
1@ge_st.gat,109,36,0	script	#魔法大会花火_18	139,{}
1@ge_st.gat,100,36,0	script	#魔法大会花火_19	139,{}
1@ge_st.gat,92,37,0		script	#魔法大会花火_20	139,{}
//1@ge_st.gat,109,49,0	script	#ガヤ管理	139,{}

//==========================================
// 応援NPC
//------------------------------------------
1@ge_st.gat,88,48,0	script	#応援NPC制御	139,{
	end;
OnStart:
	set '@rnd,rand(1,100);
	if ('@rnd <= 1 && '@rnd >= 25)
		hideoffnpc getmdnpcname("魔法大会観覧者#z1");		//出現率25％
	if ('@rnd <= 26 && '@rnd >= 45)
		hideoffnpc getmdnpcname("魔法大会観覧者#z2");		//出現率20％
	if ('@rnd <= 46 && '@rnd >= 58)
		hideoffnpc getmdnpcname("魔法大会観覧者#z3");		//出現率13％
	if ('@rnd <= 59 && '@rnd >= 68)
		hideoffnpc getmdnpcname("魔法大会観覧者#z4");		//出現率10％
	if ('@rnd <= 69 && '@rnd >= 70)
		hideoffnpc getmdnpcname("魔法大会観覧者#z5");		//出現率2％
	//出現しない率30％
	end;
}

1@ge_st.gat,88,48,8	script(HIDDEN)	魔法大会観覧者#z1	810,{
	if(!checkquest(114700)) {
		setquest 114700;
		compquest 114700;
	}
	mes "[怪しい男]";
	mes "張った張ったー。";
	mes "さぁ張った。";
	mes "今なら" +strcharinfo(0)+ "の倍率";
	mes rand(20,99)+ "倍　だよ。";
	mes "さぁ一口どうだ！";
	next;
	mes "[怪しい男]";
	mes "あっ、やべっ。";
	mes "　";
	mes "おい、試合頑張れよ。";
	mes "頼むぞ。　じゃあな！";
	close2;
	hideonnpc;
	end;
}

1@ge_st.gat,88,48,8	script(HIDDEN)	魔法大会観覧者#z2	72,{
	if(!checkquest(114701)) {
		setquest 114701;
		compquest 114701;
	}
	mes "[変な歌を歌う少女]";
	mes "応援ソング歌います！";
	mes "　";
	mes "フー！レー！フーレ！";
	mes "フーーー！";
	mes "フカヒレ！";
	mes "ありがとうございました。";
	close2;
	hideonnpc;
	end;
}

1@ge_st.gat,88,48,8	script(HIDDEN)	魔法大会観覧者#z3	61,{
	if(!checkquest(114702)) {
		setquest 114702;
		compquest 114702;
	}
	mes "[戦い好きのマスター]";
	mes "お酒は好きですか？";
	mes "勝利後の美酒に酔えるよう";
	mes "頑張ってください。";
	close2;
	hideonnpc;
	end;
}

1@ge_st.gat,88,48,8	script(HIDDEN)	魔法大会観覧者#z4	553,{
	if(!checkquest(114703)) {
		setquest 114703;
		compquest 114703;
	}
	mes "[夢中な猫]";
	mes "頑張れー！";
	mes "いけー！　もっとやれにゃー！";
	mes "餌代を取り返すにゃー！";
	mes "負けたままでは終われないにゃー！";
	close2;
	hideonnpc;
	end;
}

1@ge_st.gat,88,48,8	script(HIDDEN)	魔法大会観覧者#z5	655,{
	if(!checkquest(114704)) {
		setquest 114704;
		compquest 114704;
	}
	mes "[騎士]";
	mes "こんにちは。";
	mes "おかしいな。";
	mes "隠れていたつもりなんですけど……。";
	next;
	mes "[騎士]";
	mes "試合頑張ってくださいね。";
	mes "あと……";
	mes "お母さんに怒られちゃうので";
	mes "ここで私を見た事は";
	mes "どうか内緒にしてください。";
	close2;
	hideonnpc;
	end;
}

//==========================================
// 優勝後の祝勝会
//------------------------------------------
1@ge_st.gat,104,53,6	script(HIDDEN)	アルヒ#q1	670,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "アルヒ : ゆ、優勝おめでとうございます！　……す、すごいなあ！";
		end;
	case 1:
        unittalk "アルヒ : 本当に優勝、おめでとうございます！";
		end;
	case 2:
        unittalk "アルヒ : 僕も、一回戦くらいは勝てるようにがんばります……！";
		end;
    }
}
1@ge_st.gat,100,49,6	script(HIDDEN)	ディオ・アネモス#q1	669,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "ディオ・アネモス : 僕はねぇ……君が勝ちそうだと思ってたよ。";
		end;
	case 1:
        unittalk "ディオ・アネモス : 僕にとって今は、優勝よりマイハニーなんだよねぇ。";
		end;
	case 2:
        unittalk "ディオ・アネモス : 一応、優勝おめでとうはいっておくよ。";
		end;
	}
}
1@ge_st.gat,102,46,8	script(HIDDEN)	フェモン#q1	672,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "フェモン : フッ、腕では敵わなかったが、モテ具合ではオレが優勝だな。";
		end;
	case 1:
        unittalk "フェモン : 優勝者なら、身だしなみも気にしたほうがいいぜ？";
		end;
	case 2:
        unittalk "フェモン : フン。優勝しても、女の子にもてるとは限らないからな!?";
		end;
	}
}
1@ge_st.gat,104,44,8	script(HIDDEN)	オルドル#q1	673,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "オルドル : あなたの腕前になるまで、どのくらいかかるだろう……。";
		end;
	case 1:
        unittalk "オルドル : ……流石です！　優勝者が、戦ったあなたで私も嬉しいです。";
		end;
	case 2:
        unittalk "オルドル : やはり、参考書で読むのと実戦は違いますね。おめでとうございます。";
		end;
	}
}
1@ge_st.gat,112,45,2	script(HIDDEN)	ブルート・ハゼ#q1	674,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "ブルート・ハゼ : 優勝とか……すごすぎなんだけど!?　あっ。お、おめでとうだよ?♪";
		end;
	case 1:
        unittalk "ブルート・ハゼ : ボクも強いけど、キミも強いんだね！　今度からキミも、うさ耳つけて活動しよ?！";
		end;
	case 2:
        unittalk "ブルート・ハゼ : 優勝っておいしいんでしょ？　でしょ？　いいなー。";
		end;
	}
}
1@ge_st.gat,116,46,2	script(HIDDEN)	黒魔#q1	675,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "黒魔 : つまらん。……優勝なぞ、死んでしまえば無意味なものだ。";
		end;
	case 1:
        unittalk "黒魔 : ……もしあの女が優勝していたら、面白いものが見れたのに残念だったな。";
		end;
	case 2:
        unittalk "黒魔 : 優勝者は目立つからな。寝首をかかれないようにしろよ。";
		end;
	}
}
1@ge_st.gat,115,53,4	script(HIDDEN)	イフォドス#q1	676,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "イフォドス : くそー！　優勝とかずるいぞ！";
		end;
	case 1:
        unittalk "イフォドス : さすが、俺が認めたライバル！　おめでとうだ！";
		end;
	case 2:
        unittalk "イフォドス : 次があれば、俺が優勝してモテモテに違いない！";
		end;
	}
}
1@ge_st.gat,116,49,4	script(HIDDEN)	レチェニエ#q1	677,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "レチェニエ : 優勝、おめでとうございます。本当に凄いですわ……。";
		end;
	case 1:
        unittalk "レチェニエ : 優勝だぁ？　そんなもん、あたしには関係ねーよ！";
		end;
	case 2:
        unittalk "レチェニエ : お祝いに病院送りにしてさしあげましょうか？　うふふ、冗談ですわ。";
		end;
	}
}
1@ge_st.gat,112,53,4	script(HIDDEN)	ユメヒメ#q1	678,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "ユメヒメ : 年齢関係なく、優勝は嬉しいわよね♪";
		end;
	case 1:
        unittalk "ユメヒメ : 優勝パーティー、私の劇場で開催してほしいわ?♪";
		end;
	case 2:
        unittalk "ユメヒメ : 何度でもいうわよ?♪　優勝おめでとう。";
		end;
	}
}
1@ge_st.gat,109,54,4	script(HIDDEN)	ジュー#q1	679,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "ジュー : なにより、そなたのようなものに会えたことが一番の収穫だ。";
		end;
	case 1:
        unittalk "ジュー : またここに来る時は連絡してくれ。拙者の妻の手料理でもご馳走しよう。";
		end;
	case 2:
        unittalk "ジュー : 優勝、おめでとう。そなたの腕前であれば、当然の結果だな。";
		end;
	}
}
1@ge_st.gat,106,50,4	script(HIDDEN)	ディワイ#q1	680,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "ディワイ : 気が向いたら、ウンバラや、魔法学校にも顔を出してほしいものだ。";
		end;
	case 1:
        unittalk "ディワイ : この大会で優勝することはとても名誉なことだ。おめでとう。";
		end;
	case 2:
		unittalk "ディワイ : ウンバラの皆と族長、弟子の皆も、君におめでとうといっていたよ。";
		end;
	}
}
1@ge_st.gat,107,48,8	script(HIDDEN)	フェイ・カナビアン#q1	665,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "フェイ・カナビアン : 本当は、あたしがそこにいるはずだったのになあ。";
		end;
	case 1:
        unittalk "フェイ・カナビアン：優勝おめでと?……。でも次は、あたしが優勝だからね！";
		end;
	case 2:
        unittalk "フェイ・カナビアン : 次こそ、あたしとあの子で優勝の方程式を証明するよ！";
		end;
	}
}
1@ge_st.gat,112,50,4	script(HIDDEN)	フェンリル#q1	664,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
        unittalk "フェンリル : 今回は完全に私の負けよ。本当におめでとう。";
		end;
	case 1:
        unittalk "フェンリル : あなたのような人がいると、いろいろな意味で心強いわ。";
		end;
	case 2:
        unittalk "フェンリル : 他の参加者も、あなたの優勝を祝って、一言話したいそうよ。";
		end;
	}
}

//==========================================
// 大会終了後の原作キャラ達
//------------------------------------------
1@gef.gat,125,105,4	script(HIDDEN)	アイリス#a1	666,{
	if(checkquest(9310) & 0x8) {
		cutin "hero_iris_02.bmp", 2;
		mes "[アイリス]";
		mes "旅の途中で飛行船にトラブルが";
		mes "おきた時には本当、ついてないなって";
		mes "思ったんだけどね～。";
		mes "面白い大会も見れたから、";
		mes "結果的には良かったのかもね。";
		close2;
		cutin "hero_iris_02.bmp", 255;
		end;
	}
	if(checkquest(9308)) {
		cutin "hero_iris_02.bmp", 2;
		mes "[アイリス]";
		mes "まさか優勝するなんて……。";
		mes "ほんと、すごかったよ！";
		mes "でもだからって、";
		mes "今後も腕を磨くことを";
		mes "怠っちゃだめだよ!?";
		next;
		mes "[アイリス]";
		mes "って、ことで！";
		mes "すごい試合を見せてもらったお礼！";
		mes "私だと、どこまで勝てるか……。";
		mes "だからささやかながら、";
		mes "私からのご褒美ってところ。";
		mes "受け取ってよね！";
		set '@item,rand(6,7);
	}
	else if(checkquest(9309)) {
		cutin "hero_iris_02.bmp", 2;
		mes "[アイリス]";
		mes "試合、お疲れ様！";
		mes "今回は残念だったわね。";
		mes "次はいい結果になるといいね。";
		next;
		mes "[アイリス]";
		mes "とはいえ、がんばってたのは";
		mes "すごく伝わったし……";
		mes "たいしたものじゃないけど";
		mes "私からプレゼント！";
		mes "これからもがんばってね。";
		set '@item,rand(1,7);
	}
	switch('@item) {
	case 1: getitem 501, 1; break;
	case 2: getitem 502, 1; break;
	case 3: getitem 503, 1; break;
	case 4: getitem 504, 1; break;
	case 5: getitem 505, 1; break;
	case 6: getitem 607, 1; break;
	case 7: getitem 608, 1; break;
	}
	setquest 9310;
	compquest 9310;
	close2;
	cutin "hero_iris_02.bmp", 255;
	end;
}

1@gef.gat,123,108,4	script(HIDDEN)	ケイオス#a1	683,{
	if(checkquest(9311) & 0x8) {
		cutin "hero_chaos_01.bmp", 2;
		mes "[ケイオス]";
		mes "飛行船に問題が起き、宿を探して";
		mes "ここ、ゲフェンに来たんだ。";
		mes "色々あってフェンリルが大会に出る！";
		mes "って決まった時はどうなるかと";
		mes "不安だったんだが……。";
		mes "ある意味、結果オーライだったな。";
		close2;
		cutin "hero_chaos_01.bmp", 255;
		end;
	}
	if(checkquest(9308)) {
		cutin "hero_chaos_01.bmp", 2;
		mes "[ケイオス]";
		mes "優勝かー！";
		mes "フェンリルの強さを知ってるだけに";
		mes "正直、あまり期待してなかったが……。";
		mes "それだけにビックリだぜ！";
		mes "改めて、おめでとうな！";
		next;
		mes "[ケイオス]";
		mes "本音を言うと、";
		mes "そんなにこの大会に";
		mes "期待してなかったんだが……。";
		mes "いい意味で、裏切られたぜ！";
		mes "ってことで、将来有望な、";
		mes "あんたにこれをやるよ！";
		set '@item,rand(6,7);
	}
	else if(checkquest(9309)) {
		cutin "hero_chaos_01.bmp", 2;
		mes "[ケイオス]";
		mes "いい試合だったぜ！";
		mes "まあ、惜しいところもあるが";
		mes "それ以上に、あんたには";
		mes "可能性を感じたしな！";
		next;
		mes "[ケイオス]";
		mes "ってことで、だ。";
		mes "こっちも見てて熱くなるような";
		mes "試合を見せてくれたお礼だ！";
		mes "たいしたものじゃないが……";
		mes "良かったら貰ってくれ。";
		set '@item,rand(1,7);
	}
	switch('@item) {
	case 1: getitem 501, 1; break;
	case 2: getitem 502, 1; break;
	case 3: getitem 503, 1; break;
	case 4: getitem 504, 1; break;
	case 5: getitem 505, 1; break;
	case 6: getitem 607, 1; break;
	case 7: getitem 608, 1; break;
	}
	setquest 9311;
	compquest 9311;
	close2;
	cutin "hero_chaos_01.bmp", 255;
	end;
}

1@gef.gat,117,108,6	script(HIDDEN)	リディア#a1	10010,{
	if(checkquest(9312) & 0x8) {
		cutin "lydia_a.bmp", 2;
		mes "[リディア]";
		mes "あーあ、飛行船でもっと";
		mes "金目のものがないか";
		mes "見ておけばよかったなあ。";
		mes "こんなんじゃ、いつまでも";
		mes "世界一のトレジャーハンターに";
		mes "なれやしないよ。";
		close2;
		cutin "lydia_a.bmp", 255;
		end;
	}
	if(checkquest(9308)) {
		cutin "lydia_a.bmp", 2;
		mes "[リディア]";
		mes "まさか、フェンリルを倒して";
		mes "優勝なんて、やるじゃない！";
		mes "私も盗……ゴホン、宝探しとかなら";
		mes "自信があるんだけどなあ。";
		mes "まっ、今回は素直におめでとうって";
		mes "いっておいてあげる！";
		next;
		mes "[リディア]";
		mes "何はともあれ、お疲れさま！";
		mes "Zenyが手に入るチャンスを";
		mes "まんまと逃したこととか、";
		mes "忘れるくらい、熱中できたし、";
		mes "そのお礼ってことで……";
		mes "これあげるよ！";
		set '@item,rand(6,7);
	}
	else if(checkquest(9309)) {
		cutin "lydia_a.bmp", 2;
		mes "[リディア]";
		mes "あんたの試合、";
		mes "しっかり観客席から";
		mes "見せてもらったよ！";
		next;
		mes "[リディア]";
		mes "試合結果は残念だったね……。";
		mes "でも、あんたもがんばったんだし";
		mes "次また、がんばればいいよ！";
		mes "ほら！　これあげるから！";
		set '@item,rand(1,7);
	}
	switch('@item) {
	case 1: getitem 501, 1; break;
	case 2: getitem 502, 1; break;
	case 3: getitem 503, 1; break;
	case 4: getitem 504, 1; break;
	case 5: getitem 505, 1; break;
	case 6: getitem 607, 1; break;
	case 7: getitem 608, 1; break;
	}
	setquest 9312;
	compquest 9312;
	close2;
	cutin "lydia_a.bmp", 255;
	end;
}

1@gef.gat,115,105,6	script(HIDDEN)	ロキ#a1	512,{
	if(checkquest(9314) & 0x8) {
		cutin "ep14_roki01.bmp", 2;
		mes "[ロキ]";
		mes "俺たちは飛行船で旅をしていたが";
		mes "問題が起きて、ここで足止めを";
		mes "食っている状態だ。";
		mes "飛行船がなければ動けないというのも";
		mes "不便なものだな。";
		close2;
		cutin "ep14_roki01.bmp", 255;
		end;
	}
	if(checkquest(9308)) {
		cutin "ep14_roki01.bmp", 2;
		mes "[ロキ]";
		mes "……人間というものは";
		mes "どこからそんな力を発揮できるのか。";
		mes "……なかなか興味深い。";
		next;
		mes "[ロキ]";
		mes "何より……";
		mes "フェンリルに勝つには";
		mes "生半可な腕前のやつでは";
		mes "敵うはずがない。";
		mes "……だから受け取れ。";
		mes "これは俺からの餞別だ。";
		set '@item,rand(6,7);
	}
	else if(checkquest(9309)) {
		cutin "ep14_roki01.bmp", 2;
		mes "[ロキ]";
		mes "お前の試合、見せてもらった。";
		mes "まだまだ荒削りだが……";
		mes "見所があるようだな。";
		next;
		mes "[ロキ]";
		mes "……。";
		mes "これは俺からの餞別だ。";
		mes "受け取れ。";
		set '@item,rand(1,7);
	}
	switch('@item) {
	case 1: getitem 501, 1; break;
	case 2: getitem 502, 1; break;
	case 3: getitem 503, 1; break;
	case 4: getitem 504, 1; break;
	case 5: getitem 505, 1; break;
	case 6: getitem 607, 1; break;
	case 7: getitem 608, 1; break;
	}
	setquest 9314;
	compquest 9314;
	close2;
	cutin "ep14_roki01.bmp", 255;
	end;
}

1@gef.gat,120,108,4	script(HIDDEN)	フェンリル#a1	664,{
	if(checkquest(9313) & 0x8) {
		cutin "fenrir_a.bmp", 2;
		mes "[フェンリル]";
		mes "宿探しついでに今回の大会に";
		mes "参加することになったのだけれど、";
		mes "私としては参加して正解だったわ。";
		mes "お陰で私もまだまだ修行が";
		mes "必要なことがわかったのだから。";
		close2;
		cutin "fenrir_a.bmp", 255;
		end;
	}
	if(checkquest(9308)) {
		cutin "fenrir_a.bmp", 2;
		mes "[フェンリル]";
		mes "今回の大会、悔しいけど……";
		mes "私の負けね。";
		mes "でも逆にいえば、";
		mes "あなた程の実力の持ち主が";
		mes "居たことは、嬉しいわ。";
		next;
		mes "[フェンリル]";
		mes "次に会うときは必ず";
		mes "勝ってみせるわ。";
		mes "それじゃあまた、戦えるのを";
		mes "楽しみにしてるわよ。";
		set '@item,0;
	}
	else if(checkquest(9309)) {
		cutin "fenrir_a.bmp", 2;
		mes "[フェンリル]";
		mes "試合の結果と、あなたの";
		mes "試合内容についてロキから";
		mes "さっき話を聞いたわ。";
		mes "結果は残念だったけど";
		mes "とりあえず今は、";
		mes "休息するべきよ。";
		next;
		mes "[フェンリル]";
		mes "そして、同じ魔法大会に";
		mes "参加した選手として";
		mes "全力を尽くしたあなたに";
		mes "私からも、ささやかだけど";
		mes "贈り物を贈るわ。";
		mes "これからもがんばってね。";
		set '@item,rand(1,7);
	}
	switch('@item) {
	case 0: break;
	case 1: getitem 501, 1; break;
	case 2: getitem 502, 1; break;
	case 3: getitem 503, 1; break;
	case 4: getitem 504, 1; break;
	case 5: getitem 505, 1; break;
	case 6: getitem 607, 1; break;
	case 7: getitem 608, 1; break;
	}
	setquest 9313;
	compquest 9313;
	close2;
	cutin "fenrir_a.bmp", 255;
	end;
}

//==========================================
// 悪事を企む輩：ビリー・コスルリース
//------------------------------------------
1@gef.gat,166,168,0	script	#イベント1開始	139,9,9,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	hideonnpc getmdnpcname("#イベント2開始");
	hideonnpc getmdnpcname("#イベント3開始");
	hideoffnpc getmdnpcname("ゲフェン不良#1");
	hideoffnpc getmdnpcname("ビリー・コスルリース#2");
	hideoffnpc getmdnpcname("ゲフェン不良#3");
	hideoffnpc getmdnpcname("カプラの女性#1");
	setquest 9284;
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#2")),"ビリー・コスルリース : おれたちは、脚線美命同好会のものだ。ちょっとあんたに聞きたい。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#1")),"ゲフェン不良 : なんでもっと脚線美を強調した服じゃないんだ！　おれたちの楽しみがないだろうが！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("カプラの女性#1")),"カプラの女性 : え……な、なんですかいきなり……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#3")),"ゲフェン不良 : ……エロ可愛い……正義……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("カプラの女性#1")),"カプラの女性 : そ、そういわれても、これが制服で……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#2")),"ビリー・コスルリース : おいおい、制服だからこそだろーが！　わかってないねぇ。";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ゲフェン不良#1");
	hideonnpc getmdnpcname("ビリー・コスルリース#2");
	hideonnpc getmdnpcname("ゲフェン不良#3");
	hideoffnpc getmdnpcname("ゲフェン不良#11");
	hideoffnpc getmdnpcname("ビリー・コスルリース#22");
	hideoffnpc getmdnpcname("ゲフェン不良#33");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#11")),"ゲフェン不良 : しょうがねえな、そのあたりをじっくり教えてやるよ。";
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#22")),"ビリー・コスルリース : 人気がない場所でな！　ぐふふ……。";
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#33")),"ゲフェン不良 : ……制服……脚線美……偉大……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("カプラの女性#1")),"カプラの女性 : ど、どなたか……助けていただけませんか!?";
	if(!sleep2(2000)) end;
	hideoffnpc getmdnpcname("#イベント1開始2");
	end;
}

1@gef.gat,166,169,0	script	#イベント1開始2	139,4,4,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	unittalk getcharid(3),strcharinfo(0)+ " : やめろ！",1;
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#11")),"ゲフェン不良 : なんだお前。まさか、うなじLOVE一派のヤツか!?";
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#22")),"ビリー・コスルリース : おれたちは今、このカプラさんと交渉中なんだぜ？";
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#33")),"ゲフェン不良 : ……おれ……どっちかというと……アークビショップ……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("カプラの女性#1")),"カプラの女性 : ああ、助けてください！";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : 今、助けます！",1;
	hideonnpc getmdnpcname("ゲフェン不良#11");
	hideonnpc getmdnpcname("ビリー・コスルリース#22");
	hideonnpc getmdnpcname("ゲフェン不良#33");
	misceffect 60,"";
	monster getmdmapname("1@gef.gat"),167,169,"ビリー・コスルリース",2568,1,getmdnpcname("カプラの女性#1")+"::OnKilled";
	monster getmdmapname("1@gef.gat"),168,170,"怒ったゲフェン不良",2568,1,getmdnpcname("カプラの女性#1")+"::OnKilled";
	monster getmdmapname("1@gef.gat"),166,168,"怒ったゲフェン不良",2568,1,getmdnpcname("カプラの女性#1")+"::OnKilled";
	end;
}

1@gef.gat,169,167,2	script	カプラの女性#1	114,{
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@gef.gat"),getmdnpcname("カプラの女性#1")+ "::OnKilled");
	if('count <= 0) {
		hideoffnpc getmdnpcname("ゲフェン不良#1");
		hideoffnpc getmdnpcname("ビリー・コスルリース#2");
		hideoffnpc getmdnpcname("ゲフェン不良#3");
		hideoffnpc getmdnpcname("#イベント番外1");
	}
	end;
}

1@gef.gat,166,167,0	script	#イベント番外1	139,5,5,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	delquest 9284;
	setquest 9285;
	misceffect 220,getmdnpcname("ゲフェン不良#1");
	misceffect 220,getmdnpcname("ビリー・コスルリース#2");
	misceffect 220,getmdnpcname("ゲフェン不良#3");
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#1")),"ゲフェン不良: こっちも、脚線美パワーで、本気を出させてもらうか！";
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#2")),"ビリー・コスルリース: 少しは腕に覚えがあるみたいだな……。";
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#3")),"ゲフェン不良: ……おれたち……おまえ……ふるぼっこ……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("カプラの女性#1")),"カプラの女性: 巻き込んで、すいません……。でもまだ、あの方たちあきらめてないようです……。";
	if(!sleep2(4000)) end;
	unittalk getnpcid(0,getmdnpcname("アイリス#1")),"アイリス: ちょおっと待った！";
	if(!sleep2(2000)) end;
	hideoffnpc getmdnpcname("アイリス#1");
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("アイリス#1")),"アイリス: それくらいにしておきなさいよ！";
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("アイリス#1")),"アイリス: でないとこの私、アイリスが許さないわよ！";
	misceffect 204,getmdnpcname("アイリス#1");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#1")),"ゲフェン不良: あんた、いい脚線美じゃねえか、おれ達を踏んでくれよ～。";
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#2")),"ビリー・コスルリース: おっ、いい脚線美の女が来たぜ。";
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#3")),"ゲフェン不良: ……蹴って……。";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ゲフェン不良#1");
	hideonnpc getmdnpcname("ビリー・コスルリース#2");
	hideonnpc getmdnpcname("ゲフェン不良#3");
	hideoffnpc getmdnpcname("ゲフェン不良#11");
	hideoffnpc getmdnpcname("ビリー・コスルリース#22");
	hideoffnpc getmdnpcname("ゲフェン不良#33");
	if(!sleep2(3000)) end;
	mapannounce getmdmapname("1@gef.gat"),"その薄汚い手を引っ込めな！", 0x9, 0x00ebff;
	if(!sleep2(2000)) end;
	hideoffnpc getmdnpcname("ケイオス#1");
	if(!sleep2(2000)) end;
	misceffect 218,getmdnpcname("ケイオス#1");
	unittalk getnpcid(0,getmdnpcname("ケイオス#1")),"ケイオス : アイリスに手を出すとはな！　そんなにお約束な展開が希望なのか。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ケイオス#1")),"ケイオス : 最初に断っておくが、手加減はしねーぞ？";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ケイオス#1");
	hideoffnpc getmdnpcname("ケイオス#2");
	misceffect 60,getmdnpcname("ゲフェン不良#11");
	misceffect 60,getmdnpcname("ビリー・コスルリース#22");
	misceffect 60,getmdnpcname("ゲフェン不良#33");
	unittalk getnpcid(0,getmdnpcname("ケイオス#2")),"ケイオス : ま、安心しな！　命まで奪ったりしないからよ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ケイオス#2")),"ケイオス : くらえッ!!";
	misceffect 16,getmdnpcname("ゲフェン不良#11");
	misceffect 16,getmdnpcname("ビリー・コスルリース#22");
	misceffect 16,getmdnpcname("ゲフェン不良#33");
	hideonnpc getmdnpcname("ゲフェン不良#11");
	hideonnpc getmdnpcname("ビリー・コスルリース#22");
	hideonnpc getmdnpcname("ゲフェン不良#33");
	hideoffnpc getmdnpcname("ゲフェン不良#1");
	hideoffnpc getmdnpcname("ビリー・コスルリース#2");
	hideoffnpc getmdnpcname("ゲフェン不良#3");
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#1")),"ゲフェン不良 : 脚線美命同好会のメンツにかけて引き下がるわけには……！";
	unittalk getnpcid(0,getmdnpcname("ビリー・コスルリース#2")),"ビリー・コスルリース : うげ!?";
	unittalk getnpcid(0,getmdnpcname("ゲフェン不良#3")),"ゲフェン不良 : ……女の子にも……蹴られたこと……ない……のに……。";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ケイオス#2");
	hideoffnpc getmdnpcname("ケイオス#3");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ケイオス#3")),"ケイオス : まだ元気みたいだな！　マグナムブレイク！";
	misceffect 17,getmdnpcname("ゲフェン不良#1");
	misceffect 17,getmdnpcname("ビリー・コスルリース#2");
	misceffect 17,getmdnpcname("ゲフェン不良#3");
	if(!sleep2(1000)) end;
	misceffect 183,getmdnpcname("ゲフェン不良#1");
	misceffect 183,getmdnpcname("ビリー・コスルリース#2");
	misceffect 183,getmdnpcname("ゲフェン不良#3");
	hideonnpc getmdnpcname("ゲフェン不良#1");
	hideonnpc getmdnpcname("ビリー・コスルリース#2");
	hideonnpc getmdnpcname("ゲフェン不良#3");
	if(!sleep2(2000)) end;
	hideonnpc getmdnpcname("ケイオス#3");
	hideoffnpc getmdnpcname("ケイオス#1");
	if(!sleep2(3000)) end;
	mes "[アイリス]";
	mes "大丈夫？";
	mes "本当、ああいう輩はどこにでも";
	mes "いるんだよね。";
	mes "まったく……。";
	cutin "hero_iris_01.bmp", 2;
	next;
	mes "[カプラ]";
	mes "助けていただいて";
	mes "ありがとうございます。";
	mes "えっと……お名前は……。";
	cutin "hero_iris_02.bmp", 255;
	next;
	mes "[アイリス]";
	mes "私は、アイリス。";
	mes "こっちはケイオス。";
	mes "ケイオスと一緒に冒険してるんだよ。";
	cutin "hero_iris_02.bmp", 2;
	next;
	mes "[アイリス]";
	mes "でも私よりあの人が";
	mes "先に駆けつけてなかったら";
	mes "私もケイオスも間に合わなかったかも。";
	mes "お礼は先ず、あの人に";
	mes "いってあげてね。";
	next;
	mes "[カプラ]";
	mes "あ、そうですね。";
	mes "私ってば、気が動転して……。";
	mes "失礼いたしました。";
	mes "お名前を教えていただけますか。";
	cutin "hero_iris_02.bmp", 255;
	next;
	menu "名乗る",-;
	mes "[カプラ]";
	mes strcharinfo(0)+ "様";
	mes "ありがとうございます。";
	mes "おかげさまで無事でした。";
	mes "本当にありがとうございます。";
	next;
	mes "[アイリス]";
	mes "こんな時代だから";
	mes strcharinfo(0)+ "みたいな正義の味方は";
	mes "そうそういないし、";
	mes "こういう出会いは";
	mes "大事にしないとね！";
	cutin "hero_iris_02.bmp", 2;
	next;
	mes "[アイリス]";
	mes "そういえば……";
	mes "私とケイオスはゲフェン魔法大会に";
	mes "一緒に旅してる仲間が諸事情で";
	mes "出場するから応援に来たけど";
	mes strcharinfo(0)+ "も、その装備から察するに";
	mes "魔法大会に出場するみたいだね！";
	next;
	mes "[ケイオス]";
	mes "へえ……そうか。";
	cutin "hero_iris_01.bmp", 255;
	cutin "hero_chaos_01.bmp", 2;
	next;
	mes "[ケイオス]";
	mes "さっきの" +strcharinfo(0)+ "の";
	mes "実力もなかなかだったと思うが……";
	mes "魔法大会にはフェンリルが";
	mes "参加しているから";
	mes "簡単に勝てないだろう。";
	next;
	mes "[ケイオス]";
	mes "俺はあんたみたいな奴、嫌いじゃない。";
	mes "魔法大会でもいい試合みせてくれよ。";
	mes "だから応援って意味で";
	mes "俺が特別に気合入れてやるよ！";
	//sc_start3 EFST_GEFFEN_MAGIC3,1,0,0,0,3600000,1;
	misceffect 220,"";
	next;
	mes "[ケイオス]";
	mes "これで相手から受けるダメージを";
	mes "軽減できるはずだ！";
	mes "魔法大会で役に立つと思うぜ。";
	mes "それじゃ……アイリス！";
	mes "俺たちは魔法大会の様子でも";
	mes "見にいくとするか！　もう始まるぜ！";
	next;
	mes "[アイリス]";
	mes "そうだね、行こうか！";
	mes "そうそう。" +strcharinfo(0)+ "。";
	mes "魔法大会でいい成績がとれるよう";
	mes "応援してるから、頑張ってね！";
	cutin "hero_chaos_01.bmp", 255;
	cutin "hero_iris_02.bmp", 2;
	close2;
	cutin "hero_iris_02.bmp", 255;
	hideonnpc getmdnpcname("アイリス#1");
	hideonnpc getmdnpcname("ケイオス#1");
	hideonnpc getmdnpcname("カプラの女性#1");
	cutin "nov_magicsoul01.bmp", 255;
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : どこか不思議な感じの人たちだった。",1;
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : 忘れないうちに魔法大会の参加申し込みをしよう。",1;
}

1@gef.gat,159,172,6	script	ゲフェン不良#1	682,{}
1@gef.gat,160,176,6	script	ビリー・コスルリース#2	682,{}
1@gef.gat,164,175,6	script	ゲフェン不良#3	682,{}
1@gef.gat,166,168,6	script	ゲフェン不良#11	682,{}
1@gef.gat,167,169,6	script	ビリー・コスルリース#22	682,{}
1@gef.gat,168,170,6	script	ゲフェン不良#33	682,{}
1@gef.gat,173,167,4	script	ケイオス#1	683,{}
1@gef.gat,168,168,4	script	ケイオス#2	683,{}
1@gef.gat,162,174,4	script	ケイオス#3	683,{}
1@gef.gat,170,168,4	script	アイリス#1	666,{}

//==========================================
// 悪事を企む輩：ヒピア・スニキ
//------------------------------------------
1@gef.gat,72,169,0	script	#イベント2開始	139,9,9,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	hideonnpc getmdnpcname("#イベント1開始");
	hideonnpc getmdnpcname("#イベント3開始");
	hideoffnpc getmdnpcname("ヒピア・スニキ#1");
	hideoffnpc getmdnpcname("ゲフェンごろつき#2");
	hideoffnpc getmdnpcname("ゲフェンごろつき#3");
	hideoffnpc getmdnpcname("魔法アカデミー学生#1");
	setquest 9286;
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : おい、そこの学生。";
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#1")),"魔法アカデミー学生 : あ、はい。私にご用でしょうか。";
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : オメー以外誰がいるんだよ！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : とっとと走って来いよ、3秒やる。";
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : 3……";
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : 2……";
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : ……よし、来たな。";
	hideonnpc getmdnpcname("魔法アカデミー学生#1");
	hideoffnpc getmdnpcname("魔法アカデミー学生#2");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : おい、お前のヤロー友達を紹介しな！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#2")),"魔法アカデミー学生 : え？　え？　ヤロー？　お、男友達のことですか……？";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : おう、そうだ！　俺たちの兄貴組にスカウトするから紹介しろ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#2")),"魔法アカデミー学生 : あの……私、男の子の友達はいません……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : ……あん？　クラスメイトとか居るだろうが。";
	if(!sleep2(5000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#2")),"魔法アカデミー学生 : ク、クラスメイトの男の子もそんなに仲は……。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : べつに仲良くなくてもいいんだぜ。なっ、簡単だろう！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : 俺らに紹介するだけでいいんだぜ～。";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : ほらほら～、一人くらいいるだろ？　さっさと紹介しろ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#2")),"魔法アカデミー学生 : 無理です！　だ、誰か……助けて！";
	if(!sleep2(2000)) end;
	hideoffnpc getmdnpcname("#イベント2開始2");
	end;
}

1@gef.gat,72,170,0	script	#イベント2開始2	139,3,3,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	unittalk getcharid(3),strcharinfo(0)+ " : ちょっと待て！",1;
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : おっと、なんだ？　オメーは。";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : オメーがこいつのかわりにヤローを紹介してくれるのかよ？";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : いっとくが、兄貴組に入るのは簡単じゃねーからな！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#2")),"魔法アカデミー学生 : た、助けてください!!";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : うら若き学生さんをいじめるとは……！",1;
	hideonnpc getmdnpcname("ヒピア・スニキ#1");
	hideonnpc getmdnpcname("ゲフェンごろつき#2");
	hideonnpc getmdnpcname("ゲフェンごろつき#3");
	misceffect 60,"";
	monster getmdmapname("1@gef.gat"),75,172,"ヒピア・スニキ",2567,1,getmdnpcname("魔法アカデミー学生#2")+"::OnKilled";
	monster getmdmapname("1@gef.gat"),76,170,"ゲフェンごろつき",2567,1,getmdnpcname("魔法アカデミー学生#2")+"::OnKilled";
	monster getmdmapname("1@gef.gat"),73,173,"ゲフェンごろつき",2567,1,getmdnpcname("魔法アカデミー学生#2")+"::OnKilled";
	end;
}

1@gef.gat,73,170,1	script	魔法アカデミー学生#2	123,{
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@gef.gat"),getmdnpcname("魔法アカデミー学生#2")+ "::OnKilled");
	if('count <= 0) {
		hideoffnpc getmdnpcname("ヒピア・スニキ#1");
		hideoffnpc getmdnpcname("ゲフェンごろつき#2");
		hideoffnpc getmdnpcname("ゲフェンごろつき#3");
		hideoffnpc getmdnpcname("#イベント番外2");
	}
	end;
}

1@gef.gat,72,168,0	script	#イベント番外2	139,5,5,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	delquest 9286;
	setquest 9287;
	misceffect 220,getmdnpcname("ヒピア・スニキ#1");
	misceffect 220,getmdnpcname("ゲフェンごろつき#2");
	misceffect 220,getmdnpcname("ゲフェンごろつき#3");
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : けっ、意外とすばしっこいやつだな！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : これだから女は好かねぇ！　おとなしくしろ！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : そういうわけだ！　おとなしくついてくるんだな！";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("魔法アカデミー学生#2");
	hideoffnpc getmdnpcname("魔法アカデミー学生#1");
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("魔法アカデミー学生#1")),"魔法アカデミー学生 : きゃあああっ！　助けてください！";
	if(!sleep2(1000)) end;
	hideoffnpc getmdnpcname("フェンリル#1");
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("フェンリル#1")),"フェンリル : お待ちなさい！　それ以上の乱暴は見過ごせないわね。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("フェンリル#1")),"フェンリル : まったく……。お祭りだからって、羽目をはずしすぎよ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("フェンリル#1")),"フェンリル : やめないなら私も黙ってはいないわよ。";
	misceffect 204,getmdnpcname("フェンリル#1");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : なんだ、この女……？";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : 俺たちは今、こいつと話してるんだぜ？";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : それとも、あんたがこいつにかわって有望なヤローを紹介してくれるのか？";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ヒピア・スニキ#1");
	hideonnpc getmdnpcname("ゲフェンごろつき#2");
	hideonnpc getmdnpcname("ゲフェンごろつき#3");
	hideoffnpc getmdnpcname("ヒピア・スニキ#11");
	hideoffnpc getmdnpcname("ゲフェンごろつき#22");
	hideoffnpc getmdnpcname("ゲフェンごろつき#33");
	if(!sleep2(3000)) end;
	mapannounce getmdmapname("1@gef.gat"),"そこまでだ。", 0x9, 0x00ebff;
	if(!sleep2(3000)) end;
	hideoffnpc getmdnpcname("ロキ#1");
	if(!sleep2(1000)) end;
	misceffect 126,getmdnpcname("ロキ#1");
	if(!sleep2(1000)) end;
	misceffect 121,getmdnpcname("ロキ#1");
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#1")),"ロキ : お前らのその耳に障る笑い声。";
	if(!sleep2(1000)) end;
	misceffect 124,getmdnpcname("ロキ#1");
	if(!sleep2(1000)) end;
	misceffect 122,getmdnpcname("ゲフェンごろつき#33");
	misceffect 143,getmdnpcname("ゲフェンごろつき#33");
	misceffect 32,getmdnpcname("ゲフェンごろつき#33");
	hideonnpc getmdnpcname("ゲフェンごろつき#33");
	hideoffnpc getmdnpcname("ゲフェンごろつき#3");
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : ぐへ！";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ロキ#1");
	hideoffnpc getmdnpcname("ロキ#2");
	unittalk getnpcid(0,getmdnpcname("ロキ#2")),"ロキ : 薄汚れた言葉使い。";
	misceffect 271,getmdnpcname("ヒピア・スニキ#11");
	misceffect 122,getmdnpcname("ヒピア・スニキ#11");
	misceffect 143,getmdnpcname("ヒピア・スニキ#11");
	misceffect 32,getmdnpcname("ヒピア・スニキ#11");
	hideonnpc getmdnpcname("ヒピア・スニキ#11");
	hideoffnpc getmdnpcname("ヒピア・スニキ#1");
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : ぐぎゃあああ！";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ロキ#2");
	hideoffnpc getmdnpcname("ロキ#3");
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : ゴミ以下の行動。";
	misceffect 270,getmdnpcname("ゲフェンごろつき#22");
	misceffect 122,getmdnpcname("ゲフェンごろつき#22");
	misceffect 143,getmdnpcname("ゲフェンごろつき#22");
	misceffect 32,getmdnpcname("ゲフェンごろつき#22");
	hideonnpc getmdnpcname("ゲフェンごろつき#22");
	hideoffnpc getmdnpcname("ゲフェンごろつき#2");
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : うぎゃ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : これ以上、俺を怒らせたくなければ";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : 今すぐに消え失せろ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : ひ……ひいい!!";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : お、おい！　逃げるぞ！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : な、なんだよ……こいつ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : 10秒待ってやる。";
	misceffect 121,getmdnpcname("ロキ#3");
	misceffect 136,getmdnpcname("ロキ#3");
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : 10……9……";
	misceffect 269,getmdnpcname("ロキ#3");
	misceffect 126,getmdnpcname("ロキ#3");
	misceffect 127,getmdnpcname("ロキ#3");
	misceffect 125,getmdnpcname("ロキ#3");
	if(!sleep2(1000)) end;
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : 3……2……";
	unittalk getnpcid(0,getmdnpcname("ヒピア・スニキ#1")),"ヒピア・スニキ : ちょ、ちょっと待て！　何で9秒から3秒に！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#2")),"ゲフェンごろつき : とりあえず逃げるぞ！";
	unittalk getnpcid(0,getmdnpcname("ゲフェンごろつき#3")),"ゲフェンごろつき : くそ！　おぼえてろよ！";
	if(!sleep2(3000)) end;
	misceffect 104,getmdnpcname("ロキ#3");
	misceffect 124,getmdnpcname("ロキ#3");
	unittalk getnpcid(0,getmdnpcname("ロキ#3")),"ロキ : 1……";
	hideonnpc getmdnpcname("ヒピア・スニキ#1");
	hideonnpc getmdnpcname("ゲフェンごろつき#2");
	hideonnpc getmdnpcname("ゲフェンごろつき#3");
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ロキ#3");
	hideoffnpc getmdnpcname("ロキ#1");
	if(!sleep2(3000)) end;
	mes "[フェンリル]";
	mes "怪我はない？";
	mes "まったく……。";
	mes "ああいう輩はどこにでもいるわね。";
	cutin "fenrir_b.bmp", 2;
	next;
	mes "[魔法アカデミー学生]";
	mes "助けていただいて";
	mes "ありがとうございます。";
	mes "ところで……お名前は……。";
	cutin "fenrir_b.bmp", 255;
	next;
	mes "[フェンリル]";
	mes "私はフェンリル……";
	mes "フェンリス・フェンリル。";
	mes "こっちの彼は、ロキよ。";
	cutin "fenrir_a.bmp", 2;
	next;
	mes "[フェンリル]";
	mes "でも私たちより……";
	mes "あちらの方に、感謝してね。";
	mes "あの人が先に助けに入らなければ";
	mes "危ないところだったし。";
	next;
	menu "名乗る",-;
	mes "[魔法アカデミー学生]";
	mes strcharinfo(0)+ "様";
	mes "ありがとうございます。";
	mes "おかげさまで助かりました。";
	mes "本当にありがとうございます。";
	cutin "fenrir_a.bmp", 255;
	next;
	mes "[フェンリル]";
	mes "今のご時勢、" +strcharinfo(0)+ "のように";
	mes "人助けは、なかなかできないわ。";
	mes "あなたは誰よりも";
	mes "勇気があるみたいね。";
	cutin "fenrir_a.bmp", 2;
	next;
	mes "[フェンリル]";
	mes "私はゲフェン魔法大会の";
	mes "選手として登録しに";
	mes "向かう途中だったのよ。";
	mes "ロキは目立つのは嫌いなのと";
	mes "どのような大会なのか";
	mes "見物だけでいいって聞かなくて。";
	next;
	mes "[フェンリル]";
	mes "どうやら" +strcharinfo(0)+ "も";
	mes "魔法大会に参加するみたいね。";
	mes "さっきのあなたの身のこなしや";
	mes "装備の様子をみていれば";
	mes "魔法大会参加者なら";
	mes "すぐに気づくはずよ。";
	next;
	mes "[ロキ]";
	mes "へえ。";
	mes "お前もあの、魔法大会に参加するのか。";
	mes "なら、今からお前に手向けとして";
	mes "俺が戦闘のときに使用している";
	mes "スクロールを使ってやろう。";
	cutin "fenrir_a.bmp", 255;
	cutin "ep14_roki01.bmp", 2;
	next;
	mes "[ロキ]";
	mes "このスクロールの効果は、";
	mes "お前の魔法ダメージを上昇させる";
	mes "効果がある。";
	mes "そのかわりお前は、";
	mes "決勝まで勝ちあがってこい。";
	//sc_start3 SC_GEFFEN_MAGIC2,1,0,0,0,3600000,1;
	misceffect 220,"";
	next;
	mes "[ロキ]";
	mes "さっきのお前の行動を見ていて";
	mes "少し、フェンリルとお前の戦いを";
	mes "見てみたくなったんでな。";
	mes "お陰で多少は退屈せずに";
	mes "すみそうだ。";
	next;
	mes "[ロキ]";
	mes "……フェンリル。";
	mes "そろそろ時間だ。";
	mes "行くぞ。";
	next;
	mes "[フェンリル]";
	mes "わかったわ、ロキ。";
	mes "魔法アカデミーの学生さん。";
	mes "また機会があったら";
	mes "会いましょう。";
	cutin "ep14_roki01.bmp", 255;
	cutin "fenrir_a.bmp", 2;
	next;
	mes "[フェンリル]";
	mes strcharinfo(0)+ "とは";
	mes "魔法大会の決勝で会えることを";
	mes "楽しみにしているわね。";
	close2;
	cutin "fenrir_a.bmp", 255;
	hideonnpc getmdnpcname("フェンリル#1");
	hideonnpc getmdnpcname("ロキ#1");
	hideonnpc getmdnpcname("魔法アカデミー学生#1");
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : 何か不思議な感じの人たちだった……特にフェンリル。",1;
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+ " : それはそうと魔法大会の申し込みに行こう。",1;
	end;
}

1@gef.gat,70,167,1	script	魔法アカデミー学生#1	123,{}
1@gef.gat,75,172,4	script	ヒピア・スニキ#1	681,{}
1@gef.gat,76,170,4	script	ゲフェンごろつき#2	681,{}
1@gef.gat,73,173,4	script	ゲフェンごろつき#3	681,{}
1@gef.gat,70,171,4	script	ヒピア・スニキ#11	681,{}
1@gef.gat,68,171,4	script	ゲフェンごろつき#22	681,{}
1@gef.gat,70,169,4	script	ゲフェンごろつき#33	681,{}
1@gef.gat,68,169,8	script	フェンリル#1	664,{}
1@gef.gat,69,168,8	script	ロキ#1	512,{}
1@gef.gat,69,170,8	script	ロキ#2	512,{}
1@gef.gat,67,170,8	script	ロキ#3	512,{}

//==========================================
// 悪事を企む輩：ブラック・カネイリー
//------------------------------------------
1@gef.gat,114,143,0	script	#イベント3開始	139,2,2,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	hideonnpc getmdnpcname("#イベント1開始");
	hideonnpc getmdnpcname("#イベント2開始");
	viewpoint 2, 1, 1, 1, 0xFFFFFF;
	viewpoint 2, 1, 1, 2, 0xFFFFFF;
	viewpoint 2, 1, 1, 3, 0xFFFFFF;
	hideoffnpc getmdnpcname("ゲフェン住民#1");
	setquest 9288;
	if(!sleep2(2000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン住民#1")),"ゲフェン住民 : ど……ど……泥棒!!";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン住民#1")),"ゲフェン住民 : 僕のお小遣いだぞ！　返して～!!";
	if(!sleep2(4000)) end;
	hideoffnpc getmdnpcname("ブラック・カネイリー#1");
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : あちゃー……ばれちゃった。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン住民#1")),"ゲフェン住民 : 誰か！　あの泥棒を捕まえて！　僕のお小遣いが!!";
	if(!sleep2(3000)) end;
	hideoffnpc getmdnpcname("#イベント3開始2");
	end;
}

1@gef.gat,109,141,0	script	#イベント3開始2	139,5,5,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	unittalk getcharid(3),strcharinfo(0)+" : 盗んだZenyを返せ！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : あら～正義の味方登場？　怖いから逃げちゃお～！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : あたしはこれで！　じゃあね！";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ゲフェン住民#1")),"ゲフェン住民 : 僕のお小遣い、取り返してっ！";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : 捕まえて衛兵に渡してやる！";
	hideonnpc getmdnpcname("ブラック・カネイリー#1");
	hideoffnpc getmdnpcname("ブラック・カネイリー#2");
	end;
}

1@gef.gat,107,126,4	script	ブラック・カネイリー#2	671,3,3,{
	end;
OnTouch:
	if(Zeny >= 10000) {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#2")),"ブラック・カネイリー : 意外とやるじゃない！　その意気に免じて、盗むZenyの額を1Zenyだけおまけしてあげるわ！";
		misceffect 18,"";
		set Zeny, Zeny-99;
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : 待て！　盗んでおいて、おまけってどういうことだ！";
	} else {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#2")),"ブラック・カネイリー : なによ!?　Zenyがないやつに用はないわよ!?　これでもくらいなさい！";
		misceffect 18,"";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : !?　こ、これは……って、おもちゃのZenyをばらまくな！　自分のZenyかと思って慌てたぞ！";
	}
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#2");
	hideoffnpc getmdnpcname("ブラック・カネイリー#3");
	end;
}

1@gef.gat,111,118,4	script	ブラック・カネイリー#3	671,3,3,{
	end;
OnTouch:
	if(Zeny >= 10000) {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#3")),"ブラック・カネイリー : ふふ！　追いつけるかしら？　じゃあ、あたしはお先～！";
		misceffect 18,"";
		set Zeny, Zeny-100;
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : 捕まえたら覚悟しておけ!?";
	} else {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#3")),"ブラック・カネイリー : 誰が捕まるもんですか！　盗まれるZenyもないくせに！";
		misceffect 18,"";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : ちょ、ちょっと今は手持ちがないだけだ！";
	}
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#3");
	hideoffnpc getmdnpcname("ブラック・カネイリー#11");
	end;
}

1@gef.gat,123,111,4	script	ブラック・カネイリー#11	671,3,3,{
	end;
OnTouch:
	if(Zeny >= 10000) {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#11")),"ブラック・カネイリー : 意外とやるじゃない！　そのがんばりに免じて、また盗んであげる！";
		misceffect 18,"";
		set Zeny, Zeny-100;
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : 盗蟲みたいにちょこまかと……！　待て！";
	} else {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#11")),"ブラック・カネイリー : 意外とがんばるのね！　そのがんばりに、おもちゃのZenyあげるわ♪　使ってよね。";
		misceffect 18,"";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : だから、そんなものもらっても困る！　まったく、盗蟲みたいにちょこまかと……！　待て！";
	}
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#11");
	hideoffnpc getmdnpcname("ブラック・カネイリー#22");
	end;
}

1@gef.gat,129,121,4	script	ブラック・カネイリー#22	671,3,3,{
	end;
OnTouch:
	if(Zeny >= 10000) {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#22")),"ブラック・カネイリー : と……盗蟲！　一番嫌いなモンスターなのに！　慰謝料のZenyもらうわよ！";
		misceffect 18,"";
		set Zeny, Zeny-150;
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : そ……それは申し訳な……って、慰謝料っておかしいだろう！";
	} else {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#22")),"ブラック・カネイリー : と……盗蟲！　一番嫌いなモンスターなのよ！　お仕置きに、Zenyを盗まれた気分にしてやる！";
		misceffect 18,"";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : そ……それは申し訳な……って、や、やめろー!?";
	}
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#22");
	hideoffnpc getmdnpcname("ブラック・カネイリー#33");
	end;
}

1@gef.gat,114,137,4	script	ブラック・カネイリー#33	671,3,3,{
	end;
OnTouch:
	if(Zeny >= 10000) {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#33")),"ブラック・カネイリー : 本当にしつこいわね！　あたし、そんなに体力ないんだから！";
		misceffect 18,"";
		set Zeny, Zeny-100;
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : もう逃げ道はない！　捕まえた！";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#33")),"ブラック・カネイリー : ……仕方ない。あんまり戦いたくないんだけど、あたしも捕まるわけにいかないのよ！";
	} else {
		unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#33")),"ブラック・カネイリー : ……Zenyがないあんたと、あんまり戦いたくないんだけど……捕まるわけにはいかないし、仕方ないわね……。";
		misceffect 18,"";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : さっきからZenyがないないって言ってるが……宵越しのZenyは持たないだけだ！";
		if(!sleep2(3000)) end;
		unittalk getcharid(3),strcharinfo(0)+" : でもZenyがないのは事実だから、事実を突きつけられると悲しくなるんだよ！ ";
	}
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#33");
	monster getmdmapname("1@gef.gat"),114,137,"ブラック・カネイリー",2914,1,getmdnpcname("ゲフェン住民#1")+"::OnKilled";
	end;
}

1@gef.gat,111,146,4	script	ゲフェン住民#1	67,{
	end;
OnKilled:
	hideoffnpc getmdnpcname("ブラック・カネイリー#1");
	hideoffnpc getmdnpcname("#イベント番外3");
	end;
}

1@gef.gat,110,140,0	script	#イベント番外3	139,5,5,{
	end;
OnTouch:
	set '@dummy,attachrid(getcharid(3));
	hideonnpc;
	delquest 9288;
	setquest 9289;
	misceffect 20,getmdnpcname("ブラック・カネイリー#1");
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : も～……。少しは手加減しなさいよね！";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : さあて、そろそろお仕置きの時間だ。";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : お仕置きより、1Zenyでも多く貰えるほうが嬉しいし、まだ捕まるわけにいかないのよ。";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : なにっ!?";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : ふふ！　追いかけっこ、割と楽しかったわよ！　じゃあね！";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : こらー！　盗んだZeny返せ!!";
	if(!sleep2(3000)) end;
	unittalk getnpcid(0,getmdnpcname("ブラック・カネイリー#1")),"ブラック・カネイリー : あはは！　泥棒に返せって、無理な話よ！　バイバーイ!!";
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ブラック・カネイリー#1");
	if(!sleep2(3000)) end;
	hideonnpc getmdnpcname("ゲフェン住民#1");
	hideoffnpc getmdnpcname("ゲフェン住民#3");
	mes "[ゲフェン住民]";
	mes "ううう……僕のお小遣いが……";
	mes "こんなことって……。";
	mes "せっかく、お父上にもらったのに……";
	mes "ぐすっ……。";
	next;
	mes "[ゲフェン住民]";
	mes strcharinfo(0)+"様も";
	mes "僕のためにあの泥棒を";
	mes "追いかけてくれたのに、結果的に";
	mes "巻き込む形になってしまい";
	mes "本当に、ごめんなさい……。";
	next;
	mes "[ゲフェン住民]";
	mes "今日はなにも買ったり";
	mes "食べたりせずに";
	mes "すごすことになりそうです……。";
	mes "はあ……。";
	mes "すごく楽しみだったのに。";
	mes "うう……。";
	next;
	hideoffnpc getmdnpcname("リディア#1");
	mes "[リディア]";
	mes "ひゃっほーい！　今日はいい感じ！";
	mes "ゲフェンの泥棒って";
	mes "みんなお金持ちなのかな？";
	mes "ま、どうでもいいけどね!!";
	mes "……って。";
	cutin "lydia_a.bmp", 2;
	next;
	mes "[リディア]";
	mes "ん？　あんたたち";
	mes "なんで泣いてるの？";
	mes "何かあったの？";
	next;
	mes "‐これまでの事情を話した‐";
	cutin "lydia_a.bmp", 255;
	next;
	mes "[ゲフェン住民]";
	mes "こんなことならすぐに";
	mes "友人と合流しておけば";
	mes "良かったです……。";
	mes "つい、雰囲気に浮かれて";
	mes "ぼーっとしてました。";
	next;
	mes "[リディア]";
	mes "(さっき、うさ耳をかぶった女が";
	mes "似合わない財布を持っているのを";
	mes "見かけたから、中身がきになって";
	mes "盗んだんだけど……。";
	mes "どう考えてもこの財布が";
	mes "この子の盗まれた財布だよね。)";
	cutin "lydia_a.bmp", 2;
	next;
	mes "[リディア]";
	mes "……ねえ。";
	mes "少し聞きたいんだけどさ。";
	mes "その盗まれた財布には";
	mes "いくら入っていたの？";
	next;
	mes "[ゲフェン住民]";
	mes "100000Zenyです……。";
	cutin "lydia_a.bmp", 255;
	next;
	mes "[ゲフェン住民]";
	mes "友人と魔法大会をみようって";
	mes "話になったのですが……。";
	mes "うちのお父上は厳しい方で";
	mes "テストで一定の成績をとったら";
	mes "外出していいっていわれ……";
	next;
	mes "[ゲフェン住民]";
	mes "必死に勉強をがんばって、";
	mes "やっと外出許可がもらえたんです。";
	mes "そしたら家を出る際に";
	mes "お父上がその財布を渡して";
	mes "これで好きに遊んでこいって……。";
	cutin "lydia_a.bmp", 255;
	next;
	mes "[リディア]";
	mes "（財布の中身は……";
	mes "げっ、100000Zenyきっかり。";
	mes "金額も一致してるし、聞いた";
	mes "財布の特徴も同じだし";
	mes "返すべき、だよね……。";
	mes "やっぱり。）";
	cutin "lydia_a.bmp", 2;
	next;
	mes "[リディア]";
	mes "多分、違うと思うんだけど……";
	mes "もしかしてそれって";
	mes "この財布だったり……？";
	next;
	hideonnpc getmdnpcname("ゲフェン住民#3");
	hideoffnpc getmdnpcname("ゲフェン住民#2");
	mes "[ゲフェン住民]";
	mes "えっ……!?";
	mes "このポリンマークの財布……。";
	mes "はい！　これです！　僕のです！";
	mes "金額もちょうど合ってます！";
	mes "取り返してくれたんですね！";
	mes "ありがとうございます！";
	cutin "lydia_a.bmp", 255;
	next;
	mes "[リディア]";
	mes "え……いや、そんな";
	mes "ま、まだ、あんたにこれを";
	mes "返すとは言ってな……。";
	cutin "lydia_a.bmp", 2;
	next;
	mes "[ゲフェン住民]";
	mes "本当にありがとうございます！";
	mes "お二方に助けて頂いた";
	mes "このご恩は忘れません！";
	mes "また盗まれる前に";
	mes "友人と合流しなきゃ！";
	mes "それでは、失礼します！";
	cutin "lydia_a.bmp", 255;
	hideonnpc getmdnpcname("ゲフェン住民#2");
	next;
	mes "[リディア]";
	mes "……";
	mes "だーっ！　もう！　私の馬鹿！";
	mes "って、なによ!?　なんであんたも";
	mes "私のほうをじっと見るのよ！";
	cutin "lydia_a.bmp", 2;
	next;
	mes "‐自分も泥棒の被害に";
	mes "　あったことを話した‐";
	cutin "lydia_a.bmp", 255;
	next;
	mes "[リディア]";
	mes "だから何？　Zeny返せって？";
	mes "ない！　あってもない！";
	mes "私だって遊んでるわけじゃない！";
	mes "ポーション代！　食費！　交通費！";
	mes "ぜーんぶ自分で稼いでるんだから！";
	cutin "lydia_a.bmp", 2;
	next;
	mes "[リディア]";
	mes "ちぇ……今日も結局こうなるのか。";
	mes "さっきのZenyはプロンテラ地下水路に";
	mes "落としたと考えるとして、";
	mes "気を取り直して魔法大会でも";
	mes "見に行こうかな……。";
	mes "はあ……。";
	next;
	mes "[リディア]";
	mes "……そういえば。";
	mes "その装備見て思ったんだけど";
	mes "あんた、魔法大会に";
	mes "参加するつもりなの？";
	next;
	mes "[リディア]";
	mes "そっか……あっ、そういえば。";
	mes "Zenyはないから返せないけど";
	mes "魔法大会に参加するって話しなら、";
	mes "さっき、うさ耳被った泥棒から盗……";
	mes "コホン……。";
	mes "泥棒が落としていったこの……";
	next;
	mes "[リディア]";
	mes "攻撃力の上がる効果の";
	mes "スクロール、使ってあげる。";
	mes "私には必要ないものだし、";
	mes "Zenyになりそうにもないし……。";
	mes "あんたも被害者みたいだし、";
	mes "せめてこのくらいはね。";
	//sc_start3 SC_GEFFEN_MAGIC1,1,0,0,0,3600000,1;
	misceffect 220,"";
	next;
	mes "[リディア]";
	mes "はあ……。";
	mes "今日も収穫なし……っか。";
	mes "とほほほ……。";
	mes "それじゃ私は";
	mes "魔法大会でも見に行くから。";
	mes "じゃね。";
	close2;
	cutin "lydia_a.bmp", 255;
	hideonnpc getmdnpcname("リディア#1");
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ありがとうって言う時間さえくれなかったな。";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : まあ、悪い人じゃないみたいだ。";
	if(!sleep2(3000)) end;
	unittalk getcharid(3),strcharinfo(0)+" : それはそうと魔法大会の申し込みに行こう。";
	end;
}

1@gef.gat,108,139,6	script	ブラック・カネイリー#1	671,{}
1@gef.gat,104,141,6	script	リディア#1	10010,{}
1@gef.gat,106,141,4	script	ゲフェン住民#2	67,{}
1@gef.gat,111,146,4	script	ゲフェン住民#3	67,{}

//==========================================
// 大会参加者
//------------------------------------------
1@gef.gat,145,125,4	script	アルヒ#z1	670,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",1);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"変わった防具の組み合わせだね";
		if('@prog >= 4) set '@str$[3],"その女神の仮面もお気に入りなの";
		if('@prog >= 7) set '@str$[4],"どうしてこの大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[アルヒ]";
			mes "優勝だなんて、すごすぎです……！";
			mes "あなたの試合を見て、";
			mes "僕……決めました。";
			mes "あなたのことを目標に、";
			mes "がんばります！";
			close;
		}
		if(checkquest(9309)) {
			mes "[アルヒ]";
			mes "……ふう。";
			mes "結果は残念でしたけど……";
			mes "あなたとご一緒できて";
			mes "楽しかったです。";
			mes "あ、あの……戦ってくれて、";
			mes "本当にありがとうございました！";
			close;
		}
		mes "[アルヒ]";
		mes "ぼ、僕はアルヒといいます。";
		mes "……あなたも参加者なんですか？";
		mes "じ、実は僕も参加する予定なんです。";
		mes "とはいえ、実戦はこれが初めてで……";
		mes "こんな状態で、良い成績が残せるか";
		mes "僕自身、不安です……。";
		close;
	case 3:
		mes "[アルヒ]";
		mes "こ、こういう時は……。";
		mes "未鑑定のアイテムを鑑定して";
		mes "気持ちを落ち着かせ……";
		mes "って、だめだ！　だめだ！";
		next;
		mes "[アルヒ]";
		mes "僕は今、ノービスだから";
		mes "アイテム鑑定のスキルは";
		mes "使えないじゃないか……！";
		mes "うう……拡大鏡で我慢しよう。";
		mes "って、あれ？";
		mes "拡大鏡ってどこで買うんだろう？";
		close;
	case 4:
		mes "[アルヒ]";
		mes "ぼ、僕の防具の組み合わせ";
		mes "どこか変でしょうか……。";
		mes "まだよく組み合わせについて";
		mes "理解していなくて……。";
		next;
		mes "[アルヒ]";
		mes "僕の防具は、ほとんど両親が";
		mes "用意してくれたんです。";
		mes "その一つがこれです。";
		mes "ヴィゾフニルの羽飾り。";
		mes "僕は、この羽がお気に入りです。";
		next;
		mes "[アルヒ]";
		mes "この羽飾りは、母様がくれました。";
		mes "大会だというのに僕……";
		mes "武具すらろくに用意していなくて。";
		next;
		mes "[アルヒ]";
		mes "そんな中、母様が鷹の尾羽は";
		mes "鷹匠には特別な意味があって、";
		mes "魔よけの意味をもつということで";
		mes "大会で怪我をしないように";
		mes "この防具をくれました。";
		next;
		mes "[アルヒ]";
		mes "多分、無傷は無理でしょうけど";
		mes "それでも母様が今も傍にいて、";
		mes "僕を守ってくれているようで";
		mes "すごく心強いです。";
		close;
	case 5:
		mes "[アルヒ]";
		mes "はい！";
		mes "この女神の仮面も僕の";
		mes "お気に入りなんです。";
		mes "これは父様がくれました。";
		next;
		mes "[アルヒ]";
		mes "大会なんだから、臨むなら";
		mes "全力をもって挑むべきだ。";
		mes "当たり外れは世のならいなのだから";
		mes "おごったり落胆せず、";
		mes "どんな時も平常心でいろと……。";
		next;
		mes "[アルヒ]";
		mes "商売人らしい、父様の言葉だなと";
		mes "思いました……。";
		mes "なので、この仮面をつけて";
		mes "父様の言葉を忘れずに、";
		mes "全力でがんばるつもりです！";
		close;
	case 6:
		mes "[アルヒ]";
		mes "実は僕、家業を継いでほしいという";
		mes "両親の反対を押し切って";
		mes "この大会に出場したんです。";
		mes "そのかわり、この大会で";
		mes "良い成績を残さないと、";
		mes "家業を継ぐ約束ですが……。";
		next;
		mes "[アルヒ]";
		mes "……なぜでしょう、あなたとは";
		mes "初めて会う気がしなくて。";
		mes "もしかしたら僕にとって、";
		mes "この大会が最初で最後になるかもと";
		mes "考えたら、誰かに聞いてほしくて";
		mes "あなたに話してしまいました。";
		next;
		mes "[アルヒ]";
		mes "なのでもし、あなたと僕が";
		mes "戦うことになって、僕が負けたら";
		mes "僕みたいな参加者も居たなと";
		mes "憶えていていただけると";
		mes "すごく嬉しいです！";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "アルヒ : 優勝かあ。Zeny計算の大会なら、優勝する自信あるんだけどな……。";
			end;
		case 1:
			unittalk "アルヒ : 僕も優勝した人みたいに、立派な商人になれるかな……。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "アルヒ : ……ふう。緊張したけど、出場してよかったなあ……。";
		if(Sex == 0)	unittalk "アルヒ : 試合の結果はだめだったけど、楽しかったなあ……！";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "アルヒ : き、緊張してきた……。が、がんばるぞ……オー……。";
		if(Sex == 0)	unittalk "アルヒ : いつも執事のセポスがやってくれるから、登録に手間取っちゃったなあ……。";
		end;
	case 1:
		if(Sex == 1) unittalk "アルヒ : こ、こういう時は手のひらにZenyのZマークを書けばいいんだっけ……。";
		if(Sex == 0) unittalk "アルヒ : 噂には聞いていたけど、女性の人もいるんだなあ……。";
		end;
	case 2:
		if(Sex == 1) unittalk "アルヒ : う、うわぁ……みんな、強そうだなあ……。";
		if(Sex == 0) unittalk "アルヒ : えーっと、武器の扱い方の参考書、もう一回読み直しておこうかな……。";
		end;
	}
}

1@gef.gat,91,117,6	script	ディオ・アネモス#z1	669,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",2);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"君はマジシャンなの？";
		if('@prog >= 4) set '@str$[3],"目があったけど、なにか用事でも？";
		if('@prog >= 7) set '@str$[4],"どうしてこの大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[ディオ・アネモス]";
			mes "試合の時、";
			mes "僕の調子は最悪だったからねぇ。";
			mes "不調とはいえ僕に勝ったんだから、";
			mes "優勝くらいしてもらわないとねぇ。";
			close;
		}
		if(checkquest(9309)) {
			mes "[ディオ・アネモス]";
			mes "大会も終わってしまったねぇ。";
			mes "ちなみに僕は体調が";
			mes "いまいちだったようだ……。";
			mes "皆には黙っていたけど、";
			mes "昨日から少し体調がよくなくてねぇ！";
			mes "いや～参った参ったねぇ。";
			close;
		}
		mes "[ディオ・アネモス]";
		mes "僕はねぇ、ディオ・アネモス。";
		mes "ある崇高な目的のために";
		mes "この大会に参加するんだよねぇ。";
		mes "どうやら君も参加者の";
		mes "1人みたいだねぇ。";
		mes "まっ、よろしく頼むよ。";
		close;
	case 3:
		mes "[ディオ・アネモス]";
		mes "おお……マイハニー！";
		mes "君はどうしてそんなに";
		mes "サベージベベのように";
		mes "愛らしいんだ！";
		next;
		mes "[ディオ・アネモス]";
		mes "……。";
		mes "なんだい？";
		mes "僕はねぇ、いま大事な考えごとを";
		mes "している最中なんだよ。";
		mes "邪魔しないでくれるかい？";
		close;
	case 4:
		mes "[ディオ・アネモス]";
		mes "見て分からないかい？";
		mes "まあ、隠すことでもないからねぇ。";
		mes "教えてあげるよ。";
		mes "僕は生粋のマジシャンだよ。";
		next;
		mes "[ディオ・アネモス]";
		mes "うちの両親もマジシャンでねぇ。";
		mes "僕は5歳のころからずーっと、";
		mes "マジシャンについての勉強を";
		mes "欠かしていないんだよねぇ。";
		next;
		mes "[ディオ・アネモス]";
		mes "そんなわけだからもし君が、";
		mes "僕に負けても気にしない方が";
		mes "いいと思うよぉ。";
		mes "僕に負けるのはある意味、";
		mes "仕方がないからねぇ。";
		close;
	case 5:
		mes "[ディオ・アネモス]";
		mes "ソーサラーの女性なんだけどねぇ。";
		mes "確か、ゲフェン魔法学校に";
		mes "転職試験を受けるために";
		mes "出かけた際に、";
		mes "見かけた気がするんだよねぇ。";
		next;
		mes "[ディオ・アネモス]";
		mes "両親からこの大会に出るように";
		mes "勧められて、出場したけれど";
		mes "なかなかどうして、世間ってものは";
		mes "狭いって感じるよねぇ。";
		mes "僕の心は、ルーンミッドガッツ";
		mes "よりも広いけどね。";
		next;
		mes "[ディオ・アネモス]";
		mes "だからもし、君がいくら";
		mes "無様な試合をしても";
		mes "僕だけは君への態度を";
		mes "変えたりしないからねぇ。";
		mes "安心するといいよ。";
		close;
	case 6:
		mes "[ディオ・アネモス]";
		mes "そうそう、僕はねぇ……";
		mes "この大会で優勝したら同じ学校の";
		mes "マイハニーに大々的に告白する";
		mes "つもりなんだよねぇ。";
		mes "……。";
		mes "何がいいたいのかって顔だねぇ。";
		next;
		mes "[ディオ・アネモス]";
		mes "なんだか君は初対面のはずなのに";
		mes "前から何度も戦っている気がして";
		mes "しょうがないんだよねぇ。";
		mes "だから特別に君には僕が";
		mes "告白をする場面に";
		mes "立ちあわせてあげようじゃないか。";
		next;
		mes "[ディオ・アネモス]";
		mes "別に1人で告白しても良いんだけどね。";
		mes "君も将来、誰かに告白するときに";
		mes "参考になるんじゃないかなと";
		mes "思ったんだよね。";
		mes "断じて、1人じゃ心細いとか";
		mes "そんなことはないからねぇ。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "ディオ・アネモス : まさか僕の対戦者が優勝してしまうとはねぇ……。";
			end;
		case 1:
			unittalk "ディオ・アネモス : 優勝のトロフィーがないなら、僕が優勝する意味はないし悔しくなんかないねぇ。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "ディオ・アネモス : ま、僕がこんな大会で勝ってしまったら他の参加者に悪いし、負けてあげるのも一興だねぇ。";
		if(Sex == 0)	unittalk "ディオ・アネモス : 女性相手に本気を出せないし、負けたのはある意味、当然の結果だねぇ。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "ディオ・アネモス : 結果が決まってる試合なんて、やる必要ないと思うけどねぇ。";
		if(Sex == 0) unittalk "ディオ・アネモス : 僕の戦いぶりを見て、ファンが増えたら困るねぇ……。";
		end;
	case 1:
		if(Sex == 1) unittalk "ディオ・アネモス : 同じ男なのに、隠せない才能と華やかさ。僕の存在は罪だよねぇ……。";
		if(Sex == 0) unittalk "ディオ・アネモス : マイハニーほどじゃないが、可愛い子もいるもんだねぇ。";
		end;
	case 2:
		if(Sex == 1) unittalk "ディオ・アネモス : 試合にむけて、精神統一しておこうかねぇ。";
		if(Sex == 0) unittalk "ディオ・アネモス : 相手が女性だと戦いにくいから、やめてほしいねぇ……。";
		end;
	}
}

1@gef.gat,53,90,6	script	フェモン#z1	672,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",6);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"疲れているように見えますね";
		if('@prog >= 4) set '@str$[3],"今日も決まっていますね";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[フェモン]";
			mes "あんたが優勝してくれたお陰で";
			mes "可愛い女性たちが同情してくれてな。";
			mes "お陰でいまは、";
			mes "デートの約束で大忙しだ。";
			mes "あんたが優勝してくれて";
			mes "ある意味、良かったのかもな。";
			close;
		}
		if(checkquest(9309)) {
			mes "[フェモン]";
			mes "……そんなまさか！";
			mes "このオレが負けるとは……。";
			mes "でも、オレの美しさの";
			mes "アピールはできたはずだしな。";
			mes "それでよしとするか……。";
			mes "それじゃ、お疲れ。";
			close;
		}
		mes "[フェモン]";
		mes "その格好から察するに、";
		mes "魔法大会に参加するみたいだな。";
		mes "オレはフェモン。";
		mes "組み合わせ次第じゃ、";
		mes "戦うことになりそうだな。";
		close;
	case 3:
		mes "[フェモン]";
		mes "フフ……。";
		mes "オレ愛用の鏡で自分の格好を";
		mes "毎回確認してるんだが……。";
		mes "見てくれよ、この鍛えすぎず";
		mes "バランスが取れた肉体をさ。";
		next;
		mes "[フェモン]";
		mes "男はすぐに、筋肉美がどうとか";
		mes "鍛えすぎた肉体を自慢するが、";
		mes "あんなもの、ナンセンスだね。";
		mes "美しさは、顔と体のバランスが";
		mes "大事だっていうのに。";
		close;
	case 4:
		mes "[フェモン]";
		mes "ああ……。";
		mes "ちょっと顔見知りの男から、";
		mes "オレがもてるからって、";
		mes "やっかみ半分で文句を言われただけだ。";
		next;
		mes "[フェモン]";
		mes "オレの2人の兄貴も、";
		mes "お前がもっと稼がないから";
		mes "いつまでたっても生活が";
		mes "楽にならないだの";
		mes "自分は働かず文句ばかりで、";
		mes "オレのせいにするからな……。";
		next;
		mes "[フェモン]";
		mes "オレが関わる男はそんな奴らばかりだ。";
		mes "逆に女の子たちはどの子も";
		mes "いい子が多くて、";
		mes "特定の子だけ付き合うとか";
		mes "出来ないのが悩みだけどな！";
		close;
	case 5:
		mes "[フェモン]";
		mes "お、よう。";
		mes "……変だな、初対面なのに";
		mes "なぜだか既知の仲な気がするぜ。";
		mes "まあ、どこかで会った可能性も";
		mes "否めないが……";
		mes "気にしても仕方ないしな。";
		next;
		mes "[フェモン]";
		mes "はは！";
		mes "お前にはオレのこの";
		mes "センスがわかるみたいだな！!";
		mes "うん……そんなお前になら話しても";
		mes "大丈夫そうだな……。";
		next;
		mes "[フェモン]";
		mes "オレの趣味はZenyを貯めて";
		mes "新しい装飾品や武具を買うこと";
		mes "なんだが、どうもその考え方が";
		mes "理解されないんだ。";
		next;
		mes "[フェモン]";
		mes "ほしいものがある以上、";
		mes "使うZenyの金額は減らすよな？";
		mes "例えば、食べるものを";
		mes "タンの盛り合わせから";
		mes "たれ付き焼き肉に変えて";
		mes "Zenyを少し浮かすんだ。";
		next;
		mes "[フェモン]";
		mes "すると周りからなぜだか";
		mes "ケチだのなんだのと";
		mes "いわれちまうんだよなあ……。";
		mes "使いたくないから減らすのに";
		mes "納得いかないぜ……。";
		close;
	case 6:
		mes "[フェモン]";
		mes "出場した理由か？";
		mes "大会に出場した理由の一番は";
		mes "無論、オレの美しさアピール";
		mes "なんだが……それに加え";
		mes "手に入れた魔法大会コインを売って、";
		mes "買いたいものがあるんだよな。";
		next;
		mes "[フェモン]";
		mes "新しく発表されたデザインの";
		mes "兜や靴……いろいろと";
		mes "ほしいんだよ……！";
		mes "正直にいってしまうと";
		mes "デザインは男物のほうが";
		mes "かっこいいのが多いんだが……。";
		next;
		mes "[フェモン]";
		mes "オレは残念ながら女だから、";
		mes "似合わない場合が多いんだよ。";
		mes "この時だけは、あの暴力兄貴どもが";
		mes "少し羨ましくなるぜ……。";
		mes "まっ、オレは男が嫌いだから";
		mes "女でよかったけどな。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "フェモン : 優勝していたらオレはもっと輝けただろうな。";
			end;
		case 1:
			unittalk "フェモン : まさかアイツが優勝するとはな……。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "フェモン : ……いつも男はオレの邪魔をする。嫌になるぜ……。";
		if(Sex == 0)	unittalk "フェモン : 負けた女の子を慰めてあげたいが、暇はなさそうだな。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "フェモン : たいした男が居ないみたいだな。都合がいいぜ！";
		if(Sex == 0) unittalk "フェモン : ……ナンパは大会の後のお楽しみにしておくかね。";
		end;
	case 1:
		if(Sex == 1) unittalk "フェモン : 今度、ファンの子たちと特製肉煮込みでも食べに行くか。";
		if(Sex == 0) unittalk "フェモン : 女の子からの熱い視線を感じるぜ……。";
		end;
	case 2:
		if(Sex == 1) unittalk "フェモン : 今日のオレも、決まってるな！";
		if(Sex == 0) unittalk "フェモン : へえ。期待してなかったが出場者にも、可愛い子は多いんだな。";
		end;
	}
}

1@gef.gat,85,68,6	script	オルドル#z1	673,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",7);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"なにか悩んでいます？";
		if('@prog >= 4) set '@str$[3],"今は修行中ですか？";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[オルドル]";
			mes "……ふう。";
			mes "私は今、猛烈に感動しています。";
			mes "あなたのように腕のたつ御仁が";
			mes "いることを知り、世界は広いなと……。";
			mes "龍之城にこもっていたら、あなたにも";
			mes "お会いできなかったでしょうね。";
			close;
		}
		if(checkquest(9309)) {
			mes "[オルドル]";
			mes "……やはり、努力したところで";
			mes "生まれたときに決められた";
			mes "運命は変えられないのか……。";
			mes "あ、あなたは……。";
			mes "失礼、独り言です……。";
			mes "大会、お疲れ様でした。";
			close;
		}
		mes "[オルドル]";
		mes "あなたも参加されるのですか？";
		mes "私はオルドル。";
		mes "魔法大会参加者の1人です。";
		mes "由緒あるゲフェン魔法大会に";
		mes "参加できるとは……。";
		mes "とても光栄なことです。";
		close;
	case 3:
		mes "[オルドル]";
		mes "私はいつも太陽が昇る前に";
		mes "起床して、参考書を読んだり";
		mes "魔法の修行をおこない、";
		mes "太陽が沈むころに、";
		mes "就寝するという生活を18年間";
		mes "毎日おこなってきました。";
		next;
		mes "[オルドル]";
		mes "龍之城ではそれが";
		mes "当たり前だったのです。";
		mes "ですがこちらの街では、";
		mes "かなり遅くまで皆さん";
		mes "働いていたり起きていると聞き";
		mes "驚いています……。";
		close;
	case 4:
		mes "[オルドル]";
		mes "……あなたは本当によく";
		mes "人を観察されているのですね。";
		mes "あなたの仰るとおり、";
		mes "悩んでいる……というか";
		mes "わからないことがあって。";
		next;
		mes "[オルドル]";
		mes "大会参加予定の方や";
		mes "観戦者の方から";
		mes "話かけられることがあるのですが、";
		mes "何故かみなさん、";
		mes "私を女性だと思って";
		mes "声をかけてくるのです……。";
		next;
		mes "[オルドル]";
		mes "私はこの通り、体の線が細く";
		mes "女性っぽい印象を与えるのは";
		mes "仕方がないとは思うのですが……。";
		mes "こうも間違われると少し";
		mes "気になってしまいますね。";
		mes "体も鍛えるべきでしょうか……。";
		close;
	case 5:
		mes "[オルドル]";
		mes "さっきまで参考書を読んでいましたが";
		mes "休憩しようと思っていたところなので";
		mes "大丈夫ですよ。";
		mes "ところで……";
		next;
		mes "[オルドル]";
		mes "つかぬことをお伺いしますが、";
		mes "もしやどこかで……。";
		mes "あ、すいません。";
		mes "よく考えれば私がここに来たのは";
		mes "今回が初めてでした。";
		mes "気にしないでください。";
		next;
		mes "[オルドル]";
		mes "今、苦手な部分を克服したくて";
		mes "参考書を片手に、練習していますが";
		mes "……なかなかうまくいきませんね。";
		mes "特に私はあまり要領が良いわけではなく";
		mes "繰り返して、やっと憶えるので……。";
		next;
		mes "[オルドル]";
		mes "そんな私を、龍之城の一部の方は";
		mes "真の努力家だと、褒める方も";
		mes "中にはいらっしゃいますが……。";
		mes "私としては努力している姿も";
		mes "見せずにこなせないと";
		mes "意味がないと思うのですが……。";
		close;
	case 6:
		mes "[オルドル]";
		mes "なぜ私がこの大会に出場しようと";
		mes "思ったのか、ですか。";
		mes "実は……";
		mes "私の家は、龍之城でも1～2を争う";
		mes "権力をもっているようでして……。";
		next;
		mes "[オルドル]";
		mes "今大会のような公の場で";
		mes "よい成績を残し、お家の威厳を";
		mes "示す必要があるようなのです。";
		next;
		mes "[オルドル]";
		mes "また、当主になれるのは、";
		mes "男のみですから……";
		mes "一人っ子で男の私が";
		mes "こうして参加することになったのです。";
		next;
		mes "[オルドル]";
		mes "ここに来てから、誰かに見られている";
		mes "視線も感じますし……。";
		mes "我が家の次期当主として";
		mes "戦い方もそうですが……";
		mes "立ち振る舞いや言動にも";
		mes "気をつけないといけません。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "オルドル : ……あの方とフェンリルさんの試合、凄かったなあ。";
			end;
		case 1:
			unittalk "オルドル : 優勝は逃してしまったけれど、よい勉強になった。この経験を生かさねば。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "オルドル : ……やはり、まだ私も修行不足なのか？　それともやはり性別の……。";
		if(Sex == 0)	unittalk "オルドル : 彼女のような腕利きの人でも負けてしまうなんて……やはり、世界は広い。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "オルドル : ここで魔法の修行をしては迷惑だろうなあ……。";
		if(Sex == 0) unittalk "オルドル : 何故だろう、最近妙に誰かに見られている視線を感じる……。";
		end;
	case 1:
		if(Sex == 1) unittalk "オルドル : いつもこの時間は修行に励んでいるから落ち着かない……。参考書でも読んでおこう。";
		if(Sex == 0) unittalk "オルドル : ……もしかしたら私も彼女たちのように……だめだ！　大会前だからと弱気になってどうするんだ、私！";
		end;
	case 2:
		if(Sex == 1) unittalk "オルドル : あの人、雰囲気と装備から察するに、かなりの腕前だろうなあ。";
		if(Sex == 0) unittalk "オルドル : てっきり1人か2人くらいかと思ったけど、女性の参加者も割りと居るんだな……。";
		end;
	}
}

1@gef.gat,111,62,6	script	ブルート・ハゼ#z1	674,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",8);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"もしやゲフェンに住んでるの？";
		if('@prog >= 4) set '@str$[3],"今日もうさ耳、似合ってますね";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[ブルート・ハゼ]";
			mes "キミが優勝しちゃったの？";
			mes "そうなんだー、おめでとう！";
			mes "後でこっそり闇討ちしようと";
			mes "思ってたのに……。";
			mes "優勝しちゃったら、";
			mes "できないじゃないかー！";
			close;
		}
		if(checkquest(9309)) {
			mes "[ブルート・ハゼ]";
			mes "……ああ、良かった！";
			mes "このうさ耳、かなり年季入ってるから、";
			mes "壊れないか心配で……。";
			mes "試合に集中するどころじゃ";
			mes "なかったわ……。";
			mes "……あ、なんでもないよ～？";
			close;
		}
		mes "[ブルート・ハゼ]";
		mes "なになにー？";
		mes "ボクに興味あるのかな？";
		mes "ボクはブルート・ハゼ！";
		mes "この頭のうさ耳は……";
		mes "え？　うさ耳の名前は聞いてない？";
		mes "ちぇーっ。";
		close;
	case 3:
		mes "[ブルート・ハゼ]";
		mes "ボク、暗いのと狭い場所きらいなの♪";
		mes "だから夜とダンジョンもきらーい。";
		mes "なんで寝ないとダメなのかなー？";
		mes "寝てる間に襲われたらさ、";
		mes "自分も相手もつまらないよねー。";
		mes "そう思わないー？";
		next;
		mes "[ブルート・ハゼ]";
		mes "それに暗いと、においに敏感になるから";
		mes "むせるような血のにおいに";
		mes "気持ち悪くなったりとかするし。";
		mes "ダンジョンは、ばっちいし。";
		mes "この世から消えてくれないかなー。";
		mes "キミもそう思うでしょ？　でしょ？";
		close;
	case 4:
		mes "[ブルート・ハゼ]";
		mes "ざーんねん！";
		mes "ゲフェンには魔法大会に";
		mes "参加するために来たんだよ～！";
		mes "ボク、アルデバラン生まれなんだ。";
		next;
		mes "[ブルート・ハゼ]";
		mes "と・こ・ろ・で！";
		mes "アルデバランって聞くと、";
		mes "何を想像する～？";
		mes "カプラ本社？";
		mes "それともそれとも、";
		mes "やっぱり錬金術師ギルド？";
		next;
		mes "[ブルート・ハゼ]";
		mes "え……？　時計塔？";
		mes "……キミ、あんなとこが好きなの？";
		mes "……まあ、いいけど。";
		mes "ボク的には錬金術師ギルドが";
		mes "お勧めだから、機会があれば";
		mes "行ってみてね～♪";
		close;
	case 5:
		mes "[ブルート・ハゼ]";
		mes "わー！";
		mes "このうさ耳の良さ、";
		mes "わかってくれるんだね～♪";
		mes "そういってくれたの";
		mes "キミがはじめてかもー！";
		mes "……うーん？";
		next;
		mes "[ブルート・ハゼ]";
		mes "ううーん？？？？";
		mes "おかしいなあ……。";
		mes "ボク、記憶力は自信が";
		mes "あるんだけどなあ……。";
		mes "キミの顔に見覚えがあるのに、";
		mes "なぜか思い出せないんだよね。";
		next;
		mes "[ブルート・ハゼ]";
		mes "でもねでもね！";
		mes "ボクが強いせいで、対戦した人の中じゃ";
		mes "このうさ耳を見ただけで、逃げたり";
		mes "震え上がって動けなくなる人も";
		mes "いるらしいって聞いたよー。";
		mes "強いって罪だよね～♪";
		next;
		mes "[ブルート・ハゼ]";
		mes "もう1つ教えておくと！";
		mes "ボクが小さい頃に、お兄ちゃんから";
		mes "誕生日プレゼントにってもらったんだ。";
		mes "えへへ、ボク、お兄ちゃんっ子なの♪";
		mes "だからこのうさ耳はなにより";
		mes "大事にしてるんだ～♪";
		close;
	case 6:
		mes "[ブルート・ハゼ]";
		mes "大会ってわくわくするよね！";
		mes "観覧席でよくわからない戦いを";
		mes "目をこらしてみるくらいなら";
		mes "参加して目の前で、相手の血が";
		mes "ぶしゃーな方が楽しいよね♪";
		next;
		mes "[ブルート・ハゼ]";
		mes "以上が、ボクがこの大会に";
		mes "参加することにした大きな理由だよ！";
		mes "偉い人もほら、参加して斬ることに";
		mes "意義があるとかいってるしね♪";
		mes "え？　そんなこといってない？";
		mes "もう、細かいなあ……！";
		next;
		mes "[ブルート・ハゼ]";
		mes "斬るっていえば思い出すのが、";
		mes "時計塔で迷子になって一週間、";
		mes "モンスターと血で血を洗う争いをした";
		mes "あの日を思いだすよ～！";
		mes "今となっては、よい思い出だけどね♪";
		next;
		mes "[ブルート・ハゼ]";
		mes "あの一件のおかげで、";
		mes "今のボクがいるようなものだし。";
		mes "いつかボクも、誰かの";
		mes "ターニングポイントになるほど";
		mes "強くなれるといいな～♪";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "ブルート・ハゼ : お兄ちゃんに、ボクが優勝する姿を見せたかったな……。";
			end;
		case 1:
			unittalk "ブルート・ハゼ : ……あの子が優勝するなんて予想外だったわ。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "ブルート・ハゼ : ……負けたけど、うさ耳が無事で良かった。";
		if(Sex == 0)	unittalk "ブルート・ハゼ : ……ふう、女性のほうが攻撃が激しくてビックリだよ。だから同性は苦手なんだよ。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "ブルート・ハゼ : ふふ、やっぱりこのボクのうさ耳が他のアクセサリーや防具より一番可愛い！";
		if(Sex == 0) unittalk "ブルート・ハゼ : 誰かさんの血みどろメイク♪　楽しみだなあ！";
		end;
	case 1:
		if(Sex == 1) unittalk "ブルート・ハゼ : やっぱりお兄ちゃん以上に、かっこいい男性はいないなー。";
		if(Sex == 0) unittalk "ブルート・ハゼ : 同性は苦手だからあたらないといいなー……。";
		end;
	case 2:
		if(Sex == 1) unittalk "ブルート・ハゼ : 試合前に、腹ごしらえしておくほうがいいかなあ。";
		if(Sex == 0) unittalk "ブルート・ハゼ : んー、女性が割りといるっぽいけど、ボクと近い年齢の人は居ない感じかな？　残念！";
		end;
	}
}

1@gef.gat,104,42,6	script	黒魔#z1	675,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",9);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"なんだか楽しそうですね……？";
		if('@prog >= 4) set '@str$[3],"名前を呼ばれた気がしたのですが……";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[黒魔]";
			mes "フン。";
			mes "お前は優勝できて満足だろうが……。";
			mes "俺様はお前のお陰で、";
			mes "予定が狂っちまったぜ。";
			mes "また日を改めるか。";
			close;
		}
		if(checkquest(9309)) {
			mes "[黒魔]";
			mes "……チッ。";
			mes "いい子ちゃんの手本みたいな";
			mes "戦いっぷりで、興ざめだぜ。";
			mes "本来のターゲットもあたる前に、";
			mes "倒されちまったしな。";
			mes "時間の無駄だったぜ……。";
			close;
		}
		mes "[黒魔]";
		mes "……おい。";
		mes "お前は俺様を漆黒の牙と知って、";
		mes "話しかけてるのか？";
		mes "いや、その平和ボケした面をみる限り";
		mes "知らないで話しかけたようだな。";
		mes "なら、もう話しかけるな。";
		close;
	case 3:
		mes "[黒魔]";
		mes "……大会という舞台があるなら";
		mes "それを利用しねーとな。";
		mes "特にこういう大きな大会だ。";
		mes "不慮の事故なんてものが、";
		mes "1つや2つあってもおかしくない。";
		mes "お前もそう思うだろ？";
		next;
		mes "[黒魔]";
		mes "例えば……。";
		mes "俺様の話を立ち聞きする輩が";
		mes "大会中に不慮の事故で……";
		mes "なんて話も100%ないとは";
		mes "言い切れないよなあ？";
		mes "クックックック……。";
		close;
	case 4:
		mes "[黒魔]";
		mes "……お前、物好きだな。";
		mes "話しかけるなといったはずだが？";
		mes "……まあ、いい。";
		mes "ちょっと面白い内容の手紙を";
		mes "受け取ったもんでな。";
		next;
		mes "[黒魔]";
		mes "人の命がなによりも重いとか";
		mes "真面目くさった顔で語るやつがいるが";
		mes "自分が生きるためにしてることを";
		mes "棚に上げてる場合が多い。";
		mes "特に、名誉や名声、家系に拘る";
		mes "お偉いさん連中は……な。";
		next;
		mes "[黒魔]";
		mes "そんな奴らが居なくならないからこそ";
		mes "俺様も、おまんまの食い上げに";
		mes "ならねーんだが。";
		mes "まったく、この世の中";
		mes "うまくできてるよなあ！";
		mes "笑いがこみ上げてくるぜ……。";
		close;
	case 5:
		mes "[黒魔]";
		mes "たいした用事じゃねーが。";
		mes "少し確認したいことが";
		mes "あっただけだ。";
		mes "しかし……";
		next;
		mes "[黒魔]";
		mes "なぜか分からんが、";
		mes "お前とは既知の仲の気がするな。";
		mes "そんな風に感じた人間は、";
		mes "数えるほどしかいないんだが……。";
		mes "もしやお前も……。";
		mes "フン、まあいい。";
		next;
		mes "[黒魔]";
		mes "ところでお前、あのおん……いや";
		mes "オルドルとかいうやつと";
		mes "仲がいいのか？";
		mes "だとしたらそれ以上、";
		mes "アイツと関わらないほうが";
		mes "身のためだぞ。";
		next;
		mes "[黒魔]";
		mes "対戦者と仲良くなったところで";
		mes "なにもいいことはない上に";
		mes "アイツはもうすぐ、退場になる。";
		mes "フンッ。";
		mes "どういう意味かは聞くなよ。";
		mes "……手間が増えるからな。";
		close;
	case 6:
		mes "[黒魔]";
		mes "俺様がここにいるのは";
		mes "ギブアンドテイク。";
		mes "必要だから、居るだけだ。";
		mes "とはいえその結果……";
		mes "この子悪魔帽の色もすっかり";
		mes "変色しちまったが……。";
		next;
		mes "[黒魔]";
		mes "フン……。";
		mes "望むも望まないも、";
		mes "俺様には昔から、";
		mes "これしかなかったからな。";
		mes "これからもこの帽子を自分から";
		mes "脱ぐことはないだろう。";
		next;
		mes "[黒魔]";
		mes "……柄にもなく語っちまったな。";
		mes "仕事前に飲んだ";
		mes "フベルゲルミルの酒にでも";
		mes "酔っちまったか……？";
		mes "……酔いを醒ましたい。";
		mes "一人にしてくれ。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "黒魔 : 優勝になにも魅力は感じないが……あいつらの試合はなかなか見ごたえがあったな。";
			end;
		case 1:
			unittalk "黒魔 : フン、優勝したところで単なる自己満足にすぎない。おめでたい奴らだ。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "黒魔 : ……人生の負け犬よりはマシだ。";
		if(Sex == 0)	unittalk "黒魔 : ……チッ。あの女、なかなか運がいいみたいだな。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "黒魔 : あの女、人が多いほうが安全だろうなんて考えてるなら甘いぞ……。";
		if(Sex == 0) unittalk "黒魔 : あの女……あれで、ばれないと思っているのか。おめでたいやつだな。";
		end;
	case 1:
		if(Sex == 1) unittalk "黒魔 : 今はまだその時じゃないな……好機をまつか。";
		if(Sex == 0) unittalk "黒魔 : しかし、子悪魔帽の色がすっかり変わっちまったな。もう元の色すら憶えてないぜ……。";
		end;
	case 2:
		if(Sex == 1) unittalk "黒魔 : ……どいつもこいつも、平和ボケした腑抜けた面した奴ばかりだな。";
		if(Sex == 0) unittalk "黒魔 : ……どの女も、ファルコンの衆みたいに見分けがつかねーな。同じに見えるぜ。";
		end;
	}
}

1@gef.gat,115,66,6	script	イフォドス#z1	676,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",10);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"今日も元気ですね";
		if('@prog >= 4) set '@str$[3],"珍しくなにか悩んでる……？";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[イフォドス]";
			mes "優勝してしまったのか……。";
			mes "さすが俺のライバルだ！";
			mes "俺の次の目標はお前だ！";
			mes "お前を倒すまで、俺は";
			mes "世界の果てまでもついていく覚悟だ！";
			mes "待ってろよ！";
			close;
		}
		if(checkquest(9309)) {
			mes "[イフォドス]";
			mes "まさかの負けだと……!?";
			mes "おかしい！";
			mes "叫び声の量なら俺が勝っていたはずだ！";
			mes "それに、縁起を担いで奮発して";
			mes "強運の汁を10杯飲んだのに！";
			mes "お、思い出したら腹の調子が……。";
			close;
		}
		mes "[イフォドス]";
		mes "やあやあ！";
		mes "あんたも大会参加者か!?";
		mes "俺の名前はイフォドス！";
		mes "ルーンミッドガッツ全域を";
		mes "駆けめぐる参加者の1人だ！";
		mes "よろしくなーっ！";
		close;
	case 3:
		mes "[イフォドス]";
		mes "この大会に出れば、";
		mes "ルーンミッドガッツで一番強いやつと";
		mes "戦えると思って参加したんだ！";
		mes "俺も今までいろいろな職業の";
		mes "やつらと戦ったんだが……";
		mes "まだまだ数が少ないしな！";
		next;
		mes "[イフォドス]";
		mes "なによりこの大会に、";
		mes "ちょっと因縁のあるやつが出るんだ。";
		mes "俺はあいつとこの大会で戦えるまで";
		mes "誰にも負けん！　と、心に決めている！";
		mes "だから俺とあたって負けても";
		mes "恨まないでくれよ！";
		close;
	case 4:
		mes "[イフォドス]";
		mes "はっはっはっはっは！";
		mes "俺から元気をとったら";
		mes "何も残らないしな！";
		mes "ところで……";
		next;
		mes "[イフォドス]";
		mes "俺はフェイヨン生まれなんだが";
		mes "冒険に出たくてしょうがなかった！";
		mes "昔から、冒険の手記や物語を";
		mes "読むのが好きだったからな。";
		mes "そして忘れもしない……";
		mes "14歳の誕生日。";
		next;
		mes "[イフォドス]";
		mes "俺は家を飛び出して、";
		mes "ルーンミッドガッツ全地域を";
		mes "歩いて回る、武者修行という";
		mes "旅に出たのだ！";
		mes "そして……";
		mes "現在に至るっと。";
		next;
		mes "[イフォドス]";
		mes "！　思いついた！";
		mes "優勝した暁には、";
		mes "俺の自伝を出すのもいいな！";
		mes "よし、今度から無敗メモに";
		mes "自伝メモをつけて、";
		mes "出版に備えるとするか！";
		close;
	case 5:
		mes "[イフォドス]";
		mes "やあやあ！";
		mes "丁度お前のことを調べていた！";
		mes "ううーむ。";
		mes "……無敗メモにも名前がないな。";
		mes "ってことは初対面なのか？";
		next;
		mes "[イフォドス]";
		mes "しかーし！";
		mes "何故だかわからないのだが、";
		mes "お前とは初対面の気がしないな！";
		mes "多分、木の精……もとい";
		mes "気のせいだろう。";
		next;
		mes "[イフォドス]";
		mes "それにしても、だ。";
		mes "俺以外のルーンナイトはもてるのに";
		mes "何故、俺はさっぱりもてないんだ!?";
		mes "わからん……。";
		mes "みんな、見る目がないのか……。";
		next;
		mes "[イフォドス]";
		mes "はっ、そうか！";
		mes "俺があまりにも強すぎて";
		mes "近寄りがたい雰囲気なんだな！";
		mes "それならば納得だ！";
		mes "致し方なし、だな。";
		mes "……凄く悲しいけどな！";
		close;
	case 6:
		mes "[イフォドス]";
		mes "俺は、武者修行中にいろいろな";
		mes "職業のやつと戦ったんだが……。";
		mes "今回の大会の参加者、ジューに";
		mes "結局、勝つことができなかった！";
		mes "はっきりいって……あいつは強い！";
		mes "俺が唯一勝てなかった相手だしな！";
		next;
		mes "[イフォドス]";
		mes "しかしある日を境に、消息が途絶え";
		mes "やっと掴んだ情報によれば、";
		mes "ジューのやつがこの大会に";
		mes "選手として出場すると……！";
		mes "それだけに留まらず、あいつはリア充！";
		mes "……な、泣いてないぞ！";
		next;
		mes "[イフォドス]";
		mes "……というわけで、だ。";
		mes "現在に至るわけだな、うん。";
		mes "とにかく、俺の目的はジュー！";
		mes "そしてついでに優勝して、";
		mes "俺の強さを世間に知らしめる！";
		mes "完璧だろう!?";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "イフォドス : 俺の対戦相手が優勝とか、どんなお約束なんだ！";
			end;
		case 1:
			unittalk "イフォドス : まさかのまさか！　この俺が優勝を逃すなんて！";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "イフォドス : ぐあー！　ジューと戦う前に負けてしまった……ムネーン！";
		if(Sex == 0)	unittalk "イフォドス : まさか女性に負けるとは……最近の女性は怖いな……。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "イフォドス : うむ、俺よりいけてる男はいないな！　大丈夫だ！";
		if(Sex == 0) unittalk "イフォドス : 対戦相手は女性じゃないほうが……いやいや、しかし！　俺が華麗に勝って、そこから芽生える……ブツブツ。";
		end;
	case 1:
		if(Sex == 1) unittalk "イフォドス : 気合入れ体操でもやるか!!　イッチニーサンシー……！";
		if(Sex == 0) unittalk "イフォドス : 対戦相手じゃなけりゃ、デートの一つや二つ……ううむ、まったくもって残念だ。";
		end;
	case 2:
		if(Sex == 1) unittalk "イフォドス : ジューに会ったら、ハンドレッドスピアをお見舞いしてやりたいところだな！";
		if(Sex == 0) unittalk "イフォドス : 戦闘では無敗を誇る俺でも、なぜかモテないんだよな……。";
		end;
	}
}

1@gef.gat,137,53,4	script	レチェニエ#z1	677,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",11);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"もしや大聖堂にいたの？";
		if('@prog >= 4) set '@str$[3],"ごきげんよう";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[レチェニエ]";
			mes "あらあら！";
			mes "優勝なんて凄いわね♪";
			mes "コインも沢山、手に入るんでしょうね。";
			mes "私も優勝できていれば、";
			mes "もっと楽に逃げ……いえいえ。";
			mes "こちらの話なの、ごめんなさい♪";
			close;
		}
		if(checkquest(9309)) {
			mes "[レチェニエ]";
			mes "……。";
			mes "えっ、あらー？";
			mes "どうかなさいました？";
			mes "え、試合終わりましたの？";
			mes "まあ、いつのまに!?";
			mes "私、全然記憶がありませんわ……。";
			close;
		}
		mes "[レチェニエ]";
		mes "うふふ、あなたも参加されますの？";
		mes "申し遅れました、私はレチェニエ。";
		mes "生まれはラヘルなのですが、";
		mes "今はプロンテラに住んでおりますの。";
		mes "あら……お祈りの時間ですわ。";
		mes "また後ほど、ごきげんよう。";
		close;
	case 3:
		mes "[レチェニエ]";
		mes "我らが主オーディンよ……";
		mes "あなたの無限の慈悲と愛を……";
		mes "……。";
		mes "あら、ごきげんよう。";
		mes "どうかなさいました？";
		next;
		mes "[レチェニエ]";
		mes "この祈りの言葉、私なんだか";
		mes "好きでつい、つぶやいてしまいますの。";
		mes "それにしても……";
		mes "なぜ私をこの大会に……？";
		mes "あら、ごめんなさいね。";
		mes "単なる独り言ですわ。";
		close;
	case 4:
		mes "[レチェニエ]";
		mes "ごきげんよう。";
		mes "あら、お話していませんでした？";
		mes "私、6歳まではラヘルですごして、";
		mes "7歳からはプロンテラの大聖堂で";
		mes "お世話になっていますの。";
		next;
		mes "[レチェニエ]";
		mes "どちらの街も、とても大きく";
		mes "立派な建物が多いので、";
		mes "散歩が楽しかったですわ。";
		mes "特にこんな陽気の日は";
		mes "大聖堂に居るほうが";
		mes "勿体無い気分になりますわね。";
		next;
		mes "[レチェニエ]";
		mes "個人的に景観でいえば";
		mes "ラヘルの方が、緑が多くて";
		mes "好きですのよ。";
		mes "大会が終わったら、少し";
		mes "ラヘルに里帰りでも";
		mes "しようかしら……。";
		close;
	case 5:
		mes "[レチェニエ]";
		mes "変ですわねえ。";
		mes "どこかでお会いしたような";
		mes "気がしてしかたありませんの。";
		mes "私たちもしかしたら前世で";
		mes "お会いしてたかしら？";
		mes "うふふ……。";
		next;
		mes "[レチェニエ]";
		mes "お会いした、といえば。";
		mes "大司教様にはお会いしたことが";
		mes "ありますかしら？";
		mes "私のこともよく気にかけて下さる";
		mes "とても素敵な方ですのよ。";
		next;
		mes "[レチェニエ]";
		mes "特に悪魔つきや、";
		mes "オカルト関連に関して、";
		mes "あの方の知識と手腕にかなう方は";
		mes "いないという噂ですのよ。";
		mes "今度また是非、大聖堂に";
		mes "遊びにきてくださいませ。";
		close;
	case 6:
		mes "[レチェニエ]";
		mes "私、本当はこの大会に";
		mes "自分の意思で出たわけでは";
		mes "ありませんのよ。";
		mes "うふふ、驚きました？";
		mes "実は大司教様にいわれて";
		mes "参加しましたのよ。";
		next;
		mes "[レチェニエ]";
		mes "他の皆さんと交流することも";
		mes "神に仕えるものの、勤めだと。";
		mes "でも私、参加してよかったと";
		mes "思っていますのよ？";
		mes "大聖堂に居ると妙に記憶が";
		mes "途切れることが多くて……。";
		next;
		mes "[レチェニエ]";
		mes "でも今はまったく起きないので";
		mes "恐らく大聖堂に問題があるのでしょう。";
		mes "そのため私、この大会を好機に";
		mes "一度旅にでて、記憶喪失について";
		mes "調べてみようかなと思っていますわ。";
		mes "うふふ♪";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "レチェニエ : 私もあの方と戦ったはずなのに……やはり記憶がないわ……。";
			end;
		case 1:
			unittalk "レチェニエ : 私がもし優勝していたら、大聖堂の皆さんはなんていったのかしら……。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "レチェニエ : ……知らない間に負けてるなんて気分がよくありませんわ。";
		if(Sex == 0)	unittalk "レチェニエ : 肝心なところで記憶が途切れるているせいで、負けた実感がありませんわ……。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "レチェニエ : 大司教様、なぜ私をこの大会に参加させたのかしら……。";
		if(Sex == 0) unittalk "レチェニエ : この大会が終わったら、私は新天地に旅立たなくては……。";
		end;
	case 1:
		if(Sex == 1) unittalk "レチェニエ : 優勝できればよいのだけど……対戦なんて初めてだから、不安だわ。";
		if(Sex == 0) unittalk "レチェニエ : どうせなら、女性同士の対戦は美や、女性らしさを競う内容に変更すればよろしいのに……。";
		end;
	case 2:
		if(Sex == 1) unittalk "レチェニエ : 今回は、記憶が飛ばなければよいのだけど……本当に、困った体質ですわ。";
		if(Sex == 0) unittalk "レチェニエ : ……参加者に女性が割りといらっしゃることに驚きですわ。";
		end;
	}
}

1@gef.gat,158,63,4	script	ユメヒメ#z1	678,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",12);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"眉間にしわが……";
		if('@prog >= 4) set '@str$[3],"また眉間にしわが……";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[ユメヒメ]";
			mes "まあまあまあまあまあ！";
			mes "優勝しちゃったのね！";
			mes "すごいじゃない！";
			mes "あなたには特別に、";
			mes "優勝おめでとうのダンスを";
			mes "踊らないとね♪";
			close;
		}
		if(checkquest(9309)) {
			mes "[ユメヒメ]";
			mes "いや～ん、負けちゃった！";
			mes "みんな、強いのね。";
			mes "若さ溢れる動きで、羨ましいわぁ……！";
			mes "私ももう少し若かったら……。";
			mes "ううん、まだ私も大丈夫……よね？";
			mes "……30すぎたら、ダメかしら……。";
			close;
		}
		mes "[ユメヒメ]";
		mes "あら～？　お姉さんにご用事？";
		mes "私はユメヒメよ～♪";
		mes "参加者に見えないと思うけど";
		mes "これでも一応、大会に出場する";
		mes "参加者の1人なの♪";
		mes "よろしくねぇ～♪";
		close;
	case 3:
		mes "[ユメヒメ]";
		mes "大会といっても私には";
		mes "他のお祭りと大差ないのよ～。";
		mes "でもだからといって";
		mes "手加減したり、手は抜かないわよ～？";
		mes "安心してちょうだいね♪";
		next;
		mes "[ユメヒメ]";
		mes "それに私、優勝してちょーっと";
		mes "守りたいものがあるのよ～♪";
		mes "だから踊りの練習以上に今回は";
		mes "気合いれてがんばるつもりよ♪";
		mes "あなたももし良かったら";
		mes "私の応援よろしくね～♪";
		close;
	case 4:
		mes "[ユメヒメ]";
		mes "!!!!";
		mes "や、やだ～もうっ！";
		mes "これは年のせいじゃないわよ？";
		mes "ちょっと考えごとしてたのよ。";
		mes "どうも昔からある";
		mes "私のクセみたいなのよね♪";
		next;
		mes "[ユメヒメ]";
		mes "最近の私の悩みなんだけど、";
		mes "ダンサー志望の子が減ってきてて";
		mes "どうしたら増えるのか、";
		mes "よい案が思いつかなくて";
		mes "困ってるのよ～……。";
		mes "もう、こうなったら……";
		next;
		mes "[ユメヒメ]";
		mes "ダンサーになってくれた子には";
		mes "コモドの名産品である";
		mes "洞窟熟成チーズでも";
		mes "配るべきかしら……。";
		mes "でもチーズ嫌いだとだめだし。";
		mes "難しいわあ。";
		close;
	case 5:
		mes "[ユメヒメ]";
		mes "これは私のクセだって";
		mes "話したじゃない？";
		mes "そこはまた何か悩んでいるのか、";
		mes "聞いてあげるのが優しさよ？";
		mes "ということで、ちょっとまた";
		mes "お姉さん、少し悩んでるのよ～。";
		next;
		mes "[ユメヒメ]";
		mes "多分、あなたとは何度か、";
		mes "会ってる気はするのよねえ。";
		mes "でも詳しく思い出せないのよ～。";
		mes "もしかしてこれって歳のせ……";
		mes "……きっと気のせいね！　うん。";
		next;
		mes "[ユメヒメ]";
		mes "ところで、あなたはコモドって";
		mes "行ったことはある？";
		mes "私の生まれ故郷は";
		mes "コモドなのよ、うふふ♪";
		next;
		mes "[ユメヒメ]";
		mes "私がダンサーになったきっかけも";
		mes "コモドの劇場で見た、";
		mes "ダンサーの姿が忘れられなくてね。";
		next;
		mes "[ユメヒメ]";
		mes "13歳からダンサーとして働きだして";
		mes "1年前に引退するまではこれでも";
		mes "その劇場ナンバーワンダンサーと";
		mes "いわれてたほどに、はまったわ♪";
		mes "これが、私の唯一の自慢なの♪";
		close;
	case 6:
		mes "[ユメヒメ]";
		mes "時間って残酷よねえ。";
		mes "年はとるし、昔は大人気だった";
		mes "劇場のダンサー志望者も減る一方。";
		mes "おかげで、満員御礼だった";
		mes "劇場の運営もすっかり";
		mes "火の車なの……。";
		next;
		mes "[ユメヒメ]";
		mes "今じゃそんな劇場だけど";
		mes "私の夢が詰まった場所だし";
		mes "閉鎖してほしくないのよ。";
		mes "だから私がこの大会で、";
		mes "よい成績をあげれば、";
		mes "劇場のPRも可能になるでしょ♪";
		next;
		mes "[ユメヒメ]";
		mes "戦いに不慣れな私だけど、";
		mes "踊りと、劇場への情熱だけは";
		mes "誰にも負けるつもりはないわ♪";
		mes "あなたもこの大会に出た以上、";
		mes "誰にも負けない気持ちだけは";
		mes "忘れちゃダメよ～♪";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "ユメヒメ : 優勝者と戦えて光栄だわ～♪　土産話にしなくっちゃね！";
			end;
		case 1:
			unittalk "ユメヒメ : うふふ、まさかあの子が優勝しちゃうなんて……人は見かけによらないわね。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "ユメヒメ : いや～ん、負けちゃった！　やっぱり30代になると動きが鈍るのかしら……やだわぁ……。";
		if(Sex == 0)	unittalk "ユメヒメ : これが若さの差なのかしら!?　お姉さん、ショックだわ……。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "ユメヒメ : ううーん、この熱気！　やっぱり大会も、ダンスホールと同様、ムード作りも大事よね♪";
		if(Sex == 0) unittalk "ユメヒメ : 可愛いお嬢さんが多いけど、ダンサー志望の子は居なさそう……。";
		end;
	case 1:
		if(Sex == 1) unittalk "ユメヒメ : やっぱり、大会に参加することお客さんくらいには、いうべきだったかしら……。";
		if(Sex == 0) unittalk "ユメヒメ : 女の子をつい、ダンサーの杓子定規で見ちゃうわ……。だめねえ。";
		end;
	case 2:
		if(Sex == 1) unittalk "ユメヒメ : ダンスの練習以外でこんなにがんばったの久しぶりだわ～。";
		if(Sex == 0) unittalk "ユメヒメ : ダンサーをやっていると、どうしても体型の維持が大変なのよね。";
		end;
	}
}

1@gef.gat,178,91,4	script	ジュー#z1	679,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",13);
		set '@str$[0],"こんにちは";
		if('@prog >= 1) set '@str$[1],"雑談する";
		if('@prog >= 2) set '@str$[2],"魔法に詳しそうですね";
		if('@prog >= 4) set '@str$[3],"ベテランの雰囲気を感じます";
		if('@prog >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[ジュー]";
			mes "ゲフェン魔法大会という大舞台で、";
			mes "優勝してしまうとは。";
			mes "腕前だけでなく、";
			mes "精神も鍛えているようだな。";
			mes "またいつか、一戦交えようぞ。";
			close;
		}
		if(checkquest(9309)) {
			mes "[ジュー]";
			mes "うむ、見事だ。";
			mes "あの若さでこれだけ動ける者が";
			mes "いるとはな……。";
			mes "これでこそ、この大会に参加した";
			mes "価値があるというものだ。";
			close;
		}
		mes "[ジュー]";
		mes "拙者は、ジューと申す。";
		mes "今回、この大会に出場する権利を";
		mes "幸運にも得ることができた1人だ。";
		mes "しかし、スカーフをつけていると";
		mes "熱がこもって暑いな……。";
		mes "だが、外すわけには……。";
		close;
	case 3:
		mes "[ジュー]";
		mes "ううむ、さすがに腹が減ったな。";
		mes "とはいえ、時間的にまだ";
		mes "妻の作ってくれた弁当を";
		mes "食べるわけにいかぬ……。";
		next;
		mes "[ジュー]";
		mes "腹が減っては魔法は撃てぬとは";
		mes "言い得て妙なものだ。";
		mes "それに、腹が減っているせいか";
		mes "頭が働かず、あの御仁のことが";
		mes "まったく思い出せぬ……。";
		mes "困ったものだ……。";
		close;
	case 4:
		mes "[ジュー]";
		mes "ほう……。";
		mes "なかなか見る目があるようだな。";
		mes "いかにも、魔法に関して";
		mes "今も勉学に励む身だ。";
		next;
		mes "[ジュー]";
		mes "長年、魔法の研究をしているのだが";
		mes "研究者が実戦経験がないことには";
		mes "結局、絵に描いたおもちだと";
		mes "気づくようになってな。";
		mes "やはり何事も自分で一度";
		mes "経験することが大事だ。";
		next;
		mes "[ジュー]";
		mes "そういった経緯から25歳のときに";
		mes "全世界を回って、戦いに明け暮れた。";
		mes "その中の相手に、イフォドス殿も";
		mes "含まれていたようで、声をかけてきたが";
		mes "戦った記憶がないのだよ……。";
		mes "ううーむ、どうしたものか。";
		close;
	case 5:
		mes "[ジュー]";
		mes "そなたとは何度か手合わせをしている";
		mes "気がするのに思い出せぬとは……。";
		mes "やはり妻がいったように、";
		mes "たまには研究以外にも";
		mes "目をむけるべきか……。";
		next;
		mes "[ジュー]";
		mes "すまない。";
		mes "拙者がベテランに見えるという";
		mes "話だったか。";
		mes "なにをもってベテランというのか";
		mes "わからぬのだが……。";
		next;
		mes "[ジュー]";
		mes "拙者は長年、実戦に重点をおいた";
		mes "戦いばかりしてきたせいか、";
		mes "相手もまた、命を賭した戦いが多く";
		mes "壮絶な戦いになったこともある。";
		mes "かといって、本当に命を奪うのは";
		mes "ナンセンスな行為と考える。";
		next;
		mes "[ジュー]";
		mes "命を懸けないと強くなれないと";
		mes "いう輩も稀にいるが、強さは";
		mes "命あってのものであり、";
		mes "拙者からするとそれ以外では";
		mes "自分は弱いと、言い訳して";
		mes "いるように聞えるのだよ。";
		next;
		mes "[ジュー]";
		mes "もしかするとそういった経験が";
		mes "いまの拙者の雰囲気を";
		mes "作り出しているのかもしれん。";
		close;
	case 6:
		mes "[ジュー]";
		mes "40という節目をむかえた際";
		mes "拙者はいまの妻と結婚、";
		mes "冒険は一旦、休止した。";
		mes "あれから2年……。";
		mes "もし拙者がこれまで誰かの";
		mes "命を奪っていた場合……";
		next;
		mes "[ジュー]";
		mes "今頃、後悔に悩まされながら";
		mes "暮らしていたかもしれないし";
		mes "この大会に、最後の腕試しにと";
		mes "出場する気にならなかったかも";
		mes "しれない……。";
		next;
		mes "[ジュー]";
		mes "そう思うと、拙者は本当に";
		mes "ついていると思うのだ。";
		mes "腕試しの最後にこのような";
		mes "晴れ舞台で思う存分、";
		mes "誰にも気兼ねすることなく";
		mes "暴れることが出来るのだからな。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "ジュー : あやつ、ゲフェン魔法大会という大舞台で優勝するとは……将来が楽しみだな。";
			end;
		case 1:
			unittalk "ジュー : 優勝劣敗……まさしくこの言葉通りの大会だったな。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "ジュー : 流石に、ぬるま湯に浸りすぎたか……優勝すらできぬとはな。";
		if(Sex == 0)	unittalk "ジュー : ……勝者に性別など、やはり関係ないのだな。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "ジュー : どうせなら男同士、力と力をぶつけ合いたいものだ。";
		if(Sex == 0) unittalk "ジュー : 存外、女性のほうが侮れない可能性が高い。今一度、眦を決するべきだな。";
		end;
	case 1:
		if(Sex == 1) unittalk "ジュー : 拙者の相手は誰になるか、楽しみだ。";
		if(Sex == 0) unittalk "ジュー : 女性がこのような大会に出場するなど、以前は考えられなかったことだな。";
		end;
	case 2:
		if(Sex == 1) unittalk "ジュー : 妻は今頃家で、拙者の無事を祈っているのだろうか……。";
		if(Sex == 0) unittalk "ジュー : ふむ……女性の出場者も存外、多いのだな。";
		end;
	}
}

1@gef.gat,113,99,4	script	ディワイ#z1	680,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",14);
		set '@str$[0],"こんにちは";
		if(GMT_121COUNT >= 1) set '@str$[1],"雑談する";
		if(GMT_121COUNT >= 2) set '@str$[2],"ウンバラに行ったことがあるのですか？";
		if(GMT_121COUNT >= 4) set '@str$[3],"なんだかソワソワしてますね";
		if(GMT_121COUNT >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[ディワイ]";
			mes "あのフェンリルを打ち負かし、";
			mes "優勝するとは……。";
			mes "君の実力は本当に計り知れないのだな。";
			mes "私も今後はより一層、";
			mes "腕に磨きをかけようと思う。";
			close;
		}
		if(checkquest(9309)) {
			mes "[ディワイ]";
			mes "何もいうことがないほどに、";
			mes "素晴らしい戦いだった。";
			mes "今回の大会の観覧者に、私が";
			mes "世話になった育ての親が来ているんだ。";
			mes "あの人たちの前で、あのような戦いを";
			mes "おこなえたことに感謝だな。";
			close;
		}
		mes "[ディワイ]";
		mes "私の名はディワイ。";
		mes "どうやら君も、参加者のようだね。";
		mes "しかし君は肝が据わっている。";
		mes "敵となるかもしれない私に";
		mes "こうして声をかけるのだから。";
		mes "気に入ったよ。";
		close;
	case 3:
		mes "[ディワイ]";
		mes "しかし、最近は……";
		mes "先生と呼ばれることが多かったせいか";
		mes "名前だけ呼ばれても気づかなくてね。";
		mes "危うく、久しぶりに会う人が";
		mes "名前を呼んでくれたのに";
		mes "気づかないところだったよ。";
		next;
		mes "[ディワイ]";
		mes "あと、自分よりも若いものに";
		mes "ついつい、指導者の口調で";
		mes "話してしまう……。";
		mes "もし君にも、私の口調や態度が";
		mes "尊大に見えたら申し訳ない。";
		close;
	case 4:
		mes "[ディワイ]";
		mes "おや。";
		mes "ウータン族という言葉で";
		mes "ピンときたのかな？";
		mes "ウンバラには行ったことが";
		mes "あるというよりある意味、";
		mes "私の第二の故郷でね。";
		next;
		mes "[ディワイ]";
		mes "幼少期は、ウンバラで過ごしたが";
		mes "もともと私はゲフェン生まれでね。";
		mes "生まれ故郷の大きな大会に、";
		mes "ウンバラの皆たちや弟子たちの";
		mes "応援を受けながら出場出来るとは";
		mes "夢にも思わなかったよ。";
		next;
		mes "[ディワイ]";
		mes "その分、プレッシャーが";
		mes "ないわけではないんだが、";
		mes "それすらも味方に";
		mes "出来ないようでは流石に";
		mes "指導者の名折れだからね。";
		mes "勝ちにいくつもりだよ。";
		close;
	case 5:
		mes "[ディワイ]";
		mes "君はもしや……。";
		mes "私の授業に来たことはあるだろうか。";
		mes "いや、すまない。";
		mes "なんだか君とは初対面の感じが";
		mes "しなかったものでね。";
		mes "私の勘違いだろうか……。";
		next;
		mes "[ディワイ]";
		mes "うむ。開始時間が近づくにつれ、";
		mes "今頃、会場入りしているであろう";
		mes "ウンバラ原住民と族長様が";
		mes "どこで見守ってくださっているのか";
		mes "気になってしかたがなくてな……。";
		mes "まるで子供だな、私は。";
		next;
		mes "[ディワイ]";
		mes "ウンバラ原住民と族長が";
		mes "実質的には育ての親でね。";
		mes "本当の親は2人とも他界したんだ。";
		mes "バンジージャンプの事故でね。";
		mes "でもその事故がなければ";
		mes "今の私は居なかっただろうね。";
		close;
	case 6:
		mes "[ディワイ]";
		mes "私がこの大会に出た真の目的。";
		mes "それは、ウンバラ原住民と";
		mes "族長様に、今の自分の実力を";
		mes "全て惜しみなく出し、";
		mes "見て頂くことで感謝の気持ちを";
		mes "伝えようと思ってね。";
		next;
		mes "[ディワイ]";
		mes "ウータン族はバンジージャンプを";
		mes "成功させてこそ、大人と認められる。";
		mes "だから私もそれにならってみたんだ。";
		mes "我ながらよいタイミングで";
		mes "よいことを思いついたなと思うよ。";
		next;
		mes "[ディワイ]";
		mes "結果も出せれば最高だが、";
		mes "私としてはウンバラ原住民のみんなと";
		mes "族長様が満足できなければ意味が";
		mes "ないからね……。";
		mes "何はともあれ全身全霊で";
		mes "ぶつからせてもらうよ。";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "ディワイ : さすが魔法大会。よい意味で、優勝者の予想を裏切られた。";
			end;
		case 1:
			unittalk "ディワイ : 優勝者には今度、うちの魔法学校で臨時講師をお願いしたい限りだな。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "ディワイ : 今回の優勝者の実力から、優勝は納得だな。";
		if(Sex == 0)	unittalk "ディワイ : 何もいうことがないほどに、決勝戦は素晴らしい戦いだった。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "ディワイ : この大会に参加した経験も、授業に生かさねば。";
		if(Sex == 0)	unittalk "ディワイ : いやはや、今日は一人の参加者として来ているのに、つい授業のことを考えてしまう。";
		end;
	case 1:
		if(Sex == 1) unittalk "ディワイ : 流石に大会中の開始前の挨拶を、ウータン語でしてはまずいだろうな……。";
		if(Sex == 0)	unittalk "ディワイ : 族長、ウータン族、弟子の皆はもう中に居るのだろうか。";
		end;
	case 2:
		if(Sex == 1) unittalk "ディワイ : 族長、ウータン族、弟子の皆はどこにいるのだろう……。";
		if(Sex == 0)	unittalk "ディワイ : 見た感じ、弟子たちよりも若い参加者もいるようだな……。";
		end;
	}
}

1@gef.gat,117,72,6	script	フェイ・カナビアン#z1	665,5,5,{
	setarray '@str$,"","","","","";
	if(checkquest(9308) || checkquest(9309)) {
		set '@str$[0],"雑談する";
	} else {
		set '@prog,callfunc("#魔法大会進行度",15);
		set '@str$[0],"こんにちは";
		if(GMT_122COUNT >= 1) set '@str$[1],"雑談する";
		if(GMT_122COUNT >= 2) set '@str$[2],"ホムンクルスでなにか悩んでるみたいだね";
		if(GMT_122COUNT >= 4) set '@str$[3],"何かにおうの？";
		if(GMT_122COUNT >= 7) set '@str$[4],"どうして大会に？";
	}
	mes "‐大会参加者のようだ";
	mes "　話しかけてみようか‐";
	next;
	switch(select("やめる",'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4])) {
	case 1:
		mes "‐やっぱりやめておこう‐";
		close;
	case 2:
		if(checkquest(9308)) {
			mes "[フェイ・カナビアン]";
			mes "ねえねえ、優勝者の";
			mes "ホムンクルスを作りたいんだ！";
			mes "だから君の髪の毛なり、";
			mes "爪のかけらなり、くれない？";
			mes "優勝祝いに、あたしに頂戴ー！";
			close;
		}
		if(checkquest(9309)) {
			mes "[フェイ・カナビアン]";
			mes "え？";
			mes "あたしが負けたの!?";
			mes "嘘だ～……！";
			mes "負ける方程式はないはずだよ？";
			mes "あたしが優勝するパターンだよ？";
			mes "絶対おかしいよ!?";
			close;
		}
		mes "[フェイ・カナビアン]";
		mes "あたしに声をかけるとは！";
		mes "君、なかなか見る目あるよ～！";
		mes "あたしは今をときめく錬金術師！";
		mes "フェイ・カナビアンだよ！";
		mes "ホムンクルス大好きっ子！";
		mes "よっろしくぅ～♪";
		close;
	case 3:
		mes "[フェイ・カナビアン]";
		mes "この大会が終わったら……";
		mes "うーん、2日後に講義か～。";
		mes "そして次の日も講義。";
		mes "次の日も、次の日も講義っと。";
		mes "やれやれ、大変だよ～！";
		mes "うん？　どうかした？";
		next;
		mes "[フェイ・カナビアン]";
		mes "え？　補習の講義じゃないよ。";
		mes "あたしが壇上で話す講義だよ～！";
		mes "こう見えて、あたしの講義は";
		mes "予約殺到の大人気なんだよ～！";
		mes "凄いでしょ～？";
		mes "もっと褒めていいよ？";
		close;
	case 4:
		mes "[フェイ・カナビアン]";
		mes "んーんー……。";
		mes "新しいホムンクルスはどんな子に";
		mes "しようかな～？";
		mes "非常食やおやつになるような";
		mes "ホムンクルスとか!?";
		mes "あ、だめだ～。";
		next;
		mes "[フェイ・カナビアン]";
		mes "多分、作ってる最中に";
		mes "あたしがぱくぱく味見して";
		mes "完成するころにはもう";
		mes "原型なくなってそうだよ～！";
		mes "うん、他のホムンクルスに";
		mes "しておこうっと！";
		close;
	case 5:
		mes "[フェイ・カナビアン]";
		mes "なんとなく君からあたしの";
		mes "ホムンクルスの匂いがする気が……。";
		mes "くんくん……。";
		mes "うーん、気のせいかなあ。";
		next;
		mes "[フェイ・カナビアン]";
		mes "君とも、どこかで会ったような……。";
		mes "あーもう！";
		mes "全然わからなーい！";
		mes "でもホムンクルスの匂いなら";
		mes "嗅ぎ分ける自信はあるんだよ～！";
		mes "っていうのも。";
		next;
		mes "[フェイ・カナビアン]";
		mes "ホムンクルスは作成者が使う";
		mes "素材によって独特の匂いがあるんだよ。";
		mes "まあ、当代最高のホムンクルスを";
		mes "作ったあたしにしか分からないほど";
		mes "かすかな匂いなんだけどね！";
		mes "だから君にはわからないはず。";
		next;
		mes "[フェイ・カナビアン]";
		mes "アルデバランの錬金術師の仲間も";
		mes "この匂いはわからないんだよね～。";
		mes "こういう時、あたしみたいな天才は";
		mes "大抵理解を得られないんだよね。";
		mes "まっ、あたしには自慢のあの子が";
		mes "いるからいいんだけどね～！";
		close;
	case 6:
		mes "[フェイ・カナビアン]";
		mes "ここで問題で～す。";
		mes "あたしがこの大会に出場を決めた";
		mes "理由はなんでしょうか！";
		mes "30秒以内に答えてね！";
		mes "30……29……28……。";
		next;
		mes "[フェイ・カナビアン]";
		mes "答えは、あたしが作った最高傑作の";
		mes "ホムンクルスのあの子の素晴らしさを";
		mes "この大会でお披露目するためでした！";
		mes "あたしが精魂こめて作った子なんだよ♪";
		mes "能力はもとより、見た目とかにも";
		mes "あたしが拘った子だよ～！";
		next;
		mes "[フェイ・カナビアン]";
		mes "君と大会で戦うことになるかは";
		mes "わからないのが残念だけど……。";
		mes "もし戦うことになったら";
		mes "あたしのあの子の良さを";
		mes "独り占めできるよ～！";
		mes "良かったね～♪";
		close;
	}
OnTouch:
	if(checkquest(9308)) {
		switch(rand(2)) {
		case 0:
			unittalk "フェイ・カナビアン : あの人が優勝する要素なんて、どう計算しても出なかったのになあ！";
			end;
		case 1:
			unittalk "フェイ・カナビアン : ……優勝者のホムンクルス、作ってみたいなあ。";
			end;
		}
	}
	if(checkquest(9309)) {
		if(Sex == 1) unittalk "フェイ・カナビアン : ……おかしい！　こんな結果、ありえないのにー！";
		if(Sex == 0)	unittalk "フェイ・カナビアン : うーん、これはもしかして夢？　でも痛かったし……。あたしが負けるなんて、ありえないのになあ。";
		end;
	}
	switch(rand(3)) {
	case 0:
		if(Sex == 1) unittalk "フェイ・カナビアン : みんなちゃんと、チケット使ってあたしの優勝するとこ見に来てくれたかなー。";
		if(Sex == 0)	unittalk "フェイ・カナビアン : うーん、ペアのホムンクルスとかも、楽しそうだなあ……。";
		end;
	case 1:
		if(Sex == 1) unittalk "フェイ・カナビアン : 優勝したら、美味しいものを食べようかな～？　なにがいいだろ～！";
		if(Sex == 0)	unittalk "フェイ・カナビアン : あたしが優勝したら、同性からの嫉妬が怖そうだなあ……。まっ、いいか！";
		end;
	case 2:
		if(Sex == 1) unittalk "フェイ・カナビアン : あの子の出番、ちゃんとあるかなあ……。あの子のデビューの日なのに、出番がなかったら意味がないし。";
		if(Sex == 0)	unittalk "フェイ・カナビアン : へぇ、参加者にも結構女の子がいるんだ～。";
		end;
	}
}

1@gef.gat,115,201,4	script	不思議な看板#1	857,{
	mes "‐何を見ようか‐";
	next;
	switch(select("キャラクター","応援")) {
	case 1:
		setarray '@menu$,"アルヒ","ディオ・アネモス","フェモン","オルドル","ブルート・ハゼ","黒魔","イフォドス","レチェニエ","ユメヒメ","ジュー","ディワイ","フェイ・カナビアン","見るのをやめる";
		while(1) {
			set '@select,select(printarray('@menu$));
			if('@select == 13) {
				mes "‐見るのをやめた‐";
				close;
			}
			mes "[不思議な看板]";
			mes '@menu$['@select];
			set '@prog,callfunc("#魔法大会進行度",'@select);
			set '@talk,4;
			if('@prog >= 1) '@talk--;
			if('@prog >= 2) '@talk--;
			if('@prog >= 4) '@talk--;
			if('@prog >= 7) '@talk--;
			if('@talk > 0) {
				mes "　";
				mes "まだ聞く事が出来ない話が";
				mes "　"+ '@talk +"　ほどあるようだ。";
			}
			if('@talk == 0) {
				mes "^ff0000コンプリート^000000";
				mes "　";
				mes "‐全ての話を確認出来る状態だ‐";
			}
			next;
		}
	case 2:
		setarray '@str$,"未確認","未確認","未確認","未確認","未確認";
		if(checkquest(114700) & 0x8) {
			set '@str$[0],"怪しい男";
			'@comp++;
		}
		if(checkquest(114701) & 0x8) {
			set '@str$[1],"変な歌を歌う少女";
			'@comp++;
		}
		if(checkquest(114702) & 0x8) {
			set '@str$[2],"戦い好きのマスター";
			'@comp++;
		}
		if(checkquest(114703) & 0x8) {
			set '@str$[3],"夢中な猫";
			'@comp++;
		}
		if(checkquest(114704) & 0x8) {
			set '@str$[4],"騎士";
			'@comp++;
		}
		mes "[不思議な看板]";
		mes "‐応援状況‐";
		if('@comp == 5) {
			mes "　";
			mes "^ff0000コンプリート^000000";
		}
		next;
		set '@sel,select('@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4],"見るのをやめる") - 1;
		if('@sel == 5) {
			mes "‐見るのをやめた‐";
			close;
		}
		set '@quest,114700 + '@sel;
		if(checkquest('@quest) && checkquest('@quest) & 0x8) {
			mes "‐あなたは既に";
			mes "　"+ '@str$['@sel] +"の";
			mes "　応援を受けた事があるようだ‐";
			close;
		} else {
			mes "‐まだ見たことがない人のようだ‐";
			close;
		}
	}
}

//==========================================
// その他
//------------------------------------------
1@gef.gat,36,123,6	script	案内要員#1	705,{
	cutin "gef_soldier.bmp", 2;
	mes "[ゲフェン魔法大会案内人]";
	mes "魔法の都市^8B4513ゲフェン^000000へ";
	mes "ようこそ！";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "現在はゲフェン魔法大会が開催中で";
	mes "出し物や催し物が多くあります。";
	mes "^006400魔法大会^000000への参加をお望みなら";
	mes "ゲフェン6時方向にある";
	mes "噴水台に行ってみてください。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "また魔法大会開催を記念して";
	mes "ゲフェンのあちこちに魔法の花火が";
	mes "設置されていますので退屈することは";
	mes "ないと思います。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "歴史と伝統が息づく";
	mes "ゲフェン魔法大会は冒険者の皆さんを";
	mes "決して失望させません！";
	mes "それでは楽しい観光になりますよう！";
	close2;
	cutin "gef_soldier.bmp", 255;
	end;
}

1@gef.gat,123,203,4	script	案内要員#2	705,{
	cutin "gef_soldier.bmp", 2;
	mes "[ゲフェン魔法大会案内人]";
	mes "魔法の都市^8B4513ゲフェン^000000へ";
	mes "ようこそ！";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "現在はゲフェン魔法大会が開催中で";
	mes "出し物や催し物が多くあります。";
	mes "^006400魔法大会^000000への参加をお望みなら";
	mes "ゲフェン6時方向にある";
	mes "噴水台に行ってみてください。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "また魔法大会開催を記念して";
	mes "ゲフェンのあちこちに魔法の花火が";
	mes "設置されていますので退屈することは";
	mes "ないと思います。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "歴史と伝統が息づく";
	mes "ゲフェン魔法大会は冒険者の皆さんを";
	mes "決して失望させません！";
	mes "それでは楽しい観光になりますよう！";
	close2;
	cutin "gef_soldier.bmp", 255;
	end;
}

1@gef.gat,203,116,4	script	案内要員#4	705,{
	cutin "gef_soldier.bmp", 2;
	mes "[ゲフェン魔法大会案内人]";
	mes "魔法の都市^8B4513ゲフェン^000000へ";
	mes "ようこそ！";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "現在はゲフェン魔法大会が開催中で";
	mes "出し物や催し物が多くあります。";
	mes "^006400魔法大会^000000への参加をお望みなら";
	mes "ゲフェン6時方向にある";
	mes "噴水台に行ってみてください。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "また魔法大会開催を記念して";
	mes "ゲフェンのあちこちに魔法の花火が";
	mes "設置されていますので退屈することは";
	mes "ないと思います。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "歴史と伝統が息づく";
	mes "ゲフェン魔法大会は冒険者の皆さんを";
	mes "決して失望させません！";
	mes "それでは楽しい観光になりますよう！";
	close2;
	cutin "gef_soldier.bmp", 255;
	end;
}

1@gef.gat,116,203,5	script	案内要員#5	705,{
	viewpoint 1, 166, 168, 1, 0x32CD32;
	viewpoint 1, 72, 169, 2, 0x0000FF;
	viewpoint 1, 114, 143, 3, 0xFF8000;
	cutin "gef_soldier.bmp", 2;
	mes "[ゲフェン魔法大会案内人]";
	mes "魔法の都市^8B4513ゲフェン^000000へ";
	mes "ようこそ！";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "現在、ゲフェン魔法大会に乗じて";
	mes "^ff0000悪事を企む輩^000000が";
	mes "出没しているようです。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "^32cd32東側^000000には不良が、";
	mes "^FF8000南側^000000には泥棒が、";
	mes "^0000FF西側^000000にはごろつきが、";
	mes "それぞれ目撃されているようです。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "我々も警戒は行っていますが、";
	mes "ご注意ください！";
	close2;
	cutin "gef_soldier.bmp", 255;
	end;
}

1@gef.gat,116,203,5	script(HIDDEN)	案内要員#6	705,{
	cutin "gef_soldier.bmp", 2;
	mes "[ゲフェン魔法大会案内人]";
	mes "今回のゲフェン魔法大会は";
	mes "終了しました。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "ご来場いただきまして、";
	mes "誠にありがとうございます。";
	mes "お楽しみいただけたでしょうか。";
	next;
	mes "[ゲフェン魔法大会案内人]";
	mes "ゲフェン魔法大会運営一同、";
	mes "皆様に楽しんでいただけるよう、";
	mes "さらに精進してまいりますので、";
	mes "次回開催時もご期待ください！";
	close2;
	cutin "gef_soldier.bmp", 255;
	end;
}

1@gef.gat,124,173,4	script	ゲフェン男性#a1	49,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
		unittalk "ゲフェン住民 : この機会にいい出会いがあるといいな……。";
		end;
	case 1:
		unittalk "ゲフェン住民 : 魔法大会の季節になると人が多いな～。";
		end;
	case 2:
		unittalk "ゲフェン住民 : この歳で未だに独身……さびしい……。";
		end;
	}
}

1@gef.gat,194,91,4	script	ゲフェン子供#a2	82,5,5,{
	end;
OnTouch:
	switch(rand(3)) {
	case 0:
		unittalk "ゲフェン子供 : つまらない！　お祭りなのに！";
		end;
	case 1:
		unittalk "ゲフェン子供 : 何か楽しいことはないかな！";
		end;
	case 2:
		unittalk "ゲフェン子供 : パパにおこづかいもらおっと！";
		end;
	}
}

1@gef.gat,71,86,4	script	ゲフェン娘#a3	478,{}
1@gef.gat,73,84,4	script	ゲフェン娘#a4	879,{}
1@gef.gat,75,82,4	script	ゲフェン娘#a5	92,{}
1@gef.gat,68,79,6	script	イケメン冒険者#a6	751,{}
1@gef.gat,70,77,2	script	男冒険者#a7	869,{
	end;
OnTimer1000:
	hideonnpc getmdnpcname("イケメン冒険者#a6");
	hideonnpc getmdnpcname("男冒険者#a7");
	end;
OnTimer2000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 寂しいわ……人ごみが多いから余計に寂しい。";
	end;
OnTimer4000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : なに怖いこと言ってるの！";
	end;
OnTimer6000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : ゲフェンに来る冒険者にはいい男もいるはずよ！　逆ナンパするのよ！";
	end;
OnTimer8000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : いい男なんてどこにもいないし！";
	end;
OnTimer10000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 脳ミソまで筋肉で出来てるようなおじさん達しか見えないわよ！";
	end;
OnTimer12000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : だからって花盛りの私たちの青春をさびしく過ごすなんて……。";
	end;
OnTimer14000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : いいえ、希望を捨ててはいけない……あきらめないで！　みんな！";
	end;
OnTimer16000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : ふう……そうだね。";
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : はあ……そうだね。";
	end;
OnTimer18000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : うん？　え！　あっち！　あっちにいい男！";
	end;
OnTimer20000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : あら！　どこに！";
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : え？　どこ？　どこ？";
	end;
OnTimer21000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : ほら！　あの人、あの人！";
	hideoffnpc getmdnpcname("イケメン冒険者#a6");
	end;
OnTimer23000:
	unittalk getnpcid(0,getmdnpcname("イケメン冒険者#a6")),"イケメン冒険者 : さすがに魔法大会だからかな……かわいい人が多いな……。";
	end;
OnTimer24000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : きゃー！　かっこいい！";
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : あれ、絶対あたしに言ったのよ！";
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : キャー！　かっこいいわ！";
	end;
OnTimer26000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : ど、どうしよ……話しかけてみる？";
	end;
OnTimer28000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : それはあなたが専門じゃない！　早く話しかけてみてよ！";
	end;
OnTimer30000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 早く！　誰か話しかけてよ！";
	end;
OnTimer32000:
	unittalk getnpcid(0,getmdnpcname("イケメン冒険者#a6")),"イケメン冒険者 : もうそろそろ来るはずなんだけどな……。";
	end;
OnTimer34000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : !!　……誰かを待ってるみたい。";
	end;
OnTimer36000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : もしかして彼女?!";
	end;
OnTimer38000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : そんなのダメ～!!";
	hideoffnpc getmdnpcname("男冒険者#a7");
	end;
OnTimer40000:
	unittalk getnpcid(0,getmdnpcname("男冒険者#a7")),"男冒険者 : ごめん、待たせた？";
	end;
OnTimer42000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : 良かった！　男よ。";
	end;
OnTimer44000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : ただの友達みたい！";
	end;
OnTimer46000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 二人ともいいお・と・こ！";
	end;
OnTimer48000:
	unittalk getnpcid(0,getmdnpcname("イケメン冒険者#a6")),"イケメン冒険者 : 全然！　そんなことないよ、マイハニー！";
	emotion 3,getmdnpcname("イケメン冒険者#a6");
	end;
OnTimer49000:
	emotion 23, getmdnpcname("ゲフェン娘#a3");
	emotion 23, getmdnpcname("ゲフェン娘#a4");
	emotion 23, getmdnpcname("ゲフェン娘#a5");
	end;
OnTimer51000:
	emotion 3, getmdnpcname("イケメン冒険者#a6");
	unittalk getnpcid(0,getmdnpcname("男冒険者#a7")),"男冒険者 : ダーリン……。";
	emotion 3, getmdnpcname("男冒険者#a7");
	end;
OnTimer53000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : 私たちには縁なんてないみたい……。";
	end;
OnTimer54000:
	emotion 3, getmdnpcname("イケメン冒険者#a6");
	end;
OnTimer55000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : しょせんこんなオチだと思ったわよ……。";
	emotion 3, getmdnpcname("男冒険者#a7");
	end;
OnTimer57000:
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 私たちの友情よ、永遠に！";
	emotion 3, "イケメン冒険者#a6";
	end;
OnTimer58000:
	emotion 3, getmdnpcname("男冒険者#a7");
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a3")),"ゲフェン娘 : 私たちの友情よ、永遠に！";
	emotion 28, getmdnpcname("ゲフェン娘#a3");
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a4")),"ゲフェン娘 : 私たちの友情よ、永遠に！";
	emotion 28, getmdnpcname("ゲフェン娘#a4");
	unittalk getnpcid(0,getmdnpcname("ゲフェン娘#a5")),"ゲフェン娘 : 私たちの友情よ、永遠に！";
	emotion 28, getmdnpcname("ゲフェン娘#a5");
	end;
OnTimer60000:
	emotion 3, getmdnpcname("イケメン冒険者#a6");
	end;
OnTimer61000:
	emotion 3, getmdnpcname("男冒険者#a7");
	end;
OnTimer64000:
	emotion 3, getmdnpcname("男冒険者#a7");
	end;
OnTimer90000:
OnStart:
	initnpctimer;
	end;
}

1@gef.gat,42,102,6	script	ゲフェン住人#a8	50,{
	mes "[ゲフェン住人]";
	mes "魔法大会の季節は観光客で賑わうな！";
	close;
}

1@gef.gat,103,100,6	script	ゲフェン住人#a9	54,{
	mes "[ゲフェン住人]";
	mes "おなかへったな～。";
	close;
}

1@gef.gat,128,93,4	script	ゲフェン住人#a10	979,{
	mes "[ゲフェン住人]";
	mes "大会参加者の選手さんかい？";
	mes "大会を盛り上げてくれて";
	mes "ありがとうね～！";
	close;
}

1@gef.gat,130,196,6	script	魔法大会観覧者#c5	46,{
	mes "[魔法大会観覧者]";
	mes "!!";
	mes "なんと！　魔法のような花火だな！";
	mes "どんな仕組みで動いているのか";
	mes "気になるぞ……。";
	close;
}

1@gef.gat,137,190,6	script	魔法大会観覧者#c6	67,{
	mes "[魔法大会観覧者]";
	mes "おばあちゃん！";
	mes "綺麗な花火が沢山あがってるよ！";
	close;
}

1@gef.gat,149,196,6	script	魔法大会観覧者#c8	47,{
	mes "[魔法大会観覧者]";
	mes "人ごみは苦手だけど、";
	mes "魔法大会は見たい……。";
	mes "私はどうしたらいいんだ！";
	close;
}

1@gef.gat,136,188,6	script	魔法大会観覧者#c10	771,{
	mes "[魔法大会観覧者]";
	mes "ホホホ……";
	mes "そんなにはしゃいで、";
	mes "転ばないようにね。";
	close;
}

1@gef.gat,110,195,4	script	魔法大会観覧者#c12	49,{
	mes "[魔法大会観覧者]";
	mes "賑わってるな～。";
	close;
}

1@gef.gat,104,189,4	script	魔法大会観覧者#c14	66,{
	mes "[魔法大会観覧者]";
	mes "どうしよう～。";
	mes "友達とはぐれちゃったよ～。";
	close;
}

1@gef.gat,94,194,4	script	魔法大会観覧者#c16	68,{
	mes "[魔法大会観覧者]";
	mes "さすが魔法大会！";
	mes "すごいな～、";
	mes "そこら中に魔法の花火があがってる！";
	close;
}

1@gef.gat,52,155,6	script	魔法大会観覧者#c28	69,{
	mes "[魔法大会観覧者]";
	mes "あの人の髪色ステキ！";
	mes "わたしも染めちゃおうかしら～。";
	close;
}

1@gef.gat,55,142,4	script	魔法大会観覧者#c30	70,{
	mes "[魔法大会観覧者]";
	mes "お兄様！　早くいらしてくださいな！";
	close;
}

1@gef.gat,58,146,4	script	魔法大会観覧者#c32	51,{
	mes "[魔法大会観覧者]";
	mes "ちょ、ちょっとまってくれよ～！";
	mes "楽器が重くて走れないんだ～！";
	close;
}

1@gef.gat,45,149,6	script	魔法大会観覧者#c36	71,{
	mes "[魔法大会観覧者]";
	mes "!!";
	mes "なんだか視線を感じるわ！";
	mes "殿方に見られてるのかしら！";
	close;
}

1@gef.gat,44,133,6	script	魔法大会観覧者#c37	52,{
	mes "[魔法大会観覧者]";
	mes "ウォオオオ～！";
	mes "ワシも参加したかったぞ～！";
	close;
}

1@gef.gat,45,126,6	script	魔法大会観覧者#c38	48,{
	mes "[魔法大会観覧者]";
	mes "こんにちは。";
	mes "絶好の魔法大会日和ですね。";
	close;
}

1@gef.gat,44,118,6	script	魔法大会観覧者#c39	73,{
	mes "[魔法大会観覧者]";
	mes "あなたも魔法大会には初めて来たの？";
	close;
}

1@gef.gat,55,113,4	script	魔法大会観覧者#c40	74,{
	mes "[魔法大会観覧者]";
	mes "お祭りはいくつになっても心躍るわ～！";
	close;
}

1@gef.gat,50,107,6	script	魔法大会観覧者#c41	54,{
	mes "[魔法大会観覧者]";
	mes "いい天気だなー。";
	close;
}

1@gef.gat,44,95,6	script	魔法大会観覧者#c42	55,{
	mes "[魔法大会観覧者]";
	mes "次はどこに行こうかのう。";
	mes "賑やかで楽しいのう～。";
	close;
}

1@gef.gat,52,83,6	script	魔法大会観覧者#c43	56,{
	mes "[魔法大会観覧者]";
	mes "シッ！　静かに！";
	mes "私は観覧者に紛れて、";
	mes "ここの警備をしているのだ。";
	mes "気づかれないよう協力してくれ。";
	close;
}

1@gef.gat,72,65,6	script	魔法大会観覧者#c44	57,{
	mes "[魔法大会観覧者]";
	mes "おやおや！　君は！";
	mes "……ん？";
	mes "おお、すまない。人違いの様だ。";
	mes "知り合いの冒険者によく似ている。";
	close;
}

1@gef.gat,83,60,6	script	魔法大会観覧者#c45	75,{
	mes "[魔法大会観覧者]";
	mes "あれ～……。";
	mes "二人ともいつの間にか";
	mes "いなくなっちゃった……。";
	mes "はぐれちゃったかなぁ。";
	close;
}

1@gef.gat,94,68,6	script	魔法大会観覧者#c46	76,{
	mes "[魔法大会観覧者]";
	mes "どこ行っちゃったんだろう……。";
	mes "あっ、あそこ見て！";
	mes "あの子じゃない？";
	close;
}

1@gef.gat,97,66,4	script	魔法大会観覧者#c47	77,{
	mes "[魔法大会観覧者]";
	mes "ほんと！　あの子だわ！";
	mes "やっと見つけた～！";
	mes "こう人が多いとはぐれちゃうね。";
	mes "気を付けないと！";
	close;
}

1@gef.gat,106,56,6	script	魔法大会観覧者#c48	78,{
	mes "[魔法大会観覧者]";
	mes "お祭りはいいわねぇ～。";
	mes "若者が多くて活気があるわねぇ～。";
	mes "私も若返っちゃうわぁ～。";
	close;
}

1@gef.gat,134,63,4	script	魔法大会観覧者#c49	58,{
	mes "[魔法大会観覧者]";
	mes "あっ、あの娘！";
	mes "かわいいなぁ、ひとりかなぁ。";
	mes "声かけてみようかなぁ……。";
	close;
}

1@gef.gat,145,47,4	script	魔法大会観覧者#c50	106,{
	mes "[魔法大会観覧者]";
	mes "おや？　参加者の方ですか？";
	mes "私は観覧者に変装して";
	mes "ここの警備をしているのですよ。";
	mes "ほかのお客様には内緒ですよ。";
	close;
}

1@gef.gat,154,55,4	script	魔法大会観覧者#c51	59,{
	mes "[魔法大会観覧者]";
	mes "あなたも大会の参加者ですか？";
	mes "カッコイイなぁ……！";
	mes "僕も次は頑張って参加してみようかな！";
	close;
}

1@gef.gat,147,65,5	script	魔法大会観覧者#c52	60,{
	mes "[魔法大会観覧者]";
	mes "麗しい女性がいらっしゃいますなぁ。";
	mes "おっと、いけないいけない。";
	mes "聖職者たるもの、";
	mes "女性をそのような目で";
	mes "みてはいけませんね。";
	close;
}

1@gef.gat,163,76,4	script	魔法大会観覧者#c53	79,{
	mes "[魔法大会観覧者]";
	mes "神父様ったら、";
	mes "どこにいっちゃったんだろう。";
	mes "綺麗な女性が好きだから、";
	mes "女性の多い所にいると思うんだけど。";
	close;
}

1@gef.gat,167,68,4	script	魔法大会観覧者#c54	80,{
	mes "[魔法大会観覧者]";
	mes "食事もおいしいし、";
	mes "魔法大会は楽しいねぇ！";
	mes "まだまだ食べちゃうぞ～！";
	close;
}

1@gef.gat,175,74,4	script	魔法大会観覧者#c55	947,{
	mes "[魔法大会観覧者]";
	mes "お主はもう大会参加者に会ったか？";
	mes "今年の魔法大会は";
	mes "つわものぞろいらしいぞ！";
	close;
}

1@gef.gat,180,84,4	script	魔法大会観覧者#c56	53,{
	mes "[魔法大会観覧者]";
	mes "こんにちは！";
	mes "魔法大会、楽しんでる？";
	mes "私はとっても楽しいわ！";
	mes "ちょっと遠かったけど、";
	mes "頑張って来た甲斐があるわ！";
	close;
}

1@gef.gat,189,97,4	script	魔法大会観覧者#c57	62,{
	mes "[魔法大会観覧者]";
	mes "わーい！";
	mes "一緒に遊ぼうよー！";
	close;
}

1@gef.gat,194,110,4	script	魔法大会観覧者#c58	107,{
	mes "[魔法大会観覧者]";
	mes "うう～ん、腹が減って動けん！";
	mes "しかし、この店には";
	mes "鍋しか売っていない！";
	mes "うう～ん……。";
	close;
}

1@gef.gat,185,107,6	script	魔法大会観覧者#c59	108,{
	mes "[魔法大会観覧者]";
	mes "魔法大会が見たくて";
	mes "こっそり抜け出してきたのだ！";
	mes "どうだ、私の完璧な変装。";
	mes "誰にもばれるまい！";
	close;
}

1@gef.gat,189,120,4	script	魔法大会観覧者#c60	61,{
	mes "[魔法大会観覧者]";
	mes "あっ、あなた！";
	mes "王様の恰好をした変なおじさんを";
	mes "見かけませんでしたか?!";
	close;
}

1@gef.gat,152,120,4	script	魔法大会観覧者#c62	123,{
	mes "[魔法大会観覧者]";
	mes "たのしいな～！";
	mes "次はどっちにいこう！";
	close;
}

1@gef.gat,138,110,4	script	魔法大会観覧者#c63	90,{
	mes "[魔法大会観覧者]";
	mes "見て、この花火！";
	mes "こんなに近くで燃えているのに、";
	mes "全く熱くないのよ。";
	mes "魔法ってすごいわね。";
	close;
}

1@gef.gat,128,99,4	script	魔法大会観覧者#c64	91,{
	mes "[魔法大会観覧者]";
	mes "こんにちは！";
	mes "私ゲフェンって初めて来たの！";
	mes "ステキな街ね！";
	close;
}

1@gef.gat,105,109,6	script	魔法大会観覧者#c65	92,{
	mes "[魔法大会観覧者]";
	mes "うわぁ……。";
	mes "人が多くて目が回りそう……。";
	close;
}

1@gef.gat,96,122,6	script	魔法大会観覧者#c66	93,{
	mes "[魔法大会観覧者]";
	mes "こんにちは！";
	mes "お祭りたのしいねぇ！";
	close;
}

1@gef.gat,132,137,6	script	魔法大会観覧者#c67	920,{
	mes "[魔法大会観覧者]";
	mes "こんなに人がいるなんて！";
	mes "魔法大会って人気なんですね。";
	close;
}

1@gef.gat,141,132,4	script	魔法大会観覧者#c68	806,{
	mes "[魔法大会観覧者]";
	mes "おやおや、冒険者さん。";
	mes "ばれてしまいましたか？";
	mes "私は観覧者に変装して";
	mes "ここの警備をしているのですよ。";
	mes "怪しい人物がいたら教えてくださいね。";
	close;
}

1@gef.gat,124,72,4	script	魔法大会観覧者#c69	807,{
	mes "[魔法大会観覧者]";
	mes "こんにちは、いいお天気ですね。";
	mes "お祭りですからね。";
	mes "晴れて良かったです。";
	close;
}

1@gef.gat,130,49,6	script	魔法大会観覧者#c70	808,{
	mes "[魔法大会観覧者]";
	mes "あなた強そうですね。";
	mes "魔法大会の参加者の方ですか？";
	mes "私とちょっと";
	mes "肩慣らししませんか？";
	mes "ハハハ……。冗談ですよ。";
	close;
}

1@gef.gat,127,196,0	script	#魔法大会花火_1	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 30;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 29;
	end;
}

1@gef.gat,146,175,0	script	#魔法大会花火_2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 62;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 22;
	end;
}

1@gef.gat,182,163,0	script	#魔法大会花火_3	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 89;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 74;
	end;
}

1@gef.gat,183,126,0	script	#魔法大会花火_4	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 97;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 92;
	end;
}

1@gef.gat,194,89,0	script	#魔法大会花火_5	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 234;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 225;
	end;
}

1@gef.gat,141,56,0	script	#魔法大会花火_6	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 256;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 258;
	end;
}

1@gef.gat,127,49,0	script	#魔法大会花火_7	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 257;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 244;
	end;
}

1@gef.gat,123,75,0	script	#魔法大会花火_8	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 92;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 29;
	end;
}

1@gef.gat,135,111,0	script	#魔法大会花火_9	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 62;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 30;
	end;
}

1@gef.gat,134,145,0	script	#魔法大会花火_10	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 234;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 89;
	end;
}

1@gef.gat,90,197,0	script	#魔法大会花火_b1	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 28;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 258;
	end;
}

1@gef.gat,71,181,0	script	#魔法大会花火_b2	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 97;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 29;
	end;
}

1@gef.gat,62,147,0	script	#魔法大会花火_b3	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 195;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 116;
	end;
}

1@gef.gat,59,125,0	script	#魔法大会花火_b4	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 32;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 62;
	end;
}

1@gef.gat,62,91,0	script	#魔法大会花火_b5	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 92;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 30;
	end;
}

1@gef.gat,98,58,0	script	#魔法大会花火_b6	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 225;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 234;
	end;
}

1@gef.gat,112,49,0	script	#魔法大会花火_b7	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 28;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 89;
	end;
}

1@gef.gat,116,75,0	script	#魔法大会花火_b8	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 257;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 94;
	end;
}

1@gef.gat,107,111,0	script	#魔法大会花火_b9	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 244;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 255;
	end;
}

1@gef.gat,106,145,0	script	#魔法大会花火_b10	139,{
OnStart:
	initnpctimer;
	end;
OnTimer7000:
	misceffect 92;
	end;
OnTimer20000:
	initnpctimer;
	misceffect 195;
	end;
}

1@gef.gat,124,65,4	script	カプラ職員#gef	114,{
	mes "[カプラ職員]";
	mes "いらっしゃいませ";
	mes "カプラサービスは";
	mes "いつも皆様のそばにいます。";
	mes "何をお手伝いいたしましょう？";
	next;
	switch(select("倉庫サービス -> 40zeny","カートサービス","終了")) {
	case 1:
		if(basicskillcheck() && getskilllv(1)<6 && getskilllv(5018)<1 ) {
			mes "[カプラ職員]";
			mes "倉庫は基本スキルレベル6を";
			mes "習得してから利用可能となります。";
		}
		if(Zeny < 40) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りません。";
			mes "倉庫利用料金は40Zenyです。";
			close;
		}
		mes "[カプラ職員]";
		mes "倉庫を開きます。";
		close2;
		set Zeny,Zeny-40;
		openstorage;
		end;
	case 2:
		if(getbaseclass(Class) != CLASS_MC && Job != Job_SuperNovice && Job != Job_ExpandedSuperNovice) {
			mes "[カプラ職員]";
			mes "申し訳ございません。";
			mes "カートは商人とその上位職専用の";
			mes "サービスです。";
			close;
		}
		if(checkcart()) {
			mes "[カプラ職員]";
			mes "お客様は現在カートを";
			mes "利用されています。";
			close;
		}
		mes "[カプラ職員]";
		mes "カート利用料金は800Zenyです。";
		mes "また、カートを利用するには";
		mes "「プッシュカート」スキルが必要です。";
		mes "そのスキルがないとカートを利用";
		mes "できずにお金だけ消えてしまいます。";
		mes "準備はよろしいですか？";
		next;
		if(select("利用する","取り消し")==2) {
			mes "[カプラ職員]";
			mes "ありがとうございました。";
			mes "またご利用くださいませ。";
			close;
		}
		if(Zeny<800) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りません。";
			mes "カート利用料金は800Zenyです。";
			close;
		}
		set Zeny,Zeny-800;
		set KAFRA_PIT,KAFRA_PIT+80;
		setcart;
		close;
	case 3:
		mes "[カプラ職員]";
		mes "我々カプラサービスは、より完璧な";
		mes "サービスと管理業務を目指し";
		mes "お客様が安心してご利用いただけるよう";
		mes "いつも最善を尽くしています。";
		next;
		mes "[カプラ職員]";
		mes "（株）カプラサービスをご利用いただき";
		mes "ありがとうございました。";
		close;
	}
}

1@gef.gat,196,111,3		shop	料理材料商人#gef	85,7482
1@gef_in.gat,30,178,4	shop	武器商人#gefa		47,1750,1751,1101,1701,1201,1204,1207,1210,1213,1216,1601,1604,1607,1610
1@gef_in.gat,26,178,4	shop	防具商人#gef		66,2628,2101,2107,2401,2501,2230,2301,2303,2305,2321,2332
1@gef_in.gat,74,144,0	shop	商人#gef			66,911,910,912
1@gef_in.gat,77,167,0	shop	道具商人 #gefa		68,1750,611,501,502,503,504,645,656,601,602,2241
1@gef_in.gat,77,173,0	shop	魔法商人#gef		64,717,1601,1604,1607,1610,2232,2321,2332

1@gef.gat,193,152,4	script	テイミング商人#gef	124,{
	mes "[テイミング商人]";
	mes "申し訳御座いません、お客様。";
	mes "ただいま商品の在庫を";
	mes "切らしております。";
	mes "次回の入荷につきましては";
	mes "未定となっております。";
	close;
}

1@gef_in.gat,110,172,0	script	クリストフ・ジュニア#1	63,{
	mes "[クリストフ・ジュニア]";
	mes "^8B4513クリストフ家^000000の";
	mes "鍛冶屋へようこそ。";
	mes "ここでは精錬に関連した";
	mes "全ての品物を販売したり";
	mes "製作をしています。";
	next;
	mes "[クリストフ・ジュニア]";
	mes "今はゲフェン祭の期間中につき";
	mes "臨時休業となっています。";
	mes "楽しいお祭が終わった後に";
	mes "またお越しください。";
	close;
}

1@gef.gat,182,59,0		warp	#gef_a1	2,2,1@gef_in.gat,106,177
1@gef.gat,43,85,0		warp	#gef_a2	2,2,1@gef_in.gat,70,138
1@gef_in.gat,106,181,0	warp	#gef_a3	2,2,1@gef.gat,178,63
1@gef_in.gat,70,132,0	warp	#gef_a4	2,2,1@gef.gat,46,88
1@gef_in.gat,70,158,0	warp	#gef_a5	2,2,1@gef_in.gat,70,146
1@gef_in.gat,70,149,0	warp	#gef_a6	2,2,1@gef_in.gat,70,161
1@gef_in.gat,28,156,0	warp	#gef_a7	2,2,1@gef.gat,101,138
1@gef.gat,98,141,0		warp	#gef_a8	2,2,1@gef_in.gat,28,160
