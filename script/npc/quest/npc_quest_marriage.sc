//====================================================================
//Ragnarok Online EP4.0(J) Marriage System      V2.0
//
//  ■ @event_marry -> 受付フラグ 0or1
//  ■ @defend -> タイムアップフラグ、嫁にのみ仕込む
//====================================================================
prt_church.gat,94,100,4	script	結婚コンパニオン	71,{
	cutin "wedding_marry01",2;
	mes "[ハッピーマリー]";
	mes "こんにちは。";
	mes "結婚コンパニオンの";
	mes "ハッピーマリーです。";
	if(Upper == UPPER_BABY) {
		mes "あら、どうされました？";
		next;
		if(select("結婚したいです！","いや、何でもないです") == 2) {
			mes "[ハッピーマリー]";
			mes "はい、わかりました。";
			mes "では、お気をつけて。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		mes "[ハッピーマリー]";
		mes "申し訳ありません。";
		mes "養子になられた方には、結婚を";
		mes "ご遠慮して頂いております。";
		mes "ご両親に親孝行しながら幸せに";
		mes "なさってくださいね。";
		close2;
		cutin "wedding_marry02",255;
		end;
	}
	next;
	mes "[ハッピーマリー]";
	mes "幸せを夢見るカップルなら";
	mes "やっぱり結婚式を挙げたいですよね？";
	mes "あら？　もしかして……";
	mes "結婚したい方がいらっしゃるのですか？";
	next;
	switch (select("結婚式について聞きたい","結婚式の手順はどうなりますか","結婚式を申し込みたい","私は、無敵のソロ軍団だ！")) {
	case 1:
		mes "[ハッピーマリー]";
		mes "以前は、国王陛下の進行で";
		mes "結婚式が行われていたのですが、";
		mes "現在は、諸外国との国交が盛んになり、";
		mes "御忙しい為か国政に戻られております。";
		next;
		mes "[ハッピーマリー]";
		mes "その代わり、これからは";
		mes "ルーンミッドガッツ王国の主教である";
		mes "ボマルス様が結婚式の進行を";
		mes "担当する事になりました。";
		next;
		mes "[ハッピーマリー]";
		mes "主教様は、ソロだった多くの人々を";
		mes "ゴールインさせた事で、";
		mes "‘愛の主教　ラブプリースト！’という";
		mes "あだ名が付いてますのよ！　ホホッ";
		next;
		mes "[ハッピーマリー]";
		mes "プロポーズは慎重に、";
		mes "かつ、丁寧に行わなければいけません！";
		mes "冗談で結婚しようなんて言ったら……";
		mes "一生恨まれますよ！";
		next;
		mes "[ハッピーマリー]";
		mes "結婚した二人は、";
		mes "この世を去るその日まで";
		mes "一緒なのです。";
		next;
		mes "[ハッピーマリー]";
		mes "結婚は、異性間のみ許されております。";
		mes "稀に、同姓同士や異種族間での結婚を";
		mes "希望する方もいらっしゃいますが……";
		next;
		mes "[ハッピーマリー]";
		mes "ここ、ルーンミッドガッツ王国の";
		mes "主教様がお認めにならないので、";
		mes "ご了承くださいませ。";
		next;
		mes "[ハッピーマリー]";
		mes "未来を約束した方がいらっしゃるなら、";
		mes "プロポーズしてみたらいかがですか？";
		mes "幸せな未来を夢見る恋人の皆さんに";
		mes "たくさんの祝福が訪れる事を";
		mes "祈ります!!";
		close2;
		cutin "wedding_marry01",255;
		end;
	case 2:
		mes "[ハッピーマリー]";
		mes "まず、新郎と新婦さん、お二人とも";
		mes "私に結婚の申し込みをしたか、";
		mes "確認してください。";
		mes "勿論、未婚者同士のみですよ！";
		next;
		mes "[ハッピーマリー]";
		mes "申し込みができましたら、";
		mes "二人だけのパーティーを組み、";
		mes "主教様に会いに行ってください。";
		next;
		mes "[ハッピーマリー]";
		mes "主教様には、必ず^0000FF男性^000000が先に話しを";
		mes "してください。";
		mes "そして、結婚したい女性の名前を";
		mes "正確にお伝えください。";
		mes "名前を間違えますと、結婚できません。";
		mes "気をつけてくださいね！";
		next;
		mes "[ハッピーマリー]";
		mes "新郎さんの話が終わったら、";
		mes "次は、新婦さんの番です。";
		mes "主教様に話を掛けてください、";
		mes "すると、新郎さんの名前を聞かれます。";
		mes "間違えずに、正確に伝えてください！";
		next;
		mes "[ハッピーマリー]";
		mes "お互い結婚相手の名前が正確に伝わると";
		mes "指輪の交換が行われます。";
		mes "その瞬間から、二人は永遠の愛で";
		mes "結ばれる事になるのです！";
		mes "なんて素敵なんでしょう!?";
		next;
		mes "[ハッピーマリー]";
		mes "勿論、稀に指輪交換の段階で";
		mes "断られる事もありますけど……";
		mes "だからって、悲しまないでくださいね。";
		next;
		mes "[ハッピーマリー]";
		mes "結婚を申し込む方がたくさんいる時は、";
		mes "順番を守っていただく事になります。";
		mes "主教様は、同時に複数のカップルの";
		mes "結婚式を行いません。";
		next;
		mes "[ハッピーマリー]";
		mes "最後に一つ！";
		mes "主教様に名前を伝える時は、";
		mes "素早く行う必要があります。";
		mes "^ff0000最初に新郎が声を掛けてから3分以内に";
		mes "すべての過程を終わらせてください。^000000";
		next;
		mes "[ハッピーマリー]";
		mes "もし、3分以内に終わらない場合は、";
		mes "結婚式式が中断され、";
		mes "再開する事が出来なくなります。";
		next;
		mes "[ハッピーマリー]";
		mes "また、結婚したい相手の名前ですが、";
		mes "結婚式の前に、必ず相手の名前の";
		mes "正確な綴りをご確認ください。";
		next;
		mes "[ハッピーマリー]";
		mes "確認の方法としましては、";
		mes "相手の方に耳打ちを行ってみると";
		mes "よろしいと思います。";
		mes "相手に通じれば、その名前が";
		mes "正しい綴りですし、通じなければ、";
		mes "名前が間違っている可能性があります。";
		next;
		mes "[ハッピーマリー]";
		mes "まず、相手に一度耳打ちをして、";
		mes "チャットウィンドウ左部のボタンを";
		mes "押します。";
		mes "すると、耳打ちリストに相手の名前が";
		mes "表示されますので、選択しましょう。";
		next;
		mes "[ハッピーマリー]";
		mes "相手の名前がボタンの左に";
		mes "表示されますので、その名前を";
		mes "Ctrl+Cでコピーしておきます。";
		mes "そうすれば、報告の際に";
		mes "Shift＋Insertで相手の名前を";
		mes "呼び出す事ができます。";
		next;
		mes "[ハッピーマリー]";
		mes "1)相手と耳打ち会話をする";
		mes "2)耳打ちリストに表示された";
		mes "　相手の名前を選択する";
		mes "3)チャットウィンドウの左下に";
		mes "　表示された相手の名前を";
		mes "　Ctrl+Cでコピーする。";
		next;
		mes "[ハッピーマリー]";
		mes "この方法で、相手の名前を";
		mes "確実に覚える事ができますし、";
		mes "主教様に報告する時にも";
		mes "使っていただけると思います。";
		next;
		mes "[ハッピーマリー]";
		mes "説明だけですと、わかりづらいですし";
		mes "1度、試してみましょうか。";
		next;
		mes "[ハッピーマリー]";
		mes "Ctrl＋Cでコピーしたものを";
		mes "Shift＋Insertキーで";
		mes "呼び出してみてください。";
		mes "よろしいですか？";
		next;
		input '@test$;
		mes "[ハッピーマリー]";
		mes "どうです、出来ましたか？";
		next;
		mes "[ハッピーマリー]";
		mes "では、もし結婚したいと思うお相手が";
		mes "いましたら、申し込みを是非どうぞ。";
		close2;
		cutin "wedding_marry01",255;
		end;
	case 3:
		cutin "wedding_marry02",2;
		mes "[ハッピーマリー]";
		mes "結婚をするためには、";
		mes "いくつか条件がございます。";
		next;
		mes "[ハッピーマリー]";
		mes "まず、結婚するには^3377FFベースレベルが";
		mes "45以上^000000でなければなりません。";
		mes "そして、新郎新婦二人とも、申し込みを";
		mes "していただく必要がございます。";
		next;
		mes "[ハッピーマリー]";
		mes "申し込みの際、男性は^3377FF1,300,000zeny^000000と";
		mes "^3377FFタキシード1着^000000、女性は^3377FF1,200,000zeny^000000と";
		mes "^3377FFウェディングドレス1着^000000が必要です。";
		next;
		mes "[ハッピーマリー]";
		mes "あれ……？";
		mes "あ！　大事な物を忘れていました！";
		next;
		mes "[ハッピーマリー]";
		mes "申し込みの際に^3377FFダイヤの指輪^000000を";
		mes "二人分、用意してください。";
		mes "それが、結婚指輪となります。";
		mes "指輪は、新郎と新婦で一つずつ";
		mes "持ってくださいね。";
		next;
		mes "[ハッピーマリー]";
		mes "以上の品が全てそろっているのを";
		mes "確認しましたら、申し込み書に";
		mes "自分の名前を記入していただきます。";
		next;
		mes "[ハッピーマリー]";
		mes "二人とも申し込みが済みましたら";
		mes "結婚式を挙げる事ができます。";
		mes "申し込みをなさいますか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[ハッピーマリー]";
			mes "今日も幸せな一日にな～れっ！";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if(PartnerId) {
			mes "[ハッピーマリー]";
			mes "すでに結婚しておられるようですね。";
			mes "重婚は認めておられません。";
			next;
			mes "[ハッピーマリー]";
			mes "それ以前に、一生を共にするという";
			mes "約束を破るという事が、";
			mes "どのような意味を持つか……";
			mes "相手のお気持ちを";
			mes "考えた事がありますか？";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if(@event_marry) {
			mes "[ハッピーマリー]";
			mes "あら？";
			mes "すでに申し込みされているようですね。";
			mes "この奥に主教様がいらっしゃいます。";
			mes "主教様の元へと赴き、";
			mes "結婚式の順番をお待ちください。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if(BaseLevel<45) {
			mes "[ハッピーマリー]";
			mes "プロポーズなさるより先に、ご自分の";
			mes "鍛練が必要なようです。結婚には義務や";
			mes "責任が招じます。相手の方を守れるくら";
			mes "い強くなってから、いらして下さい。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if(countitem(2613)<1) {
			mes "[ハッピーマリー]";
			mes "結婚指輪に使うダイヤの指輪を";
			mes "忘れていらっしゃったようですね。";
			mes "ダイヤの指輪をお持ちになってから";
			mes "また、お申し込みください。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if((Sex==0 && Zeny<1200000) || (Sex==1 && Zeny<1300000)) {
			mes "[ハッピーマリー]";
			mes "大変申し訳ございませんが、";
			mes "結婚式の費用として";
			if(Sex==0)
				mes "1,200,000zenyが、必要です。";
			else
				mes "1,300,000zenyが、必要です。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		if((Sex==0 && countitem(2338)<1) || (Sex==1 && countitem(7170)<1)) {
			mes "[ハッピーマリー]";
			mes "あら？";
			if(Sex==0) {
				mes "ウェディングドレスが、ありませんね？";
				mes "結婚式を挙げるのに、";
				mes "花嫁が、そのような出で立ちでは……";
			}
			else {
				mes "タキシードが、ありませんね？";
				mes "結婚式を挙げるのに、";
				mes "花婿が、そのような出で立ちでは……";
			}
			mes "忘れずに準備してきてくださいませ。";
			close2;
			cutin "wedding_marry02",255;
			end;
		}
		mes "[ハッピーマリー]";
		mes "御結婚、お祝い申し上げます！";
		next;
		mes "[ハッピーマリー]";
		mes "それでは、これが申し込み書です。";
		mes "ここに自分の名前を記入してください。";
		while(1) {
			next;
			input '@name$;
			if('@name$ != strcharinfo(0)) {
				mes "[ハッピーマリー]";
				mes "まあまあ！";
				mes "自分の名前を正しく書けないんですか？";
				mes "本当に結婚するつもりなら、";
				mes "名前くらい正確に名乗ってください！";
				mes "もう一度、自分の名前を";
				mes "正確に記入してください。";
				continue;
			}
			break;
		}
		mes "[ハッピーマリー]";
		mes "はい、申し込み書を承りました。";
		mes "後程、主教様には、";
		mes "結婚相手の名前も報告いたします。";
		mes "結婚式の前に相手の名前を";
		mes "名前を正確に言えるよう、";
		mes "準備しておく事をお勧めいたします。";
		next;
		mes "[ハッピーマリー]";
		mes "では、結婚相手の方も";
		mes "申し込みを済ませましたら、";
		mes "二人だけでパーティーを組み、";
		mes "奥にいらっしゃる主教様の元へ赴き、";
		mes "話しかけてください。";
		next;
		mes "[ハッピーマリー]";
		mes "では、お幸せに～";
		emotion 3;
		if(Sex==0) {
			set Zeny,Zeny-1200000;
			delitem 2338,1;
		}
		else {
			set Zeny,Zeny-1300000;
			delitem 7170,1;
		}
		delitem 2613,1;
		set @event_marry,1;
		close2;
		cutin "wedding_marry02",255;
		end;
	case 4:
		cutin "wedding_marry02",2;
		emotion 23;
		hideoffnpc "ソロ軍団#プロンテラ";
		hideoffnpc "ソロ軍団#ゲフェン";
		hideoffnpc "ソロ軍団#モロク";
		hideoffnpc "ソロ軍団#フェイヨン";
		hideoffnpc "ソロ軍団#アマツ";
		hideoffnpc "ソロ軍団#コンロン";
		emotion 27,"ソロ軍団#プロンテラ";
		emotion 27,"ソロ軍団#ゲフェン";
		emotion 27,"ソロ軍団#モロク";
		emotion 27,"ソロ軍団#フェイヨン";
		emotion 27,"ソロ軍団#アマツ";
		emotion 27,"ソロ軍団#コンロン";
		mes "[ソロ軍団]";
		mes "精錬は1人で出来ちゃうぞ！";
		mes "ダンジョンでパーティーは贅沢だ！";
		mes "私には心に決めたNPCがいる！";
		mes "生まれて転職まで独りでした！";
		mes "クリスマスにはシングルベ～ル！";
		mes "私たちは無敵のソロ軍団！";
		next;
		hideonnpc "ソロ軍団#プロンテラ";
		hideonnpc "ソロ軍団#ゲフェン";
		hideonnpc "ソロ軍団#モロク";
		hideonnpc "ソロ軍団#フェイヨン";
		hideonnpc "ソロ軍団#アマツ";
		hideonnpc "ソロ軍団#コンロン";
		emotion 4;
		close2;
		cutin "wedding_marry02",255;
		end;
	}
OnInit:
	hideonnpc "ソロ軍団#プロンテラ";
	hideonnpc "ソロ軍団#ゲフェン";
	hideonnpc "ソロ軍団#モロク";
	hideonnpc "ソロ軍団#フェイヨン";
	hideonnpc "ソロ軍団#アマツ";
	hideonnpc "ソロ軍団#コンロン";
	end;
}

//========================================================================================
prt_church.gat,100,128,4	script	主教	60,{
	//1なら問答無用で弾く、2で且つ嫁以外なら弾く
	cutin "wedding_bomars01",2;
	if('flag==1) {
		mes "[ボマルス]";
		mes "他の結婚式が進行中だ。";
		mes "順番をお待ちなさい。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if('flag==2 && strcharinfo(0) != 'bride$) {
		mes "[ボマルス]";
		mes "新郎" +'groom$+ "と";
		mes "新婦" +'bride$+ "の";
		mes "結婚式が進行中だ。";
		mes "静かに。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if(PartnerId) {
		mes "[ボマルス]";
		mes "いつまでも、お幸せに。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if(Upper == UPPER_BABY) {
		mes "[ボマルス]";
		mes "結婚に憧れるのは、良い事だ。";
		mes "夢を持つ事も大事だが、";
		mes "そなたの両親のように良人を";
		mes "見つける事も大事だぞ。";
		mes "大人になってから、また来なさい。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if(@event_marry==0) {
		mes "[ボマルス]";
		mes "結婚を望むなら、結婚式を挙げる二人で";
		mes "申し込みから済ませてきなさい。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	getpartymember getcharid(1);
	for(set '@i,0; '@i<2; set '@i,'@i+1) {
		if($@partymembername$['@i] != strcharinfo(0))
			set '@another$,$@partymembername$['@i];		//PT内に居る相手の名前を一時保存
	}
	if($@partymembercount != 2 || readparam(Sex,'@another$) == 1) {	//2人PTじゃない、もしくは相手が男かオフライン
		mes "[ボマルス]";
		mes "結婚を望むなら、結婚式を挙げる二人で";
		mes "パーティーを結成しなさい。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if(Sex==1) {	//申し込みは新郎から
		set 'flag,1;
		initnpctimer;	//手続きは3分以内
		set 'groom$,strcharinfo(0);
		mes "[ボマルス]";
		mes "幸せな未来を夢見る若者よ。";
		mes "これから二人で歩む人生が至福に満ち、";
		mes "共に過ごす時が至宝となるよう……";
		next;
		announce "主教: 新郎" +'groom$+ "よ、汝に問う……",9;
		mes "[ボマルス]";
		mes 'groom$+ "よ。";
		mes "汝の将来を明るく照らし、生涯を";
		mes "共に歩まんとする女性の名前を";
		mes "ここに告げよ。";
		next;
		input 'bride$;
		//もし嫁がログインしてるなら仕込まれたタイムアップフラグを堕ろす
		if(attachrid(getcharid(3,'bride$))) {
			set @defend,0;
			detachrid;
		}
		if(attachrid(getcharid(3,'groom$))) {	//再度アタッチ
			//PTが解体されていようが嫁がすでにログアウト状態であろうが関係なし！性転換は考慮しない
			announce "主教: 汝、その富める時も、貧しき時も、病めるときも、健やかなる時も",9;
			mes "[ボマルス]";
			mes "新郎" +'groom$+ "よ。";
			mes "汝、その富める時も、貧しき時も、";
			mes "病めるときも、健やかなる時も、";
			mes 'bride$+ "を愛し";
			mes "敬い、慰め、助け、その命の限り";
			mes "堅く節操を守る事を誓うか？";
			next;
			announce "主教: " +'bride$+ "を愛し、敬い、慰め、助け、その命の限り堅く節操を守る事を誓うか？",9;
			menu "誓います",-;
			announce "主教: 新郎" +'groom$+ "が新婦" +'bride$+ "に愛を誓った……",9;
			mes "[ボマルス]";
			mes "うむ！";
			mes "では、新婦に問うてみよう。";
			set 'flag,2;
			set @event_marry,0;	//フラグ解放
		}
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	//新婦側の処理
	if('flag==0) {
		mes "[ボマルス]";
		mes "先ず、新郎から私に報告なさい。";
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	mes "[ボマルス]";
	mes "幸せな未来を夢見る若者よ。";
	mes "これから二人で歩む人生が至福に満ち、";
	mes "共に過ごす時が至宝となるよう……";
	next;
	announce "主教: 新婦" +'bride$+ "よ、汝に問う……",9;
	mes "[ボマルス]";
	mes 'bride$+ "よ。";
	mes "汝を常に守り、生涯を共に";
	mes "歩まんとする男性の名前は";
	mes 'groom$+ "か？";
	next;
	if(select("はい","いいえ")==2) {
		cutin "wedding_bomars03",2;
		announce "主教: 結婚式は取り消された。次の結婚式を行う者よ、前へ。",9;
		mes "[ボマルス]";
		mes "汝の愛する者の名前を確認し、";
		mes "また結婚式の申し込みをなさい。";
		stopnpctimer;
		set 'flag,0;
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	announce "主教: 汝、その富める時も、貧しき時も、病めるときも、健やかなる時も",9;
	mes "[ボマルス]";
	mes "新婦" +'bride$+ "よ。";
	mes "汝、その富める時も、貧しき時も、";
	mes "病めるときも、健やかなる時も、";
	mes 'groom$+ "を愛し";
	mes "敬い、慰め、助け、その命の限り";
	mes "堅く節操を守ることを誓うか。";
	announce "主教: " +'groom$+ "を愛し、敬い、慰め、助け、その命の限り堅く節操を守る事を誓うか？",9;
	next;
	if(select("誓います","……やっぱりやめます")==2) {
		cutin "wedding_bomars03",2;
		announce "主教#w: 新婦" +'bride$+ "は新郎" +'groom$+ "との愛の誓いを踏み留まった……",9;
		mes "[ボマルス]";
		mes "そうか……";
		mes "決断するには、";
		mes "まだ、心の準備が足りぬか。";
		mes "もし考え直す事があれば、";
		mes "またお出でなさい。";
		stopnpctimer;
		set 'flag,0;
		close2;
		cutin "wedding_bomars03",255;
		end;
	}
	if(@defend) {	//タイムアップしてるかどうか最終チェック
		set @event_marry,0;
		cutin "wedding_bomars03",255;
		close;
	}
	//結婚処理
	if(getcharid(3,'groom$)<=0) {	//新郎がマリッジブルーでログアウトしてたら指輪渡せない！
		stopnpctimer;
		set 'flag,0;
		set @event_marry,0;
		cutin "wedding_bomars03",255;
		close;
	}
	set '@dummy,marriage('groom$);
	getitem 2635,1,0;
	getitem 2634,1,0,getcharid(3,'groom$);
	set 'flag,0;
	set @event_marry,0;
	sc_start SC_WEDDING,3600000,0;
	sc_start SC_WEDDING,3600000,0,getcharid(3,'groom$);
	wedding;
	stopnpctimer;
	cutin "wedding_bomars02",2;
	announce "主教: 新郎" +'groom$+ "と新婦" +'bride$+ "、新たなる夫婦の誕生をここに祝福しよう！",9;
	mes "[ボマルス]";
	mes "ルーンミッドガッツ王国の主教である";
	mes "ボマルスの名において、";
	mes "汝ら二人の未来を祝福しよう。";
	next;
	mes "[ボマルス]";
	mes "二人に神の祝福を！";
	close2;
	cutin "wedding_bomars03",255;
	end;
OnTimer180000:
	announce "主教: 返事が遅い……次の式を行うとしよう。",9;
	set 'flag,0;
	stopnpctimer;
	//タイムアップの場合は嫁にフラグを仕込む
	//結婚処理直前にチェックすることで、結婚処理が重複するのを防止！
	if(attachrid(getcharid(3,'bride$)))
		set @defend,1;
	end;
}

//=======================Solo軍団==============================
prt_church.gat,97,102,0	script	ソロ軍団#プロンテラ	105,{
	mes "[ソロ軍団]";
	mes "精錬は1人で出来ちゃうぞ！";
	close;
}

prt_church.gat,98,102,0	script	ソロ軍団#ゲフェン	705,{
	mes "[ソロ軍団]";
	mes "ダンジョンでパーティーは贅沢だ！";
	close;
}

prt_church.gat,99,102,0	script	ソロ軍団#モロク		707,{
	mes "[ソロ軍団]";
	mes "私には心に決めたNPCがいる！";
	close;
}

prt_church.gat,100,102,0	script	ソロ軍団#フェイヨン	708,{
	mes "[ソロ軍団]";
	mes "生まれて転職まで独りでした！";
	close;
}

prt_church.gat,101,102,0	script	ソロ軍団#アマツ	767,{
	mes "[ソロ軍団]";
	mes "クリスマスにはシングルベ～ル！";
	close;
}

prt_church.gat,102,102,0	script	ソロ軍団#コンロン	780,{
	mes "[ソロ軍団]";
	mes "私たちは無敵のソロ軍団！";
	close;
}
