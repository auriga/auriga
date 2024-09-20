//==============================================================================
// Nightmare Jitterbug Memorial Script
//==============================================================================
// JTB_1QUE：0～24まで。ワープポイントの発生フラグ。会話の切り替え。部屋番号を格納。
// JTB_2QUE：0～7まで。険しい道のボス撃破後イベント用。
// JTB_COUNT：0～10まで。周回カウント。外伝用。
// JTB_DAILY：0～2まで。アイグ、メロディージャックの依頼用。

//==========================================
// 楽園団 (1)
//------------------------------------------
moc_para01.gat,26,95,5	script	ロエル#sara	10040,{
	cutin "roel01.bmp", 0;
	mes "[ロエル]";
	mes "何か御用ですか？";
	next;
	switch(select("ダンジョンの探索","ペンダントの交換","ジターバグの牙の交換")) {
	case 1:
		if(Job < Job_RuneKnight || (BaseLevel <= 89 && Job == Job_Summoner)) {
			mes "[ロエル]";
			mes "新たに冒険を共にしてくれる方を";
			mes "探しているのですが、";
			mes "厳しい戦いになりますので";
			mes "相応の経験を積んでいる方に";
			mes "限らせて貰っています。";
			next;
			cutin "roel01.bmp", 255;
			mes "‐進行可能な職業は";
			mes "　3次職業および限界突破した";
			mes "　スーパーノービスのような";
			mes "　レベル拡張をした職業と、";
			mes "　BaseLv90以上のドラム族です‐";
			close;
		}
		if(checkquest(13183)) {
			cutin "roel02.bmp", 0;
			mes "[ロエル]";
			mes strcharinfo(0)+ "さんの";
			mes "おかげでシャルロシーと";
			mes "友達になる事が出来ました。";
			next;
			mes "[ロエル]";
			mes "結局、最後は別れてしまいましたが";
			mes "きっと、また会えると信じています。";
			mes "本当にありがとうございました。";
			delquest 13183;
			setquest 13181;
			delquest 13181;
			setquest 116509;
			compquest 116509;
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		if(checkquest(13181) & 0x8 && checkquest(116508) & 0x8 ) {
			cutin "roel01.bmp", 0;
			mes "[ロエル]";
			mes "ご協力ありがとうございました。";
			mes "やはりシャルロシーと解りあうのは";
			mes "無理なんでしょうか……。";
			mes "なんて、弱気はダメですよね！";
			mes "大事なギルドメンバーのためです！";
			mes "次も頑張りましょう！";
			delquest 13181;
			setquest 116509;
			compquest 116509;
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		if(checkquest(13181)) {
			mes "[ロエル]";
			mes "どうしたのですか？";
			mes "準備が出来たら隣にいる";
			mes "ルナインさんに話しかけて下さい。";
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		if(checkquest(116508) & 0x8) {
			mes "[ロエル]";
			mes "初めてシャルロシーと出会った";
			mes "あの冒険以来、";
			mes "不思議な事がありました。";
			next;
			mes "[ロエル]";
			mes "詳しいことはわかりませんが、";
			mes "ルナインさんのワープポータルが";
			mes "場所だけではなく、時間も一緒に";
			mes "記憶していたらしいんです。";
			next;
			mes "[ロエル]";
			mes "つまり、シャルロシーと出会った";
			mes "あの時のあの場所へ、";
			mes "もう一度行けるという事です！";
			next;
			mes "[ロエル]";
			mes "シャルロシーも本当は";
			mes "みんなと一緒に";
			mes "ここへ帰ってきたかったはずです。";
			next;
			mes "[ロエル]";
			mes "もう一度シャルロシーに会えば、";
			mes "最後に別れずにすむ方法が";
			mes "見つかるかもしれません。";
			next;
			mes "[ロエル]";
			mes "もし、ご迷惑でなければ";
			mes "もう一度一緒にあの空間に行き、";
			mes "シャルロシーを救う手助けを";
			mes "してもらえませんか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "[ロエル]";
				mes "そうですか。";
				close2;
				cutin "roel01.bmp", 255;
				end;
			}
			mes "[ロエル]";
			mes "準備が出来たら隣にいる";
			mes "ルナインさんに話しかけて下さい。";
			setquest 13181;
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		mes "[ロエル]";
		mes "はじめまして。";
		mes "ニュオーズの白羽ギルドのメンバー、";
		mes "ロエルです！";
		next;
		mes "[ロエル]";
		mes "僕たちは前ギルドマスターの";
		mes "ニュオーズ様が発見したという、";
		mes "未知のダンジョンの探索へ出発します。";
		next;
		mes "[ロエル]";
		mes "しかし、そこは不可解な場所のため";
		mes "より多くの戦力を確保したいと思い、";
		mes "臨時のギルド員を";
		mes "募集することにしました。";
		mes "よかったら参加して頂けませんか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[ロエル]";
			mes "そうですか……残念です。";
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		cutin "roel02.bmp", 0;
		mes "[ロエル]";
		mes "ありがとうございます。";
		mes "ニュオーズ様というのは";
		mes "^FF0000ニュオーズの白羽ギルド^000000の";
		mes "前ギルドマスターです。";
		next;
		cutin "roel01.bmp", 0;
		mes "[ロエル]";
		mes "彼は冒険が好きで、";
		mes "常に新しい街やダンジョンを求め";
		mes "あちこちへ旅立ってしまうので、";
		mes "ギルドメンバーでさえもなかなか";
		mes "彼に会うことはできなかったんです。";
		next;
		mes "[ロエル]";
		mes "そんなニュオーズ様から、";
		mes "ある日一通の手紙が届きました。";
		mes "これがその手紙です。";
		next;
		mes "‐あなたは手紙を受け取り、開いた‐";
		next;
		mes "^FF0000‐ギルドのみんなへ";
		mes "　";
		mes "　^FF0000やっほ～！　みんな元気にしてる？";
		mes "　^FF0000私は毎日とっても元気だよ！";
		mes "　^FF0000冒険の先々で新しいモノに出会って";
		mes "　^FF0000とっても楽しいよ～。‐^000000";
		next;
		mes "^FF0000‐そうそう、冒険の途中で面白そうな";
		mes "　^FF0000ダンジョンを見つけたんだ。";
		mes "　^FF0000とっても不思議な雰囲気で、";
		mes "　^FF0000たぶんまだ誰にも発見されていない";
		mes "　^FF0000未知の場所だと思うんだ!!";
		mes "　^FF0000すごいよね～！‐^000000";
		next;
		mes "^FF0000‐それでね、";
		mes "　^FF0000誰も入ったことのない場所なら";
		mes "　^FF0000最初にみんなで探検したいなって";
		mes "　^FF0000思ったんだ！　と、いうわけなので";
		mes "　^FF0000みんな早く来てね！　待ってるよ～!!";
		mes "　";
		mes "　^FF0000ニュオーズより‐^000000";
		next;
		mes "‐読み終えた手紙をロエルに手渡した‐";
		next;
		mes "[ロエル]";
		mes "この手紙を見て僕は、";
		mes "ニュオーズ様の";
		mes "^0000FFギルドメンバーみんなで";
		mes "^FF0000未知のダンジョンの最初の探索に";
		mes "^FF0000出かけたい^000000という想いに、";
		mes "とても感動したのです！";
		next;
		mes "[ロエル]";
		mes "だけど、現マスターのロテルト様は";
		mes "散々心配をかけさせやがって！　と、";
		mes "すごく怒っていました。";
		mes "ロテルト様はニュオーズ様の事となると";
		mes "いつも怒ってばかりなんです。";
		next;
		mes "[ロエル]";
		mes "怒ってはいますが、";
		mes "きっとロテルト様は";
		mes "ニュオーズ様が本当に心配なんです。";
		mes "お二人は付き合いが長いそうですし、";
		mes "ケンカするほど";
		mes "仲が良いと言いますしね。";
		next;
		mes "[ロエル]";
		mes "さあ、そろそろ時間です。";
		mes "ニュオーズ様を";
		mes "お待たせするわけにはいきません。";
		mes "ニュオーズ様が指定した集合場所は、";
		mes "ルナインさんのワープポータルで";
		mes "記録してあります。";
		next;
		mes "[ロエル]";
		mes "準備が出来たら隣にいる";
		mes "ルナインさんに話しかけて下さい。";
		setquest 13181;
		close2;
		cutin "roel01.bmp", 255;
		end;
	case 2:
		cutin "roel01.bmp", 0;
		mes "[ロエル]";
		mes "^ff0000ペンダントオブハーモニー[0]^000000と";
		mes "^ff0000ペンダントオブカオス[0]^000000という";
		mes "アクセサリーを";
		mes "お持ちではありませんか？";
		next;
		mes "[ロエル]";
		mes "2つのアクセサリーと";
		mes "ジターバグの牙50個があると";
		mes "アクセサリーを^ff0000合成^000000出来るんです。";
		next;
		mes "[ロエル]";
		mes "2つを合成すると、、";
		mes "凄まじい性能になるって";
		mes "ミンミンさんが言ってました。";
		mes "確か性能はこんな感じです。";
		next;
		mes "[ペンダントオブメイルストーム[1]]";
		mes "All Status + 1";
		mes "物理・魔法攻撃で";
		mes "与えるダメージ + 6%";
		mes "魔法攻撃を受けた時、";
		mes "一定確率でオートスペル";
		mes "[メイルストーム]Lv1発動";
		mes "系列：アクセサリー";
		mes "防御：0";
		mes "重量：10";
		mes "要求レベル：130";
		mes "装備：三次職";
		next;
		mes "[ロエル]";
		mes "僕はこのペンダントを一目見たくて、";
		mes "ミンミンさんに頼んで";
		mes "合成の方法を教えてもらったのですが、";
		mes "全ての材料を揃えるのは";
		mes "とても難しくて……。";
		next;
		mes "[ロエル]";
		mes "もし、二つとも集められたら";
		mes "僕のところに持って来てください。";
		mes "僕はペンダントが見られれば";
		mes "それで満足なので、";
		mes "完成品は差し上げます！";
		close2;
		cutin "roel01.bmp", 255;
		end;
	case 3:
		cutin "roel01.bmp", 0;
		mes "[ロエル]";
		mes "ジターバグから手に入る";
		mes "ジターバグの牙……。";
		mes "もしかして持っていますか？";
		next;
		mes "[ロエル]";
		mes "研究に使える材料らしく、";
		mes "ミンミンさんに持って来いと";
		mes "頼まれてしまいまして……。";
		next;
		mes "[ロエル]";
		mes "ですが、なかなか集まらなくて";
		mes "困っていたところなんです！";
		next;
		mes "[ロエル]";
		mes "もし良かったら、";
		mes "ニュオーズ様が過去に集めていた";
		mes "戦利品と交換しませんか？";
		next;
		mes "[ロエル]";
		mes "戦利品の中にあるのは……";
		mes "ギガントボウ、嵐の弓、あとは……";
		mes "冒険に役立つアイテムから";
		mes "ニュオーズ様の想い出の品まで！";
		mes "色々あるみたいですよ。";
		next;
		mes "[ロエル]";
		mes "ジターバグの牙を^FF00002個^000000集めて来たら";
		mes "^FF0000戦利品の中からランダムで^000000";
		mes "^FF0000ひとつと交換しましょう。^000000";
		next;
		if(select("やめる","交換する")==1) {
			mes "[ロエル]";
			mes "そうですか……。";
			mes "残念です。";
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		if(countitem(6719) < 2) {
			mes "[ロエル]";
			mes "おや、数が足りないようですね。";
			mes "交換には^FF0000ジターバグの牙^000000が";
			mes "^FF00002個^000000必要です。";
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		mes "[ロエル]";
		mes "確かに2個ありますね。";
		mes "では、これをお渡ししましょう。";
		next;
		cutin "roel02.bmp", 0;
		mes "[ロエル]";
		mes "大事に使ってくださいね。";
		mes "牙をもっと集めてきたら";
		mes "また交換しましょう！";
		delitem 6719,2;
		// イグドラシルの実、イグドラシルの種、古いカード帖、スプレンディッドコイン、大量のどんぐり、宝箱、ギガントボウ、嵐の弓、ニュオーズのウクレレ
		// 凍てついたプレート、ハードプレート、アイグの花飾りマイク、力のグローブ、知力のグローブ、敏捷のグローブ
		// 体力のグローブ、器用さのグローブ、幸運のグローブ、ニュオーズの翼リング、アイグの花飾りブレスレット、ペンダントオブハーモニー
		setarray '@nameid,607,608,616,6081,6558,7444,18122,18123,1935,15100,15101,1990,2917,2918,2919,2920,2921,2922,2988,2989,2990;
		setarray '@amount,3,5,1,10,100,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
		setarray '@rate,50,50,30,150,80,200,10,40,20,20,20,20,30,20,20,20,20,80,20,20,10;
		set '@max,0;
		for(set '@i,0; '@i < getarraysize('@nameid); set '@i,'@i+1) set '@max,'@max+'@rate['@i];
		set '@rand,rand('@max);
		for(set '@i,0; '@i < getarraysize('@nameid); set '@i,'@i+1) {
			if('@i > 0)
				set '@rate['@i],'@rate['@i] + '@rate['@i-1];
			if('@rand < '@rate['@i]) {
				getitem '@nameid['@i],'@amount['@i];
				break;
			}
		}
		close2;
		cutin "roel02.bmp", 255;
		end;
	}
}

moc_para01.gat,29,95,5	script	ルナイン#sara	10039,{
	if(Job < Job_RuneKnight || (BaseLevel <= 89 && Job == Job_Summoner)) {
		cutin "lunain01.bmp", 0;
		mes "[ルナイン]";
		mes "あなたもダンジョンの探索に";
		mes "参加したいの？";
		mes "でも、今のあなたじゃ力不足ね。";
		mes "もう少し強くなってから来なさい。";
		next;
		cutin "lunain01.bmp", 255;
		mes "‐進行可能な職業は";
		mes "　3次職業および限界突破した";
		mes "　スーパーノービスのような";
		mes "　レベル拡張をした職業と、";
		mes "　BaseLv90以上のドラム族です‐";
		close;
	}
	if(checkquest(13181) ==0) {
		cutin "lunain01.bmp", 0;
		mes "[ルナイン]";
		mes "こんにちは。";
		mes "なにか聞きたそうな顔をしているわね。";
		next;
		mes "[ルナイン]";
		mes "私達は今から";
		mes "とある場所の探索へ行くのよ。";
		mes "詳しく知りたいなら";
		mes "横にいる^ff0000ロエル^000000に話を聞くといいわ。";
		close2;
		cutin "lunain01.bmp", 255;
		end;
	}
	if(checkquest(116509) & 0x8) {
		cutin "lunain01.bmp", 0;
		mes "[ルナイン]";
		mes "こんにちは。";
		mes "今日はどうするの？";
		set '@str$,"外伝を見る";
	} else {
		cutin "lunain01.bmp", 0;
		mes "[ルナイン]";
		mes "ロエルに話をきいてきたみたいね。";
		mes "私はニュオーズの白羽ギルドのメンバー";
		mes "^ff0000ルナイン^000000よ。";
		next;
		mes "[ルナイン]";
		mes "あなたも一緒に行くのね。";
		mes "準備はいいかしら？";
	}
	next;
	switch(select("ダンジョンに行く",'@str$,"やめる")) {
	case 1:
		if(checkquest(13182)) {
			if(checkquest(13182) & 0x2 && checkquest(118906) & 0x2) {
				mes "[ルナイン]";
				mes "次元ワープを使用することが";
				mes "可能になったわ。";
				delquest 13182;
				delquest 118906;
				close2;
				cutin "lunain01.bmp", 255;
				end;
			}
			mes "[ルナイン]";
			mes "今は次元ワープが使えないわ。";
			mes "入場してから次の^ff0000午前5時以降^000000に";
			mes "また来てね。";
			next;
			mes "[ルナイン]";
			mes "あと、午前5時以降だったとしても";
			mes "最後の入場をしてから";
			mes "^ff00001時間^000000経過していない場合は";
			mes "次元ワープを使えないから注意しなさい。";
			close2;
			cutin "lunain01.bmp", 255;
			end;
		}
		if(checkquest(13181) & 0x8) {
			mes "[ルナイン]";
			mes "^ff0000次元のワープ^000000を利用するなら、";
			mes "先にロエルと話をして来なさい。";
			mes "誰にでも利用させる訳には行かないの。";
			close2;
			cutin "lunain01.bmp", 255;
			end;
		}
		if(getonlinepartymember() < 1) {
			mes "[ルナイン]";
			mes "^ff0000パーティーを結成^000000していないと";
			mes "この先には進めないわよ。";
			close2;
			cutin "lunain01.bmp", 255;
			end;
		}
		set '@party$,getpartyname(getcharid(1));
		mes "[ルナイン]";
		mes "ワープポータルはいつでも開けるけど";
		mes "どうするの？";
		next;
		mes "^ff0000‐メモリアルダンジョン作成後に^000000";
		mes "　パーティーリーダーを変更した場合";
		mes "　正常に進行できない場合が";
		mes "　ありますのでご注意ください‐";
		next;
		if(getpartyleader(getcharid(1))==strcharinfo(0)) {
			switch(select("次元のワープを準備","悪夢のジターバグ入場","キャンセル")) {
			case 1:
				if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
					mes "パーティー名："+ '@party$;
					mes "^0000ffjitterbug ^000000-予約失敗";
					close2;
					cutin "lunain01.bmp", 255;
					end;
				}
				if(getonlinepartymember() < 1) {
					mes "パーティー名："+ '@party$;
					mes "パーティーリーダー："+strcharinfo(0)+"";
					mes "^0000ffjitterbug ^000000-予約失敗";
					close2;
					cutin "lunain01.bmp", 255;
					end;
				}
				mes "[ルナイン]";
				mes "^ff0000次元のワープを準備するわ。";
				mes "^ff0000少しだけ待ってなさい。^000000";
				close2;
				mdcreate "jitterbug";
				cutin "lunain01.bmp", 255;
				end;
			case 2:
				mes "[ルナイン]";
				mes "わかったわ。";
				mes "ワープポータルを開くから";
				mes "入ってちょうだい。";
				next;
				mes "[ルナイン]";
				mes "この次元ワープは一度使うと";
				mes "入場してから次の^ff0000午前5時以降^000000になるまで";
				mes "もう一度使う事が出来ないの。";
				next;
				mes "[ルナイン]";
				mes "あと、午前5時以降だったとしても";
				mes "最後の入場をしてから";
				mes "^ff00001時間^000000経過していない場合は";
				mes "次元ワープを使えないから注意しなさい。";
				next;
				switch(mdenter("jitterbug")) {
				case 0:
					cutin "lunain01.bmp", 255;
					set JTB_1QUE,0;
					setquest 13182;
					setquest 118906;
					delquest 116500;
					misceffect 316,"";
					misceffect 317,"";
					announce "メモリアルダンジョン[jitterbug] に入場しました　：　" +strcharinfo(1)+ " ("+strcharinfo(0)+")", 0x9, 0x00ff99;
					donpcevent getmdnpcname("jitter_control1")+ "::OnStart";
					close;
				case 1:	// パーティー未加入
					mes "‐パーティー員のみ、";
					mes "　メモリアルダンジョンに";
					mes "　入場することができます‐";
					close;
				case 2:
					mes "[ルナイン]";
					mes "^ff0000パーティーリーダー^000000が";
					mes "^ff0000次元ワープ^000000を準備してないわ。";
					close2;
					cutin "lunain01.bmp", 255;
					end;
				default:	// その他エラー
					close;
				}
			case 3:
				mes "[ルナイン]";
				mes "やめるのね。わかったわ。";
				mes "準備ができたらまたきて。";
				close2;
				cutin "lunain01.bmp", 255;
				end;
			}
		}
		switch(select("悪夢のジターバグ入場","キャンセル")) {
		case 1:
			mes "[ルナイン]";
			mes "わかったわ。";
			mes "ワープポータルを開くから";
			mes "入ってちょうだい。";
			next;
			mes "[ルナイン]";
			mes "この次元ワープは一度使うと";
			mes "入場してから次の^ff0000午前5時以降^000000になるまで";
			mes "もう一度使う事が出来ないの。";
			next;
			mes "[ルナイン]";
			mes "あと、午前5時以降だったとしても";
			mes "最後の入場をしてから";
			mes "^ff00001時間^000000経過していない場合は";
			mes "次元ワープを使えないから注意しなさい。";
			next;
			switch(mdenter("jitterbug")) {
			case 0:
				cutin "lunain01.bmp", 255;
				set JTB_1QUE,0;
				setquest 13182;
				setquest 118906;
				delquest 116500;
				misceffect 316,"";
				misceffect 317,"";
				announce "メモリアルダンジョン[jitterbug] に入場しました　：　" +strcharinfo(1)+ " ("+strcharinfo(0)+")", 0x9, 0x00ff99;
				donpcevent getmdnpcname("jitter_control1")+ "::OnStart";
				close;
			case 1:	// パーティー未加入
				mes "‐パーティー員のみ、";
				mes "　メモリアルダンジョンに";
				mes "　入場することができます‐";
				close;
			case 2:
				mes "[ルナイン]";
				mes "^ff0000パーティーリーダー^000000が";
				mes "^ff0000次元ワープ^000000を準備してないわ。";
				close2;
				cutin "lunain01.bmp", 255;
				end;
			default:	// その他エラー
				close;
			}
		case 2:
			mes "[ルナイン]";
			mes "やめるのね。わかったわ。";
			mes "準備ができたらまたきて。";
			close2;
			cutin "lunain01.bmp", 255;
			end;
		}
	case 2:
		mes "[ルナイン]";
		mes "あのダンジョンの冒険中、";
		mes "あなたが見ていない場所で";
		mes "何が起こっていたのか、";
		mes "どんな会話がされていたのか";
		mes "気にならない？";
		next;
		mes "[ルナイン]";
		mes "私のワープポータルを使えば";
		mes "あなたが本来いなかった場所に";
		mes "送ってあげることができるわ。";
		next;
		mes "[ルナイン]";
		mes "詳しくはわからないけど";
		mes "^ff0000あのダンジョンから帰ってくるたびに^000000";
		mes "私のワープポータルに";
		mes "行先が増えてるのよね……。";
		next;
		while(1) {
			mes "[ルナイン]";
			mes "さあ、見てみたい話を選んで。";
			mes "その話が行われた場所、時間に";
			mes "送ってあげる。";
			next;
			setarray '@menu$,"^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","^808080未開放^000000","";
			switch(JTB_COUNT) {
			case 10:
				if(JTB_2QUE == 7) {
					if(checkquest(116530) & 0x8)
						set '@menu$[10],"？？？";
					else
						set '@menu$[10],"^ff0000？？？^000000";
				}
				if(checkquest(116529) & 0x8)
					set '@menu$[9],"見えない絆";
				else
					set '@menu$[9],"^0000ff見えない絆^000000";
			case 9:
				if(checkquest(116528) & 0x8)
					set '@menu$[8],"仲間以上恋愛未満？";
				else
					set '@menu$[8],"^0000ff仲間以上恋愛未満？^000000";
			case 8:
				if(checkquest(116527) & 0x8)
					set '@menu$[7],"不思議な共通点";
				else
					set '@menu$[7],"^0000ff不思議な共通点^000000";
			case 7:
				if(checkquest(116526) & 0x8)
					set '@menu$[6],"不穏な一言";
				else
					set '@menu$[6],"^0000ff不穏な一言^000000";
			case 6:
				if(checkquest(116525) & 0x8)
					set '@menu$[5],"シャルロシーの行方";
				else
					set '@menu$[5],"^0000ffシャルロシーの行方^000000";
			case 5:
				if(checkquest(116524) & 0x8)
					set '@menu$[4],"交わされた契約";
				else
					set '@menu$[4],"^0000ff交わされた契約^000000";
			case 4:
				if(checkquest(116523) & 0x8)
					set '@menu$[3],"キノコのお味は？";
				else
					set '@menu$[3],"^0000ffキノコのお味は？^000000";
			case 3:
				if(checkquest(116522) & 0x8)
					set '@menu$[2],"モンスターの落し物";
				else
					set '@menu$[2],"^0000ffモンスターの落し物^000000";
			case 2:
				if(checkquest(116521) & 0x8)
					set '@menu$[1],"弟子と師匠";
				else
					set '@menu$[1],"^0000ff弟子と師匠^000000";
			case 1:
				if(checkquest(116520) & 0x8)
					set '@menu$[0],"不名誉な疑惑";
				else
					set '@menu$[0],"^0000ff不名誉な疑惑^000000";
			case 0:
				break;
			}
			set '@x,0;
			set '@y,0;
			set '@i,select(printarray('@menu$));
			switch('@i) {
			case 1:
				if(JTB_COUNT >= '@i) {
					set '@x,198;
					set '@y,28;
				}
				break;
			case 2:
				if(JTB_COUNT >= '@i) {
					set '@x,292;
					set '@y,37;
				}
				break;
			case 3:
				if(JTB_COUNT >= '@i) {
					set '@x,111;
					set '@y,112;
				}
				break;
			case 4:
				if(JTB_COUNT >= '@i) {
					set '@x,209;
					set '@y,103;
				}
				break;
			case 5:
				if(JTB_COUNT >= '@i) {
					set '@x,285;
					set '@y,111;
				}
				break;
			case 6:
				if(JTB_COUNT >= '@i) {
					set '@x,26;
					set '@y,198;
				}
				break;
			case 7:
				if(JTB_COUNT >= '@i) {
					set '@x,106;
					set '@y,195;
				}
				break;
			case 8:
				if(JTB_COUNT >= '@i) {
					set '@x,282;
					set '@y,191;
				}
				break;
			case 9:
				if(JTB_COUNT >= '@i) {
					set '@x,25;
					set '@y,277;
				}
				break;
			case 10:
				if(JTB_COUNT >= '@i) {
					set '@x,110;
					set '@y,278;
				}
				break;
			case 11:
				if(JTB_COUNT >= '@i) {
					set '@x,28;
					set '@y,374;
				}
				break;
			}
			if('@x > 0 && '@y > 0) {
				if('@i <= 10) {
					mes "[ルナイン]";
					mes "わかったわ。";
					mes "ワープポータルを開くから";
					mes "入ってちょうだい。";
				} else {
					mes "[ルナイン]";
					mes "え……。";
					next;
					mes "[ルナイン]";
					mes "何かしら……";
					mes "何かに呼ばれてるような、";
					mes "不思議な力を感じるわ。";
					next;
					mes "[ルナイン]";
					mes "この感じ……";
					mes "もしかしたら、あの子が";
					mes "呼んでるのかも知れない。";
					next;
					cutin "lunain01.bmp", 0;
					mes "[ルナイン]";
					mes strcharinfo(0)+"。";
					mes "きっとあなたを呼んでるのね。";
					next;
					mes "[ルナイン]";
					mes "お願い、私がワープポータルを開くから";
					mes "あの子に会いに行ってあげて。";
				}
				misceffect 316,"";
				misceffect 317,"";
				close2;
				cutin "lunain01.bmp", 255;
				warp "jtb_01.gat",'@x,'@y;
				end;
			}
			mes "[ルナイン]";
			mes "ごめんなさい。";
			mes "今はそこに送れないみたい。";
			next;
			mes "[ルナイン]";
			mes "あのダンジョンを冒険してくれば";
			mes "もしかしたら、行けるように";
			mes "なるかも知れないわよ。";
			next;
			continue;
		}
	case 3:
		mes "[ルナイン]";
		mes "やめるのね。わかったわ。";
		mes "準備ができたらまたきて。";
		close2;
		cutin "lunain01.bmp", 255;
		end;
	}
OnInit:
	waitingroom "悪夢のジターバグ", 0;
	end;
}

//==========================================
// NPC、モンスター、ワープポータル：共通
//------------------------------------------
1@jtb.gat,0,1,0		script	jitter_control1	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("1番部屋出口#JTB");
	initnpctimer getmdnpcname("ニュオーズ#01");
	end;
}
1@jtb.gat,0,2,0		script	jitter_control2	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("2番部屋出口#JTB");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control2")+"::OnKilled";
	areamonster '@map$,111,23,116,25,"ペル",3069,3,'@label$;
	areamonster '@map$,120,16,122,21,"ペル",3069,2,'@label$;
	areamonster '@map$,127,32,131,34,"ペル",3069,3,'@label$;
	areamonster '@map$,114,42,116,43,"ペル",3069,2,'@label$;
	initnpctimer;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control2")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("1番部屋出口#JTB");
		hideoffnpc getmdnpcname("2番部屋出口#JTB");
		announce "‐先へ進む道が現れた。南東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	}
	end;
OnTimer3000:
	announce "ギルドメンバーの話によると、このダンジョンは非常に空間が不安定なようだ。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer6000:
	announce "部屋の全ての敵を倒すと、その部屋への入り口が消えてしまうらしい。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer9000:
	stopnpctimer;
	announce "パーティーメンバーとはぐれないよう、入口が消える前に移動しよう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
}
1@jtb.gat,0,3,0		script	jitter_control3	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("3番部屋出口#JTB");
	hideonnpc getmdnpcname("アイグ#03");
	hideonnpc getmdnpcname("ルナイン#03");
	hideonnpc getmdnpcname("？？？#03");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control3")+"::OnKilled";
	areamonster '@map$,200,27,202,31,"ペル",3069,3,'@label$;
	areamonster '@map$,206,42,217,46,"ペル",3069,5,'@label$;
	areamonster '@map$,212,22,214,24,"ペル",3069,6,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control3")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("2番部屋出口#JTB");
		//3番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("アイグ#03");
		hideoffnpc getmdnpcname("ルナイン#03");
		initnpctimer getmdnpcname("ルナイン#03");
	}
	end;
}

1@jtb.gat,45,47,0	script	1番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control2")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),100,14;
	end;
}

1@jtb.gat,135,17,0	script	2番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control3")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),184,17;
	end;
}

1@jtb.gat,220,23,0	script	3番部屋出口#JTB	45,2,2,{
OnTouch:
	switch(.Route) {
	case 1:
		donpcevent getmdnpcname("jitter_control4")+"::OnStart";
		warp getmdmapname("1@jtb.gat"),270,13;
		end;
	case 2:
		donpcevent getmdnpcname("jitter_control7")+"::OnStart";
		warp getmdmapname("1@jtb.gat"),183,128;
		end;
	}
}

//==========================================
// NPC、モンスター、ワープポータル：なだらかな道
//------------------------------------------
1@jtb.gat,0,4,0		script	jitter_control4	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("4番部屋出口#JTB");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control4")+"::OnKilled";
	areamonster '@map$,286,17,289,20,"ペル",3069,5,'@label$;
	areamonster '@map$,286,37,289,40,"ペル",3069,5,'@label$;
	areamonster '@map$,300,38,304,40,"ペル",3069,5,'@label$;
	areamonster '@map$,300,17,304,20,"ペル",3069,5,'@label$;
	initnpctimer;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control4")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("3番部屋出口#JTB");
		hideoffnpc getmdnpcname("4番部屋出口#JTB");
		announce "‐先へ進む道が現れた。北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	}
	end;
}
1@jtb.gat,0,5,0		script	jitter_control5	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("5番部屋出口#JTB");
	hideonnpc getmdnpcname("ロエル#05");
	hideonnpc getmdnpcname("ゲルカ#05");
	hideonnpc getmdnpcname("メロディージャック#05");
	hideonnpc getmdnpcname("アイグ#05");
	hideonnpc getmdnpcname("ルナイン#05");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control5")+"::OnKilled";
	areamonster '@map$,25,98,30,102,"ペル",3069,5,'@label$;
	areamonster '@map$,25,110,30,114,"ペル",3069,5,'@label$;
	areamonster '@map$,25,126,30,130,"ペル",3069,5,'@label$;
	areamonster '@map$,39,98,45,102,"ペル",3069,5,'@label$;
	areamonster '@map$,39,126,45,130,"ペル",3069,5,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control5")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("4番部屋出口#JTB");
		//5番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("アイグ#05");
		hideoffnpc getmdnpcname("ルナイン#05");
		initnpctimer getmdnpcname("ルナイン#05");
	}
	end;
}

1@jtb.gat,0,6,0		script	jitter_control6	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("6番部屋出口#JTB");
	hideonnpc getmdnpcname("ロエル#06");
	hideonnpc getmdnpcname("ゲルカ#06");
	hideonnpc getmdnpcname("ルナイン#06");
	hideonnpc getmdnpcname("メロディージャック#06");
	hideonnpc getmdnpcname("アイグ#06");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control6")+"::OnKilled";
	areamonster '@map$,104,115,106,118,"ペル",3069,5,'@label$;
	areamonster '@map$,113,94,115,97,"ペル",3069,5,'@label$;
	areamonster '@map$,113,113,115,115,"ペル",3069,5,'@label$;
	areamonster '@map$,113,129,116,131,"ペル",3069,5,'@label$;
	areamonster '@map$,125,108,128,112,"ペル",3069,5,'@label$;
	areamonster '@map$,115,117,117,119,"p・ジターバグ",3109,1,'@label$;
	initnpctimer;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control6")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("5番部屋出口#JTB");
		//6番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("ロエル#06");
		hideoffnpc getmdnpcname("ゲルカ#06");
		hideoffnpc getmdnpcname("ルナイン#06");
		hideoffnpc getmdnpcname("メロディージャック#06");
		hideoffnpc getmdnpcname("アイグ#06");
		initnpctimer getmdnpcname("アイグ#06");
	}
	end;
OnTimer3000:
	announce "やはり、ここも非常に空間が不安定なようだ。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer6000:
	announce "部屋の全ての敵を倒すと、この部屋への入り口が消えてしまうだろう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer9000:
	stopnpctimer;
	announce "パーティーメンバーとはぐれないよう、入口が消える前に移動しよう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
}

1@jtb.gat,306,47,0	script	4番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control5")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),11,102;
	end;
}

1@jtb.gat,39,133,0	script	5番部屋出口#JTB	45,2,2,{
OnTouch:
	mes "‐これまでの戦闘で得た";
	mes "　経験からだろうか、";
	mes "　少し成長できた気がする‐";
	close2;
	donpcevent getmdnpcname("jitter_control6")+"::OnStart";
	setquest 116509;
	compquest 116509;
	if(getonlinepartymember() == 1) {
		set '@base1,500000;
		set '@base2,0;
		set '@base3,0;
	}
	if(getonlinepartymember() == 2) {
		set '@base1,1000000;
		set '@base2,0;
		set '@base3,0;
	}
	if(getonlinepartymember() == 3) {
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,500000;
	}
	if(getonlinepartymember() >= 4) {
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
	}
	getexp '@base1,0,1;
	getexp '@base2,0,1;
	getexp '@base3,0,1;
	warp getmdmapname("1@jtb.gat"),96,100;
	end;
}

1@jtb.gat,133,106,0	script	6番部屋出口#JTB	45,2,2,{
OnTouch:
	mes "‐ここからダンジョンの外へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する")==1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	if(JTB_COUNT < 5)
		set JTB_COUNT,JTB_COUNT+1;
	delquest 13181;
	setquest 116507;
	compquest 116507;
	if(getonlinepartymember() == 1) {
		set '@base1,1000000;
		set '@base2,0;
		set '@base3,0;
	}
	if(getonlinepartymember() == 2) {
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,0;
	}
	if(getonlinepartymember() == 3) {
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,500000;
	}
	if(getonlinepartymember() >= 4) {
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
	}
	getexp '@base1,0,1;
	getexp '@base2,0,1;
	getexp '@base3,0,1;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// NPC、モンスター、ワープポータル：険しい道
//------------------------------------------
1@jtb.gat,0,7,0		script	jitter_control7	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("7番部屋出口#JTB");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control7")+"::OnKilled";
	areamonster '@map$,195,111,197,114,"ペル",3069,5,'@label$;
	areamonster '@map$,202,127,205,129,"ペル",3069,5,'@label$;
	areamonster '@map$,214,119,217,124,"ペル",3069,5,'@label$;
	areamonster '@map$,211,97,215,99,"ペル",3069,5,'@label$;
	areamonster '@map$,184,98,187,104,"ペル",3069,5,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control7")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("3番部屋出口#JTB");
		hideoffnpc getmdnpcname("7番部屋出口#JTB");
		announce "‐先へ進む道が現れた。北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	}
	end;
}

1@jtb.gat,0,8,0		script	jitter_control8	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("8番部屋出口#JTB");
	hideonnpc getmdnpcname("？？？#08");
	hideonnpc getmdnpcname("ラギ#08");
	hideonnpc getmdnpcname("ニュオーズ#08");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control8")+"::OnKilled";
	areamonster '@map$,283,108,287,110,"ペル",3069,6,'@label$;
	areamonster '@map$,295,101,297,104,"ペル",3069,6,'@label$;
	areamonster '@map$,292,126,288,128,"ペル",3069,6,'@label$;
	areamonster '@map$,302,122,304,125,"ペル",3069,6,'@label$;
	areamonster '@map$,275,122,278,125,"ペル",3069,6,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control8")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("7番部屋出口#JTB");
		//8番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("？？？#08");
		hideoffnpc getmdnpcname("ラギ#08");
		hideoffnpc getmdnpcname("ニュオーズ#08");
		initnpctimer getmdnpcname("ニュオーズ#08");
	}
	end;
}

1@jtb.gat,0,9,0		script	jitter_control9	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("9番部屋出口#JTB");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control9")+"::OnKilled";
	areamonster '@map$,363,106,365,108,"シンギング・ペル",3070,4,'@label$;
	areamonster '@map$,385,106,387,109,"シンギング・ペル",3070,4,'@label$;
	areamonster '@map$,385,128,387,130,"シンギング・ペル",3070,4,'@label$;
	areamonster '@map$,353,127,356,129,"シンギング・ペル",3070,4,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control9")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("8番部屋出口#JTB");
		hideoffnpc getmdnpcname("9番部屋出口#JTB");
		announce "‐先へ進む道が現れた。北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	}
	end;
}

1@jtb.gat,0,10,0		script	jitter_control10	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("10番部屋出口#JTB");
	hideonnpc getmdnpcname("シャルロシー#10");
	hideonnpc getmdnpcname("ニュオーズ#10");
	hideonnpc getmdnpcname("ミンミン#10");
	hideonnpc getmdnpcname("アラン#10");
	hideonnpc getmdnpcname("ロエル#10");
	hideonnpc getmdnpcname("ルナイン#10");
	hideonnpc getmdnpcname("ロテルト#10");
	hideonnpc getmdnpcname("ゲルカ#10");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control10")+"::OnKilled";
	areamonster '@map$,26,217,29,218,"スイング・ペル",3071,4,'@label$;
	areamonster '@map$,38,208,41,212,"スイング・ペル",3071,4,'@label$;
	areamonster '@map$,29,194,33,196,"スイング・ペル",3071,4,'@label$;
	areamonster '@map$,18,186,21,189,"スイング・ペル",3071,4,'@label$;
	areamonster '@map$,40,184,44,187,"スイング・ペル",3071,4,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control10")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("9番部屋出口#JTB");
		//10番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("シャルロシー#10");
		hideoffnpc getmdnpcname("ニュオーズ#10");
		initnpctimer getmdnpcname("ニュオーズ#10");
	}
	end;
}

1@jtb.gat,0,11,0		script	jitter_control11	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("11番部屋出口#JTB");
	hideonnpc getmdnpcname("シャルロシー#11");
	hideonnpc getmdnpcname("ロエル#11");
	hideonnpc getmdnpcname("ルナイン#11");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control11")+"::OnKilled";
	areamonster '@map$,109,205,111,208,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,122,213,124,215,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,114,189,118,192,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,122,192,126,203,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,101,184,103,188,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,115,195,125,210,"f・ジターバグ",3108,1,'@label$;
	initnpctimer;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control11")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("10番部屋出口#JTB");
		//11番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("シャルロシー#11");
		hideoffnpc getmdnpcname("ロエル#11");
		hideoffnpc getmdnpcname("ルナイン#11");
		initnpctimer getmdnpcname("ルナイン#11");
	}
	end;
OnTimer3000:
	announce "やはり、ここも非常に空間が不安定なようだ。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer6000:
	announce "部屋の全ての敵を倒すと、この部屋への入り口が消えてしまうだろう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer9000:
	stopnpctimer;
	announce "パーティーメンバーとはぐれないよう、入口が消える前に移動しよう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
}

1@jtb.gat,0,12,0		script	jitter_control12	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("12番部屋出口#JTB");
	hideonnpc getmdnpcname("アイグ#12");
	hideonnpc getmdnpcname("アラン#12");
	hideonnpc getmdnpcname("ラギ#12");
	hideonnpc getmdnpcname("ルナイン#12");
	hideonnpc getmdnpcname("ロエル#12");
	hideonnpc getmdnpcname("ミンミン#12");
	hideonnpc getmdnpcname("ゲルカ#12");
	hideonnpc getmdnpcname("メロディージャック#12");
	hideonnpc getmdnpcname("シャルロシー#12");
	hideonnpc getmdnpcname("ニュオーズ#12");
	hideonnpc getmdnpcname("ロテルト#12");
	hideonnpc getmdnpcname("ペル#12a");
	hideonnpc getmdnpcname("ペル#12b");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control12")+"::OnKilled";
	areamonster '@map$,183,192,187,196,"ペル",3069,2,'@label$;
	areamonster '@map$,183,192,187,196,"シンギング・ペル",3070,2,'@label$;
	areamonster '@map$,183,192,187,196,"スイング・ペル",3071,2,'@label$;
	areamonster '@map$,183,192,187,196,"キスミー・ペル",3072,2,'@label$;
	areamonster '@map$,202,199,205,203,"ペル",3069,2,'@label$;
	areamonster '@map$,202,199,205,203,"シンギング・ペル",3070,2,'@label$;
	areamonster '@map$,202,199,205,203,"スイング・ペル",3071,2,'@label$;
	areamonster '@map$,202,199,205,203,"キスミー・ペル",3072,2,'@label$;
	areamonster '@map$,200,211,204,213,"ペル",3069,2,'@label$;
	areamonster '@map$,200,211,204,213,"シンギング・ペル",3070,2,'@label$;
	areamonster '@map$,200,211,204,213,"スイング・ペル",3071,2,'@label$;
	areamonster '@map$,200,211,204,213,"キスミー・ペル",3072,2,'@label$;
	areamonster '@map$,210,187,213,190,"ペル",3069,2,'@label$;
	areamonster '@map$,210,187,213,190,"シンギング・ペル",3070,2,'@label$;
	areamonster '@map$,210,187,213,190,"スイング・ペル",3071,2,'@label$;
	areamonster '@map$,210,187,213,190,"キスミー・ペル",3072,2,'@label$;
	areamonster '@map$,210,211,213,213,"ペル",3069,2,'@label$;
	areamonster '@map$,210,211,213,213,"シンギング・ペル",3070,2,'@label$;
	areamonster '@map$,210,211,213,213,"スイング・ペル",3071,2,'@label$;
	areamonster '@map$,210,211,213,213,"キスミー・ペル",3072,2,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control12")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("11番部屋出口#JTB");
		//12番部屋NPCにてhideoff
		hideoffnpc getmdnpcname("アイグ#12");
		hideoffnpc getmdnpcname("アラン#12");
		hideoffnpc getmdnpcname("ラギ#12");
		hideoffnpc getmdnpcname("ルナイン#12");
		hideoffnpc getmdnpcname("ロエル#12");
		hideoffnpc getmdnpcname("ミンミン#12");
		hideoffnpc getmdnpcname("ゲルカ#12");
		hideoffnpc getmdnpcname("メロディージャック#12");
		hideoffnpc getmdnpcname("シャルロシー#12");
		hideoffnpc getmdnpcname("ニュオーズ#12");
		hideoffnpc getmdnpcname("ロテルト#12");
		initnpctimer getmdnpcname("ロテルト#12");
	}
	end;
}

1@jtb.gat,0,9,0		script	jitter_control21	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("トンネル部屋出口#JTB");
	hideonnpc getmdnpcname("ニュオーズ#21");
	hideonnpc getmdnpcname("ロテルト#23");
	hideonnpc getmdnpcname("ゲルカ#23");
	hideonnpc getmdnpcname("ミンミン#23");
	hideonnpc getmdnpcname("アイグ#23");
	hideonnpc getmdnpcname("ラギ#23");
	hideonnpc getmdnpcname("アラン#23");
	hideonnpc getmdnpcname("ルナイン#23");
	hideonnpc getmdnpcname("ロエル#23");
	hideonnpc getmdnpcname("メロディージャック#23");
	hideonnpc getmdnpcname("シャルロシー#23");
	hideonnpc getmdnpcname("ペル#23");
	hideonnpc getmdnpcname("ペル#25");
	hideonnpc getmdnpcname("ニュオーズ#boss");
	initnpctimer getmdnpcname("ニュオーズ#22");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control21")+"::OnKilled";
	areamonster '@map$,287,293,290,295,"ペル",3069,5,'@label$;
	areamonster '@map$,296,293,299,295,"ペル",3069,5,'@label$;
	areamonster '@map$,304,293,309,295,"シンギング・ペル",3070,5,'@label$;
	areamonster '@map$,315,293,320,295,"シンギング・ペル",3070,5,'@label$;
	areamonster '@map$,356,322,359,325,"スイング・ペル",3071,5,'@label$;
	areamonster '@map$,356,331,359,334,"スイング・ペル",3071,5,'@label$;
	areamonster '@map$,356,348,359,351,"キスミー・ペル",3072,5,'@label$;
	areamonster '@map$,351,356,355,359,"キスミー・ペル",3072,5,'@label$;
	end;
OnKilled:
	set 'count,getmapmobs(getmdmapname("1@jtb.gat"),getmdnpcname("jitter_control21")+ "::OnKilled");
	if('count <= 0) {
		hideonnpc getmdnpcname("12番部屋出口#JTB");
		hideoffnpc getmdnpcname("トンネル部屋出口#JTB");
		hideoffnpc getmdnpcname("ニュオーズ#21");
	}
	end;
}

1@jtb.gat,0,22,0		script	jitter_control22	-1,{
OnStart:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("23番部屋出口#JTB");
	hideonnpc getmdnpcname("シャルロシー#22");
	hideonnpc getmdnpcname("ペル#23");
	hideonnpc getmdnpcname("ニュオーズ#22");
	hideoffnpc getmdnpcname("ニュオーズ#boss");
	set '@map$,getmdmapname("1@jtb.gat");
	set '@label$,getmdnpcname("jitter_control22")+"::OnKilled";
	set 'boss, callmonster('@map$,324,327,"fff・ジターバグ",3073,'@label$);
	areamonster '@map$,322,315,325,318,"ペル",3069,5;
	initnpctimer;
	end;
OnKilled:
	stopnpctimer;
	hideonnpc getmdnpcname("21番部屋出口#JTB");
	//END部屋NPCにてhideoff
	hideoffnpc getmdnpcname("ロテルト#23");
	hideoffnpc getmdnpcname("ゲルカ#23");
	hideoffnpc getmdnpcname("ミンミン#23");
	hideoffnpc getmdnpcname("アイグ#23");
	hideoffnpc getmdnpcname("ラギ#23");
	hideoffnpc getmdnpcname("アラン#23");
	hideoffnpc getmdnpcname("ルナイン#23");
	hideoffnpc getmdnpcname("ロエル#23");
	hideoffnpc getmdnpcname("メロディージャック#23");
	hideoffnpc getmdnpcname("シャルロシー#23");
	hideoffnpc getmdnpcname("ペル#25");
	hideonnpc getmdnpcname("ニュオーズ#boss");
	hideoffnpc getmdnpcname("ニュオーズ#23");
	initnpctimer getmdnpcname("ニュオーズ#23");
	end;
OnTimer3000:
	announce "やはり、ここも非常に空間が不安定なようだ。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer6000:
	announce "fff・ジターバグを倒すと、この部屋への入り口が消えてしまうだろう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer9000:
	announce "パーティーメンバーとはぐれないよう、入口が消える前に移動しよう。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer16000:
	areamonster getmdmapname("1@jtb.gat"),328,322,331,327,"シンギング・ペル",3070,5;
	end;
OnTimer23000:
	areamonster getmdmapname("1@jtb.gat"),318,336,323,339,"スイング・ペル",3071,5;
	end;
OnTimer30000:
	areamonster getmdmapname("1@jtb.gat"),313,322,317,327,"キスミー・ペル",3072,5;
	end;
}

1@jtb.gat,209,133,0	script	7番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control8")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),277,95;
	end;
}

1@jtb.gat,307,122,0	script	8番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control9")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),359,97;
	end;
}

1@jtb.gat,386,133,0	script	9番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control10")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),13,214;
	end;
}

1@jtb.gat,49,196,0	script	10番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control11")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),95,201;
	end;
}

1@jtb.gat,133,197,0	script	11番部屋出口#JTB	45,2,2,{
OnTouch:
	mes "‐これまでの戦闘で得た";
	mes "　経験からだろうか、";
	mes "　少し成長できた気がする。‐";
	close2;
	donpcevent getmdnpcname("jitter_control12")+"::OnStart";
	setquest 116509;
	compquest 116509;
	set '@base3,0;
	set '@base4,0;
	set '@base5,0;
	set '@base6,0;
	set '@base7,0;
	set '@job2,0;
	set '@job3,0;
	set '@job4,0;
	switch(getonlinepartymember()) {
	case 1:
		set '@base1,1000000;
		set '@base2,500000;
		set '@job1,750000;
		break;
	case 2:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@job1,1000000;
		break;
	case 3:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,500000;
		set '@job1,1000000;
		set '@job2,250000;
		break;
	case 4:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@job1,1000000;
		set '@job2,500000;
		break;
	case 5:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,500000;
		set '@job1,1000000;
		set '@job2,750000;
		break;
	case 6:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		break;
	case 7:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,250000;
		break;
	case 8:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,500000;
		break;
	case 9:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,750000;
		break;
	case 10:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		break;
	case 11:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,250000;
		break;
	case 12:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,500000;
		break;
	}
	getexp '@base1,0,1;
	getexp '@base2,0,1;
	getexp '@base3,0,1;
	getexp '@base4,0,1;
	getexp '@base5,0,1;
	getexp '@base6,0,1;
	getexp '@base7,0,1;
	getexp 0,'@job1,1;
	getexp 0,'@job2,1;
	getexp 0,'@job3,1;
	getexp 0,'@job4,1;
	warp getmdmapname("1@jtb.gat"),181,198;
	end;
}

1@jtb.gat,218,203,0	script	12番部屋出口#JTB	45,2,2,{
OnTouch:
	donpcevent getmdnpcname("jitter_control21")+"::OnStart";
	warp getmdmapname("1@jtb.gat"),287,355;
	end;
}

1@jtb.gat,311,358,0	script	トンネル部屋出口#JTB	45,2,2,{
OnTouch:
	warp getmdmapname("1@jtb.gat"),335,320;
	end;
}

//==========================================
// MD出口：険しい道
//------------------------------------------
1@jtb.gat,391,30,0	script	23番部屋出口#JTB	45,2,2,{
	if(!checkquest(116500)) {
		switch(JTB_2QUE) {
		case 0:
			mes "‐誰かの声が聞こえる‐";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ラギ君、ちょっといいかい？";
			next;
			cutin "ragi03.bmp", 2;
			mes "[ラギ]";
			mes "なんでしょうか？";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "実は君にお願いがあるんだ。";
			mes "この後、少しだけ";
			mes "付き合ってくれないかな？";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "ええ、構いませんよ。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes strcharinfo(0) + "にも";
			mes "話がしたいんだけど";
			mes "どこにいるかな～……。";
			next;
			cutin "nines01.bmp", 255;
			mes "‐ニュオーズが何か相談したいようだ。";
			mes "　詳しい話を聞くべきだろうか？‐";
			next;
			if(select("話を聞きに行く","話を聞きに行かない") == 1) {
				mes "‐ニュオーズの所へ行ってみよう‐";
				close;
			}
			break;
		case 1:
			mes "‐誰かの声が聞こえる‐";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "ミンミン……。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "あら、どうしたの？";
			mes "珍しく元気がないじゃない。";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "うん、実は相談したい事があるんだ。";
			mes "ミンミンは頭が良いし";
			mes "解決する方法を";
			mes "知らないかなって思って……。";
			next;
			mes "[アラン]";
			mes "……本当は";
			mes strcharinfo(0) + "にも";
			mes "相談したいんだけど";
			mes "忙しそうだし……。";
			next;
			cutin "arang01.bmp", 255;
			mes "‐アランが何か相談したいようだ。";
			mes "　詳しい話を聞くべきだろうか？‐";
			next;
			if(select("話を聞きに行く","話を聞きに行かない") == 1) {
				mes "‐アランの所へ行ってみよう‐";
				close;
			}
			break;
		case 2:
			mes "‐誰かの声が聞こえる‐";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "これで冒険終了……。";
			mes "僕は何か、みなさんのお役に";
			mes "たてたのでしょうか……。";
			next;
			cutin "gelca03.bmp", 2;
			mes "[ゲルカ]";
			mes "ふっふっふ～。";
			mes "聴こえちゃいましたよ！";
			mes "お悩みのようですね、ロエル君。";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "ゲルカさん!?";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "今のロエル君に足りないもの。";
			mes "それは必殺技です！";
			mes "というわけで、この後私と一緒に";
			mes "必殺技の練習をしませんか？";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "必殺技……ですか？";
			mes "よくわかりませんが、";
			mes "みなさんのお役にたてるなら";
			mes "お願いします！";
			next;
			cutin "roel01.bmp", 255;
			mes "‐ロエルとゲルカが";
			mes "　必殺技の練習をするらしい。";
			mes "　二人のシャルロシーに対する";
			mes "　気持ちを聞き出す";
			mes "　チャンスかもしれない‐";
			next;
			if(select("話を聞きに行く","話を聞きに行かない") == 1) {
				mes "‐ロエルの所へ行ってみよう‐";
				close;
			}
			break;
		case 3:
			mes "‐誰かの声が聞こえる‐";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "ルナイン……。";
			mes "大丈夫なの？";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "え、何が？";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "何か、凄く悲しそうなの……。";
			mes "今にも泣きだしそうなの……。";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "そんな事ないわよ。";
			mes "私はいつも通り。";
			mes "ニュオーズ様にも会えたし";
			mes "むしろ、嬉しいくらいよ。";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "でも……。";
			next;
			cutin "igu04.bmp", 255;
			mes "‐アイグとルナインが";
			mes "　何か話しているようだ。";
			mes "　二人のシャルロシーに対する";
			mes "　気持ちを聞き出す";
			mes "　チャンスかもしれない‐";
			next;
			if(select("話を聞きに行く","話を聞きに行かない") == 1) {
				mes "‐アイグの所へ行ってみよう‐";
				close;
			}
			break;
		case 4:
			mes "‐誰かの声が聞こえる‐";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……ふう。";
			mes "ギルドマスターも";
			mes "楽じゃねえな。";
			next;
			cutin "rote01.bmp", 255;
			mes "‐ロテルトが一人になった。";
			mes "　みんなから聞いた";
			mes "　シャルロシーに対する気持ちを";
			mes "　ロテルトに伝える";
			mes "　チャンスかもしれない‐";
			next;
			if(select("話を聞きに行く","話を聞きに行かない") == 2) {
				mes "‐ロテルトの所へ行ってみよう‐";
				close;
			}
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	mes "‐ここからダンジョンの外へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	compquest 13181;
	setquest 13183;
	compquest 13183;
	setquest 116508;
	compquest 116508;
	set '@base4,0;
	set '@base5,0;
	set '@base6,0;
	set '@base7,0;
	set '@base8,0;
	set '@job3,0;
	set '@job4,0;
	switch(getonlinepartymember()) {
	case 1:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,500000;
		set '@job1,1000000;
		set '@job2,250000;
		break;
	case 2:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@job1,1000000;
		set '@job2,500000;
		break;
	case 3:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,500000;
		set '@job1,1000000;
		set '@job2,750000;
		break;
	case 4:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		break;
	case 5:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,250000;
		break;
	case 6:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,500000;
		break;
	case 7:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,750000;
		break;
	case 8:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		break;
	case 9:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,250000;
		break;
	case 10:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,500000;
		break;
	case 11:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,1000000;
		set '@base8,500000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,750000;
		break;
	case 12:
		set '@base1,1000000;
		set '@base2,1000000;
		set '@base3,1000000;
		set '@base4,1000000;
		set '@base5,1000000;
		set '@base6,1000000;
		set '@base7,1000000;
		set '@base8,1000000;
		set '@job1,1000000;
		set '@job2,1000000;
		set '@job3,1000000;
		set '@job4,1000000;
		break;
	}
	getexp '@base1,0,1;
	getexp '@base2,0,1;
	getexp '@base3,0,1;
	getexp '@base4,0,1;
	getexp '@base5,0,1;
	getexp '@base6,0,1;
	getexp '@base7,0,1;
	getexp '@base8,0,1;
	getexp 0,'@job1,1;
	getexp 0,'@job2,1;
	getexp 0,'@job3,1;
	getexp 0,'@job4,1;
	if(BaseLevel >= 180 && BaseLevel <= 199) {
		getexp (NextBaseExp / 100 * 2),0,0;
		unittalk getcharid(0), strcharinfo(0)+ ": -Base経験値2%を追加で獲得しました-",1;
	}
	getitem 6719,1;
	if(JTB_COUNT < 10)
		set JTB_COUNT,JTB_COUNT+1;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 1番部屋NPC：共通
//------------------------------------------
1@jtb.gat,25,28,5	script	ロテルト#01	630,{
	if(JTB_1QUE <= 0) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "あ？　お前が臨時のギルド員か。";
		mes "やる気があるのはいいが、";
		mes "俺の邪魔だけはするなよ。";
		close2;
		cutin "rote01.bmp", 255;
		end;
	} else {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "チッ！";
		mes "何なんだこのダンジョンは、";
		mes "悪霊でも住み着いていやがるのか？";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
}

1@jtb.gat,31,28,4	script	アイグ#01	646,{
	if(JTB_1QUE <= 0) {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "見ない顔だね？";
		mes "よろしくなの！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "ニュオーズは相変わらずなの。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,23,26,5	script	ゲルカ#01	629,{
	if(JTB_1QUE <= 0) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "新人さんですか？";
		mes "よろしくお願いします！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	} else {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "この邪悪な気……";
		mes "何なんでしょうか？";
		mes "邪悪なんですけど、";
		mes "悪意は感じないんです。";
		mes "不思議ですよね！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
}

1@jtb.gat,33,26,4	script	ラギ#01	647,{
	if(JTB_1QUE <= 0) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "君は新人さんですか？";
		mes "僕はラギ。";
		mes "よろしくお願いしますねぇ。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	} else {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "不思議な体験をしましたねぇ。";
		mes "早速、今の気持ちを歌にしたく";
		mes "なってきましたよぉ。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	}
}

1@jtb.gat,25,24,5	script	ミンミン#01	643,{
	if(JTB_1QUE <= 0) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あなたが臨時のギルド員ね？";
		mes "よろしく。";
		close2;
		cutin "min01.bmp", 255;
		end;
	} else {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "こんな場所に平然と呼び出すなんて";
		mes "ニュオーズは相変わらずね……。";
		close2;
		cutin "min01.bmp", 255;
		end;
	}
}

1@jtb.gat,31,24,4	script	アラン#01	644,{
	if(JTB_1QUE <= 0) {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "こんにちは！";
		mes "私はアランっていうんだ！";
		close2;
		cutin "arang01.bmp", 255;
		end;
	} else {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "ほ、本当に幽霊だったら";
		mes "どうしよう……。";
		mes "幽霊怖いな……。";
		close2;
		cutin "arang01.bmp", 255;
		end;
	}
}

1@jtb.gat,23,22,5	script	ルナイン#01	10039,{
	if(JTB_1QUE <= 0) {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "あら、来たのね。";
		mes "短い間だけどよろしくね。";
		close2;
		cutin "lunain02.bmp", 255;
		end;
	} else {
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "あ、あれが本物のニュオーズ様！";
		mes "やっと会えた……。";
		mes "ニュオーズ様に憧れて";
		mes "ギルドに入った甲斐があったわ。";
		close2;
		cutin "lunain02.bmp", 255;
		end;
	}
}

1@jtb.gat,34,22,4	script	ロエル#01	10040,{
	if(JTB_1QUE <= 0) {
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "一緒にがんばりましょう！";
		mes "よろしくお願いします！";
		close2;
		cutin "rote01.bmp", 255;
		end;
	} else {
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "ニュオーズ様……";
		mes "初めてお会いしましたが";
		mes "本当にロテルト様と";
		mes "仲が良いんですね！";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
}

1@jtb.gat,28,21,5	script	メロディージャック#01	844,{
	if(JTB_1QUE <= 0) {
		mes "[メロディージャック]";
		mes "……面倒だな。";
		mes "隠れているのがわからないのか？";
		close;
	} else {
		mes "[メロディージャック]";
		mes "さて、妙な輩がいるようだが";
		mes "私は私の仕事をするだけだ。";
		mes "奴との約束のためにな。";
		close;
	}
}

1@jtb.gat,28,30,5	script	ニュオーズ#01	625,{
	if(JTB_1QUE <= 0) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116507) || checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,1;
				hideoffnpc getmdnpcname("1番部屋出口#JTB");
				announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close;
			}
		}
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ギルド条項8番に基づき、";
		mes "ギルドマスターはこの俺だ！";
		mes "今のお前はギルドメンバーの";
		mes "下っ端でしかない！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "あ、そうなの？";
		mes "じゃあ、ロテが今は";
		mes "新マスターなんだね。";
		next;
		mes "[ニュオーズ]";
		mes "よろしくね、新マスター。";
		mes "初めましてのみんなも";
		mes "これからよろしくね～。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "お前……俺になにか言うことや、";
		mes "思うことはないのかよ!?";
		next;
		mes "[ロテルト]";
		mes "ギルドマスターのくせに連絡も寄こさず";
		mes "いきなり連絡してきたと思ったら";
		mes "面白い場所を見つけたから、";
		mes "みんなで来いだと!?";
		mes "ふざけるな!!";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんごめん。";
		mes "流石に急すぎたかなと思ったんだけど";
		mes "ロテならきっと来てくれるって";
		mes "信じてたからね♪";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……ニュオーズ。お、お前な……。";
		next;
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "ふふ、私は本当果報者だよ～！";
		mes "いつも私のことを心配してくれて";
		mes "ありがとうね、ロテルト♪";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "ち、違う!!";
		mes "俺は別にお前を心配で";
		mes "来たわけじゃない!!";
		mes "ミンミンや新人メンバーがだな……。";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あーら、私と新人のせいにするなとか";
		mes "野暮なことは言わないけど、";
		mes "どうせあいつはろくなものを";
		mes "食べてないはずだって言って、";
		mes "にくを大量に買っていたのは";
		mes "どこの誰かしらね。";
		next;
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "それは本当かい!?";
		mes "にくなんて、久しぶりだよ～！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら、私が嘘をついても";
		mes "仕方ないでしょ。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠が大量のにくを1人で";
		mes "持ち帰ってきたので";
		mes "不思議だったんですよね～！";
		mes "ミンミンさんのお話を聞いて、";
		mes "納得しました！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ゲルカ！";
		mes "余計なことは言うな！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "ほら、これでわかったでしょ？";
		mes "ロテルトは本当にあんたのことを";
		mes "心配してるのよ。";
		next;
		mes "[ミンミン]";
		mes "旅に出るなとはいわないけど、";
		mes "ロテルトくらいには";
		mes "連絡してあげなさいよね。";
		next;
		mes "[ミンミン]";
		mes "あんたのことを心配する話を、";
		mes "毎日聞かされる";
		mes "こっちの身にもなってほしいわ。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "そうだよー！";
		mes "それにロテルト、心配しすぎて";
		mes "盜蟲つぶしたような顔になってて";
		mes "怖いんだよー？";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "アラン、お前まで";
		mes "そんなこというのかよ……。";
		next;
		mes "[ロテルト]";
		mes "はあ……俺の味方は";
		mes strcharinfo(0)+ "だけ";
		mes "のようだな……。";
		next;
		if(select("ロテルトはツンデレなんですね","みなさん、仲が良いんですね。") == 1) {
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ツンデレ!?";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "あら、よくわかってるじゃない。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "違うよ～！";
			mes "ロテはテレ屋なだけだよ♪";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "お前らなぁ……。";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "あまり怒るとしわが増えるよ？";
			mes "ロテルト。";
		} else {
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "まあ、確かに仲は悪くねーな……。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "ロテルト以外の皆は、ね。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "!?";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "冗談よ。";
		}
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "クソッ！　今は分が悪い……。";
		mes "それでニュオーズ。";
		mes "この洞窟はなんなんだ!?";
		mes "ここに居るだけで妙に";
		mes "落ち着かない……。";
		next;
		mes "[ロテルト]";
		mes "誰かにずっと見られているみたいだ。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "他のみんなもこの洞窟の空気のせいで";
		mes "なんだか元気がないね……。";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "そうね、この洞窟は普通じゃない。";
		mes "さっきも入り口に戻ろうとしたら、";
		mes "不思議な力でみんな";
		mes "バラバラにされたし。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "なんとかこうしてまた集まれたのが";
		mes "奇跡だな。";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "私は、師匠がいるから平気ですけど！";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "そうだね！";
		mes "でもそれだけじゃないんだよ！";
		mes "この洞窟には私たち以外に";
		mes "何かいるみたいなんだ。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……おい、何かって何だ!?";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "あれ？";
		mes "ロテ、君には聞こえないかい？";
		mes "さっきから、何かが私を";
		mes "呼んでいるようなんだけど。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "……え、それってまさか。";
		next;
		cutin "arang02.bmp", 2;
		mes "[アラン]";
		mes "幽霊……？";
		next;
		cutin "arang01.bmp", 255;
		mes "[？？？]";
		mes "幽霊って……何？";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "な、なんだ!?";
		mes "頭に直接声が……。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "あ、ロテにも聞こえたんだね～。";
		mes "良かった良かった！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "テメェェェェェッ！";
		mes "そういうことは早く言えっ！";
		next;
		cutin "nines04.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ～……";
		mes "そんなに襟を掴むと苦しいよ～？";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "お前は一度ここで";
		mes "オーディンの奴にでも";
		mes "会っておくべきかもなっ!?";
		next;
		cutin "rote01.bmp", 255;
		mes "[？？？]";
		mes "……だめ。";
		misceffect 563,"";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "……!!";
		mes "地震なの！　みんな気を付けて！";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠！　何か邪悪な気を感じます！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "クソッ！　とにかく出口を探すぞ！";
		mes "ここは何かヤバイ感じがする！";
		mes "戦闘の準備は怠るなよ！";
		set JTB_1QUE,1;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			hideoffnpc getmdnpcname("1番部屋出口#JTB");
			announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		}
		close2;
		cutin "rote01.bmp", 255;
		end;
	} else {
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "さあ、冒険のはじまりだ！";
		mes "ワクワクするね！";
		close2;
		cutin "nines01.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// 3番部屋NPC：共通
//------------------------------------------
1@jtb.gat,205,31,4	script	？？？#03	10041,{
	cutin "shaloshi01.bmp", 2;
	mes "[？？？]";
	mes "手、暖かい……。";
	close2;
	cutin "shaloshi01.bmp", 255;
	end;
}

1@jtb.gat,200,28,5	script	アイグ#03	646,{
	if(JTB_1QUE <= 1) {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "さっきの戦闘でみんなと";
		mes "はぐれちゃったの……。";
		mes "なんとかルナインと合流できたけど";
		mes "早くみんなを見つけないとなの……。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "この子、どこから来たんだろう？";
		mes "不思議な子だけど……";
		mes "まずは安全な所に";
		mes "連れて行ってあげるの！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,203,28,4	script	ルナイン#03	10039,{
	if(JTB_1QUE <= 1) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116507) || checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				while(1) {
					mes "‐どちらの道に進もう？‐";
					next;
					switch(select("少し考える","^0000ffなだらかな道^000000","^ff0000険しい道(BaseLv120以上で侵入可能)^000000")) {
					case 1:
						continue;
					case 2:
						set .Route,1;
						break;
					case 3:
						if(BaseLevel <= 119) {
							mes "‐貴方のレベルでは選択できません‐";
							continue;
						}
						set .Route,2;
						break;
					}
					stopnpctimer;
					set JTB_1QUE,3;
					hideoffnpc getmdnpcname("3番部屋出口#JTB");
					announce "‐南東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
					mes "‐あなたは記憶を探りながら";
					mes "　先を急ぐことにした‐";
					close;
				}
			}
		}
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "あら。あなたも無事だったのね。";
		mes "アイグー！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "どうかしたの？　ルナイン。";
		next;
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "ギルドメンバーの";
		mes strcharinfo(0) + "がいたわ。";
		next;
		cutin "igu03.bmp", 2;
		mes "[アイグ]";
		mes "よかったの！";
		mes "さっきの戦闘でみんなとはぐれて、";
		mes "心細かったの。";
		next;
		cutin "lunain03.bmp", 2;
		mes "[ルナイン]";
		mes "ニュオーズ様だったら";
		mes "最高だったんだけど、";
		mes "バカロエルじゃなくて良かったわ。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "そういえば";
		mes "どうしてバカロエルなの？";
		next;
		cutin "lunain03.bmp", 2;
		mes "[ルナイン]";
		mes "バカだから。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "身も蓋もない言い方なの……。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "だってあいつ、モロクの現身(人間型)を";
		mes "生きた怪我人だと勘違いして";
		mes "助けようとして、襲われたのよ？";
		mes "バカ以外の何者でもないじゃない。";
		next;
		cutin "lunain03.bmp", 255;
		mes "[？？？]";
		mes "モロク……。";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			hideoffnpc getmdnpcname("？？？#03");
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes strcharinfo(0) + "、";
		mes "アイグ、";
		mes "なにか言った？";
		next;
		menu "何も言ってない",-;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "……え？";
		mes "私も何も言ってないけど……。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "!!";
		mes "ちょ……ちょっと、";
		mes "ルナイン！　後ろ！";
		next;
		cutin "lunain04.bmp", 2;
		emotion 23,getmdnpcname("ルナイン#03");
		mes "[ルナイン]";
		mes "え？　きゃああああっ!?";
		mes "って、人間……!?";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "びっくりしたの！";
		mes "ねえ、お嬢ちゃん。";
		mes "どこからここに来たの？";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……知らない。";
		mes "……聞いた事ある言葉、聞こえた。";
		mes "……だから来ただけ。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "もしかして迷子なの？";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "ちょっと、アイグ！";
		mes "どうやってこんな小さい子が、";
		mes "こんな次元の狭間までやってくるのよ！";
		next;
		cutin "lunain03.bmp", 255;
		mes "[" + strcharinfo(0) + "]";
		mes "ニュオーズの例もあるし……。";
		next;
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "何いってるのよ。";
		mes "ニュオーズ様は特別だからに";
		mes "決まってるじゃない。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "ニュオーズ……歌う人。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "ニュオーズ様を知ってるの!?";
		mes "って、キャッ！";
		misceffect 563,"";
		next;
		cutin "lunain01.bmp", 255;
		mes "[" + strcharinfo(0) + "]";
		mes "とりあえず、みんなと合流しよう。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes strcharinfo(0) + "の";
		mes "言う通りなの。";
		mes "でも、この子をここに";
		mes "置いて行くのも危険だし、";
		mes "一緒に連れていくの。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "そうね。他に誰も居ないみたいだし、";
		mes "ニュオーズ様を知ってるなら";
		mes "なおさら、放っておけないわ。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "迷子になったら困るし、";
		mes "手をつないで行くの。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……手……つなぐ？";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "あれ？　つないだことない？";
		mes "えっと、こうなの。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "こんな場所にいたからかな？";
		mes "手が冷えてるの。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……不思議な感じがする。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "ほら、温かくなってきた。";
		mes "ぽかぽかなの♪";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "……ぽかぽか。";
		mes "……なの。";
		next;
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "^ff0000険しい道^000000と^ff0000なだらかな道^000000、";
		mes "道が2つあるわね。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "うそー……。うーん……";
		mes "険しい道から凄い力を感じるの。";
		next;
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			cutin "igu02.bmp", 2;
			mes "[アイグ]";
			mes "どっちに進むか、君たちの代表者と";
			mes "相談するから待ってて欲しいの。";
			close2;
			cutin "lunain01.bmp", 255;
			end;
		}
		while(1) {
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes strcharinfo(0)+"、";
			mes "どっちがいいと思う？";
			mes "^ff0000険しい道は凄い力を感じる^000000から";
			mes "自信がないなら止めた方が";
			mes "いいと思うの……。";
			next;
			switch(select("少し考える","^0000ffなだらかな道^000000","^ff0000険しい道(BaseLv120以上で侵入可能)^000000")) {
			case 1:
				continue;
			case 2:
				cutin "igu01.bmp", 2;
				mes "[アイグ]";
				mes "私も^ff0000なだらかな道^000000がいいと思うの！";
				mes "絶対、こっちなの！";
				next;
				cutin "lunain03.bmp", 2;
				mes "[ルナイン]";
				mes "やっぱり^ff0000なだらかな道^000000が無難よね。";
				mes "こっちに行きましょ。";
				set .Route,1;
				break;
			case 3:
				if(BaseLevel <= 119) {
					cutin "igu05.bmp", 2;
					mes "[アイグ]";
					mes "こっちの道は、嫌な予感がするの。";
					mes "止めておいた方がいいの。";
					next;
					continue;
				}
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "危険かもしれないけど、";
				mes "みんないるかもしれないから";
				mes "私も^ff0000険しい道^000000がいいと思うの。";
				next;
				cutin "lunain01.bmp", 2;
				mes "[ルナイン]";
				mes "^ff0000険しい道^000000に行けば";
				mes "ニュオーズ様がいるって、";
				mes "私の勘が告げてる気がするわ。";
				mes "こっちに行きましょ。";
				set .Route,2;
				break;
			}
			break;
		}
		set JTB_1QUE,3;
		hideoffnpc getmdnpcname("3番部屋出口#JTB");
		announce "‐南東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		close2;
		cutin "lunain01.bmp", 255;
		end;
	} else {
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "さ、道を決めたら";
		mes "さっさと進みましょ。";
		close2;
		cutin "lunain01.bmp", 255;
		// リーダーを委任した場合の救済措置
		if(.Route == 0) {
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				while(1) {
					mes "‐どちらの道に進もう？‐";
					next;
					switch(select("少し考える","^0000ffなだらかな道^000000","^ff0000険しい道(BaseLv120以上で侵入可能)^000000")) {
					case 1:
						continue;
					case 2:
						set .Route,1;
						break;
					case 3:
						if(BaseLevel <= 119) {
							mes "‐貴方のレベルでは選択できません‐";
							continue;
						}
						set .Route,2;
						break;
					}
					set JTB_1QUE,3;
					hideoffnpc getmdnpcname("3番部屋出口#JTB");
					announce "‐南東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
					close;
				}
			}
		} else {
			if(getpartyleader(getcharid(1)) != strcharinfo(0))
				announce "‐南東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		}
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// 5番部屋NPC：なだらかな道
//------------------------------------------
1@jtb.gat,25,110,4	script	アイグ#05	646,{
	if(JTB_1QUE <= 3) {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "あの子とはぐれちゃったの……。";
		mes "早く見つけないとなの……。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "微かに聴こえるピアノの音……";
		mes "凄く寂しそうな曲に聴こえるの。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,22,110,5	script	ルナイン#05	10039,{
	if(JTB_1QUE <= 3) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116507))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,5;
				hideoffnpc getmdnpcname("5番部屋出口#JTB");
				announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close;
			}
		}
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "いきなり襲ってくるなんて……。";
		mes "念のためヒールしておくから、";
		mes "動かないでよね。";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			misceffect 313,getmdnpcname("アイグ#05");
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "……どうしよう！";
		mes "さっきの戦闘であの子と";
		mes "はぐれたみたいなの……！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			misceffect 313,getmdnpcname("アイグ#05");
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "ちょっ、それ本当なの!?";
		next;
		cutin "lunain01.bmp", 255;
		mes "[？？？]";
		mes "そ、その声は……！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "やっぱり、ルナインさん！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			hideoffnpc getmdnpcname("ロエル#05");
		cutin "lunain03.bmp", 2;
		mes "[ルナイン]";
		mes "……なんだ、バカロエルか。";
		next;
		cutin "roel04.bmp", 2;
		mes "[ロエル]";
		mes "すごくガッカリされた!?";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "ロエル君、待ってくださー……";
		mes "あ！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			hideoffnpc getmdnpcname("ゲルカ#05");
			hideoffnpc getmdnpcname("メロディージャック#05");
		}
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "ゲルカも一緒なんだね！";
		mes "良かったの……。";
		mes "でも今は、それどころじゃないの！";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "え、なにかあったんですか!?";
		next;
		cutin "roel01.bmp", 255;
		mes "‐アイグはロエルとゲルカに";
		mes "　これまでの事を説明した‐";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "なるほど……。";
		next;
		cutin "roel01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "その少女らしき娘なら、";
		mes "モンスターと一緒に";
		mes "どこかに消えたぞ。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "ジャック、あの子を見たの!?";
		mes "モンスターと一緒って……";
		mes "もしかして連れ去られたって";
		mes "ことなの!?";
		next;
		cutin "igu01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "どこからか声がする!?";
		next;
		cutin "igu01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "……。";
		next;
		mes "[メロディージャック]";
		mes "とはいえすぐに見失ったからな。";
		mes "どこに行ったのかまではわからん。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "あの子、記憶がないみたいだから";
		mes "心配なの……";
		mes "早く見つけてあげないとなの……！";
		mes "教えてくれてありがとうなの。";
		next;
		cutin "igu01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "気にするな。あと念のため、";
		mes "私のことを他のメンバーにも";
		mes "紹介してくれないか。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "うん。えっと、メロディージャックは";
		mes "ニュオーズの白羽ギルドの";
		mes "メンバーなんだけど、";
		mes "事情があって今は私が団長をしている";
		mes "たんぽぽ楽団のメンバーなの。";
		next;
		mes "[アイグ]";
		mes "いつも姿を消しているのは、";
		mes "お仕事の関係らしいの。";
		next;
		cutin "igu01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes strcharinfo(0)+"です。";
		mes "今回、臨時のギルドメンバーとして";
		mes "参加しました。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "私はゲルカといいます！";
		mes "ロテルト師匠の一番弟子です！";
		mes "趣味は必殺技考案と読書です！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "ゲルカさん、よくロテルト様と";
		mes "必殺技の練習をしていますしね！";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "はい！　いつかこの星を";
		mes "真っ二つにするのが夢です！";
		next;
		cutin "lunain03.bmp", 2;
		mes "[ルナイン]";
		mes "その夢もどうなのよ……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "僕は最近、ニュオーズの白羽ギルドに";
		mes "入団したロエルといいます！";
		mes "メロディージャックさん、";
		mes "よろしくお願いします！";
		next;
		cutin "roel01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "……私はこっちだ。そっちじゃない。";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "（逆方向に挨拶しちゃった！）";
		next;
		cutin "roel01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "ところでお前達には聴こえないか？";
		mes "ピアノの音が。";
		next;
		if(select("ピアノの音？","自分にも聴こえた") == 1) {
			emotion 9,getmdnpcname("メロディージャック#05");
			mes "[メロディージャック]";
			mes strcharinfo(0)+"には";
			mes "聴こえていないようだな。";
			mes "他のみんなはどうだ？";
			next;
		} else {
			emotion 9,getmdnpcname("メロディージャック#05");
			mes "[メロディージャック]";
			mes "そうか、お前にも聴こえたか。";
			next;
		}
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "そういえばさっきから、";
		mes "聞き覚えのある音が";
		mes "聴こえるなって";
		mes "思ってたのよね。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "すっごく微かにだけど、聴こえるの。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "うーん？";
		mes "私には聴こえません。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "僕も特には……。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "とりあえずここでこうしてても";
		mes "仕方ないじゃない。";
		mes "その音の正体を確かめるためにも、";
		mes "先に進んだ方がいいんじゃないの？";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "そうだね。あの子も早く";
		mes "見つけてあげないと……なの！";
		next;
		cutin "igu01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#05");
		mes "[メロディージャック]";
		mes "オークが出るかスネイクが出るか";
		mes "わからないからな。";
		mes "気をつけて先に進む方が";
		mes "良いだろう。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "嫌な気を感じます！";
		mes "戦闘準備をお忘れなく！";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "バカロエルがなんでそんなに、";
		mes "偉そうなのよ！";
		next;
		mes "[ルナイン]";
		mes "……でも確かに嫌な気を感じるわね。";
		mes "事前の心づもりはしておきなさい。";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "（なんだかんだ言いながら優しいなあ！";
		mes "ルナインさん！）";
		set JTB_1QUE,5;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "みなさん！";
			mes "ここに道があるみたいですよー！";
			hideoffnpc getmdnpcname("5番部屋出口#JTB");
			announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			close2;
			cutin "igu01.bmp", 255;
			end;
		}
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "嫌な予感がするわね……。";
		mes "あんたも気をつけなさいよね。";
		close2;
		cutin "igu01.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐北東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

1@jtb.gat,24,106,1	script	ロエル#05	10040,{
	cutin "roel03.bmp", 2;
	mes "[ロエル]";
	mes "僕、昔から音楽には疎いんですよ。";
	mes "だからピアノの音も";
	mes "分からないのかも";
	mes "しれません……！";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

1@jtb.gat,20,108,5	script	ゲルカ#05	629,{
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "ピアノの音……。";
	mes "う～ん、やっぱり";
	mes "聴こえないですね……。";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

1@jtb.gat,29,111,5	script	メロディージャック#05	844,{
	emotion 9;
	mes "[メロディージャック]";
	mes "嫌な予感がする……。";
	mes "油断するなよ。";
	close;
}

//==========================================
// 6番部屋NPC：なだらかな道
//------------------------------------------
1@jtb.gat,111,115,5	script	ロエル#06	10040,{
	if(JTB_1QUE <= 5) {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ルナインさん、大丈夫ですか!?";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "!?";
		mes "べ、別に大丈夫よ！";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "（モンスターを怖がる顔も可愛い！）";
		close2;
		cutin "roel04.bmp", 255;
		end;
	} else {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ルナインさん！";
		mes "早く逃げましょう！";
		mes "さあ、急いで!!";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "ちょ……っ！";
		mes "どこ触ってるのよ、エロル!!";
		next;
		cutin "roel04.bmp", 2;
		mes "[ロエル]";
		mes "ス、スイマセセセンンンン!!";
		close2;
		cutin "roel04.bmp", 255;
		end;
	}
}

1@jtb.gat,116,117,4	script	ルナイン#06	10039,{
	if(JTB_1QUE <= 5) {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ルナインさん、大丈夫ですか!?";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "!?";
		mes "べ、別に大丈夫よ！";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "（モンスターを怖がる顔も可愛い！）";
		close2;
		cutin "roel04.bmp", 255;
		end;
	} else {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ルナインさん！";
		mes "早く逃げましょう！";
		mes "さあ、急いで!!";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "ちょ……っ！";
		mes "どこ触ってるのよ、エロル!!";
		next;
		cutin "roel04.bmp", 2;
		mes "[ロエル]";
		mes "ス、スイマセセセンンンン!!";
		close2;
		cutin "roel04.bmp", 255;
		end;
	}
}

1@jtb.gat,113,113,5	script	ゲルカ#06	629,{
	if(JTB_1QUE <= 5) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "なかなかの強敵でしたね！";
		mes strcharinfo(0)+"さん！";
	} else {
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠……師匠……！";
		next;
		mes "[ゲルカ]";
		mes "無事ですよね……！";
		mes "私、信じてます！";
	}
	close2;
	cutin "gelca02.bmp", 255;
	end;
}

1@jtb.gat,115,113,4	script	アイグ#06	646,{
	if(JTB_1QUE <= 5) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116507))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,6;
				hideoffnpc getmdnpcname("6番部屋出口#JTB");
				announce "‐南東の方角から脱出しよう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				close;
			}
		}
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "なんとかなった……の？";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "roel01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "下手したらヤバかったかもな。";
		next;
		menu "さっきの音はこのモンスターが？",-;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "モンスターがピアノの音を出すなんて";
		mes "面白かったですね！";
		next;
		cutin "gelca01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "いや、違う。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "……ジャック？　どうかしたの？";
		next;
		cutin "igu01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "私が聴いたピアノの音は";
		mes "もっと遠くの方から聴こ……";
		next;
		announce "？？？ : うわあああああああああっ！", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[？？？]";
		mes "うわあああああああああっ！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "!?";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "今の声……何……？";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "男性の声だったの……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "皆さんも、聞こえたんですか……!?";
		next;
		cutin "roel01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "ああ。脳内に直接響くように";
		mes "聞こえてきた……。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "あの……みなさん。";
		mes "今の声ですけど……。";
		next;
		cutin "igu01.bmp", 255;
		announce "？？？ : ああああああああっ!!", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[？？？]";
		mes "ああああああああっ!!";
		next;
		announce "？？？ : や……ヤメロッ!!", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[？？？]";
		mes "や……ヤメロッ!!";
		next;
		announce "？？？ : 気が……狂いそうだ……ッ!!　やめて……く……れ……。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[？？？]";
		mes "気が……狂いそうだ……ッ!!";
		mes "やめて……く……れ……。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "こ、この声ってまさか……。";
		next;
		cutin "roel01.bmp", 255;
		if(select("ニュオーズ!?","ロテルト!?") == 1) {
			emotion 9,getmdnpcname("メロディージャック#06");
			mes "[メロディージャック]";
			mes "いや、違う。この声は……。";
			next;
		} else {
			emotion 9,getmdnpcname("メロディージャック#06");
			mes "[メロディージャック]";
			mes "その可能性が……高い……。";
			next;
		}
		announce "ロテルト : ニュ……ニュオーズーーーーッ!!", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[ロテルト]";
		mes "ニュ……ニュオーズーーーーッ!!";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "ハッキリ聞こえました……やっぱり……";
		mes "やっぱり今のは……師匠の声!!";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "い、一体何が起きてるの!?";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "ニュオーズ様!?";
		mes "ニュオーズ様そこにいるの?!";
		mes "返事してっ!!";
		next;
		cutin "lunain01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "落ち着け!!";
		mes "恐らく、こちらの声は";
		mes "聞こえていない。";
		next;
		announce "少女の声 : だめ……やめ……て……。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[少女の声]";
		mes "だめ……やめ……て……。";
		next;
		announce "少女の声 : どうして……何を間違……。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[少女の声]";
		mes "どうして……何を間違……。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "この声……。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "!?";
		mes "じ、地震……!?";
		misceffect 563,"";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "あ、足場が……っ!!";
		next;
		cutin "igu01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "お前ら、一箇所に固まれ!!";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "揺れがだんだん酷く……!!";
		misceffect 563,"";
		next;
		cutin "gelca01.bmp", 255;
		announce "ニュオーズ : だめだよ……一緒に……約束……。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[ニュオーズ]";
		mes "だめだよ……一緒に……約束……。";
		next;
		cutin "gelca01.bmp", 255;
		announce "少女の声 : いや……イヤ……。", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[少女の声]";
		mes "いや……イヤ……。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "この悲しそうな声……やっぱり……。";
		next;
		cutin "igu01.bmp", 255;
		announce "少女の声 : ニュオーズッ!!", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		mes "[少女の声]";
		mes "ニュオーズッ!!";
		next;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "!!";
		next;
		mes "[メロディージャック]";
		mes "クソ、揺れが酷くなってきた!!";
		mes "このままでは危険だ!!";
		mes "一旦ここから離れるぞ!!";
		misceffect 563,"";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "といってもどこに……";
		mes "あっ!!";
		mes "あそこから、少し光が漏れてます!!";
		mes "ここから出れるかも……。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "……下がっててください!!";
		mes "……潜龍昇天!　雷光弾ッ!!";
		next;
		cutin "gelca01.bmp", 255;
		mes "‐ゲルカの雷光弾により";
		mes "　人一人通れそうな穴が開いた‐";
		next;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "アイツらに何があったかは";
		mes "分からんが……";
		mes "とりあえずお前達だけでも";
		mes "先にここから出るんだ!!";
		mes "私はあいつらを探して";
		mes "連れてから出る!!";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "一緒に行きたいけど、";
		mes "足手まといになりそうだし";
		mes "ジャックにお願いするの……。";
		mes "ニュオーズ達を、お願いなの!!";
		next;
		mes "[アイグ]";
		mes "……。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "アイグ、どうかしたの!?";
		mes "立ち止まって……。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "……もし私たちがあの時";
		mes "険しい道へ行っていたら……";
		mes "どうなってたんだろう……。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "そうね……。";
		mes "もし、やり直せるなら……。";
		next;
		cutin "lunain01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#06");
		mes "[メロディージャック]";
		mes "何してる!!　早く行くんだ!!";
		mes "アイグ!!　ルナイン!!";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "……ごめんなさいなの。";
		mes "みんな、急いで脱出するの！";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "なんでこんなことに……。";
		mes "私達、なにか間違ったっていうの？";
		set JTB_1QUE,6;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			hideoffnpc getmdnpcname("6番部屋出口#JTB");
			announce "‐南東の方角から脱出しよう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		}
		close2;
		cutin "lunain01.bmp", 255;
		end;
	} else {
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "……もし私たちがあの時";
		mes "険しい道へ行っていたら……";
		mes "どうなってたんだろう……。";
		close;
	}
	cutin "lunain01.bmp", 255;
	if(getpartyleader(getcharid(1)) != strcharinfo(0))
		announce "‐南東の方角から脱出しよう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
	end;
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

1@jtb.gat,117,115,5	script	メロディージャック#06	844,{
	if(JTB_1QUE <= 5) {
		emotion 9;
		mes "[メロディージャック]";
		mes "嫌な予感ほど当たるものだ……。";
		close2;
		cutin "igu02.bmp", 255;
		end;
	} else {
		emotion 9;
		mes "[メロディージャック]";
		mes "おい、"+strcharinfo(0)+"";
		mes "ロエル！";
		next;
		mes "[メロディージャック]";
		mes "とりあえず揺れはおさまったが";
		mes "お前達はルナインとゲルカの";
		mes "様子を見ておいてくれ！";
		mes "皆が落ち着き次第、";
		mes "お前達は出るんだ!!";
		next;
		mes "[メロディージャック]";
		mes "こういう状況で冷静でいられる程、";
		mes "あいつらが場馴れしているとは";
		mes "思えないからな……。";
		mes "手間をかけるが、頼んだ。";
		next;
		switch(select("ルナインの様子を見る","ゲルカの様子を見る","アイグの様子を見る")) {
		case 1:
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "どうしよう……どうしよう……";
			mes "ニュオーズ様にもしものことがあったら";
			mes "私……！";
			next;
			cutin "lunain01.bmp", 255;
			mes "["+strcharinfo(0)+"]";
			mes "ルナインは、";
			mes "あの女の子が現れたとき、";
			mes "こういいましたよね？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "^ff99ccニュオーズ様は特別だからに";
			mes "決まってるじゃない。^000000って。";
			mes "だから大丈夫！";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "……なにそれ、私のモノマネ？";
			next;
			cutin "lunain03.bmp", 2;
			mes "[ルナイン]";
			mes "全然似てないじゃない……。";
			next;
			cutin "lunain03.bmp", 255;
			mes "‐ルナインは少しいつもの調子を";
			mes "　取り戻したようだ‐";
			break;
		case 2:
			cutin "gelca04.bmp", 2;
			mes "[ゲルカ]";
			mes strcharinfo(0)+"さん!!";
			mes "師匠は……師匠は大丈夫ですよね？";
			next;
			mes "[ゲルカ]";
			mes "師匠だけじゃない……";
			mes "みんな、みんな、大丈夫ですよね……!?";
			next;
			cutin "gelca04.bmp", 255;
			mes "["+strcharinfo(0)+"]";
			mes "きっと大丈夫。";
			mes "だってゲルカの師匠なんだから。";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "そう……ですよね……。";
			mes "師匠のこと信じてあげないと";
			mes "一番弟子失格ですもんね……。";
			next;
			cutin "gelca03.bmp", 2;
			mes "[ゲルカ]";
			mes "ありがとうございます。";
			mes strcharinfo(0)+"さん。";
			next;
			cutin "gelca03.bmp", 255;
			mes "‐ゲルカは少し元気を";
			mes "　取り戻したようだ‐";
			break;
		case 3:
			emotion 9;
			mes "[メロディージャック]";
			mes "お前がアイグについてくれるのか。";
			mes "なら、安心だな。";
			mes "では、私はゲルカを見ておこう。";
			next;
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "わ、私よりルナインや";
			mes "ゲルカの方が……。";
			next;
			cutin "igu05.bmp", 255;
			mes "["+strcharinfo(0)+"]";
			mes "身体が震えているのが";
			mes "見えたから心配で……。";
			next;
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "あ……。";
			next;
			cutin "igu02.bmp", 2;
			mes "[アイグ]";
			mes "あはは、バレちゃってたの。";
			mes strcharinfo(0)+"、";
			mes "ありがとうなの……。";
			next;
			cutin "igu02.bmp", 255;
			mes "‐アイグの体の震えが";
			mes "　止まったようだ‐";
			break;
		}
		close2;
		cutin "igu02.bmp", 255;
		end;
	}
}

//==========================================
// 8番部屋NPC：険しい道
//------------------------------------------
1@jtb.gat,289,118,3	script	？？？#08	10041,{
	if(JTB_1QUE <= 3) {
		cutin "shaloshi01.bmp", 2;
		mes "[？？？]";
		mes "ニュオーズ……居た。";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	} else {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "感情……。";
		mes "どうすれば泣ける？";
		mes "……どうすれば笑える？";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	}
}

1@jtb.gat,288,122,4	script	ラギ#08	647,{
	if(JTB_1QUE <= 3) {
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "こんな時こそ";
		mes "歌を歌って元気をだしましょう。";
		close2;
		cutin "ragi02.bmp", 255;
		end;
	} else {
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "シャルロシーもいつか";
		mes "自分の気持ちを上手に";
		mes "表現できると良いですねぇ。";
		close2;
		cutin "ragi02.bmp", 255;
		end;
	}
}

1@jtb.gat,283,121,5	script	ニュオーズ#08	625,{
	if(JTB_1QUE <= 3) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,8;
				hideoffnpc getmdnpcname("8番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close;
			}
		}
		cutin "nines03.bmp", 2;
		emotion 2;
		mes "[ニュオーズ]";
		mes "その温もりはいまだに遠く～";
		mes "触れることすらかなわない～";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "さすがですねぇ、ニュオーズ様。";
		next;
		cutin "nines02.bmp", 2;
		emotion 15;
		mes "[ニュオーズ]";
		mes "ありがとう、ラギ君！";
		mes "おや、" + strcharinfo(0) + "！";
		mes "君もいたんだね～！";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ん？　かわいい子を連れているね！";
		mes "その子は誰かな？";
		next;
		menu "迷子みたいなんです",-;
		mes "[ニュオーズ]";
		mes "それはいけないね。";
		mes "出口まで一緒に行こうか。";
		mes "お嬢ちゃん、";
		mes "お名前はなんていうのかな？";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "…………シャルロシー。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "シャルロシーか！";
		mes "私はニュオーズ。彼はラギ君だよ。";
		mes "よろしくね、シャルロシー。";
		mes "出口までみんなで一緒に行こうね。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "よろしくお願いしますね、";
		mes "シャルロシー。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ところで他のみんなは";
		mes "一緒じゃないのかい？";
		next;
		menu "アイグとルナインとはぐれた",-;
		mes "[ニュオーズ]";
		mes "なるほど。";
		mes "じゃあ二人も探さないとだね。";
		next;
		mes "[ニュオーズ]";
		mes "なんだかここは不思議な力で";
		mes "すぐ一緒にいたメンバーが";
		mes "居なくなっちゃうんだよね。";
		mes "せっかく会えたんだ。";
		mes "はぐれないようにしないとね。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……歌で思い出した。";
		next;
		mes "[シャルロシー]";
		mes "……暗闇で聞こえたあの声……。";
		next;
		menu "声？",-;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……真っ暗な所で何か聞こえた。";
		next;
		mes "[シャルロシー]";
		mes "……歌だった。";
		next;
		mes "[シャルロシー]";
		mes "……ニュオーズが歌ってた。";
		next;
		mes "[シャルロシー]";
		mes "……音楽に乗って";
		mes "……知らない言葉いっぱい";
		mes "……流れてきた。";
		next;
		mes "[シャルロシー]";
		mes "……その中の友達っていう言葉、";
		mes "……友達と過ごす日々、";
		mes "……すごく気に入った。";
		next;
		mes "[シャルロシー]";
		mes "……私も友達と一緒に";
		mes "……歌いたいと思った。";
		mes "……だから、お願いした。";
		next;
		mes "[シャルロシー]";
		mes "……友達をくださいって。";
		next;
		mes "[シャルロシー]";
		mes "……そしたら、";
		mes "……アイグとルナインがいた。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "なるほど。";
		mes "もしかしたらそれは音楽の神様が、";
		mes "願いを叶えてくれたのかも";
		mes "しれませんねぇ。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "そうかもしれないね。";
		mes "音楽の神様には、";
		mes "願いや想いを届けてくれたり";
		mes "叶えてくれたりする";
		mes "不思議な力があるのかもしれないね。";
		next;
		mes "[ニュオーズ]";
		mes "そういえばさっきの歌も、";
		mes "依頼主の想い人の誕生石の";
		mes "真珠をイメージした曲で、";
		mes "彼の想いが伝わるようにって";
		mes "作ったんだ。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "この曲を贈る人にも";
		mes "想いが伝わるといいなぁ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……真珠ってなに？";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "シャルロシー、これですよぉ。";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "他にも「人魚の涙」や";
		mes "「月のしずく」「天の露」などとも";
		mes "呼ばれてますねぇ。";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……きれい。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "人魚も涙を流すのかな？";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "どうなんでしょうか。";
		mes "人魚もですが、僕としては";
		mes "魔族やモンスターも泣くのか";
		mes "気になりますねぇ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……魔族やモンスターは泣かない？";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "事実は不明ですが、少なくとも僕は";
		mes "魔族やモンスターが泣いたという話を";
		mes "聞いたことはないですねぇ。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "涙を流すということは";
		mes "感情があるという証拠だろうし、";
		mes "そんな魔族やモンスターがいるなら、";
		mes "私はすぐに友達になれそうだよ♪";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "そんな魔族やモンスターなら、";
		mes "一緒に歌を歌えたら";
		mes "楽しいでしょうねぇ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……どうしたら涙、流せる？";
		next;
		cutin "ragi03.bmp", 2;
		mes "[ラギ]";
		mes "おや、シャルロシーは";
		mes "泣いたことがないのですか？";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……多分ない。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "シャルロシー。涙は泣こうとして";
		mes "流すものじゃないんだよ～。";
		mes "そうして流した涙には";
		mes "意味がないからね。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……しゅん。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "シャルロシーは";
		mes "涙を流してみたいんですねぇ。";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "そうだ、";
		mes "シャルロシーこれをどうぞ。";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……真珠。";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "シャルロシーが";
		mes "いつか涙を流せる時まで、";
		mes "それが涙のかわりって事にしましょう。";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……わかった。";
		next;
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "さすがだね、ラギ君！";
		mes "ラギ君なら";
		mes "素晴らしいクラウンやミンストレルに";
		mes "なれると思うよ～！";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "ありがとうございます。";
		mes "でも僕は、まだしばらく";
		mes "バードのままでいたいんですよねぇ。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "はは、バードでも歌えるもんね！";
		mes "職業はあまり関係ないか♪";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……私も一緒に歌いたい。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "そうだね♪";
		mes "今度シャルロシーにも";
		mes "歌い方を教えてあげようね！";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "その時はみんなで歌いましょう。";
		mes "もちろん、";
		mes strcharinfo(0)+ "さんも";
		mes "一緒にですよぉ。";
		set JTB_1QUE,8;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			hideoffnpc getmdnpcname("8番部屋出口#JTB");
		}
		close2;
		cutin "ragi01.bmp", 255;
		end;
	} else {
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "いつか、シャルロシーとも";
		mes "歌ってみたいね。";
		mes "きっと楽しいよ。";
		close2;
		cutin "nines03.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// 10番部屋NPC：険しい道
//------------------------------------------
1@jtb.gat,38,197,4	script	シャルロシー#10	10041,{
	if(JTB_1QUE <= 8) {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "はぐれないように手……つなぐ。";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	} else {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "他人が考えていること";
		mes "聞こえない？";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	}
}

1@jtb.gat,34,198,5	script	ニュオーズ#10	625,{
	if(JTB_1QUE <= 8) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,10;
				hideoffnpc getmdnpcname("10番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close;
			}
		}
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes strcharinfo(0) + "！";
		mes "シャルロシー！　良かった！";
		mes "無事だったんだね～！";
		mes "今の戦闘でラギ君とは";
		mes "はぐれてしまったよ……。";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		switch(select("このまま会話を続ける","他のメンバーを探す")) {
		case 1:
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……ニュオーズ、";
			mes "安心したらお腹すいたの？";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "えっ!?　私そんなこと言った？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……聞こえた。";
			mes strcharinfo(0) + "には";
			mes "聞こえなかった？";
			next;
			menu "聞こえなかった",-;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "……。";
			next;
			mes "[ニュオーズ]";
			mes "……もしかしてシャルロシーには";
			mes "人の心の声が聞こえるの？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……聞こえる。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……？";
			mes "どうして怖がってるの？";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "とりあえずシャルロシーが";
			mes "人の心を読めることは";
			mes "一旦みんなには内緒にして……";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……残念ね、聞こえてるわよって";
			mes "ミンミンが言ってる。";
			next;
			cutin "nines04.bmp", 2;
			mes "[ニュオーズ]";
			mes "ミンミン!?";
			mes "い、いつのまにそこにいたんだい!?";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				hideoffnpc getmdnpcname("ミンミン#10");
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "さっきから居たわよ。";
			mes "とりあえずいつかバレるんだし、";
			mes "ちゃんと説明しなさい。";
			mes "あっちに何人かいるから。";
			next;
			cutin "min02.bmp", 255;
			mes "‐結局、シャルロシーが";
			mes "　心の声を口に出さないと約束し、";
			mes "　この話は一旦、終わることになった‐";
			next;
			mes "‐人の心が読めるシャルロシーは";
			mes "　人間ではないのだろうか……‐";
			set JTB_1QUE,10;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("10番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "nines01.bmp", 255;
			end;
		case 2:
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ん？　あっちから声がするよ！";
			mes "誰かこっちに向かってきてる！";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "おーい！　やっぱりニュオーズ達だ！";
			mes "みんな～ニュオーズ達がいたよー！";
			mes strcharinfo(0) + "と";
			mes "シャルロシーも一緒だよ！";
			next;
			cutin "lunain01.bmp", 2;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				hideoffnpc getmdnpcname("アラン#10");
			mes "[ルナイン]";
			mes "シャルロシー！　ニュオーズ様や";
			mes strcharinfo(0) + "と";
			mes "一緒だったのね。よかったわ。";
			next;
			cutin "nines01.bmp", 2;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("ロエル#10");
				hideoffnpc getmdnpcname("ルナイン#10");
				hideoffnpc getmdnpcname("ロテルト#10");
				hideoffnpc getmdnpcname("ゲルカ#10");
				hideoffnpc getmdnpcname("ミンミン#10");
			}
			mes "[ニュオーズ]";
			mes "みんな無事だったかい？";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "大丈夫。みんなケガとかしてないよ！";
			mes "でもモンスターがいっぱいいて";
			mes "大変だったんだから！";
			next;
			cutin "nines02.bmp", 2;
			mes "[ニュオーズ]";
			mes "ヒーローは最後に";
			mes "現れるものだよ、アラン！";
			mes "私のようにね！";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "そこまで計算してたなんて、";
			mes "さすがニュオーズ様!!";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "その割には間に合ってないけどね。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "こいつがヒーローだと、";
			mes "俺はどうなるんだ!?";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "師匠は……。";
			next;
			cutin "arang02.bmp", 2;
			mes "[アラン]";
			mes "闇落ちしたヒーローのライバル!!";
			mes "とか！";
			next;
			cutin "roel03.bmp", 2;
			mes "[ロエル]";
			mes "すごく似合いそうです!!";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "そんないい役、";
			mes "ロテルトには勿体無いわよ。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……ロテが、ライバルには";
			mes strcharinfo(0) + "が";
			mes "いいかもって。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "なっ!?";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……ミンミンは女幹部？";
			next;
			cutin "gelca04.bmp", 2;
			emotion 23,getmdnpcname("ゲルカ#10");
			mes "[ゲルカ]";
			mes "わわわわ、私じゃないですよ!?";
			mes "私そんなこと言ってませんからっ！";
			mes "……って、あれ？";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "ちょっと待ちなさいよ!?";
			mes "この子、もしかして……。";
			next;
			cutin "shaloshi02.bmp", 2;
			emotion 23,getmdnpcname("ルナイン#10");
			mes "[シャルロシー]";
			mes "……やだ、私が";
			mes "いつもニュ……（もごもご）";
			next;
			cutin "lunain04.bmp", 2;
			emotion 19,getmdnpcname("ルナイン#10");
			mes "[ルナイン]";
			mes "シ、シャルロシー!!";
			mes "あなたもしかして";
			mes "みんなの考えていることがわかるの!?";
			next;
			cutin "roel03.bmp", 2;
			mes "[ロエル]";
			mes "ルナインさん……";
			mes "とりあえずその塞いでる手を外さないと";
			mes "話せないと思います……。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ぷはー。";
			mes "……聞こえる。";
			mes "……心の声、みんなには聞こえない？";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "私は聞こえたことないよ……。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……こいつやっぱりここで……";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……ニュオーズ、";
			mes "みんなどうして怖がってるの？";
			next;
			mes "[シャルロシー]";
			mes "……心の声、聞こえちゃいけないの？";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー。";
			mes "一つ私やみんなと約束しよう。";
			next;
			mes "[ニュオーズ]";
			mes "心の声が聞こえるのが";
			mes "良いか悪いか、私には決められない。";
			next;
			mes "[ニュオーズ]";
			mes "だけど、みんな心の中で";
			mes "秘密に思ってる事や";
			mes "悩んでることがあるかもしれない。";
			next;
			mes "[ニュオーズ]";
			mes "心の中っていうのは";
			mes "そういうものなんだよ。";
			mes "だからみんなの声が聞こえても、";
			mes "口に出しちゃいけないよ。";
			next;
			cutin "nines03.bmp", 2;
			mes "[ニュオーズ]";
			mes "心の中のナイショがバレちゃうと、";
			mes "みんなが困ったり、びっくりしたり、";
			mes "悲しくなっちゃうかもしれないからね。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……うん。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……みんな、ごめんなさい。";
			next;
			cutin "nines03.bmp", 2;
			mes "[ニュオーズ]";
			mes "いい子だね、シャルロシー。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "おい、ニュオーズ……";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ロテ。……後でね。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……チッ。勝手にしろ!!";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "バカバカしい。";
			mes "大体、頭の中読まれて困るのは";
			mes "ロテルトぐらいでしょ。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "それより早くここから出て、";
			mes "お風呂に入る事の方が大事だわ。";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "そうですね……それに本じゃ、";
			mes "そういう力がある方が";
			mes "大変なこと多いですし……。";
			next;
			cutin "arang03.bmp", 2;
			mes "[アラン]";
			mes "よく考えたら、私も";
			mes "読まれても困ることなんて";
			mes "考えたことないかも!!";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "……わ、私も読まれて困る事なんて";
			mes "な、ないんだから……。";
			next;
			cutin "roel03.bmp", 2;
			mes "[ロエル]";
			mes "（こっそり僕が";
			mes "ルナインさんの言動に萌えてるの、";
			mes "バレちゃう……!?）";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "（心が読めるということは";
			mes "こいつ、人間じゃない……のか？）";
			set JTB_1QUE,10;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("10番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "nines01.bmp", 255;
			end;
		}
	} else {
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテは気付いたのかな。";
		mes "シャルロシーの……。";
		close2;
		cutin "nines01.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

1@jtb.gat,38,191,4	script	ミンミン#10	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あのガキ……";
	mes "やっぱり怪しいわね……。";
	mes "研究材料にしてやろうかしら。";
	close2;
	cutin "min01.bmp", 255;
	end;
}

1@jtb.gat,34,193,5	script	ロエル#10	10040,{
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "シャルロシー……";
	mes "道中、ルナインさんから";
	mes "話は聞いていましたけど";
	mes "本当に不思議な女の子ですね。";
	close2;
	cutin "roel02.bmp", 255;
	end;
}

1@jtb.gat,40,193,4	script	アラン#10	644,{
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "他の人の考えてることが";
	mes "わかるなんて凄いなー！";
	mes "私も練習すればできるかなー？";
	close2;
	cutin "arang01.bmp", 255;
	end;
}

1@jtb.gat,40,198,3	script	ルナイン#10	10039,{
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "人の心を読む力……";
	mes "昔、大聖堂で読んだ本には";
	mes "悪魔は人の心を読み、惑わす……";
	mes "なんて書いてあったわね。";
	next;
	cutin "lunain03.bmp", 2;
	mes "[ルナイン]";
	mes "シャルロシーはさしずめ";
	mes "ニュオーズ様の心を惑わす";
	mes "小悪魔ってところかしら？";
	close2;
	cutin "lunain02.bmp", 255;
	end;
}

1@jtb.gat,36,191,5	script	ゲルカ#10	629,{
	cutin "gelca04.bmp", 2;
	mes "[ゲルカ]";
	mes "私も師匠の心の中を読めれば……";
	mes "い、いえ！　何でもありません！";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

1@jtb.gat,31,194,5	script	ロテルト#10	630,{
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "他人の心を読めるだと……？";
	mes "このガキ……";
	mes "いや、まさかな……。";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

//==========================================
// 11番部屋NPC：険しい道
//------------------------------------------
1@jtb.gat,108,198,5	script	シャルロシー#11	10041,{
	if(JTB_1QUE <= 10) {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "みんな怪我してる……。";
		mes "大丈夫？　治る？";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	} else {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ペルは友達じゃない……。";
		mes "私の友達は……誰？";
		close2;
		cutin "shaloshi01.bmp", 255;
		end;
	}
}

1@jtb.gat,110,196,5	script	ロエル#11	10040,{
	if(JTB_1QUE <= 10) {
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "僕は大丈夫です。";
		mes "シャルロシーを守れましたから。";
		mes "誰かを守る事ができて誇らしいです。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "モンスターと友達……。";
		mes "人間がみんなシャルロシーみたいに";
		mes "モンスターと友達になれるなら、";
		mes "モンスターと人間が共存する";
		mes "平和な世の中になるんでしょうね。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,112,196,3	script	ルナイン#11	10039,{
	if(JTB_1QUE <= 10) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,11;
				hideoffnpc getmdnpcname("11番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close2;
				npcskillsupport 28,9999;
				heal 99999,0;
				end;
			}
		}
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "何よ、今の大きなモンスター……。";
		mes "今までいっぱい居た小さいのとは";
		mes "段違いの強さだったわ……。";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ロエル。ルナイン。怪我してる。";
		mes "大丈夫？";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "私は平気よ。";
		mes "ちょっとロエル！";
		mes "あんた怪我してるじゃない!!";
		mes "こっち来なさい!!";
		next;
		cutin "roel04.bmp", 2;
		mes "[ロエル]";
		mes "ぼ、僕は大丈夫です。";
		mes "このくらい大したこと……。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "いいから来なさい!!";
		next;
		switch(select("シャルロシーの様子を見る","ロエルの様子を見る")) {
		case 1:
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				misceffect 313,getmdnpcname("ロエル#11");
			cutin "lunain04.bmp", 255;
			mes "‐ヒールされているロエルを見て";
			mes "　シャルロシーは悲しげに口を開く‐";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				misceffect 313,getmdnpcname("ロエル#11");
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……ペル、前は暴れなかったのに。";
			next;
			menu "ペルってモンスターの名前？",-;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルペル鳴くから「ペル」。";
			mes "噛んだり、暴れたりしなかった。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "だから友達になった。";
			mes "でも……。";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "モンスターと友達に!?";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……変？";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "シャルロシーはわかってない";
			mes "みたいだから言うけど。";
			next;
			mes "[ルナイン]";
			mes "モンスターとは友達になれない。";
			mes "あいつらは私達にとって敵よ。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……敵？";
			next;
			mes "[シャルロシー]";
			mes "敵って何？";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "僕達に害をなす相手……でしょうか。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "簡単にいうと、";
			mes "私達に痛いことをしたり";
			mes "困らせたりする相手。";
			next;
			mes "[ルナイン]";
			mes "モンスターとは友達になれない。";
			mes "あいつらは私達にとって敵よ。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "でもペルは、私に痛いことや";
			mes "困ることをしたことない。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "今まではそうだった";
			mes "かもしれないけど、";
			mes "今は違うでしょ？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "今は……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "さ、次は";
			mes strcharinfo(0) + "の番よ。";
			mes "そこに座りなさい。";
			next;
			npcskillsupport 28,9999;
			heal 99999,0;
			cutin "lunain01.bmp", 255;
			mes "‐シャルロシーは何か";
			mes "　考え込んでいるようだ‐";
			next;
			mes "‐声をかけようとしたが";
			mes "　ルナインに捕まってしまったので";
			mes "　話すのは難しそうだ‐";
			set JTB_1QUE,11;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("11番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "lunain02.bmp", 255;
			end;
		case 2:
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				misceffect 313,getmdnpcname("ロエル#11");
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "まったく……先陣きって、";
			mes "モンスターにつっこみすぎ!!";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				misceffect 313,getmdnpcname("ロエル#11");
			cutin "roel04.bmp", 2;
			mes "[ロエル]";
			mes "す、すいません!!";
			mes "皆さんの役に立てるのが";
			mes "嬉しくてつい……。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ルナイン。";
			mes "文句言いながら治療してる。";
			next;
			cutin "roel02.bmp", 2;
			mes "[ロエル]";
			mes "優しいですよね、";
			mes "ルナインさん!!";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "か、勘違いしないでよね!!";
			mes "子供1人の世話も";
			mes "できないのかって、";
			mes "ニュオーズ様に";
			mes "思われたくないだけよ!!";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "顔が赤い。";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "う、うるさいわね！";
			mes "……ちょ、ちょっとこの洞窟が";
			mes "暑いだけよ!!";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルは、ここは洞窟じゃないって";
			mes "言ってた。";
			next;
			menu "ペル？",-;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ルナインとアイグに会う前に、";
			mes "いっぱいいた。";
			next;
			cutin "roel02.bmp", 2;
			mes "[ロエル]";
			mes "ペルさんですか。";
			mes "僕はまだお会いしたことが";
			mes "ない気がしますね。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "名前はないっていうから、";
			mes "私がつけた。";
			next;
			mes "[シャルロシー]";
			mes "ペルペル鳴くから「ペル」。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "もしかしてあの小さいモンスター？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルペル鳴くだけ。";
			mes "噛んだり、暴れたりしなかった。";
			next;
			mes "[シャルロシー]";
			mes "だから友達になった。";
			mes "でも……。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "シャルロシーはわかってない";
			mes "みたいだから言うけど。";
			next;
			mes "[ルナイン]";
			mes "モンスターとは友達になれない。";
			mes "あいつらは私達にとって敵よ。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "……敵？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "敵って何？";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "僕達に害をなす相手……でしょうか。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "簡単にいうと、";
			mes "私達に痛いことをしたり";
			mes "困らせたりする相手。";
			next;
			mes "[ルナイン]";
			mes "モンスターと平和的にお話しで";
			mes "問題を解決なんて無理。";
			mes "だから戦うしかないのよ。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "でもペルは、私に痛いことや";
			mes "困ることをしたことない。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "今まではそうだった";
			mes "かもしれないけど、";
			mes "今は違うでしょ？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "今は……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……。";
			next;
			cutin "roel02.bmp", 2;
			mes "[ロエル]";
			mes "そ、そうだ！";
			next;
			cutin "roel03.bmp", 2;
			mes "[ロエル]";
			mes "……ぺ、ペルペルペルペル!!";
			next;
			menu "ロエル!?",-;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "ちょ……なにやってるのよ!?";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "え……いや……";
			mes "僕がペルのかわりに";
			mes "シャルロシーさんのお友達にと……。";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "ふーん？";
			mes "ってことは……";
			mes "倒すしかないわね。";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				misceffect 85,getmdnpcname("ロエル#11");
			cutin "roel03.bmp", 2;
			mes "[ロエル]";
			mes "ペ……ペルー!?";
			next;
			cutin "lunain03.bmp", 2;
			mes "[ルナイン]";
			mes "冗談よ。";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "さ、次は";
			mes strcharinfo(0) + "の番よ。";
			mes "そこに座りなさい。";
			next;
			npcskillsupport 28,9999;
			heal 99999,0;
			cutin "lunain03.bmp", 255;
			mes "‐シャルロシーは何か";
			mes "　考え込んでいるようだ‐";
			next;
			mes "‐とりあえず今はそっと";
			mes "　しておいた方がいいだろう‐";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルは友達じゃない……";
			mes "でも……。";
			set JTB_1QUE,11;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("11番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "lunain02.bmp", 255;
			end;
		}
	} else {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "モンスターをペットにする人もいるけど";
		mes "あれは例外ね。";
		mes "やっぱりモンスターは危険で";
		mes "友達にはなれないのよ。";
		close2;
		cutin "lunain02.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// 12番部屋NPC：険しい道
//------------------------------------------
1@jtb.gat,192,205,5	script	アイグ#12	646,{
	if(JTB_1QUE <= 11) {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシー、やっと会えたの！";
		mes "無事で良かったの！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシーを放ってなんて";
		mes "おけないの！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,201,203,4	script	アラン#12	644,{
	if(JTB_1QUE <= 11) {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "ようやくみんなと合流できたよ。";
		mes "でも、シャルロシーが";
		mes "少し元気なさそう……。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "そんな……";
		mes "せっかく友達になれそうだと";
		mes "思ってたのに……。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,191,204,5	script	ラギ#12	647,{
	if(JTB_1QUE <= 11) {
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "みなさんとも合流できましたし";
		mes "そろそろクライマックスですかねぇ。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "彼女は別れ際に一体";
		mes "何を想ったんでしょうねぇ。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,192,202,5	script	ルナイン#12	10039,{
	if(JTB_1QUE <= 11) {
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "みんなとも合流できたし。";
		mes "早く帰ってシャワーでも";
		mes "浴びたいわね。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "私はニュオーズ様を追うわ。";
		mes "シャルロシーの事も";
		mes "気になるしね。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,191,200,5	script	ロエル#12	10040,{
	if(JTB_1QUE <= 11) {
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "みなさんと合流は出来ましたが";
		mes "まだ、油断は禁物です！";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "あ、でも怪我をすれば";
		mes "またルナインさんにヒールを……";
		mes "……な、何でもありません！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "普段は何だかんだ言っても";
		mes "ロテルト様とニュオーズ様は";
		mes "やっぱり親友なんですね！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,199,200,4	script	ミンミン#12	643,{
	if(JTB_1QUE <= 11) {
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "あいつの手紙に乗せられて";
		mes "ホイホイこんな所まで来て、";
		mes "私も結構お人好しよね。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	} else {
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "背格好ばかり大人になって";
		mes "ロテルトもまだまだ子供ね。";
		mes "ニュオーズの事になると";
		mes "すぐに感情的に動くんだもの。";
		next;
		mes "[ミンミン]";
		mes "何てね、これじゃあ私が";
		mes "年寄りみたいじゃない……。";
		mes "私はまだまだ若いんだから";
		mes "勘違いしちゃダメよ、";
		mes strcharinfo(0) + "。";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
}

1@jtb.gat,199,204,4	script	ゲルカ#12	629,{
	if(JTB_1QUE <= 11) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "さっきから起こる地震って";
		mes "何かのきっかけで";
		mes "起こっているような";
		mes "気がしませんか？";
		next;
		mes "[ゲルカ]";
		mes "地震が起こる度に";
		mes "まるで人の気持ちみたいに";
		mes "雰囲気が変わったり、";
		mes "空間が不安定になってる";
		mes "気がするんです。";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	} else {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "確かにこのまま進むのは";
		mes "危険かも知れませんが";
		mes "私は師匠を信じます！";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "だって、私の師匠なんですから！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
}

1@jtb.gat,189,203,5	script	メロディージャック#12	844,{
	if(JTB_1QUE <= 11) {
		mes "[メロディージャック]";
		mes "ようやく全員揃ったか。";
		mes "さっさと出口を探して";
		mes "脱出するぞ。";
		close;
	} else {
		mes "[メロディージャック]";
		mes "こうなる気はしていたが……";
		mes "ロテルトの判断は意外だったな。";
		mes "メンバー全員を危険に晒す選択肢を";
		mes "選ぶとは思わなかったぞ。";
		close;
	}
}

1@jtb.gat,195,200,5	script	シャルロシー#12	10041,{
	cutin "shaloshi03.bmp", 2;
	mes "[シャルロシー]";
	mes "……。";
	close2;
	cutin "shaloshi03.bmp", 255;
	end;
}

1@jtb.gat,195,206,4	script	ニュオーズ#12	625,{
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "地震の回数が増えてきたね。";
	mes "みんな大丈夫かい？";
	close2;
	cutin "nines01.bmp", 255;
	end;
}

1@jtb.gat,198,206,4	script	ロテルト#12	630,{
	if(JTB_1QUE <= 11) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			if(checkquest(116508))
				set '@str$,"急ぐ";
			if(select('@str$,"会話をする") == 1) {
				stopnpctimer;
				set JTB_1QUE,12;
				hideoffnpc getmdnpcname("12番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
				mes "‐あなたは記憶を探りながら";
				mes "　先を急ぐことにした‐";
				close2;
				hideonnpc getmdnpcname("ニュオーズ#12");
				hideonnpc getmdnpcname("シャルロシー#12");
				end;
			}
		}
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……おい、みんな待て！";
		mes "何か変だぞ！";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		cutin "nines01.bmp", 2;
		misceffect 563,"";
		mes "[ニュオーズ]";
		mes "わっ！　また地震!?";
		next;
		cutin "nines01.bmp", 255;
		mes "[メロディージャック]";
		mes "……まずいな。";
		next;
		mes "[メロディージャック]";
		mes "空間の崩壊が始まっているようだ。";
		next;
		switch(select("簡単に現状を知りたい","詳細に現状を知りたい")) {
		case 1:
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルが……怒ってる。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "この空間とペルは何か";
			mes "関係があるのかい？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルは……私を守るために、";
			mes "みんなを攻撃したの。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……どういうことだ!?";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……それは……。";
			next;
			emotion 0,getmdnpcname("シャルロシー#12");
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ペル……？";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("ペル#12a");
				hideoffnpc getmdnpcname("ペル#12b");
			}
			emotion 6,getmdnpcname("ペル#12b");
			mes "[ペル]";
			mes "ペルペルペル!!";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "何か言ってるみたいですね……。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "うん……。";
			mes "わかった……。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー？";
			mes "ペルは何て言っているんだい？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ニュオーズ……。";
			mes "みんな……。";
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				misceffect 316,getmdnpcname("シャルロシー#12");
				misceffect 317,getmdnpcname("シャルロシー#12");
			}
			next;
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "どうしたの？";
			mes "すごく悲しそうな顔してるの……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ごめんなさい……";
			mes "ばいばい……。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー！";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideonnpc getmdnpcname("シャルロシー#12");
				hideonnpc getmdnpcname("ペル#12a");
				hideonnpc getmdnpcname("ペル#12b");
			}
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "あのモンスターも居ません！";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "うわっ、地震!?";
			misceffect 563,"";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "洞窟の様子がおかしいわ!!";
			mes "早くここから出るわよ!!";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "…………。";
			next;
			mes "[ニュオーズ]";
			mes "……ロテ、ミンミン、ジャック。";
			mes "みんなをお願いするね。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "おい、お前まさか……!!";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "あの子に約束したから。";
			mes "歌の歌い方を教えてあげるって。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "だから、あの子を迎えにいってくるね。";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "ニュオーズ様!!";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				hideonnpc getmdnpcname("ニュオーズ#12");
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……あのバカッ!!";
			mes "お前ら!!　ニュオーズを追うぞ!!";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "全員、気を引き締めろ！";
			mes "油断するんじゃねえぞ!!";
			set JTB_1QUE,12;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("12番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "rote03.bmp", 255;
			end;
		case 2:
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "一体何が起きてるのかしら。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー？";
			mes "どうかしたかい？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルが……怒ってる。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ペル？";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "ペルって、あの小さい";
			mes "モンスターのことなの？";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルは……私の友達……。";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "まだいってるの？";
			mes "あれはモンスターなの！";
			mes "人間とは友達になれないのよ！";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ルナイン、シャルロシーの話を";
			mes "聞いてあげよう。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "ニュオーズ様……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ペルは……私を守るために、";
			mes "みんなを攻撃したの。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……どういうことだ!?";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……それは……。";
			next;
			emotion 0,getmdnpcname("シャルロシー#12");
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ペル……？";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("ペル#12a");
				hideoffnpc getmdnpcname("ペル#12b");
			}
			emotion 6,getmdnpcname("ペル#12b");
			mes "[ペル]";
			mes "ペルペルペル!!";
			next;
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "何か言ってるみたいですね……。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "うん……。";
			mes "わかった……。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー？";
			mes "ペルは何て言っているんだい？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ニュオーズ……。";
			mes "みんな……。";
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				misceffect 316,getmdnpcname("シャルロシー#12");
				misceffect 317,getmdnpcname("シャルロシー#12");
			}
			next;
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "どうしたの？";
			mes "すごく悲しそうな顔してるの……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "ごめんなさい……";
			mes "ばいばい……。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "シャルロシー！";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideonnpc getmdnpcname("シャルロシー#12");
				hideonnpc getmdnpcname("ペル#12a");
				hideonnpc getmdnpcname("ペル#12b");
			}
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "あのモンスターも居ません！";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "うわっ、地震!?";
			misceffect 563,"";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "洞窟の様子がおかしいわ!!";
			mes "早くここから出るわよ!!";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "…………。";
			next;
			mes "[ニュオーズ]";
			mes "……ロテ、ミンミン、ジャック。";
			mes "みんなをお願いするね。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "おい、お前まさか……!!";
			next;
			cutin "nines03.bmp", 2;
			mes "[ニュオーズ]";
			mes "私の唯一の自慢は人に";
			mes "嘘をついたことが";
			mes "ないことなんだよね♪";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "あの子に約束したから。";
			mes "歌の歌い方を教えてあげるって。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "だから、あの子を迎えにいってくるね。";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "ニュオーズ様!!";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				hideonnpc getmdnpcname("ニュオーズ#12");
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "シャルロシーも心配だし、";
			mes "私はニュオーズを追うの!!";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "さて……どうするかは";
			mes "あなたに任せるわ。";
			mes "ギルドマスター。";
			next;
			cutin "gelca04.bmp", 2;
			mes "[ゲルカ]";
			mes "師匠!!";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……答えるまでもねーだろ!!";
			next;
			menu "行きましょう！",-;
			cutin "roel04.bmp", 2;
			mes "[ロエル]";
			mes "ぼ、僕は今、猛烈に";
			mes "感動しています!!";
			next;
			cutin "roel04.bmp", 255;
			emotion 9,getmdnpcname("メロディージャック#12");
			mes "[メロディージャック]";
			mes "ここまで甘ちゃんだと、";
			mes "命が幾つあっても足りんな。";
			next;
			mes "[メロディージャック]";
			mes "……フン。";
			mes "油断だけはするなよ。";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "よーし！　はりきって出発！";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "全員、気を引き締めろ！";
			mes "油断するんじゃねえぞ!!";
			set JTB_1QUE,12;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideoffnpc getmdnpcname("12番部屋出口#JTB");
				announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
			}
			close2;
			cutin "rote03.bmp", 255;
			end;
		}
	} else {
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "ニュオーズの野郎……";
		mes "いつも勝手な事ばかり";
		mes "しやがって……。";
		close2;
		cutin "rote03.bmp", 255;
		if(getpartyleader(getcharid(1)) != strcharinfo(0))
			announce "‐東の方角から奥へ進もう‐", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		end;
	}
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

1@jtb.gat,194,200,5	script	ペル#12a	10047,{
	end;
}

1@jtb.gat,196,200,5	script	ペル#12b	10047,{
	end;
}

//==========================================
// トンネル部屋：険しい道
//------------------------------------------
1@jtb.gat,318,358,5	script	ニュオーズ#21	625,{
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "あれ……";
	mes strcharinfo(0) + "!?";
	next;
	menu "経緯を話す",-;
	mes "[ニュオーズ]";
	mes "なるほど。みんな私を追って";
	mes "ここに向かってくれているんだね。";
	mes "やはり持つべきものは";
	mes "ギルドメンバーだね！";
	next;
	mes "[ニュオーズ]";
	mes "では私たちは先に";
	mes "シャルロシーを探そう。";
	mes "何が起きるかわからないから、";
	mes "戦闘準備だけは忘れずにね。";
	next;
	mes "[ニュオーズ]";
	mes "さあいこう！";
	close2;
	cutin "nines01.bmp", 255;
	end;
}

//==========================================
// 22番部屋NPC：険しい道
//------------------------------------------
1@jtb.gat,324,327,4	script	ペル#22	10047,{
	mes "[ペル]";
	mes "ペル！　ペル！";
	close;
}

1@jtb.gat,324,327,4	script	ペル#23	10048,{
}

1@jtb.gat,326,329,4	script	シャルロシー#22	10041,{
	cutin "shaloshi03.bmp", 2;
	mes "[シャルロシー]";
	mes "どうして……。";
	close2;
	cutin "shaloshi03.bmp", 255;
	end;
}

1@jtb.gat,320,323,5	script	ニュオーズ#22	625,{
	cutin "nines04.bmp", 2;
	mes "[ニュオーズ]";
	mes "はあ、はあ……";
	mes "あっ、あそこにいるのは……！";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0))
		stopnpctimer;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "ペル、いいこいいこ。";
	mes "頭をなでると安心するんだって。";
	mes "ニュオーズが教えてくれた。";
	next;
	cutin "shaloshi02.bmp", 255;
	mes "[ペル]";
	mes "ペルー。";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "ペルもしたいの？";
	mes "ありがとう。でも、";
	mes "ペルは私より小さいから無理だよ。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "そうそう。";
	mes "シャルロシーの頭を撫でるのは、";
	mes "私達の特権だからね。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "ニュオーズ……";
	mes strcharinfo(0) + "……";
	mes "どうして……。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "シャルロシー、";
	mes "君とちゃんと話がしたくてね。";
	next;
	mes "[ニュオーズ]";
	mes "他のみんなもこっちに";
	mes "向かってるみたいなんだけど、";
	mes "まだ迷ってるのかな？";
	mes "ここは迷いやすいみたいだからね。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "迷いやすい……";
	mes "みんなが来れないのは";
	mes "私のせいかもしれない。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "シャルロシー。";
	mes "私のせいかもって、どういう……";
	next;
	cutin "nines01.bmp", 255;
	mes "[ペル]";
	mes "ペルルルルルル……";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "ペル？";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "ペル、私は大丈夫。";
	mes "だから……";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "……ペルはなんて？";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "私を連れ去ろうとする人間は";
	mes "許さないって……";
	mes "……ペル？";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0))
		misceffect 173,getmdnpcname("ペル#22");
	cutin "shaloshi01.bmp", 255;
	mes "[ペル]";
	mes "ペルペル！ペルペル!!";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0))
		misceffect 173,getmdnpcname("ペル#22");
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "どうしよう……";
	mes "ペルの力が強まっていく……。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ペル、落ち着くんだ。";
	mes "私は君の友達を奪ったりしないよ。";
	mes "ただ私もシャルロシーと……。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "ペル……お願い……";
	mes "話を聞いて……。";
	next;
	cutin "shaloshi01.bmp", 255;
	mes "[ペル]";
	mes "ペルペル、ペルペル、ペル！";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		misceffect 173,getmdnpcname("ペル#22");
		misceffect 90,getmdnpcname("ペル#23");
		misceffect 183,getmdnpcname("ペル#23");
		hideonnpc getmdnpcname("ペル#22");
		hideoffnpc getmdnpcname("ペル#23");
	}
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ペルの姿が……!!";
	mes "……ふう。どうやら、";
	mes "聞く耳もたないって感じだね。";
	mes "仕方ない、戦おう。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "でも……";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "……ニュオーズ……";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "うん……信じる……";
	mes "だから、ペルを止めて……！";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "ああ！　私たちに任せて！";
	close2;
	cutin "nines03.bmp", 255;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		announce "ニュオーズ : シャルロシーの友達に手荒な真似はしたくないけど、今はそんなこと言ってる場合じゃないね！", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		if(!sleep2(3000)) end;
		announce "ニュオーズ : ペル!!　君を止めて、みんなで話をしたいんだ！　だから……", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		if(!sleep2(3000)) end;
		announce "ニュオーズ : 私たちも全力でいくよ!!", 0x9, 0xffff00, 0x0190, 16, 0, 0;
		if(!sleep2(3000)) end;
		donpcevent getmdnpcname("jitter_control22")+"::OnStart";
	}
	end;
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

1@jtb.gat,320,323,5	script	ニュオーズ#boss	625,{
	end;
OnStart:
	unittalk getnpcid(0,getmdnpcname("ニュオーズ#boss")),"ニュオーズ : 私も協力するから、心配無用さ！";
	initnpctimer;
OnTimer30000:
	set '@rnd,rand(1,5);
	switch('@rnd) {
	case 1:
		unittalk getnpcid(0,"ニュオーズ#boss"),"ニュオーズ : バナナが腐ってた？　そんなバナナ！";
		break;
	case 2:
		unittalk getnpcid(0,"ニュオーズ#boss"),"ニュオーズ : ビフロストで肉を食べたのさ。　メニューはローストビーフ！";
		break;
	case 3:
		unittalk getnpcid(0,"ニュオーズ#boss"),"ニュオーズ : ジルバの意味？　そんなのジルバ！";
		break;
	case 4:
		unittalk getnpcid(0,"ニュオーズ#boss"),"ニュオーズ : 肉が憎い！";
		break;
	case 5:
		unittalk getnpcid(0,"ニュオーズ#boss"),"ニュオーズ : ちょっと待って。ウクレレの弦が切れて演奏ができない……。歌でも歌っておこうか？";
		break;
	}
	emotion 2;
	set '@boss,getvariableofnpc('boss,getmdnpcname("jitter_control22"));
	mobuseskill '@boss, 89, 1, 0, 0, 63, 0, 0;	//ストームガスト
	mobuseskill '@boss, 664, 5, 0, 0, -1, 0, 0;	//ワイドフリーズ
	initnpctimer;
	end;
}

//==========================================
// 23番部屋NPC：険しい道（22番と同じマップ）
//------------------------------------------
1@jtb.gat,328,326,4	script	ロテルト#23	630,{
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "お前ら！　無事だったか……。";
	mes "心配させやがって！";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

1@jtb.gat,330,328,4	script	ゲルカ#23	629,{
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "あんなに強そうなモンスターを";
	mes "倒してしまうなんて、";
	mes strcharinfo(0) + "さんって";
	mes "凄く強いんですね！";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

1@jtb.gat,329,323,4	script	ミンミン#23	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あなた、結構やるのね。";
	mes "口下手なロテルトに変わって";
	mes "礼を言うわ。";
	mes "ニュオーズを助けてくれて";
	mes "ありがとう。";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

1@jtb.gat,317,325,5	script	アイグ#23	646,{
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "あのモンスター……";
	mes "何であんなにシャルロシーの事を";
	mes "守ろうとしてたんだろう……。";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

1@jtb.gat,316,322,5	script	ラギ#23	647,{
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "ご無事でしたか。";
	mes "あのモンスターの出す音色……";
	mes "きっと、シャルロシーを守ろうと";
	mes "必死だったんでしょうねぇ。";
	close2;
	cutin "ragi01.bmp", 255;
	end;
}

1@jtb.gat,319,320,5	script	アラン#23	644,{
	cutin "arang02.bmp", 2;
	mes "[アラン]";
	mes "すっごく強そうで格好良い";
	mes "モンスターだったね！";
	mes "あんなのを倒しちゃうなんて";
	mes strcharinfo(0) + "は";
	mes "凄いなぁ！";
	close2;
	cutin "arang01.bmp", 255;
	end;
}

1@jtb.gat,319,328,5	script	ルナイン#23	10039,{
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "け、結構やるじゃない。";
	mes "その、怪我とかしてない？";
	mes "ニュオーズ様の次なら";
	mes "ヒールしてあげるわよ。";
	close2;
	cutin "lunain01.bmp", 255;
	end;
}

1@jtb.gat,325,321,4	script	ロエル#23	10040,{
	cutin "roel04.bmp", 2;
	mes "[ロエル]";
	mes "ご無事でしたか！";
	mes "いざという時にお役に立てず";
	mes "申し訳ありません!!";
	close2;
	cutin "roel01.bmp", 255;
	end;
}

1@jtb.gat,322,321,4	script	メロディージャック#23	844,{
	emotion 9;
	mes "[メロディージャック]";
	mes "おい、このモンスターはまだ";
	mes "息があるようだぞ。";
	mes "生かしておくと面倒だ、";
	mes "さっさと止めを刺しておけ。";
	close;
}

1@jtb.gat,324,327,4	script	ペル#25	10047,{
	mes "[ペル]";
	mes "ペルルル……。";
	close;
}

1@jtb.gat,326,329,4	script	シャルロシー#23	10041,{
	cutin "shaloshi03.bmp", 2;
	mes "[シャルロシー]";
	mes "みんな……。";
	close2;
	cutin "shaloshi03.bmp", 255;
	end;
}

1@jtb.gat,320,323,5	script	ニュオーズ#23	625,{
	if(JTB_2QUE == 7)
		set '@str$,"急ぐ";
	if(select('@str$,"会話をする") == 1) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		set JTB_1QUE,23;
		close2;
		initnpctimer getmdnpcname("ニュオーズ#end");
		mes "‐あなたは記憶を探りながら";
		mes "　先を急ぐことにした‐";
		misceffect 317,getmdnpcname("シャルロシー#23");
		misceffect 317,getmdnpcname("ペル#25");
		close2;
		hideonnpc getmdnpcname("シャルロシー#23");
		hideonnpc getmdnpcname("ペル#25");
		warp getmdmapname("1@jtb.gat"),360,23;
		end;
	}
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ふう、ずいぶんとタフだったね。";
	mes "これで少しは大人しくなるかな？";
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0))
		stopnpctimer;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "やっと見つけた……!!";
	mes "お前ら、大丈夫か!!";
	next;
	switch(JTB_2QUE) {
	case 0:
		if(select("簡単に話を聞きたい","詳しく話を聞きたい")) {
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "とりあえずここから出ましょう。";
			mes "話はそれからよ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ああ、そうだな。";
			mes "しかし出口が見当たらねえ。";
			mes "そいつに原因があるんじゃないか？";
			next;
			cutin "rote01.bmp", 255;
			mes "‐悲しそうに話し出すシャルロシー。";
			mes "　シャルロシーの話から、";
			mes "　彼女は魔王モロクに作られた";
			mes "　使徒であることが発覚した‐";
			next;
			mes "‐ニュオーズは、シャルロシーを";
			mes "　白羽ギルドに迎えようと提案するが、";
			mes "　ギルドメンバーの反応は";
			mes "　非常に冷たいものだった‐";
			next;
			mes "‐自分に向けられた視線の意味を";
			mes "　察したシャルロシーは";
			mes "　何処かに消えてしまった……‐";
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				misceffect 317,getmdnpcname("シャルロシー#23");
				misceffect 317,getmdnpcname("ペル#25");
			}
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				hideonnpc getmdnpcname("シャルロシー#23");
				hideonnpc getmdnpcname("ペル#25");
			}
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……";
			next;
			mes "[ロテルト]";
			mes "チッ……";
			mes "お前ら、さっさと帰るぞ！";
			mes "準備しろ。";
			set JTB_1QUE,23;
			close2;
			initnpctimer getmdnpcname("ニュオーズ#end");
			warp getmdmapname("1@jtb.gat"),360,23;
			end;
		} else {
			cutin "rote01.bmp", 255;
			mes "[メロディージャック]";
			mes "そのモンスター、";
			mes "生かしておくつもりか？";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ここで倒さねーと、";
			mes "また襲ってくるかも知れないぞ。";
			mes "なんなら退魔界一の悪童と呼ばれる";
			mes "俺の力を見せてやろうか。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ダメ！　ペルは私の友達。";
			next;
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "シャルロシー……。";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ここは私の為に";
			mes "ペルが作ってくれた空間……。";
			mes "ペルが暴走したり、消えると";
			mes "この空間も消えてなくなる。";
			mes "ここにいる全員を含めて。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "脅しのつもりか……!!";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "とりあえずここから出ましょう。";
			mes "話はそれからよ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ああ、そうだな。";
			mes "しかし出口が見当たらねえ。";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "恐らくだけど、";
			mes "この空間から脱出できない原因も";
			mes "その子にあるんじゃないかしら？";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "どういうこと？";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "この空間の土の状態を調べたときに、";
			mes "崩壊したモロクの街と同じ魔力を";
			mes "微力ながら感じたわ。";
			next;
			mes "[ミンミン]";
			mes "そして多発する地震。";
			mes "その子が不安そうにしていたり";
			mes "感情が昂ったりした時に";
			mes "起こっていたように見えた。";
			next;
			mes "[ミンミン]";
			mes "この空間、あなたの精神……";
			mes "気持ちにリンクしてるんじゃない？";
			mes "私たちに帰ってほしくない、";
			mes "あなたがそう思ってるから";
			mes "出口が無いんじゃないのかしら。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……。";
			next;
			mes "[シャルロシー]";
			mes "私はただ友達が欲しかっただけ。";
			mes "みんなを閉じ込めるつもりなんて";
			mes "なかった……。";
			next;
			mes "[シャルロシー]";
			mes "でも、出口が消えてしまった。";
			mes "みんなに迷惑かけた……。";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "空間を自由に支配する力なんて……。";
			mes "そしてこの魔力の感じ……";
			mes "あなた、一体何者なの？";
			mes "それだけ記憶が戻っているようなら";
			mes "説明できるわよね？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……私は……";
			next;
			mes "[シャルロシー]";
			mes "私は次元の狭間で生まれた悪魔。";
			mes "魔王モロクに作られた";
			mes "第三の使徒、シャルロシー。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "おい、今何て言った！";
			mes "モロクだと!?";
			next;
			cutin "rote03.bmp", 255;
			mes "[メロディージャック]";
			mes "魔王モロクに作られた存在。";
			mes "さしずめ、魔王の娘と言ったところか。";
			mes "……なるほど。";
			mes "それで懐かしい力を感じたのか。";
			next;
			cutin "lunain02.bmp", 2;
			mes "[ルナイン]";
			mes "……どういうことよ、それ……。";
			next;
			cutin "igu05.bmp", 2;
			mes "[アイグ]";
			mes "魔王モロクの使徒……!?";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "やっぱりこいつ、ここで……！";
			next;
			cutin "ragi02.bmp", 2;
			mes "[ラギ]";
			mes "これは困りましたねぇ。";
			mes "シャルロシーと戦う理由が";
			mes "できてしまいました……。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "でも、安心して。";
			mes "私は今、モロクとの繋がりはない。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "繋がりはないって……";
			mes "どういう事だい？";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "魔王モロクが倒された。";
			mes "だから、モロクとの繋がりが";
			mes "なくなった。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "何寝ぼけたこと言ってやがる！";
			mes "そんな話聞いてないぞ！";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "この空間は外とは時間の流れが違う。";
			mes "みんなにとっては過去かも知れないし";
			mes "未来かもしれない。";
			mes "魔王モロクを倒したのだって……。";
			next;
			cutin "shaloshi01.bmp", 255;
			mes "‐シャルロシーは一瞬";
			mes "　こちらに目を向けると、";
			mes "　すぐに視線を戻した‐";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "……だから、今は自由の身。";
			mes "でも、私が悪魔だって事実は";
			mes "変わらない。";
			next;
			cutin "shaloshi01.bmp", 2;
			mes "[シャルロシー]";
			mes "私は悪魔だから……";
			mes "一緒に居ちゃいけないって……";
			mes "そう思って……だから……。";
			next;
			cutin "gelca02.bmp", 2;
			mes "[ゲルカ]";
			mes "シャルロシーちゃん……";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ねぇ、ロテ、みんな。";
			next;
			mes "[ニュオーズ]";
			mes "……私は悪魔だとか関係なく、";
			mes "今のシャルロシーが好きだし、";
			mes "これからも力になってあげたいんだ。";
			next;
			mes "[ニュオーズ]";
			mes "だから……私はシャルロシーを";
			mes "白羽ギルドに迎え入れたい。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……ニュオーズ、お前……";
			mes "自分が何を言っているか、";
			mes "わかってるのか!?";
			next;
			mes "[ロテルト]";
			mes "こいつは悪魔だ。";
			mes "お前はこいつが、";
			mes "今後も悪さをしないって";
			mes "保証できるのか？";
			next;
			mes "[ロテルト]";
			mes "モロクの力が復活して、";
			mes "こいつが今後も操られないって保証は？";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "……私が全部、責任を持つよ。";
			mes "だからシャルロシーを……";
			next;
			cutin "nines01.bmp", 255;
			mes "[メロディージャック]";
			mes "最悪の事態を想定してみろ。";
			mes "お前の責任だけで";
			mes "済む問題ではないだろう。";
			next;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "ジャック……";
			mes "で、でも、他のみんなもきっと……";
			next;
			cutin "nines01.bmp", 255;
			mes "‐続けて何かを言おうとした";
			mes "　ニュオーズを遮るかのように";
			mes "　シャルロシーが口を開いた‐";
			next;
			cutin "shaloshi02.bmp", 2;
			mes "[シャルロシー]";
			mes "ニュオーズ、ありがとう。";
			mes "……でも。";
			next;
		}
		break;
	case 1:
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ、それにみんなも。";
		mes "私と"+strcharinfo(0)+"は";
		mes "大丈夫だよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ペル、大丈夫？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんね、ペルを傷つけてしまって。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ううん、原因は私にあるから……。";
		next;
		cutin "rote01.bmp", 255;
		mes "‐ニュオーズとシャルロシーが";
		mes "　話をしている。そこに他のメンバーが";
		mes "　駆けつけてきた‐";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……この空間、お前いったい何者だ!?";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……私は……";
		next;
		mes "[シャルロシー]";
		mes "私は次元の狭間で生まれた悪魔。";
		mes "魔王モロクに作られた";
		mes "第三の使徒、シャルロシー。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐シャルロシーの言葉に動揺が走る中、";
		mes "　ラギだけ様子が違う気がした‐";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ねぇ、ロテ、みんな。";
		next;
		mes "[ニュオーズ]";
		mes "……私は悪魔だとか関係なく、";
		mes "今のシャルロシーが好きだし、";
		mes "これからも力になってあげたいんだ。";
		next;
		mes "[ニュオーズ]";
		mes "だから……私はシャルロシーを";
		mes "白羽ギルドに迎え入れたい。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……ニュオーズ、お前……";
		mes "自分が何を言っているか、";
		mes "わかってるのか!?";
		next;
		mes "[ロテルト]";
		mes "こいつは悪魔だ。";
		mes "お前はこいつが、";
		mes "今後も悪さをしないって";
		mes "保証できるのか？";
		next;
		mes "[ロテルト]";
		mes "モロクの力が復活して、";
		mes "こいつが今後も操られないって保証は？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "……私が全部、責任を持つよ。";
		mes "だからシャルロシーを……";
		next;
		cutin "nines01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "最悪の事態を想定してみろ。";
		mes "お前の責任だけで";
		mes "済む問題ではないだろう。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ジャック……";
		mes "で、でも、他のみんなもきっと……";
		next;
		cutin "nines01.bmp", 255;
		mes "‐重苦しい沈黙が流れる。";
		mes "　すると誰かが口を開いた‐";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "僕はいくら小さい子供とはいえ、";
		mes "女性を悲しませるのは好きじゃ";
		mes "ないんですよねぇ。";
		mes "やはり女性に一番似合うのは、";
		mes "笑顔だと思いますし。";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "ということで僕はシャルロシーを";
		mes "仲間に引きずり込むことに、";
		mes "一票ですねぇ。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "ありがとう、ラギ！";
		next;
		cutin "nines03.bmp", 255;
		mes "‐それを聞き、一瞬シャルロシーの";
		mes "　表情が変わった気がしたのも束の間";
		mes "　シャルロシーはこう続けた‐";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……ラギ、嬉しい。";
		mes "……ありがとう。";
		mes "……でも。";
		next;
		break;
	case 2:
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ、それにみんなも。";
		mes "私と"+strcharinfo(0)+"は";
		mes "大丈夫だよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ペル、大丈夫？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんね、ペルを傷つけてしまって。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ううん、原因は私にあるから……。";
		next;
		cutin "rote01.bmp", 255;
		mes "‐ニュオーズとシャルロシーが";
		mes "　話をしている。そこに他のメンバーが";
		mes "　駆けつけてきた‐";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……この空間、お前いったい何者だ!?";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……私は……";
		next;
		mes "[シャルロシー]";
		mes "私は次元の狭間で生まれた悪魔。";
		mes "魔王モロクに作られた";
		mes "第三の使徒、シャルロシー。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐シャルロシーの言葉に動揺が走る中、";
		mes "　なぜかミンミンとアランの様子に";
		mes "　違和感を感じた‐";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ねぇ、ロテ、みんな。";
		next;
		mes "[ニュオーズ]";
		mes "……私は悪魔だとか関係なく、";
		mes "今のシャルロシーが好きだし、";
		mes "これからも力になってあげたいんだ。";
		next;
		mes "[ニュオーズ]";
		mes "だから……私はシャルロシーを";
		mes "白羽ギルドに迎え入れたい。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……ニュオーズ、お前……";
		mes "自分が何を言っているか、";
		mes "わかってるのか!?";
		next;
		mes "[ロテルト]";
		mes "こいつは悪魔だ。";
		mes "お前はこいつが、";
		mes "今後も悪さをしないって";
		mes "保証できるのか？";
		next;
		mes "[ロテルト]";
		mes "モロクの力が復活して、";
		mes "こいつが今後も操られないって保証は？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "……私が全部、責任を持つよ。";
		mes "だからシャルロシーを……";
		next;
		cutin "nines01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "最悪の事態を想定してみろ。";
		mes "お前の責任だけで";
		mes "済む問題ではないだろう。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ジャック……";
		mes "で、でも、他のみんなもきっと……";
		next;
		cutin "nines01.bmp", 255;
		mes "‐重苦しい沈黙が流れる。";
		mes "　すると誰かが口を開いた‐";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "私がシャルロシーのお姉ちゃんに、";
		mes "ミンミンが先生になって、";
		mes "悪い事しないように教えるよ！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "まあ、教育係は必要だろうし、";
		mes "私は別に構わないわよ。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "だから、私達からもお願い!!";
		mes "シャルロシーをこのギルドの";
		mes "ギルドメンバーとして、";
		mes "認めてあげて！　お願い！";
		next;
		cutin "nines03.bmp", 255;
		mes "‐それを聞き、一瞬シャルロシーの";
		mes "　表情が変わった気がしたのも束の間";
		mes "　シャルロシーはこう続けた‐";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "アラン、ミンミンありがとう。";
		mes "……信じて貰えて嬉しい。";
		mes "……でも。";
		next;
		break;
	case 3:
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "やっと見つけた……!!";
		mes "お前ら、大丈夫か!!";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ、それにみんなも。";
		mes "私と"+strcharinfo(0)+"は";
		mes "大丈夫だよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ペル、大丈夫？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんね、ペルを傷つけてしまって。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ううん、原因は私にあるから……。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐ニュオーズとシャルロシーが";
		mes "　話をしている。そこに他のメンバーが";
		mes "　駆けつけてきた‐";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……この空間、お前いったい何者だ!?";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……私は……";
		next;
		mes "[シャルロシー]";
		mes "私は次元の狭間で生まれた悪魔。";
		mes "魔王モロクに作られた";
		mes "第三の使徒、シャルロシー。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐シャルロシーの言葉に動揺が走る中、";
		mes "　ゲルカとロエルが";
		mes "　目配せしたのが見えた‐";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ねぇ、ロテ、みんな。";
		next;
		mes "[ニュオーズ]";
		mes "……私は悪魔だとか関係なく、";
		mes "今のシャルロシーが好きだし、";
		mes "これからも力になってあげたいんだ。";
		next;
		mes "[ニュオーズ]";
		mes "だから……私はシャルロシーを";
		mes "白羽ギルドに迎え入れたい。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……ニュオーズ、お前……";
		mes "自分が何を言っているか、";
		mes "わかってるのか!?";
		next;
		mes "[ロテルト]";
		mes "こいつは悪魔だ。";
		mes "お前はこいつが、";
		mes "今後も悪さをしないって";
		mes "保証できるのか？";
		next;
		mes "[ロテルト]";
		mes "モロクの力が復活して、";
		mes "こいつが今後も操られないって保証は？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "……私が全部、責任を持つよ。";
		mes "だからシャルロシーを……";
		next;
		cutin "nines01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "最悪の事態を想定してみろ。";
		mes "お前の責任だけで";
		mes "済む問題ではないだろう。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ジャック……";
		mes "で、でも、他のみんなもきっと……。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐重苦しい沈黙が流れる。";
		mes "　すると誰かが口を開いた‐";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠。";
		mes "シャルロシーちゃんがもし、";
		mes "間違った道に進んだら……";
		mes "私が責任を持って倒します。";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "だから私からもお願いします。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "僕も全力で";
		mes "シャルロシーさんを止めます！";
		mes "止めて見せます!!";
		next;
		mes "[ロエル]";
		mes "ゲルカさんと同じく、";
		mes "僕からもお願いします!!";
		next;
		cutin "roel01.bmp", 255;
		mes "‐それを聞き、一瞬シャルロシーの";
		mes "　表情が変わった気がしたのも束の間、";
		mes "　シャルロシーはこう続けた‐";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "ゲルカ、ロエル……ありがとう。";
		mes "……二人の気持ち、伝わった。";
		mes "……でも。";
		next;
		break;
	case 4:
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ、それにみんなも。";
		mes "私と"+strcharinfo(0)+"は";
		mes "大丈夫だよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ペル、大丈夫？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんね、ペルを傷つけてしまって。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ううん、原因は私にあるから……。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐ニュオーズとシャルロシーが";
		mes "　話をしている。そこに他のメンバーが";
		mes "　駆けつけてきた‐";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……この空間、お前いったい何者だ!?";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……私は……";
		next;
		mes "[シャルロシー]";
		mes "私は次元の狭間で生まれた悪魔。";
		mes "魔王モロクに作られた";
		mes "第三の使徒、シャルロシー。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐シャルロシーの言葉に動揺が走る中、";
		mes "　アイグとルナインは";
		mes "　妙に落ち着いているように見えた‐";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ねぇ、ロテ、みんな。";
		next;
		mes "[ニュオーズ]";
		mes "……私は悪魔だとか関係なく、";
		mes "今のシャルロシーが好きだし、";
		mes "これからも力になってあげたいんだ。";
		next;
		mes "[ニュオーズ]";
		mes "だから……私はシャルロシーを";
		mes "白羽ギルドに迎え入れたい。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……ニュオーズ、お前……";
		mes "自分が何を言っているか、";
		mes "わかってるのか!?";
		next;
		mes "[ロテルト]";
		mes "こいつは悪魔だ。";
		mes "お前はこいつが、";
		mes "今後も悪さをしないって";
		mes "保証できるのか？";
		next;
		mes "[ロテルト]";
		mes "モロクの力が復活して、";
		mes "こいつが今後も操られないって保証は？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "……私が全部、責任を持つよ。";
		mes "だからシャルロシーを……";
		next;
		cutin "nines01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "最悪の事態を想定してみろ。";
		mes "お前の責任だけで";
		mes "済む問題ではないだろう。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ジャック……";
		mes "で、でも、他のみんなもきっと……";
		next;
		cutin "nines01.bmp", 255;
		mes "‐重苦しい沈黙が流れる。";
		mes "　すると誰かが口を開いた‐";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "責任、責任って……";
		mes "俺も一緒に何とかしてやるってくらいの";
		mes "かっこよさ見せなさいよ……。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "私はみんな好きだけど……";
		mes "その中にやっぱり";
		mes "シャルロシーも居て欲しいの！";
		next;
		cutin "igu05.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "私はアイグに危険が及ばなければ、";
		mes "アイグの意向を尊重したい。";
		mes "それだけだな。";
		next;
		mes "‐それを聞き、一瞬シャルロシーの";
		mes "　表情が変わった気がしたのも束の間、";
		mes "　シャルロシーはこう続けた‐";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "メロディジャック、大丈夫。";
		mes "危険な目にあわせる気はない。";
		mes "ルナイン、アイグ……。";
		mes "私も……2人は大好き。";
		mes "でも……。";
		next;
		break;
	case 5:
	case 6:
	case 7:
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ、それにみんなも。";
		mes "私と"+strcharinfo(0)+"は";
		mes "大丈夫だよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ペル、大丈夫？";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ごめんね、ペルを傷つけてしまって。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ううん、原因は私にあるから……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "わかってるんじゃねーか。";
		mes "なら、話は早いだろ。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ロテ……。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "お前らだって感じてるはずだ。";
		mes "記憶ははっきりはしねーが、";
		mes "こんな話をもう何度も";
		mes "繰り返してるってことを。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "これこそ、悪魔と関わると";
		mes "ろくなことにならないってことの";
		mes "証明だろ!!";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら、そこは悪魔だとか";
		mes "関係ないんじゃない？";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "ギルドメンバーにも関わると、";
		mes "ろくなことにならない人間が居るんだし？";
		mes "ねえ？";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "何故、俺を見る……。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "私もペルも、これ以上";
		mes "迷惑かけるつもりない……。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "これ以上？";
		mes "もうすでに迷惑かけられてるんだよ!!";
		mes "わかってるのかよ!?";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "酷いよ、ロテルト……";
		mes "誰にも迷惑かけないなんて、";
		mes "無理だよ!!";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "人間と悪魔じゃ迷惑の度合いが、";
		mes "全然違うだろ！";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "悪魔と人間は違う……";
		mes "それはよくわかった。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "物分りがいいじゃねーか。";
		mes "そのくらい素直じゃねーとな。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "そういうロテルトこそ、";
		mes "ギルドマスター名乗るなら、";
		mes "メンバーの気持ちに";
		mes "少しは理解を示しなさいよ……！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ハッ！";
		mes "俺がニュオーズみたいな甘ちゃんで、";
		mes "こんなホイホイ悪魔だのモンスターだの";
		mes "簡単に仲間にしていたら、";
		mes "そのうちギルドは崩壊するぜ？";
		mes "それでもいいのかよ？";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……私のせいで";
		mes "そんなことになるのは嫌。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "ロテルト、これじゃあまるで";
		mes "シャルロシーをいじめてる";
		mes "みたいなの……。";
		mes "シャルロシーが傷つくの。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "何を言ってるんだ、アイグ。";
		mes "俺は事実を言っているだけだ。";
		mes "そもそも悪魔に感情なんてないんだ、";
		mes "傷つくもなにもないだろ。";
		next;
		cutin "rote01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "悪魔だから、人間だからと";
		mes "種族だけで物事を決めつけるのは、";
		mes "些か早計ではないか？";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……どういうことだ？";
		next;
		cutin "rote01.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#23");
		mes "[メロディージャック]";
		mes "感情を理解し、意思の疎通を図れるなら";
		mes "再考の余地はある、という事だ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "みんなの感情……。";
		mes "なんとなく……わかる。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "こいつが俺たちの感情がわかろうが";
		mes "俺たちがこいつの感情をわからなければ";
		mes "意味無えじゃねえか……！";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠。シャルロシーちゃんって";
		mes "表情の変化が乏しいだけで";
		mes "感情はあると思うことが";
		mes "割りとありましたよ!!";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "多分ですけど……";
		mes "感情を表現することが苦手なだけで、";
		mes "僕達と同じように感情は";
		mes "あるのではないでしょうか？";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "百歩譲ってこのガキに感情があるとして、";
		mes "だから安全だ、仲間になりましょうって";
		mes "簡単に言えると思ってるのか？";
		mes "何度も言うが、こいつは悪魔なんだぞ!?";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "少なくとも僕は、";
		mes "感情があることがわかった以上、";
		mes "悪魔だからとあっさり";
		mes "切り捨てることはできないですねぇ。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "感情があり、僕達人間を";
		mes "攻撃する意思がない。";
		mes "そして、仲良くなりたいと願っている。";
		next;
		mes "[ラギ]";
		mes "メンバーとして迎えるには、";
		mes "十分な条件じゃないですかねぇ。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……。";
		next;
		menu "どうすべきか、もう分かっているのでは",-;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……!?";
		next;
		mes "[ロテルト]";
		mes "なんだ？";
		mes strcharinfo(0)+"。";
		mes "お前は人の心を見抜く修行でも";
		mes "してるのか？";
		next;
		mes "[ロテルト]";
		mes "それとも、そいつのような";
		mes "人の心を読む力でも持っているのか？";
		next;
		mes "[ロテルト]";
		mes "そういえば前もお前と";
		mes "こんな話した気がするぜ……。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "まったくお前らは……";
		mes "揃いも揃って……";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……あーやめやめ!!";
		mes "馬鹿馬鹿しくなってきた。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "これじゃあ俺がまるで";
		mes "悪者みてーじゃねぇか!!";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら、自覚あったのね。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "とはいえこれは単純に";
		mes "メンバーが増えるって";
		mes "簡単な話じゃねーんだ!!";
		mes "前代未聞なんだ!!";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "なのに、お前達みたいに……";
		mes "ホイホイ許可なんて";
		mes "出せるわけねーだろ……。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "シャルロシー。";
		mes "今回のことで分かっただろ？";
		mes "人間っていうのはこの上なく面倒で、";
		mes "こいつらみたいに、";
		mes "気のいい連中ばかりじゃねぇ。";
		mes "傷つける奴もわんさか居る。";
		next;
		mes "[ロテルト]";
		mes "その度に、泣いたり笑ったり……";
		mes "いろんなものを感じて……";
		mes "時にこの感情を邪魔に感じながら";
		mes "それでも生きようともがくのが、";
		mes "俺たち人間だ。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "だからこそ……";
		mes "いいことばかりじゃない。";
		mes "きっと嫌なことも多いはずだ。";
		mes "それでも来るのか？";
		mes "それでも……俺たちと一緒にいたいのか？";
		mes "答えろ！　シャルロシー!!";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……ロテ。";
		next;
		mes "[シャルロシー]";
		mes "答えたいのに……。";
		mes "私の心……変……。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "シャルロシー、それが嬉しいって";
		mes "感情なんだよ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "これが、嬉しい……。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "ロテ、私……。";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "みんなと友達になりたい……！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……決まりだな。";
		next;
		mes "[ロテルト]";
		mes "シャルロシー。";
		mes "お前をギルドメンバーとして、";
		mes "ここに認める！";
		next;
		mes "[ロテルト]";
		mes "ただし！　だ。";
		mes "ギルドメンバーになったからには";
		mes "悪さなんかしたら承知しないからな！";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "約束する。悪さなんかしない。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "そ、それとだな、";
		mes "この先お前の事を、その……";
		mes "邪険に扱う奴がいたら俺に言え。";
		mes "俺はギルドマスターだからな。";
		mes "メンバーを守るのも俺の仕事だ。";
		mes "そんな奴は俺が灸を据えてやる！";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "ロテ……。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "よかったね、シャルロシー。";
		mes "ようこそ、私たちの白羽ギルドへ！";
		next;
		cutin "nines01.bmp", 255;
		mes "‐ギルドメンバーは各々";
		mes "　シャルロシーに対し";
		mes "　祝福の言葉と拍手を送る‐";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "みんな、ありがとう……！";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "あ、あれ……。";
		next;
		cutin "shaloshi01.bmp", 255;
		mes "‐ギルドメンバーが祝福する中";
		mes "　シャルロシーの頬を";
		mes "　一筋の雫が伝った‐";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "涙……？";
		mes "嬉しいはずなのに……。";
		mes "悲しいの……？";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "あはは、大丈夫だよシャルロシー。";
		mes "涙は嬉しい時にも出るんだ。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "そうなんだ……。";
		mes "初めて……泣けた。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "やはり、本当の涙の美しさには";
		mes "人魚の涙といわれる宝石も";
		mes "かなわないようですねぇ。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……さて。";
		mes "湿っぽいのは終いにして";
		mes "そろそろ脱出するぞ！";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……私は一緒に行けない。";
		next;
		mes "[シャルロシー]";
		mes "ペルが私と誰にも邪魔されずに";
		mes "一緒に居たいって言ってる。";
		mes "ペルも大事な友達だから、";
		mes "しばらく一緒に居てあげたい。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "そっか、少しの間お別れなんだね。";
		mes "でも……また会えるよね？";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "うん。私もみんなに会いたい。";
		mes "だから、みんな……。";
		next;
		cutin "shaloshi04.bmp", 2;
		mes "[シャルロシー]";
		mes "……またね。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "ああ、また会おう。";
		mes "またね、シャルロシー。";
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			misceffect 317,getmdnpcname("シャルロシー#23");
			misceffect 317,getmdnpcname("ペル#25");
		}
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
			hideonnpc getmdnpcname("シャルロシー#23");
			hideonnpc getmdnpcname("ペル#25");
		}
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "よ、用事が済んだら帰るからな";
		mes "さっさと準備しろよ！";
		close2;
		set JTB_2QUE,6;
		cutin "rote01.bmp", 255;
		end;
	}
	mes "[シャルロシー]";
	mes "私は、私が神様に";
	mes "お願いを叶えてもらったように";
	mes "今度はペルの夢をかなえてあげたいの。";
	mes "これは私にしか出来ない……。";
	next;
	mes "[シャルロシー]";
	mes "ペルの夢……。";
	mes "それは私と誰にも邪魔されずに";
	mes "一緒に居たいって言ってる。";
	mes "だから……ごめん。私……行くね。";
	next;
	mes "[シャルロシー]";
	mes strcharinfo(0) + "も、";
	mes "みんなも……。";
	mes "仲良くしてくれてありがとう……。";
	next;
	cutin "shaloshi01.bmp", 255;
	mes "‐こちらを見たシャルロシーの顔が";
	mes "　とても寂しげに見えた‐";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "シャルロシー……";
	mes "こんな悲しい結末だなんて、";
	mes "私は嫌だよ……。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "ごめんなさい……";
	mes "……ばいばい。";
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		misceffect 317,getmdnpcname("シャルロシー#23");
		misceffect 317,getmdnpcname("ペル#25");
	}
	next;
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		hideonnpc getmdnpcname("シャルロシー#23");
		hideonnpc getmdnpcname("ペル#25");
	}
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "……";
	next;
	mes "[ロテルト]";
	mes "チッ……";
	mes "お前ら、さっさと帰るぞ！";
	mes "準備しろ。";
	set JTB_1QUE,23;
	close2;
	initnpctimer getmdnpcname("ニュオーズ#end");
	warp getmdmapname("1@jtb.gat"),360,23;
	end;
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// END部屋：険しい道
//------------------------------------------
1@jtb.gat,370,26,5	script	アラン#end	644,{
	if(JTB_2QUE >= 6) {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "同じ事を繰り返すとか";
		mes "難しい事はわかんないけど";
		mes "シャルロシーと友達になれて";
		mes "本当に良かった！";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "ありがとうね！";
		mes strcharinfo(0)+"！";
		close2;
		cutin "arang03.bmp", 255;
		end;
	}
	if(JTB_2QUE == 1) {
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes strcharinfo(0)+"……。";
		next;
		menu "どうしたの？",-;
		mes "[アラン]";
		mes "あの、その……。";
		next;
		mes "[アラン]";
		mes "ちょっと話したい事が";
		mes "あるんだけど……。";
		next;
		if(select("いいよ","忙しい") == 2) {
			cutin "arang03.bmp", 2;
			mes "[アラン]";
			mes "あ……";
			mes "そっか……";
			mes "忙しいのにごめんね。";
			close2;
			cutin "arang03.bmp", 255;
			end;
		}
		cutin "arang02.bmp", 2;
		mes "[アラン]";
		mes "本当!?";
		mes "じゃあ、その……";
		mes "ここだと話しづらいから";
		mes "こっちに来てほしいな。";
		close2;
		warp getmdmapname("1@jtb.gat"),99,298;
		end;
	}
	cutin "arang03.bmp", 2;
	mes "[アラン]";
	mes "ロエルと友達になったよ！";
	close2;
	cutin "arang03.bmp", 255;
	end;
}

1@jtb.gat,376,23,3	script	ロエル#end	10040,{
	if(JTB_2QUE >= 6) {
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "シャルロシーとは";
		mes "しばらく別れることに";
		mes "なってしまいましたが";
		mes "また会えると信じています！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "シャルロシーも";
		mes "ギルドメンバーなんですから！";
		close2;
		cutin "roel01.bmp", 255;
		end;
	}
	if(JTB_2QUE == 2) {
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "あ、ちょうどいい所に！";
		next;
		mes "[ロエル]";
		mes "今からゲルカさんと";
		mes "二人の必殺技を作るんです！";
		mes "アドバイスも頂きたいですし、";
		mes "よかったら見に来てくれませんか？";
		next;
		if(select("いいよ","忙しい") == 2) {
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "そうですか……";
			mes "残念ですけど、またの機会に";
			mes "お願いします！";
			close2;
			cutin "roel01.bmp", 255;
			end;
		}
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "本当ですか!?";
		mes "ありがとうございます！";
		mes "それじゃあ、さっそく行きましょう！";
		close2;
		warp getmdmapname("1@jtb.gat"),200,271;
		end;
	}
	cutin "roel03.bmp", 2;
	mes "[ロエル]";
	mes "アランと友達になりました！";
	mes "今度、一緒にダンジョンへ";
	mes "冒険しに行くんですよ！";
	close2;
	cutin "roel01.bmp", 255;
	end;
}

1@jtb.gat,375,18,4	script	アイグ#end	646,{
	if(JTB_2QUE >= 6) {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシーも何度も";
		mes "同じ経験をしたの……？";
		next;
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "辛かったと思うし、";
		mes "色々とごめんなさいって";
		mes "思うけど……";
		mes "最後は笑顔になれて良かったの！";
		close2;
		cutin "igu01.bmp", 255;
		end;
	}
	if(JTB_2QUE == 3) {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシーがいなくなって";
		mes "ルナインがさみしそうなの。";
		next;
		mes "[アイグ]";
		mes "ルナインは強がってるけど";
		mes "元気づけてあげたいの！";
		mes "ちょっとあっちではなしてくるの。";
		next;
		if(select("アイグについて行く","頑張ってね") == 2) {
			cutin "igu02.bmp", 2;
			mes "[アイグ]";
			mes "ありがとうなの。";
			mes "ルナインが元気になってくれるように";
			mes "頑張ってくるの！";
			close2;
			cutin "igu01.bmp", 255;
			end;
		}
		mes "‐あなたはアイグに";
		mes "　こっそりついて行くことにした‐";
		close2;
		warp getmdmapname("1@jtb.gat"),13,384;
		end;
	}
	cutin "igu03.bmp", 2;
	mes "[アイグ]";
	mes "お疲れ様なの！";
	mes "みんな無事でよかったの。";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

1@jtb.gat,368,21,5	script	ロテルト#end	630,{
	if(JTB_2QUE >= 6) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "お前にはずいぶん世話になったな。";
		mes "記憶は曖昧なんだが、";
		mes "お前が居なければ、こんな結末は";
		mes "迎えられなかったろうよ。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "その……";
		mes "ありがとうな。";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
	if(JTB_2QUE == 4) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes strcharinfo(0)+"か。";
		mes "どうかしたのか？";
		next;
		if(select("話がある","なんでもない") == 2) {
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "あんまり俺の邪魔するなよ。";
			mes "冒険は終わったんだ。";
			mes "早く帰りな。";
			close2;
			cutin "rote01.bmp", 255;
			end;
		}
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "俺に話……？";
		mes "まあいい、手短に済ませろよ。";
		close2;
		warp getmdmapname("1@jtb.gat"),108,377;
		end;
	}
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "今は臨時のギルドメンバー";
	mes "かも知れねえが、";
	mes "頑張ったら良い事あるかもな。";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

1@jtb.gat,366,20,5	script	ゲルカ#end	629,{
	if(JTB_2QUE >= 6) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "同じ経験を何度も……";
		mes "まるで小説みたいですね！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "もっと強くなります。";
	mes "修行も頑張らないと！";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

1@jtb.gat,364,18,5	script	ミンミン#end	643,{
	if(JTB_2QUE >= 6) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "ルナインやロエルは";
		mes "過去にワープするという";
		mes "ところまでは覚えてるみたい。";
		mes "でも、過去の私たちは";
		mes "どこにもいないのよね。";
		next;
		mes "[ミンミン]";
		mes "意識だけ過去に来たって";
		mes "ことなのかしら？";
		mes "まったく、頭が爆発しそうだわ。";
		close2;
		cutin "min01.bmp", 255;
		end;
	}
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "もしかしてと思って";
	mes "シャルロシーの髪の毛を";
	mes "何本か採取しておいたわ。";
	mes "まずは研究はしてみないと。";
	next;
	emotion 29;
	mes "[ミンミン]";
	mes "ここにはまだ";
	mes "研究しなきゃいけないものが";
	mes "たくさんあるわね。";
	close2;
	cutin "min01.bmp", 255;
	end;
}

1@jtb.gat,373,25,3	script	ラギ#end	647,{
	if(JTB_2QUE >= 6) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "シャルロシーにあげた真珠は";
		mes "ようやく役目を終えたようですね。";
		mes "涙だけではなく、笑う事もできて、";
		mes "本当に良かったですねぇ。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	}
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "心を読めるというのも";
	mes "時と場合によりけり、ですねぇ。";
	mes "僕にはそんな力がなくて、";
	mes "良かったと思いますよ。";
	close2;
	cutin "ragi01.bmp", 255;
	end;
}

1@jtb.gat,373,16,3	script	ルナイン#end	10039,{
	if(JTB_2QUE >= 6) {
		cutin "lunain03.bmp", 2;
		mes "[ルナイン]";
		mes "もしかしたらシャルロシーは";
		mes "私たちと友達になりたくて";
		mes "同じことを繰り返して";
		mes "いたのかも知れないわね。";
		close2;
		cutin "lunain03.bmp", 255;
		end;
	}
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "あの子もしかして……";
	mes "な、なんでもないわ。";
	mes "流石に疲れたし、";
	mes "早く帰って休みたいわ……。";
	close2;
	cutin "lunain03.bmp", 255;
	end;
}

1@jtb.gat,367,13,5	script	メロディージャック#end_	844,{
	if(JTB_2QUE >= 6) {
		mes "[メロディージャック]";
		mes "時間遡行……";
		mes "同一人物が存在しない事から考えるに";
		mes "過去の意識への介入か……？";
		close;
	}
	mes "[メロディージャック]";
	mes "隠れているのだから声をかけるな！";
	mes "まったく……。";
	mes "隠れている者を見つけるのには";
	mes "それなりの修業が必要だというのに。";
	mes "……お前は大した奴だな。";
	close;
}

1@jtb.gat,372,22,4	script	ニュオーズ#end	625,{
	if(JTB_1QUE <= 23) {
		if(JTB_2QUE == 7)
			set '@str$,"急ぐ";
		if(select('@str$,"会話をする") == 1) {
			if(getpartyleader(getcharid(1)) == strcharinfo(0))
				stopnpctimer;
			set JTB_1QUE,24;
			if('flag != 1) {
				set 'flag,1;
				hideoffnpc getmdnpcname("23番部屋出口#JTB");
				mes "‐東の出口から外に出よう‐";
			}
			close;
		}
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "みんな、ひとまずお疲れ様。";
		mes "いろいろあった後だし、少し";
		mes "ここで休憩して帰ろう。";
		next;
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			stopnpctimer;
		if(JTB_2QUE >= 6) {
			cutin "arang03.bmp", 2;
			mes "[アラン]";
			mes "本当、本当良かったよ～!!";
			next;
			cutin "gelca03.bmp", 2;
			mes "[ゲルカ]";
			mes "良かったですね、";
			mes "アランさん!!";
			next;
			cutin "arang02.bmp", 2;
			mes "[アラン]";
			mes "ぐすっ……";
			mes "うん、本当はすごく";
			mes "不安だったから……。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "まったく……ロテルトが";
			mes "ギルドマスターになってから、";
			mes "ろくなことにならないわね。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "ギルド名の件もありますしねぇ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "お前ら……";
			mes "そんな事ばっかり覚えてやがって……。";
			next;
			mes "[ロテルト]";
			mes "大体！";
			mes "あの名前のどこが悪いんだよ!!";
			mes "最高に格好良いじゃねーか！";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "そうね……";
			mes "例えばシャルロシーが、";
			mes "ギルドの名前を名乗らないと";
			mes "いけなくなったら最悪ね。";
			next;
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "私は魔王の力で作られた悪魔。";
			mes "そして、ロテルトの超必殺ギルド所属";
			mes "シャルロシー。";
			next;
			mes "[アイグ]";
			mes "こういう感じ、なの？";
			next;
			cutin "nines02.bmp", 2;
			mes "[ニュオーズ]";
			mes "アイグ、似てるね♪";
			next;
			cutin "arang01.bmp", 2;
			mes "[アラン]";
			mes "すごく小物臭がするよ……。";
			next;
			cutin "roel01.bmp", 2;
			mes "[ロエル]";
			mes "全然怖くないですね……!!";
			next;
			cutin "lunain01.bmp", 2;
			mes "[ルナイン]";
			mes "ありえないわ……。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "おい……!!";
			next;
			cutin "gelca04.bmp", 2;
			mes "[ゲルカ]";
			mes "みなさん!!";
			mes "ダメじゃないですか!!";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "いってやれ!!　ゲルカ!!";
			next;
			cutin "gelca03.bmp", 2;
			mes "[ゲルカ]";
			mes "大事なポイント、";
			mes "二つ名を忘れちゃダメですよ!!";
			next;
			mes "[ゲルカ]";
			mes "例えば……そうですね……";
			mes "次元の番人";
			mes "（ディメンシオングアルディア）";
			mes "シャルロシーとかっ!!";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "すまん、ゲルカ……";
			mes "お前に期待した俺がバカだった……。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "そもそも……";
			mes "ロテルトの超必殺って何よ？";
			mes "って話よね。";
			mes "名は体を表すって言葉、";
			mes "知らないんじゃないかしら。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "ロテルト様の名前が、";
			mes "別の意味で有名になりそうですねぇ。";
			next;
			cutin "ragi01.bmp", 255;
			mes "[メロディージャック]";
			mes "良かったなロテルト。";
			mes "有名になれるぞ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ちっともよくねぇ!!";
			next;
			cutin "nines02.bmp", 2;
			mes "[ニュオーズ]";
			mes "あ、そうだ、ロテ～！";
			mes "今度またシャルロシーも入れて";
			mes "みんなの職位を決めようよ♪";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……しゃーねぇな。";
			mes "俺が格好良い職位を";
			mes "全員分、考えてやるよ。";
			next;
			menu "それは……",-;
			cutin "rote01.bmp", 255;
			mes "[全員]";
			mes "却下！";
			next;
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "なの♪";
			close2;
			cutin "rote01.bmp", 255;
			set JTB_2QUE,7;
			set JTB_1QUE,24;
			if('flag != 1) {
				set 'flag,1;
				hideoffnpc getmdnpcname("23番部屋出口#JTB");
			}
			end;
		}
		cutin "rote01.bmp", 2;
		emotion 36,getmdnpcname("ロテルト#end");
		mes "[ロテルト]";
		mes "そういや……";
		mes "ニュオーズ!!";
		mes "お前さっきはよくも";
		mes "勝手に「白羽ギルド」とか";
		mes "言いやがったな！";
		next;
		cutin "nines04.bmp", 2;
		mes "[ニュオーズ]";
		mes "えっ？";
		mes "ギルドマスターは変わったけど……";
		mes "もうギルド名まで変更したのかい？";
		next;
		cutin "rote01.bmp", 2;
		emotion 32,getmdnpcname("ロテルト#end");
		mes "[ロテルト]";
		mes "ギルドマスターが変わったんだ！";
		mes "ギルド名も変えるのが、普通だろ！";
		mes "その……う～ん。";
		mes "アレだ！　あの名前……。";
		next;
		emotion 54,getmdnpcname("ミンミン#end");
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "新しい名前が思いつかないなら、";
		mes "そのままにすれば？";
		next;
		emotion 52,getmdnpcname("ロテルト#end");
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "そんなことはできるか！";
		mes "俺がギルドマスターだしな。";
		next;
		mes "[ロテルト]";
		mes "おっ、そうだ!!";
		mes "これからは";
		mes "「ロテルトの超必殺ギルド」だ！";
		emotion 40,getmdnpcname("ロテルト#end");
		next;
		emotion 57,getmdnpcname("アイグ#end");
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "変な名前、なの。";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "師匠らしいギルド名ですよね!!";
		next;
		cutin "roel04.bmp", 2;
		mes "[ロエル]";
		mes "こ、個性的ですね……。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "うわっダサッ！";
		next;
		cutin "rote01.bmp", 2;
		emotion 36,getmdnpcname("ロテルト#end");
		mes "[ロテルト]";
		mes "うるせー!!";
		mes "ギルドマスターは俺だ！";
		mes "決定権は俺にある！";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "……格好悪い。";
		next;
		emotion 29,getmdnpcname("ミンミン#end");
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "その名前で決定っていうなら";
		mes "私はギルドを脱退するわ。";
		mes "そんな名前、名乗りたくないもの。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "なんだと！";
		emotion 23,getmdnpcname("ロテルト#end");
		next;
		cutin "min02.bmp", 255;
		mes "[メロディージャック]";
		mes "私は元々ギルドメンバーではないしな。";
		mes "好きにさせて貰うぞ。";
		emotion 9,getmdnpcname("メロディージャック#end_");
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "こんな恥ずかしいギルド名じゃ";
		mes "どこに行っても目立ちますねぇ。";
		mes "そのせいでアイグ様の人気にも";
		mes "変な影響が出ないと良いですが。";
		next;
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "あはは、大丈夫なの。";
		mes "多分……。";
		emotion 14,getmdnpcname("アイグ#end");
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "白羽ギルドの方が";
		mes "分かりやすいし、何より";
		mes "ニュオーズ様のセンスが";
		mes "光る名前で良かったのに。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "でもまあ……";
		mes "こんな名前になるなら";
		mes "あの子が入らなくて";
		mes "ある意味、正解だったかもね……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "お前ら……";
		mes "好き勝手言いやがって！";
		mes "とにかく今日は疲れたから解散するぞ！";
		mes "ロテルトの超必殺ギルドの冒険終了！";
		close2;
		cutin "rote01.bmp", 255;
		set JTB_1QUE,24;
		if('flag != 1) {
			set 'flag,1;
			hideoffnpc getmdnpcname("23番部屋出口#JTB");
		}
		end;
	}
	if(JTB_2QUE == 0) {
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "やあ、君か。ちょうどよかった！";
		mes "実はちょっと話したいことが";
		mes "あるんだけど……。";
		mes "よかったら聞いてくれないかな？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[ニュオーズ]";
			mes "残念だなぁ……。";
			mes "気が変わったらでいいから";
			mes "いつか聞いてくれると嬉しいな。";
			close2;
			cutin "nines01.bmp", 255;
			end;
		}
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "本当かい!?";
		mes "それじゃあ、場所を移動しようか。";
		mes "こっちだよ。";
		close2;
		warp getmdmapname("1@jtb.gat"),13,274;
		end;
	}
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "久しぶりに仲間たちと一緒だと";
	mes "楽しいな。";
	close2;
	cutin "nines01.bmp", 255;
	end;
OnTimer3000:
	emotion 9;
	initnpctimer;
	end;
}

//==========================================
// 15番部屋NPC：険しい道＋ボス撃破後イベント
//------------------------------------------
1@jtb.gat,36,289,3	script	ラギ#15	647,{
	if(JTB_2QUE != 1) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes strcharinfo(0) + "さん、";
		mes "お疲れ様です。";
		mes "僕もニュオーズ様に呼ばれて";
		mes "きたのですが、";
		mes "何があるのでしょうか。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	} else {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "素晴らしい曲ができましたね。";
		mes "アイグ様のダンスも";
		mes "とても楽しみですねぇ。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	}
}

1@jtb.gat,34,291,3	script	ニュオーズ#15	625,{
	if(JTB_2QUE != 1) {
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "やあやあ、ラギ君、";
		mes strcharinfo(0) + "。";
		mes "こんなところに呼び出してごめんね～。";
		mes "実は二人にお願いがあるんだ。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "なんでしょう。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "今回の冒険を曲にしたくってさ。";
		mes "冒険者は冒険記を書いたりするだろう？";
		mes "私はそれを音楽で残すのが好きなんだ。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "それは素晴らしいですねぇ。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "それでね、二人に";
		mes "曲作りのお手伝いをして欲しいんだ～。";
		mes "どうかな？";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "僕は構わないですよ。";
		mes "ニュオーズ様とゆっくり音楽について";
		mes "お話もしたかったところですし。";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "ラギ君！　ありがとう～！";
		mes strcharinfo(0) + "は";
		mes "どう？　お願いできる？";
		next;
		menu "手伝う",-;
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "やった～！　ありがとう！";
		mes "さっそくだけど、";
		mes "どんな曲にしたらいいと思う？";
		next;
		switch(select("明るい曲","暗い曲","激しい曲")) {
		case 1:
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "明るい曲か！　いいね！";
			mes "冒険は楽しいものだからね！";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "allegramente……いいですねぇ。";
			mes "白羽ギルドにぴったりですね。";
			next;
			menu "アレグラメンテ？",-;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "はい。allegramenteとは";
			mes "音楽用語で";
			mes "明るく、楽しくという意味です。";
			next;
			menu "なるほど",-;
			cutin "nines03.bmp", 2;
			mes "[ニュオーズ]";
			mes "よし、ギルドによく似合う";
			mes "明るい曲にしよう！";
			mes "賑やかなメンバーに負けない、";
			mes "元気な曲にしないとね！";
			break;
		case 2:
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "暗い曲かぁ。";
			mes "たまにはそういうのもいいかも。";
			mes "冒険は色々な事があるものだしね。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "lamentabile……。";
			mes "最後に盛り上がりが欲しいですねぇ。";
			next;
			menu "ラメンタービレ？",-;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "はい。lamentabileとは";
			mes "音楽用語で";
			mes "悲しげにという意味です。";
			next;
			menu "なるほど",-;
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "そうだね。最後に盛り上がって……";
			mes "シャルロシーとは一旦別れたけど、";
			mes "また出会える日を";
			mes "心待ちにできるような、";
			mes "そんな曲がいいな。";
			break;
		case 3:
			cutin "nines01.bmp", 2;
			mes "[ニュオーズ]";
			mes "激しい曲か！　なるほど！";
			mes "今回の冒険も激しい戦闘が";
			mes "たくさんあったからね～。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "herzhaft……ですねぇ。";
			mes "戦闘をイメージした曲ができそうです。";
			next;
			menu "ヘルツハフト？",-;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "はい。herzhaftとは";
			mes "音楽用語で";
			mes "勇敢な、力強いという意味です。";
			next;
			menu "なるほど",-;
			cutin "nines02.bmp", 2;
			mes "[ニュオーズ]";
			mes "激しい戦闘の曲！";
			mes "う～ん、いいね！";
			mes "勇敢な僕が颯爽と戦ってる曲！";
			mes "良い曲ができそうだよ～！";
			break;
		}
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes "うん、うん！　イメージが湧いてきた！";
		mes "メロディも浮かんできた～！";
		mes "これから私は曲を作るから、";
		mes "ラギ君、演奏を手伝って！";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "わかりました。";
		next;
		cutin "nines01.bmp", 2;
		mes "[ニュオーズ]";
		mes strcharinfo(0) + "には";
		mes "歌詞を考えて欲しいな。";
		mes "この紙に書いてくれたら、";
		mes "曲と合わせるよ。";
		next;
		cutin "nines01.bmp", 255;
		mes "‐紙とペンを受け取った‐";
		next;
		cutin "nines03.bmp", 2;
		mes "[ニュオーズ]";
		mes "頼んだよ～！";
		mes "さあ、ラギ君。";
		mes "私達もかんばろう！";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "はい。";
		next;
		cutin "ragi01.bmp", 255;
		mes "‐さっそく受け取った紙に";
		mes "　思いつく歌詞を書いてみよう。";
		mes "　最初は何を書こうか‐";
		setarray '@str$[1],"シャルロシーの事","ニュオーズの事","自分の事";
		while(1) {
			next;
			switch('@succsess) {
			case 0:
				switch(select('@str$[1],'@str$[2],'@str$[3])) {
				case 1:
					mes "[" + strcharinfo(0) + "]";
					mes "ダンジョンで出会った謎の少女……";
					mes "魔王の娘、シャルロシー……";
					mes "彼女は友達がほしかった……";
					set '@song[1],1;
					set '@str$[1],"";
					break;
				case 2:
					mes "[" + strcharinfo(0) + "]";
					mes "お騒がせな前マスター……";
					mes "ミンストレルのニュオーズ……";
					mes "彼と仲間の冒険記……";
					set '@song[1],2;
					set '@str$[2],"";
					break;
				case 3:
					mes "[" + strcharinfo(0) + "]";
					mes "臨時で入った白羽ギルド……";
					mes "冒険者" + strcharinfo(0) + "……";
					mes "新しい冒険の始まり……";
					set '@song[1],3;
					set '@str$[3],"";
					break;
				}
				next;
				mes "‐紙にするすると";
				mes "　思いついた言葉を書いていく。";
				mes "　次は何を書こうか‐";
				set '@succsess,'@succsess + 1;
				continue;
			case 1:
				switch(select('@str$[1],'@str$[2],'@str$[3])) {
				case 1:
					mes "[" + strcharinfo(0) + "]";
					mes "ダンジョンで出会った謎の少女……";
					mes "魔王の娘、シャルロシー……";
					mes "彼女は友達がほしかった……";
					set '@song[2],1;
					set '@str$[1],"";
					break;
				case 2:
					mes "[" + strcharinfo(0) + "]";
					mes "お騒がせな前マスター……";
					mes "ミンストレルのニュオーズ……";
					mes "彼と仲間の冒険記……";
					set '@song[2],2;
					set '@str$[2],"";
					break;
				case 3:
					mes "[" + strcharinfo(0) + "]";
					mes "臨時で入った白羽ギルド……";
					mes "冒険者" + strcharinfo(0) + "……";
					mes "新しい冒険の始まり……";
					set '@song[2],3;
					set '@str$[3],"";
					break;
				}
				next;
				mes "‐紙にするすると";
				mes "　思いついた言葉を書いていく。";
				mes "　最後の文章も書こう‐";
				set '@succsess,'@succsess + 1;
				continue;
			case 2:
				switch(select('@str$[1],'@str$[2],'@str$[3])) {
				case 1:
					mes "[" + strcharinfo(0) + "]";
					mes "ダンジョンで出会った謎の少女……";
					mes "魔王の娘、シャルロシー……";
					mes "彼女は友達がほしかった……";
					set '@song[3],1;
					set '@str$[1],"";
					break;
				case 2:
					mes "[" + strcharinfo(0) + "]";
					mes "お騒がせな前マスター……";
					mes "ミンストレルのニュオーズ……";
					mes "彼と仲間の冒険記……";
					set '@song[3],2;
					set '@str$[2],"";
					break;
				case 3:
					mes "[" + strcharinfo(0) + "]";
					mes "臨時で入った白羽ギルド……";
					mes "冒険者" + strcharinfo(0) + "……";
					mes "新しい冒険の始まり……";
					set '@song[3],3;
					set '@str$[3],"";
					break;
				}
				next;
				mes "‐紙にするすると";
				mes "　思いついた言葉を書いていく。";
				mes "　歌詞が出来上がった‐";
				set '@succsess,'@succsess + 1;
				continue;
			case 3:
				next;
				cutin "nines01.bmp", 2;
				mes "[ニュオーズ]";
				mes strcharinfo(0) + "～！";
				mes "曲ができたよ～！";
				mes strcharinfo(0) + "は";
				mes "できたかい？";
				next;
				menu "できた",-;
				cutin "nines03.bmp", 2;
				mes "[ニュオーズ]";
				mes "おおっ！　見せて見せて！";
				mes "どれどれ……";
				next;
				mes "[ニュオーズ]";
				mes "……";
				next;
				mes "[ニュオーズ]";
				mes "……";
				mes "…………";
				next;
				cutin "nines02.bmp", 2;
				mes "[ニュオーズ]";
				mes "……";
				mes "…………";
				mes "いいね～！　すばらしい!!";
				next;
				cutin "nines03.bmp", 2;
				mes "[ニュオーズ]";
				mes "さぁ、ラギ君！";
				mes "私達が作ったメロディーに乗せて";
				mes "歌ってみようじゃないか！";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "はい。それでは演奏を始めます。";
				next;
				cutin "ragi02.bmp", 2;
				mes "[ラギ]";
				mes "ラ～ララ～ラ～";
				mes "白羽ギルドの物語～";
				mes "小さな冒険の物語～";
				for(set '@i,1; '@i<=3; set '@i,'@i+1) {
					next;
					switch('@song['@i]) {
					case 1:
						cutin "nines02.bmp", 2;
						mes "[ニュオーズ]";
						mes "ダンジョンで出会った謎の少女～";
						mes "魔王の娘、シャルロシー～";
						mes "彼女は友達がほしかった～";
						break;
					case 2:
						cutin "nines02.bmp", 2;
						mes "[ニュオーズ]";
						mes "お騒がせな前マスター～";
						mes "ミンストレルのニュオーズ～";
						mes "彼と仲間の冒険記～";
						break;
					case 3:
						cutin "nines02.bmp", 2;
						mes "[ニュオーズ]";
						mes "臨時で入った白羽ギルド～";
						mes "冒険者" + strcharinfo(0) + "～";
						mes "新しい冒険の始まり～";
						break;
					}
				}
				next;
				cutin "ragi02.bmp", 2;
				mes "[ラギ]";
				mes "こうして僕らはまた明日も";
				mes "仲間と冒険を繰り返す～";
				mes "ラ～ララ～ラ～";
				mes "白羽ギルドの物語～";
				next;
				cutin "nines01.bmp", 2;
				mes "[ニュオーズ]";
				mes "……ふう。";
				mes strcharinfo(0) + "、";
				mes "どうかな？";
				next;
				menu "いいね！",-;
				cutin "nines02.bmp", 2;
				mes "[ニュオーズ]";
				mes "本当かい？　嬉しいな！";
				mes "私も素晴らしいと思うよ！";
				mes "とても良い曲ができた。";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "僕も、ニュオーズ様と";
				mes strcharinfo(0) + "さんと";
				mes "合作が作れて嬉しいです。";
				mes "ありがとうございます。";
				next;
				cutin "nines03.bmp", 2;
				mes "[ニュオーズ]";
				mes "うんうん、私も";
				mes "3人でこんな良い曲を作れて";
				mes "大満足だよ～!!";
				next;
				mes "[ニュオーズ]";
				mes strcharinfo(0) + "、";
				mes "ラギ君、ありがとう！";
				next;
				mes "[ニュオーズ]";
				mes "さぁ、さっそく";
				mes "みんなにお披露目してこよう！";
				mes "アイグにも踊ってもらわないと～！";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "僕もお供します。";
				next;
				cutin "nines01.bmp", 2;
				mes "[ニュオーズ]";
				mes "戻ってきたらシャルロシーにも";
				mes "聴かせてあげないとね！";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "そうですね。";
				mes "その時は全員で歌えるように";
				mes "みんなに覚えてもらわないと";
				mes "いけませんねぇ。";
				next;
				cutin "nines03.bmp", 2;
				mes "[ニュオーズ]";
				mes "そうだね～！";
				mes "とっても楽しみだ！";
				close2;
				cutin "nines01.bmp", 255;
				set JTB_2QUE,1;
				setquest 116500;
				compquest 116500;
				end;
			}
		}
	} else {
		cutin "nines02.bmp", 2;
		mes "[ニュオーズ]";
		mes "素敵な曲ができて嬉しいな。";
		close2;
		cutin "nines01.bmp", 255;
		end;
	}
}

1@jtb.gat,24,304,0	script	#周回15番部屋出口	45,2,2,{
	mes "‐ここからメンバーがいる場所へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	warp getmdmapname("1@jtb.gat"),353,42;
	end;
}

//==========================================
// 16番部屋NPC：険しい道＋ボス撃破後イベント
//------------------------------------------
1@jtb.gat,113,295,5	script	ミンミン#16	643,{
	if(JTB_2QUE != 2) {
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "とりあえず";
		mes "アランの方が深刻そうだから、";
		mes "アランの話から聞いてあげて。";
		mes "たぶん私と同じ内容だと思うけど。";
		close2;
		cutin "min02.bmp", 255;
		end;
	} else {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "面倒をかけるわね。";
		mes "……ありがとう。助かるわ。";
		close2;
		cutin "min01.bmp", 255;
		end;
	}
}

1@jtb.gat,116,295,3	script	アラン#16	644,{
	if(JTB_2QUE != 2) {
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "ごめんね、ちょっとミンミンと";
		mes strcharinfo(0)+"に";
		mes "聞いてもらいたいことがあるんだ。";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "私もちょうど";
		mes strcharinfo(0)+"の意見を";
		mes "聞きたいと思っていたところよ。";
		next;
		if(select("シャルロシーの事？","ロテルトのギルド名の事？") == 2) {
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "ちがうわ。";
			mes "アイツの事なんてどうでもいいのよ。";
			mes "本気でおかしなギルド名にしたら";
			mes "脱退するだけだし。";
			mes "そうじゃなくて、あのガキの事よ。";
			next;
			menu "シャルロシーの事？",-;
		}
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "そう、シャルロシーのこと。";
		mes "私はね、ギルドの中では";
		mes "いつも妹みたいな位置づけだから、";
		mes "シャルロシーに会って、";
		mes "同年代の女の子の友達ができて";
		mes "嬉しかったんだ。";
		next;
		mes "[アラン]";
		mes "でもシャルロシーの正体が……";
		mes "モロクの娘って聞いて、";
		mes "すごくびっくりした。";
		next;
		mes "[アラン]";
		mes "騙された！　って気分にもなったけど、";
		mes "ちゃんとシャルロシーの気持ちを聞いて";
		mes "私やみんなで守ってあげなくっちゃって";
		mes "思ったの。";
		next;
		mes "[アラン]";
		mes "だからニュオーズが";
		mes "シャルロシーに、";
		mes "ギルドのメンバーだって言った時は";
		mes "嬉しかった。";
		next;
		mes "[アラン]";
		mes "でも、ロテルトは";
		mes "シャルロシーの事嫌いみたいだし、";
		mes "みんなも本当はどう思ってるのか";
		mes "ちょっと不安になって……。";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "私はあのガキ嫌いよ。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "そうなんだ……。";
		next;
		mes "[アラン]";
		mes "でもミンミン、";
		mes "ガキだなんてひどいよ～。";
		mes "いつも私に言葉遣いは美しく！　って";
		mes "教えてくれてるのに～。";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "うっ……。そうね……。";
		mes "確かに汚い言葉は良くないわね。";
		mes "お里が知れるわ。";
		mes "でもあのガ……あの子、";
		mes "私の事をおばさんって言ったのよ。";
		mes "失礼な子！";
		next;
		mes "[ミンミン]";
		mes "まだそんな歳じゃないのよ！";
		mes "さすがの私も取り乱しちゃったわ。";
		mes "世間知らずなのね。";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "シャルロシーは";
		mes "世間知らずって言うより、";
		mes "産まれたて……なんじゃないかな。";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "産まれたて？";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "うん。";
		mes "魔王モロクが倒されて、";
		mes "支配から解放されたってことは、";
		mes "シャルロシーが自由になったのは";
		mes "少なくともそんな昔の話じゃないはず。";
		next;
		mes "[アラン]";
		mes "と言うことは、";
		mes "初めて自我を持ってから";
		mes "私達に会うまでも、そう時間は";
		mes "経ってないんじゃないかなあ。";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "なるほどね……。";
		mes "そうだとしたらあの子の物知らずや、";
		mes "反応にも説明がつくわ。";
		mes "あの子は産まれたてで、";
		mes "わからない事ばかりなのね。";
		next;
		mes "[ミンミン]";
		mes "だからって、";
		mes "おばさん発言は許せないわよ！";
		mes "産まれたてで世間を知らないのなら、";
		mes "徹底的に正しい物事を教えて、";
		mes "おばさん発言を撤回させてやる！";
		next;
		cutin "arang02.bmp", 2;
		mes "[アラン]";
		mes "えっと、うん、そうだね！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "ちゃんと私の事を名前で";
		mes "呼べるようになるのなら、";
		mes "みんなも気に入ってるみたいだし、";
		mes "私はギルドメンバーとして";
		mes "あの子を迎え入れてもいいと思うわ。";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "本当!?　よかった～！";
		mes "ウチのギルドには頼れる";
		mes "お兄さんもお姉さんもいるんだもん！";
		mes "きっといい子になるよ！";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "それでね、臨時メンバーの";
		mes strcharinfo(0)+"から見て、";
		mes "シャルロシーは危険な子だと思う？";
		next;
		if(select("危険じゃないと思う","危険だと思う") == 1) {
			cutin "arang01.bmp", 255;
			mes "‐あなたはシャルロシーに";
			mes "　悪意を感じる事はなかったことや、";
			mes "　友達がほしいという彼女の願いを";
			mes "　叶えることが出来るのは恐らく";
			mes "　このギルドメンバー以外に";
			mes "　出来ないと思うことを二人に伝えた‐";
			next;
		} else {
			cutin "arang01.bmp", 255;
			mes "‐あなたはシャルロシーが";
			mes "　危険だと思ったことを素直に伝え";
			mes "　その上で、先ずは彼女に";
			mes "　良い事や悪いことについて、";
			mes "　このギルドメンバーがきちんと";
			mes "　教えてあげる必要があるのでは？と";
			mes "　二人に伝えた‐";
			next;
		}
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "私たちが……";
		mes "うん、そうだね。";
		mes strcharinfo(0)+"の";
		mes "言う通りだね！";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "そうね。";
		mes "ニュオーズが言ってたように、";
		mes "私達が最初にここに来たのなら、";
		mes "あの子と会ったことがあるのは";
		mes "私達だけかもしれないわね。";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "よぉし、私の不安は吹き飛んだ～！";
		mes "あとは他のみんなの気持ちも";
		mes "聞いてみないとだよね！";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "とくにロテルトね。";
		mes "プライドが邪魔して";
		mes "本心と違う事を言うクセがあるから";
		mes "厄介なのよね。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "そうだね～。";
		mes "特に私たちギルドメンバーには……。";
		next;
		mes "[アラン]";
		mes "そうだ!!";
		mes strcharinfo(0)+"、";
		mes "ロテルトの説得に協力して欲しいかも！";
		mes "私たちに隠す本音を、";
		mes strcharinfo(0)+"には";
		mes "言ってくれるかもしれないし！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "そうね。いいかも。";
		mes "ロテルトちょっと";
		mes strcharinfo(0)+"の事、";
		mes "気に入ってるみたいだし。";
		next;
		cutin "arang02.bmp", 2;
		mes "[アラン]";
		mes "そうなんだ！";
		mes "全然わからなかった～！";
		mes "さすがだねぇ、ミンミン！";
		next;
		cutin "min03.bmp", 2;
		mes "[ミンミン]";
		mes "長年の勘ってヤツかしら。";
		mes strcharinfo(0)+"と話す時";
		mes "ちょ～っと態度が違うのよね。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "どうかな、";
		mes strcharinfo(0)+"。";
		mes "協力してくれる？";
		next;
		menu "協力する",-;
		cutin "arang02.bmp", 2;
		mes "[アラン]";
		mes "ほんと？　ありがと～！";
		mes "やっぱり持つべきものは";
		mes "臨時でもギルドメンバーだよね～！";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes strcharinfo(0)+"、";
		mes "ありがとう。私からもお礼を言うわ。";
		next;
		cutin "arang01.bmp", 2;
		mes "[アラン]";
		mes "^FF0000ロテルトの説得の前に、";
		mes "他のメンバーにも";
		mes "話を聞いてみてほしいな。^000000";
		mes "みんなの意見を知っていれば";
		mes "ロテルトとの話も";
		mes "スムーズに行くと思うの。";
		next;
		menu "わかった",-;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "そうと決まったら、";
		mes "ロテルトに感付かれる前に";
		mes "私たちも解散した方が良さそうね。";
		next;
		mes "[ミンミン]";
		mes "ロテルトって";
		mes "何気に勘が鋭いところもあるから、";
		mes "^FF0000あまり短時間の間に";
		mes "何度もメンバーに話しかけるのは";
		mes "良くないわ。^000000";
		next;
		mes "[ミンミン]";
		mes "^FF0000十分に時間をおいて、";
		mes "メンバーに話しかけて。^000000";
		mes "面倒をかけるけど、お願いね。";
		next;
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "それじゃあ、またあとで！";
		mes strcharinfo(0)+"、";
		mes "頼んだよ～！";
		close2;
		cutin "arang03.bmp", 255;
		set JTB_2QUE,2;
		setquest 116500;
		compquest 116500;
		end;
	} else {
		cutin "arang03.bmp", 2;
		mes "[アラン]";
		mes "よかったよ～。";
		mes "二人に話すまで不安だったんだ～。";
		mes "ありがとね！";
		close2;
		cutin "arang03.bmp", 255;
		end;
	}
}

1@jtb.gat,117,304,0	script	#周回16番部屋出口	45,2,2,{
	mes "‐ここからメンバーがいる場所へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	warp getmdmapname("1@jtb.gat"),353,42;
	end;
}

//==========================================
// 17番部屋NPC：険しい道＋ボス撃破後イベント
//------------------------------------------
1@jtb.gat,197,284,5	script	ゲルカ#17	629,{
	if(JTB_2QUE != 3) {
		cutin "roel01.bmp", 255;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "どんな必殺技にしようかなあ。";
		mes "師匠を驚かせるためには";
		mes "今までの必殺技より";
		mes "かっこよくしないと……。";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	} else {
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes strcharinfo(0)+"さん、";
		mes "ありがとうございます！";
		mes "おかげで必殺技ができました！";
		close2;
		cutin "roel02.bmp", 255;
		end;
	}
}

1@jtb.gat,204,284,4	script	ロエル#17	10040,{
	if(JTB_2QUE != 3) {
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes strcharinfo(0)+"さん";
		mes "わざわざすみません！";
		next;
		mes "[ロエル]";
		mes "ゲルカさん、僕らの必殺技を";
		mes strcharinfo(0)+"さんに";
		mes "見てもらおうと思って";
		mes "お呼びしたんですよ。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "そうだったんですか！";
		mes strcharinfo(0)+"さん、";
		mes "よろしくお願いします！";
		next;
		mes "[ゲルカ]";
		mes "ロエル君と二人で戦ってみて、";
		mes "お互いの力を合わせた必殺技があれば";
		mes "私たちはより強くなれると";
		mes "気づいたのです。";
		next;
		mes "[ゲルカ]";
		mes "そして必殺技を作って、";
		mes "師匠にお披露目するのです！";
		mes "師匠に認めてもらうには";
		mes "強いだけではなく、";
		mes "かっこよさも必要です！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "なるほど！";
		mes "では、強さとかっこよさを兼ね備えた";
		mes "超新必殺技を考えましょう！";
		next;
		mes "[ロエル]";
		mes strcharinfo(0)+"さんも";
		mes "何か気づいたところがあったら";
		mes "アドバイスお願いします！";
		next;
		menu "わかった",-;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "よろしくお願いします！";
		mes "ではさっそく……";
		mes "必殺技で使うスキルなんですが、";
		mes "何にしましょうか。";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "そうですね……";
		mes "僕はロイヤルガードですから";
		mes "防御系のスキルが得意です。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "防御系！　新しいですね！";
		mes "確かに戦うための";
		mes "戦闘スキルの必殺技も良いですが、";
		mes "仲間を守る必殺技もステキです！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "それでは必殺技は";
		mes "自分や仲間を守る";
		mes "防御系の技にしましょうか！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "はい！";
		mes "私も防御系のスキルを使って、";
		mes "二人で完全なる";
		mes "鉄壁の防御を完成させましょう！";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "鉄壁の防御!!";
		mes "すばらしくかっこいい響きです！";
		mes "鉄壁と言えばオートガードですね。";
		mes "僕は必殺技に";
		mes "オートガードを使いたいと思います！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "では私は……";
		next;
		if(select("金剛","阿修羅覇凰拳") == 2) {
			cutin "gelca04.bmp", 2;
			mes "[ゲルカ]";
			mes "阿修羅覇凰拳ですか？";
			mes "確かにかっこいいスキルですが……。";
			mes "防御系のスキルがいいんです！";
			next;
			menu "じゃあ……金剛は？",-;
			mes "……！　そうですね！";
		} else {
			cutin "gelca03.bmp", 2;
			mes "そうですね！";
		}
		mes "[ゲルカ]";
		mes "修羅の防御といえば金剛！";
		mes "金剛にしましょう！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "それでは";
		mes "僕はオートガード、";
		mes "ゲルカさんは金剛で、";
		mes "鉄壁の防御を作りましょう！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "はい！では……";
		mes "どちらからスキルを使いますか？";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "僕はゲルカさんの金剛から";
		mes "発動する方がかっこいいと思います！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "えぇ～！　私は";
		mes "ロエル君のオートガードからが";
		mes "いいと思いますよ!!";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "そうですか？";
		mes "う～ん、悩みますね……。";
		mes "そうだ！　こんな時こそ！";
		mes strcharinfo(0)+"さんに";
		mes "決めていただきましょう!!";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "そうですね！　見る人からは";
		mes "どちらがかっこよく見えるのか、";
		mes strcharinfo(0)+"さんの";
		mes "意見をききたいです!!";
		next;
		if(select("ロエルのオートガードから","ゲルカの金剛から") == 1) {
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "わかりました！";
			mes "ではさっそくやってみましょう！";
			mes "ロエル君、いきますよ！";
			next;
			cutin "roel02.bmp", 2;
			mes "[ロエル]";
			mes "はい!!";
			next;
			emotion 44,getmdnpcname("ロエル#17");
			cutin "roel01.bmp", 0;
			mes "[ロエル]";
			mes "鉄壁の盾！";
			mes "ロエル式オートガード!!";
			misceffect 214,getmdnpcname("ロエル#17");
			next;
			emotion 44,getmdnpcname("ゲルカ#17");
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "完全なる防御！";
			mes "ゲルカ式ニノ型・金剛!!";
			misceffect 203,getmdnpcname("ゲルカ#17");
			next;
		} else {
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "わかりました！";
			mes "ではさっそくやってみましょう！";
			mes "ロエル君、いきますよ！";
			next;
			cutin "roel02.bmp", 2;
			mes "[ロエル]";
			mes "はい!!";
			next;
			emotion 44,getmdnpcname("ゲルカ#17");
			cutin "gelca01.bmp", 2;
			mes "[ゲルカ]";
			mes "完全なる防御！";
			mes "ゲルカ式ニノ型・金剛!!";
			misceffect 203,getmdnpcname("ゲルカ#17");
			next;
			emotion 44,getmdnpcname("ロエル#17");
			cutin "roel01.bmp", 0;
			mes "[ロエル]";
			mes "鉄壁の盾！";
			mes "ロエル式オートガード!!";
			misceffect 214,getmdnpcname("ロエル#17");
			next;
		}
		cutin "gelca01.bmp", 2;
		mes "[ロエル&ゲルカ]";
		mes "クロス！";
		misceffect 220,getmdnpcname("ロエル#17");
		misceffect 220,getmdnpcname("ゲルカ#17");
		next;
		cutin "roel01.bmp", 0;
		mes "[ロエル&ゲルカ]";
		mes "我らは自身と仲間を守る盾となる!!";
		misceffect 249,getmdnpcname("ロエル#17");
		misceffect 374,getmdnpcname("ゲルカ#17");
		misceffect 246,getmdnpcname("ロエル#17");
		misceffect 13,getmdnpcname("ゲルカ#17");
		misceffect 13,getmdnpcname("ロエル#17");
		misceffect 336,getmdnpcname("ロエル#17");
		misceffect 41,getmdnpcname("ゲルカ#17");
		misceffect 41,getmdnpcname("ロエル#17");
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "……ふぅ。";
		mes "どうでしたか、";
		mes strcharinfo(0)+"さん。";
		next;
		menu "良いと思う",-;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "!!　ありがとうございます！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "やりましたね！　ゲルカさん！";
		mes strcharinfo(0)+"さん、";
		mes "色々意見をくださって";
		mes "ありがとうございます！";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "はい！　これなら師匠も";
		mes "合格点をくれると思います！";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ロテルト様は";
		mes "必殺技には厳しい方という";
		mes "イメージがありますが、";
		mes "実際にはどんな方なんですか？";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "そうですね、師匠は";
		mes "必殺技には特にうるさいですね。";
		next;
		mes "[ゲルカ]";
		mes "必殺技とは！";
		mes "いざという時に使うもの！";
		mes "したがって、そのいざと言う時に";
		mes "完璧に使いこなせるよう、";
		mes "日々鍛錬を重ねる事！";
		mes "これが師匠の教えです。";
		next;
		mes "[ゲルカ]";
		mes "そして師匠自らもまた、";
		mes "アークビショップでありながら";
		mes "筋力トレーニングを欠かさず";
		mes "毎日、行っているんです！";
		next;
		mes "[ゲルカ]";
		mes "仲間を守るには先ず自分も";
		mes "身体を鍛えて強くならないと";
		mes "意味がないからと！";
		next;
		mes "[ゲルカ]";
		mes "ただ……";
		mes "一つ不満があるとすれば、";
		mes "アークビショップの衣装では";
		mes "師匠の鍛え抜かれた素晴らしい";
		mes "大胸筋や腹直筋が";
		mes "見れないことなんですよね。";
		next;
		cutin "roel03.bmp", 2;
		mes "[ロエル]";
		mes "……き、筋肉のことは";
		mes "僕には良くわかりませんが、";
		mes "素晴らしい教えですね！";
		mes "さすが、ロテルト様だなあ。";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "はい！　師匠は";
		mes "ちょっと口が悪いけど";
		mes "強いし、仲間思いですし、";
		mes "素晴らしい方です！";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "……だから、";
		mes "シャルロシーちゃんの事も";
		mes "警戒しているのだと思います。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "仲間に危険があるかもしれないと";
		mes "警戒されているのですね。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "きっとそうだと思います。";
		mes "シャルロシーちゃんの事が";
		mes "嫌いなわけではないと思います。";
		next;
		mes "[ゲルカ]";
		mes "意味もなく、";
		mes "人を嫌ったりする方ではないので。";
		mes "口が悪いので";
		mes "誤解されやすいんですけどね。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "なるほど。確かにマスターとして、";
		mes "ギルドメンバーを守ることは";
		mes "とても大事な事です。";
		mes "ロテルト様はそれを";
		mes "気にかけていらっしゃるのでしょう。";
		next;
		mes "[ロエル]";
		mes "僕だって、";
		mes "仲間が危険な目に合うのは嫌です！";
		mes "でも、僕にはシャルロシーさんが";
		mes "みんなに危害を加えるとは";
		mes "思えないのですが……。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "そうですね。私もそう思います。";
		mes "シャルロシーちゃんは";
		mes "お友達が欲しかっただけだと思います。";
		mes "私は、シャルロシーちゃんと";
		mes "もっと色々話したかったです。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "大丈夫です、ゲルカさん!!";
		mes "シャルロシーさんは";
		mes "きっと戻ってきます!!";
		next;
		mes "[ロエル]";
		mes "シャルロシーさんが戻ってきて";
		mes "もしも危険なことがあったら、";
		mes "その時は僕らの必殺技で";
		mes "みんなを守りましょう！";
		next;
		mes "[ロエル]";
		mes "もちろん、";
		mes "シャルロシーさんも守ります！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "ロエル君……!!";
		mes "そうですね！　私たちが";
		mes "みんなを、シャルロシーちゃんを";
		mes "守りましょう!!";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "さあ、そうと決まったら！";
		mes "必殺技の練習です！";
		mes "僕らが本当に強くなれば";
		mes "ロテルト様も少しは";
		mes "安心してくださるでしょう！";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "そうですね！";
		mes "頑張りましょう！";
		close2;
		cutin "gelca01.bmp", 255;
		set JTB_2QUE,3;
		setquest 116500;
		compquest 116500;
		end;
	} else {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "必殺技を練習しています！";
		mes "かっこよく、そして強くなるために！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
}

1@jtb.gat,200,304,0	script	#周回17番部屋出口	45,2,2,{
	mes "‐ここからメンバーがいる場所へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	warp getmdmapname("1@jtb.gat"),353,42;
	end;
}

//==========================================
// 18番部屋NPC：険しい道＋ボス撃破後イベント
//------------------------------------------
1@jtb.gat,32,376,5	script	ルナイン#18	10039,{
	if(JTB_2QUE != 4) {
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "べ、別にシャルロシーの事なんて";
		mes "気にしてないわよ！";
		mes "全然さみしくなんかないんだから！";
		close2;
		cutin "lunain04.bmp", 255;
		end;
	} else {
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "私は私のするべきことをやるだけよ。";
		mes "バカロエルになんか負けないわ。";
		close2;
		cutin "lunain04.bmp", 255;
		end;
	}
}

1@jtb.gat,40,378,5	script	メロディージャック#18	844,{
	if(JTB_2QUE != 4) {
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "聞き耳など立てていない！";
		mes "隠れているのは";
		mes "癖みたいなものだ！";
		close;
	} else {
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "ふん。私に気づかないとは";
		mes "あの二人もまだまだだな。";
		close;
	}
}

1@jtb.gat,37,376,3	script	アイグ#18	646,{
	if(JTB_2QUE != 4) {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "ルナイン……";
		mes "そんな悲しい顔しないでなの。";
		mes "私まで悲しくなっちゃうの。";
		next;
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "悲しくなんかない！　別に";
		mes "シャルロシーが行っちゃったからって";
		mes "悲しくなんかないんだから！";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "やっぱりシャルロシーの事なの。";
		mes "ルナイン泣いちゃいそうなの。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "なによ……アイグの方が";
		mes "泣きそうになってるじゃないの。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "泣いてないの！　大丈夫なの！";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "私だって泣いてないんだから！";
		next;
		if(select("声をかける","そっとしておく") == 1) {
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes "!?　ちょっと、";
			mes strcharinfo(0)+"！";
			mes "そ、そんなところで何見てるのよ！";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "ほんとなの。";
			mes strcharinfo(0)+"がいるの！";
			mes "どうしたの？";
			mes "なにかあったの？　なの。";
			next;
		} else {
			cutin "igu02.bmp", 255;
			mes "["+strcharinfo(0)+"]";
			mes "アイグ、ルナイン……";
			next;
			cutin "lunain04.bmp", 2;
			mes "[ルナイン]";
			mes strcharinfo(0)+"!!";
			mes "な、なによ！　びっくりするじゃない！";
			next;
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "どうしたの？";
			mes "なにかあったの？　なの。";
			next;
		}
		menu "シャルロシーの事で話がある",-;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "別にあの子がいなくなって";
		mes "さみしいとか、そんなことないわよ！";
		mes "ちょっと静かになったくらいよ！";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "ルナイン……それ、さみしいって";
		mes "言ってるようなものなの。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "!!!!!!";
		mes "そ、そんなことッ……！";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "…………。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……さみしいわよ。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "急にどっか行っちゃうんだもの。";
		mes "さみしいに決まってるじゃない。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "私もさみしいの。";
		mes "せっかく仲良くなれたのに。";
		next;
		menu "魔王の娘なのに怖くないの？",-;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "不思議と怖くはないわね。";
		mes "でも、どんなに仲良くなれたとしても";
		mes "あの子は魔王の娘……。";
		mes "確かに全く不安がないかと言われれば";
		mes "そんなことはないわ。";
		next;
		mes "[ルナイン]";
		mes "でも私たちを襲ったりしなかったし、";
		mes "モンスターとは友達になれないと";
		mes "ずっと思ってたけど、";
		mes "そんなことないのかもしれない。";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシーは";
		mes "友達が欲しいって願って";
		mes "そこに私たちが現れたの。";
		mes "だったら、もう私たちは友達なの！";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "友達……でも……。";
		mes "私は……";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "本当はルナインはもう、";
		mes "シャルロシーの事、友達だと思ってる。";
		mes "だからシャルロシーが";
		mes "いなくなってさみしいの。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "友達が遠くに行ってしまって";
		mes "さみしいけど……";
		mes "シャルロシーとは";
		mes "また会えるような気がするの。";
		next;
		mes "[アイグ]";
		mes "だから、また会えたら、";
		mes "その時、ルナインの気持ちを";
		mes "伝えればいいと思うの。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……そっか……そうよね。";
		mes "友達になれるとかそういうの";
		mes "まだよくわからないけど、";
		mes "シャルロシーが居なくなって";
		mes "ちょっとさみしいのは事実よ。";
		next;
		mes "[ルナイン]";
		mes "また会えるかもしれないなら、";
		mes "その時悩むことにするわ。";
		mes "だからもう私は";
		mes "メソメソしたりなんかしない。";
		mes "私にはやらなきゃいけない";
		mes "大事なことがあるから。";
		next;
		menu "大事なこと？",-;
		cutin "lunain01.bmp", 2;
		mes "[ルナイン]";
		mes "そうよ。";
		mes "あのバカロエルと同じような目標なんて";
		mes "ちょっと不服だけど、";
		mes "私だって強くなりたいの。";
		next;
		mes "[ルナイン]";
		mes "ニュオーズ様も、みんなも";
		mes "守れるくらい強く、ね。";
		mes "女だから、ハイプリーストだからって";
		mes "足手まといはご免だわ。";
		next;
		cutin "igu03.bmp", 2;
		mes "[アイグ]";
		mes "ルナイン、かっこいいの！";
		next;
		mes "[アイグ]";
		mes "じゃあ、私はもっともっと";
		mes "みんなを元気にする";
		mes "歌や音楽や踊りを、";
		mes "世界中に届け続けるの！";
		next;
		mes "[アイグ]";
		mes "どこか遠くにいるシャルロシーにも";
		mes "きっと届くはず……なの！";
		next;
		menu "素敵な目標だね",-;
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "ありがとうなの♪";
		mes "頑張るの！";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "べ、別に！";
		mes strcharinfo(0)+"に";
		mes "褒められても嬉しくないわよ！";
		mes "……みんなには言わないでよ。";
		mes "ナイショなんだからね！";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "そろそろ戻らないと";
		mes "みんな心配するの。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "そうね。色々詮索されても面倒だわ。";
		mes "別に泣いてなんかないけど。";
		next;
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "じゃあ"+strcharinfo(0)+"。";
		mes "私たちは先に戻るの！";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes strcharinfo(0)+"！";
		mes "余計なことは言わないでよね！";
		mes "わかってるわよね！";
		next;
		cutin "lunain04.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "大丈夫だ。私も喋ったりしない。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "ジャック……！";
		mes "また隠れてたの？";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "!?!?";
		mes "えっ、ちょ、ちょっと！";
		mes "今の話きいてたの!?";
		next;
		cutin "lunain04.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "フン。二人の質問への返答は";
		mes "両方イエスだ。";
		mes "大丈夫だ。誰にも言わん。";
		mes "安心するといい。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "安心なんてできないわよ！";
		mes "いい？　絶対だからね！";
		mes "絶対、言わないでよねっ！";
		next;
		cutin "lunain04.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "ああ。";
		mes "ルナイン、お前が泣いていた事は";
		mes "誰にも言わん。";
		next;
		cutin "lunain04.bmp", 2;
		mes "[ルナイン]";
		mes "なっ！　泣いてなんかいないわよっ！";
		mes "もー！";
		mes "アイグ、行こ！";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "あっ、ルナイン待ってなの！";
		mes strcharinfo(0)+"、";
		mes "ジャック、また後で！　なの！";
		next;
		cutin "igu02.bmp", 255;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "隠れている私に気づかないとは、";
		mes "あの二人もまだまだだな。";
		mes strcharinfo(0)+"、";
		mes "お前は気づいていただろう？";
		next;
		if(select("気付いていた","気付かなかった") == 1) {
			emotion 9,getmdnpcname("メロディージャック#18");
			mes "[メロディージャック]";
			mes "さすがだな。";
			next;
		} else {
			emotion 9,getmdnpcname("メロディージャック#18");
			mes "[メロディージャック]";
			mes "フン、お前もまだまだだな。";
			next;
		}
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "まぁ、聞きたそうにしているから";
		mes "先に言っておこう。";
		next;
		mes "[メロディージャック]";
		mes "私はあの少女については";
		mes "どうでもいい。";
		mes "魔王の娘と言っても";
		mes "悪意や殺意は感じなかったからな。";
		next;
		mes "[メロディージャック]";
		mes "アイグも気に入ってるようだし、";
		mes "危害を加えないのならば";
		mes "私からは何もしない。";
		next;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "何かあれば私は戦う。";
		mes "それだけだ。";
		next;
		menu "わかった",-;
		emotion 9,getmdnpcname("メロディージャック#18");
		mes "[メロディージャック]";
		mes "では私も戻るとしよう。";
		mes "アイグが心配だ。";
		close2;
		cutin "igu02.bmp", 255;
		set JTB_2QUE,4;
		setquest 116500;
		compquest 116500;
		setquest 116501;
		end;
	} else {
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "シャルロシーにも";
		mes "私の歌は届くはずなの♪";
		close2;
		cutin "igu02.bmp", 255;
		end;
	}
}

1@jtb.gat,35,390,0	script	#周回18番部屋出口	45,2,2,{
	mes "‐ここからメンバーがいる場所へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	warp getmdmapname("1@jtb.gat"),353,42;
	end;
}

//==========================================
// 19番部屋NPC：険しい道＋ボス撃破後イベント
//------------------------------------------
1@jtb.gat,112,377,3	script	ロテルト#19	630,{
	if(JTB_2QUE != 5) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes strcharinfo(0)+"、";
		mes "話ってなんだ？";
		mes "俺は忙しいんだ。手短に頼むぜ。";
		next;
		if(select("単刀直入に言う","まずは世間話をする") == 1) {
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "あの魔王の娘の事か。";
			mes "なんだ、お前もアイツを";
			mes "気に入っているのか。";
			next;
		} else {
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "なんだ？";
			mes "そんな世間話のために";
			mes "俺を呼んだんじゃないんだろ？";
			next;
			mes "[ロテルト]";
			mes "俺は忙しいと言ってるんだ。";
			mes "早く用件を話せ。";
			next;
		}
		menu "シャルロシーをギルドに入れてください",-;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "お前もか……。";
		mes "どいつもこいつも、後先考えなく";
		mes "簡単に言いやがって……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "いいか。あいつは悪魔だ。";
		mes "しかも、魔王に作られた使徒。";
		mes "魔王モロクに";
		mes "より近い悪魔だ。";
		next;
		mes "[ロテルト]";
		mes "俺も一応、聖職者の端くれだ。";
		mes "魔は滅するものだと心得ている。";
		mes "更に魔王の使徒ときたら、";
		mes "普通は即刻処分するものだ。";
		next;
		mes "[ロテルト]";
		mes "それをギルドに入れるだと？";
		mes "有り得ないだろう！";
		mes "これでも一応ギルドマスターだ。";
		mes "メンバーに危険が及ぶかもしれない";
		mes "不安要素を、ギルドに";
		mes "迎え入れるわけにはいかない。";
		next;
		mes "[ロテルト]";
		mes "依って"+strcharinfo(0)+"。";
		mes "お前の要望は却下だ。";
		next;
		mes "[ロテルト]";
		mes "話はそれだけか？";
		mes "だったらもう戻るぞ。";
		next;
		menu "待ってください",-;
		mes "[ロテルト]";
		mes "なんだ？　まだ何かあるのか？";
		mes "何度も言うが俺は忙しいんだ。";
		mes "くだらない話は辞めてくれよ。";
		next;
		menu "敵意がない相手でも危険なのか？",-;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……お前もしつこいな……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ああそうだ。相手に敵意がなくとも、";
		mes "滅すべき存在だという認識は";
		mes "なにも変わらない。";
		mes "相手が悪魔ならなおさらだ。";
		next;
		mes "[ロテルト]";
		mes "聖職者とはそういうものなんだよ。";
		mes "仲間を守るために必要な事だ。";
		next;
		menu "仲間が望まなくとも？",-;
		mes "[ロテルト]";
		mes "仲間が望まない……か。";
		mes "臨時メンバーのくせに";
		mes "知ったような言い方しやがる。";
		next;
		mes "[ロテルト]";
		mes "ああ、知っているとも。";
		mes "あいつらがあの娘を";
		mes "気に入っている事も。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "ニュオーズの奴が";
		mes "本気でギルドに入れたがっている事も！";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "でもな！　今は俺がマスターだ！";
		mes "メンバーを危険な目に";
		mes "合わせる訳にはいかねぇ！";
		next;
		mes "[ロテルト]";
		mes "もしあの魔王の使徒が、";
		mes "突然襲い掛かってきたらどうする？";
		mes "油断しているアイツらは";
		mes "すぐにやられてしまうだろう！";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "悪魔とはそういう生き物だ！";
		mes "人の心を読み、その隙をついてくる。";
		mes "だから俺ら聖職者は";
		mes "転職の時からそれを教えられ、";
		mes "それを見抜くための修業をするんだ！";
		next;
		menu "シャルロシーの事も見抜けるのでは？",-;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "俺に見抜けるか、だと……？";
		next;
		mes "[ロテルト]";
		mes "…………";
		next;
		mes "[ロテルト]";
		mes "なんだ？";
		mes "お前は人の心を見抜く修行でも";
		mes "してるのか？";
		next;
		mes "[ロテルト]";
		mes "それとも";
		mes "あの悪魔の使徒のような";
		mes "人の心を読む力でも持っているのか？";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……そうだ。";
		mes "俺にはもうわかっている。";
		mes "あの魔王の使徒、シャルロシーが";
		mes "俺らを騙すつもりなど無い事を。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "あいつは本当に";
		mes "ただ、仲間が欲しかっただけだ。";
		next;
		mes "[ロテルト]";
		mes "だが、だからと言って";
		mes "そう簡単に";
		mes "ギルドメンバーにする事は";
		mes "できないだろう。";
		next;
		mes "[ロテルト]";
		mes "あいつが無害なのはわかっている。";
		mes "しかし、もし、";
		mes "心が変わってしまったらどうする。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "もし、ある日突然";
		mes "人間を襲ったらどうするんだ！";
		next;
		menu "その時はあなたがみんなを守ればいい",-;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "ああ、その時は守るさ！";
		mes "だがしかし、相手は魔王直属の使徒！";
		mes "一般のモンスターとは";
		mes "明らかに強さが違うだろう！";
		next;
		mes "[ロテルト]";
		mes "それに、またあの";
		mes "ペルというモンスターも";
		mes "大量に現れるかもしれん！";
		next;
		mes "[ロテルト]";
		mes "俺一人でどうやって";
		mes "すべての人間を守れる!?";
		next;
		menu "なぜ一人で守ろうとする",-;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "なん、だと……!?";
		next;
		menu "仲間と共に戦うという選択肢はないのか",-;
		mes "[ロテルト]";
		mes "……";
		next;
		mes "[ロテルト]";
		mes "…………";
		next;
		mes "[ロテルト]";
		mes "………………。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……仲間と共に……か。";
		mes "わかったよ、降参だ。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "本当はわかっていたんだ。";
		mes "どうすれば";
		mes "メンバーにとって、";
		mes "あの魔王の使徒にとって、";
		mes "一番良いかを。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "だけどな、";
		mes "聖職者としての無駄なプライドとか、";
		mes "ちょっとした意地とかで";
		mes "それを見ないフリしていた。";
		next;
		mes "[ロテルト]";
		mes "それに俺は、";
		mes "聖職者なんてやってるが";
		mes "神の類を妄信してるわけじゃねぇ。";
		mes "むしろ頭の固い教会のお偉い連中は";
		mes "嫌いなくらいだしな。";
		next;
		mes "[ロテルト]";
		mes "……あいつらの困った顔を見れるなら";
		mes "面白いかもしれないしな……。";
		next;
		menu "と言うことは!?",-;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……まだハッキリと";
		mes "決めたわけじゃねえぞ!?";
		next;
		mes "[ロテルト]";
		mes "……あいつの話くらいは";
		mes "聞いてやるって事だ！";
		next;
		menu "あいつ？",-,"名前を言ってくれないとわからない",-;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "クッ……！";
		mes "シャルロシーだ!!";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "いいな!!　お前らや、";
		mes "あいつのためじゃないからな!!";
		mes "俺が面白そうだと思ったからだ！";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "……フン。";
		mes "調子が狂うぜ……。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "そういえば昔、";
		mes "今のお前に言われた事と";
		mes "似たようなことを言った奴がいたな。";
		next;
		mes "[ロテルト]";
		mes "まさかお前に";
		mes "同じことをいわれるとはな……。";
		next;
		mes "[ロテルト]";
		mes "……まあいい。";
		mes strcharinfo(0)+"、";
		mes "お前と話して吹っ切れたぜ。";
		next;
		mes "[ロテルト]";
		mes "臨時メンバーのお前に";
		mes "こんなこと言うのも何だが、";
		mes strcharinfo(0)+"、";
		mes "お前がメンバーで良かったよ。";
		next;
		cutin "rote04.bmp", 2;
		mes "[ロテルト]";
		mes "……ありがとな。";
		close2;
		cutin "rote04.bmp", 255;
		set JTB_2QUE,5;
		setquest 116500;
		compquest 116500;
		compquest 116501;
		end;
	} else {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "先に戻れ、俺は後から行く。";
		mes "少し頭の中を整理したい。";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
}

1@jtb.gat,109,390,0	script	#周回19番部屋出口	45,2,2,{
	mes "‐ここからメンバーがいる場所へ";
	mes "　移動することができるようだ‐";
	next;
	if(select("移動しない","移動する") == 1) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐移動しよう‐";
	close2;
	warp getmdmapname("1@jtb.gat"),353,42;
	end;
}

//==========================================
// 外伝：不名誉な疑惑
//------------------------------------------
jtb_01.gat,198,31,5	script	ミンミン#03	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "ニュオーズ、話があるんだけど。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "どうかした？　ミンミン。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "どうかした？って、あなたね！";
	mes "その手を握って連れてる子は誰よ。";
	next;
	mes "[ミンミン]";
	mes "まさかニュオーズ……";
	mes "とうとう本物のロリコンに……。";
	next;
	menu "ニュオーズはロリコンなの？",-;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes strcharinfo(0)+"……";
	mes "いきなり現れて";
	mes "ロリコンとは酷いなあ！";
	mes "確かにこの子は可愛いけどね♪";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "それで、本当に";
	mes "その子は何なの？";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "この子とはこの洞窟で";
	mes "会っただけだよ～！";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "……こんな場所で？";
	mes "ねえ、普通に考えて、";
	mes "怪しくないかしら？";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[？？？]";
	mes "……ニュオーズ。";
	mes "このおばさん、誰？";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "……おばさん？";
	next;
	mes "[ミンミン]";
	mes "……は？";
	mes "まさかとは思うけど……";
	mes "私のこと!?";
	next;
	menu "多分……",-;
	mes "[ミンミン]";
	mes "……。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ミンミン～？";
	mes "おーい。";
	next;
	mes "[ニュオーズ]";
	mes "反応ない……。";
	mes "おばさん発言がかなり";
	mes "ショックだったみたい。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[？？？]";
	mes "……？";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "女の人におばさんなんて";
	mes "言っちゃだめだよー？";
	next;
	mes "[ニュオーズ]";
	mes "今度言ったら、めっ！　だよ～。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[？？？]";
	mes "……いわない。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "さて……おーい、";
	mes "ミンミンちゃーん。";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "……誰がミンミンちゃんよっ!!";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "お、さすがにこの呼び方は";
	mes "効果あったみたいだね。";
	next;
	menu "謝ったほうがいいのでは？",-;
	mes "[ニュオーズ]";
	mes "そうだね。";
	mes "ミンミンにごめんなさいしよう。";
	next;
	cutin "shaloshi01.bmp", 2;
	mes "[？？？]";
	mes "……ごめんなさい。";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "……。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ミンミン、謝ったんだし";
	mes "そんな怖い顔……";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "違うわよ!!　モンスターよ!!";
	mes "早く構えなさいっ!!";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "おおっと～。了解だよ。";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "私……そんなに老けて見えるの……？";
	next;
	cutin "min02.bmp", 255;
	mes "‐ミンミンは武器を構えながら";
	mes "　ぶつぶつ呟いている。";
	mes "　どうやら相当ショックを";
	mes "　受けたようだ……‐";
	close2;
	if(!(checkquest(116520) & 0x8)) {
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		setquest 116520;
		compquest 116520;
	}
	end;
}

jtb_01.gat,205,31,4	script	ニュオーズ#03	625,{
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ミンミンはまだまだ若いんだよ。";
	close2;
	cutin "nines01.bmp", 255;
	end;
}

jtb_01.gat,204,33,4	script	？？？#03	10041,{
	cutin "shaloshi02.bmp", 2;
	mes "[？？？]";
	mes "……おばさん。";
	mes "……お姉さん？";
	close2;
	cutin "shaloshi02.bmp", 255;
	end;
}

jtb_01.gat,220,23,0	script	3番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：弟子と師匠
//------------------------------------------
jtb_01.gat,291,42,5	script	ロテルト#04	630,{
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "必殺技はいいぞ。";
	mes "確実に敵を葬り、";
	mes "仲間を助けることができる。";
	mes "なにより、格好良いだろ？";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

jtb_01.gat,297,42,4	script	ゲルカ#04	629,{
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "ドーモ、シショウ＝サン";
	mes "ゲルカデス！";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "……お前また変な本読んだな？";
	next;
	cutin "gelca03.bmp", 2;
	mes "[ゲルカ]";
	mes "アマツで今人気の小説ですよ！";
	mes "名前は確か……。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "……それより";
	mes "何故お前を呼んだかわかるか？";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "むむ……";
	mes "師匠から真面目オーラが見えます。";
	next;
	mes "[ゲルカ]";
	mes "あ、"+strcharinfo(0)+"さん。";
	mes "こういう時の師匠に";
	mes "冗談は通じませんから";
	mes "気をつけてください。";
	next;
	menu "わかった",-;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "ゲルカ、お前も感じただろ？";
	mes "この洞窟……何かある。";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "そうですね……";
	mes "得体の知れない力を感じます。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "こういう時こそ、";
	mes "アレが役に立つかもしれねーからな。";
	mes "軽く練習しておくぞ。";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "そうですね！";
	mes "さすが師匠です！";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes strcharinfo(0)+"は";
	mes "俺たちが今からやることを見て、";
	mes "悪い部分がないか教えてくれ。";
	next;
	mes "[ロテルト]";
	mes "いくぞ、ゲルカ!!";
	mes "超必殺技ナンバー8だ!!";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "はい！";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "我は解放せん！";
	mes "聖なる光！　デュプレライト！";
	misceffect 220,"ロテルト#04";
	misceffect 40,"ロテルト#04";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "我が力、悪しき者を打ち砕け!!";
	mes "二重の天羅地網！";
	misceffect 330;
	misceffect 377;
	misceffect 203;
	next;
	cutin "gelca01.bmp", 255;
	mes "[ロテルト&ゲルカ]";
	mes "我と汝の力、等しく滅びを与えん！";
	next;
	mes "[ロテルト&ゲルカ]";
	mes "昇天!!　舞い散れ!!　閃光の道標よ!!";
	misceffect 85,"ロテルト#04";
	misceffect 85;
	misceffect 226,"ロテルト#04";
	misceffect 226;
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "ふう。相変わらず師匠は凄いですね!!";
	next;
	mes "[ゲルカ]";
	mes "無駄のない身体と";
	mes "高度な体術……うーん。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "なんだ？";
	next;
	cutin "gelca03.bmp", 2;
	mes "[ゲルカ]";
	mes "師匠!!　アークビショップより";
	mes "絶対修羅のほうがいいですよ!!";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "フン。";
	mes "俺はこの格好が気に入ってるんだ。";
	mes "それに男が露出しても……";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "こうなったら!!";
	mes strcharinfo(0)+"さんは";
	mes "どう思います!?";
	next;
	switch(select("修羅がいい","アークビショップがいい")) {
	case 1:
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "ほら!!";
		mes strcharinfo(0)+"さんも";
		mes "言ってますよ!!";
		next;
		mes "[ゲルカ]";
		mes "鍛え抜かれた筋肉にほとばしる汗!!";
		mes "それに勝るかっこよさは";
		mes "ありませんよ!?";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "なんだお前……筋肉フェチなのか!?";
		mes "それとも変態……。";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "酷いですよ、師匠!!";
		mes "私はちょっと大胸筋と腹直筋が";
		mes "好きなだけです!!";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "……。";
		next;
		cutin "rote01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "……。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "お二人にはどうやら、";
		mes "筋肉の素晴らしさを語る";
		mes "必要がありそうですね！";
		break;
	case 2:
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes strcharinfo(0)+"、";
		mes "わかってるじゃねーか。";
		next;
		cutin "gelca04.bmp", 2;
		mes "[ゲルカ]";
		mes "何を言っているんですか!!";
		next;
		mes "[ゲルカ]";
		mes "師匠はかっこよくて強いですけど……";
		mes "足りないものがあります!!";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "それはズバリ!!　露出です!!";
		mes "特に鍛え抜かれた身体は……。";
		break;
	}
	next;
	cutin "gelca01.bmp", 255;
	mes "["+strcharinfo(0)+"]";
	mes "（……口を挟む余地がないほど";
	mes "すごい剣幕だ。）";
	next;
	misceffect 194;
	cutin "gelca04.bmp", 2;
	mes "[ゲルカ]";
	mes "きゃんっ！　師匠!!";
	mes "いきなりチョップって酷いですよ!?";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "お前は興奮すると話が長いうえに、";
	mes "緊張感がなさすぎだ。";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "うう～……すいません……。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "とにかく、この洞窟は";
	mes "普通じゃねぇからな……。";
	mes "みんな無事だといいんだが……。";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "師匠、超必殺技の前に";
	mes "緊急召集を練習するべきでしたね……。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "それより先に、お前はもっと";
	mes "危機感をもつべきだな。";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "はぁい……。";
	next;
	cutin "gelca02.bmp", 255;
	mes "["+strcharinfo(0)+"]";
	mes "（この2人、本当にいい";
	mes "師弟関係だなあ。）";
	close2;
	if(!(checkquest(116521) & 0x8)) {
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		setquest 116521;
		compquest 116521;
	}
	end;
}

jtb_01.gat,306,47,0	script	4番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：モンスターの落し物
//------------------------------------------
jtb_01.gat,115,113,4	script	アイグ#06	646,{
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "最近はレッスンやライブが忙しくて";
	mes "冒険ができなかったけど、";
	mes "やっぱりこうやって冒険すると";
	mes "気分がいいの！";
	mes "ニュオーズにも会えたし！";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

jtb_01.gat,112,119,5	script	ミンミン#06	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "ここは本当に不思議なものばかりね。";
	close2;
	cutin "min01.bmp", 255;
	end;
}

jtb_01.gat,111,115,5	script	アラン#06	644,{
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "宝石って綺麗だよね！";
	mes "私も自分の宝石欲しいなぁ。";
	close2;
	cutin "arang01.bmp", 255;
	end;
}

jtb_01.gat,116,117,4	script	ルナイン#06	10039,{
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "ミンミン。";
	mes "これなんだと思う？";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "そうね……見た感じだと";
	mes "ただの真珠にしか見えないわね。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "凄く綺麗なの♪";
	next;
	menu "どうかしたの？",-;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "あ、"+strcharinfo(0)+"。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "さっき、あの小さいモンスターが";
	mes "これを落としたの。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "真珠よりルビーが好きだなあ♪";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "大きさは測ったように";
	mes "全部同じね。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "……。";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "ちょっと、アイグ。";
	mes "どうしたのよ。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "……え？";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "アイグ、泣いてるの……？";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "あ、あれ……？";
	mes "どうして私泣いてるの？";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "それはこっちが聞きたいわ。";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "この真珠、凄く綺麗だなって";
	mes "見てて……。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "うん。";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "でもなんていうか……";
	mes "綺麗なだけだって、気づいたの。";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "どういうこと？";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "うまく言えないんだけど……";
	mes "空っぽなの……。";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "綺麗なだけで、この真珠には";
	mes "何も惹かれるものがないの。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "それは多分、イミテーションだから";
	mes "じゃないかしら？";
	next;
	menu "イミテーション？",-;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "模造品ってことね。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "これ、真珠じゃないの？";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "成分は詳しく調べないと";
	mes "わからないけどね。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "ただ、見た限りこれは自然に作られた";
	mes "モノではないことは確かね。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "うん……見よう見まねで";
	mes "作られた感じなの……。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "本当だ、中身がスカスカみたいに";
	mes "凄く軽いし……って、ミンミン!?";
	next;
	misceffect 3,"ミンミン#06";
	cutin "arang01.bmp", 255;
	mes "‐ミンミンは真珠をいきなり";
	mes "　地面に叩きつけた！‐";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "音もなく消えた……!?";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "まるであの小さいモンスターが";
	mes "消える時みたいな";
	mes "消え方だったの……。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "やっぱりこれ、真珠とは違う何かね。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "でも、どうしてこれを";
	mes "モンスターが持ってたの？";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "さすがにそれはミンミンでも";
	mes "わからないでしょ。";
	next;
	menu "この洞窟と関係がありそう",-;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes strcharinfo(0)+"。";
	mes "あなた、鋭いじゃない。";
	next;
	mes "[ミンミン]";
	mes "あのモンスターが持っていたことや";
	mes "消え方もあのモンスターと";
	mes "類似点があるところから";
	mes "きっと、何か意味があるはずよ。";
	next;
	mes "[ミンミン]";
	mes "この真珠の事も";
	mes "調べてみる必要がありそうね。";
	close2;
	if(!(checkquest(116522) & 0x8)) {
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		setquest 116522;
		compquest 116522;
	}
	cutin "min01.bmp", 255;
	end;
}

jtb_01.gat,133,106,0	script	6番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：キノコのお味は？
//------------------------------------------
jtb_01.gat,206,107,5	script	ミンミン#07	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あら、"+strcharinfo(0)+"。";
	next;
	menu "こんにちは",-;
	mes "[ミンミン]";
	mes "ここ、初めて見た時は";
	mes "森かと思ったけど……";
	mes "洞窟のような気もするわね。";
	next;
	menu "地形を調査中ですか？",-;
	mes "[ミンミン]";
	mes "私こう見えて割りと植物とか";
	mes "地形には詳しいのよ。";
	next;
	mes "[ミンミン]";
	mes "でも、ここの植物や土は";
	mes "初めてみるものばかりね……";
	mes "最初は腐葉土かと思ったのに。";
	mes "何度確認しても、変ね。";
	next;
	menu "変……？",-;
	mes "[ミンミン]";
	mes "そうね、例えるなら想像で描いた";
	mes "絵のような植物と土だわ……。";
	mes "こうなったら……。";
	next;
	mes "‐ミンミンは傍に生えていた";
	mes "　キノコを採取した‐";
	next;
	mes "[ミンミン]";
	mes "見たところどう思う？";
	next;
	switch(select("美味しそう","美味しくなさそう")) {
	case 1:
		mes "[ミンミン]";
		mes "そうね。毒キノコ特有の";
		mes "派手さもないし……";
		mes "多分食べても大丈夫だと思うわ。";
		break;
	case 2:
		mes "[ミンミン]";
		mes "あら、そうかしら。";
		mes "案外美味しいかもよ？";
		break;
	}
	mes "そういうことで……。";
	next;
	mes "[ミンミン]";
	mes "はい、食べて。";
	next;
	menu "え!?",-;
	cutin "min03.bmp", 2;
	mes "[ミンミン]";
	mes "こんな機会、滅多にないわよ？";
	next;
	switch(select("断る","食べてみる")) {
	case 1:
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら、私って信用ないのかしら？";
		next;
		mes "[ミンミン]";
		mes "大丈夫よ、";
		mes "何かあったら私が助けてあげるわ。";
		next;
		mes "[ミンミン]";
		mes "逆に、私に何かあったときに";
		mes "助けてくれる自信があるなら";
		mes "私が食べるけど？";
		next;
		cutin "min01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "（あまり食べる気はしないが、";
		mes "今より仲良くなる";
		mes "チャンスかもしれない……。）";
		next;
		menu "いただきます",-;
		mes "["+strcharinfo(0)+"]";
		mes "（……味が全くしない。";
		mes "味がなくなったバブルガムを";
		mes "食べているようだ……。）";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "なるほど。";
		mes "やっぱり毒とかはないみたいね。";
		mes "私も食べてみようかしら。";
		next;
		mes "[ミンミン]";
		mes "……もぐもぐ。";
		mes "毒だの何だの言う以前に、";
		mes "味がしないわね……。";
		next;
		mes "[ミンミン]";
		mes "でも食料が尽きたらとりあえず、";
		mes "このキノコは食べても大丈夫そうね。";
		break;
	case 2:
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "さすがね。はい、食べてみて。";
		next;
		cutin "min01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "（この味は……。）";
		next;
		mes "‐すごく渋くて、お世辞にも";
		mes "　美味しいとは言えない味だった‐";
		next;
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "え？　そんなに渋いの？";
		next;
		mes "[ミンミン]";
		mes "食べてみる価値はありそうね。";
		next;
		mes "[ミンミン]";
		mes "……もぐもぐ。";
		mes "これは……苦味成分が多く";
		mes "含まれているようね。";
		next;
		mes "[ミンミン]";
		mes "味はどんぐりに近いかしら。";
		break;
	}
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "助かったわ、ありがとう。";
	next;
	mes "[ミンミン]";
	mes "あなたの事も何となく分かったし、";
	mes "何よりこのキノコについて";
	mes "分かったのが大きいわ。";
	next;
	menu "もしかして試された？",-;
	cutin "min03.bmp", 2;
	mes "[ミンミン]";
	mes "さて、どうかしら？";
	next;
	mes "[ミンミン]";
	mes "でもこれだけは言っておくわ。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "私、あなたみたいな人は";
	mes "嫌いじゃないわよ。";
	next;
	mes "[ミンミン]";
	mes "それじゃあね。";
	next;
	cutin "min01.bmp", 255;
	mes "‐ミンミンとの距離がなんとなく";
	mes "　近くなった気がする‐";
	close2;
	if(!(checkquest(116523) & 0x8)) {
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		setquest 116523;
		compquest 116523;
	}
	end;

}

jtb_01.gat,209,133,0	script	7番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：交わされた契約
//------------------------------------------
jtb_01.gat,290,114,4	script	メロディージャック#08	844,{
	mes "[メロディージャック]";
	mes "契約の内容が気になるか？";
	mes "……まぁ、そのうちわかるかもな。";
	close;
}

jtb_01.gat,285,114,5	script	ニュオーズ#08	625,{
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "あれ？　何故かな。";
	mes "気づけばまた一人だよ。";
	next;
	menu "声をかける",-;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "あ、"+strcharinfo(0)+"！";
	mes "良かった～、一人じゃなかった！";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "……ニュオーズ。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "何故かな。";
	mes "どこからか私を呼ぶ声が……。";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "……私はつっこまんぞ。";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "やだなあ、ジャック。";
	mes "それがすでにツッコミだよ？";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "それはさておき。";
	mes "少し話がしたい。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "珍しいね～！";
	mes "私に何か用なのかい？";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "お前と交わした、例の契約の話だ。";
	next;
	menu "席をはずそうか？",-;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "ああ。いいよ、気にしないで。";
	mes "どうせ知られても問題ないし♪";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "お前が気にしないなら、";
	mes "続けるとしよう。";
	next;
	mes "[メロディージャック]";
	mes "それで本題だが……";
	mes "お前がギルドに復帰した時点で、";
	mes "契約は完了した。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "あ、そうだね。";
	mes "でも、そもそも私が";
	mes "ギルドマスターじゃなくなった時点で、";
	mes "契約終了になるんだね。";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "そうだな。";
	mes "しかし、今は状況が状況だ。";
	mes "例の約束は守る。";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "さすが、ジャック♪";
	mes "とはいえまさか、保険として交わした";
	mes "約束が役に立つとはねえ……。";
	mes "本当に何が役に立つか";
	mes "分からないよね～！";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "勘違いするな。";
	mes "お前とは今後も取引があるのと、";
	mes "アレをお前から貰うためだ。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "え、まさかジャック……！";
	mes "私が後生大事に持っている";
	mes "タヌキ人形がほしいのかい？";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "そんな物をもらったところで";
	mes "どうしろと……。";
	next;
	switch(select("1人の時寂しくない","抱いて寝るとか")) {
	case 1:
		mes "[メロディージャック]";
		mes "私が信じているのは、私自身。";
		mes "寂しいと感じたことはない。";
		mes "だから人形は必要ないな。";
		break;
	case 2:
		mes "[メロディージャック]";
		mes "寝るといってもここ何年かは";
		mes "ベットで寝た記憶がないがな……。";
		break;
	}
	next;
	mes "[メロディージャック]";
	mes "とにかく……契約は終了したが";
	mes "約束は守る。";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "わかったよ、ジャック。ありがとう♪";
	mes "改めて……よろしくね。";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "……最後に老婆心ながら言うが、";
	mes "あの少女と関わるのは";
	mes "止めたほうがいい。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "……。";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "あの少女からは別の意味で";
	mes "懐かしい力を感じる。";
	next;
	mes "[メロディージャック]";
	mes "そうあれは魔の力……。";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "あれー？";
	mes "昔、習わなかった？";
	mes "疑わしきは悪とせずってね♪";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "それはお前の持論だろう。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "とにかく大丈夫！";
	mes "私を信じてよ、ジャック♪";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "だといいんだがな……。";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "さ、暗い話はおしまいにして";
	mes "先に進むよー！";
	next;
	cutin "nines03.bmp", 255;
	mes "[メロディージャック]";
	mes strcharinfo(0)+"。";
	next;
	mes "‐歩き出そうとすると、";
	mes "　メロディージャックが";
	mes "　声をかけてきた‐";
	next;
	mes "[メロディージャック]";
	mes "……私が居ない時に何かあったら";
	mes "そのときは頼む。";
	next;
	mes "‐ジャックの言葉にうなずいたものの、";
	mes "　少し複雑な気持ちになった‐";
	close2;
	if(!(checkquest(116524) & 0x8)) {
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		setquest 116524;
		compquest 116524;
	}
	end;
}

jtb_01.gat,307,122,0	script	8番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：シャルロシーの行方
//------------------------------------------
jtb_01.gat,31,197,5	script	メロディージャック#10	844,{
}

jtb_01.gat,25,196,5	script	アイグ#10	646,{
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "こんなにたくさん集まったの。";
	mes "このままみんな集まればいいの！";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

jtb_01.gat,27,194,5	script	ラギ#10	647,{
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "ミルクのにおい、お菓子のにおい。";
	mes "子供なら飛びつくでしょうね。";
	close2;
	cutin "ragi01.bmp", 255;
	end;
}

jtb_01.gat,28,197,4	script	アラン#10	644,{
	cutin "arang02.bmp", 2;
	mes "[アラン]";
	mes "格好良いモンスター出ておいで～♪";
	mes "怖いモンスターはノーサンキュー！";
	close2;
	cutin "arang02.bmp", 255;
	end;
}

jtb_01.gat,29,194,4	script	ロテルト#10	630,{
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "いい加減、この風景も見飽きたな。";
	mes "さっさと出口を見つけるぞ。";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

jtb_01.gat,23,200,5	script	ミンミン#10	643,{
	cutin "min02.bmp", 0;
	mes "[ミンミン]";
	mes "この生臭さ……";
	mes "どこかで嗅いだ気がするわ。";
	close2;
	cutin "min02.bmp", 255;
	end;
}

jtb_01.gat,26,201,4	script	ニュオーズ#10	625,{
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "あれ？　洞窟の雰囲気が変わったね。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "周囲のにおいが変わった気がするわね。";
	mes "……むしろにおいが弱まったのかしら。";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "なんだか甘いミルクや";
	mes "お菓子のようなにおいでしたよね。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あら、私には少し生臭い";
	mes "においに感じたわね。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "見た目はなにも変わってないよな？";
	mes "流石にこの風景にも飽きてきたぜ……。";
	next;
	cutin "rote01.bmp", 255;
	mes "[メロディージャック]";
	mes "そうだろうな。";
	mes "なんと言ってもお前達は、";
	mes "同じ場所を何度も";
	mes "行き来しているからな。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "やっぱりね。";
	mes "狭い空間というわけでもないけど、";
	mes "そこまで凄く広いという";
	mes "わけでもなさそうだし。";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "ということはこれ以上の探索は、";
	mes "無意味なのでしょうかねぇ？";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "どうかしらね。";
	mes "ただ一ついえるとすれば、";
	mes "周辺が何らかの理由で";
	mes "変化しているのは間違いないわ。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "何かの視線を感じるのと、";
	mes "関係があるのかもな。";
	next;
	menu "ロテルトも？",-;
	mes "[ロテルト]";
	mes "何だ、お前も妙な視線を感じるのか。";
	next;
	cutin "arang02.bmp", 2;
	mes "[アラン]";
	mes "実はここは誰かの実験室で、";
	mes "閉じ込められた人間の反応によって";
	mes "変化や影響が……とか！";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "アラン……お前、";
	mes "ゲルカにかなり影響されてないか？";
	next;
	cutin "arang03.bmp", 2;
	mes "[アラン]";
	mes "えへへ！　ゲルカにこの前借りた本が";
	mes "そんな内容だったんだよね！";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ところで気のせいかな？";
	mes "私には景色が徐々に";
	mes "霞んできているように";
	mes "感じるんだよ。";
	next;
	cutin "nines01.bmp", 255;
	mes "[メロディージャック]";
	mes "対して、何かの気は";
	mes "徐々に強くなってきているようだ。";
	next;
	cutin "arang02.bmp", 2;
	mes "[アラン]";
	mes "何かってモンスター!?";
	mes "格好良いモンスターならいいなっ！";
	mes "わくわくっ♪";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "でも、強いモンスターは";
	mes "ちょっと怖いかも……。";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "アラン、それよりもっと";
	mes "おっかないものがありますよぉ。";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "え、なになになになに!?";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "ズバリ!!　お金です。";
	mes "お金はおっかね～ってね！";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "やるね、ラギ君♪";
	mes "なら私は……。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "アラン、モンスターより";
	mes "こいつらを先に倒せ。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "まったく……";
	mes "ニュオーズとラギが揃うと、";
	mes "緊張感がなくなるわね。";
	next;
	cutin "igu05.bmp", 2;
	mes "[アイグ]";
	mes "あれ……。";
	next;
	menu "どうかした？",-;
	mes "[アイグ]";
	mes "みんな！　あの子が……";
	mes "シャルロシーが居ないの!!";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "え？　シャルロシーなら";
	mes "その辺りに……いないね。";
	mes "ロテが隠したのかな？";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "……おい。";
	next;
	cutin "ragi02.bmp", 2;
	mes "[ラギ]";
	mes "黄金と濡羽色の輝きをもつ幼き姫君～♪";
	mes "貴女はいずこに消えたのか～♪";
	next;
	cutin "arang01.bmp", 2;
	mes "[アラン]";
	mes "ラギ、歌ってないで探さないと!!";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "シャルロシーは歌が";
	mes "好きみたいですからねぇ。";
	mes "歌を歌えば、ひょっこり";
	mes "出てくるかと思ったんですよぉ。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "そういえば、あの子……";
	mes "好きだっていう割に歌を聞いても、";
	mes "笑顔の一つも浮かべないのが";
	mes "不思議なのよね。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "多分だけど……";
	mes "どうやって笑えばいいか";
	mes "分からないんじゃないかな。";
	next;
	mes "[ニュオーズ]";
	mes "心の底から笑ったことがない。";
	mes "だから、笑い方がわからない。";
	mes "私にはそう見えたんだ。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "……あの子も早く、";
	mes "笑えるようになれるといいな……なの。";
	next;
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "そのためにも、僕やニュオーズ様が";
	mes "頑張らないといけませんねぇ。";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "そうだね、ラギ君♪";
	mes "それじゃあ、早速！";
	mes "先ずは寒いジョークから……。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "……お前ら、置いて行くぞ。";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "冗談だってば～！";
	mes "待ってよ、ロテー!!";
	close2;
	if(!(checkquest(116525) & 0x8)) {
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 1000000,0,1;
		setquest 116525;
		compquest 116525;
	}
	cutin "nines01.bmp", 255;
	end;
}

jtb_01.gat,49,196,0	script	10番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：不穏な一言
//------------------------------------------
jtb_01.gat,106,198,5	script	ロエル#11	10040,{
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "みなさんは無事でしょうか……。";
	mes "早く見つけて合流した方が";
	mes "良さそうですね。";
	close2;
	cutin "roel01.bmp", 255;
	end;
}

jtb_01.gat,110,197,4	script	アイグ#11	646,{
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "あの子はどこに行っちゃったの……？";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

jtb_01.gat,110,200,4	script	ルナイン#11	10039,{
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "霧が晴れたわね。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "相変わらずあちらこちらに皆さん、";
	mes "散り散りになっているようですね。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "手をつないでここまで来たのに……";
	mes "シャルロシーがいないの……。";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "え、居なくなった!?";
	mes "もう!!　あの子、";
	mes "迷子になりすぎじゃない!?";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "って……シャルロシーって、";
	mes "あの子の名前なの？";
	next;
	menu "ニュオーズが聞いたら答えた",-;
	mes "[ルナイン]";
	mes "あんなに名前をきいても";
	mes "教えてくれなかったのに……！";
	next;
	mes "[ルナイン]";
	mes "これだからニュオーズ様に";
	mes "近づく女は、嫌いなのよ！";
	next;
	mes "[ルナイン]";
	mes "そんな女はみんな、";
	mes "リバースオーキッシュに";
	mes "かかればいいのに!!";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "あはは……落ち着いてなの、";
	mes "ルナイン。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "そういえば……";
	mes "あ、やっぱりやめておきます。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "どうかしたの？　ロエル。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "いえ……なんだかモンスターの数が";
	mes "増えている気がして……。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "それはないと思うの。";
	mes "みんな頑張って戦っているはずなの。";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "そんなんだから、";
	mes "バカロエルって呼ばれるのよ。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "……で、ですよね！";
	mes "すいませんっ!!";
	next;
	menu "気のせいじゃないかも",-;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes strcharinfo(0)+"まで";
	mes "ロエルのバカがうつったの？";
	next;
	menu "ジャックが何かいってなかった？",-;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "そういえば、ジャックが言ってたの。";
	next;
	mes "[アイグ]";
	mes "何かの気が徐々に";
	mes "強くなってきているって……。";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "……。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "……。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "……。";
	next;
	menu "急いで合流した方が良い",-;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "そうですね、";
	mes "それは間違いありません!!";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "さっさとニュオーズ様を探して";
	mes "みんなで脱出するわよ!!";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "うん、みんなと一緒に";
	mes "あの子もきっとみつけるの!!";
	close2;
	if(!(checkquest(116526) & 0x8)) {
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 1000000,0,1;
		setquest 116526;
		compquest 116526;
	}
	cutin "igu01.bmp", 255;
	end;
}

jtb_01.gat,133,197,0	script	11番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：不思議な共通点
//------------------------------------------
jtb_01.gat,282,194,5	script	ロエル#13	10040,{
	cutin "roel02.bmp", 2;
	mes "[ロエル]";
	mes "ゲルカさんはいつも僕の模擬戦に";
	mes "付き合ってくれるんです！";
	next;
	mes "[ロエル]";
	mes "僕は今回が初めての実戦なので";
	mes "足手まといにならないよう、";
	mes "頑張ります！";
	close2;
	cutin "roel02.bmp", 255;
	end;
}

jtb_01.gat,286,194,4	script	ゲルカ#13	629,{
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "てぇーいっ!!";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "オートガード!!";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "……ふぅ。";
	mes "さすがロエル君！";
	mes "凄い防御力ですね！";
	next;
	cutin "roel02.bmp", 2;
	mes "[ロエル]";
	mes "ゲルカさんもお見事です。";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "おや、"+strcharinfo(0)+"さん。";
	mes "夢中で気づきませんでしたよ！";
	mes "私たちの模擬戦どうでした？";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "シャルロシーちゃんも……";
	mes "って、あれ？";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "……おや？";
	mes "シャルロシーはどこに？";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "さっきまで私たちの模擬戦を";
	mes "見ていた気がしたんですが……。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "また迷子になったんでしょうか!?";
	mes "早く探しに行かないと……!!";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "実はそれが敵の狙いだったり……。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "……。";
	next;
	cutin "gelca02.bmp", 2;
	mes "[ゲルカ]";
	mes "そういう展開の本を、";
	mes "最近読んだんです……。";
	next;
	menu "自分が探してくる",-;
	cutin "gelca04.bmp", 2;
	mes "[ゲルカ]";
	mes "待ってください!!";
	mes "そういうのが後々、大惨事に……。";
	next;
	cutin "roel04.bmp", 2;
	mes "[ロエル]";
	mes "うぅ……";
	mes "それ以上怖い事を言うのは";
	mes "やめましょう！";
	next;
	cutin "gelca04.bmp", 2;
	mes "[ゲルカ]";
	mes "あ、すいません！";
	mes "とりあえず今は人数も人数ですし";
	mes "下手に動くのはやめましょう。";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "シャルロシーちゃんも";
	mes "戻ってくるかもしれないし。";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "そ、そうですね……。";
	next;
	cutin "gelca03.bmp", 2;
	mes "[ゲルカ]";
	mes "シャルロシーちゃん、";
	mes "特徴的だから見つかりやすくて";
	mes "いいですよね。";
	next;
	cutin "gelca03.bmp", 255;
	mes "‐確かにシャルロシーは特徴的だ。";
	mes "　その中でも……。‐";
	next;
	switch(select("髪型が気になる","瞳が気になる","服装が気になる")) {
	case 1:
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "そういえば……前髪は黒で、";
		mes "後ろは金色ですね。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "結構、お洒落に拘りが";
		mes "あるんでしょうか？";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "服装も可愛らしいですもんね、";
		mes "シャルロシーちゃん♪";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "もしかしたら良い家柄の";
		mes "娘さんなのかもしれませんね！";
		next;
		cutin "roel01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "（あの髪の色、";
		mes "どこかで見たような……。）";
		next;
		break;
	case 2:
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "オッドアイってやつですよね！";
		mes "本で読んだことがあります。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "オッドアイというと……。";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "左右の眼で色が異なる";
		mes "瞳のことです！";
		next;
		cutin "roel02.bmp", 2;
		mes "[ロエル]";
		mes "なるほど！";
		mes "格好良いなぁ！　オッドアイ。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "オッドアイって珍しいだけに";
		mes "印象に残りますよね。";
		next;
		cutin "gelca01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "（あの瞳の色、";
		mes "どこかで見たような……。）";
		next;
		break;
	case 3:
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "あの服装、変わってますよね。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "何ていうファッション";
		mes "なんでしょうね？";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "あれは、ゴシック・アンド・ロリータ";
		mes "というファッションです！";
		mes "ゴスロリとも呼ばれていますね。";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "ゴスロリ……！";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "難点は戦いにくいことですよね。";
		mes "あんなにヒラヒラしてたら";
		mes "踏んじゃいそうです!!";
		next;
		cutin "roel01.bmp", 2;
		mes "[ロエル]";
		mes "（あの服装、ルナインさんにも";
		mes "似合いそうだなあ……！）";
		next;
		cutin "gelca01.bmp", 255;
		mes "["+strcharinfo(0)+"]";
		mes "（あの服装には、何か";
		mes "意味があるんだろうか……。）";
		next;
		break;
	}
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "しかし……シャルロシー、";
	mes "戻ってきませんね。";
	next;
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "仕方ありませんね。";
	mes "みんなで探しに行きましょう!!";
	next;
	cutin "roel01.bmp", 2;
	mes "[ロエル]";
	mes "そうですね。";
	mes "いつまでもここに居ても";
	mes "仕方ないですし……。";
	close2;
	if(!(checkquest(116527) & 0x8)) {
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 1000000,0,1;
		setquest 116527;
		compquest 116527;
	}
	cutin "roel01.bmp", 255;
	end;
}

jtb_01.gat,307,195,0	script	13番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：仲間以上恋愛未満？
//------------------------------------------
jtb_01.gat,30,279,4	script	アイグ#15	646,{
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "今は恋とかよりも、";
	mes "みんなと一緒にいれる方が";
	mes "嬉しいし、好きなの♪";
	close2;
	cutin "igu01.bmp", 255;
	end;
}

jtb_01.gat,28,279,3	script	シャルロシー#15	10041,{
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "……恋愛。";
	mes "よくわからない……。";
	mes "……恋愛っておいしい？";
	close2;
	cutin "shaloshi01.bmp", 255;
	end;
}

jtb_01.gat,29,283,4	script	ルナイン#15	10039,{
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "ねえ、アイグ。";
	next;
	cutin "igu01.bmp", 2;
	mes "[アイグ]";
	mes "なあに？　ルナイン。";
	next;
	mes "[アイグ]";
	mes "あ、シャルロシー。";
	mes "髪をすくから、少し動かないでね。";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "……動かない。";
	next;
	cutin "igu02.bmp", 2;
	mes "[アイグ]";
	mes "うん♪";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "ニュオーズ様ってあれ？";
	mes "ポリン系男子ってやつ？";
	next;
	menu "ポリン系男子？",-;
	mes "[ルナイン]";
	mes "び、びっくりした！";
	mes strcharinfo(0)+"、いたのね。";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "ポリン系男子ってのは、";
	mes "ポリンみたいに無害なくせに";
	mes "興味あるものはすぐに飛びつく";
	mes "男性のことよ。";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "ルナインはニュオーズと";
	mes "今日が初対面だったと思うけど、";
	mes "やっぱり気づいたみたいなの。";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "ミンミンいわく、ニュオーズは";
	mes "冒険一筋らしいの。";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "やっぱりかぁ……。";
	next;
	cutin "lunain03.bmp", 2;
	mes "[ルナイン]";
	mes "ニュオーズ様が";
	mes "冒険にしか興味ないとか";
	mes "認めたくないけど、";
	mes "そんな感じよね。";
	mes "はぁ……。";
	next;
	menu "ニュオーズが好きなの？",-;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "……。";
	next;
	cutin "igu03.bmp", 2;
	mes "[アイグ]";
	mes "……ルナイン、顔が赤いの。";
	next;
	cutin "lunain04.bmp", 2;
	mes "[ルナイン]";
	mes "……す、好きとかじゃなくて!!";
	mes "ちょ、ちょっと顔と性格が";
	mes "タイプっていうか……。";
	next;
	cutin "igu02.bmp", 2;
	mes "[アイグ]";
	mes "ルナインってニュオーズみたいな人が";
	mes "好みなんだね♪";
	next;
	menu "ところでロエルは？",-;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "ロエルはタイプじゃないのかってこと？";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "うんうん。ロエルとルナイン、";
	mes "すごく仲よさそうだったけど。";
	next;
	cutin "lunain03.bmp", 2;
	mes "[ルナイン]";
	mes "ただのお子ちゃまに、";
	mes "興味はありません。";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "……ロエルはお子ちゃま。";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "シャルロシーが変なこと";
	mes "覚えちゃったの!!";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "事実だし。";
	mes "ところでアイグも";
	mes "気になってるんじゃないの？";
	mes "ニュオーズ様のこと。";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "なの？";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "あれ？　違うの？";
	next;
	cutin "igu04.bmp", 2;
	mes "[アイグ]";
	mes "ニュオーズのことは";
	mes "確かに好きなの♪";
	next;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "でしょ？";
	next;
	cutin "igu02.bmp", 2;
	mes "[アイグ]";
	mes "でもでも、みんなも同じくらい";
	mes "好きなの♪";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "……私もみんな好き。";
	next;
	cutin "lunain02.bmp", 2;
	mes "[ルナイン]";
	mes "わ、私も……今のみんなは……";
	mes "嫌いじゃないわ。";
	next;
	cutin "igu02.bmp", 2;
	mes "[アイグ]";
	mes "二人ともありがとうなの♪";
	mes "私も大好きなの♪";
	next;
	cutin "igu02.bmp", 255;
	menu "誰も恋愛経験はないと……",-;
	cutin "lunain01.bmp", 2;
	mes "[ルナイン]";
	mes "あら、"+strcharinfo(0)+"。";
	mes "偉そうに言っているけど";
	mes "あなたはどうなのよ？";
	next;
	cutin "igu03.bmp", 2;
	mes "[アイグ]";
	mes "え、"+strcharinfo(0)+"は";
	mes "恋愛経験あるの!?";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "……じーっ。";
	next;
	cutin "shaloshi02.bmp", 255;
	mes "["+strcharinfo(0)+"]";
	mes "えーっと……。";
	next;
	if(select("あ、ニュオーズ！","語ると長いよ？") == 1) {
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "ニュオーズ様!?";
		next;
		cutin "igu03.bmp", 2;
		mes "[アイグ]";
		mes "え、ニュオーズ？";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……"+strcharinfo(0)+"は";
		mes "逃げだした。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "どこで覚えたのよ、";
		mes "そんな言葉……。";
	} else {
		cutin "igu03.bmp", 2;
		mes "[アイグ]";
		mes "そんなに凄い内容なの!?";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "べ、別に気になるわけじゃ";
		mes "ないんだから!!";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……ルナイン、興味津々。";
		next;
		cutin "shaloshi02.bmp", 255;
		mes "‐3人に話してみた‐";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "ふぇぇ……。";
		next;
		cutin "lunain02.bmp", 2;
		mes "[ルナイン]";
		mes "……。";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……よくわからない。";
		next;
		cutin "shaloshi02.bmp", 255;
		mes "‐アイグはわたわたと慌て、";
		mes "　ルナインは固まっており、";
		mes "　シャルロシーは変わらず‐";
		next;
		mes "‐この3人に恋愛話は";
		mes "　まだ早かったようだ……‐";
	}
	close2;
	if(!(checkquest(116528) & 0x8)) {
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 1000000,0,1;
		setquest 116528;
		compquest 116528;
	}
	cutin "shaloshi02.bmp", 255;
	end;
}

jtb_01.gat,47,302,0	script	15番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：見えない絆
//------------------------------------------
jtb_01.gat,113,285,4	script	ミンミン#16	643,{
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "たまには昔を思い出して語るのも";
	mes "悪くないわね。";
	close2;
	cutin "min01.bmp", 255;
	end;
}

jtb_01.gat,108,285,5	script	ロテルト#16	630,{
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "ニュオーズが";
	mes "すぐフラフラどこかに行くせいで";
	mes "ギルドをまとめるのが大変だ。";
	close2;
	cutin "rote01.bmp", 255;
	end;
}

jtb_01.gat,110,281,5	script	ニュオーズ#16	625,{
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "ひさしぶりに3人揃ったね。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "久しぶりなのは、誰かが";
	mes "何も言わずに出て行くせいだけどな!?";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "男のヒステリーは醜いわよ。";
	mes "ほどほどになさいな。";
	mes "それとも嫉妬かしら。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "嫉妬じゃねえ！";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あら、ロテルトが嫉妬深いのは";
	mes "昔からじゃない。";
	next;
	menu "3人は昔からの知りあいなの？",-;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "あら、"+strcharinfo(0)+"。";
	mes "言ってなかった？";
	mes "不本意ながら事実なのよね。";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "私とロテで";
	mes "昔はよく競い合ったよね～！";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "プロンテラの南門近くで";
	mes "花を売ってる女の子に、";
	mes "どちらが先に告白して";
	mes "OK貰うか競ったアレ？";
	next;
	cutin "min03.bmp", 2;
	mes "[ミンミン]";
	mes "それともニュオーズが";
	mes "寒いジョーク大会開いて、";
	mes "まさかのロテルトが";
	mes "一番寒いジョークをつぶやいた";
	mes "アレのこと？";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "なんでお前は";
	mes "そんなに詳しく覚えてるんだよ!?";
	next;
	cutin "nines02.bmp", 2;
	mes "[ニュオーズ]";
	mes "後にも先にも、";
	mes "ロテの寒いジョークが聞けたのは";
	mes "あの一回だけだったね～！";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "や、やめろっ!!";
	mes "それ以上は言うなっ!!";
	next;
	cutin "min03.bmp", 2;
	mes "[ミンミン]";
	mes "後は……古木の枝で遊んでる時に";
	mes "気絶した話とか？";
	mes "セージのなんとかって子を呼んで";
	mes "アブラカタブラで遊んでいたら、";
	mes "モンスターが大暴れして";
	mes "怒られたこともあったわね。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "でもそのお陰で";
	mes "大量のモンスターの対処法も知ったし、";
	mes "3人の連携も生まれたから";
	mes "無駄じゃなかったよ。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "そうね。";
	mes "でもそう考えると、あの新人くん達を";
	mes "もう少し鍛えてあげないとだめね。";
	next;
	cutin "min02.bmp", 2;
	mes "[ミンミン]";
	mes "今の状態じゃ、";
	mes "いざって時に緊張感がなさすぎて";
	mes "大惨事になりかねないわよ。";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "……ああ。";
	mes "それにあいつらに、俺のような苦労を";
	mes "味合わせたくないしな。";
	next;
	menu "苦労？",-;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "……。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "え？　ロテのいう苦労って……";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "聖水が必要だけど";
	mes "空きビンもZenyもないから、";
	mes "ロッダフロッグを倒して";
	mes "空きビンを集めるって、";
	mes "大量にロッダフロッグを集めて";
	mes "鳴き声がうるさすぎるって怒られた事？";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "そうじゃなくて、";
	mes "プロンテラ南門前で鹿の角と";
	mes "スピングラスをつけて遊んでた時に、";
	mes "衛兵に南門の地獄の鹿なんて";
	mes "変なあだ名をつけられて";
	mes "しばらく笑いものにされた事でしょう？";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "どっちも違うだろ!!";
	next;
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "……昔ちょっと";
	mes "俺の素行が悪かったせいで、";
	mes "ほぼソロで活動するしかなかった時期が";
	mes "あったんだよ。";
	next;
	mes "[ロテルト]";
	mes "1人の力じゃ限界がある。";
	mes "俺はこのギルドに居る誰よりも";
	mes "それを知っている。";
	mes "だからこそ、あいつらには";
	mes "俺みたいになってほしくないんだ。";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "まーたはじまった。";
	mes "本当、ロテルトは昔から";
	mes "心配しすぎなところがあるのよね。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "そうそう。";
	mes "ロテは昔みたいにもう一人じゃない。";
	mes "私たちも居るし、それに……";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "今だってほら、";
	mes strcharinfo(0)+"や、";
	mes "ギルドのみんなもいるんだから♪";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "……フンッ。";
	mes "だからこそあいつらを鍛えて、";
	mes "これからもこきつかうつもりだ!!";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "ほーんと、素直じゃないわね。";
	next;
	cutin "nines01.bmp", 2;
	mes "[ニュオーズ]";
	mes "ロテは恥ずかしがり屋さんだからね！";
	mes "さっ、そろそろ行こう♪";
	mes "私たちの大事な仲間を探しに。";
	next;
	cutin "rote01.bmp", 2;
	mes "[ロテルト]";
	mes "ニュオーズ！　お前が仕切るなっ！";
	next;
	cutin "min01.bmp", 2;
	mes "[ミンミン]";
	mes "はいはい。";
	mes "バカな男共は放っておいて行くわよ、";
	mes strcharinfo(0)+"。";
	next;
	cutin "nines03.bmp", 2;
	mes "[ニュオーズ]";
	mes "あ、もちろん";
	mes strcharinfo(0)+"も";
	mes "私達の大事な仲間だよ～♪";
	next;
	cutin "rote04.bmp", 2;
	mes "[ロテルト]";
	mes "フン。まったくだ。";
	mes "ここまで俺達に付き合ったんだ。";
	mes "簡単に途中退場はさせねえよ、";
	mes strcharinfo(0)+"。";
	close2;
	if(!(checkquest(116529) & 0x8)) {
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 1000000,0,1;
		setquest 116529;
		compquest 116529;
	}
	cutin "rote04.bmp", 255;
	end;
}

jtb_01.gat,134,275,0	script	16番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 外伝：？？？
//------------------------------------------
jtb_01.gat,30,377,3	script	ペル#18	10047,{
	mes "[ペル]";
	mes "ペルペル。";
	next;
	switch(select("ペル!!","ペルー？","ぺろぺろ")) {
	case 1:
		mes "[ペル]";
		mes "ペルー♪";
		close;
	case 2:
		mes "[ペル]";
		mes "ペル～？　ペルペルル？";
		close;
	case 3:
		mes "[ペル]";
		mes "？";
		mes "ペルペル。";
		mes "ペルル、ペルペル～。";
		next;
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "どうしてペルをなめるの？";
		mes "おいしいの？";
		next;
		cutin "shaloshi02.bmp", 2;
		mes "[シャルロシー]";
		mes "……私もたべてみる……。";
		next;
		cutin "shaloshi02.bmp", 255;
		emotion 19,"ペル#18";
		mes "[ペル]";
		mes "ペル!?";
		mes "ペル～！　ペルぺル!!";
		close;
	}
}

jtb_01.gat,28,378,5	script	シャルロシー#18	10041,{
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes strcharinfo(0)+"……";
	mes "きてくれた、嬉しい。";
	next;
	mes "[シャルロシー]";
	mes strcharinfo(0)+"が";
	mes "私とみんな、仲良くなるように";
	mes "がんばってくれたの知ってる。";
	next;
	mes "[シャルロシー]";
	mes "だからこうして";
	mes "ギルドメンバーになれた。";
	mes "ありがとう。";
	next;
	mes "[シャルロシー]";
	mes "あれからゲルカに本を借りたりして、";
	mes "たくさん言葉覚えた。";
	mes "前より話し方、うまくなったかな……？";
	next;
	if(select("良いと思う","アドバイスする") == 1) {
		mes "[シャルロシー]";
		mes "よかった。";
		mes "でもまだ分からない言葉も多くて……。";
		next;
	} else {
		cutin "shaloshi01.bmp", 2;
		mes "[シャルロシー]";
		mes "……言葉って難しい。";
		mes "どんなふうにすればいい？";
		next;
		switch(select("男っぽさが足りない","萌えが足りない","個性が足りない")) {
		case 1:
			mes "[シャルロシー]";
			mes "男っぽさ？";
			mes "男っぽさっどんな感じだろう……。";
			next;
			if(select("ロテルトみたいな感じ","ジャックみたいな感じ") == 1) {
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ロテみたいな感じ？";
				mes "やってみる……。";
				next;
				mes "[シャルロシー]";
				mes "ああ、お前か……。";
				mes "なんだかんだと";
				mes "お前にも迷惑をかけちまったな。";
				mes "……";
				mes "そ、その……あれだ。";
				mes "……サンキュー……な。";
				next;
			} else {
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "メロディージャックみたいな感じ？";
				mes "えっと……";
				next;
				mes "[シャルロシー]";
				mes "お前にはいろいろと世話になったな。";
				mes "最初はどうなることかと思ったが……";
				mes "私は良い友達をもったものだ。";
				mes "ありがとう。";
				next;
			}
			mes "[シャルロシー]";
			mes "こんなかんじ？";
			mes "男っぽさって、難しい……。";
			next;
			break;
		case 2:
			mes "[シャルロシー]";
			mes "萌え？";
			mes "萌えってどんな感じだろう……。";
			next;
			switch(select("ルナインみたいな感じ","アイグみたいな感じ","ゲルカみたいな感じ","アランみたいな感じ","ミンミンみたいな感じ")) {
			case 1:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ルナインみたいな感じ？";
				mes "えっと……";
				next;
				mes "[シャルロシー]";
				mes "も、もう……!!";
				mes strcharinfo(0)+"の事";
				mes "考えてるタイミングで";
				mes "ちょうどよく来るのよ……。";
				next;
				mes "[シャルロシー]";
				mes "こ、これじゃあ私がいつも";
				mes strcharinfo(0)+"の事";
				mes "考えてるみたいじゃない。";
				mes "べ、別にいつも考えてるわけじゃ";
				mes "ないんだからね！";
				next;
				mes "[シャルロシー]";
				mes "……どう？";
				mes "ルナインの話し方、真似してみた。";
				next;
				break;
			case 2:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "アイグみたいな感じ？";
				mes "わかった。";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"なの♪";
				mes "最近、歌の練習をみんなとしてるの。";
				mes "まだうまく歌えないけど、";
				mes "良かったら今度一緒に歌ってほしいの♪";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"と一緒に";
				mes "歌えたら、すごく楽しいと思うの♪";
				next;
				mes "[シャルロシー]";
				mes "……どう？";
				mes "アイグの話し方、真似してみた。";
				next;
				break;
			case 3:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ゲルカみたいな感じ？";
				mes "えっと……";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"さん！";
				mes strcharinfo(0)+"さんは";
				mes "必殺技とか考えたことありますか？";
				mes "私も必殺技を作りたいと思って、";
				mes "いま色々考えてるんです！";
				next;
				mes "[シャルロシー]";
				mes "良かったら今度、";
				mes "二人で練習しましょう！";
				mes "アドバイスしてくださいね！";
				next;
				mes "[シャルロシー]";
				mes "……どう？";
				mes "ゲルカの話し方、真似してみた。";
				next;
				break;
			case 4:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "アランみたいな感じ？";
				mes "やってみる。";
				next;
				mes "[シャルロシー]";
				mes "実はいま、料理の練習もしてるんだよ。";
				mes "私は別に、食べ物を食べなくても";
				mes "平気なんだけどね！";
				mes "おいしい食べ物を食べると、";
				mes "みんな幸せな気持ちになるんだって。";
				next;
				mes "[シャルロシー]";
				mes "だから頑張って練習してるんだ！";
				mes "じょうずにできたら、";
				mes strcharinfo(0)+"にも";
				mes "ごちそうするね！";
				next;
				mes "[シャルロシー]";
				mes "……どう？";
				mes "アランの話し方、真似してみた。";
				next;
				break;
			case 5:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ミンミンみたいな感じ？";
				mes "こうかな……";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"じゃない。";
				mes "今日はどうしたの？";
				mes "あら、なんだか疲れてるみたいね。";
				mes "ちょっとお姉さんが";
				mes "肩でも揉んであげましょうか？";
				next;
				mes "[シャルロシー]";
				mes "こう見えて私、";
				mes "マッサージとか得意なのよね。";
				mes "本で読んでペルと練習したのよ。";
				mes "さあ、ちょっとそこに座りなさいな。";
				next;
				mes "[シャルロシー]";
				mes "……どう？";
				mes "ミンミンの話し方、真似してみた。";
				next;
				break;
			}
			break;
		case 3:
			mes "[シャルロシー]";
			mes "個性？";
			mes "個性ってどんな感じだろう……。";
			next;
			switch(select("ニュオーズみたいな感じ","ラギみたいな感じ","ロエルみたいな感じ")) {
			case 1:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ニュオーズみたいな感じ……";
				mes "えっと……";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"～！";
				mes "最近、世紀末カプラ伝説って本を";
				mes "読んだんだよ！";
				next;
				mes "[シャルロシー]";
				mes "昔からカプラセンターに伝わる";
				mes "伝説みたいな話なんだって。";
				mes "カプラさんがカッコよくって";
				mes "ドキドキしちゃったよ～!!";
				mes "本物のカプラさんに";
				mes "会いたくなっちゃった♪";
				next;
				break;
			case 2:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ラギみたいな感じ……";
				mes "こうかな……";
				next;
				mes "[シャルロシー]";
				mes "おや、"+strcharinfo(0)+"さん。";
				mes "このあいだ、ペルに真珠を見せたら";
				mes "ペルも欲しがってしまいまして。";
				mes "私があげれないと言うと、ペルは";
				mes "自分の力で真珠を作り出したんですよ。";
				next;
				mes "[シャルロシー]";
				mes "消えてしまう真珠だったんですが、";
				mes "涙のかわりですからねぇ。";
				mes "泣いてたくさん涙を流しても、";
				mes "いつか涙は消えて";
				mes "笑顔になれるって事なんですね。";
				next;
				break;
			case 3:
				cutin "shaloshi02.bmp", 2;
				mes "[シャルロシー]";
				mes "ロエルみたいな感じ……";
				mes "わかった。";
				next;
				mes "[シャルロシー]";
				mes strcharinfo(0)+"さん！";
				mes "お疲れ様です!!　今回の冒険、";
				mes strcharinfo(0)+"さんの";
				mes "お力があったおかげで、";
				mes "素晴らしいものになりました。";
				next;
				mes "[シャルロシー]";
				mes "ギルドのみんなの気持ちも";
				mes "少しだけど、分かった気がします。";
				mes strcharinfo(0)+"さん、";
				mes "本当にありがとうございます!!";
				next;
				break;
			}
			mes "[シャルロシー]";
			mes "こんなかんじ？";
			next;
			break;
		}
	}
	cutin "shaloshi01.bmp", 2;
	mes "[シャルロシー]";
	mes "……。";
	mes "みんなの真似するの";
	mes "難しいし、ちょっと恥ずかしい……";
	next;
	cutin "shaloshi02.bmp", 2;
	mes "[シャルロシー]";
	mes "……。";
	mes "やっぱりいつもの話し方が";
	mes "一番私らしい？";
	mes "……そっか。わかった。";
	next;
	menu "どうして言葉を覚えたいの？",-;
	mes "[シャルロシー]";
	mes "今は外の世界……";
	mes "みんなの所に行くの無理みたい。";
	mes "でもいつか外の世界、行ってみたい。";
	mes "その時のために勉強……。";
	next;
	mes "[シャルロシー]";
	mes "それと、みんなが好きそうな";
	mes "冒険を見つけたらみんなを呼ぶの。";
	mes "手紙っていうものの書き方も";
	mes "ニュオーズに教えてもらった。";
	next;
	mes "[シャルロシー]";
	mes "だからがんばる。";
	mes "たくさん言葉、覚えて";
	mes "手紙を書くの。";
	next;
	cutin "shaloshi04.bmp", 2;
	mes "[シャルロシー]";
	if(!(checkquest(116530) & 0x8)) {
		mes "今度"+strcharinfo(0)+"も";
		mes "言葉を教えて。";
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		getexp 3000000,0,1;
		setquest 116530;
		compquest 116530;
		setquest 201715;
	} else {
		mes strcharinfo(0)+"、";
		mes "また言葉とか色々、教えてね。";
	}
	close2;
	cutin "shaloshi04.bmp", 255;
	end;
}

jtb_01.gat,49,365,0	script	18番部屋出口	45,2,2,{
OnTouch:
	mes "‐外にでますか？‐";
	next;
	if(select("はい","いいえ")==2) {
		mes "‐その場に留まる事にした‐";
		close;
	}
	mes "‐外に出た‐";
	close2;
	warp "moc_para01.gat",30,88;
	end;
}

//==========================================
// 楽園団 (2)
//------------------------------------------
moc_para01.gat,37,95,5	script	ゲルカ#1	629,{
	if(checkquest(117055) & 0x8) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "こんにちは！";
		mes "今日は修行ですか？　冒険ですか？";
		mes "私はまだ決めていなくて……。";
		mes "ところで私に何か";
		mes "ご用でしょうか？";
		next;
		switch(select("師匠について","好きなものについて","師匠から頼まれた")) {
		case 1:
			mes "[ゲルカ]";
			mes "ふふふふふふふふ……。";
			mes strcharinfo(0)+ "さんもとうとう、";
			mes "師匠の素晴らしさというか魅力に";
			mes "気づいてきたようですね！";
			mes "では、もっと師匠の魅力を";
			mes "知っていただきましょう！";
			next;
			mes "[ゲルカ]";
			mes "師匠について、";
			mes "どのお話が聞きたいですか？";
			next;
			switch(select("性格について","ギルドについて","思い出について")) {
			case 1:
				mes "[ゲルカ]";
				mes strcharinfo(0)+ "さん。";
				mes "これ、なんだか分かりますか？";
				next;
				cutin "gelca01.bmp", 255;
				mes "‐手作り感溢れる白い紙に";
				mes "　様々な形の紙がある。";
				mes "　そこにお世辞にもうまいとは";
				mes "　いえないような絵と";
				mes "　いやに丁寧な文字で";
				mes "　何か書かれた紙を";
				mes "　ゲルカが差し出した‐";
				next;
				cutin "gelca02.bmp", 2;
				mes "[ゲルカ]";
				mes "手作り感溢れるこの絵も字も";
				mes "師匠が直接書いたものです。";
				mes "普通の紙では作れないと言って、";
				mes "この紙の材料を探しにあらゆる所を";
				mes "冒険したんですよ。";
				next;
				cutin "gelca02.bmp", 255;
				mes "‐少しの間ゲルカは思い出に浸った後、";
				mes "　その紙に目を落とした‐";
				next;
				cutin "gelca02.bmp", 2;
				mes "[ゲルカ]";
				mes "師匠がここで依頼を一所懸命に";
				mes "頑張ってくれた冒険者に、";
				mes "何かしてやりたいと言って";
				mes "作った賞状みたいなものです。";
				mes "残念ながらこの賞状が";
				mes "活躍する日はまだ先ですけど……。";
				next;
				cutin "gelca01.bmp", 2;
				mes "[ゲルカ]";
				mes "頑張る人を応援したい……";
				mes "師匠はその一心でこれを";
				mes "作ったのだと思います。";
				mes "それゆえにシャルロシーちゃんの";
				mes "ために頑張るみんなを見ていて";
				mes "辛かったのではないかと……。";
				next;
				cutin "gelca03.bmp", 2;
				mes "[ゲルカ]";
				mes "なので、" +strcharinfo(0)+ "さんがあの時";
				mes "居てくれて本当に良かったと";
				mes "今更ながら感謝しています。";
				mes "遅くなりましたけど……";
				mes "本当にあの時は、ありがとう";
				mes "ございました！";
				close2;
				cutin "gelca03.bmp", 255;
				end;
			case 2:
				mes "[ゲルカ]";
				mes "ギルドといえば、シャルロシーちゃんの";
				mes "一件で師匠のことを";
				mes "頑固者の分からず屋だなあと";
				mes "感じたんじゃないですか？";
				mes "正直、師匠のことをよく知る私も";
				mes "少し思ったくらいですから。";
				next;
				cutin "gelca02.bmp", 2;
				mes "[ゲルカ]";
				mes "あの融通のなさはこの楽園団でも";
				mes "有名なんです。";
				mes "でも……";
				mes "ギルドもそうですが、もし誰かに";
				mes "何かがあったとき、責任を取るのは";
				mes "師匠なんです……。";
				next;
				mes "[ゲルカ]";
				mes "だから師匠は仲間に何か";
				mes "問題が起きる可能性がある事柄を";
				mes "簡単に許可することが出来ず";
				mes "あんな風につっけんどんな";
				mes "態度になってしまうんですよね……。";
				next;
				cutin "gelca01.bmp", 2;
				mes "[ゲルカ]";
				mes "本当、面倒な師匠ですけど";
				mes strcharinfo(0)+ "さんのことは気に入って";
				mes "いるみたいなので、今後もどうか";
				mes "この不出来な弟子ともども";
				mes "よろしくお願いします♪";
				close2;
				cutin "gelca01.bmp", 255;
				end;
			case 3:
				mes "[ゲルカ]";
				mes "師匠に前に聞いた話ですが";
				mes "師匠は元々、戦闘系アコライトで";
				mes "有名な悪童だったそうです。";
				next;
				mes "[ゲルカ]";
				mes "今では多くの聖職者たちが武器を持って";
				mes "戦いますけど、当時の聖職者は";
				mes "パーティーで他人を補助する役割を";
				mes "優先するべきだという風潮が強く、";
				mes "戦うくらいなら補助していろと";
				mes "いう方が多かったようですね。";
				next;
				mes "[ゲルカ]";
				mes "なのに師匠は補助よりもむしろ";
				mes "自ら敵に向かっていって、";
				mes "愛用のソードメイスで";
				mes "モンスターを撲滅することを";
				mes "優先する事が多かったようです。";
				next;
				cutin "gelca02.bmp", 2;
				mes "[ゲルカ]";
				mes "他にも、当時お世話になっていた";
				mes "プロンテラ修道院の人の指示にも、";
				mes "耳を貸さなかったり……。";
				mes "そのため、問題児とみなされ、";
				mes "結局その修道院からも";
				mes "追い出され……";
				next;
				mes "[ゲルカ]";
				mes "今でもその修道院の方たちとは、";
				mes "あまり仲が良くありません……。";
				mes "どうも昔の師匠は今に比べて、";
				mes "勝負に対して誰よりも意欲が強い、";
				mes "半人前の冒険者の一人だった";
				mes "ようですね。";
				next;
				mes "[ゲルカ]";
				mes "そんな中^FF0000あの方^000000に出会ったそうです。";
				mes "その方は、プロンテラ南の方で";
				mes "いつも歌っていた方だとか。";
				mes "今は他の人がその場所に";
				mes "いるようですけど……。";
				next;
				cutin "gelca03.bmp", 2;
				mes "[ゲルカ]";
				mes "結局、師匠はその方と出会い、";
				mes "パーティーで協力する意味を";
				mes "いろいろ学ぶことが出来たようです。";
				mes "出会いがきっかけで人は、";
				mes "変わることが出来るんだと、";
				mes "懐かしそうに語ってくれました。";
				next;
				mes "[ゲルカ]";
				mes "誰かははっきり言いませんが、";
				mes strcharinfo(0)+ "さんならそれが誰かは";
				mes "わかりますよね？";
				mes "よくお二人は喧嘩していますけど、";
				mes "喧嘩するほど仲がいいって言葉は、";
				mes "あのお二人にこそ、ぴったりです♪";
				close2;
				cutin "gelca03.bmp", 255;
				end;
			}
		case 2:
			mes "[ゲルカ]";
			mes "私の好きなもの……。";
			mes "それはやっぱりズバリ！";
			mes "修行の敵……";
			next;
			mes "[ゲルカ]";
			mes "甘いデザートです!!";
			mes "甘いケーキ、チョコレート!!";
			mes "冷えたアイスクリームとか、";
			mes "考えただけで最高です!!";
			mes "特に、コモドで師匠と飲んだ";
			mes "天上のフルーツジュース。";
			next;
			mes "[ゲルカ]";
			mes "あの味は今でも忘れません……。";
			mes "今度は" +strcharinfo(0)+ "さんや皆さんとも";
			mes "一緒に行って、あの味を";
			mes "味わってみたいですね。";
			mes "無論、シャルロシーちゃんも";
			mes "絶対一緒に♪";
			close2;
			cutin "gelca03.bmp", 255;
			end;
		case 3:
			mes "[ゲルカ]";
			mes "え！？";
			mes "師匠から私の話し相手に";
			mes "なってくれと頼まれたんですか？";
			mes "そうですか……";
			mes "……。";
			next;
			cutin "gelca03.bmp", 2;
			mes "[ゲルカ]";
			mes "では、筋肉のよさを語る";
			mes "マッスル筋肉トークを解禁するしか";
			mes "ないようですね！";
			mes "きっと聞き終わる頃には絶対、";
			mes "筋肉を見る目が変わるはずです!!";
			mes "今日は思いっきり語りますよ!!";
			next;
			mes "‐この後滅茶苦茶";
			mes "　ゲルカから筋肉について";
			mes "　聞かされた。";
			mes "　";
			mes "　自分の変な知識が";
			mes "　^FF00001上がった^000000……気がする‐";
			emotion 19,"";
			close2;
			cutin "gelca03.bmp", 255;
			end;
		}
	}
	if(JTB_2QUE == 7) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "あ……" +strcharinfo(0)+ "さん！";
		mes "こんにちは。";
		mes "聞いてください！";
		mes "他にも何人かこの学園で";
		mes "働いているのはご存知";
		mes "ですよね？";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "実はそれを聞いて、";
		mes "シャルロシーちゃんもここに、";
		mes "来たがっていたんですけど……";
		mes "流石にそれはダメだって";
		mes "師匠に怒られちゃいました。";
		next;
		mes "[ゲルカ]";
		mes "シャルロシーちゃんならきっと";
		mes "喜びそうなものがここには";
		mes "いっぱいあるんですけど……";
		mes "流石に素性が素性ですしね。";
		mes "でもいつかシャルロシーちゃんを";
		mes "ここに招待しますよ！";
		next;
		cutin "gelca03.bmp", 2;
		mes "[ゲルカ]";
		mes "その時は是非、";
		mes strcharinfo(0)+ "さんも一緒に集まって";
		mes "みんなであの時みたいにまた、";
		mes "冒険の続きに出かけられたら";
		mes "いいですね♪";
		setquest 117055;
		compquest 117055;
		close2;
		cutin "gelca02.bmp", 255;
		end;
	}
	if(checkquest(116508) & 0x8) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "あ……" + strcharinfo(0) + "さん！";
		mes "こんにちは。";
		next;
		cutin "gelca02.bmp", 2;
		mes "[ゲルカ]";
		mes "そうそう、実はですね。";
		mes "あの後、やっぱりこんな結末";
		mes "良くないんじゃないかって話に";
		mes "なったんです……。";
		mes "シャルロシーちゃんだってきっと、";
		mes "本心は違ったはず……。";
		next;
		mes "[ゲルカ]";
		mes "あと、ルナインさんのワープポータルが";
		mes "あの時の場所と時間も記憶している";
		mes "そうなので、とりあえず今一度";
		mes "修行してもう少し腕を上げてまた、";
		mes "もう一度あの場所に行こうという話に";
		mes "落ち着きました。";
		next;
		mes "[ゲルカ]";
		mes "なので私と師匠、あと何人かは";
		mes "この楽園団に戻って装備を買うための";
		mes "資金集めと修行を兼ねてバイトを。";
		mes "ニュオーズ様は一人で考えたいからと、";
		mes "私達とは今は別行動をとっています。";
		mes "今回は流石に仕方ないですね……。";
		next;
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "なのでまたもし" + strcharinfo(0) + "さんが";
		mes "あの場所の探索に協力して良いなら";
		mes "その時は是非、私達と一緒に";
		mes "またあの場所に行きましょうね！";
		mes "それまでに私ももう少し腕を";
		mes "上げておきますから。";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
	if(checkquest(13181)) {
		cutin "gelca01.bmp", 2;
		mes "[ゲルカ]";
		mes "臨時メンバーとして、";
		mes "ご一緒していただける";
		mes "みたいですね！";
		mes "よろしくお願いします！";
		close2;
		cutin "gelca01.bmp", 255;
		end;
	}
	cutin "gelca01.bmp", 2;
	mes "[ゲルカ]";
	mes "一に修行、二に修行！";
	mes "三四がなくて、五に師匠！";
	mes "毎日が修行の日です！";
	mes "今日も頑張ります！";
	close2;
	cutin "gelca01.bmp", 255;
	end;
}

moc_para01.gat,41,95,5	script	ロテルト#1	630,{
	if(checkquest(117060) & 0x8) {
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "なんだ？";
		mes "もしかすると暇そうに見えるのか？";
		mes "……これでも色々と忙しいんだ。";
		mes "もし、話し相手がほしいだけなら";
		mes "そこのゲルカでいいと思うぞ。";
		next;
		switch(select("仕事とは？","弟子について","ニュオーズについて")) {
		case 1:
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "簡単に言えば後輩の";
			mes "指導だ。";
			mes "とりあえず試験的に、";
			mes "俺たちが初心者や不慣れな";
			mes "冒険者を指導することに";
			mes "なったんだ。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "お蔭でいまは、";
			mes "天下の悪童と呼ばれたこの俺、";
			mes "ロテルト様が";
			mes "ひよっこ冒険者の統制及び引率だ。";
			mes "チッ……。";
			mes "考えるだけでイライラしてくる。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "とはいえ、ここの関係者に";
			mes "多少なりとも借りがあるし、";
			mes "俺一人でやるよりは";
			mes "ひよっこに仕事を回して、";
			mes "多少は世間の厳しさを";
			mes "分からせてやらないとな。";
			next;
			mes "[ロテルト]";
			mes "結果的に苦労するのは、";
			mes "俺たちみたいに冒険に多少";
			mes "馴れた連中だ。";
			mes "俺はそのことを嫌というほど";
			mes "知っている……。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "だからお前もあまり、";
			mes "相手がひよっこだからと";
			mes "過度に世話を焼いたりするなよ。";
			mes "その時でしか味わえない";
			mes "経験や思い出が、後々そいつの";
			mes "成長に影響するかもしれないからな。";
			close2;
			cutin "rote03.bmp", 255;
			end;
		case 2:
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "おい、まさか……";
			mes "俺の弟子になりたいとか";
			mes "ふざけた理由で声をかけたなら";
			mes "覚悟しておけよ？";
			next;
			menu "ゲルカについてだと伝える",-;
			mes "[ロテルト]";
			mes "なんだ、弟子っていうのは";
			mes "ゲルカのことか。";
			mes "アイツは確かに俺の一番弟子に";
			mes "間違いない。";
			mes "とはいえ、アイツ以外にもう";
			mes "弟子をとる予定もないけどな。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "正直、これ以上増えても";
			mes "きちんと師匠らしいことを";
			mes "してやる自信がないしな。";
			mes "ゲルカは弟子が増えれば";
			mes "それだけ賑やかになって、";
			mes "楽しそうとか言ってるが。";
			next;
			mes "[ロテルト]";
			mes "大体アイツの修羅としての腕前は";
			mes "なかなかのものなんだが、";
			mes "あの性格がどうにも災いしてしまい";
			mes "実力を発揮できていない部分が";
			mes "かなりある。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "そういう意味でもアイツは";
			mes "まだまだひよっこってとこだな。";
			mes "まったく。";
			mes "虎に翼が生える日は一体";
			mes "いつになるやらだ……。";
			close2;
			cutin "rote01.bmp", 255;
			end;
		case 3:
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ニュオーズか。";
			mes "あいつなら……";
			mes "シャルロシーの部下に";
			mes "転職したぞ？";
			next;
			menu "え!?",-,"羨ましい……",-;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……冗談だ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "ニュオーズなら相変わらず、";
			mes "どこでどうしてるのか分からん。";
			mes "シャルロシーが言うにはどうも、";
			mes "またどこかの次元の狭間を";
			mes "迷子になってるらしい。";
			next;
			mes "[ロテルト]";
			mes "シャルロシーがギルドメンバーに";
			mes "入ったお陰で多少はアイツの";
			mes "居場所が把握しやすくなったのは";
			mes "ある意味、嬉しい誤算だな。";
			next;
			menu "居場所を把握する必要を尋ねる",-;
			mes "[ロテルト]";
			mes "フン、当然の疑問か。";
			mes "いうなればアイツは俺たちの";
			mes "ギルドにとって、";
			mes "万能薬みたいなもんだからな。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "……万能薬はわかるだろ？";
			mes "なくてもいいが、持っていると";
			mes "何かあった時に安心のアイテムだ。";
			mes "そんな感じで、だ。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "普段は別に居ても居なくても";
			mes "かまわないが、何かあるって時に";
			mes "アイツがいるとうちのギルドは";
			mes "妙にうまくいくことが多い。";
			mes "今回もそうだったしな。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "だから何かあったとき、";
			mes "アイツをすぐに捕まえて呼び戻せる";
			mes "状態にしておきたいんだ。";
			mes "もっとも、アイツがもう少し";
			mes "まめな人間ならこんな心配は";
			mes "無用なんだが……。";
			next;
			cutin "rote01.bmp", 2;
			mes "[ロテルト]";
			mes "……少し喋りすぎたな。";
			mes "今言ったことは他言無用だ。";
			mes "特にミンミンがこの話を聞いたら";
			mes "素直じゃないだの、ツンデレだのと、";
			mes "うるさいからな。";
			close2;
			cutin "rote01.bmp", 255;
			end;
		}
	}
	if(JTB_2QUE == 7) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "よう、" +strcharinfo(0)+ "。";
		mes "あの薄暗い洞窟で会うのとは";
		mes "やっぱり一味違うな。";
		mes "調子はどうだ？";
		next;
		if(select("はい、元気です","最近スランプ気味で……") == 1) {
			cutin "rote04.bmp", 2;
			mes "[ロテルト]";
			mes "そうか……。";
			next;
			cutin "rote03.bmp", 2;
			mes "[ロテルト]";
			mes "なら良かったぜ。";
			mes "お前には色々と迷惑を";
			mes "かけちまったからな……。";
			next;
		} else {
			cutin "rote04.bmp", 2;
			mes "[ロテルト]";
			mes "そうか……。";
			next;
		}
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ところで……だ。";
		mes "お前はアイツにあれから";
		mes "会いに行ってやってるか？";
		mes "アイツとはつまり……";
		mes "シャルロシーのことだ。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "俺らも暇を見て顔を出してるが";
		mes "お前も臨時メンバーとはいえ、";
		mes "アイツのことを知る人間なんだ。";
		mes "時々でいいからお前の顔も";
		mes "見せてやってくれ。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ギ、ギルドメンバーだから";
		mes "ギルドマスターの俺がなにかと";
		mes "気にかけてやらないといけないしな！";
		mes "だからお前も何かあったら、";
		mes "俺に遠慮なく言えよ？";
		setquest 117060;
		compquest 117060;
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
	if(checkquest(116508) & 0x8) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "ああ、お前か。";
		mes "妙に冒険なれした";
		mes "雰囲気のやつがいると";
		mes "思ったぜ……。";
		next;
		mes "[ロテルト]";
		mes "俺がどうしてここに";
		mes "居るのかって顔だな。";
		mes "簡単にいうとここで日々、";
		mes "飯の食い上げにならないよう";
		mes "頑張ってるってだけだ。";
		next;
		cutin "rote03.bmp", 2;
		mes "[ロテルト]";
		mes "あとはまあ……";
		mes "他の連中が変にやる気になって";
		mes "もう少し腕を上げてまた、";
		mes "あの場所に挑みたいと";
		mes "言い出しててな。";
		next;
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "そのためには装備とか";
		mes "いろいろ先立つものが必要だしな。";
		mes "そんなわけでここで他のヤツも";
		mes "何人か働いてるんだ。";
		mes "良かったら顔だけでも";
		mes "見せてやってくれ。";
		next;
		mes "[ロテルト]";
		mes "特にゲルカのやつは、";
		mes "俺が最近忙しくてあまり相手を";
		mes "出来ていない状態だからな。";
		mes "今度暇になった時にでも、";
		mes "俺のかわりにアイツの話相手に";
		mes "なってもらえると助かるぜ。";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
	if(checkquest(13181)) {
		cutin "rote01.bmp", 2;
		mes "[ロテルト]";
		mes "未知の場所だから、";
		mes "油断するなよ？";
		mes "臨時メンバーとはいえ、";
		mes "大事な戦力なんだからな。";
		close2;
		cutin "rote01.bmp", 255;
		end;
	}
	cutin "rote03.bmp", 2;
	mes "[ロテルト]";
	mes "ったく……！";
	mes "肝心な時にアイツは";
	mes "いつもこうだ。";
	mes "人の都合も考えないで";
	mes "いつも俺や皆が暇だとは";
	mes "限らないぞ!?";
	next;
	mes "[ロテルト]";
	mes "……なんだ？";
	mes "俺はいま少し虫の居所が";
	mes "悪いんだ。";
	mes "用がないなら離れていた方が";
	mes "いいと思うぞ。";
	close2;
	cutin "rote03.bmp", 255;
	end;
}

moc_para01.gat,17,95,5	script	ミンミン#1	643,{
	if(checkquest(117065) & 0x8) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら、何か私に";
		mes "聞きたそうな顔をしているわね。";
		mes "スリーサイズと年齢以外なら、";
		mes "答えてあげることも";
		mes "やぶさかではないわね。";
		next;
		switch(select("ミンミンについて","モンスターの研究について","ロテルトについて")) {
		case 1:
			mes "[ミンミン]";
			mes "なあに？";
			mes "私について知りたいの？";
			mes "あなたも物好きね。";
			mes "まあいいわ。";
			mes "今更知らない仲じゃないんだし。";
			mes "私の何について聞きたいの？";
			next;
			if(select("どうして楽園団に？","そのマントの付箋は？") == 1) {
				mes "[ミンミン]";
				mes "私がここ楽園団にいるのは";
				mes "ある研究を手伝ってほしいと";
				mes "言われたからよ。";
				next;
				mes "[ミンミン]";
				mes "元々私は山で暮らしながら";
				mes "キノコを栽培して研究をしていたの。";
				mes "ただ……思うように研究が";
				mes "進まなかったのよね。";
				mes "だから気分転換も兼ねて、";
				mes "冒険することにしたの。";
				next;
				mes "[ミンミン]";
				mes "といっても普通の冒険じゃなく";
				mes "私の探究心を満たすような、";
				mes "冒険が良かったのよねぇ。";
				mes "だから、希少なモンスターを探して、";
				mes "冒険することを目的にした";
				mes "^ff0000レアモンスター探索同好会^000000に入ったわ。";
				next;
				cutin "min02.bmp", 2;
				mes "[ミンミン]";
				mes "ただそれがある意味、";
				mes "運のつきだったんでしょうね。";
				mes "その同好会であの二人と";
				mes "出会ってしまったのよねぇ。";
				mes "あの二人っていうのは無論、";
				mes "ロテルトとニュオーズね。";
				next;
				mes "[ミンミン]";
				mes "そのかわり、希少なモンスターとは";
				mes "かなりの確率で会うことが出来たわ。";
				mes "お陰で本業であるキノコの研究より";
				mes "モンスターの研究のほうが、";
				mes "面白いように進んだわ。";
				mes "本末転倒な気もするけど。";
				next;
				mes "[ミンミン]";
				mes "お陰で気がつけば……";
				mes "主に希少なモンスターに関して、";
				mes "先生と呼ばれるレベルまで";
				mes "知識がついていたの。";
				mes "とはいえ、キノコの研究も";
				mes "懲りずに続けているわよ？";
				next;
				cutin "min01.bmp", 2;
				mes "[ミンミン]";
				mes "とにかくそんなわけで今は";
				mes "モンスターに関する研究を";
				mes "手伝ってほしいと要請されて";
				mes "ここにいるのよ。";
				mes "ただ問題があるとすれば、";
				mes "弟子がいない点くらいねぇ。";
				close2;
				cutin "min01.bmp", 255;
				end;
			} else {
				mes "[ミンミン]";
				mes "ああ、マントの裏に貼った";
				mes "付箋……今はポスト・イットって";
				mes "言うんだったかしら？";
				mes "これが気になるのね。";
				next;
				mes "[ミンミン]";
				mes "楽園団で依頼されている";
				mes "研究以外に、自分のための";
				mes "研究も行っているの。";
				mes "そうね、あなただけには";
				mes "こっそり教えてあげるわ。";
				next;
				cutin "min02.bmp", 2;
				mes "[ミンミン]";
				mes "実はまったく新しい技術の";
				mes "開発のための研究をしているのよ。";
				mes "これが成功したらかなり";
				mes "便利になるはずよ。";
				next;
				mes "[ミンミン]";
				mes "研究対象は魔力の角と";
				mes "未知の欠片、そして最後に";
				mes "血のついた紙……。";
				next;
				mes "[ミンミン]";
				mes "血の付いた紙に眠る";
				mes "古代の技術を読み解きながら";
				mes "魔力の角から抽出した魔力を";
				mes "未知の欠片に注ぎ込むの。";
				next;
				cutin "min01.bmp", 2;
				mes "[ミンミン]";
				mes "もしこれが私の予想通りに成功したら";
				mes "どんな膨大な情報も自由に圧縮して";
				mes "好きな時に自由に取り出す事の出来る";
				mes "魔法のメモ帳が出来上がるわ！";
				mes "どう、便利だと思わない？";
				close2;
				cutin "min01.bmp", 255;
				end;
			}
		case 2:
			mes "[ミンミン]";
			mes "う～ん、そうね。";
			mes "流石に詳しい話は出来ないけど";
			mes "楽園団では冒険者の育成を第一に";
			mes "簡単な依頼から割りと腕が必要な";
			mes "依頼を請け負う予定なのよね。";
			next;
			mes "[ミンミン]";
			mes "そのためにもある程度、";
			mes "危険なモンスターの生息地や";
			mes "特徴などのデータを収集したい";
			mes "みたいなのよね。";
			next;
			mes "[ミンミン]";
			mes "特に成長中の冒険者達のために";
			mes "あらかじめ危険な要素を伝え";
			mes "事前に準備可能なように、";
			mes "しておきたいみたい。";
			mes "まあ、私個人としては正直";
			mes "余計なお世話って感じかしら。";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "あなたも冒険者なら";
			mes "なんとなく私の言いたいことが";
			mes "分かるんじゃないかしら。";
			mes "冒険って予想外の出来事や";
			mes "命の危険にいつ何時でも、";
			mes "陥ることがあるでしょう？";
			next;
			mes "[ミンミン]";
			mes "そういう経験って早いほうが";
			mes "後々になって、生きてくるだろうし";
			mes "教えてもらったことしか出来ないと";
			mes "何かあったときに挫折しやすいの。";
			mes "例えば本来いないモンスターに";
			mes "襲われた時とかね。";
			next;
			mes "[ミンミン]";
			mes "そもそもミッドガルドの外まで";
			mes "出たことがある冒険者なら、";
			mes "既にある程度の適応能力は";
			mes "備わっていると思うのよね。";
			mes "ここまで過保護にしなくても。";
			next;
			mes "[ミンミン]";
			mes "まあ、これは全て私の主観よ。";
			mes "それに依頼されている以上、";
			mes "私は楽園団の指針に従うだけよ。";
			mes "その代わりなるべく正確で";
			mes "詳細なデータを出すように";
			mes "努めているわ。";
			close2;
			cutin "min02.bmp", 255;
			end;
		case 3:
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "ロテルトね……。";
			mes "私がこの楽園団で働く";
			mes "きっかけになったのが";
			mes "実はロテルトなのよね。";
			next;
			mes "[ミンミン]";
			mes "私より先にあいつがここで";
			mes "働いていて、人手が足りないからと";
			mes "私が借り出されたわけ。";
			mes "結局そのままここで、";
			mes "研究を続けることに";
			mes "なったんだけど。";
			next;
			mes "[ミンミン]";
			mes "ある日、ソロとパーティーでの";
			mes "モンスター討伐に関する";
			mes "難易度調査の依頼があったんだけど";
			mes "まだこの学園にきて日が浅い";
			mes "私じゃ人を集めるのが";
			mes "難しかったのよ。";
			next;
			mes "[ミンミン]";
			mes "だから私よりここが長い";
			mes "ロテルトに相談したわけ。";
			mes "日が浅い私がなるべく";
			mes "多くの冒険者を集めるには";
			mes "どうしたらいいかしら？";
			mes "ってね。";
			next;
			mes "[ミンミン]";
			mes "そしたらロテルトの奴、";
			mes "涼しげな顔してこういったわ。";
			mes "ミンミンならここで鞭持って";
			mes "^ff0000女王様とお呼び!!^000000って";
			mes "叫んでれば物好きな奴が、";
			mes "反応するんじゃないか？って。";
			next;
			cutin "min01.bmp", 2;
			mes "[ミンミン]";
			mes "その後無論ロテルトに";
			mes "お仕置きの意味をこめて";
			mes "スポアエクスプロージョンを";
			mes "食らわせておいたわ。";
			next;
			cutin "min02.bmp", 2;
			mes "[ミンミン]";
			mes "結局そのお陰で人が集まったんだけど";
			mes "何故だか私を怒らせると怖いから";
			mes "怒らせてはいけない！みたいな";
			mes "雰囲気になったのだけは";
			mes "納得いかないわ。";
			next;
			mes "[ミンミン]";
			mes "まったく……";
			mes "ロテルトに関わると";
			mes "ろくな目にあわないわね。";
			close2;
			cutin "min02.bmp", 255;
			end;
		}
	}
	if(JTB_2QUE == 7) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら……";
		mes strcharinfo(0)+ "じゃない。";
		mes "改めてここでも言うわ。";
		mes "お疲れ様。";
		next;
		mes "[ミンミン]";
		mes "まさかあの気難しいロテルトを";
		mes "説得できるとは思わなかったわ。";
		mes "付き合いが長い私ですら、";
		mes "半分諦めていたくらいだったのに。";
		mes "よくやったわね。";
		next;
		mes "[ミンミン]";
		mes "とはいえ、これからが本当の意味で";
		mes "大変なのは間違いないでしょうね。";
		mes "今まではギルドメンバー限定だけど";
		mes "これからあの子、他の人間の";
		mes "目に触れる機会が多くなるかも";
		mes "しれないし。";
		next;
		cutin "min03.bmp", 2;
		mes "[ミンミン]";
		mes "まっ、最悪ロテルトに全部";
		mes "押し付ければ問題ないはずだし。";
		mes "あなたはギルドにまた";
		mes "参加したくなったらいつでも";
		mes "遊びに来るといいわよ？";
		mes "歓迎するし。";
		setquest 117065;
		compquest 117065;
		close2;
		cutin "min03.bmp", 255;
		end;
	}
	if(checkquest(116508) & 0x8) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あら。";
		mes strcharinfo(0) + "。";
		mes "こっちで会うとなんだか";
		mes "変な感じね。";
		next;
		mes "[ミンミン]";
		mes "とりあえずシャルロシーの件は";
		mes "まだ色々と問題がありそうね。";
		mes "特に新しいギルドマスターを";
		mes "攻略しないと無理だと思うわ。";
		next;
		cutin "min02.bmp", 2;
		mes "[ミンミン]";
		mes "ロテルトって見た目通り、";
		mes "気難しい性格だから大変よ。";
		mes "特に、ギルドメンバーに何か";
		mes "危険がおよぶ可能性があることには";
		mes "かな～り敏感なのよね。";
		next;
		mes "[ミンミン]";
		mes "まあ、そこはあの子なりに";
		mes "色々あったから仕方がないんだけど。";
		mes "なにはともあれここでこうして";
		mes "色々と話してみたところで、";
		mes "机上の空論でしかないし。";
		mes "とにかく……";
		next;
		mes "[ミンミン]";
		mes "ルナインのワープポータルが";
		mes "時間を記憶しているみたいだし、";
		mes "それをうまく利用して誰かが";
		mes "ロテルトを含め、他のみんなを";
		mes "説得するしかないんじゃないかしら？";
		close2;
		cutin "min02.bmp", 255;
		end;
	}
	if(checkquest(13181)) {
		cutin "min01.bmp", 2;
		mes "[ミンミン]";
		mes "あなたも物好きね。";
		mes "何にしろ短い間だろうけど、";
		mes "よろしくお願いするわ。";
		close2;
		cutin "min01.bmp", 255;
		end;
	}
	mes "[ミンミン]";
	mes "さーってと。";
	mes "今日こそあの研究、";
	mes "少しは進展あるかしら？";
	mes "いい加減そろそろ";
	mes "次の段階に進みたいわね。";
	close2;
	cutin "min01.bmp", 255;
	end;
}

moc_para01.gat,41,76,3	script	ラギ#1	647,{
	if(checkquest(117070) & 0x8) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "今、アイグ様の新曲の";
		mes "歌詞を考えているんですが、";
		mes "少しインスピレーションが";
		mes "ほしいんですよねぇ。";
		mes "良かったら私に質問して";
		mes "くれませんか？";
		next;
		switch(select("ラギについて","新曲について","アイグについて")) {
		case 1:
			cutin "ragi02.bmp", 2;
			mes "[ラギ]";
			mes "いいですねぇ。";
			mes "僕自身のことについて";
			mes "改めてお話しすることで";
			mes "何か良い歌詞が思いつくかも";
			mes "しれません。";
			mes "何についてお話しましょう。";
			next;
			if(select("ラギのヘアスタイルについて","歌を聴かせてほしい") == 1) {
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "僕のこの髪はアルベルタにいる";
				mes "ある美容師に整えていただきました。";
				mes "なぜかその美容師、髪用じゃなく";
				mes "肉を切るための鋏で切るのが";
				mes "不思議ではあるんですが。";
				next;
				cutin "ragi02.bmp", 2;
				mes "[ラギ]";
				mes "腕は良いし気に入っているのですが、";
				mes "そこの美容師に髪型はお任せになるので";
				mes "たまに変な髪形にされることが";
				mes "あるみたいですよぉ。";
				mes "そういう意味では僕の髪型は";
				mes "運が良かったのでしょうねぇ。";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "あと、この髪の色は僕の所属する";
				mes "たんぽぽ楽団にピッタリの色で";
				mes "個人的にかなり気に入って";
				mes "いるんですよねぇ。";
				mes "ちなみにこの色は天然です。";
				mes "染めたわけではないんですよぉ。";
				next;
				mes "[ラギ]";
				mes "そういえばタンポポの花言葉は";
				mes "^0000FF愛の信託^000000だそうです。";
				mes "古くから、タンポポの綿毛で";
				mes "恋占いをしていたことから";
				mes "そのような花言葉に";
				mes "なったという説があります。";
				next;
				mes "[ラギ]";
				mes "他にも誠実、幸福……";
				mes "また、別離という意味もあります。";
				mes "でも僕は別離というのは";
				mes "再び会うための一時の約束だと";
				mes "考えていますから考え方次第では";
				mes "悪い意味ではないと思っていますよ。";
				next;
				mes "[ラギ]";
				mes "なにはともあれ……";
				mes "誠実や幸福という言葉はまさに";
				mes "アイグ様の歌のようで";
				mes "たんぽぽ楽団の一員になれたことを";
				mes "僕は心から誇りに思いますよ。";
				close2;
				cutin "ragi01.bmp", 255;
				end;
			} else {
				cutin "ragi03.bmp", 2;
				mes "[ラギ]";
				mes "えっ、僕の歌をですか？";
				mes "確かに僕の職業はバードだし";
				mes "アイグ様のために歌詞を良く";
				mes "書いていますが……";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "実はたんぽぽ楽団に所属してから";
				mes "自分のために";
				mes "正式に作曲した曲や歌は";
				mes "まだない状態なんですよね……。";
				mes "主に僕はアイグ様の歌詞の作成を";
				mes "担っていますから。";
				next;
				cutin "ragi02.bmp", 2;
				mes "[ラギ]";
				mes "いつか自分で作詞作曲した歌を";
				mes "誰かに聴いていただけるように";
				mes "なりたいとは思っているんですが、";
				mes "なかなか音楽の神様が";
				mes "おりてこないんですよねぇ。";
				next;
				mes "[ラギ]";
				mes "とはいえ僕もバードのはしくれ。";
				mes "きっといつかたんぽぽ楽団の";
				mes "正規メンバーとして";
				mes "最高の歌を作曲してみますよぉ。";
				next;
				cutin "ragi01.bmp", 2;
				mes "[ラギ]";
				mes "なので申し訳ないですが、";
				mes "そのときがくるまで僕の歌は";
				mes "お楽しみ、ということで";
				mes "お願いします。";
				close2;
				cutin "ragi01.bmp", 255;
				end;
			}
		case 2:
			mes "[ラギ]";
			mes "アイグ様の新曲なのですが";
			mes "せっかくなのでモロクに関する";
			mes "歌を作ろうかなと考えていたり";
			mes "するんですよねぇ。";
			next;
			mes "[ラギ]";
			mes "といっても魔王の方ではなく、";
			mes "魔王モロクの現身の方です。";
			mes "多分僕よりも" +strcharinfo(0)+ "さんの方が";
			mes "よくご存知だとは思いますが……。";
			next;
			cutin "ragi02.bmp", 2;
			mes "[ラギ]";
			mes "魔王モロクに関する歌については";
			mes "恐らくいろいろな人が題材に";
			mes "することは明らかですし。";
			mes "それなら僕は魔王モロクの";
			mes "現身の方を題材にしたほうが";
			mes "面白そうですから。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "特にモロクの現身の";
			mes "天使型と人間型。";
			mes "モロクにより生み出された";
			mes "モンスターに関わらず、";
			mes "なぜ天使と人間の形式である";
			mes "必要があるんでしょうねぇ。";
			next;
			mes "[ラギ]";
			mes "モロクがどうして現身をそのような";
			mes "形に創造したのか、僕にとって";
			mes "かなり興味のある題材です。";
			mes "まあ、モロクの現身に限らず";
			mes "僕にとってこの世界はとても興味深い";
			mes "観察対象なんですが。";
			next;
			mes "[ラギ]";
			mes "そういう謎めいた部分などを";
			mes "うまく歌詞と曲に融合させて";
			mes "後々、こういうことがあったんだと";
			mes "語り継がれるような歌に出来れば";
			mes "いいなと思っています。";
			next;
			mes "[ラギ]";
			mes "そう考えると冒険者という職業は";
			mes "気づかないうちに色々と、";
			mes "世界の謎や出来事に";
			mes "関わっている唯一の職業かも";
			mes "しれませんねぇ。";
			close2;
			cutin "ragi01.bmp", 255;
			end;
		case 3:
			cutin "ragi02.bmp", 2;
			mes "[ラギ]";
			mes "アイグ様について、ですか。";
			mes "そうですねぇ。";
			mes "僕がたんぽぽ楽団に";
			mes "入団するきっかけになったのは";
			mes "間違いなくアイグ様ですね。";
			next;
			mes "[ラギ]";
			mes "アイグ様と初めて会った時のことは";
			mes "今でも鮮明に憶えています。";
			mes "アイグ様が公演を終えて、";
			mes "イズルードに戻ってきた時に、";
			mes "僕もアイグ様を迎えるために";
			mes "その港に居たんです。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "あ、言い忘れていましたが僕は";
			mes "全国にあるアイグファンクラブ、";
			mes "イズルード支部の会長なんですよぉ。";
			mes "なのでその日も会長として";
			mes "一番にアイグ様をお迎えしました。";
			next;
			mes "[ラギ]";
			mes "とはいえアイグ様は人気者ですから";
			mes "アイグ様を一目見ようと、港は";
			mes "すごい人だかりで……。";
			mes "多分アイグ様には僕の姿など";
			mes "分からないだろうなと、";
			mes "諦めていたんですが……。";
			next;
			mes "[ラギ]";
			mes "アイグ様はそんな中でも、僕の姿を";
			mes "しっかり見つけてくれたんです。";
			mes "あの時は本当に嬉しかったですよぉ。";
			mes "……というわけでそれがきっかけで";
			mes "アイグ様と親しくなり、";
			mes "現在にいたります。";
			next;
			mes "[ラギ]";
			mes "ただ最近どうにも僕自身が、";
			mes "アイグ様の力になれない事が多くて";
			mes "自分の無力さを感じる場面が";
			mes "多いんですよねぇ。";
			next;
			mes "[ラギ]";
			mes "なのでせめて歌くらいはと";
			mes "作詞を頑張っているんですが、";
			mes "やはり心に余裕がないからか";
			mes "なかなかうまくいきません。";
			mes "困ったものですよぉ。";
			next;
			cutin "ragi02.bmp", 2;
			mes "[ラギ]";
			mes "ところで……";
			mes "今までの話、信じましたか？";
			mes "全てのお話にはある程度、";
			mes "飾ったり偽った内容を含めて";
			mes "語られた可能性があります。";
			next;
			cutin "ragi01.bmp", 2;
			mes "[ラギ]";
			mes "少なくとも僕はこれでも";
			mes "バードですからねぇ。";
			mes "あまり言葉通りにとらずに";
			mes "聞き流しておいてくださいね。";
			mes "特にアイグ様には";
			mes "他言無用でお願いします。";
			close2;
			cutin "ragi01.bmp", 255;
			end;
		}
	}
	if(JTB_2QUE == 7) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "こんにちは。";
		mes strcharinfo(0)+ "さん。";
		mes "改めて、お疲れ様でした。";
		next;
		mes "[ラギ]";
		mes "あのロテルト様を説得する様は";
		mes "惚れ惚れしましたよぉ。";
		mes strcharinfo(0)+ "さんは冒険者ではなく、";
		mes "参謀などの地位のほうが";
		mes "似合うのではないでしょうか。";
		next;
		mes "[ラギ]";
		mes "とはいえ本当に大変なのは";
		mes "これからなんですよねぇ。";
		mes "そんなことを言いながら、";
		mes "僕自身はシャルロシーが";
		mes "どういう成長を見せてくれるのか";
		mes "楽しみでなりませんが。";
		next;
		cutin "ragi02.bmp", 2;
		mes "[ラギ]";
		mes "刺激が無いとアイディアというのは";
		mes "すぐに枯渇してしまいますし。";
		mes "そういう意味でも僕は、";
		mes strcharinfo(0)+ "さんを含めて皆さんと";
		mes "会えたことには今でも";
		mes "感謝していますよぉ。";
		setquest 117070;
		compquest 117070;
		close2;
		cutin "ragi02.bmp", 255;
		end;
	}
	if(checkquest(116508) & 0x8) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes strcharinfo(0) + "さん。";
		mes "今日も冒険に行かれる";
		mes "予定ですか？";
		next;
		cutin "ragi03.bmp", 2;
		mes "[ラギ]";
		mes "それにしても……";
		mes "一難去ってまた一難。";
		mes "そんな言葉がピッタリの";
		mes "展開になっていますねぇ。";
		next;
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "とはいえ僕はロテルト様の";
		mes "言うことももっともだと";
		mes "思うんですよねぇ。";
		mes "いうなればモンスターの首に";
		mes "鈴を付けるようなものですし。";
		next;
		mes "[ラギ]";
		mes "ただ、アイグ様を見ていると";
		mes "僕個人としてはやはり、";
		mes "シャルロシーのことをなんとか";
		mes "出来ないものかと頭を";
		mes "悩ませてはいるのですが……";
		mes "成果は出ていません。";
		next;
		mes "[ラギ]";
		mes "とりあえずルナインさんの";
		mes "ワープポータルで何度もあの場所に";
		mes "通って、皆さんが納得できるような";
		mes "解答が見つかるまで頑張るしか";
		mes "ないようですねぇ……。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	}
	if(checkquest(13181)) {
		cutin "ragi01.bmp", 2;
		mes "[ラギ]";
		mes "こんにちは。";
		mes "短い間ですが、";
		mes "よろしくお願いしますね。";
		mes "あなたの活躍、";
		mes "楽しみにしていますよぉ。";
		close2;
		cutin "ragi01.bmp", 255;
		end;
	}
	cutin "ragi01.bmp", 2;
	mes "[ラギ]";
	mes "その髪は黄金蟲のように……";
	mes "ふむ、さすがに歌詞に";
	mes "蟲はあまり良くない気が";
	mes "しますねぇ。";
	mes "他に何かあるかな……。";
	close2;
	cutin "ragi01.bmp", 255;
	end;
}

//==========================================
// デイリークエスト
//------------------------------------------
moc_para01.gat,44,81,3	script	メロディージャック#1	648,8,8,{
	if(JTB_DAILY == 2) {
		mes "[メロディージャック]";
		mes "……。";
		mes "今日はどうする？";
		next;
		switch(select("依頼を受ける","依頼を報告する","特別報酬について","依頼を破棄する","話をする")) {
		case 1:
			if(BaseLevel >= 140) {
				mes "[メロディージャック]";
				mes "残念だがお前に依頼できるものは";
				mes "無いようだ。";
				mes "私の依頼はある程度決まった腕前の";
				mes "メンバーに依頼する必要がある。";
				mes "それがクライアントからの";
				mes "指示だから仕方がない。";
				next;
				mes "[メロディージャック]";
				mes "あちらを立てればこちらが立たず";
				mes "と言ったように、細かい約束ごとが";
				mes "今回はいろいろ決められている。";
				mes "このためお前に依頼することは";
				mes "もう出来ないから、";
				mes "憶えておいてくれ。";
				next;
				mes "‐^ff0000メロディージャックの依頼は";
				mes "　BaseLv140以上では受けることが";
				mes "　できません^000000‐";
				close;
			}
			if(checkquest(96800)) {
				if(!(checkquest(96800) & 0x2)) {
					mes "[メロディージャック]";
					mes "今日の分の仕事は終えたようだな。";
					mes "しかしモンスターというやつらは";
					mes "いきなり現れたりするから";
					mes "安心する事はできない。";
					mes "また暇なときに頼む。";
					close;
				}
			}
			if(checkquest(96801)) {
				mes "[メロディージャック]";
				mes "どうした？　依頼を忘れたのか？";
				mes "仕方がない奴だな。";
				next;
				mes "[メロディージャック]";
				mes "お前に頼んだ内容は";
				mes "^FF0000タナトスタワー^000000で";
				mes "^FF0000慰める者";
				mes "執行する者";
				mes "保護する者^000000を";
				mes "20匹倒してもらいたい。";
				next;
				mes "[メロディージャック]";
				mes "アイグには気づかれるなよ。";
				mes "よろしく頼む。";
				close;
			}
			if(checkquest(96802)) {
				mes "[メロディージャック]";
				mes "どうした？　依頼を忘れたのか？";
				mes "仕方がない奴だな。";
				next;
				mes "[メロディージャック]";
				mes "お前に頼んだ内容は";
				mes "^FF0000フレイヤ大神殿^000000で";
				mes "^FF0000ヴァンベルク";
				mes "アイシラ";
				mes "エキオ^000000を";
				mes "20匹倒してもらいたい。";
				next;
				mes "[メロディージャック]";
				mes "アイグには気づかれるなよ。";
				mes "よろしく頼む。";
				close;
			}
			if(checkquest(96803)) {
				mes "[メロディージャック]";
				mes "どうした？　依頼を忘れたのか？";
				mes "仕方がない奴だな。";
				next;
				mes "[メロディージャック]";
				mes "お前に頼んだ内容は";
				mes "^FF0000名もなき島^000000で";
				mes "^FF0000ゾンビスローター";
				mes "ラギッドゾンビ";
				mes "バンシー^000000を";
				mes "20匹倒してもらいたい。";
				next;
				mes "[メロディージャック]";
				mes "アイグには気づかれるなよ。";
				mes "よろしく頼む。";
				close;
			}
			if(checkquest(96804)) {
				mes "[メロディージャック]";
				mes "どうした？　依頼を忘れたのか？";
				mes "仕方がない奴だな。";
				next;
				mes "[メロディージャック]";
				mes "お前に頼んだ内容は";
				mes "^FF0000アビスレイク^000000で";
				mes "^FF0000グリーンペロス";
				mes "ブルーオシドス";
				mes "レッドペロス^000000を";
				mes "20匹倒してもらいたい。";
				next;
				mes "[メロディージャック]";
				mes "アイグには気づかれるなよ。";
				mes "よろしく頼む。";
				close;
			}
			if(checkquest(96801) & 0x4 || checkquest(96802) & 0x4 || checkquest(96803) & 0x4 || checkquest(96804) & 0x4) {
				mes "[メロディージャック]";
				mes "達成済みの依頼があるようだな。";
				mes "まずはそっちを報告してくれ。";
				close;
			}
			mes "[メロディージャック]";
			mes "すまん、手間をかけるな。";
			mes "依頼内容だが、";
			mes "アイグが行きそうな場所を中心に";
			mes "モンスターを減らしてきてほしい。";
			next;
			mes "[メロディージャック]";
			mes "アイグが行きそうな場所はここだ。";
			mes "4つあるが、どこに行くかは";
			mes "はっきりしていない。";
			mes "場合によっては徒労に帰す";
			mes "可能性はあるが念のためだ。";
			next;
			set '@sel,(select("タナトスタワー","フレイヤ大神殿","名もなき島","アビスレイク"));
			switch('@sel) {
			case 1:
				mes "[メロディージャック]";
				mes "^FF0000タナトスタワー^000000は一番面倒な場所だ。";
				mes "その分報酬も弾むから心配するな。";
				mes "私は約束を守る男だ。";
				mes "まあ、そのお陰で今回、";
				mes "色々面倒なんだが……。";
				next;
				mes "[メロディージャック]";
				mes "^FF0000タナトスタワー^000000では";
				mes "^FF0000慰める者";
				mes "執行する者";
				mes "保護する者^000000";
				break;
			case 2:
				mes "[メロディージャック]";
				mes "アイグの探検はラヘルの";
				mes "フレイヤ大神殿にまで及ぶようだな。";
				mes "そう……アイグが探している^FF0000その人間^000000は";
				mes "どこで発見されてもおかしくない。";
				mes "というわけで以下のモンスターの";
				mes "討伐を頼む。";
				next;
				mes "[メロディージャック]";
				mes "^FF0000フレイヤ大神殿^000000では";
				mes "^FF0000ヴァンベルク";
				mes "アイシラ";
				mes "エキオ^000000";
				break;
			case 3:
				mes "[メロディージャック]";
				mes "普通の冒険者なら";
				mes "存在すら知らない^FF0000名もなき島^000000。";
				mes "そこもアイグは注目し始めている。";
				mes "まったく……面倒なことだ。";
				next;
				mes "[メロディージャック]";
				mes "^FF0000名もなき島^000000では";
				mes "^FF0000ゾンビスローター";
				mes "ラギッドゾンビ";
				mes "バンシー^000000";
				break;
			case 4:
				mes "[メロディージャック]";
				mes "^FF0000アビスレイク^000000にもアイグの";
				mes "依頼が入って来たのか……。";
				mes "世も末だな。";
				next;
				mes "[メロディージャック]";
				mes "^FF0000アビスレイク^000000では";
				mes "^FF0000グリーンペロス";
				mes "ブルーオシドス";
				mes "レッドペロス^000000";
				break;
			}
			mes "を20匹討伐してもらいたい。";
			mes "頼めるか？";
			next;
			if(select("受ける","やめる") == 2) {
				mes "[メロディージャック]";
				mes "そうか。";
				mes "気が変わったらまた来てくれ。";
				close;
			}
			mes "[メロディージャック]";
			mes "助かる。";
			mes "よろしく頼むぞ。";
			mes "あと秘密を守るのも忘れるな。";
			switch('@sel) {
			case 1:
				setquest 96801;
				break;
			case 2:
				setquest 96802;
				break;
			case 3:
				setquest 96803;
				break;
			case 4:
				setquest 96804;
				break;
			}
			close;
		case 2:
			set '@quest,0;
			if(checkquest(96801) & 0x4) {
				set '@quest,96801;
			}
			if(checkquest(96802) & 0x4) {
				set '@quest,96802;
			}
			if(checkquest(96803) & 0x4) {
				set '@quest,96803;
			}
			if(checkquest(96804) & 0x4) {
				set '@quest,96804;
			}
			if('@quest == 0) {
				mes "[メロディージャック]";
				mes "おいおい、";
				mes "完了している依頼は無いようだぞ？";
				mes "もう一度よく確認してみてくれ。";
				close;
			}
			mes "[メロディージャック]";
			mes "依頼は上手くこなしてくれたようだな。";
			mes "助かった。礼を言う。";
			mes "これは報酬だ、受け取ってくれ";
			next;
			if(select("受け取る","受け取らない") == 2) {
				mes "[メロディージャック]";
				mes "なんだ？　なにかあるのか？";
				mes "まあいい、受け取りたくなったら";
				mes "言ってくれ。";
				close;
			}
			delquest '@quest;
			switch('@quest) {
			case 96801:
				setquest 96811;
				break;
			case 96802:
				setquest 96812;
				break;
			case 96803:
				setquest 96813;
				break;
			case 96804:
				setquest 96814;
				break;
			}
			setquest 96800;
			if(BaseLevel >= 90) {
				set '@base1,1000000;
			}
			if(BaseLevel >= 100) {
				set '@base2,1000000;
				set '@base3,1000000;
			}
			if(BaseLevel >= 110) {
				set '@base4,1000000;
				set '@base5,1000000;
			}
			if(BaseLevel >= 120) {
				set '@base6,1000000;
				set '@base7,1000000;
			}
			if(BaseLevel >= 130) {
				set '@base8,1000000;
				set '@base9,1000000;
			}
			getexp '@base1,0,1;
			getexp '@base2,0,1;
			getexp '@base3,0,1;
			getexp '@base4,0,1;
			getexp '@base5,0,1;
			getexp '@base6,0,1;
			getexp '@base7,0,1;
			getexp '@base8,0,1;
			getexp '@base9,0,1;
			mes "[メロディージャック]";
			mes "世話になった。";
			mes "また良かったら手伝ってくれ。";
			close;
		case 3:
			set '@quest,0;
			set '@quest,'@quest+checkquest(96811);
			set '@quest,'@quest+checkquest(96812);
			set '@quest,'@quest+checkquest(96813);
			set '@quest,'@quest+checkquest(96814);
			set '@quest,'@quest+checkquest(96816);
			set '@quest,'@quest+checkquest(96817);
			set '@quest,'@quest+checkquest(96818);
			set '@quest,'@quest+checkquest(96819);
			if('@quest <= 7) {
				mes "[メロディージャック]";
				mes "私とアイグの依頼、";
				mes "^FF0000それぞれ4種類すべてを";
				mes "完了させたら^000000特別報酬をやろう。";
				mes "もし内容が気になるなら";
				mes "私とアイグの依頼を達成してくれ。";
				next;
				mes "[メロディージャック]";
				mes "すべてこなすのは大変だろう。";
				mes "だが、その苦労に見合った";
				mes "報酬は約束する。";
				mes "その気があったら挑んでみてくれ。";
				close;
			} else if('@quest == 8) {
				// 特別報酬
				mes "[メロディージャック]";
				close;
			} else if('@quest == 64) {
				// 特別報酬
				mes "[メロディージャック]";
				close;
			}
		case 4:
			mes "[メロディージャック]";
			mes "依頼した仕事を破棄したいのか？";
			mes "フン、まぁいい。";
			mes "お前にはお前の事情があるんだろう。";
			next;
			mes "[メロディージャック]";
			mes "破棄の方法は2種類ある。";
			mes "好きな方を選べ。";
			next;
			if(select("依頼の破棄","報告記録の破棄") == 1) {
				set '@quest,0;
				set '@quest,'@quest+checkquest(96801);
				set '@quest,'@quest+checkquest(96802);
				set '@quest,'@quest+checkquest(96803);
				set '@quest,'@quest+checkquest(96804);
				if('@quest == 0) {
					mes "[メロディージャック]";
					mes "おいおい、";
					mes "依頼している仕事は無いようだぞ？";
					mes "もう一度よく確認してみてくれ。";
					close;
				}
				mes "[メロディージャック]";
				mes "依頼の破棄は";
				mes "今お前が受けている依頼の";
				mes "^FF0000完了しているものを含め、";
				mes "全てを破棄することになる。^000000";
				mes "報告記録だけ残る形になるな。";
				next;
				mes "[メロディージャック]";
				mes "完了している依頼を破棄してしまうと";
				mes "報酬を渡すことができなくなるぞ。";
				mes "^FF0000完了している依頼は先に報告をして";
				mes "報酬を受け取ってから、";
				mes "依頼の破棄をしてくれ。^000000";
				next;
				mes "[メロディージャック]";
				mes "本当に依頼を破棄してもいいか？";
				next;
				if(select("はい","いいえ") == 2) {
					mes "[メロディージャック]";
					mes "そうか、続けてくれるか。";
					mes "助かる。";
					mes "時間がかかっても構わないから";
					mes "依頼の遂行にあたってくれ。";
					close;
				}
				delquest 96801;
				delquest 96802;
				delquest 96803;
				delquest 96804;
				mes "[メロディージャック]";
				mes "お前に依頼した仕事は取り下げた。";
				mes "また気が向いたら";
				mes "声をかけてくれ。";
				close;
			} else {
				set '@quest,0;
				set '@quest,'@quest+checkquest(96811);
				set '@quest,'@quest+checkquest(96812);
				set '@quest,'@quest+checkquest(96813);
				set '@quest,'@quest+checkquest(96814);
				if('@quest == 0) {
					mes "[メロディージャック]";
					mes "おいおい、";
					mes "完了している報告の記録は";
					mes "無いようだぞ？";
					mes "もう一度よく確認してみてくれ。";
					close;
				}
				mes "[メロディージャック]";
				mes "報告記録の破棄は";
				mes "今お前が^FF0000報告している依頼の";
				mes "全てを破棄することになる。^000000";
				next;
				mes "[メロディージャック]";
				mes "報告を破棄してしまうと";
				mes "^FF0000特別報酬を得るためには";
				mes "4種類の依頼すべてを、";
				mes "もう一度最初から";
				mes "完了させる必要がある。^000000";
				next;
				mes "‐報告記録の破棄は";
				mes "^FF0000　完了報告を行ったクエストを";
				mes "　全て消去します。^000000";
				mes "　特別報酬を得るためには、";
				mes "^FF0000　再度4種類のクエストを受け、";
				mes "　完了する必要があります^000000‐";
				next;
				mes "[メロディージャック]";
				mes "本当に報告記録を破棄してもいいか？";
				next;
				if(select("はい","いいえ") == 2) {
					mes "[メロディージャック]";
					mes "わかった。";
					mes "引き続き";
					mes "依頼の遂行にあたってくれ。";
					close;
				}
				delquest 96811;
				delquest 96812;
				delquest 96813;
				delquest 96814;
				mes "[メロディージャック]";
				mes "お前が報告した記録は";
				mes "全て破棄した。";
				mes "また気が向いたら依頼を受けてくれ。";
				close;
			}
		case 5:
			mes "[メロディージャック]";
			mes "何だ、まさかお前……";
			mes "私に興味があるのか？";
			mes "フン。";
			mes "あまり首をつっこむと";
			mes "大変なことになるぞ。";
			next;
			switch(select("興味がある","依頼について聞く","取引について聞く","約束とは？")) {
			case 1:
				mes "[メロディージャック]";
				mes "残念だが……";
				mes "私はお前に興味はない。";
				mes "ゆえに、語ることもない。";
				mes "そういうことだ。";
				close;
			case 2:
				mes "[メロディージャック]";
				mes "この私としたことが……";
				mes "やっかいな依頼を受けてしまった。";
				mes "信用問題があるから";
				mes "契約した奴の行方が不明とはいえ";
				mes "一度契約した内容を途中で";
				mes "投げ出すわけにもいかない。";
				next;
				mes "[メロディージャック]";
				mes "それに何より、";
				mes "私のプライドが許さない。";
				mes "契約解除という言葉は";
				mes "余程のことがない限り";
				mes "行わないのがポリシーだ。";
				next;
				mes "[メロディージャック]";
				mes "とはいえお前のような冒険者に";
				mes "依頼の一部を任せることができて";
				mes "良かった。";
				mes "二重契約が駄目とは契約書に";
				mes "書いてなかったし問題はない。";
				close;
			case 3:
				mes "[メロディージャック]";
				mes "正直、この世で信じられるのは";
				mes "何もないぞ。";
				mes "信頼や約束のようなものは";
				mes "全部意味のないことだ。";
				mes "裏切ったり、破ることは";
				mes "至極、簡単だからな。";
				next;
				mes "[メロディージャック]";
				mes "だからこそ……";
				mes "私が信じるのは自分自身と";
				mes "私がした取引だけだ。";
				mes "他人は騙せるが";
				mes "自分自身は騙せない。";
				next;
				mes "[メロディージャック]";
				mes "それに約束や信頼は";
				mes "裏切られると遺恨が残ったり";
				mes "いろいろ面倒だが、";
				mes "取引は報酬をもらったり";
				mes "報復することができる。";
				next;
				mes "[メロディージャック]";
				mes "フン、無駄にしゃべりすぎたか。";
				mes "とにかく私は以上のように";
				mes "考えているということだ。";
				mes "それを理解しろとも、";
				mes "従えとも思っていない。";
				mes "そこだけ了承してほしい。";
				close;
			case 4:
				mes "[メロディージャック]";
				mes "約束について……だと？";
				mes "それを何故お前に話す必要が";
				mes "あるというんだ？";
				mes "あまり詮索すると";
				mes "身を滅ぼすことになるぞ。";
				next;
				mes "[メロディージャック]";
				mes "今は仕方なく表に出ているが、";
				mes "影の中で生きて行くのが";
				mes "本来、私の生き方だ。";
				mes "ゆえに必要なこと以外は";
				mes "特に話すつもりはない。";
				close;
			}
		}
	}
	if(JTB_DAILY == 0) {
		if(Job < Job_RuneKnight || (BaseLevel <= 89 && Job == Job_Summoner)) {
			mes "[メロディージャック]";
			mes "私は今、";
			mes "依頼を受けてくれる人物を探すのに";
			mes "忙しいんだ。";
			mes "邪魔をしないでくれ。";
			next;
			mes "‐^ff0000メロディージャックの依頼は";
			mes "　3次職、4次職、影狼、朧、リベリオン、";
			mes "　限界突破したスーパーノービス、";
			mes "　星帝、ソウルリーパー、";
			mes "　BaseLv90以上のドラム族のみ";
			mes "　受ける事が可能です^000000‐";
			close;
		}
		mes "[メロディージャック]";
		mes "何だ？";
		mes "見て分からないか？";
		mes "私は今、忙しいんだ。";
		mes "邪魔をしないでくれ。";
		close;
	}	else {
		emotion 0;
		mes "[メロディージャック]";
		mes "お前か……。";
		mes "ニュオーズの件以来だな。";
		mes "息災なようで何よりだ。";
		next;
		emotion 0;
		mes "[メロディージャック]";
		mes "どうした、不思議そうな顔をして。";
		mes "私の姿に可笑しい所でも";
		mes "あるのか？";
		next;
		mes "[メロディージャック]";
		mes "ああ、あの時は姿を隠していたからな。";
		mes "私の姿は初めて見るのか。";
		mes "慣れないとは思うが我慢してくれ。";
		next;
		mes "[メロディージャック]";
		mes "さて、本題なんだが……。";
		mes "お前の腕を見込んで頼みがある。";
		next;
		mes "[メロディージャック]";
		mes "見た所、お前はアイグの依頼も";
		mes "受けているんだろう？";
		mes "そこで相談だ。";
		mes "アイグの依頼を解決しながらでいい。";
		mes "私からの依頼も同時に";
		mes "遂行してほしいのだ。";
		next;
		mes "[メロディージャック]";
		mes "私の依頼を受けてくれるなら";
		mes "無論、私からも報酬を出す。";
		mes "アイグからの報酬とは別にだ。";
		mes "お前にとってもこの話は";
		mes "悪い内容ではないはずだ。";
		next;
		mes "[メロディージャック]";
		mes "難しく考えなくていい。";
		mes "アイグの依頼を解決するついでに";
		mes "私の依頼も解決する。";
		mes "それだけだ。";
		mes "簡単なことだろう？";
		next;
		if(select("手伝う","手伝わない") == 2) {
			emotion 0;
			mes "[メロディージャック]";
			mes "そうか。手間をかけさせたな。";
			mes "この話は忘れてくれ。";
			close;
		}
		mes "[メロディージャック]";
		mes "そうか、手伝ってくれるか。";
		mes "助かる。";
		next;
		mes "[メロディージャック]";
		mes "ただ一点だけ、気をつけてほしい。";
		mes "私からの依頼についてだが、";
		mes "アイグには秘密だ。";
		mes "もし依頼内容を話したら";
		mes "お前の身がどうなるかは保証しない。";
		next;
		mes "[メロディージャック]";
		mes "それじゃ、準備ができたら";
		mes "話しかけてくれ。";
		set JTB_DAILY,2;
		close;
	}
OnTouch:
	if(JTB_DAILY == 1) {
		emotion 0;
		mes "[メロディージャック]";
		mes "おい。";
		mes "そこのお前……。";
		mes "ちょっと私の所まで来てくれ。";
		close;
	}
	end;
}

moc_para01.gat,17,77,5	script	アイグ#1	646,{
	if(JTB_DAILY >= 1) {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "こんにちは！";
		mes "何だかうれしい気分なの♪";
		mes "初めて舞台で歌った時みたいに、";
		mes "とても新鮮な感じなの！";
		next;
		switch(select("依頼を受ける","依頼を報告する","依頼を破棄する","話をする")) {
		case 1:
			if(BaseLevel >= 140) {
				cutin "igu02.bmp", 2;
				mes "[アイグ]";
				mes "ありがとうなの♪";
				mes "でも私の依頼は他の人にもう";
				mes "お願いしてしまったの。";
				mes "だから私以外で困っている人を";
				mes "助けてあげてほしいの。";
				next;
				cutin "igu02.bmp", 255;
				mes "‐^ff0000アイグの依頼は";
				mes "　BaseLv140以上では受けることが";
				mes "　できません^000000‐";
				close;
			}
			if(checkquest(96815)) {
				if(!(checkquest(96815) & 0x2)) {
					mes "[アイグ]";
					mes "ありがとうなの。";
					mes "でも、調べてもらったばかりだし、";
					mes "もう少し時間が経過してから";
					mes "お願いしたいの。";
					close2;
					cutin "igu01.bmp", 255;
					end;
				}
			}
			if(checkquest(13107)) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "タナトスタワーは";
				mes "危険な場所だから";
				mes "気を付けて探索して欲しいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			if(checkquest(13108)) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "フレイヤ大神殿は";
				mes "危険な場所だから";
				mes "気を付けて探索して欲しいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			if(checkquest(13109)) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "名もなき島は";
				mes "危険な場所だから";
				mes "気を付けて探索して欲しいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			if(checkquest(13110)) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "アビスレイクは";
				mes "危険な場所だから";
				mes "気を付けて探索して欲しいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			if(checkquest(13111) || checkquest(13112) || checkquest(13113) || checkquest(13114)) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "探索は終わったの？";
				mes "まずは結果を報告してほしいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			if(checkquest(116508) == 0) {
				cutin "igu03.bmp", 2;
				mes "[アイグ]";
				mes "あの人を探してくれるの？";
				mes "ありがと、なの♪";
				next;
				cutin "igu01.bmp", 2;
				mes "[アイグ]";
				mes "私が探している人は";
				mes "あちこちを探検して回っている";
				mes "冒険者なの。いつもは私が";
				mes "ツアーから帰ってくるころには";
				mes "ここに戻ってくるはずなのに、";
				mes "今回はいないから心配なの。";
				next;
			} else {
				cutin "igu03.bmp", 2;
				mes "[アイグ]";
				mes "ニュオーズを探してくれるの？";
				mes "ありがと、なの♪";
				next;
				cutin "igu01.bmp", 2;
				mes "[アイグ]";
				mes "ニュオーズはいつもは私が";
				mes "ツアーから帰ってくるころには";
				mes "ここに戻ってくるはずなのに、";
				mes "今回はいないから心配なの。";
				next;
			}
			mes "[アイグ]";
			mes "確かにちょっと放浪癖が";
			mes "ある人なんだけど……だから、";
			mes "あの人を見かけたっていう場所を";
			mes "探してみて欲しいの。";
			mes "気に入った場所には何度も行く人だから";
			mes "もしかしたら居るかもしれないの！";
			next;
			cutin "igu04.bmp", 2;
			mes "[アイグ]";
			mes "えっと、このリストが";
			mes "いろんな冒険者の人から聞いた";
			mes "あの人を見かけたっていう場所なの。";
			next;
			set '@sel,select("タナトスタワー探索","フレイヤ大神殿探索","名もなき島探索","アビスレイク探索");
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			switch('@sel) {
			case 1:
				mes "タナトスタワー……。";
				break;
			case 2:
				mes "フレイヤ大神殿……。";
				break;
			case 3:
				mes "名もなき島……。";
				break;
			case 4:
				mes "アビスレイク……。";
				break;
			}
			mes "そこならあの人がいるかもしれないの！";
			mes "お願いできる？";
			next;
			if(select("受ける","やめる") == 2) {
				cutin "igu05.bmp", 2;
				mes "[アイグ]";
				mes "なの……？";
				mes "残念なの……。";
				mes "気が変わったらまた";
				mes "声をかけてほしいの。";
				close2;
				cutin "igu05.bmp", 255;
				end;
			}
			mes "[アイグ]";
			mes "ありがとなの！";
			mes "危険な場所だから";
			mes "気を付けて探索して欲しいの。";
			switch('@sel) {
			case 1:
				setquest 13107;
				break;
			case 2:
				setquest 13108;
				break;
			case 3:
				setquest 13109;
				break;
			case 4:
				setquest 13110;
				break;
			}
			close2;
			cutin "igu01.bmp", 255;
			end;
		case 2:
			set '@quest,0;
			if(checkquest(13111)) {
				set '@quest,13111;
			}
			if(checkquest(13112)) {
				set '@quest,13112;
			}
			if(checkquest(13113)) {
				set '@quest,13113;
			}
			if(checkquest(13114)) {
				set '@quest,13114;
			}
			if('@quest == 0) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "なの？";
				mes "完了している依頼は無いみたい。";
				mes "もう一度よく確認してみてほしいの。";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "おかえりなさい！";
			mes "あの人は見つからなかった";
			mes "みたいだけど、";
			mes "あなたが無事に帰ってきてくれたから";
			mes "良かったの♪";
			next;
			mes "[アイグ]";
			mes "依頼のお礼を渡したいんだけど、";
			mes "報酬を渡してもいい？";
			next;
			if(select("はい","いいえ") == 2) {
				cutin "igu04.bmp", 2;
				mes "[アイグ]";
				mes "なの？";
				mes "報酬を受け取れるようになったら";
				mes "また来てほしいの♪";
				close2;
				cutin "igu04.bmp", 255;
				end;
			}
			setquest 96815;
			delquest '@quest;
			switch('@quest) {
			case 13111:
				setquest 96816;
				break;
			case 13112:
				setquest 96817;
				break;
			case 13113:
				setquest 96818;
				break;
			case 13114:
				setquest 96819;
				break;
			}
			getexp 500000,0,0;
			getexp 500000,0,0;
			cutin "igu02.bmp", 2;
			mes "[アイグ]";
			mes "本当にありがとなの！";
			mes "また良かったら手伝ってほしいの♪";
			close2;
			cutin "igu02.bmp", 255;
			end;
		case 3:
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "依頼したお仕事を破棄するの？";
			mes "忙しかったの？";
			mes "ごめんね、ありがとうなの。";
			next;
			mes "[アイグ]";
			mes "破棄の方法は2種類あるの。";
			mes "好きな方を選んで。";
			next;
			if(select("依頼の破棄","報告記録の破棄") == 1) {
				set '@quest,0;
				set '@quest,'@quest+checkquest(13107);
				set '@quest,'@quest+checkquest(13108);
				set '@quest,'@quest+checkquest(13109);
				set '@quest,'@quest+checkquest(13110);
				set '@quest,'@quest+checkquest(13111);
				set '@quest,'@quest+checkquest(13112);
				set '@quest,'@quest+checkquest(13113);
				set '@quest,'@quest+checkquest(13114);
				if('@quest == 0) {
					cutin "igu04.bmp", 2;
					mes "[アイグ]";
					mes "なの？";
					mes "依頼したお仕事は無いみたい。";
					mes "もう一度よく確認してみてほしいの。";
					close2;
					cutin "igu04.bmp", 255;
					end;
				}
				mes "[アイグ]";
				mes "依頼の破棄は";
				mes "今あなたが受けている依頼の";
				mes "^FF0000完了しているものを含め、";
				mes "全てを破棄することになるの。^000000";
				mes "報告記録は残るの。";
				next;
				mes "[アイグ]";
				mes "完了している依頼を破棄してしまうと";
				mes "報酬を渡すことができなくなるの。";
				mes "^FF0000完了している依頼は先に報告をして";
				mes "報酬を受け取ってから、";
				mes "依頼の破棄をしてほしいの。^000000";
				next;
				mes "[アイグ]";
				mes "本当に依頼を破棄してもいい？";
				next;
				if(select("はい","いいえ") == 2) {
					cutin "igu02.bmp", 2;
					mes "[アイグ]";
					mes "続けてくれるの？";
					mes "忙しいのに、ありがとうなの！";
					mes "時間がかかっても構わないから";
					mes "お願いしたいの。";
					close2;
					cutin "igu02.bmp", 255;
					end;
				}
				delquest 13107;
				delquest 13108;
				delquest 13109;
				delquest 13110;
				delquest 13111;
				delquest 13112;
				delquest 13113;
				delquest 13114;
				mes "[アイグ]";
				mes "依頼したお仕事は取り下げたの。";
				mes "また気が向いたら";
				mes "手伝ってくれると嬉しいの！";
				close2;
				cutin "igu01.bmp", 255;
				end;
			} else {
				set '@quest,0;
				set '@quest,'@quest+checkquest(96816);
				set '@quest,'@quest+checkquest(96817);
				set '@quest,'@quest+checkquest(96818);
				set '@quest,'@quest+checkquest(96819);
				if('@quest == 0) {
					cutin "igu04.bmp", 2;
					mes "[アイグ]";
					mes "なの？";
					mes "完了している報告の記録は";
					mes "無いみたい。";
					mes "もう一度よく確認してみてほしいの。";
					close2;
					cutin "igu04.bmp", 255;
					end;
				}
				mes "[アイグ]";
				mes "報告記録の破棄は";
				mes "今あなたが^FF0000報告している依頼の";
				mes "全てを破棄することになるの。^000000";
				next;
				cutin "igu02.bmp", 255;
				mes "‐報告記録の破棄は";
				mes "^FF0000　完了報告を行ったクエストを";
				mes "　全て消去します。^000000";
				mes "　特別報酬を得るためには、";
				mes "^FF0000　再度4種類のクエストを受け、";
				mes "　完了する必要があります^000000‐";
				next;
				cutin "igu01.bmp", 2;
				mes "[アイグ]";
				mes "本当に報告記録を破棄してもいい？";
				next;
				if(select("はい","いいえ") == 2) {
					mes "[アイグ]";
					mes "報告記録の破棄はやめたの。";
					mes "時間がかかっても構わないから、";
					mes "色々な所を探してほしいの。";
					close2;
					cutin "igu01.bmp", 255;
					end;
				}
				delquest 96816;
				delquest 96817;
				delquest 96818;
				delquest 96819;
				mes "[アイグ]";
				mes "あなたが報告した記録は";
				mes "全て破棄したの。";
				mes "また気が向いたら";
				mes "手伝ってくれると嬉しいの！";
				close2;
				cutin "igu01.bmp", 255;
				end;
			}
		case 4:
			cutin "igu01.bmp", 2;
			mes "[アイグ]";
			mes "私が団長を務めるたんぽぽ楽団は";
			mes "世界のいろんな場所を巡りながら、";
			mes "人々に癒しの音楽を伝えるギルドなの♪";
			next;
			cutin "igu02.bmp", 2;
			mes "[アイグ]";
			mes "実際に私たちの歌は魔法ではないけど、";
			mes "人々の力になるのは確かなことなの。";
			mes "そして私たちもみんなから、";
			mes "言葉や笑顔で元気を貰っているの。";
			mes "私たちの歌はそうやって";
			mes "世界を巡っているの♪";
			close2;
			cutin "igu02.bmp", 255;
			end;
		}
	}
	if(Job < Job_RuneKnight || (BaseLevel <= 89 && Job == Job_Summoner)) {
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "こんにちは♪";
		mes "楽園団の冒険者は";
		mes "優しい人ばかりだと聞いたの。";
		mes "もし良かったら私のお願いを";
		mes "聞いてくれる人を探しているの。";
		next;
		cutin "igu04.bmp", 2;
		mes "[アイグ]";
		mes "でもあなたにはまだ";
		mes "お願いできそうにないの……。";
		mes "とても危険な依頼だから、";
		mes "もう少し強くなってから";
		mes "私のお願いを聞いてほしいの！";
		next;
		cutin "igu04.bmp", 255;
		mes "‐^ff0000アイグの依頼は";
		mes "　3次職、4次職、影狼、朧、リベリオン、";
		mes "　限界突破したスーパーノービス、";
		mes "　星帝、ソウルリーパー、";
		mes "　BaseLv90以上のドラム族のみ";
		mes "　受ける事が可能です^000000‐";
		close;
	}
	if(checkquest(116508) == 0) {
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "こんにちは♪";
		mes "楽園団の冒険者は";
		mes "優しい人ばかりだと聞いたの。";
		mes "もし良かったら私のお願いを";
		mes "聞いてほしいのなの。";
		next;
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "先ずは自己紹介なの。";
		mes "私は^FF0000たんぽぽ楽団^000000の団長を任されている";
		mes "^FF0000アイグ^000000なの♪";
		next;
		mes "[アイグ]";
		mes "私は長いライブツアーから";
		mes "今帰ってきたところなの。";
		mes "行った所が無いくらい";
		mes "いろんな場所で歌ってきたの♪";
		mes "旅をした後って";
		mes "誰かに話したくならない？";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "私は毎回そうなの。";
		mes "だから帰ったら真っ先に会って";
		mes "旅の話したかった人がいるんだけど、";
		mes "その人に会いに行ったら";
		mes "他の人に暫く前から行方が";
		mes "わからないって言われたの。";
		next;
		mes "[アイグ]";
		mes "だから……";
		mes "楽園団に頼みにきたの……。";
		mes "その人を探してくださいって。";
		mes "だけど……";
		next;
		mes "[アイグ]";
		mes "行方不明の人を探してくれる、";
		mes "担当者もいないし、人手も足りないし、";
		mes "みんな忙しいといわれて、";
		mes "全然相手にしてくれないの。";
		mes "だからといって待つのも嫌だし、";
		mes "直接依頼をする事にしたの！";
		next;
		mes "[アイグ]";
		mes "……ここまで話を聞いてくれたのも";
		mes "あなたが初めてなの。";
		mes "そうだ！";
		mes "迷惑を承知であなたに";
		mes "今回の依頼をお願いしたいの。";
		mes "お願いなの……！";
		next;
	}	else {
		cutin "igu02.bmp", 2;
		mes "[アイグ]";
		mes "久しぶりなの♪";
		mes "元気そうでよかったの！";
		next;
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "それよりも大変なの！";
		mes "ニュオーズがまたどこかへ";
		mes "いなくなっちゃったの！";
		next;
		mes "[アイグ]";
		mes "楽園団にニュオーズを";
		mes "探してくれるように";
		mes "頼みにきたんだけど";
		mes "担当者も居なくて忙しいって";
		mes "断られちゃったの……。";
		next;
		cutin "igu01.bmp", 2;
		mes "[アイグ]";
		mes "だから……自分で直接、";
		mes "冒険者の人にお願いする事にしたの！";
		next;
		mes "[アイグ]";
		mes "あなたなら実力も十分だし安心なの！";
		mes "迷惑かもしれないけど、";
		mes "もし良かったら私のお願いを";
		mes "聞いてほしいの。";
		mes "お願いなの……。";
		next;
	}
	if(select("手伝う","手伝わない") == 2) {
		cutin "igu05.bmp", 2;
		mes "[アイグ]";
		mes "なの……？";
		mes "ごめんなさい……。";
		mes "あなたにも都合があるの。";
		mes "話を聞いてくれて";
		mes "ありがとうなの……。";
		close2;
		cutin "igu05.bmp", 255;
		end;
	}
	cutin "igu03.bmp", 2;
	mes "[アイグ]";
	mes "よかった！　引き受けてくれて";
	mes "とっても嬉しいの！";
	mes "今の私にはあなたしか";
	mes "頼れる人が居ないの……。";
	next;
	cutin "igu02.bmp", 2;
	mes "[アイグ]";
	mes "依頼を受ける準備ができたら";
	mes "もう一度話しかけて欲しいの。";
	mes "依頼内容を整理して、";
	mes "詳しい話をするの。";
	close2;
	cutin "igu02.bmp", 255;
	set JTB_DAILY,1;
	end;
}

thana_step.gat,167,292,5	script	冒険者の痕跡#1	649,{
	if(checkquest(13107)) {
		mes "‐誰かが留まっていた痕跡があるが、";
		mes "　誰なのかはわからない。";
		mes "　戻ってアイグに報告しよう‐";
		delquest 13107;
		setquest 13111;
		close;
	}
	mes "‐誰かが留まっていた痕跡がある‐";
	close;
}

ra_san05.gat,265,69,5	script	冒険者の痕跡#2	649,{
	if(checkquest(13108)) {
		mes "‐誰かが留まっていた痕跡があるが、";
		mes "　誰なのかはわからない。";
		mes "　戻ってアイグに報告しよう‐";
		delquest 13108;
		setquest 13112;
		close;
	}
	mes "‐誰かが留まっていた痕跡がある‐";
	close;
}

abbey02.gat,155,290,5	script	冒険者の痕跡#3	649,{
	if(checkquest(13109)) {
		mes "‐誰かが留まっていた痕跡があるが、";
		mes "　誰なのかはわからない。";
		mes "　戻ってアイグに報告しよう‐";
		delquest 13109;
		setquest 13113;
		close;
	}
	mes "‐誰かが留まっていた痕跡がある‐";
	close;
}

abyss_03.gat,102,140,5	script	冒険者の痕跡#4	649,{
	if(checkquest(13110)) {
		mes "‐誰かが留まっていた痕跡があるが、";
		mes "　誰なのかはわからない。";
		mes "　戻ってアイグに報告しよう‐";
		delquest 13110;
		setquest 13114;
		close;
	}
	mes "‐誰かが留まっていた痕跡がある‐";
	close;
}
