//====================================================================
//Ragnarok Online Swordman jobchange script
//
//　■ CHANGE_SM -> 0～1, 0～4(Old)
//     OLD_CLASS -> 転生前の職業
//====================================================================

//==========================================
// 試験申請および転職
//------------------------------------------

izlude_in.gat,74,172,4	script	剣士ギルド員#SM	119,{
	if(Upper == UPPER_HIGH && (OLD_CLASS == Job_Knight || OLD_CLASS == Job_Crusader)) {
		if(Job == Job_Novice) {
			mes "[剣士ギルド員]";
			mes "ハハハ！";
			mes "生まれ変わってもまたソードマンに";
			mes "なりたいとは、嬉しいことを";
			mes "言うじゃねーか！";
			next;
			if(getskilllv(1) < 9) {
				mes "[剣士ギルド員]";
				mes "わしは今忙しいから、";
				mes "もう少し剣を振ってから来い。";
				mes "まずは、JobLvを10にまで成長させて、";
				mes "^0000FF「基本スキル」のレベルを9　^000000に";
				mes "してくるってことだ。";
				next;
				mes "[剣士ギルド員]";
				mes "ちょっと教えておくとだな、";
				mes "^0000FF「基本スキル」^000000のレベルは";
				mes "^0000FF「スキルリスト」^000000ウィンドウで";
				mes "上げることができる。";
				next;
				mes "[剣士ギルド員]";
				mes "そして、^0000FF「スキルリスト」^000000ウィンドウは";
				mes "^0000FF「基本情報」^000000ウィンドウ内の";
				mes "^0000FF「Skill」^000000ボタンで表示されるからな。";
				next;
				mes "[剣士ギルド員]";
				mes "最後に忘れちゃならないのは";
				mes "スキルのレベルを上げるには、";
				mes "スキルポイントを割り振った後、";
				mes "^FF0000「確定」^000000ボタンが";
				mes "必要ってことだよ。";
				mes "注意しろよ。";
				next;
				mes "[剣士ギルド員]";
				mes "今までどうしてきたか知らんが";
				mes "このままではソードマンとして";
				mes "認められん。";
				close;
			}
			mes "[剣士ギルド員]";
			mes "よし、問題ないな。";
			mes "手続きも特にいらん。";
			mes "すぐに転職させてやろう。";
			next;
			unequip;
			jobchange Job_Swordman,UPPER_HIGH;
			//setquest 50615;
			//setquest 50670;
			//setquest 50725;
			skill 144,1,0;
			skill 145,1,0;
			skill 146,1,0;
			mes "[剣士ギルド員]";
			mes "よし、引き締まったな。";
			mes "これからも修錬をサボるなよ！";
			close;
		}
	}
	if(Upper == UPPER_HIGH) {
		mes "[剣士ギルド員]";
		mes "うん？";
		mes "なんだ？";
		mes "わしは剣士ギルドの者だ。";
		next;
		mes "[剣士ギルド員]";
		mes "何だって言うんだ……";
		mes "わしは今眠いんだ。";
		mes "用が無いなら帰ってくれ。";
		close;
	}
	mes "[剣士ギルド員]";
	mes "わしは、ここ剣士ギルドの";
	mes "転職係！何の用だ？";
	next;
	switch (select("ソードマンに転職する","ソードマンについて聞く","ソードマン転職要件を聞く","なんでもありません")) {
	case 1:
		if(Job == Job_Swordman) {
			mes "[剣士ギルド員]";
			mes "うはははは！";
			mes "面白いジョーダンじゃねーか！";
			mes "君はもうソードマンだろう？";
			next;
			mes "[組合員マンス]";
			mes "面白い奴だな！";
			mes "ソードマンになったのなら、";
			mes "冒険者アカデミーに";
			mes "行ってみるといいぞ。";
			next;
			mes "[組合員マンス]";
			mes "この建物を出たら";
			mes "冒険者アカデミーのサポートを";
			mes "行っている奴がいるから、";
			mes "送ってもらうといいぞ！";
			close;
		}
		if(Job != Job_Novice) {
			mes "[剣士ギルド員]";
			mes "はは！　まったく、変なこと言うな！";
			mes "君はもう他の職業に";
			mes "なっているではないか！";
			close;
		}
		break;
	case 2:
		mes "[剣士ギルド員]";
		mes "ソードマンについて知りたい？";
		mes "よし、説明しよう！";
		next;
		mes "[剣士ギルド員]";
		mes "ソードマンの一番大きな特徴は、";
		mes "近接戦で最強の威力を";
		mes "発揮できるってことだ！";
		mes "ソードマンが接近戦に";
		mes "最強な理由は３つ！";
		next;
		mes "[剣士ギルド員]";
		mes "1つ目、他職業に比べて";
		mes "HPがより高い！";
		mes "2つ目、弓と杖を除いた、全ての";
		mes "武器を使える！だから状況によって";
		mes "必要な武器を選べる！";
		next;
		mes "[剣士ギルド員]";
		mes "3つ目、ソードマンのスキルは、大抵";
		mes "強力な物理打撃を与えるものが多い。";
		mes "簡単な説明だが、これで十分だ。";
		mes "何故かというと、ソードマンは世界で";
		mes "一番格好いい職業で、そもそも";
		mes "説明などは、必要がないからだ！";
		close;
	case 3:
		mes "[剣士ギルド員]";
		mes "ソードマンになりたいのか!?";
		if(Job != Job_Novice) {
			if(Job == Job_Swordman) {
				mes "……っていうか、";
				mes "君はもうソードマンだろう……？";
			}
			else {
				mes "しかし、君はもう他の職業に";
				mes "なっているだろう？";
			}
			mes "それでも聞きたい……？";
			mes "まあ、なら教えよう。";
		}
		mes "[剣士ギルド員]";
		mes "ソードマンになるためには、";
		mes "まず、^0000FF「基本スキル」のレベルを9^000000 に";
		mes "上げてからじゃないと駄目だ。";
		next;
		mes "[剣士ギルド員]";
		mes "まずは、JobLvを10にまで成長させて、";
		mes "^0000FF「基本スキル」のレベルを9^000000 に";
		mes "してくるってことだ。";
		mes "^0000FF「基本スキル」^000000のレベルは";
		mes "^0000FF「スキルリスト」^000000ウィンドウで";
		mes "上げることができる。";
		next;
		mes "[剣士ギルド員]";
		mes "^0000FF「スキルリスト」^000000ウィンドウは";
		mes "^0000FF「基本情報」^000000ウィンドウ内の";
		mes "^0000FF「Skill」^000000ボタンで表示されるぞ。";
		next;
		mes "[剣士ギルド員]";
		mes "最後に忘れちゃならないのは";
		mes "スキルのレベルを上げるには、";
		mes "スキルポイントを割り振った後、";
		mes "^FF0000「確定」^000000ボタンが";
		mes "必要ってことだよ。";
		mes "注意しろよ。";
		next;
		mes "[剣士ギルド員]";
		mes "まあ、いま言ったことを済ませば、";
		mes "ソードマンになる要件が全部揃うから、";
		mes "好きな時にいつでも";
		mes "転職できるのだ。";
		close2;
		cutin "start_020_jp.bmp",4;
		end;
	case 4:
		mes "[剣士ギルド員]";
		mes "ははは！君を見ていると、";
		mes "わしの若い頃を思い出すよ！";
		close;
	}
	//case1の続き
	if(CHANGE_SM==0) {
		mes "[剣士ギルド員]";
		mes "ソードマンに転職したいか？";
		mes "よし、なら先に";
		mes "申し込みをするのだ。";
		next;
		if(select("転職申し込みをする","やめる")==2) {
			mes "[剣士ギルド員]";
			mes "そうか……気が変わったら";
			mes "また来な。";
			close;
		}
		mes "[剣士ギルド員]";
		mes "そこにサインして……よし！";
		mes "この申込書はすぐ処理させよう。";
		mes "あ、転職要件を満たしたら";
		mes "すぐ転職できるぞ。";
		mes "転職要件を満たしているか調べるか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[剣士ギルド員]";
			mes "転職要件について知らない部分が";
			mes "あったら、わしに聞いてみろ。";
			mes "あとは、こっちが提示した条件を";
			mes "満たすだけだ。では、幸運を祈る！";
			close;
		}
		set CHANGE_SM,1;
		mes "[剣士ギルド員]";
		mes "ほう？　さてと、確認してみようか？";
		next;
	}
	mes "[剣士ギルド員]";
	mes "それじゃ、早速ソードマンに";
	mes "転職できるか確認を行うぞ！";
	next;
	mes "[剣士ギルド員]";
	mes "……ほう。";
	next;
	mes "[剣士ギルド員]";
	mes "……ふむふむ。";
	next;
	if(getskilllv(1) < 9 || SkillPoint) {
		mes "[剣士ギルド員]";
		mes "おい、君。「基本スキル」のレベルが、";
		mes "規定水準になっていないぞ。";
		mes "まずは、JobLvを10にまで成長させて、";
		mes "^0000FF「基本スキル」のレベルを9^000000 に";
		mes "してきなさい。";
		next;
		mes "[剣士ギルド員]";
		mes "^0000FF「基本スキル」^000000のレベルは";
		mes "^0000FF「スキルリスト」^000000ウィンドウで";
		mes "上げることができる。";
		mes "^0000FF「スキルリスト」^000000ウィンドウは";
		mes "^0000FF「基本情報」^000000ウィンドウ内の";
		mes "^0000FF「Skill」^000000ボタンで表示されるぞ。";
		next;
		mes "[剣士ギルド員]";
		mes "最後に忘れちゃならないのは";
		mes "スキルのレベルを上げるには、";
		mes "スキルポイントを割り振った後、";
		mes "^FF0000「確定」^000000ボタンが";
		mes "必要ってことだから。";
		mes "注意してくれよ。";
		close2;
		cutin "start_020_jp.bmp",4;
		end;
	}
	mes "[剣士ギルド員]";
	mes "^0000FF「基本スキル」^000000のレベルは十分だし、";
	mes "根性もありそうだな。";
	mes "実戦試験がまだまだのようだが、";
	mes "これから経験を積めば問題ないだろう！";
	next;
	mes "[剣士ギルド員]";
	mes "おめでとう！";
	mes "君は、これからそーーどまんという";
	mes "素晴らしい職業になるわけだ！";
	mes "君をソードマンに任命する！";
	next;
	getitem 11025,1;
	unequip;
	jobchange Job_Swordman;
	set CHANGE_SM,0;
	setquest 50165;
	mes "[剣士ギルド員]";
	mes "そして、これを受け取るがいい！";
	mes "このソードマンの書を読めば、";
	mes "君はソードマンとして";
	mes "正しく歩んでいけるだろう！";
	next;
	mes "[剣士ギルド員]";
	mes "ソードマンになったことをもう一度";
	mes "お祝いする。これから";
	mes "剣士ギルドのため、";
	mes "たくさん力を貸してくれ！";
	close;
OnInit:
	waitingroom "転職",0;
	end;
}


//==========================================
// 実地試験
//------------------------------------------
//転職試験撤去
//izlude_in.gat,62,170,6	script	剣士ギルド員	85,{
//	if(Job == Job_Swordman) {
//		mes "[剣士ギルド員]";
//		mes "止まれ！ここは初心者実地試験場だ！";
//		mes "既に転職したお前が入る理由はない！";
//		mes "帰れ！";
//		close;
//	}
//	if(Job != Job_Novice) {
//		mes "[剣士ギルド員]";
//		mes "何者だ！もう他の職業になっている";
//		mes "お前が、ここに来るんじゃない！";
//		close;
//	}
//	if(getskilllv(1) < 9) {
//		mes "[剣士ギルド員]";
//		mes "止まれ！初心者スキルポイントが";
//		mes "９にもならない素人が来る所じゃない！";
//		mes "スキルポイントが９以上になったら、";
//		mes "転職試験場に入らせるからな。";
//		close;
//	}
//	switch(CHANGE_SM) {
//	case 0:
//		mes "[剣士ギルド員]";
//		mes "止まれ！剣士転職試験を";
//		mes "受けたいなら、転職申込書を";
//		mes "書いてからだ！";
//		close;
//	default:
//		warp "izlude_in.gat",39,170;
//		end;
//	case 4:
//		mes "[剣士ギルド員]";
//		mes "止まれ！まず中央のギルド員に";
//		mes "問い合わせてからだ！";
//		close;
//	}
//}

//==============================================================
izlude_in.gat,30,175,4	script	剣士ギルド員	92,{
	mes "[剣士ギルド員]";
	mes "実地試験に関して、簡単に説明しよう！";
	mes "よーく聞いて、あとで変な質問とか";
	mes "しないように！";
	next;
	mes "[剣士ギルド員]";
	mes "この試験の目的は、丈夫な体力と強靭な";
	mes "精神力が必要である剣士の才能が";
	mes "あるかどうかをテストするのだ！";
	mes "もちろん才能がなければ、";
	mes "試験で落ちてしまうだろう。";
	next;
	mes "[剣士ギルド員]";
	mes "試験の^33ff55合格条件^000000は、すごーく簡単だ！";
	mes "試験場の全てのコースを";
	mes "無事に通過して、最後の";
	mes "チェックポイントで待っている試験官に";
	mes "合格認定をもらうだけでいいんだ。";
	next;
	mes "[剣士ギルド員]";
	mes "反対に、放棄宣言をしたり、最後の";
	mes "チェックポイントに到着できなかった";
	mes "場合は不合格になる、もし、放棄宣言を";
	mes "したいなら、各コース入り口に";
	mes "戻ったり、各チェックポイントの";
	mes "関係者に話したらいい。";
	next;
	mes "[剣士ギルド員]";
	mes "試験場は３つのコースになっていて、";
	mes "コースを離脱したら、地下洞窟の";
	mes "ランダムな位置に落ちてしまうから、";
	mes "注意した方がいい。";
	mes "それじゃ、幸運を祈る。";
	close;
}

//==============================================================
izlude_in.gat,30,163,0	script	試験場職員	105,{
	switch(CHANGE_SM) {
	default:
		mes "[試験場職員]";
		mes "む、どうやって入ってきたんだ？";
		close2;
		warp "izlude_in.gat",63,169;
		end;
	case 1:
		mes "[試験場職員]";
		mes "剣士になりたいのか？ふん、";
		mes "まあ、才能はあるみたいだな。";
		mes "これからの人生に比べたら、ここの";
		mes "苦難は、何ともないだろう！";
		mes "緊張するな！お前ならできる！";
		close2;
		set CHANGE_SM,2;
		break;
	case 2:
		mes "[試験場職員]";
		mes "失敗したのか…";
		mes "これをもっていけ";
		close2;
		getitem 512,5;
		set CHANGE_SM,3;
		break;
	case 3:
		mes "[試験場職員]";
		mes "諦めるな！再挑戦だ”";
		close2;
		break;
	}
	warp "sword_1-1.gat",10,245;
	end;
}

//==============================================================
sword_1-1.gat,7,245,0	script	試験場サポーター#1	45,1,3,{
	end;
OnTouch:
	mes "[試験場サポーター]";
	mes "受験生 " +strcharinfo(0)+ "、放棄宣言をしますか？";
	next;
	if(select("はい","いいえ")==1) {
		announce "試験場サポーター: 受験生 " +strcharinfo(0)+ " が試験を放棄しました。",9;
		warp "izlude_in.gat",65,165;
		end;
	}
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: warp "sword_1-1.gat",10,245; break;
		case 2: warp "sword_1-1.gat",11,207; break;
		case 3: warp "sword_1-1.gat",11,169; break;
	}
	end;
}

sword_1-1.gat,8,207,0	duplicate(試験場サポーター#1)	試験場サポーター#2	45,1,1
sword_1-1.gat,8,169,0	duplicate(試験場サポーター#1)	試験場サポーター#3	45,1,1

//==============================================================
sword_1-1.gat,192,244,0	script	試験場サポーター#4	45,1,3,{
	end;
OnTouch:
	set '@num,strnpcinfo(2);
	announce "試験場サポーター: 受験生 " +strcharinfo(0)+ "、第" +(('@num==4)? "１": ('@num==5)? "２": "３")+ "ポイント通過。",9;
	switch('@num) {
		case 4: warp "sword_1-1.gat",215,244; break;
		case 5: warp "sword_1-1.gat",215,205; break;
		case 6: warp "sword_1-1.gat",215,167; break;
	}
	end;
}

sword_1-1.gat,193,207,0	duplicate(試験場サポーター#4)	試験場サポーター#5	45,1,1
sword_1-1.gat,193,168,0	duplicate(試験場サポーター#4)	試験場サポーター#6	45,1,1

//==============================================================
sword_1-1.gat,230,242,2		script	試験場サポーター#7	105,{
	mes "[試験場サポーター]";
	mes "放棄宣言をするのか？";
	next;
	if(select("はい","いいえ")==1) {
		announce "試験場サポーター: 受験生 " +strcharinfo(0)+ " が試験を放棄しました。",9;
		warp "izlude_in.gat",65,165;
		end;
	}
	mes "[試験場サポーター]";
	mes "よーし！";
	mes "燃える若いパワーで立ち向かうのだ！";
	close;
}

sword_1-1.gat,230,204,2		duplicate(試験場サポーター#7)	試験場サポーター#8	105

//==============================================================
sword_1-1.gat,230,245,2		script	医療担当サポーター#1	105,{
	mes "[医療担当サポーター]";
	mes "ここが第" +((strnpcinfo(2)==1)? "１": "２")+ "チェックポイントだ！";
	mes "体力を回復してあげるから頑張れよ！";
	heal 1000,0;
	close;
}

sword_1-1.gat,230,207,2		duplicate(医療担当サポーター#1)	医療担当サポーター#2	105

//==============================================================
sword_1-1.gat,223,167,4	script	マンシュタイン	92,{
	announce "マンシュタイン: 受験生 " +strcharinfo(0)+ "、試験に合格しました。",9;
	set CHANGE_SM,4;
	mes "[マンシュタイン]";
	mes "試験の合格、おめでとうございます！";
	mes "既に合格の旨は、";
	mes "転職管理課に伝えました。";
	mes "ここを出て、中央の転職管理職員の";
	mes "ところに行って下さい。";
	close2;
	warp "izlude_in.gat",66,173;
	end;
}

//==============================================================
sword_1-1.gat,16,250,0		script	SM_1stfall	-1,{
	switch(rand(5)) {
		case 0:	warp "sword_1-1.gat",65,56; end;
		case 1:	warp "sword_1-1.gat",29,26; end;
		case 2:	warp "sword_1-1.gat",43,16; end;
		case 3:	warp "sword_1-1.gat",23,112; end;
		case 4:	warp "sword_1-1.gat",58,83; end;
	}
}
sword_1-1.gat,16,251,0		duplicate(SM_1stfall)	#swordwarp6101_a	139,0,1
sword_1-1.gat,19,251,0		duplicate(SM_1stfall)	#swordwarp6101_b	139,0,1
sword_1-1.gat,17,250,0		duplicate(SM_1stfall)	#swordwarp6101_c	139,1,0
sword_1-1.gat,16,238,0		duplicate(SM_1stfall)	#swordwarp6102_a	139,0,1
sword_1-1.gat,19,238,0		duplicate(SM_1stfall)	#swordwarp6102_b	139,0,1
sword_1-1.gat,17,239,0		duplicate(SM_1stfall)	#swordwarp6102_c	139,0,1
sword_1-1.gat,28,247,0		duplicate(SM_1stfall)	#swordwarp6103_a	139,4,0
sword_1-1.gat,33,245,0		duplicate(SM_1stfall)	#swordwarp6103_b	139,0,2
sword_1-1.gat,29,242,0		duplicate(SM_1stfall)	#swordwarp6103_c	139,4,0
sword_1-1.gat,24,244,0		duplicate(SM_1stfall)	#swordwarp6103_d	139,0,2
sword_1-1.gat,38,251,0		duplicate(SM_1stfall)	#swordwarp6104_a	139,0,1
sword_1-1.gat,41,251,0		duplicate(SM_1stfall)	#swordwarp6104_b	139,0,1
sword_1-1.gat,39,250,0		duplicate(SM_1stfall)	#swordwarp6104_c	139,1,0
sword_1-1.gat,38,238,0		duplicate(SM_1stfall)	#swordwarp6105_a	139,0,1
sword_1-1.gat,41,238,0		duplicate(SM_1stfall)	#swordwarp6105_b	139,0,1
sword_1-1.gat,39,239,0		duplicate(SM_1stfall)	#swordwarp6105_c	139,1,0
sword_1-1.gat,54,251,0		duplicate(SM_1stfall)	#swordwarp6106_a	139,0,1
sword_1-1.gat,71,251,0		duplicate(SM_1stfall)	#swordwarp6106_b	139,0,1
sword_1-1.gat,62,250,0		duplicate(SM_1stfall)	#swordwarp6106_c	139,9,0
sword_1-1.gat,62,247,0		duplicate(SM_1stfall)	#swordwarp6107_a	139,8,0
sword_1-1.gat,71,244,0		duplicate(SM_1stfall)	#swordwarp6107_b	139,0,2
sword_1-1.gat,63,242,0		duplicate(SM_1stfall)	#swordwarp6107_c	139,8,0
sword_1-1.gat,54,244,0		duplicate(SM_1stfall)	#swordwarp6107_d	139,0,2
sword_1-1.gat,54,238,0		duplicate(SM_1stfall)	#swordwarp6108_a	139,0,1
sword_1-1.gat,71,238,0		duplicate(SM_1stfall)	#swordwarp6108_b	139,0,1
sword_1-1.gat,62,239,0		duplicate(SM_1stfall)	#swordwarp6108_c	139,9,0
sword_1-1.gat,102,247,0		duplicate(SM_1stfall)	#swordwarp6109_a	139,2,0
sword_1-1.gat,105,245,0		duplicate(SM_1stfall)	#swordwarp6109_b	139,0,2
sword_1-1.gat,103,242,0		duplicate(SM_1stfall)	#swordwarp6109_c	139,2,0
sword_1-1.gat,100,244,0		duplicate(SM_1stfall)	#swordwarp6109_d	139,0,2
sword_1-1.gat,156,249,0		duplicate(SM_1stfall)	#swordwarp6110_a	139,14,0
sword_1-1.gat,156,248,0		duplicate(SM_1stfall)	#swordwarp6110_b	139,14,0
sword_1-1.gat,170,249,0		duplicate(SM_1stfall)	#swordwarp6110_c	139,1,0
sword_1-1.gat,170,248,0		duplicate(SM_1stfall)	#swordwarp6110_d	139,1,0
sword_1-1.gat,156,245,0		duplicate(SM_1stfall)	#swordwarp6111_a	139,14,0
sword_1-1.gat,156,244,0		duplicate(SM_1stfall)	#swordwarp6111_b	139,14,0
sword_1-1.gat,170,245,0		duplicate(SM_1stfall)	#swordwarp6111_c	139,1,0
sword_1-1.gat,170,244,0		duplicate(SM_1stfall)	#swordwarp6111_d	139,1,0
sword_1-1.gat,156,241,0		duplicate(SM_1stfall)	#swordwarp6112_a	139,14,0
sword_1-1.gat,156,240,0		duplicate(SM_1stfall)	#swordwarp6112_b	139,14,0
sword_1-1.gat,170,241,0		duplicate(SM_1stfall)	#swordwarp6112_c	139,1,0
sword_1-1.gat,170,240,0		duplicate(SM_1stfall)	#swordwarp6112_d	139,1,0
sword_1-1.gat,180,251,0		duplicate(SM_1stfall)	#swordwarp6113_a	139,0,1
sword_1-1.gat,183,251,0		duplicate(SM_1stfall)	#swordwarp6113_b	139,0,1
sword_1-1.gat,181,250,0		duplicate(SM_1stfall)	#swordwarp6113_c	139,1,0
sword_1-1.gat,180,238,0		duplicate(SM_1stfall)	#swordwarp6114_a	139,0,1
sword_1-1.gat,183,238,0		duplicate(SM_1stfall)	#swordwarp6114_b	139,0,1
sword_1-1.gat,181,239,0		duplicate(SM_1stfall)	#swordwarp6114_c	139,1,0

//==============================================================
sword_1-1.gat,56,211,0		script	SM_2ndfall	-1,{
	switch(rand(5)) {
		case 0:	warp "sword_1-1.gat",162,120; end;
		case 1:	warp "sword_1-1.gat",94,120; end;
		case 2:	warp "sword_1-1.gat",94,85; end;
		case 3:	warp "sword_1-1.gat",162,85; end;
		case 4:	warp "sword_1-1.gat",130,47; end;
	}
}
sword_1-1.gat,26,212,0		duplicate(SM_2ndfall)	#swordwarp6201_a	139,10,0
sword_1-1.gat,47,212,0		duplicate(SM_2ndfall)	#swordwarp6201_b	139,10,0
sword_1-1.gat,68,212,0		duplicate(SM_2ndfall)	#swordwarp6201_c	139,10,0
sword_1-1.gat,87,212,0		duplicate(SM_2ndfall)	#swordwarp6201_d	139,10,0
sword_1-1.gat,26,210,0		duplicate(SM_2ndfall)	#swordwarp6201_e	139,10,0
sword_1-1.gat,47,210,0		duplicate(SM_2ndfall)	#swordwarp6201_f	139,10,0
sword_1-1.gat,68,210,0		duplicate(SM_2ndfall)	#swordwarp6201_g	139,10,0
sword_1-1.gat,87,210,0		duplicate(SM_2ndfall)	#swordwarp6201_h	139,10,0
sword_1-1.gat,16,206,0		duplicate(SM_2ndfall)	#swordwarp6202_a	139,0,3
sword_1-1.gat,97,206,0		duplicate(SM_2ndfall)	#swordwarp6202_b	139,0,3
sword_1-1.gat,26,203,0		duplicate(SM_2ndfall)	#swordwarp6203_a	139,10,0
sword_1-1.gat,47,203,0		duplicate(SM_2ndfall)	#swordwarp6203_b	139,10,0
sword_1-1.gat,68,203,0		duplicate(SM_2ndfall)	#swordwarp6203_c	139,10,0
sword_1-1.gat,87,203,0		duplicate(SM_2ndfall)	#swordwarp6203_d	139,10,0
sword_1-1.gat,26,201,0		duplicate(SM_2ndfall)	#swordwarp6203_e	139,10,0
sword_1-1.gat,47,201,0		duplicate(SM_2ndfall)	#swordwarp6203_f	139,10,0
sword_1-1.gat,68,201,0		duplicate(SM_2ndfall)	#swordwarp6203_g	139,10,0
sword_1-1.gat,87,201,0		duplicate(SM_2ndfall)	#swordwarp6203_h	139,10,0
sword_1-1.gat,113,212,0		duplicate(SM_2ndfall)	#swordwarp6204_a	139,14,0
sword_1-1.gat,125,212,0		duplicate(SM_2ndfall)	#swordwarp6204_b	139,2,0
sword_1-1.gat,113,210,0		duplicate(SM_2ndfall)	#swordwarp6205_a	139,14,0
sword_1-1.gat,125,210,0		duplicate(SM_2ndfall)	#swordwarp6205_b	139,2,0
sword_1-1.gat,100,206,0		duplicate(SM_2ndfall)	#swordwarp6205_c	139,0,3
sword_1-1.gat,127,206,0		duplicate(SM_2ndfall)	#swordwarp6205_d	139,0,3
sword_1-1.gat,113,203,0		duplicate(SM_2ndfall)	#swordwarp6205_e	139,14,0
sword_1-1.gat,125,203,0		duplicate(SM_2ndfall)	#swordwarp6205_f	139,2,0
sword_1-1.gat,113,201,0		duplicate(SM_2ndfall)	#swordwarp6206_a	139,14,0
sword_1-1.gat,125,201,0		duplicate(SM_2ndfall)	#swordwarp6206_b	139,2,0
sword_1-1.gat,132,212,0		duplicate(SM_2ndfall)	#swordwarp6207_0	139,2,0
sword_1-1.gat,155,212,0		duplicate(SM_2ndfall)	#swordwarp6207_a	139,21,0
sword_1-1.gat,181,212,0		duplicate(SM_2ndfall)	#swordwarp6207_b	139,2,0
sword_1-1.gat,132,210,0		duplicate(SM_2ndfall)	#swordwarp6208_0	139,2,0
sword_1-1.gat,155,210,0		duplicate(SM_2ndfall)	#swordwarp6208_a	139,21,0
sword_1-1.gat,181,210,0		duplicate(SM_2ndfall)	#swordwarp6208_b	139,2,0
sword_1-1.gat,130,206,0		duplicate(SM_2ndfall)	#swordwarp6208_c	139,0,3
sword_1-1.gat,183,206,0		duplicate(SM_2ndfall)	#swordwarp6208_d	139,0,3
sword_1-1.gat,132,203,0		duplicate(SM_2ndfall)	#swordwarp6208_1	139,2,0
sword_1-1.gat,155,203,0		duplicate(SM_2ndfall)	#swordwarp6208_e	139,21,0
sword_1-1.gat,181,203,0		duplicate(SM_2ndfall)	#swordwarp6208_f	139,2,0
sword_1-1.gat,132,201,0		duplicate(SM_2ndfall)	#swordwarp6209_0	139,2,0
sword_1-1.gat,155,201,0		duplicate(SM_2ndfall)	#swordwarp6209_a	139,21,0
sword_1-1.gat,181,201,0		duplicate(SM_2ndfall)	#swordwarp6209_b	139,2,0

//==============================================================
sword_1-1.gat,17,174,0		script	SM_3rdfall	-1,{
	switch(rand(5)) {
		case 0:	warp "sword_1-1.gat",195,15; end;
		case 1:	warp "sword_1-1.gat",195,38; end;
		case 2:	warp "sword_1-1.gat",231,30; end;
		case 3:	warp "sword_1-1.gat",198,65; end;
		case 4:	warp "sword_1-1.gat",196,116; end;
	}
}
sword_1-1.gat,17,174,0		duplicate(SM_3rdfall)	#swordwarp6301_a	139,2,0
sword_1-1.gat,17,163,0		duplicate(SM_3rdfall)	#swordwarp6302_a	139,2,0
sword_1-1.gat,29,171,0		duplicate(SM_3rdfall)	#swordwarp6303_a	139,2,0
sword_1-1.gat,31,168,0		duplicate(SM_3rdfall)	#swordwarp6303_b	139,0,2
sword_1-1.gat,28,166,0		duplicate(SM_3rdfall)	#swordwarp6303_c	139,2,0
sword_1-1.gat,26,168,0		duplicate(SM_3rdfall)	#swordwarp6303_d	139,0,2
sword_1-1.gat,36,169,0		duplicate(SM_3rdfall)	#swordwarp6304_a	139,0,0
sword_1-1.gat,37,169,0		duplicate(SM_3rdfall)	#swordwarp6304_b	139,0,0
sword_1-1.gat,37,168,0		duplicate(SM_3rdfall)	#swordwarp6304_c	139,0,0
sword_1-1.gat,36,168,0		duplicate(SM_3rdfall)	#swordwarp6304_d	139,0,0
sword_1-1.gat,40,175,0		duplicate(SM_3rdfall)	#swordwarp6305_a	139,0,1
sword_1-1.gat,41,175,0		duplicate(SM_3rdfall)	#swordwarp6305_b	139,0,1
sword_1-1.gat,41,171,0		duplicate(SM_3rdfall)	#swordwarp6306_a	139,1,0
sword_1-1.gat,41,170,0		duplicate(SM_3rdfall)	#swordwarp6306_b	139,1,0
sword_1-1.gat,41,167,0		duplicate(SM_3rdfall)	#swordwarp6306_c	139,1,0
sword_1-1.gat,41,166,0		duplicate(SM_3rdfall)	#swordwarp6306_d	139,1,0
sword_1-1.gat,42,169,0		duplicate(SM_3rdfall)	#swordwarp6306_e	139,0,1
sword_1-1.gat,43,170,0		duplicate(SM_3rdfall)	#swordwarp6306_f	139,0,1
sword_1-1.gat,43,167,0		duplicate(SM_3rdfall)	#swordwarp6306_g	139,0,1
sword_1-1.gat,40,162,0		duplicate(SM_3rdfall)	#swordwarp6307_a	139,0,1
sword_1-1.gat,41,162,0		duplicate(SM_3rdfall)	#swordwarp6307_b	139,0,1
sword_1-1.gat,46,175,0		duplicate(SM_3rdfall)	#swordwarp6308_a	139,0,1
sword_1-1.gat,51,175,0		duplicate(SM_3rdfall)	#swordwarp6308_b	139,0,1
sword_1-1.gat,47,174,0		duplicate(SM_3rdfall)	#swordwarp6308_c	139,1,0
sword_1-1.gat,50,174,0		duplicate(SM_3rdfall)	#swordwarp6308_d	139,1,0
sword_1-1.gat,48,173,0		duplicate(SM_3rdfall)	#swordwarp6308_e	139,0,1
sword_1-1.gat,49,173,0		duplicate(SM_3rdfall)	#swordwarp6308_f	139,0,1
sword_1-1.gat,46,162,0		duplicate(SM_3rdfall)	#swordwarp6309_a	139,0,1
sword_1-1.gat,51,162,0		duplicate(SM_3rdfall)	#swordwarp6309_b	139,0,1
sword_1-1.gat,47,163,0		duplicate(SM_3rdfall)	#swordwarp6309_c	139,1,0
sword_1-1.gat,50,163,0		duplicate(SM_3rdfall)	#swordwarp6309_d	139,1,0
sword_1-1.gat,48,164,0		duplicate(SM_3rdfall)	#swordwarp6309_e	139,0,1
sword_1-1.gat,49,164,0		duplicate(SM_3rdfall)	#swordwarp6309_f	139,0,1
sword_1-1.gat,54,170,0		duplicate(SM_3rdfall)	#swordwarp6310_a	139,0,1
sword_1-1.gat,55,170,0		duplicate(SM_3rdfall)	#swordwarp6310_b	139,0,1
sword_1-1.gat,54,167,0		duplicate(SM_3rdfall)	#swordwarp6310_c	139,0,1
sword_1-1.gat,55,167,0		duplicate(SM_3rdfall)	#swordwarp6310_d	139,0,1
sword_1-1.gat,53,169,0		duplicate(SM_3rdfall)	#swordwarp6310_e	139,1,0
sword_1-1.gat,53,168,0		duplicate(SM_3rdfall)	#swordwarp6310_f	139,1,0
sword_1-1.gat,56,169,0		duplicate(SM_3rdfall)	#swordwarp6310_g	139,1,0
sword_1-1.gat,56,168,0		duplicate(SM_3rdfall)	#swordwarp6310_h	139,1,0
sword_1-1.gat,58,175,0		duplicate(SM_3rdfall)	#swordwarp6311_a	139,0,1
sword_1-1.gat,59,174,0		duplicate(SM_3rdfall)	#swordwarp6311_b	139,1,0
sword_1-1.gat,60,173,0		duplicate(SM_3rdfall)	#swordwarp6311_c	139,0,1
sword_1-1.gat,61,172,0		duplicate(SM_3rdfall)	#swordwarp6311_d	139,1,0
sword_1-1.gat,58,162,0		duplicate(SM_3rdfall)	#swordwarp6312_a	139,0,1
sword_1-1.gat,59,163,0		duplicate(SM_3rdfall)	#swordwarp6312_b	139,1,0
sword_1-1.gat,60,164,0		duplicate(SM_3rdfall)	#swordwarp6312_c	139,0,1
sword_1-1.gat,61,165,0		duplicate(SM_3rdfall)	#swordwarp6312_d	139,1,0
sword_1-1.gat,76,172,0		duplicate(SM_3rdfall)	#swordwarp6313_a	139,1,0
sword_1-1.gat,77,173,0		duplicate(SM_3rdfall)	#swordwarp6313_b	139,0,1
sword_1-1.gat,78,174,0		duplicate(SM_3rdfall)	#swordwarp6313_c	139,1,0
sword_1-1.gat,79,175,0		duplicate(SM_3rdfall)	#swordwarp6313_d	139,0,1
sword_1-1.gat,76,165,0		duplicate(SM_3rdfall)	#swordwarp6314_a	139,1,0
sword_1-1.gat,77,164,0		duplicate(SM_3rdfall)	#swordwarp6314_b	139,0,1
sword_1-1.gat,78,163,0		duplicate(SM_3rdfall)	#swordwarp6314_c	139,1,0
sword_1-1.gat,79,162,0		duplicate(SM_3rdfall)	#swordwarp6314_d	139,0,1
sword_1-1.gat,94,175,0		duplicate(SM_3rdfall)	#swordwarp6315_a	139,0,1
sword_1-1.gat,95,174,0		duplicate(SM_3rdfall)	#swordwarp6315_b	139,1,0
sword_1-1.gat,98,174,0		duplicate(SM_3rdfall)	#swordwarp6315_c	139,1,0
sword_1-1.gat,99,175,0		duplicate(SM_3rdfall)	#swordwarp6316_d	139,0,1
sword_1-1.gat,96,169,0		duplicate(SM_3rdfall)	#swordwarp6317_a	139,0,0
sword_1-1.gat,97,169,0		duplicate(SM_3rdfall)	#swordwarp6317_b	139,0,0
sword_1-1.gat,97,168,0		duplicate(SM_3rdfall)	#swordwarp6317_c	139,0,0
sword_1-1.gat,96,168,0		duplicate(SM_3rdfall)	#swordwarp6317_d	139,0,0
sword_1-1.gat,94,162,0		duplicate(SM_3rdfall)	#swordwarp6318_a	139,0,1
sword_1-1.gat,95,163,0		duplicate(SM_3rdfall)	#swordwarp6318_b	139,1,0
sword_1-1.gat,98,163,0		duplicate(SM_3rdfall)	#swordwarp6318_c	139,1,0
sword_1-1.gat,99,162,0		duplicate(SM_3rdfall)	#swordwarp6318_d	139,0,1
sword_1-1.gat,114,175,0		duplicate(SM_3rdfall)	#swordwarp6319_a	139,0,1
sword_1-1.gat,115,175,0		duplicate(SM_3rdfall)	#swordwarp6319_b	139,0,1
sword_1-1.gat,114,162,0		duplicate(SM_3rdfall)	#swordwarp6320_a	139,0,1
sword_1-1.gat,115,162,0		duplicate(SM_3rdfall)	#swordwarp6320_b	139,0,1
sword_1-1.gat,126,175,0		duplicate(SM_3rdfall)	#swordwarp6321_a	139,0,1
sword_1-1.gat,127,175,0		duplicate(SM_3rdfall)	#swordwarp6321_b	139,0,1
sword_1-1.gat,126,162,0		duplicate(SM_3rdfall)	#swordwarp6323_a	139,0,1
sword_1-1.gat,127,162,0		duplicate(SM_3rdfall)	#swordwarp6323_b	139,0,1
sword_1-1.gat,160,174,0		duplicate(SM_3rdfall)	#swordwarp6324_a	139,0,2
sword_1-1.gat,161,174,0		duplicate(SM_3rdfall)	#swordwarp6324_b	139,0,2
sword_1-1.gat,160,163,0		duplicate(SM_3rdfall)	#swordwarp6325_a	139,0,2
sword_1-1.gat,161,163,0		duplicate(SM_3rdfall)	#swordwarp6325_b	139,0,2
sword_1-1.gat,168,175,0		duplicate(SM_3rdfall)	#swordwarp6326_a	139,0,2
sword_1-1.gat,169,175,0		duplicate(SM_3rdfall)	#swordwarp6326_b	139,0,2
sword_1-1.gat,168,162,0		duplicate(SM_3rdfall)	#swordwarp6327_a	139,0,2
sword_1-1.gat,169,162,0		duplicate(SM_3rdfall)	#swordwarp6327_b	139,0,2
sword_1-1.gat,176,174,0		duplicate(SM_3rdfall)	#swordwarp6328_a	139,0,2
sword_1-1.gat,177,174,0		duplicate(SM_3rdfall)	#swordwarp6328_b	139,0,2
sword_1-1.gat,178,173,0		duplicate(SM_3rdfall)	#swordwarp6328_c	139,1,0
sword_1-1.gat,178,172,0		duplicate(SM_3rdfall)	#swordwarp6328_d	139,1,0
sword_1-1.gat,181,174,0		duplicate(SM_3rdfall)	#swordwarp6328_e	139,2,0
sword_1-1.gat,179,169,0		duplicate(SM_3rdfall)	#swordwarp6329_a	139,3,0
sword_1-1.gat,179,168,0		duplicate(SM_3rdfall)	#swordwarp6329_b	139,3,0
sword_1-1.gat,182,169,0		duplicate(SM_3rdfall)	#swordwarp6329_c	139,0,2
sword_1-1.gat,183,169,0		duplicate(SM_3rdfall)	#swordwarp6329_d	139,0,2
sword_1-1.gat,181,167,0		duplicate(SM_3rdfall)	#swordwarp6329_e	139,1,0
sword_1-1.gat,181,166,0		duplicate(SM_3rdfall)	#swordwarp6329_f	139,1,0
sword_1-1.gat,183,167,0		duplicate(SM_3rdfall)	#swordwarp6329_g	139,0,1
sword_1-1.gat,176,163,0		duplicate(SM_3rdfall)	#swordwarp6330_a	139,0,2
sword_1-1.gat,177,163,0		duplicate(SM_3rdfall)	#swordwarp6330_b	139,0,2
sword_1-1.gat,181,163,0		duplicate(SM_3rdfall)	#swordwarp6330_c	139,2,0
